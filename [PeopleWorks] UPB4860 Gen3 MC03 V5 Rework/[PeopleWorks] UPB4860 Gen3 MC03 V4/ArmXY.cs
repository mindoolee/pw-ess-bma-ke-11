using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
    class ArmXY
    {

        // 공통 외부 참조
        public bool bPortStat = false;

        // 내부 내용

        public SerialPort port = new SerialPort();

        public string readTemp = "";


        private byte[] byStx = new byte[] { 0x02 };
        private byte[] byEtx = new byte[] { 0x03 };
        private byte[] buff = new byte[1024];        // 수신버퍼 최대 사이즈

        public int nCurrentStep = 0;
        private int nBufferIndex = 0;
        private bool bWorkStop;


        public void Process()
        {
            if (!port.IsOpen) { return; }
            try
            {
                if (port.BytesToRead > 0)
                {
                    if (nBufferIndex > 1000) { ClearBuffer(); }


                    port.Read(buff, nBufferIndex++, 1);

                    if (buff[Math.Max((nBufferIndex - 1), 0)] == 0x1B)          // STX 가 들어온다면
                    {
                        ClearBuffer();
                        buff[0] = 0x1B;
                        nBufferIndex++;
                    }

                    if (buff[0] == 0x1B && buff[Math.Max((nBufferIndex - 1), 0)] == 0x0D && nBufferIndex == 14)   // 개수와 ETX가 맞는다면
                    {
                        // 데이터를 읽는다
                        readTemp = Encoding.ASCII.GetString(buff, 1, nBufferIndex - 2);

                        int.TryParse(readTemp.Substring(2, 4), out _SysInfo.nST2EncoderX);
                        int.TryParse(readTemp.Substring(8, 4), out _SysInfo.nST2EncoderY);
                    }


                }
            }
            catch { }

        }


        public void Start()
        {
            bWorkStop = false;
            //Thread Proc = new Thread(new ThreadStart(Process));
            //Proc.Start();
        }


        public void Stop()
        {
            bWorkStop = true;
        }

        public void SetPort(String strPortName, int nBaudRate, Parity nParity, int nDataBit, StopBits nStopBit)
        {
            port.PortName = strPortName;
            port.BaudRate = nBaudRate;
            port.Parity = nParity;
            port.DataBits = nDataBit;
            port.StopBits = nStopBit;
            bPortStat = false;

            port.RtsEnable = true;
            port.DtrEnable = true;
        }

        public bool PortOpen()
        {
            if (port.IsOpen)
            {
                try
                {
                    port.Close();
                    port.Open();
                    return true;
                }
                catch { return false; }
            }
            else
            {
                try
                {
                    port.Open();
                    return true;
                }
                catch { return false; }
            }

        }

        public void CloseComm()
        {
            bWorkStop = true;
            Stop();
            port.Close();
        }

        void ClearBuffer()
        {
            Array.Clear(buff, 0, buff.Length);
            nBufferIndex = 0;
        }
    }
}
