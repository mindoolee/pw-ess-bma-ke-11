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

namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
    public partial class ModelSetup : Form
    {
        public static MODEL_INFO _ModelInfo = new MODEL_INFO();

        public string strAuto = "";
        public string strManual = "";

        public ModelSetup(MODEL_INFO _mInfo)
        {
            InitializeComponent();

            _ModelInfo = _mInfo.CopyJsons<MODEL_INFO>();


            DevExpress.XtraEditors.SimpleButton[] Jog_bt = { Jog_Y1, Jog_Y2, Jog_X1, Jog_X2, Jog_Z1, Jog_Z2, 
                                                               HIPOTX1_1, HIPOTX1_2, HIPOTY1_1, HIPOTY1_2, HIPOTZ1_1, HIPOTZ1_2, 
                                                               HIPOTX2_1, HIPOTX2_2, HIPOTY2_1, HIPOTY2_2, HIPOTZ2_1, HIPOTZ2_2,
                                                               EOLX_1, EOLX_2, EOLY_1, EOLY_2 , EOLZ_1, EOLZ_2 , Jog_R1, Jog_R2,
                                                               CAMERA1_X1, CAMERA1_X2, CAMERA1_Y1, CAMERA1_Y2, CAMERA1_Z1, CAMERA1_Z2,
                                                               CAMERA2_X1, CAMERA2_X2, CAMERA2_Y1, CAMERA2_Y2, CAMERA2_Z1, CAMERA2_Z2};

            for (int i = 0; i < Jog_bt.Count(); i++)
            {
                Jog_bt[i].MouseDown += new MouseEventHandler(this.Jog_Bt_Down);
                Jog_bt[i].MouseUp += new MouseEventHandler(this.Jog_Bt_Up);
            }

            
        }



        public void ViewTiteArmInfo()
        {
            checkBox1.Checked = _ModelInfo.bUseST2Encoder;
            textBox1.Text = _ModelInfo.nST2EncoderRange.ToString();

            dataGridView28.Rows.Clear();
            try
            {
                for (int i = 0; i < _ModelInfo._ST2Tip.Count; i++)
                {
                    dataGridView28.Rows.Add(i + 1, _ModelInfo._ST2Tip[i].nX.ToString(), _ModelInfo._ST2Tip[i].nY.ToString(), _ModelInfo._ST2Tip[i].nTip, (dataGridView28.Columns[4] as DataGridViewComboBoxColumn).Items[_ModelInfo._ST2Tip[i].nSch]);
                }
            }
            catch (Exception e) 
            {
                MessageBox.Show(e.Message);
                _ModelInfo._ST2Tip = new List<ST2_TIP_INFO>(); 
            }
        }


        public void LoadTiteInfo()
        {
            _ModelInfo.bUseST2Encoder = checkBox1.Checked;
            int.TryParse(textBox1.Text, out _ModelInfo.nST2EncoderRange);
            
            int nX = 0;
            int nY = 0;
            int nTip = 0;
            int nSch = 0;
            try
            {
                _ModelInfo._ST2Tip.Clear();
            }
            catch 
            {
                _ModelInfo._ST2Tip = new List<ST2_TIP_INFO>(); 
            }
            for (int i = 0; i < dataGridView28.Rows.Count; i++)
            {
                int.TryParse(dataGridView28.Rows[i].Cells[1].Value.ToString(), out nX);
                int.TryParse(dataGridView28.Rows[i].Cells[2].Value.ToString(), out nY);
                int.TryParse(dataGridView28.Rows[i].Cells[3].Value.ToString(), out nTip);
                nSch = (dataGridView28.Rows[i].Cells[4] as DataGridViewComboBoxCell).Items.IndexOf(dataGridView28.Rows[i].Cells[4].Value);
                _ModelInfo._ST2Tip.Add(new ST2_TIP_INFO() { nX = nX, nY = nY, nTip = nTip, nSch = nSch });
                
            }

        }

        void ViewETCData()
        {
            ViewTiteArmInfo();
            // 해당 항목이 null 일경우 재할당
            if (_ModelInfo._EtcDataScan == null)
            {
                _ModelInfo._EtcDataScan = new ETC_SCAN_SET[5];
                for (int i = 0; i < _ModelInfo._EtcDataScan.Length; i++)
                {
                    _ModelInfo._EtcDataScan[i] = new ETC_SCAN_SET();
                }
            }

            //dataGridView18.Rows.Clear();
            //for (int i = 0; i < _ModelInfo._EtcDataScan[2]._List.Count; i++)
            //{
            //    dataGridView18.Rows.Add(_ModelInfo._EtcDataScan[2]._List[i].strScanName, _ModelInfo._EtcDataScan[2]._List[i].strScanSymbol, _ModelInfo._EtcDataScan[2]._List[i].nMaxCount.ToString());
            //}

            dataGridView24.Rows.Clear();
            for (int i = 0; i < _ModelInfo._EtcDataScan[1]._List.Count; i++)
            {
                dataGridView24.Rows.Add(_ModelInfo._EtcDataScan[1]._List[i].strScanName, _ModelInfo._EtcDataScan[1]._List[i].strScanSymbol, _ModelInfo._EtcDataScan[1]._List[i].nMaxCount.ToString());
            }

            dataGridView23.Rows.Clear();
            for (int i = 0; i < _ModelInfo._EtcDataScan[0]._List.Count; i++)
            {
                dataGridView23.Rows.Add(_ModelInfo._EtcDataScan[0]._List[i].strScanName, _ModelInfo._EtcDataScan[0]._List[i].strScanSymbol, _ModelInfo._EtcDataScan[0]._List[i].nMaxCount.ToString());
            }

            dataGridView25.Rows.Clear();
            for (int i = 0; i < _ModelInfo._EtcDataScan[2]._List.Count; i++)
            {
                dataGridView25.Rows.Add(_ModelInfo._EtcDataScan[2]._List[i].strScanName, _ModelInfo._EtcDataScan[2]._List[i].strScanSymbol, _ModelInfo._EtcDataScan[2]._List[i].nMaxCount.ToString());
            }

            dataGridView16.Rows.Clear();
            for (int i = 0; i < _ModelInfo._ListEppScan.Count; i++)
            {
                dataGridView16.Rows.Add(_ModelInfo._ListEppScan[i].strScanName, _ModelInfo._ListEppScan[i].strScanSymbol);
            }


        }

        void LoadETCData()
        {
            LoadTiteInfo();
            //_ModelInfo._EtcDataScan[2]._List.Clear();
            //for (int i = 0; i < dataGridView18.RowCount; i++)
            //{
            //    _ModelInfo._EtcDataScan[2]._List.Add(new ETC_SCAN_LIST() { strScanName = dataGridView18[0, i].Value.ToString(), strScanSymbol = dataGridView18[1, i].Value.ToString(), nMaxCount = int.Parse(dataGridView18[2, i].Value.ToString()) });
            //}

            _ModelInfo._EtcDataScan[1]._List.Clear();
            for (int i = 0; i < dataGridView24.RowCount; i++)
            {
                _ModelInfo._EtcDataScan[1]._List.Add(new ETC_SCAN_LIST() { strScanName = dataGridView24[0, i].Value.ToString(), strScanSymbol = dataGridView24[1, i].Value.ToString(), nMaxCount = int.Parse(dataGridView24[2, i].Value.ToString()) });
            }

            _ModelInfo._EtcDataScan[0]._List.Clear();
            for (int i = 0; i < dataGridView23.RowCount; i++)
            {
                _ModelInfo._EtcDataScan[0]._List.Add(new ETC_SCAN_LIST() { strScanName = dataGridView23[0, i].Value.ToString(), strScanSymbol = dataGridView23[1, i].Value.ToString(), nMaxCount = int.Parse(dataGridView23[2, i].Value.ToString()) });
            }

            _ModelInfo._EtcDataScan[2]._List.Clear();
            for (int i = 0; i < dataGridView25.RowCount; i++)
            {
                _ModelInfo._EtcDataScan[2]._List.Add(new ETC_SCAN_LIST() { strScanName = dataGridView25[0, i].Value.ToString(), strScanSymbol = dataGridView25[1, i].Value.ToString(), nMaxCount = int.Parse(dataGridView25[2, i].Value.ToString()) });
            }

            _ModelInfo._ListEppScan.Clear();
            for (int i = 0; i < dataGridView16.RowCount; i++)
            {
                _ModelInfo._ListEppScan.Add(new ETC_SCAN_LIST() { strScanName = dataGridView16[0, i].Value.ToString(), strScanSymbol = dataGridView16[1, i].Value.ToString() });
            }


        }






        // 체결존 정보 보여주기
        public void ViewLockingSTInfo()
        {
   
            dataGridView5.Rows.Clear();
            dataGridView6.Rows.Clear();
            dataGridView7.Rows.Clear();
            dataGridView8.Rows.Clear();
            dataGridView13.Rows.Clear();
            dataGridView15.Rows.Clear();


            dataGridView17.Rows.Clear();
            dataGridView18.Rows.Clear();
            dataGridView19.Rows.Clear();
            dataGridView20.Rows.Clear();
            dataGridView21.Rows.Clear();
            dataGridView22.Rows.Clear();

            (dataGridView5.Columns[2] as DataGridViewComboBoxColumn).Items.Clear();
            (dataGridView6.Columns[2] as DataGridViewComboBoxColumn).Items.Clear();
            (dataGridView7.Columns[2] as DataGridViewComboBoxColumn).Items.Clear();
            (dataGridView8.Columns[2] as DataGridViewComboBoxColumn).Items.Clear();
            (dataGridView13.Columns[2] as DataGridViewComboBoxColumn).Items.Clear();
            (dataGridView15.Columns[2] as DataGridViewComboBoxColumn).Items.Clear();


            (dataGridView17.Columns[3] as DataGridViewComboBoxColumn).Items.Clear();
            (dataGridView18.Columns[3] as DataGridViewComboBoxColumn).Items.Clear();
            (dataGridView19.Columns[3] as DataGridViewComboBoxColumn).Items.Clear();
            (dataGridView20.Columns[3] as DataGridViewComboBoxColumn).Items.Clear();
            (dataGridView21.Columns[3] as DataGridViewComboBoxColumn).Items.Clear();
            (dataGridView22.Columns[3] as DataGridViewComboBoxColumn).Items.Clear();
            for (int i = 0; i < _Config._TipName.Count; i++)
            {
                (dataGridView5.Columns[2] as DataGridViewComboBoxColumn).Items.Add(_Config._TipName[i]);
                (dataGridView6.Columns[2] as DataGridViewComboBoxColumn).Items.Add(_Config._TipName[i]);
                (dataGridView7.Columns[2] as DataGridViewComboBoxColumn).Items.Add(_Config._TipName[i]);
                (dataGridView8.Columns[2] as DataGridViewComboBoxColumn).Items.Add(_Config._TipName[i]);
                (dataGridView13.Columns[2] as DataGridViewComboBoxColumn).Items.Add(_Config._TipName[i]);
                (dataGridView15.Columns[2] as DataGridViewComboBoxColumn).Items.Add(_Config._TipName[i]);

                (dataGridView17.Columns[3] as DataGridViewComboBoxColumn).Items.Add(_Config._TipName[i]);
                (dataGridView18.Columns[3] as DataGridViewComboBoxColumn).Items.Add(_Config._TipName[i]);
                (dataGridView19.Columns[3] as DataGridViewComboBoxColumn).Items.Add(_Config._TipName[i]);
                (dataGridView20.Columns[3] as DataGridViewComboBoxColumn).Items.Add(_Config._TipName[i]);
                (dataGridView21.Columns[3] as DataGridViewComboBoxColumn).Items.Add(_Config._TipName[i]);
                (dataGridView22.Columns[3] as DataGridViewComboBoxColumn).Items.Add(_Config._TipName[i]);
                (dataGridView28.Columns[4] as DataGridViewComboBoxColumn).Items.Add(_Config._TipName[i]);
            }
            for(int i= 0; i < 5; i++)
            {
                dataGridView5.Rows.Add(String.Format("Tip #{0}", i + 1), _ModelInfo._TipInfo[0].nTipMaxCount[i], (dataGridView5.Columns[2] as DataGridViewComboBoxColumn).Items[_ModelInfo._TipInfo[0].nTipSch[i]]);
                dataGridView6.Rows.Add(String.Format("Tip #{0}", i + 1), _ModelInfo._TipInfo[1].nTipMaxCount[i], (dataGridView6.Columns[2] as DataGridViewComboBoxColumn).Items[_ModelInfo._TipInfo[1].nTipSch[i]]);
                dataGridView7.Rows.Add(String.Format("Tip #{0}", i + 1), _ModelInfo._TipInfo[2].nTipMaxCount[i], (dataGridView7.Columns[2] as DataGridViewComboBoxColumn).Items[_ModelInfo._TipInfo[2].nTipSch[i]]);
                dataGridView8.Rows.Add(String.Format("Tip #{0}", i + 1), _ModelInfo._TipInfo[3].nTipMaxCount[i], (dataGridView8.Columns[2] as DataGridViewComboBoxColumn).Items[_ModelInfo._TipInfo[3].nTipSch[i]]);
                dataGridView13.Rows.Add(String.Format("Tip #{0}", i + 1), _ModelInfo._TipInfo[5].nTipMaxCount[i], (dataGridView13.Columns[2] as DataGridViewComboBoxColumn).Items[_ModelInfo._TipInfo[5].nTipSch[i]]);
                dataGridView15.Rows.Add(String.Format("Tip #{0}", i + 1), _ModelInfo._TipInfo[4].nTipMaxCount[i], (dataGridView15.Columns[2] as DataGridViewComboBoxColumn).Items[_ModelInfo._TipInfo[4].nTipSch[i]]);


                dataGridView17.Rows.Add(_ModelInfo._TipInfo[0].nSpare_a[i] > 0 ? true : false, String.Format("Tip #{0}", i + 1), _ModelInfo._TipInfo[0].nTipMaxCount[i + 5], (dataGridView5.Columns[2] as DataGridViewComboBoxColumn).Items[_ModelInfo._TipInfo[0].nTipSch[i + 5]]);
                dataGridView18.Rows.Add(_ModelInfo._TipInfo[1].nSpare_a[i] > 0 ? true : false, String.Format("Tip #{0}", i + 1), _ModelInfo._TipInfo[1].nTipMaxCount[i + 5], (dataGridView6.Columns[2] as DataGridViewComboBoxColumn).Items[_ModelInfo._TipInfo[1].nTipSch[i + 5]]);
                dataGridView19.Rows.Add(_ModelInfo._TipInfo[2].nSpare_a[i] > 0 ? true : false, String.Format("Tip #{0}", i + 1), _ModelInfo._TipInfo[2].nTipMaxCount[i + 5], (dataGridView7.Columns[2] as DataGridViewComboBoxColumn).Items[_ModelInfo._TipInfo[2].nTipSch[i + 5]]);
                dataGridView20.Rows.Add(_ModelInfo._TipInfo[3].nSpare_a[i] > 0 ? true : false, String.Format("Tip #{0}", i + 1), _ModelInfo._TipInfo[3].nTipMaxCount[i + 5], (dataGridView8.Columns[2] as DataGridViewComboBoxColumn).Items[_ModelInfo._TipInfo[3].nTipSch[i + 5]]);
                dataGridView21.Rows.Add(_ModelInfo._TipInfo[4].nSpare_a[i] > 0 ? true : false, String.Format("Tip #{0}", i + 1), _ModelInfo._TipInfo[4].nTipMaxCount[i + 5], (dataGridView13.Columns[2] as DataGridViewComboBoxColumn).Items[_ModelInfo._TipInfo[4].nTipSch[i + 5]]);
                dataGridView22.Rows.Add(_ModelInfo._TipInfo[5].nSpare_a[i] > 0 ? true : false, String.Format("Tip #{0}", i + 1), _ModelInfo._TipInfo[5].nTipMaxCount[i + 5], (dataGridView15.Columns[2] as DataGridViewComboBoxColumn).Items[_ModelInfo._TipInfo[5].nTipSch[i + 5]]);

                dataGridView5[0, i].ReadOnly = true;
                dataGridView5[0, i].Style.BackColor = Color.FromArgb(255, 255, 230);

                dataGridView6[0, i].ReadOnly = true;
                dataGridView6[0, i].Style.BackColor = Color.FromArgb(255, 255, 230);

                dataGridView7[0, i].ReadOnly = true;
                dataGridView7[0, i].Style.BackColor = Color.FromArgb(255, 255, 230);

                dataGridView8[0, i].ReadOnly = true;
                dataGridView8[0, i].Style.BackColor = Color.FromArgb(255, 255, 230);


                dataGridView13[0, i].ReadOnly = true;
                dataGridView13[0, i].Style.BackColor = Color.FromArgb(255, 255, 230);


                dataGridView15[0, i].ReadOnly = true;
                dataGridView15[0, i].Style.BackColor = Color.FromArgb(255, 255, 230);


                ViewETCData();

                ///


                //dataGridView17
                //dataGridView18
                //dataGridView19
                //dataGridView20
                //dataGridView21
                //dataGridView22

                dataGridView17[1, i].ReadOnly = true;
                dataGridView17[1, i].Style.BackColor = Color.FromArgb(255, 255, 230);
                               
                dataGridView18[1, i].ReadOnly = true;
                dataGridView18[1, i].Style.BackColor = Color.FromArgb(255, 255, 230);
                               
                dataGridView19[1, i].ReadOnly = true;
                dataGridView19[1, i].Style.BackColor = Color.FromArgb(255, 255, 230);
                               
                dataGridView20[1, i].ReadOnly = true;
                dataGridView20[1, i].Style.BackColor = Color.FromArgb(255, 255, 230);
                               
                               
                dataGridView21[1, i].ReadOnly = true;
                dataGridView21[1, i].Style.BackColor = Color.FromArgb(255, 255, 230);
                               
                               
                dataGridView22[1, i].ReadOnly = true;
                dataGridView22[1, i].Style.BackColor = Color.FromArgb(255, 255, 230);



            }

           
          
        }

        // 체결존 정보 읽기
        public void SaveLocingSTInfo()
        {
            dataGridView5.EndEdit();
            dataGridView6.EndEdit();
            dataGridView7.EndEdit();
            dataGridView8.EndEdit();
            dataGridView13.EndEdit();
            dataGridView15.EndEdit();


            dataGridView17.EndEdit();
            dataGridView18.EndEdit();
            dataGridView19.EndEdit();
            dataGridView20.EndEdit();
            dataGridView21.EndEdit();
            dataGridView22.EndEdit();

            LoadETCData();

            for (int i = 0; i < 5; i++)
            {
                int.TryParse(dataGridView5.Rows[i].Cells[1].Value.ToString(), out _ModelInfo._TipInfo[0].nTipMaxCount[i]);
                _ModelInfo._TipInfo[0].nTipSch[i] = (dataGridView5.Rows[i].Cells[2] as DataGridViewComboBoxCell).Items.IndexOf(dataGridView5.Rows[i].Cells[2].Value);


                int.TryParse(dataGridView6.Rows[i].Cells[1].Value.ToString(), out _ModelInfo._TipInfo[1].nTipMaxCount[i]);
                _ModelInfo._TipInfo[1].nTipSch[i] = (dataGridView6.Rows[i].Cells[2] as DataGridViewComboBoxCell).Items.IndexOf(dataGridView6.Rows[i].Cells[2].Value);

                int.TryParse(dataGridView7.Rows[i].Cells[1].Value.ToString(), out _ModelInfo._TipInfo[2].nTipMaxCount[i]);
                _ModelInfo._TipInfo[2].nTipSch[i] = (dataGridView7.Rows[i].Cells[2] as DataGridViewComboBoxCell).Items.IndexOf(dataGridView7.Rows[i].Cells[2].Value);

                int.TryParse(dataGridView8.Rows[i].Cells[1].Value.ToString(), out _ModelInfo._TipInfo[3].nTipMaxCount[i]);
                _ModelInfo._TipInfo[3].nTipSch[i] = (dataGridView8.Rows[i].Cells[2] as DataGridViewComboBoxCell).Items.IndexOf(dataGridView8.Rows[i].Cells[2].Value);

                int.TryParse(dataGridView13.Rows[i].Cells[1].Value.ToString(), out _ModelInfo._TipInfo[5].nTipMaxCount[i]);
                _ModelInfo._TipInfo[5].nTipSch[i] = (dataGridView13.Rows[i].Cells[2] as DataGridViewComboBoxCell).Items.IndexOf(dataGridView13.Rows[i].Cells[2].Value);

                int.TryParse(dataGridView15.Rows[i].Cells[1].Value.ToString(), out _ModelInfo._TipInfo[4].nTipMaxCount[i]);
                _ModelInfo._TipInfo[4].nTipSch[i] = (dataGridView15.Rows[i].Cells[2] as DataGridViewComboBoxCell).Items.IndexOf(dataGridView15.Rows[i].Cells[2].Value);




                _ModelInfo._TipInfo[0].nSpare_a[i] = bool.Parse(dataGridView17.Rows[i].Cells[0].Value.ToString()) ? 1 : 0;
                int.TryParse(dataGridView17.Rows[i].Cells[2].Value.ToString(), out _ModelInfo._TipInfo[0].nTipMaxCount[i + 5]);
                _ModelInfo._TipInfo[0].nTipSch[i + 5] = (dataGridView17.Rows[i].Cells[3] as DataGridViewComboBoxCell).Items.IndexOf(dataGridView17.Rows[i].Cells[3].Value);

                _ModelInfo._TipInfo[1].nSpare_a[i] = bool.Parse(dataGridView18.Rows[i].Cells[0].Value.ToString()) ? 1 : 0;
                int.TryParse(dataGridView18.Rows[i].Cells[2].Value.ToString(), out _ModelInfo._TipInfo[1].nTipMaxCount[i + 5]);
                _ModelInfo._TipInfo[1].nTipSch[i + 5] = (dataGridView18.Rows[i].Cells[3] as DataGridViewComboBoxCell).Items.IndexOf(dataGridView18.Rows[i].Cells[3].Value);

                _ModelInfo._TipInfo[2].nSpare_a[i] = bool.Parse(dataGridView19.Rows[i].Cells[0].Value.ToString()) ? 1 : 0;
                int.TryParse(dataGridView19.Rows[i].Cells[2].Value.ToString(), out _ModelInfo._TipInfo[2].nTipMaxCount[i + 5]);
                _ModelInfo._TipInfo[2].nTipSch[i + 5] = (dataGridView19.Rows[i].Cells[3] as DataGridViewComboBoxCell).Items.IndexOf(dataGridView19.Rows[i].Cells[3].Value);

                _ModelInfo._TipInfo[3].nSpare_a[i] = bool.Parse(dataGridView20.Rows[i].Cells[0].Value.ToString()) ? 1 : 0;
                int.TryParse(dataGridView20.Rows[i].Cells[2].Value.ToString(), out _ModelInfo._TipInfo[3].nTipMaxCount[i + 5]);
                _ModelInfo._TipInfo[3].nTipSch[i + 5] = (dataGridView20.Rows[i].Cells[3] as DataGridViewComboBoxCell).Items.IndexOf(dataGridView20.Rows[i].Cells[3].Value);

                _ModelInfo._TipInfo[4].nSpare_a[i] = bool.Parse(dataGridView21.Rows[i].Cells[0].Value.ToString()) ? 1 : 0;
                int.TryParse(dataGridView21.Rows[i].Cells[2].Value.ToString(), out _ModelInfo._TipInfo[4].nTipMaxCount[i + 5]);
                _ModelInfo._TipInfo[4].nTipSch[i + 5] = (dataGridView21.Rows[i].Cells[3] as DataGridViewComboBoxCell).Items.IndexOf(dataGridView21.Rows[i].Cells[3].Value);

                _ModelInfo._TipInfo[5].nSpare_a[i] = bool.Parse(dataGridView22.Rows[i].Cells[0].Value.ToString()) ? 1 : 0;
                int.TryParse(dataGridView22.Rows[i].Cells[2].Value.ToString(), out _ModelInfo._TipInfo[5].nTipMaxCount[i + 5]);
                _ModelInfo._TipInfo[5].nTipSch[i + 5] = (dataGridView22.Rows[i].Cells[3] as DataGridViewComboBoxCell).Items.IndexOf(dataGridView22.Rows[i].Cells[3].Value);

            }




        }


        // 로딩포인트 정보 보여주기
        public void LoadingInfoView()
        {
            comboBox5.SelectedIndex = _ModelInfo.nSpare[0];
            comboBox6.SelectedIndex = _ModelInfo.nSpare[1];
            comboBox7.SelectedIndex = _ModelInfo.nSpare[2];
            comboBox8.SelectedIndex = _ModelInfo.nSpare[3];

            dataGridView1.Rows.Clear();
            dataGridView1.Rows.Add("LOAD", true, _ModelInfo.dbPackLoadingPointX, _ModelInfo.dbPackLoadingPointY, _ModelInfo.dbPackLoadingPointZ, "0");
            dataGridView1.Rows.Add("TURN", true, _ModelInfo.dbTurnPosX, _ModelInfo.dbTurnPosY, 0, "0");
            dataGridView1.Rows.Add("PC Sheet", true, _ModelInfo.dbLoadingJigTestPos1X, _ModelInfo.dbLoadingJigTestPos1Y, _ModelInfo.dbLoadingJigTestPos1Z, "0");
            //dataGridView1.Rows.Add("JIG2", true, _ModelInfo.dbLoadingJigTestPos2X, _ModelInfo.dbLoadingJigTestPos2Y, _ModelInfo.dbLoadingJigTestPos2Z, "0");

            for (int i = 0; i < 20; i++)
            {
                string strAngle = "";

                if (_ModelInfo._Loading[i].nType == 0) strAngle = "0";
                else if (_ModelInfo._Loading[i].nType == 1) strAngle = "90";
                else if (_ModelInfo._Loading[i].nType == 2) strAngle = "180";
                else if (_ModelInfo._Loading[i].nType == 3) strAngle = "-90";

                bool bRev = _ModelInfo._Loading[i].nSpare_a[0] > 0 ? true : false;

                dataGridView1.Rows.Add(String.Format("P{0:D2}", i + 1), _ModelInfo._Loading[i].bUse, _ModelInfo._Loading[i].dbX, _ModelInfo._Loading[i].dbY, _ModelInfo._Loading[i].dbZ,
                    strAngle, _ModelInfo._Loading[i].dbS, _ModelInfo._Loading[i].dbSpare_b[1], _ModelInfo._Loading[i].dbSpare_b[0], bRev);
            }


            dataGridView1[0, 0].ReadOnly = true;
            dataGridView1[0, 0].Style.BackColor = Color.FromArgb(240,240,250);

            dataGridView1[1, 0].ReadOnly = true;
            dataGridView1[1, 0].Style.BackColor = Color.FromArgb(240, 240, 250);

            dataGridView1[5, 0].ReadOnly = true;
            dataGridView1[5, 0].Style.BackColor = Color.DimGray;
            dataGridView1[6, 0].ReadOnly = true;
            dataGridView1[6, 0].Style.BackColor = Color.DimGray;
            dataGridView1[7, 0].ReadOnly = true;
            dataGridView1[7, 0].Style.BackColor = Color.DimGray;
            dataGridView1[8, 0].ReadOnly = true;
            dataGridView1[8, 0].Style.BackColor = Color.DimGray;

            dataGridView1[0, 1].ReadOnly = true;
            dataGridView1[0, 1].Style.BackColor = Color.FromArgb(240,250,240);
            dataGridView1[1, 1].ReadOnly = true;
            dataGridView1[1, 1].Style.BackColor = Color.FromArgb(240, 250, 240);

            dataGridView1[5, 1].ReadOnly = true;
            dataGridView1[5, 1].Style.BackColor = Color.DimGray;
            dataGridView1[6, 1].ReadOnly = true;
            dataGridView1[6, 1].Style.BackColor = Color.DimGray;
            dataGridView1[7, 1].ReadOnly = true;
            dataGridView1[7, 1].Style.BackColor = Color.DimGray;
            dataGridView1[8, 1].ReadOnly = true;
            dataGridView1[8, 1].Style.BackColor = Color.DimGray;


            dataGridView1[0, 2].ReadOnly = true;
            dataGridView1[0, 2].Style.BackColor = Color.FromArgb(255, 255, 230);
            dataGridView1[1, 2].ReadOnly = true;
            dataGridView1[1, 2].Style.BackColor = Color.FromArgb(255, 255, 230);

            dataGridView1[5, 2].ReadOnly = true;
            dataGridView1[5, 2].Style.BackColor = Color.DimGray;
            dataGridView1[6, 2].ReadOnly = true;
            dataGridView1[6, 2].Style.BackColor = Color.DimGray;
            dataGridView1[7, 2].ReadOnly = true;
            dataGridView1[7, 2].Style.BackColor = Color.DimGray;
            dataGridView1[8, 2].ReadOnly = true;
            dataGridView1[8, 2].Style.BackColor = Color.DimGray;

            //dataGridView1[0, 3].ReadOnly = true;
            //dataGridView1[0, 3].Style.BackColor = Color.FromArgb(255, 255, 230);
            //dataGridView1[1, 3].ReadOnly = true;
            //dataGridView1[1, 3].Style.BackColor = Color.FromArgb(255, 255, 230);

            //dataGridView1[5, 3].ReadOnly = true;
            //dataGridView1[5, 3].Style.BackColor = Color.DimGray;
            //dataGridView1[6, 3].ReadOnly = true;
            //dataGridView1[6, 3].Style.BackColor = Color.DimGray;
            //dataGridView1[7, 3].ReadOnly = true;
            //dataGridView1[7, 3].Style.BackColor = Color.DimGray;
            //dataGridView1[8, 3].ReadOnly = true;
            //dataGridView1[8, 3].Style.BackColor = Color.DimGray;

            for(int i =0; i  < 20; i++)
            {
                dataGridView1[0, i + 3].ReadOnly = true;
                dataGridView1[0, i + 3].Style.BackColor = Color.FromArgb(240, 240, 250);
                dataGridView1[1, i + 3].Style.BackColor = Color.FromArgb(240, 240, 250);
            }
        }

        // 로딩 포인트 정보 읽어오기
        public void LoadingInfoLoad()
        {
            _ModelInfo.nSpare[0] = comboBox5.SelectedIndex;
            _ModelInfo.nSpare[1] = comboBox6.SelectedIndex;
            _ModelInfo.nSpare[2] = comboBox7.SelectedIndex;
            _ModelInfo.nSpare[3] = comboBox8.SelectedIndex;

            dataGridView1.EndEdit();
            double.TryParse(dataGridView1[2, 0].Value.ToString(), out _ModelInfo.dbPackLoadingPointX);
            double.TryParse(dataGridView1[3, 0].Value.ToString(), out _ModelInfo.dbPackLoadingPointY);
            double.TryParse(dataGridView1[4, 0].Value.ToString(), out _ModelInfo.dbPackLoadingPointZ);

            double.TryParse(dataGridView1[2, 1].Value.ToString(), out _ModelInfo.dbTurnPosX);
            double.TryParse(dataGridView1[3, 1].Value.ToString(), out _ModelInfo.dbTurnPosY);

            double.TryParse(dataGridView1[2, 2].Value.ToString(), out _ModelInfo.dbLoadingJigTestPos1X);
            double.TryParse(dataGridView1[3, 2].Value.ToString(), out _ModelInfo.dbLoadingJigTestPos1Y);
            double.TryParse(dataGridView1[4, 2].Value.ToString(), out _ModelInfo.dbLoadingJigTestPos1Z);

            //double.TryParse(dataGridView1[2, 3].Value.ToString(), out _ModelInfo.dbLoadingJigTestPos2X);
            //double.TryParse(dataGridView1[3, 3].Value.ToString(), out _ModelInfo.dbLoadingJigTestPos2Y);
            //double.TryParse(dataGridView1[4, 3].Value.ToString(), out _ModelInfo.dbLoadingJigTestPos2Z);
            for (int i = 0; i < 20; i++)
            {
                bool.TryParse(dataGridView1[1, i + 3].Value.ToString(), out _ModelInfo._Loading[i].bUse);
                double.TryParse(dataGridView1[2, i + 3].Value.ToString(), out _ModelInfo._Loading[i].dbX);
                double.TryParse(dataGridView1[3, i + 3].Value.ToString(), out _ModelInfo._Loading[i].dbY);
                double.TryParse(dataGridView1[4, i + 3].Value.ToString(), out _ModelInfo._Loading[i].dbZ);

                if (dataGridView1[5, i + 3].Value.ToString() == "0") _ModelInfo._Loading[i].nType = 0;
                if (dataGridView1[5, i + 3].Value.ToString() == "90") _ModelInfo._Loading[i].nType = 1;
                if (dataGridView1[5, i + 3].Value.ToString() == "180") _ModelInfo._Loading[i].nType = 2;
                if (dataGridView1[5, i + 3].Value.ToString() == "-90") _ModelInfo._Loading[i].nType = 3;

                double.TryParse(dataGridView1[6, i + 3].Value.ToString(), out _ModelInfo._Loading[i].dbS);
                double.TryParse(dataGridView1[7, i + 3].Value.ToString(), out _ModelInfo._Loading[i].dbSpare_b[1]);
                double.TryParse(dataGridView1[8, i + 3].Value.ToString(), out _ModelInfo._Loading[i].dbSpare_b[0]);

                //bool bRev = false;
                //bool.TryParse(dataGridView1[9, i + 4].Value.ToString(), out bRev);

                //_ModelInfo._Loading[i].nSpare_a[0] = bRev ? 1 : 0;
            }



        }


        // 하이팟 정보
        public void HipotInfoView()
        {
            OmronDataView();
            dataGridView11.Rows.Clear();

            dataGridView11.Rows.Add(_ModelInfo.bPassNOSCTest, "(-) OSC", _ModelInfo.dbNOSCgetCS, "", _ModelInfo.dbNOSCSpecOpen, _ModelInfo.dbNOSCSpecShort);
            dataGridView11.Rows.Add(_ModelInfo.bPassOSCTest, "(+) OSC", _ModelInfo.dbOSCgetCS, "", _ModelInfo.dbOSCSpecOpen, _ModelInfo.dbOSCSpecShort);
            dataGridView11.Rows.Add(_ModelInfo.bPassNIRTest, "(-) IR", _ModelInfo.dbNIRInput, _ModelInfo.dbNIRTestTime, _ModelInfo.dbNIRLowLimit, "OFF");
            dataGridView11.Rows.Add(_ModelInfo.bPassPIRTest, "(+) IR", _ModelInfo.dbPIRInput, _ModelInfo.dbPIRTestTime, _ModelInfo.dbPIRLowLimit, "OFF");
            dataGridView11.Rows.Add(_ModelInfo.bPassGBTest, "GB", _ModelInfo.dbGBInput, _ModelInfo.dbGBTestTime, "OFF", _ModelInfo.dbGBHighLimit);
            dataGridView11.Rows.Add(_ModelInfo.bPassNHIPOTTest, "(-) HIPOT", _ModelInfo.dbNHIPOTInput, _ModelInfo.dbNHIPOTTestTime, "OFF", _ModelInfo.dbNHIPOTLowLimit);
            dataGridView11.Rows.Add(_ModelInfo.bPassPHIPOTTest, "(+) HIPOT", _ModelInfo.dbPHIPOTInput, _ModelInfo.dbPHIPOTTestTime, "OFF", _ModelInfo.dbPHIPOTLowLimit);


            for (int i = 0; i < 7; i++)
            {

                dataGridView11[0, i].Style.BackColor = Color.FromArgb(255, 255, 230);
                dataGridView11[1, i].ReadOnly = true;
                dataGridView11[1, i].Style.BackColor = Color.FromArgb(255, 255, 230);
            }


            dataGridView11[3, 0].ReadOnly = true;
            dataGridView11[3, 0].Style.BackColor = Color.DimGray;

            dataGridView11[3, 1].ReadOnly = true;
            dataGridView11[3, 1].Style.BackColor = Color.DimGray;

            dataGridView11[4, 4].ReadOnly = true;
            dataGridView11[4, 4].Style.BackColor = Color.DimGray;

            dataGridView11[5, 2].ReadOnly = true;
            dataGridView11[5, 2].Style.BackColor = Color.DimGray;

            dataGridView11[5, 3].ReadOnly = true;
            dataGridView11[5, 3].Style.BackColor = Color.DimGray;

            dataGridView11[4, 5].ReadOnly = true;
            dataGridView11[4, 5].Style.BackColor = Color.DimGray;

            dataGridView11[4, 6].ReadOnly = true;
            dataGridView11[4, 6].Style.BackColor = Color.DimGray;



        }


        public void HipotInfoLoad()
        {
            OmronDataLoad();
            dataGridView11.EndEdit();


            bool.TryParse(dataGridView11[0, 0].Value.ToString(), out _ModelInfo.bPassNOSCTest);
            double.TryParse(dataGridView11[2, 0].Value.ToString(), out _ModelInfo.dbNOSCgetCS);
            double.TryParse(dataGridView11[4, 0].Value.ToString(), out _ModelInfo.dbNOSCSpecOpen);
            double.TryParse(dataGridView11[5, 0].Value.ToString(), out _ModelInfo.dbNOSCSpecShort);

            bool.TryParse(dataGridView11[0, 1].Value.ToString(), out _ModelInfo.bPassOSCTest);
            double.TryParse(dataGridView11[2, 1].Value.ToString(), out _ModelInfo.dbOSCgetCS);
            double.TryParse(dataGridView11[4, 1].Value.ToString(), out _ModelInfo.dbOSCSpecOpen);
            double.TryParse(dataGridView11[5, 1].Value.ToString(), out _ModelInfo.dbOSCSpecShort);


            bool.TryParse(dataGridView11[0, 2].Value.ToString(), out _ModelInfo.bPassNIRTest);
            double.TryParse(dataGridView11[2, 2].Value.ToString(), out _ModelInfo.dbNIRInput);
            double.TryParse(dataGridView11[3, 2].Value.ToString(), out _ModelInfo.dbNIRTestTime);
            double.TryParse(dataGridView11[4, 2].Value.ToString(), out _ModelInfo.dbNIRLowLimit);

            bool.TryParse(dataGridView11[0, 3].Value.ToString(), out _ModelInfo.bPassPIRTest);
            double.TryParse(dataGridView11[2, 3].Value.ToString(), out _ModelInfo.dbPIRInput);
            double.TryParse(dataGridView11[3, 3].Value.ToString(), out _ModelInfo.dbPIRTestTime);
            double.TryParse(dataGridView11[4, 3].Value.ToString(), out _ModelInfo.dbPIRLowLimit);

            bool.TryParse(dataGridView11[0, 4].Value.ToString(), out _ModelInfo.bPassGBTest);
            double.TryParse(dataGridView11[2, 4].Value.ToString(), out _ModelInfo.dbGBInput);
            double.TryParse(dataGridView11[3, 4].Value.ToString(), out _ModelInfo.dbGBTestTime);
            double.TryParse(dataGridView11[5, 4].Value.ToString(), out _ModelInfo.dbGBHighLimit);

            // 
            bool.TryParse(dataGridView11[0, 5].Value.ToString(), out _ModelInfo.bPassNHIPOTTest);
            double.TryParse(dataGridView11[2, 5].Value.ToString(), out _ModelInfo.dbNHIPOTInput);
            double.TryParse(dataGridView11[3, 5].Value.ToString(), out _ModelInfo.dbNHIPOTTestTime);
            double.TryParse(dataGridView11[5, 5].Value.ToString(), out _ModelInfo.dbNHIPOTLowLimit);

            //
            bool.TryParse(dataGridView11[0, 6].Value.ToString(), out _ModelInfo.bPassPHIPOTTest);
            double.TryParse(dataGridView11[2, 6].Value.ToString(), out _ModelInfo.dbPHIPOTInput);
            double.TryParse(dataGridView11[3, 6].Value.ToString(), out _ModelInfo.dbPHIPOTTestTime);
            double.TryParse(dataGridView11[5, 6].Value.ToString(), out _ModelInfo.dbPHIPOTLowLimit);
        }



        // 검사 포인트 정보
        public void PointInfoView()
        {
            string strLabel = "";

            dataGridView3.Rows.Clear();

            if (_Config.strLangue == "KOR") strLabel = "대기위치";
            else if (_Config.strLangue == "CHINA") strLabel = "待机位置";

            dataGridView3.Rows.Add(strLabel, _ModelInfo._TestInfo[0].dbReadyPos1X.ToString("F2"),
                _ModelInfo._TestInfo[0].dbReadyPos1Y.ToString("F2"),
                 _ModelInfo._TestInfo[0].dbReadyPos1Z.ToString("F2"),
                  _ModelInfo._TestInfo[0].dbReadyPos2X.ToString("F2"),
                   _ModelInfo._TestInfo[0].dbReadyPos2Y.ToString("F2"),
                    _ModelInfo._TestInfo[0].dbReadyPos2Z.ToString("F2"));

            if (_Config.strLangue == "KOR") strLabel = "검사위치";
            else if (_Config.strLangue == "CHINA") strLabel = "联系位置";

            dataGridView3.Rows.Add(strLabel, _ModelInfo._TestInfo[0].dbContactPos1X.ToString("F2"),
               _ModelInfo._TestInfo[0].dbContactPos1Y.ToString("F2"),
                _ModelInfo._TestInfo[0].dbContactPos1Z.ToString("F2"),
                 _ModelInfo._TestInfo[0].dbContactPos2X.ToString("F2"),
                  _ModelInfo._TestInfo[0].dbContactPos2Y.ToString("F2"),
                   _ModelInfo._TestInfo[0].dbContactPos2Z.ToString("F2"));

            if (_Config.strLangue == "KOR") strLabel = "바코드 스캔 위치";
            else if (_Config.strLangue == "CHINA") strLabel = "条码扫描位置";

            dataGridView3.Rows.Add(strLabel, "", "", "", _ModelInfo._TestInfo[0].dbSpare_b[0].ToString("F2"),
                         _ModelInfo._TestInfo[0].dbSpare_b[1].ToString("F2"),
                          _ModelInfo._TestInfo[0].dbSpare_b[2].ToString("F2"));

            if (_Config.strLangue == "KOR") strLabel = "상부 라벨검사 위치";
            else if (_Config.strLangue == "CHINA") strLabel = "顶部标签检查位置";
            dataGridView3.Rows.Add(strLabel, "", "", "", _ModelInfo._TestInfo[0].dbSpare_b[3].ToString("F2"),
                        _ModelInfo._TestInfo[0].dbSpare_b[4].ToString("F2"),
                         _ModelInfo._TestInfo[0].dbSpare_b[5].ToString("F2"));

            if (_Config.strLangue == "KOR") strLabel = "전면 라벨검사 위치";
            else if (_Config.strLangue == "CHINA") strLabel = "正面标签检查位置";
            dataGridView3.Rows.Add(strLabel, "", "", "", _ModelInfo._TestInfo[0].dbSpare_b[6].ToString("F2"),
                       _ModelInfo._TestInfo[0].dbSpare_b[7].ToString("F2"),
                        _ModelInfo._TestInfo[0].dbSpare_b[8].ToString("F2"));



            for (int i = 0; i < 5; i++)
            {
                dataGridView3[0, i].ReadOnly = true;
                dataGridView3[0, i].Style.BackColor = Color.FromArgb(255, 255, 230);
            }

            dataGridView3[1, 2].ReadOnly = true;
            dataGridView3[1, 2].Style.BackColor = Color.DimGray;

            dataGridView3[2, 2].ReadOnly = true;
            dataGridView3[2, 2].Style.BackColor = Color.DimGray;

            dataGridView3[3, 2].ReadOnly = true;
            dataGridView3[3, 2].Style.BackColor = Color.DimGray;



            dataGridView3[1, 3].ReadOnly = true;
            dataGridView3[1, 3].Style.BackColor = Color.DimGray;
                             
            dataGridView3[2, 3].ReadOnly = true;
            dataGridView3[2, 3].Style.BackColor = Color.DimGray;
                             
            dataGridView3[3, 3].ReadOnly = true;
            dataGridView3[3, 3].Style.BackColor = Color.DimGray;


            dataGridView3[1, 4].ReadOnly = true;
            dataGridView3[1, 4].Style.BackColor = Color.DimGray;
                             
            dataGridView3[2, 4].ReadOnly = true;
            dataGridView3[2, 4].Style.BackColor = Color.DimGray;
                             
            dataGridView3[3, 4].ReadOnly = true;
            dataGridView3[3, 4].Style.BackColor = Color.DimGray;



            dataGridView4.Rows.Clear();
            if (_Config.strLangue == "KOR") strLabel = "대기위치";
            else if (_Config.strLangue == "CHINA") strLabel = "待机位置";
            dataGridView4.Rows.Add(strLabel, _ModelInfo._TestInfo[1].dbReadyPos1X.ToString("F2"),
                _ModelInfo._TestInfo[1].dbReadyPos1Y.ToString("F2"),
                 _ModelInfo._TestInfo[1].dbReadyPos1Z.ToString("F2"));

            if (_Config.strLangue == "KOR") strLabel = "검사위치";
            else if (_Config.strLangue == "CHINA") strLabel = "联系位置";
            dataGridView4.Rows.Add(strLabel, _ModelInfo._TestInfo[1].dbContactPos1X.ToString("F2"),
               _ModelInfo._TestInfo[1].dbContactPos1Y.ToString("F2"),
                _ModelInfo._TestInfo[1].dbContactPos1Z.ToString("F2"));

            if (_Config.strLangue == "KOR") strLabel = "바코드 스캔 위치";
            else if (_Config.strLangue == "CHINA") strLabel = "条码扫描位置";
            dataGridView4.Rows.Add(strLabel, _ModelInfo._TestInfo[1].dbSpare_b[0].ToString("F2"),
            _ModelInfo._TestInfo[1].dbSpare_b[1].ToString("F2"),
             _ModelInfo._TestInfo[1].dbSpare_b[2].ToString("F2"));



            for (int i = 0; i < 3; i++)
            {
                dataGridView4[0, i].ReadOnly = true;
                dataGridView4[0, i].Style.BackColor = Color.FromArgb(255, 255, 230);
            }

            




            dataGridView9.Rows.Clear();
            if (_Config.strLangue == "KOR") strLabel = "상부 라벨 스케쥴";
            else if (_Config.strLangue == "CHINA") strLabel = "顶部图像编号";
            dataGridView9.Rows.Add(_ModelInfo.bUseTopCamera, strLabel, _ModelInfo._TestInfo[0].nSpare_a[0].ToString());

            if (_Config.strLangue == "KOR") strLabel = "전면 라벨 스케쥴";
            else if (_Config.strLangue == "CHINA") strLabel = "正面图像编号";
            dataGridView9.Rows.Add(_ModelInfo.bUseFrotCamera, strLabel, _ModelInfo._TestInfo[0].nSpare_a[1].ToString());

            //dataGridView9.Rows.Add(true, "HIPOT(+) CH", _ModelInfo._TestInfo[0].nSpare_a[2].ToString());
            //dataGridView9.Rows.Add(true, "HIPOT(-) CH", _ModelInfo._TestInfo[0].nSpare_a[3].ToString());


            if (_Config.strLangue == "KOR") strLabel = "HIPOT 자동스캔 사용";
            else if (_Config.strLangue == "CHINA") strLabel = "条形码扫描仪使用";
            dataGridView9.Rows.Add(_ModelInfo.bUseHipotBCDScanner, strLabel, "");

            dataGridView9.Rows.Add(_ModelInfo.bUseHipotHandReader, "HIPOT 수동스캔 사용", "");

            dataGridView9.Rows.Add(_ModelInfo.bUseStandAloneCanComm, "스탠드 얼론 Can 통신 사용", "");
            dataGridView9.Rows.Add(_ModelInfo.bUseResuCanComm, "가정용 Can 통신 사용", "");
            dataGridView9.Rows.Add(_ModelInfo.bUseTwinPort, "Twin Port 사용", "");

            dataGridView9.Rows.Add(true, "HIPOT RAMP TIME (Sec)", _ModelInfo.dbHipotRampTime);
            //dataGridView9.Rows.Add(_ModelInfo.bUseHipot1Distance, "Distance", _ModelInfo.dbHipot1Distance);
            dataGridView9.Rows.Add(_ModelInfo.bUseHipot1UpDwContact, "하이팟 1번축 상하 컨텍 사용여부", "");

            for (int i = 0; i < 9; i++)
            {
                dataGridView9[0, i].Style.BackColor = Color.FromArgb(255, 255, 230);
                dataGridView9[1, i].ReadOnly = true;
                dataGridView9[1, i].Style.BackColor = Color.FromArgb(255, 255, 230);
            }


            dataGridView10.Rows.Clear();
            if (_Config.strLangue == "KOR") strLabel = "EOL 자동스캔 사용";
            else if (_Config.strLangue == "CHINA") strLabel = "条形码扫描仪使用";
            dataGridView10.Rows.Add(_ModelInfo.bUseEolBCDScanner, strLabel, "");
            dataGridView10.Rows.Add(_ModelInfo.bUseEolHandReader,"EOL 수동스캔 사용", "");
            dataGridView10.Rows.Add(_ModelInfo.bUseBpuScan, "BPU 스캔 기능 사용함", "");
            //dataGridView10.Rows.Add(_ModelInfo.bUseEolDistance, "Distance", _ModelInfo.dbEolDistance);
            for (int i = 0; i < 3; i++)
            {
                dataGridView10[0, i].Style.BackColor = Color.FromArgb(255, 255, 230);
                dataGridView10[1, i].ReadOnly = true;
                dataGridView10[1, i].Style.BackColor = Color.FromArgb(255, 255, 230);
            }
            //dataGridView1.Rows.Add("로딩 위치", false, _ModelInfo.dbPackLoadingPointX, _ModelInfo.dbPackLoadingPointY, _ModelInfo.dbPackLoadingPointZ, 0);


            dataGridView2.Rows.Clear();

            if (_Config.strLangue == "KOR")
            {
                dataGridView2.Rows.Add(_ModelInfo.bUseHipotFix, "HIPOT 고정 실린더 사용함", "");
                dataGridView2.Rows.Add(_ModelInfo.bUseEolFix, "EOL 고정 실린더 사용함", "");
                dataGridView2.Rows.Add(_ModelInfo.bUseHipotAutoContact, "HIPOT 자동검사 사용함", "");
                dataGridView2.Rows.Add(_ModelInfo.bUseEolAutoContact, "EOL 자동검사 사용함", "");
                dataGridView2.Rows.Add(_ModelInfo.bUseEOLSideContact, "EOL 측면 컨텍 사용함", "");
                dataGridView2.Rows.Add(_ModelInfo.bUseLabelFoolproof, "Omron Label 검사 사용함", "");
                dataGridView2.Rows.Add(_ModelInfo.bUseOmronHipotTest, "HIPOT / EOL Omron 검사모드", "");
                dataGridView2.Rows.Add(_ModelInfo.bUseScanSTTester, "충방전 시험기 사용함", "");
                dataGridView2.Rows.Add(_ModelInfo.bUseLandingPCSheet, "로딩시 PC Sheet 부착 기능 사용");
                dataGridView2.Rows.Add(_ModelInfo.bUsePalletBarcode, "파레트 바코드 스캔 기능 사용");
                dataGridView2.Rows.Add(_ModelInfo.bUseSharpPrint, "Sharp향 바코드 프린트 사용", "");
                dataGridView2.Rows.Add(_ModelInfo.bUseCmaBizBCD, "CMA Biz 바코드 출력 사용");
                dataGridView2.Rows.Add(_ModelInfo.bUseOmronGen3TypeBCDPrint, "Omron Gen3 AB 출력 사용");
                dataGridView2.Rows.Add(_ModelInfo.bUseResuGen3TypeBCDPrint, "Resu Gen3 AB 출력 사용");
                dataGridView2.Rows.Add(_ModelInfo.bUseOmronGen3Type150BCDPrint, "Omron Gen3(150V) CD 출력 사용");
                

                dataGridView2.Rows.Add(_ModelInfo.bUseLaserMarking, "레이저 마킹기 사용", _ModelInfo.strLaserMarkingSymbol);
                dataGridView2.Rows.Add(_ModelInfo.bUnUseLineSymbol, "바코드 출력시 라인구분자 사용안함");
            }
            else if (_Config.strLangue == "CHINA")
            {
                dataGridView2.Rows.Add(_ModelInfo.bUseHipotFix, "USE HIPOT FIX", "");
                dataGridView2.Rows.Add(_ModelInfo.bUseEolFix, "USE EOL FIX", "");
                dataGridView2.Rows.Add(_ModelInfo.bUseHipotAutoContact, "USE HIPOT AUTO TEST", "");
                dataGridView2.Rows.Add(_ModelInfo.bUseEolAutoContact, "USE EOL AUTO TEST", "");
                dataGridView2.Rows.Add(_ModelInfo.bUseEOLSideContact, "USE EOL CONTACT", "");
                dataGridView2.Rows.Add(_ModelInfo.bUseLabelFoolproof, "USE Omron Label TEST", "");
                dataGridView2.Rows.Add(_ModelInfo.bUseOmronHipotTest, "USE HIPOT / EOL Omron Mode", "");
                dataGridView2.Rows.Add(_ModelInfo.bUseScanSTTester, "충방전 시험기 사용함", "");

                dataGridView2.Rows.Add(_ModelInfo.bUseLandingPCSheet, "Loading PC Sheet 附着");
                dataGridView2.Rows.Add(_ModelInfo.bUsePalletBarcode, "Pallet Barcode Scan 使用");
                dataGridView2.Rows.Add(_ModelInfo.bUseSharpPrint, "Sharp향 바코드 프린트 사용", "");
                dataGridView2.Rows.Add(_ModelInfo.bUseCmaBizBCD, "CMA Biz 바코드 출력 사용");
                dataGridView2.Rows.Add(_ModelInfo.bUseOmronGen3TypeBCDPrint, "Omron Gen3 AB 출력 사용");
                dataGridView2.Rows.Add(_ModelInfo.bUseResuGen3TypeBCDPrint, "Resu Gen3 AB 출력 사용");
                dataGridView2.Rows.Add(_ModelInfo.bUseOmronGen3Type150BCDPrint, "Omron Gen3(150V) CD 출력 사용");
                dataGridView2.Rows.Add(_ModelInfo.bUseLaserMarking, "레이저 마킹기 사용", _ModelInfo.strLaserMarkingSymbol);
                dataGridView2.Rows.Add(_ModelInfo.bUnUseLineSymbol, "바코드 출력시 라인구분자 사용안함");
            }

            
            for (int i = 0; i < dataGridView2.Rows.Count; i++)
            {
                dataGridView2[0, i].Style.BackColor = Color.FromArgb(255, 255, 230);
                dataGridView2[1, i].ReadOnly = true;
                dataGridView2[1, i].Style.BackColor = Color.FromArgb(255, 255, 230);
            }

        }


        public void PointInfoLoad()
        {
            dataGridView3.EndEdit();
            double.TryParse(dataGridView3[1, 0].Value.ToString(), out _ModelInfo._TestInfo[0].dbReadyPos1X);
            double.TryParse(dataGridView3[2, 0].Value.ToString(), out _ModelInfo._TestInfo[0].dbReadyPos1Y);
            double.TryParse(dataGridView3[3, 0].Value.ToString(), out _ModelInfo._TestInfo[0].dbReadyPos1Z);

            double.TryParse(dataGridView3[4, 0].Value.ToString(), out _ModelInfo._TestInfo[0].dbReadyPos2X);
            double.TryParse(dataGridView3[5, 0].Value.ToString(), out _ModelInfo._TestInfo[0].dbReadyPos2Y);
            double.TryParse(dataGridView3[6, 0].Value.ToString(), out _ModelInfo._TestInfo[0].dbReadyPos2Z);


            double.TryParse(dataGridView3[1, 1].Value.ToString(), out _ModelInfo._TestInfo[0].dbContactPos1X);
            double.TryParse(dataGridView3[2, 1].Value.ToString(), out _ModelInfo._TestInfo[0].dbContactPos1Y);
            double.TryParse(dataGridView3[3, 1].Value.ToString(), out _ModelInfo._TestInfo[0].dbContactPos1Z);

            double.TryParse(dataGridView3[4, 1].Value.ToString(), out _ModelInfo._TestInfo[0].dbContactPos2X);
            double.TryParse(dataGridView3[5, 1].Value.ToString(), out _ModelInfo._TestInfo[0].dbContactPos2Y);
            double.TryParse(dataGridView3[6, 1].Value.ToString(), out _ModelInfo._TestInfo[0].dbContactPos2Z);


            double.TryParse(dataGridView3[4, 2].Value.ToString(), out _ModelInfo._TestInfo[0].dbSpare_b[0]);
            double.TryParse(dataGridView3[5, 2].Value.ToString(), out _ModelInfo._TestInfo[0].dbSpare_b[1]);
            double.TryParse(dataGridView3[6, 2].Value.ToString(), out _ModelInfo._TestInfo[0].dbSpare_b[2]);

            double.TryParse(dataGridView3[4, 3].Value.ToString(), out _ModelInfo._TestInfo[0].dbSpare_b[3]);
            double.TryParse(dataGridView3[5, 3].Value.ToString(), out _ModelInfo._TestInfo[0].dbSpare_b[4]);
            double.TryParse(dataGridView3[6, 3].Value.ToString(), out _ModelInfo._TestInfo[0].dbSpare_b[5]);

            double.TryParse(dataGridView3[4, 4].Value.ToString(), out _ModelInfo._TestInfo[0].dbSpare_b[6]);
            double.TryParse(dataGridView3[5, 4].Value.ToString(), out _ModelInfo._TestInfo[0].dbSpare_b[7]);
            double.TryParse(dataGridView3[6, 4].Value.ToString(), out _ModelInfo._TestInfo[0].dbSpare_b[8]);

            dataGridView4.EndEdit();
            double.TryParse(dataGridView4[1, 0].Value.ToString(), out _ModelInfo._TestInfo[1].dbReadyPos1X);
            double.TryParse(dataGridView4[2, 0].Value.ToString(), out _ModelInfo._TestInfo[1].dbReadyPos1Y);
            double.TryParse(dataGridView4[3, 0].Value.ToString(), out _ModelInfo._TestInfo[1].dbReadyPos1Z);

            double.TryParse(dataGridView4[1, 1].Value.ToString(), out _ModelInfo._TestInfo[1].dbContactPos1X);
            double.TryParse(dataGridView4[2, 1].Value.ToString(), out _ModelInfo._TestInfo[1].dbContactPos1Y);
            double.TryParse(dataGridView4[3, 1].Value.ToString(), out _ModelInfo._TestInfo[1].dbContactPos1Z);

            double.TryParse(dataGridView4[1, 2].Value.ToString(), out _ModelInfo._TestInfo[1].dbSpare_b[0]);
            double.TryParse(dataGridView4[2, 2].Value.ToString(), out _ModelInfo._TestInfo[1].dbSpare_b[1]);
            double.TryParse(dataGridView4[3, 2].Value.ToString(), out _ModelInfo._TestInfo[1].dbSpare_b[2]);

            dataGridView9.EndEdit();
            int.TryParse(dataGridView9[2, 0].Value.ToString(), out _ModelInfo._TestInfo[0].nSpare_a[0]);
            int.TryParse(dataGridView9[2, 1].Value.ToString(), out _ModelInfo._TestInfo[0].nSpare_a[1]);
            //int.TryParse(dataGridView9[2, 2].Value.ToString(), out _ModelInfo._TestInfo[0].nSpare_a[2]);
            //int.TryParse(dataGridView9[2, 3].Value.ToString(), out _ModelInfo._TestInfo[0].nSpare_a[3]);

            bool.TryParse(dataGridView9[0, 0].Value.ToString(), out _ModelInfo.bUseTopCamera);
            bool.TryParse(dataGridView9[0, 1].Value.ToString(), out _ModelInfo.bUseFrotCamera);
            bool.TryParse(dataGridView9[0, 2].Value.ToString(), out _ModelInfo.bUseHipotBCDScanner);
            bool.TryParse(dataGridView9[0, 3].Value.ToString(), out _ModelInfo.bUseHipotHandReader);

            
            bool.TryParse(dataGridView9[0, 4].Value.ToString(), out _ModelInfo.bUseStandAloneCanComm);
            bool.TryParse(dataGridView9[0, 5].Value.ToString(), out _ModelInfo.bUseResuCanComm);
            bool.TryParse(dataGridView9[0, 6].Value.ToString(), out _ModelInfo.bUseTwinPort);

            double.TryParse(dataGridView9[2, 7].Value.ToString(), out _ModelInfo.dbHipotRampTime);
            bool.TryParse(dataGridView9[0, 8].Value.ToString(), out _ModelInfo.bUseHipot1UpDwContact);
            //bool.TryParse(dataGridView9[0, 8].Value.ToString(), out _ModelInfo.bUseHipot1Distance);
            //double.TryParse(dataGridView9[2, 8].Value.ToString(), out _ModelInfo.dbHipot1Distance);


            dataGridView10.EndEdit();
            bool.TryParse(dataGridView10[0, 0].Value.ToString(), out _ModelInfo.bUseEolBCDScanner);
            bool.TryParse(dataGridView10[0, 1].Value.ToString(), out _ModelInfo.bUseEolHandReader);
            bool.TryParse(dataGridView10[0, 2].Value.ToString(), out _ModelInfo.bUseBpuScan);
            //bool.TryParse(dataGridView10[0, 3].Value.ToString(), out _ModelInfo.bUseEolDistance);
            //double.TryParse(dataGridView10[2, 3].Value.ToString(), out _ModelInfo.dbEolDistance);


            dataGridView2.EndEdit();
            bool.TryParse(dataGridView2[0, 0].Value.ToString(), out _ModelInfo.bUseHipotFix);
            bool.TryParse(dataGridView2[0, 1].Value.ToString(), out _ModelInfo.bUseEolFix);
            bool.TryParse(dataGridView2[0, 2].Value.ToString(), out _ModelInfo.bUseHipotAutoContact);
            bool.TryParse(dataGridView2[0, 3].Value.ToString(), out _ModelInfo.bUseEolAutoContact);
            bool.TryParse(dataGridView2[0, 4].Value.ToString(), out _ModelInfo.bUseEOLSideContact);
            bool.TryParse(dataGridView2[0, 5].Value.ToString(), out _ModelInfo.bUseLabelFoolproof);
            bool.TryParse(dataGridView2[0, 6].Value.ToString(), out _ModelInfo.bUseOmronHipotTest);
            bool.TryParse(dataGridView2[0, 7].Value.ToString(), out _ModelInfo.bUseScanSTTester);

            bool.TryParse(dataGridView2[0, 8].Value.ToString(), out _ModelInfo.bUseLandingPCSheet);
            bool.TryParse(dataGridView2[0, 9].Value.ToString(), out _ModelInfo.bUsePalletBarcode);
            bool.TryParse(dataGridView2[0, 10].Value.ToString(), out _ModelInfo.bUseSharpPrint);
            bool.TryParse(dataGridView2[0, 11].Value.ToString(), out _ModelInfo.bUseCmaBizBCD);
            bool.TryParse(dataGridView2[0, 12].Value.ToString(), out _ModelInfo.bUseOmronGen3TypeBCDPrint);
            bool.TryParse(dataGridView2[0, 13].Value.ToString(), out _ModelInfo.bUseResuGen3TypeBCDPrint);
            bool.TryParse(dataGridView2[0, 14].Value.ToString(), out _ModelInfo.bUseOmronGen3Type150BCDPrint);

            bool.TryParse(dataGridView2[0, 15].Value.ToString(), out _ModelInfo.bUseLaserMarking);
            _ModelInfo.strLaserMarkingSymbol = dataGridView2[2, 15].Value.ToString();
            bool.TryParse(dataGridView2[0, 16].Value.ToString(), out _ModelInfo.bUnUseLineSymbol);
        }

        

        //void TPCDataView() 
        //{
        //    dataGridView16.Rows.Clear();

        //    if (_Config.strLangue == "KOR")
        //    {
        //        dataGridView16.Rows.Add(_ModelInfo.bUseTPCRobot, "TPC 모델명 #1", _ModelInfo.strST3Model1);
        //        dataGridView16.Rows.Add(_ModelInfo.bUseST3Model2, "TPC 모델명 #2", _ModelInfo.strST3Model2);
        //        dataGridView16.Rows.Add(true, "체결 스케쥴", _ModelInfo.nTPCTiteSch);
        //        dataGridView16.Rows.Add(true, "제품 회전 각도", _ModelInfo.dbST3TurnAngle);
        //        dataGridView16.Rows.Add(true, "제품 회전 속도", _ModelInfo.dbST3TurnSpeed);
        //    }
        //    else
        //    {
        //        dataGridView16.Rows.Add(_ModelInfo.bUseTPCRobot, "TPC MODEL NAME #1", _ModelInfo.strST3Model1);
        //        dataGridView16.Rows.Add(_ModelInfo.bUseST3Model2, "TPC MODEL NAME #2", _ModelInfo.strST3Model2);
        //        dataGridView16.Rows.Add(true, "Nutrunner Sch", _ModelInfo.nTPCTiteSch);
        //        dataGridView16.Rows.Add(true, "产品回转角度", _ModelInfo.dbST3TurnAngle);
        //        dataGridView16.Rows.Add(true, "产品回转速度", _ModelInfo.dbST3TurnSpeed);
        //    }

        //    for (int i = 0; i < 5; i++)
        //    {
        //        dataGridView16[0, i].Style.BackColor = Color.FromArgb(255, 255, 230);
        //        dataGridView16[1, i].ReadOnly = true;
        //        dataGridView16[1, i].Style.BackColor = Color.FromArgb(255, 255, 230);
        //    }

        //}

        //void TPCDataLoad()
        //{
        //    dataGridView16.EndEdit();

        //    bool.TryParse(dataGridView16[0, 0].Value.ToString(), out _ModelInfo.bUseTPCRobot);
        //    //_ModelInfo.strST3Model1 = dataGridView16[2, 0].Value.ToString();
        //    try
        //    {
        //        _ModelInfo.strST3Model1 = dataGridView16[2, 0].Value.ToString();
        //    }
        //    catch { _ModelInfo.strST3Model1 = ""; }

        //    bool.TryParse(dataGridView16[0, 1].Value.ToString(), out _ModelInfo.bUseST3Model2);
        //    try
        //    {
        //        _ModelInfo.strST3Model2 = dataGridView16[2, 1].Value.ToString();
        //    }
        //    catch { _ModelInfo.strST3Model2 = ""; }

        //    int.TryParse(dataGridView16[2, 2].Value.ToString(), out _ModelInfo.nTPCTiteSch);

        //    double.TryParse(dataGridView16[2, 3].Value.ToString(), out _ModelInfo.dbST3TurnAngle);
        //    double.TryParse(dataGridView16[2, 4].Value.ToString(), out _ModelInfo.dbST3TurnSpeed);
        //}


        void ETCDataView()
        {
            dataGridView14.Rows.Clear();
            if (_Config.strLangue == "KOR")
            {
                dataGridView14.Rows.Add("CMA 적재 개수", _ModelInfo.nCmaCount);
                dataGridView14.Rows.Add("CMA 바코드 구분자", _ModelInfo.strCmaSymbol);

                dataGridView14.Rows.Add("BMS 적재 개수", _ModelInfo.nBmsCount);
                dataGridView14.Rows.Add("BMS 바코드 구분자", _ModelInfo.strBmsSymbol);

                dataGridView14.Rows.Add("PRE WORK 적재 개수", _ModelInfo.nPreWorkCount);
                dataGridView14.Rows.Add("PRE WORK 바코드 구분자", _ModelInfo.strPreWorkSymbol);

                dataGridView14.Rows.Add("FUSE 검사 사용 유무", _ModelInfo.nFuseCount);
                dataGridView14.Rows.Add("FUSE 검사 구분자", _ModelInfo.strFuseSymbol);

                dataGridView14.Rows.Add("이종품1 검사 사용 유무", _ModelInfo.nUseETC1BCD);
                dataGridView14.Rows.Add("이종품1 검사 구분자", _ModelInfo.strETC1BCD);

                dataGridView14.Rows.Add("이종품2 검사 사용 유무", _ModelInfo.nUseETC2BCD);
                dataGridView14.Rows.Add("이종품2 검사 구분자", _ModelInfo.strETC2BCD);
                dataGridView14.Rows.Add("제품 2단 적재시 대기위치", _ModelInfo.nLoadingStopProduct);


                dataGridView14.Rows.Add("PP Sheet Base 검사 사용 유무", _ModelInfo.nUseETC3BCD);
                dataGridView14.Rows.Add("PP Sheet Base 검사 구분자", _ModelInfo.strETC3BCD);

                dataGridView14.Rows.Add("PP Sheet Top 검사 사용 유무", _ModelInfo.nUseETC4BCD);
                dataGridView14.Rows.Add("PP Sheet Top 검사 구분자", _ModelInfo.strETC4BCD);


                //dataGridView14.Rows.Add("Rear Support Plate 검사 사용 유무", _ModelInfo.nUseETC5BCD);
                dataGridView14.Rows.Add("Rear Support Plate 검사 구분자", _ModelInfo.strETC5BCD);
                dataGridView14.Rows.Add("Rear Support Plate 수량", _ModelInfo.nUseETC5BCDCount);

                dataGridView14.Rows.Add("바코드 라인 구분자", _ModelInfo.strBCDSymbol);

                dataGridView14.Rows.Add("출력 바코드 사이즈", _ModelInfo.nBCDsize);
                dataGridView14.Rows.Add("출력 텍스트 넓이", _ModelInfo.nBCDStringWidth);
                dataGridView14.Rows.Add("출력 텍스트 높이", _ModelInfo.nBCDStringHeight);
                dataGridView14.Rows.Add("바코드 출력 횟수", _ModelInfo.nBCDPrintCount);

                dataGridView14.Rows.Add("바코드 출력 위치(X)", _ModelInfo.nBCDOffsetX);
                dataGridView14.Rows.Add("바코드 출력 위치(Y)", _ModelInfo.nBCDOffsetY);
                dataGridView14.Rows.Add("텍스트 출력 위치(X)", _ModelInfo.nTextOffsetX);
                dataGridView14.Rows.Add("텍스트 출력 위치(Y)", _ModelInfo.nTextOffsetY);

             
                dataGridView14.Rows.Add("PACK바코드 구분자", _ModelInfo.strLaserReadBmaSymbol);
                dataGridView14.Rows.Add("레이저마킹 스테이션", _ModelInfo.nMarkingStation);

                dataGridView14.Rows.Add("CMA 바코드 날짜 시작 위치", _ModelInfo.nCMAStartIndex);
                dataGridView14.Rows.Add("CMA 인터락 시간 범위", _ModelInfo.nTimeLimit);

              



            }
            else if (_Config.strLangue == "CHINA")
            {
                dataGridView14.Rows.Add("CMA堆叠数量", _ModelInfo.nCmaCount);
                dataGridView14.Rows.Add("CMA条码区分", _ModelInfo.strCmaSymbol);

                dataGridView14.Rows.Add("BMS堆叠数量", _ModelInfo.nBmsCount);
                dataGridView14.Rows.Add("BMS条码区分", _ModelInfo.strBmsSymbol);

                dataGridView14.Rows.Add("PRE WORK 적재 개수", _ModelInfo.nPreWorkCount);
                dataGridView14.Rows.Add("PRE WORK 바코드 구분자", _ModelInfo.strPreWorkSymbol);

                dataGridView14.Rows.Add("FUSE装载数量", _ModelInfo.nFuseCount);
                dataGridView14.Rows.Add("FUSE检查区分", _ModelInfo.strFuseSymbol);

                dataGridView14.Rows.Add("ETC1装载数量", _ModelInfo.nUseETC1BCD);
                dataGridView14.Rows.Add("ETC1检查区分", _ModelInfo.strETC1BCD);

                dataGridView14.Rows.Add("ETC2装载数量", _ModelInfo.nUseETC2BCD);
                dataGridView14.Rows.Add("ETC2检查区分", _ModelInfo.strETC2BCD);

                // 이종품 추가
                dataGridView14.Rows.Add("产品二楼当装载备用位置", _ModelInfo.nLoadingStopProduct);

                
                dataGridView14.Rows.Add("PP Sheet Base 装载数量", _ModelInfo.nUseETC3BCD);
                dataGridView14.Rows.Add("PP Sheet Base 检查区分", _ModelInfo.strETC3BCD);

                dataGridView14.Rows.Add("PP Sheet Top 装载数量", _ModelInfo.nUseETC4BCD);
                dataGridView14.Rows.Add("PP Sheet Top 检查区分", _ModelInfo.strETC4BCD);
                
                //dataGridView14.Rows.Add("Rear Support Plate 装载数量", _ModelInfo.nUseETC5BCD);
                dataGridView14.Rows.Add("Rear Support Plate 检查区分", _ModelInfo.strETC5BCD);
                dataGridView14.Rows.Add("Rear Support Plate 数量", _ModelInfo.nUseETC5BCDCount);

                dataGridView14.Rows.Add("线体区分", _ModelInfo.strBCDSymbol);

                dataGridView14.Rows.Add("打印二维码宽度", _ModelInfo.nBCDsize);
                dataGridView14.Rows.Add("条码字体宽度", _ModelInfo.nBCDStringWidth);
                dataGridView14.Rows.Add("条码字体高度", _ModelInfo.nBCDStringHeight);
                dataGridView14.Rows.Add("条码打印数量", _ModelInfo.nBCDPrintCount);

                dataGridView14.Rows.Add("二维码打印位置(X)", _ModelInfo.nBCDOffsetX);
                dataGridView14.Rows.Add("二维码打印位置(Y)", _ModelInfo.nBCDOffsetY);
                dataGridView14.Rows.Add("条码打印位置(X)", _ModelInfo.nTextOffsetX);
                dataGridView14.Rows.Add("条码打印位置(Y)", _ModelInfo.nTextOffsetY);

   
                dataGridView14.Rows.Add("레이저마킹 PACK바코드 구분자", _ModelInfo.strLaserReadBmaSymbol);
                dataGridView14.Rows.Add("레이저마킹 스테이션", _ModelInfo.nMarkingStation);

                dataGridView14.Rows.Add("CMA 바코드 날짜 시작 위치", _ModelInfo.nCMAStartIndex);
                dataGridView14.Rows.Add("CMA 인터락 시간 범위", _ModelInfo.nTimeLimit);

               


            }
            for (int i = 0; i < dataGridView14.Rows.Count; i++)
            {
                dataGridView14[0, i].ReadOnly = true;
                dataGridView14[0, i].Style.BackColor = Color.FromArgb(255, 255, 230);
            }
        }

        void EtcDataLoad()
        {
            dataGridView14.EndEdit();

            int.TryParse(dataGridView14[1, 0].Value.ToString(), out _ModelInfo.nCmaCount);
            _ModelInfo.strCmaSymbol = dataGridView14[1, 1].Value.ToString();

            int.TryParse(dataGridView14[1, 2].Value.ToString(), out _ModelInfo.nBmsCount);
            _ModelInfo.strBmsSymbol = dataGridView14[1, 3].Value.ToString();

            int.TryParse(dataGridView14[1, 4].Value.ToString(), out _ModelInfo.nPreWorkCount);
            _ModelInfo.strPreWorkSymbol = dataGridView14[1, 5].Value.ToString();

            int.TryParse(dataGridView14[1, 6].Value.ToString(), out _ModelInfo.nFuseCount);
            _ModelInfo.strFuseSymbol = dataGridView14[1, 7].Value.ToString();

            int.TryParse(dataGridView14[1, 8].Value.ToString(), out _ModelInfo.nUseETC1BCD);

            try
            {
                _ModelInfo.strETC1BCD = dataGridView14[1, 9].Value.ToString();
            }
            catch { _ModelInfo.strETC1BCD = ""; }

            int.TryParse(dataGridView14[1, 10].Value.ToString(), out _ModelInfo.nUseETC2BCD);
            try
            {
                _ModelInfo.strETC2BCD = dataGridView14[1, 11].Value.ToString();
            }
            catch { _ModelInfo.strETC2BCD = ""; }

            int.TryParse(dataGridView14[1, 12].Value.ToString(), out _ModelInfo.nLoadingStopProduct);

            int.TryParse(dataGridView14[1, 13].Value.ToString(), out _ModelInfo.nUseETC3BCD);
            try
            {
                _ModelInfo.strETC3BCD = dataGridView14[1, 14].Value.ToString();
            }
            catch { _ModelInfo.strETC3BCD = ""; }


            int.TryParse(dataGridView14[1, 15].Value.ToString(), out _ModelInfo.nUseETC4BCD);
            try
            {
                _ModelInfo.strETC4BCD = dataGridView14[1, 16].Value.ToString();
            }
            catch { _ModelInfo.strETC4BCD = ""; }


            //int.TryParse(dataGridView14[1, 15].Value.ToString(), out _ModelInfo.nUseETC5BCD);
            try
            {
                _ModelInfo.strETC5BCD = dataGridView14[1, 17].Value.ToString();
            }
            catch { _ModelInfo.strETC5BCD = ""; }
            int.TryParse(dataGridView14[1, 18].Value.ToString(), out _ModelInfo.nUseETC5BCDCount);



            _ModelInfo.strBCDSymbol = dataGridView14[1, 19].Value.ToString();
            int.TryParse(dataGridView14[1, 20].Value.ToString(), out _ModelInfo.nBCDsize);
            int.TryParse(dataGridView14[1, 21].Value.ToString(), out _ModelInfo.nBCDStringWidth);
            int.TryParse(dataGridView14[1, 22].Value.ToString(), out _ModelInfo.nBCDStringHeight);
            int.TryParse(dataGridView14[1, 23].Value.ToString(), out _ModelInfo.nBCDPrintCount);

            int.TryParse(dataGridView14[1, 24].Value.ToString(), out _ModelInfo.nBCDOffsetX);
            int.TryParse(dataGridView14[1, 25].Value.ToString(), out _ModelInfo.nBCDOffsetY);
            int.TryParse(dataGridView14[1, 26].Value.ToString(), out _ModelInfo.nTextOffsetX);
            int.TryParse(dataGridView14[1, 27].Value.ToString(), out _ModelInfo.nTextOffsetY);

            _ModelInfo.strLaserReadBmaSymbol = dataGridView14[1, 28].Value.ToString();
            int.TryParse(dataGridView14[1, 29].Value.ToString(), out _ModelInfo.nMarkingStation);
            int.TryParse(dataGridView14[1, 30].Value.ToString(), out _ModelInfo.nCMAStartIndex);
            int.TryParse(dataGridView14[1, 31].Value.ToString(), out _ModelInfo.nTimeLimit);
        }

        void OmronDataView()
        {
            dataGridView26.Rows.Clear();
            dataGridView26.Rows.Add("카메라 대기 위치", _ModelInfo.dbCamera1ReadyPosX, _ModelInfo.dbCamera1ReadyPosY, _ModelInfo.dbCamera1ReadyPosZ, _ModelInfo.dbCamera2ReadyPosX, _ModelInfo.dbCamera2ReadyPosY, _ModelInfo.dbCamera2ReadyPosZ);
            dataGridView26.Rows.Add("카메라 검사 위치", _ModelInfo.dbCamera1WorkPosX, _ModelInfo.dbCamera1WorkPosY, _ModelInfo.dbCamera1WorkPosZ, _ModelInfo.dbCamera2WorkPosX, _ModelInfo.dbCamera2WorkPosY, _ModelInfo.dbCamera2WorkPosZ);

            for (int i = 0; i < 2; i++)
            {
                dataGridView26[0, i].ReadOnly = true;
                dataGridView26[0, i].Style.BackColor = Color.FromArgb(255, 255, 230);
            }


            dataGridView27.Rows.Clear();
            dataGridView27.Rows.Add(_ModelInfo.bUseOmronWHTest, "외함측정 기능 사용여부");
            dataGridView27.Rows.Add(false, "외함측정 검사 커맨드", _ModelInfo.strOmronWHTestCMD);
            dataGridView27.Rows.Add(false, "외함측정 검사 모델번호", _ModelInfo.strOmronWHTestSch);
            dataGridView27.Rows.Add(false, "외함측정 검사 설정번호", _ModelInfo.strOmronWHTestSelect);
            //dataGridView8.Rows.Add(false, "외함측정 검사 스펙 최소값(전폭)", _ModelInfo.dbOmronWDTestSpecWidth);
            //dataGridView8.Rows.Add(false, "외함측정 검사 스펙 최대값(전폭)", _ModelInfo.dbOmronWDTestSpecWidthMax);
           dataGridView27.Rows.Add(false, "외함측정 검사 스펙 최소값(전장)", _ModelInfo.dbOmronWDTestSpecHight);
            dataGridView27.Rows.Add(false, "외함측정 검사 스펙 최대값(전장)", _ModelInfo.dbOmronWDTestSpecHightMax);

            for (int i = 0; i < dataGridView27.Rows.Count; i++)
            {
                dataGridView27[1, i].ReadOnly = true;
                dataGridView27[1, i].Style.BackColor = Color.FromArgb(255, 255, 230);
            }
        }

        void OmronDataLoad()
        {
            dataGridView24.EndEdit();
            double.TryParse(dataGridView26[1, 0].Value.ToString(), out _ModelInfo.dbCamera1ReadyPosX);
            double.TryParse(dataGridView26[2, 0].Value.ToString(), out _ModelInfo.dbCamera1ReadyPosY);
            double.TryParse(dataGridView26[3, 0].Value.ToString(), out _ModelInfo.dbCamera1ReadyPosZ);
            double.TryParse(dataGridView26[4, 0].Value.ToString(), out _ModelInfo.dbCamera2ReadyPosX);
            double.TryParse(dataGridView26[5, 0].Value.ToString(), out _ModelInfo.dbCamera2ReadyPosY);
            double.TryParse(dataGridView26[6, 0].Value.ToString(), out _ModelInfo.dbCamera2ReadyPosZ);

            double.TryParse(dataGridView26[1, 1].Value.ToString(), out _ModelInfo.dbCamera1WorkPosX);
            double.TryParse(dataGridView26[2, 1].Value.ToString(), out _ModelInfo.dbCamera1WorkPosY);
            double.TryParse(dataGridView26[3, 1].Value.ToString(), out _ModelInfo.dbCamera1WorkPosZ);
            double.TryParse(dataGridView26[4, 1].Value.ToString(), out _ModelInfo.dbCamera2WorkPosX);
            double.TryParse(dataGridView26[5, 1].Value.ToString(), out _ModelInfo.dbCamera2WorkPosY);
            double.TryParse(dataGridView26[6, 1].Value.ToString(), out _ModelInfo.dbCamera2WorkPosZ);

            dataGridView27.EndEdit();
            bool.TryParse(dataGridView27[0, 0].Value.ToString(), out _ModelInfo.bUseOmronWHTest);
            _ModelInfo.strOmronWHTestCMD = dataGridView27[2, 1].Value.ToString();
            _ModelInfo.strOmronWHTestSch = dataGridView27[2, 2].Value.ToString();
            _ModelInfo.strOmronWHTestSelect = dataGridView27[2, 3].Value.ToString();
            //double.TryParse(dataGridView8[2, 4].Value.ToString(), out _ModelInfo.dbOmronWDTestSpecWidth);
            //double.TryParse(dataGridView8[2, 5].Value.ToString(), out _ModelInfo.dbOmronWDTestSpecWidthMax);
            double.TryParse(dataGridView27[2, 4].Value.ToString(), out _ModelInfo.dbOmronWDTestSpecHight);
            double.TryParse(dataGridView27[2, 5].Value.ToString(), out _ModelInfo.dbOmronWDTestSpecHightMax);

        }

        private void SpeedDataView()
        {

            dataGridView12.Rows.Clear();
            if (_Config.strLangue == "KOR")
            {
                dataGridView12.Rows.Add("제품 없을시 XY축 이동속도", _ModelInfo.dbNoClampXYMoveSpeed);
                dataGridView12.Rows.Add("제품 없을시 Z축 이동속도", _ModelInfo.dbNoClampZMoveSpeed);
                dataGridView12.Rows.Add("제품 있을시 XY축 이동속도", _ModelInfo.dbClampXYMoveSpeed);
                dataGridView12.Rows.Add("제품 있을시 Z축 이동속도", _ModelInfo.dbClampZMoveSpeed);
                dataGridView12.Rows.Add("제품 시프트시 이동 속도", _ModelInfo.dbShiftMoveSpeed);
                dataGridView12.Rows.Add("제품 로딩 각도", _ModelInfo.dbLoadingAngle);
            }
            else if (_Config.strLangue == "CHINA")
            {
                dataGridView12.Rows.Add("没有产品 XY 移动速度", _ModelInfo.dbNoClampXYMoveSpeed);
                dataGridView12.Rows.Add("没有产品 Z 移动速度", _ModelInfo.dbNoClampZMoveSpeed);
                dataGridView12.Rows.Add("有产品 XY 移动速度", _ModelInfo.dbClampXYMoveSpeed);
                dataGridView12.Rows.Add("有产品 Z 移动速度", _ModelInfo.dbClampZMoveSpeed);
                dataGridView12.Rows.Add("产品移 移动速度", _ModelInfo.dbShiftMoveSpeed);
                dataGridView12.Rows.Add("产品角度修正", _ModelInfo.dbLoadingAngle);
            }



            for (int i = 0; i < 6; i++)
            {
                dataGridView12[0, i].ReadOnly = true;
                dataGridView12[0, i].Style.BackColor = Color.FromArgb(255, 255, 230);
            }
        }

        private void SpeedDataLoad()
        {
            dataGridView12.EndEdit();

            double.TryParse(dataGridView12[1, 0].Value.ToString(), out _ModelInfo.dbNoClampXYMoveSpeed);
            double.TryParse(dataGridView12[1, 1].Value.ToString(), out _ModelInfo.dbNoClampZMoveSpeed);
            double.TryParse(dataGridView12[1, 2].Value.ToString(), out _ModelInfo.dbClampXYMoveSpeed);
            double.TryParse(dataGridView12[1, 3].Value.ToString(), out _ModelInfo.dbClampZMoveSpeed);
            double.TryParse(dataGridView12[1, 4].Value.ToString(), out _ModelInfo.dbShiftMoveSpeed);
            double.TryParse(dataGridView12[1, 5].Value.ToString(), out _ModelInfo.dbLoadingAngle);
        }


        void CommentNEtcLoad()
        {
            _ModelInfo.strComment1 = richTextBox1.Text;
            _ModelInfo.strComment2 = richTextBox2.Text;
            _ModelInfo.strComment3 = richTextBox3.Text;
            _ModelInfo.strComment4 = richTextBox5.Text;
        }

        void CommentNEtcView()
        {
            richTextBox1.Text = _ModelInfo.strComment1;
            richTextBox2.Text = _ModelInfo.strComment2;
            richTextBox3.Text = _ModelInfo.strComment3;
            richTextBox5.Text = _ModelInfo.strComment4;
        }

        private void BcdDataView()
        {

            dataGridView29.Rows.Clear();
            if (_Config.strLangue == "KOR")
            {
                //dataGridView3.Rows.Add("바코드 전체 오프셋 X", _Config.nBCDAllOffsetX);
                //dataGridView3.Rows.Add("바코드 전체 오프셋 Y", _Config.nBCDAllOffsetY);
                //dataGridView3.Rows.Add("바코드 오프셋 X", _Config.nBCDbcdOffsetX);
                //dataGridView3.Rows.Add("바코드 오프셋 Y", _Config.nBCDbcdOffsetY);
                //dataGridView3.Rows.Add("바코드 텍스트 오프셋 X", _Config.nBCDtextOffsetX);
                //dataGridView3.Rows.Add("바코드 텍스트 오프셋 Y", _Config.nBCDtextOffsetY);
                dataGridView29.Rows.Add("바코드 스캔 스테이션", _ModelInfo.nBCDScanStation);
                //_BCDDataTable.Rows.Add("바코드 설비 구분자", _Config.strBCDSymbol);
                dataGridView29.Rows.Add("이종품 검사 스테이션", _ModelInfo.nETCScanStation);
                dataGridView29.Rows.Add("시작 번호", _ModelInfo.nStartLotNum);
            }
            else if (_Config.strLangue == "CHINA")
            {
                //dataGridView3.Rows.Add("条码完全抵消 X", _Config.nBCDAllOffsetX);
                //dataGridView3.Rows.Add("条码完全抵消 Y", _Config.nBCDAllOffsetY);
                //dataGridView3.Rows.Add("条码偏移 X", _Config.nBCDbcdOffsetX);
                //dataGridView3.Rows.Add("条码偏移 Y", _Config.nBCDbcdOffsetY);
                //dataGridView3.Rows.Add("条码文字偏移 X", _Config.nBCDtextOffsetX);
                //dataGridView3.Rows.Add("条码文字偏移 Y", _Config.nBCDtextOffsetY);
                dataGridView29.Rows.Add("条码扫描位置", _ModelInfo.nBCDScanStation);
                //_BCDDataTable.Rows.Add("바코드 설비 구분자", _Config.strBCDSymbol);
                dataGridView29.Rows.Add("FUSE检查位置", _ModelInfo.nETCScanStation);
                dataGridView29.Rows.Add("LOT 序号", _ModelInfo.nStartLotNum);
            }

        }

        private void BcdDataLoad()
        {
            dataGridView29.EndEdit();
            //int.TryParse(dataGridView3[1, 0].Value.ToString(), out _Config.nBCDAllOffsetX);
            //int.TryParse(dataGridView3[1, 1].Value.ToString(), out _Config.nBCDAllOffsetY);
            //int.TryParse(dataGridView3[1, 2].Value.ToString(), out _Config.nBCDbcdOffsetX);
            //int.TryParse(dataGridView3[1, 3].Value.ToString(), out _Config.nBCDbcdOffsetY);
            //int.TryParse(dataGridView3[1, 4].Value.ToString(), out _Config.nBCDtextOffsetX);
            //int.TryParse(dataGridView3[1, 5].Value.ToString(), out _Config.nBCDtextOffsetY);
            int.TryParse(dataGridView29[1, 0].Value.ToString(), out _ModelInfo.nBCDScanStation);
            //_Config.strBCDSymbol = _BCDDataTable.Rows[7][1].ToString();
            int.TryParse(dataGridView29[1, 1].Value.ToString(), out _ModelInfo.nETCScanStation);
            int.TryParse(dataGridView29[1, 2].Value.ToString(), out _ModelInfo.nStartLotNum);
        }

        // Jog Down 이벤트
        public void Jog_Bt_Down(object sender, MouseEventArgs e)
        {

            double dbSpeed = 0.0;

            switch (((DevExpress.XtraEditors.SimpleButton)sender).Name)
            {
                case "Jog_X1": double.TryParse(comboBox1.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.X, -(dbSpeed), 0.2, 0.2); break;
                case "Jog_X2": double.TryParse(comboBox1.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.X, +(dbSpeed), 0.2, 0.2); break;
                case "Jog_Y1": double.TryParse(comboBox1.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.Y, -(dbSpeed), 0.2, 0.2); break;
                case "Jog_Y2": double.TryParse(comboBox1.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.Y, +(dbSpeed), 0.2, 0.2); break;
                case "Jog_Z1": double.TryParse(comboBox1.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.Z, -(dbSpeed), 0.2, 0.2); break;
                case "Jog_Z2": double.TryParse(comboBox1.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.Z, +(dbSpeed), 0.2, 0.2); break;

                case "HIPOTX1_1": double.TryParse(comboBox3.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.HIPOT_1X, -(dbSpeed), 0.2, 0.2); break;
                case "HIPOTX1_2": double.TryParse(comboBox3.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.HIPOT_1X, +(dbSpeed), 0.2, 0.2); break;
                case "HIPOTY1_1": double.TryParse(comboBox3.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.HIPOT_1Y, +(dbSpeed), 0.2, 0.2); break;
                case "HIPOTY1_2": double.TryParse(comboBox3.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.HIPOT_1Y, -(dbSpeed), 0.2, 0.2); break;
                case "HIPOTZ1_1": double.TryParse(comboBox3.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.HIPOT_1Z, -(dbSpeed), 0.2, 0.2); break;
                case "HIPOTZ1_2": double.TryParse(comboBox3.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.HIPOT_1Z, +(dbSpeed), 0.2, 0.2); break;

                case "HIPOTX2_1": double.TryParse(comboBox2.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.HIPOT_2X, +(dbSpeed), 0.2, 0.2); break;
                case "HIPOTX2_2": double.TryParse(comboBox2.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.HIPOT_2X, -(dbSpeed), 0.2, 0.2); break;
                case "HIPOTY2_1": double.TryParse(comboBox2.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.HIPOT_2Y, +(dbSpeed), 0.2, 0.2); break;
                case "HIPOTY2_2": double.TryParse(comboBox2.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.HIPOT_2Y, -(dbSpeed), 0.2, 0.2); break;
                case "HIPOTZ2_1": double.TryParse(comboBox2.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.HIPOT_2Z, -(dbSpeed), 0.2, 0.2); break;
                case "HIPOTZ2_2": double.TryParse(comboBox2.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.HIPOT_2Z, +(dbSpeed), 0.2, 0.2); break;

                case "EOLX_1": double.TryParse(comboBox4.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.EOL_X, +(dbSpeed), 0.2, 0.2); break;
                case "EOLX_2": double.TryParse(comboBox4.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.EOL_X, -(dbSpeed), 0.2, 0.2); break;
                case "EOLY_1": double.TryParse(comboBox4.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.EOL_Y, +(dbSpeed), 0.2, 0.2); break;
                case "EOLY_2": double.TryParse(comboBox4.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.EOL_Y, -(dbSpeed), 0.2, 0.2); break;
                case "EOLZ_1": double.TryParse(comboBox4.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.EOL_Z, +(dbSpeed), 0.2, 0.2); break;
                case "EOLZ_2": double.TryParse(comboBox4.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.EOL_Z, -(dbSpeed), 0.2, 0.2); break;

                case "Jog_R1": double.TryParse(comboBox1.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.R, -(dbSpeed), 0.2, 0.2); break;
                case "Jog_R2": double.TryParse(comboBox1.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.R, +(dbSpeed), 0.2, 0.2); break;

                case "CAMERA1_Y1": double.TryParse(comboBox11.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.CAMERA1_Y, +(dbSpeed), 0.2, 0.2); break;
                case "CAMERA1_Y2": double.TryParse(comboBox11.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.CAMERA1_Y, -(dbSpeed), 0.2, 0.2); break;
                case "CAMERA1_X1": double.TryParse(comboBox11.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.CAMERA1_X, +(dbSpeed), 0.2, 0.2); break;
                case "CAMERA1_X2": double.TryParse(comboBox11.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.CAMERA1_X, -(dbSpeed), 0.2, 0.2); break;
                case "CAMERA1_Z1": double.TryParse(comboBox11.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.CAMERA1_Z, -(dbSpeed), 0.2, 0.2); break;
                case "CAMERA1_Z2": double.TryParse(comboBox11.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.CAMERA1_Z, +(dbSpeed), 0.2, 0.2); break;


                case "CAMERA2_Y1": double.TryParse(comboBox10.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.CAMERA2_Y, -(dbSpeed), 0.2, 0.2); break;
                case "CAMERA2_Y2": double.TryParse(comboBox10.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.CAMERA2_Y, +(dbSpeed), 0.2, 0.2); break;
                case "CAMERA2_X1": double.TryParse(comboBox10.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.CAMERA2_X, -(dbSpeed), 0.2, 0.2); break;
                case "CAMERA2_X2": double.TryParse(comboBox10.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.CAMERA2_X, +(dbSpeed), 0.2, 0.2); break;
                case "CAMERA2_Z1": double.TryParse(comboBox10.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.CAMERA2_Z, -(dbSpeed), 0.2, 0.2); break;
                case "CAMERA2_Z2": double.TryParse(comboBox10.Text, out dbSpeed); CAXM.AxmMoveVel((int)AXIS.CAMERA2_Z, +(dbSpeed), 0.2, 0.2); break;
            }

            //timer2.Start();
        }

        // 조그 버튼 Up 이벤트
        public void Jog_Bt_Up(object sender, MouseEventArgs e)
        {
            //timer2.Stop();

            switch (((DevExpress.XtraEditors.SimpleButton)sender).Name)
            {
                case "Jog_X1": CAXM.AxmMoveSStop((int)AXIS.X); break;
                case "Jog_X2": CAXM.AxmMoveSStop((int)AXIS.X); break;
                case "Jog_Y1": CAXM.AxmMoveSStop((int)AXIS.Y); break;
                case "Jog_Y2": CAXM.AxmMoveSStop((int)AXIS.Y); break;
                case "Jog_Z1": CAXM.AxmMoveSStop((int)AXIS.Z); break;
                case "Jog_Z2": CAXM.AxmMoveSStop((int)AXIS.Z); break;
                case "HIPOTX1_1": CAXM.AxmMoveSStop((int)AXIS.HIPOT_1X); break;
                case "HIPOTX1_2": CAXM.AxmMoveSStop((int)AXIS.HIPOT_1X); break;
                case "HIPOTY1_1": CAXM.AxmMoveSStop((int)AXIS.HIPOT_1Y); break;
                case "HIPOTY1_2": CAXM.AxmMoveSStop((int)AXIS.HIPOT_1Y); break;
                case "HIPOTZ1_1": CAXM.AxmMoveSStop((int)AXIS.HIPOT_1Z); break;
                case "HIPOTZ1_2": CAXM.AxmMoveSStop((int)AXIS.HIPOT_1Z); break;
                case "HIPOTX2_1": CAXM.AxmMoveSStop((int)AXIS.HIPOT_2X); break;
                case "HIPOTX2_2": CAXM.AxmMoveSStop((int)AXIS.HIPOT_2X); break;
                case "HIPOTY2_1": CAXM.AxmMoveSStop((int)AXIS.HIPOT_2Y); break;
                case "HIPOTY2_2": CAXM.AxmMoveSStop((int)AXIS.HIPOT_2Y); break;
                case "HIPOTZ2_1": CAXM.AxmMoveSStop((int)AXIS.HIPOT_2Z); break;
                case "HIPOTZ2_2": CAXM.AxmMoveSStop((int)AXIS.HIPOT_2Z); break;
                case "EOLX_1": CAXM.AxmMoveSStop((int)AXIS.EOL_X); break;
                case "EOLX_2": CAXM.AxmMoveSStop((int)AXIS.EOL_X); break;
                case "EOLY_1": CAXM.AxmMoveSStop((int)AXIS.EOL_Y); break;
                case "EOLY_2": CAXM.AxmMoveSStop((int)AXIS.EOL_Y); break;
                case "EOLZ_1": CAXM.AxmMoveSStop((int)AXIS.EOL_Z); break;
                case "EOLZ_2": CAXM.AxmMoveSStop((int)AXIS.EOL_Z); break;
                case "Jog_R1": CAXM.AxmMoveSStop((int)AXIS.R); break;
                case "Jog_R2": CAXM.AxmMoveSStop((int)AXIS.R); break;

                case "CAMERA1_Y1": CAXM.AxmMoveSStop((int)AXIS.CAMERA1_Y); CAXM.AxmMoveSStop((int)AXIS.CAMERA1_Y); break;
                case "CAMERA1_Y2": CAXM.AxmMoveSStop((int)AXIS.CAMERA1_Y); CAXM.AxmMoveSStop((int)AXIS.CAMERA1_Y); break;
                case "CAMERA1_X1": CAXM.AxmMoveSStop((int)AXIS.CAMERA1_X); CAXM.AxmMoveSStop((int)AXIS.CAMERA1_X); break;
                case "CAMERA1_X2": CAXM.AxmMoveSStop((int)AXIS.CAMERA1_X); CAXM.AxmMoveSStop((int)AXIS.CAMERA1_X); break;
                case "CAMERA1_Z1": CAXM.AxmMoveSStop((int)AXIS.CAMERA1_Z); CAXM.AxmMoveSStop((int)AXIS.CAMERA1_Z); break;
                case "CAMERA1_Z2": CAXM.AxmMoveSStop((int)AXIS.CAMERA1_Z); CAXM.AxmMoveSStop((int)AXIS.CAMERA1_Z); break;

                case "CAMERA2_Y1": CAXM.AxmMoveSStop((int)AXIS.CAMERA2_Y); CAXM.AxmMoveSStop((int)AXIS.CAMERA2_Y); break;
                case "CAMERA2_Y2": CAXM.AxmMoveSStop((int)AXIS.CAMERA2_Y); CAXM.AxmMoveSStop((int)AXIS.CAMERA2_Y); break;
                case "CAMERA2_X1": CAXM.AxmMoveSStop((int)AXIS.CAMERA2_X); CAXM.AxmMoveSStop((int)AXIS.CAMERA2_X); break;
                case "CAMERA2_X2": CAXM.AxmMoveSStop((int)AXIS.CAMERA2_X); CAXM.AxmMoveSStop((int)AXIS.CAMERA2_X); break;
                case "CAMERA2_Z1": CAXM.AxmMoveSStop((int)AXIS.CAMERA2_Z); CAXM.AxmMoveSStop((int)AXIS.CAMERA2_Z); break;
                case "CAMERA2_Z2": CAXM.AxmMoveSStop((int)AXIS.CAMERA2_Z); CAXM.AxmMoveSStop((int)AXIS.CAMERA2_Z); break;
            }
        }


        public void ChinaLangSet()
        {
            if (_Config.strLangue == "KOR") return;


            simpleButton74.Text = "上升";
            simpleButton73.Text = "下降";

            simpleButton72.Text = "上升";
            simpleButton71.Text = "下降";

            simpleButton6.Text = "排出";
            simpleButton5.Text = "投入";

            simpleButton76.Text = "上升";
            simpleButton75.Text = "下降";

            simpleButton35.Text = "上升";
            simpleButton34.Text = "下降";

            simpleButton31.Text = "上升";
            simpleButton30.Text = "下降";

            simpleButton45.Text = "上升";
            simpleButton44.Text = "下降";

            simpleButton41.Text = "上升";
            simpleButton40.Text = "下降";

            simpleButton53.Text = "上升";
            simpleButton52.Text = "下降";

            simpleButton49.Text = "上升";
            simpleButton48.Text = "下降";

            simpleButton61.Text = "上升";
            simpleButton60.Text = "下降";

            simpleButton57.Text = "上升";
            simpleButton56.Text = "下降";

            simpleButton98.Text = "上升";
            simpleButton97.Text = "下降";

            simpleButton94.Text = "上升";
            simpleButton93.Text = "下降";

            simpleButton67.Text = "上升";
            simpleButton66.Text = "下降";

            simpleButton65.Text = "固定";
            simpleButton64.Text = "松开";

            //前进
            //后退

            //固定
            //松开

            simpleButton29.Text = "前进";
            simpleButton28.Text = "后退";

            simpleButton22.Text = "上升";
            simpleButton23.Text = "下降";

            simpleButton27.Text = "固定";
            simpleButton26.Text = "松开";

            simpleButton88.Text = "上升";
            simpleButton83.Text = "下降";

            simpleButton82.Text = "上升";
            simpleButton81.Text = "下降";

            simpleButton80.Text = "排出";
            simpleButton79.Text = "输入";  
            
            simpleButton33.Text = "防旋转 ON";
            simpleButton32.Text = "防旋转 OFF";

            simpleButton43.Text = "防旋转 ON";
            simpleButton42.Text = "防旋转 OFF";

            simpleButton51.Text = "防旋转 ON";
            simpleButton50.Text = "防旋转 OFF";

            simpleButton59.Text = "防旋转 ON";
            simpleButton58.Text = "防旋转 OFF";

            simpleButton96.Text = "防旋转 ON";
            simpleButton95.Text = "防旋转 OFF";

            simpleButton3.Text = "选择位置移动";
            simpleButton90.Text = "当前位置保存\r\n(OFFSET)";
            simpleButton2.Text = "当前位置保存";


            simpleButton11.Text = "选择位置移动 [ 1号 ]";
            simpleButton14.Text = "选择位置移动 [ 2号 ]";
            simpleButton12.Text = "当前位置保存 [ 1号 ]";
            simpleButton13.Text = "当前位置保存 [ 2号 ]";

            tabPage1.Text = " [工程 #1] 输入 ";
            tabPage2.Text = " [工程 #2] ST #1 ";
            tabPage8.Text = " [工程 #2] ST #2 ";
            tabPage9.Text = " [工程 #2] ST #3 ";
            tabPage10.Text = " [工程 #2] ST #4 ";
            tabPage7.Text = " [工程 #2] ST #5 ";
            tabPage3.Text = " [工程 #3] HIPOT ";
            tabPage4.Text = " [工程 #4] EOL ";
            tabPage5.Text = " [工程 #5] 排出 ";
            tabPage6.Text = " ETC ";


            label190.Text = "顶部标签检查";
            label189.Text = "正面标签检查";

            simpleButton77.Text = "正面标签检查";
            simpleButton78.Text = "顶部标签检查";

            simpleButton18.Text = "选择位置移动";
            simpleButton16.Text = "当前位置保存";

        }

        // 타이머
        private void timer1_Tick(object sender, EventArgs e)
        {
            label3.Text = _ModelInfo.strModelName;

            label298.Text = _SysInfo.nST2EncoderX.ToString();
            label297.Text = _SysInfo.nST2EncoderY.ToString();

            // 거리 측정 유닛 거리 표시
            label287.Text = Program._TesterDistance.dbDistance[1].ToString("F2");
            label251.Text = Program._TesterDistance.dbDistance[0].ToString("F2");

            label161.BackColor = _SysInfo.bStationAutoMode[(int)STATION_LIST.LOADING] ? Color.LightGreen : Color.DarkGreen;
            label161.Text = _SysInfo.bStationAutoMode[(int)STATION_LIST.LOADING] ? "Auto" : "Manual";

            label169.BackColor = _SysInfo.bStationAutoMode[(int)STATION_LIST.IN_LIFT] ? Color.LightGreen : Color.DarkGreen;
            label169.Text = _SysInfo.bStationAutoMode[(int)STATION_LIST.IN_LIFT] ? "Auto" : "Manual";

            label53.BackColor = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST1] ? Color.LightGreen : Color.DarkGreen;
            label53.Text = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST1] ? "Auto" : "Manual";

            label57.BackColor = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST2] ? Color.LightGreen : Color.DarkGreen;
            label57.Text = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST2] ? "Auto" : "Manual";

            label78.BackColor = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST3] ? Color.LightGreen : Color.DarkGreen;
            label78.Text = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST3] ? "Auto" : "Manual";

            label100.BackColor = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST4] ? Color.LightGreen : Color.DarkGreen;
            label100.Text = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST4] ? "Auto" : "Manual";

            label216.BackColor = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST5] ? Color.LightGreen : Color.DarkGreen;
            label216.Text = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST5] ? "Auto" : "Manual";

            label163.BackColor = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST6] ? Color.LightGreen : Color.DarkGreen;
            label163.Text = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST6] ? "Auto" : "Manual";

            label165.BackColor = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7] ? Color.LightGreen : Color.DarkGreen;
            label165.Text = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7] ? "Auto" : "Manual";

            label167.BackColor = _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING] ? Color.LightGreen : Color.DarkGreen;
            label167.Text = _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING] ? "Auto" : "Manual";


            label40.BackColor = Program.GetDIOPort(DI.CMA_LOADING_CLAMP1_ON) ? Color.LightGreen : Color.DarkGreen;
            label54.BackColor = Program.GetDIOPort(DI.CMA_LOADING_CLAMP2_ON) ? Color.LightGreen : Color.DarkGreen;
            label56.BackColor = Program.GetDIOPort(DI.CMA_LOADING_CLAMP1_OFF) ? Color.LightGreen : Color.DarkGreen;
            label55.BackColor = Program.GetDIOPort(DI.CMA_LOADING_CLAMP2_OFF) ? Color.LightGreen : Color.DarkGreen;

            label171.BackColor = Program.GetDIOPort(DI.INLIFT_PALLET_END) ? Color.LightGreen : Color.DarkGreen;
            label157.BackColor = Program.GetDIOPort(DI.INLIFT_PRODUCT_BASEPLATE) ? Color.LightGreen : Color.DarkGreen;
            label178.BackColor = Program.GetDIOPort(DI.INLIFT_PRODUCT_CMA) ? Color.LightGreen : Color.DarkGreen;

            label183.BackColor = Program.GetDIOPort(DI.MAIN_DOOR1) ? Color.LightGreen : Color.DarkGreen;
            label182.BackColor = Program.GetDIOPort(DI.MAIN_DOOR2) ? Color.LightGreen : Color.DarkGreen;
            label181.BackColor = Program.GetDIOPort(DI.MAIN_DOOR3) ? Color.LightGreen : Color.DarkGreen;

            label186.BackColor = Program.GetDIOPort(DI.UNDER_CV_PALLET_FULL) ? Color.LightGreen : Color.DarkGreen;
            label185.BackColor = Program.GetDIOPort(DI.BETWEEN_INLIFT_CV) ? Color.LightGreen : Color.DarkGreen;


            label47.BackColor = Program.GetDIOPort(DI.STATION1_TIP1) ? Color.LightGreen : Color.DarkGreen;
            label48.BackColor = Program.GetDIOPort(DI.STATION1_TIP2) ? Color.LightGreen : Color.DarkGreen;
            label49.BackColor = Program.GetDIOPort(DI.STATION1_TIP3) ? Color.LightGreen : Color.DarkGreen;
            label50.BackColor = Program.GetDIOPort(DI.STATION1_TIP4) ? Color.LightGreen : Color.DarkGreen;
            label51.BackColor = Program.GetDIOPort(DI.STATION1_TIP5) ? Color.LightGreen : Color.DarkGreen;

            label63.BackColor = Program.GetDIOPort(DI.STATION2_TIP1) ? Color.LightGreen : Color.DarkGreen;
            label62.BackColor = Program.GetDIOPort(DI.STATION2_TIP2) ? Color.LightGreen : Color.DarkGreen;
            label61.BackColor = Program.GetDIOPort(DI.STATION2_TIP3) ? Color.LightGreen : Color.DarkGreen;
            label60.BackColor = Program.GetDIOPort(DI.STATION2_TIP4) ? Color.LightGreen : Color.DarkGreen;
            label59.BackColor = Program.GetDIOPort(DI.STATION2_TIP5) ? Color.LightGreen : Color.DarkGreen;

            label84.BackColor = Program.GetDIOPort(DI.STATION3_TIP1) ? Color.LightGreen : Color.DarkGreen;
            label83.BackColor = Program.GetDIOPort(DI.STATION3_TIP2) ? Color.LightGreen : Color.DarkGreen;
            label82.BackColor = Program.GetDIOPort(DI.STATION3_TIP3) ? Color.LightGreen : Color.DarkGreen;
            label81.BackColor = Program.GetDIOPort(DI.STATION3_TIP4) ? Color.LightGreen : Color.DarkGreen;
            label80.BackColor = Program.GetDIOPort(DI.STATION3_TIP5) ? Color.LightGreen : Color.DarkGreen;

            label106.BackColor = Program.GetDIOPort(DI.STATION4_TIP1) ? Color.LightGreen : Color.DarkGreen;
            label105.BackColor = Program.GetDIOPort(DI.STATION4_TIP2) ? Color.LightGreen : Color.DarkGreen;
            label104.BackColor = Program.GetDIOPort(DI.STATION4_TIP3) ? Color.LightGreen : Color.DarkGreen;
            label103.BackColor = Program.GetDIOPort(DI.STATION4_TIP4) ? Color.LightGreen : Color.DarkGreen;
            label102.BackColor = Program.GetDIOPort(DI.STATION4_TIP5) ? Color.LightGreen : Color.DarkGreen;

            label222.BackColor = Program.GetDIOPort(DI.STATION5_TIP1) ? Color.LightGreen : Color.DarkGreen;
            label221.BackColor = Program.GetDIOPort(DI.STATION5_TIP2) ? Color.LightGreen : Color.DarkGreen;
            label220.BackColor = Program.GetDIOPort(DI.STATION5_TIP3) ? Color.LightGreen : Color.DarkGreen;
            label219.BackColor = Program.GetDIOPort(DI.STATION5_TIP4) ? Color.LightGreen : Color.DarkGreen;
            label218.BackColor = Program.GetDIOPort(DI.STATION5_TIP5) ? Color.LightGreen : Color.DarkGreen;


            label35.BackColor = Program.GetDIOPort(DI.STATION1_PALLET) ? Color.LightGreen : Color.DarkGreen;
            label42.BackColor = Program.GetDIOPort(DI.STATION1_CENTER) ? Color.LightGreen : Color.DarkGreen;
            label43.BackColor = Program.GetDIOPort(DI.STATION1_FOOT_SW) ? Color.LightGreen : Color.DarkGreen;
            label44.BackColor = Program.GetDIOPort(DI.STATION1_FINISH_SW) ? Color.LightGreen : Color.DarkGreen;

            label69.BackColor = Program.GetDIOPort(DI.STATION2_PALLET) ? Color.LightGreen : Color.DarkGreen;
            label68.BackColor = Program.GetDIOPort(DI.STATION2_CENTER) ? Color.LightGreen : Color.DarkGreen;
            label67.BackColor = Program.GetDIOPort(DI.STATION2_FOOT_SW) ? Color.LightGreen : Color.DarkGreen;
            label66.BackColor = Program.GetDIOPort(DI.STATION2_FINISH_SW) ? Color.LightGreen : Color.DarkGreen;

            label91.BackColor = Program.GetDIOPort(DI.STATION3_PALLET) ? Color.LightGreen : Color.DarkGreen;
            label90.BackColor = Program.GetDIOPort(DI.STATION3_CENTER) ? Color.LightGreen : Color.DarkGreen;
            label89.BackColor = Program.GetDIOPort(DI.STATION3_FOOT_SW) ? Color.LightGreen : Color.DarkGreen;
            label88.BackColor = Program.GetDIOPort(DI.STATION3_FINISH_SW) ? Color.LightGreen : Color.DarkGreen;

            label112.BackColor = Program.GetDIOPort(DI.STATION4_PALLET) ? Color.LightGreen : Color.DarkGreen;
            label111.BackColor = Program.GetDIOPort(DI.STATION4_CENTER) ? Color.LightGreen : Color.DarkGreen;
            label110.BackColor = Program.GetDIOPort(DI.STATION4_FOOT_SW) ? Color.LightGreen : Color.DarkGreen;
            label109.BackColor = Program.GetDIOPort(DI.STATION4_FINISH_SW) ? Color.LightGreen : Color.DarkGreen;

            label228.BackColor = Program.GetDIOPort(DI.STATION5_PALLET) ? Color.LightGreen : Color.DarkGreen;
            label227.BackColor = Program.GetDIOPort(DI.STATION5_CENTER) ? Color.LightGreen : Color.DarkGreen;
            label226.BackColor = Program.GetDIOPort(DI.STATION5_FOOT_SW) ? Color.LightGreen : Color.DarkGreen;
            label225.BackColor = Program.GetDIOPort(DI.STATION5_FINISH_SW) ? Color.LightGreen : Color.DarkGreen;


            label126.BackColor = Program.GetDIOPort(DI.HIPOT_PALLET) ? Color.LightGreen : Color.DarkGreen;
            label125.BackColor = Program.GetDIOPort(DI.HIPOT_PRODUCT) ? Color.LightGreen : Color.DarkGreen;
            label124.BackColor = Program.GetDIOPort(DI.MAIN_DOOR1) ? Color.LightGreen : Color.DarkGreen;

            label85.BackColor = Program.GetDIOPort(DI.EOL_PALLET) ? Color.LightGreen : Color.DarkGreen;
            label26.BackColor = Program.GetDIOPort(DI.EOL_PRODUCT) ? Color.LightGreen : Color.DarkGreen;
            label27.BackColor = Program.GetDIOPort(DI.MAIN_DOOR2) ? Color.LightGreen : Color.DarkGreen;


            label197.BackColor = Program.GetDIOPort(DI.RELIFT_PALLET_END) ? Color.LightGreen : Color.DarkGreen;
            label196.BackColor = Program.GetDIOPort(DI.RELIFT_CAN_CABLE_CHECK) ? Color.LightGreen : Color.DarkGreen;
            label188.BackColor = Program.GetDIOPort(DI.UNDER_CV_PALLET_FULL) ? Color.LightGreen : Color.DarkGreen;
            label187.BackColor = Program.GetDIOPort(DI.BETWEEN_RELIFT_CV) ? Color.LightGreen : Color.DarkGreen;


            simpleButton19.Image = _SysInfo.bStationAutoMode[(int)STATION_LIST.LOADING] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton17.Image = !_SysInfo.bStationAutoMode[(int)STATION_LIST.LOADING] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;


            simpleButton69.Image = _SysInfo.bStationAutoMode[(int)STATION_LIST.IN_LIFT] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton68.Image = !_SysInfo.bStationAutoMode[(int)STATION_LIST.IN_LIFT] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;

            simpleButton37.Image = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST1] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton36.Image = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST1] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;

            simpleButton39.Image = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST2] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton38.Image = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST2] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;

            simpleButton47.Image = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST3] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton46.Image = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST3] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;

            simpleButton55.Image = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST4] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton54.Image = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST4] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;

            simpleButton92.Image = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST5] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton91.Image = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST5] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;


            simpleButton21.Image = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST6] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton20.Image = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST6] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;

            simpleButton25.Image = _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton24.Image = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST7] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;

            simpleButton63.Image = _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton62.Image = !_SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING] ? Properties.Resources.checksample3 : Properties.Resources.checksample5;


            simpleButton74.Image = Program.GetDIOPortStat(DO.INLIFT_UP) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton73.Image = Program.GetDIOPortStat(DO.INLIFT_DW) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;

            simpleButton72.Image = Program.GetDIOPortStat(DO.INLIFT_PALLET_UP) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton71.Image = Program.GetDIOPortStat(DO.INLIFT_PALLET_DW) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;

            simpleButton6.Image = Program.GetDIOPortStat(DO.INLIFT_CV_ON) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton5.Image = Program.GetDIOPortStat(DO.INLIFT_CV_REV) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;

            simpleButton80.Image = Program.GetDIOPortStat(DO.RELIFT_CV_ON) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton79.Image = Program.GetDIOPortStat(DO.RELIFT_CV_REV) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;

            simpleButton76.Image = !Program.GetDIOPortStat(DO.UNDER_CV_STOPPER_DW) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton75.Image = Program.GetDIOPortStat(DO.UNDER_CV_STOPPER_DW) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;

            simpleButton70.Image = Program.GetDIOPortStat(DO.CMA_LOADING_CLAMP_ON) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton10.Image = Program.GetDIOPortStat(DO.CMA_LOADING_CLAMP_OFF) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;


            simpleButton35.Image = Program.GetDIOPortStat(DO.STATION1_PALLET_UP) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton34.Image = Program.GetDIOPortStat(DO.STATION1_PALLET_DW) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton33.Image = !Program.GetDIOPortStat(DO.STATION1_LOCK_OFF) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton32.Image = Program.GetDIOPortStat(DO.STATION1_LOCK_OFF) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton31.Image = !Program.GetDIOPortStat(DO.STATION1_STOPPER_DW) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton30.Image = Program.GetDIOPortStat(DO.STATION1_STOPPER_DW) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;

            simpleButton45.Image = Program.GetDIOPortStat(DO.STATION2_PALLET_UP) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton44.Image = Program.GetDIOPortStat(DO.STATION2_PALLET_DW) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton43.Image = !Program.GetDIOPortStat(DO.STATION2_LOCK_OFF) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton42.Image = Program.GetDIOPortStat(DO.STATION2_LOCK_OFF) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton41.Image = !Program.GetDIOPortStat(DO.STATION2_STOPPER_DW) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton40.Image = Program.GetDIOPortStat(DO.STATION2_STOPPER_DW) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;

            simpleButton53.Image = Program.GetDIOPortStat(DO.STATION3_PALLET_UP) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton52.Image = Program.GetDIOPortStat(DO.STATION3_PALLET_DW) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton51.Image = !Program.GetDIOPortStat(DO.STATION3_LOCK_OFF) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton50.Image = Program.GetDIOPortStat(DO.STATION3_LOCK_OFF) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton49.Image = !Program.GetDIOPortStat(DO.STATION3_STOPPER_DW) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton48.Image = Program.GetDIOPortStat(DO.STATION3_STOPPER_DW) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;

            simpleButton61.Image = Program.GetDIOPortStat(DO.STATION4_PALLET_UP) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton60.Image = Program.GetDIOPortStat(DO.STATION4_PALLET_DW) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton59.Image = !Program.GetDIOPortStat(DO.STATION4_LOCK_OFF) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton58.Image = Program.GetDIOPortStat(DO.STATION4_LOCK_OFF) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton57.Image = !Program.GetDIOPortStat(DO.STATION4_STOPPER_DW) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton56.Image = Program.GetDIOPortStat(DO.STATION4_STOPPER_DW) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;

            simpleButton98.Image = Program.GetDIOPortStat(DO.STATION5_PALLET_UP) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton97.Image = Program.GetDIOPortStat(DO.STATION5_PALLET_DW) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton96.Image = !Program.GetDIOPortStat(DO.STATION5_LOCK_OFF) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton95.Image = Program.GetDIOPortStat(DO.STATION5_LOCK_OFF) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton94.Image = !Program.GetDIOPortStat(DO.STATION5_STOPPER_DW) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton93.Image = Program.GetDIOPortStat(DO.STATION5_STOPPER_DW) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;



            simpleButton67.Image = Program.GetDIOPortStat(DO.HIPOT_PALLET_UP) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton66.Image = Program.GetDIOPortStat(DO.HIPOT_PALLET_DW) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;

            simpleButton65.Image = Program.GetDIOPortStat(DO.HIPOT_PRODUCT_PUSH_ON) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton64.Image = !Program.GetDIOPortStat(DO.HIPOT_PRODUCT_PUSH_ON) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;

            simpleButton22.Image = Program.GetDIOPortStat(DO.EOL_PALLET_UP) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton23.Image = Program.GetDIOPortStat(DO.EOL_PALLET_DW) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
                             
            simpleButton27.Image = Program.GetDIOPortStat(DO.EOL_PRODUCT_PUSH_ON) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton26.Image = !Program.GetDIOPortStat(DO.EOL_PRODUCT_PUSH_ON) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;

            simpleButton29.Image = Program.GetDIOPortStat(DO.EOL_CAN_CONTACT_ON) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton28.Image = !Program.GetDIOPortStat(DO.EOL_CAN_CONTACT_ON) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;

            simpleButton88.Image = Program.GetDIOPortStat(DO.RELIFT_UP) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton83.Image = Program.GetDIOPortStat(DO.RELIFT_DW) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;

            simpleButton82.Image = Program.GetDIOPortStat(DO.RELIFT_PALLET_UP) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;
            simpleButton81.Image = Program.GetDIOPortStat(DO.RELIFT_PALLET_DW) ? Properties.Resources.checksample3 : Properties.Resources.checksample5;



            if(_Config.strLangue == "CHINA")
            {

            }
            

            double dbPose = 0.0;


            CAXM.AxmStatusGetCmdPos((int)AXIS.X, ref dbPose);
            label140.Text = dbPose.ToString("F2");

            CAXM.AxmStatusGetCmdPos((int)AXIS.Y, ref dbPose);
            label138.Text = dbPose.ToString("F2");

            CAXM.AxmStatusGetCmdPos((int)AXIS.Z, ref dbPose);
            label136.Text = dbPose.ToString("F2");

            CAXM.AxmStatusGetCmdPos((int)AXIS.R, ref dbPose);
            label159.Text = (-dbPose).ToString("F2");


            CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_1X, ref dbPose);
            label148.Text = dbPose.ToString("F2");

            CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_1Y, ref dbPose);
            label146.Text = dbPose.ToString("F2");

            CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_1Z, ref dbPose);
            label144.Text = dbPose.ToString("F2");


            CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_2X, ref dbPose);
            label156.Text = dbPose.ToString("F2");

            CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_2Y, ref dbPose);
            label154.Text = dbPose.ToString("F2");

            CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_2Z, ref dbPose);
            label152.Text = dbPose.ToString("F2");


            CAXM.AxmStatusGetCmdPos((int)AXIS.EOL_X, ref dbPose);
            label15.Text = dbPose.ToString("F2");

            CAXM.AxmStatusGetCmdPos((int)AXIS.EOL_Y, ref dbPose);
            label11.Text = dbPose.ToString("F2");

            CAXM.AxmStatusGetCmdPos((int)AXIS.EOL_Z, ref dbPose);
            label13.Text = dbPose.ToString("F2");

            CAXM.AxmStatusGetCmdPos((int)AXIS.CAMERA1_X, ref dbPose);
            label293.Text = String.Format("{0:F2}", dbPose);

            CAXM.AxmStatusGetCmdPos((int)AXIS.CAMERA1_Y, ref dbPose);
            label291.Text = String.Format("{0:F2}", dbPose);

            CAXM.AxmStatusGetCmdPos((int)AXIS.CAMERA1_Z, ref dbPose);
            label289.Text = String.Format("{0:F2}", dbPose);


            CAXM.AxmStatusGetCmdPos((int)AXIS.CAMERA2_X, ref dbPose);
            label284.Text = String.Format("{0:F2}", dbPose);

            CAXM.AxmStatusGetCmdPos((int)AXIS.CAMERA2_Y, ref dbPose);
            label282.Text = String.Format("{0:F2}", dbPose);

            CAXM.AxmStatusGetCmdPos((int)AXIS.CAMERA2_Z, ref dbPose);
            label280.Text = String.Format("{0:F2}", dbPose);

            //CAXM.AxmStatusGetActPos((int)AXIS.ST3_R, ref dbPose);
            //label239.Text = dbPose.ToString("F2");


            // 컨트롤 잠금 및 해제
            panel1.Enabled = !_SysInfo.bStationAutoMode[(int)STATION_LIST.LOADING];
            panel15.Enabled = !_SysInfo.bStationAutoMode[(int)STATION_LIST.LOADING];
            panel23.Enabled = !_SysInfo.bStationAutoMode[(int)STATION_LIST.LOADING];

            panel24.Enabled = !_SysInfo.bStationAutoMode[(int)STATION_LIST.IN_LIFT];

            panel6.Enabled = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST1];
            panel9.Enabled = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST2];
            panel11.Enabled = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST3];
            panel13.Enabled = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST4];
            panel32.Enabled = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST5];

            panel3.Enabled = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST6];
            panel26.Enabled = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST6];
            panel14.Enabled = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST6];
            panel16.Enabled = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST6];
            panel17.Enabled = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST6];
            panel29.Enabled = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST6];
            panel28.Enabled = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST6];

            panel4.Enabled = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST7];
            panel27.Enabled = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST7];
            panel5.Enabled = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST7];
            panel2.Enabled = !_SysInfo.bStationAutoMode[(int)STATION_LIST.ST7];

            panel25.Enabled = !_SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING];
        }



        private void ModelSetup_Load(object sender, EventArgs e)
        {
            ViewLockingSTInfo();
            LoadingInfoView();
            HipotInfoView();
            PointInfoView();
            ETCDataView();
          //  TPCDataView();
            SpeedDataView();
            CommentNEtcView();
            ChinaLangSet();
            BcdDataView();
            dataGridView1.DoubleBuffered(true);


            radioButton4.Checked = _ModelInfo.bUseAutoContect;
            radioButton5.Checked = _ModelInfo.bUseManualContect;


            checkBox28.Checked = _ModelInfo.bLockingStationSkip[0];
            checkBox27.Checked = _ModelInfo.bLockingStationSkip[1];
            checkBox26.Checked = _ModelInfo.bLockingStationSkip[2];
            checkBox25.Checked = _ModelInfo.bLockingStationSkip[3];
            checkBox24.Checked = _ModelInfo.bLockingStationSkip[4];

            checkBox11.Checked = _ModelInfo.bHipotSkip;
            checkBox12.Checked = _ModelInfo.bEolSkip;

            timer1.Interval = 100;
            timer1.Start();

            if(_Config.strLangue != "KOR")
            {
                simpleButton133.Text = "距离基准设置";
                simpleButton109.Text = "距离基准设置";
            }
        }

        private void simpleButton5_Click(object sender, EventArgs e)
        {
            Program.nProcessStep[(int)PROC_LIST.MANUAL] = 1000;
        }

        private void simpleButton6_Click(object sender, EventArgs e)
        {
            Program.nProcessStep[(int)PROC_LIST.MANUAL] = 1100;
        }

        private void simpleButton19_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.LOADING] = true;
        }

        private void simpleButton17_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.LOADING] = false;
        }

        private void simpleButton69_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.IN_LIFT] = true; 
        }

        private void simpleButton68_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.IN_LIFT] = false;
        }

        private void simpleButton37_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST1] = true; 
        }

        private void simpleButton36_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST1] = false; 
        }

        private void simpleButton39_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST2] = true; 
        }

        private void simpleButton38_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST2] = false;
        }

        private void simpleButton47_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST3] = true;
        }

        private void simpleButton46_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST3] = false;
        }

        private void simpleButton55_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST4] = true;
        }

        private void simpleButton54_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST4] = false;
        }

        private void simpleButton21_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST6] = true;
        }

        private void simpleButton20_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST6] = false;
        }

        private void simpleButton25_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7] = true;
        }

        private void simpleButton24_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST7] = false;
        }

        private void simpleButton63_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING] = true;
        }

        private void simpleButton62_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.UNLOADING] = false;
        }

        private void simpleButton80_Click(object sender, EventArgs e)
        {
            Program.nProcessStep[(int)PROC_LIST.MANUAL] = 1300;
        }

        private void simpleButton79_Click(object sender, EventArgs e)
        {
            Program.nProcessStep[(int)PROC_LIST.MANUAL] = 1200;
        }












        // 저장 & 닫기 버튼
        private void simpleButton9_Click(object sender, EventArgs e)
        {
            SaveLocingSTInfo();
            LoadingInfoLoad();
            HipotInfoLoad();
            PointInfoLoad();
            EtcDataLoad();
           // TPCDataLoad();
            SpeedDataLoad();
            CommentNEtcLoad();
            BcdDataLoad();

            _ModelInfo.bUseAutoContect = radioButton4.Checked;
            _ModelInfo.bUseManualContect = radioButton5.Checked;


            _ModelInfo.bLockingStationSkip[0] = checkBox28.Checked;
            _ModelInfo.bLockingStationSkip[1] = checkBox27.Checked;
            _ModelInfo.bLockingStationSkip[2] = checkBox26.Checked;
            _ModelInfo.bLockingStationSkip[3] = checkBox25.Checked;
            _ModelInfo.bLockingStationSkip[4] = checkBox24.Checked;
            
            _ModelInfo.bHipotSkip = checkBox11.Checked;
            _ModelInfo.bEolSkip = checkBox12.Checked;
            Program._ModelInfo = _ModelInfo.CopyJsons<MODEL_INFO>();
            Program.SaveModelInfo(Program._ModelInfo, Program._ModelInfo.strModelName);
            Program.SaveWorkPageInI(Program._ModelInfo.strModelName);
            this.Close();
        }




        // 저장 버튼
        private void simpleButton7_Click(object sender, EventArgs e)
        {
            SaveLocingSTInfo();
            LoadingInfoLoad();
            HipotInfoLoad();
            PointInfoLoad();
            EtcDataLoad();
           // TPCDataLoad();
            SpeedDataLoad();
            CommentNEtcLoad();
            BcdDataLoad();

            _ModelInfo.bUseAutoContect = radioButton4.Checked;
            _ModelInfo.bUseManualContect = radioButton5.Checked;


           _ModelInfo.bLockingStationSkip[0] = checkBox28.Checked;
           _ModelInfo.bLockingStationSkip[1] = checkBox27.Checked;
           _ModelInfo.bLockingStationSkip[2] = checkBox26.Checked;
           _ModelInfo.bLockingStationSkip[3] = checkBox25.Checked;
           _ModelInfo.bLockingStationSkip[4] = checkBox24.Checked;

           _ModelInfo.bHipotSkip = checkBox11.Checked;
           _ModelInfo.bEolSkip = checkBox12.Checked;

            Program._ModelInfo = _ModelInfo.CopyJsons<MODEL_INFO>();
            Program.SaveModelInfo(Program._ModelInfo, Program._ModelInfo.strModelName);
            Program.SaveWorkPageInI(Program._ModelInfo.strModelName);
        }

        private void simpleButton74_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.INLIFT_UP, true);
            Program.SetDIOPort(DO.INLIFT_DW, false);
        }

        private void simpleButton73_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.INLIFT_UP, false);
            Program.SetDIOPort(DO.INLIFT_DW, true);
        }

        private void simpleButton72_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.INLIFT_PALLET_UP, true);
            Program.SetDIOPort(DO.INLIFT_PALLET_DW, false);
        }

        private void simpleButton71_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.INLIFT_PALLET_UP, false);
            Program.SetDIOPort(DO.INLIFT_PALLET_DW, true);
        }

        private void simpleButton76_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.UNDER_CV_STOPPER_DW, false);
        }

        private void simpleButton75_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.UNDER_CV_STOPPER_DW, true);
        }

        private void simpleButton70_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.CMA_LOADING_CLAMP_ON, true);
            Program.SetDIOPort(DO.CMA_LOADING_CLAMP_OFF, false);
        }

        private void simpleButton10_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.CMA_LOADING_CLAMP_ON, false);
            Program.SetDIOPort(DO.CMA_LOADING_CLAMP_OFF, true);
        }

        private void simpleButton35_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION1_PALLET_UP, true);
            Program.SetDIOPort(DO.STATION1_PALLET_DW, false);
        }

        private void simpleButton34_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION1_PALLET_UP, false);
            Program.SetDIOPort(DO.STATION1_PALLET_DW, true);
        }

        private void simpleButton33_Click(object sender, EventArgs e)
        {
            if(Program.GetDIOPort(DI.STATION1_CENTER))
            {
                Program.SetDIOPort(DO.STATION1_BREAK_OFF, true);
                Program.SetDIOPort(DO.STATION1_LOCK_OFF, false);
            }
            else
            {
                Program.SetDIOPort(DO.STATION1_BREAK_OFF, false);
                Program.SetDIOPort(DO.STATION1_LOCK_OFF, true);
            }
            
        }

        private void simpleButton32_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION1_BREAK_OFF, true);
            Program.SetDIOPort(DO.STATION1_LOCK_OFF, true);
        }

        private void simpleButton31_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION1_STOPPER_DW, false);
        }

        private void simpleButton30_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION1_STOPPER_DW, true);
        }

        private void simpleButton45_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION2_PALLET_UP, true);
            Program.SetDIOPort(DO.STATION2_PALLET_DW, false);
        }

        private void simpleButton44_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION2_PALLET_UP, false);
            Program.SetDIOPort(DO.STATION2_PALLET_DW, true);
        }

        private void simpleButton43_Click(object sender, EventArgs e)
        {
            if (Program.GetDIOPort(DI.STATION2_CENTER))
            {
                Program.SetDIOPort(DO.STATION2_BREAK_OFF, true);
                Program.SetDIOPort(DO.STATION2_LOCK_OFF, false);
            }
            else
            {
                Program.SetDIOPort(DO.STATION2_BREAK_OFF, false);
                Program.SetDIOPort(DO.STATION2_LOCK_OFF, true);
            }

        }

        private void simpleButton42_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION2_BREAK_OFF, true);
            Program.SetDIOPort(DO.STATION2_LOCK_OFF, true);
        }

        private void simpleButton41_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION2_STOPPER_DW, false);
        }

        private void simpleButton40_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION2_STOPPER_DW, true);
        }

        private void simpleButton53_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION3_PALLET_UP, true);
            Program.SetDIOPort(DO.STATION3_PALLET_DW, false);
        }

        private void simpleButton52_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION3_PALLET_UP, false);
            Program.SetDIOPort(DO.STATION3_PALLET_DW, true);
        }

        private void simpleButton51_Click(object sender, EventArgs e)
        {
            if (Program.GetDIOPort(DI.STATION3_CENTER))
            {
                Program.SetDIOPort(DO.STATION3_BREAK_OFF, true);
                Program.SetDIOPort(DO.STATION3_LOCK_OFF, false);
            }
            else
            {
                Program.SetDIOPort(DO.STATION3_BREAK_OFF, false);
                Program.SetDIOPort(DO.STATION3_LOCK_OFF, true);
            }
        }

        private void simpleButton50_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION3_BREAK_OFF, true);
            Program.SetDIOPort(DO.STATION3_LOCK_OFF, true);
        }

        private void simpleButton49_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION3_STOPPER_DW, false);
        }

        private void simpleButton48_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION3_STOPPER_DW, true);
        }

        private void simpleButton61_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION4_PALLET_UP, true);
            Program.SetDIOPort(DO.STATION4_PALLET_DW, false);
        }

        private void simpleButton60_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION4_PALLET_UP, false);
            Program.SetDIOPort(DO.STATION4_PALLET_DW, true);
        }

        private void simpleButton59_Click(object sender, EventArgs e)
        {
            if (Program.GetDIOPort(DI.STATION4_CENTER))
            {
                Program.SetDIOPort(DO.STATION4_BREAK_OFF, true);
                Program.SetDIOPort(DO.STATION4_LOCK_OFF, false);
            }
            else
            {
                Program.SetDIOPort(DO.STATION4_BREAK_OFF, false);
                Program.SetDIOPort(DO.STATION4_LOCK_OFF, true);
            }
        }

        private void simpleButton58_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION4_BREAK_OFF, true);
            Program.SetDIOPort(DO.STATION4_LOCK_OFF, true);
        }

        private void simpleButton57_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION4_STOPPER_DW, false);
        }

        private void simpleButton56_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION4_STOPPER_DW, true);
        }

        private void simpleButton67_Click(object sender, EventArgs e)
        {

            if (!Program.GetDIOPort(DI.HIPOT_PRODUCT_PUSH1_OFF) || !Program.GetDIOPort(DI.HIPOT_PRODUCT_PUSH2_OFF))
            {
                MessageBox.Show("제품 고정상태 입니다");
                return;
            }



            Program.SetDIOPort(DO.HIPOT_PALLET_UP, true);
            Program.SetDIOPort(DO.HIPOT_PALLET_DW, false);
        }

        private void simpleButton66_Click(object sender, EventArgs e)
        {
            if (!Program.GetDIOPort(DI.HIPOT_PRODUCT_PUSH1_OFF) || !Program.GetDIOPort(DI.HIPOT_PRODUCT_PUSH1_OFF))
            {
                MessageBox.Show("제품 고정상태 입니다");
                return;
            }



            Program.SetDIOPort(DO.HIPOT_PALLET_UP, false);
            Program.SetDIOPort(DO.HIPOT_PALLET_DW, true);
        }

        private void simpleButton65_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.HIPOT_PRODUCT_PUSH_ON, true);
        }

        private void simpleButton64_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.HIPOT_PRODUCT_PUSH_ON, false);
        }

        private void simpleButton22_Click(object sender, EventArgs e)
        {
            if (!Program.GetDIOPort(DI.EOL_CAN_OFF))
            {
                MessageBox.Show("측면 컨택 상태입니다");
                return;
            }

            if (!Program.GetDIOPort(DI.EOL_PRODUCT_PUSH1_OFF) || !Program.GetDIOPort(DI.EOL_PRODUCT_PUSH2_OFF))
            {
                MessageBox.Show("제품 고정상태 입니다");
                return;
            }


            Program.SetDIOPort(DO.EOL_PALLET_UP, true);
            Program.SetDIOPort(DO.EOL_PALLET_DW, false);
        }

        private void simpleButton23_Click(object sender, EventArgs e)
        {
            if (!Program.GetDIOPort(DI.EOL_CAN_OFF))
            {
                MessageBox.Show("측면 컨택 상태입니다");
                return;
            }

            if (!Program.GetDIOPort(DI.EOL_PRODUCT_PUSH1_OFF) || !Program.GetDIOPort(DI.EOL_PRODUCT_PUSH2_OFF))
            {
                MessageBox.Show("제품 고정상태 입니다");
                return;
            }

            Program.SetDIOPort(DO.EOL_PALLET_UP, false);
            Program.SetDIOPort(DO.EOL_PALLET_DW, true);
        }

        private void simpleButton27_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.EOL_PRODUCT_PUSH_ON, true);
        }

        private void simpleButton26_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.EOL_PRODUCT_PUSH_ON, false);
        }

        private void simpleButton29_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.EOL_CAN_CONTACT_ON, true);
        }

        private void simpleButton28_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.EOL_CAN_CONTACT_ON, false);
        }

        private void simpleButton88_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.RELIFT_UP, true);
            Program.SetDIOPort(DO.RELIFT_DW, false);
        }

        private void simpleButton83_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.RELIFT_UP, false);
            Program.SetDIOPort(DO.RELIFT_DW, true);
        }

        private void simpleButton82_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.RELIFT_PALLET_UP, true);
            Program.SetDIOPort(DO.RELIFT_PALLET_DW, false);
        }

        private void simpleButton81_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.RELIFT_PALLET_UP, false);
            Program.SetDIOPort(DO.RELIFT_PALLET_DW, true);
        }

        private void simpleButton3_Click(object sender, EventArgs e)
        {

            dataGridView1.EndEdit();
            if (Program.GetDIOPort(DI.CMA_LOADING_CLAMP1_OFF) && Program.GetDIOPort(DI.CMA_LOADING_CLAMP2_OFF))
            {
                if (dataGridView1.CurrentRow.Index == 0 || dataGridView1.CurrentRow.Index == 2 || dataGridView1.CurrentRow.Index == 3)
                {

                    double.TryParse(dataGridView1[2, dataGridView1.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[0]);
                    double.TryParse(dataGridView1[3, dataGridView1.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[1]);
                    double.TryParse(dataGridView1[4, dataGridView1.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[2]);

                    //_SysInfo.dbManualMovePos[0] = (double)dataGridView1[2, dataGridView1.CurrentRow.Index].Value;
                    //_SysInfo.dbManualMovePos[1] = (double)dataGridView1[3, dataGridView1.CurrentRow.Index].Value;
                    //_SysInfo.dbManualMovePos[2] = (double)dataGridView1[4, dataGridView1.CurrentRow.Index].Value;
                    Program.nProcessStep[(int)PROC_LIST.MANUAL] = 1600;
                }
                else if (dataGridView1.CurrentRow.Index == 1)
                {
                    double.TryParse(dataGridView1[2, dataGridView1.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[0]);
                    double.TryParse(dataGridView1[3, dataGridView1.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[1]);

                    //_SysInfo.dbManualMovePos[0] = (double)dataGridView1[2, dataGridView1.CurrentRow.Index].Value;
                    //_SysInfo.dbManualMovePos[1] = (double)dataGridView1[3, dataGridView1.CurrentRow.Index].Value;
                    Program.nProcessStep[(int)PROC_LIST.MANUAL] = 1800;
                }
                else
                {
                    double.TryParse(dataGridView1[2, dataGridView1.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[0]);
                    double.TryParse(dataGridView1[3, dataGridView1.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[1]);
                    double.TryParse(dataGridView1[4, dataGridView1.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[2]);
                    double.TryParse(dataGridView1[6, dataGridView1.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[3]);
                    double.TryParse(dataGridView1[8, dataGridView1.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[4]);
                    double.TryParse(dataGridView1[7, dataGridView1.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[5]);

                    //_SysInfo.dbManualMovePos[0] = (double)dataGridView1[2, dataGridView1.CurrentRow.Index].Value;
                    //_SysInfo.dbManualMovePos[1] = (double)dataGridView1[3, dataGridView1.CurrentRow.Index].Value;
                    //_SysInfo.dbManualMovePos[2] = (double)dataGridView1[4, dataGridView1.CurrentRow.Index].Value;
                    //_SysInfo.dbManualMovePos[3] = (double)dataGridView1[6, dataGridView1.CurrentRow.Index].Value;
                    //_SysInfo.dbManualMovePos[4] = (double)dataGridView1[8, dataGridView1.CurrentRow.Index].Value;
                    //_SysInfo.dbManualMovePos[5] = (double)dataGridView1[7, dataGridView1.CurrentRow.Index].Value;
                    Program.nProcessStep[(int)PROC_LIST.MANUAL] = 1700;
                }
            }
            else
            {
                if (MessageBox.Show("제품을 클램프 중입니다 클램프 한 상태로 이송하시겠습니까?", "MOVE", MessageBoxButtons.YesNo) == DialogResult.No)
                {
                    return;
                }

                if (dataGridView1.CurrentRow.Index == 0)
                {
      

                    double.TryParse(dataGridView1[2, dataGridView1.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[0]);
                    double.TryParse(dataGridView1[3, dataGridView1.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[1]);
                    double.TryParse(dataGridView1[4, dataGridView1.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[2]);

                    //_SysInfo.dbManualMovePos[0] = (double)dataGridView1[2, dataGridView1.CurrentRow.Index].Value;
                    //_SysInfo.dbManualMovePos[1] = (double)dataGridView1[3, dataGridView1.CurrentRow.Index].Value;
                    //_SysInfo.dbManualMovePos[2] = (double)dataGridView1[4, dataGridView1.CurrentRow.Index].Value;
                    Program.nProcessStep[(int)PROC_LIST.MANUAL] = 1600;
                }
                else if (dataGridView1.CurrentRow.Index == 1)
                {
                    double.TryParse(dataGridView1[2, dataGridView1.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[0]);
                    double.TryParse(dataGridView1[3, dataGridView1.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[1]);

                    //_SysInfo.dbManualMovePos[0] = (double)dataGridView1[2, dataGridView1.CurrentRow.Index].Value;
                    //_SysInfo.dbManualMovePos[1] = (double)dataGridView1[3, dataGridView1.CurrentRow.Index].Value;
                    Program.nProcessStep[(int)PROC_LIST.MANUAL] = 1800;
                }
                else
                {
                    double.TryParse(dataGridView1[2, dataGridView1.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[0]);
                    double.TryParse(dataGridView1[3, dataGridView1.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[1]);
                    double.TryParse(dataGridView1[4, dataGridView1.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[2]);
                    double.TryParse(dataGridView1[6, dataGridView1.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[3]);
                    double.TryParse(dataGridView1[8, dataGridView1.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[4]);
                    double.TryParse(dataGridView1[7, dataGridView1.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[5]);


                    //_SysInfo.dbManualMovePos[0] = (double)dataGridView1[2, dataGridView1.CurrentRow.Index].Value;
                    //_SysInfo.dbManualMovePos[1] = (double)dataGridView1[3, dataGridView1.CurrentRow.Index].Value;
                    //_SysInfo.dbManualMovePos[2] = (double)dataGridView1[4, dataGridView1.CurrentRow.Index].Value;
                    //_SysInfo.dbManualMovePos[3] = (double)dataGridView1[6, dataGridView1.CurrentRow.Index].Value;
                    //_SysInfo.dbManualMovePos[4] = (double)dataGridView1[8, dataGridView1.CurrentRow.Index].Value;
                    //_SysInfo.dbManualMovePos[5] = (double)dataGridView1[7, dataGridView1.CurrentRow.Index].Value;
                    Program.nProcessStep[(int)PROC_LIST.MANUAL] = 1700;
                }

            }
        }

        private void simpleButton2_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("현재 위치를 기억 하시겠습니까?", "Save", MessageBoxButtons.YesNo) == DialogResult.No)
            {
                return;
            }

            double dbPos = 0.0;
            if (dataGridView1.CurrentRow.Index == 1)
            {
                CAXM.AxmStatusGetCmdPos((int)AXIS.X, ref dbPos);
                dataGridView1[2, dataGridView1.CurrentRow.Index].Value = Math.Round(dbPos, 2);

                CAXM.AxmStatusGetCmdPos((int)AXIS.Y, ref dbPos);
                dataGridView1[3, dataGridView1.CurrentRow.Index].Value = Math.Round(dbPos, 2);
            }
            else
            {
                CAXM.AxmStatusGetCmdPos((int)AXIS.X, ref dbPos);
                dataGridView1[2, dataGridView1.CurrentRow.Index].Value = Math.Round(dbPos, 2);


                CAXM.AxmStatusGetCmdPos((int)AXIS.Y, ref dbPos);
                dataGridView1[3, dataGridView1.CurrentRow.Index].Value = Math.Round(dbPos, 2);

                CAXM.AxmStatusGetCmdPos((int)AXIS.Z, ref dbPos);
                dataGridView1[4, dataGridView1.CurrentRow.Index].Value = Math.Round(dbPos, 2);

            }
        }

        private void simpleButton11_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("선택 위치로 이동 하시겠습니까?", "Move", MessageBoxButtons.YesNo) == DialogResult.No)
            {
                return;
            }


            double.TryParse(dataGridView3[1, dataGridView3.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[0]);
            double.TryParse(dataGridView3[2, dataGridView3.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[1]);
            double.TryParse(dataGridView3[3, dataGridView3.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[2]);
            Program.nProcessStep[(int)PROC_LIST.MANUAL] = 2099;
        }

        private void simpleButton12_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("현재 위치를 기억 하시겠습니까?", "Save", MessageBoxButtons.YesNo) == DialogResult.No)
            {
                return;
            }

            double dbPos = 0.0;


            CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_1X, ref dbPos);
            dataGridView3[1, dataGridView3.CurrentRow.Index].Value = Math.Round(dbPos, 2);

            CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_1Y, ref dbPos);
            dataGridView3[2, dataGridView3.CurrentRow.Index].Value = Math.Round(dbPos, 2);

            CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_1Z, ref dbPos);
            dataGridView3[3, dataGridView3.CurrentRow.Index].Value = Math.Round(dbPos, 2);
        }

        private void simpleButton14_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("선택 위치로 이동 하시겠습니까", "Move", MessageBoxButtons.YesNo) == DialogResult.No)
            {
                return;
            }

            double.TryParse(dataGridView3[4, dataGridView3.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[0]);
            double.TryParse(dataGridView3[5, dataGridView3.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[1]);
            double.TryParse(dataGridView3[6, dataGridView3.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[2]);
            Program.nProcessStep[(int)PROC_LIST.MANUAL] = 2200;
        }

        private void simpleButton13_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("현재 위치를 기억 하시겠습니까?", "Save", MessageBoxButtons.YesNo) == DialogResult.No)
            {
                return;
            }

            double dbPos = 0.0;

            CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_2X, ref dbPos);
            dataGridView3[4, dataGridView3.CurrentRow.Index].Value = Math.Round(dbPos, 2);

            CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_2Y, ref dbPos);
            dataGridView3[5, dataGridView3.CurrentRow.Index].Value = Math.Round(dbPos, 2);

            CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_2Z, ref dbPos);
            dataGridView3[6, dataGridView3.CurrentRow.Index].Value = Math.Round(dbPos, 2);
        }

        private void simpleButton18_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("선택 위치로 이동 하시겠습니까?", "Move", MessageBoxButtons.YesNo) == DialogResult.No)
            {
                return;
            }

            double.TryParse(dataGridView4[1, dataGridView4.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[0]);
            double.TryParse(dataGridView4[2, dataGridView4.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[1]);
            double.TryParse(dataGridView4[3, dataGridView4.CurrentRow.Index].Value.ToString(), out  _SysInfo.dbManualMovePos[2]);
            Program.nProcessStep[(int)PROC_LIST.MANUAL] = 2000;
        }

        private void simpleButton16_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("현재 위치를 기억 하시겠습니까?", "Save", MessageBoxButtons.YesNo) == DialogResult.No)
            {
                return;
            }

            double dbPos = 0.0;

            CAXM.AxmStatusGetCmdPos((int)AXIS.EOL_X, ref dbPos);
            dataGridView4[1, dataGridView4.CurrentRow.Index].Value = Math.Round(dbPos, 2);

            CAXM.AxmStatusGetCmdPos((int)AXIS.EOL_Y, ref dbPos);
            dataGridView4[2, dataGridView4.CurrentRow.Index].Value = Math.Round(dbPos, 2);

            CAXM.AxmStatusGetCmdPos((int)AXIS.EOL_Z, ref dbPos);
            dataGridView4[3, dataGridView4.CurrentRow.Index].Value = Math.Round(dbPos, 2);
        }





        private void simpleButton85_Click(object sender, EventArgs e)
        {
            Program.MoveTo(AXIS.R, 90, _Config.dbTurnSpeed);
        }




        public void ViewVisionData(int nStation, string strBCD)
        {

            if (nStation == 0)
            {
                pictureBox3.Refresh();

                FileStream fs = new FileStream(String.Format("{0}.bmp", _Config.strVisionDir1), FileMode.Open);

                pictureBox3.SizeMode = PictureBoxSizeMode.StretchImage;
                pictureBox3.Image = Image.FromStream(fs);

                fs.Close();

            }
            else if (nStation == 1)
            {
                pictureBox2.Refresh();

                FileStream fs = new FileStream(String.Format("{0}.bmp", _Config.strVisionDir2), FileMode.Open);

                pictureBox2.SizeMode = PictureBoxSizeMode.StretchImage;
                pictureBox2.Image = Image.FromStream(fs);

                fs.Close();

            }

        }

        private void simpleButton77_Click(object sender, EventArgs e)
        {
            Program.nProcessStep[(int)PROC_LIST.MANUAL] = 2600;
        }

        private void simpleButton78_Click(object sender, EventArgs e)
        {
            Program.nProcessStep[(int)PROC_LIST.MANUAL] = 2500;
        }

        private void simpleButton86_Click(object sender, EventArgs e)
        {
            Program.MoveTo(AXIS.R, 0, _Config.dbTurnSpeed);
        }

        private void simpleButton87_Click(object sender, EventArgs e)
        {
            Program.MoveTo(AXIS.R, -90, _Config.dbTurnSpeed);
        }

        private void simpleButton84_Click(object sender, EventArgs e)
        {
            Program.MoveTo(AXIS.R, -180, _Config.dbTurnSpeed);
        }

        private void simpleButton1_Click(object sender, EventArgs e)
        {
            SaveLocingSTInfo();
            LoadingInfoLoad();
            HipotInfoLoad();
            PointInfoLoad();
            EtcDataLoad();
          //  TPCDataLoad();
            SpeedDataLoad();
            CommentNEtcLoad();
            BcdDataLoad();

            //_ModelInfo.bUseTopCamera = checkBox2.Checked;
            //_ModelInfo.bUseFrotCamera = checkBox19.Checked;

            //_ModelInfo.bUseHipotBCDScanner = checkBox1.Checked;
            //_ModelInfo.bUseEolBCDScanner = checkBox4.Checked;
            //_ModelInfo.bUseHipotContactTest = checkBox3.Checked;
            //_ModelInfo.bUseEolContactTest = checkBox17.Checked;
            //_ModelInfo.bUseJigTest = checkBox18.Checked;
            _ModelInfo.bUseAutoContect = radioButton4.Checked;
            _ModelInfo.bUseManualContect = radioButton5.Checked;


           _ModelInfo.bLockingStationSkip[0] = checkBox28.Checked;
           _ModelInfo.bLockingStationSkip[1] = checkBox27.Checked;
           _ModelInfo.bLockingStationSkip[2] = checkBox26.Checked;
           _ModelInfo.bLockingStationSkip[3] = checkBox25.Checked;
           _ModelInfo.bLockingStationSkip[4] = checkBox24.Checked;
           
           _ModelInfo.bHipotSkip = checkBox11.Checked;
           _ModelInfo.bEolSkip   = checkBox12.Checked;

            NewName _form = new NewName(_ModelInfo);

            if (_form.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                _ModelInfo = Program._ModelInfo.CopyJsons<MODEL_INFO>();
                PointInfoView();
                LoadingInfoView();
                SpeedDataView();
                ETCDataView();
               // TPCDataView();
                HipotInfoView();
                CommentNEtcView();
                BcdDataView();
                //checkBox2.Checked = _ModelInfo.bUseTopCamera;
                //checkBox19.Checked = _ModelInfo.bUseFrotCamera;

                //checkBox1.Checked = _ModelInfo.bUseHipotBCDScanner;
                //checkBox4.Checked = _ModelInfo.bUseEolBCDScanner;

                //checkBox18.Checked = _ModelInfo.bUseJigTest;
                radioButton4.Checked = _ModelInfo.bUseAutoContect;
                radioButton5.Checked = _ModelInfo.bUseManualContect;

                checkBox28.Checked = _ModelInfo.bLockingStationSkip[0];
                checkBox27.Checked = _ModelInfo.bLockingStationSkip[1];
                checkBox26.Checked = _ModelInfo.bLockingStationSkip[2];
                checkBox25.Checked = _ModelInfo.bLockingStationSkip[3];
                checkBox24.Checked = _ModelInfo.bLockingStationSkip[4];
                
                checkBox11.Checked = _ModelInfo.bHipotSkip;
                checkBox12.Checked = _ModelInfo.bEolSkip;
                Program.SaveWorkPageInI(Program._ModelInfo.strModelName);
                _SysInfo.bModelChangeFirstLoading = true;
            }
        }

        private void simpleButton8_Click(object sender, EventArgs e)
        {

            ModelList _form = new ModelList();

            if (_form.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                _ModelInfo = Program._ModelInfo.CopyJsons<MODEL_INFO>();
                ViewLockingSTInfo();
                PointInfoView();
                LoadingInfoView();
                SpeedDataView();
                ETCDataView();
               // TPCDataView();
                CommentNEtcView();
                HipotInfoView();
                BcdDataView();
                //checkBox2.Checked = _ModelInfo.bUseTopCamera;
                //checkBox19.Checked = _ModelInfo.bUseFrotCamera;

                //checkBox1.Checked = _ModelInfo.bUseHipotBCDScanner;
                //checkBox4.Checked = _ModelInfo.bUseEolBCDScanner;


                //checkBox18.Checked = _ModelInfo.bUseJigTest;

                radioButton4.Checked = _ModelInfo.bUseAutoContect;
                radioButton5.Checked = _ModelInfo.bUseManualContect;

                 checkBox28.Checked = _ModelInfo.bLockingStationSkip[0];
                 checkBox27.Checked = _ModelInfo.bLockingStationSkip[1];
                 checkBox26.Checked = _ModelInfo.bLockingStationSkip[2];
                 checkBox25.Checked = _ModelInfo.bLockingStationSkip[3];
                 checkBox24.Checked = _ModelInfo.bLockingStationSkip[4];
                 
                 checkBox11.Checked = _ModelInfo.bHipotSkip;
                 checkBox12.Checked = _ModelInfo.bEolSkip;
                _SysInfo.bModelChangeFirstLoading = true;
            }
        }

        private void dataGridView11_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            if (e.RowIndex == 0 && e.ColumnIndex == 2) { e.Value = String.Format("{0} nF", e.Value); }
            if (e.RowIndex == 0 && e.ColumnIndex == 4) { e.Value = String.Format("{0} %", e.Value); }
            if (e.RowIndex == 0 && e.ColumnIndex == 5) { e.Value = String.Format("{0} %", e.Value); }

            if (e.RowIndex == 1 && e.ColumnIndex == 2) { e.Value = String.Format("{0} nF", e.Value); }
            if (e.RowIndex == 1 && e.ColumnIndex == 4) { e.Value = String.Format("{0} %", e.Value); }
            if (e.RowIndex == 1 && e.ColumnIndex == 5) { e.Value = String.Format("{0} %", e.Value); }

            if (e.RowIndex == 2 && e.ColumnIndex == 2) { e.Value = String.Format("{0} V", e.Value); }
            if (e.RowIndex == 2 && e.ColumnIndex == 3) { e.Value = String.Format("{0} Sec", e.Value); }
            if (e.RowIndex == 2 && e.ColumnIndex == 4) { e.Value = String.Format("{0} MΩ", e.Value); }

            if (e.RowIndex == 3 && e.ColumnIndex == 2) { e.Value = String.Format("{0} V", e.Value); }
            if (e.RowIndex == 3 && e.ColumnIndex == 3) { e.Value = String.Format("{0} Sec", e.Value); }
            if (e.RowIndex == 3 && e.ColumnIndex == 4) { e.Value = String.Format("{0} MΩ", e.Value); }


            if (e.RowIndex == 4 && e.ColumnIndex == 2) { e.Value = String.Format("{0} A", e.Value); }
            if (e.RowIndex == 4 && e.ColumnIndex == 3) { e.Value = String.Format("{0} Sec", e.Value); }
            if (e.RowIndex == 4 && e.ColumnIndex == 5) { e.Value = String.Format("{0} Ω", e.Value); }

            if (e.RowIndex == 5 && e.ColumnIndex == 2) { e.Value = String.Format("{0} V", e.Value); }
            if (e.RowIndex == 5 && e.ColumnIndex == 3) { e.Value = String.Format("{0} Sec", e.Value); }
            if (e.RowIndex == 5 && e.ColumnIndex == 5) { e.Value = String.Format("{0} mA", e.Value); }

            if (e.RowIndex == 6 && e.ColumnIndex == 2) { e.Value = String.Format("{0} V", e.Value); }
            if (e.RowIndex == 6 && e.ColumnIndex == 3) { e.Value = String.Format("{0} Sec", e.Value); }
            if (e.RowIndex == 6 && e.ColumnIndex == 5) { e.Value = String.Format("{0} mA", e.Value); }
        }

        private void simpleButton15_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void dataGridView2_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void simpleButton89_Click(object sender, EventArgs e)
        {
            LoadingInfoLoad();

            Offset _form = new Offset(_ModelInfo);
            if (_form.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {

            }

            LoadingInfoView();
        }

        private void simpleButton90_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("현재 위치를 기억 하시겠습니까?", "Save", MessageBoxButtons.YesNo) == DialogResult.No)
            {
                return;
            }

            double dbPos = 0.0;
            double dbCalcPos = 0.0;
            if (dataGridView1.CurrentRow.Index == 1)
            {
                CAXM.AxmStatusGetCmdPos((int)AXIS.X, ref dbPos);
                dataGridView1[2, dataGridView1.CurrentRow.Index].Value = Math.Round(dbPos, 2);

                CAXM.AxmStatusGetCmdPos((int)AXIS.Y, ref dbPos);
                dataGridView1[3, dataGridView1.CurrentRow.Index].Value = Math.Round(dbPos, 2);
            }
            else
            {
                CAXM.AxmStatusGetCmdPos((int)AXIS.X, ref dbPos);
                double.TryParse(dataGridView1[6, dataGridView1.CurrentRow.Index].Value.ToString(), out dbCalcPos);
                dataGridView1[2, dataGridView1.CurrentRow.Index].Value = Math.Round(dbPos - dbCalcPos, 2);


                CAXM.AxmStatusGetCmdPos((int)AXIS.Y, ref dbPos);
                double.TryParse(dataGridView1[7, dataGridView1.CurrentRow.Index].Value.ToString(), out dbCalcPos);
                dataGridView1[3, dataGridView1.CurrentRow.Index].Value = Math.Round(dbPos - dbCalcPos, 2);

                CAXM.AxmStatusGetCmdPos((int)AXIS.Z, ref dbPos);
                double.TryParse(dataGridView1[8, dataGridView1.CurrentRow.Index].Value.ToString(), out dbCalcPos);
                dataGridView1[4, dataGridView1.CurrentRow.Index].Value = Math.Round(dbPos - dbCalcPos, 2);

            }
        }

        private void simpleButton92_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST5] = true; 
        }

        private void simpleButton91_Click(object sender, EventArgs e)
        {
            _SysInfo.bStationAutoMode[(int)STATION_LIST.ST5] = false; 
        }

        private void simpleButton98_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION5_PALLET_UP, true);
            Program.SetDIOPort(DO.STATION5_PALLET_DW, false);
        }

        private void simpleButton97_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION5_PALLET_UP, false);
            Program.SetDIOPort(DO.STATION5_PALLET_DW, true);
        }

        private void simpleButton94_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION5_STOPPER_DW, false);

        }

        private void simpleButton93_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION5_STOPPER_DW, true);
        }

        private void simpleButton96_Click(object sender, EventArgs e)
        {
            if (Program.GetDIOPort(DI.STATION5_CENTER))
            {
                Program.SetDIOPort(DO.STATION5_BREAK_OFF, true);
                Program.SetDIOPort(DO.STATION5_LOCK_OFF, false);
            }
            else
            {
                Program.SetDIOPort(DO.STATION5_BREAK_OFF, false);
                Program.SetDIOPort(DO.STATION5_LOCK_OFF, true);
            }
        }

        private void simpleButton95_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort(DO.STATION5_LOCK_OFF, true);
        }

        private void dataGridView5_DataError(object sender, DataGridViewDataErrorEventArgs e)
        {

        }

        private void simpleButton102_Click(object sender, EventArgs e)
        {
            CAXM.AxmSignalServoOn((int)AXIS.ST3_R, 1);
        }

        private void simpleButton101_Click(object sender, EventArgs e)
        {
            CAXM.AxmSignalServoOn((int)AXIS.ST3_R, 0);
        }

        



        
        
        // R축 조그 
        private void simpleButton100_MouseDown(object sender, MouseEventArgs e)
        {
            double dbSpeed = 0.0;

            double.TryParse(comboBox9.Text, out dbSpeed); 
            CAXM.AxmMoveVel((int)AXIS.ST3_R, +(dbSpeed), 0.2, 0.2); 

        }

        private void simpleButton99_MouseDown(object sender, MouseEventArgs e)
        {
            double dbSpeed = 0.0;

            double.TryParse(comboBox9.Text, out dbSpeed);
            CAXM.AxmMoveVel((int)AXIS.ST3_R, -(dbSpeed), 0.2, 0.2); 
        }

        private void simpleButton100_MouseUp(object sender, MouseEventArgs e)
        {
            CAXM.AxmMoveSStop((int)AXIS.ST3_R);
        }

        private void simpleButton99_MouseUp(object sender, MouseEventArgs e)
        {
            CAXM.AxmMoveSStop((int)AXIS.ST3_R);
        }

        private void simpleButton103_Click(object sender, EventArgs e)
        {
            Program.nProcessStep[(int)PROC_LIST.MANUAL] = 4100;

            //if (!Program.GetDIOPortStat(DO.STATION3_BREAK_OFF) || !Program.GetDIOPortStat(DO.STATION3_LOCK_OFF)) 
            //{
            //    MessageBox.Show("STATION #3 LOCKED");
            //    return;
            //}
            //Program.MoveTo(AXIS.ST3_R, 180.0, _ModelInfo.dbST3TurnSpeed, 1);
        }

        private void simpleButton104_Click(object sender, EventArgs e)
        {
            Program.nProcessStep[(int)PROC_LIST.MANUAL] = 4000;

            //if (!Program.GetDIOPortStat(DO.STATION3_BREAK_OFF) || !Program.GetDIOPortStat(DO.STATION3_LOCK_OFF))
            //{
            //    MessageBox.Show("STATION #3 LOCKED");
            //    return;
            //}
            //Program.MoveTo(AXIS.ST3_R, 0, _ModelInfo.dbST3TurnSpeed, 1);
        }

        private void simpleButton105_Click(object sender, EventArgs e)
        {

        }

        private void ModelSetup_FormClosing(object sender, FormClosingEventArgs e)
        {
            timer1.Stop();
           
        }

        private void tabPage6_Click(object sender, EventArgs e)
        {

        }

        private void simpleButton108_Click(object sender, EventArgs e)
        {
            dataGridView24.Rows.Add("NONAME", "", "1");
        }

        private void simpleButton107_Click(object sender, EventArgs e)
        {
            TitePass _forms = new TitePass(1);
            if (_forms.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                if (dataGridView24.CurrentRow != null)
                {
                    if (dataGridView24.CurrentRow.Index >= 0)
                    {
                        dataGridView24.Rows.Remove(dataGridView24.CurrentRow);
                    }
                }
            }
        }

        private void simpleButton106_Click(object sender, EventArgs e)
        {
            dataGridView23.Rows.Add("NONAME", "", "1");
        }

        private void simpleButton105_Click_1(object sender, EventArgs e)
        {
            TitePass _forms = new TitePass(1);
            if (_forms.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                if (dataGridView23.CurrentRow != null)
                {
                    if (dataGridView23.CurrentRow.Index >= 0)
                    {
                        dataGridView23.Rows.Remove(dataGridView23.CurrentRow);
                    }
                }
            }
        }

        private void simpleButton133_Click(object sender, EventArgs e)
        {
            // 바코드 설정 위치에서만 수정가능
            double dbSourceX = 0.0;
            double dbSourceY = 0.0;
            double dbSourceZ = 0.0;

            double dbTargetX = 0.0;
            double dbTargetY = 0.0;
            double dbTargetZ = 0.0;

            CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_2X, ref dbSourceX);
            CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_2Y, ref dbSourceY);
            CAXM.AxmStatusGetCmdPos((int)AXIS.HIPOT_2Z, ref dbSourceZ);

            double.TryParse(dataGridView3[4, 2].Value.ToString(), out dbTargetX);
            double.TryParse(dataGridView3[5, 2].Value.ToString(), out dbTargetY);
            double.TryParse(dataGridView3[6, 2].Value.ToString(), out dbTargetZ);

            if (Math.Abs(dbSourceX - dbTargetX) > 1.0 || Math.Abs(dbSourceY - dbTargetY) > 1.0 || Math.Abs(dbSourceZ - dbTargetZ) > 1.0)
            {
                MessageBox.Show("바코드 스캔 위치에서만 기준값을 설정할수 있습니다.");
                return;
            }
            else
            {
                dataGridView9[2, 6].Value = Program._TesterDistance.dbDistance[1].ToString("F2");
            }
        }

        private void simpleButton109_Click(object sender, EventArgs e)
        {
            double dbSourceX = 0.0;
            double dbSourceY = 0.0;
            double dbSourceZ = 0.0;

            double dbTargetX = 0.0;
            double dbTargetY = 0.0;
            double dbTargetZ = 0.0;

            CAXM.AxmStatusGetCmdPos((int)AXIS.EOL_X, ref dbSourceX);
            CAXM.AxmStatusGetCmdPos((int)AXIS.EOL_Y, ref dbSourceY);
            CAXM.AxmStatusGetCmdPos((int)AXIS.EOL_Z, ref dbSourceZ);

            double.TryParse(dataGridView4[1, 2].Value.ToString(), out dbTargetX);
            double.TryParse(dataGridView4[2, 2].Value.ToString(), out dbTargetY);
            double.TryParse(dataGridView4[3, 2].Value.ToString(), out dbTargetZ);

            if (Math.Abs(dbSourceX - dbTargetX) > 1.0 || Math.Abs(dbSourceY - dbTargetY) > 1.0 || Math.Abs(dbSourceZ - dbTargetZ) > 1.0)
            {
                MessageBox.Show("바코드 스캔 위치에서만 기준값을 설정할수 있습니다.");
                return;
            }
            else
            {
                dataGridView10[2, 1].Value = Program._TesterDistance.dbDistance[0].ToString("F2");
            }
        }

        private void simpleButton138_Click(object sender, EventArgs e)
        {
            dataGridView28.Rows.Add(dataGridView28.Rows.Count + 1, 0, 0, 0, (dataGridView28.Columns[4] as DataGridViewComboBoxColumn).Items[0]);
        }

        private void simpleButton136_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("현재 위치를 기억 하시겠습니까?", "Save", MessageBoxButtons.YesNo) == DialogResult.No)
            {
                return;
            }


            dataGridView28[1, dataGridView28.CurrentRow.Index].Value = _SysInfo.nST2EncoderX;
            dataGridView28[2, dataGridView28.CurrentRow.Index].Value = _SysInfo.nST2EncoderY;
        }

        private void simpleButton137_Click(object sender, EventArgs e)
        {
            if (dataGridView28.CurrentRow.Index > -1)
            {
                dataGridView28.Rows.RemoveAt(dataGridView28.CurrentRow.Index);
            }
        }

        private void simpleButton110_Click(object sender, EventArgs e)
        {
            TitePass _forms = new TitePass(1);
            if (_forms.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                if (dataGridView25.CurrentRow != null)
                {
                    if (dataGridView25.CurrentRow.Index >= 0)
                    {
                        dataGridView25.Rows.Remove(dataGridView25.CurrentRow);
                    }
                }
            }
        }

        private void simpleButton111_Click(object sender, EventArgs e)
        {
            dataGridView25.Rows.Add("NONAME", "", "1");
        }

        private void simpleButton102_Click_1(object sender, EventArgs e)
        {
            dataGridView16.Rows.Add("NONAME", "");
        }

        private void simpleButton101_Click_1(object sender, EventArgs e)
        {
            if (dataGridView16.CurrentRow != null)
            {
                if (dataGridView16.CurrentRow.Index >= 0)
                {
                    dataGridView16.Rows.Remove(dataGridView16.CurrentRow);
                }
            }
        }

        private void simpleButton141_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("선택한 위치로 이동하시겠습니까?", "MOVE", MessageBoxButtons.YesNo) == DialogResult.No)
            {
                return;
            }

            if (dataGridView26.CurrentRow.Index < 0) { return; }
            dataGridView26.EndEdit();
            double.TryParse(dataGridView26[1, dataGridView26.CurrentRow.Index].Value.ToString(), out _SysInfo.dbManualMovePos[0]);
            double.TryParse(dataGridView26[2, dataGridView26.CurrentRow.Index].Value.ToString(), out _SysInfo.dbManualMovePos[1]);
            double.TryParse(dataGridView26[3, dataGridView26.CurrentRow.Index].Value.ToString(), out _SysInfo.dbManualMovePos[2]);
            Program.nProcessStep[(int)PROC_LIST.MANUAL] = 3100;
        }

        private void simpleButton139_Click(object sender, EventArgs e)
        {
            if (dataGridView26.CurrentRow.Index < 0)
            {
                return;
            }

            if (MessageBox.Show("선택 항목에 현재 위치를 기억시키시겠습니까?", "현재 위치 기억", MessageBoxButtons.YesNo) == DialogResult.No)
            {
                return;
            }

            double dbPos = 0.0;
            CAXM.AxmStatusGetCmdPos((int)AXIS.CAMERA1_X, ref dbPos);
            dataGridView26[1, dataGridView26.CurrentRow.Index].Value = Math.Round(dbPos, 2);

            CAXM.AxmStatusGetCmdPos((int)AXIS.CAMERA1_Y, ref dbPos);
            dataGridView26[2, dataGridView26.CurrentRow.Index].Value = Math.Round(dbPos, 2);

            CAXM.AxmStatusGetCmdPos((int)AXIS.CAMERA1_Z, ref dbPos);
            dataGridView26[3, dataGridView26.CurrentRow.Index].Value = Math.Round(dbPos, 2);
        }

        private void simpleButton140_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("선택한 위치로 이동하시겠습니까?", "MOVE", MessageBoxButtons.YesNo) == DialogResult.No)
            {
                return;
            }

            if (dataGridView26.CurrentRow.Index < 0) { return; }
            dataGridView26.EndEdit();
            double.TryParse(dataGridView26[4, dataGridView26.CurrentRow.Index].Value.ToString(), out _SysInfo.dbManualMovePos[0]);
            double.TryParse(dataGridView26[5, dataGridView26.CurrentRow.Index].Value.ToString(), out _SysInfo.dbManualMovePos[1]);
            double.TryParse(dataGridView26[6, dataGridView26.CurrentRow.Index].Value.ToString(), out _SysInfo.dbManualMovePos[2]);
            Program.nProcessStep[(int)PROC_LIST.MANUAL] = 3200;
        }

        private void simpleButton103_Click_1(object sender, EventArgs e)
        {
            if (dataGridView26.CurrentRow.Index < 0)
            {
                return;
            }

            if (MessageBox.Show("선택 항목에 현재 위치를 기억시키시겠습니까?", "현재 위치 기억", MessageBoxButtons.YesNo) == DialogResult.No)
            {
                return;
            }

            double dbPos = 0.0;
            CAXM.AxmStatusGetCmdPos((int)AXIS.CAMERA2_X, ref dbPos);
            dataGridView26[4, dataGridView26.CurrentRow.Index].Value = Math.Round(dbPos, 2);

            CAXM.AxmStatusGetCmdPos((int)AXIS.CAMERA2_Y, ref dbPos);
            dataGridView26[5, dataGridView26.CurrentRow.Index].Value = Math.Round(dbPos, 2);

            CAXM.AxmStatusGetCmdPos((int)AXIS.CAMERA2_Z, ref dbPos);
            dataGridView26[6, dataGridView26.CurrentRow.Index].Value = Math.Round(dbPos, 2);
        }
    }
}
