using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using System.Data;
using System.Threading;


namespace _PeopleWorks__UPB4860_Gen3_Counter
{
    static class Program
    {
        //========== 쓰레드
        public static Thread MainThread = new Thread(WorkMain);

        public static MainForm _mainform;

        public static ClientSoket cSoket = new ClientSoket();


        public static bool bConnection = false;
        public static Stopwatch tTimer = new Stopwatch();

        public static bool bReadData = new bool();

   

        public static int[] nMaxCount = new int[5];
        public static int[] nNowCount = new int[5];
        public static bool[] bSelectTool = new bool[5];

        /// <summary>
        /// 해당 응용 프로그램의 주 진입점입니다.
        /// </summary>
        [STAThread]
        static void Main()
        {
            bool createdNew = true;

            using (Mutex mutex = new Mutex(true, Application.ProductName, out createdNew))
            {
                if (createdNew)
                {
                    Application.EnableVisualStyles();
                    Application.SetCompatibleTextRenderingDefault(false);
                    _mainform = new MainForm();
                    Application.Run(_mainform);
                }
                else
                {
                    MessageBox.Show("프로그램이 이미 실행중 입니다.");
                }
            }
        }




        static void WorkMain()
        {
            LoadIniFile();

            tTimer.Restart();

            while (!_SysInfo.bMainProcessStop)
            {
             
                    if(bReadData)
                    {
                        bConnection = true;    
                        bReadData = false;
                        tTimer.Restart();
                    }
                    else if(tTimer.ElapsedMilliseconds > 5000)
                    {
                        bConnection = false;
                        tTimer.Restart();
                        cSoket.StopClient();
                        cSoket.ConnectToServer(_Config.strIP, _Config.nPort);
                    }
            
                
                Thread.Sleep(20);
            }
            
            SaveIniFile();
            _mainform.BeginInvoke(new Action(() => _mainform.Close()));

        }

        public static void ViewMessage(string str)
        {
            MessageBox.Show(str);
        }


        


        public static void SaveIniFile()
        {
            string strPath = "./Config.ini";
            _IniFile.IniWriteValue("COMM", "strIP", _Config.strIP, strPath);
            _IniFile.IniWriteValue("COMM", "strPort", _Config.nPort.ToString(), strPath);
            _IniFile.IniWriteValue("COMM", "strSTNum", _Config.strSTNum, strPath);
        }


        static void LoadIniFile()
        {
            string strPath = "./Config.ini";

            _Config.strIP = _IniFile.IniReadValue("COMM", "strIP", "1234", strPath);
            ushort.TryParse(_IniFile.IniReadValue("COMM", "strPort", "1234", strPath), out _Config.nPort);
            _Config.strSTNum = _IniFile.IniReadValue("COMM", "strSTNum", "1234", strPath);
        }

    }




    public static class _Config
    {
        public static string strIP;
        public static ushort nPort;
        public static string strSTNum;

    }

    public static class _SysInfo
    {
        public static bool bMainProcessStop;


        public static bool[] bPushUp = new bool[5];
        public static bool[] bPushDW = new bool[5];
        public static bool[] bPushCLR = new bool[5];

        public static bool bUnlock;
        public static bool bUpUnLock;



        public static bool bUseScanRead;
        public static bool bScanOk;

        public static bool bUseCMAScan;
        public static bool bCMAOk;
        public static bool bBMSOk;

        public static int nTiteLog;

         
    }

    public class _IniFile
    {
        [DllImport("kernel32.dll")]
        private static extern int GetPrivateProfileString(String section, String key, String def, StringBuilder retVal, int Size, String filePat);

        [DllImport("Kernel32.dll")]
        private static extern long WritePrivateProfileString(String Section, String Key, String val, String filePath);

        public static void IniWriteValue(String Section, String Key, String Value, string avaPath)
        {
            WritePrivateProfileString(Section, Key, Value, avaPath);
        }

        public static String IniReadValue(String Section, String Key, string def, string avsPath)
        {
            StringBuilder temp = new StringBuilder(2000);
            int i = GetPrivateProfileString(Section, Key, def, temp, 2000, avsPath);
            return temp.ToString();
        }
    } 
}
 