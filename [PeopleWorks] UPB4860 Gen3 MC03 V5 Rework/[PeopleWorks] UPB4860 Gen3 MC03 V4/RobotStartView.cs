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
    public partial class RobotStartView : Form
    {
        int _nType = 0;

        public RobotStartView(int nType)
        {
            InitializeComponent();
            _nType = nType;

        }

        private void RobotStartView_Load(object sender, EventArgs e)
        {

        }

        //private void simpleButton3_Click(object sender, EventArgs e)
        //{
        //    if(_nType == 0)
        //    {
        //        _SysInfo.nST3ResumeResult = 1;
        //    }
        //    this.Close();
        //}

        private void simpleButton2_Click(object sender, EventArgs e)
        {
            _SysInfo.bStation3NgOut = 1;
            _SysInfo.TL_Buzzer = TOWER_LAMP.TL_OFF;
            this.Close();
        }

        private void simpleButton4_Click(object sender, EventArgs e)
        {
            _SysInfo.TL_Buzzer = TOWER_LAMP.TL_OFF;
        }



    }
}
