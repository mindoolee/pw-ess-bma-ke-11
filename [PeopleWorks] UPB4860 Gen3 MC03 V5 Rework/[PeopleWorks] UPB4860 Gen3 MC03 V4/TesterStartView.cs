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
    public partial class TesterStartView : Form
    {
        bool bUseHipot = false;

        bool bUseCharge = false;
        int nStation = 0;

        public TesterStartView(bool _bUseHipot, bool _bUseCharge, int _nStation)
        {
            InitializeComponent();
            bUseHipot = _bUseHipot;
            bUseCharge = _bUseCharge;
            nStation = _nStation;
        }

        private void TesterStartView_Load(object sender, EventArgs e)
        {
            if (bUseHipot)
            {
                label_Hipot.Enabled = true;
                label65.Enabled = true;
            }
            else
            {
                label_Hipot.Enabled = false;
                label65.Enabled = false;

                label_Hipot.Text = "";
                label_Hipot.BackColor = Color.DimGray;
            }


            if (bUseCharge)
            {
                label_Charge.Enabled = true;
                label3.Enabled = true;
            }
            else
            {
                label_Charge.Enabled = false;
                label3.Enabled = false;

                label_Charge.Text = "";
                label_Charge.BackColor = Color.DimGray;
            }


            label91.Text = String.Format("Station #{0}", nStation + 1);

            timer1.Interval = 100;
            timer1.Start();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (bUseHipot)
            {
                // 하이팟 스테이션일 경우
                if (nStation == 5)
                {
                    if (!_SysInfo.bContactOneTime[0])
                    {
                        label65.Text = "HIPOT";
                        label_Hipot.Text = "READY";
                        label_Hipot.BackColor = Color.LightGray;
                    }
                    else
                    {
                        if (_SysInfo.bContactTestOk[0])
                        {
                            label65.Text = "HIPOT";
                            label_Hipot.Text = "O.K";
                            label_Hipot.BackColor = Color.LightGreen;
                        }
                        else
                        {
                            label65.Text = "HIPOT";
                            label_Hipot.Text = "N.G";
                            label_Hipot.BackColor = Color.LightPink;
                        }
                    }
                }

                // EOL 스테이션인 경우
                if (nStation == 6)
                {
                    if (!_SysInfo.bContactOneTime[1])
                    {
                        label65.Text = "EOL";
                        label_Hipot.Text = "READY";
                        label_Hipot.BackColor = Color.LightGray;
                    }
                    else
                    {
                        if (_SysInfo.bContactTestOk[1])
                        {
                            label65.Text = "EOL";
                            label_Hipot.Text = "O.K";
                            label_Hipot.BackColor = Color.LightGreen;
                        }
                        else
                        {
                            label65.Text = "EOL";
                            label_Hipot.Text = "N.G";
                            label_Hipot.BackColor = Color.LightPink;
                        }
                    }
                }
            }



            if (bUseCharge)
            {
                if (nStation + 1 == _Config.nBCDScanStation)
                {
                    if (_SysInfo.bScanSTTesetFinish)
                    {
                        if (_SysInfo.bScanSTTestOKNG[(int)STATION_LIST.ST1 + nStation])
                        {
                            label_Charge.Text = "O.K";
                            label_Charge.BackColor = Color.LightGreen;
                        }
                        else
                        {
                            label_Charge.Text = "N.G";
                            label_Charge.BackColor = Color.LightPink;

                        }
                    }
                    else
                    {
                        label_Charge.Text = "READY";
                        label_Charge.BackColor = Color.LightGray;
                    }
                }
                else
                {
                    if (_SysInfo.bScanSTTestOKNG[(int)STATION_LIST.ST1 + nStation])
                    {
                        label_Charge.Text = "O.K";
                        label_Charge.BackColor = Color.LightGreen;
                    }
                    else
                    {
                        label_Charge.Text = "N.G";
                        label_Charge.BackColor = Color.LightPink;

                    }
                }
            }
        }

        private void label_Hipot_Click(object sender, EventArgs e)
        {
            if (nStation == 5)
            {
                if (_SysInfo.bContactOneTime[0])
                {
                    if (_SysInfo.bContactTestOk[0])
                    {
                        _SysInfo.bContactTestOk[0] = false;
                        _SysInfo.bContactTestNg[0] = true;
                    }
                    else
                    {
                        _SysInfo.bContactOneTime[0] = false;
                    }
                }
                else
                {
                    _SysInfo.bContactTestOk[0] = true;
                    _SysInfo.bContactTestNg[0] = false;
                    _SysInfo.bContactOneTime[0] = true;
                }
            }
            else if (nStation == 6)
            {
                if (_SysInfo.bContactOneTime[1])
                {
                    if (_SysInfo.bContactTestOk[1])
                    {
                        _SysInfo.bContactTestOk[1] = false;
                    }
                    else
                    {
                        _SysInfo.bContactOneTime[1] = false;
                    }
                }
                else
                {
                    _SysInfo.bContactTestOk[1] = true;
                    _SysInfo.bContactOneTime[1] = true;
                }
            }
        }

        private void label_Charge_Click(object sender, EventArgs e)
        {
            if (nStation + 1 == _Config.nBCDScanStation)
            {
                if (_SysInfo.bScanSTTesetFinish)
                {
                    if (_SysInfo.bScanSTTestOKNG[(int)STATION_LIST.ST1 + nStation])
                    {
                        _SysInfo.bScanSTTestOKNG[(int)STATION_LIST.ST1 + nStation] = false;
                    }
                    else
                    {
                        _SysInfo.bScanSTTesetFinish = false;
                    }
                }
                else
                {
                    _SysInfo.bScanSTTestOKNG[(int)STATION_LIST.ST1 + nStation] = true;
                    _SysInfo.bScanSTTesetFinish = true;
                }
            }
            else
            {
                _SysInfo.bScanSTTestOKNG[(int)STATION_LIST.ST1 + nStation] = !_SysInfo.bScanSTTestOKNG[(int)STATION_LIST.ST1 + nStation];
            }
        }

        private void simpleButton1_Click(object sender, EventArgs e)
        {
            DialogResult = System.Windows.Forms.DialogResult.Yes;
        }

        private void simpleButton3_Click(object sender, EventArgs e)
        {
            DialogResult = System.Windows.Forms.DialogResult.Cancel;
        }
    }
}
