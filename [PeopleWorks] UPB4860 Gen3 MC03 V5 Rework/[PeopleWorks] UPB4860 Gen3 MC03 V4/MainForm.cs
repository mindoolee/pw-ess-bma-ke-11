using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Drawing.Imaging;
using System.Xml.Serialization;
using Oracle.ManagedDataAccess.Client;

namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
    public partial class MainForm : Form
    {
        #region 시스템 메뉴 추가
        private const int WM_SYSCOMMAND = 0x112;
        private const int MF_STRING = 0x0;
        private const int MF_SEPARATOR = 0x800;

        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern IntPtr GetSystemMenu(IntPtr hWnd, bool bRevert);

        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern bool AppendMenu(IntPtr hMenu, int uFlags, int uIDNewItem, string lpNewItem);

        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern bool InsertMenu(IntPtr hMenu, int uPosition, int uFlags, int uIDNewItem, string lpNewItem);



        private int SYSMENU_DIO1 = 0x1;
        private int SYSMENU_STEP = 0x2;
        private int TORQUE_MENU = 0x4;

        protected override void OnHandleCreated(EventArgs e)
        {
            base.OnHandleCreated(e);

            // Get a handle to a copy of this form's system (window) menu
            IntPtr hSysMenu = GetSystemMenu(this.Handle, false);

            // Add a separator
            AppendMenu(hSysMenu, MF_SEPARATOR, 0, string.Empty);

            // Add the About menu item
            AppendMenu(hSysMenu, MF_STRING, SYSMENU_DIO1, "I/O 입출력 모니터");
            AppendMenu(hSysMenu, MF_STRING, SYSMENU_STEP, "Step Monitor");
            AppendMenu(hSysMenu, MF_STRING, TORQUE_MENU, "Torque Spec");

        }
        protected override void WndProc(ref Message m)
        {
            base.WndProc(ref m);

            // Test if the About item was selected from the system menu
            if ((m.Msg == WM_SYSCOMMAND) && ((int)m.WParam == SYSMENU_DIO1))
            {
                // DIO_Monitor _form = new DIO_Monitor();

                IO_Monitor _form = new IO_Monitor();
                _form.Show();
            }

            // Test if the About item was selected from the system menu
            if ((m.Msg == WM_SYSCOMMAND) && ((int)m.WParam == SYSMENU_STEP))
            {
                StepMonitor _form = new StepMonitor();
                _form.Show();
            }

            // Test if the About item was selected from the system menu
            if ((m.Msg == WM_SYSCOMMAND) && ((int)m.WParam == TORQUE_MENU))
            {
                TorqueSpec torqueSpec = new TorqueSpec();
                torqueSpec.Show();
            }
        }
        #endregion


        public MainForm()
        {
            InitializeComponent();

            
    
        }

        private void simpleButton8_Click(object sender, EventArgs e)
        {
            if (_Config.bUseAdminPass)
            {
                AdminPass _forms = new AdminPass();
                if (_forms.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    Program._modelSetup = new ModelSetup(Program._ModelInfo);
                    Program._modelSetup.ShowDialog();
                }
            }
            else
            {
                Program._modelSetup = new ModelSetup(Program._ModelInfo);
                Program._modelSetup.ShowDialog();
            }
            _SysInfo.bChangeHipotInfo = true;
            Program._MasterLoadTime = DateTime.Now;
        }


        public void ViewHipotLog(DATA_RESULT _HipotResult)
        {

            listView2.BeginUpdate();
            // == 리스트뷰 업데이트 시작 

            // 최대 100라인
            if (listView2.Items.Count > 100) listView2.Items.RemoveAt(0);

            // 시간 출력
            ListViewItem lvitem = new ListViewItem();
            

            lvitem.Text = System.DateTime.Now.ToString("HH:mm:ss");     // 시간

            lvitem.SubItems.Add(_HipotResult.strBCD);                   // 바코드

            // 종합 결과
            if(_HipotResult.tr_TOTAL == TEST_RESULT.OK)
            {
                lvitem.SubItems.Add("O.K", Color.Black, Color.LightGreen, Font);
            }
            else
            {
                lvitem.SubItems.Add("N.G", Color.Black, Color.LightPink, Font);
            }

            
            // 단자접촉성(+)
            if(_HipotResult.tr_OSC == TEST_RESULT.OK)
            {
                lvitem.SubItems.Add((_HipotResult.dbOSCData * 1000000000).ToString("0.00 nF"), Color.Black, Color.White, Font);
            }
            else if (_HipotResult.tr_OSC == TEST_RESULT.NG)
            {
                lvitem.SubItems.Add((_HipotResult.dbOSCData * 1000000000).ToString("0.00 nF"), Color.Black, Color.LightPink, Font);
            }
            else if (_HipotResult.tr_OSC == TEST_RESULT.PASS)
            {
                lvitem.SubItems.Add((_HipotResult.dbOSCData * 1000000000).ToString("0.00 nF"), Color.Black, Color.LightBlue, Font);
            }
            else
            {
                lvitem.SubItems.Add((_HipotResult.dbOSCData * 1000000000).ToString("0.00 nF"), Color.Black, Color.White, Font);
            }

            // 단자접촉성(-)
            if (_HipotResult.tr_NOSC == TEST_RESULT.OK)
            {
                lvitem.SubItems.Add((_HipotResult.dbNOSCData * 1000000000).ToString("0.00 nF"), Color.Black, Color.White, Font);
            }
            else if (_HipotResult.tr_NOSC == TEST_RESULT.NG)
            {
                lvitem.SubItems.Add((_HipotResult.dbNOSCData * 1000000000).ToString("0.00 nF"), Color.Black, Color.LightPink, Font);
            }
            else if (_HipotResult.tr_NOSC == TEST_RESULT.PASS)
            {
                lvitem.SubItems.Add((_HipotResult.dbNOSCData * 1000000000).ToString("0.00 nF"), Color.Black, Color.LightBlue, Font);
            }
            else
            {
                lvitem.SubItems.Add((_HipotResult.dbNOSCData * 1000000000).ToString("0.00 nF"), Color.Black, Color.White, Font);
            }



            // 접지연속성
            if (_HipotResult.tr_GB == TEST_RESULT.OK)
            {
                lvitem.SubItems.Add((_HipotResult.dbGBData * 1000).ToString("0.000 mΩ"), Color.Black, Color.White, Font);
            }
            else if (_HipotResult.tr_GB == TEST_RESULT.NG)
            {
                lvitem.SubItems.Add((_HipotResult.dbGBData * 1000).ToString("0.000 mΩ"), Color.Black, Color.LightPink, Font);
            }
            else if (_HipotResult.tr_GB == TEST_RESULT.PASS)
            {
                lvitem.SubItems.Add((_HipotResult.dbGBData * 1000).ToString("0.000 mΩ"), Color.Black, Color.LightBlue, Font);
            }
            else
            {
                lvitem.SubItems.Add((_HipotResult.dbGBData * 1000).ToString("0.000 mΩ"), Color.Black, Color.White, Font);
            }


            // 절연 저항 +
            if (_HipotResult.tr_IRP == TEST_RESULT.OK)
            {
                lvitem.SubItems.Add((_HipotResult.dbPIRData * 0.000001).ToString("0.00 MΩ"), Color.Black, Color.White, Font);
            }
            else if (_HipotResult.tr_IRP == TEST_RESULT.NG)
            {
                lvitem.SubItems.Add((_HipotResult.dbPIRData * 0.000001).ToString("0.00 MΩ"), Color.Black, Color.LightPink, Font);
            }
            else if (_HipotResult.tr_IRP == TEST_RESULT.PASS)
            {
                lvitem.SubItems.Add((_HipotResult.dbPIRData * 0.000001).ToString("0.00 MΩ"), Color.Black, Color.LightBlue, Font);
            }
            else
            {
                lvitem.SubItems.Add((_HipotResult.dbPIRData * 0.000001).ToString("0.00 MΩ"), Color.Black, Color.White, Font);
            }

            // 절연저항 -
            if (_HipotResult.tr_IRN == TEST_RESULT.OK)
            {
                lvitem.SubItems.Add((_HipotResult.dbNIRData * 0.000001).ToString("0.00 MΩ"), Color.Black, Color.White, Font);
            }
            else if (_HipotResult.tr_IRN == TEST_RESULT.NG)
            {
                lvitem.SubItems.Add((_HipotResult.dbNIRData * 0.000001).ToString("0.00 MΩ"), Color.Black, Color.LightPink, Font);
            }
            else if (_HipotResult.tr_IRN == TEST_RESULT.PASS)
            {
                lvitem.SubItems.Add((_HipotResult.dbNIRData * 0.000001).ToString("0.00 MΩ"), Color.Black, Color.LightBlue, Font);
            }
            else
            {
                lvitem.SubItems.Add((_HipotResult.dbNIRData * 0.000001).ToString("0.00 MΩ"), Color.Black, Color.White, Font);
            }


            // 하이팟 +
            if (_HipotResult.tr_HIP == TEST_RESULT.OK)
            {
                lvitem.SubItems.Add((_HipotResult.dbHipotPos * 1000).ToString("0.00 mA"), Color.Black, Color.White, Font);
            }
            else if (_HipotResult.tr_HIP == TEST_RESULT.NG)
            {
                lvitem.SubItems.Add((_HipotResult.dbHipotPos * 1000).ToString("0.00 mA"), Color.Black, Color.LightPink, Font);
            }
            else if (_HipotResult.tr_HIP == TEST_RESULT.PASS)
            {
                lvitem.SubItems.Add((_HipotResult.dbHipotPos * 1000).ToString("0.00 mA"), Color.Black, Color.LightBlue, Font);
            }
            else
            {
                lvitem.SubItems.Add((_HipotResult.dbHipotPos * 1000).ToString("0.00 mA"), Color.Black, Color.White, Font);
            }


            // 하이팟 -
            if (_HipotResult.tr_HIN == TEST_RESULT.OK)
            {
                lvitem.SubItems.Add((_HipotResult.dbHipotNeg * 1000).ToString("0.00 mA"), Color.Black, Color.White, Font);
            }
            else if (_HipotResult.tr_HIN == TEST_RESULT.NG)
            {
                lvitem.SubItems.Add((_HipotResult.dbHipotNeg * 1000).ToString("0.00 mA"), Color.Black, Color.LightPink, Font);
            }
            else if (_HipotResult.tr_HIN == TEST_RESULT.PASS)
            {
                lvitem.SubItems.Add((_HipotResult.dbHipotNeg * 1000).ToString("0.00 mA"), Color.Black, Color.LightBlue, Font);
            }
            else
            {
                lvitem.SubItems.Add((_HipotResult.dbHipotNeg * 1000).ToString("0.00 mA"), Color.Black, Color.White, Font);
            }

            // 메세지 출력
            

            lvitem.UseItemStyleForSubItems = false;
            listView2.Items.Add(lvitem);
            listView2.EnsureVisible(listView2.Items.Count - 1);


            // == 리스트뷰 업데이트 종료
            listView2.EndUpdate();


        }






        public void ViewLogMsg(string strMsg, LOG_TYPE type)
        {

            listView1.BeginUpdate();
            // == 리스트뷰 업데이트 시작 

            // 최대 100라인
            if (listView1.Items.Count > 100) listView1.Items.RemoveAt(0);

            // 시간 출력
            ListViewItem lvitem = new ListViewItem();
            lvitem.Text = System.DateTime.Now.ToString("[HH:mm:ss]");



            // 타입별 출력 변경
            if (type == LOG_TYPE.LOG)
            {
                lvitem.SubItems.Add("LOG", Color.Black, Color.White, Font);
            }
            else if (type == LOG_TYPE.ERROR)
            {
                lvitem.SubItems.Add("ERROR", Color.Black, Color.LightPink, Font);
            }
            else if (type == LOG_TYPE.INFO)
            {
                lvitem.SubItems.Add("INFO", Color.Black, Color.WhiteSmoke, Font);
            }

            // 메세지 출력
            lvitem.SubItems.Add(strMsg);

            lvitem.UseItemStyleForSubItems = false;
            listView1.Items.Add(lvitem);
            listView1.EnsureVisible(listView1.Items.Count - 1);

            listView1.Columns[0].Width = -2;
            listView1.Columns[1].Width = -2;
            listView1.Columns[2].Width = -2;

            // == 리스트뷰 업데이트 종료
            listView1.EndUpdate();


            // 로그 저장
            string strFolderPath = String.Format(@"LOG\\");

            DirectoryInfo dir = new DirectoryInfo(strFolderPath);
            if (dir.Exists == false) { dir.Create(); }

            string savePath = String.Format("{0}{1:D4}{2:D2}{3:D2}.txt", strFolderPath, DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
            System.IO.File.AppendAllText(savePath, lvitem.Text + "\t" + lvitem.SubItems[1].Text + "\t" + lvitem.SubItems[2].Text + "\r\n", Encoding.Default);
            ///

        }





        public void ViewCommMsg(String str, Color clr)
        {
            int maxline = 100; // 최대 라인수

            if (richTextBox1.GetLineFromCharIndex(richTextBox1.Text.Length - 1) + 1 >= maxline)
            {
                Int32 endmarker = richTextBox1.Text.IndexOf('\n') + 1;
                richTextBox1.Select(0, endmarker);
                richTextBox1.Cut();
            }
            String strMessge = System.DateTime.Now.ToString("[HH:mm:ss]") + " " + str + Environment.NewLine;

            richTextBox1.SelectionStart = richTextBox1.Text.Length;
            richTextBox1.SelectionLength = 0;
            richTextBox1.SelectionColor = clr;
            richTextBox1.AppendText(strMessge);
            richTextBox1.ScrollToCaret();

            string strFolderPath = String.Format(@"CommunicationLog\\");

            DirectoryInfo dir = new DirectoryInfo(strFolderPath);
            if (dir.Exists == false) { dir.Create(); }

            string savePath = String.Format("{0}{1:D4}{2:D2}{3:D2}.txt", strFolderPath, DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
            System.IO.File.AppendAllText(savePath, strMessge, Encoding.Default);
        }

        public void ViewOmronWHLog(string strBCD, string strResult, double dbWidth, double dbHight)
        {
            listView4.BeginUpdate();
            // == 리스트뷰 업데이트 시작 

            // 최대 100라인
            if (listView4.Items.Count > 100) listView4.Items.RemoveAt(0);

            // 시간 출력
            ListViewItem lvitem = new ListViewItem();

            lvitem.Text = System.DateTime.Now.ToString("HH:mm:ss");     // 시간

            lvitem.SubItems.Add(strBCD);                   // 바코드

            // 종합 결과
            if (strResult == "OK")
            {
                lvitem.SubItems.Add("O.K", Color.Black, Color.LightGreen, Font);
            }
            else
            {
                lvitem.SubItems.Add("N.G", Color.Black, Color.LightPink, Font);
            }

            // 전폭
            if (dbWidth > Program._ModelInfo.dbOmronWDTestSpecWidthMax || dbWidth < Program._ModelInfo.dbOmronWDTestSpecWidth)
            {
                lvitem.SubItems.Add(dbWidth.ToString("F3"), Color.Black, Color.LightPink, Font);
            }
            else
            {
                lvitem.SubItems.Add(dbWidth.ToString("F3"), Color.Black, Color.White, Font);
            }

            // 전장
            if (dbHight > Program._ModelInfo.dbOmronWDTestSpecHightMax || dbHight < Program._ModelInfo.dbOmronWDTestSpecHight)
            {
                lvitem.SubItems.Add(dbHight.ToString("F3"), Color.Black, Color.LightPink, Font);
            }
            else
            {
                lvitem.SubItems.Add(dbHight.ToString("F3"), Color.Black, Color.White, Font);
            }


            lvitem.UseItemStyleForSubItems = false;
            listView4.Items.Add(lvitem);
            listView4.EnsureVisible(listView4.Items.Count - 1);



            // == 리스트뷰 업데이트 종료
            listView4.EndUpdate();

        }

        private void MainForm_Load(object sender, EventArgs e)
        {
    
            Program.MainThread.Start();

            listView1.DoubleBuffered(true);
            listView2.DoubleBuffered(true);
            listView3.DoubleBuffered(true);
            UpdateBCDGridStyle();
            UpdateEOLTestLog("", TEST_RESULT.READY);
            timer1.Interval = 100;
            timer1.Start();
        }

        public void UpdateEOLResultData(string strBCD, TEST_RESULT _Result)
        {
            listView3.BeginUpdate();
            // == 리스트뷰 업데이트 시작 

            // 최대 100라인
            if (listView3.Items.Count > 100) listView3.Items.RemoveAt(0);

            // 시간 출력
            ListViewItem lvitem = new ListViewItem();


            lvitem.Text = System.DateTime.Now.ToString("HH:mm:ss");     // 시간

            lvitem.SubItems.Add(strBCD);                   // 바코드

            // 종합 결과
            if (_Result == TEST_RESULT.OK)
            {
                lvitem.SubItems.Add("O.K", Color.Black, Color.LightGreen, Font);
            }
            else
            {
                lvitem.SubItems.Add("N.G", Color.Black, Color.LightPink, Font);
            }

            lvitem.UseItemStyleForSubItems = false;
            listView3.Items.Add(lvitem);
            listView3.EnsureVisible(listView3.Items.Count - 1);


            // == 리스트뷰 업데이트 종료
            listView3.EndUpdate();
        }

        public void UpdateBCDGridStyle()
        {

            //dataGridView1.DataSource = Program._dtBCDInfo;


            dataGridView1.Rows.Clear();

            for (int i = 0; i < Program._ReadBCDList.Count; i++)
            {
                dataGridView1.Rows.Add(Program._ReadBCDList[i].strBCD, Program._ReadBCDList[i].strCate);
            }


            dataGridView1.Columns[0].Width = 300;
            dataGridView1.Columns[0].ReadOnly = true;
            dataGridView1.Columns[0].SortMode = DataGridViewColumnSortMode.NotSortable;
            dataGridView1.Columns[0].DefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;

            dataGridView1.Columns[1].Width = 100;
            dataGridView1.Columns[1].ReadOnly = true;
            dataGridView1.Columns[1].SortMode = DataGridViewColumnSortMode.NotSortable;
            dataGridView1.Columns[1].AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            dataGridView1.Columns[1].DefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;

        }

        public void UpdateBCDCount()
        {

            label77.Text = _SysInfo.nCmaCount.ToString() + " / " + Program._ModelInfo.nCmaCount.ToString();
            label78.Text = _SysInfo.nBmsCount.ToString() + " / " + Program._ModelInfo.nBmsCount.ToString();
            //label26.Text = _SysInfo.nFuseCount.ToString() + " / " + Program._ModelInfo.nFuseCount.ToString();

            if (_SysInfo.nCmaCount >= Program._ModelInfo.nCmaCount)
            {
                label77.BackColor = Color.LightGreen;
            }
            else
            {
                label77.BackColor = Color.LightPink;
            }

            if (_SysInfo.nBmsCount >= Program._ModelInfo.nBmsCount)
            {
                label78.BackColor = Color.LightGreen;
            }
            else
            {
                label78.BackColor = Color.LightPink;
            }

            //if (_SysInfo.nFuseCount >= Program._ModelInfo.nFuseCount)
            //{
            //    label26.BackColor = Color.LightGreen;
            //}
            //else
            //{
            //    label26.BackColor = Color.LightPink;
            //}
        }

        public void ViewLoadingStartInfo()
        {
            StartView _form = new StartView();
            DialogResult _resut = _form.ShowDialog();


            if (_resut == System.Windows.Forms.DialogResult.Yes)     // 처음부터 적재 시작
            {
                _SysInfo.nLoadingWorkIndex = 0;
                for (int i = 0; i < 14; i++)
                {
                    _SysInfo.bLoading_View_Ing[i] = false;
                    _SysInfo.bLoading_View_Complated[i] = false;
                }
                _SysInfo.bLoading_ing = false;
                _SysInfo.bLoadingComplated = false;
                _SysInfo.eLoadingInfoSetOk = START_INFO.OK;
            }
            else if (_resut == System.Windows.Forms.DialogResult.OK) // 적재 완료된 제품
            {
                for (int i = 0; i < 14; i++)
                {
                    _SysInfo.bLoading_View_Ing[i] = false;
                    _SysInfo.bLoading_View_Complated[i] = true;
                }
                _SysInfo.bLoading_ing = false;
                _SysInfo.bLoadingComplated = true;
                _SysInfo.eLoadingInfoSetOk = START_INFO.OK;

            }
            else if (_resut == System.Windows.Forms.DialogResult.No)  // 선택한 위치부터 적재 시작
            {

                _SysInfo.bLoading_ing = false;
                _SysInfo.bLoadingComplated = false;
                _SysInfo.eLoadingInfoSetOk = START_INFO.OK;
            }
            else
            {
                _SysInfo.eLoadingInfoSetOk = START_INFO.CANCEL;
            }

        }

        public void ViewVisionData(int nStation, string strBCD)
        {
            // 이미지 파일 저장
            string strSaveFolderPath = String.Format(@"E:\\DATA\\LABEL\\{0}\\{1}\\{2}\\", Program._ModelInfo.strModelName, Program._LotCount.tLotClearTime.ToString("yyMMdd"), strBCD);
            DirectoryInfo Savedir = new DirectoryInfo(strSaveFolderPath);
            if (Savedir.Exists == false) { Savedir.Create(); }

            if (nStation == 0)
            {
                pictureBox2.Refresh();

                FileStream fs = new FileStream(String.Format("{0}.bmp", _Config.strVisionDir1), FileMode.Open);

                pictureBox2.SizeMode = PictureBoxSizeMode.StretchImage;
                pictureBox2.Image = Image.FromStream(fs);

                fs.Close();

                File.Copy(_Config.strVisionDir1 + ".bmp", strSaveFolderPath + "1.BMP", true);
                File.Delete(_Config.strVisionDir1 + ".bmp");


            }
            else if (nStation == 1)
            {
                pictureBox3.Refresh();

                FileStream fs = new FileStream(String.Format("{0}.bmp", _Config.strVisionDir2), FileMode.Open);

                pictureBox3.SizeMode = PictureBoxSizeMode.StretchImage;
                pictureBox3.Image = Image.FromStream(fs);

                fs.Close();

                File.Copy(_Config.strVisionDir2 + ".bmp", strSaveFolderPath + "2.BMP", true);
                File.Delete(_Config.strVisionDir2 + ".bmp");
            }

        }

        public void ViewST3Resume(int nType)
        {
            RobotStartView _form = new RobotStartView(nType);
            _form.ShowDialog();
        }


        public void ViewTesterStartInfo(int nStation)
        {
            TesterStartView _form;
            DialogResult _result;

            if (nStation <= 4)
            {
                _form = new TesterStartView(false, Program._ModelInfo.bUseScanSTTester, nStation);
                _result = _form.ShowDialog();

                if (_result == System.Windows.Forms.DialogResult.Yes)     // 작업 시작시
                {
                    _SysInfo.eChargeStartInfo[nStation] = START_INFO.OK;
                }
                else
                {
                    _SysInfo.eChargeStartInfo[nStation] = START_INFO.CANCEL;
                }
            }
            else if (nStation == 5)
            {
                _form = new TesterStartView(true, Program._ModelInfo.bUseScanSTTester, nStation);
                _result = _form.ShowDialog();

                if (_result == System.Windows.Forms.DialogResult.Yes)     // 작업 시작시
                {
                    _SysInfo.eChargeStartInfo[nStation] = START_INFO.OK;
                }
                else
                {
                    _SysInfo.eChargeStartInfo[nStation] = START_INFO.CANCEL;
                }
            }
            else if (nStation == 6)
            {
                _form = new TesterStartView(true, Program._ModelInfo.bUseScanSTTester, nStation);
                _result = _form.ShowDialog();

                if (_result == System.Windows.Forms.DialogResult.Yes)     // 작업 시작시
                {
                    _SysInfo.eChargeStartInfo[nStation] = START_INFO.OK;
                }
                else
                {
                    _SysInfo.eChargeStartInfo[nStation] = START_INFO.CANCEL;
                }
            }
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (!_SysInfo.bMainProcessStop)
            {
                if (MessageBox.Show("프로그램을 종료하시겠습니까?", "프로그램 종료", MessageBoxButtons.YesNo) == DialogResult.No)
                {
                    e.Cancel = true;
                    return;
                }
                else
                {
                    _SysInfo.bMainProcessStop = true;
                    e.Cancel = true;
                    return;
                }
            }
        }

        private void simpleButton15_Click(object sender, EventArgs e)
        {
            this.Close();
        }



        private void simpleButton9_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("장비를 초기화 하시겠습니까？", "장비 초기화", MessageBoxButtons.YesNo) == DialogResult.No)
            {
                return;
            }


            Program.nProcessStep[(int)PROC_LIST.MAIN] = 100;
        }





        private void timer1_Tick(object sender, EventArgs e)
        {
            Label[] ContatcLb = { label35, label40, label49, label51, label90, label96 };

            for (int i = 0; i < 6; i++)
            {
                if (Program.bCounterConatct[i])
                {
                    ContatcLb[i].Text = "Online";
                    ContatcLb[i].BackColor = Color.LightGreen;
                }
                else
                {
                    ContatcLb[i].Text = "Offline";
                    ContatcLb[i].BackColor = Color.LightPink;
                }
            }
            UpdateBCDCount();

            label6.Text = _Config.nStation5PinMaxCount.ToString();
            label7.Text = _Config.nStation6PinMaxCount.ToString();
            label5.Text = Program._Count.nStation5PinCount.ToString();
            label8.Text = Program._Count.nStation6PinCount.ToString();

            //모댈명
            label3.Text = Program._ModelInfo.strModelName;

         
        
            //시간
            label33.Text = DateTime.Now.ToLocalTime().ToLongTimeString();
            label34.Text = DateTime.Now.ToLocalTime().ToLongDateString();

            //생산정보
            label27.Text = Program._LotCount.nLotCount.ToString();
            label36.Text = Program._LotCount.nProductCount.ToString();
            label47.Text = Program._LotCount.tLotClearTime.ToLongTimeString() + "\r\n" + Program._LotCount.tLotClearTime.ToLongDateString();
            label31.Text = Program._LotCount.tProductClearTime.ToLongTimeString() + "\r\n" + Program._LotCount.tProductClearTime.ToLongDateString();
            label45.Text = Program._Count.nTotalCount.ToString();



    
            label89.BackColor = _SysInfo.bStationAutoMode[(int)STATION_LIST.IN_LIFT] ? Color.LightGreen : Color.FromArgb(255, 220, 150);
            label63.BackColor = _SysInfo.bStationAutoMode[(int)STATION_LIST.LOADING] ? Color.LightGreen : Color.FromArgb(255, 220, 150);
            label66.BackColor = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST1] ? Color.LightGreen : Color.FromArgb(255, 220, 150);
            label79.BackColor = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST2] ? Color.LightGreen : Color.FromArgb(255, 220, 150);
            label74.BackColor = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST3] ? Color.LightGreen : Color.FromArgb(255, 220, 150);
            label83.BackColor = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST4] ? Color.LightGreen : Color.FromArgb(255, 220, 150);
            label95.BackColor = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST5] ? Color.LightGreen : Color.FromArgb(255, 220, 150);

            label81.BackColor = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST6] ? Color.LightGreen : Color.FromArgb(255, 220, 150);
            label87.BackColor = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7] ? Color.LightGreen : Color.FromArgb(255, 220, 150);
            label85.BackColor = _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING] ? Color.LightGreen : Color.FromArgb(255, 220, 150);


            label89.Text = _SysInfo.bStationAutoMode[(int)STATION_LIST.IN_LIFT] ? "Auto" : "Manual";
            label63.Text = _SysInfo.bStationAutoMode[(int)STATION_LIST.LOADING] ? "Auto" : "Manual";
            label66.Text = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST1] ? "Auto" : "Manual";
            label79.Text = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST2] ? "Auto" : "Manual";
            label74.Text = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST3] ? "Auto" : "Manual";
            label83.Text = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST4] ? "Auto" : "Manual";
            label95.Text = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST5] ? "Auto" : "Manual";

            label81.Text = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST6] ? "Auto" : "Manual";
            label87.Text = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7] ? "Auto" : "Manual";
            label85.Text = _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING] ? "Auto" : "Manual";



            AutoButtonStyle();


            //label94.Text = Program._tHipotTimer.Elapsed.ToString("mm':'ss':'ff");

            label98.Text = Program._tSTCycleTimer[(int)STATION_LIST.LOADING].Elapsed.ToString("mm':'ss':'ff");

            label97.Text = Program._tSTCycleTimer[(int)STATION_LIST.IN_LIFT].Elapsed.ToString("mm':'ss':'ff");

            label101.Text = Program._tSTCycleTimer[(int)STATION_LIST.ST1].Elapsed.ToString("mm':'ss':'ff");
            label100.Text = Program._tSTCycleTimer[(int)STATION_LIST.ST2].Elapsed.ToString("mm':'ss':'ff");
            label99.Text = Program._tSTCycleTimer[(int)STATION_LIST.ST3].Elapsed.ToString("mm':'ss':'ff");
            label106.Text = Program._tSTCycleTimer[(int)STATION_LIST.ST4].Elapsed.ToString("mm':'ss':'ff");
            label92.Text = Program._tSTCycleTimer[(int)STATION_LIST.ST5].Elapsed.ToString("mm':'ss':'ff");
            label103.Text = Program._tSTCycleTimer[(int)STATION_LIST.ST6].Elapsed.ToString("mm':'ss':'ff");
            label108.Text = Program._tSTCycleTimer[(int)STATION_LIST.ST7].Elapsed.ToString("mm':'ss':'ff");


            label107.Text = Program._tSTCycleTimer[(int)STATION_LIST.UNLOADING].Elapsed.ToString("mm':'ss':'ff");



            label20.Text = (Program._HipotResult.dbOSCData * 1000000000).ToString("0.00 nF");
            label21.Text = (Program._HipotResult.dbNOSCData * 1000000000).ToString("0.00 nF");
            label57.Text = (Program._HipotResult.dbGBData * 1000).ToString("0.000 mΩ");
            label38.Text = (Program._HipotResult.dbHipotNeg * 1000).ToString("0.00 mA");
            label42.Text = (Program._HipotResult.dbHipotPos * 1000).ToString("0.00 mA");

            label25.Text = (Program._HipotResult.dbPIRData * 0.000001).ToString("0.00 MΩ");
            label24.Text = (Program._HipotResult.dbNIRData * 0.000001).ToString("0.00 MΩ");



            TEST_RESULT[] tr_Result = { Program._HipotResult.tr_OSC, Program._HipotResult.tr_GB, Program._HipotResult.tr_HIN, Program._HipotResult.tr_HIP, 
                                          Program._HipotResult.tr_IRP,Program._HipotResult.tr_IRN,Program._HipotResult.tr_NOSC };


            Label[] lb = { label20, label57, label38, label42, label25, label24, label21 };

            for (int i = 0; i < 7; i++)
            {
                if (tr_Result[i] == TEST_RESULT.OK)
                {
                    lb[i].BackColor = Color.LightGreen;

                }
                else if (tr_Result[i] == TEST_RESULT.NG)
                {
                    lb[i].BackColor = Color.LightPink;

                }
                else if (tr_Result[i] == TEST_RESULT.PASS)
                {
                    lb[i].BackColor = Color.LightBlue;
                    lb[i].Text = "PASS";
                }
                else if (tr_Result[i] == TEST_RESULT.READY)
                {
                    lb[i].BackColor = Color.Gray;

                }
                else if (tr_Result[i] == TEST_RESULT.ING)
                {
                    lb[i].BackColor = Color.LightYellow;

                }
            }


            label61.Text = Program._HipotResult.strBCD;

            //label60.Text = Program._nutEth.nCurrentStep.ToString();
            if (Program._HipotResult.tr_TOTAL == TEST_RESULT.READY)
            {
                label60.BackColor = Color.Ivory;
                label60.Text = "READY";
            }
            else if (Program._HipotResult.tr_TOTAL == TEST_RESULT.OK)
            {
                label60.BackColor = Color.LightGreen;
                label60.Text = "O.K";
            }
            else if (Program._HipotResult.tr_TOTAL == TEST_RESULT.NG)
            {
                label60.BackColor = Color.LightPink;
                label60.Text = "N.G";
            }


            if (_Config.strLangue == "KOR")
            {
                label30.Text = "[OSC]단자접촉성(+)";
                label93.Text = "[OSC]단자접촉성(-)";
                label58.Text = "[GB]접지연속성";
                label32.Text = "[IR]절연저항(+)";
                label26.Text = "[IR]절연저항(-)";
                label48.Text = "[HIPOT]내전압(+)";
                label43.Text = "[HIPOT]내전압(-)";
                label56.Text = "상부 라벨 검사";
                label17.Text = "전면 라벨 검사";
            }
            else if (_Config.strLangue == "CHINA")
            {
                label30.Text = "[OSC]端子接触性(+)";
                label93.Text = "[OSC]端子接触性(-)";
                label58.Text = "[GB]接地延续性";
                label32.Text = "[IR]绝缘电阻(+)";
                label26.Text = "[IR]绝缘电阻(-)";
                label48.Text = "[HIPOT]耐电压(+)";
                label43.Text = "[HIPOT]耐电压(-)";
                label56.Text = "顶部标签检查";
                label17.Text = "正面标签检查";
            }


            MainStatusMonitor();
        }




        public void UpdateEOLTestLog(string strBCD, TEST_RESULT _Result)
        {

            label69.Text = strBCD;

            if (_Result == TEST_RESULT.READY)
            {
                label55.BackColor = Color.Ivory;
                label55.Text = "READY";
            }
            else if (_Result == TEST_RESULT.OK)
            {
                label55.BackColor = Color.LightGreen;
                label55.Text = "O.K";
            }
            else if (_Result == TEST_RESULT.NG)
            {
                label55.BackColor = Color.LightPink;
                label55.Text = "N.G";
            }

        }
        // 자동 수동 버튼 설정
        public void AutoButtonStyle()
        {
            if (_SysInfo.Main_Status == MAIN_STATUS.SYSTEM_ERR || _SysInfo.Main_Status == MAIN_STATUS.NO_INIT || _SysInfo.Main_Status == MAIN_STATUS.INIT)
            {
                simpleButton23.Enabled = false;
                simpleButton25.Enabled = false;
                simpleButton27.Enabled = false;
                simpleButton29.Enabled = false;
                simpleButton31.Enabled = false;
                simpleButton33.Enabled = false;
                simpleButton20.Enabled = false;
                simpleButton37.Enabled = false;
                simpleButton39.Enabled = false;
                simpleButton41.Enabled = false;
            }
            else
            {
                simpleButton23.Enabled = true;
                simpleButton25.Enabled = true;
                simpleButton27.Enabled = true;
                simpleButton29.Enabled = true;
                simpleButton31.Enabled = true;
                simpleButton33.Enabled = true;
                simpleButton20.Enabled = true;
                simpleButton37.Enabled = true;
                simpleButton39.Enabled = true;
                simpleButton41.Enabled = true;
            }


            simpleButton23.Image = _SysInfo.bStationAutoMode[(int)STATION_LIST.IN_LIFT] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton25.Image = _SysInfo.bStationAutoMode[(int)STATION_LIST.LOADING] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton27.Image = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST1] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton29.Image = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST2] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton31.Image = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST3] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton33.Image = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST4] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton20.Image = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST5] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton37.Image = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST6] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton39.Image = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton41.Image = _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;

            simpleButton22.Image = !_SysInfo.bStationAutoMode[(int)STATION_LIST.IN_LIFT] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton24.Image = !_SysInfo.bStationAutoMode[(int)STATION_LIST.LOADING] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton26.Image = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST1] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton28.Image = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST2] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton30.Image = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST3] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton32.Image = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST4] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton19.Image = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST5] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;

            simpleButton36.Image = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST6] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton38.Image = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST7] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton40.Image = !_SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;


        }

        private void simpleButton1_Click(object sender, EventArgs e)
        {
            
            if (MessageBox.Show("생산 수량을 초기화 하시겠습니까?", "생산 수량 초기화", MessageBoxButtons.YesNo) == DialogResult.No)
            {
                return;
            }

            Program._LotCount.nProductCount = 0;
            Program._LotCount.tProductClearTime = DateTime.Now;
            Program.SaveModelProductCount(Program._ModelInfo.strModelName);
        }

        private void simpleButton4_Click(object sender, EventArgs e)
        {
            //Program.OutputLogMsg(OutPutMessage.MASTER_PC_NG);
            _SysInfo.TL_Buzzer = TOWER_LAMP.TL_OFF;
        }


        public void DSViewFormOpen()
        {
            Program._hipotDsForm = new HipotDSSWAlarm();
            Program._hipotDsForm.ShowDialog();

        }


        public void DSViewClose()
        {
            Program._hipotDsForm.Close();
        }


        private void simpleButton11_Click(object sender, EventArgs e)
        {
            TitePass _forms = new TitePass(0);
            if (_forms.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                _SysInfo.bCountUnlock[0] = true;
                _SysInfo.bUpCountUnlock[0] = false;
            }
        }

        private void simpleButton12_Click(object sender, EventArgs e)
        {
            TitePass _forms = new TitePass(0);
            if (_forms.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                _SysInfo.bCountUnlock[1] = true;
                _SysInfo.bUpCountUnlock[1] = false;
            }
        }

        private void simpleButton13_Click(object sender, EventArgs e)
        {
            TitePass _forms = new TitePass(0);
            if (_forms.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                _SysInfo.bCountUnlock[2] = true;
                _SysInfo.bUpCountUnlock[2] = false;
            }
        }

        private void simpleButton14_Click(object sender, EventArgs e)
        {
            TitePass _forms = new TitePass(0);
            if (_forms.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                _SysInfo.bCountUnlock[3] = true;
                _SysInfo.bUpCountUnlock[3] = false;
            }
        }

        private void simpleButton10_Click(object sender, EventArgs e)
        {
            if (_Config.bUseAdminPass)
            {
                AdminPass _forms = new AdminPass();
                if (_forms.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    ConfigSetup _form = new ConfigSetup();
                    _form.ShowDialog();
                }
            }
            else
            {
                ConfigSetup _form = new ConfigSetup();
                _form.ShowDialog();
            }
                
        }





        // 메인상태 모니터링
        private void MainStatusMonitor()
        {
            switch (_SysInfo.Main_Status)
            {
                case MAIN_STATUS.NO_INIT:
                    label71.Text = "시스템 초기화 필요";
                    label71.ForeColor = Color.LightPink;
                    Program.TowerLampBlink(LAMP_COLOR.TL_YELLOW);
                    simpleButton7.Enabled = false;
                    simpleButton6.Enabled = false;
                    simpleButton9.Enabled = true;
                    simpleButton5.Enabled = true;
                    simpleButton8.Enabled = true;                   // tlt
                    break;

                case MAIN_STATUS.RUNNING:
                    label71.Text = "전체 자동 운전중";
                    label71.ForeColor = Color.LightGreen;
                    Program.TowerLampOn(LAMP_COLOR.TL_GREEN);
                    simpleButton7.Enabled = false;
                    simpleButton6.Enabled = true;
                    simpleButton9.Enabled = false;
                    simpleButton5.Enabled = false;
                    simpleButton8.Enabled = false;
                    break;

                case MAIN_STATUS.INIT:
                    label71.Text = "시스템 초기화 중";
                    label71.ForeColor = Color.LightYellow;
                    Program.TowerLampOn(LAMP_COLOR.TL_YELLOW);
                    simpleButton7.Enabled = false;
                    simpleButton6.Enabled = false;
                    simpleButton9.Enabled = false;
                    simpleButton5.Enabled = true;
                    simpleButton8.Enabled = true;
                    break;

                case MAIN_STATUS.STOP:
                    label71.Text = "전체 정지됨";
                    label71.ForeColor = Color.LightPink;
                    Program.TowerLampBlink(LAMP_COLOR.TL_GREEN);
                    simpleButton7.Enabled = true;
                    simpleButton6.Enabled = false;
                    simpleButton9.Enabled = true;
                    simpleButton5.Enabled = true;
                    simpleButton8.Enabled = true;
                    break;

                case MAIN_STATUS.SYSTEM_ERR:
                    label71.Text = "시스템 에러";
                    label71.ForeColor = Color.LightPink;
                    Program.TowerLampBlink(LAMP_COLOR.TL_RED);
                    simpleButton7.Enabled = false;
                    simpleButton6.Enabled = false;
                    simpleButton9.Enabled = true;
                    simpleButton5.Enabled = true;
                    simpleButton8.Enabled = true;
                    break;

                case MAIN_STATUS.ALARM:
                    label71.Text = "알람 상태";
                    label71.ForeColor = Color.LightPink;
                    Program.TowerLampBlink(LAMP_COLOR.TL_RED);
                    simpleButton7.Enabled = false;
                    simpleButton6.Enabled = false;
                    simpleButton9.Enabled = true;
                    simpleButton5.Enabled = true;
                    simpleButton8.Enabled = true;
                    break;

                case MAIN_STATUS.READY:
                    label71.Text = "시스템 정상";
                    label71.ForeColor = Color.LightGreen;
                    Program.TowerLampBlink(LAMP_COLOR.TL_GREEN);

                    //simpleButton7.Enabled = true;
                    simpleButton6.Enabled = true;
                    simpleButton5.Enabled = true;
                    simpleButton8.Enabled = true;


                    if (_SysInfo.TL_Buzzer == TOWER_LAMP.TL_ON)
                    {
                        _SysInfo.TL_Yellow = TOWER_LAMP.TL_BLINK;
                    }
                    else
                    {
                        _SysInfo.TL_Yellow = TOWER_LAMP.TL_OFF;
                    }



                    if (_SysInfo.bStationAutoMode[(int)STATION_LIST.LOADING] &&
                        _SysInfo.bStationAutoMode[(int)STATION_LIST.IN_LIFT] &&
                        _SysInfo.bStationAutoMode[(int)STATION_LIST.ST1] &&
                        _SysInfo.bStationAutoMode[(int)STATION_LIST.ST2] &&
                        _SysInfo.bStationAutoMode[(int)STATION_LIST.ST3] &&
                        _SysInfo.bStationAutoMode[(int)STATION_LIST.ST4] &&
                        _SysInfo.bStationAutoMode[(int)STATION_LIST.ST5] &&
                        _SysInfo.bStationAutoMode[(int)STATION_LIST.ST6] &&
                        _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7] &&
                        _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING])
                    {
                        label71.Text = "전체 자동운전중";
                        label71.ForeColor = Color.LightGreen;
                        _SysInfo.TL_Green = TOWER_LAMP.TL_ON;
                        simpleButton7.Enabled = false;
                    }
                    else
                    {
                        label71.Text = "시스템 정상";
                        label71.ForeColor = Color.LightGreen;
                        _SysInfo.TL_Green = TOWER_LAMP.TL_BLINK;
                        simpleButton7.Enabled = true;
                    }




                    break;

            }
        }

        private void simpleButton23_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.IN_LIFT] = true;
        }

        private void simpleButton22_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.IN_LIFT] = false;
        }

        private void simpleButton25_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.LOADING] = true;
        }

        private void simpleButton24_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.LOADING] = false;
        }

        private void simpleButton27_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST1] = true;
        }

        private void simpleButton26_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST1] = false;
        }

        private void simpleButton29_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST2] = true;
        }

        private void simpleButton28_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST2] = false;
        }

        private void simpleButton31_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST3] = true;
        }

        private void simpleButton30_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST3] = false;
        }

        private void simpleButton33_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST4] = true;
        }

        private void simpleButton32_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST4] = false;
        }

        private void simpleButton37_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST6] = true;
        }

        private void simpleButton36_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST6] = false;
        }

        private void simpleButton39_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7] = true;
        }

        private void simpleButton38_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7] = false;
        }

        private void simpleButton41_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING] = true;
        }

        private void simpleButton40_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING] = false;
        }

        private void simpleButton2_Click(object sender, EventArgs e)
        {
            if (_Config.bUseAdminPass)
            {
                AdminPass _forms = new AdminPass();
                if (_forms.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    // 비밀번호가 일치할 경우
                    Program._Count.nStation5PinCount = 0;
                    Program.SaveProductCount();
                }
            }
            else
            {
                Program._Count.nStation5PinCount = 0;
                Program.SaveProductCount();
            }
        }

        private void simpleButton16_Click(object sender, EventArgs e)
        {
            try
            {
                if (dataGridView1.CurrentRow.Index < 0) return;

                AdminPass _form = new AdminPass();
                if (_form.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    Program._ReadBCDList.RemoveAt(dataGridView1.CurrentRow.Index);
                    UpdateBCDGridStyle();
                    Program.SaveBCDListInfo();
                    //Program._dtBCDInfo.Rows.RemoveAt(dataGridView1.CurrentRow.Index);
                }
            }
            catch { }
        }

        private void simpleButton42_Click(object sender, EventArgs e)
        {
            try
            {
                if (dataGridView1.CurrentRow.Index < 0) return;

                AdminPass _form = new AdminPass();
                if (_form.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    Program._ReadBCDList.Clear();
                    UpdateBCDGridStyle();
                    Program.SaveBCDListInfo();
                    //Program._dtBCDInfo.Rows.RemoveAt(dataGridView1.CurrentRow.Index);
                }
            }
            catch { }
        }

        private void simpleButton7_Click(object sender, EventArgs e)
        {
            for (int i = (int)STATION_LIST.LOADING; i <= (int)STATION_LIST.UNLOADING; i++)
            {
                _SysInfo.bStationAutoMode[i] = true;
            }
            Program.SaveIniFile();
        }

        private void simpleButton6_Click(object sender, EventArgs e)
        {
            for (int i = (int)STATION_LIST.LOADING; i <= (int)STATION_LIST.UNLOADING; i++)
            {
                _SysInfo.bStationAutoMode[i] = false;
            }
        }

        private void simpleButton5_Click(object sender, EventArgs e)
        {

            ModelList _form = new ModelList();
            if (_form.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                _SysInfo.bModelChangeFirstLoading = true;
            }
        }

        private void simpleButton17_Click(object sender, EventArgs e)
        {
            BCDManualPrint _form = new BCDManualPrint();
            _form.ShowDialog();
        }

        private void simpleButton18_Click(object sender, EventArgs e)
        {
            TitePass _forms = new TitePass(0);
            if (_forms.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                _SysInfo.bCountUnlock[4] = true;
                _SysInfo.bUpCountUnlock[4] = false;
            }
        }

        private void simpleButton20_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST5] = true;
        }

        private void simpleButton19_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST5] = false;
        }

        private void simpleButton21_Click(object sender, EventArgs e)
        {
            TitePass _forms = new TitePass(0);
            if (_forms.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                _SysInfo.bCountUnlock[5] = true;
                _SysInfo.bUpCountUnlock[5] = false;
            }
        }

        // LOT 더블클릭시
        private void label27_DoubleClick(object sender, EventArgs e)
        {
            AdminPass _forms = new AdminPass();
            if (_forms.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                LotCountForm _lotform = new LotCountForm();
                _lotform.ShowDialog();
            }
        }

        private void simpleButton46_Click(object sender, EventArgs e)
        {
            TitePass _forms = new TitePass(2);
            if (_forms.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                _SysInfo.bCountUnlock[0] = false;
                _SysInfo.bUpCountUnlock[0] = true;
                Program.AppendLogMsg("Station #1 Up Button UnLocked", LOG_TYPE.INFO);
            }
        }

        private void simpleButton45_Click(object sender, EventArgs e)
        {
            TitePass _forms = new TitePass(2);
            if (_forms.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                _SysInfo.bCountUnlock[1] = false;
                _SysInfo.bUpCountUnlock[1] = true;
                Program.AppendLogMsg("Station #2 Up Button UnLocked", LOG_TYPE.INFO);
            }
        }

        private void simpleButton44_Click(object sender, EventArgs e)
        {
            TitePass _forms = new TitePass(2);
            if (_forms.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                _SysInfo.bCountUnlock[2] = false;
                _SysInfo.bUpCountUnlock[2] = true;
                Program.AppendLogMsg("Station #3 Up Button UnLocked", LOG_TYPE.INFO);
            }
        }

        private void simpleButton43_Click(object sender, EventArgs e)
        {
            TitePass _forms = new TitePass(2);
            if (_forms.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                _SysInfo.bCountUnlock[3] = false;
                _SysInfo.bUpCountUnlock[3] = true;
                Program.AppendLogMsg("Station #4 Up Button UnLocked", LOG_TYPE.INFO);
            }
        }

        private void simpleButton35_Click(object sender, EventArgs e)
        {
            TitePass _forms = new TitePass(2);
            if (_forms.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                _SysInfo.bCountUnlock[4] = false;
                _SysInfo.bUpCountUnlock[4] = true;
                Program.AppendLogMsg("Station #5 Up Button UnLocked", LOG_TYPE.INFO);
            }
        }

        private void simpleButton34_Click(object sender, EventArgs e)
        {
            TitePass _forms = new TitePass(2);
            if (_forms.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                _SysInfo.bCountUnlock[5] = false;
                _SysInfo.bUpCountUnlock[5] = true;
                Program.AppendLogMsg("Station #Lift Up Button UnLocked", LOG_TYPE.INFO);
            }
        }

        private void simpleButton3_Click(object sender, EventArgs e)
        {
            if (_Config.bUseAdminPass)
            {
                AdminPass _forms = new AdminPass();
                if (_forms.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    Program._Count.nStation6PinCount = 0;
                    Program.SaveProductCount();
                }
            }
            else
            {
                Program._Count.nStation5PinCount = 0;
                Program.SaveProductCount();
            }
        }
    }
}
