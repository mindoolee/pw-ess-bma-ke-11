using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
    public class Mirae_Timer
    {
        private int tMesc = new int();
        private Stopwatch tTimer = new Stopwatch();

        public Mirae_Timer()
        {
            tMesc = 0;
            tTimer.Restart();
        }

        public void Start(int nIndex)
        {
            tMesc = nIndex;
            tTimer.Restart();
        }

        public bool Verify()
        {
            if (tTimer.ElapsedMilliseconds > tMesc)
            {
                tTimer.Stop();
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}
