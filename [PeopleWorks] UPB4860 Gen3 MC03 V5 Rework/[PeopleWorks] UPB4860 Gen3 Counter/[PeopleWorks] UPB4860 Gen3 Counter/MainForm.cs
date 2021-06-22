using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;

namespace _PeopleWorks__UPB4860_Gen3_Counter
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void panel5_Paint(object sender, PaintEventArgs e)
        {

        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            Program.MainThread.Start();
            timer1.Interval = 100;
            timer1.Start();

            

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            st1t1.Text = Program.nNowCount[0].ToString();
            label4.Text = Program.nNowCount[1].ToString();
            label7.Text = Program.nNowCount[2].ToString();
            label10.Text = Program.nNowCount[3].ToString();
            label13.Text = Program.nNowCount[4].ToString();

            label1.Text = Program.nMaxCount[0].ToString();
            label3.Text = Program.nMaxCount[1].ToString();
            label6.Text = Program.nMaxCount[2].ToString();
            label9.Text = Program.nMaxCount[3].ToString();
            label12.Text = Program.nMaxCount[4].ToString();

            if(Program.bConnection)
            {
                label20.Text = "Online";
                label20.BackColor = Color.LightGreen;
            }
            else
            {
                label20.Text = "Offline";
                label20.BackColor = Color.LightPink;
            }

            Label[] lb = { st1t1, label4, label7, label10, label13 };

            for (int i = 0; i < 5; i++)
            {
                if (Program.nNowCount[i] >= Program.nMaxCount[i])
                {
                    lb[i].BackColor = Color.LightGreen;
                }
                else
                {
                    lb[i].BackColor = Color.Gainsboro;
                }
            }


            Label[] slb = { label21, label22, label23, label24, label25 };

            for(int i = 0; i < 5; i++)
            {
                if(Program.bSelectTool[i])
                {
                    slb[i].BackColor = Color.HotPink;
                }
                else
                {
                    slb[i].BackColor = Color.Gainsboro;
                }
            }

            simpleButton5.Enabled = _SysInfo.bUpUnLock;         // 상승 해제는 따로
            simpleButton1.Enabled = _SysInfo.bUnlock;
            simpleButton2.Enabled = _SysInfo.bUnlock;
            simpleButton6.Enabled = _SysInfo.bUpUnLock;         // 상승 해제는 따로
            simpleButton4.Enabled = _SysInfo.bUnlock;
            simpleButton3.Enabled = _SysInfo.bUnlock;
            simpleButton9.Enabled = _SysInfo.bUpUnLock;         // 상승 해제는 따로
            simpleButton8.Enabled = _SysInfo.bUnlock;
            simpleButton7.Enabled = _SysInfo.bUnlock;
            simpleButton12.Enabled = _SysInfo.bUpUnLock;        // 상승 해제는 따로
            simpleButton11.Enabled = _SysInfo.bUnlock;
            simpleButton10.Enabled = _SysInfo.bUnlock;
            simpleButton15.Enabled = _SysInfo.bUpUnLock;        // 상승 해제는 따로
            simpleButton14.Enabled = _SysInfo.bUnlock;
            simpleButton13.Enabled = _SysInfo.bUnlock;


            if(_SysInfo.bUseScanRead)
            {
                panel7.Visible = true;
                
                if(_SysInfo.bScanOk)
                {
                    label26.Text = "READ OK";
                    label26.BackColor = Color.LightGreen;
                }
                else
                {
                    label26.Text = "NO READ";
                    label26.BackColor = Color.LightPink;
                }
            }
            else
            {
                panel7.Visible = false;
            }


            if(_SysInfo.bUseCMAScan)
            {
                panel8.Visible = true;

                if(_SysInfo.bCMAOk)
                {
                    label28.Text = "READ OK";
                    label28.BackColor = Color.LightGreen;
                }
                else
                {
                    label28.Text = "NO READ";
                    label28.BackColor = Color.LightPink;
                }

                if (_SysInfo.bBMSOk)
                {
                    label31.Text = "READ OK";
                    label31.BackColor = Color.LightGreen;
                }
                else
                {
                    label31.Text = "NO READ";
                    label31.BackColor = Color.LightPink;
                }

            }
            else
            {
                panel8.Visible = false;
            }


            if(_SysInfo.nTiteLog == 0)
            {
                label32.Text = "-";
                label32.BackColor = Color.LightYellow;
            }
            else if(_SysInfo.nTiteLog == 1)
            {
                label32.Text = "ING..";
                label32.BackColor = Color.LightYellow;
            }
            else if(_SysInfo.nTiteLog == 2)
            {
                label32.Text = "O.K";
                label32.BackColor = Color.LightGreen;
            }
            else if (_SysInfo.nTiteLog == 3)
            {
                label32.Text = "N.G";
                label32.BackColor = Color.LightPink;
            }
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (!_SysInfo.bMainProcessStop)
            {
                if (MessageBox.Show("프로그램을 종료하시겠습니까?", "종료", MessageBoxButtons.YesNo) == DialogResult.No)
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

        private void simpleButton5_Click(object sender, EventArgs e)
        {
            _SysInfo.bPushUp[0] = true;
        }

        private void simpleButton1_Click(object sender, EventArgs e)
        {
            _SysInfo.bPushDW[0] = true;
        }

        private void simpleButton6_Click(object sender, EventArgs e)
        {
            _SysInfo.bPushUp[1] = true;
        }

        private void simpleButton9_Click(object sender, EventArgs e)
        {
            _SysInfo.bPushUp[2] = true;
        }

        private void simpleButton12_Click(object sender, EventArgs e)
        {
            _SysInfo.bPushUp[3] = true;
        }

        private void simpleButton15_Click(object sender, EventArgs e)
        {
            _SysInfo.bPushUp[4] = true;
        }

        private void simpleButton4_Click(object sender, EventArgs e)
        {
            _SysInfo.bPushDW[1] = true;
        }

        private void simpleButton8_Click(object sender, EventArgs e)
        {
            _SysInfo.bPushDW[2] = true;
        }

        private void simpleButton11_Click(object sender, EventArgs e)
        {
            _SysInfo.bPushDW[3] = true;
        }

        private void simpleButton14_Click(object sender, EventArgs e)
        {
            _SysInfo.bPushDW[4] = true;
        }

        private void simpleButton2_Click(object sender, EventArgs e)
        {
            _SysInfo.bPushCLR[0] = true;
        }

        private void simpleButton3_Click(object sender, EventArgs e)
        {
            _SysInfo.bPushCLR[1] = true;
        }

        private void simpleButton7_Click(object sender, EventArgs e)
        {
            _SysInfo.bPushCLR[2] = true;
        }

        private void simpleButton10_Click(object sender, EventArgs e)
        {
            _SysInfo.bPushCLR[3] = true;
        }

        private void simpleButton13_Click(object sender, EventArgs e)
        {
            _SysInfo.bPushCLR[4] = true;
        }
    }
}
