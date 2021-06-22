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
    public partial class Offset : Form
    {
        MODEL_INFO _mInfo = new MODEL_INFO();

        public Offset(MODEL_INFO _ModelInfo)
        {
            InitializeComponent();
            _mInfo = _ModelInfo;
        }

        private void Offset_Load(object sender, EventArgs e)
        {
            for (int i = 0; i < 20; i++)
            {
                comboBox1.Items.Add(String.Format("{0}", i + 1));
                comboBox2.Items.Add(String.Format("{0}", i + 1));
                comboBox3.Items.Add(String.Format("{0}", i + 1));
              
                comboBox4.Items.Add(String.Format("{0}", i + 1));
                comboBox6.Items.Add(String.Format("{0}", i + 1));

            }
        }

        private void simpleButton1_Click(object sender, EventArgs e)
        {
            if (tabControl1.SelectedIndex == 0)
            {


                if (comboBox1.SelectedIndex > comboBox2.SelectedIndex)
                {
                    MessageBox.Show("범위설정 오류!!");
                    return;
                }

                double dbAddX = 0.0;
                double dbAddY = 0.0;


                double.TryParse(textBox1.Text, out dbAddX);
                double.TryParse(textBox2.Text, out dbAddY);

                if (checkBox1.Checked)
                {
                    for (int i = comboBox1.SelectedIndex; i <= comboBox2.SelectedIndex; i++)
                    {
                        _mInfo._Loading[i].dbX += dbAddX;
                        _mInfo._Loading[i].dbY += dbAddY;
                    }
                }
                else
                {
                    if (comboBox2.SelectedIndex >= comboBox3.SelectedIndex)
                    {
                        MessageBox.Show("범위설정 오류!!");
                        return;
                    }

                    for (int i = comboBox1.SelectedIndex; i <= comboBox2.SelectedIndex; i++)
                    {

                        _mInfo._Loading[i - comboBox1.SelectedIndex + comboBox3.SelectedIndex].dbX = _mInfo._Loading[i].dbX + dbAddX;
                        _mInfo._Loading[i - comboBox1.SelectedIndex + comboBox3.SelectedIndex].dbY = _mInfo._Loading[i].dbY + dbAddY;
                        _mInfo._Loading[i - comboBox1.SelectedIndex + comboBox3.SelectedIndex].nType = _mInfo._Loading[i].nType;
                        _mInfo._Loading[i - comboBox1.SelectedIndex + comboBox3.SelectedIndex].bUse = _mInfo._Loading[i].bUse;

                        _mInfo._Loading[i - comboBox1.SelectedIndex + comboBox3.SelectedIndex].dbS = _mInfo._Loading[i].dbS;
                        _mInfo._Loading[i - comboBox1.SelectedIndex + comboBox3.SelectedIndex].dbSpare_b[1] = _mInfo._Loading[i].dbSpare_b[1];
                        _mInfo._Loading[i - comboBox1.SelectedIndex + comboBox3.SelectedIndex].dbSpare_b[0] = _mInfo._Loading[i].dbSpare_b[0];
                    }
                }


            }
            else if (tabControl1.SelectedIndex == 1)
            {



                double dbAddX = 0.0;
                double dbAddY = 0.0;
                double dbSumX = 0.0;
                double dbSumY = 0.0;
                int dbCount = 0;

                double.TryParse(textBox4.Text, out dbAddX);
                double.TryParse(textBox3.Text, out dbAddY);
                int.TryParse(textBox5.Text, out dbCount);


                if (comboBox4.SelectedIndex >= comboBox6.SelectedIndex)
                {
                    MessageBox.Show("범위설정 오류!!");
                    return;
                }

                dbSumX = _mInfo._Loading[comboBox4.SelectedIndex].dbX;
                dbSumY = _mInfo._Loading[comboBox4.SelectedIndex].dbY;

                for (int i = 0; i < dbCount; i++)
                {
                    dbSumX += dbAddX;
                    dbSumY += dbAddY;

                    _mInfo._Loading[comboBox6.SelectedIndex + i].dbX = dbSumX;
                    _mInfo._Loading[comboBox6.SelectedIndex + i].dbY = dbSumY;


                    _mInfo._Loading[comboBox6.SelectedIndex + i].nType = _mInfo._Loading[comboBox4.SelectedIndex].nType;
                    _mInfo._Loading[comboBox6.SelectedIndex + i].bUse = _mInfo._Loading[comboBox4.SelectedIndex].bUse;

                    _mInfo._Loading[comboBox6.SelectedIndex + i].dbS = _mInfo._Loading[comboBox4.SelectedIndex].dbS;
                    _mInfo._Loading[comboBox6.SelectedIndex + i].dbSpare_b[1] = _mInfo._Loading[comboBox4.SelectedIndex].dbSpare_b[1];
                    _mInfo._Loading[comboBox6.SelectedIndex + i].dbSpare_b[0] = _mInfo._Loading[comboBox4.SelectedIndex].dbSpare_b[0];
                }
                
            }

            this.DialogResult = System.Windows.Forms.DialogResult.OK;
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked)
            {
                comboBox3.Enabled = false;
            }
            else
            {
                comboBox3.Enabled = true;
            }
        }


    }
}
