using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
    public class IL1000
    {

        public double[] dbDistance = new double[10];
        public bool bPortStat = false;


        private Mirae_Timer tMainTimer = new Mirae_Timer();

        private byte[] byStx = new byte[] { 0x02 };
        private byte[] byEtx = new byte[] { 0x03 };
        private byte[] buff = new byte[1024];        // 수신버퍼 최대 사이즈

        public SerialPort port = new SerialPort();
        private Stopwatch watch = new Stopwatch();

        private int nCurrentStep = 0;
        private int nBufferIndex = 0;

        private string strReadData = "";

        public void Process()
        {

            if (!port.IsOpen) { bPortStat = false; return; }


            switch (nCurrentStep)
            {
                case 0:
                    // 통신 커맨드 전송
                    try
                    {
                        port.ReadExisting();        // 버퍼비우기
                        port.DiscardInBuffer();
                        port.DiscardOutBuffer();
                        ClearBuffer();
                        WirteData("M0");
                        tMainTimer.Start(2000);
                        nCurrentStep = 10;
                    }
                    catch { }
                    break;


                case 10:
                    // 데이터가 들어오면 읽기
                    if (tMainTimer.Verify())
                    {
                        // 시간내 데이터가 안들어오면 0번으로 이동
                        bPortStat = false;
                        nCurrentStep = 0;
                    }

                    try
                    {


                        while (port.BytesToRead > 0)
                        {
                            port.Read(buff, nBufferIndex++, 1);
                            if (buff[Math.Max(nBufferIndex - 2, 0)] == 0x0D && buff[Math.Max(nBufferIndex - 1, 0)] == 0x0A)
                            {
                                strReadData = Encoding.Default.GetString(buff, 1, nBufferIndex - 2);

                                if (strReadData.Split(',').Length == 4)
                                {
                                    for (int i = 0; i < 3; i++)
                                    {
                                        double.TryParse(strReadData.Split(',')[i + 1], out dbDistance[i]);
                                    }
                                    bPortStat = true;
                                }
                                ClearBuffer();
                                tMainTimer.Start(10);        // 10ms 단위로 읽음
                                nCurrentStep++;              // 정상적인 데이터가 들어왔다면 스텝 20번으로 이동
                            }
                        }
                    }
                    catch { }
                    break;

                case 11:
                    if (!tMainTimer.Verify()) { break; }

                    nCurrentStep = 0;
                    break;
            }

        }



        public void WirteData(string strData)
        {
            try
            {
                port.Write(strData);
                port.Write(new byte[] { 0x0D, 0x0A }, 0, 2);
            }
            catch { }
        }


        public void SetPort(String strPortName, int nBaudRate, Parity nParity, int nDataBit, StopBits nStopBit)
        {
            port.PortName = strPortName;
            port.BaudRate = nBaudRate;
            port.Parity = nParity;
            port.DataBits = nDataBit;
            port.StopBits = nStopBit;

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
            port.Close();
        }

        void ClearBuffer()
        {
            Array.Clear(buff, 0, buff.Length);
            nBufferIndex = 0;
        }

    }
}
