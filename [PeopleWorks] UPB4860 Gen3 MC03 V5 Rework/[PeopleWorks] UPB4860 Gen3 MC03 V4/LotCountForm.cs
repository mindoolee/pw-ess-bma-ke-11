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
    public partial class LotCountForm : Form
    {
        public LotCountForm()
        {
            InitializeComponent();
        }

        private void simpleButton1_Click(object sender, EventArgs e)
        {
            int.TryParse(textBox1.Text, out Program._LotCount.nLotCount);
            Program.SaveModelProductCount(Program._ModelInfo.strModelName);
            this.Close();
        }

        private void simpleButton2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                int.TryParse(textBox1.Text, out Program._LotCount.nLotCount);
                Program.SaveModelProductCount(Program._ModelInfo.strModelName);
                this.Close();
            }
        }

        private void simpleButton3_Click(object sender, EventArgs e)
        {
            int.TryParse(textBox1.Text, out Program._LotCount.nLotCount);
            Program.SaveModelProductCount(Program._ModelInfo.strModelName);
            this.Close();
        }

        private void simpleButton4_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
