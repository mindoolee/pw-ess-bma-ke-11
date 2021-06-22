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
    public partial class TorqueSpec : Form
    {
        public TorqueSpec()
        {
            InitializeComponent();

            ViewSpecData();
        }





        // 스펙 보여주기
        public void ViewSpecData()
        {
            // 팁네임 만큼 데이터 추가
            for(int i = 0; i < _Config._TipName.Count; i++)
            {
                dataGridView1.Rows.Add(_Config._TipName[i], _Config.dbTorqueSepcMin[0, i].ToString(), _Config.dbTorqueSepcMax[0, i].ToString(), _Config.nAngleSepcMin[0, i].ToString(), _Config.nAngleSepcMax[0, i].ToString());
                dataGridView2.Rows.Add(_Config._TipName[i], _Config.dbTorqueSepcMin[1, i].ToString(), _Config.dbTorqueSepcMax[1, i].ToString(), _Config.nAngleSepcMin[1, i].ToString(), _Config.nAngleSepcMax[1, i].ToString());
                dataGridView3.Rows.Add(_Config._TipName[i], _Config.dbTorqueSepcMin[2, i].ToString(), _Config.dbTorqueSepcMax[2, i].ToString(), _Config.nAngleSepcMin[2, i].ToString(), _Config.nAngleSepcMax[2, i].ToString());
                dataGridView4.Rows.Add(_Config._TipName[i], _Config.dbTorqueSepcMin[3, i].ToString(), _Config.dbTorqueSepcMax[3, i].ToString(), _Config.nAngleSepcMin[3, i].ToString(), _Config.nAngleSepcMax[3, i].ToString());
                dataGridView5.Rows.Add(_Config._TipName[i], _Config.dbTorqueSepcMin[4, i].ToString(), _Config.dbTorqueSepcMax[4, i].ToString(), _Config.nAngleSepcMin[4, i].ToString(), _Config.nAngleSepcMax[4, i].ToString());
                dataGridView6.Rows.Add(_Config._TipName[i], _Config.dbTorqueSepcMin[5, i].ToString(), _Config.dbTorqueSepcMax[5, i].ToString(), _Config.nAngleSepcMin[5, i].ToString(), _Config.nAngleSepcMax[5, i].ToString());
            }
        }

        public void LoadSpecData()
        {
            dataGridView1.EndEdit();
            dataGridView2.EndEdit();
            dataGridView3.EndEdit();
            dataGridView4.EndEdit();
            dataGridView5.EndEdit();
            dataGridView6.EndEdit();
            for(int i = 0; i < _Config._TipName.Count; i++)
            {
                double.TryParse(dataGridView1[1, i].Value.ToString(), out _Config.dbTorqueSepcMin[0, i]);
                double.TryParse(dataGridView1[2, i].Value.ToString(), out _Config.dbTorqueSepcMax[0, i]);
                int.TryParse(dataGridView1[3, i].Value.ToString(), out _Config.nAngleSepcMin[0, i]);
                int.TryParse(dataGridView1[4, i].Value.ToString(), out _Config.nAngleSepcMax[0, i]);

                double.TryParse(dataGridView2[1, i].Value.ToString(), out _Config.dbTorqueSepcMin[1, i]);
                double.TryParse(dataGridView2[2, i].Value.ToString(), out _Config.dbTorqueSepcMax[1, i]);
                int.TryParse(dataGridView2[3, i].Value.ToString(), out _Config.nAngleSepcMin[1, i]);
                int.TryParse(dataGridView2[4, i].Value.ToString(), out _Config.nAngleSepcMax[1, i]);

                double.TryParse(dataGridView3[1, i].Value.ToString(), out _Config.dbTorqueSepcMin[2, i]);
                double.TryParse(dataGridView3[2, i].Value.ToString(), out _Config.dbTorqueSepcMax[2, i]);
                int.TryParse(dataGridView3[3, i].Value.ToString(), out _Config.nAngleSepcMin[2, i]);
                int.TryParse(dataGridView3[4, i].Value.ToString(), out _Config.nAngleSepcMax[2, i]);


                double.TryParse(dataGridView4[1, i].Value.ToString(), out _Config.dbTorqueSepcMin[3, i]);
                double.TryParse(dataGridView4[2, i].Value.ToString(), out _Config.dbTorqueSepcMax[3, i]);
                int.TryParse(dataGridView4[3, i].Value.ToString(), out _Config.nAngleSepcMin[3, i]);
                int.TryParse(dataGridView4[4, i].Value.ToString(), out _Config.nAngleSepcMax[3, i]);

                double.TryParse(dataGridView5[1, i].Value.ToString(), out _Config.dbTorqueSepcMin[4, i]);
                double.TryParse(dataGridView5[2, i].Value.ToString(), out _Config.dbTorqueSepcMax[4, i]);
                int.TryParse(dataGridView5[3, i].Value.ToString(), out _Config.nAngleSepcMin[4, i]);
                int.TryParse(dataGridView5[4, i].Value.ToString(), out _Config.nAngleSepcMax[4, i]);

                double.TryParse(dataGridView6[1, i].Value.ToString(), out _Config.dbTorqueSepcMin[5, i]);
                double.TryParse(dataGridView6[2, i].Value.ToString(), out _Config.dbTorqueSepcMax[5, i]);
                int.TryParse(dataGridView6[3, i].Value.ToString(), out _Config.nAngleSepcMin[5, i]);
                int.TryParse(dataGridView6[4, i].Value.ToString(), out _Config.nAngleSepcMax[5, i]);
            }
        }



        private void simpleButton15_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void simpleButton7_Click(object sender, EventArgs e)
        {
            LoadSpecData();
            Program.SaveTorqueSpec();
            this.Close();
        }
    }
}
