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
    public partial class ModelList : Form
    {
        public int nClickCell = new int();
        public string[] strFileNaems = new string[2000];

        public ModelList()
        {
            InitializeComponent();

            string[] files = Directory.GetFiles("MODEL\\", "*.rcp", SearchOption.AllDirectories);

            foreach (string s in files)
            {
                FileInfo fileInfo = new FileInfo(s);
                dataGridView1.Rows.Add(fileInfo.FullName.Substring(fileInfo.FullName.LastIndexOf("MODEL\\") + 6, (fileInfo.FullName.LastIndexOf(".") - fileInfo.FullName.LastIndexOf("MODEL\\") - 6)));
            }
        }



        public void LoadModelInfo(int nIndex)
        {
            Program.LoadModelInfo(ref Program._ModelInfo, dataGridView1.Rows[nIndex].Cells[0].Value.ToString());
            Program.LoadModelProductCount(Program._ModelInfo.strModelName);
        }

        private void simpleButton4_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            nClickCell = e.RowIndex;
        }

        private void dataGridView1_CellDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex < 0) return;
            LoadModelInfo(e.RowIndex);
            this.DialogResult = System.Windows.Forms.DialogResult.OK;
        }

        private void simpleButton3_Click(object sender, EventArgs e)
        {
            if (nClickCell < 0) return;
            LoadModelInfo(nClickCell);
            this.DialogResult = System.Windows.Forms.DialogResult.OK;
        }
    }
}
