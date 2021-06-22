using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
    class BatteryTester3
    {

        public BatteryTesterStat _Status = new BatteryTesterStat();

        // 내부 내용
        public SerialPort port = new SerialPort();

        public int nStation;
        private int nBufferIndex = 0;
        private bool bWorkStop;

        public string readTemp = "";


        private byte[] byStx = new byte[] { 0x02 };
        private byte[] byEtx = new byte[] { 0x03 };
        private byte[] buff = new byte[1024];        // 수신버퍼 최대 사이즈

        public void Process()
        {
            if (!port.IsOpen) { return; }
            try
            {
                if (port.BytesToRead > 0)
                {
                    if (nBufferIndex > 1000) { ClearBuffer(); }


                    port.Read(buff, nBufferIndex++, 1);

                    if (buff[Math.Max((nBufferIndex - 1), 0)] == 0x02)          // STX 가 들어온다면
                    {
                        ClearBuffer();
                        buff[0] = 0x02;
                        nBufferIndex++;
                    }

                    if (buff[0] == 0x02 && buff[Math.Max((nBufferIndex - 1), 0)] == 0x03)   // ETX 까지 들어온다면
                    {
                        // 데이터를 읽는다
                        readTemp = Encoding.ASCII.GetString(buff, 1, nBufferIndex - 2);

                        Program.AppendLogMsg(readTemp, LOG_TYPE.INFO);
                        if (readTemp == "OK") { _Status = BatteryTesterStat.OK; }
                        else if (readTemp == "NG") { _Status = BatteryTesterStat.NG; }
                        else if (readTemp == "ST") { _Status = BatteryTesterStat.START; }
                        else if (readTemp == "ING") { _Status = BatteryTesterStat.ING; }
                        else if (readTemp == "NOREAD") { _Status = BatteryTesterStat.NOREAD; }
                        else if (readTemp == "COMMNG") { _Status = BatteryTesterStat.COMMNG; }
                        else if (readTemp == "FOWARD") { _Status = BatteryTesterStat.FOWARD; }
                        else if (readTemp == "BACKWARD") { _Status = BatteryTesterStat.BACKWARD; }

                        AppendLogMsg(String.Format("{0} << {1}", nStation, readTemp), Color.Blue);
                    }


                }
            }
            catch { }

        }

        public void WriteData(string str)
        {
            try
            {
                port.ReadExisting();
                port.Write(byStx, 0, byStx.Length);
                port.Write(str);
                port.Write(byEtx, 0, byEtx.Length);
                ClearBuffer();
                AppendLogMsg(String.Format("{0} >> {1}", nStation, str), Color.Red);
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
            bWorkStop = true;
            port.Close();
        }

        void ClearBuffer()
        {
            Array.Clear(buff, 0, buff.Length);
            nBufferIndex = 0;
        }

        //====== 로그 메세지 출력
        public static void AppendLogMsg(String str, Color clr)
        {
            Program._mainform.BeginInvoke(new Action(() => Program._mainform.ViewCommMsg(str, clr)));
        }

        public void SendOmronData(string strBarcod, string strResult, double strLen)
        {
            try
            {
                port.Write(byStx, 0, byStx.Length);
                port.Write(String.Format("LN:{0},{1},{2}", strBarcod, strResult, strLen));
                port.Write(byEtx, 0, byEtx.Length);
                AppendLogMsg(String.Format("{0} >> LN:{1},{2},{3}", nStation, strBarcod, strResult, strLen), Color.Red);
            }
            catch { }
        }
    }
}
