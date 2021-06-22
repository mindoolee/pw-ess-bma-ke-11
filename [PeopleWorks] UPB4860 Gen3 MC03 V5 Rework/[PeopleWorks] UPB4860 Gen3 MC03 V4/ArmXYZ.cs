using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
	// 너트러너 Arm XYZ 타입
	public class ArmXYZ
	{
        // XYZ 버전 너트러너 암

        public int nPosX = 0;
        public int nPosY = 0;
        public int nPosZ = 0;
        public string strStatus = "";
        public byte byCheckSum = 0x00;

        public string strReadCheckSum = "";

        public bool bPortStat = false;


        private Mirae_Timer tMainTimer = new Mirae_Timer();

        private byte[] byStx = new byte[] { 0x1B };
        private byte[] byEtx = new byte[] { 0x0D };
        private byte[] buff = new byte[1024];        // 수신버퍼 최대 사이즈

        public SerialPort port = new SerialPort();
        private Stopwatch watch = new Stopwatch();

        private int nCurrentStep = 0;
        private int nBufferIndex = 0;

        private string strReadData = "";

        public void Process()
        {

            if (!port.IsOpen) { bPortStat = false; return; }


            switch (nCurrentStep)
            {
                case 0:
                    // 통신 커맨드 전송
                    try
                    {
                        port.ReadExisting();        // 버퍼비우기
                        port.DiscardInBuffer();
                        port.DiscardOutBuffer();
                        ClearBuffer();
                        WirteData("R");
                        tMainTimer.Start(2000);
                        nCurrentStep = 10;
                    }
                    catch { }
                    break;


                case 10:
                    // 데이터가 들어오면 읽기
                    if (tMainTimer.Verify())
                    {
                        // 시간내 데이터가 안들어오면 0번으로 이동
                        bPortStat = false;
                        nCurrentStep = 0;
                    }

                    try
                    {


                        while (port.BytesToRead > 0)
                        {
                            port.Read(buff, nBufferIndex++, 1);

                            // 1B가 들어올경우 초기화
                            if (buff[Math.Max((nBufferIndex - 1), 0)] == 0x1B)
                            {
                                ClearBuffer();
                                buff[0] = 0x1B;
                                nBufferIndex++;
                            }
                            
                            
                            // 25개 들어왔을때 파싱함
                            if (buff[Math.Max(nBufferIndex - 1, 0)] == 0x0D && nBufferIndex == 25)
                            {
                                

                                strReadData = Encoding.Default.GetString(buff, 1, nBufferIndex - 2);

                                if (strReadData.Split(',').Length == 5)
                                {
                                    byCheckSum = 0x00;
                                    for (int i = 0; i < 22; i++)
                                    {
                                        byCheckSum += buff[i];
                                    }
                                    if(strReadData.Split(',')[4] == byCheckSum.ToString("X"))
                                    {
                                        strStatus = strReadData.Split(',')[0];
                                        int.TryParse(strReadData.Split(',')[1], out nPosX);
                                        int.TryParse(strReadData.Split(',')[2], out nPosY);
                                        int.TryParse(strReadData.Split(',')[3], out nPosZ);
                                        strReadCheckSum = strReadData.Split(',')[4];

                                    }


                                    bPortStat = true;
                                }
                                ClearBuffer();
                                tMainTimer.Start(10);        // 10ms 단위로 읽음
                                nCurrentStep++;              // 정상적인 데이터가 들어왔다면 스텝 20번으로 이동
                            }
                        }
                    }
                    catch { }
                    break;

                case 11:
                    if (!tMainTimer.Verify()) { break; }

                    nCurrentStep = 0;
                    break;
            }

        }



        public void WirteData(string strData)
        {
            try
            {
                port.Write(new byte[] { 0x1B }, 0, 1);
                port.Write(strData);
                port.Write(new byte[] { 0x0D }, 0, 1);
            }
            catch { }
        }


        public void SetPort(String strPortName, int nBaudRate, Parity nParity, int nDataBit, StopBits nStopBit)
        {
            port.PortName = strPortName;
            port.BaudRate = nBaudRate;
            port.Parity = nParity;
            port.DataBits = nDataBit;
            port.StopBits = nStopBit;

            port.RtsEnable = true;
            port.DtrEnable = true;
        }

        public bool PortOpen()
        {
            if (port.IsOpen)
            {
                try
                {
                    port.Close();
                    port.Open();
                    return true;
                }
                catch { return false; }
            }
            else
            {
                try
                {
                    port.Open();
                    return true;
                }
                catch { return false; }
            }

        }
        public void CloseComm()
        {
            port.Close();
        }

        void ClearBuffer()
        {
            Array.Clear(buff, 0, buff.Length);
            nBufferIndex = 0;
        }



    }
}
