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
    public partial class AdminPass : Form
    {
        public AdminPass()
        {
            InitializeComponent();
        }

        private void simpleButton1_Click(object sender, EventArgs e)
        {

        }

        private void simpleButton2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                if (_Config.strAdminPass == textBox1.Text)
                {
                    this.DialogResult = System.Windows.Forms.DialogResult.OK;
                }
                else
                {
                    MessageBox.Show("패스워드가 일치하지 않습니다.");
                    this.Close();
                }
            }
        }

        private void simpleButton3_Click(object sender, EventArgs e)
        {
            if (_Config.strAdminPass == textBox1.Text)
            {
                this.DialogResult = System.Windows.Forms.DialogResult.OK;
            }
            else
            {
                MessageBox.Show("패스워드가 일치하지 않습니다.");
                this.Close();
            }
        }

        private void simpleButton4_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
