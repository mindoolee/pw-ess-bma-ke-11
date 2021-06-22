using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Diagnostics;
using System.Threading;
using System.Drawing;

namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
    class BatteryTester2
    {
        // 공통 외부 참조
        public bool bPortStat = false;

        public int nStation;

        // 외부 참조 데이터
        public bool bRequest = false;
        public bool bStart = false;
        public bool bCsStart = false;
        public bool bStop = false;
        public bool bCheckOkng = false;
        public bool bBarcodeRead = false;
        public bool bCommFail = false;

        public string strReadData = "";

        public string strSendBcd = "";

        // 내부 내용
        public SerialPort port = new SerialPort();
        public Stopwatch watch = new Stopwatch();
        public Stopwatch _tShowTimer = new Stopwatch();

        public int nCurrentStep = 0;
        private int nBufferIndex = 0;
        private bool bWorkStop;

        public string readTemp = "";
        public string strShowData = "";

        private byte[] byDIOInPort = new byte[8];   // In Port Stat
        private byte[] byDIOOutPort = new byte[8];  // Out Port Stat

        private byte[] byStx = new byte[] { 0x02 };
        private byte[] byEtx = new byte[] { 0x03 };
        private byte[] buff = new byte[1024];        // 수신버퍼 최대 사이즈

        public BatteryTesterStat _Status = new BatteryTesterStat();

        // 메인 프로세스
        public void Process()
        {
            if (!port.IsOpen) { bCommFail = true; return; }

            //while (!bWorkStop)
            {


                switch (nCurrentStep)
                {
                    case 0:
                        if (bStart)
                        {
                            bStart = false;
                            bCsStart = false;
                            bCommFail = false;
                            bStop = false;
                            bCheckOkng = false;
                            bBarcodeRead = false;
                            try
                            {
                                port.ReadExisting();
                                _Status = BatteryTesterStat.READY;
                                port.Write(byStx, 0, byStx.Length);
                                port.Write(String.Format("ST:{0},{0},{0}", strSendBcd));
                                port.Write(byEtx, 0, byEtx.Length);
                                AppendLogMsg(String.Format("{0} >> ST:{1},{1},{1}", nStation, strSendBcd), Color.Red);

                                ClearBuffer();
                            }
                            catch (Exception e)
                            {
                                bCommFail = true;
                                AppendLogMsg(e.Message, Color.DimGray);
                            }
                            nBufferIndex = 0;
                            nCurrentStep = 1;
                            watch.Restart();
                        }

                        if (bBarcodeRead)
                        {
                            bStart = false;
                            bCsStart = false;
                            bCommFail = false;
                            bStop = false;
                            bCheckOkng = false;
                            bBarcodeRead = false;
                            nBufferIndex = 0;
                            nCurrentStep = 2;
                            watch.Restart();
                            ClearBuffer();
                        }

                        if (bCheckOkng)
                        {
                            bStart = false;
                            bCsStart = false;
                            bCommFail = false;
                            bStop = false;
                            bCheckOkng = false;
                            bBarcodeRead = false;
                            nBufferIndex = 0;
                            nCurrentStep = 3;
                            watch.Restart();
                            ClearBuffer();
                        }

                        if (bStop)
                        {
                            bStart = false;
                            bCsStart = false;
                            bCommFail = false;
                            bStop = false;
                            bCheckOkng = false;
                            bBarcodeRead = false;
                            try
                            {
                                port.ReadExisting();
                                port.Write(byStx, 0, byStx.Length);
                                port.Write("END");
                                port.Write(byEtx, 0, byEtx.Length);
                                ClearBuffer();
                                AppendLogMsg(String.Format("{0} >> END", nStation), Color.Red);
                            }
                            catch
                            {
                                bCommFail = true;
                            }
                            nBufferIndex = 0;
                            nCurrentStep = 5;
                            watch.Restart();
                        }


                        if (bCsStart)
                        {
                            bStart = false;
                            bCsStart = false;
                            bCommFail = false;
                            bStop = false;
                            bCheckOkng = false;
                            bBarcodeRead = false;
                            try
                            {
                                port.ReadExisting();
                                port.Write(byStx, 0, byStx.Length);
                                port.Write("CS");
                                port.Write(byEtx, 0, byEtx.Length);
                                ClearBuffer();
                                AppendLogMsg(String.Format("{0} >> CS", nStation), Color.Red);
                            }
                            catch
                            {
                                bCommFail = true;
                            }
                            watch.Restart();
                        }
                        break;

                    // ST 응답
                    case 1:
                        if (watch.ElapsedMilliseconds > 10000)
                        {
                            bCommFail = true;
                            bPortStat = false;
                            break;
                        }
                        try
                        {
                            if (port.BytesToRead > 0)
                            {
                                if (nBufferIndex > 1000) { ClearBuffer(); }



                                port.Read(buff, nBufferIndex++, 1);

                                if (buff[Math.Max((nBufferIndex - 1), 0)] == 0x02)
                                {
                                    ClearBuffer();
                                    buff[0] = 0x02;
                                    nBufferIndex++;
                                }

                                // ================= 데이터 추적
                                _tShowTimer.Restart();

                                if (buff[Math.Max((nBufferIndex - 1), 0)] < 0x20)
                                {
                                    strShowData += "{0x";
                                    strShowData += buff[Math.Max((nBufferIndex - 1), 0)].ToString("X2");
                                    strShowData += "}";
                                }
                                else
                                {
                                    strShowData += Encoding.ASCII.GetString(buff, Math.Max((nBufferIndex - 1), 0), 1);
                                }
                                //=================================

                                if (buff[0] == 0x02 && buff[Math.Max((nBufferIndex - 1), 0)] == 0x03)
                                {
                                    readTemp = Encoding.ASCII.GetString(buff, 1, nBufferIndex - 2);


                                    if (readTemp == "ST")
                                    {
                                        bRequest = true;
                                        _Status = BatteryTesterStat.START;
                                        nCurrentStep = 0;
                                        _tShowTimer.Stop();
                                        _tShowTimer.Reset();
                                        AppendLogMsg(String.Format("{0} << {1}", nStation, strShowData), Color.Blue);
                                        strShowData = "";
                                    }
                                    else if (readTemp == "ING")
                                    {
                                        bRequest = true;
                                        _Status = BatteryTesterStat.ING;
                                        nCurrentStep = 0;
                                        _tShowTimer.Stop();
                                        _tShowTimer.Reset();
                                        AppendLogMsg(String.Format("{0} << {1}", nStation, strShowData), Color.Blue);
                                        strShowData = "";
                                    }
                                    ClearBuffer();
                                    bPortStat = true;
                                    break;
                                }
                            }

                            if (_tShowTimer.ElapsedMilliseconds > 200)
                            {
                                _tShowTimer.Stop();
                                _tShowTimer.Reset();
                                AppendLogMsg(String.Format("{0} << {1}", nStation, strShowData), Color.Blue);
                                strShowData = "";
                            }

                        }
                        catch { nCurrentStep = 0; bCommFail = true; }
                        break;

                    // 바코드 대기
                    case 2:
                        try
                        {
                            if (port.BytesToRead > 0)
                            {
                                if (nBufferIndex > 1000) { ClearBuffer(); }


                                port.Read(buff, nBufferIndex++, 1);
                                if (buff[Math.Max((nBufferIndex - 1), 0)] == 0x02)
                                {
                                    ClearBuffer();
                                    buff[0] = 0x02;
                                    nBufferIndex++;
                                }

                                // ================= 데이터 추적
                                _tShowTimer.Restart();

                                if (buff[Math.Max((nBufferIndex - 1), 0)] < 0x20)
                                {
                                    strShowData += "{0x";
                                    strShowData += buff[Math.Max((nBufferIndex - 1), 0)].ToString("X2");
                                    strShowData += "}";
                                }
                                else
                                {
                                    strShowData += Encoding.ASCII.GetString(buff, Math.Max((nBufferIndex - 1), 0), 1);
                                }
                                //=================================

                                if (buff[0] == 0x02 && buff[Math.Max((nBufferIndex - 1), 0)] == 0x03)
                                {
                                    readTemp = Encoding.ASCII.GetString(buff, 1, nBufferIndex - 2);


                                    if (readTemp == "NOREAD")
                                    {
                                        bRequest = true;
                                        _Status = BatteryTesterStat.NOREAD;
                                        nCurrentStep = 0;
                                        _tShowTimer.Stop();
                                        _tShowTimer.Reset();
                                        AppendLogMsg(String.Format("{0} << {1}", nStation, strShowData), Color.Blue);
                                        strShowData = "";
                                    }
                                    else
                                    {
                                        bRequest = true;
                                        _Status = BatteryTesterStat.READ;
                                        nCurrentStep = 0;
                                        _tShowTimer.Stop();
                                        _tShowTimer.Reset();
                                        AppendLogMsg(String.Format("{0} << {1}", nStation, strShowData), Color.Blue);
                                        strShowData = "";
                                    }
                                    ClearBuffer();
                                    bPortStat = true;
                                    break;
                                }
                            }


                            if (_tShowTimer.ElapsedMilliseconds > 200)
                            {
                                _tShowTimer.Stop();
                                _tShowTimer.Reset();
                                AppendLogMsg(String.Format("{0} << {1}", nStation, strShowData), Color.Blue);
                                strShowData = "";
                            }
                        }
                        catch { nCurrentStep = 0; bCommFail = true; }
                        break;

                    case 3:
                        try
                        {
                            if (port.BytesToRead > 0)
                            {
                                if (nBufferIndex > 1000) { ClearBuffer(); }


                                port.Read(buff, nBufferIndex++, 1);
                                if (buff[Math.Max((nBufferIndex - 1), 0)] == 0x02)
                                {
                                    ClearBuffer();
                                    buff[0] = 0x02;
                                    nBufferIndex++;
                                }

                                // ================= 데이터 추적 
                                _tShowTimer.Restart();

                                if (buff[Math.Max((nBufferIndex - 1), 0)] < 0x20)
                                {
                                    strShowData += "{0x";
                                    strShowData += buff[Math.Max((nBufferIndex - 1), 0)].ToString("X2");
                                    strShowData += "}";
                                }
                                else
                                {
                                    strShowData += Encoding.ASCII.GetString(buff, Math.Max((nBufferIndex - 1), 0), 1);
                                }
                                //=================================

                                if (buff[0] == 0x02 && buff[Math.Max((nBufferIndex - 1), 0)] == 0x03)
                                {

                                    readTemp = Encoding.ASCII.GetString(buff, 1, nBufferIndex - 2);

                                    if (readTemp == "OK")
                                    {
                                        bRequest = true;
                                        _Status = BatteryTesterStat.OK;
                                        nCurrentStep = 0;
                                        _tShowTimer.Stop();
                                        _tShowTimer.Reset();
                                        AppendLogMsg(String.Format("{0} << {1}", nStation, strShowData), Color.Blue);
                                        strShowData = "";

                                    }
                                    else if (readTemp == "NG")
                                    {
                                        bRequest = true;
                                        _Status = BatteryTesterStat.NG;
                                        nCurrentStep = 0;
                                        _tShowTimer.Stop();
                                        _tShowTimer.Reset();
                                        AppendLogMsg(String.Format("{0} << {1}", nStation, strShowData), Color.Blue);
                                        strShowData = "";
                                    }
                                    else if(readTemp == "COMMNG")
                                    {
                                        // BMS 통신 NG 일 경우 [ 통신 NG 재시도 루틴 ]

                                        bRequest = true;
                                        _Status = BatteryTesterStat.COMMNG;
                                        nCurrentStep = 0;
                                        _tShowTimer.Stop();
                                        _tShowTimer.Reset();
                                        AppendLogMsg(String.Format("{0} << {1}", nStation, strShowData), Color.Blue);
                                        strShowData = "";


                                    }
                                    ClearBuffer();
                                    bPortStat = true;
                                    break;
                                }
                            }

                            if (_tShowTimer.ElapsedMilliseconds > 200)
                            {
                                _tShowTimer.Stop();
                                _tShowTimer.Reset();
                                AppendLogMsg(String.Format("{0} << {1}", nStation, strShowData), Color.Blue);
                                strShowData = "";
                            }
                        }
                        catch { nCurrentStep = 0; bCommFail = true; }
                        break;



                    case 5:
                        try
                        {
                            if (port.BytesToRead > 0)
                            {
                                if (nBufferIndex > 1000) { ClearBuffer(); }


                                port.Read(buff, nBufferIndex++, 1);
                                if (buff[Math.Max((nBufferIndex - 1), 0)] == 0x02)
                                {
                                    ClearBuffer();
                                    buff[0] = 0x02;
                                    nBufferIndex++;
                                }

                                // ================= 데이터 추적
                                _tShowTimer.Restart();

                                if (buff[Math.Max((nBufferIndex - 1), 0)] < 0x20)
                                {
                                    strShowData += "{0x";
                                    strShowData += buff[Math.Max((nBufferIndex - 1), 0)].ToString("X2");
                                    strShowData += "}";
                                }
                                else
                                {
                                    strShowData += Encoding.ASCII.GetString(buff, Math.Max((nBufferIndex - 1), 0), 1);
                                }
                                //=================================

                                if (buff[0] == 0x02 && buff[Math.Max((nBufferIndex - 1), 0)] == 0x03)
                                {

                                    readTemp = Encoding.ASCII.GetString(buff, 1, nBufferIndex - 2);

                                    if (readTemp == "END")
                                    {
                                        bRequest = true;
                                        _Status = BatteryTesterStat.END;
                                        nCurrentStep = 0;

                                        _tShowTimer.Stop();
                                        _tShowTimer.Reset();
                                        AppendLogMsg(String.Format("{0} << {1}", nStation, strShowData), Color.Blue);
                                        strShowData = "";
                                    }
                                    ClearBuffer();
                                    bPortStat = true;
                                    break;
                                }
                            }

                            if (_tShowTimer.ElapsedMilliseconds > 200)
                            {
                                _tShowTimer.Stop();
                                _tShowTimer.Reset();
                                AppendLogMsg(String.Format("{0} << {1}", nStation, strShowData), Color.Blue);
                                strShowData = "";
                            }
                        }
                        catch { nCurrentStep = 0; bCommFail = true; }
                        break;
                }

                //Thread.Sleep(1);

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

        //====== 로그 메세지 출력
        public static void AppendLogMsg(String str, Color clr)
        {
            Program._mainform.BeginInvoke(new Action(() => Program._mainform.ViewCommMsg(str, clr)));
        }
    }
}
