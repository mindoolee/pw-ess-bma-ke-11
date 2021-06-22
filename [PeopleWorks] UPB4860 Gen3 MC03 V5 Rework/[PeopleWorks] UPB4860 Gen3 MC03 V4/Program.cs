using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.IO.Ports;
using System.IO;
using System.Diagnostics;
using System.Drawing;
using System.Data;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections;
using System.Reflection;
using Newtonsoft.Json;
using System.Globalization;
using Oracle.ManagedDataAccess.Client;
using System.Net.Sockets;

namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
    static class Program
    {
        //========== 쓰레드
        public static Thread MainThread = new Thread(WorkMain);



        //========== 메인폼
        public static MainForm _mainform;
        public static ModelSetup _modelSetup;
        public static Mirae_Timer[] tMainTimer = new Mirae_Timer[100];
        public static Mirae_Timer[] tAlamTimer = new Mirae_Timer[100]; // 메인 알람용 타이머
        public static Mirae_Timer[] tFeederTimer = new Mirae_Timer[4];
        public static Mirae_Timer[] tUnLockTimer = new Mirae_Timer[6];
        public static Stopwatch _tIRLogTimer = new Stopwatch();

        public static Mirae_Timer tCVTimer = new Mirae_Timer();

        //========== 모델 정보
        public static MODEL_INFO _ModelInfo = new MODEL_INFO();

        //========== Can 통신
        public static PCanComm _CanComm = new PCanComm();

        //========== 바코드 스캐너 통신
        public static BarcodeReader _BCDReader = new BarcodeReader();
        public static BarcodeReader _ETCReader = new BarcodeReader();
        public static BarcodeReader _ST1Reader = new BarcodeReader();       // 스테이션 1번 스캐너

        //========== 바코드 스캐너 통신
        public static HoneyWell _EOLReader = new HoneyWell();
        public static HoneyWell _HIPOTReader = new HoneyWell();

        //========== TPC 로봇 통신
        public static TPCRobot _TPCRobot = new TPCRobot();

        //========== 모터 정보
        public static MOTOR_DATA[] _MotorAxisInfo = new MOTOR_DATA[20];

        //========== 홈서치 파라메터 종류
        public static SEARCH_HOME_PARAM _Search_ALL = new SEARCH_HOME_PARAM();

        //========== 프로세스 스텝
        public static int[] nProcessStep = new int[100];


        public static NutSocket1[] nutSocket = new NutSocket1[6];

        public static bool[] bCounterConatct = new bool[6];

        //========== 대류 테스터기 통신
        public static BatteryTester3[] _BatteryTester = new BatteryTester3[2];

        public static BatteryTester2 _BatteryTester2 = new BatteryTester2();


        //========== 거리 측정 센서 통신
        public static IL1000 _TesterDistance = new IL1000();


        //========== 바코드 프린터 통신
        public static BarcodePrint _BCDPrint = new BarcodePrint();

        //========== 누적 수량 정보
        public static ProductCount _Count = new ProductCount();

        public static LotCount _LotCount = new LotCount();

        //========== 바코드 리딩 데이터 테이블
        //public static DataTable _dtBCDInfo = new DataTable();

        //========== 계측기
        public static Chroma_19032 _HipotTester = new Chroma_19032();

        //========== 너트러너 통신
        public static Nutrunner[] _NutRunner = new Nutrunner[6];

        //========== 이더넷 타입 너트러너 통신
        public static NutrunnerEth[] _NutRunnerEth = new NutrunnerEth[6];

        //public static NutrunnerEth _nutEth = new NutrunnerEth();



        //=========== 결과
        public static DATA_RESULT _HipotResult = new DATA_RESULT();

        public static Stopwatch _tHipotTimer = new Stopwatch();

        public static Stopwatch[] _tSTCycleTimer = new Stopwatch[20];
        public static DateTime[] _tSTCycleStartTime = new DateTime[20];
        public static DateTime[] _tSTCycleEndTime = new DateTime[20];

        public static DateTime _MasterLoadTime = new DateTime();


        public static HipotDSSWAlarm _hipotDsForm;

        public static DateTime _DtCMATarget = new DateTime();
        // TPCRobot _TPCRobot = new TPCRobot();


        public static int nLangueIndex = 0;

        public static ArmXY _Arm = new ArmXY();

        public static ArmXYZ _ArmXYZ = new ArmXYZ();

        public static List<_ReadBarcodeData> _ReadBCDList = new List<_ReadBarcodeData>();

        // Station #1 리딩 바코드
        public static List<_ReadBarcodeData> _ST1BCDList = new List<_ReadBarcodeData>();



        public static List<string> _NgDataList = new List<string>();

        public static Stopwatch _tAliveTimer = new Stopwatch();


        // Omron 외함측정 프로세스
        public static OmronWHTester _OmronWHTester = new OmronWHTester();

        //========== 바코드 스캐너 통신
        public static BarcodeReader _HipotHandReader = new BarcodeReader();
        public static BarcodeReader _EOLHandReader = new BarcodeReader();

        //========== 레이저 마킹기
        public static LaserMarking _LaserMarking = new LaserMarking();
        public static BarcodeReader _LaserReader = new BarcodeReader();

        [STAThread]
        static void Main()
        {
            bool createdNew = true;

            using (Mutex mutex = new Mutex(true, Application.ProductName, out createdNew))
            {
                if (createdNew)
                {

                    //uint[] dwaSendData = new uint[22];
                    //for (int i = 0; i < dwaSendData.Length; i++) { dwaSendData[i] = 0x00; }
                    //CAXDev.AxlSetSendBoardCommand(0, 0x74, ref dwaSendData[0], 0);

                    //Thread.Sleep(5000);

                    //CAXL.AxlClose();
                    CAXL.AxlOpen(7);



                    LoadIniFile();
                    LoadTorqueSpec();
                    LoadNgList();
                    LoadProductCount();
                    LoadSTLockInfo(0);
                    LoadSTLockInfo(1);
                    LoadSTLockInfo(2);
                    LoadSTLockInfo(3);
                    LoadBCDListInfo();
                    LoadModelInfo(ref _ModelInfo, _Config.strCurrentModel);
                    LoadModelProductCount(_ModelInfo.strModelName);
                    _MasterLoadTime = DateTime.Now;

                    _BatteryTester[0] = new BatteryTester3();
                    _BatteryTester[1] = new BatteryTester3();

                    //_dtBCDInfo.TableName = "BCDInfo";
                    //_dtBCDInfo.Columns.Add("Barcode");
                    //_dtBCDInfo.Columns.Add("Type");

                    //LoadBCDInfoTable();

                    for (int i = 0; i < tFeederTimer.Length; i++) { tFeederTimer[i] = new Mirae_Timer(); }
                    for (int i = 0; i < nutSocket.Length; i++) { nutSocket[i] = new NutSocket1(); }
                    for (int i = 0; i < _NutRunner.Length; i++) { _NutRunner[i] = new Nutrunner(); }
                    for (int i = 0; i < _NutRunnerEth.Length; i++) { _NutRunnerEth[i] = new NutrunnerEth(); }      // 이더넷 타입 너트러너 통신
                    for (int i = 0; i < tMainTimer.Length; i++) { tMainTimer[i] = new Mirae_Timer(); }
                    for (int i = 0; i < tAlamTimer.Length; i++) { tAlamTimer[i] = new Mirae_Timer(); }
                    for (int i = 0; i < tUnLockTimer.Length; i++) { tUnLockTimer[i] = new Mirae_Timer(); }
                    for (int i = 0; i < _tSTCycleTimer.Length; i++) { _tSTCycleTimer[i] = new Stopwatch(); }
                    for (int i = 0; i < _tSTCycleStartTime.Length; i++) { _tSTCycleStartTime[i] = new DateTime(); }
                    for (int i = 0; i < _tSTCycleEndTime.Length; i++) { _tSTCycleEndTime[i] = new DateTime(); }
                    _Define.CreateDIOInfo();

                    AppDomain.CurrentDomain.AssemblyResolve += new ResolveEventHandler(ResolveAssembly);


                    Application.EnableVisualStyles();
                    Application.SetCompatibleTextRenderingDefault(false);
                    _mainform = new MainForm();
                    Application.Run(_mainform);
                }
                else
                {
                    MessageBox.Show("프로그램이 이미 실행중 입니다.");
                }
            }

        }


        static Assembly ResolveAssembly(object sender, ResolveEventArgs args)
        {
            Assembly thisAssembly = Assembly.GetExecutingAssembly();
            var name = args.Name.Substring(0, args.Name.IndexOf(',')) + ".dll";

            var resources = thisAssembly.GetManifestResourceNames().Where(s => s.EndsWith(name));
            if (resources.Count() > 0)
            {
                string resourceName = resources.First();
                using (Stream stream = thisAssembly.GetManifestResourceStream(resourceName))
                {
                    if (stream != null)
                    {
                        byte[] assembly = new byte[stream.Length];
                        stream.Read(assembly, 0, assembly.Length);
                        Console.WriteLine("Dll file load : " + resourceName);
                        return Assembly.Load(assembly);
                    }
                }
            }
            return null;
        }


        // 메인쓰레드
        static void WorkMain()
        {
            _SysInfo.Err_Code = ERR_CODE.NONE;
            _SysInfo.Old_Err_Code = ERR_CODE.NONE;
            _SysInfo.Alarm_Code = ALARM_CODE.NONE;
            _SysInfo.Old_Alarm_Code = ALARM_CODE.NONE;
            _SysInfo.bFirst = true;
            _SysInfo.bModelChangeFirstLoading = true;
            _SysInfo.bChangeHipotInfo = true;               // 최초시작시 하이팟 스케쥴 변경한다
            TowerLampBlink(LAMP_COLOR.TL_YELLOW);

            Thread.Sleep(500);

            int nThreadCount = 0;

            InitCommPort();

            // Alive 타이머를 적용한다
            //_tAliveTimer.Restart();

            while (!_SysInfo.bMainProcessStop)
            {
                //if(_ModelInfo.bUseTPCRobot || _ModelInfo.bUseST3Model2)
                //{
                //    SetDIOPort(DO.ROBOT_OUT1, GetDIOPort(DI.NUTRUNNER3_IN1));
                //    SetDIOPort(DO.ROBOT_OUT2, GetDIOPort(DI.NUTRUNNER3_IN2));
                //    SetDIOPort(DO.ROBOT_OUT3, GetDIOPort(DI.NUTRUNNER3_IN3));
                //    SetDIOPort(DO.ROBOT_OUT4, GetDIOPort(DI.NUTRUNNER3_IN4));

                //    SetDIOPort(DO.NUTRUNNER3_OUT1, GetDIOPort(DI.ROBOT_IN1));
                //    SetDIOPort(DO.NUTRUNNER3_OUT2, GetDIOPort(DI.ROBOT_IN2));
                //    SetDIOPort(DO.NUTRUNNER3_OUT3, GetDIOPort(DI.ROBOT_IN3));
                //    SetDIOPort(DO.NUTRUNNER3_OUT4, GetDIOPort(DI.ROBOT_IN4));


                //    for (int i = 0; i < 4; i++)
                //    {
                //        if (GetDIOPort(DI.ROBOT_IN1 + i) != _SysInfo.bInOldStatTm[i])
                //        {   // TM IN 1번 스테이터스에 변화가 있는 경우

                //            string strFolderPath = String.Format(@"TMLOG\\");

                //            DirectoryInfo dir = new DirectoryInfo(strFolderPath);
                //            if (dir.Exists == false) { dir.Create(); }

                //            // TM로봇 로그 남기기
                //            string savePath = String.Format("{0}{1:D4}{2:D2}{3:D2}.txt", strFolderPath, DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
                //            System.IO.File.AppendAllText(savePath, DateTime.Now.ToString("[HH:mm:ss]") + ",PC<-TM," + "IO #" + (i + 1).ToString() + "," + GetDIOPort(DI.ROBOT_IN1 + i).ToString() + "\r\n", Encoding.Default);

                //            _SysInfo.bInOldStatTm[i] = GetDIOPort(DI.ROBOT_IN1 + i);
                //        }

                //        if (GetDIOPortStat(DO.ROBOT_OUT1 + i) != _SysInfo.bOutOldStatTm[i])
                //        {   // TM IN 1번 스테이터스에 변화가 있는 경우

                //            string strFolderPath = String.Format(@"TMLOG\\");

                //            DirectoryInfo dir = new DirectoryInfo(strFolderPath);
                //            if (dir.Exists == false) { dir.Create(); }

                //            // TM로봇 로그 남기기
                //            string savePath = String.Format("{0}{1:D4}{2:D2}{3:D2}.txt", strFolderPath, DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
                //            System.IO.File.AppendAllText(savePath, DateTime.Now.ToString("[HH:mm:ss]") + ",PC->TM," + "IO #" + (i + 1).ToString() + "," + GetDIOPortStat(DO.ROBOT_OUT1 + i).ToString() + "\r\n", Encoding.Default);
                //            _SysInfo.bOutOldStatTm[i] = GetDIOPortStat(DO.ROBOT_OUT1 + i);
                //        }


                //        if (GetDIOPort(DI.NUTRUNNER3_IN1 + i) != _SysInfo.bInOldStatNut[i])
                //        {   // TM IN 1번 스테이터스에 변화가 있는 경우

                //            string strFolderPath = String.Format(@"TMLOG\\");

                //            DirectoryInfo dir = new DirectoryInfo(strFolderPath);
                //            if (dir.Exists == false) { dir.Create(); }

                //            // TM로봇 로그 남기기
                //            string savePath = String.Format("{0}{1:D4}{2:D2}{3:D2}.txt", strFolderPath, DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
                //            System.IO.File.AppendAllText(savePath, DateTime.Now.ToString("[HH:mm:ss]") + ",PC<-NUT3," + "IO #" + (i + 1).ToString() + "," + GetDIOPort(DI.NUTRUNNER3_IN1 + i).ToString() + "\r\n", Encoding.Default);

                //            _SysInfo.bInOldStatNut[i] = GetDIOPort(DI.NUTRUNNER3_IN1 + i);
                //        }

                //        if (GetDIOPortStat(DO.NUTRUNNER3_OUT1 + i) != _SysInfo.bOutOldStatNut[i])
                //        {   // TM IN 1번 스테이터스에 변화가 있는 경우

                //            string strFolderPath = String.Format(@"TMLOG\\");

                //            DirectoryInfo dir = new DirectoryInfo(strFolderPath);
                //            if (dir.Exists == false) { dir.Create(); }

                //            // TM로봇 로그 남기기
                //            string savePath = String.Format("{0}{1:D4}{2:D2}{3:D2}.txt", strFolderPath, DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
                //            System.IO.File.AppendAllText(savePath, DateTime.Now.ToString("[HH:mm:ss]") + ",PC->NUT3," + "IO #" + (i + 1).ToString() + "," + GetDIOPortStat(DO.NUTRUNNER3_OUT1 + i).ToString() + "\r\n", Encoding.Default);
                //            _SysInfo.bOutOldStatNut[i] = GetDIOPortStat(DO.NUTRUNNER3_OUT1 + i);
                //        }


                //    }

                //    TM_ROBOT_IO();
                //}



                //_nutEth.Process();

                //_TPCRobot.Process();
                _CanComm.ReadMessage();
                LotCountInfoUpdate();
                SUB_CABLE_PRODUCT();
                _BCDPrint.Process();
                _BatteryTester[0].Process();
                _BatteryTester[1].Process();
                _BatteryTester2.Process();

                //CMALoadingUnSafeLock();  6호기로 컨버팅 하면서 SMEMA 인터락 동작 취소

                _BCDReader.Process();
                _ETCReader.Process();
                _EOLReader.Process();
                _HIPOTReader.Process();
                _ST1Reader.Process();



                //if (_Config.bUseNutrunnerEthMode)
                //{
                //    if (_Config.bUseNutrunner[0]) _NutRunnerEth[0].Process();
                //    if (_Config.bUseNutrunner[1]) _NutRunnerEth[1].Process();
                //    if (_Config.bUseNutrunner[2]) _NutRunnerEth[2].Process();
                //    if (_Config.bUseNutrunner[3]) _NutRunnerEth[3].Process();
                //    if (_Config.bUseNutrunner[4]) _NutRunnerEth[4].Process();
                //    if (_Config.bUseNutrunner[5]) _NutRunnerEth[5].Process();
                //}
                //else
                //{
                    _NutRunner[0].Process();
                    _NutRunner[1].Process();
                    _NutRunner[2].Process();
                    _NutRunner[3].Process();
                    _NutRunner[4].Process();
                    _NutRunner[5].Process();
                //}

                _OmronWHTester.Process();

                _HipotHandReader.Process();
                _EOLHandReader.Process();

                _LaserMarking.Process();
                _LaserReader.Process();



                _Arm.Process();
                //_ArmXYZ.Process();

                //_TesterDistance.Process();


                WorkMainProcess();


                WorkLockingProcess(0);
                WorkLockingProcess(1);
                WorkLockingProcess(2);
                WorkLockingProcess(3);
                WorkLockingProcess(4);


                // 체결 프로세스 밖으로 뺐음
                SUB_TITE_PROCESS(0);
                SUB_TITE_PROCESS(1);
                SUB_TITE_PROCESS(2);
                SUB_TITE_PROCESS(3);
                SUB_TITE_PROCESS(4);
                SUB_TITE_PROCESS(5);

                CountCommunication(0);
                CountCommunication(1);
                CountCommunication(2);
                CountCommunication(3);
                CountCommunication(4);
                CountCommunication(5);

                // 부저 및 램프 프로세스
                CounterBuzzerProcess(0);
                CounterBuzzerProcess(1);
                CounterBuzzerProcess(2);
                CounterBuzzerProcess(3);
                CounterBuzzerProcess(4);
                CounterBuzzerProcess(5);
                CounterBuzzerProcess(6);
                CounterBuzzerProcess(7);
                CounterBuzzerProcess(8);

                WorkStationLampProcess(0);
                WorkStationLampProcess(1);
                WorkStationTowerLampProcess(0);
                WorkStationTowerLampProcess(1);

                WorkLoadingProcess();

                WORK_INLIFT_PROC();
                WorkHipotProcess();
                WorkEolProcess();

                WorkOutLiftProcess();



                SUB_MARKING();              // 레이저 마킹 프로세스
                SUB_MARKING_READ();         // 레이저 마킹 바코드 스캔


                TowerBuzzerProcess();
                TowerLampProcess();
                WorkManualProcess();



                //AliveCheckProcess();
                //MasterModelLoadProcess();



                //System.Windows.Forms.Application.DoEvents();

                nThreadCount++;

                if (nThreadCount > 100)
                {
                    nThreadCount = 0;
                    Thread.Sleep(1);
                }


            }


            _BCDReader.Stop();
            _ETCReader.Stop();
            _BCDPrint.Stop();
            _ST1Reader.Stop();

            //          _BatteryTester[0].Stop();
            //          _BatteryTester[1].Stop();
            _BatteryTester2.Stop();
            _EOLReader.Stop();
            _HIPOTReader.Stop();

            _NutRunner[0].Stop();
            _NutRunner[1].Stop();
            _NutRunner[2].Stop();
            _NutRunner[3].Stop();
            _NutRunner[4].Stop();
            _NutRunner[5].Stop();
            _Arm.Stop();


            nutSocket[0].StopServer();
            nutSocket[1].StopServer();
            nutSocket[2].StopServer();
            nutSocket[3].StopServer();
            nutSocket[4].StopServer();
            nutSocket[5].StopServer();

            Thread.Sleep(200);

            _BatteryTester[1].CloseComm();

            _BCDReader.CloseComm();
            _ETCReader.CloseComm();
            _BCDPrint.CloseComm();
            _ST1Reader.CloseComm();
            _BatteryTester[0].CloseComm();
            _BatteryTester[1].CloseComm();
            _BatteryTester2.CloseComm();
            _EOLReader.CloseComm();
            _HIPOTReader.CloseComm();
            _Arm.CloseComm();
            _TesterDistance.CloseComm();
            _ArmXYZ.CloseComm();


            _NutRunner[0].CloseComm();
            _NutRunner[1].CloseComm();
            _NutRunner[2].CloseComm();
            _NutRunner[3].CloseComm();
            _NutRunner[4].CloseComm();
            _NutRunner[5].CloseComm();
            _HipotTester.port.Close();

            _HipotHandReader.CloseComm();
            _EOLHandReader.CloseComm();

            _LaserMarking.CloseComm();
            _LaserReader.CloseComm();


            Thread.Sleep(200);

            while (_BatteryTester[1].port.IsOpen) { Thread.Sleep(1); }
            while (_BCDReader._Port.IsOpen) { Thread.Sleep(1); }
            while (_ST1Reader._Port.IsOpen) { Thread.Sleep(1); }

            while (_ETCReader._Port.IsOpen) { Thread.Sleep(1); }
            while (_BCDPrint._Port.IsOpen) { Thread.Sleep(1); }
            while (_BatteryTester[0].port.IsOpen) { Thread.Sleep(1); }
            while (_BatteryTester[1].port.IsOpen) { Thread.Sleep(1); }
            while (_BatteryTester2.port.IsOpen) { Thread.Sleep(1); }
            while (_EOLReader._Port.IsOpen) { Thread.Sleep(1); }
            while (_HIPOTReader._Port.IsOpen) { Thread.Sleep(1); }
            while (_NutRunner[0]._Port.IsOpen) { Thread.Sleep(1); }
            while (_NutRunner[1]._Port.IsOpen) { Thread.Sleep(1); }
            while (_NutRunner[2]._Port.IsOpen) { Thread.Sleep(1); }
            while (_NutRunner[3]._Port.IsOpen) { Thread.Sleep(1); }
            while (_NutRunner[4]._Port.IsOpen) { Thread.Sleep(1); }
            while (_NutRunner[5]._Port.IsOpen) { Thread.Sleep(1); }
            while (_TesterDistance.port.IsOpen) { Thread.Sleep(1); }
            while (_HipotTester.port.IsOpen) { Thread.Sleep(1); }
            while (_Arm.port.IsOpen) { Thread.Sleep(1); }
            while (_ArmXYZ.port.IsOpen) { Thread.Sleep(1); }
            while (_HipotHandReader._Port.IsOpen) { Thread.Sleep(1); }
            while (_EOLHandReader._Port.IsOpen) { Thread.Sleep(1); }

            while (_LaserMarking._Port.IsOpen) { Thread.Sleep(1); }
            while (_LaserReader._Port.IsOpen) { Thread.Sleep(1); }

            SaveIniFile();


            for (int i = (int)AXIS.X; i <= (int)AXIS.EOL_Z; i++)
            {
                CAXM.AxmSignalServoOn(i, 0);
            }


            for (int i = 0; i < 0xFF; i++)
            {
                SetDIOPort((DO)i, false);
            }

            _mainform.BeginInvoke(new Action(() => _mainform.Close()));

        }


        static void TM_ROBOT_IO()
        {
            int nStepIndex = (int)PROC_LIST.ROBOT_IO;

            switch (nProcessStep[nStepIndex])
            {
                case 0:
                    if (!GetDIOPort(DI.NUTRUNNER3_IN3))
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    break;


                case 1:
                    if (GetDIOPort(DI.NUTRUNNER3_IN3))
                    {
                        // 작업완료 신호가 들어온다면
                        if (GetDIOPort(DI.NUTRUNNER3_IN1))
                        {
                            // 1번이 들어왔다면 OK 전송
                            _SysInfo.bTPCReadOK = false;
                            _SysInfo.nTPCSendRetryCount = 0;
                            tMainTimer[nStepIndex].Start(1000);

                            _TPCRobot.SetOk();
                            nProcessStep[nStepIndex] = 5;
                        }
                        else if (GetDIOPort(DI.NUTRUNNER3_IN2))
                        {
                            // 2번이 들어왔다면 NG 전송
                            _SysInfo.bTPCReadOK = false;
                            _SysInfo.nTPCSendRetryCount = 0;
                            tMainTimer[nStepIndex].Start(1000);

                            _TPCRobot.SetNg();
                            nProcessStep[nStepIndex] = 10;

                        }
                    }
                    break;



                // OK 신호 재송신 행정
                case 5:
                    if (_SysInfo.bTPCReadOK)
                    {
                        // TPC 에서 응답이 왔다면
                        nProcessStep[nStepIndex] = 0;   // 0번으로 복귀
                        break;
                    }
                    else if (tMainTimer[nStepIndex].Verify() && _SysInfo.nTPCSendRetryCount < 3)
                    {
                        _SysInfo.nTPCSendRetryCount++;
                        _TPCRobot.SetOk();
                        tMainTimer[nStepIndex].Start(1000);
                    }
                    else if (_SysInfo.nTPCSendRetryCount >= 3)
                    {
                        // 재전송 횟수를 초과했을 경우
                        nProcessStep[nStepIndex] = 0;
                    }
                    break;



                case 10:
                    if (_SysInfo.bTPCReadOK)
                    {
                        // TPC 에서 응답이 왔다면
                        nProcessStep[nStepIndex] = 0;   // 0번으로 복귀
                        break;
                    }
                    else if (tMainTimer[nStepIndex].Verify() && _SysInfo.nTPCSendRetryCount < 3)
                    {
                        _SysInfo.nTPCSendRetryCount++;
                        _TPCRobot.SetNg();
                        tMainTimer[nStepIndex].Start(1000);
                    }
                    else if (_SysInfo.nTPCSendRetryCount >= 3)
                    {
                        // 재전송 횟수를 초과했을 경우
                        nProcessStep[nStepIndex] = 0;
                    }
                    break;
            }


        }

        // CMA 로딩 로봇 SMEMA 인터락
        static void CMALoadingUnSafeLock()
        {
            double dbPosX = 0.0;
            double dbPosZ = 0.0;

            CAXM.AxmStatusGetCmdPos((int)AXIS.X, ref dbPosX);
            CAXM.AxmStatusGetCmdPos((int)AXIS.Z, ref dbPosZ);

            if (_Config.dbLoadingUnSafePosX < dbPosX && _Config.dbLoadingUnSafePosZ < dbPosZ)
            {
                SetDIOPort(DO.SMEMA_OUT1, false);
            }
            else
            {
                SetDIOPort(DO.SMEMA_OUT1, true);
            }
        }



        // 메인 프로세스
        static void WorkMainProcess()
        {
            int nStepIndex = (int)PROC_LIST.MAIN;


            WorkCV();


            // 최초 시작시 200ms 딜레이 후 감시 시작
            if (_SysInfo.bFirst)
            {
                tAlamTimer[(int)MAINALAM_TIME.SERVO].Start(500);
                tAlamTimer[(int)MAINALAM_TIME.MAIN].Start(500);
                tAlamTimer[(int)MAINALAM_TIME.AIR].Start(500);
                _SysInfo.bFirst = false;
            }

            // ++ 시스템 알람발생 감지 ////////////////////////////////////////
            // 모션 감시
            if (tAlamTimer[(int)MAINALAM_TIME.SERVO].Verify())
            {
                uint upStatus = 0;

                for (int i = (int)AXIS.X; i <= (int)AXIS.CAMERA2_Z; i++)
                {
                    //if (_Config.bUseReworkLineMode)
                    //{
                    //if (i >= (int)AXIS.HIPOT_1X)
                    //{
                    //    CAXM.AxmSignalReadServoAlarm(i, ref upStatus);

                    //    if (_SysInfo.bServoErrMonitor)
                    //    {
                    //        if (upStatus != 0)
                    //            _SysInfo.Err_Code |= (ERR_CODE)((int)ERR_CODE.X << i);
                    //    }
                    //}
                    //}
                    //else
                    //{
                    

                    // 알람 모니터링 방법 변경 21.05.21(홍)
                    CAXM.AxmSignalReadServoAlarm(i, ref upStatus);

                    if (_SysInfo.bServoErrMonitor)
                    {
                        if(i != (int)AXIS.ST3_R)
                        {
                            if (upStatus != 0)
                                _SysInfo.Err_Code |= (ERR_CODE)((int)ERR_CODE.X << i);
                        }

                    }
                    //}

                }

                tAlamTimer[(int)MAINALAM_TIME.SERVO].Start(200);
            }

            // 메인 감시
            if (tAlamTimer[(int)MAINALAM_TIME.MAIN].Verify())
            {
                // 비상 정지 감시
                if ((int)(_SysInfo.Err_Code & ERR_CODE.EMG_SW) == 0)
                {
                    if (!GetDIOPort(DI.EMG_SW)) { _SysInfo.Err_Code |= ERR_CODE.EMG_SW; }
                }

                if (_Config.bAirPressure)
                {
                    // 공압 감시
                    if ((int)(_SysInfo.Err_Code & ERR_CODE.AIR_PRESSURE) == 0)
                    {
                        if (!GetDIOPort(DI.AIR_PRESSURE) || !GetDIOPort(DI.AIR_PRESSURE)) { _SysInfo.Err_Code |= ERR_CODE.AIR_PRESSURE; }
                    }
                }




                tAlamTimer[(int)MAINALAM_TIME.MAIN].Start(200);
            }

            // ++ 에러 추적 ///////////////////////////////////////////////////
            if (_SysInfo.Err_Code != _SysInfo.Old_Err_Code)
            {
                if (_SysInfo.Err_Code == ERR_CODE.NONE)
                {
                    //TowerLampOn(LAMP_COLOR.TL_GREEN);
                }
                else if (_SysInfo.Err_Code == ERR_CODE.NO_ORG)
                {
                    //TowerLampOn(LAMP_COLOR.TL_YELLOW);
                }
                else
                {
                    TowerLampOn(LAMP_COLOR.TL_RED);
                    _SysInfo.TL_Buzzer = TOWER_LAMP.TL_ON;
                    _SysInfo.Main_Status = MAIN_STATUS.SYSTEM_ERR;
                    _SysInfo.bAutoRunning = false;

                    // 모든 행정 스텝 0 으로
                    for (int i = (int)STATION_LIST.LOADING; i <= (int)STATION_LIST.UNLOADING; i++)
                    {
                        _SysInfo.bStationAutoMode[i] = false;
                    }

                    // 검사기에 STOP 보냄
                    _BatteryTester[1].WriteData("END");

                    //_BatteryTester[1].bStop = true;
                    //_BatteryTester[1].nCurrentStep = 0;


                    _HipotTester.TestStop();

                    // 알람상태가 되면 서보 OFF
                    for (int i = (int)AXIS.X; i <= (int)AXIS.CAMERA2_Z; i++)
                    {
                        CAXM.AxmMoveEStop(i);
                        CAXM.AxmSignalServoOn(i, 0);
                    }

                    //SetDIOPort(DO.SERVO_ON, false);
                    nProcessStep[(int)PROC_LIST.MAIN] = 0;

                    // 비상정지 스위치 눌림
                    if ((int)(_SysInfo.Err_Code & ERR_CODE.EMG_SW) != 0 && (int)(_SysInfo.Old_Err_Code & ERR_CODE.EMG_SW) == 0)
                    {
                        AppendLogMsg("EMERGENCY..", LOG_TYPE.ERROR);
                    }



                    // 공압감지 에러
                    if ((int)(_SysInfo.Err_Code & ERR_CODE.AIR_PRESSURE) != 0 && (int)(_SysInfo.Old_Err_Code & ERR_CODE.AIR_PRESSURE) == 0)
                        AppendLogMsg("AIR SUPPLY ERROR..", LOG_TYPE.ERROR);

                    // 모션 에러
                    if ((int)(_SysInfo.Err_Code & ERR_CODE.X) != 0 && (int)(_SysInfo.Old_Err_Code & ERR_CODE.X) == 0)
                        AppendLogMsg("SERVO X ALARM..", LOG_TYPE.ERROR);

                    if ((int)(_SysInfo.Err_Code & ERR_CODE.Y) != 0 && (int)(_SysInfo.Old_Err_Code & ERR_CODE.Y) == 0)
                        AppendLogMsg("SERVO Y ALARM..", LOG_TYPE.ERROR);

                    if ((int)(_SysInfo.Err_Code & ERR_CODE.Z) != 0 && (int)(_SysInfo.Old_Err_Code & ERR_CODE.Z) == 0)
                        AppendLogMsg("SERVO Z ALARM..", LOG_TYPE.ERROR);

                    if ((int)(_SysInfo.Err_Code & ERR_CODE.R) != 0 && (int)(_SysInfo.Old_Err_Code & ERR_CODE.R) == 0)
                        AppendLogMsg("SERVO R ALARM..", LOG_TYPE.ERROR);

                    if ((int)(_SysInfo.Err_Code & ERR_CODE.HIPOT_1X) != 0 && (int)(_SysInfo.Old_Err_Code & ERR_CODE.HIPOT_1X) == 0)
                        AppendLogMsg("SERVO HIPOT_1X ALARM..", LOG_TYPE.ERROR);

                    if ((int)(_SysInfo.Err_Code & ERR_CODE.HIPOT_1Y) != 0 && (int)(_SysInfo.Old_Err_Code & ERR_CODE.HIPOT_1Y) == 0)
                        AppendLogMsg("SERVO HIPOT_1Y ALARM..", LOG_TYPE.ERROR);

                    if ((int)(_SysInfo.Err_Code & ERR_CODE.HIPOT_1Z) != 0 && (int)(_SysInfo.Old_Err_Code & ERR_CODE.HIPOT_1Z) == 0)
                        AppendLogMsg("SERVO HIPOT_1Z ALARM..", LOG_TYPE.ERROR);

                    if ((int)(_SysInfo.Err_Code & ERR_CODE.HIPOT_2X) != 0 && (int)(_SysInfo.Old_Err_Code & ERR_CODE.HIPOT_2X) == 0)
                        AppendLogMsg("SERVO HIPOT_2X ALARM..", LOG_TYPE.ERROR);

                    if ((int)(_SysInfo.Err_Code & ERR_CODE.HIPOT_2Y) != 0 && (int)(_SysInfo.Old_Err_Code & ERR_CODE.HIPOT_2Y) == 0)
                        AppendLogMsg("SERVO HIPOT_2Y ALARM..", LOG_TYPE.ERROR);

                    if ((int)(_SysInfo.Err_Code & ERR_CODE.HIPOT_2Z) != 0 && (int)(_SysInfo.Old_Err_Code & ERR_CODE.HIPOT_2Z) == 0)
                        AppendLogMsg("SERVO HIPOT_2Z ALARM..", LOG_TYPE.ERROR);

                    if ((int)(_SysInfo.Err_Code & ERR_CODE.EOL_X) != 0 && (int)(_SysInfo.Old_Err_Code & ERR_CODE.EOL_X) == 0)
                        AppendLogMsg("SERVO EOL_X ALARM..", LOG_TYPE.ERROR);

                    if ((int)(_SysInfo.Err_Code & ERR_CODE.EOL_Y) != 0 && (int)(_SysInfo.Old_Err_Code & ERR_CODE.EOL_Y) == 0)
                        AppendLogMsg("SERVO EOL_Y ALARM..", LOG_TYPE.ERROR);

                    if ((int)(_SysInfo.Err_Code & ERR_CODE.EOL_Z) != 0 && (int)(_SysInfo.Old_Err_Code & ERR_CODE.EOL_Z) == 0)
                        AppendLogMsg("SERVO EOL_Z ALARM..", LOG_TYPE.ERROR);

                    if ((int)(_SysInfo.Err_Code & ERR_CODE.CAMERA1_X) != 0 && (int)(_SysInfo.Old_Err_Code & ERR_CODE.CAMERA1_X) == 0)
                        AppendLogMsg("SERVO CAMERA1_X ALARM..", LOG_TYPE.ERROR);

                    if ((int)(_SysInfo.Err_Code & ERR_CODE.CAMERA1_Y) != 0 && (int)(_SysInfo.Old_Err_Code & ERR_CODE.CAMERA1_Y) == 0)
                        AppendLogMsg("SERVO CAMERA1_Y ALARM..", LOG_TYPE.ERROR);

                    if ((int)(_SysInfo.Err_Code & ERR_CODE.CAMERA1_Z) != 0 && (int)(_SysInfo.Old_Err_Code & ERR_CODE.CAMERA1_Z) == 0)
                        AppendLogMsg("SERVO CAMERA1_Z ALARM..", LOG_TYPE.ERROR);

                    if ((int)(_SysInfo.Err_Code & ERR_CODE.CAMERA2_X) != 0 && (int)(_SysInfo.Old_Err_Code & ERR_CODE.CAMERA2_X) == 0)
                        AppendLogMsg("SERVO CAMERA2_X ALARM..", LOG_TYPE.ERROR);

                    if ((int)(_SysInfo.Err_Code & ERR_CODE.CAMERA2_Y) != 0 && (int)(_SysInfo.Old_Err_Code & ERR_CODE.CAMERA2_Y) == 0)
                        AppendLogMsg("SERVO CAMERA2_Y ALARM..", LOG_TYPE.ERROR);

                    if ((int)(_SysInfo.Err_Code & ERR_CODE.CAMERA2_Z) != 0 && (int)(_SysInfo.Old_Err_Code & ERR_CODE.CAMERA2_Z) == 0)
                        AppendLogMsg("SERVO CAMERA2_Z ALARM..", LOG_TYPE.ERROR);

                    


                }
                _SysInfo.Old_Err_Code = _SysInfo.Err_Code;
            }

            // ++ 알람 해제 버튼이 눌렸을 경우 ////////////////////////////////
            if (_SysInfo.bErrorClear)
            {
                if (((int)(_SysInfo.Err_Code & ERR_CODE.NO_ORG) != 0 ||
                    (int)(_SysInfo.Err_Code & ERR_CODE.DIO_UNIT1) != 0 ||
                    (int)(_SysInfo.Err_Code & ERR_CODE.DIO_UNIT2) != 0 ||
                    (int)(_SysInfo.Err_Code & ERR_CODE.EMG_SW) != 0 ||
                    (int)(_SysInfo.Err_Code & ERR_CODE.X) != 0 ||
                    (int)(_SysInfo.Err_Code & ERR_CODE.Y) != 0 ||
                    (int)(_SysInfo.Err_Code & ERR_CODE.Z) != 0 ||
                    (int)(_SysInfo.Err_Code & ERR_CODE.R) != 0 ||
                    (int)(_SysInfo.Err_Code & ERR_CODE.HIPOT_1X) != 0 ||
                    (int)(_SysInfo.Err_Code & ERR_CODE.HIPOT_1Y) != 0 ||
                    (int)(_SysInfo.Err_Code & ERR_CODE.HIPOT_1Z) != 0 ||
                    (int)(_SysInfo.Err_Code & ERR_CODE.HIPOT_2X) != 0 ||
                    (int)(_SysInfo.Err_Code & ERR_CODE.HIPOT_2Y) != 0 ||
                    (int)(_SysInfo.Err_Code & ERR_CODE.HIPOT_2Z) != 0 ||
                    (int)(_SysInfo.Err_Code & ERR_CODE.EOL_X) != 0 ||
                    (int)(_SysInfo.Err_Code & ERR_CODE.EOL_Y) != 0 ||
                    (int)(_SysInfo.Err_Code & ERR_CODE.EOL_Z) != 0 ||
                    (int)(_SysInfo.Err_Code & ERR_CODE.CAMERA1_X) != 0 ||
                    (int)(_SysInfo.Err_Code & ERR_CODE.CAMERA1_Y) != 0 ||
                    (int)(_SysInfo.Err_Code & ERR_CODE.CAMERA1_Z) != 0 ||
                    (int)(_SysInfo.Err_Code & ERR_CODE.CAMERA2_X) != 0 ||
                    (int)(_SysInfo.Err_Code & ERR_CODE.CAMERA2_Y) != 0 ||
                    (int)(_SysInfo.Err_Code & ERR_CODE.CAMERA2_Z) != 0))
                {
                    _SysInfo.Err_Code = ERR_CODE.NO_ORG;
                    _SysInfo.Old_Err_Code = ERR_CODE.NO_ORG;
                    _SysInfo.Alarm_Code = ALARM_CODE.NONE;
                    _SysInfo.Old_Alarm_Code = ALARM_CODE.NONE;
                    _SysInfo.Main_Status = MAIN_STATUS.NO_INIT;
                    TowerLampBlink(LAMP_COLOR.TL_YELLOW);
                }
                else if (_SysInfo.Main_Status == MAIN_STATUS.ALARM)
                {
                    _SysInfo.Err_Code = ERR_CODE.NONE;
                    _SysInfo.Old_Err_Code = ERR_CODE.NONE;
                    _SysInfo.Alarm_Code = ALARM_CODE.NONE;
                    _SysInfo.Old_Alarm_Code = ALARM_CODE.NONE;
                    _SysInfo.Main_Status = MAIN_STATUS.READY;
                }
                else
                {
                    _SysInfo.Err_Code = ERR_CODE.NONE;
                    _SysInfo.Old_Err_Code = ERR_CODE.NONE;
                    _SysInfo.Alarm_Code = ALARM_CODE.NONE;
                    _SysInfo.Old_Alarm_Code = ALARM_CODE.NONE;
                }
                _SysInfo.bErrorClear = false;
            }





            switch (nProcessStep[nStepIndex])
            {
                //===============================
                // 시스템 초기화 루틴
                case 100:
                    _SysInfo.nTL_Beep = 1;

                    _SysInfo.Err_Code = ERR_CODE.NO_ORG;
                    _SysInfo.Old_Err_Code = ERR_CODE.NO_ORG;
                    _SysInfo.Alarm_Code = ALARM_CODE.NONE;
                    _SysInfo.Old_Alarm_Code = ALARM_CODE.NONE;
                    _SysInfo.TL_Buzzer = TOWER_LAMP.TL_OFF;
                    _SysInfo.Main_Status = MAIN_STATUS.INIT;


                    for (int i = (int)STATION_LIST.LOADING; i <= (int)STATION_LIST.UNLOADING; i++)
                    {
                        _SysInfo.bStationAutoMode[i] = false;
                    }


                    nProcessStep[nStepIndex]++;
                    break;


                case 101:
                    nProcessStep[nStepIndex] = 110;
                    break;


                case 102:
                    nProcessStep[nStepIndex] = 110;
                    break;

                case 110:
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 5; j++)
                        {
                            _SysInfo.bBoltReady[i, j] = false;
                        }

                    }
                    SetDIOPort(DO.STATION1_STOPPER_DW, false);
                    SetDIOPort(DO.STATION2_STOPPER_DW, false);
                    SetDIOPort(DO.STATION3_STOPPER_DW, false);
                    SetDIOPort(DO.STATION4_STOPPER_DW, false);
                    SetDIOPort(DO.STATION5_STOPPER_DW, false);
                    SetDIOPort(DO.EOL_STOPPER_DW, false);
                    SetDIOPort(DO.HIPOT_STOPPER_DW, false);
                    SetDIOPort(DO.UNDER_CV_STOPPER_DW, false);
                    //SetDIOPort(DO.EOL_SIDE_CONATCT_ON, false);
                    SetDIOPort(DO.HIPOT_PRODUCT_PUSH_ON, false);
                    SetDIOPort(DO.EOL_PRODUCT_PUSH_ON, false);
                    //SetDIOPort(DO.HIPOT_CONTACT_CHECK, false);

                    InitMotion();
                    _SysInfo.bServoErrMonitor = false;
                    for (int i = (int)AXIS.X; i <= (int)AXIS.CAMERA2_Z; i++)
                    {
                        CAXM.AxmMoveEStop(i);
                        CAXM.AxmSignalServoOn(i, 0);
                    }
                    SetDIOPort(DO.LP1_SERVO_ON, false);
                    SetDIOPort(DO.LP3_SERVO_ON, false);
                    tMainTimer[nStepIndex].Start(2500);
                    nProcessStep[nStepIndex]++;
                    break;

                case 111:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    SetDIOPort(DO.LP1_SERVO_ON, true);
                    tMainTimer[nStepIndex].Start(1000);
                    nProcessStep[nStepIndex]++;
                    break;

                case 112:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    SetDIOPort(DO.LP3_SERVO_ON, true);
                    tMainTimer[nStepIndex].Start(2500);
                    nProcessStep[nStepIndex]++;
                    break;


                case 113:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    for (int i = (int)AXIS.X; i <= (int)AXIS.CAMERA2_Z; i++)
                    {
                        CAXM.AxmSignalServoAlarmReset(i, 1);
                    }
                    tMainTimer[nStepIndex].Start(200);
                    nProcessStep[nStepIndex]++;
                    break;




                case 114:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    for (int i = (int)AXIS.X; i <= (int)AXIS.CAMERA2_Z; i++)
                    {
                        CAXM.AxmSignalServoAlarmReset(i, 0);
                    }
                    tMainTimer[nStepIndex].Start(200);
                    nProcessStep[nStepIndex]++;
                    break;


                case 115:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    for (int i = (int)AXIS.X; i <= (int)AXIS.CAMERA2_Z; i++)
                    {
                        if ((i + 1) % 2 == 0)
                        {
                            CAXM.AxmSignalServoOn(i, 1);
                        }

                    }
                    tMainTimer[nStepIndex].Start(200);
                    nProcessStep[nStepIndex]++;
                    break;

                case 116:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    for (int i = (int)AXIS.X; i <= (int)AXIS.CAMERA2_Z; i++)
                    {
                        if ((i + 1) % 2 == 1)
                        {
                            CAXM.AxmSignalServoOn(i, 1);
                        }

                    }
                    tMainTimer[nStepIndex].Start(200);
                    nProcessStep[nStepIndex]++;
                    break;

                case 117:
                    _SysInfo.bServoErrMonitor = true;
                    nProcessStep[nStepIndex]++;
                    break;

                case 118:
                    CAXM.AxmSignalServoOn((int)AXIS.ST3_R, 0);
                    // 프로브 후진부분 주석처리
                    Move(AXIS.HIPOT_1X, -100.0, _Config.dbMotorHomeSpeed);
                    Move(AXIS.HIPOT_2X, -100.0, _Config.dbMotorHomeSpeed);
                    Move(AXIS.EOL_X, -100.0, _Config.dbMotorHomeSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 119:
                    if (!MotionDone(AXIS.HIPOT_1X) || !MotionDone(AXIS.HIPOT_2X) || !MotionDone(AXIS.EOL_X)) { break; }
                    nProcessStep[nStepIndex]++;
                    break;

                case 120:
                    _SysInfo.nMotorCount = 0;
                    _Search_ALL.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.CAMERA1_Z;
                    _Search_ALL.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.CAMERA2_Z;
                    _Search_ALL.nAxisSize = _SysInfo.nMotorCount;
                    nProcessStep[(int)PROC_LIST.SUB_HOME_SEARCH] = 0;
                    nProcessStep[nStepIndex]++;
                    break;

                case 121:
                    if (SUB_SEARCH_HOME(true) == -1)
                    {
                        _SysInfo.nMotorSearchErrCnt = 0;
                        for (int i = 0; i < _Search_ALL.nAxisSize; i++)
                        {
                            if (_Search_ALL.bResult[i])
                            {
                                AppendLogMsg(String.Format("{0} 축 홈서치 완료", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.INFO);
                            }
                            else
                            {
                                AppendLogMsg(String.Format("{0} 축 홈서치 실패", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR);
                                _SysInfo.nMotorSearchErrCnt++;
                            }

                        }

                        if (_SysInfo.nMotorSearchErrCnt > 0) nProcessStep[nStepIndex] = 10000;
                        else nProcessStep[nStepIndex] = 122;
                    }
                    break;

                case 122:
                    // 상하컨텍을 사용하지 않을경우 X축 먼저 후진
                    // 상하컨텍을 사용할경우 Z축 먼저 상승
                    if (!_ModelInfo.bUseHipot1UpDwContact)
                    {
                        Move(AXIS.HIPOT_1X, -100.0, _Config.dbMotorHomeSpeed);
                    }
                    else
                    {
                        Move(AXIS.HIPOT_1Z, -10.0, _Config.dbMotorHomeSpeed);
                    }

                    Move(AXIS.HIPOT_2X, -100.0, _Config.dbMotorHomeSpeed);
                    Move(AXIS.EOL_X, -100.0, _Config.dbMotorHomeSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 123:
                    if (!MotionDone(AXIS.HIPOT_1X) || !MotionDone(AXIS.HIPOT_2X) || !MotionDone(AXIS.EOL_X) || !MotionDone(AXIS.HIPOT_1Z)) { break; }
                    nProcessStep[nStepIndex] = 125;
                    break;

                case 125:
                    _SysInfo.nMotorCount = 0;
                    //if(_Config.bUseBoltSupply)
                    //{
                    //    _Search_ALL.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.BOLT_R1;
                    //    _Search_ALL.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.BOLT_R2;
                    //    _Search_ALL.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.BOLT_R3;
                    //    _Search_ALL.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.BOLT_R4;
                    //}

                    _Search_ALL.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.CAMERA1_X;
                    _Search_ALL.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.CAMERA1_Y;
                    _Search_ALL.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.CAMERA2_X;
                    _Search_ALL.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.CAMERA2_Y;

                    _Search_ALL.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.HIPOT_1Y;
                    _Search_ALL.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.HIPOT_2Y;
                    _Search_ALL.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.HIPOT_1Z;
                    _Search_ALL.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.HIPOT_2Z;
                    _Search_ALL.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.EOL_Y;
                    _Search_ALL.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.EOL_Z;
                    //if (!_Config.bUseReworkLineMode)
                    //{
                    _Search_ALL.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.Z;
                    //}

                    _Search_ALL.nAxisSize = _SysInfo.nMotorCount;
                    nProcessStep[(int)PROC_LIST.SUB_HOME_SEARCH] = 0;
                    nProcessStep[nStepIndex]++;
                    break;

                case 126:
                    if (SUB_SEARCH_HOME(true) == -1)
                    {
                        _SysInfo.nMotorSearchErrCnt = 0;
                        for (int i = 0; i < _Search_ALL.nAxisSize; i++)
                        {
                            if (_Search_ALL.bResult[i])
                            {
                                AppendLogMsg(String.Format("{0} 축 홈서치 완료", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.INFO);
                            }
                            else
                            {
                                AppendLogMsg(String.Format("{0} 축 홈서치 실패", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR);
                                _SysInfo.nMotorSearchErrCnt++;
                            }

                        }

                        if (_SysInfo.nMotorSearchErrCnt > 0) nProcessStep[nStepIndex] = 10000;
                        else nProcessStep[nStepIndex]++;
                    }
                    break;


                case 127:
                    _SysInfo.nMotorCount = 0;
                    _Search_ALL.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.HIPOT_1X;
                    _Search_ALL.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.HIPOT_2X;
                    _Search_ALL.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.EOL_X;
                    //if (!_Config.bUseReworkLineMode)
                    //{
                        _Search_ALL.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.R;
                    //}
                    _Search_ALL.nAxisSize = _SysInfo.nMotorCount;
                    nProcessStep[(int)PROC_LIST.SUB_HOME_SEARCH] = 0;
                    nProcessStep[nStepIndex]++;
                    break;



                case 128:
                    if (SUB_SEARCH_HOME(true) == -1)
                    {
                        _SysInfo.nMotorSearchErrCnt = 0;
                        for (int i = 0; i < _Search_ALL.nAxisSize; i++)
                        {
                            if (_Search_ALL.bResult[i])
                            {
                                AppendLogMsg(String.Format("{0} 축 홈서치 완료", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.INFO);
                            }
                            else
                            {
                                AppendLogMsg(String.Format("{0} 축 홈서치 실패", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR);
                                _SysInfo.nMotorSearchErrCnt++;
                            }

                        }

                        if (_SysInfo.nMotorSearchErrCnt > 0) nProcessStep[nStepIndex] = 10000;
                        else nProcessStep[nStepIndex]++;
                    }
                    break;

                case 129:
                    if (!MotionDone(AXIS.R)) { break; }


                    nProcessStep[nStepIndex]++;
                    break;

                case 130:
                    if (!MotionDone(AXIS.R)) { break; }


                    nProcessStep[nStepIndex]++;
                    break;

                case 131:
                    //if (_Config.bUseReworkLineMode)
                    //{
                    //    nProcessStep[nStepIndex] = 130;
                    //    break;
                    //}

                    _SysInfo.nMotorCount = 0;
                    _Search_ALL.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.X;
                    _Search_ALL.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.Y;
                    _Search_ALL.nAxisSize = _SysInfo.nMotorCount;
                    nProcessStep[(int)PROC_LIST.SUB_HOME_SEARCH] = 0;
                    nProcessStep[nStepIndex]++;
                    break;

                case 132:
                    if (SUB_SEARCH_HOME(true) == -1)
                    {
                        _SysInfo.nMotorSearchErrCnt = 0;
                        for (int i = 0; i < _Search_ALL.nAxisSize; i++)
                        {
                            if (_Search_ALL.bResult[i])
                            {
                                AppendLogMsg(String.Format("{0} 축 홈서치 완료", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.INFO);
                            }
                            else
                            {
                                AppendLogMsg(String.Format("{0} 축 홈서치 실패", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR);
                                _SysInfo.nMotorSearchErrCnt++;
                            }

                        }

                        if (_SysInfo.nMotorSearchErrCnt > 0) nProcessStep[nStepIndex] = 10000;
                        else nProcessStep[nStepIndex] = 133;
                    }
                    break;




                case 133:
                    CAXM.AxmSignalSetSoftLimit((int)AXIS.EOL_Y, (int)AXT_USE.ENABLE, (int)AXT_MOTION_STOPMODE.EMERGENCY_STOP, (int)AXT_MOTION_SELECTION.COMMAND,
                        0.0, _MotorAxisInfo[(int)AXIS.EOL_Y].dbPositiveLimit);

                    CAXM.AxmSignalSetSoftLimit((int)AXIS.HIPOT_1Y, (int)AXT_USE.ENABLE, (int)AXT_MOTION_STOPMODE.EMERGENCY_STOP, (int)AXT_MOTION_SELECTION.COMMAND,
                         0.0, _MotorAxisInfo[(int)AXIS.HIPOT_1Y].dbPositiveLimit);

                    CAXM.AxmSignalSetSoftLimit((int)AXIS.HIPOT_2Y, (int)AXT_USE.ENABLE, (int)AXT_MOTION_STOPMODE.EMERGENCY_STOP, (int)AXT_MOTION_SELECTION.COMMAND,
                         0.0, _MotorAxisInfo[(int)AXIS.HIPOT_2Y].dbPositiveLimit);

                    AxmUserSetSoftwareLimitEnable(AXIS.EOL_Y, true, true);
                    AxmUserSetSoftwareLimitEnable(AXIS.HIPOT_1Y, true, true);
                    AxmUserSetSoftwareLimitEnable(AXIS.HIPOT_2Y, true, true);

                    AxmUserSetSoftwareLimitPosition(AXIS.EOL_Y, _MotorAxisInfo[(int)AXIS.EOL_Y].dbNegativeLimit, _MotorAxisInfo[(int)AXIS.EOL_Y].dbPositiveLimit);
                    AxmUserSetSoftwareLimitPosition(AXIS.HIPOT_1Y, _MotorAxisInfo[(int)AXIS.HIPOT_1Y].dbNegativeLimit, _MotorAxisInfo[(int)AXIS.HIPOT_1Y].dbPositiveLimit);
                    AxmUserSetSoftwareLimitPosition(AXIS.HIPOT_2Y, _MotorAxisInfo[(int)AXIS.HIPOT_2Y].dbNegativeLimit, _MotorAxisInfo[(int)AXIS.HIPOT_2Y].dbPositiveLimit);

                    _SysInfo.Alarm_Code = ALARM_CODE.NONE;
                    _SysInfo.Old_Err_Code = ERR_CODE.NONE;
                    _SysInfo.Err_Code = ERR_CODE.NONE;
                    _SysInfo.Main_Status = MAIN_STATUS.READY;
                    _SysInfo.nTL_Beep = 2;
                    nProcessStep[nStepIndex] = 200;
                    break;







                case 200:
                    break;


                case 10000:
                    _SysInfo.Main_Status = MAIN_STATUS.SYSTEM_ERR;
                    _SysInfo.TL_Buzzer = TOWER_LAMP.TL_ON;
                    nProcessStep[nStepIndex] = 0;
                    break;
            }


        }



        static void WORK_INLIFT_PROC()
        {

            int nStepIndex = (int)PROC_LIST.INLIFT;


            if (!_SysInfo.bStationAutoMode[(int)STATION_LIST.IN_LIFT])
            {

                nProcessStep[nStepIndex] = 0; _SysInfo.bLoadingReadySw = false; _SysInfo.bInLiftReady = false; _SysInfo.bLiftOutComplated = false;



                if (_tSTCycleTimer[(int)STATION_LIST.IN_LIFT].IsRunning)
                {
                    _tSTCycleTimer[(int)STATION_LIST.IN_LIFT].Stop();
                    _tSTCycleEndTime[(int)STATION_LIST.IN_LIFT] = DateTime.Now;
                    SaveStationTactTime(STATION_LIST.IN_LIFT, _tSTCycleStartTime[(int)STATION_LIST.IN_LIFT], _tSTCycleEndTime[(int)STATION_LIST.IN_LIFT], 1);
                }

                return;

            } // 수동모드

            switch (nProcessStep[nStepIndex])
            {
                case 0:
                    // 작업 완료후 정지면
                    if (_SysInfo.bAutoCycleStop)
                    {
                        nProcessStep[nStepIndex] = 9000;
                        break;
                    }

                    // 돌려야할 상황 아니면 LIFT/CV OFF 스토퍼 상승
                    SetDIOPort(DO.INLIFT_CV_ON, false);
                    SetDIOPort(DO.INLIFT_CV_REV, false);
                    SetDIOPort(DO.UNDER_CV_STOPPER_DW, false);

                    if (GetDIOPort(DI.INLIFT_UP) && GetDIOPort(DI.INLIFT_PALLET_END) && (!_SysInfo.bLoadingComplated && !_Config.bUseReworkLineMode))
                    {
                        //리프트가 상승상태고 파레트가 있고 로딩완료가 아니라면
                        if (GetDIOPort(DI.INLIFT_PALLET_UP))
                        {
                            // 그리고 얼라인 리프트가 상승되어있다면
                            nProcessStep[nStepIndex] = 200;
                        }
                        else
                        {
                            // 상승 상태가 아니라면 상승시킴
                            _SysInfo.bInLiftReady = false;
                            nProcessStep[nStepIndex] = 300;
                        }
                    }
                    else if (GetDIOPort(DI.INLIFT_UP) && GetDIOPort(DI.INLIFT_PALLET_END) && (_SysInfo.bLoadingComplated || _Config.bUseReworkLineMode) && _SysInfo.bLoadingReadySw)
                    {
                        // 리프트 업 파레트 있는 상태인데 로딩 완료 플래그가 들어오고 로딩 스위치가 눌렸다면 배출함
                        nProcessStep[nStepIndex] = 400;

                    }
                    else if (GetDIOPort(DI.INLIFT_UP) && GetDIOPort(DI.INLIFT_PALLET_END) && (_SysInfo.bLoadingComplated || _Config.bUseReworkLineMode) && !_SysInfo.bLoadingReadySw)
                    {
                        if (_Config.bUseReworkLineMode)
                        {
                            //리프트가 상승상태고 파레트가 있고 로딩완료가 아니라면
                            if (GetDIOPort(DI.INLIFT_PALLET_UP))
                            {
                                // 그리고 얼라인 리프트가 상승되어있다면
                                nProcessStep[nStepIndex] = 200;
                            }
                            else
                            {
                                // 상승 상태가 아니라면 상승시킴
                                _SysInfo.bInLiftReady = false;
                                nProcessStep[nStepIndex] = 300;
                            }
                        }
                        else
                        {
                            nProcessStep[nStepIndex] = 200;
                        }

                    }
                    else if (GetDIOPort(DI.INLIFT_UP) && !GetDIOPort(DI.INLIFT_PALLET_END) && !GetDIOPort(DI.INLIFT_PALLET_SLOWPOINT))
                    {
                        //리프트가 상승상태 파레트가 없다면 파레트를 가지러감
                        _SysInfo.bInLiftReady = false;
                        nProcessStep[nStepIndex] = 800;

                    }
                    else if (GetDIOPort(DI.INLIFT_DW) && GetDIOPort(DI.INLIFT_PALLET_END))
                    {
                        //리프트가 하강 상태고 파레트가 있다면
                        _SysInfo.bInLiftReady = false;
                        nProcessStep[nStepIndex] = 900;
                    }
                    else if (GetDIOPort(DI.INLIFT_DW) && !GetDIOPort(DI.INLIFT_PALLET_END) && !GetDIOPort(DI.INLIFT_PALLET_SLOWPOINT))
                    {
                        //리프트 하강 사태고 파레트가 없다면
                        _SysInfo.bInLiftReady = false;
                        nProcessStep[nStepIndex] = 1000;
                    }
                    break;





                // 
                case 200:
                    _SysInfo.bInLiftReady = true;
                    nProcessStep[nStepIndex]++;
                    break;

                case 201:
                    if (_SysInfo.bLoadingComplated || _Config.bUseReworkLineMode)
                    {
                        nProcessStep[nStepIndex] = 0;
                    }
                    break;


                case 300:
                    SetDIOPort(DO.INLIFT_PALLET_UP, true);
                    SetDIOPort(DO.INLIFT_PALLET_DW, false);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 301:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        if (!GetDIOPort(DI.INLIFT_PALLET_UP)) { AppendTimeOutMsg(DI.INLIFT_PALLET_UP); }
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }

                    if (GetDIOPort(DI.INLIFT_PALLET_UP))
                    {
                        // 파레트가 업돼었을때 제품감지가 안된다면
                        if (!GetDIOPort(DI.INLIFT_PALLET_END))
                        {
                            // 상승후 파레트가 없다면 알람
                            AppendLogMsg("PALLET 感知不良", LOG_TYPE.ERROR);
                            nProcessStep[nStepIndex] = 10000;
                        }
                        else
                        {
                            nProcessStep[nStepIndex]++;
                        }
                    }
                    break;

                case 302:
                    if (_Config.bUseAutoLoadingReadySw)
                    {
                        if (GetDIOPort(DI.INLIFT_PRODUCT_BASEPLATE))
                        {
                            _SysInfo.bLoadingReadySw = true;

                            if (GetDIOPort(DI.INLIFT_PRODUCT_CMA))
                            {
                                _SysInfo.bInLiftReady = true;
                                _SysInfo.bLoadingComplated = true;
                            }
                        }
                    }
                    nProcessStep[nStepIndex] = 0;
                    break;


                // 배출 동작
                case 400:
                    tMainTimer[nStepIndex].Start(3000);
                    nProcessStep[nStepIndex]++;
                    break;

                case 401:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }

                    if (!GetDIOPort(DI.STATION1_PALLET) && GetDIOPort(DI.STATION1_PALLET_DW) && _SysInfo.bStationAutoMode[(int)STATION_LIST.ST1])
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 402:
                    tCVTimer.Start(_Config.nCVAutoStopTime);
                    SetDIOPort(DO.INLIFT_PALLET_DW, true);
                    SetDIOPort(DO.INLIFT_PALLET_UP, false);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 403:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        if (!GetDIOPort(DI.INLIFT_PALLET_DW)) { AppendTimeOutMsg(DI.INLIFT_PALLET_DW); }
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }

                    if (GetDIOPort(DI.INLIFT_PALLET_DW))
                    {
                        SetDIOPort(DO.INLIFT_CV_FAST, true);
                        SetDIOPort(DO.INLIFT_CV_SLOW, false);
                        SetDIOPort(DO.INLIFT_CV_REV, false);
                        SetDIOPort(DO.INLIFT_CV_ON, true);
                        tMainTimer[nStepIndex].Start(20000);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 404:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("INLIFT 产品转移超时", LOG_TYPE.ERROR);
                        SetDIOPort(DO.INLIFT_CV_FAST, false);
                        SetDIOPort(DO.INLIFT_CV_SLOW, false);
                        SetDIOPort(DO.INLIFT_CV_REV, false);
                        SetDIOPort(DO.INLIFT_CV_ON, false);

                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }

                    if (GetDIOPort(DI.STATION1_PALLET))
                    {
                        tMainTimer[nStepIndex].Start(20000);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 405:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("INLIFT 产品转移超时", LOG_TYPE.ERROR);
                        SetDIOPort(DO.INLIFT_CV_FAST, false);
                        SetDIOPort(DO.INLIFT_CV_SLOW, false);
                        SetDIOPort(DO.INLIFT_CV_REV, false);
                        SetDIOPort(DO.INLIFT_CV_ON, false);

                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }

                    if (GetDIOPort(DI.STATION1_PALLET) && !GetDIOPort(DI.BETWEEN_INLIFT_CV))
                    {
                        _tSTCycleEndTime[(int)STATION_LIST.IN_LIFT] = DateTime.Now;
                        _tSTCycleTimer[(int)STATION_LIST.IN_LIFT].Stop();
                        SaveStationTactTime(STATION_LIST.IN_LIFT, _tSTCycleStartTime[(int)STATION_LIST.IN_LIFT], _tSTCycleEndTime[(int)STATION_LIST.IN_LIFT], 0);

                        SetDIOPort(DO.INLIFT_CV_FAST, false);
                        SetDIOPort(DO.INLIFT_CV_SLOW, false);
                        SetDIOPort(DO.INLIFT_CV_REV, false);
                        SetDIOPort(DO.INLIFT_CV_ON, false);
                        _SysInfo.bLiftOutComplated = true;
                        nProcessStep[nStepIndex]++;
                    }
                    else if (!GetDIOPort(DI.STATION1_PALLET))
                    {
                        nProcessStep[nStepIndex] = 404;
                    }
                    break;

                case 406:
                    if (_SysInfo.bAutoCycleStop)
                    {
                        nProcessStep[nStepIndex] = 9000;
                    }

                    if (!_SysInfo.bLiftOutComplated || _Config.bUseReworkLineMode)
                    {
                        nProcessStep[nStepIndex] = 0;
                    }
                    break;

                // 파레트가 없으므로 하강시킴
                case 800:
                    SetDIOPort(DO.INLIFT_UP, false);
                    SetDIOPort(DO.INLIFT_DW, true);


                    tMainTimer[nStepIndex].Start(_Config.nLiftTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 801:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        if (!GetDIOPort(DI.INLIFT_DW)) { AppendTimeOutMsg(DI.INLIFT_DW); }
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }

                    if (GetDIOPort(DI.INLIFT_DW))
                    {
                        tMainTimer[nStepIndex].Start(_Config.nLiftCylStabilTime);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 802:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    nProcessStep[nStepIndex] = 0;
                    break;



                // 리프트 하강상태 파레트 감지되면 리프트 상승
                case 900: // 리프트 상승시키기 전 안전센서에 파레트가 걸려있는지 확인한다
                    if (GetDIOPort(DI.BETWEEN_INLIFT_CV))
                    {
                        // 제품이 있으면 알람
                        AppendLogMsg("Main C/V <-> INLIFT 有产品", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 10000;
                    }
                    else
                    {
                        nProcessStep[nStepIndex] = 910; // 없을경우 상승
                    }
                    break;

                case 910:
                    SetDIOPort(DO.INLIFT_UP, true);
                    SetDIOPort(DO.INLIFT_DW, false);

                    // 추가된 부분
                    SetDIOPort(DO.INLIFT_PALLET_UP, true);
                    SetDIOPort(DO.INLIFT_PALLET_DW, false);
                    ////////

                    tMainTimer[nStepIndex].Start(_Config.nLiftTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 911:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        if (!GetDIOPort(DI.INLIFT_UP)) { AppendTimeOutMsg(DI.INLIFT_UP); }
                        nProcessStep[nStepIndex] = 10000;
                    }

                    if (GetDIOPort(DI.INLIFT_UP))
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 912:
                    if (!GetDIOPort(DI.INLIFT_PALLET_END))
                    {
                        // 상승후 파레트가 없다면 알람
                        AppendLogMsg("PALLET 感知不良", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 10000;
                    }
                    else
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                // 추가된 부분
                case 913:
                    SetDIOPort(DO.INLIFT_PALLET_UP, true);
                    SetDIOPort(DO.INLIFT_PALLET_DW, false);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 914:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        if (!GetDIOPort(DI.INLIFT_PALLET_UP)) { AppendTimeOutMsg(DI.INLIFT_PALLET_UP); }
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }

                    if (GetDIOPort(DI.INLIFT_PALLET_UP))
                    {
                        // 파레트가 업돼었을때 제품감지가 안된다면
                        if (!GetDIOPort(DI.INLIFT_PALLET_END))
                        {
                            // 상승후 파레트가 없다면 알람
                            AppendLogMsg("PALLET 感知不良", LOG_TYPE.ERROR);
                            nProcessStep[nStepIndex] = 10000;
                        }
                        else
                        {
                            nProcessStep[nStepIndex]++;
                        }
                    }
                    break;

                case 915:
                    if (_Config.bUseAutoLoadingReadySw)
                    {
                        if (GetDIOPort(DI.INLIFT_PRODUCT_BASEPLATE))
                        {
                            _SysInfo.bLoadingReadySw = true;

                            if (GetDIOPort(DI.INLIFT_PRODUCT_CMA))
                            {
                                _SysInfo.bInLiftReady = true;
                                _SysInfo.bLoadingComplated = true;
                            }
                        }
                    }
                    nProcessStep[nStepIndex] = 0;
                    break;






                // 파레트 요청 
                case 1000:
                    SetDIOPort(DO.INLIFT_PALLET_DW, true);
                    SetDIOPort(DO.INLIFT_PALLET_UP, false);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 1001:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        if (!GetDIOPort(DI.INLIFT_PALLET_DW)) { AppendTimeOutMsg(DI.INLIFT_PALLET_DW); }
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }

                    if (GetDIOPort(DI.INLIFT_PALLET_DW))
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 1002:
                    // 파레트를 하강시켰는데 파레트 감지가 된다면 0번 스텝으로
                    if (GetDIOPort(DI.INLIFT_PALLET_END))    // 종단부 파레트 감지 확인
                    {
                        nProcessStep[nStepIndex] = 0;           // 0번 -> 상승스텝으로
                        break;
                    }

                    tMainTimer[nStepIndex].Start(1000);
                    nProcessStep[nStepIndex]++;
                    break;

                case 1003:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }

                    if (GetDIOPort(DI.UNDER_CV_PALLET_END))
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                // 파레트 가져옴
                case 1004:

                    SetDIOPort(DO.UNDER_CV_STOPPER_DW, true);
                    tMainTimer[nStepIndex].Start(200);
                    nProcessStep[nStepIndex]++;
                    break;

                case 1005:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    SetDIOPort(DO.INLIFT_CV_FAST, true);
                    SetDIOPort(DO.INLIFT_CV_SLOW, false);
                    SetDIOPort(DO.INLIFT_CV_REV, true);
                    SetDIOPort(DO.INLIFT_CV_ON, false);
                    tMainTimer[nStepIndex].Start(1000);
                    nProcessStep[nStepIndex]++;
                    break;

                case 1006:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    SetDIOPort(DO.UNDER_CV_STOPPER_DW, false);
                    nProcessStep[nStepIndex]++;
                    break;

                case 1007:
                    if (GetDIOPort(DI.INLIFT_PALLET_SLOWPOINT) || GetDIOPort(DI.INLIFT_PALLET_END))
                    {
                        SetDIOPort(DO.INLIFT_CV_FAST, false);
                        SetDIOPort(DO.INLIFT_CV_SLOW, true);

                        tMainTimer[nStepIndex].Start(20000);        // 20초 타임아웃

                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 1008:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("INLIFT 产品转移超时", LOG_TYPE.ERROR);
                        SetDIOPort(DO.INLIFT_CV_FAST, false);
                        SetDIOPort(DO.INLIFT_CV_SLOW, false);
                        SetDIOPort(DO.INLIFT_CV_REV, false);
                        SetDIOPort(DO.INLIFT_CV_ON, false);

                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }
                    if (GetDIOPort(DI.INLIFT_PALLET_END) && !GetDIOPort(DI.BETWEEN_INLIFT_CV))
                    {
                        // C/V 일정시간 더돌림
                        tMainTimer[nStepIndex].Start(_Config.nLiftInTime);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 1009:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    SetDIOPort(DO.INLIFT_CV_FAST, false);
                    SetDIOPort(DO.INLIFT_CV_SLOW, false);
                    SetDIOPort(DO.INLIFT_CV_REV, false);
                    SetDIOPort(DO.INLIFT_CV_ON, false);
                    _tSTCycleTimer[(int)STATION_LIST.IN_LIFT].Restart();
                    _tSTCycleStartTime[(int)STATION_LIST.IN_LIFT] = DateTime.Now;

                    // 원점으로 돌아가지 않고 상승 루틴까지 포함해서 돌림
                    // nProcessStep[nStepIndex] = 0;

                    nProcessStep[nStepIndex] = 900;
                    break;




                case 9000:
                    _SysInfo.bStationAutoMode[(int)STATION_LIST.IN_LIFT] = false;
                    break;

                case 10000:
                    nProcessStep[nStepIndex] = 9000;
                    _SysInfo.TL_Buzzer = TOWER_LAMP.TL_ON;
                    break;

            }

        }




        //===========================================================
        //====== STATION 1,2,3,4,5===================================
        static void WorkLockingProcess(int nStation)
        {
            int nStepIndex = (int)PROC_LIST.ST1 + nStation;

            if (nStation == 0)
            {
                SUB_BARCODE_READ();
                SUB_ETCBCD_READ();
                SUB_ST1_BARCODE_READ();
            }

            if (!_SysInfo.bStationAutoMode[(int)STATION_LIST.ST1 + nStation])
            {

                nProcessStep[nStepIndex] = 0;

                //if (nStation == 2 && (_ModelInfo.bUseTPCRobot || _ModelInfo.bUseST3Model2))
                //{
                //    _SysInfo.strST3NowWorkModel = "";
                //    _SysInfo.bST3Work2Finish = false;
                //}


                if (_tSTCycleTimer[(int)STATION_LIST.ST1 + nStation].IsRunning)
                {
                    _tSTCycleTimer[(int)STATION_LIST.ST1 + nStation].Stop();
                    _tSTCycleEndTime[(int)STATION_LIST.ST1 + nStation] = DateTime.Now;
                    SaveStationTactTime(STATION_LIST.ST1 + nStation, _tSTCycleStartTime[(int)STATION_LIST.ST1 + nStation], _tSTCycleEndTime[(int)STATION_LIST.ST1 + nStation], 1);
                }
                return;
            } // 수동모드




            #region Station 별 IO 할당
            DI _in_Lift_Up = new DI();
            DI _in_Lift_Dw = new DI();
            DI _in_Pallet = new DI();
            DI _in_Pass_SW = new DI();
            DI _in_Pallet_Center = new DI();
            DI _Next_Pallet = new DI();
            DI _Next_Lift_DW = new DI();

            DO _out_Lift_Up = new DO();
            DO _out_Lift_Dw = new DO();
            DO _out_Stopper_Open = new DO();
            DO _out_Count_Clear = new DO();
            switch (nStation)
            {
                case 0:
                    _in_Lift_Up = DI.STATION1_PALLET_UP;
                    _in_Lift_Dw = DI.STATION1_PALLET_DW;
                    _in_Pallet = DI.STATION1_PALLET;
                    _in_Pass_SW = DI.STATION1_FINISH_SW;
                    _in_Pallet_Center = DI.STATION1_CENTER;
                    _Next_Pallet = DI.STATION2_PALLET;
                    _Next_Lift_DW = DI.STATION2_PALLET_DW;

                    _out_Lift_Up = DO.STATION1_PALLET_UP;
                    _out_Lift_Dw = DO.STATION1_PALLET_DW;
                    _out_Stopper_Open = DO.STATION1_STOPPER_DW;
                    break;

                case 1:
                    _in_Lift_Up = DI.STATION2_PALLET_UP;
                    _in_Lift_Dw = DI.STATION2_PALLET_DW;
                    _in_Pallet = DI.STATION2_PALLET;
                    _in_Pass_SW = DI.STATION2_FINISH_SW;
                    _in_Pallet_Center = DI.STATION2_CENTER;
                    _Next_Pallet = DI.STATION3_PALLET;
                    _Next_Lift_DW = DI.STATION3_PALLET_DW;

                    _out_Lift_Up = DO.STATION2_PALLET_UP;
                    _out_Lift_Dw = DO.STATION2_PALLET_DW;
                    _out_Stopper_Open = DO.STATION2_STOPPER_DW;
                    break;

                case 2:
                    _in_Lift_Up = DI.STATION3_PALLET_UP;
                    _in_Lift_Dw = DI.STATION3_PALLET_DW;
                    _in_Pallet = DI.STATION3_PALLET;
                    _in_Pass_SW = DI.STATION3_FINISH_SW;
                    _in_Pallet_Center = DI.STATION3_CENTER;
                    _Next_Pallet = DI.STATION4_PALLET;
                    _Next_Lift_DW = DI.STATION4_PALLET_DW;

                    _out_Lift_Up = DO.STATION3_PALLET_UP;
                    _out_Lift_Dw = DO.STATION3_PALLET_DW;
                    _out_Stopper_Open = DO.STATION3_STOPPER_DW;
                    break;

                case 3:
                    _in_Lift_Up = DI.STATION4_PALLET_UP;
                    _in_Lift_Dw = DI.STATION4_PALLET_DW;
                    _in_Pallet = DI.STATION4_PALLET;
                    _in_Pass_SW = DI.STATION4_FINISH_SW;
                    _in_Pallet_Center = DI.STATION4_CENTER;
                    _Next_Pallet = DI.STATION5_PALLET;
                    _Next_Lift_DW = DI.STATION5_PALLET_DW;

                    _out_Lift_Up = DO.STATION4_PALLET_UP;
                    _out_Lift_Dw = DO.STATION4_PALLET_DW;
                    _out_Stopper_Open = DO.STATION4_STOPPER_DW;
                    break;

                case 4:
                    _in_Lift_Up = DI.STATION5_PALLET_UP;
                    _in_Lift_Dw = DI.STATION5_PALLET_DW;
                    _in_Pallet = DI.STATION5_PALLET;
                    _in_Pass_SW = DI.STATION5_FINISH_SW;
                    _in_Pallet_Center = DI.STATION5_CENTER;
                    _Next_Pallet = DI.HIPOT_PALLET;
                    _Next_Lift_DW = DI.HIPOT_PALLET_DW;

                    _out_Lift_Up = DO.STATION5_PALLET_UP;
                    _out_Lift_Dw = DO.STATION5_PALLET_DW;
                    _out_Stopper_Open = DO.STATION5_STOPPER_DW;
                    break;


            }
            #endregion

            //===== FOOT SW 동작
            //if(nStation == 2 && (_ModelInfo.bUseTPCRobot || _ModelInfo.bUseST3Model2 ))
            //{
            //    // TPC 로봇을 사용하고 3번 스테이션인 경우 풋스위치 동작을 하지 않는다
            //    // 너트러너 동작도 하지 않는다
            //}
            //else
            //{
            //    SUB_FOOT_SW(nStation);
            //    SUB_TITE_PROCESS(nStation);
            //}


            SUB_FOOT_SW(nStation);
            

            //===== 리프트 관련 프로세스
            switch (nProcessStep[nStepIndex])
            {


                case 0:
                    _SysInfo.nPsetOldIndex[nStation] = 0;           // Old PSet 을 Clear 하여 스케쥴 재할당 가능토록 변경
                    if (_ModelInfo.bUseScanSTTester && nStation + 1 >= _ModelInfo.nBCDScanStation && (GetDIOPort(_in_Pallet) || GetDIOPort(_in_Lift_Up)))
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    else
                    {
                        nProcessStep[nStepIndex] = 50;
                    }

                    break;

                case 1:
                    _SysInfo.eChargeStartInfo[nStation] = START_INFO.READY;
                    _mainform.BeginInvoke(new Action(() => _mainform.ViewTesterStartInfo(nStation)));
                    nProcessStep[nStepIndex]++;
                    break;

                case 2:
                    if (_SysInfo.eChargeStartInfo[nStation] == START_INFO.OK)
                    {
                        nProcessStep[nStepIndex] = 50;
                    }
                    else if (_SysInfo.eChargeStartInfo[nStation] == START_INFO.CANCEL)
                    {
                        nProcessStep[nStepIndex] = 9000;
                    }
                    break;

                case 50:
                    // 작업 완료후 정지면
                    if (_SysInfo.bAutoCycleStop)
                    {
                        nProcessStep[nStepIndex] = 9000;
                        break;
                    }
                    // 일반적인 상황에선 스토퍼 상승상태 유지
                    SetDIOPort(_out_Stopper_Open, false);

                    // 리프트가 하강 상태라면
                    if (GetDIOPort(_in_Lift_Dw))
                    {
                        _SysInfo.bTite_Ing[nStation] = false;
                        if (!GetDIOPort(_in_Pallet))
                        {
                            //nProcessStep[nStepIndex] = 100;
                        }
                        else
                        {
                            nProcessStep[nStepIndex] = 150;
                        }
                    }
                    // 리프트가 상승 상태
                    else if (GetDIOPort(_in_Lift_Up))
                    {
                        //if (!_SysInfo.bAlive)
                        //{
                        //    AppendLogMsg(String.Format("Station #{0} - {1}", nStation + 1, OutputLogMsg(OutPutMessage.MASTER_PC_NG)), LOG_TYPE.ERROR);
                        //    nProcessStep[nStepIndex] = 10000;
                        //    break;
                        //}

                        _SysInfo.bTite_Ing[nStation] = true;
                         //정위치 인데 파레트 감지가 안된다면
                        if (!GetDIOPort(_in_Pallet) && GetDIOPort(_in_Pallet_Center))
                        {
                            nProcessStep[nStepIndex] = 200;
                        }
                        // 그외 상황에선 체결작업 수행함
                        else
                        {
                        //if (!_tSTCycleTimer[(int)STATION_LIST.ST1 + nStation].IsRunning)
                        //{
                        //    _tSTCycleTimer[(int)STATION_LIST.ST1 + nStation].Restart();
                        //    _tSTCycleStartTime[(int)STATION_LIST.ST1 + nStation] = DateTime.Now; 
                            nProcessStep[nStepIndex] = 300;
                        }
                       
                        //}
                    }
                    break;



                // 리프트가 하강상태고 파레트가 감지가 안된다면
                // 전단 장비에 Pallet Call 함
                case 100:
                    tMainTimer[nStepIndex].Start(3000);
                    _SysInfo.bPrePalletCall[(int)STATION_LIST.ST1 + nStation] = true;   // 파레트 Call 플래그를 듬
                    nProcessStep[nStepIndex]++;
                    break;

                case 101:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        _SysInfo.bPrePalletCall[(int)STATION_LIST.ST1 + nStation] = false;
                        nProcessStep[nStepIndex] = 50;
                    }

                    // 전단장비에서 배출한다는 시그널이 들어온다면
                    if (_SysInfo.bNextPalletOut[(int)STATION_LIST.ST1 + nStation - 1])
                    {
                        _SysInfo.bNextPalletOut[(int)STATION_LIST.ST1 + nStation - 1] = false;
                        _SysInfo.bPrePalletCall[(int)STATION_LIST.ST1 + nStation] = false;
                        nProcessStep[nStepIndex] = 110;
                    }
                    break;

                // 파레트 들어올때까지 대기
                case 110:
                    if (_SysInfo.bAutoCycleStop) // 검사중 정지가 된다면
                    {
                        nProcessStep[nStepIndex] = 9000;
                        break;
                    }

                    if (GetDIOPort(_in_Pallet))
                    {
                        nProcessStep[nStepIndex] = 50;
                    }
                    break;

                // =========================================
                // 리프트가 하강상태
                // 파레트 투입된다면 리프트 상승
                case 150:
                    tMainTimer[nStepIndex].Start(1000);
                    nProcessStep[nStepIndex]++;
                    break;

                case 151:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 50;
                        break;
                    }

                    // 파레트가 들어온다면
                    if (GetDIOPort(_in_Pallet))
                    {
                        tMainTimer[nStepIndex].Start(2000); // 2초간 더 대기
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 152:
                    if (GetDIOPort(_in_Pallet) && tMainTimer[nStepIndex].Verify())
                    {

                        // 스킵모드 바이패스 전환 -임시- 2017.09.13
                        if (_ModelInfo.bLockingStationSkip[nStation])
                        {
                            nProcessStep[nStepIndex] = 170;
                            break;
                        }


                        // 바이패스 작업
                        if (_ModelInfo.bUseScanSTTester && !_SysInfo.bScanSTTestOKNG[(int)STATION_LIST.ST1 + nStation] && nStation + 1 > _ModelInfo.nBCDScanStation)
                        {
                            nProcessStep[nStepIndex] = 170;
                            break;
                        }


                        nProcessStep[nStepIndex]++;     // 파레트가 1초간 감지된다면
                    }
                    else if (!GetDIOPort(_in_Pallet))
                    {
                        nProcessStep[nStepIndex] = 50;
                        break;
                    }
                    break;

                case 153:
                    //_SysInfo.nBoltNeed[_ModelInfo._TipInfo[nStation].nSpare_a[0], nStation] += _ModelInfo._TipInfo[nStation].nTipMaxCount[0];
                    //_SysInfo.nBoltNeed[_ModelInfo._TipInfo[nStation].nSpare_a[1], nStation] += _ModelInfo._TipInfo[nStation].nTipMaxCount[1];
                    //_SysInfo.nBoltNeed[_ModelInfo._TipInfo[nStation].nSpare_a[2], nStation] += _ModelInfo._TipInfo[nStation].nTipMaxCount[2];
                    //_SysInfo.nBoltNeed[_ModelInfo._TipInfo[nStation].nSpare_a[3], nStation] += _ModelInfo._TipInfo[nStation].nTipMaxCount[3];
                    //_SysInfo.nBoltNeed[_ModelInfo._TipInfo[nStation].nSpare_a[4], nStation] += _ModelInfo._TipInfo[nStation].nTipMaxCount[4];
                    // 리프트 상승
                    //if (nStation == 2 && (_ModelInfo.bUseTPCRobot || _ModelInfo.bUseST3Model2))
                    //{
                    //    _SysInfo.strST3NowWorkModel = ""; //체결로봇 모델정보 초기화
                    //    _SysInfo.bST3Work2Finish = false;
                    //    _SysInfo.nTPCRobotRetryCount = 0;
                    //}

                    _tSTCycleTimer[(int)STATION_LIST.ST1 + nStation].Restart();
                    _tSTCycleStartTime[(int)STATION_LIST.ST1 + nStation] = DateTime.Now;

                    SetDIOPort(_out_Lift_Up, true);
                    SetDIOPort(_out_Lift_Dw, false);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 154:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 10000;
                        AppendTimeOutMsg(_in_Lift_Up);      // 리프트 상승 타임아웃
                    }

                    if (GetDIOPort(_in_Lift_Up))
                    {

                        nProcessStep[nStepIndex] = 50;




                        //if (nStation == 2 && (_ModelInfo.bUseTPCRobot || _ModelInfo.bUseST3Model2))
                        //{
                        //    // ST3번이고 TPC로봇을 사용한다면
                        //    nProcessStep[nStepIndex] = 2000;    // 2000번대로이동
                        //}

                    }
                    break;


                case 170:
                    if (_SysInfo.bAutoCycleStop)
                    {
                        nProcessStep[nStepIndex] = 9000;
                        break;
                    }

                    // 다음장비에서 요청이 온다면 바이패스 시킴
                    if (!GetDIOPort(_Next_Pallet) && GetDIOPort(_Next_Lift_DW) && _SysInfo.bStationAutoMode[(int)STATION_LIST.ST1 + nStation + 1])
                    {
                        SetDIOPort(_out_Stopper_Open, true);
                        nProcessStep[nStepIndex] = 400;
                    }
                    break;
                //================================================




                // =========================================
                // 리프트가 상승상태
                // 파레트가 없다면 리프트를 하강 시킴
                case 200:
                    tMainTimer[nStepIndex].Start(1000); // 1초동안 파레트가 감지가 안된다면
                    nProcessStep[nStepIndex]++;
                    break;

                case 201:
                    if (!GetDIOPort(_in_Pallet) && GetDIOPort(_in_Pallet_Center) && tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    else if (GetDIOPort(_in_Pallet) || !GetDIOPort(_in_Pallet_Center))
                    {
                        nProcessStep[nStepIndex] = 50;
                        break;
                    }
                    break;

                case 202:
                    _SysInfo.bTite_Ing[nStation] = false;
                    SetDIOPort(_out_Lift_Dw, true);
                    SetDIOPort(_out_Lift_Up, false);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 203:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 10000;
                        AppendTimeOutMsg(_in_Lift_Dw);      // 리프트 하강 타임아웃
                    }

                    if (GetDIOPort(_in_Lift_Dw))
                    {
                        nProcessStep[nStepIndex] = 50;
                    }
                    break;


                // =========================================
                // 리프트가 상승상태
                // 파레트가 있다면 스위치 입력을 기다림
                case 300:
                    // 예약 버튼이 눌려 있다면
                    //if (_SysInfo.bStationReservation[(int)STATION_LIST.ST1 + nStation])
                    //{
                    //    // 전단장비 콜이 들어오면
                    //    if (!GetDIOPort(_Next_Pallet) && GetDIOPort(_Next_Lift_DW) && _SysInfo.bStationAutoMode[(int)STATION_LIST.ST1 + nStation + 1])
                    //    {
                    //        nProcessStep[nStepIndex] = 400;
                    //        break;
                    //    }
                    //}
                    //if (nStation == 2 && (_ModelInfo.bUseTPCRobot || _ModelInfo.bUseST3Model2))
                    //{
                    //    // ST3번이고 TPC로봇을 사용한다면
                    //    nProcessStep[nStepIndex] = 2000;    // 2000번대로이동
                    //    break;
                    //}

                    if (GetDIOPort(_in_Pass_SW))
                    {
                        nProcessStep[nStepIndex] = 50;
                        break;
                    }
                    tMainTimer[nStepIndex].Start(3000);
                    nProcessStep[nStepIndex]++;
                    break;

                case 301:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 50;
                        break;
                    }

                    if (_ModelInfo.bLockingStationSkip[nStation])
                    {
                        // 전단장비 콜이 들어오면
                        if (!GetDIOPort(_Next_Pallet) && GetDIOPort(_Next_Lift_DW) && _SysInfo.bStationAutoMode[(int)STATION_LIST.ST1 + nStation + 1])
                        {
                            nProcessStep[nStepIndex] = 400;
                        }
                        break;
                    }

                    // PASS 스위치가 들어온다면
                    if (GetDIOPort(_in_Pass_SW))
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 302:
                    tMainTimer[nStepIndex].Start(_Config.nChatteringTime);  // 채터링 방지 시간
                    nProcessStep[nStepIndex]++;
                    break;


                case 303:
                    if (GetDIOPort(_in_Pass_SW) && tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 350;
                    }
                    else if (!GetDIOPort(_in_Pass_SW))
                    {
                        nProcessStep[nStepIndex] = 50;
                    }
                    break;


                // =========================================
                // 배출 스위치가 눌렸을경우
                // 파레트 정위치, 체결 상태, 컨베어 동작상태 체크
                case 350:
                   if (_Config.bUseNutrunnerMove && nStation == 0)
                   {
                       if (GetDIOPort(_in_Pallet_Center) && (GetDIOPort(DI.INVERTER1_RUN) || !_Config.bUseMainCVMonitor))
                       {
                           if (nStation + 1 == _ModelInfo.nBCDScanStation)
                           {
                               if (_SysInfo.bBCDReadAllOk &&
                                    _ModelInfo._EtcDataScan[0].CheckListAllOk())
                               {
                                   if (_ModelInfo.bUseScanSTTester && !_SysInfo.bScanSTTesetFinish)
                                   {
                                       AppendLogMsg(String.Format("Station #{0} - {1}", nStation + 1, OutputLogMsg(OutPutMessage.TEST_NOT_COMPLATE)), LOG_TYPE.ERROR);
                                       _SysInfo.nCount_Beep[nStation] = 3;
                                       nProcessStep[nStepIndex] = 50;

                                   }
                                   else if (_Config.bUseReWorkTypeBCDScan && !_SysInfo.bReworkScanFinish)
                                   {
                                       AppendLogMsg(String.Format("Station #{0} - 재작업 PACK 바코드 스캔이 이뤄지지 않았습니다", nStation + 1), LOG_TYPE.ERROR);
                                       _SysInfo.nCount_Beep[nStation] = 3;
                                       nProcessStep[nStepIndex] = 50;
                                   }
                                   else
                                   {
                                       nProcessStep[nStepIndex] = 370;
                                   }
                               }
                               else
                               {
                                   AppendLogMsg(String.Format("Station #{0} - {1}", nStation + 1, OutputLogMsg(OutPutMessage.READ_NOT_COMPLATE)), LOG_TYPE.ERROR);
                                   _SysInfo.nCount_Beep[nStation] = 3;

                                   nProcessStep[nStepIndex] = 50;
                               }
                           }
                           else if (nStation + 1 == _ModelInfo.nETCScanStation)
                           {
                               //if ((_SysInfo.bETCReadOk || (_ModelInfo.nFuseCount < 1)) &&
                               //    (_SysInfo.bETCScan1 || (_ModelInfo.nUseETC1BCD < 1)) &&
                               //    (_SysInfo.bETCScan2 || (_ModelInfo.nUseETC2BCD < 1)) &&
                               //     (_SysInfo.bETCScan3 || (_ModelInfo.nUseETC3BCD < 1)))
                               //{
                               //    nProcessStep[nStepIndex] = 370;
                               //}
                               if (_ModelInfo._EtcDataScan[1].CheckListAllOk())
                               {
                                   nProcessStep[nStepIndex] = 370;
                               }
                               else
                               {
                                   AppendLogMsg(String.Format("Station #{0} - {1}", nStation + 1, OutputLogMsg(OutPutMessage.FUSE_NOT_COMPLATE)), LOG_TYPE.ERROR);
                                   _SysInfo.nCount_Beep[nStation] = 3;

                                   nProcessStep[nStepIndex] = 50;
                                   break;
                               }
                           }
                           else if (nStation == 0)
                           {
                                // 모델 정보를 사용하고 Pallet 바코드 스캔 기능을 사용 한다면
                                //if ((_SysInfo.bST1BCDReadAllOk || !_ModelInfo.bUsePalletBarcode) && _ModelInfo._EtcDataScan[2].CheckListAllOk())
                                //{
                                //    nProcessStep[nStepIndex] = 370;
                                //}
                                //else
                                //{
                                //    AppendLogMsg(String.Format("Station #{0} - {1}", nStation + 1, OutputLogMsg(OutPutMessage.READ_NOT_COMPLATE)), LOG_TYPE.ERROR);
                                //    _SysInfo.nCount_Beep[nStation] = 3;

                                //    nProcessStep[nStepIndex] = 50;
                                //    break;
                                //}
                                if (_ModelInfo._EtcDataScan[2].CheckListAllOk() && GetEPPAllOK())
                                {
                                    nProcessStep[nStepIndex] = 370;
                                }
                                else
                                {
                                    if (!_ModelInfo._EtcDataScan[2].CheckListAllOk())
                                    {
                                        AppendLogMsg(String.Format("Station #1 - 이종품 검사가 완료되지 않았습니다"), LOG_TYPE.ERROR);
                                    }
                                    else if (!GetEPPAllOK())
                                    {
                                        AppendLogMsg(String.Format("Station #{0} - EPP 검사가 이뤄지지 않았습니다.", nStation + 1), LOG_TYPE.ERROR);
                                    }
                                    _SysInfo.nCount_Beep[nStation] = 3;
                                    nProcessStep[nStepIndex] = 50;
                                    break;
                                }
                            }
                           else
                           {
                               nProcessStep[nStepIndex] = 370;
                           }
                       }
                       else
                       {
                           if (!GetDIOPort(_in_Pallet_Center)) { AppendLogMsg(String.Format("Station #{0} - {1}", nStation + 1, OutputLogMsg(OutPutMessage.PALLET_NOT_CENTER)), LOG_TYPE.ERROR); }
                           if (_Config.bUseMainCVMonitor) { if (!GetDIOPort(DI.INVERTER1_RUN)) { AppendLogMsg(String.Format("Station #{0} - {1}", nStation + 1, OutputLogMsg(OutPutMessage.MAIN_CV_NOT_RUNNING)), LOG_TYPE.ERROR); } }

                           _SysInfo.nCount_Beep[nStation] = 3;

                           nProcessStep[nStepIndex] = 50;
                       }
                   }
                   else
                    {
                        // 바이패스 작업
                        if (_ModelInfo.bUseScanSTTester && !_SysInfo.bScanSTTestOKNG[(int)STATION_LIST.ST1 + nStation] && nStation + 1 > _ModelInfo.nBCDScanStation)
                        {
                            nProcessStep[nStepIndex] = 370;
                            break;
                        }

                        if (_SysInfo.bTiteOk[nStation] && GetDIOPort(_in_Pallet_Center) && (GetDIOPort(DI.INVERTER1_RUN) || !_Config.bUseMainCVMonitor))
                        {
                            if (nStation + 1 == _ModelInfo.nBCDScanStation)
                            {
                                if (_SysInfo.bBCDReadAllOk &&
                                   _ModelInfo._EtcDataScan[0].CheckListAllOk())
                                {
                                    if (_ModelInfo.bUseScanSTTester && !_SysInfo.bScanSTTesetFinish)
                                    {
                                        AppendLogMsg(String.Format("Station #{0} - {1}", nStation + 1, OutputLogMsg(OutPutMessage.TEST_NOT_COMPLATE)), LOG_TYPE.ERROR);
                                        _SysInfo.nCount_Beep[nStation] = 3;
                                        nProcessStep[nStepIndex] = 50;

                                    }
                                    else if (_Config.bUseReWorkTypeBCDScan && !_SysInfo.bReworkScanFinish)
                                    {
                                        AppendLogMsg(String.Format("Station #{0} - 재작업 PACK 바코드 스캔이 이뤄지지 않았습니다", nStation + 1), LOG_TYPE.ERROR);
                                        _SysInfo.nCount_Beep[nStation] = 3;
                                        nProcessStep[nStepIndex] = 50;
                                    }
                                    else
                                    {
                                        nProcessStep[nStepIndex] = 370;
                                    }
                                }
                                else
                                {
                                    AppendLogMsg(String.Format("Station #{0} - {1}", nStation + 1, OutputLogMsg(OutPutMessage.READ_NOT_COMPLATE)), LOG_TYPE.ERROR);
                                    _SysInfo.nCount_Beep[nStation] = 3;

                                    nProcessStep[nStepIndex] = 50;
                                    break;
                                }
                            }
                            else if (nStation + 1 == _ModelInfo.nETCScanStation)
                            {
                                //if ((_SysInfo.bETCReadOk || (_ModelInfo.nFuseCount < 1)) &&
                                //   (_SysInfo.bETCScan1 || (_ModelInfo.nUseETC1BCD < 1)) &&
                                //   (_SysInfo.bETCScan2 || (_ModelInfo.nUseETC2BCD < 1)) &&
                                //    (_SysInfo.bETCScan3 || (_ModelInfo.nUseETC3BCD < 1)))
                                //{
                                //    nProcessStep[nStepIndex] = 370;
                                //}
                                if (_ModelInfo._EtcDataScan[1].CheckListAllOk())
                                {
                                    nProcessStep[nStepIndex] = 370;
                                }
                                else
                                {
                                    AppendLogMsg(String.Format("Station #{0} - {1}", nStation + 1, OutputLogMsg(OutPutMessage.FUSE_NOT_COMPLATE)), LOG_TYPE.ERROR);
                                    _SysInfo.nCount_Beep[nStation] = 3;

                                    nProcessStep[nStepIndex] = 50;
                                    break;
                                }
                            }
                            else if (nStation == 0)
                            {
                                // 모델 정보를 사용하고 Pallet 바코드 스캔 기능을 사용 한다면
                                if ((_SysInfo.bST1BCDReadAllOk || !_ModelInfo.bUsePalletBarcode) && _ModelInfo._EtcDataScan[2].CheckListAllOk() && GetEPPAllOK())
                                {
                                    nProcessStep[nStepIndex] = 370;
                                }
                                //else
                                //{
                                //    AppendLogMsg(String.Format("Station #{0} - {1}", nStation + 1, OutputLogMsg(OutPutMessage.READ_NOT_COMPLATE)), LOG_TYPE.ERROR);
                                //    _SysInfo.nCount_Beep[nStation] = 3;

                                //    nProcessStep[nStepIndex] = 50;
                                //    break;
                                //}
                                else
                                {
                                    //AppendLogMsg(String.Format("Station #{0} - {1}", nStation + 1, OutputLogMsg(OutPutMessage.READ_NOT_COMPLATE)), LOG_TYPE.ERROR);
                                    if (!_ModelInfo._EtcDataScan[2].CheckListAllOk())
                                    {
                                        AppendLogMsg(String.Format("Station #1 - 이종품 검사가 완료되지 않았습니다"), LOG_TYPE.ERROR);
                                    }
                                    else if (!GetEPPAllOK())
                                    {
                                        AppendLogMsg(String.Format("Station #{0} - EPP 검사가 이뤄지지 않았습니다.", nStation + 1), LOG_TYPE.ERROR);
                                    }
                                    _SysInfo.nCount_Beep[nStation] = 3;

                                    nProcessStep[nStepIndex] = 50;
                                    //nProcessStep[nStepIndex] = 300;
                                    break;
                                }
                            }
                            else if (nStation == (_ModelInfo.nMarkingStation - 1) && _ModelInfo.bUseLaserMarking)
                            {
                                if (_SysInfo.bLaserBarcodeCompare)
                                {
                                    nProcessStep[nStepIndex] = 370;
                                }
                                else
                                {
                                    AppendLogMsg(String.Format("Station #{0} - 레이저 마킹 검사가 이뤄지지 않았습니다.", nStation + 1), LOG_TYPE.ERROR);
                                    _SysInfo.nCount_Beep[nStation] = 3;

                                    nProcessStep[nStepIndex] = 50;
                                    break;
                                }
                            }
                        
                            else
                            {
                                nProcessStep[nStepIndex] = 370;
                            }
                        }
                        else
                        {
                            if (!_SysInfo.bTiteOk[nStation]) { AppendLogMsg(String.Format("Station #{0} - {1}", nStation + 1, OutputLogMsg(OutPutMessage.TITE_NOT_COMPLATE)), LOG_TYPE.ERROR); }
                            if (!GetDIOPort(_in_Pallet_Center)) { AppendLogMsg(String.Format("Station #{0} - {1}", nStation + 1, OutputLogMsg(OutPutMessage.PALLET_NOT_CENTER)), LOG_TYPE.ERROR); }
                            if (_Config.bUseMainCVMonitor) { if (!GetDIOPort(DI.INVERTER1_RUN)) { AppendLogMsg(String.Format("Station #{0} - {1}", nStation + 1, OutputLogMsg(OutPutMessage.MAIN_CV_NOT_RUNNING)), LOG_TYPE.ERROR); } }

                            _SysInfo.nCount_Beep[nStation] = 3;

                            nProcessStep[nStepIndex] = 50;
                        }
                    }
                    break;


                case 370:
                    if (_Config.bUseStationReservation)
                    {
                        _SysInfo.bStationReservation[(int)STATION_LIST.ST1 + nStation] = true;
                        nProcessStep[nStepIndex] = 50;
                    }
                    else if (_Config.bUseLockingStationDwStay)
                    {
                        // 하강 대기 스텝을 사용할경우
                        nProcessStep[nStepIndex] = 380;
                    }
                    else
                    {
                        if (!GetDIOPort(_Next_Pallet) && GetDIOPort(_Next_Lift_DW) && _SysInfo.bStationAutoMode[(int)STATION_LIST.ST1 + nStation + 1])
                        {
                            nProcessStep[nStepIndex] = 400;
                        }
                        else
                        {
                            AppendLogMsg(String.Format("Station #{0} - {1}", nStation + 1, OutputLogMsg(OutPutMessage.NEXT_STATION_NOT_READY)), LOG_TYPE.ERROR);
                            _SysInfo.nCount_Beep[nStation] = 3;
                            nProcessStep[nStepIndex] = 50;
                        }
                    }
                    break;



                // 하강후 배출대기 행정 ( 기능추가 )
                case 380:
                    SetDIOPort(_out_Lift_Dw, true);
                    SetDIOPort(_out_Lift_Up, false);
                    nProcessStep[nStepIndex]++;
                    break;

                case 381:
                    // 리프트 하강상태로 다음 스테이션 준비될때까지 대기
                    if (!GetDIOPort(_Next_Pallet) && GetDIOPort(_Next_Lift_DW) && _SysInfo.bStationAutoMode[(int)STATION_LIST.ST1 + nStation + 1])
                    {
                        nProcessStep[nStepIndex] = 400;         // 다음스테이션 준비되면 배출 동작
                    }
                    break;



                // =========================================
                // 배출 조건에 맞아 배출할 경우
                case 400:
                    _tSTCycleTimer[(int)STATION_LIST.ST1 + nStation].Stop();
                    _tSTCycleEndTime[(int)STATION_LIST.ST1 + nStation] = DateTime.Now;
                    SaveStationTactTime(STATION_LIST.ST1 + nStation, _tSTCycleStartTime[(int)STATION_LIST.ST1 + nStation], _tSTCycleEndTime[(int)STATION_LIST.ST1 + nStation], 0);

                    tCVTimer.Start(_Config.nCVAutoStopTime);
                    SetDIOPort(_out_Lift_Dw, true);
                    SetDIOPort(_out_Lift_Up, false);
                    if (_Config.bUseStopper || _ModelInfo.bLockingStationSkip[nStation] || _Config.bUseLockingStationDwStay) { SetDIOPort(_out_Stopper_Open, true); }
                    _SysInfo.bStationReservation[(int)STATION_LIST.ST1 + nStation] = false;
                    _SysInfo.bNextPalletOut[(int)STATION_LIST.ST1 + nStation] = true;   // 배출한다고 알림
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 401:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 10000;
                        AppendTimeOutMsg(_in_Lift_Dw);      // 리프트 하강 타임아웃
                        break;
                    }

                    if (GetDIOPort(_in_Lift_Dw))
                    {
                        tMainTimer[nStepIndex].Start(1000); // 스토퍼 동작 시간
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 402:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    SetDIOPort(_out_Stopper_Open, false);
                    tMainTimer[nStepIndex].Start(20000);    // 제품 배출 타임아웃
                    nProcessStep[nStepIndex]++;
                    break;

                case 403:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg(String.Format("Station #{0} - {1}", nStation + 1, OutputLogMsg(OutPutMessage.PALLET_OUTPUT_TIMEOUT)), LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 10000;
                    }


                    if (!GetDIOPort(_in_Pallet))
                    {
                        //_SysInfo.bTiteInfoClear[nStation] = true;
                        nProcessStep[nStepIndex] = 410;
                    }
                    break;

                // 체결정보 초기화
                case 410:
                    if (_Config.bUseNutrunnerMove && nStation == 0)
                    {
                        if (nStation == _ModelInfo.nBCDScanStation - 1)
                        {

                            _ReadBCDList.Clear();
                            _ModelInfo._EtcDataScan[0].ClearListData();
                            _mainform.BeginInvoke(new Action(() => _mainform.UpdateBCDGridStyle()));
                            SaveBCDListInfo();
                            //_dtBCDInfo.Rows.Clear();
                            //_dtBCDInfo.AcceptChanges();
                            //SaveBCDInfoTable();

                        }

                        if (nStation == 0)
                        {
                            _ST1BCDList.Clear();
                            _ModelInfo._EtcDataScan[2].ClearListData();
                            _SysInfo.nEPPReadCount = 0;
                            _SysInfo.bSt1ReadPalletBarcode = false;
                        }

                        if (nStation + 1 == _ModelInfo.nETCScanStation)
                        {
                            _ModelInfo._EtcDataScan[1].ClearListData();
                            _SysInfo.bETCReadOk = false;
                            _SysInfo.bETCScan1 = false;
                            _SysInfo.bETCScan2 = false;
                            _SysInfo.bETCScan3 = false;
                        }

                        nProcessStep[nStepIndex] = 50;
                        break;
                    }
                    else
                    {
                        //for (int i = 0; i < 5; i++)
                        //{
                        //    _SysInfo.nTipNowCount[nStation, i] = 0;
                        //}
                        //if (nStation == 2 && _ModelInfo.bUseST2Encoder)
                        if (nStation == 1 && _ModelInfo.bUseST2Encoder)
                        {
                            _SysInfo.nST2TiteWorkCount = 0;
                        }
                        else
                        {
                            for (int i = 0; i < 5; i++)
                            {
                                _SysInfo.nTipNowCount[nStation, i] = 0;
                            }
                        }
                        SaveSTLockInfo(nStation);
                        SUB_MOVE_TITE_LOG(nStation);

                        //SetDIOPort(_out_Count_Clear, true);
                        if (nStation == _ModelInfo.nBCDScanStation - 1)
                        {
                            //_dtBCDInfo.Rows.Clear();
                            //_dtBCDInfo.AcceptChanges();
                            //SaveBCDInfoTable();
                            _ReadBCDList.Clear();
                            _mainform.BeginInvoke(new Action(() => _mainform.UpdateBCDGridStyle()));
                            SaveBCDListInfo();
                            _SysInfo.bScanSTTestOKNG[(int)STATION_LIST.ST1 + nStation] = _SysInfo.bScanSTTesetOK;

                            _ModelInfo._EtcDataScan[0].ClearListData();

                            _SysInfo.bScanSTTesetFinish = false;
                            _SysInfo.bScanSTTesetOK = false;
                            _SysInfo.bReworkScanFinish = false;

                            _SysInfo.bETCScan4 = false;
                        }

                        if (nStation == 0)
                        {
                            _ST1BCDList.Clear();
                            _ModelInfo._EtcDataScan[2].ClearListData();
                            _SysInfo.nEPPReadCount = 0;
                            _SysInfo.bSt1ReadPalletBarcode = false;
                        }

                        if (nStation + 1 == _ModelInfo.nETCScanStation)
                        {
                            _ModelInfo._EtcDataScan[1].ClearListData();
                            _SysInfo.bETCReadOk = false;
                            _SysInfo.bETCScan1 = false;
                            _SysInfo.bETCScan2 = false;
                            _SysInfo.bETCScan3 = false;
                        }

                        if (nStation == 4)
                        {
                            _SysInfo.bLaserBarcodeCompare = false;
                            _SysInfo.strLaserReadBarcode = "";
                        }
                        _SysInfo.bScanSTTestOKNG[(int)STATION_LIST.ST1 + nStation + 1] = _SysInfo.bScanSTTestOKNG[(int)STATION_LIST.ST1 + nStation];
                        tMainTimer[nStepIndex].Start(200);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 411:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    //SetDIOPort(_out_Count_Clear, false);
                    nProcessStep[nStepIndex] = 50;
                    break;


                case 1900:
                    // _SysInfo.eChargeStartInfo[2] = START_INFO.READY;
                    //_mainform.BeginInvoke(new Action(() => _mainform.ViewTesterStartInfo(2)));
                    _SysInfo.nST3ResumeResult = 0;
                    _mainform.BeginInvoke(new Action(() => _mainform.ViewST3Resume(0)));
                    nProcessStep[nStepIndex]++;
                    break;

                case 1901:
                    if (_SysInfo.nST3ResumeResult == 1)
                    {
                        _TPCRobot.SetHome();    // HOME으로 보낸다
                        nProcessStep[nStepIndex] = 1920;
                    }
                    else if (_SysInfo.nST3ResumeResult == 2)
                    {
                        // 종료하라는 명령이 들어온 경우
                        _TPCRobot.SetHome();    // HOME으로 보낸다
                        nProcessStep[nStepIndex] = 3510;
                    }
                    break;

                case 1920:
                    break;

                // 정위치 확인 확인겸 서보 ON
                case 2000:
                    if (GetDIOPort(DI.STATION3_CENTER))
                    {
                        CAXM.AxmSignalServoOn((int)AXIS.ST3_R, 1);
                        CAXM.AxmStatusSetActPos((int)AXIS.ST3_R, 0.0);
                        CAXM.AxmStatusSetCmdPos((int)AXIS.ST3_R, 0.0);
                        _SysInfo.nPsetOldIndex[nStation] = 0;       // Old Index 초기화 하여 너트러너 스케쥴 변경함
                        SetNutRunnerSch(nStation, _ModelInfo.nTPCTiteSch);
                        nProcessStep[nStepIndex] = 2100;
                    }
                    else
                    {
                        // TM로봇 간섭때문에 원복행정 삭제


                        CAXM.AxmSignalServoOn((int)AXIS.ST3_R, 0);
                        AppendLogMsg("ST3 PALLET NOT CENTER", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 10000;
                    }
                    break;

                case 2100:
                    SetDIOPort(DO.STATION3_BREAK_OFF, true);
                    SetDIOPort(DO.STATION3_LOCK_OFF, true);  // 물리적인 브레이크 해제
                    tMainTimer[nStepIndex].Start(200);
                    nProcessStep[nStepIndex] = 2110;
                    break;

                case 2110:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    //if(_ModelInfo.bUseTPCRobot)
                    //{
                    //    _SysInfo.strST3NowWorkModel = _ModelInfo.strST3Model1;
                    //    nProcessStep[nStepIndex] = 2900;
                    //}
                    //else
                    //{
                    // 2번 체크하러 감
                    nProcessStep[nStepIndex] = 3900;
                    //}
                    break;

                case 2900:
                    if (!MotionDone(AXIS.ST3_R)) { break; }

                    MoveTo(AXIS.ST3_R, 0.0, _ModelInfo.dbST3TurnSpeed, 1);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2901:
                    if (!MotionDone(AXIS.ST3_R)) { break; }

                    tMainTimer[nStepIndex].Start(500);      // 관성 잡아주는 시간
                    nProcessStep[nStepIndex]++;
                    break;

                case 2902:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    SetDIOPort(DO.STATION3_BREAK_OFF, false);
                    SetDIOPort(DO.STATION3_LOCK_OFF, false);
                    tMainTimer[nStepIndex].Start(500);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2903:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    CAXM.AxmSignalServoOn((int)AXIS.ST3_R, 0);
                    nProcessStep[nStepIndex] = 3000;
                    break;

                // 3000번대부터 행정 시작
                case 3000:
                    // TPC 로봇 스텟을 홈상태로 만듬
                    _TPCRobot._Stat = TPC_STAT.READY;
                    _TPCRobot.SetHome();    // 로봇을 홈으로 보냄
                    tMainTimer[nStepIndex].Start(_Config.nTPCRobotCommTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 3001:
                    // 통신 타임아웃
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        if (_SysInfo.nTPCRobotRetryCount > 2)
                        {
                            AppendLogMsg("STATION #3 ROBOT 通信 ERROR", LOG_TYPE.ERROR);
                            nProcessStep[nStepIndex] = 8000;
                            _SysInfo.nTPCRobotRetryCount = 0;
                        }
                        else
                        {
                            _SysInfo.nTPCRobotRetryCount++;
                            nProcessStep[nStepIndex] = 3000;
                        }

                    }

                    if (_TPCRobot._Stat == TPC_STAT.HOME)
                    {
                        _SysInfo.nTPCRobotRetryCount = 0;
                        tMainTimer[nStepIndex].Start(3000);
                        nProcessStep[nStepIndex] = 3100;
                    }
                    break;


                // 해당행정에선 모델 선택을 함
                case 3100:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    _TPCRobot.SetModel(_SysInfo.strST3NowWorkModel);
                    tMainTimer[nStepIndex].Start(_Config.nTPCRobotCommTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                // PSELECT 결과를 기다림
                case 3101:
                    // 통신 타임아웃
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("STATION #3 ROBOT 通信 ERROR", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 8000;
                    }

                    // 모델 선택 NG
                    if (_TPCRobot._Stat == TPC_STAT.PSELECTNG)
                    {
                        AppendLogMsg("STATION #3 - PSELECT NG", LOG_TYPE.ERROR);
                        tMainTimer[nStepIndex].Start(1000);
                        nProcessStep[nStepIndex] = 8000;
                    }

                    // 모델 선택 OK
                    if (_TPCRobot._Stat == TPC_STAT.PSELECTOK)
                    {
                        nProcessStep[nStepIndex] = 3200;
                        tMainTimer[nStepIndex].Start(1000);
                    }
                    break;

                case 3110:
                    if (_SysInfo.nST3ResumeResult == 1)
                    {
                        nProcessStep[nStepIndex] = 3100;
                    }
                    else if (_SysInfo.nST3ResumeResult == 2)
                    {
                        // 종료하라는 명령이 들어온 경우
                        _TPCRobot.SetHome();    // HOME으로 보낸다
                        nProcessStep[nStepIndex] = 3510;
                    }
                    break;


                // TPC로봇 자동행정 시작
                case 3200:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    _TPCRobot.SetStart();
                    nProcessStep[nStepIndex] = 3210;
                    break;

                case 3210:
                    if (_TPCRobot._Stat == TPC_STAT.PSTARTOK)
                    {

                        nProcessStep[nStepIndex] = 3300;
                    }
                    break;

                // 반복 행정
                case 3300:
                    if (_TPCRobot._Stat == TPC_STAT.VNG)
                    {
                        nProcessStep[nStepIndex] = 8000;
                    }
                    else if (_TPCRobot._Stat == TPC_STAT.TNG)
                    {
                        //// 체결 NG가 들어왔다면
                        //// 종료할지 더 할지 설정하는 행정
                        //_SysInfo.bStation3NgOut = 0;
                        //_mainform.BeginInvoke(new Action(() => _mainform.ViewST3Resume(0)));
                        //nProcessStep[nStepIndex] = 3600;
                        AppendLogMsg("STATION #3 ROBOT 紧固件 NG", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 8000;
                        tMainTimer[nStepIndex].Start(300);
                        break;

                    }
                    else if (_TPCRobot._Stat == TPC_STAT.OK)
                    {
                        // OK가 들어왔다면
                        // 다음 스텝으로 넘어가는 행정
                        nProcessStep[nStepIndex] = 3400;
                        tMainTimer[nStepIndex].Start(300);      // 기존 1000ms 에서 500ms 로 변경  [ 2019. 06. 11 ]
                    }
                    else if (_TPCRobot.bFinishFlag)
                    {
                        // 완료가 들어왔다면
                        // 종료 행정 
                        nProcessStep[nStepIndex] = 3310;
                        tMainTimer[nStepIndex].Start(300);             // 완료 이후에 HOME을 확인하고 행동 해야함
                    }
                    break;

                // FINISH 이후 홈 확인 행정
                case 3310:
                    if (_TPCRobot._Stat == TPC_STAT.HOME)
                    {
                        nProcessStep[nStepIndex] = 3900;
                    }
                    break;

                // 다음 스텝으로 넘어가는 행정
                case 3400:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    _SysInfo.bTPCReadOK = true; // 데이터가 들어왔다고 알림

                    _TPCRobot.SetNext();
                    nProcessStep[nStepIndex] = 3300;
                    break;

                // VISION NG일 경우
                case 3500:
                    // 재작업 하라는 명령이 들어온 경우
                    if (_SysInfo.nST3ResumeResult == 1)
                    {
                        _TPCRobot.SetVresume();
                        nProcessStep[nStepIndex] = 3300;
                    }
                    else if (_SysInfo.nST3ResumeResult == 2)
                    {
                        // 종료하라는 명령이 들어온 경우
                        _TPCRobot.SetHome();    // HOME으로 보낸다
                        nProcessStep[nStepIndex] = 3510;
                    }
                    break;

                case 3510:
                    if (_TPCRobot._Stat == TPC_STAT.HOME)
                    {
                        // HOME 위치로 정상적으로 이동한경우
                        tMainTimer[nStepIndex].Start(3000);
                        nProcessStep[nStepIndex] = 4000;        // 작업을 마무리한다
                    }
                    break;

                // TNG가 들어온경우
                case 3600:
                    //if (_SysInfo.bStation3NgOut == 1)
                    //{
                    //    //다음 포인트 작업하라는 명령이 들어온 경우
                    //    _TPCRobot.SetNext();
                    //    nProcessStep[nStepIndex] = 3300;
                    //}
                    //else 
                    if (_SysInfo.bStation3NgOut == 1)
                    {
                        // NG 창이 닫히면
                        _TPCRobot.SetHome();
                        nProcessStep[nStepIndex] = 3610;
                    }
                    break;

                case 3610:
                    if (_TPCRobot._Stat == TPC_STAT.HOME)
                    {
                        tMainTimer[nStepIndex].Start(3000);
                        // HOME 위치로 정상적으로 이동한경우
                        nProcessStep[nStepIndex] = 4000;        // 작업을 마무리한다
                    }
                    break;

                // 종료행정
                case 3900:
                    //if (_ModelInfo.bUseST3Model2 && _SysInfo.strST3NowWorkModel != _ModelInfo.strST3Model2)
                    //{
                    //    _SysInfo.strST3NowWorkModel = _ModelInfo.strST3Model2;
                    //    nProcessStep[nStepIndex] = 3910;
                    //    break;
                    //}

                    if (_ModelInfo.bUseST3Model2 && !_SysInfo.bST3Work2Finish)
                    {
                        _SysInfo.bST3Work2Finish = true;
                        _SysInfo.strST3NowWorkModel = _ModelInfo.strST3Model2;
                        nProcessStep[nStepIndex] = 3910;
                        break;
                    }
                    nProcessStep[nStepIndex] = 4000;  // 작업을 마무리한다
                    break;

                // 무빙전엔 항상 락 해제
                case 3910:
                    SetDIOPort(DO.STATION3_LOCK_OFF, true);
                    SetDIOPort(DO.STATION3_BREAK_OFF, true);
                    tMainTimer[nStepIndex].Start(300);
                    CAXM.AxmSignalServoOn((int)AXIS.ST3_R, 1);
                    nProcessStep[nStepIndex]++;
                    break;

                case 3911:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    nProcessStep[nStepIndex] = 3920;
                    break;


                case 3920:
                    MoveTo(AXIS.ST3_R, _ModelInfo.dbST3TurnAngle, _ModelInfo.dbST3TurnSpeed, 1);
                    nProcessStep[nStepIndex] = 3930;
                    break;


                case 3930:
                    if (!MotionDone(AXIS.ST3_R)) { break; }

                    // 관성 잡기
                    tMainTimer[nStepIndex].Start(500);


                    nProcessStep[nStepIndex] = 3940;
                    break;

                case 3940:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }


                    SetDIOPort(DO.STATION3_LOCK_OFF, false);
                    SetDIOPort(DO.STATION3_BREAK_OFF, false);
                    CAXM.AxmSignalServoOn((int)AXIS.ST3_R, 0);
                    tMainTimer[nStepIndex].Start(300);
                    nProcessStep[nStepIndex]++;
                    break;

                case 3941:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    nProcessStep[nStepIndex] = 3000;
                    break;


                // 마무리 작업을 함
                // 판을 돌리기전엔 항상 브레이크 해제
                case 4000:
                    SetDIOPort(DO.STATION3_BREAK_OFF, true);
                    SetDIOPort(DO.STATION3_LOCK_OFF, true);
                    CAXM.AxmSignalServoOn((int)AXIS.ST3_R, 1);
                    tMainTimer[nStepIndex].Start(300);
                    nProcessStep[nStepIndex]++;
                    break;

                case 4001:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    nProcessStep[nStepIndex]++;
                    break;

                case 4002:
                    MoveTo(AXIS.ST3_R, 0.0, _ModelInfo.dbST3TurnSpeed);
                    nProcessStep[nStepIndex] = 4010;
                    break;

                case 4010:
                    if (!MotionDone(AXIS.ST3_R)) { break; }

                    tMainTimer[nStepIndex].Start(500); // 관성을 안정화 시킨다
                    nProcessStep[nStepIndex] = 4020;
                    break;

                case 4020:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    SetDIOPort(DO.STATION3_BREAK_OFF, false);
                    SetDIOPort(DO.STATION3_LOCK_OFF, false);
                    CAXM.AxmSignalServoOn((int)AXIS.ST3_R, 0); // 브레이크를 채우면서 서보를 OFF 한다
                    tMainTimer[nStepIndex].Start(300);
                    nProcessStep[nStepIndex]++;
                    break;

                case 4021:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    nProcessStep[nStepIndex] = 4100;
                    break;

                // 배출한다
                case 4100:
                    // 전단장비 콜이 들어오면
                    if (!GetDIOPort(_Next_Pallet) && GetDIOPort(_Next_Lift_DW) && _SysInfo.bStationAutoMode[(int)STATION_LIST.ST1 + nStation + 1])
                    {
                        nProcessStep[nStepIndex] = 400; // 배출한다
                    }
                    break;


                case 8000:
                    _SysInfo.bTPCReadOK = true; // 데이터가 들어왔다고 알림

                    tMainTimer[nStepIndex].Start(1000);
                    nProcessStep[nStepIndex]++;
                    break;

                case 8001:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    _TPCRobot.SetHome();
                    tMainTimer[nStepIndex].Start(30000);
                    nProcessStep[nStepIndex]++;
                    break;

                case 8002:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("STATION #3 ROBOT 通信 ERROR", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 10000;

                    }

                    if (_TPCRobot._Stat == TPC_STAT.HOME)
                    {
                        nProcessStep[nStepIndex] = 8100;
                    }
                    break;

                // 마무리 작업을 함
                // 판을 돌리기전엔 항상 브레이크 해제
                case 8100:
                    SetDIOPort(DO.STATION3_BREAK_OFF, true);
                    SetDIOPort(DO.STATION3_LOCK_OFF, true);
                    CAXM.AxmSignalServoOn((int)AXIS.ST3_R, 1);
                    tMainTimer[nStepIndex].Start(200);
                    nProcessStep[nStepIndex]++;
                    break;

                case 8101:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    nProcessStep[nStepIndex]++;
                    break;

                case 8102:
                    MoveTo(AXIS.ST3_R, 0.0, _ModelInfo.dbST3TurnSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 8103:
                    if (!MotionDone(AXIS.ST3_R)) { break; }

                    tMainTimer[nStepIndex].Start(500); // 관성을 안정화 시킨다
                    nProcessStep[nStepIndex]++;
                    break;

                case 8104:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    SetDIOPort(DO.STATION3_BREAK_OFF, false);
                    SetDIOPort(DO.STATION3_LOCK_OFF, false);
                    CAXM.AxmSignalServoOn((int)AXIS.ST3_R, 0); // 브레이크를 채우면서 서보를 OFF 한다
                    nProcessStep[nStepIndex] = 8200;
                    break;

                case 8200:
                    _mainform.BeginInvoke(new Action(() => _mainform.ViewST3Resume(0)));
                    nProcessStep[nStepIndex] = 10000;
                    break;

                case 9000:
                    _SysInfo.bStationAutoMode[(int)STATION_LIST.ST1 + nStation] = false;
                    break;





                case 10000:
                    nProcessStep[nStepIndex] = 9000;
                    _SysInfo.TL_Buzzer = TOWER_LAMP.TL_ON;
                    break;
            }
        }
        //===========================================================


        static void WorkManualProcess()
        {
            int nStepIndex = (int)PROC_LIST.MANUAL;

            switch (nProcessStep[nStepIndex])
            {
                case 0:
                    _SysInfo.bManualEstop = false;
                    break;

                // 로딩 리프트 파레트 진입 프로세스
                case 1000:
                    SetDIOPort(DO.INLIFT_CV_FAST, false);
                    SetDIOPort(DO.INLIFT_CV_SLOW, false);
                    SetDIOPort(DO.INLIFT_CV_ON, false);
                    SetDIOPort(DO.INLIFT_CV_REV, false);
                    tMainTimer[nStepIndex].Start(200);
                    nProcessStep[nStepIndex]++;
                    break;

                case 1001:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        SetDIOPort(DO.INLIFT_CV_FAST, false);
                        SetDIOPort(DO.INLIFT_CV_SLOW, true);
                        SetDIOPort(DO.INLIFT_CV_ON, false);
                        SetDIOPort(DO.INLIFT_CV_REV, true);
                        tMainTimer[nStepIndex].Start(5000);
                        nProcessStep[nStepIndex]++;
                    }
                    break;


                case 1002:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    SetDIOPort(DO.INLIFT_CV_FAST, false);
                    SetDIOPort(DO.INLIFT_CV_SLOW, false);
                    SetDIOPort(DO.INLIFT_CV_ON, false);
                    SetDIOPort(DO.INLIFT_CV_REV, false);
                    nProcessStep[nStepIndex] = 0;
                    break;




                // 로딩 리프트 파레트 배출 프로세스
                case 1100:
                    SetDIOPort(DO.INLIFT_CV_FAST, false);
                    SetDIOPort(DO.INLIFT_CV_SLOW, false);
                    SetDIOPort(DO.INLIFT_CV_ON, false);
                    SetDIOPort(DO.INLIFT_CV_REV, false);
                    tMainTimer[nStepIndex].Start(200);
                    nProcessStep[nStepIndex]++;
                    break;

                case 1101:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        SetDIOPort(DO.INLIFT_CV_FAST, false);
                        SetDIOPort(DO.INLIFT_CV_SLOW, true);
                        SetDIOPort(DO.INLIFT_CV_ON, true);
                        SetDIOPort(DO.INLIFT_CV_REV, false);
                        tMainTimer[nStepIndex].Start(5000);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 1102:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    SetDIOPort(DO.INLIFT_CV_FAST, false);
                    SetDIOPort(DO.INLIFT_CV_SLOW, false);
                    SetDIOPort(DO.INLIFT_CV_ON, false);
                    SetDIOPort(DO.INLIFT_CV_REV, false);
                    nProcessStep[nStepIndex] = 0;
                    break;



                // 배출 리프트 파레트 적재 프로세스
                case 1200:
                    SetDIOPort(DO.RELIFT_CV_REV, false);
                    SetDIOPort(DO.RELIFT_CV_ON, false);
                    SetDIOPort(DO.RELIFT_CV_FAST, false);
                    SetDIOPort(DO.RELIFT_CV_SLOW, false);
                    tMainTimer[nStepIndex].Start(200);
                    nProcessStep[nStepIndex]++;
                    break;

                case 1201:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        SetDIOPort(DO.RELIFT_CV_REV, false);
                        SetDIOPort(DO.RELIFT_CV_ON, true);
                        SetDIOPort(DO.RELIFT_CV_FAST, false);
                        SetDIOPort(DO.RELIFT_CV_SLOW, true);
                        tMainTimer[nStepIndex].Start(5000);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 1202:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    SetDIOPort(DO.RELIFT_CV_REV, false);
                    SetDIOPort(DO.RELIFT_CV_ON, false);
                    SetDIOPort(DO.RELIFT_CV_FAST, false);
                    SetDIOPort(DO.RELIFT_CV_SLOW, false);
                    nProcessStep[nStepIndex] = 0;
                    break;

                // 배출 리프트 파레트 배출 프로세스
                case 1300:
                    SetDIOPort(DO.RELIFT_CV_REV, false);
                    SetDIOPort(DO.RELIFT_CV_ON, false);
                    SetDIOPort(DO.RELIFT_CV_FAST, false);
                    SetDIOPort(DO.RELIFT_CV_SLOW, false);
                    tMainTimer[nStepIndex].Start(200);
                    nProcessStep[nStepIndex]++;
                    break;

                case 1301:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        SetDIOPort(DO.RELIFT_CV_REV, true);
                        SetDIOPort(DO.RELIFT_CV_ON, false);
                        SetDIOPort(DO.RELIFT_CV_FAST, true);
                        SetDIOPort(DO.RELIFT_CV_SLOW, false);
                        tMainTimer[nStepIndex].Start(5000);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 1302:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    SetDIOPort(DO.RELIFT_CV_REV, false);
                    SetDIOPort(DO.RELIFT_CV_ON, false);
                    SetDIOPort(DO.RELIFT_CV_FAST, false);
                    SetDIOPort(DO.RELIFT_CV_SLOW, false);
                    nProcessStep[nStepIndex] = 0;
                    break;


                // 로딩 위치로 이동
                case 1600:
                    MoveTo(AXIS.Z, _Config.dbSafeLoadZPos, _ModelInfo.dbNoClampZMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 1601:
                    if (_SysInfo.bManualEstop)
                    {
                        CAXM.AxmMoveEStop((int)AXIS.Z);
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }
                    if (!MotionDone(AXIS.Z)) { break; }

                    MoveToXY(_SysInfo.dbManualMovePos[0], _SysInfo.dbManualMovePos[1], _ModelInfo.dbNoClampXYMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 1602:
                    if (_SysInfo.bManualEstop)
                    {
                        CAXM.AxmMoveEStop((int)AXIS.X);
                        CAXM.AxmMoveEStop((int)AXIS.Y);
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }
                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y)) { break; }

                    MoveTo(AXIS.Z, _SysInfo.dbManualMovePos[2], _ModelInfo.dbNoClampZMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 1603:
                    if (_SysInfo.bManualEstop)
                    {
                        CAXM.AxmMoveEStop((int)AXIS.Z);
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }
                    if (!MotionDone(AXIS.Z)) { break; }

                    nProcessStep[nStepIndex] = 0;
                    break;


                // 안착위치 선택위치로 이동
                case 1700:
                    MoveTo(AXIS.Z, _Config.dbSafeLoadZPos, _ModelInfo.dbNoClampZMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 1701:
                    if (_SysInfo.bManualEstop)
                    {
                        CAXM.AxmMoveEStop((int)AXIS.Z);
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }
                    if (!MotionDone(AXIS.Z)) { break; }

                    MoveToXY(_SysInfo.dbManualMovePos[0], _SysInfo.dbManualMovePos[1], _ModelInfo.dbClampXYMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 1702:
                    if (_SysInfo.bManualEstop)
                    {
                        CAXM.AxmMoveEStop((int)AXIS.X);
                        CAXM.AxmMoveEStop((int)AXIS.Y);
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }
                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y)) { break; }

                    MoveTo(AXIS.Z, _SysInfo.dbManualMovePos[2], _ModelInfo.dbClampZMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 1703:
                    if (_SysInfo.bManualEstop)
                    {
                        CAXM.AxmMoveEStop((int)AXIS.Z);
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }
                    if (!MotionDone(AXIS.Z)) { break; }
                    Move(AXIS.X, _SysInfo.dbManualMovePos[3], _ModelInfo.dbShiftMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 1704:
                    if (_SysInfo.bManualEstop)
                    {
                        CAXM.AxmMoveEStop((int)AXIS.X);
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }
                    if (!MotionDone(AXIS.X)) { break; }
                    Move(AXIS.Y, _SysInfo.dbManualMovePos[5], _ModelInfo.dbShiftMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 1705:
                    if (_SysInfo.bManualEstop)
                    {
                        CAXM.AxmMoveEStop((int)AXIS.X);
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }
                    if (!MotionDone(AXIS.Y)) { break; }
                    Move(AXIS.Z, _SysInfo.dbManualMovePos[4], _ModelInfo.dbShiftMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 1706:
                    if (_SysInfo.bManualEstop)
                    {
                        CAXM.AxmMoveEStop((int)AXIS.Z);
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }
                    if (!MotionDone(AXIS.Z)) { break; }
                    nProcessStep[nStepIndex] = 0;
                    break;


                // 회전위치로 이동
                case 1800:
                    MoveTo(AXIS.Z, _Config.dbSafeLoadZPos, _ModelInfo.dbNoClampZMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 1801:
                    if (_SysInfo.bManualEstop)
                    {
                        CAXM.AxmMoveEStop((int)AXIS.Z);
                        nProcessStep[nStepIndex] = 0;

                        break;
                    }
                    if (!MotionDone(AXIS.Z)) { break; }

                    MoveToXY(_SysInfo.dbManualMovePos[0], _SysInfo.dbManualMovePos[1], _ModelInfo.dbNoClampXYMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 1802:
                    if (_SysInfo.bManualEstop)
                    {
                        CAXM.AxmMoveEStop((int)AXIS.X);
                        CAXM.AxmMoveEStop((int)AXIS.Y);
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }

                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y)) { break; }
                    nProcessStep[nStepIndex] = 0;
                    break;




                //EOL 선택위치로 이동
                case 2000:
                    MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbReadyPos1X, _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2001:
                    if (!MotionDone(AXIS.EOL_X)) { break; }

                    MoveTo(AXIS.EOL_Y, _SysInfo.dbManualMovePos[1], _Config.dbTestZoneMoveSpeed);
                    MoveTo(AXIS.EOL_Z, _SysInfo.dbManualMovePos[2], _Config.dbTestZoneMoveSpeed);

                    nProcessStep[nStepIndex]++;
                    break;


                case 2002:
                    if (!MotionDone(AXIS.EOL_Y) || !MotionDone(AXIS.EOL_Z)) { break; }

                    MoveTo(AXIS.EOL_X, _SysInfo.dbManualMovePos[0], _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2003:
                    if (!MotionDone(AXIS.EOL_X)) { break; }

                    nProcessStep[nStepIndex] = 0;
                    break;


                //HIPOT1 선택위치로 이동
                case 2099:
                    if(_ModelInfo.bUseHipot1UpDwContact)
					{
                        nProcessStep[nStepIndex] = 2150;
                    }
                    else
					{
                        nProcessStep[nStepIndex] = 2100;
                    }
                    break;

                //상하 컨택 미사용시 하이팟1 선택이동 모션
                case 2100:
                    MoveTo(AXIS.HIPOT_1X, _ModelInfo._TestInfo[0].dbReadyPos1X, _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2101:
                    if (!MotionDone(AXIS.HIPOT_1X)) { break; }

                    MoveTo(AXIS.HIPOT_1Y, _SysInfo.dbManualMovePos[1], _Config.dbTestZoneMoveSpeed);
                    {
                        double dbNowPos1Z = 0;
                        CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_1Z, ref dbNowPos1Z);

                        double dbSpeed = 0;
                        dbSpeed = (Math.Abs(_SysInfo.dbManualMovePos[2] - dbNowPos1Z) > _Config.dbTestZoneContactZSlowMovePos) ? _Config.dbTestZoneContactZSlowMoveSpeed : _Config.dbTestZoneMoveSpeed;
                        MoveTo(AXIS.HIPOT_1Z, _SysInfo.dbManualMovePos[2], dbSpeed);
                    }


                    nProcessStep[nStepIndex]++;
                    break;


                case 2102:
                    if (!MotionDone(AXIS.HIPOT_1Y) || !MotionDone(AXIS.HIPOT_1Z)) { break; }

                    MoveTo(AXIS.HIPOT_1X, _SysInfo.dbManualMovePos[0], _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2103:
                    if (!MotionDone(AXIS.HIPOT_1X)) { break; }

                    nProcessStep[nStepIndex] = 0;
                    break;


               //상하 컨택 사용시 하이팟1 선택이동 모션
                case 2150:
                    MoveTo(AXIS.HIPOT_1Z, 0 , _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2151:
					if (!MotionDone(AXIS.HIPOT_1Z)) { break; }
                    nProcessStep[nStepIndex]++;
                    break;

                case 2152:
                    MoveTo(AXIS.HIPOT_2X, _SysInfo.dbManualMovePos[0], _Config.dbTestZoneMoveSpeed);
                    MoveTo(AXIS.HIPOT_2Y, _SysInfo.dbManualMovePos[1], _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2153:
                    if (!MotionDone(AXIS.HIPOT_1X) || !MotionDone(AXIS.HIPOT_1Y)) { break; }
                    nProcessStep[nStepIndex]++;
                    break;

                case 2154:
                    MoveTo(AXIS.HIPOT_1Z, _SysInfo.dbManualMovePos[2], _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2155:
                    if (!MotionDone(AXIS.HIPOT_1Z)) { break; }

                    nProcessStep[nStepIndex] = 0;
                    break;




                //HIPOT2 선택위치로 이동
                case 2200:
                    MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbReadyPos2X, _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2201:
                    if (!MotionDone(AXIS.HIPOT_2X)) { break; }

                    MoveTo(AXIS.HIPOT_2Y, _SysInfo.dbManualMovePos[1], _Config.dbTestZoneMoveSpeed);
                    MoveTo(AXIS.HIPOT_2Z, _SysInfo.dbManualMovePos[2], _Config.dbTestZoneMoveSpeed);

                    nProcessStep[nStepIndex]++;
                    break;


                case 2202:
                    if (!MotionDone(AXIS.HIPOT_2Y) || !MotionDone(AXIS.HIPOT_2Z)) { break; }

                    MoveTo(AXIS.HIPOT_2X, _SysInfo.dbManualMovePos[0], _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2203:
                    if (!MotionDone(AXIS.HIPOT_2X)) { break; }

                    nProcessStep[nStepIndex] = 0;
                    break;










                // ============== 수동으로 비전 검사 ==========================
                // 상부 라벨 검사
                case 2500:
                    // 검사시작전에 파일이 있으면 파일을 삭제함
                    if (File.Exists(String.Format("{0}.BMP", _Config.strVisionDir1)))
                    {
                        File.Delete(String.Format("{0}.BMP", _Config.strVisionDir1));
                    }

                    SetCmeraSch(0, _ModelInfo._TestInfo[0].nSpare_a[0]);
                    tMainTimer[nStepIndex].Start(100);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2501:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    if (!GetDIOPort(DI.CAMERA1_BUSY))
                    {
                        nProcessStep[nStepIndex] = 2510;
                    }
                    break;


                case 2510:
                    SetDIOPort(DO.CAMERA1_TRIG, true);
                    tMainTimer[nStepIndex].Start(100);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2511:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    if (!GetDIOPort(DI.CAMERA1_BUSY))
                    {
                        SetDIOPort(DO.CAMERA1_TRIG, false);
                        nProcessStep[nStepIndex]++;
                    }
                    break;


                case 2512:
                    nProcessStep[nStepIndex]++;
                    tMainTimer[nStepIndex].Start(20000);
                    break;



                case 2513:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg(String.Format("Hipot - Vision Img Load Fail.."), LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 0;    // 커뮤니케이션 실패
                        break;
                    }

                    if (File.Exists(String.Format("{0}.BMP", _Config.strVisionDir1)))
                    {
                        tMainTimer[nStepIndex].Start(500);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 2514:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    try
                    {
                        _modelSetup.BeginInvoke(new Action(() => _modelSetup.ViewVisionData(0, _HipotResult.strBCD)));
                    }
                    catch { };
                    nProcessStep[nStepIndex] = 0;
                    break;




                // ============== 수동으로 비전 검사 ==========================
                // 전면 검사
                case 2600:
                    // 검사시작전에 파일이 있으면 파일을 삭제함
                    if (File.Exists(String.Format("{0}.BMP", _Config.strVisionDir2)))
                    {
                        File.Delete(String.Format("{0}.BMP", _Config.strVisionDir2));
                    }

                    SetCmeraSch(1, _ModelInfo._TestInfo[0].nSpare_a[1]);
                    tMainTimer[nStepIndex].Start(100);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2601:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    if (!GetDIOPort(DI.CAMERA2_BUSY))
                    {
                        nProcessStep[nStepIndex] = 2610;
                    }
                    break;


                case 2610:
                    SetDIOPort(DO.CAMERA2_TRIG, true);
                    tMainTimer[nStepIndex].Start(100);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2611:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    if (!GetDIOPort(DI.CAMERA2_BUSY))
                    {
                        SetDIOPort(DO.CAMERA2_TRIG, false);
                        nProcessStep[nStepIndex]++;
                    }
                    break;


                case 2612:
                    nProcessStep[nStepIndex]++;
                    tMainTimer[nStepIndex].Start(20000);
                    break;



                case 2613:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg(String.Format("Hipot - Vision Img Load Fail.."), LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 0;    // 커뮤니케이션 실패
                        break;
                    }

                    if (File.Exists(String.Format("{0}.BMP", _Config.strVisionDir2)))
                    {
                        tMainTimer[nStepIndex].Start(500);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 2614:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    try
                    {
                        _modelSetup.BeginInvoke(new Action(() => _modelSetup.ViewVisionData(1, _HipotResult.strBCD)));
                    }
                    catch { };
                    nProcessStep[nStepIndex] = 0;
                    break;


                case 3100:
                    // 해당축 Z축 먼저 원점위치로 이동후 XYZ 지정위치로 이동함
                    MoveTo(AXIS.CAMERA1_Z, 0.0, _Config.dbOmronCameraZMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 3101:
                    if (!MotionDone(AXIS.CAMERA1_Z)) { break; }

                    MoveTo(AXIS.CAMERA1_X, _SysInfo.dbManualMovePos[0], _Config.dbOmronCameraXYMoveSpeed);
                    MoveTo(AXIS.CAMERA1_Y, _SysInfo.dbManualMovePos[1], _Config.dbOmronCameraXYMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 3102:
                    if (!MotionDone(AXIS.CAMERA1_X) || !MotionDone(AXIS.CAMERA1_Y)) { break; }

                    MoveTo(AXIS.CAMERA1_Z, _SysInfo.dbManualMovePos[2], _Config.dbOmronCameraZMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 3103:
                    if (!MotionDone(AXIS.CAMERA1_Z)) { break; }
                    nProcessStep[nStepIndex] = 0;
                    break;




                //카메라 선택위치 메뉴얼 이동 Camera 1번축
                case 3200:
                    // 해당축 Z축 먼저 원점위치로 이동후 XYZ 지정위치로 이동함
                    MoveTo(AXIS.CAMERA2_Z, 0.0, _Config.dbOmronCameraZMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 3201:
                    if (!MotionDone(AXIS.CAMERA2_Z)) { break; }

                    MoveTo(AXIS.CAMERA2_X, _SysInfo.dbManualMovePos[0], _Config.dbOmronCameraXYMoveSpeed);
                    MoveTo(AXIS.CAMERA2_Y, _SysInfo.dbManualMovePos[1], _Config.dbOmronCameraXYMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 3202:
                    if (!MotionDone(AXIS.CAMERA2_X) || !MotionDone(AXIS.CAMERA2_Y)) { break; }

                    MoveTo(AXIS.CAMERA2_Z, _SysInfo.dbManualMovePos[2], _Config.dbOmronCameraZMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 3203:
                    if (!MotionDone(AXIS.CAMERA2_Z)) { break; }
                    nProcessStep[nStepIndex] = 0;
                    break;


                // 테이블 0도 복귀
                case 4000:
                    SetDIOPort(DO.STATION3_BREAK_OFF, true);
                    SetDIOPort(DO.STATION3_LOCK_OFF, true);         // 브레이크 해제
                    CAXM.AxmSignalServoOn((int)AXIS.ST3_R, 1);      // 서보 ON
                    tMainTimer[nStepIndex].Start(300);  // 안정화 시간
                    nProcessStep[nStepIndex]++;
                    break;

                case 4001:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    MoveTo(AXIS.ST3_R, 0.0, _ModelInfo.dbST3TurnSpeed, 1);
                    nProcessStep[nStepIndex]++;
                    break;

                case 4002:
                    if (!MotionDone(AXIS.ST3_R)) { break; }
                    // 모션이 완료된다면

                    tMainTimer[nStepIndex].Start(500);  // 안정화 시간을 가짐
                    nProcessStep[nStepIndex]++;
                    break;

                case 4003:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    SetDIOPort(DO.STATION3_BREAK_OFF, true);
                    SetDIOPort(DO.STATION3_LOCK_OFF, false);         // 테이블 락
                    CAXM.AxmSignalServoOn((int)AXIS.ST3_R, 0);      // 서보 OFF
                    tMainTimer[nStepIndex].Start(300);              // 안정화 시간을 가짐
                    nProcessStep[nStepIndex]++;
                    break;

                case 4004:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    nProcessStep[nStepIndex] = 0;       // 매뉴얼 프로세스 종료
                    break;


                // 테이블 180도 회전
                case 4100:
                    SetDIOPort(DO.STATION3_BREAK_OFF, true);
                    SetDIOPort(DO.STATION3_LOCK_OFF, true);         // 브레이크 해제
                    CAXM.AxmSignalServoOn((int)AXIS.ST3_R, 1);      // 서보 ON
                    tMainTimer[nStepIndex].Start(300);  // 안정화 시간
                    nProcessStep[nStepIndex]++;
                    break;

                case 4101:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    MoveTo(AXIS.ST3_R, 180.0, _ModelInfo.dbST3TurnSpeed, 1);
                    nProcessStep[nStepIndex]++;
                    break;

                case 4102:
                    if (!MotionDone(AXIS.ST3_R)) { break; }
                    // 모션이 완료된다면

                    tMainTimer[nStepIndex].Start(500);  // 안정화 시간을 가짐
                    nProcessStep[nStepIndex]++;
                    break;

                case 4103:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    SetDIOPort(DO.STATION3_BREAK_OFF, true);
                    SetDIOPort(DO.STATION3_LOCK_OFF, false);         // 테이블 락
                    CAXM.AxmSignalServoOn((int)AXIS.ST3_R, 0);      // 서보 OFF
                    tMainTimer[nStepIndex].Start(300);              // 안정화 시간을 가짐
                    nProcessStep[nStepIndex]++;
                    break;

                case 4104:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    nProcessStep[nStepIndex] = 0;       // 매뉴얼 프로세스 종료
                    break;


            }
        }



        // 스테이션 3번 로봇 행정
        static void Station3_RobotProcess()
        {
            int nStepIndex = (int)PROC_LIST.ST3_ROBOT;



            // 프로세스
            switch (nProcessStep[nStepIndex])
            {



                // 작업 시작
                case 100:
                    break;




                // 작업 각도 설정
                case 200:
                    break;



                // 1000번대부터 행정 시작
                case 1000:
                    // TPC 로봇 스텟을 홈상태로 만듬
                    _TPCRobot._Stat = TPC_STAT.READY;
                    _TPCRobot.SetHome();    // 로봇을 홈으로 보냄
                    nProcessStep[nStepIndex]++;
                    break;

                case 1001:
                    if (_TPCRobot._Stat == TPC_STAT.HOME)
                    {
                        tMainTimer[nStepIndex].Start(200);
                        nProcessStep[nStepIndex] = 1100;
                    }
                    break;


                // 해당행정에선 모델 선택을 함
                case 1100:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    _TPCRobot.SetModel(_ModelInfo.strST3Model1);
                    tMainTimer[nStepIndex].Start(_Config.nTPCRobotCommTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                // PSELECT 결과를 기다림
                case 1101:
                    // 통신 타임아웃
                    if (tMainTimer[nStepIndex].Verify())
                    {

                    }

                    // 모델 선택 NG
                    if (_TPCRobot._Stat == TPC_STAT.PSELECTNG)
                    {

                    }

                    // 모델 선택 OK
                    if (_TPCRobot._Stat == TPC_STAT.PSELECTOK)
                    {
                        tMainTimer[nStepIndex].Start(200);
                        nProcessStep[nStepIndex] = 1200;
                    }
                    break;


                // TPC로봇 자동행정 시작
                case 1200:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    _TPCRobot.SetStart();
                    nProcessStep[nStepIndex] = 1300;
                    break;

                // 반복 행정
                case 1300:
                    if (_TPCRobot._Stat == TPC_STAT.VNG)
                    {
                        // 비전 NG가 들어왔다면
                        // 재시도 여부 판단 행정
                        nProcessStep[nStepIndex] = 1500;

                    }
                    else if (_TPCRobot._Stat == TPC_STAT.TNG)
                    {
                        // 체결 NG가 들어왔다면
                        // 종료할지 더 할지 설정하는 행정
                        nProcessStep[nStepIndex] = 1600;

                    }
                    else if (_TPCRobot._Stat == TPC_STAT.OK)
                    {
                        // OK가 들어왔다면
                        // 다음 스텝으로 넘어가는 행정
                        nProcessStep[nStepIndex] = 1400;
                    }
                    else if (_TPCRobot._Stat == TPC_STAT.FINISH)
                    {
                        // 완료가 들어왔다면
                        // 종료 행정
                        nProcessStep[nStepIndex] = 1900;
                    }
                    break;

                // 다음 스텝으로 넘어가는 행정
                case 1400:
                    _TPCRobot.SetNext();
                    nProcessStep[nStepIndex] = 1300;
                    break;

                // VISION NG일 경우
                case 1500:
                    // 재작업 하라는 명령이 들어온 경우
                    if (true)
                    {
                        _TPCRobot.SetVresume();
                        nProcessStep[nStepIndex] = 1300;
                    }
                    else
                    {
                        // 종료하라는 명령이 들어온 경우
                        _TPCRobot.SetHome();    // HOME으로 보낸다
                        nProcessStep[nStepIndex] = 1510;
                    }
                    break;

                case 1510:
                    if (_TPCRobot._Stat == TPC_STAT.HOME)
                    {
                        // HOME 위치로 정상적으로 이동한경우
                        nProcessStep[nStepIndex] = 2000;        // 작업을 마무리한다
                    }
                    break;

                // TNG가 들어온경우
                case 1600:
                    if (true)
                    {
                        //다음 포인트 작업하라는 명령이 들어온 경우
                        _TPCRobot.SetNext();
                        nProcessStep[nStepIndex] = 1300;
                    }
                    else
                    {
                        _TPCRobot.SetHome();
                        nProcessStep[nStepIndex] = 1610;
                    }
                    break;

                case 1610:
                    if (_TPCRobot._Stat == TPC_STAT.HOME)
                    {
                        // HOME 위치로 정상적으로 이동한경우
                        nProcessStep[nStepIndex] = 2000;        // 작업을 마무리한다
                    }
                    break;

                // 종료행정
                case 1900:
                    nProcessStep[nStepIndex] = 2000;  // 작업을 마무리한다
                    break;


                // 배출시엔 원점으로 Move
                case 2000:
                    break;
            }

        }

        //====== 로딩 스위치 동작 ===================================
        static void SUB_LOADING_SW()
        {
            int nStepIndex = (int)PROC_LIST.SUB_LOADING_SW;


            switch (nProcessStep[nStepIndex])
            {
                case 0:
                    if (!_SysInfo.bLoadingReadySw && _SysInfo.bInLiftReady)
                    {
                        if (GetDIOPort(DI.LOADING_START_SW))
                        {
                            tMainTimer[nStepIndex].Start(_Config.nChatteringTime);
                            nProcessStep[nStepIndex]++;
                        }
                    }
                    break;

                case 1:
                    if (GetDIOPort(DI.LOADING_START_SW) && tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    else if (!GetDIOPort(DI.LOADING_START_SW))
                    {
                        nProcessStep[nStepIndex] = 0;
                    }
                    break;

                case 2:
                    if (_Config.bUseMainCVMonitor)
                    {
                        if (!GetDIOPort(DI.INVERTER1_RUN))
                        {
                            AppendLogMsg("로딩리프트 - 메인컨베어가 동작중이 아닙니다.", LOG_TYPE.ERROR);
                            _SysInfo.nTL_Beep = 3;
                            nProcessStep[nStepIndex]++;
                            break;
                        }
                        else
                        {
                            if (!GetDIOPort(DI.INLIFT_PRODUCT_BASEPLATE))
                            {
                                AppendLogMsg("로딩리프트 - 파레트 준비가 이뤄지지 않았습니다.", LOG_TYPE.ERROR);
                                _SysInfo.nTL_Beep = 3;
                                nProcessStep[nStepIndex]++;
                                break;
                            }
                            else
                            {
                                _SysInfo.bLoadingReadySw = true;
                                nProcessStep[nStepIndex] = 0;
                            }
                        }
                    }
                    else
                    {
                        if (!GetDIOPort(DI.INLIFT_PRODUCT_BASEPLATE))
                        {
                            AppendLogMsg("로딩리프트 - 파레트 준비가 이뤄지지 않았습니다.", LOG_TYPE.ERROR);
                            _SysInfo.nTL_Beep = 3;
                            nProcessStep[nStepIndex]++;
                            break;
                        }
                        else
                        {
                            _SysInfo.bLoadingReadySw = true;
                            nProcessStep[nStepIndex] = 0;
                        }
                    }
                    break;

                case 3:
                    if (!GetDIOPort(DI.LOADING_START_SW))
                    {
                        nProcessStep[nStepIndex] = 0;
                    }
                    break;

            }

        }
        //===========================================================


        //====== 로딩 프로세스 ======================================
        static void WorkLoadingProcess()
        {

            int nStepIndex = (int)PROC_LIST.CMA_MOVE;


            if (_SysInfo.bLoadingReadySw)
            {
                SetDIOPort(DO.LOADING_START_SW_LAMP, true);
            }
            else
            {
                SetDIOPort(DO.LOADING_START_SW_LAMP, false);
            }

            if (!_SysInfo.bStationAutoMode[(int)STATION_LIST.LOADING])
            {
                _SysInfo.bLoadingReadySw = false;
                nProcessStep[nStepIndex] = 0;


                if (_tSTCycleTimer[(int)STATION_LIST.LOADING].IsRunning)
                {
                    _tSTCycleTimer[(int)STATION_LIST.LOADING].Stop();
                    _tSTCycleEndTime[(int)STATION_LIST.LOADING] = DateTime.Now;
                    SaveStationTactTime(STATION_LIST.LOADING, _tSTCycleStartTime[(int)STATION_LIST.LOADING], _tSTCycleEndTime[(int)STATION_LIST.LOADING], 1);
                }

                return;

            } // 수동모드



            SUB_LOADING_SW();

            switch (nProcessStep[nStepIndex])
            {

                case 0:
                    if (!_SysInfo.bStationAutoMode[(int)STATION_LIST.IN_LIFT])
                    {
                        AppendLogMsg("INLIFT NOT RUNNING!!", LOG_TYPE.ERROR);
                        _SysInfo.nTL_Beep = 3;
                        nProcessStep[nStepIndex] = 9000;
                        break;
                    }
                    else
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 1:
                    _SysInfo.eLoadingInfoSetOk = START_INFO.READY;
                    _mainform.BeginInvoke(new Action(() => _mainform.ViewLoadingStartInfo()));
                    nProcessStep[nStepIndex]++;
                    break;

                case 2:
                    if (_SysInfo.eLoadingInfoSetOk == START_INFO.OK)
                    {
                        nProcessStep[nStepIndex] = 30;

                    }
                    else if (_SysInfo.eLoadingInfoSetOk == START_INFO.CANCEL)
                    {
                        nProcessStep[nStepIndex] = 9000;
                    }
                    break;

                //case 10:
                //    InitMotionXYZ();
                //    _SysInfo.bServoErrMonitorXYZ = false;
                //    for (int i = (int)AXIS.X; i <= (int)AXIS.Z; i++)
                //    {
                //        CAXM.AxmMoveEStop(i);
                //        CAXM.AxmSignalServoOn(i, 0);
                //        _SysInfo.Err_Code &= ~(ERR_CODE)((int)ERR_CODE.X << i);
                //    }

                //    SetDIOPort(DO.Z_BREAK, false);
                //    tMainTimer[nStepIndex].Start(1500);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 11:
                //    if (!tMainTimer[nStepIndex].Verify()) { break; }
                //    SetDIOPort(DO.SERVO_ON, true);
                //    tMainTimer[nStepIndex].Start(2500);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 12:
                //    if (!tMainTimer[nStepIndex].Verify()) { break; }

                //    for (int i = (int)AXIS.X; i <= (int)AXIS.Z; i++)
                //    {
                //        CAXM.AxmSignalServoAlarmReset(i, 1);
                //    }
                //    tMainTimer[nStepIndex].Start(200);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 13:
                //    if (!tMainTimer[nStepIndex].Verify()) { break; }

                //    for (int i = (int)AXIS.X; i <= (int)AXIS.Z; i++)
                //    {
                //        CAXM.AxmSignalServoAlarmReset(i, 0);
                //    }
                //    tMainTimer[nStepIndex].Start(200);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 14:
                //    if (!tMainTimer[nStepIndex].Verify()) { break; }

                //    for (int i = (int)AXIS.X; i <= (int)AXIS.Z; i++)
                //    {
                //        CAXM.AxmSignalServoOn(i, 1);
                //    }
                //    tMainTimer[nStepIndex].Start(200);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 15:
                //    if (!tMainTimer[nStepIndex].Verify()) { break; }

                //    SetDIOPort(DO.Z_BREAK, true);
                //    _SysInfo.bServoErrMonitorXYZ = true;
                //    nProcessStep[nStepIndex] = 20;
                //    break;

                //case 20:
                //    _SysInfo.nMotorCountXYZ = 0;
                //    _Search_XYZ.nAxis[_SysInfo.nMotorCountXYZ++] = (int)AXIS.Z;
                //    _Search_XYZ.nAxisSize = _SysInfo.nMotorCountXYZ;
                //    nProcessStep[(int)STEP_NUM.SUB_HOME_SEARCHXYZ] = 0;
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 21:
                //    if (SUB_SEARCH_HOMEXYZ(true) == -1)
                //    {
                //        _SysInfo.nMotorSearchErrCnXYZt = 0;
                //        for (int i = 0; i < _Search_XYZ.nAxisSize; i++)
                //        {
                //            if (_Search_XYZ.bResult[i])
                //            {
                //                AppendLogMsg(String.Format("{0} 축 홈서치 완료", (AXIS)_Search_XYZ.nAxis[i]), Color.Green);
                //            }
                //            else
                //            {
                //                AppendLogMsg(String.Format("{0} 축 홈서치 실패", (AXIS)_Search_XYZ.nAxis[i]), Color.Red);
                //                _SysInfo.nMotorSearchErrCntXYZ++;
                //            }

                //        }

                //        if (_SysInfo.nMotorSearchErrCntXYZ > 0) nProcessStep[nStepIndex] = 10000;
                //        else nProcessStep[nStepIndex]++;
                //    }
                //    break;

                //case 22:
                //    _SysInfo.nMotorCountXYZ = 0;
                //    _Search_XYZ.nAxis[_SysInfo.nMotorCountXYZ++] = (int)AXIS.X;
                //    _Search_XYZ.nAxis[_SysInfo.nMotorCountXYZ++] = (int)AXIS.Y;
                //    _Search_XYZ.nAxisSize = _SysInfo.nMotorCountXYZ;
                //    nProcessStep[(int)STEP_NUM.SUB_HOME_SEARCHXYZ] = 0;
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 23:
                //    if (SUB_SEARCH_HOMEXYZ(true) == -1)
                //    {
                //        _SysInfo.nMotorSearchErrCntXYZ = 0;
                //        for (int i = 0; i < _Search_XYZ.nAxisSize; i++)
                //        {
                //            if (_Search_XYZ.bResult[i])
                //            {
                //                AppendLogMsg(String.Format("{0} 축 홈서치 완료", (AXIS)_Search_XYZ.nAxis[i]), Color.Green);
                //            }
                //            else
                //            {
                //                AppendLogMsg(String.Format("{0} 축 홈서치 실패", (AXIS)_Search_XYZ.nAxis[i]), Color.Red);
                //                _SysInfo.nMotorSearchErrCntXYZ++;
                //            }

                //        }

                //        if (_SysInfo.nMotorSearchErrCntXYZ > 0) nProcessStep[nStepIndex] = 10000;
                //        else
                //        {
                //            if (_SysInfo.bInitXYZ)
                //            {
                //                _SysInfo.bInitXYZ = false;
                //                nProcessStep[nStepIndex] = 0;
                //            }
                //            else
                //            {
                //                nProcessStep[nStepIndex] = 50;
                //            }
                //            _SysInfo.bInitComplateXYZ = true;
                //        }
                //    }
                //    break;

                case 30:
                    MoveTo(AXIS.Z, _Config.dbSafeLoadZPos, _ModelInfo.dbClampZMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 31:
                    if (!MotionDone(AXIS.Z)) { break; }

                    MoveToXY(_ModelInfo.dbTurnPosX, _ModelInfo.dbTurnPosY, _ModelInfo.dbClampXYMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 32:
                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y)) { break; }

                    nProcessStep[nStepIndex] = 50;
                    break;


                case 50:
                    nProcessStep[nStepIndex]++;
                    break;

                case 51:
                    // 작업 완료후 정지면
                    if (_SysInfo.bAutoCycleStop)
                    {
                        nProcessStep[nStepIndex] = 9000;
                        break;
                    }

                    // 리웍 모드 사용중이라면
                    if (_Config.bUseReworkLineMode)
                    {
                        if (_SysInfo.bInLiftReady && _SysInfo.bLoadingReadySw)
                        {
                            nProcessStep[nStepIndex] = 700;
                        }
                        break;
                    }


                    // 클램프 OFF 상태 제품 없다고 봄
                    if (GetDIOPort(DI.CMA_LOADING_CLAMP1_OFF) || GetDIOPort(DI.CMA_LOADING_CLAMP2_OFF))
                    {
                        // 모델 변경후 첫 로딩이라면
                        if (_ModelInfo.bUseJigTest)
                        {
                            if (_SysInfo.bModelChangeFirstLoading)
                            {
                                nProcessStep[nStepIndex] = 60;
                                break;
                            }

                        }


                        // 클램프 OFF 상태고 , 리프트가 Ready, 로딩스위치가 On 됐고 로딩완료가 아니라면
                        if (_SysInfo.bInLiftReady && _SysInfo.bLoadingReadySw && !_SysInfo.bLoadingComplated)
                        {
                            tMainTimer[nStepIndex].Start(1000);
                            nProcessStep[nStepIndex] = 100;
                        }
                        // 클램프가 OFF 상태고, 리프트가 Ready, 로딩스위치가 On 됐고 로딩완료라면
                        else if (_SysInfo.bInLiftReady && _SysInfo.bLoadingReadySw && (_SysInfo.bLoadingComplated || _Config.bUseReworkLineMode))
                        {
                            // 파레트 배출함
                            nProcessStep[nStepIndex] = 700;
                        }
                    }
                    else if (GetDIOPort(DI.CMA_LOADING_CLAMP1_ON) && GetDIOPort(DI.CMA_LOADING_CLAMP2_ON))
                    {
                        if (_SysInfo.bLoadingComplated || _Config.bUseReworkLineMode)
                        {
                            if (_SysInfo.bInLiftReady && _SysInfo.bLoadingReadySw)
                            {
                                // 파레트 배출함
                                nProcessStep[nStepIndex] = 700;
                            }
                        }
                        else
                        {
                            if (_SysInfo.bInLiftReady && _SysInfo.bLoadingReadySw && _SysInfo.bStationAutoMode[(int)STATION_LIST.IN_LIFT])
                            {
                                // 클램프가 On 된 상태로 작업이 시작되었다면
                                nProcessStep[nStepIndex] = 300; // 적재작업 시작
                            }
                        }

                    }
                    break;

                case 60:
                    if (!MotionDone(AXIS.Z)) { break; }

                    MoveTo(AXIS.Z, _Config.dbSafeLoadZPos, _ModelInfo.dbNoClampZMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 61:
                    if (!MotionDone(AXIS.Z)) { break; }

                    MoveToXY(_ModelInfo.dbTurnPosX, _ModelInfo.dbTurnPosY, _ModelInfo.dbNoClampXYMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 62:
                    // 90도 위치 먼저
                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y)) { break; }

                    MoveTo(AXIS.R, -90.0, _Config.dbTurnSpeed);
                    nProcessStep[nStepIndex]++;
                    break;



                case 63:
                    if (!MotionDone(AXIS.R)) { break; }

                    MoveTo(AXIS.Z, _ModelInfo.dbLoadingJigTestPos1Z, _ModelInfo.dbNoClampZMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 64:
                    if (!MotionDone(AXIS.Z)) { break; }

                    MoveToXY(_ModelInfo.dbLoadingJigTestPos1X, _ModelInfo.dbLoadingJigTestPos1Y, _ModelInfo.dbNoClampXYMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 65:
                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y)) { break; }

                    if (GetDIOPort(DI.LOADING_JIG_POSITION))
                    {
                        nProcessStep[nStepIndex] = 70;
                    }
                    else
                    {
                        AppendLogMsg("LOADING - Jig Position Err", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }
                    break;


                case 70:
                    if (!MotionDone(AXIS.Z)) { break; }

                    MoveTo(AXIS.Z, _Config.dbSafeLoadZPos, _ModelInfo.dbNoClampZMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 71:
                    if (!MotionDone(AXIS.Z)) { break; }

                    MoveToXY(_ModelInfo.dbTurnPosX, _ModelInfo.dbTurnPosY, _ModelInfo.dbNoClampXYMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 72:
                    // -90도 위치 먼저
                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y)) { break; }

                    MoveTo(AXIS.R, 90.0, _Config.dbTurnSpeed);
                    nProcessStep[nStepIndex]++;
                    break;



                case 73:
                    if (!MotionDone(AXIS.R)) { break; }

                    MoveTo(AXIS.Z, _ModelInfo.dbLoadingJigTestPos2Z, _ModelInfo.dbNoClampZMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 74:
                    if (!MotionDone(AXIS.Z)) { break; }

                    MoveToXY(_ModelInfo.dbLoadingJigTestPos2X, _ModelInfo.dbLoadingJigTestPos2Y, _ModelInfo.dbNoClampXYMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 75:
                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y)) { break; }

                    if (GetDIOPort(DI.LOADING_JIG_POSITION))
                    {
                        nProcessStep[nStepIndex] = 80;
                    }
                    else
                    {
                        AppendLogMsg("LOADING - Jig Position Err", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }
                    break;


                case 80:
                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y)) { break; }

                    MoveToXY(_ModelInfo.dbTurnPosX, _ModelInfo.dbTurnPosY, _ModelInfo.dbNoClampXYMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 81:
                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y)) { break; }

                    MoveTo(AXIS.R, 0.0, _Config.dbTurnSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 82:
                    if (!MotionDone(AXIS.R)) { break; }

                    _SysInfo.bModelChangeFirstLoading = false;
                    nProcessStep[nStepIndex] = 50;
                    break;





                case 100:
                    if (_SysInfo.nLoadingWorkIndex >= _ModelInfo._Loading.Length)
                    {
                        // 로딩 인덱스가 실제 카운트보다 많다면
                        //_SysInfo.nLoadingWorkIndex = 0;

                        _SysInfo.bLoadingComplated = true;
                        nProcessStep[nStepIndex] = 50;
                        break;
                    }

                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 50;
                        break;
                    }

                    if (!_ModelInfo._Loading[_SysInfo.nLoadingWorkIndex].bUse)
                    {
                        _SysInfo.nLoadingWorkIndex++;
                        nProcessStep[nStepIndex] = 50;
                        break;
                    }

                    // 전단장비 준비신호가 들어왔다면
                    if ((GetDIOPort(DI.SMEMA_IN1) || !_Config.bUseSemea))
                    {
                        tMainTimer[nStepIndex].Start(100);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 101:
                    if (tMainTimer[nStepIndex].Verify() && (GetDIOPort(DI.SMEMA_IN1) || !_Config.bUseSemea))
                    {
                        // 로딩 작업 시작
                        nProcessStep[nStepIndex] = 200;
                    }
                    else if (!GetDIOPort(DI.SMEMA_IN1) && _Config.bUseSemea)
                    {
                        nProcessStep[nStepIndex] = 50;
                    }
                    break;

                // 전단장비 준비 됐으므로 로딩행정 시작
                case 200:
                    _tSTCycleStartTime[(int)STATION_LIST.LOADING] = DateTime.Now;
                    _tSTCycleTimer[(int)STATION_LIST.LOADING].Restart();
                    SetDIOPort(DO.CMA_LOADING_CLAMP_OFF, true);
                    SetDIOPort(DO.CMA_LOADING_CLAMP_ON, false);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 201:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        if (!GetDIOPort(DI.CMA_LOADING_CLAMP1_OFF)) { AppendTimeOutMsg(DI.CMA_LOADING_CLAMP1_OFF); }
                        if (!GetDIOPort(DI.CMA_LOADING_CLAMP2_OFF)) { AppendTimeOutMsg(DI.CMA_LOADING_CLAMP2_OFF); }
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }

                    if (GetDIOPort(DI.CMA_LOADING_CLAMP1_OFF) && GetDIOPort(DI.CMA_LOADING_CLAMP2_OFF))
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 202:
                    MoveTo(AXIS.Z, _Config.dbSafeLoadZPos, _ModelInfo.dbNoClampZMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 203:
                    if (!MotionDone(AXIS.Z)) { break; }

                    if (CheckMotionPosErr(AXIS.Z, _Config.dbSafeLoadZPos))
                    {
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }

                    // 스킵행정 추가 180220
                    if (Math.Abs(-(_ModelInfo.dbLoadingAngle) - GetNowPos(AXIS.R)) < 1)
                    {
                        nProcessStep[nStepIndex] = 220;
                    }
                    else
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    ///////////

                    //// 실린더가 회전 상태라면
                    //if(GetDioPort(DI.LOADING_ROTATE_ON))
                    //{
                    //    nProcessStep[nStepIndex]++;
                    //}
                    //else
                    //{
                    //    nProcessStep[nStepIndex] = 220;
                    //}

                    //nProcessStep[nStepIndex]++;
                    break;

                // 회전 실린더 원복
                case 204:
                    //if (!GetDIOPort(DI.INLIFT_DOOR)) { break; }

                    MoveToXY(_ModelInfo.dbTurnPosX, _ModelInfo.dbTurnPosY, _ModelInfo.dbNoClampXYMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 205:
                    //if (!GetDIOPort(DI.INLIFT_DOOR))
                    //{
                    //    CAXM.AxmMoveEStop((int)AXIS.X);
                    //    CAXM.AxmMoveEStop((int)AXIS.Y);
                    //    nProcessStep[nStepIndex] = 204;
                    //    break;
                    //}

                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y)) { break; }

                    if (CheckMotionPosErr(AXIS.X, _ModelInfo.dbTurnPosX))
                    {
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }

                    if (CheckMotionPosErr(AXIS.Y, _ModelInfo.dbTurnPosY))
                    {
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }


                    MoveTo(AXIS.R, -(_ModelInfo.dbLoadingAngle), _Config.dbTurnSpeed);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 206:
                    //if (tMainTimer[nStepIndex].Verify())
                    //{
                    //    if (!GetDioPort(DI.LOADING_ROTATE_OFF)) { AppendTimeOutMsg(DI.LOADING_ROTATE_OFF); }
                    //    nProcessStep[nStepIndex] = 10000;
                    //}

                    //if (GetDioPort(DI.LOADING_ROTATE_OFF))
                    //{
                    //    nProcessStep[nStepIndex] = 220;
                    //}

                    if (!MotionDone(AXIS.R)) { break; }


                    if (CheckMotionPosErr(AXIS.R, -(_ModelInfo.dbLoadingAngle)))
                    {
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }

                    nProcessStep[nStepIndex] = 220;
                    break;


                case 220:
                    if (!GetLoadingDoor()) { break; }
                    if (!MotionDone(AXIS.Z)) { break; }

                    MoveToXY(_ModelInfo.dbPackLoadingPointX, _ModelInfo.dbPackLoadingPointY, _ModelInfo.dbNoClampXYMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 221:
                    if (!GetLoadingDoor())
                    {
                        CAXM.AxmMoveEStop((int)AXIS.X);
                        CAXM.AxmMoveEStop((int)AXIS.Y);
                        nProcessStep[nStepIndex] = 220;
                        break;
                    }

                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y)) { break; }

                    if (CheckMotionPosErr(AXIS.X, _ModelInfo.dbPackLoadingPointX))
                    {
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }

                    if (CheckMotionPosErr(AXIS.Y, _ModelInfo.dbPackLoadingPointY))
                    {
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }
                    nProcessStep[nStepIndex]++;
                    break;

                case 222:
                    if (!GetLoadingDoor()) { break; }

                    MoveTo(AXIS.Z, _ModelInfo.dbPackLoadingPointZ, _ModelInfo.dbNoClampZMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 223:
                    if (!GetLoadingDoor())
                    {
                        CAXM.AxmMoveEStop((int)AXIS.Z);
                        nProcessStep[nStepIndex] = 222;
                        break;
                    }

                    if (!GetDIOPort(DI.SMEMA_IN1) && _Config.bUseSemea)
                    {
                        nProcessStep[nStepIndex] = 270;
                        break;
                    }

                    if (!MotionDone(AXIS.Z)) { break; }

                    if (CheckMotionPosErr(AXIS.Z, _ModelInfo.dbPackLoadingPointZ))
                    {
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }

                    nProcessStep[nStepIndex] = 250;
                    break;

                case 224:
                    // 센서가 감지가 안된다면 추가이동
                    Move(AXIS.Z, _Config.dbZSensingHeight, _Config.dbZSensingSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 225:
                    // 가는도중 센서 감지가 된다면 급정지 후 클램프 스탭으로
                    //if (GetDioPort(DI.LOADING_HAND_PRODUCT))
                    //{
                    //    CAXM.AxmMoveEStop((int)AXIS.Z);
                    //    nProcessStep[nStepIndex] = 250;
                    //    break;
                    //}

                    if (!MotionDone(AXIS.Z)) { break; }

                    // 센서 이동을 했음에도 감지가 안된다면 에러처리
                    nProcessStep[nStepIndex] = 10000;
                    break;


                // 클램프 스탭
                case 250:
                    if (!GetDIOPort(DI.SMEMA_IN1) && _Config.bUseSemea)
                    {
                        nProcessStep[nStepIndex] = 270;
                        break;
                    }

                    SetDIOPort(DO.CMA_LOADING_CLAMP_ON, true);
                    SetDIOPort(DO.CMA_LOADING_CLAMP_OFF, false);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 251:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        if (!GetDIOPort(DI.CMA_LOADING_CLAMP1_ON)) { AppendTimeOutMsg(DI.CMA_LOADING_CLAMP1_ON); }
                        if (!GetDIOPort(DI.CMA_LOADING_CLAMP2_ON)) { AppendTimeOutMsg(DI.CMA_LOADING_CLAMP2_ON); }
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }

                    if (GetDIOPort(DI.CMA_LOADING_CLAMP1_ON) && GetDIOPort(DI.CMA_LOADING_CLAMP2_ON))
                    {
                        //SetDIOPort(DO.SMEMA_OUT2, true);    // 가져간다는 신호 보냄
                        SetDIOPort(DO.SMEMA_OUT1, true);    // 가져간다는 신호 보냄
                        tMainTimer[nStepIndex].Start(_Config.nClampStabilTime);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 252:
                    if (!GetDIOPort(DI.SMEMA_IN1) && _Config.bUseSemea)
                    {
                        nProcessStep[nStepIndex] = 270;
                        break;
                    }

                    if (GetDIOPort(DI.SMEMA_IN2) || !_Config.bUseSemea)    // 2번이 들어오면 움직임www
                    {
                        tMainTimer[nStepIndex].Start(200);
                        nProcessStep[nStepIndex] = 255;
                    }
                    break;

                case 255:
                    if (tMainTimer[nStepIndex].Verify() && GetDIOPort(DI.SMEMA_IN2) || !_Config.bUseSemea)
                    {
                        nProcessStep[nStepIndex] = 260;
                    }
                    else if (!GetDIOPort(DI.SMEMA_IN2))
                    {
                        nProcessStep[nStepIndex] = 252;
                    }
                    break;



                case 260:
                    if (!GetDIOPort(DI.SMEMA_IN1) && _Config.bUseSemea)
                    {
                        nProcessStep[nStepIndex] = 270;
                        break;
                    }

                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    // 클램프한 제품 안전위치로 이동
                    MoveTo(AXIS.Z, _Config.dbSafeLoadZPos, _ModelInfo.dbClampZMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 261:
                    if (!MotionDone(AXIS.Z)) { break; }

                    if (CheckMotionPosErr(AXIS.Z, _Config.dbSafeLoadZPos))
                    {
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }

                    // 기존 이타이밍에 신호 OFF 했으나 안전상의 문제로 변경 => 안전위치 이동후 OFF
                    //SetDIOPort(DO.SMEMA_OUT2, false); // 모션 완료됐으면 신호 끔
                    SetDIOPort(DO.SMEMA_OUT1, false); // 모션 완료됐으면 신호 끔
                    nProcessStep[nStepIndex] = 300;
                    break;





                // =================================
                // 작업도중 SMEMA1 OFF시 하는 동작 
                case 270:
                    CAXM.AxmMoveEStop((int)AXIS.Z);
                    SetDIOPort(DO.CMA_LOADING_CLAMP_ON, false);
                    SetDIOPort(DO.CMA_LOADING_CLAMP_OFF, true);  // 클램프 해제

                    AppendLogMsg("전단 장비 예기치 않게 SMEMA1 꺼짐", LOG_TYPE.ERROR);
                    nProcessStep[nStepIndex]++;
                    break;

                case 271:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        if (!GetDIOPort(DI.CMA_LOADING_CLAMP1_OFF)) { AppendTimeOutMsg(DI.CMA_LOADING_CLAMP1_OFF); }
                        if (!GetDIOPort(DI.CMA_LOADING_CLAMP2_OFF)) { AppendTimeOutMsg(DI.CMA_LOADING_CLAMP2_OFF); }
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }

                    if (GetDIOPort(DI.CMA_LOADING_CLAMP1_OFF) && GetDIOPort(DI.CMA_LOADING_CLAMP2_OFF))
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    break;


                case 272:
                    if (!MotionDone(AXIS.Z)) { break; }

                    MoveTo(AXIS.Z, _Config.dbSafeLoadZPos, _ModelInfo.dbClampZMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 273:
                    if (!MotionDone(AXIS.Z)) { break; }

                    //SetDIOPort(DO.PRE_SMEMA_OUT1, false);    // 가져간다는 끔
                    nProcessStep[nStepIndex] = 10000;
                    break;
                //=======================================================



                // 적재 작업 시작
                case 300:
                    if (_SysInfo.nLoadingWorkIndex >= _ModelInfo._Loading.Length)
                    {
                        // 로딩 인덱스가 실제 카운트보다 많다면
                        _SysInfo.bLoadingComplated = true;
                        nProcessStep[nStepIndex] = 50;
                        break;
                    }

                    nProcessStep[(int)PROC_LIST.SUB_LOADING] = 0;
                    nProcessStep[nStepIndex]++;
                    break;

                case 301:
                    if (!GetDIOPort(DI.INLIFT_PRODUCT_BASEPLATE))
                    {
                        AppendLogMsg("BASE PLATE SENSING ERR..", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }
                    else
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 302:
                    // 서브 프로세서 
                    if (SUB_LOADING_PROCESS(_SysInfo.nLoadingWorkIndex) == 0)
                    {
                        if (_SysInfo.bPackLoadFail)
                        {
                            nProcessStep[nStepIndex] = 10000;
                        }
                        else
                        {
                            //_SysInfo.bLoading_View_Complated[_SysInfo.nLoadingWorkIndex] = true;
                            _SysInfo.nLoadingWorkIndex++;
                            if (_SysInfo.nLoadingWorkIndex >= _ModelInfo._Loading.Length)
                            {
                                // 로딩 인덱스가 실제 카운트보다 많다면
                                _SysInfo.bLoadingComplated = true;
                            }
                            nProcessStep[nStepIndex] = 400;
                        }
                    }
                    break;

                // 배치가 끝났다면 픽업위치로 이동
                case 400:

                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y) || !MotionDone(AXIS.Z)) { break; }

                    //MoveTo(AXIS.Z, 5.0, _ModelInfo.dbNoClampZMoveSpeed);
                    //nProcessStep[nStepIndex]++;
                    nProcessStep[nStepIndex] = 410;
                    break;

                //case 401:
                //    if (!MotionDone(AXIS.Z)) { break; }

                //    _SysInfo.nMotorCount = 0;
                //    _Search_XYZ.nAxis[_SysInfo.nMotorCount++] = (int)AXIS.Z;
                //    _Search_XYZ.nAxisSize = _SysInfo.nMotorCount;
                //    nProcessStep[(int)STEP_NUM.SUB_HOME_SEARCHXYZ] = 0;
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 402:
                //    if (SUB_SEARCH_HOMEXYZ(false) == -1)
                //    {
                //        _SysInfo.nMotorSearchErrCnt = 0;
                //        for (int i = 0; i < _Search_XYZ.nAxisSize; i++)
                //        {
                //            if (_Search_XYZ.bResult[i])
                //            {
                //                //AppendLogMsg(String.Format("{0} 축 홈서치 완료", (AXIS)SEARCH_HOME_PARAM.nAxis[i]), Color.Green);
                //            }
                //            else
                //            {
                //                //AppendLogMsg(String.Format("{0} 축 홈서치 실패", (AXIS)SEARCH_HOME_PARAM.nAxis[i]), Color.Red);
                //                _SysInfo.nMotorSearchErrCnt++;
                //            }

                //        }

                //        if (_SysInfo.nMotorSearchErrCnt > 0) nProcessStep[nStepIndex] = 10000;
                //        else nProcessStep[nStepIndex] = 410;
                //    }
                //    break;

                case 410:
                    if (!GetLoadingDoor()) { break; }

                    if (!MotionDone(AXIS.Z)) { break; }

                    MoveTo(AXIS.Z, _Config.dbSafeLoadZPos, _ModelInfo.dbNoClampZMoveSpeed);
                    nProcessStep[nStepIndex] = 420;
                    break;


                // Z축이 다 움직였다면
                case 420:
                    if (!GetLoadingDoor())
                    {
                        CAXM.AxmMoveEStop((int)AXIS.Z);
                        nProcessStep[nStepIndex] = 410;
                        break;
                    }

                    if (!MotionDone(AXIS.Z)) { break; }

                    // 스킵행정 추가 180220
                    if (Math.Abs(-(_ModelInfo.dbLoadingAngle) - GetNowPos(AXIS.R)) < 1)
                    {
                        nProcessStep[nStepIndex] = 450;
                    }
                    else
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    ///////////

                    //if(GetDioPort(DI.LOADING_ROTATE_OFF))
                    //{
                    //    nProcessStep[nStepIndex] = 450;
                    //}
                    //else
                    //{
                    //    nProcessStep[nStepIndex]++;
                    //}

                    //nProcessStep[nStepIndex]++;
                    break;

                case 421:
                    if (!GetLoadingDoor()) { break; }

                    MoveToXY(_ModelInfo.dbTurnPosX, _ModelInfo.dbTurnPosY, _ModelInfo.dbNoClampXYMoveSpeed);
                    MoveTo(AXIS.R, -(_ModelInfo.dbLoadingAngle), _Config.dbTurnSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                // 회전 원복
                case 422:
                    if (!GetLoadingDoor())
                    {
                        CAXM.AxmMoveEStop((int)AXIS.X);
                        CAXM.AxmMoveEStop((int)AXIS.Y);
                        nProcessStep[nStepIndex] = 421;
                        break;
                    }
                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y)) { break; }

                    //SetDIOPort(DO.LOADING_ROTATE_OFF, true);
                    //SetDIOPort(DO.LOADING_ROTATE_ON, false);
                    if (!MotionDone(AXIS.R)) { break; }

                    MoveTo(AXIS.R, -(_ModelInfo.dbLoadingAngle), _Config.dbTurnSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 423:
                    //if (tMainTimer[nStepIndex].Verify())
                    //{
                    //    if (!GetDioPort(DI.LOADING_ROTATE_OFF)) { AppendTimeOutMsg(DI.LOADING_ROTATE_OFF); }
                    //    nProcessStep[nStepIndex] = 10000;
                    //}

                    //if (GetDioPort(DI.LOADING_ROTATE_OFF))
                    //{
                    //    nProcessStep[nStepIndex] = 450;
                    //}
                    if (!MotionDone(AXIS.R)) { break; }
                    _tSTCycleEndTime[(int)STATION_LIST.LOADING] = DateTime.Now;
                    _tSTCycleTimer[(int)STATION_LIST.LOADING].Stop();
                    SaveStationTactTime(STATION_LIST.LOADING, _tSTCycleStartTime[(int)STATION_LIST.LOADING], _tSTCycleEndTime[(int)STATION_LIST.LOADING], 0);
                    nProcessStep[nStepIndex] = 450;
                    break;





                case 450:
                    if (!GetLoadingDoor()) { break; }
                    if (!MotionDone(AXIS.Z)) { break; }

                    // 로딩 대기위치로 이동
                    MoveToXY(_ModelInfo.dbPackLoadingPointX, _ModelInfo.dbPackLoadingPointY, _ModelInfo.dbNoClampXYMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 451:
                    if (!GetLoadingDoor())
                    {
                        CAXM.AxmMoveEStop((int)AXIS.X);
                        CAXM.AxmMoveEStop((int)AXIS.Y);
                        nProcessStep[nStepIndex] = 450;
                        break;
                    }

                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y) || !MotionDone(AXIS.Z)) { break; }

                    nProcessStep[nStepIndex] = 460;
                    break;

                case 460:
                    if (_SysInfo.nLoadingWorkIndex == _ModelInfo.nLoadingStopProduct)
                    {
                        _SysInfo.nCount_Beep[6] = 3;
                        nProcessStep[nStepIndex]++;
                    }
                    else
                    {
                        nProcessStep[nStepIndex] = 50;
                    }
                    break;

                case 461:
                    if (_SysInfo.bAutoCycleStop)
                    {
                        nProcessStep[nStepIndex] = 9000;
                        break;
                    }

                    if (GetDIOPort(DI.LOADING_START_SW))
                    {
                        tMainTimer[nStepIndex].Start(200);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 462:
                    if (GetDIOPort(DI.LOADING_START_SW) && tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 50;
                    }
                    else if (!GetDIOPort(DI.LOADING_START_SW))
                    {
                        nProcessStep[nStepIndex] = 461;
                    }
                    break;


                // 파레트 배출 확인 프로세스
                case 700:
                    // 작업 완료후 정지면
                    if (_SysInfo.bAutoCycleStop)
                    {
                        nProcessStep[nStepIndex] = 9000;
                        break;
                    }

                    if (_SysInfo.bLiftOutComplated)
                    {
                        _SysInfo.bLiftOutComplated = false;
                        _SysInfo.bLoadingComplated = false;
                        _SysInfo.bLoading_ing = false;
                        _SysInfo.bLoadingReadySw = false;
                        _SysInfo.nLoadingWorkIndex = 0;
                        //for (int i = 0; i < 14; i++)
                        //{
                        //    _SysInfo.bLoading_View_Ing[i] = false;
                        //    _SysInfo.bLoading_View_Complated[i] = false;
                        //}
                        nProcessStep[nStepIndex] = 50;

                    }
                    break;

                case 9000:
                    _SysInfo.bStationAutoMode[(int)STATION_LIST.LOADING] = false;
                    break;

                case 10000:
                    nProcessStep[nStepIndex] = 9000;
                    _SysInfo.TL_Buzzer = TOWER_LAMP.TL_ON;
                    break;
            }
        }
        //===========================================================

        //====== STATION 6 ==========================================
        static void WorkHipotProcess()
        {
            int nStepIndex = (int)PROC_LIST.ST6;

            if (!_SysInfo.bStationAutoMode[(int)STATION_LIST.ST6])
            {
                _tHipotTimer.Stop();
                _SysInfo.ST_Red[0] = TOWER_LAMP.TL_OFF;
                _SysInfo.ST_Green[0] = TOWER_LAMP.TL_OFF;
                _SysInfo.ST_Yellow[0] = TOWER_LAMP.TL_OFF;
                _SysInfo.ST_Buzzer[0] = TOWER_LAMP.TL_OFF;

                _SysInfo.ST_TL_RED[0] = TOWER_LAMP.TL_OFF;
                _SysInfo.ST_TL_YELLOW[0] = TOWER_LAMP.TL_OFF;
                _SysInfo.ST_TL_GREEN[0] = TOWER_LAMP.TL_OFF;
                nProcessStep[nStepIndex] = 0;

                if (_tSTCycleTimer[(int)STATION_LIST.ST6].IsRunning)
                {
                    _tSTCycleTimer[(int)STATION_LIST.ST6].Stop();
                    _tSTCycleEndTime[(int)STATION_LIST.ST6] = DateTime.Now;
                    SaveStationTactTime(STATION_LIST.ST6, _tSTCycleStartTime[(int)STATION_LIST.ST6], _tSTCycleEndTime[(int)STATION_LIST.ST6], 1);
                }

                return;

            } // 수동모드

             if(_ModelInfo.bUseAutoContect == true && _ModelInfo.bUseManualContect == false)
            {
                _SysInfo.nHioptContectP = _Config.nAutoChannelP;
                _SysInfo.nHioptContectN = _Config.nAutoChannelN;
            }
            else if(_ModelInfo.bUseAutoContect == false && _ModelInfo.bUseManualContect == true)
            {
                _SysInfo.nHioptContectP = _Config.nManualChannelP;
                _SysInfo.nHioptContectN = _Config.nManualChannelN;
            }


            SUB_CONTACT_SW(0);


            if (nProcessStep[nStepIndex] > 410 && nProcessStep[nStepIndex] < 480)
            {
                if (!GetDIOPort(DI.MAIN_DOOR2) && _Config.bUseHipotDoor)
                {
                    _HipotTester.TestStop();
                    AppendLogMsg("HIPOT 검사도중 문열림 발생!!", LOG_TYPE.ERROR);
                    nProcessStep[nStepIndex] = 10000;
                }
            }


            switch (nProcessStep[nStepIndex])
            {
                case 0:
                    tMainTimer[nStepIndex].Start(10000);
                    nProcessStep[nStepIndex]++;
                    break;


                case 1:
                    //if (!_SysInfo.bAlive)
                    //{
                    //    AppendLogMsg(String.Format("Station #HIPOT - {0}", OutputLogMsg(OutPutMessage.MASTER_PC_NG)), LOG_TYPE.ERROR);
                    //    nProcessStep[nStepIndex] = 9000;
                    //    break;
                    //}

                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("하이팟 테스터 초기화 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 9000;
                        break;
                    }


                    if (!_HipotTester.port.IsOpen)
                    {
                        AppendLogMsg("하이팟 테스터 연결 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 9000;
                        break;
                    }

                    if (_HipotTester.DeviceInit())
                    {
                        _SysInfo.bChangeHipotInfo = true;
                        tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                        nProcessStep[nStepIndex] = 10;
                    }
                    break;

                case 10:
                    if (GetDIOPort(DI.HIPOT_PALLET))
                    {
                        _SysInfo.eChargeStartInfo[5] = START_INFO.READY;
                        _mainform.BeginInvoke(new Action(() => _mainform.ViewTesterStartInfo(5)));
                        nProcessStep[nStepIndex]++;
                        break;
                    }
                    else
                    {

                        nProcessStep[nStepIndex] = 60;
                    }
                    break;

                case 11:
                    if (_SysInfo.eChargeStartInfo[5] == START_INFO.OK)
                    {
                        _SysInfo.bNeedHipotMessageView = false;
                        nProcessStep[nStepIndex] = 60;
                    }
                    else if (_SysInfo.eChargeStartInfo[5] == START_INFO.CANCEL)
                    {
                        nProcessStep[nStepIndex] = 9000;
                    }
                    break;



                case 60:
                    MoveTo(AXIS.HIPOT_1X, _ModelInfo._TestInfo[0].dbReadyPos1X, _Config.dbTestZoneMoveSpeed);
                    MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbReadyPos2X, _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 61:
                    if (!MotionDone(AXIS.HIPOT_1X) || !MotionDone(AXIS.HIPOT_2X)) { break; }
                    {
                        double dbNowPos1Z = 0;
                        CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_1Z, ref dbNowPos1Z);

                        double dbSpeed = 0;
                        dbSpeed = (Math.Abs(_ModelInfo._TestInfo[0].dbReadyPos1Z - dbNowPos1Z) > _Config.dbTestZoneContactZSlowMovePos) ? _Config.dbTestZoneContactZSlowMoveSpeed : _Config.dbTestZoneMoveSpeed;
                        MoveTo(AXIS.HIPOT_1Z, _ModelInfo._TestInfo[0].dbReadyPos1Z, dbSpeed);
                    }
                    {
                        double dbNowPos1Z = 0;
                        CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_2Z, ref dbNowPos1Z);

                        double dbSpeed = 0;
                        dbSpeed = (Math.Abs(_ModelInfo._TestInfo[0].dbReadyPos2Z - dbNowPos1Z) > _Config.dbTestZoneContactZSlowMovePos) ? _Config.dbTestZoneContactZSlowMoveSpeed : _Config.dbTestZoneMoveSpeed;
                        MoveTo(AXIS.HIPOT_2Z, _ModelInfo._TestInfo[0].dbReadyPos2Z, dbSpeed);
                    }


                    nProcessStep[nStepIndex]++;
                    break;

                case 62:
                    if (!MotionDone(AXIS.HIPOT_1Z) || !MotionDone(AXIS.HIPOT_2Z)) { break; }
                    MoveTo(AXIS.HIPOT_1Y, _ModelInfo._TestInfo[0].dbReadyPos1Y, _Config.dbTestZoneMoveSpeed);
                    MoveTo(AXIS.HIPOT_2Y, _ModelInfo._TestInfo[0].dbReadyPos2Y, _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 63:
                    if (!MotionDone(AXIS.HIPOT_1Y) || !MotionDone(AXIS.HIPOT_2Y)) { break; }


                    nProcessStep[nStepIndex]++;
                    break;

                case 64:

                    nProcessStep[nStepIndex]++;
                    break;

                case 65:
                    _SysInfo.bContact_ing[0] = false;
                    nProcessStep[nStepIndex] = 100;
                    break;

                case 100:
                    // 작업 완료후 정지면
                    if (_SysInfo.bAutoCycleStop)
                    {
                        nProcessStep[nStepIndex] = 9000;
                        break;
                    }
                    // 일반적인 상황에선 스토퍼 상승
                    SetDIOPort(DO.HIPOT_STOPPER_DW, false);



                    // 리프트가 하강 상태라면
                    if (GetDIOPort(DI.HIPOT_PALLET_DW))
                    {
                        if (!GetDIOPort(DI.HIPOT_PALLET))
                        {
                            nProcessStep[nStepIndex] = 200;
                        }
                        else
                        {
                            // ST 6일경우 불량 바이패스 

                            if (_SysInfo.bNeedHipotMessageView)
                            {
                                nProcessStep[nStepIndex] = 10;
                                break;
                            }

                            if (_ModelInfo.bHipotSkip)
                            {
                                tMainTimer[nStepIndex].Start(1000);
                                nProcessStep[nStepIndex] = 110;
                                break;
                            }


                            // 충방전 불량 제품일 경우 바이패스
                            if (_ModelInfo.bUseScanSTTester && !_SysInfo.bScanSTTestOKNG[(int)STATION_LIST.ST6])
                            {
                                tMainTimer[nStepIndex].Start(1000);
                                nProcessStep[nStepIndex] = 110;
                                break;
                            }

                            nProcessStep[nStepIndex] = 250;
                        }
                    }
                    // 리프트가 상승 상태
                    else if (GetDIOPort(DI.HIPOT_PALLET_UP))
                    {
                        //파레트 감지가 안된다면
                        if (!GetDIOPort(DI.HIPOT_PALLET))
                        {
                            nProcessStep[nStepIndex] = 300;
                        }
                        // 그외 상황에선 컨텍 작업 수행함
                        else
                        {
                            // 컨택 작업 중이 아니면 컨텍만 작업 혹은 패스 가능
                            if (!_SysInfo.bContact_ing[0])
                            {
                                _SysInfo.eContactStatus[0] = CONTACT_STATUS.CONTACT_READY;
                                nProcessStep[nStepIndex] = 400;


                            }
                            // 컨텍 작업 중이면 컨텍 해제만 작업 가능
                            else
                            {
                                nProcessStep[nStepIndex] = 500;
                            }



                        }
                    }
                    break;

                case 110:
                    if (tMainTimer[nStepIndex].Verify()) { nProcessStep[nStepIndex] = 100; }

                    tCVTimer.Start(_Config.nCVAutoStopTime);
                    if (GetDIOPort(DI.EOL_PALLET_DW) && !GetDIOPort(DI.EOL_PALLET) && (GetDIOPort(DI.INVERTER1_RUN) || !_Config.bUseMainCVMonitor) && _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7])
                    {
                        SetDIOPort(DO.HIPOT_STOPPER_DW, true);
                        nProcessStep[nStepIndex] = 750;
                    }
                    break;


                // 리프트가 하강상태고 파레트가 감지가 안된다면
                // 전단 장비에 Pallet Call 함
                case 200:
                    tMainTimer[nStepIndex].Start(3000);
                    _SysInfo.bContactTestOk[0] = false;
                    _SysInfo.bAutoContactComplated[0] = false;
                    _SysInfo.bPrePalletCall[(int)STATION_LIST.ST6] = true;   // 파레트 Call 플래그를 듬
                    nProcessStep[nStepIndex]++;
                    break;

                case 201:
                    if (GetDIOPort(DI.HIPOT_PALLET))    // 시그널 오기전에 감지 될경우
                    {
                        _SysInfo.bNeedHipotMessageView = true;
                        nProcessStep[nStepIndex] = 100;
                    }

                    // 전단장비에서 배출한다는 시그널이 들어온다면
                    if (_SysInfo.bNextPalletOut[(int)STATION_LIST.ST6 - 1])
                    {
                        _SysInfo.bNextPalletOut[(int)STATION_LIST.ST6 - 1] = false;
                        _SysInfo.bPrePalletCall[(int)STATION_LIST.ST6] = false;
                        nProcessStep[nStepIndex] = 210;
                    }
                    break;

                // 파레트 들어올때까지 대기
                case 210:
                    if (_SysInfo.bAutoCycleStop) // 검사중 정지가 된다면
                    {
                        nProcessStep[nStepIndex] = 9000;
                        break;
                    }

                    if (GetDIOPort(DI.HIPOT_PALLET))
                    {
                        _tSTCycleTimer[(int)STATION_LIST.ST6].Restart();
                        _tSTCycleStartTime[(int)STATION_LIST.ST6] = DateTime.Now;
                        _SysInfo.bNeedHipotMessageView = false;
                        nProcessStep[nStepIndex] = 100;
                    }
                    break;

                // =========================================
                // 리프트가 하강상태
                // 파레트 투입을 기다림
                case 250:
                    tMainTimer[nStepIndex].Start(1000);
                    nProcessStep[nStepIndex]++;
                    break;

                case 251:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 100;
                        break;
                    }

                    // 파레트가 들어온다면
                    if (GetDIOPort(DI.HIPOT_PALLET))
                    {
                        tMainTimer[nStepIndex].Start(1000); // 1초간 더 대기
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 252:
                    if (GetDIOPort(DI.HIPOT_PALLET) && tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex]++;     // 파레트가 1초간 감지된다면
                    }
                    else if (!GetDIOPort(DI.HIPOT_PALLET))
                    {
                        nProcessStep[nStepIndex] = 100;
                    }
                    break;

                case 253:
                    SetDIOPort(DO.HIPOT_PRODUCT_PUSH_ON, false);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 254:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 10000;
                        if (!GetDIOPort(DI.HIPOT_PRODUCT_PUSH1_OFF)) AppendTimeOutMsg(DI.HIPOT_PRODUCT_PUSH1_OFF);      // 리프트 상승 타임아웃
                        if (!GetDIOPort(DI.HIPOT_PRODUCT_PUSH2_OFF)) AppendTimeOutMsg(DI.HIPOT_PRODUCT_PUSH2_OFF);      // 리프트 상승 타임아웃
                    }

                    if (GetDIOPort(DI.HIPOT_PRODUCT_PUSH1_OFF) && GetDIOPort(DI.HIPOT_PRODUCT_PUSH2_OFF))
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 255:
                    // 리프트 상승
                    _SysInfo.nOSCRetryNowCount = 0;
                    SetDIOPort(DO.HIPOT_PALLET_UP, true);
                    SetDIOPort(DO.HIPOT_PALLET_DW, false);

                    // 생산성 향상관련 행정 변경 19.11.06
                    if (_ModelInfo.bUseHipotAutoContact && _ModelInfo.bUseHipotBCDScanner)
                    {
                        MoveTo(AXIS.HIPOT_2Y, _ModelInfo._TestInfo[0].dbSpare_b[1], _Config.dbTestZoneMoveSpeed);
                        {
                            double dbNowPos1Z = 0;
                            CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_2Z, ref dbNowPos1Z);

                            double dbSpeed = 0;
                            dbSpeed = (Math.Abs(_ModelInfo._TestInfo[0].dbSpare_b[2] - dbNowPos1Z) > _Config.dbTestZoneContactZSlowMovePos) ? _Config.dbTestZoneContactZSlowMoveSpeed : _Config.dbTestZoneMoveSpeed;
                            MoveTo(AXIS.HIPOT_2Z, _ModelInfo._TestInfo[0].dbSpare_b[2], dbSpeed);
                        }
                    }

                    _SysInfo.bStationReservation[(int)STATION_LIST.ST6] = false;
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 256:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 10000;
                        AppendTimeOutMsg(DI.HIPOT_PALLET_UP);      // 리프트 상승 타임아웃
                    }
                    //if (!_SysInfo.bAlive)
                    //{
                    //    AppendLogMsg(String.Format("Station #HIPOT - {0}", OutputLogMsg(OutPutMessage.MASTER_PC_NG)), LOG_TYPE.ERROR);
                    //    nProcessStep[nStepIndex] = 10000;
                    //    break;
                    //}

                    if (GetDIOPort(DI.HIPOT_PALLET_UP))
                    {

                        nProcessStep[nStepIndex] = 100;

                    }
                    break;



                //================================================



                // =========================================
                // 리프트가 상승상태
                // 파레트가 없다면 리프트를 하강 시킴
                case 300:
                    tMainTimer[nStepIndex].Start(1000); // 1초동안 파레트가 감지가 안된다면
                    nProcessStep[nStepIndex]++;
                    break;

                case 301:
                    if (!GetDIOPort(DI.HIPOT_PALLET) && tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    else if (GetDIOPort(DI.HIPOT_PALLET))
                    {
                        nProcessStep[nStepIndex] = 100;
                    }
                    break;

                case 302:
                    SetDIOPort(DO.HIPOT_PRODUCT_PUSH_ON, false);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 303:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 10000;
                        if (!GetDIOPort(DI.HIPOT_PRODUCT_PUSH1_OFF)) AppendTimeOutMsg(DI.HIPOT_PRODUCT_PUSH1_OFF);      // 리프트 상승 타임아웃
                        if (!GetDIOPort(DI.HIPOT_PRODUCT_PUSH2_OFF)) AppendTimeOutMsg(DI.HIPOT_PRODUCT_PUSH2_OFF);      // 리프트 상승 타임아웃
                    }

                    if (GetDIOPort(DI.HIPOT_PRODUCT_PUSH1_OFF) && GetDIOPort(DI.HIPOT_PRODUCT_PUSH2_OFF))
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 304:
                    SetDIOPort(DO.HIPOT_PALLET_DW, true);
                    SetDIOPort(DO.HIPOT_PALLET_UP, false);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 305:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 10000;
                        AppendTimeOutMsg(DI.HIPOT_PALLET_DW);      // 리프트 하강 타임아웃
                    }

                    if (GetDIOPort(DI.HIPOT_PALLET_DW))
                    {
                        nProcessStep[nStepIndex] = 100;
                    }
                    break;
                //================================================



                // =========================================
                // 리프트가 상승상태
                // 컨텍 작업중이 아니라면 컨텍 스위치 입력 대기
                case 400:
                    _SysInfo.ST_Yellow[0] = TOWER_LAMP.TL_BLINK;
                    _SysInfo.ST_Red[0] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_Green[0] = TOWER_LAMP.TL_OFF;

                    _HipotHandReader.bReadOk = false;

                    if (_ModelInfo.bUseOmronHipotTest && !_SysInfo.bContactOneTime[0])
                    {
                        nProcessStep[nStepIndex] = 2000;
                    }
                    else
                    {
                        tMainTimer[nStepIndex].Start(1000);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 401:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 100;
                    }

                    // 배출예약을 사용하고 검사 OK 경우
                    if (_Config.bUseStationReservation && !_SysInfo.bContact_ing[0])
                    {
                        // 예약상태이고
                        if (_SysInfo.bStationReservation[(int)STATION_LIST.ST6])
                        {
                            tCVTimer.Start(_Config.nCVAutoStopTime);
                            // 다음 스테이션이 준비 되었을때 배출함
                            if (GetDIOPort(DI.EOL_PALLET_DW) && !GetDIOPort(DI.EOL_PALLET) && (GetDIOPort(DI.INVERTER1_RUN) || !_Config.bUseMainCVMonitor) && _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7])
                            {
                                _SysInfo.bContactTestOk[0] = false;
                                nProcessStep[nStepIndex] = 750;
                            }

                        }


                    }

                    //if (_ModelInfo.bTestStationSkip[0])
                    //{
                    //    tCVTimer.Start(_Config.nCVAutoStopTime);
                    //    // 다음 스테이션이 준비 되었을때 배출함
                    //    if (GetDIOPort(DI.EOL_PALLET_DW) && !GetDIOPort(DI.EOL_PALLET) && (GetDIOPort(DI.INVERTER1_RUN) || !_Config.bUseMainCVMonitor) && _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7])
                    //    {
                    //        _SysInfo.bContactTestOk[0] = false;
                    //        nProcessStep[nStepIndex] = 750;
                    //    }
                    //    break;
                    //}

                    // PASS 작업 스위치 신호가 들어온다면
                    if (GetDIOPort(DI.HIPOT_FINISH_SW))
                    {
                        nProcessStep[nStepIndex] = 700;
                    }

                    // 컨텍 작업 스위치 신호가 들어온다면
                    if (GetDIOPort(DI.HIPOT_READY_SW) || (_ModelInfo.bUseHipotAutoContact && !_SysInfo.bAutoContactComplated[0]))
                    {
                        nProcessStep[nStepIndex]++;

                        if (_ModelInfo.bUseHipotAutoContact && !_SysInfo.bAutoContactComplated[0])
                        {
                            if (!_SysInfo.bContactOneTime[0])
                            {
                                if (_Config.bUseNoProductPass && !GetDIOPort(DI.HIPOT_PRODUCT))
                                {
                                    nProcessStep[nStepIndex] = 405;
                                }
                                else
                                {
                                    _HipotResult.Clear();
                                    _SysInfo.bAutoContactComplated[0] = true;
                                    nProcessStep[nStepIndex] = 1500;
                                }
                            }

                        }
                    }

                    if (_ModelInfo.bUseHipotHandReader && _HipotHandReader.bReadOk)
                    {
                        _HipotHandReader.bReadOk = false;
                        if (CheckContactBCDInfo(_HipotHandReader.strReadBarcode, _ModelInfo.strLaserReadBmaSymbol))
                        {
                            _HipotResult.Clear();
                            _HIPOTReader.strReadBarcode = _HipotHandReader.strReadBarcode;
                            _HipotResult.strBCD = _HIPOTReader.strReadBarcode;
                            nProcessStep[nStepIndex] = 1500;
                        }
                        else
                        {
                            AppendLogMsg("HIPOT - 바코드 정보가 일치하지 않습니다.", LOG_TYPE.ERROR);
                            _SysInfo.nTL_Beep = 3;
                            break;
                        }
                    }


                    break;


                case 402:
                    tMainTimer[nStepIndex].Start(_Config.nChatteringTime);  // 채터링 방지 시간
                    nProcessStep[nStepIndex]++;
                    break;

                case 403:
                    if (GetDIOPort(DI.HIPOT_READY_SW) && tMainTimer[nStepIndex].Verify())
                    {
                        _HipotResult.Clear();
                        nProcessStep[nStepIndex] = 1500;
                    }
                    else if (!GetDIOPort(DI.HIPOT_READY_SW))
                    {
                        nProcessStep[nStepIndex] = 100;
                    }
                    break;

                // 제품없을때 배출
                case 405:
                    if (!GetDIOPort(DI.EOL_PALLET) && GetDIOPort(DI.EOL_PALLET_DW) && _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7])
                    {

                        tCVTimer.Start(_Config.nCVAutoStopTime);
                        if (!GetDIOPort(DI.EOL_PALLET) && GetDIOPort(DI.EOL_PALLET_DW) && (GetDIOPort(DI.INVERTER1_RUN) || !_Config.bUseMainCVMonitor) && _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7])
                        {
                            nProcessStep[nStepIndex] = 750;
                        }
                    }
                    break;


                // 컨텍 작업 시작
                case 410:
                    _SysInfo.bContactTestOk[0] = false;
                    _SysInfo.bContact_ing[0] = true;
                    _SysInfo.ST_Yellow[0] = TOWER_LAMP.TL_ON;
                    _SysInfo.ST_Red[0] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_Green[0] = TOWER_LAMP.TL_OFF;

                    _SysInfo.ST_TL_RED[0] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_TL_YELLOW[0] = TOWER_LAMP.TL_ON;
                    _SysInfo.ST_TL_GREEN[0] = TOWER_LAMP.TL_OFF;
                    _tHipotTimer.Restart();


                    nProcessStep[nStepIndex]++;
                    break;

                case 411:
                    if (!_ModelInfo.bUseHipot1UpDwContact)
                    {
                        MoveTo(AXIS.HIPOT_1X, _ModelInfo._TestInfo[0].dbReadyPos1X, _Config.dbTestZoneMoveSpeed);
                    }
                    else
                    {
                        MoveTo(AXIS.HIPOT_1Z, _ModelInfo._TestInfo[0].dbReadyPos1Z, _Config.dbTestZoneMoveSpeed);
                    }
                    MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbReadyPos2X, _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 412:
                    if (!MotionDone(AXIS.HIPOT_1X) || !MotionDone(AXIS.HIPOT_2X) || !MotionDone(AXIS.HIPOT_1Z) || !MotionDone(AXIS.HIPOT_1Y)) { break; }
                    if (!_ModelInfo.bUseHipot1UpDwContact)
                    {
                        MoveTo(AXIS.HIPOT_1Y, _ModelInfo._TestInfo[0].dbContactPos1Y, _Config.dbTestZoneMoveSpeed);
                        {
                            double dbNowPos1Z = 0;
                            CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_1Z, ref dbNowPos1Z);

                            double dbSpeed = 0;
                            dbSpeed = (Math.Abs(_ModelInfo._TestInfo[0].dbContactPos1Z - dbNowPos1Z) > _Config.dbTestZoneContactZSlowMovePos) ? _Config.dbTestZoneContactZSlowMoveSpeed : _Config.dbTestZoneMoveSpeed;
                            MoveTo(AXIS.HIPOT_1Z, _ModelInfo._TestInfo[0].dbContactPos1Z, dbSpeed);
                        }

                    }
                    else
                    {
                        MoveTo(AXIS.HIPOT_1X, _ModelInfo._TestInfo[0].dbContactPos1X, _Config.dbTestZoneMoveSpeed);
                        MoveTo(AXIS.HIPOT_1Y, _ModelInfo._TestInfo[0].dbContactPos1Y, _Config.dbTestZoneMoveSpeed);
                    }


                    MoveTo(AXIS.HIPOT_2Y, _ModelInfo._TestInfo[0].dbContactPos2Y, _Config.dbTestZoneMoveSpeed);
                    {
                        double dbNowPos1Z = 0;
                        CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_2Z, ref dbNowPos1Z);

                        double dbSpeed = 0;
                        dbSpeed = (Math.Abs(_ModelInfo._TestInfo[0].dbContactPos2Z - dbNowPos1Z) > _Config.dbTestZoneContactZSlowMovePos) ? _Config.dbTestZoneContactZSlowMoveSpeed : _Config.dbTestZoneMoveSpeed;
                        MoveTo(AXIS.HIPOT_2Z, _ModelInfo._TestInfo[0].dbContactPos2Z, dbSpeed);
                    }


                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 413:
                    if (!MotionDone(AXIS.HIPOT_1Y) || !MotionDone(AXIS.HIPOT_1Z) || !MotionDone(AXIS.HIPOT_1X) || !MotionDone(AXIS.HIPOT_2Y) || !MotionDone(AXIS.HIPOT_2Z)) { break; }

                    //if (_ModelInfo._TestInfo[0].dbContactPos1X - _ModelInfo._TestInfo[0].dbReadyPos1X > _Config.dbTestZoneContactMovePos)
                    //{
                    //    MoveTo(AXIS.HIPOT_1X, _ModelInfo._TestInfo[0].dbContactPos1X - _Config.dbTestZoneContactMovePos, _Config.dbTestZoneMoveSpeed);
                    //}

                    //if (_ModelInfo._TestInfo[0].dbContactPos2X - _ModelInfo._TestInfo[0].dbReadyPos2X > _Config.dbTestZoneContactMovePos)
                    //{
                    //    MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbContactPos2X - _Config.dbTestZoneContactMovePos, _Config.dbTestZoneMoveSpeed);
                    //}
                    //if (_ModelInfo.bUseHipot1Distance && _ModelInfo.bUseHipotBCDScanner)
                    //{
                    //    if ((_ModelInfo._TestInfo[0].dbContactPos1X - _SysInfo.dbHipot1DistanceGap) - _ModelInfo._TestInfo[0].dbReadyPos1X > _Config.dbTestZoneContactMovePos)
                    //    {
                    //        MoveTo(AXIS.HIPOT_1X, (_ModelInfo._TestInfo[0].dbContactPos1X - _SysInfo.dbHipot1DistanceGap) - _Config.dbTestZoneContactMovePos, _Config.dbTestZoneMoveSpeed);
                    //    }

                    //    if ((_ModelInfo._TestInfo[0].dbContactPos2X + _SysInfo.dbHipot1DistanceGap) - _ModelInfo._TestInfo[0].dbReadyPos2X > _Config.dbTestZoneContactMovePos)
                    //    {
                    //        MoveTo(AXIS.HIPOT_2X, (_ModelInfo._TestInfo[0].dbContactPos2X + _SysInfo.dbHipot1DistanceGap) - _Config.dbTestZoneContactMovePos, _Config.dbTestZoneMoveSpeed);
                    //    }
                    //}
                    //else
                    //{
                    if (!_ModelInfo.bUseHipot1UpDwContact)
                    {
                        if (_ModelInfo._TestInfo[0].dbContactPos1X - _ModelInfo._TestInfo[0].dbReadyPos1X > _Config.dbTestZoneContactMovePos)
                        {
                            MoveTo(AXIS.HIPOT_1X, _ModelInfo._TestInfo[0].dbContactPos1X - _Config.dbTestZoneContactMovePos, _Config.dbTestZoneMoveSpeed);
                        }
                    }
                    else
                    {
                        if (_ModelInfo._TestInfo[0].dbContactPos1Z - _ModelInfo._TestInfo[0].dbReadyPos1Z > _Config.dbTestZoneContactMovePos)
                        {
                            MoveTo(AXIS.HIPOT_1Z, _ModelInfo._TestInfo[0].dbContactPos1Z - _Config.dbTestZoneContactMovePos, _Config.dbTestZoneMoveSpeed);
                        }
                    }

                    if (_ModelInfo._TestInfo[0].dbContactPos2X - _ModelInfo._TestInfo[0].dbReadyPos2X > _Config.dbTestZoneContactMovePos)
                        {
                            MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbContactPos2X - _Config.dbTestZoneContactMovePos, _Config.dbTestZoneMoveSpeed);
                        }
                    //}
                    nProcessStep[nStepIndex]++;
                    break;



                case 414:
                    if (!MotionDone(AXIS.HIPOT_1X) || !MotionDone(AXIS.HIPOT_2X) || !MotionDone(AXIS.HIPOT_1Z)) { break; }

                    //MoveTo(AXIS.HIPOT_1X, _ModelInfo._TestInfo[0].dbContactPos1X, _Config.dbTestZoneContactSpeed);
                    //MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbContactPos2X, _Config.dbTestZoneContactSpeed);

                    //if (_ModelInfo.bUseHipot1Distance && _ModelInfo.bUseHipotBCDScanner)
                    //{
                    //    MoveTo(AXIS.HIPOT_1X, (_ModelInfo._TestInfo[0].dbContactPos1X - _SysInfo.dbHipot1DistanceGap), _Config.dbTestZoneContactSpeed);
                    //    MoveTo(AXIS.HIPOT_2X, (_ModelInfo._TestInfo[0].dbContactPos2X + _SysInfo.dbHipot1DistanceGap), _Config.dbTestZoneContactSpeed);
                    //}
                    //else
                    //{
                    //MoveTo(AXIS.HIPOT_1X, _ModelInfo._TestInfo[0].dbContactPos1X, _Config.dbTestZoneContactSpeed);
                    if (!_ModelInfo.bUseHipot1UpDwContact)
                    {
                        MoveTo(AXIS.HIPOT_1X, _ModelInfo._TestInfo[0].dbContactPos1X, _Config.dbTestZoneContactSpeed);
                    }
                    else
                    {
                        MoveTo(AXIS.HIPOT_1Z, _ModelInfo._TestInfo[0].dbContactPos1Z, _Config.dbTestZoneContactSpeed);
                    }
                    MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbContactPos2X, _Config.dbTestZoneContactSpeed);
                    //}
                    nProcessStep[nStepIndex]++;
                    break;

                case 415:
                    if (!MotionDone(AXIS.HIPOT_1X) || !MotionDone(AXIS.HIPOT_2X) || !MotionDone(AXIS.HIPOT_1Z)) { break; }
                    _Count.nStation5PinCount++;
                    SaveProductCount();
                    if (_ModelInfo.bUseHipotContactTest)
                    {
                        nProcessStep[nStepIndex] = 416;
                    }
                    else
                    {
                        _SysInfo.nHipotTestStep = 0;
                        nProcessStep[nStepIndex] = 420;
                    }
                    break;

                //case 416:
                //    SetDIOPort(DO.HIPOT_CONTACT_CHECK, true);
                //    tMainTimer[nStepIndex].Start(1000);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 417:
                //    if (!tMainTimer[nStepIndex].Verify()) { break; }

                //    _mainform.BeginInvoke(new Action(() => _mainform.ViewHIPOTContactInof()));

                //    tMainTimer[nStepIndex].Start(200);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 418:
                //    if (!tMainTimer[nStepIndex].Verify()) { break; }

                //    if (GetDIOPort(DI.HIPOT_G_CONTACT_OK) &&
                //        GetDIOPort(DI.HIPOT_S_CONTACT_OK) &&
                //        GetDIOPort(DI.HIPOT_N_CONTACT_OK) &&
                //        GetDIOPort(DI.HIPOT_P_CONTACT_OK))
                //    {
                //        nProcessStep[nStepIndex] = 425;
                //    }
                //    else
                //    {
                //        if (GetDIOPort(DI.HIPOT_G_CONTACT_OK) &&
                //        GetDIOPort(DI.HIPOT_N_CONTACT_OK) &&
                //        GetDIOPort(DI.HIPOT_P_CONTACT_OK))
                //        {
                //            AppendLogMsg("Hipot - Contact Fail..", LOG_TYPE.ERROR);
                //            SetDIOPort(DO.HIPOT_CONTACT_CHECK, false);
                //            nProcessStep[nStepIndex] = 1000;
                //        }
                //        else
                //        {
                //            nProcessStep[nStepIndex] = 3000;
                //        }
                //        break;
                //    }
                //    break;


                case 420:
                    // TWIN PORT 기능용 [ LG화학 및 남경 요청 , 2018. 11. 22 ]  - 택타임 이슈
                    _HipotResult.tTestTime = DateTime.Now;
                    _SysInfo.nHipotStep = 1;
                    tMainTimer[nStepIndex].Start(10000);

                    if (_SysInfo.bChangeHipotInfo)
                    {
                        _SysInfo.bChangeHipotInfo = false;
                        nProcessStep[nStepIndex]++;
                    }
                    else
                    {
                        nProcessStep[nStepIndex] = 479;
                    }


                    //if (_SysInfo.nHipotTestStep > 3)
                    //{
                    //    nProcessStep[nStepIndex] = 480;
                    //    break;
                    //}

                    //if (_ModelInfo.nSpare[_SysInfo.nHipotTestStep] == 0)
                    //{
                    //    // 단자 접촉성
                    //    nProcessStep[nStepIndex] = 425;
                    //}
                    //else if (_ModelInfo.nSpare[_SysInfo.nHipotTestStep] == 1)
                    //{
                    //    // 내전압
                    //    nProcessStep[nStepIndex] = 435;
                    //}
                    //else if (_ModelInfo.nSpare[_SysInfo.nHipotTestStep] == 2)
                    //{
                    //    // 절연저항
                    //    nProcessStep[nStepIndex] = 445;
                    //}
                    //else if (_ModelInfo.nSpare[_SysInfo.nHipotTestStep] == 3)
                    //{
                    //    // 접지연속성
                    //    nProcessStep[nStepIndex] = 460;
                    //}
                    break;

                case 421:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("하이팟 테스터 초기화 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 9000;
                        break;
                    }

                    if (_HipotTester.DeviceInit())
                    {
                        tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                        nProcessStep[nStepIndex] = 465;
                    }
                    break;

                // 단자접촉성
                case 425:
                    //SetDIOPort(DO.HIPOT_CONTACT_CHECK, false);
                    _HipotResult.tTestTime = DateTime.Now;
                    if (_ModelInfo.bPassNOSCTest)
                    {
                        _HipotResult.tr_NOSC = TEST_RESULT.PASS;
                        nProcessStep[nStepIndex] = 430;
                        break;
                    }


                    if (!_HipotTester.port.IsOpen)
                    {
                        AppendLogMsg("하이팟 테스터 통신 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    _HipotResult.tr_NOSC = TEST_RESULT.ING;
                    _HipotResult.tr_TOTAL = TEST_RESULT.ING;
                    //UpdateHipotResult();
                   //_HipotTester.SetOscTestThread(_ModelInfo.dbNOSCgetCS, _ModelInfo.dbNOSCSpecOpen * 0.01, _ModelInfo.dbNOSCSpecShort * 0.01, 2, _ModelInfo._TestInfo[0].nSpare_a[3], 1);
                    _HipotTester.SetOscTestThread(_ModelInfo.dbNOSCgetCS, _ModelInfo.dbNOSCSpecOpen * 0.01, _ModelInfo.dbNOSCSpecShort * 0.01, 2, _SysInfo.nHioptContectN, 1);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 426:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("하이팟 테스터 통신 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    //if (_HipotTester.SetOscTest(_ModelInfo.dbNOSCgetCS, _ModelInfo.dbNOSCSpecOpen * 0.01, _ModelInfo.dbNOSCSpecShort * 0.01, 2, _ModelInfo._TestInfo[0].nSpare_a[3]))
                    //{
                    //    AppendLogMsg(String.Format("Set OSC , {0} , {1} , {2}", _ModelInfo.dbNOSCgetCS, _ModelInfo.dbNOSCSpecOpen * 0.01, _ModelInfo.dbNOSCSpecShort * 0.01), LOG_TYPE.INFO);
                    //    nProcessStep[nStepIndex]++;
                    //}
                    if (_HipotTester.bThreadResult)
                    {
                        AppendLogMsg(String.Format("Set OSC , {0} , {1} , {2}", _ModelInfo.dbNOSCgetCS, _ModelInfo.dbNOSCSpecOpen * 0.01, _ModelInfo.dbNOSCSpecShort * 0.01), LOG_TYPE.INFO);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 427:
                    _HipotTester.TestStart();
                    tMainTimer[nStepIndex].Start(3000);
                    _HipotTester.BufferClear();
                    nProcessStep[nStepIndex]++;
                    break;

                case 428:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("하이팟 OSC 검사 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    if (_HipotTester.GetTestAutoReport())
                    {
                        double.TryParse(_HipotTester.strReportData, out _HipotResult.dbNOSCData);

                        if ((_HipotResult.dbNOSCData * 1000000000) >= (_ModelInfo.dbNOSCgetCS * _ModelInfo.dbNOSCSpecOpen * 0.01) &&
                            (_HipotResult.dbNOSCData * 1000000000) <= (_ModelInfo.dbNOSCgetCS * _ModelInfo.dbNOSCSpecShort * 0.01))
                        {
                            _HipotResult.tr_NOSC = TEST_RESULT.OK;
                            nProcessStep[nStepIndex] = 430;
                        }
                        else
                        {
                            _HipotResult.tr_NOSC = TEST_RESULT.NG;
                            nProcessStep[nStepIndex] = 490;
                        }
                        //UpdateHipotResult();
                        tMainTimer[nStepIndex].Start(2000);
                        _HipotTester.ClearDevice();
                        _HipotTester.ClearDevice();

                    }
                    break;



                case 430:
                    if (_ModelInfo.bPassOSCTest)
                    {
                        _HipotResult.tr_OSC = TEST_RESULT.PASS;
                        //nProcessStep[nStepIndex] = 435;


                        _SysInfo.nHipotTestStep++;
                        nProcessStep[nStepIndex] = 420;
                        break;
                    }


                    if (!_HipotTester.port.IsOpen)
                    {
                        AppendLogMsg("하이팟 테스터 통신 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    _HipotResult.tr_OSC = TEST_RESULT.ING;
                    _HipotResult.tr_TOTAL = TEST_RESULT.ING;
                    //UpdateHipotResult();
                    //_HipotTester.SetOscTestThread(_ModelInfo.dbOSCgetCS, _ModelInfo.dbOSCSpecOpen * 0.01, _ModelInfo.dbOSCSpecShort * 0.01, 2, _ModelInfo._TestInfo[0].nSpare_a[2], 1);
                    _HipotTester.SetOscTestThread(_ModelInfo.dbOSCgetCS, _ModelInfo.dbOSCSpecOpen * 0.01, _ModelInfo.dbOSCSpecShort * 0.01, 2, _SysInfo.nHioptContectP, 1);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 431:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("하이팟 테스터 통신 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    //if (_HipotTester.SetOscTest(_ModelInfo.dbOSCgetCS, _ModelInfo.dbOSCSpecOpen * 0.01, _ModelInfo.dbOSCSpecShort * 0.01, 2, _ModelInfo._TestInfo[0].nSpare_a[2]))
                    //{
                    //    AppendLogMsg(String.Format("Set OSC , {0} , {1} , {2}", _ModelInfo.dbOSCgetCS, _ModelInfo.dbOSCSpecOpen * 0.01, _ModelInfo.dbOSCSpecShort * 0.01), LOG_TYPE.INFO);
                    //    nProcessStep[nStepIndex]++;
                    //}
                    if (_HipotTester.bThreadResult)
                    {
                        AppendLogMsg(String.Format("Set OSC , {0} , {1} , {2}", _ModelInfo.dbOSCgetCS, _ModelInfo.dbOSCSpecOpen * 0.01, _ModelInfo.dbOSCSpecShort * 0.01), LOG_TYPE.INFO);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 432:
                    _HipotTester.TestStart();
                    tMainTimer[nStepIndex].Start(3000);
                    _HipotTester.BufferClear();
                    nProcessStep[nStepIndex]++;
                    break;

                case 433:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("하이팟 OSC 통신 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    if (_HipotTester.GetTestAutoReport())
                    {
                        double.TryParse(_HipotTester.strReportData, out _HipotResult.dbOSCData);

                        if ((_HipotResult.dbOSCData * 1000000000) >= (_ModelInfo.dbOSCgetCS * _ModelInfo.dbOSCSpecOpen * 0.01) &&
                            (_HipotResult.dbOSCData * 1000000000) <= (_ModelInfo.dbOSCgetCS * _ModelInfo.dbOSCSpecShort * 0.01))
                        {
                            _HipotResult.tr_OSC = TEST_RESULT.OK;
                            //nProcessStep[nStepIndex] = 435;

                            _SysInfo.nHipotTestStep++;
                            nProcessStep[nStepIndex] = 420;
                        }
                        else
                        {
                            _HipotResult.tr_OSC = TEST_RESULT.NG;
                            nProcessStep[nStepIndex] = 490;
                        }
                        //UpdateHipotResult();
                        tMainTimer[nStepIndex].Start(2000);
                        _HipotTester.ClearDevice();
                        _HipotTester.ClearDevice();

                    }
                    break;






                // HIPOT TEST 내전압 테스트
                case 435:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    if (_ModelInfo.bPassPHIPOTTest)
                    {
                        _HipotResult.tr_HIP = TEST_RESULT.PASS;
                        nProcessStep[nStepIndex] = 440;
                        break;
                    }

                    if (!_HipotTester.port.IsOpen)
                    {
                        AppendLogMsg("하이팟 테스터 연결 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }
                    _HipotResult.tr_HIP = TEST_RESULT.ING;
                   // _HipotTester.SetDcTestThread(_ModelInfo.dbPHIPOTInput, _ModelInfo.dbPHIPOTLowLimit, _ModelInfo.dbPHIPOTTestTime, 2, _ModelInfo._TestInfo[0].nSpare_a[2], _ModelInfo.dbHipotRampTime, 1);
                    _HipotTester.SetDcTestThread(_ModelInfo.dbPHIPOTInput, _ModelInfo.dbPHIPOTLowLimit, _ModelInfo.dbPHIPOTTestTime, 2, _SysInfo.nHioptContectP, _ModelInfo.dbHipotRampTime, 1);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 436:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("하이팟 테스터 통신 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    //if (_HipotTester.SetDCTest(_ModelInfo.dbPHIPOTInput, _ModelInfo.dbPHIPOTLowLimit, _ModelInfo.dbPHIPOTTestTime, 2, _ModelInfo._TestInfo[0].nSpare_a[2]))
                    //{
                    //    AppendLogMsg(String.Format("Set PHI , {0} , {1} , {2}", _ModelInfo.dbPHIPOTInput, _ModelInfo.dbPHIPOTLowLimit, _ModelInfo.dbPHIPOTTestTime), LOG_TYPE.INFO);
                    //    nProcessStep[nStepIndex]++;
                    //}
                    if (_HipotTester.bThreadResult)
                    {
                        AppendLogMsg(String.Format("Set PHI , {0} , {1} , {2}", _ModelInfo.dbPHIPOTInput, _ModelInfo.dbPHIPOTLowLimit, _ModelInfo.dbPHIPOTTestTime), LOG_TYPE.INFO);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 437:
                    _HipotTester.TestStart();
                    tMainTimer[nStepIndex].Start((int)(_ModelInfo.dbPHIPOTTestTime * 1500));
                    _HipotTester.BufferClear();
                    nProcessStep[nStepIndex]++;
                    break;

                case 438:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("하이팟(+) 검사 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    if (_HipotTester.GetTestAutoReport())
                    {
                        double.TryParse(_HipotTester.strReportData, out _HipotResult.dbHipotPos);

                        if ((_HipotResult.dbHipotPos * 1000) < (_ModelInfo.dbPHIPOTLowLimit))
                        {
                            _HipotResult.tr_HIP = TEST_RESULT.OK;
                            nProcessStep[nStepIndex] = 440;
                        }
                        else
                        {
                            _HipotResult.tr_HIP = TEST_RESULT.NG;
                            nProcessStep[nStepIndex] = 490;
                        }
                        // UpdateHipotResult();

                        tMainTimer[nStepIndex].Start(2000);

                        _HipotTester.ClearDevice();
                        _HipotTester.ClearDevice();
                    }
                    break;



                // HIPOT TEST
                case 440:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    if (_ModelInfo.bPassNHIPOTTest)
                    {
                        _HipotResult.tr_HIN = TEST_RESULT.PASS;
                        ///nProcessStep[nStepIndex] = 445;

                        _SysInfo.nHipotTestStep++;
                        nProcessStep[nStepIndex] = 420;
                        break;
                    }

                    if (!_HipotTester.port.IsOpen)
                    {
                        AppendLogMsg("하이팟 테스터 통신 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }
                    _HipotResult.tr_HIN = TEST_RESULT.ING;
                    //_HipotTester.SetDcTestThread(_ModelInfo.dbNHIPOTInput, _ModelInfo.dbNHIPOTLowLimit, _ModelInfo.dbNHIPOTTestTime, 2, _ModelInfo._TestInfo[0].nSpare_a[3], _ModelInfo.dbHipotRampTime, 1);
                    _HipotTester.SetDcTestThread(_ModelInfo.dbNHIPOTInput, _ModelInfo.dbNHIPOTLowLimit, _ModelInfo.dbNHIPOTTestTime, 2, _SysInfo.nHioptContectN, _ModelInfo.dbHipotRampTime, 1);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 441:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("하이팟 테스터 통신 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    //if (_HipotTester.SetDCTest(_ModelInfo.dbNHIPOTInput, _ModelInfo.dbNHIPOTLowLimit, _ModelInfo.dbNHIPOTTestTime, 2, _ModelInfo._TestInfo[0].nSpare_a[3]))
                    //{
                    //    AppendLogMsg(String.Format("Set NHI , {0} , {1} , {2}", _ModelInfo.dbNHIPOTInput, _ModelInfo.dbNHIPOTLowLimit, _ModelInfo.dbNHIPOTTestTime), LOG_TYPE.INFO);
                    //    nProcessStep[nStepIndex]++;
                    //}
                    if (_HipotTester.bThreadResult)
                    {
                        AppendLogMsg(String.Format("Set NHI , {0} , {1} , {2}", _ModelInfo.dbNHIPOTInput, _ModelInfo.dbNHIPOTLowLimit, _ModelInfo.dbNHIPOTTestTime), LOG_TYPE.INFO);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 442:
                    _HipotTester.TestStart();
                    tMainTimer[nStepIndex].Start((int)(_ModelInfo.dbNHIPOTTestTime * 1500));
                    _HipotTester.BufferClear();
                    nProcessStep[nStepIndex]++;
                    break;

                case 443:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("하이팟(-) 검사 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    if (_HipotTester.GetTestAutoReport())
                    {
                        double.TryParse(_HipotTester.strReportData, out _HipotResult.dbHipotNeg);

                        if ((_HipotResult.dbHipotNeg * 1000) < (_ModelInfo.dbNHIPOTLowLimit))
                        {
                            _HipotResult.tr_HIN = TEST_RESULT.OK;
                            // nProcessStep[nStepIndex] = 445;

                            _SysInfo.nHipotTestStep++;
                            nProcessStep[nStepIndex] = 420;
                        }
                        else
                        {
                            _HipotResult.tr_HIN = TEST_RESULT.NG;
                            nProcessStep[nStepIndex] = 490;
                        }
                        // UpdateHipotResult();

                        tMainTimer[nStepIndex].Start(2000);

                        _HipotTester.ClearDevice();
                        _HipotTester.ClearDevice();

                    }

                    break;





                // NIR TEST 절연저항 테스트
                case 445:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    if (_ModelInfo.bPassNIRTest)
                    {
                        _HipotResult.tr_IRN = TEST_RESULT.PASS;
                        nProcessStep[nStepIndex] = 450;
                        break;
                    }


                    if (!_HipotTester.port.IsOpen)
                    {
                        AppendLogMsg("하이팟 테스터 통신 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }
                    _HipotResult.tr_IRN = TEST_RESULT.ING;
                    //UpdateHipotResult();
                    //_HipotTester.SetIRTestThread(_ModelInfo.dbNIRInput, _ModelInfo.dbNIRLowLimit, _ModelInfo.dbNIRTestTime, 2, _ModelInfo._TestInfo[0].nSpare_a[3], 1);
                    _HipotTester.SetIRTestThread(_ModelInfo.dbNIRInput, _ModelInfo.dbNIRLowLimit, _ModelInfo.dbNIRTestTime, 2, _SysInfo.nHioptContectN, 1);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 446:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("하이팟 테스터 통신 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    //if (_HipotTester.SetIRTest(_ModelInfo.dbNIRInput, _ModelInfo.dbNIRLowLimit, _ModelInfo.dbNIRTestTime, 2, _ModelInfo._TestInfo[0].nSpare_a[3]))
                    //{
                    //    AppendLogMsg(String.Format("Set NIR , {0} , {1} , {2}", _ModelInfo.dbNIRInput, _ModelInfo.dbNIRLowLimit, _ModelInfo.dbNIRTestTime), LOG_TYPE.INFO);
                    //    nProcessStep[nStepIndex]++;
                    //}
                    if (_HipotTester.bThreadResult)
                    {
                        AppendLogMsg(String.Format("Set NIR , {0} , {1} , {2}", _ModelInfo.dbNIRInput, _ModelInfo.dbNIRLowLimit, _ModelInfo.dbNIRTestTime), LOG_TYPE.INFO);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 447:
                    _HipotTester.TestStart();

                    _tIRLogTimer.Restart();             // NIR LOG 타이머 시작
                    _SysInfo.nIRTestTimeCount = 0;      // NIR LOG 카운트 시작


                    tMainTimer[nStepIndex].Start((int)(_ModelInfo.dbNIRTestTime * 1500));
                    _HipotTester.BufferClear();
                    nProcessStep[nStepIndex]++;
                    break;

                case 448:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("하이팟 IR 검사 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    // 검사 시간보다 1초 적게
                    if (_tIRLogTimer.ElapsedMilliseconds < (_ModelInfo.dbNIRTestTime - 1) * 1000)
                    {

                        if ((_tIRLogTimer.ElapsedMilliseconds / 1000) > _SysInfo.nIRTestTimeCount)
                        {
                            _HipotTester.FetchCall();           // FETCH 콜하고
                            _SysInfo.nIRTestTimeCount++;        // 카운터를 하나 증가시킴
                        }

                        if (_HipotTester.GetTestFetchReport())
                        {
                            double.TryParse(_HipotTester.strReportData, out _SysInfo.dbIRTestMode);
                            SaveIRFetchData(_HipotResult.strBCD, _SysInfo.dbIRTestMode, _SysInfo.nIRTestTimeCount, "IR(-)");
                        }
                        break;  //시간 중엔 오토리포트로 가는것을 차단
                    }



                    if (_HipotTester.GetTestAutoReport())
                    {
                        double.TryParse(_HipotTester.strReportData, out _HipotResult.dbNIRData);
                        if ((_HipotResult.dbNIRData * 0.000001) > (_ModelInfo.dbNIRLowLimit))
                        {
                            //if (_HipotResult.dbNIRData * 0.000001 > 999.99)
                            //{
                            //    _HipotResult.dbNIRData = 999990000.00;
                            //}

                            _HipotResult.tr_IRN = TEST_RESULT.OK;
                            nProcessStep[nStepIndex] = 450;
                        }
                        else
                        {
                            _HipotResult.tr_IRN = TEST_RESULT.NG;
                            nProcessStep[nStepIndex] = 490;
                        }
                        // UpdateHipotResult();

                        tMainTimer[nStepIndex].Start(2000);
                        _HipotTester.ClearDevice();
                        _HipotTester.ClearDevice();

                    }
                    break;


                // PIR 전환
                case 450:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    if (_ModelInfo.bPassPIRTest)
                    {
                        _HipotResult.tr_HIP = TEST_RESULT.PASS;
                        //nProcessStep[nStepIndex] = 460;

                        _SysInfo.nHipotTestStep++;
                        nProcessStep[nStepIndex] = 420;
                        break;
                    }

                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    nProcessStep[nStepIndex]++;
                    break;

                case 451:
                    tMainTimer[nStepIndex].Start(2000);
                    nProcessStep[nStepIndex]++;
                    break;

                case 452:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    nProcessStep[nStepIndex] = 455;
                    break;



                // PIR TEST
                case 455:
                    if (!_HipotTester.port.IsOpen)
                    {
                        AppendLogMsg("하이팟 테스터 통신 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    _HipotResult.tr_IRP = TEST_RESULT.ING;
                    //_HipotTester.SetIRTestThread(_ModelInfo.dbPIRInput, _ModelInfo.dbPIRLowLimit, _ModelInfo.dbPIRTestTime, 2, _ModelInfo._TestInfo[0].nSpare_a[2], 1);
                    _HipotTester.SetIRTestThread(_ModelInfo.dbPIRInput, _ModelInfo.dbPIRLowLimit, _ModelInfo.dbPIRTestTime, 2, _SysInfo.nHioptContectP, 1);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 456:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("하이팟 테스터 통신 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    //if (_HipotTester.SetIRTest(_ModelInfo.dbPIRInput, _ModelInfo.dbPIRLowLimit, _ModelInfo.dbPIRTestTime, 2, _ModelInfo._TestInfo[0].nSpare_a[2]))
                    //{
                    //    AppendLogMsg(String.Format("Set PIR , {0} , {1} , {2}", _ModelInfo.dbPIRInput, _ModelInfo.dbPIRLowLimit, _ModelInfo.dbPIRTestTime), LOG_TYPE.INFO);
                    //    nProcessStep[nStepIndex]++;
                    //}
                    if (_HipotTester.bThreadResult)
                    {
                        AppendLogMsg(String.Format("Set PIR , {0} , {1} , {2}", _ModelInfo.dbPIRInput, _ModelInfo.dbPIRLowLimit, _ModelInfo.dbPIRTestTime), LOG_TYPE.INFO);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 457:
                    _HipotTester.TestStart();

                    _SysInfo.nIRTestTimeCount = 0;
                    _tIRLogTimer.Restart();

                    tMainTimer[nStepIndex].Start((int)(_ModelInfo.dbPIRTestTime * 1500));
                    _HipotTester.BufferClear();
                    nProcessStep[nStepIndex]++;
                    break;

                case 458:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("하이팟 IR 검사 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    // 검사 시간보다 1초 적게
                    if (_tIRLogTimer.ElapsedMilliseconds < (_ModelInfo.dbPIRTestTime - 1) * 1000)
                    {

                        if ((_tIRLogTimer.ElapsedMilliseconds / 1000) > _SysInfo.nIRTestTimeCount)
                        {
                            _HipotTester.FetchCall();           // FETCH 콜하고
                            _SysInfo.nIRTestTimeCount++;        // 카운터를 하나 증가시킴
                        }

                        if (_HipotTester.GetTestFetchReport())
                        {
                            double.TryParse(_HipotTester.strReportData, out _SysInfo.dbIRTestMode);
                            SaveIRFetchData(_HipotResult.strBCD, _SysInfo.dbIRTestMode, _SysInfo.nIRTestTimeCount, "IR(+)");
                        }
                        break;  //시간 중엔 오토리포트로 가는것을 차단
                    }


                    if (_HipotTester.GetTestAutoReport())
                    {
                        double.TryParse(_HipotTester.strReportData, out _HipotResult.dbPIRData);

                        if ((_HipotResult.dbPIRData * 0.000001) > (_ModelInfo.dbPIRLowLimit))
                        {
                            //if (_HipotResult.dbPIRData * 0.000001 > 999.99)
                            //{
                            //    _HipotResult.dbPIRData = 999990000.00;
                            //}

                            _HipotResult.tr_IRP = TEST_RESULT.OK;
                            //nProcessStep[nStepIndex] = 460;
                            _SysInfo.nHipotTestStep++;
                            nProcessStep[nStepIndex] = 420;
                        }
                        else
                        {
                            _HipotResult.tr_IRP = TEST_RESULT.NG;
                            nProcessStep[nStepIndex] = 490;
                        }
                        // UpdateHipotResult();

                        tMainTimer[nStepIndex].Start(2000);

                        _HipotTester.ClearDevice();
                        _HipotTester.ClearDevice();


                    }
                    break;


                // GB TEST 접지연속성 테스트
                case 460:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    if (_ModelInfo.bPassGBTest)
                    {
                        _HipotResult.tr_GB = TEST_RESULT.PASS;
                        //nProcessStep[nStepIndex] = 480;

                        _SysInfo.nHipotTestStep++;
                        nProcessStep[nStepIndex] = 420;
                        break;
                    }


                    if (!_HipotTester.port.IsOpen)
                    {
                        AppendLogMsg("하이팟 테스터 연결 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    _HipotResult.tr_GB = TEST_RESULT.ING;
                    //UpdateHipotResult();
                    _HipotTester.SetGbTestThread(_ModelInfo.dbGBInput, _ModelInfo.dbGBHighLimit, _ModelInfo.dbGBTestTime, 1, 3, 1, false);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 461:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("하이팟 테스터 통신 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    //if (_HipotTester.SetGBTest(_ModelInfo.dbGBInput, _ModelInfo.dbGBHighLimit, _ModelInfo.dbGBTestTime,1,3))
                    //{
                    //    AppendLogMsg(String.Format("Set GB , {0} , {1} , {2}", _ModelInfo.dbGBInput, _ModelInfo.dbGBHighLimit, _ModelInfo.dbGBTestTime), LOG_TYPE.INFO);
                    //    nProcessStep[nStepIndex]++;
                    //}
                    if (_HipotTester.bThreadResult)
                    {
                        AppendLogMsg(String.Format("Set GB , {0} , {1} , {2}", _ModelInfo.dbGBInput, _ModelInfo.dbGBHighLimit, _ModelInfo.dbGBTestTime), LOG_TYPE.INFO);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 462:
                    _HipotTester.TestStart();
                    tMainTimer[nStepIndex].Start((int)(_ModelInfo.dbGBTestTime * 1500));
                    _HipotTester.BufferClear();
                    nProcessStep[nStepIndex]++;
                    break;

                case 463:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("하이팟 GB 검사 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    if (_HipotTester.GetTestAutoReport())
                    {
                        double.TryParse(_HipotTester.strReportData, out _HipotResult.dbGBData);
                        if (0 < (_HipotResult.dbGBData) && (_HipotResult.dbGBData) < _ModelInfo.dbGBHighLimit)
                        {
                            _HipotResult.tr_GB = TEST_RESULT.OK;
                            //nProcessStep[nStepIndex] = 480;
                            _SysInfo.nHipotTestStep++;
                            nProcessStep[nStepIndex] = 420;
                        }
                        else
                        {
                            _HipotResult.tr_GB = TEST_RESULT.NG;
                            nProcessStep[nStepIndex] = 490;
                        }
                        //UpdateHipotResult();
                        AppendLogMsg(String.Format("GB READ : {0}", _HipotTester.strReportData), LOG_TYPE.INFO);
                        tMainTimer[nStepIndex].Start(2000);

                        _HipotTester.ClearDevice();
                        _HipotTester.ClearDevice();
                    }
                    break;







                // TWIN PORT 기능용 [ LG화학 및 남경 요청 , 2018. 11. 22 ]  - 택타임 이슈
                case 465:
                    //  - OSC
                    //_HipotTester.SetOscTestThread(_ModelInfo.dbNOSCgetCS, _ModelInfo.dbNOSCSpecOpen * 0.01, _ModelInfo.dbNOSCSpecShort * 0.01, 2, _ModelInfo._TestInfo[0].nSpare_a[3], _SysInfo.nHipotStep++);
                    _HipotTester.SetOscTestThread(_ModelInfo.dbNOSCgetCS, _ModelInfo.dbNOSCSpecOpen * 0.01, _ModelInfo.dbNOSCSpecShort * 0.01, 2, _SysInfo.nHioptContectN, _SysInfo.nHipotStep++);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 466:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("하이팟 테스터 통신 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    if (_HipotTester.bThreadResult)
                    {
                        AppendLogMsg(String.Format("Set OSC , {0} , {1} , {2}", _ModelInfo.dbNOSCgetCS, _ModelInfo.dbNOSCSpecOpen * 0.01, _ModelInfo.dbNOSCSpecShort * 0.01), LOG_TYPE.INFO);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 467:
                    //  + OSC
                   // _HipotTester.SetOscTestThread(_ModelInfo.dbOSCgetCS, _ModelInfo.dbOSCSpecOpen * 0.01, _ModelInfo.dbOSCSpecShort * 0.01, 2, _ModelInfo._TestInfo[0].nSpare_a[2], _SysInfo.nHipotStep++);
                    _HipotTester.SetOscTestThread(_ModelInfo.dbOSCgetCS, _ModelInfo.dbOSCSpecOpen * 0.01, _ModelInfo.dbOSCSpecShort * 0.01, 2, _SysInfo.nHioptContectP, _SysInfo.nHipotStep++);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 468:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("하이팟 테스터 통신 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    if (_HipotTester.bThreadResult)
                    {
                        AppendLogMsg(String.Format("Set OSC , {0} , {1} , {2}", _ModelInfo.dbOSCgetCS, _ModelInfo.dbOSCSpecOpen * 0.01, _ModelInfo.dbOSCSpecShort * 0.01), LOG_TYPE.INFO);
                        nProcessStep[nStepIndex]++;
                    }
                    break;


                case 469:
                    // - IR
                    //_HipotTester.SetIRTestThread(_ModelInfo.dbNIRInput, _ModelInfo.dbNIRLowLimit, _ModelInfo.dbNIRTestTime, 2, _ModelInfo._TestInfo[0].nSpare_a[3], _SysInfo.nHipotStep++);
                    _HipotTester.SetIRTestThread(_ModelInfo.dbNIRInput, _ModelInfo.dbNIRLowLimit, _ModelInfo.dbNIRTestTime, 2, _SysInfo.nHioptContectN, _SysInfo.nHipotStep++);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 470:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("하이팟 테스터 통신 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    if (_HipotTester.bThreadResult)
                    {
                        AppendLogMsg(String.Format("Set NIR , {0} , {1} , {2}", _ModelInfo.dbNIRInput, _ModelInfo.dbNIRLowLimit, _ModelInfo.dbNIRTestTime), LOG_TYPE.INFO);
                        nProcessStep[nStepIndex]++;
                    }
                    break;


                case 471:
                    // + IR
                    //_HipotTester.SetIRTestThread(_ModelInfo.dbPIRInput, _ModelInfo.dbPIRLowLimit, _ModelInfo.dbPIRTestTime, 2, _ModelInfo._TestInfo[0].nSpare_a[2], _SysInfo.nHipotStep++);
                    _HipotTester.SetIRTestThread(_ModelInfo.dbPIRInput, _ModelInfo.dbPIRLowLimit, _ModelInfo.dbPIRTestTime, 2, _SysInfo.nHioptContectP, _SysInfo.nHipotStep++);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 472:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("하이팟 테스터 통신 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    if (_HipotTester.bThreadResult)
                    {
                        AppendLogMsg(String.Format("Set PIR , {0} , {1} , {2}", _ModelInfo.dbPIRInput, _ModelInfo.dbPIRLowLimit, _ModelInfo.dbPIRTestTime), LOG_TYPE.INFO);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 473:
                    // - HIPOT
                    //_HipotTester.SetDcTestThread(_ModelInfo.dbNHIPOTInput, _ModelInfo.dbNHIPOTLowLimit, _ModelInfo.dbNHIPOTTestTime, 2, _ModelInfo._TestInfo[0].nSpare_a[3], _ModelInfo.dbHipotRampTime, _SysInfo.nHipotStep++);
                    _HipotTester.SetDcTestThread(_ModelInfo.dbNHIPOTInput, _ModelInfo.dbNHIPOTLowLimit, _ModelInfo.dbNHIPOTTestTime, 2, _SysInfo.nHioptContectN, _ModelInfo.dbHipotRampTime, _SysInfo.nHipotStep++);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 474:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("하이팟 테스터 통신 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    if (_HipotTester.bThreadResult)
                    {
                        AppendLogMsg(String.Format("Set NHI , {0} , {1} , {2}", _ModelInfo.dbNHIPOTInput, _ModelInfo.dbNHIPOTLowLimit, _ModelInfo.dbNHIPOTTestTime), LOG_TYPE.INFO);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 475:
                    // GB
                    _HipotTester.SetGbTestThread(_ModelInfo.dbGBInput, _ModelInfo.dbGBHighLimit, _ModelInfo.dbGBTestTime, 1, 3, _SysInfo.nHipotStep++, true);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 476:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("하이팟 테스터 통신 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    if (_HipotTester.bThreadResult)
                    {
                        AppendLogMsg(String.Format("Set GB , {0} , {1} , {2}", _ModelInfo.dbGBInput, _ModelInfo.dbGBHighLimit, _ModelInfo.dbGBTestTime), LOG_TYPE.INFO);
                        nProcessStep[nStepIndex]++;
                    }
                    break;
                case 477:
                    // + HIPOT
                    //_HipotTester.SetDcTestThread(_ModelInfo.dbPHIPOTInput, _ModelInfo.dbPHIPOTLowLimit, _ModelInfo.dbPHIPOTTestTime, 2, _ModelInfo._TestInfo[0].nSpare_a[2], _ModelInfo.dbHipotRampTime, _SysInfo.nHipotStep++);
                    _HipotTester.SetDcTestThread(_ModelInfo.dbPHIPOTInput, _ModelInfo.dbPHIPOTLowLimit, _ModelInfo.dbPHIPOTTestTime, 2, _SysInfo.nHioptContectP, _ModelInfo.dbHipotRampTime, _SysInfo.nHipotStep++);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 478:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("하이팟 테스터 통신 실패", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;
                        break;
                    }

                    if (_HipotTester.bThreadResult)
                    {
                        AppendLogMsg(String.Format("Set PHI , {0} , {1} , {2}", _ModelInfo.dbPHIPOTInput, _ModelInfo.dbPHIPOTLowLimit, _ModelInfo.dbPHIPOTTestTime), LOG_TYPE.INFO);
                        nProcessStep[nStepIndex]++;
                    }
                    break;


                case 479:
                    _HipotTester.TestStart();
                    _HipotTester.BufferClear();
                    nProcessStep[nStepIndex]++;
                    break;

                case 480:
                    if (_HipotTester.GetTestAutoReports())
                    {
                        // 갯수가 21개면 파싱
                        if (_HipotTester.strReportDatas.Length == 21)
                        {

                            // - OSC 파싱
                            if (_HipotTester.strReportDatas[0] == "OSC")
                            {
                                double.TryParse(_HipotTester.strReportDatas[1], out _HipotResult.dbNOSCData);

                                if (_HipotTester.strReportDatas[2] == "116") // OK코드
                                {


                                    if ((_HipotResult.dbNOSCData * 1000000000) >= (_ModelInfo.dbNOSCgetCS * _ModelInfo.dbNOSCSpecOpen * 0.01) &&
                                        (_HipotResult.dbNOSCData * 1000000000) <= (_ModelInfo.dbNOSCgetCS * _ModelInfo.dbNOSCSpecShort * 0.01))
                                    {
                                        _HipotResult.tr_NOSC = TEST_RESULT.OK;
                                    }
                                    else
                                    {
                                        _HipotResult.tr_NOSC = TEST_RESULT.NG;
                                    }
                                }
                                else
                                {
                                    _HipotResult.tr_NOSC = TEST_RESULT.NG;
                                }
                            }
                            else
                            {
                                _HipotResult.tr_NOSC = TEST_RESULT.NG;
                            }

                            // + OSC 파싱
                            if (_HipotTester.strReportDatas[3] == "OSC")
                            {
                                double.TryParse(_HipotTester.strReportDatas[4], out _HipotResult.dbOSCData);
                                if (_HipotTester.strReportDatas[5] == "116") // OK코드
                                {


                                    if ((_HipotResult.dbOSCData * 1000000000) >= (_ModelInfo.dbOSCgetCS * _ModelInfo.dbOSCSpecOpen * 0.01) &&
                                        (_HipotResult.dbOSCData * 1000000000) <= (_ModelInfo.dbOSCgetCS * _ModelInfo.dbOSCSpecShort * 0.01))
                                    {
                                        _HipotResult.tr_OSC = TEST_RESULT.OK;
                                    }
                                    else
                                    {
                                        _HipotResult.tr_OSC = TEST_RESULT.NG;
                                    }
                                }
                                else
                                {
                                    _HipotResult.tr_OSC = TEST_RESULT.NG;
                                }
                            }
                            else
                            {
                                _HipotResult.tr_OSC = TEST_RESULT.NG;
                            }

                            // - IR 파싱
                            if (_HipotTester.strReportDatas[6] == "IR")
                            {
                                double.TryParse(_HipotTester.strReportDatas[7], out _HipotResult.dbNIRData);
                                if (_HipotTester.strReportDatas[8] == "116") // OK코드
                                {

                                    if ((_HipotResult.dbNIRData * 0.000001) > (_ModelInfo.dbNIRLowLimit))
                                    {
                                        if (_HipotResult.dbNIRData * 0.000001 > 99999.99)
                                        {
                                            _HipotResult.dbNIRData = 99999990000.00;
                                        }
                                        _HipotResult.tr_IRN = TEST_RESULT.OK;
                                    }
                                    else
                                    {
                                        _HipotResult.tr_IRN = TEST_RESULT.NG;
                                    }

                                }
                                else
                                {
                                    _HipotResult.tr_IRN = TEST_RESULT.NG;
                                }
                            }
                            else
                            {
                                _HipotResult.tr_IRN = TEST_RESULT.NG;
                            }


                            // + IR 파싱
                            if (_HipotTester.strReportDatas[9] == "IR")
                            {
                                double.TryParse(_HipotTester.strReportDatas[10], out _HipotResult.dbPIRData);
                                if (_HipotTester.strReportDatas[11] == "116") // OK코드
                                {

                                    if ((_HipotResult.dbPIRData * 0.000001) > (_ModelInfo.dbPIRLowLimit))
                                    {
                                        if (_HipotResult.dbPIRData * 0.000001 > 99999.99)
                                        {
                                            _HipotResult.dbPIRData = 99999990000.00;
                                        }
                                        _HipotResult.tr_IRP = TEST_RESULT.OK;
                                    }
                                    else
                                    {
                                        _HipotResult.tr_IRP = TEST_RESULT.NG;
                                    }

                                }
                                else
                                {
                                    _HipotResult.tr_IRP = TEST_RESULT.NG;
                                }
                            }
                            else
                            {
                                _HipotResult.tr_IRP = TEST_RESULT.NG;
                            }


                            // - HIPOT 파싱
                            if (_HipotTester.strReportDatas[12] == "DC")
                            {
                                double.TryParse(_HipotTester.strReportDatas[13], out _HipotResult.dbHipotNeg);

                                if (_HipotTester.strReportDatas[14] == "116") // OK코드
                                {

                                    if ((_HipotResult.dbHipotNeg * 1000) < (_ModelInfo.dbNHIPOTLowLimit))
                                    {
                                        _HipotResult.tr_HIN = TEST_RESULT.OK;
                                    }
                                    else
                                    {
                                        _HipotResult.tr_HIN = TEST_RESULT.NG;
                                    }

                                }
                                else
                                {
                                    _HipotResult.tr_HIN = TEST_RESULT.NG;
                                }
                            }
                            else
                            {
                                _HipotResult.tr_HIN = TEST_RESULT.NG;
                            }


                            // GB 파싱
                            if (_HipotTester.strReportDatas[15] == "GB")
                            {
                                double.TryParse(_HipotTester.strReportDatas[16], out _HipotResult.dbGBData);
                                if (_HipotTester.strReportDatas[17] == "116") // OK코드
                                {
                                    if (0 < (_HipotResult.dbGBData) && (_HipotResult.dbGBData) < _ModelInfo.dbGBHighLimit)
                                    {
                                        _HipotResult.tr_GB = TEST_RESULT.OK;
                                    }
                                    else
                                    {
                                        _HipotResult.tr_GB = TEST_RESULT.NG;
                                    }

                                }
                                else
                                {
                                    _HipotResult.tr_GB = TEST_RESULT.NG;
                                }
                            }
                            else
                            {
                                _HipotResult.tr_GB = TEST_RESULT.NG;
                            }



                            // + HIPOT 파싱
                            if (_HipotTester.strReportDatas[18] == "DC")
                            {
                                double.TryParse(_HipotTester.strReportDatas[19], out _HipotResult.dbHipotPos);
                                if (_HipotTester.strReportDatas[20] == "116") // OK코드
                                {
                                    if ((_HipotResult.dbHipotPos * 1000) < (_ModelInfo.dbPHIPOTLowLimit))
                                    {
                                        _HipotResult.tr_HIP = TEST_RESULT.OK;
                                    }
                                    else
                                    {
                                        _HipotResult.tr_HIP = TEST_RESULT.NG;
                                    }

                                }
                                else
                                {
                                    _HipotResult.tr_HIP = TEST_RESULT.NG;
                                }
                            }
                            else
                            {
                                _HipotResult.tr_HIP = TEST_RESULT.NG;
                            }
                        }


                        _HipotTester.ClearDevice();
                        _HipotTester.ClearDevice();

                        nProcessStep[nStepIndex] = 490;
                    }
                    break;








                // 판정 및 저장
                case 490:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    _tHipotTimer.Stop();
                    _HipotTester.ClearDevice();
                    _HipotTester.DeviceStop();

                    // 스탠드 올론 모델의 경우 판정이 끝나면 전원 OFF 데이터를 보내준다
                    if (_ModelInfo.bUseStandAloneCanComm)
                    {
                        _CanComm.WriteFrame(0x6F0, new byte[] { 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });      // 전원 OFF 명령
                    }


                    if (_ModelInfo.bUseResuCanComm)
                    {
                        nProcessStep[nStepIndex] = 495;
                        break;
                    }
                    _CanComm.CloseCan();

                    if ((_HipotResult.tr_GB == TEST_RESULT.OK || _HipotResult.tr_GB == TEST_RESULT.PASS) &&
                        (_HipotResult.tr_NOSC == TEST_RESULT.OK || _HipotResult.tr_NOSC == TEST_RESULT.PASS) &&
                        (_HipotResult.tr_OSC == TEST_RESULT.OK || _HipotResult.tr_OSC == TEST_RESULT.PASS) &&
                        (_HipotResult.tr_HIN == TEST_RESULT.OK || _HipotResult.tr_HIN == TEST_RESULT.PASS) &&
                        (_HipotResult.tr_IRP == TEST_RESULT.OK || _HipotResult.tr_IRP == TEST_RESULT.PASS) &&
                        (_HipotResult.tr_IRN == TEST_RESULT.OK || _HipotResult.tr_IRN == TEST_RESULT.PASS) &&
                        (_HipotResult.tr_HIP == TEST_RESULT.OK || _HipotResult.tr_HIP == TEST_RESULT.PASS))
                    {
                        _HipotResult.tr_TOTAL = TEST_RESULT.OK;
                        _SysInfo.bContactTestOk[0] = true;

                        _SysInfo.bContactOneTime[0] = true;
                        _SysInfo.bContactTestNg[0] = false;
                        _SysInfo.eContactStatus[0] = CONTACT_STATUS.CONTACT_OK;

                        _SysInfo.ST_TL_RED[0] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_YELLOW[0] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_GREEN[0] = TOWER_LAMP.TL_ON;

                        if (_ModelInfo.bUseHipotAutoContact)
                        {
                            nProcessStep[nStepIndex] = 510; // 양품일경우 자동 해제   
                        }
                        else
                        {
                            nProcessStep[nStepIndex] = 100;
                        }

                        _mainform.Invoke(new Action(() => _mainform.ViewHipotLog(_HipotResult)));
                        SaveHipotMESData();
                    }
                    else
                    {
                        if (_HipotResult.tr_OSC == TEST_RESULT.NG)
                        {
                            // OSC NG일때

                            if (_SysInfo.nOSCRetryNowCount > _Config.nOscRetryCount - 1)
                            {
                                _SysInfo.nOSCRetryNowCount = 0;

                                _HipotResult.tr_TOTAL = TEST_RESULT.NG;
                                _SysInfo.bContactTestOk[0] = false;
                                _SysInfo.bContactTestNg[0] = true;

                                _SysInfo.bContactOneTime[0] = true;
                                _SysInfo.eContactStatus[0] = CONTACT_STATUS.CONTACT_NG;
                                nProcessStep[nStepIndex] = 1000;

                                _mainform.Invoke(new Action(() => _mainform.ViewHipotLog(_HipotResult)));
                                SaveHipotMESData();

                            }
                            else
                            {
                                _SysInfo.nOSCRetryNowCount++;
                                nProcessStep[nStepIndex] = 420;
                            }


                        }
                        else
                        {
                            _HipotResult.tr_TOTAL = TEST_RESULT.NG;
                            _SysInfo.bContactTestOk[0] = false;
                            _SysInfo.bContactTestNg[0] = true;

                            _SysInfo.bContactOneTime[0] = true;
                            _SysInfo.eContactStatus[0] = CONTACT_STATUS.CONTACT_NG;
                            nProcessStep[nStepIndex] = 1000;

                            _mainform.Invoke(new Action(() => _mainform.ViewHipotLog(_HipotResult)));
                            SaveHipotMESData();

                        }

                    }
                    //다시커밋용

                    //_mainform.Invoke(new Action(() => _mainform.ViewHipotLog(_HipotResult)));
                    //SaveHipotMESData();


                    // UpdateHipotResult();
                    break;


                case 495:
                    _CanComm.ClearBuffer(); // 버퍼를 클리어하고
                    _CanComm.WriteFrame(0x021, new byte[] { 0x55, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });      // EOL 모드 진입요청을 한다
                    tMainTimer[nStepIndex].Start(10000);
                    nProcessStep[nStepIndex]++;
                    break;

                case 496:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        // Can 통신 에러 발생
                        nProcessStep[nStepIndex] = 9000;
                    }

                    // EOL 모드에 정상적으로 진입했다면
                    if (_CanComm.m_ReadMsg.ID == 0x721 && _CanComm.m_ReadMsg.DATA[0] == 0x55 && _CanComm.m_ReadMsg.DATA[1] == 0xAA)
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 497:
                    _tHipotTimer.Stop();
                    _HipotTester.ClearDevice();
                    _HipotTester.DeviceStop();

                    // 캔을 닫는다
                    _CanComm.CloseCan();

                    if (_HipotResult.tr_GB == TEST_RESULT.NG ||
                        _HipotResult.tr_NOSC == TEST_RESULT.NG ||
                        _HipotResult.tr_OSC == TEST_RESULT.NG ||
                        _HipotResult.tr_HIN == TEST_RESULT.NG ||
                        _HipotResult.tr_IRP == TEST_RESULT.NG ||
                        _HipotResult.tr_IRN == TEST_RESULT.NG ||
                        _HipotResult.tr_HIP == TEST_RESULT.NG)
                    {
                        //_HipotResult.tr_TOTAL = TEST_RESULT.NG;
                        //_SysInfo.bContactTestOk[0] = false;
                        //_SysInfo.bContactTestNg[0] = true;

                        //_SysInfo.bContactOneTime[0] = true;
                        //_SysInfo.eContactStatus[0] = CONTACT_STATUS.CONTACT_NG;
                        //nProcessStep[nStepIndex] = 1000;

                        if (_HipotResult.tr_OSC == TEST_RESULT.NG)
                        {
                            // OSC NG일때

                            if (_SysInfo.nOSCRetryNowCount > _Config.nOscRetryCount - 1)
                            {
                                _SysInfo.nOSCRetryNowCount = 0;

                                _HipotResult.tr_TOTAL = TEST_RESULT.NG;
                                _SysInfo.bContactTestOk[0] = false;
                                _SysInfo.bContactTestNg[0] = true;

                                _SysInfo.bContactOneTime[0] = true;
                                _SysInfo.eContactStatus[0] = CONTACT_STATUS.CONTACT_NG;
                                nProcessStep[nStepIndex] = 1000;

                                _mainform.Invoke(new Action(() => _mainform.ViewHipotLog(_HipotResult)));
                                SaveHipotMESData();

                            }
                            else
                            {
                                _SysInfo.nOSCRetryNowCount++;
                                nProcessStep[nStepIndex] = 420;
                            }


                        }
                        else
                        {
                            _HipotResult.tr_TOTAL = TEST_RESULT.NG;
                            _SysInfo.bContactTestOk[0] = false;
                            _SysInfo.bContactTestNg[0] = true;

                            _SysInfo.bContactOneTime[0] = true;
                            _SysInfo.eContactStatus[0] = CONTACT_STATUS.CONTACT_NG;
                            nProcessStep[nStepIndex] = 1000;

                            _mainform.Invoke(new Action(() => _mainform.ViewHipotLog(_HipotResult)));
                            SaveHipotMESData();

                        }
                    }
                    else
                    {
                        _HipotResult.tr_TOTAL = TEST_RESULT.OK;
                        _SysInfo.bContactTestOk[0] = true;

                        _SysInfo.bContactOneTime[0] = true;
                        _SysInfo.bContactTestNg[0] = false;
                        _SysInfo.eContactStatus[0] = CONTACT_STATUS.CONTACT_OK;



                        _SysInfo.ST_TL_RED[0] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_YELLOW[0] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_GREEN[0] = TOWER_LAMP.TL_ON;

                        _mainform.Invoke(new Action(() => _mainform.ViewHipotLog(_HipotResult)));
                        SaveHipotMESData();

                        if (_ModelInfo.bUseHipotAutoContact)
                        {
                            nProcessStep[nStepIndex] = 510; // 양품일경우 자동 해제   
                        }
                        else
                        {
                            nProcessStep[nStepIndex] = 100;
                        }
                    }



                    break;





                // =========================================
                // 리프트가 상승상태
                // 컨텍 작업중이 라면 컨텍 해제 스위치 입력 대기
                case 500:
                    _SysInfo.ST_Yellow[0] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_Red[0] = TOWER_LAMP.TL_BLINK;
                    _SysInfo.ST_Green[0] = TOWER_LAMP.TL_OFF;

                    tMainTimer[nStepIndex].Start(1000);
                    nProcessStep[nStepIndex]++;
                    break;

                case 501:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 100;
                        break;
                    }

                    // 컨텍 해제 스위치 신호가 들어온다면
                    if (GetDIOPort(DI.HIPOT_STOP_SW))
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 502:
                    tMainTimer[nStepIndex].Start(_Config.nChatteringTime);  // 채터링 방지 시간
                    nProcessStep[nStepIndex]++;
                    break;

                case 503:
                    if (GetDIOPort(DI.HIPOT_STOP_SW) && tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 510;
                    }
                    else if (!GetDIOPort(DI.HIPOT_STOP_SW))
                    {
                        nProcessStep[nStepIndex] = 100;
                    }
                    break;


                // 컨텍 해제 시작
                case 510:
                    _SysInfo.ST_Yellow[0] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_Red[0] = TOWER_LAMP.TL_ON;
                    _SysInfo.ST_Green[0] = TOWER_LAMP.TL_OFF;
                    nProcessStep[nStepIndex]++;
                    break;


                case 511:
                    SetDIOPort(DO.HIPOT_PRODUCT_PUSH_ON, false);
                    nProcessStep[nStepIndex]++;
                    break;

                case 512:
                    if (_ModelInfo.bUseHipotFix)
                    {
                        tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                        nProcessStep[nStepIndex]++;
                    }
                    else
                    {
                        nProcessStep[nStepIndex] = 520;
                    }
                    break;

                case 513:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 10000;
                        if (!GetDIOPort(DI.HIPOT_PRODUCT_PUSH1_ON)) { AppendTimeOutMsg(DI.HIPOT_PRODUCT_PUSH1_ON); }
                        if (!GetDIOPort(DI.HIPOT_PRODUCT_PUSH2_ON)) { AppendTimeOutMsg(DI.HIPOT_PRODUCT_PUSH2_ON); }

                        break;
                    }

                    if (GetDIOPort(DI.HIPOT_PRODUCT_PUSH1_ON) && GetDIOPort(DI.HIPOT_PRODUCT_PUSH2_ON))
                    {
                        nProcessStep[nStepIndex] = 520;
                    }
                    break;



                // 상승하강 실린더를 사용하는 경우
                case 520:
                    //MoveTo(AXIS.HIPOT_1X, _ModelInfo._TestInfo[0].dbReadyPos1X, _Config.dbTestZoneMoveSpeed);
                    if (!_ModelInfo.bUseHipot1UpDwContact)
                    {
                        MoveTo(AXIS.HIPOT_1X, _ModelInfo._TestInfo[0].dbReadyPos1X, _Config.dbTestZoneMoveSpeed);
                    }
                    else
                    {
                        MoveTo(AXIS.HIPOT_1Z, _ModelInfo._TestInfo[0].dbReadyPos1Z, _Config.dbTestZoneMoveSpeed);
                    }

                    MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbReadyPos2X, _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 521:
                    if (!MotionDone(AXIS.HIPOT_1X) || !MotionDone(AXIS.HIPOT_2X) || !MotionDone(AXIS.HIPOT_1Z)) { break; }
                    if (!_ModelInfo.bUseHipot1UpDwContact)
                    {
                        MoveTo(AXIS.HIPOT_1Y, _ModelInfo._TestInfo[0].dbReadyPos1Y, _Config.dbTestZoneMoveSpeed);
                        {
                            double dbNowPos1Z = 0;
                            CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_1Z, ref dbNowPos1Z);

                            double dbSpeed = 0;
                            dbSpeed = (Math.Abs(_ModelInfo._TestInfo[0].dbReadyPos1Z - dbNowPos1Z) > _Config.dbTestZoneContactZSlowMovePos) ? _Config.dbTestZoneContactZSlowMoveSpeed : _Config.dbTestZoneMoveSpeed;
                            MoveTo(AXIS.HIPOT_1Z, _ModelInfo._TestInfo[0].dbReadyPos1Z, dbSpeed);
                        }
                    }
                    else
                    {
                        MoveTo(AXIS.HIPOT_1X, _ModelInfo._TestInfo[0].dbReadyPos1X, _Config.dbTestZoneMoveSpeed);
                        MoveTo(AXIS.HIPOT_1Y, _ModelInfo._TestInfo[0].dbReadyPos1Y, _Config.dbTestZoneMoveSpeed);
                    }

                    MoveTo(AXIS.HIPOT_2Y, _ModelInfo._TestInfo[0].dbReadyPos2Y, _Config.dbTestZoneMoveSpeed);
                    {
                        double dbNowPos1Z = 0;
                        CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_2Z, ref dbNowPos1Z);

                        double dbSpeed = 0;
                        dbSpeed = (Math.Abs(_ModelInfo._TestInfo[0].dbReadyPos2Z - dbNowPos1Z) > _Config.dbTestZoneContactZSlowMovePos) ? _Config.dbTestZoneContactZSlowMoveSpeed : _Config.dbTestZoneMoveSpeed;
                        MoveTo(AXIS.HIPOT_2Z, _ModelInfo._TestInfo[0].dbReadyPos2Z, dbSpeed);
                    }




                    nProcessStep[nStepIndex]++;
                    break;

                case 522:
                    nProcessStep[nStepIndex]++;
                    break;

                case 523:
                    if (!MotionDone(AXIS.HIPOT_1X) || !MotionDone(AXIS.HIPOT_2X) || !MotionDone(AXIS.HIPOT_1Y)) { break; }

                    MoveTo(AXIS.HIPOT_1Y, _ModelInfo._TestInfo[0].dbReadyPos1Y, _Config.dbTestZoneMoveSpeed);
                    {
                        double dbNowPos1Z = 0;
                        CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_1Z, ref dbNowPos1Z);

                        double dbSpeed = 0;
                        dbSpeed = (Math.Abs(_ModelInfo._TestInfo[0].dbReadyPos1Z - dbNowPos1Z) > _Config.dbTestZoneContactZSlowMovePos) ? _Config.dbTestZoneContactZSlowMoveSpeed : _Config.dbTestZoneMoveSpeed;
                        MoveTo(AXIS.HIPOT_1Z, _ModelInfo._TestInfo[0].dbReadyPos1Z, dbSpeed);
                    }

                    MoveTo(AXIS.HIPOT_2Y, _ModelInfo._TestInfo[0].dbReadyPos2Y, _Config.dbTestZoneMoveSpeed);
                    {
                        double dbNowPos1Z = 0;
                        CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_2Z, ref dbNowPos1Z);

                        double dbSpeed = 0;
                        dbSpeed = (Math.Abs(_ModelInfo._TestInfo[0].dbReadyPos2Z - dbNowPos1Z) > _Config.dbTestZoneContactZSlowMovePos) ? _Config.dbTestZoneContactZSlowMoveSpeed : _Config.dbTestZoneMoveSpeed;
                        MoveTo(AXIS.HIPOT_2Z, _ModelInfo._TestInfo[0].dbReadyPos2Z, dbSpeed);
                    }


                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 524:
                    if (!MotionDone(AXIS.HIPOT_1Y) || !MotionDone(AXIS.HIPOT_1Z) || !MotionDone(AXIS.HIPOT_1X) || !MotionDone(AXIS.HIPOT_2Y) || !MotionDone(AXIS.HIPOT_2Z)) { break; }

                    nProcessStep[nStepIndex] = 570;
                    break;





                // 컨텍 해제 완료
                case 570:
                    if (_ModelInfo.bUseHipotAutoContact && _SysInfo.bContactTestOk[0])
                    {
                        _SysInfo.bContact_ing[0] = false;
                        _SysInfo.eContactStatus[0] = CONTACT_STATUS.CONTACT_READY;

                        if (_SysInfo.bAutoCycleStop)
                        {
                            nProcessStep[nStepIndex] = 9000;
                            break;
                        }
                        if (!GetDIOPort(DI.EOL_PALLET) && GetDIOPort(DI.EOL_PALLET_DW) && _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7])
                        {
                            tCVTimer.Start(_Config.nCVAutoStopTime);

                            if (!GetDIOPort(DI.EOL_PALLET) && GetDIOPort(DI.EOL_PALLET_DW) && (GetDIOPort(DI.INVERTER1_RUN) || !_Config.bUseMainCVMonitor) && _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7])
                            {
                                nProcessStep[nStepIndex] = 750;
                            }
                        }
                    }
                    else
                    {
                        _SysInfo.bContact_ing[0] = false;
                        _SysInfo.eContactStatus[0] = CONTACT_STATUS.CONTACT_READY;
                        nProcessStep[nStepIndex] = 100;
                    }
                    break;




                // =========================================
                // 리프트가 상승상태
                // 배출 스위치가 눌렸다면
                case 700:
                    tMainTimer[nStepIndex].Start(_Config.nChatteringTime);  // 채터링 방지 시간
                    nProcessStep[nStepIndex]++;
                    break;

                case 701:
                    if (GetDIOPort(DI.HIPOT_FINISH_SW) && tMainTimer[nStepIndex].Verify())
                    {
                        if (_SysInfo.bStationReservation[(int)STATION_LIST.ST6])
                        {
                            _SysInfo.bStationReservation[(int)STATION_LIST.ST6] = false;
                            nProcessStep[nStepIndex] = 100;
                        }
                        else
                        {
                            nProcessStep[nStepIndex] = 710;
                        }
                    }
                    else if (!GetDIOPort(DI.HIPOT_FINISH_SW))
                    {
                        nProcessStep[nStepIndex] = 100;
                    }
                    break;

                // =========================================
                // 배출 조건에 맞아 배출할 경우
                case 710:
                    if (!_SysInfo.bContact_ing[0] && (GetDIOPort(DI.INVERTER1_RUN) || !_Config.bUseMainCVMonitor) &&
                        //!GetDIOPort(DI.EOL_PALLET) && GetDIOPort(DI.EOL_PALLET_DW) && _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7] &&
                        (_SysInfo.bContactOneTime[0] || (_Config.bUseNoProductPass && !GetDIOPort(DI.HIPOT_PRODUCT))) &&
                        GetDIOPort(DI.HIPOT_CABLE1) && GetDIOPort(DI.HIPOT_CABLE2))
                    {

                        if (_Config.bUseHipotStationDwStay)
                        {
                            nProcessStep[nStepIndex] = 750;
                        }
                        else
                        {
                            if (!GetDIOPort(DI.EOL_PALLET) && GetDIOPort(DI.EOL_PALLET_DW) && _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7])
                            {
                                nProcessStep[nStepIndex] = 750;
                            }
                            else
                            {
                                AppendLogMsg(String.Format("HIPOT - 다음스테이션이 준비상태가 아닙니다.", 6), LOG_TYPE.ERROR);
                                _SysInfo.nCount_Beep[4] = 3;
                                nProcessStep[nStepIndex]++;
                            }
                        }
                        break;
                    }
                    //else if (!_SysInfo.bContact_ing[0] && (GetDIOPort(DI.MAIN_CV_ON) || !_Config.bUseMainCVMonitor) &&
                    //        !(!GetDIOPort(DI.EOL_PALLET) && GetDIOPort(DI.EOL_LIFT_DW) && _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7]) && _SysInfo.bContactOneTime[0])
                    //{
                    //    nProcessStep[nStepIndex] = 730;
                    //    break;
                    //}
                    else
                    {
                        // 충방전 불량 제품일 경우 바이패스
                        if (_ModelInfo.bUseScanSTTester && !_SysInfo.bScanSTTestOKNG[(int)STATION_LIST.ST6])
                        {
                            if (!GetDIOPort(DI.EOL_PALLET) && GetDIOPort(DI.EOL_PALLET_DW) && _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7])
                            {
                                tCVTimer.Start(_Config.nCVAutoStopTime);
                                if (!GetDIOPort(DI.EOL_PALLET) && GetDIOPort(DI.EOL_PALLET_DW) && (GetDIOPort(DI.INVERTER1_RUN) || !_Config.bUseMainCVMonitor) && _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7])
                                {
                                    nProcessStep[nStepIndex] = 750;
                                }
                            }
                            else
                            {
                                nProcessStep[nStepIndex] = 730;
                            }
                            break;
                        }

                        if (_SysInfo.bContact_ing[0]) { AppendLogMsg(String.Format("HIPOT - 컨택 상태입니다.", 6), LOG_TYPE.ERROR); }
                        if (_Config.bUseMainCVMonitor) { if (!GetDIOPort(DI.INVERTER1_RUN)) { AppendLogMsg(String.Format("HIPOT - 메인컨베어가 동작중이 아닙니다.", 6), LOG_TYPE.ERROR); } }
                        //if (!(!GetDIOPort(DI.EOL_PALLET) && GetDIOPort(DI.EOL_PALLET_DW) && _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7])) { AppendLogMsg(String.Format("HIPOT - 다음스테이션이 준비상태가 아닙니다.", 6), LOG_TYPE.ERROR); }
                        if (!_SysInfo.bContactOneTime[0]) { AppendLogMsg(String.Format("HIPOT - 제품 검사가 이뤄지지 않았습니다.", 6), LOG_TYPE.ERROR); }
                        if (!GetDIOPort(DI.HIPOT_CABLE1)) { AppendLogMsg("HIPOT - 수동컨텍지그 #1 이 정위치가 아닙니다", LOG_TYPE.ERROR); }
                        if (!GetDIOPort(DI.HIPOT_CABLE2)) { AppendLogMsg("HIPOT - 수동컨텍지그 #2 이 정위치가 아닙니다", LOG_TYPE.ERROR); }
                        _SysInfo.nCount_Beep[4] = 3;
                        nProcessStep[nStepIndex]++;

                    }
                    break;

                case 711:
                    if (!GetDIOPort(DI.HIPOT_FINISH_SW))
                    {
                        nProcessStep[nStepIndex] = 100;
                    }
                    break;


                case 730:
                    if (GetDIOPort(DI.HIPOT_FINISH_SW)) { break; }

                    //_SysInfo.bStationReservation[(int)STATION_LIST.ST6] = true;
                    nProcessStep[nStepIndex] = 100;
                    break;


                case 750:
                    SetDIOPort(DO.HIPOT_PRODUCT_PUSH_ON, false);
                    nProcessStep[nStepIndex]++;
                    break;

                case 751:
                    if (_ModelInfo.bUseHipotFix)
                    {
                        tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                        nProcessStep[nStepIndex] = 752;
                    }
                    else
                    {
                        nProcessStep[nStepIndex] = 760;
                    }
                    break;

                case 752:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 10000;
                        if (!GetDIOPort(DI.EOL_PRODUCT_PUSH1_OFF)) { AppendTimeOutMsg(DI.EOL_PRODUCT_PUSH1_OFF); }
                        if (!GetDIOPort(DI.EOL_PRODUCT_PUSH2_OFF)) { AppendTimeOutMsg(DI.EOL_PRODUCT_PUSH2_OFF); }
                        break;
                    }

                    if (GetDIOPort(DI.EOL_PRODUCT_PUSH1_OFF) && GetDIOPort(DI.EOL_PRODUCT_PUSH2_OFF))
                    {
                        nProcessStep[nStepIndex] = 760;
                    }
                    break;

                // 뭐가됐든 배출시엔 대기위치로
                case 760:
                    if (!MotionDone(AXIS.HIPOT_1X) || !MotionDone(AXIS.HIPOT_2X)) { break; }
                    MoveTo(AXIS.HIPOT_1X, _ModelInfo._TestInfo[0].dbReadyPos1X, _Config.dbTestZoneMoveSpeed);
                    MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbReadyPos2X, _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 761:
                    if (!MotionDone(AXIS.HIPOT_1X) || !MotionDone(AXIS.HIPOT_2X)) { break; }
                    if (!MotionDone(AXIS.HIPOT_1Y) || !MotionDone(AXIS.HIPOT_2Y)) { break; }
                    if (!MotionDone(AXIS.HIPOT_1Z) || !MotionDone(AXIS.HIPOT_2Z)) { break; }
                    MoveTo(AXIS.HIPOT_1Y, _ModelInfo._TestInfo[0].dbReadyPos1Y, _Config.dbTestZoneMoveSpeed);
                    {
                        double dbNowPos1Z = 0;
                        CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_1Z, ref dbNowPos1Z);

                        double dbSpeed = 0;
                        dbSpeed = (Math.Abs(_ModelInfo._TestInfo[0].dbReadyPos1Z - dbNowPos1Z) > _Config.dbTestZoneContactZSlowMovePos) ? _Config.dbTestZoneContactZSlowMoveSpeed : _Config.dbTestZoneMoveSpeed;
                        MoveTo(AXIS.HIPOT_1Z, _ModelInfo._TestInfo[0].dbReadyPos1Z, dbSpeed);
                    }



                    MoveTo(AXIS.HIPOT_2Y, _ModelInfo._TestInfo[0].dbReadyPos2Y, _Config.dbTestZoneMoveSpeed);
                    {
                        double dbNowPos1Z = 0;
                        CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_2Z, ref dbNowPos1Z);

                        double dbSpeed = 0;
                        dbSpeed = (Math.Abs(_ModelInfo._TestInfo[0].dbReadyPos2Z - dbNowPos1Z) > _Config.dbTestZoneContactZSlowMovePos) ? _Config.dbTestZoneContactZSlowMoveSpeed : _Config.dbTestZoneMoveSpeed;
                        MoveTo(AXIS.HIPOT_2Z, _ModelInfo._TestInfo[0].dbReadyPos2Z, dbSpeed);
                    }
                    nProcessStep[nStepIndex]++;
                    break;


                case 762:
                    if (!MotionDone(AXIS.HIPOT_1X) || !MotionDone(AXIS.HIPOT_2X)) { break; }
                    if (!MotionDone(AXIS.HIPOT_1Y) || !MotionDone(AXIS.HIPOT_2Y)) { break; }
                    if (!MotionDone(AXIS.HIPOT_1Z) || !MotionDone(AXIS.HIPOT_2Z)) { break; }

                    if (_Config.bUseHipotStationDwStay)
                    {
                        SetDIOPort(DO.HIPOT_PALLET_DW, true);
                        SetDIOPort(DO.HIPOT_PALLET_UP, false);
                        if (!GetDIOPort(DI.EOL_PALLET) && GetDIOPort(DI.EOL_PALLET_DW) && _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7])
                        {
                            nProcessStep[nStepIndex] = 770;
                        }
                    }
                    else
                    {
                        nProcessStep[nStepIndex] = 770;
                    }
                    break;

                case 770:
                    _tSTCycleTimer[(int)STATION_LIST.ST6].Stop();
                    _tSTCycleEndTime[(int)STATION_LIST.ST6] = DateTime.Now;
                    SaveStationTactTime(STATION_LIST.ST6, _tSTCycleStartTime[(int)STATION_LIST.ST6], _tSTCycleEndTime[(int)STATION_LIST.ST6], 0);
                    SetDIOPort(DO.HIPOT_PALLET_DW, true);
                    SetDIOPort(DO.HIPOT_PALLET_UP, false);
                    if (_Config.bUseStopper || _Config.bUseHipotStationDwStay) { SetDIOPort(DO.HIPOT_STOPPER_DW, true); }
                    _SysInfo.bAutoContactComplated[0] = false;
                    _SysInfo.bContactOneTime[0] = false;

                    _SysInfo.bContactTestNg[1] = _SysInfo.bContactTestNg[0];

                    _SysInfo.bNextPalletOut[(int)STATION_LIST.ST6] = true;   // 배출한다고 알림
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 771:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 10000;
                        AppendTimeOutMsg(DI.HIPOT_PALLET_DW);      // 리프트 하강 타임아웃
                        break;
                    }

                    if (GetDIOPort(DI.HIPOT_PALLET_DW))
                    {
                        tMainTimer[nStepIndex].Start(2000); // 스토퍼 동작 시간
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 772:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    SetDIOPort(DO.HIPOT_STOPPER_DW, false);
                    tMainTimer[nStepIndex].Start(20000);    // 제품 배출 타임아웃
                    nProcessStep[nStepIndex]++;
                    break;

                case 773:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg(String.Format("Station #{0} - 제품 배출 타임아웃.", 6), LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 10000;
                    }


                    if (!GetDIOPort(DI.HIPOT_PALLET))
                    {
                        _SysInfo.ST_Yellow[0] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Red[0] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Green[0] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Buzzer[0] = TOWER_LAMP.TL_OFF;

                        _SysInfo.ST_TL_RED[0] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_YELLOW[0] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_GREEN[0] = TOWER_LAMP.TL_OFF;

                        _HipotResult.Clear();

                        _SysInfo.bScanSTTestOKNG[(int)STATION_LIST.ST6 + 1] = _SysInfo.bScanSTTestOKNG[(int)STATION_LIST.ST6];
                        nProcessStep[nStepIndex] = 100;
                    }
                    break;



                // 검사기와 인터페이스 오류시
                case 1000:
                    _tHipotTimer.Stop();
                    _CanComm.CloseCan();
                    _SysInfo.ST_Yellow[0] = TOWER_LAMP.TL_BLINK;
                    _SysInfo.ST_Red[0] = TOWER_LAMP.TL_BLINK;
                    _SysInfo.ST_Green[0] = TOWER_LAMP.TL_BLINK;
                    _SysInfo.ST_Buzzer[0] = TOWER_LAMP.TL_BLINK;

                    _SysInfo.ST_TL_RED[0] = TOWER_LAMP.TL_ON;
                    _SysInfo.ST_TL_YELLOW[0] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_TL_GREEN[0] = TOWER_LAMP.TL_OFF;
                    nProcessStep[nStepIndex]++;
                    break;

                case 1001:
                    if (GetDIOPort(DI.HIPOT_READY_SW))
                    {
                        tMainTimer[nStepIndex].Start(_Config.nChatteringTime);
                        nProcessStep[nStepIndex] = 1100;
                    }

                    if (GetDIOPort(DI.HIPOT_STOP_SW))
                    {
                        tMainTimer[nStepIndex].Start(_Config.nChatteringTime);
                        _SysInfo.ST_Buzzer[0] = TOWER_LAMP.TL_OFF;
                        nProcessStep[nStepIndex] = 1200;
                    }
                    if (_SysInfo.bAutoCycleStop)
                    {
                        _SysInfo.ST_Yellow[0] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Red[0] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Green[0] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Buzzer[0] = TOWER_LAMP.TL_OFF;

                        _SysInfo.ST_TL_RED[0] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_YELLOW[0] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_GREEN[0] = TOWER_LAMP.TL_OFF;
                        nProcessStep[nStepIndex] = 9000;
                    }
                    break;

                // 컨텍 스위치가 들어올경우 재검사 시작
                case 1100:
                    if (GetDIOPort(DI.HIPOT_READY_SW) && tMainTimer[nStepIndex].Verify())
                    {
                        _SysInfo.ST_Yellow[0] = TOWER_LAMP.TL_ON;
                        _SysInfo.ST_Red[0] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Green[0] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Buzzer[0] = TOWER_LAMP.TL_OFF;

                        _SysInfo.ST_TL_RED[0] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_YELLOW[0] = TOWER_LAMP.TL_ON;
                        _SysInfo.ST_TL_GREEN[0] = TOWER_LAMP.TL_OFF;
                        nProcessStep[nStepIndex] = 1500;
                        break;
                    }
                    else if (!GetDIOPort(DI.HIPOT_READY_SW))
                    {
                        nProcessStep[nStepIndex] = 1001;
                    }
                    break;

                case 1200:
                    if (GetDIOPort(DI.HIPOT_STOP_SW) && tMainTimer[nStepIndex].Verify())
                    {
                        _SysInfo.ST_Yellow[0] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Red[0] = TOWER_LAMP.TL_ON;
                        _SysInfo.ST_Green[0] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Buzzer[0] = TOWER_LAMP.TL_OFF;

                        _SysInfo.ST_TL_RED[0] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_YELLOW[0] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_GREEN[0] = TOWER_LAMP.TL_OFF;

                        nProcessStep[nStepIndex] = 510;
                        break;
                    }
                    else if (!GetDIOPort(DI.HIPOT_STOP_SW))
                    {
                        nProcessStep[nStepIndex] = 1001;
                    }
                    break;

                // Can통신 관련 스텝  컨텍 / 바코드보다 우선임
                case 1500:
                    _SysInfo.ST_Yellow[0] = TOWER_LAMP.TL_ON;
                    _SysInfo.ST_Red[0] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_Green[0] = TOWER_LAMP.TL_OFF;

                    _SysInfo.ST_TL_RED[0] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_TL_YELLOW[0] = TOWER_LAMP.TL_ON;
                    _SysInfo.ST_TL_GREEN[0] = TOWER_LAMP.TL_OFF;


                    if (_ModelInfo.bUseStandAloneCanComm)
                    {
                        nProcessStep[nStepIndex] = 1550;
                        break;
                    }

                    if (_ModelInfo.bUseResuCanComm)
                    {
                        nProcessStep[nStepIndex] = 1600;
                        break;
                    }

                    // 캔 모듈을 사용하지 않는 모델이면 2000번으로 점프하여 검사작업 수행
                    nProcessStep[nStepIndex] = 2000;
                    break;


                // 스탠드 얼론 모델 Can 통신
                case 1550:
                    // 캔 모듈을 초기화 한다
                    if (_CanComm.CanInit(Peak.Can.Basic.TPCANBaudrate.PCAN_BAUD_500K, Peak.Can.Basic.TPCANType.PCAN_TYPE_ISA) == Peak.Can.Basic.TPCANStatus.PCAN_ERROR_OK)
                    {
                        // 정상적으로 초기화를 한경우
                        _CanComm.ClearBuffer(); // 버퍼를 클리어하고
                        _CanComm.WriteFrame(0x600, new byte[] { 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });      // EOL 모드 진입요청을 한다
                        tMainTimer[nStepIndex].Start(10000);
                        nProcessStep[nStepIndex]++;
                    }
                    else
                    {
                        // Can 통신 에러 발생
                        nProcessStep[nStepIndex] = 1950;
                    }
                    break;

                case 1551:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        // Can 통신 에러 발생
                        nProcessStep[nStepIndex] = 1950;
                    }

                    // EOL 모드에 정상적으로 진입했다면
                    if (_CanComm.m_ReadMsg.ID == 0x601 && _CanComm.m_ReadMsg.DATA[0] == 0xAA)
                    {
                        _CanComm.ClearBuffer(); // 버퍼를 클리어하고
                        _CanComm.WriteFrame(0x602, new byte[] { 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });      // 전원 인가 요청을 한다
                        tMainTimer[nStepIndex].Start(10000);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 1552:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        // Can 통신 에러 발생
                        nProcessStep[nStepIndex] = 1950;
                    }

                    // 전원 인가가 정상적으로 이뤄졌다면
                    if (_CanComm.m_ReadMsg.ID == 0x603 && _CanComm.m_ReadMsg.DATA[0] == 0xFF && _CanComm.m_ReadMsg.DATA[1] == 0xAA)
                    {
                        nProcessStep[nStepIndex] = 2000;    // 검사를 시작한다
                    }
                    break;



                // 스탠드 얼론 모델 Can 통신
                case 1600:
                    // 캔 모듈을 초기화 한다
                    if (_CanComm.CanInit(Peak.Can.Basic.TPCANBaudrate.PCAN_BAUD_500K, Peak.Can.Basic.TPCANType.PCAN_TYPE_ISA) == Peak.Can.Basic.TPCANStatus.PCAN_ERROR_OK)
                    {
                        // 정상적으로 초기화를 한경우
                        _CanComm.ClearBuffer(); // 버퍼를 클리어하고
                        _CanComm.WriteFrame(0x001, new byte[] { 0x55, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });      // EOL 모드 진입요청을 한다
                        tMainTimer[nStepIndex].Start(10000);
                        nProcessStep[nStepIndex]++;
                    }
                    else
                    {
                        // Can 통신 에러 발생
                        nProcessStep[nStepIndex] = 1950;
                    }
                    break;

                case 1601:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        // Can 통신 에러 발생
                        nProcessStep[nStepIndex] = 1950;
                    }

                    // EOL 모드에 정상적으로 진입했다면
                    if (_CanComm.m_ReadMsg.ID == 0x701 && _CanComm.m_ReadMsg.DATA[0] == 0x55 && _CanComm.m_ReadMsg.DATA[1] == 0xAA)
                    {
                        _CanComm.ClearBuffer(); // 버퍼를 클리어하고
                        _CanComm.WriteFrame(0x02C, new byte[] { 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });      // 전원 인가 요청을 한다
                        tMainTimer[nStepIndex].Start(10000);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 1602:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        // Can 통신 에러 발생
                        nProcessStep[nStepIndex] = 1950;
                    }

                    // EOL 모드에 정상적으로 진입했다면
                    if (_CanComm.m_ReadMsg.ID == 0x72C && _CanComm.m_ReadMsg.DATA[0] == 0x55 && _CanComm.m_ReadMsg.DATA[1] == 0xAA)
                    {
                        _CanComm.ClearBuffer(); // 버퍼를 클리어하고
                        _CanComm.WriteFrame(0x02C, new byte[] { 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });      // 전원 인가 요청을 한다
                        tMainTimer[nStepIndex].Start(10000);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 1603:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        // Can 통신 에러 발생
                        nProcessStep[nStepIndex] = 1950;
                    }

                    // EOL 모드에 정상적으로 진입했다면
                    if (_CanComm.m_ReadMsg.ID == 0x72C && _CanComm.m_ReadMsg.DATA[0] == 0x55 && _CanComm.m_ReadMsg.DATA[1] == 0xAA)
                    {
                        nProcessStep[nStepIndex] = 2000;
                    }
                    break;


                // Can 통신 NG 스텝
                case 1950:
                    // Can 모듈을 닫고 에러 처리
                    _CanComm.CloseCan();
                    AppendLogMsg("HIPOT Can 통신 에러", LOG_TYPE.ERROR);
                    nProcessStep[nStepIndex] = 9000;
                    break;





                // 바코드 스캔 작업 및 비전 작업
                case 2000:
                    if (_ModelInfo.bUseHipotFix)
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    else
                    {
                        nProcessStep[nStepIndex] = 2050;
                    }
                    break;


                case 2001:
                    SetDIOPort(DO.HIPOT_PRODUCT_PUSH_ON, true);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2002:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        if (GetDIOPort(DI.HIPOT_PRODUCT_PUSH1_ON)) { AppendTimeOutMsg(DI.HIPOT_PRODUCT_PUSH1_ON); }
                        if (GetDIOPort(DI.HIPOT_PRODUCT_PUSH2_ON)) { AppendTimeOutMsg(DI.HIPOT_PRODUCT_PUSH2_ON); }
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }

                    if (GetDIOPort(DI.HIPOT_PRODUCT_PUSH1_ON) && GetDIOPort(DI.HIPOT_PRODUCT_PUSH2_ON))
                    {
                        tMainTimer[nStepIndex].Start(200);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 2003:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    _HipotResult.Clear();
                    nProcessStep[nStepIndex] = 2050;
                    break;


                case 2050:
                    if (_ModelInfo.bUseOmronHipotTest)
                    {
                        nProcessStep[nStepIndex] = 2060;
                    }
                    else
                    {
                        if (_ModelInfo.bUseHipotBCDScanner)
                        {
                            nProcessStep[nStepIndex] = 2100;
                        }
                        else
                        {
                            nProcessStep[nStepIndex] = 2500;
                        }
                    }
                    break;

                case 2060:
                    _HIPOTReader.bReadOk = false;
                    nProcessStep[nStepIndex]++;
                    break;

                case 2061:
                    if (_HIPOTReader.bReadOk)
                    {
                        _HipotResult.strBCD = _HIPOTReader.strReadBarcode;
                        nProcessStep[nStepIndex]++;
                    }
                    break;


                case 2062:
                    _mainform.BeginInvoke(new Action(() => _mainform.DSViewFormOpen()));
                    nProcessStep[nStepIndex]++;
                    break;

                case 2063:
                    if (!GetDIOPort(DI.HIPOT_READY_SW))
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 2064:
                    if (GetDIOPort(DI.HIPOT_READY_SW))
                    {
                        tMainTimer[nStepIndex].Start(50);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 2065:
                    if (GetDIOPort(DI.HIPOT_READY_SW) && tMainTimer[nStepIndex].Verify())
                    {
                        _mainform.BeginInvoke(new Action(() => _mainform.DSViewClose()));
                        nProcessStep[nStepIndex] = 2400;
                    }
                    else if (!GetDIOPort(DI.HIPOT_READY_SW))
                    {
                        nProcessStep[nStepIndex] = 2063;
                    }
                    break;

                case 2100:
                    if (!MotionDone(AXIS.HIPOT_2X) || !MotionDone(AXIS.HIPOT_2Y) || !MotionDone(AXIS.HIPOT_2Z)) { break; }

                    MoveTo(AXIS.HIPOT_1X, _ModelInfo._TestInfo[0].dbReadyPos1X, _Config.dbTestZoneMoveSpeed);
                    MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbReadyPos2X, _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2101:
                    if (!MotionDone(AXIS.HIPOT_2X) || !MotionDone(AXIS.HIPOT_1X)) { break; }

                    if (_ModelInfo.bUseHipot1UpDwContact)
                    {
                        MoveTo(AXIS.HIPOT_1X, _ModelInfo._TestInfo[0].dbContactPos1X, _Config.dbTestZoneMoveSpeed);
                        MoveTo(AXIS.HIPOT_1Y, _ModelInfo._TestInfo[0].dbContactPos1Y, _Config.dbTestZoneMoveSpeed);
                    }
                    else
                    {
                        MoveTo(AXIS.HIPOT_1Y, _ModelInfo._TestInfo[0].dbContactPos1Y, _Config.dbTestZoneMoveSpeed);
                        {
                            double dbNowPos1Z = 0;
                            CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_1Z, ref dbNowPos1Z);

                            double dbSpeed = 0;
                            dbSpeed = (Math.Abs(_ModelInfo._TestInfo[0].dbContactPos1Z - dbNowPos1Z) > _Config.dbTestZoneContactZSlowMovePos) ? _Config.dbTestZoneContactZSlowMoveSpeed : _Config.dbTestZoneMoveSpeed;
                            MoveTo(AXIS.HIPOT_1Z, _ModelInfo._TestInfo[0].dbContactPos1Z, dbSpeed);
                        }
                    }


                    MoveTo(AXIS.HIPOT_2Y, _ModelInfo._TestInfo[0].dbSpare_b[1], _Config.dbTestZoneMoveSpeed);
                    {
                        double dbNowPos1Z = 0;
                        CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_2Z, ref dbNowPos1Z);

                        double dbSpeed = 0;
                        dbSpeed = (Math.Abs(_ModelInfo._TestInfo[0].dbSpare_b[2] - dbNowPos1Z) > _Config.dbTestZoneContactZSlowMovePos) ? _Config.dbTestZoneContactZSlowMoveSpeed : _Config.dbTestZoneMoveSpeed;
                        MoveTo(AXIS.HIPOT_2Z, _ModelInfo._TestInfo[0].dbSpare_b[2], dbSpeed);
                    }

                    nProcessStep[nStepIndex]++;
                    break;

                case 2102:
                    if (!MotionDone(AXIS.HIPOT_2Y) || !MotionDone(AXIS.HIPOT_2Z)) { break; }

                    MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbSpare_b[0], _Config.dbTestZoneMoveSpeed);
                    _HIPOTReader.bReadOk = false;
                    _HIPOTReader.TriggerOn();
                    nProcessStep[nStepIndex] = 2110;
                    break;

                // 바코드 스캔 시도
                case 2110:
                    //if (MotionDone(AXIS.HIPOT_2X))
                    //{
                    //    tMainTimer[nStepIndex].Start(_Config.nBCDScanTimeOut);
                    //    nProcessStep[nStepIndex]++;
                    //    break;
                    //}

                    //if (_HIPOTReader.bReadOk)
                    //{
                    //    _HipotResult.strBCD = _HIPOTReader.strReadBarcode;
                    //    nProcessStep[nStepIndex] = 2400;
                    //}
                    if (MotionDone(AXIS.HIPOT_2X))
                    {
                        // ===== 거리 측정하여 보정
                        //_SysInfo.dbHipot1DistanceGap = _ModelInfo.dbHipot1Distance - _TesterDistance.dbDistance[1];     // 거리 편차를 구함

                        //// 거리측정을 사용하고 거리가 지정수치 이상일경우
                        //if (_ModelInfo.bUseHipot1Distance)
                        //{
                        //    if (_SysInfo.dbHipot1DistanceGap > 100)
                        //    {
                        //        _SysInfo.eContactStatus[0] = CONTACT_STATUS.CONTACT_ALARM;
                        //        AppendLogMsg(String.Format("Station #{0} - 하이팟 거리측정 실패.", 6), LOG_TYPE.ERROR);
                        //        _HIPOTReader.TriggerOff();
                        //        nProcessStep[nStepIndex] = 1000;    // 커뮤니케이션 실패
                        //        break;
                        //    }
                        //}

                        if (_HIPOTReader.bReadOk)
                        {
                            _HipotResult.strBCD = _HIPOTReader.strReadBarcode;
                            nProcessStep[nStepIndex] = 2400;
                        }
                        else
                        {
                            tMainTimer[nStepIndex].Start(_Config.nBCDScanTimeOut);
                            nProcessStep[nStepIndex]++;
                        }
                    }
                    break;

                case 2111:
                    if (!tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex]++;
                        break;
                    }

                    if (_HIPOTReader.bReadOk)
                    {
                        _HipotResult.strBCD = _HIPOTReader.strReadBarcode;
                        nProcessStep[nStepIndex] = 2400;
                    }
                    break;

                case 2112:
                    //if (tMainTimer[nStepIndex].Verify())
                    //{
                    //    _SysInfo.eContactStatus[0] = CONTACT_STATUS.CONTACT_ALARM;
                    //    AppendLogMsg(String.Format("Station #{0} - 바코드 스캔 실패.", 6), LOG_TYPE.ERROR);
                    //    _HIPOTReader.TriggerOff();
                    //    nProcessStep[nStepIndex] = 1000;    // 커뮤니케이션 실패
                    //    break;
                    //}

                    MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbSpare_b[0] + 2, _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex] = 2120;
                    break;


                // 바코드 재검사 루틴
                case 2120:
                    if (MotionDone(AXIS.HIPOT_2X))
                    {
                        MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbSpare_b[0], _Config.dbTestZoneMoveSpeed);
                        nProcessStep[nStepIndex]++;
                    }

                    if (_HIPOTReader.bReadOk)
                    {
                        _HipotResult.strBCD = _HIPOTReader.strReadBarcode;
                        nProcessStep[nStepIndex] = 2400;
                    }
                    break;

                case 2121:
                    if (MotionDone(AXIS.HIPOT_2X))
                    {
                        MoveTo(AXIS.HIPOT_2Y, _ModelInfo._TestInfo[0].dbSpare_b[1] - 2, _Config.dbTestZoneMoveSpeed);
                        nProcessStep[nStepIndex]++;
                    }

                    if (_HIPOTReader.bReadOk)
                    {
                        _HipotResult.strBCD = _HIPOTReader.strReadBarcode;
                        nProcessStep[nStepIndex] = 2400;
                    }
                    break;

                case 2122:
                    if (MotionDone(AXIS.HIPOT_2Y))
                    {
                        MoveTo(AXIS.HIPOT_2Y, _ModelInfo._TestInfo[0].dbSpare_b[1] + 2, _Config.dbTestZoneMoveSpeed);
                        nProcessStep[nStepIndex]++;
                    }

                    if (_HIPOTReader.bReadOk)
                    {
                        _HipotResult.strBCD = _HIPOTReader.strReadBarcode;
                        nProcessStep[nStepIndex] = 2400;
                    }
                    break;

                case 2123:
                    if (MotionDone(AXIS.HIPOT_2Y))
                    {
                        MoveTo(AXIS.HIPOT_2Y, _ModelInfo._TestInfo[0].dbSpare_b[1], _Config.dbTestZoneMoveSpeed);
                        nProcessStep[nStepIndex]++;
                    }

                    if (_HIPOTReader.bReadOk)
                    {
                        _HipotResult.strBCD = _HIPOTReader.strReadBarcode;
                        nProcessStep[nStepIndex] = 2400;
                    }
                    break;


                case 2124:
                    if (MotionDone(AXIS.HIPOT_2Y))
                    {
                        _SysInfo.eContactStatus[0] = CONTACT_STATUS.CONTACT_ALARM;
                        AppendLogMsg(String.Format("Station #{0} - 바코드 스캔 실패.", 6), LOG_TYPE.ERROR);
                        _HIPOTReader.TriggerOff();
                        nProcessStep[nStepIndex] = 1000;    // 커뮤니케이션 실패
                    }
                    break;




                // 스캔완료 스텝
                case 2400:
                    if (!MotionDone(AXIS.HIPOT_2X) || !MotionDone(AXIS.HIPOT_2Y) || !MotionDone(AXIS.HIPOT_2Z)) { break; }

                    if (_Config.bUseMESTestCheck)
                    {
                        if (!Check_Server_Barcode(_HIPOTReader.strReadBarcode, 0))
                        {
                            _SysInfo.eContactStatus[0] = CONTACT_STATUS.CONTACT_ALARM;
                            AppendLogMsg(String.Format("Station #{0} - MES ERROR.", 6), LOG_TYPE.ERROR);
                            _HIPOTReader.TriggerOff();
                            nProcessStep[nStepIndex] = 1000;    // 커뮤니케이션 실패
                            break;
                        }

                    }

                    // 중복바코드가 존재한다면
                    if (CheckHipotBcdDuplicate(_HIPOTReader.strReadBarcode))
                    {
                        _SysInfo.eContactStatus[0] = CONTACT_STATUS.CONTACT_ALARM;
                        if (_Config.strLangue == "KOR") { AppendLogMsg(String.Format("HIPOT - 중복 바코드 입니다."), LOG_TYPE.ERROR); }
                        else { AppendLogMsg(String.Format("HIPOT - 重复条形码。"), LOG_TYPE.ERROR); }

                        _HIPOTReader.TriggerOff();
                        nProcessStep[nStepIndex] = 1000;    // 커뮤니케이션 실패
                        break;
                    }

                    nProcessStep[nStepIndex] = 2500;
                    break;



                // 비전 검사
                case 2500:
                    if (_ModelInfo.bUseTopCamera)
                    {
                        nProcessStep[nStepIndex] = 2600;
                    }
                    else
                    {
                        //nProcessStep[nStepIndex] = 410;
                        nProcessStep[nStepIndex] = 2790;
                    }
                    break;



                case 2600:
                    if (!MotionDone(AXIS.HIPOT_2X) || !MotionDone(AXIS.HIPOT_2Y) || !MotionDone(AXIS.HIPOT_2Z)) { break; }

                    MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbReadyPos2X, _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2601:
                    if (!MotionDone(AXIS.HIPOT_2X)) { break; }

                    MoveTo(AXIS.HIPOT_2Y, _ModelInfo._TestInfo[0].dbSpare_b[4], _Config.dbTestZoneMoveSpeed);
                    {
                        double dbNowPos1Z = 0;
                        CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_2Z, ref dbNowPos1Z);

                        double dbSpeed = 0;
                        dbSpeed = (Math.Abs(_ModelInfo._TestInfo[0].dbSpare_b[5] - dbNowPos1Z) > _Config.dbTestZoneContactZSlowMovePos) ? _Config.dbTestZoneContactZSlowMoveSpeed : _Config.dbTestZoneMoveSpeed;
                        MoveTo(AXIS.HIPOT_2Z, _ModelInfo._TestInfo[0].dbSpare_b[5], dbSpeed);
                    }
                    nProcessStep[nStepIndex]++;
                    break;

                case 2602:
                    if (!MotionDone(AXIS.HIPOT_2Y) || !MotionDone(AXIS.HIPOT_2Z)) { break; }

                    //MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbSpare_b[3], _Config.dbTestZoneMoveSpeed);
                    //if (_ModelInfo.bUseHipot1Distance && _ModelInfo.bUseHipotBCDScanner)
                    //{
                    //    MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbSpare_b[3] + _SysInfo.dbHipot1DistanceGap, _Config.dbTestZoneMoveSpeed);
                    //}
                    //else
                    //{
                        MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbSpare_b[3], _Config.dbTestZoneMoveSpeed);
                    //}
                    nProcessStep[nStepIndex]++;
                    break;

                case 2603:
                    if (!MotionDone(AXIS.HIPOT_2X)) { break; }

                    nProcessStep[nStepIndex] = 2610;
                    break;

                // 상부 라벨 검사
                case 2610:
                    // 검사시작전에 파일이 있으면 파일을 삭제함
                    if (File.Exists(String.Format("{0}.BMP", _Config.strVisionDir1)))
                    {
                        File.Delete(String.Format("{0}.BMP", _Config.strVisionDir1));
                    }

                    SetCmeraSch(0, _ModelInfo._TestInfo[0].nSpare_a[0]);
                    tMainTimer[nStepIndex].Start(100);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2611:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    if (!GetDIOPort(DI.CAMERA1_BUSY))
                    {
                        nProcessStep[nStepIndex] = 2620;
                    }
                    break;


                case 2620:
                    SetDIOPort(DO.CAMERA1_TRIG, true);
                    tMainTimer[nStepIndex].Start(100);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2621:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    if (!GetDIOPort(DI.CAMERA1_BUSY))
                    {
                        SetDIOPort(DO.CAMERA1_TRIG, false);
                        nProcessStep[nStepIndex]++;
                    }
                    break;


                case 2622:
                    if (GetDIOPort(DI.CAMERA1_TOTAL))
                    {
                        nProcessStep[nStepIndex] = 2700;
                        tMainTimer[nStepIndex].Start(20000);
                    }
                    else
                    {
                        nProcessStep[nStepIndex] = 2710;
                        tMainTimer[nStepIndex].Start(20000);
                    }
                    break;



                case 2700:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        _SysInfo.eContactStatus[0] = CONTACT_STATUS.CONTACT_ALARM;
                        AppendLogMsg(String.Format("Hipot - Vision Img Load Fail.."), LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;    // 커뮤니케이션 실패
                        break;
                    }

                    if (File.Exists(String.Format("{0}.BMP", _Config.strVisionDir1)))
                    {
                        tMainTimer[nStepIndex].Start(500);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 2701:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    _mainform.BeginInvoke(new Action(() => _mainform.ViewVisionData(0, _HipotResult.strBCD)));
                    nProcessStep[nStepIndex]++;
                    break;

                case 2702:
                    nProcessStep[nStepIndex] = 2790;
                    break;


                case 2710:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        _SysInfo.eContactStatus[0] = CONTACT_STATUS.CONTACT_ALARM;
                        AppendLogMsg(String.Format("Hipot - Vision Img Load Fail.."), LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;    // 커뮤니케이션 실패
                        break;
                    }

                    if (File.Exists(String.Format("{0}.BMP", _Config.strVisionDir1)))
                    {
                        tMainTimer[nStepIndex].Start(500);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 2711:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    _mainform.BeginInvoke(new Action(() => _mainform.ViewVisionData(0, _HipotResult.strBCD)));
                    nProcessStep[nStepIndex]++;
                    break;

                case 2712:
                    _SysInfo.eContactStatus[0] = CONTACT_STATUS.CONTACT_ALARM;
                    AppendLogMsg(String.Format("Hipot - Vision NG.."), LOG_TYPE.ERROR);
                    nProcessStep[nStepIndex] = 1000;    // 커뮤니케이션 실패
                    break;

                // 전면 검사하는지 체크
                case 2790:
                    if (_ModelInfo.bUseFrotCamera)
                    {
                        nProcessStep[nStepIndex] = 2800;
                    }
                    else
                    {
                        nProcessStep[nStepIndex] = 410;
                    }
                    break;

                // 전면 포인트 검사
                case 2800:
                    if (!MotionDone(AXIS.HIPOT_2X) || !MotionDone(AXIS.HIPOT_2Y) || !MotionDone(AXIS.HIPOT_2Z)) { break; }

                    MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbReadyPos2X, _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2801:
                    if (!MotionDone(AXIS.HIPOT_2X)) { break; }

                    MoveTo(AXIS.HIPOT_2Y, _ModelInfo._TestInfo[0].dbSpare_b[7], _Config.dbTestZoneMoveSpeed);
                    {
                        double dbNowPos1Z = 0;
                        CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_2Z, ref dbNowPos1Z);

                        double dbSpeed = 0;
                        dbSpeed = (Math.Abs(_ModelInfo._TestInfo[0].dbSpare_b[8] - dbNowPos1Z) > _Config.dbTestZoneContactZSlowMovePos) ? _Config.dbTestZoneContactZSlowMoveSpeed : _Config.dbTestZoneMoveSpeed;
                        MoveTo(AXIS.HIPOT_2Z, _ModelInfo._TestInfo[0].dbSpare_b[8], dbSpeed);
                    }
                    nProcessStep[nStepIndex]++;
                    break;

                case 2802:
                    if (!MotionDone(AXIS.HIPOT_2Y) || !MotionDone(AXIS.HIPOT_2Z)) { break; }

                    //MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbSpare_b[6], _Config.dbTestZoneMoveSpeed);
                    //if (_ModelInfo.bUseHipot1Distance && _ModelInfo.bUseHipotBCDScanner)
                    //{
                    //    MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbSpare_b[6] + _SysInfo.dbHipot1DistanceGap, _Config.dbTestZoneMoveSpeed);
                    //}
                    //else
                    //{
                        MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbSpare_b[6], _Config.dbTestZoneMoveSpeed);
                    //}
                    nProcessStep[nStepIndex]++;
                    break;

                case 2803:
                    if (!MotionDone(AXIS.HIPOT_2X)) { break; }

                    nProcessStep[nStepIndex] = 2810;
                    break;

                // 상부 라벨 검사
                case 2810:
                    // 검사시작전에 파일이 있으면 파일을 삭제함
                    if (File.Exists(String.Format("{0}.BMP", _Config.strVisionDir2)))
                    {
                        File.Delete(String.Format("{0}.BMP", _Config.strVisionDir2));
                    }

                    SetCmeraSch(1, _ModelInfo._TestInfo[0].nSpare_a[1]);
                    tMainTimer[nStepIndex].Start(100);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2811:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    if (!GetDIOPort(DI.CAMERA2_BUSY))
                    {
                        nProcessStep[nStepIndex] = 2820;
                    }
                    break;


                case 2820:
                    SetDIOPort(DO.CAMERA2_TRIG, true);
                    tMainTimer[nStepIndex].Start(100);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2821:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    if (!GetDIOPort(DI.CAMERA2_BUSY))
                    {
                        SetDIOPort(DO.CAMERA2_TRIG, false);
                        nProcessStep[nStepIndex]++;
                    }
                    break;


                case 2822:
                    if (GetDIOPort(DI.CAMERA2_TOTAL))
                    {
                        // 양품 행정
                        nProcessStep[nStepIndex] = 2900;
                        tMainTimer[nStepIndex].Start(20000);
                    }
                    else
                    {

                        nProcessStep[nStepIndex] = 2910;
                        tMainTimer[nStepIndex].Start(20000);
                    }
                    break;



                case 2900:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        _SysInfo.eContactStatus[0] = CONTACT_STATUS.CONTACT_ALARM;
                        AppendLogMsg(String.Format("Hipot - Vision Img Load Fail.."), LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;    // 커뮤니케이션 실패
                        break;
                    }

                    if (File.Exists(String.Format("{0}.BMP", _Config.strVisionDir2)))
                    {
                        tMainTimer[nStepIndex].Start(500);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 2901:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    _mainform.BeginInvoke(new Action(() => _mainform.ViewVisionData(1, _HipotResult.strBCD)));
                    nProcessStep[nStepIndex]++;
                    break;

                case 2902:
                    nProcessStep[nStepIndex] = 410;
                    break;



                case 2910:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        _SysInfo.eContactStatus[0] = CONTACT_STATUS.CONTACT_ALARM;
                        AppendLogMsg(String.Format("Hipot - Vision Img Load Fail.."), LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1000;    // 커뮤니케이션 실패
                        break;
                    }

                    if (File.Exists(String.Format("{0}.BMP", _Config.strVisionDir2)))
                    {
                        tMainTimer[nStepIndex].Start(500);
                        nProcessStep[nStepIndex]++;
                    }
                    break;


                case 2911:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    _mainform.BeginInvoke(new Action(() => _mainform.ViewVisionData(1, _HipotResult.strBCD)));
                    nProcessStep[nStepIndex]++;
                    break;

                case 2912:
                    _SysInfo.eContactStatus[0] = CONTACT_STATUS.CONTACT_ALARM;
                    AppendLogMsg(String.Format("Hipot - Vision NG.."), LOG_TYPE.ERROR);
                    nProcessStep[nStepIndex] = 1000;    // 커뮤니케이션 실패
                    break;





                //// 움직이면서 체크
                //case 3000:
                //    if (!MotionDone(AXIS.HIPOT_2X)) { break; }
                //    MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbContactPos2X - _Config.dbTestZoneContactMovePos, _Config.dbTestZoneMoveSpeed);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 3001:
                //    if (!MotionDone(AXIS.HIPOT_2X)) { break; }

                //    MoveTo(AXIS.HIPOT_2Y, _ModelInfo._TestInfo[0].dbContactPos2Y - 1.0, _Config.dbTestZoneMoveSpeed);
                //    MoveTo(AXIS.HIPOT_2Z, _ModelInfo._TestInfo[0].dbContactPos2Z - 1.0, _Config.dbTestZoneMoveSpeed);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 3002:
                //    if (!MotionDone(AXIS.HIPOT_2Y) || !MotionDone(AXIS.HIPOT_2Z)) { break; }

                //    MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbContactPos2X, _Config.dbTestZoneContactSpeed);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 3003:
                //    if (!MotionDone(AXIS.HIPOT_2X)) { break; }

                //    if (GetDIOPort(DI.HIPOT_G_CONTACT_OK) &&
                //        GetDIOPort(DI.HIPOT_N_CONTACT_OK) &&
                //        GetDIOPort(DI.HIPOT_P_CONTACT_OK))
                //    {
                //        _mainform.BeginInvoke(new Action(() => _mainform.ViewHIPOTContactInof()));
                //        nProcessStep[nStepIndex] = 425;
                //    }
                //    else
                //    {
                //        nProcessStep[nStepIndex] = 3010;
                //    }
                //    break;



                //case 3010:
                //    if (!MotionDone(AXIS.HIPOT_2X)) { break; }
                //    MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbContactPos2X - _Config.dbTestZoneContactMovePos, _Config.dbTestZoneMoveSpeed);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 3011:
                //    if (!MotionDone(AXIS.HIPOT_2X)) { break; }

                //    MoveTo(AXIS.HIPOT_2Y, _ModelInfo._TestInfo[0].dbContactPos2Y + 1.0, _Config.dbTestZoneMoveSpeed);
                //    MoveTo(AXIS.HIPOT_2Z, _ModelInfo._TestInfo[0].dbContactPos2Z - 1.0, _Config.dbTestZoneMoveSpeed);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 3012:
                //    if (!MotionDone(AXIS.HIPOT_2Y) || !MotionDone(AXIS.HIPOT_2Z)) { break; }

                //    MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbContactPos2X, _Config.dbTestZoneContactSpeed);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 3013:
                //    if (!MotionDone(AXIS.HIPOT_2X)) { break; }

                //    if (GetDIOPort(DI.HIPOT_G_CONTACT_OK) &&
                //        GetDIOPort(DI.HIPOT_N_CONTACT_OK) &&
                //        GetDIOPort(DI.HIPOT_P_CONTACT_OK))
                //    {
                //        _mainform.BeginInvoke(new Action(() => _mainform.ViewHIPOTContactInof()));
                //        nProcessStep[nStepIndex] = 425;
                //    }
                //    else
                //    {
                //        nProcessStep[nStepIndex] = 3020;
                //    }
                //    break;



                //case 3020:
                //    if (!MotionDone(AXIS.HIPOT_2X)) { break; }
                //    MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbContactPos2X - _Config.dbTestZoneContactMovePos, _Config.dbTestZoneMoveSpeed);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 3021:
                //    if (!MotionDone(AXIS.HIPOT_2X)) { break; }

                //    MoveTo(AXIS.HIPOT_2Y, _ModelInfo._TestInfo[0].dbContactPos2Y - 1.0, _Config.dbTestZoneMoveSpeed);
                //    MoveTo(AXIS.HIPOT_2Z, _ModelInfo._TestInfo[0].dbContactPos2Z + 1.0, _Config.dbTestZoneMoveSpeed);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 3022:
                //    if (!MotionDone(AXIS.HIPOT_2Y) || !MotionDone(AXIS.HIPOT_2Z)) { break; }

                //    MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbContactPos2X, _Config.dbTestZoneContactSpeed);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 3023:
                //    if (!MotionDone(AXIS.HIPOT_2X)) { break; }

                //    if (GetDIOPort(DI.HIPOT_G_CONTACT_OK) &&
                //        GetDIOPort(DI.HIPOT_N_CONTACT_OK) &&
                //        GetDIOPort(DI.HIPOT_P_CONTACT_OK))
                //    {
                //        _mainform.BeginInvoke(new Action(() => _mainform.ViewHIPOTContactInof()));
                //        nProcessStep[nStepIndex] = 425;
                //    }
                //    else
                //    {
                //        nProcessStep[nStepIndex] = 3030;
                //    }
                //    break;

                //case 3030:
                //    if (!MotionDone(AXIS.HIPOT_2X)) { break; }
                //    MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbContactPos2X - _Config.dbTestZoneContactMovePos, _Config.dbTestZoneMoveSpeed);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 3031:
                //    if (!MotionDone(AXIS.HIPOT_2X)) { break; }

                //    MoveTo(AXIS.HIPOT_2Y, _ModelInfo._TestInfo[0].dbContactPos2Y + 1.0, _Config.dbTestZoneMoveSpeed);
                //    MoveTo(AXIS.HIPOT_2Z, _ModelInfo._TestInfo[0].dbContactPos2Z + 1.0, _Config.dbTestZoneMoveSpeed);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 3032:
                //    if (!MotionDone(AXIS.HIPOT_2Y) || !MotionDone(AXIS.HIPOT_2Z)) { break; }

                //    MoveTo(AXIS.HIPOT_2X, _ModelInfo._TestInfo[0].dbContactPos2X, _Config.dbTestZoneContactSpeed);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 3033:
                //    if (!MotionDone(AXIS.HIPOT_2X)) { break; }

                //    if (GetDIOPort(DI.HIPOT_G_CONTACT_OK) &&
                //        GetDIOPort(DI.HIPOT_N_CONTACT_OK) &&
                //        GetDIOPort(DI.HIPOT_P_CONTACT_OK))
                //    {
                //        _mainform.BeginInvoke(new Action(() => _mainform.ViewHIPOTContactInof()));
                //        nProcessStep[nStepIndex] = 425;
                //    }
                //    else
                //    {
                //        AppendLogMsg("Hipot - Contact Fail..", LOG_TYPE.ERROR);
                //        SetDIOPort(DO.HIPOT_CONTACT_CHECK, false);
                //        nProcessStep[nStepIndex] = 1000;
                //    }
                //    break;



                case 9000:
                    _SysInfo.ST_Yellow[0] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_Red[0] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_Green[0] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_Buzzer[0] = TOWER_LAMP.TL_OFF;

                    _SysInfo.ST_TL_RED[0] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_TL_YELLOW[0] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_TL_GREEN[0] = TOWER_LAMP.TL_OFF;
                    _SysInfo.bStationAutoMode[(int)STATION_LIST.ST6] = false;
                    break;

                case 10000:
                    nProcessStep[nStepIndex] = 9000;
                    _SysInfo.TL_Buzzer = TOWER_LAMP.TL_ON;
                    break;
            }

        }
        //===========================================================






        //===========================================================
        //====== 리턴 리프트 ========================================
        static void WorkOutLiftProcess()
        {
            int nStepIndex = (int)PROC_LIST.RELIFT;

            if (!_SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING])
            {
                nProcessStep[nStepIndex] = 0;

                if (_tSTCycleTimer[(int)STATION_LIST.UNLOADING].IsRunning)
                {
                    _tSTCycleTimer[(int)STATION_LIST.UNLOADING].Stop();
                    _tSTCycleEndTime[(int)STATION_LIST.UNLOADING] = DateTime.Now;
                    SaveStationTactTime(STATION_LIST.UNLOADING, _tSTCycleStartTime[(int)STATION_LIST.UNLOADING], _tSTCycleEndTime[(int)STATION_LIST.UNLOADING], 1);
                }

                return;

            } // 수동모드

            
            switch (nProcessStep[nStepIndex])
            {
                case 0:
                    if (GetDIOPort(DI.RELIFT_UP) && GetDIOPort(DI.RELIFT_PALLET_END))
                    {
                        SetDIOPort(DO.RELIFT_PALLET_UP, true);
                        SetDIOPort(DO.RELIFT_PALLET_DW, false);
                    }

                    if (GetDIOPort(DI.RELIFT_UP) && !GetDIOPort(DI.RELIFT_PALLET_END))
                    {
                        SetDIOPort(DO.RELIFT_PALLET_UP, false);
                        SetDIOPort(DO.RELIFT_PALLET_DW, true);
                    }
                    nProcessStep[nStepIndex] = 10;
                    break;


                case 10:
                    // 작업 완료후 정지면
                    if (_SysInfo.bAutoCycleStop)
                    {
                        nProcessStep[nStepIndex] = 9000;
                        break;
                    }
                    // 돌려야할 상황 아니면 LIFT 끔
                    SetDIOPort(DO.RELIFT_CV_ON, false);
                    SetDIOPort(DO.RELIFT_CV_FAST, false);
                    SetDIOPort(DO.RELIFT_CV_SLOW, false);
                    // 파레트가 있고,  리프트가 업상태이면 스위치 입력 대기
                    if (GetDIOPort(DI.RELIFT_PALLET_END) && GetDIOPort(DI.RELIFT_UP))
                    {
                        nProcessStep[nStepIndex] = 100;
                    }
                    // 파레트가 없고, 리프트가 상승 상태이면 전단 장비에 파레트 Call
                    else if (!GetDIOPort(DI.RELIFT_PALLET_END) && GetDIOPort(DI.RELIFT_UP) && !GetDIOPortStat(DO.RELIFT_CV_ON) && _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING])
                    {
                        nProcessStep[nStepIndex] = 200;
                    }
                    // 파레트가 있고, 리프트가 다운 상태이면 배출 작업 진행 [ 공압관련 문제시 문제될수있어서 일단 HOLD ]
                    else if (GetDIOPort(DI.RELIFT_PALLET_END) && GetDIOPort(DI.RELIFT_DW))
                    {
                        //nProcessStep[nStepIndex] = 300;
                    }
                    // 파레트가 없고, 리프트가 하강 상태이면 상승
                    else if (!GetDIOPort(DI.RELIFT_PALLET_END) && GetDIOPort(DI.RELIFT_DW) /*&& !GetDIOPort(DI.OUTLIFT_SAFE)*/)
                    {
                        nProcessStep[nStepIndex] = 400;
                    }
                    break;


                // =========================================
                // 리프트가 상승 상태
                // 스위치 입력을 기다림
                case 100:
                    tMainTimer[nStepIndex].Start(1000);
                    nProcessStep[nStepIndex]++;
                    break;

                case 101:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 10;
                        break;
                    }

                    // 패스 스위치가 들어온다면
                    if (GetDIOPort(DI.RELIFT_FINISH_SW))
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 102:
                    tMainTimer[nStepIndex].Start(_Config.nChatteringTime);  // 채터링 방지 시간
                    nProcessStep[nStepIndex]++;
                    break;

                case 103:
                    if (GetDIOPort(DI.RELIFT_FINISH_SW) && tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 105;
                    }
                    else if (!GetDIOPort(DI.RELIFT_FINISH_SW))
                    {
                        nProcessStep[nStepIndex] = 10;
                    }
                    break;

                case 105:

                    //if (_Config.bUseNutrunnerMove)
                    //{
                    if (!_SysInfo.bTiteOk[5])
                    {
                        AppendLogMsg("리턴리프트 - 미체결된 팁이 있습니다.", LOG_TYPE.ERROR);
                        _SysInfo.nTL_Beep = 3;
                        nProcessStep[nStepIndex]++;
                        break;
                    }
                    //}

                    if (_Config.bUseMainCVMonitor)
                    {
                        if (GetDIOPort(DI.INVERTER1_RUN))
                        {
                            nProcessStep[nStepIndex] = 110;
                        }
                        else
                        {
                            AppendLogMsg("리턴리프트 - 메인컨베어가 동작중이 아닙니다.", LOG_TYPE.ERROR);
                            _SysInfo.nTL_Beep = 3;
                            nProcessStep[nStepIndex]++;
                            break;
                        }
                    }
                    else
                    {
                        nProcessStep[nStepIndex] = 110;
                    }

                    break;

                case 106:
                    if (!GetDIOPort(DI.RELIFT_FINISH_SW))
                    {
                        nProcessStep[nStepIndex] = 10;
                    }
                    break;


                case 110:
                    //if (_Config.bUseNutrunnerMove)
                    //{


                    //SetDIOPort(DO.ST1_COUNTER_RESET, true);
                    tMainTimer[nStepIndex].Start(200);
                    nProcessStep[nStepIndex]++;
                    //}
                    //else
                    //{
                    //    nProcessStep[nStepIndex] = 115;
                    //}
                    break;

                case 111:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    //SetDIOPort(DO.ST1_COUNTER_RESET, false);
                    nProcessStep[nStepIndex] = 115;
                    break;


                // 스위치 입력이 들어왔다면 리프트 하강 시키고 파레트 배출함
                case 115:
                    if (GetDIOPort(DI.UNDER_CV_PALLET_FULL))
                    {
                        AppendLogMsg("리턴리프트 - 하층 컨베어 파레트가 가득 찼습니다.", LOG_TYPE.ERROR);
                        _SysInfo.nTL_Beep = 3;
                        nProcessStep[nStepIndex] = 10;
                        break;
                    }

                    if ((GetDIOPort(DI.RELIFT_CAN_CABLE_CHECK) || !GetDIOPort(DI.RELIFT_CAN_CABLE_ALIGN)) && _Config.bUseReLiftCableSensing)
                    {
                        AppendLogMsg("리턴리프트 - 커넥트가 정위치가 아닙니다.", LOG_TYPE.ERROR);
                        _SysInfo.nTL_Beep = 3;
                        nProcessStep[nStepIndex] = 10;
                        break;
                    }

                    SetDIOPort(DO.RELIFT_DW, true);
                    SetDIOPort(DO.RELIFT_UP, false);
                    SetDIOPort(DO.RELIFT_PALLET_DW, true);
                    SetDIOPort(DO.RELIFT_PALLET_UP, false);
                    tMainTimer[nStepIndex].Start(_Config.nLiftTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 116:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        if (!GetDIOPort(DI.RELIFT_DW)) { AppendTimeOutMsg(DI.RELIFT_DW); }
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }

                    if (GetDIOPort(DI.RELIFT_DW))
                    {
                        tMainTimer[nStepIndex].Start(_Config.nLiftCylStabilTime);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                // 실린더 안정화
                case 117:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    nProcessStep[nStepIndex] = 120;
                    break;

                // 파레트 배출 
                case 120:
                    tMainTimer[nStepIndex].Start(200);  // 릴레이 전환 안정화 시간
                    nProcessStep[nStepIndex]++;
                    break;

                case 121:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    tCVTimer.Start(_Config.nCVAutoStopTime);
                    SetDIOPort(DO.RELIFT_CV_REV, true);
                    SetDIOPort(DO.RELIFT_CV_ON, false);
                    SetDIOPort(DO.RELIFT_CV_FAST, true);
                    SetDIOPort(DO.RELIFT_CV_SLOW, false);
                    tMainTimer[nStepIndex].Start(20000);
                    nProcessStep[nStepIndex]++;
                    break;

                case 122:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("RELIFT 제품 이송 실패", LOG_TYPE.ERROR);
                        SetDIOPort(DO.RELIFT_CV_REV, false);
                        SetDIOPort(DO.RELIFT_CV_ON, false);
                        SetDIOPort(DO.RELIFT_CV_FAST, false);
                        SetDIOPort(DO.RELIFT_CV_SLOW, false);
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }

                    if (GetDIOPort(DI.UNDER_CV_PALLET_FULL))
                    {
                        tMainTimer[nStepIndex].Start(_Config.nReturnPalletOutTime);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 123:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    tMainTimer[nStepIndex].Start(20000);
                    nProcessStep[nStepIndex]++;
                    break;


                case 124:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("RELIFT 제품 이송 실패", LOG_TYPE.ERROR);
                        SetDIOPort(DO.RELIFT_CV_REV, false);
                        SetDIOPort(DO.RELIFT_CV_ON, false);
                        SetDIOPort(DO.RELIFT_CV_FAST, false);
                        SetDIOPort(DO.RELIFT_CV_SLOW, false);
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }
                    if (GetDIOPort(DI.BETWEEN_RELIFT_CV)) { break; }

                    _tSTCycleTimer[(int)STATION_LIST.UNLOADING].Stop();
                    _tSTCycleEndTime[(int)STATION_LIST.UNLOADING] = DateTime.Now;
                    SaveStationTactTime(STATION_LIST.UNLOADING, _tSTCycleStartTime[(int)STATION_LIST.UNLOADING], _tSTCycleEndTime[(int)STATION_LIST.UNLOADING], 0);

                    // 카운터 초기화
                    for (int i = 0; i < 5; i++)
                    {
                        _SysInfo.nTipNowCount[5, i] = 0;

                    }
                    //if (GetDioPort(DI.UNDERCV_START_PALLET)) { break; }
                    SetDIOPort(DO.RELIFT_CV_REV, false);
                    SetDIOPort(DO.RELIFT_CV_ON, false);
                    SetDIOPort(DO.RELIFT_CV_FAST, false);
                    SetDIOPort(DO.RELIFT_CV_SLOW, false);
                    nProcessStep[nStepIndex] = 10;
                    break;



                // =========================================
                // 리프트가 상승 상태
                // 파레트가 없으므로 전단장비에 파레트 요청함
                case 200:
                    tMainTimer[nStepIndex].Start(1000);
                    _SysInfo.bPrePalletCall[(int)STATION_LIST.UNLOADING] = true;
                    nProcessStep[nStepIndex]++;
                    break;

                case 201:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        _SysInfo.bPrePalletCall[(int)STATION_LIST.UNLOADING] = false;
                        nProcessStep[nStepIndex] = 10;
                    }

                    // Station 6번에서 배출한다는 플래그가 Set된다면
                    if (_SysInfo.bNextPalletOut[(int)STATION_LIST.ST7])
                    {
                        // 해당 플래그, Call 플래그 초기화 컨베어 동작 시작
                        _SysInfo.bPrePalletCall[(int)STATION_LIST.UNLOADING] = false;
                        _SysInfo.bNextPalletOut[(int)STATION_LIST.ST7] = false;

                        nProcessStep[nStepIndex] = 210;
                    }
                    break;


                case 210:
                    tMainTimer[nStepIndex].Start(200);  // 릴레이 안정화 시간
                    nProcessStep[nStepIndex]++;
                    break;

                case 211:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    SetDIOPort(DO.RELIFT_CV_SLOW, false);
                    SetDIOPort(DO.RELIFT_CV_FAST, true);
                    SetDIOPort(DO.RELIFT_CV_ON, true);
                    SetDIOPort(DO.RELIFT_CV_REV, false);
                    tMainTimer[nStepIndex].Start(30000);
                    nProcessStep[nStepIndex]++;
                    break;

                case 212:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("EOL검사존 -> 리턴리프트 로 파레트 이동이 정상적으로 이뤄지지 않았습니다!!", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }

                    // 작업 완료후 정지면
                    if (_SysInfo.bAutoCycleStop)
                    {
                        nProcessStep[nStepIndex] = 9000;
                        SetDIOPort(DO.RELIFT_CV_FAST, false);
                        SetDIOPort(DO.RELIFT_CV_SLOW, false);
                        SetDIOPort(DO.RELIFT_CV_ON, false);
                        SetDIOPort(DO.RELIFT_CV_REV, false);
                        break;
                    }

                    if (GetDIOPort(DI.RELIFT_PALLET_SLOWPOINT) || GetDIOPort(DI.RELIFT_PALLET_END))
                    {
                        SetDIOPort(DO.RELIFT_CV_SLOW, true);
                        SetDIOPort(DO.RELIFT_CV_FAST, false);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 213:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("EOL검사존 -> 리턴리프트 로 파레트 이동이 정상적으로 이뤄지지 않았습니다!!", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }

                    // 작업 완료후 정지면
                    if (_SysInfo.bAutoCycleStop)
                    {
                        nProcessStep[nStepIndex] = 9000;
                        SetDIOPort(DO.RELIFT_CV_FAST, false);
                        SetDIOPort(DO.RELIFT_CV_SLOW, false);
                        SetDIOPort(DO.RELIFT_CV_ON, false);
                        SetDIOPort(DO.RELIFT_CV_REV, false);
                        break;
                    }

                    if (GetDIOPort(DI.RELIFT_PALLET_END) && !GetDIOPort(DI.BETWEEN_RELIFT_CV))
                    {
                        tMainTimer[nStepIndex].Start(_Config.nLiftInTime);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 214:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    SetDIOPort(DO.RELIFT_CV_FAST, false);
                    SetDIOPort(DO.RELIFT_CV_SLOW, false);
                    SetDIOPort(DO.RELIFT_CV_ON, false);
                    SetDIOPort(DO.RELIFT_CV_REV, false);
                    SetDIOPort(DO.RELIFT_PALLET_DW, false);
                    SetDIOPort(DO.RELIFT_PALLET_UP, true);
                    tMainTimer[nStepIndex].Start(3000);
                    _tSTCycleTimer[(int)STATION_LIST.UNLOADING].Restart();
                    _tSTCycleStartTime[(int)STATION_LIST.UNLOADING] = DateTime.Now;
                    nProcessStep[nStepIndex]++;
                    break;

                case 215:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    nProcessStep[nStepIndex] = 10;
                    break;



                // =========================================
                // 리프트가 하강 상태
                // 파레트가 없으므로 리프트 상승 시킴
                case 400:
                    if (_Config.bUseOutLiftSafty)
                    {

                        if (GetDIOPort(DI.RELIFT_SAFTY))
                        {
                            nProcessStep[nStepIndex] = 0;
                            break;
                        }
                    }

                    SetDIOPort(DO.RELIFT_UP, true);
                    SetDIOPort(DO.RELIFT_DW, false);
                    tMainTimer[nStepIndex].Start(_Config.nLiftTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 401:
                    if (_Config.bUseOutLiftSafty)
                    {
                        if (GetDIOPort(DI.RELIFT_SAFTY))
                        {
                            SetDIOPort(DO.RELIFT_UP, false);
                            SetDIOPort(DO.RELIFT_DW, true);
                            nProcessStep[nStepIndex] = 400;
                            break;
                        }
                    }

                    if (tMainTimer[nStepIndex].Verify())
                    {
                        if (!GetDIOPort(DI.RELIFT_UP)) { AppendTimeOutMsg(DI.RELIFT_UP); }
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }

                    if (GetDIOPort(DI.RELIFT_UP))
                    {
                        tMainTimer[nStepIndex].Start(_Config.nLiftCylStabilTime);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 402:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    nProcessStep[nStepIndex] = 10;
                    break;

                case 9000:
                    _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING] = false;
                    break;

                case 10000:
                    nProcessStep[nStepIndex] = 9000;
                    SetDIOPort(DO.RELIFT_CV_ON, false);
                    _SysInfo.TL_Buzzer = TOWER_LAMP.TL_ON;
                    break;

            }
        }
        //===========================================================


        public static void SetCmeraSch(int nStation, int nIndex)
        {
            #region 스테이션별 IO 할당
            DO _out_Camera_1 = new DO();

            switch (nStation)
            {
                case 0:
                    _out_Camera_1 = DO.CAMERA1_OUT0;
                    break;

                case 1:
                    _out_Camera_1 = DO.CAMERA2_OUT0;
                    break;

            }
            #endregion

            for (int i = 0; i < 5; i++)
            {
                SetDIOPort(_out_Camera_1 + i, (nIndex & (1 << (i))) != 0 ? true : false);
            }

        }

        //====== STATION 7 ==========================================
        static void WorkEolProcess()
        {
            int nStepIndex = (int)PROC_LIST.ST7;

            if (!GetDIOPort(DI.EOL_PALLET) && GetDIOPort(DI.EOL_PALLET_DW))
            {
                // 파레트가 없고 파레트 하강 상태라면
                SetDIOPort(DO.EOL_CAN_CONTACT_ON, false);       // 해당 실린더 강제로 후진시킴
            }


            if (!_SysInfo.bStationAutoMode[(int)STATION_LIST.ST7])
            {
                _SysInfo.ST_Red[1] = TOWER_LAMP.TL_OFF;
                _SysInfo.ST_Green[1] = TOWER_LAMP.TL_OFF;
                _SysInfo.ST_Yellow[1] = TOWER_LAMP.TL_OFF;
                _SysInfo.ST_Buzzer[1] = TOWER_LAMP.TL_OFF;

                _SysInfo.ST_TL_RED[1] = TOWER_LAMP.TL_OFF;
                _SysInfo.ST_TL_YELLOW[1] = TOWER_LAMP.TL_OFF;
                _SysInfo.ST_TL_GREEN[1] = TOWER_LAMP.TL_OFF;
                nProcessStep[nStepIndex] = 0;


                if (_tSTCycleTimer[(int)STATION_LIST.ST7].IsRunning)
                {
                    _tSTCycleTimer[(int)STATION_LIST.ST7].Stop();
                    _tSTCycleEndTime[(int)STATION_LIST.ST7] = DateTime.Now;
                    SaveStationTactTime(STATION_LIST.ST7, _tSTCycleStartTime[(int)STATION_LIST.ST7], _tSTCycleEndTime[(int)STATION_LIST.ST7], 1);
                }

                return;

            } // 수동모드


            SUB_CONTACT_SW(1);

            if (nProcessStep[nStepIndex] > 410 && nProcessStep[nStepIndex] < 480)
            {
                if (!GetDIOPort(DI.MAIN_DOOR3) && _Config.bUseEolDoor)
                {
                    _SysInfo.bContactTestOk[1] = false;
                    //_BatteryTester[1].bRequest = false;
                    //_BatteryTester[1].bStop = true;
                    _BatteryTester[1].WriteData("END");
                    //_BatteryTester[1].nCurrentStep = 0;
                    AppendLogMsg("EOL 검사도중 문열림 발생!!", LOG_TYPE.ERROR);
                    nProcessStep[nStepIndex] = 10000;

                }
            }



            switch (nProcessStep[nStepIndex])
            {
                case 0:

                    nProcessStep[nStepIndex]++;
                    break;

                case 1:
                    //if (!_SysInfo.bAlive)
                    //{
                    //    AppendLogMsg(String.Format("Station #EOL - {0}", OutputLogMsg(OutPutMessage.MASTER_PC_NG)), LOG_TYPE.ERROR);
                    //    nProcessStep[nStepIndex] = 9000;
                    //    break;
                    //}

                    if (GetDIOPort(DI.EOL_PALLET))
                    {
                        _SysInfo.eChargeStartInfo[6] = START_INFO.READY;
                        _mainform.BeginInvoke(new Action(() => _mainform.ViewTesterStartInfo(6)));
                        nProcessStep[nStepIndex]++;
                        break;
                    }
                    else
                    {

                        nProcessStep[nStepIndex] = 60;
                    }
                    break;

                case 2:
                    if (_SysInfo.eChargeStartInfo[6] == START_INFO.OK)
                    {
                        _SysInfo.bNeedEolMessageView = false;
                        nProcessStep[nStepIndex] = 60;
                    }
                    else if (_SysInfo.eChargeStartInfo[6] == START_INFO.CANCEL)
                    {
                        nProcessStep[nStepIndex] = 9000;
                    }
                    break;



                case 60:
                    MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbReadyPos1X, _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 61:
                    if (!MotionDone(AXIS.EOL_X)) { break; }
                    {
                        double dbNowPos1Z = 0;
                        CAXM.AxmStatusGetCmdPos((int)AXIS.EOL_Z, ref dbNowPos1Z);

                        double dbSpeed = 0;
                        dbSpeed = (Math.Abs(_ModelInfo._TestInfo[1].dbReadyPos1Z - dbNowPos1Z) > _Config.dbTestZoneContactZSlowMovePos) ? _Config.dbTestZoneContactZSlowMoveSpeed : _Config.dbTestZoneMoveSpeed;
                        MoveTo(AXIS.EOL_Z, _ModelInfo._TestInfo[1].dbReadyPos1Z, dbSpeed);
                    }


                    nProcessStep[nStepIndex]++;
                    break;

                case 62:
                    if (!MotionDone(AXIS.EOL_Z)) { break; }
                    MoveTo(AXIS.EOL_Y, _ModelInfo._TestInfo[1].dbReadyPos1Y, _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 63:
                    if (!MotionDone(AXIS.EOL_Y)) { break; }


                    nProcessStep[nStepIndex]++;
                    break;

                case 64:

                    nProcessStep[nStepIndex]++;
                    break;

                case 65:
                    _SysInfo.bContact_ing[1] = false;
                    nProcessStep[nStepIndex] = 100;
                    break;

                case 100:
                    // 작업 완료후 정지면
                    if (_SysInfo.bAutoCycleStop)
                    {
                        nProcessStep[nStepIndex] = 9000;
                        break;
                    }
                    // 일반적인 상황에선 스토퍼 상승
                    SetDIOPort(DO.EOL_STOPPER_DW, false);



                    // 리프트가 하강 상태라면
                    if (GetDIOPort(DI.EOL_PALLET_DW))
                    {
                        if (!GetDIOPort(DI.EOL_PALLET))
                        {
                            nProcessStep[nStepIndex] = 200;
                        }
                        else
                        {
                            if (_SysInfo.bNeedEolMessageView)
                            {
                                nProcessStep[nStepIndex] = 1;
                                break;
                            }
                            // ST 6일경우 불량 바이패스 

                            if (_Config.bUseST6NgByPass)
                            {
                                if (_SysInfo.bContactTestNg[1])
                                {
                                    tMainTimer[nStepIndex].Start(1000);
                                    nProcessStep[nStepIndex] = 110;
                                    break;
                                }
                            }

                            if (_ModelInfo.bEolSkip)
                            {
                                tMainTimer[nStepIndex].Start(1000);
                                nProcessStep[nStepIndex] = 110;
                                break;
                            }

                            // 충방전 불량 제품일 경우 바이패스
                            if (_ModelInfo.bUseScanSTTester && !_SysInfo.bScanSTTestOKNG[(int)STATION_LIST.ST6])
                            {
                                tMainTimer[nStepIndex].Start(1000);
                                nProcessStep[nStepIndex] = 110;
                                break;
                            }

                            nProcessStep[nStepIndex] = 250;
                        }
                    }
                    // 리프트가 상승 상태
                    else if (GetDIOPort(DI.EOL_PALLET_UP))
                    {
                        //파레트 감지가 안된다면
                        if (!GetDIOPort(DI.EOL_PALLET))
                        {
                            nProcessStep[nStepIndex] = 300;
                        }
                        // 그외 상황에선 컨텍 작업 수행함
                        else
                        {
                            // 컨택 작업 중이 아니면 컨텍만 작업 혹은 패스 가능
                            if (!_SysInfo.bContact_ing[1])
                            {
                                _SysInfo.eContactStatus[1] = CONTACT_STATUS.CONTACT_READY;
                                nProcessStep[nStepIndex] = 400;


                            }
                            // 컨텍 작업 중이면 컨텍 해제만 작업 가능
                            else
                            {
                                nProcessStep[nStepIndex] = 500;
                            }

                        }
                    }
                    break;



                case 110:
                    if (tMainTimer[nStepIndex].Verify()) { nProcessStep[nStepIndex] = 100; }

                    if (!GetDIOPort(DI.RELIFT_PALLET_END) && GetDIOPort(DI.RELIFT_UP) && !GetDIOPortStat(DO.RELIFT_CV_ON) && _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING])
                    {
                        SetDIOPort(DO.EOL_STOPPER_DW, true);
                        nProcessStep[nStepIndex] = 750;
                    }
                    break;


                // 리프트가 하강상태고 파레트가 감지가 안된다면
                // 전단 장비에 Pallet Call 함
                case 200:
                    tMainTimer[nStepIndex].Start(3000);
                    _SysInfo.bContactTestOk[1] = false;
                    _SysInfo.bAutoContactComplated[1] = false;
                    _SysInfo.bPrePalletCall[(int)STATION_LIST.ST7] = true;   // 파레트 Call 플래그를 듬
                    nProcessStep[nStepIndex]++;
                    break;

                case 201:
                    if (GetDIOPort(DI.EOL_PALLET))
                    {
                        _SysInfo.bNeedEolMessageView = true;
                        _SysInfo.bPrePalletCall[(int)STATION_LIST.ST7] = false;
                        nProcessStep[nStepIndex] = 100;
                    }

                    // 전단장비에서 배출한다는 시그널이 들어온다면
                    if (_SysInfo.bNextPalletOut[(int)STATION_LIST.ST7 - 1])
                    {
                        _SysInfo.bNextPalletOut[(int)STATION_LIST.ST7 - 1] = false;
                        _SysInfo.bPrePalletCall[(int)STATION_LIST.ST7] = false;
                        nProcessStep[nStepIndex] = 210;
                    }
                    break;

                // 파레트 들어올때까지 대기
                case 210:
                    if (_SysInfo.bAutoCycleStop) // 검사중 정지가 된다면
                    {
                        nProcessStep[nStepIndex] = 9000;
                        break;
                    }

                    if (GetDIOPort(DI.EOL_PALLET))
                    {
                        _tSTCycleTimer[(int)STATION_LIST.ST7].Restart();
                        _tSTCycleStartTime[(int)STATION_LIST.ST7] = DateTime.Now;
                        _SysInfo.bNeedEolMessageView = false;
                        nProcessStep[nStepIndex] = 100;
                    }
                    break;

                // =========================================
                // 리프트가 하강상태
                // 파레트 투입을 기다림
                case 250:
                    tMainTimer[nStepIndex].Start(1000);
                    nProcessStep[nStepIndex]++;
                    break;

                case 251:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 100;
                        break;
                    }

                    // 파레트가 들어온다면
                    if (GetDIOPort(DI.EOL_PALLET))
                    {
                        tMainTimer[nStepIndex].Start(1000); // 1초간 더 대기
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 252:
                    if (GetDIOPort(DI.EOL_PALLET) && tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex]++;     // 파레트가 1초간 감지된다면
                    }
                    else if (!GetDIOPort(DI.EOL_PALLET))
                    {
                        nProcessStep[nStepIndex] = 100;
                    }
                    break;

                case 253:
                    SetDIOPort(DO.EOL_CAN_CONTACT_ON, false);
                    SetDIOPort(DO.EOL_PRODUCT_PUSH_ON, false);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 254:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 10000;
                        if (!GetDIOPort(DI.EOL_PRODUCT_PUSH1_OFF)) AppendTimeOutMsg(DI.EOL_PRODUCT_PUSH1_OFF);
                        if (!GetDIOPort(DI.EOL_PRODUCT_PUSH2_OFF)) AppendTimeOutMsg(DI.EOL_PRODUCT_PUSH2_OFF);
                        if (!GetDIOPort(DI.EOL_CAN_OFF)) AppendTimeOutMsg(DI.EOL_CAN_OFF);
                    }

                    if (GetDIOPort(DI.EOL_PRODUCT_PUSH1_OFF) && GetDIOPort(DI.EOL_PRODUCT_PUSH1_OFF) && GetDIOPort(DI.EOL_CAN_OFF))
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 255:
                    // 리프트 상승
                    //if (!tMainTimer[nStepIndex].Verify()) { break; }

                    SetDIOPort(DO.EOL_PALLET_UP, true);
                    SetDIOPort(DO.EOL_PALLET_DW, false);
                    _SysInfo.bStationReservation[(int)STATION_LIST.ST6] = false;
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 256:
                    //if (!_SysInfo.bAlive)
                    //{
                    //    AppendLogMsg(String.Format("Station #EOL - {0}", OutputLogMsg(OutPutMessage.MASTER_PC_NG)), LOG_TYPE.ERROR);
                    //    nProcessStep[nStepIndex] = 10000;
                    //    break;
                    //}

                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 10000;
                        AppendTimeOutMsg(DI.EOL_PALLET_UP);      // 리프트 상승 타임아웃
                    }

                    if (GetDIOPort(DI.EOL_PALLET_UP))
                    {

                        nProcessStep[nStepIndex] = 100;
                    }
                    break;



                case 260:
                    SetDIOPort(DO.EOL_PRODUCT_PUSH_ON, true);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 261:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        if (GetDIOPort(DI.EOL_PRODUCT_PUSH1_ON)) { AppendTimeOutMsg(DI.EOL_PRODUCT_PUSH1_ON); }
                        if (GetDIOPort(DI.EOL_PRODUCT_PUSH2_ON)) { AppendTimeOutMsg(DI.EOL_PRODUCT_PUSH2_ON); }
                    }

                    if (GetDIOPort(DI.EOL_PRODUCT_PUSH1_ON) && GetDIOPort(DI.EOL_PRODUCT_PUSH2_ON))
                    {
                        tMainTimer[nStepIndex].Start(200);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 262:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    nProcessStep[nStepIndex] = 100;
                    break;
                //================================================



                // =========================================
                // 리프트가 상승상태
                // 파레트가 없다면 리프트를 하강 시킴

                case 300:
                    tMainTimer[nStepIndex].Start(1000); // 1초동안 파레트가 감지가 안된다면
                    nProcessStep[nStepIndex]++;
                    break;

                case 301:
                    if (!GetDIOPort(DI.EOL_PALLET) && tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    else if (GetDIOPort(DI.EOL_PALLET))
                    {
                        nProcessStep[nStepIndex] = 100;
                    }
                    break;

                case 302:
                    SetDIOPort(DO.EOL_CAN_CONTACT_ON, false);
                    SetDIOPort(DO.EOL_PRODUCT_PUSH_ON, false);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 303:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 10000;
                        if (!GetDIOPort(DI.EOL_PRODUCT_PUSH1_OFF)) AppendTimeOutMsg(DI.EOL_PRODUCT_PUSH1_OFF);
                        if (!GetDIOPort(DI.EOL_PRODUCT_PUSH2_OFF)) AppendTimeOutMsg(DI.EOL_PRODUCT_PUSH2_OFF);
                        if (!GetDIOPort(DI.EOL_CAN_OFF)) AppendTimeOutMsg(DI.EOL_CAN_OFF);
                    }

                    if (GetDIOPort(DI.EOL_PRODUCT_PUSH1_OFF) && GetDIOPort(DI.EOL_PRODUCT_PUSH2_OFF) && GetDIOPort(DI.EOL_CAN_OFF))
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 304:
                    SetDIOPort(DO.EOL_PALLET_DW, true);
                    SetDIOPort(DO.EOL_PALLET_UP, false);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 305:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 10000;
                        AppendTimeOutMsg(DI.EOL_PALLET_DW);      // 리프트 하강 타임아웃
                    }

                    if (GetDIOPort(DI.EOL_PALLET_DW))
                    {
                        nProcessStep[nStepIndex] = 100;
                    }
                    break;
                //================================================




                // =========================================
                // 리프트가 상승상태
                // 컨텍 작업중이 아니라면 컨텍 스위치 입력 대기
                case 400:
                    _SysInfo.ST_Yellow[1] = TOWER_LAMP.TL_BLINK;
                    _SysInfo.ST_Red[1] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_Green[1] = TOWER_LAMP.TL_OFF;
                    _EOLHandReader.bReadOk = false;
                    tMainTimer[nStepIndex].Start(1000);
                    nProcessStep[nStepIndex]++;
                    break;

                case 401:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 100;
                        break;
                    }

                    // 배출예약을 사용하고 검사 OK 경우
                    if (_Config.bUseStationReservation && !_SysInfo.bContact_ing[1])
                    {
                        // 예약상태이고
                        if (_SysInfo.bStationReservation[(int)STATION_LIST.ST6])
                        {

                            if (!GetDIOPort(DI.RELIFT_PALLET_END) && GetDIOPort(DI.RELIFT_UP) && GetDIOPort(DI.RELIFT_PALLET_DW) && _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING])
                            {
                                tCVTimer.Start(_Config.nCVAutoStopTime);
                                // 다음 스테이션이 준비 되었을때 배출함
                                if (!GetDIOPort(DI.RELIFT_PALLET_END) && GetDIOPort(DI.RELIFT_UP) && GetDIOPort(DI.RELIFT_PALLET_DW) && (GetDIOPort(DI.INVERTER1_RUN) || !_Config.bUseMainCVMonitor) && _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING])
                                {
                                    _SysInfo.bContactTestOk[1] = false;
                                    nProcessStep[nStepIndex] = 750;
                                }
                            }




                        }


                    }

                    if (_ModelInfo.bTestStationSkip[1])
                    {
                        if (!GetDIOPort(DI.RELIFT_PALLET_END) && GetDIOPort(DI.RELIFT_UP) && GetDIOPort(DI.RELIFT_PALLET_DW) && _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING])
                        {
                            tCVTimer.Start(_Config.nCVAutoStopTime);
                            // 다음 스테이션이 준비 되었을때 배출함

                            if (!GetDIOPort(DI.RELIFT_PALLET_END) && GetDIOPort(DI.RELIFT_UP) && GetDIOPort(DI.RELIFT_PALLET_DW) && (GetDIOPort(DI.INVERTER1_RUN) || !_Config.bUseMainCVMonitor) && _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING])
                            {
                                _SysInfo.bContactTestOk[1] = false;
                                nProcessStep[nStepIndex] = 750;
                            }
                            break;
                        }
                    }

                    // PASS 작업 스위치 신호가 들어온다면
                    if (GetDIOPort(DI.EOL_FINISH_SW))
                    {
                        nProcessStep[nStepIndex] = 700;
                    }

                    // 컨텍 작업 스위치 신호가 들어온다면
                    if (GetDIOPort(DI.EOL_READY_SW) || (_ModelInfo.bUseEolAutoContact && !_SysInfo.bAutoContactComplated[1]))
                    {
                        nProcessStep[nStepIndex]++;

                        if (_ModelInfo.bUseEolAutoContact && !_SysInfo.bAutoContactComplated[1])
                        {

                            if (!_SysInfo.bContactOneTime[1])
                            {
                                if (_Config.bUseNoProductPass && !GetDIOPort(DI.EOL_PRODUCT))
                                {
                                    nProcessStep[nStepIndex] = 405;
                                }
                                else
                                {
                                    _SysInfo.bAutoContactComplated[1] = true;
                                    nProcessStep[nStepIndex] = 2000;
                                }
                            }
                        }
                    }

                    if (_ModelInfo.bUseEolHandReader && _EOLHandReader.bReadOk)
                    {
                        _EOLHandReader.bReadOk = false;
                        if (CheckContactBCDInfo(_EOLHandReader.strReadBarcode, _ModelInfo.strLaserReadBmaSymbol))
                        {
                            _EOLReader.strReadBarcode = _EOLHandReader.strReadBarcode;

                            if (_ModelInfo.bUseBpuScan)
                            {
                                nProcessStep[nStepIndex] = 407;
                            }
                            else
                            {
                                nProcessStep[nStepIndex] = 3000;
                            }
                        }
                        else
                        {
                            AppendLogMsg("EOL1 - 바코드 정보가 일치하지 않습니다.", LOG_TYPE.ERROR);
                            _SysInfo.nTL_Beep = 3;
                            break;
                        }
                    }
                    break;




                case 402:
                    tMainTimer[nStepIndex].Start(_Config.nChatteringTime);  // 채터링 방지 시간
                    nProcessStep[nStepIndex]++;
                    break;




                case 403:
                    if (GetDIOPort(DI.EOL_READY_SW) && tMainTimer[nStepIndex].Verify())
                    {

                        nProcessStep[nStepIndex] = 2000;

                    }
                    else if (!GetDIOPort(DI.EOL_READY_SW))
                    {
                        nProcessStep[nStepIndex] = 100;
                    }
                    break;


                case 405:
                    if (!GetDIOPort(DI.RELIFT_PALLET_END) && GetDIOPort(DI.RELIFT_UP) && GetDIOPort(DI.RELIFT_PALLET_DW) && _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING])
                    {

                        tCVTimer.Start(_Config.nCVAutoStopTime);
                        if (!GetDIOPort(DI.RELIFT_PALLET_END) && GetDIOPort(DI.RELIFT_UP) && GetDIOPort(DI.RELIFT_PALLET_DW) && (GetDIOPort(DI.INVERTER1_RUN) || !_Config.bUseMainCVMonitor) && _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING])
                        {
                            nProcessStep[nStepIndex] = 750;
                        }
                    }
                    break;


                case 407:
                    if (_EOLHandReader.bReadOk)
                    {
                        _EOLHandReader.bReadOk = false;
                        _SysInfo.strBpuBCD = _EOLHandReader.strReadBarcode;
                        nProcessStep[nStepIndex] = 3000;
                    }
                    break;


                // 컨텍 작업 시작
                case 410:
                     if (_ModelInfo.bUseEOLSideContact)
                     {
                       SetDIOPort(DO.EOL_CAN_CONTACT_ON, true);
                     }

                    _SysInfo.bContactTestOk[1] = false;
                    _SysInfo.bContact_ing[1] = true;
                    _SysInfo.ST_Yellow[1] = TOWER_LAMP.TL_ON;
                    _SysInfo.ST_Red[1] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_Green[1] = TOWER_LAMP.TL_OFF;

                    _SysInfo.ST_TL_RED[1] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_TL_YELLOW[1] = TOWER_LAMP.TL_ON;
                    _SysInfo.ST_TL_GREEN[1] = TOWER_LAMP.TL_OFF;

                    //if (_ModelInfo.bUseOmronHipotTest)
                    //{
                    //    _BatteryTester[1]._Status = BatteryTesterStat.READY;
                    //    //_BatteryTester[1].bCheckOkng = true;
                    //    nProcessStep[nStepIndex] = 460;
                    //}
                    //else
                    //{
                        nProcessStep[nStepIndex] = 420;
                   // }
                    break;


                // 상승하강 실린더를 사용하는 경우
                case 420:
                    MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbReadyPos1X, _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 421:
                    if (!MotionDone(AXIS.EOL_X)) { break; }

                    MoveTo(AXIS.EOL_Y, _ModelInfo._TestInfo[1].dbContactPos1Y, _Config.dbTestZoneMoveSpeed);
                    {
                        double dbNowPos1Z = 0;
                        CAXM.AxmStatusGetCmdPos((int)AXIS.EOL_Z, ref dbNowPos1Z);

                        double dbSpeed = 0;
                        dbSpeed = (Math.Abs(_ModelInfo._TestInfo[1].dbContactPos1Z - dbNowPos1Z) > _Config.dbTestZoneContactZSlowMovePos) ? _Config.dbTestZoneContactZSlowMoveSpeed : _Config.dbTestZoneMoveSpeed;
                        MoveTo(AXIS.EOL_Z, _ModelInfo._TestInfo[1].dbContactPos1Z, dbSpeed);
                    }


                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 422:
                    if (!MotionDone(AXIS.EOL_Y) || !MotionDone(AXIS.EOL_Z)) { break; }

                    nProcessStep[nStepIndex]++;
                    break;

                // 모션 개별 움직임
                case 423:
                    //if (_ModelInfo._TestInfo[1].dbContactPos1X - _ModelInfo._TestInfo[1].dbReadyPos1X > _Config.dbTestZoneContactMovePos)
                    //{
                    //    MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbContactPos1X - _Config.dbTestZoneContactMovePos, _Config.dbTestZoneMoveSpeed);
                    //}
                    //if (_ModelInfo.bUseEolDistance && _ModelInfo.bUseEolBCDScanner)
                    //{
                    //    if ((_ModelInfo._TestInfo[1].dbContactPos1X + _SysInfo.dbEolDistanceGap) - _ModelInfo._TestInfo[1].dbReadyPos1X > _Config.dbTestZoneContactMovePos)
                    //    {
                    //        MoveTo(AXIS.EOL_X, (_ModelInfo._TestInfo[1].dbContactPos1X + _SysInfo.dbEolDistanceGap) - _Config.dbTestZoneContactMovePos, _Config.dbTestZoneMoveSpeed);
                    //    }
                    //}
                    //else
                    //{
                        if (_ModelInfo._TestInfo[1].dbContactPos1X - _ModelInfo._TestInfo[1].dbReadyPos1X > _Config.dbTestZoneContactMovePos)
                        {
                            MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbContactPos1X - _Config.dbTestZoneContactMovePos, _Config.dbTestZoneMoveSpeed);
                        }
                    //}

                    nProcessStep[nStepIndex]++;
                    break;

                case 424:
                    if (!MotionDone(AXIS.EOL_X)) { break; }

                    //MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbContactPos1X, _Config.dbTestZoneContactSpeed);
                    //if (_ModelInfo.bUseEolDistance && _ModelInfo.bUseEolBCDScanner)
                    //{
                    //    MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbContactPos1X + _SysInfo.dbEolDistanceGap, _Config.dbTestZoneContactSpeed);
                    //}
                    //else
                    //{
                        MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbContactPos1X, _Config.dbTestZoneContactSpeed);
                    //}
                    nProcessStep[nStepIndex]++;
                    break;


                case 425:
                    if (!MotionDone(AXIS.EOL_X)) { break; }

                    _Count.nStation6PinCount++;
                    SaveProductCount();
                    nProcessStep[nStepIndex] = 430;
                    break;


                case 430:
                    //if (_ModelInfo.bUseEolContactTest)
                    //{
                    //    nProcessStep[nStepIndex] = 4000;
                    //}
                    //else
                    //{
                        nProcessStep[nStepIndex] = 450;
                    //}
                    break;


                // 컨텍 완료 검사 작업 시작함
                case 450:
                    if (_Config.bUseContactAutoTestMode)
                    {
                        _BatteryTester[1]._Status = BatteryTesterStat.READY;
                        _mainform.Invoke(new Action(() => _mainform.UpdateEOLTestLog(_EOLReader.strReadBarcode, TEST_RESULT.READY)));
                        //_BatteryTester[1].strSendBcd = _EOLReader.strReadBarcode;
                        _BatteryTester[1].WriteData(String.Format("ST:{0},{0},{0}", _EOLReader.strReadBarcode));
                        //_BatteryTester[1].bRequest = false;
                        //_BatteryTester[1].bStart = true;
                        //_BatteryTester[1].nCurrentStep = 0;

                        _SysInfo.nEOLCommRetryCount = 0;    // EOL 리노핀 재컨텍 카운터 초기화
                        tMainTimer[nStepIndex].Start(10000);
                        nProcessStep[nStepIndex]++;
                    }
                    else
                    {
                        nProcessStep[nStepIndex] = 100;
                    }
                    break;



                case 451:
                    // 양불 판정 들어오길 기다림
                    if (_SysInfo.bAutoCycleStop) // 검사중 정지가 된다면
                    {
                        _SysInfo.bContactTestOk[1] = false;
                        //_BatteryTester[1].bRequest = false;
                        //_BatteryTester[1].bStop = true;
                        //_BatteryTester[1].nCurrentStep = 0;
                        nProcessStep[nStepIndex] = 9000;
                        break;
                    }

                    // 시작에대한 응답이 왔다면
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        _SysInfo.nEOLRetryCount++;
                        if (_SysInfo.nEOLRetryCount > 2)
                        {
                            _SysInfo.nEOLRetryCount = 0;
                            AppendLogMsg("EOL 검사기가 응답하지 않습니다...", LOG_TYPE.ERROR);
                            _SysInfo.nTL_Beep = 2;
                            nProcessStep[nStepIndex] = 1000;
                        }
                        else
                        {
                            nProcessStep[nStepIndex] = 450;
                        }

                    }

                    //if (_BatteryTester[1].bRequest)
                    //{
                    if (_BatteryTester[1]._Status == BatteryTesterStat.START)
                    {

                        // 정상적으로 시작했을시 양불 대기스텝으로 이동
                        _SysInfo.nEOLRetryCount = 0;
                        //_BatteryTester[1].bRequest = false;
                        //_BatteryTester[1].bCheckOkng = true;
                        //_BatteryTester[1].nCurrentStep = 0;
                        nProcessStep[nStepIndex] = 460;
                    }
                    else if (_BatteryTester[1]._Status == BatteryTesterStat.ING)
                    {
                        // 검사 중이라면 해당 작업 정지 시키고 재시작함
                        nProcessStep[nStepIndex]++;
                    }
                    //}
                    break;




                case 452:
                    //_BatteryTester[1].bRequest = false;
                    //_BatteryTester[1].bStop = true;
                    _BatteryTester[1].WriteData("END");
                    //_BatteryTester[1].nCurrentStep = 0;
                    nProcessStep[nStepIndex]++;
                    break;



                case 453:
                    if (_SysInfo.bAutoCycleStop)
                    {
                        //_BatteryTester[1].bRequest = false;
                        //_BatteryTester[1].bStop = true;
                        //_BatteryTester[1].nCurrentStep = 0;
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }

                    //if (_BatteryTester[1].bRequest)
                    //{
                    if (_BatteryTester[1]._Status == BatteryTesterStat.END)
                    {
                        // 정지 신호가 온다면 시작
                        nProcessStep[nStepIndex]++;
                    }
                    //}
                    break;


                case 454:
                    _BatteryTester[1]._Status = BatteryTesterStat.READY;
                    //_BatteryTester[1].strSendBcd = _SysInfo.strReadBCDData;
                    _BatteryTester[1].WriteData(String.Format("ST:{0},{0},{0}", _EOLReader.strReadBarcode));
                    //_BatteryTester[1].bRequest = false;
                    //_BatteryTester[1].bStart = true;
                    //_BatteryTester[1].nCurrentStep = 0;
                    tMainTimer[nStepIndex].Start(5000);
                    nProcessStep[nStepIndex]++;
                    break;


                case 455:
                    if (_SysInfo.bAutoCycleStop)
                    {
                        //_BatteryTester[1].bRequest = false;
                        //_BatteryTester[1].bStop = true;
                        //_BatteryTester[1].nCurrentStep = 0;
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }

                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("EOL 검사기가 응답하지 않습니다...", LOG_TYPE.ERROR);
                        _SysInfo.nTL_Beep = 2;
                        nProcessStep[nStepIndex] = 1000;
                    }

                    //if (_BatteryTester[1].bRequest)
                    //{
                    if (_BatteryTester[1]._Status == BatteryTesterStat.START)
                    {
                        // 정상적으로 시작했을시 양불 대기스텝으로 이동
                        //_BatteryTester[1].bRequest = false;
                        //_BatteryTester[1].bCheckOkng = true;
                        //_BatteryTester[1].nCurrentStep = 0;
                        nProcessStep[nStepIndex] = 460;
                    }
                    //}
                    break;

                case 460:
                    if (!_ModelInfo.bUseBpuScan) { nProcessStep[nStepIndex] = 465; break; }

                    _BatteryTester[1]._Status = BatteryTesterStat.READY;
                    //_BatteryTester[1].strSendBcd = _SysInfo.strReadBCDData;
                    _BatteryTester[1].WriteData(String.Format("ST:{0},{0},{0}", _SysInfo.strBpuBCD));
                    //_BatteryTester[1].bRequest = false;
                    //_BatteryTester[1].bStart = true;
                    //_BatteryTester[1].nCurrentStep = 0;
                    tMainTimer[nStepIndex].Start(5000);
                    nProcessStep[nStepIndex]++;
                    break;


                case 461:
                    if (_SysInfo.bAutoCycleStop)
                    {
                        //_BatteryTester[1].bRequest = false;
                        //_BatteryTester[1].bStop = true;
                        //_BatteryTester[1].nCurrentStep = 0;
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }

                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("EOL 검사기가 응답하지 않습니다...", LOG_TYPE.ERROR);
                        _SysInfo.nTL_Beep = 2;
                        nProcessStep[nStepIndex] = 1000;
                    }

                    //if (_BatteryTester[1].bRequest)
                    //{
                    if (_BatteryTester[1]._Status == BatteryTesterStat.START)
                    {
                        // 정상적으로 시작했을시 양불 대기스텝으로 이동
                        //_BatteryTester[1].bRequest = false;
                        //_BatteryTester[1].bCheckOkng = true;
                        //_BatteryTester[1].nCurrentStep = 0;
                        nProcessStep[nStepIndex] = 465;
                    }
                    //}
                    break;


                case 465:
                    // 양불 판정 들어오길 기다림       
                    if (_SysInfo.bAutoCycleStop) // 검사중 정지가 된다면
                    {
                        _SysInfo.bContactTestOk[1] = false;
                        //_BatteryTester[1].bRequest = false;
                        //_BatteryTester[1].bStop = true;
                        //_BatteryTester[1].nCurrentStep = 0;
                        //_BatteryTester[1]._Status = BatteryTesterStat.READY;
                        //_BatteryTester[1].WriteData(String.Format("ST:{0},{0},{0}", _SysInfo.strBpuBCD));
                        nProcessStep[nStepIndex] = 9000;
                        break;
                    }


                    if (_BatteryTester[1]._Status == BatteryTesterStat.NG)
                    {
                        _SysInfo.bContactTestOk[1] = false;

                        _SysInfo.bContactOneTime[1] = true;
                        _SysInfo.eContactStatus[1] = CONTACT_STATUS.CONTACT_NG;
                        _mainform.Invoke(new Action(() => _mainform.UpdateEOLTestLog(_EOLReader.strReadBarcode, TEST_RESULT.NG)));
                        _mainform.Invoke(new Action(() => _mainform.UpdateEOLResultData(_EOLReader.strReadBarcode, TEST_RESULT.NG)));
                        SaveEOLBcdDuplicate(_EOLReader.strReadBarcode);
                        nProcessStep[nStepIndex] = 1000;

                    }
                    else if (_BatteryTester[1]._Status == BatteryTesterStat.COMMNG)
                    {
                        if (_SysInfo.nEOLCommRetryCount > 2)
                        {
                            // 통신 NG가 2번이상 발생했을 경우 NG 처리
                            _SysInfo.bContactTestOk[1] = false;

                            _SysInfo.bContactOneTime[1] = true;
                            _SysInfo.eContactStatus[1] = CONTACT_STATUS.CONTACT_NG;
                            _mainform.Invoke(new Action(() => _mainform.UpdateEOLTestLog(_EOLReader.strReadBarcode, TEST_RESULT.NG)));
                            _mainform.Invoke(new Action(() => _mainform.UpdateEOLResultData(_EOLReader.strReadBarcode, TEST_RESULT.NG)));
                            SaveEOLBcdDuplicate(_EOLReader.strReadBarcode);
                            // 정지 메세지를 보냄
                            _BatteryTester[1].WriteData("STOP");

                            nProcessStep[nStepIndex] = 1000;
                        }
                        else
                        {
                            // 통신 NG 일 경우
                            _SysInfo.nEOLCommRetryCount++;
                            nProcessStep[nStepIndex] = 4000;

                        }

                    }
                    else if (_BatteryTester[1]._Status == BatteryTesterStat.OK)
                    {
                        _SysInfo.bContactTestOk[1] = true;

                        _SysInfo.bContactOneTime[1] = true;

                        _SysInfo.eContactStatus[1] = CONTACT_STATUS.CONTACT_OK;

                        _mainform.Invoke(new Action(() => _mainform.UpdateEOLTestLog(_EOLReader.strReadBarcode, TEST_RESULT.OK)));
                        _mainform.Invoke(new Action(() => _mainform.UpdateEOLResultData(_EOLReader.strReadBarcode, TEST_RESULT.OK)));
                        SaveEOLBcdDuplicate(_EOLReader.strReadBarcode);
                        _SysInfo.ST_TL_RED[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_YELLOW[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_GREEN[1] = TOWER_LAMP.TL_ON;

                        if (_ModelInfo.bUseEolAutoContact)
                        {
                            nProcessStep[nStepIndex] = 510; // 양품일경우 자동 해제   
                        }
                        else
                        {
                            nProcessStep[nStepIndex] = 100;
                        }
                    }
                    else if (_BatteryTester[1]._Status == BatteryTesterStat.BACKWARD)                // 후진 및 전진 명령 추가 19.11.13 피플,LG화학 요청
                    {
                        // 후진 명령이 들어왔다면
                        _BatteryTester[1]._Status = BatteryTesterStat.READY;
                        nProcessStep[nStepIndex] = 470;

                    }
                    else if (_BatteryTester[1]._Status == BatteryTesterStat.FOWARD)                  // 후진 및 전진 명령 추가 19.11.13 피플,LG화학 요청
                    {
                        // 전진 명령이 들어왔다면
                        _BatteryTester[1]._Status = BatteryTesterStat.READY;
                        nProcessStep[nStepIndex] = 480;
                    }
                    break;


                // BACKWARD 명령
                case 470:
                    if (!MotionDone(AXIS.EOL_X)) { break; }

                    MoveTo(AXIS.EOL_X, 0.0, _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 471:
                    if (!MotionDone(AXIS.EOL_X)) { break; }

                    nProcessStep[nStepIndex] = 460;
                    break;

                // FOWARD 명령
                // 모션 개별 움직임
                case 480:
                    if (!MotionDone(AXIS.EOL_X)) { break; }
                    //if (_ModelInfo._TestInfo[1].dbContactPos1X - _ModelInfo._TestInfo[1].dbReadyPos1X > _Config.dbTestZoneContactMovePos)
                    //{
                    //    MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbContactPos1X - _Config.dbTestZoneContactMovePos, _Config.dbTestZoneMoveSpeed);
                    //}
                    //if (_ModelInfo.bUseEolDistance && _ModelInfo.bUseEolBCDScanner)
                    //{
                    //    if ((_ModelInfo._TestInfo[1].dbContactPos1X + _SysInfo.dbEolDistanceGap) - _ModelInfo._TestInfo[1].dbReadyPos1X > _Config.dbTestZoneContactMovePos)
                    //    {
                    //        MoveTo(AXIS.EOL_X, (_ModelInfo._TestInfo[1].dbContactPos1X + _SysInfo.dbEolDistanceGap) - _Config.dbTestZoneContactMovePos, _Config.dbTestZoneMoveSpeed);
                    //    }
                    //}
                    //else
                    //{
                        if (_ModelInfo._TestInfo[1].dbContactPos1X - _ModelInfo._TestInfo[1].dbReadyPos1X > _Config.dbTestZoneContactMovePos)
                        {
                            MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbContactPos1X - _Config.dbTestZoneContactMovePos, _Config.dbTestZoneMoveSpeed);
                        }
                    //}
                    nProcessStep[nStepIndex]++;
                    break;

                case 481:
                    if (!MotionDone(AXIS.EOL_X)) { break; }

                    //MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbContactPos1X, _Config.dbTestZoneContactSpeed);
                    //if (_ModelInfo.bUseEolDistance && _ModelInfo.bUseEolBCDScanner)
                    //{
                    //    MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbContactPos1X + _SysInfo.dbEolDistanceGap, _Config.dbTestZoneContactSpeed);
                    //}
                    //else
                    //{
                        MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbContactPos1X, _Config.dbTestZoneContactSpeed);
                    //}
                    nProcessStep[nStepIndex]++;
                    break;


                case 482:
                    if (!MotionDone(AXIS.EOL_X)) { break; }

                    nProcessStep[nStepIndex] = 460;
                    break;





                case 490:
                    if (_SysInfo.bAutoCycleStop) // 검사중 정지가 된다면
                    {
                        _SysInfo.bContactTestOk[1] = false;
                        //_BatteryTester[1].bRequest = false;
                        //_BatteryTester[1].bStop = true;
                        //_BatteryTester[1].nCurrentStep = 0;
                        nProcessStep[nStepIndex] = 9000;
                        break;
                    }

                    // 양불 판정 들어오길 기다림
                    //if (_BatteryTester[1].bRequest)
                    //{
                    //    nProcessStep[nStepIndex] = 450;
                    //}
                    break;



                // =========================================
                // 리프트가 상승상태
                // 컨텍 작업중이 라면 컨텍 해제 스위치 입력 대기
                case 500:
                    _SysInfo.ST_Yellow[1] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_Red[1] = TOWER_LAMP.TL_BLINK;
                    _SysInfo.ST_Green[1] = TOWER_LAMP.TL_OFF;
                    tMainTimer[nStepIndex].Start(1000);
                    nProcessStep[nStepIndex]++;
                    break;

                case 501:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 100;
                        break;
                    }

                    // 컨텍 해제 스위치 신호가 들어온다면
                    if (GetDIOPort(DI.EOL_STOP_SW))
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 502:
                    tMainTimer[nStepIndex].Start(_Config.nChatteringTime);  // 채터링 방지 시간
                    nProcessStep[nStepIndex]++;
                    break;

                case 503:
                    if (GetDIOPort(DI.EOL_STOP_SW) && tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 510;
                    }
                    else if (!GetDIOPort(DI.EOL_STOP_SW))
                    {
                        nProcessStep[nStepIndex] = 100;
                    }
                    break;

                //외함측정 해제
                //외함측정 검사(EOL 스테이션에 있음)
                case 505:
                    // 움직이기 전에 일단 Z축부터 대기위치로 이동한다
                    MoveTo(AXIS.CAMERA1_Z, _ModelInfo.dbCamera1ReadyPosZ, _Config.dbOmronCameraZMoveSpeed);
                    MoveTo(AXIS.CAMERA2_Z, _ModelInfo.dbCamera2ReadyPosZ, _Config.dbOmronCameraZMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 506:
                    if (!MotionDone(AXIS.CAMERA1_Z) || !MotionDone(AXIS.CAMERA2_Z)) { break; }

                    nProcessStep[nStepIndex]++;
                    break;

                // 검사위치로 이동
                case 507:
                    MoveTo(AXIS.CAMERA1_X, _ModelInfo.dbCamera1ReadyPosX, _Config.dbOmronCameraZMoveSpeed);
                    MoveTo(AXIS.CAMERA1_Y, _ModelInfo.dbCamera1ReadyPosY, _Config.dbOmronCameraZMoveSpeed);
                    MoveTo(AXIS.CAMERA2_X, _ModelInfo.dbCamera2ReadyPosX, _Config.dbOmronCameraZMoveSpeed);
                    MoveTo(AXIS.CAMERA2_Y, _ModelInfo.dbCamera2ReadyPosY, _Config.dbOmronCameraZMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 508:
                    if (!MotionDone(AXIS.CAMERA1_X) || !MotionDone(AXIS.CAMERA1_Y) || !MotionDone(AXIS.CAMERA2_X) || !MotionDone(AXIS.CAMERA2_Y)) { break; }

                    nProcessStep[nStepIndex] = 510;
                    break;

                // 컨텍 해제 시작
                case 510:
                    _SysInfo.ST_Yellow[1] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_Red[1] = TOWER_LAMP.TL_ON;
                    _SysInfo.ST_Green[1] = TOWER_LAMP.TL_OFF;
                    // 상승 하강 실린더를 사용하는 경우 ( 1번 실린더 )
                    nProcessStep[nStepIndex]++;

                    break;

                case 511:
                    SetDIOPort(DO.EOL_PRODUCT_PUSH_ON, false);
                    nProcessStep[nStepIndex]++;
                    break;

                case 512:
                    if (_ModelInfo.bUseEolFix)
                    {
                        tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                        nProcessStep[nStepIndex]++;
                    }
                    else
                    {
                        nProcessStep[nStepIndex] = 520;
                    }
                    break;

                case 513:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 10000;
                        if (!GetDIOPort(DI.EOL_PRODUCT_PUSH1_OFF)) { AppendTimeOutMsg(DI.EOL_PRODUCT_PUSH1_OFF); }
                        if (!GetDIOPort(DI.EOL_PRODUCT_PUSH2_OFF)) { AppendTimeOutMsg(DI.EOL_PRODUCT_PUSH2_OFF); }
                        break;
                    }

                    if (GetDIOPort(DI.EOL_PRODUCT_PUSH1_OFF) && GetDIOPort(DI.EOL_PRODUCT_PUSH2_OFF))
                    {
                        nProcessStep[nStepIndex] = 520;
                    }
                    break;



                // 상승하강 실린더를 사용하는 경우
                case 520:
                    SetDIOPort(DO.EOL_CAN_CONTACT_ON, false);
                    MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbReadyPos1X, _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;


                case 521:
                    if (!MotionDone(AXIS.EOL_X)) { break; }

                    MoveTo(AXIS.EOL_Y, _ModelInfo._TestInfo[1].dbReadyPos1Y, _Config.dbTestZoneMoveSpeed);
                    {
                        double dbNowPos1Z = 0;
                        CAXM.AxmStatusGetCmdPos((int)AXIS.EOL_Z, ref dbNowPos1Z);

                        double dbSpeed = 0;
                        dbSpeed = (Math.Abs(_ModelInfo._TestInfo[1].dbReadyPos1Z - dbNowPos1Z) > _Config.dbTestZoneContactZSlowMovePos) ? _Config.dbTestZoneContactZSlowMoveSpeed : _Config.dbTestZoneMoveSpeed;
                        MoveTo(AXIS.EOL_Z, _ModelInfo._TestInfo[1].dbReadyPos1Z, dbSpeed);
                    }

                    nProcessStep[nStepIndex]++;
                    break;

                case 522:
                    nProcessStep[nStepIndex]++;
                    break;

                case 523:
                    if (!MotionDone(AXIS.EOL_X) || !MotionDone(AXIS.EOL_Y)) { break; }

                    MoveTo(AXIS.EOL_Y, _ModelInfo._TestInfo[1].dbReadyPos1Y, _Config.dbTestZoneMoveSpeed);
                    {
                        double dbNowPos1Z = 0;
                        CAXM.AxmStatusGetCmdPos((int)AXIS.EOL_Z, ref dbNowPos1Z);

                        double dbSpeed = 0;
                        dbSpeed = (Math.Abs(_ModelInfo._TestInfo[1].dbReadyPos1Z - dbNowPos1Z) > _Config.dbTestZoneContactZSlowMovePos) ? _Config.dbTestZoneContactZSlowMoveSpeed : _Config.dbTestZoneMoveSpeed;
                        MoveTo(AXIS.EOL_Z, _ModelInfo._TestInfo[1].dbReadyPos1Z, dbSpeed);
                    }

                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 524:
                    if (!MotionDone(AXIS.EOL_X) || !MotionDone(AXIS.EOL_Y) || !MotionDone(AXIS.EOL_Z)) { break; }

                    nProcessStep[nStepIndex] = 570;
                    break;





                // 컨텍 해제 완료
                case 570:
                    if (_ModelInfo.bUseEolAutoContact && _SysInfo.bContactTestOk[1])
                    {
                        _SysInfo.bContact_ing[1] = false;
                        _SysInfo.eContactStatus[1] = CONTACT_STATUS.CONTACT_READY;

                        if (_SysInfo.bAutoCycleStop)
                        {
                            nProcessStep[nStepIndex] = 9000;
                            break;
                        }


                        if (!GetDIOPort(DI.RELIFT_PALLET_END) && GetDIOPort(DI.RELIFT_UP) && GetDIOPort(DI.RELIFT_PALLET_DW) && _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING])
                        {
                            tCVTimer.Start(_Config.nCVAutoStopTime);
                            if (!GetDIOPort(DI.RELIFT_PALLET_END) && GetDIOPort(DI.RELIFT_UP) && GetDIOPort(DI.RELIFT_PALLET_DW) && (GetDIOPort(DI.INVERTER1_RUN) || !_Config.bUseMainCVMonitor) && _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING])
                            {
                                nProcessStep[nStepIndex] = 750;
                            }
                        }



                    }
                    else
                    {
                        _SysInfo.bContact_ing[1] = false;
                        _SysInfo.eContactStatus[1] = CONTACT_STATUS.CONTACT_READY;
                        nProcessStep[nStepIndex] = 100;
                    }
                    break;





                // =========================================
                // 리프트가 상승상태
                // 배출 스위치가 눌렸다면
                case 700:
                    tMainTimer[nStepIndex].Start(_Config.nChatteringTime);  // 채터링 방지 시간
                    nProcessStep[nStepIndex]++;
                    break;



                case 701:
                    if (GetDIOPort(DI.EOL_FINISH_SW) && tMainTimer[nStepIndex].Verify())
                    {
                        if (_SysInfo.bStationReservation[(int)STATION_LIST.ST7])
                        {
                            _SysInfo.bStationReservation[(int)STATION_LIST.ST7] = false;
                            nProcessStep[nStepIndex] = 100;
                        }
                        else
                        {
                            nProcessStep[nStepIndex] = 710;
                        }
                    }
                    else if (!GetDIOPort(DI.EOL_FINISH_SW))
                    {
                        nProcessStep[nStepIndex] = 100;
                    }
                    break;

                // =========================================
                // 배출 조건에 맞아 배출할 경우
                case 710:

                    if (_ModelInfo.bUseLabelFoolproof)
                    {
                        // 비전 OK면 아무작업도 하지않음
                        if (GetDIOPort(DI.VISION_OK) && !GetDIOPort(DI.VISION_NG))
                        {

                        }
                        else if (!GetDIOPort(DI.VISION_OK) && GetDIOPort(DI.VISION_NG)) // 비전 NG인 경우
                        {
                            AppendLogMsg("EOL - 라벨검사 불량 제품입니다.", LOG_TYPE.ERROR);
                            _SysInfo.nCount_Beep[5] = 3;
                            nProcessStep[nStepIndex] = 711;
                            break;
                        }
                        else
                        {
                            AppendLogMsg("EOL - 라벨검사가 이뤄지지 않았습니다.", LOG_TYPE.ERROR);
                            _SysInfo.nCount_Beep[5] = 3;
                            nProcessStep[nStepIndex] = 711;
                            break;
                        }
                    }

                    if (!_SysInfo.bContact_ing[1] && (GetDIOPort(DI.INVERTER1_RUN) || !_Config.bUseMainCVMonitor) &&
                        //!GetDIOPort(DI.RELIFT_PALLET_END) && GetDIOPort(DI.RELIFT_UP) && !GetDIOPortStat(DO.RELIFT_CV_ON) && _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING] &&
                        (_SysInfo.bContactOneTime[1] || (_Config.bUseNoProductPass && !GetDIOPort(DI.EOL_PRODUCT))) &&
                        GetDIOPort(DI.EOL_CABLE1) && GetDIOPort(DI.EOL_CABLE2) && GetDIOPort(DI.EOL_CABLE3) && GetDIOPort(DI.EOL_CABLE4) && GetDIOPort(DI.EOL_CABLE5))
                    {

                        if (_Config.bUseHipotStationDwStay)
                        {
                            nProcessStep[nStepIndex] = 750;
                        }
                        else
                        {
                            if (!GetDIOPort(DI.RELIFT_PALLET_END) && GetDIOPort(DI.RELIFT_UP) && !GetDIOPortStat(DO.RELIFT_CV_ON) && _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING])
                            {
                                nProcessStep[nStepIndex] = 750;
                            }
                            else
                            {
                                AppendLogMsg(String.Format("EOL - 다음스테이션이 준비상태가 아닙니다.", 6), LOG_TYPE.ERROR);
                                _SysInfo.nCount_Beep[5] = 3;
                                nProcessStep[nStepIndex]++;
                            }
                        }
                        break;
                    }
                    //else if (!_SysInfo.bContact_ing[1] && (GetDIOPort(DI.MAIN_CV_ON) || !_Config.bUseMainCVMonitor) &&
                    //        !(!GetDIOPort(DI.RELIFT_PALLET) && GetDIOPort(DI.RELIFT_UP) && !GetDIOPortStat(DO.RELIFT_CV_ON) && _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING]) && _SysInfo.bContactOneTime[1])
                    //{
                    //    nProcessStep[nStepIndex] = 730;
                    //    break;
                    //}
                    else
                    {
                        // 충방전 불량 제품일 경우 바이패스
                        if (_ModelInfo.bUseScanSTTester && !_SysInfo.bScanSTTestOKNG[(int)STATION_LIST.ST7])
                        {
                            if (!GetDIOPort(DI.RELIFT_PALLET_END) && GetDIOPort(DI.RELIFT_UP) && !GetDIOPortStat(DO.RELIFT_CV_ON) && _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING])
                            {
                                nProcessStep[nStepIndex] = 750;
                            }
                            else
                            {
                                nProcessStep[nStepIndex] = 730;
                            }
                            break;
                        }

                        if (_SysInfo.bContact_ing[1]) { AppendLogMsg(String.Format("EOL - 컨택 상태입니다.", 6), LOG_TYPE.ERROR); }
                        if (_Config.bUseMainCVMonitor) { if (!GetDIOPort(DI.INVERTER1_RUN)) { AppendLogMsg(String.Format("EOL - 메인컨베어가 동작중이 아닙니다.", 6), LOG_TYPE.ERROR); } }
                        if (!(!GetDIOPort(DI.RELIFT_PALLET_END) && GetDIOPort(DI.RELIFT_UP) && !GetDIOPortStat(DO.RELIFT_CV_ON) && _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING]))
                        {
                            AppendLogMsg(String.Format("EOL - 다음스테이션이 준비상태가 아닙니다.", 6), LOG_TYPE.ERROR);

                        }


                        if (!_SysInfo.bContactOneTime[1])
                        {
                            AppendLogMsg(String.Format("EOL - 제품 검사가 이뤄지지 않았습니다.", 6), LOG_TYPE.ERROR);
                        }

                        if (!GetDIOPort(DI.EOL_CABLE1)) { AppendLogMsg("EOL - 수동컨텍지그 #1 이 정위치가 아닙니다", LOG_TYPE.ERROR); }
                        if (!GetDIOPort(DI.EOL_CABLE2)) { AppendLogMsg("EOL - 수동컨텍지그 #2 이 정위치가 아닙니다", LOG_TYPE.ERROR); }
                        if (!GetDIOPort(DI.EOL_CABLE3)) { AppendLogMsg("EOL - 수동컨텍지그 #3 이 정위치가 아닙니다", LOG_TYPE.ERROR); }
                        if (!GetDIOPort(DI.EOL_CABLE4)) { AppendLogMsg("EOL - 수동컨텍지그 #4 이 정위치가 아닙니다", LOG_TYPE.ERROR); }
                        if (!GetDIOPort(DI.EOL_CABLE5)) { AppendLogMsg("EOL - 수동컨텍지그 #5 이 정위치가 아닙니다", LOG_TYPE.ERROR); }
                        _SysInfo.nCount_Beep[5] = 3;
                        nProcessStep[nStepIndex]++;

                    }
                    break;

                case 711:
                    if (!GetDIOPort(DI.EOL_FINISH_SW))
                    {
                        nProcessStep[nStepIndex] = 100;
                    }
                    break;


                case 730:
                    if (GetDIOPort(DI.EOL_FINISH_SW)) { break; }



                    //_SysInfo.bStationReservation[(int)STATION_LIST.ST7] = true;

                    nProcessStep[nStepIndex] = 100;
                    break;



                case 750:
                    SetDIOPort(DO.EOL_PRODUCT_PUSH_ON, false);
                    SetDIOPort(DO.EOL_CAN_CONTACT_ON, false);
                    SetDIOPort(DO.VISION_CLEAR, true);
                    nProcessStep[nStepIndex]++;
                    break;

                case 751:
                    if (_ModelInfo.bUseEolFix)
                    {
                        tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                        nProcessStep[nStepIndex] = 752;
                    }
                    else
                    {
                        nProcessStep[nStepIndex] = 760;
                    }
                    break;

                case 752:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 10000;
                        if (!GetDIOPort(DI.EOL_PRODUCT_PUSH1_OFF)) { AppendTimeOutMsg(DI.EOL_PRODUCT_PUSH1_OFF); }
                        if (!GetDIOPort(DI.EOL_PRODUCT_PUSH2_OFF)) { AppendTimeOutMsg(DI.EOL_PRODUCT_PUSH2_OFF); }
                        break;
                    }

                    if (GetDIOPort(DI.EOL_PRODUCT_PUSH1_OFF) && GetDIOPort(DI.EOL_PRODUCT_PUSH2_OFF))
                    {
                        nProcessStep[nStepIndex] = 760;
                    }
                    break;


                case 760:
                    if (_Config.bUseHipotStationDwStay)
                    {
                        SetDIOPort(DO.EOL_PALLET_DW, true);
                        SetDIOPort(DO.EOL_PALLET_UP, false);

                        if (!GetDIOPort(DI.RELIFT_PALLET_END) && GetDIOPort(DI.RELIFT_UP) && GetDIOPort(DI.RELIFT_PALLET_DW) && !GetDIOPortStat(DO.RELIFT_CV_ON) && _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING])
                        {
                            nProcessStep[nStepIndex] = 770;
                        }
                    }
                    else
                    {
                        nProcessStep[nStepIndex] = 770;
                    }
                    break;

                case 770:
                    tCVTimer.Start(_Config.nCVAutoStopTime);
                    _tSTCycleTimer[(int)STATION_LIST.ST7].Stop();
                    _tSTCycleEndTime[(int)STATION_LIST.ST7] = DateTime.Now;
                    SaveStationTactTime(STATION_LIST.ST7, _tSTCycleStartTime[(int)STATION_LIST.ST7], _tSTCycleEndTime[(int)STATION_LIST.ST7], 0);
                    SetDIOPort(DO.EOL_PALLET_DW, true);
                    SetDIOPort(DO.EOL_PALLET_UP, false);
                    if (_Config.bUseStopper || _Config.bUseHipotStationDwStay) { SetDIOPort(DO.EOL_STOPPER_DW, true); }
                    _SysInfo.bAutoContactComplated[1] = false;
                    _SysInfo.bContactOneTime[1] = false;


                    _SysInfo.bNextPalletOut[(int)STATION_LIST.ST7] = true;   // 배출한다고 알림
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 771:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 10000;
                        AppendTimeOutMsg(DI.EOL_PALLET_DW);      // 리프트 하강 타임아웃
                        break;
                    }

                    if (GetDIOPort(DI.EOL_PALLET_DW))
                    {
                        SetDIOPort(DO.VISION_CLEAR, false);
                        tMainTimer[nStepIndex].Start(2000); // 스토퍼 동작 시간
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 772:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    SetDIOPort(DO.EOL_STOPPER_DW, false);
                    tMainTimer[nStepIndex].Start(20000);    // 제품 배출 타임아웃
                    nProcessStep[nStepIndex]++;
                    break;

                case 773:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg(String.Format("Station #{0} - 제품 배출 타임아웃.", 6), LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 10000;
                    }


                    if (!GetDIOPort(DI.EOL_PALLET))
                    {
                        _SysInfo.ST_Yellow[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Red[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Green[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Buzzer[1] = TOWER_LAMP.TL_OFF;

                        _SysInfo.ST_TL_RED[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_YELLOW[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_GREEN[1] = TOWER_LAMP.TL_OFF;

                        _SysInfo.bScanSTTestOKNG[(int)STATION_LIST.ST7 + 1] = _SysInfo.bScanSTTestOKNG[(int)STATION_LIST.ST7];
                        nProcessStep[nStepIndex] = 100;
                    }
                    break;



                // 검사기와 인터페이스 오류시
                case 1000:
                    _SysInfo.ST_Yellow[1] = TOWER_LAMP.TL_BLINK;
                    _SysInfo.ST_Red[1] = TOWER_LAMP.TL_BLINK;
                    _SysInfo.ST_Green[1] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_Buzzer[1] = TOWER_LAMP.TL_BLINK;

                    _SysInfo.ST_TL_RED[1] = TOWER_LAMP.TL_ON;
                    _SysInfo.ST_TL_YELLOW[1] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_TL_GREEN[1] = TOWER_LAMP.TL_OFF;
                    nProcessStep[nStepIndex]++;
                    break;

                //ㅇㅇㅇ
                //여기까지
                case 1001:
                    if (GetDIOPort(DI.EOL_READY_SW))
                    {
                        tMainTimer[nStepIndex].Start(_Config.nChatteringTime);
                        nProcessStep[nStepIndex] = 1100;
                    }

                    if (GetDIOPort(DI.EOL_STOP_SW))
                    {
                        _SysInfo.ST_Buzzer[1] = TOWER_LAMP.TL_OFF;
                        tMainTimer[nStepIndex].Start(_Config.nChatteringTime);
                        nProcessStep[nStepIndex] = 1200;
                    }
                    if (_SysInfo.bAutoCycleStop)
                    {
                        _SysInfo.ST_Red[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Green[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Yellow[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Buzzer[1] = TOWER_LAMP.TL_OFF;

                        _SysInfo.ST_TL_RED[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_YELLOW[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_GREEN[1] = TOWER_LAMP.TL_OFF;
                        nProcessStep[nStepIndex] = 9000;
                    }
                    break;

                // 컨텍 스위치가 들어올경우 재검사 시작
                case 1100:
                    if (GetDIOPort(DI.EOL_READY_SW) && tMainTimer[nStepIndex].Verify())
                    {
                        _SysInfo.ST_Red[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Green[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Yellow[1] = TOWER_LAMP.TL_ON;
                        _SysInfo.ST_Buzzer[1] = TOWER_LAMP.TL_OFF;

                        _SysInfo.ST_TL_RED[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_YELLOW[1] = TOWER_LAMP.TL_ON;
                        _SysInfo.ST_TL_GREEN[1] = TOWER_LAMP.TL_OFF;
                        nProcessStep[nStepIndex] = 2000;
                        break;
                    }
                    else if (!GetDIOPort(DI.EOL_READY_SW))
                    {
                        nProcessStep[nStepIndex] = 1001;
                    }
                    break;

                case 1200:
                    if (GetDIOPort(DI.EOL_STOP_SW) && tMainTimer[nStepIndex].Verify())
                    {
                        _SysInfo.ST_Red[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Green[1] = TOWER_LAMP.TL_ON;
                        _SysInfo.ST_Yellow[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Buzzer[1] = TOWER_LAMP.TL_OFF;

                        _SysInfo.ST_TL_RED[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_YELLOW[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_GREEN[1] = TOWER_LAMP.TL_OFF;

                        nProcessStep[nStepIndex] = 510;
                        break;
                    }
                    else if (!GetDIOPort(DI.EOL_STOP_SW))
                    {
                        nProcessStep[nStepIndex] = 1001;
                    }
                    break;

                // 외함측정에서 불량이 났을경우
                case 1300:
                    _SysInfo.ST_Yellow[1] = TOWER_LAMP.TL_BLINK;
                    _SysInfo.ST_Red[1] = TOWER_LAMP.TL_BLINK;
                    _SysInfo.ST_Green[1] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_Buzzer[1] = TOWER_LAMP.TL_BLINK;

                    _SysInfo.ST_TL_RED[1] = TOWER_LAMP.TL_ON;
                    _SysInfo.ST_TL_YELLOW[1] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_TL_GREEN[1] = TOWER_LAMP.TL_OFF;
                    nProcessStep[nStepIndex]++;
                    break;


                case 1301:
                    if (GetDIOPort(DI.EOL_READY_SW))
                    {
                        tMainTimer[nStepIndex].Start(_Config.nChatteringTime);
                        nProcessStep[nStepIndex] = 1310;
                    }

                    if (GetDIOPort(DI.EOL_STOP_SW))
                    {
                        tMainTimer[nStepIndex].Start(_Config.nChatteringTime);
                        nProcessStep[nStepIndex] = 1320;

                    }
                    if (_SysInfo.bAutoCycleStop)
                    {
                        _SysInfo.ST_Green[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Yellow[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Buzzer[1] = TOWER_LAMP.TL_OFF;

                        _SysInfo.ST_TL_RED[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_YELLOW[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_GREEN[1] = TOWER_LAMP.TL_OFF;
                        nProcessStep[nStepIndex] = 9000;
                    }
                    break;

                // 컨텍 스위치가 들어올경우 재검사 시작
                case 1310:
                    if (GetDIOPort(DI.EOL_READY_SW) && tMainTimer[nStepIndex].Verify())
                    {
                        _SysInfo.ST_Green[1] = TOWER_LAMP.TL_ON;
                        _SysInfo.ST_Yellow[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Buzzer[1] = TOWER_LAMP.TL_OFF;

                        _SysInfo.ST_TL_RED[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_YELLOW[1] = TOWER_LAMP.TL_ON;
                        _SysInfo.ST_TL_GREEN[1] = TOWER_LAMP.TL_OFF;
                        nProcessStep[nStepIndex] = 3000;
                        break;
                    }
                    else if (!GetDIOPort(DI.EOL_READY_SW))
                    {
                        nProcessStep[nStepIndex] = 1301;
                    }
                    break;

                case 1320:
                    if (GetDIOPort(DI.EOL_STOP_SW) && tMainTimer[nStepIndex].Verify())
                    {
                        _SysInfo.ST_Green[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_Yellow[1] = TOWER_LAMP.TL_ON;
                        _SysInfo.ST_Buzzer[1] = TOWER_LAMP.TL_OFF;

                        _SysInfo.ST_TL_RED[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_YELLOW[1] = TOWER_LAMP.TL_OFF;
                        _SysInfo.ST_TL_GREEN[1] = TOWER_LAMP.TL_OFF;


                        nProcessStep[nStepIndex] = 505;

                        break;
                    }
                    else if (!GetDIOPort(DI.EOL_STOP_SW))
                    {
                        nProcessStep[nStepIndex] = 1301;
                    }
                    break;




                // 바코드 스캔 작업 및 비전 작업
                case 2000:
                    if (_ModelInfo.bUseEolFix)
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    else
                    {
                        nProcessStep[nStepIndex] = 2050;
                    }
                    break;


                case 2001:
                    SetDIOPort(DO.EOL_PRODUCT_PUSH_ON, true);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2002:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        if (GetDIOPort(DI.EOL_PRODUCT_PUSH1_ON)) { AppendTimeOutMsg(DI.EOL_PRODUCT_PUSH1_ON); }
                        if (GetDIOPort(DI.EOL_PRODUCT_PUSH2_ON)) { AppendTimeOutMsg(DI.EOL_PRODUCT_PUSH2_ON); }
                        nProcessStep[nStepIndex] = 10000;
                        break;
                    }

                    if (GetDIOPort(DI.EOL_PRODUCT_PUSH1_ON) && GetDIOPort(DI.EOL_PRODUCT_PUSH2_ON))
                    {
                        tMainTimer[nStepIndex].Start(200);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 2003:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    nProcessStep[nStepIndex] = 2050;
                    break;


                case 2050:
                    if (_ModelInfo.bUseOmronHipotTest)
                    {
                        nProcessStep[nStepIndex] = 410;
                    }
                    else
                    {
                        if (_ModelInfo.bUseEolBCDScanner)
                        {
                            nProcessStep[nStepIndex] = 2100;
                        }
                        else
                        {
                            nProcessStep[nStepIndex] = 4000;
                        }
                    }
                    break;



                case 2100:
                    if (!MotionDone(AXIS.EOL_X) || !MotionDone(AXIS.EOL_Y) || !MotionDone(AXIS.EOL_Z)) { break; }

                    MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbReadyPos1X, _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2101:
                    if (!MotionDone(AXIS.EOL_X)) { break; }

                    MoveTo(AXIS.EOL_Y, _ModelInfo._TestInfo[1].dbSpare_b[1], _Config.dbTestZoneMoveSpeed);
                    {
                        double dbNowPos1Z = 0;
                        CAXM.AxmStatusGetCmdPos((int)AXIS.EOL_Z, ref dbNowPos1Z);

                        double dbSpeed = 0;
                        dbSpeed = (Math.Abs(_ModelInfo._TestInfo[1].dbSpare_b[2] - dbNowPos1Z) > _Config.dbTestZoneContactZSlowMovePos) ? _Config.dbTestZoneContactZSlowMoveSpeed : _Config.dbTestZoneMoveSpeed;
                        MoveTo(AXIS.EOL_Z, _ModelInfo._TestInfo[1].dbSpare_b[2], dbSpeed);
                    }



                    nProcessStep[nStepIndex]++;
                    break;

                case 2102:
                    if (!MotionDone(AXIS.EOL_Y) || !MotionDone(AXIS.EOL_Z)) { break; }

                    MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbSpare_b[0], _Config.dbTestZoneMoveSpeed);
                    _EOLReader.bReadOk = false;
                    _EOLReader.TriggerOn();
                    nProcessStep[nStepIndex] = 2110;
                    break;

                // 바코드 스캔 시도
                case 2110:
                    //if (MotionDone(AXIS.EOL_X))
                    //{
                    //    tMainTimer[nStepIndex].Start(_Config.nBCDScanTimeOut);
                    //    nProcessStep[nStepIndex]++;
                    //    break;
                    //}
                    //if (_EOLReader.bReadOk)
                    //{
                    //    nProcessStep[nStepIndex] = 2400;
                    //}
                    if (MotionDone(AXIS.EOL_X))
                    {
                        //_SysInfo.dbEolDistanceGap = _ModelInfo.dbEolDistance - _TesterDistance.dbDistance[0];     // 거리 편차를 구함

                        //if (_ModelInfo.bUseEolDistance)
                        //{
                        //    if (Math.Abs(_SysInfo.dbEolDistanceGap) > 100)
                        //    {
                        //        _SysInfo.eContactStatus[1] = CONTACT_STATUS.CONTACT_ALARM;
                        //        AppendLogMsg(String.Format("Station #EOL - 거리측정 실패."), LOG_TYPE.ERROR);
                        //        _EOLReader.TriggerOff();
                        //        nProcessStep[nStepIndex] = 1000;    // 커뮤니케이션 실패
                        //        break;
                        //    }
                        //}


                        if (_EOLReader.bReadOk)
                        {
                            nProcessStep[nStepIndex] = 2400;
                        }
                        else
                        {
                            tMainTimer[nStepIndex].Start(_Config.nBCDScanTimeOut);
                            nProcessStep[nStepIndex]++;
                        }

                    }
                    break;

                case 2111:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex]++;
                        break;
                    }

                    if (_EOLReader.bReadOk)
                    {
                        nProcessStep[nStepIndex] = 2400;
                    }
                    break;

                //case 2111:
                //    if (tMainTimer[nStepIndex].Verify())
                //    {
                //        _SysInfo.eContactStatus[1] = CONTACT_STATUS.CONTACT_ALARM;
                //        AppendLogMsg(String.Format("Station #{0} - 바코드 스캔 실패.", 6), LOG_TYPE.ERROR);
                //        _EOLReader.TriggerOff();
                //        nProcessStep[nStepIndex] = 1000;    // 커뮤니케이션 실패
                //        break;
                //    }

                //    if (_EOLReader.bReadOk)
                //    {

                //        nProcessStep[nStepIndex] = 410;
                //    }
                //    break;


                case 2112:
                    MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbSpare_b[0] + 2, _Config.dbTestZoneMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2113:
                    if (MotionDone(AXIS.EOL_X))
                    {
                        MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbSpare_b[0], _Config.dbTestZoneMoveSpeed);
                        nProcessStep[nStepIndex]++;
                    }
                    if (_EOLReader.bReadOk)
                    {
                        nProcessStep[nStepIndex] = 2400;
                    }
                    break;

                case 2114:
                    if (MotionDone(AXIS.EOL_X))
                    {
                        MoveTo(AXIS.EOL_Y, _ModelInfo._TestInfo[1].dbSpare_b[1] + 2, _Config.dbTestZoneMoveSpeed);
                        nProcessStep[nStepIndex]++;
                    }
                    if (_EOLReader.bReadOk)
                    {
                        nProcessStep[nStepIndex] = 2400;
                    }
                    break;

                case 2115:
                    if (MotionDone(AXIS.EOL_Y))
                    {
                        MoveTo(AXIS.EOL_Y, _ModelInfo._TestInfo[1].dbSpare_b[1] - 2, _Config.dbTestZoneMoveSpeed);
                        nProcessStep[nStepIndex]++;
                    }
                    if (_EOLReader.bReadOk)
                    {
                        nProcessStep[nStepIndex] = 2400;
                    }
                    break;

                case 2116:
                    if (MotionDone(AXIS.EOL_Y))
                    {
                        MoveTo(AXIS.EOL_Y, _ModelInfo._TestInfo[1].dbSpare_b[1], _Config.dbTestZoneMoveSpeed);
                        nProcessStep[nStepIndex]++;
                    }
                    if (_EOLReader.bReadOk)
                    {
                        nProcessStep[nStepIndex] = 2400;
                    }
                    break;

                case 2117:
                    if (MotionDone(AXIS.EOL_Y))
                    {
                        _SysInfo.eContactStatus[1] = CONTACT_STATUS.CONTACT_ALARM;
                        AppendLogMsg(String.Format("Station #EOL - 바코드 스캔 실패.", 7), LOG_TYPE.ERROR);
                        _EOLReader.TriggerOff();
                        nProcessStep[nStepIndex] = 1000;    // 커뮤니케이션 실패
                    }
                    break;

                case 2400:
                    if (!MotionDone(AXIS.EOL_X) || !MotionDone(AXIS.EOL_Y) || !MotionDone(AXIS.EOL_Z)) { break; }
                    if (_Config.bUseMESTestCheck)
                    {
                        if (!Check_Server_Barcode(_EOLReader.strReadBarcode, 1))
                        {
                            _SysInfo.eContactStatus[1] = CONTACT_STATUS.CONTACT_ALARM;
                            AppendLogMsg(String.Format("Station #EOL - MES ERROR."), LOG_TYPE.ERROR);
                            _EOLReader.TriggerOff();
                            nProcessStep[nStepIndex] = 1000;    // 커뮤니케이션 실패
                            break;
                        }

                    }
                    if (CheckEOLBcdDuplicate(_EOLReader.strReadBarcode))
                    {
                        _SysInfo.eContactStatus[1] = CONTACT_STATUS.CONTACT_ALARM;
                        if (_Config.strLangue == "KOR") { AppendLogMsg(String.Format("EOL - 중복 바코드 입니다."), LOG_TYPE.ERROR); }
                        else { AppendLogMsg(String.Format("EOL - 重复条形码。"), LOG_TYPE.ERROR); }
                        _EOLReader.TriggerOff();
                        nProcessStep[nStepIndex] = 1000;    // 커뮤니케이션 실패
                        break;

                    }
                    nProcessStep[nStepIndex] = 3000;
                    break;

               // 외함측정 검사 (EOL 스테이션에 있음)
                case 3000:
                    if (!_ModelInfo.bUseOmronWHTest)
                    {
                        //외함측정 검사를 사용하지 않을경우 바로 EOL 테스트로 돌입한다
                        nProcessStep[nStepIndex] = 410;
                        break;
                    }

                    //움직이기 전에 일단 Z축부터 대기위치로 이동한다
                    MoveTo(AXIS.CAMERA1_Z, _ModelInfo.dbCamera1ReadyPosZ, _Config.dbOmronCameraZMoveSpeed);
                    MoveTo(AXIS.CAMERA2_Z, _ModelInfo.dbCamera2ReadyPosZ, _Config.dbOmronCameraZMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 3001:
                    if (!MotionDone(AXIS.CAMERA1_Z) || !MotionDone(AXIS.CAMERA2_Z)) { break; }

                    nProcessStep[nStepIndex] = 3010;
                    break;

                // 검사위치로 이동
                case 3010:
                    MoveTo(AXIS.CAMERA1_X, _ModelInfo.dbCamera1WorkPosX, _Config.dbOmronCameraXYMoveSpeed);
                    MoveTo(AXIS.CAMERA1_Y, _ModelInfo.dbCamera1WorkPosY, _Config.dbOmronCameraXYMoveSpeed);
                    MoveTo(AXIS.CAMERA2_X, _ModelInfo.dbCamera2WorkPosX, _Config.dbOmronCameraXYMoveSpeed);
                    MoveTo(AXIS.CAMERA2_Y, _ModelInfo.dbCamera2WorkPosY, _Config.dbOmronCameraXYMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 3011:
                    if (!MotionDone(AXIS.CAMERA1_X) || !MotionDone(AXIS.CAMERA1_Y) || !MotionDone(AXIS.CAMERA2_X) || !MotionDone(AXIS.CAMERA2_Y)) { break; }

                    nProcessStep[nStepIndex] = 3020;
                    break;

                // 검사위치 Z축 이동
                case 3020:
                    MoveTo(AXIS.CAMERA1_Z, _ModelInfo.dbCamera1WorkPosZ, _Config.dbOmronCameraZMoveSpeed);
                    MoveTo(AXIS.CAMERA2_Z, _ModelInfo.dbCamera2WorkPosZ, _Config.dbOmronCameraZMoveSpeed);
                    DeleteOmronWHData();
                    nProcessStep[nStepIndex]++;
                    break;

                case 3021:
                    if (!MotionDone(AXIS.CAMERA1_Z) || !MotionDone(AXIS.CAMERA2_Z)) { break; }

                    tMainTimer[nStepIndex].Start(_Config.nOmronCameraStabliTime); // 1초의 대기시간 ( 흔들림 안정화 시간 )
                    nProcessStep[nStepIndex]++;
                    break;

                case 3022:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    nProcessStep[nStepIndex] = 3050;
                    break;


                // 카메라 검사시작
                case 3050:
                    _OmronWHTester.SetSch(_ModelInfo.strOmronWHTestCMD, _ModelInfo.strOmronWHTestSch, _ModelInfo.strOmronWHTestSelect); // 스케쥴 설정
                    _OmronWHTester.TestStart(); // 검사 시작
                    tMainTimer[nStepIndex].Start(20000);    // 테스트 타임아웃
                    nProcessStep[nStepIndex]++;
                    break;

                case 3051:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        // 통신 타임아웃
                        AppendLogMsg("외함측정 통신 타임아웃", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 1300;
                        break;
                    }


                    if (_OmronWHTester.GetTestFinish())
                    {
                        tMainTimer[nStepIndex].Start(_Config.nCapDealy);
                        nProcessStep[nStepIndex] = 3052;
                    }
                    break;

                case 3052:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    _OmronWHTester.SetSch(_Config.strOmronWHTesterCapCMD, _Config.strOmronWHTesterCapSch, _Config.strOmronWHTesterCapOpt); // 스케쥴 설정
                    _OmronWHTester.TestStart(); // 검사 시작
                    tMainTimer[nStepIndex].Start(_Config.nFileGetDealy);
                    nProcessStep[nStepIndex] = 3055;
                    break;

                case 3055:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    // 검사가 종료된 경우   
                    //if (_OmronWHTester.GetWidth() > _ModelInfo.dbOmronWDTestSpecWidthMax ||
                    //_OmronWHTester.GetWidth() < _ModelInfo.dbOmronWDTestSpecWidth)
                    if (_OmronWHTester.GetHight() > _ModelInfo.dbOmronWDTestSpecHightMax ||
                       _OmronWHTester.GetHight() < _ModelInfo.dbOmronWDTestSpecHight)
                    {
                        // NG 임
                        _mainform.Invoke(new Action(() => _mainform.ViewOmronWHLog(_EOLReader.strReadBarcode, "NG", _OmronWHTester.GetWidth(), _OmronWHTester.GetHight())));
                        _BatteryTester[1].SendOmronData(_EOLReader.strReadBarcode, "NG", _OmronWHTester.GetHight());
                        SaveOmronWHResult(_EOLReader.strReadBarcode, "NG", _OmronWHTester.GetWidth(), _OmronWHTester.GetHight());
                        nProcessStep[nStepIndex] = 1300;
                    }
                    else
                    {
                        // OK 임
                        _mainform.Invoke(new Action(() => _mainform.ViewOmronWHLog(_EOLReader.strReadBarcode, "OK", _OmronWHTester.GetWidth(), _OmronWHTester.GetHight())));
                        _BatteryTester[1].SendOmronData(_EOLReader.strReadBarcode, "OK", _OmronWHTester.GetHight());
                        SaveOmronWHResult(_EOLReader.strReadBarcode, "OK", _OmronWHTester.GetWidth(), _OmronWHTester.GetHight());
                        nProcessStep[nStepIndex] = 3060;
                    }

                    MoveOmronWHData(_EOLReader.strReadBarcode);
                    break;








                case 3060:
                    // Z 대기위치로 이동
                    MoveTo(AXIS.CAMERA1_Z, _ModelInfo.dbCamera1ReadyPosZ, _Config.dbOmronCameraZMoveSpeed);
                    MoveTo(AXIS.CAMERA2_Z, _ModelInfo.dbCamera2ReadyPosZ, _Config.dbOmronCameraZMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;


                case 3061:
                    if (!MotionDone(AXIS.CAMERA1_Z) || !MotionDone(AXIS.CAMERA2_Z)) { break; }

                    nProcessStep[nStepIndex] = 3070;
                    break;


                case 3070:
                    MoveTo(AXIS.CAMERA1_X, _ModelInfo.dbCamera1ReadyPosX, _Config.dbOmronCameraXYMoveSpeed);
                    MoveTo(AXIS.CAMERA1_Y, _ModelInfo.dbCamera1ReadyPosY, _Config.dbOmronCameraXYMoveSpeed);
                    MoveTo(AXIS.CAMERA2_X, _ModelInfo.dbCamera2ReadyPosX, _Config.dbOmronCameraXYMoveSpeed);
                    MoveTo(AXIS.CAMERA2_Y, _ModelInfo.dbCamera2ReadyPosY, _Config.dbOmronCameraXYMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 3071:
                    if (!MotionDone(AXIS.CAMERA1_X) || !MotionDone(AXIS.CAMERA1_Y) || !MotionDone(AXIS.CAMERA2_X) || !MotionDone(AXIS.CAMERA2_Y)) { break; }

                    nProcessStep[nStepIndex] = 410;
                    break;



                //case 3000:
                //    SetDIOPort(DO.EOL_N_CONTACT_CHECK, true);
                //    SetDIOPort(DO.EOL_P_CONTACT_CHECK, true);
                //    tMainTimer[nStepIndex].Start(200);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 3001:
                //    if (GetDIOPort(DI.EOL_N_CONTACT_OK) && GetDIOPort(DI.EOL_P_CONTACT_OK))
                //    {
                //        SetDIOPort(DO.EOL_N_CONTACT_CHECK, false);
                //        SetDIOPort(DO.EOL_P_CONTACT_CHECK, false);
                //        nProcessStep[nStepIndex] = 450;
                //    }
                //    else
                //    {
                //        nProcessStep[nStepIndex] = 3010;
                //    }
                //    break;


                //case 3010:
                //    if (!MotionDone(AXIS.EOL_X)) { break; }

                //    MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbContactPos1X - _Config.dbTestZoneContactMovePos, _Config.dbTestZoneMoveSpeed);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 3011:
                //    if (!MotionDone(AXIS.EOL_X)) { break; }

                //    MoveTo(AXIS.EOL_Y, _ModelInfo._TestInfo[1].dbContactPos1Y - 1.0, _Config.dbTestZoneMoveSpeed);
                //    MoveTo(AXIS.EOL_Z, _ModelInfo._TestInfo[1].dbContactPos1Z - 1.0, _Config.dbTestZoneMoveSpeed);

                //    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 3012:
                //    if (!MotionDone(AXIS.EOL_Y) || !MotionDone(AXIS.EOL_Z)) { break; }
                //    MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbContactPos1X, _Config.dbTestZoneContactSpeed);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //// 모션 개별 움직임
                //case 3013:
                //    if (!MotionDone(AXIS.EOL_X)) { break; }

                //    if (GetDIOPort(DI.EOL_N_CONTACT_OK) && GetDIOPort(DI.EOL_P_CONTACT_OK))
                //    {
                //        SetDIOPort(DO.EOL_N_CONTACT_CHECK, false);
                //        SetDIOPort(DO.EOL_P_CONTACT_CHECK, false);
                //        nProcessStep[nStepIndex] = 450;
                //    }
                //    else
                //    {
                //        nProcessStep[nStepIndex] = 3020;
                //    }
                //    break;


                //case 3020:
                //    if (!MotionDone(AXIS.EOL_X)) { break; }

                //    MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbContactPos1X - _Config.dbTestZoneContactMovePos, _Config.dbTestZoneMoveSpeed);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 3021:
                //    if (!MotionDone(AXIS.EOL_X)) { break; }

                //    MoveTo(AXIS.EOL_Y, _ModelInfo._TestInfo[1].dbContactPos1Y + 1.0, _Config.dbTestZoneMoveSpeed);
                //    MoveTo(AXIS.EOL_Z, _ModelInfo._TestInfo[1].dbContactPos1Z - 1.0, _Config.dbTestZoneMoveSpeed);

                //    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 3022:
                //    if (!MotionDone(AXIS.EOL_Y) || !MotionDone(AXIS.EOL_Z)) { break; }
                //    MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbContactPos1X, _Config.dbTestZoneContactSpeed);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //// 모션 개별 움직임
                //case 3023:
                //    if (!MotionDone(AXIS.EOL_X)) { break; }

                //    if (GetDIOPort(DI.EOL_N_CONTACT_OK) && GetDIOPort(DI.EOL_P_CONTACT_OK))
                //    {
                //        SetDIOPort(DO.EOL_N_CONTACT_CHECK, false);
                //        SetDIOPort(DO.EOL_P_CONTACT_CHECK, false);
                //        nProcessStep[nStepIndex] = 450;
                //    }
                //    else
                //    {
                //        nProcessStep[nStepIndex] = 3030;
                //    }
                //    break;


                //case 3030:
                //    if (!MotionDone(AXIS.EOL_X)) { break; }

                //    MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbContactPos1X - _Config.dbTestZoneContactMovePos, _Config.dbTestZoneMoveSpeed);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 3031:
                //    if (!MotionDone(AXIS.EOL_X)) { break; }

                //    MoveTo(AXIS.EOL_Y, _ModelInfo._TestInfo[1].dbContactPos1Y - 1.0, _Config.dbTestZoneMoveSpeed);
                //    MoveTo(AXIS.EOL_Z, _ModelInfo._TestInfo[1].dbContactPos1Z + 1.0, _Config.dbTestZoneMoveSpeed);

                //    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 3032:
                //    if (!MotionDone(AXIS.EOL_Y) || !MotionDone(AXIS.EOL_Z)) { break; }
                //    MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbContactPos1X, _Config.dbTestZoneContactSpeed);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //// 모션 개별 움직임
                //case 3033:
                //    if (!MotionDone(AXIS.EOL_X)) { break; }

                //    if (GetDIOPort(DI.EOL_N_CONTACT_OK) && GetDIOPort(DI.EOL_P_CONTACT_OK))
                //    {
                //        SetDIOPort(DO.EOL_N_CONTACT_CHECK, false);
                //        SetDIOPort(DO.EOL_P_CONTACT_CHECK, false);
                //        nProcessStep[nStepIndex] = 450;
                //    }
                //    else
                //    {
                //        nProcessStep[nStepIndex] = 3040;
                //    }
                //    break;


                //case 3040:
                //    if (!MotionDone(AXIS.EOL_X)) { break; }

                //    MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbContactPos1X - _Config.dbTestZoneContactMovePos, _Config.dbTestZoneMoveSpeed);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 3041:
                //    if (!MotionDone(AXIS.EOL_X)) { break; }

                //    MoveTo(AXIS.EOL_Y, _ModelInfo._TestInfo[1].dbContactPos1Y + 1.0, _Config.dbTestZoneMoveSpeed);
                //    MoveTo(AXIS.EOL_Z, _ModelInfo._TestInfo[1].dbContactPos1Z + 1.0, _Config.dbTestZoneMoveSpeed);

                //    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //case 3042:
                //    if (!MotionDone(AXIS.EOL_Y) || !MotionDone(AXIS.EOL_Z)) { break; }
                //    MoveTo(AXIS.EOL_X, _ModelInfo._TestInfo[1].dbContactPos1X, _Config.dbTestZoneContactSpeed);
                //    nProcessStep[nStepIndex]++;
                //    break;

                //// 모션 개별 움직임
                //case 3043:
                //    if (!MotionDone(AXIS.EOL_X)) { break; }

                //    if (GetDIOPort(DI.EOL_N_CONTACT_OK) && GetDIOPort(DI.EOL_P_CONTACT_OK))
                //    {
                //        SetDIOPort(DO.EOL_N_CONTACT_CHECK, false);
                //        SetDIOPort(DO.EOL_P_CONTACT_CHECK, false);
                //        nProcessStep[nStepIndex] = 450;
                //    }
                //    else
                //    {
                //        SetDIOPort(DO.EOL_N_CONTACT_CHECK, false);
                //        SetDIOPort(DO.EOL_P_CONTACT_CHECK, false);
                //        nProcessStep[nStepIndex] = 3050;
                //    }
                //    break;


                //case 3050:
                //    _SysInfo.eContactStatus[1] = CONTACT_STATUS.CONTACT_ALARM;
                //    AppendLogMsg(String.Format("EOL - CONATCT FAIL.."), LOG_TYPE.ERROR);
                //    nProcessStep[nStepIndex] = 1000;    // 커뮤니케이션 실패
                //    break;



                // ???
                // EOL 재시도 루틴
                case 4000:
                    SetDIOPort(DO.EOL_CAN_CONTACT_ON, false);
                    tMainTimer[nStepIndex].Start(200);
                    nProcessStep[nStepIndex]++;
                    break;

                case 4001:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    SetDIOPort(DO.EOL_CAN_CONTACT_ON, true);
                    tMainTimer[nStepIndex].Start(200);
                    nProcessStep[nStepIndex]++;
                    break;

                case 4002:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    _BatteryTester[1]._Status = BatteryTesterStat.READY;    // 준비 상태로 만들고
                    _BatteryTester[1].WriteData("RETRY");   // 리트라이 명령 보냄
                    tMainTimer[nStepIndex].Start(5000);     // 5초 대기
                    nProcessStep[nStepIndex]++;
                    // Retry 명령
                    break;

                case 4003:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("EOL 시험기가 응답하지 않습니다...", LOG_TYPE.ERROR);
                        _SysInfo.nTL_Beep = 2;
                        nProcessStep[nStepIndex] = 1000;
                    }

                    //if (_BatteryTester[1].bRequest)
                    //{
                    if (_BatteryTester[1]._Status == BatteryTesterStat.START)
                    {
                        // 정상적으로 시작했을시 양불 대기스텝으로 이동
                        //_BatteryTester[1].bRequest = false;
                        //_BatteryTester[1].bCheckOkng = true;
                        //_BatteryTester[1].nCurrentStep = 0;
                        nProcessStep[nStepIndex] = 460;
                    }
                    //}
                    break;

                case 9000:
                    _SysInfo.ST_Red[1] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_Green[1] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_Yellow[1] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_Buzzer[1] = TOWER_LAMP.TL_OFF;

                    _SysInfo.ST_TL_RED[1] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_TL_YELLOW[1] = TOWER_LAMP.TL_OFF;
                    _SysInfo.ST_TL_GREEN[1] = TOWER_LAMP.TL_OFF;
                    _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7] = false;
                    break;

                case 10000:
                    nProcessStep[nStepIndex] = 9000;
                    _SysInfo.TL_Buzzer = TOWER_LAMP.TL_ON;
                    break;
            }

        }
        //===========================================================

        // EOL 중복정보 저장
        static void SaveEOLBcdDuplicate(string strBCD)
        {
            // EOL 중복 생성
            string strSaveFolderPath = String.Format(@"Duplicate\\EOL\\");
            DirectoryInfo Savedir = new DirectoryInfo(strSaveFolderPath);
            if (Savedir.Exists == false) { Savedir.Create(); }

            string strSaveFilePath = String.Format(@"{0}{1}.txt", strSaveFolderPath, strBCD);
            File.WriteAllText(strSaveFilePath, "");

            // 저장하면서 오래된 파일 삭제
            string[] files = Directory.GetFiles(strSaveFolderPath);

            foreach (string file in files)
            {
                FileInfo fi = new FileInfo(file);
                if (fi.LastAccessTime < DateTime.Now.AddMonths(-1))
                    fi.Delete();
            }
        }

        static bool CheckEOLBcdDuplicate(string strBCD)
        {

            string strSaveFolderPath = String.Format(@"Duplicate\\EOL\\");
            DirectoryInfo Savedir = new DirectoryInfo(strSaveFolderPath);
            if (Savedir.Exists == false) { Savedir.Create(); }

            string strSaveFilePath = String.Format(@"{0}{1}.txt", strSaveFolderPath, strBCD);
            FileInfo _file = new FileInfo(strSaveFilePath);

            return _file.Exists;            // 파일 존재여부 확인

        }


        // 외함측정 결과 저장하기
        public static void SaveOmronWHResult(string strBCD, string strResult, double dbWidth, double dbHight)
        {
            string strMessage = "";

            strMessage = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss") + "\t" + strBCD + "\t" + strResult + "\t" + dbWidth.ToString() + "\t" + dbHight.ToString() + "\r\n";



            // 우리쪽 임시 폴더에 저장
            string strSaveFolderPath = String.Format(@"E:\\DATA\\OMRONWH\\{0}\\{1}\\", _ModelInfo.strModelName, Program._LotCount.tLotClearTime.ToString("yyMMdd"));
            DirectoryInfo Savedir = new DirectoryInfo(strSaveFolderPath);
            if (Savedir.Exists == false) { Savedir.Create(); }

            string strSaveFilePath = String.Format(@"{0}{1}.txt", strSaveFolderPath, strBCD);
            File.AppendAllText(strSaveFilePath, strMessage);



            // CSV 파일로 저장하기
            strSaveFilePath = String.Format(@"{0}TotalData.csv", strSaveFolderPath);



            string strWidthResult = "";
            string strHightResult = "";

            if (dbWidth > _ModelInfo.dbOmronWDTestSpecWidthMax || dbWidth < _ModelInfo.dbOmronWDTestSpecWidth)
            {
                strWidthResult = "NG";
            }
            else
            {
                strWidthResult = "OK";
            }

            if (dbHight > _ModelInfo.dbOmronWDTestSpecHightMax || dbHight < _ModelInfo.dbOmronWDTestSpecHight)
            {
                strHightResult = "NG";
            }
            else
            {
                strHightResult = "OK";
            }

            strMessage = "";
            if (!File.Exists(strSaveFilePath))
            {
                // 파일이 없을경우 헤더 생성
                //strMessage += "시간," + "바코드," + "결과," + "전장," + "판정(전장)," + "전폭," + "판정(전폭)" + "\r\n";
                strMessage += "시간," + "바코드," + "결과," + "전장," + "판정(전장)," + "\r\n";
            }

            //strMessage += DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss") + "," + strBCD + "," + strResult + "," + dbWidth.ToString() + "," + strWidthResult + "," + dbHight.ToString() + "," + strHightResult + "\r\n";
            strMessage += DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss") + "," + strBCD + "," + strResult + "," + dbHight.ToString() + "," + strHightResult + "\r\n";
            File.AppendAllText(strSaveFilePath, strMessage);

        }


        // 데이터 삭제
        public static void DeleteOmronWHData()
        {
            DirectoryInfo _Origin = new DirectoryInfo(_Config.strOmronOriginImgDir);

            foreach (DirectoryInfo _dinfo in _Origin.GetDirectories())
            {
                _dinfo.Delete(true);
            }

            DirectoryInfo _Screen = new DirectoryInfo(_Config.strOmronScreenImgDir);

            foreach (FileInfo _finfo in _Screen.GetFiles())
            {
                File.Delete(_finfo.FullName);
            }
        }

        // 데이터 이동
        public static void MoveOmronWHData(string strBCD)
        {
            string strSaveFolderPath = String.Format(@"E:\\DATA\\OMRONWH_LOG\\{0}\\{1}\\{2}\\", _ModelInfo.strModelName, Program._LotCount.tLotClearTime.ToString("yyMMdd"), strBCD);
            DirectoryInfo Savedir = new DirectoryInfo(strSaveFolderPath);
            if (Savedir.Exists == false) { Savedir.Create(); }

            DirectoryInfo _Origin = new DirectoryInfo(_Config.strOmronOriginImgDir);

            foreach (DirectoryInfo _dinfo in _Origin.GetDirectories())
            {
                //AppendLogMsg(_dinfo.FullName, Color.Gray);
                foreach (FileInfo _finfo in _dinfo.GetFiles())
                {
                    // AppendLogMsg(_finfo.FullName, Color.Gray);
                    File.Copy(_finfo.FullName, strSaveFolderPath + _finfo.Name, true);
                }
            }

            DirectoryInfo _Screen = new DirectoryInfo(_Config.strOmronScreenImgDir);

            foreach (FileInfo _finfo in _Screen.GetFiles())
            {
                File.Copy(_finfo.FullName, strSaveFolderPath + _finfo.Name, true);
            }

        }



        public static void SaveIRFetchData(string strBCD, double dbIR, int nCount, string strCate)
        {
            string strSaveFolderPath = String.Format(@"E:\\DATA\\HIPOT\\IR_LOG\\");
            DirectoryInfo Savedir = new DirectoryInfo(strSaveFolderPath);
            if (Savedir.Exists == false) { Savedir.Create(); }


            string strSaveData = "";
            strSaveData = strBCD + ",";
            strSaveData += strCate + ",";
            strSaveData += DateTime.Now.ToString("yyyy'.'MM'.'dd") + " " + DateTime.Now.ToString("HH':'mm':'ss") + ",";
            strSaveData += nCount.ToString() + ",";
            strSaveData += (dbIR * 0.000001).ToString("0.00") + "\r\n";

            string strSaveFilePath = String.Format(@"{0}{1}.txt", strSaveFolderPath, Program._LotCount.tLotClearTime.ToString("yyyy-MM-dd"));

            File.AppendAllText(strSaveFilePath, strSaveData);

            //AppendLogMsg(strSaveData, LOG_TYPE.LOG);
        }

        public static void SaveHipotMESData()
        {




            try
            {
                string strSaveData = "";
                strSaveData = _HipotResult.strBCD + ",";
                strSaveData += _HipotResult.tTestTime.ToString("yyyy'.'MM'.'dd") + " " + _HipotResult.tTestTime.ToString("HH':'mm':'ss") + ",";
                strSaveData += _HipotResult.tr_TOTAL.ToString() + ",";
                strSaveData += (_HipotResult.dbOSCData * 1000000000).ToString("0.00") + ",";
                strSaveData += (_HipotResult.dbNOSCData * 1000000000).ToString("0.00") + ",";
                strSaveData += (_HipotResult.dbPIRData * 0.000001).ToString("0.00") + ",";
                strSaveData += (_HipotResult.dbNIRData * 0.000001).ToString("0.00") + ",";
                strSaveData += (_HipotResult.dbGBData * 1000).ToString("0.000") + ",";
                strSaveData += (_HipotResult.dbHipotPos * 1000).ToString("0.00") + ",";
                strSaveData += (_HipotResult.dbHipotNeg * 1000).ToString("0.00") + ",";
                strSaveData += _tHipotTimer.Elapsed.ToString("mm':'ss':'ff") + "\r\n";

                //===============우리쪽 임시데이터 저장 =========
                // 바코드 파일
                string strSaveFolderPath = String.Format(@"E:\\DATA\\HIPOT\\{0}\\", _ModelInfo.strModelName);
                DirectoryInfo Savedir = new DirectoryInfo(strSaveFolderPath);
                if (Savedir.Exists == false) { Savedir.Create(); }

                string strSaveFilePath = String.Format(@"{0}{1}.txt", strSaveFolderPath, Program._LotCount.tLotClearTime.ToString("yyyy-MM-dd"));
                if (!File.Exists(strSaveFilePath))
                {
                    string strTitle = "";
                    strTitle = "Barcode,";
                    strTitle += "Time,";
                    strTitle += "Total,";
                    strTitle += "OSC(+),";
                    strTitle += "OSC(-),";
                    strTitle += "IR(+),";
                    strTitle += "IR(-),";
                    strTitle += "GB(+),";
                    strTitle += "HIPOT(+),";
                    strTitle += "HIPOT(-),";
                    strTitle += "TestTime\r\n";

                    File.AppendAllText(strSaveFilePath, strTitle);
                }
                File.AppendAllText(strSaveFilePath, strSaveData);

                //===============우리쪽 임시데이터 추가 저장 =========
                // 바코드 파일
                strSaveFolderPath = String.Format(@"E:\\DATA2\\HIPOT\\{0}\\", _ModelInfo.strModelName);
                Savedir = new DirectoryInfo(strSaveFolderPath);
                if (Savedir.Exists == false) { Savedir.Create(); }

                strSaveFilePath = String.Format(@"{0}{1}.txt", strSaveFolderPath, Program._LotCount.tLotClearTime.ToString("yyyy-MM-dd"));
                if (!File.Exists(strSaveFilePath))
                {
                    string strTitle = "";
                    strTitle = "Barcode,";
                    strTitle += "Time,";
                    strTitle += "Total,";
                    strTitle += "OSC(+),";
                    strTitle += "OSC(-),";
                    strTitle += "IR(+),";
                    strTitle += "IR(-),";
                    strTitle += "GB(+),";
                    strTitle += "HIPOT(+),";
                    strTitle += "HIPOT(-),";
                    strTitle += "TestTime\r\n";

                    File.AppendAllText(strSaveFilePath, strTitle);
                }
                File.AppendAllText(strSaveFilePath, strSaveData);


                //================ 마스터 데이터 저장
                strSaveFolderPath = String.Format(@"E:\\MASTER\\HIPOT\\{0}\\", _ModelInfo.strModelName);
                Savedir = new DirectoryInfo(strSaveFolderPath);
                if (Savedir.Exists == false) { Savedir.Create(); }

                strSaveFilePath = String.Format(@"{0}{1}]{1}.txt", strSaveFolderPath, Program._LotCount.tLotClearTime.ToString("yyyy-MM-dd"));
                if (!File.Exists(strSaveFilePath))
                {
                    string strTitle = "";
                    strTitle = "Barcode,";
                    strTitle += "Time,";
                    strTitle += "Total,";
                    strTitle += "OSC(+),";
                    strTitle += "OSC(-),";
                    strTitle += "IR(+),";
                    strTitle += "IR(-),";
                    strTitle += "GB(+),";
                    strTitle += "HIPOT(+),";
                    strTitle += "HIPOT(-),";
                    strTitle += "TestTime\r\n";

                    File.AppendAllText(strSaveFilePath, strTitle);
                }
                File.AppendAllText(strSaveFilePath, strSaveData);


                strSaveData = _HipotResult.strBCD + "\t";
                strSaveData += _HipotResult.tTestTime.ToString("yyyy'.'MM'.'dd") + " " + _HipotResult.tTestTime.ToString("HH':'mm':'ss") + "\t";
                strSaveData += _HipotResult.tr_TOTAL.ToString() + "\t";
                strSaveData += (_HipotResult.dbOSCData * 1000000000).ToString("0.00") + "\t";
                strSaveData += (_HipotResult.dbNOSCData * 1000000000).ToString("0.00") + "\t";
                strSaveData += (_HipotResult.dbPIRData * 0.000001).ToString("0.00") + "\t";
                strSaveData += (_HipotResult.dbNIRData * 0.000001).ToString("0.00") + "\t";
                strSaveData += (_HipotResult.dbGBData * 1000).ToString("0.000") + "\t";
                strSaveData += (_HipotResult.dbHipotPos * 1000).ToString("0.00") + "\t";
                strSaveData += (_HipotResult.dbHipotNeg * 1000).ToString("0.00") + "\t";
                strSaveData += _tHipotTimer.Elapsed.ToString("mm':'ss':'ff");



                //========================== ERP 데이터 저장
                strSaveFolderPath = String.Format(@"{0}\\", _Config.strHIPOTMESDir);
                Savedir = new DirectoryInfo(strSaveFolderPath);
                if (Savedir.Exists == false) { Savedir.Create(); }

                strSaveFilePath = String.Format(@"{0}{1}.txt", strSaveFolderPath, _HipotResult.strBCD);
                File.WriteAllText(strSaveFilePath, strSaveData);


                //========================== BackUp 데이터 저장
                strSaveFolderPath = String.Format(@"E:\\BACKUP\\HIPOT\\{0}\\{1}\\", _ModelInfo.strModelName, Program._LotCount.tLotClearTime.ToString("yyMMdd"));
                Savedir = new DirectoryInfo(strSaveFolderPath);
                if (Savedir.Exists == false) { Savedir.Create(); }

                strSaveFilePath = String.Format(@"{0}{1}.txt", strSaveFolderPath, _HipotResult.strBCD);
                File.WriteAllText(strSaveFilePath, strSaveData);

                //========================== BackUp 데이터 저장
                strSaveFolderPath = String.Format(@"E:\\BACKUP2\\HIPOT\\{0}\\{1}\\", _ModelInfo.strModelName, Program._LotCount.tLotClearTime.ToString("yyMMdd"));
                Savedir = new DirectoryInfo(strSaveFolderPath);
                if (Savedir.Exists == false) { Savedir.Create(); }

                strSaveFilePath = String.Format(@"{0}{1}.txt", strSaveFolderPath, _HipotResult.strBCD);
                File.WriteAllText(strSaveFilePath, strSaveData);



                // 중복 감지 데이터 남김
                SaveHipotBcdDuplicate(_HipotResult.strBCD);



            }
            catch { }
        }



        // CMA 중복정보 저장
        static void SaveCMABcdDuplicate()
        {
            // Hipot 중복 생성
            string strSaveFolderPath = String.Format(@"Duplicate\\CMA\\");
            DirectoryInfo Savedir = new DirectoryInfo(strSaveFolderPath);
            if (Savedir.Exists == false) { Savedir.Create(); }


            for (int i = 0; i < _ReadBCDList.Count; i++)
            {
                if (_ReadBCDList[i].strCate == "CMA")
                {
                    string strSaveFilePath = String.Format(@"{0}{1}.txt", strSaveFolderPath, _ReadBCDList[i].strBCD);
                    File.WriteAllText(strSaveFilePath, "");
                }
            }

            // 저장하면서 오래된 파일 삭제
            string[] files = Directory.GetFiles(strSaveFolderPath);

            foreach (string file in files)
            {
                FileInfo fi = new FileInfo(file);
                if (fi.LastAccessTime < DateTime.Now.AddMonths(-1))
                    fi.Delete();
            }
        }


        public static bool CheckBarcode(string readBarcode, string strTargetBarcode)
        {
            if (readBarcode.Length != strTargetBarcode.Length)
            {
                return false;
            }
            else
            {

                for (int nBCDLen = 0; nBCDLen < strTargetBarcode.Length; nBCDLen++)
                {
                    if (strTargetBarcode[nBCDLen] == '*')  // 아무거나
                    {

                    }
                    else if (strTargetBarcode[nBCDLen] == '@')   // 영문자
                    {
                        if (readBarcode[nBCDLen] < 0x41 || readBarcode[nBCDLen] > 0x7A)
                        {
                            return false;
                        }
                    }
                    else if (strTargetBarcode[nBCDLen] == '#')   // 숫자
                    {
                        if (readBarcode[nBCDLen] < 0x30 || readBarcode[nBCDLen] > 0x39)
                        {
                            return false;
                        }
                    }
                    else
                    {
                        if (strTargetBarcode[nBCDLen] != readBarcode[nBCDLen]) // 그외 경우 일치하지 않으면 NG
                        {
                            return false;
                        }
                    }
                }

            }

            return true;
        }

        // CMA 중복정보 체크
        static bool CheckCMABcdDuplicate(string strBCD)
        {
            bool bResult = true;

            string strSaveFolderPath = String.Format(@"Duplicate\\CMA\\");
            DirectoryInfo Savedir = new DirectoryInfo(strSaveFolderPath);
            if (Savedir.Exists == false) { Savedir.Create(); }

            string strSaveFilePath = String.Format(@"{0}{1}.txt", strSaveFolderPath, strBCD);
            FileInfo _file = new FileInfo(strSaveFilePath);

            try
            {
                bResult = _file.Exists;
            }
            catch { bResult = true; }

            return bResult;

        }



        // 하이팟 중복정보 저장
        static void SaveHipotBcdDuplicate(string strBCD)
        {
            // Hipot 중복 생성
            string strSaveFolderPath = String.Format(@"Duplicate\\HIPOT\\");
            DirectoryInfo Savedir = new DirectoryInfo(strSaveFolderPath);
            if (Savedir.Exists == false) { Savedir.Create(); }

            string strSaveFilePath = String.Format(@"{0}{1}.txt", strSaveFolderPath, strBCD);
            File.WriteAllText(strSaveFilePath, "");

            // 저장하면서 오래된 파일 삭제
            string[] files = Directory.GetFiles(strSaveFolderPath);

            foreach (string file in files)
            {
                FileInfo fi = new FileInfo(file);
                if (fi.LastAccessTime < DateTime.Now.AddMonths(-1))
                    fi.Delete();
            }
        }

        static bool CheckHipotBcdDuplicate(string strBCD)
        {

            string strSaveFolderPath = String.Format(@"Duplicate\\HIPOT\\");
            DirectoryInfo Savedir = new DirectoryInfo(strSaveFolderPath);
            if (Savedir.Exists == false) { Savedir.Create(); }

            string strSaveFilePath = String.Format(@"{0}{1}.txt", strSaveFolderPath, strBCD);
            FileInfo _file = new FileInfo(strSaveFilePath);

            return _file.Exists;            // 파일 존재여부 확인

        }

       // Lot Barcode 출력
        public static string GetPrintLotBarcode(int nLotCount)
        {

            string strLot = "";


            // Gen3타입 바코드를 사용하는 경우 홀수는 A추가, 짝수는 B추가 // nUseResuGen3TypeBCDPrint
            if (_ModelInfo.bUseResuGen3TypeBCDPrint)
            {
                if (nLotCount % 2 == 0)
                {
                    // 짝수 팩일경우 B출력
                    if (_ModelInfo.bUnUseLineSymbol)
                    {
                        strLot = _LotCount.tLotClearTime.ToString("yyMMdd") + (nLotCount + _ModelInfo.nStartLotNum).ToString("D4") + "B";
                    }
                    else
                    {
                        strLot = _LotCount.tLotClearTime.ToString("yyMMdd") + _ModelInfo.strBCDSymbol + (nLotCount + _ModelInfo.nStartLotNum).ToString("D3") + "B";
                    }
                }
                else
                {
                    // 홀수 팩일경우 A출력
                    if (_ModelInfo.bUnUseLineSymbol)
                    {
                        strLot = _LotCount.tLotClearTime.ToString("yyMMdd") + (nLotCount + _ModelInfo.nStartLotNum).ToString("D4") + "A";
                    }
                    else
                    {
                        strLot = _LotCount.tLotClearTime.ToString("yyMMdd") + _ModelInfo.strBCDSymbol + (nLotCount + _ModelInfo.nStartLotNum).ToString("D3") + "A";
                    }
                }
            }
            else if (_ModelInfo.bUseOmronGen3TypeBCDPrint)
            {
                if (nLotCount % 2 == 0)
                {
                    // 홀수 팩일경우 B출력
                    if (_ModelInfo.bUnUseLineSymbol)
                    {
                        strLot = _LotCount.tLotClearTime.ToString("yyMMdd") + (_ModelInfo.nStartLotNum + ((nLotCount + 1) / 2)).ToString("D4") + "B";
                    }
                    else
                    {
                        strLot = _LotCount.tLotClearTime.ToString("yyMMdd") + _ModelInfo.strBCDSymbol + (_ModelInfo.nStartLotNum + ((nLotCount + 1) / 2)).ToString("D3") + "B";
                    }
                }
                else
                {
                    // 홀수 팩일경우 A출력
                    if (_ModelInfo.bUnUseLineSymbol)
                    {
                        strLot = _LotCount.tLotClearTime.ToString("yyMMdd") + (_ModelInfo.nStartLotNum + ((nLotCount + 1) / 2)).ToString("D4") + "A";
                    }
                    else
                    {
                        strLot = _LotCount.tLotClearTime.ToString("yyMMdd") + _ModelInfo.strBCDSymbol + (_ModelInfo.nStartLotNum + ((nLotCount + 1) / 2)).ToString("D3") + "A";
                    }
                }
            }
            else if (_ModelInfo.bUseOmronGen3Type150BCDPrint)
            {
                if (nLotCount % 2 == 0)
                {
                    // 홀수 팩일경우 B출력
                    if (_ModelInfo.bUnUseLineSymbol)
                    {
                        strLot = _LotCount.tLotClearTime.ToString("yyMMdd") + (_ModelInfo.nStartLotNum + ((nLotCount + 1) / 2)).ToString("D4") + "D";
                    }
                    else
                    {
                        strLot = _LotCount.tLotClearTime.ToString("yyMMdd") + _ModelInfo.strBCDSymbol + (_ModelInfo.nStartLotNum + ((nLotCount + 1) / 2)).ToString("D3") + "D";
                    }
                }
                else
                {
                    // 홀수 팩일경우 A출력
                    if (_ModelInfo.bUnUseLineSymbol)
                    {
                        strLot = _LotCount.tLotClearTime.ToString("yyMMdd") + (_ModelInfo.nStartLotNum + ((nLotCount + 1) / 2)).ToString("D4") + "C";
                    }
                    else
                    {
                        strLot = _LotCount.tLotClearTime.ToString("yyMMdd") + _ModelInfo.strBCDSymbol + (_ModelInfo.nStartLotNum + ((nLotCount + 1) / 2)).ToString("D3") + "C";
                    }
                }
            }
            else if (_ModelInfo.bUseSharpPrint)
            {
                //strLot = _ModelInfo.strBCDSymbol; // 라인구분자 삭제
                strLot = "";
                strLot += (char)(0x41 + _LotCount.tLotClearTime.Year - 2017);
                string[] strMData = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "X", "Y", "Z" };
                strLot += strMData[_LotCount.tLotClearTime.Month - 1];
                strLot += _LotCount.tLotClearTime.ToString("dd");
                strLot += String.Format("{0:D3}", nLotCount + _ModelInfo.nStartLotNum);
            }
            else if (_ModelInfo.bUseXYZPrint)
            {
                //
                string[] strMData = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "X", "Y", "Z" };
                strLot = _LotCount.tLotClearTime.ToString("yyyy");
                strLot += strMData[_LotCount.tLotClearTime.Month - 1];
                strLot += _LotCount.tLotClearTime.ToString("dd");
                if (_ModelInfo.bUnUseLineSymbol)
                {
                    strLot += String.Format("{0:D4}", nLotCount + _ModelInfo.nStartLotNum);
                }
                else
                {
                    strLot += _ModelInfo.strBCDSymbol + String.Format("{0:D3}", nLotCount + _ModelInfo.nStartLotNum);
                }


            }
            else if (_ModelInfo.bUseCmaBizBCD)
            {
                strLot = _LotCount.tLotClearTime.ToString("yyMMdd") + _ModelInfo.strComment3 + _ModelInfo.strBCDSymbol + (_ModelInfo.nStartLotNum + nLotCount).ToString("D3");
            }
            else
            {
                if (_ModelInfo.bUnUseLineSymbol)
                {
                    strLot = _LotCount.tLotClearTime.ToString("yyMMdd") + String.Format("{0:D4}", _LotCount.nLotCount + _ModelInfo.nStartLotNum);
                }
                else
                {
                    strLot = _LotCount.tLotClearTime.ToString("yyMMdd") + _ModelInfo.strBCDSymbol + (_ModelInfo.nStartLotNum + nLotCount).ToString("D3");
                }
            }


            return strLot;
        }


        //===========================================================
        //====== 바코드 리딩 프로세스 ===============================
        static void SUB_BARCODE_READ()
        {

            int nStepIndex = (int)PROC_LIST.BARCODE_READ;
              if (_Config.bReWorkMode)
              {
                  _SysInfo.nReworkCount = _ReadBCDList.Count(str => str.strCate == "REWORK");
              
                  if (_SysInfo.nReworkCount >= 1)
                  {
                      _SysInfo.bBCDReadAllOk = true;
                  }
                  else
                  {
                      _SysInfo.bBCDReadAllOk = false;
                  }
              }
              else
              {


                try
                {

                    _SysInfo.nCmaCount = _ReadBCDList.Count(str => str.strCate == "CMA");
                    _SysInfo.nBmsCount = _ReadBCDList.Count(str => str.strCate == "BMS");
                    _SysInfo.nRearCount = _ReadBCDList.Count(str => str.strCate == "REAR");
                    _SysInfo.nPreWorkCount = _ReadBCDList.Count(str => str.strCate == "PREWORK");
                    //_SysInfo.nCmaCount = _dtBCDInfo.Select("[Type] = 'CMA'").Count();
                    //_SysInfo.nBmsCount = _dtBCDInfo.Select("[Type] = 'BMS'").Count();
                    //_SysInfo.nFuseCount = _dtBCDInfo.Select("[항목] = 'FUSE'").Count();
                }
                catch { }

                if (_SysInfo.nCmaCount >= _ModelInfo.nCmaCount &&
                    _SysInfo.nBmsCount >= _ModelInfo.nBmsCount &&
                    _SysInfo.nPreWorkCount >= _ModelInfo.nPreWorkCount)
                {
                    _SysInfo.bBCDReadAllOk = true;
                }
                else
                {
                    _SysInfo.bBCDReadAllOk = false;
                }

            }
            _SysInfo.bBCDCMAReadOk = (_SysInfo.nCmaCount >= _ModelInfo.nCmaCount);
            _SysInfo.bBCDBMSReadOk = (_SysInfo.nBmsCount >= _ModelInfo.nBmsCount);



            switch (nProcessStep[nStepIndex])
            {
                case 0:
                    _BCDReader.bReadOk = false;
                    nProcessStep[nStepIndex]++;
                    break;

                case 1:
                    if (_BCDReader.bReadOk)
                    {
                        _SysInfo.bBCDAddFlag = false;
                        _BCDReader.bReadOk = false;
                        _SysInfo.bPalletBCDReadOK = false;
                        _SysInfo.strReadBCDData = _BCDReader.strReadBarcode;

                        if (_ModelInfo.bUsePalletBarcode)
                        {
                            for (int i = 0; i < 20; i++)
                            {
                                // 파레트 바코드와 일치하는 경우
                                if (_SysInfo.strReadBCDData == _Config.strPalletBCD[i])
                                {
                                    _SysInfo.bPalletBCDReadOK = true;                       // 파레트 바코드가 들어온 경우 True
                                    if (_SysInfo.nCmaCount >= _ModelInfo.nCmaCount)         // ?????
                                    {
                                        AppendLogMsg("CMA 스캔 개수를 초과 하였습니다.", LOG_TYPE.ERROR);
                                        _SysInfo.nTL_Beep = 2;
                                        nProcessStep[nStepIndex] = 0;
                                    }
                                    else
                                    {
                                        _SysInfo.strReadPalletBCD = _SysInfo.strReadBCDData;
                                        LoadPalletBCDListInfo(_SysInfo.strReadBCDData);
                                        SaveBCDListInfo();
                                        _mainform.BeginInvoke(new Action(() => _mainform.UpdateBCDGridStyle()));
                                        _SysInfo.bBCDAddFlag = true;
                                        nProcessStep[nStepIndex] = 4;
                                    }
                                    break;
                                }
                            }
                        }

                        if (_ModelInfo.bUsePalletBarcode && _SysInfo.bPalletBCDReadOK) { break; }           // Pallet 바코드가 읽혔다면 아래 리딩 스텝은 Pass 한다

                        //// 리워크 바코드 스캔 기능
                        //if (_SysInfo.bBCDReadAllOk && _Config.bUseReWorkTypeBCDScan)
                        //{
                        //    if (_SysInfo.strReadBCDData.Substring(0, Math.Min(_SysInfo.strReadBCDData.Length, _ModelInfo.strComment1.Length)) == _ModelInfo.strComment1)
                        //    {
                        //        _SysInfo.strReWorkBCD = _SysInfo.strReadBCDData;
                        //        nProcessStep[nStepIndex] = 6;
                        //        break;
                        //    }
                        //}

                        /////////// 리워크 바코드 스캔 기능
                        if (_SysInfo.bBCDReadAllOk && _ModelInfo.bUseScanSTTester)
                        {
                            if (_SysInfo.strReadBCDData.Substring(0, Math.Min(_SysInfo.strReadBCDData.Length, _ModelInfo.strComment1.Length)) == _ModelInfo.strComment1)
                            {
                                nProcessStep[nStepIndex] = 20;
                            }
                            else
                            {
                                AppendLogMsg("정상적인 바코드가 아닙니다.", LOG_TYPE.ERROR);
                                _SysInfo.nTL_Beep = 2;
                                nProcessStep[nStepIndex] = 0;
                            }
                        }
                        else
                        {
                            nProcessStep[nStepIndex]++;
                        }


                    }
                    break;

                case 2:
                    //int nCount = 0;
                    //try { nCount = _dtBCDInfo.Select(String.Format("[Barcode] = '{0}'", _SysInfo.strReadBCDData)).Count(); }
                    //catch { nCount = 0; }

                    if (/*nCount*/ _ReadBCDList.Count(str => str.strBCD == _SysInfo.strReadBCDData) != 0)
                    {
                        if (_Config.strLangue == "KOR") { AppendLogMsg(String.Format("CMA 중복 바코드 입니다."), LOG_TYPE.ERROR); }
                        else { AppendLogMsg(String.Format("CMA 重复条形码。"), LOG_TYPE.ERROR); }
                        _SysInfo.nTL_Beep = 2;

                        nProcessStep[nStepIndex] = 0;
                        break;
                    }
                    else
                    {
                        //if (CheckCMABcdDuplicate(_SysInfo.strReadBCDData))
                        //{

                        //    if (_Config.strLangue == "KOR") { AppendLogMsg(String.Format("CMA 중복 바코드 입니다."), LOG_TYPE.ERROR); }
                        //    else { AppendLogMsg(String.Format("CMA 重复条形码。"), LOG_TYPE.ERROR); }
                        //    _SysInfo.nTL_Beep = 2;

                        //    nProcessStep[nStepIndex] = 0;
                        //    break;
                        //}
                        //else
                        //{
                        nProcessStep[nStepIndex]++;
                        //}

                    }
                    break;

                case 3:
                    // CMA 일경우
                    _SysInfo.bBCDAddFlag = false;

                    // 리웤 모드일경우
                    if (_Config.bReWorkMode)
                    {
                        if (_SysInfo.strReadBCDData.Substring(0, Math.Min(_SysInfo.strReadBCDData.Length, _ModelInfo.strComment1.Length)) == _ModelInfo.strComment1)
                        {
                            if (_SysInfo.nReworkCount >= 1)
                            {
                                AppendLogMsg("Scan Count Over.", LOG_TYPE.ERROR);
                                nProcessStep[nStepIndex] = 0;
                                _SysInfo.nTL_Beep = 2;
                                break;
                            }
                            else
                            {
                                _ReadBCDList.Add(new _ReadBarcodeData() { strBCD = _SysInfo.strReadBCDData, strCate = "REWORK" });

                                SaveBCDListInfo();
                                _mainform.BeginInvoke(new Action(() => _mainform.UpdateBCDGridStyle()));
                                nProcessStep[nStepIndex] = 5;
                                break;
                            }
                        }
                        else
                        {
                            AppendLogMsg("MODEL TYPE ERR.", LOG_TYPE.ERROR);
                            _SysInfo.nTL_Beep = 2;
                            break;
                        }
                    }

                    //// 바코드 스캔 인터록 2018. 11. 26  피플 정부장님 요청
                    //if (_SysInfo.nCmaCount == 0 || _SysInfo.strCompareBCD == "")
                    //{
                    //    string[] strSplitBCD = _ModelInfo.strCmaSymbol.Split(',');
                    
                    //    // 기본정보는 Index 0번으로 설정
                    //    _SysInfo.strCompareBCD = strSplitBCD[0];
                    
                    //    // 추가 비교후 Index에 따른 할당
                    //    for (int i = 0; i < strSplitBCD.Length; i++)
                    //    {
                    //        if (_SysInfo.strReadBCDData.Substring(0, Math.Min(_SysInfo.strReadBCDData.Length, strSplitBCD[i].Length)) == strSplitBCD[i])
                    //        {
                    //            _SysInfo.strCompareBCD = strSplitBCD[i];
                    //        }
                    //    }
                    //}

                    // 해당 부분 변경

                    //if (_SysInfo.strReadBCDData.Substring(0, Math.Min(_SysInfo.strReadBCDData.Length, _SysInfo.strCompareBCD.Length)) == _SysInfo.strCompareBCD)
                    if (CheckBarcode(_SysInfo.strReadBCDData, _ModelInfo.strCmaSymbol))
                    {
                        if (CheckCMABcdDuplicate(_SysInfo.strReadBCDData))
                        {

                            if (_Config.strLangue == "KOR") { AppendLogMsg(String.Format("CMA 중복 바코드 입니다."), LOG_TYPE.ERROR); }
                            else { AppendLogMsg(String.Format("CMA 重复条形码。"), LOG_TYPE.ERROR); }
                            _SysInfo.nTL_Beep = 2;

                            nProcessStep[nStepIndex] = 0;
                            break;
                        }

                        //if (_SysInfo.nCmaCount == 0 && _Config.bUseReWorkTypeBCDScan)
                        //{
                        //    // 첫 CMA 이고 리워크 타입 바코드 스캔을 사용한다면

                        //    DateTime.TryParseExact(_SysInfo.strReadBCDData.Substring(_ModelInfo.nCMAStartIndex, 6),
                        //          "yyMMdd",
                        //          CultureInfo.InvariantCulture,
                        //          DateTimeStyles.None,
                        //          out _DtCMATarget);
                        //}
                        if (_SysInfo.nCmaCount >= _ModelInfo.nCmaCount)         // ?????
                        {
                            AppendLogMsg("CMA 스캔 개수를 초과 하였습니다.", LOG_TYPE.ERROR);
                            _SysInfo.nTL_Beep = 2;
                        }
                        else
                        {
                            if (_Config.bUseCMAStatusCheck)
                            {
                                if (CheckCMAStatus(_SysInfo.strReadBCDData) == "OK")
                                {
                                    _SysInfo.bBCDAddFlag = true;
                                    _ReadBCDList.Add(new _ReadBarcodeData() { strBCD = _SysInfo.strReadBCDData, strCate = "CMA" });
                                    SaveBCDListInfo();
                                    _mainform.BeginInvoke(new Action(() => _mainform.UpdateBCDGridStyle()));
                                    //_dtBCDInfo.Rows.Add(_SysInfo.strReadBCDData, "CMA");
                                    //SaveBCDInfoTable();
                                }
                                else if (CheckCMAStatus(_SysInfo.strReadBCDData) == "NG")
                                {
                                    AppendLogMsg("CMA 검사 불량 제품 입니다.", LOG_TYPE.ERROR);
                                    _SysInfo.nTL_Beep = 2;
                                }
                                else if (CheckCMAStatus(_SysInfo.strReadBCDData) == "NOFILE")
                                {
                                    AppendLogMsg("CMA 검사 정보가 없습니다.", LOG_TYPE.ERROR);
                                    _SysInfo.nTL_Beep = 2;
                                }
                                else
                                {
                                    AppendLogMsg("CMA 검사 정보가 정확하지 않습니다.", LOG_TYPE.ERROR);
                                    _SysInfo.nTL_Beep = 2;
                                }
                            }
                            else if (_NgDataList.Exists(x => x == _SysInfo.strReadBCDData))
                            {
                                AppendLogMsg("불량 CMA 입니다.", LOG_TYPE.ERROR);
                                _SysInfo.nTL_Beep = 2;
                            }
                            else
                            {
                                //if (_Config.bUseReWorkTypeBCDScan)
                                //{
                                //    DateTime _DtTemp = new DateTime();

                                //    DateTime.TryParseExact(_SysInfo.strReadBCDData.Substring(_ModelInfo.nCMAStartIndex, 6),
                                //            "yyMMdd",
                                //            CultureInfo.InvariantCulture,
                                //            DateTimeStyles.None,
                                //            out _DtTemp);

                                //    TimeSpan _TsTemp = _DtCMATarget - _DtTemp;


                                //    if (Math.Abs(_TsTemp.Days) > _ModelInfo.nTimeLimit)
                                //    {
                                //        AppendLogMsg("CMA 날자 NG 제품입니다.", LOG_TYPE.ERROR);
                                //        _SysInfo.nTL_Beep = 2;
                                //    }
                                //    else
                                //    {
                                //        _SysInfo.bBCDAddFlag = true;

                                //        _ReadBCDList.Add(new _ReadBarcodeData() { strBCD = _SysInfo.strReadBCDData, strCate = "CMA" });
                                //        SaveBCDListInfo();
                                //        _mainform.BeginInvoke(new Action(() => _mainform.UpdateBCDGridStyle()));
                                //        //_dtBCDInfo.Rows.Add(_SysInfo.strReadBCDData, "CMA");
                                //        //_dtBCDInfo.AcceptChanges();

                                //        //SaveBCDInfoTable();
                                //    }
                                //}
                                //else
                                //{
                                //    _SysInfo.bBCDAddFlag = true;

                                //    _ReadBCDList.Add(new _ReadBarcodeData() { strBCD = _SysInfo.strReadBCDData, strCate = "CMA" });
                                //    SaveBCDListInfo();
                                //    _mainform.BeginInvoke(new Action(() => _mainform.UpdateBCDGridStyle()));

                                //    // CMA 중복 데이터 저장




                                //    //_dtBCDInfo.Rows.Add(_SysInfo.strReadBCDData, "CMA");
                                //    //_dtBCDInfo.AcceptChanges();
                                //    //SaveBCDInfoTable();
                                //}

                                _SysInfo.bBCDAddFlag = true;

                                _ReadBCDList.Add(new _ReadBarcodeData() { strBCD = _SysInfo.strReadBCDData, strCate = "CMA" });
                                SaveBCDListInfo();
                                _mainform.BeginInvoke(new Action(() => _mainform.UpdateBCDGridStyle()));
                                //_dtBCDInfo.Rows.Add(_SysInfo.strReadBCDData, "CMA");
                                //_dtBCDInfo.AcceptChanges();

                                //SaveBCDInfoTable();

                            }
                        }
                    }
                    // BMS 일 경우
                    //else if (_SysInfo.strReadBCDData.Substring(0, Math.Min(_SysInfo.strReadBCDData.Length, _ModelInfo.strBmsSymbol.Length)) == _ModelInfo.strBmsSymbol)
                    //else if (CheckBarcode(_SysInfo.strReadBCDData, _ModelInfo.strBmsSymbol))
                    else if (_ModelInfo.nBmsCount  > 0 && CheckBarcode(_SysInfo.strReadBCDData, _ModelInfo.strBmsSymbol))
                    {
                        if (_SysInfo.nBmsCount >= _ModelInfo.nBmsCount)
                        {
                            AppendLogMsg("BMS 스캔 개수를 초과 하였습니다.", LOG_TYPE.ERROR);
                            _SysInfo.nTL_Beep = 2;
                        }
                        else
                        {
                            _SysInfo.bBCDAddFlag = true;
                            _ReadBCDList.Add(new _ReadBarcodeData() { strBCD = _SysInfo.strReadBCDData, strCate = "BMS" });
                            SaveBCDListInfo();
                            _mainform.BeginInvoke(new Action(() => _mainform.UpdateBCDGridStyle()));
                            //_dtBCDInfo.Rows.Add(_SysInfo.strReadBCDData, "BMS");
                            //_dtBCDInfo.AcceptChanges();
                            //SaveBCDInfoTable();
                        }
                    }
                    else if (_ModelInfo.nPreWorkCount > 0 && CheckBarcode(_SysInfo.strReadBCDData, _ModelInfo.strPreWorkSymbol))
                    {
                        if (_SysInfo.nPreWorkCount >= _ModelInfo.nPreWorkCount)
                        {
                            AppendLogMsg("PRE WORK 스캔 개수를 초과 하였습니다.", LOG_TYPE.ERROR);
                            _SysInfo.nTL_Beep = 2;
                        }
                        else
                        {
                            _SysInfo.bBCDAddFlag = true;
                            _ReadBCDList.Add(new _ReadBarcodeData() { strBCD = _SysInfo.strReadBCDData, strCate = "PREWORK" });
                            SaveBCDListInfo();
                            _mainform.BeginInvoke(new Action(() => _mainform.UpdateBCDGridStyle()));
                            //_dtBCDInfo.Rows.Add(_SysInfo.strReadBCDData, "BMS");
                            //_dtBCDInfo.AcceptChanges();
                            //SaveBCDInfoTable();
                        }
                    }

                    //else if (_SysInfo.strReadBCDData.Substring(0, Math.Min(_SysInfo.strReadBCDData.Length, _ModelInfo.strETC4BCD.Length)) == _ModelInfo.strETC4BCD)
                    //{
                    //    _SysInfo.bETCScan4 = true;
                    //}
                    //else if (_SysInfo.strReadBCDData.Substring(0, Math.Min(_SysInfo.strReadBCDData.Length, _ModelInfo.strETC5BCD.Length)) == _ModelInfo.strETC5BCD)
                    //{
                    //    if (_SysInfo.nRearCount >= _ModelInfo.nUseETC5BCDCount)
                    //    {
                    //        AppendLogMsg("Rear Support Plate 스캔 개수를 초과 하였습니다.", LOG_TYPE.ERROR);
                    //        _SysInfo.nTL_Beep = 2;
                    //    }
                    //    else
                    //    {
                    //        _ReadBCDList.Add(new _ReadBarcodeData() { strBCD = _SysInfo.strReadBCDData, strCate = "REAR" });
                    //        SaveBCDListInfo();
                    //        _mainform.BeginInvoke(new Action(() => _mainform.UpdateBCDGridStyle()));
                    //    }

                    //}
                    else if (_ModelInfo._EtcDataScan[0].CheckBarcode(_SysInfo.strReadBCDData))
                    {
                        // 바코드 일치의 경우
                    }
                    // 퓨즈 일경우
                    //else if (_SysInfo.strReadBCDData.Substring(0, Math.Min(_SysInfo.strReadBCDData.Length, _ModelInfo.strFuseSymbol.Length)) == _ModelInfo.strFuseSymbol)
                    //{
                    //    if (_SysInfo.nFuseCount >= _ModelInfo.nFuseCount)
                    //    {
                    //        AppendLogMsg("FUSE 스캔 개수를 초과 하였습니다.", Color.Red);
                    //        _SysInfo.nTL_Beep = 2;
                    //    }
                    //    else
                    //    {
                    //        _SysInfo.bBCDAddFlag = true;
                    //        _dtBCDInfo.Rows.Add(_SysInfo.strReadBCDData, "FUSE");
                    //        _dtBCDInfo.AcceptChanges();
                    //        SaveBCDInfoTable();
                    //    }
                    //}
                    else
                    {
                        AppendLogMsg("정상적인 바코드가 아닙니다.", LOG_TYPE.ERROR);
                        _SysInfo.nTL_Beep = 2;
                    }
                    nProcessStep[nStepIndex]++;
                    break;

                case 4:
                    if (_SysInfo.nCmaCount >= _ModelInfo.nCmaCount &&
                        _SysInfo.nBmsCount >= _ModelInfo.nBmsCount &&
                        _SysInfo.nPreWorkCount >= _ModelInfo.nPreWorkCount &&
                        /*_SysInfo.nFuseCount >= _ModelInfo.nFuseCount &&*/ _SysInfo.bBCDAddFlag)
                    {
                        _SysInfo.bBCDAddFlag = false;
                        nProcessStep[nStepIndex]++;
                    }
                    else
                    {
                        nProcessStep[nStepIndex] = 0;
                    }
                    break;

                case 5:
                    // 기존 카운터 
                    //_ModelInfo.nLotCount++;
                    //_ModelInfo.nProductCount++;
                    //

                    // 신규 카운터
                    _LotCount.nLotCount++;
                    _LotCount.nProductCount++;
                    SaveModelProductCount(_ModelInfo.strModelName);
                    //

                    _Count.nTotalCount++;
                    SaveProductCount();
                    //SaveModelInfo(_ModelInfo, _ModelInfo.strModelName);


                    //if (_Config.bUseReWorkTypeBCDScan)
                    //{
                    //    nProcessStep[nStepIndex] = 0;
                    //    break;
                    //}

                    //if (!_ModelInfo.bUseSharpPrint)
                    //{

                    //    _BCDPrint.strModelInfo = _ModelInfo.strComment1 + _ModelInfo.strComment3;

                    //    if (_ModelInfo.bUnUseLineSymbol)
                    //    {
                    //        if (_ModelInfo.bUseXYZPrint)
                    //        {
                    //            //
                    //            string[] strMData = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "X", "Y", "Z" };
                    //            _BCDPrint.strPrintBCD = _LotCount.tLotClearTime.ToString("yyyy");
                    //            _BCDPrint.strPrintBCD += strMData[_LotCount.tLotClearTime.Month - 1];
                    //            _BCDPrint.strPrintBCD += _LotCount.tLotClearTime.ToString("dd");
                    //            _BCDPrint.strPrintBCD += String.Format("{0:D4}", _LotCount.nLotCount + _Config.nStartLotNum);
                    //        }
                    //        else
                    //        {
                    //            _BCDPrint.strPrintBCD = _LotCount.tLotClearTime.ToString("yyMMdd") + String.Format("{0:D4}", _LotCount.nLotCount + _Config.nStartLotNum);
                    //        }
                    //    }
                    //    else
                    //    {
                    //        if (_ModelInfo.bUseXYZPrint)
                    //        {
                    //            string[] strMData = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "X", "Y", "Z" };

                    //            _BCDPrint.strPrintBCD = _LotCount.tLotClearTime.ToString("yyyy");
                    //            _BCDPrint.strPrintBCD += strMData[_LotCount.tLotClearTime.Month - 1];
                    //            _BCDPrint.strPrintBCD += _LotCount.tLotClearTime.ToString("dd");
                    //            _BCDPrint.strPrintBCD += _ModelInfo.strBCDSymbol;
                    //            _BCDPrint.strPrintBCD += String.Format("{0:D3}", _LotCount.nLotCount + _Config.nStartLotNum);
                    //        }
                    //        else
                    //        {
                    //            _BCDPrint.strPrintBCD = _LotCount.tLotClearTime.ToString("yyMMdd") + _ModelInfo.strBCDSymbol + String.Format("{0:D3}", _LotCount.nLotCount + _Config.nStartLotNum);
                    //        }

                    //    }

                    //}
                    //else
                    //{

                    //    _BCDPrint.strModelInfo = _ModelInfo.strComment1 + _ModelInfo.strComment3;
                    //    _BCDPrint.strPrintBCD = _ModelInfo.strBCDSymbol;
                    //    _BCDPrint.strPrintBCD += (char)(0x41 + _LotCount.tLotClearTime.Year - 2017);
                    //    string[] strMData = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "X", "Y", "Z" };
                    //    _BCDPrint.strPrintBCD += strMData[_LotCount.tLotClearTime.Month - 1];
                    //    _BCDPrint.strPrintBCD += _LotCount.tLotClearTime.ToString("dd");
                    //    _BCDPrint.strPrintBCD += String.Format("{0:D3}", _LotCount.nLotCount + _Config.nStartLotNum);





                    //}

                    if(_ModelInfo.bUseCmaBizBCD || _ModelInfo.bUseSharpPrint)
                    {
                        _BCDPrint.strModelInfo = "";
                    }
                    else
                    {
                        _BCDPrint.strModelInfo = _ModelInfo.strComment1 + _ModelInfo.strComment3;
                    }
                    
                    _BCDPrint.strPrintBCD = GetPrintLotBarcode(_LotCount.nLotCount);

                    nProcessStep[nStepIndex]++;
                    break;

                case 6:
                    _BCDPrint.bManualMode = false;
                    _BCDPrint.bPrintStart = true;
                    SaveBarcodeInfo();
                    _SysInfo.bReworkScanFinish = true;
                    if (_Config.bUseReWorkTypeBCDScan)
                    {
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }

                    //SaveduplicationCode();        상구대리 요청 CMA 중복체크 저장 해제
                    SaveCMABcdDuplicate();          // 신형타입 추가
                    if (_ModelInfo.bUsePalletBarcode)
                    {
                        AppendLogMsg(String.Format("PID : {0} , BMA ID : {1}{2}", _SysInfo.strReadPalletBCD, _BCDPrint.strModelInfo, _BCDPrint.strPrintBCD), LOG_TYPE.INFO);
                        DelPalletBCDListInfo(_SysInfo.strReadPalletBCD);
                    }
                    _SysInfo.nNowPrintCount++;
                    tMainTimer[nStepIndex].Start(5000);
                    nProcessStep[nStepIndex]++;
                    break;

                case 7:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 0;
                    }

                    if (_BCDPrint.bPrintFail || _BCDPrint.bPrintOk)
                    {
                        if (_BCDPrint.bPrintFail)
                        {
                            _BCDPrint.bPrintFail = false;
                            AppendLogMsg("출력 실패", LOG_TYPE.ERROR);

                            if (_BCDPrint.bPrintHeadUp)
                            {
                                AppendLogMsg("헤드 열림", LOG_TYPE.ERROR);
                            }

                            if (_BCDPrint.bPrintPasue)
                            {
                                AppendLogMsg("일시 정지", LOG_TYPE.ERROR);
                            }
                            if (_BCDPrint.bPrintRibonErr)
                            {
                                AppendLogMsg("리본 없음", LOG_TYPE.ERROR);
                            }

                            if (_BCDPrint.bPrintPaperEmpty)
                            {
                                AppendLogMsg("용지 없음", LOG_TYPE.ERROR);
                            }
                            _SysInfo.nTL_Beep = 2;
                            nProcessStep[nStepIndex] = 0;
                        }

                        if (_BCDPrint.bPrintOk)
                        {
                            if (_SysInfo.nNowPrintCount >= _ModelInfo.nBCDPrintCount)
                            {
                                _SysInfo.nNowPrintCount = 0;
                                _BCDPrint.bPrintOk = false;
                                nProcessStep[nStepIndex] = 0;
                            }
                            else
                            {
                                _BCDPrint.bPrintOk = false;
                                nProcessStep[nStepIndex] = 6;
                            }
                        }
                    }
                    break;


                // 바코드 스캔 완료시 검사 시작 프로세스
                case 20:
                    _BatteryTester2._Status = BatteryTesterStat.READY;
                    _BatteryTester2.strSendBcd = _SysInfo.strReadBCDData;
                    _BatteryTester2.bRequest = false;
                    _BatteryTester2.bStart = true;
                    _BatteryTester2.nCurrentStep = 0;
                    tMainTimer[nStepIndex].Start(2000);
                    nProcessStep[nStepIndex]++;
                    break;

                case 21:
                    if (_SysInfo.bAutoCycleStop)
                    {
                        _BatteryTester2.bRequest = false;
                        _BatteryTester2.bStop = true;
                        _BatteryTester2.nCurrentStep = 0;
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }

                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("충방전 시험기가 응답하지 않습니다...", LOG_TYPE.ERROR);
                        _SysInfo.nTL_Beep = 2;
                        nProcessStep[nStepIndex] = 0;
                    }

                    if (_BatteryTester2.bRequest)
                    {
                        if (_BatteryTester2._Status == BatteryTesterStat.START)
                        {
                            // 정상적으로 시작했을시 양불 대기스텝으로 이동
                            _BatteryTester2.bRequest = false;
                            _BatteryTester2.bCheckOkng = true;
                            _BatteryTester2.nCurrentStep = 0;
                            nProcessStep[nStepIndex] = 30;
                        }
                        else if (_BatteryTester2._Status == BatteryTesterStat.ING)
                        {
                            // 검사 중이라면 해당 작업 정지 시키고 재시작함
                            nProcessStep[nStepIndex]++;
                        }
                    }
                    break;


                case 22:
                    _BatteryTester2.bRequest = false;
                    _BatteryTester2.bStop = true;
                    _BatteryTester2.nCurrentStep = 0;
                    nProcessStep[nStepIndex]++;
                    break;

                case 23:
                    if (_SysInfo.bAutoCycleStop)
                    {
                        _BatteryTester2.bRequest = false;
                        _BatteryTester2.bStop = true;
                        _BatteryTester2.nCurrentStep = 0;
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }

                    if (_BatteryTester2.bRequest)
                    {
                        if (_BatteryTester2._Status == BatteryTesterStat.END)
                        {
                            // 정지 신호가 온다면 시작
                            nProcessStep[nStepIndex]++;
                        }
                    }
                    break;


                case 24:
                    _BatteryTester2._Status = BatteryTesterStat.READY;
                    _BatteryTester2.strSendBcd = _SysInfo.strReadBCDData;
                    _BatteryTester2.bRequest = false;
                    _BatteryTester2.bStart = true;
                    _BatteryTester2.nCurrentStep = 0;
                    tMainTimer[nStepIndex].Start(2000);
                    nProcessStep[nStepIndex]++;
                    break;


                case 25:
                    if (_SysInfo.bAutoCycleStop)
                    {
                        _BatteryTester2.bRequest = false;
                        _BatteryTester2.bStop = true;
                        _BatteryTester2.nCurrentStep = 0;
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }

                    if (tMainTimer[nStepIndex].Verify())
                    {
                        AppendLogMsg("충방전 시험기가 응답하지 않습니다...", LOG_TYPE.ERROR);
                        _SysInfo.nTL_Beep = 5;
                        nProcessStep[nStepIndex] = 0;
                    }

                    if (_BatteryTester2.bRequest)
                    {
                        if (_BatteryTester2._Status == BatteryTesterStat.START)
                        {
                            // 정상적으로 시작했을시 양불 대기스텝으로 이동
                            _BatteryTester2.bRequest = false;
                            _BatteryTester2.bCheckOkng = true;
                            _BatteryTester2.nCurrentStep = 0;
                            nProcessStep[nStepIndex] = 30;
                        }
                    }
                    break;

                case 30:
                    if (_SysInfo.bAutoCycleStop)
                    {
                        _BatteryTester2.bRequest = false;
                        _BatteryTester2.bStop = true;
                        _BatteryTester2.nCurrentStep = 0;
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }

                    if (_BatteryTester2._Status == BatteryTesterStat.OK)
                    {
                        // 양품일 경우
                        _SysInfo.bScanSTTesetFinish = true;
                        _SysInfo.bScanSTTesetOK = true;
                        _SysInfo.nTL_Beep = 2;
                        nProcessStep[nStepIndex] = 0;

                    }
                    else if (_BatteryTester2._Status == BatteryTesterStat.NG)
                    {
                        // 불량일 경우
                        _SysInfo.bScanSTTesetFinish = true;
                        _SysInfo.bScanSTTesetOK = false;

                        AppendLogMsg("충방전 불량!!", LOG_TYPE.ERROR);
                        _SysInfo.nTL_Beep = 5;
                        nProcessStep[nStepIndex] = 0;
                    }
                    break;
            }
        }



        //===========================================================
        //====== 바코드 리딩 프로세스 ===============================
        static void SUB_ST1_BARCODE_READ()
        {
            int nStepIndex = (int)PROC_LIST.SUB_ST1_BARCODE;
            try
            {

                _SysInfo.nST1CmaCount = _ST1BCDList.Count(str => str.strCate == "CMA");
                //_SysInfo.nBmsCount = _ReadBCDList.Count(str => str.strCate == "BMS");
                //_SysInfo.nCmaCount = _dtBCDInfo.Select("[Type] = 'CMA'").Count();
                //_SysInfo.nBmsCount = _dtBCDInfo.Select("[Type] = 'BMS'").Count();
                //_SysInfo.nFuseCount = _dtBCDInfo.Select("[항목] = 'FUSE'").Count();
            }
            catch { }

            if (_SysInfo.nST1CmaCount >= _ModelInfo.nCmaCount)
            {
                _SysInfo.bST1BCDReadAllOk = true;
            }
            else
            {
                _SysInfo.bST1BCDReadAllOk = false;
            }


            switch (nProcessStep[nStepIndex])
            {
                case 0:

                    _ST1Reader.bReadOk = false;
                    nProcessStep[nStepIndex]++;
                    break;

                case 1:
                    if (_ST1Reader.bReadOk)
                    {
                        _ST1Reader.bReadOk = false;
                        _SysInfo.strST1ReadBCDData = _ST1Reader.strReadBarcode;

                        if (_ModelInfo.bUsePalletBarcode)
                        {
                            for (int i = 0; i < 20; i++)
                            {
                                if (_SysInfo.strST1ReadBCDData == _Config.strPalletBCD[i])
                                {
                                    // 파레트 바코드가 인식된다면
                                    _SysInfo.strSt1ReadPalletBarcode = _SysInfo.strST1ReadBCDData;
                                    _SysInfo.bSt1ReadPalletBarcode = true;
                                    _ST1BCDList.Clear();
                                    nProcessStep[nStepIndex] = 0;
                                    break;
                                }
                            }
                        }

                        //// 리워크 바코드 스캔 기능
                        //if (_SysInfo.bBCDReadAllOk && _Config.bUseReWorkTypeBCDScan)
                        //{
                        //    if (_SysInfo.strST1ReadBCDData.Substring(0, Math.Min(_SysInfo.strST1ReadBCDData.Length, _ModelInfo.strComment1.Length)) == _ModelInfo.strComment1)
                        //    {
                        //        _SysInfo.strReWorkBCD = _SysInfo.strST1ReadBCDData;
                        //        nProcessStep[nStepIndex] = 6;
                        //        break;
                        //    }
                        //}
                        ///////////// 리워크 바코드 스캔 기능


                        //if (_SysInfo.bBCDReadAllOk && _ModelInfo.bUseScanSTTester)
                        //{
                        //    if (_SysInfo.strST1ReadBCDData.Substring(0, Math.Min(_SysInfo.strST1ReadBCDData.Length, _ModelInfo.strComment1.Length)) == _ModelInfo.strComment1)
                        //    {
                        //        nProcessStep[nStepIndex] = 20;
                        //    }
                        //    else
                        //    {
                        //        AppendLogMsg("정상적인 바코드가 아닙니다.", LOG_TYPE.ERROR);
                        //        _SysInfo.nTL_Beep = 2;
                        //        nProcessStep[nStepIndex] = 0;
                        //    }
                        //}
                        //else
                        //{
                            nProcessStep[nStepIndex]++;
                        //}
                    }
                    break;

                case 2:
                    //int nCount = 0;
                    //try { nCount = _dtBCDInfo.Select(String.Format("[Barcode] = '{0}'", _SysInfo.strReadBCDData)).Count(); }
                    //catch { nCount = 0; }

                    if (/*nCount*/ _ST1BCDList.Count(str => str.strBCD == _SysInfo.strST1ReadBCDData) != 0)
                    {
                        if (_Config.strLangue == "KOR") { AppendLogMsg(String.Format("CMA 중복 바코드 입니다."), LOG_TYPE.ERROR); }
                        else { AppendLogMsg(String.Format("CMA 重复条形码。"), LOG_TYPE.ERROR); }
                        _SysInfo.nTL_Beep = 2;

                        nProcessStep[nStepIndex] = 0;
                        break;
                    }
                    else
                    {
                        //if (CheckCMABcdDuplicate(_SysInfo.strReadBCDData))
                        //{

                        //    if (_Config.strLangue == "KOR") { AppendLogMsg(String.Format("CMA 중복 바코드 입니다."), LOG_TYPE.ERROR); }
                        //    else { AppendLogMsg(String.Format("CMA 重复条形码。"), LOG_TYPE.ERROR); }
                        //    _SysInfo.nTL_Beep = 2;

                        //    nProcessStep[nStepIndex] = 0;
                        //    break;
                        //}
                        //else
                        //{
                        nProcessStep[nStepIndex]++;
                        //}

                    }
                    break;

                case 3:
                    // CMA 일경우
                    _SysInfo.bST1BCDAddFlag = false;


                    //// 바코드 스캔 인터록 2018. 11. 26  피플 정부장님 요청
                    //if (_SysInfo.nCmaCount == 0 || _SysInfo.strST1CompareBCD == "")
                    //{
                    //    string[] strSplitBCD = _ModelInfo.strCmaSymbol.Split(',');

                    //    // 기본정보는 Index 0번으로 설정
                    //    _SysInfo.strST1CompareBCD = strSplitBCD[0];

                    //    // 추가 비교후 Index에 따른 할당
                    //    for (int i = 0; i < strSplitBCD.Length; i++)
                    //    {
                    //        if (_SysInfo.strReadBCDData.Substring(0, Math.Min(_SysInfo.strReadBCDData.Length, strSplitBCD[i].Length)) == strSplitBCD[i])
                    //        {
                    //            _SysInfo.strST1CompareBCD = strSplitBCD[i];
                    //        }
                    //    }
                    //}
                    // 해당 부분 변경








                    //if (_SysInfo.strReadBCDData.Substring(0, Math.Min(_SysInfo.strReadBCDData.Length, _SysInfo.strCompareBCD.Length)) == _SysInfo.strCompareBCD)
                    if (CheckBarcode(_SysInfo.strST1ReadBCDData, _ModelInfo.strCmaSymbol) && (_SysInfo.bSt1ReadPalletBarcode || !_ModelInfo.bUsePalletBarcode))
                    {
                        if (CheckCMABcdDuplicate(_SysInfo.strST1ReadBCDData))
                        {

                            if (_Config.strLangue == "KOR") { AppendLogMsg(String.Format("CMA 중복 바코드 입니다."), LOG_TYPE.ERROR); }
                            else { AppendLogMsg(String.Format("CMA 重复条形码。"), LOG_TYPE.ERROR); }
                            _SysInfo.nTL_Beep = 2;

                            nProcessStep[nStepIndex] = 0;
                            break;
                        }

                        if (_SysInfo.nST1CmaCount == 0 && _Config.bUseReWorkTypeBCDScan)
                        {
                            // 첫 CMA 이고 리워크 타입 바코드 스캔을 사용한다면

                            DateTime.TryParseExact(_SysInfo.strST1ReadBCDData.Substring(_ModelInfo.nCMAStartIndex, 6),
                                  "yyMMdd",
                                  CultureInfo.InvariantCulture,
                                  DateTimeStyles.None,
                                  out _DtCMATarget);
                        }
                        if (_SysInfo.nST1CmaCount >= _ModelInfo.nCmaCount)         // ?????
                        {
                            AppendLogMsg("CMA 스캔 개수를 초과 하였습니다.", LOG_TYPE.ERROR);
                            _SysInfo.nTL_Beep = 2;
                        }
                        else
                        {
                            if (_Config.bUseCMAStatusCheck)
                            {
                                if (CheckCMAStatus(_SysInfo.strST1ReadBCDData) == "OK")
                                {
                                    _SysInfo.bST1BCDAddFlag = true;
                                    _ST1BCDList.Add(new _ReadBarcodeData() { strBCD = _SysInfo.strST1ReadBCDData, strCate = "CMA" });
                                    //SaveBCDListInfo();
                                    //_mainform.BeginInvoke(new Action(() => _mainform.UpdateBCDGridStyle()));
                                    //_dtBCDInfo.Rows.Add(_SysInfo.strReadBCDData, "CMA");
                                    //SaveBCDInfoTable();
                                }
                                else if (CheckCMAStatus(_SysInfo.strST1ReadBCDData) == "NG")
                                {
                                    AppendLogMsg("CMA 검사 불량 제품 입니다.", LOG_TYPE.ERROR);
                                    _SysInfo.nTL_Beep = 2;
                                }
                                else if (CheckCMAStatus(_SysInfo.strST1ReadBCDData) == "NOFILE")
                                {
                                    AppendLogMsg("CMA 검사 정보가 없습니다.", LOG_TYPE.ERROR);
                                    _SysInfo.nTL_Beep = 2;
                                }
                                else
                                {
                                    AppendLogMsg("CMA 검사 정보가 정확하지 않습니다.", LOG_TYPE.ERROR);
                                    _SysInfo.nTL_Beep = 2;
                                }
                            }
                            else if (_NgDataList.Exists(x => x == _SysInfo.strST1ReadBCDData))
                            {
                                AppendLogMsg("불량 CMA 입니다.", LOG_TYPE.ERROR);
                                _SysInfo.nTL_Beep = 2;
                            }
                            else
                            {
                                //if (_Config.bUseReWorkTypeBCDScan)
                                //{
                                //    DateTime _DtTemp = new DateTime();

                                //    DateTime.TryParseExact(_SysInfo.strST1ReadBCDData.Substring(_ModelInfo.nCMAStartIndex, 6),
                                //            "yyMMdd",
                                //            CultureInfo.InvariantCulture,
                                //            DateTimeStyles.None,
                                //            out _DtTemp);

                                //    TimeSpan _TsTemp = _DtCMATarget - _DtTemp;


                                //    if (Math.Abs(_TsTemp.Days) > _ModelInfo.nTimeLimit)
                                //    {
                                //        AppendLogMsg("CMA 날자 NG 제품입니다.", LOG_TYPE.ERROR);
                                //        _SysInfo.nTL_Beep = 2;
                                //    }
                                //    else
                                //    {
                                        //_SysInfo.bST1BCDAddFlag = true;

                                        //_ST1BCDList.Add(new _ReadBarcodeData() { strBCD = _SysInfo.strST1ReadBCDData, strCate = "CMA" });
                                        //SaveBCDListInfo();
                                        //_mainform.BeginInvoke(new Action(() => _mainform.UpdateBCDGridStyle()));
                                        //_dtBCDInfo.Rows.Add(_SysInfo.strReadBCDData, "CMA");
                                        //_dtBCDInfo.AcceptChanges();

                                        //SaveBCDInfoTable();
                                    //}
                                //}
                                //else
                                //{
                                    _SysInfo.bST1BCDAddFlag = true;

                                    _ST1BCDList.Add(new _ReadBarcodeData() { strBCD = _SysInfo.strST1ReadBCDData, strCate = "CMA" });
                                    //SaveBCDListInfo();
                                    //_mainform.BeginInvoke(new Action(() => _mainform.UpdateBCDGridStyle()));

                                    // CMA 중복 데이터 저장

                                    //_dtBCDInfo.Rows.Add(_SysInfo.strReadBCDData, "CMA");
                                    //_dtBCDInfo.AcceptChanges();
                                    //SaveBCDInfoTable();
                               // }

                            }
                        }
                    }
                    else if (_ModelInfo._EtcDataScan[2].CheckBarcode(_SysInfo.strST1ReadBCDData))
                    {
                        // 바코드 일치의 경우
                    }
                    else
                    {
                        if (CheckEPPBarcodeInList(_SysInfo.strST1ReadBCDData))
                        {
                            // EPP 리스트에 있는 바코드라면
                            if (_SysInfo.nEPPReadCount < _ModelInfo._ListEppScan.Count)
                            {
                                if (CheckEPPBCD(_SysInfo.strST1ReadBCDData, _SysInfo.nEPPReadCount))
                                {
                                    // EPP 순서에 맞게 리딩을 하였다면
                                    _SysInfo.nEPPReadCount++;
                                }
                                else
                                {
                                    _SysInfo.nEPPReadCount = 0;
                                    AppendLogMsg("이종품 검사 - EPP 스캔순서가 잘못되었습니다!!", LOG_TYPE.ERROR);
                                    _SysInfo.nTL_Beep = 2;
                                }
                            }
                            else
                            {
                                _SysInfo.nEPPReadCount = 0;
                                AppendLogMsg("이종품 검사 - EPP 스캔횟수를 초과하였습니다!!", LOG_TYPE.ERROR);
                                _SysInfo.nTL_Beep = 2;
                            }
                        }
                        else
                        {
                            AppendLogMsg("이종품 검사 - 바코드가 일치하지 않습니다!!", LOG_TYPE.ERROR);
                            _SysInfo.nTL_Beep = 2;
                        }
                        //AppendLogMsg("정상적인 바코드가 아닙니다.", LOG_TYPE.ERROR);
                        //_SysInfo.nTL_Beep = 2;
                    }
                    nProcessStep[nStepIndex]++;
                    break;

                case 4:
                    if (_SysInfo.nST1CmaCount >= _ModelInfo.nCmaCount && _SysInfo.bST1BCDAddFlag)
                    {
                        _SysInfo.bST1BCDAddFlag = false;
                        nProcessStep[nStepIndex]++;
                    }
                    else
                    {
                        nProcessStep[nStepIndex] = 0;
                    }
                    break;

                case 5:
                    //SaveProductCount();         // 파레트 및 바코드 정보 저장
                    // 파레트 및 바코드 정보 저장
                    SavePalletBCDListInfo(_SysInfo.strSt1ReadPalletBarcode);
                    nProcessStep[nStepIndex] = 0;
                    break;


            }
        }

        public static bool GetEPPAllOK()
        {
            if (_SysInfo.nEPPReadCount >= _ModelInfo._ListEppScan.Count)
            {
                return true;
            }
            else
            {
                return false;
            }
        }


        public static bool CheckEPPBCD(string strReadBCD, int nIndex)
        {
            bool bResult = true;

            // 길이가 같다면 검사 시작함
            if (strReadBCD.Length == _ModelInfo._ListEppScan[nIndex].strScanSymbol.Length)
            {

                for (int i = 0; i < _ModelInfo._ListEppScan[nIndex].strScanSymbol.Length; i++)
                {
                    if (_ModelInfo._ListEppScan[nIndex].strScanSymbol[i] != '*')
                    {
                        if (strReadBCD[i] != _ModelInfo._ListEppScan[nIndex].strScanSymbol[i])
                        {
                            bResult = false;
                            break;
                        }
                    }
                }
            }
            else
            {
                bResult = false;
            }

            return bResult;
        }

        public static bool CheckEPPBarcodeInList(string strReadBCD)
        {
            bool bResult = false;

            bool bCheckBCD = true;

            for (int i = 0; i < _ModelInfo._ListEppScan.Count; i++)
            {
                if (strReadBCD.Length == _ModelInfo._ListEppScan[i].strScanSymbol.Length)
                {
                    // 길이가 같다면
                    bCheckBCD = true;
                    for (int j = 0; j < _ModelInfo._ListEppScan[i].strScanSymbol.Length; j++)
                    {
                        if (_ModelInfo._ListEppScan[i].strScanSymbol[j] != '*')
                        {
                            if (strReadBCD[j] != _ModelInfo._ListEppScan[i].strScanSymbol[j])
                            {
                                bCheckBCD = false;
                                break;
                            }
                        }
                    }

                    if (bCheckBCD)
                    {
                        // 정상 바코드를 찾게 된다면
                        bResult = true;
                        break;  //반복문을 벗어남
                    }
                }
            }

            return bResult;
        }
        //===========================================================

        //public static void CountCommunication(int nIndex)
        //{
        //    int nStepIndex = (int)PROC_LIST.COUNT_COMM1 + nIndex;

        //    #region Station 별 IO 할당
        //    DI _in_Tip1 = new DI();
        //    DI _in_Tip2 = new DI();
        //    DI _in_Tip3 = new DI();
        //    DI _in_Tip4 = new DI();
        //    DI _in_Tip5 = new DI();

        //    switch (nIndex)
        //    {
        //        case 0:
        //            _in_Tip1 = DI.STATION1_TIP1;
        //            _in_Tip2 = DI.STATION1_TIP2;
        //            _in_Tip3 = DI.STATION1_TIP3;
        //            _in_Tip4 = DI.STATION1_TIP4;
        //            _in_Tip5 = DI.STATION1_TIP5;
        //            break;

        //        case 1:
        //            _in_Tip1 = DI.STATION2_TIP1;
        //            _in_Tip2 = DI.STATION2_TIP2;
        //            _in_Tip3 = DI.STATION2_TIP3;
        //            _in_Tip4 = DI.STATION2_TIP4;
        //            _in_Tip5 = DI.STATION2_TIP5;
        //            break;

        //        case 2:
        //            _in_Tip1 = DI.STATION3_TIP1;
        //            _in_Tip2 = DI.STATION3_TIP2;
        //            _in_Tip3 = DI.STATION3_TIP3;
        //            _in_Tip4 = DI.STATION3_TIP4;
        //            _in_Tip5 = DI.STATION3_TIP5;
        //            break;

        //        case 3:
        //            _in_Tip1 = DI.STATION4_TIP1;
        //            _in_Tip2 = DI.STATION4_TIP2;
        //            _in_Tip3 = DI.STATION4_TIP3;
        //            _in_Tip4 = DI.STATION4_TIP4;
        //            _in_Tip5 = DI.STATION4_TIP5;
        //            break;

        //        case 4:
        //            _in_Tip1 = DI.STATION5_TIP1;
        //            _in_Tip2 = DI.STATION5_TIP2;
        //            _in_Tip3 = DI.STATION5_TIP3;
        //            _in_Tip4 = DI.STATION5_TIP4;
        //            _in_Tip5 = DI.STATION5_TIP5;
        //            break;

        //        case 5:
        //            _in_Tip1 = DI.LIFT_TIP1;
        //            _in_Tip2 = DI.LIFT_TIP2;
        //            _in_Tip3 = DI.LIFT_TIP3;
        //            _in_Tip4 = DI.LIFT_TIP4;
        //            _in_Tip5 = DI.LIFT_TIP5;
        //            break;
        //    }
        //    #endregion



        //    if (!_SysInfo.bCountUnlock[nIndex])
        //    {
        //        tUnLockTimer[nIndex].Start(10000);
        //    }
        //    else
        //    {
        //        if (tUnLockTimer[nIndex].Verify())
        //        {
        //            _SysInfo.bCountUnlock[nIndex] = false;
        //            tUnLockTimer[nIndex].Start(10000);
        //        }
        //    }


        //    switch (nProcessStep[nStepIndex])
        //    {
        //        case 0:
        //            nutSocket[nIndex].StartServer((ushort)(12000 + nIndex));
        //            nProcessStep[nStepIndex] = 100;
        //            break;


        //        case 100:
        //            nutSocket[nIndex].strReadData = "";
        //            nutSocket[nIndex].bReciveData = false;


        //            string strSendMsg = "";
        //            strSendMsg = _ModelInfo._TipInfo[nIndex].nTipMaxCount[0].ToString() + ",";
        //            strSendMsg += _ModelInfo._TipInfo[nIndex].nTipMaxCount[1].ToString() + ",";
        //            strSendMsg += _ModelInfo._TipInfo[nIndex].nTipMaxCount[2].ToString() + ",";
        //            strSendMsg += _ModelInfo._TipInfo[nIndex].nTipMaxCount[3].ToString() + ",";
        //            strSendMsg += _ModelInfo._TipInfo[nIndex].nTipMaxCount[4].ToString() + ",";
        //            strSendMsg += _SysInfo.nTipNowCount[nIndex, 0].ToString() + ",";
        //            strSendMsg += _SysInfo.nTipNowCount[nIndex, 1].ToString() + ",";
        //            strSendMsg += _SysInfo.nTipNowCount[nIndex, 2].ToString() + ",";
        //            strSendMsg += _SysInfo.nTipNowCount[nIndex, 3].ToString() + ",";
        //            strSendMsg += _SysInfo.nTipNowCount[nIndex, 4].ToString() + ",";
        //            strSendMsg += GetDIOPort(_in_Tip1) ? "0," : "1,";
        //            strSendMsg += GetDIOPort(_in_Tip2) ? "0," : "1,";
        //            strSendMsg += GetDIOPort(_in_Tip3) ? "0," : "1,";
        //            strSendMsg += GetDIOPort(_in_Tip4) ? "0," : "1,";
        //            strSendMsg += GetDIOPort(_in_Tip5) ? "0," : "1,";
        //            strSendMsg += _SysInfo.bCountUnlock[nIndex] ? "1," : "0,";

        //            if (_Config.nETCScanStation - 1 == nIndex)
        //            {
        //                //if ((_SysInfo.bETCReadOk || (_ModelInfo.nFuseCount < 1)) &&
        //                //    (_SysInfo.bETCScan1 || (_ModelInfo.nUseETC1BCD < 1)) &&
        //                //    (_SysInfo.bETCScan2 || (_ModelInfo.nUseETC2BCD < 1)) &&
        //                //     (_SysInfo.bETCScan3 || (_ModelInfo.nUseETC3BCD < 1)))
        //                //{
        //                //    strSendMsg += "2";
        //                //}
        //                //else
        //                //{
        //                //    strSendMsg += "1";
        //                //}
        //                if (_ModelInfo._EtcDataScan[1].CheckListAllOk())
        //                {
        //                    strSendMsg += "2";
        //                }
        //                else
        //                {
        //                    strSendMsg += "1";
        //                }
        //            }
        //            else if (_Config.nBCDScanStation - 1 == nIndex)
        //            {
        //                //if (_SysInfo.bBCDReadAllOk)
        //                //{
        //                //    strSendMsg += "2";
        //                //}
        //                //else
        //                //{
        //                //    strSendMsg += "1";
        //                //}

        //                if (_SysInfo.bBCDCMAReadOk && _SysInfo.bBCDBMSReadOk) { strSendMsg += "5"; }   // 둘다 읽힌경우
        //                if (_SysInfo.bBCDCMAReadOk && !_SysInfo.bBCDBMSReadOk) { strSendMsg += "6"; }   // CMA만 읽힌경우
        //                if (!_SysInfo.bBCDCMAReadOk && _SysInfo.bBCDBMSReadOk) { strSendMsg += "7"; }   // BMS만 읽힌경우
        //                if (!_SysInfo.bBCDCMAReadOk && !_SysInfo.bBCDBMSReadOk) { strSendMsg += "8"; }   // 둘다 안읽힌경우


        //            }
        //            else
        //            {
        //                strSendMsg += "0";
        //            }

        //            strSendMsg += "," + _SysInfo.nTiteLog[nIndex].ToString();   // 체결상태 모니터용

        //            nutSocket[nIndex].SendMessage(strSendMsg);
        //            tMainTimer[nStepIndex].Start(1000);
        //            nProcessStep[nStepIndex]++;
        //            break;

        //        case 101:
        //            if (tMainTimer[nStepIndex].Verify())
        //            {
        //                nutSocket[nIndex].StopServer();
        //                nutSocket[nIndex].StartServer((ushort)(12000 + nIndex));
        //                nProcessStep[nStepIndex] = 100;
        //                bCounterConatct[nIndex] = false;
        //            }

        //            if (nutSocket[nIndex].bReciveData)
        //            {
        //                int nSwIndex = 0;
        //                int.TryParse(nutSocket[nIndex].strReadData, out nSwIndex);

        //                if (nSwIndex == 0)
        //                {
        //                    nProcessStep[nStepIndex] = 100;
        //                }
        //                else if (nSwIndex > 0 && nSwIndex < 6)
        //                {
        //                    tUnLockTimer[nIndex].Start(10000);
        //                    if (nIndex == 2 && _ModelInfo.bUseST2Encoder)
        //                    {
        //                        _SysInfo.nST2TiteWorkCount++;
        //                        _SysInfo.nCount_Beep[nIndex] = 1;
        //                        if (_SysInfo.nST2TiteWorkCount > _ModelInfo._ST2Tip.Count)
        //                        {
        //                            _SysInfo.nST2TiteWorkCount = _ModelInfo._ST2Tip.Count;
        //                        }
        //                        else if (_SysInfo.nST2TiteWorkCount < 0)
        //                        {
        //                            _SysInfo.nST2TiteWorkCount = 0;
        //                        }
        //                    }
        //                    else
        //                    {
        //                        _SysInfo.nTipNowCount[nIndex, nSwIndex - 1]++;
        //                        SaveSTLockInfo(nIndex);
        //                        _SysInfo.nCount_Beep[nIndex] = 1;
        //                        if (_SysInfo.nTipNowCount[nIndex, nSwIndex - 1] > _ModelInfo._TipInfo[nIndex].nTipMaxCount[nSwIndex - 1])
        //                        {
        //                            _SysInfo.nTipNowCount[nIndex, nSwIndex - 1] = _ModelInfo._TipInfo[nIndex].nTipMaxCount[nSwIndex - 1];
        //                        }
        //                        else if (_SysInfo.nTipNowCount[nIndex, nSwIndex - 1] < 0)
        //                        {
        //                            _SysInfo.nTipNowCount[nIndex, nSwIndex - 1] = 0;
        //                        }
        //                    }
        //                }
        //                else if (nSwIndex > 5 && nSwIndex < 11)
        //                {
        //                    tUnLockTimer[nIndex].Start(10000);

        //                    if (nIndex == 2 && _ModelInfo.bUseST2Encoder)
        //                    {
        //                        _SysInfo.nST2TiteWorkCount--;
        //                        _SysInfo.nCount_Beep[nIndex] = 1;
        //                        if (_SysInfo.nST2TiteWorkCount > _ModelInfo._ST2Tip.Count)
        //                        {
        //                            _SysInfo.nST2TiteWorkCount = _ModelInfo._ST2Tip.Count;
        //                        }
        //                        else if (_SysInfo.nST2TiteWorkCount < 0)
        //                        {
        //                            _SysInfo.nST2TiteWorkCount = 0;
        //                        }
        //                    }
        //                    else
        //                    {
        //                        _SysInfo.nTipNowCount[nIndex, nSwIndex - 6]--;
        //                        SaveSTLockInfo(nIndex);
        //                        _SysInfo.nCount_Beep[nIndex] = 1;
        //                        if (_SysInfo.nTipNowCount[nIndex, nSwIndex - 6] > _ModelInfo._TipInfo[nIndex].nTipMaxCount[nSwIndex - 6])
        //                        {
        //                            _SysInfo.nTipNowCount[nIndex, nSwIndex - 6] = _ModelInfo._TipInfo[nIndex].nTipMaxCount[nSwIndex - 6];
        //                        }
        //                        else if (_SysInfo.nTipNowCount[nIndex, nSwIndex - 6] < 0)
        //                        {
        //                            _SysInfo.nTipNowCount[nIndex, nSwIndex - 6] = 0;
        //                        }
        //                    }
        //                }
        //                else if (nSwIndex > 10 && nSwIndex < 16)
        //                {
        //                    tUnLockTimer[nIndex].Start(10000);
        //                    if (nIndex == 2 && _ModelInfo.bUseST2Encoder)
        //                    {
        //                        _SysInfo.nST2TiteWorkCount = 0;
        //                        _SysInfo.nCount_Beep[nIndex] = 1;
        //                        if (_SysInfo.nST2TiteWorkCount > _ModelInfo._ST2Tip.Count)
        //                        {
        //                            _SysInfo.nST2TiteWorkCount = _ModelInfo._ST2Tip.Count;
        //                        }
        //                        else if (_SysInfo.nST2TiteWorkCount < 0)
        //                        {
        //                            _SysInfo.nST2TiteWorkCount = 0;
        //                        }
        //                    }
        //                    else
        //                    {
        //                        _SysInfo.nTipNowCount[nIndex, nSwIndex - 11] = 0;
        //                        SaveSTLockInfo(nIndex);
        //                        _SysInfo.nCount_Beep[nIndex] = 1;
        //                        if (_SysInfo.nTipNowCount[nIndex, nSwIndex - 11] > _ModelInfo._TipInfo[nIndex].nTipMaxCount[nSwIndex - 11])
        //                        {
        //                            _SysInfo.nTipNowCount[nIndex, nSwIndex - 11] = _ModelInfo._TipInfo[nIndex].nTipMaxCount[nSwIndex - 11];
        //                        }
        //                        else if (_SysInfo.nTipNowCount[nIndex, nSwIndex - 11] < 0)
        //                        {
        //                            _SysInfo.nTipNowCount[nIndex, nSwIndex - 11] = 0;
        //                        }
        //                    }
        //                }

        //                nProcessStep[nStepIndex] = 100;
        //                bCounterConatct[nIndex] = true;
        //            }
        //            break;
        //    }
        //}

        public static void CountCommunication(int nIndex)
        {
            int nStepIndex = (int)PROC_LIST.COUNT_COMM1 + nIndex;

            #region Station 별 IO 할당
            DI _in_Tip1 = new DI();
            DI _in_Tip2 = new DI();
            DI _in_Tip3 = new DI();
            DI _in_Tip4 = new DI();
            DI _in_Tip5 = new DI();

            switch (nIndex)
            {
                case 0:
                    _in_Tip1 = DI.STATION1_TIP1;
                    _in_Tip2 = DI.STATION1_TIP2;
                    _in_Tip3 = DI.STATION1_TIP3;
                    _in_Tip4 = DI.STATION1_TIP4;
                    _in_Tip5 = DI.STATION1_TIP5;
                    break;

                case 1:
                    _in_Tip1 = DI.STATION2_TIP1;
                    _in_Tip2 = DI.STATION2_TIP2;
                    _in_Tip3 = DI.STATION2_TIP3;
                    _in_Tip4 = DI.STATION2_TIP4;
                    _in_Tip5 = DI.STATION2_TIP5;
                    break;

                case 2:
                    _in_Tip1 = DI.STATION3_TIP1;
                    _in_Tip2 = DI.STATION3_TIP2;
                    _in_Tip3 = DI.STATION3_TIP3;
                    _in_Tip4 = DI.STATION3_TIP4;
                    _in_Tip5 = DI.STATION3_TIP5;
                    break;

                case 3:
                    _in_Tip1 = DI.STATION4_TIP1;
                    _in_Tip2 = DI.STATION4_TIP2;
                    _in_Tip3 = DI.STATION4_TIP3;
                    _in_Tip4 = DI.STATION4_TIP4;
                    _in_Tip5 = DI.STATION4_TIP5;
                    break;

                case 4:
                    _in_Tip1 = DI.STATION5_TIP1;
                    _in_Tip2 = DI.STATION5_TIP2;
                    _in_Tip3 = DI.STATION5_TIP3;
                    _in_Tip4 = DI.STATION5_TIP4;
                    _in_Tip5 = DI.STATION5_TIP5;
                    break;

                case 5:
                    _in_Tip1 = DI.LIFT_TIP1;
                    _in_Tip2 = DI.LIFT_TIP2;
                    _in_Tip3 = DI.LIFT_TIP3;
                    _in_Tip4 = DI.LIFT_TIP4;
                    _in_Tip5 = DI.LIFT_TIP5;
                    break;
            }
            #endregion



            if (!_SysInfo.bCountUnlock[nIndex] && !_SysInfo.bUpCountUnlock[nIndex])
            {
                tUnLockTimer[nIndex].Start(10000);
            }
            else
            {
                if (tUnLockTimer[nIndex].Verify())
                {
                    _SysInfo.bCountUnlock[nIndex] = false;
                    _SysInfo.bUpCountUnlock[nIndex] = false;
                    tUnLockTimer[nIndex].Start(10000);
                }
            }


            switch (nProcessStep[nStepIndex])
            {
                case 0:
                    //try
                    //{
                        nutSocket[nIndex].StartServer((ushort)(12000 + nIndex));
                   // }
                    //catch { }
                    nProcessStep[nStepIndex] = 100;
                    break;


                case 100:
                    nutSocket[nIndex].strReadData = "";
                    nutSocket[nIndex].bReciveData = false;


                    string strSendMsg = "";
                    strSendMsg = _SysInfo.nTipMaxCount[nIndex, 0].ToString() + ",";      // 1번팁 최대 카운트
                    strSendMsg += _SysInfo.nTipMaxCount[nIndex, 1].ToString() + ",";    // 2번팁 최대 카운트
                    strSendMsg += _SysInfo.nTipMaxCount[nIndex, 2].ToString() + ",";    // 3번팁 최대 카운트
                    strSendMsg += _SysInfo.nTipMaxCount[nIndex, 3].ToString() + ",";    // 4번팁 최대 카운트
                    strSendMsg += _SysInfo.nTipMaxCount[nIndex, 4].ToString() + ",";    // 5번팁 최대 카운트
                    strSendMsg += _SysInfo.nTipNowCount[nIndex, 0].ToString() + ",";    // 1번팁 현재 카운트
                    strSendMsg += _SysInfo.nTipNowCount[nIndex, 1].ToString() + ",";    // 2번팁 현재 카운트
                    strSendMsg += _SysInfo.nTipNowCount[nIndex, 2].ToString() + ",";    // 3번팁 현재 카운트
                    strSendMsg += _SysInfo.nTipNowCount[nIndex, 3].ToString() + ",";    // 4번팁 현재 카운트
                    strSendMsg += _SysInfo.nTipNowCount[nIndex, 4].ToString() + ",";    // 5번팁 현재 카운트
                    strSendMsg += GetDIOPort(_in_Tip1) ? "0," : "1,";                   // 팁 1번 감지
                    strSendMsg += GetDIOPort(_in_Tip2) ? "0," : "1,";                   // 팁 2번 감지
                    strSendMsg += GetDIOPort(_in_Tip3) ? "0," : "1,";                   // 팁 3번 감지
                    strSendMsg += GetDIOPort(_in_Tip4) ? "0," : "1,";                   // 팁 4번 감지
                    strSendMsg += GetDIOPort(_in_Tip5) ? "0," : "1,";                   // 팁 5번 감지
                    if (_SysInfo.bCountUnlock[nIndex])
                    {
                        strSendMsg += "1,";          // 카운터 잠금 여부
                    }
                    else if (_SysInfo.bUpCountUnlock[nIndex])
                    {
                        strSendMsg += "2,";          // 카운터 잠금 여부
                    }
                    else
                    {
                        strSendMsg += "0,";          // 카운터 잠금 여부
                    }
                    // +
                    // 0 : 바코드 스캔 사용하지 않음
                    // 1 : 이종품 검사 완료되지 않음   |  해당필드에 1 or 2 가 들어올경우
                    // 2 : 이종품 검사 완료됨          |  이종품 검사 항목 카운터 모니터에 표시
                    // 3 : Spare
                    // 4 : Spare
                    // 5 : BMS,CMA 둘다 읽힘           | 해당필드에 5~8 들어올경우
                    // 6 : CMA만 읽힘                  | BMS,CMA 검사항목 카운터 모니터에 표시
                    // 7 : BMS만 읽힘                  |
                    // 8 : 둘다 안읽힘                 |



                    if (_ModelInfo.nETCScanStation - 1 == nIndex)
                    {
                        //if ((_SysInfo.bETCReadOk || (_ModelInfo.nFuseCount < 1)) &&
                        //    (_SysInfo.bETCScan1 || (_ModelInfo.nUseETC1BCD < 1)) &&
                        //    (_SysInfo.bETCScan2 || (_ModelInfo.nUseETC2BCD < 1)) &&
                        //     (_SysInfo.bETCScan3 || (_ModelInfo.nUseETC3BCD < 1)) &&
                        //    (_SysInfo.bETCScan6 || (_ModelInfo.nUseETC6BCD < 1)))
                        //{
                        //    strSendMsg += "2";
                        //}
                        if (_ModelInfo._EtcDataScan[1].CheckListAllOk())
                        {
                            strSendMsg += "2";
                        }
                        else
                        {
                            strSendMsg += "1";
                        }
                    }
                    else if (nIndex == 0)
                    {
                    //    //if ((_SysInfo.bETCReadOk || (_ModelInfo.nFuseCount < 1)) &&
                    //    //    (_SysInfo.bETCScan1 || (_ModelInfo.nUseETC1BCD < 1)) &&
                    //    //    (_SysInfo.bETCScan2 || (_ModelInfo.nUseETC2BCD < 1)) &&
                    //    //     (_SysInfo.bETCScan3 || (_ModelInfo.nUseETC3BCD < 1)) &&
                    //    //    (_SysInfo.bETCScan6 || (_ModelInfo.nUseETC6BCD < 1)))
                    //    //{
                    //    //    strSendMsg += "2";
                    //    //}
                         if (_ModelInfo._EtcDataScan[2].CheckListAllOk())
                         {
                             strSendMsg += "2";
                         }
                         else
                         {
                             strSendMsg += "1";
                         }
                     }
                    else if (_ModelInfo.nBCDScanStation - 1 == nIndex)
                    {
                        //if (_SysInfo.bBCDReadAllOk)
                        //{
                        //    strSendMsg += "2";
                        //}
                        //else
                        //{
                        //    strSendMsg += "1";
                        //}

                        if (_SysInfo.bBCDCMAReadOk && _SysInfo.bBCDBMSReadOk) { strSendMsg += "5"; }   // 둘다 읽힌경우
                        if (_SysInfo.bBCDCMAReadOk && !_SysInfo.bBCDBMSReadOk) { strSendMsg += "6"; }   // CMA만 읽힌경우
                        if (!_SysInfo.bBCDCMAReadOk && _SysInfo.bBCDBMSReadOk) { strSendMsg += "7"; }   // BMS만 읽힌경우
                        if (!_SysInfo.bBCDCMAReadOk && !_SysInfo.bBCDBMSReadOk) { strSendMsg += "8"; }   // 둘다 안읽힌경우
                    }
                    else if (nIndex == 0)            // Pallet 스캔 사용시 
                    {
                        if ((_SysInfo.bST1BCDReadAllOk || !_ModelInfo.bUsePalletBarcode) && _ModelInfo._EtcDataScan[2].CheckListAllOk() && GetEPPAllOK())
                        {
                            strSendMsg += "2";
                        }
                        else
                        {
                            strSendMsg += "1";
                        }
                    }
                    //else if (nIndex == 5)
                    //{
                    //    if ((_SysInfo.bETCScan5 || (_ModelInfo.nUseETC5BCD < 1)))
                    //    {
                    //        strSendMsg += "2";
                    //    }
                    //    else
                    //    {
                    //        strSendMsg += "1";
                    //    }
                    //}
                    else
                    {
                        strSendMsg += "0";
                    }

                    strSendMsg += "," + _SysInfo.nTiteLog[nIndex].ToString();   // 체결상태 모니터용

                    nutSocket[nIndex].SendMessage(strSendMsg);
                    tMainTimer[nStepIndex].Start(5000);
                    nProcessStep[nStepIndex]++;
                    break;

                case 101:

                    // 1 : 1번팁 카운트 + 1          6 : 1번팁 카운트 - 1         11 : 1번팁 카운트 0으로 초기화
                    // 2 : 2번팁 카운트 + 1          7 : 2번팁 카운트 - 1         12 : 2번팁 카운트 0으로 초기화
                    // 3 : 3번팁 카운트 + 1          8 : 3번팁 카운트 - 1         13 : 3번팁 카운트 0으로 초기화
                    // 4 : 4번팁 카운트 + 1          9 : 4번팁 카운트 - 1         14 : 4번팁 카운트 0으로 초기화
                    // 5 : 5번팁 카운트 + 1         10 : 5번팁 카운트 - 1         15 : 5번팁 카운트 0으로 초기화

                    if (tMainTimer[nStepIndex].Verify())
                    {
                        //try
                        //{
                        nutSocket[nIndex].StopServer();
                        nutSocket[nIndex].StartServer((ushort)(12000 + nIndex));
                        //}
                        //catch { }

                        nProcessStep[nStepIndex] = 100;
                        bCounterConatct[nIndex] = false;
                    }

                    if (nutSocket[nIndex].bReciveData)
                    {
                        int nSwIndex = 0;
                        int.TryParse(nutSocket[nIndex].strReadData, out nSwIndex);

                        if (nSwIndex == 0)
                        {
                            nProcessStep[nStepIndex] = 100;
                        }
                        else if (nSwIndex > 0 && nSwIndex < 6)
                        {
                            tUnLockTimer[nIndex].Start(10000);

                            // ST2번에 관한 설정
                            //if (nIndex == 2 && _ModelInfo.bUseST2Encoder)
                            if (nIndex == 1 && _ModelInfo.bUseST2Encoder)
                            {
                                _SysInfo.nST2TiteWorkCount++;
                                _SysInfo.nCount_Beep[nIndex] = 1;
                                if (_SysInfo.nST2TiteWorkCount > _ModelInfo._ST2Tip.Count)
                                {
                                    _SysInfo.nST2TiteWorkCount = _ModelInfo._ST2Tip.Count;
                                }
                                else if (_SysInfo.nST2TiteWorkCount < 0)
                                {
                                    _SysInfo.nST2TiteWorkCount = 0;
                                }
                            }
                            else
                            {
                                _SysInfo.nTipNowCount[nIndex, nSwIndex - 1]++;
                                SaveSTLockInfo(nIndex);
                                _SysInfo.nCount_Beep[nIndex] = 1;
                                if (_SysInfo.nTipNowCount[nIndex, nSwIndex - 1] > _ModelInfo._TipInfo[nIndex].nTipMaxCount[nSwIndex - 1])
                                {
                                    _SysInfo.nTipNowCount[nIndex, nSwIndex - 1] = _ModelInfo._TipInfo[nIndex].nTipMaxCount[nSwIndex - 1];
                                }
                                else if (_SysInfo.nTipNowCount[nIndex, nSwIndex - 1] < 0)
                                {
                                    _SysInfo.nTipNowCount[nIndex, nSwIndex - 1] = 0;
                                }
                            }



                        }
                        else if (nSwIndex > 5 && nSwIndex < 11)
                        {
                            tUnLockTimer[nIndex].Start(10000);

                            // ST2번에 관한 설정
                            //if (nIndex == 2 && _ModelInfo.bUseST2Encoder)
                            if (nIndex == 1 && _ModelInfo.bUseST2Encoder)
                            {
                                _SysInfo.nST2TiteWorkCount--;
                                _SysInfo.nCount_Beep[nIndex] = 1;
                                if (_SysInfo.nST2TiteWorkCount > _ModelInfo._ST2Tip.Count)
                                {
                                    _SysInfo.nST2TiteWorkCount = _ModelInfo._ST2Tip.Count;
                                }
                                else if (_SysInfo.nST2TiteWorkCount < 0)
                                {
                                    _SysInfo.nST2TiteWorkCount = 0;
                                }
                            }
                            else
                            {
                                _SysInfo.nTipNowCount[nIndex, nSwIndex - 6]--;
                                SaveSTLockInfo(nIndex);
                                _SysInfo.nCount_Beep[nIndex] = 1;
                                if (_SysInfo.nTipNowCount[nIndex, nSwIndex - 6] > _ModelInfo._TipInfo[nIndex].nTipMaxCount[nSwIndex - 6])
                                {
                                    _SysInfo.nTipNowCount[nIndex, nSwIndex - 6] = _ModelInfo._TipInfo[nIndex].nTipMaxCount[nSwIndex - 6];
                                }
                                else if (_SysInfo.nTipNowCount[nIndex, nSwIndex - 6] < 0)
                                {
                                    _SysInfo.nTipNowCount[nIndex, nSwIndex - 6] = 0;
                                }
                            }
                        }
                        else if (nSwIndex > 10 && nSwIndex < 16)
                        {
                            tUnLockTimer[nIndex].Start(10000);
                            //if (nIndex == 2 && _ModelInfo.bUseST2Encoder)
                            if (nIndex == 1 && _ModelInfo.bUseST2Encoder)
                            {
                                _SysInfo.nST2TiteWorkCount = 0;
                                _SysInfo.nCount_Beep[nIndex] = 1;
                                if (_SysInfo.nST2TiteWorkCount > _ModelInfo._ST2Tip.Count)
                                {
                                    _SysInfo.nST2TiteWorkCount = _ModelInfo._ST2Tip.Count;
                                }
                                else if (_SysInfo.nST2TiteWorkCount < 0)
                                {
                                    _SysInfo.nST2TiteWorkCount = 0;
                                }
                            }
                            else
                            {
                                _SysInfo.nTipNowCount[nIndex, nSwIndex - 11] = 0;
                                SaveSTLockInfo(nIndex);
                                _SysInfo.nCount_Beep[nIndex] = 1;
                                if (_SysInfo.nTipNowCount[nIndex, nSwIndex - 11] > _ModelInfo._TipInfo[nIndex].nTipMaxCount[nSwIndex - 11])
                                {
                                    _SysInfo.nTipNowCount[nIndex, nSwIndex - 11] = _ModelInfo._TipInfo[nIndex].nTipMaxCount[nSwIndex - 11];
                                }
                                else if (_SysInfo.nTipNowCount[nIndex, nSwIndex - 11] < 0)
                                {
                                    _SysInfo.nTipNowCount[nIndex, nSwIndex - 11] = 0;
                                }
                            }
                        }

                        nProcessStep[nStepIndex] = 100;
                        bCounterConatct[nIndex] = true;
                    }
                    break;
            }
        }


        public static int SUB_SEARCH_HOME(bool bLog)
        {
            int i = new int();
            int nProcIndex = (int)PROC_LIST.SUB_HOME_SEARCH;
            uint endStatus = new uint();
            uint nowStatus = new uint();

            switch (nProcessStep[nProcIndex])
            {
                case 0:
                    for (i = 0; i < _Search_ALL.nAxisSize; i++)
                    {
                        _Search_ALL.nWorkStep[i] = 0;
                        _Search_ALL.bComplete[i] = false;
                        _Search_ALL.bResult[i] = false;

                        // 소프트웨어 리미트 끄기
                        CAXM.AxmSignalSetSoftLimit(_Search_ALL.nAxis[i], (uint)AXT_USE.DISABLE, (uint)AXT_MOTION_STOPMODE.EMERGENCY_STOP, (uint)AXT_MOTION_SELECTION.COMMAND,
                            _MotorAxisInfo[_Search_ALL.nAxis[i]].dbPositiveLimit, _MotorAxisInfo[_Search_ALL.nAxis[i]].dbNegativeLimit);


                        AxmUserSetSoftwareLimitEnable((AXIS)_Search_ALL.nAxis[i], false, false);


                        // 홈서치 시작
                        if (bLog)
                            AppendLogMsg(String.Format("{0} 축 홈서치 시작", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.INFO);
                    }
                    nProcessStep[nProcIndex]++;
                    break;

                case 1:
                    for (i = 0; i < _Search_ALL.nAxisSize; i++)
                    {
                        switch (_Search_ALL.nWorkStep[i])
                        {

                            case 0:
                                switch ((AXIS)_Search_ALL.nAxis[i])
                                {
                                    case AXIS.X:
                                    case AXIS.Y:
                                    case AXIS.HIPOT_1X:
                                    case AXIS.HIPOT_1Z:
                                    case AXIS.HIPOT_2X:
                                    case AXIS.HIPOT_2Z:
                                    case AXIS.EOL_X:
                                    case AXIS.EOL_Z:
                                    case AXIS.EOL_Y:
                                    case AXIS.HIPOT_2Y:
                                    case AXIS.HIPOT_1Y:
                                    //case AXIS.BOLT_R1:
                                    //case AXIS.BOLT_R2:
                                    //case AXIS.BOLT_R3:
                                    //case AXIS.BOLT_R4:
                                    case AXIS.CAMERA1_X:
                                    case AXIS.CAMERA1_Y:
                                    case AXIS.CAMERA1_Z:
                                    case AXIS.CAMERA2_X:
                                    case AXIS.CAMERA2_Y:
                                    case AXIS.CAMERA2_Z:
                                        _Search_ALL.nWorkStep[i] = 400;     // ORG 로 홈 검색
                                        break;


                                    case AXIS.Z:
                                        _Search_ALL.nWorkStep[i] = 500;
                                        break;


                                    //case AXIS.EOL_Y:
                                    //case AXIS.HIPOT_2Y:
                                    //case AXIS.HIPOT_1Y:
                                    //    _Search_ALL.nWorkStep[i] = 700;
                                    //    break;

                                    case AXIS.R:
                                        _Search_ALL.nWorkStep[i] = 400;     // ORG 로 홈 검색하는데 + 방향으로
                                        break;

                                }
                                break;

                            // ORG 로 Home 검색
                            case 100:
                                //AppendLogMsg(String.Format("{0}축 -방향으로 홈센서 찾는중...", (AXIS)_HomeParam.nAxis[i]), Color.Green);
                                Move((AXIS)_Search_ALL.nAxis[i], -0.1, _Config.dbMotorHomeSpeed, 0.1);  // - 방향으로 홈센서 찾기
                                _Search_ALL.nWorkStep[i]++;
                                break;

                            case 101:
                                if (!MotionDone((AXIS)_Search_ALL.nAxis[i]))
                                    break;

                                CAXM.AxmHomeReadSignal(_Search_ALL.nAxis[i], ref nowStatus);

                                if (nowStatus != 0)
                                {
                                    _Search_ALL.nWorkStep[i] = 103;
                                    break;
                                }

                                CAXM.AxmMoveSignalSearch(_Search_ALL.nAxis[i], -(_Config.dbMotorHomeSpeed), 0.2, (int)AXT_MOTION_HOME_DETECT.HomeSensor,
                                    (int)AXT_DIO_EDGE.UP_EDGE, (int)AXT_MOTION_STOPMODE.SLOWDOWN_STOP);

                                _Search_ALL.nWorkStep[i]++;
                                break;

                            case 102:
                                if (!MotionDone((AXIS)_Search_ALL.nAxis[i]))
                                    break;

                                CAXM.AxmStatusReadStop(_Search_ALL.nAxis[i], ref endStatus);

                                if ((endStatus & (uint)AXT_MOTION_QIEND_STATUS.QIEND_STATUS_18) != 0 || (endStatus & (uint)AXT_MOTION_QIEND_STATUS.QIEND_STATUS_1) != 0)
                                {
                                    _Search_ALL.nWorkStep[i]++;
                                }
                                else
                                {
                                    _Search_ALL.nWorkStep[i] = 110;
                                }
                                break;


                            case 103:
                                //AppendLogMsg(String.Format("{0}축 +방향으로 홈센서 벗어나는중...", (AXIS)_HomeParam.nAxis[i]), Color.Green);
                                CAXM.AxmMoveSignalSearch(_Search_ALL.nAxis[i], _Config.dbMotorHomeSpeed * 0.3, 0.2, (int)AXT_MOTION_HOME_DETECT.HomeSensor,
                                    (int)AXT_DIO_EDGE.DOWN_EDGE, (int)AXT_MOTION_STOPMODE.SLOWDOWN_STOP);
                                _Search_ALL.nWorkStep[i]++;
                                break;



                            case 104:
                                if (!MotionDone((AXIS)_Search_ALL.nAxis[i]))
                                    break;

                                CAXM.AxmStatusReadStop(_Search_ALL.nAxis[i], ref endStatus);

                                if ((endStatus & (uint)AXT_MOTION_QIEND_STATUS.QIEND_STATUS_18) != 0)
                                {
                                    //AppendLogMsg(String.Format("{0}축 원점 검색 완료됨...", (AXIS)_HomeParam.nAxis[i]), Color.Green);
                                    _Search_ALL.bResult[i] = true;
                                }
                                else
                                {
                                    //AppendLogMsg(String.Format("{0}축 원점 검중 비정상 에러 발생됨...", (AXIS)_HomeParam.nAxis[i]), Color.Red);
                                }
                                _Search_ALL.nWorkStep[i]++;
                                break;


                            case 105:
                                if (bLog)
                                    AppendLogMsg(String.Format("{0}축 -방향으로 홈센서 찾아 저속이동중...", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR);

                                CAXM.AxmMoveSignalSearch(_Search_ALL.nAxis[i], -(_Config.dbMotorHomeSpeed * 0.1), 0.2, (int)AXT_MOTION_HOME_DETECT.HomeSensor,
                                    (int)AXT_DIO_EDGE.UP_EDGE, (int)AXT_MOTION_STOPMODE.EMERGENCY_STOP);
                                _Search_ALL.nWorkStep[i]++;
                                break;


                            case 106:
                                if (!MotionDone((AXIS)_Search_ALL.nAxis[i]))
                                    break;
                                CAXM.AxmStatusReadStop(_Search_ALL.nAxis[i], ref endStatus);

                                if ((endStatus & (uint)AXT_MOTION_QIEND_STATUS.QIEND_STATUS_18) != 0)
                                {
                                    if (bLog)
                                        AppendLogMsg(String.Format("{0}축 원점 검색 완료됨...", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR);
                                    _Search_ALL.bResult[i] = true;
                                }
                                else
                                {
                                    if (bLog)
                                        AppendLogMsg(String.Format("{0}축 원점 검중 비정상 에러 발생됨...", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR);
                                }
                                _Search_ALL.nWorkStep[i] = 110;
                                break;


                            case 110:
                                _Search_ALL.tTimer[i].Restart();
                                _Search_ALL.nWorkStep[i]++;
                                break;

                            case 111:
                                if (!(_Search_ALL.tTimer[i].ElapsedMilliseconds > 200))
                                    break;

                                _Search_ALL.tTimer[i].Stop();
                                CAXM.AxmStatusSetCmdPos(_Search_ALL.nAxis[i], 0.0);
                                CAXM.AxmStatusSetActPos(_Search_ALL.nAxis[i], 0.0);

                                _Search_ALL.bComplete[i] = true;
                                _Search_ALL.nWorkStep[i] = 1000;
                                break;
                            ////////////////////////

                            // NELM 로 Home 검색
                            case 200:
                                //AppendLogMsg(String.Format("{0}축 -방향으로 홈센서 찾는중...", (AXIS)_HomeParam.nAxis[i]), Color.Green);
                                Move((AXIS)_Search_ALL.nAxis[i], 0.1, _Config.dbMotorHomeSpeed, 0.1);  // - 방향으로 홈센서 찾기
                                _Search_ALL.nWorkStep[i]++;
                                break;

                            case 201:
                                if (!MotionDone((AXIS)_Search_ALL.nAxis[i]))
                                    break;
                                {
                                    uint pLimit = 0;
                                    uint nLimit = 0;
                                    CAXM.AxmSignalReadLimit(_Search_ALL.nAxis[i], ref pLimit, ref nLimit);

                                    if (nLimit != 0)
                                    {
                                        _Search_ALL.nWorkStep[i] = 203;
                                        break;
                                    }
                                }

                                CAXM.AxmMoveSignalSearch(_Search_ALL.nAxis[i], -(_Config.dbMotorHomeSpeed), 0.2, (int)AXT_MOTION_HOME_DETECT.NegEndLimit,
                                    (int)AXT_DIO_EDGE.DOWN_EDGE, (int)AXT_MOTION_STOPMODE.SLOWDOWN_STOP);

                                _Search_ALL.nWorkStep[i]++;
                                break;

                            case 202:
                                if (!MotionDone((AXIS)_Search_ALL.nAxis[i]))
                                    break;

                                CAXM.AxmStatusReadStop(_Search_ALL.nAxis[i], ref endStatus);

                                if ((endStatus & (uint)AXT_MOTION_QIEND_STATUS.QIEND_STATUS_18) != 0 || (endStatus & (uint)AXT_MOTION_QIEND_STATUS.QIEND_STATUS_1) != 0)
                                {
                                    _Search_ALL.nWorkStep[i]++;
                                }
                                else
                                {
                                    _Search_ALL.nWorkStep[i] = 210;
                                }
                                break;


                            case 203:
                                //AppendLogMsg(String.Format("{0}축 +방향으로 홈센서 벗어나는중...", (AXIS)_HomeParam.nAxis[i]), Color.Green);
                                CAXM.AxmMoveSignalSearch(_Search_ALL.nAxis[i], _Config.dbMotorHomeSpeed * 0.3, 0.2, (int)AXT_MOTION_HOME_DETECT.NegEndLimit,
                                    (int)AXT_DIO_EDGE.UP_EDGE, (int)AXT_MOTION_STOPMODE.SLOWDOWN_STOP);
                                _Search_ALL.nWorkStep[i]++;
                                break;



                            case 204:
                                if (!MotionDone((AXIS)_Search_ALL.nAxis[i]))
                                    break;

                                CAXM.AxmStatusReadStop(_Search_ALL.nAxis[i], ref endStatus);

                                if ((endStatus & (uint)AXT_MOTION_QIEND_STATUS.QIEND_STATUS_18) != 0)
                                {
                                    //AppendLogMsg(String.Format("{0}축 원점 검색 완료됨...", (AXIS)_HomeParam.nAxis[i]), Color.Green);
                                    _Search_ALL.bResult[i] = true;
                                }
                                else
                                {
                                    //AppendLogMsg(String.Format("{0}축 원점 검중 비정상 에러 발생됨...", (AXIS)_HomeParam.nAxis[i]), Color.Red);
                                }
                                _Search_ALL.nWorkStep[i]++;
                                break;


                            case 205:
                                if (bLog)
                                    AppendLogMsg(String.Format("{0}축 -방향으로 홈센서 찾아 저속이동중...", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.LOG);
                                CAXM.AxmMoveSignalSearch(_Search_ALL.nAxis[i], -(_Config.dbMotorHomeSpeed * 0.1), 0.2, (int)AXT_MOTION_HOME_DETECT.NegEndLimit,
                                    (int)AXT_DIO_EDGE.DOWN_EDGE, (int)AXT_MOTION_STOPMODE.EMERGENCY_STOP);
                                _Search_ALL.nWorkStep[i]++;
                                break;


                            case 206:
                                if (!MotionDone((AXIS)_Search_ALL.nAxis[i]))
                                    break;
                                CAXM.AxmStatusReadStop(_Search_ALL.nAxis[i], ref endStatus);

                                if ((endStatus & (uint)AXT_MOTION_QIEND_STATUS.QIEND_STATUS_18) != 0 || (endStatus & (uint)AXT_MOTION_QIEND_STATUS.QIEND_STATUS_1) != 0)
                                {
                                    if (bLog)
                                        AppendLogMsg(String.Format("{0}축 원점 검색 완료됨...", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.LOG);
                                    _Search_ALL.bResult[i] = true;
                                }
                                else
                                {
                                    if (bLog)
                                        AppendLogMsg(String.Format("{0}축 원점 검중 비정상 에러 발생됨...", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR);
                                }
                                _Search_ALL.nWorkStep[i] = 210;
                                break;


                            case 210:
                                _Search_ALL.tTimer[i].Restart();
                                _Search_ALL.nWorkStep[i]++;
                                break;

                            case 211:
                                if (!(_Search_ALL.tTimer[i].ElapsedMilliseconds > 200))
                                    break;

                                _Search_ALL.tTimer[i].Stop();
                                CAXM.AxmStatusSetCmdPos(_Search_ALL.nAxis[i], 0.0);
                                CAXM.AxmStatusSetActPos(_Search_ALL.nAxis[i], 0.0);

                                _Search_ALL.bComplete[i] = true;
                                _Search_ALL.nWorkStep[i] = 1000;
                                break;
                            ////////////////////////




                            // ORG 로 Home 검색
                            case 300:
                                //AppendLogMsg(String.Format("{0}축 +방향으로 홈센서 찾는중...", (AXIS)_HomeParam.nAxis[i]), Color.Green);
                                Move((AXIS)_Search_ALL.nAxis[i], 0.1, -(_Config.dbMotorHomeSpeed), 0.1);  // + 방향으로 홈센서 찾기
                                _Search_ALL.nWorkStep[i]++;
                                break;

                            case 301:
                                if (!MotionDone((AXIS)_Search_ALL.nAxis[i]))
                                    break;

                                CAXM.AxmHomeReadSignal(_Search_ALL.nAxis[i], ref nowStatus);

                                if (nowStatus != 0)
                                {
                                    _Search_ALL.nWorkStep[i] = 303;
                                    break;
                                }

                                CAXM.AxmMoveSignalSearch(_Search_ALL.nAxis[i], -(_Config.dbMotorHomeSpeed), 0.2, (int)AXT_MOTION_HOME_DETECT.HomeSensor,
                                    (int)AXT_DIO_EDGE.UP_EDGE, (int)AXT_MOTION_STOPMODE.SLOWDOWN_STOP);

                                _Search_ALL.nWorkStep[i]++;
                                break;

                            case 302:
                                if (!MotionDone((AXIS)_Search_ALL.nAxis[i]))
                                    break;

                                CAXM.AxmStatusReadStop(_Search_ALL.nAxis[i], ref endStatus);

                                if ((endStatus & (uint)AXT_MOTION_QIEND_STATUS.QIEND_STATUS_18) != 0 || (endStatus & (uint)AXT_MOTION_QIEND_STATUS.QIEND_STATUS_1) != 0)
                                {
                                    _Search_ALL.nWorkStep[i]++;
                                }
                                else
                                {
                                    _Search_ALL.nWorkStep[i] = 310;
                                }
                                break;


                            case 303:
                                //AppendLogMsg(String.Format("{0}축 -방향으로 홈센서 벗어나는중...", (AXIS)_HomeParam.nAxis[i]), Color.Green);
                                CAXM.AxmMoveSignalSearch(_Search_ALL.nAxis[i], (_Config.dbMotorHomeSpeed * 0.3), 0.2, (int)AXT_MOTION_HOME_DETECT.HomeSensor,
                                    (int)AXT_DIO_EDGE.DOWN_EDGE, (int)AXT_MOTION_STOPMODE.SLOWDOWN_STOP);
                                _Search_ALL.nWorkStep[i]++;
                                break;



                            case 304:
                                if (!MotionDone((AXIS)_Search_ALL.nAxis[i]))
                                    break;

                                CAXM.AxmStatusReadStop(_Search_ALL.nAxis[i], ref endStatus);

                                if ((endStatus & (uint)AXT_MOTION_QIEND_STATUS.QIEND_STATUS_18) != 0)
                                {
                                    //AppendLogMsg(String.Format("{0}축 원점 검색 완료됨...", (AXIS)_HomeParam.nAxis[i]), Color.Green);
                                    _Search_ALL.bResult[i] = true;
                                }
                                else
                                {
                                    //AppendLogMsg(String.Format("{0}축 원점 검중 비정상 에러 발생됨...", (AXIS)_HomeParam.nAxis[i]), Color.Red);
                                }
                                _Search_ALL.nWorkStep[i]++;
                                break;


                            case 305:
                                if (bLog)
                                    AppendLogMsg(String.Format("{0}축 +방향으로 홈센서 찾아 저속이동중...", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.LOG);

                                CAXM.AxmMoveSignalSearch(_Search_ALL.nAxis[i], -(_Config.dbMotorHomeSpeed * 0.1), 0.2, (int)AXT_MOTION_HOME_DETECT.HomeSensor,
                                    (int)AXT_DIO_EDGE.UP_EDGE, (int)AXT_MOTION_STOPMODE.EMERGENCY_STOP);
                                _Search_ALL.nWorkStep[i]++;
                                break;


                            case 306:
                                if (!MotionDone((AXIS)_Search_ALL.nAxis[i]))
                                    break;
                                CAXM.AxmStatusReadStop(_Search_ALL.nAxis[i], ref endStatus);

                                if ((endStatus & (uint)AXT_MOTION_QIEND_STATUS.QIEND_STATUS_18) != 0)
                                {
                                    if (bLog)
                                        AppendLogMsg(String.Format("{0}축 원점 검색 완료됨...", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.LOG);
                                    _Search_ALL.bResult[i] = true;
                                }
                                else
                                {
                                    if (bLog)
                                        AppendLogMsg(String.Format("{0}축 원점 검중 비정상 에러 발생됨...", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR);
                                }
                                _Search_ALL.nWorkStep[i] = 310;
                                break;


                            case 310:
                                _Search_ALL.tTimer[i].Restart();
                                _Search_ALL.nWorkStep[i]++;
                                break;

                            case 311:
                                if (!(_Search_ALL.tTimer[i].ElapsedMilliseconds > 200))
                                    break;

                                _Search_ALL.tTimer[i].Stop();
                                CAXM.AxmStatusSetCmdPos(_Search_ALL.nAxis[i], 0.0);
                                CAXM.AxmStatusSetActPos(_Search_ALL.nAxis[i], 0.0);

                                _Search_ALL.bComplete[i] = true;
                                _Search_ALL.nWorkStep[i] = 1000;
                                break;


                            // 아진꺼 홈서치 사용
                            case 400:


                                if (_Search_ALL.nAxis[i] == (int)AXIS.R)
                                {
                                    CAXM.AxmHomeSetSignalLevel(_Search_ALL.nAxis[i], 1);
                                    CAXM.AxmHomeSetMethod(_Search_ALL.nAxis[i], 1, 4, 0, 0.5, _Config.dbTurnRev);
                                }
                                else
                                {
                                    CAXM.AxmHomeSetSignalLevel(_Search_ALL.nAxis[i], 1);
                                    CAXM.AxmHomeSetMethod(_Search_ALL.nAxis[i], 0, 4, 0, 0.5, 0.0);
                                }

                                CAXM.AxmHomeSetFineAdjust(_Search_ALL.nAxis[i], 0.0, 1, 1, 1);
                                CAXM.AxmHomeSetVel(_Search_ALL.nAxis[i], 60, 30, 15, 10, 0.2, 0.2);
                                _Search_ALL.nWorkStep[i]++;
                                break;

                            case 401:
                                CAXM.AxmHomeSetStart(_Search_ALL.nAxis[i]);
                                _Search_ALL.nWorkStep[i]++;
                                break;

                            case 402:
                                {
                                    uint nHomeResult = 0;
                                    CAXM.AxmHomeGetResult(_Search_ALL.nAxis[i], ref nHomeResult);

                                    if (nHomeResult != 0x02)
                                    {
                                        if (nHomeResult == 0x01)
                                        {
                                            if (bLog)
                                                AppendLogMsg(String.Format("{0}축 원점 검색 완료됨...", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.LOG);
                                            _Search_ALL.bResult[i] = true;
                                        }
                                        else
                                        {
                                            if (bLog)
                                            {
                                                AppendLogMsg(String.Format("{0}축 원점 검중 비정상 에러 발생됨...", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR);

                                                if (nHomeResult == 0x10) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_GNT_RANGE", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x11) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_USER_BREAK", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x12) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_VELOCITY", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x13) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_AMP_FAULT", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x14) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_NEG_LIMIT", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x15) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_POS_LIMIT", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x16) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_NOT_DETECT", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0xFF) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_UNKNOWN", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                            }

                                        }

                                        _Search_ALL.bComplete[i] = true;
                                        _Search_ALL.nWorkStep[i] = 1000;
                                    }
                                }

                                break;
                            ////////////////////////

                            // 아진꺼 홈서치 사용
                            case 500:
                                CAXM.AxmHomeSetSignalLevel(_Search_ALL.nAxis[i], 1);
                                CAXM.AxmHomeSetMethod(_Search_ALL.nAxis[i], 0, 1, 0, 0.5, 0.0);
                                CAXM.AxmHomeSetVel(_Search_ALL.nAxis[i], 60, 10, 5, 1, 0.1, 0.1);
                                _Search_ALL.nWorkStep[i]++;
                                break;

                            case 501:
                                CAXM.AxmHomeSetStart(_Search_ALL.nAxis[i]);
                                _Search_ALL.nWorkStep[i]++;
                                break;

                            case 502:
                                {
                                    uint nHomeResult = 0;
                                    CAXM.AxmHomeGetResult(_Search_ALL.nAxis[i], ref nHomeResult);

                                    if (nHomeResult != 0x02)
                                    {
                                        if (nHomeResult == 0x01)
                                        {
                                            if (bLog)
                                                AppendLogMsg(String.Format("{0}축 원점 검색 완료됨...", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.LOG);
                                            _Search_ALL.bResult[i] = true;
                                        }
                                        else
                                        {
                                            if (bLog)
                                            {
                                                AppendLogMsg(String.Format("{0}축 원점 검중 비정상 에러 발생됨...", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR);
                                                if (nHomeResult == 0x10) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_GNT_RANGE", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x11) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_USER_BREAK", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x12) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_VELOCITY", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x13) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_AMP_FAULT", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x14) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_NEG_LIMIT", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x15) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_POS_LIMIT", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x16) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_NOT_DETECT", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0xFF) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_UNKNOWN", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                            }


                                        }

                                        _Search_ALL.bComplete[i] = true;
                                        _Search_ALL.nWorkStep[i] = 1000;
                                    }
                                }

                                break;


                            // 아진꺼 홈서치 사용
                            case 600:
                                CAXM.AxmHomeSetSignalLevel(_Search_ALL.nAxis[i], 1);
                                CAXM.AxmHomeSetMethod(_Search_ALL.nAxis[i], 1, 4, 0, 0.5, 0.0);
                                CAXM.AxmHomeSetVel(_Search_ALL.nAxis[i], 60, 30, 20, 10, 0.2, 0.2);
                                _Search_ALL.nWorkStep[i]++;
                                break;

                            case 601:
                                CAXM.AxmHomeSetStart(_Search_ALL.nAxis[i]);
                                _Search_ALL.nWorkStep[i]++;
                                break;

                            case 602:
                                {
                                    uint nHomeResult = 0;
                                    CAXM.AxmHomeGetResult(_Search_ALL.nAxis[i], ref nHomeResult);

                                    if (nHomeResult != 0x02)
                                    {
                                        if (nHomeResult == 0x01)
                                        {
                                            if (bLog)
                                                AppendLogMsg(String.Format("{0}축 원점 검색 완료됨...", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.LOG);
                                            _Search_ALL.bResult[i] = true;
                                        }
                                        else
                                        {
                                            if (bLog)
                                            {


                                                AppendLogMsg(String.Format("{0}축 원점 검중 비정상 에러 발생됨...", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR);
                                                if (nHomeResult == 0x10) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_GNT_RANGE", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x11) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_USER_BREAK", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x12) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_VELOCITY", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x13) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_AMP_FAULT", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x14) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_NEG_LIMIT", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x15) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_POS_LIMIT", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x16) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_NOT_DETECT", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0xFF) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_UNKNOWN", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                            }
                                        }

                                        _Search_ALL.bComplete[i] = true;
                                        _Search_ALL.nWorkStep[i] = 1000;
                                    }
                                }

                                break;
                            ////////////////////////


                            // 아진꺼 홈서치 사용
                            case 700:
                                CAXM.AxmHomeSetSignalLevel(_Search_ALL.nAxis[i], 1);
                                CAXM.AxmHomeSetMethod(_Search_ALL.nAxis[i], 0, 1, 0, 0.5, 0.0);
                                CAXM.AxmHomeSetVel(_Search_ALL.nAxis[i], 60, 10, 5, 1, 0.01, 0.1);
                                _Search_ALL.nWorkStep[i]++;
                                break;

                            case 701:
                                CAXM.AxmHomeSetStart(_Search_ALL.nAxis[i]);
                                _Search_ALL.nWorkStep[i]++;
                                break;

                            case 702:
                                {
                                    uint nHomeResult = 0;
                                    CAXM.AxmHomeGetResult(_Search_ALL.nAxis[i], ref nHomeResult);

                                    if (nHomeResult != 0x02)
                                    {
                                        if (nHomeResult == 0x01)
                                        {
                                            if (bLog)
                                                AppendLogMsg(String.Format("{0}축 원점 검색 완료됨...", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.LOG);
                                            _Search_ALL.bResult[i] = true;
                                        }
                                        else
                                        {
                                            if (bLog)
                                            {
                                                AppendLogMsg(String.Format("{0}축 원점 검중 비정상 에러 발생됨...", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR);
                                                if (nHomeResult == 0x10) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_GNT_RANGE", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x11) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_USER_BREAK", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x12) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_VELOCITY", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x13) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_AMP_FAULT", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x14) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_NEG_LIMIT", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x15) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_POS_LIMIT", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0x16) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_NOT_DETECT", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                                if (nHomeResult == 0xFF) { AppendLogMsg(String.Format("{0} ERR_CODE : HOME_ERR_UNKNOWN", (AXIS)_Search_ALL.nAxis[i]), LOG_TYPE.ERROR); }
                                            }
                                        }

                                        _Search_ALL.bComplete[i] = true;
                                        _Search_ALL.nWorkStep[i] = 1000;
                                    }
                                }

                                break;



                            ////////////////////////

                            case 1000:
                                break;

                        }
                    }

                    for (i = 0; i < _Search_ALL.nAxisSize; i++)
                    {
                        if (!_Search_ALL.bComplete[i])
                            break;
                    }

                    if (i >= _Search_ALL.nAxisSize)
                        nProcessStep[nProcIndex]++;
                    break;

                case 2:
                    nProcessStep[nProcIndex] = 0;
                    return -1;

            }

            return 0;
        }

        //====== FOOT SW 동작 =======================================
        static void SUB_FOOT_SW(int nStation)
        {
            #region Station 별 IO 할당
            DI _In_Foot_Sw = new DI();
            DI _In_Center = new DI();
            DO _out_Lock_off = new DO();
            DO _out_Break_off = new DO();

            switch (nStation)
            {
                case 0:
                    _In_Foot_Sw = DI.STATION1_FOOT_SW;
                    _In_Center = DI.STATION1_CENTER;
                    _out_Lock_off = DO.STATION1_LOCK_OFF;
                    _out_Break_off = DO.STATION1_BREAK_OFF;
                    break;

                case 1:
                    _In_Foot_Sw = DI.STATION2_FOOT_SW;
                    _In_Center = DI.STATION2_CENTER;
                    _out_Lock_off = DO.STATION2_LOCK_OFF;
                    _out_Break_off = DO.STATION2_BREAK_OFF;
                    break;

                case 2:
                    _In_Foot_Sw = DI.STATION3_FOOT_SW;
                    _In_Center = DI.STATION3_CENTER;
                    _out_Lock_off = DO.STATION3_LOCK_OFF;
                    _out_Break_off = DO.STATION3_BREAK_OFF;
                    break;

                case 3:
                    _In_Foot_Sw = DI.STATION4_FOOT_SW;
                    _In_Center = DI.STATION4_CENTER;
                    _out_Lock_off = DO.STATION4_LOCK_OFF;
                    _out_Break_off = DO.STATION4_BREAK_OFF;
                    break;

                case 4:
                    _In_Foot_Sw = DI.STATION5_FOOT_SW;
                    _In_Center = DI.STATION5_CENTER;
                    _out_Lock_off = DO.STATION5_LOCK_OFF;
                    _out_Break_off = DO.STATION5_BREAK_OFF;
                    break;
            }
            #endregion

            if (GetDIOPort(_In_Foot_Sw) && _SysInfo.bTite_Ing[nStation])
            {
                SetDIOPort(_out_Lock_off, true);
                SetDIOPort(_out_Break_off, true);
            }
            else
            {
                if (GetDIOPort(_In_Center))
                {
                    SetDIOPort(_out_Lock_off, false);
                    SetDIOPort(_out_Break_off, true);
                }
                else
                {
                    SetDIOPort(_out_Lock_off, true);
                    SetDIOPort(_out_Break_off, false);
                }

            }
        }
        //===========================================================


        ////====== 체결 프로세스 ======================================
        //static void SUB_TITE_PROCESS(int nStation)
        //{
        //    int nStepIndex = (int)PROC_LIST.SUB_TITE1 + nStation;

        //    int nUseTipCount = 0;
        //    int nUseTip = 0;
        //    #region Station 별 IO 할당
        //    DI _in_Tip1 = new DI();

        //    DI _in_Nut_1 = new DI();
        //    DI _in_Nut_2 = new DI();
        //    DI _in_Nut_3 = new DI();
        //    DI _in_Nut_4 = new DI();

        //    DO _out_Nut_4 = new DO();
        //    DO _out_Counter_1 = new DO();

        //    switch (nStation)
        //    {
        //        case 0:
        //            _in_Tip1 = DI.STATION1_TIP1;
        //            _in_Nut_1 = DI.NUTRUNNER1_IN1;
        //            _in_Nut_2 = DI.NUTRUNNER1_IN2;
        //            _in_Nut_3 = DI.NUTRUNNER1_IN3;
        //            _in_Nut_4 = DI.NUTRUNNER1_IN4;

        //            _out_Nut_4 = DO.NUTRUNNER1_OUT1;
        //            //_out_Counter_1 = DO.ST1_COUNTER_UP1;
        //            break;

        //        case 1:
        //            _in_Tip1 = DI.STATION2_TIP1;
        //            _in_Nut_1 = DI.NUTRUNNER2_IN1;
        //            _in_Nut_2 = DI.NUTRUNNER2_IN2;
        //            _in_Nut_3 = DI.NUTRUNNER2_IN3;
        //            _in_Nut_4 = DI.NUTRUNNER2_IN4;

        //            _out_Nut_4 = DO.NUTRUNNER2_OUT4;
        //            //_out_Counter_1 = DO.ST2_COUNTER_UP1;
        //            break;

        //        case 2:
        //            _in_Tip1 = DI.STATION3_TIP1;
        //            _in_Nut_1 = DI.NUTRUNNER3_IN1;
        //            _in_Nut_2 = DI.NUTRUNNER3_IN2;
        //            _in_Nut_3 = DI.NUTRUNNER3_IN3;
        //            _in_Nut_4 = DI.NUTRUNNER3_IN4;

        //            _out_Nut_4 = DO.NUTRUNNER3_OUT4;
        //            // _out_Counter_1 = DO.ST3_COUNTER_UP1;
        //            break;

        //        case 3:
        //            _in_Tip1 = DI.STATION4_TIP1;
        //            _in_Nut_1 = DI.NUTRUNNER4_IN1;
        //            _in_Nut_2 = DI.NUTRUNNER4_IN2;
        //            _in_Nut_3 = DI.NUTRUNNER4_IN3;
        //            _in_Nut_4 = DI.NUTRUNNER4_IN4;

        //            _out_Nut_4 = DO.NUTRUNNER4_OUT4;
        //            // _out_Counter_1 = DO.ST4_COUNTER_UP1;
        //            break;

        //        case 4:
        //            _in_Tip1 = DI.STATION5_TIP1;
        //            _in_Nut_1 = DI.NUTRUNNER5_IN1;
        //            _in_Nut_2 = DI.NUTRUNNER5_IN2;
        //            _in_Nut_3 = DI.NUTRUNNER5_IN3;
        //            _in_Nut_4 = DI.NUTRUNNER5_IN4;

        //            _out_Nut_4 = DO.NUTRUNNER5_OUT4;
        //            // _out_Counter_1 = DO.ST4_COUNTER_UP1;
        //            break;

        //        case 5:
        //            _in_Tip1 = DI.LIFT_TIP1;
        //            _in_Nut_1 = DI.NUTRUNNER6_IN1;
        //            _in_Nut_2 = DI.NUTRUNNER6_IN2;
        //            _in_Nut_3 = DI.NUTRUNNER6_IN3;
        //            _in_Nut_4 = DI.NUTRUNNER6_IN4;

        //            _out_Nut_4 = DO.NUTRUNNER_LIFT_OUT4;
        //            // _out_Counter_1 = DO.ST4_COUNTER_UP1;
        //            break;
        //    }
        //    #endregion


        //    // 사용팁 개수 및 팁 확인
        //    for (int i = 0; i < 5; i++)
        //    {
        //        if (!GetDIOPort(_in_Tip1 + i))
        //        {
        //            nUseTipCount++;
        //            nUseTip = i;
        //        }
        //    }

        //    _SysInfo.nNowUseTip[nStation] = nUseTip;
        //    _SysInfo.nNowUseTipCount[nStation] = nUseTipCount;


        //    if (_SysInfo.nTipNowCount[nStation, 0] >= _ModelInfo._TipInfo[nStation].nTipMaxCount[0] &&
        //        _SysInfo.nTipNowCount[nStation, 1] >= _ModelInfo._TipInfo[nStation].nTipMaxCount[1] &&
        //        _SysInfo.nTipNowCount[nStation, 2] >= _ModelInfo._TipInfo[nStation].nTipMaxCount[2] &&
        //        _SysInfo.nTipNowCount[nStation, 3] >= _ModelInfo._TipInfo[nStation].nTipMaxCount[3] &&
        //        _SysInfo.nTipNowCount[nStation, 4] >= _ModelInfo._TipInfo[nStation].nTipMaxCount[4])
        //    {
        //        _SysInfo.bTiteOk[nStation] = true;
        //    }
        //    else
        //    {
        //        _SysInfo.bTiteOk[nStation] = false;
        //    }



        //    //if (!_SysInfo.bTite_Ing[nStation]) { return; }      // 체결 작업 가능 시점이 아닐땐 그냥 리턴


        //    // 선택팁 개수가 1개이상이거나, 0개이거나, 해당팁이 체결 완료된 팁이라면
        //    if (nUseTipCount > 1 || nUseTipCount == 0 ||
        //        _SysInfo.nTipNowCount[nStation, nUseTip] >= _ModelInfo._TipInfo[nStation].nTipMaxCount[nUseTip])
        //    {
        //        SetDIOPort(_out_Nut_4, true);   // 너트러너 잠금
        //    }
        //    else
        //    {
        //        SetDIOPort(_out_Nut_4, false);  // 너트러너 잠금 해제
        //    }

        //    if (nUseTipCount == 1)
        //    {

        //        if (_ModelInfo._TipInfo[nStation].nSpare_a[nUseTip] > 0)
        //        {
        //            if (_SysInfo.nTipNowCount[nStation, nUseTip] >= _ModelInfo._TipInfo[nStation].nTipMaxCount[nUseTip + 5])
        //            {
        //                SetNutRunnerSch(nStation, _ModelInfo._TipInfo[nStation].nTipSch[nUseTip + 5] + 1);   // Torque 2번보다 카운트가 클경우 토크 2번에 저장된 데이터 사용
        //            }
        //            else
        //            {
        //                SetNutRunnerSch(nStation, _ModelInfo._TipInfo[nStation].nTipSch[nUseTip] + 1);   // 너트러너 스케줄 설정
        //            }
        //        }
        //        else
        //        {
        //            SetNutRunnerSch(nStation, _ModelInfo._TipInfo[nStation].nTipSch[nUseTip] + 1);   // 너트러너 스케줄 설정
        //        }

        //        //SetNutRunnerSch(nStation, _ModelInfo._TipInfo[nStation].nTipSch[nUseTip] + 1);   // 너트러너 스케줄 설정
        //    }


        //    switch (nProcessStep[nStepIndex])
        //    {
        //        case 0:
        //            if (!GetDIOPort(_in_Nut_1) && !GetDIOPort(_in_Nut_2) && !GetDIOPort(_in_Nut_3))
        //            {
        //                nProcessStep[nStepIndex]++;
        //            }
        //            break;

        //        case 1:
        //            if (GetDIOPort(_in_Nut_3))
        //            {
        //                _SysInfo.nTiteLog[nStation] = 1;
        //            }


        //            if (GetDIOPort(_in_Nut_1) && nUseTipCount == 1)
        //            {
        //                _SysInfo.nTiteLog[nStation] = 2;
        //                nProcessStep[nStepIndex]++;

        //            }
        //            else if (GetDIOPort(_in_Nut_2) && nUseTipCount == 1)
        //            {
        //                _SysInfo.nTiteLog[nStation] = 3;

        //                AppendLogMsg(String.Format("Station #{0} - 팁 체결 불량", nStation + 1), LOG_TYPE.ERROR);
        //                _SysInfo.nCount_Beep[nStation] = 3;
        //                nProcessStep[nStepIndex] = 0;
        //            }
        //            else if (GetDIOPort(_in_Nut_3) && nUseTipCount != 1)
        //            {
        //                AppendLogMsg(String.Format("Station #{0} - 팁 선택 오류", nStation + 1), LOG_TYPE.ERROR);
        //                _SysInfo.nCount_Beep[nStation] = 3;
        //                nProcessStep[nStepIndex] = 0;
        //            }
        //            else if (GetDIOPort(_in_Nut_3) && _SysInfo.nTipNowCount[nStation, nUseTip] >= _ModelInfo._TipInfo[nStation].nTipMaxCount[nUseTip])
        //            {
        //                AppendLogMsg(String.Format("Station #{0} - 해당 팁 체결 완료", nStation + 1), LOG_TYPE.ERROR);
        //                _SysInfo.nCount_Beep[nStation] = 3;
        //                nProcessStep[nStepIndex] = 0;
        //            }
        //            break;

        //        case 2:
        //            //SetDIOPort(_out_Counter_1 + nUseTip, true);
        //            _SysInfo.nTipNowCount[nStation, nUseTip]++;
        //            SaveSTLockInfo(nStation);
        //            if (_SysInfo.nTipNowCount[nStation, nUseTip] >= _ModelInfo._TipInfo[nStation].nTipMaxCount[nUseTip])
        //            {
        //                _SysInfo.nCount_Beep[nStation] = 2;
        //            }
        //            else
        //            {
        //                _SysInfo.nCount_Beep[nStation] = 1;
        //            }
        //            tMainTimer[nStepIndex].Start(100);
        //            nProcessStep[nStepIndex]++;
        //            break;

        //        case 3:
        //            if (tMainTimer[nStepIndex].Verify())
        //            {
        //                //SetDIOPort(_out_Counter_1 + nUseTip, false);
        //                nProcessStep[nStepIndex] = 0;
        //            }
        //            break;
        //    }
        //}
        ////===========================================================



        static void SUB_TITE_PROCESS(int nStation)
        {
            int nStepIndex = (int)PROC_LIST.SUB_TITE1 + nStation;

            int nUseTipCount = 0;
            int nUseTip = 0;
            #region Station 별 IO 할당
            DI _in_Tip1 = new DI();

            DI _in_Nut_1 = new DI();
            DI _in_Nut_2 = new DI();
            DI _in_Nut_3 = new DI();
            DI _in_Nut_4 = new DI();

            DO _out_Nut_4 = new DO();
            DO _out_Counter_1 = new DO();

            switch (nStation)
            {
                case 0:
                    _in_Tip1 = DI.STATION1_TIP1;
                    _in_Nut_1 = DI.NUTRUNNER1_IN1;
                    _in_Nut_2 = DI.NUTRUNNER1_IN2;
                    _in_Nut_3 = DI.NUTRUNNER1_IN3;
                    _in_Nut_4 = DI.NUTRUNNER1_IN4;

                    _out_Nut_4 = DO.NUTRUNNER1_OUT4;
                    //_out_Counter_1 = DO.ST1_COUNTER_UP1;
                    break;

                case 1:
                    _in_Tip1 = DI.STATION2_TIP1;
                    _in_Nut_1 = DI.NUTRUNNER2_IN1;
                    _in_Nut_2 = DI.NUTRUNNER2_IN2;
                    _in_Nut_3 = DI.NUTRUNNER2_IN3;
                    _in_Nut_4 = DI.NUTRUNNER2_IN4;

                    _out_Nut_4 = DO.NUTRUNNER2_OUT4;
                    //_out_Counter_1 = DO.ST2_COUNTER_UP1;
                    break;

                case 2:
                    _in_Tip1 = DI.STATION3_TIP1;
                    _in_Nut_1 = DI.NUTRUNNER3_IN1;
                    _in_Nut_2 = DI.NUTRUNNER3_IN2;
                    _in_Nut_3 = DI.NUTRUNNER3_IN3;
                    _in_Nut_4 = DI.NUTRUNNER3_IN4;

                    _out_Nut_4 = DO.NUTRUNNER3_OUT4;
                    // _out_Counter_1 = DO.ST3_COUNTER_UP1;
                    break;

                case 3:
                    _in_Tip1 = DI.STATION4_TIP1;
                    _in_Nut_1 = DI.NUTRUNNER4_IN1;
                    _in_Nut_2 = DI.NUTRUNNER4_IN2;
                    _in_Nut_3 = DI.NUTRUNNER4_IN3;
                    _in_Nut_4 = DI.NUTRUNNER4_IN4;

                    _out_Nut_4 = DO.NUTRUNNER4_OUT4;
                    // _out_Counter_1 = DO.ST4_COUNTER_UP1;
                    break;

                case 4:
                    _in_Tip1 = DI.STATION5_TIP1;
                    _in_Nut_1 = DI.NUTRUNNER5_IN1;
                    _in_Nut_2 = DI.NUTRUNNER5_IN2;
                    _in_Nut_3 = DI.NUTRUNNER5_IN3;
                    _in_Nut_4 = DI.NUTRUNNER5_IN4;

                    _out_Nut_4 = DO.NUTRUNNER5_OUT4;
                    // _out_Counter_1 = DO.ST4_COUNTER_UP1;
                    break;

                case 5:
                    _in_Tip1 = DI.LIFT_TIP1;
                    _in_Nut_1 = DI.NUTRUNNER6_IN1;
                    _in_Nut_2 = DI.NUTRUNNER6_IN2;
                    _in_Nut_3 = DI.NUTRUNNER6_IN3;
                    _in_Nut_4 = DI.NUTRUNNER6_IN4;

                    _out_Nut_4 = DO.NUTRUNNER_LIFT_OUT4;
                    // _out_Counter_1 = DO.ST4_COUNTER_UP1;
                    break;

            }
            #endregion



            // ST1 엔코더 기능을 사용하는 경우
            if (_ModelInfo.bUseST2Encoder && nStation == 1)
            {

                // 맥스 카운트
                _SysInfo.nTipMaxCount[nStation, 0] = _ModelInfo._ST2Tip.Count(x => x.nTip == 1);
                _SysInfo.nTipMaxCount[nStation, 1] = _ModelInfo._ST2Tip.Count(x => x.nTip == 2);
                _SysInfo.nTipMaxCount[nStation, 2] = _ModelInfo._ST2Tip.Count(x => x.nTip == 3);
                _SysInfo.nTipMaxCount[nStation, 3] = _ModelInfo._ST2Tip.Count(x => x.nTip == 4);
                _SysInfo.nTipMaxCount[nStation, 4] = _ModelInfo._ST2Tip.Count(x => x.nTip == 5);


                // 현재 카운트
                _SysInfo.nTipNowCount[nStation, 0] = _ModelInfo._ST2Tip.Take(_SysInfo.nST2TiteWorkCount).Count(x => x.nTip == 1);
                _SysInfo.nTipNowCount[nStation, 1] = _ModelInfo._ST2Tip.Take(_SysInfo.nST2TiteWorkCount).Count(x => x.nTip == 2);
                _SysInfo.nTipNowCount[nStation, 2] = _ModelInfo._ST2Tip.Take(_SysInfo.nST2TiteWorkCount).Count(x => x.nTip == 3);
                _SysInfo.nTipNowCount[nStation, 3] = _ModelInfo._ST2Tip.Take(_SysInfo.nST2TiteWorkCount).Count(x => x.nTip == 4);
                _SysInfo.nTipNowCount[nStation, 4] = _ModelInfo._ST2Tip.Take(_SysInfo.nST2TiteWorkCount).Count(x => x.nTip == 5);


                // 사용팁 개수 및 팁 확인
                for (int i = 0; i < 5; i++)
                {
                    if (!GetDIOPort(_in_Tip1 + i))
                    {
                        nUseTipCount++;
                        nUseTip = i;
                    }
                }

                _SysInfo.nNowUseTip[nStation] = nUseTip;
                _SysInfo.nNowUseTipCount[nStation] = nUseTipCount;


                if (_SysInfo.nTipNowCount[nStation, 0] >= _SysInfo.nTipMaxCount[nStation, 0] &&
                    _SysInfo.nTipNowCount[nStation, 1] >= _SysInfo.nTipMaxCount[nStation, 1] &&
                    _SysInfo.nTipNowCount[nStation, 2] >= _SysInfo.nTipMaxCount[nStation, 2] &&
                    _SysInfo.nTipNowCount[nStation, 3] >= _SysInfo.nTipMaxCount[nStation, 3] &&
                    _SysInfo.nTipNowCount[nStation, 4] >= _SysInfo.nTipMaxCount[nStation, 4])
                {
                    _SysInfo.bTiteOk[nStation] = true;
                }
                else
                {
                    _SysInfo.bTiteOk[nStation] = false;
                }



                switch (nProcessStep[nStepIndex])
                {
                    case 0:
                        if (!GetDIOPort(_in_Nut_1) && !GetDIOPort(_in_Nut_2) && !GetDIOPort(_in_Nut_3))
                        {
                            //_SysInfo.nPsetOldIndex[nStation] = 0;       // Old Status 클리어하여 스케쥴 재할당 가능토록 변경
                            _SysInfo.bST2TiteIng = false;
                            nProcessStep[nStepIndex]++;
                        }
                        break;


                    case 1:
                        //// 위치 추적하여 토크하고 팁 설정
                        //if (_ModelInfo._ST1Tip.Count(x => x.nX + _ModelInfo.nST1EncoderRange >= _SysInfo.nST1EncoderX && x.nX - _ModelInfo.nST1EncoderRange <= _SysInfo.nST1EncoderX &&
                        //                                        x.nY + _ModelInfo.nST1EncoderRange >= _SysInfo.nST1EncoderY && x.nY - _ModelInfo.nST1EncoderRange <= _SysInfo.nST1EncoderY) == 1)
                        //{
                        //    ST1_TIP_INFO _temp = _ModelInfo._ST1Tip.Find(x => x.nX + _ModelInfo.nST1EncoderRange >= _SysInfo.nST1EncoderX && x.nX - _ModelInfo.nST1EncoderRange <= _SysInfo.nST1EncoderX &&
                        //                                        x.nY + _ModelInfo.nST1EncoderRange >= _SysInfo.nST1EncoderY && x.nY - _ModelInfo.nST1EncoderRange <= _SysInfo.nST1EncoderY);


                        //    SetNutRunnerSch(nStation, _temp.nSch + 1);   // 너트러너 스케줄 설정

                        //    // 해당 포인트가 체결 완료된 경우
                        //    if (_temp.bTiteOk)
                        //    {
                        //        SetDIOPort(_out_Nut_4, true);   // 너트러너 잠금

                        //        // 완료된 자리에서 입력이 들어올 경우
                        //        if (GetDIOPort(_in_Nut_3))
                        //        {
                        //            _SysInfo.nTiteLog[nStation] = 3;

                        //            AppendLogMsg(String.Format("Station #{0} - 체결 완료된 위치 입니다.", nStation + 1), LOG_TYPE.ERROR);
                        //            _SysInfo.nCount_Beep[nStation] = 3;
                        //            nProcessStep[nStepIndex] = 0;

                        //        }
                        //    }
                        //    else
                        //    {
                        //        //SetDIOPort(_out_Nut_4, false);   // 너트러너 잠금 해제

                        //        // 선택팁 개수가 1개이상이거나, 0개이거나, 팁이 일치 하지 않는다면
                        //        if (nUseTipCount > 1 || nUseTipCount == 0 ||
                        //            _temp.nTip != nUseTip + 1)
                        //        {
                        //            SetDIOPort(_out_Nut_4, true);   // 너트러너 잠금

                        //            // 완료된 자리에서 입력이 들어올 경우
                        //            if (GetDIOPort(_in_Nut_3))
                        //            {
                        //                _SysInfo.nTiteLog[nStation] = 3;

                        //                AppendLogMsg(String.Format("Station #{0} - 팁 선택 오류.", nStation + 1), LOG_TYPE.ERROR);
                        //                _SysInfo.nCount_Beep[nStation] = 3;
                        //                nProcessStep[nStepIndex] = 0;

                        //            }
                        //        }
                        //        else
                        //        {
                        //            SetDIOPort(_out_Nut_4, false);   // 너트러너 잠금 해제

                        //            // 체결작업 진행
                        //            if (GetDIOPort(_in_Nut_1))
                        //            {
                        //                _SysInfo.nTiteLog[nStation] = 2;
                        //                _ModelInfo._ST1Tip.Find(x => x.nX + _ModelInfo.nST1EncoderRange >= _SysInfo.nST1EncoderX && x.nX - _ModelInfo.nST1EncoderRange <= _SysInfo.nST1EncoderX &&
                        //                                            x.nY + _ModelInfo.nST1EncoderRange >= _SysInfo.nST1EncoderY && x.nY - _ModelInfo.nST1EncoderRange <= _SysInfo.nST1EncoderY).bTiteOk = true;
                        //                nProcessStep[nStepIndex]++;

                        //            }
                        //            else if (GetDIOPort(_in_Nut_2))
                        //            {
                        //                _SysInfo.nTiteLog[nStation] = 3;

                        //                AppendLogMsg(String.Format("Station #{0} - 팁 체결 불량", nStation + 1), LOG_TYPE.ERROR);
                        //                _SysInfo.nCount_Beep[nStation] = 3;
                        //                nProcessStep[nStepIndex] = 0;
                        //            }
                        //        }

                        //    }

                        //}
                        //else
                        //{


                        //    SetDIOPort(_out_Nut_4, true);   // 너트러너 잠금

                        //    if (GetDIOPort(_in_Nut_3))
                        //    {
                        //        _SysInfo.nTiteLog[nStation] = 3;

                        //        AppendLogMsg(String.Format("Station #{0} - 체결 위치 에러.", nStation + 1), LOG_TYPE.ERROR);
                        //        _SysInfo.nCount_Beep[nStation] = 3;
                        //        nProcessStep[nStepIndex] = 0;

                        //    }

                        //}
                        // 순차적인 체결 모드
                        if (_SysInfo.nST2TiteWorkCount < _ModelInfo._ST2Tip.Count)
                        {
                            // 변경 => 범위내에 없어도 스텝에 맞춰 스케쥴 변경 2020.04.17 김상구D 요청
                            SetNutRunnerSch(nStation, _ModelInfo._ST2Tip[_SysInfo.nST2TiteWorkCount].nSch + 1);   // 너트러너 스케줄 설정

                            if (_ModelInfo._ST2Tip[_SysInfo.nST2TiteWorkCount].nX + _ModelInfo.nST2EncoderRange >= _SysInfo.nST2EncoderX &&
                                _ModelInfo._ST2Tip[_SysInfo.nST2TiteWorkCount].nX - _ModelInfo.nST2EncoderRange <= _SysInfo.nST2EncoderX &&
                                _ModelInfo._ST2Tip[_SysInfo.nST2TiteWorkCount].nY + _ModelInfo.nST2EncoderRange >= _SysInfo.nST2EncoderY &&
                                _ModelInfo._ST2Tip[_SysInfo.nST2TiteWorkCount].nY - _ModelInfo.nST2EncoderRange <= _SysInfo.nST2EncoderY)
                            {
                                // 범위내에 있다면
                                // 선택팁 개수가 1개이상이거나, 0개이거나, 팁이 일치 하지 않는다면
                                if (nUseTipCount > 1 || nUseTipCount == 0 ||
                                     _ModelInfo._ST2Tip[_SysInfo.nST2TiteWorkCount].nTip != nUseTip + 1)
                                {
                                    SetDIOPort(_out_Nut_4, true);   // 너트러너 잠금

                                    // 완료된 자리에서 입력이 들어올 경우
                                    if (GetDIOPort(_in_Nut_3))
                                    {
                                        _SysInfo.nTiteLog[nStation] = 3;

                                        AppendLogMsg(String.Format("Station #{0} - 팁 선택 오류.", nStation + 1), LOG_TYPE.ERROR);
                                        _SysInfo.nCount_Beep[nStation] = 3;
                                        nProcessStep[nStepIndex] = 0;

                                    }
                                }
                                else
                                {
                                    SetDIOPort(_out_Nut_4, false);   // 너트러너 잠금 해제

                                    if (GetDIOPort(_in_Nut_3))
                                    {
                                        _SysInfo.bST2TiteIng = true;
                                    }


                                    // 체결작업 진행
                                    if (GetDIOPort(_in_Nut_1))
                                    {
                                        // OK 시그널이 들어옴
                                        _NutRunner[nStation].nTiteX = _SysInfo.nST2EncoderX;    // 엔코더 X위치 너트러너에 기입
                                        _NutRunner[nStation].nTiteY = _SysInfo.nST2EncoderY;    // 엔코더 Y위치 너트러너에 기입
                                        _NutRunner[nStation].nTiteNum = _SysInfo.nST2TiteWorkCount;

                                        //if (_Config.bUseNutrunnerCommCompare)
                                        //{
                                        //    // 너트러너 데이터 비교 기능을 사용하는 경우
                                        //    nProcessStep[nStepIndex] = 10;
                                        //    tMainTimer[nStepIndex].Start(5000);     // 5초동안 응답없을경우 NG로 판정
                                        //    _NutRunner[nStation].bDataRead = false;
                                        //}
                                        //else
                                        //{

                                            _SysInfo.nST2TiteWorkCount++;
                                            _SysInfo.nTiteLog[nStation] = 2;
                                            nProcessStep[nStepIndex]++;
                                        //}


                                    }
                                    else if (GetDIOPort(_in_Nut_2))
                                    {
                                        // NG 시그널이 들어옴
                                        _NutRunner[nStation].nTiteX = _SysInfo.nST2EncoderX;    // 엔코더 X위치 너트러너에 기입
                                        _NutRunner[nStation].nTiteY = _SysInfo.nST2EncoderY;    // 엔코더 Y위치 너트러너에 기입
                                        _NutRunner[nStation].nTiteNum = _SysInfo.nST2TiteWorkCount;

                                        _SysInfo.nTiteLog[nStation] = 3;
                                        AppendLogMsg(String.Format("Station #{0} - 팁 체결 불량", nStation + 1), LOG_TYPE.ERROR);
                                        _SysInfo.nCount_Beep[nStation] = 3;
                                        nProcessStep[nStepIndex] = 0;
                                    }
                                }
                            }
                            else
                            {
                                // 범위 밖이라면
                                if (!GetDIOPort(_in_Nut_3))
                                {
                                    _SysInfo.bST2TiteIng = false;
                                }

                                if (_SysInfo.bST2TiteIng)
                                {
                                    // 체결작업 진행
                                    if (GetDIOPort(_in_Nut_1))
                                    {
                                        // OK 시그널이 들어옴
                                        _NutRunner[nStation].nTiteX = _SysInfo.nST2EncoderX;    // 엔코더 X위치 너트러너에 기입
                                        _NutRunner[nStation].nTiteY = _SysInfo.nST2EncoderY;    // 엔코더 Y위치 너트러너에 기입
                                        _NutRunner[nStation].nTiteNum = _SysInfo.nST2TiteWorkCount;
                                        _SysInfo.nST2TiteWorkCount++;
                                        _SysInfo.nTiteLog[nStation] = 2;
                                        nProcessStep[nStepIndex]++;

                                    }
                                    else if (GetDIOPort(_in_Nut_2))
                                    {
                                        // NG 시그널이 들어옴
                                        _NutRunner[nStation].nTiteX = _SysInfo.nST2EncoderX;    // 엔코더 X위치 너트러너에 기입
                                        _NutRunner[nStation].nTiteY = _SysInfo.nST2EncoderY;    // 엔코더 Y위치 너트러너에 기입
                                        _NutRunner[nStation].nTiteNum = _SysInfo.nST2TiteWorkCount;
                                        _SysInfo.nTiteLog[nStation] = 3;
                                        AppendLogMsg(String.Format("Station #{0} - 팁 체결 불량", nStation + 1), LOG_TYPE.ERROR);
                                        _SysInfo.nCount_Beep[nStation] = 3;
                                        nProcessStep[nStepIndex] = 0;
                                    }
                                }
                                else
                                {
                                    SetDIOPort(_out_Nut_4, true);   // 너트러너 잠금
                                }



                                // 완료된 자리에서 입력이 들어올 경우
                                if (GetDIOPort(_in_Nut_3) && !_SysInfo.bST2TiteIng)
                                {
                                    _SysInfo.nTiteLog[nStation] = 3;

                                    AppendLogMsg(String.Format("Station #{0} - 체결 위치 에러.", nStation + 1), LOG_TYPE.ERROR);
                                    _SysInfo.nCount_Beep[nStation] = 3;
                                    nProcessStep[nStepIndex] = 0;

                                }
                            }
                        }
                        else
                        {


                            SetDIOPort(_out_Nut_4, true);   // 너트러너 잠금

                            if (GetDIOPort(_in_Nut_3))
                            {
                                _SysInfo.nTiteLog[nStation] = 3;

                                AppendLogMsg(String.Format("Station #{0} - 체결 작업이 완료되었습니다.", nStation + 1), LOG_TYPE.ERROR);
                                _SysInfo.nCount_Beep[nStation] = 3;
                                nProcessStep[nStepIndex] = 0;

                            }

                        }
                        break;

                    case 2:
                        //SetDIOPort(_out_Counter_1 + nUseTip, true);
                        //_SysInfo.nTipNowCount[nStation, nUseTip]++;
                        //SaveSTLockInfo(nStation);
                        if (_SysInfo.nTipNowCount[nStation, nUseTip] >= _SysInfo.nTipMaxCount[nStation, nUseTip])
                        {
                            _SysInfo.nCount_Beep[nStation] = 2;
                        }
                        else
                        {
                            _SysInfo.nCount_Beep[nStation] = 1;
                        }
                        tMainTimer[nStepIndex].Start(100);
                        nProcessStep[nStepIndex]++;
                        break;

                    case 3:
                        if (tMainTimer[nStepIndex].Verify())
                        {
                            //SetDIOPort(_out_Counter_1 + nUseTip, false);
                            nProcessStep[nStepIndex] = 0;
                        }
                        break;



                    // 데이터 기반 OK, NG 판정 기능 추가
                    //case 10:
                    //    if (tMainTimer[nStepIndex].Verify())
                    //    {
                    //        // 타임아웃 행정
                    //        _SysInfo.nTiteLog[nStation] = 3;
                    //        nProcessStep[nStepIndex] = 0;
                    //    }


                    //    if (_NutRunner[nStation].bDataRead)          // 데이터가 정상적으로 들어왔을경우
                    //    {
                    //        if (_Config.dbTorqueSepcMin[nStation, _ModelInfo._ST2Tip[_SysInfo.nST2TiteWorkCount].nSch] <= _NutRunner[nStation].dbTorqueData * 0.01 &&
                    //            _Config.dbTorqueSepcMax[nStation, _ModelInfo._ST2Tip[_SysInfo.nST2TiteWorkCount].nSch] >= _NutRunner[nStation].dbTorqueData * 0.01 &&
                    //            _Config.nAngleSepcMin[nStation, _ModelInfo._ST2Tip[_SysInfo.nST2TiteWorkCount].nSch] <= _NutRunner[nStation].nAngleData &&
                    //            _Config.nAngleSepcMax[nStation, _ModelInfo._ST2Tip[_SysInfo.nST2TiteWorkCount].nSch] >= _NutRunner[nStation].nAngleData)
                    //        {
                    //            // 토크와 앵글이 정상 스펙 이내라면
                    //            _SysInfo.nST2TiteWorkCount++;
                    //            _SysInfo.nTiteLog[nStation] = 2;
                    //            nProcessStep[nStepIndex]++;
                    //        }
                    //        else
                    //        {
                    //            // 아니라면
                    //            _SysInfo.nTiteLog[nStation] = 3;
                    //            AppendLogMsg(String.Format("Station #{0} - 팁 체결 불량", nStation + 1), LOG_TYPE.ERROR);
                    //            _SysInfo.nCount_Beep[nStation] = 3;
                    //            nProcessStep[nStepIndex] = 0;
                    //        }
                    //    }
                    //    break;


                    //case 11:
                    //    //SetDIOPort(_out_Counter_1 + nUseTip, true);
                    //    //_SysInfo.nTipNowCount[nStation, nUseTip]++;
                    //    //SaveSTLockInfo(nStation);
                    //    if (_SysInfo.nTipNowCount[nStation, nUseTip] >= _SysInfo.nTipMaxCount[nStation, nUseTip])
                    //    {
                    //        _SysInfo.nCount_Beep[nStation] = 2;
                    //    }
                    //    else
                    //    {
                    //        _SysInfo.nCount_Beep[nStation] = 1;
                    //    }
                    //    tMainTimer[nStepIndex].Start(100);
                    //    nProcessStep[nStepIndex]++;
                    //    break;

                    //case 12:
                    //    if (tMainTimer[nStepIndex].Verify())
                    //    {
                    //        //SetDIOPort(_out_Counter_1 + nUseTip, false);
                    //        nProcessStep[nStepIndex] = 0;
                    //    }
                    //    break;
                }







            }
            else
            {

                // 맥스 카운트
                _SysInfo.nTipMaxCount[nStation, 0] = _ModelInfo._TipInfo[nStation].nTipMaxCount[0];
                _SysInfo.nTipMaxCount[nStation, 1] = _ModelInfo._TipInfo[nStation].nTipMaxCount[1];
                _SysInfo.nTipMaxCount[nStation, 2] = _ModelInfo._TipInfo[nStation].nTipMaxCount[2];
                _SysInfo.nTipMaxCount[nStation, 3] = _ModelInfo._TipInfo[nStation].nTipMaxCount[3];
                _SysInfo.nTipMaxCount[nStation, 4] = _ModelInfo._TipInfo[nStation].nTipMaxCount[4];


                // 사용팁 개수 및 팁 확인
                for (int i = 0; i < 5; i++)
                {
                    if (!GetDIOPort(_in_Tip1 + i))
                    {
                        nUseTipCount++;
                        nUseTip = i;
                    }
                }

                _SysInfo.nNowUseTip[nStation] = nUseTip;
                _SysInfo.nNowUseTipCount[nStation] = nUseTipCount;


                if (_SysInfo.nTipNowCount[nStation, 0] >= _ModelInfo._TipInfo[nStation].nTipMaxCount[0] &&
                    _SysInfo.nTipNowCount[nStation, 1] >= _ModelInfo._TipInfo[nStation].nTipMaxCount[1] &&
                    _SysInfo.nTipNowCount[nStation, 2] >= _ModelInfo._TipInfo[nStation].nTipMaxCount[2] &&
                    _SysInfo.nTipNowCount[nStation, 3] >= _ModelInfo._TipInfo[nStation].nTipMaxCount[3] &&
                    _SysInfo.nTipNowCount[nStation, 4] >= _ModelInfo._TipInfo[nStation].nTipMaxCount[4])
                {
                    _SysInfo.bTiteOk[nStation] = true;
                }
                else
                {
                    _SysInfo.bTiteOk[nStation] = false;
                }



                //if (!_SysInfo.bTite_Ing[nStation]) { return; }      // 체결 작업 가능 시점이 아닐땐 그냥 리턴


                // 선택팁 개수가 1개이상이거나, 0개이거나, 해당팁이 체결 완료된 팁이라면
                if (nUseTipCount > 1 || nUseTipCount == 0 ||
                    _SysInfo.nTipNowCount[nStation, nUseTip] >= _ModelInfo._TipInfo[nStation].nTipMaxCount[nUseTip])
                {
                    SetDIOPort(_out_Nut_4, true);   // 너트러너 잠금
                }
                else
                {
                    SetDIOPort(_out_Nut_4, false);  // 너트러너 잠금 해제
                }

               if (nUseTipCount == 1)
               {
                   SetNutRunnerSch(nStation, _ModelInfo._TipInfo[nStation].nTipSch[nUseTip] + 1);   // 너트러너 스케줄 설정
               }
                //if (nUseTipCount == 1)
                //{

                //    if (_ModelInfo._TipInfo[nStation].nSpare_a[nUseTip] > 0)
                //    {
                //        if (_SysInfo.nTipNowCount[nStation, nUseTip] >= _ModelInfo._TipInfo[nStation].nTipMaxCount[nUseTip + 5])
                //        {
                //            SetNutRunnerSch(nStation, _ModelInfo._TipInfo[nStation].nTipSch[nUseTip + 5] + 1);   // Torque 2번보다 카운트가 클경우 토크 2번에 저장된 데이터 사용
                //            _SysInfo.nNowSch[nStation] = _ModelInfo._TipInfo[nStation].nTipSch[nUseTip + 5];
                //        }
                //        else
                //        {
                //            SetNutRunnerSch(nStation, _ModelInfo._TipInfo[nStation].nTipSch[nUseTip] + 1);   // 너트러너 스케줄 설정
                //            _SysInfo.nNowSch[nStation] = _ModelInfo._TipInfo[nStation].nTipSch[nUseTip];
                //        }
                //    }
                //    else
                //    {
                //        SetNutRunnerSch(nStation, _ModelInfo._TipInfo[nStation].nTipSch[nUseTip] + 1);   // 너트러너 스케줄 설정
                //        _SysInfo.nNowSch[nStation] = _ModelInfo._TipInfo[nStation].nTipSch[nUseTip];
                //    }

                    //SetNutRunnerSch(nStation, _ModelInfo._TipInfo[nStation].nTipSch[nUseTip] + 1);   // 너트러너 스케줄 설정
                //}

                switch (nProcessStep[nStepIndex])
                {
                    case 0:
                        if (!GetDIOPort(_in_Nut_1) && !GetDIOPort(_in_Nut_2) && !GetDIOPort(_in_Nut_3))
                        {
                            //_SysInfo.nPsetOldIndex[nStation] = 0;
                            nProcessStep[nStepIndex]++;
                        }
                        break;

                    case 1:
                        if (GetDIOPort(_in_Nut_3))
                        {
                            _SysInfo.nTiteLog[nStation] = 1;
                        }


                        if (GetDIOPort(_in_Nut_1) && nUseTipCount == 1)
                        {
                            //if (_Config.bUseNutrunnerCommCompare)
                            //{
                            //    // 너트러너 데이터 비교 기능을 사용하는 경우
                            //    nProcessStep[nStepIndex] = 10;
                            //    tMainTimer[nStepIndex].Start(5000);     // 5초동안 응답없을경우 NG로 판정
                            //    _NutRunner[nStation].bDataRead = false;
                            //}
                            //else
                            //{
                                _SysInfo.nTiteLog[nStation] = 2;
                                _NutRunner[nStation].nTiteNum = (_SysInfo.nTipNowCount[nStation, 0] + _SysInfo.nTipNowCount[nStation, 1] + _SysInfo.nTipNowCount[nStation, 2] + _SysInfo.nTipNowCount[nStation, 3] + _SysInfo.nTipNowCount[nStation, 4]) + 1;
                                nProcessStep[nStepIndex]++;
                            //}
                        }
                        else if (GetDIOPort(_in_Nut_2) && nUseTipCount == 1)
                        {
                            _SysInfo.nTiteLog[nStation] = 3;

                            AppendLogMsg(String.Format("Station #{0} - 팁 체결 불량", nStation + 1), LOG_TYPE.ERROR);
                            _SysInfo.nCount_Beep[nStation] = 3;
                            nProcessStep[nStepIndex] = 0;
                        }
                        else if (GetDIOPort(_in_Nut_3) && nUseTipCount != 1)
                        {
                            AppendLogMsg(String.Format("Station #{0} - 팁 선택 오류", nStation + 1), LOG_TYPE.ERROR);
                            _SysInfo.nCount_Beep[nStation] = 3;
                            nProcessStep[nStepIndex] = 0;
                        }
                        else if (GetDIOPort(_in_Nut_3) && _SysInfo.nTipNowCount[nStation, nUseTip] >= _ModelInfo._TipInfo[nStation].nTipMaxCount[nUseTip])
                        {
                            AppendLogMsg(String.Format("Station #{0} - 해당 팁 체결 완료", nStation + 1), LOG_TYPE.ERROR);
                            _SysInfo.nCount_Beep[nStation] = 3;
                            nProcessStep[nStepIndex] = 0;
                        }
                        break;

                    case 2:
                        //SetDIOPort(_out_Counter_1 + nUseTip, true);
                        _SysInfo.nTipNowCount[nStation, nUseTip]++;
                        SaveSTLockInfo(nStation);
                        if (_SysInfo.nTipNowCount[nStation, nUseTip] >= _ModelInfo._TipInfo[nStation].nTipMaxCount[nUseTip])
                        {
                            _SysInfo.nCount_Beep[nStation] = 2;
                        }
                        else
                        {
                            _SysInfo.nCount_Beep[nStation] = 1;
                        }
                        tMainTimer[nStepIndex].Start(100);
                        nProcessStep[nStepIndex]++;
                        break;

                    case 3:
                        if (tMainTimer[nStepIndex].Verify())
                        {
                            //SetDIOPort(_out_Counter_1 + nUseTip, false);
                            nProcessStep[nStepIndex] = 0;
                        }
                        break;




                    //// 데이터 기반 OK, NG 판정 기능 추가
                    //case 10:
                    //    if (tMainTimer[nStepIndex].Verify())
                    //    {
                    //        // 타임아웃 행정
                    //        _SysInfo.nTiteLog[nStation] = 3;
                    //        AppendLogMsg(String.Format("Station #{0} - 팁 체결 불량", nStation + 1), LOG_TYPE.ERROR);
                    //        _SysInfo.nCount_Beep[nStation] = 3;
                    //        nProcessStep[nStepIndex] = 0;
                    //    }


                    //    if (_NutRunner[nStation].bDataRead)          // 데이터가 정상적으로 들어왔을경우
                    //    {
                    //        if (_Config.dbTorqueSepcMin[nStation, _SysInfo.nNowSch[nStation]] <= _NutRunner[nStation].dbTorqueData * 0.01 &&
                    //            _Config.dbTorqueSepcMax[nStation, _SysInfo.nNowSch[nStation]] >= _NutRunner[nStation].dbTorqueData * 0.01 &&
                    //            _Config.nAngleSepcMin[nStation, _SysInfo.nNowSch[nStation]] <= _NutRunner[nStation].nAngleData &&
                    //            _Config.nAngleSepcMax[nStation, _SysInfo.nNowSch[nStation]] >= _NutRunner[nStation].nAngleData)
                    //        {
                    //            // 토크와 앵글이 정상 스펙 이내라면
                    //            _SysInfo.nTiteLog[nStation] = 2;
                    //            nProcessStep[nStepIndex]++;
                    //        }
                    //        else
                    //        {
                    //            // 아니라면
                    //            _SysInfo.nTiteLog[nStation] = 3;
                    //            AppendLogMsg(String.Format("Station #{0} - 팁 체결 불량", nStation + 1), LOG_TYPE.ERROR);
                    //            _SysInfo.nCount_Beep[nStation] = 3;
                    //            nProcessStep[nStepIndex] = 0;
                    //        }
                    //    }
                    //    break;


                    //case 11:
                    //    //SetDIOPort(_out_Counter_1 + nUseTip, true);
                    //    _SysInfo.nTipNowCount[nStation, nUseTip]++;
                    //    SaveSTLockInfo(nStation);
                    //    if (_SysInfo.nTipNowCount[nStation, nUseTip] >= _ModelInfo._TipInfo[nStation].nTipMaxCount[nUseTip])
                    //    {
                    //        _SysInfo.nCount_Beep[nStation] = 2;
                    //    }
                    //    else
                    //    {
                    //        _SysInfo.nCount_Beep[nStation] = 1;
                    //    }
                    //    tMainTimer[nStepIndex].Start(100);
                    //    nProcessStep[nStepIndex]++;
                    //    break;

                    //case 12:
                    //    if (tMainTimer[nStepIndex].Verify())
                    //    {
                    //        //SetDIOPort(_out_Counter_1 + nUseTip, false);
                    //        nProcessStep[nStepIndex] = 0;
                    //    }
                    //    break;
                }
            }

        }






        //====== 적재 프로세스 ======================================
        static int SUB_LOADING_PROCESS(int nLoadStep)
        {
            int nStepIndex = (int)PROC_LIST.SUB_LOADING;

            switch (nProcessStep[nStepIndex])
            {
                case 0:
                    _SysInfo.bPackLoadFail = false;
                    nProcessStep[nStepIndex] = 100;
                    break;

                // 제품 회전 스텝
                case 100:
                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y) || !MotionDone(AXIS.Z)) { break; }

                    MoveTo(AXIS.Z, _Config.dbSafeLoadZPos, _ModelInfo.dbClampZMoveSpeed);      // Z축 안전위치로 이동
                    nProcessStep[nStepIndex]++;
                    break;

                case 101:
                    if (!MotionDone(AXIS.Z)) { break; }

                    if (CheckMotionPosErr(AXIS.Z, _Config.dbSafeLoadZPos))
                    {
                        _SysInfo.bPackLoadFail = true;
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }

                    if (!_ModelInfo._Loading[nLoadStep].bUse)
                    { nProcessStep[nStepIndex] = 0; break; }


                    // PC Sheet 부착행정 점프
                    if (_ModelInfo.bUseLandingPCSheet)
                    {
                        // Landing시 PC Sheet 부착 기능을 사용한다면
                        if (nLoadStep == 0 || nLoadStep == _ModelInfo.nCmaCount - 1)
                        {
                            // 첫번째 CMA 일 경우
                            nProcessStep[nStepIndex] = 300;
                            break;
                        }
                    }




                    if (_ModelInfo._Loading[nLoadStep].nType == 0)          // 0도 일때
                    {
                        if (Math.Abs(0 - GetNowPos(AXIS.R)) < 1)
                        {
                            _SysInfo.bMoveClampPickUpComplate = true;
                            nProcessStep[nStepIndex] = 200;
                        }
                        else
                        {
                            nProcessStep[nStepIndex] = 110;
                        }

                    }
                    else if (_ModelInfo._Loading[nLoadStep].nType == 1)     // 90도 일때
                    {
                        if (Math.Abs(-90 - GetNowPos(AXIS.R)) < 1)
                        {
                            _SysInfo.bMoveClampPickUpComplate = true;
                            nProcessStep[nStepIndex] = 200;
                        }
                        else
                        {
                            nProcessStep[nStepIndex] = 110;
                        }
                    }
                    else if (_ModelInfo._Loading[nLoadStep].nType == 2)     // 180도 일때
                    {
                        if (Math.Abs(-180 - GetNowPos(AXIS.R)) < 1)
                        {
                            _SysInfo.bMoveClampPickUpComplate = true;
                            nProcessStep[nStepIndex] = 200;
                        }
                        else
                        {
                            nProcessStep[nStepIndex] = 110;
                        }
                    }
                    else if (_ModelInfo._Loading[nLoadStep].nType == 3)     // -90도 일때
                    {
                        if (Math.Abs(90 - GetNowPos(AXIS.R)) < 1)
                        {
                            _SysInfo.bMoveClampPickUpComplate = true;
                            nProcessStep[nStepIndex] = 200;
                        }
                        else
                        {
                            nProcessStep[nStepIndex] = 110;
                        }
                    }
                    else
                    {
                        _SysInfo.bPackLoadFail = true;
                        AppendLogMsg("해당 팩 모델설정 에러", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 0;

                    }
                    break;

                // 제품 회전위치로 이동 역방향일때
                case 102:
                    if (!GetLoadingDoor()) { break; }

                    MoveToXY(_ModelInfo.dbTurnPosX, _ModelInfo.dbTurnPosY, _ModelInfo.dbClampXYMoveSpeed);   // XY축 제품 회전위치로 이동
                    nProcessStep[nStepIndex]++;
                    break;

                case 103:
                    if (!GetLoadingDoor())
                    {
                        CAXM.AxmMoveEStop((int)AXIS.X);
                        CAXM.AxmMoveEStop((int)AXIS.Y);
                        nProcessStep[nStepIndex] = 102;
                        break;
                    }

                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y) || !MotionDone(AXIS.Z)) { break; }

                    if (CheckMotionPosErr(AXIS.X, _ModelInfo.dbTurnPosX))
                    {
                        _SysInfo.bPackLoadFail = true;
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }

                    if (CheckMotionPosErr(AXIS.Y, _ModelInfo.dbTurnPosY))
                    {
                        _SysInfo.bPackLoadFail = true;
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }

                    //SetDIOPort(DO.LOADING_ROTATE_ON, true);
                    //SetDIOPort(DO.LOADING_ROTATE_OFF, false);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 104:
                    //if(tMainTimer[nStepIndex].Verify())
                    //{
                    //    if (!GetDioPort(DI.LOADING_ROTATE_ON)) { AppendTimeOutMsg(DI.LOADING_ROTATE_ON); }
                    //    _SysInfo.bPackLoadFail = true;
                    //    nProcessStep[nStepIndex] = 0;
                    //}

                    //if (GetDioPort(DI.LOADING_ROTATE_ON))
                    //{
                    //    nProcessStep[nStepIndex] = 200;
                    //}
                    break;


                // 정방향일때
                case 110:
                    //if (!GetLoadingDoor()) { break; }             // 상구팀장 요청 Door 감시 해제 19.09.17

                    MoveToXY(_ModelInfo.dbTurnPosX, _ModelInfo.dbTurnPosY, _ModelInfo.dbClampXYMoveSpeed);   // XY축 제품 회전위치로 이동
                    nProcessStep[nStepIndex]++;
                    break;

                case 111:
                    //if (!GetLoadingDoor())
                    //{
                    //    CAXM.AxmMoveEStop((int)AXIS.X);
                    //    CAXM.AxmMoveEStop((int)AXIS.Y);
                    //    nProcessStep[nStepIndex] = 110;
                    //    break;
                    //}


                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y) || !MotionDone(AXIS.Z)) { break; }


                    if (CheckMotionPosErr(AXIS.X, _ModelInfo.dbTurnPosX))
                    {
                        _SysInfo.bPackLoadFail = true;
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }

                    if (CheckMotionPosErr(AXIS.Y, _ModelInfo.dbTurnPosY))
                    {
                        _SysInfo.bPackLoadFail = true;
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }

                    if (_ModelInfo.dbTurnPosX > _ModelInfo._Loading[nLoadStep].dbX)
                    {
                        // 모델 설정된 X좌표가 회전위치보다 작다면 ( Station 방향 움직임이라면 )
                        // X,Y축 적재위치로 이동명령 함께 동작
                        //if(_ModelInfo.bUseCmaBizPcSheetLanding)
                        //{
                        //    MoveToXY(_ModelInfo.dbLoadingJigTestPos1X, _ModelInfo.dbLoadingJigTestPos1Y, _ModelInfo.dbClampXYMoveSpeed);
                        //}
                        //else
                        //{
                        MoveToXY(_ModelInfo._Loading[nLoadStep].dbX, _ModelInfo._Loading[nLoadStep].dbY, _ModelInfo.dbClampXYMoveSpeed);
                        //}
                    }

                    if (_ModelInfo._Loading[nLoadStep].nType == 0)          // 0도 일때
                    {
                        MoveTo(AXIS.R, 0.0, _Config.dbTurnSpeed);
                    }
                    else if (_ModelInfo._Loading[nLoadStep].nType == 1)     // 90도 일때
                    {
                        MoveTo(AXIS.R, -90.0, _Config.dbTurnSpeed);
                    }
                    else if (_ModelInfo._Loading[nLoadStep].nType == 2)     // 180도 일때
                    {
                        MoveTo(AXIS.R, -180.0, _Config.dbTurnSpeed);
                    }
                    else if (_ModelInfo._Loading[nLoadStep].nType == 3)     // -90도 일때
                    {
                        MoveTo(AXIS.R, 90.0, _Config.dbTurnSpeed);
                    }
                    else
                    {
                        _SysInfo.bPackLoadFail = true;
                        AppendLogMsg("해당 팩 모델설정 에러", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 0;

                    }
                    SetDIOPort(DO.SMEMA_OUT2, false);           // 회전할때는 이타이밍에 끈다 20.03.31  상구D 요청
                    _SysInfo.bMoveClampPickUpComplate = true;
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 112:
                    if (!MotionDone(AXIS.R)) { break; }


                    if (_ModelInfo._Loading[nLoadStep].nType == 0)          // 0도 일때
                    {
                        if (CheckMotionPosErr(AXIS.R, 0.0))
                        {
                            _SysInfo.bPackLoadFail = true;
                            nProcessStep[nStepIndex] = 0;
                            break;
                        }
                    }
                    else if (_ModelInfo._Loading[nLoadStep].nType == 1)     // 90도 일때
                    {
                        if (CheckMotionPosErr(AXIS.R, 90.0))
                        {
                            _SysInfo.bPackLoadFail = true;
                            nProcessStep[nStepIndex] = 0;
                            break;
                        }
                    }
                    else if (_ModelInfo._Loading[nLoadStep].nType == 2)     // 180도 일때
                    {
                        if (CheckMotionPosErr(AXIS.R, 180.0))
                        {
                            _SysInfo.bPackLoadFail = true;
                            nProcessStep[nStepIndex] = 0;
                            break;
                        }
                    }
                    else if (_ModelInfo._Loading[nLoadStep].nType == 3)     // -90도 일때
                    {
                        if (CheckMotionPosErr(AXIS.R, -90.0))
                        {
                            _SysInfo.bPackLoadFail = true;
                            nProcessStep[nStepIndex] = 0;
                            break;
                        }
                    }





                    nProcessStep[nStepIndex] = 200;
                    //if (tMainTimer[nStepIndex].Verify())
                    //{
                    //    if (!GetDioPort(DI.LOADING_ROTATE_OFF)) { AppendTimeOutMsg(DI.LOADING_ROTATE_OFF); }
                    //    _SysInfo.bPackLoadFail = true;
                    //    nProcessStep[nStepIndex] = 0;
                    //}

                    //if (GetDioPort(DI.LOADING_ROTATE_OFF))
                    //{
                    //    nProcessStep[nStepIndex] = 200;
                    //}
                    break;


                // 제품 하강 스텝
                case 200:
                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y) || !MotionDone(AXIS.Z)) { break; }

                    MoveTo(AXIS.Z, _Config.dbSafeLoadZPos, _ModelInfo.dbClampZMoveSpeed);      // Z축 안전위치로 이동
                    nProcessStep[nStepIndex]++;
                    break;

                case 201:
                    //if (!GetLoadingDoor()) { break; }
                    if (!MotionDone(AXIS.Z)) { break; }

                    if (CheckMotionPosErr(AXIS.Z, _Config.dbSafeLoadZPos))
                    {
                        _SysInfo.bPackLoadFail = true;
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }

                    MoveToXY(_ModelInfo._Loading[nLoadStep].dbX, _ModelInfo._Loading[nLoadStep].dbY, _ModelInfo.dbClampXYMoveSpeed);   // XY축 제품 적재위치로 이동
                    nProcessStep[nStepIndex]++;
                    break;

                case 202:
                    //if (!GetLoadingDoor())                    // 상구 팀장 요청 간섭발생문제 19.09.17
                    //{
                    //    CAXM.AxmMoveEStop((int)AXIS.X);
                    //    CAXM.AxmMoveEStop((int)AXIS.Y);
                    //    nProcessStep[nStepIndex] = 201;
                    //    break;
                    //}

                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y) || !MotionDone(AXIS.R)) { break; }


                    if (CheckMotionPosErr(AXIS.X, _ModelInfo._Loading[nLoadStep].dbX))
                    {
                        _SysInfo.bPackLoadFail = true;
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }

                    if (CheckMotionPosErr(AXIS.Y, _ModelInfo._Loading[nLoadStep].dbY))
                    {
                        _SysInfo.bPackLoadFail = true;
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }

                    SetDIOPort(DO.SMEMA_OUT2, false);       // 회전없이 적재할때는 이타이밍에 끈다 20.03.31 상구D요청
                    nProcessStep[nStepIndex]++;
                    break;

                case 203:
                    if (!GetLoadingDoor()) { break; }

                    MoveTo(AXIS.Z, _ModelInfo._Loading[nLoadStep].dbZ, _ModelInfo.dbClampZMoveSpeed);      // Z축 적재 위치로 이동

                    nProcessStep[nStepIndex]++;
                    break;

                case 204:
                    if (!GetLoadingDoor())
                    {
                        CAXM.AxmMoveEStop((int)AXIS.Z);
                        nProcessStep[nStepIndex] = 203;
                        break;
                    }

                    if (!MotionDone(AXIS.Z)) { break; }
                    // 해당 위치까지 갔는데 센서 감지 안되면 추가이동
                    //nProcessStep[nStepIndex]++;

                    if (CheckMotionPosErr(AXIS.Z, _ModelInfo._Loading[nLoadStep].dbZ))
                    {
                        _SysInfo.bPackLoadFail = true;
                        nProcessStep[nStepIndex] = 0;
                        break;
                    }


                    nProcessStep[nStepIndex] = 250;
                    break;

                case 205:
                    Move(AXIS.Z, _Config.dbZSensingHeight, _Config.dbZSensingSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 206:
                    // 가는도중 센서 감지가 된다면 급정지 후 시프트 스텝으로
                    //if (GetDioPort(DI.LOADING_HAND_PRODUCT))
                    //{
                    //    CAXM.AxmMoveEStop((int)AXIS.Z);
                    //    nProcessStep[nStepIndex] = 250;
                    //    break;
                    //}

                    if (!MotionDone(AXIS.Z)) { break; }
                    // 설정 위치가지 센싱이동 했는데도 감지가 안된다면 문제가 있는 상태.

                    _SysInfo.bPackLoadFail = true;
                    AppendLogMsg("팩 로딩 제품 감지 에러", LOG_TYPE.ERROR);
                    nProcessStep[nStepIndex] = 0;
                    break;

                // 제품 Shift
                case 250:
                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y) || !MotionDone(AXIS.Z)) { break; }

                    Move(AXIS.X, _ModelInfo._Loading[nLoadStep].dbS, _ModelInfo.dbShiftMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 251:
                    if (!MotionDone(AXIS.X)) { break; }
                    Move(AXIS.Y, _ModelInfo._Loading[nLoadStep].dbSpare_b[1], _ModelInfo.dbShiftMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;


                case 252:
                    if (!MotionDone(AXIS.Y)) { break; }

                    Move(AXIS.Z, _ModelInfo._Loading[nLoadStep].dbSpare_b[0], _ModelInfo.dbShiftMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 253:
                    if (!MotionDone(AXIS.Z)) { break; }

                    SetDIOPort(DO.CMA_LOADING_CLAMP_OFF, true);
                    SetDIOPort(DO.CMA_LOADING_CLAMP_ON, false);
                    tMainTimer[nStepIndex].Start(_Config.nCylTimeOut);
                    nProcessStep[nStepIndex]++;
                    break;

                case 254:
                    if (tMainTimer[nStepIndex].Verify())
                    {
                        if (!GetDIOPort(DI.CMA_LOADING_CLAMP1_OFF)) { AppendTimeOutMsg(DI.CMA_LOADING_CLAMP1_OFF); }
                        _SysInfo.bPackLoadFail = true;
                        nProcessStep[nStepIndex] = 0;
                    }

                    if (GetDIOPort(DI.CMA_LOADING_CLAMP1_OFF) && GetDIOPort(DI.CMA_LOADING_CLAMP2_OFF))
                    {
                        nProcessStep[nStepIndex] = 0;
                    }
                    break;


                // PC Sheet 부착 행정
                case 300:
                    // 회전위치로 이동
                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y) || !MotionDone(AXIS.Z) || !MotionDone(AXIS.R)) { break; }

                    MoveToXY(_ModelInfo.dbTurnPosX, _ModelInfo.dbTurnPosY, _ModelInfo.dbClampXYMoveSpeed);   // XY축 제품 회전위치로 이동
                    nProcessStep[nStepIndex]++;
                    break;

                case 301:
                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y) || !MotionDone(AXIS.Z) || !MotionDone(AXIS.R)) { break; }

                    //  회전위치에 도착헸다면 원하는 각도로 돌리고 Smema Siganl 변경
                    if (nLoadStep == 0)
                    {
                        MoveTo(AXIS.R, -(_Config.dbFirstPCSheetAngle), _Config.dbTurnSpeed);
                    }
                    else if (nLoadStep == _ModelInfo.nCmaCount - 1)
                    {
                        MoveTo(AXIS.R, -(_Config.dbLastPCSheetAngle), _Config.dbTurnSpeed);
                    }
                    SetDIOPort(DO.SMEMA_OUT2, false);           // PC시트 부착시에는 이타이밍에 끈다 20.03.31 상구D 요청
                    nProcessStep[nStepIndex] = 310;
                    break;


                case 310:
                    // 부착위치로 이동
                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y) || !MotionDone(AXIS.Z) || !MotionDone(AXIS.R)) { break; }

                    MoveToXY(_ModelInfo.dbLoadingJigTestPos1X, _ModelInfo.dbLoadingJigTestPos1Y, _ModelInfo.dbClampXYMoveSpeed);   // XY축 제품 회전위치로 이동
                    _SysInfo.bMoveClampPickUpComplate = true;
                    nProcessStep[nStepIndex]++;
                    break;

                case 311:
                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y) || !MotionDone(AXIS.Z) || !MotionDone(AXIS.R)) { break; }

                    MoveTo(AXIS.Z, _ModelInfo.dbLoadingJigTestPos1Z, _ModelInfo.dbClampZMoveSpeed);
                    nProcessStep[nStepIndex]++;
                    break;

                case 312:
                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y) || !MotionDone(AXIS.Z) || !MotionDone(AXIS.R)) { break; }

                    nProcessStep[nStepIndex] = 320;
                    break;

                // 스위치 입력을 기다림
                case 320:
                    if (GetDIOPort(DI.LOADING_START_SW))
                    {
                        tMainTimer[nStepIndex].Start(100);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 321:
                    if (GetDIOPort(DI.LOADING_START_SW) && tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex] = 330;
                    }
                    else if (!GetDIOPort(DI.LOADING_START_SW))
                    {
                        nProcessStep[nStepIndex] = 320;
                    }
                    break;

                // 스위치 입력이 들어왔을 경우 다시 Turn 위치로 이동하여 회전 및 안착
                case 330:
                    MoveTo(AXIS.Z, _Config.dbSafeLoadZPos, _ModelInfo.dbClampZMoveSpeed);      // Z축 안전위치로 이동
                    nProcessStep[nStepIndex]++;
                    break;

                case 331:
                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y) || !MotionDone(AXIS.Z) || !MotionDone(AXIS.R)) { break; }

                    MoveToXY(_ModelInfo.dbTurnPosX, _ModelInfo.dbTurnPosY, _ModelInfo.dbClampXYMoveSpeed);   // XY축 제품 회전위치로 이동
                    nProcessStep[nStepIndex]++;
                    break;

                case 332:
                    if (!MotionDone(AXIS.X) || !MotionDone(AXIS.Y) || !MotionDone(AXIS.Z) || !MotionDone(AXIS.R)) { break; }

                    if (_ModelInfo.dbTurnPosX > _ModelInfo._Loading[nLoadStep].dbX)
                    {
                        // 모델 설정된 X좌표가 회전위치보다 작다면 ( Station 방향 움직임이라면 )
                        // X,Y축 적재위치로 이동명령 함께 동작
                        //if(_ModelInfo.bUseCmaBizPcSheetLanding)
                        //{
                        //    MoveToXY(_ModelInfo.dbLoadingJigTestPos1X, _ModelInfo.dbLoadingJigTestPos1Y, _ModelInfo.dbClampXYMoveSpeed);
                        //}
                        //else
                        //{
                        MoveToXY(_ModelInfo._Loading[nLoadStep].dbX, _ModelInfo._Loading[nLoadStep].dbY, _ModelInfo.dbClampXYMoveSpeed);
                        //}
                    }

                    if (_ModelInfo._Loading[nLoadStep].nType == 0)          // 0도 일때
                    {
                        MoveTo(AXIS.R, 0.0, _Config.dbTurnSpeed);
                    }
                    else if (_ModelInfo._Loading[nLoadStep].nType == 1)     // 90도 일때
                    {
                        MoveTo(AXIS.R, -90.0, _Config.dbTurnSpeed);
                    }
                    else if (_ModelInfo._Loading[nLoadStep].nType == 2)     // 180도 일때
                    {
                        MoveTo(AXIS.R, -180.0, _Config.dbTurnSpeed);
                    }
                    else if (_ModelInfo._Loading[nLoadStep].nType == 3)     // -90도 일때
                    {
                        MoveTo(AXIS.R, 90.0, _Config.dbTurnSpeed);
                    }
                    else
                    {
                        _SysInfo.bPackLoadFail = true;
                        AppendLogMsg("해당 팩 모델설정 에러", LOG_TYPE.ERROR);
                        nProcessStep[nStepIndex] = 0;

                    }
                    nProcessStep[nStepIndex] = 200;
                    break;

            }

            return nProcessStep[nStepIndex];

        }
        //===========================================================


        //===========================================================


        // 마킹기 프로세스
        static void SUB_MARKING()
        {
            int nStepIndex = (int)PROC_LIST.MARKING;


            switch (nProcessStep[nStepIndex])
            {
                case 0:
                    if (_LaserMarking.bReadOk)
                    {
                        _LaserMarking.bReadOk = false;
                        if (_SysInfo.bCanLaserPrint)
                        {
                            _SysInfo.bCanLaserPrint = false;
                            // 데이터가 들어온경우
                            if (_LaserMarking.strReadBarcode == _Config.strLaserMarkingSendMsg)
                            {
                                // Send Data 일치의 경우
                                nProcessStep[nStepIndex] = 10;  // 마킹 시작
                            }
                            else
                            {
                                AppendLogMsg("레이저 마킹기 수신 데이터 이상(" + _LaserMarking.strReadBarcode + ")", LOG_TYPE.ERROR);
                                _SysInfo.nTL_Beep = 5;
                            }
                        }
                        else
                        {
                            AppendLogMsg("마킹 데이터 스캔 정보 없음", LOG_TYPE.ERROR);
                            _SysInfo.nTL_Beep = 5;
                        }
                    }
                    break;

                case 10:
                    _LaserMarking.SendData(_SysInfo.strLaserReadBarcode + _ModelInfo.strLaserMarkingSymbol);    // 심볼을 붙여서 전송한다
                    nProcessStep[nStepIndex] = 0;
                    break;
            }
        }


        // 마킹기 바코드 스캐너 프로세스
        static void SUB_MARKING_READ()
        {
            int nStepIndex = (int)PROC_LIST.MARKING_READ;

            switch (nProcessStep[nStepIndex])
            {
                case 0:
                    if (_LaserReader.bReadOk)
                    {
                        _LaserReader.bReadOk = false;
                        // 데이터가 들어온경우

                        if (_LaserReader.strReadBarcode == (_SysInfo.strLaserReadBarcode + _ModelInfo.strLaserMarkingSymbol))
                        {
                            // 리딩바코드와 출력바코드가 일치한다면
                            _SysInfo.bLaserBarcodeCompare = true;   // 비교 결과 TRUE로 만듬
                        }
                        //else if (string.Compare(_LaserReader.strReadBarcode, 0, _ModelInfo.strComment1, 0, _ModelInfo.strComment1.Length, false) == 0)
                        //{
                        //    // 리딩 바코드와 BMA 심볼이 일치한다면
                        //    if (_LaserReader.strReadBarcode.Substring(_LaserReader.strReadBarcode.Length - _ModelInfo.strLaserMarkingSymbol.Length, _ModelInfo.strLaserMarkingSymbol.Length) == _ModelInfo.strLaserMarkingSymbol)
                        //    {
                        //        //  혹시 이미 마킹된것의 바코드를 읽었다면
                        //        AppendLogMsg("레이저 마킹 - 원본 BMA 바코드를 리딩해주시기 바랍니다.", LOG_TYPE.ERROR);
                        //        _SysInfo.nTL_Beep = 3;
                        //    }
                        //    else
                        //    {
                        //        // 아니라면 리딩 바코드에 추가한다
                        //        _SysInfo.strLaserReadBarcode = _LaserReader.strReadBarcode;
                        //    }
                        //}
                        else if (CheckLaserBarcode(_LaserReader.strReadBarcode, _ModelInfo.strLaserReadBmaSymbol))
                        {
                            // 설정된 BMA 바코드와 일치할 경우
                            _SysInfo.strLaserReadBarcode = _LaserReader.strReadBarcode;
                            _SysInfo.bCanLaserPrint = true;
                        }
                        else
                        {
                            AppendLogMsg("레이저 마킹 - 바코드 정보 에러", LOG_TYPE.ERROR);
                            _SysInfo.nTL_Beep = 3;
                        }

                    }
                    break;
            }
        }


        public static bool CheckLaserBarcode(string readBarcode, string strTargetBarcode)
        {
            if (readBarcode.Length != strTargetBarcode.Length)
            {
                return false;
            }
            else
            {

                for (int nBCDLen = 0; nBCDLen < strTargetBarcode.Length; nBCDLen++)
                {
                    if (strTargetBarcode[nBCDLen] == '*')  // 아무거나
                    {

                    }
                    else if (strTargetBarcode[nBCDLen] == '@')   // 영문자
                    {
                        if (readBarcode[nBCDLen] < 0x41 || readBarcode[nBCDLen] > 0x7A)
                        {
                            return false;
                        }
                    }
                    else if (strTargetBarcode[nBCDLen] == '#')   // 숫자
                    {
                        if (readBarcode[nBCDLen] < 0x30 || readBarcode[nBCDLen] > 0x39)
                        {
                            return false;
                        }
                    }
                    else
                    {
                        if (strTargetBarcode[nBCDLen] != readBarcode[nBCDLen]) // 그외 경우 일치하지 않으면 NG
                        {
                            return false;
                        }
                    }
                }

            }

            return true;
        }

        static bool CheckduplicationCode(string str)
        {
            bool result = false;

            try
            {
                string strFolderPath = String.Format(@"DupllcationData\\");
                DirectoryInfo dir = new DirectoryInfo(strFolderPath);
                if (dir.Exists == false) { dir.Create(); }

                string strFilePath = String.Format(@"{0}{1}.txt", strFolderPath, DateTime.Now.ToString("yyMMdd"));
                FileInfo _file = new FileInfo(strFilePath);

                if (_file.Exists)
                {
                    string[] strTemp = File.ReadAllLines(strFilePath);

                    for (int i = 0; i < strTemp.Length; i++)
                    {
                        if (strTemp[i] == str)
                        {
                            result |= true;
                        }
                    }
                }
                else
                {
                    result = false;
                }
            }
            catch { }

            return result;
        }

        //====== 너트러너 스케쥴 설정
        public static void SetNutRunnerSch(int nStation, int nIndex)
        {
            #region 스테이션별 IO 할당
            DO _out_Nut_1 = new DO();

            switch (nStation)
            {
                case 0:
                    _out_Nut_1 = DO.NUTRUNNER1_OUT1;
                    break;

                case 1:
                    _out_Nut_1 = DO.NUTRUNNER2_OUT1;
                    break;

                case 2:
                    _out_Nut_1 = DO.NUTRUNNER3_OUT1;
                    break;

                case 3:
                    _out_Nut_1 = DO.NUTRUNNER4_OUT1;
                    break;

            }
            #endregion
            //if(_Config.bPset232Select)
            //{
            //    if(nStation != 0)
            //    {
            //        if (_SysInfo.nPsetOldIndex != nIndex)
            //        {
            //            _NutRunner[nStation - 1].nPSet = nIndex;
            //            _NutRunner[nStation - 1].bPSet = true;
            //            _SysInfo.nPsetOldIndex = nIndex;
            //        }
            //    }
            //}
            //else
            //{
            //    for (int i = 0; i < 3; i++)
            //    {
            //        SetDIOPort(_out_Nut_1 + i, (nIndex & (1 << (i))) != 0 ? true : false);
            //    }
            //}


            if (_Config.bUseNutrunnerEthMode)
            {
                // 너트러너 이더넷 모드 사용경우
                if (_SysInfo.nPsetOldIndex[nStation] != nIndex)
                {
                    _NutRunnerEth[nStation].nPSet = nIndex;
                    _NutRunnerEth[nStation].bPSet = true;
                    _SysInfo.nPsetOldIndex[nStation] = nIndex;
                }
            }
            else
            {
                if (_SysInfo.nPsetOldIndex[nStation] != nIndex)
                {
                    _NutRunner[nStation].nPSet = nIndex;
                    _NutRunner[nStation].bPSet = true;
                    _SysInfo.nPsetOldIndex[nStation] = nIndex;
                }
            }






        }

        // 스테이션 타워램프 프로세스
        static void WorkStationTowerLampProcess(int nStaion)
        {
            int nStepIndex = (int)PROC_LIST.HIPOT_TL + nStaion;

            DO _out_Red = new DO();
            DO _out_Yellow = new DO();
            DO _out_Green = new DO();

            switch (nStaion)
            {
                case 0:
                    _out_Yellow = DO.HIPOT_TOWERLAMP_YELLOW;
                    _out_Green = DO.HIPOT_TOWERLAMP_GREEN;
                    _out_Red = DO.HIPOT_TOWERLAMP_RED;
                    break;

                case 1:
                    _out_Yellow = DO.EOL_TOWERLAMP_YELLOW;
                    _out_Green = DO.EOL_TOWERLAMP_GREEN;
                    _out_Red = DO.EOL_TOWERLAMP_RED;
                    break;
            }

            switch (nProcessStep[nStepIndex])
            {
                case 0:
                    if (_SysInfo.ST_TL_RED[nStaion] != TOWER_LAMP.TL_OFF) { SetDIOPort(_out_Red, true); }
                    else { SetDIOPort(_out_Red, false); }

                    if (_SysInfo.ST_TL_GREEN[nStaion] != TOWER_LAMP.TL_OFF) { SetDIOPort(_out_Green, true); }
                    else { SetDIOPort(_out_Green, false); }

                    if (_SysInfo.ST_TL_YELLOW[nStaion] != TOWER_LAMP.TL_OFF) { SetDIOPort(_out_Yellow, true); }
                    else { SetDIOPort(_out_Yellow, false); }

                    tMainTimer[nStepIndex].Start(500);
                    nProcessStep[nStepIndex]++;
                    break;


                case 1:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    if (_SysInfo.ST_TL_RED[nStaion] == TOWER_LAMP.TL_ON) { SetDIOPort(_out_Red, true); }
                    else { SetDIOPort(_out_Red, false); }

                    if (_SysInfo.ST_TL_GREEN[nStaion] == TOWER_LAMP.TL_ON) { SetDIOPort(_out_Green, true); }
                    else { SetDIOPort(_out_Green, false); }

                    if (_SysInfo.ST_TL_YELLOW[nStaion] == TOWER_LAMP.TL_ON) { SetDIOPort(_out_Yellow, true); }
                    else { SetDIOPort(_out_Yellow, false); }

                    tMainTimer[nStepIndex].Start(500);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    nProcessStep[nStepIndex] = 0;
                    break;
            }
        }

        // 스테이션 램프 프로세스
        static void WorkStationLampProcess(int nStaion)
        {
            int nStepIndex = (int)PROC_LIST.STATION6_LAMP + nStaion;

            DO _out_Red = new DO();
            DO _out_Yellow = new DO();
            DO _out_Green = new DO();
            DO _out_Buzzer = new DO();

            switch (nStaion)
            {
                case 0:
                    _out_Red = DO.HIPOT_STOP_SW_LAMP;
                    _out_Yellow = DO.HIPOT_START_SW_LAMP;
                    _out_Green = DO.HIPOT_FINISH_SW_LAMP;
                    _out_Buzzer = DO.HIPOT_BUZZER;
                    break;

                case 1:
                    _out_Red = DO.EOL_STOP_SW_LAMP;
                    _out_Yellow = DO.EOL_START_SW_LAMP;
                    _out_Green = DO.EOL_FINISH_SW_LAMP;
                    _out_Buzzer = DO.EOL_BUZZER;
                    break;
            }

            switch (nProcessStep[nStepIndex])
            {
                case 0:

                    if (_SysInfo.ST_Red[nStaion] != TOWER_LAMP.TL_OFF) { SetDIOPort(_out_Red, true); }
                    else { SetDIOPort(_out_Red, false); }

                    if (_SysInfo.ST_Yellow[nStaion] != TOWER_LAMP.TL_OFF) { SetDIOPort(_out_Yellow, true); }
                    else { SetDIOPort(_out_Yellow, false); }

                    if (_SysInfo.ST_Green[nStaion] != TOWER_LAMP.TL_OFF) { SetDIOPort(_out_Green, true); }
                    else { SetDIOPort(_out_Green, false); }

                    if (!(_SysInfo.nCount_Beep[5 + nStaion] > 0))
                    {
                        if (_SysInfo.ST_Buzzer[nStaion] != TOWER_LAMP.TL_OFF) { SetDIOPort(_out_Buzzer, true); }
                        else { SetDIOPort(_out_Buzzer, false); }
                    }

                    tMainTimer[nStepIndex].Start(500);
                    nProcessStep[nStepIndex]++;
                    break;


                case 1:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    if (_SysInfo.ST_Red[nStaion] == TOWER_LAMP.TL_ON) { SetDIOPort(_out_Red, true); }
                    else { SetDIOPort(_out_Red, false); }

                    if (_SysInfo.ST_Yellow[nStaion] == TOWER_LAMP.TL_ON) { SetDIOPort(_out_Yellow, true); }
                    else { SetDIOPort(_out_Yellow, false); }

                    if (_SysInfo.ST_Green[nStaion] == TOWER_LAMP.TL_ON) { SetDIOPort(_out_Green, true); }
                    else { SetDIOPort(_out_Green, false); }

                    if (!(_SysInfo.nCount_Beep[5 + nStaion] > 0))
                    {
                        if (_SysInfo.ST_Buzzer[nStaion] == TOWER_LAMP.TL_ON) { SetDIOPort(_out_Buzzer, true); }
                        else { SetDIOPort(_out_Buzzer, false); }
                    }

                    tMainTimer[nStepIndex].Start(500);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    nProcessStep[nStepIndex] = 0;
                    break;
            }
        }

        //=== CMA 데이터 관리
        public static string CheckCMAStatus(string str)
        {
            //string _Path = String.Format("{0}\\{1}.txt", _Config.strCMACheckDir, str);

            string _Path = String.Format("{0}\\{1}.inf", _Config.strCMACheckDir, str);

            FileInfo _info = new FileInfo(_Path);

            if (_info.Exists)
            {
                try
                {
                    //string[] _ReadData = File.ReadAllLines(_Path, Encoding.Default);
                    //return _ReadData[0];

                    if (_IniFile.IniReadValue("COMMON", "IS_WORK_COMPLETE", "0", _Path) == "1")
                    {
                        return "OK";
                    }
                    else
                    {
                        return "NG";
                    }

                    // INF 파일 읽는 형식으로 변경



                }
                catch { return "NOFILE"; }
            }
            else
            {
                return "NOFILE";
            }

        }


        public static bool Check_Server_Barcode(string strBCD, int nIndex)
        {
            bool result = false;

            string svrName = _Config.strMESDBIP;          //"192.168.10.39";          //SID : PIMES
            string userId = _Config.strMESDBID;           //"BISESS";                 // PORT = 1521
            string userPw = _Config.strMESDBPASS;         //"BISESS";
            string strReadData = "";
            string strTarget = "";
            if (nIndex == 0) { strTarget = "BMA"; }
            else if (nIndex == 1) { strTarget = "EOL"; }

            string connectionString = string.Format("Data Source=(DESCRIPTION=(ADDRESS=(PROTOCOL=TCP)(HOST={0})(PORT={4}))(CONNECT_DATA=(SERVICE_NAME={3})));User Id={1};Password={2};", svrName, userId, userPw, _Config.strMESDBSID, _Config.nMESDBPort);
            //connectionString = string.Format("user id={0};password={1}; data source={2}:1521/XE", userId, userPw, svrName);
            using (OracleConnection oracleConnection = new OracleConnection(connectionString))
            {
                try
                {
                    oracleConnection.Open();
                    OracleCommand myCommand = new OracleCommand(String.Format("SELECT BISDBA.FUN_{1}_CHECK('{0}') FROM DUAL", strBCD, strTarget), oracleConnection);

                    OracleDataReader rdr = myCommand.ExecuteReader();
                    if (rdr.Read())
                    {
                        strReadData = rdr.GetString(0);

                        if (strReadData == "OK")
                        {
                            result = true;
                        }
                        else
                        {

                            AppendLogMsg("MES DB ERROR (" + strReadData + ")", LOG_TYPE.ERROR); result = false;
                            // 27일부터 3라인 양산
                            // 22일부터 공정성 평가
                        }

                    }
                    else
                    {
                        result = false;
                    }
                }
                catch (OracleException e) { AppendLogMsg("MES DB ERROR (" + e.Message + ")", LOG_TYPE.ERROR); result = false; }
            }



            return result;
        }

        //====== 컨택존 작업완료 스위치 프로세스 ====================
        static void SUB_CONTACT_SW(int nStation)
        {
            if (!_Config.bUseStationReservation) { return; }

            int nStepIndex = (int)PROC_LIST.HIPOT_SW + nStation;

            DI _in_Sw = new DI();

            switch (nStation)
            {
                case 0:
                    _in_Sw = DI.HIPOT_FINISH_SW;
                    break;

                case 1:
                    _in_Sw = DI.EOL_FINISH_SW;
                    break;
            }


            switch (nProcessStep[nStepIndex])
            {
                case 0:
                    if (GetDIOPort(_in_Sw))
                    {
                        tMainTimer[nStepIndex].Start(_Config.nChatteringTime);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 1:
                    if (GetDIOPort(_in_Sw) && tMainTimer[nStepIndex].Verify())
                    {
                        nProcessStep[nStepIndex]++;
                    }
                    else if (!GetDIOPort(_in_Sw))
                    {
                        nProcessStep[nStepIndex] = 0;
                    }
                    break;

                case 2:
                    if (_SysInfo.bStationReservation[(int)STATION_LIST.ST6 + nStation])
                    {
                        _SysInfo.bStationReservation[(int)STATION_LIST.ST6 + nStation] = false;
                    }
                    else
                    {
                        _SysInfo.bStationReservation[(int)STATION_LIST.ST6 + nStation] = true;
                    }
                    nProcessStep[nStepIndex] = 0;
                    break;
            }
        }
        //===========================================================


        public static void WorkCV()
        {

            ///// 일반적인 컨베어 동작
            if (!_Config.bUseCVAutoStop)
            {


                if (GetDIOPort(DI.CV_ON_SW) && !GetDIOPort(DI.CV_OFF_SW))
                {
                    SetDIOPort(DO.MAIN_CV_ON, true);
                    SetDIOPort(DO.CV_ON_SW_LAMP, true);
                    SetDIOPort(DO.CV_OFF_SW_LAMP, false);
                }
                else if (GetDIOPort(DI.CV_OFF_SW) && !GetDIOPort(DI.CV_ON_SW))
                {
                    SetDIOPort(DO.MAIN_CV_ON, false);
                    SetDIOPort(DO.CV_ON_SW_LAMP, false);
                    SetDIOPort(DO.CV_OFF_SW_LAMP, true);
                }

            }
            
            //////////////////////////////////////////////////
            else
            {
                if (GetDIOPort(DI.CV_ON_SW) && !GetDIOPort(DI.CV_OFF_SW))
                {
                    _SysInfo.bCVMainOn = true;
                    tCVTimer.Start(_Config.nCVAutoStopTime);

                    SetDIOPort(DO.CV_ON_SW_LAMP, true);
                    SetDIOPort(DO.CV_OFF_SW_LAMP, false);


                }
                else if (GetDIOPort(DI.CV_OFF_SW) && !GetDIOPort(DI.CV_ON_SW))
                {
                    _SysInfo.bCVMainOn = false;
                    SetDIOPort(DO.CV_ON_SW_LAMP, false);
                    SetDIOPort(DO.CV_OFF_SW_LAMP, true);
                }

                if (_SysInfo.bCVMainOn)
                {


                    if (GetDIOPort(DI.STATION1_FINISH_SW) ||
                        GetDIOPort(DI.STATION2_FINISH_SW) ||
                        GetDIOPort(DI.STATION3_FINISH_SW) ||
                        GetDIOPort(DI.STATION4_FINISH_SW) ||
                        GetDIOPort(DI.STATION5_FINISH_SW) ||
                        GetDIOPort(DI.HIPOT_FINISH_SW) ||
                        GetDIOPort(DI.EOL_FINISH_SW) ||
                        GetDIOPort(DI.RELIFT_FINISH_SW) ||
                        GetDIOPortStat(DO.RELIFT_CV_ON) ||
                        GetDIOPortStat(DO.INLIFT_CV_ON) ||
                        !GetDIOPort(DI.UNDER_CV_PALLET_END))
                    {
                        tCVTimer.Start(_Config.nCVAutoStopTime);
                    }




                    if (tCVTimer.Verify())
                    {
                        SetDIOPort(DO.MAIN_CV_ON, false);
                    }
                    else
                    {
                        SetDIOPort(DO.MAIN_CV_ON, true);
                    }

                }
                else
                {
                    SetDIOPort(DO.MAIN_CV_ON, false);
                }
            }

        }


        //===========================================================
        //====== 체결정보 이동 프로세스스 ===========================
        static void SUB_MOVE_TITE_LOG(int nStation)
        {
            try
            {
                if (nStation != 4)
                {
                    string strFolderPath1 = String.Format(@"TEMP_DATA\\ST{0}\\", nStation + 1);
                    DirectoryInfo dir1 = new DirectoryInfo(strFolderPath1);
                    if (dir1.Exists == false) { dir1.Create(); }

                    string strFolderPath2 = String.Format(@"TEMP_DATA\\ST{0}\\", nStation + 2);
                    DirectoryInfo dir2 = new DirectoryInfo(strFolderPath2);
                    if (dir2.Exists == false) { dir2.Create(); }

                    string strFilePath1 = String.Format(@"{0}ST{1}.txt", strFolderPath1, nStation + 1);
                    string strFilePath2 = String.Format(@"{0}ST{1}.txt", strFolderPath2, nStation + 2);


                    FileInfo file1 = new FileInfo(strFilePath1);
                    FileInfo file2 = new FileInfo(strFilePath2);

                    // 본인 스테이션에 파일이 존재한다면
                    if (file1.Exists)
                    {
                        string strRead = File.ReadAllText(strFilePath1);
                        File.AppendAllText(strFilePath2, strRead, Encoding.Default);
                        File.Delete(strFilePath1);
                    }

                    // 시프트 하려는 스테이션이 바코드 스캔 스테이션 이라면
                    if (nStation >= _ModelInfo.nBCDScanStation - 1)
                    {
                        //바코드 정보 데이터를 이동함
                        strFilePath1 = String.Format(@"{0}BarcodeInfo.txt", strFolderPath1);
                        strFilePath2 = String.Format(@"{0}BarcodeInfo.txt", strFolderPath2);

                        file1 = new FileInfo(strFilePath1);
                        if (file1.Exists)
                        {
                            File.Copy(strFilePath1, strFilePath2, true);
                            File.Delete(strFilePath1);
                        }
                    }
                }
                else
                {
                    string strFolderPath = String.Format(@"TEMP_DATA\\ST{0}\\", nStation + 1);
                    DirectoryInfo dir = new DirectoryInfo(strFolderPath);
                    if (dir.Exists == false) { dir.Create(); }


                    string strFilePath1 = String.Format(@"{0}BarcodeInfo.txt", strFolderPath);
                    string strFilePath2 = String.Format(@"{0}ST{1}.txt", strFolderPath, nStation + 1);

                    FileInfo file1 = new FileInfo(strFilePath1);
                    FileInfo file2 = new FileInfo(strFilePath2);

                    if (file1.Exists)
                    {
                        string[] strRead = File.ReadAllLines(strFilePath1);
                        string[] strFIleName = strRead[0].Split('\t');

                        string strReadData = "";

                        for (int i = 0; i < strRead.Length; i++)
                        {
                            strReadData += strRead[i] + "\r\n";
                        }


                        string strReadNutRunnerData = "";
                        if (file2.Exists)
                        {
                            strReadNutRunnerData = File.ReadAllText(strFilePath2);
                            //strReadData += strReadNutRunnerData;
                        }


                        // 너트러너 파일
                        if (file2.Exists)
                        {
                            string strSaveFolderPath = String.Format(@"E:\\DATA\\NUTRUNNER\\{0}\\{1}\\", _ModelInfo.strModelName, Program._LotCount.tLotClearTime.ToString("yyMMdd"));
                            DirectoryInfo Savedir = new DirectoryInfo(strSaveFolderPath);
                            if (Savedir.Exists == false) { Savedir.Create(); }

                            string strSaveFilePath = String.Format(@"{0}{1}.txt", strSaveFolderPath, strFIleName[0]);
                            File.WriteAllText(strSaveFilePath, strReadNutRunnerData);
                        }
                        //==============================================



                        File.Delete(strFilePath1);
                        if (file2.Exists)
                        {
                            File.Delete(strFilePath2);
                        }

                    }
                }
            }
            catch (Exception e)
            {
                AppendLogMsg(e.Message, LOG_TYPE.ERROR);
            }
        }
        //===========================================================

        // 리턴리프트 케이블정보 중계
        public static void SUB_CABLE_PRODUCT()
        {
            if (_Config.bUseReLiftCableSensing)
            {
                SetDIOPort(DO.CABLE_INFO_OUT, !(GetDIOPort(DI.RELIFT_CAN_CABLE_CHECK) || !GetDIOPort(DI.RELIFT_CAN_CABLE_ALIGN)));
            }
            else
            {
                SetDIOPort(DO.CABLE_INFO_OUT, true);
            }

        }



        //===========================================================
        //====== LOT CLEAR ==========================================
        static void LotCountInfoUpdate()
        {
            if (DateTime.Now.Year == _LotCount.tLotClearTime.Year &&
                (DateTime.Now.Month != _LotCount.tLotClearTime.Month ||
                DateTime.Now.Day != _LotCount.tLotClearTime.Day))              // 년이 같은경우 DayofYear에 의한 초기화
            {
                if (DateTime.Now.DayOfYear - _LotCount.tLotClearTime.DayOfYear > 1)
                {
                    _LotCount.nLotCount = 0;
                    _LotCount.tLotClearTime = DateTime.Now;
                    SaveModelProductCount(_ModelInfo.strModelName);
                }
                else
                {
                    if (DateTime.Now.Hour > (_Config.nLotClearTime / 100))
                    {
                        // 시간이 크면 초기화
                        _LotCount.nLotCount = 0;
                        _LotCount.tLotClearTime = DateTime.Now;
                        SaveModelProductCount(_ModelInfo.strModelName);
                    }
                    else if (DateTime.Now.Hour == (_Config.nLotClearTime / 100) &&
                        DateTime.Now.Minute >= (_Config.nLotClearTime % 100))
                    {
                        // 시간이 같고 분이 크면 초기화
                        _LotCount.nLotCount = 0;
                        _LotCount.tLotClearTime = DateTime.Now;
                        SaveModelProductCount(_ModelInfo.strModelName);
                    }
                }
            }
            else if (DateTime.Now.Year != _LotCount.tLotClearTime.Year)             // 년이 다른 경우 클리어 날짜가 12월 31일 이고 오늘 날짜가 1월 1일이면 지정한 시간에 초기화
            {
                if (DateTime.Now.Month == 1 && DateTime.Now.Day == 1 && _LotCount.tLotClearTime.Month == 12 && _LotCount.tLotClearTime.Day == 31)
                {
                    if (DateTime.Now.Hour >= (_Config.nLotClearTime / 100) &&
                        DateTime.Now.Minute >= (_Config.nLotClearTime % 100))
                    {
                        _LotCount.nLotCount = 0;
                        _LotCount.tLotClearTime = DateTime.Now;
                        SaveModelProductCount(_ModelInfo.strModelName);
                    }
                }
                else
                {
                    _LotCount.nLotCount = 0;
                    _LotCount.tLotClearTime = DateTime.Now;
                    SaveModelProductCount(_ModelInfo.strModelName);
                }
            }


        }
        //===========================================================

        //====== 타임아웃 메세지 출력
        static void AppendTimeOutMsg(DI _nIndex)
        {
            AppendLogMsg(String.Format("X{0:X2} - {1} TIME OUT..", (int)_nIndex, _Define.DITable[0].Rows[(int)_nIndex]["Comment"].ToString()), LOG_TYPE.ERROR);
        }


        //===========================================================
        //====== 바코드 정보 저장 ===================================
        static void SaveBarcodeInfo()
        {
            string strOutputBCD = "";

            if (_Config.bUseReWorkTypeBCDScan)
            {
                strOutputBCD = _SysInfo.strReWorkBCD;
            }
            else
            {
                strOutputBCD = _BCDPrint.strModelInfo + _BCDPrint.strPrintBCD;
            }

            string strDaySave = strOutputBCD + "," + _ModelInfo.strComment2 + "," + DateTime.Now.ToString("yyyy'.'MM'.'dd") + " " + DateTime.Now.ToString("HH':'mm':'ss") + ",";
            string strPrintBcd = strOutputBCD + "\t" + _ModelInfo.strComment2 + "\t" + DateTime.Now.ToString("yyyy'.'MM'.'dd") + " " + DateTime.Now.ToString("HH':'mm':'ss") + "\r\n";


            //// CMA
            //DataRow[] _cmaRow = _dtBCDInfo.Select("[Type] = 'CMA'");
            //for (int i = 0; i < _cmaRow.Count(); i++) { strPrintBcd += String.Format("{0}\tCMA\r\n", _cmaRow[i][0].ToString()); }


            //// BMS
            //DataRow[] _bmsRow = _dtBCDInfo.Select("[Type] = 'BMS'");
            //for (int i = 0; i < _bmsRow.Count(); i++) { strPrintBcd += String.Format("{0}\tBMS\r\n", _bmsRow[i][0].ToString()); }

            //// FUSE
            //DataRow[] _FuseRow = _dtBCDInfo.Select("[Type] = 'FUSE'");
            //for (int i = 0; i < _FuseRow.Count(); i++) { strPrintBcd += String.Format("{0}\tFUSE\r\n", _FuseRow[i][0].ToString()); }

            for (int i = 0; i < _ReadBCDList.Count; i++)
            {
                if (_ReadBCDList[i].strCate != "REAR")
                {
                    strDaySave += _ReadBCDList[i].strBCD + ",";
                    strPrintBcd += _ReadBCDList[i].strBCD + "\t" + _ReadBCDList[i].strCate + "\r\n";
                }
            }
            strDaySave += "\r\n";

            string strFolderPath = String.Format(@"TEMP_DATA\\ST{0}\\", _ModelInfo.nBCDScanStation);
            DirectoryInfo dir = new DirectoryInfo(strFolderPath);
            if (dir.Exists == false) { dir.Create(); }


            try
            {
                //===============우리쪽 임시데이터 저장 =========
                // 바코드 파일
                string strSaveFolderPath = String.Format(@"E:\\DATA\\PACK\\{0}\\{1}\\", _ModelInfo.strModelName, Program._LotCount.tLotClearTime.ToString("yyMMdd"));
                DirectoryInfo Savedir = new DirectoryInfo(strSaveFolderPath);
                if (Savedir.Exists == false) { Savedir.Create(); }

                string strSaveFilePath = String.Format(@"{0}{1}.txt", strSaveFolderPath, strOutputBCD);
                File.WriteAllText(strSaveFilePath, strPrintBcd);

                strSaveFolderPath = String.Format(@"E:\\DATA2\\PACK\\{0}\\{1}\\", _ModelInfo.strModelName, Program._LotCount.tLotClearTime.ToString("yyMMdd"));
                Savedir = new DirectoryInfo(strSaveFolderPath);
                if (Savedir.Exists == false) { Savedir.Create(); }

                strSaveFilePath = String.Format(@"{0}{1}.txt", strSaveFolderPath, strOutputBCD);
                File.WriteAllText(strSaveFilePath, strPrintBcd);



                strSaveFolderPath = String.Format(@"E:\\DATA\\PACK\\{0}\\{1}\\", _ModelInfo.strModelName, Program._LotCount.tLotClearTime.ToString("yyMMdd"));
                Savedir = new DirectoryInfo(strSaveFolderPath);
                if (Savedir.Exists == false) { Savedir.Create(); }

                strSaveFilePath = String.Format(@"{0}{1}.txt", strSaveFolderPath, "Total");
                File.AppendAllText(strSaveFilePath, strDaySave);


                //=============== 마스터 데이터 저장 =========
                // 바코드 파일
                strSaveFolderPath = String.Format(@"E:\\MASTER\\PACK\\{0}\\", _ModelInfo.strModelName);
                Savedir = new DirectoryInfo(strSaveFolderPath);
                if (Savedir.Exists == false) { Savedir.Create(); }

                strSaveFilePath = String.Format(@"{0}{1}]{2}.txt", strSaveFolderPath, Program._LotCount.tLotClearTime.ToString("yyMMdd"), strOutputBCD);
                File.WriteAllText(strSaveFilePath, strPrintBcd);



                //========================== ERP 데이터 저장
                strSaveFolderPath = String.Format(@"{0}\\", _Config.strMESDir);
                Savedir = new DirectoryInfo(strSaveFolderPath);
                if (Savedir.Exists == false) { Savedir.Create(); }

                strSaveFilePath = String.Format(@"{0}{1}.txt", strSaveFolderPath, strOutputBCD);
                File.WriteAllText(strSaveFilePath, strPrintBcd);


                //========================== BackUp 데이터 저장
                strSaveFolderPath = String.Format(@"E:\\BACKUP\\PACK\\{0}\\{1}\\", _ModelInfo.strModelName, Program._LotCount.tLotClearTime.ToString("yyMMdd"));
                Savedir = new DirectoryInfo(strSaveFolderPath);
                if (Savedir.Exists == false) { Savedir.Create(); }

                strSaveFilePath = String.Format(@"{0}{1}.txt", strSaveFolderPath, strOutputBCD);
                File.WriteAllText(strSaveFilePath, strPrintBcd);

                strSaveFolderPath = String.Format(@"E:\\BACKUP2\\PACK\\{0}\\{1}\\", _ModelInfo.strModelName, Program._LotCount.tLotClearTime.ToString("yyMMdd"));
                Savedir = new DirectoryInfo(strSaveFolderPath);
                if (Savedir.Exists == false) { Savedir.Create(); }

                strSaveFilePath = String.Format(@"{0}{1}.txt", strSaveFolderPath, strOutputBCD);
                File.WriteAllText(strSaveFilePath, strPrintBcd);

                //================= 일일 데이터 저장 ==================
                // CSV 파일로 열거형으로 저장


            }
            catch { }



            string strFilePath = String.Format(@"{0}BarcodeInfo.txt", strFolderPath);

            File.WriteAllText(strFilePath, strPrintBcd, Encoding.Default);


        }

        //===========================================================



        static void MasterModelLoadProcess()
        {
            string strFolderPath1 = String.Format(@"MASTER_MODEL\\");
            DirectoryInfo dir1 = new DirectoryInfo(strFolderPath1);
            if (dir1.Exists == false) { dir1.Create(); }

            if (_Config.bMasterModelLoad)
            {
                string strFilePath1 = String.Format(@"{0}{1}.inf", strFolderPath1, _ModelInfo.strModelName);


                FileInfo file1 = new FileInfo(strFilePath1);

                // 본인 스테이션에 파일이 존재한다면
                if (file1.Exists)
                {
                    LoadMasterIni(strFilePath1);
                }

            }

        }

        static void AliveCheckProcess()
        {
            string strFolderPath1 = String.Format(@"AliveCheck\\");
            DirectoryInfo dir1 = new DirectoryInfo(strFolderPath1);
            if (dir1.Exists == false) { dir1.Create(); }


            // 마스터 모드 사용시
            if (_Config.bMasterModelLoad)
            {


                string[] strReadFile = Directory.GetFiles(String.Format("{0}\\", strFolderPath1), @"ALIVE_*.txt");

                if (strReadFile.Length > 0)
                {
                    for (int i = 0; i < strReadFile.Length; i++)
                    {
                        if (string.IsNullOrEmpty(strReadFile[i])) return;
                        if (File.Exists(strReadFile[i]) == false) return;
                        if (!FileIsUse(strReadFile[i])) return;

                        File.Delete(strReadFile[i]);

                        _SysInfo.bAlive = true;
                        _tAliveTimer.Restart();
                    }
                }
                else
                {
                    if (_tAliveTimer.ElapsedMilliseconds > _Config.nAliveCheckTime)
                    {
                        _SysInfo.bAlive = false;
                        _tAliveTimer.Restart();
                    }
                }

            }
            else
            {
                _SysInfo.bAlive = true;         // Alive 사용안할시 항상 True
            }

        }

        private static bool FileIsUse(string strFilePath)
        {
            try
            {
                using (System.IO.FileStream fs = new System.IO.FileStream(strFilePath, System.IO.FileMode.Open, System.IO.FileAccess.Read, System.IO.FileShare.Read))
                {
                    //파일 닫기... 
                    fs.Close();
                }
            }
            catch (Exception ex)
            {
                return false;
            }
            return true;
        }


        static void LoadMasterIni(string strPath)
        {

            DateTime _UpdateTime = new DateTime();
            DateTime.TryParse(_IniFile.IniReadValue("COMMON", "TIME_UPDATE", "0", strPath), out _UpdateTime);

            if (_UpdateTime == _MasterLoadTime) return;         // 업데이트 시간과 로드시간이 일치한다면 수행하지 않음

            int nIndex = 1;

            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    int.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo._TipInfo[i].nTipMaxCount[j]);
                    int.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo._TipInfo[i].nTipSch[j]);
                }
            }

            bool bData = false;
            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    // 사용여부 파싱   
                    bool.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "False", strPath), out bData);
                    if (bData) { _ModelInfo._TipInfo[i].nSpare_a[j] = 1; }
                    else { _ModelInfo._TipInfo[i].nSpare_a[j] = 0; }

                    int.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo._TipInfo[i].nTipMaxCount[j + 5]);
                    int.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo._TipInfo[i].nTipSch[j + 5]);
                }
            }




            //nIndex = 101;

            //bool.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "False", strPath), out _ModelInfo.bPassOSCTest);

            //bool.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "False", strPath), out _ModelInfo.bPassNOSCTest);

            double.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo.dbNOSCgetCS);
            double.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo.dbNOSCSpecOpen);
            double.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo.dbNOSCSpecShort);


            double.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo.dbOSCgetCS);
            double.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo.dbOSCSpecOpen);
            double.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo.dbOSCSpecShort);


            //bool.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "False", strPath), out _ModelInfo.bPassNIRTest);
            double.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo.dbNIRInput);
            double.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo.dbNIRTestTime);
            double.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo.dbNIRLowLimit);

            //bool.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "False", strPath), out _ModelInfo.bPassPIRTest);
            double.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo.dbPIRInput);
            double.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo.dbPIRTestTime);
            double.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo.dbPIRLowLimit);

            //bool.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "False", strPath), out _ModelInfo.bPassGBTest);
            double.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo.dbGBInput);
            double.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo.dbGBTestTime);
            double.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo.dbGBHighLimit);

            // 
            //bool.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "False", strPath), out _ModelInfo.bPassNHIPOTTest);
            double.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo.dbNHIPOTInput);
            double.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo.dbNHIPOTTestTime);
            double.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo.dbNHIPOTLowLimit);

            //
            //bool.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "False", strPath), out _ModelInfo.bPassPHIPOTTest);
            double.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo.dbPHIPOTInput);
            double.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo.dbPHIPOTTestTime);
            double.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo.dbPHIPOTLowLimit);

            double.TryParse(_IniFile.IniReadValue("SPEC", String.Format("SPEC{0}", nIndex++), "0", strPath), out _ModelInfo.dbHipotRampTime);




            SaveModelInfo(_ModelInfo, _ModelInfo.strModelName);

            AppendLogMsg(String.Format("마스터 모델 로드 완료 : {0}", strPath), LOG_TYPE.LOG);

            _MasterLoadTime = _UpdateTime;
        }


        // 카운터 부저 프로세스
        public static void CounterBuzzerProcess(int nStation)
        {
            int nStepIndex = (int)PROC_LIST.COUNT_BUZZER1 + nStation;

            DO _nStationBuzzer = new DO();
            int nOnTime = 0;
            int nOffTime = 0;

            switch (nStation)
            {
                case 0: _nStationBuzzer = DO.STATION1_BUZZER; nOnTime = 60; nOffTime = 100; break;
                case 1: _nStationBuzzer = DO.STATION2_BUZZER; nOnTime = 60; nOffTime = 100; break;
                case 2: _nStationBuzzer = DO.STATION3_BUZZER; nOnTime = 60; nOffTime = 100; break;
                case 3: _nStationBuzzer = DO.STATION4_BUZZER; nOnTime = 60; nOffTime = 100; break;
                case 4: _nStationBuzzer = DO.STATION5_BUZZER; nOnTime = 60; nOffTime = 100; break;
                case 5: _nStationBuzzer = DO.HIPOT_BUZZER; nOnTime = 60; nOffTime = 60; break;
                case 6: _nStationBuzzer = DO.EOL_BUZZER; nOnTime = 60; nOffTime = 60; break;
                case 7: _nStationBuzzer = DO.LOADING_START_SW_BUZZER; nOnTime = 60; nOffTime = 100; break;
                case 8: _nStationBuzzer = DO.RELIFT_BUZZER; nOnTime = 60; nOffTime = 100; break;
            }

            switch (nProcessStep[nStepIndex])
            {
                case 0:
                    if (_SysInfo.nCount_Beep[nStation] > 0)
                    {
                        SetDIOPort(_nStationBuzzer, true);
                        tMainTimer[nStepIndex].Start(nOnTime);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 1:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    SetDIOPort(_nStationBuzzer, false);
                    tMainTimer[nStepIndex].Start(nOffTime);

                    if (_SysInfo.nCount_Beep[nStation] > 0) { _SysInfo.nCount_Beep[nStation]--; }
                    nProcessStep[nStepIndex]++;
                    break;

                case 2:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    nProcessStep[nStepIndex] = 0;
                    break;
            }
        }



        #region 타워램프
        public static void TowerLampProcess()
        {
            int nStepIndex = (int)PROC_LIST.TOWER_LAMP;

            switch (nProcessStep[nStepIndex])
            {
                case 0:
                    if (_SysInfo.TL_Red != TOWER_LAMP.TL_OFF) { SetDIOPort(DO.MAIN_TOWERLAMP_RED, true); }
                    else { SetDIOPort(DO.MAIN_TOWERLAMP_RED, false); }

                    if (_SysInfo.TL_Yellow != TOWER_LAMP.TL_OFF) { SetDIOPort(DO.MAIN_TOWERLAMP_YELLOW, true); }
                    else { SetDIOPort(DO.MAIN_TOWERLAMP_YELLOW, false); }

                    if (_SysInfo.TL_Green != TOWER_LAMP.TL_OFF) { SetDIOPort(DO.MAIN_TOWERLAMP_GREEN, true); }
                    else { SetDIOPort(DO.MAIN_TOWERLAMP_GREEN, false); }

                    if (!(_SysInfo.nTL_Beep > 0))
                    {
                        if (_SysInfo.TL_Buzzer != TOWER_LAMP.TL_OFF) { SetDIOPort(DO.MAIN_TOWERLAMP_BUZZER, true); }
                        else { SetDIOPort(DO.MAIN_TOWERLAMP_BUZZER, false); }
                    }

                    tMainTimer[nStepIndex].Start(500);
                    nProcessStep[nStepIndex]++;
                    break;


                case 1:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    if (_SysInfo.TL_Red == TOWER_LAMP.TL_ON) { SetDIOPort(DO.MAIN_TOWERLAMP_RED, true); }
                    else { SetDIOPort(DO.MAIN_TOWERLAMP_RED, false); }

                    if (_SysInfo.TL_Yellow == TOWER_LAMP.TL_ON) { SetDIOPort(DO.MAIN_TOWERLAMP_YELLOW, true); }
                    else { SetDIOPort(DO.MAIN_TOWERLAMP_YELLOW, false); }

                    if (_SysInfo.TL_Green == TOWER_LAMP.TL_ON) { SetDIOPort(DO.MAIN_TOWERLAMP_GREEN, true); }
                    else { SetDIOPort(DO.MAIN_TOWERLAMP_GREEN, false); }

                    if (!(_SysInfo.nTL_Beep > 0))
                    {
                        if (_SysInfo.TL_Buzzer == TOWER_LAMP.TL_ON) { SetDIOPort(DO.MAIN_TOWERLAMP_BUZZER, true); }
                        else { SetDIOPort(DO.MAIN_TOWERLAMP_BUZZER, false); }
                    }

                    tMainTimer[nStepIndex].Start(500);
                    nProcessStep[nStepIndex]++;
                    break;

                case 2:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    nProcessStep[nStepIndex] = 0;
                    break;
            }
        }

        public static void TowerBuzzerProcess()
        {

            int nStepIndex = (int)PROC_LIST.TOWER_BUZZER;

            switch (nProcessStep[nStepIndex])
            {
                case 0:
                    if (_SysInfo.nTL_Beep > 0)
                    {
                        SetDIOPort(DO.MAIN_TOWERLAMP_BUZZER, true);
                        tMainTimer[nStepIndex].Start(60);
                        nProcessStep[nStepIndex]++;
                    }
                    break;

                case 1:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }

                    SetDIOPort(DO.MAIN_TOWERLAMP_BUZZER, false);
                    tMainTimer[nStepIndex].Start(100);

                    if (_SysInfo.nTL_Beep > 0) { _SysInfo.nTL_Beep--; }
                    nProcessStep[nStepIndex]++;
                    break;

                case 2:
                    if (!tMainTimer[nStepIndex].Verify()) { break; }
                    nProcessStep[nStepIndex] = 0;
                    break;
            }
        }

        public static void TowerLampOn(LAMP_COLOR LAMP_Clr)
        {
            if (LAMP_Clr == LAMP_COLOR.TL_RED)
            {
                _SysInfo.TL_Red = TOWER_LAMP.TL_ON;
                _SysInfo.TL_Yellow = TOWER_LAMP.TL_OFF;
                _SysInfo.TL_Green = TOWER_LAMP.TL_OFF;
            }

            if (LAMP_Clr == LAMP_COLOR.TL_YELLOW)
            {
                _SysInfo.TL_Red = TOWER_LAMP.TL_OFF;
                _SysInfo.TL_Yellow = TOWER_LAMP.TL_ON;
                _SysInfo.TL_Green = TOWER_LAMP.TL_OFF;
            }

            if (LAMP_Clr == LAMP_COLOR.TL_GREEN)
            {
                _SysInfo.TL_Red = TOWER_LAMP.TL_OFF;
                _SysInfo.TL_Yellow = TOWER_LAMP.TL_OFF;
                _SysInfo.TL_Green = TOWER_LAMP.TL_ON;
            }
        }

        public static void TowerLampBlink(LAMP_COLOR LAMP_Clr)
        {
            if (LAMP_Clr == LAMP_COLOR.TL_RED)
            {
                _SysInfo.TL_Red = TOWER_LAMP.TL_BLINK;
                _SysInfo.TL_Yellow = TOWER_LAMP.TL_OFF;
                _SysInfo.TL_Green = TOWER_LAMP.TL_OFF;
            }

            if (LAMP_Clr == LAMP_COLOR.TL_YELLOW)
            {
                _SysInfo.TL_Red = TOWER_LAMP.TL_OFF;
                _SysInfo.TL_Yellow = TOWER_LAMP.TL_BLINK;
                _SysInfo.TL_Green = TOWER_LAMP.TL_OFF;
            }

            if (LAMP_Clr == LAMP_COLOR.TL_GREEN)
            {
                _SysInfo.TL_Red = TOWER_LAMP.TL_OFF;
                _SysInfo.TL_Yellow = TOWER_LAMP.TL_OFF;
                _SysInfo.TL_Green = TOWER_LAMP.TL_BLINK;
            }
        }
        #endregion

        // 검사존 바코드 정보 비교
        public static bool CheckContactBCDInfo(string strReadBCD, string strTargetBCD)
        {
            bool bResult = true;

            int nLen = 0;

            nLen = Math.Min(strReadBCD.Length, strTargetBCD.Length);

            for (int i = 0; i < nLen; i++)
            {
                if (strTargetBCD[i] != '*')
                {
                    if (strReadBCD[i] != strTargetBCD[i])
                    {
                        bResult = false;
                        break;
                    }
                }
            }

            return bResult;
        }


        //====== 로그 메세지 출력
        public static void AppendLogMsg(string str, LOG_TYPE type)
        {
            _mainform.BeginInvoke(new Action(() => _mainform.ViewLogMsg(str, type)));
        }



        //====== 기타 바코드 리딩 프로세스 ==========================
        static void SUB_ETCBCD_READ()
        {
            int nStepIndex = (int)PROC_LIST.ETC_BCD_READ;

            switch (nProcessStep[nStepIndex])
            {
                case 0:
                    _ETCReader.bReadOk = false;
                    nProcessStep[nStepIndex]++;
                    break;


                case 1:
                    if (_ETCReader.bReadOk)
                    {
                        _ETCReader.bReadOk = false;
                        _SysInfo.strETCReadData = _ETCReader.strReadBarcode;
                        nProcessStep[nStepIndex]++;
                    }
                    break;



                case 2:
                    try
                    {

                        if (!_ModelInfo._EtcDataScan[1].CheckBarcode(_SysInfo.strETCReadData))
                        {
                            AppendLogMsg("이종품 검사 - 바코드가 일치하지 않습니다!!", LOG_TYPE.ERROR);
                            _SysInfo.nTL_Beep = 2;
                        }

                        //if (_SysInfo.strETCReadData.Substring(0, Math.Min(_SysInfo.strETCReadData.Length, _ModelInfo.strFuseSymbol.Length)) == _ModelInfo.strFuseSymbol)
                        //{
                        //    _SysInfo.bETCReadOk = true;
                        //}
                        //else if (_SysInfo.strETCReadData.Substring(0, Math.Min(_SysInfo.strETCReadData.Length, _ModelInfo.strETC1BCD.Length)) == _ModelInfo.strETC1BCD)
                        //{
                        //    _SysInfo.bETCScan1 = true;
                        //}
                        //else if (_SysInfo.strETCReadData.Substring(0, Math.Min(_SysInfo.strETCReadData.Length, _ModelInfo.strETC2BCD.Length)) == _ModelInfo.strETC2BCD)
                        //{
                        //    _SysInfo.bETCScan2 = true;
                        //}
                        //else if (_SysInfo.strETCReadData.Substring(0, Math.Min(_SysInfo.strETCReadData.Length, _ModelInfo.strETC3BCD.Length)) == _ModelInfo.strETC3BCD)
                        //{
                        //    _SysInfo.bETCScan3 = true;
                        //}
                        //else
                        //{
                        //    AppendLogMsg("이종품 검사 - 바코드가 일치하지 않습니다!!", LOG_TYPE.ERROR);
                        //    _SysInfo.nTL_Beep = 2;
                        //}
                    }
                    catch
                    {
                        AppendLogMsg("이종품 검사 - 이종품 바코드 설정이 잘못되었습니다!!", LOG_TYPE.ERROR);
                        _SysInfo.nTL_Beep = 2;
                    }
                    nProcessStep[nStepIndex] = 0;
                    break;

            }
        }

        #region CommPort 초기화
        // 포트 초기화 및 시작
        public static void InitCommPort()
        {

            //====== 배터리 테스터
            _HipotTester.SetPort(String.Format("COM{0}", _Config.nBatteryComm1), 9600, Parity.None, 8, StopBits.One);
            if (_HipotTester.PortOpen())
            {
                AppendLogMsg(String.Format("<COM{0}> HIPOT Tester Port Open Success", _Config.nBatteryComm1), LOG_TYPE.INFO);

            }
            else
            {
                AppendLogMsg(String.Format("<COM{0}> HIPOT Tester Port Open Fail", _Config.nBatteryComm1), LOG_TYPE.ERROR);
            }




            _BatteryTester[1].SetPort(String.Format("COM{0}", _Config.nBatteryComm2), 9600, Parity.None, 8, StopBits.One);
            if (_BatteryTester[1].PortOpen())
            {
                AppendLogMsg(String.Format("<COM{0}> EOL Tester Port Open Success", _Config.nBatteryComm2), LOG_TYPE.INFO);
                _BatteryTester[1].nStation = 2;
                //_BatteryTester[1].Start();
            }
            else
            {
                AppendLogMsg(String.Format("<COM{0}> EOL Teste Port Open Fail", _Config.nBatteryComm2), LOG_TYPE.ERROR);
            }

            ///// ===== 너트러너
            _NutRunner[0].SetPort(String.Format("COM{0}", _Config.nNutRunner1), 9600, Parity.None, 8, StopBits.One);
            if (_NutRunner[0].PortOpen())
            {
                AppendLogMsg(String.Format("<COM{0}> NutRunner #1 Port Open Success", _Config.nNutRunner1), LOG_TYPE.INFO);
                _NutRunner[0].nStation = 1;
                _NutRunner[0].Start();
            }
            else
            {
                AppendLogMsg(String.Format("<COM{0}> NutRunner #1 Port Open Fail", _Config.nNutRunner1), LOG_TYPE.ERROR);
            }


            _NutRunner[1].SetPort(String.Format("COM{0}", _Config.nNutRunner2), 9600, Parity.None, 8, StopBits.One);
            if (_NutRunner[1].PortOpen())
            {
                AppendLogMsg(String.Format("<COM{0}> NutRunner #2 Port Open Success", _Config.nNutRunner2), LOG_TYPE.INFO);
                _NutRunner[1].nStation = 2;
                _NutRunner[1].Start();
            }
            else
            {
                AppendLogMsg(String.Format("<COM{0}> NutRunner #2 Port Open Fail", _Config.nNutRunner2), LOG_TYPE.ERROR);
            }

            _NutRunner[2].SetPort(String.Format("COM{0}", _Config.nNutRunner3), 9600, Parity.None, 8, StopBits.One);
            if (_NutRunner[2].PortOpen())
            {
                AppendLogMsg(String.Format("<COM{0}> NutRunner #3 Port Open Success", _Config.nNutRunner3), LOG_TYPE.INFO);
                _NutRunner[2].nStation = 3;
                _NutRunner[2].Start();
            }
            else
            {
                AppendLogMsg(String.Format("<COM{0}> NutRunner #3 Port Open Fail", _Config.nNutRunner3), LOG_TYPE.ERROR);
            }


            _NutRunner[3].SetPort(String.Format("COM{0}", _Config.nNutRunner4), 9600, Parity.None, 8, StopBits.One);
            if (_NutRunner[3].PortOpen())
            {
                AppendLogMsg(String.Format("<COM{0}> NutRunner #4 Port Open Success", _Config.nNutRunner4), LOG_TYPE.INFO);
                _NutRunner[3].nStation = 4;
                _NutRunner[3].Start();
            }
            else
            {
                AppendLogMsg(String.Format("<COM{0}> NutRunner #4 Port Open Fail", _Config.nNutRunner4), LOG_TYPE.ERROR);
            }



            _NutRunner[4].SetPort(String.Format("COM{0}", _Config.nNutRunner5), 9600, Parity.None, 8, StopBits.One);
            if (_NutRunner[4].PortOpen())
            {
                AppendLogMsg(String.Format("<COM{0}> NutRunner #5 Port Open Success", _Config.nNutRunner5), LOG_TYPE.INFO);
                _NutRunner[4].nStation = 5;
                _NutRunner[4].Start();
            }
            else
            {
                AppendLogMsg(String.Format("<COM{0}> NutRunner #5 Port Open Fail", _Config.nNutRunner5), LOG_TYPE.ERROR);
            }


            _NutRunner[5].SetPort(String.Format("COM{0}", _Config.nNutRunner6), 9600, Parity.None, 8, StopBits.One);
            if (_NutRunner[5].PortOpen())
            {
                AppendLogMsg(String.Format("<COM{0}> NutRunner #LIFT Port Open Success", _Config.nNutRunner6), LOG_TYPE.INFO);
                _NutRunner[5].nStation = 6;
                _NutRunner[5].Start();
            }
            else
            {
                AppendLogMsg(String.Format("<COM{0}> NutRunner #LIFT Port Open Fail", _Config.nNutRunner6), LOG_TYPE.ERROR);
            }



            _ST1Reader.SetPort(String.Format("COM{0}", _Config.nStation1Reader), 115200, Parity.None, 8, StopBits.One);
            if (_ST1Reader.PortOpen())
            {
                _ST1Reader.nIndex = 1;
                AppendLogMsg(String.Format("<COM{0}> Station #1 Barcode Reader Port Open Success", _Config.nStation1Reader), LOG_TYPE.INFO);
                _ST1Reader.Start();
            }
            else
            {
                AppendLogMsg(String.Format("<COM{0}> Station #1 Barcode Reader Port Open Fail", _Config.nStation1Reader), LOG_TYPE.ERROR);
            }



            _BCDReader.SetPort(String.Format("COM{0}", _Config.nBcdReader), 115200, Parity.None, 8, StopBits.One);
            if (_BCDReader.PortOpen())
            {
                _BCDReader.nIndex = 3;
                AppendLogMsg(String.Format("<COM{0}> Barcode Reader #1 Port Open Success", _Config.nBcdReader), LOG_TYPE.INFO);
                _BCDReader.Start();
            }
            else
            {
                AppendLogMsg(String.Format("<COM{0}> Barcode Reader #1 Port Open Fail", _Config.nBcdReader), LOG_TYPE.ERROR);
            }


            _ETCReader.SetPort(String.Format("COM{0}", _Config.nETCReader), 115200, Parity.None, 8, StopBits.One);
            if (_ETCReader.PortOpen())
            {
                _ETCReader.nIndex = 2;
                AppendLogMsg(String.Format("<COM{0}> Barcode Reader #2 Port Open Success", _Config.nETCReader), LOG_TYPE.INFO);
                _ETCReader.Start();
            }
            else
            {
                AppendLogMsg(String.Format("<COM{0}> Barcode Reader #2 Port Open Fail", _Config.nETCReader), LOG_TYPE.ERROR);
            }


            _BCDPrint.SetPort(String.Format("COM{0}", _Config.nBcdPrinter), 9600, Parity.None, 8, StopBits.One);
            if (_BCDPrint.PortOpen())
            {
                AppendLogMsg(String.Format("<COM{0}> Barcode Printer Port Open Success", _Config.nBcdPrinter), LOG_TYPE.INFO);
                _BCDPrint.Start();
            }
            else
            {
                AppendLogMsg(String.Format("<COM{0}> Barcode Printer Port Open Fail", _Config.nBcdPrinter), LOG_TYPE.ERROR);
            }


            _EOLReader.SetPort(String.Format("COM{0}", _Config.nEolReader), 115200, Parity.None, 8, StopBits.One);
            if (_EOLReader.PortOpen())
            {
                _EOLReader.nIndex = 7;
                AppendLogMsg(String.Format("<COM{0}> EOL Barcode Reader Port Open Success", _Config.nEolReader), LOG_TYPE.INFO);
                _EOLReader.Start();
            }
            else
            {
                AppendLogMsg(String.Format("<COM{0}> EOL Barcode Reader Port Open Fail", _Config.nEolReader), LOG_TYPE.ERROR);
            }

            _HIPOTReader.SetPort(String.Format("COM{0}", _Config.nHipotReader), 115200, Parity.None, 8, StopBits.One);
            if (_HIPOTReader.PortOpen())
            {
                _HIPOTReader.nIndex = 6;
                AppendLogMsg(String.Format("<COM{0}> HIPOT Barcode Reader Port Open Success", _Config.nHipotReader), LOG_TYPE.INFO);
                _HIPOTReader.Start();
            }
            else
            {
                AppendLogMsg(String.Format("<COM{0}> HIPOT Barcode Reader Port Open Fail", _Config.nHipotReader), LOG_TYPE.ERROR);
            }


            _HipotHandReader.SetPort(String.Format("COM{0}", _Config.nHipotHnadReader), 115200, Parity.None, 8, StopBits.One);
            if (_HipotHandReader.PortOpen())
            {
                _HipotHandReader.nIndex = 6;
                AppendLogMsg(String.Format("<COM{0}> HIPOT Hand Barcode Reader Port Open Success", _Config.nHipotHnadReader), LOG_TYPE.INFO);
                _HipotHandReader.Start();
            }
            else
            {
                AppendLogMsg(String.Format("<COM{0}> HIPOT Hand Barcode Reader Port Open Fail", _Config.nHipotHnadReader), LOG_TYPE.ERROR);
            }

            _EOLHandReader.SetPort(String.Format("COM{0}", _Config.nEOLHandReader), 115200, Parity.None, 8, StopBits.One);
            if (_EOLHandReader.PortOpen())
            {
                _EOLHandReader.nIndex = 7;
                AppendLogMsg(String.Format("<COM{0}> EOL Hand Barcode Reader Port Open Success", _Config.nEOLHandReader), LOG_TYPE.INFO);
                _EOLHandReader.Start();
            }
            else
            {
                AppendLogMsg(String.Format("<COM{0}> EOL Hand Barcode Reader Port Open Fail", _Config.nEOLHandReader), LOG_TYPE.ERROR);
            }

            //_TPCRobot.SetPort(String.Format("COM{0}", _Config.nTPCRobot), _Config.nTPCRobotBaudRate, Parity.None, 8, StopBits.One);
            //if (_TPCRobot.PortOpen())
            //{
            //    AppendLogMsg(String.Format("<COM{0}> TPC ROBOT Port Open Success", _Config.nTPCRobot), LOG_TYPE.INFO);
            //    _TPCRobot.Start();
            //}
            //else
            //{
            //    AppendLogMsg(String.Format("<COM{0}> TPC ROBOT Port Open Fail", _Config.nTPCRobot), LOG_TYPE.ERROR);
            //}

            //_TesterDistance.SetPort(String.Format("COM{0}", _Config.nDistancePort), _Config.nDistanceBaudRate, Parity.None, 8, StopBits.One);
            //if (_TesterDistance.PortOpen())
            //{
            //    AppendLogMsg(String.Format("<COM{0}> Distance Unit Port Open Success", _Config.nDistancePort), LOG_TYPE.INFO);
            //}
            //else
            //{
            //    AppendLogMsg(String.Format("<COM{0}> Distance Unit Port Open Fail", _Config.nDistancePort), LOG_TYPE.ERROR);
            //}


            _Arm.SetPort(String.Format("COM{0}", _Config.nArmPort), 9600, Parity.None, 8, StopBits.One);
            if (_Arm.PortOpen())
            {
                AppendLogMsg(String.Format("<COM{0}> ArmXY Port Open Success", _Config.nArmPort), LOG_TYPE.INFO);

            }
            else
            {
                AppendLogMsg(String.Format("<COM{0}> ArmXY Port Open Fail", _Config.nArmPort), LOG_TYPE.ERROR);
            }


            // 레이저 마킹 관련
            _LaserMarking.SetPort(String.Format("COM{0}", _Config.nLaserMarkingPort), _Config.nLaserMarkingBaudRate, Parity.None, 8, StopBits.One);
            if (_LaserMarking.PortOpen())
            {
                AppendLogMsg(String.Format("<COM{0}> 레이저 마킹기 통신 포트 오픈 성공", _Config.nLaserMarkingPort), LOG_TYPE.INFO);

            }
            else
            {
                AppendLogMsg(String.Format("<COM{0}> 레이저 마킹기 통신 포트 오픈 실패", _Config.nLaserMarkingPort), LOG_TYPE.ERROR);
            }


            //====== 배터리 테스터
            _LaserReader.SetPort(String.Format("COM{0}", _Config.nLaserBCDReaderPort), _Config.nLaserBCDReaderBaudRate, Parity.None, 8, StopBits.One);
            if (_LaserReader.PortOpen())
            {
                _LaserReader.nIndex = 5;
                AppendLogMsg(String.Format("<COM{0}> 레이저 마킹기 스캐너 포트 오픈 성공", _Config.nLaserBCDReaderPort), LOG_TYPE.INFO);

            }
            else
            {
                AppendLogMsg(String.Format("<COM{0}> 레이저 마킹기 스캐너 포트 오픈 실패", _Config.nLaserBCDReaderPort), LOG_TYPE.ERROR);
            }

            // 외함측정 포트 오픈
            _OmronWHTester.strIP = _Config.strOmronWHTesterIP;
            _OmronWHTester.nPort = _Config.nOmronWHTesterPort;
            _OmronWHTester.SetPort();

            //_ArmXYZ.SetPort(String.Format("COM{0}", _Config.nArmXYZPort), _Config.nArmXYZBaudRate, Parity.None, 8, StopBits.One);
            //if (_ArmXYZ.PortOpen())
            //{
            //    AppendLogMsg(String.Format("<COM{0}> ArmXYZ Port Open Success", _Config.nArmXYZPort), LOG_TYPE.INFO);

            //}
            //else
            //{
            //    AppendLogMsg(String.Format("<COM{0}> ArmXYZ Port Open Fail", _Config.nArmXYZPort), LOG_TYPE.ERROR);
            //}

            _BatteryTester2.SetPort(String.Format("COM{0}", _Config.nBatteryChargeTest), 9600, Parity.None, 8, StopBits.One);
            if (_BatteryTester2.PortOpen())
            {
                _BatteryTester2.nStation = 3;
                AppendLogMsg(String.Format("<COM{0}> 충방전 시험기 통신 포트 오픈 성공", _Config.nBatteryChargeTest), LOG_TYPE.ERROR);
                _BatteryTester2.Start();
            }
            else
            {
                AppendLogMsg(String.Format("<COM{0}> 충방전 시험기 통신 포트 오픈 실패", _Config.nBatteryChargeTest), LOG_TYPE.ERROR);
            }
            

            //_nutEth.nPort = 4545;
            //_nutEth.nNutrunnerIndex = 1;
            //_nutEth.strIP = "192.168.0.186";
            //_nutEth.SetPort();

            // 너트러너 이더넷 모드를 사용할 경우
            if (_Config.bUseNutrunnerEthMode)
            {
                for (int i = 0; i < 6; i++)
                {
                    if (_Config.bUseNutrunner[i])
                    {
                        _NutRunnerEth[i].strIP = _Config.strNutrunnerIP[i];
                        _NutRunnerEth[i].nPort = _Config.nNutrunnerPort[i];
                        _NutRunnerEth[i].nStation = i + 1;
                        _NutRunnerEth[i].SetPort();
                    }
                }
            }
        }
        #endregion


        public static bool CheckMotionPosErr(AXIS _Axis, double pos)
        {
            bool bFlag = false;

            double dbActPos = 0.0;
            double dbCmdPos = 0.0;

            CAXM.AxmStatusGetActPos((int)_Axis, ref dbActPos);
            CAXM.AxmStatusGetCmdPos((int)_Axis, ref dbCmdPos);


            //if (Math.Abs(dbActPos - pos) > 3.0)            // 지령좌표와 ActPos 간의 차이가 10mm 이상 난다면 알람.
            //{
            //    bFlag = true;
            //    AppendLogMsg(String.Format("{0}축 좌표 이상 발생!! (지령위치 : {1:F2},  Cmd : {2:F2}, Act : {3:F2}, 오차 : {4:F2})", (AXIS)_Axis, pos, dbCmdPos, dbActPos, Math.Abs(dbActPos - pos)), LOG_TYPE.ERROR);
            //}
            //else
            //{
            //    bFlag = false;
            //}

            return bFlag;
        }


        // 모션 완료 체크
        public static bool MotionDone(AXIS eAXIS)
        {
            int nAxis = (int)eAXIS;
            uint Status = 0;
            CAXM.AxmStatusReadInMotion(nAxis, ref Status);
            return (Status != 0) ? false : true;
        }

        // 축 1개 절대 좌표 운전
        public static void MoveTo(AXIS eAXIS, double dbPos, double dbSpeed, double AccelTime)
        {
            int nAxis = (int)eAXIS;
            CAXM.AxmMotSetAbsRelMode(nAxis, (uint)AXT_MOTION_ABSREL.POS_ABS_MODE);
            CAXM.AxmMotSetProfileMode(nAxis, (uint)AXT_MOTION_PROFILE_MODE.SYM_TRAPEZOIDE_MODE);
            CAXM.AxmMoveStartPos(nAxis, dbPos, Math.Min(dbSpeed, _MotorAxisInfo[nAxis].dbMaxSpeed), AccelTime, AccelTime);
        }

        public static void MoveTo(AXIS eAXIS, double dbPos, double dbSpeed)
        {
            int nAxis = (int)eAXIS;
            CAXM.AxmMotSetAbsRelMode(nAxis, (uint)AXT_MOTION_ABSREL.POS_ABS_MODE);
            CAXM.AxmMotSetProfileMode(nAxis, (uint)AXT_MOTION_PROFILE_MODE.SYM_TRAPEZOIDE_MODE);
            CAXM.AxmMoveStartPos(nAxis, dbPos, Math.Min(dbSpeed, _MotorAxisInfo[nAxis].dbMaxSpeed), _MotorAxisInfo[nAxis].dbAccelTime, _MotorAxisInfo[nAxis].dbAccelTime);
        }

        // 축 1개 상대 좌표 운전
        public static void Move(AXIS eAXIS, double dbPos, double dbSpeed, double AccelTime)
        {
            if (dbPos == 0.0)
                return;

            int nAxis = (int)eAXIS;
            CAXM.AxmMotSetAbsRelMode(nAxis, (uint)AXT_MOTION_ABSREL.POS_REL_MODE);
            CAXM.AxmMotSetProfileMode(nAxis, (uint)AXT_MOTION_PROFILE_MODE.SYM_TRAPEZOIDE_MODE);
            CAXM.AxmMoveStartPos(nAxis, dbPos, Math.Min(dbSpeed, _MotorAxisInfo[nAxis].dbMaxSpeed), AccelTime, AccelTime);
        }

        public static void Move(AXIS eAXIS, double dbPos, double dbSpeed)
        {
            if (dbPos == 0.0)
                return;

            int nAxis = (int)eAXIS;
            CAXM.AxmMotSetAbsRelMode(nAxis, (uint)AXT_MOTION_ABSREL.POS_REL_MODE);
            CAXM.AxmMotSetProfileMode(nAxis, (uint)AXT_MOTION_PROFILE_MODE.SYM_TRAPEZOIDE_MODE);
            CAXM.AxmMoveStartPos(nAxis, dbPos, Math.Min(dbSpeed, _MotorAxisInfo[nAxis].dbMaxSpeed), _MotorAxisInfo[nAxis].dbAccelTime, _MotorAxisInfo[nAxis].dbAccelTime);
        }

        // 축 2개 절대좌표 보간 운전
        public static void MoveToXY(double x, double y, double dbSpeed)
        {
            int[] nAxis = new int[2];
            double[] dbPos = new double[2];

            uint[] uPositiveStatus = new uint[2];
            uint[] uNegativeStatus = new uint[2];

            double dbCurrentSpeed = new double();
            double dbCurrentAccTime = new double();

            dbPos[0] = x;
            dbPos[1] = y;

            nAxis[0] = (int)AXIS.X;
            nAxis[1] = (int)AXIS.Y;


            // 리미트 여부 읽어옴
            CAXM.AxmSignalReadLimit(nAxis[0], ref uPositiveStatus[0], ref uNegativeStatus[0]);
            CAXM.AxmSignalReadLimit(nAxis[1], ref uPositiveStatus[1], ref uNegativeStatus[1]);


            // 소프트웨어 리미트 사용시 현재위치가 리미트 설정내에 있는지 검사
            if (_Config.bUseSoftwareLimit)
            {
                double dblPosX = 0.0;
                double dblPosY = 0.0;


                CAXM.AxmStatusGetCmdPos(nAxis[0], ref dblPosX);
                CAXM.AxmStatusGetCmdPos(nAxis[1], ref dblPosY);


                if (dblPosX <= _MotorAxisInfo[nAxis[0]].dbNegativeLimit + 0.1) uNegativeStatus[0] = 1;
                if (dblPosX >= _MotorAxisInfo[nAxis[0]].dbPositiveLimit - 0.1) uPositiveStatus[0] = 1;

                if (dblPosY <= _MotorAxisInfo[nAxis[1]].dbNegativeLimit + 0.1) uNegativeStatus[1] = 1;
                if (dblPosY >= _MotorAxisInfo[nAxis[1]].dbPositiveLimit - 0.1) uPositiveStatus[1] = 1;


            }


            if (uNegativeStatus[0] > 0 || uPositiveStatus[0] > 0 || uNegativeStatus[1] > 0 || uPositiveStatus[1] > 0)
            {
                MoveTo((AXIS)nAxis[0], dbPos[0], dbSpeed);
                MoveTo((AXIS)nAxis[1], dbPos[1], dbSpeed);
            }
            else
            {
                dbCurrentAccTime = Math.Max(_MotorAxisInfo[nAxis[0]].dbAccelTime, _MotorAxisInfo[nAxis[1]].dbAccelTime);

                dbCurrentSpeed = Math.Min(_MotorAxisInfo[nAxis[0]].dbMaxSpeed, _MotorAxisInfo[nAxis[1]].dbMaxSpeed);
                dbCurrentSpeed = Math.Min(dbCurrentSpeed, dbSpeed);

                CAXM.AxmContiWriteClear(0);
                CAXM.AxmContiSetAxisMap(0, 2, nAxis);
                CAXDev.AxmContiSetProfileMode(0, (uint)AXT_MOTION_PROFILE_MODE.ASYM_TRAPEZOIDE_MODE);
                CAXM.AxmContiSetAbsRelMode(0, (uint)AXT_MOTION_ABSREL.POS_ABS_MODE);

                CAXM.AxmContiBeginNode(0);
                CAXM.AxmLineMove(0, dbPos, dbCurrentSpeed, dbCurrentAccTime, dbCurrentAccTime);
                CAXM.AxmContiEndNode(0);

                CAXM.AxmContiStart(0, (uint)AXT_MOTION_CONTISTART_NODE.CONTI_NODE_VELOCITY, 0);

            }


        }

        // 축 3개 절대좌표 보간 운전
        public static void MoveToXYZ(double x, double y, double z, double dbSpeed)
        {
            int[] nAxis = new int[3];
            double[] dbPos = new double[3];

            uint[] uPositiveStatus = new uint[3];
            uint[] uNegativeStatus = new uint[3];

            double dbCurrentSpeed = new double();
            double dbCurrentAccTime = new double();

            dbPos[0] = x;
            dbPos[1] = y;
            dbPos[2] = z;

            nAxis[0] = (int)AXIS.X;
            nAxis[1] = (int)AXIS.Y;
            nAxis[2] = (int)AXIS.Z;

            // 리미트 여부 읽어옴
            CAXM.AxmSignalReadLimit(nAxis[0], ref uPositiveStatus[0], ref uNegativeStatus[0]);
            CAXM.AxmSignalReadLimit(nAxis[1], ref uPositiveStatus[1], ref uNegativeStatus[1]);
            CAXM.AxmSignalReadLimit(nAxis[2], ref uPositiveStatus[2], ref uNegativeStatus[2]);

            // 소프트웨어 리미트 사용시 현재위치가 리미트 설정내에 있는지 검사
            if (_Config.bUseSoftwareLimit)
            {
                double dblPosX = 0.0;
                double dblPosY = 0.0;
                double dblPosZ = 0.0;


                CAXM.AxmStatusGetCmdPos(nAxis[0], ref dblPosX);
                CAXM.AxmStatusGetCmdPos(nAxis[1], ref dblPosY);
                CAXM.AxmStatusGetCmdPos(nAxis[2], ref dblPosZ);

                if (dblPosX <= _MotorAxisInfo[nAxis[0]].dbNegativeLimit + 0.1) uNegativeStatus[0] = 1;
                if (dblPosX >= _MotorAxisInfo[nAxis[0]].dbPositiveLimit - 0.1) uPositiveStatus[0] = 1;

                if (dblPosY <= _MotorAxisInfo[nAxis[1]].dbNegativeLimit + 0.1) uNegativeStatus[1] = 1;
                if (dblPosY >= _MotorAxisInfo[nAxis[1]].dbPositiveLimit - 0.1) uPositiveStatus[1] = 1;

                if (dblPosZ <= _MotorAxisInfo[nAxis[2]].dbNegativeLimit + 0.1) uNegativeStatus[2] = 1;
                if (dblPosZ >= _MotorAxisInfo[nAxis[2]].dbPositiveLimit - 0.1) uPositiveStatus[2] = 1;

            }


            if (uNegativeStatus[0] > 0 || uPositiveStatus[0] > 0 || uNegativeStatus[1] > 0 || uPositiveStatus[1] > 0 || uNegativeStatus[2] > 0 || uPositiveStatus[2] > 0)
            {
                MoveTo((AXIS)nAxis[0], dbPos[0], dbSpeed);
                MoveTo((AXIS)nAxis[1], dbPos[1], dbSpeed);
                MoveTo((AXIS)nAxis[2], dbPos[2], dbSpeed);
            }
            else
            {
                dbCurrentAccTime = Math.Max(Math.Max(_MotorAxisInfo[nAxis[0]].dbAccelTime, _MotorAxisInfo[nAxis[1]].dbAccelTime), _MotorAxisInfo[nAxis[2]].dbAccelTime);

                dbCurrentSpeed = Math.Min(Math.Min(_MotorAxisInfo[nAxis[0]].dbMaxSpeed, _MotorAxisInfo[nAxis[1]].dbMaxSpeed), _MotorAxisInfo[nAxis[2]].dbMaxSpeed);
                dbCurrentSpeed = Math.Min(dbCurrentSpeed, dbSpeed);

                CAXM.AxmContiWriteClear(0);
                CAXM.AxmContiSetAxisMap(0, 3, nAxis);
                CAXDev.AxmContiSetProfileMode(0, (uint)AXT_MOTION_PROFILE_MODE.ASYM_TRAPEZOIDE_MODE);
                CAXM.AxmContiSetAbsRelMode(0, (uint)AXT_MOTION_ABSREL.POS_ABS_MODE);

                CAXM.AxmContiBeginNode(0);
                CAXM.AxmLineMove(0, dbPos, dbCurrentSpeed, dbCurrentAccTime, dbCurrentAccTime);
                CAXM.AxmContiEndNode(0);

                CAXM.AxmContiStart(0, (uint)AXT_MOTION_CONTISTART_NODE.CONTI_NODE_VELOCITY, 0);

            }


        }

        public static void MoveVel(AXIS eAXIS, double dbspeed, int nDir)
        {
            dbspeed = Math.Min(_MotorAxisInfo[(int)eAXIS].dbMaxSpeed, dbspeed);

            if (nDir != 0)
                dbspeed += -0.1;

            CAXM.AxmMoveVel((int)eAXIS, dbspeed, _MotorAxisInfo[(int)eAXIS].dbAccelTime, _MotorAxisInfo[(int)eAXIS].dbAccelTime);
        }

        public static void MoveVelOverride(AXIS eAXIS, double dbspeed, int nDir)
        {
            dbspeed = Math.Min(_MotorAxisInfo[(int)eAXIS].dbMaxSpeed, dbspeed);

            if (nDir != 0)
                dbspeed += -0.1;


            CAXM.AxmOverrideAccelVelDecel((int)eAXIS, dbspeed, _MotorAxisInfo[(int)eAXIS].dbAccelTime, _MotorAxisInfo[(int)eAXIS].dbAccelTime);
        }


        // 소프트 웨어 리미트 켜기
        public static void AxmUserSetSoftwareLimitEnable(AXIS axis, bool bNUse, bool bPUse)
        {
            uint dwQiUCFG3 = 0;

            CAXDev.AxmGetCommandData32Qi((int)axis, (byte)Shared.AxtMotDef.QICOMMAND.QiUCFG3Read, ref dwQiUCFG3);

            dwQiUCFG3 &= 0xFCCF;

            if (bNUse) dwQiUCFG3 |= 0x0020;
            if (bPUse) dwQiUCFG3 |= 0x0010;

            CAXDev.AxmSetCommandData32Qi((int)axis, (byte)Shared.AxtMotDef.QICOMMAND.QiUCFG3Write, dwQiUCFG3);
            Thread.Sleep(1);
        }


        public static void AxmUserSetSoftwareLimitPosition(AXIS axis, double dNPosition, double dPPosition)
        {
            int npPulse = 0;
            double dpUnit = 0;
            double dCurPosition = 0;
            double dQiPosition = 0;
            double dPositionOffset = 0;
            uint dwQiPosition = 0;


            uint dwSNSMT;
            uint dwSPSMT;


            CAXM.AxmMotGetMoveUnitPerPulse((int)axis, ref dpUnit, ref npPulse);


            CAXM.AxmStatusGetCmdPos((int)axis, ref dCurPosition);

            CAXDev.AxmGetCommandData32Qi((int)axis, (byte)Shared.AxtMotDef.QICOMMAND.QiCNT1Read, ref dwQiPosition);

            dQiPosition = (double)(long)dwQiPosition * dpUnit / (double)npPulse;
            dPositionOffset = dCurPosition - dQiPosition;

            dwSNSMT = (uint)((dNPosition - dPositionOffset) * (double)npPulse / dpUnit);
            dwSPSMT = (uint)((dPPosition - dPositionOffset) * (double)npPulse / dpUnit);


            CAXDev.AxmSetCommandData32Qi((int)axis, (byte)Shared.AxtMotDef.QICOMMAND.QiSNSMTWrite, dwSNSMT);
            CAXDev.AxmSetCommandData32Qi((int)axis, (byte)Shared.AxtMotDef.QICOMMAND.QiSPSMTWrite, dwSPSMT);

            Thread.Sleep(1);
        }





        public static void InitMotion()
        {
            for (int i = (int)AXIS.X; i <= (int)AXIS.ST3_R; i++)
            {
                CAXM.AxmSignalSetServoOnLevel(i, (int)AXT_MOTION_LEVEL_MODE.HIGH);
                CAXM.AxmSignalServoOn(i, 0);
                CAXM.AxmMoveEStop(i);


                if ((AXIS)i == AXIS.HIPOT_2Y || (AXIS)i == AXIS.HIPOT_1Y || (AXIS)i == AXIS.EOL_Y || (AXIS)i == AXIS.ST3_R)
                {
                    CAXM.AxmSignalSetLimit(i, (int)AXT_MOTION_STOPMODE.EMERGENCY_STOP, (int)AXT_MOTION_LEVEL_MODE.UNUSED, (int)AXT_MOTION_LEVEL_MODE.UNUSED);
                }
                else if ((AXIS)i == AXIS.R /*|| (AXIS)i == AXIS.BOLT_R1 || (AXIS)i == AXIS.BOLT_R2 || (AXIS)i == AXIS.BOLT_R3 || (AXIS)i == AXIS.BOLT_R4*/)
                {
                    CAXM.AxmSignalSetLimit(i, (int)AXT_MOTION_STOPMODE.EMERGENCY_STOP, (int)AXT_MOTION_LEVEL_MODE.UNUSED, (int)AXT_MOTION_LEVEL_MODE.UNUSED);
                }
                else
                {
                    CAXM.AxmSignalSetLimit(i, (int)AXT_MOTION_STOPMODE.EMERGENCY_STOP, (int)AXT_MOTION_LEVEL_MODE.LOW, (int)AXT_MOTION_LEVEL_MODE.LOW);
                }


                CAXM.AxmSignalSetInpos(i, 1);
                CAXM.AxmSignalSetServoAlarm(i, (int)AXT_MOTION_LEVEL_MODE.LOW);
                CAXM.AxmSignalSetStop(i, (int)AXT_MOTION_STOPMODE.EMERGENCY_STOP, (int)AXT_MOTION_LEVEL_MODE.UNUSED);
                CAXM.AxmMotSetMoveUnitPerPulse(i, 1.0, 100);
                CAXM.AxmSignalSetSoftLimit(i, (int)AXT_USE.DISABLE, (int)AXT_MOTION_STOPMODE.EMERGENCY_STOP, (int)AXT_MOTION_SELECTION.COMMAND, 100.0, 0.0);
                CAXM.AxmMotSetMinVel(i, 0.01);
                CAXM.AxmMotSetMaxVel(i, _MotorAxisInfo[i].dbMaxSpeed);
                CAXM.AxmMotSetAccelUnit(i, (int)AXT_MOTION_ACC_UNIT.SEC);
                CAXM.AxmMotSetAbsRelMode(i, (int)AXT_MOTION_ABSREL.POS_REL_MODE);
                CAXM.AxmMotSetProfileMode(i, (int)AXT_MOTION_PROFILE_MODE.SYM_S_CURVE_MODE);
                CAXM.AxmStatusSetCmdPos(i, 0.0);
                CAXM.AxmStatusSetActPos(i, 0.0);
            }

            for (int i = (int)AXIS.CAMERA1_X; i <= (int)AXIS.CAMERA2_Z; i++)
            {
                CAXM.AxmSignalSetServoOnLevel(i, (int)AXT_MOTION_LEVEL_MODE.HIGH);

                CAXM.AxmSignalServoOn(i, 0);

                CAXM.AxmMoveEStop(i);
                CAXM.AxmSignalSetLimit(i, (int)AXT_MOTION_STOPMODE.EMERGENCY_STOP, (int)AXT_MOTION_LEVEL_MODE.HIGH, (int)AXT_MOTION_LEVEL_MODE.HIGH);
                CAXM.AxmSignalSetInpos(i, 1);
                CAXM.AxmSignalSetServoAlarm(i, (int)AXT_MOTION_LEVEL_MODE.HIGH);
                CAXM.AxmSignalSetStop(i, (int)AXT_MOTION_STOPMODE.EMERGENCY_STOP, (int)AXT_MOTION_LEVEL_MODE.UNUSED);
                CAXM.AxmMotSetMoveUnitPerPulse(i, 1.0, 100);
                //CAXM.AxmSignalSetSoftLimit(i, (int)AXT_USE.DISABLE, (int)AXT_MOTION_STOPMODE.EMERGENCY_STOP, (int)AXT_MOTION_SELECTION.COMMAND, 100.0, 0.0);
                CAXM.AxmMotSetMinVel(i, 0.01);
                CAXM.AxmMotSetMaxVel(i, _MotorAxisInfo[i].dbMaxSpeed);
                CAXM.AxmMotSetAccelUnit(i, (int)AXT_MOTION_ACC_UNIT.SEC);
                CAXM.AxmMotSetAbsRelMode(i, (int)AXT_MOTION_ABSREL.POS_REL_MODE);
                CAXM.AxmMotSetProfileMode(i, (int)AXT_MOTION_PROFILE_MODE.SYM_S_CURVE_MODE);
                CAXM.AxmStatusSetCmdPos(i, 0.0);
                CAXM.AxmStatusSetActPos(i, 0.0);

            }


            CAXM.AxmMotSetPulseOutMethod((int)AXIS.X, (int)AXT_MOTION_PULSE_OUTPUT.TwoCcwCwHigh);
            CAXM.AxmMotSetEncInputMethod((int)AXIS.X, (int)AXT_MOTION_EXTERNAL_COUNTER_INPUT.ReverseSqr4Mode);

            CAXM.AxmMotSetPulseOutMethod((int)AXIS.Y, (int)AXT_MOTION_PULSE_OUTPUT.TwoCcwCwHigh);
            CAXM.AxmMotSetEncInputMethod((int)AXIS.Y, (int)AXT_MOTION_EXTERNAL_COUNTER_INPUT.ReverseSqr4Mode);

            CAXM.AxmMotSetPulseOutMethod((int)AXIS.Z, (int)AXT_MOTION_PULSE_OUTPUT.TwoCwCcwHigh);
            CAXM.AxmMotSetEncInputMethod((int)AXIS.Z, (int)AXT_MOTION_EXTERNAL_COUNTER_INPUT.ObverseSqr4Mode);

            CAXM.AxmMotSetPulseOutMethod((int)AXIS.R, (int)AXT_MOTION_PULSE_OUTPUT.TwoCcwCwHigh);
            CAXM.AxmMotSetEncInputMethod((int)AXIS.R, (int)AXT_MOTION_EXTERNAL_COUNTER_INPUT.ReverseSqr4Mode);

            //CAXM.AxmMotSetPulseOutMethod((int)AXIS.BOLT_R1, (int)AXT_MOTION_PULSE_OUTPUT.TwoCwCcwHigh);
            //CAXM.AxmMotSetEncInputMethod((int)AXIS.BOLT_R1, (int)AXT_MOTION_EXTERNAL_COUNTER_INPUT.ObverseSqr4Mode);

            //CAXM.AxmMotSetPulseOutMethod((int)AXIS.BOLT_R2, (int)AXT_MOTION_PULSE_OUTPUT.TwoCwCcwHigh);
            //CAXM.AxmMotSetEncInputMethod((int)AXIS.BOLT_R2, (int)AXT_MOTION_EXTERNAL_COUNTER_INPUT.ObverseSqr4Mode);

            //CAXM.AxmMotSetPulseOutMethod((int)AXIS.BOLT_R3, (int)AXT_MOTION_PULSE_OUTPUT.TwoCwCcwHigh);
            //CAXM.AxmMotSetEncInputMethod((int)AXIS.BOLT_R3, (int)AXT_MOTION_EXTERNAL_COUNTER_INPUT.ObverseSqr4Mode);

            //CAXM.AxmMotSetPulseOutMethod((int)AXIS.BOLT_R4, (int)AXT_MOTION_PULSE_OUTPUT.TwoCwCcwHigh);
            //CAXM.AxmMotSetEncInputMethod((int)AXIS.BOLT_R4, (int)AXT_MOTION_EXTERNAL_COUNTER_INPUT.ObverseSqr4Mode);

            CAXM.AxmMotSetPulseOutMethod((int)AXIS.HIPOT_1X, (int)AXT_MOTION_PULSE_OUTPUT.TwoCcwCwHigh);
            CAXM.AxmMotSetEncInputMethod((int)AXIS.HIPOT_1X, (int)AXT_MOTION_EXTERNAL_COUNTER_INPUT.ReverseSqr4Mode);

            CAXM.AxmMotSetPulseOutMethod((int)AXIS.HIPOT_1Y, (int)AXT_MOTION_PULSE_OUTPUT.TwoCwCcwHigh);
            CAXM.AxmMotSetEncInputMethod((int)AXIS.HIPOT_1Y, (int)AXT_MOTION_EXTERNAL_COUNTER_INPUT.ObverseSqr4Mode);

            CAXM.AxmMotSetPulseOutMethod((int)AXIS.HIPOT_1Z, (int)AXT_MOTION_PULSE_OUTPUT.TwoCcwCwHigh);
            CAXM.AxmMotSetEncInputMethod((int)AXIS.HIPOT_1Z, (int)AXT_MOTION_EXTERNAL_COUNTER_INPUT.ReverseSqr4Mode);

            CAXM.AxmMotSetPulseOutMethod((int)AXIS.HIPOT_2X, (int)AXT_MOTION_PULSE_OUTPUT.TwoCcwCwHigh);
            CAXM.AxmMotSetEncInputMethod((int)AXIS.HIPOT_2X, (int)AXT_MOTION_EXTERNAL_COUNTER_INPUT.ReverseSqr4Mode);

            CAXM.AxmMotSetPulseOutMethod((int)AXIS.HIPOT_2Y, (int)AXT_MOTION_PULSE_OUTPUT.TwoCwCcwHigh);
            CAXM.AxmMotSetEncInputMethod((int)AXIS.HIPOT_2Y, (int)AXT_MOTION_EXTERNAL_COUNTER_INPUT.ObverseSqr4Mode);

            CAXM.AxmMotSetPulseOutMethod((int)AXIS.HIPOT_2Z, (int)AXT_MOTION_PULSE_OUTPUT.TwoCcwCwHigh);
            CAXM.AxmMotSetEncInputMethod((int)AXIS.HIPOT_2Z, (int)AXT_MOTION_EXTERNAL_COUNTER_INPUT.ReverseSqr4Mode);

            CAXM.AxmMotSetPulseOutMethod((int)AXIS.EOL_X, (int)AXT_MOTION_PULSE_OUTPUT.TwoCcwCwHigh);
            CAXM.AxmMotSetEncInputMethod((int)AXIS.EOL_X, (int)AXT_MOTION_EXTERNAL_COUNTER_INPUT.ReverseSqr4Mode);

            CAXM.AxmMotSetPulseOutMethod((int)AXIS.EOL_Y, (int)AXT_MOTION_PULSE_OUTPUT.TwoCwCcwHigh);
            CAXM.AxmMotSetEncInputMethod((int)AXIS.EOL_Y, (int)AXT_MOTION_EXTERNAL_COUNTER_INPUT.ObverseSqr4Mode);

            CAXM.AxmMotSetPulseOutMethod((int)AXIS.EOL_Z, (int)AXT_MOTION_PULSE_OUTPUT.TwoCcwCwHigh);
            CAXM.AxmMotSetEncInputMethod((int)AXIS.EOL_Z, (int)AXT_MOTION_EXTERNAL_COUNTER_INPUT.ReverseSqr4Mode);
        }


        public static void SaveStationTactTime(STATION_LIST _ST, DateTime _startTime, DateTime _endTime, int nCase)
        {
            ////===============우리쪽 임시데이터 저장 =========
            //// 바코드 파일
            //string strSaveFolderPath = String.Format(@"E:\\DATA\\TACTTIME\\{0}\\", _ST.ToString());
            //DirectoryInfo Savedir = new DirectoryInfo(strSaveFolderPath);
            //if (Savedir.Exists == false) { Savedir.Create(); }

            //string strSaveFilePath = String.Format(@"{0}{1}.txt", strSaveFolderPath, DateTime.Now.ToString("yyMMdd"));
            //File.AppendAllText(strSaveFilePath, DateTime.Now.ToString("[HH:mm:ss] ") + _ts.ToString("mm':'ss':'ff") + "\r\n");

            string strComment = "";

            if (nCase == 0)
            {

            }

            //===============우리쪽 임시데이터 저장 =========

            string strSaveFolderPath = String.Format(@"E:\\DATA\\TACTTIME\\{0}\\", DateTime.Now.ToString("yyMMdd"));
            DirectoryInfo Savedir = new DirectoryInfo(strSaveFolderPath);
            if (Savedir.Exists == false) { Savedir.Create(); }

            string strSaveFilePath = String.Format(@"{0}{1}.txt", strSaveFolderPath, _ST.ToString());

            TimeSpan _CalcTime;

            if (File.Exists(strSaveFilePath))
            {
                // 파일이 있는경우 내용만 추가


                strComment = "";
                strComment += _startTime.ToString("HH:mm:ss") + ",";        // 시작 시간
                strComment += _endTime.ToString("HH:mm:ss") + ",";          // 종료 시간

                _CalcTime = _endTime - _startTime;
                strComment += String.Format("{0:D2}:{1:D2}:{2:D2}", _CalcTime.Hours, _CalcTime.Minutes, _CalcTime.Seconds) + ",";   // 택타임

                if (nCase == 1)
                {
                    strComment += "MANUAL MODE,";
                }
                else if (nCase == 0)
                {
                    strComment += ",";
                }

                strComment += _ModelInfo.strModelName + ",";
                strComment += "\r\n";
                File.AppendAllText(strSaveFilePath, strComment);

            }
            else
            {
                // 파일이 없는경우 헤더도 추가
                File.AppendAllText(strSaveFilePath, "STATION WORK INFORMATION REPORT\r\n\r\n\r\n");
                File.AppendAllText(strSaveFilePath, "[WORK INFOMATIONS]\r\n");
                File.AppendAllText(strSaveFilePath, String.Format("LOT START TIME,{0}\r\n\r\n", _LotCount.tLotClearTime.ToString("yyyy-MM-dd HH:mm:ss")));
                File.AppendAllText(strSaveFilePath, "START TIME,END TIME,ELAPSE TIME,STATUS,WORK MODEL,REMARK\r\n");


                strComment = "";
                strComment += _startTime.ToString("HH:mm:ss") + ",";        // 시작 시간
                strComment += _endTime.ToString("HH:mm:ss") + ",";          // 종료 시간
                _CalcTime = _endTime - _startTime;
                strComment += String.Format("{0:D2}:{1:D2}:{2:D2}", _CalcTime.Hours, _CalcTime.Minutes, _CalcTime.Seconds) + ",";   // 택타임

                if (nCase == 1)
                {
                    strComment += "MANUAL MODE,";
                }
                else if (nCase == 0)
                {
                    strComment += ",";
                }

                strComment += _ModelInfo.strModelName + ",";
                strComment += "\r\n";
                File.AppendAllText(strSaveFilePath, strComment);

            }


        }

        public static void SaveSTLockInfo(int nIndex)
        {
            string strFolderPath = String.Format(@"TEMP\\ST{0}\\", nIndex + 1);
            DirectoryInfo dir = new DirectoryInfo(strFolderPath);
            if (dir.Exists == false) { dir.Create(); }

            string strPath = String.Format("{0}Lockinfo.ini", strFolderPath);

            _IniFile.IniWriteValue("TipInfo", "Tip1", _SysInfo.nTipNowCount[nIndex, 0].ToString(), strPath);
            _IniFile.IniWriteValue("TipInfo", "Tip2", _SysInfo.nTipNowCount[nIndex, 1].ToString(), strPath);
            _IniFile.IniWriteValue("TipInfo", "Tip3", _SysInfo.nTipNowCount[nIndex, 2].ToString(), strPath);
            _IniFile.IniWriteValue("TipInfo", "Tip4", _SysInfo.nTipNowCount[nIndex, 3].ToString(), strPath);
            _IniFile.IniWriteValue("TipInfo", "Tip5", _SysInfo.nTipNowCount[nIndex, 4].ToString(), strPath);

        }


        public static void LoadSTLockInfo(int nIndex)
        {
            string strFolderPath = String.Format(@"TEMP\\ST{0}\\", nIndex + 1);
            DirectoryInfo dir = new DirectoryInfo(strFolderPath);
            if (dir.Exists == false) { dir.Create(); }

            string strPath = String.Format("{0}Lockinfo.ini", strFolderPath);

            int.TryParse(_IniFile.IniReadValue("TipInfo", "Tip1", "0", strPath), out _SysInfo.nTipNowCount[nIndex, 0]);
            int.TryParse(_IniFile.IniReadValue("TipInfo", "Tip2", "0", strPath), out _SysInfo.nTipNowCount[nIndex, 1]);
            int.TryParse(_IniFile.IniReadValue("TipInfo", "Tip3", "0", strPath), out _SysInfo.nTipNowCount[nIndex, 2]);
            int.TryParse(_IniFile.IniReadValue("TipInfo", "Tip4", "0", strPath), out _SysInfo.nTipNowCount[nIndex, 3]);
            int.TryParse(_IniFile.IniReadValue("TipInfo", "Tip5", "0", strPath), out _SysInfo.nTipNowCount[nIndex, 4]);
        }



        public static void SaveProductCount()
        {
            IFormatter formatter = new BinaryFormatter();
            Stream streamWrite = new FileStream("Count.cnt", FileMode.Create, FileAccess.Write, FileShare.None);
            formatter.Serialize(streamWrite, _Count);
            streamWrite.Close();
        }

        // 카운터 로드
        public static void LoadProductCount()
        {
            IFormatter formatter = new BinaryFormatter();
            Stream streamRead = new FileStream("Count.cnt", FileMode.OpenOrCreate, FileAccess.Read, FileShare.None);
            try { _Count = (ProductCount)formatter.Deserialize(streamRead); }
            catch { }
            ; streamRead.Close();
        }


        public static void SaveBCDListInfo()
        {
            string strFolderPath = String.Format(@"TEMP\\BCDINFO\\");
            DirectoryInfo dir = new DirectoryInfo(strFolderPath);
            if (dir.Exists == false) { dir.Create(); }

            string strPath = String.Format("{0}BarcodeInfo.ini", strFolderPath);

            _IniFile.IniWriteValue("BCDINFO", "COUNT", _ReadBCDList.Count.ToString(), strPath);

            for (int i = 0; i < _ReadBCDList.Count; i++)
            {
                _IniFile.IniWriteValue("BCDINFO", String.Format("BCD{0}", i), _ReadBCDList[i].strBCD, strPath);
                _IniFile.IniWriteValue("BCDINFO", String.Format("CATE{0}", i), _ReadBCDList[i].strCate, strPath);
            }


        }

        public static void LoadBCDListInfo()
        {
            string strFolderPath = String.Format(@"TEMP\\BCDINFO\\");
            DirectoryInfo dir = new DirectoryInfo(strFolderPath);
            if (dir.Exists == false) { dir.Create(); }

            string strPath = String.Format("{0}BarcodeInfo.ini", strFolderPath);
            int nReadCount = 0;

            int.TryParse(_IniFile.IniReadValue("BCDINFO", "COUNT", "0", strPath), out nReadCount);

            for (int i = 0; i < nReadCount; i++)
            {


                _ReadBCDList.Add(new _ReadBarcodeData()
                {
                    strBCD = _IniFile.IniReadValue("BCDINFO", String.Format("BCD{0}", i), "", strPath),
                    strCate = _IniFile.IniReadValue("BCDINFO", String.Format("CATE{0}", i), "", strPath)
                });


            }
        }



        public static void SavePalletBCDListInfo(string strPalletBarcode)
        {
            string strFolderPath = String.Format(@"PALLET_INFO\\");
            DirectoryInfo dir = new DirectoryInfo(strFolderPath);
            if (dir.Exists == false) { dir.Create(); }

            string strPath = String.Format("{0}{1}.ini", strFolderPath, strPalletBarcode);

            _IniFile.IniWriteValue("BCDINFO", "COUNT", _ST1BCDList.Count.ToString(), strPath);

            for (int i = 0; i < _ST1BCDList.Count; i++)
            {
                _IniFile.IniWriteValue("BCDINFO", String.Format("BCD{0}", i), _ST1BCDList[i].strBCD, strPath);
                _IniFile.IniWriteValue("BCDINFO", String.Format("CATE{0}", i), _ST1BCDList[i].strCate, strPath);
            }


        }

        public static void LoadPalletBCDListInfo(string strPalletBarcode)
        {
            string strFolderPath = String.Format(@"PALLET_INFO\\");
            DirectoryInfo dir = new DirectoryInfo(strFolderPath);
            if (dir.Exists == false) { dir.Create(); }

            string strPath = String.Format("{0}{1}.ini", strFolderPath, strPalletBarcode);
            int nReadCount = 0;

            int.TryParse(_IniFile.IniReadValue("BCDINFO", "COUNT", "0", strPath), out nReadCount);

            for (int i = 0; i < nReadCount; i++)
            {

                if (CheckCMABcdDuplicate(_IniFile.IniReadValue("BCDINFO", String.Format("BCD{0}", i), "", strPath)))
                {
                    AppendLogMsg(String.Format("CMA 重复条形码。 {0}", _IniFile.IniReadValue("BCDINFO", String.Format("BCD{0}", i), "", strPath)), LOG_TYPE.ERROR);
                }
                else
                {
                    _ReadBCDList.Add(new _ReadBarcodeData()
                    {
                        strBCD = _IniFile.IniReadValue("BCDINFO", String.Format("BCD{0}", i), "", strPath),
                        strCate = _IniFile.IniReadValue("BCDINFO", String.Format("CATE{0}", i), "", strPath)
                    });
                }


                //// Barcode Check 기능 추가


            }
        }

        public static void DelPalletBCDListInfo(string strPalletBarcode)
        {
            string strFolderPath = String.Format(@"PALLET_INFO\\");
            DirectoryInfo dir = new DirectoryInfo(strFolderPath);
            if (dir.Exists == false) { dir.Create(); }

            string strPath = String.Format("{0}{1}.ini", strFolderPath, strPalletBarcode);

            try
            {
                File.Delete(strPath);
            }
            catch { }

        }


        public static double GetNowPos(AXIS _axis)
        {
            double dbPos = 0.0;

            CAXM.AxmStatusGetCmdPos((int)_axis, ref dbPos);

            return dbPos;
        }

        // 모델별 카운트 저장
        public static void SaveModelProductCount(string strModelName)
        {

            try
            {
                DirectoryInfo dir = new DirectoryInfo(@"Count\\");
                if (dir.Exists == false) { dir.Create(); }

                IFormatter formatter = new BinaryFormatter();
                Stream streamWrite = new FileStream(String.Format("Count\\{0}.cnt", strModelName), FileMode.Create, FileAccess.Write, FileShare.None);
                formatter.Serialize(streamWrite, _LotCount);
                streamWrite.Close();

            }
            catch { };

        }

        // 카운터 로드
        public static void LoadModelProductCount(string strModelName)
        {
            DirectoryInfo dir = new DirectoryInfo(@"Count\\");
            if (dir.Exists == false) { dir.Create(); }

            IFormatter formatter = new BinaryFormatter();
            Stream streamRead = new FileStream(String.Format("Count\\{0}.cnt", strModelName), FileMode.OpenOrCreate, FileAccess.Read, FileShare.None);
            try { _LotCount = (LotCount)formatter.Deserialize(streamRead); }
            catch
            {

                _LotCount.nLotCount = 0;
                _LotCount.nProductCount = 0;
                _LotCount.tLotClearTime = DateTime.Now;
                _LotCount.tProductClearTime = DateTime.Now;
                //SaveModelProductCount(_ModelInfo.strModelName);
            }
            ; streamRead.Close();

            SaveModelProductCount(_ModelInfo.strModelName);
        }

        //====== 모델 정보 저장
        public static void SaveModelInfo(MODEL_INFO _ModelInfo, String _ModelName)
        {
            //try
            //{
            //    string strFolderPath = String.Format(@"MODEL\\");
            //    DirectoryInfo dir = new DirectoryInfo(strFolderPath);
            //    if (dir.Exists == false) { dir.Create(); }

            //    _ModelInfo.strModelName = _ModelName;
            //    IFormatter formatter = new BinaryFormatter();
            //    Stream streamWrite = new FileStream(String.Format("MODEL\\{0}.rcp", _ModelName), FileMode.Create, FileAccess.Write, FileShare.None);
            //    formatter.Serialize(streamWrite, _ModelInfo);
            //    streamWrite.Close();
            //}
            //catch { }

            try
            {
                string strFolderPath = String.Format(@"MODEL\\");
                DirectoryInfo dir = new DirectoryInfo(strFolderPath);
                if (dir.Exists == false) { dir.Create(); }

                File.WriteAllText(String.Format("MODEL\\{0}.rcp", _ModelName), JsonConvert.SerializeObject(_ModelInfo));
            }
            catch (Exception _e) { MessageBox.Show(_e.Message); }
        }

        //====== 모델 정보 불러오기
        public static void LoadModelInfo(ref MODEL_INFO _ModelInfo, String _ModelName)
        {
            //string strFolderPath = String.Format(@"MODEL\\");
            //DirectoryInfo dir = new DirectoryInfo(strFolderPath);
            //if (dir.Exists == false) { dir.Create(); }

            //IFormatter formatter = new BinaryFormatter();
            //MODEL_INFO m_testModelInfo = new MODEL_INFO();


            //Stream streamRead = new FileStream(String.Format(@"MODEL\\{0}.rcp", _ModelName), FileMode.OpenOrCreate, FileAccess.Read, FileShare.None);
            //try
            //{
            //    m_testModelInfo = (MODEL_INFO)formatter.Deserialize(streamRead);
            //    _ModelInfo = m_testModelInfo;

            //}

            //catch { _ModelInfo.strModelName = "_Noname_"; }

            //_ModelInfo.strModelName = _ModelName;

            //streamRead.Close();
            string strFolderPath = String.Format(@"MODEL\\");
            DirectoryInfo dir = new DirectoryInfo(strFolderPath);
            if (dir.Exists == false) { dir.Create(); }

            try
            {
                _ModelInfo = JsonConvert.DeserializeObject<MODEL_INFO>(File.ReadAllText(String.Format(@"MODEL\\{0}.rcp", _ModelName)));
                if (_ModelInfo._EtcDataScan == null)
                {
                    _ModelInfo._EtcDataScan = new ETC_SCAN_SET[5];
                    for (int i = 0; i < _ModelInfo._EtcDataScan.Length; i++)
                    {
                        _ModelInfo._EtcDataScan[i] = new ETC_SCAN_SET();
                    }
                }

            }

           // catch (Exception _e) { _ModelInfo.strModelName = "_Noname_"; MessageBox.Show(_e.Message); }
           catch
            {
                IFormatter formatter = new BinaryFormatter();
                MODEL_INFO m_testModelInfo = new MODEL_INFO();


                Stream streamRead = new FileStream(String.Format(@"MODEL\\{0}.rcp", _ModelName), FileMode.OpenOrCreate, FileAccess.Read, FileShare.None);
                try
                {
                    m_testModelInfo = (MODEL_INFO)formatter.Deserialize(streamRead);
                    _ModelInfo = m_testModelInfo;

                    if (_ModelInfo._EtcDataScan == null)
                    {
                        _ModelInfo._EtcDataScan = new ETC_SCAN_SET[5];
                        for (int i = 0; i < _ModelInfo._EtcDataScan.Length; i++)
                        {
                            _ModelInfo._EtcDataScan[i] = new ETC_SCAN_SET();
                        }
                    }
                }

                catch { _ModelInfo.strModelName = "_Noname_"; }

                _ModelInfo.strModelName = _ModelName;
                streamRead.Close();
            }

            SaveWorkPageInI(_ModelInfo.strModelName);
        }


        //====== INI 불러오기
        public static void SaveWorkPageInI(string strModelName)
        {
            string strPath = @"D:\\_work_guide_data_\\Config.ini";


            _IniFile.IniWriteValue("CONFIG", "szMasterCurrentModel", strModelName, strPath);
        }

        //====== INI 저장
        public static void SaveIniFile()
        {
            string strPath = "./Config.ini";

            File.WriteAllText(String.Format("TipName.ini"), JsonConvert.SerializeObject(_Config._TipName));

            // 통신포트 데이터
            _IniFile.IniWriteValue("COMM", "nMiraeDio1", _Config.nMiraeDio1.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nMiraeDio2", _Config.nMiraeDio2.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nBatteryComm1", _Config.nBatteryComm1.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nBatteryComm2", _Config.nBatteryComm2.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nNutRunner1", _Config.nNutRunner1.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nNutRunner2", _Config.nNutRunner2.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nNutRunner3", _Config.nNutRunner3.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nNutRunner4", _Config.nNutRunner4.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nNutRunner5", _Config.nNutRunner5.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nNutRunner6", _Config.nNutRunner6.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nBcdReader", _Config.nBcdReader.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nBcdPrinter", _Config.nBcdPrinter.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nETCReader", _Config.nETCReader.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nBatteryChargeTest", _Config.nBatteryChargeTest.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nEolReader", _Config.nEolReader.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nHipotReader", _Config.nHipotReader.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nTPCRobot", _Config.nTPCRobot.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nTPCRobotBaudRate", _Config.nTPCRobotBaudRate.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nDistancePort", _Config.nDistancePort.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nDistanceBaudRate", _Config.nDistanceBaudRate.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nArmPort", _Config.nArmPort.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nStation1Reader", _Config.nStation1Reader.ToString(), strPath);

            _IniFile.IniWriteValue("COMM", "nOmronWHTesterPort", _Config.nOmronWHTesterPort.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "strOmronWHTesterIP", _Config.strOmronWHTesterIP.ToString(), strPath);

            _IniFile.IniWriteValue("COMM", "nHipotHnadReader", _Config.nHipotHnadReader.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nEOLHandReader", _Config.nEOLHandReader.ToString(), strPath);


            _IniFile.IniWriteValue("COMM", "nLaserMarkingPort", _Config.nLaserMarkingPort.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nLaserMarkingBaudRate", _Config.nLaserMarkingBaudRate.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nLaserBCDReaderPort", _Config.nLaserBCDReaderPort.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nLaserBCDReaderBaudRate", _Config.nLaserBCDReaderBaudRate.ToString(), strPath);


            _IniFile.IniWriteValue("COMM", "nArmXYZPort", _Config.nArmXYZPort.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "nArmXYZBaudRate", _Config.nArmXYZBaudRate.ToString(), strPath);

          
            // 마지막 작업모델
            _Config.strCurrentModel = _ModelInfo.strModelName;
            _IniFile.IniWriteValue("CURRENT", "strCurrentModel", _Config.strCurrentModel, strPath);


            // 공통 설정
            _IniFile.IniWriteValue("COMMON", "bAirPressure", _Config.bAirPressure.ToString(), strPath);
            _IniFile.IniWriteValue("COMMON", "nCylTimeOut", _Config.nCylTimeOut.ToString(), strPath);
            _IniFile.IniWriteValue("COMMON", "strAdminPass", _Config.strAdminPass, strPath);

            _IniFile.IniWriteValue("COMMON", "strBarcodeAdminPass", _Config.strBarcodeAdminPass, strPath);

            _IniFile.IniWriteValue("COMMON", "bUseAdminPass", _Config.bUseAdminPass.ToString(), strPath);
            _IniFile.IniWriteValue("COMMON", "nReturnPalletOutTime", _Config.nReturnPalletOutTime.ToString(), strPath);
            _IniFile.IniWriteValue("COMMON", "strTitePass", _Config.strTitePass, strPath);
            _IniFile.IniWriteValue("COMMON", "bUseBoltSupply", _Config.bUseBoltSupply.ToString(), strPath);

            _IniFile.IniWriteValue("COMMON", "bPset232Select", _Config.bPset232Select.ToString(), strPath);
            _IniFile.IniWriteValue("COMMON", "bPsetTorqueMode", _Config.bPsetTorqueMode.ToString(), strPath);

            //_IniFile.IniWriteValue("COMMON", "bUseHipotFix", _ModelInfo.bUseHipotFix.ToString(), strPath);
            //_IniFile.IniWriteValue("COMMON", "bUseEolFix", _ModelInfo.bUseEolFix.ToString(), strPath);

            _IniFile.IniWriteValue("COMMON", "bUseCVAutoStop", _Config.bUseCVAutoStop.ToString(), strPath);
            _IniFile.IniWriteValue("COMMON", "nCVAutoStopTime", _Config.nCVAutoStopTime.ToString(), strPath);
            _IniFile.IniWriteValue("COMMON", "nBCDScanTimeOut", _Config.nBCDScanTimeOut.ToString(), strPath);

            _IniFile.IniWriteValue("COMMON", "strCountUpPassword", _Config.strCountUpPassword, strPath);

            // 모션데이터
            for (int i = (int)AXIS.X; i <= (int)AXIS.CAMERA2_Z; i++)
            {
                _IniFile.IniWriteValue(String.Format("AXIS.{0}", (AXIS)i), "dbAccelTime", _MotorAxisInfo[i].dbAccelTime.ToString(), strPath);
                _IniFile.IniWriteValue(String.Format("AXIS.{0}", (AXIS)i), "dbMaxSpeed", _MotorAxisInfo[i].dbMaxSpeed.ToString(), strPath);
                _IniFile.IniWriteValue(String.Format("AXIS.{0}", (AXIS)i), "dbNegativeLimit", _MotorAxisInfo[i].dbNegativeLimit.ToString(), strPath);
                _IniFile.IniWriteValue(String.Format("AXIS.{0}", (AXIS)i), "dbPositiveLimit", _MotorAxisInfo[i].dbPositiveLimit.ToString(), strPath);
            }

            _IniFile.IniWriteValue("MOTION", "bUseSoftwareLimit", _Config.bUseSoftwareLimit.ToString(), strPath);
            _IniFile.IniWriteValue("MOTION", "dbMotorHomeSpeed", _Config.dbMotorHomeSpeed.ToString(), strPath);

            _IniFile.IniWriteValue("MOTION", "dbOmronCameraXYMoveSpeed", _Config.dbOmronCameraXYMoveSpeed.ToString(), strPath);
            _IniFile.IniWriteValue("MOTION", "dbOmronCameraZMoveSpeed", _Config.dbOmronCameraZMoveSpeed.ToString(), strPath);
            _IniFile.IniWriteValue("MOTION", "nOmronCameraStabliTime", _Config.nOmronCameraStabliTime.ToString(), strPath);


            _IniFile.IniWriteValue("MOTION", "dbBoltSupply1Rev", _Config.dbBoltSupply1Rev.ToString(), strPath);
            _IniFile.IniWriteValue("MOTION", "dbBoltSupply2Rev", _Config.dbBoltSupply2Rev.ToString(), strPath);
            _IniFile.IniWriteValue("MOTION", "dbBoltSupply3Rev", _Config.dbBoltSupply3Rev.ToString(), strPath);
            _IniFile.IniWriteValue("MOTION", "dbBoltSupply4Rev", _Config.dbBoltSupply4Rev.ToString(), strPath);


            _IniFile.IniWriteValue("MOTION", "dbLoadingUnSafePosX", _Config.dbLoadingUnSafePosX.ToString(), strPath);
            _IniFile.IniWriteValue("MOTION", "dbLoadingUnSafePosZ", _Config.dbLoadingUnSafePosZ.ToString(), strPath);

            _IniFile.IniWriteValue("ETC", "nChatteringTime", _Config.nChatteringTime.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "nSMEMAChatteringTime", _Config.nSMEMAChatteringTime.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "dbTestZoneMoveSpeed", _Config.dbTestZoneMoveSpeed.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "dbTestZoneContactSpeed", _Config.dbTestZoneContactSpeed.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "dbTestZoneContactZSlowMovePos", _Config.dbTestZoneContactZSlowMovePos.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "dbTestZoneContactZSlowMoveSpeed", _Config.dbTestZoneContactZSlowMoveSpeed.ToString(), strPath);

            _IniFile.IniWriteValue("ETC", "dbTestZoneContactMovePos", _Config.dbTestZoneContactMovePos.ToString(), strPath);

            _IniFile.IniWriteValue("ETC", "nContactStabilTime", _Config.nContactStabilTime.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "nLiftCylStabilTime", _Config.nLiftCylStabilTime.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "nLiftOutTime", _Config.nLiftOutTime.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "nLiftInTime", _Config.nLiftInTime.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "dbSafeLoadZPos", _Config.dbSafeLoadZPos.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "dbNoClampXYMoveSpeed", _Config.dbNoClampXYMoveSpeed.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "dbNoClampZMoveSpeed", _Config.dbNoClampZMoveSpeed.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "dbClampXYMoveSpeed", _Config.dbClampXYMoveSpeed.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "dbClampZMoveSpeed", _Config.dbClampZMoveSpeed.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "dbZSensingHeight", _Config.dbZSensingHeight.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "dbZSensingSpeed", _Config.dbZSensingSpeed.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "dbShiftMoveSpeed", _Config.dbShiftMoveSpeed.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "nClampStabilTime", _Config.nClampStabilTime.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "nLiftTimeOut", _Config.nLiftTimeOut.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "nLotClearTime", _Config.nLotClearTime.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "bUseContactAutoTestMode", _Config.bUseContactAutoTestMode.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "bUseSemea", _Config.bUseSemea.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "bUseMainCVMonitor", _Config.bUseMainCVMonitor.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "bUseStationReservation", _Config.bUseStationReservation.ToString(), strPath);
            //_IniFile.IniWriteValue("ETC", "bUseAutoContact[0]", _ModelInfo.bUseHipotAutoContact.ToString(), strPath);
            //_IniFile.IniWriteValue("ETC", "bUseAutoContact[1]", _ModelInfo.bUseHipotAutoContact.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "bUseStopper", _Config.bUseStopper.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "bUseST6NgByPass", _Config.bUseST6NgByPass.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "bUseCMAStatusCheck", _Config.bUseCMAStatusCheck.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "bUseNutrunnerMove", _Config.bUseNutrunnerMove.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "strBCDSymbol", _Config.strBCDSymbol, strPath);

            _IniFile.IniWriteValue("ETC", "strVisionDir1", _Config.strVisionDir1, strPath);
            _IniFile.IniWriteValue("ETC", "strVisionDir2", _Config.strVisionDir2, strPath);
            _IniFile.IniWriteValue("ETC", "strLangue", _Config.strLangue, strPath);

            _IniFile.IniWriteValue("ETC", "bLockingStationSkip[0]", _Config.bLockingStationSkip[0].ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "bLockingStationSkip[1]", _Config.bLockingStationSkip[1].ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "bLockingStationSkip[2]", _Config.bLockingStationSkip[2].ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "bLockingStationSkip[3]", _Config.bLockingStationSkip[3].ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "bLockingStationSkip[4]", _Config.bLockingStationSkip[4].ToString(), strPath);

            _IniFile.IniWriteValue("ETC", "bTestStationSkip[0]", _Config.bTestStationSkip[0].ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "bTestStationSkip[1]", _Config.bTestStationSkip[1].ToString(), strPath);


            _IniFile.IniWriteValue("ETC", "bUseSameTimeContact[0]", _Config.bUseSameTimeContact[0].ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "bUseSameTimeContact[1]", _Config.bUseSameTimeContact[1].ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "bUseAutoLoadingReadySw", _Config.bUseAutoLoadingReadySw.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "bUseScanSTTester", _Config.bUseScanSTTester.ToString(), strPath);

            _IniFile.IniWriteValue("ETC", "bUseLoadingDoor", _Config.bUseLoadingDoor.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "bUseHipotDoor", _Config.bUseHipotDoor.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "bUseEolDoor", _Config.bUseEolDoor.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "bUseOutLiftSafty", _Config.bUseOutLiftSafty.ToString(), strPath);

            _IniFile.IniWriteValue("ETC", "bMasterModelLoad", _Config.bMasterModelLoad.ToString(), strPath);

            _IniFile.IniWriteValue("ETC", "bUseNoProductPass", _Config.bUseNoProductPass.ToString(), strPath);

            _IniFile.IniWriteValue("ETC", "nStation5PinMaxCount", _Config.nStation5PinMaxCount.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "nStation6PinMaxCount", _Config.nStation6PinMaxCount.ToString(), strPath);

            _IniFile.IniWriteValue("BCD", "nBCDAllOffsetX", _Config.nBCDAllOffsetX.ToString(), strPath);
            _IniFile.IniWriteValue("BCD", "nBCDAllOffsetY", _Config.nBCDAllOffsetY.ToString(), strPath);
            _IniFile.IniWriteValue("BCD", "nBCDbcdOffsetX", _Config.nBCDbcdOffsetX.ToString(), strPath);
            _IniFile.IniWriteValue("BCD", "nBCDbcdOffsetY", _Config.nBCDbcdOffsetY.ToString(), strPath);
            _IniFile.IniWriteValue("BCD", "nBCDtextOffsetX", _Config.nBCDtextOffsetX.ToString(), strPath);
            _IniFile.IniWriteValue("BCD", "nBCDtextOffsetY", _Config.nBCDtextOffsetY.ToString(), strPath);
            _IniFile.IniWriteValue("BCD", "nBCDScanStation", _Config.nBCDScanStation.ToString(), strPath);
            _IniFile.IniWriteValue("BCD", "nETCScanStation", _Config.nETCScanStation.ToString(), strPath);

            _IniFile.IniWriteValue("BCD", "nStartLotNum", _Config.nStartLotNum.ToString(), strPath);

            _IniFile.IniWriteValue("ETC", "dbTurnSpeed", _Config.dbTurnSpeed.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "dbTurnRev", _Config.dbTurnRev.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "dbLoadingAng", _Config.dbLoadingAng.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "dbCMAMoveLoadOffset", _Config.dbCMAMoveLoadOffset.ToString(), strPath);


            _IniFile.IniWriteValue("ETC", "dbTurnOkXn", _Config.dbTurnOkXn.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "dbTurnOkXp", _Config.dbTurnOkXp.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "dbTurnOkYn", _Config.dbTurnOkYn.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "dbTurnOkYp", _Config.dbTurnOkYp.ToString(), strPath);

            _IniFile.IniWriteValue("DIR", "strMESDir", _Config.strMESDir, strPath);
            _IniFile.IniWriteValue("DIR", "strHIPOTMESDir", _Config.strHIPOTMESDir, strPath);
            _IniFile.IniWriteValue("DIR", "strCMACheckDir", _Config.strCMACheckDir, strPath);

            _IniFile.IniWriteValue("TR", "nTRTurnClampTime", _Config.nTRTurnClampTime.ToString(), strPath);
            _IniFile.IniWriteValue("TR", "nTRStabilTime", _Config.nTRStabilTime.ToString(), strPath);

            _IniFile.IniWriteValue("ETC", "bHipotSkip", _Config.bHipotSkip.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "bEolSkip", _Config.bEolSkip.ToString(), strPath);

            _IniFile.IniWriteValue("ETC", "bUseReLiftCableSensing", _Config.bUseReLiftCableSensing.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "bUseReworkLineMode", _Config.bUseReworkLineMode.ToString(), strPath);

            _IniFile.IniWriteValue("ETC", "bUseReWorkTypeBCDScan", _Config.bUseReWorkTypeBCDScan.ToString(), strPath);


            _IniFile.IniWriteValue("MESDB", "strMESDBID", _Config.strMESDBID.ToString(), strPath);
            _IniFile.IniWriteValue("MESDB", "strMESDBIP", _Config.strMESDBIP.ToString(), strPath);
            _IniFile.IniWriteValue("MESDB", "strMESDBPASS", _Config.strMESDBPASS.ToString(), strPath);
            _IniFile.IniWriteValue("MESDB", "strMESDBSID", _Config.strMESDBSID.ToString(), strPath);
            _IniFile.IniWriteValue("MESDB", "nMESDBPort", _Config.nMESDBPort.ToString(), strPath);
            _IniFile.IniWriteValue("MESDB", "bUseMESTestCheck", _Config.bUseMESTestCheck.ToString(), strPath);

            _IniFile.IniWriteValue("TPC", "nTPCRobotCommTimeOut", _Config.nTPCRobotCommTimeOut.ToString(), strPath);

            _IniFile.IniWriteValue("ETC", "bUseLockingStationDwStay", _Config.bUseLockingStationDwStay.ToString(), strPath);            // 파레트 하강대기 기능 사용함
            _IniFile.IniWriteValue("ETC", "bUseHipotStationDwStay", _Config.bUseHipotStationDwStay.ToString(), strPath);            // 파레트 하강대기 기능 사용함


            _IniFile.IniWriteValue("ETC", "dbFirstPCSheetAngle", _Config.dbFirstPCSheetAngle.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "dbLastPCSheetAngle", _Config.dbLastPCSheetAngle.ToString(), strPath);
            //nTPCRobotCommTimeOut

            // Pallet 관련 데이터
            for (int i = 0; i < 20; i++)
            {
                _IniFile.IniWriteValue("PALLET", String.Format("strPalletBCD[{0}]", i), _Config.strPalletBCD[i], strPath);
            }

            _IniFile.IniWriteValue("ETC", "bUseNutrunnerCommCompare", _Config.bUseNutrunnerCommCompare.ToString(), strPath);
            _IniFile.IniWriteValue("ETC", "bReWorkMode", _Config.bReWorkMode.ToString(), strPath);



            // 너트러너 이더넷 모드 관련
            _IniFile.IniWriteValue("NUTRUNNERETH", "bUseNutrunnerEthMode", _Config.bUseNutrunnerEthMode.ToString(), strPath);
            for (int i = 0; i < 6; i++)
            {
                _IniFile.IniWriteValue("NUTRUNNERETH", String.Format("bUseNutrunner[{0}]", i), _Config.bUseNutrunner[i].ToString(), strPath);
                _IniFile.IniWriteValue("NUTRUNNERETH", String.Format("strNutrunnerIP[{0}]", i), _Config.strNutrunnerIP[i].ToString(), strPath);
                _IniFile.IniWriteValue("NUTRUNNERETH", String.Format("nNutrunnerPort[{0}]", i), _Config.nNutrunnerPort[i].ToString(), strPath);
            }

            _IniFile.IniWriteValue("ETC", "nAliveCheckTime", _Config.nAliveCheckTime.ToString(), strPath);


            _IniFile.IniWriteValue("CAMERA", "strOmronWHTesterCapCMD", _Config.strOmronWHTesterCapCMD.ToString(), strPath);
            _IniFile.IniWriteValue("CAMERA", "strOmronWHTesterCapOpt", _Config.strOmronWHTesterCapOpt.ToString(), strPath);
            _IniFile.IniWriteValue("CAMERA", "strOmronWHTesterCapSch", _Config.strOmronWHTesterCapSch.ToString(), strPath);
            _IniFile.IniWriteValue("CAMERA", "nCapDealy", _Config.nCapDealy.ToString(), strPath);
            _IniFile.IniWriteValue("CAMERA", "nFileGetDealy", _Config.nFileGetDealy.ToString(), strPath);

            _IniFile.IniWriteValue("DIR", "strOmronOriginImgDir", _Config.strOmronOriginImgDir, strPath);
            _IniFile.IniWriteValue("DIR", "strOmronScreenImgDir", _Config.strOmronScreenImgDir, strPath);

            _IniFile.IniWriteValue("LASER", "strLaserMarkingSendMsg", _Config.strLaserMarkingSendMsg, strPath);

            _IniFile.IniWriteValue("HIPOT", "nManualChannelP", _Config.nManualChannelP.ToString(), strPath);
            _IniFile.IniWriteValue("HIPOT", "nManualChannelN", _Config.nManualChannelN.ToString(), strPath);
            _IniFile.IniWriteValue("HIPOT", "nAutoChannelP", _Config.nAutoChannelP.ToString(), strPath);
            _IniFile.IniWriteValue("HIPOT", "nAutoChannelN", _Config.nAutoChannelN.ToString(), strPath);

            _IniFile.IniWriteValue("ETC", "nOscRetryCount", _Config.nOscRetryCount.ToString(), strPath);
        }


        public static void LoadNgList()
        {
            string strSaveFolderPath = String.Format(@"NGDATA\\");
            DirectoryInfo Savedir = new DirectoryInfo(strSaveFolderPath);
            if (Savedir.Exists == false) { Savedir.Create(); }

            string[] _files = Directory.GetFiles(strSaveFolderPath, "*.csv");

            for (int i = 0; i < _files.Length; i++)
            {
                _NgDataList.AddRange(File.ReadLines(_files[i]));
            }

            // MessageBox.Show(_NgDataList.Exists(x => x == "SM007189P3B1CND1710230331").ToString());

        }

        //====== INI 불러오기
        static void LoadIniFile()
        {
            string strPath = "./Config.ini";

            try
            {
                _Config._TipName = JsonConvert.DeserializeObject<List<string>>(File.ReadAllText(String.Format(@"TipName.ini")));
            }
            catch { }
            // 통신포트 데이터
            int.TryParse(_IniFile.IniReadValue("COMM", "nMiraeDio1", "3", strPath), out _Config.nMiraeDio1);
            int.TryParse(_IniFile.IniReadValue("COMM", "nMiraeDio2", "4", strPath), out _Config.nMiraeDio2);
            int.TryParse(_IniFile.IniReadValue("COMM", "nBatteryComm1", "-1", strPath), out _Config.nBatteryComm1);
            int.TryParse(_IniFile.IniReadValue("COMM", "nBatteryComm2", "-1", strPath), out _Config.nBatteryComm2);
            int.TryParse(_IniFile.IniReadValue("COMM", "nNutRunner1", "6", strPath), out _Config.nNutRunner1);
            int.TryParse(_IniFile.IniReadValue("COMM", "nNutRunner2", "7", strPath), out _Config.nNutRunner2);
            int.TryParse(_IniFile.IniReadValue("COMM", "nNutRunner3", "8", strPath), out _Config.nNutRunner3);
            int.TryParse(_IniFile.IniReadValue("COMM", "nNutRunner4", "8", strPath), out _Config.nNutRunner4);
            int.TryParse(_IniFile.IniReadValue("COMM", "nNutRunner5", "9", strPath), out _Config.nNutRunner5);
            int.TryParse(_IniFile.IniReadValue("COMM", "nNutRunner6", "8", strPath), out _Config.nNutRunner6);
            int.TryParse(_IniFile.IniReadValue("COMM", "nBcdReader", "12", strPath), out _Config.nBcdReader);
            int.TryParse(_IniFile.IniReadValue("COMM", "nBcdPrinter", "13", strPath), out _Config.nBcdPrinter);
            int.TryParse(_IniFile.IniReadValue("COMM", "nETCReader", "13", strPath), out _Config.nETCReader);
            int.TryParse(_IniFile.IniReadValue("COMM", "nBatteryChargeTest", "18", strPath), out _Config.nBatteryChargeTest);
            int.TryParse(_IniFile.IniReadValue("COMM", "nEolReader", "11", strPath), out _Config.nEolReader);
            int.TryParse(_IniFile.IniReadValue("COMM", "nHipotReader", "10", strPath), out _Config.nHipotReader);
            int.TryParse(_IniFile.IniReadValue("COMM", "nTPCRobot", "16", strPath), out _Config.nTPCRobot);
            int.TryParse(_IniFile.IniReadValue("COMM", "nTPCRobotBaudRate", "9600", strPath), out _Config.nTPCRobotBaudRate);

            int.TryParse(_IniFile.IniReadValue("COMM", "nDistancePort", "20", strPath), out _Config.nDistancePort);
            int.TryParse(_IniFile.IniReadValue("COMM", "nDistanceBaudRate", "9600", strPath), out _Config.nDistanceBaudRate);
            int.TryParse(_IniFile.IniReadValue("COMM", "nArmPort", "17", strPath), out _Config.nArmPort);
            int.TryParse(_IniFile.IniReadValue("COMM", "nStation1Reader", "-1", strPath), out _Config.nStation1Reader);
            int.TryParse(_IniFile.IniReadValue("COMM", "nArmXYZPort", "-1", strPath), out _Config.nArmXYZPort);
            int.TryParse(_IniFile.IniReadValue("COMM", "nArmXYZBaudRate", "9600", strPath), out _Config.nArmXYZBaudRate);

            int.TryParse(_IniFile.IniReadValue("COMM", "nOmronWHTesterPort", "12010", strPath), out _Config.nOmronWHTesterPort);
            _Config.strOmronWHTesterIP = _IniFile.IniReadValue("COMM", "strOmronWHTesterIP", "192.168.0.1", strPath);

            int.TryParse(_IniFile.IniReadValue("COMM", "nHipotHnadReader", "-1", strPath), out _Config.nHipotHnadReader);
            int.TryParse(_IniFile.IniReadValue("COMM", "nEOLHandReader", "-1", strPath), out _Config.nEOLHandReader);


            int.TryParse(_IniFile.IniReadValue("COMM", "nLaserMarkingPort", "-1", strPath), out _Config.nLaserMarkingPort);
            int.TryParse(_IniFile.IniReadValue("COMM", "nLaserMarkingBaudRate", "19200", strPath), out _Config.nLaserMarkingBaudRate);

            int.TryParse(_IniFile.IniReadValue("COMM", "nLaserBCDReaderPort", "-1", strPath), out _Config.nLaserBCDReaderPort);
            int.TryParse(_IniFile.IniReadValue("COMM", "nLaserBCDReaderBaudRate", "115200", strPath), out _Config.nLaserBCDReaderBaudRate);

            //마지막 작업 모델
            _Config.strCurrentModel = _IniFile.IniReadValue("CURRENT", "strCurrentModel", "_NONAME_", strPath);

            // 공통 설정
            bool.TryParse(_IniFile.IniReadValue("COMMON", "bAirPressure", "false", strPath), out _Config.bAirPressure);
            int.TryParse(_IniFile.IniReadValue("COMMON", "nCylTimeOut", "3000", strPath), out _Config.nCylTimeOut);
            bool.TryParse(_IniFile.IniReadValue("COMMON", "bUseAdminPass", "true", strPath), out _Config.bUseAdminPass);
            _Config.strAdminPass = _IniFile.IniReadValue("COMMON", "strAdminPass", "1234", strPath);
            _Config.strBarcodeAdminPass = _IniFile.IniReadValue("COMMON", "strBarcodeAdminPass", "mre1234", strPath);
            _Config.strCountUpPassword = _IniFile.IniReadValue("COMMON", "strCountUpPassword", "default", strPath);
            int.TryParse(_IniFile.IniReadValue("COMMON", "nReturnPalletOutTime", "5000", strPath), out _Config.nReturnPalletOutTime);
            _Config.strTitePass = _IniFile.IniReadValue("COMMON", "strTitePass", "1234", strPath);
            bool.TryParse(_IniFile.IniReadValue("COMMON", "bUseBoltSupply", "false", strPath), out _Config.bUseBoltSupply);

            bool.TryParse(_IniFile.IniReadValue("COMMON", "bPset232Select", "false", strPath), out _Config.bPset232Select);
            bool.TryParse(_IniFile.IniReadValue("COMMON", "bPsetTorqueMode", "false", strPath), out _Config.bPsetTorqueMode);

            // bool.TryParse(_IniFile.IniReadValue("COMMON", "bUseHipotFix", "false", strPath), out _ModelInfo.bUseHipotFix);
            // bool.TryParse(_IniFile.IniReadValue("COMMON", "bUseEolFix", "false", strPath), out _ModelInfo.bUseEolFix);

            bool.TryParse(_IniFile.IniReadValue("COMMON", "bUseCVAutoStop", "false", strPath), out _Config.bUseCVAutoStop);
            int.TryParse(_IniFile.IniReadValue("COMMON", "nCVAutoStopTime", "30000", strPath), out _Config.nCVAutoStopTime);
            int.TryParse(_IniFile.IniReadValue("COMMON", "nBCDScanTimeOut", "1000", strPath), out _Config.nBCDScanTimeOut);
            // 모션 데이터
            for (int i = (int)AXIS.X; i <= (int)AXIS.CAMERA2_Z; i++)
            {
                _MotorAxisInfo[i].dbAccelTime = double.Parse(_IniFile.IniReadValue(String.Format("AXIS.{0}", (AXIS)i), "dbAccelTime", "0.1", strPath));
                _MotorAxisInfo[i].dbMaxSpeed = double.Parse(_IniFile.IniReadValue(String.Format("AXIS.{0}", (AXIS)i), "dbMaxSpeed", "50", strPath));
                _MotorAxisInfo[i].dbNegativeLimit = double.Parse(_IniFile.IniReadValue(String.Format("AXIS.{0}", (AXIS)i), "dbNegativeLimit", "-100", strPath));
                _MotorAxisInfo[i].dbPositiveLimit = double.Parse(_IniFile.IniReadValue(String.Format("AXIS.{0}", (AXIS)i), "dbPositiveLimit", "100", strPath));
            }

            bool.TryParse(_IniFile.IniReadValue("MOTION", "bUseSoftwareLimit", "false", strPath), out _Config.bUseSoftwareLimit);
            double.TryParse(_IniFile.IniReadValue("MOTION", "dbMotorHomeSpeed", "20.0", strPath), out _Config.dbMotorHomeSpeed);

            double.TryParse(_IniFile.IniReadValue("MOTION", "dbOmronCameraXYMoveSpeed", "20.0", strPath), out _Config.dbOmronCameraXYMoveSpeed);
            double.TryParse(_IniFile.IniReadValue("MOTION", "dbOmronCameraZMoveSpeed", "20.0", strPath), out _Config.dbOmronCameraZMoveSpeed);
            int.TryParse(_IniFile.IniReadValue("MOTION", "nOmronCameraStabliTime", "1000", strPath), out _Config.nOmronCameraStabliTime);


            double.TryParse(_IniFile.IniReadValue("MOTION", "dbBoltSupply1Rev", "0.0", strPath), out _Config.dbBoltSupply1Rev);
            double.TryParse(_IniFile.IniReadValue("MOTION", "dbBoltSupply2Rev", "0.0", strPath), out _Config.dbBoltSupply2Rev);
            double.TryParse(_IniFile.IniReadValue("MOTION", "dbBoltSupply3Rev", "0.0", strPath), out _Config.dbBoltSupply3Rev);
            double.TryParse(_IniFile.IniReadValue("MOTION", "dbBoltSupply4Rev", "0.0", strPath), out _Config.dbBoltSupply4Rev);

            double.TryParse(_IniFile.IniReadValue("MOTION", "dbLoadingUnSafePosX", "0.0", strPath), out _Config.dbLoadingUnSafePosX);
            double.TryParse(_IniFile.IniReadValue("MOTION", "dbLoadingUnSafePosZ", "0.0", strPath), out _Config.dbLoadingUnSafePosZ);

            int.TryParse(_IniFile.IniReadValue("ETC", "nChatteringTime", "500", strPath), out _Config.nChatteringTime);
            int.TryParse(_IniFile.IniReadValue("ETC", "nSMEMAChatteringTime", "500", strPath), out _Config.nSMEMAChatteringTime);
            int.TryParse(_IniFile.IniReadValue("ETC", "nContactStabilTime", "2000", strPath), out _Config.nContactStabilTime);
            int.TryParse(_IniFile.IniReadValue("ETC", "nLiftOutTime", "3000", strPath), out _Config.nLiftOutTime);
            int.TryParse(_IniFile.IniReadValue("ETC", "nLiftInTime", "1000", strPath), out _Config.nLiftInTime);
            int.TryParse(_IniFile.IniReadValue("ETC", "nClampStabilTime", "1000", strPath), out _Config.nClampStabilTime);
            int.TryParse(_IniFile.IniReadValue("ETC", "nLiftTimeOut", "10000", strPath), out _Config.nLiftTimeOut);
            int.TryParse(_IniFile.IniReadValue("ETC", "nLiftCylStabilTime", "3000", strPath), out _Config.nLiftCylStabilTime);

            int.TryParse(_IniFile.IniReadValue("ETC", "nStation5PinMaxCount", "100000", strPath), out _Config.nStation5PinMaxCount);
            int.TryParse(_IniFile.IniReadValue("ETC", "nStation6PinMaxCount", "100000", strPath), out _Config.nStation6PinMaxCount);
            int.TryParse(_IniFile.IniReadValue("ETC", "nLotClearTime", "0800", strPath), out _Config.nLotClearTime);

            double.TryParse(_IniFile.IniReadValue("ETC", "dbTestZoneMoveSpeed", "50.0", strPath), out _Config.dbTestZoneMoveSpeed);
            double.TryParse(_IniFile.IniReadValue("ETC", "dbTestZoneContactSpeed", "25.0", strPath), out _Config.dbTestZoneContactSpeed);
            double.TryParse(_IniFile.IniReadValue("ETC", "dbTestZoneContactMovePos", "25.0", strPath), out _Config.dbTestZoneContactMovePos);
            double.TryParse(_IniFile.IniReadValue("ETC", "dbTestZoneContactZSlowMovePos", "100.0", strPath), out _Config.dbTestZoneContactZSlowMovePos);
            double.TryParse(_IniFile.IniReadValue("ETC", "dbTestZoneContactZSlowMoveSpeed", "25.0", strPath), out _Config.dbTestZoneContactZSlowMoveSpeed);

            double.TryParse(_IniFile.IniReadValue("ETC", "dbSafeLoadZPos", "30.0", strPath), out _Config.dbSafeLoadZPos);


            double.TryParse(_IniFile.IniReadValue("ETC", "dbNoClampXYMoveSpeed", "50.0", strPath), out _Config.dbNoClampXYMoveSpeed);
            double.TryParse(_IniFile.IniReadValue("ETC", "dbNoClampZMoveSpeed", "50.0", strPath), out _Config.dbNoClampZMoveSpeed);

            double.TryParse(_IniFile.IniReadValue("ETC", "dbClampXYMoveSpeed", "50.0", strPath), out _Config.dbClampXYMoveSpeed);
            double.TryParse(_IniFile.IniReadValue("ETC", "dbClampZMoveSpeed", "50.0", strPath), out _Config.dbClampZMoveSpeed);

            double.TryParse(_IniFile.IniReadValue("ETC", "dbZSensingHeight", "10.0", strPath), out _Config.dbZSensingHeight);
            double.TryParse(_IniFile.IniReadValue("ETC", "dbZSensingSpeed", "20.0", strPath), out _Config.dbZSensingSpeed);
            double.TryParse(_IniFile.IniReadValue("ETC", "dbShiftMoveSpeed", "20.0", strPath), out _Config.dbShiftMoveSpeed);

            bool.TryParse(_IniFile.IniReadValue("ETC", "bUseContactAutoTestMode", "False", strPath), out _Config.bUseContactAutoTestMode);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bUseSemea", "True", strPath), out _Config.bUseSemea);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bUseMainCVMonitor", "True", strPath), out _Config.bUseMainCVMonitor);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bUseStationReservation", "True", strPath), out _Config.bUseStationReservation);
            //bool.TryParse(_IniFile.IniReadValue("ETC", "bUseAutoContact[0]", "True", strPath), out _ModelInfo.bUseHipotAutoContact);
            //bool.TryParse(_IniFile.IniReadValue("ETC", "bUseAutoContact[1]", "True", strPath), out _ModelInfo.bUseHipotAutoContact);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bUseStopper", "True", strPath), out _Config.bUseStopper);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bUseST6NgByPass", "True", strPath), out _Config.bUseST6NgByPass);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bUseCMAStatusCheck", "True", strPath), out _Config.bUseCMAStatusCheck);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bUseNutrunnerMove", "True", strPath), out _Config.bUseNutrunnerMove);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bMasterModelLoad", "False", strPath), out _Config.bMasterModelLoad);

            bool.TryParse(_IniFile.IniReadValue("ETC", "bUseNoProductPass", "False", strPath), out _Config.bUseNoProductPass);


            bool.TryParse(_IniFile.IniReadValue("ETC", "bUseAutoLoadingReadySw", "True", strPath), out _Config.bUseAutoLoadingReadySw);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bUseSameTimeContact[0]", "True", strPath), out _Config.bUseSameTimeContact[0]);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bUseSameTimeContact[1]", "True", strPath), out _Config.bUseSameTimeContact[1]);
            _Config.strBCDSymbol = _IniFile.IniReadValue("ETC", "strBCDSymbol", "7", strPath);

            _Config.strVisionDir1 = _IniFile.IniReadValue("ETC", "strVisionDir1", "TEST", strPath);
            _Config.strVisionDir2 = _IniFile.IniReadValue("ETC", "strVisionDir2", "TEST", strPath);
            _Config.strLangue = _IniFile.IniReadValue("ETC", "strLangue", "KOR", strPath);


            bool.TryParse(_IniFile.IniReadValue("ETC", "bLockingStationSkip[0]", "False", strPath), out _Config.bLockingStationSkip[0]);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bLockingStationSkip[1]", "False", strPath), out _Config.bLockingStationSkip[1]);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bLockingStationSkip[2]", "False", strPath), out _Config.bLockingStationSkip[2]);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bLockingStationSkip[3]", "False", strPath), out _Config.bLockingStationSkip[3]);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bLockingStationSkip[4]", "False", strPath), out _Config.bLockingStationSkip[4]);

            bool.TryParse(_IniFile.IniReadValue("ETC", "bTestStationSkip[0]", "False", strPath), out _Config.bTestStationSkip[0]);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bTestStationSkip[1]", "False", strPath), out _Config.bTestStationSkip[1]);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bUseScanSTTester", "False", strPath), out _Config.bUseScanSTTester);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bUseLoadingDoor", "True", strPath), out _Config.bUseLoadingDoor);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bUseHipotDoor", "True", strPath), out _Config.bUseHipotDoor);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bUseEolDoor", "True", strPath), out _Config.bUseEolDoor);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bUseOutLiftSafty", "False", strPath), out _Config.bUseOutLiftSafty);


            bool.TryParse(_IniFile.IniReadValue("ETC", "bHipotSkip", "False", strPath), out _Config.bHipotSkip);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bEolSkip", "False", strPath), out _Config.bEolSkip);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bUseReLiftCableSensing", "False", strPath), out _Config.bUseReLiftCableSensing);

            bool.TryParse(_IniFile.IniReadValue("ETC", "bUseReworkLineMode", "False", strPath), out _Config.bUseReworkLineMode);

            double.TryParse(_IniFile.IniReadValue("ETC", "dbTurnSpeed", "20.0", strPath), out _Config.dbTurnSpeed);
            double.TryParse(_IniFile.IniReadValue("ETC", "dbTurnRev", "20.0", strPath), out _Config.dbTurnRev);
            double.TryParse(_IniFile.IniReadValue("ETC", "dbLoadingAng", "90", strPath), out _Config.dbLoadingAng);

            double.TryParse(_IniFile.IniReadValue("ETC", "dbTurnOkXn", "90", strPath), out _Config.dbTurnOkXn);
            double.TryParse(_IniFile.IniReadValue("ETC", "dbTurnOkXp", "90", strPath), out _Config.dbTurnOkXp);
            double.TryParse(_IniFile.IniReadValue("ETC", "dbTurnOkYn", "90", strPath), out _Config.dbTurnOkYn);
            double.TryParse(_IniFile.IniReadValue("ETC", "dbTurnOkYp", "90", strPath), out _Config.dbTurnOkYp);

            double.TryParse(_IniFile.IniReadValue("ETC", "dbCMAMoveLoadOffset", "30", strPath), out _Config.dbCMAMoveLoadOffset);

            bool.TryParse(_IniFile.IniReadValue("ETC", "bUseReWorkTypeBCDScan", "False", strPath), out _Config.bUseReWorkTypeBCDScan);

            int.TryParse(_IniFile.IniReadValue("BCD", "nBCDAllOffsetX", "10", strPath), out _Config.nBCDAllOffsetX);
            int.TryParse(_IniFile.IniReadValue("BCD", "nBCDAllOffsetY", "10", strPath), out _Config.nBCDAllOffsetY);
            int.TryParse(_IniFile.IniReadValue("BCD", "nBCDbcdOffsetX", "10", strPath), out _Config.nBCDbcdOffsetX);
            int.TryParse(_IniFile.IniReadValue("BCD", "nBCDbcdOffsetY", "10", strPath), out _Config.nBCDbcdOffsetY);
            int.TryParse(_IniFile.IniReadValue("BCD", "nBCDtextOffsetX", "10", strPath), out _Config.nBCDtextOffsetX);
            int.TryParse(_IniFile.IniReadValue("BCD", "nBCDtextOffsetY", "10", strPath), out _Config.nBCDtextOffsetY);
            int.TryParse(_IniFile.IniReadValue("BCD", "nBCDScanStation", "3", strPath), out _Config.nBCDScanStation);
            int.TryParse(_IniFile.IniReadValue("BCD", "nETCScanStation", "2", strPath), out _Config.nETCScanStation);
            int.TryParse(_IniFile.IniReadValue("BCD", "nStartLotNum", "0", strPath), out _Config.nStartLotNum);


            int.TryParse(_IniFile.IniReadValue("TR", "nTRTurnClampTime", "3000", strPath), out _Config.nTRTurnClampTime);
            int.TryParse(_IniFile.IniReadValue("TR", "nTRStabilTime", "2000", strPath), out _Config.nTRStabilTime);

            _Config.strMESDir = _IniFile.IniReadValue("DIR", "strMESDir", "EMS", strPath);
            _Config.strHIPOTMESDir = _IniFile.IniReadValue("DIR", "strHIPOTMESDir", "EMS", strPath);
            _Config.strCMACheckDir = _IniFile.IniReadValue("DIR", "strCMACheckDir", "EMS", strPath);


            _Config.strMESDBID = _IniFile.IniReadValue("MESDB", "strMESDBID", "192.168.10.39", strPath);
            _Config.strMESDBIP = _IniFile.IniReadValue("MESDB", "strMESDBIP", "BISESS", strPath);
            _Config.strMESDBPASS = _IniFile.IniReadValue("MESDB", "strMESDBPASS", "BISESS", strPath);
            _Config.strMESDBSID = _IniFile.IniReadValue("MESDB", "strMESDBSID", "PIMES", strPath);
            int.TryParse(_IniFile.IniReadValue("MESDB", "nMESDBPort", "1521", strPath), out _Config.nMESDBPort);
            bool.TryParse(_IniFile.IniReadValue("MESDB", "bUseMESTestCheck", "False", strPath), out _Config.bUseMESTestCheck);

            int.TryParse(_IniFile.IniReadValue("TPC", "nTPCRobotCommTimeOut", "10000", strPath), out _Config.nTPCRobotCommTimeOut);


            bool.TryParse(_IniFile.IniReadValue("ETC", "bUseLockingStationDwStay", "False", strPath), out _Config.bUseLockingStationDwStay);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bUseHipotStationDwStay", "False", strPath), out _Config.bUseHipotStationDwStay);

            double.TryParse(_IniFile.IniReadValue("ETC", "dbFirstPCSheetAngle", "0", strPath), out _Config.dbFirstPCSheetAngle);
            double.TryParse(_IniFile.IniReadValue("ETC", "dbLastPCSheetAngle", "0", strPath), out _Config.dbLastPCSheetAngle);


            _Config.strOmronWHTesterCapCMD = _IniFile.IniReadValue("CAMERA", "strOmronWHTesterCapCMD", "CMD0001", strPath);
            _Config.strOmronWHTesterCapSch = _IniFile.IniReadValue("CAMERA", "strOmronWHTesterCapSch", "1", strPath);
            _Config.strOmronWHTesterCapOpt = _IniFile.IniReadValue("CAMERA", "strOmronWHTesterCapOpt", "1", strPath);
            int.TryParse(_IniFile.IniReadValue("CAMERA", "nCapDealy", "1000", strPath), out _Config.nCapDealy);
            int.TryParse(_IniFile.IniReadValue("CAMERA", "nFileGetDealy", "1000", strPath), out _Config.nFileGetDealy);


            _Config.strOmronOriginImgDir = _IniFile.IniReadValue("DIR", "strOmronOriginImgDir", "Origin", strPath);
            _Config.strOmronScreenImgDir = _IniFile.IniReadValue("DIR", "strOmronScreenImgDir", "Screen", strPath);

            _Config.strLaserMarkingSendMsg = _IniFile.IniReadValue("LASER", "strLaserMarkingSendMsg", "COM:Give me string", strPath);


            // 파레트 ID 할당
            for (int i = 0; i < 20; i++)
            {
                _Config.strPalletBCD[i] = _IniFile.IniReadValue("PALLET", String.Format("strPalletBCD[{0}]", i), "PALLETID", strPath);
            }


            bool.TryParse(_IniFile.IniReadValue("ETC", "bUseNutrunnerCommCompare", "False", strPath), out _Config.bUseNutrunnerCommCompare);
            bool.TryParse(_IniFile.IniReadValue("ETC", "bReWorkMode", "False", strPath), out _Config.bReWorkMode);


            bool.TryParse(_IniFile.IniReadValue("NUTRUNNERETH", "bUseNutrunnerEthMode", "False", strPath), out _Config.bUseNutrunnerEthMode);

            for (int i = 0; i < 6; i++)
            {
                bool.TryParse(_IniFile.IniReadValue("NUTRUNNERETH", String.Format("bUseNutrunner[{0}]", i), "True", strPath), out _Config.bUseNutrunner[i]);
                int.TryParse(_IniFile.IniReadValue("NUTRUNNERETH", String.Format("nNutrunnerPort[{0}]", i), "4545", strPath), out _Config.nNutrunnerPort[i]);
                _Config.strNutrunnerIP[i] = _IniFile.IniReadValue("NUTRUNNERETH", String.Format("strNutrunnerIP[{0}]", i), "192.168.0.1", strPath);
            }

            int.TryParse(_IniFile.IniReadValue("ETC", "nAliveCheckTime", "200000", strPath), out _Config.nAliveCheckTime);

            int.TryParse(_IniFile.IniReadValue("HIPOT", "nManualChannelP", "1", strPath), out _Config.nManualChannelP);
            int.TryParse(_IniFile.IniReadValue("HIPOT", "nManualChannelN", "2", strPath), out _Config.nManualChannelN);
            int.TryParse(_IniFile.IniReadValue("HIPOT", "nAutoChannelP", "3", strPath), out _Config.nAutoChannelP);
            int.TryParse(_IniFile.IniReadValue("HIPOT", "nAutoChannelN", "4", strPath), out _Config.nAutoChannelN);

            int.TryParse(_IniFile.IniReadValue("ETC", "nOscRetryCount", "1", strPath), out _Config.nOscRetryCount);
        }

        public static void SaveTorqueSpec()
        {
            string strPath = "./TorqueSpec.ini";

            for (int i = 0; i < _Config._TipName.Count; i++)
            {
                for (int j = 0; j < 6; j++)
                {
                    _IniFile.IniWriteValue("TORQUE_SPEC", String.Format("dbTorqueSepcMin[{0},{1}]", j, i), _Config.dbTorqueSepcMin[j, i].ToString(), strPath);
                    _IniFile.IniWriteValue("TORQUE_SPEC", String.Format("dbTorqueSepcMax[{0},{1}]", j, i), _Config.dbTorqueSepcMax[j, i].ToString(), strPath);
                    _IniFile.IniWriteValue("TORQUE_SPEC", String.Format("nAngleSepcMin[{0},{1}]", j, i), _Config.nAngleSepcMin[j, i].ToString(), strPath);
                    _IniFile.IniWriteValue("TORQUE_SPEC", String.Format("nAngleSepcMax[{0},{1}]", j, i), _Config.nAngleSepcMax[j, i].ToString(), strPath);
                }
            }
        }

        public static void LoadTorqueSpec()
        {
            string strPath = "./TorqueSpec.ini";

            for (int i = 0; i < _Config._TipName.Count; i++)
            {
                for (int j = 0; j < 6; j++)
                {
                    double.TryParse(_IniFile.IniReadValue("TORQUE_SPEC", String.Format("dbTorqueSepcMin[{0},{1}]", j, i), "0", strPath), out _Config.dbTorqueSepcMin[j, i]);
                    double.TryParse(_IniFile.IniReadValue("TORQUE_SPEC", String.Format("dbTorqueSepcMax[{0},{1}]", j, i), "0", strPath), out _Config.dbTorqueSepcMax[j, i]);
                    int.TryParse(_IniFile.IniReadValue("TORQUE_SPEC", String.Format("nAngleSepcMin[{0},{1}]", j, i), "0", strPath), out _Config.nAngleSepcMin[j, i]);
                    int.TryParse(_IniFile.IniReadValue("TORQUE_SPEC", String.Format("nAngleSepcMax[{0},{1}]", j, i), "0", strPath), out _Config.nAngleSepcMax[j, i]);
                }
            }
        }



        public static string OutputLogMsg(OutPutMessage _msg)
        {
            return _Define.strOutPutMessage[(int)_msg, nLangueIndex];
        }



        #region AXIO
        // AX IO =================================================
        public static void SetDIOPort(DO nDO, bool bEnable)
        {
            try
            {

                if (bEnable)
                    CAXD.AxdoWriteOutport((int)nDO, 1);
                else
                    CAXD.AxdoWriteOutport((int)nDO, 0);
            }
            catch { }
        }

        public static bool GetLoadingDoor()
        {
            if (_Config.bUseLoadingDoor)
            {
                if (GetDIOPort(DI.LOADING_DOOR2)) return true;
                else return false;
            }
            else return true;
        }

        public static bool GetDIOPort(DI nDI)
        {
            uint bResult = 0;


            try
            {
                CAXD.AxdiReadInport((int)nDI, ref bResult);
            }
            catch { }

            return (bResult != 0) ? true : false;
        }



        public static bool GetDIOPortStat(DO nDO)
        {
            uint bResult = 0;

            try
            {
                CAXD.AxdoReadOutport((int)nDO, ref bResult);
            }
            catch { }
            return (bResult != 0) ? true : false;
        }
        // =========================================================
        #endregion
    }
}
