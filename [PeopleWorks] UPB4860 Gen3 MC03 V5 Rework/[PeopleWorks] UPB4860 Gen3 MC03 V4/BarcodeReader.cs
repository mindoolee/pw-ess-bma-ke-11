using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Diagnostics;
using System.Threading;
using System.Windows.Forms;
using System.Globalization;

namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
    public class BarcodeReader
    {
        // 외부 관리 데이터
        public string strReadBarcode;
        public bool bReadOk = false;

        public int nIndex = 0;

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
            if (!_Port.IsOpen) { return; }

            {
                try
                {
                    if (_Port.BytesToRead > 0)
                    {
                        if (Len > 1000) { ClearReadBuffer(); }

                        _Port.Read(rcvBuff, Len++, 1);

                        if (rcvBuff[Math.Max((Len - 1), 0)] == 0x0D)
                        {
                            strReadBarcode = Encoding.Default.GetString(rcvBuff, 0, Len - 1);
                            Program.AppendLogMsg(String.Format("Scanner {0} : ", nIndex) + strReadBarcode, LOG_TYPE.INFO);
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
                //Thread.Sleep(1);
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


        // Read 버퍼 클리어
        private void ClearReadBuffer()
        {
            Array.Clear(rcvBuff, 0, rcvBuff.Length);
            Len = 0;
        }
    }
}
