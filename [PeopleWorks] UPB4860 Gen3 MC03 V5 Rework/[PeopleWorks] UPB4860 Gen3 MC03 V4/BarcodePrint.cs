using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Diagnostics;
using System.Threading;
using System.Windows.Forms;

namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
    public class BarcodePrint
    {
        // 공통 외부 참조
        public bool bPortStat = false;
        public bool bPrintStart = false;
        public string strModelInfo;
        public string strPrintBCD;


        public bool bManualMode;
        public string strManualModelInfo;
        public string strManualPrintBCD;

        // 출력관련 플래그
        public bool bPrintPaperEmpty = false;
        public bool bPrintPasue = false;
        public bool bPrintHeadUp = false;
        public bool bPrintRibonErr = false;
        public bool bPrintFail = false;
        public bool bPrintOk = false;


        // 시리얼 포트
        public SerialPort _Port = new SerialPort();
        private Stopwatch _tTimer = new Stopwatch();
        public Mirae_Timer _tSendDelayTimer = new Mirae_Timer();

        // 쓰레드 플래그
        private bool bWorkStop = false;

        // 에러 카운트
        private int nErrCount = 0;


        // 수신 데이터
        private int Len = 0;
        public string readTemp = "";
        public byte[] rcvBuff = new byte[1024];



        // STX / ETX
        private byte[] byStx = new byte[] { 0x07, 0x09, 0x07, 0x09, 0x02 };
        private byte[] byEtx = new byte[] { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x03 };


        public int nCurrentStep;

        public void Process()
        {
            if (!_Port.IsOpen) { return; }
            //while (!bWorkStop)
            {
                switch (nCurrentStep)
                {
                    case 0:
                        if (bPrintStart)
                        {
                            bPrintStart = false;
                            bPrintPaperEmpty = false;
                            bPrintPasue = false;
                            bPrintHeadUp = false;
                            bPrintRibonErr = false;
                            bPrintFail = false;
                            bPrintOk = false;

                            ClearReadBuffer();
                            nCurrentStep = 10;
                        }
                        break;

                    case 10:
                        try
                        {
                            _Port.ReadExisting();
                            _Port.Write("~HS");
                            ClearReadBuffer();
                            nCurrentStep++;
                            _tTimer.Restart();
                        }
                        catch
                        {
                            bPrintFail = true;
                            nCurrentStep = 0;
                        }
                        break;

                    case 11:
                        if (_tTimer.ElapsedMilliseconds > 500)
                        {
                            nErrCount++;
                            nCurrentStep = 0;
                            if (nErrCount > 10)
                            {
                                bPrintFail = true;
                                nErrCount = 0;
                                bPortStat = false;
                            }
                            break;
                        }

                        try
                        {
                            if (_Port.BytesToRead > 0)
                            {
                                if (Len > 1000) { ClearReadBuffer(); }
                                _Port.Read(rcvBuff, Len++, 1);

                                if (rcvBuff[Math.Max((Len - 1), 0)] == 0x02)
                                {
                                    ClearReadBuffer();
                                    rcvBuff[0] = 0x02;
                                    Len++;
                                }


                                if (rcvBuff[0] == 0x02 && rcvBuff[Math.Max((Len - 3), 0)] == 0x03 && rcvBuff[Math.Max((Len - 2), 0)] == 0x0D && rcvBuff[Math.Max((Len - 1), 0)] == 0x0A)
                                {
                                    readTemp = Encoding.Default.GetString(rcvBuff, 0, Len);
                                    {
                                        string[] strTemp = readTemp.Split(',');

                                        if (strTemp[1] == "1")       // 용지 상태 읽음
                                        {
                                            bPrintPaperEmpty = true;
                                        }
                                        else
                                        {
                                            bPrintPaperEmpty = false;
                                        }

                                        if (strTemp[2] == "1")
                                        {
                                            bPrintPasue = true;     // 일시정지 상태 읽음
                                        }
                                        else
                                        {
                                            bPrintPasue = false;
                                        }

                                        nCurrentStep++;
                                        _tTimer.Restart();
                                        ClearReadBuffer();

                                        break;
                                    }
                                }
                            }

                        }
                        catch
                        {
                            bPrintFail = true;
                            nCurrentStep = 0;
                        }
                        break;

                    case 12:
                        if (_tTimer.ElapsedMilliseconds > 500)
                        {
                            nErrCount++;
                            nCurrentStep = 0;
                            if (nErrCount > 10)
                            {
                                bPrintFail = true;
                                nErrCount = 0;
                                bPortStat = false;
                            }
                            break;
                        }

                        try
                        {

                            if (_Port.BytesToRead > 0)
                            {
                                if (Len > 1000) { ClearReadBuffer(); }

                                _Port.Read(rcvBuff, Len++, 1);

                                if (rcvBuff[Math.Max((Len - 1), 0)] == 0x02)
                                {
                                    ClearReadBuffer();
                                    rcvBuff[0] = 0x02;
                                    Len++;
                                }

                                if (rcvBuff[0] == 0x02 && rcvBuff[Math.Max((Len - 3), 0)] == 0x03 && rcvBuff[Math.Max((Len - 2), 0)] == 0x0D && rcvBuff[Math.Max((Len - 1), 0)] == 0x0A)
                                {
                                    readTemp = Encoding.Default.GetString(rcvBuff, 0, Len);
                                    {
                                        string[] strTemp = readTemp.Split(',');

                                        if (strTemp[2] == "1")
                                        {
                                            bPrintHeadUp = true;
                                        }
                                        else
                                        {
                                            bPrintHeadUp = false;
                                        }

                                        if (strTemp[3] == "1")
                                        {
                                            bPrintRibonErr = true;
                                        }
                                        else
                                        {
                                            bPrintRibonErr = false;
                                        }

                                        nCurrentStep++;
                                        _tTimer.Restart();
                                        ClearReadBuffer();

                                        break;
                                    }
                                }
                            }

                        }
                        catch
                        {
                            bPrintFail = true;
                            nCurrentStep = 0;
                        }
                        break;


                    case 13:
                        if (_tTimer.ElapsedMilliseconds > 500)
                        {
                            nErrCount++;
                            nCurrentStep = 0;
                            if (nErrCount > 10)
                            {
                                bPrintFail = true;
                                nErrCount = 0;
                                bPortStat = false;
                            }
                            break;
                        }

                        try
                        {
                            if (_Port.BytesToRead > 0)
                            {
                                if (Len > 1000) { ClearReadBuffer(); }
                                _Port.Read(rcvBuff, Len++, 1);

                                if (rcvBuff[Math.Max((Len - 1), 0)] == 0x02)
                                {
                                    ClearReadBuffer();
                                    rcvBuff[0] = 0x02;
                                    Len++;
                                }


                                if (rcvBuff[0] == 0x02 && rcvBuff[Math.Max((Len - 3), 0)] == 0x03 && rcvBuff[Math.Max((Len - 2), 0)] == 0x0D && rcvBuff[Math.Max((Len - 1), 0)] == 0x0A)
                                {
                                    readTemp = Encoding.Default.GetString(rcvBuff, 0, Len);
                                    {
                                        string[] strTemp = readTemp.Split(',');


                                        nCurrentStep = 15;
                                        _tTimer.Restart();
                                        ClearReadBuffer();

                                        break;
                                    }
                                }
                            }

                        }
                        catch
                        {
                            bPrintFail = true;
                            nCurrentStep = 0;
                        }
                        break;


                    case 15:
                        if (bPrintPaperEmpty || bPrintPasue || bPrintHeadUp || bPrintRibonErr)
                        {
                            bPrintFail = true;
                            nCurrentStep = 0;
                        }
                        else
                        {
                            if (bManualMode)
                            {
                                bManualMode = false;
                                nCurrentStep = 19;
                            }
                            else
                            {
                                nCurrentStep = 20;
                            }

                        }
                        break;


                    case 19:
                        try
                        {
                            {
                                string strLabelData = "";

                                strLabelData += "^XA";
                                strLabelData += "^FWN";
                                strLabelData += "^LH0,0";

                                int XOffset = _Config.nBCDAllOffsetX + _Config.nBCDbcdOffsetX + Program._ModelInfo.nBCDOffsetX;
                                int YOffset = _Config.nBCDAllOffsetY + _Config.nBCDbcdOffsetY + Program._ModelInfo.nBCDOffsetY;

                                strLabelData += String.Format("^FS^FO{0},{1}", (XOffset < 0) ? 0 : XOffset, (YOffset < 0) ? 0 : YOffset);
                                strLabelData += String.Format("^BXN,{0},200", Program._ModelInfo.nBCDsize);
                                strLabelData += String.Format("^FD{0}{1}", strManualModelInfo, strManualPrintBCD);

                                XOffset = _Config.nBCDAllOffsetX + _Config.nBCDtextOffsetX + Program._ModelInfo.nTextOffsetX;
                                YOffset = _Config.nBCDAllOffsetY + _Config.nBCDtextOffsetY + Program._ModelInfo.nTextOffsetY;

                                if (Program._ModelInfo.bUseSharpPrint)
                                {
                                    strLabelData += String.Format("^FS^FO{0},{1}", (XOffset < 0) ? 0 : XOffset, (YOffset < 0) ? 0 : YOffset + 30);
                                    strLabelData += String.Format("^A0,{0},{1}", Program._ModelInfo.nBCDStringHeight, Program._ModelInfo.nBCDStringWidth);
                                    strLabelData += String.Format("^FD{0}{1}", strManualModelInfo, strManualPrintBCD);
                                }
                                else
                                {
                                    strLabelData += String.Format("^FS^FO{0},{1}", (XOffset < 0) ? 0 : XOffset, (YOffset < 0) ? 0 : YOffset);
                                    strLabelData += String.Format("^A0,{0},{1}", Program._ModelInfo.nBCDStringHeight, Program._ModelInfo.nBCDStringWidth);
                                    strLabelData += String.Format("^FD{0}", strManualModelInfo);

                                    strLabelData += String.Format("^FS^FO{0},{1}", (XOffset < 0) ? 0 : XOffset, (YOffset < 0) ? 0 : YOffset + 30);
                                    strLabelData += String.Format("^A0,{0},{1}", Program._ModelInfo.nBCDStringHeight, Program._ModelInfo.nBCDStringWidth);
                                    strLabelData += String.Format("^FD{0}", strManualPrintBCD);
                                }



                                strLabelData += "^FR";
                                strLabelData += "^PQ1";
                                strLabelData += "^FS";
                                strLabelData += "^XZ";

                                _Port.Write(strLabelData);
                            }

                            nCurrentStep = 21;
                        }
                        catch
                        {
                            bPrintFail = true;
                            nCurrentStep = 0;
                        }
                        break;


                    case 20:
                        try
                        {
                            {
                                string strLabelData = "";

                                strLabelData += "^XA";
                                strLabelData += "^FWN";
                                strLabelData += "^LH0,0";

                                int XOffset = _Config.nBCDAllOffsetX + _Config.nBCDbcdOffsetX + Program._ModelInfo.nBCDOffsetX;
                                int YOffset = _Config.nBCDAllOffsetY + _Config.nBCDbcdOffsetY + Program._ModelInfo.nBCDOffsetY;

                                strLabelData += String.Format("^FS^FO{0},{1}", (XOffset < 0) ? 0 : XOffset, (YOffset < 0) ? 0 : YOffset);
                                strLabelData += String.Format("^BXN,{0},200", Program._ModelInfo.nBCDsize);
                                strLabelData += String.Format("^FD{0}{1}", strModelInfo, strPrintBCD);

                                XOffset = _Config.nBCDAllOffsetX + _Config.nBCDtextOffsetX + Program._ModelInfo.nTextOffsetX;
                                YOffset = _Config.nBCDAllOffsetY + _Config.nBCDtextOffsetY + Program._ModelInfo.nTextOffsetY;

                                if (Program._ModelInfo.bUseSharpPrint)
                                {
                                    strLabelData += String.Format("^FS^FO{0},{1}", (XOffset < 0) ? 0 : XOffset, (YOffset < 0) ? 0 : YOffset + 30);
                                    strLabelData += String.Format("^A0,{0},{1}", Program._ModelInfo.nBCDStringHeight, Program._ModelInfo.nBCDStringWidth);
                                    strLabelData += String.Format("^FD{0}{1}", strModelInfo, strPrintBCD);
                                }
                                else
                                {
                                    strLabelData += String.Format("^FS^FO{0},{1}", (XOffset < 0) ? 0 : XOffset, (YOffset < 0) ? 0 : YOffset);
                                    strLabelData += String.Format("^A0,{0},{1}", Program._ModelInfo.nBCDStringHeight, Program._ModelInfo.nBCDStringWidth);
                                    strLabelData += String.Format("^FD{0}", strModelInfo);

                                    strLabelData += String.Format("^FS^FO{0},{1}", (XOffset < 0) ? 0 : XOffset, (YOffset < 0) ? 0 : YOffset + 30);
                                    strLabelData += String.Format("^A0,{0},{1}", Program._ModelInfo.nBCDStringHeight, Program._ModelInfo.nBCDStringWidth);
                                    strLabelData += String.Format("^FD{0}", strPrintBCD);
                                }


                                strLabelData += "^FR";
                                strLabelData += "^PQ1";
                                strLabelData += "^FS";
                                strLabelData += "^XZ";

                                _Port.Write(strLabelData);
                            }

                            nCurrentStep++;
                        }
                        catch
                        {
                            bPrintFail = true;
                            nCurrentStep = 0;
                        }
                        break;

                    case 21:
                        bPrintOk = true;
                        nCurrentStep = 0;
                        break;



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
            bPortStat = false;

            _Port.RtsEnable = true;
            _Port.DtrEnable = true;

            _Port.Handshake = Handshake.XOnXOff;
        }

        // Port Open
        public bool PortOpen()
        {
            if (_Port.IsOpen)
            {
                try
                {
                    _Port.Close();
                    _Port.Open();
                    return true;
                }
                catch { return false; }
            }
            else
            {
                try
                {
                    _Port.Open();
                    return true;
                }
                catch { return false; }
            }

        }

        public void Start()
        {
            bWorkStop = false;
            //   Thread Proc = new Thread(new ThreadStart(Process));
            //   Proc.Start();
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
