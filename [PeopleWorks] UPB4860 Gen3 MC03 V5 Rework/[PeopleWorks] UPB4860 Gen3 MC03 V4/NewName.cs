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
    public partial class NewName : Form
    {
        public static MODEL_INFO _ModelInfo = new MODEL_INFO();

        public NewName(MODEL_INFO _mInfo)
        {
            InitializeComponent();
            _ModelInfo = _mInfo.CopyJsons<MODEL_INFO>();
        }

        private void NewName_Load(object sender, EventArgs e)
        {
            textBox1.Text = _ModelInfo.strModelName;
        }

        private void simpleButton1_Click(object sender, EventArgs e)
        {
            _ModelInfo.strModelName = textBox1.Text;
            Program._LotCount.nLotCount = 0;
            Program._LotCount.nProductCount = 0;
            Program._LotCount.tLotClearTime = DateTime.Now;
            Program._LotCount.tProductClearTime = DateTime.Now;

            Program.SaveModelInfo(_ModelInfo, _ModelInfo.strModelName);
            Program.LoadModelInfo(ref Program._ModelInfo, _ModelInfo.strModelName);


            Program.SaveModelProductCount(_ModelInfo.strModelName);
            Program.LoadModelProductCount(_ModelInfo.strModelName);

            this.DialogResult = System.Windows.Forms.DialogResult.OK;
        }

        private void simpleButton2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void simpleButton3_Click(object sender, EventArgs e)
        {
            _ModelInfo.strModelName = textBox1.Text;
            Program._LotCount.nLotCount = 0;
            Program._LotCount.nProductCount = 0;
            Program._LotCount.tLotClearTime = DateTime.Now;
            Program._LotCount.tProductClearTime = DateTime.Now;

            Program.SaveModelInfo(_ModelInfo, _ModelInfo.strModelName);
            Program.LoadModelInfo(ref Program._ModelInfo, _ModelInfo.strModelName);


            Program.SaveModelProductCount(_ModelInfo.strModelName);
            Program.LoadModelProductCount(_ModelInfo.strModelName);

            this.DialogResult = System.Windows.Forms.DialogResult.OK;
        }

        private void simpleButton4_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
