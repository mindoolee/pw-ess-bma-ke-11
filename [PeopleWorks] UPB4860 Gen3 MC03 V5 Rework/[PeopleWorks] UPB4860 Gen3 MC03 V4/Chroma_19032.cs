using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Diagnostics;
using System.Threading;

namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
    public class Chroma_19032
    {

        public bool bPortStat = false;

        // 외부 참조 데이터


        // 내부 내용
        public SerialPort port = new SerialPort();
        private Stopwatch watch = new Stopwatch();
        private int nBufferIndex = 0;
        private byte[] buff = new byte[1024];        // 수신버퍼 최대 사이즈
        private int nComm_dly = 50;
        public string strReadData = "";
        public string strReportData = "";
        public string[] strReportDatas = new string[1000];

        public bool bThreadResult = false;

        // 패킷 수신
        private bool ReceivePacket()
        {
            bool bReceived = false;


            // 버퍼 초기화
            Array.Clear(buff, 0, buff.Length);
            nBufferIndex = 0;
            watch.Restart();

            while (!bReceived && !(watch.ElapsedMilliseconds > 200))
            {

                while (port.BytesToRead > 0)
                {
                    port.Read(buff, nBufferIndex++, 1);

                    // 패킷이 완성되면 해석
                    if (buff[Math.Max((nBufferIndex - 2), 0)] == 0x0D && buff[Math.Max((nBufferIndex - 1), 0)] == 0x0A)
                    {
                        bReceived = true;
                        strReadData = Encoding.Default.GetString(buff, 0, nBufferIndex - 2);

                        //FProgram.AppendLogMsg(strReadPacket, LOG_TYPE.ERROR);
                        // 버퍼 초기화
                        Array.Clear(buff, 0, buff.Length);
                        nBufferIndex = 0;

                    }

                    // 오버플로우 방지
                    if (nBufferIndex > 1000) { nBufferIndex = 0; }

                }

            }


            return bReceived;
        }


        public void BufferClear()
        {
            // 버퍼 초기화
            Array.Clear(buff, 0, buff.Length);
            nBufferIndex = 0;
        }


        private bool ReceivePacket2()
        {
            bool bReceived = false;

            if (port.BytesToRead > 0)
            {
                port.Read(buff, nBufferIndex++, 1);

                // 패킷이 완성되면 해석
                if (buff[Math.Max((nBufferIndex - 2), 0)] == 0x0D && buff[Math.Max((nBufferIndex - 1), 0)] == 0x0A)
                {
                    bReceived = true;
                    strReadData = Encoding.Default.GetString(buff, 0, nBufferIndex - 2);

                    //FProgram.AppendLogMsg(strReadPacket, LOG_TYPE.ERROR);
                    // 버퍼 초기화
                    Array.Clear(buff, 0, buff.Length);
                    nBufferIndex = 0;

                }

                // 오버플로우 방지
                if (nBufferIndex > 1000) { nBufferIndex = 0; }

            }

            return bReceived;
        }

        private void WritePacket(String str)
        {
            try
            {
                port.ReadExisting();
                byte[] byEtx = { 0x0D, 0x0A };
                port.Write(str);
                port.Write(byEtx, 0, 2);
            }
            catch { }
        }


        private static DateTime Delay(int MS)
        {
            DateTime ThisMoment = DateTime.Now;
            TimeSpan duration = new TimeSpan(0, 0, 0, 0, MS);
            DateTime AfterWards = ThisMoment.Add(duration);

            while (AfterWards >= ThisMoment)
            {
                System.Windows.Forms.Application.DoEvents();
                ThisMoment = DateTime.Now;
            }

            return DateTime.Now;
        }



        public void SetOscTestThread(double dbCS, double dbLow, double dbHigh, int nBox, int nCh, int nStep)
        {
            bThreadResult = false;
            Thread th = new Thread(() => SetOscTest(dbCS, dbLow, dbHigh, nBox, nCh, nStep));
            th.Start();
        }


        public bool SetOscTest(double dbCS, double dbLow, double dbHigh, int nBox, int nCh, int nStep)
        {
            bool bResult = false;
            int nReTryCount = 0;

            try
            {
                // 상한 하한 설정
                do
                {
                    WritePacket(String.Format("SAFETY:STEP{0}:OSC:LIM:OPEN {1}", nStep, dbLow));
                    Delay(nComm_dly);
                    WritePacket(String.Format("SAFETY:STEP{0}:OSC:LIM:OPEN?", nStep));
                    Delay(nComm_dly);
                    if (ReceivePacket())
                    {
                        if (double.Parse(strReadData) == dbLow)
                        {
                            bResult = true;
                            break;
                        }
                    }


                } while (++nReTryCount < 3);



                if (bResult)
                {
                    do
                    {
                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:OSC:CHAN (@1(0))", nStep));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:OSC:CHAN (@2(0))", nStep));
                        Delay(nComm_dly);

                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:OSC:CHAN?", nStep));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (strReadData == String.Format("(0)", nBox, nCh))
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);

                    // AC 채널 설정
                    do
                    {
                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:OSC:CHAN (@{1}({2}))", nStep, nBox, nCh));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:OSC:CHAN?", nStep));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (strReadData == String.Format("(@{0}({1}))", nBox, nCh))
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);


                    do
                    {
                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:OSC:CHAN:LOW (@1(3))", nStep));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:OSC:CHAN?", nStep));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (strReadData == String.Format("(@1(3))", nCh))
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);

                    // 상한 상한 설정
                    //do
                    //{
                    //    WritePacket(String.Format("SAFETY:STEP1:OSC:LIM:SHORT {0}", dbHigh));
                    //    Delay(nComm_dly);
                    //    WritePacket(String.Format("SAFETY:STEP1:OSC:LIM:SHORT?"));
                    //    Delay(nComm_dly);
                    //    if (ReceivePacket())
                    //    {

                    //        if (double.Parse(strReadData) == dbHigh)
                    //        {
                    //            bResult = true;
                    //            break;
                    //        }
                    //    }


                    //} while (++nReTryCount < 3);


                    // 상한치 사용하지 않음 [ 노이즈 현상 의심, 순간적으로 SHORT 나는 것때문에 정상적으로 뜨지 않음 ]
                    do
                    {
                        WritePacket(String.Format("SAFETY:STEP{0}:OSC:LIM:SHORT {1}", nStep, 0));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SAFETY:STEP{0}:OSC:LIM:SHORT?", nStep));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {

                            if (double.Parse(strReadData) == 0)
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);



                    // OSC 채널 설정
                    //do
                    //{

                    //    WritePacket(String.Format("SAFETY:STEP1:OSC:CHAN (@1(3))"));
                    //    Delay(nComm_dly);
                    //    WritePacket(String.Format("SAFETY:STEP1:OSC:CHAN?"));
                    //    Delay(nComm_dly);
                    //    if (ReceivePacket())
                    //    {
                    //        if (strReadData == "(@1(3))")
                    //        {

                    //            bResult = true;
                    //            break;
                    //        }
                    //    }


                    //} while (++nReTryCount < 3);

                    // OSC CS설정
                    do
                    {
                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:OSC:CST 1,{1}", nStep, dbCS * 0.000000001));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:OSC:CST?", nStep));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (double.Parse(strReadData) == dbCS * 0.000000001)
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);

                }
            }
            catch { bResult = false; bThreadResult = false; return bResult; }

            bThreadResult = bResult;
            return bResult;
        }


        public void SetGbTestThread(double dbA, double dbHigh, double dbTime, int nBox, int nCh, int nStep, bool bUseTwinPort)
        {
            bThreadResult = false;
            Thread th = new Thread(() => SetGBTest(dbA, dbHigh, dbTime, nBox, nCh, nStep, bUseTwinPort));
            th.Start();
        }


        public bool SetGBTest(double dbA, double dbHigh, double dbTime, int nBox, int nCh, int nStep, bool bUseTwinPort)
        {
            bool bResult = false;
            int nReTryCount = 0;

            try
            {

                // GB A설정
                do
                {
                    WritePacket(String.Format("SAFETY:STEP{0}:GB {1}", nStep, dbA));
                    Delay(nComm_dly);
                    WritePacket(String.Format("SAFETY:STEP{0}:GB?", nStep));
                    Delay(nComm_dly);
                    if (ReceivePacket())
                    {
                        if (double.Parse(strReadData) == dbA)
                        {
                            bResult = true;
                            break;
                        }
                    }


                } while (++nReTryCount < 3);




                if (bResult)
                {

                    // GB HIGH LIMIT
                    do
                    {
                        WritePacket(String.Format("SAFETY:STEP{0}:GB:LIM {1}", nStep, dbHigh));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SAFETY:STEP{0}:GB:LIM?", nStep));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (double.Parse(strReadData) == dbHigh)
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);

                    do
                    {
                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:GB:CHAN (@1(0))", nStep));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:GB:CHAN (@2(0))", nStep));
                        Delay(nComm_dly);

                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:GB:CHAN?", nStep));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (strReadData == "(0)")
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);

                    // GB 시간설정
                    do
                    {
                        WritePacket(String.Format("SAFETY:STEP{0}:GB:TIME {1}", nStep, dbTime));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SAFETY:STEP{0}:GB:TIME?", nStep));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (double.Parse(strReadData) == dbTime)
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);


                    if (bUseTwinPort)
                    {
                        do
                        {
                            WritePacket(String.Format("SAFETY:STEP{0}:GB:TPOR {1}", nStep, "ON"));
                            Delay(nComm_dly);
                            WritePacket(String.Format("SAFETY:STEP{0}:GB:TPOR?", nStep));
                            Delay(nComm_dly);
                            if (ReceivePacket())
                            {
                                if (strReadData == "1")
                                {
                                    bResult = true;
                                    break;
                                }
                            }


                        } while (++nReTryCount < 3);
                    }



                }
            }
            catch { bResult = false; bThreadResult = false; return bResult; }


            bThreadResult = bResult;
            return bResult;
        }


        public void SetIRTestThread(double dbVolt, double dbLow, double dbTime, int nBox, int nCh, int nStep)
        {
            bThreadResult = false;
            Thread th = new Thread(() => SetIRTest(dbVolt, dbLow, dbTime, nBox, nCh, nStep));
            th.Start();
        }

        public bool SetIRTest(double dbVolt, double dbLow, double dbTime, int nBox, int nCh, int nStep)
        {
            bool bResult = false;
            int nReTryCount = 0;

            try
            {
                // IR 전압설정
                do
                {
                    WritePacket(String.Format("SAFETY:STEP{0}:IR {1}", nStep, dbVolt));
                    Delay(nComm_dly);
                    WritePacket(String.Format("SAFETY:STEP{0}:IR?", nStep));
                    Delay(nComm_dly);
                    if (ReceivePacket())
                    {
                        if (double.Parse(strReadData) == dbVolt)
                        {
                            bResult = true;
                            break;
                        }
                    }


                } while (++nReTryCount < 3);



                if (bResult)
                {

                    // IR 채널 설정

                    do
                    {
                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:IR:CHAN (@1(0))", nStep));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:IR:CHAN (@2(0))", nStep));
                        Delay(nComm_dly);

                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:IR:CHAN?", nStep));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (strReadData == "(0)")
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);

                    do
                    {
                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:IR:CHAN (@{1}({2}))", nStep, nBox, nCh));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:IR:CHAN?", nStep));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (strReadData == String.Format("(@{0}({1}))", nBox, nCh))
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);


                    do
                    {
                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:IR:CHAN:LOW (@1(0))", nStep));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:IR:CHAN:LOW?", nStep));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (strReadData == String.Format("(0)", nCh))
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);

                    // IR 상한 설정
                    do
                    {
                        WritePacket(String.Format("SAFETY:STEP{0}:IR:LIM {1}", nStep, dbLow * 1000000));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SAFETY:STEP{0}:IR:LIM?", nStep));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (double.Parse(strReadData) == dbLow * 1000000)
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);


                    // IR 시간 설정
                    do
                    {
                        WritePacket(String.Format("SAFETY:STEP{0}:IR:TIME {1}", nStep, dbTime));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SAFETY:STEP{0}:IR:TIME?", nStep));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (double.Parse(strReadData) == dbTime)
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);
                }
            }
            catch { bResult = false; bThreadResult = false; return bResult; }
            bThreadResult = bResult;
            return bResult;
        }





        public void SetAcTestThread(double dbVolt, double dbLow, double dbTime, int nBox, int nCh)
        {
            bThreadResult = false;
            Thread th = new Thread(() => SetACTest(dbVolt, dbLow, dbTime, nBox, nCh));
            th.Start();
        }

        public bool SetACTest(double dbVolt, double dbLow, double dbTime, int nBox, int nCh)
        {
            bool bResult = false;
            int nReTryCount = 0;

            try
            {
                // IR 전압설정
                do
                {
                    WritePacket(String.Format("SAFETY:STEP1:AC {0}", dbVolt));
                    Delay(nComm_dly);
                    WritePacket(String.Format("SAFETY:STEP1:AC?"));
                    Delay(nComm_dly);
                    if (ReceivePacket())
                    {
                        if (double.Parse(strReadData) == dbVolt)
                        {
                            bResult = true;
                            break;
                        }
                    }


                } while (++nReTryCount < 3);



                if (bResult)
                {

                    do
                    {
                        WritePacket(String.Format("SOUR:SAFETY:STEP1:AC:CHAN (@1(0))"));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SOUR:SAFETY:STEP1:AC:CHAN (@2(0))"));
                        Delay(nComm_dly);

                        WritePacket(String.Format("SOUR:SAFETY:STEP1:AC:CHAN?"));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (strReadData == String.Format("(0)", nBox, nCh))
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);

                    // AC 채널 설정
                    do
                    {
                        WritePacket(String.Format("SOUR:SAFETY:STEP1:AC:CHAN (@{0}({1}))", nBox, nCh));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SOUR:SAFETY:STEP1:AC:CHAN?"));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (strReadData == String.Format("(@{0}({1}))", nBox, nCh))
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);


                    do
                    {
                        WritePacket(String.Format("SOUR:SAFETY:STEP1:AC:CHAN:LOW (@1(0))"));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SOUR:SAFETY:STEP1:AC:CHAN?"));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (strReadData == String.Format("(0)", nCh))
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);

                    // AC 상한 설정
                    do
                    {
                        WritePacket(String.Format("SAFETY:STEP1:AC:LIM {0}", dbLow * 0.001));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SAFETY:STEP1:AC:LIM?"));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (double.Parse(strReadData) == dbLow * 0.001)
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);


                    // AC 시간 설정
                    do
                    {
                        WritePacket(String.Format("SAFETY:STEP1:AC:TIME {0}", dbTime));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SAFETY:STEP1:AC:TIME?"));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (double.Parse(strReadData) == dbTime)
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);
                }
            }
            catch { bResult = false; bThreadResult = false; return bResult; }

            bThreadResult = bResult;
            return bResult;
        }



        public void SetDcTestThread(double dbVolt, double dbLow, double dbTime, int nBox, int nCh, double dbRampTime, int nStep)
        {
            bThreadResult = false;
            Thread th = new Thread(() => SetDCTest(dbVolt, dbLow, dbTime, nBox, nCh, dbRampTime, nStep));
            th.Start();
        }

        public bool SetDCTest(double dbVolt, double dbLow, double dbTime, int nBox, int nCh, double dbRampTime, int nStep)
        {
            bool bResult = false;
            int nReTryCount = 0;

            try
            {
                // IR 전압설정
                do
                {
                    WritePacket(String.Format("SAFETY:STEP{0}:DC {1}", nStep, dbVolt));
                    Delay(nComm_dly);
                    WritePacket(String.Format("SAFETY:STEP{0}:DC?", nStep));
                    Delay(nComm_dly);
                    if (ReceivePacket())
                    {
                        if (double.Parse(strReadData) == dbVolt)
                        {
                            bResult = true;
                            break;
                        }
                    }


                } while (++nReTryCount < 3);



                if (bResult)
                {

                    do
                    {
                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:DC:CHAN (@1(0))", nStep));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:DC:CHAN (@2(0))", nStep));
                        Delay(nComm_dly);

                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:DC:CHAN?", nStep));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (strReadData == String.Format("(0)", nBox, nCh))
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);

                    // AC 채널 설정
                    do
                    {
                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:DC:CHAN (@{1}({2}))", nStep, nBox, nCh));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:DC:CHAN?", nStep));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (strReadData == String.Format("(@{0}({1}))", nBox, nCh))
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);


                    do
                    {
                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:DC:CHAN:LOW (@1(0))", nStep));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SOUR:SAFETY:STEP{0}:DC:CHAN?", nStep));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (strReadData == String.Format("(0)", nCh))
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);

                    // AC 상한 설정
                    do
                    {
                        WritePacket(String.Format("SAFETY:STEP{0}:DC:LIM {1}", nStep, dbLow * 0.001));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SAFETY:STEP{0}:DC:LIM?", nStep));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (double.Parse(strReadData) == dbLow * 0.001)
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);


                    // AC 시간 설정
                    do
                    {
                        WritePacket(String.Format("SAFETY:STEP{0}:DC:TIME {1}", nStep, dbTime));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SAFETY:STEP{0}:DC:TIME?", nStep));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (double.Parse(strReadData) == dbTime)
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);

                    // DC 램프타임 설정
                    do
                    {
                        WritePacket(String.Format("SAFETY:STEP{0}:DC:TIME:RAMP {1}", nStep, dbRampTime));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SAFETY:STEP{0}:DC:TIME:RAMP?", nStep));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (double.Parse(strReadData) == dbRampTime)
                            {
                                bResult = true;
                                break;
                            }
                        }


                    } while (++nReTryCount < 3);
                }
            }
            catch { bResult = false; bThreadResult = false; return bResult; }

            bThreadResult = bResult;
            return bResult;
        }


        public void SetTestVoltageThread(int nStep, MODE mode, double dbVoltage, double dbTime)
        {
            bThreadResult = false;
            Thread th = new Thread(() => SetTestVoltage(nStep, mode, dbVoltage, dbTime));
            th.Start();
        }


        public bool SetTestVoltage(int nStep, MODE mode, double dbVoltage, double dbTime)
        {
            bool bResult = false;
            int nReTryCount = 0;

            try
            {
                do
                {
                    WritePacket(String.Format("SAFETY:STEP{0}:{1} {2}", nStep, mode, dbVoltage));
                    Delay(nComm_dly);
                    WritePacket(String.Format("SAFETY:STEP{0}:{1}?", nStep, mode));
                    Delay(nComm_dly);
                    if (ReceivePacket())
                    {
                        if (double.Parse(strReadData) == dbVoltage)
                        {
                            bResult = true;
                            break;
                        }
                    }


                } while (++nReTryCount < 3);

                if (bResult)
                {
                    do
                    {
                        bResult = false;
                        WritePacket(String.Format("SAFETY:STEP{0}:{1}:TIME {2}", nStep, mode, dbTime));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SAFETY:STEP{0}:{1}:TIME?", nStep, mode));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (double.Parse(strReadData) == dbTime)
                            {
                                bResult = true;
                                break;
                            }

                        }


                    } while (++nReTryCount < 3);
                }
            }
            catch { bResult = false; bThreadResult = false; return bResult; }
            bThreadResult = bResult;
            return bResult;
        }



        public void SetTestAutoReportThread()
        {
            bThreadResult = false;
            Thread th = new Thread(() => SetTestAutoReport());
            th.Start();
        }

        public bool SetTestAutoReport()
        {
            bool bResult = false;
            int nReTryCount = 0;

            // 모든 자동 리포트 활성화
            try
            {
                do
                {
                    bResult = false;
                    WritePacket(String.Format("SAFETY:RESULT:AREPORT ON"));
                    Delay(nComm_dly);
                    WritePacket(String.Format("SAFETY:RESULT:AREPORT?"));
                    Delay(nComm_dly);
                    if (ReceivePacket())
                    {
                        if (strReadData == "1")
                        {
                            bResult = true;
                            break;
                        }
                    }
                } while (++nReTryCount < 3);

                if (bResult)
                {
                    nReTryCount = 0;

                    do
                    {
                        bResult = false;
                        WritePacket(String.Format("SAFETY:RESULT:AREPORT:ITEM STAT,MODE,MMET"));
                        Delay(nComm_dly);
                        WritePacket(String.Format("SAFETY:RESULT:AREPORT:ITEM?"));
                        Delay(nComm_dly);
                        if (ReceivePacket())
                        {
                            if (strReadData == "MODE,MMET,STAT")
                            {
                                bResult = true;
                                break;
                            }
                        }
                    } while (++nReTryCount < 3);
                }
            }
            catch { bResult = false; bThreadResult = false; return bResult; }
            bThreadResult = bResult;
            return bResult;
        }

        public bool GetTestAutoReport()
        {
            bool bResult = false;


            if (ReceivePacket2())
            {
                try
                {
                    string[] strReadDatas = strReadData.Split(',');

                    strReportData = strReadDatas[1];
                    bResult = true;
                }
                catch { bResult = false; }
            }


            return bResult;
        }

        public bool GetTestAutoReports()
        {
            bool bResult = false;


            if (ReceivePacket2())
            {
                try
                {
                    string[] strDatas = strReadData.Split(',');

                    strReportDatas = strDatas;
                    bResult = true;
                }
                catch { bResult = false; }
            }


            return bResult;
        }


        public bool GetTestFetchReport()
        {
            bool bResult = false;


            if (ReceivePacket2())
            {
                try
                {
                    string[] strReadDatas = strReadData.Split(';');

                    strReportData = strReadDatas[1];
                    bResult = true;
                }
                catch { bResult = false; }
            }


            return bResult;
        }


        public bool DeviceInit()
        {
            bool bResult = false;
            int nRetryCount = 0;

            if (!port.IsOpen) return false;

            do
            {
                WritePacket("*IDN?");

                if (ReceivePacket())
                {
                    string[] strReadDatas = strReadData.Split(',');

                    if (strReadDatas[0] == "Chroma" && strReadDatas[1] == "19032")
                    {
                        TestStop();
                        bResult = ReSetTestStep();
                        bResult = SetTestAutoReport();
                        WritePacket("*RST");
                        break;
                    }
                }
            } while (++nRetryCount < 3);


            return bResult;
        }

        public void ClearDevice()
        {
            WritePacket("*CLS");
        }

        public void DeviceStop()
        {
            WritePacket("SAFETY:STOP");
        }
        public bool ReSetTestStep()
        {
            bool bResult = false;
            int nRetryCount = 0;
            int nTestStep = 0;

            do
            {
                WritePacket("SAFETY:SNUMBER?");

                if (ReceivePacket())
                {
                    nTestStep = int.Parse(strReadData);

                    if (nTestStep > 1)
                    {
                        for (int nStep = nTestStep; nStep > 1; nStep--)
                        {
                            WritePacket(String.Format("SAFETY:STEP{0}:DELETE", nStep));
                        }
                    }

                    bResult = true;
                }

            } while (nRetryCount++ < 3);

            return bResult;
        }


        public void TestStart()
        {
            port.ReadExisting();
            WritePacket("SAFETY:START");
        }


        public void FetchCall()
        {
            port.ReadExisting();
            WritePacket("SAFETY:FETCH? MODE,MMET");
        }


        public void TestStop()
        {
            WritePacket("SAFETY:STOP");
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


        public enum MODE
        {
            DC,
            AC,
            IR,
        }


    }
}
