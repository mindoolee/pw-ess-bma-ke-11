using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
    class OmronWHTester
    {
		public string strIP;
		public int nPort;

		Socket soket;
		IPEndPoint ep;

		Stopwatch ReConnetTimer = new Stopwatch();

		public int nCurrentStep;
		bool bReadOk = false;

		string strCommand = "";
		string strModels = "";
		string strOption = "";
		byte[] buff = new byte[2048];                   // 수신버퍼
		string strReadData = "";

		double dbWidth = 0.0;
		double dbHight = 0.0;

		public void Process()
		{

			//소켓 연결이 되어있지않다면 해당 시간마다 연결 시도함
			if (!soket.Connected)
			{
				nCurrentStep = 0;
				if (ReConnetTimer.IsRunning)
				{
					if (ReConnetTimer.ElapsedMilliseconds > 5000)           // 소켓이 닫혀있다면 5초마다 재접속 시도한다
					{
						SetPort();
						ReConnetTimer.Restart();
					}
				}
				else
				{
					ReConnetTimer.Restart();
				}
				return;
			}


			// PROCESS
			switch (nCurrentStep)
			{
				case 0:
					break;

				case 10:
					SendData(String.Format("{0} {1} {2}", strCommand, strModels, strOption));
					nCurrentStep = 20;
					break;

				case 20:
					if (ReadData(ref buff))
					{
						strReadData = Encoding.Default.GetString(buff);
						//Program.AppendLogMsg(strReadData, Color.Blue);
						strReadData.Trim(new char[] { (char)0x0D, ' ' });
						string[] strReadData2 = strReadData.Split(',');

						if (strReadData2.Length == 2)
						{
							double.TryParse(strReadData2[0], out dbHight);
							double.TryParse(strReadData2[1], out dbWidth);
							bReadOk = true;
						}
						//else if(strReadData2.Length == 1)
						//{
						//	if(strReadData2[0].Substring(0,2) == "OK" || strReadData2[0].Substring(0, 2) == "NG" || strReadData2[0].Substring(0, 2) == "ER")
						//	{
						//		bReadOk = true;
						//		nCurrentStep = 0;

						//	}
						//}

						Array.Clear(buff, 0, buff.Length);  // 버퍼 클리어
					}
					break;

			}
		}


		public void TestStart()
		{
			bReadOk = false;
			nCurrentStep = 10;
		}


		public double GetWidth()
		{
			return dbWidth;
		}

		public double GetHight()
		{
			return dbHight;
		}

		public bool GetTestFinish()
		{
			return bReadOk;
		}

		public void SetSch(string command, string model, string option)
		{
			strCommand = command;
			strModels = model;
			strOption = option;
		}

		public void SetPort()
		{

			allDone.Reset();
			soket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
			//ep = new IPEndPoint(IPAddress.Parse(strIP), nPort);
			//soket.Connect(ep);
			soket.BeginConnect(IPAddress.Parse(strIP), nPort, new AsyncCallback(ConnectCallback1), soket);

		}

		ManualResetEvent allDone = new ManualResetEvent(false);

		void ConnectCallback1(IAsyncResult ar)
		{
			try
			{
				allDone.Set();
				Socket s = (Socket)ar.AsyncState;
				s.EndConnect(ar);
			}
			catch (Exception e)
			{
				//Program.AppendLogMsg(nStation.ToString() + ":" + e.Message, LOG_TYPE.ERROR); 
			}
		}


		public void SendData(string strData)
		{
			try
			{
				List<byte> sendData = new List<byte>();

				sendData.AddRange(Encoding.UTF8.GetBytes(strData));
				soket.BeginSend(sendData.ToArray(), 0, sendData.ToArray().Length, 0, new AsyncCallback(SendCallback), soket);
			}
			catch (Exception e)
			{
				//Program.AppendLogMsg(nStation.ToString() + ":" + e.Message, LOG_TYPE.ERROR); 
			}
		}


		private ManualResetEvent sendDone = new ManualResetEvent(false);
		private void SendCallback(IAsyncResult ar)
		{
			try
			{
				// Retrieve the socket from the state object.  
				Socket client = (Socket)ar.AsyncState;

				// Complete sending the data to the remote device.  
				int bytesSent = client.EndSend(ar);

				// Signal that all bytes have been sent.  
				sendDone.Set();
			}
			catch (Exception e)
			{
				//Program.AppendLogMsg("외함측정 Camera :" + e.Message, Color.Red); 
			}
		}



		public bool ReadData(ref byte[] vs)
		{
			try
			{
				if (soket.Available > 0)
				{
					soket.Receive(vs);
					return true;
				}
				else
				{
					return false;
				}
			}
			catch (Exception e)
			{
				//Program.AppendLogMsg(nStation.ToString() + ":" + e.Message, LOG_TYPE.ERROR);
				return false;
			}
		}
	}
}
