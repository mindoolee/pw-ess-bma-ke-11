using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;

namespace _PeopleWorks__UPB4860_Gen3_Counter
{
	class ClientSoket
	{
		public class AsyncObject {
			public Byte[] Buffer;
			public Socket WorkingSocket;
			public AsyncObject(Int32 bufferSize) {
				this.Buffer = new Byte[bufferSize];
			}
		}
		 
		private Boolean g_Connected;
		private Socket m_ClientSocket = null;
		private AsyncCallback m_fnReceiveHandler;
		private AsyncCallback m_fnSendHandler;

		public ClientSoket()
		{

			// 비동기 작업에 사용될 대리자를 초기화합니다.
			m_fnReceiveHandler = new AsyncCallback(handleDataReceive);
			m_fnSendHandler = new AsyncCallback(handleDataSend);

		}
		
		public Boolean Connected {
			get {
				return g_Connected;
			}
		}

		public void ConnectToServer(String hostName, UInt16 hostPort) {
			// TCP 통신을 위한 소켓을 생성합니다.
			m_ClientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.IP);
		 
			Boolean isConnected = false;
			try {
				// 연결 시도
				m_ClientSocket.Connect(hostName, hostPort);
				
				// 연결 성공
				isConnected = true;
			} catch {
				// 연결 실패 (연결 도중 오류가 발생함)
				isConnected = false;
			}
			g_Connected = isConnected;
			
			if ( isConnected ) {
		
				// 4096 바이트의 크기를 갖는 바이트 배열을 가진 AsyncObject 클래스 생성
				AsyncObject ao = new AsyncObject(4096);
			 
				// 작업 중인 소켓을 저장하기 위해 sockClient 할당
				ao.WorkingSocket = m_ClientSocket;
			 
				// 비동기적으로 들어오는 자료를 수신하기 위해 BeginReceive 메서드 사용!
				m_ClientSocket.BeginReceive(ao.Buffer, 0, ao.Buffer.Length, SocketFlags.None, m_fnReceiveHandler, ao);
				
				Console.WriteLine("연결 성공!");
				
			} else {
				
				Console.WriteLine("연결 실패!");
				
			}
		}
		
		public void StopClient() {
			// 가차없이 클라이언트 소켓을 닫습니다.
			if (m_ClientSocket == null) { return; }
            try
            {
                m_ClientSocket.Close();
            }
            catch { }
		}
		 
		public void SendMessage(String message) {
			// 추가 정보를 넘기기 위한 변수 선언
			// 크기를 설정하는게 의미가 없습니다.
			// 왜냐하면 바로 밑의 코드에서 문자열을 유니코드 형으로 변환한 바이트 배열을 반환하기 때문에
			// 최소한의 크기르 배열을 초기화합니다.
			AsyncObject ao = new AsyncObject(1);
		 
			// 문자열을 바이트 배열으로 변환
			ao.Buffer = Encoding.Unicode.GetBytes(message);
			
			ao.WorkingSocket = m_ClientSocket;
		 
			// 전송 시작!
			try {
				m_ClientSocket.BeginSend(ao.Buffer, 0, ao.Buffer.Length, SocketFlags.None, m_fnSendHandler, ao);
			} catch (Exception ex) {
				Console.WriteLine("전송 중 오류 발생!\n메세지: {0}", ex.Message);
			}
		}
		 
		private void handleDataReceive(IAsyncResult ar) {
		 
			// 넘겨진 추가 정보를 가져옵니다.
			// AsyncState 속성의 자료형은 Object 형식이기 때문에 형 변환이 필요합니다~!
			AsyncObject ao = (AsyncObject) ar.AsyncState;
		 
			// 받은 바이트 수 저장할 변수 선언
			Int32 recvBytes; 
			
			try {
				// 자료를 수신하고, 수신받은 바이트를 가져옵니다.
				recvBytes = ao.WorkingSocket.EndReceive(ar);
			} catch {
				// 예외가 발생하면 함수 종료!
				return;
			}
		 
			// 수신받은 자료의 크기가 1 이상일 때에만 자료 처리
			if ( recvBytes > 0 ) {
				// 공백 문자들이 많이 발생할 수 있으므로, 받은 바이트 수 만큼 배열을 선언하고 복사한다.
				Byte[] msgByte = new Byte[recvBytes];
				Array.Copy(ao.Buffer, msgByte, recvBytes);

                string strReadMsg = Encoding.Unicode.GetString(msgByte);
				// 받은 메세지를 출력
                //Program.ViewMessage(strReadMsg);

                string[] strCount = strReadMsg.Split(',');

                for (int i = 0; i < 10; i++)
                {


                    if (i > 4)
                    {
                        int.TryParse(strCount[i], out Program.nNowCount[i - 5]);
                    }
                    else
                    {
                        int.TryParse(strCount[i], out Program.nMaxCount[i]);
                    }
                }


                for(int i = 10; i < 15; i++)
                {
                    if(strCount[i] == "0")
                    {
                        Program.bSelectTool[i - 10] = false;
                    }
                    else if(strCount[i] == "1")
                    {
                        Program.bSelectTool[i - 10] = true;
                    }
                }

                if(strCount[15] == "0")
                {
					_SysInfo.bUpUnLock = false;
					_SysInfo.bUnlock = false;
                }
                else if(strCount[15] == "1")			// UP은 해제 안함
                {
                    _SysInfo.bUnlock = true;
					_SysInfo.bUpUnLock = false;
				}
				else if(strCount[15] == "2")			// UP 까지 전부 해제
				{
					_SysInfo.bUnlock = true;
					_SysInfo.bUpUnLock = true;
				}


                if(strCount[16] == "0")
                {
                    _SysInfo.bUseScanRead = false;
                    _SysInfo.bUseCMAScan = false;
                }
                else if(strCount[16] == "1")
                {
                    _SysInfo.bUseCMAScan = false;
                    _SysInfo.bUseScanRead = true;
                    _SysInfo.bScanOk = false;
                }
                else if(strCount[16] == "2")
                {
                    _SysInfo.bUseCMAScan = false;
                    _SysInfo.bUseScanRead = true;
                    _SysInfo.bScanOk = true;
                }
                else if(strCount[16] == "5")
                {
                    _SysInfo.bUseCMAScan = true;
                    _SysInfo.bUseScanRead = false;
                    _SysInfo.bCMAOk = true;
                    _SysInfo.bBMSOk = true;
                }
                else if (strCount[16] == "6")
                {
                    _SysInfo.bUseCMAScan = true;
                    _SysInfo.bUseScanRead = false;
                    _SysInfo.bCMAOk = true;
                    _SysInfo.bBMSOk = false;
                }
                else if (strCount[16] == "7")
                {
                    _SysInfo.bUseCMAScan = true;
                    _SysInfo.bUseScanRead = false;
                    _SysInfo.bCMAOk = false;
                    _SysInfo.bBMSOk = true;
                }
                else if (strCount[16] == "8")
                {
                    _SysInfo.bUseCMAScan = true;
                    _SysInfo.bUseScanRead = false;
                    _SysInfo.bCMAOk = false;
                    _SysInfo.bBMSOk = false;
                }

                try
                {
                    // 체결 작업 대기
                    if(strCount[17] == "0")
                    {
                        // 입력없음
                        _SysInfo.nTiteLog = 0;
                    }
                    else if(strCount[17] == "1")
                    {
                        //ING
                        _SysInfo.nTiteLog = 1;
                    }
                    else if(strCount[17] == "2")
                    {
                        //체결 OK
                        _SysInfo.nTiteLog = 2;
                    }
                    else if (strCount[17] == "3")
                    {
                        //체결 NG
                        _SysInfo.nTiteLog = 3;
                    }
                }
                catch { }

                int nClickIndex = 0;

                for (int i = 0; i < 5;i++ )
                {
                    if(_SysInfo.bPushUp[i])
                    {
                        _SysInfo.bPushUp[i] = false;
                        nClickIndex = 1 + i;
                    }

                    if(_SysInfo.bPushDW[i])
                    {
                        _SysInfo.bPushDW[i] = false;    
                        nClickIndex = 6 + i;
                    }

                    if(_SysInfo.bPushCLR[i])
                    {
                        _SysInfo.bPushCLR[i] = false;
                        nClickIndex = 11 + i;
                    }
                }
                Program.bReadData = true;
                SendMessage(nClickIndex.ToString());

				Console.WriteLine("메세지 받음: {0}", Encoding.Unicode.GetString(msgByte));
			}
		 
			try {
				// 자료 처리가 끝났으면~
				// 이제 다시 데이터를 수신받기 위해서 수신 대기를 해야 합니다.
				// Begin~~ 메서드를 이용해 비동기적으로 작업을 대기했다면
				// 반드시 대리자 함수에서 End~~ 메서드를 이용해 비동기 작업이 끝났다고 알려줘야 합니다!
				ao.WorkingSocket.BeginReceive(ao.Buffer, 0, ao.Buffer.Length, SocketFlags.None, m_fnReceiveHandler, ao);
			} catch (Exception ex) {
				// 예외가 발생하면 예외 정보 출력 후 함수를 종료한다.
				Console.WriteLine("자료 수신 대기 도중 오류 발생! 메세지: {0}", ex.Message);
				return;
			}
		}
		private void handleDataSend(IAsyncResult ar) {
		 
			// 넘겨진 추가 정보를 가져옵니다.
			AsyncObject ao = (AsyncObject) ar.AsyncState;
			
			// 보낸 바이트 수를 저장할 변수 선언
			Int32 sentBytes;
			
			try {
				// 자료를 전송하고, 전송한 바이트를 가져옵니다.
				sentBytes = ao.WorkingSocket.EndSend(ar);
			} catch (Exception ex) {
				// 예외가 발생하면 예외 정보 출력 후 함수를 종료한다.
				Console.WriteLine("자료 송신 도중 오류 발생! 메세지: {0}", ex.Message);
				return;
			}
		 
			if ( sentBytes > 0 ) {
				// 여기도 마찬가지로 보낸 바이트 수 만큼 배열 선언 후 복사한다.
				Byte[] msgByte = new Byte[sentBytes];
				Array.Copy(ao.Buffer, msgByte, sentBytes);
				
				Console.WriteLine("메세지 보냄: {0}", Encoding.Unicode.GetString(msgByte));
			}
		}
	}
}
