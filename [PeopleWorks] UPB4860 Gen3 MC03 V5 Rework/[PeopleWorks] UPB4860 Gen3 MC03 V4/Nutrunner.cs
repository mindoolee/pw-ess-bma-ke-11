using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.IO.Ports;
using System.Diagnostics;
using System.Threading;
using System.Windows.Forms;


namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
    class Nutrunner
    {
        // 공통 외부 참조
        public bool bPortStat = false;
        public int nStation = 0;


        public bool bPSet;
        public int nPSet;

        public bool bDataRead = false;
        public string strPramID;
        public string strTorque;
        public string strAngle;
        public string strTime;
        public string strResult;
        public string strSaveResult;
		public string strRundownAngle;

        public string strTorqueResult;
        public string strAngleResult;
        public string strRundownResult;

        public double dbTorqueData;
        public int nAngleData;

        public int nTiteX;
        public int nTiteY;
        public int nTiteNum;    // 체결 숫자


        // 시리얼 포트
        public SerialPort _Port = new SerialPort();
        private Stopwatch _tTimer = new Stopwatch();
        private Mirae_Timer _tSendDelayTimer = new Mirae_Timer();

        // 쓰레드 플래그
        private bool bWorkStop = false;

        // 에러 카운트
        private int nErrCount = 0;


        // 수신 데이터
        private int Len = 0;
        public string readTemp = "";
        public byte[] rcvBuff = new byte[4096];




        // STX / ETX
        private byte[] byStx = new byte[] { 0x07, 0x09, 0x07, 0x09, 0x02 };
        private byte[] byEtx = new byte[] { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x03 };
        private byte[] byNULEtx = new byte[] { 0x00, 0x03 };

        public int nCurrentStep;

        Stopwatch AliveTimer = new Stopwatch();
        bool bAlive = false;


        //public void Process()
        //{
        //    if (!_Port.IsOpen) { return; }
        //    // while (!bWorkStop)
        //    {
        //        switch (nCurrentStep)
        //        {
        //            case 0:
        //                try
        //                {
        //                    _Port.DiscardInBuffer();
        //                    _Port.DiscardOutBuffer();
        //                    ClearReadBuffer();
        //                    nCurrentStep = 10;
        //                }
        //                catch { }
        //                break;

        //            case 10:
        //                try
        //                {
        //                    _Port.ReadExisting();
        //                    _Port.Write(Encoding.Default.GetString(byStx) + "0020" + "0001" + "0010" + Encoding.Default.GetString(byEtx));
        //                    ClearReadBuffer();
        //                    nCurrentStep++;
        //                    _tTimer.Restart();
        //                }
        //                catch
        //                {
        //                    nCurrentStep = 0;
        //                }
        //                break;

        //            case 11:
        //                if (_tTimer.ElapsedMilliseconds > 500)
        //                {
        //                    nErrCount++;
        //                    nCurrentStep = 0;
        //                    if (nErrCount > 10)
        //                    {
        //                        nErrCount = 0;
        //                        bPortStat = false;
        //                    }
        //                    break;
        //                }

        //                try
        //                {
        //                    if (_Port.BytesToRead > 0)
        //                    {
        //                        if (Len > 4000) { ClearReadBuffer(); }

        //                        _Port.Read(rcvBuff, Len++, 1);

        //                        if (rcvBuff[Math.Max((Len - 1), 0)] == 0x02)
        //                        {
        //                            ClearReadBuffer();
        //                            rcvBuff[0] = 0x02;
        //                            Len++;
        //                        }

        //                        if (rcvBuff[0] == 0x02 && rcvBuff[Math.Max((Len - 1), 0)] == 0x03)
        //                        {
        //                            readTemp = Encoding.Default.GetString(rcvBuff, 0, Len);
        //                            if (readTemp.Substring(5, 4) == "0002" || readTemp.Substring(5, 4) == "0004")    // 응답이 0002 나 0004 일경우 다음스텝 진행함
        //                            {
        //                                nCurrentStep = 20;
        //                                nErrCount = 0;
        //                            }
        //                        }
        //                    }
        //                }
        //                catch
        //                {
        //                    nCurrentStep = 0;
        //                }
        //                break;

        //            case 20:
        //                try
        //                {
        //                    _Port.ReadExisting();
        //                    // 기존 너트러너 데이터 요청 [ Rev 1 ]
        //                    //_Port.Write(Encoding.Default.GetString(byStx) + "0020" + "0060" + "0010" + Encoding.Default.GetString(byEtx));

        //                    // 신규 너트러너 데이터 요청 [ Rev 2 ]  김상구 팀장 요청 * RunDown Angle 데이터 추출 추가 2018. 12. 16
        //                    _Port.Write(Encoding.Default.GetString(byStx) + "0020" + "0060" + "0020" + Encoding.Default.GetString(byEtx));
        //                    ClearReadBuffer();
        //                    nCurrentStep++;
        //                    _tTimer.Restart();
        //                }
        //                catch
        //                {
        //                    nCurrentStep = 0;
        //                }
        //                break;

        //            case 21:
        //                if (_tTimer.ElapsedMilliseconds > 500)
        //                {
        //                    nErrCount++;
        //                    nCurrentStep = 20;
        //                    if (nErrCount > 10)
        //                    {
        //                        nCurrentStep = 0;
        //                        nErrCount = 0;
        //                        bPortStat = false;
        //                    }
        //                    break;
        //                }

        //                try
        //                {
        //                    if (_Port.BytesToRead > 0)
        //                    {
        //                        if (Len > 4000) { ClearReadBuffer(); }

        //                        _Port.Read(rcvBuff, Len++, 1);

        //                        if (rcvBuff[Math.Max((Len - 1), 0)] == 0x02)
        //                        {
        //                            ClearReadBuffer();
        //                            rcvBuff[0] = 0x02;
        //                            Len++;
        //                        }

        //                        if (rcvBuff[0] == 0x02 && rcvBuff[Math.Max((Len - 1), 0)] == 0x03)
        //                        {
        //                            readTemp = Encoding.Default.GetString(rcvBuff, 0, Len);
        //                            if (readTemp.Substring(5, 4) == "0005" || readTemp.Substring(5, 4) == "0004")    // 응답이 0005 나 0004 일경우 다음스텝 진행함
        //                            {
        //                                nCurrentStep = 30;
        //                                _tSendDelayTimer.Start(10);
        //                                nErrCount = 0;
        //                            }
        //                        }
        //                    }

        //                }
        //                catch
        //                {
        //                    nCurrentStep = 0;
        //                }
        //                break;


        //            case 30:
        //                try
        //                {
        //                    if (!_tSendDelayTimer.Verify()) { break; }
        //                    if (bPSet)
        //                    {
        //                        bPSet = false;
        //                        nCurrentStep = 50;
        //                        break;
        //                    }

        //                    _Port.ReadExisting();
        //                    _Port.Write(Encoding.Default.GetString(byStx) + "0020" + "9999" + "0010" + Encoding.Default.GetString(byEtx));
        //                    ClearReadBuffer();
        //                    nCurrentStep++;
        //                    _tTimer.Restart();
        //                }
        //                catch
        //                {
        //                    nCurrentStep = 0;
        //                }
        //                break;

        //            case 31:
        //                if (_tTimer.ElapsedMilliseconds > 2000)
        //                {
        //                    nErrCount++;
        //                    nCurrentStep = 30;
        //                    if (nErrCount > 10)
        //                    {
        //                        nCurrentStep = 0;
        //                        nErrCount = 0;
        //                        bPortStat = false;
        //                    }
        //                    break;
        //                }

        //                try
        //                {
        //                    if (_Port.BytesToRead > 0)
        //                    {
        //                        if (Len > 4000) { ClearReadBuffer(); }

        //                        _Port.Read(rcvBuff, Len++, 1);

        //                        if (rcvBuff[Math.Max((Len - 1), 0)] == 0x02)
        //                        {
        //                            ClearReadBuffer();
        //                            rcvBuff[0] = 0x02;
        //                            Len++;
        //                        }


        //                        if (rcvBuff[0] == 0x02 && rcvBuff[Math.Max((Len - 1), 0)] == 0x03)
        //                        {
        //                            readTemp = Encoding.Default.GetString(rcvBuff, 0, Len);
        //                            if (readTemp.Substring(5, 4) == "9999" || readTemp.Substring(5, 4) == "0061")    // 응답이 0005 나 0004 일경우 다음스텝 진행함
        //                            {
        //                                if (readTemp.Substring(5, 4) == "9999")
        //                                {

        //                                    _tSendDelayTimer.Start(50);
        //                                    nCurrentStep = 30;
        //                                    nErrCount = 0;
        //                                }
        //                                else if (readTemp.Substring(5, 4) == "0061" /*&& readTemp.Substring(107, 2) == "09" && readTemp.Substring(91, 2) == "06" && readTemp.Substring(131, 2) == "15"*/)
        //                                {
        //                                    try
        //                                    {
        //                                        //strPramID = readTemp.Substring(91, 3);
        //                                        //strTorque = readTemp.Substring(141, 6);
        //                                        //strAngle = readTemp.Substring(170, 5);
        //                                        //strResult = readTemp.Substring(108, 1);


        //                                        // 신규 너트러너 데이터 파싱 [ Rev 2 ] 김상구 팀장 요청 * RunDown Angle 데이터 추출 추가 2018. 12. 16
        //                                        strPramID = readTemp.Substring(93, 3);                          // Parameter Sst ID
        //                                        strTorque = readTemp.Substring(184, 6);                         // Torque
        //                                        strAngle = readTemp.Substring(213, 5);                          // Angle
        //                                        strResult = readTemp.Substring(121, 1);
        //                                        strTime = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");         // 현재 시간 기준으로 저장
        //                                        strRundownAngle = readTemp.Substring(234, 5);                   // Rundown Angle [ Torque 를 적용받지않는 Angle값 ]
        //                                                                                                        // ㄴ 요청사유 : 원자재 불량으로 인한 사회불량 발생

        //                                        if (strResult == "0") strSaveResult = "NG";
        //                                        else if (strResult == "1") strSaveResult = "OK";
        //                                        else strSaveResult = "N/A";
        //                                        strTime = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");         // 현재 시간 기준으로 저장




        //                                        if (readTemp.Substring(127, 1) == "0") { strTorqueResult = "LOW"; }
        //                                        else if (readTemp.Substring(127, 1) == "1") { strTorqueResult = "OK"; }
        //                                        else if (readTemp.Substring(127, 1) == "2") { strTorqueResult = "HIGH"; }
        //                                        else { strTorqueResult = "N/A"; }

        //                                        if (readTemp.Substring(130, 1) == "0") { strAngleResult = "LOW"; }
        //                                        else if (readTemp.Substring(130, 1) == "1") { strAngleResult = "OK"; }
        //                                        else if (readTemp.Substring(130, 1) == "2") { strAngleResult = "HIGH"; }
        //                                        else { strAngleResult = "N/A"; }

        //                                        if (readTemp.Substring(133, 1) == "0") { strRundownResult = "LOW"; }
        //                                        else if (readTemp.Substring(133, 1) == "1") { strRundownResult = "OK"; }
        //                                        else if (readTemp.Substring(133, 1) == "2") { strRundownResult = "HIGH"; }
        //                                        else { strRundownResult = "N/A"; }


        //                                        double.TryParse(strTorque, out dbTorqueData);           // 토크값 변환
        //                                        int.TryParse(strAngle, out nAngleData);                 // 앵글값 변환

        //                                        {
        //                                            string strMessge = "";

        //                                            if (nStation == 2)
        //                                            {
        //                                                strMessge = String.Format("ST : {0}, ", nStation) +
        //                                                                            "Time : " + strTime +
        //                                                                            ", Param ID :" + strPramID +
        //                                                                            ", Torque :" + strTorque +
        //                                                                            ", Torque Result :" + strTorqueResult +
        //                                                                            ", Angle : " + strAngle +
        //                                                                            ", Angle Result :" + strAngleResult +
        //                                                                            ", Rundown Angle : " + strRundownAngle +
        //                                                                            ", Rundown Result : " + strRundownResult +
        //                                                                            ", Total Result : " + strSaveResult +
        //                                                                            ", X : " + nTiteX +
        //                                                                            ", Y : " + nTiteY +
        //                                                                            ", Num : " + nTiteNum +
        //                                                                            "\r\n";
        //                                            }
        //                                            else
        //                                            {
        //                                                strMessge = String.Format("ST : {0}, ", nStation) +
        //                                                                            "Time : " + strTime +
        //                                                                            ", Param ID :" + strPramID +
        //                                                                            ", Torque :" + strTorque +
        //                                                                            ", Torque Result :" + strTorqueResult +
        //                                                                            ", Angle : " + strAngle +
        //                                                                            ", Angle Result :" + strAngleResult +
        //                                                                            ", Rundown Angle : " + strRundownAngle +
        //                                                                            ", Rundown Result : " + strRundownResult +
        //                                                                            ", Total Result : " + strSaveResult +
        //                                                                            ", Num : " + nTiteNum +
        //                                                                            "\r\n";
        //                                            }

        //                                            string strFolderPath = String.Format(@"DATA\\NUTRUNNER{0}\\", nStation);

        //                                            DirectoryInfo dir = new DirectoryInfo(strFolderPath);
        //                                            if (dir.Exists == false) { dir.Create(); }

        //                                            string savePath = String.Format("{0}{1}.txt", strFolderPath, DateTime.Now.ToString("yyMMdd"));
        //                                            System.IO.File.AppendAllText(savePath, strMessge, Encoding.Default);



        //                                            strFolderPath = String.Format(@"TEMP_DATA\\ST{0}\\", nStation);

        //                                            dir = new DirectoryInfo(strFolderPath);
        //                                            if (dir.Exists == false) { dir.Create(); }

        //                                            savePath = String.Format("{0}ST{1}.txt", strFolderPath, nStation);
        //                                            System.IO.File.AppendAllText(savePath, strMessge, Encoding.Default);

        //                                        }
        //                                    }
        //                                    catch { }

        //                                    bDataRead = true;
        //                                    nCurrentStep = 40;
        //                                    nErrCount = 0;
        //                                }
        //                            }
        //                            ClearReadBuffer();
        //                        }
        //                    }

        //                }
        //                catch
        //                {
        //                    nCurrentStep = 0;
        //                }
        //                break;

        //            case 40:
        //                try
        //                {
        //                    _Port.ReadExisting();
        //                    _Port.Write(Encoding.Default.GetString(byStx) + "0020" + "0062" + "0010" + Encoding.Default.GetString(byEtx));
        //                    ClearReadBuffer();
        //                    _tSendDelayTimer.Start(50);
        //                    nCurrentStep = 30;
        //                    _tTimer.Restart();
        //                }
        //                catch
        //                {
        //                    nCurrentStep = 0;
        //                }
        //                break;



        //            case 50:
        //                _Port.ReadExisting();
        //                _Port.Write(Encoding.Default.GetString(byStx) + "00230018            " + nPSet.ToString("000") + Encoding.Default.GetString(byNULEtx));
        //                ClearReadBuffer();
        //                _tSendDelayTimer.Start(50);
        //                nCurrentStep = 30;
        //                _tTimer.Restart();
        //                break;


        //            case 51:
        //                if (_tTimer.ElapsedMilliseconds > 2000)
        //                {
        //                    nErrCount++;
        //                    nCurrentStep = 30;
        //                    if (nErrCount > 10)
        //                    {
        //                        nCurrentStep = 0;
        //                        nErrCount = 0;
        //                        bPortStat = false;
        //                    }
        //                    break;
        //                }
        //                try
        //                {
        //                    if (_Port.BytesToRead > 0)
        //                    {
        //                        if (Len > 4000) { ClearReadBuffer(); }

        //                        _Port.Read(rcvBuff, Len++, 1);

        //                        if (rcvBuff[Math.Max((Len - 1), 0)] == 0x02)
        //                        {
        //                            ClearReadBuffer();
        //                            rcvBuff[0] = 0x02;
        //                            Len++;
        //                        }


        //                        if (rcvBuff[0] == 0x02 && rcvBuff[Math.Max((Len - 1), 0)] == 0x03)
        //                        {
        //                            readTemp = Encoding.Default.GetString(rcvBuff, 0, Len);
        //                            if (readTemp.Substring(5, 4) == "0005")    // 응답이 0005 나 0004 일경우 다음스텝 진행함
        //                            {
        //                                nCurrentStep = 30;
        //                            }
        //                            else
        //                            {
        //                                nCurrentStep = 50;
        //                            }
        //                        }
        //                    }
        //                }
        //                catch { }
        //                break;
        //        }
        //        //Thread.Sleep(1);
        //    }
        //}

        public void Process()
        {
            // while (!bWorkStop)
            {
                switch (nCurrentStep)
                {
                    case 0:
                        try
                        {
                            _Port.DiscardInBuffer();
                            _Port.DiscardOutBuffer();
                            ClearReadBuffer();
                            nCurrentStep = 10;
                        }
                        catch { }
                        break;

                    case 10:
                        try
                        {
                            _Port.ReadExisting();
                            _Port.Write(Encoding.Default.GetString(byStx) + "0020" + "0001" + "0010" + Encoding.Default.GetString(byEtx));
                            ClearReadBuffer();
                            nCurrentStep++;
                            _tTimer.Restart();
                        }
                        catch
                        {
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
                                nErrCount = 0;
                                bPortStat = false;
                            }
                            break;
                        }

                        try
                        {
                            if (_Port.BytesToRead > 0)
                            {
                                if (Len > 4000) { ClearReadBuffer(); }

                                _Port.Read(rcvBuff, Len++, 1);

                                if (rcvBuff[Math.Max((Len - 1), 0)] == 0x02)
                                {
                                    ClearReadBuffer();
                                    rcvBuff[0] = 0x02;
                                    Len++;
                                }

                                if (rcvBuff[0] == 0x02 && rcvBuff[Math.Max((Len - 1), 0)] == 0x03)
                                {
                                    readTemp = Encoding.Default.GetString(rcvBuff, 0, Len);
                                    if (readTemp.Substring(5, 4) == "0002" || readTemp.Substring(5, 4) == "0004")    // 응답이 0002 나 0004 일경우 다음스텝 진행함
                                    {
                                        nCurrentStep = 20;
                                        nErrCount = 0;
                                    }
                                }
                            }
                        }
                        catch
                        {
                            nCurrentStep = 0;
                        }
                        break;

                    case 20:
                        try
                        {
                            _Port.ReadExisting();
                            _Port.Write(Encoding.Default.GetString(byStx) + "0020" + "0060" + "0020" + Encoding.Default.GetString(byEtx));
                            ClearReadBuffer();
                            nCurrentStep++;
                            _tTimer.Restart();
                        }
                        catch
                        {
                            nCurrentStep = 0;
                        }
                        break;

                    case 21:
                        if (_tTimer.ElapsedMilliseconds > 500)
                        {
                            nErrCount++;
                            nCurrentStep = 20;
                            if (nErrCount > 10)
                            {
                                nCurrentStep = 0;
                                nErrCount = 0;
                                bPortStat = false;
                            }
                            break;
                        }

                        try
                        {
                            if (_Port.BytesToRead > 0)
                            {
                                if (Len > 4000) { ClearReadBuffer(); }

                                _Port.Read(rcvBuff, Len++, 1);

                                if (rcvBuff[Math.Max((Len - 1), 0)] == 0x02)
                                {
                                    ClearReadBuffer();
                                    rcvBuff[0] = 0x02;
                                    Len++;
                                }

                                if (rcvBuff[0] == 0x02 && rcvBuff[Math.Max((Len - 1), 0)] == 0x03)
                                {
                                    readTemp = Encoding.Default.GetString(rcvBuff, 0, Len);
                                    if (readTemp.Substring(5, 4) == "0005" || readTemp.Substring(5, 4) == "0004")    // 응답이 0005 나 0004 일경우 다음스텝 진행함
                                    {
                                        nCurrentStep = 30;
                                        _tSendDelayTimer.Start(10);
                                        nErrCount = 0;
                                    }
                                }
                            }

                        }
                        catch
                        {
                            nCurrentStep = 0;
                        }
                        break;


                    case 30:
                        try
                        {
                            //if (!_tSendDelayTimer.Verify()) { break; }
                            //if (bPSet)
                            //{
                            //    bPSet = false;
                            //    nCurrentStep = 50;
                            //    break;
                            //}

                            //_Port.ReadExisting();
                            _Port.Write(Encoding.Default.GetString(byStx) + "0020" + "9999" + "0010" + Encoding.Default.GetString(byEtx));
                            ClearReadBuffer();
                            AliveTimer.Restart();
                            bAlive = false;
                            nCurrentStep++;
                            _tTimer.Restart();
                        }
                        catch
                        {
                            nCurrentStep = 0;
                        }
                        break;

                    case 31:
                        //if (_tTimer.ElapsedMilliseconds > 2000)
                        //{
                        //    nErrCount++;
                        //    nCurrentStep = 30;
                        //    if (nErrCount > 10)
                        //    {
                        //        nCurrentStep = 0;
                        //        nErrCount = 0;
                        //        bPortStat = false;
                        //    }
                        //    break;
                        //}

                        if (AliveTimer.ElapsedMilliseconds > 3000)
                        {
                            if (bAlive)
                            {
                                nCurrentStep = 30;          // 3초마다 재전송
                            }
                            else
                            {
                                nCurrentStep = 0;
                            }
                        }

                        try
                        {
                            while (_Port.BytesToRead > 0)
                            {
                                if (Len > 4000) { ClearReadBuffer(); }

                                _Port.Read(rcvBuff, Len++, 1);

                                if (rcvBuff[Math.Max((Len - 1), 0)] == 0x02)
                                {
                                    ClearReadBuffer();
                                    rcvBuff[0] = 0x02;
                                    Len++;
                                }


                                if (rcvBuff[0] == 0x02 && rcvBuff[Math.Max((Len - 1), 0)] == 0x03)
                                {
                                    readTemp = Encoding.Default.GetString(rcvBuff, 0, Len);
                                    if (readTemp.Substring(5, 4) == "9999" || readTemp.Substring(5, 4) == "0061")    // 응답이 0005 나 0004 일경우 다음스텝 진행함
                                    {
                                        if (readTemp.Substring(5, 4) == "9999")
                                        {
                                            bAlive = true;
                                            _tSendDelayTimer.Start(50);
                                            //nCurrentStep = 30;
                                            nErrCount = 0;
                                        }
                                        else if (readTemp.Substring(5, 4) == "0061")
                                        {
                                            try
                                            {
                                                //strPramID = readTemp.Substring(91, 3);
                                                //strTorque = readTemp.Substring(141, 6);
                                                //strAngle = readTemp.Substring(170, 5);
                                                //strTime = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");   


                                                // 신규 너트러너 데이터 파싱 [ Rev 2 ] 권용현 대리 요청 * RunDown Angle 데이터 추출 추가 2020. 09. 22
                                                strPramID = readTemp.Substring(93, 3);                          // Parameter Sst ID
                                                strTorque = readTemp.Substring(184, 6);                         // Torque
                                                strAngle = readTemp.Substring(213, 5);                          // Angle
                                                strResult = readTemp.Substring(121, 1);
                                                strTime = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");         // 현재 시간 기준으로 저장
                                                strRundownAngle = readTemp.Substring(234, 5);                   // Rundown Angle [ Torque 를 적용받지않는 Angle값 ]
                                                                                                                // ㄴ 요청사유 : 원자재 불량으로 인한 사회불량 발생

                                                if (strResult == "0") strSaveResult = "NG";
                                                else if (strResult == "1") strSaveResult = "OK";
                                                else strSaveResult = "N/A";
                                                strTime = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");         // 현재 시간 기준으로 저장


                                                //double.TryParse(strTorque, out dbTorqueData);           // 토크값 변환
                                                //int.TryParse(strAngle, out nAngleData);                 // 앵글값 변환



                                                if (readTemp.Substring(127, 1) == "0") { strTorqueResult = "LOW"; }
                                                else if (readTemp.Substring(127, 1) == "1") { strTorqueResult = "OK"; }
                                                else if (readTemp.Substring(127, 1) == "2") { strTorqueResult = "HIGH"; }
                                                else { strTorqueResult = "N/A"; }

                                                if (readTemp.Substring(130, 1) == "0") { strAngleResult = "LOW"; }
                                                else if (readTemp.Substring(130, 1) == "1") { strAngleResult = "OK"; }
                                                else if (readTemp.Substring(130, 1) == "2") { strAngleResult = "HIGH"; }
                                                else { strAngleResult = "N/A"; }

                                                if (readTemp.Substring(133, 1) == "0") { strRundownResult = "LOW"; }
                                                else if (readTemp.Substring(133, 1) == "1") { strRundownResult = "OK"; }
                                                else if (readTemp.Substring(133, 1) == "2") { strRundownResult = "HIGH"; }
                                                else { strRundownResult = "N/A"; }


                                                {
                                                    string strMessge = "";

                                                    if (nStation == 2)
                                                    {
                                                        //strMessge = String.Format("ST : {0}, ", nStation) +
                                                        //                            "Time : " + strTime +
                                                        //                            ", Param ID :" + strPramID +
                                                        //                            ", Torque :" + strTorque +
                                                        //                            ", Angle : " + strAngle +
                                                        //                            ", X : " + nTiteX.ToString() +
                                                        //                            ", Y : " + nTiteY.ToString() + 
                                                        //                            "\r\n";
                                                        strMessge = String.Format("ST : {0}, ", nStation) +
                                                                           "Time : " + strTime +
                                                                           ", Param ID :" + strPramID +
                                                                           ", Torque :" + strTorque +
                                                                           ", Torque Result :" + strTorqueResult +
                                                                           ", Angle : " + strAngle +
                                                                           ", Angle Result :" + strAngleResult +
                                                                           ", Rundown Angle : " + strRundownAngle +
                                                                           ", Rundown Result : " + strRundownResult +
                                                                           ", Total Result : " + strSaveResult +
                                                                           ", X : " + nTiteX +
                                                                           ", Y : " + nTiteY +
                                                                           ", Num : " + nTiteNum +
                                                                           "\r\n";
                                                    }
                                                    else
                                                    {
                                                        //strMessge = String.Format("ST : {0}, ", nStation) + "Time : " + strTime + ", Param ID :" + strPramID + ", Torque :" + strTorque + ", Angle : " + strAngle + "\r\n";
                                                        strMessge = String.Format("ST : {0}, ", nStation) +
                                                                                    "Time : " + strTime +
                                                                                    ", Param ID :" + strPramID +
                                                                                    ", Torque :" + strTorque +
                                                                                    ", Torque Result :" + strTorqueResult +
                                                                                    ", Angle : " + strAngle +
                                                                                    ", Angle Result :" + strAngleResult +
                                                                                    ", Rundown Angle : " + strRundownAngle +
                                                                                    ", Rundown Result : " + strRundownResult +
                                                                                    ", Total Result : " + strSaveResult +
                                                                                     ", Num : " + nTiteNum +
                                                                                     "\r\n";
                                                    }


                                                    string strFolderPath = String.Format(@"DATA\\NUTRUNNER{0}\\", nStation);

                                                    DirectoryInfo dir = new DirectoryInfo(strFolderPath);
                                                    if (dir.Exists == false) { dir.Create(); }

                                                    string savePath = String.Format("{0}{1}.txt", strFolderPath, DateTime.Now.ToString("yyMMdd"));
                                                    System.IO.File.AppendAllText(savePath, strMessge, Encoding.Default);



                                                    strFolderPath = String.Format(@"TEMP_DATA\\ST{0}\\", nStation);

                                                    dir = new DirectoryInfo(strFolderPath);
                                                    if (dir.Exists == false) { dir.Create(); }

                                                    savePath = String.Format("{0}ST{1}.txt", strFolderPath, nStation);
                                                    System.IO.File.AppendAllText(savePath, strMessge, Encoding.Default);

                                                }
                                            }
                                            catch { }

                                            bDataRead = true;
                                            nCurrentStep = 40;
                                            nErrCount = 0;
                                        }
                                    }
                                    ClearReadBuffer();
                                }
                            }

                        }
                        catch
                        {
                            nCurrentStep = 0;
                        }


                        if (bPSet)
                        {
                            bPSet = false;
                            nCurrentStep = 50;
                            break;
                        }
                        break;

                    case 40:
                        try
                        {
                            _Port.ReadExisting();
                            _Port.Write(Encoding.Default.GetString(byStx) + "0020" + "0062" + "0010" + Encoding.Default.GetString(byEtx));
                            ClearReadBuffer();
                            _tSendDelayTimer.Start(50);
                            nCurrentStep = 31;
                            _tTimer.Restart();
                            AliveTimer.Restart();
                        }
                        catch
                        {
                            nCurrentStep = 0;
                        }
                        break;



                    case 50:
                        _Port.ReadExisting();
                        _Port.Write(Encoding.Default.GetString(byStx) + "00230018            " + nPSet.ToString("000") + Encoding.Default.GetString(byNULEtx));
                        ClearReadBuffer();
                        _tSendDelayTimer.Start(50);
                        nCurrentStep = 31;
                        _tTimer.Restart();
                        AliveTimer.Restart();
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
