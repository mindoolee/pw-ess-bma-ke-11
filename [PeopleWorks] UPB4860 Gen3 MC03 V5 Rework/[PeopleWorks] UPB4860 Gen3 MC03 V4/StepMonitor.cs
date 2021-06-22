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
    public partial class StepMonitor : Form
    {
        public StepMonitor()
        {
            InitializeComponent();

            timer1.Interval = 100;
            timer1.Start();
        }




        private void timer1_Tick(object sender, EventArgs e)
        {
            label10.Text = Program.nProcessStep[(int)PROC_LIST.MAIN].ToString();
            label68.Text = Program.nProcessStep[(int)PROC_LIST.ST1].ToString();
            label2.Text = Program.nProcessStep[(int)PROC_LIST.ST2].ToString();
            label7.Text = Program.nProcessStep[(int)PROC_LIST.ST3].ToString();
            label5.Text = Program.nProcessStep[(int)PROC_LIST.ST4].ToString();

            label34.Text = Program.nProcessStep[(int)PROC_LIST.ST6].ToString();
            label36.Text = Program.nProcessStep[(int)PROC_LIST.ST7].ToString();

            label40.Text = Program.nProcessStep[(int)PROC_LIST.INLIFT].ToString();
            label42.Text = Program.nProcessStep[(int)PROC_LIST.RELIFT].ToString();

            label79.Text = Program.nProcessStep[(int)PROC_LIST.MANUAL].ToString();
            label82.Text = Program.nProcessStep[(int)PROC_LIST.SUB_LOADING].ToString();

            label76.Text = Program.nProcessStep[(int)PROC_LIST.SUB_TITE1].ToString();
            label81.Text = Program.nProcessStep[(int)PROC_LIST.SUB_TITE2].ToString();
            label80.Text = Program.nProcessStep[(int)PROC_LIST.SUB_TITE3].ToString();
            label72.Text = Program.nProcessStep[(int)PROC_LIST.SUB_TITE4].ToString();

            label38.Text = Program.nProcessStep[(int)PROC_LIST.CMA_MOVE].ToString();

            label44.Text = Program.nProcessStep[(int)PROC_LIST.SUB_LOADING_SW].ToString();
            label46.Text = Program.nProcessStep[(int)PROC_LIST.ST3_ROBOT].ToString();

            label46.Text = Program.nProcessStep[(int)PROC_LIST.ST3_ROBOT].ToString();
            


            label58.Text = "bInLiftReady";
            label58.BackColor = _SysInfo.bInLiftReady ? Color.LightGreen : Color.DarkGreen;

            label56.Text = "bLiftOutComp";
            label56.BackColor = _SysInfo.bLiftOutComplated ? Color.LightGreen : Color.DarkGreen;

            label53.Text = "bLoadingComp";
            label53.BackColor = _SysInfo.bLoadingComplated ? Color.LightGreen : Color.DarkGreen;

            label84.Text = "ReadySw";
            label84.BackColor = _SysInfo.bLoadingReadySw ? Color.LightGreen : Color.DarkGreen;



            label70.Text = Program._NutRunner[0].nCurrentStep.ToString();
            label66.Text = Program._NutRunner[1].nCurrentStep.ToString();
            label64.Text = Program._NutRunner[2].nCurrentStep.ToString();
            label62.Text = Program._NutRunner[3].nCurrentStep.ToString();
            label60.Text = Program._NutRunner[4].nCurrentStep.ToString();
            label51.Text = Program._NutRunner[5].nCurrentStep.ToString();

            label88.Text = Program._ArmXYZ.nPosX.ToString();
            label91.Text = Program._ArmXYZ.nPosY.ToString();
            label49.Text = Program._ArmXYZ.nPosZ.ToString();
            label90.Text = Program._ArmXYZ.strStatus;
            label89.Text = String.Format("{0} / {1}", Program._ArmXYZ.byCheckSum.ToString("X"), Program._ArmXYZ.strReadCheckSum);
        }
    }
}
