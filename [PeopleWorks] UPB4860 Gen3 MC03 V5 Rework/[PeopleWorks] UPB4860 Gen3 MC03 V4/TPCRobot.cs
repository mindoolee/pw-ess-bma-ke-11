using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
    // TPC 통신 프로토콜

    // 송신 명령어 
    // HOME : 홈으로 이동
    // START : 작업 시작
    // VRESUME : 비전 재촬영
    // NEXT : 다음포인트로

    // 수신 명령어
    // OK : 작업 완료
    // VNG : 비전 NG
    // TNG : 체결 NG
   
    // 플로우
    // -> 프로젝트선택
    // <- PSELECTOK or PSELECTNG
    // -> START
    // <- PSTARTOK
    // <- VNG or TNG or OK
    // -> NEXT or HOME
    // <- FINISH
    // <- HOME
   


    // 수신시에는 STX 0x02 , ETX 0x03



    // IN #1 : TOOL START
    // IN #2 :
    // IN #3 :
    // IN #4 : 

    public class TPCRobot
    {
        // 공통 외부 참조
        public bool bPortStat = false;

        public int nStation;

        public TPC_STAT _Stat = new TPC_STAT();


        public bool bFinishFlag;

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
                        if (readTemp == "HOME") { _Stat = TPC_STAT.HOME; }
                        else if (readTemp == "OK") { _Stat = TPC_STAT.OK; }
                        else if (readTemp == "TNG") { _Stat = TPC_STAT.TNG; }
                        else if (readTemp == "VNG") { _Stat = TPC_STAT.VNG; }
                        else if (readTemp == "FINISH") { bFinishFlag = true; }
                        else if (readTemp == "PSELECTOK") { _Stat = TPC_STAT.PSELECTOK; }
                        else if (readTemp == "PSELECTNG") { _Stat = TPC_STAT.PSELECTNG; }
                        else if (readTemp == "PSTARTOK") { _Stat = TPC_STAT.PSTARTOK; }

                        string strFolderPath = String.Format(@"TMLOG\\");

                        DirectoryInfo dir = new DirectoryInfo(strFolderPath);
                        if (dir.Exists == false) { dir.Create(); }

                        // TM로봇 로그 남기기
                        string savePath = String.Format("{0}{1:D4}{2:D2}{3:D2}.txt", strFolderPath, DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
                        System.IO.File.AppendAllText(savePath, DateTime.Now.ToString("[HH:mm:ss]") + ",PC<-TM,RS 232," + readTemp + "\r\n", Encoding.Default);

                    }


                }
            }
            catch { }

        }



        // 커맨드
        public void SetHome() { _Stat = TPC_STAT.READY; WriteData("HOME"); Program.AppendLogMsg("SetHome", LOG_TYPE.INFO); }                // HOME 으로 이동
        public void SetNext() { _Stat = TPC_STAT.READY; WriteData("NEXT"); Program.AppendLogMsg("SetNEXT", LOG_TYPE.INFO); }                // 다음 행정 작업
        public void SetVresume() { _Stat = TPC_STAT.READY; WriteData("VRESUME"); Program.AppendLogMsg("SetVRESUME", LOG_TYPE.INFO); }          // 비전 재시도
        public void SetModel(string str) { _Stat = TPC_STAT.READY; WriteData(str); Program.AppendLogMsg(String.Format("SetModel : {0}", str), LOG_TYPE.INFO); }        // 모델 선택
        public void SetStart() { _Stat = TPC_STAT.READY; WriteData("START"); Program.AppendLogMsg("SetSTART", LOG_TYPE.INFO); bFinishFlag = false; }              // 시작 명령
        public void SetOk() { WriteData("OK"); }                // OK 으로 이동
        public void SetNg() { WriteData("NG"); }                // OK 으로 이동


        void WriteData(string str)
        {
            port.Write(str);


            string strFolderPath = String.Format(@"TMLOG\\");

            DirectoryInfo dir = new DirectoryInfo(strFolderPath);
            if (dir.Exists == false) { dir.Create(); }

            // TM로봇 로그 남기기
            string savePath = String.Format("{0}{1:D4}{2:D2}{3:D2}.txt", strFolderPath, DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
            System.IO.File.AppendAllText(savePath, DateTime.Now.ToString("[HH:mm:ss]") + ",PC->TM,RS 232," + str + "\r\n", Encoding.Default);


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
