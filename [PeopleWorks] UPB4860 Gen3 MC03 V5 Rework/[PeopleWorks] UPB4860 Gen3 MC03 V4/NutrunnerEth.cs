using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.Windows.Forms;
using System.Diagnostics;
using System.Threading;
using System.IO;

namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
	// 이더넷 타입 너트러너 클래스

	class NutrunnerEth
	{
		public int nStation;
		public string strIP;
		public int nPort;

		public bool bPSet;
		public int nPSet;

		string strPramID;
		string strTorque;
		string strAngle;
		string strTime;
		string strResult;
		string strSaveResult;
		string strRundownAngle;

		public double dbTorqueData;
		public int nAngleData;

		Socket soket;
		IPEndPoint ep;
		public int nCurrentStep;
		byte[] buff = new byte[2048];                   // 수신버퍼
		byte[] btEtx = new byte[] { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00 };

		Stopwatch ReConnetTimer = new Stopwatch();
		Stopwatch AliveTimer = new Stopwatch();
		string strReadData = "";

		bool bAlive = false;


		public void Process()
		{
			
			//소켓 연결이 되어있지않다면 해당 시간마다 연결 시도함
			if (!soket.Connected)
			{
				nCurrentStep = 0;
				if (ReConnetTimer.IsRunning)
				{
					if (ReConnetTimer.ElapsedMilliseconds > 5000)			// 소켓이 닫혀있다면 5초마다 재접속 시도한다
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
					nCurrentStep = 10;
					break;

				case 10:
					SendData("0020" +"0001" + "0010");
					Array.Clear(buff, 0, buff.Length);  // 버퍼 클리어
					AliveTimer.Restart();
					nCurrentStep++;
					break;
				
				case 11:
					if(AliveTimer.ElapsedMilliseconds > 5000)
					{
						nCurrentStep = 0;
					}

					if (ReadData(ref buff))
					{
						strReadData = Encoding.Default.GetString(buff);
						if(strReadData.Substring(4,4) == "0002" || strReadData.Substring(4, 4) == "0004")
						{
							nCurrentStep = 20;
						}
					}
					break;


				case 20:
					SendData("0020" + "0060" + "0020");
					Array.Clear(buff, 0, buff.Length);  // 버퍼 클리어
					nCurrentStep++;
					break;

				case 21:
					if (AliveTimer.ElapsedMilliseconds > 5000)
					{
						nCurrentStep = 0;
					}

					if (ReadData(ref buff))
					{
						strReadData = Encoding.Default.GetString(buff);
						if (strReadData.Substring(4, 4) == "0005" || strReadData.Substring(4, 4) == "0004")
						{
							nCurrentStep = 30;
						}
					}
					break;


				case 30:
					if (bPSet)
					{
						bPSet = false;
						nCurrentStep = 50;
						break;
					}
					SendData("0020" + "9999" + "0010");
					Array.Clear(buff, 0, buff.Length);  // 버퍼 클리어
					AliveTimer.Restart();
					bAlive = false;
					nCurrentStep++;
					break;

				case 31:
					if(AliveTimer.ElapsedMilliseconds > 3000)
					{
						if(bAlive)
						{
							nCurrentStep = 30;          // 3초마다 재전송
						}
						else
						{
							nCurrentStep = 0;
						}
					}

					if(ReadData(ref buff))
					{
						//데이터가 들어온 경우 비교
						strReadData = Encoding.Default.GetString(buff);
						if(strReadData.Substring(4,4) == "9999")
						{
							bAlive = true;
						}
						else if(strReadData.Substring(4,4) == "0061")
						{

							try
							{
								//strPramID = readTemp.Substring(91, 3);
								//strTorque = readTemp.Substring(141, 6);
								//strAngle = readTemp.Substring(170, 5);
								//strResult = readTemp.Substring(108, 1);


								// 신규 너트러너 데이터 파싱 [ Rev 2 ] 김상구 팀장 요청 * RunDown Angle 데이터 추출 추가 2018. 12. 16
								strPramID = strReadData.Substring(92, 3);                          // Parameter Sst ID
								strTorque = strReadData.Substring(183, 6);                         // Torque
								strAngle = strReadData.Substring(212, 5);                          // Angle
								strResult = strReadData.Substring(120, 1);
								strTime = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");         // 현재 시간 기준으로 저장
								strRundownAngle = strReadData.Substring(233, 5);                   // Rundown Angle [ Torque 를 적용받지않는 Angle값 ]
																								// ㄴ 요청사유 : 원자재 불량으로 인한 사회불량 발생

								if (strResult == "0") strSaveResult = "NG";
								else if (strResult == "1") strSaveResult = "OK";
								else strSaveResult = "N/A";
								strTime = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");         // 현재 시간 기준으로 저장


								double.TryParse(strTorque, out dbTorqueData);           // 토크값 변환
								int.TryParse(strAngle, out nAngleData);                 // 앵글값 변환

								{
									string strMessge = "";

									if (nStation == 2)
									{
										strMessge = String.Format("ST : {0}, ", nStation) +
																	"Time : " + strTime +
																	", Param ID :" + strPramID +
																	", Torque :" + strTorque +
																	", Angle : " + strAngle +
																	", Rundown Angle : " + strRundownAngle +
																	", Result : " + strSaveResult + "\r\n";
									}
									else
									{
										strMessge = String.Format("ST : {0}, ", nStation) +
																	 "Time : " + strTime +
																	 ", Param ID :" + strPramID +
																	 ", Torque :" + strTorque +
																	 ", Angle : " + strAngle +
																	 ", Rundown Angle : " + strRundownAngle +
																	 ", Result : " + strSaveResult + "\r\n";
									}

									string strFolderPath = String.Format(@"DATA\\NUTRUNNER{0}\\", nStation);

									DirectoryInfo dir = new DirectoryInfo(strFolderPath);
									if (dir.Exists == false) { dir.Create(); }

									string savePath = String.Format("{0}{1}.txt", strFolderPath, DateTime.Now.ToString("yyMMdd"));
									System.IO.File.AppendAllText(savePath, strMessge, Encoding.Default);



									strFolderPath = String.Format(@"TEMP_DATA\\ST{0}\\", nStation);

									dir = new DirectoryInfo(strFolderPath);
									if (dir.Exists == false) { dir.Create(); }

									savePath = String.Format("{0}ST{1}.txt", strFolderPath, nStation);
									System.IO.File.AppendAllText(savePath, strMessge, Encoding.Default);

								}
							}
							catch { }

							nCurrentStep = 40;
						}
					}
					break;


				case 40:
					SendData("0020" + "0062" + "0010");
					Array.Clear(buff, 0, buff.Length);  // 버퍼 클리어
					nCurrentStep = 30;
					break;


				case 50:
					SendData("00230018            " + nPSet.ToString("000"), true);
					Array.Clear(buff, 0, buff.Length);  // 버퍼 클리어
					nCurrentStep = 30;
					break;
			}
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
			catch (Exception e) { Program.AppendLogMsg(nStation.ToString() + ":" + e.Message, LOG_TYPE.ERROR); }
		}


		public void SendData(string strData, bool bNullOnly = false)
		{
			try
			{
				List<byte> sendData = new List<byte>();
				if(bNullOnly)
				{
					sendData.AddRange(Encoding.UTF8.GetBytes(strData));
					sendData.Add(0x00);
				}
				else
				{
					sendData.AddRange(Encoding.UTF8.GetBytes(strData));
					sendData.AddRange(btEtx);
				}
				

				soket.BeginSend(sendData.ToArray(), 0, sendData.ToArray().Length, 0, new AsyncCallback(SendCallback), soket);
			}
			catch(Exception e){ Program.AppendLogMsg(nStation.ToString() + ":" + e.Message, LOG_TYPE.ERROR); }
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
			catch (Exception e) { Program.AppendLogMsg(nStation.ToString() + ":" + e.Message, LOG_TYPE.ERROR); }
		}






		public bool ReadData(ref byte[] vs)
		{
			try
			{
				if(soket.Available > 0)
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
				Program.AppendLogMsg(nStation.ToString() + ":" + e.Message, LOG_TYPE.ERROR);
				return false;
			}
		}



	}
}
