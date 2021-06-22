using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.Windows.Forms;

namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
    public class NutSocket1
    {
        public class AsyncObject
        {
            public Byte[] Buffer;
            public Socket WorkingSocket;
            public AsyncObject(Int32 bufferSize)
            {
                this.Buffer = new Byte[bufferSize];
            }
        }

        private Socket m_ConnectedClient = null;
        public Socket m_ServerSocket = null;
        private AsyncCallback m_fnReceiveHandler;
        private AsyncCallback m_fnSendHandler;
        private AsyncCallback m_fnAcceptHandler;

        public bool bReciveData;
        public string strReadData;

        public NutSocket1()
        {

            // 비동기 작업에 사용될 대리자를 초기화합니다.
            m_fnReceiveHandler = new AsyncCallback(handleDataReceive);
            m_fnSendHandler = new AsyncCallback(handleDataSend);
            m_fnAcceptHandler = new AsyncCallback(handleClientConnectionRequest);

        }

        public void StartServer(UInt16 port)
        {

            try
            {
                // TCP 통신을 위한 소켓을 생성합니다.
                m_ServerSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.IP);

                // 특정 포트에서 모든 주소로부터 들어오는 연결을 받기 위해 포트를 바인딩합니다.
                m_ServerSocket.Bind(new IPEndPoint(IPAddress.Any, port));

                // 연결 요청을 받기 시작합니다.
                m_ServerSocket.Listen(5);

                // BeginAccept 메서드를 이용해 들어오는 연결 요청을 비동기적으로 처리합니다.
                // 연결 요청을 처리하는 함수는 handleClientConnectionRequest 입니다.
                m_ServerSocket.BeginAccept(m_fnAcceptHandler, null);
            }
            catch {  }
        }

        public void StopServer()
        {
            // 가차없이 서버 소켓을 닫습니다.
            try
            {
                m_ServerSocket.Close();
            }
            catch { }
        }

        public void SendMessage(String message)
        {
            if (m_ConnectedClient == null) { return; }
            if (!m_ConnectedClient.Connected) { return; }
            // 추가 정보를 넘기기 위한 변수 선언
            // 크기를 설정하는게 의미가 없습니다.
            // 왜냐하면 바로 밑의 코드에서 문자열을 유니코드 형으로 변환한 바이트 배열을 반환하기 때문에
            // 최소한의 크기르 배열을 초기화합니다.
            AsyncObject ao = new AsyncObject(1);

            // 문자열을 바이트 배열으로 변환
            ao.Buffer = Encoding.Unicode.GetBytes(message);
            
            ao.WorkingSocket = m_ConnectedClient;
            
            // 전송 시작!
            try
            {
                m_ConnectedClient.BeginSend(ao.Buffer, 0, ao.Buffer.Length, SocketFlags.None, m_fnSendHandler, ao);
            }
            catch (Exception ex)
            {
                Console.WriteLine("전송 중 오류 발생!\n메세지: {0}", ex.Message);
            }
        }



        private void handleClientConnectionRequest(IAsyncResult ar)
        {
            if (m_ServerSocket == null) { return; }
            //if (!m_ServerSocket.Connected) { return; }
            Socket sockClient;
            try
            {
                // 클라이언트의 연결 요청을 수락합니다.
                sockClient = m_ServerSocket.EndAccept(ar);
            }
            catch (Exception ex)
            {
                Console.WriteLine("연결 수락 도중 오류 발생! 메세지: {0}", ex.Message);
                return;
            }

            // 4096 바이트의 크기를 갖는 바이트 배열을 가진 AsyncObject 클래스 생성
            AsyncObject ao = new AsyncObject(4096);

            // 작업 중인 소켓을 저장하기 위해 sockClient 할당
            ao.WorkingSocket = sockClient;

            // 클라이언트 소켓 저장
            m_ConnectedClient = sockClient;

            try
            {
                // 비동기적으로 들어오는 자료를 수신하기 위해 BeginReceive 메서드 사용!
                sockClient.BeginReceive(ao.Buffer, 0, ao.Buffer.Length, SocketFlags.None, m_fnReceiveHandler, ao);
            }
            catch (Exception ex)
            {
                // 예외가 발생하면 예외 정보 출력 후 함수를 종료한다.
                Console.WriteLine("자료 수신 대기 도중 오류 발생! 메세지: {0}", ex.Message);
                return;
            }
        }
        private void handleDataReceive(IAsyncResult ar)
        {

            // 넘겨진 추가 정보를 가져옵니다.
            // AsyncState 속성의 자료형은 Object 형식이기 때문에 형 변환이 필요합니다~!
            AsyncObject ao = (AsyncObject)ar.AsyncState;

            // 받은 바이트 수 저장할 변수 선언
            Int32 recvBytes;

            try
            {
                // 자료를 수신하고, 수신받은 바이트를 가져옵니다.
                recvBytes = ao.WorkingSocket.EndReceive(ar);
            }
            catch
            {
                // 예외가 발생하면 함수 종료!
                return;
            }

            // 수신받은 자료의 크기가 1 이상일 때에만 자료 처리
            if (recvBytes > 0)
            {
                // 공백 문자들이 많이 발생할 수 있으므로, 받은 바이트 수 만큼 배열을 선언하고 복사한다.
                Byte[] msgByte = new Byte[recvBytes];
                Array.Copy(ao.Buffer, msgByte, recvBytes);

                // 받은 메세지를 출력
                bReciveData = true;
                strReadData = Encoding.Unicode.GetString(msgByte);
                Console.WriteLine("메세지 받음: {0}", Encoding.Unicode.GetString(msgByte));
            }

            try
            {
                // 비동기적으로 들어오는 자료를 수신하기 위해 BeginReceive 메서드 사용!
                ao.WorkingSocket.BeginReceive(ao.Buffer, 0, ao.Buffer.Length, SocketFlags.None, m_fnReceiveHandler, ao);
            }
            catch (Exception ex)
            {
                // 예외가 발생하면 예외 정보 출력 후 함수를 종료한다.
                Console.WriteLine("자료 수신 대기 도중 오류 발생! 메세지: {0}", ex.Message);
                return;
            }
        }
        private void handleDataSend(IAsyncResult ar)
        {

            // 넘겨진 추가 정보를 가져옵니다.
            AsyncObject ao = (AsyncObject)ar.AsyncState;

            // 보낸 바이트 수를 저장할 변수 선언
            Int32 sentBytes;

            try
            {
                // 자료를 전송하고, 전송한 바이트를 가져옵니다.
                sentBytes = ao.WorkingSocket.EndSend(ar);
            }
            catch (Exception ex)
            {
                // 예외가 발생하면 예외 정보 출력 후 함수를 종료한다.
                Console.WriteLine("자료 송신 도중 오류 발생! 메세지: {0}", ex.Message);
                return;
            }

            if (sentBytes > 0)
            {
                // 여기도 마찬가지로 보낸 바이트 수 만큼 배열 선언 후 복사한다.
                Byte[] msgByte = new Byte[sentBytes];
                Array.Copy(ao.Buffer, msgByte, sentBytes);

                Console.WriteLine("메세지 보냄: {0}", Encoding.Unicode.GetString(msgByte));
            }
        }
    }
}
