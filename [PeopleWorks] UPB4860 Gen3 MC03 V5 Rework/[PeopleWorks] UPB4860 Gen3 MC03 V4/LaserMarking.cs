using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
    class LaserMarking
    {
        public string strReadBarcode;
        public bool bReadOk = false;

        // 시리얼 포트
        public SerialPort _Port = new SerialPort();
        private Stopwatch _tTimer = new Stopwatch();


        // 쓰레드 플래그
        private bool bWorkStop = false;

        // 수신 데이터
        private int Len = 0;
        private byte[] rcvBuff = new byte[1024];

        public void Process()
        {
            // while (!bWorkStop)
            if (!_Port.IsOpen) { return;}

            {
                try
                {
                    if (_Port.BytesToRead > 0)
                    {
                        if (Len > 1000) { ClearReadBuffer(); }

                        _Port.Read(rcvBuff, Len++, 1);

                        if (rcvBuff[Math.Max((Len - 2), 0)] == 0x23 && rcvBuff[Math.Max((Len - 1), 0)] == 0x24)
                        {
                            strReadBarcode = Encoding.Default.GetString(rcvBuff, 0, Len - 2);
                            Program.AppendLogMsg("PC < Laser : " + strReadBarcode, LOG_TYPE.INFO);

                            bReadOk = true;
                            ClearReadBuffer();
                            _Port.ReadExisting();
                        }
                    }
                }
                catch
                {
                    ClearReadBuffer();
                }
            }
        }


        public void SetPort(String strPortName, int nBaudRate, Parity nParity, int nDataBit, StopBits nStopBit)
        {
            _Port.PortName = strPortName;
            _Port.BaudRate = nBaudRate;
            _Port.Parity = nParity;
            _Port.DataBits = nDataBit;
            _Port.StopBits = nStopBit;
            _Port.RtsEnable = true;
            _Port.DtrEnable = true;

        }

        // Port Open
        public bool PortOpen()
        {
            try
            {
                _Port.Open();
                return true;
            }
            catch
            {
                return false;
            }

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

        public void CloseComm()
        {
            _Port.Close();
        }

        public bool IsOpened()
        {
            return _Port.IsOpen;
        }


        public void SendData(string strSendData)
        {
            try
            {
                List<byte> sendData = new List<byte>();

                sendData.AddRange(Encoding.UTF8.GetBytes(strSendData));
                sendData.Add(0x0D);
                sendData.Add(0x0A);
                _Port.Write(sendData.ToArray(), 0, sendData.ToArray().Length);
                Program.AppendLogMsg("PC > Laser : " + strSendData, LOG_TYPE.INFO);
            }
            catch { }
        }

        // Read 버퍼 클리어
        private void ClearReadBuffer()
        {
            Array.Clear(rcvBuff, 0, rcvBuff.Length);
            Len = 0;
        }
    }
}
