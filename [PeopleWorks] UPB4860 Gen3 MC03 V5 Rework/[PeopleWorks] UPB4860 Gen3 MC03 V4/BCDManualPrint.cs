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
    public partial class BCDManualPrint : Form
    {
        public BCDManualPrint()
        {
            InitializeComponent();
        }

        private void simpleButton2_Click(object sender, EventArgs e)
        {

        }

        private void BCDManualPrint_Load(object sender, EventArgs e)
        {



            if (Program._ModelInfo.bUseCmaBizBCD || Program._ModelInfo.bUseSharpPrint)
            {
                richTextBox1.Text = "";
            }
            else
            {
                richTextBox1.Text = Program._ModelInfo.strComment1 + Program._ModelInfo.strComment3;
            }

            richTextBox3.Text = Program.GetPrintLotBarcode(Program._LotCount.nLotCount);

        //    if (!Program._ModelInfo.bUseSharpPrint)
        //    {

        //        if (Program._ModelInfo.bUnUseLineSymbol)
        //        {
        //            if (Program._ModelInfo.bUseXYZPrint)
        //            {
        //                string[] strMData = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "X", "Y", "Z" };
        //                richTextBox3.Text = Program._LotCount.tLotClearTime.ToString("yyyy");
        //                richTextBox3.Text += strMData[Program._LotCount.tLotClearTime.Month - 1];
        //                richTextBox3.Text += Program._LotCount.tLotClearTime.ToString("dd");
        //                richTextBox3.Text += String.Format("{0:D4}", (Program._LotCount.nLotCount + _Config.nStartLotNum));

        //                //richTextBox3.Text = Program._ModelInfo.tLotClearTime.ToString("yyMMdd") + Program._ModelInfo.nLotCount.ToString("0000");
        //            }
        //            else
        //            {
        //                richTextBox3.Text = Program._LotCount.tLotClearTime.ToString("yyMMdd") + (Program._LotCount.nLotCount + _Config.nStartLotNum).ToString("0000");
        //            }
        //        }
        //        else
        //        {
        //            if (Program._ModelInfo.bUseXYZPrint)
        //            {
        //                string[] strMData = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "X", "Y", "Z" };

        //                richTextBox3.Text = Program._LotCount.tLotClearTime.ToString("yyyy");
        //                richTextBox3.Text += strMData[Program._LotCount.tLotClearTime.Month - 1];
        //                richTextBox3.Text += Program._LotCount.tLotClearTime.ToString("dd");
        //                richTextBox3.Text += Program._ModelInfo.strBCDSymbol;
        //                richTextBox3.Text += String.Format("{0:D3}", (Program._LotCount.nLotCount + _Config.nStartLotNum));
        //            }
        //            else
        //            {
        //                richTextBox3.Text = Program._LotCount.tLotClearTime.ToString("yyMMdd") + Program._ModelInfo.strBCDSymbol + (Program._LotCount.nLotCount + _Config.nStartLotNum).ToString("000");
        //            }

        //        }
        //    }
        //    else
        //    {
        //        richTextBox3.Text += Program._ModelInfo.strBCDSymbol;
        //        richTextBox3.Text += (char)(0x41 + Program._LotCount.tLotClearTime.Year - 2017);
        //        string[] strMData = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "X", "Y", "Z" };
        //        richTextBox3.Text += strMData[Program._LotCount.tLotClearTime.Month - 1];
        //        richTextBox3.Text += Program._LotCount.tLotClearTime.ToString("dd");
        //        richTextBox3.Text += String.Format("{0:D3}", (Program._LotCount.nLotCount + _Config.nStartLotNum));
        //    }
        }

        private void simpleButton17_Click(object sender, EventArgs e)
        {
            Program._BCDPrint.strManualModelInfo = richTextBox1.Text;
            Program._BCDPrint.strManualPrintBCD = richTextBox3.Text;
            Program._BCDPrint.bManualMode = true;
            Program._BCDPrint.bPrintStart = true;

            string strFolderPath = String.Format(@"BcdRePrintLog\\");

            DirectoryInfo dir = new DirectoryInfo(strFolderPath);
            if (dir.Exists == false) { dir.Create(); }

            string savePath = String.Format("{0}{1:D4}{2:D2}{3:D2}.txt", strFolderPath, DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);

            String strMessge = System.DateTime.Now.ToString("[HH:mm:ss]") + " " + richTextBox1.Text + richTextBox3.Text + Environment.NewLine;

            System.IO.File.AppendAllText(savePath, strMessge, Encoding.Default);
        }
    }
}
