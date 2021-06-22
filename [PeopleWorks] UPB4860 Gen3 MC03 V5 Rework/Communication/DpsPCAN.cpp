
///////////////////////////////////////////////////////////////////////////////////////////////////
//																								 //
// Project			:	PeakSystem PCAN Handler													 //
// IDE				:	Microsoft Visual Studio 2013											 //
// Created Date		:	2018. 03. 13.															 //
// Modified Date	:	2018. 03. 13.															 //
// Programmer		:	DiMPLe(TM)																 //
//																								 //
// DpsPCAN.cpp																					 //
//																								 //
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
// Includes ///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DpsPCAN.h"
#include "../../DPS Device Library.h"







///////////////////////////////////////////////////////////////////////////////////////////////////
// DLL Function Pointer ///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

TPCANStatus		(__stdcall *PCAN_API_Initialize)(TPCANHandle Channel, TPCANBaudrate Btr0Btr1, TPCANType HwType, DWORD IOPort, WORD Interrupt);
TPCANStatus		(__stdcall *PCAN_API_InitializeFD)(TPCANHandle Channel, TPCANBitrateFD BitrateFD);
TPCANStatus		(__stdcall *PCAN_API_Uninitialize)(TPCANHandle Channel);
TPCANStatus		(__stdcall *PCAN_API_Reset)(TPCANHandle Channel);
TPCANStatus		(__stdcall *PCAN_API_GetStatus)(TPCANHandle Channel);
TPCANStatus		(__stdcall *PCAN_API_Read)(TPCANHandle Channel, TPCANMsg* MessageBuffer, TPCANTimestamp* TimestampBuffer);
TPCANStatus		(__stdcall *PCAN_API_ReadFD)(TPCANHandle Channel, TPCANMsgFD* MessageBuffer, TPCANTimestampFD *TimestampBuffer);
TPCANStatus		(__stdcall *PCAN_API_Write)(TPCANHandle Channel, TPCANMsg* MessageBuffer);
TPCANStatus		(__stdcall *PCAN_API_WriteFD)(TPCANHandle Channel, TPCANMsgFD* MessageBuffer);
TPCANStatus		(__stdcall *PCAN_API_FilterMessages)(TPCANHandle Channel, DWORD FromID, DWORD ToID, TPCANMode Mode);
TPCANStatus		(__stdcall *PCAN_API_GetValue)(TPCANHandle Channel, TPCANParameter Parameter, void* Buffer, DWORD BufferLength);
TPCANStatus		(__stdcall *PCAN_API_SetValue)(TPCANHandle Channel, TPCANParameter Parameter, void* Buffer, DWORD BufferLength);
TPCANStatus		(__stdcall *PCAN_API_GetErrorText)(TPCANStatus Error, WORD Language, LPSTR Buffer);







///////////////////////////////////////////////////////////////////////////////////////////////////
// Declaration ////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

HINSTANCE			CDpsPCAN::m_hLibHandle	= NULL;
CCriticalSection	CDpsPCAN::m_csDeviceReset;
PCAN_LIB_INFO_T		CDpsPCAN::m_stLibraryInfo;
TPCANHandle			CDpsPCAN::m_hHandleArray[PCAN_MAX_HANDLES];






///////////////////////////////////////////////////////////////////////////////////////////////////
// CDpsPCAN Ŭ���� ////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CDpsPCAN, CWnd)

///////////////////////////////////////////////////////////////////////////////
// Ŭ���� ���� ////////////////////////////////////////////////////////////////
CDpsPCAN::CDpsPCAN(CWnd* pParent /* = NULL */)
{
	m_pParentWnd			= NULL;
	m_pMonitorWnd			= NULL;
	m_nDeviceID				= 0;

	m_pThread				= NULL;
	m_bExitThread			= FALSE;
	m_bHoldThread			= FALSE;

	m_bIsDeviceConnected	= FALSE;

	m_nPosHead				= 0;
	m_nPosTail				= 0;

	ZeroMemory(m_stPacketBuffer, sizeof(PCAN_PACKET_T) * PCAN_MAX_RCVD_DATA_BUFFER);
	ZeroMemory(&m_stDeviceInfo, sizeof(PCAN_DEVICE_INFO_T));
}


///////////////////////////////////////////////////////////////////////////////
// Ŭ���� �Ҹ� ////////////////////////////////////////////////////////////////
CDpsPCAN::~CDpsPCAN()
{

}


///////////////////////////////////////////////////////////////////////////////
// �޼��� �� //////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CDpsPCAN, CWnd)

	/////////////////////////////////////////////////////////////////
	// ������ �޼��� ////////////////////////////////////////////////
	ON_WM_DEVICECHANGE()


	/////////////////////////////////////////////////////////////////
	// ����� �޼��� ////////////////////////////////////////////////
	ON_MESSAGE(UM_DPS_DEV_PCAN_RCVD_DATA, OnMsgReceivedData)
	ON_MESSAGE(UM_DPS_DEV_PCAN_DEVICE_REMOVED, OnMsgDeviceRemoved)

END_MESSAGE_MAP()







///////////////////////////////////////////////////////////////////////////////////////////////////
// ������ �̺�Ʈ �ڵ鷯 ///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ����̽� ���� ���� üũ ////////////////////////////////////////////////////
BOOL CDpsPCAN::OnDeviceChange(UINT nEventType, DWORD_PTR dwData)
{
	return	FALSE;
}







///////////////////////////////////////////////////////////////////////////////////////////////////
// ����� �޼��� �ڵ鷯 ///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// USB-CAN ������ ���� ////////////////////////////////////////////////////////
LRESULT CDpsPCAN::OnMsgReceivedData(WPARAM wParam, LPARAM lParam)
{
	return	0L;
}


///////////////////////////////////////////////////////////////////////////////
// ����̽� ���� ���� /////////////////////////////////////////////////////////
LRESULT CDpsPCAN::OnMsgDeviceRemoved(WPARAM wParam, LPARAM lParam)
{
	return	0L;
}







///////////////////////////////////////////////////////////////////////////////////////////////////
// Ŭ���� �Լ� ////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ���̺귯�� �ε� ////////////////////////////////////////////////////////////
BOOL CDpsPCAN::PCAN_LoadLibrary(void)
{
	/////////////////////////////////////////////////////////////////
	// �̹� �ʱ�ȭ�� �Ǿ�������, �н� ///////////////////////////////
	if (CDpsPCAN::m_hLibHandle != NULL)		return	TRUE;


	/////////////////////////////////////////////////////////////////
	// PCAN ä�� ��� ///////////////////////////////////////////////
	CDpsPCAN::m_hHandleArray[0]  = PCAN_ISABUS1;
	CDpsPCAN::m_hHandleArray[1]  = PCAN_ISABUS2;
	CDpsPCAN::m_hHandleArray[2]  = PCAN_ISABUS3;
	CDpsPCAN::m_hHandleArray[3]  = PCAN_ISABUS4;
	CDpsPCAN::m_hHandleArray[4]  = PCAN_ISABUS5;
	CDpsPCAN::m_hHandleArray[5]  = PCAN_ISABUS6;
	CDpsPCAN::m_hHandleArray[6]  = PCAN_ISABUS7;
	CDpsPCAN::m_hHandleArray[7]  = PCAN_ISABUS8;
	CDpsPCAN::m_hHandleArray[8]  = PCAN_DNGBUS1;
	CDpsPCAN::m_hHandleArray[9]  = PCAN_PCIBUS1;
	CDpsPCAN::m_hHandleArray[10] = PCAN_PCIBUS2;
	CDpsPCAN::m_hHandleArray[11] = PCAN_PCIBUS3;
	CDpsPCAN::m_hHandleArray[12] = PCAN_PCIBUS4;
	CDpsPCAN::m_hHandleArray[13] = PCAN_PCIBUS5;
	CDpsPCAN::m_hHandleArray[14] = PCAN_PCIBUS6;
	CDpsPCAN::m_hHandleArray[15] = PCAN_PCIBUS7;
	CDpsPCAN::m_hHandleArray[16] = PCAN_PCIBUS8;
	CDpsPCAN::m_hHandleArray[17] = PCAN_PCIBUS9;
	CDpsPCAN::m_hHandleArray[18] = PCAN_PCIBUS10;
	CDpsPCAN::m_hHandleArray[19] = PCAN_PCIBUS11;
	CDpsPCAN::m_hHandleArray[20] = PCAN_PCIBUS12;
	CDpsPCAN::m_hHandleArray[21] = PCAN_PCIBUS13;
	CDpsPCAN::m_hHandleArray[22] = PCAN_PCIBUS14;
	CDpsPCAN::m_hHandleArray[23] = PCAN_PCIBUS15;
	CDpsPCAN::m_hHandleArray[24] = PCAN_PCIBUS16;
	CDpsPCAN::m_hHandleArray[25] = PCAN_USBBUS1;
	CDpsPCAN::m_hHandleArray[26] = PCAN_USBBUS2;
	CDpsPCAN::m_hHandleArray[27] = PCAN_USBBUS3;
	CDpsPCAN::m_hHandleArray[28] = PCAN_USBBUS4;
	CDpsPCAN::m_hHandleArray[29] = PCAN_USBBUS5;
	CDpsPCAN::m_hHandleArray[30] = PCAN_USBBUS6;
	CDpsPCAN::m_hHandleArray[31] = PCAN_USBBUS7;
	CDpsPCAN::m_hHandleArray[32] = PCAN_USBBUS8;
	CDpsPCAN::m_hHandleArray[33] = PCAN_USBBUS9;
	CDpsPCAN::m_hHandleArray[34] = PCAN_USBBUS10;
	CDpsPCAN::m_hHandleArray[35] = PCAN_USBBUS11;
	CDpsPCAN::m_hHandleArray[36] = PCAN_USBBUS12;
	CDpsPCAN::m_hHandleArray[37] = PCAN_USBBUS13;
	CDpsPCAN::m_hHandleArray[38] = PCAN_USBBUS14;
	CDpsPCAN::m_hHandleArray[39] = PCAN_USBBUS15;
	CDpsPCAN::m_hHandleArray[40] = PCAN_USBBUS16;
	CDpsPCAN::m_hHandleArray[41] = PCAN_PCCBUS1;
	CDpsPCAN::m_hHandleArray[42] = PCAN_PCCBUS2;
	CDpsPCAN::m_hHandleArray[43] = PCAN_LANBUS1;
	CDpsPCAN::m_hHandleArray[44] = PCAN_LANBUS2;
	CDpsPCAN::m_hHandleArray[45] = PCAN_LANBUS3;
	CDpsPCAN::m_hHandleArray[46] = PCAN_LANBUS4;
	CDpsPCAN::m_hHandleArray[47] = PCAN_LANBUS5;
	CDpsPCAN::m_hHandleArray[48] = PCAN_LANBUS6;
	CDpsPCAN::m_hHandleArray[49] = PCAN_LANBUS7;
	CDpsPCAN::m_hHandleArray[50] = PCAN_LANBUS8;
	CDpsPCAN::m_hHandleArray[51] = PCAN_LANBUS9;
	CDpsPCAN::m_hHandleArray[52] = PCAN_LANBUS10;
	CDpsPCAN::m_hHandleArray[53] = PCAN_LANBUS11;
	CDpsPCAN::m_hHandleArray[54] = PCAN_LANBUS12;
	CDpsPCAN::m_hHandleArray[55] = PCAN_LANBUS13;
	CDpsPCAN::m_hHandleArray[56] = PCAN_LANBUS14;
	CDpsPCAN::m_hHandleArray[57] = PCAN_LANBUS15;
	CDpsPCAN::m_hHandleArray[58] = PCAN_LANBUS16;


	/////////////////////////////////////////////////////////////////
	// ���̺귯�� �ε� //////////////////////////////////////////////
	CDpsPCAN::m_hLibHandle = NULL;
	CDpsPCAN::m_hLibHandle = LoadLibrary(_T("PCANBasic"));

	if (CDpsPCAN::m_hLibHandle) {

		/////////////////////////////////////////////////////////////
		// ���̺귯�� �Լ� ���� /////////////////////////////////////
		if ((PCAN_API_Initialize = (TPCANStatus(__stdcall *)(TPCANHandle,TPCANBaudrate,TPCANType,DWORD,WORD))GetProcAddress(CDpsPCAN::m_hLibHandle, "CAN_Initialize")) == NULL)		return	FALSE;
		if ((PCAN_API_InitializeFD = (TPCANStatus(__stdcall *)(TPCANHandle,TPCANBitrateFD))GetProcAddress(CDpsPCAN::m_hLibHandle, "CAN_InitializeFD")) == NULL)						return	FALSE;
		if ((PCAN_API_Uninitialize = (TPCANStatus(__stdcall *)(TPCANHandle))GetProcAddress(CDpsPCAN::m_hLibHandle, "CAN_Uninitialize")) == NULL)									return	FALSE;
		if ((PCAN_API_Reset	= (TPCANStatus(__stdcall *)(TPCANHandle))GetProcAddress(CDpsPCAN::m_hLibHandle, "CAN_Reset")) == NULL)													return	FALSE;
		if ((PCAN_API_GetStatus	= (TPCANStatus(__stdcall *)(TPCANHandle))GetProcAddress(CDpsPCAN::m_hLibHandle, "CAN_GetStatus")) == NULL)											return	FALSE;
		if ((PCAN_API_Read = (TPCANStatus(__stdcall *)(TPCANHandle,TPCANMsg*,TPCANTimestamp*))GetProcAddress(CDpsPCAN::m_hLibHandle, "CAN_Read")) == NULL)							return	FALSE;
		if ((PCAN_API_ReadFD = (TPCANStatus(__stdcall *)(TPCANHandle,TPCANMsgFD*,TPCANTimestampFD*))GetProcAddress(CDpsPCAN::m_hLibHandle, "CAN_ReadFD")) == NULL)					return	FALSE;
		if ((PCAN_API_Write	= (TPCANStatus(__stdcall *)(TPCANHandle,TPCANMsg*))GetProcAddress(CDpsPCAN::m_hLibHandle, "CAN_Write")) == NULL)										return	FALSE;
		if ((PCAN_API_WriteFD = (TPCANStatus(__stdcall *)(TPCANHandle,TPCANMsgFD*))GetProcAddress(CDpsPCAN::m_hLibHandle, "CAN_WriteFD")) == NULL)									return	FALSE;
		if ((PCAN_API_FilterMessages = (TPCANStatus(__stdcall *)(TPCANHandle,DWORD,DWORD,TPCANMode))GetProcAddress(CDpsPCAN::m_hLibHandle, "CAN_FilterMessages")) == NULL)			return	FALSE;
		if ((PCAN_API_GetValue = (TPCANStatus(__stdcall *)(TPCANHandle,TPCANParameter,void*,DWORD))GetProcAddress(CDpsPCAN::m_hLibHandle, "CAN_GetValue")) == NULL)					return	FALSE;
		if ((PCAN_API_SetValue = (TPCANStatus(__stdcall *)(TPCANHandle,TPCANParameter,void*,DWORD))GetProcAddress(CDpsPCAN::m_hLibHandle, "CAN_SetValue")) == NULL)					return	FALSE;
		if ((PCAN_API_GetErrorText = (TPCANStatus(__stdcall *)(TPCANStatus,WORD,LPSTR))GetProcAddress(CDpsPCAN::m_hLibHandle, "CAN_GetErrorText")) == NULL)							return	FALSE;


		/////////////////////////////////////////////////////////////
		// ���̺귯�� ���� �ε� /////////////////////////////////////
		USES_CONVERSION;

		TPCANStatus stsResult;
		CHAR		szBuffer[MAX_STRVALUE_S];

		ZeroMemory(&CDpsPCAN::m_stLibraryInfo, sizeof(PCAN_LIB_INFO_T));
		stsResult = PCAN_API_GetValue(PCAN_NONEBUS, PCAN_API_VERSION, szBuffer, MAX_STRVALUE_S);
		if (stsResult == PCAN_ERROR_OK)		_tcscpy_s(CDpsPCAN::m_stLibraryInfo.szVersionAPI, MAX_STRINPUT_S, A2W(szBuffer));
		else								_tcscpy_s(CDpsPCAN::m_stLibraryInfo.szVersionAPI, MAX_STRINPUT_S, _T("UNKNOWN"));

		return	TRUE;
	}

	return	FALSE;
}


///////////////////////////////////////////////////////////////////////////////
// ���̺귯�� ���� ////////////////////////////////////////////////////////////
BOOL CDpsPCAN::PCAN_FreeLibrary(void)
{
	BOOL	bResult = FALSE;
	
	FreeLibrary(CDpsPCAN::m_hLibHandle);
	CDpsPCAN::m_hLibHandle = NULL;

	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// �ϵ���� �˻� //////////////////////////////////////////////////////////////
BOOL CDpsPCAN::PCAN_FindDevice(void)
{
	TPCANStatus		stsResult		= 0;
	UINT			nIndexDevice	= 0;
	INT				nBuffer			= 0;
	BOOL			bIsFD			= FALSE;


	/////////////////////////////////////////////////////////////////
	// �ϵ���� �˻� ////////////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < PCAN_MAX_HANDLES; nIndex++) {
	
		// Plug&Play �𵨸� �˻�
		if (CDpsPCAN::m_hHandleArray[nIndex] > PCAN_DNGBUS1) {

			stsResult = PCAN_API_GetValue((TPCANHandle)CDpsPCAN::m_hHandleArray[nIndex], PCAN_CHANNEL_CONDITION, (void*)&nBuffer, sizeof(nBuffer));
			if ((stsResult == PCAN_ERROR_OK) && (nBuffer & PCAN_CHANNEL_AVAILABLE) == PCAN_CHANNEL_AVAILABLE) {

				stsResult	= PCAN_API_GetValue((TPCANHandle)CDpsPCAN::m_hHandleArray[nIndex], PCAN_CHANNEL_FEATURES, (void*)&nBuffer, sizeof(nBuffer));
				bIsFD		= ((stsResult == PCAN_ERROR_OK) && (nBuffer & FEATURE_FD_CAPABLE)) ? TRUE : FALSE;
				CDpsPCAN::m_stLibraryInfo.stDeviceInfo[nIndexDevice] = PCAN_GetChannelName(CDpsPCAN::m_hHandleArray[nIndex], bIsFD);
				nIndexDevice++;
			}
		}
	}

	CDpsPCAN::m_stLibraryInfo.dwDeviceCount = nIndexDevice;


	return	nIndexDevice ? TRUE : FALSE;
}


///////////////////////////////////////////////////////////////////////////////
// ����̽� ä�� ���� /////////////////////////////////////////////////////////
PCAN_DEVICE_INFO_T CDpsPCAN::PCAN_GetChannelName(TPCANHandle hHandle, BOOL bIsFD)
{
	PCAN_DEVICE_INFO_T	stDeviceInfo;
	CString				strName		= _T("");


	/////////////////////////////////////////////////////////////////
	ZeroMemory(&stDeviceInfo, sizeof(PCAN_DEVICE_INFO_T));
	stDeviceInfo.hHandle = hHandle;


	/////////////////////////////////////////////////////////////////
	// ä�� ��ȣ ���� ///////////////////////////////////////////////
	if (hHandle < 0x100)	stDeviceInfo.nChannelNo = (INT8U)(hHandle) & 0xF;
	else					stDeviceInfo.nChannelNo = (INT8U)(hHandle) & 0xFF;


	/////////////////////////////////////////////////////////////////
	// ����̽� �̸� ���� ///////////////////////////////////////////
	INT8U				nChannelNo	= 0;
	strName.Format(bIsFD ? _T("%s:FD %d (%Xh)") : _T("%s %d (%Xh)"), PCAN_GetHandleName(hHandle), stDeviceInfo.nChannelNo, stDeviceInfo.hHandle);
	_tcscpy_s(stDeviceInfo.szModelName, MAX_STRINPUT_S, strName);


	return	stDeviceInfo;
}

CString CDpsPCAN::PCAN_GetHandleName(TPCANHandle hHandle)
{
	CString		strName = _T("PCAN_NONE");


	switch(hHandle) {

		case PCAN_ISABUS1	:
		case PCAN_ISABUS2	:
		case PCAN_ISABUS3	:
		case PCAN_ISABUS4	:
		case PCAN_ISABUS5	:
		case PCAN_ISABUS6	:
		case PCAN_ISABUS7	:
		case PCAN_ISABUS8	:
								strName = _T("PCAN_ISA");
								break;

		case PCAN_DNGBUS1	:
								strName = _T("PCAN_DNG");
								break;

		case PCAN_PCIBUS1	:
		case PCAN_PCIBUS2	:
		case PCAN_PCIBUS3	:
		case PCAN_PCIBUS4	:
		case PCAN_PCIBUS5	:
		case PCAN_PCIBUS6	:
		case PCAN_PCIBUS7	:
		case PCAN_PCIBUS8	:
		case PCAN_PCIBUS9	:
		case PCAN_PCIBUS10	:
		case PCAN_PCIBUS11	:
		case PCAN_PCIBUS12	:
		case PCAN_PCIBUS13	:
		case PCAN_PCIBUS14	:
		case PCAN_PCIBUS15	:
		case PCAN_PCIBUS16	:
								strName = _T("PCAN_PCI");
								break;

		case PCAN_USBBUS1	:
		case PCAN_USBBUS2	:
		case PCAN_USBBUS3	:
		case PCAN_USBBUS4	:
		case PCAN_USBBUS5	:
		case PCAN_USBBUS6	:
		case PCAN_USBBUS7	:
		case PCAN_USBBUS8	:
		case PCAN_USBBUS9	:
		case PCAN_USBBUS10	:
		case PCAN_USBBUS11	:
		case PCAN_USBBUS12	:
		case PCAN_USBBUS13	:
		case PCAN_USBBUS14	:
		case PCAN_USBBUS15	:
		case PCAN_USBBUS16	:
								strName = _T("PCAN_USB");
								break;

		case PCAN_PCCBUS1	:
		case PCAN_PCCBUS2	:
								strName = _T("PCAN_PCC");
								break;

		case PCAN_LANBUS1	:
		case PCAN_LANBUS2	:
		case PCAN_LANBUS3	:
		case PCAN_LANBUS4	:
		case PCAN_LANBUS5	:
		case PCAN_LANBUS6	:
		case PCAN_LANBUS7	:
		case PCAN_LANBUS8	:
		case PCAN_LANBUS9	:
		case PCAN_LANBUS10	:
		case PCAN_LANBUS11	:
		case PCAN_LANBUS12	:
		case PCAN_LANBUS13	:
		case PCAN_LANBUS14	:
		case PCAN_LANBUS15	:
		case PCAN_LANBUS16	:
								strName = _T("PCAN_LAN");
								break;
	}


	return	strName;
}


///////////////////////////////////////////////////////////////////////////////
// �޼��� ���� (���ڿ� ��ȯ) //////////////////////////////////////////////////
CString CDpsPCAN::PCAN_GetTypeMsgString(TPCANMessageType nType)
{
	CString		strValue	= _T("");


    if ((nType & PCAN_MESSAGE_STATUS) != 0)		return	_T("STATUS");
    if ((nType & PCAN_MESSAGE_ERRFRAME) != 0)	return	_T("ERROR");
	if((nType & PCAN_MESSAGE_EXTENDED) != 0)	strValue = _T("EXT");
	else										strValue = _T("STD");

	if((nType & PCAN_MESSAGE_RTR) == PCAN_MESSAGE_RTR) {

		strValue = (strValue + _T("/RTR"));

	} else {

		if(nType > PCAN_MESSAGE_EXTENDED) {

			strValue.Append(_T(" [ "));
            if (nType & PCAN_MESSAGE_FD)	strValue.Append(_T(" FD"));
            if (nType & PCAN_MESSAGE_BRS)	strValue.Append(_T(" BRS"));
            if (nType & PCAN_MESSAGE_ESI)	strValue.Append(_T(" ESI"));
            strValue.Append(_T(" ]"));
		}
	}


	return	strValue;
}







///////////////////////////////////////////////////////////////////////////////////////////////////
// ����� �Լ� ////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ����̽� ���� //////////////////////////////////////////////////////////////
BOOL CDpsPCAN::DeviceOpen(PCAN_CONNECT_INFO_T stConnectInfo, PPCAN_DEVICE_INFO_T pstDeviceInfo /* = NULL */, CWnd* pParentWnd /* = NULL */)
{
	TPCANStatus		stsResult;


	/////////////////////////////////////////////////////////////////
	// �޼��� �ڽ� �ڵ� ���� ////////////////////////////////////////
	m_MessageBox.SetHwnd(GetSafeHwnd());


	/////////////////////////////////////////////////////////////////
	// ���� ���� üũ ///////////////////////////////////////////////
	if (!CDpsPCAN::m_stLibraryInfo.dwDeviceCount)	return	FALSE;
	if (!stConnectInfo.hHandle)						return	FALSE;
	if (!stConnectInfo.wBaudrate)					return	FALSE;


	/////////////////////////////////////////////////////////////////
	// �θ� ������ ���� /////////////////////////////////////////////
	m_pParentWnd = pParentWnd;


	/////////////////////////////////////////////////////////////////
	// ����̽� ID ���� /////////////////////////////////////////////
	m_nDeviceID = stConnectInfo.hHandle;


	/////////////////////////////////////////////////////////////////
	// ����̽� ���� ////////////////////////////////////////////////
	stsResult = PCAN_API_Initialize(stConnectInfo.hHandle, stConnectInfo.wBaudrate, stConnectInfo.nTypeHW, stConnectInfo.dwSelectIO, stConnectInfo.wInterrupt);
	if (stsResult != PCAN_ERROR_OK)		return	FALSE;

	m_bIsDeviceConnected = TRUE;


	/////////////////////////////////////////////////////////////////
	// ����̽� ���� �ε� ///////////////////////////////////////////
	if (pstDeviceInfo) {

		CHAR	szBuffer[MAX_STRVALUE_S];

		ZeroMemory(pstDeviceInfo, sizeof(PCAN_DEVICE_INFO_T));

		// ����̽� �̸� ����
		for (UINT nIndex = 0; nIndex < CDpsPCAN::m_stLibraryInfo.dwDeviceCount; nIndex++) {
		
			if (CDpsPCAN::m_stLibraryInfo.stDeviceInfo[nIndex].hHandle == stConnectInfo.hHandle) {
			
				_tcscpy_s(pstDeviceInfo->szModelName, MAX_STRINPUT_S, CDpsPCAN::m_stLibraryInfo.stDeviceInfo[nIndex].szModelName);
			}
		}

		// ä�� ���� üũ
		stsResult = PCAN_API_GetValue(stConnectInfo.hHandle, PCAN_CHANNEL_VERSION, szBuffer, MAX_STRVALUE_S);
		if (stsResult == PCAN_ERROR_OK) {
		
			CString		strInfo(szBuffer);
			CString		strToken	= _T("");
			INT			nPos		= 0;

			strToken = strInfo.Tokenize(_T("\n"), nPos);
			if (!strToken.IsEmpty())	_tcscpy_s(pstDeviceInfo->szVersion, MAX_STRINPUT_S, strToken);
		}

		// ����̽� ���� ����
		m_stDeviceInfo		 = *pstDeviceInfo;
		m_stDeviceInfo.bIsFD = stConnectInfo.bIsFD;
	}


	/////////////////////////////////////////////////////////////////
	// �۾� ������ ���� /////////////////////////////////////////////
	m_bExitThread				= FALSE;
	m_pThread					= ::AfxBeginThread(ThreadFuncMonitor, this, THREAD_PRIORITY_HIGHEST);
	m_pThread->m_bAutoDelete	= FALSE;

	// ������ ����ȭ �ð� ����
	DPS_Delay_ms(500);


	return	TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// ����̽� �ݱ� //////////////////////////////////////////////////////////////
void CDpsPCAN::DeviceClose(void)
{
	/////////////////////////////////////////////////////////////////
	// �۾� ������ ���� /////////////////////////////////////////////
	if (m_pThread) {

		m_csExitThread.Lock();
		m_bExitThread = TRUE;
		m_csExitThread.Unlock();

		// ������ ���� ���
		DWORD	dwRetCode = ::WaitForSingleObject(m_pThread->m_hThread, 100);
		if (dwRetCode != WAIT_OBJECT_0) {

			// ���� ����
			::TerminateThread(m_pThread->m_hThread, 0);
			CloseHandle(m_pThread->m_hThread);
		}

		// ������ ��ü ����
		m_pThread->m_hThread = NULL;
		delete	m_pThread;
		m_pThread	= NULL;
	}


	/////////////////////////////////////////////////////////////////
	// ����̽� ���� ���� ///////////////////////////////////////////
	TPCANStatus stsResult = PCAN_API_Uninitialize(m_nDeviceID);
	DPS_Delay_ms(500);

	m_bIsDeviceConnected = FALSE;
}


///////////////////////////////////////////////////////////////////////////////
// ����̽� ���� //////////////////////////////////////////////////////////////
BOOL CDpsPCAN::DeviceReset(BOOL bHardReset /* = TRUE */)
{
	/////////////////////////////////////////////////////////////////
	if (!m_bIsDeviceConnected)			return	FALSE;


	/////////////////////////////////////////////////////////////////
	// ����̽� ���� ////////////////////////////////////////////////
	TPCANStatus	stsResult = PCAN_API_Reset(m_nDeviceID);


	/////////////////////////////////////////////////////////////////
	// ���� �ʱ�ȭ //////////////////////////////////////////////////
	ClearBuffer();
	

	return	(stsResult == PCAN_ERROR_OK) ? TRUE : FALSE;
}


///////////////////////////////////////////////////////////////////////////////
// ��Ŷ ���� �ʱ�ȭ ///////////////////////////////////////////////////////////
void CDpsPCAN::ClearBuffer(void)
{
	m_csRcvdBuffer.Lock();

	m_nPosHead	= 0;
	m_nPosTail	= 0;

	m_csRcvdBuffer.Unlock();
}


///////////////////////////////////////////////////////////////////////////////
// ����� : ��Ŷ ���� /////////////////////////////////////////////////////////
BOOL CDpsPCAN::SendPacket(PCAN_PACKET_T& stPacket)
{
	TPCANStatus		stsResult;


	/////////////////////////////////////////////////////////////////
	// ������ üũ //////////////////////////////////////////////////
	if (!m_bIsDeviceConnected)			return	FALSE;
	if (stPacket.stMessage.DLC <= 0)	return	FALSE;
	if (!m_stDeviceInfo.bIsFD && stPacket.stMessage.DLC > PCAN_MAX_MSG_BYTE)	return	FALSE;
	if (m_stDeviceInfo.bIsFD && stPacket.stMessage.DLC > PCAN_MAX_MSG_BYTE_FD)	return	FALSE;


	/////////////////////////////////////////////////////////////////
	// ������ ���� //////////////////////////////////////////////////
	if (m_stDeviceInfo.bIsFD)	stsResult = PCAN_SendMessageFD(stPacket);
	else						stsResult = PCAN_SendMessage(stPacket);


	/////////////////////////////////////////////////////////////////
	// CAN ��� ����� ���� /////////////////////////////////////////
	if (stsResult == PCAN_ERROR_OK && m_pMonitorWnd) {

		PPCAN_PACKET_T	pstPacket	= new PCAN_PACKET_T;
		if (pstPacket) {

			*pstPacket = stPacket;
			m_pMonitorWnd->PostMessage(UM_DPS_DEV_PCAN_SEND_DATA, 0, (LPARAM)pstPacket);
		}
	}


	return	(stsResult == PCAN_ERROR_OK) ? TRUE : FALSE;
}


///////////////////////////////////////////////////////////////////////////////
// ����� : ��Ŷ ���� /////////////////////////////////////////////////////////
BOOL CDpsPCAN::ReadPacket(PCAN_PACKET_T& stPacket)
{
	// ũ��Ƽ�� ���� ���
	m_csRcvdBuffer.Lock();

	// ���۰� �������
	if (m_nPosTail == m_nPosHead) {
		
		m_csRcvdBuffer.Unlock();
		return	FALSE;
	}

	// ��Ŷ ���ۿ��� ���������� ����
	stPacket = m_stPacketBuffer[m_nPosTail++];
	if (m_nPosTail >= PCAN_MAX_RCVD_DATA_BUFFER)	m_nPosTail = 0;

	// ũ��Ƽ�� ���� ����
	m_csRcvdBuffer.Unlock();


	return	TRUE;
}







///////////////////////////////////////////////////////////////////////////////////////////////////
// ����̽� �Լ� //////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CAN �޼��� ���� ////////////////////////////////////////////////////////////
TPCANStatus CDpsPCAN::PCAN_SendMessage(PCAN_PACKET_T& stPacket)
{
	TPCANMsg	stCANMsg;


	/////////////////////////////////////////////////////////////////
	// �޼��� �籸�� ////////////////////////////////////////////////
	stCANMsg.ID			= stPacket.stMessage.ID;
	stCANMsg.LEN		= stPacket.stMessage.DLC;
    stCANMsg.MSGTYPE	= stPacket.stMessage.MSGTYPE;

	for (INT nIndex = 0; nIndex < PCAN_MAX_MSG_BYTE; nIndex++)
        stCANMsg.DATA[nIndex] = stPacket.stMessage.DATA[nIndex];


	return	PCAN_API_Write(m_nDeviceID, &stCANMsg);
}

TPCANStatus CDpsPCAN::PCAN_SendMessageFD(PCAN_PACKET_T& stPacket)
{
	return	PCAN_API_WriteFD(m_nDeviceID, &stPacket.stMessage);
}


///////////////////////////////////////////////////////////////////////////////
// CAN �޼��� ���� ////////////////////////////////////////////////////////////
TPCANStatus CDpsPCAN::PCAN_ReadMessage(void)
{
	TPCANMsg		stCANMsg;
    TPCANTimestamp	stCANTimeStamp;
    TPCANStatus		stsResult;


	/////////////////////////////////////////////////////////////////
	// ��Ŷ ���� ////////////////////////////////////////////////////
    stsResult = PCAN_API_Read(m_nDeviceID, &stCANMsg, &stCANTimeStamp);
    if (stsResult != PCAN_ERROR_QRCVEMPTY)
        PCAN_ProcessMessage(stCANMsg, stCANTimeStamp);

    return	stsResult;
}

TPCANStatus CDpsPCAN::PCAN_ReadMessageFD(void)
{
	TPCANMsgFD			stCANMsg;
    TPCANTimestampFD	nCANTimeStamp;
    TPCANStatus			stsResult;


	/////////////////////////////////////////////////////////////////
	// ��Ŷ ���� ////////////////////////////////////////////////////
    stsResult = PCAN_API_ReadFD(m_nDeviceID, &stCANMsg, &nCANTimeStamp);
    if (stsResult != PCAN_ERROR_QRCVEMPTY)
        PCAN_ProcessMessageFD(stCANMsg, nCANTimeStamp);

    return	stsResult;
}

void CDpsPCAN::PCAN_ReadMessages(void)
{
	TPCANStatus stsResult;


	/////////////////////////////////////////////////////////////////
	// QUEUE �� �������� ���� ///////////////////////////////////////
	do {

		stsResult = m_stDeviceInfo.bIsFD ? PCAN_ReadMessageFD() : PCAN_ReadMessage();
        if (stsResult == PCAN_ERROR_ILLOPERATION)
            break;

	} while (!(stsResult & PCAN_ERROR_QRCVEMPTY));
}


///////////////////////////////////////////////////////////////////////////////
// CAN �޼��� ���μ��� ////////////////////////////////////////////////////////
void CDpsPCAN::PCAN_ProcessMessage(TPCANMsg stCANMsg, TPCANTimestamp stCANTimeStamp)
{
	TPCANMsgFD			stCANMsgFD;
	TPCANTimestampFD	nCANTimeStamp;


	/////////////////////////////////////////////////////////////////
	// �޼��� �籸�� ////////////////////////////////////////////////
	stCANMsgFD.ID		= stCANMsg.ID;
	stCANMsgFD.DLC		= stCANMsg.LEN;
    stCANMsgFD.MSGTYPE	= stCANMsg.MSGTYPE;

	for (INT nIndex = 0; nIndex < ((stCANMsg.LEN > PCAN_MAX_MSG_BYTE) ? PCAN_MAX_MSG_BYTE : stCANMsg.LEN); nIndex++)
        stCANMsgFD.DATA[nIndex] = stCANMsg.DATA[nIndex];
    

	/////////////////////////////////////////////////////////////////
	// Ÿ�� ������ ���� /////////////////////////////////////////////
	nCANTimeStamp = stCANTimeStamp.micros + 1000 * stCANTimeStamp.millis + 0x100000000 * 1000 * stCANTimeStamp.millis_overflow;
	

	/////////////////////////////////////////////////////////////////
	// CAN �޼��� ���μ��� //////////////////////////////////////////
	PCAN_ProcessMessageFD(stCANMsgFD, nCANTimeStamp);
}

void CDpsPCAN::PCAN_ProcessMessageFD(TPCANMsgFD stCANMsg, TPCANTimestampFD nCANTimeStamp)
{
	PCAN_PACKET_T	stPacket;


	/////////////////////////////////////////////////////////////////
	// ��Ŷ ���� ////////////////////////////////////////////////////
	ZeroMemory(&stPacket, sizeof(PCAN_PACKET_T));
	stPacket.stMessage		= stCANMsg;
	stPacket.nTimeStampFD	= nCANTimeStamp;
	

	/////////////////////////////////////////////////////////////////
	// ��Ŷ ���ۿ� ���� /////////////////////////////////////////////
	m_stPacketBuffer[m_nPosHead++]	= stPacket;
	if (m_nPosHead >= PCAN_MAX_RCVD_DATA_BUFFER)	m_nPosHead = 0;

	// CAN ��� ����� ����
	if (m_pMonitorWnd) {

		PPCAN_PACKET_T	pstPacket	= new PCAN_PACKET_T;
		if (pstPacket) {

			*pstPacket = stPacket;
			m_pMonitorWnd->PostMessage(UM_DPS_DEV_PCAN_RCVD_DATA, 0, (LPARAM)pstPacket);
		}
	}
}







///////////////////////////////////////////////////////////////////////////////////////////////////
// �۾� ������ ////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ������ : ����� ////////////////////////////////////////////////////////////
UINT CDpsPCAN::ThreadFuncMonitor(LPVOID lpParam)
{
	CDpsPCAN*		pParentWnd	= (CDpsPCAN*)lpParam;
	CWnd*			pMainWnd	= pParentWnd->m_pParentWnd;
	UINT			nDeviceID	= pParentWnd->m_nDeviceID;


	/////////////////////////////////////////////////////////////////
	// ������ ���� //////////////////////////////////////////////////
	while (TRUE) {

		/////////////////////////////////////////////////////////////
		// ������ ���� üũ /////////////////////////////////////////
		pParentWnd->m_csExitThread.Lock();
		if (pParentWnd->m_bExitThread) {

			pParentWnd->m_csExitThread.Unlock();
			break;
		}

		pParentWnd->m_csExitThread.Unlock();


		/////////////////////////////////////////////////////////////
		// ������ ���� //////////////////////////////////////////////
		pParentWnd->PCAN_ReadMessages();
	}


	return	0;
}
