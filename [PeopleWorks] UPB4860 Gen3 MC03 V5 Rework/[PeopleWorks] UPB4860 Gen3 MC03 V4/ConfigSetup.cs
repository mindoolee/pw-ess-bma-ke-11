using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
    public partial class ConfigSetup : Form
    {
        public ConfigSetup()
        {
            InitializeComponent();
        }


        private void LoadingDataView()
        {
            dataGridView1.Rows.Clear();
            if (_Config.strLangue == "KOR")
            {
                dataGridView1.Rows.Add("로딩시 안전 이동 높이", _Config.dbSafeLoadZPos);
                dataGridView1.Rows.Add("제품 클램프 안정화 시간", _Config.nClampStabilTime);
                dataGridView1.Rows.Add("제품 회전 속도", _Config.dbTurnSpeed);
                dataGridView1.Rows.Add("회전축 원점 보정", _Config.dbTurnRev);
                dataGridView1.Rows.Add("제품 로딩 각도", _Config.dbLoadingAng);
                dataGridView1.Rows.Add("트랜스퍼 제품 클램프 시간", _Config.nTRTurnClampTime);
                dataGridView1.Rows.Add("트랜스퍼 이송 안정화 시간", _Config.nTRStabilTime);
                dataGridView1.Rows.Add("Main C/V Auto Stop Time", _Config.nCVAutoStopTime);
                dataGridView1.Rows.Add("로딩 안전 위치 X", _Config.dbLoadingUnSafePosX);
                dataGridView1.Rows.Add("로딩 안전 위치 Z", _Config.dbLoadingUnSafePosZ);
                dataGridView1.Rows.Add("첫번째 PC Sheet 부착 로딩각도", _Config.dbFirstPCSheetAngle);
                dataGridView1.Rows.Add("마지막 PC Sheet 부착 로딩각도", _Config.dbLastPCSheetAngle);

            }
            else if (_Config.strLangue == "CHINA")
            {
                dataGridView1.Rows.Add("抓取后提升高度", _Config.dbSafeLoadZPos);
                dataGridView1.Rows.Add("夹取产品等待时间", _Config.nClampStabilTime);
                dataGridView1.Rows.Add("产品回转速度", _Config.dbTurnSpeed);
                dataGridView1.Rows.Add("原点回转校验", _Config.dbTurnRev);
                dataGridView1.Rows.Add("产品角度修正", _Config.dbLoadingAng);
                dataGridView1.Rows.Add("转运单位产品固定时间", _Config.nTRTurnClampTime);
                dataGridView1.Rows.Add("转运单位建立时间", _Config.nTRStabilTime);
                dataGridView1.Rows.Add("Main C/V Auto Stop Time", _Config.nCVAutoStopTime);
                dataGridView1.Rows.Add("抓取安全位置 X", _Config.dbLoadingUnSafePosX);
                dataGridView1.Rows.Add("抓取安全位置 Z", _Config.dbLoadingUnSafePosZ);
                dataGridView1.Rows.Add("初 PC Sheet 附着角度", _Config.dbFirstPCSheetAngle);
                dataGridView1.Rows.Add("最后 PC Sheet 附着角度", _Config.dbLastPCSheetAngle);

            }

        }

        private void LoadingDataLoad()
        {
            dataGridView1.EndEdit();

            double.TryParse(dataGridView1[1, 0].Value.ToString(), out _Config.dbSafeLoadZPos);
            int.TryParse(dataGridView1[1, 1].Value.ToString(), out _Config.nClampStabilTime);
            double.TryParse(dataGridView1[1, 2].Value.ToString(), out _Config.dbTurnSpeed);
            double.TryParse(dataGridView1[1, 3].Value.ToString(), out _Config.dbTurnRev);
            double.TryParse(dataGridView1[1, 4].Value.ToString(), out _Config.dbLoadingAng);
            int.TryParse(dataGridView1[1, 5].Value.ToString(), out _Config.nTRTurnClampTime);
            int.TryParse(dataGridView1[1, 6].Value.ToString(), out _Config.nTRStabilTime);
            int.TryParse(dataGridView1[1, 7].Value.ToString(), out _Config.nCVAutoStopTime);
            double.TryParse(dataGridView1[1, 8].Value.ToString(), out _Config.dbLoadingUnSafePosX);
            double.TryParse(dataGridView1[1, 9].Value.ToString(), out _Config.dbLoadingUnSafePosZ);
            double.TryParse(dataGridView1[1, 10].Value.ToString(), out _Config.dbFirstPCSheetAngle);
            double.TryParse(dataGridView1[1, 11].Value.ToString(), out _Config.dbLastPCSheetAngle);
        }

        private void LiftDataView()
        {
            comboBox1.Text = _Config.strLangue;

            dataGridView2.Rows.Clear();
            if (_Config.strLangue == "KOR")
            {
                dataGridView2.Rows.Add("리프트 실린더 안정화 시간", _Config.nLiftCylStabilTime);
                dataGridView2.Rows.Add("리프트 제품 투입 지연 시간", _Config.nLiftInTime);
                dataGridView2.Rows.Add("리프트 타임아웃 시간", _Config.nLiftTimeOut);
                dataGridView2.Rows.Add("리턴 리프트 제품 배출 시간", _Config.nReturnPalletOutTime);
            }
            else if (_Config.strLangue == "CHINA")
            {
                dataGridView2.Rows.Add("气缸缓冲时间", _Config.nLiftCylStabilTime);
                dataGridView2.Rows.Add("Pallet进入时，传送带延迟", _Config.nLiftInTime);
                dataGridView2.Rows.Add("电梯等待时间", _Config.nLiftTimeOut);
                dataGridView2.Rows.Add("提起产品等待时间", _Config.nReturnPalletOutTime);
            }
            else
            {
                dataGridView2.Rows.Add("리프트 실린더 안정화 시간", _Config.nLiftCylStabilTime);
                dataGridView2.Rows.Add("리프트 제품 투입 지연 시간", _Config.nLiftInTime);
                dataGridView2.Rows.Add("리프트 타임아웃 시간", _Config.nLiftTimeOut);
                dataGridView2.Rows.Add("리턴 리프트 제품 배출 시간", _Config.nReturnPalletOutTime);
            }


            dataGridView5.Rows.Clear();
            for(int i = 0; i < 11; i++)
            {
                dataGridView5.Rows.Add(String.Format("PALLET ID #{0}", i + 1), _Config.strPalletBCD[i]);
            }
            
        }

        private void LiftDataLoad()
        {
            _Config.strLangue = comboBox1.Text;
            dataGridView2.EndEdit();
            int.TryParse(dataGridView2[1, 0].Value.ToString(), out _Config.nLiftCylStabilTime);
            int.TryParse(dataGridView2[1, 1].Value.ToString(), out _Config.nLiftInTime);
            int.TryParse(dataGridView2[1, 2].Value.ToString(), out _Config.nLiftTimeOut);
            int.TryParse(dataGridView2[1, 3].Value.ToString(), out _Config.nReturnPalletOutTime);


            dataGridView5.EndEdit();
            for(int i = 0; i < 11; i++)
            {
                _Config.strPalletBCD[i] = dataGridView5[1, i].Value.ToString();
            }
        }

        //private void BcdDataView()
        //{

        //    dataGridView3.Rows.Clear();
        //    if (_Config.strLangue == "KOR")
        //    {
        //        //dataGridView3.Rows.Add("바코드 전체 오프셋 X", _Config.nBCDAllOffsetX);
        //        //dataGridView3.Rows.Add("바코드 전체 오프셋 Y", _Config.nBCDAllOffsetY);
        //        //dataGridView3.Rows.Add("바코드 오프셋 X", _Config.nBCDbcdOffsetX);
        //        //dataGridView3.Rows.Add("바코드 오프셋 Y", _Config.nBCDbcdOffsetY);
        //        //dataGridView3.Rows.Add("바코드 텍스트 오프셋 X", _Config.nBCDtextOffsetX);
        //        //dataGridView3.Rows.Add("바코드 텍스트 오프셋 Y", _Config.nBCDtextOffsetY);
        //        dataGridView3.Rows.Add("바코드 스캔 스테이션", _Config.nBCDScanStation);
        //        //_BCDDataTable.Rows.Add("바코드 설비 구분자", _Config.strBCDSymbol);
        //        dataGridView3.Rows.Add("이종품 검사 스테이션", _Config.nETCScanStation);
        //        dataGridView3.Rows.Add("시작 번호", _Config.nStartLotNum);
        //    }
        //    else if (_Config.strLangue == "CHINA")
        //    {
        //        //dataGridView3.Rows.Add("条码完全抵消 X", _Config.nBCDAllOffsetX);
        //        //dataGridView3.Rows.Add("条码完全抵消 Y", _Config.nBCDAllOffsetY);
        //        //dataGridView3.Rows.Add("条码偏移 X", _Config.nBCDbcdOffsetX);
        //        //dataGridView3.Rows.Add("条码偏移 Y", _Config.nBCDbcdOffsetY);
        //        //dataGridView3.Rows.Add("条码文字偏移 X", _Config.nBCDtextOffsetX);
        //        //dataGridView3.Rows.Add("条码文字偏移 Y", _Config.nBCDtextOffsetY);
        //        dataGridView3.Rows.Add("条码扫描位置", _Config.nBCDScanStation);
        //        //_BCDDataTable.Rows.Add("바코드 설비 구분자", _Config.strBCDSymbol);
        //        dataGridView3.Rows.Add("FUSE检查位置", _Config.nETCScanStation);
        //        dataGridView3.Rows.Add("LOT 序号", _Config.nStartLotNum);
        //    }

        //}

        //private void BcdDataLoad()
        //{
        //    dataGridView3.EndEdit();
        //    //int.TryParse(dataGridView3[1, 0].Value.ToString(), out _Config.nBCDAllOffsetX);
        //    //int.TryParse(dataGridView3[1, 1].Value.ToString(), out _Config.nBCDAllOffsetY);
        //    //int.TryParse(dataGridView3[1, 2].Value.ToString(), out _Config.nBCDbcdOffsetX);
        //    //int.TryParse(dataGridView3[1, 3].Value.ToString(), out _Config.nBCDbcdOffsetY);
        //    //int.TryParse(dataGridView3[1, 4].Value.ToString(), out _Config.nBCDtextOffsetX);
        //    //int.TryParse(dataGridView3[1, 5].Value.ToString(), out _Config.nBCDtextOffsetY);
        //    int.TryParse(dataGridView3[1, 0].Value.ToString(), out _Config.nBCDScanStation);
        //    //_Config.strBCDSymbol = _BCDDataTable.Rows[7][1].ToString();
        //    int.TryParse(dataGridView3[1, 1].Value.ToString(), out _Config.nETCScanStation);
        //    int.TryParse(dataGridView3[1, 2].Value.ToString(), out _Config.nStartLotNum);
        //}

        private void TestZoneView()
        {

            dataGridView14.Rows.Clear();
            if (_Config.strLangue == "KOR")
            {
                dataGridView14.Rows.Add("검사존 이동속도", _Config.dbTestZoneMoveSpeed);
                dataGridView14.Rows.Add("검사존 저속 이동속도", _Config.dbTestZoneContactSpeed);
                dataGridView14.Rows.Add("검사존 저속 이동 거리", _Config.dbTestZoneContactMovePos);
                dataGridView14.Rows.Add("검사존 Z축 저속 이동 거리", _Config.dbTestZoneContactZSlowMovePos);
                dataGridView14.Rows.Add("검사존 Z축 저속 이동속도", _Config.dbTestZoneContactZSlowMoveSpeed);
                dataGridView14.Rows.Add("바코드 리딩 대기시간", _Config.nBCDScanTimeOut);

                dataGridView14.Rows.Add("외함측정 XY 이동속도", _Config.dbOmronCameraXYMoveSpeed);
                dataGridView14.Rows.Add("외함측정 Z 이동속도", _Config.dbOmronCameraZMoveSpeed);
                dataGridView14.Rows.Add("외함측정 모션 안정화 시간(Msec)", _Config.nOmronCameraStabliTime);

                dataGridView14.Rows.Add("스크린 캡쳐 커맨드", _Config.strOmronWHTesterCapCMD);
                dataGridView14.Rows.Add("스크린 캡쳐 번호", _Config.strOmronWHTesterCapSch);
                dataGridView14.Rows.Add("스크린 캡쳐 옵션", _Config.strOmronWHTesterCapOpt);
                dataGridView14.Rows.Add("스크린 캡쳐 딜레이(Msec)", _Config.nCapDealy);
                dataGridView14.Rows.Add("캡처 파일 복사 딜레이(Msec)", _Config.nFileGetDealy);

                dataGridView14.Rows.Add("수동 하이팟 검사 채널(+)", _Config.nManualChannelP);
                dataGridView14.Rows.Add("수동 하이팟 검사 채널(-)", _Config.nManualChannelN);
                dataGridView14.Rows.Add("자동 하이팟 검사 채널(+)", _Config.nAutoChannelP);
                dataGridView14.Rows.Add("자동 하이팟 검사 채널(-)", _Config.nAutoChannelN);
                
                dataGridView14.Rows.Add("OSC 검사 재시도 횟수", _Config.nOscRetryCount);
            }
            else if (_Config.strLangue == "CHINA")
            {
                dataGridView14.Rows.Add("HIPOT,EOL 移动速度(基本)", _Config.dbTestZoneMoveSpeed);
                dataGridView14.Rows.Add("HIPOT,EOL 移动速度(慢)", _Config.dbTestZoneContactSpeed);
                dataGridView14.Rows.Add("HIPOT,EOL 移动距离", _Config.dbTestZoneContactMovePos);
                dataGridView14.Rows.Add("HIPOT,EOL Z 移动距离", _Config.dbTestZoneContactZSlowMovePos);
                dataGridView14.Rows.Add("HIPOT,EOL Z 移动速度(慢)", _Config.dbTestZoneContactZSlowMoveSpeed);
                dataGridView14.Rows.Add("条形码扫描等待时间", _Config.nBCDScanTimeOut);

                dataGridView14.Rows.Add("외함측정 XY 이동속도", _Config.dbOmronCameraXYMoveSpeed);
                dataGridView14.Rows.Add("외함측정 Z 이동속도", _Config.dbOmronCameraZMoveSpeed);
                dataGridView14.Rows.Add("외함측정 모션 안정화 시간(Msec)", _Config.nOmronCameraStabliTime);

                dataGridView14.Rows.Add("스크린 캡쳐 커맨드", _Config.strOmronWHTesterCapCMD);
                dataGridView14.Rows.Add("스크린 캡쳐 번호", _Config.strOmronWHTesterCapSch);
                dataGridView14.Rows.Add("스크린 캡쳐 옵션", _Config.strOmronWHTesterCapOpt);
                dataGridView14.Rows.Add("스크린 캡쳐 딜레이(Msec)", _Config.nCapDealy);
                dataGridView14.Rows.Add("캡처 파일 복사 딜레이(Msec)", _Config.nFileGetDealy);

                dataGridView14.Rows.Add("수동 하이팟 검사 채널(+)", _Config.nManualChannelP);
                dataGridView14.Rows.Add("수동 하이팟 검사 채널(-)", _Config.nManualChannelN);
                dataGridView14.Rows.Add("자동 하이팟 검사 채널(+)", _Config.nAutoChannelP);
                dataGridView14.Rows.Add("자동 하이팟 검사 채널(-)", _Config.nAutoChannelN);

                dataGridView14.Rows.Add("OSC 검사 재시도 횟수", _Config.nOscRetryCount);
            }

            dataGridView4.Rows.Clear();

            if (_Config.strLangue == "KOR")
            {
                dataGridView4.Rows.Add("관리자 비밀번호", _Config.strAdminPass);
                dataGridView4.Rows.Add("체결 카운트 변경 비밀번호", _Config.strTitePass);
                dataGridView4.Rows.Add("LOT CLEAR TIME", _Config.nLotClearTime.ToString("0000"));
                dataGridView4.Rows.Add("MES 데이터 저장 경로", _Config.strMESDir);
                dataGridView4.Rows.Add("HIPOT 데이터 저장 경로", _Config.strHIPOTMESDir);
            }

            else if (_Config.strLangue == "CHINA")
            {
                dataGridView4.Rows.Add("管理员密码", _Config.strAdminPass);
                dataGridView4.Rows.Add("更改编辑紧固计数的密码", _Config.strTitePass);
                dataGridView4.Rows.Add("LOT 复位时间", _Config.nLotClearTime.ToString("0000"));
                dataGridView4.Rows.Add("MES DATA 保存路径", _Config.strMESDir);
                dataGridView4.Rows.Add("HIPOT DATA 保存路径", _Config.strHIPOTMESDir);
            }


        }

        private void TestZoneLoad()
        {
            dataGridView14.EndEdit();
            double.TryParse(dataGridView14[1, 0].Value.ToString(), out _Config.dbTestZoneMoveSpeed);
            double.TryParse(dataGridView14[1, 1].Value.ToString(), out _Config.dbTestZoneContactSpeed);
            double.TryParse(dataGridView14[1, 2].Value.ToString(), out _Config.dbTestZoneContactMovePos);
            double.TryParse(dataGridView14[1, 3].Value.ToString(), out _Config.dbTestZoneContactZSlowMovePos);
            double.TryParse(dataGridView14[1, 4].Value.ToString(), out _Config.dbTestZoneContactZSlowMoveSpeed);
            int.TryParse(dataGridView14[1, 5].Value.ToString(), out _Config.nBCDScanTimeOut);

            double.TryParse(dataGridView14[1, 6].Value.ToString(), out _Config.dbOmronCameraXYMoveSpeed);
            double.TryParse(dataGridView14[1, 7].Value.ToString(), out _Config.dbOmronCameraZMoveSpeed);
            int.TryParse(dataGridView14[1, 8].Value.ToString(), out _Config.nOmronCameraStabliTime);

            _Config.strOmronWHTesterCapCMD = dataGridView14[1, 9].Value.ToString();
            _Config.strOmronWHTesterCapSch = dataGridView14[1, 10].Value.ToString();
            _Config.strOmronWHTesterCapOpt = dataGridView14[1, 11].Value.ToString();

            int.TryParse(dataGridView14[1, 12].Value.ToString(), out _Config.nCapDealy);
            int.TryParse(dataGridView14[1, 13].Value.ToString(), out _Config.nFileGetDealy);
            int.TryParse(dataGridView14[1, 14].Value.ToString(), out _Config.nManualChannelP);
            int.TryParse(dataGridView14[1, 15].Value.ToString(), out _Config.nManualChannelN);
            int.TryParse(dataGridView14[1, 16].Value.ToString(), out _Config.nAutoChannelP);
            int.TryParse(dataGridView14[1, 17].Value.ToString(), out _Config.nAutoChannelN);

            int.TryParse(dataGridView14[1, 18].Value.ToString(), out _Config.nOscRetryCount);

            _Config.strAdminPass = dataGridView4[1, 0].Value.ToString();
            _Config.strTitePass = dataGridView4[1, 1].Value.ToString();
            int.TryParse(dataGridView4[1, 2].Value.ToString(), out  _Config.nLotClearTime);
            _Config.strMESDir = dataGridView4[1, 3].Value.ToString();
            _Config.strHIPOTMESDir = dataGridView4[1, 4].Value.ToString();
        }


        private void ConfigSetup_Load(object sender, EventArgs e)
        {
            LoadingDataView();
            LiftDataView();
            //BcdDataView();
            TestZoneView();

            checkBox1.Checked = _Config.bAirPressure;
            checkBox2.Checked = _Config.bUseAdminPass;
            checkBox6.Checked = _Config.bUseReLiftCableSensing;
            checkBox5.Checked = _Config.bUseReworkLineMode;
            checkBox4.Checked = _Config.bUseMainCVMonitor;
            checkBox3.Checked = _Config.bUseReWorkTypeBCDScan;
            checkBox9.Checked = _Config.bUseAutoContact[0];
            checkBox7.Checked = _Config.bUseAutoContact[1];
            //checkBox8.Checked = _Config.bUseStopper;
            checkBox10.Checked = _Config.bUseST6NgByPass;

            //checkBox28.Checked = _Config.bLockingStationSkip[0];
            //checkBox27.Checked = _Config.bLockingStationSkip[1];
            //checkBox26.Checked = _Config.bLockingStationSkip[2];
            //checkBox25.Checked = _Config.bLockingStationSkip[3];
            //checkBox24.Checked = _Config.bLockingStationSkip[4];

            //checkBox15.Checked = _Config.bTestStationSkip[0];
            //checkBox16.Checked = _Config.bTestStationSkip[1];dataGridView3
            checkBox17.Checked = _Config.bUseOutLiftSafty;
            checkBox18.Checked = _Config.bUseAutoLoadingReadySw;
            checkBox19.Checked = _Config.bUseHipotFix;
            checkBox20.Checked = _Config.bUseEolFix;
            checkBox21.Checked = _Config.bUseCVAutoStop;
            checkBox23.Checked = _Config.bReWorkMode;
            checkBox29.Checked = _Config.bMasterModelLoad;

            checkBox22.Checked = _Config.bUseNoProductPass;
            checkBox13.Checked = _Config.bUseMESTestCheck;
            checkBox14.Checked = _Config.bUseLockingStationDwStay;
            checkBox15.Checked = _Config.bUseHipotStationDwStay;
            checkBox16.Checked =_Config.bUseNutrunnerCommCompare;


            //checkBox11.Checked = _Config.bHipotSkip;
            //checkBox12.Checked = _Config.bEolSkip;


            if (_Config.strLangue == "KOR")
            {
                checkBox9.Text = "HIPOT  자동컨텍 기능 사용함";
                checkBox7.Text = "EOL 자동컨텍 기능 사용함";
                checkBox10.Text = "EOL 불량 바이패스 기능 사용함";
                checkBox18.Text = "로딩리프트 파레트 있을시 자동으로 스위치 눌림기능 사용함";

                checkBox1.Text = "공압감지 사용함";
                checkBox2.Text = "관리자 비밀번호 사용함";
                checkBox4.Text = "메인컨베어 미동작시 배출안함";

                checkBox14.Text = "파레트 하강대기 기능 사용";
                checkBox23.Text = "리웍모드2(BMA바코드변경)";
            }
            else if (_Config.strLangue == "CHINA")
            {
                checkBox9.Text = "HIPOT自动测试机能";
                checkBox7.Text = "EOL自动测试机能";
                checkBox10.Text = "EOL不良分流机能";
                checkBox18.Text = "CMA自动堆叠";


                checkBox1.Text = "气压监控";
                checkBox2.Text = "管理者密码使用";
                checkBox4.Text = "主传送带不运转时不排出";

                checkBox6.Text = "排放时感应通信电缆使用盒";
                checkBox22.Text = "HIPOT/EOL 无产品时自动排出";
                checkBox21.Text = "Main C/V 自动模式";
                checkBox13.Text = "HIPOT/EOL 检查时 MES 确认";
                checkBox17.Text = "排出 LIFT 安全传感器使用";

                checkBox14.Text = "Pallet 停留下";
                checkBox15.Text = "Pallet 停留下 ( HIPOT,EOL )";

                checkBox23.Text = "리웍모드2(BMA条码变更)";
                checkBox3.Visible = false;
                checkBox5.Visible = false;
            }


        }

        private void simpleButton1_Click(object sender, EventArgs e)
        {
            LoadingDataLoad();
            LiftDataLoad();
            //BcdDataLoad();
            TestZoneLoad();

            _Config.bAirPressure = checkBox1.Checked;
            _Config.bUseAdminPass = checkBox2.Checked;
            _Config.bUseReLiftCableSensing = checkBox6.Checked;
            _Config.bUseReworkLineMode = checkBox5.Checked;
            _Config.bUseMainCVMonitor = checkBox4.Checked;
            _Config.bUseReWorkTypeBCDScan = checkBox3.Checked;
            _Config.bUseAutoContact[0] = checkBox9.Checked;
            _Config.bUseAutoContact[1] = checkBox7.Checked;
            //_Config.bUseStopper = checkBox8.Checked;
            _Config.bUseST6NgByPass = checkBox10.Checked;
            _Config.bUseOutLiftSafty = checkBox17.Checked;


            //_Config.bLockingStationSkip[0] = checkBox28.Checked;
            //_Config.bLockingStationSkip[1] = checkBox27.Checked;
            //_Config.bLockingStationSkip[2] = checkBox26.Checked;
            //_Config.bLockingStationSkip[3] = checkBox25.Checked;
            //_Config.bLockingStationSkip[4] = checkBox24.Checked;
            //_Config.bTestStationSkip[0] = checkBox15.Checked;
            //_Config.bTestStationSkip[1] = checkBox16.Checked;

            _Config.bUseAutoLoadingReadySw = checkBox18.Checked;

            //_Config.bHipotSkip = checkBox11.Checked;
            //_Config.bEolSkip = checkBox12.Checked;

            _Config.bUseHipotFix = checkBox19.Checked;
            _Config.bUseEolFix = checkBox20.Checked;

            _Config.bUseNoProductPass = checkBox22.Checked;
             _Config.bUseMESTestCheck = checkBox13.Checked;
            _Config.bUseLockingStationDwStay = checkBox14.Checked;
            _Config.bUseHipotStationDwStay = checkBox15.Checked;
            _Config.bUseCVAutoStop = checkBox21.Checked;
            _Config.bReWorkMode = checkBox23.Checked;
            _Config.bMasterModelLoad = checkBox29.Checked;

            _Config.bUseBoltSupply = false;
            Program.SaveIniFile();
            this.Close();
        }

        private void simpleButton2_Click(object sender, EventArgs e)
        {
            LoadingDataLoad();
            LiftDataLoad();
            //BcdDataLoad();
            TestZoneLoad();

            _Config.bAirPressure = checkBox1.Checked;
            _Config.bUseAdminPass = checkBox2.Checked;
            _Config.bUseReLiftCableSensing = checkBox6.Checked;
            _Config.bUseReworkLineMode = checkBox5.Checked;
            _Config.bUseMainCVMonitor = checkBox4.Checked;
            _Config.bUseReWorkTypeBCDScan = checkBox3.Checked;
            _Config.bUseAutoContact[0] = checkBox9.Checked;
            _Config.bUseAutoContact[1] = checkBox7.Checked;
            //_Config.bUseStopper = checkBox8.Checked;
            _Config.bUseST6NgByPass = checkBox10.Checked;
            _Config.bUseOutLiftSafty = checkBox17.Checked;


            //_Config.bLockingStationSkip[0] = checkBox28.Checked;
            //_Config.bLockingStationSkip[1] = checkBox27.Checked;
            //_Config.bLockingStationSkip[2] = checkBox26.Checked;
            //_Config.bLockingStationSkip[3] = checkBox25.Checked;
            //_Config.bLockingStationSkip[4] = checkBox24.Checked;
            ////_Config.bTestStationSkip[0] = checkBox15.Checked;
            ////_Config.bTestStationSkip[1] = checkBox16.Checked;

            _Config.bUseAutoLoadingReadySw = checkBox18.Checked;


            //_Config.bHipotSkip = checkBox11.Checked;
            //_Config.bEolSkip = checkBox12.Checked;

            _Config.bUseHipotFix = checkBox19.Checked;
            _Config.bUseEolFix = checkBox20.Checked;
            _Config.bUseNoProductPass = checkBox22.Checked;
            _Config.bUseMESTestCheck = checkBox13.Checked;
            _Config.bUseLockingStationDwStay = checkBox14.Checked;
            _Config.bUseHipotStationDwStay = checkBox15.Checked;
            _Config.bUseNutrunnerCommCompare = checkBox16.Checked;
            _Config.bUseCVAutoStop = checkBox21.Checked;
            _Config.bReWorkMode = checkBox23.Checked;
            _Config.bMasterModelLoad = checkBox29.Checked;
            _Config.bUseBoltSupply = false;
            Program.SaveIniFile();
        }

        private void simpleButton3_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void simpleButton9_Click(object sender, EventArgs e)
        {
            LoadingDataLoad();
            LiftDataLoad();
            //BcdDataLoad();
            TestZoneLoad();

            _Config.bAirPressure = checkBox1.Checked;
            _Config.bUseAdminPass = checkBox2.Checked;
            _Config.bUseReLiftCableSensing = checkBox6.Checked;
            _Config.bUseReworkLineMode = checkBox5.Checked;
            _Config.bUseMainCVMonitor = checkBox4.Checked;
            _Config.bUseReWorkTypeBCDScan = checkBox3.Checked;
            _Config.bUseAutoContact[0] = checkBox9.Checked;
            _Config.bUseAutoContact[1] = checkBox7.Checked;
            //_Config.bUseStopper = checkBox8.Checked;
            _Config.bUseST6NgByPass = checkBox10.Checked;
            _Config.bUseOutLiftSafty = checkBox17.Checked;


            //_Config.bLockingStationSkip[0] = checkBox28.Checked;
            //_Config.bLockingStationSkip[1] = checkBox27.Checked;
            //_Config.bLockingStationSkip[2] = checkBox26.Checked;
            //_Config.bLockingStationSkip[3] = checkBox25.Checked;
            //_Config.bLockingStationSkip[4] = checkBox24.Checked;
            ////_Config.bTestStationSkip[0] = checkBox15.Checked;
            ////_Config.bTestStationSkip[1] = checkBox16.Checked;

            _Config.bUseAutoLoadingReadySw = checkBox18.Checked;

            //_Config.bHipotSkip = checkBox11.Checked;
            //_Config.bEolSkip = checkBox12.Checked;

            _Config.bUseHipotFix = checkBox19.Checked;
            _Config.bUseEolFix = checkBox20.Checked;

            _Config.bUseNoProductPass = checkBox22.Checked;
            _Config.bUseMESTestCheck = checkBox13.Checked;
            _Config.bUseLockingStationDwStay = checkBox14.Checked;
            _Config.bUseHipotStationDwStay = checkBox15.Checked;
            _Config.bUseNutrunnerCommCompare = checkBox16.Checked;
            _Config.bUseCVAutoStop = checkBox21.Checked;
            _Config.bReWorkMode = checkBox23.Checked;
            _Config.bMasterModelLoad = checkBox29.Checked;

            _Config.bUseBoltSupply = false;
            Program.SaveIniFile();
            this.Close();
        }

        private void simpleButton7_Click(object sender, EventArgs e)
        {
            LoadingDataLoad();
            LiftDataLoad();
            //BcdDataLoad();
            TestZoneLoad();

            _Config.bAirPressure = checkBox1.Checked;
            _Config.bUseAdminPass = checkBox2.Checked;
            _Config.bUseReLiftCableSensing = checkBox6.Checked;
            _Config.bUseReworkLineMode = checkBox5.Checked;
            _Config.bUseMainCVMonitor = checkBox4.Checked;
            _Config.bUseReWorkTypeBCDScan = checkBox3.Checked;
            _Config.bUseAutoContact[0] = checkBox9.Checked;
            _Config.bUseAutoContact[1] = checkBox7.Checked;
            //_Config.bUseStopper = checkBox8.Checked;
            _Config.bUseST6NgByPass = checkBox10.Checked;
            _Config.bUseOutLiftSafty = checkBox17.Checked;


            //_Config.bLockingStationSkip[0] = checkBox28.Checked;
            //_Config.bLockingStationSkip[1] = checkBox27.Checked;
            //_Config.bLockingStationSkip[2] = checkBox26.Checked;
            //_Config.bLockingStationSkip[3] = checkBox25.Checked;
            //_Config.bLockingStationSkip[4] = checkBox24.Checked;
            ////_Config.bTestStationSkip[0] = checkBox15.Checked;
            ////_Config.bTestStationSkip[1] = checkBox16.Checked;

            _Config.bUseAutoLoadingReadySw = checkBox18.Checked;


            //_Config.bHipotSkip = checkBox11.Checked;
            //_Config.bEolSkip = checkBox12.Checked;

            _Config.bUseHipotFix = checkBox19.Checked;
            _Config.bUseEolFix = checkBox20.Checked;
            _Config.bUseNoProductPass = checkBox22.Checked;
            _Config.bUseMESTestCheck = checkBox13.Checked;
            _Config.bUseLockingStationDwStay = checkBox14.Checked;
            _Config.bUseHipotStationDwStay = checkBox15.Checked;
            _Config.bUseNutrunnerCommCompare = checkBox16.Checked;
            _Config.bUseCVAutoStop = checkBox21.Checked;
            _Config.bReWorkMode = checkBox23.Checked;
            _Config.bMasterModelLoad = checkBox29.Checked;
            _Config.bUseBoltSupply = false;
            Program.SaveIniFile();
        }

        private void simpleButton15_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void tabPage1_Click(object sender, EventArgs e)
        {

        }
    }
}
