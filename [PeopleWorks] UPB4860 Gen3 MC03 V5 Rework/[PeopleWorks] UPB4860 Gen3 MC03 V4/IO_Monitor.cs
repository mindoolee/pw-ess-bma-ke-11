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
    public partial class IO_Monitor : Form
    {
        Label[] _YNum;
        Label[] _YCate;
        Label[] _YComment;

        Label[] _XNum;
        Label[] _XCate;
        Label[] _XComment;


        int nYindex = 0;
        int nXindex = 0;

        public IO_Monitor()
        {
            InitializeComponent();

            _YNum = new Label[]{label1, label6, label12, label9, label24, label21, label18, label15,
                                label48, label45, label42, label39, label36, label33, label30, label27, 
                                label72, label69, label66, label63, label60, label57, label54, label51, 
                                label96, label93, label90, label87, label84, label81, label78, label75};

            _YCate = new Label[]{ label3, label5, label11, label8, label23 , label20, label17, label14,
                                  label47, label44, label41, label38, label35, label32, label29, label26,
                                  label71, label68, label65, label62, label59, label56, label53, label50,
                                  label95, label92, label89, label86, label83, label80, label77, label74};


            _YComment = new Label[] { label4, label2, label10, label7, label22, label19, label16, label13,
                                      label46, label43, label40, label37, label34, label31, label28, label25,
                                      label70, label67, label64, label61, label58, label55, label52, label49,
                                      label94, label91, label88, label85, label82, label79, label76, label73 };


            _XNum = new Label[] { label188, label186, label183,  label180, label177, label174, label171, label168,
                                  label165, label163, label160, label157, label154, label151, label148, label145,
                                  label142, label140, label137, label134, label131, label128, label125, label122, 
                                  label119, label117, label114, label111, label108, label105, label102, label99};

            _XCate = new Label[] { label192, label185, label182, label179, label176, label173, label170, label167, 
                                   label191, label162, label159, label156, label153, label150, label147, label144,
                                   label190, label139, label136,  label133, label130, label127, label124, label121, 
                                   label189, label116, label113, label110, label107, label104, label101, label98 };

            _XComment = new Label[] { label187, label184, label181, label178, label175, label172, label169, label166,
                                      label164, label161, label158, label155, label152, label149, label146, label143, 
                                      label141, label138, label135, label132, label129, label126, label123, label120, 
                                      label118, label115, label112, label109, label106, label103, label100, label97};


            

            for (int i = 0; i < _YNum.Length; i++)
            {
                _YNum[i].TabIndex = i;
                _YNum[i].Click += IO_Monitor_Click;
            }

            timer1.Interval = 100;
            timer1.Start();
        }


        // 넘버 클릭 이벤트
        void IO_Monitor_Click(object sender, EventArgs e)
        {
            Program.SetDIOPort((DO)(((Label)sender).TabIndex + (nYindex * 32)), !Program.GetDIOPortStat((DO)(((Label)sender).TabIndex + (nYindex * 32))));
        }





        // 타이머
        private void timer1_Tick(object sender, EventArgs e)
        {
            for(int i = 0; i < 32; i++)
            {
                _YNum[i].Text = String.Format("  Y{0:X3}:", i + (nYindex * 32));
                _YNum[i].Image = Program.GetDIOPortStat((DO)(i + (nYindex * 32))) ? Properties.Resources.Led_Green : Properties.Resources.led_gray;

                _XNum[i].Text = String.Format("  X{0:X3}:", i + (nXindex * 32));
                _XNum[i].Image = Program.GetDIOPort((DI)(i + (nXindex * 32))) ? Properties.Resources.Led_Green : Properties.Resources.led_gray;

                _YCate[i].Text = String.Format("{0}", _Define.DOTable[0].Rows[i + (nYindex * 32)]["Cate"]);
                _YComment[i].Text = String.Format("{0}", _Define.DOTable[0].Rows[i + (nYindex * 32)]["Comment"]);

                _XCate[i].Text = String.Format("{0}", _Define.DITable[0].Rows[i + (nXindex * 32)]["Cate"]);
                _XComment[i].Text = String.Format("{0}", _Define.DITable[0].Rows[i + (nXindex * 32)]["Comment"]);
            }
        }

        private void tabControl1_SelectedIndexChanged(object sender, EventArgs e)
        {
            nYindex = tabControl1.SelectedIndex;
        }

        private void tabControl2_SelectedIndexChanged(object sender, EventArgs e)
        {
            nXindex = tabControl2.SelectedIndex;
        }
    }
}
