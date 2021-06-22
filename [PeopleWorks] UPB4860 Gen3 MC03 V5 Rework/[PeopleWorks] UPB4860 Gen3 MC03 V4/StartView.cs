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
    public partial class StartView : Form
    {
        public StartView()
        {
            InitializeComponent();
        }

        private void simpleButton11_Click(object sender, EventArgs e)
        {
            if (!Program.GetLoadingDoor())
            {
                MessageBox.Show("MAIN DOOR OPEN..");
                return;
            }

            this.DialogResult = System.Windows.Forms.DialogResult.Yes;
        }

        private void simpleButton3_Click(object sender, EventArgs e)
        {
            this.DialogResult = System.Windows.Forms.DialogResult.OK;
        }

        private void simpleButton1_Click(object sender, EventArgs e)
        {
            if (!Program.GetLoadingDoor())
            {
                MessageBox.Show("MAIN DOOR OPEN..");
                return;
            }

            _SysInfo.nLoadingWorkIndex = dataGridView1.CurrentCell.RowIndex;
            this.DialogResult = System.Windows.Forms.DialogResult.No;
        }

        private void simpleButton2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void StartView_Load(object sender, EventArgs e)
        {
            simpleButton11.Enabled = !Program.GetDIOPort(DI.INLIFT_PRODUCT_CMA);

            for (int i = 0; i < 20; i++)
            {
                string strResult = "";
                if (i > _SysInfo.nLoadingWorkIndex)
                {
                    strResult = "대기중";
                }
                else if (i == _SysInfo.nLoadingWorkIndex)
                {
                    strResult = "작업중";
                }
                if (i < _SysInfo.nLoadingWorkIndex)
                {
                    strResult = "작업완료";
                }


                if (Program._ModelInfo._Loading[i].bUse)
                {
                    dataGridView1.Rows.Add
                        (String.Format("P{0}", i + 1),
                        Program._ModelInfo._Loading[i].dbX.ToString(),
                        Program._ModelInfo._Loading[i].dbY.ToString(),
                        Program._ModelInfo._Loading[i].dbZ.ToString(),
                        strResult);
                }

            }
        }
    }
}
