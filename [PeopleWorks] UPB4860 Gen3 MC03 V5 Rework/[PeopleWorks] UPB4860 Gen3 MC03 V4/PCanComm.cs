using Peak.Can.Basic;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TPCANHandle = System.UInt16;
using TPCANBitrateFD = System.String;
using TPCANTimestampFD = System.UInt64;

namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
    class PCanComm
    {
        private TPCANHandle m_PcanHandle;
        private TPCANBaudrate m_Baudrate;
        private TPCANType m_HwType;
        public TPCANMsg m_ReadMsg;




        public TPCANStatus ReadMessage()
        {

            TPCANTimestamp CANTimeStamp;
            TPCANStatus stsResult;

            // We execute the "Read" function of the PCANBasic                
            //
            stsResult = PCANBasic.Read(m_PcanHandle, out m_ReadMsg, out CANTimeStamp);

            if (stsResult != TPCANStatus.PCAN_ERROR_QRCVEMPTY)
            {
                if (m_ReadMsg.ID != 0)
                {
                    if (m_ReadMsg.LEN == 8)
                    {
                        Program.AppendLogMsg(String.Format("HIPOT Can Read << 0x{0:X3}, 0x{1:X2}, 0x{2:X2}, 0x{3:X2}, 0x{4:X2}, 0x{5:X2}, 0x{6:X2}, 0x{7:X2}, 0x{8:X2}",
                            m_ReadMsg.ID,
                            m_ReadMsg.DATA[0], m_ReadMsg.DATA[1], m_ReadMsg.DATA[2], m_ReadMsg.DATA[3], m_ReadMsg.DATA[4], m_ReadMsg.DATA[5], m_ReadMsg.DATA[6], m_ReadMsg.DATA[7])
                            , LOG_TYPE.INFO);
                    }

                }

            }



            return stsResult;
        }


        public void ClearBuffer()
        {
            m_ReadMsg = new TPCANMsg();
        }

        public TPCANStatus CanInit(TPCANBaudrate baudrate, TPCANType type)
        {
            TPCANStatus bResult;

            m_Baudrate = baudrate;
            m_HwType = type;


            // Sets the connection status of the main-form
            //
            m_PcanHandle = Convert.ToUInt16("51", 16);

            bResult = PCANBasic.Initialize(m_PcanHandle, m_Baudrate, m_HwType, Convert.ToUInt32("0100", 16), Convert.ToUInt16("3"));

            return bResult;
        }





        public void CloseCan()
        {
            PCANBasic.Uninitialize(m_PcanHandle);
        }


        // 8 바이트 전송 
        public TPCANStatus WriteFrame(uint nID, byte[] btData)
        {

            TPCANMsg CANMsg;

            CANMsg = new TPCANMsg();
            CANMsg.DATA = new byte[8];

            CANMsg.ID = nID;
            CANMsg.LEN = 8;
            CANMsg.MSGTYPE = TPCANMessageType.PCAN_MESSAGE_STANDARD;

            for (int i = 0; i < 8; i++)
            {
                CANMsg.DATA[i] = btData[i];
            }
            Program.AppendLogMsg(String.Format("HIPOT Can Send >> 0x{0:X3}, 0x{1:X2}, 0x{2:X2}, 0x{3:X2}, 0x{4:X2}, 0x{5:X2}, 0x{6:X2}, 0x{7:X2}, 0x{8:X2}",
            CANMsg.ID,
            CANMsg.DATA[0], CANMsg.DATA[1], CANMsg.DATA[2], CANMsg.DATA[3], CANMsg.DATA[4], CANMsg.DATA[5], CANMsg.DATA[6], CANMsg.DATA[7])
            , LOG_TYPE.INFO);

            return PCANBasic.Write(m_PcanHandle, ref CANMsg);
        }
    }
}
