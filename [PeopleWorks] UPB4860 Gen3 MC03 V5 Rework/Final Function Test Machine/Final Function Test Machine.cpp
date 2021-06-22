
///////////////////////////////////////////////////////////////////////////////////////////////////
//																								 //
// Project			:	OS EV CDM Final Function Test Machine									 //
// Custommer		:	DongAh																	 //
// IDE				:	Microsoft Visual Studio 2013											 //
// Created Date		:	2018. 03. 05.															 //
// Modified Date	:	2019. 01. 26.															 //
// Programmer		:	DiMPLe(TM)																 //
//																								 //
// Final Function Test Machine.cpp																 //
//																								 //
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
// Includes ///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Final Function Test Machine.h"
#include "Final Function Test MachineDlg.h"







///////////////////////////////////////////////////////////////////////////////////////////////////
// Debug //////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
//#define new DEBUG_NEW
#endif







///////////////////////////////////////////////////////////////////////////////////////////////////
// ���α׷� ���� ���� ���� ////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma comment(linker, "/SECTION:.shr,RWS")
#pragma data_seg(".shr")
LONG	g_nProcessCount	= 0;
#pragma data_seg()







///////////////////////////////////////////////////////////////////////////////////////////////////
// CMainApp Ŭ���� ////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// �޼��� �� //////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMainApp, CWinApp)

	/////////////////////////////////////////////////////////////////
	// ������ �޼��� ////////////////////////////////////////////////
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)

END_MESSAGE_MAP()


///////////////////////////////////////////////////////////////////////////////
// Ŭ���� ���� ////////////////////////////////////////////////////////////////
CMainApp::CMainApp()
{
	/////////////////////////////////////////////////////////////////
	// ���̾�α� ///////////////////////////////////////////////////
	m_pDebugMonitorDlg		= NULL; 
	m_pMessageBoxDlg		= NULL;
	m_pSysDisplayDlg		= NULL;
	m_pSysMonitorDlg		= NULL;
	m_pSysHistoryDlg		= NULL;
	m_pDIOMonitorDlg		= NULL;
	m_pImageViewWnd			= NULL;

	ZeroMemory(m_pMCPSubPageDlg, sizeof(CMCPSubPageDlg*) * MAX_MCP_SUB_PAGE);


	/////////////////////////////////////////////////////////////////
	// ������ ///////////////////////////////////////////////////////
	m_pSysStateMonitorWnd	= NULL;
	m_pProductionWnd		= NULL;
	m_pWorkInfoWnd			= NULL;
	m_pTimerWnd				= NULL;

	m_pTactTimerWndOverView	= NULL;
	ZeroMemory(m_pTactTimerWnd, sizeof(CDpsTimerWnd*) * MAX_STATION);


	/////////////////////////////////////////////////////////////////
	// �Ϲ� /////////////////////////////////////////////////////////
	m_pDIOCtrl[DIO_CTRL_1]	= NULL;

	m_nTypeLanguage			= LANGUAGE_KOR;
	m_nTypeMachine			= MC_TYPE_1;

	ZeroMemory(&m_stSystemStatus, sizeof(SYSTEM_STATUS_T));
	ZeroMemory(m_pThread, sizeof(CWinThread*) * MAX_WORK_THREAD);


	/////////////////////////////////////////////////////////////////
	// ������ ///////////////////////////////////////////////////////
	for (UINT nStationNo = 0; nStationNo < MAX_STATION; nStationNo++) {
	
		m_strCurrentProductCode[nStationNo] = _T("");
	}

	m_pstTestProcedureData				= NULL;
	m_pstVisionProcedureData			= NULL;

	ZeroMemory(&m_stWorkStatus, sizeof(WORK_STATUS_T) * MAX_STATION);
	ZeroMemory(&m_stTestProcedureHeader, sizeof(TPRD_HEADER_T));
	ZeroMemory(&m_stVisionProcedureHeader, sizeof(VPRD_HEADER_T));


	/////////////////////////////////////////////////////////////////
	// CAN ��� ���� ////////////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_CAN_SIGNAL_LIST; nIndex++)
		m_strCAN_MsgSignalValue[nIndex] = _T("");


	/////////////////////////////////////////////////////////////////
	// ���� �˻� ////////////////////////////////////////////////////
	m_MilApplication					= M_NULL;
	m_MilSystem							= M_NULL;

	m_MilDigitizerNbBands				= 0;
	m_MilNumberOfDigitizer				= 0;
	m_MilBufferAttributes				= M_DEFAULT;

	m_pMilImageWnd						= NULL;

	for (UINT nVisionCH = 0; nVisionCH < MAX_VISION_CHANNEL; nVisionCH++) {

		m_MilDigitizer[nVisionCH]		= M_NULL;
		m_MilImageGrab[nVisionCH]		= M_NULL;
		m_pMilVideoWnd[nVisionCH]		= NULL;
	}

	for (UINT nTestItemNo = 0; nTestItemNo < MAX_TEST_SHEET; nTestItemNo++) {

		m_MilImageInspection[nTestItemNo]	= M_NULL;
	}
}


///////////////////////////////////////////////////////////////////////////////
// ������ Ŭ���� ��ü /////////////////////////////////////////////////////////
CMainApp theApp;


///////////////////////////////////////////////////////////////////////////////
// ���ø����̼� �ʱ�ȭ ////////////////////////////////////////////////////////
BOOL CMainApp::InitInstance(void)
{
	/////////////////////////////////////////////////////////////////
	// ���α׷� �ߺ� ���� ���� //////////////////////////////////////
	g_nProcessCount++;
	if (g_nProcessCount > 1) {

		if (m_nTypeLanguage == LANGUAGE_KOR)	AfxMessageBox(_T("���α׷��� �̹� �������Դϴ�."));
		else									AfxMessageBox(_T("This Program is already running..."));

		return	FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// ��ġ ����Ʈ ��Ʈ�ѷ� �ʱ�ȭ //////////////////////////////////
	AfxInitRichEdit2();


	/////////////////////////////////////////////////////////////////
	// ���ø����̼� �ʱ�ȭ //////////////////////////////////////////
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize	= sizeof(InitCtrls);
	InitCtrls.dwICC		= ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	if (!DPS_InitApplication()) {

		m_MessageBox.ErrorMessage(NULL, _T("���α׷��� �ʱ�ȭ�� �� �����ϴ�."));
		return	FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// Ŭ���� �ʱ�ȭ ////////////////////////////////////////////////
	CWinApp::InitInstance();
	CShellManager* pShellManager = new CShellManager;								// �� ������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));	// ���־� ������

	
	/////////////////////////////////////////////////////////////////
	// ������Ʈ�� ���� //////////////////////////////////////////////
	SetRegistryKey(_T("DPS Applications"));


	/////////////////////////////////////////////////////////////////
	// ���� ���̾�α� ���� /////////////////////////////////////////
	CMainDlg* pDlgMain = new CMainDlg;
	if (pDlgMain) {

		///////////////////////////////////////////////////
		// ���� ���̾�α� ������ ���� ////////////////////
		m_pMainWnd	= pDlgMain;


		///////////////////////////////////////////////////
		// �ý��� �ʱ�ȭ ���̾�α� ���� //////////////////
		CInitializeDlg	dlg(m_pMainWnd);
		dlg.DoModal();


		///////////////////////////////////////////////////
		// ���� ���̾�α� ���� ///////////////////////////
		INT_PTR nResponse = pDlgMain->DoModal();
		delete	pDlgMain;
		if (nResponse == -1) {
			
			TRACE(traceAppMsg, 0, "���: ��ȭ ���ڸ� ������ �������Ƿ� ���� ���α׷��� ����ġ �ʰ� ����˴ϴ�.\n");
			TRACE(traceAppMsg, 0, "���: ��ȭ ���ڿ��� MFC ��Ʈ���� ����ϴ� ��� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS�� ������ �� �����ϴ�.\n");
		}


		///////////////////////////////////////////////////
		// ��Ʈ�Ͻ� �̹��� ���̺귯�� ���� ////////////////
		MatroxRelease();

	} else {

		AfxMessageBox(_T("���α׷��� ������ �� �����ϴ�."));
	}

	return FALSE;
}








///////////////////////////////////////////////////////////////////////////////////////////////////
// ���α׷� ���� //////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ���ø����̼� �ʱ�ȭ ////////////////////////////////////////////////////////
BOOL CMainApp::DPS_InitApplication(void)
{
	BOOL		bResult		= TRUE;
	CString		strFileName	= _T("");
	CString		strFilePath	= _T("");
	CFileFind	fileFinder;


	/////////////////////////////////////////////////////////////////
	// ���α׷� ���� �ð� ���� //////////////////////////////////////
	::GetLocalTime(&m_stTimeAppStart);


	/////////////////////////////////////////////////////////////////
	// �ý��� ȯ�� ���� �ʱ�ȭ //////////////////////////////////////
	m_SystemConfig.InitSystemConfig();

	m_nTypeLanguage = m_SystemConfig.GetTypeLanguage();					// ��� ����
	m_nTypeMachine	= m_SystemConfig.GetTypeMachine();					// ��� ����
	m_stSystemStatus.bOnTestMode = m_SystemConfig.IsTestMode();			// �׽�Ʈ ���


	/////////////////////////////////////////////////////////////////
	// �ý��� ���� �ε� /////////////////////////////////////////////

	// ��� �� ���� �ε�
	strFileName.Format(_T("%s\\%s"), DPS_GetCurrentAppDirectory(), _TFILE_MOTION_AXIS_INFO);
	if (fileFinder.FindFile(strFileName))	LoadMotionAxisInfo(FALSE);
	else									LoadMotionAxisInfo(TRUE);
	
	fileFinder.Close();


	/////////////////////////////////////////////////////////////////
	// �� �������� ���� ///////////////////////////////////////////
	m_ModelProfile.SetModelProfilePath(m_SystemConfig.GetWorkDirectory(DIR_MODEL_PROFILE));		// �⺻ ���丮 ����
	m_ModelProfile.SetModelProfileExtension(_MPF_EXTENSION);									// Ȯ���� ����
	m_ModelProfile.SetModelProfileSize(sizeof(MODEL_PROFILE_T));								// �� �������� ũ�� ����


	/////////////////////////////////////////////////////////////////
	// ���� �������̽� ���� /////////////////////////////////////////

	// �˻� ��� ���� ����
	m_LibInterface.SetTestResultColorSet(T_RESULT_NONE, CLR_BLUE_DARKEST, CLR_YELLOW_LIGHTEST);
	m_LibInterface.SetTestResultColorSet(T_RESULT_SUCCESS, CLR_BLUE_DARKEST, CLR_GREEN_LIGHTEST);
	m_LibInterface.SetTestResultColorSet(T_RESULT_FAILURE, CLR_WHITE, CLR_RED);
	m_LibInterface.SetTestResultColorSet(T_RESULT_ERROR, CLR_WHITE, CLR_RED);


	/////////////////////////////////////////////////////////////////
	// ��� ���� �ε� ///////////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_MODULES; nIndex++)
		m_stSystemStatus.stIncludedModules[nIndex] = g_stIncludedModules[nIndex];


	/////////////////////////////////////////////////////////////////
	// �۾� ���丮 ���� ///////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_WORK_DIR; nIndex++) {

		if (g_stSystemPath[nIndex].bEnableDIR && g_stSystemPath[nIndex].bCreateDIR) 
			CreateDirectory(m_SystemConfig.GetWorkDirectory(nIndex), NULL);
	}


	/////////////////////////////////////////////////////////////////
	// ���� ī���� ���� �ε� ////////////////////////////////////////
	LoadWorkSubCounter();


	/////////////////////////////////////////////////////////////////
	// ��Ʈ�Ͻ� �̹��� ���̺귯�� �ʱ�ȭ ////////////////////////////
	bResult = MatroxInitialize();


	/////////////////////////////////////////////////////////////////
	// ������ I/O ��Ʈ�ѷ� �ʱ�ȭ ///////////////////////////////////
	for (UINT nIndex = 0; nIndex < (MAX_DIO_CTRL * MAX_DIO_CH); nIndex++)
		SetDOStatus(DO_OFF, nIndex);


	/////////////////////////////////////////////////////////////////
	// �۾� ������ ���� /////////////////////////////////////////////
	if (!StartWorkProcess()) {
		
		SErrorMessage(FALSE, _T("�۾� �����带 ������ �� �����ϴ�."));
		bResult = FALSE;
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// ���ø����̼� ���� //////////////////////////////////////////////////////////
void CMainApp::DPS_ExitApplication(void)
{
	/////////////////////////////////////////////////////////////////
	// ����-�� üũ /////////////////////////////////////////////////
	//if (m_stSystemStatus.nDeviceStatus[SD_DIO_1] == DS_NORMAL) {



	//}


	/////////////////////////////////////////////////////////////////
	// �۾� ���μ��� ���� ///////////////////////////////////////////
	StopWorkProcess();


	/////////////////////////////////////////////////////////////////
	// ����̽� ���� ////////////////////////////////////////////////

	///////////////////////////////////////////////////////
	// ������ I/O ��Ʈ�ѷ� �ʱ�ȭ /////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_DIO_CTRL; nIndex++) {

		if (m_pDIOCtrl[nIndex]) {

			m_pDIOCtrl[nIndex]->SetDOStatus(0);
			DPS_Delay_ms(100);

			m_pDIOCtrl[nIndex]->ControlStop();
			delete	m_pDIOCtrl[nIndex];
			m_pDIOCtrl[nIndex] = NULL;
		}
	}


	///////////////////////////////////////////////////////
	// ��� ��Ʈ�ѷ� ���� /////////////////////////////////
	for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++)
		AxmSignalServoOn(nAxisNo, DISABLE);

	DPS_Delay_ms(100);

	// ��� ��Ʈ�ѷ� ���� ����
	if (AxlIsOpened())	AxlClose();


	///////////////////////////////////////////////////////
	// �Ŀ� ���ö��� ���� /////////////////////////////////
	m_devPOWER.DeviceQuit();


	///////////////////////////////////////////////////////
	// CAN ������ ���� ////////////////////////////////////
	m_devCAN.DeviceClose();
	CDpsPCAN::PCAN_FreeLibrary();


	/////////////////////////////////////////////////////////////////
	// ��� ���� ////////////////////////////////////////////////////
	ConnectComm(FALSE);


	/////////////////////////////////////////////////////////////////
	// �ý��� ȯ�� ���� ���� ////////////////////////////////////////
	m_SystemConfig.SaveSystemConfig(TRUE);


	/////////////////////////////////////////////////////////////////
	// �ý��� ���� ���� /////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////
	// ������ ���� //////////////////////////////////////////////////
	if (m_pstTestProcedureData != NULL)		delete []	m_pstTestProcedureData;
	if (m_pstVisionProcedureData != NULL)	delete []	m_pstVisionProcedureData;
}


///////////////////////////////////////////////////////////////////////////////
// ��ȿ ���̼��� �˻� /////////////////////////////////////////////////////////
BOOL CMainApp::CheckValidLicense(BOOL bOnPopupMessage /* = TRUE */)
{
	UINT		nLicenseCode	= DPS_LICENSE_SUCCESS;
	CString		strMessage		= _T("");


	/////////////////////////////////////////////////////////////////
	// ���̼��� �˻� ////////////////////////////////////////////////
	nLicenseCode = DPS_CheckLicenseKey(m_stSystemStatus.stLicenseInfo);


	/////////////////////////////////////////////////////////////////
	// ��� ���� ���� ///////////////////////////////////////////////
	_stprintf_s(m_stSystemStatus.stIncludedModules[MODULE_MRE_LICENSE_KEY].szModuleVersion, MAX_STRINPUT_L, _T("%s"), m_stSystemStatus.stLicenseInfo.szLicenseInfo);


	/////////////////////////////////////////////////////////////////
	// �޼��� ��� //////////////////////////////////////////////////
	if (nLicenseCode != DPS_LICENSE_SUCCESS) {

		if (bOnPopupMessage)	m_MessageBox.Message(MB_ICONEXCLAMATION, _T("LICENSE ERROR!"), m_stSystemStatus.stLicenseInfo.szErrorMessage);
		else					ErrorMessage(TRUE, m_stSystemStatus.stLicenseInfo.szErrorMessage);
	}


	return	(nLicenseCode == DPS_LICENSE_SUCCESS) ? TRUE : FALSE;
}


///////////////////////////////////////////////////////////////////////////////
// ��� ����/���� /////////////////////////////////////////////////////////////
BOOL CMainApp::ConnectComm(BOOL bConn)
{
	BOOL			bConnectResult	= TRUE;
	BOOL			bResult			= FALSE;
	SYSTEM_CONFIG_T	stSystemConfig	= m_SystemConfig.GetSystemConfig();


	/////////////////////////////////////////////////////////////////
	// ��� ���� ////////////////////////////////////////////////////
	if (bConn) {

		///////////////////////////////////////////////////
		// ������ I/O ��Ʈ�ѷ� ���� ///////////////////////
		for (UINT nIndex = 0; nIndex < MAX_DIO_CTRL; nIndex++) {

			bResult	= FALSE;
			if (stSystemConfig.nCommPort[COMM_DIO_1 + nIndex] > 0) {

				m_Comm[COMM_DIO_1 + nIndex].SetCommPort(stSystemConfig.nCommPort[COMM_DIO_1 + nIndex], stSystemConfig.nCommBaudrate[COMM_DIO_1 + nIndex], COMM_DATABITS, COMM_STOPBITS, COMM_PARITYBITS);
				m_Comm[COMM_DIO_1 + nIndex].CreateCommInfo();
				bResult		=  m_Comm[COMM_DIO_1 + nIndex].OpenCommPort();
			}

			bConnectResult	&= bResult;
			if (bResult)	m_stSystemStatus.nDeviceStatus[SD_DIO_1 + nIndex]	= DS_CONNECT;
			else			m_stSystemStatus.nDeviceStatus[SD_DIO_1 + nIndex]	= DS_DISCONNECT;
		}


		///////////////////////////////////////////////////
		// ���ڵ� ��ĳ�� ���� /////////////////////////////
		for (UINT nIndex = 0; nIndex < MAX_BCD_SCAN; nIndex++) {

			bResult	= FALSE;
			m_stSystemStatus.nDeviceStatus[SD_SCAN_1 + nIndex] = DS_NONE;
			if (stSystemConfig.nCommPort[COMM_SCAN_1 + nIndex] > 0) {

				m_Comm[COMM_SCAN_1 + nIndex].SetCommPort(stSystemConfig.nCommPort[COMM_SCAN_1 + nIndex], stSystemConfig.nCommBaudrate[COMM_SCAN_1 + nIndex], COMM_DATABITS, COMM_STOPBITS, COMM_PARITYBITS);
				m_Comm[COMM_SCAN_1 + nIndex].CreateCommInfo();
				bResult		=  m_Comm[COMM_SCAN_1 + nIndex].OpenCommPort();

				bConnectResult	&= bResult;
				if (bResult)	m_stSystemStatus.nDeviceStatus[SD_SCAN_1 + nIndex]	= DS_CONNECT;
				else			m_stSystemStatus.nDeviceStatus[SD_SCAN_1 + nIndex]	= DS_DISCONNECT;
			}
		}


		///////////////////////////////////////////////////
		// �� ������ ���� ///////////////////////////////
		for (UINT nIndex = 0; nIndex < MAX_BARCODE_PRINTER; nIndex++) {

			bResult	= FALSE;
			m_stSystemStatus.nDeviceStatus[COMM_PRINT_1 + nIndex] = DS_NONE;
			if (stSystemConfig.nCommPort[COMM_PRINT_1 + nIndex] > 0) {

				m_Comm[COMM_PRINT_1 + nIndex].SetCommPort(stSystemConfig.nCommPort[COMM_PRINT_1 + nIndex], stSystemConfig.nCommBaudrate[COMM_PRINT_1 + nIndex], COMM_DATABITS, COMM_STOPBITS, COMM_PARITYBITS);
				m_Comm[COMM_PRINT_1 + nIndex].CreateCommInfo();
				bResult		=  m_Comm[COMM_PRINT_1 + nIndex].OpenCommPort();

				bConnectResult	&= bResult;
				if (bResult)	m_stSystemStatus.nDeviceStatus[SD_PRINT_1 + nIndex]	= DS_CONNECT;
				else			m_stSystemStatus.nDeviceStatus[SD_PRINT_1 + nIndex]	= DS_DISCONNECT;
			}
		}


		///////////////////////////////////////////////////
		// ������ ��Ƽ���� ���� ///////////////////////////
		bResult = FALSE;
		if (stSystemConfig.nCommPort[COMM_DEV_DMM] > 0) {

			m_Comm[COMM_DEV_DMM].SetCommPort(stSystemConfig.nCommPort[COMM_DEV_DMM], stSystemConfig.nCommBaudrate[COMM_DEV_DMM], COMM_DATABITS, COMM_STOPBITS, COMM_PARITYBITS);
			m_Comm[COMM_DEV_DMM].CreateCommInfo();
			bResult = m_Comm[COMM_DEV_DMM].OpenCommPort();
		}

		bConnectResult &= bResult;
		if (bResult)	m_stSystemStatus.nDeviceStatus[SD_DEV_DMM] = DS_CONNECT;
		else			m_stSystemStatus.nDeviceStatus[SD_DEV_DMM] = DS_DISCONNECT;


		///////////////////////////////////////////////////
		// �Ŀ� ���ö��� ���� /////////////////////////////
		bResult = FALSE;
		if (stSystemConfig.nCommPort[COMM_DEV_PS] > 0) {

			m_Comm[COMM_DEV_PS].SetCommPort(stSystemConfig.nCommPort[COMM_DEV_PS], stSystemConfig.nCommBaudrate[COMM_DEV_PS], COMM_DATABITS, COMM_STOPBITS, COMM_PARITYBITS);
			m_Comm[COMM_DEV_PS].CreateCommInfo();
			bResult = m_Comm[COMM_DEV_PS].OpenCommPort();
		}

		bConnectResult &= bResult;
		if (bResult)	m_stSystemStatus.nDeviceStatus[SD_DEV_PS] = DS_CONNECT;
		else			m_stSystemStatus.nDeviceStatus[SD_DEV_PS] = DS_DISCONNECT;


		///////////////////////////////////////////////////
		// ���� ī�޶� ���� ///////////////////////////////
		bResult	= FALSE;
		if (stSystemConfig.nCommPort[COMM_DEV_CAM] > 0) {

			m_Comm[COMM_DEV_CAM].SetCommPort(stSystemConfig.nCommPort[COMM_DEV_CAM], stSystemConfig.nCommBaudrate[COMM_DEV_CAM], COMM_DATABITS, COMM_STOPBITS, COMM_PARITYBITS);
			m_Comm[COMM_DEV_CAM].CreateCommInfo();
			bResult		=  m_Comm[COMM_DEV_CAM].OpenCommPort();
		}

		bConnectResult	&= bResult;
		if (bResult)	m_stSystemStatus.nDeviceStatus[SD_DEV_CAM]	= DS_CONNECT;
		else			m_stSystemStatus.nDeviceStatus[SD_DEV_CAM]	= DS_DISCONNECT;


		///////////////////////////////////////////////////
		// �ε弿 ��Ʈ�ѷ� ���� ///////////////////////////
		for (UINT nIndex = 0; nIndex < MAX_LOADCELL_CONTROLLERS; nIndex++) {

			bResult	= FALSE;
			m_stSystemStatus.nDeviceStatus[SD_DEV_LCC_1 + nIndex] = DS_NONE;
			if (stSystemConfig.nCommPort[COMM_DEV_LCC_1 + nIndex] > 0) {

				m_Comm[COMM_DEV_LCC_1 + nIndex].SetCommPort(stSystemConfig.nCommPort[COMM_DEV_LCC_1 + nIndex], stSystemConfig.nCommBaudrate[COMM_DEV_LCC_1 + nIndex], COMM_DATABITS, COMM_STOPBITS, COMM_PARITYBITS);
				m_Comm[COMM_DEV_LCC_1 + nIndex].CreateCommInfo();
				bResult		=  m_Comm[COMM_DEV_LCC_1 + nIndex].OpenCommPort();

				bConnectResult	&= bResult;
				if (bResult)	m_stSystemStatus.nDeviceStatus[SD_DEV_LCC_1 + nIndex]	= DS_CONNECT;
				else			m_stSystemStatus.nDeviceStatus[SD_DEV_LCC_1 + nIndex]	= DS_DISCONNECT;
			}
		}


		///////////////////////////////////////////////////
		// ���� ���� //////////////////////////////////////
		if (!bConnectResult) {

			ErrorMessage(FALSE, _T(""));

			if (m_nTypeLanguage == LANGUAGE_KOR) {

				for (UINT nIndex = 0; nIndex < MAX_DIO_CTRL; nIndex++) {

					if (m_stSystemStatus.nDeviceStatus[SD_DIO_1 + nIndex] == DS_DISCONNECT)		
						ErrorMessage(FALSE, _T("[COM%d] ������ I/O ��Ʈ�ѷ� #%d ��� ��Ʈ�� ����� �� �����ϴ�."), stSystemConfig.nCommPort[COMM_DIO_1 + nIndex], nIndex + 1);
				}

				for (UINT nIndex = 0; nIndex < MAX_BCD_SCAN; nIndex++) {
				
					if (m_stSystemStatus.nDeviceStatus[SD_SCAN_1 + nIndex] == DS_DISCONNECT)		
						ErrorMessage(FALSE, _T("[COM%d] ���ڵ� ��ĳ�� #%d ��� ��Ʈ�� ����� �� �����ϴ�."), stSystemConfig.nCommPort[COMM_SCAN_1 + nIndex], nIndex + 1);
				}

				for (UINT nIndex = 0; nIndex < MAX_BARCODE_PRINTER; nIndex++) {
				
					if (m_stSystemStatus.nDeviceStatus[SD_PRINT_1 + nIndex] == DS_DISCONNECT)		
						ErrorMessage(FALSE, _T("[COM%d] �� ������ #%d ��� ��Ʈ�� ����� �� �����ϴ�."), stSystemConfig.nCommPort[COMM_PRINT_1 + nIndex], nIndex + 1);
				}

				if (m_stSystemStatus.nDeviceStatus[SD_DEV_DMM] == DS_DISCONNECT)		
					ErrorMessage(FALSE, _T("[COM%d] ������ ��Ƽ���� ��� ��Ʈ�� ����� �� �����ϴ�."), stSystemConfig.nCommPort[COMM_DEV_DMM]);

				if (m_stSystemStatus.nDeviceStatus[SD_DEV_PS] == DS_DISCONNECT)		
					ErrorMessage(FALSE, _T("[COM%d] DC �Ŀ� �ҽ� ��� ��Ʈ�� ����� �� �����ϴ�."), stSystemConfig.nCommPort[COMM_DEV_PS]);

				if (m_stSystemStatus.nDeviceStatus[SD_DEV_CAM] == DS_DISCONNECT)		
					ErrorMessage(FALSE, _T("[COM%d] ���� ī�޶� ��� ��Ʈ�� ����� �� �����ϴ�."), stSystemConfig.nCommPort[COMM_DEV_CAM]);

				for (UINT nIndex = 0; nIndex < MAX_LOADCELL_CONTROLLERS; nIndex++) {
				
					if (m_stSystemStatus.nDeviceStatus[SD_DEV_LCC_1 + nIndex] == DS_DISCONNECT)		
						ErrorMessage(FALSE, _T("[COM%d] �ε弿 ��Ʈ�ѷ� #%d ��� ��Ʈ�� ����� �� �����ϴ�."), stSystemConfig.nCommPort[COMM_DEV_LCC_1 + nIndex], nIndex + 1);
				}

			} else {

				for (UINT nIndex = 0; nIndex < MAX_DIO_CTRL; nIndex++) {

					if (m_stSystemStatus.nDeviceStatus[SD_DIO_1 + nIndex] == DS_DISCONNECT)		
						ErrorMessage(FALSE, _T("[COM%d] Can not use COM Port [Digital I/O Control Unit #%d]"), stSystemConfig.nCommPort[COMM_DIO_1 + nIndex], nIndex + 1);
				}

				for (UINT nIndex = 0; nIndex < MAX_BCD_SCAN; nIndex++) {
				
					if (m_stSystemStatus.nDeviceStatus[SD_SCAN_1 + nIndex] == DS_DISCONNECT)		
						ErrorMessage(FALSE, _T("[COM%d] Can not use COM Port [Scanner #%d]"), stSystemConfig.nCommPort[COMM_SCAN_1 + nIndex], nIndex + 1);
				}
				
				for (UINT nIndex = 0; nIndex < MAX_BARCODE_PRINTER; nIndex++) {
				
					if (m_stSystemStatus.nDeviceStatus[SD_PRINT_1 + nIndex] == DS_DISCONNECT)		
						ErrorMessage(FALSE, _T("[COM%d] Can not use COM Port [Label Printer #%d]"), stSystemConfig.nCommPort[COMM_PRINT_1 + nIndex], nIndex + 1);
				}

				if (m_stSystemStatus.nDeviceStatus[SD_DEV_DMM] == DS_DISCONNECT)		
					ErrorMessage(FALSE, _T("[COM%d] Can not use COM Port [Digital Multimeter]"), stSystemConfig.nCommPort[COMM_DEV_DMM]);

				if (m_stSystemStatus.nDeviceStatus[SD_DEV_PS] == DS_DISCONNECT)		
					ErrorMessage(FALSE, _T("[COM%d] Can not use COM Port [DC Power Source]"), stSystemConfig.nCommPort[COMM_DEV_PS]);

				if (m_stSystemStatus.nDeviceStatus[SD_DEV_CAM] == DS_DISCONNECT)		
					ErrorMessage(FALSE, _T("[COM%d] Can not use COM Port [Vision CAM]"), stSystemConfig.nCommPort[COMM_DEV_CAM]);

				for (UINT nIndex = 0; nIndex < MAX_LOADCELL_CONTROLLERS; nIndex++) {
				
					if (m_stSystemStatus.nDeviceStatus[SD_DEV_LCC_1 + nIndex] == DS_DISCONNECT)		
						ErrorMessage(FALSE, _T("[COM%d] Can not use COM Port [Loadcell Controller #%d]"), stSystemConfig.nCommPort[COMM_DEV_LCC_1 + nIndex], nIndex + 1);
				}
			}
		}


	/////////////////////////////////////////////////////////////////
	// ��� ���� ���� ///////////////////////////////////////////////
	} else {

		for (UINT nIndex = 0; nIndex < MAX_COMM; nIndex++)
			m_Comm[nIndex].DestroyComm();
	}


	return	bConnectResult;
}


///////////////////////////////////////////////////////////////////////////////
// �ý��� �غ� ���� üũ //////////////////////////////////////////////////////
BOOL CMainApp::IsSystemReady(void)
{
	BOOL	bResult	= TRUE;


	/////////////////////////////////////////////////////////////////
	// �ý��� �ʱ�ȭ ��� ///////////////////////////////////////////
	bResult &= m_stSystemStatus.bResultSystemInitialize;


	/////////////////////////////////////////////////////////////////
	// ��� �ʱ�ȭ ��� /////////////////////////////////////////////
	if (m_nTypeMachine == MC_TYPE_1)	bResult &= m_stSystemStatus.bResultMachineInitialize;


	/////////////////////////////////////////////////////////////////
	// �� �������� ���� ///////////////////////////////////////////
	bResult &= m_stSystemStatus.bIsSelectedProfile;


	/////////////////////////////////////////////////////////////////
	// �ý��� ����̽� ���� /////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_SYSTEM_DEVICE; nIndex++) {

		bResult &= (m_stSystemStatus.nDeviceStatus[nIndex] != DS_DISCONNECT && m_stSystemStatus.nDeviceStatus[nIndex] != DS_ERROR && m_stSystemStatus.nDeviceStatus[nIndex] != DS_NORESPONSE) ? TRUE : FALSE;
	}


	return	m_SystemConfig.IsSimulationMode() ? TRUE : bResult;
}


///////////////////////////////////////////////////////////////////////////////
// DIO : ��� ���� ////////////////////////////////////////////////////////////
void CMainApp::SetDOStatus(UINT nSwitch, UINT nPort)
{
	if (m_pDIOCtrl[DIO_CTRL_1])		m_pDIOCtrl[DIO_CTRL_1]->SetDOStatus(nSwitch, nPort);
}

BOOL CMainApp::GetDOStatus(UINT nPort)
{
	BOOL	bStatus	= FALSE;

	if (m_pDIOCtrl[DIO_CTRL_1]) {

		bStatus = m_pDIOCtrl[DIO_CTRL_1]->GetDOStatus(nPort);
	}

	return	bStatus;
}


///////////////////////////////////////////////////////////////////////////////
// DIO : �Է� ���� ////////////////////////////////////////////////////////////
BOOL CMainApp::GetDIStatus(UINT nPort)
{
	BOOL	bStatus	= FALSE;

	if (m_pDIOCtrl[DIO_CTRL_1]) {

		bStatus = m_pDIOCtrl[DIO_CTRL_1]->GetDIStatus(nPort);
	}

	return	bStatus;
}


///////////////////////////////////////////////////////////////////////////////
// �ý��� �޼��� //////////////////////////////////////////////////////////////
BOOL CMainApp::TestMessage(BOOL bViewDate, LPCTSTR lpszFormat,...)
{
	if (m_pSysHistoryDlg) {

		LPTSTR		szMessage  = new TCHAR[MAX_BUFFER];
		CString		strMsg	   = _T("");
		va_list		vList;

		if (szMessage) {

			va_start(vList, lpszFormat);
			_vstprintf_s(szMessage, MAX_BUFFER, lpszFormat, vList);
			va_end(vList);

			// ��µ� �޼����� CR+LF �߰�
			if (bViewDate)	strMsg.Format(_T("%s\t%s\t%s\r\n"), CTime(CTime::GetCurrentTime()).Format(_T("%Y-%m-%d")), CTime(CTime::GetCurrentTime()).Format(_T("%H:%M:%S")), szMessage);
			else			strMsg.Format(_T("%s\r\n"), szMessage);

			// �˻� �̷� ���̾�α׿� �޼��� ���
			m_pSysHistoryDlg->ViewSysMessage(strMsg, CLR_SYS_MSG_PROCESS);

			// ���� ���̾�α׷� ����
			PSYSTEM_MSG_T	pstSystemMsg	= new SYSTEM_MSG_T;
			if (pstSystemMsg) {

				ZeroMemory(pstSystemMsg, sizeof(SYSTEM_MSG_T));
				_stprintf_s(pstSystemMsg->szMessage, MAX_STRVALUE, _T("%s\r\n"), szMessage);
				pstSystemMsg->crTextColor	= CLR_SYS_MSG_PROCESS;

				if (m_pMainWnd->GetSafeHwnd())	m_pMainWnd->PostMessage(UM_MAIN_SYSTEM_MESSAGE, 0, (LPARAM)pstSystemMsg);
				else							delete pstSystemMsg;
			}

			// �޸� ����
			delete []	szMessage;

			return	TRUE;
		}
	}

	return	FALSE;
}

BOOL CMainApp::TestMessageL(BOOL bViewDate, LPCTSTR lpszFormat,...)
{
	if (m_pSysHistoryDlg) {

		LPTSTR		szMessage  = new TCHAR[MAX_BUFFER];
		CString		strMsg	   = _T("");
		va_list		vList;

		if (szMessage) {

			va_start(vList, lpszFormat);
			_vstprintf_s(szMessage, MAX_BUFFER, lpszFormat, vList);
			va_end(vList);

			// ��µ� �޼���
			if (bViewDate)	strMsg.Format(_T("%s\t%s\t%s"), CTime(CTime::GetCurrentTime()).Format(_T("%Y-%m-%d")), CTime(CTime::GetCurrentTime()).Format(_T("%H:%M:%S")), szMessage);
			else			strMsg.Format(_T("%s"), szMessage);

			// �ý��� �̷� ���̾�α׿� �޼��� ���
			m_pSysHistoryDlg->ViewSysMessage(strMsg, CLR_SYS_MSG_PROCESS);
			
			// ���� ���̾�α׷� ����
			PSYSTEM_MSG_T	pstSystemMsg	= new SYSTEM_MSG_T;
			if (pstSystemMsg) {

				ZeroMemory(pstSystemMsg, sizeof(SYSTEM_MSG_T));
				_stprintf_s(pstSystemMsg->szMessage, MAX_STRVALUE, _T("%s"), szMessage);
				pstSystemMsg->crTextColor	= CLR_SYS_MSG_PROCESS;

				if (m_pMainWnd->GetSafeHwnd())	m_pMainWnd->PostMessage(UM_MAIN_SYSTEM_MESSAGE, 0, (LPARAM)pstSystemMsg);
				else							delete pstSystemMsg;
			}

			// �޸� ����
			delete []	szMessage;

			return	TRUE;
		}
	}

	return	FALSE;	
}

BOOL CMainApp::ErrorMessage(BOOL bViewDate, LPCTSTR lpszFormat,...)
{
	if (m_pSysHistoryDlg) {

		LPTSTR		szMessage  = new TCHAR[MAX_BUFFER];
		CString		strMsg	   = _T("");
		va_list		vList;

		if (szMessage) {

			va_start(vList, lpszFormat);
			_vstprintf_s(szMessage, MAX_BUFFER, lpszFormat, vList);
			va_end(vList);

			// ��µ� �޼����� CR+LF �߰�
			if (bViewDate)	strMsg.Format(_T("%s\t%s\t%s\r\n"), CTime(CTime::GetCurrentTime()).Format(_T("%Y-%m-%d")), CTime(CTime::GetCurrentTime()).Format(_T("%H:%M:%S")), szMessage);
			else			strMsg.Format(_T("%s\r\n"), szMessage);

			// �ý��� �̷� ���̾�α׿� �޼��� ���
			m_pSysHistoryDlg->ViewSysMessage(strMsg, CLR_SYS_MSG_ERROR);
			m_pSysHistoryDlg->ViewErrMessage(strMsg, CLR_SYS_MSG_ERROR);

			// ���� ���̾�α׷� ����
			PSYSTEM_MSG_T	pstSystemMsg	= new SYSTEM_MSG_T;
			if (pstSystemMsg) {

				ZeroMemory(pstSystemMsg, sizeof(SYSTEM_MSG_T));
				_stprintf_s(pstSystemMsg->szMessage, MAX_STRVALUE, _T("%s\r\n"), szMessage);
				pstSystemMsg->crTextColor	= CLR_SYS_MSG_ERROR;

				if (m_pMainWnd->GetSafeHwnd())	m_pMainWnd->PostMessage(UM_MAIN_SYSTEM_MESSAGE, 0, (LPARAM)pstSystemMsg);
				else							delete pstSystemMsg;
			}

			// �޸� ����
			delete []	szMessage;

			return	TRUE;
		}
	}

	return	FALSE;	
}

BOOL CMainApp::SErrorMessage(BOOL bViewDate, LPCTSTR lpszFormat,...)
{
	if (m_pSysHistoryDlg) {

		LPTSTR		szMessage  = new TCHAR[MAX_BUFFER];
		CString		strMsg	   = _T("");
		CString		strTemp	   = _T("");
		va_list		vList;

		if (szMessage) {

			va_start(vList, lpszFormat);
			_vstprintf_s(szMessage, MAX_BUFFER, lpszFormat, vList);
			va_end(vList);

			// ���Ӹ� �߰�
			if (m_nTypeLanguage == LANGUAGE_KOR)	strTemp.Format(_T("[�ý��� ����] %s"), szMessage);
			else									strTemp.Format(_T("[SYSTEM ERROR] %s"), szMessage);

			// ��µ� �޼����� CR+LF �߰�
			if (bViewDate)	strMsg.Format(_T("%s\t%s\t%s\r\n"), CTime(CTime::GetCurrentTime()).Format(_T("%Y-%m-%d")), CTime(CTime::GetCurrentTime()).Format(_T("%H:%M:%S")), strTemp);
			else			strMsg.Format(_T("%s\r\n"), strTemp);

			// �ý��� �̷� ���̾�α׿� �޼��� ���
			m_pSysHistoryDlg->ViewSysMessage(strMsg, CLR_SYS_MSG_ERROR);
			m_pSysHistoryDlg->ViewErrMessage(strMsg, CLR_SYS_MSG_ERROR);

			// ���� ���̾�α׷� ����
			PSYSTEM_MSG_T	pstSystemMsg	= new SYSTEM_MSG_T;
			if (pstSystemMsg) {

				ZeroMemory(pstSystemMsg, sizeof(SYSTEM_MSG_T));
				_stprintf_s(pstSystemMsg->szMessage, MAX_STRVALUE, _T("%s\r\n"), szMessage);
				pstSystemMsg->crTextColor	= CLR_SYS_MSG_ERROR;

				if (m_pMainWnd->GetSafeHwnd())	m_pMainWnd->PostMessage(UM_MAIN_SYSTEM_MESSAGE, 0, (LPARAM)pstSystemMsg);
				else							delete pstSystemMsg;
			}

			// �޸� ����
			delete []	szMessage;

			return	TRUE;
		}
	}

	return	FALSE;	
}

BOOL CMainApp::SDebugMessage(BOOL bViewDate, LPCTSTR lpszFormat,...)
{
	if (m_pSysHistoryDlg && m_SystemConfig.IsDebugMode()) {

		LPTSTR		szMessage  = new TCHAR[MAX_BUFFER];
		CString		strMsg	   = _T("");
		CString		strTemp	   = _T("");
		va_list		vList;

		if (szMessage) {

			va_start(vList, lpszFormat);
			_vstprintf_s(szMessage, MAX_BUFFER, lpszFormat, vList);
			va_end(vList);

			// ���Ӹ� �߰�
			if (m_nTypeLanguage == LANGUAGE_KOR)	strTemp.Format(_T("[�����] %s"), szMessage);
			else									strTemp.Format(_T("[DEBUG] %s"), szMessage);

			// ��µ� �޼����� CR+LF �߰�
			if (bViewDate)	strMsg.Format(_T("%s\t%s\t%s\r\n"), CTime(CTime::GetCurrentTime()).Format(_T("%Y-%m-%d")), CTime(CTime::GetCurrentTime()).Format(_T("%H:%M:%S")), strTemp);
			else			strMsg.Format(_T("%s\r\n"), strTemp);

			// �ý��� �̷� ���̾�α׿� �޼��� ���
			m_pSysHistoryDlg->ViewSysMessage(strMsg, CLR_SYS_MSG_DEBUG);

			// ���� ���̾�α׷� ����
// 			PSYSTEM_MSG_T	pstSystemMsg	= new SYSTEM_MSG_T;
// 			if (pstSystemMsg) {
// 
// 				ZeroMemory(pstSystemMsg, sizeof(SYSTEM_MSG_T));
// 				_stprintf_s(pstSystemMsg->szMessage, MAX_STRVALUE, _T("%s\r\n"), szMessage);
// 				pstSystemMsg->crTextColor	= CLR_SYS_MSG_DEBUG;
// 
// 				if (m_pMainWnd->GetSafeHwnd())	m_pMainWnd->PostMessage(UM_MAIN_SYSTEM_MESSAGE, 0, (LPARAM)pstSystemMsg);
// 				else							delete pstSystemMsg;
// 			}

			// �޸� ����
			delete []	szMessage;

			return	TRUE;
		}
	}

	return	FALSE;	
}

BOOL CMainApp::NormalMessage(BOOL bViewDate, LPCTSTR lpszFormat,...)
{
	if (m_pSysHistoryDlg) {

		LPTSTR		szMessage  = new TCHAR[MAX_BUFFER];
		CString		strMsg	   = _T("");
		va_list		vList;

		if (szMessage) {

			va_start(vList, lpszFormat);
			_vstprintf_s(szMessage, MAX_BUFFER, lpszFormat, vList);
			va_end(vList);

			// ��µ� �޼����� CR+LF �߰�
			if (bViewDate)	strMsg.Format(_T("%s\t%s\t%s\r\n"), CTime(CTime::GetCurrentTime()).Format(_T("%Y-%m-%d")), CTime(CTime::GetCurrentTime()).Format(_T("%H:%M:%S")), szMessage);
			else			strMsg.Format(_T("%s\r\n"), szMessage);

			// �ý��� �̷� ���̾�α׿� �޼��� ���
			m_pSysHistoryDlg->ViewSysMessage(strMsg, CLR_SYS_MSG_NORMAL);

			// �޸� ����
			delete []	szMessage;

			return	TRUE;
		}
	}

	return	FALSE;	
}

BOOL CMainApp::NormalMessageL(BOOL bViewDate, LPCTSTR lpszFormat,...)
{
	if (m_pSysHistoryDlg) {

		LPTSTR		szMessage  = new TCHAR[MAX_BUFFER];
		CString		strMsg	   = _T("");
		va_list		vList;

		if (szMessage) {

			va_start(vList, lpszFormat);
			_vstprintf_s(szMessage, MAX_BUFFER, lpszFormat, vList);
			va_end(vList);

			// ��µ� �޼���
			if (bViewDate)	strMsg.Format(_T("%s\t%s\t%s"), CTime(CTime::GetCurrentTime()).Format(_T("%Y-%m-%d")), CTime(CTime::GetCurrentTime()).Format(_T("%H:%M:%S")), szMessage);
			else			strMsg.Format(_T("%s"), szMessage);

			// �ý��� �̷� ���̾�α׿� �޼��� ���
			m_pSysHistoryDlg->ViewSysMessage(strMsg, CLR_SYS_MSG_NORMAL);

			// �޸� ����
			delete[]	szMessage;

			return	TRUE;
		}
	}

	return	FALSE;
}


///////////////////////////////////////////////////////////////////////////////
// ����� �޼��� //////////////////////////////////////////////////////////////
BOOL CMainApp::MessageWindow(COLORREF clrColor, LPCTSTR lpszFormat,...)
{
	if (m_pDebugMonitorDlg && m_pDebugMonitorDlg->GetSafeHwnd()) {

		LPTSTR		szMessage  = new TCHAR[MAX_BUFFER * 100];
		CString		strMsg	   = _T("");
		va_list		vList;

		if (szMessage) {

			va_start(vList, lpszFormat);
			_vstprintf_s(szMessage, MAX_BUFFER * 100, lpszFormat, vList);
			va_end(vList);

			// ��µ� �޼����� CR+LF �߰�
			//strMsg.Format(_T("%s\r\n"), strMessage);

			// �޼��� �����쿡 ���
			m_pDebugMonitorDlg->Display(clrColor, szMessage);

			// �޸� ����
			delete []	szMessage;

			return	TRUE;
		}
	}

	return	FALSE;
}







///////////////////////////////////////////////////////////////////////////////////////////////////
// �ùķ��̼� /////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////







///////////////////////////////////////////////////////////////////////////////////////////////////
// �۾� ���� //////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// �۾� ���� �ʱ�ȭ ///////////////////////////////////////////////////////////
BOOL CMainApp::InitWorkStatus(UINT nStationNo)
{
	BOOL					bResult				= FALSE;

	PWORK_STATUS_T			pstWorkStatus		= &m_stWorkStatus[nStationNo];
	PMODEL_PROFILE_T		pstModelProfile		= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
	SYSTEM_CONFIG_T			stSystemConfig		= m_SystemConfig.GetSystemConfig();


	/////////////////////////////////////////////////////////////////
	// �۾� ���� �ʱ�ȭ /////////////////////////////////////////////
	ZeroMemory(pstWorkStatus, sizeof(WORK_STATUS_T));

	// �۾� ��� �ʱ�ȭ
	pstWorkStatus->nResultFinal	= T_RESULT_SUCCESS;


	/////////////////////////////////////////////////////////////////
	// �۾� �ð� �ʱ�ȭ /////////////////////////////////////////////
	::GetLocalTime(&pstWorkStatus->stTimeWorkStart);


	/////////////////////////////////////////////////////////////////
	// ���� �˻� ������ �ʱ�ȭ //////////////////////////////////////
	m_arrFuncTestData.RemoveAll();
	m_arrContiMeasData.RemoveAll();


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// ���� �˻� �ʱ�ȭ ///////////////////////////////////////////////////////////
BOOL CMainApp::InitVisionTest(void)
{
	/////////////////////////////////////////////////////////////////
	// ���� �˻� �ʱ�ȭ /////////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_TEST_SHEET; nIndex++) {
	
		// �˻� �̹��� ���� �ʱ�ȭ
		if (m_MilImageInspection[nIndex] != M_NULL) {
		
			MbufFree(m_MilImageInspection[nIndex]);
			m_MilImageInspection[nIndex] = M_NULL;
		}

		// �˻� ������ �ʱ�ȭ
		m_arrVisionTestData[nIndex].RemoveAll();
	}


	return	TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// �۾� ��� ���丮 ���� ////////////////////////////////////////////////////
BOOL CMainApp::CreateWorkResultDirectory(UINT nStationNo, BOOL bIsMasterProduct /* = FALSE */)
{
	BOOL						bResult				= FALSE;

	CString						strDirSave			= _T("");
	CString						strDirectory		= _T("");
	CString						strFileName			= _T("");
	CString						strProductCode		= _T("");
	
	PWORK_STATUS_T				pstWorkStatus		= GetWorkStatus(nStationNo);
	DPS_PRODUCTION_V2_INFO_T	stProductionInfo	= m_pProductionWnd->GetProductionInfo();
	DPS_PRODUCTION_V2_SYSTEM_T	stProductionSystem	= m_pProductionWnd->GetProductionSystem();
	SYSTEM_CONFIG_T				stSystemConfig		= m_SystemConfig.GetSystemConfig();


	// �⺻ ���� ���丮 ����
	strDirSave = m_SystemConfig.GetWorkDirectory(DIR_SAVE_DATA);

	// �� ���丮 ����
	strDirectory.Format(_T("%s\\%s"), strDirSave, DPS_GetFileInfo(stSystemConfig.szLastModelFile).szFileName);
	CreateDirectory(strDirectory, NULL);

	// ��¥ ���丮 ����
	strDirectory.AppendFormat(_T("\\%s"), CTime(stProductionSystem.stTimeProduction).Format(_T("%Y-%m-%d")));
	CreateDirectory(strDirectory, NULL);

	// ��ǰ ���丮 ����
	strProductCode = pstWorkStatus->szProductCode;
	if (strProductCode.IsEmpty())	strProductCode = _T("NOCODE");
	if (bIsMasterProduct)	strDirectory.AppendFormat(_T("\\(M)_%s_%s"), strProductCode, CTime(pstWorkStatus->stTimeWorkStart).Format(_T("%Y%m%d%H%M%S")));
	else					strDirectory.AppendFormat(_T("\\Inspection_%s_%s"), strProductCode, CTime(pstWorkStatus->stTimeWorkStart).Format(_T("%Y%m%d%H%M%S")));

	bResult = CreateDirectory(strDirectory, NULL);

	// ���� ���丮 ����
	_tcscpy_s(pstWorkStatus->szWorkDataSaveDirectory, MAX_STRFILE, strDirectory);


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// �۾� ��Ʈ ���� (���� �˻�) /////////////////////////////////////////////////
BOOL CMainApp::SaveWorkSheet01(BOOL bIsMasterProduct /* = FALSE */)
{
	BOOL						bResult				= FALSE;
	UINT						nSTATION_NO			= STATION_1;

	CString						strDirSave			= _T("");
	CString						strDirectory		= _T("");

	CString						strFileName			= _T("");
	CString						strData				= _T("");

	PMODEL_PROFILE_T			pstModelProfile		= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
	SYSTEM_CONFIG_T				stSystemConfig		= m_SystemConfig.GetSystemConfig();
	DPS_PRODUCTION_V2_INFO_T	stProductionInfo	= m_pProductionWnd->GetProductionInfo();
	DPS_PRODUCTION_V2_SYSTEM_T	stProductionSystem	= m_pProductionWnd->GetProductionSystem();
	PWORK_STATUS_T				pstWorkStatus		= GetWorkStatus(nSTATION_NO);

	CFile						fileSaveFile;


	/////////////////////////////////////////////////////////////////
	if (pstModelProfile == NULL)	return	FALSE;


	/////////////////////////////////////////////////////////////////
	// ���丮 ���� ////////////////////////////////////////////////

	// ���� ���丮 ����
	strDirSave = m_SystemConfig.GetWorkDirectory(DIR_SAVE_DATA);

	// �� ���丮 ����
	strDirectory.Format(_T("%s\\%s"), strDirSave, DPS_GetFileInfo(m_SystemConfig.GetLastModelProfile()).szFileName);
	CreateDirectory(strDirectory, NULL);

	// ��¥ ���丮 ����
	strDirectory.AppendFormat(_T("\\%s"), CTime(stProductionSystem.stTimeProduction).Format(_T("%Y-%m-%d")));
	CreateDirectory(strDirectory, NULL);

	
	/////////////////////////////////////////////////////////////////
	// ���� �̸� ���� ///////////////////////////////////////////////
	strFileName.Format(_T("%s\\"), strDirectory);

	// ������ ��ǰ
	if (bIsMasterProduct)	strFileName.AppendFormat(_T("(M)_"));

	// ���� �̸� ����
	strFileName.AppendFormat(_T("%s_%s_%s"),	pstWorkStatus->szProductCode,
												CTime(pstWorkStatus->stTimeWorkStart).Format(_T("%Y%m%d_%H%M%S")),
												g_szTestResultEngS[pstWorkStatus->nResultFinal]);

	// ���� Ȯ���� ����
	strFileName.AppendFormat(_T(".CSV"));


	/////////////////////////////////////////////////////////////////
	// ������ ���� //////////////////////////////////////////////////
	TRY {

		if (bResult = fileSaveFile.Open(strFileName, CFile::modeCreate | CFile::modeWrite)) {

			/////////////////////////////////////////////////////////
			// �⺻ ��� ���� ///////////////////////////////////////
			strData.Empty();
			strData.AppendFormat(_T("\r\nOS EV CDM ���� ���� �˻� ��� ����"));
			strData.AppendFormat(_T("\r\n\r\n"));


			/////////////////////////////////////////////////////////
			// �� �������� ���� ///////////////////////////////////
			strData.AppendFormat(_T("\r\n[�� �������� ����]\r\n"));
			strData.AppendFormat(_T("�� ��������,%s\r\n"), DPS_GetFileInfo(m_SystemConfig.GetLastModelProfile()).szFileName);
			strData.AppendFormat(_T("�� �̸�,%s\r\n"), pstModelProfile->stModelProfileInfo.szModelInfo[MI_MODEL_NAME]);


			/////////////////////////////////////////////////////////
			// �˻� ���� ////////////////////////////////////////////
			strData.AppendFormat(_T("\r\n[�۾� ����]\r\n"));
			strData.AppendFormat(_T("LOT ����,%s\r\n"), CTime(stProductionSystem.stTimeProduction).Format(_T("%Y�� %m�� %d�� %H�� %M�� %S��")));
			strData.AppendFormat(_T("�˻� �ð�,%s\r\n"), CTime(pstWorkStatus->stTimeWorkStart).Format(_T("%Y�� %m�� %d�� %H�� %M�� %S��")));
			strData.AppendFormat(_T("�˻� ���,%s\r\n"), g_szTestResult[pstWorkStatus->nResultFinal]);
			strData.AppendFormat(_T("��ǰ �ڵ�,%s\r\n"), pstWorkStatus->szProductCode);
			strData.AppendFormat(_T("��� �ڵ�,%s\r\n"), pstWorkStatus->szOutputCode);


			/////////////////////////////////////////////////////////
			// �� �÷� �ۼ� /////////////////////////////////////////
			strData.AppendFormat(_T("\r\n��ȣ,Ŀ�ǵ�,�׸�,���,������,����,���Ѱ�,���Ѱ�,�Ķ����,���"));


			/////////////////////////////////////////////////////////
			// ���Ͽ� ���� //////////////////////////////////////////
			CStringA	strSaveData(strData);
			fileSaveFile.SeekToBegin();
			fileSaveFile.Write(strSaveData, strSaveData.GetLength());
		}


		/////////////////////////////////////////////////////////////
		// �����͸� ���� ////////////////////////////////////////////
		if (bResult) {

			INT					nDataMAX	= m_arrFuncTestData.GetCount();
			FUNC_TEST_DATA_T	stFuncTestData;

			// \n ����
			strData.Empty();
			strData.Format(_T("\r\n"));

			// �⺻ �˻� ������
			for (INT nIndex = 0; nIndex < nDataMAX; nIndex++) {

				stFuncTestData = m_arrFuncTestData.GetAt(nIndex);

				// ��ȣ
				strData.AppendFormat(_T("%d,"), nIndex + 1);

				// Ŀ�ǵ�
				strData.AppendFormat(_T("%s,"), g_stTestProcedureCommand[stFuncTestData.nCommand].szDescription[m_nTypeLanguage]);

				// �׸�
				strData.AppendFormat(_T("%s,"), stFuncTestData.szName);

				// ���
				strData.AppendFormat(_T("%s,"), g_szTestResultEng[stFuncTestData.nResult]);

				// ������
				strData.AppendFormat(_T("%s,"), stFuncTestData.szValue);

				// ����
				strData.AppendFormat(_T("%s,"), stFuncTestData.szUnit);

				// ���Ѱ�
				strData.AppendFormat(_T("%s,"), stFuncTestData.szSpecMIN);

				// ���Ѱ�
				strData.AppendFormat(_T("%s,"), stFuncTestData.szSpecMAX);

				// �Ķ����
				strData.AppendFormat(_T("%s,"), stFuncTestData.szParameters);
				strData.AppendFormat(_T("\r\n"));

				// CAN ������
				if (stFuncTestData.nCommand == TPRD_CMD_TEST_PUSH_UP || stFuncTestData.nCommand == TPRD_CMD_TEST_COMM ||
					stFuncTestData.nCommand == TPRD_CMD_TEST_PUSH_1_DN || stFuncTestData.nCommand == TPRD_CMD_TEST_PUSH_2_DN) {
				
					for (UINT nIndexCAN = 0; nIndexCAN < MAX_TPRD_DATA_VALUE; nIndexCAN++) {
					
						if (stFuncTestData.stCanValue[nIndexCAN].bUsable) {

							strData.AppendFormat(_T(",,"));
						
							if (stFuncTestData.stCanValue[nIndexCAN].nTypeMessage == CAN_MSG_TYPE_TX)	strData.AppendFormat(_T("=>,"));
							else																		strData.AppendFormat(_T("<=,"));

							strData.AppendFormat(_T("%03X,"), stFuncTestData.stCanValue[nIndexCAN].nCAN_ID);

							for (UINT nIndexDATA = 0; nIndexDATA < MPUSBCAN_MAX_CAN_BYTE; nIndexDATA++)
								strData.AppendFormat(_T("%02X "), stFuncTestData.stCanValue[nIndexCAN].abData[nIndexDATA]);

							strData.AppendFormat(_T("\r\n"));
						}
					}
				}
			}

			// ���Ͽ� ����
			CStringA	strSaveData(strData);
			fileSaveFile.SeekToEnd();
			fileSaveFile.Write(strSaveData, strSaveData.GetLength());	
		}

		// ���� ����
		fileSaveFile.Close();

	} CATCH (CFileException, e) {
		e->ReportError();
	} END_CATCH


	return	bResult;
}

BOOL CMainApp::SaveWorkSheet01T(BOOL bIsMasterProduct /* = FALSE */)
{
	BOOL						bResult				= FALSE;
	UINT						nSTATION_NO			= STATION_1;

	CString						strDirSave			= _T("");
	CString						strDirectory		= _T("");

	CString						strFileName			= _T("");
	CString						strData				= _T("");

	PMODEL_PROFILE_T			pstModelProfile		= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
	SYSTEM_CONFIG_T				stSystemConfig		= m_SystemConfig.GetSystemConfig();
	DPS_PRODUCTION_V2_INFO_T	stProductionInfo	= m_pProductionWnd->GetProductionInfo();
	DPS_PRODUCTION_V2_SYSTEM_T	stProductionSystem	= m_pProductionWnd->GetProductionSystem();
	PWORK_STATUS_T				pstWorkStatus		= GetWorkStatus(nSTATION_NO);

	CFile						fileSaveFile;
	CFileFind					fileFinder;


	/////////////////////////////////////////////////////////////////
	if (pstModelProfile == NULL)	return	FALSE;


	/////////////////////////////////////////////////////////////////
	// ���丮 ���� ////////////////////////////////////////////////

	// ���� ���丮 ����
	strDirSave = m_SystemConfig.GetWorkDirectory(DIR_SAVE_DATA);

	// �� ���丮 ����
	strDirectory.Format(_T("%s\\%s"), strDirSave, DPS_GetFileInfo(m_SystemConfig.GetLastModelProfile()).szFileName);
	CreateDirectory(strDirectory, NULL);

	// ��¥ ���丮 ����
	strDirectory.AppendFormat(_T("\\%s"), CTime(stProductionSystem.stTimeProduction).Format(_T("%Y-%m-%d")));
	CreateDirectory(strDirectory, NULL);

	
	/////////////////////////////////////////////////////////////////
	// ���� �̸� ���� ///////////////////////////////////////////////
	
	// ���� �̸� ����
	strFileName.Format(_T("%s\\InspectionReport_%s"), strDirectory, CTime(stProductionSystem.stTimeProduction).Format(_T("%H%M%S")));

	// ���� Ȯ���� ����
	strFileName.AppendFormat(_T(".CSV"));


	/////////////////////////////////////////////////////////////////
	// ������ ���� //////////////////////////////////////////////////
	TRY {

		/////////////////////////////////////////////////////////////
		// �� ���� ���� /////////////////////////////////////////////
		if (!fileFinder.FindFile(strFileName)) {

			bResult = fileSaveFile.Open(strFileName, CFile::modeCreate | CFile::modeWrite);

		/////////////////////////////////////////////////////////////
		// ���� ������ ������ �߰��� ��� ///////////////////////////
		} else {

			bResult = fileSaveFile.Open(strFileName, CFile::modeWrite | CFile::modeNoTruncate);
		}


		/////////////////////////////////////////////////////////////
		// ��� ���� ////////////////////////////////////////////////
		{
			/////////////////////////////////////////////////////////
			// �⺻ ��� ���� ///////////////////////////////////////
			strData.Empty();
			strData.AppendFormat(_T("\r\nOS EV CDM ���� ���� �˻� ��� ����"));
			strData.AppendFormat(_T("\r\n\r\n"));


			/////////////////////////////////////////////////////
			// �۾� ���� ////////////////////////////////////////
			strData.AppendFormat(_T("\r\n[�۾� ����]\r\n"));
			strData.AppendFormat(_T("LOT ����,%s\r\n"), CTime(stProductionSystem.stTimeProduction).Format(_T("%Y�� %m�� %d�� %H�� %M�� %S��")));


			/////////////////////////////////////////////////////////
			// �� �������� ���� ///////////////////////////////////
			strData.AppendFormat(_T("\r\n[�� �������� ����]\r\n"));
			strData.AppendFormat(_T("�� ��������,%s\r\n"), DPS_GetFileInfo(m_SystemConfig.GetLastModelProfile()).szFileName);
			strData.AppendFormat(_T("�� �̸�,%s\r\n"), pstModelProfile->stModelProfileInfo.szModelInfo[MI_MODEL_NAME]);
			strData.AppendFormat(_T("ǰ��,%s\r\n"), pstModelProfile->stModelProfileInfo.szModelInfo[MI_PRODUCT_NO]);


			/////////////////////////////////////////////////////////
			// �˻� ���� ////////////////////////////////////////////
			strData.AppendFormat(_T("\r\n[�˻� ����]\r\n"));
			strData.AppendFormat(_T("��ü ����,%10d\r\n"), stProductionInfo.nCountProduction);
			strData.AppendFormat(_T("��ǰ ����,%10d\r\n"), stProductionInfo.nCountProduction - stProductionInfo.nCountNG);
			strData.AppendFormat(_T("�ҷ� ����,%10d\r\n"), stProductionInfo.nCountNG);


			/////////////////////////////////////////////////////////
			// �� �÷� �ۼ� /////////////////////////////////////////
			strData.AppendFormat(_T("\r\n��ȣ,�˻� ����,�˻� �ð�,��ǰ �ڵ�,�˻� ���,��� �ڵ�,���"));


			/////////////////////////////////////////////////////////
			// ���Ͽ� ���� //////////////////////////////////////////
			CStringA	strSaveData(strData);
			fileSaveFile.SeekToBegin();
			fileSaveFile.Write(strSaveData, strSaveData.GetLength());
		}


		/////////////////////////////////////////////////////////////
		// �����͸� ���� ////////////////////////////////////////////
		if (bResult) {

			// \n ����
			strData.Empty();
			strData.Format(_T("\r\n"));

			// ��ȣ
			strData.AppendFormat(_T("%d,"), stProductionInfo.nCountProduction);

			// �˻� ����
			strData.AppendFormat(_T("%s,"), CTime(pstWorkStatus->stTimeWorkStart).Format(_T("%Y-%m-%d")));

			// �˻� �ð�
			strData.AppendFormat(_T("%s,"), CTime(pstWorkStatus->stTimeWorkStart).Format(_T("%H:%M:%S")));

			// ��ǰ �ڵ�
			strData.AppendFormat(_T("%s,"), pstWorkStatus->szProductCode);

			// �˻� ���
			strData.AppendFormat(_T("%s,"), g_szTestResultEng[pstWorkStatus->nResultFinal]);

			// ��� �ڵ�
			strData.AppendFormat(_T("%s,"), pstWorkStatus->szOutputCode);

			// ���
			strData.AppendFormat(_T("%s,"), bIsMasterProduct ? _T("������ ��ǰ") : _T(""));


			// ���Ͽ� ����
			CStringA	strSaveData(strData);
			fileSaveFile.SeekToEnd();
			fileSaveFile.Write(strSaveData, strSaveData.GetLength());	
		}

		// ���� ����
		fileSaveFile.Close();

	} CATCH (CFileException, e) {
		e->ReportError();
	} END_CATCH


	return	bResult;
}

BOOL CMainApp::SaveWorkSheetERP_01(BOOL bIsMasterProduct /* = FALSE */)
{
	BOOL						bResult				= FALSE;
	UINT						nSTATION_NO			= STATION_1;

	CString						strDirSave			= _T("");
	CString						strDirectory		= _T("");

	CString						strFileName			= _T("");
	CString						strData				= _T("");

	PMODEL_PROFILE_T			pstModelProfile		= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
	SYSTEM_CONFIG_T				stSystemConfig		= m_SystemConfig.GetSystemConfig();
	DPS_PRODUCTION_V2_INFO_T	stProductionInfo	= m_pProductionWnd->GetProductionInfo();
	DPS_PRODUCTION_V2_SYSTEM_T	stProductionSystem	= m_pProductionWnd->GetProductionSystem();
	PWORK_STATUS_T				pstWorkStatus		= GetWorkStatus(nSTATION_NO);
	CTime						timeCurrent			= CTime::GetCurrentTime();

	CFile						fileSaveFile;


	/////////////////////////////////////////////////////////////////
	if (pstModelProfile == NULL)	return	FALSE;


	/////////////////////////////////////////////////////////////////
	// ���丮 ���� ////////////////////////////////////////////////

	// ���� ���丮 ����
	strDirSave   = bIsMasterProduct ? m_SystemConfig.GetWorkDirectory(DIR_MASTER_DATA) : m_SystemConfig.GetWorkDirectory(DIR_EXPORT_DATA);
	strDirectory = strDirSave;

	// �� ���丮 ����
	strDirectory.AppendFormat(_T("\\%s"), pstModelProfile->stModelProfileInfo.szModelInfo[MI_MODEL_NAME]);
	CreateDirectory(strDirectory, NULL);

	// ��� ���丮 ����
	strDirectory.AppendFormat(_T("\\%s"), pstModelProfile->stModelProfileInfo.szModelInfo[MI_SPECIFICATION]);
	CreateDirectory(strDirectory, NULL);

	// ��¥ ���丮 ����
	if (!bIsMasterProduct)	timeCurrent = stProductionSystem.stTimeProduction;
	strDirectory.AppendFormat(_T("\\%s"), timeCurrent.Format(_T("%Y%m%d")));
	CreateDirectory(strDirectory, NULL);

	
	/////////////////////////////////////////////////////////////////
	// ���� �̸� ���� ///////////////////////////////////////////////
	strFileName.Format(_T("%s\\"), strDirectory);

	// ���� �̸� ����
	strFileName.Format(_T("%s\\%s_%10s_%s_%s_%c"),	strDirectory,
													pstWorkStatus->szProductCode,													// ��ǰ �ڵ�
													_T("XXXXXXXXXX"),																// �߿� ������ ��
													CTime(pstWorkStatus->stTimeWorkStart).Format(_T("%Y%m%d")),						// �۾� ��¥
													CTime(pstWorkStatus->stTimeWorkStart).Format(_T("%H%M%S")),						// �۾� �ð�
													pstWorkStatus->nResultFinal == T_RESULT_SUCCESS ? TEXT('O') : TEXT('X'));		// ���

	// ���� Ȯ���� ����
	strFileName.AppendFormat(_T(".TXT"));


	/////////////////////////////////////////////////////////////////
	// ������ ���� //////////////////////////////////////////////////
	TRY {

		if (bResult = fileSaveFile.Open(strFileName, CFile::modeCreate | CFile::modeWrite)) {

			/////////////////////////////////////////////////////////
			// �⺻ ��� ���� ///////////////////////////////////////
			strData.Empty();
			strData.AppendFormat(_T("***********************************************************************************\r\n"));
			strData.AppendFormat(_T("*                      OS EV CDM FINAL FUNCTION TEST REPORT                       *\r\n"));
			strData.AppendFormat(_T("***********************************************************************************\r\n"));
			strData.AppendFormat(_T("\r\n"));
			strData.AppendFormat(_T("Serial No : %s\r\n"), pstWorkStatus->szProductCode);
			strData.AppendFormat(_T("Manufacture LotNo : \r\n"));
			strData.AppendFormat(_T("PCB LotNo : \r\n"));
			strData.AppendFormat(_T("Program Version : \r\n"));
			strData.AppendFormat(_T("Model Name : %s\r\n"), pstModelProfile->stModelProfileInfo.szModelInfo[MI_MODEL_NAME]);
			strData.AppendFormat(_T("Project Name : PWM\r\n"));
			strData.AppendFormat(_T("Test Begin Time : %s\r\n"), CTime(pstWorkStatus->stTimeWorkStart).Format(_T("%Y/%m/%d %H:%M:%S")));
			strData.AppendFormat(_T("Test End Time : %s\r\n"), CTime(pstWorkStatus->stTimeWorkStart).Format(_T("%Y/%m/%d %H:%M:%S")));
			strData.AppendFormat(_T("Tester : \r\n"));
			strData.AppendFormat(_T("\r\n"));
			strData.AppendFormat(_T("Overall Result : %s\r\n"), pstWorkStatus->nResultFinal == T_RESULT_SUCCESS ? _T("PASS") : _T("FAIL"));
			strData.AppendFormat(_T("\r\n"));
			strData.AppendFormat(_T("***********************************************************************************\r\n"));


			/////////////////////////////////////////////////////////
			// �˻� ���� ////////////////////////////////////////////
			strData.AppendFormat(_T("\r\n"));
			strData.AppendFormat(_T("�˻� ���,%s\r\n"), g_szTestResult[pstWorkStatus->nResultFinal]);
			strData.AppendFormat(_T("��ǰ �ڵ�,%s\r\n"), pstWorkStatus->szProductCode);
			strData.AppendFormat(_T("��� �ڵ�,%s\r\n"), pstWorkStatus->szOutputCode);


			/////////////////////////////////////////////////////////
			// �� �÷� �ۼ� /////////////////////////////////////////
			strData.AppendFormat(_T("\r\n��ȣ,Ŀ�ǵ�,�׸�,���,������,����,���Ѱ�,���Ѱ�,�Ķ����,���"));


			/////////////////////////////////////////////////////////
			// ���Ͽ� ���� //////////////////////////////////////////
			CStringA	strSaveData(strData);
			fileSaveFile.SeekToBegin();
			fileSaveFile.Write(strSaveData, strSaveData.GetLength());
		}


		/////////////////////////////////////////////////////////////
		// �����͸� ���� ////////////////////////////////////////////
		if (bResult) {

			INT					nDataMAX	= m_arrFuncTestData.GetCount();
			FUNC_TEST_DATA_T	stFuncTestData;

			// \n ����
			strData.Empty();
			strData.Format(_T("\r\n"));

			// �⺻ �˻� ������
			for (INT nIndex = 0; nIndex < nDataMAX; nIndex++) {

				stFuncTestData = m_arrFuncTestData.GetAt(nIndex);

				// ��ȣ
				strData.AppendFormat(_T("%d,"), nIndex + 1);

				// Ŀ�ǵ�
				strData.AppendFormat(_T("%s,"), g_stTestProcedureCommand[stFuncTestData.nCommand].szDescription[m_nTypeLanguage]);

				// �׸�
				strData.AppendFormat(_T("%s,"), stFuncTestData.szName);

				// ���
				strData.AppendFormat(_T("%s,"), g_szTestResultEng[stFuncTestData.nResult]);

				// ������
				strData.AppendFormat(_T("%s,"), stFuncTestData.szValue);

				// ����
				strData.AppendFormat(_T("%s,"), stFuncTestData.szUnit);

				// ���Ѱ�
				strData.AppendFormat(_T("%s,"), stFuncTestData.szSpecMIN);

				// ���Ѱ�
				strData.AppendFormat(_T("%s,"), stFuncTestData.szSpecMAX);

				// �Ķ����
				strData.AppendFormat(_T("%s,"), stFuncTestData.szParameters);
				strData.AppendFormat(_T("\r\n"));
			}

			// ���Ͽ� ����
			CStringA	strSaveData(strData);
			fileSaveFile.SeekToEnd();
			fileSaveFile.Write(strSaveData, strSaveData.GetLength());	
		}

		// ���� ����
		fileSaveFile.Close();

	} CATCH (CFileException, e) {
		e->ReportError();
	} END_CATCH


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// ���� ��Ʈ ���� /////////////////////////////////////////////////////////////
BOOL CMainApp::SaveVisionSheet(UINT nTestItemNo, UINT nTestPointNo, VISION_TEST_DATA_T& stVisionTestData, UINT nInspectionCount)
{
	UINT						nStationNo			= STATION_1;
	UINT						nStationSubNo		= 0;

	static UINT					nItemNo				= 0;
	BOOL						bResult				= FALSE;
	
	CString						strDirSave			= _T("");
	CString						strDirectory		= _T("");
	CString						strFileName			= _T("");
	CString						strData				= _T("");
	CString						strValue			= _T("");
	
	PMODEL_PROFILE_T			pstModelProfile		= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
	PWORK_STATUS_T				pstWorkStatus		= GetWorkStatus(nStationNo);
	PMEAS_SHEET_T				pstMeasSheet		= NULL;

	PSP_WI_VISION_SETUP_T		pstStationSetup		= NULL;
	PTSI_SETUP_INFO_T			pstTestSetupInfo	= NULL;
	PVPRD_DATA_T				pstProcedureData	= NULL;

	DPS_PRODUCTION_V2_INFO_T	stProductionInfo	= m_pProductionWnd->GetProductionInfo();
	DPS_PRODUCTION_V2_SYSTEM_T	stProductionSystem	= m_pProductionWnd->GetProductionSystem();
	SYSTEM_CONFIG_T				stSystemConfig		= m_SystemConfig.GetSystemConfig();

	CTime						timeCurrent			= CTime::GetCurrentTime();

	CFile						fileSaveFile;
	CFileFind					fileFinder;


	/////////////////////////////////////////////////////////////////
	// �� ���� �ε� ///////////////////////////////////////////////
	if (pstModelProfile == NULL)										return	FALSE;
	if (m_pstVisionProcedureData == NULL)								return	FALSE;
	if (m_stVisionProcedureHeader.nNumProcedureData <= nTestPointNo)	return	FALSE;

	pstStationSetup		= &pstModelProfile->stModelProfileConfig.stSpVisionSetupInfo;
	pstTestSetupInfo	= &pstStationSetup->stTestItemSetupInfo[nTestItemNo];
	pstProcedureData	= &m_pstVisionProcedureData[nTestPointNo];


	/////////////////////////////////////////////////////////////////
	// ���丮 ���� ////////////////////////////////////////////////

	// �⺻ ���� ���丮 ����
	strDirectory = pstWorkStatus->szWorkDataSaveDirectory;


	/////////////////////////////////////////////////////////////////
	// ���� �̸� ���� ///////////////////////////////////////////////

	// ���� �̸� ����
	strFileName.Format(_T("%s\\[T%02d] Vision Inspection Result"), strDirectory, nTestItemNo + 1);

	// ���� Ȯ���� ����
	strFileName.AppendFormat(_T(".CSV"));
	MessageWindow(cDEBUG, _T("VISION SAVE FILE = %s"), strFileName);


	/////////////////////////////////////////////////////////////////
	// ������ ���� //////////////////////////////////////////////////
	TRY {

		/////////////////////////////////////////////////////////////
		// �� ���� ���� /////////////////////////////////////////////
		if (!fileFinder.FindFile(strFileName)) {

			if (bResult = fileSaveFile.Open(strFileName, CFile::modeCreate | CFile::modeWrite)) {

				/////////////////////////////////////////////////////
				// �⺻ ��� ���� ///////////////////////////////////
				strData.Empty();
				strData.AppendFormat(_T("\r\nVISION INSPECTION REPORT\r\n\r\n"));


				/////////////////////////////////////////////////////
				// �۾� ���� ////////////////////////////////////////
				strData.AppendFormat(_T("\r\n[WORK INFORMATIONS]\r\n"));
				strData.AppendFormat(_T("LOT START TIME,%s\r\n"), CTime(stProductionSystem.stTimeProduction).Format(_T("%Y-%m-%d %H:%M:%S")));
				strData.AppendFormat(_T("TEST DATE,%s\r\n"), timeCurrent.Format(_T("%Y-%m-%d")));
				strData.AppendFormat(_T("TEST TIME,%s\r\n"), timeCurrent.Format(_T("%H:%M:%S")));
				strData.AppendFormat(_T("TEST RESULT,%s\r\n"), g_szTestResultEng[pstWorkStatus->nResultFinal]);
				strData.AppendFormat(_T("TEST PROCEDURE,%s\r\n"), pstStationSetup->szVisionProcedureFile[nTestItemNo]);
				strData.AppendFormat(_T("PRODUCT CODE,%s\r\n"), pstWorkStatus->szProductCode);


				/////////////////////////////////////////////////////
				// �� �������� ���� ///////////////////////////////
				strData.AppendFormat(_T("\r\n[MODEL INFORMATIONS]\r\n"));
				strData.AppendFormat(_T("MODEL PROFILE,%s\r\n"), DPS_GetFileInfo(m_SystemConfig.GetLastModelProfile()).szFileName);
				strData.AppendFormat(_T("%s,%s\r\n"), g_stModelInfo[MI_MODEL_NAME].stName.szDescription[LANGUAGE_ENG], pstModelProfile->stModelProfileInfo.szModelInfo[MI_MODEL_NAME]);
				strData.AppendFormat(_T("%s,%s\r\n"), g_stModelInfo[MI_PRODUCT_NO].stName.szDescription[LANGUAGE_ENG], pstModelProfile->stModelProfileInfo.szModelInfo[MI_PRODUCT_NO]);
				strData.AppendFormat(_T("%s,%s\r\n"), g_stModelInfo[MI_SPECIFICATION].stName.szDescription[LANGUAGE_ENG], pstModelProfile->stModelProfileInfo.szModelInfo[MI_SPECIFICATION]);


				/////////////////////////////////////////////////////
				// �˻� ���� ////////////////////////////////////////
				strData.AppendFormat(_T("\r\n[INSPECTION INFORMATIONS]\r\n"));
				strData.AppendFormat(_T("TEST NAME,%s\r\n"), CString(pstTestSetupInfo->szUserDefName).IsEmpty() ? g_stTestSheetItem[pstTestSetupInfo->nTestSheetItem].szName[LANGUAGE_ENG] : pstTestSetupInfo->szUserDefName);
				strData.AppendFormat(_T("DELAY,%d\r\n"), pstTestSetupInfo->nValue[TSI_VALUE_COMMON_DELAY]);
				strData.AppendFormat(_T("SHUTTER SPEED,%d\r\n"), pstTestSetupInfo->nValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_CAMERA_SPEED]);
				strData.AppendFormat(_T("LIGHT VALUE,%d\r\n"), pstTestSetupInfo->nValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_LIGHT_VALUE_1]);
				strData.AppendFormat(_T("CAM POSITION (X),%.2f\r\n"), pstTestSetupInfo->dblValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_POSITION_1]);
				strData.AppendFormat(_T("CAM POSITION (Y),%.2f\r\n"), pstTestSetupInfo->dblValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_POSITION_2]);
				strData.AppendFormat(_T("CAM POSITION (Z),%.2f\r\n"), pstTestSetupInfo->dblValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_POSITION_3]);


				/////////////////////////////////////////////////////
				// �� �÷� �ۼ� /////////////////////////////////////
				strData.AppendFormat(_T("\r\nNO,NAME,RESULT,VALUE,PARAMETERS,RETRY COUNT"));


				/////////////////////////////////////////////////////
				// ���Ͽ� ���� //////////////////////////////////////
				//CStringA	strSaveData	= CW2A(strData, CP_UTF8);
				CStringA	strSaveData(strData);
				fileSaveFile.SeekToBegin();
				fileSaveFile.Write(strSaveData, strSaveData.GetLength());
			}

		/////////////////////////////////////////////////////////////
		// ���� ������ ������ �߰��� ��� ///////////////////////////
		} else {

			bResult = fileSaveFile.Open(strFileName, CFile::modeWrite | CFile::modeNoTruncate);
		}

		fileFinder.Close();


		/////////////////////////////////////////////////////////////
		// �����͸� ���� ////////////////////////////////////////////
		if (bResult) {

			// \n ����
			strData.Empty();
			strData.Format(_T("\r\n"));

			// ��ȣ
			strData.AppendFormat(_T("%lu,"), ++nItemNo);

			// �׸�
			strData.AppendFormat(_T("%s,"), pstProcedureData->szName);

			// ���
			strData.AppendFormat(_T("%s,"), g_szTestResultEng[stVisionTestData.nResult]);

			// ������
			strData.AppendFormat(_T("%.2f,"), stVisionTestData.dblValue);

			// �Ķ����
			strData.AppendFormat(_T("%s,"), stVisionTestData.szParameters);

			// ��˻� Ƚ��
			strValue.Empty();
			if (nInspectionCount)	strValue.Format(_T("%d"), nInspectionCount);
			else					strValue = _T("-");
			strData.AppendFormat(_T("%s"), strValue);
			
			// ���Ͽ� ����
			//CStringA	strSaveData	= CW2A(strData, CP_UTF8);
			CStringA	strSaveData(strData);
			fileSaveFile.SeekToEnd();
			fileSaveFile.Write(strSaveData, strSaveData.GetLength());	
		}

		// ���� ����
		if (bResult)	fileSaveFile.Close();

	} CATCH (CFileException, e) {
		e->ReportError();
	} END_CATCH


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// ����� �޼��� ���� /////////////////////////////////////////////////////////
BOOL CMainApp::SetUserMessage(UINT nUserMessageID)
{
	if (m_stSystemStatus.nCurrentUserMessage >= UMSG_WARN_MACHINE_INITIALIZING)
		return	FALSE;

	m_stSystemStatus.nPreviousUserMessage = m_stSystemStatus.nCurrentUserMessage;
	m_stSystemStatus.nCurrentUserMessage  = nUserMessageID;

	return	TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// ���� ī���� ���� ///////////////////////////////////////////////////////////
BOOL CMainApp::SaveWorkSubCounter(void)
{
	CString		strFileName		= _T("");
	BOOL		bFileResult		= TRUE;
	UINT		nRetryCount		= 0;
	CFile		fileWrite;


	TRY {

		/////////////////////////////////////////////////////////////
		// ���� �̸� ���� ///////////////////////////////////////////
		strFileName.Format(_T("%s\\%s"), DPS_GetCurrentAppDirectory(), _FILE_SUB_COUNTER_INFO);


		/////////////////////////////////////////////////////////////
		// ���� ���� ////////////////////////////////////////////////
		while (TRUE) {

			if (bFileResult = fileWrite.Open(strFileName, CFile::modeCreate | CFile::modeWrite)) {

				fileWrite.Write(&m_stWorkSubCounter, sizeof(WORK_SUB_COUNT_T));
				fileWrite.Close();
			}

			// �����̰ų� ��õ� Ƚ���� �����Ǹ�, ����
			if (bFileResult || ++nRetryCount >= MAX_RETRY_COUNT)
				break;
		}

	} CATCH (CFileException, e) {
		e->ReportError();
	} END_CATCH


	return	bFileResult;
}


///////////////////////////////////////////////////////////////////////////////
// ���� ī���� �ε� ///////////////////////////////////////////////////////////
BOOL CMainApp::LoadWorkSubCounter(void)
{
	CString		strFileName		= _T("");
	BOOL		bFileResult		= TRUE;
	UINT		nRetryCount		= 0;
	UINT		nReadCount		= 0;
	CFile		fileRead;


	TRY {

		/////////////////////////////////////////////////////////////
		// ���� �̸� ���� ///////////////////////////////////////////
		strFileName.Format(_T("%s\\%s"), DPS_GetCurrentAppDirectory(), _FILE_SUB_COUNTER_INFO);


		/////////////////////////////////////////////////////////////
		// ���� �б� ////////////////////////////////////////////////
		while (TRUE) {

			if (bFileResult = fileRead.Open(strFileName, CFile::modeRead)) {

				ZeroMemory(&m_stWorkSubCounter, sizeof(WORK_SUB_COUNT_T));
				nReadCount = fileRead.Read(&m_stWorkSubCounter, sizeof(WORK_SUB_COUNT_T));

				if (nReadCount != sizeof(WORK_SUB_COUNT_T)) {

					bFileResult = FALSE;
					break;
				}

				fileRead.Close();
			}

			// �����̰ų� ��õ� Ƚ���� �����Ǹ�, ����
			if (bFileResult || ++nRetryCount >= MAX_RETRY_COUNT)
				break;
		}

	} CATCH (CFileException, e) {
		e->ReportError();
	} END_CATCH


	return	bFileResult;
}


///////////////////////////////////////////////////////////////////////////////
// ��ǰ ���� ��¥ �ڵ� ��� ///////////////////////////////////////////////////
CString CMainApp::GetLOTDateCode(SYSTEMTIME stTime)
{
	CString		strCode = _T("");
	CString		strYear	= _T("");
	TCHAR		chCode	= 0;


	/////////////////////////////////////////////////////////////////
	// ���� /////////////////////////////////////////////////////////
	strCode.AppendChar(TEXT('C') + stTime.wYear - 2007);


	/////////////////////////////////////////////////////////////////
	// �� ///////////////////////////////////////////////////////////
	strCode.AppendChar(TEXT('A') + stTime.wMonth - 1);


	/////////////////////////////////////////////////////////////////
	// �� ///////////////////////////////////////////////////////////
	if (stTime.wDay > 26)	strCode.AppendFormat(_T("%d"), stTime.wDay - 26);
	else					strCode.AppendFormat(_T("%c"), TEXT('A') + stTime.wDay - 1);


	return	strCode;
}


///////////////////////////////////////////////////////////////////////////////
// ������ �˻� üũ ///////////////////////////////////////////////////////////
BOOL CMainApp::CheckMasterTest(void)
{
	PMODEL_PROFILE_T		pstModelProfile		= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
	PSP_WI_BASIC_SETUP_T	pstBasicSetupInfo	= NULL;

	BOOL					bResult				= TRUE;
	UINT					nNumMasterProduct	= 0;
	CTime					timeCurrent			= CTime::GetCurrentTime();


	/////////////////////////////////////////////////////////////////
	if (pstModelProfile == NULL)	return	FALSE;

	pstBasicSetupInfo = &pstModelProfile->stModelProfileConfig.stSpBasicSetupInfo;


	/////////////////////////////////////////////////////////////////
	// ������ ��ǰ ���� üũ ////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_BCD_MASTER_CODE; nIndex++) {
	
		if (!CString(pstBasicSetupInfo->szMasterCode[nIndex]).IsEmpty())
			nNumMasterProduct++;
	}


	/////////////////////////////////////////////////////////////////
	// ������ �˻� üũ /////////////////////////////////////////////
	if (nNumMasterProduct) {
	
		CString		strFileName	= _T("");
		CFileFind	fileFinder;


		for (UINT nIndex = 0; nIndex < MAX_BCD_MASTER_CODE; nIndex++) {
		
			if (!CString(pstBasicSetupInfo->szMasterCode[nIndex]).IsEmpty()) {
			
				// ���� �̸� ����
				strFileName.Empty();
				strFileName.Format(_T("%s\\%s\\%s\\%s\\*%s*.TXT"),	m_SystemConfig.GetWorkDirectory(DIR_MASTER_DATA), 
																	pstModelProfile->stModelProfileInfo.szModelInfo[MI_MODEL_NAME],
																	pstModelProfile->stModelProfileInfo.szModelInfo[MI_SPECIFICATION],
																	timeCurrent.Format(_T("%Y%m%d")),
																	pstBasicSetupInfo->szMasterCode[nIndex]);

				// ���� �˻�
				bResult &= fileFinder.FindFile(strFileName);
				fileFinder.Close();
			}
		}
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// ���ڵ� ��ĳ�� Ʈ���� ///////////////////////////////////////////////////////
void CMainApp::SetTrigBarcode(UINT nID, BOOL bOnActivate /* = TRUE */)
{
	CComm*	pComm		= GetComm(COMM_SCAN_1 + nID);
	BYTE	byReadData	= 0;

	// ���� �ʱ�ȭ
	while (pComm->ReadByte(&byReadData));

	// Ʈ���� Ŀ�ǵ� ����
	if (bOnActivate) {
	
		pComm->SendByte(0x16);	// SYN
		pComm->SendByte(0x54);	// T
		pComm->SendByte(0x0D);	// CR
		
	} else {
	
		pComm->SendByte(0x16);	// SYN
		pComm->SendByte(0x55);	// U
		pComm->SendByte(0x0D);	// CR
	}
}


///////////////////////////////////////////////////////////////////////////////
// ��ǰ �ڵ� �ߺ� üũ ////////////////////////////////////////////////////////
BOOL CMainApp::CheckProductCodeDuplicated(const CString& strProductCode, UINT nDIR_ID)
{
	BOOL		bResult			= TRUE;
	CString		strFileName		= _T("");

	CFileFind	fileFinder;


	/////////////////////////////////////////////////////////////////
	// ��� ���� ////////////////////////////////////////////////////
	if (m_SystemConfig.UseSystemOption(SOPT_DISABLE_CHECK_DUPLICIATION_CODE))
		return	bResult;


	/////////////////////////////////////////////////////////////////
	// ���� �̸� ���� ///////////////////////////////////////////////
	strFileName.Format(_T("%s\\%s.INF"), m_SystemConfig.GetWorkDirectory(nDIR_ID), strProductCode);


	/////////////////////////////////////////////////////////////////
	// ���� �˻� ////////////////////////////////////////////////////
	if (fileFinder.FindFile(strFileName))	bResult = FALSE;

	fileFinder.Close();


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// ��ǰ �ڵ� ���� ���� ////////////////////////////////////////////////////////
BOOL CMainApp::SaveProductCodeFile(PRODUCT_CODE_INFO_T& stProductCodeInfo, UINT nDIR_ID, BOOL bOnAdvanced /* = TRUE */)
{
	PMODEL_PROFILE_T			pstModelProfile				= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();

	BOOL						bResult						= TRUE;
	UINT						nTestSheetItemMAX			= 0;
	PMEAS_SHEET_T				pstMeasSheet				= NULL;

	CString						strFileName					= _T("");
	CString						strDirSave					= _T("");
	CString						strDirectory				= _T("");

	TCHAR						szSection[MAX_STRVALUE]		= { 0, };
	TCHAR						szItem[MAX_STRVALUE]		= { 0, };
	TCHAR						szKeyName[MAX_STRVALUE]		= { 0, };
	TCHAR						szValue[MAX_STRVALUE]		= { 0, };


	/////////////////////////////////////////////////////////////////
	if (CString(stProductCodeInfo.szProductCode).IsEmpty())
		return	FALSE;


	/////////////////////////////////////////////////////////////////
	// ���� �̸� ���� ///////////////////////////////////////////////
	strFileName.Format(_T("%s\\%s.INF"),	m_SystemConfig.GetWorkDirectory(nDIR_ID),
											stProductCodeInfo.szProductCode);


	/////////////////////////////////////////////////////////////////
	// ���� : ���� ���� /////////////////////////////////////////////
	_tcscpy_s(szSection, MAX_STRVALUE, _T("COMMON"));

	// ���� �ð�
	_stprintf_s(szValue, MAX_STRVALUE, _T("%s"), CTime(stProductCodeInfo.stTimeCreate).Format(_T("%Y-%m-%d,%H:%M:%S")));
	WritePrivateProfileString(szSection, _T("TIME_CREATE"), szValue, strFileName);

	// ���� �ð�
	::GetLocalTime(&stProductCodeInfo.stTimeModify);
	_stprintf_s(szValue, MAX_STRVALUE, _T("%s"), CTime(stProductCodeInfo.stTimeModify).Format(_T("%Y-%m-%d,%H:%M:%S")));
	WritePrivateProfileString(szSection, _T("TIME_MODIFY"), szValue, strFileName);

	// �𵨸�
	_stprintf_s(szKeyName, MAX_STRVALUE, _T("MODEL_NAME"));
	WritePrivateProfileString(szSection, szKeyName, stProductCodeInfo.szModelName, strFileName);

	// ��ǰ �ڵ�
	_stprintf_s(szKeyName, MAX_STRVALUE, _T("PRODUCT_CODE"));
	WritePrivateProfileString(szSection, szKeyName, stProductCodeInfo.szProductCode, strFileName);

	// �۾� ����
	_stprintf_s(szValue, MAX_STRVALUE, _T("%d"), stProductCodeInfo.bIsWorkComplete);
	WritePrivateProfileString(szSection, _T("IS_WORK_COMPLETE"), szValue, strFileName);


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// ��ǰ �ڵ� ���� �ε� ////////////////////////////////////////////////////////
BOOL CMainApp::LoadProductCodeFile(const CString& strProductCode, PRODUCT_CODE_INFO_T& stProductCodeInfo, UINT nDIR_ID)
{
	BOOL				bResult						= TRUE;
	UINT				nTestSheetItemMAX			= 0;
	PMEAS_SHEET_T		pstMeasSheet				= NULL;

	CString				strFileName					= _T("");
	CFileFind			fileFinder;

	TCHAR				szSection[MAX_STRVALUE]		= { 0, };
	TCHAR				szStringBuf[MAX_STRVALUE_L]	= { 0, };
	TCHAR				szItem[MAX_STRVALUE]		= { 0, };
	TCHAR				szKeyName[MAX_STRVALUE]		= { 0, };
	TCHAR				szDefValue[MAX_STRVALUE]	= { 0, };


	/////////////////////////////////////////////////////////////////
	// �ʱ�ȭ ///////////////////////////////////////////////////////
	ZeroMemory(&stProductCodeInfo, sizeof(PRODUCT_CODE_INFO_T));


	/////////////////////////////////////////////////////////////////
	// ���� �̸� ���� ///////////////////////////////////////////////
	strFileName.Format(_T("%s\\%s.INF"),	m_SystemConfig.GetWorkDirectory(nDIR_ID),
											strProductCode);
	
	// ���� ���� Ȯ��
	if (!fileFinder.FindFile(strFileName)) {

		fileFinder.Close();
		return	FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// ���� : ���� ���� /////////////////////////////////////////////
	_tcscpy_s(szSection, MAX_STRVALUE, _T("COMMON"));

	// ���� �ð�
	GetPrivateProfileString(szSection, _T("TIME_CREATE"), _T(""), szStringBuf, MAX_STRVALUE_L, strFileName);
	_stscanf_s(szStringBuf, _T("%d-%d-%d,%d:%d:%d"),	&stProductCodeInfo.stTimeCreate.wYear,
														&stProductCodeInfo.stTimeCreate.wMonth,
														&stProductCodeInfo.stTimeCreate.wDay,
														&stProductCodeInfo.stTimeCreate.wHour,
														&stProductCodeInfo.stTimeCreate.wMinute,
														&stProductCodeInfo.stTimeCreate.wSecond);

	// ���� �ð�
	GetPrivateProfileString(szSection, _T("TIME_MODIFY"), _T(""), szStringBuf, MAX_STRVALUE_L, strFileName);
	_stscanf_s(szStringBuf, _T("%d-%d-%d,%d:%d:%d"),	&stProductCodeInfo.stTimeModify.wYear,
														&stProductCodeInfo.stTimeModify.wMonth,
														&stProductCodeInfo.stTimeModify.wDay,
														&stProductCodeInfo.stTimeModify.wHour,
														&stProductCodeInfo.stTimeModify.wMinute,
														&stProductCodeInfo.stTimeModify.wSecond);

	// �𵨸�
	_stprintf_s(szKeyName, MAX_STRVALUE, _T("MODEL_NAME"));
	GetPrivateProfileString(szSection, szKeyName, _T(""), szStringBuf, MAX_STRVALUE_L, strFileName);
	if (_tcslen(szStringBuf) < MAX_STRINPUT_L)	_tcscpy_s(stProductCodeInfo.szModelName, MAX_STRINPUT_L, szStringBuf);
	else										bResult = FALSE;

	// ��ǰ �ڵ�
	_stprintf_s(szKeyName, MAX_STRVALUE, _T("PRODUCT_CODE"));
	GetPrivateProfileString(szSection, szKeyName, _T(""), szStringBuf, MAX_STRVALUE_L, strFileName);
	if (_tcslen(szStringBuf) < MAX_STRINPUT_S)	_tcscpy_s(stProductCodeInfo.szProductCode, MAX_STRINPUT_S, szStringBuf);
	else										bResult = FALSE;

	// �۾� ����
	_stprintf_s(szKeyName, MAX_STRVALUE, _T("IS_WORK_COMPLETE"));
	GetPrivateProfileString(szSection, szKeyName, _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
	stProductCodeInfo.bIsWorkComplete = _ttoi(szStringBuf);


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// ��ǰ �ڵ� ���� ���� ////////////////////////////////////////////////////////
BOOL CMainApp::DeleteProductCodeFile(const CString& strProductCode, UINT nDIR_ID)
{
	BOOL		bResult			= TRUE;
	CString		strFileName		= _T("");
	CFileFind	fileFinder;


	/////////////////////////////////////////////////////////////////
	// ���� �̸� ���� ///////////////////////////////////////////////
	strFileName.Format(_T("%s\\%s.INF"), m_SystemConfig.GetWorkDirectory(nDIR_ID), strProductCode);


	/////////////////////////////////////////////////////////////////
	// ���� ���� ////////////////////////////////////////////////////
	if (fileFinder.FindFile(strFileName)) {

		bResult = DeleteFile(strFileName);
		fileFinder.Close();
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// ���� ���� ���� /////////////////////////////////////////////////////////////
BOOL CMainApp::CleanInformationFile(UINT nDIR_ID)
{
	return	CleanInformationFile(m_SystemConfig.GetWorkDirectory(nDIR_ID));
}

BOOL CMainApp::CleanInformationFile(const CString& strPath)
{
	BOOL		bResult			= TRUE;
	BOOL		bIsFile			= FALSE;
	BOOL		bOnDelete		= FALSE;
	UINT		nDayLimit		= m_SystemConfig.GetProductCodeDayLimit();

	CString		strFileName		= _T("");
	CTime		timeCurrent		= CTime::GetCurrentTime();
	CTimeSpan	timeSpan;

	CFileFind	fileFinder;
	CFileStatus	fileStatus;


	/////////////////////////////////////////////////////////////////
	// ���� �˻� ////////////////////////////////////////////////////
	if (nDayLimit) {

		strFileName.Format(_T("%s\\*.*"), strPath);
		bIsFile	= fileFinder.FindFile(strFileName);

		while (bIsFile) {

			bIsFile			= fileFinder.FindNextFile();
			strFileName		= fileFinder.GetFilePath();

			if (!fileFinder.IsDots()) {
		
				bOnDelete	= TRUE;
				if (CFile::GetStatus(strFileName, fileStatus)) {

					//if (fileStatus.m_size > 0) {
				
						// ������ �������ڸ� �������� ���� ���
						timeSpan = timeCurrent - fileStatus.m_mtime;							

						// ���� �ϼ����� ������ ���� ����
						if (timeSpan.GetDays() <= nDayLimit)
							bOnDelete = FALSE;
					//}
				}

				// ���ڵ� ���� ����
				if (bOnDelete)	DeleteFile(strFileName);
			}
		}

		fileFinder.Close();
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// �� ���� ���� /////////////////////////////////////////////////////////////
BOOL CMainApp::CreateLabelFormat(UINT nBCP_NO, LABEL_PRINT_INFO_T& stLabelPrintInfo, UINT nPrintQuantity /* = 1 */, UINT nRetIndex /* = 0 */, CString* pStrRetValue /* = NULL */, UINT nCustomSerialNo /* = 0 */, PBCP_FIXED_FIELD_INFO_T pstFixedFieldData /* = NULL */)
{
	BOOL						bResult				= TRUE;
	BOOL						bIsSkipFormat		= FALSE;

	CString						strLabelData		= _T("");
	CString						strBarcode			= _T("");
	CString						strFieldData		= _T("");
	CString						strFixedData		= _T("");
	CString						strValue			= _T("");

	PBCP_USER_FORMAT_T			pstUserFormat		= stLabelPrintInfo.stUserFormat;
	SYSTEM_CONFIG_T				stSystemConfig		= m_SystemConfig.GetSystemConfig();
	DPS_PRODUCTION_V2_INFO_T	stProductionInfo	= m_pProductionWnd->GetProductionInfo();
	DPS_PRODUCTION_V2_SYSTEM_T	stProductionSystem	= m_pProductionWnd->GetProductionSystem();
	PWORK_STATUS_T				pstWorkStatus		= NULL;
	UINT						nSerialNo			= 0;

	INT							nOffsetX			= 0;
	INT							nOffsetY			= 0;
	INT							nBasisOffsetX		= 0;
	INT							nBasisOffsetY		= 0;
	INT							nLabelSizeX			= stLabelPrintInfo.sizeLabel.cx * stLabelPrintInfo.nDotPerMillimeter;
	INT							nLabelSizeY			= stLabelPrintInfo.sizeLabel.cy * stLabelPrintInfo.nDotPerMillimeter;
	TCHAR						chOrientation		= 0;


	/////////////////////////////////////////////////////////////////
	// �ø��� ��ȣ ���� /////////////////////////////////////////////
	if (nCustomSerialNo == 0)	nSerialNo = stProductionInfo.nCountProduction - stProductionInfo.nCountNG;
	else						nSerialNo = nCustomSerialNo;


	/////////////////////////////////////////////////////////////////
	// �⺻ �� ������ ���� ////////////////////////////////////////
	nBasisOffsetX = (INT)(stLabelPrintInfo.ptOffsetBasis.x * stLabelPrintInfo.nDotPerMillimeter);
	nBasisOffsetY = (INT)(stLabelPrintInfo.ptOffsetBasis.y * stLabelPrintInfo.nDotPerMillimeter);


	/////////////////////////////////////////////////////////////////
	// ��� /////////////////////////////////////////////////////////
	strLabelData.Empty();
	strLabelData.AppendFormat(_T("^XA"));
	//strLabelData.AppendFormat(_T("~TA000"));										// Tear-off Adjust Position
	strLabelData.AppendFormat(_T("~JSN"));											// Change Backfeed Sequence (N = NORMAL)
	strLabelData.AppendFormat(_T("^PON"));											// Print Orientation (N = NORMAL, I = INVERT)
	strLabelData.AppendFormat(_T("^JMA"));											// Set Dots per Milimeter
	strLabelData.AppendFormat(_T("^FWN"));								
	strLabelData.AppendFormat(_T("~SD%d"), stLabelPrintInfo.nDensity);				// Set Darkness
	strLabelData.AppendFormat(_T("^PW%d"), nLabelSizeX);							// Print Width
	strLabelData.AppendFormat(_T("^LL%d"), nLabelSizeY);							// Label Length
	strLabelData.AppendFormat(_T("^LH0,0"));										// Label Home
	strLabelData.AppendFormat(_T("^LT%d"), (INT)stLabelPrintInfo.ptOffsetLabel.y);	// Label Top
	strLabelData.AppendFormat(_T("^LS%d"), (INT)stLabelPrintInfo.ptOffsetLabel.x);	// Label Shift
	strLabelData.AppendFormat(_T("^JUS"));											// Configuration Update (S = Recall last saved settings)
	strLabelData.AppendFormat(_T("^CI0"));											// Change International Font/Encoding (0 = USA 1 Character Set)
	strLabelData.AppendFormat(_T("^XZ"));


	/////////////////////////////////////////////////////////////////
	// ����� ���� ���� ���� ////////////////////////////////////////
	strLabelData.AppendFormat(_T("^XA"));
	for (UINT nIndex = 0; nIndex < MAX_BCP_USER_FORMAT_USE; nIndex++) {
	
		if (pstUserFormat[nIndex].bUseFormat) {

			/////////////////////////////////////////////////////////
			// �⺻ ���� ���� ///////////////////////////////////////
			nOffsetX		= nBasisOffsetX + (INT)(pstUserFormat[nIndex].ptOffset.x * stLabelPrintInfo.nDotPerMillimeter);
			nOffsetY		= nBasisOffsetY + (INT)(pstUserFormat[nIndex].ptOffset.y * stLabelPrintInfo.nDotPerMillimeter);
			bIsSkipFormat	= FALSE;


			/////////////////////////////////////////////////////////
			// ��� ���� ���� ///////////////////////////////////////
			switch (pstUserFormat[nIndex].nOrientation) {
			
				case	BCP_ORI_NORMAL		:	chOrientation = TEXT('N');	break;
				case	BCP_ORI_ROTATE_90	:	chOrientation = TEXT('R');	break;
				case	BCP_ORI_ROTATE_180	:	chOrientation = TEXT('I');	break;
				case	BCP_ORI_ROTATE_270	:	chOrientation = TEXT('B');	break;
			}


			/////////////////////////////////////////////////////////
			// �ʵ� ������ ���� /////////////////////////////////////
			strFieldData = pstUserFormat[nIndex].szFieldData;

			// �ʵ� ���� #1 (LOT DATE + SERIAL NO)
			if (strFieldData.Find(g_stBCP_FixedFieldInfo[BCP_FIXED_FIELD_DATA_1].szFixedCode) >= 0) {

				strFixedData.Empty();
				if (pstFixedFieldData)	strFixedData = pstFixedFieldData[BCP_FIXED_FIELD_DATA_1].szFixedData;

				if (strFixedData.IsEmpty()) {
				
					strFixedData.Format(_T("%s"), CTime(stProductionSystem.stTimeProduction).Format(_T("%y%m%d")));
				}
			
				strValue.Empty();
				strValue.Format(_T("%s%04d"), strFixedData, nSerialNo);
				strFieldData.Replace(g_stBCP_FixedFieldInfo[BCP_FIXED_FIELD_DATA_1].szFixedCode, strValue);
			}

			// �ʵ� ���� #2 (LOT DATE)
			if (strFieldData.Find(g_stBCP_FixedFieldInfo[BCP_FIXED_FIELD_DATA_2].szFixedCode) >= 0) {

				strFixedData.Empty();
				if (pstFixedFieldData)	strFixedData = pstFixedFieldData[BCP_FIXED_FIELD_DATA_2].szFixedData;

				if (strFixedData.IsEmpty()) {
				
					strFixedData.Format(_T("%s"), CTime(stProductionSystem.stTimeProduction).Format(_T("%y%m%d")));
				}
			
				strValue.Empty();
				strValue.Format(_T("%s"), strFixedData);
				strFieldData.Replace(g_stBCP_FixedFieldInfo[BCP_FIXED_FIELD_DATA_2].szFixedCode, strValue);
			}

			// �ʵ� ���� #3 (SERIAL NO 3-DIGIT)
			if (strFieldData.Find(g_stBCP_FixedFieldInfo[BCP_FIXED_FIELD_DATA_3].szFixedCode) >= 0) {

				strFixedData.Empty();
				if (pstFixedFieldData)	strFixedData = pstFixedFieldData[BCP_FIXED_FIELD_DATA_3].szFixedData;

				if (strFixedData.IsEmpty()) {
					
					strFixedData.Format(_T("%03d"), nSerialNo);
				}
			
				strValue.Empty();
				strValue.Format(_T("%s"), strFixedData);
				strFieldData.Replace(g_stBCP_FixedFieldInfo[BCP_FIXED_FIELD_DATA_3].szFixedCode, strValue);
			}

			// �ʵ� ���� #4 (SERIAL NO 4-DIGIT)
			if (strFieldData.Find(g_stBCP_FixedFieldInfo[BCP_FIXED_FIELD_DATA_4].szFixedCode) >= 0) {

				strFixedData.Empty();
				if (pstFixedFieldData)	strFixedData = pstFixedFieldData[BCP_FIXED_FIELD_DATA_4].szFixedData;

				if (strFixedData.IsEmpty()) {
					
					strFixedData.Format(_T("%04d"), nSerialNo);
				}
			
				strValue.Empty();
				strValue.Format(_T("%s"), strFixedData);
				strFieldData.Replace(g_stBCP_FixedFieldInfo[BCP_FIXED_FIELD_DATA_4].szFixedCode, strValue);
			}

			// �ʵ� ���� #5 (��ǰ ���� ����)
			if (strFieldData.Find(g_stBCP_FixedFieldInfo[BCP_FIXED_FIELD_DATA_5].szFixedCode) >= 0) {

				strFixedData.Empty();
				if (pstFixedFieldData)	strFixedData = pstFixedFieldData[BCP_FIXED_FIELD_DATA_5].szFixedData;

				if (strFixedData.IsEmpty()) {

					if (nCustomSerialNo == 0)	nSerialNo = stProductionInfo.nCountCumulativeProduct - stProductionInfo.nCountCumulativeProductNG;
					
					strFixedData.Format(_T("%07d"), nSerialNo);
				}
			
				strValue.Empty();
				strValue.Format(_T("%s"), strFixedData);
				strFieldData.Replace(g_stBCP_FixedFieldInfo[BCP_FIXED_FIELD_DATA_5].szFixedCode, strValue);
			}

			// ���ϰ� ����
			if (pStrRetValue != NULL && nRetIndex == nIndex)
				*pStrRetValue = strFieldData;


			/////////////////////////////////////////////////////////
			// ���� ���� �� ���� ////////////////////////////////////
			if (!bIsSkipFormat) {

				switch (pstUserFormat[nIndex].nTypeFormat) {
			
					/////////////////////////////////////////////////
					// �׷��� ///////////////////////////////////////
					case	BCP_UFI_TYPE_G	:
							{
								BCP_GRAPHIC_T	stObjectInfo = GetPrintGraphics(pstUserFormat[nIndex].nGraphicID);

								strLabelData.AppendFormat(_T("^FS^FT%d,%d"), (nOffsetX < 0 ? 0 : nOffsetX), (nOffsetY < 0 ? 0 : nOffsetY));
								strLabelData.AppendFormat(_T("^XG%s,%d,%d"),	DPS_GetFileInfo(stObjectInfo.szFontName).szFileName,
																				pstUserFormat[nIndex].stMagnifyFactor.x,
																				pstUserFormat[nIndex].stMagnifyFactor.y);
							}

							break;

					/////////////////////////////////////////////////
					// �̹��� ///////////////////////////////////////
					case	BCP_UFI_TYPE_I	:
							{
								BCP_IMAGE_T		stObjectInfo = GetPrintImages(pstUserFormat[nIndex].nImageID);

								strLabelData.AppendFormat(_T("^FS^FO%d,%d"), (nOffsetX < 0 ? 0 : nOffsetX), (nOffsetY < 0 ? 0 : nOffsetY));
								strLabelData.AppendFormat(_T("^IM%s.BMP^FS"), DPS_GetFileInfo(stObjectInfo.szFontName).szFileName);
								strLabelData.AppendFormat(_T("^IL%s.BMP"), DPS_GetFileInfo(stObjectInfo.szFontName).szFileName);
							}

							break;

					/////////////////////////////////////////////////
					// ���ڵ� ///////////////////////////////////////
					case	BCP_UFI_TYPE_B	:
							{
								CString		strOptionFD	= _T("");

								strValue.Empty();
								switch (pstUserFormat[nIndex].nTypeBarcode) {
							
									case	BCP_BCD_CODE128		:
											{
												strValue.AppendFormat(_T("^BC%c,%d,N,N,N,D"), chOrientation, (INT)(pstUserFormat[nIndex].dblBarcodeHeight * stLabelPrintInfo.nDotPerMillimeter));
												strValue.AppendFormat(_T("^BY%d"), pstUserFormat[nIndex].nBarcodeWidth);
											}

											break;

									case	BCP_BCD_QR_CODE		:
											{
												strValue.AppendFormat(_T("^BQ%c,2,%d"), chOrientation, pstUserFormat[nIndex].nBarcodeWidth);
												strOptionFD = _T("QA,");
											}

											break;

									case	BCP_BCD_DATA_MATRIX	:
											{
												strValue.AppendFormat(_T("^BX%c,%d,%d"), chOrientation, (UINT)pstUserFormat[nIndex].dblBarcodeHeight, pstUserFormat[nIndex].nBarcodeWidth);
											}

											break;
								}

								strLabelData.AppendFormat(_T("^FS^FO%d,%d"), (nOffsetX < 0 ? 0 : nOffsetX), (nOffsetY < 0 ? 0 : nOffsetY));
								strLabelData.AppendFormat(_T("%s"), strValue);
								strLabelData.AppendFormat(_T("^FD%s%s"), strOptionFD, strFieldData);
							}

							break;

					/////////////////////////////////////////////////
					// �ؽ�Ʈ ///////////////////////////////////////
					case	BCP_UFI_TYPE_T	:
							{
								strLabelData.AppendFormat(_T("^FS^FO%d,%d"), (nOffsetX < 0 ? 0 : nOffsetX), (nOffsetY < 0 ? 0 : nOffsetY));
								strLabelData.AppendFormat(_T("^A%c%c,%d,%d"), pstUserFormat[nIndex].chFontName, chOrientation, pstUserFormat[nIndex].stFontSize.x, pstUserFormat[nIndex].stFontSize.y);
								strLabelData.AppendFormat(_T("^FD%s"), strFieldData);
							}

							break;

					/////////////////////////////////////////////////
					// �ڵ� /////////////////////////////////////////
					case	BCP_UFI_TYPE_C	:
							{
								CString		strUserCode	= pstUserFormat[nIndex].szUserCode;

								strUserCode.Remove(TEXT('\r'));
								strUserCode.Remove(TEXT('\n'));
								strLabelData.AppendFormat(_T("%s"), strUserCode);
							}

							break;
				}
			}
		}
	}


	/////////////////////////////////////////////////////////////////
	// ���� /////////////////////////////////////////////////////////
	strLabelData.AppendFormat(_T("^FS"));
	strLabelData.AppendFormat(_T("^PQ%d"), nPrintQuantity);
	strLabelData.AppendFormat(_T("^FS"));
	strLabelData.AppendFormat(_T("^XZ"));


	/////////////////////////////////////////////////////////////////
	// �� ���� ���� ///////////////////////////////////////////////
	m_strLabelFormat[nBCP_NO].Empty();
	m_strLabelFormat[nBCP_NO] = strLabelData;


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// �� ������ �׷��� �ε� ////////////////////////////////////////////////////
UINT CMainApp::LoadZebraGraphics(void)
{
	BOOL				bIsFile			= FALSE;
	UINT				nNumGraphics	= 0;
	UINT				nFileSize		= 0;
	CString				strFileName		= _T("");
	CString				strFilePath		= _T("");

	BCP_GRAPHIC_T		stGraphicInfo;
	CFileStatus			fileStatus;
	CFileFind			fileFinder;


	/////////////////////////////////////////////////////////////////
	// �ʱ�ȭ ///////////////////////////////////////////////////////
	m_arrBCPGraphicList.RemoveAll();


	/////////////////////////////////////////////////////////////////
	// Zebra �׷��� ���� �˻� ///////////////////////////////////////
	strFileName.Format(_T("%s\\*.%s"), m_SystemConfig.GetWorkDirectory(DIR_BCP_OBJECTS), BCP_GRF_EXTENSION);
	bIsFile	= fileFinder.FindFile(strFileName);
	if (!bIsFile)	return	nNumGraphics;

	while (bIsFile) {

		bIsFile			= fileFinder.FindNextFile();
		strFileName		= fileFinder.GetFileName();
		strFilePath		= fileFinder.GetFilePath();
		
		// ���� ���� �ε�
		CFile::GetStatus(strFilePath, fileStatus);
		if (fileStatus.m_size > 0) {
		
			ZeroMemory(&stGraphicInfo, sizeof(BCP_GRAPHIC_T));
			_tcscpy_s(stGraphicInfo.szFontName, MAX_STRINPUT_S, strFileName);
			m_arrBCPGraphicList.Add(stGraphicInfo);
			nNumGraphics++;

			NormalMessage(FALSE, _T("Loading Printer Graphics = %s"), stGraphicInfo.szFontName);
		}
	}

	// ���� ���δ� �ݱ�
	fileFinder.Close();


	/////////////////////////////////////////////////////////////////
	// �׷��� ��Ʈ ���� ���� ////////////////////////////////////////
	m_stSystemStatus.nPrintNumGraphics = nNumGraphics;


	return	nNumGraphics;
}

BOOL CMainApp::TransmitZebraGraphics(UINT nBCP_NO)
{
	BOOL		bResult			= FALSE;
	CString		strFileName		= _T("");
	CString		strBuffer		= _T("");
	CString		strRead			= _T("");

	CStdioFile	filePrinter;


	for (UINT nIndex = 0; nIndex < m_stSystemStatus.nPrintNumGraphics; nIndex++) {
										
		// �׷��� ���� �̸� ����
		strFileName.Empty();
		strFileName.Format(_T("%s\\%s"), m_SystemConfig.GetWorkDirectory(DIR_BCP_OBJECTS), GetPrintGraphics(nIndex).szFontName);

		// ���� ����
		if (bResult = filePrinter.Open(strFileName, CFile::modeRead)) {

			// ���� �ε�
			strBuffer.Empty();
			while (filePrinter.ReadString(strRead))
				strBuffer += strRead;

			filePrinter.Close();

			// ������ ������ ����
			m_Comm[COMM_PRINT_1 + nBCP_NO].TransmitString(FALSE, strBuffer);
			DPS_Delay_ms(BCP_DELAY_SETUP);
		
		} else break;
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// �� ������ �̹��� �ε� ////////////////////////////////////////////////////
UINT CMainApp::LoadZebraImages(void)
{
	BOOL				bIsFile			= FALSE;
	UINT				nNumImages		= 0;
	UINT				nFileSize		= 0;
	CString				strFileName		= _T("");
	CString				strFilePath		= _T("");

	BCP_IMAGE_T			stImageInfo;
	CFileStatus			fileStatus;
	CFileFind			fileFinder;


	/////////////////////////////////////////////////////////////////
	// �ʱ�ȭ ///////////////////////////////////////////////////////
	m_arrBCPImageList.RemoveAll();


	/////////////////////////////////////////////////////////////////
	// Zebra �̹��� ���� �˻� ///////////////////////////////////////
	strFileName.Format(_T("%s\\*.%s"), m_SystemConfig.GetWorkDirectory(DIR_BCP_OBJECTS), BCP_IMG_EXTENSION);
	bIsFile	= fileFinder.FindFile(strFileName);
	if (!bIsFile)	return	nNumImages;

	while (bIsFile) {

		bIsFile			= fileFinder.FindNextFile();
		strFileName		= fileFinder.GetFileName();
		strFilePath		= fileFinder.GetFilePath();
		
		// ���� ���� �ε�
		CFile::GetStatus(strFilePath, fileStatus);
		if (fileStatus.m_size > 0) {
		
			ZeroMemory(&stImageInfo, sizeof(BCP_IMAGE_T));
			_tcscpy_s(stImageInfo.szFontName, MAX_STRINPUT_S, strFileName);
			m_arrBCPImageList.Add(stImageInfo);
			nNumImages++;

			NormalMessage(FALSE, _T("Loading Printer Images = %s"), stImageInfo.szFontName);
		}
	}

	// ���� ���δ� �ݱ�
	fileFinder.Close();


	/////////////////////////////////////////////////////////////////
	// �׷��� ��Ʈ ���� ���� ////////////////////////////////////////
	m_stSystemStatus.nPrintNumImages = nNumImages;


	return	nNumImages;
}

BOOL CMainApp::TransmitZebraImages(UINT nBCP_NO)
{
	BOOL		bResult			= FALSE;
	PBYTE		pBuffer			= NULL;
	CString		strFileName		= _T("");
	CString		strPacket		= _T("");

	CFile		filePrinter;
	CFileStatus	fileStatus;


	/////////////////////////////////////////////////////////////////
	// ���� ���� ////////////////////////////////////////////////////
	pBuffer = new (std::nothrow) BYTE[MAX_BCP_IMAGE_BUFFER];
	if (pBuffer == NULL)	return	bResult;


	/////////////////////////////////////////////////////////////////
	// �̹��� �ε� //////////////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < m_stSystemStatus.nPrintNumImages; nIndex++) {
										
		// �׷��� ���� �̸� ����
		strFileName.Empty();
		strFileName.Format(_T("%s\\%s"), m_SystemConfig.GetWorkDirectory(DIR_BCP_OBJECTS), GetPrintImages(nIndex).szFontName);

		// ���� ����
		if (bResult = filePrinter.Open(strFileName, CFile::modeRead)) {

			// ���� �ε�
			ZeroMemory(pBuffer, MAX_BCP_IMAGE_BUFFER);
			CFile::GetStatus(strFileName, fileStatus);
			filePrinter.Read(pBuffer, MAX_BCP_IMAGE_BUFFER);
			filePrinter.Close();

			// ������ ������ ����
			strPacket.AppendFormat(_T("~DY%s,"), GetPrintImages(nIndex).szFontName);
			strPacket.AppendFormat(_T("B,B,%d,,"), fileStatus.m_size);
			m_Comm[COMM_PRINT_1 + nBCP_NO].TransmitString(FALSE, strPacket);
			m_Comm[COMM_PRINT_1 + nBCP_NO].WriteCommBlock(pBuffer, (DWORD)fileStatus.m_size);
			DPS_Delay_ms(BCP_DELAY_SETUP);

		} else break;
	}


	return	bResult;
}







///////////////////////////////////////////////////////////////////////////////////////////////////
// �۾� ���ν��� //////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// �˻� ���ν��� �ε� /////////////////////////////////////////////////////////
BOOL CMainApp::LoadTestProcedure(void)
{
	PMODEL_PROFILE_T	pstModelProfile	= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
	BOOL				bResult			= FALSE;


	/////////////////////////////////////////////////////////////////
	// ���ν��� ������ ���� /////////////////////////////////////////
	if (m_pstTestProcedureData != NULL)	{
		
		delete [] m_pstTestProcedureData;
		m_pstTestProcedureData = NULL;
	}


	/////////////////////////////////////////////////////////////////
	// ���ν��� �ε� ////////////////////////////////////////////////
	bResult = LoadTestProcedure(pstModelProfile->stModelProfileConfig.stSpBasicSetupInfo.szTestProcedureFile,
								m_stTestProcedureHeader, &m_pstTestProcedureData);


	return	bResult;
}

BOOL CMainApp::LoadTestProcedure(const CString& strProcedureFile, TPRD_HEADER_T& stHeader, PTPRD_DATA_T* pstData /* = NULL */)
{
	BOOL			bResult		= FALSE;
	UINT			nOffset		= 0;
	UINT			nReadCount	= 0;

	CDpsFileRecord	fileRecord;
	CFileFind		fileFinder;


	/////////////////////////////////////////////////////////////////
	// üũ /////////////////////////////////////////////////////////
	if (strProcedureFile.IsEmpty() || !fileFinder.FindFile(strProcedureFile))	
		return	FALSE;


	/////////////////////////////////////////////////////////////////
	// ���ν��� ���� �ε� ///////////////////////////////////////////
	fileRecord.SetFileName(strProcedureFile);
	
	// ��� �ε�
	if (bResult = fileRecord.ReadHeader(&stHeader, sizeof(TPRD_HEADER_T))) {

		nReadCount = stHeader.nNumProcedureData;

		// ���ν��� ������ ����
		if (pstData != NULL) {

			(*pstData) = new (std::nothrow) TPRD_DATA_T[nReadCount];
			if ((*pstData) != NULL) {
		
				// ������ �ε� (10���� �ε�)
				while (nReadCount || !bResult) {
		
					if (nReadCount > 10) {
				
						bResult		= fileRecord.ReadRecordBlock((PBYTE)(*pstData) + nOffset, sizeof(TPRD_DATA_T) * 10, sizeof(TPRD_HEADER_T) + nOffset);
						nReadCount -= 10;

					} else {
				
						bResult		= fileRecord.ReadRecordBlock((PBYTE)(*pstData) + nOffset, sizeof(TPRD_DATA_T) * nReadCount, sizeof(TPRD_HEADER_T) + nOffset);
						nReadCount	= 0;
					}

					if  (!bResult)		break;

					nOffset += (sizeof(TPRD_DATA_T) * 10);
				}
		
			} else {
		
				bResult = FALSE;
			}
		}
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// �˻� ���ν��� ���� /////////////////////////////////////////////////////////
BOOL CMainApp::SaveTestProcedure(const CString& strProcedureFile, TPRD_HEADER_T& stHeader, PTPRD_DATA_T pstData /* = NULL */)
{
	BOOL			bResult		= FALSE;
	INT				nRetCode	= 0;
	UINT			nOffset		= 0;
	UINT			nWriteCount	= 0;
	CDpsFileRecord	fileRecord;


	/////////////////////////////////////////////////////////////////
	// ���� �ڵ� ���� ///////////////////////////////////////////////
	_tcscpy_s(stHeader.szUniqueCode, MAX_STRINPUT_L, _TPRD_UNIQUE_CODE);


	/////////////////////////////////////////////////////////////////
	// ���ν��� ���� ���� ///////////////////////////////////////////
	fileRecord.SetFileName(strProcedureFile);

	do {

		// ��� ����
		if (bResult = fileRecord.WriteHeader(&stHeader, sizeof(TPRD_HEADER_T))) {
		
			if (pstData != NULL) {

				// ������ ���� (10���� ����)
				nOffset		= 0;
				nWriteCount	= stHeader.nNumProcedureData;
				while (nWriteCount || !bResult) {
			
					if (nWriteCount > 10) {
					
						bResult		 = fileRecord.WriteRecordBlock((PBYTE)pstData + nOffset, sizeof(TPRD_DATA_T) * 10, sizeof(TPRD_HEADER_T) + nOffset);
						nWriteCount -= 10;	

					} else {
					
						bResult		 = fileRecord.WriteRecordBlock((PBYTE)pstData + nOffset, sizeof(TPRD_DATA_T) * nWriteCount, sizeof(TPRD_HEADER_T) + nOffset);
						nWriteCount	 = 0;
					}

					nOffset += (sizeof(TPRD_DATA_T) * 10);
				}
			}
		}

		if (!bResult) {

			nRetCode = m_MessageBox.Message(MB_RETRYCANCEL | MB_ICONERROR, _T("���� ���� ����!"), _T("���ν��� ���� ���� �� ������ �߻��߽��ϴ�."));
		}

	} while (!bResult && nRetCode == IDRETRY);


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// ���� ���ν��� �ε� /////////////////////////////////////////////////////////
BOOL CMainApp::LoadVisionProcedure(UINT nTestItemNo)
{
	PMODEL_PROFILE_T	pstModelProfile	= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
	BOOL				bResult			= FALSE;


	/////////////////////////////////////////////////////////////////
	// ���ν��� ������ ���� /////////////////////////////////////////
	if (m_pstVisionProcedureData != NULL)	{
		
		delete [] m_pstVisionProcedureData;
		m_pstVisionProcedureData = NULL;
	}


	/////////////////////////////////////////////////////////////////
	// ���ν��� �ε� ////////////////////////////////////////////////
	bResult = LoadVisionProcedure(	pstModelProfile->stModelProfileConfig.stSpVisionSetupInfo.szVisionProcedureFile[nTestItemNo],
									m_stVisionProcedureHeader, &m_pstVisionProcedureData);


	return	bResult;
}

BOOL CMainApp::LoadVisionProcedure(const CString& strProcedureFile, VPRD_HEADER_T& stHeader, PVPRD_DATA_T* pstData /* = NULL */)
{
	BOOL			bResult		= FALSE;
	UINT			nOffset		= 0;
	UINT			nReadCount	= 0;

	CDpsFileRecord	fileRecord;
	CFileFind		fileFinder;


	/////////////////////////////////////////////////////////////////
	// üũ /////////////////////////////////////////////////////////
	if (strProcedureFile.IsEmpty() || !fileFinder.FindFile(strProcedureFile))	
		return	FALSE;


	/////////////////////////////////////////////////////////////////
	// ���ν��� ���� �ε� ///////////////////////////////////////////
	fileRecord.SetFileName(strProcedureFile);
	
	// ��� �ε�
	if (bResult = fileRecord.ReadHeader(&stHeader, sizeof(VPRD_HEADER_T))) {

		nReadCount = stHeader.nNumProcedureData;

		// ���ν��� ������ ����
		if (pstData != NULL) {

			(*pstData) = new (std::nothrow) VPRD_DATA_T[nReadCount];
			if ((*pstData) != NULL) {
		
				// ������ �ε� (10���� �ε�)
				while (nReadCount || !bResult) {
		
					if (nReadCount > 10) {
				
						bResult		= fileRecord.ReadRecordBlock((PBYTE)(*pstData) + nOffset, sizeof(VPRD_DATA_T) * 10, sizeof(VPRD_HEADER_T) + nOffset);
						nReadCount -= 10;

					} else {
				
						bResult		= fileRecord.ReadRecordBlock((PBYTE)(*pstData) + nOffset, sizeof(VPRD_DATA_T) * nReadCount, sizeof(VPRD_HEADER_T) + nOffset);
						nReadCount	= 0;
					}

					if  (!bResult)		break;

					nOffset += (sizeof(VPRD_DATA_T) * 10);
				}
		
			} else {
		
				bResult = FALSE;
			}
		}
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// ���� ���ν��� ���� /////////////////////////////////////////////////////////
BOOL CMainApp::SaveVisionProcedure(const CString& strProcedureFile, VPRD_HEADER_T& stHeader, PVPRD_DATA_T pstData /* = NULL */)
{
	BOOL			bResult		= FALSE;
	INT				nRetCode	= 0;
	UINT			nOffset		= 0;
	UINT			nWriteCount	= 0;
	CDpsFileRecord	fileRecord;


	/////////////////////////////////////////////////////////////////
	// ���� �ڵ� ���� ///////////////////////////////////////////////
	_tcscpy_s(stHeader.szUniqueCode, MAX_STRINPUT_L, _VPRD_UNIQUE_CODE);


	/////////////////////////////////////////////////////////////////
	// ���ν��� ���� ���� ///////////////////////////////////////////
	fileRecord.SetFileName(strProcedureFile);

	do {

		// ��� ����
		if (bResult = fileRecord.WriteHeader(&stHeader, sizeof(VPRD_HEADER_T))) {
		
			if (pstData != NULL) {

				// ������ ���� (10���� ����)
				nOffset		= 0;
				nWriteCount	= stHeader.nNumProcedureData;
				while (nWriteCount || !bResult) {
			
					if (nWriteCount > 10) {
					
						bResult		 = fileRecord.WriteRecordBlock((PBYTE)pstData + nOffset, sizeof(VPRD_DATA_T) * 10, sizeof(VPRD_HEADER_T) + nOffset);
						nWriteCount -= 10;	

					} else {
					
						bResult		 = fileRecord.WriteRecordBlock((PBYTE)pstData + nOffset, sizeof(VPRD_DATA_T) * nWriteCount, sizeof(VPRD_HEADER_T) + nOffset);
						nWriteCount	 = 0;
					}

					nOffset += (sizeof(VPRD_DATA_T) * 10);
				}
			}
		}

		if (!bResult) {

			nRetCode = m_MessageBox.Message(MB_RETRYCANCEL | MB_ICONERROR, _T("���� ���� ����!"), _T("���ν��� ���� ���� �� ������ �߻��߽��ϴ�."));
		}

	} while (!bResult && nRetCode == IDRETRY);


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// CAN �޼��� ���μ��� : ���� /////////////////////////////////////////////////
BOOL CMainApp::TPRD_CAN_MSG_VERIFY_Process(PCAN_PACKET_T& stPacket, TPRD_CAN_MSG_T& stCAN_MSG)
{
	BOOL		bResult		= TRUE;
	BYTE		byDATA		= 0;


	/////////////////////////////////////////////////////////////////
	// ������ �� //////////////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_CAN_MSG_BYTE; nIndex++) {
									
		byDATA = stPacket.stMessage.DATA[nIndex] & stCAN_MSG.abDataMask[nIndex];
		if (stCAN_MSG.abData[nIndex] != byDATA) {
										
			bResult = FALSE;
			break;
		}
	}

	
	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// CAN �޼��� ���μ��� ////////////////////////////////////////////////////////
BOOL CMainApp::TPRD_CAN_MSG_Process(TPRD_CAN_MSG_T& stCAN_MSG)
{
	USES_CONVERSION;

	BOOL		bResult		= TRUE;
	CString		strData		= _T("");
	SYSTEMTIME	stTimeCurrent;


	/////////////////////////////////////////////////////////////////
	// �ʱ�ȭ ///////////////////////////////////////////////////////
	ZeroMemory(stCAN_MSG.abData, sizeof(BYTE) * MAX_CAN_MSG_BYTE);
	ZeroMemory(stCAN_MSG.abDataMask, sizeof(BYTE) * MAX_CAN_MSG_BYTE);
	GetLocalTime(&stTimeCurrent);


	/////////////////////////////////////////////////////////////////
	// CAN ������ ///////////////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_CAN_MSG_BYTE; nIndex++) {
	
		// ������ ����� üũ
// 		if (stCAN_MSG.szData[nIndex][0] == TEXT('$')) {
// 
// 			strData = stCAN_MSG.szData[nIndex];
// 			if (strData.Compare(g_szCAN_RESERVED_VALUE[CAN_VALUE_YEAR_1]) == 0)	stCAN_MSG.abData[nIndex] = (BYTE)(((WORD)DPS_DecToBcd(stTimeCurrent.wYear) & 0xFF00) >> 8);
// 			if (strData.Compare(g_szCAN_RESERVED_VALUE[CAN_VALUE_YEAR_2]) == 0)	stCAN_MSG.abData[nIndex] = (BYTE)((WORD)DPS_DecToBcd(stTimeCurrent.wYear) & 0xFF);
// 			if (strData.Compare(g_szCAN_RESERVED_VALUE[CAN_VALUE_MONTH]) == 0)	stCAN_MSG.abData[nIndex] = (BYTE)DPS_DecToBcd(stTimeCurrent.wMonth);
// 			if (strData.Compare(g_szCAN_RESERVED_VALUE[CAN_VALUE_DAY]) == 0)	stCAN_MSG.abData[nIndex] = (BYTE)DPS_DecToBcd(stTimeCurrent.wDay);
// 
// 			continue;
// 		}

		// HEX ��ȯ
		stCAN_MSG.abData[nIndex] = (BYTE)DPS_HexToDec(W2A(stCAN_MSG.szData[nIndex]));
	}


	/////////////////////////////////////////////////////////////////
	// CAN ����ũ ///////////////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_CAN_MSG_BYTE; nIndex++) {

		// HEX ��ȯ
		stCAN_MSG.abDataMask[nIndex] = (BYTE)DPS_HexToDec(W2A(stCAN_MSG.szDataMask[nIndex]));
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// CAN �޼��� ���μ��� : ���� ������ //////////////////////////////////////////
BOOL CMainApp::TPRD_CAN_MSG_SECURITY_Process(PCAN_PACKET_T& stPacket, TPRD_CAN_MSG_T& stCAN_MSG, UINT& nSecurityCode)
{
	USES_CONVERSION;

	BOOL		bResult		= TRUE;
	CString		strData		= _T("");


	/////////////////////////////////////////////////////////////////
	// �۽� ��� ////////////////////////////////////////////////////
	if (stCAN_MSG.nTypeMessage == CAN_MSG_TYPE_TX) {
	
		// SECURITY-KEY ����
// 		for (UINT nIndex = 0; nIndex < MPUSBCAN_MAX_CAN_BYTE; nIndex++) {
// 	
// 			// ������ ����� üũ
// 			if (stCAN_MSG.szData[nIndex][0] == TEXT('$')) {
// 
// 				strData = stCAN_MSG.szData[nIndex];
// 				if (strData.Compare(g_szCAN_RESERVED_VALUE[CAN_VALUE_SECU_1]) == 0)	stPacket.abData[nIndex] = (BYTE)((nSecurityCode & 0xFF000000) >> 24);
// 				if (strData.Compare(g_szCAN_RESERVED_VALUE[CAN_VALUE_SECU_2]) == 0)	stPacket.abData[nIndex] = (BYTE)((nSecurityCode & 0x00FF0000) >> 16);
// 				if (strData.Compare(g_szCAN_RESERVED_VALUE[CAN_VALUE_SECU_3]) == 0)	stPacket.abData[nIndex] = (BYTE)((nSecurityCode & 0x0000FF00) >> 8);
// 				if (strData.Compare(g_szCAN_RESERVED_VALUE[CAN_VALUE_SECU_4]) == 0)	stPacket.abData[nIndex] = (BYTE)(nSecurityCode & 0x000000FF);
// 
// 				continue;
// 			}
// 		}
	}


	/////////////////////////////////////////////////////////////////
	// ���� ��� ////////////////////////////////////////////////////
	if (stCAN_MSG.nTypeMessage == CAN_MSG_TYPE_RX) {
	
		// SEED-KEY ����
// 		for (UINT nIndex = 0; nIndex < MPUSBCAN_MAX_CAN_BYTE; nIndex++) {
// 	
// 			// ������ ����� üũ
// 			if (stCAN_MSG.szData[nIndex][0] == TEXT('$')) {
// 
// 				strData = stCAN_MSG.szData[nIndex];
// 				if (strData.Compare(g_szCAN_RESERVED_VALUE[CAN_VALUE_SECU_1]) == 0)	nSecurityCode |= stPacket.abData[nIndex] << 24;
// 				if (strData.Compare(g_szCAN_RESERVED_VALUE[CAN_VALUE_SECU_2]) == 0)	nSecurityCode |= stPacket.abData[nIndex] << 16;
// 				if (strData.Compare(g_szCAN_RESERVED_VALUE[CAN_VALUE_SECU_3]) == 0)	nSecurityCode |= stPacket.abData[nIndex] << 8;
// 				if (strData.Compare(g_szCAN_RESERVED_VALUE[CAN_VALUE_SECU_4]) == 0)	nSecurityCode |= stPacket.abData[nIndex];
// 
// 				continue;
// 			}
// 		}
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// CAN �޼��� ���μ��� : ������ ///////////////////////////////////////////////
BOOL CMainApp::TPRD_CAN_MSG_DATA_Process(PCAN_PACKET_T& stPacket, TPRD_CAN_MSG_T& stCAN_MSG, PBYTE pData, UINT& nLength)
{
	USES_CONVERSION;

	BOOL		bResult		= TRUE;
	BOOL		bOnData		= FALSE;
	CString		strData		= _T("");


	/////////////////////////////////////////////////////////////////
	// �ʱ�ȭ ///////////////////////////////////////////////////////
	if (pData != NULL)	ZeroMemory(pData, nLength);
	nLength = 0;


	/////////////////////////////////////////////////////////////////
	// �۽� ��� ////////////////////////////////////////////////////
	if (stCAN_MSG.nTypeMessage == CAN_MSG_TYPE_TX) {

		// Not yet
	}


	/////////////////////////////////////////////////////////////////
	// ���� ��� ////////////////////////////////////////////////////
	if (stCAN_MSG.nTypeMessage == CAN_MSG_TYPE_RX) {

		for (UINT nIndex = 0; nIndex < MAX_CAN_MSG_BYTE; nIndex++) {
	
			// ������ ����� üũ
			if (stCAN_MSG.szData[nIndex][0] == TEXT('$')) {

				strData = stCAN_MSG.szData[nIndex];
				bOnData	= FALSE;
				for (UINT nValueNo = 0; nValueNo < MAX_CAN_RESERVED_VALUE; nValueNo++) {
				
					if (strData.CompareNoCase(g_szCAN_RESERVED_VALUE[nValueNo]) == 0) {
					
						bOnData = TRUE;
						break;
					}
				}

				if (bOnData)	pData[nLength++] = stPacket.stMessage.DATA[nIndex];
			}
		}
	}


	return	bResult;
}






///////////////////////////////////////////////////////////////////////////////////////////////////
// CAN ��� ���� //////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ��� ���� �ʱ�ȭ ///////////////////////////////////////////////////////////
void CMainApp::CAN_InitInformation(void)
{
	/////////////////////////////////////////////////////////////////
	// �÷��� �ʱ�ȭ ////////////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_CAN_MESSAGE; nIndex++)
		m_stSystemStatus.bCAN_EnableTransmitData[nIndex] = FALSE;


	/////////////////////////////////////////////////////////////////
	// �۽� ������ �ʱ�ȭ ///////////////////////////////////////////
	ZeroMemory(m_stCAN_TransmitData, sizeof(CAN_MSG_DATA_INFO_T) * MAX_CAN_MESSAGE);
	for (UINT nIndex = 0; nIndex < MAX_CAN_MESSAGE; nIndex++) {
	
		m_stCAN_TransmitData[nIndex].nCAN_ID = g_stCAN_MsgInfo_ID[nIndex].nID;
		m_stCAN_TransmitData[nIndex].nLength = MAX_CAN_MSG_BYTE;
		m_stCAN_TransmitData[nIndex].nType	 = PCAN_MESSAGE_STANDARD;
	}


	/////////////////////////////////////////////////////////////////
	// �ñ׳� ������ �ʱ�ȭ /////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_CAN_SIGNAL_LIST; nIndex++)
		m_strCAN_MsgSignalValue[nIndex].Empty();
}


///////////////////////////////////////////////////////////////////////////////
// �ñ׳� ������ �ʱ�ȭ ///////////////////////////////////////////////////////
void CMainApp::CAN_ClearSignalValue(void)
{
	/////////////////////////////////////////////////////////////////
	// ������ �ʱ�ȭ ////////////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_CAN_SIGNAL_LIST; nIndex++)
		m_strCAN_MsgSignalValue[nIndex].Empty();


	/////////////////////////////////////////////////////////////////
	// ������Ʈ /////////////////////////////////////////////////////
	CAN_UpdateSignalValue();
}


///////////////////////////////////////////////////////////////////////////////
// �ñ׳� ������ ������Ʈ /////////////////////////////////////////////////////
void CMainApp::CAN_UpdateSignalValue(void)
{
	UINT		nMsgNo		= 0;
	UINT		nSignalNo	= 0;
	UINT		nValue		= 0;
	DOUBLE		dblValue	= 0;
	CString		strValue	= _T("");


	/////////////////////////////////////////////////////////////////
	// BMS22 ////////////////////////////////////////////////////////

	// CF_Bms_ChgSts
	nMsgNo		= CID_BMS22;
	nSignalNo	= CF_Bms_ChgSts;
	strValue	= m_strCAN_MsgSignalValue[nSignalNo];
	if (!strValue.IsEmpty()) {

		nValue		= abs(_ttoi(strValue));
		nValue		= (nValue == 1) ? 1 : 0;
		m_stCAN_TransmitData[nMsgNo].abData[0] &= 0xEF;
		m_stCAN_TransmitData[nMsgNo].abData[0] |= (INT8U)nValue << 4;
	}

	// CR_BMS_DisplaySOC
	nMsgNo		= CID_BMS22;
	nSignalNo	= CR_BMS_DisplaySOC;
	strValue	= m_strCAN_MsgSignalValue[nSignalNo];
	if (!strValue.IsEmpty()) {

		nValue		= abs(_ttoi(strValue));
		nValue		= ((nValue > 100) ? 100 : nValue) * 2;
		m_stCAN_TransmitData[nMsgNo].abData[1] = (INT8U)nValue;
	}


	/////////////////////////////////////////////////////////////////
	// BMS4 /////////////////////////////////////////////////////////

	// CF_Bms_ChgLamp
	nMsgNo		= CID_BMS4;
	nSignalNo	= CF_Bms_ChgLamp;
	strValue	= m_strCAN_MsgSignalValue[nSignalNo];
	if (!strValue.IsEmpty()) {

		nValue		= abs(_ttoi(strValue));
		nValue		= (nValue > 7) ? 7 : nValue;
		m_stCAN_TransmitData[nMsgNo].abData[7] &= 0xF0;
		m_stCAN_TransmitData[nMsgNo].abData[7] |= (INT8U)(nValue & 0x0F);
	}

	
	/////////////////////////////////////////////////////////////////
	// OBC1 /////////////////////////////////////////////////////////

	// CF_OBC_IG3_DRV_STATE
	nMsgNo		= CID_OBC1;
	nSignalNo	= CF_OBC_IG3_DRV_STATE;
	strValue	= m_strCAN_MsgSignalValue[nSignalNo];
	if (!strValue.IsEmpty()) {

		nValue		= abs(_ttoi(strValue));
		nValue		= (nValue == 1) ? 1 : 0;
		m_stCAN_TransmitData[nMsgNo].abData[4] &= 0xFE;
		m_stCAN_TransmitData[nMsgNo].abData[4] |= (INT8U)(nValue & 0x01);
	}


	/////////////////////////////////////////////////////////////////
	// TMU1 /////////////////////////////////////////////////////////

	// CF_Tmu_IG3Rly
	nMsgNo		= CID_TMU1;
	nSignalNo	= CF_Tmu_IG3Rly;
	strValue	= m_strCAN_MsgSignalValue[nSignalNo];
	if (!strValue.IsEmpty()) {

		nValue		= abs(_ttoi(strValue));
		nValue		= (nValue > 3) ? 3 : nValue;
		m_stCAN_TransmitData[nMsgNo].abData[4] &= 0xFC;
		m_stCAN_TransmitData[nMsgNo].abData[4] |= (INT8U)(nValue & 0x03);
	}


	/////////////////////////////////////////////////////////////////
	// VCU19 ////////////////////////////////////////////////////////

	// CF_VCU_IG3DrvSts
	nMsgNo		= CID_VCU19;
	nSignalNo	= CF_VCU_IG3DrvSts;
	strValue	= m_strCAN_MsgSignalValue[nSignalNo];
	if (!strValue.IsEmpty()) {

		nValue		= abs(_ttoi(strValue));
		nValue		= (nValue == 1) ? 1 : 0;
		m_stCAN_TransmitData[nMsgNo].abData[7] &= 0xEF;
		m_stCAN_TransmitData[nMsgNo].abData[7] |= (INT8U)nValue << 4;
	}


	/////////////////////////////////////////////////////////////////
	// MCU3 /////////////////////////////////////////////////////////

	// CR_Mcu_VehSpd_Kph
	nMsgNo		= CID_MCU3;
	nSignalNo	= CR_Mcu_VehSpd_Kph;
	strValue	= m_strCAN_MsgSignalValue[nSignalNo];
	if (!strValue.IsEmpty()) {

		nValue		= abs(_ttoi(strValue));
		nValue		= (nValue > 255) ? 255 : nValue;
		m_stCAN_TransmitData[nMsgNo].abData[2] = (INT8U)nValue;
	}

	// CR_Mcu_VehSpd_Kph
	nMsgNo		= CID_MCU3;
	nSignalNo	= CR_Mcu_VehSpdDec_Kph;
	strValue	= m_strCAN_MsgSignalValue[nSignalNo];
	if (!strValue.IsEmpty()) {

		dblValue	= abs(_ttof(strValue));
		dblValue	= ((dblValue > 0.99) ? 0.99 : dblValue) / 0.007;
		nValue		= (UINT)dblValue;
		m_stCAN_TransmitData[nMsgNo].abData[3] = (INT8U)nValue;
	}


	/////////////////////////////////////////////////////////////////
	// WHL_SPD11 ////////////////////////////////////////////////////

	// WHL_SPD_RL
	nMsgNo		= CID_WHL_SPD11;
	nSignalNo	= WHL_SPD_RL;
	strValue	= m_strCAN_MsgSignalValue[nSignalNo];
	if (!strValue.IsEmpty()) {

		dblValue	= abs(_ttof(strValue));
		dblValue	= ((dblValue > 507.873) ? 507.873 : dblValue) / 0.031;
		nValue		= (UINT)dblValue;
		m_stCAN_TransmitData[nMsgNo].abData[4] =  (INT8U)(nValue & 0x00FF);
		m_stCAN_TransmitData[nMsgNo].abData[5] &= 0xC0;
		m_stCAN_TransmitData[nMsgNo].abData[5] |= (INT8U)((nValue & 0x3F00) >> 8);
	}

	// WHL_SPD_RR
	nMsgNo		= CID_WHL_SPD11;
	nSignalNo	= WHL_SPD_RR;
	strValue	= m_strCAN_MsgSignalValue[nSignalNo];
	if (!strValue.IsEmpty()) {

		dblValue	= abs(_ttof(strValue));
		dblValue	= ((dblValue > 507.873) ? 507.873 : dblValue) / 0.031;
		nValue		= (UINT)dblValue;
		m_stCAN_TransmitData[nMsgNo].abData[6] =  (INT8U)(nValue & 0x00FF);
		m_stCAN_TransmitData[nMsgNo].abData[7] &= 0xC0;
		m_stCAN_TransmitData[nMsgNo].abData[7] |= (INT8U)((nValue & 0x3F00) >> 8);
	}
}







///////////////////////////////////////////////////////////////////////////////////////////////////
// ��� ��Ʈ�ѷ� //////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ��� ��Ʈ�ѷ� �������� �ʱ�ȭ //////////////////////////////////////////////
void CMainApp::Motion_Initialize(void)
{
	/////////////////////////////////////////////////////////////////
	// ���� ���� ////////////////////////////////////////////////////
	for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++) {

		// ���� OFF
		AxmSignalSetServoOnLevel(nAxisNo, HIGH);
		AxmSignalServoOn(nAxisNo, DISABLE);
		AxmMoveEStop(nAxisNo);

		// 1 �޽��� 0.01mm �̵� 
		AxmMotSetMoveUnitPerPulse(nAxisNo, m_stMotionAxisInfo[nAxisNo].dblResolution, 1);

		// �⺻ �ӵ� ����
		AxmMotSetMinVel(nAxisNo, 1.0);
		AxmMotSetMaxVel(nAxisNo, m_stMotionAxisInfo[nAxisNo].dblSpeedMAX);
		AxmMotSetAccelUnit(nAxisNo, SEC);

		// COMMAND �޽� ��� ��� (���� ȸ�� ����)
		AxmMotSetPulseOutMethod(nAxisNo, m_stMotionAxisInfo[nAxisNo].nPulseDirection == MAI_PULSE_DIR_CCWCW ? TwoCcwCwHigh : TwoCwCcwHigh);

		// ���ڴ� �޽� �Է�����
		AxmMotSetEncInputMethod(nAxisNo, m_stMotionAxisInfo[nAxisNo].nEncoderDirection == MAI_ENC_DIR_SQR4MODE ? ObverseSqr4Mode : ReverseSqr4Mode);

		// ����Ʈ���� ����Ʈ ���� (������)
		AxmSignalSetSoftLimit(nAxisNo, DISABLE, EMERGENCY_STOP, COMMAND, m_stMotionAxisInfo[nAxisNo].dblLimitPositivePos, m_stMotionAxisInfo[nAxisNo].dblLimitNegativePos);

		// ����Ʈ ���� ��Ƽ�� ����
		AxmSignalSetLimit(nAxisNo,	EMERGENCY_STOP, 
									m_stMotionAxisInfo[nAxisNo].nSensorLevelPLimit == MAI_ACT_LV_HIGH ? HIGH : (m_stMotionAxisInfo[nAxisNo].nSensorLevelPLimit == MAI_ACT_LV_LOW ? LOW : UNUSED), 
									m_stMotionAxisInfo[nAxisNo].nSensorLevelNLimit == MAI_ACT_LV_HIGH ? HIGH : (m_stMotionAxisInfo[nAxisNo].nSensorLevelNLimit == MAI_ACT_LV_LOW ? LOW : UNUSED)), 

		// Ȩ ���� ��Ƽ�� ����
		AxmHomeSetSignalLevel(nAxisNo, m_stMotionAxisInfo[nAxisNo].nHomeSensorLogic == MAI_ACT_LV_HIGH ? HIGH : LOW);	

		// Z-Phase ��Ƽ�� ����
		AxmSignalSetZphaseLevel(nAxisNo, HIGH);		

		// �������� ��Ƽ�� ����
		AxmSignalSetInpos(nAxisNo, HIGH);		

		// ���� �˶� ��Ƽ�� ����
		AxmSignalSetServoAlarm(nAxisNo, m_stMotionAxisInfo[nAxisNo].nSensorLevelAlarm == MAI_ACT_LV_HIGH ? HIGH : (m_stMotionAxisInfo[nAxisNo].nSensorLevelAlarm == MAI_ACT_LV_LOW ? LOW : UNUSED));		

		// EMG-STOP ��Ƽ�� ����
		AxmSignalSetStop(nAxisNo, EMERGENCY_STOP, UNUSED);					

		// ��ġ ī���� �ʱ�ȭ
		AxmStatusSetCmdPos(nAxisNo, 0);
		AxmStatusSetActPos(nAxisNo, 0);

		// ���� ��� ����
		AxmSignalWriteOutputBit(nAxisNo, UIO_OUT2, DISABLE);
		AxmSignalWriteOutputBit(nAxisNo, UIO_OUT3, DISABLE);
		AxmSignalWriteOutputBit(nAxisNo, UIO_OUT4, DISABLE);
		AxmSignalWriteOutputBit(nAxisNo, UIO_OUT5, DISABLE);

		// ��Ÿ
		AxmMotSetAbsRelMode(nAxisNo, POS_REL_MODE);
		AxmMotSetProfileMode(nAxisNo, SYM_S_CURVE_MODE);
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���� ////////////////////////////////////////////////////
}


///////////////////////////////////////////////////////////////////////////////
// ��� �� ���� ���� //////////////////////////////////////////////////////////
BOOL CMainApp::SaveMotionAxisInfo(BOOL bBinary /* = TRUE */)
{	
	CString		strFileName		= _T("");
	BOOL		bFileResult		= TRUE;
	


	/////////////////////////////////////////////////////////////////
	// ���̳ʸ� ���� ////////////////////////////////////////////////
	if (bBinary) {

		UINT	nRetryCount	= 0;
		CFile	fileWrite;

		TRY {

			/////////////////////////////////////////////////////////
			// ���� �̸� ���� ///////////////////////////////////////
			strFileName.Format(_T("%s\\%s"), DPS_GetCurrentAppDirectory(), _BFILE_MOTION_AXIS_INFO);


			/////////////////////////////////////////////////////////
			// ���� ���� ////////////////////////////////////////////
			while (TRUE) {

				if (bFileResult = fileWrite.Open(strFileName, CFile::modeCreate | CFile::modeWrite)) {

					for (UINT nIndex = 0; nIndex < MAX_MOTION_AXIS; nIndex++)
						fileWrite.Write(&m_stMotionAxisInfo[nIndex], sizeof(DPS_MOTION_AXIS_INFO_T));

					fileWrite.Close();
				}

				// �����̰ų� ��õ� Ƚ���� �����Ǹ�, ����
				if (bFileResult || ++nRetryCount >= MAX_RETRY_COUNT)
					break;
			}

		} CATCH (CFileException, e) {
			e->ReportError();
		} END_CATCH


	/////////////////////////////////////////////////////////////////
	// �ؽ�Ʈ ���� //////////////////////////////////////////////////
	} else {
	
		TCHAR	szSection[MAX_STRVALUE];
		TCHAR	szValue[MAX_STRVALUE];
		TCHAR	szKeyName[MAX_STRVALUE];


		/////////////////////////////////////////////////////////////
		// ���� �̸� ���� ///////////////////////////////////////////
		strFileName.Format(_T("%s\\%s"), DPS_GetCurrentAppDirectory(), _TFILE_MOTION_AXIS_INFO);


		/////////////////////////////////////////////////////////////
		// �� ���� ���� /////////////////////////////////////////////
		for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++) {
		
			// ����
			ZeroMemory(szSection, MAX_STRVALUE);
			_stprintf_s(szSection, MAX_STRVALUE, _T("AXIS %02d"), nAxisNo + 1);

			// �޽� ��� ����
			_stprintf_s(szValue, MAX_STRVALUE, _T("%d"), m_stMotionAxisInfo[nAxisNo].nPulseDirection);
			WritePrivateProfileString(szSection, _T("PULSE_DIRECTION"), szValue, strFileName);

			// ���ھ� �Է�
			_stprintf_s(szValue, MAX_STRVALUE, _T("%d"), m_stMotionAxisInfo[nAxisNo].nEncoderDirection);
			WritePrivateProfileString(szSection, _T("ENCODER_DIRECTION"), szValue, strFileName);

			// Ȩ ���� ��
			_stprintf_s(szValue, MAX_STRVALUE, _T("%d"), m_stMotionAxisInfo[nAxisNo].nHomeSensorLogic);
			WritePrivateProfileString(szSection, _T("HOME_SENSOR_LOGIC"), szValue, strFileName);

			// ���� ���� : P-LIMIT
			_stprintf_s(szValue, MAX_STRVALUE, _T("%d"), m_stMotionAxisInfo[nAxisNo].nSensorLevelPLimit);
			WritePrivateProfileString(szSection, _T("SENSOR_LEVEL_PLIMIT"), szValue, strFileName);

			// ���� ���� : N-LIMIT
			_stprintf_s(szValue, MAX_STRVALUE, _T("%d"), m_stMotionAxisInfo[nAxisNo].nSensorLevelNLimit);
			WritePrivateProfileString(szSection, _T("SENSOR_LEVEL_NLIMIT"), szValue, strFileName);

			// ���� ���� : �˶�
			_stprintf_s(szValue, MAX_STRVALUE, _T("%d"), m_stMotionAxisInfo[nAxisNo].nSensorLevelAlarm);
			WritePrivateProfileString(szSection, _T("SENSOR_LEVEL_ALARM"), szValue, strFileName);

			// ���� ���ص�
			_stprintf_s(szValue, MAX_STRVALUE, _T("%.12f"), m_stMotionAxisInfo[nAxisNo].dblResolution);
			WritePrivateProfileString(szSection, _T("RESOLUTION"), szValue, strFileName);

			// ����Ʈ���� ����Ʈ
			_stprintf_s(szValue, MAX_STRVALUE, _T("%.2f"), m_stMotionAxisInfo[nAxisNo].dblLimitPositivePos);
			WritePrivateProfileString(szSection, _T("SOFT_LIMIT_POSITIVE"), szValue, strFileName);
			_stprintf_s(szValue, MAX_STRVALUE, _T("%.2f"), m_stMotionAxisInfo[nAxisNo].dblLimitNegativePos);
			WritePrivateProfileString(szSection, _T("SOFT_LIMIT_NEGATIVE"), szValue, strFileName);

			// �ӵ�
			_stprintf_s(szValue, MAX_STRVALUE, _T("%.2f"), m_stMotionAxisInfo[nAxisNo].dblSpeedMAX);
			WritePrivateProfileString(szSection, _T("SPEED_MAX"), szValue, strFileName);
			_stprintf_s(szValue, MAX_STRVALUE, _T("%.2f"), m_stMotionAxisInfo[nAxisNo].dblSpeedBase);
			WritePrivateProfileString(szSection, _T("SPEED_BASE"), szValue, strFileName);
			_stprintf_s(szValue, MAX_STRVALUE, _T("%.2f"), m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch);
			WritePrivateProfileString(szSection, _T("SPEED_HOME"), szValue, strFileName);
			_stprintf_s(szValue, MAX_STRVALUE, _T("%.2f"), m_stMotionAxisInfo[nAxisNo].dblSpeedJogSlow);
			WritePrivateProfileString(szSection, _T("SPEED_JOG_SLOW"), szValue, strFileName);
			_stprintf_s(szValue, MAX_STRVALUE, _T("%.2f"), m_stMotionAxisInfo[nAxisNo].dblSpeedJogFast);
			WritePrivateProfileString(szSection, _T("SPEED_JOG_FAST"), szValue, strFileName);

			// ������ �ð�
			_stprintf_s(szValue, MAX_STRVALUE, _T("%.2f"), m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration);
			WritePrivateProfileString(szSection, _T("TIME_ACCELERATION"), szValue, strFileName);
			_stprintf_s(szValue, MAX_STRVALUE, _T("%.2f"), m_stMotionAxisInfo[nAxisNo].dblTimeAccelerationJog);
			WritePrivateProfileString(szSection, _T("TIME_ACCELERATION_JOG"), szValue, strFileName);

			// ���� ��ġ
			_stprintf_s(szValue, MAX_STRVALUE, _T("%.2f"), m_stMotionAxisInfo[nAxisNo].dblSafePositionMIN);
			WritePrivateProfileString(szSection, _T("POSITION_SAFE_MIN"), szValue, strFileName);
			_stprintf_s(szValue, MAX_STRVALUE, _T("%.2f"), m_stMotionAxisInfo[nAxisNo].dblSafePositionMAX);
			WritePrivateProfileString(szSection, _T("POSITION_SAFE_MAX"), szValue, strFileName);

			// Ŀ���� ��ġ
			for (UINT nIndex = 0; nIndex < MAX_MAI_CUSTOM_POSITION; nIndex++) {
			
				_stprintf_s(szKeyName, MAX_STRVALUE, _T("POSITION_CUSTOM_%02d"), nIndex + 1);
				_stprintf_s(szValue, MAX_STRVALUE, _T("%.2f"), m_stMotionAxisInfo[nAxisNo].dblCustomPosition[nIndex]);
				WritePrivateProfileString(szSection, szKeyName, szValue, strFileName);
			}
		}
	}


	/////////////////////////////////////////////////////////////////
	// �޼��� ��� //////////////////////////////////////////////////
	if (!bFileResult) {

		if (m_nTypeLanguage == LANGUAGE_KOR)	SErrorMessage(FALSE, _T("��� �� ������ ������ �� �����ϴ�."));
		else									SErrorMessage(FALSE, _T("Can NOT Save Motion Axis Information"));
	}


	return	bFileResult;
}


///////////////////////////////////////////////////////////////////////////////
// ��� �� ���� �ε� //////////////////////////////////////////////////////////
BOOL CMainApp::LoadMotionAxisInfo(BOOL bBinary /* = TRUE */)
{
	CString		strFileName		= _T("");
	BOOL		bFileResult		= TRUE;
	


	/////////////////////////////////////////////////////////////////
	// ���̳ʸ� �ε� ////////////////////////////////////////////////
	if (bBinary) {

		UINT	nRetryCount		= 0;
		UINT	nReadCount		= 0;
		CFile	fileRead;


		TRY {

			/////////////////////////////////////////////////////////
			// ���� �̸� ���� ///////////////////////////////////////
			strFileName.Format(_T("%s\\%s"), DPS_GetCurrentAppDirectory(), _BFILE_MOTION_AXIS_INFO);


			/////////////////////////////////////////////////////////
			// ���� �б� ////////////////////////////////////////////
			while (TRUE) {

				if (bFileResult = fileRead.Open(strFileName, CFile::modeRead)) {

					for (UINT nIndex = 0; nIndex < MAX_MOTION_AXIS; nIndex++) {

						ZeroMemory(&m_stMotionAxisInfo[nIndex], sizeof(DPS_MOTION_AXIS_INFO_T));
						nReadCount = fileRead.Read(&m_stMotionAxisInfo[nIndex], sizeof(DPS_MOTION_AXIS_INFO_T));

						if (nReadCount != sizeof(DPS_MOTION_AXIS_INFO_T)) {

							bFileResult = FALSE;
							break;
						}
					}

					fileRead.Close();
				}

				// �����̰ų� ��õ� Ƚ���� �����Ǹ�, ����
				if (bFileResult || ++nRetryCount >= MAX_RETRY_COUNT)
					break;
			}

		} CATCH (CFileException, e) {
			e->ReportError();
		} END_CATCH
	
	
	/////////////////////////////////////////////////////////////////
	// �ؽ�Ʈ �ε� //////////////////////////////////////////////////
	} else {
	
		TCHAR	szSection[MAX_STRVALUE];
		TCHAR	szStringBuf[MAX_STRVALUE_L];
		TCHAR	szKeyName[MAX_STRVALUE];


		/////////////////////////////////////////////////////////////
		// ���� �̸� ���� ///////////////////////////////////////////
		strFileName.Format(_T("%s\\%s"), DPS_GetCurrentAppDirectory(), _TFILE_MOTION_AXIS_INFO);


		/////////////////////////////////////////////////////////////
		// �� ���� ���� /////////////////////////////////////////////
		for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++) {

			// ����
			ZeroMemory(szSection, MAX_STRVALUE);
			_stprintf_s(szSection, MAX_STRVALUE, _T("AXIS %02d"), nAxisNo + 1);

			// �޽� ��� ����
			GetPrivateProfileString(szSection, _T("PULSE_DIRECTION"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].nPulseDirection		= _ttoi(szStringBuf);

			// ���ڴ� �Է�
			GetPrivateProfileString(szSection, _T("ENCODER_DIRECTION"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].nEncoderDirection	= _ttoi(szStringBuf);
			 
			// Ȩ ���� ��
			GetPrivateProfileString(szSection, _T("HOME_SENSOR_LOGIC"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].nHomeSensorLogic	= _ttoi(szStringBuf);

			// ���� ���� : P-LIMIT
			GetPrivateProfileString(szSection, _T("SENSOR_LEVEL_PLIMIT"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].nSensorLevelPLimit	= _ttoi(szStringBuf);

			// ���� ���� : N-LIMIT
			GetPrivateProfileString(szSection, _T("SENSOR_LEVEL_NLIMIT"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].nSensorLevelNLimit	= _ttoi(szStringBuf);

			// ���� ���� : �˶�
			GetPrivateProfileString(szSection, _T("SENSOR_LEVEL_ALARM"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].nSensorLevelAlarm	= _ttoi(szStringBuf);

			// ���� ���ص�
			GetPrivateProfileString(szSection, _T("RESOLUTION"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].dblResolution		= _ttof(szStringBuf);

			// ����Ʈ���� ����Ʈ
			GetPrivateProfileString(szSection, _T("SOFT_LIMIT_POSITIVE"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].dblLimitPositivePos	= _ttof(szStringBuf);
			GetPrivateProfileString(szSection, _T("SOFT_LIMIT_NEGATIVE"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].dblLimitNegativePos	= _ttof(szStringBuf);

			// �ӵ�
			GetPrivateProfileString(szSection, _T("SPEED_MAX"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].dblSpeedMAX			= _ttof(szStringBuf);
			GetPrivateProfileString(szSection, _T("SPEED_BASE"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].dblSpeedBase		= _ttof(szStringBuf);
			GetPrivateProfileString(szSection, _T("SPEED_HOME"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch	= _ttof(szStringBuf);
			GetPrivateProfileString(szSection, _T("SPEED_JOG_SLOW"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].dblSpeedJogSlow		= _ttof(szStringBuf);
			GetPrivateProfileString(szSection, _T("SPEED_JOG_FAST"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].dblSpeedJogFast		= _ttof(szStringBuf);

			// ������ �ð�
			GetPrivateProfileString(szSection, _T("TIME_ACCELERATION"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration		= _ttof(szStringBuf);
			GetPrivateProfileString(szSection, _T("TIME_ACCELERATION_JOG"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].dblTimeAccelerationJog	= _ttof(szStringBuf);

			// ���� ��ġ
			GetPrivateProfileString(szSection, _T("POSITION_SAFE_MIN"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].dblSafePositionMIN		= _ttof(szStringBuf);
			GetPrivateProfileString(szSection, _T("POSITION_SAFE_MAX"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].dblSafePositionMAX		= _ttof(szStringBuf);

			// Ŀ���� ��ġ
			for (UINT nIndex = 0; nIndex < MAX_MAI_CUSTOM_POSITION; nIndex++) {
			
				_stprintf_s(szKeyName, MAX_STRVALUE, _T("POSITION_CUSTOM_%02d"), nIndex + 1);
				GetPrivateProfileString(szSection, szKeyName, _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
				m_stMotionAxisInfo[nAxisNo].dblCustomPosition[nIndex]	= _ttof(szStringBuf);
			}
		}
	}


	/////////////////////////////////////////////////////////////////
	// �޼��� ��� //////////////////////////////////////////////////
	if (!bFileResult) {

		if (m_nTypeLanguage == LANGUAGE_KOR)	SErrorMessage(FALSE, _T("��� �� ������ �ε��� �� �����ϴ�."));
		else									SErrorMessage(FALSE, _T("Can NOT Load Motion Axis Information"));
	}


	return	bFileResult;
}


///////////////////////////////////////////////////////////////////////////////
// ��� �̵� : ��� ��ǥ //////////////////////////////////////////////////////
BOOL CMainApp::Motion_Move(UINT nAxisNo, DOUBLE dblDistance, DOUBLE dblSpeed, BOOL bOnMessage /* = TRUE */)
{
	if (dblDistance != 0) {

		DWORD	dwRetCode	= 0;


		// �ӵ� ����
		dblSpeed = __min(dblSpeed, m_stMotionAxisInfo[nAxisNo].dblSpeedMAX);

		// ��� �̵�
		AxmMotSetAbsRelMode(nAxisNo, POS_REL_MODE);
		AxmMotSetProfileMode(nAxisNo, SYM_TRAPEZOIDE_MODE);
		dwRetCode = AxmMoveStartPos(nAxisNo, dblDistance, dblSpeed, m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration, m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration);
		if (dwRetCode != AXT_RT_SUCCESS)	NormalMessage(TRUE, _T("Move::AxmMoveStartPos() Failure! RetCode = %d (%08X)"), dwRetCode, dwRetCode);

		// �޼��� ���
		if (bOnMessage) {

			DOUBLE	dblCmdPos	= 0;
			DOUBLE	dblActPos	= 0;
	
			AxmStatusGetActPos(nAxisNo, &dblActPos);
			AxmStatusGetCmdPos(nAxisNo, &dblCmdPos);

			NormalMessage(TRUE,	_T("%s::%s, CurrCmdPos=%.2f, CurrActPos=%.2f, Distance=%.2f, Speed=%.2f"),	
								g_stSystemString[SYSSTR_MOTION_MOVE_START].szDescription[m_nTypeLanguage],
								g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
								dblCmdPos, dblActPos, dblDistance, dblSpeed);
		}
	}

	return	TRUE;
}

BOOL CMainApp::Motion_MoveEx(UINT nAxisNo, DOUBLE dblDistance, DOUBLE dblSpeed, DOUBLE dblAccel, DOUBLE dblDecel, BOOL bOnMessage /* = TRUE */)
{
	if (dblDistance != 0) {

		DWORD	dwRetCode	= 0;

		// �ӵ� ����
		dblSpeed = __min(dblSpeed, m_stMotionAxisInfo[nAxisNo].dblSpeedMAX);

		// ��� �̵�
		AxmMotSetAbsRelMode(nAxisNo, POS_REL_MODE);
		AxmMotSetProfileMode(nAxisNo, ASYM_S_CURVE_MODE);
		dwRetCode = AxmMoveStartPos(nAxisNo, dblDistance, dblSpeed, dblAccel, dblDecel);
		if (dwRetCode != AXT_RT_SUCCESS)	NormalMessage(TRUE, _T("MoveEx::AxmMoveStartPos() Failure! RetCode = %d (%08X)"), dwRetCode, dwRetCode);

		// �޼��� ���
		if (bOnMessage) {

			DOUBLE	dblCmdPos	= 0;
			DOUBLE	dblActPos	= 0;
	
			AxmStatusGetActPos(nAxisNo, &dblActPos);
			AxmStatusGetCmdPos(nAxisNo, &dblCmdPos);

			NormalMessage(TRUE,	_T("%s::%s, CurrCmdPos=%.2f, CurrActPos=%.2f, Distance=%.2f, Speed=%.2f"),	
								g_stSystemString[SYSSTR_MOTION_MOVE_START].szDescription[m_nTypeLanguage],
								g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
								dblCmdPos, dblActPos, dblDistance, dblSpeed);
		}
	}

	return	TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// ��� �̵� : ���� ��ǥ //////////////////////////////////////////////////////
BOOL CMainApp::Motion_MoveTo(UINT nAxisNo, DOUBLE dblPosition, DOUBLE dblSpeed, BOOL bOnMessage /* = TRUE */)
{
	DWORD	dwRetCode	= 0;

	// �ӵ� ����
	dblSpeed = __min(dblSpeed, m_stMotionAxisInfo[nAxisNo].dblSpeedMAX);

	// ��� �̵�
	AxmMotSetAbsRelMode(nAxisNo, POS_ABS_MODE);
	AxmMotSetProfileMode(nAxisNo, SYM_TRAPEZOIDE_MODE);
	dwRetCode = AxmMoveStartPos(nAxisNo, dblPosition, dblSpeed, m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration, m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration);
	if (dwRetCode != AXT_RT_SUCCESS)	NormalMessage(TRUE, _T("MoveTo::AxmMoveStartPos() Failure! RetCode = %d (%08X)"), dwRetCode, dwRetCode);

	// �޼��� ���
	if (bOnMessage) {

		DOUBLE	dblCmdPos	= 0;
		DOUBLE	dblActPos	= 0;
	
		AxmStatusGetActPos(nAxisNo, &dblActPos);
		AxmStatusGetCmdPos(nAxisNo, &dblCmdPos);

		NormalMessage(TRUE,	_T("%s::%s, CurrCmdPos=%.2f, CurrActPos=%.2f, DestCmdPos=%.2f, Speed=%.2f"),	
							g_stSystemString[SYSSTR_MOTION_MOVE_START].szDescription[m_nTypeLanguage],
							g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
							dblCmdPos, dblActPos, dblPosition, dblSpeed);
	}

	return	TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// ��� �̵� : �ӵ� �̵� //////////////////////////////////////////////////////
BOOL CMainApp::Motion_MoveVel(UINT nAxisNo, DOUBLE dblSpeed, DOUBLE dblAccelTime, UINT nDirection)
{
	// �ӵ� ����
	dblSpeed = __min(dblSpeed, m_stMotionAxisInfo[nAxisNo].dblSpeedMAX);
	if (nDirection == MOTION_CCW)	dblSpeed *= -1.0;

	// ��� �̵�
	AxmMoveVel(nAxisNo, dblSpeed, dblAccelTime, dblAccelTime);

	return	TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// ��� �̵� : 2�� ���� ���� �̵� /////////////////////////////////////////////
BOOL CMainApp::Motion_Move2X(LONG lCoord, UINT nAxisNo1, UINT nAxisNo2, DOUBLE dblPos1, DOUBLE dblPos2, DOUBLE dblSpeed, BOOL bOnMessage /* = TRUE */)
{
	LONG	lMapAxis[2];
	DOUBLE	dblPosition[2];
	DOUBLE	dblAccelTime	= 0;
	DWORD	dwStatus		= 0;
	BOOL	bSoftMode		= FALSE;
	BOOL	bResult			= FALSE;


	/////////////////////////////////////////////////////////////////
	// ��� ��ġ ���� ///////////////////////////////////////////////
	lMapAxis[0]		= nAxisNo1;
	lMapAxis[1]		= nAxisNo2;

	dblPosition[0]	= dblPos1;
	dblPosition[1]	= dblPos2;


	/////////////////////////////////////////////////////////////////
	// ��� �ӵ� �� ���� �ð� ���� //////////////////////////////////
	dblSpeed		= __min(dblSpeed, m_stMotionAxisInfo[lMapAxis[0]].dblSpeedMAX);
	dblSpeed		= __min(dblSpeed, m_stMotionAxisInfo[lMapAxis[1]].dblSpeedMAX);
	dblAccelTime	= __max(m_stMotionAxisInfo[lMapAxis[0]].dblTimeAcceleration, m_stMotionAxisInfo[lMapAxis[1]].dblTimeAcceleration);


	/////////////////////////////////////////////////////////////////
	// ��� �Ķ���� ���� ///////////////////////////////////////////
	AxmContiWriteClear(lCoord);
	AxmContiSetAxisMap(lCoord, 2, lMapAxis);
	AxmContiSetProfileMode(lCoord, SYM_S_CURVE_MODE);
	AxmContiSetAbsRelMode(lCoord, POS_ABS_MODE);


	/////////////////////////////////////////////////////////////////
	// ����Ʈ üũ //////////////////////////////////////////////////
	BOOL	bEnableSoftLimit		= FALSE;
	DOUBLE	dblSoftLimitNegative	= 0;
	DOUBLE	dblSoftLimitPositive	= 0;
	DOUBLE	dblCurrentPosition		= 0;

	for (UINT nIndex = 0; nIndex < 2; nIndex++) {

		// �ϵ���� ����Ʈ üũ
		dwStatus = 0;
		AxmStatusReadMechanical(lMapAxis[nIndex], &dwStatus);

		if (dwStatus & 0x00000001)	bSoftMode = TRUE;		// + ����Ʈ
		if (dwStatus & 0x00000002)	bSoftMode = TRUE;		// - ����Ʈ

		// ����Ʈ���� ����Ʈ üũ
		bEnableSoftLimit = Motion_GetSoftLimit(lMapAxis[nIndex], dblSoftLimitNegative, dblSoftLimitPositive);
		if (bEnableSoftLimit) {

			AxmStatusGetCmdPos(lMapAxis[nIndex], &dblCurrentPosition);
			MessageWindow(cDEBUG, _T("Move2X::SoftLimitNeg = %.2f, SoftLimitPos = %.2f, CurrPos = %.2f"), dblSoftLimitNegative, dblSoftLimitPositive, dblCurrentPosition);
			if (dblCurrentPosition <= dblSoftLimitNegative || dblCurrentPosition >= dblSoftLimitPositive)
				bSoftMode = TRUE;
		}
	}


	/////////////////////////////////////////////////////////////////
	// ��� �̵� ////////////////////////////////////////////////////
	if (bSoftMode) {

		// �Ϲ� �̵�
		Motion_MoveTo(lMapAxis[0], dblPos1, m_stMotionAxisInfo[lMapAxis[0]].dblSpeedBase);
		Motion_MoveTo(lMapAxis[1], dblPos2, m_stMotionAxisInfo[lMapAxis[1]].dblSpeedBase);
		bOnMessage = FALSE;

	} else {

		// �ϵ���� ������ ����Ͽ� �̵� : ���� �࿡ ����Ʈ ������ �ɷ�������, �ϵ���� ������ �������� ����
		AxmContiBeginNode(lCoord);
		AxmLineMove(lCoord, dblPosition, dblSpeed, dblAccelTime, dblAccelTime);
		AxmContiEndNode(lCoord);

		DWORD	dwRetCode = AxmContiStart(lCoord, CONTI_NODE_VELOCITY, 0);
		MessageWindow(cDEBUG, _T("Move2X::AxmContiStart result = %d"), dwRetCode);

		// ���� �̵� ���� �� �Ϲ� �̵�
		if (dwRetCode != AXT_RT_SUCCESS) {
		
			NormalMessage(TRUE, _T("Move2X::AxmContiStart() Failure! RetCode = %d"), dwRetCode);
			Motion_MoveTo(lMapAxis[0], dblPos1, dblSpeed);
			Motion_MoveTo(lMapAxis[1], dblPos2, dblSpeed);
			bOnMessage = FALSE;
		}
	}


	/////////////////////////////////////////////////////////////////
	// �޼��� ��� //////////////////////////////////////////////////
	if (bOnMessage) {

		DOUBLE	dblCmdPos	= 0;
		DOUBLE	dblActPos	= 0;
	
		for (UINT nIndex = 0; nIndex < 2; nIndex++) {

			AxmStatusGetActPos(lMapAxis[nIndex], &dblActPos);
			AxmStatusGetCmdPos(lMapAxis[nIndex], &dblCmdPos);

			NormalMessage(TRUE,	_T("%s::%s, CurrCmdPos=%.2f, CurrActPos=%.2f, DestCmdPos=%.2f, Speed=%.2f"),	
								g_stSystemString[SYSSTR_MOTION_MOVE_START].szDescription[m_nTypeLanguage],
								g_stMotionAxisName[lMapAxis[nIndex]].stDescription.szDescription[m_nTypeLanguage],
								dblCmdPos, dblActPos, dblPosition[nIndex], dblSpeed);
		}
	}


	return	bResult;	
}


///////////////////////////////////////////////////////////////////////////////
// ��� �̵� : 3�� ���� ���� �̵� /////////////////////////////////////////////
BOOL CMainApp::Motion_Move3X(LONG lCoord, UINT nAxisNo1, UINT nAxisNo2, UINT nAxisNo3, DOUBLE dblPos1, DOUBLE dblPos2, DOUBLE dblPos3, DOUBLE dblSpeed, BOOL bOnMessage /* = TRUE */)
{
	LONG	lMapAxis[3];
	DOUBLE	dblPosition[3];
	DOUBLE	dblAccelTime	= 0;
	DWORD	dwStatus		= 0;
	BOOL	bSoftMode		= FALSE;
	BOOL	bResult			= FALSE;


	/////////////////////////////////////////////////////////////////
	// ��� ��ġ ���� ///////////////////////////////////////////////
	lMapAxis[0]		= nAxisNo1;
	lMapAxis[1]		= nAxisNo2;
	lMapAxis[2]		= nAxisNo3;

	dblPosition[0]	= dblPos1;
	dblPosition[1]	= dblPos2;
	dblPosition[2]	= dblPos3;


	/////////////////////////////////////////////////////////////////
	// ��� �ӵ� �� ���� �ð� ���� //////////////////////////////////
	dblSpeed		= __min(dblSpeed, m_stMotionAxisInfo[lMapAxis[0]].dblSpeedMAX);
	dblSpeed		= __min(dblSpeed, m_stMotionAxisInfo[lMapAxis[1]].dblSpeedMAX);
	dblSpeed		= __min(dblSpeed, m_stMotionAxisInfo[lMapAxis[2]].dblSpeedMAX);
	dblAccelTime	= __max(m_stMotionAxisInfo[lMapAxis[0]].dblTimeAcceleration, m_stMotionAxisInfo[lMapAxis[1]].dblTimeAcceleration);
	dblAccelTime	= __max(dblAccelTime, m_stMotionAxisInfo[lMapAxis[2]].dblTimeAcceleration);


	/////////////////////////////////////////////////////////////////
	// ��� �Ķ���� ���� ///////////////////////////////////////////
	AxmContiWriteClear(lCoord);
	AxmContiSetAxisMap(lCoord, 3, lMapAxis);
	AxmContiSetProfileMode(lCoord, SYM_S_CURVE_MODE);
	AxmContiSetAbsRelMode(lCoord, POS_ABS_MODE);


	/////////////////////////////////////////////////////////////////
	// ����Ʈ üũ //////////////////////////////////////////////////
	BOOL	bEnableSoftLimit		= FALSE;
	DOUBLE	dblSoftLimitNegative	= 0;
	DOUBLE	dblSoftLimitPositive	= 0;
	DOUBLE	dblCurrentPosition		= 0;

	for (UINT nIndex = 0; nIndex < 3; nIndex++) {

		// �ϵ���� ����Ʈ üũ
		dwStatus = 0;
		AxmStatusReadMechanical(lMapAxis[nIndex], &dwStatus);

		if (dwStatus & 0x00000001)	bSoftMode = TRUE;		// + ����Ʈ
		if (dwStatus & 0x00000002)	bSoftMode = TRUE;		// - ����Ʈ

		// ����Ʈ���� ����Ʈ üũ
		bEnableSoftLimit = Motion_GetSoftLimit(lMapAxis[nIndex], dblSoftLimitNegative, dblSoftLimitPositive);
		if (bEnableSoftLimit) {

			AxmStatusGetCmdPos(lMapAxis[nIndex], &dblCurrentPosition);
			MessageWindow(cDEBUG, _T("Move3X::SoftLimitNeg = %.2f, SoftLimitPos = %.2f, CurrPos = %.2f"), dblSoftLimitNegative, dblSoftLimitPositive, dblCurrentPosition);
			if (dblCurrentPosition <= dblSoftLimitNegative || dblCurrentPosition >= dblSoftLimitPositive)
				bSoftMode = TRUE;
		}
	}


	/////////////////////////////////////////////////////////////////
	// ��� �̵� ////////////////////////////////////////////////////
	if (bSoftMode) {

		// �Ϲ� �̵�
		Motion_MoveTo(lMapAxis[0], dblPos1, m_stMotionAxisInfo[lMapAxis[0]].dblSpeedBase);
		Motion_MoveTo(lMapAxis[1], dblPos2, m_stMotionAxisInfo[lMapAxis[1]].dblSpeedBase);
		Motion_MoveTo(lMapAxis[2], dblPos3, m_stMotionAxisInfo[lMapAxis[2]].dblSpeedBase);
		bOnMessage = FALSE;

	} else {

		// �ϵ���� ������ ����Ͽ� �̵� : ���� �࿡ ����Ʈ ������ �ɷ�������, �ϵ���� ������ �������� ����
		AxmContiBeginNode(lCoord);
		AxmLineMove(lCoord, dblPosition, dblSpeed, dblAccelTime, dblAccelTime);
		AxmContiEndNode(lCoord);

		DWORD	dwRetCode = AxmContiStart(lCoord, CONTI_NODE_VELOCITY, 0);
		MessageWindow(cDEBUG, _T("Move3X::AxmContiStart result = %d"), dwRetCode);

		// ���� �̵� ���� �� �Ϲ� �̵�
		if (dwRetCode != AXT_RT_SUCCESS) {
		
			NormalMessage(TRUE, _T("Move3X:AxmContiStart() Failure! RetCode = %d"), dwRetCode);
			Motion_MoveTo(lMapAxis[0], dblPos1, dblSpeed);
			Motion_MoveTo(lMapAxis[1], dblPos2, dblSpeed);
			Motion_MoveTo(lMapAxis[2], dblPos3, dblSpeed);
			bOnMessage = FALSE;
		}
	}


	/////////////////////////////////////////////////////////////////
	// �޼��� ��� //////////////////////////////////////////////////
	if (bOnMessage) {

		DOUBLE	dblCmdPos	= 0;
		DOUBLE	dblActPos	= 0;
	
		for (UINT nIndex = 0; nIndex < 2; nIndex++) {

			AxmStatusGetActPos(lMapAxis[nIndex], &dblActPos);
			AxmStatusGetCmdPos(lMapAxis[nIndex], &dblCmdPos);

			NormalMessage(TRUE,	_T("%s::%s, CurrCmdPos=%.2f, CurrActPos=%.2f, DestCmdPos=%.2f, Speed=%.2f"),	
								g_stSystemString[SYSSTR_MOTION_MOVE_START].szDescription[m_nTypeLanguage],
								g_stMotionAxisName[lMapAxis[nIndex]].stDescription.szDescription[m_nTypeLanguage],
								dblCmdPos, dblActPos, dblPosition[nIndex], dblSpeed);
		}
	}


	return	bResult;	
}


///////////////////////////////////////////////////////////////////////////////
// ��� �̵� : ���� ���� ���� �̵� ////////////////////////////////////////////
BOOL CMainApp::Motion_MoveNX(LONG lCoord, UINT nNumAxis, UINT* pAxisNo, DOUBLE* pPosition, DOUBLE dblSpeed, BOOL bOnMessage /* = TRUE */)
{
	PLONG	pMapAxis		= NULL;
	DOUBLE*	pMapPosition	= NULL;
	DOUBLE	dblAccelTime	= 0;
	DWORD	dwStatus		= 0;
	BOOL	bSoftMode		= FALSE;
	BOOL	bResult			= FALSE;


	/////////////////////////////////////////////////////////////////
	// �Ķ���� üũ ////////////////////////////////////////////////
	if (nNumAxis <= 1)		return	FALSE;
	if (dblSpeed <= 0)		return	FALSE;
	if (pAxisNo == NULL)	return	FALSE;
	if (pPosition == NULL)	return	FALSE;


	/////////////////////////////////////////////////////////////////
	// ���� ���� �Ҵ� ///////////////////////////////////////////////
	pMapAxis = new (std::nothrow) LONG[nNumAxis];
	if (pMapAxis == NULL)	return	FALSE;

	pMapPosition = new (std::nothrow) DOUBLE[nNumAxis];
	if (pMapPosition == NULL) {
	
		delete [] pMapAxis;
		return	FALSE;
	}	


	/////////////////////////////////////////////////////////////////
	// ��� ��ġ ���� ///////////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < nNumAxis; nIndex++) {
	
		pMapAxis[nIndex]		= pAxisNo[nIndex];
		pMapPosition[nIndex]	= pPosition[nIndex];
	}


	/////////////////////////////////////////////////////////////////
	// ��� �ӵ� �� ���� �ð� ���� //////////////////////////////////
	for (UINT nIndex = 0; nIndex < nNumAxis; nIndex++)
		dblSpeed = __min(dblSpeed, m_stMotionAxisInfo[pMapAxis[nIndex]].dblSpeedMAX);

	dblAccelTime = __max(m_stMotionAxisInfo[pMapAxis[0]].dblTimeAcceleration, m_stMotionAxisInfo[pMapAxis[1]].dblTimeAcceleration);
	for (UINT nIndex = 2; nIndex < nNumAxis; nIndex++)
		dblAccelTime = __max(dblAccelTime, m_stMotionAxisInfo[pMapAxis[nIndex]].dblTimeAcceleration);


	/////////////////////////////////////////////////////////////////
	// ��� �Ķ���� ���� ///////////////////////////////////////////
	AxmContiWriteClear(lCoord);
	AxmContiSetAxisMap(lCoord, nNumAxis, pMapAxis);
	AxmContiSetProfileMode(lCoord, SYM_S_CURVE_MODE);
	AxmContiSetAbsRelMode(lCoord, POS_ABS_MODE);


	/////////////////////////////////////////////////////////////////
	// ����Ʈ üũ //////////////////////////////////////////////////
	BOOL	bEnableSoftLimit		= FALSE;
	DOUBLE	dblSoftLimitNegative	= 0;
	DOUBLE	dblSoftLimitPositive	= 0;
	DOUBLE	dblCurrentPosition		= 0;

	for (UINT nIndex = 0; nIndex < nNumAxis; nIndex++) {

		// �ϵ���� ����Ʈ üũ
		dwStatus = 0;
		AxmStatusReadMechanical(pMapAxis[nIndex], &dwStatus);

		if (dwStatus & 0x00000001)	bSoftMode = TRUE;		// + ����Ʈ
		if (dwStatus & 0x00000002)	bSoftMode = TRUE;		// - ����Ʈ

		// ����Ʈ���� ����Ʈ üũ
		bEnableSoftLimit = Motion_GetSoftLimit(pMapAxis[nIndex], dblSoftLimitNegative, dblSoftLimitPositive);
		if (bEnableSoftLimit) {

			AxmStatusGetCmdPos(pMapAxis[nIndex], &dblCurrentPosition);
			MessageWindow(cDEBUG, _T("MoveNX::SoftLimitNeg = %.2f, SoftLimitPos = %.2f, CurrPos = %.2f"), dblSoftLimitNegative, dblSoftLimitPositive, dblCurrentPosition);
			if (dblCurrentPosition <= dblSoftLimitNegative || dblCurrentPosition >= dblSoftLimitPositive)
				bSoftMode = TRUE;
		}
	}


	/////////////////////////////////////////////////////////////////
	// ��� �̵� ////////////////////////////////////////////////////
	if (bSoftMode) {

		// �Ϲ� �̵�
		for (UINT nIndex = 0; nIndex < nNumAxis; nIndex++)
			Motion_MoveTo(pMapAxis[nIndex], pMapPosition[nIndex], m_stMotionAxisInfo[pMapAxis[nIndex]].dblSpeedBase);

		bOnMessage = FALSE;

	} else {

		// �ϵ���� ������ ����Ͽ� �̵� : ���� �࿡ ����Ʈ ������ �ɷ�������, �ϵ���� ������ �������� ����
		AxmContiBeginNode(lCoord);
		AxmLineMove(lCoord, pMapPosition, dblSpeed, dblAccelTime, dblAccelTime);
		AxmContiEndNode(lCoord);

		DWORD	dwRetCode = AxmContiStart(lCoord, CONTI_NODE_VELOCITY, 0);
		MessageWindow(cDEBUG, _T("MoveNX::AxmContiStart result = %d"), dwRetCode);

		// ���� �̵� ���� �� �Ϲ� �̵�
		if (dwRetCode != AXT_RT_SUCCESS) {
		
			NormalMessage(TRUE, _T("MoveNX:AxmContiStart() Failure! RetCode = %d"), dwRetCode);
			for (UINT nIndex = 0; nIndex < nNumAxis; nIndex++)
				Motion_MoveTo(pMapAxis[nIndex], pMapPosition[nIndex], m_stMotionAxisInfo[pMapAxis[nIndex]].dblSpeedBase);

			bOnMessage = FALSE;
		}
	}

	for (UINT nIndex = 0; nIndex < nNumAxis; nIndex++)
		MessageWindow(cDEBUG, _T("MoveNX[%d] = %.2f"), nIndex, pMapPosition[nIndex]);


	/////////////////////////////////////////////////////////////////
	// �޼��� ��� //////////////////////////////////////////////////
	if (bOnMessage) {

		DOUBLE	dblCmdPos	= 0;
		DOUBLE	dblActPos	= 0;
	
		for (UINT nIndex = 0; nIndex < 2; nIndex++) {

			AxmStatusGetActPos(pMapAxis[nIndex], &dblActPos);
			AxmStatusGetCmdPos(pMapAxis[nIndex], &dblCmdPos);

			NormalMessage(TRUE,	_T("%s::%s, CurrCmdPos=%.2f, CurrActPos=%.2f, DestCmdPos=%.2f, Speed=%.2f"),	
								g_stSystemString[SYSSTR_MOTION_MOVE_START].szDescription[m_nTypeLanguage],
								g_stMotionAxisName[pMapAxis[nIndex]].stDescription.szDescription[m_nTypeLanguage],
								dblCmdPos, dblActPos, pMapPosition[nIndex], dblSpeed);
		}
	}


	/////////////////////////////////////////////////////////////////
	delete []	pMapAxis;
	delete []	pMapPosition;


	return	bResult;	
}


///////////////////////////////////////////////////////////////////////////////
// ��� �̵� �Ϸ� üũ ////////////////////////////////////////////////////////
BOOL CMainApp::Motion_Done(UINT nAxisNo)
{
	DWORD	dwStatus = 0;

	// ��� ���� üũ
	AxmStatusReadInMotion(nAxisNo, &dwStatus);

	return	dwStatus ? FALSE : TRUE;
}

BOOL CMainApp::Motion_DoneAll(void)
{
	BOOL	bResult	= TRUE;

	for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++)
		bResult &= Motion_Done(nAxisNo);


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// ���� ��ġ üũ /////////////////////////////////////////////////////////////
BOOL CMainApp::Motion_CheckSafePosition(UINT nAxisNo, DOUBLE dblPosition)
{
	BOOL	bResult	= FALSE;


	if ((m_stMotionAxisInfo[nAxisNo].dblSafePositionMIN == 0 && m_stMotionAxisInfo[nAxisNo].dblSafePositionMAX == 0) ||
		(m_stMotionAxisInfo[nAxisNo].dblSafePositionMIN <= dblPosition && m_stMotionAxisInfo[nAxisNo].dblSafePositionMAX >= dblPosition)) {

			bResult = TRUE;
	}


	return	bResult;
}

BOOL CMainApp::Motion_CheckSafePosition(UINT nAxisNo, BOOL bIsMIN /* = TRUE */, BOOL bIsMAX /* = TRUE */)
{
	BOOL	bResult				= TRUE;
	DOUBLE	dblMotorPosition	= 0;


	AxmStatusGetCmdPos(nAxisNo, &dblMotorPosition);

	if (m_stMotionAxisInfo[nAxisNo].dblSafePositionMIN == 0 && m_stMotionAxisInfo[nAxisNo].dblSafePositionMAX == 0)
		return	bResult;

	if (bIsMIN)		bResult	&= (m_stMotionAxisInfo[nAxisNo].dblSafePositionMIN <= dblMotorPosition) ? TRUE : FALSE;
	if (bIsMAX)		bResult	&= (m_stMotionAxisInfo[nAxisNo].dblSafePositionMAX >= dblMotorPosition) ? TRUE : FALSE;


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// Ŀ���� ��ġ üũ ///////////////////////////////////////////////////////////
BOOL CMainApp::Motion_CheckCustomPosition(UINT nPosition)
{
	BOOL	bResult				= TRUE;
	DOUBLE	dblOffset			= 0;
	DOUBLE	dblMotorPosition	= 0;


	for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++) {

		AxmStatusGetCmdPos(nAxisNo, &dblMotorPosition);
		dblOffset	= dblMotorPosition - m_stMotionAxisInfo[nAxisNo].dblCustomPosition[nPosition];

		// 0.02mm ������ ����
		if (abs(dblOffset) > 0.02) {

			bResult = FALSE;
			break;
		}
	}


	return	bResult;
}

BOOL CMainApp::Motion_CheckCustomPosition(UINT nAxisNo, DOUBLE dblPosition, DOUBLE dblTolerance /* = 0.01 */)
{
	BOOL	bResult			= TRUE;
	DOUBLE	dblOffset		= 0;
	DOUBLE	dblMotorCmdPos	= 0;
	DOUBLE	dblMotorActPos	= 0;


	// Ŀ�ǵ� ��ġ
	AxmStatusGetCmdPos(nAxisNo, &dblMotorCmdPos);

	// ���ڴ� ��ġ
	AxmStatusGetActPos(nAxisNo, &dblMotorActPos);

	// ������
	dblOffset = dblMotorActPos - dblPosition;

	// ������ ����
	if (abs(dblOffset) > dblTolerance) {

		NormalMessage(TRUE, _T("Motion_CheckCustomPosition:: AxisNo = %d, dblPosition = %.2f, CommandPos = %.2f, ActualPos = %.2f, dblOffset = %.2f"), nAxisNo + 1, dblPosition, dblMotorCmdPos, dblMotorActPos, dblOffset);

		bResult = FALSE;
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// ��-������ üũ /////////////////////////////////////////////////////////////
BOOL CMainApp::Motion_CheckInPosition(UINT nAxisNo, DOUBLE dblPositionMIN, DOUBLE dblPositionMAX)
{
	BOOL	bResult				= FALSE;
	DOUBLE	dblMotorPosition	= 0;


	AxmStatusGetCmdPos(nAxisNo, &dblMotorPosition);

	if (dblPositionMIN <= dblMotorPosition && dblPositionMAX >= dblMotorPosition) {

		bResult = TRUE;
	}


	return	bResult;
}

BOOL CMainApp::Motion_CheckInPosition(UINT nAxisNo, DOUBLE dblMotorPosition, DOUBLE dblPositionMIN, DOUBLE dblPositionMAX)
{
	BOOL	bResult	= FALSE;

	if (dblPositionMIN <= dblMotorPosition && dblPositionMAX >= dblMotorPosition) {

		bResult = TRUE;
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// ���� ���� üũ /////////////////////////////////////////////////////////////
BOOL CMainApp::Motion_CheckStopStatus(UINT nAxisNo, DOUBLE dblDestPosition, BOOL bOnMessage /* = TRUE */, DWORD* pStatus /* = NULL */)
{
	BOOL		bResult			= TRUE;
	UINT		nRetryCount		= 0;
	DWORD		dwStatusEnd		= 0;
	DWORD		dwRetCode		= 0;
	DOUBLE		dblCmdPos		= 0;
	DOUBLE		dblActPos		= 0;
	DOUBLE		dblOffsetEnc	= 0;
	DOUBLE		dblOffsetPos	= 0;


	/////////////////////////////////////////////////////////////////
	// ���� ���� üũ ///////////////////////////////////////////////
	dwRetCode = AxmStatusReadStop(nAxisNo, &dwStatusEnd);
	
	if (pStatus)	*pStatus = dwStatusEnd;


	/////////////////////////////////////////////////////////////////
	// ��ġ ���е� üũ /////////////////////////////////////////////
	do {

		bResult = TRUE;

		// ��ġ üũ
		AxmStatusGetActPos(nAxisNo, &dblActPos);
		AxmStatusGetCmdPos(nAxisNo, &dblCmdPos);

		// �ܺ�/���� ���ڴ� üũ
		dblOffsetEnc = dblActPos - dblCmdPos;
		//if (abs(dblOffsetEnc) > 5.0)	bResult = FALSE;

		// ��ǥ ��ġ üũ
		dblOffsetPos = dblDestPosition - dblCmdPos;
		if (abs(dblOffsetPos) > 1.0)	bResult = FALSE;

	} while (!bResult && ++nRetryCount <= MAX_RETRY_DEVICE);


	/////////////////////////////////////////////////////////////////
	// �޼��� ��� //////////////////////////////////////////////////
	if (bOnMessage) {

		NormalMessage(TRUE,	_T("%s::%s, CurrCmdPos=%.2f, CurrActPos=%.2f, Status=%d(%X), OffsetEnc=%.2f, OffsetPos=%.2f"),	
							g_stSystemString[SYSSTR_MOTION_MOVE_STOP].szDescription[m_nTypeLanguage],
							g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
							dblCmdPos, dblActPos, dwStatusEnd, dwStatusEnd,
							dblOffsetEnc, dblOffsetPos);
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// ����Ʈ ����Ʈ ���� /////////////////////////////////////////////////////////
void CMainApp::Motion_SetSoftLimit(UINT nAxisNo, BOOL bEnable /* = TRUE */)
{
	DWORD	dwEnable			= bEnable ? ENABLE : DISABLE;
	DOUBLE	dblLimitNegativePos	= m_stMotionAxisInfo[nAxisNo].dblLimitNegativePos;
	DOUBLE	dblLimitPositivePos	= m_stMotionAxisInfo[nAxisNo].dblLimitPositivePos;

	if (dblLimitNegativePos == 0 && dblLimitPositivePos == 0)
		dwEnable = DISABLE;

	AxmSignalSetSoftLimit(	nAxisNo, 
							dwEnable, 
							EMERGENCY_STOP,
							COMMAND,
							dblLimitPositivePos, 
							dblLimitNegativePos);

	MessageWindow(cDEBUG, _T("[AXIS:%d] SoftLimit=%d, Pos=%.2f, Neg=%.2f"), nAxisNo + 1, dwEnable, m_stMotionAxisInfo[nAxisNo].dblLimitPositivePos, m_stMotionAxisInfo[nAxisNo].dblLimitNegativePos);
}

void CMainApp::Motion_SetSoftLimit(UINT nAxisNo, DOUBLE dblLimitNegativePos, DOUBLE dblLimitPositivePos)
{
	DWORD	dwEnable = ENABLE;

	if (dblLimitNegativePos == 0 && dblLimitPositivePos == 0)
		dwEnable = DISABLE;

	AxmSignalSetSoftLimit(	nAxisNo, 
							dwEnable, 
							EMERGENCY_STOP, 
							COMMAND,
							dblLimitPositivePos, 
							dblLimitNegativePos);

	MessageWindow(cDEBUG, _T("[AXIS:%d] SoftLimit=%d, Pos=%.2f, Neg=%.2f"), nAxisNo + 1, dwEnable, dblLimitPositivePos, dblLimitNegativePos);
}

BOOL CMainApp::Motion_GetSoftLimit(UINT nAxisNo, DOUBLE& dblLimitNegativePos, DOUBLE& dblLimitPositivePos)
{
	DWORD	dwStatus				= 0;
	DOUBLE	dblSoftLimitPositive	= 0;
	DOUBLE	dblSoftLimitNegative	= 0;


	AxmSignalGetSoftLimit(nAxisNo, &dwStatus, NULL, NULL, &dblSoftLimitPositive, &dblSoftLimitNegative);
	dblLimitNegativePos = dblSoftLimitNegative;
	dblLimitPositivePos = dblSoftLimitPositive;

	MessageWindow(cDEBUG, _T("[AXIS:%d] SoftLimit=%d(%08X), Pos=%.2f, Neg=%.2f"), nAxisNo + 1, dwStatus, dwStatus, dblLimitPositivePos, dblLimitNegativePos);


	return	dwStatus ? TRUE : FALSE;
}


///////////////////////////////////////////////////////////////////////////////
// ��� �ñ׳� �̺�Ʈ ���� ////////////////////////////////////////////////////
//																			 //
// nAxisNo    : �� ��ȣ														 //
// nSignalNo  : �Է� �ñ׳� ��ȣ (0 ~ 4)									 //
// nTypeEdge  : ���� ���� ���� (SIGNAL_DOWN_EDGE, SIGNAL_UP_EDGE)			 //
// nTypeCount : ��ġ ī���� ���� (0 = Command, 1 = Actual)					 //
///////////////////////////////////////////////////////////////////////////////
BOOL CMainApp::Motion_SignalEventPositionStart(UINT nAxisNo, UINT nSignalNo, UINT nTypeEdge, UINT nTypeCount)
{
	DWORD	dwEvent		= 0;
	DWORD	dwCommand	= 0;
	LONG	lAxisQI		= (LONG)nAxisNo % 4;


	/////////////////////////////////////////////////////////////////
	// �Ķ���� üũ ////////////////////////////////////////////////
	if (nSignalNo > 4)				return	FALSE;
	if (nTypeEdge > SIGNAL_UP_EDGE)	return	FALSE;
	if (nTypeCount > 1)				return	FALSE;


	/////////////////////////////////////////////////////////////////
	// �̺�Ʈ ���� //////////////////////////////////////////////////
	switch (nSignalNo) {
	
		case	0	:	dwEvent = nTypeEdge == SIGNAL_UP_EDGE ? EVENT_QIUIO5RISING : EVENT_QIUIO5FALLING;	break;
		case	1	:	dwEvent = nTypeEdge == SIGNAL_UP_EDGE ? EVENT_QIUIO6RISING : EVENT_QIUIO6FALLING;	break;
		case	2	:	dwEvent = nTypeEdge == SIGNAL_UP_EDGE ? EVENT_QIUIO7RISING : EVENT_QIUIO7FALLING;	break;
		case	3	:	dwEvent = nTypeEdge == SIGNAL_UP_EDGE ? EVENT_QIUIO8RISING : EVENT_QIUIO8FALLING;	break;
		case	4	:	dwEvent = nTypeEdge == SIGNAL_UP_EDGE ? EVENT_QIUIO9RISING : EVENT_QIUIO9FALLING;	break;
	}


	/////////////////////////////////////////////////////////////////
	// Ŀ�ǵ� ���� //////////////////////////////////////////////////
	dwCommand = nTypeCount ? QiCNT2Read : QiCNT1Read;

	switch (lAxisQI) {
	
		case	0	:	dwCommand = dwCommand + (QiNoOperation_0C << 8) + (QiNoOperation_0C << 16) + (QiNoOperation_0C << 24);	break;
		case	1	:	dwCommand = QiNoOperation_0C + (dwCommand << 8) + (QiNoOperation_0C << 16) + (QiNoOperation_0C << 24);	break;
		case	2	:	dwCommand = QiNoOperation_0C + (QiNoOperation_0C << 8) + (dwCommand << 16) + (QiNoOperation_0C << 24);	break;
		case	3	:	dwCommand = QiNoOperation_0C + (QiNoOperation_0C << 8) + (QiNoOperation_0C << 16) + (dwCommand << 24);	break;
		default		:	return	FALSE;
	}


	/////////////////////////////////////////////////////////////////
	AxmSetCommandData32Qi(nAxisNo, QiSCRCMD4Write, dwCommand);

	dwEvent += (EVENT_QIBUSY << 8) + (lAxisQI << 16) + (lAxisQI << 18) + (0x01 << 20) + (0 << 22) + (0 << 23) + (0 << 24);
	AxmSetCommandData32Qi(nAxisNo, QiSCRCON4Write, dwEvent);


	return	TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// ��� �ñ׳� �̺�Ʈ ��� ////////////////////////////////////////////////////
BOOL CMainApp::Motion_SignalEventPositionStop(UINT nAxisNo)
{
	DWORD dwData;

	AxmGetCommandData32Qi(nAxisNo, QiCQ4Read, &dwData);
	AxmSetCommandData32Qi(nAxisNo, QiINITSQWrite, 0x0008);

	return	TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// ��� �ñ׳� �̺�Ʈ ��ġ �б� ///////////////////////////////////////////////
BOOL CMainApp::Motion_SignalEvantReadPosition(UINT nAxisNo, DOUBLE* pPosition)
{
	BOOL	bResult	= FALSE;
	DWORD	dwData;
	DOUBLE	dblUnit;
	LONG	lPulse;


	if (pPosition != NULL) {

		AxmGetCommandData32Qi(nAxisNo, QiCQ4Read, &dwData);
		AxmMotGetMoveUnitPerPulse(nAxisNo, &dblUnit, &lPulse);

		*pPosition	= (double)((long)dwData) * dblUnit / (double)lPulse;
		bResult		= TRUE;
	}

	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// ��� �ñ׳� �̺�Ʈ ���� üũ ///////////////////////////////////////////////
BOOL CMainApp::Motion_SignalEventReadStatus(UINT nAxisNo, PINT pStatus)
{
	BOOL	bResult	= FALSE;
	DWORD	dwData;
	DWORD	dwStatus;


	if (pStatus != NULL) {
	
		AxmGetCommandData32Qi(nAxisNo, QiSCRSTAT1Read, &dwData);

		dwStatus = dwData & 0xF000;
		switch (dwStatus) {
		
			case	0x5000	:	*pStatus = MSE_RESULT_NONE;		break;
			case	0x6000	:	*pStatus = MSE_RESULT_READY;	break;
			case	0x9000	:	*pStatus = MSE_RESULT_DETECT;	break;
			default			:	*pStatus = MSE_RESULT_ERROR;	break;
		}
	}

	return	bResult;
}







///////////////////////////////////////////////////////////////////////////////////////////////////
// ���� �˻� ���� /////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// MIL �ʱ�ȭ /////////////////////////////////////////////////////////////////
BOOL CMainApp::MatroxInitialize(void)
{
	SYSTEM_CONFIG_T	stSystemConfig	= m_SystemConfig.GetSystemConfig();
	BOOL			bResult			= TRUE;
	CFileFind		fileFinder;


	/////////////////////////////////////////////////////////////////
	// MIL �ʱ�ȭ ///////////////////////////////////////////////////
	try {

		/////////////////////////////////////////////////////////////
		// ���ø����̼� �ʱ�ȭ //////////////////////////////////////
		MappAlloc(M_DEFAULT, &m_MilApplication);
		if (m_MilApplication == M_NULL)	throw -1;


		/////////////////////////////////////////////////////////////
		// �ý��� �ʱ�ȭ ////////////////////////////////////////////
		MsysAlloc(stSystemConfig.szVisionSystemName, M_DEF_SYSTEM_NUM, M_COMPLETE, &m_MilSystem);
		if (m_MilSystem == M_NULL)		throw -1;


		/////////////////////////////////////////////////////////////
		// ����Ÿ���� �ʱ�ȭ ////////////////////////////////////////
		CString		strFileDCF	= _T("");

		m_MilNumberOfDigitizer = MsysInquire(m_MilSystem, M_DIGITIZER_NUM, NULL);
		if (m_MilNumberOfDigitizer && m_MilNumberOfDigitizer >= MAX_VISION_CHANNEL) {

			for (UINT nDigIndex = 0; nDigIndex < MAX_VISION_CHANNEL; nDigIndex++) {

				// DCF ���� ����
				if (fileFinder.FindFile(stSystemConfig.szVisionCameraDCF[nDigIndex]))	strFileDCF.Format(_T("%s"), stSystemConfig.szVisionCameraDCF[nDigIndex]);
				else																	strFileDCF = _T("M_DEFAULT");

				// ����Ÿ���� ����
				MdigAlloc(m_MilSystem, M_DEV0 + stSystemConfig.nVisionDigitizerNo + nDigIndex, (MIL_TEXT_CHAR*)(LPCTSTR)strFileDCF, M_DEFAULT, &m_MilDigitizer[nDigIndex]);
				if (m_MilDigitizer[nDigIndex] == NULL)	throw -1;

				MdigInquire(m_MilDigitizer[nDigIndex], M_SIZE_X, &m_sizeFrame[nDigIndex].cx);
				MdigInquire(m_MilDigitizer[nDigIndex], M_SIZE_Y, &m_sizeFrame[nDigIndex].cy);
				MdigInquire(m_MilDigitizer[nDigIndex], M_SIZE_BAND, &m_MilDigitizerNbBands);

				if (m_sizeFrame[nDigIndex].cx > M_DEF_IMAGE_SIZE_X_MAX)		m_sizeFrame[nDigIndex].cx	= M_DEF_IMAGE_SIZE_X_MAX;
				if (m_sizeFrame[nDigIndex].cy > M_DEF_IMAGE_SIZE_Y_MAX) 	m_sizeFrame[nDigIndex].cy	= M_DEF_IMAGE_SIZE_Y_MAX;
			}

		} else {

			if (m_nTypeLanguage == LANGUAGE_KOR)	SErrorMessage(FALSE, _T("��Ʈ�Ͻ� ����Ÿ������ ������ �� �����ϴ�."));
			else									SErrorMessage(FALSE, _T("Can NOT Create Matrox Digitizer"));

			m_MilDigitizer[VISION_CH1]	= M_NULL;

			m_sizeFrame[VISION_CH1].cx	= M_DEF_IMAGE_SIZE_X_MAX;
			m_sizeFrame[VISION_CH1].cy	= M_DEF_IMAGE_SIZE_Y_MAX;
		}


		/////////////////////////////////////////////////////////////
		// MIL ���� �޼��� Ȱ��ȭ ///////////////////////////////////
		MappControl(M_ERROR, stSystemConfig.bOnVisionMessageDisplay ? M_PRINT_ENABLE : M_PRINT_DISABLE);


	/////////////////////////////////////////////////////////////////
	// MIL �ʱ�ȭ ���� //////////////////////////////////////////////
	} catch (...) {

		MatroxRelease();
		bResult = FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// �޼��� ��� //////////////////////////////////////////////////
	if (!bResult) {

		if (m_nTypeLanguage == LANGUAGE_KOR)	SErrorMessage(FALSE, _T("��Ʈ�Ͻ� �̹��� ���̺귯���� �ʱ�ȭ�� �� �����ϴ�."));
		else									SErrorMessage(FALSE, _T("Matrox Image Library Initialize Failure!!"));
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// MIL ������ /////////////////////////////////////////////////////////////////
void CMainApp::MatroxRelease(void)
{
	for (UINT nIndex = 0; nIndex < MAX_TEST_SHEET; nIndex++) {

		if (m_MilImageInspection[nIndex] != M_NULL)		{ MbufFree(m_MilImageInspection[nIndex]);	m_MilImageInspection[nIndex] = NULL; }
	}

	for (UINT nVisionCH = 0; nVisionCH < MAX_VISION_CHANNEL; nVisionCH++) {

		if (m_MilImageGrab[nVisionCH] != M_NULL)		{ MbufFree(m_MilImageGrab[nVisionCH]);		m_MilImageGrab[nVisionCH] = NULL; }		// Release MIL Image Buffer
		if (m_MilDigitizer[nVisionCH] != M_NULL)		{ MdigFree(m_MilDigitizer[nVisionCH]);		m_MilDigitizer[nVisionCH] = NULL; }		// Release MIL Digitizer
	}

	if (m_MilSystem != M_NULL)			{ MsysFree(m_MilSystem);		m_MilSystem      = NULL; }			// Release MIL System
	if (m_MilApplication != M_NULL)		{ MappFree(m_MilApplication);	m_MilApplication = NULL; }			// Release MIL Application
}


///////////////////////////////////////////////////////////////////////////////
// ���� �̹��� ĸ�� ///////////////////////////////////////////////////////////
BOOL CMainApp::GrabVisionImage(UINT nVisionCH, UINT nTestItemNo)
{
	BOOL	bResult		= FALSE;


	/////////////////////////////////////////////////////////////////
	// ũ��Ƽ�� ���� ���� ///////////////////////////////////////////
	m_csDigitizerGrabImage[nVisionCH].Lock();


	/////////////////////////////////////////////////////////////////
	// �̹��� ���� �ʱ�ȭ //////////////////////////////////////
	if (m_MilImageGrab[nVisionCH] != M_NULL) {

		MbufFree(m_MilImageGrab[nVisionCH]);
		m_MilImageGrab[nVisionCH] = M_NULL;
	}

	if (m_MilImageInspection[nTestItemNo] != M_NULL) {

		MbufFree(m_MilImageInspection[nTestItemNo]);
		m_MilImageInspection[nTestItemNo] = M_NULL;
	}


	/////////////////////////////////////////////////////////////////
	// MIL ���� ������ �̹��� ĸ�� ////////////////////////////////
	if (theApp.m_pMilVideoWnd[nVisionCH]) {

		if (theApp.m_pMilVideoWnd[nVisionCH]->TakeGrabImageBuffer(&m_MilImageGrab[nVisionCH])) {

			/////////////////////////////////////////////////////////
			// �˻� �̹��� ���� ���� ////////////////////////////////
			MbufAllocColor(	m_MilSystem, 
							m_MilDigitizerNbBands, 
							m_sizeFrame[nVisionCH].cx, 
							m_sizeFrame[nVisionCH].cy, 
							(8 + M_UNSIGNED), 
							M_IMAGE + M_DISP + M_PROC, 
							&m_MilImageInspection[nTestItemNo]);


			/////////////////////////////////////////////////////////
			// �˻� �̹��� ���ۿ� ���� //////////////////////////////
			if (m_MilImageInspection[nTestItemNo] != M_NULL) {

				MbufClear(m_MilImageInspection[nTestItemNo], M_NULL);
				MbufCopy(m_MilImageGrab[nVisionCH], m_MilImageInspection[nTestItemNo]);

				bResult = TRUE;
			
			} else {

				SErrorMessage(TRUE, _T("INSPECTION IMAGE BUFFER ALLOCATION FAILURE!!"));
			}
		
		} else {

			SErrorMessage(TRUE, _T("CAM IMAGE BUFFER ALLOCATION FAILURE!!"));
		}
	}


	/////////////////////////////////////////////////////////////////
	// ũ��Ƽ�� ���� ���� ///////////////////////////////////////////
	m_csDigitizerGrabImage[nVisionCH].Unlock();


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// ���� �̹��� ���� ///////////////////////////////////////////////////////////
BOOL CMainApp::SaveVisionImage(UINT nTestItemNo, BOOL bGrayScale /* = TRUE */, BOOL bIsJPEG /* = FALSE */, BOOL bIsCommon /* = FALSE */)
{
	BOOL						bResult				= TRUE;
	MIL_INT						MilFileFormat		= bIsJPEG ? M_JPEG_LOSSY : M_BMP;

	CString						strFileName			= _T("");
	CString						strReturnFileName	= _T("");
	CString						strDirSave			= _T("");
	CString						strDirectory		= _T("");
	CFileFind					fileFinder;

	DPS_DISK_INFO_T				stDiskInfo;
	DPS_PRODUCTION_V2_INFO_T	stProductionInfo	= m_pProductionWnd->GetProductionInfo();
	SYSTEM_CONFIG_T				stSystemConfig		= m_SystemConfig.GetSystemConfig();
	PMODEL_PROFILE_T			pstModelProfile		= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
	PWORK_STATUS_T				pstWorkStatus		= GetWorkStatus(STATION_1);


	/////////////////////////////////////////////////////////////////
	// ��ũ �뷮 üũ /////////////////////////////////////////////
	if (DPS_GetDiskInfo(DPS_GetCurrentAppDirectory(), stDiskInfo)) {

		ULONGLONG	ulFreeSize_MB = stDiskInfo.ulDiskFreeSize / 1024 / 1024;

		// ��ũ �뷮�� 100MB �̸��̸�,
		if (ulFreeSize_MB <= 100) {

			if (m_nTypeLanguage == LANGUAGE_KOR)	SErrorMessage(TRUE, _T("��ũ �뷮�� �����Ͽ� ���� �̹����� ������ �� �����ϴ�. [���� ���� = %luMB]"), ulFreeSize_MB);
			else									SErrorMessage(TRUE, _T("Disk is FULL!! Can NOT Save Vision Image [Free Space = %luMB]"), ulFreeSize_MB);

			return	FALSE;
		}
	
	} else {

		if (m_nTypeLanguage == LANGUAGE_KOR)	SErrorMessage(TRUE, _T("��ũ ������ �ε��� �� �����ϴ�."));
		else									SErrorMessage(TRUE, _T("Can NOT Load Disk Information"));

		return	FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// ���� �̸� ���� ///////////////////////////////////////////////
	if (bIsCommon) {

		// ���� ���丮 ����
		strDirSave = m_SystemConfig.GetWorkDirectory(DIR_WORK_PROCEDURE);

		// �� ���丮 ����
		strDirectory.Format(_T("%s\\%s"), strDirSave, DPS_GetFileInfo(stSystemConfig.szLastModelFile).szFileName);
		CreateDirectory(strDirectory, NULL);
	
	} else {

		strDirectory = pstWorkStatus->szWorkDataSaveDirectory;
	}

	// ���� �̸� ����
	strFileName.Format(_T("%s\\[T%02d] Inspection Image"), strDirectory, nTestItemNo + 1);

	// ���� Ȯ���� ����
	if (bIsJPEG)	strFileName.AppendFormat(_T(".JPG"));
	else			strFileName.AppendFormat(_T(".BMP"));


	/////////////////////////////////////////////////////////////////
	// �̹��� ���� //////////////////////////////////////////////////
	if (!fileFinder.FindFile(strFileName)) {

		fileFinder.Close();

		MIL_ID		MilImageLuminance		= M_NULL;
		MIL_INT		MilSizeBand				= 0;
		MIL_INT64	MilBufferAttributes		= M_IMAGE + M_PROC;
		CSize		sizeImage;

		if (bGrayScale) {

			MbufInquire(m_MilImageInspection[nTestItemNo], M_SIZE_BAND, &MilSizeBand);
			MbufInquire(m_MilImageInspection[nTestItemNo], M_SIZE_X, &sizeImage.cx);
			MbufInquire(m_MilImageInspection[nTestItemNo], M_SIZE_Y, &sizeImage.cy);

			if (MilSizeBand == MIL_BAND_RGB) {
					
				MbufAllocColor(m_MilSystem, MIL_BAND_GRAY, sizeImage.cx, sizeImage.cy, (8 + M_UNSIGNED), MilBufferAttributes, &MilImageLuminance);
				if (MilImageLuminance != M_NULL) {

					MimConvert(m_MilImageInspection[nTestItemNo], MilImageLuminance, M_RGB_TO_L);
					MbufExport(strFileName, MilFileFormat, MilImageLuminance);
					MbufFree(MilImageLuminance);

					return	TRUE;
				}
			}
		}

		MbufExport(strFileName, MilFileFormat, m_MilImageInspection[nTestItemNo]);
		MessageWindow(cDEBUG, _T("Save Vision Image : %s"), strFileName);
	}


	return	TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// ���� ī�޶� Ŀ�ǵ� : �Ķ���� ���� /////////////////////////////////////////
BOOL CMainApp::SaveVisionCameraParameters(UINT nVisionCH, UINT nChannelNo)
{
	CComm*		pComm		= GetComm(COMM_DEV_CAM);
	BYTE		byReadByte	= 0;
	UINT		nCommIndex	= 0;
	TCHAR		szReadBuffer[COMM_PACKET_SIZE];
	LTimerMsec	LTimerTimeOut;


	/////////////////////////////////////////////////////////////////
	// Ŀ�ǵ� ���� //////////////////////////////////////////////////
	while (pComm->ReadByte(&byReadByte));
	pComm->TransmitString(FALSE, _T("USERSET-SAVE %d\r"), nChannelNo);
	DPS_Delay_ms(2000);
	LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_VISION_CAMERA));


	/////////////////////////////////////////////////////////////////
	// ���� ���� ////////////////////////////////////////////////////
	ZeroMemory(szReadBuffer, sizeof(TCHAR) * COMM_PACKET_SIZE);
	while (!LTimerTimeOut.Verify()) {

		while (pComm->ReadByte(&byReadByte)) {

			szReadBuffer[nCommIndex++]	= byReadByte;
			if (byReadByte == 0x0D) {

				// CR + LF ���� ����
				szReadBuffer[nCommIndex - 1] = '\0';
				nCommIndex = 0;

				// ������ �м�
				if (CString(szReadBuffer).Find(_T("OK")) >= 0)
					return	TRUE;
			}

			if (nCommIndex >= COMM_PACKET_SIZE)	{

				nCommIndex = 0;
				break;
			}
		}

		Sleep(1);
	}

	return	FALSE;
}


///////////////////////////////////////////////////////////////////////////////
// ���� ī�޶� Ŀ�ǵ� : �Ķ���� �ε� /////////////////////////////////////////
BOOL CMainApp::LoadVisionCameraParameters(UINT nVisionCH, UINT nChannelNo)
{
	CComm*		pComm		= GetComm(COMM_DEV_CAM);
	BYTE		byReadByte	= 0;
	UINT		nCommIndex	= 0;
	TCHAR		szReadBuffer[COMM_PACKET_SIZE];
	LTimerMsec	LTimerTimeOut;


	/////////////////////////////////////////////////////////////////
	// Ŀ�ǵ� ���� //////////////////////////////////////////////////
	while (pComm->ReadByte(&byReadByte));
	pComm->TransmitString(FALSE, _T("USERSET-LOAD %d\r"), nChannelNo);
	LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_VISION_CAMERA));


	/////////////////////////////////////////////////////////////////
	// ���� ���� ////////////////////////////////////////////////////
	ZeroMemory(szReadBuffer, sizeof(TCHAR) * COMM_PACKET_SIZE);
	while (!LTimerTimeOut.Verify()) {

		while (pComm->ReadByte(&byReadByte)) {

			szReadBuffer[nCommIndex++]	= byReadByte;
			if (byReadByte == 0x0D) {

				// CR + LF ���� ����
				szReadBuffer[nCommIndex - 1] = '\0';
				nCommIndex = 0;

				// ������ �м�
				if (CString(szReadBuffer).Find(_T("OK")) >= 0)
					return	TRUE;
			}

			if (nCommIndex >= COMM_PACKET_SIZE)	{

				nCommIndex = 0;
				break;
			}
		}

		Sleep(1);
	}

	return	FALSE;
}


///////////////////////////////////////////////////////////////////////////////
// ���� ī�޶� Ŀ�ǵ� : �ڵ� ȭ��Ʈ �뷱�� ////////////////////////////////////
BOOL CMainApp::SetVisionCameraAutoWhiteBalance(UINT nVisionCH, UINT nValue)
{
	CComm*		pComm		= GetComm(COMM_DEV_CAM);
	BYTE		byReadByte	= 0;
	UINT		nCommIndex	= 0;
	TCHAR		szReadBuffer[COMM_PACKET_SIZE];
	LTimerMsec	LTimerTimeOut;


	/////////////////////////////////////////////////////////////////
	// Ŀ�ǵ� ���� //////////////////////////////////////////////////
	while (pComm->ReadByte(&byReadByte));
	pComm->TransmitString(FALSE, _T("WHITEBALANCE-AUTO %d\r"), nValue);
	DPS_Delay_ms(2000);
	LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_VISION_CAMERA));


	/////////////////////////////////////////////////////////////////
	// ���� ���� ////////////////////////////////////////////////////
	ZeroMemory(szReadBuffer, sizeof(TCHAR) * COMM_PACKET_SIZE);
	while (!LTimerTimeOut.Verify()) {

		while (pComm->ReadByte(&byReadByte)) {

			szReadBuffer[nCommIndex++]	= byReadByte;
			if (byReadByte == 0x0D) {

				// CR + LF ���� ����
				szReadBuffer[nCommIndex - 1] = '\0';
				nCommIndex = 0;

				// ������ �м�
				if (CString(szReadBuffer).Find(_T("OK")) >= 0)
					return	TRUE;
			}

			if (nCommIndex >= COMM_PACKET_SIZE) {

				nCommIndex = 0;
				break;
			}
		}

		Sleep(1);
	}

	return	FALSE;
}


///////////////////////////////////////////////////////////////////////////////
// ���� ī�޶� Ŀ�ǵ� : ���� ���� /////////////////////////////////////////////
BOOL CMainApp::SetVisionCameraExposure(UINT nVisionCH, UINT nValue)
{
	BYTE	byReadByte;

	while (m_Comm[COMM_DEV_CAM].ReadByte(&byReadByte));
	m_Comm[COMM_DEV_CAM].TransmitString(FALSE, _T("EXP %d\r"), nValue);

	return	TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// �̹��� ���μ��� : THRESHOLD ////////////////////////////////////////////////
BOOL CMainApp::ProcessImage_Threshold(UINT nTestItemNo, UINT nTestStationNo, DPS_POINT2D_T stOriginOffset, VI_PARAM_THRESHOLD_T& stParam, VI_RESULT_THRESHOLD_T& stResult, BOOL bSaveClip /* = TRUE */)
{
	BOOL			bResultProcess		= TRUE;

	MIL_ID			MilImageInspection	= M_NULL;
	MIL_ID			MilImageGrayScale	= M_NULL;
	MIL_ID			MilImageThreshold	= M_NULL;

	MIL_ID			MilHistResult		= M_NULL;
	MIL_INT			HistValues[DMW_HIST_NUM_INTENSITIES];

	MIL_INT			MilSizeBand			= 0;
	MIL_INT64		MilBufferAttributes	= M_IMAGE + M_PROC;
	SIZE			sizeImage;
	DPS_RECT_T		rectInspectionRegion;

	DWORD			dwTimeProcess		= GetTickCount();
	UINT			nResultInspection	= T_RESULT_NONE;
	PWORK_STATUS_T	pstWorkStatus		= GetWorkStatus(nTestStationNo);


	/////////////////////////////////////////////////////////////////
	// �ʱ�ȭ ///////////////////////////////////////////////////////
	ZeroMemory(&stResult, sizeof(VI_RESULT_THRESHOLD_T));

	stResult.nResultInspection = T_RESULT_ERROR;


	/////////////////////////////////////////////////////////////////
	// �Ķ���� �ε� ////////////////////////////////////////////////
	rectInspectionRegion	= stParam.rectInspectionArea;


	/////////////////////////////////////////////////////////////////
	// �˻� �̹��� ���� ���� ////////////////////////////////////////
	MbufChild2d(stParam.MilImageInspection, 
				rectInspectionRegion.ptTopLeft.x + (INT)stOriginOffset.dblX,
				rectInspectionRegion.ptTopLeft.y + (INT)stOriginOffset.dblY,
				rectInspectionRegion.sizeRect.cx,
				rectInspectionRegion.sizeRect.cy,
				&MilImageInspection);

	if (MilImageInspection == M_NULL)		bResultProcess = FALSE;


	/////////////////////////////////////////////////////////////////
	// �׷��� ������ �̹��� ���� ���� ///////////////////////////////
	if (bResultProcess) {
	
		MbufInquire(MilImageInspection, M_SIZE_BAND, &MilSizeBand);
		MbufInquire(MilImageInspection, M_SIZE_X, &sizeImage.cx);
		MbufInquire(MilImageInspection, M_SIZE_Y, &sizeImage.cy);

		MbufAllocColor(m_MilSystem, MIL_BAND_GRAY, sizeImage.cx, sizeImage.cy, (8 + M_UNSIGNED), MilBufferAttributes, &MilImageGrayScale);
		if (MilImageGrayScale == M_NULL)	bResultProcess = FALSE;
		else {
		
			if (MilSizeBand == MIL_BAND_RGB) {

				UINT	nTypeGrayScale = DMW_IP_GRAY_DEFAULT + stParam.stInspectionInfo.stThresholdInfo.nTypeGrayscale;

				if (nTypeGrayScale == DMW_IP_GRAY_DEFAULT) {
				
					MimConvert(MilImageInspection, MilImageGrayScale, M_RGB_TO_L);

				} else {

					MIL_INT		MilBand	= 0;

					switch (nTypeGrayScale) {
					
						case	DMW_IP_GRAY_RED		:	MilBand = M_RED;	break;
						case	DMW_IP_GRAY_GREEN	:	MilBand = M_GREEN;	break;
						case	DMW_IP_GRAY_BLUE	:	MilBand = M_BLUE;	break;
					}

					MbufCopyColor(MilImageInspection, MilImageGrayScale, MilBand);
				}

			} else {
				
				MbufCopy(MilImageInspection, MilImageGrayScale);
			}
		}
	}

	
	/////////////////////////////////////////////////////////////////
	// THRESHOLD �̹��� ���� ���� ///////////////////////////////////
	if (bResultProcess) {

		MbufAllocColor(m_MilSystem, MIL_BAND_GRAY, sizeImage.cx, sizeImage.cy, (8 + M_UNSIGNED), MilBufferAttributes, &MilImageThreshold);
		if (MilImageThreshold == M_NULL)	bResultProcess = FALSE;;
	}


	/////////////////////////////////////////////////////////////////
	// �̹��� ��ȯ //////////////////////////////////////////////////
	if (bResultProcess) {

		// THRESHOLD ��ȯ
		MbufClear(MilImageThreshold, M_NULL);
		CDpsMilImageWnd::ConvertBinarize(MilImageGrayScale, MilImageThreshold, stParam.stInspectionInfo.stThresholdInfo);

		// �̹��� ����
		if (stParam.stInspectionInfo.bInvertImage)	CDpsMilImageWnd::InvertImage(MilImageThreshold);

		// �̼� ���� ����
		CDpsMilImageWnd::RemoveParticles(MilImageThreshold, MilImageThreshold, stParam.stInspectionInfo.nParticleRadius, M_BINARY);
	}

	
	/////////////////////////////////////////////////////////////////
	// ������׷� ���� //////////////////////////////////////////////
	if (bResultProcess) {

		MimAllocResult(m_MilSystem, DMW_HIST_NUM_INTENSITIES, M_HIST_LIST, &MilHistResult);
		if (MilHistResult) {

			MimHistogram(MilImageThreshold, MilHistResult);
			MimGetResult(MilHistResult, M_VALUE, HistValues);
		
		} else {

			bResultProcess = FALSE;
		}
	}


	/////////////////////////////////////////////////////////////////
	// ���� /////////////////////////////////////////////////////////
	if (bResultProcess) {

		UINT	nNumberOfPixel		= 0;
		DOUBLE	dblWhitePixelRatio	= 0;

		// �˻� ���� ��ü �ȼ� ��
		nNumberOfPixel = rectInspectionRegion.sizeRect.cx * rectInspectionRegion.sizeRect.cy;

		// ȭ��Ʈ �ȼ� ����
		if ((UINT)HistValues[DMW_HIST_WHITE] == 0)	dblWhitePixelRatio = 0;
		else										dblWhitePixelRatio = (DOUBLE)((DOUBLE)HistValues[DMW_HIST_WHITE] / nNumberOfPixel) * 100.0;

		// ����
		stResult.nResultRatioWhitePixel = stParam.bUseReverseJudgement ? T_RESULT_SUCCESS : T_RESULT_FAILURE;
		if ((UINT)(dblWhitePixelRatio * 100) >= (UINT)(stParam.stInspectionInfo.dblRatioWhitePixelMIN * 100) &&
			(UINT)(dblWhitePixelRatio * 100) <= (UINT)(stParam.stInspectionInfo.dblRatioWhitePixelMAX * 100))	
				stResult.nResultRatioWhitePixel = stParam.bUseReverseJudgement ? T_RESULT_FAILURE : T_RESULT_SUCCESS;

		// ���� ����
		nResultInspection = T_RESULT_SUCCESS;
		if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultRatioWhitePixel;

		// ��� ����
		stResult.dblRatioWhitePixel	= dblWhitePixelRatio;
		stResult.nResultInspection	= nResultInspection;

		// ���μ��� �ð�
		dwTimeProcess = GetTickCount() - dwTimeProcess;

		// ����� �޼���
// 		MessageWindow(cDEBUG, _T("----------------------------------------------------------------------------------------------------"));
// 		MessageWindow(cDEBUG, _T("ProcessImage_Threshold::Inspection Rect.x=%.2f"), (DOUBLE)rectInspectionRegion.ptTopLeft.x + stOriginOffset.dblX);
// 		MessageWindow(cDEBUG, _T("ProcessImage_Threshold::Inspection Rect.y=%.2f"), (DOUBLE)rectInspectionRegion.ptTopLeft.y + stOriginOffset.dblY);
// 		MessageWindow(cDEBUG, _T("ProcessImage_Threshold::GrayScale Type=%d"), stParam.stInspectionInfo.stThresholdInfo.nTypeGrayscale);
// 		MessageWindow(cDEBUG, _T("ProcessImage_Threshold::nNumberOfPixel=%d"), nNumberOfPixel);
// 		MessageWindow(cDEBUG, _T("ProcessImage_Threshold::HistValues[DMW_HIST_WHITE]=%d"), HistValues[DMW_HIST_WHITE]);
// 		MessageWindow(cDEBUG, _T("ProcessImage_Threshold::stParam.stInspectionInfo.dblRatioWhitePixelMIN=%.2f"), stParam.stInspectionInfo.dblRatioWhitePixelMIN);
// 		MessageWindow(cDEBUG, _T("ProcessImage_Threshold::stParam.stInspectionInfo.dblRatioWhitePixelMAX=%.2f"), stParam.stInspectionInfo.dblRatioWhitePixelMAX);
// 		MessageWindow(cDEBUG, _T("ProcessImage_Threshold::dblWhilePixelRatio=%.2f"), dblWhitePixelRatio);
// 		MessageWindow(cDEBUG, _T("ProcessImage_Threshold::dwTimeProcess=%d"), dwTimeProcess);
// 		MessageWindow(cDEBUG, _T("----------------------------------------------------------------------------------------------------"));
	}


	/////////////////////////////////////////////////////////////////
	// �˻� �̹��� ���� /////////////////////////////////////////////
	if (bSaveClip && bResultProcess && stResult.nResultInspection != T_RESULT_SUCCESS) {
	
		PMODEL_PROFILE_T		pstModelProfile		= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
		PVPRD_DATA_T			pstVisionSetupInfo	= &m_pstVisionProcedureData[m_stSystemStatus.nCurrentVisionInspectionNo];
		UINT					nInspectionNo		= 0;
		CString					strFileName			= _T("");
		CFileFind				fileFinder;

		// ���� �̸� ����
		strFileName.Format(_T("%s\\T%02d_%02d_%s_%s.JPG"),	pstWorkStatus->szWorkDataSaveDirectory, 
															nTestItemNo + 1,
															m_stSystemStatus.nCurrentVisionInspectionNo + 1,
															g_szTestResultEngS[stResult.nResultInspection],
															pstVisionSetupInfo->szName);

		// �̹��� ���� ����
		if (fileFinder.FindFile(strFileName)) {

			do {
			
				fileFinder.Close();
				strFileName.Empty();
				strFileName.Format(_T("%s\\T%02d_%02d_%s_%s_R%d.JPG"),	pstWorkStatus->szWorkDataSaveDirectory,
																		nTestItemNo + 1, 
																		m_stSystemStatus.nCurrentVisionInspectionNo + 1,
																		g_szTestResultEngS[stResult.nResultInspection],
																		pstVisionSetupInfo->szName,
																		++nInspectionNo);
			
			} while (fileFinder.FindFile(strFileName));
		}

		MbufExport(strFileName, M_JPEG_LOSSY, MilImageInspection);
		SDebugMessage(TRUE, _T("ProcessImage_Threshold::ExportImage = %s"), strFileName);
		fileFinder.Close();
	}


	/////////////////////////////////////////////////////////////////
	// MIL ���� ���� ////////////////////////////////////////////////
	if (MilImageThreshold)		MbufFree(MilImageThreshold);
	if (MilImageGrayScale)		MbufFree(MilImageGrayScale);
	if (MilImageInspection)		MbufFree(MilImageInspection);
	if (MilHistResult)			MimFree(MilHistResult);


	return	bResultProcess;
}


///////////////////////////////////////////////////////////////////////////////
// �̹��� ���μ��� : ���� ���� (THRESHOLD) ////////////////////////////////////
BOOL CMainApp::ProcessImage_ThresholdLength(UINT nTestItemNo, UINT nTestStationNo, DPS_POINT2D_T stOriginOffset, VI_PARAM_THRESHOLD_LENGTH_T& stParam, VI_RESULT_THRESHOLD_LENGTH_T& stResult, BOOL bSaveClip /* = TRUE */)
{
	BOOL			bResultProcess		= TRUE;

	MIL_ID			MilImageInspection	= M_NULL;
	MIL_ID			MilImageGrayScale	= M_NULL;
	MIL_ID			MilImageThreshold[VI_THL_MAX_POINT];

	MIL_ID			MilBlobResult		= M_NULL;
	MIL_ID			MilBlobFeatureList	= M_NULL;
	MIL_INT			MilTotalBlobs		= 0;

	MIL_DOUBLE*		MilPosX_MIN			= M_NULL;
	MIL_DOUBLE*		MilPosY_MIN			= M_NULL;
	MIL_DOUBLE*		MilPosX_MAX			= M_NULL;
	MIL_DOUBLE*		MilPosY_MAX			= M_NULL;

	INT				nPosX_MIN			= 0;
	INT				nPosX_MAX			= 0;
	INT				nPosY_MIN			= 0;
	INT				nPosY_MAX			= 0;

	MIL_INT			MilSizeBand			= 0;
	MIL_INT64		MilBufferAttributes	= M_IMAGE + M_PROC;
	SIZE			sizeImage;
	DPS_POINT2D_T	sizeTotalBlobs;
	DPS_RECT_T		rectInspectionRegion[VI_THL_MAX_POINT];

	DWORD			dwTimeProcess		= GetTickCount();
	UINT			nResultInspection	= T_RESULT_NONE;
	PWORK_STATUS_T	pstWorkStatus		= GetWorkStatus(nTestStationNo);


	/////////////////////////////////////////////////////////////////
	// �ʱ�ȭ ///////////////////////////////////////////////////////
	ZeroMemory(&stResult, sizeof(VI_RESULT_THRESHOLD_T));

	stResult.nResultInspection = T_RESULT_ERROR;

	MilImageThreshold[VI_THL_P1]	= M_NULL;
	MilImageThreshold[VI_THL_P2]	= M_NULL;


	/////////////////////////////////////////////////////////////////
	// �Ķ���� �ε� ////////////////////////////////////////////////
	rectInspectionRegion[VI_THL_P1]	= stParam.rectInspectionArea[VI_THL_P1];
	rectInspectionRegion[VI_THL_P2]	= stParam.rectInspectionArea[VI_THL_P2];


	/////////////////////////////////////////////////////////////////
	// 1�� ����Ʈ ��ġ ���� /////////////////////////////////////////
	{
		/////////////////////////////////////////////////////////////
		// �˻� �̹��� ���� ���� ////////////////////////////////////
		MbufChild2d(stParam.MilImageInspection, 
					rectInspectionRegion[VI_THL_P1].ptTopLeft.x + (INT)stOriginOffset.dblX,
					rectInspectionRegion[VI_THL_P1].ptTopLeft.y + (INT)stOriginOffset.dblY,
					rectInspectionRegion[VI_THL_P1].sizeRect.cx,
					rectInspectionRegion[VI_THL_P1].sizeRect.cy,
					&MilImageInspection);

		if (MilImageInspection == M_NULL)		bResultProcess = FALSE;
	

		/////////////////////////////////////////////////////////////
		// �׷��� ������ �̹��� ���� ���� ///////////////////////////
		if (bResultProcess) {
	
			MbufInquire(MilImageInspection, M_SIZE_BAND, &MilSizeBand);
			MbufInquire(MilImageInspection, M_SIZE_X, &sizeImage.cx);
			MbufInquire(MilImageInspection, M_SIZE_Y, &sizeImage.cy);

			MbufAllocColor(m_MilSystem, MIL_BAND_GRAY, sizeImage.cx, sizeImage.cy, (8 + M_UNSIGNED), MilBufferAttributes, &MilImageGrayScale);
			if (MilImageGrayScale == M_NULL)	bResultProcess = FALSE;
			else {
		
				if (MilSizeBand == MIL_BAND_RGB) {

					UINT	nTypeGrayScale = DMW_IP_GRAY_DEFAULT + stParam.stInspectionInfo.stThresholdInfo[VI_THL_P1].nTypeGrayscale;

					if (nTypeGrayScale == DMW_IP_GRAY_DEFAULT) {
				
						MimConvert(MilImageInspection, MilImageGrayScale, M_RGB_TO_L);

					} else {

						MIL_INT		MilBand	= 0;

						switch (nTypeGrayScale) {
					
							case	DMW_IP_GRAY_RED		:	MilBand = M_RED;	break;
							case	DMW_IP_GRAY_GREEN	:	MilBand = M_GREEN;	break;
							case	DMW_IP_GRAY_BLUE	:	MilBand = M_BLUE;	break;
						}

						MbufCopyColor(MilImageInspection, MilImageGrayScale, MilBand);
					}

				} else {
				
					MbufCopy(MilImageInspection, MilImageGrayScale);
				}
			}
		}


		/////////////////////////////////////////////////////////////
		// THRESHOLD �̹��� ���� ���� ///////////////////////////////
		if (bResultProcess) {

			MbufAllocColor(m_MilSystem, MIL_BAND_GRAY, sizeImage.cx, sizeImage.cy, (8 + M_UNSIGNED), MilBufferAttributes, &MilImageThreshold[VI_THL_P1]);
			if (MilImageThreshold[VI_THL_P1] == M_NULL)		bResultProcess = FALSE;;
		}


		/////////////////////////////////////////////////////////////
		// �̹��� ��ȯ //////////////////////////////////////////////
		if (bResultProcess) {

			// THRESHOLD ��ȯ
			MbufClear(MilImageThreshold[VI_THL_P1], M_NULL);
			CDpsMilImageWnd::ConvertBinarize(MilImageGrayScale, MilImageThreshold[VI_THL_P1], stParam.stInspectionInfo.stThresholdInfo[VI_THL_P1]);

			// �̹��� ����
			if (stParam.stInspectionInfo.bInvertImage[VI_THL_P1])	CDpsMilImageWnd::InvertImage(MilImageThreshold[VI_THL_P1]);

			// �̼� ���� ����
			CDpsMilImageWnd::RemoveParticles(MilImageThreshold[VI_THL_P1], MilImageThreshold[VI_THL_P1], stParam.stInspectionInfo.nParticleRadius[VI_THL_P1], M_BINARY);
		}


		/////////////////////////////////////////////////////////////
		// BLOB ���� ////////////////////////////////////////////////
		if (bResultProcess) {

			BOOL	bFoundBlob	= FALSE;
		
			// Blob Feature List ����
			MblobAllocFeatureList(m_MilSystem, &MilBlobFeatureList);
			MblobSelectFeature(MilBlobFeatureList, M_BOX);

			// Blob ��� ���� ����
			MblobAllocResult(m_MilSystem, &MilBlobResult); 

			// Blob ó��
			MblobCalculate(MilImageThreshold[VI_THL_P1], M_NULL, MilBlobFeatureList, MilBlobResult); 

			// Blob ���� ����
			MblobGetNumber(MilBlobResult, &MilTotalBlobs); 

			// Blob ��� ���� �� ��ġ ���� ���� (���� ū BLOB�� ����)
			if (MilTotalBlobs > 0) {

				// Blob ��� ����
				MilPosX_MIN	= new MIL_DOUBLE[MilTotalBlobs];
				MilPosY_MIN	= new MIL_DOUBLE[MilTotalBlobs];
				ZeroMemory(MilPosX_MIN, sizeof(MIL_DOUBLE) * MilTotalBlobs);
				ZeroMemory(MilPosY_MIN, sizeof(MIL_DOUBLE) * MilTotalBlobs);

				MblobGetResult(MilBlobResult, M_BOX_X_MIN, MilPosX_MIN); 
				MblobGetResult(MilBlobResult, M_BOX_Y_MIN, MilPosY_MIN); 

				MilPosX_MAX	= new MIL_DOUBLE[MilTotalBlobs];
				MilPosY_MAX	= new MIL_DOUBLE[MilTotalBlobs];
				ZeroMemory(MilPosX_MAX, sizeof(MIL_DOUBLE) * MilTotalBlobs);
				ZeroMemory(MilPosY_MAX, sizeof(MIL_DOUBLE) * MilTotalBlobs);

				MblobGetResult(MilBlobResult, M_BOX_X_MAX, MilPosX_MAX); 
				MblobGetResult(MilBlobResult, M_BOX_Y_MAX, MilPosY_MAX);

				// ��ġ ���� ����
				UINT	nIndexBlobs		= 0;
				UINT	nTotalBlobs		= (UINT)MilTotalBlobs;
				INT		nBlobSizeX		= 0;
				INT		nBlobSizeY		= 0;
				PINT	pAreaBlobSize	= new INT[nTotalBlobs];

				if (pAreaBlobSize) {

					ZeroMemory(pAreaBlobSize, sizeof(INT) * nTotalBlobs);
					ZeroMemory(&sizeTotalBlobs, sizeof(DPS_POINT2D_T));

					//MessageWindow(cDEBUG, _T("total blobs = %d"), nTotalBlobs);

					for (UINT nIndex = 0; nIndex < nTotalBlobs; nIndex++) {

						// BLOB ũ�� ���
						nBlobSizeX				= (INT)(MilPosX_MAX[nIndex] - MilPosX_MIN[nIndex]);
						nBlobSizeY				= (INT)(MilPosY_MAX[nIndex] - MilPosY_MIN[nIndex]);
						pAreaBlobSize[nIndex]	= nBlobSizeX * nBlobSizeY;

						//MessageWindow(cDEBUG, _T("blob size = %d * %d = %d"), nBlobSizeX, nBlobSizeY, pAreaBlobSize[nIndex]);

						// BLOB ũ�� ���� (MIN)
						if (stParam.stInspectionInfo.stSizeLimitBlob_MIN.cx) {
						
							if (nBlobSizeX < stParam.stInspectionInfo.stSizeLimitBlob_MIN.cx)
								continue;
						}

						if (stParam.stInspectionInfo.stSizeLimitBlob_MIN.cy) {
						
							if (nBlobSizeY < stParam.stInspectionInfo.stSizeLimitBlob_MIN.cy)
								continue;
						}

						// BLOB ũ�� ���� (MAX)
						if (stParam.stInspectionInfo.stSizeLimitBlob_MAX.cx) {
						
							if (nBlobSizeX > stParam.stInspectionInfo.stSizeLimitBlob_MAX.cx)
								continue;
						}

						if (stParam.stInspectionInfo.stSizeLimitBlob_MAX.cy) {
						
							if (nBlobSizeY > stParam.stInspectionInfo.stSizeLimitBlob_MAX.cy)
								continue;
						}

						// ���� ���
						switch (stParam.stInspectionInfo.nModeMeasurement) {

							case	VISION_THL_MODE_1P_X_TOTAL	:	
							case	VISION_THL_MODE_1P_Y_TOTAL	:
									{
										sizeTotalBlobs.dblX += nBlobSizeX;
										sizeTotalBlobs.dblY += nBlobSizeY;
									}

									break;

							case	VISION_THL_MODE_1P_X_SMALL	:	
							case	VISION_THL_MODE_1P_Y_SMALL	:	
									{
										// ���� ���� BLOB �˻�
										if (pAreaBlobSize[nIndex] < pAreaBlobSize[nIndexBlobs])
											nIndexBlobs = nIndex;
									}

									break;

							case	VISION_THL_MODE_1P_X_BIG	:	
							case	VISION_THL_MODE_1P_Y_BIG	:
							case	VISION_THL_MODE_2P_TB		:	
							case	VISION_THL_MODE_2P_BT		:	
							case	VISION_THL_MODE_2P_LR		:	
							case	VISION_THL_MODE_2P_RL		:	
									{
										// ���� ū BLOB �˻�
										if (pAreaBlobSize[nIndex] > pAreaBlobSize[nIndexBlobs])
											nIndexBlobs = nIndex;
									}

									break;
						}
					}

					nPosX_MIN	= (INT)MilPosX_MIN[nIndexBlobs];
					nPosX_MAX	= (INT)MilPosX_MAX[nIndexBlobs];
					nPosY_MIN	= (INT)MilPosY_MIN[nIndexBlobs];
					nPosY_MAX	= (INT)MilPosY_MAX[nIndexBlobs];
					bFoundBlob	= TRUE;
				}

				delete	[]	MilPosX_MIN;
				delete	[]	MilPosX_MAX;
				delete	[]	MilPosY_MIN;
				delete	[]	MilPosY_MAX;

				if (bFoundBlob) {

					stResult.dblPosX_MIN[VI_THL_P1] = (INT)rectInspectionRegion[VI_THL_P1].ptTopLeft.x + (INT)stOriginOffset.dblX + nPosX_MIN;
					stResult.dblPosX_MAX[VI_THL_P1] = (INT)rectInspectionRegion[VI_THL_P1].ptTopLeft.x + (INT)stOriginOffset.dblX + nPosX_MAX;
					stResult.dblPosY_MIN[VI_THL_P1] = (INT)rectInspectionRegion[VI_THL_P1].ptTopLeft.y + (INT)stOriginOffset.dblY + nPosY_MIN;
					stResult.dblPosY_MAX[VI_THL_P1] = (INT)rectInspectionRegion[VI_THL_P1].ptTopLeft.y + (INT)stOriginOffset.dblY + nPosY_MAX;
				}
			}

			// ���μ��� ��� ����
			bResultProcess = (stParam.stInspectionInfo.nModeMeasurement < VISION_THL_MODE_2P_TB) ? TRUE : bFoundBlob;

			// Blob ���� ����
			MblobFree(MilBlobResult); 
			MblobFree(MilBlobFeatureList);

			// �̹��� ���� ����
			if (MilImageGrayScale)		{ MbufFree(MilImageGrayScale);	MilImageGrayScale  = M_NULL; }
			if (MilImageInspection)		{ MbufFree(MilImageInspection); MilImageInspection = M_NULL; }
		}
	}


	/////////////////////////////////////////////////////////////////
	// 2�� ����Ʈ ��ġ ���� /////////////////////////////////////////
	if (bResultProcess && stParam.stInspectionInfo.nModeMeasurement >= VISION_THL_MODE_2P_TB) {

		/////////////////////////////////////////////////////////////
		// �˻� �̹��� ���� ���� ////////////////////////////////////
		MbufChild2d(stParam.MilImageInspection, 
					rectInspectionRegion[VI_THL_P2].ptTopLeft.x + (INT)stOriginOffset.dblX,
					rectInspectionRegion[VI_THL_P2].ptTopLeft.y + (INT)stOriginOffset.dblY,
					rectInspectionRegion[VI_THL_P2].sizeRect.cx,
					rectInspectionRegion[VI_THL_P2].sizeRect.cy,
					&MilImageInspection);

		if (MilImageInspection == M_NULL)		bResultProcess = FALSE;
	

		/////////////////////////////////////////////////////////////
		// �׷��� ������ �̹��� ���� ���� ///////////////////////////
		if (bResultProcess) {
	
			MbufInquire(MilImageInspection, M_SIZE_BAND, &MilSizeBand);
			MbufInquire(MilImageInspection, M_SIZE_X, &sizeImage.cx);
			MbufInquire(MilImageInspection, M_SIZE_Y, &sizeImage.cy);

			MbufAllocColor(m_MilSystem, MIL_BAND_GRAY, sizeImage.cx, sizeImage.cy, (8 + M_UNSIGNED), MilBufferAttributes, &MilImageGrayScale);
			if (MilImageGrayScale == M_NULL)	bResultProcess = FALSE;
			else {
		
				if (MilSizeBand == MIL_BAND_RGB) {

					UINT	nTypeGrayScale = DMW_IP_GRAY_DEFAULT + stParam.stInspectionInfo.stThresholdInfo[VI_THL_P1].nTypeGrayscale;

					if (nTypeGrayScale == DMW_IP_GRAY_DEFAULT) {
				
						MimConvert(MilImageInspection, MilImageGrayScale, M_RGB_TO_L);

					} else {

						MIL_INT		MilBand	= 0;

						switch (nTypeGrayScale) {
					
							case	DMW_IP_GRAY_RED		:	MilBand = M_RED;	break;
							case	DMW_IP_GRAY_GREEN	:	MilBand = M_GREEN;	break;
							case	DMW_IP_GRAY_BLUE	:	MilBand = M_BLUE;	break;
						}

						MbufCopyColor(MilImageInspection, MilImageGrayScale, MilBand);
					}

				} else {
				
					MbufCopy(MilImageInspection, MilImageGrayScale);
				}
			}
		}


		/////////////////////////////////////////////////////////////
		// THRESHOLD �̹��� ���� ���� ///////////////////////////////
		if (bResultProcess) {

			MbufAllocColor(m_MilSystem, MIL_BAND_GRAY, sizeImage.cx, sizeImage.cy, (8 + M_UNSIGNED), MilBufferAttributes, &MilImageThreshold[VI_THL_P2]);
			if (MilImageThreshold[VI_THL_P2] == M_NULL)		bResultProcess = FALSE;;
		}


		/////////////////////////////////////////////////////////////
		// �̹��� ��ȯ //////////////////////////////////////////////
		if (bResultProcess) {

			// THRESHOLD ��ȯ
			MbufClear(MilImageThreshold[VI_THL_P2], M_NULL);
			CDpsMilImageWnd::ConvertBinarize(MilImageGrayScale, MilImageThreshold[VI_THL_P2], stParam.stInspectionInfo.stThresholdInfo[VI_THL_P2]);

			// �̹��� ����
			if (stParam.stInspectionInfo.bInvertImage[VI_THL_P2])	CDpsMilImageWnd::InvertImage(MilImageThreshold[VI_THL_P2]);

			// �̼� ���� ����
			CDpsMilImageWnd::RemoveParticles(MilImageThreshold[VI_THL_P2], MilImageThreshold[VI_THL_P2], stParam.stInspectionInfo.nParticleRadius[VI_THL_P2], M_BINARY);
		}


		/////////////////////////////////////////////////////////////
		// BLOB ���� ////////////////////////////////////////////////
		if (bResultProcess) {

			BOOL	bFoundBlob	= FALSE;
		
			// Blob Feature List ����
			MblobAllocFeatureList(m_MilSystem, &MilBlobFeatureList);
			MblobSelectFeature(MilBlobFeatureList, M_BOX);

			// Blob ��� ���� ����
			MblobAllocResult(m_MilSystem, &MilBlobResult); 

			// Blob ó��
			MblobCalculate(MilImageThreshold[VI_THL_P2], M_NULL, MilBlobFeatureList, MilBlobResult); 

			// Blob ���� ����
			MblobGetNumber(MilBlobResult, &MilTotalBlobs); 

			// Blob ��� ���� �� ��ġ ���� ���� (���� ū BLOB�� ����)
			if (MilTotalBlobs > 0) {

				// Blob ��� ����
				MilPosX_MIN	= new MIL_DOUBLE[MilTotalBlobs];
				MilPosY_MIN	= new MIL_DOUBLE[MilTotalBlobs];
				ZeroMemory(MilPosX_MIN, sizeof(MIL_DOUBLE) * MilTotalBlobs);
				ZeroMemory(MilPosY_MIN, sizeof(MIL_DOUBLE) * MilTotalBlobs);

				MblobGetResult(MilBlobResult, M_BOX_X_MIN, MilPosX_MIN); 
				MblobGetResult(MilBlobResult, M_BOX_Y_MIN, MilPosY_MIN); 

				MilPosX_MAX	= new MIL_DOUBLE[MilTotalBlobs];
				MilPosY_MAX	= new MIL_DOUBLE[MilTotalBlobs];
				ZeroMemory(MilPosX_MAX, sizeof(MIL_DOUBLE) * MilTotalBlobs);
				ZeroMemory(MilPosY_MAX, sizeof(MIL_DOUBLE) * MilTotalBlobs);

				MblobGetResult(MilBlobResult, M_BOX_X_MAX, MilPosX_MAX); 
				MblobGetResult(MilBlobResult, M_BOX_Y_MAX, MilPosY_MAX);

				// ��ġ ���� ����
				UINT	nIndexBlobsMAX	= 0;
				UINT	nTotalBlobs		= (UINT)MilTotalBlobs;
				INT		nBlobSizeX		= 0;
				INT		nBlobSizeY		= 0;
				PINT	pAreaBlobSize	= new INT[nTotalBlobs];

				if (pAreaBlobSize) {

					ZeroMemory(pAreaBlobSize, sizeof(INT) * nTotalBlobs);

					for (UINT nIndex = 0; nIndex < nTotalBlobs; nIndex++) {

						nBlobSizeX				= (INT)(MilPosX_MAX[nIndex] - MilPosX_MIN[nIndex]);
						nBlobSizeY				= (INT)(MilPosY_MAX[nIndex] - MilPosY_MIN[nIndex]);
						pAreaBlobSize[nIndex]	= nBlobSizeX * nBlobSizeY;

						// ���� ū BLOB �˻�
						if (pAreaBlobSize[nIndex] > pAreaBlobSize[nIndexBlobsMAX])
							nIndexBlobsMAX = nIndex;
					}

					nPosX_MIN	= (INT)MilPosX_MIN[nIndexBlobsMAX];
					nPosX_MAX	= (INT)MilPosX_MAX[nIndexBlobsMAX];
					nPosY_MIN	= (INT)MilPosY_MIN[nIndexBlobsMAX];
					nPosY_MAX	= (INT)MilPosY_MAX[nIndexBlobsMAX];
					bFoundBlob	= TRUE;
				}

				delete	[]	MilPosX_MIN;
				delete	[]	MilPosX_MAX;
				delete	[]	MilPosY_MIN;
				delete	[]	MilPosY_MAX;

				if (bFoundBlob) {

					stResult.dblPosX_MIN[VI_THL_P2] = (INT)rectInspectionRegion[VI_THL_P2].ptTopLeft.x + (INT)stOriginOffset.dblX + nPosX_MIN;
					stResult.dblPosX_MAX[VI_THL_P2] = (INT)rectInspectionRegion[VI_THL_P2].ptTopLeft.x + (INT)stOriginOffset.dblX + nPosX_MAX;
					stResult.dblPosY_MIN[VI_THL_P2] = (INT)rectInspectionRegion[VI_THL_P2].ptTopLeft.y + (INT)stOriginOffset.dblY + nPosY_MIN;
					stResult.dblPosY_MAX[VI_THL_P2] = (INT)rectInspectionRegion[VI_THL_P2].ptTopLeft.y + (INT)stOriginOffset.dblY + nPosY_MAX;
				}
			}

			// ���μ��� ��� ����
			bResultProcess = bFoundBlob;

			// Blob ���� ����
			MblobFree(MilBlobResult); 
			MblobFree(MilBlobFeatureList);

			// �̹��� ���� ����
			if (MilImageGrayScale)		{ MbufFree(MilImageGrayScale);	MilImageGrayScale  = M_NULL; }
			if (MilImageInspection)		{ MbufFree(MilImageInspection); MilImageInspection = M_NULL; }
		}
	}


	/////////////////////////////////////////////////////////////////
	// ���� /////////////////////////////////////////////////////////
	if (bResultProcess) {

		DOUBLE	dblOriginPixelCount	= 0;
		DOUBLE	dblMeasurement		= 0;

		// �ȼ� �� ���
		switch (stParam.stInspectionInfo.nModeMeasurement) {

			case	VISION_THL_MODE_1P_X_TOTAL	:	dblOriginPixelCount	= sizeTotalBlobs.dblX;	break;
			case	VISION_THL_MODE_1P_Y_TOTAL	:	dblOriginPixelCount	= sizeTotalBlobs.dblY;	break;

			case	VISION_THL_MODE_1P_X_BIG	:
			case	VISION_THL_MODE_1P_X_SMALL	:	dblOriginPixelCount = stResult.dblPosX_MAX[VI_THL_P1] - stResult.dblPosX_MIN[VI_THL_P1];	break;

			case	VISION_THL_MODE_1P_Y_BIG	:
			case	VISION_THL_MODE_1P_Y_SMALL	:	dblOriginPixelCount = stResult.dblPosY_MAX[VI_THL_P1] - stResult.dblPosY_MIN[VI_THL_P1];	break;

			case	VISION_THL_MODE_2P_TB		:	dblOriginPixelCount = stResult.dblPosY_MAX[VI_THL_P2] - stResult.dblPosY_MIN[VI_THL_P1];	break;
			case	VISION_THL_MODE_2P_BT		:	dblOriginPixelCount = stResult.dblPosY_MAX[VI_THL_P1] - stResult.dblPosY_MIN[VI_THL_P2];	break;
			case	VISION_THL_MODE_2P_LR		:	dblOriginPixelCount = stResult.dblPosX_MAX[VI_THL_P2] - stResult.dblPosX_MIN[VI_THL_P1];	break;
			case	VISION_THL_MODE_2P_RL		:	dblOriginPixelCount = stResult.dblPosX_MAX[VI_THL_P1] - stResult.dblPosX_MIN[VI_THL_P2];	break;
		}

		if (dblOriginPixelCount < 0)	dblOriginPixelCount = 0;

		// ����
		dblMeasurement		= dblOriginPixelCount * stParam.dblGainLength;
		nResultInspection	= stParam.bUseReverseJudgement ? T_RESULT_SUCCESS : T_RESULT_FAILURE;
		if ((UINT)(dblMeasurement * 100) >= (UINT)(stParam.stInspectionInfo.dblLengthSpecMIN * 100) &&
			(UINT)(dblMeasurement * 100) <= (UINT)(stParam.stInspectionInfo.dblLengthSpecMAX * 100))	
				nResultInspection = stParam.bUseReverseJudgement ? T_RESULT_FAILURE : T_RESULT_SUCCESS;

		// ��� ����
		stResult.dblMeasurement		= dblMeasurement;
		stResult.nResultInspection	= nResultInspection;

		// ���μ��� �ð�
		dwTimeProcess = GetTickCount() - dwTimeProcess;

		// ����� �޼���
// 		MessageWindow(cDEBUG, _T("----------------------------------------------------------------------------------------------------"));
// 		MessageWindow(cDEBUG, _T("ProcessImage_ThresholdLength::stParam.stInspectionInfo.dblLengthSpecMIN=%.2f"), stParam.stInspectionInfo.dblLengthSpecMIN);
// 		MessageWindow(cDEBUG, _T("ProcessImage_ThresholdLength::stParam.stInspectionInfo.dblLengthSpecMAX=%.2f"), stParam.stInspectionInfo.dblLengthSpecMAX);
// 		MessageWindow(cDEBUG, _T("ProcessImage_ThresholdLength::dblOriginPixelCount=%.2f"), dblOriginPixelCount);
// 		MessageWindow(cDEBUG, _T("ProcessImage_ThresholdLength::dblMeasurement=%.2f"), dblMeasurement);
// 		MessageWindow(cDEBUG, _T("ProcessImage_ThresholdLength::dwTimeProcess=%d"), dwTimeProcess);
// 		MessageWindow(cDEBUG, _T("----------------------------------------------------------------------------------------------------"));
	}


	/////////////////////////////////////////////////////////////////
	// �˻� �̹��� ���� /////////////////////////////////////////////
	if (bSaveClip && bResultProcess && stResult.nResultInspection != T_RESULT_SUCCESS) {
	
		PMODEL_PROFILE_T		pstModelProfile		= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
		PVPRD_DATA_T			pstVisionSetupInfo	= &m_pstVisionProcedureData[m_stSystemStatus.nCurrentVisionInspectionNo];
		UINT					nInspectionNo		= 0;
		CString					strFileName			= _T("");
		CFileFind				fileFinder;

		for (UINT nIndex = 0; nIndex < VI_THL_MAX_POINT; nIndex++) {

			// ���� �̸� ����
			strFileName.Format(_T("%s\\T%02d_%02d_%s_%s_P%d.JPG"),	pstWorkStatus->szWorkDataSaveDirectory,
																	nTestItemNo + 1,
																	m_stSystemStatus.nCurrentVisionInspectionNo + 1,
																	g_szTestResultEngS[stResult.nResultInspection],
																	pstVisionSetupInfo->szName,
																	nIndex + 1);

			// �̹��� ���� ����
			if (fileFinder.FindFile(strFileName)) {

				do {
			
					fileFinder.Close();
					strFileName.Empty();
					strFileName.Format(_T("%s\\T%02d_%02d_%s_%s_P%d_R%d.JPG"),	pstWorkStatus->szWorkDataSaveDirectory,
																				nTestItemNo + 1,
																				m_stSystemStatus.nCurrentVisionInspectionNo + 1,
																				g_szTestResultEngS[stResult.nResultInspection],
																				pstVisionSetupInfo->szName,
																				nIndex + 1,
																				++nInspectionNo);
			
				} while (fileFinder.FindFile(strFileName));
			}

			MbufExport(strFileName, M_JPEG_LOSSY, MilImageThreshold[nIndex]);
			SDebugMessage(TRUE, _T("ProcessImage_ThresholdLength[%d]::ExportImage = %s"), nIndex + 1, strFileName);
			fileFinder.Close();
		}
	}


	/////////////////////////////////////////////////////////////////
	// MIL ���� ���� ////////////////////////////////////////////////
	if (MilImageThreshold[VI_THL_P1])		MbufFree(MilImageThreshold[VI_THL_P1]);
	if (MilImageThreshold[VI_THL_P2])		MbufFree(MilImageThreshold[VI_THL_P2]);


	return	bResultProcess;
}


///////////////////////////////////////////////////////////////////////////////
// �̹��� ���μ��� : ���� ��Ī ////////////////////////////////////////////////
BOOL CMainApp::ProcessImage_PatternMatch(UINT nTestItemNo, UINT nTestStationNo, DPS_POINT2D_T stOriginOffset, VI_PARAM_PATTERN_T& stParam, VI_RESULT_PATTERN_T& stResult, BOOL bSaveClip /* = TRUE */)
{
	BOOL			bResultProcess			= TRUE;

	MIL_ID			MilImageOrigin			= M_NULL;
	MIL_ID			MilImageOriginSearch	= M_NULL;
	MIL_ID			MilImageInspection		= M_NULL;

	MIL_ID			MilImageGrayOrigin		= M_NULL;
	MIL_ID			MilImageGrayInspection	= M_NULL;

	MIL_ID			MilModel				= M_NULL;
	MIL_ID			MilPatResult			= M_NULL;

	MIL_INT			MilNumberOfPattern		= 0;

	MIL_DOUBLE		MilPosX					= 0;
	MIL_DOUBLE		MilPosY					= 0;
	MIL_DOUBLE		MilAngle				= 0;
	MIL_DOUBLE		MilScore				= 0;
	MIL_DOUBLE		MilOrgPosX				= 0;
	MIL_DOUBLE		MilOrgPosY				= 0;

	DOUBLE			dblOffsetX				= 0;
	DOUBLE			dblOffsetY				= 0;
	DOUBLE			dblAngle				= 0;
	DOUBLE			dblMatchScore			= 0;

	MIL_INT			MilSizeBand				= 0;
	MIL_INT64		MilBufferAttributes		= M_IMAGE + M_PROC;
	DPS_RECT_T		rectInspectionRegion;
	CRect			rectRegionSearch;
	CRect			rectRegionPattern;
	SIZE			sizeImage;

	DWORD			dwTimeProcess			= GetTickCount();
	UINT			nResultInspection		= T_RESULT_NONE;
	PWORK_STATUS_T	pstWorkStatus			= GetWorkStatus(nTestStationNo);


	/////////////////////////////////////////////////////////////////
	// �ʱ�ȭ ///////////////////////////////////////////////////////
	ZeroMemory(&stResult, sizeof(VI_RESULT_PATTERN_T));

	stResult.nResultInspection = T_RESULT_ERROR;


	/////////////////////////////////////////////////////////////////
	// �Ķ���� �ε� ////////////////////////////////////////////////
	rectInspectionRegion	= stParam.rectInspectionArea;


	/////////////////////////////////////////////////////////////////
	// ���� �̹��� �ε� �� �׷��� ������ ���� ///////////////////////
	MbufImport((MIL_TEXT_CHAR*)stParam.szFileOriginImage, M_DEFAULT, M_RESTORE, m_MilSystem, &MilImageOrigin);
	if (MilImageOrigin == M_NULL)		bResultProcess = FALSE;
	else {
	
		MbufInquire(MilImageOrigin, M_SIZE_BAND, &MilSizeBand);
		MbufInquire(MilImageOrigin, M_SIZE_X, &sizeImage.cx);
		MbufInquire(MilImageOrigin, M_SIZE_Y, &sizeImage.cy);

		MbufAllocColor(m_MilSystem, MIL_BAND_GRAY, sizeImage.cx, sizeImage.cy, (8 + M_UNSIGNED), MilBufferAttributes, &MilImageGrayOrigin);
		if (MilImageGrayOrigin == M_NULL)	bResultProcess = FALSE;
		else {
		
			if (MilSizeBand == MIL_BAND_RGB)	MimConvert(MilImageOrigin, MilImageGrayOrigin, M_RGB_TO_L);
			else								MbufCopy(MilImageOrigin, MilImageGrayOrigin);

			MbufFree(MilImageOrigin);
			MilImageOrigin = M_NULL;
		}
	}


	/////////////////////////////////////////////////////////////////
	// �˻� �̹��� �׷��� ������ ���� ///////////////////////////////
	if (bResultProcess) {
	
		MbufInquire(stParam.MilImageInspection, M_SIZE_BAND, &MilSizeBand);
		MbufInquire(stParam.MilImageInspection, M_SIZE_X, &sizeImage.cx);
		MbufInquire(stParam.MilImageInspection, M_SIZE_Y, &sizeImage.cy);

		MbufAllocColor(m_MilSystem, MIL_BAND_GRAY, sizeImage.cx, sizeImage.cy, (8 + M_UNSIGNED), MilBufferAttributes, &MilImageGrayInspection);
		if (MilImageGrayInspection == M_NULL)	bResultProcess = FALSE;
		else {
		
			if (MilSizeBand == MIL_BAND_RGB)	MimConvert(stParam.MilImageInspection, MilImageGrayInspection, M_RGB_TO_L);
			else								MbufCopy(stParam.MilImageInspection, MilImageGrayInspection);
		}
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���� �˻� ���� ���� ���� ////////////////////////////////
	if (bResultProcess) {

		// �̹��� ���� �ε�
		MbufInquire(MilImageGrayOrigin, M_SIZE_X, &sizeImage.cx);
		MbufInquire(MilImageGrayOrigin, M_SIZE_Y, &sizeImage.cy);

		// �˻� ���� ���� (�˻� ���� + �˻� ����)
		rectRegionSearch.left		= __max((LONG)(rectInspectionRegion.ptTopLeft.x - (LONG)stParam.stInspectionInfo.nPatternSearchRange), 0);
		rectRegionSearch.top		= __max((LONG)(rectInspectionRegion.ptTopLeft.y - (LONG)stParam.stInspectionInfo.nPatternSearchRange), 0);
		rectRegionSearch.right		= __min((LONG)(rectInspectionRegion.ptTopLeft.x + rectInspectionRegion.sizeRect.cx + (LONG)stParam.stInspectionInfo.nPatternSearchRange), sizeImage.cx);
		rectRegionSearch.bottom		= __min((LONG)(rectInspectionRegion.ptTopLeft.y + rectInspectionRegion.sizeRect.cy + (LONG)stParam.stInspectionInfo.nPatternSearchRange), sizeImage.cy);

		// ���� ���� ���� (�˻� ���� ���� ��� ����)
		rectRegionPattern.left		= rectInspectionRegion.ptTopLeft.x - rectRegionSearch.left;
		rectRegionPattern.top		= rectInspectionRegion.ptTopLeft.y - rectRegionSearch.top;
		rectRegionPattern.right		= rectRegionPattern.left + rectInspectionRegion.sizeRect.cx;
		rectRegionPattern.bottom	= rectRegionPattern.top  + rectInspectionRegion.sizeRect.cy;

		// ���� ����
		MbufChild2d(MilImageGrayOrigin, 
					rectRegionSearch.left, 
					rectRegionSearch.top, 
					rectRegionSearch.Width(), 
					rectRegionSearch.Height(), 
					&MilImageOriginSearch);

		if (MilImageOriginSearch == M_NULL)		bResultProcess = FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// ��� ���� �˻� ���� ���� ���� ////////////////////////////////
	if (bResultProcess) {

		// �˻� ���� ���� (�˻� ���� + �˻� ����)
		// Ȩ ��ġ ���� �� �������� ������ �� ����.
		rectRegionSearch.left		= __max((LONG)(rectInspectionRegion.ptTopLeft.x + (INT)stOriginOffset.dblX - (LONG)stParam.stInspectionInfo.nPatternSearchRange), 0);
		rectRegionSearch.top		= __max((LONG)(rectInspectionRegion.ptTopLeft.y + (INT)stOriginOffset.dblY - (LONG)stParam.stInspectionInfo.nPatternSearchRange), 0);
		rectRegionSearch.right		= __min((LONG)(rectInspectionRegion.ptTopLeft.x + (INT)stOriginOffset.dblX + rectInspectionRegion.sizeRect.cx + (LONG)stParam.stInspectionInfo.nPatternSearchRange), sizeImage.cx);
		rectRegionSearch.bottom		= __min((LONG)(rectInspectionRegion.ptTopLeft.y + (INT)stOriginOffset.dblY + rectInspectionRegion.sizeRect.cy + (LONG)stParam.stInspectionInfo.nPatternSearchRange), sizeImage.cy);

		// ���� ����
		MbufChild2d(MilImageGrayInspection, 
					rectRegionSearch.left, 
					rectRegionSearch.top, 
					rectRegionSearch.Width(), 
					rectRegionSearch.Height(), 
					&MilImageInspection);

		if (MilImageInspection == M_NULL)		bResultProcess = FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// ���� �˻� ////////////////////////////////////////////////////
	if (bResultProcess) {

		bResultProcess = FALSE;

		// ���� ���
		MpatAllocModel(	m_MilSystem, 
						MilImageOriginSearch,
						rectRegionPattern.left, 
						rectRegionPattern.top, 
						rectRegionPattern.Width(), 
						rectRegionPattern.Height(), 
						M_NORMALIZED, 
						&MilModel);

		if (MilModel) {

			MIL_INT		nSpeed		= M_HIGH;
			MIL_INT		nAccuracy	= M_HIGH;

			// ���� �˻� �ӵ� ����
			switch (stParam.stInspectionInfo.nSpeed) {
			
				case	VISION_PTN_SPEED_HIGH		:	nSpeed = M_HIGH;		break;
				case	VISION_PTN_SPEED_LOW		:	nSpeed = M_LOW;			break;
				case	VISION_PTN_SPEED_MEDIUM		:	nSpeed = M_MEDIUM;		break;
				case	VISION_PTN_SPEED_VERY_HIGH	:	nSpeed = M_VERY_HIGH;	break;
				case	VISION_PTN_SPEED_VERY_LOW	:	nSpeed = M_VERY_LOW;	break;
			}

			// ���� �˻� ���е� ����
			switch (stParam.stInspectionInfo.nAccuracy) {
			
				case	VISION_PTN_ACCURACY_HIGH	:	nAccuracy = M_HIGH;		break;
				case	VISION_PTN_ACCURACY_LOW		:	nAccuracy = M_LOW;		break;
				case	VISION_PTN_ACCURACY_MEDIUM	:	nAccuracy = M_MEDIUM;	break;
			}

			// ���� �˻� ����
			MpatSetSpeed(MilModel, nSpeed);
			MpatSetAccuracy(MilModel, nAccuracy);
			MpatSetAngle(MilModel, M_SEARCH_ANGLE_MODE, M_ENABLE);
			MpatSetAngle(MilModel, M_SEARCH_ANGLE_DELTA_NEG, 5);
			MpatSetAngle(MilModel, M_SEARCH_ANGLE_DELTA_POS, 5);
			MpatSetAngle(MilModel, M_SEARCH_ANGLE_ACCURACY, 1.0);
			MpatSetAngle(MilModel, M_SEARCH_ANGLE_INTERPOLATION_MODE, M_BILINEAR);
			MpatPreprocModel(MilImageOriginSearch, MilModel, M_DEFAULT);

			// ���� �˻� ��� ���� ����
			MpatAllocResult(m_MilSystem, 1L, &MilPatResult);
			if (MilPatResult) {

				// ���� �˻�
				MpatFindModel(MilImageInspection, MilModel, MilPatResult);
				MilNumberOfPattern = MpatGetNumber(MilPatResult, M_NULL);
				if (MilNumberOfPattern == 1L) {

					MpatGetResult(MilPatResult, M_POSITION_X, &MilPosX); 
					MpatGetResult(MilPatResult, M_POSITION_Y, &MilPosY);
					MpatGetResult(MilPatResult, M_ANGLE, &MilAngle);
					MpatGetResult(MilPatResult, M_SCORE, &MilScore);

					MpatInquire(MilModel, M_ORIGINAL_X, &MilOrgPosX);
					MpatInquire(MilModel, M_ORIGINAL_Y, &MilOrgPosY);
				}

				bResultProcess = TRUE;
			}
		}
	}


	/////////////////////////////////////////////////////////////////
	// ���� /////////////////////////////////////////////////////////
	if (bResultProcess) {

		// ������
		dblOffsetX = (DOUBLE)(MilPosX - MilOrgPosX);
		dblOffsetY = (DOUBLE)(MilPosY - MilOrgPosY);

		stResult.nResultOffsetX = T_RESULT_SUCCESS;
		if (!stParam.bUseReverseJudgement && (INT)abs((INT)(dblOffsetX * 100)) > (INT)(stParam.stInspectionInfo.flOffset.x * 100))
			stResult.nResultOffsetX = T_RESULT_FAILURE;

		stResult.nResultOffsetY = T_RESULT_SUCCESS;
		if (!stParam.bUseReverseJudgement && (INT)abs((INT)(dblOffsetY * 100)) > (INT)(stParam.stInspectionInfo.flOffset.y * 100))
			stResult.nResultOffsetY = T_RESULT_FAILURE;

		// ����
		dblAngle = (DOUBLE)(abs(MilAngle) > 180 ? abs(MilAngle) - 360 : MilAngle);

		stResult.nResultAngle = T_RESULT_SUCCESS;
		if (!stParam.bUseReverseJudgement && (INT)abs((INT)(dblAngle * 100)) > (INT)(stParam.stInspectionInfo.dblAngle * 100))
			stResult.nResultAngle = T_RESULT_FAILURE;

		// ��Ī��
		dblMatchScore = (DOUBLE)MilScore;

		stResult.nResultMatchScore = stParam.bUseReverseJudgement ? T_RESULT_FAILURE : T_RESULT_SUCCESS;
		if ((INT)(dblMatchScore * 100) < (INT)(stParam.stInspectionInfo.dblMatchScore * 100))
			stResult.nResultMatchScore = stParam.bUseReverseJudgement ? T_RESULT_SUCCESS : T_RESULT_FAILURE;

		// ���� ����
		nResultInspection = T_RESULT_SUCCESS;
		if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultOffsetX;
		if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultOffsetY;
		if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultAngle;
		if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultMatchScore;

		// ��� ����
		stResult.flOffset.x			= (FLOAT)dblOffsetX;
		stResult.flOffset.y			= (FLOAT)dblOffsetY;
		stResult.dblAngle			= dblAngle;
		stResult.dblMatchScore		= dblMatchScore;
		stResult.nResultInspection	= nResultInspection;

		// ���μ��� �ð�
		dwTimeProcess = GetTickCount() - dwTimeProcess;

		// ����� �޼���
// 		MessageWindow(cDEBUG, _T("----------------------------------------------------------------------------------------------------"));
// 		MessageWindow(cDEBUG, _T("ProcessImage_PatternMatch::rectRegionSearch = %d, %d, %d, %d"), rectRegionSearch.left, rectRegionSearch.top, rectRegionSearch.right, rectRegionSearch.bottom);
// 		MessageWindow(cDEBUG, _T("ProcessImage_PatternMatch::MilNumberOfPattern=%d"), MilNumberOfPattern);
// 		MessageWindow(cDEBUG, _T("ProcessImage_PatternMatch::flOffset=%.2f, %.2f"), dblOffsetX, dblOffsetY);
// 		MessageWindow(cDEBUG, _T("ProcessImage_PatternMatch::dblAngle=%.2f"), dblAngle);
// 		MessageWindow(cDEBUG, _T("ProcessImage_PatternMatch::dblMatchScore=%.2f"), dblMatchScore);
// 		MessageWindow(cDEBUG, _T("ProcessImage_PatternMatch::dwTimeProcess=%d"), dwTimeProcess);
// 		MessageWindow(cDEBUG, _T("----------------------------------------------------------------------------------------------------"));
	}


	/////////////////////////////////////////////////////////////////
	// �˻� �̹��� ���� /////////////////////////////////////////////
	if (bSaveClip && bResultProcess && stResult.nResultInspection != T_RESULT_SUCCESS) {
	
		PMODEL_PROFILE_T		pstModelProfile		= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
		PVPRD_DATA_T			pstVisionSetupInfo	= &m_pstVisionProcedureData[m_stSystemStatus.nCurrentVisionInspectionNo];
		UINT					nInspectionNo		= 0;
		CString					strFileName			= _T("");
		CFileFind				fileFinder;

		// ���� �̸� ����
		strFileName.Format(_T("%s\\T%02d_%02d_%s_%s.JPG"),	pstWorkStatus->szWorkDataSaveDirectory, 
															nTestItemNo + 1,
															m_stSystemStatus.nCurrentVisionInspectionNo + 1,
															g_szTestResultEngS[stResult.nResultInspection],
															pstVisionSetupInfo->szName);

		// �̹��� ���� ����
		if (fileFinder.FindFile(strFileName)) {

			do {
			
				fileFinder.Close();
				strFileName.Empty();
															
				strFileName.Format(_T("%s\\T%02d_%02d_%s_%s_R%d.JPG"),	pstWorkStatus->szWorkDataSaveDirectory, 
																		nTestItemNo + 1,
																		m_stSystemStatus.nCurrentVisionInspectionNo + 1,
																		g_szTestResultEngS[stResult.nResultInspection],
																		pstVisionSetupInfo->szName,
																		++nInspectionNo);
			
			} while (fileFinder.FindFile(strFileName));
		}

		MbufExport(strFileName, M_JPEG_LOSSY, MilImageInspection);
		SDebugMessage(TRUE, _T("ProcessImage_PatternMatch::ExportImage = %s"), strFileName);
		fileFinder.Close();
	}


	/////////////////////////////////////////////////////////////////
	// MIL ���� ���� ////////////////////////////////////////////////
	if (MilPatResult != M_NULL)				{ MpatFree(MilPatResult);			/*MessageWindow(cDEBUG, _T("ProcessImage_PatternMatch::Release <MilPatResult>"));*/ }
	if (MilModel != M_NULL)					{ MpatFree(MilModel);				/*MessageWindow(cDEBUG, _T("ProcessImage_PatternMatch::Release <MilModel>"));*/ }
	if (MilImageOriginSearch != M_NULL)		{ MbufFree(MilImageOriginSearch);	/*MessageWindow(cDEBUG, _T("ProcessImage_PatternMatch::Release <MilImageOriginSearch>"));*/ }
	if (MilImageGrayOrigin != M_NULL)		{ MbufFree(MilImageGrayOrigin);		/*MessageWindow(cDEBUG, _T("ProcessImage_PatternMatch::Release <MilImageGrayOrigin>"));*/ }
	if (MilImageInspection != M_NULL)		{ MbufFree(MilImageInspection);		/*MessageWindow(cDEBUG, _T("ProcessImage_PatternMatch::Release <MilImageInspection>"));*/ }
	if (MilImageOrigin != M_NULL)			{ MbufFree(MilImageOrigin);			/*MessageWindow(cDEBUG, _T("ProcessImage_PatternMatch::Release <MilImageOrigin>"));*/ }
	if (MilImageGrayInspection != M_NULL)	{ MbufFree(MilImageGrayInspection);	/*MessageWindow(cDEBUG, _T("ProcessImage_PatternMatch::Release <MilImageGrayInspection>"));*/ }


	return	bResultProcess;
}


///////////////////////////////////////////////////////////////////////////////
// �̹��� ���μ��� : �� �˻� ////////////////////////////////////////////////
BOOL CMainApp::ProcessImage_ModelFind(UINT nTestItemNo, UINT nTestStationNo, DPS_POINT2D_T stOriginOffset, VI_PARAM_MODEL_T& stParam, VI_RESULT_MODEL_T& stResult, BOOL bSaveClip /* = TRUE */)
{
	BOOL			bResultProcess			= TRUE;
	BOOL			bFoundModel				= FALSE;

	MIL_ID			MilImageInspection		= M_NULL;
	MIL_ID			MilImageThreshold		= M_NULL;
	MIL_ID			MilImageGrayInspection	= M_NULL;

	MIL_ID			MilModelFinderContext	= M_NULL;
	MIL_ID			MilModelFinderResult	= M_NULL;

	MIL_INT			MilNumberOfResult		= 0;

	MIL_INT*		MilModelIndex			= M_NULL;
	MIL_DOUBLE*		MilPosX					= M_NULL;
	MIL_DOUBLE*		MilPosY					= M_NULL;
	MIL_DOUBLE*		MilAngle				= M_NULL;
	MIL_DOUBLE*		MilScore				= M_NULL;

	MIL_DOUBLE		MilOrgPosX				= 0;
	MIL_DOUBLE		MilOrgPosY				= 0;
	MIL_DOUBLE		MilOrgAngle				= 0;
	MIL_DOUBLE		MilOrgScore				= 0;

	MIL_DOUBLE		MilTimePreProcess		= 0;
	MIL_DOUBLE		MilTimeFind				= 0;

	DOUBLE			dblOffsetX				= 0;
	DOUBLE			dblOffsetY				= 0;
	DOUBLE			dblAngle				= 0;
	DOUBLE			dblMatchScore			= 0;

	MIL_INT			MilSizeBand				= 0;
	MIL_INT64		MilBufferAttributes		= M_IMAGE + M_PROC;

	DPS_RECT_T		rectInspectionRegion;
	CRect			rectRegionSearch;
	SIZE			sizeImage;
	
	CString			strFileName				= _T("");
	CFileFind		fileFinder;

	UINT			nCountRecursive			= 0;
	DPS_POINT2D_T	stOffsetRecursive;
	DPS_POINT2D_T	stRangeRecursive;

	DWORD			dwTimeProcess			= GetTickCount();
	UINT			nResultInspection		= T_RESULT_NONE;
	PWORK_STATUS_T	pstWorkStatus			= GetWorkStatus(nTestStationNo);


	/////////////////////////////////////////////////////////////////
	// �ʱ�ȭ ///////////////////////////////////////////////////////
	ZeroMemory(&stResult, sizeof(VI_RESULT_MODEL_T));
	ZeroMemory(&stOffsetRecursive, sizeof(DPS_POINT2D_T));
	ZeroMemory(&stRangeRecursive, sizeof(DPS_POINT2D_T));

	stResult.nResultInspection = T_RESULT_ERROR;


	/////////////////////////////////////////////////////////////////
	// �Ķ���� �ε� ////////////////////////////////////////////////
	rectInspectionRegion	= stParam.rectInspectionArea;


	/////////////////////////////////////////////////////////////////
	// �� ������Ʈ�� ���� üũ ////////////////////////////////////
	bResultProcess = FALSE;
	for (INT nIndex = 0; nIndex < stParam.stInspectionInfo.nNumberOfGeometryFile; nIndex++) {
	
		strFileName = stParam.stInspectionInfo.szFileGeometry[nIndex];
		if (!strFileName.IsEmpty() && fileFinder.FindFile(strFileName))
			bResultProcess = TRUE;

		fileFinder.Close();
	}


	/////////////////////////////////////////////////////////////////
	// �׷��� ������ �̹��� ���� ���� ///////////////////////////////
	if (bResultProcess) {
	
		MbufInquire(stParam.MilImageInspection, M_SIZE_BAND, &MilSizeBand);
		MbufInquire(stParam.MilImageInspection, M_SIZE_X, &sizeImage.cx);
		MbufInquire(stParam.MilImageInspection, M_SIZE_Y, &sizeImage.cy);

		MbufAllocColor(m_MilSystem, MIL_BAND_GRAY, sizeImage.cx, sizeImage.cy, (8 + M_UNSIGNED), MilBufferAttributes, &MilImageGrayInspection);
		if (MilImageGrayInspection == M_NULL)	bResultProcess = FALSE;
		else {
		
			if (MilSizeBand == MIL_BAND_RGB) {

				UINT	nTypeGrayScale = DMW_IP_GRAY_DEFAULT + stParam.stThresholdInfo.stThresholdInfo.nTypeGrayscale;

				if (nTypeGrayScale == DMW_IP_GRAY_DEFAULT) {
				
					MimConvert(stParam.MilImageInspection, MilImageGrayInspection, M_RGB_TO_L);

				} else {

					MIL_INT		MilBand	= M_RGB_TO_L;

					switch (nTypeGrayScale) {
					
						case	DMW_IP_GRAY_RED		:	MilBand = M_RED;	break;
						case	DMW_IP_GRAY_GREEN	:	MilBand = M_GREEN;	break;
						case	DMW_IP_GRAY_BLUE	:	MilBand = M_BLUE;	break;
					}

					MbufCopyColor(stParam.MilImageInspection, MilImageGrayInspection, MilBand);
				}

			} else {
				
				MbufCopy(stParam.MilImageInspection, MilImageGrayInspection);
			}
		}
	}


	/////////////////////////////////////////////////////////////////
	// THRESHOLD �̹��� ��ȯ ////////////////////////////////////////
	if (bResultProcess && stParam.stThresholdInfo.dblRatioWhitePixelMIN > 0) {

		MbufAllocColor(m_MilSystem, MIL_BAND_GRAY, sizeImage.cx, sizeImage.cy, (8 + M_UNSIGNED), MilBufferAttributes, &MilImageThreshold);
		if (MilImageThreshold == M_NULL)	bResultProcess = FALSE;
		else {

			// THRESHOLD ��ȯ
			MbufClear(MilImageThreshold, M_NULL);
			CDpsMilImageWnd::ConvertBinarize(MilImageGrayInspection, MilImageThreshold, stParam.stThresholdInfo.stThresholdInfo);

			// �̹��� ����
			if (stParam.stThresholdInfo.bInvertImage)	CDpsMilImageWnd::InvertImage(MilImageThreshold);

			// �̼� ���� ����
			CDpsMilImageWnd::RemoveParticles(MilImageThreshold, MilImageThreshold, stParam.stThresholdInfo.nParticleRadius, M_BINARY);

			// �׷��� ������ �̹��� ���� ���� �� THRESHOLD �� ����
			MbufFree(MilImageGrayInspection);
			MilImageGrayInspection = MilImageThreshold;
		}
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���� ////////////////////////////////////////////////////
	do {

		/////////////////////////////////////////////////////////////
		// �ʱ�ȭ ///////////////////////////////////////////////////
		stResult.nResultInspection = T_RESULT_ERROR;

	
		/////////////////////////////////////////////////////////////
		// ��� ���� ���� ���� //////////////////////////////////////
		if (bResultProcess) {

			// �̹��� ���� �ε�
			MbufInquire(stParam.MilImageInspection, M_SIZE_X, &sizeImage.cx);
			MbufInquire(stParam.MilImageInspection, M_SIZE_Y, &sizeImage.cy);

			// �˻� ���� ����
			rectRegionSearch.left		= __max(rectInspectionRegion.ptTopLeft.x + (LONG)stOriginOffset.dblX + (LONG)stOffsetRecursive.dblX + (LONG)stRangeRecursive.dblX, 0);
			rectRegionSearch.top		= __max(rectInspectionRegion.ptTopLeft.y + (LONG)stOriginOffset.dblY + (LONG)stOffsetRecursive.dblY + (LONG)stRangeRecursive.dblY, 0);
			rectRegionSearch.right		= __min(rectInspectionRegion.ptTopLeft.x + (LONG)stOriginOffset.dblX + (LONG)stOffsetRecursive.dblX + rectInspectionRegion.sizeRect.cx - (LONG)stRangeRecursive.dblX, sizeImage.cx);
			rectRegionSearch.bottom		= __min(rectInspectionRegion.ptTopLeft.y + (LONG)stOriginOffset.dblY + (LONG)stOffsetRecursive.dblY + rectInspectionRegion.sizeRect.cy - (LONG)stRangeRecursive.dblY, sizeImage.cy);

			// ���� �ʱ�ȭ
			if (MilImageInspection != M_NULL) {
			
				MbufFree(MilImageInspection);
				MilImageInspection = M_NULL;
			}

			// ���� ����
			MbufChild2d(MilImageGrayInspection, 
						rectRegionSearch.left, 
						rectRegionSearch.top, 
						rectRegionSearch.Width(), 
						rectRegionSearch.Height(), 
						&MilImageInspection);

			if (MilImageInspection == M_NULL)		bResultProcess = FALSE;
		}


		/////////////////////////////////////////////////////////////////
		// ��� �� �˻� ///////////////////////////////////////////////
		if (bResultProcess) {

			//MessageWindow(cDEBUG, _T("----------------------------------------------------------------------------------------------------"));
			//MessageWindow(cDEBUG, _T("ProcessImage_ModelFind::rectRegionSearch = %d, %d, %d, %d"), rectRegionSearch.left, rectRegionSearch.top, rectRegionSearch.right, rectRegionSearch.bottom);

			bFoundModel = FALSE;
			for (INT nIndex = 0; nIndex < stParam.stInspectionInfo.nNumberOfGeometryFile; nIndex++) {

				strFileName = stParam.stInspectionInfo.szFileGeometry[nIndex];
				if (!strFileName.IsEmpty() && fileFinder.FindFile(strFileName)) {
	
					MmodRestore((MIL_CONST_TEXT_PTR)stParam.stInspectionInfo.szFileGeometry[nIndex], m_MilSystem, M_DEFAULT, &MilModelFinderContext);
					if (MilModelFinderContext) {

						MmodAllocResult(m_MilSystem, M_DEFAULT, &MilModelFinderResult);
						MappTimer(M_TIMER_RESET + M_SYNCHRONOUS, M_NULL);
						MmodPreprocess(MilModelFinderContext, M_DEFAULT);
						MappTimer(M_TIMER_READ + M_SYNCHRONOUS, &MilTimePreProcess);
						MappTimer(M_TIMER_RESET + M_SYNCHRONOUS, M_NULL);
						MmodFind(MilModelFinderContext, MilImageInspection, MilModelFinderResult);
						MappTimer(M_TIMER_READ + M_SYNCHRONOUS, &MilTimeFind);
						MmodGetResult(MilModelFinderResult, M_DEFAULT, M_NUMBER + M_TYPE_MIL_INT, &MilNumberOfResult);

						//MessageWindow(cDEBUG, _T("ProcessImage_ModelFind::Searching File    = [%d] %s"), nIndex, strFileName);
						//MessageWindow(cDEBUG, _T("ProcessImage_ModelFind::MilNumberOfResult = %d"), MilNumberOfResult);
						//MessageWindow(cDEBUG, _T("ProcessImage_ModelFind::MilTimePreProcess = %.1f ms"), MilTimePreProcess * 1000.0);
						//MessageWindow(cDEBUG, _T("ProcessImage_ModelFind::MilTimeFind       = %.1f ms"), MilTimeFind * 1000.0);

						if (MilNumberOfResult > 0) {

							MilModelIndex	= new MIL_INT[MilNumberOfResult];
							MilPosX			= new MIL_DOUBLE[MilNumberOfResult];
							MilPosY			= new MIL_DOUBLE[MilNumberOfResult];
							MilAngle		= new MIL_DOUBLE[MilNumberOfResult];
							MilScore		= new MIL_DOUBLE[MilNumberOfResult];

							ZeroMemory(MilModelIndex, sizeof(MIL_INT) * MilNumberOfResult);
							ZeroMemory(MilPosX, sizeof(MIL_DOUBLE) * MilNumberOfResult);
							ZeroMemory(MilPosY, sizeof(MIL_DOUBLE) * MilNumberOfResult);
							ZeroMemory(MilAngle, sizeof(MIL_DOUBLE) * MilNumberOfResult);
							ZeroMemory(MilScore, sizeof(MIL_DOUBLE) * MilNumberOfResult);

							MmodGetResult(MilModelFinderResult, M_DEFAULT, M_INDEX + M_TYPE_MIL_INT, MilModelIndex);
							MmodGetResult(MilModelFinderResult, M_DEFAULT, M_POSITION_X, MilPosX);
							MmodGetResult(MilModelFinderResult, M_DEFAULT, M_POSITION_Y, MilPosY);
							MmodGetResult(MilModelFinderResult, M_DEFAULT, M_ANGLE, MilAngle);
							MmodGetResult(MilModelFinderResult, M_DEFAULT, M_SCORE, MilScore);

							/////////////////////////////////////////////
							// ���� /////////////////////////////////////
							for (INT nIndexModel = 0; nIndexModel < (INT)MilNumberOfResult; nIndexModel++) {
						
								// ������
								if (!nCountRecursive) {

									stResult.flOffset_M.x	= (FLOAT)MilPosX[nIndexModel];
									stResult.flOffset_M.y	= (FLOAT)MilPosY[nIndexModel];
									dblOffsetX = (DOUBLE)(stResult.flOffset_M.x - stParam.stInspectionInfo.flOffset_M.x);
									dblOffsetY = (DOUBLE)(stResult.flOffset_M.y - stParam.stInspectionInfo.flOffset_M.y);
							
									stResult.nResultOffsetX = T_RESULT_SUCCESS;
									if (!stParam.bUseReverseJudgement && (INT)abs((INT)(dblOffsetX * 100)) > (INT)(stParam.stInspectionInfo.flOffset.x * 100))
										stResult.nResultOffsetX = T_RESULT_FAILURE;

									stResult.nResultOffsetY = T_RESULT_SUCCESS;
									if (!stParam.bUseReverseJudgement && (INT)abs((INT)(dblOffsetY * 100)) > (INT)(stParam.stInspectionInfo.flOffset.y * 100))
										stResult.nResultOffsetY = T_RESULT_FAILURE;
								}

								// ����
								dblAngle = (DOUBLE)MilAngle[nIndexModel];
								dblAngle = abs(dblAngle) > 180 ? abs(dblAngle) - 360 : dblAngle;

								stResult.nResultAngle = T_RESULT_SUCCESS;
								if (!stParam.bUseReverseJudgement && (INT)abs((INT)(dblAngle * 100)) > (INT)(stParam.stInspectionInfo.dblAngle * 100))
									stResult.nResultAngle = T_RESULT_FAILURE;

								// ��Ī��
								dblMatchScore = (DOUBLE)MilScore[nIndexModel];

								stResult.nResultMatchScore = stParam.bUseReverseJudgement ? T_RESULT_FAILURE : T_RESULT_SUCCESS;
								if ((INT)(dblMatchScore * 100) < (INT)(stParam.stInspectionInfo.dblMatchScore * 100))
									stResult.nResultMatchScore = stParam.bUseReverseJudgement ? T_RESULT_SUCCESS : T_RESULT_FAILURE;

								// ���� ����
								nResultInspection = T_RESULT_SUCCESS;
								if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultOffsetX;
								if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultOffsetY;
								if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultAngle;
								if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultMatchScore;
							
								// �հ��̸� �˻� ����
								if (nResultInspection == T_RESULT_SUCCESS) {

									//MessageWindow(cDEBUG, _T("ProcessImage_ModelFind::Found Model Index = %d"), MilModelIndex[nIndexModel]);
									//MessageWindow(cDEBUG, _T("ProcessImage_ModelFind::flOffset=%.2f, %.2f"), dblOffsetX, dblOffsetY);
									//MessageWindow(cDEBUG, _T("ProcessImage_ModelFind::dblAngle=%.2f"), dblAngle);
									//MessageWindow(cDEBUG, _T("ProcessImage_ModelFind::dblMatchScore=%.2f"), dblMatchScore);
							
									stResult.nIndexGeometryFile		= nIndex;
									stResult.nIndexGeometryModel	= (INT)MilModelIndex[nIndexModel];
							
									bFoundModel = TRUE;
									break;
								}
							}

							delete []	MilModelIndex;
							delete []	MilPosX;
							delete []	MilPosY;
							delete []	MilAngle;
							delete []	MilScore;
						}

						MmodFree(MilModelFinderContext);
						MmodFree(MilModelFinderResult);

						if (bFoundModel)	break;
					}
				}

				fileFinder.Close();
			}

			// ��� ����
			stResult.flOffset.x			= (FLOAT)dblOffsetX;
			stResult.flOffset.y			= (FLOAT)dblOffsetY;
			stResult.dblAngle			= dblAngle;
			stResult.dblMatchScore		= dblMatchScore;
			stResult.nResultInspection	= nResultInspection != T_RESULT_SUCCESS ? T_RESULT_FAILURE : nResultInspection;

			// ���μ��� �ð�
			dwTimeProcess = GetTickCount() - dwTimeProcess;

			//MessageWindow(cDEBUG, _T("ProcessImage_ModelFind::dwTimeProcess=%d"), dwTimeProcess);
			//MessageWindow(cDEBUG, _T("----------------------------------------------------------------------------------------------------"));

			// ��ȯ ����
			if (stParam.bUseRecursiveMeasurement) {
			
				stOffsetRecursive.dblX	= (DOUBLE)stResult.flOffset.x;
				stOffsetRecursive.dblY	= (DOUBLE)stResult.flOffset.y;
				stRangeRecursive.dblX	= stParam.stInspectionInfo.flOffset.x * 0.5;
				stRangeRecursive.dblY	= stParam.stInspectionInfo.flOffset.y * 0.5;
				nCountRecursive++;
			}
		}
	
	} while (bResultProcess && stResult.nResultInspection == T_RESULT_SUCCESS && stParam.bUseRecursiveMeasurement && nCountRecursive <= 1);


	/////////////////////////////////////////////////////////////////
	// ���� ���� �̹��� ���� ////////////////////////////////////////
	{
		CString		strFileName	= _T("");
		CFileFind	fileFinder;

		strFileName.Format(_T("%s\\%s.BMP"), m_SystemConfig.GetWorkDirectory(DIR_SAVE_IMAGE), _FILE_VISION_MODEL_FINDER_CLIP);
		if (fileFinder.FindFile(strFileName))
			CFile::Remove(strFileName);

		if (bResultProcess) {
		
			MbufExport(strFileName, M_BMP, MilImageInspection);
		}

		fileFinder.Close();
	}


	/////////////////////////////////////////////////////////////////
	// �˻� �̹��� ���� /////////////////////////////////////////////
	if (bSaveClip && bResultProcess && stResult.nResultInspection != T_RESULT_SUCCESS) {
	
		PMODEL_PROFILE_T		pstModelProfile		= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
		PVPRD_DATA_T			pstVisionSetupInfo	= &m_pstVisionProcedureData[m_stSystemStatus.nCurrentVisionInspectionNo];
		UINT					nInspectionNo		= 0;
		CString					strFileName			= _T("");
		CFileFind				fileFinder;

		// ���� �̸� ����
		strFileName.Format(_T("%s\\T%02d_%02d_%s_%s.JPG"),	pstWorkStatus->szWorkDataSaveDirectory, 
															nTestItemNo + 1,
															m_stSystemStatus.nCurrentVisionInspectionNo + 1,
															g_szTestResultEngS[stResult.nResultInspection],
															pstVisionSetupInfo->szName);

		// �̹��� ���� ����
		if (fileFinder.FindFile(strFileName)) {

			do {
			
				fileFinder.Close();
				strFileName.Empty();
				strFileName.Format(_T("%s\\T%02d_%02d_%s_%s_R%d.JPG"),	pstWorkStatus->szWorkDataSaveDirectory, 
																		nTestItemNo + 1,
																		m_stSystemStatus.nCurrentVisionInspectionNo + 1,
																		g_szTestResultEngS[stResult.nResultInspection],
																		pstVisionSetupInfo->szName,
																		++nInspectionNo);
			
			} while (fileFinder.FindFile(strFileName));
		}

		MbufExport(strFileName, M_JPEG_LOSSY, MilImageInspection);
		SDebugMessage(TRUE, _T("ProcessImage_ModelFind::ExportImage = %s"), strFileName);
		fileFinder.Close();
	}


	/////////////////////////////////////////////////////////////////
	// MIL ���� ���� ////////////////////////////////////////////////
	if (MilImageInspection != M_NULL)		{ MbufFree(MilImageInspection);		/*MessageWindow(cDEBUG, _T("ProcessImage_ModelFind::Release <MilImageInspection>"));*/ }
	if (MilImageGrayInspection != M_NULL)	{ MbufFree(MilImageGrayInspection);	/*MessageWindow(cDEBUG, _T("ProcessImage_ModelFind::Release <MilImageGrayInspection>"));*/ }


	return	bResultProcess;
}


///////////////////////////////////////////////////////////////////////////////
// �̹��� ���μ��� : �÷� �м� ////////////////////////////////////////////////
BOOL CMainApp::ProcessImage_ColorAnalysis(UINT nTestItemNo, UINT nTestStationNo, DPS_POINT2D_T stOriginOffset, VI_PARAM_COLOR_T& stParam, VI_RESULT_COLOR_T& stResult, BOOL bSaveClip /* = TRUE */)
{
	BOOL			bResultProcess			= TRUE;
	BOOL			bFoundColor				= FALSE;

	MIL_ID			MilImageInspection		= M_NULL;
	MIL_ID			MilImageThreshold		= M_NULL;
	MIL_ID			MilImageGrayInspection	= M_NULL;

	MIL_ID			MilColorContext			= M_NULL;
	MIL_ID			MilColorResult			= M_NULL;

	MIL_INT			MilNumSamples			= 0;
	MIL_INT			MilPixelCount			= 0;
	MIL_DOUBLE		MilDistance				= 0;
	MIL_DOUBLE		MilScore				= 0;

	MIL_DOUBLE		MilTimePreProcess		= 0;
	MIL_DOUBLE		MilTimeAnalysis			= 0;

	UINT			nPixelCount				= 0;
	DOUBLE			dblDistance				= 0;
	DOUBLE			dblMatchScore			= 0;

	MIL_INT			MilSizeBand				= 0;
	MIL_INT64		MilBufferAttributes		= M_IMAGE + M_PROC;

	DPS_RECT_T		rectInspectionRegion;
	CRect			rectRegionSearch;
	SIZE			sizeImage;
	
	CString			strFileName				= _T("");
	CFileFind		fileFinder;

	DWORD			dwTimeProcess			= GetTickCount();
	UINT			nResultInspection		= T_RESULT_NONE;
	PWORK_STATUS_T	pstWorkStatus			= GetWorkStatus(nTestStationNo);


	/////////////////////////////////////////////////////////////////
	// �ʱ�ȭ ///////////////////////////////////////////////////////
	ZeroMemory(&stResult, sizeof(VI_RESULT_COLOR_T));

	stResult.nResultInspection = T_RESULT_ERROR;


	/////////////////////////////////////////////////////////////////
	// �Ķ���� �ε� ////////////////////////////////////////////////
	rectInspectionRegion	= stParam.rectInspectionArea;


	/////////////////////////////////////////////////////////////////
	// �÷� ������Ʈ�� ���� üũ ////////////////////////////////////
	bResultProcess = FALSE;
	for (INT nIndex = 0; nIndex < stParam.stInspectionInfo.nNumberOfGeometryFile; nIndex++) {
	
		strFileName = stParam.stInspectionInfo.szFileGeometry[nIndex];
		if (!strFileName.IsEmpty() && fileFinder.FindFile(strFileName))
			bResultProcess = TRUE;

		fileFinder.Close();
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���� ////////////////////////////////////////////////////
	stResult.nResultInspection = T_RESULT_ERROR;

	
	/////////////////////////////////////////////////////////////////
	// ��� ���� ���� ���� //////////////////////////////////////////
	if (bResultProcess) {

		// �̹��� ���� �ε�
		MbufInquire(stParam.MilImageInspection, M_SIZE_X, &sizeImage.cx);
		MbufInquire(stParam.MilImageInspection, M_SIZE_Y, &sizeImage.cy);

		// �˻� ���� ����
		rectRegionSearch.left		= __max(rectInspectionRegion.ptTopLeft.x + (LONG)stOriginOffset.dblX, 0);
		rectRegionSearch.top		= __max(rectInspectionRegion.ptTopLeft.y + (LONG)stOriginOffset.dblY, 0);
		rectRegionSearch.right		= __min(rectInspectionRegion.ptTopLeft.x + (LONG)stOriginOffset.dblX + rectInspectionRegion.sizeRect.cx, sizeImage.cx);
		rectRegionSearch.bottom		= __min(rectInspectionRegion.ptTopLeft.y + (LONG)stOriginOffset.dblY + rectInspectionRegion.sizeRect.cy, sizeImage.cy);

		// ���� �ʱ�ȭ
		if (MilImageInspection != M_NULL) {
			
			MbufFree(MilImageInspection);
			MilImageInspection = M_NULL;
		}

		// ���� ����
		MbufChild2d(stParam.MilImageInspection, 
					rectRegionSearch.left, 
					rectRegionSearch.top, 
					rectRegionSearch.Width(), 
					rectRegionSearch.Height(), 
					&MilImageInspection);

		if (MilImageInspection == M_NULL)		bResultProcess = FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// ��� �÷� �˻� ///////////////////////////////////////////////
	if (bResultProcess) {

		//MessageWindow(cDEBUG, _T("----------------------------------------------------------------------------------------------------"));
		//MessageWindow(cDEBUG, _T("ProcessImage_ColorAnalysis::rectRegionSearch = %d, %d, %d, %d"), rectRegionSearch.left, rectRegionSearch.top, rectRegionSearch.right, rectRegionSearch.bottom);


		strFileName = stParam.stInspectionInfo.szFileGeometry[0];
		if (!strFileName.IsEmpty() && fileFinder.FindFile(strFileName)) {

			McolRestore((MIL_CONST_TEXT_PTR)stParam.stInspectionInfo.szFileGeometry[0], m_MilSystem, M_DEFAULT, &MilColorContext);
			if (MilColorContext) {

				McolAllocResult(m_MilSystem, M_COLOR_MATCHING_RESULT, M_DEFAULT, &MilColorResult);
				if (MilColorResult) {

					MappTimer(M_TIMER_RESET + M_SYNCHRONOUS, M_NULL);
					McolPreprocess(MilColorContext, M_DEFAULT);
					MappTimer(M_TIMER_READ + M_SYNCHRONOUS, &MilTimePreProcess);
					MappTimer(M_TIMER_RESET + M_SYNCHRONOUS, M_NULL);
					McolMatch(MilColorContext, MilImageInspection, M_DEFAULT, M_NULL, MilColorResult, M_DEFAULT);
					MappTimer(M_TIMER_READ + M_SYNCHRONOUS, &MilTimeAnalysis);
					McolInquire(MilColorContext, M_CONTEXT, M_NUMBER_OF_SAMPLES + M_TYPE_MIL_INT, &MilNumSamples);
					if (MilNumSamples > 0) {

						for (UINT nIndex = 0; nIndex < (UINT)MilNumSamples; nIndex++) {
				
							//McolGetResult(MilColorResult, M_DEFAULT, M_SAMPLE_INDEX(nIndex), M_SAMPLE_PIXEL_COUNT, &MilPixelCount);
							McolGetResult(MilColorResult, M_DEFAULT, M_SAMPLE_INDEX(nIndex), M_COLOR_DISTANCE, &MilDistance);
							McolGetResult(MilColorResult, M_DEFAULT, M_SAMPLE_INDEX(nIndex), M_SCORE, &MilScore);

							// �ȼ� ��
							nPixelCount = (UINT)MilPixelCount;
							stResult.nResultPixelCount = T_RESULT_SUCCESS;
							//if (nPixelCount < stParam.stInspectionInfo.nPixelCount)
								//stResult.nResultPixelCount = T_RESULT_FAILURE;

							// �Ÿ�
							dblDistance = (DOUBLE)MilDistance;
							stResult.nResultDistance = T_RESULT_SUCCESS;
							//if (dblDistance < stParam.stInspectionInfo.dblDistance)
								//stResult.nResultDistance = T_RESULT_FAILURE;

							// ��Ī��
							dblMatchScore = (DOUBLE)MilScore;
							stResult.nResultMatchScore = T_RESULT_SUCCESS;
							if ((INT)(dblMatchScore * 100) < (INT)(stParam.stInspectionInfo.dblMatchScore * 100))
								stResult.nResultMatchScore = T_RESULT_FAILURE;

							// ���� ����
							nResultInspection = T_RESULT_SUCCESS;
							if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultPixelCount;
							if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultDistance;
							if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultMatchScore;

							// �հ��̸� �м� ����
							if (nResultInspection == T_RESULT_SUCCESS) {
							
								stResult.nIndexGeometrySample = nIndex;
								break;
							}
						}
					}
					
					McolFree(MilColorResult);
				}

				McolFree(MilColorContext);
			}
		}

		fileFinder.Close();

		// ��� ����
		stResult.nPixelCount		= nPixelCount;
		stResult.dblDistance		= dblDistance;
		stResult.dblMatchScore		= dblMatchScore;
		stResult.nResultInspection	= nResultInspection;

		// ���μ��� �ð�
		dwTimeProcess = GetTickCount() - dwTimeProcess;

		//MessageWindow(cDEBUG, _T("ProcessImage_ColorAnalysis::dwTimeProcess=%d"), dwTimeProcess);
		//MessageWindow(cDEBUG, _T("----------------------------------------------------------------------------------------------------"));
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���� �̹��� ���� ////////////////////////////////////////
	{
		CString		strFileName	= _T("");
		CFileFind	fileFinder;

		strFileName.Format(_T("%s\\%s.BMP"), m_SystemConfig.GetWorkDirectory(DIR_SAVE_IMAGE), _FILE_VISION_COLOR_ANALYSIS_CLIP);
		if (fileFinder.FindFile(strFileName))
			CFile::Remove(strFileName);

		if (bResultProcess) {
		
			MbufExport(strFileName, M_BMP, MilImageInspection);
		}

		fileFinder.Close();
	}


	/////////////////////////////////////////////////////////////////
	// �˻� �̹��� ���� /////////////////////////////////////////////
	if (bSaveClip && bResultProcess && stResult.nResultInspection != T_RESULT_SUCCESS) {
	
		PMODEL_PROFILE_T		pstModelProfile		= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
		PVPRD_DATA_T			pstVisionSetupInfo	= &m_pstVisionProcedureData[m_stSystemStatus.nCurrentVisionInspectionNo];
		UINT					nInspectionNo		= 0;
		CString					strFileName			= _T("");
		CFileFind				fileFinder;

		// ���� �̸� ����
		strFileName.Format(_T("%s\\T%02d_%02d_%s_%s.JPG"),	pstWorkStatus->szWorkDataSaveDirectory, 
															nTestItemNo + 1,
															m_stSystemStatus.nCurrentVisionInspectionNo + 1,
															g_szTestResultEngS[stResult.nResultInspection],
															pstVisionSetupInfo->szName);

		// �̹��� ���� ����
		if (fileFinder.FindFile(strFileName)) {

			do {
			
				fileFinder.Close();
				strFileName.Empty();
				strFileName.Format(_T("%s\\T%02d_%02d_%s_%s_R%d.JPG"),	pstWorkStatus->szWorkDataSaveDirectory, 
																		nTestItemNo + 1,
																		m_stSystemStatus.nCurrentVisionInspectionNo + 1,
																		g_szTestResultEngS[stResult.nResultInspection],
																		pstVisionSetupInfo->szName,
																		++nInspectionNo);
			
			} while (fileFinder.FindFile(strFileName));
		}

		MbufExport(strFileName, M_JPEG_LOSSY, MilImageInspection);
		SDebugMessage(TRUE, _T("ProcessImage_ColorAnalysis::ExportImage = %s"), strFileName);
		fileFinder.Close();
	}


	/////////////////////////////////////////////////////////////////
	// MIL ���� ���� ////////////////////////////////////////////////
	if (MilImageInspection != M_NULL)		{ MbufFree(MilImageInspection);		/*MessageWindow(cDEBUG, _T("ProcessImage_ColorAnalysis::Release <MilImageInspection>"));*/ }


	return	bResultProcess;
}







///////////////////////////////////////////////////////////////////////////////////////////////////
// ���� ���� ���� ���� ////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ���� ���α׷� ��ȣ ���� ////////////////////////////////////////////////////
BOOL CMainApp::VISION_SelectProgramNo(BOOL bEnable, INT nProgramNo /* = 0 */)
{
	/////////////////////////////////////////////////////////////////
	// ��� Ȱ��ȭ //////////////////////////////////////////////////
	if (bEnable) {

		/////////////////////////////////////////////////////////////
		// ������ ��ȣ üũ /////////////////////////////////////////
		if (nProgramNo < 0 || nProgramNo > MAX_VISION_PROGRAM_NO)
			return	FALSE;


		/////////////////////////////////////////////////////////////
		// ��ȣ ���� ////////////////////////////////////////////////
		SetDOStatus(nProgramNo & 0x01 ? DO_ON : DO_OFF, DO_SIG_S02_VISION_SELECT_0);
		SetDOStatus(nProgramNo & 0x02 ? DO_ON : DO_OFF, DO_SIG_S02_VISION_SELECT_1);
		SetDOStatus(nProgramNo & 0x04 ? DO_ON : DO_OFF, DO_SIG_S02_VISION_SELECT_2);
		SetDOStatus(nProgramNo & 0x08 ? DO_ON : DO_OFF, DO_SIG_S02_VISION_SELECT_3);
		SetDOStatus(nProgramNo & 0x10 ? DO_ON : DO_OFF, DO_SIG_S02_VISION_SELECT_4);


	/////////////////////////////////////////////////////////////////
	// ��� ��Ȱ��ȭ ////////////////////////////////////////////////
	} else {

		SetDOStatus(DO_OFF, DO_SIG_S02_VISION_SELECT_0);
		SetDOStatus(DO_OFF, DO_SIG_S02_VISION_SELECT_1);
		SetDOStatus(DO_OFF, DO_SIG_S02_VISION_SELECT_2);
		SetDOStatus(DO_OFF, DO_SIG_S02_VISION_SELECT_3);
		SetDOStatus(DO_OFF, DO_SIG_S02_VISION_SELECT_4);
	}


	return	TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// ���� ��� �������� /////////////////////////////////////////////////////////
BOOL CMainApp::VISION_ImportResult(const CString& strFileName, VISION_RESULT_T& stResult)
{
	BOOL			bIsFile			= FALSE;
	BOOL			bResult			= FALSE;

	CString			strBuffer		= _T("");
	CString			strRead			= _T("");

	LPTSTR			szType			= NULL;
	LPTSTR			szToken			= NULL;

	TCHAR			szTemp[MAX_STRVALUE];

	CFileFind		fileFinder;
	CStdioFile		fileResult;


	/////////////////////////////////////////////////////////////////
	// ��� ���� �ε� ///////////////////////////////////////////////
	TRY {

		INT		nValue	= 0;
		CString	strTemp	= _T("");

		if (bResult = fileResult.Open(strFileName, CStdioFile::modeRead)) {

			MessageWindow(cDEBUG, _T("[VISION IMPORT] File Size = %d"), fileResult.GetLength());
			bResult = fileResult.GetLength() > 0 ? TRUE : FALSE;

			if (bResult) {

				ZeroMemory(&stResult, sizeof(VISION_RESULT_T));

				fileResult.SeekToBegin();
				while (fileResult.ReadString(strRead)) {

					/////////////////////////////////////////////////
					strBuffer.AppendFormat(_T("%s\r\n"), strRead);
					MessageWindow(cDEBUG, _T("[READ] %s"), strRead);

					/////////////////////////////////////////////////
					strRead.Remove(' ');	// ���� ����
					
					/////////////////////////////////////////////////
					_stprintf_s(szTemp, MAX_STRVALUE, _T("%s"), strRead);
					szToken	= _tcstok_s(szTemp, _T("\t"), &szType);
					if (szToken) {

						// ���α׷� ��ȣ
						if (_tcsncmp(szToken, _T("ProgramNo."), 10) == 0) {

							szToken	= _tcstok_s(NULL, _T("\t"), &szType);
							if (szToken) {
										
								nValue = _ttoi(szToken);
								stResult.nProgramNo = (UINT)nValue;
							}

							continue;
						}

						// Ʈ���� ��ȣ
						if (_tcsncmp(szToken, _T("TriggerNo."), 10) == 0) {

							szToken	= _tcstok_s(NULL, _T("\t"), &szType);
							if (szToken) {
										
								nValue = _ttoi(szToken);
								stResult.nTriggerNo = (UINT)nValue;
							}

							continue;
						}

						// �˻� �ð�
						if (_tcsncmp(szToken, _T("TIME[ms]"), 8) == 0) {

							szToken	= _tcstok_s(NULL, _T("\t"), &szType);
							if (szToken) {
										
								nValue = _ttoi(szToken);
								stResult.nTimeInspection = (UINT)nValue;
							}

							continue;
						}

						// ���� ���
						if (_tcsncmp(szToken, _T("TotalStatus"), 11) == 0) {

							szToken	= _tcstok_s(NULL, _T("\t"), &szType);
							if (szToken) {
										
								if (_tcsncmp(szToken, _T("OK"), 2) == 0)	stResult.nResultFinal = T_RESULT_SUCCESS;
								else										stResult.nResultFinal = T_RESULT_FAILURE;
							}

							continue;
						}

						// ���� ��ġ ���
						for (UINT nIndex = 0; nIndex < MAX_VISION_USER_RECT; nIndex++) {

							strTemp.Empty();
							strTemp.Format(_T("Tool%02d:"), nIndex + 1);

							if (_tcsncmp(szToken, strTemp, 7) == 0) {

								szToken	= _tcstok_s(NULL, _T("\t"), &szType);
								if (szToken) {
										
									if (_tcsncmp(szToken, _T("OK"), 2) == 0)	stResult.nResultPoint[nIndex] = T_RESULT_SUCCESS;
									else										stResult.nResultPoint[nIndex] = T_RESULT_FAILURE;
								}

								continue;
							}
						}
					}
				}
			}

			fileResult.Close();
		}

	} CATCH (CFileException, e) {
		e->ReportError();
	} END_CATCH


	MessageWindow(cDEBUG, _T("[VISION IMPORT : %s] Result = %d"), strFileName, bResult);


	return	bResult;
}



///////////////////////////////////////////////////////////////////////////////
// ���� �̹��� �˻� ///////////////////////////////////////////////////////////
BOOL CMainApp::VISION_GetInspectionImage(CString& strFileName)
{
	BOOL			bIsFile			= FALSE;
	BOOL			bIsFoundImage	= FALSE;

	CDpsStringArray	strArrayFiles;
	CFileFind		fileFinder;


	/////////////////////////////////////////////////////////////////
	// ���� �˻� ////////////////////////////////////////////////////
	strFileName.Format(_T("%s\\*.BMP"), m_SystemConfig.GetWorkDirectory(DIR_IMPORT_DATA));
	bIsFile	= fileFinder.FindFile(strFileName);

	while (bIsFile) {

		bIsFile		= fileFinder.FindNextFile();
		strFileName	= fileFinder.GetFilePath();

		if (!fileFinder.IsDots() && !fileFinder.IsDirectory()) {

			bIsFoundImage = TRUE;
			strArrayFiles.Add(strFileName);
			MessageWindow(cDEBUG, _T("VISION_GetInspectionImage::Find Files = %s"), strFileName);
		}
	}

	fileFinder.Close();


	/////////////////////////////////////////////////////////////////
	// ���� ���� ////////////////////////////////////////////////////
	if (strArrayFiles.GetCount()) {

		strArrayFiles.Sort(DPS_SORT_DESC);
		strFileName = strArrayFiles.GetAt(0);
	}


	return	bIsFoundImage;
}







///////////////////////////////////////////////////////////////////////////////////////////////////
// �۾� ���μ��� //////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// �۾� ���μ��� ���� /////////////////////////////////////////////////////////
BOOL CMainApp::StartWorkProcess(void)
{
	PTHREAD_PARAM_T	pstParam	= NULL;
	BOOL			bResult		= TRUE;


	/////////////////////////////////////////////////////////////////
	// ���� ������ //////////////////////////////////////////////////
	m_bExitThread[THREAD_MAIN]	= FALSE;
	m_pThread[THREAD_MAIN]		= ::AfxBeginThread(ThreadFuncMain, this, THREAD_PRIORITY_NORMAL);
	if (m_pThread[THREAD_MAIN]) {
	
		m_pThread[THREAD_MAIN]->m_bAutoDelete = FALSE;
		bResult &= TRUE;
	
	} else {
	
		bResult = FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// �ý��� ������ ////////////////////////////////////////////////
	pstParam = new THREAD_PARAM_T;
	ZeroMemory(pstParam, sizeof(THREAD_PARAM_T));
	pstParam->pMainApp	= this;
	pstParam->nThreadID	= THREAD_SUB_1;

	m_bExitThread[THREAD_SUB_1]	= FALSE;
	m_pThread[THREAD_SUB_1]		= ::AfxBeginThread(ThreadFuncSub, pstParam, THREAD_PRIORITY_NORMAL);
	if (m_pThread[THREAD_SUB_1]) {
	
		m_pThread[THREAD_SUB_1]->m_bAutoDelete = FALSE;
		bResult &= TRUE;
	
	} else {
	
		bResult = FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// �ý��� ������ ////////////////////////////////////////////////
	m_bExitThread[THREAD_SYSTEM]	= FALSE;
	m_pThread[THREAD_SYSTEM]		= ::AfxBeginThread(ThreadFuncSystem, this, THREAD_PRIORITY_NORMAL);
	if (m_pThread[THREAD_SYSTEM]) {
	
		m_pThread[THREAD_SYSTEM]->m_bAutoDelete = FALSE;
		bResult &= TRUE;
	
	} else {
	
		bResult = FALSE;
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// �۾� ���μ��� ���� /////////////////////////////////////////////////////////
void CMainApp::StopWorkProcess(void)
{
	// ������ ����
	for (UINT nIndex = 0; nIndex < MAX_WORK_THREAD; nIndex++) {

		if (m_pThread[nIndex]) {

			// ������ ����
			m_csExitThread[nIndex].Lock();
			m_bExitThread[nIndex] = TRUE;
			m_csExitThread[nIndex].Unlock();

			// ������ ���� ���
			DWORD	dwRetCode = ::WaitForSingleObject(m_pThread[nIndex]->m_hThread, THREAD_WAIT_TIME);
			if (dwRetCode != WAIT_OBJECT_0) {

				// ���� ����
				::TerminateThread(m_pThread[nIndex]->m_hThread, 0);
				CloseHandle(m_pThread[nIndex]->m_hThread);
			}

			// ������ ��ü ����
			m_pThread[nIndex]->m_hThread = NULL;
			delete	m_pThread[nIndex];
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� : �ý��� //////////////////////////////////////////////////////////
void CMainApp::ProcessSystem(void)
{
	static		UINT		nSysBeepStep			= 0;

	static		BOOL		bOnManualControlMode	= FALSE;
	static		BOOL		bOnAlarm				= FALSE;
	static		BOOL		bOnInsideLamp			= FALSE;

	static		BOOL		bEnableTLamp			= FALSE;
	static		BOOL		bEnableTBuzz			= FALSE;

	static		LTimerMsec	LTimerTLamp;
	static		LTimerMsec	LTimerTBuzz;
	static		LTimerMsec	LTimerTBeep;

	static		CHAR		szRcvdPacket[COMM_PACKET_SIZE];
	static		CHAR		szTemp[MAX_STRVALUE];
	static		UINT		nRcvdPacketIndex		= 0;
	static		BYTE		byRcvdPacket			= 0;

	static		UINT		nDO_SIG_TL_RED;
	static		UINT		nDO_SIG_TL_YELLOW;
	static		UINT		nDO_SIG_TL_GREEN;
	static		UINT		nDO_SIG_TL_BUZZER;

	BOOL					bOnUpdateUI				= FALSE;
	UI_PARAM_UPDATE_T		stParamUI;


	/////////////////////////////////////////////////////////////////
	// ���� �ʱ�ȭ //////////////////////////////////////////////////
	ZeroMemory(&stParamUI, sizeof(UI_PARAM_UPDATE_T));

	nDO_SIG_TL_RED		= m_nTypeMachine == MC_TYPE_1 ? DO_SIG_TL1_RED : DO_SIG_TL2_RED;
	nDO_SIG_TL_YELLOW	= m_nTypeMachine == MC_TYPE_1 ? DO_SIG_TL1_YELLOW : DO_SIG_TL2_YELLOW;
	nDO_SIG_TL_GREEN	= m_nTypeMachine == MC_TYPE_1 ? DO_SIG_TL1_GREEN : DO_SIG_TL2_GREEN;
	nDO_SIG_TL_BUZZER	= m_nTypeMachine == MC_TYPE_1 ? DO_SIG_TL1_BUZZER : DO_SIG_TL2_BUZZER;


	/////////////////////////////////////////////////////////////////
	// ���� ���� ��� ///////////////////////////////////////////////
	bOnManualControlMode  = FALSE;
	bOnManualControlMode |= m_stSystemStatus.bOnManualControlDIO;
	for (UINT nIndex = 0; nIndex < MAX_STATION; nIndex++)
		bOnManualControlMode |= m_stSystemStatus.bIsManualControl[nIndex];


	/////////////////////////////////////////////////////////////////
	// �˶� ���� ���� ///////////////////////////////////////////////
	bOnAlarm	= FALSE;
	bOnAlarm   |= m_stSystemStatus.bOnAlarmSystem;
	for (UINT nIndex = 0; nIndex < MAX_STATION; nIndex++)
		bOnAlarm |= m_stSystemStatus.bOnAlarmStation[nIndex];


	/////////////////////////////////////////////////////////////////
	// �ý��� ���� ����� ���� //////////////////////////////////////
	if (m_pSysStateMonitorWnd) {

		if (m_stSystemStatus.bOnMachineInitialize)				m_pSysStateMonitorWnd->SetSystemState(S_STATE_MACHINE_INIT);					// ��� �ʱ�ȭ��
		else if (!m_stSystemStatus.bResultSystemInitialize)		m_pSysStateMonitorWnd->SetSystemState(S_STATE_SYSTEM_INIT_FAIL, TRUE);			// �ý��� �ʱ�ȭ ����
		else if (m_nTypeMachine == MC_TYPE_1 && !m_stSystemStatus.bResultMachineInitialize)	m_pSysStateMonitorWnd->SetSystemState(S_STATE_MACHINE_INIT_FAIL, TRUE);			// ��� �ʱ�ȭ ����
		else if (m_stSystemStatus.bOnEmergencyStop)				m_pSysStateMonitorWnd->SetSystemState(S_STATE_EMERGENCY_STOP, TRUE);			// ��� ����
		else if (m_stSystemStatus.bOnAirSupplyFail)				m_pSysStateMonitorWnd->SetSystemState(S_STATE_AIR_SUPPLY_FAIL, TRUE);			// ���� ���� ����
		else if (bOnAlarm)										m_pSysStateMonitorWnd->SetSystemState(S_STATE_WARNING, TRUE);					// �ý��� �˶�
		else if (m_stSystemStatus.bOnDoorOpened)				m_pSysStateMonitorWnd->SetSystemState(S_STATE_DOOR_OPEN, TRUE);					// ���� ����
		else if (m_stSystemStatus.bOnWaitForUser)				m_pSysStateMonitorWnd->SetSystemState(S_STATE_WAIT_USER);						// ����� �Է� ���
		else if (m_stSystemStatus.bOnTestMode)					m_pSysStateMonitorWnd->SetSystemState(S_STATE_TEST_MODE);						// �׽�Ʈ ���
		else if (m_stSystemStatus.bOnPassDrive)					m_pSysStateMonitorWnd->SetSystemState(S_STATE_PASS_MODE);						// �н� ���
		else if (bOnManualControlMode)							m_pSysStateMonitorWnd->SetSystemState(S_STATE_MANUAL_MODE);						// ���� ���
		else if (m_stSystemStatus.bOnPause)						m_pSysStateMonitorWnd->SetSystemState(S_STATE_PAUSE);							// �Ͻ� ����
		else if (m_stSystemStatus.bOnOperatingStopReservated)	m_pSysStateMonitorWnd->SetSystemState(S_STATE_OP_STOP_RESERVATE);				// �۾� ���� ����
		else if (m_stSystemStatus.bOnOperating)					m_pSysStateMonitorWnd->SetSystemState(S_STATE_OP_START);						// �۾� ����
		else													m_pSysStateMonitorWnd->SetSystemState(S_STATE_OP_STOP);							// �۾� ����
	}


	/////////////////////////////////////////////////////////////////
	// Ÿ������ ���μ��� ////////////////////////////////////////////

	///////////////////////////////////////////////////////
	// �ý��� �˶� ���� ///////////////////////////////////
	if (m_stSystemStatus.bOnEmergencyStop || m_stSystemStatus.bOnAirSupplyFail || !m_stSystemStatus.bResultSystemInitialize) {

		SetDOStatus(DO_OFF, nDO_SIG_TL_YELLOW);

		// ���� ���� ����
		if (LTimerTLamp.Verify()) {

			bEnableTLamp = !bEnableTLamp;
			SetDOStatus(bEnableTLamp ? DO_ON : DO_OFF, nDO_SIG_TL_RED);
			LTimerTLamp.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_LAMP));
		}

	///////////////////////////////////////////////////////
	// �Ϲ� �˶� ���� /////////////////////////////////////
	} else if (bOnAlarm || m_stSystemStatus.bOnDoorOpened) {

		SetDOStatus(DO_OFF, nDO_SIG_TL_RED);

		// Ȳ�� ���� ����
		if (LTimerTLamp.Verify()) {

			bEnableTLamp = !bEnableTLamp;
			SetDOStatus(bEnableTLamp ? DO_ON : DO_OFF, nDO_SIG_TL_YELLOW);
			LTimerTLamp.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_LAMP));
		}

	///////////////////////////////////////////////////////
	// ����� �Է� ��� ���� //////////////////////////////
	} else if (m_stSystemStatus.bOnWaitForUser) {

		SetDOStatus(DO_OFF, nDO_SIG_TL_RED);

		// Ȳ�� ���� ����
		if (LTimerTLamp.Verify()) {

			bEnableTLamp = !bEnableTLamp;
			SetDOStatus(bEnableTLamp ? DO_ON : DO_OFF, nDO_SIG_TL_YELLOW);
			LTimerTLamp.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_LAMP));
		}

	///////////////////////////////////////////////////////
	// ���� ���� //////////////////////////////////////////
	} else if (m_stSystemStatus.bOnOperating) {

		SetDOStatus(DO_ON,  nDO_SIG_TL_GREEN);			// ��� ���� ����
		SetDOStatus(DO_OFF, nDO_SIG_TL_YELLOW);			// Ȳ�� ���� �ҵ�
		SetDOStatus(DO_OFF, nDO_SIG_TL_RED);			// ���� ���� �ҵ�

	///////////////////////////////////////////////////////
	// �⺻ ���� //////////////////////////////////////////
	} else {

		SetDOStatus(DO_OFF, nDO_SIG_TL_YELLOW);			// Ȳ�� ���� �ҵ�
		SetDOStatus(DO_OFF, nDO_SIG_TL_RED);			// ���� ���� �ҵ�

		// ��� ���� ����
		if (LTimerTLamp.Verify()) {

			bEnableTLamp = !bEnableTLamp;
			SetDOStatus(bEnableTLamp ? DO_ON : DO_OFF, nDO_SIG_TL_GREEN);
			LTimerTLamp.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_LAMP));
		}
	}


	/////////////////////////////////////////////////////////////////
	// Ÿ������ ���� ���� ///////////////////////////////////////////
	if (m_stSystemStatus.bOnBuzzer) {

		// ���� ON/OFF
		if (LTimerTBuzz.Verify()) {

			bEnableTBuzz = !bEnableTBuzz;
			SetDOStatus(bEnableTBuzz ? DO_ON : DO_OFF, nDO_SIG_TL_BUZZER);
			LTimerTBuzz.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_BUZZER));
		}

	} else {

		// ������ ���°� �ƴϸ�, ���� OFF
		if (!m_stSystemStatus.bOnBeep)	SetDOStatus(DO_OFF, nDO_SIG_TL_BUZZER);
	}


	/////////////////////////////////////////////////////////////////
	// ������ ���μ��� //////////////////////////////////////////////
	switch (nSysBeepStep) {

		case	0		:
							if (m_stSystemStatus.nBeepCount) {

								m_stSystemStatus.bOnBeep = TRUE;
								nSysBeepStep++;
								break;
							}

							m_stSystemStatus.bOnBeep = FALSE;
							break;

		case	1		:
							if (LTimerTBeep.Verify()) {

								SetDOStatus(DO_ON, nDO_SIG_TL_BUZZER);
								LTimerTBeep.Start(100);

								nSysBeepStep++;
							}

							break;

		case	2		:
							if (LTimerTBeep.Verify()) {

								SetDOStatus(DO_OFF, nDO_SIG_TL_BUZZER);
								nSysBeepStep++;
							}

							break;

		case	3		:
							if (m_stSystemStatus.nBeepCount)
								m_stSystemStatus.nBeepCount--;

							LTimerTBeep.Start(70);
							nSysBeepStep = 0;
							break;
	}


	/////////////////////////////////////////////////////////////////
	// ������Ʈ UI //////////////////////////////////////////////////
	if (bOnUpdateUI) {

		PUI_PARAM_UPDATE_T	pstParamUI	= new (std::nothrow) UI_PARAM_UPDATE_T;
		if (pstParamUI) {

			*pstParamUI = stParamUI;

			if (m_pMainWnd && m_pMainWnd->GetSafeHwnd())
				m_pMainWnd->PostMessage(UM_MAIN_UPDATE_UI, (WPARAM)pstParamUI);
		}
	}
}

void CMainApp::ProcessSystemSub01(UINT nSTATION_NO)
{

}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� : ���� ���� ///////////////////////////////////////////////////////
void CMainApp::ProcessErrorDetect(void)
{
	static		LTimerTMsec		LTimerVacuum;

	BOOL						bOnUpdateUI	= FALSE;
	UI_PARAM_UPDATE_T			stParamUI;


	/////////////////////////////////////////////////////////////////
	// ���� �ʱ�ȭ //////////////////////////////////////////////////
	ZeroMemory(&stParamUI, sizeof(UI_PARAM_UPDATE_T));


	/////////////////////////////////////////////////////////////////
	// ���� ���� üũ ///////////////////////////////////////////////
	if (!m_SystemConfig.UseSystemOption(SOPT_DISABLE_SAFETY_AREA)) {
	
		// �����̼� #1
		//m_stSystemStatus.bOnSafetyDetected[STATION_1][STN1_SUB_COMMON_1] = !GetDIStatus(DI_SENS_S10A_DETECT_SAFETY_1) | !GetDIStatus(DI_SENS_S10A_DETECT_SAFETY_2) | !GetDIStatus(DI_SENS_S10A_DETECT_SAFETY_3);
		//m_stSystemStatus.bOnSafetyDetected[STATION_1][STN1_SUB_COMMON_2] = !GetDIStatus(DI_SENS_S10B_DETECT_SAFETY_1) | !GetDIStatus(DI_SENS_S10A_DETECT_SAFETY_2) | !GetDIStatus(DI_SENS_S10B_DETECT_SAFETY_3);
			
	} else {
	
		ZeroMemory(m_stSystemStatus.bOnSafetyDetected, sizeof(BOOL) * MAX_STATION * MAX_SUB_STATION);
	}


	/////////////////////////////////////////////////////////////////
	// �ҷ��� FULL ���� üũ ////////////////////////////////////////
// 	static		UINT			nDI_SENS_DETECT_NG_FULL;
// 	static		BOOL			bIsFullBoxNG[MAX_STATION];
// 	static		LTimerMsec		LTimerNGBox[MAX_STATION];
// 
// 	for (UINT nStationNo = 0; nStationNo < MAX_STATION; nStationNo++) {
// 
// 		if (nStationNo == STATION_5 || nStationNo == STATION_16) {
// 
// 			switch (nStationNo) {
// 			
// 				case	STATION_5	:	nDI_SENS_DETECT_NG_FULL = DI_SENS_S05_UNLOAD_DETECT_PRODUCT;	break;
// 				case	STATION_16	:	nDI_SENS_DETECT_NG_FULL = DI_SENS_S16_UNLOAD_DETECT_PRODUCT;	break;
// 			}
// 
// 			if (GetDIStatus(nDI_SENS_DETECT_NG_FULL)) {
// 	
// 				if (!bIsFullBoxNG[nStationNo]) {
// 		
// 					LTimerNGBox[nStationNo].Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_NG_BOX_FULL));
// 					bIsFullBoxNG[nStationNo] = TRUE;
// 
// 				} else {
// 		
// 					if (LTimerNGBox[nStationNo].Verify())
// 						m_stSystemStatus.bIsFullBoxNG[nStationNo] = TRUE;
// 				}
// 	
// 			} else {
// 	
// 				bIsFullBoxNG[nStationNo]					= FALSE;
// 				m_stSystemStatus.bIsFullBoxNG[nStationNo]	= FALSE;
// 			}
// 		}
// 	}


	/////////////////////////////////////////////////////////////////
	// ������Ʈ UI //////////////////////////////////////////////////
	if (bOnUpdateUI) {

		PUI_PARAM_UPDATE_T		pstParamUI	= new (std::nothrow) UI_PARAM_UPDATE_T;
		if (pstParamUI) {

			*pstParamUI = stParamUI;

			if (m_pMainWnd && m_pMainWnd->GetSafeHwnd())
				m_pMainWnd->PostMessage(UM_MAIN_UPDATE_UI, (WPARAM)pstParamUI);
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� : ��� üũ ///////////////////////////////////////////////////////
void CMainApp::ProcessCheckEmergency(void)
{
	static	UINT			nCurrentStep		= 0;
	static	UINT			nPreviousStep		= 0;

	static	LTimerMsec		LTimerProceed;
	static	LTimerMsec		LTimerTimeOut;
	static	LTimerMsec		LTimerSystemMonitor;

	BOOL					bOnError			= FALSE;
	BOOL					bOnErrorClear		= FALSE;
	BOOL					bDI_EMERGENCY_STOP	= !GetDIStatus(DI_SIG_EMERGENCY_STOP_1) | !GetDIStatus(DI_SIG_EMERGENCY_STOP_2);


	/////////////////////////////////////////////////////////////////
	//if (m_nTypeMachine == MC_TYPE_2)	bDI_EMERGENCY_STOP |= !GetDIStatus(DI_SIG_EMERGENCY_STOP_2);


	/////////////////////////////////////////////////////////////////
	// ���� ���μ��� ////////////////////////////////////////////////
	switch (nCurrentStep) {

		case	0		:
							nCurrentStep = 100;
							break;

		case	100		:
							if (m_stSystemStatus.nDeviceStatus[SD_DIO_1] == DS_NORMAL) {

								nCurrentStep = 110;
								break;
							}

							// ��� ���� �÷��� ����
							m_stSystemStatus.bOnEmergencyStop = FALSE;

							nCurrentStep = 190;
							break;

		case	110		:
							if (!m_stSystemStatus.bOnEmergencyStop && bDI_EMERGENCY_STOP)		nCurrentStep = 120;
							else if (m_stSystemStatus.bOnEmergencyStop && !bDI_EMERGENCY_STOP)	nCurrentStep = 130;
							else																nCurrentStep = 190;

							break;

		// ���� ����
		case	120		:
							// ��� ���� �÷��� ����
							m_stSystemStatus.bOnEmergencyStop = TRUE;

							// ����� �޼��� ����
							m_stSystemStatus.nPreviousUserMessage	= UMSG_NONE;
							m_stSystemStatus.nCurrentUserMessage	= UMSG_ERROR_EMERGENCY_STOP;

							// ���� ���� ����
							for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++) {

								Motion_Stop_E(nAxisNo);
								Motion_Stop_E(nAxisNo);
								AxmSignalServoOn(nAxisNo, DISABLE);
							}

							// ���� �극��ũ ����
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z1);
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z2);
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z3);
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z4);

							bOnError	 = TRUE;
							nCurrentStep = 190;
							break;

		// ���� ����
		case	130		:
							// ��� ���� �÷��� ����
							m_stSystemStatus.bOnEmergencyStop = FALSE;

							// ����� �޼��� �ʱ�ȭ
							ClearUserMessage();

							bOnErrorClear = TRUE;
							nCurrentStep  = 190;
							break;

		case	190		:
							nCurrentStep = 0;
							break;
	}


	/////////////////////////////////////////////////////////////////
	// ���� �߻� ////////////////////////////////////////////////////
	if (bOnError) {

		PERROR_CODE_T pstErrorCode = new (std::nothrow) ERROR_CODE_T;
		if (pstErrorCode) {

			ZeroMemory(pstErrorCode, sizeof(ERROR_CODE_T));
			pstErrorCode->nErrorCode = ERROR_EMERGENCY_STOP;

			if (m_pSysHistoryDlg)	m_pSysHistoryDlg->SendMessage(UM_HISTORY_ON_ERROR, (WPARAM)pstErrorCode);
			else					delete	pstErrorCode;
		}

		// �Ͻ� ����
		if (m_stSystemStatus.bOnOperating) {

			m_stSystemStatus.bOnPause = TRUE;
			if (m_pMainWnd && m_pMainWnd->GetSafeHwnd())
				m_pMainWnd->PostMessage(UM_MAIN_PAUSE);
		}
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���� ////////////////////////////////////////////////////
	if (bOnErrorClear) {

		if (m_pSysHistoryDlg) {

			if (m_stSystemStatus.nCurrentErrorCode == ERROR_AIR_PRESSURE)
				m_pSysHistoryDlg->PostMessage(UM_HISTORY_CLEAR);
		}
	}


	/////////////////////////////////////////////////////////////////
	// ���� ����͸� ////////////////////////////////////////////////
	if (LTimerSystemMonitor.Verify()) {

		if (nPreviousStep != nCurrentStep) {

			nPreviousStep = nCurrentStep;
			if (m_pSysMonitorDlg && m_pSysMonitorDlg->GetSafeHwnd()) {

				//m_pSysMonitorDlg->PostMessage(UM_SYSM_UPDATE_STEP, PSTEP_PROC_EMG, nCurrentStep);
				LTimerSystemMonitor.Start(DLY_REFRESH_SYSTEM_MONITOR);
			}
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� : ���� üũ ///////////////////////////////////////////////////////
void CMainApp::ProcessCheckAirPressure(void)
{
	static	UINT			nCurrentStep		= 0;
	static	UINT			nPreviousStep		= 0;

	static	LTimerMsec		LTimerProceed;
	static	LTimerMsec		LTimerTimeOut;

	BOOL					bOnError			= FALSE;
	BOOL					bOnErrorClear		= FALSE;
	BOOL					bDI_AIR_PRESSURE	= !GetDIStatus(DI_SIG_AIR_PRESSURE);


	/////////////////////////////////////////////////////////////////
	// ���� ���μ��� ////////////////////////////////////////////////
	switch (nCurrentStep) {

		case	0		:
							nCurrentStep = 100;
							break;

		case	100		:
							if (!m_SystemConfig.UseSystemOption(SOPT_DISABLE_AIR_PRESSURE)) {

								if (m_stSystemStatus.nDeviceStatus[SD_DIO_1] == DS_NORMAL) {

									nCurrentStep = 110;
									break;
								}
							}

							// ���� ���� �÷��� ����
							m_stSystemStatus.bOnAirSupplyFail = FALSE;

							nCurrentStep = 190;
							break;

		case	110		:
							if (!m_stSystemStatus.bOnAirSupplyFail && bDI_AIR_PRESSURE)			nCurrentStep = 120;
							else if (m_stSystemStatus.bOnAirSupplyFail && !bDI_AIR_PRESSURE)	nCurrentStep = 130;
							else																nCurrentStep = 190;

							break;

		// ���� ����
		case	120		:
							LTimerProceed.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_AIR_PRESSURE));
							nCurrentStep++;
							break;

		case	121		:
							if (bDI_AIR_PRESSURE) {

								if (LTimerProceed.Verify())
									nCurrentStep++;

								break;
							}

							nCurrentStep = 190;
							break;

		case	122		:
							// ���� ���� �÷��� ����
							m_stSystemStatus.bOnAirSupplyFail = TRUE;

							bOnError	 = TRUE;
							nCurrentStep = 190;
							break;

		// ���� ����
		case	130		:
							// ���� ���� �÷��� ����
							m_stSystemStatus.bOnAirSupplyFail = FALSE;

							bOnErrorClear = TRUE;
							nCurrentStep  = 190;
							break;

		case	190		:
							nCurrentStep = 0;
							break;
	}


	/////////////////////////////////////////////////////////////////
	// ���� �߻� ////////////////////////////////////////////////////
	if (bOnError) {

		PERROR_CODE_T pstErrorCode = new (std::nothrow) ERROR_CODE_T;
		if (pstErrorCode) {

			ZeroMemory(pstErrorCode, sizeof(ERROR_CODE_T));
			pstErrorCode->nErrorCode = ERROR_AIR_PRESSURE;

			if (m_pSysHistoryDlg)	m_pSysHistoryDlg->SendMessage(UM_HISTORY_ON_ERROR, (WPARAM)pstErrorCode);
			else					delete	pstErrorCode;
		}

		// �Ͻ� ����
		if (m_stSystemStatus.bOnOperating) {

			m_stSystemStatus.bOnPause = TRUE;
			if (m_pMainWnd && m_pMainWnd->GetSafeHwnd())
				m_pMainWnd->PostMessage(UM_MAIN_PAUSE);
		}
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���� ////////////////////////////////////////////////////
	if (bOnErrorClear) {

		if (m_pSysHistoryDlg) {

			if (m_stSystemStatus.nCurrentErrorCode == ERROR_AIR_PRESSURE)
				m_pSysHistoryDlg->PostMessage(UM_HISTORY_CLEAR);
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� : ���� üũ ///////////////////////////////////////////////////////
void CMainApp::ProcessCheckDoorOpen(void)
{
	static	UINT			nCurrentStep		= 0;
	static	UINT			nPreviousStep		= 0;

	static	LTimerMsec		LTimerProceed;
	static	LTimerMsec		LTimerTimeOut;

	BOOL					bOnError			= FALSE;
	BOOL					bOnErrorClear		= FALSE;
	BOOL					bDI_DOOR_OPEN		= FALSE;


	/////////////////////////////////////////////////////////////////
	bDI_DOOR_OPEN |= !GetDIStatus(DI_SIG_DOOR_OPENED_1);
	bDI_DOOR_OPEN |= !GetDIStatus(DI_SIG_DOOR_OPENED_2);


	/////////////////////////////////////////////////////////////////
	// ���� ���μ��� ////////////////////////////////////////////////
	switch (nCurrentStep) {

		case	0		:
							nCurrentStep = 100;
							break;

		case	100		:
							if (!m_SystemConfig.UseSystemOption(SOPT_DISABLE_DOOR_OPEN)) {

								if (m_stSystemStatus.nDeviceStatus[SD_DIO_1] == DS_NORMAL) {

									nCurrentStep = 110;
									break;
								}
							}

							// ������ �÷��� ����
							m_stSystemStatus.bOnDoorOpened = FALSE;

							nCurrentStep = 190;
							break;

		case	110		:
							if (!m_stSystemStatus.bOnDoorOpened && bDI_DOOR_OPEN)		nCurrentStep = 120;
							else if (m_stSystemStatus.bOnDoorOpened && !bDI_DOOR_OPEN)	nCurrentStep = 130;
							else														nCurrentStep = 190;

							break;

		// ���� ����
		case	120		:
							LTimerProceed.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_DOOR_OPEN));
							nCurrentStep++;
							break;

		case	121		:
							if (bDI_DOOR_OPEN) {

								if (LTimerProceed.Verify())
									nCurrentStep++;

								break;
							}

							nCurrentStep = 190;
							break;

		case	122		:
							// ������ �÷��� ����
							m_stSystemStatus.bOnDoorOpened = TRUE;

							bOnError     = TRUE;
							nCurrentStep = 190;
							break;

		// ���� ����
		case	130		:
							// ������ �÷��� ����
							m_stSystemStatus.bOnDoorOpened = FALSE;

							bOnErrorClear = TRUE;
							nCurrentStep  = 190;
							break;

		case	190		:
							nCurrentStep = 0;
							break;
	}


	/////////////////////////////////////////////////////////////////
	// ���� �߻� ////////////////////////////////////////////////////
	if (bOnError) {

		if (!GetDIStatus(DI_SIG_DOOR_OPENED_1))		ErrorMessage(TRUE, _T("%s::(X%03X) %s"), g_stSystemString[SYSSTR_MC_WARN_DOOR_OPENED].szDescription[m_nTypeLanguage], DI_SIG_DOOR_OPENED_1, g_stDIODescription[m_nTypeLanguage][DI_SIG_DOOR_OPENED_1].szInput);
		if (!GetDIStatus(DI_SIG_DOOR_OPENED_2))		ErrorMessage(TRUE, _T("%s::(X%03X) %s"), g_stSystemString[SYSSTR_MC_WARN_DOOR_OPENED].szDescription[m_nTypeLanguage], DI_SIG_DOOR_OPENED_2, g_stDIODescription[m_nTypeLanguage][DI_SIG_DOOR_OPENED_2].szInput);

		if (m_nTypeLanguage != LANGUAGE_KOR) {

			if (!GetDIStatus(DI_SIG_DOOR_OPENED_1))	ErrorMessage(TRUE, _T("%s::(X%03X) %s"), g_stSystemString[SYSSTR_MC_WARN_DOOR_OPENED].szDescription[LANGUAGE_KOR], DI_SIG_DOOR_OPENED_1, g_stDIODescription[LANGUAGE_KOR][DI_SIG_DOOR_OPENED_1].szInput);
			if (!GetDIStatus(DI_SIG_DOOR_OPENED_2))	ErrorMessage(TRUE, _T("%s::(X%03X) %s"), g_stSystemString[SYSSTR_MC_WARN_DOOR_OPENED].szDescription[LANGUAGE_KOR], DI_SIG_DOOR_OPENED_2, g_stDIODescription[LANGUAGE_KOR][DI_SIG_DOOR_OPENED_2].szInput);
		}

		// �Ͻ� ����
		if (m_stSystemStatus.bOnOperating) {

			// �ý��� �÷��� ����
			m_stSystemStatus.bOnBuzzer = TRUE;

// 			m_stSystemStatus.bOnPause = TRUE;
// 			if (m_pMainWnd && m_pMainWnd->GetSafeHwnd())
// 				m_pMainWnd->PostMessage(UM_MAIN_PAUSE);
		}
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���� ////////////////////////////////////////////////////
	if (bOnErrorClear) {

		// �Ͻ� ���� ����
		if (m_stSystemStatus.bOnOperating) {

			// �ý��� �÷��� ����
			m_stSystemStatus.bOnBuzzer = FALSE;

// 			m_stSystemStatus.bOnPause = FALSE;
// 			if (m_pMainWnd && m_pMainWnd->GetSafeHwnd())
// 				m_pMainWnd->PostMessage(UM_MAIN_PAUSE);
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� : ��� ��Ʈ�� /////////////////////////////////////////////////////
void CMainApp::ProcessMotion(void)
{
	static	UINT			nCurrentStep			= 0;
	static	UINT			nMC_CurrentStep			= 0;
	static	UINT			nMC_PreviousStep		= 0;
	static	UINT			nMC_ReturnStep			= 0;
	static	UINT			nRetryCount				= 0;
	static	UINT			nActionCount			= 0;
	static	UINT			nCurrentAxisNo			= 0;
	static	UINT			nLastAxisNo				= 0;

	static	BOOL			bOnManualControlMode	= FALSE;

	static	DOUBLE			dblMotionPosition		= 0;
	static	DOUBLE			dblMotionSpeed			= 0;
	static	DWORD			dwMotionStatus			= 0;
	static	DWORD			dwRetCode				= 0;

	static	UINT			nSTATION_NO;

	static	LTimerMsec		LTimerProceed;
	static	LTimerMsec		LTimerSteady;
	static	LTimerMsec		LTimerReadPosition;
	static	LTimerMsec		LTimerCheckAlarm;
	static	LTimerMsec		LTimerTimeOut;
	static	LTimerMsec		LTimerSystemMonitor;

	static	ERROR_CODE_T	stErrorCode;
	static	SYSTEM_CONFIG_T	stSystemConfig;

	BOOL					bOnError				= FALSE;
	PERROR_CODE_T			pstErrorCode			= NULL;


	/////////////////////////////////////////////////////////////////
	// ���� ���� ��� ���� //////////////////////////////////////////
	bOnManualControlMode  = FALSE;
	bOnManualControlMode |= m_stSystemStatus.bOnManualControlDIO;
	for (UINT nIndex = 0; nIndex < MAX_STATION; nIndex++)
		bOnManualControlMode |= m_stSystemStatus.bIsManualControl[nIndex];


	/////////////////////////////////////////////////////////////////
	// ��� ���� üũ ///////////////////////////////////////////////
	if (m_stSystemStatus.bOnEmergencyStop) {

		nCurrentStep	= 0;
		nMC_CurrentStep	= 0;
	
		// ���� ��Ʈ�� �÷��� ����
		m_stSystemStatus.bOnMC_MotionMoveJog	= FALSE;
		ZeroMemory(m_stSystemStatus.bOnMC_MotionMove, sizeof(BOOL) * MAX_STATION);
		ZeroMemory(m_stSystemStatus.bOnMC_MotionMoveEx, sizeof(BOOL) * MAX_STATION);
		ZeroMemory(m_stSystemStatus.bOnMC_MotionMoveCustom, sizeof(BOOL) * MAX_STATION * MAX_MOTION_MC_MOVE);

		return;
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���μ��� ////////////////////////////////////////////////
	switch (nCurrentStep) {

		case	0		:
							nCurrentStep = 100;
							break;


		/////////////////////////////////////////////////////////
		// ��� ��Ʈ�ѷ� ���� üũ //////////////////////////////
		case	100		:
							nCurrentStep = 110;
							break;


		/////////////////////////////////////////////////////////
		// ���� ���� ���� üũ //////////////////////////////////
		case	110		:
							if (m_stSystemStatus.bOnMotion_CheckServoMotorAlarm) {

								if (LTimerCheckAlarm.Verify()) {

									nCurrentAxisNo = MOTION_AXIS_1;
									nCurrentStep++;
									break;
								}
							}

							nCurrentStep = 120;
							break;

		case	111		:
							dwMotionStatus = 0;
							AxmSignalReadServoAlarm(nCurrentAxisNo, &dwMotionStatus);
							if (dwMotionStatus) {

								bOnError		= TRUE;
								nRetryCount		= 0;
								nCurrentStep	= 900;

								stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR;
								stErrorCode.nMotionAxisNo	= nCurrentAxisNo;
								break;
							}

							nCurrentStep++;
							break;

		case	112		:
							if (++nCurrentAxisNo >= MAX_MOTION_AXIS) {

								nCurrentStep = 119;
								break;
							}

							nCurrentStep--;
							break;

		case	119		:
							LTimerCheckAlarm.Start(200);

							nCurrentStep = 120;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� ��ġ ����͸� //////////////////////////////////
		case	120		:
							if (m_stSystemStatus.bOnMotion_ReadCurrentPosition) {

								if (LTimerReadPosition.Verify()) {

									nCurrentAxisNo = MOTION_AXIS_1;
									nCurrentStep++;
									break;
								}
							}

							nCurrentStep = 0;
							break;

		case	121		:
							// ���� ��ġ (�ܺ� ���ڴ� ��)
							AxmStatusGetActPos(nCurrentAxisNo, &dblMotionPosition);
							m_stSystemStatus.dblMotionActualPosition[nCurrentAxisNo] = dblMotionPosition;
							
							// Ŀ�ǵ� ��ġ (���� ī��Ʈ ��)
							AxmStatusGetCmdPos(nCurrentAxisNo, &dblMotionPosition);
							m_stSystemStatus.dblMotionCurrentPosition[nCurrentAxisNo] = dblMotionPosition;

							nCurrentStep++;
							break;

		case	122		:
							if (++nCurrentAxisNo >= MAX_MOTION_AXIS) {

								nCurrentStep = 129;
								break;
							}

							nCurrentStep--;
							break;

		case	129		:
							LTimerReadPosition.Start(10);

							nCurrentStep = 0;
							break;


		/////////////////////////////////////////////////////////////
		// ��� ���� ////////////////////////////////////////////////
		case	900		:
							// ���� ���� ����
							for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++) {
								
								// ���� ������
								Motion_Stop_E(nAxisNo);
								Motion_Stop_E(nAxisNo);

								// ���� ���� OFF
								AxmSignalServoOn(nAxisNo, DISABLE);
							}

							// ���� �극��ũ ����
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z1);
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z2);
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z3);
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z4);

							// ���� ��Ʈ�� �÷��� ����
							nMC_CurrentStep = 0;
							m_stSystemStatus.bOnMC_MotionMoveJog	= FALSE;
							ZeroMemory(m_stSystemStatus.bOnMC_MotionMove, sizeof(BOOL) * MAX_STATION);
							ZeroMemory(m_stSystemStatus.bOnMC_MotionMoveEx, sizeof(BOOL) * MAX_STATION);
							ZeroMemory(m_stSystemStatus.bOnMC_MotionMoveCustom, sizeof(BOOL) * MAX_STATION * MAX_MOTION_MC_MOVE);

							nCurrentStep++;
							break;

		case	901		:
							if (!m_stSystemStatus.bOnAlarmSystem) {

								SErrorMessage(TRUE, _T("MOTION PROCESS ERROR!"));

								// �÷��� ����
								m_stSystemStatus.bOnMotion_CheckServoMotorAlarm	= FALSE;
								m_stSystemStatus.bOnMotion_ReadCurrentPosition	= FALSE;
								for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++)
									m_stSystemStatus.bOnMotion_HomeSearchStart[nAxisNo]	= FALSE;

								nCurrentStep = 0;
							}

							break;
	}


	/////////////////////////////////////////////////////////////////
	// ���� ��Ʈ�� ���� ���μ��� ////////////////////////////////////
	if (bOnManualControlMode) {

		switch (nMC_CurrentStep) {

			case	0		:
								nMC_CurrentStep = 100;
								break;


			/////////////////////////////////////////////////////////
			// ���� �̵� : �⺻ /////////////////////////////////////
			case	100		:
								if (m_stSystemStatus.bOnMC_MotionMove[STATION_1]) {

									m_stSystemStatus.bOnMC_MotionMoveResult[STATION_1] = FALSE;

									nMC_CurrentStep = 110;
									break;
								}

								nMC_CurrentStep = 200;
								break;

			// VZ Ȩ ��ġ �̵�
			case	110		:
								if (Motion_Done(MOTION_RVZ)) {

									DOUBLE	dblSpeed = m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase * m_SystemConfig.GetGainServoMotorSpeedMC();

									if (dblSpeed <= 0.0)	dblSpeed = m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase;

									Motion_MoveTo(MOTION_RVZ, m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME], dblSpeed);

									nMC_CurrentStep++;
								}

								break;

			case	111		:
								if (Motion_Done(MOTION_RVZ)) {

									BOOL	bResult	= TRUE;

									bResult &= Motion_CheckStopStatus(MOTION_RVZ, m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME]);

									nMC_CurrentStep = bResult ? 150 : 190;
								}

								break;

			// VX, VY ��ǥ ��ġ ���� �̵�
			case	150		:
								if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVY)) {

									DOUBLE	dblSpeed	= m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase * m_SystemConfig.GetGainServoMotorSpeedMC();

									if (dblSpeed <= 0.0)	dblSpeed = m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase;

									Motion_Move2X(MCOORD_S01, MOTION_RVX, MOTION_RVY,
												  m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVX],
												  m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVY],
												  dblSpeed);

									nMC_CurrentStep++;
								}
								
								break;

			case	151		:
								if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVY)) {

									BOOL	bResult	= TRUE;

									bResult &= Motion_CheckStopStatus(MOTION_RVX, m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVX]);
									bResult &= Motion_CheckStopStatus(MOTION_RVY, m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVY]);

									nMC_CurrentStep = bResult ? 160 : 190;
								}

								break;

			// VZ ��ǥ ��ġ �̵�
			case	160		:
								if (Motion_Done(MOTION_RVZ)) {

									DOUBLE	dblSpeed = m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase * m_SystemConfig.GetGainServoMotorSpeedMC();

									if (dblSpeed <= 0.0)	dblSpeed = m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase;

									Motion_MoveTo(MOTION_RVZ, m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVZ], dblSpeed);

									nMC_CurrentStep++;
								}

								break;

			case	161		:
								if (Motion_Done(MOTION_RVZ)) {

									BOOL	bResult	= TRUE;

									bResult &= Motion_CheckStopStatus(MOTION_RVZ, m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVZ]);

									nMC_CurrentStep = bResult ? 180 : 190;
								}

								break;

			// ���� �̵� ����
			case	180		:
								m_stSystemStatus.bOnMC_MotionMoveResult[STATION_1] = TRUE;

								nMC_CurrentStep = 190;
								break;

			// �Ϸ�
			case	190		:
								
								m_stSystemStatus.bOnMC_MotionMove[STATION_1] = FALSE;

								nMC_CurrentStep = 200;
								break;


			/////////////////////////////////////////////////////////
			case	200		:
								nMC_CurrentStep = 1000;
								break;


			/////////////////////////////////////////////////////////
			// ���� �̵� : ���� ���� ���� ///////////////////////////
			case	1000	:
								if (m_stSystemStatus.bOnMC_MotionMoveCustom[STATION_1][MMC_MOVE_OPEN_BEGIN]) {

									m_stSystemStatus.bOnMC_MotionMoveResult[STATION_1] = FALSE;

									nMC_CurrentStep = 1010;
									break;
								}

								nMC_CurrentStep = 1100;
								break;

			// VZ Ȩ ��ġ �̵�
			case	1010	:
								if (Motion_Done(MOTION_RVZ)) {

									DOUBLE	dblSpeed = m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase * m_SystemConfig.GetGainServoMotorSpeedMC();

									if (dblSpeed <= 0.0)	dblSpeed = m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase;

									Motion_MoveTo(MOTION_RVZ, m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME], dblSpeed);

									nMC_CurrentStep++;
								}

								break;

			case	1011	:
								if (Motion_Done(MOTION_RVZ)) {

									BOOL	bResult	= TRUE;

									bResult &= Motion_CheckStopStatus(MOTION_RVZ, m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME]);

									nMC_CurrentStep = bResult ? 1020 : 1090;
								}

								break;

			// VY Ȩ ��ġ �̵�
			case	1020	:
								if (Motion_Done(MOTION_RVY)) {

									DOUBLE	dblSpeed = m_stMotionAxisInfo[MOTION_RVY].dblSpeedBase * m_SystemConfig.GetGainServoMotorSpeedMC();

									if (dblSpeed <= 0.0)	dblSpeed = m_stMotionAxisInfo[MOTION_RVY].dblSpeedBase;

									Motion_MoveTo(MOTION_RVY, m_stMotionAxisInfo[MOTION_RVY].dblCustomPosition[MAI_CPOS_HOME], dblSpeed);

									nMC_CurrentStep++;
								}

								break;

			case	1021	:
								if (Motion_Done(MOTION_RVY)) {

									BOOL	bResult	= TRUE;

									bResult &= Motion_CheckStopStatus(MOTION_RVY, m_stMotionAxisInfo[MOTION_RVY].dblCustomPosition[MAI_CPOS_HOME]);

									nMC_CurrentStep = bResult ? 1050 : 1090;
								}

								break;

			// VX, VZ ��ǥ ��ġ ���� �̵�
			case	1050	:
								if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVZ)) {

									DOUBLE	dblSpeed	= m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase * m_SystemConfig.GetGainServoMotorSpeedMC();

									if (dblSpeed <= 0.0)	dblSpeed = m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase;

									Motion_Move2X(MCOORD_S01, MOTION_RVZ, MOTION_RVX,
												  m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVZ],
												  m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVX],
												  dblSpeed);

									nMC_CurrentStep++;
								}
								
								break;

			case	1051	:
								if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVZ)) {

									BOOL	bResult	= TRUE;

									bResult &= Motion_CheckStopStatus(MOTION_RVX, m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVX]);
									bResult &= Motion_CheckStopStatus(MOTION_RVZ, m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVZ]);

									nMC_CurrentStep = bResult ? 1060 : 1090;
								}

								break;

			// VY ��ǥ ��ġ �̵�
			case	1060	:
								if (Motion_Done(MOTION_RVY)) {

									DOUBLE	dblSpeed = m_stMotionAxisInfo[MOTION_RVY].dblSpeedBase * m_SystemConfig.GetGainServoMotorSpeedMC();

									if (dblSpeed <= 0.0)	dblSpeed = m_stMotionAxisInfo[MOTION_RVY].dblSpeedBase;

									Motion_MoveTo(MOTION_RVY, m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVY], dblSpeed);

									nMC_CurrentStep++;
								}

								break;

			case	1061	:
								if (Motion_Done(MOTION_RVY)) {

									BOOL	bResult	= TRUE;

									bResult &= Motion_CheckStopStatus(MOTION_RVY, m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVY]);

									nMC_CurrentStep = bResult ? 1080 : 1090;
								}

								break;

			// ���� �̵� ����
			case	1080	:
								m_stSystemStatus.bOnMC_MotionMoveResult[STATION_1] = TRUE;

								nMC_CurrentStep = 1090;
								break;

			// �Ϸ�
			case	1090	:
								m_stSystemStatus.bOnMC_MotionMoveCustom[STATION_1][MMC_MOVE_OPEN_BEGIN] = FALSE;

								nMC_CurrentStep = 1100;
								break;


			/////////////////////////////////////////////////////////
			// ���� �̵� : ���� ���� �Ϸ� ///////////////////////////
			case	1100	:
								if (m_stSystemStatus.bOnMC_MotionMoveCustom[STATION_1][MMC_MOVE_OPEN_END]) {

									m_stSystemStatus.bOnMC_MotionMoveResult[STATION_1] = FALSE;

									nMC_CurrentStep = 1110;
									break;
								}

								nMC_CurrentStep = 1200;
								break;

			// VX, VY, VZ ��ǥ ��ġ ���� �̵�
			case	1110	:
								if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVY) && Motion_Done(MOTION_RVZ)) {

									DOUBLE	dblSpeed	= m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase * m_SystemConfig.GetGainServoMotorSpeedMC();

									if (dblSpeed <= 0.0)	dblSpeed = m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase;

									Motion_Move3X(MCOORD_S01, MOTION_RVZ, MOTION_RVX, MOTION_RVY,
												  m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVZ],
												  m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVX],
												  m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVY],
												  dblSpeed);

									nMC_CurrentStep++;
								}
								
								break;

			case	1111	:
								if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVY) && Motion_Done(MOTION_RVZ)) {

									BOOL	bResult	= TRUE;

									bResult &= Motion_CheckStopStatus(MOTION_RVX, m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVX]);
									bResult &= Motion_CheckStopStatus(MOTION_RVY, m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVY]);
									bResult &= Motion_CheckStopStatus(MOTION_RVZ, m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVZ]);

									nMC_CurrentStep = bResult ? 1180 : 1190;
								}

								break;

			// ���� �̵� ����
			case	1180	:
								m_stSystemStatus.bOnMC_MotionMoveResult[STATION_1] = TRUE;

								nMC_CurrentStep = 1190;
								break;

			// �Ϸ�
			case	1190	:
								m_stSystemStatus.bOnMC_MotionMoveCustom[STATION_1][MMC_MOVE_OPEN_END] = FALSE;

								nMC_CurrentStep = 1200;
								break;


			/////////////////////////////////////////////////////////
			// ���� �̵� : ���� �ݱ� ���� ///////////////////////////
			case	1200	:
								if (m_stSystemStatus.bOnMC_MotionMoveCustom[STATION_1][MMC_MOVE_CLOSE_BEGIN]) {

									m_stSystemStatus.bOnMC_MotionMoveResult[STATION_1] = FALSE;

									nMC_CurrentStep = 1210;
									break;
								}

								nMC_CurrentStep = 1300;
								break;

			// VZ Ȩ ��ġ �̵�
			case	1210	:
								if (Motion_Done(MOTION_RVZ)) {

									DOUBLE	dblSpeed = m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase * m_SystemConfig.GetGainServoMotorSpeedMC();

									if (dblSpeed <= 0.0)	dblSpeed = m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase;

									Motion_MoveTo(MOTION_RVZ, m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME], dblSpeed);

									nMC_CurrentStep++;
								}

								break;

			case	1211	:
								if (Motion_Done(MOTION_RVZ)) {

									BOOL	bResult	= TRUE;

									bResult &= Motion_CheckStopStatus(MOTION_RVZ, m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME]);

									nMC_CurrentStep = bResult ? 1220 : 1290;
								}

								break;

			// VY Ȩ ��ġ �̵�
			case	1220	:
								if (Motion_Done(MOTION_RVY)) {

									DOUBLE	dblSpeed = m_stMotionAxisInfo[MOTION_RVY].dblSpeedBase * m_SystemConfig.GetGainServoMotorSpeedMC();

									if (dblSpeed <= 0.0)	dblSpeed = m_stMotionAxisInfo[MOTION_RVY].dblSpeedBase;

									Motion_MoveTo(MOTION_RVY, m_stMotionAxisInfo[MOTION_RVY].dblCustomPosition[MAI_CPOS_HOME], dblSpeed);

									nMC_CurrentStep++;
								}

								break;

			case	1221	:
								if (Motion_Done(MOTION_RVY)) {

									BOOL	bResult	= TRUE;

									bResult &= Motion_CheckStopStatus(MOTION_RVY, m_stMotionAxisInfo[MOTION_RVY].dblCustomPosition[MAI_CPOS_HOME]);

									nMC_CurrentStep = bResult ? 1230 : 1290;
								}

								break;

			// VZ ��ǥ ��ġ �̵�
			case	1230	:
								if (Motion_Done(MOTION_RVZ)) {

									DOUBLE	dblSpeed = m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase * m_SystemConfig.GetGainServoMotorSpeedMC();

									if (dblSpeed <= 0.0)	dblSpeed = m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase;

									Motion_MoveTo(MOTION_RVZ, m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVZ], dblSpeed);

									nMC_CurrentStep++;
								}

								break;

			case	1231	:
								if (Motion_Done(MOTION_RVZ)) {

									BOOL	bResult	= TRUE;

									bResult &= Motion_CheckStopStatus(MOTION_RVZ, m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVZ]);

									nMC_CurrentStep = bResult ? 1240 : 1290;
								}

								break;

			// VX ��ǥ ��ġ �̵�
			case	1240	:
								if (Motion_Done(MOTION_RVX)) {

									DOUBLE	dblSpeed = m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase * m_SystemConfig.GetGainServoMotorSpeedMC();

									if (dblSpeed <= 0.0)	dblSpeed = m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase;

									Motion_MoveTo(MOTION_RVX, m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVX], dblSpeed);

									nMC_CurrentStep++;
								}

								break;

			case	1241	:
								if (Motion_Done(MOTION_RVX)) {

									BOOL	bResult	= TRUE;

									bResult &= Motion_CheckStopStatus(MOTION_RVX, m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVX]);

									nMC_CurrentStep = bResult ? 1260 : 1290;
								}

								break;

			// VX, VZ ��ǥ ��ġ ���� �̵�
			case	1250	:
								if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVZ)) {

									DOUBLE	dblSpeed	= m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase * m_SystemConfig.GetGainServoMotorSpeedMC();

									if (dblSpeed <= 0.0)	dblSpeed = m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase;

									Motion_Move2X(MCOORD_S01, MOTION_RVZ, MOTION_RVX,
												  m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVZ],
												  m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVX],
												  dblSpeed);

									nMC_CurrentStep++;
								}
								
								break;

			case	1251	:
								if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVZ)) {

									BOOL	bResult	= TRUE;

									bResult &= Motion_CheckStopStatus(MOTION_RVX, m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVX]);
									bResult &= Motion_CheckStopStatus(MOTION_RVZ, m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVZ]);

									nMC_CurrentStep = bResult ? 1260 : 1290;
								}

								break;

			// VY ��ǥ ��ġ �̵�
			case	1260	:
								if (Motion_Done(MOTION_RVY)) {

									DOUBLE	dblSpeed = m_stMotionAxisInfo[MOTION_RVY].dblSpeedBase * m_SystemConfig.GetGainServoMotorSpeedMC();

									if (dblSpeed <= 0.0)	dblSpeed = m_stMotionAxisInfo[MOTION_RVY].dblSpeedBase;

									Motion_MoveTo(MOTION_RVY, m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVY], dblSpeed);

									nMC_CurrentStep++;
								}

								break;

			case	1261	:
								if (Motion_Done(MOTION_RVY)) {

									BOOL	bResult	= TRUE;

									bResult &= Motion_CheckStopStatus(MOTION_RVY, m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVY]);

									nMC_CurrentStep = bResult ? 1280 : 1290;
								}

								break;

			// ���� �̵� ����
			case	1280	:
								m_stSystemStatus.bOnMC_MotionMoveResult[STATION_1] = TRUE;

								nMC_CurrentStep = 1290;
								break;

			// �Ϸ�
			case	1290	:
								m_stSystemStatus.bOnMC_MotionMoveCustom[STATION_1][MMC_MOVE_CLOSE_BEGIN] = FALSE;

								nMC_CurrentStep = 1300;
								break;


			/////////////////////////////////////////////////////////
			// ���� �̵� : ���� �ݱ� �Ϸ� ///////////////////////////
			case	1300	:
								if (m_stSystemStatus.bOnMC_MotionMoveCustom[STATION_1][MMC_MOVE_CLOSE_END]) {

									m_stSystemStatus.bOnMC_MotionMoveResult[STATION_1] = FALSE;

									nMC_CurrentStep = 1310;
									break;
								}

								nMC_CurrentStep = 1400;
								break;

			// VX, VY, VZ ��ǥ ��ġ ���� �̵�
			case	1310	:
								if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVY) && Motion_Done(MOTION_RVZ)) {

									DOUBLE	dblSpeed	= m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase * m_SystemConfig.GetGainServoMotorSpeedMC();

									if (dblSpeed <= 0.0)	dblSpeed = m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase;

									Motion_Move3X(MCOORD_S01, MOTION_RVZ, MOTION_RVX, MOTION_RVY,
												  m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVZ],
												  m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVX],
												  m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVY],
												  dblSpeed);

									nMC_CurrentStep++;
								}
								
								break;

			case	1311	:
								if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVY) && Motion_Done(MOTION_RVZ)) {

									BOOL	bResult	= TRUE;

									bResult &= Motion_CheckStopStatus(MOTION_RVX, m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVX]);
									bResult &= Motion_CheckStopStatus(MOTION_RVY, m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVY]);
									bResult &= Motion_CheckStopStatus(MOTION_RVZ, m_stSystemStatus.dblMC_MotionMovePosition[MOTION_RVZ]);

									nMC_CurrentStep = bResult ? 1380 : 1390;
								}

								break;

			// ���� �̵� ����
			case	1380	:
								m_stSystemStatus.bOnMC_MotionMoveResult[STATION_1] = TRUE;

								nMC_CurrentStep = 1390;
								break;

			// �Ϸ�
			case	1390	:
								m_stSystemStatus.bOnMC_MotionMoveCustom[STATION_1][MMC_MOVE_CLOSE_END] = FALSE;

								nMC_CurrentStep = 1400;
								break;


			/////////////////////////////////////////////////////////
			case	1400	:
								nMC_CurrentStep = 8000;
								break;


			/////////////////////////////////////////////////////////
			case	8000	:
								nMC_CurrentStep = 9000;
								break;


			/////////////////////////////////////////////////////////
			// ���� �̵� ////////////////////////////////////////////
			case	9000	:
								if (m_stSystemStatus.bOnMC_MotionMoveJog) {

									nMC_CurrentStep++;
									break;
								}

								nMC_CurrentStep = 0;
								break;

			case	9001	:
								if (Motion_Done(m_stSystemStatus.stMC_MotionJogInfo.nAxisNo)) {

									UINT	nAxisNo	= m_stSystemStatus.stMC_MotionJogInfo.nAxisNo;
								
									Motion_MoveVel(	m_stSystemStatus.stMC_MotionJogInfo.nAxisNo, 
													m_stSystemStatus.stMC_MotionJogInfo.dblSpeed, 
													m_stSystemStatus.stMC_MotionJogInfo.dblAcceleration,
													m_stSystemStatus.stMC_MotionJogInfo.nDirection);

									NormalMessage(TRUE,	_T("JOG MOTION::%s, Jog-Speed=%.2f, Jog-Direction=%d"),	
														g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
														m_stSystemStatus.stMC_MotionJogInfo.dblSpeed,
														m_stSystemStatus.stMC_MotionJogInfo.nDirection);

									nLastAxisNo = m_stSystemStatus.stMC_MotionJogInfo.nAxisNo;

									nMC_CurrentStep++;
								}

								break;

			case	9002	:
								if (!m_stSystemStatus.bOnMC_MotionMoveJog) {

									NormalMessage(TRUE,	_T("JOG STOP::%s"),	
														g_stMotionAxisName[nLastAxisNo].stDescription.szDescription[m_nTypeLanguage]);

									Motion_Stop_E(nLastAxisNo);
									Motion_Stop_E(nLastAxisNo);

									nMC_CurrentStep = 0;
								}

								break;
		}
	}


	/////////////////////////////////////////////////////////////////
	// ���� �߻� ////////////////////////////////////////////////////
	if (bOnError) {

		pstErrorCode = new ERROR_CODE_T;
		if (pstErrorCode) {

			*pstErrorCode = stErrorCode;

			// �˶� �̷� ���̾�α׿� �޼��� ����
			if (m_pSysHistoryDlg)		m_pSysHistoryDlg->SendMessage(UM_HISTORY_ON_ERROR, (WPARAM)pstErrorCode);
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� : ��� ���� ���� #1 (ORG, PL, NL) /////////////////////////////////
void CMainApp::ProcessMotionHomeSearch01(UINT nAxisNo)
{
	static	UINT			nCurrentStep[MAX_MOTION_AXIS];
	static	UINT			nReturnStep[MAX_MOTION_AXIS];
	static	UINT			nPreviousStep[MAX_MOTION_AXIS];
	static	UINT			nRecoveryStep[MAX_MOTION_AXIS];
	static	UINT			nRetryCount[MAX_MOTION_AXIS];

	static	BOOL			bOnPause[MAX_MOTION_AXIS];

	static	DWORD			dwStatusPositive[MAX_MOTION_AXIS];
	static	DWORD			dwStatusNegative[MAX_MOTION_AXIS];
	static	DWORD			dwStatusHome[MAX_MOTION_AXIS];
	static	DWORD			dwStatusEnd[MAX_MOTION_AXIS];

	static	BYTE			byHomeMethod[MAX_MOTION_AXIS][3];
	static	DOUBLE			dblHomeVelocity[MAX_MOTION_AXIS][3];
	static	DOUBLE			dblHomeAcceleration[MAX_MOTION_AXIS][3];

	static	DOUBLE			dblMotorSpeed[MAX_MOTION_AXIS];

	static	LTimerMsec		LTimerProceed[MAX_MOTION_AXIS];
	static	LTimerMsec		LTimerTimeOut[MAX_MOTION_AXIS];


	/////////////////////////////////////////////////////////////////
	// ��� ���� ���� ///////////////////////////////////////////////
	if (m_stSystemStatus.bOnEmergencyStop && !bOnPause[nAxisNo]) {

		bOnPause[nAxisNo]		= TRUE;
		nRecoveryStep[nAxisNo]	= 0;
		nCurrentStep[nAxisNo]	= STEP_EMG;

		return;
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���μ��� ////////////////////////////////////////////////
	switch (nCurrentStep[nAxisNo]) {

		case	0		:
							nCurrentStep[nAxisNo] = 100;
							break;


		/////////////////////////////////////////////////////////////
		// ��� /////////////////////////////////////////////////////
		case	100		:
							if (m_stSystemStatus.bOnMotion_HomeSearchStart[nAxisNo]) {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_START].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// ����Ʈ ����Ʈ ����
								Motion_SetSoftLimit(nAxisNo, FALSE);

								// �÷��� �ʱ�ȭ
								m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo] = FALSE;

								// ���� ���� Ÿ�Ӿƿ� ����
								LTimerTimeOut[nAxisNo].Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_HOME_SEARCH));

								nCurrentStep[nAxisNo] = 200;
							}

							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� ////////////////////////////////////////////////
		case	200		:
							nCurrentStep[nAxisNo]++;
							break;

		// ���� ���� �ɼ�
		case	201		:
							// P-LIMIT �켱 ���� �ɼ�
							if (m_stSystemStatus.bOnMotion_HomeSearchOptionPLStop[nAxisNo]) {
							
								dblMotorSpeed[nAxisNo] = m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch;
								nCurrentStep[nAxisNo]  = 300;
								break;
							}

							// N-LIMIT �켱 ���� �ɼ�
							if (m_stSystemStatus.bOnMotion_HomeSearchOptionNLStop[nAxisNo]) {
							
								dblMotorSpeed[nAxisNo] = m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch;
								nCurrentStep[nAxisNo]  = 400;
								break;
							}
							
							nCurrentStep[nAxisNo] = 210;
							break;

		// HOME �˻�
		case	210		:
							AxmSignalReadLimit(nAxisNo, &dwStatusPositive[nAxisNo], &dwStatusNegative[nAxisNo]);
							AxmSignalReadInputBit(nAxisNo, 0, &dwStatusHome[nAxisNo]);
							
							// HOME/LIMIT ���� ����
							if (dwStatusHome[nAxisNo]) {
							
								dblMotorSpeed[nAxisNo] = m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch;
								nCurrentStep[nAxisNo]  = 270;
							
							} else {
							
								dblMotorSpeed[nAxisNo] = m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch;
								nCurrentStep[nAxisNo]  = 220;
							}

							break;

		// (-) �������� HOME ���� ��� ���� ���� �� ���� ����
		case	220		:
							AxmMoveSignalSearch(nAxisNo,
												dblMotorSpeed[nAxisNo] * (-1.0),					// ���� �ӵ�						
												m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration,	// ������ �ð�
												HomeSensor,											// ORG
												SIGNAL_UP_EDGE,										// ��� ����
												SLOWDOWN_STOP);										// ���� ����

							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Speed=%.2f"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_MOVE_NEG_UP_EDGE].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dblMotorSpeed[nAxisNo]);

							nCurrentStep[nAxisNo]++;
							break;

		case	221		:
							// ���� �̵� �Ϸ���� ���
							if (!Motion_Done(nAxisNo))	break;

							// ���� ���� ���� üũ
							AxmStatusReadStop(nAxisNo, &dwStatusEnd[nAxisNo]);
							dwStatusEnd[nAxisNo] &= 0x1FFFF;

							// ���� �ӵ� ����
							dblMotorSpeed[nAxisNo] = 10.0;

							// ��ȣ �˻� ���� ����
							if (!dwStatusEnd[nAxisNo] || dwStatusEnd[nAxisNo] & QIEND_STATUS_18 || dwStatusEnd[nAxisNo] & QIEND_STATUS_1) {

								// ������ ����Ʈ ���� ����
								if (dwStatusEnd[nAxisNo] & QIEND_STATUS_1) {

									// ���� �ӵ� ����
									dblMotorSpeed[nAxisNo] = m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch;

									TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
														nAxisNo + 1,
														g_stSystemString[SYSSTR_MOTION_HOME_STOP_LIMIT_NEG].szDescription[m_nTypeLanguage],
														g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								} else {

									TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
														nAxisNo + 1,
														g_stSystemString[SYSSTR_MOTION_HOME_STOP_UP_EDGE].szDescription[m_nTypeLanguage],
														g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);
								}

								nCurrentStep[nAxisNo] = 270;
								break;
							}

							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Status=%d(%X)"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_STOP_UNKNOWN].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dwStatusEnd[nAxisNo], dwStatusEnd[nAxisNo]);

							nCurrentStep[nAxisNo] = 290;
							break;

		// (+) �������� HOME ���� �ϰ� ���� ���� �� ���� ����
		case	270		:
							AxmMoveSignalSearch(nAxisNo,
												dblMotorSpeed[nAxisNo],								// ���� �ӵ�						
												m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration,	// ������ �ð�
												HomeSensor,											// ORG
												SIGNAL_DOWN_EDGE,									// �ϰ� ����
												SLOWDOWN_STOP);										// ���� ����

							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Speed=%.2f"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_MOVE_POS_DN_EDGE].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dblMotorSpeed[nAxisNo]);

							nCurrentStep[nAxisNo]++;
							break;

		case	271		:
							// ���� �̵� �Ϸ���� ���
							if (!Motion_Done(nAxisNo))	break;

							// ���� ���� ���� üũ
							AxmStatusReadStop(nAxisNo, &dwStatusEnd[nAxisNo]);
							dwStatusEnd[nAxisNo] &= 0x1FFFF;

							// ���� �ӵ� ����
							dblMotorSpeed[nAxisNo] = 5.0;

							// ��ȣ �˻� ���� ����
							if (!dwStatusEnd[nAxisNo] || dwStatusEnd[nAxisNo] & QIEND_STATUS_18 || dwStatusEnd[nAxisNo] & QIEND_STATUS_0) {

								// ������ ����Ʈ ���� ����
								if (dwStatusEnd[nAxisNo] & QIEND_STATUS_0) {

									// ���� �ӵ� ����
									dblMotorSpeed[nAxisNo] = m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch;

									TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
														nAxisNo + 1,
														g_stSystemString[SYSSTR_MOTION_HOME_STOP_LIMIT_POS].szDescription[m_nTypeLanguage],
														g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

									nCurrentStep[nAxisNo] = 220;
									break;
								}

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_STOP_DN_EDGE].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								nCurrentStep[nAxisNo] = 280;
								break;
							}

							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Status=%d(%X)"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_STOP_UNKNOWN].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dwStatusEnd[nAxisNo], dwStatusEnd[nAxisNo]);

							nCurrentStep[nAxisNo] = 290;
							break;

		// (-) �������� HOME ���� ��� ���� ���� �� ������
		case	280		:
							AxmMoveSignalSearch(nAxisNo,
												dblMotorSpeed[nAxisNo] * (-1.0),					// ���� �ӵ�
												m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration,	// ������ �ð�
												HomeSensor,											// ORG
												SIGNAL_UP_EDGE,										// ��� ����
												EMERGENCY_STOP);									// ������

							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Speed=%.2f"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_MOVE_NEG_UP_EDGE].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dblMotorSpeed[nAxisNo]);

							nCurrentStep[nAxisNo]++;
							break;

		case	281		:
							// ���� �̵� �Ϸ���� ���
							if (!Motion_Done(nAxisNo))	break;

							// ���� ���� ���� üũ
							AxmStatusReadStop(nAxisNo, &dwStatusEnd[nAxisNo]);
							dwStatusEnd[nAxisNo] &= 0x1FFFF;

							// ��ȣ �˻� ���� ����
							if (!dwStatusEnd[nAxisNo] || dwStatusEnd[nAxisNo] & QIEND_STATUS_18 || dwStatusEnd[nAxisNo] & QIEND_STATUS_1) {

								// ������ ����Ʈ ���� ����
								if (dwStatusEnd[nAxisNo] & QIEND_STATUS_1) {

									// ���� �ӵ� ����
									dblMotorSpeed[nAxisNo] = m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch;

									TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
														nAxisNo + 1,
														g_stSystemString[SYSSTR_MOTION_HOME_STOP_LIMIT_NEG].szDescription[m_nTypeLanguage],
														g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

									nCurrentStep[nAxisNo] = 270;
									break;
								}

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_STOP_UP_EDGE].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// ���� ���� ��� �÷��� ����
								m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo] = TRUE;

								nCurrentStep[nAxisNo] = 290;
								break;
							}

							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Status=%d(%X)"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_STOP_UNKNOWN].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dwStatusEnd[nAxisNo], dwStatusEnd[nAxisNo]);

							nCurrentStep[nAxisNo] = 290;
							break;

		// HOME �˻� �Ϸ�
		case	290		:
							// ���� ����
							AxmMoveSStop(nAxisNo);
							AxmMoveSStop(nAxisNo);

							nCurrentStep[nAxisNo]++;
							break;

		case	291		:
							if (Motion_Done(nAxisNo))
								nCurrentStep[nAxisNo]++;
							
							break;

		case	292		:
							// ���� ���� : OFF (�ĳ��Ҵ� ����)
							//AxmSignalServoOn(nAxisNo, DISABLE);
							//LTimerProceed[nAxisNo].Start(1000);

							nCurrentStep[nAxisNo]++;
							break;

		case	293		:
							if (LTimerProceed[nAxisNo].Verify()) {

								// ��ġ ī���� �ʱ�ȭ
								AxmStatusSetCmdPos(nAxisNo, 0);
								AxmStatusSetActPos(nAxisNo, 0);

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_COMPLETE].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// ���� ���� : ON (�ĳ��Ҵ� ����)
								//AxmSignalServoOn(nAxisNo, ENABLE);

								nCurrentStep[nAxisNo] = 900;
							}

							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� �ɼ� : P-LIMIT �켱 ���� ///////////////////////
		case	300		:
							nCurrentStep[nAxisNo] = 310;
							break;
							
		// (+) �������� ������ ����Ʈ ���� ��� ���� ���� �� ������
		case	310		:
							AxmMoveSignalSearch(nAxisNo,
												dblMotorSpeed[nAxisNo],								// ���� �ӵ�						
												m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration,	// ������ �ð�
												PosEndLimit,										// ������ ����Ʈ
												SIGNAL_UP_EDGE,										// ��� ����
												EMERGENCY_STOP);									// ������

							TestMessage(TRUE,	_T("[AXIS:%02d] %s (P-LIMIT)::%s, Speed=%.2f"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_MOVE_POS_UP_EDGE].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dblMotorSpeed[nAxisNo]);

							nCurrentStep[nAxisNo]++;
							break;

		case	311		:
							// ���� �̵� �Ϸ���� ���
							if (!Motion_Done(nAxisNo))	break;

							// ���� ���� ���� üũ
							AxmStatusReadStop(nAxisNo, &dwStatusEnd[nAxisNo]);
							dwStatusEnd[nAxisNo] &= 0x1FFFF;

							// ��ȣ �˻� ���� ����
							if (!dwStatusEnd[nAxisNo] || dwStatusEnd[nAxisNo] & QIEND_STATUS_18 || dwStatusEnd[nAxisNo] & QIEND_STATUS_0) {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_STOP_LIMIT_POS].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// ���� ���� ��� �÷��� ����
								m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo] = TRUE;

								nCurrentStep[nAxisNo] = 290;
								break;
							}

							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Status=%d(%X)"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_STOP_UNKNOWN].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dwStatusEnd[nAxisNo], dwStatusEnd[nAxisNo]);

							nCurrentStep[nAxisNo] = 290;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� �ɼ� : N-LIMIT �켱 ���� ///////////////////////
		case	400		:
							nCurrentStep[nAxisNo] = 410;
							break;
							
		// (-) �������� ������ ����Ʈ ���� ��� ���� ���� �� ������
		case	410		:
							AxmMoveSignalSearch(nAxisNo,
												dblMotorSpeed[nAxisNo] * (-1.0),					// ���� �ӵ�						
												m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration,	// ������ �ð�
												NegEndLimit,										// ������ ����Ʈ
												SIGNAL_UP_EDGE,										// ��� ����
												EMERGENCY_STOP);									// ������

							TestMessage(TRUE,	_T("[AXIS:%02d] %s (N-LIMIT)::%s, Speed=%.2f"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_MOVE_NEG_UP_EDGE].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dblMotorSpeed[nAxisNo]);

							nCurrentStep[nAxisNo]++;
							break;

		case	411		:
							// ���� �̵� �Ϸ���� ���
							if (!Motion_Done(nAxisNo))	break;

							// ���� ���� ���� üũ
							AxmStatusReadStop(nAxisNo, &dwStatusEnd[nAxisNo]);
							dwStatusEnd[nAxisNo] &= 0x1FFFF;

							// ��ȣ �˻� ���� ����
							if (!dwStatusEnd[nAxisNo] || dwStatusEnd[nAxisNo] & QIEND_STATUS_18 || dwStatusEnd[nAxisNo] & QIEND_STATUS_1) {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_STOP_LIMIT_NEG].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// ���� ���� ��� �÷��� ����
								m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo] = TRUE;

								nCurrentStep[nAxisNo] = 290;
								break;
							}

							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Status=%d(%X)"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_STOP_UNKNOWN].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dwStatusEnd[nAxisNo], dwStatusEnd[nAxisNo]);

							nCurrentStep[nAxisNo] = 290;
							break;


		/////////////////////////////////////////////////////////////
		// �Ϸ� /////////////////////////////////////////////////////
		case	900		:
							m_stSystemStatus.bOnMotion_HomeSearchStart[nAxisNo] = FALSE;

							if (m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo]) {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_SUCCESS].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);
							
							} else {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_FAILURE].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// ����Ʈ ����Ʈ ����
								Motion_SetSoftLimit(nAxisNo);
							}

							nCurrentStep[nAxisNo] = 0;
							break;


		/////////////////////////////////////////////////////////////
		// ��� ���� ���� ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop) {

									nCurrentStep[nAxisNo]	= nRecoveryStep[nAxisNo];
									bOnPause[nAxisNo]		= FALSE;
								}

								break;
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���� Ÿ�� �ƿ� üũ /////////////////////////////////////
	if (m_stSystemStatus.bOnMotion_HomeSearchStart[nAxisNo]) {

		if (LTimerTimeOut[nAxisNo].Verify()) {

			AxmMoveSStop(nAxisNo);
			AxmMoveSStop(nAxisNo);

			TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
								nAxisNo + 1,
								g_stSystemString[SYSSTR_MOTION_HOME_TIMEOUT].szDescription[m_nTypeLanguage],
								g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

			nCurrentStep[nAxisNo] = 900;
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� : ��� ���� ���� #2 (PL, NL) //////////////////////////////////////
void CMainApp::ProcessMotionHomeSearch02(UINT nAxisNo)
{
	static	UINT			nCurrentStep[MAX_MOTION_AXIS];
	static	UINT			nReturnStep[MAX_MOTION_AXIS];
	static	UINT			nPreviousStep[MAX_MOTION_AXIS];
	static	UINT			nRecoveryStep[MAX_MOTION_AXIS];
	static	UINT			nRetryCount[MAX_MOTION_AXIS];

	static	BOOL			bOnPause[MAX_MOTION_AXIS];

	static	DWORD			dwStatusPositive[MAX_MOTION_AXIS];
	static	DWORD			dwStatusNegative[MAX_MOTION_AXIS];
	static	DWORD			dwStatusHome[MAX_MOTION_AXIS];
	static	DWORD			dwStatusEnd[MAX_MOTION_AXIS];

	static	BYTE			byHomeMethod[MAX_MOTION_AXIS][3];
	static	DOUBLE			dblHomeVelocity[MAX_MOTION_AXIS][3];
	static	DOUBLE			dblHomeAcceleration[MAX_MOTION_AXIS][3];

	static	DOUBLE			dblMotorSpeed[MAX_MOTION_AXIS];

	static	LTimerMsec		LTimerProceed[MAX_MOTION_AXIS];
	static	LTimerMsec		LTimerTimeOut[MAX_MOTION_AXIS];


	/////////////////////////////////////////////////////////////////
	// ��� ���� ���� ///////////////////////////////////////////////
	if (m_stSystemStatus.bOnEmergencyStop && !bOnPause[nAxisNo]) {

		bOnPause[nAxisNo]		= TRUE;
		nRecoveryStep[nAxisNo]	= 0;
		nCurrentStep[nAxisNo]	= STEP_EMG;

		return;
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���μ��� ////////////////////////////////////////////////
	switch (nCurrentStep[nAxisNo]) {

		case	0		:
							nCurrentStep[nAxisNo] = 100;
							break;


		/////////////////////////////////////////////////////////////
		// ��� /////////////////////////////////////////////////////
		case	100		:
							if (m_stSystemStatus.bOnMotion_HomeSearchStart[nAxisNo]) {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_START].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// ����Ʈ ����Ʈ ����
								Motion_SetSoftLimit(nAxisNo, FALSE);

								// �÷��� �ʱ�ȭ
								m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo] = FALSE;

								// ���� ���� Ÿ�Ӿƿ� ����
								LTimerTimeOut[nAxisNo].Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_HOME_SEARCH));

								nCurrentStep[nAxisNo] = 200;
							}

							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� ////////////////////////////////////////////////
		case	200		:
							nCurrentStep[nAxisNo]++;
							break;

		// ���� ���� �ɼ�
		case	201		:
							// P-LIMIT �켱 ���� �ɼ�
							if (m_stSystemStatus.bOnMotion_HomeSearchOptionPLStop[nAxisNo]) {
							
								dblMotorSpeed[nAxisNo] = m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch;
								nCurrentStep[nAxisNo]  = 300;
								break;
							}

							// N-LIMIT �켱 ���� �ɼ�
							if (m_stSystemStatus.bOnMotion_HomeSearchOptionNLStop[nAxisNo]) {
							
								dblMotorSpeed[nAxisNo] = m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch;
								nCurrentStep[nAxisNo]  = 400;
								break;
							}
							
							nCurrentStep[nAxisNo] = 210;
							break;

		// LIMIT �˻� (N-LIMIT = HOME)
		case	210		:
							AxmSignalReadLimit(nAxisNo, &dwStatusPositive[nAxisNo], &dwStatusNegative[nAxisNo]);
							
							// N-LIMIT ���� ����
							if (dwStatusNegative[nAxisNo]) {
							
								dblMotorSpeed[nAxisNo] = m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch;
								nCurrentStep[nAxisNo]  = 270;
							
							} else {
							
								dblMotorSpeed[nAxisNo] = m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch;
								nCurrentStep[nAxisNo]  = 220;
							}

							break;

		// (-) �������� N-LIMIT ���� ��� ���� ���� �� ���� ����
		case	220		:
							AxmMoveSignalSearch(nAxisNo,
												dblMotorSpeed[nAxisNo] * (-1.0),					// ���� �ӵ�						
												m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration,	// ������ �ð�
												NegEndLimit,										// N-LIMIT
												SIGNAL_UP_EDGE,										// ��� ����
												SLOWDOWN_STOP);										// ���� ����

							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Speed=%.2f"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_MOVE_NEG_UP_EDGE].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dblMotorSpeed[nAxisNo]);

							nCurrentStep[nAxisNo]++;
							break;

		case	221		:
							// ���� �̵� �Ϸ���� ���
							if (!Motion_Done(nAxisNo))	break;

							// ���� ���� ���� üũ
							AxmStatusReadStop(nAxisNo, &dwStatusEnd[nAxisNo]);
							dwStatusEnd[nAxisNo] &= 0x1FFFF;

							// ���� �ӵ� ����
							dblMotorSpeed[nAxisNo] = 10.0;

							// ��ȣ �˻� ���� ����
							if (!dwStatusEnd[nAxisNo] || dwStatusEnd[nAxisNo] & QIEND_STATUS_18 || dwStatusEnd[nAxisNo] & QIEND_STATUS_1) {

								// ������ ����Ʈ ���� ����
								if (dwStatusEnd[nAxisNo] & QIEND_STATUS_1) {

									// ���� �ӵ� ����
									dblMotorSpeed[nAxisNo] = m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch;

									TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
														nAxisNo + 1,
														g_stSystemString[SYSSTR_MOTION_HOME_STOP_LIMIT_NEG].szDescription[m_nTypeLanguage],
														g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								} else {

									TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
														nAxisNo + 1,
														g_stSystemString[SYSSTR_MOTION_HOME_STOP_UP_EDGE].szDescription[m_nTypeLanguage],
														g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);
								}

								nCurrentStep[nAxisNo] = 270;
								break;
							}

							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Status=%d(%X)"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_STOP_UNKNOWN].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dwStatusEnd[nAxisNo], dwStatusEnd[nAxisNo]);

							nCurrentStep[nAxisNo] = 290;
							break;

		// (+) �������� N-LIMIT ���� �ϰ� ���� ���� �� ���� ����
		case	270		:
							AxmMoveSignalSearch(nAxisNo,
												dblMotorSpeed[nAxisNo],								// ���� �ӵ�						
												m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration,	// ������ �ð�
												NegEndLimit,										// N-LIMIT
												SIGNAL_DOWN_EDGE,									// �ϰ� ����
												SLOWDOWN_STOP);										// ���� ����

							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Speed=%.2f"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_MOVE_POS_DN_EDGE].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dblMotorSpeed[nAxisNo]);

							nCurrentStep[nAxisNo]++;
							break;

		case	271		:
							// ���� �̵� �Ϸ���� ���
							if (!Motion_Done(nAxisNo))	break;

							// ���� ���� ���� üũ
							AxmStatusReadStop(nAxisNo, &dwStatusEnd[nAxisNo]);
							dwStatusEnd[nAxisNo] &= 0x1FFFF;

							// ���� �ӵ� ����
							dblMotorSpeed[nAxisNo] = 5.0;

							// ��ȣ �˻� ���� ����
							if (!dwStatusEnd[nAxisNo] || dwStatusEnd[nAxisNo] & QIEND_STATUS_18 || dwStatusEnd[nAxisNo] & QIEND_STATUS_0) {

								// ������ ����Ʈ ���� ����
								if (dwStatusEnd[nAxisNo] & QIEND_STATUS_0) {

									// ���� �ӵ� ����
									dblMotorSpeed[nAxisNo] = m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch;

									TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
														nAxisNo + 1,
														g_stSystemString[SYSSTR_MOTION_HOME_STOP_LIMIT_POS].szDescription[m_nTypeLanguage],
														g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

									nCurrentStep[nAxisNo] = 220;
									break;
								}

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_STOP_DN_EDGE].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								nCurrentStep[nAxisNo] = 280;
								break;
							}

							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Status=%d(%X)"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_STOP_UNKNOWN].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dwStatusEnd[nAxisNo], dwStatusEnd[nAxisNo]);

							nCurrentStep[nAxisNo] = 290;
							break;

		// (-) �������� N-LIMIT ���� ��� ���� ���� �� ������
		case	280		:
							AxmMoveSignalSearch(nAxisNo,
												dblMotorSpeed[nAxisNo] * (-1.0),					// ���� �ӵ�
												m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration,	// ������ �ð�
												NegEndLimit,										// N-LIMIT
												SIGNAL_UP_EDGE,										// ��� ����
												EMERGENCY_STOP);									// ������

							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Speed=%.2f"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_MOVE_NEG_UP_EDGE].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dblMotorSpeed[nAxisNo]);

							nCurrentStep[nAxisNo]++;
							break;

		case	281		:
							// ���� �̵� �Ϸ���� ���
							if (!Motion_Done(nAxisNo))	break;

							// ���� ���� ���� üũ
							AxmStatusReadStop(nAxisNo, &dwStatusEnd[nAxisNo]);
							dwStatusEnd[nAxisNo] &= 0x1FFFF;

							// ��ȣ �˻� ���� ����
							if (!dwStatusEnd[nAxisNo] || dwStatusEnd[nAxisNo] & QIEND_STATUS_18 || dwStatusEnd[nAxisNo] & QIEND_STATUS_1) {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_STOP_LIMIT_NEG].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// ���� ���� ��� �÷��� ����
								m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo] = TRUE;

								nCurrentStep[nAxisNo] = 290;
								break;
							}

							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Status=%d(%X)"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_STOP_UNKNOWN].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dwStatusEnd[nAxisNo], dwStatusEnd[nAxisNo]);

							nCurrentStep[nAxisNo] = 290;
							break;

		// HOME �˻� �Ϸ�
		case	290		:
							// ���� ����
							AxmMoveSStop(nAxisNo);
							AxmMoveSStop(nAxisNo);

							nCurrentStep[nAxisNo]++;
							break;

		case	291		:
							if (Motion_Done(nAxisNo))
								nCurrentStep[nAxisNo]++;
							
							break;

		case	292		:
							// ���� ���� : OFF (�ĳ��Ҵ� ����)
							//AxmSignalServoOn(nAxisNo, DISABLE);
							//LTimerProceed[nAxisNo].Start(1000);

							nCurrentStep[nAxisNo]++;
							break;

		case	293		:
							if (LTimerProceed[nAxisNo].Verify()) {

								// ��ġ ī���� �ʱ�ȭ
								AxmStatusSetCmdPos(nAxisNo, 0);
								AxmStatusSetActPos(nAxisNo, 0);

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_COMPLETE].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// ���� ���� : ON (�ĳ��Ҵ� ����)
								//AxmSignalServoOn(nAxisNo, ENABLE);

								nCurrentStep[nAxisNo] = 900;
							}

							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� �ɼ� : P-LIMIT �켱 ���� ///////////////////////
		case	300		:
							nCurrentStep[nAxisNo] = 310;
							break;
							
		// (+) �������� ������ ����Ʈ ���� ��� ���� ���� �� ������
		case	310		:
							AxmMoveSignalSearch(nAxisNo,
												dblMotorSpeed[nAxisNo],								// ���� �ӵ�						
												m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration,	// ������ �ð�
												PosEndLimit,										// ������ ����Ʈ
												SIGNAL_UP_EDGE,										// ��� ����
												EMERGENCY_STOP);									// ������

							TestMessage(TRUE,	_T("[AXIS:%02d] %s (P-LIMIT)::%s, Speed=%.2f"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_MOVE_POS_UP_EDGE].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dblMotorSpeed[nAxisNo]);

							nCurrentStep[nAxisNo]++;
							break;

		case	311		:
							// ���� �̵� �Ϸ���� ���
							if (!Motion_Done(nAxisNo))	break;

							// ���� ���� ���� üũ
							AxmStatusReadStop(nAxisNo, &dwStatusEnd[nAxisNo]);
							dwStatusEnd[nAxisNo] &= 0x1FFFF;

							// ��ȣ �˻� ���� ����
							if (!dwStatusEnd[nAxisNo] || dwStatusEnd[nAxisNo] & QIEND_STATUS_18 || dwStatusEnd[nAxisNo] & QIEND_STATUS_0) {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_STOP_LIMIT_POS].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// ���� ���� ��� �÷��� ����
								m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo] = TRUE;

								nCurrentStep[nAxisNo] = 290;
								break;
							}

							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Status=%d(%X)"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_STOP_UNKNOWN].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dwStatusEnd[nAxisNo], dwStatusEnd[nAxisNo]);

							nCurrentStep[nAxisNo] = 290;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� �ɼ� : N-LIMIT �켱 ���� ///////////////////////
		case	400		:
							nCurrentStep[nAxisNo] = 410;
							break;
							
		// (-) �������� ������ ����Ʈ ���� ��� ���� ���� �� ������
		case	410		:
							AxmMoveSignalSearch(nAxisNo,
												dblMotorSpeed[nAxisNo] * (-1.0),					// ���� �ӵ�						
												m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration,	// ������ �ð�
												NegEndLimit,										// ������ ����Ʈ
												SIGNAL_UP_EDGE,										// ��� ����
												EMERGENCY_STOP);									// ������

							TestMessage(TRUE,	_T("[AXIS:%02d] %s (N-LIMIT)::%s, Speed=%.2f"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_MOVE_NEG_UP_EDGE].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dblMotorSpeed[nAxisNo]);

							nCurrentStep[nAxisNo]++;
							break;

		case	411		:
							// ���� �̵� �Ϸ���� ���
							if (!Motion_Done(nAxisNo))	break;

							// ���� ���� ���� üũ
							AxmStatusReadStop(nAxisNo, &dwStatusEnd[nAxisNo]);
							dwStatusEnd[nAxisNo] &= 0x1FFFF;

							// ��ȣ �˻� ���� ����
							if (!dwStatusEnd[nAxisNo] || dwStatusEnd[nAxisNo] & QIEND_STATUS_18 || dwStatusEnd[nAxisNo] & QIEND_STATUS_1) {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_STOP_LIMIT_NEG].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// ���� ���� ��� �÷��� ����
								m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo] = TRUE;

								nCurrentStep[nAxisNo] = 290;
								break;
							}

							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Status=%d(%X)"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_STOP_UNKNOWN].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dwStatusEnd[nAxisNo], dwStatusEnd[nAxisNo]);

							nCurrentStep[nAxisNo] = 290;
							break;


		/////////////////////////////////////////////////////////////
		// �Ϸ� /////////////////////////////////////////////////////
		case	900		:
							m_stSystemStatus.bOnMotion_HomeSearchStart[nAxisNo] = FALSE;

							if (m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo]) {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_SUCCESS].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);
							
							} else {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_FAILURE].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// ����Ʈ ����Ʈ ����
								Motion_SetSoftLimit(nAxisNo);
							}

							nCurrentStep[nAxisNo] = 0;
							break;


		/////////////////////////////////////////////////////////////
		// ��� ���� ���� ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop) {

									nCurrentStep[nAxisNo]	= nRecoveryStep[nAxisNo];
									bOnPause[nAxisNo]		= FALSE;
								}

								break;
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���� Ÿ�� �ƿ� üũ /////////////////////////////////////
	if (m_stSystemStatus.bOnMotion_HomeSearchStart[nAxisNo]) {

		if (LTimerTimeOut[nAxisNo].Verify()) {

			AxmMoveSStop(nAxisNo);
			AxmMoveSStop(nAxisNo);

			TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
								nAxisNo + 1,
								g_stSystemString[SYSSTR_MOTION_HOME_TIMEOUT].szDescription[m_nTypeLanguage],
								g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

			nCurrentStep[nAxisNo] = 900;
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� : ��� ���� ���� #3 (AXT ����) ////////////////////////////////////
void CMainApp::ProcessMotionHomeSearch03(UINT nAxisNo, UINT nSignalNo)
{
	static	UINT			nCurrentStep[MAX_MOTION_AXIS];
	static	UINT			nReturnStep[MAX_MOTION_AXIS];
	static	UINT			nPreviousStep[MAX_MOTION_AXIS];
	static	UINT			nRecoveryStep[MAX_MOTION_AXIS];
	static	UINT			nRetryCount[MAX_MOTION_AXIS];

	static	BOOL			bOnPause[MAX_MOTION_AXIS];

	static	DWORD			dwStatusPositive[MAX_MOTION_AXIS];
	static	DWORD			dwStatusNegative[MAX_MOTION_AXIS];
	static	DWORD			dwStatusHome[MAX_MOTION_AXIS];
	static	DWORD			dwStatusEnd[MAX_MOTION_AXIS];

	static	BYTE			byHomeMethod[MAX_MOTION_AXIS][3];
	static	DOUBLE			dblHomeVelocity[MAX_MOTION_AXIS][3];
	static	DOUBLE			dblHomeAcceleration[MAX_MOTION_AXIS][3];

	static	DOUBLE			dblMotorSpeed[MAX_MOTION_AXIS];

	static	LTimerMsec		LTimerProceed[MAX_MOTION_AXIS];
	static	LTimerMsec		LTimerTimeOut[MAX_MOTION_AXIS];


	/////////////////////////////////////////////////////////////////
	// ��� ���� ���� ///////////////////////////////////////////////
	if (m_stSystemStatus.bOnEmergencyStop && !bOnPause[nAxisNo]) {

		bOnPause[nAxisNo]		= TRUE;
		nRecoveryStep[nAxisNo]	= 0;
		nCurrentStep[nAxisNo]	= STEP_EMG;

		return;
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���μ��� ////////////////////////////////////////////////
	switch (nCurrentStep[nAxisNo]) {

		case	0		:
							nCurrentStep[nAxisNo] = 100;
							break;


		/////////////////////////////////////////////////////////////
		// ��� /////////////////////////////////////////////////////
		case	100		:
							if (m_stSystemStatus.bOnMotion_HomeSearchStart[nAxisNo]) {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_START].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// ����Ʈ ����Ʈ ����
								Motion_SetSoftLimit(nAxisNo, FALSE);

								// �÷��� �ʱ�ȭ
								m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo] = FALSE;

								// ���� ���� Ÿ�Ӿƿ� ����
								LTimerTimeOut[nAxisNo].Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_HOME_SEARCH));

								nCurrentStep[nAxisNo] = 110;
							}

							break;

		// ���� ���� ��� ����
		case	110		:
							if (m_SystemConfig.UseMotionHomeSearch(nAxisNo)) {

								// BY1, BY2, HZ1, HZ2, LY1, LY2, HOME ��ġ �켱 �̵�
// 								if (nAxisNo == MOTION_RBY1 || nAxisNo == MOTION_RBY2 ||
// 									nAxisNo == MOTION_RHZ1 || nAxisNo == MOTION_RHZ2 ||
// 									nAxisNo == MOTION_RLY1 || nAxisNo == MOTION_RLY2) {
// 
// 									nCurrentStep[nAxisNo] = 120;
// 									break;
// 								}
							
								nCurrentStep[nAxisNo] = 200;
								break;
							}

							m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo] = TRUE;

							nCurrentStep[nAxisNo] = 900;
							break;

		// HOME ��ġ�� �̵�
		case	120		:
							{
								DWORD	dwStatusHome	= 0;


								// HOME ���� üũ
								AxmSignalReadInputBit(nAxisNo, 0, &dwStatusHome);
								if (!dwStatusHome) {

									AxmMoveSignalSearch(nAxisNo,
														0 - m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch,
														m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration,
														nSignalNo, SIGNAL_UP_EDGE, EMERGENCY_STOP);

									TestMessage(TRUE, _T("[AXIS:%02d] %s::%s, Speed=%.2f"),
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_MOVE_POS_UP_EDGE].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dblMotorSpeed[nAxisNo]);

									nCurrentStep[nAxisNo]++;
									break;
								}

								nCurrentStep[nAxisNo] = 200;
							}

							break;

		case	121		:
							if (Motion_Done(nAxisNo)) {
							
								// ���� ���� ���� üũ
								AxmStatusReadStop(nAxisNo, &dwStatusEnd[nAxisNo]);
								dwStatusEnd[nAxisNo] &= 0x1FFFF;

								// ��ȣ �˻� ���� ����
								if (!dwStatusEnd[nAxisNo] || dwStatusEnd[nAxisNo] & QIEND_STATUS_18 || dwStatusEnd[nAxisNo] & QIEND_STATUS_1) {

									// ������ ����Ʈ ���� ����
									if (dwStatusEnd[nAxisNo] & QIEND_STATUS_1) {

										TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
															nAxisNo + 1,
															g_stSystemString[SYSSTR_MOTION_HOME_STOP_LIMIT_NEG].szDescription[m_nTypeLanguage],
															g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

									} else {

										TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
															nAxisNo + 1,
															g_stSystemString[SYSSTR_MOTION_HOME_STOP_UP_EDGE].szDescription[m_nTypeLanguage],
															g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);
									}

									nCurrentStep[nAxisNo] = 200;
									break;
								}

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Status=%d(%X)"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_STOP_UNKNOWN].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
													dwStatusEnd[nAxisNo], dwStatusEnd[nAxisNo]);

								nCurrentStep[nAxisNo] = 290;
							}

							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� ////////////////////////////////////////////////
		case	200		:
							nCurrentStep[nAxisNo] = 210;
							break;

		// �Ķ���� ����
		case	210		:
							{
								// �޼ҵ� ����
								AxmHomeSetMethod(nAxisNo,			
												 DIR_CCW,			// �ʱ� ���� ����
												 nSignalNo,			// ���� ��ȣ
												 0,					// Z-Phas ��� ����
												 500,				// ���� �˻� �� ī���� ���� ��� �ð�
												 0);				// ���� �˻� �� ������ �̵� ��ġ
								
								// �ӵ� ����
								AxmHomeSetVel(nAxisNo, 
											  m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch,			// �ʱ� ���� �ӵ� (���� = OFF)
											  m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch * 0.5,		// �ʱ� ���� �ӵ� (���� = ON)
											  10.0,														// 2�� �˻� ���� �ӵ�
											  1.0,														// ������ �˻� �ӵ�
											  m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration,			// ������ �ӵ� (���� = OFF)
											  m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration);			// ������ �ӵ� (���� = ON)

								nCurrentStep[nAxisNo] = 220;		
							}

							break;

		// ���� �˻� ����
		case	220		:
							AxmHomeSetStart(nAxisNo);

							nCurrentStep[nAxisNo]++;
							break;

		case	221		:
							AxmHomeGetResult(nAxisNo, &dwStatusHome[nAxisNo]);

							if (dwStatusHome[nAxisNo] == HOME_SEARCHING)
								break;

							if (dwStatusHome[nAxisNo] == HOME_SUCCESS) {
							
								m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo] = TRUE;
							
							} else {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Status=%d(%X)"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_STOP_UNKNOWN].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
													dwStatusHome[nAxisNo], dwStatusHome[nAxisNo]);
							}

							nCurrentStep[nAxisNo] = 290;
							break;

		// HOME �˻� �Ϸ�
		case	290		:
							// ���� ����
							AxmMoveSStop(nAxisNo);
							AxmMoveSStop(nAxisNo);

							nCurrentStep[nAxisNo]++;
							break;

		case	291		:
							if (Motion_Done(nAxisNo))
								nCurrentStep[nAxisNo]++;
							
							break;

		case	292		:
							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_COMPLETE].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

							nCurrentStep[nAxisNo] = 900;
							break;


		/////////////////////////////////////////////////////////////
		// �Ϸ� /////////////////////////////////////////////////////
		case	900		:
							m_stSystemStatus.bOnMotion_HomeSearchStart[nAxisNo] = FALSE;

							if (m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo]) {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_SUCCESS].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);
							
							} else {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_FAILURE].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);
							}

							nCurrentStep[nAxisNo] = m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo] ? 910 : 0;
							break;

		// Ȩ ��ġ �̵�
		case	910		:
							if (m_stSystemStatus.bOnMotion_HomeSearchOptionMoveHome[nAxisNo]) {
							
								Motion_MoveTo(nAxisNo, 
											  m_stMotionAxisInfo[nAxisNo].dblCustomPosition[MAI_CPOS_HOME], 
											  m_stMotionAxisInfo[nAxisNo].dblSpeedBase);

								nCurrentStep[nAxisNo]++;
								break;
							}

							nCurrentStep[nAxisNo] = 990;
							break;

		case	911		:
							if (Motion_Done(nAxisNo))
								nCurrentStep[nAxisNo] = 990;

							break;

		// �Ϸ�
		case	990		:
							// ����Ʈ ����Ʈ ����
							Motion_SetSoftLimit(nAxisNo);

							nCurrentStep[nAxisNo] = 0;
							break;


		/////////////////////////////////////////////////////////////
		// ��� ���� ���� ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop) {

									nCurrentStep[nAxisNo]	= nRecoveryStep[nAxisNo];
									bOnPause[nAxisNo]		= FALSE;
								}

								break;
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���� Ÿ�� �ƿ� üũ /////////////////////////////////////
	if (m_stSystemStatus.bOnMotion_HomeSearchStart[nAxisNo]) {

		if (LTimerTimeOut[nAxisNo].Verify()) {

			AxmMoveSStop(nAxisNo);
			AxmMoveSStop(nAxisNo);

			TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
								nAxisNo + 1,
								g_stSystemString[SYSSTR_MOTION_HOME_TIMEOUT].szDescription[m_nTypeLanguage],
								g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

			nCurrentStep[nAxisNo] = 900;
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� : ��� ���� ���� #4 (SMC ������) //////////////////////////////////
void CMainApp::ProcessMotionHomeSearch04(UINT nAxisNo)
{
	static	UINT			nCurrentStep[MAX_MOTION_AXIS];
	static	UINT			nReturnStep[MAX_MOTION_AXIS];
	static	UINT			nPreviousStep[MAX_MOTION_AXIS];
	static	UINT			nRecoveryStep[MAX_MOTION_AXIS];
	static	UINT			nRetryCount[MAX_MOTION_AXIS];

	static	BOOL			bOnPause[MAX_MOTION_AXIS];

	static	DWORD			dwStatusPositive[MAX_MOTION_AXIS];
	static	DWORD			dwStatusNegative[MAX_MOTION_AXIS];
	static	DWORD			dwStatusHome[MAX_MOTION_AXIS];
	static	DWORD			dwStatusEnd[MAX_MOTION_AXIS];

	static	BYTE			byHomeMethod[MAX_MOTION_AXIS][3];
	static	DOUBLE			dblHomeVelocity[MAX_MOTION_AXIS][3];
	static	DOUBLE			dblHomeAcceleration[MAX_MOTION_AXIS][3];

	static	DOUBLE			dblMotorSpeed[MAX_MOTION_AXIS];

	static	LTimerMsec		LTimerProceed[MAX_MOTION_AXIS];
	static	LTimerMsec		LTimerReady[MAX_MOTION_AXIS];
	static	LTimerMsec		LTimerTimeOut[MAX_MOTION_AXIS];
	

	/////////////////////////////////////////////////////////////////
	// ��� ���� ���� ///////////////////////////////////////////////
	if (m_stSystemStatus.bOnEmergencyStop && !bOnPause[nAxisNo]) {

		bOnPause[nAxisNo]		= TRUE;
		nRecoveryStep[nAxisNo]	= 0;
		nCurrentStep[nAxisNo]	= STEP_EMG;

		return;
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���μ��� ////////////////////////////////////////////////
	switch (nCurrentStep[nAxisNo]) {

		case	0		:
							nCurrentStep[nAxisNo] = 100;
							break;


		/////////////////////////////////////////////////////////////
		// ��� /////////////////////////////////////////////////////
		case	100		:
							if (m_stSystemStatus.bOnMotion_HomeSearchStart[nAxisNo]) {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_START].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// ����Ʈ ����Ʈ ����
								Motion_SetSoftLimit(nAxisNo, FALSE);

								// �÷��� �ʱ�ȭ
								m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo] = FALSE;

								// ���� ���� Ÿ�Ӿƿ� ����
								LTimerTimeOut[nAxisNo].Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_HOME_SEARCH));

								nCurrentStep[nAxisNo] = 110;
							}

							break;

		// ���� ���� ��� ����
		case	110		:
							if (m_SystemConfig.UseMotionHomeSearch(nAxisNo)) {
							
								nCurrentStep[nAxisNo] = 200;
								break;
							}

							m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo] = TRUE;

							nCurrentStep[nAxisNo] = 900;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� ////////////////////////////////////////////////
		case	200		:
							nCurrentStep[nAxisNo] = 210;

		// �غ� �۾�
		case	210		:
							// ���� ���� ���� ��ȣ ����
							AxmSignalWriteOutputBit(nAxisNo, UIO_OUT3, DISABLE);

							LTimerProceed[nAxisNo].Start(2000);

							nCurrentStep[nAxisNo]++;
							break;

		case	211		:
							if (LTimerProceed[nAxisNo].Verify())
								nCurrentStep[nAxisNo] = 220;

							break;

		// �˶� ����
		case	220		:
							AxmSignalServoAlarmReset(nAxisNo, ENABLE);
							LTimerProceed[nAxisNo].Start(1000);

							nCurrentStep[nAxisNo]++;
							break;

		case	221		:
							if (LTimerProceed[nAxisNo].Verify()) {
							
								AxmSignalServoAlarmReset(nAxisNo, DISABLE);
								LTimerProceed[nAxisNo].Start(1000);
							
								nCurrentStep[nAxisNo]++;
							}
								

							break;

		case	222		:
							if (LTimerProceed[nAxisNo].Verify())
								nCurrentStep[nAxisNo] = 230;

							break;

		// �غ� ��ȣ ���
		case	230		:
							LTimerReady[nAxisNo].Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_HOME_READY));

							nCurrentStep[nAxisNo]++;
							break;

		case	231		:
							{
								DWORD	dwStatus	= 0;

								AxmSignalReadInputBit(nAxisNo, UIO_INP4, &dwStatus);

								if (dwStatus) {
								
									nCurrentStep[nAxisNo] = 240;
									break;
								}

								if (LTimerReady[nAxisNo].Verify())
									nCurrentStep[nAxisNo] = 900;
							}

							break;

		// ���� �˻� ����
		case	240		:
							{
								// ���� ���� ���� ��ȣ ���
								AxmSignalWriteOutputBit(nAxisNo, UIO_OUT3, ENABLE);

								nCurrentStep[nAxisNo]++;		
							}

							break;

		case	241		:
							{
								DWORD	dwStatus	= 0;


								// Ȩ �ñ׳� ����
								AxmSignalReadInputBit(nAxisNo, 0, &dwStatus);
								if (dwStatus) {
								
									m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo] = TRUE;

									// ���� ���� ���� ��ȣ ����
									AxmSignalWriteOutputBit(nAxisNo, UIO_OUT3, DISABLE);

									nCurrentStep[nAxisNo] = 290;
								}

								// ���� ���� ����
								if (!m_stSystemStatus.bOnMotion_HomeSearchStart[nAxisNo]) {

									// ���� ���� ���� ��ȣ ����
									AxmSignalWriteOutputBit(nAxisNo, UIO_OUT3, DISABLE);

									nCurrentStep[nAxisNo] = 0;
								}

								// �˶� üũ
								AxmSignalReadServoAlarm(nAxisNo, &dwStatus);
								if (dwStatus) {

									NormalMessage(TRUE,	_T("[AXIS:%02d] SERVO ALARM STATUS::%s"),	
														nAxisNo + 1,
														g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

									nCurrentStep[nAxisNo] = 210;
								}
							}

							break;

		// HOME �˻� �Ϸ�
		case	290		:
							// ���� ����
							AxmMoveSStop(nAxisNo);
							AxmMoveSStop(nAxisNo);

							nCurrentStep[nAxisNo]++;
							break;

		case	291		:
							if (Motion_Done(nAxisNo))
								nCurrentStep[nAxisNo]++;
							
							break;

		case	292		:
							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_COMPLETE].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

							nCurrentStep[nAxisNo] = 900;
							break;


		/////////////////////////////////////////////////////////////
		// �Ϸ� /////////////////////////////////////////////////////
		case	900		:
							m_stSystemStatus.bOnMotion_HomeSearchStart[nAxisNo] = FALSE;

							if (m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo]) {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_SUCCESS].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);
							
							} else {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_FAILURE].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);
							}

							nCurrentStep[nAxisNo] = m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo] ? 910 : 0;
							break;

		// Ȩ ��ġ �̵�
		case	910		:
							if (m_stSystemStatus.bOnMotion_HomeSearchOptionMoveHome[nAxisNo]) {
							
								Motion_MoveTo(nAxisNo, 
											  m_stMotionAxisInfo[nAxisNo].dblCustomPosition[MAI_CPOS_HOME], 
											  m_stMotionAxisInfo[nAxisNo].dblSpeedBase);

								nCurrentStep[nAxisNo]++;
								break;
							}

							nCurrentStep[nAxisNo] = 990;
							break;

		case	911		:
							if (Motion_Done(nAxisNo))
								nCurrentStep[nAxisNo] = 990;

							break;

		// �Ϸ�
		case	990		:
							// ����Ʈ ����Ʈ ����
							Motion_SetSoftLimit(nAxisNo);

							nCurrentStep[nAxisNo] = 0;
							break;


		/////////////////////////////////////////////////////////////
		// ��� ���� ���� ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop) {

									nCurrentStep[nAxisNo]	= nRecoveryStep[nAxisNo];
									bOnPause[nAxisNo]		= FALSE;
								}

								break;
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���� Ÿ�� �ƿ� üũ /////////////////////////////////////
	if (m_stSystemStatus.bOnMotion_HomeSearchStart[nAxisNo]) {

		if (LTimerTimeOut[nAxisNo].Verify()) {

			AxmMoveSStop(nAxisNo);
			AxmMoveSStop(nAxisNo);

			TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
								nAxisNo + 1,
								g_stSystemString[SYSSTR_MOTION_HOME_TIMEOUT].szDescription[m_nTypeLanguage],
								g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

			nCurrentStep[nAxisNo] = 900;
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� : ��� �ʱ�ȭ /////////////////////////////////////////////////////
PERROR_CODE_T CMainApp::ProcessMachineInit(void)
{
	static	UINT				nCurrentStep		= 0;
	static	UINT				nReturnStep			= 0;
	static	UINT				nPreviousStep		= 0;
	static	UINT				nRecoveryStep		= 0;

	static	UINT				nRetryCount			= 0;
	static	UINT				nIndexDevice		= 0;

	static	BOOL				bOnPause			= FALSE;
	static	BOOL				bIsStepMoveHome		= FALSE;

	static	LTimerMsec			LTimerProceed;
	static	LTimerMsec			LTimerTimeOut;
	static	LTimerMsec			LTimerSteady;
	static	LTimerMsec			LTimerSystemMonitor;

	static	ERROR_CODE_T		stErrorCode;
	static	SYSTEM_CONFIG_T		stSystemConfig;

	BOOL						bOnError			= FALSE;
	PERROR_CODE_T				pstErrorCode		= NULL;

	BOOL						bOnUpdateUI			= FALSE;
	UI_PARAM_UPDATE_T			stParamUI;


	/////////////////////////////////////////////////////////////////
	// ���� �ʱ�ȭ //////////////////////////////////////////////////
	ZeroMemory(&stErrorCode, sizeof(ERROR_CODE_T));
	ZeroMemory(&stParamUI, sizeof(UI_PARAM_UPDATE_T));


	/////////////////////////////////////////////////////////////////
	// ��� ���� ���� ///////////////////////////////////////////////
	if (m_stSystemStatus.bOnEmergencyStop && !bOnPause) {

		bOnPause		= TRUE;
		nRecoveryStep	= 0;
		nCurrentStep	= STEP_EMG;

		return	NULL;
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���μ��� ////////////////////////////////////////////////
	switch (nCurrentStep) {

		/////////////////////////////////////////////////////////////
		// ��� /////////////////////////////////////////////////////
		case	0		:
							if (m_stSystemStatus.bOnMachineInitialize) {

								TestMessage(TRUE, _T("%s"), g_stSystemString[SYSSTR_MC_INIT_START].szDescription[m_nTypeLanguage]);

								// �÷��� �ʱ�ȭ
								m_stSystemStatus.bOnMotion_CheckServoMotorAlarm = FALSE;
								for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++)
									m_stSystemStatus.bOnMotion_HomeSearchStart[nAxisNo]	= FALSE;

								// ����� �޼��� ����
								ClearUserMessage();
								m_stSystemStatus.nCurrentUserMessage = UMSG_WARN_MACHINE_INITIALIZING;

								// ��� �ʱ�ȭ ��� �ʱ�ȭ
								m_stSystemStatus.bResultMachineInitialize = FALSE;

								// ������ 1ȸ ���
								m_stSystemStatus.nBeepCount = 1;

								nRetryCount  = 0;
								nCurrentStep = STEP_INIT_INIT;
							}

							break;	


		/////////////////////////////////////////////////////////////
		// �ʱ�ȭ �غ� //////////////////////////////////////////////
		case	STEP_INIT_INIT	:
									nCurrentStep = 110;
									break;

		// ��� ���� �÷��� �ʱ�ȭ
		case	110		:
							ZeroMemory(m_stSystemStatus.bOnMP_Error, sizeof(BOOL) * MAX_STATION);
							ZeroMemory(m_stSystemStatus.bOnSCP_MoveParts, sizeof(BOOL) * MAX_STATION * MAX_STATION_CONTROL);

							nCurrentStep = 190;
							break;

		// �Ϸ�
		case	190		:
							nCurrentStep = STEP_INIT_DEVICE;
							break;


		/////////////////////////////////////////////////////////////
		// ����̽� �ʱ�ȭ //////////////////////////////////////////
		case	STEP_INIT_DEVICE	:
										nCurrentStep = 4200;
										break;

		// ������ ��Ƽ���� �ʱ�ȭ
		case	4200	:
							nIndexDevice = 0;

							nCurrentStep = 4210;
							break;

		case	4210	:
							TestMessage(TRUE,	_T("%s (DIGITAL MULTIMETER)"),	
												g_stSystemString[SYSSTR_MC_INIT_MEAS_DEVICE_START].szDescription[m_nTypeLanguage]);

							// ����̽� üũ
							if (m_stSystemStatus.nDeviceStatus[SD_DEV_DMM] != DS_NORMAL) {
							
								nCurrentStep = STEP_INIT_ERROR_DEV_DMM;
								break;
							}

							nCurrentStep = 4220;
							break;

		case	4220	:
							// ���� ����
							if (!m_devDMM.SetSystemCommand(FLKDMM_SYS_CLS)) {

								nCurrentStep = STEP_INIT_ERROR_DEV_DMM;
								break;
							}

							LTimerSteady.Start(FLKDMM_DLY_SETUP);
							nCurrentStep = 4230;
							break;

		case	4230	:
							// ���� ��� : DCV
							if (LTimerSteady.Verify()) {

								if (!m_devDMM.SetMeasurementMode(FLKDMM_MODE_DCV)) {

									nCurrentStep = STEP_INIT_ERROR_DEV_DMM;
									break;
								}

								LTimerSteady.Start(FLKDMM_DLY_SETUP);
								nCurrentStep = 4240;
							}

							break;

		case	4240	:
							// ����Ʈ ��� ����
							if (LTimerSteady.Verify()) {

								if (!m_devDMM.SetSystemCommand(FLKDMM_SYS_REMOTE_LOCK)) {

									nCurrentStep = STEP_INIT_ERROR_DEV_DMM;
									break;
								}

								LTimerSteady.Start(FLKDMM_DLY_SETUP);
								nCurrentStep = 4290;
							}

							break;

		case	4290	:
							TestMessage(TRUE,	_T("%s (DIGITAL MULTIMETER)"),	
												g_stSystemString[SYSSTR_MC_INIT_MEAS_DEVICE_COMPLETE].szDescription[m_nTypeLanguage]);

							nCurrentStep = 4900;
							break;

		// �Ϸ�
		case	4900	:
							nCurrentStep = STEP_INIT_STN;
							break;


		/////////////////////////////////////////////////////////////
		// ���� �ʱ�ȭ //////////////////////////////////////////////
		case	STEP_INIT_STN	:
									TestMessage(TRUE, _T("%s"), g_stSystemString[SYSSTR_MC_INIT_STATION_START].szDescription[m_nTypeLanguage]);

									nCurrentStep = 210;
									break;

		case	210		:
							nCurrentStep = 230;
							break;
							
		// ���� �ʱ�ȭ
		case	230		:
							for (UINT nStationNo = STATION_1; nStationNo < MAX_STATION; nStationNo++) {

								m_stSystemStatus.bOnStationInitialize[nStationNo][0] = TRUE;
							}

							nCurrentStep++;
							break;

		case	231		:
							{
								BOOL	bIsComplete = TRUE;
																
								for (UINT nStationNo = STATION_1; nStationNo < MAX_STATION; nStationNo++) {

									bIsComplete &= !m_stSystemStatus.bOnStationInitialize[nStationNo][0];
								}
																
								// ��� �����̼��� �Ϸ�Ǹ� ���� �������� ����
								if (bIsComplete)	nCurrentStep++;
							}

							break;

		case	232		:
							{
								BOOL	bInitResult	= TRUE;

								for (UINT nStationNo = STATION_1; nStationNo < MAX_STATION; nStationNo++) {

									bInitResult &= m_stSystemStatus.bOnStationInitializeResult[nStationNo][0];

									if (!m_stSystemStatus.bOnStationInitializeResult[nStationNo][0])
										MessageWindow(cDEBUG, _T("STATION #%d Initialize Failure"), nStationNo);
								}
																
								nCurrentStep = bInitResult ? 290 : STEP_INIT_ERROR_STATION;
							}

							break;

		// �Ϸ�
		case	290		:
							TestMessage(TRUE, _T("%s"), g_stSystemString[SYSSTR_MC_INIT_STATION_COMPLETE].szDescription[m_nTypeLanguage]);

							nCurrentStep = STEP_INIT_MOTION;
							break;


		/////////////////////////////////////////////////////////////
		// ��� �ʱ�ȭ //////////////////////////////////////////////
		case	STEP_INIT_MOTION	:
										TestMessage(TRUE, _T("%s"), g_stSystemString[SYSSTR_MC_INIT_MOTION_START].szDescription[m_nTypeLanguage]);

										nCurrentStep++;
										break;

		// ��� ��Ʈ�ѷ� ����
		case	401		:
							{
								// ��� ��Ʈ�ѷ� �� ����
								//if (AxlIsOpened())	AxlClose();

								//LONG	lResult	= AxlOpen(7);
								//if (lResult == AXT_RT_SUCCESS) {

								//	nCurrentStep[nCHANNEL_NO]++;

								//} else {

								//	SErrorMessage(FALSE, _T("��� ��Ʈ�ѷ��� ������ �� �����ϴ�."));
								//	nCurrentStep[nCHANNEL_NO] = STEP_INIT_ERROR_MOTION;
								//}

								nCurrentStep++;
							}

							break;

		case	402		:
							// Z�� �극��Ŀ ����
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z1);
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z2);
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z3);
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z4);
							//LTimerProceed.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));

							nCurrentStep = 410;
							break;

		// ���� ���� ���� ���� ����
		case	410		:
							if (LTimerProceed.Verify()) {

								SetDOStatus(DO_OFF, DO_SSR_SERVO_POWER_ON);
								LTimerProceed.Start(3000);
								
								nCurrentStep++;
							}

							break;

		// ��� ��Ʈ�ѷ� �������� �ʱ�ȭ
		case	411		:
							if (LTimerProceed.Verify()) {

								// ��� ��Ʈ�ѷ� �������� �ʱ�ȭ
								Motion_Initialize();
								LTimerProceed.Start(100);
								
								nCurrentStep++;
							}

							break;

		// ���� ���� ���� ���� ����
		case	412		:
							if (LTimerProceed.Verify()) {

								SetDOStatus(DO_ON, DO_SSR_SERVO_POWER_ON);
								LTimerProceed.Start(m_SystemConfig.GetDelayProcess(DLY_PROC_SERVO_POWER_ON_1));
							
								nCurrentStep++;
							}

							break;

		case	413		:
							if (LTimerProceed.Verify()) {
							
								nCurrentStep++;
							}

							break;

		// ���� ���� ALARM RESET ON
		case	414		:
							if (LTimerProceed.Verify()) {

								for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++)
									AxmSignalServoAlarmReset(nAxisNo, ENABLE);

								LTimerProceed.Start(500);
								nCurrentStep++;
							}

							break;

		// ���� ���� ALARM RESET OFF
		case	415		:
							if (LTimerProceed.Verify()) {

								for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++)
									AxmSignalServoAlarmReset(nAxisNo, DISABLE);

								LTimerProceed.Start(500);
								nCurrentStep = 420;
							}

							break;

		// ���� ���� ON
		case	420		:
							if (LTimerProceed.Verify()) {

								for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++) {

									AxmSignalServoOn(nAxisNo, ENABLE);
								}

								LTimerProceed.Start(500);
								nCurrentStep++;
							}

							break;

		case	421		:
							if (LTimerProceed.Verify()) {

								nCurrentStep++;
							}

							break;

		case	422		:
							if (LTimerProceed.Verify()) {

								// Z�� �극��Ŀ ����
								//SetDOStatus(DO_ON, DO_RLY_SERVO_BREAK_OFF_Z1);
								//SetDOStatus(DO_ON, DO_RLY_SERVO_BREAK_OFF_Z2);
								//SetDOStatus(DO_ON, DO_RLY_SERVO_BREAK_OFF_Z3);
								//SetDOStatus(DO_ON, DO_RLY_SERVO_BREAK_OFF_Z4);
								//LTimerProceed[nCHANNEL_NO].Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));

								nCurrentStep++;
							}

							break;

		case	423		:
							if (LTimerProceed.Verify())
								nCurrentStep = 490;

							break;

		// �Ϸ�
		case	490		:
							// ���� ���� �˶� ���� üũ ����
							m_stSystemStatus.bOnMotion_CheckServoMotorAlarm = TRUE;

							nCurrentStep = STEP_INIT_STN_LOCK;
							break;


		/////////////////////////////////////////////////////////////
		// �۾��� ���ͷ� ////////////////////////////////////////////
		case	STEP_INIT_STN_LOCK	:	
										nCurrentStep = 510;
										break;

		// ���ͷ� üũ
		case	510		:
							nCurrentStep = 590;
							break;

		case	590		:
							nCurrentStep = STEP_INIT_HOME_SEARCH;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� ////////////////////////////////////////////////
		case	STEP_INIT_HOME_SEARCH	:
											nCurrentStep = 610;
											break;

		case	610		:
							// ���� ���� ��� �÷��� �ʱ�ȭ
							for (UINT nIndex = 0; nIndex < MAX_MOTION_AXIS; nIndex++) {

								m_stSystemStatus.bOnMotion_HomeSearchStart[nIndex]			= FALSE;
								m_stSystemStatus.bOnMotion_ResultHomeSearch[nIndex]			= FALSE;
								m_stSystemStatus.bOnMotion_HomeSearchOptionPLStop[nIndex]	= FALSE;
								m_stSystemStatus.bOnMotion_HomeSearchOptionNLStop[nIndex]	= FALSE;
							}

							// �÷��� �ʱ�ȭ
							bIsStepMoveHome = FALSE;

							nCurrentStep = 620;
							break;

		// VZ ���� ���� ����
		case	620		:
							m_stSystemStatus.bOnMotion_HomeSearchStart[MOTION_RVZ]	= TRUE;

							nCurrentStep++;
							break;

		case	621		:
							if (!m_stSystemStatus.bOnMotion_HomeSearchStart[MOTION_RVZ]) {
							
								// ���� ���� ����
								if (!m_stSystemStatus.bOnMotion_ResultHomeSearch[MOTION_RVZ]) {
								
									nCurrentStep = STEP_INIT_ERROR_MOTION;
									break;
								}

								nCurrentStep = 630;
							}

							break;

		// VY ���� ���� ����
		case	630		:
							m_stSystemStatus.bOnMotion_HomeSearchStart[MOTION_RVY]	= TRUE;

							nCurrentStep++;
							break;

		case	631		:
							if (!m_stSystemStatus.bOnMotion_HomeSearchStart[MOTION_RVY]) {
							
								// ���� ���� ����
								if (!m_stSystemStatus.bOnMotion_ResultHomeSearch[MOTION_RVY]) {
								
									nCurrentStep = STEP_INIT_ERROR_MOTION;
									break;
								}

								nCurrentStep++;
							}

							break;

		case	632		:
							// VY ��� ��ġ �̵�
							Motion_MoveTo(MOTION_RVY, 
										  m_stMotionAxisInfo[MOTION_RVY].dblCustomPosition[MAI_CPOS_HOME], 
										  m_stMotionAxisInfo[MOTION_RVY].dblSpeedBase);

							nCurrentStep++;
							break;

		case	633		:
							if (Motion_Done(MOTION_RVY))
								nCurrentStep = 640;

							break;

		// VX ���� ���� ����
		case	640		:
							m_stSystemStatus.bOnMotion_HomeSearchStart[MOTION_RVX]	= TRUE;

							nCurrentStep++;
							break;

		case	641		:
							if (!m_stSystemStatus.bOnMotion_HomeSearchStart[MOTION_RVX]) {
							
								// ���� ���� ����
								if (!m_stSystemStatus.bOnMotion_ResultHomeSearch[MOTION_RVX]) {
								
									nCurrentStep = STEP_INIT_ERROR_MOTION;
									break;
								}

								nCurrentStep = 680;
							}

							break;

		// �⺻ ��� ��ġ�� �̵�
		case	680		:
							nCurrentStep++;
							break;

		case	681		:
							nCurrentStep = 690;
							break;

		// �Ϸ�
		case	690		:
							TestMessage(TRUE, _T("%s"), g_stSystemString[SYSSTR_MC_INIT_MOTION_COMPLETE].szDescription[m_nTypeLanguage]);

							nCurrentStep = STEP_INIT_STN_UNLOCK;
							break;


		/////////////////////////////////////////////////////////////
		// �۾��� ���ͷ� ���� ///////////////////////////////////////
		case	STEP_INIT_STN_UNLOCK	:		
											nCurrentStep = 790;
											break;

		case	790		:
							nCurrentStep = STEP_INIT_SUCCESS;
							break;


		/////////////////////////////////////////////////////////////
		// �ʱ�ȭ ���� //////////////////////////////////////////////
		case	STEP_INIT_ERROR	:
									// ������ 2ȸ ���
									m_stSystemStatus.nBeepCount = 2;

									nCurrentStep = 1010;
									break;

		case	1010	:
							TestMessage(TRUE, _T("%s"), g_stSystemString[SYSSTR_MC_INIT_FAILURE].szDescription[m_nTypeLanguage]);

							nCurrentStep = STEP_INIT_DONE;
							break;

		// ����̽� ����
		case	STEP_INIT_ERROR_DEV_BATT	:
		case	STEP_INIT_ERROR_DEV_DMM		:
												TestMessage(TRUE, _T("%s"), g_stSystemString[SYSSTR_MC_INIT_MEAS_DEVICE_FAILURE].szDescription[m_nTypeLanguage]);

												nCurrentStep = STEP_INIT_ERROR;
												break;

		// �����̼� ����
		case	STEP_INIT_ERROR_STATION	:
											TestMessage(TRUE, _T("%s"), g_stSystemString[SYSSTR_MC_INIT_STATION_FAILURE].szDescription[m_nTypeLanguage]);

											nCurrentStep = STEP_INIT_ERROR;
											break;

		// ���ͷ� ����
		case	STEP_INIT_ERROR_INTERLK	:
											TestMessage(TRUE, _T("%s"),	g_stSystemString[SYSSTR_MC_INIT_INTLK_FAILURE].szDescription[m_nTypeLanguage]);

											nCurrentStep = STEP_INIT_ERROR;
											break;

		// ���� ����
		case	STEP_INIT_ERROR_PARTS	:
											TestMessage(TRUE, _T("%s"),	g_stSystemString[SYSSTR_MC_INIT_SEQUENCE_FAILURE].szDescription[m_nTypeLanguage]);

											// ���� �ڵ� ����
											stErrorCode.nErrorCode	= ERROR_MACHINE_SEQUENCE;
											stErrorCode.nProcessID	= PROCESS_INIT;
											bOnError				= TRUE;

											nCurrentStep = STEP_INIT_ERROR;
											break;

		// ��� ����
		case	STEP_INIT_ERROR_MOTION	:
											TestMessage(TRUE, _T("%s"),	g_stSystemString[SYSSTR_MC_INIT_MOTION_FAILURE].szDescription[m_nTypeLanguage]);

											// ���� ���� ����
											for (UINT nAxisNo = MOTION_AXIS_1; nAxisNo < MAX_MOTION_AXIS; nAxisNo++) {

												Motion_Stop_E(nAxisNo);
												Motion_Stop_E(nAxisNo);
												AxmSignalServoOn(nAxisNo, DISABLE);
											}

											// Z�� �극��Ŀ ����
											//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z1);
											//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z2);
											//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z3);
											//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z4);

											nCurrentStep = STEP_INIT_ERROR;
											break;
	

		/////////////////////////////////////////////////////////////
		// �ʱ�ȭ ���� //////////////////////////////////////////////
		case	STEP_INIT_SUCCESS	:
										// ������ 1ȸ ���
										m_stSystemStatus.nBeepCount = 1;

										nCurrentStep = 2010;
										break;

		case	2010	:
							// ��� �ʱ�ȭ ��� ����
							m_stSystemStatus.bResultMachineInitialize = TRUE;

							TestMessage(TRUE, _T("%s"), g_stSystemString[SYSSTR_MC_INIT_COMPLETE].szDescription[m_nTypeLanguage]);

							nCurrentStep = STEP_INIT_DONE;
							break;


		/////////////////////////////////////////////////////////////
		// �ʱ�ȭ �Ϸ� //////////////////////////////////////////////
		case	STEP_INIT_DONE	:
									m_stSystemStatus.bOnMachineInitialize = FALSE;

									// ����� �޼��� �ʱ�ȭ
									ClearUserMessage();

									// �Ϸ� �޼��� ����
									m_pMainWnd->PostMessage(UM_MAIN_MACHINE_INITIALIZE, FALSE);

									nCurrentStep = 0;
									break;


		/////////////////////////////////////////////////////////////
		// ��� ���� ���� ///////////////////////////////////////////
		case	STEP_EMG	:
								// �÷��� �ʱ�ȭ
								m_stSystemStatus.bOnMachineInitialize		= FALSE;
								m_stSystemStatus.bResultMachineInitialize	= FALSE;
								ZeroMemory(m_stSystemStatus.bOnMotion_HomeSearchStart, sizeof(BOOL) * MOTION_AXIS_1);

								if (!m_stSystemStatus.bOnEmergencyStop) {

									bOnPause	 = FALSE;
									nCurrentStep = STEP_INIT_DONE;
								}

								break;
	}


	/////////////////////////////////////////////////////////////////
	// ������Ʈ UI //////////////////////////////////////////////////
	if (bOnUpdateUI) {

		PUI_PARAM_UPDATE_T		pstParamUI	= new UI_PARAM_UPDATE_T;
		if (pstParamUI) {

			*pstParamUI = stParamUI;

			if (m_pMainWnd && m_pMainWnd->GetSafeHwnd())
				m_pMainWnd->PostMessage(UM_MAIN_UPDATE_UI, (WPARAM)pstParamUI);
		}
	}


	/////////////////////////////////////////////////////////////////
	// ���� �߻� ////////////////////////////////////////////////////
	if (bOnError) {

		pstErrorCode = new ERROR_CODE_T;
		if (pstErrorCode)	*pstErrorCode = stErrorCode;
	}


	/////////////////////////////////////////////////////////////////
	// ���� ����͸� ////////////////////////////////////////////////
	if (LTimerSystemMonitor.Verify()) {

		if (nPreviousStep != nCurrentStep) {

			nPreviousStep = nCurrentStep;
			if (m_pSysMonitorDlg && m_pSysMonitorDlg->GetSafeHwnd()) {

				m_pSysMonitorDlg->PostMessage(UM_SYSM_UPDATE_STEP, PSTEP_PROC_MACHINE_INIT, nCurrentStep);
				LTimerSystemMonitor.Start(DLY_REFRESH_SYSTEM_MONITOR);
			}
		}
	}


	return	pstErrorCode;
}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� : ���� �۾� (���ν���) ///////////////////////////////////////////
PERROR_CODE_T CMainApp::ProcessMainWorkProcedure(void)
{
	static	PROCESS_CTRL_T		PROCESS;

	static	UINT				nSTATION_NO					= STATION_1;
	static	UINT				nSTATION_SUB_NO				= STN1_SUB_NONE;

			PBOOL				pOnSCP_MoveParts			= m_stSystemStatus.bOnSCP_MoveParts[nSTATION_NO];
	static	UINT				nSCP_PARTS_ID				= 0;
	
	static	BOOL				bResultProcess				= FALSE;
	static	BOOL				bOnVisionTrigged			= FALSE;
	static	BOOL				bUseLoadCell				= FALSE;
	static	CString				strMessageBox				= _T("");
	static	CString				strParameters				= _T("");
	static	CString				strDataValue				= _T("");
	static	CString				strVisionImageName			= _T("");
	static	CString				strVisionResultName			= _T("");

	static	UINT				nCurrentLoadCellNo			= 0;
	static	UINT				nCurrentMessageNo			= 0;
	static	UINT				nIndexTestDataCAN			= 0;
	static	PCAN_PACKET_T		stSendPacket;
	static	PCAN_PACKET_T		stReadPacket;

	static	DOUBLE				dblSetupValue				= 0;
	static	DOUBLE				dblSetupValueVoltage		= 0;
	static	DOUBLE				dblSetupValueCurrent		= 0;
	static	UINT				nSetupValue					= 0;
	static	UINT				nSetupOption_1				= 0;
	static	UINT				nSetupOption_2				= 0;
	static	BOOL				bSetupState					= FALSE;
	
	static	FUNC_TEST_DATA_T	stFunctionTestData;
	static	ODAPWR_DATA_T		stODAPowerData;
	static	PTPRD_DATA_T		pstWorkProcedureData		= NULL;

	static	LTimerMsec			LTimerProceed;
	static	LTimerMsec			LTimerSteady;
	static	LTimerMsec			LTimerSteadyDMM;
	static	LTimerMsec			LTimerSteadyPS;
	static	LTimerMsec			LTimerTimeOut;
	static	LTimerMsec			LTimerTimeOutProcess;
	static	LTimerMsec			LTimerInterval;
	static	LTimerMsec			LTimerSignal;
	static	LTimerMsec			LTimerSensor;
	static	LTimerMsec			LTimerMeasurement;
	static	LTimerMsec			LTimerSystemMonitor;
	static	LTimerMsec			LTimerSystemDisplay;
	static	LTimeHighResCounter	LCounterMeasurement;


	/////////////////////////////////////////////////////////////////
	// ���μ��� ������ �ʱ�ȭ ///////////////////////////////////////
	ProcessDataInitialize(PROCESS);


	/////////////////////////////////////////////////////////////////
	// �ڵ� ���� ����/���� �ʱ�ȭ ///////////////////////////////////
	if (CheckProcessOperating(PROCESS)) {
	
		m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]				= FALSE;
		m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
		m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
		m_stSystemStatus.bOnMainProcessOption01[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;
		m_stSystemStatus.bOnMainProcessOption02[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;
		m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
		m_stSystemStatus.bIsMainProcessInitialized[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;

		Motion_Stop_S(MOTION_RVX);
		Motion_Stop_S(MOTION_RVY);
		Motion_Stop_S(MOTION_RVZ);
	}


	/////////////////////////////////////////////////////////////////
	// ��� �ʱ�ȭ //////////////////////////////////////////////////
	if (CheckProcessMachineInitialize(PROCESS))
		return	NULL;


	/////////////////////////////////////////////////////////////////
	// ���� ���� ��� ///////////////////////////////////////////////
	PROCESS.bOnManualControlMode = m_stSystemStatus.bIsManualControl[nSTATION_NO];


	/////////////////////////////////////////////////////////////////
	// ���/�Ͻ� ���� ���� //////////////////////////////////////////
	if (CheckProcessEmergencyStop(PROCESS))					return	NULL;
	if (CheckProcessOperatingPause(nSTATION_NO, PROCESS))	return	NULL;


	/////////////////////////////////////////////////////////////////
	// ���� ���μ��� ////////////////////////////////////////////////
	switch (PROCESS.nCurrentStep) {

		case	0		:
							PROCESS.nCurrentStep = 10;
							break;

		// �ý��� üũ
		case	10		:
							if (IsSystemReady()) {
							
								PROCESS.nCurrentStep = 20;
							}
								
							break;

		// ���μ��� �ʱ�ȭ
		case	20		:
							m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]				= FALSE;
							m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
							m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
							m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
							m_stSystemStatus.bIsMainProcessInitialized[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;

							PROCESS.nCurrentStep = 90;
							break;

		// �Ϸ�
		case	90		:
							PROCESS.nCurrentStep = STEP_WORK_STANDBY;
							break;


		/////////////////////////////////////////////////////////////
		// �ʱ�ȭ ///////////////////////////////////////////////////
		case	STEP_WORK_INIT	:
									PROCESS.nCurrentStep = 110;
									break;

		// �÷��� �ʱ�ȭ
		case	110		:
							PROCESS.nCurrentStep = 130;
							break;

		// ���� ��ȣ �ʱ�ȭ
		case	130		:
							// ���� ������ �ʱ�ȭ
							SetDOStatus(DO_OFF, DO_RLY_S01_PRODUCT_POWER_ON);
							SetDOStatus(DO_OFF, DO_RLY_S01_BYPASS_ON);
							SetDOStatus(DO_OFF, DO_RLY_S01_CONN_P);
							SetDOStatus(DO_OFF, DO_RLY_S01_CONN_N);
							SetDOStatus(DO_OFF, DO_RLY_S01_RANGE_mA);
							SetDOStatus(DO_OFF, DO_RLY_S01_RANGE_A);
							SetDOStatus(DO_OFF, DO_RLY_S01_MEAS_CURRENT);
							SetDOStatus(DO_OFF, DO_RLY_S01_CONN_BATT);
							SetDOStatus(DO_OFF, DO_RLY_S01_CONN_IGN);
							SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_CHECK);
							SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_LOCK_ON);
							SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_LOCK_OFF);

							PROCESS.nCurrentStep = 140;
							break;

		// ���� ���� ����
		case	140		:
							// ���� ���� ����
							bSetupState				= FALSE;
							PROCESS.nCurrentStep	= STEP_WORK_SUB_SET_PS;
							PROCESS.nReturn03Step	= 150;
							break;

		// CAN ��� �ʱ�ȭ
		case	150		:
							// ��� ���� �ʱ�ȭ
							CAN_InitInformation();

							// �ñ׳� ������ �ʱ�ȭ
							CAN_ClearSignalValue();
							
							PROCESS.nCurrentStep = 190;
							break;

		// �Ϸ�
		case	190		:
							// �ʱ�ȭ �Ϸ� �÷��� ����
							m_stSystemStatus.bIsMainProcessInitialized[nSTATION_NO][nSTATION_SUB_NO] = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn01Step;
							break;


		/////////////////////////////////////////////////////////////
		// ��� /////////////////////////////////////////////////////
		case	STEP_WORK_STANDBY	:
										PROCESS.nCurrentStep = 220;
										break;

		// ���μ��� ���
		case	220		:
							if (m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]) {

								m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;
								m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;

								PROCESS.nCurrentStep = 230;
								break;
							}

							PROCESS.nCurrentStep = STEP_WORK_STANDBY;
							break;
							
		// �� �������� �ε�
		case	230		:
							PROCESS.pstModelProfile	= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
							PROCESS.pstWorkStatus	= GetWorkStatus(nSTATION_NO);

							if (PROCESS.pstModelProfile != NULL) {

								PROCESS.pstModelProfileConfig	= &((PROCESS.pstModelProfile)->stModelProfileConfig);
								PROCESS.pstWorkInfo				= &((PROCESS.pstModelProfileConfig)->stWorkInfo);
								PROCESS.pstStationSetupInfo		= &(PROCESS.pstModelProfileConfig)->stSpBasicSetupInfo;
								PROCESS.pstMiscellaneousInfo	= &(PROCESS.pstModelProfileConfig)->stSpMiscellaneousInfo;
								PROCESS.pstWorkPositionInfo		= (PROCESS.pstModelProfileConfig)->stSpBasicSetupInfo.stWorkPositionSheet;
								PROCESS.pstTestSetupInfo		= (PROCESS.pstModelProfileConfig)->stSpVisionSetupInfo.stTestItemSetupInfo;
								PROCESS.nNumWorkSheetItem		= (PROCESS.pstModelProfileConfig)->stSpVisionSetupInfo.nNumTestSheetItem;
								
								PROCESS.nCurrentStep = 280;
								break;
							}

							SErrorMessage(TRUE, _T("[S%02d/%s] �� ������ �ε��� �� �����ϴ�."),	nSTATION_NO, 
																									g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

							PROCESS.nCurrentStep = STEP_WORK_ERROR_SYSTEM;
							break;

		// �ʱ�ȭ
		case	280		:
							PROCESS.nCurrentStep	= STEP_WORK_INIT;
							PROCESS.nReturn01Step	= 290;
							break;

		// �Ϸ�
		case	290		:
							PROCESS.nCurrentStep = STEP_WORK_START;
							break;


		/////////////////////////////////////////////////////////////
		// �۾� /////////////////////////////////////////////////////
		case	STEP_WORK_START	:
									PROCESS.nCurrentStep = 410;
									break;

		// �غ�
		case	410		:
							// �۾� ���� �ʱ�ȭ
							bResultProcess				= TRUE;
							PROCESS.bOnInstantStop		= FALSE;
							PROCESS.nCurrentProcedureNo	= 0;
							PROCESS.nRetryCount			= 0;

							PROCESS.nCurrentStep = 420;
							break;

		// �۾� �Ϸ� üũ
		case	420		:
							{
								BOOL	bIsStopProcess	= FALSE;

								// �۾� ����
								if (m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO])
									bIsStopProcess = TRUE;

								// �˻� �Ϸ�
								if (PROCESS.nCurrentProcedureNo >= m_stTestProcedureHeader.nNumProcedureData)
									bIsStopProcess = TRUE;

								// ���հ� ���� �� �˻� ����
								if (PROCESS.bOnInstantStop || (PROCESS.pstModelProfileConfig)->bWorkOption[WOPT_NG_STOP]) {
							
									if (!bResultProcess)	bIsStopProcess = TRUE;
								}

								PROCESS.nCurrentStep = bIsStopProcess ? 490 : 450;
							}

							break;

		// 1 ���� �۾�
		case	450		:
							PROCESS.nCurrentStep	= STEP_WORK_CYCLE;
							PROCESS.nReturn01Step	= 451;
							break;

		case	451		:
							PROCESS.nCurrentProcedureNo++;

							PROCESS.nCurrentStep = 420;
							break;

		// �Ϸ�
		case	490		:
							// ���� ������ �ʱ�ȭ
							SetDOStatus(DO_OFF, DO_RLY_S01_PRODUCT_POWER_ON);
							SetDOStatus(DO_OFF, DO_RLY_S01_BYPASS_ON);
							SetDOStatus(DO_OFF, DO_RLY_S01_CONN_P);
							SetDOStatus(DO_OFF, DO_RLY_S01_CONN_N);
							SetDOStatus(DO_OFF, DO_RLY_S01_RANGE_mA);
							SetDOStatus(DO_OFF, DO_RLY_S01_RANGE_A);
							SetDOStatus(DO_OFF, DO_RLY_S01_MEAS_CURRENT);
							SetDOStatus(DO_OFF, DO_RLY_S01_CONN_BATT);
							SetDOStatus(DO_OFF, DO_RLY_S01_CONN_IGN);
							SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_CHECK);
							SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_LOCK_ON);
							SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_LOCK_OFF);

							// ���� ���� ����
							bSetupState				= FALSE;
							PROCESS.nCurrentStep	= STEP_WORK_SUB_SET_PS;
							PROCESS.nReturn03Step	= STEP_WORK_DONE;
							break;


		/////////////////////////////////////////////////////////////
		// �Ϸ� /////////////////////////////////////////////////////
		case	STEP_WORK_DONE	:
									PROCESS.nCurrentStep = 590;
									break;

		// �Ϸ�
		case	590		:
							// ���� ���μ��� �Ϸ�
							m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;
							m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]	= bResultProcess;

							PROCESS.nCurrentStep = STEP_WORK_STANDBY;
							break;

		
		/////////////////////////////////////////////////////////////
		// 1 ���� �۾� //////////////////////////////////////////////
		case	STEP_WORK_CYCLE	:
									PROCESS.nCurrentStep = 1010;
									break;

		case	1010	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							// 1 ���� �÷��� ����
							PROCESS.bOnProcessCycle = TRUE;

							// �÷��� �ʱ�ȭ
							PROCESS.nRetryCount			= 0;
							PROCESS.nResultInspection	= T_RESULT_SUCCESS;
							PROCESS.bOnUpdateWorkSheet	= FALSE;
														
							PROCESS.nCurrentStep = 1100;
							break;

		// ���ν��� Ŀ�ǵ�
		case	1100	:
							{
								pstWorkProcedureData = &m_pstTestProcedureData[PROCESS.nCurrentProcedureNo];
								strParameters.Empty();
								strDataValue.Empty();

								// ���� �˻� ������ �ʱ�ȭ
								ZeroMemory(&stFunctionTestData, sizeof(FUNC_TEST_DATA_T));
								_tcscpy_s(stFunctionTestData.szName, MAX_STRINPUT_S, pstWorkProcedureData->szName);
								stFunctionTestData.nCommand	= pstWorkProcedureData->nCommand;

								// Ŀ�ǵ� �б�
								switch (pstWorkProcedureData->nCommand) {
							
									case	TPRD_CMD_SETUP_ENV			:	PROCESS.nCurrentStep = STEP_WORK_SUB_CMD_SETUP_ENV;			break;
									case	TPRD_CMD_SETUP_COMM			:	PROCESS.nCurrentStep = STEP_WORK_SUB_CMD_SETUP_COMM;		break;

									case	TPRD_CMD_MEASUREMENT		:	PROCESS.nCurrentStep = STEP_WORK_SUB_CMD_MEAS;				break;
									case	TPRD_CMD_MEASUREMENT_START	:	PROCESS.nCurrentStep = STEP_WORK_SUB_CMD_MEAS_START;		break;
									case	TPRD_CMD_MEASUREMENT_RESULT	:	PROCESS.nCurrentStep = STEP_WORK_SUB_CMD_MEAS_RESULT;		break;

									case	TPRD_CMD_ACTION_MOVE		:	PROCESS.nCurrentStep = STEP_WORK_SUB_CMD_ACTION_MOVE;		break;
									case	TPRD_CMD_ACTION_OPEN		:	PROCESS.nCurrentStep = STEP_WORK_SUB_CMD_ACTION_OPEN;		break;
									case	TPRD_CMD_ACTION_CLOSE		:	PROCESS.nCurrentStep = STEP_WORK_SUB_CMD_ACTION_CLOSE;		break;

									case	TPRD_CMD_TEST_PUSH_UP		:	PROCESS.nCurrentStep = STEP_WORK_SUB_CMD_TEST_PUSH_UP;		break;
									case	TPRD_CMD_TEST_PUSH_1_DN		:	PROCESS.nCurrentStep = STEP_WORK_SUB_CMD_TEST_PUSH_1_DN;	break;
									case	TPRD_CMD_TEST_PUSH_2_DN		:	PROCESS.nCurrentStep = STEP_WORK_SUB_CMD_TEST_PUSH_2_DN;	break;
									case	TPRD_CMD_TEST_PUSH_LOCK		:	PROCESS.nCurrentStep = STEP_WORK_SUB_CMD_TEST_PUSH_LOCK;	break;
									case	TPRD_CMD_TEST_COMM			:	PROCESS.nCurrentStep = STEP_WORK_SUB_CMD_TEST_COMM;			break;
									case	TPRD_CMD_TEST_VISION_1		:	PROCESS.nCurrentStep = STEP_WORK_SUB_CMD_TEST_VISION_1;		break;
									case	TPRD_CMD_TEST_VISION_2		:	PROCESS.nCurrentStep = STEP_WORK_SUB_CMD_TEST_VISION_2;		break;

									case	TPRD_CMD_DELAY				:	PROCESS.nCurrentStep = STEP_WORK_SUB_CMD_DELAY;				break;

									default								:	PROCESS.nCurrentStep = 1900;								break;
								}

								PROCESS.nReturn02Step	= 1900;
							}

							break;

		// �Ϸ�
		case	1900	:
							// 1 ���� �÷��� ����
							PROCESS.bOnProcessCycle = FALSE;

							// ���μ��� ��� ����
							bResultProcess &= PROCESS.nResultInspection == T_RESULT_SUCCESS ? TRUE : FALSE;

							// ���� �˻� ������ ����
							_tcscpy_s(stFunctionTestData.szParameters, MAX_STRVALUE, strParameters);
							m_arrFuncTestData.Add(stFunctionTestData);

							// ������Ʈ UI
							if (PROCESS.bOnUpdateWorkSheet) {

								PROCESS.bOnUpdateWorkSheet		= FALSE;
								PROCESS.bOnUpdateUI				= TRUE;
								PROCESS.bIsUpdateSendMessage	= TRUE;
								PROCESS.stParamUI.nUpdateID		= UI_WORK_SHEET_01;
								PROCESS.stParamUI.nStationNo	= nSTATION_NO;
								PROCESS.stParamUI.stWorkSheet.nIndexFuncTestData	= m_arrFuncTestData.GetCount() - 1;
							}

							PROCESS.nCurrentStep = PROCESS.nReturn01Step;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� : Ŀ�ǵ� - ȯ�� ���� ///////////////////////////
		case	STEP_WORK_SUB_CMD_SETUP_ENV	:
												MessageWindow(cDEBUG, _T("PROC::CMD_SETUP_ENV"));

												PROCESS.nCurrentStep = 2010;
												break;

		// �ʱ�ȭ
		case	2010	:
							PROCESS.nCurrentStep = 2050;
							break;

		// ���� ����/���� ����
		case	2050	:
							if (pstWorkProcedureData->bEnableValue[TPRD_DATA_VALUE_SET_ENV_SUPPLY_VOLTAGE] ||
								pstWorkProcedureData->bEnableValue[TPRD_DATA_VALUE_SET_ENV_SUPPLY_CURRENT]) {
								
								dblSetupValueVoltage	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_SET_ENV_SUPPLY_VOLTAGE];
								dblSetupValueCurrent	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_SET_ENV_SUPPLY_CURRENT];
								bSetupState				= TRUE;
								PROCESS.nCurrentStep	= STEP_WORK_SUB_SET_PS;
								PROCESS.nReturn03Step	= 2060;

								// �Ķ���� ����
								strParameters.AppendFormat(_T("PS=%.2f/%.2f "), dblSetupValueVoltage, dblSetupValueCurrent);
								break;
							}

							PROCESS.nCurrentStep = 2060;
							break;

		// ������ ��� ����
		case	2060	:
							if (pstWorkProcedureData->bEnableValue[TPRD_DATA_VALUE_SET_ENV_DEV_MODE]) {

								if (LTimerSteadyDMM.Verify()) {

									// ���� ����
									if (!m_devDMM.SetSystemCommand(AGDMM_SYS_CLS)) {

										ErrorMessage(TRUE, _T("������ ��Ƽ���Ͱ� �������� �ʽ��ϴ�."));
										PROCESS.nCurrentStep = STEP_WORK_ERROR_DEVICE;
										break;
									}

									LTimerSteadyDMM.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_DMM_CONTROL));

									PROCESS.nCurrentStep++;
								}

								break;
							}

							PROCESS.nCurrentStep = 2100;
							break;

		case	2061	:
							if (LTimerSteadyDMM.Verify()) {

								UINT	nMode	= pstWorkProcedureData->nValue[TPRD_DATA_VALUE_SET_ENV_DEV_MODE];

								switch (nMode) {
								
									case	1	:	nMode = FLKDMM_MODE_DCI;	break;
									case	2	:	nMode = FLKDMM_MODE_RES;	break;
									default		:	nMode = FLKDMM_MODE_DCV;	break;
								}

								// ���� ��� ����
								if (!m_devDMM.SetMeasurementMode(nMode)) {

									ErrorMessage(TRUE, _T("������ ��Ƽ���Ͱ� �������� �ʽ��ϴ�."));
									PROCESS.nCurrentStep = STEP_WORK_ERROR_DEVICE;
									break;
								}

								LTimerSteadyDMM.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_DMM_CONTROL));

								PROCESS.nCurrentStep = 2100;
							}

							break;

		// ���� ��� üũ
		case	2100	:
							if (pstWorkProcedureData->bEnableValue[TPRD_DATA_VALUE_SET_ENV_CONN_MODE]) {

								UINT	nMode	= (UINT)pstWorkProcedureData->nValue[TPRD_DATA_VALUE_SET_ENV_CONN_MODE];

								switch (nMode) {
								
									case	CONN_MODE_RES			:	PROCESS.nNextStep = 2110;	break;
									case	CONN_MODE_VOLT_P		:	PROCESS.nNextStep = 2120;	break;
									case	CONN_MODE_VOLT_D		:	PROCESS.nNextStep = 2130;	break;
									case	CONN_MODE_CURR_mA		:	PROCESS.nNextStep = 2140;	break;
									case	CONN_MODE_CURR_A		:	PROCESS.nNextStep = 2150;	break;
									case	CONN_MODE_DOOR_LOCK		:	PROCESS.nNextStep = 2160;	break;
									case	CONN_MODE_DOOR_UNLOCK	:	PROCESS.nNextStep = 2170;	break;
									default							:	PROCESS.nNextStep = 2180;	break;
								}

								// �Ķ���� ����
								strParameters.AppendFormat(_T("Mode=%s "), g_szConnectionModeShort[nMode]);

								PROCESS.nCurrentStep = PROCESS.nNextStep;
								break;
							}

							PROCESS.nCurrentStep = 2180;
							break;

		// ���� ��� ���� : ���� ����
		case	2110	:
							// ���� ������ �ʱ�ȭ
							SetDOStatus(DO_OFF, DO_RLY_S01_PRODUCT_POWER_ON);
							SetDOStatus(DO_OFF, DO_RLY_S01_BYPASS_ON);
							SetDOStatus(DO_OFF, DO_RLY_S01_CONN_P);
							SetDOStatus(DO_OFF, DO_RLY_S01_CONN_N);
							SetDOStatus(DO_OFF, DO_RLY_S01_RANGE_mA);
							SetDOStatus(DO_OFF, DO_RLY_S01_RANGE_A);
							SetDOStatus(DO_OFF, DO_RLY_S01_MEAS_CURRENT);
							SetDOStatus(DO_OFF, DO_RLY_S01_CONN_BATT);
							SetDOStatus(DO_OFF, DO_RLY_S01_CONN_IGN);
							SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_CHECK);
							SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_LOCK_ON);
							SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_LOCK_OFF);
							LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));

							PROCESS.nCurrentStep++;
							break;

		case	2111	:
							if (LTimerSteady.Verify()) {
							
								// ���� ��� ����
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_P);
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_N);
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_BATT);
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_IGN);

								PROCESS.nCurrentStep = 2190;
							}

							break;

		// ���� ��� ���� : ���� ���� (�⺻)
		case	2120	:
							// ������ �����н� ����
							if (!GetDOStatus(DO_RLY_S01_BYPASS_ON)) {

								SetDOStatus(DO_ON, DO_RLY_S01_BYPASS_ON);
								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));
							}

							PROCESS.nCurrentStep++;
							break;

		case	2121	:
							if (LTimerSteady.Verify()) {
							
								// ���� ���� ��� ����
								if (GetDOStatus(DO_RLY_S01_MEAS_CURRENT) || GetDOStatus(DO_RLY_S01_RANGE_mA) || GetDOStatus(DO_RLY_S01_RANGE_A)) {
					
									SetDOStatus(DO_OFF, DO_RLY_S01_MEAS_CURRENT);
									SetDOStatus(DO_OFF, DO_RLY_S01_RANGE_mA);
									SetDOStatus(DO_OFF, DO_RLY_S01_RANGE_A);
									LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));
								}

								PROCESS.nCurrentStep++;
							}
							
							break;

		case	2122	:
							if (LTimerSteady.Verify()) {
							
								// ���� ���� ����
								if (GetDOStatus(DO_RLY_S01_DOOR_CHECK)) {
					
									SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_CHECK);
									LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));
								}

								PROCESS.nCurrentStep++;
							}
							
							break;

		case	2123	:
							if (LTimerSteady.Verify()) {
							
								// ���� ���� ��� ����
								SetDOStatus(DO_ON, DO_RLY_S01_PRODUCT_POWER_ON);
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_P);
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_N);
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_BATT);
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_IGN);

								PROCESS.nCurrentStep = 2190;
							}
							
							break;

		// ���� ��� ���� : ���� ���� (����)
		case	2130	:
							// ������ �����н� ����
							if (!GetDOStatus(DO_RLY_S01_BYPASS_ON)) {

								SetDOStatus(DO_ON, DO_RLY_S01_BYPASS_ON);
								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));
							}

							PROCESS.nCurrentStep++;
							break;

		case	2131	:
							if (LTimerSteady.Verify()) {
							
								// ���� ���� ��� ����
								if (GetDOStatus(DO_RLY_S01_MEAS_CURRENT) || GetDOStatus(DO_RLY_S01_RANGE_mA) || GetDOStatus(DO_RLY_S01_RANGE_A)) {
					
									SetDOStatus(DO_OFF, DO_RLY_S01_MEAS_CURRENT);
									SetDOStatus(DO_OFF, DO_RLY_S01_RANGE_mA);
									SetDOStatus(DO_OFF, DO_RLY_S01_RANGE_A);
									LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));
								}

								PROCESS.nCurrentStep++;
							}
							
							break;

		case	2132	:
							if (LTimerSteady.Verify()) {
							
								// ��ǰ ���� ����
								if (GetDOStatus(DO_RLY_S01_CONN_P)) {
					
									SetDOStatus(DO_OFF, DO_RLY_S01_CONN_P);
									LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));
								}

								PROCESS.nCurrentStep++;
							}
							
							break;

		case	2133	:
							if (LTimerSteady.Verify()) {
							
								// ���� ���� ��� ����
								SetDOStatus(DO_ON, DO_RLY_S01_PRODUCT_POWER_ON);
								SetDOStatus(DO_ON, DO_RLY_S01_DOOR_CHECK);
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_N);
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_BATT);
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_IGN);

								PROCESS.nCurrentStep = 2190;
							}
							
							break;

		// ���� ��� ���� : ���� ���� (mA)
		case	2140	:
							// ���� ���� ���� ���� ����
							if (GetDOStatus(DO_RLY_S01_CONN_P) || GetDOStatus(DO_RLY_S01_CONN_N) || GetDOStatus(DO_RLY_S01_DOOR_CHECK)) {
					
								SetDOStatus(DO_OFF, DO_RLY_S01_CONN_P);
								SetDOStatus(DO_OFF, DO_RLY_S01_CONN_N);
								SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_CHECK);
								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));
							}

							PROCESS.nCurrentStep++;
							break;

		case	2141	:
							if (LTimerSteady.Verify()) {

								// ������ �����н� ����
								if (!theApp.GetDOStatus(DO_RLY_S01_BYPASS_ON)) {

									theApp.SetDOStatus(DO_ON, DO_RLY_S01_BYPASS_ON);
									LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));
								}

								PROCESS.nCurrentStep++;
							}
							
							break;	

		case	2142	:
							if (LTimerSteady.Verify()) {
							
								// ���� ���� ��� �ʱ�ȭ
								if (GetDOStatus(DO_RLY_S01_CONN_IGN) || GetDOStatus(DO_RLY_S01_RANGE_A)) {

									SetDOStatus(DO_OFF, DO_RLY_S01_CONN_IGN);
									SetDOStatus(DO_OFF, DO_RLY_S01_RANGE_A);
									LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));
								}

								PROCESS.nCurrentStep++;
							}
							
							break;

		case	2143	:
							if (LTimerSteady.Verify()) {
							
								// ���� ���� ��� ����
								SetDOStatus(DO_ON, DO_RLY_S01_PRODUCT_POWER_ON);
								SetDOStatus(DO_ON, DO_RLY_S01_MEAS_CURRENT);
								SetDOStatus(DO_ON, DO_RLY_S01_RANGE_mA);
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_BATT);
								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));

								PROCESS.nCurrentStep++;
							}
							
							break;

		case	2144	:
							if (LTimerSteady.Verify()) {
							
								// ������ �����н� ���� ����
								if (GetDOStatus(DO_RLY_S01_BYPASS_ON)) {

									SetDOStatus(DO_OFF, DO_RLY_S01_BYPASS_ON);
								}

								PROCESS.nCurrentStep = 2190;
							}
							
							break;

		// ���� ��� ���� : ���� ���� (A)
		case	2150	:
							// ���� ���� ���� ���� ����
							if (GetDOStatus(DO_RLY_S01_CONN_P) || GetDOStatus(DO_RLY_S01_CONN_N) || GetDOStatus(DO_RLY_S01_DOOR_CHECK)) {
					
								SetDOStatus(DO_OFF, DO_RLY_S01_CONN_P);
								SetDOStatus(DO_OFF, DO_RLY_S01_CONN_N);
								SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_CHECK);
								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));
							}

							PROCESS.nCurrentStep++;
							break;

		case	2151	:
							if (LTimerSteady.Verify()) {

								// ������ �����н� ����
								if (!theApp.GetDOStatus(DO_RLY_S01_BYPASS_ON)) {

									theApp.SetDOStatus(DO_ON, DO_RLY_S01_BYPASS_ON);
									LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));
								}

								PROCESS.nCurrentStep++;
							}
							
							break;	

		case	2152	:
							if (LTimerSteady.Verify()) {
							
								// ���� ���� ��� �ʱ�ȭ
								if (GetDOStatus(DO_RLY_S01_RANGE_mA)) {

									SetDOStatus(DO_OFF, DO_RLY_S01_RANGE_mA);
									LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));
								}

								PROCESS.nCurrentStep++;
							}
							
							break;

		case	2153	:
							if (LTimerSteady.Verify()) {
							
								// ���� ���� ��� ����
								SetDOStatus(DO_ON, DO_RLY_S01_PRODUCT_POWER_ON);
								SetDOStatus(DO_ON, DO_RLY_S01_MEAS_CURRENT);
								SetDOStatus(DO_ON, DO_RLY_S01_RANGE_A);
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_BATT);
								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));

								PROCESS.nCurrentStep++;
							}
							
							break;

		case	2154	:
							if (LTimerSteady.Verify()) {
							
								// ������ �����н� ���� ����
								if (GetDOStatus(DO_RLY_S01_BYPASS_ON)) {

									SetDOStatus(DO_OFF, DO_RLY_S01_BYPASS_ON);
								}

								PROCESS.nCurrentStep = 2190;
							}
							
							break;

		// ���� ��� ���� : ���� ���
		case	2160	:
							if (GetDOStatus(DO_RLY_S01_DOOR_LOCK_ON) || GetDOStatus(DO_RLY_S01_DOOR_LOCK_OFF)) {

								SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_LOCK_ON);
								SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_LOCK_OFF);
								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));
							}

							PROCESS.nCurrentStep++;
							break;

		case	2161	:
							if (LTimerSteady.Verify()) {
							
								// mA ������ �ƴ� ��쿡�� ����
								if (!GetDOStatus(DO_RLY_S01_RANGE_mA)) {

									SetDOStatus(DO_ON, DO_RLY_S01_DOOR_LOCK_ON);
									LTimerProceed.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_ACTION_DOOR_LOCK_ACTIVE));
								}

								PROCESS.nCurrentStep++;
							}

							break;

		case	2162	:
							if (LTimerProceed.Verify()) {
							
								SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_LOCK_ON);

								PROCESS.nCurrentStep = 2190;
							}

							break;

		// ���� ��� ���� : ���� ��� ����
		case	2170	:	
							if (GetDOStatus(DO_RLY_S01_DOOR_LOCK_ON) || GetDOStatus(DO_RLY_S01_DOOR_LOCK_OFF)) {

								SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_LOCK_ON);
								SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_LOCK_OFF);
								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));
							}

							PROCESS.nCurrentStep++;
							break;

		case	2171	:
							if (LTimerSteady.Verify()) {
							
								// mA ������ �ƴ� ��쿡�� ����
								if (!GetDOStatus(DO_RLY_S01_RANGE_mA)) {

									SetDOStatus(DO_ON, DO_RLY_S01_DOOR_LOCK_OFF);
									LTimerProceed.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_ACTION_DOOR_LOCK_ACTIVE));
								}

								PROCESS.nCurrentStep++;
							}

							break;

		case	2172	:
							if (LTimerProceed.Verify()) {
							
								SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_LOCK_OFF);

								PROCESS.nCurrentStep = 2190;
							}

							break;

		// ���� ������ ����
		case	2180	:
							{
								BOOL	bEnable		= FALSE;
								UINT	nDATA_ID	= 0;


								// ���͸� ��ȣ
								nDATA_ID = TPRD_DATA_VALUE_SET_ENV_CONN_BATTERY;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
									SetDOStatus(bEnable ? DO_ON : DO_OFF, DO_RLY_S01_CONN_BATT);

									// �Ķ���� ����
									strParameters.AppendFormat(_T("BATT=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
								}

								// IGN ��ȣ
								nDATA_ID = TPRD_DATA_VALUE_SET_ENV_CONN_IGN;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									if (!GetDOStatus(DO_RLY_S01_RANGE_mA)) {

										bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
										SetDOStatus(bEnable ? DO_ON : DO_OFF, DO_RLY_S01_CONN_IGN);

										// �Ķ���� ����
										strParameters.AppendFormat(_T("IGN=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
									
									} else {
									
										// �Ķ���� ����
										strParameters.AppendFormat(_T("IGN=ERR "));
									}
								}

								PROCESS.nCurrentStep = 2190;
							}

							break;

		// �Ϸ�
		case	2190	:
							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� : Ŀ�ǵ� - ��� ���� ///////////////////////////
		case	STEP_WORK_SUB_CMD_SETUP_COMM	:
													MessageWindow(cDEBUG, _T("PROC::CMD_SETUP_COMM"));

													PROCESS.nCurrentStep = 2210;
													break;

		// �ʱ�ȭ
		case	2210	:
							PROCESS.nCurrentStep = 2250;
							break;

		// �޼��� ���� Ȱ��ȭ
		case	2250	:
							{
								BOOL	bEnable		= FALSE;
								UINT	nDATA_ID	= 0;


								// BMS22
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_ENABLE_SEND_MSG_T01;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
									m_stSystemStatus.bCAN_EnableTransmitData[CID_BMS22] = bEnable;

									// �Ķ���� ����
									strParameters.AppendFormat(_T("BMS22=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
								}

								// BMS4
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_ENABLE_SEND_MSG_T02;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
									m_stSystemStatus.bCAN_EnableTransmitData[CID_BMS4] = bEnable;

									// �Ķ���� ����
									strParameters.AppendFormat(_T("BMS4=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
								}

								// OBC1
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_ENABLE_SEND_MSG_T03;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
									m_stSystemStatus.bCAN_EnableTransmitData[CID_OBC1] = bEnable;

									// �Ķ���� ����
									strParameters.AppendFormat(_T("OBC1=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
								}

								// TMU1
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_ENABLE_SEND_MSG_T04;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
									m_stSystemStatus.bCAN_EnableTransmitData[CID_TMU1] = bEnable;

									// �Ķ���� ����
									strParameters.AppendFormat(_T("TMU1=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
								}

								// VCU1
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_ENABLE_SEND_MSG_T05;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
									m_stSystemStatus.bCAN_EnableTransmitData[CID_VCU1] = bEnable;

									// �Ķ���� ����
									strParameters.AppendFormat(_T("VCU1=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
								}

								// VCU19
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_ENABLE_SEND_MSG_T06;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
									m_stSystemStatus.bCAN_EnableTransmitData[CID_VCU19] = bEnable;

									// �Ķ���� ����
									strParameters.AppendFormat(_T("VCU19=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
								}

								// CGW1
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_ENABLE_SEND_MSG_T07;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
									m_stSystemStatus.bCAN_EnableTransmitData[CID_CGW1] = bEnable;

									// �Ķ���� ����
									strParameters.AppendFormat(_T("CGW1=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
								}

								// IGPM_EV1
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_ENABLE_SEND_MSG_T08;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
									m_stSystemStatus.bCAN_EnableTransmitData[CID_IGPM_EV1] = bEnable;

									// �Ķ���� ����
									strParameters.AppendFormat(_T("IGPM_EV1=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
								}

								// MCU3
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_ENABLE_SEND_MSG_T09;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
									m_stSystemStatus.bCAN_EnableTransmitData[CID_MCU3] = bEnable;

									// �Ķ���� ����
									strParameters.AppendFormat(_T("MCU3=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
								}

								// WHL_SPD11
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_ENABLE_SEND_MSG_T10;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
									m_stSystemStatus.bCAN_EnableTransmitData[CID_WHL_SPD11] = bEnable;

									// �Ķ���� ����
									strParameters.AppendFormat(_T("WHL_SPD11=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
								}

								PROCESS.nCurrentStep = 2260;
							}

							break;

		// �ñ׳� ���� ����
		case	2260	:
							{
								BOOL	bEnable		= FALSE;
								UINT	nDATA_ID	= 0;
								UINT	nSIG_ID		= 0;


								// CF_Bms_ChgSts
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T01_S01;
								nSIG_ID	 = CF_Bms_ChgSts;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// �Ķ���� ����
									strParameters.AppendFormat(_T("Bms_ChgSts=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// CR_BMS_DisplaySOC
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T01_S02;
								nSIG_ID	 = CR_BMS_DisplaySOC;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// �Ķ���� ����
									strParameters.AppendFormat(_T("BMS_DisplaySOC=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// CF_Bms_ChgLamp
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T02_S01;
								nSIG_ID	 = CF_Bms_ChgLamp;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// �Ķ���� ����
									strParameters.AppendFormat(_T("Bms_ChgLamp=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// CF_OBC_IG3_DRV_STATE
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T03_S01;
								nSIG_ID	 = CF_OBC_IG3_DRV_STATE;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// �Ķ���� ����
									strParameters.AppendFormat(_T("OBC_IG3_DRV_STATE=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// CF_Tmu_IG3Rly
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T04_S01;
								nSIG_ID	 = CF_Tmu_IG3Rly;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// �Ķ���� ����
									strParameters.AppendFormat(_T("Tmu_IG3Rly=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// CF_Vcu_EvRdy
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T05_S01;
								nSIG_ID	 = CF_Vcu_EvRdy;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// �Ķ���� ����
									strParameters.AppendFormat(_T("Vcu_EvRdy=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// CF_VCU_IG3DrvSts
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T06_S01;
								nSIG_ID	 = CF_VCU_IG3DrvSts;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// �Ķ���� ����
									strParameters.AppendFormat(_T("VCU_IG3DrvSts=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// CF_Gway_Ign1
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T07_S01;
								nSIG_ID	 = CF_Gway_Ign1;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// �Ķ���� ����
									strParameters.AppendFormat(_T("Gway_Ign1=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// C_Ign3Rly
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T08_S01;
								nSIG_ID	 = C_Ign3Rly;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// �Ķ���� ����
									strParameters.AppendFormat(_T("Ign3Rly=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// CR_Mcu_VehSpd_Kph
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T09_S01;
								nSIG_ID	 = CR_Mcu_VehSpd_Kph;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// �Ķ���� ����
									strParameters.AppendFormat(_T("Mcu_VehSpd_Kph=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// CR_Mcu_VehSpdDec_Kph
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T09_S02;
								nSIG_ID	 = CR_Mcu_VehSpdDec_Kph;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// �Ķ���� ����
									strParameters.AppendFormat(_T("Mcu_VehSpdDec_Kph=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// WHL_SPD_RL
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T10_S01;
								nSIG_ID	 = WHL_SPD_RL;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// �Ķ���� ����
									strParameters.AppendFormat(_T("WHL_SPD_RL=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// WHL_SPD_RR
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T10_S02;
								nSIG_ID	 = WHL_SPD_RR;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// �Ķ���� ����
									strParameters.AppendFormat(_T("WHL_SPD_RR=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// �ñ׳� ������ ������Ʈ
								CAN_UpdateSignalValue();

								PROCESS.nCurrentStep = 2390;
							}

							break;

		// �Ϸ�
		case	2390	:
							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� : Ŀ�ǵ� - ���� ���� ///////////////////////////
		case	STEP_WORK_SUB_CMD_MEAS	:
											MessageWindow(cDEBUG, _T("PROC::CMD_MEASUREMENT"));

											PROCESS.nCurrentStep = 2410;
											break;

		// �ʱ�ȭ
		case	2410	:
							// �÷��� �ʱ�ȭ
							PROCESS.bResultMainProcess = FALSE;

							// ���� ���ν��� ��ȣ ����
							m_stSystemStatus.nCurrentWorkProcedureNo = PROCESS.nCurrentProcedureNo;

							// �˻� ��Ʈ �ʱ�ȭ
							ZeroMemory((PROCESS.pstWorkStatus)->stMeasSheet, sizeof(MEAS_SHEET_T) * MAX_TEST_SHEET);

							PROCESS.nCurrentStep = 2420;
							break;

		// �Ķ���� ����
		case	2420	:
							{
								strParameters.AppendFormat(_T("Jdg=%lf "),		pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_JUDGE]);
								strParameters.AppendFormat(_T("NG_Stop=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_USE_NG_STOP]);
								strParameters.AppendFormat(_T("Abs=%d "),		pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_USE_ABS]);
								strParameters.AppendFormat(_T("Avg=%d "),		pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_USE_AVG]);
								strParameters.AppendFormat(_T("D_Rng=%lf "),	pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_DEV_RANGE]);

								PROCESS.nCurrentStep = 2500;
							}

							break;

		// �˻� ����
		case	2500	:
							m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][STN1_SUB_TEST] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	2501	:
							if (!m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][STN1_SUB_TEST]) {
							
								PROCESS.bResultMainProcess = m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][STN1_SUB_TEST];

								PROCESS.nCurrentStep = 2510;
							}

							break;

		// ��� ����
		case	2510	:
							{
								BOOL	bUseStopNG	= (BOOL)pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_USE_NG_STOP];
								DOUBLE	dblGain		= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_GAIN];
								DOUBLE	dblOffset	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_OFFSET];
								DOUBLE	dblSpecMIN	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_SPEC_L];
								DOUBLE	dblSpecMAX	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_SPEC_H];


								// �˻� ������ ����
								stFunctionTestData.nResult = (PROCESS.pstWorkStatus)->stMeasSheet[0].nResult;
								_stprintf_s(stFunctionTestData.szValue, MAX_STRINPUT_S, _T("%.4f"), (PROCESS.pstWorkStatus)->stMeasSheet[0].dblMeasurementValue);
								_stprintf_s(stFunctionTestData.szSpecMIN, MAX_STRINPUT, _T("%.4f"), (PROCESS.pstWorkStatus)->stMeasSheet[0].dblSpecMIN);
								_stprintf_s(stFunctionTestData.szSpecMAX, MAX_STRINPUT, _T("%.4f"), (PROCESS.pstWorkStatus)->stMeasSheet[0].dblSpecMAX);
								_tcscpy_s(stFunctionTestData.szUnit, MAX_STRINPUT, (PROCESS.pstWorkStatus)->stMeasSheet[0].szUnit);

								// �˻� ��� ����
								PROCESS.nResultInspection = (PROCESS.pstWorkStatus)->stMeasSheet[0].nResult;

								// ���հ� ���� �� ��� ���� �ɼ�
								if (PROCESS.nResultInspection != T_RESULT_SUCCESS && bUseStopNG)
									PROCESS.bOnInstantStop = TRUE;

								PROCESS.nCurrentStep = 2580;
							}

							break;

		// ���հ� ���� �� ��˻�
		case	2580	:
							if (m_SystemConfig.UseSystemOption(SOPT_RETRY_WORK_NG)) {

								if (PROCESS.nResultInspection != T_RESULT_SUCCESS) {

									// ��õ� ī��Ʈ üũ
									if (++PROCESS.nRetryCount <= m_SystemConfig.GetWorkRetryCount()) {

										// �÷��� �ʱ�ȭ
										PROCESS.nResultInspection	= T_RESULT_SUCCESS;
										PROCESS.bOnInstantStop		= FALSE;
										PROCESS.bResultMainProcess	= FALSE;

										// �˻� ��Ʈ �ʱ�ȭ
										ZeroMemory((PROCESS.pstWorkStatus)->stMeasSheet, sizeof(MEAS_SHEET_T) * MAX_TEST_SHEET);

										PROCESS.nCurrentStep = 2500;
										break;
									}
								}
							}

							PROCESS.nCurrentStep = 2590;
							break;

		// �Ϸ�
		case	2590	:
							// �۾� ��Ʈ ������Ʈ ����
							PROCESS.bOnUpdateWorkSheet = !pstWorkProcedureData->bOptions[TPRD_DATA_OPT_MEAS_UNUSE_UPDATE];
							if (PROCESS.nResultInspection != T_RESULT_SUCCESS)
								PROCESS.bOnUpdateWorkSheet = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� : Ŀ�ǵ� - ���� ���� ///////////////////////////
		case	STEP_WORK_SUB_CMD_MEAS_START	:
													MessageWindow(cDEBUG, _T("PROC::CMD_MEASUREMENT_START"));

													PROCESS.nCurrentStep = 2610;
													break;

		// �ʱ�ȭ
		case	2610	:
							// �÷��� �ʱ�ȭ
							PROCESS.bResultMainProcess = FALSE;

							// ���� ���ν��� ��ȣ ����
							m_stSystemStatus.nCurrentWorkProcedureNo = PROCESS.nCurrentProcedureNo;

							PROCESS.nCurrentStep = 2620;
							break;

		// �Ķ���� ����
		case	2620	:
							{
								strParameters.AppendFormat(_T("Jdg_min=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_START_JUDGE_STOP_MIN]);
								strParameters.AppendFormat(_T("Jdg_max=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_START_JUDGE_STOP_MAX]);
								strParameters.AppendFormat(_T("Jdg=%lf "),		pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_JUDGE]);
								strParameters.AppendFormat(_T("D_Rng=%lf "),	pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_DEV_RANGE]);

								PROCESS.nCurrentStep = 2700;
							}

							break;

		// �˻� ����
		case	2700	:
							m_stSystemStatus.bOnMainProcess[nSTATION_NO][STN1_SUB_TEST] = TRUE;

							PROCESS.nCurrentStep = 2790;
							break;

		// �Ϸ�
		case	2790	:
							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� : Ŀ�ǵ� - ���� ��� ///////////////////////////
		case	STEP_WORK_SUB_CMD_MEAS_RESULT	:
													MessageWindow(cDEBUG, _T("PROC::CMD_MEASUREMENT_RESULT"));

													PROCESS.nCurrentStep = 2810;
													break;

		// �ʱ�ȭ
		case	2810	:
							// �÷��� �ʱ�ȭ
							PROCESS.bResultMainProcess			= FALSE;
							PROCESS.dblValueRaw					= 0;
							PROCESS.dblValueMeasurement			= 0;
							PROCESS.dblValueMeasurementSUM		= 0;
							PROCESS.nIndexAverageMeasurement	= 0;

							// �˻� ��Ʈ �ʱ�ȭ
							ZeroMemory((PROCESS.pstWorkStatus)->stMeasSheet, sizeof(MEAS_SHEET_T) * MAX_TEST_SHEET);

							PROCESS.nCurrentStep = 2820;
							break;

		// �Ķ���� ����
		case	2820	:
							{
								switch (pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_RESULT_MODE]) {
					
									case	0	:	strParameters.AppendFormat(_T("Mode=AVG "));	break;
									case	1	:	strParameters.AppendFormat(_T("Mode=T1 "));		break;
									case	2	:	strParameters.AppendFormat(_T("Mode=T2 "));		break;
									case	3	:	strParameters.AppendFormat(_T("Mode=DEV "));	break;
									case	4	:	strParameters.AppendFormat(_T("Mode=MIN "));	break;
									case	5	:	strParameters.AppendFormat(_T("Mode=MAX "));	break;
									default		:	strParameters.AppendFormat(_T("Mode=ERR "));	break;
											}

								strParameters.AppendFormat(_T("Jdg=%lf "),		pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_RESULT_JUDGE]);
								strParameters.AppendFormat(_T("NG_Stop=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_RESULT_USE_NG_STOP]);
								strParameters.AppendFormat(_T("Abs=%d "),		pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_RESULT_USE_ABS]);

								PROCESS.nCurrentStep = 2900;
							}

							break;

		// �˻� �Ϸ� üũ
		case	2900	:
							if (!m_stSystemStatus.bOnMainProcess[nSTATION_NO][STN1_SUB_TEST]) {
							
								PROCESS.bResultMainProcess = m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][STN1_SUB_TEST];

								PROCESS.nCurrentStep = 2910;
							}

							break;

		// ������ �м� (���)
		case	2910	:
							if (pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_RESULT_MODE] == 0) {
							
								UINT				nMeasCount	= (UINT)m_arrContiMeasData.GetCount();
								CONTI_MEAS_DATA_T	stMeasData;


								for (UINT nIndex = 0; nIndex < nMeasCount; nIndex++) {
								
									stMeasData = m_arrContiMeasData.GetAt(nIndex);
									PROCESS.dblValueMeasurementSUM += stMeasData.dblValue;
								}

								PROCESS.dblValueRaw = PROCESS.dblValueMeasurementSUM / (DOUBLE)nMeasCount;

								PROCESS.nCurrentStep = 2980;
								break;
							}

							PROCESS.nCurrentStep = 2920;
							break;

		// ������ �м� (�ð�)
		case	2920	:
							if (pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_RESULT_MODE] == 1) {
								
								UINT				nMeasCount	= (UINT)m_arrContiMeasData.GetCount();
								CONTI_MEAS_DATA_T	stMeasData	= m_arrContiMeasData.GetAt(nMeasCount - 1);


								PROCESS.dblValueRaw	= (DOUBLE)stMeasData.nTimeStamp;
							
								PROCESS.nCurrentStep = 2980;
								break;
							}

							PROCESS.nCurrentStep++;
							break;

		case	2921	:
							if (pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_RESULT_MODE] == 2) {
							
								PROCESS.nCurrentStep = 2980;
								break;
							}

							PROCESS.nCurrentStep = 2930;
							break;

		// ������ �м� (����)
		case	2930	:
							if (pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_RESULT_MODE] == 3) {
							
								UINT				nMeasCount	= (UINT)m_arrContiMeasData.GetCount();
								DOUBLE				dblValueMIN	= 0;
								DOUBLE				dblValueMAX	= 0;
								CONTI_MEAS_DATA_T	stMeasData;


								stMeasData	= m_arrContiMeasData.GetAt(0);
								dblValueMIN	= stMeasData.dblValue;
								dblValueMAX	= stMeasData.dblValue;

								for (UINT nIndex = 1; nIndex < nMeasCount; nIndex++) {

									stMeasData = m_arrContiMeasData.GetAt(nIndex);

									if (dblValueMIN > stMeasData.dblValue)	dblValueMIN = stMeasData.dblValue;
									if (dblValueMAX < stMeasData.dblValue)	dblValueMAX = stMeasData.dblValue;
								}

								PROCESS.dblValueRaw = dblValueMAX - dblValueMIN;

								PROCESS.nCurrentStep = 2980;
								break;
							}

							PROCESS.nCurrentStep = 2940;
							break;

		// ������ �м� (�ּҰ�/�ִ밪)
		case	2940	:
							if (pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_RESULT_MODE] == 4 ||
								pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_RESULT_MODE] == 5) {
							
								CONTI_MEAS_DATA_T	stMeasData;
								UINT				nMeasCount	= (UINT)m_arrContiMeasData.GetCount();
								DOUBLE				dblValueMIN	= 0;
								DOUBLE				dblValueMAX	= 0;


								stMeasData	= m_arrContiMeasData.GetAt(0);
								dblValueMIN	= stMeasData.dblValue;
								dblValueMAX	= stMeasData.dblValue;

								for (UINT nIndex = 1; nIndex < nMeasCount; nIndex++) {

									stMeasData = m_arrContiMeasData.GetAt(nIndex);

									if (dblValueMIN > stMeasData.dblValue)	dblValueMIN = stMeasData.dblValue;
									if (dblValueMAX < stMeasData.dblValue)	dblValueMAX = stMeasData.dblValue;
								}

								if (pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_RESULT_MODE] == 4)	PROCESS.dblValueRaw = dblValueMIN;
								if (pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_RESULT_MODE] == 5)	PROCESS.dblValueRaw = dblValueMAX;

								PROCESS.nCurrentStep = 2980;
								break;
							}

							PROCESS.nCurrentStep = 2980;
							break;

		// ��� ����
		case	2980	:
							{
								BOOL	bUseStopNG	= (BOOL)pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_RESULT_USE_NG_STOP];
								DOUBLE	dblGain		= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_RESULT_GAIN];
								DOUBLE	dblOffset	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_RESULT_OFFSET];
								DOUBLE	dblSpecMIN	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_RESULT_SPEC_L];
								DOUBLE	dblSpecMAX	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_RESULT_SPEC_H];


								PROCESS.dblValueMeasurement	= (PROCESS.dblValueRaw * dblGain) + dblOffset;

								// �˻� ��� ����
								if (DPS_Round(PROCESS.dblValueMeasurement, 4) < DPS_Round(dblSpecMIN, 4) ||
									DPS_Round(PROCESS.dblValueMeasurement, 4) > DPS_Round(dblSpecMAX, 4))
										PROCESS.nResultInspection = T_RESULT_FAILURE;

								// �˻� ������ ����
								stFunctionTestData.nResult = PROCESS.nResultInspection;
								_stprintf_s(stFunctionTestData.szValue, MAX_STRINPUT_S, _T("%.4f (%d)"), PROCESS.dblValueMeasurement, m_arrContiMeasData.GetCount());
								_stprintf_s(stFunctionTestData.szSpecMIN, MAX_STRINPUT, _T("%.4f"), dblSpecMIN);
								_stprintf_s(stFunctionTestData.szSpecMAX, MAX_STRINPUT, _T("%.4f"), dblSpecMAX);
								_tcscpy_s(stFunctionTestData.szUnit, MAX_STRINPUT, pstWorkProcedureData->szValue[TPRD_DATA_VALUE_MEAS_RESULT_UNIT]);

								// ���հ� ���� �� ��� ���� �ɼ�
								if (PROCESS.nResultInspection != T_RESULT_SUCCESS && bUseStopNG)
									PROCESS.bOnInstantStop = TRUE;

								PROCESS.nCurrentStep = 2990;
							}

							break;

		// �Ϸ�
		case	2990	:
							// �۾� ��Ʈ ������Ʈ ����
							PROCESS.bOnUpdateWorkSheet = !pstWorkProcedureData->bOptions[TPRD_DATA_OPT_MEAS_RESULT_UNUSE_UPDATE];
							if (PROCESS.nResultInspection != T_RESULT_SUCCESS)
								PROCESS.bOnUpdateWorkSheet = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� : Ŀ�ǵ� - �Ϲ� ���� ///////////////////////////
		case	STEP_WORK_SUB_CMD_ACTION_MOVE	:
													MessageWindow(cDEBUG, _T("PROC::CMD_ACTION_MOVE"));

													PROCESS.nCurrentStep = 3010;
													break;

		// �ʱ�ȭ
		case	3010	:
							// �۾� ��Ʈ ��ġ ����
							PROCESS.nCurrentWorkSheetNo = pstWorkProcedureData->nValue[TPRD_DATA_VALUE_ACT_WPS_NO] - 1;
							if (PROCESS.nCurrentWorkSheetNo > MAX_S01_WORK_POSITION_SHEET)
								PROCESS.nCurrentWorkSheetNo = WPS_S01_STANDBY;

							if (PROCESS.nCurrentWorkSheetNo >= WPS_S01_OPEN_BEGIN && PROCESS.nCurrentWorkSheetNo <= WPS_S01_CLOSE_END)
								PROCESS.nCurrentWorkSheetNo = WPS_S01_STANDBY;

							PROCESS.nCurrentStep = 3020;
							break;

		// �Ķ���� ����
		case	3020	:
							{
								strParameters.AppendFormat(_T("WPS_no=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_ACT_WPS_NO]);
								strParameters.AppendFormat(_T("Push_up=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_ACT_PUSH_UP]);
								strParameters.AppendFormat(_T("Push_dn=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_ACT_PUSH_DN]);
								strParameters.AppendFormat(_T("Dr_open=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_ACT_DOOR_OPEN]);
								strParameters.AppendFormat(_T("Dr_close=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_ACT_DOOR_CLOSE]);

								if (m_nTypeMachine == MC_TYPE_1) {
								
									PROCESS.nCurrentStep = 3100;
									break;

								} else {
								
									if (pstWorkProcedureData->nValue[TPRD_DATA_VALUE_ACT_PUSH_UP])			PROCESS.nCurrentStep = 3050;
									else if (pstWorkProcedureData->nValue[TPRD_DATA_VALUE_ACT_PUSH_DN])		PROCESS.nCurrentStep = 3055;
									else if (pstWorkProcedureData->nValue[TPRD_DATA_VALUE_ACT_DOOR_OPEN])	PROCESS.nCurrentStep = 3060;
									else if (pstWorkProcedureData->nValue[TPRD_DATA_VALUE_ACT_DOOR_CLOSE])	PROCESS.nCurrentStep = 3065;
									else																	PROCESS.nCurrentStep = 3190;
								}
							}

							break;

		// ���� ���� ���� : UP
		case	3050	:
							pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_A_UP] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	3051	:
							if (!pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_A_UP])
								PROCESS.nCurrentStep = 3190;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// ���� ���� ���� : DN
		case	3055	:
							pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_1_DN] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	3056	:
							if (!pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_1_DN])
								PROCESS.nCurrentStep = 3190;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// ���� ���� ���� : UP
		case	3060	:
							pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_OPEN_UP] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	3061	:
							if (!pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_OPEN_UP])
								PROCESS.nCurrentStep = 3190;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// ���� ���� ���� : DN
		case	3065	:
							pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_OPEN_DN] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	3066	:
							if (!pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_OPEN_DN])
								PROCESS.nCurrentStep = 3190;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// VZ ��� ��ġ �̵�
		case	3100	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVZ)) {

								Motion_MoveTo(	MOTION_RVZ,
												m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME], 
												m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3101	:
							if (Motion_Done(MOTION_RVZ)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME];
								if (!Motion_CheckStopStatus(MOTION_RVZ, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVZ;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 3110;
							}

							break;

		// VX, VY ��ǥ ��ġ ���� �̵�
		case	3110	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVY)) {

								Motion_Move2X(	MCOORD_S01, MOTION_RVX, MOTION_RVY,
												PROCESS.pstWorkPositionInfo[PROCESS.nCurrentWorkSheetNo].dblPosition[MINDEX_VX],
												PROCESS.pstWorkPositionInfo[PROCESS.nCurrentWorkSheetNo].dblPosition[MINDEX_VY],
												m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3111	:
							if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVY)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = PROCESS.pstWorkPositionInfo[PROCESS.nCurrentWorkSheetNo].dblPosition[MINDEX_VX];
								if (!Motion_CheckStopStatus(MOTION_RVX, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVX;
								}

								dblPosition = PROCESS.pstWorkPositionInfo[PROCESS.nCurrentWorkSheetNo].dblPosition[MINDEX_VY];
								if (!Motion_CheckStopStatus(MOTION_RVY, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVY;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 3120;
							}

							break;

		// VZ ��ǥ ��ġ �̵�
		case	3120	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVZ)) {

								Motion_MoveTo(	MOTION_RVZ,
												PROCESS.pstWorkPositionInfo[PROCESS.nCurrentWorkSheetNo].dblPosition[MINDEX_VZ],
												m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3121	:
							if (Motion_Done(MOTION_RVZ)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = PROCESS.pstWorkPositionInfo[PROCESS.nCurrentWorkSheetNo].dblPosition[MINDEX_VZ];
								if (!Motion_CheckStopStatus(MOTION_RVZ, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVZ;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 3130;
							}

							break;

		// VZ ������ �̵�
		case	3130	:
							if (Motion_Done(MOTION_RVZ)) {

								DOUBLE	dblSpeed	= (PROCESS.pstWorkInfo)->dblWorkInfoValue[WI_ITEM_WORK_SPEED_OFFSET_VZ];

								if (dblSpeed <= 0)	dblSpeed = m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase;

								Motion_Move(MOTION_RVZ,
											PROCESS.pstWorkPositionInfo[PROCESS.nCurrentWorkSheetNo].dblOffset[MINDEX_VZ],
											dblSpeed);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3131	:
							if (Motion_Done(MOTION_RVZ)) {

								PROCESS.nCurrentStep = 3150;
							}

							break;

		// ���� �ð� ����
		case	3150	:
							LTimerProceed.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_ACT_DELAY]);

							PROCESS.nCurrentStep++;
							break;

		case	3151	:
							if (LTimerProceed.Verify())
								PROCESS.nCurrentStep = 3160;

							break;

		// VZ ��� ��ġ �̵�
		case	3160	:
							if (!pstWorkProcedureData->bOptions[TPRD_DATA_OPT_ACT_UNUSE_HOME]) {

								PROCESS.nCurrentStep++;
								break;
							}

							PROCESS.nCurrentStep = 3170;
							break;

		case	3161	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVZ)) {

								Motion_MoveTo(	MOTION_RVZ,
												m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME], 
												m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3162	:
							if (Motion_Done(MOTION_RVZ)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME];
								if (!Motion_CheckStopStatus(MOTION_RVZ, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVZ;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 3170;
							}

							break;

		// ...?
		case	3170	:
							PROCESS.nCurrentStep = 3190;
							break;

		// �Ϸ�
		case	3190	:
							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� : Ŀ�ǵ� - ���� ���� ///////////////////////////
		case	STEP_WORK_SUB_CMD_ACTION_OPEN	:
													MessageWindow(cDEBUG, _T("PROC::CMD_ACTION_OPEN"));

													PROCESS.nCurrentStep = 3210;
													break;

		// �ʱ�ȭ
		case	3210	:
							PROCESS.nCurrentStep = 3220;
							break;

		// �Ķ���� ����
		case	3220	:
							{
								PROCESS.nCurrentStep = 3240;
							}

							break;

		// ���� ���� üũ
		case	3240	:
							if (/*GetDIStatus(DI_SENS_S01_DETECT_PRODUCT_DOOR) && */GetDIStatus(DI_SENS_S01_PRODUCT_DOOR_OPEN_UP)) {
							
								PROCESS.nCurrentStep = 3250;
								break;
							}

							// ��� ����
							PROCESS.nResultInspection = T_RESULT_ERROR;

							// ���� ���� ���� : DN
							pOnSCP_MoveParts[SCP_S01_PRODUCT_DOOR_OPEN_DN] = TRUE;

							PROCESS.nCurrentStep = 3370;
							break;

		// VZ ��� ��ġ �̵�
		case	3250	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVZ)) {

								Motion_MoveTo(	MOTION_RVZ,
												m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME], 
												m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3251	:
							if (Motion_Done(MOTION_RVZ)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME];
								if (!Motion_CheckStopStatus(MOTION_RVZ, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVZ;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 3260;
							}

							break;

		// VY ��� ��ġ �̵�
		case	3260	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVY)) {

								Motion_MoveTo(	MOTION_RVY,
												m_stMotionAxisInfo[MOTION_RVY].dblCustomPosition[MAI_CPOS_HOME], 
												m_stMotionAxisInfo[MOTION_RVY].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3261	:
							if (Motion_Done(MOTION_RVY)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = m_stMotionAxisInfo[MOTION_RVY].dblCustomPosition[MAI_CPOS_HOME];
								if (!Motion_CheckStopStatus(MOTION_RVY, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVY;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 3270;
							}

							break;

		// VX, VZ ��ǥ ��ġ ���� �̵�
		case	3270	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVZ)) {

								Motion_Move2X(	MCOORD_S01, MOTION_RVZ, MOTION_RVX,
												PROCESS.pstWorkPositionInfo[WPS_S01_OPEN_BEGIN].dblPosition[MINDEX_VZ],
												PROCESS.pstWorkPositionInfo[WPS_S01_OPEN_BEGIN].dblPosition[MINDEX_VX],
												m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3271	:
							if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVZ)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = PROCESS.pstWorkPositionInfo[WPS_S01_OPEN_BEGIN].dblPosition[MINDEX_VX];
								if (!Motion_CheckStopStatus(MOTION_RVX, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVX;
								}

								dblPosition = PROCESS.pstWorkPositionInfo[WPS_S01_OPEN_BEGIN].dblPosition[MINDEX_VZ];
								if (!Motion_CheckStopStatus(MOTION_RVZ, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVZ;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 3280;
							}

							break;

		// VY ��ǥ ��ġ �̵�
		case	3280	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVY)) {

								Motion_MoveTo(	MOTION_RVY,
												PROCESS.pstWorkPositionInfo[WPS_S01_OPEN_BEGIN].dblPosition[MINDEX_VY], 
												m_stMotionAxisInfo[MOTION_RVY].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3281	:
							if (Motion_Done(MOTION_RVY)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = PROCESS.pstWorkPositionInfo[WPS_S01_OPEN_BEGIN].dblPosition[MINDEX_VY];
								if (!Motion_CheckStopStatus(MOTION_RVY, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVY;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 3300;
							}

							break;

		// ���� �ð� ����
		case	3300	:
							LTimerProceed.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_ACT_OPEN_DELAY]);

							PROCESS.nCurrentStep++;
							break;

		case	3301	:
							if (LTimerProceed.Verify())
								PROCESS.nCurrentStep = 3310;

							break;

		// ���� ���� ���� : DN
		case	3310	:
							pOnSCP_MoveParts[SCP_S01_PRODUCT_DOOR_OPEN_DN] = TRUE;

							PROCESS.nCurrentStep = 3320;
							break;

		// VX, VY, VZ ��ǥ ��ġ ���� �̵�
		case	3320	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVY) && Motion_Done(MOTION_RVZ)) {

								Motion_Move3X(	MCOORD_S01, MOTION_RVZ, MOTION_RVX, MOTION_RVY,
												PROCESS.pstWorkPositionInfo[WPS_S01_OPEN_END].dblPosition[MINDEX_VZ],
												PROCESS.pstWorkPositionInfo[WPS_S01_OPEN_END].dblPosition[MINDEX_VX],
												PROCESS.pstWorkPositionInfo[WPS_S01_OPEN_END].dblPosition[MINDEX_VY],
												m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3321	:
							if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVY) && Motion_Done(MOTION_RVZ)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = PROCESS.pstWorkPositionInfo[WPS_S01_OPEN_END].dblPosition[MINDEX_VX];
								if (!Motion_CheckStopStatus(MOTION_RVX, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVX;
								}

								dblPosition = PROCESS.pstWorkPositionInfo[WPS_S01_OPEN_END].dblPosition[MINDEX_VY];
								if (!Motion_CheckStopStatus(MOTION_RVY, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVY;
								}

								dblPosition = PROCESS.pstWorkPositionInfo[WPS_S01_OPEN_END].dblPosition[MINDEX_VZ];
								if (!Motion_CheckStopStatus(MOTION_RVZ, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVZ;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 3350;
							}

							break;

		// VY ��� ��ġ �̵�
		case	3350	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVY)) {

								Motion_MoveTo(	MOTION_RVY,
												m_stMotionAxisInfo[MOTION_RVY].dblCustomPosition[MAI_CPOS_HOME], 
												m_stMotionAxisInfo[MOTION_RVY].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3351	:
							if (Motion_Done(MOTION_RVY)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = m_stMotionAxisInfo[MOTION_RVY].dblCustomPosition[MAI_CPOS_HOME];
								if (!Motion_CheckStopStatus(MOTION_RVY, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVY;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 3360;
							}

							break;

		// ���� ���� üũ
		case	3360	:
							if (GetDIStatus(DI_SENS_S01_DETECT_PRODUCT_DOOR)) {

								LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_PRODUCT));

								PROCESS.nCurrentStep++;
								break;
							}

							LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_PRODUCT_NONE));

							PROCESS.nCurrentStep = 3362;
							break;

		case	3361	:
							if (GetDIStatus(DI_SENS_S01_DETECT_PRODUCT_DOOR)) {

								if (LTimerSensor.Verify()) {

									// ��� ����
									PROCESS.nResultInspection = T_RESULT_FAILURE;

									PROCESS.nCurrentStep = 3370;
								}

								break;
							}

							PROCESS.nCurrentStep--;
							break;

		case	3362	:
							if (!GetDIStatus(DI_SENS_S01_DETECT_PRODUCT_DOOR)) {

								if (LTimerSensor.Verify()) {

									PROCESS.nCurrentStep = 3370;
								}

								break;
							}

							PROCESS.nCurrentStep = 3360;
							break;

		// ���� ���� ���� Ȯ�� : DN
		case	3370	:
							if (!pOnSCP_MoveParts[SCP_S01_PRODUCT_DOOR_OPEN_DN])
								PROCESS.nCurrentStep = 3380;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// ��� ����
		case	3380	:
							{
								// �˻� ������ ����
								stFunctionTestData.nResult = PROCESS.nResultInspection;

								PROCESS.nCurrentStep = 3390;
							}

							break;

		// �Ϸ�
		case	3390	:
							// �۾� ��Ʈ ������Ʈ ����
							PROCESS.bOnUpdateWorkSheet = !pstWorkProcedureData->bOptions[TPRD_DATA_OPT_ACT_OPEN_UNUSE_UPDATE];
							if (PROCESS.nResultInspection != T_RESULT_SUCCESS)
								PROCESS.bOnUpdateWorkSheet = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� : Ŀ�ǵ� - �ݱ� ���� ///////////////////////////
		case	STEP_WORK_SUB_CMD_ACTION_CLOSE	:
													MessageWindow(cDEBUG, _T("PROC::CMD_ACTION_CLOSE"));

													PROCESS.nCurrentStep = 3410;
													break;

		// �ʱ�ȭ
		case	3410	:
							PROCESS.nCurrentStep = 3420;
							break;

		// �Ķ���� ����
		case	3420	:
							{
								PROCESS.nCurrentStep = 3440;
							}

							break;

		// ���� ���� üũ
		case	3440	:
							if (!GetDIStatus(DI_SENS_S01_DETECT_PRODUCT_DOOR)) {

								// ���� ���� ���� : UP
								pOnSCP_MoveParts[SCP_S01_PRODUCT_DOOR_OPEN_UP] = TRUE;
							
								PROCESS.nCurrentStep = 3460;
								break;
							}

							// ��� ����
							PROCESS.nResultInspection = T_RESULT_ERROR;

							PROCESS.nCurrentStep = 3580;
							break;

		// VZ ��� ��ġ �̵� (��ŵ��)
		case	3450	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVZ)) {

								Motion_MoveTo(	MOTION_RVZ,
												m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME], 
												m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3451	:
							if (Motion_Done(MOTION_RVZ)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME];
								if (!Motion_CheckStopStatus(MOTION_RVZ, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVZ;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 3460;
							}

							break;

		// VY ��� ��ġ �̵�
		case	3460	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVY)) {

								Motion_MoveTo(	MOTION_RVY,
												m_stMotionAxisInfo[MOTION_RVY].dblCustomPosition[MAI_CPOS_HOME], 
												m_stMotionAxisInfo[MOTION_RVY].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3461	:
							if (Motion_Done(MOTION_RVY)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = m_stMotionAxisInfo[MOTION_RVY].dblCustomPosition[MAI_CPOS_HOME];
								if (!Motion_CheckStopStatus(MOTION_RVY, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVY;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 3470;
							}

							break;

		// VX, VZ ��ǥ ��ġ ���� �̵�
		case	3470	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVZ)) {

								Motion_Move2X(	MCOORD_S01, MOTION_RVZ, MOTION_RVX,
												PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_BEGIN].dblPosition[MINDEX_VZ],
												PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_BEGIN].dblPosition[MINDEX_VX],
												m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3471	:
							if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVZ)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_BEGIN].dblPosition[MINDEX_VX];
								if (!Motion_CheckStopStatus(MOTION_RVX, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVX;
								}

								dblPosition = PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_BEGIN].dblPosition[MINDEX_VZ];
								if (!Motion_CheckStopStatus(MOTION_RVZ, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVZ;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 3480;
							}

							break;

		// VY ��ǥ ��ġ �̵�
		case	3480	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVY)) {

								Motion_MoveTo(	MOTION_RVY,
												PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_BEGIN].dblPosition[MINDEX_VY], 
												m_stMotionAxisInfo[MOTION_RVY].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3481	:
							if (Motion_Done(MOTION_RVY)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_BEGIN].dblPosition[MINDEX_VY];
								if (!Motion_CheckStopStatus(MOTION_RVY, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVY;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 3490;
							}

							break;

		// ���� ���� ���� Ȯ�� : UP
		case	3490	:
							if (!pOnSCP_MoveParts[SCP_S01_PRODUCT_DOOR_OPEN_UP])
								PROCESS.nCurrentStep = 3500;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// ���� �ð� ����
		case	3500	:
							LTimerProceed.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_ACT_CLOSE_DELAY]);

							PROCESS.nCurrentStep++;
							break;

		case	3501	:
							if (LTimerProceed.Verify())
								PROCESS.nCurrentStep = 3520;

							break;

		// VX, VY, VZ ��ǥ ��ġ ���� �̵�
		case	3520	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVY) && Motion_Done(MOTION_RVZ)) {

								Motion_Move3X(	MCOORD_S01, MOTION_RVZ, MOTION_RVX, MOTION_RVY,
												PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_END].dblPosition[MINDEX_VZ],
												PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_END].dblPosition[MINDEX_VX],
												PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_END].dblPosition[MINDEX_VY],
												m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3521	:
							if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVY) && Motion_Done(MOTION_RVZ)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_END].dblPosition[MINDEX_VX];
								if (!Motion_CheckStopStatus(MOTION_RVX, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVX;
								}

								dblPosition = PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_END].dblPosition[MINDEX_VY];
								if (!Motion_CheckStopStatus(MOTION_RVY, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVY;
								}

								dblPosition = PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_END].dblPosition[MINDEX_VZ];
								if (!Motion_CheckStopStatus(MOTION_RVZ, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVZ;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 3550;
							}

							break;

		// VY ��� ��ġ �̵�
		case	3550	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVY)) {

								Motion_MoveTo(	MOTION_RVY,
												m_stMotionAxisInfo[MOTION_RVY].dblCustomPosition[MAI_CPOS_HOME], 
												m_stMotionAxisInfo[MOTION_RVY].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3551	:
							if (Motion_Done(MOTION_RVY)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = m_stMotionAxisInfo[MOTION_RVY].dblCustomPosition[MAI_CPOS_HOME];
								if (!Motion_CheckStopStatus(MOTION_RVY, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVY;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 3560;
							}

							break;

		// ���� ���� ���� : DN
		case	3560	:
							pOnSCP_MoveParts[SCP_S01_PRODUCT_DOOR_OPEN_DN] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	3561	:
							if (!pOnSCP_MoveParts[SCP_S01_PRODUCT_DOOR_OPEN_DN])
								PROCESS.nCurrentStep = 3570;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// ���� ���� üũ
		case	3570	:
							if (GetDIStatus(DI_SENS_S01_DETECT_PRODUCT_DOOR)) {

								LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_PRODUCT));

								PROCESS.nCurrentStep++;
								break;
							}

							LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_PRODUCT_NONE));

							PROCESS.nCurrentStep = 3372;
							break;

		case	3571	:
							if (GetDIStatus(DI_SENS_S01_DETECT_PRODUCT_DOOR)) {

								if (LTimerSensor.Verify()) {

									PROCESS.nCurrentStep = 3580;
								}

								break;
							}

							PROCESS.nCurrentStep--;
							break;

		case	3572	:
							if (!GetDIStatus(DI_SENS_S01_DETECT_PRODUCT_DOOR)) {

								if (LTimerSensor.Verify()) {

									// ��� ����
									PROCESS.nResultInspection = T_RESULT_FAILURE;

									PROCESS.nCurrentStep = 3580;
								}

								break;
							}

							PROCESS.nCurrentStep = 3570;
							break;

		// ��� ����
		case	3580	:
							{
								// �˻� ������ ����
								stFunctionTestData.nResult = PROCESS.nResultInspection;

								PROCESS.nCurrentStep = 3590;
							}

							break;

		// �Ϸ�
		case	3590	:
							// �۾� ��Ʈ ������Ʈ ����
							PROCESS.bOnUpdateWorkSheet = !pstWorkProcedureData->bOptions[TPRD_DATA_OPT_ACT_CLOSE_UNUSE_UPDATE];
							if (PROCESS.nResultInspection != T_RESULT_SUCCESS)
								PROCESS.bOnUpdateWorkSheet = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� : Ŀ�ǵ� - ��� PUSH �˻� //////////////////////
		case	STEP_WORK_SUB_CMD_TEST_PUSH_UP	:
													MessageWindow(cDEBUG, _T("PROC::CMD_TEST_PUSH_UP"));

													PROCESS.nCurrentStep = 3610;
													break;

		// �ʱ�ȭ
		case	3610	:
							// �÷��� �ʱ�ȭ
							PROCESS.dblValueRaw			= 0;
							PROCESS.dblValueMeasurement	= 0;
							bUseLoadCell				= (BOOL)pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA1_USE_LC];

							// �ε弿 ä�� ����
							nCurrentLoadCellNo = pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA1_LCC_NO];
							if (nCurrentLoadCellNo >= MAX_LOADCELL_CHANNEL_USE)
								nCurrentLoadCellNo = LOADCELL_CH01;

							// �ε弿 ������ �ʱ�ȭ
							m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo]		= 0;
							m_stSystemStatus.dblPeakHoldDataLoadCell[nCurrentLoadCellNo]	= 0;

							PROCESS.nCurrentStep = 3620;
							break;

		// �Ķ���� ����
		case	3620	:
							{
								switch (pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA1_MODE]) {
					
									case	0	:	strParameters.AppendFormat(_T("Mode=NORMAL "));		break;
									case	1	:	strParameters.AppendFormat(_T("Mode=LOCK "));		break;
									default		:	strParameters.AppendFormat(_T("Mode=ERR "));		break;
								}

								strParameters.AppendFormat(_T("Jdg=%lf, "),		pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA1_JUDGE]);
								strParameters.AppendFormat(_T("LC_no=%d "),		pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA1_LCC_NO]);
								strParameters.AppendFormat(_T("LC_use=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA1_USE_LC]);

								PROCESS.nCurrentStep = 3630;
							}

							break;

		// ���� �ð�
		case	3630	:
							LTimerProceed.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA1_DELAY]);

							PROCESS.nCurrentStep++;
							break;

		case	3631	:
							if (LTimerProceed.Verify())
								PROCESS.nCurrentStep = 3700;

							break;

		// ���� ���� ���� : UP
		case	3700	:
							SetDOStatus(DO_ON, m_nTypeMachine == MC_TYPE_1 ? DO_SOL_S01_PRODUCT_DOOR_OPEN_UP : DO_SOL_S02_PRODUCT_DOOR_OPEN_UP);
							LTimerTimeOut.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA1_TIMEOUT]);

							if (pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA1_MODE] == 0) {
							
								PROCESS.nCurrentStep = 3710;
								break;
							}

							if (pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA1_MODE] == 1) {
							
								PROCESS.nCurrentStep = 3720;
								break;
							}

							// �˻� ��� ����
							PROCESS.nResultInspection = T_RESULT_ERROR;

							PROCESS.nCurrentStep = 3710;
							break;

		// ���� ���� üũ (�Ϲ� ���)
		case	3710	:
							if (GetDIStatus(m_nTypeMachine == MC_TYPE_1 ? DI_SENS_S01_PRODUCT_DOOR_OPEN_UP : DI_SENS_S02_PRODUCT_DOOR_OPEN_UP)) {
							
								PROCESS.nCurrentStep = 3780;
								break;
							}

							if (LTimerTimeOut.Verify() || 
								(bUseLoadCell && m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo] > pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA1_JUDGE])) {
							
								// �˻� ��� ����
								PROCESS.nResultInspection = T_RESULT_FAILURE;

								PROCESS.nCurrentStep = 3750;
							}
							
							break;

		// ���� ���� üũ (��� ���)
		case	3720	:
							if (GetDIStatus(m_nTypeMachine == MC_TYPE_1 ? DI_SENS_S01_PRODUCT_DOOR_OPEN_UP : DI_SENS_S02_PRODUCT_DOOR_OPEN_UP)) {

								// �˻� ��� ����
								PROCESS.nResultInspection = T_RESULT_FAILURE;
							
								PROCESS.nCurrentStep = 3750;
								break;
							}

							if (LTimerTimeOut.Verify() ||
								(bUseLoadCell && m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo] > pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA1_JUDGE])) {

								PROCESS.nCurrentStep = 3750;
							}
							
							break;

		// ���� ���� ���� : DN
		case	3750	:
							nSCP_PARTS_ID = m_nTypeMachine == MC_TYPE_1 ? SCP_S01_PRODUCT_DOOR_OPEN_DN : SCP_S02_PRODUCT_DOOR_OPEN_DN; 
							pOnSCP_MoveParts[nSCP_PARTS_ID] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	3751	:
							if (!pOnSCP_MoveParts[nSCP_PARTS_ID])
								PROCESS.nCurrentStep = 3780;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// ��� ����
		case	3780	:
							{
								DOUBLE	dblGain		= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA1_GAIN];
								DOUBLE	dblOffset	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA1_OFFSET];
								DOUBLE	dblSpecMIN	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA1_SPEC_L];
								DOUBLE	dblSpecMAX	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA1_SPEC_H];


								PROCESS.dblValueRaw			= m_stSystemStatus.dblPeakHoldDataLoadCell[nCurrentLoadCellNo];
								PROCESS.dblValueMeasurement	= (PROCESS.dblValueRaw * dblGain) + dblOffset;

								// �˻� ��� ����
								if (bUseLoadCell) {

									if (DPS_Round(PROCESS.dblValueMeasurement, 2) < DPS_Round(dblSpecMIN, 2) ||
										DPS_Round(PROCESS.dblValueMeasurement, 2) > DPS_Round(dblSpecMAX, 2))
											PROCESS.nResultInspection = T_RESULT_FAILURE;
								}

								// �˻� ������ ����
								stFunctionTestData.nResult = PROCESS.nResultInspection;
								if (bUseLoadCell) {

									_stprintf_s(stFunctionTestData.szValue, MAX_STRINPUT_S, _T("%.2f"), PROCESS.dblValueMeasurement);
									_stprintf_s(stFunctionTestData.szSpecMIN, MAX_STRINPUT, _T("%.2f"), dblSpecMIN);
									_stprintf_s(stFunctionTestData.szSpecMAX, MAX_STRINPUT, _T("%.2f"), dblSpecMAX);
									_tcscpy_s(stFunctionTestData.szUnit, MAX_STRINPUT, pstWorkProcedureData->szValue[TPRD_DATA_VALUE_TA1_UNIT]);
								}

								PROCESS.nCurrentStep = 3790;
							}

							break;

		// �Ϸ�
		case	3790	:
							// �۾� ��Ʈ ������Ʈ ����
							PROCESS.bOnUpdateWorkSheet = !pstWorkProcedureData->bOptions[TPRD_DATA_OPT_TA1_UNUSE_UPDATE];
							if (PROCESS.nResultInspection != T_RESULT_SUCCESS)
								PROCESS.bOnUpdateWorkSheet = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� : Ŀ�ǵ� - �ϰ� PUSH �˻� #1 ///////////////////
		case	STEP_WORK_SUB_CMD_TEST_PUSH_1_DN	:
													MessageWindow(cDEBUG, _T("PROC::CMD_TEST_PUSH_DN_01"));

													PROCESS.nCurrentStep = 3810;
													break;

		// �ʱ�ȭ
		case	3810	:
							// �÷��� �ʱ�ȭ
							PROCESS.dblValueRaw			= 0;
							PROCESS.dblValueMeasurement	= 0;
							nCurrentMessageNo			= TPRD_DATA_VALUE_TA2_CAN_MSG;
							nIndexTestDataCAN			= 0;

							// CAN ��� �ʱ�ȭ
							m_devCAN.ClearBuffer();

							// �ε弿 ä�� ����
							nCurrentLoadCellNo = pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA2_LCC_NO];
							if (nCurrentLoadCellNo >= MAX_LOADCELL_CHANNEL_USE)
								nCurrentLoadCellNo = LOADCELL_CH01;

							// �ε弿 ������ �ʱ�ȭ
							m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo]		= 0;
							m_stSystemStatus.dblPeakHoldDataLoadCell[nCurrentLoadCellNo]	= 0;

							// CAN ���� ������ �ʱ�ȭ
							if (pstWorkProcedureData->stCanValue[nCurrentMessageNo].bUsable)
								TPRD_CAN_MSG_Process(pstWorkProcedureData->stCanValue[nCurrentMessageNo]);

							PROCESS.nCurrentStep = 3820;
							break;

		// �Ķ���� ����
		case	3820	:
							{
								strParameters.AppendFormat(_T("T_hld=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA2_HOLD]);
								strParameters.AppendFormat(_T("LC_no=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA2_LCC_NO]);

								PROCESS.nCurrentStep = 3830;
							}

							break;

		// ���� ���� üũ
		case	3830	:
							if (GetDIStatus(DI_SENS_S01_DETECT_PRODUCT_DOOR) && GetDIStatus(DI_SENS_S01_PRODUCT_DOOR_OPEN_DN)) {
							
								PROCESS.nCurrentStep = 3840;
								break;
							}

							// ��� ����
							PROCESS.nResultInspection = T_RESULT_ERROR;

							PROCESS.nCurrentStep = 3980;
							break;

		// ���� �ð�
		case	3840	:
							LTimerProceed.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA2_DELAY]);

							PROCESS.nCurrentStep++;
							break;

		case	3841	:
							if (LTimerProceed.Verify())
								PROCESS.nCurrentStep = 3850;

							break;

		// VZ ��� ��ġ �̵�
		case	3850	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVZ)) {

								Motion_MoveTo(	MOTION_RVZ,
												m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME], 
												m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3851	:
							if (Motion_Done(MOTION_RVZ)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME];
								if (!Motion_CheckStopStatus(MOTION_RVZ, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVZ;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 3860;
							}

							break;

		// VX, VY ��ǥ ��ġ ���� �̵�
		case	3860	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVY)) {

								Motion_Move2X(	MCOORD_S01, MOTION_RVX, MOTION_RVY,
												PROCESS.pstWorkPositionInfo[WPS_S01_DOOR_PUSH].dblPosition[MINDEX_VX],
												PROCESS.pstWorkPositionInfo[WPS_S01_DOOR_PUSH].dblPosition[MINDEX_VY],
												m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3861	:
							if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVY)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = PROCESS.pstWorkPositionInfo[WPS_S01_DOOR_PUSH].dblPosition[MINDEX_VX];
								if (!Motion_CheckStopStatus(MOTION_RVX, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVX;
								}

								dblPosition = PROCESS.pstWorkPositionInfo[WPS_S01_DOOR_PUSH].dblPosition[MINDEX_VY];
								if (!Motion_CheckStopStatus(MOTION_RVY, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVY;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 3870;
							}

							break;

		// VZ ��ǥ ��ġ �̵�
		case	3870	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVZ)) {

								Motion_MoveTo(	MOTION_RVZ,
												PROCESS.pstWorkPositionInfo[WPS_S01_DOOR_PUSH].dblPosition[MINDEX_VZ], 
												m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3871	:
							if (Motion_Done(MOTION_RVZ)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = PROCESS.pstWorkPositionInfo[WPS_S01_DOOR_PUSH].dblPosition[MINDEX_VZ];
								if (!Motion_CheckStopStatus(MOTION_RVZ, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVZ;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 3900;
							}

							break;

		// VZ ��� ��ġ �̵�
		case	3900	:
							if (Motion_Done(MOTION_RVZ)) {
		
								DOUBLE	dblCurrentPosition	= 0;
								DOUBLE	dblLimitPositive	= 0;
								DOUBLE	dblPosition			= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA2_MOT_LIMIT];
								DOUBLE	dblSpeed			= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA2_MOT_SPEED];
								

								// ����Ʈ ����Ʈ ����
								AxmStatusGetCmdPos(MOTION_RVZ, &dblCurrentPosition);
								dblLimitPositive = dblCurrentPosition + dblPosition;
								Motion_SetSoftLimit(MOTION_RVZ, m_stMotionAxisInfo[MOTION_RVZ].dblLimitNegativePos, dblLimitPositive);

								// ��� ��ǥ �̵�
								Motion_Move(MOTION_RVZ, dblPosition, dblSpeed);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3901	:
							{
								BOOL	bResult	= TRUE;


								if (m_devCAN.ReadPacket(stReadPacket)) {

									if (stReadPacket.stMessage.ID == pstWorkProcedureData->stCanValue[nCurrentMessageNo].nCAN_ID) {

										// ����� �޼���
										CString	strDebugMessage	= _T("");
										for (UINT nIndex = 0; nIndex < MAX_CAN_MSG_BYTE; nIndex++)	strDebugMessage.AppendFormat(_T("%02X "), stReadPacket.stMessage.DATA[nIndex]);
										NormalMessage(TRUE, _T("CAN READ => %s"), strDebugMessage);

										// ���� ������ ����
										if (TPRD_CAN_MSG_VERIFY_Process(stReadPacket, pstWorkProcedureData->stCanValue[nCurrentMessageNo])) {

											// �˻� ������ ����
											if (nIndexTestDataCAN < MAX_TPRD_DATA_VALUE) {

												stFunctionTestData.stCanValue[nIndexTestDataCAN].bUsable		= TRUE;
												stFunctionTestData.stCanValue[nIndexTestDataCAN].nTypeMessage	= CAN_MSG_TYPE_RX;
												stFunctionTestData.stCanValue[nIndexTestDataCAN].nCAN_ID		= stReadPacket.stMessage.ID;
												stFunctionTestData.stCanValue[nIndexTestDataCAN].nDLC			= stReadPacket.stMessage.DLC;
												memcpy_s(stFunctionTestData.stCanValue[nIndexTestDataCAN].abData, MAX_CAN_MSG_BYTE, stReadPacket.stMessage.DATA, MAX_CAN_MSG_BYTE);
												nIndexTestDataCAN++;
											}

											PROCESS.nCurrentStep++;
											break;
										}
									}
								}

								// �ε弿 ������ üũ
								if (m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo] >= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA2_LC_LIMIT])
									bResult = FALSE;

								// ���� �̵� �Ϸ�
								if (Motion_Done(MOTION_RVZ))
									bResult = FALSE;

								if (!bResult) {
									
									// �˻� ��� ����
									PROCESS.nResultInspection = T_RESULT_FAILURE;
									
									PROCESS.nCurrentStep = 3970;
								}
							}

							break;

		case	3902	:
							// ���� ����
							Motion_Stop_E(MOTION_RVZ);

							// ����Ʈ ����Ʈ �ʱ�ȭ
							Motion_SetSoftLimit(MOTION_RVZ);

							PROCESS.nCurrentStep = 3910;
							break;

		// VZ ������ (FORCE) �̵�
		// VZ FORCE ��ġ �̵� (���밪 �̵�)
		case	3910	:
							if (Motion_Done(MOTION_RVZ)) {

								DOUBLE	dblPosition	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA2_MOT_OFFSET_1];
								DOUBLE	dblSpeed	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA2_MOT_SPEED];

								if (dblSpeed <= 0)	dblSpeed = m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase;

								//Motion_Move(MOTION_RVZ, dblPosition, dblSpeed);
								Motion_MoveTo(MOTION_RVZ, dblPosition, dblSpeed);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3911	:
							if (Motion_Done(MOTION_RVZ)) {

								// �ε弿 ���� ����ȭ �ð�
								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_MEASUREMENT_1));

								PROCESS.nCurrentStep++;
							}

							break;

		case	3912	:
							if (LTimerSteady.Verify()) {
							
								// �ε弿 ������ ����
								PROCESS.dblValueRaw = m_stSystemStatus.dblPeakHoldDataLoadCell[nCurrentLoadCellNo];

								PROCESS.nCurrentStep = 3920;
							}

							break;

		// VZ PUSH ��ġ �̵� (���밪 �̵�)
		case	3920	:
							if (Motion_Done(MOTION_RVZ)) {

								DOUBLE	dblPosition	= PROCESS.pstWorkPositionInfo[WPS_S01_DOOR_PUSH].dblPosition[MINDEX_VZ] + pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA2_MOT_OFFSET_2];
								DOUBLE	dblSpeed	= (PROCESS.pstWorkInfo)->dblWorkInfoValue[WI_ITEM_WORK_SPEED_OFFSET_VZ];

								if (dblSpeed <= 0)	dblSpeed = m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase;

								Motion_MoveTo(MOTION_RVZ, dblPosition, dblSpeed);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3921	:
							if (Motion_Done(MOTION_RVZ)) {

								PROCESS.nCurrentStep = 3950;
							}

							break;

		// VZ ��ǥ ��ġ �̵�
		case	3930	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVZ)) {

								Motion_MoveTo(	MOTION_RVZ,
												PROCESS.pstWorkPositionInfo[WPS_S01_DOOR_PUSH].dblPosition[MINDEX_VZ], 
												m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3931	:
							if (Motion_Done(MOTION_RVZ)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = PROCESS.pstWorkPositionInfo[WPS_S01_DOOR_PUSH].dblPosition[MINDEX_VZ];
								if (!Motion_CheckStopStatus(MOTION_RVZ, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVZ;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 3940;
							}

							break;

		// VZ ������ (PUSH) �̵�
		case	3940	:
							if (Motion_Done(MOTION_RVZ)) {

								DOUBLE	dblPosition	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA2_MOT_OFFSET_2];
								DOUBLE	dblSpeed	= (PROCESS.pstWorkInfo)->dblWorkInfoValue[WI_ITEM_WORK_SPEED_OFFSET_VZ];

								if (dblSpeed <= 0)	dblSpeed = m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase;

								Motion_Move(MOTION_RVZ, dblPosition, dblSpeed);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3941	:
							if (Motion_Done(MOTION_RVZ)) {

								PROCESS.nCurrentStep = 3950;
							}

							break;

		// Ȧ�� �ð� ����
		case	3950	:
							LTimerProceed.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA2_HOLD]);

							PROCESS.nCurrentStep++;
							break;

		case	3951	:
							if (LTimerProceed.Verify())
								PROCESS.nCurrentStep = 3970;

							break;

		// VZ ��� ��ġ �̵�
		case	3970	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVZ)) {

								Motion_MoveTo(	MOTION_RVZ,
												m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME], 
												m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3971	:
							if (Motion_Done(MOTION_RVZ)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME];
								if (!Motion_CheckStopStatus(MOTION_RVZ, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVZ;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 3980;
							}

							break;

		// ��� ����
		case	3980	:
							{
								DOUBLE	dblGain		= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA2_GAIN];
								DOUBLE	dblOffset	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA2_OFFSET];
								DOUBLE	dblSpecMIN	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA2_SPEC_L];
								DOUBLE	dblSpecMAX	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA2_SPEC_H];


								PROCESS.dblValueMeasurement	= (PROCESS.dblValueRaw * dblGain) + dblOffset;

								// �˻� ��� ����
								if (DPS_Round(PROCESS.dblValueMeasurement, 2) < DPS_Round(dblSpecMIN, 2) ||
									DPS_Round(PROCESS.dblValueMeasurement, 2) > DPS_Round(dblSpecMAX, 2))
										PROCESS.nResultInspection = T_RESULT_FAILURE;

								// �˻� ������ ����
								stFunctionTestData.nResult = PROCESS.nResultInspection;
								_stprintf_s(stFunctionTestData.szValue, MAX_STRINPUT_S, _T("%.2f"), PROCESS.dblValueMeasurement);
								_stprintf_s(stFunctionTestData.szSpecMIN, MAX_STRINPUT, _T("%.2f"), dblSpecMIN);
								_stprintf_s(stFunctionTestData.szSpecMAX, MAX_STRINPUT, _T("%.2f"), dblSpecMAX);
								_tcscpy_s(stFunctionTestData.szUnit, MAX_STRINPUT, pstWorkProcedureData->szValue[TPRD_DATA_VALUE_TA2_UNIT]);

								PROCESS.nCurrentStep = 3990;
							}

							break;

		// �Ϸ�
		case	3990	:
							// �۾� ��Ʈ ������Ʈ ����
							PROCESS.bOnUpdateWorkSheet = !pstWorkProcedureData->bOptions[TPRD_DATA_OPT_TA2_UNUSE_UPDATE];
							if (PROCESS.nResultInspection != T_RESULT_SUCCESS)
								PROCESS.bOnUpdateWorkSheet = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� : Ŀ�ǵ� - �ϰ� PUSH �˻� #2 ///////////////////
		case	STEP_WORK_SUB_CMD_TEST_PUSH_2_DN	:
													MessageWindow(cDEBUG, _T("PROC::CMD_TEST_PUSH_DN_02"));

													PROCESS.nCurrentStep = 4610;
													break;

		// �ʱ�ȭ
		case	4610	:
							// �÷��� �ʱ�ȭ
							PROCESS.dblValueRaw			= 0;
							PROCESS.dblValueMeasurement	= 0;
							nCurrentMessageNo			= TPRD_DATA_VALUE_TA3_CAN_MSG;
							nIndexTestDataCAN			= 0;

							// CAN ��� �ʱ�ȭ
							m_devCAN.ClearBuffer();

							// �ε弿 ä�� ����
							nCurrentLoadCellNo = pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA3_LCC_NO];
							if (nCurrentLoadCellNo >= MAX_LOADCELL_CHANNEL_USE)
								nCurrentLoadCellNo = LOADCELL_CH01;

							// �ε弿 ������ �ʱ�ȭ
							m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo]		= 0;
							m_stSystemStatus.dblPeakHoldDataLoadCell[nCurrentLoadCellNo]	= 0;

							// CAN ���� ������ �ʱ�ȭ
							if (pstWorkProcedureData->stCanValue[nCurrentMessageNo].bUsable)
								TPRD_CAN_MSG_Process(pstWorkProcedureData->stCanValue[nCurrentMessageNo]);

							PROCESS.nCurrentStep = 4620;
							break;

		// �Ķ���� ����
		case	4620	:
							{
								strParameters.AppendFormat(_T("T_hld=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA3_HOLD]);
								strParameters.AppendFormat(_T("LC_no=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA3_LCC_NO]);
								strParameters.AppendFormat(_T("Jdg=%.2f "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA3_JUDGE]);

								PROCESS.nCurrentStep = 4630;
							}

							break;

		// ���� ���� üũ
		case	4630	:
							if (GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_1_UP) && GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_2_UP)) {
							
								PROCESS.nCurrentStep = 4640;
								break;
							}

							// ��� ����
							PROCESS.nResultInspection = T_RESULT_ERROR;

							PROCESS.nCurrentStep = 4780;
							break;

		// ���� �ð�
		case	4640	:
							LTimerProceed.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA3_DELAY]);

							PROCESS.nCurrentStep++;
							break;

		case	4641	:
							if (LTimerProceed.Verify())
								PROCESS.nCurrentStep = 4700;

							break;

		// ...?
		case	4700	:
							PROCESS.nCurrentStep = 4710;
							break;

		// ���� ���� ���� #1 : DN
		case	4710	:
							SetDOStatus(DO_ON, DO_SOL_S02_PRODUCT_DOOR_PUSHER_1_DN);
							LTimerTimeOut.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA3_TIMEOUT]);

							PROCESS.nCurrentStep++;
							break;

		case	4711	:
							if (GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_1_DN)) {
							
								// �ε弿 ���� ����ȭ �ð�
								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_MEASUREMENT_1));

								PROCESS.nCurrentStep = 4720;
								break;
							}

							if (LTimerTimeOut.Verify() || 
								m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo] > pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA3_LC_LIMIT]) {
							
								// ����� �޼��� ���
								MessageWindow(cERROR, _T("LOADCELL OVERLOAD FAILURE!! (%.2f, %.2f)"), m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo], pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA3_LC_LIMIT]);

								// ���� ���� ���� #1 : UP
								SetDOStatus(DO_OFF, DO_SOL_S02_PRODUCT_DOOR_PUSHER_1_DN);

								// �˻� ��� ����
								PROCESS.nResultInspection = T_RESULT_FAILURE;

								PROCESS.nCurrentStep = 4780;
							}
							
							break;

		// ������ üũ
		case	4720	:
							if (LTimerSteady.Verify()) {

								// 1�� ������ üũ
								if (m_stSystemStatus.dblPeakHoldDataLoadCell[nCurrentLoadCellNo] < pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA3_JUDGE]) {

									// ����� �޼��� ���
									MessageWindow(cERROR, _T("PUSH #1 JUDGEMENT VALUE FAILURE!! (%.2f, %.2f)"), m_stSystemStatus.dblPeakHoldDataLoadCell[nCurrentLoadCellNo], pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA3_JUDGE]);
								
									// �˻� ��� ����
									PROCESS.nResultInspection = T_RESULT_FAILURE;

									PROCESS.nCurrentStep = 4780;
									break;
								}
							
								// �ε弿 ������ ����
								PROCESS.dblValueRaw = m_stSystemStatus.dblPeakHoldDataLoadCell[nCurrentLoadCellNo];

								PROCESS.nCurrentStep = 4780;
							}

							break;

		// ��� ����
		case	4780	:
							{
								DOUBLE	dblGain		= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA3_GAIN];
								DOUBLE	dblOffset	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA3_OFFSET];
								DOUBLE	dblSpecMIN	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA3_SPEC_L];
								DOUBLE	dblSpecMAX	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA3_SPEC_H];


								PROCESS.dblValueMeasurement	= (PROCESS.dblValueRaw * dblGain) + dblOffset;

								// �˻� ��� ����
								if (DPS_Round(PROCESS.dblValueMeasurement, 2) < DPS_Round(dblSpecMIN, 2) ||
									DPS_Round(PROCESS.dblValueMeasurement, 2) > DPS_Round(dblSpecMAX, 2))
										PROCESS.nResultInspection = T_RESULT_FAILURE;

								// �˻� ������ ����
								stFunctionTestData.nResult = PROCESS.nResultInspection;
								_stprintf_s(stFunctionTestData.szValue, MAX_STRINPUT_S, _T("%.2f"), PROCESS.dblValueMeasurement);
								_stprintf_s(stFunctionTestData.szSpecMIN, MAX_STRINPUT, _T("%.2f"), dblSpecMIN);
								_stprintf_s(stFunctionTestData.szSpecMAX, MAX_STRINPUT, _T("%.2f"), dblSpecMAX);
								_tcscpy_s(stFunctionTestData.szUnit, MAX_STRINPUT, pstWorkProcedureData->szValue[TPRD_DATA_VALUE_TA3_UNIT]);

								PROCESS.nCurrentStep = 4790;
							}

							break;

		// �Ϸ�
		case	4790	:
							// �۾� ��Ʈ ������Ʈ ����
							PROCESS.bOnUpdateWorkSheet = !pstWorkProcedureData->bOptions[TPRD_DATA_OPT_TA3_UNUSE_UPDATE];
							if (PROCESS.nResultInspection != T_RESULT_SUCCESS)
								PROCESS.bOnUpdateWorkSheet = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� : Ŀ�ǵ� - PUSH LOCK �˻� //////////////////////
		case	STEP_WORK_SUB_CMD_TEST_PUSH_LOCK	:
													MessageWindow(cDEBUG, _T("PROC::CMD_TEST_PUSH_LOCK"));

													PROCESS.nCurrentStep = 4810;
													break;

		// �ʱ�ȭ
		case	4810	:
							// �÷��� �ʱ�ȭ
							PROCESS.dblValueRaw			= 0;
							PROCESS.dblValueMeasurement	= 0;
							nCurrentMessageNo			= TPRD_DATA_VALUE_TA4_CAN_MSG;
							nIndexTestDataCAN			= 0;

							// CAN ��� �ʱ�ȭ
							m_devCAN.ClearBuffer();

							// �ε弿 ä�� ����
							nCurrentLoadCellNo = pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA4_LCC_NO];
							if (nCurrentLoadCellNo >= MAX_LOADCELL_CHANNEL_USE)
								nCurrentLoadCellNo = LOADCELL_CH01;

							// �ε弿 ������ �ʱ�ȭ
							m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo]		= 0;
							m_stSystemStatus.dblPeakHoldDataLoadCell[nCurrentLoadCellNo]	= 0;

							// CAN ���� ������ �ʱ�ȭ
							if (pstWorkProcedureData->stCanValue[nCurrentMessageNo].bUsable)
								TPRD_CAN_MSG_Process(pstWorkProcedureData->stCanValue[nCurrentMessageNo]);

							PROCESS.nCurrentStep = 4820;
							break;

		// �Ķ���� ����
		case	4820	:
							{
								switch (pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA4_MODE]) {
					
									case	0	:	strParameters.AppendFormat(_T("Mode=NORMAL "));		break;
									case	1	:	strParameters.AppendFormat(_T("Mode=LOCK "));		break;
									default		:	strParameters.AppendFormat(_T("Mode=ERR "));		break;
								}

								strParameters.AppendFormat(_T("T_hld=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA4_HOLD]);
								strParameters.AppendFormat(_T("LC_no=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA4_LCC_NO]);
								strParameters.AppendFormat(_T("Jdg=%.2f "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA4_JUDGE]);

								PROCESS.nCurrentStep = 4830;
							}

							break;

		// ���� ���� üũ
		case	4830	:
							if (GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_1_DN) && GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_2_UP)) {
							
								PROCESS.nCurrentStep = 4840;
								break;
							}

							// ��� ����
							PROCESS.nResultInspection = T_RESULT_ERROR;

							PROCESS.nCurrentStep = 4880;
							break;

		// ���� �ð�
		case	4840	:
							LTimerProceed.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA4_DELAY]);

							PROCESS.nCurrentStep++;
							break;

		case	4841	:
							if (LTimerProceed.Verify())
								PROCESS.nCurrentStep = 4900;

							break;

		// ...?
		case	4900	:
							PROCESS.nCurrentStep = 4910;
							break;

		// ���� ���� ���� #2 : DN
		case	4910	:
							pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_2_DN]  = TRUE;
							m_stSystemStatus.nSCP_TimeDoorPushLockDown			= pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA4_TIMEOUT];

							PROCESS.nCurrentStep++;
							break;

		case	4911	:
							if (!pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_2_DN]) {
							
								// Ȧ�� �ð� ����
								LTimerProceed.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA4_HOLD]);

								PROCESS.nCurrentStep = 4920;
								break;
							}

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;
							
							break;

		case	4912	:
							if (LTimerProceed.Verify())
								PROCESS.nCurrentStep = 4920;

							break;

		// ���� ���� ���� #2 : UP
		case	4920	:
							pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_2_UP] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	4921	:
							if (!pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_2_UP]) {
							
								if (pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA4_MODE] == 1) {

									// �ε弿 ���� ����ȭ �ð�
									LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_MEASUREMENT_1));

									PROCESS.nCurrentStep++;
									break;
								}

								PROCESS.nCurrentStep = 4990;
								break;
							}

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;
							
							break;

		case	4922	:
							if (LTimerSteady.Verify()) {
							
								// �ε弿 ������ ����
								PROCESS.dblValueRaw = m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo];

								PROCESS.nCurrentStep = 4980;
							}

							break;

		// ��� ����
		case	4980	:
							{
								DOUBLE	dblGain		= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA4_GAIN];
								DOUBLE	dblOffset	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA4_OFFSET];
								DOUBLE	dblSpecMIN	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA4_SPEC_L];
								DOUBLE	dblSpecMAX	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA4_SPEC_H];


								PROCESS.dblValueMeasurement	= (PROCESS.dblValueRaw * dblGain) + dblOffset;

								// �˻� ��� ����
								if (DPS_Round(PROCESS.dblValueMeasurement, 2) < DPS_Round(dblSpecMIN, 2) ||
									DPS_Round(PROCESS.dblValueMeasurement, 2) > DPS_Round(dblSpecMAX, 2))
										PROCESS.nResultInspection = T_RESULT_FAILURE;

								// �˻� ������ ����
								stFunctionTestData.nResult = PROCESS.nResultInspection;
								_stprintf_s(stFunctionTestData.szValue, MAX_STRINPUT_S, _T("%.2f"), PROCESS.dblValueMeasurement);
								_stprintf_s(stFunctionTestData.szSpecMIN, MAX_STRINPUT, _T("%.2f"), dblSpecMIN);
								_stprintf_s(stFunctionTestData.szSpecMAX, MAX_STRINPUT, _T("%.2f"), dblSpecMAX);
								_tcscpy_s(stFunctionTestData.szUnit, MAX_STRINPUT, pstWorkProcedureData->szValue[TPRD_DATA_VALUE_TA4_UNIT]);

								PROCESS.nCurrentStep = 4990;
							}

							break;

		// �Ϸ�
		case	4990	:
							// �۾� ��Ʈ ������Ʈ ����
							PROCESS.bOnUpdateWorkSheet = pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA4_MODE] == 0 ? FALSE : !pstWorkProcedureData->bOptions[TPRD_DATA_OPT_TA4_UNUSE_UPDATE];
							if (PROCESS.nResultInspection != T_RESULT_SUCCESS)
								PROCESS.bOnUpdateWorkSheet = pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA4_MODE] == 0 ? FALSE : TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� : Ŀ�ǵ� - ��� �˻� ///////////////////////////
		case	STEP_WORK_SUB_CMD_TEST_COMM	:
												MessageWindow(cDEBUG, _T("PROC::CMD_TEST_COMM"));

												PROCESS.nCurrentStep = 4010;
												break;

		// �ʱ�ȭ
		case	4010	:
							// �÷��� �ʱ�ȭ
							nCurrentMessageNo	= TPRD_DATA_VALUE_TC_CAN_MSG;
							nIndexTestDataCAN	= 0;

							// CAN ��� �ʱ�ȭ
							m_devCAN.ClearBuffer();

							PROCESS.nCurrentStep = 4020;
							break;

		// �Ķ���� ����
		case	4020	:
							{
								PROCESS.nCurrentStep = 4100;
							}

							break;

		// CAN �޼��� ������ üũ
		case	4100	:
							if (g_stTestProcedureDataValue[pstWorkProcedureData->nCommand][nCurrentMessageNo].bUseData) {
							
								if (pstWorkProcedureData->stCanValue[nCurrentMessageNo].bUsable) {
								
									TPRD_CAN_MSG_Process(pstWorkProcedureData->stCanValue[nCurrentMessageNo]);
									PROCESS.nCurrentStep = pstWorkProcedureData->stCanValue[nCurrentMessageNo].nTypeMessage == CAN_MSG_TYPE_TX ? 4110 : 4120;
									break;
								}
							}

							PROCESS.nCurrentStep++;
							break;

		case	4101	:
							if (++nCurrentMessageNo >= MAX_TPRD_DATA_VALUE) {
							
								PROCESS.nCurrentStep = 4180;
								break;
							}

							PROCESS.nCurrentStep--;
							break;

		// CAN �޼��� �۽�
		case	4110	:
							ZeroMemory(&stSendPacket, sizeof(PCAN_PACKET_T));
							stSendPacket.stMessage.ID		= pstWorkProcedureData->stCanValue[nCurrentMessageNo].nCAN_ID;
							stSendPacket.stMessage.DLC		= pstWorkProcedureData->stCanValue[nCurrentMessageNo].nDLC;
							stSendPacket.stMessage.MSGTYPE	= PCAN_MESSAGE_STANDARD;
							memcpy_s(stSendPacket.stMessage.DATA, MAX_CAN_MSG_BYTE, pstWorkProcedureData->stCanValue[nCurrentMessageNo].abData, MAX_CAN_MSG_BYTE);
							m_devCAN.SendPacket(stSendPacket);
							 
							// �۽� Ÿ�� �ƿ� ����
							LTimerTimeOut.Start(pstWorkProcedureData->stCanValue[nCurrentMessageNo].nTimeout);

							// �˻� ������ ����
							if (nIndexTestDataCAN < MAX_TPRD_DATA_VALUE) {

								stFunctionTestData.stCanValue[nIndexTestDataCAN].bUsable		= TRUE;
								stFunctionTestData.stCanValue[nIndexTestDataCAN].nTypeMessage	= CAN_MSG_TYPE_TX;
								stFunctionTestData.stCanValue[nIndexTestDataCAN].nCAN_ID		= stSendPacket.stMessage.ID;
								stFunctionTestData.stCanValue[nIndexTestDataCAN].nDLC			= stSendPacket.stMessage.DLC;
								memcpy_s(stFunctionTestData.stCanValue[nIndexTestDataCAN].abData, MAX_CAN_MSG_BYTE, stSendPacket.stMessage.DATA, MAX_CAN_MSG_BYTE);
								nIndexTestDataCAN++;
							}

							PROCESS.nCurrentStep = 4101;
							break;

		// CAN �޼��� ����
		case	4120	:
							// ���� Ÿ�� �ƿ� ����
							LTimerTimeOut.Start(pstWorkProcedureData->stCanValue[nCurrentMessageNo].nTimeout);

							PROCESS.nCurrentStep++;
							break;

		case	4121	:
							if (m_devCAN.ReadPacket(stReadPacket)) {
								
								if (stReadPacket.stMessage.ID == pstWorkProcedureData->stCanValue[nCurrentMessageNo].nCAN_ID) {

									// ����� �޼���
									CString	strDebugMessage = _T("");
									for (UINT nIndex = 0; nIndex < MAX_CAN_MSG_BYTE; nIndex++)	strDebugMessage.AppendFormat(_T("%02X "), stSendPacket.stMessage.DATA[nIndex]);
									NormalMessage(TRUE, _T("CAN SEND => %s"), strDebugMessage);

									strDebugMessage.Empty();
									for (UINT nIndex = 0; nIndex < MAX_CAN_MSG_BYTE; nIndex++)	strDebugMessage.AppendFormat(_T("%02X "), stReadPacket.stMessage.DATA[nIndex]);
									NormalMessage(TRUE, _T("CAN READ => %s"), strDebugMessage);

									// ���� ������ ����
									if (TPRD_CAN_MSG_VERIFY_Process(stReadPacket, pstWorkProcedureData->stCanValue[nCurrentMessageNo])) {

										// �˻� ������ ����
										if (nIndexTestDataCAN < MAX_TPRD_DATA_VALUE) {

											stFunctionTestData.stCanValue[nIndexTestDataCAN].bUsable		= TRUE;
											stFunctionTestData.stCanValue[nIndexTestDataCAN].nTypeMessage	= CAN_MSG_TYPE_RX;
											stFunctionTestData.stCanValue[nIndexTestDataCAN].nCAN_ID		= stReadPacket.stMessage.ID;
											stFunctionTestData.stCanValue[nIndexTestDataCAN].nDLC			= stReadPacket.stMessage.DLC;
											memcpy_s(stFunctionTestData.stCanValue[nIndexTestDataCAN].abData, MAX_CAN_MSG_BYTE, stReadPacket.stMessage.DATA, MAX_CAN_MSG_BYTE);
											nIndexTestDataCAN++;
										}

										PROCESS.nCurrentStep = 4101;
										break;
									}
								}
							}

							// Ÿ�� �ƿ�
							if (LTimerTimeOut.Verify()) {

								// �˻� ������ ����
								_tcscpy_s(stFunctionTestData.szValue, MAX_STRINPUT_S, _T("RESPONSE TIMEOUT"));
								if (nIndexTestDataCAN < MAX_TPRD_DATA_VALUE) {

									stFunctionTestData.stCanValue[nIndexTestDataCAN].bUsable		= TRUE;
									stFunctionTestData.stCanValue[nIndexTestDataCAN].nTypeMessage	= CAN_MSG_TYPE_RX;
									stFunctionTestData.stCanValue[nIndexTestDataCAN].nCAN_ID		= stReadPacket.stMessage.ID;
									stFunctionTestData.stCanValue[nIndexTestDataCAN].nDLC			= stReadPacket.stMessage.DLC;
									memcpy_s(stFunctionTestData.stCanValue[nIndexTestDataCAN].abData, MAX_CAN_MSG_BYTE, stReadPacket.stMessage.DATA, MAX_CAN_MSG_BYTE);
									nIndexTestDataCAN++;
								}
							
								PROCESS.nResultInspection	= T_RESULT_FAILURE;
								PROCESS.nCurrentStep		= 4180;
							}

							break;

		// ���հ� ���� �� ��˻�
		case	4180	:
							if (m_SystemConfig.UseSystemOption(SOPT_RETRY_WORK_NG)) {

								if (PROCESS.nResultInspection != T_RESULT_SUCCESS) {

									// ��õ� ī��Ʈ üũ
									if (++PROCESS.nRetryCount <= m_SystemConfig.GetWorkRetryCount()) {

										// �÷��� �ʱ�ȭ
										PROCESS.nResultInspection = T_RESULT_SUCCESS;

										PROCESS.nCurrentStep = 4010;
										break;
									}
								}
							}

							PROCESS.nCurrentStep = 4190;
							break;

		// �Ϸ�
		case	4190	:
							// �˻� ������ ����
							stFunctionTestData.nResult = PROCESS.nResultInspection;

							// �۾� ��Ʈ ������Ʈ ����
							PROCESS.bOnUpdateWorkSheet = !pstWorkProcedureData->bOptions[TPRD_DATA_OPT_TC_UNUSE_UPDATE];
							if (PROCESS.nResultInspection != T_RESULT_SUCCESS)
								PROCESS.bOnUpdateWorkSheet = TRUE;


							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� : Ŀ�ǵ� - ���� �˻� (�ӽź���) ////////////////
		case	STEP_WORK_SUB_CMD_TEST_VISION_1	:
													MessageWindow(cDEBUG, _T("PROC::CMD_TEST_VISION_01"));

													PROCESS.nCurrentStep = 4210;
													break;

		// �ʱ�ȭ
		case	4210	:
							// �÷��� �ʱ�ȭ
							PROCESS.bResultMainProcess = FALSE;

							// ���� ���ν��� ��ȣ ����
							m_stSystemStatus.nCurrentWorkProcedureNo = PROCESS.nCurrentProcedureNo;

							// ���� �˻� �׸� ����
							PROCESS.nCurrentWorkSheetNo = pstWorkProcedureData->nValue[TPRD_DATA_VALUE_VISION_01_TEST_NO] - 1;
							m_stSystemStatus.nMainProcessWorkIndex[nSTATION_NO][STN1_SUB_VISION] = PROCESS.nCurrentWorkSheetNo;

							// �˻� ��Ʈ �ʱ�ȭ
							ZeroMemory((PROCESS.pstWorkStatus)->stMeasSheet, sizeof(MEAS_SHEET_T) * MAX_TEST_SHEET);

							PROCESS.nCurrentStep = 4220;
							break;

		// �Ķ���� ����
		case	4220	:
							{
								switch (pstWorkProcedureData->nValue[TPRD_DATA_VALUE_VISION_01_MODE]) {
					
									case	0	:	strParameters.AppendFormat(_T("Mode=SINGLE "));		break;
									case	1	:	strParameters.AppendFormat(_T("Mode=CONTI "));		break;
									default		:	strParameters.AppendFormat(_T("Mode=ERR "));		break;
								}

								strParameters.AppendFormat(_T("Ts_no=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_VISION_01_TEST_NO]);

								switch (pstWorkProcedureData->nValue[TPRD_DATA_VALUE_VISION_01_MOVE_MODE]) {
					
									case	0	:	strParameters.AppendFormat(_T("Move=NORMAL "));	break;
									case	1	:	strParameters.AppendFormat(_T("Move=INTP "));	break;
									default		:	strParameters.AppendFormat(_T("Move=ERR "));	break;
								}

								PROCESS.nCurrentStep = 4300;
							}

							break;

		// �˻� ����
		case	4300	:
							if (pstWorkProcedureData->nValue[TPRD_DATA_VALUE_VISION_01_MODE] == 0)	m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][STN1_SUB_VISION]	= TRUE;
							else																	m_stSystemStatus.bOnMainProcess[nSTATION_NO][STN1_SUB_VISION]		= TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	4301	:
							if (!m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][STN1_SUB_VISION] && !m_stSystemStatus.bOnMainProcess[nSTATION_NO][STN1_SUB_VISION]) {
							
								PROCESS.bResultMainProcess = m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][STN1_SUB_VISION];

								PROCESS.nCurrentStep = 4310;
							}

							break;

		// ��� ����
		case	4310	:
							{
								// �˻� ������ ����
								stFunctionTestData.nResult = (PROCESS.pstWorkStatus)->stMeasSheet[PROCESS.nCurrentWorkSheetNo].nResult;
								_stprintf_s(stFunctionTestData.szValue, MAX_STRINPUT_S, _T("%s"), PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].szUserDefName);

								// �˻� ��� ����
								PROCESS.nResultInspection = (PROCESS.pstWorkStatus)->stMeasSheet[PROCESS.nCurrentWorkSheetNo].nResult;

								PROCESS.nCurrentStep = 4390;
							}

							break;

		// �Ϸ�
		case	4390	:
							// �۾� ��Ʈ ������Ʈ ����
							PROCESS.bOnUpdateWorkSheet = !pstWorkProcedureData->bOptions[TPRD_DATA_OPT_VISION_01_UNUSE_UPDATE];
							if (PROCESS.nResultInspection != T_RESULT_SUCCESS)
								PROCESS.bOnUpdateWorkSheet = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� : Ŀ�ǵ� - ���� �˻� (��������) ////////////////
		case	STEP_WORK_SUB_CMD_TEST_VISION_2	:
													MessageWindow(cDEBUG, _T("PROC::CMD_TEST_VISION_02"));

													PROCESS.nCurrentStep = 4410;
													break;

		// �ʱ�ȭ
		case	4410	:
							// �÷��� �ʱ�ȭ
							PROCESS.bResultMainProcess	= FALSE;
							PROCESS.nUpdateWorkSheetNo	= m_stSystemStatus.nCurrentVisionWorkSheetUpdateNo;
							bOnVisionTrigged			= FALSE;

							// ���� ���ν��� ��ȣ ����
							m_stSystemStatus.nCurrentWorkProcedureNo = PROCESS.nCurrentProcedureNo;

							// ���� �˻� �׸� ����
							PROCESS.nCurrentWorkSheetNo = pstWorkProcedureData->nValue[TPRD_DATA_VALUE_VISION_02_PGM_NO];

							// �˻� ��Ʈ �ʱ�ȭ
							ZeroMemory((PROCESS.pstWorkStatus)->stMeasSheet, sizeof(MEAS_SHEET_T) * MAX_TEST_SHEET);

							// ���� �̹��� ����
							DPS_DeleteDirectory(m_SystemConfig.GetWorkDirectory(DIR_IMPORT_DATA), FALSE);

							// ���� �̹��� ������ �ʱ�ȭ
							if (m_pMainWnd)	{
								
								m_stSystemStatus.bIsVisionImageWindowCleared = FALSE;
								m_pMainWnd->PostMessage(UM_VISION_CLEAR_IMAGE);
							}

							PROCESS.nCurrentStep = 4420;
							break;

		// �Ķ���� ����
		case	4420	:
							{
								strParameters.AppendFormat(_T("Pgm_no=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_VISION_02_PGM_NO]);

								PROCESS.nCurrentStep = 4440;
							}

							break;

		// ���� ���� �ʱ�ȭ
		case	4440	:
							// ���� ���� üũ
							if (GetDIStatus(DI_SIG_S02_VISION_ERROR)) {
							
								PROCESS.nResultInspection	= T_RESULT_ERROR;
								PROCESS.nCurrentStep		= 4580;
								break;
							}

							// ���� ���α׷� ��ȣ ����
							VISION_SelectProgramNo(TRUE, PROCESS.nCurrentWorkSheetNo);
							LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_VISION_SENSOR));

							PROCESS.nCurrentStep = 4500;
							break;

		// �˻� ����
		case	4500	:
							if (LTimerSteady.Verify()) {
							
								// ���� ����
								SetDOStatus(DO_ON, DO_SIG_S02_VISION_TRIG);
								bOnVisionTrigged = TRUE;

								LTimerSignal.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_ACTION_SIGNAL_VISION_SENSOR));
								LTimerTimeOut.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_VISION_02_TIMEOUT]);
								LTimerProceed.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_VISION_02_TIME]);

								PROCESS.nCurrentStep++;
							}

							break;

		case	4501	:
							if (LTimerProceed.Verify()) {
							
								// BUSY üũ
								if (!GetDIStatus(DI_SIG_S02_VISION_BUSY)) {
								
									if (GetDIStatus(DI_SIG_S02_VISION_RESULT))	PROCESS.nResultInspection = T_RESULT_SUCCESS;
									else										PROCESS.nResultInspection = T_RESULT_FAILURE;

									PROCESS.nCurrentStep++;
								}
							}

							break;

		case	4502	:
							{
								// ���� �̹��� ���� �̸� ����
								strVisionImageName.Empty();
								strVisionImageName.Format(	_T("%s\\%05d_%02d_%s.BMP"),		
															m_SystemConfig.GetWorkDirectory(DIR_IMPORT_DATA),
															0,
															PROCESS.nCurrentWorkSheetNo,
															PROCESS.nResultInspection == T_RESULT_SUCCESS ? _T("OK") : _T("NG"));

								MessageWindow(cDEBUG, _T("VISION IMG=%s"), strVisionImageName);

								// ���� ��� ���� �̸� ����
								strVisionResultName.Empty();
								strVisionResultName.Format(	_T("%s\\%05d_%02d_%s.TXT"),	
															m_SystemConfig.GetWorkDirectory(DIR_IMPORT_DATA),
															0,
															PROCESS.nCurrentWorkSheetNo,
															PROCESS.nResultInspection == T_RESULT_SUCCESS ? _T("OK") : _T("NG"));

								MessageWindow(cDEBUG, _T("VISION TXT=%s"), strVisionResultName);

								PROCESS.nCurrentStep++;
							}

							break;

		case	4503	:
							if (m_stSystemStatus.bIsVisionImageWindowCleared) {

								VISION_RESULT_T	stVisionResult;
								CFileFind		fileFinderImage;
								CFileFind		fileFinderResult;

								// ���� �̹��� ���� üũ
								if (fileFinderImage.FindFile(strVisionImageName) && fileFinderResult.FindFile(strVisionResultName)) {

									// ���� ��� ��������
									if (!VISION_ImportResult(strVisionResultName, stVisionResult)) {

										PROCESS.nResultInspection = T_RESULT_ERROR;
									}

									// ��� ���� ����
									if (PROCESS.nResultInspection != T_RESULT_ERROR) {

										CString		strNewVisionImageName	= _T("");
										CString		strNewVisionResultName	= _T("");

// 										strNewVisionImageName.Format(_T("%s\\%s.%s"),	(PROCESS.pstWorkStatus)->szWorkDataSaveDirectory,
// 																						DPS_GetFileInfo(strVisionImageName).szFileName,
// 																						DPS_GetFileInfo(strVisionImageName).szFileExtension);

										strNewVisionResultName.Format(_T("%s\\%s.%s"),	(PROCESS.pstWorkStatus)->szWorkDataSaveDirectory,
																						DPS_GetFileInfo(strVisionResultName).szFileName,
																						DPS_GetFileInfo(strVisionResultName).szFileExtension);
									
										CopyFile(strVisionImageName, strNewVisionImageName, FALSE);
										CopyFile(strVisionResultName, strNewVisionResultName, FALSE);
									}

									PROCESS.nCurrentStep++;
									break;
								}

								// Ÿ�� �ƿ�
								if (LTimerTimeOut.Verify()) {

									// ��� ����
									PROCESS.nResultInspection = T_RESULT_ERROR;
								
									// �޼��� ���
									if (m_nTypeLanguage == LANGUAGE_KOR)	ErrorMessage(TRUE, _T("���� ���� �̹����� �ε��� �� �����ϴ�."));
									else									ErrorMessage(TRUE, _T("Vision Sensor Result Image Failure."));

									PROCESS.nCurrentStep++;
								}
							}

							break;

		case	4504	:
							// ���� Ʈ���� ����
							SetDOStatus(DO_OFF, DO_SIG_S02_VISION_TRIG);	

							PROCESS.nCurrentStep = 4520;
							break;

		// �̹��� ����
		case	4520	:
							if (PROCESS.nResultInspection != T_RESULT_ERROR) {

								// �̹��� ������Ʈ
								if (m_MilImageInspection[PROCESS.nCurrentWorkSheetNo] != M_NULL) {

									MbufFree(m_MilImageInspection[PROCESS.nCurrentWorkSheetNo]);
									m_MilImageInspection[PROCESS.nCurrentWorkSheetNo] = M_NULL;
								}

								MbufImport((MIL_TEXT_CHAR*)(LPCTSTR)strVisionImageName, M_DEFAULT, M_RESTORE, m_MilSystem, &m_MilImageInspection[PROCESS.nCurrentWorkSheetNo]);

								// �̹��� �����쿡 �ε�
								if (m_pMainWnd)	m_pMainWnd->SendMessage(UM_VISION_LOAD_IMAGE, VISION_CH1, (LPARAM)m_MilImageInspection[PROCESS.nCurrentWorkSheetNo]);

								// ��� �̹��� ����
								if (m_SystemConfig.UseSystemOption(SOPT_SAVE_VISION_IMAGE))			SaveVisionImage(PROCESS.nCurrentWorkSheetNo, FALSE);
								if (m_SystemConfig.UseSystemOption(SOPT_SAVE_VISION_IMAGE_JPEG))	SaveVisionImage(PROCESS.nCurrentWorkSheetNo, FALSE, TRUE);

								// ���հ� ���� �� ���� �˻� �̹��� ����
								if (m_SystemConfig.UseSystemOption(SOPT_SAVE_VISION_IMAGE_NG) && PROCESS.nResultInspection == T_RESULT_FAILURE)
									SaveVisionImage(PROCESS.nCurrentWorkSheetNo, FALSE);
							}

							PROCESS.nCurrentStep = 4580;
							break;

		// ��� ����
		case	4580	:
							{
								// �˻� ������ ����
								stFunctionTestData.nResult = PROCESS.nResultInspection;
								_stprintf_s(stFunctionTestData.szValue, MAX_STRINPUT_S, _T("%s"), pstWorkProcedureData->szName);

								// �˻� ��� ����
								(PROCESS.pstWorkStatus)->stMeasSheet[PROCESS.nCurrentWorkSheetNo].nResult = PROCESS.nResultInspection;

								PROCESS.nCurrentStep = 4590;
							}

							break;

		// �Ϸ�
		case	4590	:
							// �۾� ��Ʈ ������Ʈ ����
							PROCESS.bOnUpdateWorkSheet = !pstWorkProcedureData->bOptions[TPRD_DATA_OPT_VISION_02_UNUSE_UPDATE];
							if (PROCESS.nResultInspection != T_RESULT_SUCCESS)
								PROCESS.bOnUpdateWorkSheet = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� : Ŀ�ǵ� - �ð� ���� ///////////////////////////
		case	STEP_WORK_SUB_CMD_DELAY	:
											MessageWindow(cDEBUG, _T("PROC::CMD_DELAY"));

											PROCESS.nCurrentStep = 5010;
											break;

		// �ʱ�ȭ
		case	5010	:
							PROCESS.nCurrentStep = 5020;
							break;

		// �Ķ���� ����
		case	5020	:
							{
								strParameters.AppendFormat(_T("T_dly=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_DELAY_TIME]);

								PROCESS.nCurrentStep = 5050;
							}

							break;

		// ���� �ð� ����
		case	5050	:
							LTimerProceed.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_DELAY_TIME]);

							PROCESS.nCurrentStep++;
							break;

		case	5051	:
							if (LTimerProceed.Verify())
								PROCESS.nCurrentStep = 5190;

							break;

		// �Ϸ�
		case	5190	:
							// �˻� ������ ����
							stFunctionTestData.nResult = PROCESS.nResultInspection;
							_stprintf_s(stFunctionTestData.szValue, MAX_STRINPUT_S, _T("%d"), pstWorkProcedureData->nValue[TPRD_DATA_VALUE_DELAY_TIME]);
							_tcscpy_s(stFunctionTestData.szUnit, MAX_STRINPUT, _T("msec"));

							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� : �Ŀ� ���ö��� ���� ///////////////////////////
		case	STEP_WORK_SUB_SET_PS	:
											MessageWindow(cDEBUG, _T("PROC::SUB-SET PS"));

											PROCESS.nCurrentStep = m_SystemConfig.IsSimulationMode() ? 6090 : 6010;
											break;

		// �ʱ�ȭ
		case	6010	:
							PROCESS.nRetryCount		= 0;
							PROCESS.nRetrySubCount	= 0;

							PROCESS.nCurrentStep = bSetupState ? 6020 : 6030;
							break;

		// ����/���� ����
		case	6020	:
							if (LTimerSteadyPS.Verify()) {

								LTimerSteadyPS.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_PS_CONTROL));

								if (dblSetupValueVoltage > g_stODAPWRModelInfo[ODAPWR_OPS_305].dblMaxVoltage)
									dblSetupValueVoltage = g_stODAPWRModelInfo[ODAPWR_OPS_305].dblMaxVoltage;

								if (dblSetupValueCurrent > g_stODAPWRModelInfo[ODAPWR_OPS_305].dblMaxCurrent)
									dblSetupValueCurrent = g_stODAPWRModelInfo[ODAPWR_OPS_305].dblMaxCurrent;

								if (m_devPOWER.SetVoltageCurrent(dblSetupValueVoltage, dblSetupValueCurrent)) {

									PROCESS.nRetrySubCount = 0;
									PROCESS.nCurrentStep++;
									break;
								}

								if (++PROCESS.nRetrySubCount >= MAX_RETRY_DEVICE) {

									PROCESS.nCurrentStep = 6080;
									break;
								}
							}

							break;

		case	6021	:
							if (LTimerSteadyPS.Verify()) {

								LTimerSteadyPS.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_PS_CONTROL));
								if (m_devPOWER.GetVoltageCurrent(stODAPowerData)) {

									// ���� �Ҽ��� 1�ڸ�, ���� �Ҽ��� 2�ڸ� ��
									if ((INT)(stODAPowerData.dblVoltage_V * 10) == (INT)(dblSetupValueVoltage * 10) &&
										(INT)(stODAPowerData.dblCurrent_A * 100) == (INT)(dblSetupValueCurrent * 100)) {

										PROCESS.nRetryCount		= 0;
										PROCESS.nRetrySubCount	= 0;
										PROCESS.nCurrentStep	= 6030;
										break;
									}

									if (++PROCESS.nRetryCount >= MAX_RETRY_DEVICE) {

										PROCESS.nCurrentStep = 6080;
										break;
									}

									PROCESS.nCurrentStep--;
									break;
								}

								if (++PROCESS.nRetrySubCount >= MAX_RETRY_DEVICE) {

									PROCESS.nCurrentStep = 6080;
									break;
								}
							}

							break;

		// ��� ���� ����
		case	6030	:
							if (LTimerSteadyPS.Verify()) {

								LTimerSteadyPS.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_PS_CONTROL));
								if (m_devPOWER.SetStateOutput(bSetupState)) {

									PROCESS.nRetrySubCount = 0;
									PROCESS.nCurrentStep++;
									break;
								}

								if (++PROCESS.nRetrySubCount >= MAX_RETRY_DEVICE) {

									PROCESS.nCurrentStep = 6080;
									break;
								}
							}

							break;

		case	6031	:
							if (LTimerSteadyPS.Verify()) {

								LTimerSteadyPS.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_PS_CONTROL));
								if (m_devPOWER.GetStateOutput(stODAPowerData)) {

									if (stODAPowerData.bStateOutput == bSetupState) {

										PROCESS.nRetryCount		= 0;
										PROCESS.nRetrySubCount	= 0;
										PROCESS.nCurrentStep	= 6090;
										break;
									}

									if (++PROCESS.nRetryCount >= MAX_RETRY_DEVICE) {

										PROCESS.nCurrentStep = 6080;
										break;
									}

									PROCESS.nCurrentStep--;
									break;
								}

								if (++PROCESS.nRetrySubCount >= MAX_RETRY_DEVICE) {

									PROCESS.nCurrentStep = 6080;
									break;
								}
							}

							break;
								
		// ����
		case	6080	:
							// �޼��� ���
							ErrorMessage(TRUE, _T("�Ŀ��ҽ��� �������� �ʽ��ϴ�."));

							PROCESS.nCurrentStep = STEP_WORK_ERROR_DEVICE;
							break;

		// �Ϸ�
		case	6090	:
							PROCESS.nCurrentStep = PROCESS.nReturn03Step;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� : �Ŀ� ���ö��� ���� ///////////////////////////
		case	STEP_WORK_SUB_GET_PS	:
											MessageWindow(cDEBUG, _T("PROC::SUB-GET PS"));

											PROCESS.nCurrentStep = 6110;
											break;

		// �ʱ�ȭ
		case	6110	:
							PROCESS.nRetryCount			= 0;
							PROCESS.nRetrySubCount		= 0;
							PROCESS.dblValueMeasurement	= 0;

							PROCESS.nCurrentStep = 6120;
							break;

		// ����/���� ����
		case	6120	:
							if (LTimerSteadyPS.Verify()) {

								LTimerSteadyPS.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_PS_CONTROL));
								if (m_devPOWER.MeasVoltageCurrent(stODAPowerData)) {

									PROCESS.dblValueMeasurement	= stODAPowerData.dblCurrent_A;

									PROCESS.nRetryCount		= 0;
									PROCESS.nRetrySubCount	= 0;
									PROCESS.nCurrentStep	= 6190;
									break;
								}

								if (++PROCESS.nRetrySubCount >= MAX_RETRY_DEVICE) {

									PROCESS.nCurrentStep = 6180;
									break;
								}
							}

							break;

		// ����
		case	6180	:
							// �޼��� ���
							ErrorMessage(TRUE, _T("�Ŀ��ҽ��� �������� �ʽ��ϴ�."));

							PROCESS.nCurrentStep = STEP_WORK_ERROR_DEVICE;
							break;

		// �Ϸ�
		case	6190	:
							PROCESS.nCurrentStep = PROCESS.nReturn03Step;
							break;


		/////////////////////////////////////////////////////////////
		// ���� /////////////////////////////////////////////////////
		case	STEP_WORK_ERROR	:
									PROCESS.bOnOperatingStop = TRUE;
									break;

		case	STEP_WORK_ERROR_PARTS	:
											PROCESS.bOnError				= TRUE;
											PROCESS.nRecoveryStep			= STEP_WORK_ERROR;
											PROCESS.stErrorCode.nErrorCode	= ERROR_MACHINE_SEQUENCE;
											PROCESS.stErrorCode.nProcessID	= PROCESS_MAIN_WORK_TEST;
											PROCESS.stErrorCode.nStationNo	= nSTATION_NO;

											// ����� �޼���
											SDebugMessage(TRUE, _T("[P%d:%d] ERROR PARTS"), nSTATION_NO, nSTATION_SUB_NO + 1);
											break;

		case	STEP_WORK_ERROR_SYSTEM	:
											// ����� �޼���
											SDebugMessage(TRUE, _T("[P%d:%d] ERROR SYSTEM"), nSTATION_NO, nSTATION_SUB_NO + 1);
											break;	

		case	STEP_WORK_ERROR_DEVICE	:
											// ����� �޼���
											SDebugMessage(TRUE, _T("[P%d:%d] ERROR DEVICE"), nSTATION_NO, nSTATION_SUB_NO + 1);

											// �޼��� ���
											ErrorMessage(TRUE, _T("[P%d] NO RESPONSE DEVICE"), nSTATION_NO);

											// ���μ��� �÷��� �ʱ�ȭ
											m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]				= FALSE;
											m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
											m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
											m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
											m_stSystemStatus.bIsMainProcessInitialized[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;

											PROCESS.nCurrentStep = STEP_WORK_STANDBY;
											break;	


		/////////////////////////////////////////////////////////////
		// �Ͻ� ���� ���� ///////////////////////////////////////////
		case	STEP_PAUSE	:
								if (m_stSystemStatus.bOnEmergencyStop) {

									PROCESS.nCurrentStep = STEP_EMG;
									break;
								}

								PROCESS.nCurrentStep++;
								break;

		case	20001	:
							if (!m_stSystemStatus.bOnPause && !m_stSystemStatus.bOnAlarmSystem && !m_stSystemStatus.bOnAlarmStation[nSTATION_NO]) {

								PROCESS.nCurrentStep = 20100;
							}

							break;

		// ���� ����
		case	20100	:
							PROCESS.nCurrentStep	= PROCESS.nRecoveryStep;
							PROCESS.bOnPause		= FALSE;
							break;


		/////////////////////////////////////////////////////////////
		// ��� ���� ���� ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop)	{

									PROCESS.nRecoveryStep	= 0;
									PROCESS.nCurrentStep	= STEP_PAUSE;
								}

								break;


		/////////////////////////////////////////////////////////////
		// ��� �ʱ�ȭ ���� /////////////////////////////////////////
		case	STEP_MC_INIT	:
									PROCESS.nCurrentStep = 22020;
									break;

		case	22020	:
							if (!m_stSystemStatus.bOnMachineInitialize) {
							
								PROCESS.bIsOperatingStop		= FALSE;
								PROCESS.bOnMachineInitialize	= FALSE;
								PROCESS.nCurrentStep			= PROCESS.nRecoveryStep;
							}

							break;
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���� �ñ׳� ���� ////////////////////////////////////////
	if (bOnVisionTrigged && LTimerSignal.Verify()) {
	
		SetDOStatus(DO_OFF, DO_SIG_S02_VISION_TRIG);
		bOnVisionTrigged = FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���� üũ ///////////////////////////////////////////////
	CheckProcessOperatingStop(PROCESS);


	/////////////////////////////////////////////////////////////////
	// �Ϲ� /////////////////////////////////////////////////////////
	CheckProcessGeneral(nSTATION_NO, PROCESS);


	/////////////////////////////////////////////////////////////////
	// ���� ����͸� ////////////////////////////////////////////////
	if (LTimerSystemMonitor.Verify()) {

		if (PROCESS.nPrevStep != PROCESS.nCurrentStep) {

			PROCESS.nPrevStep = PROCESS.nCurrentStep;
			if (m_pSysMonitorDlg && m_pSysMonitorDlg->GetSafeHwnd()) {

				m_pSysMonitorDlg->PostMessage(UM_SYSM_UPDATE_STEP, PSTEP_PROC_MAIN_WORK_PROCEDURE, PROCESS.nCurrentStep);
				LTimerSystemMonitor.Start(DLY_REFRESH_SYSTEM_MONITOR);
			}
		}
	}


	return	PROCESS.pstErrorCode;
}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� : ���� �۾� (�Ϲ� �˻�) ///////////////////////////////////////////
PERROR_CODE_T CMainApp::ProcessMainWorkTest(void)
{
	static	PROCESS_CTRL_T		PROCESS;

	static	UINT				nSTATION_NO					= STATION_1;
	static	UINT				nSTATION_SUB_NO				= STN1_SUB_TEST;

			PBOOL				pOnSCP_MoveParts			= m_stSystemStatus.bOnSCP_MoveParts[nSTATION_NO];
	static	UINT				nSCP_PARTS_ID				= 0;
	
	static	BOOL				bResultProcess				= FALSE;
	
	static	PTPRD_DATA_T		pstWorkProcedureData		= NULL;
	static	FLKDMM_DATA_T		stMeasurementData;

	static	LTimerMsec			LTimerProceed;
	static	LTimerMsec			LTimerSteady;
	static	LTimerMsec			LTimerSteadyDMM;
	static	LTimerMsec			LTimerTimeOut;
	static	LTimerMsec			LTimerTimeOutProcess;
	static	LTimerMsec			LTimerInterval;
	static	LTimerMsec			LTimerSignal;
	static	LTimerMsec			LTimerMeasurement;
	static	LTimerMsec			LTimerSystemMonitor;
	static	LTimerMsec			LTimerSystemDisplay;
	static	LTimeHighResCounter	LCounterMeasurement;


	/////////////////////////////////////////////////////////////////
	// ���μ��� ������ �ʱ�ȭ ///////////////////////////////////////
	ProcessDataInitialize(PROCESS);


	/////////////////////////////////////////////////////////////////
	// �ڵ� ���� ����/���� �ʱ�ȭ ///////////////////////////////////
	if (CheckProcessOperating(PROCESS)) {
	
		m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]				= FALSE;
		m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
		m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
		m_stSystemStatus.bOnMainProcessOption01[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;
		m_stSystemStatus.bOnMainProcessOption02[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;
		m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
		m_stSystemStatus.bIsMainProcessInitialized[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;

		Motion_Stop_S(MOTION_RVX);
		Motion_Stop_S(MOTION_RVY);
		Motion_Stop_S(MOTION_RVZ);
	}


	/////////////////////////////////////////////////////////////////
	// ��� �ʱ�ȭ //////////////////////////////////////////////////
	if (CheckProcessMachineInitialize(PROCESS))
		return	NULL;


	/////////////////////////////////////////////////////////////////
	// ���� ���� ��� ///////////////////////////////////////////////
	PROCESS.bOnManualControlMode = m_stSystemStatus.bIsManualControl[nSTATION_NO];


	/////////////////////////////////////////////////////////////////
	// ���/�Ͻ� ���� ���� //////////////////////////////////////////
	if (CheckProcessEmergencyStop(PROCESS))					return	NULL;
	if (CheckProcessOperatingPause(nSTATION_NO, PROCESS))	return	NULL;


	/////////////////////////////////////////////////////////////////
	// ���� ���μ��� ////////////////////////////////////////////////
	switch (PROCESS.nCurrentStep) {

		case	0		:
							PROCESS.nCurrentStep = 10;
							break;

		// �ý��� üũ
		case	10		:
							if (IsSystemReady()) {
							
								PROCESS.nCurrentStep = 20;
							}
								
							break;

		// ���μ��� �ʱ�ȭ
		case	20		:
							m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]				= FALSE;
							m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
							m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
							m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
							m_stSystemStatus.bIsMainProcessInitialized[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;

							PROCESS.nCurrentStep = 90;
							break;

		// �Ϸ�
		case	90		:
							PROCESS.nCurrentStep = STEP_WORK_STANDBY;
							break;


		/////////////////////////////////////////////////////////////
		// �ʱ�ȭ ///////////////////////////////////////////////////
		case	STEP_WORK_INIT	:
									PROCESS.nCurrentStep = 110;
									break;

		// �÷��� �ʱ�ȭ
		case	110		:
							PROCESS.nCurrentStep = 130;
							break;

		// ���� ��ȣ �ʱ�ȭ
		case	130		:
							PROCESS.nCurrentStep = 190;
							break;

		// �Ϸ�
		case	190		:
							// �ʱ�ȭ �Ϸ� �÷��� ����
							m_stSystemStatus.bIsMainProcessInitialized[nSTATION_NO][nSTATION_SUB_NO] = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn01Step;
							break;


		/////////////////////////////////////////////////////////////
		// ��� /////////////////////////////////////////////////////
		case	STEP_WORK_STANDBY	:
										PROCESS.nCurrentStep = 220;
										break;

		// ���μ��� ���
		case	220		:
							if (m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO] ||
								m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]) {

								m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;
								m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;

								PROCESS.nCurrentStep = 230;
							}

							break;
							
		// �� �������� �ε�
		case	230		:
							PROCESS.pstModelProfile	= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
							PROCESS.pstWorkStatus	= GetWorkStatus(nSTATION_NO);

							if (PROCESS.pstModelProfile != NULL) {

								PROCESS.pstModelProfileConfig	= &((PROCESS.pstModelProfile)->stModelProfileConfig);
								PROCESS.pstWorkInfo				= &((PROCESS.pstModelProfileConfig)->stWorkInfo);
								
								PROCESS.nCurrentStep = 280;
								break;
							}

							SErrorMessage(TRUE, _T("[S%02d/%s] �� ������ �ε��� �� �����ϴ�."),	nSTATION_NO, 
																									g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

							PROCESS.nCurrentStep = STEP_WORK_ERROR_SYSTEM;
							break;

		// �ʱ�ȭ
		case	280		:
							PROCESS.nCurrentStep	= STEP_WORK_INIT;
							PROCESS.nReturn01Step	= 290;
							break;

		// �Ϸ�
		case	290		:
							PROCESS.nCurrentStep = STEP_WORK_START;
							break;


		/////////////////////////////////////////////////////////////
		// �۾� /////////////////////////////////////////////////////
		case	STEP_WORK_START	:
									PROCESS.nCurrentStep = 410;
									break;

		// �غ�
		case	410		:
							// �۾� ���� �ʱ�ȭ
							bResultProcess				= TRUE;
							PROCESS.nRetryCount			= 0;
							PROCESS.nResultInspection	= T_RESULT_SUCCESS;

							// ���ν��� ������ ����
							pstWorkProcedureData = &m_pstTestProcedureData[m_stSystemStatus.nCurrentWorkProcedureNo];

							PROCESS.nCurrentStep = 440;
							break;

		// �˻� ���� ����
		case	440		:
							LTimerSteady.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_DELAY]);
							
							PROCESS.nCurrentStep++;
							break;

		case	441		:
							if (LTimerSteady.Verify())
								PROCESS.nCurrentStep = 450;

							break;

		// �۾� �Ϸ� üũ
		case	450		:
							{
								BOOL	bIsStopProcess	= FALSE;

								// �۾� ����
								if (m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO])
									bIsStopProcess = TRUE;

								PROCESS.nCurrentStep = bIsStopProcess ? 490 : 460;
							}

							break;

		// �۾� ����
		case	460		:
							// �˻� �ð� ����
							LTimerTimeOutProcess.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_TIME]);

							// ���� ���� ���
							if (m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO]) {
							
								PROCESS.nCurrentStep  = STEP_WORK_SUB_TEST;
								PROCESS.nReturn01Step = 490;
								break;
							}

							// ���� ���� ���
							PROCESS.nCurrentStep  = STEP_WORK_SUB_TEST_EX;
							PROCESS.nReturn01Step = 490;
							break;

		// �Ϸ�
		case	490		:
							PROCESS.nCurrentStep = STEP_WORK_DONE;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� ////////////////////////////////////////////////
		case	STEP_WORK_SUB_TEST	:
										PROCESS.nCurrentStep = 2010;
										break;

		// �˻� �غ�
		case	2010	:
							{
								// ��� ���� ��� ����
								PROCESS.bOnAverageMeasurement = (BOOL)pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_USE_AVG];

								// ��� ���� ���
								if (PROCESS.bOnAverageMeasurement) {
								
									PROCESS.dblValueMeasurementSUM		= 0;
									PROCESS.nIndexAverageMeasurement	= 0;
								}

								PROCESS.nCurrentStep = 2050;
							}

							break;

		// ����
		case	2050	:
							if (LTimerSteadyDMM.Verify()) {

								DOUBLE	dblRange	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_DEV_RANGE];

								if (!m_devDMM.GetMeasurementValue(stMeasurementData, dblRange)) {

									ErrorMessage(TRUE, _T("������ ��Ƽ���Ͱ� �������� �ʽ��ϴ�."));
									PROCESS.nCurrentStep = STEP_WORK_ERROR_DEVICE;
									break;
								}	

								PROCESS.nCurrentStep = PROCESS.bOnAverageMeasurement ? 2051 : 2080;
							}

							break;

		case	2051	:
							{
								PROCESS.dblValueMeasurementSUM += stMeasurementData.dblMeasValue;
								PROCESS.nIndexAverageMeasurement++;

								if (LTimerTimeOutProcess.Verify()) {

									stMeasurementData.dblMeasValue = PROCESS.dblValueMeasurementSUM / (DOUBLE)PROCESS.nIndexAverageMeasurement;
									MessageWindow(cDEBUG, _T("[MEAS_AVG] %.2f / %d = %.2f"), PROCESS.dblValueMeasurementSUM, PROCESS.nIndexAverageMeasurement, stMeasurementData.dblMeasValue);

									PROCESS.nCurrentStep = 2080;
									break;
								}

								// ���� ���� ����
								LTimerSteadyDMM.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_INTV]);

								PROCESS.nCurrentStep--;
							}

							break;

		// ����
		case	2080	:
							{
								BOOL	bIsABS		= (BOOL)pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_USE_ABS];
								DOUBLE	dblGain		= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_GAIN];
								DOUBLE	dblOffset	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_OFFSET];
								DOUBLE	dblSpecMIN	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_SPEC_L];
								DOUBLE	dblSpecMAX	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_SPEC_H];
		
								PROCESS.dblValueRaw			= stMeasurementData.dblMeasValue;
								PROCESS.dblValueMeasurement	= (PROCESS.dblValueRaw * dblGain) + dblOffset;

								// ���밪 ����
								if (bIsABS)		PROCESS.dblValueMeasurement = abs(PROCESS.dblValueMeasurement);

								// �˻� ��� ����
								if (DPS_Round(PROCESS.dblValueMeasurement, 4) < DPS_Round(dblSpecMIN, 4) ||
									DPS_Round(PROCESS.dblValueMeasurement, 4) > DPS_Round(dblSpecMAX, 4))
										PROCESS.nResultInspection = T_RESULT_FAILURE;

								// �˻� ��� ����
								(PROCESS.pstWorkStatus)->stMeasSheet[0].dblRawValue			= PROCESS.dblValueRaw;
								(PROCESS.pstWorkStatus)->stMeasSheet[0].dblMeasurementValue	= PROCESS.dblValueMeasurement;
								(PROCESS.pstWorkStatus)->stMeasSheet[0].dblSpecMIN			= dblSpecMIN;
								(PROCESS.pstWorkStatus)->stMeasSheet[0].dblSpecMAX			= dblSpecMAX;
								(PROCESS.pstWorkStatus)->stMeasSheet[0].nResult				= PROCESS.nResultInspection;
								_tcscpy_s((PROCESS.pstWorkStatus)->stMeasSheet[0].szUnit, MAX_STRINPUT, pstWorkProcedureData->szValue[TPRD_DATA_VALUE_MEAS_UNIT]);

								PROCESS.nCurrentStep = 2090;
							}

							break;

		// �Ϸ�
		case	2090	:
							PROCESS.nCurrentStep = PROCESS.nReturn01Step;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� ////////////////////////////////////////////////
		case	STEP_WORK_SUB_TEST_EX	:
											PROCESS.nCurrentStep = 2110;
											break;

		// �˻� �غ�
		case	2110	:
							{
								// ���� ���� ������ �ʱ�ȭ
								m_arrContiMeasData.RemoveAll();

								// Ÿ�� ������ �ʱ�ȭ
								LCounterMeasurement.Reset();

								PROCESS.nCurrentStep = 2150;
							}

							break;

		// ����
		case	2150	:
							if (LTimerSteadyDMM.Verify()) {

								DOUBLE	dblRange	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_START_DEV_RANGE];

								if (!m_devDMM.GetMeasurementValue(stMeasurementData, dblRange)) {

									ErrorMessage(TRUE, _T("������ ��Ƽ���Ͱ� �������� �ʽ��ϴ�."));
									PROCESS.nCurrentStep = STEP_WORK_ERROR_DEVICE;
									break;
								}	

								PROCESS.nCurrentStep++;
							}

							break;

		case	2151	:
							{
								CONTI_MEAS_DATA_T	stMeasData;
								BOOL				bOnMeasStop		= FALSE;
								BOOL				bOnJudgeStopMIN	= (BOOL)pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_START_JUDGE_STOP_MIN];
								BOOL				bOnJudgeStopMAX	= (BOOL)pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_START_JUDGE_STOP_MAX];
								DOUBLE				dblValueJudge	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_START_JUDGE];
								DOUBLE				dblGain			= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_START_GAIN];
								DOUBLE				dblOffset		= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_START_OFFSET];


								PROCESS.dblValueRaw			= stMeasurementData.dblMeasValue;
								PROCESS.dblValueMeasurement	= (PROCESS.dblValueRaw * dblGain) + dblOffset;

								// �˻� ������ ����
								ZeroMemory(&stMeasData, sizeof(CONTI_MEAS_DATA_T));
								stMeasData.dblValue		= PROCESS.dblValueMeasurement;
								stMeasData.nTimeStamp	= LCounterMeasurement.GetCounterMsec();
								m_arrContiMeasData.Add(stMeasData);

								// ������ ���� (�ּҰ�)
								if (bOnJudgeStopMIN && PROCESS.dblValueMeasurement < dblValueJudge)
									bOnMeasStop = TRUE;

								// ������ ���� (�ִ밪)
								if (bOnJudgeStopMAX && PROCESS.dblValueMeasurement > dblValueJudge)
									bOnMeasStop = TRUE;

								// �˻� �ð� üũ
								if (bOnMeasStop || LTimerTimeOutProcess.Verify()) {

									stMeasurementData.dblMeasValue = PROCESS.dblValueMeasurementSUM / (DOUBLE)PROCESS.nIndexAverageMeasurement;
									MessageWindow(cDEBUG, _T("[MEAS_CONTI] Count = %d"), m_arrContiMeasData.GetCount());

									PROCESS.nCurrentStep = 2190;
									break;
								}

								// ���� ���� ����
								LTimerSteadyDMM.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_START_INTV]);

								PROCESS.nCurrentStep--;
							}

							break;

		// �Ϸ�
		case	2190	:
							PROCESS.nCurrentStep = PROCESS.nReturn01Step;
							break;


		/////////////////////////////////////////////////////////////
		// �Ϸ� /////////////////////////////////////////////////////
		case	STEP_WORK_DONE	:
									PROCESS.nCurrentStep = 590;
									break;

		// �Ϸ�
		case	590		:
							// ���� ���μ��� �Ϸ�
							m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;
							m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;
							m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]	= bResultProcess;

							PROCESS.nCurrentStep = STEP_WORK_STANDBY;
							break;


		/////////////////////////////////////////////////////////////
		// ���� /////////////////////////////////////////////////////
		case	STEP_WORK_ERROR	:
									PROCESS.bOnOperatingStop = TRUE;
									break;

		case	STEP_WORK_ERROR_PARTS	:
											PROCESS.bOnError				= TRUE;
											PROCESS.nRecoveryStep			= STEP_WORK_ERROR;
											PROCESS.stErrorCode.nErrorCode	= ERROR_MACHINE_SEQUENCE;
											PROCESS.stErrorCode.nProcessID	= PROCESS_MAIN_WORK_TEST;
											PROCESS.stErrorCode.nStationNo	= nSTATION_NO;

											// ����� �޼���
											SDebugMessage(TRUE, _T("[P%d:%d] ERROR PARTS"), nSTATION_NO, nSTATION_SUB_NO + 1);
											break;

		case	STEP_WORK_ERROR_SYSTEM	:
											// ����� �޼���
											SDebugMessage(TRUE, _T("[P%d:%d] ERROR SYSTEM"), nSTATION_NO, nSTATION_SUB_NO + 1);
											break;	

		case	STEP_WORK_ERROR_DEVICE	:
											// ����� �޼���
											SDebugMessage(TRUE, _T("[P%d:%d] ERROR DEVICE"), nSTATION_NO, nSTATION_SUB_NO + 1);

											// �޼��� ���
											ErrorMessage(TRUE, _T("[P%d] NO RESPONSE DEVICE"), nSTATION_NO);

											// ���μ��� �÷��� �ʱ�ȭ
											m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]				= FALSE;
											m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
											m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
											m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
											m_stSystemStatus.bIsMainProcessInitialized[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;

											PROCESS.nCurrentStep = STEP_WORK_STANDBY;
											break;	


		/////////////////////////////////////////////////////////////
		// �Ͻ� ���� ���� ///////////////////////////////////////////
		case	STEP_PAUSE	:
								if (m_stSystemStatus.bOnEmergencyStop) {

									PROCESS.nCurrentStep = STEP_EMG;
									break;
								}

								PROCESS.nCurrentStep++;
								break;

		case	20001	:
							if (!m_stSystemStatus.bOnPause && !m_stSystemStatus.bOnAlarmSystem && !m_stSystemStatus.bOnAlarmStation[nSTATION_NO]) {

								PROCESS.nCurrentStep = 20100;
							}

							break;

		// ���� ����
		case	20100	:
							PROCESS.nCurrentStep	= PROCESS.nRecoveryStep;
							PROCESS.bOnPause		= FALSE;
							break;


		/////////////////////////////////////////////////////////////
		// ��� ���� ���� ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop)	{

									PROCESS.nRecoveryStep	= 0;
									PROCESS.nCurrentStep	= STEP_PAUSE;
								}

								break;


		/////////////////////////////////////////////////////////////
		// ��� �ʱ�ȭ ���� /////////////////////////////////////////
		case	STEP_MC_INIT	:
									PROCESS.nCurrentStep = 22020;
									break;

		case	22020	:
							if (!m_stSystemStatus.bOnMachineInitialize) {
							
								PROCESS.bIsOperatingStop		= FALSE;
								PROCESS.bOnMachineInitialize	= FALSE;
								PROCESS.nCurrentStep			= PROCESS.nRecoveryStep;
							}

							break;
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���� üũ ///////////////////////////////////////////////
	CheckProcessOperatingStop(PROCESS);


	/////////////////////////////////////////////////////////////////
	// �Ϲ� /////////////////////////////////////////////////////////
	CheckProcessGeneral(nSTATION_NO, PROCESS);


	/////////////////////////////////////////////////////////////////
	// ���� ����͸� ////////////////////////////////////////////////
	if (LTimerSystemMonitor.Verify()) {

		if (PROCESS.nPrevStep != PROCESS.nCurrentStep) {

			PROCESS.nPrevStep = PROCESS.nCurrentStep;
			if (m_pSysMonitorDlg && m_pSysMonitorDlg->GetSafeHwnd()) {

				m_pSysMonitorDlg->PostMessage(UM_SYSM_UPDATE_STEP, PSTEP_PROC_MAIN_WORK_TEST, PROCESS.nCurrentStep);
				LTimerSystemMonitor.Start(DLY_REFRESH_SYSTEM_MONITOR);
			}
		}
	}


	return	PROCESS.pstErrorCode;
}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� : ���� �۾� (���� �˻�) ///////////////////////////////////////////
PERROR_CODE_T CMainApp::ProcessMainWorkVision(void)
{
	static	PROCESS_CTRL_T					PROCESS;

	static	UINT							nSTATION_NO				= STATION_1;
	static	UINT							nSTATION_SUB_NO			= STN1_SUB_VISION;
	static	UINT							nCHANNEL_NO				= 0;

			PBOOL							pOnSCP_MoveParts		= m_stSystemStatus.bOnSCP_MoveParts[nSTATION_NO];
	static	UINT							nSCP_PARTS_ID			= 0;

	static	BOOL							bResultProcess			= FALSE;

	static	UINT							nCurrentVisionCH		= VISION_CH1;
	static	UINT							nResultVision			= 0;
	static	UINT							nRetryOriginDetect		= 0;
	static	BOOL							bOnOriginDetectFailure	= FALSE;
	static	BOOL							bOnSaveVisionImage		= FALSE;

	static	DPS_RECT_T						stOriginDetectArea;
	static	VI_MODEL_T						stOriginDetectModel;
	static	DMW_USER_RECT_T					stRectInspection;

	static	PTPRD_DATA_T					pstWorkProcedureData	= NULL;
	static	PVPRD_DATA_T					pstVisionProcedureData	= NULL;
	static	VI_PARAM_THRESHOLD_T			stParamThreshold;
	static	VI_RESULT_THRESHOLD_T			stResultThreshold;
	static	VI_PARAM_THRESHOLD_LENGTH_T		stParamThresholdLength;
	static	VI_RESULT_THRESHOLD_LENGTH_T	stResultThresholdLength;
	static	VI_PARAM_PATTERN_T				stParamPatternMatch;
	static	VI_RESULT_PATTERN_T				stResultPatternMatch;
	static	VI_PARAM_MODEL_T				stParamModelFind;
	static	VI_RESULT_MODEL_T				stResultModelFind;
	static	VI_PARAM_COLOR_T				stParamColorAnalysis;
	static	VI_RESULT_COLOR_T				stResultColorAnalysis;

	static	BYTE							byReadByte				= 0;
	static	CHAR							szRcvdPacket[MAX_VISION_CHANNEL][COMM_PACKET_SIZE];
	static	UINT							nRcvdPacketIndex[MAX_VISION_CHANNEL];
	static	BOOL							bReceiveData[MAX_VISION_CHANNEL];

	static	LTimerMsec						LTimerProceed;
	static	LTimerMsec						LTimerAlarm;
	static	LTimerMsec						LTimerSensor;
	static	LTimerMsec						LTimerSteady;
	static	LTimerMsec						LTimerSteadyCAM;
	static	LTimerMsec						LTimerTimeOut;
	static	LTimerMsec						LTimerTimeOutProcess;
	static	LTimerMsec						LTimerWaitProduct;
	static	LTimerMsec						LTimerSystemMonitor;
	static	LTimerMsec						LTimerSystemDisplay;


	/////////////////////////////////////////////////////////////////
	// ���μ��� ������ �ʱ�ȭ ///////////////////////////////////////
	ProcessDataInitialize(PROCESS);


	/////////////////////////////////////////////////////////////////
	// �ڵ� ���� ����/���� �ʱ�ȭ ///////////////////////////////////
	if (CheckProcessOperating(PROCESS)) {
	
		m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]				= FALSE;
		m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
		m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
		m_stSystemStatus.bOnMainProcessOption01[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;
		m_stSystemStatus.bOnMainProcessOption02[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;
		m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
		m_stSystemStatus.bIsMainProcessInitialized[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;

		Motion_Stop_S(MOTION_RVX);
		Motion_Stop_S(MOTION_RVY);
		Motion_Stop_S(MOTION_RVZ);
	}


	/////////////////////////////////////////////////////////////////
	// ��� �ʱ�ȭ //////////////////////////////////////////////////
	if (CheckProcessMachineInitialize(PROCESS))
		return	NULL;


	/////////////////////////////////////////////////////////////////
	// ���� ���� ��� ///////////////////////////////////////////////
	PROCESS.bOnManualControlMode = m_stSystemStatus.bIsManualControl[nSTATION_NO];


	/////////////////////////////////////////////////////////////////
	// ���/�Ͻ� ���� ���� //////////////////////////////////////////
	if (CheckProcessEmergencyStop(PROCESS))					return	NULL;
	if (CheckProcessOperatingPause(nSTATION_NO, PROCESS))	return	NULL;


	/////////////////////////////////////////////////////////////////
	// ���� ���μ��� ////////////////////////////////////////////////
	switch (PROCESS.nCurrentStep) {

		case	0		:
							PROCESS.nCurrentStep = 10;
							break;

		// �ý��� üũ
		case	10		:
							if (IsSystemReady()) {
							
								PROCESS.nCurrentStep = 20;
							}
								
							break;

		// ���μ��� �ʱ�ȭ
		case	20		:
							m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]				= FALSE;
							m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
							m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
							m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
							m_stSystemStatus.bIsMainProcessInitialized[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;

							PROCESS.nCurrentStep = 90;
							break;

		// �Ϸ�
		case	90		:
							PROCESS.nCurrentStep = STEP_WORK_STANDBY;
							break;


		/////////////////////////////////////////////////////////////
		// �ʱ�ȭ ///////////////////////////////////////////////////
		case	STEP_WORK_INIT	:
									PROCESS.nCurrentStep = 110;
									break;

		// �÷��� �ʱ�ȭ
		case	110		:
							PROCESS.nCurrentStep = 190;
							break;

		// �Ϸ�
		case	190		:
							// �ʱ�ȭ �Ϸ� �÷��� ����
							m_stSystemStatus.bIsMainProcessInitialized[nSTATION_NO][nSTATION_SUB_NO] = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn01Step;
							break;


		/////////////////////////////////////////////////////////////
		// ��� /////////////////////////////////////////////////////
		case	STEP_WORK_STANDBY	:
										PROCESS.nCurrentStep = 220;
										break;

		// ���μ��� ���
		case	220		:
							if (m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO] ||
								m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]) {

								m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;
								m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;

								PROCESS.nCurrentStep = 230;
							}

							break;
							
		// �� �������� �ε�
		case	230		:
							if (PROCESS.bOnManualControlMode)	PROCESS.pstModelProfile = (PMODEL_PROFILE_T)m_stSystemStatus.pstMC_ModelProfile;
							else								PROCESS.pstModelProfile	= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
							
							PROCESS.pstWorkStatus = GetWorkStatus(nSTATION_NO);

							if (PROCESS.pstModelProfile != NULL) {

								PROCESS.pstModelProfileConfig	= &(PROCESS.pstModelProfile)->stModelProfileConfig;
								PROCESS.pstWorkInfo				= &(PROCESS.pstModelProfileConfig)->stWorkInfo;
								PROCESS.pstStationSetupInfo		= (LPVOID)&(PROCESS.pstModelProfileConfig)->stSpVisionSetupInfo;
						
								PROCESS.pstTestSetupInfo		= ((PSP_WI_VISION_SETUP_T)PROCESS.pstStationSetupInfo)->stTestItemSetupInfo;
								PROCESS.nNumWorkSheetItem		= ((PSP_WI_VISION_SETUP_T)PROCESS.pstStationSetupInfo)->nNumTestSheetItem;

								PROCESS.nCurrentStep = 280;
								break;
							}

							SErrorMessage(TRUE, _T("[S%02d/%s] �� ������ �ε��� �� �����ϴ�."),	nSTATION_NO, 
																									g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

							PROCESS.nCurrentStep = STEP_WORK_ERROR_SYSTEM;
							break;

		// �ʱ�ȭ
		case	280		:
							PROCESS.nCurrentStep	= STEP_WORK_INIT;
							PROCESS.nReturn01Step	= 290;
							break;

		// �Ϸ�
		case	290		:
							PROCESS.nCurrentStep = STEP_WORK_START;
							break;


		/////////////////////////////////////////////////////////////
		// �۾� /////////////////////////////////////////////////////
		case	STEP_WORK_START	:
									PROCESS.nCurrentStep = 410;
									break;

		// �غ�
		case	410		:
							// �۾� ���� �ʱ�ȭ
							PROCESS.nRetryCount			= 0;
							PROCESS.nCurrentWorkSheetNo	= m_stSystemStatus.nMainProcessWorkIndex[nSTATION_NO][nSTATION_SUB_NO];
							PROCESS.nUpdateWorkSheetNo	= m_stSystemStatus.nCurrentVisionWorkSheetUpdateNo;
							PROCESS.bOnRetryInspection	= FALSE;
							bResultProcess				= TRUE;

							// �۾� ���ν��� ������ ����
							pstWorkProcedureData = &m_pstTestProcedureData[m_stSystemStatus.nCurrentWorkProcedureNo];

							// �˻� �ð� ����
							LTimerTimeOutProcess.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_VISION_01_TIME]);

							PROCESS.nCurrentStep = 450;
							break;

		// �۾� �Ϸ� üũ
		case	450		:
							{
								BOOL	bIsStopProcess	= FALSE;

								// �۾� ����
								if (m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO])
									bIsStopProcess = TRUE;

								// �۾� �Ϸ�
								if (PROCESS.nCurrentWorkSheetNo >= PROCESS.nNumWorkSheetItem) {

									bResultProcess = FALSE;

									PROCESS.nCurrentStep = 490;
									break;
								}

								PROCESS.nCurrentStep = bIsStopProcess ? 480 : 460;
							}

							break;

		// 1 ���� �۾�
		case	460		:
							PROCESS.nCurrentStep	= STEP_WORK_CYCLE;
							PROCESS.nReturn01Step	= 461;
							break;

		case	461		:
							PROCESS.nCurrentStep = 470;
							break;

		// �˻� ��� üũ
		case	470		:
							// ���� �˻� ����̰�, ���հ� ������ ��� ��˻�
							if (m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO] && !bResultProcess && !LTimerTimeOutProcess.Verify()) {
							
								// �÷��� �ʱ�ȭ
								bResultProcess				= TRUE;
								PROCESS.bOnRetryInspection	= TRUE;

								// �˻� ���� ����
								LTimerProceed.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_VISION_01_INTV]);

								PROCESS.nCurrentStep++;
								break;
							}

							// ���հ� ���� �� ���� �˻� �̹��� ����
							if (m_SystemConfig.UseSystemOption(SOPT_SAVE_VISION_IMAGE_NG) && !bResultProcess)
								SaveVisionImage(PROCESS.nCurrentWorkSheetNo, FALSE);

							// ���� ���� �˻� �۾� ��Ʈ ������Ʈ ��ȣ ����
							m_stSystemStatus.nCurrentVisionWorkSheetUpdateNo = ++PROCESS.nUpdateWorkSheetNo;

							PROCESS.nCurrentStep = 480;
							break;

		case	471		:
							if (LTimerProceed.Verify())
								PROCESS.nCurrentStep = 460;

							break;

		// ...?
		case	480		:
							PROCESS.nCurrentStep = 490;
							break;

		// �Ϸ�
		case	490		:
							PROCESS.nCurrentStep = STEP_WORK_DONE;
							break;


		/////////////////////////////////////////////////////////////
		// �Ϸ� /////////////////////////////////////////////////////
		case	STEP_WORK_DONE	:
									PROCESS.nCurrentStep = 590;
									break;

		// �Ϸ�
		case	590		:
							// ���� ���μ��� �Ϸ�
							m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;
							m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;
							m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]	= bResultProcess;

							PROCESS.nCurrentStep = STEP_WORK_STANDBY;
							break;


		/////////////////////////////////////////////////////////////
		// 1 ���� �۾� //////////////////////////////////////////////
		case	STEP_WORK_CYCLE	:
									PROCESS.nCurrentStep = 1010;
									break;

		case	1010	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							// 1 ���� �÷��� ����
							PROCESS.bOnProcessCycle = TRUE;

							// �÷��� �ʱ�ȭ
							PROCESS.nRetryCount			= 0;
							PROCESS.nResultInspection	= T_RESULT_SUCCESS;
														
							PROCESS.nCurrentStep = 1100;
							break;

		// �˻� ���Ǻ� �б�
		case	1100	:
							{
								if (PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].bUseTest) {

									PROCESS.bOnUpdateWorkSheet = TRUE;
									switch (PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].nTestSheetItem) {

										case	TSI1_VISION	:	PROCESS.nCurrentStep = STEP_WORK_SUB_TSI_VISION;	break;
										default				:
																PROCESS.nCurrentStep = 1900;
																PROCESS.bOnUpdateWorkSheet = FALSE;
																break;
									}

									// ������Ʈ UI
									if (PROCESS.bOnUpdateWorkSheet) {

										PROCESS.bOnUpdateUI								= TRUE;
										PROCESS.stParamUI.nUpdateID						= UI_WORK_SHEET_02;
										PROCESS.stParamUI.nStationNo					= nSTATION_NO;
										PROCESS.stParamUI.stWorkSheet.nWorkPosition		= PROCESS.nCurrentWorkSheetNo;
										PROCESS.stParamUI.stWorkSheet.nUpdatePosition	= PROCESS.nUpdateWorkSheetNo;
										PROCESS.stParamUI.stWorkSheet.nWorkStatus		= WORK_STATE_TESTING;
										PROCESS.stParamUI.stWorkSheet.bOnUpdate			= PROCESS.bOnRetryInspection;
									}

									PROCESS.nReturn02Step = 1900;
									break;
								}

								PROCESS.nCurrentStep = 1990;
							}

							break;

		// �Ϸ�
		case	1900	:
							// ���μ��� ��� ����
							bResultProcess &= PROCESS.nResultInspection == T_RESULT_SUCCESS ? TRUE : FALSE;

							// �۾� ���� ���� ����
							(PROCESS.pstWorkStatus)->stMeasSheet[PROCESS.nCurrentWorkSheetNo].nResult = PROCESS.nResultInspection;
							MessageWindow(cDEBUG, _T("VISION_%02d = %d"), PROCESS.nCurrentWorkSheetNo, PROCESS.nResultInspection);

							// ������Ʈ UI
							if (PROCESS.bOnUpdateWorkSheet) {

								PROCESS.bOnUpdateWorkSheet						= FALSE;
								PROCESS.bOnUpdateUI								= TRUE;
								PROCESS.stParamUI.nUpdateID						= UI_WORK_SHEET_02;
								PROCESS.stParamUI.nStationNo					= nSTATION_NO;
								PROCESS.stParamUI.stWorkSheet.nWorkPosition		= PROCESS.nCurrentWorkSheetNo;
								PROCESS.stParamUI.stWorkSheet.nUpdatePosition	= PROCESS.nUpdateWorkSheetNo;
								PROCESS.stParamUI.stWorkSheet.nWorkStatus		= WORK_STATE_COMPLETE;
								PROCESS.stParamUI.stWorkSheet.bOnUpdate			= TRUE;
							}

							PROCESS.nCurrentStep = 1990;
							break;

		case	1990	:
							// 1 ���� �÷��� ����
							PROCESS.bOnProcessCycle = FALSE;

							PROCESS.nCurrentStep = PROCESS.nReturn01Step;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� : �˻� �׸� - ���� �˻� ////////////////////////
		case	STEP_WORK_SUB_TSI_VISION	:
												PROCESS.nCurrentStep = 2010;
												break;

		// �ʱ�ȭ
		case	2010	:
							// ������Ʈ UI
							PROCESS.bOnUpdateUI						= TRUE;
							PROCESS.stParamUI.nUpdateID				= UI_VISION_SHEET;
							PROCESS.stParamUI.nStationNo			= nSTATION_NO;
							PROCESS.stParamUI.stWorkSheet.bOnClear	= TRUE;

							// ���� ���� ���� �ʱ�ȭ
							ZeroMemory(&m_stSystemStatus.stVisionOriginOffset, sizeof(DPS_POINT2D_T));

							// ���� �̹��� ������ �ʱ�ȭ
							if (m_pMainWnd)	{
								
								m_stSystemStatus.bIsVisionImageWindowCleared = FALSE;
								m_pMainWnd->PostMessage(UM_VISION_CLEAR_IMAGE);
							}

							// �÷��� �ʱ�ȭ
							PROCESS.bOnRetryInspection	= FALSE;
							bOnOriginDetectFailure		= FALSE;
							bOnSaveVisionImage			= TRUE;
							nCurrentVisionCH			= VISION_CH1;
							m_stSystemStatus.nCurrentVisionInspectionNo = 0;

							PROCESS.nCurrentStep = m_SystemConfig.IsSimulationMode() ? 2050 : 2020;
							break;

		// �˻� �غ�
		case	2020	:
							// ī�޶� ���� ����
							if (!m_SystemConfig.IsSimulationMode()) {

								UINT	nValueExposure	= PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].nValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_CAMERA_SPEED];

								SetVisionCameraExposure(nCurrentVisionCH, nValueExposure);
								MessageWindow(cDEBUG, _T("SET EXPOSURE = %d"), nValueExposure);
								
								nRcvdPacketIndex[nCurrentVisionCH]	= 0;
								bReceiveData[nCurrentVisionCH]		= FALSE;
								LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_VISION_CAMERA));								
							}

							// ���� �̵� ���
							if (pstWorkProcedureData->nValue[TPRD_DATA_VALUE_VISION_01_MOVE_MODE]) {
							
								PROCESS.nCurrentStep = 2030;
								break;
							}

							PROCESS.nCurrentStep++;
							break;

		case	2021	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							// VZ ��� ��ġ �̵�
							if (Motion_Done(MOTION_RVZ)) {

								Motion_MoveTo(MOTION_RVZ, m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME], m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}											

							break;

		case	2022	:
							// �۾� ��ġ �̵� Ȯ��
							if (Motion_Done(MOTION_RVZ)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME];
								if (!Motion_CheckStopStatus(MOTION_RVZ, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVZ;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_WORK_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep++;
							}

							break;

		case	2023	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							// VX, VY �۾� ��ġ �̵�
							if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVY)) {

								Motion_Move2X(0, MOTION_RVX, MOTION_RVY,
											  PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_POSITION_1],
											  PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_POSITION_2],
											  m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}											

							break;

		case	2024	:
							// �۾� ��ġ �̵� Ȯ��
							if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVY)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_POSITION_1];
								if (!Motion_CheckStopStatus(MOTION_RVX, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVX;
								}

								dblPosition = PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_POSITION_2];
								if (!Motion_CheckStopStatus(MOTION_RVY, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVY;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_WORK_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep++;
							}

							break;

		case	2025	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							// VZ �۾� ��ġ �̵�
							if (Motion_Done(MOTION_RVZ)) {

								DOUBLE	dblPosition	= PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_POSITION_3];

								Motion_MoveTo(MOTION_RVZ, dblPosition, m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}											

							break;

		case	2026	:
							// �۾� ��ġ �̵� Ȯ��
							if (Motion_Done(MOTION_RVZ)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_POSITION_3];
								if (!Motion_CheckStopStatus(MOTION_RVZ, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVZ;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_WORK_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 2040;
							}

							break;

		case	2030	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							// VX, VY, VZ �۾� ��ġ ���� �̵�
							if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVY) && Motion_Done(MOTION_RVZ)) {

								Motion_Move3X(MCOORD_S01, MOTION_RVZ, MOTION_RVX, MOTION_RVY, 
											  PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_POSITION_3],
											  PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_POSITION_1],
											  PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_POSITION_2],
											  m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}											

							break;

		case	2031	:
							// �۾� ��ġ �̵� Ȯ��
							if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVY) && Motion_Done(MOTION_RVZ)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_POSITION_1];
								if (!Motion_CheckStopStatus(MOTION_RVX, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVX;
								}

								dblPosition = PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_POSITION_2];
								if (!Motion_CheckStopStatus(MOTION_RVY, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVY;
								}

								dblPosition = PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_POSITION_3];
								if (!Motion_CheckStopStatus(MOTION_RVZ, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVZ;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_WORK_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 2040;
							}

							break;

		// �غ� �Ϸ� üũ
		case	2040	:
							// ���� ī�޶� ���� Ȯ��
							if (m_SystemConfig.IsSimulationMode() || bReceiveData[nCurrentVisionCH]) {
							
								PROCESS.nCurrentStep = 2050;
								break;
							}

							// Ÿ�� �ƿ�
							if (LTimerTimeOut.Verify()) {
							
								PROCESS.nCurrentStep = STEP_WORK_ERROR_DEVICE;
							}

							break;

		// ���� ���ν��� �ε�
		case	2050	:
							{
								if (!LoadVisionProcedure(PROCESS.nCurrentWorkSheetNo)) {
								
									ErrorMessage(TRUE, _T("���� �˻� ���ν��� [%d]�� �ҷ��� �� �����ϴ�."), PROCESS.nCurrentWorkSheetNo);
									PROCESS.nCurrentStep = STEP_WORK_ERROR_SYSTEM;
									break;
								}

								PROCESS.nCurrentStep = 2060;
							}

							break;

		// �˻� ���� ����
		case	2060	:
							LTimerSteady.Start(PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].nValue[TSI_VALUE_COMMON_DELAY]);

							PROCESS.nCurrentStep++;
							break;

		case	2061	:
							if (LTimerSteady.Verify())
								PROCESS.nCurrentStep = 2100;

							break;

		// ī�޶� ���� ĸ��
		case	2100	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (LTimerSteadyCAM.Verify() && m_stSystemStatus.bIsVisionImageWindowCleared) {

								if (m_SystemConfig.IsSimulationMode()) {

									if (m_MilImageInspection[PROCESS.nCurrentWorkSheetNo] != M_NULL) {

										MbufFree(m_MilImageInspection[PROCESS.nCurrentWorkSheetNo]);
										m_MilImageInspection[PROCESS.nCurrentWorkSheetNo] = M_NULL;
									}

									MbufImport((MIL_TEXT_CHAR*)m_stVisionProcedureHeader.szFileLastLoadedImage, M_DEFAULT, M_RESTORE, m_MilSystem, &m_MilImageInspection[PROCESS.nCurrentWorkSheetNo]);

								} else {

									if (!GrabVisionImage(nCurrentVisionCH, PROCESS.nCurrentWorkSheetNo)) {

										SErrorMessage(TRUE, _T("���� ī�޶� [%d] �̹����� ������ �� �����ϴ�."), nCurrentVisionCH + 1);

										PROCESS.nResultInspection = T_RESULT_ERROR;
										PROCESS.nCurrentStep = 2190;
										break;
									}

									// ���� �˻� �̹��� ����
									if (bOnSaveVisionImage) {

										if (m_SystemConfig.UseSystemOption(SOPT_SAVE_VISION_IMAGE))			SaveVisionImage(PROCESS.nCurrentWorkSheetNo, FALSE);
										if (m_SystemConfig.UseSystemOption(SOPT_SAVE_VISION_IMAGE_JPEG))	SaveVisionImage(PROCESS.nCurrentWorkSheetNo, FALSE, TRUE);

										// ������ �̹��� ��� ����
										SaveVisionImage(PROCESS.nCurrentWorkSheetNo, FALSE, FALSE, TRUE);
									}
								}

								PROCESS.nCurrentStep++;
							}

							break;

		case	2101	:
							// �̹��� �����쿡 �ε�
							if (m_pMainWnd)	m_pMainWnd->SendMessage(UM_VISION_LOAD_IMAGE, nCurrentVisionCH, (LPARAM)m_MilImageInspection[PROCESS.nCurrentWorkSheetNo]);

							// ���� ĸ�� �Ϸ� �÷��� ����
							m_stSystemStatus.bIsVisionCaptureComplete[nCurrentVisionCH] = TRUE;

							PROCESS.nCurrentStep = 2110;
							break;

		// ���� �˻� ����
		case	2110	:
							{
								VISION_TEST_DATA_T stVisionTestData;

								if (m_pstVisionProcedureData[m_stSystemStatus.nCurrentVisionInspectionNo].bUsePoint) {
							
									if (!PROCESS.bOnRetryInspection) {

										PROCESS.nCurrentStep++;
										break;
								
									} else {

										// �հ� ����Ʈ�� �ƴϸ� �˻� ����
										stVisionTestData = m_arrVisionTestData[PROCESS.nCurrentWorkSheetNo].GetAt(m_stSystemStatus.nCurrentVisionInspectionNo);
										if (stVisionTestData.nResult != T_RESULT_SUCCESS) {

											PROCESS.nCurrentStep++;
											break;
										}
									}
								
								} else {

									if (!PROCESS.bOnRetryInspection) {

										ZeroMemory(&stVisionTestData, sizeof(VISION_TEST_DATA_T));
										m_arrVisionTestData[PROCESS.nCurrentWorkSheetNo].Add(stVisionTestData);
									}
								}
							}

							PROCESS.nCurrentStep = 2120;
							break;

		case	2111	:
							PROCESS.nCurrentStep	= STEP_WORK_SUB_TSI_VISION_EX;
							PROCESS.nReturn03Step	= 2120;
							break;
							
		// �˻� �׸� ����
		case	2120	:
							if (++m_stSystemStatus.nCurrentVisionInspectionNo >= m_stVisionProcedureHeader.nNumProcedureData) {

								// ���� �̹��� ������ ������Ʈ
								if (m_pMilImageWnd)	m_pMilImageWnd->SendMessage(UM_DPS_MIL_WND_IMAGE_UPDATE_WINDOW);
							
								PROCESS.nCurrentStep = 2130;
								break;
							}

							// ���� ���� ���� ��
							if (bOnOriginDetectFailure) {
							
								PROCESS.nCurrentStep = 2130;
								break;
							}

							PROCESS.nCurrentStep = 2110;
							break;

		// ���հ� ���� �� ��˻�
		case	2130	:
							if (m_SystemConfig.UseSystemOption(SOPT_RETRY_WORK_NG) && !PROCESS.bOnManualControlMode) {

								if (PROCESS.nResultInspection != T_RESULT_SUCCESS) {

									// �÷��� ����
									PROCESS.bOnRetryInspection	= TRUE;
									bOnSaveVisionImage			= bOnOriginDetectFailure;
									bOnOriginDetectFailure		= FALSE;
									m_stSystemStatus.nCurrentVisionInspectionNo	= 0;

									// ��õ� ī��Ʈ üũ
									if (++PROCESS.nRetryCount >= m_SystemConfig.GetWorkRetryCount()) {

										PROCESS.nCurrentStep = 2180;
										break;
									}

									// �÷��� �ʱ�ȭ
									PROCESS.nResultInspection = T_RESULT_SUCCESS;

									// ������Ʈ
									PROCESS.bOnUpdateUI						= TRUE;
									PROCESS.stParamUI.nUpdateID				= UI_VISION_SHEET;
									PROCESS.stParamUI.nStationNo			= nSTATION_NO;
									PROCESS.stParamUI.stWorkSheet.bOnClear	= TRUE;

									// ���� �̹��� ĸ�� ����ȭ �ð�
									LTimerSteadyCAM.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_GRAB_IMAGE));

									PROCESS.nCurrentStep = 2100;
									break;
								}
							}

							PROCESS.nCurrentStep = 2180;
							break;

		case	2180	:  
							PROCESS.nCurrentStep = 2190;
							break;

		// �Ϸ�
		case	2190	:
							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// ���� ���� : ���� �˻� ////////////////////////////////////
		case	STEP_WORK_SUB_TSI_VISION_EX	:
												PROCESS.nCurrentStep = 3010;
												break;

		// �غ� �۾�
		case	3010	:
							// �÷��� �ʱ�ȭ
							nResultVision		= T_RESULT_SUCCESS;
							nRetryOriginDetect	= 0;
							ZeroMemory(&stRectInspection, sizeof(DMW_USER_RECT_T));

							// ���ν��� ������ ����
							pstVisionProcedureData = &m_pstVisionProcedureData[m_stSystemStatus.nCurrentVisionInspectionNo];

							PROCESS.nCurrentStep = 3100;
							break;

		// �˻� ��� : THRESHOLD
		case	3100	:
							if (pstVisionProcedureData->nInspectionMode == VI_MODE_THRESHOLD) {
							
								if (pstVisionProcedureData->nNumberOfVisionRegion) {

									// �Ķ���� ����
									ZeroMemory(&stParamThreshold, sizeof(VI_PARAM_THRESHOLD_T));
									stParamThreshold.MilImageInspection		= m_MilImageInspection[PROCESS.nCurrentWorkSheetNo];
									stParamThreshold.rectInspectionArea		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo;
									stParamThreshold.stInspectionInfo		= pstVisionProcedureData->stInspection_Threshold;
									stParamThreshold.bUseReverseJudgement	= pstVisionProcedureData->bOptions[VOPT_REVERSE_JUDGEMENT];

									// �̹��� ���μ��� ����
									ProcessImage_Threshold(	PROCESS.nCurrentWorkSheetNo, 
															nSTATION_NO, 
															m_stSystemStatus.stVisionOriginOffset,
															stParamThreshold, 
															stResultThreshold);

									nResultVision = stResultThreshold.nResultInspection;
								}

								PROCESS.nCurrentStep = 3180;
								break;
							}

							PROCESS.nCurrentStep = 3110;
							break;

		// �˻� ��� : ���� ���� (THRESHOLD)
		case	3110	:
							if (pstVisionProcedureData->nInspectionMode == VI_MODE_THRESHOLD_LENGTH) {
							
								if (pstVisionProcedureData->nNumberOfVisionRegion) {

									// �Ķ���� ����
									ZeroMemory(&stParamThresholdLength, sizeof(VI_PARAM_THRESHOLD_LENGTH_T));
									stParamThresholdLength.MilImageInspection				= m_MilImageInspection[PROCESS.nCurrentWorkSheetNo];
									stParamThresholdLength.rectInspectionArea[VI_THL_P1]	= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo;
									stParamThresholdLength.rectInspectionArea[VI_THL_P2]	= pstVisionProcedureData->stVisionRegionInfo[1].stRegionInfo;
									stParamThresholdLength.stInspectionInfo					= pstVisionProcedureData->stInspection_ThresholdLength;
									stParamThresholdLength.dblGainLength					= m_SystemConfig.GetVisionLengthGain(nCurrentVisionCH);
									stParamThresholdLength.bUseReverseJudgement				= pstVisionProcedureData->bOptions[VOPT_REVERSE_JUDGEMENT];

									// �̹��� ���μ��� ����
									ProcessImage_ThresholdLength(	PROCESS.nCurrentWorkSheetNo, 
																	nSTATION_NO, 
																	m_stSystemStatus.stVisionOriginOffset,
																	stParamThresholdLength, 
																	stResultThresholdLength);

									nResultVision = stResultThresholdLength.nResultInspection;

									// ���� ���� ����Ʈ
									if (pstVisionProcedureData->bOptions[VOPT_ORIGIN_POINT]) {
								
										if (nResultVision == T_RESULT_SUCCESS) {

											switch (stParamThresholdLength.stInspectionInfo.nModeOriginDetect) {
									
												case	VI_ORG_MODE_X	:
														{
															m_stSystemStatus.stVisionOriginOffset.dblX	= stResultThresholdLength.dblMeasurement - stParamThresholdLength.stInspectionInfo.dblOriginOffset;
														}

														break;

												case	VI_ORG_MODE_Y	:
														{
															m_stSystemStatus.stVisionOriginOffset.dblY	= stResultThresholdLength.dblMeasurement - stParamThresholdLength.stInspectionInfo.dblOriginOffset;
														}

														break;
											}

											// ����� �޼���
											MessageWindow(cDEBUG, _T("[P:%02d] ���� ���� = x%.2f, y%.2f, a%.2f"),	m_stSystemStatus.nCurrentVisionInspectionNo + 1,
																													m_stSystemStatus.stVisionOriginOffset.dblX,
																													m_stSystemStatus.stVisionOriginOffset.dblY,
																													m_stSystemStatus.stVisionOriginOffset.dblAngle);
										}
									}
								}

								PROCESS.nCurrentStep = 3180;
								break;
							}

							PROCESS.nCurrentStep = 3120;
							break;

		// �˻� ��� : ���� ��Ī
		case	3120	:
							if (pstVisionProcedureData->nInspectionMode == VI_MODE_PATTERN) {

								if (pstVisionProcedureData->nNumberOfVisionRegion) {

									// �Ķ���� ����
									ZeroMemory(&stParamPatternMatch, sizeof(VI_PARAM_PATTERN_T));
									stParamPatternMatch.MilImageInspection		= m_MilImageInspection[PROCESS.nCurrentWorkSheetNo];
									stParamPatternMatch.rectInspectionArea		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo;
									stParamPatternMatch.stInspectionInfo		= pstVisionProcedureData->stInspection_PatternMatch;
									stParamPatternMatch.bUseReverseJudgement	= pstVisionProcedureData->bOptions[VOPT_REVERSE_JUDGEMENT];
									_stprintf_s(stParamPatternMatch.szFileOriginImage, MAX_STRFILE_M, _T("%s"), m_stVisionProcedureHeader.szFileOriginImage);

									// �̹��� ���μ��� ����
									ProcessImage_PatternMatch(	PROCESS.nCurrentWorkSheetNo, 
																nSTATION_NO, 
																m_stSystemStatus.stVisionOriginOffset,
																stParamPatternMatch, 
																stResultPatternMatch);

									nResultVision = stResultPatternMatch.nResultInspection;

									// ���� ���� ����Ʈ
									if (pstVisionProcedureData->bOptions[VOPT_ORIGIN_POINT]) {

										if (nResultVision == T_RESULT_SUCCESS) {

											switch (stParamPatternMatch.stInspectionInfo.nModeOriginDetect) {

												case	VI_ORG_MODE_XY	:
														{
															m_stSystemStatus.stVisionOriginOffset.dblX	= stResultPatternMatch.flOffset.x;
															m_stSystemStatus.stVisionOriginOffset.dblY	= stResultPatternMatch.flOffset.y;										
														}

														break;
									
												case	VI_ORG_MODE_X	:
														{
															m_stSystemStatus.stVisionOriginOffset.dblX	= stResultPatternMatch.flOffset.x;
														}

														break;

												case	VI_ORG_MODE_Y	:
														{
															m_stSystemStatus.stVisionOriginOffset.dblY	= stResultPatternMatch.flOffset.y;
														}

														break;
											}

											m_stSystemStatus.stVisionOriginOffset.dblAngle	= stResultPatternMatch.dblAngle;

											// ����� �޼���
											MessageWindow(cDEBUG, _T("[P:%02d] ���� ���� = x%.2f, y%.2f, a%.2f"),	m_stSystemStatus.nCurrentVisionInspectionNo + 1,
																													m_stSystemStatus.stVisionOriginOffset.dblX,
																													m_stSystemStatus.stVisionOriginOffset.dblY,
																													m_stSystemStatus.stVisionOriginOffset.dblAngle);
										}
									}
								}

								PROCESS.nCurrentStep = 3180;
								break;
							}

							PROCESS.nCurrentStep = 3130;
							break;

		// �˻� ��� : �� �˻�
		case	3130	:
							if (pstVisionProcedureData->nInspectionMode == VI_MODE_MODEL_FINDER) {

								if (pstVisionProcedureData->nNumberOfVisionRegion) {

									// �˻� ���� ����
									if (!pstVisionProcedureData->bOptions[VOPT_ORIGIN_POINT] ||
										(pstVisionProcedureData->bOptions[VOPT_ORIGIN_POINT] && !nRetryOriginDetect)) {

										stOriginDetectArea  = pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo;
										stOriginDetectModel = pstVisionProcedureData->stInspection_ModelFind;
									}

									// �Ķ���� ����
									ZeroMemory(&stParamModelFind, sizeof(VI_PARAM_MODEL_T));
									stParamModelFind.MilImageInspection			= m_MilImageInspection[PROCESS.nCurrentWorkSheetNo];
									stParamModelFind.rectInspectionArea			= stOriginDetectArea;
									stParamModelFind.stInspectionInfo			= stOriginDetectModel;
									stParamModelFind.stThresholdInfo			= pstVisionProcedureData->stInspection_Threshold;
									stParamModelFind.bUseReverseJudgement		= pstVisionProcedureData->bOptions[VOPT_REVERSE_JUDGEMENT];
									stParamModelFind.bUseRecursiveMeasurement	= pstVisionProcedureData->bOptions[VOPT_RECURSIVE_MEASUREMENT];
									_stprintf_s(stParamModelFind.szFileOriginImage, MAX_STRFILE_M, _T("%s"), m_stVisionProcedureHeader.szFileOriginImage);

									// �̹��� ���μ��� ����
									ProcessImage_ModelFind(	PROCESS.nCurrentWorkSheetNo, 
															nSTATION_NO, 
															m_stSystemStatus.stVisionOriginOffset,
															stParamModelFind, 
															stResultModelFind);

									nResultVision = stResultModelFind.nResultInspection;

									// ���� ���� ����Ʈ
									if (pstVisionProcedureData->bOptions[VOPT_ORIGIN_POINT]) {

										if (nResultVision == T_RESULT_SUCCESS) {

											switch (stParamModelFind.stInspectionInfo.nModeOriginDetect) {

												case	VI_ORG_MODE_XY	:
														{
															m_stSystemStatus.stVisionOriginOffset.dblX	= stResultModelFind.flOffset.x;
															m_stSystemStatus.stVisionOriginOffset.dblY	= stResultModelFind.flOffset.y;
														}

														break;
									
												case	VI_ORG_MODE_X	:
														{
															m_stSystemStatus.stVisionOriginOffset.dblX	= stResultModelFind.flOffset.x;
														}

														break;

												case	VI_ORG_MODE_Y	:
														{
															m_stSystemStatus.stVisionOriginOffset.dblY	= stResultModelFind.flOffset.y;
														}

														break;
											}

											m_stSystemStatus.stVisionOriginOffset.dblAngle	= stResultModelFind.dblAngle;

											// ����� �޼���
											MessageWindow(cDEBUG, _T("[P:%02d] ���� ���� = x%.2f, y%.2f, a%.2f"),	m_stSystemStatus.nCurrentVisionInspectionNo + 1,
																													m_stSystemStatus.stVisionOriginOffset.dblX,
																													m_stSystemStatus.stVisionOriginOffset.dblY,
																													m_stSystemStatus.stVisionOriginOffset.dblAngle);
									
										} else {

											if (++nRetryOriginDetect <= MAX_VISION_ORIGIN_RETRY) {

												switch (nRetryOriginDetect) {
											
													case	1	:
																	// ���� ������ X�������� (-) �̵�
																	stOriginDetectArea.ptTopLeft.x		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.x - VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.x	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.x - VISION_ORIGIN_OFFSET;
																	break;

													case	2	:
																	// ���� ������ X�������� (+) �̵�
																	stOriginDetectArea.ptTopLeft.x		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.x + VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.x	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.x + VISION_ORIGIN_OFFSET;
																	break;

													case	3	:
																	// ���� ������ Y�������� (-) �̵�
																	stOriginDetectArea.ptTopLeft.x		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.x;
																	stOriginDetectArea.ptTopLeft.y		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.y - VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.x	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.x;
																	stOriginDetectModel.flOffset_M.y	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.y - VISION_ORIGIN_OFFSET;
																	break;

													case	4	:
																	// ���� ������ Y�������� (+) �̵�
																	stOriginDetectArea.ptTopLeft.x		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.x;
																	stOriginDetectArea.ptTopLeft.y		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.y + VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.x	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.x;
																	stOriginDetectModel.flOffset_M.y	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.y + VISION_ORIGIN_OFFSET;
																	break;

													case	5	:
																	// ���� ������ X�������� (-), Y�������� (-) �̵�
																	stOriginDetectArea.ptTopLeft.x		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.x - VISION_ORIGIN_OFFSET;
																	stOriginDetectArea.ptTopLeft.y		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.y - VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.x	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.x - VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.y	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.y - VISION_ORIGIN_OFFSET;
																	break;

													case	6	:
																	// ���� ������ X�������� (-), Y�������� (+) �̵�
																	stOriginDetectArea.ptTopLeft.x		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.x - VISION_ORIGIN_OFFSET;
																	stOriginDetectArea.ptTopLeft.y		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.y + VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.x	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.x - VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.y	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.y + VISION_ORIGIN_OFFSET;
																	break;

													case	7	:
																	// ���� ������ X�������� (+), Y�������� (-) �̵�
																	stOriginDetectArea.ptTopLeft.x		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.x + VISION_ORIGIN_OFFSET;
																	stOriginDetectArea.ptTopLeft.y		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.y - VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.x	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.x + VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.y	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.y - VISION_ORIGIN_OFFSET;
																	break;

													case	8	:
																	// ���� ������ X�������� (+), Y�������� (+) �̵�
																	stOriginDetectArea.ptTopLeft.x		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.x + VISION_ORIGIN_OFFSET;
																	stOriginDetectArea.ptTopLeft.y		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.y + VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.x	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.x + VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.y	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.y + VISION_ORIGIN_OFFSET;
																	break;
												}

												// �޼��� ���
												ErrorMessage(TRUE, _T("[P:%02d] ���� ���� ������ ��õ��մϴ�. (%d)"), m_stSystemStatus.nCurrentVisionInspectionNo + 1, nRetryOriginDetect);
												break;
											}

											// ���� ���� ����
											bOnOriginDetectFailure = TRUE;
										}
									}
								}

								PROCESS.nCurrentStep = 3180;
								break;
							}

							PROCESS.nCurrentStep = 3140;
							break;

		// �˻� ��� : �÷� �м�
		case	3140	:
							if (pstVisionProcedureData->nInspectionMode == VI_MODE_COLOR_ANALYSIS) {

								if (pstVisionProcedureData->nNumberOfVisionRegion) {

									// �Ķ���� ����
									ZeroMemory(&stParamColorAnalysis, sizeof(VI_PARAM_COLOR_T));
									stParamColorAnalysis.MilImageInspection		= m_MilImageInspection[PROCESS.nCurrentWorkSheetNo];
									stParamColorAnalysis.rectInspectionArea		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo;
									stParamColorAnalysis.stInspectionInfo		= pstVisionProcedureData->stInspection_ColorAnalysis;
									stParamColorAnalysis.bUseReverseJudgement	= pstVisionProcedureData->bOptions[VOPT_REVERSE_JUDGEMENT];

									// �̹��� ���μ��� ����
									ProcessImage_ColorAnalysis(	PROCESS.nCurrentWorkSheetNo, 
																nSTATION_NO, 
																m_stSystemStatus.stVisionOriginOffset,
																stParamColorAnalysis, 
																stResultColorAnalysis);

									nResultVision = stResultColorAnalysis.nResultInspection;
								}

								PROCESS.nCurrentStep = 3180;
								break;
							}

							PROCESS.nCurrentStep = 3170;
							break;

		// �˻� ��� : ����
		case	3170	:
							SErrorMessage(TRUE, _T("[P:%02d] ���� ���� ��尡 ���ǵǾ� ���� �ʽ��ϴ�."), m_stSystemStatus.nCurrentVisionInspectionNo + 1);

							nResultVision			= T_RESULT_ERROR;
							PROCESS.nCurrentStep	= 3200;
							break;

		// �˻� ���� ǥ��
		case	3180	:
							if (m_pMilImageWnd) {

								// �ҷ��̰ų� ��ǰ ǥ�� �ɼ��� ����� ���
								if (nResultVision != T_RESULT_SUCCESS || m_SystemConfig.UseSystemOption(SOPT_VIEW_VISION_MARK_OK)) {

									PDMW_USER_RECT_T pstUserRect = new (std::nothrow) DMW_USER_RECT_T;
									if (pstUserRect) {

										ZeroMemory(pstUserRect, sizeof(DMW_USER_RECT_T));
										pstUserRect->crColor	= nResultVision == T_RESULT_SUCCESS ? CLR_GREEN : CLR_RED;
										pstUserRect->nPosX		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.x + (INT)m_stSystemStatus.stVisionOriginOffset.dblX;
										pstUserRect->nPosY		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.y + (INT)m_stSystemStatus.stVisionOriginOffset.dblY;
										pstUserRect->nSizeX		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.sizeRect.cx;
										pstUserRect->nSizeY		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.sizeRect.cy;
									
										m_pMilImageWnd->InsertListUserRect(pstUserRect);
										stRectInspection = *pstUserRect;
									}
								}
							}

							PROCESS.nCurrentStep = 3200;
							break;

		// �˻� ��� ����
		case	3200	:
							{
								DOUBLE				dblGain			= PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_GAIN];
								DOUBLE				dblOffset		= PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_OFFSET];
								DOUBLE				dblJudgement	= PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_JUDGE];
								DOUBLE				dblSpecMIN		= PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_SPEC_L];
								DOUBLE				dblSpecMAX		= PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_SPEC_H];

								CString				strParameters	= _T("");
								VISION_TEST_DATA_T	stVisionTestData;


								// �˻� �׸� ��� ����
								if (PROCESS.nResultInspection == T_RESULT_SUCCESS)
									PROCESS.nResultInspection = nResultVision;

								// �ҷ� �׷� ����
								if (nResultVision != T_RESULT_SUCCESS) {

									//(PROCESS.pstWorkStatus)->nGroupNG = pstVisionProcedureData->nGroupNG;
									//MessageWindow(cDEBUG, _T("[T%d%d] NG-GROUP = %d"), nSTATION_NO + 1, nSTATION_SUB_NO + 1, (PROCESS.pstWorkStatus)->nGroupNG);
								}
								
								// �˻� �Ķ���� ����
								switch (pstVisionProcedureData->nInspectionMode) {
				
									case	VI_MODE_THRESHOLD			:
																			PROCESS.dblValueMeasurement = stResultThreshold.dblRatioWhitePixel;
																			strParameters.AppendFormat(_T("TR/"));
																			strParameters.AppendFormat(_T("ratio=%.2f/"),		stResultThreshold.dblRatioWhitePixel);
																			strParameters.AppendFormat(_T("spec_min=%.2f/"),	stParamThreshold.stInspectionInfo.dblRatioWhitePixelMIN);
																			strParameters.AppendFormat(_T("spec_max=%.2f"),		stParamThreshold.stInspectionInfo.dblRatioWhitePixelMAX);
																			break;

									case	VI_MODE_THRESHOLD_LENGTH	:
																			PROCESS.dblValueMeasurement = (stResultThresholdLength.dblMeasurement * dblGain) + dblOffset;

																			// ������ üũ
																			if (dblJudgement != 0.0)
																				PROCESS.dblValueMeasurement = dblJudgement - PROCESS.dblValueMeasurement;

																			// �˻� ��� ����
																			if (DPS_Round(PROCESS.dblValueMeasurement, 2) < DPS_Round(dblSpecMIN, 2) ||
																				DPS_Round(PROCESS.dblValueMeasurement, 2) > DPS_Round(dblSpecMAX, 2))
																					PROCESS.nResultInspection = T_RESULT_FAILURE;

																			strParameters.AppendFormat(_T("TL/"));
																			strParameters.AppendFormat(_T("length=%.2f(%.2f)/"),	stResultThresholdLength.dblMeasurement, PROCESS.dblValueMeasurement);
																			strParameters.AppendFormat(_T("length_min=%.2f/"),		stParamThresholdLength.stInspectionInfo.dblLengthSpecMIN);
																			strParameters.AppendFormat(_T("length_max=%.2f"),		stParamThresholdLength.stInspectionInfo.dblLengthSpecMAX);
																			break;

									case	VI_MODE_PATTERN				:
																			PROCESS.dblValueMeasurement = stResultPatternMatch.dblMatchScore;
																			strParameters.AppendFormat(_T("PTN/"));
																			strParameters.AppendFormat(_T("offset=%.2f|%.2f"),	stResultPatternMatch.flOffset.x, stResultPatternMatch.flOffset.y);
																			strParameters.AppendFormat(_T("(%.2f|%.2f)/"),		stParamPatternMatch.stInspectionInfo.flOffset.x, stParamPatternMatch.stInspectionInfo.flOffset.y);
																			strParameters.AppendFormat(_T("angle=%.2f(%.2f)/"),	stResultPatternMatch.dblAngle, stParamPatternMatch.stInspectionInfo.dblAngle);
																			strParameters.AppendFormat(_T("score=%.2f(%.2f)"),	stResultPatternMatch.dblMatchScore, stParamPatternMatch.stInspectionInfo.dblMatchScore);
																			break;
							
									case	VI_MODE_MODEL_FINDER		:
																			PROCESS.dblValueMeasurement = stResultModelFind.dblMatchScore;
																			strParameters.AppendFormat(_T("MOD/"));
																			strParameters.AppendFormat(_T("offset=%.2f|%.2f"),	stResultModelFind.flOffset.x, stResultModelFind.flOffset.y);
																			strParameters.AppendFormat(_T("(%.2f/%.2f)/"),		stParamModelFind.stInspectionInfo.flOffset.x, stParamPatternMatch.stInspectionInfo.flOffset.y);
																			strParameters.AppendFormat(_T("angle=%.2f(%.2f)/"),	stResultModelFind.dblAngle, stParamModelFind.stInspectionInfo.dblAngle);
																			strParameters.AppendFormat(_T("score=%.2f(%.2f)"),	stResultModelFind.dblMatchScore, stParamModelFind.stInspectionInfo.dblMatchScore);
																			break;

									case	VI_MODE_COLOR_ANALYSIS		:
																			PROCESS.dblValueMeasurement = stResultColorAnalysis.dblMatchScore;
																			strParameters.AppendFormat(_T("COL/"));
																			strParameters.AppendFormat(_T("score=%.2f(%.2f)"),	stResultColorAnalysis.dblMatchScore, stParamColorAnalysis.stInspectionInfo.dblMatchScore);
																			break;
								}							

								// �˻� ��� ����
								if (PROCESS.bOnRetryInspection) {
								
									stVisionTestData					= m_arrVisionTestData[PROCESS.nCurrentWorkSheetNo].GetAt(m_stSystemStatus.nCurrentVisionInspectionNo);
									stVisionTestData.stRectInspection	= stRectInspection;
									stVisionTestData.nResult			= nResultVision;
									stVisionTestData.dblValue			= PROCESS.dblValueMeasurement;
									_tcscpy_s(stVisionTestData.szName, MAX_STRINPUT_L, pstVisionProcedureData->szName);
									_tcscpy_s(stVisionTestData.szParameters, MAX_STRINPUT_L, strParameters);
									m_arrVisionTestData[PROCESS.nCurrentWorkSheetNo].SetAt(m_stSystemStatus.nCurrentVisionInspectionNo, stVisionTestData);
								
								} else {
								
									ZeroMemory(&stVisionTestData, sizeof(VISION_TEST_DATA_T));
									stVisionTestData.bUsePoint			= TRUE;
									stVisionTestData.stRectInspection	= stRectInspection;
									stVisionTestData.nResult			= nResultVision;
									stVisionTestData.dblValue			= PROCESS.dblValueMeasurement;
									_tcscpy_s(stVisionTestData.szName, MAX_STRINPUT_L, pstVisionProcedureData->szName);
									_tcscpy_s(stVisionTestData.szParameters, MAX_STRINPUT_L, strParameters);
									m_arrVisionTestData[PROCESS.nCurrentWorkSheetNo].Add(stVisionTestData);
								}

								// ������Ʈ
								PROCESS.bOnUpdateUI					= TRUE;
								PROCESS.stParamUI.nUpdateID			= UI_VISION_SHEET;
								PROCESS.stParamUI.nStationNo		= nSTATION_NO;
								PROCESS.stParamUI.stWorkSheet.nTestItem				= PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].nTestSheetItem;
								PROCESS.stParamUI.stWorkSheet.nWorkPosition			= PROCESS.nCurrentWorkSheetNo;
								PROCESS.stParamUI.stWorkSheet.nWorkStatus			= WORK_STATE_COMPLETE;
								PROCESS.stParamUI.stWorkSheet.nIndexVisionTestData	= m_stSystemStatus.nCurrentVisionInspectionNo;

								// ���� ��Ʈ ����
								SaveVisionSheet(PROCESS.nCurrentWorkSheetNo, 
												m_stSystemStatus.nCurrentVisionInspectionNo,
												stVisionTestData,
												PROCESS.nRetryCount);
							}

							PROCESS.nCurrentStep = 3300;
							break;

		// �Ϸ�
		case	3300	:
							PROCESS.nCurrentStep = PROCESS.nReturn03Step;
							break;


		/////////////////////////////////////////////////////////////
		// ���� /////////////////////////////////////////////////////
		case	STEP_WORK_ERROR	:
									PROCESS.bOnOperatingStop = TRUE;
									break;

		case	STEP_WORK_ERROR_PARTS	:
											PROCESS.bOnError				= TRUE;
											PROCESS.nRecoveryStep			= STEP_WORK_ERROR;
											PROCESS.stErrorCode.nErrorCode	= ERROR_MACHINE_SEQUENCE;
											PROCESS.stErrorCode.nProcessID	= PROCESS_MAIN_WORK_VISION;
											PROCESS.stErrorCode.nStationNo	= nSTATION_NO;

											// ����� �޼���
											SDebugMessage(TRUE, _T("[P%d:%d] ERROR PARTS"), nSTATION_NO, nSTATION_SUB_NO + 1);
											break;

		case	STEP_WORK_ERROR_SYSTEM	:
											// ����� �޼���
											SDebugMessage(TRUE, _T("[P%d:%d] ERROR SYSTEM"), nSTATION_NO, nSTATION_SUB_NO + 1);
											break;	

		case	STEP_WORK_ERROR_DEVICE	:
											// ����� �޼���
											SDebugMessage(TRUE, _T("[P%d:%d] ERROR DEVICE"), nSTATION_NO, nSTATION_SUB_NO + 1);

											// �޼��� ���
											ErrorMessage(TRUE, _T("[P%d] NO RESPONSE CAMERA"), nSTATION_NO);

											// ���μ��� �÷��� �ʱ�ȭ
											m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]				= FALSE;
											m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
											m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
											m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
											m_stSystemStatus.bIsMainProcessInitialized[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;

											PROCESS.nCurrentStep = STEP_WORK_STANDBY;
											break;	


		/////////////////////////////////////////////////////////////
		// �Ͻ� ���� ���� ///////////////////////////////////////////
		case	STEP_PAUSE	:
								if (m_stSystemStatus.bOnEmergencyStop) {

									PROCESS.nCurrentStep = STEP_EMG;
									break;
								}

								PROCESS.nCurrentStep++;
								break;

		case	20001	:
							if (!m_stSystemStatus.bOnPause && !m_stSystemStatus.bOnAlarmSystem && !m_stSystemStatus.bOnAlarmStation[nSTATION_NO]) {

								PROCESS.nCurrentStep = 20100;
							}

							break;

		// ���� ����
		case	20100	:
							PROCESS.nCurrentStep	= PROCESS.nRecoveryStep;
							PROCESS.bOnPause		= FALSE;
							break;


		/////////////////////////////////////////////////////////////
		// ��� ���� ���� ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop)	{

									PROCESS.nRecoveryStep	= 0;
									PROCESS.nCurrentStep	= STEP_PAUSE;
								}

								break;


		/////////////////////////////////////////////////////////////
		// ��� �ʱ�ȭ ���� /////////////////////////////////////////
		case	STEP_MC_INIT	:
									PROCESS.nCurrentStep = 22020;
									break;

		case	22020	:
							if (!m_stSystemStatus.bOnMachineInitialize) {
							
								PROCESS.bIsOperatingStop		= FALSE;
								PROCESS.bOnMachineInitialize	= FALSE;
								PROCESS.nCurrentStep			= PROCESS.nRecoveryStep;
							}

							break;
	}


	/////////////////////////////////////////////////////////////////
	// ������ ���� //////////////////////////////////////////////////
	for (UINT nVisionCH = 0; nVisionCH < MAX_VISION_CHANNEL; nVisionCH++) {

		while (m_Comm[COMM_DEV_CAM + nVisionCH].ReadByte(&byReadByte)) {

			// ������ ����
			szRcvdPacket[nVisionCH][nRcvdPacketIndex[nVisionCH]++] = byReadByte;

			// �ϳ��� ��Ŷ�� �ϼ��Ǹ� �ؼ�
			if (byReadByte == COMM_ETX_F) {

				USES_CONVERSION;
				szRcvdPacket[nVisionCH][nRcvdPacketIndex[nVisionCH] - 1] = '\0';
				MessageWindow(cDEBUG, _T("[CAM%d->] %s"), nVisionCH + 1, A2W(szRcvdPacket[nVisionCH]));
				
				// ���� üũ
				if (strncmp(szRcvdPacket[nVisionCH], "OK", 2))	
					bReceiveData[nVisionCH] = TRUE;

				// ��Ŷ �ʱ�ȭ
				nRcvdPacketIndex[nVisionCH] = 0;
			}

			// ��Ŷ �����÷ο� ����
			if (nRcvdPacketIndex[nVisionCH] >= COMM_PACKET_SIZE) {

				nRcvdPacketIndex[nVisionCH] = 0;
				break;
			}
		}
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���� üũ ///////////////////////////////////////////////
	CheckProcessOperatingStop(PROCESS);


	/////////////////////////////////////////////////////////////////
	// �Ϲ� /////////////////////////////////////////////////////////
	PROCESS.bIsUpdateSendMessage = TRUE;
	CheckProcessGeneral(nSTATION_NO, PROCESS);


	/////////////////////////////////////////////////////////////////
	// ���� ����͸� ////////////////////////////////////////////////
	if (LTimerSystemMonitor.Verify()) {

		if (PROCESS.nPrevStep != PROCESS.nCurrentStep) {

			PROCESS.nPrevStep = PROCESS.nCurrentStep;
			if (m_pSysMonitorDlg && m_pSysMonitorDlg->GetSafeHwnd()) {

				m_pSysMonitorDlg->PostMessage(UM_SYSM_UPDATE_STEP, PSTEP_PROC_MAIN_WORK_VISION, PROCESS.nCurrentStep);
				LTimerSystemMonitor.Start(DLY_REFRESH_SYSTEM_MONITOR);
			}
		}
	}


	return	PROCESS.pstErrorCode;
}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� : ���� ////////////////////////////////////////////////////////////
PERROR_CODE_T CMainApp::ProcessCommon(void)
{
	return	NULL;
}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� : ���� #01 - �˻� ���� (OS) ///////////////////////////////////////
PERROR_CODE_T CMainApp::ProcessStation01(void)
{
	static	PROCESS_CTRL_T		PROCESS;

	static	UINT				nSTATION_NO					= STATION_1;
	static	UINT				nSTATION_SUB_NO				= STN1_SUB_NONE;

	static	UINT				nBCS_INPUT_M				= BCS_INPUT_1;
	static	UINT				nBCS_INPUT_A				= BCS_INPUT_2;

			PBOOL				pOnSCP_MoveParts			= m_stSystemStatus.bOnSCP_MoveParts[nSTATION_NO];
	static	UINT				nSCP_PARTS_ID				= 0;

	static	CString				strMessage					= _T("");
	static	BOOL				bOnCheckProductCodeEmpty	= FALSE;
	static	BOOL				bOnErrorProductCode			= FALSE;

	static	LTimerMsec			LTimerProceed;
	static	LTimerMsec			LTimerSubProceed;
	static	LTimerMsec			LTimerAlarm;
	static	LTimerMsec			LTimerSensor;
	static	LTimerMsec			LTimerSteady;
	static	LTimerMsec			LTimerSteadyScan;
	static	LTimerMsec			LTimerTimeOut;
	static	LTimerMsec			LTimerTimeOutScan;
	static	LTimerMsec			LTimerButton;
	static	LTimerMsec			LTimerWaitProduct;
	static	LTimerMsec			LTimerWaitPallet;
	static	LTimerMsec			LTimerUserProcess;
	static	LTimerMsec			LTimerSystemMonitor;
	static	LTimerMsec			LTimerSystemDisplay;


	/////////////////////////////////////////////////////////////////
	// ���μ��� ������ �ʱ�ȭ ///////////////////////////////////////
	ProcessDataInitialize(PROCESS);


	/////////////////////////////////////////////////////////////////
	// �ڵ� ���� ����/���� �ʱ�ȭ ///////////////////////////////////
	CheckProcessOperating(PROCESS);


	/////////////////////////////////////////////////////////////////
	// ��� �ʱ�ȭ //////////////////////////////////////////////////
	if (CheckProcessMachineInitialize(PROCESS))
		return	NULL;


	/////////////////////////////////////////////////////////////////
	// �۾� ���� ���� ///////////////////////////////////////////////
	if (CheckProcessOperatingStopReservated(nSTATION_NO, nSTATION_SUB_NO, PROCESS))
		return	NULL;


	/////////////////////////////////////////////////////////////////
	// ���� ���� ��� ///////////////////////////////////////////////
	if (CheckProcessManualControlMode(nSTATION_NO, PROCESS))
		return	NULL;
	

	/////////////////////////////////////////////////////////////////
	// ���/�Ͻ� ���� ���� //////////////////////////////////////////
	if (CheckProcessEmergencyStop(PROCESS))					return	NULL;
	if (CheckProcessOperatingPause(nSTATION_NO, PROCESS))	return	NULL;


	/////////////////////////////////////////////////////////////////
	// ���� ���μ��� ////////////////////////////////////////////////
	switch (PROCESS.nCurrentStep) {

		case	0		:
							PROCESS.nCurrentStep = 10;
							break;

		// �ý��� üũ
		case	10		:
							if (IsSystemReady()) {
							
								PROCESS.nCurrentStep = 20;
							}
								
							break;

		// �÷��� �ʱ�ȭ
		case	20		:
							// ���� ���μ��� ������ �ʱ�ȭ
							StationProcessDataInitialize(nSTATION_NO, nSTATION_SUB_NO, PROCESS);

							PROCESS.nCurrentStep = 30;
							break;

		// ���� �ʱ�ȭ
		case	30		:
							// ���ڵ� ��ĳ�� Ʈ���� ����
							SetTrigBarcode(nBCS_INPUT_M, FALSE);
							SetTrigBarcode(nBCS_INPUT_A, FALSE);

							PROCESS.nCurrentStep = 40;
							break;

		// ���� ���� ����
		case	40		:
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_NONE;

							PROCESS.nCurrentStep = 50;
							break;

		// �ڵ� ���� üũ
		case	50		:
							if (m_stSystemStatus.bOnOperating) {

								PROCESS.nCurrentStep = 60;
							}

							break;

		// �� �������� �ε�
		case	60		:
							PROCESS.pstModelProfile	= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
							PROCESS.pstWorkStatus	= GetWorkStatus(nSTATION_NO);

							if (PROCESS.pstModelProfile != NULL) {

								PROCESS.pstModelProfileConfig	= &(PROCESS.pstModelProfile)->stModelProfileConfig;
								PROCESS.pstWorkInfo				= &(PROCESS.pstModelProfileConfig)->stWorkInfo;
								PROCESS.pstStationSetupInfo		= &(PROCESS.pstModelProfileConfig)->stSpBasicSetupInfo;
								PROCESS.pstLabelPrintInfo		= &(PROCESS.pstModelProfileConfig)->stSpLabelPrintSetupInfo.stLabelPrintInfo;
								PROCESS.pstMiscellaneousInfo	= &(PROCESS.pstModelProfileConfig)->stSpMiscellaneousInfo;
								PROCESS.pstWorkPositionInfo		= (PROCESS.pstModelProfileConfig)->stSpBasicSetupInfo.stWorkPositionSheet;

								PROCESS.nCurrentStep = 90;
								break;
							}

							SErrorMessage(TRUE, _T("[S%02d/%s] �� ������ �ε��� �� �����ϴ�."),	nSTATION_NO, 
																									g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

							PROCESS.nCurrentStep = STEP_STN_ERROR_SYSTEM;
							break;

		// �Ϸ�
		case	90		:
							PROCESS.nCurrentStep	= STEP_STN_INIT;
							PROCESS.nReturn01Step	= STEP_STN_STANDBY;
							break;


		/////////////////////////////////////////////////////////////
		// �ʱ�ȭ ///////////////////////////////////////////////////
		case	STEP_STN_INIT	:
									PROCESS.nCurrentStep = 110;
									break;

		// �÷��� �ʱ�ȭ
		case	110		:
							m_stSystemStatus.bOnStationInitializeResult[nSTATION_NO][nSTATION_SUB_NO]	= TRUE;
							m_stSystemStatus.bIsStationProcessLock[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;

							PROCESS.nCurrentStep = 120;
							break;

		// ���� ���� ����
		case	120		:
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_NONE;

							// ������Ʈ UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_STATUS_STATION;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;

							PROCESS.nCurrentStep = 130;
							break;

		// ���� �ʱ�ȭ
		case	130		:
							// ���� ������ �ʱ�ȭ
							SetDOStatus(DO_OFF, DO_RLY_S01_PRODUCT_POWER_ON);
							SetDOStatus(DO_OFF, DO_RLY_S01_BYPASS_ON);
							SetDOStatus(DO_OFF, DO_RLY_S01_CONN_P);
							SetDOStatus(DO_OFF, DO_RLY_S01_CONN_N);
							SetDOStatus(DO_OFF, DO_RLY_S01_RANGE_mA);
							SetDOStatus(DO_OFF, DO_RLY_S01_RANGE_A);
							SetDOStatus(DO_OFF, DO_RLY_S01_MEAS_CURRENT);
							SetDOStatus(DO_OFF, DO_RLY_S01_CONN_BATT);
							SetDOStatus(DO_OFF, DO_RLY_S01_CONN_IGN);
							SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_CHECK);
							SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_LOCK_ON);
							SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_LOCK_OFF);
							
							// ���ڵ� ��ĳ�� Ʈ���� ����
							SetTrigBarcode(nBCS_INPUT_M, FALSE);
							SetTrigBarcode(nBCS_INPUT_A, FALSE);

							PROCESS.nCurrentStep = 140;
							break;

		// �۾� ��� ��ġ �̵�
		case	140		:
							if (!PROCESS.bOnMachineInitialize) {

								PROCESS.nCurrentStep	= STEP_STN_HOME;
								PROCESS.nReturn02Step	= 150;
								break;
							}

							PROCESS.nCurrentStep = 150;
							break;

		// �۾� ���� �ʱ�ȭ
		case	150		:
							if (!PROCESS.bOnMachineInitialize) {

								PROCESS.nCurrentStep	= STEP_STN_SUB_01;
								PROCESS.nReturn02Step	= 190;
								break;
							}

							PROCESS.nCurrentStep = 190;
							break;

		// �Ϸ�
		case	190		:
							// �ʱ�ȭ �Ϸ� �÷��� ����
							m_stSystemStatus.bOnStationInitializeComplete[nSTATION_NO][nSTATION_SUB_NO] = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn01Step;
							break;


		/////////////////////////////////////////////////////////////
		// ��� ��ġ �̵� ///////////////////////////////////////////
		case	STEP_STN_HOME	:
									PROCESS.nCurrentStep = 410;
									break;

		// ���ͷ� üũ
		case	410		:
							{
								BOOL	bOnInterLock	= FALSE;

								if (bOnInterLock) {
								
									PROCESS.bOnError				= TRUE;
									PROCESS.nRecoveryStep			= 410;
									PROCESS.stErrorCode.nErrorCode	= ERROR_MACHINE_SEQUENCE;
									PROCESS.stErrorCode.nProcessID	= PROCESS_STATION;
									PROCESS.stErrorCode.nStationNo	= nSTATION_NO;
									break;
								}

								PROCESS.nCurrentStep = 420;
							}
		
							break;

		// VY ���� ��ġ üũ
		case	420		:
							if (!Motion_CheckSafePosition(MOTION_RVY, FALSE, TRUE)) {
							
								PROCESS.nCurrentStep++;
								break;
							}

							PROCESS.nCurrentStep = 450;
							break;

		case	421		:
							// ���� ��ġ �ִ� ��ġ�� ���� �̵�
							if (Motion_Done(MOTION_RVY)) {

								Motion_MoveTo(	MOTION_RVY,
												m_stMotionAxisInfo[MOTION_RVY].dblSafePositionMAX, 
												m_stMotionAxisInfo[MOTION_RVY].dblSpeedJogSlow);

								PROCESS.nCurrentStep++;
							}

							break;

		case	422		:
							if (Motion_Done(MOTION_RVY)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = m_stMotionAxisInfo[MOTION_RVY].dblSafePositionMAX;
								if (!Motion_CheckStopStatus(MOTION_RVY, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVY;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 450;
							}

							break;

		// VZ ��� ��ġ �̵�
		case	450		:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVZ)) {

								Motion_MoveTo(	MOTION_RVZ,
												m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME], 
												m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	451		:
							if (Motion_Done(MOTION_RVZ)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME];
								if (!Motion_CheckStopStatus(MOTION_RVZ, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVZ;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 460;
							}

							break;

		// VY ��� ��ġ �̵�
		case	460		:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVY)) {

								Motion_MoveTo(	MOTION_RVY,
												m_stMotionAxisInfo[MOTION_RVY].dblCustomPosition[MAI_CPOS_HOME], 
												m_stMotionAxisInfo[MOTION_RVY].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	461		:
							if (Motion_Done(MOTION_RVY)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = m_stMotionAxisInfo[MOTION_RVY].dblCustomPosition[MAI_CPOS_HOME];
								if (!Motion_CheckStopStatus(MOTION_RVY, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVY;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 470;
							}

							break;

		// VX ��� ��ġ �̵�
		case	470		:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVX)) {

								Motion_MoveTo(	MOTION_RVX,
												m_stMotionAxisInfo[MOTION_RVX].dblCustomPosition[MAI_CPOS_HOME], 
												m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	471		:
							if (Motion_Done(MOTION_RVX)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = m_stMotionAxisInfo[MOTION_RVX].dblCustomPosition[MAI_CPOS_HOME];
								if (!Motion_CheckStopStatus(MOTION_RVX, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVX;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 490;
							}

							break;

		// �Ϸ�
		case	490		:
							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// �۾� ���� �ʱ�ȭ /////////////////////////////////////////
		case	STEP_STN_SUB_01	:
									PROCESS.nCurrentStep = 8010;
									break;

		// �غ� �۾�
		case	8010	:
							PROCESS.nCurrentStep = 8020;
							break;

		// ���κ� ���̵� : OFF
		case	8020	:
							pOnSCP_MoveParts[SCP_S01_PROBE_GUIDE_OFF] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	8021	:
							if (!pOnSCP_MoveParts[SCP_S01_PROBE_GUIDE_OFF])
								PROCESS.nCurrentStep = 8030;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// ���κ� : OFF
		case	8030	:
							pOnSCP_MoveParts[SCP_S01_PROBE_OFF] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	8031	:
							if (!pOnSCP_MoveParts[SCP_S01_PROBE_OFF])
								PROCESS.nCurrentStep = 8040;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// ���� ���� ���� : DN
		case	8040	:
							pOnSCP_MoveParts[SCP_S01_PRODUCT_DOOR_OPEN_DN] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	8041	:
							if (!pOnSCP_MoveParts[SCP_S01_PRODUCT_DOOR_OPEN_DN])
								PROCESS.nCurrentStep = 8050;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// ��ǰ ���� üũ
		case	8050	:
							if (GetDIStatus(DI_SENS_S01_DETECT_PRODUCT)) {

								LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_PRODUCT));

								PROCESS.nCurrentStep++;
								break;
							}

							LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_PRODUCT_NONE));

							PROCESS.nCurrentStep = 8052;
							break;

		case	8051	:
							if (GetDIStatus(DI_SENS_S01_DETECT_PRODUCT)) {

								if (LTimerSensor.Verify()) {

									PROCESS.nCurrentStep = 8060;
								}

								break;
							}

							PROCESS.nCurrentStep--;
							break;

		case	8052	:
							if (!GetDIStatus(DI_SENS_S01_DETECT_PRODUCT)) {

								if (LTimerSensor.Verify()) {

									PROCESS.nCurrentStep = 8070;
								}

								break;
							}

							PROCESS.nCurrentStep--;
							break;

		// ��ǰ ���� ���� üũ
		case	8060	:
							if (GetDIStatus(DI_SENS_S01_DETECT_PRODUCT_DOOR)) {

								LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_PRODUCT));

								PROCESS.nCurrentStep++;
								break;
							}

							LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_PRODUCT_NONE));

							PROCESS.nCurrentStep = 8062;
							break;

		case	8061	:
							if (GetDIStatus(DI_SENS_S01_DETECT_PRODUCT_DOOR)) {

								if (LTimerSensor.Verify()) {

									PROCESS.nCurrentStep = 8070;
								}

								break;
							}

							PROCESS.nCurrentStep--;
							break;

		case	8062	:
							if (!GetDIStatus(DI_SENS_S01_DETECT_PRODUCT_DOOR)) {

								if (LTimerSensor.Verify()) {

									PROCESS.nCurrentStep = 8080;
								}

								break;
							}

							PROCESS.nCurrentStep = 8060;
							break;

		// �ε� ���� : FWD
		case	8070	:
							pOnSCP_MoveParts[SCP_S01_LOADING_FWD] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	8071	:
							if (!pOnSCP_MoveParts[SCP_S01_LOADING_FWD])
								PROCESS.nCurrentStep = 8080;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// ...?
		case	8080	:
							PROCESS.nCurrentStep = 8090;
							break;

		// �Ϸ�
		case	8090	:
							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// ��ǰ ���� ���� üũ //////////////////////////////////////
		case	STEP_STN_SUB_02	:
									PROCESS.nCurrentStep = 8110;
									break;

		// �غ� �۾�
		case	8110	:
							// �÷��� �ʱ�ȭ
							PROCESS.bOnInterLock = FALSE;

							PROCESS.nCurrentStep = 8120;
							break;

		// �ε� ���� : BWD
		case	8120	:
							pOnSCP_MoveParts[SCP_S01_LOADING_BWD] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	8121	:
							if (!pOnSCP_MoveParts[SCP_S01_LOADING_BWD])
								PROCESS.nCurrentStep = 8130;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// ���� ���� ���� : UP
		case	8130	:
							SetDOStatus(DO_ON, DO_SOL_S01_PRODUCT_DOOR_OPEN_UP);
							LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_MOVE_CYLINDER));

							PROCESS.nCurrentStep++;
							break;

		case	8131	:
							if (GetDIStatus(DI_SENS_S01_PRODUCT_DOOR_OPEN_UP)) {
							
								PROCESS.nCurrentStep = 8140;
								break;
							}

							if (LTimerTimeOut.Verify()) {
							
								// �÷��� ����
								PROCESS.bOnInterLock = TRUE;

								PROCESS.nCurrentStep = 8140;
							}

							break;

		// ���� ���� ���� : DN
		case	8140	:
							pOnSCP_MoveParts[SCP_S01_PRODUCT_DOOR_OPEN_DN] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	8141	:
							if (!pOnSCP_MoveParts[SCP_S01_PRODUCT_DOOR_OPEN_DN])
								PROCESS.nCurrentStep = PROCESS.bOnInterLock ? 8170 : 8190;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// �ε� ���� : FWD
		case	8170	:
							pOnSCP_MoveParts[SCP_S01_LOADING_FWD] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	8171	:
							if (!pOnSCP_MoveParts[SCP_S01_LOADING_FWD])
								PROCESS.nCurrentStep = 8190;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// �Ϸ�
		case	8190	:
							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// ��ǰ ���� �ݱ� ///////////////////////////////////////////
		case	STEP_STN_SUB_03	:
									PROCESS.nCurrentStep = 8210;
									break;

		// �غ� �۾�
		case	8210	:
							PROCESS.nCurrentStep = 8220;
							break;

		// VZ ��� ��ġ �̵�
		case	8220	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVZ)) {

								Motion_MoveTo(	MOTION_RVZ,
												m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME], 
												m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	8221	:
							if (Motion_Done(MOTION_RVZ)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME];
								if (!Motion_CheckStopStatus(MOTION_RVZ, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVZ;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 8230;
							}

							break;

		// VY ��� ��ġ �̵�
		case	8230	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVY)) {

								Motion_MoveTo(	MOTION_RVY,
												m_stMotionAxisInfo[MOTION_RVY].dblCustomPosition[MAI_CPOS_HOME], 
												m_stMotionAxisInfo[MOTION_RVY].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	8231	:
							if (Motion_Done(MOTION_RVY)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = m_stMotionAxisInfo[MOTION_RVY].dblCustomPosition[MAI_CPOS_HOME];
								if (!Motion_CheckStopStatus(MOTION_RVY, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVY;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 8240;
							}

							break;

		// VX, VZ ��ǥ ��ġ ���� �̵� (���� �ݱ� ����)
		case	8240	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVZ)) {

								Motion_Move2X(	MCOORD_S01, MOTION_RVZ, MOTION_RVX,
												PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_BEGIN].dblPosition[MINDEX_VZ],
												PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_BEGIN].dblPosition[MINDEX_VX],
												m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	8241	:
							if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVZ)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_BEGIN].dblPosition[MINDEX_VX];
								if (!Motion_CheckStopStatus(MOTION_RVX, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVX;
								}

								dblPosition = PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_BEGIN].dblPosition[MINDEX_VZ];
								if (!Motion_CheckStopStatus(MOTION_RVZ, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVZ;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 8250;
							}

							break;

		// VY ��ǥ ��ġ �̵� (���� �ݱ� ����)
		case	8250	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVY)) {

								Motion_MoveTo(	MOTION_RVY,
												PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_BEGIN].dblPosition[MINDEX_VY],
												m_stMotionAxisInfo[MOTION_RVY].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	8251	:
							if (Motion_Done(MOTION_RVY)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_BEGIN].dblPosition[MINDEX_VY];
								if (!Motion_CheckStopStatus(MOTION_RVY, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVY;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 8260;
							}

							break;
		
		// VX, VY, VZ ��ǥ ��ġ ���� �̵� (���� �ݱ� ����)
		case	8260	:
							// ���� ���� üũ
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVY) && Motion_Done(MOTION_RVZ)) {

								Motion_Move3X(	MCOORD_S01, MOTION_RVZ, MOTION_RVX, MOTION_RVY,
												PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_END].dblPosition[MINDEX_VZ],
												PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_END].dblPosition[MINDEX_VX],
												PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_END].dblPosition[MINDEX_VY],
												m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}

							break;

		case	8261	:
							if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVY) && Motion_Done(MOTION_RVZ)) {

								BOOL	bResult			= TRUE;
								UINT	nMotionAxisNo	= 0;
								DOUBLE	dblPosition		= 0;
								
								dblPosition = PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_END].dblPosition[MINDEX_VX];
								if (!Motion_CheckStopStatus(MOTION_RVX, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVX;
								}

								dblPosition = PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_END].dblPosition[MINDEX_VY];
								if (!Motion_CheckStopStatus(MOTION_RVY, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVY;
								}

								dblPosition = PROCESS.pstWorkPositionInfo[WPS_S01_CLOSE_END].dblPosition[MINDEX_VZ];
								if (!Motion_CheckStopStatus(MOTION_RVZ, dblPosition)) {
								
									bResult			= FALSE;
									nMotionAxisNo	= MOTION_RVZ;
								}

								if (!bResult) {
								
									PROCESS.bOnError					= TRUE;
									PROCESS.nRecoveryStep				= STEP_STN_ERROR;
									PROCESS.stErrorCode.nErrorCode		= ERROR_SERVO_MOTOR_POS;
									PROCESS.stErrorCode.nMotionAxisNo	= nMotionAxisNo;
									break;
								}

								PROCESS.nCurrentStep = 8290;
							}

							break;

		// �Ϸ�
		case	8290	:
							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// �޼��� �ڽ� ��� /////////////////////////////////////////
		case	STEP_STN_MESSAGE_BOX_01	:
											PROCESS.nCurrentStep = 9010;
											break;

		case	9010	:
							// �޼��� �ڽ��� ��� ���� üũ
							if (!m_stSystemStatus.bIsDisplayMessageBox) {
							
								m_stSystemStatus.bIsDisplayMessageBox = TRUE;

								PROCESS.nCurrentStep++;
							}

							break;

		case	9011	:
							// �ý��� �÷��� ����
							m_stSystemStatus.bOnWaitForUser			= TRUE;				// ����� �Է� ��� ����
							m_stSystemStatus.bOnBuzzer				= TRUE;				// ����� ���
							m_stSystemStatus.nMessageBoxButtonCode	= MBOX_BCODE_NONE;	// ��ư �ڵ� �ʱ�ȭ

							// �޼��� �ڽ� ����
							PROCESS.pstMBoxParam = new (std::nothrow) MBOX_PARAM_T;
							if (PROCESS.pstMBoxParam) {

								CString		strValue = _T("");

								strValue.AppendFormat(_T("\n%s\n"), strMessage);
								strValue.AppendFormat(_T(" %s"), g_stSystemString[SYSSTR_INFO_PRESS_CONFIRM_CONTINUE].szDescription[m_nTypeLanguage]);
	
								ZeroMemory(PROCESS.pstMBoxParam, sizeof(MBOX_PARAM_T));
								_stprintf_s((PROCESS.pstMBoxParam)->szButtonTitle[MBOX_BUTTON_0], MAX_STRINPUT, _T("%s\n(ENTER)"), g_stSystemString[SYSSTR_BTN_CONFIRM].szDescription[m_nTypeLanguage]);
								_stprintf_s((PROCESS.pstMBoxParam)->szButtonTitle[MBOX_BUTTON_1], MAX_STRINPUT, _T("%s\n(ESC)"), g_stSystemString[SYSSTR_BTN_BUZZER_OFF].szDescription[m_nTypeLanguage]);
								_stprintf_s((PROCESS.pstMBoxParam)->szMessage, MAX_STRVALUE, _T("%s"), strValue);

								(PROCESS.pstMBoxParam)->bEnableButton[MBOX_BUTTON_0]	= TRUE;
								(PROCESS.pstMBoxParam)->bEnableButton[MBOX_BUTTON_1]	= TRUE;
								(PROCESS.pstMBoxParam)->nTypeButton[MBOX_BUTTON_0]		= MBOX_BTYPE_CLOSE;
								(PROCESS.pstMBoxParam)->nTypeButton[MBOX_BUTTON_1]		= MBOX_BTYPE_NORMAL;
								(PROCESS.pstMBoxParam)->nTimerButton[MBOX_BUTTON_0]		= 0;
								(PROCESS.pstMBoxParam)->nTimerButton[MBOX_BUTTON_1]		= 0;
								(PROCESS.pstMBoxParam)->bEnableShortCutKey				= TRUE;
								(PROCESS.pstMBoxParam)->nKeyShortCut[MBOX_BUTTON_0]		= VK_RETURN;
								(PROCESS.pstMBoxParam)->nKeyShortCut[MBOX_BUTTON_1]		= VK_ESCAPE;
								(PROCESS.pstMBoxParam)->nMessageFontSize				= 26;
								(PROCESS.pstMBoxParam)->crMessageFgColor				= CLR_RED;
								(PROCESS.pstMBoxParam)->bEnableSetWindowPos				= TRUE;
								(PROCESS.pstMBoxParam)->ptWindowPosition				= m_SystemConfig.GetMBoxWindowPosition();
								m_pMessageBoxDlg->SendMessage(UM_DPS_DLG_MESSAGE_BOX_SHOWHIDE, SW_SHOW, (LPARAM)(PROCESS.pstMBoxParam));

								PROCESS.nCurrentStep++;
								break;
							}

							// ������ 2ȸ ���
							m_stSystemStatus.nBeepCount = 2;

							SErrorMessage(TRUE, _T("[S%02d/%s] �޼��� �ڽ��� ������ �� �����ϴ�."),	nSTATION_NO + 1, 
																									g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

							PROCESS.nCurrentStep = 9013;
							break;

		case	9012	:
							if (m_stSystemStatus.nMessageBoxButtonCode != MBOX_BCODE_NONE) {

								// ��ư 0 : Ȯ��
								if (m_stSystemStatus.nMessageBoxButtonCode == MBOX_BCODE_0) {

									PROCESS.nCurrentStep++;
									break;
								} 

								// ��ư 1 : ����� ����
								if (m_stSystemStatus.nMessageBoxButtonCode == MBOX_BCODE_1) {

									m_stSystemStatus.bOnBuzzer				= FALSE;			// ����� ����
									m_stSystemStatus.nMessageBoxButtonCode	= MBOX_BCODE_NONE;	// ��ư �ڵ� �ʱ�ȭ
								}
							}

							break;
								
		case	9013	:
							// �޼��� �ڽ� ��� �÷��� ����
							m_stSystemStatus.bIsDisplayMessageBox = FALSE;

							// �޼��� �ڽ� ���߱�	
							m_pMessageBoxDlg->SendMessage(UM_DPS_DLG_MESSAGE_BOX_SHOWHIDE, SW_HIDE, NULL);

							// �ý��� �÷��� ����
							m_stSystemStatus.bOnWaitForUser	= FALSE;	// ����� �Է� ��� ����
							m_stSystemStatus.bOnBuzzer		= FALSE;	// ����� ����

							PROCESS.nCurrentStep = 9090;
							break;

		// �Ϸ�
		case	9090	:
							PROCESS.nCurrentStep = PROCESS.nReturn03Step;
							break;


		/////////////////////////////////////////////////////////////
		// ��ǰ �ڵ� üũ ///////////////////////////////////////////
		case	STEP_STN_SCAN_CODE	:
										PROCESS.nCurrentStep = 6010;
										break;

		// ��ǰ �ڵ� üũ
		case	6010	:
							{
								CString		strProductCodeM		= GetBarcodeInfo(nBCS_INPUT_M);
								CString		strProductCodeA		= GetBarcodeInfo(nBCS_INPUT_A);
								CString		strProductCode		= _T("");
								BOOL		bOnErrorProduct		= FALSE;
								UINT		nCodeStatus			= BCD_SCAN_NONE;
								UINT		nCodeWorkNG			= WORK_NG_NONE;


								// ��ĵ �ڵ� ����
								strProductCode = strProductCodeM;
								if (strProductCode.IsEmpty())	strProductCode = strProductCodeA;

								// ������ ��ǰ �ڵ� üũ
								PROCESS.bIsMasterProduct = FALSE;
								if (!strProductCode.IsEmpty()) {
								
									for (UINT nIndex = 0; nIndex < MAX_BCD_MASTER_CODE; nIndex++) {
									
										if (strProductCode.Compare(((PSP_WI_BASIC_SETUP_T)PROCESS.pstStationSetupInfo)->szMasterCode[nIndex]) == 0)
											PROCESS.bIsMasterProduct = TRUE;
									}

									if (PROCESS.bIsMasterProduct) {
									
										// �޼��� ���
										TestMessage(TRUE, _T("[S%02d/%s] %s [%s]"),	nSTATION_NO + 1, 
																					g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																					g_stSystemString[SYSSTR_MC_INFO_MASTER_PRODUCT_LOADED].szDescription[m_nTypeLanguage],
																					strProductCode);

										if (m_nTypeLanguage != LANGUAGE_KOR) {

											TestMessage(TRUE, _T("[S%02d/%s] %s [%s]"),	nSTATION_NO + 1, 
																						g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																						g_stSystemString[SYSSTR_MC_INFO_MASTER_PRODUCT_LOADED].szDescription[LANGUAGE_KOR],
																						strProductCode);
										}
									}
								}

								// ��ǰ �ڵ� üũ
								if (!PROCESS.bIsMasterProduct && (PROCESS.pstModelProfileConfig)->bWorkOption[WOPT_USE_SCAN_CODE]) {
								
									// ��ǰ �ڵ� ����
									if (bOnCheckProductCodeEmpty && strProductCode.IsEmpty()) {
									
										// �޼��� ���
										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_INPUT].szDescription[m_nTypeLanguage]);

										if (m_nTypeLanguage != LANGUAGE_KOR) {

											ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																					g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																					g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_INPUT].szDescription[LANGUAGE_KOR]);
										}
	
										// �ڵ� ���� ����
										nCodeStatus		= BCD_SCAN_EMPTY;
										bOnErrorProduct	= TRUE;
									
									// ��ǰ �ڵ� ����
									} else {

										CString		strInputFormat	= (PROCESS.pstWorkInfo)->szWorkInfoValue[WI_ITEM_BCD_INPUT_FORMAT];
									
										// ��ǰ �ڵ� ���� üũ
										if (!strInputFormat.IsEmpty() && !DPS_CheckInputBarcodeFormat(strInputFormat, (LPCTSTR)strProductCode, strProductCode.GetLength())) {

												ErrorMessage(TRUE, _T("[S%02d/%s] %s (%s, %s)"),	nSTATION_NO, 
																									g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																									g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_FORMAT].szDescription[m_nTypeLanguage],
																									strInputFormat, strProductCode);

												if (m_nTypeLanguage != LANGUAGE_KOR) {

													ErrorMessage(TRUE, _T("[S%02d/%s] %s (%s, %s)"),	nSTATION_NO, 
																										g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																										g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_FORMAT].szDescription[LANGUAGE_KOR],
																										strInputFormat, strProductCode);
												}

												nCodeStatus		= BCD_SCAN_WRONG;
												nCodeWorkNG		= WORK_NG_CODE_WRONG;
												bOnErrorProduct	= TRUE;
										}

										// ��ǰ �ڵ� �ߺ� üũ
										if (!m_SystemConfig.UseSystemOption(SOPT_DISABLE_CHECK_DUPLICIATION_CODE)) {

											if (!bOnErrorProduct &&
												!CheckProductCodeDuplicated(strProductCode, DIR_PRODUCT_CODE)) {

												ErrorMessage(TRUE, _T("[S%02d/%s] %s (%s)"),	nSTATION_NO, 
																								g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																								g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_DUPLICATED].szDescription[m_nTypeLanguage],
																								strProductCode);

												if (m_nTypeLanguage != LANGUAGE_KOR) {

													ErrorMessage(TRUE, _T("[S%02d/%s] %s (%s)"),	nSTATION_NO, 
																									g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																									g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_DUPLICATED].szDescription[LANGUAGE_KOR],
																									strProductCode);
												}

												nCodeStatus		= BCD_SCAN_DUPLICATE;
												nCodeWorkNG		= WORK_NG_CODE_DUPLCIATED;
												bOnErrorProduct	= TRUE;
											}
										}
									}

									// ��ǰ �ڵ� ����
									if (bOnErrorProduct) {
									
										// ������Ʈ UI
										PROCESS.bOnUpdateUI				= TRUE;
										PROCESS.stParamUI.nUpdateID		= UI_PRODUCT_CODE_IN;
										PROCESS.stParamUI.nStationNo	= nSTATION_NO;
										PROCESS.stParamUI.stProductCodeInfo.nStatusCodeInput = nCodeStatus;
										_tcscpy_s(PROCESS.stParamUI.stProductCodeInfo.szCodeInput, MAX_STRINPUT_L, strProductCode);

										// ������ ���
										m_stSystemStatus.nBeepCount = 2;

										// �÷��� ����
										bOnErrorProductCode = TRUE;

										PROCESS.nCurrentStep = 6090;
										break;
									}
								}

								if (!strProductCode.IsEmpty()) {
								
									// ���� ��ǰ �ڵ� ����
									SetCurrentProductCode(nSTATION_NO, strProductCode);

									PROCESS.nCurrentStep = 6020;
									break;
								}

								PROCESS.nCurrentStep = 6090;
							}

							break;

		// ������ �˻� üũ
		case	6020	:
							if (!PROCESS.bIsMasterProduct && m_SystemConfig.UseSystemOption(SOPT_ENABLE_CHECK_MASTER_TEST)) {
		
								if (!CheckMasterTest()) {

									// �޼��� ���
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[SYSSTR_MC_WARN_MASTER_TEST].szDescription[m_nTypeLanguage]);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[SYSSTR_MC_WARN_MASTER_TEST].szDescription[LANGUAGE_KOR]);
									}
								
									// ������ ���
									m_stSystemStatus.nBeepCount = 2;

									// ���� ��ǰ �ڵ� �ʱ�ȭ
									ClearCurrentProductCode(nSTATION_NO);

									// ����� �޼��� ����
									PROCESS.bOnSetUserMessage = SetUserMessage(UMSG_WARN_MASTER_TEST);
									LTimerProceed.Start(m_SystemConfig.GetDelaySystem(DLY_SYS_ACTION_SHOW_USER_MESSAGE));

									PROCESS.nCurrentStep++;
									break;
								}
							}

							PROCESS.nCurrentStep = 6090;
							break;

		case	6021	:
							if (LTimerProceed.Verify()) {

								// ����� �޼��� ����
								if (PROCESS.bOnSetUserMessage)	
									RestoreUserMessage();

								// �÷��� ����
								bOnErrorProductCode = TRUE;

								PROCESS.nCurrentStep = 6090;
							}

							break;

		// �Ϸ�
		case	6090	:
							PROCESS.nCurrentStep = PROCESS.nReturn03Step;
							break;


		/////////////////////////////////////////////////////////////
		// ��� /////////////////////////////////////////////////////
		case	STEP_STN_STANDBY	:
										// ���� �ɼ� ���
										if (m_stSystemStatus.bOnStationProcessStart)
											PROCESS.nCurrentStep = 210;

										break;

		// ���� ���� ����
		case	210		:
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_STANDBY;

							// ������Ʈ UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_STATUS_STATION;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;

							PROCESS.nCurrentStep = 220;
							break;

		// �غ� �۾�
		case	220		:
							// ����� �޼��� ����
							SetUserMessage(UMSG_STANDBY);

							// ���ڵ� ���� �ʱ�ȭ
							ClearBarcodeInfo(nBCS_INPUT_M);
							ClearBarcodeInfo(nBCS_INPUT_A);
							ClearCurrentProductCode(nSTATION_NO);

							PROCESS.nCurrentStep = 230;
							break;

		// ���� ��ư �Է� üũ
		case	230		:
							if (!GetDIStatus(DI_BTN_S01_START))
								PROCESS.nCurrentStep++;
							
							break;

		case	231		:
							if (GetDIStatus(DI_BTN_S01_START)) {
							
								// ��ư �Է� ����
								LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_PUSH_BUTTON));

								PROCESS.nCurrentStep++;
								break;
							}

							// �ùķ��̼� ���
							if (m_SystemConfig.IsSimulationMode()) {

								if (m_stSystemStatus.bOnSimulationStart[nSTATION_NO]) {

									m_stSystemStatus.bOnSimulationStart[nSTATION_NO] = FALSE;
									PROCESS.nCurrentStep = 250;
									break;
								}
							}

							break;

		case	232		:
							if (GetDIStatus(DI_BTN_S01_START)) {

								if (LTimerSensor.Verify()) {

									PROCESS.nCurrentStep = 235;
								}

								break;
							}

							PROCESS.nCurrentStep--;
							break;

		// �� ���� ���� üũ
		case	235		:
								if (m_stSystemStatus.stPrintStatus[BCP_PRINT_1].bIsLabelWaiting) {

									// �޼��� ���
									if (m_nTypeLanguage == LANGUAGE_KOR)	ErrorMessage(TRUE, _T("[S%02d/%s] ���� �̹� ����Ǿ� �ֽ��ϴ�."),	nSTATION_NO, g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);
									else									ErrorMessage(TRUE, _T("[S%02d/%s] LABEL IS ALREADY ISSUED."),	nSTATION_NO, g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);
									
									// ������ ���
									m_stSystemStatus.nBeepCount = 2;

									PROCESS.nCurrentStep = 230;
									break;
								}

								PROCESS.nCurrentStep = 240;
								break;

		// ��ǰ ���� �� Ŭ����, PIN S/W üũ
		case	240		:
							// ��ǰ �� PIN S/W ���� üũ
							if (GetDIStatus(DI_SENS_S01_DETECT_PRODUCT) && (m_SystemConfig.UseSystemOption(SOPT_ENABLE_CHECK_PIN_SW) ? GetDIStatus(DI_SENS_S01_DETECT_PIN_SW) : TRUE)) {

								LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_PRODUCT));

								PROCESS.nCurrentStep++;
								break;
							}

							LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_PRODUCT_NONE));

							PROCESS.nCurrentStep = 242;
							break;

		case	241		:
							if (GetDIStatus(DI_SENS_S01_DETECT_PRODUCT) && (m_SystemConfig.UseSystemOption(SOPT_ENABLE_CHECK_PIN_SW) ? GetDIStatus(DI_SENS_S01_DETECT_PIN_SW) : TRUE)) {

								if (LTimerSensor.Verify()) {

									PROCESS.nCurrentStep = 245;
								}

								break;
							}

							PROCESS.nCurrentStep--;
							break;

		case	242		:
							if (!GetDIStatus(DI_SENS_S01_DETECT_PRODUCT) || (m_SystemConfig.UseSystemOption(SOPT_ENABLE_CHECK_PIN_SW) ? !GetDIStatus(DI_SENS_S01_DETECT_PIN_SW) : FALSE)) {

								if (LTimerSensor.Verify()) {

									UINT	nSystemMessageID	= (m_SystemConfig.UseSystemOption(SOPT_ENABLE_CHECK_PIN_SW) && !GetDIStatus(DI_SENS_S01_DETECT_PRODUCT)) ? SYSSTR_MC_WARN_PRODUCT_NONE : SYSSTR_MC_WARN_DETECT_PIN_SW;

									// �޼��� ���
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[nSystemMessageID].szDescription[m_nTypeLanguage]);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[nSystemMessageID].szDescription[m_nTypeLanguage]);
									}

									// ������ ���
									m_stSystemStatus.nBeepCount = 2;

									PROCESS.nCurrentStep = 230;
								}

								break;
							}

							PROCESS.nCurrentStep = 240;
							break;

		case	245		:
							// ��ǰ Ŭ���� üũ
							if (GetDIStatus(DI_SENS_S01_CLAMP_1_ON) && GetDIStatus(DI_SENS_S01_CLAMP_2_ON)) {

								LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_PRODUCT));

								PROCESS.nCurrentStep++;
								break;
							}

							LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_PRODUCT_NONE));

							PROCESS.nCurrentStep = 247;
							break;

		case	246		:
							if (GetDIStatus(DI_SENS_S01_CLAMP_1_ON) && GetDIStatus(DI_SENS_S01_CLAMP_2_ON)) {

								if (LTimerSensor.Verify()) {

									PROCESS.nCurrentStep = 250;
								}

								break;
							}

							PROCESS.nCurrentStep--;
							break;

		case	247		:
							if (!GetDIStatus(DI_SENS_S01_CLAMP_1_ON) || !GetDIStatus(DI_SENS_S01_CLAMP_2_ON)) {

								if (LTimerSensor.Verify()) {

									// �޼��� ���
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CLAMP].szDescription[m_nTypeLanguage]);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CLAMP].szDescription[m_nTypeLanguage]);
									}

									// ������ ���
									m_stSystemStatus.nBeepCount = 2;

									PROCESS.nCurrentStep = 230;
								}

								break;
							}

							PROCESS.nCurrentStep = 245;
							break;

		// ���� üũ
		case	250		:
							{
								BOOL		bIsErrorState	= FALSE;
								UINT		nUserMessageID	= 0;
								CString		strErrorMessage	= _T("");


								// �ʱ�ȭ
								strMessage.Empty();

								// ���κ� ī���� üũ
								if (!bIsErrorState) {

									bIsErrorState |= m_stSystemStatus.bIsFullProbeCounter[nSTATION_NO];

									if (bIsErrorState) {

										strMessage.AppendFormat(_T(" %s\n %s\n"), g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage], g_stSystemString[SYSSTR_MC_WARN_EXPIRE_PROBE].szDescription[m_nTypeLanguage]);
										strMessage.AppendFormat(_T(" %s"), g_stSystemString[SYSSTR_MC_WARN_EXPIRE_PROBE_COMMENT].szDescription[m_nTypeLanguage]);
										strErrorMessage		= g_stSystemString[SYSSTR_MC_WARN_EXPIRE_PROBE_COMMENT].szDescription[m_nTypeLanguage];
										nUserMessageID		= UMSG_WARN_PROBE_COUNT_EXPIRED;
									}
								}

								// ���� ó��
								if (bIsErrorState) {

									// �޼��� ���
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			strErrorMessage);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[SYSSTR_MC_WARN_EXPIRE_PROBE_COMMENT].szDescription[LANGUAGE_KOR]);
									}

									// ����� �޼��� ����
									PROCESS.bOnSetUserMessage = SetUserMessage(nUserMessageID);

									PROCESS.nCurrentStep	= STEP_STN_MESSAGE_BOX_01;
									PROCESS.nReturn03Step	= 251;
									break;
								}

								PROCESS.nCurrentStep = 260;
							}

							break;

		case	251		:
							// ����� �޼��� ����
							if (PROCESS.bOnSetUserMessage)	
								RestoreUserMessage();

							PROCESS.nCurrentStep--;
							break;

		// ��ǰ �ڵ� üũ (���� ��ĵ)
		case	260		:
							if (!GetBarcodeInfo(nBCS_INPUT_M).IsEmpty()) {

								bOnCheckProductCodeEmpty = FALSE;
								bOnErrorProductCode		 = FALSE;

								PROCESS.nCurrentStep	 = STEP_STN_SCAN_CODE;
								PROCESS.nReturn03Step	 = 261;
								break;
							}

							PROCESS.nCurrentStep = 270;
							break;

		case	261		:
							if (bOnErrorProductCode) {
							
								PROCESS.nCurrentStep = 230;
								break;
							}

							PROCESS.nCurrentStep = 270;
							break;

		// ��ǰ ���� ���� üũ
		case	270		:
							if (GetDIStatus(DI_SENS_S01_DETECT_PRODUCT_DOOR)) {

								LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_PRODUCT));

								PROCESS.nCurrentStep++;
								break;
							}

							LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_PRODUCT_NONE));

							PROCESS.nCurrentStep = 272;
							break;

		case	271		:
							if (GetDIStatus(DI_SENS_S01_DETECT_PRODUCT_DOOR)) {

								if (LTimerSensor.Verify()) {

									PROCESS.nCurrentStep = 290;
								}

								break;
							}

							PROCESS.nCurrentStep--;
							break;

		case	272		:
							if (!GetDIStatus(DI_SENS_S01_DETECT_PRODUCT_DOOR)) {

								if (LTimerSensor.Verify()) {

									PROCESS.nCurrentStep++;
								}

								break;
							}

							PROCESS.nCurrentStep = 270;
							break;

		case	273		:
							if (!GetDIStatus(DI_SENS_S01_DETECT_PRODUCT_DOOR)) {

								if (LTimerProceed.Verify()) {
							
									// �޼��� ���
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[SYSSTR_MC_WARN_PRODUCT_DOOR_OPENED].szDescription[m_nTypeLanguage]);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[SYSSTR_MC_WARN_PRODUCT_DOOR_OPENED].szDescription[m_nTypeLanguage]);
									}

									// ������ ���
									m_stSystemStatus.nBeepCount = 2;

									// Ÿ�̸� ����
									LTimerProceed.Start(m_SystemConfig.GetDelaySystem(DLY_SYS_INTV_USER_WARNING_MESSAGE));
								}

								break;
							}

							PROCESS.nCurrentStep = 270;
							break;

		// ��ǰ ���� ���� �ҷ�
		case	280		:
							// �޼��� ���
							ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																	g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																	g_stSystemString[SYSSTR_MC_WARN_PRODUCT_DOOR_STATUS].szDescription[m_nTypeLanguage]);

							if (m_nTypeLanguage != LANGUAGE_KOR) {

								ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																		g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																		g_stSystemString[SYSSTR_MC_WARN_PRODUCT_DOOR_STATUS].szDescription[m_nTypeLanguage]);
							}

							// ������ ���
							m_stSystemStatus.nBeepCount = 2;

							// ����� �޼��� ����
							SetUserMessage(UMSG_WARN_PRODUCT_DOOR_LOCK);
							LTimerProceed.Start(m_SystemConfig.GetDelaySystem(DLY_SYS_ACTION_SHOW_USER_MESSAGE));

							// ��-Ÿ�� ����
							m_pTactTimerWnd[nSTATION_NO]->PostMessage(UM_TACT_TIMER_STATE, TACT_STOP);

							PROCESS.nCurrentStep++;
							break;

		case	281		:
							if (LTimerProceed.Verify()) {
							
								// ����� �޼��� ����
								RestoreUserMessage();
								SetUserMessage(UMSG_STANDBY);

								PROCESS.nCurrentStep = 230;
							}

							break;

		// �Ϸ�
		case	290		:
							// ������ ���
							m_stSystemStatus.nBeepCount = 1;

							// ����� �޼��� ����
							SetUserMessage(UMSG_PREPARING);

							// ������Ʈ UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_WORK_SHEET_01 | UI_WORK_SHEET_02 | UI_VISION_SHEET | UI_PRODUCT_CODE_OUT;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;
							PROCESS.stParamUI.stWorkSheet.bOnClear	= TRUE;

							// ��-Ÿ�� ����
							m_pTactTimerWnd[nSTATION_NO]->PostMessage(UM_TACT_TIMER_STATE, TACT_PROCEED);

							PROCESS.nCurrentStep  = STEP_STN_SUB_02;
							PROCESS.nReturn02Step = 291;
							break;

		case	291		:
							PROCESS.nCurrentStep = PROCESS.bOnInterLock ? 280 : STEP_STN_WORK;
							break;


		/////////////////////////////////////////////////////////////
		// �۾� /////////////////////////////////////////////////////
		case	STEP_STN_WORK	:
									PROCESS.nCurrentStep = 2010;
									break;

		// ���� ���� ����
		case	2010	:
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_PROCEED;

							// ������Ʈ UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_STATUS_STATION;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;

							PROCESS.nCurrentStep = 2050;
							break;

		// ��ǰ �ڵ� üũ (�ڵ� ��ĵ)
		case	2050	:
							if (GetCurrentProductCode(nSTATION_NO).IsEmpty()) {

								PROCESS.nRetryCount = 0;
								PROCESS.nCurrentStep++;
								break;
							}

							PROCESS.nCurrentStep = 2100;
							break;

		case	2051	:
							if (LTimerSteadyScan.Verify()) {

								ClearBarcodeInfo(nBCS_INPUT_A);
								SetTrigBarcode(nBCS_INPUT_A);
								LTimerTimeOutScan.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_BARCODE_AUTO_SCAN_1));

								PROCESS.nCurrentStep++;
							}

							break;

		case	2052	:
							if (!GetBarcodeInfo(nBCS_INPUT_A).IsEmpty()) {

								// �޼��� ���
								NormalMessage(TRUE, _T("[%s] AUTO SCAN PRODUCT CODE = %s"),	g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage], 
																							GetBarcodeInfo(nBCS_INPUT_A));

								bOnCheckProductCodeEmpty = TRUE;
								bOnErrorProductCode		 = FALSE;

								PROCESS.nCurrentStep	 = STEP_STN_SCAN_CODE;
								PROCESS.nReturn03Step	 = 2053;
								break;
							}

							// ��ĵ Ÿ�� �ƿ�
							if (LTimerTimeOutScan.Verify()) {

								// ���ڵ� ��ĳ�� Ʈ���� ����
								SetTrigBarcode(nBCS_INPUT_A, FALSE);
								LTimerSteadyScan.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_BCD_CONTROL));

								if (++PROCESS.nRetryCount >= MAX_RETRY_BCD_SCAN) {

									// �޼��� ���
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_SCAN].szDescription[m_nTypeLanguage]);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_SCAN].szDescription[LANGUAGE_KOR]);
									}

									// ������ ���
									m_stSystemStatus.nBeepCount = 2;

									PROCESS.nCurrentStep = 2060;
									break;
								}

								PROCESS.nCurrentStep--;
							}

							break;

		case	2053	:
							if (bOnErrorProductCode) {
							
								PROCESS.nCurrentStep = 2060;
								break;
							}

							PROCESS.nCurrentStep = 2100;
							break;

		// �ε� ���� : FWD
		case	2060	:
							pOnSCP_MoveParts[SCP_S01_LOADING_FWD] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	2061	:
							if (!pOnSCP_MoveParts[SCP_S01_LOADING_FWD])
								PROCESS.nCurrentStep = STEP_STN_STANDBY;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// �غ� �۾�
		case	2100	:
							// �۾� ���� ���� �ʱ�ȭ
							InitWorkStatus(nSTATION_NO);
							_tcscpy_s((PROCESS.pstWorkStatus)->szProductCode, MAX_STRINPUT_S, GetCurrentProductCode(nSTATION_NO));

							// ���� �˻� �ʱ�ȭ
							InitVisionTest();

							// ���� ���� �˻� �۾� ��Ʈ ������Ʈ ��ȣ �ʱ�ȭ
							m_stSystemStatus.nCurrentVisionWorkSheetUpdateNo = 0;

							// �� ���� ���ͷ� ����
							m_stSystemStatus.bOnInterlockViewDetail = TRUE;

							// �۾� ��� ���丮 ����
							CreateWorkResultDirectory(nSTATION_NO);

							// ���� �̹��� ������ �ʱ�ȭ
							if (m_pMainWnd)	{
								
								m_stSystemStatus.bIsVisionImageWindowCleared = FALSE;
								m_pMainWnd->PostMessage(UM_VISION_CLEAR_IMAGE);
							}

							PROCESS.nCurrentStep = 2110;
							break;

		// ���κ� ���̵� : ON
		case	2110	:
							pOnSCP_MoveParts[SCP_S01_PROBE_GUIDE_ON] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	2111	:
							if (!pOnSCP_MoveParts[SCP_S01_PROBE_GUIDE_ON])
								PROCESS.nCurrentStep = 2120;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// ���κ� : ON
		case	2120	:
							pOnSCP_MoveParts[SCP_S01_PROBE_ON] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	2121	:
							if (!pOnSCP_MoveParts[SCP_S01_PROBE_ON])
								PROCESS.nCurrentStep = 2200;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// ���� �۾� ����
		case	2200	:
							// ���μ��� ��� ����
							m_stSystemStatus.bIsStationProcessLock[nSTATION_NO][nSTATION_SUB_NO] = TRUE;

							// ���� ���μ��� ����
							m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	2201	:
							if (!m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]) {

								// ���� ���μ��� ��� ����
								PROCESS.bResultMainProcess = m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO];

								PROCESS.nCurrentStep = 2250;
							}

							break;

		// ��ε�
		case	2250	:
							pOnSCP_MoveParts[SCP_S01_UNLOADING] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	2251	:
							if (!pOnSCP_MoveParts[SCP_S01_UNLOADING])
								PROCESS.nCurrentStep = 2280;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// ��� ��ġ �̵�
		case	2280	:
							PROCESS.nCurrentStep  = STEP_STN_HOME;
							PROCESS.nReturn02Step = 2290;
							break;

		// ���� �۾� ���հ� �� ���۾�
		case	2290	:
							// ��� ����

							PROCESS.nCurrentStep = 2300;
							break;

		// ��ǰ ���� ���� üũ
		case	2300	:
							if (GetDIStatus(DI_SENS_S01_DETECT_PRODUCT_DOOR)) {

								LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_PRODUCT));

								PROCESS.nCurrentStep++;
								break;
							}

							LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_PRODUCT_NONE));

							PROCESS.nCurrentStep = 2302;
							break;

		case	2301	:
							if (GetDIStatus(DI_SENS_S01_DETECT_PRODUCT_DOOR)) {

								if (LTimerSensor.Verify()) {

									PROCESS.nCurrentStep = 2320;
								}

								break;
							}

							PROCESS.nCurrentStep--;
							break;

		case	2302	:
							if (!GetDIStatus(DI_SENS_S01_DETECT_PRODUCT_DOOR)) {

								if (LTimerSensor.Verify()) {

									PROCESS.nCurrentStep = 2310;
								}

								break;
							}

							PROCESS.nCurrentStep = 2300;
							break;

		// ��ǰ ���� �ݱ�
		case	2310	:
							PROCESS.nCurrentStep  = STEP_STN_SUB_03;
							PROCESS.nReturn02Step = 2320;
							break;

		// ��� ��ġ �̵�
		case	2320	:
							PROCESS.nCurrentStep  = STEP_STN_HOME;
							PROCESS.nReturn02Step = 2330;
							break;

		// �ε� ���� : FWD
		case	2330	:
							pOnSCP_MoveParts[SCP_S01_LOADING_FWD] = TRUE;

							PROCESS.nCurrentStep = 2380;
							break;

		// �۾� ��� ����
		case	2380	:
							// �۾� ���� ���� ����
							(PROCESS.pstWorkStatus)->nResultFinal = PROCESS.bResultMainProcess ? T_RESULT_SUCCESS : T_RESULT_FAILURE;

							// ���μ��� ��� ����
							m_stSystemStatus.bIsStationProcessLock[nSTATION_NO][nSTATION_SUB_NO] = FALSE;

							// ��-Ÿ�� ����
							m_pTactTimerWnd[nSTATION_NO]->PostMessage(UM_TACT_TIMER_STATE, TACT_STOP);

							// ���� ���� ����
							if (!PROCESS.bIsMasterProduct) {

								m_pProductionWnd->SetCumulativeCount();
								m_pProductionWnd->SetProductionCount(PROCESS.bResultMainProcess);
							}

							PROCESS.nCurrentStep++;
							break;
		
		case	2381	:
							// �� ��� ����
							if (!m_SystemConfig.IsTestMode() && !PROCESS.bIsMasterProduct && m_stSystemStatus.bUsePrintLabel && PROCESS.bResultMainProcess) {

								UINT		nPrintQuantity	= 1;
								CString		strOutputCode	= _T("");
							

								if (nPrintQuantity) {

									// �� ���� ����
									CreateLabelFormat(BCP_PRINT_1, *PROCESS.pstLabelPrintInfo, nPrintQuantity, 0, &strOutputCode);
									_tcscpy_s((PROCESS.pstWorkStatus)->szOutputCode, MAX_STRINPUT_S, strOutputCode);

									// ������Ʈ UI
									PROCESS.bOnUpdateUI				= TRUE;
									PROCESS.stParamUI.nUpdateID		= UI_PRODUCT_CODE_OUT;
									PROCESS.stParamUI.nStationNo	= nSTATION_NO;
									_tcscpy_s(PROCESS.stParamUI.stProductCodeInfo.szCodeOutput, MAX_STRINPUT_L, strOutputCode);

									// �� ��� ����
									m_stSystemStatus.bOnPrintLabel[BCP_PRINT_1]	= TRUE;
								}
							}

							PROCESS.nCurrentStep++;
							break;

		case	2382	:
							// �۾� ��Ʈ ����
							SaveWorkSheet01(PROCESS.bIsMasterProduct);
							SaveWorkSheet01T(PROCESS.bIsMasterProduct);
							SaveWorkSheetERP_01(PROCESS.bIsMasterProduct);

							// ��ǰ �ڵ� ���� ����
							if ((PROCESS.pstWorkStatus)->nResultFinal == T_RESULT_SUCCESS) {
							
								PRODUCT_CODE_INFO_T	stProductCodeInfo;
								ZeroMemory(&stProductCodeInfo, sizeof(PRODUCT_CODE_INFO_T));

								_tcscpy_s(stProductCodeInfo.szProductCode, MAX_STRINPUT_S, (PROCESS.pstWorkStatus)->szProductCode);

								if (!SaveProductCodeFile(stProductCodeInfo, DIR_PRODUCT_CODE)) {

									ErrorMessage(TRUE,	_T("[S%02d/%s] CREATE PRODUCT CODE FILE ERROR!"),	
														nSTATION_NO + 1, 
														g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);
								}
							}

							// ���� ī���� ����
							m_stWorkSubCounter.nCountStation[nSTATION_NO]++;
							SaveWorkSubCounter();

							// ���� ���� ����
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_COMPLETE;

							// �� ���� ���ͷ� ����
							m_stSystemStatus.bOnInterlockViewDetail = FALSE;

							// ������Ʈ UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_STATUS_STATION | UI_SUB_COUNTER;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;

							// ����� �޼��� ����
							SetUserMessage(UMSG_COMPLETE);

							PROCESS.nCurrentStep = 2390;
							break;

		// �ε� ���� Ȯ�� : FWD
		case	2390	:
							if (!pOnSCP_MoveParts[SCP_S01_LOADING_FWD])
								PROCESS.nCurrentStep = 2400;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// ���հ� ���� �� ����� ����
		case	2400	:
							if (!m_SystemConfig.IsTestMode() && !PROCESS.bIsMasterProduct && (PROCESS.pstWorkStatus)->nResultFinal != T_RESULT_SUCCESS) {
							
								PROCESS.nCurrentStep	= STEP_STN_USER_UNLOAD;
								PROCESS.nReturn01Step	= 2900;
								break;
							}

							// ������ ��� (�հ� ���� ��)
							m_stSystemStatus.nBeepCount = 3;

							PROCESS.nCurrentStep = 2410;
							break;

		// �� ��� Ȯ��
		case	2410	:
							if (!m_stSystemStatus.bOnPrintLabel[BCP_PRINT_1])
								PROCESS.nCurrentStep = 2800;
							
							break;

		// ��ǰ ���� Ȯ��
		case	2800	:
							if (m_SystemConfig.IsTestMode())
								PROCESS.nCurrentStep = 2900;

							if (!GetDIStatus(DI_SENS_S01_DETECT_PRODUCT) && !GetDIStatus(DI_SENS_S01_CLAMP_1_ON) && !GetDIStatus(DI_SENS_S01_CLAMP_1_ON))
								PROCESS.nCurrentStep = 2900;

							break;

		// �Ϸ�
		case	2900	:
							// ���� ���� ����
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_NONE;

							// ������Ʈ UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_STATUS_STATION;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;

							// ������ �˻� �Ϸ� ����
							m_stSystemStatus.bIsMasterTestComplete = CheckMasterTest();

							PROCESS.nCurrentStep = m_SystemConfig.IsTestMode() ? 290 : STEP_STN_STANDBY;
							break;


		/////////////////////////////////////////////////////////////
		// ����� ���� //////////////////////////////////////////////
		case	STEP_STN_USER_UNLOAD	:
											PROCESS.nCurrentStep = 3020;
											break;

		// �޼��� �ڽ� ���
		case	3020	:
							// �޼��� �ڽ��� ��� ���� üũ
							if (!m_stSystemStatus.bIsDisplayMessageBox) {
							
								m_stSystemStatus.bIsDisplayMessageBox = TRUE;

								PROCESS.nCurrentStep++;
							}

							break;

		case	3021	:
							// �޼��� ���
							ErrorMessage(TRUE, _T("[S%02d/%s] �ҷ� ��ǰ�� ���� �� �ҷ��Կ� ������ �ֽʽÿ�."), nSTATION_NO + 1, g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

							// �ý��� �÷��� ����
							m_stSystemStatus.bOnWaitForUser			= TRUE;				// ����� �Է� ��� ����
							m_stSystemStatus.bOnBuzzer				= TRUE;				// ����� ���
							m_stSystemStatus.nMessageBoxButtonCode	= MBOX_BCODE_NONE;	// ��ư �ڵ� �ʱ�ȭ

							// �޼��� �ڽ� ����
							PROCESS.pstMBoxParam = new MBOX_PARAM_T;
							if (PROCESS.pstMBoxParam) {

								CString		strValue = _T("");

								strValue.AppendFormat(_T("\n [����� �ҷ� ����]\n\n"));
								strValue.AppendFormat(_T(" ���� ���� �˻� ���հ� ��ǰ�Դϴ�.\n"));
								strValue.AppendFormat(_T(" ��ǰ�� ���� �� �ҷ��Կ� ������ �ֽʽÿ�."));
	
								ZeroMemory(PROCESS.pstMBoxParam, sizeof(MBOX_PARAM_T));
								_stprintf_s((PROCESS.pstMBoxParam)->szButtonTitle[MBOX_BUTTON_0], MAX_STRINPUT, _T("����� ����\n(ESC)"));
								_stprintf_s((PROCESS.pstMBoxParam)->szMessage, MAX_STRVALUE, _T("%s"), strValue);

								(PROCESS.pstMBoxParam)->bEnableButton[MBOX_BUTTON_0]	= TRUE;
								(PROCESS.pstMBoxParam)->nTypeButton[MBOX_BUTTON_0]		= MBOX_BTYPE_NORMAL;
								(PROCESS.pstMBoxParam)->bEnableShortCutKey				= TRUE;
								(PROCESS.pstMBoxParam)->nKeyShortCut[MBOX_BUTTON_0]		= VK_ESCAPE;
								(PROCESS.pstMBoxParam)->nMessageFontSize				= 26;
								(PROCESS.pstMBoxParam)->bEnableSetWindowPos				= TRUE;
								(PROCESS.pstMBoxParam)->ptWindowPosition				= m_SystemConfig.GetMBoxWindowPosition();
								m_pMessageBoxDlg->SendMessage(UM_DPS_DLG_MESSAGE_BOX_SHOWHIDE, SW_SHOW, (LPARAM)(PROCESS.pstMBoxParam));

								PROCESS.nCurrentStep++;
								break;
							}

							// ������ 2ȸ ���
							m_stSystemStatus.nBeepCount	= 2;

							SErrorMessage(TRUE, _T("[S%02d/%s] �޼��� �ڽ��� ������ �� �����ϴ�."),	nSTATION_NO + 1, 
																									g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

							PROCESS.nCurrentStep++;
							break;

		case	3022	:
							if (m_stSystemStatus.nMessageBoxButtonCode != MBOX_BCODE_NONE) {

								// ��ư 1 : ����� ����
								if (m_stSystemStatus.nMessageBoxButtonCode == MBOX_BCODE_0) {

									m_stSystemStatus.bOnBuzzer				= FALSE;			// ����� ����
									m_stSystemStatus.nMessageBoxButtonCode	= MBOX_BCODE_NONE;	// ��ư �ڵ� �ʱ�ȭ
								}
							}

							// �ҷ��� ���� üũ
							if (!GetDIStatus(DI_SENS_S01_DETECT_PRODUCT) && 
								!GetDIStatus(DI_SENS_S01_CLAMP_1_ON) && 
								!GetDIStatus(DI_SENS_S01_CLAMP_1_ON) &&
								(m_SystemConfig.UseSystemOption(SOPT_DISABLE_CHECK_NG_BOX) || GetDIStatus(DI_SENS_S01_DETECT_NG_BOX))) {

								// �޼��� ���
								ErrorMessage(TRUE, _T("[S%02d/%s] �ҷ��Կ� ��ǰ ������ �Ϸ�Ǿ����ϴ�."), nSTATION_NO + 1, g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3023	:
							// �޼��� �ڽ� ��� �÷��� ����
							m_stSystemStatus.bIsDisplayMessageBox = FALSE;

							// �޼��� �ڽ� ���߱�	
							m_pMessageBoxDlg->SendMessage(UM_DPS_DLG_MESSAGE_BOX_SHOWHIDE, SW_HIDE, NULL);

							// �ý��� �÷��� ����
							m_stSystemStatus.bOnWaitForUser	= FALSE;	// ����� �Է� ��� ����
							m_stSystemStatus.bOnBuzzer		= FALSE;	// ����� ����

							PROCESS.nCurrentStep = 3090;
							break;

		// �Ϸ�
		case	3090	:
							PROCESS.nCurrentStep = PROCESS.nReturn01Step;
							break;


		/////////////////////////////////////////////////////////////
		// �۾� ���� ���� ///////////////////////////////////////////
		case	STEP_STN_WAIT_STOP	:
										if (!m_stSystemStatus.bOnOperatingStopReservated) {

											PROCESS.bIsStopReservated	= FALSE;
											PROCESS.nCurrentStep		= PROCESS.nRecoveryStopStep;
										}

										break;


		/////////////////////////////////////////////////////////////
		// ���� /////////////////////////////////////////////////////
		case	STEP_STN_ERROR	:
									PROCESS.bOnOperatingStop = TRUE;
									break;

		case	STEP_STN_ERROR_PARTS	:
											if (PROCESS.bOnMachineInitialize) {
											
												m_stSystemStatus.bOnStationInitializeResult[nSTATION_NO][nSTATION_SUB_NO] = FALSE;
												PROCESS.nCurrentStep = PROCESS.nReturn01Step;
												break;
											}

											PROCESS.bOnError				= TRUE;
											PROCESS.nRecoveryStep			= STEP_STN_ERROR;
											PROCESS.stErrorCode.nErrorCode	= ERROR_MACHINE_SEQUENCE;
											PROCESS.stErrorCode.nProcessID	= PROCESS_STATION;
											PROCESS.stErrorCode.nStationNo	= nSTATION_NO;

											// ����� �޼���
											SDebugMessage(TRUE, _T("[S%02d] ERROR PARTS"), nSTATION_NO);
											break;

		case	STEP_STN_ERROR_SYSTEM	:
											// ����� �޼���
											SDebugMessage(TRUE, _T("[S%02d] ERROR SYSTEM"), nSTATION_NO);
											break;


		/////////////////////////////////////////////////////////////
		// �Ͻ� ���� ���� ///////////////////////////////////////////
		case	STEP_PAUSE	:
								if (m_stSystemStatus.bOnEmergencyStop) {

									PROCESS.nCurrentStep = STEP_EMG;
									break;
								}

								PROCESS.nCurrentStep++;
								break;

		case	20001	:
							if (!m_stSystemStatus.bOnPause && !m_stSystemStatus.bOnAlarmSystem && !m_stSystemStatus.bOnAlarmStation[nSTATION_NO]) {

								PROCESS.nCurrentStep = 20100;
							}

							break;

		// ���� ����
		case	20100	:
							PROCESS.nCurrentStep	= PROCESS.nRecoveryStep;
							PROCESS.bOnPause		= FALSE;
							break;


		/////////////////////////////////////////////////////////////
		// ��� ���� ���� ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop)	{

									PROCESS.nRecoveryStep	= 0;
									PROCESS.nCurrentStep	= 20001;
								}

								break;


		/////////////////////////////////////////////////////////////
		// ��� �ʱ�ȭ ���� /////////////////////////////////////////
		case	STEP_MC_INIT	:
									PROCESS.nCurrentStep = 22010;
									break;

		case	22010	:
							// ���� �ʱ�ȭ
							if (m_stSystemStatus.bOnStationInitialize[nSTATION_NO][nSTATION_SUB_NO]) {

								PROCESS.nCurrentStep	= STEP_STN_INIT;
								PROCESS.nReturn01Step	= 22011;
							}

							break;

		case	22011	:
							m_stSystemStatus.bOnStationInitialize[nSTATION_NO][nSTATION_SUB_NO] = FALSE;

							PROCESS.nCurrentStep = 22020;
							break;

		case	22020	:
							if (!m_stSystemStatus.bOnMachineInitialize) {
							
								PROCESS.bIsOperatingStop		= FALSE;
								PROCESS.bOnMachineInitialize	= FALSE;
								PROCESS.nCurrentStep			= PROCESS.nRecoveryStep;
							}

							break;
	}
	

	/////////////////////////////////////////////////////////////////
	// ���� ���� üũ ///////////////////////////////////////////////
	CheckProcessOperatingStop(PROCESS);


	/////////////////////////////////////////////////////////////////
	// �Ϲ� /////////////////////////////////////////////////////////
	CheckProcessGeneral(nSTATION_NO, PROCESS);


	/////////////////////////////////////////////////////////////////
	// ���� ����͸� ////////////////////////////////////////////////
	if (LTimerSystemMonitor.Verify()) {

		if (PROCESS.nPrevStep != PROCESS.nCurrentStep) {

			PROCESS.nPrevStep = PROCESS.nCurrentStep;
			if (m_pSysMonitorDlg && m_pSysMonitorDlg->GetSafeHwnd()) {

				m_pSysMonitorDlg->PostMessage(UM_SYSM_UPDATE_STEP, PSTEP_PROC_STATION_01, PROCESS.nCurrentStep);
				LTimerSystemMonitor.Start(DLY_REFRESH_SYSTEM_MONITOR);
			}
		}
	}


	return	PROCESS.pstErrorCode;
}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� : ���� #02 - �˻� ���� (SK) ///////////////////////////////////////
PERROR_CODE_T CMainApp::ProcessStation02(void)
{
	static	PROCESS_CTRL_T		PROCESS;

	static	UINT				nSTATION_NO					= STATION_1;
	static	UINT				nSTATION_SUB_NO				= STN1_SUB_NONE;

	static	UINT				nBCS_INPUT_M				= BCS_INPUT_1;
	static	UINT				nBCS_INPUT_A				= BCS_INPUT_2;

			PBOOL				pOnSCP_MoveParts			= m_stSystemStatus.bOnSCP_MoveParts[nSTATION_NO];
	static	UINT				nSCP_PARTS_ID				= 0;

	static	CString				strMessage					= _T("");
	static	BOOL				bOnCheckProductCodeEmpty	= FALSE;
	static	BOOL				bOnErrorProductCode			= FALSE;

	static	LTimerMsec			LTimerProceed;
	static	LTimerMsec			LTimerSubProceed;
	static	LTimerMsec			LTimerAlarm;
	static	LTimerMsec			LTimerSensor;
	static	LTimerMsec			LTimerSteady;
	static	LTimerMsec			LTimerSteadyScan;
	static	LTimerMsec			LTimerTimeOut;
	static	LTimerMsec			LTimerTimeOutScan;
	static	LTimerMsec			LTimerButton;
	static	LTimerMsec			LTimerWaitProduct;
	static	LTimerMsec			LTimerWaitPallet;
	static	LTimerMsec			LTimerUserProcess;
	static	LTimerMsec			LTimerSystemMonitor;
	static	LTimerMsec			LTimerSystemDisplay;


	/////////////////////////////////////////////////////////////////
	// ���μ��� ������ �ʱ�ȭ ///////////////////////////////////////
	ProcessDataInitialize(PROCESS);


	/////////////////////////////////////////////////////////////////
	// �ڵ� ���� ����/���� �ʱ�ȭ ///////////////////////////////////
	CheckProcessOperating(PROCESS);


	/////////////////////////////////////////////////////////////////
	// ��� �ʱ�ȭ //////////////////////////////////////////////////
	if (CheckProcessMachineInitialize(PROCESS))
		return	NULL;


	/////////////////////////////////////////////////////////////////
	// �۾� ���� ���� ///////////////////////////////////////////////
	if (CheckProcessOperatingStopReservated(nSTATION_NO, nSTATION_SUB_NO, PROCESS))
		return	NULL;


	/////////////////////////////////////////////////////////////////
	// ���� ���� ��� ///////////////////////////////////////////////
	if (CheckProcessManualControlMode(nSTATION_NO, PROCESS))
		return	NULL;
	

	/////////////////////////////////////////////////////////////////
	// ���/�Ͻ� ���� ���� //////////////////////////////////////////
	if (CheckProcessEmergencyStop(PROCESS))					return	NULL;
	if (CheckProcessOperatingPause(nSTATION_NO, PROCESS))	return	NULL;


	/////////////////////////////////////////////////////////////////
	// ���� ���μ��� ////////////////////////////////////////////////
	switch (PROCESS.nCurrentStep) {

		case	0		:
							PROCESS.nCurrentStep = 10;
							break;

		// �ý��� üũ
		case	10		:
							if (IsSystemReady()) {
							
								PROCESS.nCurrentStep = 20;
							}
								
							break;

		// �÷��� �ʱ�ȭ
		case	20		:
							// ���� ���μ��� ������ �ʱ�ȭ
							StationProcessDataInitialize(nSTATION_NO, nSTATION_SUB_NO, PROCESS);

							PROCESS.nCurrentStep = 30;
							break;

		// ���� �ʱ�ȭ
		case	30		:
							// ���ڵ� ��ĳ�� Ʈ���� ����
							SetTrigBarcode(nBCS_INPUT_M, FALSE);
							SetTrigBarcode(nBCS_INPUT_A, FALSE);

							PROCESS.nCurrentStep = 40;
							break;

		// ���� ���� ����
		case	40		:
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_NONE;

							PROCESS.nCurrentStep = 50;
							break;

		// �ڵ� ���� üũ
		case	50		:
							if (m_stSystemStatus.bOnOperating) {

								PROCESS.nCurrentStep = 60;
							}

							break;

		// �� �������� �ε�
		case	60		:
							PROCESS.pstModelProfile	= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
							PROCESS.pstWorkStatus	= GetWorkStatus(nSTATION_NO);

							if (PROCESS.pstModelProfile != NULL) {

								PROCESS.pstModelProfileConfig	= &(PROCESS.pstModelProfile)->stModelProfileConfig;
								PROCESS.pstWorkInfo				= &(PROCESS.pstModelProfileConfig)->stWorkInfo;
								PROCESS.pstStationSetupInfo		= &(PROCESS.pstModelProfileConfig)->stSpBasicSetupInfo;
								PROCESS.pstLabelPrintInfo		= &(PROCESS.pstModelProfileConfig)->stSpLabelPrintSetupInfo.stLabelPrintInfo;
								PROCESS.pstMiscellaneousInfo	= &(PROCESS.pstModelProfileConfig)->stSpMiscellaneousInfo;
								PROCESS.pstWorkPositionInfo		= (PROCESS.pstModelProfileConfig)->stSpBasicSetupInfo.stWorkPositionSheet;

								PROCESS.nCurrentStep = 90;
								break;
							}

							SErrorMessage(TRUE, _T("[S%02d/%s] �� ������ �ε��� �� �����ϴ�."),	nSTATION_NO, 
																									g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

							PROCESS.nCurrentStep = STEP_STN_ERROR_SYSTEM;
							break;

		// �Ϸ�
		case	90		:
							PROCESS.nCurrentStep	= STEP_STN_INIT;
							PROCESS.nReturn01Step	= STEP_STN_STANDBY;
							break;


		/////////////////////////////////////////////////////////////
		// �ʱ�ȭ ///////////////////////////////////////////////////
		case	STEP_STN_INIT	:
									PROCESS.nCurrentStep = 110;
									break;

		// �÷��� �ʱ�ȭ
		case	110		:
							m_stSystemStatus.bOnStationInitializeResult[nSTATION_NO][nSTATION_SUB_NO]	= TRUE;
							m_stSystemStatus.bIsStationProcessLock[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;

							PROCESS.nCurrentStep = 120;
							break;

		// ���� ���� ����
		case	120		:
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_NONE;

							// ������Ʈ UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_STATUS_STATION;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;

							PROCESS.nCurrentStep = 130;
							break;

		// ���� �ʱ�ȭ
		case	130		:
							// ���� ������ �ʱ�ȭ
							SetDOStatus(DO_OFF, DO_RLY_S01_PRODUCT_POWER_ON);
							SetDOStatus(DO_OFF, DO_RLY_S01_BYPASS_ON);
							SetDOStatus(DO_OFF, DO_RLY_S01_CONN_P);
							SetDOStatus(DO_OFF, DO_RLY_S01_CONN_N);
							SetDOStatus(DO_OFF, DO_RLY_S01_RANGE_mA);
							SetDOStatus(DO_OFF, DO_RLY_S01_RANGE_A);
							SetDOStatus(DO_OFF, DO_RLY_S01_MEAS_CURRENT);
							SetDOStatus(DO_OFF, DO_RLY_S01_CONN_BATT);
							SetDOStatus(DO_OFF, DO_RLY_S01_CONN_IGN);
							SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_CHECK);
							SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_LOCK_ON);
							SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_LOCK_OFF);

							// ���� Ʈ���� ����
							SetDOStatus(DO_OFF, DO_SIG_S02_VISION_TRIG);	
							
							// ���ڵ� ��ĳ�� Ʈ���� ����
							SetTrigBarcode(nBCS_INPUT_M, FALSE);
							SetTrigBarcode(nBCS_INPUT_A, FALSE);

							PROCESS.nCurrentStep = 140;
							break;

		// �۾� ��� ��ġ �̵�
		case	140		:
							PROCESS.nCurrentStep = 150;
							break;

		// �۾� ���� �ʱ�ȭ
		case	150		:
							if (!PROCESS.bOnMachineInitialize) {

								PROCESS.nCurrentStep	= STEP_STN_SUB_01;
								PROCESS.nReturn02Step	= 190;
								break;
							}

							PROCESS.nCurrentStep = 190;
							break;

		// �Ϸ�
		case	190		:
							// �ʱ�ȭ �Ϸ� �÷��� ����
							m_stSystemStatus.bOnStationInitializeComplete[nSTATION_NO][nSTATION_SUB_NO] = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn01Step;
							break;


		/////////////////////////////////////////////////////////////
		// �۾� ���� �ʱ�ȭ /////////////////////////////////////////
		case	STEP_STN_SUB_01	:
									PROCESS.nCurrentStep = 8010;
									break;

		// �غ� �۾�
		case	8010	:
							PROCESS.nCurrentStep = 8020;
							break;

		// ��ǰ ���� ���� : UP
		case	8020	:
							pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_A_UP] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	8021	:
							if (!pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_A_UP])
								PROCESS.nCurrentStep = 8030;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// ���κ� : OFF
		case	8030	:
							pOnSCP_MoveParts[SCP_S02_PROBE_OFF] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	8031	:
							if (!pOnSCP_MoveParts[SCP_S02_PROBE_OFF])
								PROCESS.nCurrentStep = 8040;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// ���� ���� ���� : DN
		case	8040	:
							pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_OPEN_DN] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	8041	:
							if (!pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_OPEN_DN])
								PROCESS.nCurrentStep = 8080;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// ...?
		case	8080	:
							PROCESS.nCurrentStep = 8090;
							break;

		// �Ϸ�
		case	8090	:
							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// �޼��� �ڽ� ��� /////////////////////////////////////////
		case	STEP_STN_MESSAGE_BOX_01	:
											PROCESS.nCurrentStep = 9010;
											break;

		case	9010	:
							// �޼��� �ڽ��� ��� ���� üũ
							if (!m_stSystemStatus.bIsDisplayMessageBox) {
							
								m_stSystemStatus.bIsDisplayMessageBox = TRUE;

								PROCESS.nCurrentStep++;
							}

							break;

		case	9011	:
							// �ý��� �÷��� ����
							m_stSystemStatus.bOnWaitForUser			= TRUE;				// ����� �Է� ��� ����
							m_stSystemStatus.bOnBuzzer				= TRUE;				// ����� ���
							m_stSystemStatus.nMessageBoxButtonCode	= MBOX_BCODE_NONE;	// ��ư �ڵ� �ʱ�ȭ

							// �޼��� �ڽ� ����
							PROCESS.pstMBoxParam = new (std::nothrow) MBOX_PARAM_T;
							if (PROCESS.pstMBoxParam) {

								CString		strValue = _T("");

								strValue.AppendFormat(_T("\n%s\n"), strMessage);
								strValue.AppendFormat(_T(" %s"), g_stSystemString[SYSSTR_INFO_PRESS_CONFIRM_CONTINUE].szDescription[m_nTypeLanguage]);
	
								ZeroMemory(PROCESS.pstMBoxParam, sizeof(MBOX_PARAM_T));
								_stprintf_s((PROCESS.pstMBoxParam)->szButtonTitle[MBOX_BUTTON_0], MAX_STRINPUT, _T("%s\n(ENTER)"), g_stSystemString[SYSSTR_BTN_CONFIRM].szDescription[m_nTypeLanguage]);
								_stprintf_s((PROCESS.pstMBoxParam)->szButtonTitle[MBOX_BUTTON_1], MAX_STRINPUT, _T("%s\n(ESC)"), g_stSystemString[SYSSTR_BTN_BUZZER_OFF].szDescription[m_nTypeLanguage]);
								_stprintf_s((PROCESS.pstMBoxParam)->szMessage, MAX_STRVALUE, _T("%s"), strValue);

								(PROCESS.pstMBoxParam)->bEnableButton[MBOX_BUTTON_0]	= TRUE;
								(PROCESS.pstMBoxParam)->bEnableButton[MBOX_BUTTON_1]	= TRUE;
								(PROCESS.pstMBoxParam)->nTypeButton[MBOX_BUTTON_0]		= MBOX_BTYPE_CLOSE;
								(PROCESS.pstMBoxParam)->nTypeButton[MBOX_BUTTON_1]		= MBOX_BTYPE_NORMAL;
								(PROCESS.pstMBoxParam)->nTimerButton[MBOX_BUTTON_0]		= 0;
								(PROCESS.pstMBoxParam)->nTimerButton[MBOX_BUTTON_1]		= 0;
								(PROCESS.pstMBoxParam)->bEnableShortCutKey				= TRUE;
								(PROCESS.pstMBoxParam)->nKeyShortCut[MBOX_BUTTON_0]		= VK_RETURN;
								(PROCESS.pstMBoxParam)->nKeyShortCut[MBOX_BUTTON_1]		= VK_ESCAPE;
								(PROCESS.pstMBoxParam)->nMessageFontSize				= 26;
								(PROCESS.pstMBoxParam)->crMessageFgColor				= CLR_RED;
								(PROCESS.pstMBoxParam)->bEnableSetWindowPos				= TRUE;
								(PROCESS.pstMBoxParam)->ptWindowPosition				= m_SystemConfig.GetMBoxWindowPosition();
								m_pMessageBoxDlg->SendMessage(UM_DPS_DLG_MESSAGE_BOX_SHOWHIDE, SW_SHOW, (LPARAM)(PROCESS.pstMBoxParam));

								PROCESS.nCurrentStep++;
								break;
							}

							// ������ 2ȸ ���
							m_stSystemStatus.nBeepCount = 2;

							SErrorMessage(TRUE, _T("[S%02d/%s] �޼��� �ڽ��� ������ �� �����ϴ�."),	nSTATION_NO + 1, 
																									g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

							PROCESS.nCurrentStep = 9013;
							break;

		case	9012	:
							if (m_stSystemStatus.nMessageBoxButtonCode != MBOX_BCODE_NONE) {

								// ��ư 0 : Ȯ��
								if (m_stSystemStatus.nMessageBoxButtonCode == MBOX_BCODE_0) {

									PROCESS.nCurrentStep++;
									break;
								} 

								// ��ư 1 : ����� ����
								if (m_stSystemStatus.nMessageBoxButtonCode == MBOX_BCODE_1) {

									m_stSystemStatus.bOnBuzzer				= FALSE;			// ����� ����
									m_stSystemStatus.nMessageBoxButtonCode	= MBOX_BCODE_NONE;	// ��ư �ڵ� �ʱ�ȭ
								}
							}

							break;
								
		case	9013	:
							// �޼��� �ڽ� ��� �÷��� ����
							m_stSystemStatus.bIsDisplayMessageBox = FALSE;

							// �޼��� �ڽ� ���߱�	
							m_pMessageBoxDlg->SendMessage(UM_DPS_DLG_MESSAGE_BOX_SHOWHIDE, SW_HIDE, NULL);

							// �ý��� �÷��� ����
							m_stSystemStatus.bOnWaitForUser	= FALSE;	// ����� �Է� ��� ����
							m_stSystemStatus.bOnBuzzer		= FALSE;	// ����� ����

							PROCESS.nCurrentStep = 9090;
							break;

		// �Ϸ�
		case	9090	:
							PROCESS.nCurrentStep = PROCESS.nReturn03Step;
							break;


		/////////////////////////////////////////////////////////////
		// ��ǰ �ڵ� üũ ///////////////////////////////////////////
		case	STEP_STN_SCAN_CODE	:
										PROCESS.nCurrentStep = 6010;
										break;

		// ��ǰ �ڵ� üũ
		case	6010	:
							{
								CString		strProductCodeM		= GetBarcodeInfo(nBCS_INPUT_M);
								CString		strProductCodeA		= GetBarcodeInfo(nBCS_INPUT_A);
								CString		strProductCode		= _T("");
								BOOL		bOnErrorProduct		= FALSE;
								UINT		nCodeStatus			= BCD_SCAN_NONE;
								UINT		nCodeWorkNG			= WORK_NG_NONE;


								// ��ĵ �ڵ� ����
								strProductCode = strProductCodeM;
								if (strProductCode.IsEmpty())	strProductCode = strProductCodeA;

								// ������ ��ǰ �ڵ� üũ
								PROCESS.bIsMasterProduct = FALSE;
								if (!strProductCode.IsEmpty()) {
								
									for (UINT nIndex = 0; nIndex < MAX_BCD_MASTER_CODE; nIndex++) {
									
										if (strProductCode.Compare(((PSP_WI_BASIC_SETUP_T)PROCESS.pstStationSetupInfo)->szMasterCode[nIndex]) == 0)
											PROCESS.bIsMasterProduct = TRUE;
									}

									if (PROCESS.bIsMasterProduct) {
									
										// �޼��� ���
										TestMessage(TRUE, _T("[S%02d/%s] %s [%s]"),	nSTATION_NO + 1, 
																					g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																					g_stSystemString[SYSSTR_MC_INFO_MASTER_PRODUCT_LOADED].szDescription[m_nTypeLanguage],
																					strProductCode);

										if (m_nTypeLanguage != LANGUAGE_KOR) {

											TestMessage(TRUE, _T("[S%02d/%s] %s [%s]"),	nSTATION_NO + 1, 
																						g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																						g_stSystemString[SYSSTR_MC_INFO_MASTER_PRODUCT_LOADED].szDescription[LANGUAGE_KOR],
																						strProductCode);
										}
									}
								}

								// ��ǰ �ڵ� üũ
								if (!PROCESS.bIsMasterProduct && (PROCESS.pstModelProfileConfig)->bWorkOption[WOPT_USE_SCAN_CODE]) {
								
									// ��ǰ �ڵ� ����
									if (bOnCheckProductCodeEmpty && strProductCode.IsEmpty()) {
									
										// �޼��� ���
										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_INPUT].szDescription[m_nTypeLanguage]);

										if (m_nTypeLanguage != LANGUAGE_KOR) {

											ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																					g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																					g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_INPUT].szDescription[LANGUAGE_KOR]);
										}
	
										// �ڵ� ���� ����
										nCodeStatus		= BCD_SCAN_EMPTY;
										bOnErrorProduct	= TRUE;
									
									// ��ǰ �ڵ� ����
									} else {

										CString		strInputFormat	= (PROCESS.pstWorkInfo)->szWorkInfoValue[WI_ITEM_BCD_INPUT_FORMAT];
									
										// ��ǰ �ڵ� ���� üũ
										if (!strInputFormat.IsEmpty() && !DPS_CheckInputBarcodeFormat(strInputFormat, (LPCTSTR)strProductCode, strProductCode.GetLength())) {

												ErrorMessage(TRUE, _T("[S%02d/%s] %s (%s, %s)"),	nSTATION_NO, 
																									g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																									g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_FORMAT].szDescription[m_nTypeLanguage],
																									strInputFormat, strProductCode);

												if (m_nTypeLanguage != LANGUAGE_KOR) {

													ErrorMessage(TRUE, _T("[S%02d/%s] %s (%s, %s)"),	nSTATION_NO, 
																										g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																										g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_FORMAT].szDescription[LANGUAGE_KOR],
																										strInputFormat, strProductCode);
												}

												nCodeStatus		= BCD_SCAN_WRONG;
												nCodeWorkNG		= WORK_NG_CODE_WRONG;
												bOnErrorProduct	= TRUE;
										}

										// ��ǰ �ڵ� �ߺ� üũ
										if (!m_SystemConfig.UseSystemOption(SOPT_DISABLE_CHECK_DUPLICIATION_CODE)) {

											if (!bOnErrorProduct &&
												!CheckProductCodeDuplicated(strProductCode, DIR_PRODUCT_CODE)) {

												ErrorMessage(TRUE, _T("[S%02d/%s] %s (%s)"),	nSTATION_NO, 
																								g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																								g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_DUPLICATED].szDescription[m_nTypeLanguage],
																								strProductCode);

												if (m_nTypeLanguage != LANGUAGE_KOR) {

													ErrorMessage(TRUE, _T("[S%02d/%s] %s (%s)"),	nSTATION_NO, 
																									g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																									g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_DUPLICATED].szDescription[LANGUAGE_KOR],
																									strProductCode);
												}

												nCodeStatus		= BCD_SCAN_DUPLICATE;
												nCodeWorkNG		= WORK_NG_CODE_DUPLCIATED;
												bOnErrorProduct	= TRUE;
											}
										}
									}

									// ��ǰ �ڵ� ����
									if (bOnErrorProduct) {
									
										// ������Ʈ UI
										PROCESS.bOnUpdateUI				= TRUE;
										PROCESS.stParamUI.nUpdateID		= UI_PRODUCT_CODE_IN;
										PROCESS.stParamUI.nStationNo	= nSTATION_NO;
										PROCESS.stParamUI.stProductCodeInfo.nStatusCodeInput = nCodeStatus;
										_tcscpy_s(PROCESS.stParamUI.stProductCodeInfo.szCodeInput, MAX_STRINPUT_L, strProductCode);

										// ������ ���
										m_stSystemStatus.nBeepCount = 2;

										// �÷��� ����
										bOnErrorProductCode = TRUE;

										PROCESS.nCurrentStep = 6090;
										break;
									}
								}

								if (!strProductCode.IsEmpty()) {
								
									// ���� ��ǰ �ڵ� ����
									SetCurrentProductCode(nSTATION_NO, strProductCode);

									PROCESS.nCurrentStep = 6020;
									break;
								}

								PROCESS.nCurrentStep = 6090;
							}

							break;

		// ������ �˻� üũ
		case	6020	:
							if (!PROCESS.bIsMasterProduct && m_SystemConfig.UseSystemOption(SOPT_ENABLE_CHECK_MASTER_TEST)) {
		
								if (!CheckMasterTest()) {

									// �޼��� ���
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[SYSSTR_MC_WARN_MASTER_TEST].szDescription[m_nTypeLanguage]);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[SYSSTR_MC_WARN_MASTER_TEST].szDescription[LANGUAGE_KOR]);
									}
								
									// ������ ���
									m_stSystemStatus.nBeepCount = 2;

									// ���� ��ǰ �ڵ� �ʱ�ȭ
									ClearCurrentProductCode(nSTATION_NO);

									// ����� �޼��� ����
									PROCESS.bOnSetUserMessage = SetUserMessage(UMSG_WARN_MASTER_TEST);
									LTimerProceed.Start(m_SystemConfig.GetDelaySystem(DLY_SYS_ACTION_SHOW_USER_MESSAGE));

									PROCESS.nCurrentStep++;
									break;
								}
							}

							PROCESS.nCurrentStep = 6090;
							break;

		case	6021	:
							if (LTimerProceed.Verify()) {

								// ����� �޼��� ����
								if (PROCESS.bOnSetUserMessage)	
									RestoreUserMessage();

								// �÷��� ����
								bOnErrorProductCode = TRUE;

								PROCESS.nCurrentStep = 6090;
							}

							break;

		// �Ϸ�
		case	6090	:
							PROCESS.nCurrentStep = PROCESS.nReturn03Step;
							break;


		/////////////////////////////////////////////////////////////
		// ��� /////////////////////////////////////////////////////
		case	STEP_STN_STANDBY	:
										// ���� �ɼ� ���
										if (m_stSystemStatus.bOnStationProcessStart)
											PROCESS.nCurrentStep = 210;

										break;

		// ���� ���� ����
		case	210		:
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_STANDBY;

							// ������Ʈ UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_STATUS_STATION;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;

							PROCESS.nCurrentStep = 220;
							break;

		// �غ� �۾�
		case	220		:
							// ����� �޼��� ����
							SetUserMessage(UMSG_STANDBY);

							// ���ڵ� ���� �ʱ�ȭ
							ClearBarcodeInfo(nBCS_INPUT_M);
							ClearBarcodeInfo(nBCS_INPUT_A);
							ClearCurrentProductCode(nSTATION_NO);

							PROCESS.nCurrentStep = 230;
							break;

		// ���� ��ư �Է� üũ
		case	230		:
							if (!GetDIStatus(DI_BTN_S02_START))
								PROCESS.nCurrentStep++;
							
							break;

		case	231		:
							if (GetDIStatus(DI_BTN_S02_START)) {
							
								// ��ư �Է� ����
								LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_PUSH_BUTTON));

								PROCESS.nCurrentStep++;
								break;
							}

							// �ùķ��̼� ���
							if (m_SystemConfig.IsSimulationMode()) {

								if (m_stSystemStatus.bOnSimulationStart[nSTATION_NO]) {

									m_stSystemStatus.bOnSimulationStart[nSTATION_NO] = FALSE;
									PROCESS.nCurrentStep = 250;
									break;
								}
							}

							break;

		case	232		:
							if (GetDIStatus(DI_BTN_S02_START)) {

								if (LTimerSensor.Verify()) {

									PROCESS.nCurrentStep = 235;
								}

								break;
							}

							PROCESS.nCurrentStep--;
							break;

		// �� ���� ���� üũ
		case	235		:
								if (m_stSystemStatus.stPrintStatus[BCP_PRINT_1].bIsLabelWaiting) {

									// �޼��� ���
									if (m_nTypeLanguage == LANGUAGE_KOR)	ErrorMessage(TRUE, _T("[S%02d/%s] ���� �̹� ����Ǿ� �ֽ��ϴ�."),	nSTATION_NO, g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);
									else									ErrorMessage(TRUE, _T("[S%02d/%s] LABEL IS ALREADY ISSUED."),	nSTATION_NO, g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);
									
									// ������ ���
									m_stSystemStatus.nBeepCount = 2;

									PROCESS.nCurrentStep = 230;
									break;
								}

								PROCESS.nCurrentStep = 240;
								break;

		// ��ǰ ���� �� Ŭ���� üũ, PIN S/W üũ
		case	240		:
							// ��ǰ �� PIN S/W ���� üũ
							if (GetDIStatus(DI_SENS_S02_DETECT_PRODUCT) && (m_SystemConfig.UseSystemOption(SOPT_ENABLE_CHECK_PIN_SW) ? GetDIStatus(DI_SENS_S02_DETECT_PIN_SW) : TRUE)) {

								LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_PRODUCT));

								PROCESS.nCurrentStep++;
								break;
							}

							LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_PRODUCT_NONE));

							PROCESS.nCurrentStep = 242;
							break;

		case	241		:
							if (GetDIStatus(DI_SENS_S02_DETECT_PRODUCT) && (m_SystemConfig.UseSystemOption(SOPT_ENABLE_CHECK_PIN_SW) ? GetDIStatus(DI_SENS_S02_DETECT_PIN_SW) : TRUE)) {

								if (LTimerSensor.Verify()) {

									PROCESS.nCurrentStep = 245;
								}

								break;
							}

							PROCESS.nCurrentStep--;
							break;

		case	242		:
							if (!GetDIStatus(DI_SENS_S02_DETECT_PRODUCT) || (m_SystemConfig.UseSystemOption(SOPT_ENABLE_CHECK_PIN_SW) ? !GetDIStatus(DI_SENS_S02_DETECT_PIN_SW) : FALSE)) {

								if (LTimerSensor.Verify()) {

									UINT	nSystemMessageID	= (m_SystemConfig.UseSystemOption(SOPT_ENABLE_CHECK_PIN_SW) && !GetDIStatus(DI_SENS_S02_DETECT_PRODUCT)) ? SYSSTR_MC_WARN_PRODUCT_NONE : SYSSTR_MC_WARN_DETECT_PIN_SW;

									// �޼��� ���
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[nSystemMessageID].szDescription[m_nTypeLanguage]);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[nSystemMessageID].szDescription[m_nTypeLanguage]);
									}

									// ������ ���
									m_stSystemStatus.nBeepCount = 2;

									PROCESS.nCurrentStep = 230;
								}

								break;
							}

							PROCESS.nCurrentStep = 240;
							break;

		case	245		:
							// ��ǰ Ŭ���� üũ
							if (GetDIStatus(DI_SENS_S02_CLAMP_1_ON) && GetDIStatus(DI_SENS_S02_CLAMP_2_ON)) {

								LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_PRODUCT));

								PROCESS.nCurrentStep++;
								break;
							}

							LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_PRODUCT_NONE));

							PROCESS.nCurrentStep = 247;
							break;

		case	246		:
							if (GetDIStatus(DI_SENS_S02_CLAMP_1_ON) && GetDIStatus(DI_SENS_S02_CLAMP_2_ON)) {

								if (LTimerSensor.Verify()) {

									PROCESS.nCurrentStep = 250;
								}

								break;
							}

							PROCESS.nCurrentStep--;
							break;

		case	247		:
							if (!GetDIStatus(DI_SENS_S02_CLAMP_1_ON) || !GetDIStatus(DI_SENS_S02_CLAMP_2_ON)) {

								if (LTimerSensor.Verify()) {

									// �޼��� ���
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CLAMP].szDescription[m_nTypeLanguage]);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CLAMP].szDescription[m_nTypeLanguage]);
									}

									// ������ ���
									m_stSystemStatus.nBeepCount = 2;

									PROCESS.nCurrentStep = 230;
								}

								break;
							}

							PROCESS.nCurrentStep = 245;
							break;

		// ���� üũ
		case	250		:
							{
								BOOL		bIsErrorState	= FALSE;
								UINT		nUserMessageID	= 0;
								CString		strErrorMessage	= _T("");


								// �ʱ�ȭ
								strMessage.Empty();

								// ���κ� ī���� üũ
								if (!bIsErrorState) {

									bIsErrorState |= m_stSystemStatus.bIsFullProbeCounter[nSTATION_NO];

									if (bIsErrorState) {

										strMessage.AppendFormat(_T(" %s\n %s\n"), g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage], g_stSystemString[SYSSTR_MC_WARN_EXPIRE_PROBE].szDescription[m_nTypeLanguage]);
										strMessage.AppendFormat(_T(" %s"), g_stSystemString[SYSSTR_MC_WARN_EXPIRE_PROBE_COMMENT].szDescription[m_nTypeLanguage]);
										strErrorMessage		= g_stSystemString[SYSSTR_MC_WARN_EXPIRE_PROBE_COMMENT].szDescription[m_nTypeLanguage];
										nUserMessageID		= UMSG_WARN_PROBE_COUNT_EXPIRED;
									}
								}

								// ���� ó��
								if (bIsErrorState) {

									// �޼��� ���
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			strErrorMessage);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[SYSSTR_MC_WARN_EXPIRE_PROBE_COMMENT].szDescription[LANGUAGE_KOR]);
									}

									// ����� �޼��� ����
									PROCESS.bOnSetUserMessage = SetUserMessage(nUserMessageID);

									PROCESS.nCurrentStep	= STEP_STN_MESSAGE_BOX_01;
									PROCESS.nReturn03Step	= 251;
									break;
								}

								PROCESS.nCurrentStep = 260;
							}

							break;

		case	251		:
							// ����� �޼��� ����
							if (PROCESS.bOnSetUserMessage)	
								RestoreUserMessage();

							PROCESS.nCurrentStep--;
							break;

		// ��ǰ �ڵ� üũ (���� ��ĵ)
		case	260		:
							if (!GetBarcodeInfo(nBCS_INPUT_M).IsEmpty()) {

								bOnCheckProductCodeEmpty = FALSE;
								bOnErrorProductCode		 = FALSE;

								PROCESS.nCurrentStep	 = STEP_STN_SCAN_CODE;
								PROCESS.nReturn03Step	 = 261;
								break;
							}

							PROCESS.nCurrentStep = 270;
							break;

		case	261		:
							if (bOnErrorProductCode) {
							
								PROCESS.nCurrentStep = 230;
								break;
							}

							PROCESS.nCurrentStep = 270;
							break;

		// ��ǰ ���� ���� üũ
		case	270		:
							if (GetDIStatus(DI_SENS_S02_DETECT_PRODUCT_DOOR)) {

								LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_PRODUCT));

								PROCESS.nCurrentStep++;
								break;
							}

							LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_SENSOR_PRODUCT_NONE));

							PROCESS.nCurrentStep = 272;
							break;

		case	271		:
							if (GetDIStatus(DI_SENS_S02_DETECT_PRODUCT_DOOR)) {

								if (LTimerSensor.Verify()) {

									PROCESS.nCurrentStep = 290;
								}

								break;
							}

							PROCESS.nCurrentStep--;
							break;

		case	272		:
							if (!GetDIStatus(DI_SENS_S02_DETECT_PRODUCT_DOOR)) {

								if (LTimerSensor.Verify()) {

									PROCESS.nCurrentStep++;
								}

								break;
							}

							PROCESS.nCurrentStep = 270;
							break;

		case	273		:
							if (!GetDIStatus(DI_SENS_S02_DETECT_PRODUCT_DOOR)) {

								if (LTimerProceed.Verify()) {
							
									// �޼��� ���
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[SYSSTR_MC_WARN_PRODUCT_DOOR_OPENED].szDescription[m_nTypeLanguage]);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[SYSSTR_MC_WARN_PRODUCT_DOOR_OPENED].szDescription[m_nTypeLanguage]);
									}

									// ������ ���
									m_stSystemStatus.nBeepCount = 2;

									// Ÿ�̸� ����
									LTimerProceed.Start(m_SystemConfig.GetDelaySystem(DLY_SYS_INTV_USER_WARNING_MESSAGE));
								}

								break;
							}

							PROCESS.nCurrentStep = 270;
							break;

		// ��ǰ ���� ���� �ҷ�
		case	280		:
							// �޼��� ���
							ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																	g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																	g_stSystemString[SYSSTR_MC_WARN_PRODUCT_DOOR_STATUS].szDescription[m_nTypeLanguage]);

							if (m_nTypeLanguage != LANGUAGE_KOR) {

								ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																		g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																		g_stSystemString[SYSSTR_MC_WARN_PRODUCT_DOOR_STATUS].szDescription[m_nTypeLanguage]);
							}

							// ������ ���
							m_stSystemStatus.nBeepCount = 2;

							// ����� �޼��� ����
							SetUserMessage(UMSG_WARN_PRODUCT_DOOR_LOCK);
							LTimerProceed.Start(m_SystemConfig.GetDelaySystem(DLY_SYS_ACTION_SHOW_USER_MESSAGE));

							// ��-Ÿ�� ����
							m_pTactTimerWnd[nSTATION_NO]->PostMessage(UM_TACT_TIMER_STATE, TACT_STOP);

							PROCESS.nCurrentStep++;
							break;

		case	281		:
							if (LTimerProceed.Verify()) {
							
								// ����� �޼��� ����
								RestoreUserMessage();
								SetUserMessage(UMSG_STANDBY);

								PROCESS.nCurrentStep = 230;
							}

							break;

		// �Ϸ�
		case	290		:
							// ������ ���
							m_stSystemStatus.nBeepCount = 1;

							// ����� �޼��� ����
							SetUserMessage(UMSG_PREPARING);

							// ������Ʈ UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_WORK_SHEET_01 | UI_WORK_SHEET_02 | UI_VISION_SHEET | UI_PRODUCT_CODE_OUT;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;
							PROCESS.stParamUI.stWorkSheet.bOnClear	= TRUE;

							// ��-Ÿ�� ����
							m_pTactTimerWnd[nSTATION_NO]->PostMessage(UM_TACT_TIMER_STATE, TACT_PROCEED);

							PROCESS.nCurrentStep  = STEP_STN_SUB_01;
							PROCESS.nReturn02Step = 291;
							break;

		case	291		:
							PROCESS.nCurrentStep = PROCESS.bOnInterLock ? 280 : STEP_STN_WORK;
							break;


		/////////////////////////////////////////////////////////////
		// �۾� /////////////////////////////////////////////////////
		case	STEP_STN_WORK	:
									PROCESS.nCurrentStep = 2010;
									break;

		// ���� ���� ����
		case	2010	:
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_PROCEED;

							// ������Ʈ UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_STATUS_STATION;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;

							PROCESS.nCurrentStep = 2050;
							break;

		// ��ǰ �ڵ� üũ (�ڵ� ��ĵ)
		case	2050	:
							if (GetCurrentProductCode(nSTATION_NO).IsEmpty()) {

								PROCESS.nRetryCount = 0;
								PROCESS.nCurrentStep++;
								break;
							}

							PROCESS.nCurrentStep = 2100;
							break;

		case	2051	:
							if (LTimerSteadyScan.Verify()) {

								ClearBarcodeInfo(nBCS_INPUT_A);
								SetTrigBarcode(nBCS_INPUT_A);
								LTimerTimeOutScan.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_BARCODE_AUTO_SCAN_1));

								PROCESS.nCurrentStep++;
							}

							break;

		case	2052	:
							if (!GetBarcodeInfo(nBCS_INPUT_A).IsEmpty()) {

								// �޼��� ���
								NormalMessage(TRUE, _T("[%s] AUTO SCAN PRODUCT CODE = %s"),	g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage], 
																							GetBarcodeInfo(nBCS_INPUT_A));

								bOnCheckProductCodeEmpty = TRUE;
								bOnErrorProductCode		 = FALSE;

								PROCESS.nCurrentStep	 = STEP_STN_SCAN_CODE;
								PROCESS.nReturn03Step	 = 2053;
								break;
							}

							// ��ĵ Ÿ�� �ƿ�
							if (LTimerTimeOutScan.Verify()) {

								// ���ڵ� ��ĳ�� Ʈ���� ����
								SetTrigBarcode(nBCS_INPUT_A, FALSE);
								LTimerSteadyScan.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_BCD_CONTROL));

								if (++PROCESS.nRetryCount >= MAX_RETRY_BCD_SCAN) {

									// �޼��� ���
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_SCAN].szDescription[m_nTypeLanguage]);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_SCAN].szDescription[LANGUAGE_KOR]);
									}

									// ������ ���
									m_stSystemStatus.nBeepCount = 2;

									PROCESS.nCurrentStep = 2060;
									break;
								}

								PROCESS.nCurrentStep--;
							}

							break;

		case	2053	:
							if (bOnErrorProductCode) {
							
								PROCESS.nCurrentStep = STEP_STN_STANDBY;
								break;
							}

							PROCESS.nCurrentStep = 2100;
							break;

		// �غ� �۾�
		case	2100	:
							// �۾� ���� ���� �ʱ�ȭ
							InitWorkStatus(nSTATION_NO);
							_tcscpy_s((PROCESS.pstWorkStatus)->szProductCode, MAX_STRINPUT_S, GetCurrentProductCode(nSTATION_NO));

							// ���� �˻� �ʱ�ȭ
							InitVisionTest();

							// ���� ���� �˻� �۾� ��Ʈ ������Ʈ ��ȣ �ʱ�ȭ
							m_stSystemStatus.nCurrentVisionWorkSheetUpdateNo = 0;

							// �� ���� ���ͷ� ����
							m_stSystemStatus.bOnInterlockViewDetail = TRUE;

							// �۾� ��� ���丮 ����
							CreateWorkResultDirectory(nSTATION_NO);

							// ���� �̹��� ������ �ʱ�ȭ
							if (m_pMainWnd)	{
								
								m_stSystemStatus.bIsVisionImageWindowCleared = FALSE;
								m_pMainWnd->PostMessage(UM_VISION_CLEAR_IMAGE);
							}

							PROCESS.nCurrentStep = 2120;
							break;

		// ���κ� : ON
		case	2120	:
							pOnSCP_MoveParts[SCP_S02_PROBE_ON] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	2121	:
							if (!pOnSCP_MoveParts[SCP_S02_PROBE_ON])
								PROCESS.nCurrentStep = 2200;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// ���� �۾� ����
		case	2200	:
							// ���μ��� ��� ����
							m_stSystemStatus.bIsStationProcessLock[nSTATION_NO][nSTATION_SUB_NO] = TRUE;

							// ���� ���μ��� ����
							m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	2201	:
							if (!m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]) {

								// ���� ���μ��� ��� ����
								PROCESS.bResultMainProcess = m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO];

								PROCESS.nCurrentStep = 2250;
							}

							break;

		// ��ε�
		case	2250	:
							pOnSCP_MoveParts[SCP_S02_UNLOADING] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	2251	:
							if (!pOnSCP_MoveParts[SCP_S02_UNLOADING])
								PROCESS.nCurrentStep = 2290;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// ���� �۾� ���հ� �� ���۾�
		case	2290	:
							// ��� ����

							PROCESS.nCurrentStep = 2300;
							break;

		// ...?
		case	2300	:
							PROCESS.nCurrentStep = 2380;
							break;

		// �۾� ��� ����
		case	2380	:
							// �۾� ���� ���� ����
							(PROCESS.pstWorkStatus)->nResultFinal = PROCESS.bResultMainProcess ? T_RESULT_SUCCESS : T_RESULT_FAILURE;

							// ���μ��� ��� ����
							m_stSystemStatus.bIsStationProcessLock[nSTATION_NO][nSTATION_SUB_NO] = FALSE;

							// ��-Ÿ�� ����
							m_pTactTimerWnd[nSTATION_NO]->PostMessage(UM_TACT_TIMER_STATE, TACT_STOP);

							// ���� ���� ����
							if (!PROCESS.bIsMasterProduct) {

								m_pProductionWnd->SetCumulativeCount();
								m_pProductionWnd->SetProductionCount(PROCESS.bResultMainProcess);
							}

							PROCESS.nCurrentStep++;
							break;
		
		case	2381	:
							// �� ��� ����
							if (!m_SystemConfig.IsTestMode() && !PROCESS.bIsMasterProduct && m_stSystemStatus.bUsePrintLabel && PROCESS.bResultMainProcess) {

								UINT		nPrintQuantity	= 1;
								CString		strOutputCode	= _T("");
							

								if (nPrintQuantity) {

									// �� ���� ����
									CreateLabelFormat(BCP_PRINT_1, *PROCESS.pstLabelPrintInfo, nPrintQuantity, 0, &strOutputCode);
									_tcscpy_s((PROCESS.pstWorkStatus)->szOutputCode, MAX_STRINPUT_S, strOutputCode);

									// ������Ʈ UI
									PROCESS.bOnUpdateUI				= TRUE;
									PROCESS.stParamUI.nUpdateID		= UI_PRODUCT_CODE_OUT;
									PROCESS.stParamUI.nStationNo	= nSTATION_NO;
									_tcscpy_s(PROCESS.stParamUI.stProductCodeInfo.szCodeOutput, MAX_STRINPUT_L, strOutputCode);

									// �� ��� ����
									m_stSystemStatus.bOnPrintLabel[BCP_PRINT_1]	= TRUE;
								}
							}

							PROCESS.nCurrentStep++;
							break;

		case	2382	:
							// �۾� ��Ʈ ����
							SaveWorkSheet01(PROCESS.bIsMasterProduct);
							SaveWorkSheet01T(PROCESS.bIsMasterProduct);
							SaveWorkSheetERP_01(PROCESS.bIsMasterProduct);

							// ��ǰ �ڵ� ���� ����
							if ((PROCESS.pstWorkStatus)->nResultFinal == T_RESULT_SUCCESS) {
							
								PRODUCT_CODE_INFO_T	stProductCodeInfo;
								ZeroMemory(&stProductCodeInfo, sizeof(PRODUCT_CODE_INFO_T));

								_tcscpy_s(stProductCodeInfo.szProductCode, MAX_STRINPUT_S, (PROCESS.pstWorkStatus)->szProductCode);

								if (!SaveProductCodeFile(stProductCodeInfo, DIR_PRODUCT_CODE)) {

									ErrorMessage(TRUE,	_T("[S%02d/%s] CREATE PRODUCT CODE FILE ERROR!"),	
														nSTATION_NO + 1, 
														g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);
								}
							}

							// ���� ī���� ����
							m_stWorkSubCounter.nCountStation[nSTATION_NO]++;
							SaveWorkSubCounter();

							// �� ���� ���ͷ� ����
							m_stSystemStatus.bOnInterlockViewDetail = FALSE;

							// ���� ���� ����
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_COMPLETE;

							// ������Ʈ UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_STATUS_STATION | UI_SUB_COUNTER;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;

							// ����� �޼��� ����
							SetUserMessage(UMSG_COMPLETE);

							PROCESS.nCurrentStep = 2400;
							break;

		// ���հ� ���� �� ����� ����
		case	2400	:
							if (!m_SystemConfig.IsTestMode() && !PROCESS.bIsMasterProduct && (PROCESS.pstWorkStatus)->nResultFinal != T_RESULT_SUCCESS) {
							
								PROCESS.nCurrentStep	= STEP_STN_USER_UNLOAD;
								PROCESS.nReturn01Step	= 2900;
								break;
							}

							// ������ ��� (�հ� ���� ��)
							m_stSystemStatus.nBeepCount = 3;

							PROCESS.nCurrentStep = 2410;
							break;

		// �� ��� Ȯ��
		case	2410	:
							if (!m_stSystemStatus.bOnPrintLabel[BCP_PRINT_1])
								PROCESS.nCurrentStep = 2800;
							
							break;

		// ��ǰ ���� Ȯ��
		case	2800	:
							if (m_SystemConfig.IsTestMode())
								PROCESS.nCurrentStep = 2900;

							if (!GetDIStatus(DI_SENS_S02_DETECT_PRODUCT) && !GetDIStatus(DI_SENS_S02_CLAMP_1_ON) && !GetDIStatus(DI_SENS_S02_CLAMP_1_ON))
								PROCESS.nCurrentStep = 2900;

							break;

		// �Ϸ�
		case	2900	:
							// ���� ���� ����
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_NONE;

							// ������Ʈ UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_STATUS_STATION;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;

							// ������ �˻� �Ϸ� ����
							m_stSystemStatus.bIsMasterTestComplete = CheckMasterTest();

							PROCESS.nCurrentStep = m_SystemConfig.IsTestMode() ? 290 : STEP_STN_STANDBY;
							break;


		/////////////////////////////////////////////////////////////
		// ����� ���� //////////////////////////////////////////////
		case	STEP_STN_USER_UNLOAD	:
											PROCESS.nCurrentStep = 3020;
											break;

		// �޼��� �ڽ� ���
		case	3020	:
							// �޼��� �ڽ��� ��� ���� üũ
							if (!m_stSystemStatus.bIsDisplayMessageBox) {
							
								m_stSystemStatus.bIsDisplayMessageBox = TRUE;

								PROCESS.nCurrentStep++;
							}

							break;

		case	3021	:
							// �޼��� ���
							ErrorMessage(TRUE, _T("[S%02d/%s] �ҷ� ��ǰ�� ���� �� �ҷ��Կ� ������ �ֽʽÿ�."), nSTATION_NO + 1, g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

							// �ý��� �÷��� ����
							m_stSystemStatus.bOnWaitForUser			= TRUE;				// ����� �Է� ��� ����
							m_stSystemStatus.bOnBuzzer				= TRUE;				// ����� ���
							m_stSystemStatus.nMessageBoxButtonCode	= MBOX_BCODE_NONE;	// ��ư �ڵ� �ʱ�ȭ

							// �޼��� �ڽ� ����
							PROCESS.pstMBoxParam = new MBOX_PARAM_T;
							if (PROCESS.pstMBoxParam) {

								CString		strValue = _T("");

								strValue.AppendFormat(_T("\n [����� �ҷ� ����]\n\n"));
								strValue.AppendFormat(_T(" ���� ���� �˻� ���հ� ��ǰ�Դϴ�.\n"));
								strValue.AppendFormat(_T(" ��ǰ�� ���� �� �ҷ��Կ� ������ �ֽʽÿ�."));
	
								ZeroMemory(PROCESS.pstMBoxParam, sizeof(MBOX_PARAM_T));
								_stprintf_s((PROCESS.pstMBoxParam)->szButtonTitle[MBOX_BUTTON_0], MAX_STRINPUT, _T("����� ����\n(ESC)"));
								_stprintf_s((PROCESS.pstMBoxParam)->szMessage, MAX_STRVALUE, _T("%s"), strValue);

								(PROCESS.pstMBoxParam)->bEnableButton[MBOX_BUTTON_0]	= TRUE;
								(PROCESS.pstMBoxParam)->nTypeButton[MBOX_BUTTON_0]		= MBOX_BTYPE_NORMAL;
								(PROCESS.pstMBoxParam)->bEnableShortCutKey				= TRUE;
								(PROCESS.pstMBoxParam)->nKeyShortCut[MBOX_BUTTON_0]		= VK_ESCAPE;
								(PROCESS.pstMBoxParam)->nMessageFontSize				= 26;
								(PROCESS.pstMBoxParam)->bEnableSetWindowPos				= TRUE;
								(PROCESS.pstMBoxParam)->ptWindowPosition				= m_SystemConfig.GetMBoxWindowPosition();
								m_pMessageBoxDlg->SendMessage(UM_DPS_DLG_MESSAGE_BOX_SHOWHIDE, SW_SHOW, (LPARAM)(PROCESS.pstMBoxParam));

								PROCESS.nCurrentStep++;
								break;
							}

							// ������ 2ȸ ���
							m_stSystemStatus.nBeepCount	= 2;

							SErrorMessage(TRUE, _T("[S%02d/%s] �޼��� �ڽ��� ������ �� �����ϴ�."),	nSTATION_NO + 1, 
																									g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

							PROCESS.nCurrentStep++;
							break;

		case	3022	:
							if (m_stSystemStatus.nMessageBoxButtonCode != MBOX_BCODE_NONE) {

								// ��ư 1 : ����� ����
								if (m_stSystemStatus.nMessageBoxButtonCode == MBOX_BCODE_0) {

									m_stSystemStatus.bOnBuzzer				= FALSE;			// ����� ����
									m_stSystemStatus.nMessageBoxButtonCode	= MBOX_BCODE_NONE;	// ��ư �ڵ� �ʱ�ȭ
								}
							}

							// �ҷ��� ���� üũ
							if (!GetDIStatus(DI_SENS_S02_DETECT_PRODUCT) && 
								!GetDIStatus(DI_SENS_S02_CLAMP_1_ON) && 
								!GetDIStatus(DI_SENS_S02_CLAMP_1_ON) &&
								(m_SystemConfig.UseSystemOption(SOPT_DISABLE_CHECK_NG_BOX) || GetDIStatus(DI_SENS_S02_DETECT_NG_BOX))) {

								// �޼��� ���
								ErrorMessage(TRUE, _T("[S%02d/%s] �ҷ��Կ� ��ǰ ������ �Ϸ�Ǿ����ϴ�."), nSTATION_NO + 1, g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3023	:
							// �޼��� �ڽ� ��� �÷��� ����
							m_stSystemStatus.bIsDisplayMessageBox = FALSE;

							// �޼��� �ڽ� ���߱�	
							m_pMessageBoxDlg->SendMessage(UM_DPS_DLG_MESSAGE_BOX_SHOWHIDE, SW_HIDE, NULL);

							// �ý��� �÷��� ����
							m_stSystemStatus.bOnWaitForUser	= FALSE;	// ����� �Է� ��� ����
							m_stSystemStatus.bOnBuzzer		= FALSE;	// ����� ����

							PROCESS.nCurrentStep = 3090;
							break;

		// �Ϸ�
		case	3090	:
							PROCESS.nCurrentStep = PROCESS.nReturn01Step;
							break;


		/////////////////////////////////////////////////////////////
		// �۾� ���� ���� ///////////////////////////////////////////
		case	STEP_STN_WAIT_STOP	:
										if (!m_stSystemStatus.bOnOperatingStopReservated) {

											PROCESS.bIsStopReservated	= FALSE;
											PROCESS.nCurrentStep		= PROCESS.nRecoveryStopStep;
										}

										break;


		/////////////////////////////////////////////////////////////
		// ���� /////////////////////////////////////////////////////
		case	STEP_STN_ERROR	:
									PROCESS.bOnOperatingStop = TRUE;
									break;

		case	STEP_STN_ERROR_PARTS	:
											if (PROCESS.bOnMachineInitialize) {
											
												m_stSystemStatus.bOnStationInitializeResult[nSTATION_NO][nSTATION_SUB_NO] = FALSE;
												PROCESS.nCurrentStep = PROCESS.nReturn01Step;
												break;
											}

											PROCESS.bOnError				= TRUE;
											PROCESS.nRecoveryStep			= STEP_STN_ERROR;
											PROCESS.stErrorCode.nErrorCode	= ERROR_MACHINE_SEQUENCE;
											PROCESS.stErrorCode.nProcessID	= PROCESS_STATION;
											PROCESS.stErrorCode.nStationNo	= nSTATION_NO;

											// ����� �޼���
											SDebugMessage(TRUE, _T("[S%02d] ERROR PARTS"), nSTATION_NO);
											break;

		case	STEP_STN_ERROR_SYSTEM	:
											// ����� �޼���
											SDebugMessage(TRUE, _T("[S%02d] ERROR SYSTEM"), nSTATION_NO);
											break;


		/////////////////////////////////////////////////////////////
		// �Ͻ� ���� ���� ///////////////////////////////////////////
		case	STEP_PAUSE	:
								if (m_stSystemStatus.bOnEmergencyStop) {

									PROCESS.nCurrentStep = STEP_EMG;
									break;
								}

								PROCESS.nCurrentStep++;
								break;

		case	20001	:
							if (!m_stSystemStatus.bOnPause && !m_stSystemStatus.bOnAlarmSystem && !m_stSystemStatus.bOnAlarmStation[nSTATION_NO]) {

								PROCESS.nCurrentStep = 20100;
							}

							break;

		// ���� ����
		case	20100	:
							PROCESS.nCurrentStep	= PROCESS.nRecoveryStep;
							PROCESS.bOnPause		= FALSE;
							break;


		/////////////////////////////////////////////////////////////
		// ��� ���� ���� ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop)	{

									PROCESS.nRecoveryStep	= 0;
									PROCESS.nCurrentStep	= 20001;
								}

								break;


		/////////////////////////////////////////////////////////////
		// ��� �ʱ�ȭ ���� /////////////////////////////////////////
		case	STEP_MC_INIT	:
									PROCESS.nCurrentStep = 22010;
									break;

		case	22010	:
							// ���� �ʱ�ȭ
							if (m_stSystemStatus.bOnStationInitialize[nSTATION_NO][nSTATION_SUB_NO]) {

								PROCESS.nCurrentStep	= STEP_STN_INIT;
								PROCESS.nReturn01Step	= 22011;
							}

							break;

		case	22011	:
							m_stSystemStatus.bOnStationInitialize[nSTATION_NO][nSTATION_SUB_NO] = FALSE;

							PROCESS.nCurrentStep = 22020;
							break;

		case	22020	:
							if (!m_stSystemStatus.bOnMachineInitialize) {
							
								PROCESS.bIsOperatingStop		= FALSE;
								PROCESS.bOnMachineInitialize	= FALSE;
								PROCESS.nCurrentStep			= PROCESS.nRecoveryStep;
							}

							break;
	}
	

	/////////////////////////////////////////////////////////////////
	// ���� ���� üũ ///////////////////////////////////////////////
	CheckProcessOperatingStop(PROCESS);


	/////////////////////////////////////////////////////////////////
	// �Ϲ� /////////////////////////////////////////////////////////
	CheckProcessGeneral(nSTATION_NO, PROCESS);


	/////////////////////////////////////////////////////////////////
	// ���� ����͸� ////////////////////////////////////////////////
	if (LTimerSystemMonitor.Verify()) {

		if (PROCESS.nPrevStep != PROCESS.nCurrentStep) {

			PROCESS.nPrevStep = PROCESS.nCurrentStep;
			if (m_pSysMonitorDlg && m_pSysMonitorDlg->GetSafeHwnd()) {

				m_pSysMonitorDlg->PostMessage(UM_SYSM_UPDATE_STEP, PSTEP_PROC_STATION_02, PROCESS.nCurrentStep);
				LTimerSystemMonitor.Start(DLY_REFRESH_SYSTEM_MONITOR);
			}
		}
	}


	return	PROCESS.pstErrorCode;
}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� (����) : ���� /////////////////////////////////////////////////////
PERROR_CODE_T CMainApp::ProcessCommonParts(void)
{
	return	NULL;
}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� (����) : ���� #01 - �˻� ���� (OS) ////////////////////////////////
PERROR_CODE_T CMainApp::ProcessStation01Parts(void)
{
	static	PROCESS_CTRL_T		PROCESS;

	static	UINT				nSTATION_NO				= STATION_1;
	static	UINT				nSTATION_SUB_NO			= 0;
	static	UINT				nPARTS_COUNT			= MAX_STATION_CONTROL_PARTS_01;
			PBOOL				pOnSCP_MoveParts		= m_stSystemStatus.bOnSCP_MoveParts[nSTATION_NO];

	static	LTimerMsec			LTimerProceed;
	static	LTimerMsec			LTimerTimeOut;
	static	LTimerMsec			LTimerSteady;
	static	LTimerMsec			LTimerInterLock;


	/////////////////////////////////////////////////////////////////
	// ���μ��� ������ �ʱ�ȭ ///////////////////////////////////////
	ProcessDataInitialize(PROCESS);


	/////////////////////////////////////////////////////////////////
	// �ڵ� ���� ����/���� �ʱ�ȭ ///////////////////////////////////
	if (CheckProcessOperating(PROCESS) || m_SystemConfig.IsSimulationMode()) {
	
		ZeroMemory(pOnSCP_MoveParts, sizeof(BOOL) * nPARTS_COUNT);
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���� ��� ///////////////////////////////////////////////
	if (CheckProcessManualControlMode(nSTATION_NO, PROCESS)) {
	
		ZeroMemory(pOnSCP_MoveParts, sizeof(BOOL) * nPARTS_COUNT);
	}


	/////////////////////////////////////////////////////////////////
	// ���/�Ͻ� ���� ���� //////////////////////////////////////////
	if (CheckProcessEmergencyStop(PROCESS))					return	NULL;
	if (CheckProcessOperatingPause(nSTATION_NO, PROCESS))	return	NULL;
	

	/////////////////////////////////////////////////////////////////
	// ���� ���μ��� ////////////////////////////////////////////////
	switch (PROCESS.nCurrentStep) {

		case	0		:
							PROCESS.nCurrentStep = 10;
							break;


		/////////////////////////////////////////////////////////////
		// �ε��� ///////////////////////////////////////////////////
		case	10		:
							PROCESS.nRetryCount		= 0;
							PROCESS.nRetryInterLock	= 0;
							PROCESS.nActionCount	= 0;
							PROCESS.bOnInterLock	= FALSE;

							if (pOnSCP_MoveParts[SCP_S01_LOADING_FWD])			{ PROCESS.nCurrentStep = 1100; break; }
							if (pOnSCP_MoveParts[SCP_S01_LOADING_BWD])			{ PROCESS.nCurrentStep = 1150; break; }
							if (pOnSCP_MoveParts[SCP_S01_PROBE_ON])				{ PROCESS.nCurrentStep = 2100; break; }
							if (pOnSCP_MoveParts[SCP_S01_PROBE_OFF])			{ PROCESS.nCurrentStep = 2150; break; }
							if (pOnSCP_MoveParts[SCP_S01_PROBE_GUIDE_ON])		{ PROCESS.nCurrentStep = 2200; break; }
							if (pOnSCP_MoveParts[SCP_S01_PROBE_GUIDE_OFF])		{ PROCESS.nCurrentStep = 2250; break; }
							if (pOnSCP_MoveParts[SCP_S01_PRODUCT_DOOR_OPEN_UP])	{ PROCESS.nCurrentStep = 3100; break; }
							if (pOnSCP_MoveParts[SCP_S01_PRODUCT_DOOR_OPEN_DN])	{ PROCESS.nCurrentStep = 3150; break; }
							if (pOnSCP_MoveParts[SCP_S01_UNLOADING])			{ PROCESS.nCurrentStep = 6000; break; }
							
							break;


		/////////////////////////////////////////////////////////////
		// �ε� ���� ////////////////////////////////////////////////

		// FWD
		case	1100	:
							if (LTimerInterLock.Verify()) {

								if (!GetDIStatus(DI_SENS_S01_LOADING_FWD)) {

									// ����-�� üũ
									PROCESS.bOnInterLock = FALSE;

									if (!GetDIStatus(DI_SENS_S01_PROBE_OFF)) {

										NormalMessage(TRUE, _T("[S%02d_LOADING_FWD] INTERLOCK::(X%03X) %s"), 
															nSTATION_NO,
															DI_SENS_S01_PROBE_OFF, 
															g_stDIODescription[m_nTypeLanguage][DI_SENS_S01_PROBE_OFF].szInput);

										PROCESS.bOnInterLock = TRUE;
									}

									if (!GetDIStatus(DI_SENS_S01_PROBE_GUIDE_OFF)) {

										NormalMessage(TRUE, _T("[S%02d_LOADING_FWD] INTERLOCK::(X%03X) %s"), 
															nSTATION_NO,
															DI_SENS_S01_PROBE_GUIDE_OFF, 
															g_stDIODescription[m_nTypeLanguage][DI_SENS_S01_PROBE_GUIDE_OFF].szInput);

										PROCESS.bOnInterLock = TRUE;
									}

									if (PROCESS.bOnInterLock) {

										if (++PROCESS.nRetryInterLock >= MAX_RETRY_COUNT) {

											m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
											PROCESS.nCurrentStep = 1140;
											break;
										}

										LTimerInterLock.Start(m_SystemConfig.GetDelayProcess(DLY_PROC_INTERLOCK_RETRY));
										PROCESS.bOnInterLock = FALSE;
										break;
									}

									SetDOStatus(DO_ON,  DO_SOL_S01_LOADING_FWD);
									SetDOStatus(DO_OFF, DO_SOL_S01_LOADING_BWD);
									LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_MOVE_CYLINDER));

									PROCESS.nCurrentStep++;
									break;
								}

								PROCESS.nCurrentStep = 1140;
							}

							break;

		case	1101	:
							if (GetDIStatus(DI_SENS_S01_LOADING_FWD)) {

								SetDOStatus(DO_OFF, DO_SOL_S01_LOADING_FWD);

								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_CYLINDER));
								PROCESS.nCurrentStep = 1140;
								break;
							}

							// �Ǹ��� Ÿ�Ӿƿ�
							if (LTimerTimeOut.Verify()) {

								if (++PROCESS.nRetryCount > MAX_RETRY_COUNT) {

									PROCESS.bOnError		= TRUE;
									PROCESS.nRetryCount		= 0;
									PROCESS.nRecoveryStep	= 1100;

									PROCESS.stErrorCode.nErrorCode	= ERROR_TOUT_CYLINDER;
									PROCESS.stErrorCode.nSensor		= DI_SENS_S01_LOADING_FWD;
									break;
								}

								PROCESS.nCurrentStep--;
							}

							break;

		case	1140	:
							if (LTimerSteady.Verify()) {

								pOnSCP_MoveParts[SCP_S01_LOADING_FWD] = FALSE;
								PROCESS.nCurrentStep = 0;
							}

							break;

		// BWD
		case	1150	:
							if (LTimerInterLock.Verify()) {

								if (!GetDIStatus(DI_SENS_S01_LOADING_BWD)) {

									// ����-�� üũ
									PROCESS.bOnInterLock = FALSE;

									if (!GetDIStatus(DI_SENS_S01_PROBE_OFF)) {

										NormalMessage(TRUE, _T("[S%02d_LOADING_BWD] INTERLOCK::(X%03X) %s"), 
															nSTATION_NO,
															DI_SENS_S01_PROBE_OFF, 
															g_stDIODescription[m_nTypeLanguage][DI_SENS_S01_PROBE_OFF].szInput);

										PROCESS.bOnInterLock = TRUE;
									}

									if (!GetDIStatus(DI_SENS_S01_PROBE_GUIDE_OFF)) {

										NormalMessage(TRUE, _T("[S%02d_LOADING_BWD] INTERLOCK::(X%03X) %s"), 
															nSTATION_NO,
															DI_SENS_S01_PROBE_GUIDE_OFF, 
															g_stDIODescription[m_nTypeLanguage][DI_SENS_S01_PROBE_GUIDE_OFF].szInput);

										PROCESS.bOnInterLock = TRUE;
									}

									if (PROCESS.bOnInterLock) {

										if (++PROCESS.nRetryInterLock >= MAX_RETRY_COUNT) {

											m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
											PROCESS.nCurrentStep = 1190;
											break;
										}

										LTimerInterLock.Start(m_SystemConfig.GetDelayProcess(DLY_PROC_INTERLOCK_RETRY));
										PROCESS.bOnInterLock = FALSE;
										break;
									}

									SetDOStatus(DO_ON,  DO_SOL_S01_LOADING_BWD);
									SetDOStatus(DO_OFF, DO_SOL_S01_LOADING_FWD);
									LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_MOVE_CYLINDER));

									PROCESS.nCurrentStep++;
									break;
								}

								PROCESS.nCurrentStep = 1190;
							}

							break;

		case	1151	:
							if (GetDIStatus(DI_SENS_S01_LOADING_BWD)) {

								SetDOStatus(DO_OFF, DO_SOL_S01_LOADING_BWD);

								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_CYLINDER));
								PROCESS.nCurrentStep = 1190;
								break;
							}

							// �Ǹ��� Ÿ�Ӿƿ�
							if (LTimerTimeOut.Verify()) {

								if (++PROCESS.nRetryCount > MAX_RETRY_COUNT) {

									PROCESS.bOnError		= TRUE;
									PROCESS.nRetryCount		= 0;
									PROCESS.nRecoveryStep	= 1150;

									PROCESS.stErrorCode.nErrorCode	= ERROR_TOUT_CYLINDER;
									PROCESS.stErrorCode.nSensor		= DI_SENS_S01_LOADING_BWD;
									break;
								}

								PROCESS.nCurrentStep--;
							}

							break;

		case	1190	:
							if (LTimerSteady.Verify()) {

								pOnSCP_MoveParts[SCP_S01_LOADING_BWD] = FALSE;
								PROCESS.nCurrentStep = 0;
							}

							break;


		/////////////////////////////////////////////////////////////
		// ���κ� ///////////////////////////////////////////////////

		// ON
		case	2100	:
							if (LTimerInterLock.Verify()) {

								if (!GetDIStatus(DI_SENS_S01_PROBE_ON)) {

									// ����-�� üũ
									PROCESS.bOnInterLock = FALSE;

									if (PROCESS.bOnInterLock) {

										if (++PROCESS.nRetryInterLock >= MAX_RETRY_COUNT) {

											m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
											PROCESS.nCurrentStep = 2140;
											break;
										}

										LTimerInterLock.Start(m_SystemConfig.GetDelayProcess(DLY_PROC_INTERLOCK_RETRY));
										PROCESS.bOnInterLock = FALSE;
										break;
									}

									SetDOStatus(DO_ON,  DO_SOL_S01_PROBE_ON);
									LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_MOVE_CYLINDER));

									PROCESS.nCurrentStep++;
									break;
								}

								PROCESS.nCurrentStep = 2140;
							}

							break;

		case	2101	:
							if (GetDIStatus(DI_SENS_S01_PROBE_ON)) {

								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_CYLINDER));
								PROCESS.nCurrentStep = 2140;
								break;
							}

							// �Ǹ��� Ÿ�Ӿƿ�
							if (LTimerTimeOut.Verify()) {

								if (++PROCESS.nRetryCount > MAX_RETRY_COUNT) {

									PROCESS.bOnError		= TRUE;
									PROCESS.nRetryCount		= 0;
									PROCESS.nRecoveryStep	= 2100;

									PROCESS.stErrorCode.nErrorCode	= ERROR_TOUT_CYLINDER;
									PROCESS.stErrorCode.nSensor		= DI_SENS_S01_PROBE_ON;
									break;
								}

								PROCESS.nCurrentStep--;
							}

							break;

		case	2140	:
							if (LTimerSteady.Verify()) {

								pOnSCP_MoveParts[SCP_S01_PROBE_ON] = FALSE;
								PROCESS.nCurrentStep = 0;
							}

							break;

		// OFF
		case	2150	:
							if (LTimerInterLock.Verify()) {

								if (!GetDIStatus(DI_SENS_S01_PROBE_OFF)) {

									// ����-�� üũ
									PROCESS.bOnInterLock = FALSE;

									if (PROCESS.bOnInterLock) {

										if (++PROCESS.nRetryInterLock >= MAX_RETRY_COUNT) {

											m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
											PROCESS.nCurrentStep = 2190;
											break;
										}

										LTimerInterLock.Start(m_SystemConfig.GetDelayProcess(DLY_PROC_INTERLOCK_RETRY));
										PROCESS.bOnInterLock = FALSE;
										break;
									}

									SetDOStatus(DO_OFF, DO_SOL_S01_PROBE_ON);
									LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_MOVE_CYLINDER));

									PROCESS.nCurrentStep++;
									break;
								}

								PROCESS.nCurrentStep = 2190;
							}

							break;

		case	2151	:
							if (GetDIStatus(DI_SENS_S01_PROBE_OFF)) {

								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_CYLINDER));
								PROCESS.nCurrentStep = 2190;
								break;
							}

							// �Ǹ��� Ÿ�Ӿƿ�
							if (LTimerTimeOut.Verify()) {

								if (++PROCESS.nRetryCount > MAX_RETRY_COUNT) {

									PROCESS.bOnError		= TRUE;
									PROCESS.nRetryCount		= 0;
									PROCESS.nRecoveryStep	= 2150;

									PROCESS.stErrorCode.nErrorCode	= ERROR_TOUT_CYLINDER;
									PROCESS.stErrorCode.nSensor		= DI_SENS_S01_PROBE_OFF;
									break;
								}

								PROCESS.nCurrentStep--;
							}

							break;

		case	2190	:
							if (LTimerSteady.Verify()) {

								pOnSCP_MoveParts[SCP_S01_PROBE_OFF] = FALSE;
								PROCESS.nCurrentStep = 0;
							}

							break;


		/////////////////////////////////////////////////////////////
		// ���κ� ���̵� ////////////////////////////////////////////

		// ON
		case	2200	:
							if (LTimerInterLock.Verify()) {

								if (m_SystemConfig.UseSystemOption(SOPT_ENABLE_PROBE_GUIDE_UNIT) && !GetDIStatus(DI_SENS_S01_PROBE_ON)) {

									// ����-�� üũ
									PROCESS.bOnInterLock = FALSE;

									if (PROCESS.bOnInterLock) {

										if (++PROCESS.nRetryInterLock >= MAX_RETRY_COUNT) {

											m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
											PROCESS.nCurrentStep = 2240;
											break;
										}

										LTimerInterLock.Start(m_SystemConfig.GetDelayProcess(DLY_PROC_INTERLOCK_RETRY));
										PROCESS.bOnInterLock = FALSE;
										break;
									}

									SetDOStatus(DO_ON,  DO_SOL_S01_PROBE_GUIDE_ON);
									LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_MOVE_CYLINDER));

									PROCESS.nCurrentStep++;
									break;
								}

								PROCESS.nCurrentStep = 2240;
							}

							break;

		case	2201	:
							if (GetDIStatus(DI_SENS_S01_PROBE_GUIDE_ON)) {

								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_CYLINDER));
								PROCESS.nCurrentStep = 2240;
								break;
							}

							// �Ǹ��� Ÿ�Ӿƿ�
							if (LTimerTimeOut.Verify()) {

								if (++PROCESS.nRetryCount > MAX_RETRY_COUNT) {

									PROCESS.bOnError		= TRUE;
									PROCESS.nRetryCount		= 0;
									PROCESS.nRecoveryStep	= 2200;

									PROCESS.stErrorCode.nErrorCode	= ERROR_TOUT_CYLINDER;
									PROCESS.stErrorCode.nSensor		= DI_SENS_S01_PROBE_GUIDE_ON;
									break;
								}

								PROCESS.nCurrentStep--;
							}

							break;

		case	2240	:
							if (LTimerSteady.Verify()) {

								pOnSCP_MoveParts[SCP_S01_PROBE_GUIDE_ON] = FALSE;
								PROCESS.nCurrentStep = 0;
							}

							break;

		// OFF
		case	2250	:
							if (LTimerInterLock.Verify()) {

								if (m_SystemConfig.UseSystemOption(SOPT_ENABLE_PROBE_GUIDE_UNIT) && !GetDIStatus(DI_SENS_S01_PROBE_GUIDE_OFF)) {

									// ����-�� üũ
									PROCESS.bOnInterLock = FALSE;

									if (PROCESS.bOnInterLock) {

										if (++PROCESS.nRetryInterLock >= MAX_RETRY_COUNT) {

											m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
											PROCESS.nCurrentStep = 2290;
											break;
										}

										LTimerInterLock.Start(m_SystemConfig.GetDelayProcess(DLY_PROC_INTERLOCK_RETRY));
										PROCESS.bOnInterLock = FALSE;
										break;
									}

									SetDOStatus(DO_OFF, DO_SOL_S01_PROBE_GUIDE_ON);
									LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_MOVE_CYLINDER));

									PROCESS.nCurrentStep++;
									break;
								}

								PROCESS.nCurrentStep = 2290;
							}

							break;

		case	2251	:
							if (GetDIStatus(DI_SENS_S01_PROBE_GUIDE_OFF)) {

								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_CYLINDER));
								PROCESS.nCurrentStep = 2290;
								break;
							}

							// �Ǹ��� Ÿ�Ӿƿ�
							if (LTimerTimeOut.Verify()) {

								if (++PROCESS.nRetryCount > MAX_RETRY_COUNT) {

									PROCESS.bOnError		= TRUE;
									PROCESS.nRetryCount		= 0;
									PROCESS.nRecoveryStep	= 2250;

									PROCESS.stErrorCode.nErrorCode	= ERROR_TOUT_CYLINDER;
									PROCESS.stErrorCode.nSensor		= DI_SENS_S01_PROBE_GUIDE_OFF;
									break;
								}

								PROCESS.nCurrentStep--;
							}

							break;

		case	2290	:
							if (LTimerSteady.Verify()) {

								pOnSCP_MoveParts[SCP_S01_PROBE_GUIDE_OFF] = FALSE;
								PROCESS.nCurrentStep = 0;
							}

							break;


		/////////////////////////////////////////////////////////////
		// ��ǰ ���� ���� ///////////////////////////////////////////

		// UP
		case	3100	:
							if (LTimerInterLock.Verify()) {

								if (TRUE) {

									// ����-�� üũ
									PROCESS.bOnInterLock = FALSE;

									if (PROCESS.bOnInterLock) {

										if (++PROCESS.nRetryInterLock >= MAX_RETRY_COUNT) {

											m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
											PROCESS.nCurrentStep = 3140;
											break;
										}

										LTimerInterLock.Start(m_SystemConfig.GetDelayProcess(DLY_PROC_INTERLOCK_RETRY));
										PROCESS.bOnInterLock = FALSE;
										break;
									}

									SetDOStatus(DO_ON, DO_SOL_S01_PRODUCT_DOOR_OPEN_UP);
									LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_MOVE_CYLINDER));

									PROCESS.nCurrentStep++;
									break;
								}

								PROCESS.nCurrentStep = 3140;
							}

							break;

		case	3101	:
							if (GetDIStatus(DI_SENS_S01_PRODUCT_DOOR_OPEN_UP)) {

								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_CYLINDER));
								PROCESS.nCurrentStep = 3140;
								break;
							}

							// �Ǹ��� Ÿ�Ӿƿ�
							if (LTimerTimeOut.Verify()) {

								if (++PROCESS.nRetryCount > MAX_RETRY_COUNT) {

									PROCESS.bOnError		= TRUE;
									PROCESS.nRetryCount		= 0;
									PROCESS.nRecoveryStep	= 3100;

									PROCESS.stErrorCode.nErrorCode	= ERROR_TOUT_CYLINDER;
									PROCESS.stErrorCode.nSensor		= DI_SENS_S01_PRODUCT_DOOR_OPEN_UP;
									break;
								}

								PROCESS.nCurrentStep--;
							}

							break;

		case	3140	:
							if (LTimerSteady.Verify()) {

								pOnSCP_MoveParts[SCP_S01_PRODUCT_DOOR_OPEN_UP] = FALSE;
								PROCESS.nCurrentStep = 0;
							}

							break;

		// DN
		case	3150	:
							if (LTimerInterLock.Verify()) {

								if (TRUE) {

									// ����-�� üũ
									PROCESS.bOnInterLock = FALSE;

									if (PROCESS.bOnInterLock) {

										if (++PROCESS.nRetryInterLock >= MAX_RETRY_COUNT) {

											m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
											PROCESS.nCurrentStep = 3190;
											break;
										}

										LTimerInterLock.Start(m_SystemConfig.GetDelayProcess(DLY_PROC_INTERLOCK_RETRY));
										PROCESS.bOnInterLock = FALSE;
										break;
									}

									SetDOStatus(DO_OFF, DO_SOL_S01_PRODUCT_DOOR_OPEN_UP);
									LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_MOVE_CYLINDER));

									PROCESS.nCurrentStep++;
									break;
								}

								PROCESS.nCurrentStep = 3190;
							}

							break;

		case	3151	:
							if (GetDIStatus(DI_SENS_S01_PRODUCT_DOOR_OPEN_DN)) {

								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_CYLINDER));
								PROCESS.nCurrentStep = 3190;
								break;
							}

							// �Ǹ��� Ÿ�Ӿƿ�
							if (LTimerTimeOut.Verify()) {

								if (++PROCESS.nRetryCount > MAX_RETRY_COUNT) {

									PROCESS.bOnError		= TRUE;
									PROCESS.nRetryCount		= 0;
									PROCESS.nRecoveryStep	= 3150;

									PROCESS.stErrorCode.nErrorCode	= ERROR_TOUT_CYLINDER;
									PROCESS.stErrorCode.nSensor		= DI_SENS_S01_PRODUCT_DOOR_OPEN_DN;
									break;
								}

								PROCESS.nCurrentStep--;
							}

							break;

		case	3190	:
							if (LTimerSteady.Verify()) {

								pOnSCP_MoveParts[SCP_S01_PRODUCT_DOOR_OPEN_DN] = FALSE;
								PROCESS.nCurrentStep = 0;
							}

							break;


		/////////////////////////////////////////////////////////////
		// ��ε� ///////////////////////////////////////////////////
		case	6000	:
							if (LTimerInterLock.Verify()) {

								if (TRUE) {

									// ����-�� üũ
									PROCESS.bOnInterLock = FALSE;

									if (PROCESS.bOnInterLock) {

										if (++PROCESS.nRetryInterLock >= MAX_RETRY_COUNT) {

											m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
											PROCESS.nCurrentStep = 6040;
											break;
										}

										LTimerInterLock.Start(m_SystemConfig.GetDelayProcess(DLY_PROC_INTERLOCK_RETRY));
										PROCESS.bOnInterLock = FALSE;
										break;
									}

									SetDOStatus(DO_OFF, DO_SOL_S01_PROBE_ON);
									SetDOStatus(DO_OFF, DO_SOL_S01_PROBE_GUIDE_ON);
									SetDOStatus(DO_OFF, DO_SOL_S01_PRODUCT_DOOR_OPEN_UP);
									LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_MOVE_CYLINDER));

									PROCESS.nCurrentStep++;
									break;
								}

								PROCESS.nCurrentStep = 6040;
							}

							break;

		case	6001	:
							if (GetDIStatus(DI_SENS_S01_PROBE_OFF) && GetDIStatus(DI_SENS_S01_PRODUCT_DOOR_OPEN_DN) &&
								(m_SystemConfig.UseSystemOption(SOPT_ENABLE_PROBE_GUIDE_UNIT) || GetDIStatus(DI_SENS_S01_PROBE_GUIDE_OFF))) {

								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_CYLINDER));
								PROCESS.nCurrentStep = 6040;
								break;
							}

							// �Ǹ��� Ÿ�Ӿƿ�
							if (LTimerTimeOut.Verify()) {

								if (++PROCESS.nRetryCount > MAX_RETRY_COUNT) {

									PROCESS.bOnError		= TRUE;
									PROCESS.nRetryCount		= 0;
									PROCESS.nRecoveryStep	= 6000;

									PROCESS.stErrorCode.nErrorCode	= ERROR_TOUT_CYLINDER;
									PROCESS.stErrorCode.nSensor		= GetDIStatus(DI_SENS_S01_PROBE_OFF) ? DI_SENS_S01_PRODUCT_DOOR_OPEN_DN : DI_SENS_S01_PROBE_OFF;
									if (m_SystemConfig.UseSystemOption(SOPT_ENABLE_PROBE_GUIDE_UNIT) && !GetDIStatus(DI_SENS_S01_PROBE_GUIDE_OFF))
										PROCESS.stErrorCode.nSensor = DI_SENS_S01_PROBE_GUIDE_OFF;

									break;
								}

								PROCESS.nCurrentStep--;
							}

							break;

		case	6040	:
							if (LTimerSteady.Verify()) {

								pOnSCP_MoveParts[SCP_S01_UNLOADING] = FALSE;
								PROCESS.nCurrentStep = 0;
							}

							break;


		/////////////////////////////////////////////////////////////
		// �Ͻ� ���� ���� ///////////////////////////////////////////
		case	STEP_PAUSE	:
								if (m_stSystemStatus.bOnEmergencyStop) {

									PROCESS.nCurrentStep = STEP_EMG;
									break;
								}

								if (!m_stSystemStatus.bOnPause && !m_stSystemStatus.bOnAlarmSystem && !m_stSystemStatus.bOnAlarmStation[nSTATION_NO])		
									PROCESS.nCurrentStep = 20001;

								break;

		// ���� ����
		case	20001	:
							PROCESS.nCurrentStep	= PROCESS.nRecoveryStep;
							PROCESS.bOnPause		= FALSE;
							break;


		/////////////////////////////////////////////////////////////
		// ��� ���� ���� ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop)	{

									ZeroMemory(pOnSCP_MoveParts, sizeof(BOOL) * nPARTS_COUNT);

									PROCESS.nRecoveryStep	= 0;
									PROCESS.nCurrentStep	= STEP_PAUSE;
								}

								break;
	}


	/////////////////////////////////////////////////////////////////
	// ����-�� ���� /////////////////////////////////////////////////
	if (PROCESS.bOnInterLock) {
	
		if (m_nTypeLanguage == LANGUAGE_KOR)	ErrorMessage(TRUE, _T("[S%02d] ����-�� ����!"), nSTATION_NO);
		else									ErrorMessage(TRUE, _T("[S%02d] INTER-LOCK ERROR!"), nSTATION_NO);

		PROCESS.bOnInterLock = FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// ���� �߻� ////////////////////////////////////////////////////
	if (PROCESS.bOnError) {

		PROCESS.pstErrorCode = new (std::nothrow) ERROR_CODE_T;
		if (PROCESS.pstErrorCode)	*(PROCESS.pstErrorCode) = PROCESS.stErrorCode;

		if (!m_stSystemStatus.bOnOperating) {

			PROCESS.nCurrentStep = 0;
			m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
			ZeroMemory(pOnSCP_MoveParts, sizeof(BOOL) * nPARTS_COUNT);

		} else {

			// ���� ����
			PROCESS.nCurrentStep = PROCESS.nRecoveryStep;

			// ���� �˶� ����
			m_stSystemStatus.bOnAlarmStation[nSTATION_NO] = TRUE;

			// �Ͻ� ����
// 			m_stSystemStatus.bOnPause = TRUE;	
// 			if (m_pMainWnd && m_pMainWnd->GetSafeHwnd())
// 				m_pMainWnd->PostMessage(UM_MAIN_PAUSE);
		}
	}


	return	PROCESS.pstErrorCode;
}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� (����) : ���� #02 - �˻� ���� (SK) ////////////////////////////////
PERROR_CODE_T CMainApp::ProcessStation02Parts(void)
{
	static	PROCESS_CTRL_T		PROCESS;

	static	UINT				nSTATION_NO				= STATION_1;
	static	UINT				nSTATION_SUB_NO			= 0;
	static	UINT				nPARTS_COUNT			= MAX_STATION_CONTROL_PARTS_02;
			PBOOL				pOnSCP_MoveParts		= m_stSystemStatus.bOnSCP_MoveParts[nSTATION_NO];

	static	LTimerMsec			LTimerProceed;
	static	LTimerMsec			LTimerTimeOut;
	static	LTimerMsec			LTimerSteady;
	static	LTimerMsec			LTimerInterLock;


	/////////////////////////////////////////////////////////////////
	// ���μ��� ������ �ʱ�ȭ ///////////////////////////////////////
	ProcessDataInitialize(PROCESS);


	/////////////////////////////////////////////////////////////////
	// �ڵ� ���� ����/���� �ʱ�ȭ ///////////////////////////////////
	if (CheckProcessOperating(PROCESS) || m_SystemConfig.IsSimulationMode()) {
	
		ZeroMemory(pOnSCP_MoveParts, sizeof(BOOL) * nPARTS_COUNT);
	}


	/////////////////////////////////////////////////////////////////
	// ���� ���� ��� ///////////////////////////////////////////////
	if (CheckProcessManualControlMode(nSTATION_NO, PROCESS)) {
	
		ZeroMemory(pOnSCP_MoveParts, sizeof(BOOL) * nPARTS_COUNT);
	}


	/////////////////////////////////////////////////////////////////
	// ���/�Ͻ� ���� ���� //////////////////////////////////////////
	if (CheckProcessEmergencyStop(PROCESS))					return	NULL;
	if (CheckProcessOperatingPause(nSTATION_NO, PROCESS))	return	NULL;
	

	/////////////////////////////////////////////////////////////////
	// ���� ���μ��� ////////////////////////////////////////////////
	switch (PROCESS.nCurrentStep) {

		case	0		:
							PROCESS.nCurrentStep = 10;
							break;


		/////////////////////////////////////////////////////////////
		// �ε��� ///////////////////////////////////////////////////
		case	10		:
							PROCESS.nRetryCount		= 0;
							PROCESS.nRetryInterLock	= 0;
							PROCESS.nActionCount	= 0;
							PROCESS.bOnInterLock	= FALSE;

							if (pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_1_UP])		{ PROCESS.nCurrentStep = 1100; break; }
							if (pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_1_DN])		{ PROCESS.nCurrentStep = 1150; break; }
							if (pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_2_UP])		{ PROCESS.nCurrentStep = 1200; break; }
							if (pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_2_DN])		{ PROCESS.nCurrentStep = 1250; break; }
							if (pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_A_UP])		{ PROCESS.nCurrentStep = 1300; break; }
							if (pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_A_DN])		{ PROCESS.nCurrentStep = 1350; break; }
							if (pOnSCP_MoveParts[SCP_S02_PROBE_ON])						{ PROCESS.nCurrentStep = 2100; break; }
							if (pOnSCP_MoveParts[SCP_S02_PROBE_OFF])					{ PROCESS.nCurrentStep = 2150; break; }
							if (pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_OPEN_UP])			{ PROCESS.nCurrentStep = 3100; break; }
							if (pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_OPEN_DN])			{ PROCESS.nCurrentStep = 3150; break; }
							if (pOnSCP_MoveParts[SCP_S02_UNLOADING])					{ PROCESS.nCurrentStep = 6000; break; }
							
							break;


		/////////////////////////////////////////////////////////////
		// ��ǰ ���� ���� #1 ////////////////////////////////////////

		// UP
		case	1100	:
							if (LTimerInterLock.Verify()) {

								if (TRUE) {

									// ����-�� üũ
									PROCESS.bOnInterLock = FALSE;

									if (PROCESS.bOnInterLock) {

										if (++PROCESS.nRetryInterLock >= MAX_RETRY_COUNT) {

											m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
											PROCESS.nCurrentStep = 1140;
											break;
										}

										LTimerInterLock.Start(m_SystemConfig.GetDelayProcess(DLY_PROC_INTERLOCK_RETRY));
										PROCESS.bOnInterLock = FALSE;
										break;
									}

									SetDOStatus(DO_OFF, DO_SOL_S02_PRODUCT_DOOR_PUSHER_1_DN);
									LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_MOVE_CYLINDER));

									PROCESS.nCurrentStep++;
									break;
								}

								PROCESS.nCurrentStep = 1140;
							}

							break;

		case	1101	:
							if (GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_1_UP)) {

								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_CYLINDER));
								PROCESS.nCurrentStep = 1140;
								break;
							}

							// �Ǹ��� Ÿ�Ӿƿ�
							if (LTimerTimeOut.Verify()) {

								if (++PROCESS.nRetryCount > MAX_RETRY_COUNT) {

									PROCESS.bOnError		= TRUE;
									PROCESS.nRetryCount		= 0;
									PROCESS.nRecoveryStep	= 1100;

									PROCESS.stErrorCode.nErrorCode	= ERROR_TOUT_CYLINDER;
									PROCESS.stErrorCode.nSensor		= DI_SENS_S02_PRODUCT_DOOR_PUSHER_1_UP;
									break;
								}

								PROCESS.nCurrentStep--;
							}

							break;

		case	1140	:
							if (LTimerSteady.Verify()) {

								pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_1_UP] = FALSE;
								PROCESS.nCurrentStep = 0;
							}

							break;

		// DN
		case	1150	:
							if (LTimerInterLock.Verify()) {

								if (TRUE) {

									// ����-�� üũ
									PROCESS.bOnInterLock = FALSE;

									if (PROCESS.bOnInterLock) {

										if (++PROCESS.nRetryInterLock >= MAX_RETRY_COUNT) {

											m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
											PROCESS.nCurrentStep = 1190;
											break;
										}

										LTimerInterLock.Start(m_SystemConfig.GetDelayProcess(DLY_PROC_INTERLOCK_RETRY));
										PROCESS.bOnInterLock = FALSE;
										break;
									}

									SetDOStatus(DO_ON, DO_SOL_S02_PRODUCT_DOOR_PUSHER_1_DN);
									LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_MOVE_CYLINDER));

									PROCESS.nCurrentStep++;
									break;
								}

								PROCESS.nCurrentStep = 1190;
							}

							break;

		case	1151	:
							if (GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_1_DN)) {

								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_CYLINDER));
								PROCESS.nCurrentStep = 1190;
								break;
							}

							// �Ǹ��� Ÿ�Ӿƿ�
							if (LTimerTimeOut.Verify()) {

								if (++PROCESS.nRetryCount > MAX_RETRY_COUNT) {

									PROCESS.bOnError		= TRUE;
									PROCESS.nRetryCount		= 0;
									PROCESS.nRecoveryStep	= 1150;

									PROCESS.stErrorCode.nErrorCode	= ERROR_TOUT_CYLINDER;
									PROCESS.stErrorCode.nSensor		= DI_SENS_S02_PRODUCT_DOOR_PUSHER_1_DN;
									break;
								}

								PROCESS.nCurrentStep--;
							}

							break;

		case	1190	:
							if (LTimerSteady.Verify()) {

								pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_1_DN] = FALSE;
								PROCESS.nCurrentStep = 0;
							}

							break;


		/////////////////////////////////////////////////////////////
		// ��ǰ ���� ���� #2 ////////////////////////////////////////

		// UP
		case	1200	:
							if (LTimerInterLock.Verify()) {

								if (TRUE) {

									// ����-�� üũ
									PROCESS.bOnInterLock = FALSE;

									if (PROCESS.bOnInterLock) {

										if (++PROCESS.nRetryInterLock >= MAX_RETRY_COUNT) {

											m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
											PROCESS.nCurrentStep = 1240;
											break;
										}

										LTimerInterLock.Start(m_SystemConfig.GetDelayProcess(DLY_PROC_INTERLOCK_RETRY));
										PROCESS.bOnInterLock = FALSE;
										break;
									}

									SetDOStatus(DO_OFF, DO_SOL_S02_PRODUCT_DOOR_PUSHER_2_DN);
									LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_MOVE_CYLINDER));

									PROCESS.nCurrentStep++;
									break;
								}

								PROCESS.nCurrentStep = 1240;
							}

							break;

		case	1201	:
							if (GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_2_UP)) {

								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_CYLINDER));
								PROCESS.nCurrentStep = 1240;
								break;
							}

							// �Ǹ��� Ÿ�Ӿƿ�
							if (LTimerTimeOut.Verify()) {

								if (++PROCESS.nRetryCount > MAX_RETRY_COUNT) {

									PROCESS.bOnError		= TRUE;
									PROCESS.nRetryCount		= 0;
									PROCESS.nRecoveryStep	= 1200;

									PROCESS.stErrorCode.nErrorCode	= ERROR_TOUT_CYLINDER;
									PROCESS.stErrorCode.nSensor		= DI_SENS_S02_PRODUCT_DOOR_PUSHER_2_UP;
									break;
								}

								PROCESS.nCurrentStep--;
							}

							break;

		case	1240	:
							if (LTimerSteady.Verify()) {

								pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_2_UP] = FALSE;
								PROCESS.nCurrentStep = 0;
							}

							break;

		// DN
		case	1250	:
							if (LTimerInterLock.Verify()) {

								if (TRUE) {

									// ����-�� üũ
									PROCESS.bOnInterLock = FALSE;

									if (PROCESS.bOnInterLock) {

										if (++PROCESS.nRetryInterLock >= MAX_RETRY_COUNT) {

											m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
											PROCESS.nCurrentStep = 1290;
											break;
										}

										LTimerInterLock.Start(m_SystemConfig.GetDelayProcess(DLY_PROC_INTERLOCK_RETRY));
										PROCESS.bOnInterLock = FALSE;
										break;
									}

									SetDOStatus(DO_ON, DO_SOL_S02_PRODUCT_DOOR_PUSHER_2_DN);
									LTimerProceed.Start(m_stSystemStatus.nSCP_TimeDoorPushLockDown);
									LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_MOVE_CYLINDER));

									PROCESS.nCurrentStep++;
									break;
								}

								PROCESS.nCurrentStep = 1290;
							}

							break;

		case	1251	:
							if (GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_2_DN)) {

								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_CYLINDER));
								PROCESS.nCurrentStep = 1290;
								break;
							}

							if (m_stSystemStatus.nSCP_TimeDoorPushLockDown > 0 && LTimerProceed.Verify()) {
							
								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_CYLINDER));
								PROCESS.nCurrentStep = 1290;
								break;
							}

							// �Ǹ��� Ÿ�Ӿƿ�
							if (LTimerTimeOut.Verify()) {

								if (++PROCESS.nRetryCount > MAX_RETRY_COUNT) {

									PROCESS.bOnError		= TRUE;
									PROCESS.nRetryCount		= 0;
									PROCESS.nRecoveryStep	= 1250;

									PROCESS.stErrorCode.nErrorCode	= ERROR_TOUT_CYLINDER;
									PROCESS.stErrorCode.nSensor		= DI_SENS_S02_PRODUCT_DOOR_PUSHER_2_DN;
									break;
								}

								PROCESS.nCurrentStep--;
							}

							break;

		case	1290	:
							if (LTimerSteady.Verify()) {

								pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_2_DN] = FALSE;
								PROCESS.nCurrentStep = 0;
							}

							break;


		/////////////////////////////////////////////////////////////
		// ��ǰ ���� ���� (A) ///////////////////////////////////////

		// UP
		case	1300	:
							if (LTimerInterLock.Verify()) {

								if (TRUE) {

									// ����-�� üũ
									PROCESS.bOnInterLock = FALSE;

									if (PROCESS.bOnInterLock) {

										if (++PROCESS.nRetryInterLock >= MAX_RETRY_COUNT) {

											m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
											PROCESS.nCurrentStep = 1340;
											break;
										}

										LTimerInterLock.Start(m_SystemConfig.GetDelayProcess(DLY_PROC_INTERLOCK_RETRY));
										PROCESS.bOnInterLock = FALSE;
										break;
									}

									SetDOStatus(DO_OFF, DO_SOL_S02_PRODUCT_DOOR_PUSHER_1_DN);
									SetDOStatus(DO_OFF, DO_SOL_S02_PRODUCT_DOOR_PUSHER_2_DN);
									LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_MOVE_CYLINDER));

									PROCESS.nCurrentStep++;
									break;
								}

								PROCESS.nCurrentStep = 1340;
							}

							break;

		case	1301	:
							if (GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_1_UP) &&
								GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_2_UP)) {

								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_CYLINDER));
								PROCESS.nCurrentStep = 1340;
								break;
							}

							// �Ǹ��� Ÿ�Ӿƿ�
							if (LTimerTimeOut.Verify()) {

								if (++PROCESS.nRetryCount > MAX_RETRY_COUNT) {

									PROCESS.bOnError		= TRUE;
									PROCESS.nRetryCount		= 0;
									PROCESS.nRecoveryStep	= 1300;

									PROCESS.stErrorCode.nErrorCode	= ERROR_TOUT_CYLINDER;
									PROCESS.stErrorCode.nSensor		= DI_SENS_S02_PRODUCT_DOOR_PUSHER_1_UP;
									if (!GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_2_UP))		PROCESS.stErrorCode.nSensor	= DI_SENS_S02_PRODUCT_DOOR_PUSHER_2_UP;
									break;
								}

								PROCESS.nCurrentStep--;
							}

							break;

		case	1340	:
							if (LTimerSteady.Verify()) {

								pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_A_UP] = FALSE;
								PROCESS.nCurrentStep = 0;
							}

							break;

		// DN
		case	1350	:
							if (LTimerInterLock.Verify()) {

								if (TRUE) {

									// ����-�� üũ
									PROCESS.bOnInterLock = FALSE;

									if (PROCESS.bOnInterLock) {

										if (++PROCESS.nRetryInterLock >= MAX_RETRY_COUNT) {

											m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
											PROCESS.nCurrentStep = 1390;
											break;
										}

										LTimerInterLock.Start(m_SystemConfig.GetDelayProcess(DLY_PROC_INTERLOCK_RETRY));
										PROCESS.bOnInterLock = FALSE;
										break;
									}

									SetDOStatus(DO_ON, DO_SOL_S02_PRODUCT_DOOR_PUSHER_1_DN);
									SetDOStatus(DO_ON, DO_SOL_S02_PRODUCT_DOOR_PUSHER_2_DN);
									LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_MOVE_CYLINDER));

									PROCESS.nCurrentStep++;
									break;
								}

								PROCESS.nCurrentStep = 1390;
							}

							break;

		case	1351	:
							if (GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_1_DN) &&
								GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_2_DN)) {

								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_CYLINDER));
								PROCESS.nCurrentStep = 1390;
								break;
							}

							// �Ǹ��� Ÿ�Ӿƿ�
							if (LTimerTimeOut.Verify()) {

								if (++PROCESS.nRetryCount > MAX_RETRY_COUNT) {

									PROCESS.bOnError		= TRUE;
									PROCESS.nRetryCount		= 0;
									PROCESS.nRecoveryStep	= 1350;

									PROCESS.stErrorCode.nErrorCode	= ERROR_TOUT_CYLINDER;
									PROCESS.stErrorCode.nSensor		= DI_SENS_S02_PRODUCT_DOOR_PUSHER_1_DN;
									if (!GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_2_DN))		PROCESS.stErrorCode.nSensor	= DI_SENS_S02_PRODUCT_DOOR_PUSHER_2_DN;
									break;
								}

								PROCESS.nCurrentStep--;
							}

							break;

		case	1390	:
							if (LTimerSteady.Verify()) {

								pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_A_DN] = FALSE;
								PROCESS.nCurrentStep = 0;
							}

							break;


		/////////////////////////////////////////////////////////////
		// ���κ� ///////////////////////////////////////////////////

		// ON
		case	2100	:
							if (LTimerInterLock.Verify()) {

								if (TRUE) {

									// ����-�� üũ
									PROCESS.bOnInterLock = FALSE;

									if (PROCESS.bOnInterLock) {

										if (++PROCESS.nRetryInterLock >= MAX_RETRY_COUNT) {

											m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
											PROCESS.nCurrentStep = 2140;
											break;
										}

										LTimerInterLock.Start(m_SystemConfig.GetDelayProcess(DLY_PROC_INTERLOCK_RETRY));
										PROCESS.bOnInterLock = FALSE;
										break;
									}

									SetDOStatus(DO_ON,  DO_SOL_S02_PROBE_ON);
									LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_MOVE_CYLINDER));

									PROCESS.nCurrentStep++;
									break;
								}

								PROCESS.nCurrentStep = 2140;
							}

							break;

		case	2101	:
							if (GetDIStatus(DI_SENS_S02_PROBE_ON)) {

								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_CYLINDER));
								PROCESS.nCurrentStep = 2140;
								break;
							}

							// �Ǹ��� Ÿ�Ӿƿ�
							if (LTimerTimeOut.Verify()) {

								if (++PROCESS.nRetryCount > MAX_RETRY_COUNT) {

									PROCESS.bOnError		= TRUE;
									PROCESS.nRetryCount		= 0;
									PROCESS.nRecoveryStep	= 2100;

									PROCESS.stErrorCode.nErrorCode	= ERROR_TOUT_CYLINDER;
									PROCESS.stErrorCode.nSensor		= DI_SENS_S02_PROBE_ON;
									break;
								}

								PROCESS.nCurrentStep--;
							}

							break;

		case	2140	:
							if (LTimerSteady.Verify()) {

								pOnSCP_MoveParts[SCP_S02_PROBE_ON] = FALSE;
								PROCESS.nCurrentStep = 0;
							}

							break;

		// OFF
		case	2150	:
							if (LTimerInterLock.Verify()) {

								if (TRUE) {

									// ����-�� üũ
									PROCESS.bOnInterLock = FALSE;

									if (PROCESS.bOnInterLock) {

										if (++PROCESS.nRetryInterLock >= MAX_RETRY_COUNT) {

											m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
											PROCESS.nCurrentStep = 2190;
											break;
										}

										LTimerInterLock.Start(m_SystemConfig.GetDelayProcess(DLY_PROC_INTERLOCK_RETRY));
										PROCESS.bOnInterLock = FALSE;
										break;
									}

									SetDOStatus(DO_OFF, DO_SOL_S02_PROBE_ON);
									LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_MOVE_CYLINDER));

									PROCESS.nCurrentStep++;
									break;
								}

								PROCESS.nCurrentStep = 2190;
							}

							break;

		case	2151	:
							if (GetDIStatus(DI_SENS_S02_PROBE_OFF)) {

								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_CYLINDER));
								PROCESS.nCurrentStep = 2190;
								break;
							}

							// �Ǹ��� Ÿ�Ӿƿ�
							if (LTimerTimeOut.Verify()) {

								if (++PROCESS.nRetryCount > MAX_RETRY_COUNT) {

									PROCESS.bOnError		= TRUE;
									PROCESS.nRetryCount		= 0;
									PROCESS.nRecoveryStep	= 2150;

									PROCESS.stErrorCode.nErrorCode	= ERROR_TOUT_CYLINDER;
									PROCESS.stErrorCode.nSensor		= DI_SENS_S02_PROBE_OFF;
									break;
								}

								PROCESS.nCurrentStep--;
							}

							break;

		case	2190	:
							if (LTimerSteady.Verify()) {

								pOnSCP_MoveParts[SCP_S02_PROBE_OFF] = FALSE;
								PROCESS.nCurrentStep = 0;
							}

							break;


		/////////////////////////////////////////////////////////////
		// ��ǰ ���� ���� ///////////////////////////////////////////

		// UP
		case	3100	:
							if (LTimerInterLock.Verify()) {

								if (TRUE) {

									// ����-�� üũ
									PROCESS.bOnInterLock = FALSE;

									if (PROCESS.bOnInterLock) {

										if (++PROCESS.nRetryInterLock >= MAX_RETRY_COUNT) {

											m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
											PROCESS.nCurrentStep = 3140;
											break;
										}

										LTimerInterLock.Start(m_SystemConfig.GetDelayProcess(DLY_PROC_INTERLOCK_RETRY));
										PROCESS.bOnInterLock = FALSE;
										break;
									}

									SetDOStatus(DO_ON, DO_SOL_S02_PRODUCT_DOOR_OPEN_UP);
									LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_MOVE_CYLINDER));

									PROCESS.nCurrentStep++;
									break;
								}

								PROCESS.nCurrentStep = 3140;
							}

							break;

		case	3101	:
							if (GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_OPEN_UP)) {

								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_CYLINDER));
								PROCESS.nCurrentStep = 3140;
								break;
							}

							// �Ǹ��� Ÿ�Ӿƿ�
							if (LTimerTimeOut.Verify()) {

								if (++PROCESS.nRetryCount > MAX_RETRY_COUNT) {

									PROCESS.bOnError		= TRUE;
									PROCESS.nRetryCount		= 0;
									PROCESS.nRecoveryStep	= 3100;

									PROCESS.stErrorCode.nErrorCode	= ERROR_TOUT_CYLINDER;
									PROCESS.stErrorCode.nSensor		= DI_SENS_S02_PRODUCT_DOOR_OPEN_UP;
									break;
								}

								PROCESS.nCurrentStep--;
							}

							break;

		case	3140	:
							if (LTimerSteady.Verify()) {

								pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_OPEN_UP] = FALSE;
								PROCESS.nCurrentStep = 0;
							}

							break;

		// DN
		case	3150	:
							if (LTimerInterLock.Verify()) {

								if (TRUE) {

									// ����-�� üũ
									PROCESS.bOnInterLock = FALSE;

									if (PROCESS.bOnInterLock) {

										if (++PROCESS.nRetryInterLock >= MAX_RETRY_COUNT) {

											m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
											PROCESS.nCurrentStep = 3190;
											break;
										}

										LTimerInterLock.Start(m_SystemConfig.GetDelayProcess(DLY_PROC_INTERLOCK_RETRY));
										PROCESS.bOnInterLock = FALSE;
										break;
									}

									SetDOStatus(DO_OFF, DO_SOL_S02_PRODUCT_DOOR_OPEN_UP);
									LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_MOVE_CYLINDER));

									PROCESS.nCurrentStep++;
									break;
								}

								PROCESS.nCurrentStep = 3190;
							}

							break;

		case	3151	:
							if (GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_OPEN_DN)) {

								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_CYLINDER));
								PROCESS.nCurrentStep = 3190;
								break;
							}

							// �Ǹ��� Ÿ�Ӿƿ�
							if (LTimerTimeOut.Verify()) {

								if (++PROCESS.nRetryCount > MAX_RETRY_COUNT) {

									PROCESS.bOnError		= TRUE;
									PROCESS.nRetryCount		= 0;
									PROCESS.nRecoveryStep	= 3150;

									PROCESS.stErrorCode.nErrorCode	= ERROR_TOUT_CYLINDER;
									PROCESS.stErrorCode.nSensor		= DI_SENS_S02_PRODUCT_DOOR_OPEN_DN;
									break;
								}

								PROCESS.nCurrentStep--;
							}

							break;

		case	3190	:
							if (LTimerSteady.Verify()) {

								pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_OPEN_DN] = FALSE;
								PROCESS.nCurrentStep = 0;
							}

							break;


		/////////////////////////////////////////////////////////////
		// ��ε� ///////////////////////////////////////////////////
		case	6000	:
							if (LTimerInterLock.Verify()) {

								if (TRUE) {

									// ����-�� üũ
									PROCESS.bOnInterLock = FALSE;

									if (PROCESS.bOnInterLock) {

										if (++PROCESS.nRetryInterLock >= MAX_RETRY_COUNT) {

											m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
											PROCESS.nCurrentStep = 6040;
											break;
										}

										LTimerInterLock.Start(m_SystemConfig.GetDelayProcess(DLY_PROC_INTERLOCK_RETRY));
										PROCESS.bOnInterLock = FALSE;
										break;
									}

									SetDOStatus(DO_OFF, DO_SOL_S02_PROBE_ON);
									SetDOStatus(DO_OFF, DO_SOL_S02_PRODUCT_DOOR_OPEN_UP);
									SetDOStatus(DO_OFF, DO_SOL_S02_PRODUCT_DOOR_PUSHER_1_DN);
									SetDOStatus(DO_OFF, DO_SOL_S02_PRODUCT_DOOR_PUSHER_2_DN);
									LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_MOVE_CYLINDER));

									PROCESS.nCurrentStep++;
									break;
								}

								PROCESS.nCurrentStep = 6040;
							}

							break;

		case	6001	:
							if (GetDIStatus(DI_SENS_S02_PROBE_OFF) && GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_OPEN_DN) &&
								GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_1_UP) && GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_2_UP)) {

								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_CYLINDER));
								PROCESS.nCurrentStep = 6040;
								break;
							}

							// �Ǹ��� Ÿ�Ӿƿ�
							if (LTimerTimeOut.Verify()) {

								if (++PROCESS.nRetryCount > MAX_RETRY_COUNT) {

									PROCESS.bOnError		= TRUE;
									PROCESS.nRetryCount		= 0;
									PROCESS.nRecoveryStep	= 6000;

									PROCESS.stErrorCode.nErrorCode	= ERROR_TOUT_CYLINDER;
									PROCESS.stErrorCode.nSensor		= DI_SENS_S02_PROBE_OFF;
									if (!GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_OPEN_DN))			PROCESS.stErrorCode.nSensor = DI_SENS_S02_PRODUCT_DOOR_OPEN_DN;
									if (!GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_1_UP))		PROCESS.stErrorCode.nSensor = DI_SENS_S02_PRODUCT_DOOR_PUSHER_1_UP;
									if (!GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_2_UP))		PROCESS.stErrorCode.nSensor = DI_SENS_S02_PRODUCT_DOOR_PUSHER_2_UP;

									break;
								}

								PROCESS.nCurrentStep--;
							}

							break;

		case	6040	:
							if (LTimerSteady.Verify()) {

								pOnSCP_MoveParts[SCP_S02_UNLOADING] = FALSE;
								PROCESS.nCurrentStep = 0;
							}

							break;


		/////////////////////////////////////////////////////////////
		// �Ͻ� ���� ���� ///////////////////////////////////////////
		case	STEP_PAUSE	:
								if (m_stSystemStatus.bOnEmergencyStop) {

									PROCESS.nCurrentStep = STEP_EMG;
									break;
								}

								if (!m_stSystemStatus.bOnPause && !m_stSystemStatus.bOnAlarmSystem && !m_stSystemStatus.bOnAlarmStation[nSTATION_NO])		
									PROCESS.nCurrentStep = 20001;

								break;

		// ���� ����
		case	20001	:
							PROCESS.nCurrentStep	= PROCESS.nRecoveryStep;
							PROCESS.bOnPause		= FALSE;
							break;


		/////////////////////////////////////////////////////////////
		// ��� ���� ���� ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop)	{

									ZeroMemory(pOnSCP_MoveParts, sizeof(BOOL) * nPARTS_COUNT);

									PROCESS.nRecoveryStep	= 0;
									PROCESS.nCurrentStep	= STEP_PAUSE;
								}

								break;
	}


	/////////////////////////////////////////////////////////////////
	// ����-�� ���� /////////////////////////////////////////////////
	if (PROCESS.bOnInterLock) {
	
		if (m_nTypeLanguage == LANGUAGE_KOR)	ErrorMessage(TRUE, _T("[S%02d] ����-�� ����!"), nSTATION_NO);
		else									ErrorMessage(TRUE, _T("[S%02d] INTER-LOCK ERROR!"), nSTATION_NO);

		PROCESS.bOnInterLock = FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// ���� �߻� ////////////////////////////////////////////////////
	if (PROCESS.bOnError) {

		PROCESS.pstErrorCode = new (std::nothrow) ERROR_CODE_T;
		if (PROCESS.pstErrorCode)	*(PROCESS.pstErrorCode) = PROCESS.stErrorCode;

		if (!m_stSystemStatus.bOnOperating) {

			PROCESS.nCurrentStep = 0;
			m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
			ZeroMemory(pOnSCP_MoveParts, sizeof(BOOL) * nPARTS_COUNT);

		} else {

			// ���� ����
			PROCESS.nCurrentStep = PROCESS.nRecoveryStep;

			// ���� �˶� ����
			m_stSystemStatus.bOnAlarmStation[nSTATION_NO] = TRUE;

			// �Ͻ� ����
// 			m_stSystemStatus.bOnPause = TRUE;	
// 			if (m_pMainWnd && m_pMainWnd->GetSafeHwnd())
// 				m_pMainWnd->PostMessage(UM_MAIN_PAUSE);
		}
	}


	return	PROCESS.pstErrorCode;
}








///////////////////////////////////////////////////////////////////////////////////////////////////
// ��Ÿ ���μ��� //////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ���μ��� : ����̽� (LOADCELL) /////////////////////////////////////////////
PERROR_CODE_T CMainApp::ProcessDeviceLC(void)
{
	static	PROCESS_CTRL_T		PROCESS;

	static	UINT				nCurrentLoadCellNo		= 0;
	static	BYTE				byReadByte				= 0;

	static	CHAR				szRcvdPacket[MAX_LOADCELL_CHANNEL_USE][COMM_PACKET_SIZE];
	static	UINT				nRcvdPacketIndex[MAX_LOADCELL_CHANNEL_USE];
	static	BOOL				bOnReceiveData[MAX_LOADCELL_CHANNEL_USE];
	static	BOOL				bIsFirstScan[MAX_LOADCELL_CHANNEL_USE];

	static	LTimerMsec			LTimerProceed;
	static	LTimerMsec			LTimerAlarm;
	static	LTimerMsec			LTimerSensor;
	static	LTimerMsec			LTimerSteady;
	static	LTimerMsec			LTimerTimeOut[MAX_LOADCELL_CHANNEL_USE];
	static	LTimerMsec			LTimerWaitProduct;
	static	LTimerMsec			LTimerSystemMonitor;
	static	LTimerMsec			LTimerSystemDisplay;


	/////////////////////////////////////////////////////////////////
	// ���μ��� ������ �ʱ�ȭ ///////////////////////////////////////
	ProcessDataInitialize(PROCESS);


	/////////////////////////////////////////////////////////////////
	// ���� ���μ��� ////////////////////////////////////////////////
	switch (PROCESS.nCurrentStep) {

		case	0		:
							// LOADCELL ���� ��� �ð� ����
							LTimerProceed.Start(m_SystemConfig.GetDelaySystem(DLY_SYS_WAIT_LC_MEASUREMENT_START));

							// ��� ���� �ʱ�ȭ
							m_Comm[COMM_DEV_LCC_1].ClearBuffer();
							m_Comm[COMM_DEV_LCC_2].ClearBuffer();
							m_Comm[COMM_DEV_LCC_3].ClearBuffer();

							// �÷��� �ʱ�ȭ
							nCurrentLoadCellNo	= LOADCELL_CH01;

							// �ε弿 ������ �ʱ�ȭ
							for (UINT nIndex = 0; nIndex < MAX_LOADCELL_CHANNEL_USE; nIndex++) {

								m_stSystemStatus.nStatusLoadCellData[nIndex]	= LCDT_STABLE;
								m_stSystemStatus.dblMeasurementLoadCell[nIndex]	= 0;
							
								bOnReceiveData[nIndex] = FALSE;
								LTimerTimeOut[nIndex].Start(m_SystemConfig.GetDelaySystem(DLY_SYS_TOUT_LOADCELL_DATA));
							}

							PROCESS.nCurrentStep = 110;
							break;

		// �ε弿 ���� ����
		case	110		:
							if (LTimerProceed.Verify()) {

								UINT	nTypeLoadCell	= m_SystemConfig.GetLoadCellType();

								if (nTypeLoadCell == LOADCELL_TYPE_STREAM)	
									PROCESS.nCurrentStep = 200;
							}

							break;


		/////////////////////////////////////////////////////////////
		// �ε弿 ���� (��Ʈ�� ���) ////////////////////////////////
		case	200		:
							if (!m_SystemConfig.UseSystemOption(SOPT_DISABLE_LOADCELL_01 + nCurrentLoadCellNo)) {

								if (m_stSystemStatus.nDeviceStatus[SD_DEV_LCC_1 + nCurrentLoadCellNo] == DS_NONE ||
									m_stSystemStatus.nDeviceStatus[SD_DEV_LCC_1 + nCurrentLoadCellNo] == DS_NORMAL ||
									m_stSystemStatus.nDeviceStatus[SD_DEV_LCC_1 + nCurrentLoadCellNo] == DS_CONNECT) {

									// ������ ���� üũ
									if (bOnReceiveData[nCurrentLoadCellNo]) {
							
										bOnReceiveData[nCurrentLoadCellNo] = FALSE;
										LTimerTimeOut[nCurrentLoadCellNo].Start(m_SystemConfig.GetDelaySystem(DLY_SYS_TOUT_LOADCELL_DATA));

										// ��ũ ������ ����
										if (m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo] > m_stSystemStatus.dblPeakHoldDataLoadCell[nCurrentLoadCellNo])
											m_stSystemStatus.dblPeakHoldDataLoadCell[nCurrentLoadCellNo] = m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo];
									}

									// Ÿ�� �ƿ�
									if (LTimerTimeOut[nCurrentLoadCellNo].Verify()) {
							
										if (!m_SystemConfig.UseSystemOption(SOPT_DISABLE_ALARM_LOADCELL)) {

											PROCESS.bOnError				= TRUE;
											PROCESS.nRecoveryStep			= 0;
											PROCESS.stErrorCode.nErrorCode	= ERROR_TOUT_COMM;
											PROCESS.stErrorCode.nCommPort	= COMM_DEV_LCC_1 + nCurrentLoadCellNo;
											break;
										}
									}
								}
							}

							PROCESS.nCurrentStep++;
							break;

		case	201		:
							if (++nCurrentLoadCellNo >= MAX_LOADCELL_CHANNEL_USE)
								nCurrentLoadCellNo = LOADCELL_CH01;
							
							PROCESS.nCurrentStep = 200;

							break;


		/////////////////////////////////////////////////////////////
		// �Ͻ� ���� ���� ///////////////////////////////////////////
		case	STEP_PAUSE	:
								if (m_stSystemStatus.bOnEmergencyStop) {

									PROCESS.nCurrentStep = STEP_EMG;
									break;
								}

								PROCESS.nCurrentStep++;
								break;

		case	20001	:
							if (!m_stSystemStatus.bOnPause && !m_stSystemStatus.bOnAlarmSystem)	{

								PROCESS.nCurrentStep = 20100;
							}

							break;

		// ���� ����
		case	20100	:
							PROCESS.nCurrentStep	= PROCESS.nRecoveryStep;
							PROCESS.bOnPause		= FALSE;
							break;


		/////////////////////////////////////////////////////////////
		// ��� ���� ���� ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop)	{

									PROCESS.nRecoveryStep	= 0;
									PROCESS.nCurrentStep	= 20001;
								}

								break;
	}


	/////////////////////////////////////////////////////////////////
	// �ε弿 ������ ���� ///////////////////////////////////////////
	for (UINT nLoadCellNo = 0; nLoadCellNo < MAX_LOADCELL_CHANNEL_USE; nLoadCellNo++) {
	
		while (m_Comm[COMM_DEV_LCC_1 + nLoadCellNo].ReadByte(&byReadByte)) {

			// ������ ����
			szRcvdPacket[nLoadCellNo][nRcvdPacketIndex[nLoadCellNo]++] = byReadByte;

			// �ϳ��� ��Ŷ�� �ϼ��Ǹ� �ؼ�
			if (byReadByte == COMM_LF_F && szRcvdPacket[nLoadCellNo][nRcvdPacketIndex[nLoadCellNo] - 2] == COMM_CR_F) {
			
				USES_CONVERSION;

				szRcvdPacket[nLoadCellNo][nRcvdPacketIndex[nLoadCellNo] - 2] = '\0';
				m_stSystemStatus.nDeviceStatus[SD_DEV_LCC_1 + nLoadCellNo]   = DS_NORMAL;

				/////////////////////////////////////////////////////
				// ��Ʈ�� ��� //////////////////////////////////////
				if (m_SystemConfig.GetLoadCellType() == LOADCELL_TYPE_STREAM) {

					BOOL	bIsCorrectData	= TRUE;
					UINT	nCurrentStatus	= LCDT_STABLE;

					if (szRcvdPacket[nLoadCellNo][0] == 'S' && szRcvdPacket[nLoadCellNo][1] == 'T')			nCurrentStatus	= LCDT_STABLE;
					else if (szRcvdPacket[nLoadCellNo][0] == 'U' && szRcvdPacket[nLoadCellNo][1] == 'S')	nCurrentStatus	= LCDT_UNSTABLE;
					else if (szRcvdPacket[nLoadCellNo][0] == 'O' && szRcvdPacket[nLoadCellNo][1] == 'L')	nCurrentStatus	= LCDT_OVERFLOW;
					else if (szRcvdPacket[nLoadCellNo][0] == 'U' && szRcvdPacket[nLoadCellNo][1] == 'L')	nCurrentStatus	= LCDT_UNDERFLOW;
					else																					bIsCorrectData	= FALSE;

					if (bIsCorrectData) {
				
						m_stSystemStatus.dblMeasurementLoadCell[nLoadCellNo]	= atof(szRcvdPacket[nLoadCellNo] + 6) * m_SystemConfig.GetGainLoadCellData(nLoadCellNo);
						m_stSystemStatus.nStatusLoadCellData[nLoadCellNo]		= nCurrentStatus;
					}	

					// �÷��� ����
					bOnReceiveData[nLoadCellNo] = bIsCorrectData;

				/////////////////////////////////////////////////////
				// Ŀ�ǵ� ��� //////////////////////////////////////
				} else {
				
					UINT	nID		= m_SystemConfig.GetLoadCellID(nLoadCellNo);
					UINT	nReadID	= 0;
					CHAR	szTemp[10];

					// ID üũ
					strncpy_s(szTemp, 10, szRcvdPacket[nLoadCellNo] + 2, 3);
					nReadID = atoi(szTemp);
					if (nReadID == nID) {
					
						m_stSystemStatus.dblPeakHoldDataLoadCell[nLoadCellNo]	= atof(szRcvdPacket[nLoadCellNo] + 6) * m_SystemConfig.GetGainLoadCellData(nLoadCellNo);
						m_stSystemStatus.bOnReceivedLoadCellData[nLoadCellNo]	= TRUE;
					}
				}

				// ��Ŷ �ʱ�ȭ
				nRcvdPacketIndex[nLoadCellNo] = 0;
			}

			// ��Ŷ �����÷ο� ����
			if (nRcvdPacketIndex[nLoadCellNo] >= COMM_PACKET_SIZE) {

				nRcvdPacketIndex[nLoadCellNo] = 0;
				break;
			}
		}
	}


	/////////////////////////////////////////////////////////////////
	// �Ϲ� /////////////////////////////////////////////////////////
	CheckProcessGeneral(0, PROCESS);


	/////////////////////////////////////////////////////////////////
	// ���� ����͸� ////////////////////////////////////////////////
	if (LTimerSystemMonitor.Verify()) {

		if (PROCESS.nPrevStep != PROCESS.nCurrentStep) {

			PROCESS.nPrevStep = PROCESS.nCurrentStep;
			if (m_pSysMonitorDlg && m_pSysMonitorDlg->GetSafeHwnd()) {

				m_pSysMonitorDlg->PostMessage(UM_SYSM_UPDATE_STEP, PSTEP_PROC_DEVICE_2, PROCESS.nCurrentStep);
				LTimerSystemMonitor.Start(DLY_REFRESH_SYSTEM_MONITOR);
			}
		}
	}


	return	PROCESS.pstErrorCode;
}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� : �� ������ /////////////////////////////////////////////////////
PERROR_CODE_T CMainApp::ProcessLabelPrint(UINT nBCP_NO)
{	
	static	UINT					nCurrentStep[MAX_BARCODE_PRINTER];
	static	UINT					nReturnStep[MAX_BARCODE_PRINTER];
	static	UINT					nPreviousStep[MAX_BARCODE_PRINTER];
	static	UINT					nRecoveryStep[MAX_BARCODE_PRINTER];

	static	UINT					nRetryCount[MAX_BARCODE_PRINTER];
	static	UINT					nPrintRetryCount[MAX_BARCODE_PRINTER];

	static	BOOL					bOnPause[MAX_BARCODE_PRINTER];
	static	BOOL					bIsCheckStatus[MAX_BARCODE_PRINTER];

	static	CHAR					szStatusBuffer[MAX_BARCODE_PRINTER][BCP_STATUS_STRING1_LEN][BCP_STATUS_INFO_LEN];
	static	UINT					nStatusIndex[MAX_BARCODE_PRINTER];

	static	BYTE					byReadByte				= 0;
	static	CHAR					szRcvdPacket[MAX_BARCODE_PRINTER][COMM_PACKET_SIZE];
	static	UINT					nRcvdPacketIndex[MAX_BARCODE_PRINTER];
	static	BOOL					bOnRcvdPacket[MAX_BARCODE_PRINTER];
	static	CString					strPacket[MAX_BARCODE_PRINTER];
	static	CString					strMessageBox[MAX_BARCODE_PRINTER];

	static	LTimerMsec				LTimerProceed[MAX_BARCODE_PRINTER];
	static	LTimerMsec				LTimerTimeOut[MAX_BARCODE_PRINTER];
	static	LTimerMsec				LTimerTimeOutIssue[MAX_BARCODE_PRINTER];
	static	LTimerMsec				LTimerStandby[MAX_BARCODE_PRINTER];
	static	LTimerMsec				LTimerSteady[MAX_BARCODE_PRINTER];
	static	LTimerMsec				LTimerInterval[MAX_BARCODE_PRINTER];

	CComm*							pComm					= GetComm(COMM_PRINT_1 + nBCP_NO);

	BOOL							bOnError				= FALSE;
	PERROR_CODE_T					pstErrorCode			= NULL;
	ERROR_CODE_T					stErrorCode;


	/////////////////////////////////////////////////////////////////
	// ���ڵ� ������ ���� �ȵ� //////////////////////////////////////
	if (m_stSystemStatus.nDeviceStatus[SD_PRINT_1 + nBCP_NO] == DS_NONE || m_stSystemStatus.nDeviceStatus[SD_PRINT_1 + nBCP_NO] == DS_DISCONNECT)
		return	NULL;


	/////////////////////////////////////////////////////////////////
	// ���� �ʱ�ȭ //////////////////////////////////////////////////
	ZeroMemory(&stErrorCode, sizeof(ERROR_CODE_T));


	/////////////////////////////////////////////////////////////////
	// ���ڵ� ������ ���� ///////////////////////////////////////////
	if (m_stSystemStatus.bOnResetLabelPrinter[nBCP_NO]) {

		// ��Ŷ ����
		nRcvdPacketIndex[nBCP_NO]	= 0;
		//m_Comm[COMM_PRINT].TransmitString(FALSE, _T("{WR|}"));

		// ���� Ÿ�̸� ����
		LTimerStandby[nBCP_NO].Start(5000);

		m_stSystemStatus.bOnResetLabelPrinter[nBCP_NO] = FALSE;
		return	NULL;
	}


	/////////////////////////////////////////////////////////////////
	// ��� Ÿ�̸� üũ /////////////////////////////////////////////
	if (!LTimerStandby[nBCP_NO].Verify())	return	NULL;


	/////////////////////////////////////////////////////////////////
	// ���� ���μ��� ////////////////////////////////////////////////
	switch (nCurrentStep[nBCP_NO]) {

		/////////////////////////////////////////////////////////////
		// ��� ���� ////////////////////////////////////////////////
		case	0		:
							// �÷��� �ʱ�ȭ
							bIsCheckStatus[nBCP_NO]	= FALSE;

							nCurrentStep[nBCP_NO] = 10;
							break;
								
		case	10		:
							if (m_stSystemStatus.bOnPrintLabel[nBCP_NO]) {

								// �ʱ�ȭ
								nPrintRetryCount[nBCP_NO]	= 0;
								nRetryCount[nBCP_NO]		= 0;

								nCurrentStep[nBCP_NO] = 100;
								break;
							}

							// ���� üũ
							if (LTimerInterval[nBCP_NO].Verify()) {
							
								bIsCheckStatus[nBCP_NO]	= TRUE;
								nCurrentStep[nBCP_NO]	= 100;
							}

							break;


		/////////////////////////////////////////////////////////////
		// ���� üũ ////////////////////////////////////////////////

		// ���ڵ� ������ ���� üũ
		case	100		:
							if (LTimerSteady[nBCP_NO].Verify()) {

								// ������ ���� �ʱ�ȭ
								ZeroMemory(&m_stSystemStatus.stPrintStatus[nBCP_NO], sizeof(PRINT_STATUS_T));

								// ��Ŷ ����
								nRcvdPacketIndex[nBCP_NO]	= 0;
								bOnRcvdPacket[nBCP_NO]		= FALSE;
								pComm->ClearBuffer();
								pComm->TransmitString(FALSE, BCP_CMD_REQ_STATUS);
								LTimerTimeOut[nBCP_NO].Start(m_SystemConfig.GetDelaySystem(DLY_SYS_TOUT_COMM));

								nCurrentStep[nBCP_NO]++;
							}

							break;

		case	101		:
							if (m_stSystemStatus.stPrintStatus[nBCP_NO].bOnPrintStatus && bOnRcvdPacket[nBCP_NO]) {

								bOnRcvdPacket[nBCP_NO]	= FALSE;
								nRetryCount[nBCP_NO]	= 0;

								if (bIsCheckStatus[nBCP_NO]) {
								
									// ���� üũ ���� ����
									LTimerInterval[nBCP_NO].Start(m_SystemConfig.GetDelayControl(DLY_CTRL_INTV_READ_BCP_STATUS));

									nCurrentStep[nBCP_NO] = 0;
									break;
								}

								nCurrentStep[nBCP_NO]++;
								break;
							}

							// Ÿ�� �ƿ�
							if (LTimerTimeOut[nBCP_NO].Verify()) {

								if (++nRetryCount[nBCP_NO] > MAX_RETRY_COUNT) {

									bOnError				= TRUE;
									nRetryCount[nBCP_NO]	= 0;
									nRecoveryStep[nBCP_NO]	= bIsCheckStatus[nBCP_NO] ? 0 : 800;

									stErrorCode.nErrorCode	= ERROR_TOUT_COMM;
									stErrorCode.nCommPort	= COMM_PRINT_1 + nBCP_NO;
									break;
								}

								nCurrentStep[nBCP_NO]--;
							}

							break;

		// ���ڵ� ������ ���� üũ
		case	102		:
							{
								CString		strMsg			= _T("");
								BOOL		bOnErrorStatus	= FALSE;


								if (m_stSystemStatus.stPrintStatus[nBCP_NO].bIsPaperOut) {
									
									if (m_nTypeLanguage == LANGUAGE_KOR)	strMsg.Format(_T("������ �����ϴ�."));
									else									strMsg.Format(_T("PAPER OUT"));

									bOnErrorStatus = TRUE;

								} else if (m_stSystemStatus.stPrintStatus[nBCP_NO].bIsRibbonOut) {
									
									if (m_nTypeLanguage == LANGUAGE_KOR)	strMsg.Format(_T("���� ����"));
									else									strMsg.Format(_T("RIBBON OUT"));

									bOnErrorStatus = TRUE;

								} else if (m_stSystemStatus.stPrintStatus[nBCP_NO].bIsHeadUpPosition) {
									
									if (m_nTypeLanguage == LANGUAGE_KOR)	strMsg.Format(_T("��尡 �����ֽ��ϴ�."));
									else									strMsg.Format(_T("HEAD UP POSITION"));

									bOnErrorStatus = TRUE;

								} else if (m_stSystemStatus.stPrintStatus[nBCP_NO].bIsPauseActive) {
									
									if (m_nTypeLanguage == LANGUAGE_KOR)	strMsg.Format(_T("�Ͻ� ���� �����Դϴ�."));
									else									strMsg.Format(_T("PAUSE ACTIVE"));

									bOnErrorStatus = TRUE;
								
								} else if (m_stSystemStatus.stPrintStatus[nBCP_NO].bIsLabelWaiting) {
									
									if (m_nTypeLanguage == LANGUAGE_KOR)	strMsg.Format(_T("���� �̹� ����Ǿ� �ֽ��ϴ�."));
									else									strMsg.Format(_T("LABEL IS ALREADY ISSUED"));

									bOnErrorStatus = TRUE;
								}

								if (bOnErrorStatus) {

									// �޼��� ���
									ErrorMessage(TRUE, _T("[LABEL PRINTER #%d ERROR] %s"), nBCP_NO + 1, strMsg);

									// �޼��� �ڽ� ����
									strMessageBox[nBCP_NO] = strMsg;

									nCurrentStep[nBCP_NO] = STEP_ERROR;
									break;
								}

								nCurrentStep[nBCP_NO] = 200;
							}

							break;


		/////////////////////////////////////////////////////////////
		// ���ڵ� ��� //////////////////////////////////////////////

		// ���ڵ� ������ ���� �� ���
		case	200		:
							if (!m_strLabelFormat[nBCP_NO].IsEmpty()) {

								// ��Ŷ ����
								nRcvdPacketIndex[nBCP_NO]	= 0;
								nRetryCount[nBCP_NO]		= 0;
								pComm->ClearBuffer();
								pComm->TransmitString(FALSE, m_strLabelFormat[nBCP_NO]);

								// �߱� ���� �ð� ����
								LTimerSteady[nBCP_NO].Start(m_SystemConfig.GetDelayControl(DLY_CTRL_WAIT_LABEL_ISSUE));

								// �߱� Ÿ�� �ƿ�
								LTimerTimeOutIssue[nBCP_NO].Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_LABEL_ISSUE));

								nCurrentStep[nBCP_NO]++;
								break;								
							}

							nCurrentStep[nBCP_NO] = 800;
							break;

		case	201		:
							if (LTimerSteady[nBCP_NO].Verify())
								nCurrentStep[nBCP_NO] = 210;

							break;

		// ���� ���� �� üũ
		case	210		:
							// ������ ���� �ʱ�ȭ
							ZeroMemory(&m_stSystemStatus.stPrintStatus[nBCP_NO], sizeof(PRINT_STATUS_T));
							nPrintRetryCount[nBCP_NO] = 0;

							// ��Ŷ ����
							nRcvdPacketIndex[nBCP_NO]	= 0;
							bOnRcvdPacket[nBCP_NO]		= FALSE;
							pComm->ClearBuffer();
							pComm->TransmitString(FALSE, BCP_CMD_REQ_STATUS);
							LTimerTimeOut[nBCP_NO].Start(m_SystemConfig.GetDelaySystem(DLY_SYS_TOUT_COMM) * 4);

							nCurrentStep[nBCP_NO]++;
							break;

		case	211		:
							if (m_stSystemStatus.stPrintStatus[nBCP_NO].bOnPrintStatus && bOnRcvdPacket[nBCP_NO]) {

								bOnRcvdPacket[nBCP_NO]	= FALSE;
								nRetryCount[nBCP_NO]	= 0;
								nCurrentStep[nBCP_NO]	= 210;

								// ������ ���� üũ
								if (!m_stSystemStatus.stPrintStatus[nBCP_NO].bIsPaperOut && !m_stSystemStatus.stPrintStatus[nBCP_NO].bIsRibbonOut &&
									!m_stSystemStatus.stPrintStatus[nBCP_NO].bIsHeadUpPosition && !m_stSystemStatus.stPrintStatus[nBCP_NO].bIsPauseActive) {

										m_stSystemStatus.bOnPrintLabelResult[nBCP_NO] = TRUE;

										nCurrentStep[nBCP_NO] = 900;
										break;
								}

								// �߱� Ÿ�� �ƿ�
								if (LTimerTimeOutIssue[nBCP_NO].Verify()) {

									if (m_nTypeLanguage == LANGUAGE_KOR)	ErrorMessage(TRUE, _T("[�� ������ #%d ����] �� ����� �Ϸ��� �� �����ϴ�."), nBCP_NO + 1);
									else 									ErrorMessage(TRUE, _T("[LABEL PRINTER #%d ERROR] LABEL ISSUE FAILURE"), nBCP_NO + 1);

									nCurrentStep[nBCP_NO] = 800;
								}

								break;
							}

							// Ÿ�� �ƿ�
							if (LTimerTimeOut[nBCP_NO].Verify()) {

								if (++nRetryCount[nBCP_NO] > MAX_RETRY_COUNT) {

									bOnError				= TRUE;
									nRetryCount[nBCP_NO]	= 0;
									nRecoveryStep[nBCP_NO]	= 800;

									stErrorCode.nErrorCode	= ERROR_TOUT_COMM;
									stErrorCode.nCommPort	= COMM_PRINT_1 + nBCP_NO;
									break;
								}

								nCurrentStep[nBCP_NO]--;
							}

							break;


		/////////////////////////////////////////////////////////////
		// ���� /////////////////////////////////////////////////////
		case	800		:
							// ������ ����
							m_stSystemStatus.bOnResetLabelPrinter[nBCP_NO]	= TRUE;
							
							// �� ��� ��� ����
							m_stSystemStatus.bOnPrintLabelResult[nBCP_NO]	= FALSE;

							// ������ 2ȸ ���
							m_stSystemStatus.nBeepCount = 2;

							bOnRcvdPacket[nBCP_NO]	= FALSE;
							nRetryCount[nBCP_NO]	= 0;
							nCurrentStep[nBCP_NO]	= 900;
							break;


		/////////////////////////////////////////////////////////
		// ��� �Ϸ� ////////////////////////////////////////////
		case	900		:
							m_stSystemStatus.bOnPrintLabel[nBCP_NO]	= FALSE;
							nCurrentStep[nBCP_NO] = 0;
							break;


		/////////////////////////////////////////////////////////////
		// ���� �޼��� //////////////////////////////////////////////
		case	STEP_ERROR	:
								nCurrentStep[nBCP_NO] = 90010;
								break;

		case	90010	:
							nCurrentStep[nBCP_NO] = 90020;
							break;

		// �޼��� �ڽ� ���
		case	90020	:
							// �޼��� �ڽ��� ��� ���� üũ
							if (!m_stSystemStatus.bIsDisplayMessageBox) {
							
								m_stSystemStatus.bIsDisplayMessageBox = TRUE;

								nCurrentStep[nBCP_NO]++;
							}

							break;

		case	90021	:
							{
								// �ý��� �÷��� ����
								m_stSystemStatus.nMessageBoxButtonCode	= MBOX_BCODE_NONE;	// ��ư �ڵ� �ʱ�ȭ
								m_stSystemStatus.bOnBuzzer				= TRUE;				// ����� ���
								m_stSystemStatus.bOnWaitForUser			= TRUE;				// ����� �Է� ��� ����

								// �޼��� �ڽ� ����
								PMBOX_PARAM_T	pstMBoxParam = new MBOX_PARAM_T;
								if (pstMBoxParam) {

									ZeroMemory(pstMBoxParam, sizeof(MBOX_PARAM_T));
									_stprintf_s(pstMBoxParam->szButtonTitle[MBOX_BUTTON_0], MAX_STRINPUT, _T("%s\n(ENTER)"), g_stSystemString[SYSSTR_BTN_RETRY].szDescription[m_nTypeLanguage]);
									_stprintf_s(pstMBoxParam->szButtonTitle[MBOX_BUTTON_1], MAX_STRINPUT, _T("%s\n(ESC)"), g_stSystemString[SYSSTR_BTN_BUZZER_OFF].szDescription[m_nTypeLanguage]);
									_stprintf_s(pstMBoxParam->szMessage, MAX_STRVALUE, _T("\n%s"), strMessageBox[nBCP_NO]);

									pstMBoxParam->bEnableButton[MBOX_BUTTON_0]	= TRUE;
									pstMBoxParam->bEnableButton[MBOX_BUTTON_1]	= TRUE;
									pstMBoxParam->nTypeButton[MBOX_BUTTON_0]	= MBOX_BTYPE_CLOSE;
									pstMBoxParam->nTypeButton[MBOX_BUTTON_1]	= MBOX_BTYPE_NORMAL;
									pstMBoxParam->bEnableShortCutKey			= TRUE;
									pstMBoxParam->nKeyShortCut[MBOX_BUTTON_0]	= VK_RETURN;
									pstMBoxParam->nKeyShortCut[MBOX_BUTTON_1]	= VK_ESCAPE;
									pstMBoxParam->nMessageFontSize				= 26;
									pstMBoxParam->bEnableSetWindowPos			= TRUE;
									pstMBoxParam->ptWindowPosition				= m_SystemConfig.GetMBoxWindowPosition();
									m_pMessageBoxDlg->SendMessage(UM_DPS_DLG_MESSAGE_BOX_SHOWHIDE, SW_SHOW, (LPARAM)pstMBoxParam);

									nCurrentStep[nBCP_NO]++;
									break;
								}

								// ������ 2ȸ ���
								m_stSystemStatus.nBeepCount = 2;

								SErrorMessage(TRUE, _T("[BCP] �޼��� �ڽ��� ������ �� �����ϴ�."));
							}

							nCurrentStep[nBCP_NO] = 90090;
							break;

		case	90022	:
							if (m_stSystemStatus.nMessageBoxButtonCode != MBOX_BCODE_NONE) {
							
								// ��ư 0 : ��õ�
								if (m_stSystemStatus.nMessageBoxButtonCode == MBOX_BCODE_0) {

									nCurrentStep[nBCP_NO] = 90090;
									break;
								}

								// ��ư 1 : ����� ����
								if (m_stSystemStatus.nMessageBoxButtonCode == MBOX_BCODE_1) {

									m_stSystemStatus.bOnBuzzer				= FALSE;			// ����� ����
									m_stSystemStatus.nMessageBoxButtonCode	= MBOX_BCODE_NONE;	// ��ư �ڵ� �ʱ�ȭ
								}
							}

							// �޼��� �ڽ��� ����� ���
							if (!m_stSystemStatus.bIsDisplayMessageBox)
								nCurrentStep[nBCP_NO] = 90090;

							break;

		// �Ϸ�
		case	90090	:
							// �޼��� �ڽ� ��� �÷��� ����
							m_stSystemStatus.bIsDisplayMessageBox = FALSE;

							// �޼��� �ڽ� ���߱�	
							m_pMessageBoxDlg->SendMessage(UM_DPS_DLG_MESSAGE_BOX_SHOWHIDE, SW_HIDE, NULL);

							// �ý��� �÷��� ����
							m_stSystemStatus.bOnWaitForUser	= FALSE;	// ����� �Է� ��� ����
							m_stSystemStatus.bOnBuzzer		= FALSE;	// ����� ����

							nCurrentStep[nBCP_NO] = 0;
							break;
	}


	/////////////////////////////////////////////////////////////////
	// ������ ���� ���� üũ ////////////////////////////////////////
	while (pComm->ReadByte(&byReadByte)) {

		// STX üũ
		if (byReadByte == COMM_STD_STX_F)
			nRcvdPacketIndex[nBCP_NO] = 0;

		// ������ ����
		szRcvdPacket[nBCP_NO][nRcvdPacketIndex[nBCP_NO]++] = byReadByte;

		// �ϳ��� ��Ŷ�� �ϼ��Ǹ� �ؼ�
		if (byReadByte == 0x0A && szRcvdPacket[nBCP_NO][nRcvdPacketIndex[nBCP_NO] - 2] == 0x0D) {

			USES_CONVERSION;

			// ���ڿ� ��ȯ
			szRcvdPacket[nBCP_NO][0] = 0x20;
			szRcvdPacket[nBCP_NO][nRcvdPacketIndex[nBCP_NO] - 2] = '\0';

			// ��ġ ���� üũ
			m_stSystemStatus.nDeviceStatus[SD_PRINT_1 + nBCP_NO] = DS_NORMAL;

			// ����Ʈ ���� ���� ���� �ʱ�ȭ
			nStatusIndex[nBCP_NO] = 0;
			ZeroMemory(szStatusBuffer[nBCP_NO], BCP_STATUS_STRING1_LEN * BCP_STATUS_INFO_LEN);

			// ��ū �и�
			BOOL	bResult		= TRUE;
			UINT	nTokenLen	= 0;
			LPSTR	lpszType	= NULL;
			LPSTR	lpszToken	= (LPSTR)strtok_s(szRcvdPacket[nBCP_NO] + 1, ",", &lpszType);
			if (lpszToken != NULL) {

				do {

					nTokenLen = strlen(lpszToken);
					if (nTokenLen >= BCP_STATUS_INFO_LEN || nStatusIndex[nBCP_NO] > BCP_STATUS_STRING1_LEN) {

						SErrorMessage(TRUE, _T("[BCP] LABEL PRINTER PACKET DATA ERROR! [%s]"), lpszToken);
						SErrorMessage(TRUE, _T("[BCP] RECEIVED DATA [%s]"), szRcvdPacket[nBCP_NO]);
					
						bResult = FALSE;
						break;
					}

					strncpy_s(szStatusBuffer[nBCP_NO][nStatusIndex[nBCP_NO]++], BCP_STATUS_INFO_LEN, lpszToken, nTokenLen);
				
				} while ((lpszToken = (LPSTR)strtok_s(NULL, ",", &lpszType)) != NULL);

				if (bResult) {

					switch (nStatusIndex[nBCP_NO]) {

						case	BCP_STATUS_STRING1_LEN	:
															m_stSystemStatus.stPrintStatus[nBCP_NO].bIsPaperOut			= (BOOL)atoi(szStatusBuffer[nBCP_NO][1]);
															m_stSystemStatus.stPrintStatus[nBCP_NO].bIsPauseActive		= (BOOL)atoi(szStatusBuffer[nBCP_NO][2]);
															break;

						case	BCP_STATUS_STRING2_LEN	:
															m_stSystemStatus.stPrintStatus[nBCP_NO].bIsHeadUpPosition	= (BOOL)atoi(szStatusBuffer[nBCP_NO][2]);
															m_stSystemStatus.stPrintStatus[nBCP_NO].bIsRibbonOut		= (BOOL)atoi(szStatusBuffer[nBCP_NO][3]);
															m_stSystemStatus.stPrintStatus[nBCP_NO].bIsLabelWaiting		= (BOOL)atoi(szStatusBuffer[nBCP_NO][7]);
															break;

						case	BCP_STATUS_STRING3_LEN	:
															m_stSystemStatus.stPrintStatus[nBCP_NO].bOnPrintStatus		= TRUE;
															break;
					}
				}
			}

			// ��Ŷ ���� �÷��� ����
			bOnRcvdPacket[nBCP_NO] = bResult;

			// ��Ŷ �ʱ�ȭ
			nRcvdPacketIndex[nBCP_NO] = 0;
		}

		// ��Ŷ �����÷ο� ����
		if (nRcvdPacketIndex[nBCP_NO] >= COMM_PACKET_SIZE) {
			
			nRcvdPacketIndex[nBCP_NO] = 0;
			break;
		}
	}


	/////////////////////////////////////////////////////////////////
	// ���� �߻� ////////////////////////////////////////////////////
	if (bOnError) {

		pstErrorCode = new ERROR_CODE_T;
		if (pstErrorCode)	*pstErrorCode = stErrorCode;

		// ���� ���̸�,
		if (m_stSystemStatus.bOnOperating) {

			// ���� ����
			nCurrentStep[nBCP_NO] = nRecoveryStep[nBCP_NO];
		
		} else {

			m_stSystemStatus.bOnPrintLabel[nBCP_NO] = FALSE;
			nCurrentStep[nBCP_NO] = 0;
		}
	}


	return	pstErrorCode;
}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� : ���ڵ� ��ĵ /////////////////////////////////////////////////////
void CMainApp::ProcessBarcodeScan(void)
{
	USES_CONVERSION;

	static	CHAR		szRcvdPacket[MAX_BCD_SCAN][COMM_PACKET_SIZE];
	static	UINT		nRcvdPacketIndex[MAX_BCD_SCAN];
	static	UINT		nCurrentScanIndex	= 0;
	static	BYTE		byRcvdPacket		= 0;

	BOOL				bOnUpdateUI			= FALSE;
	UI_PARAM_UPDATE_T	stParamUI;


	/////////////////////////////////////////////////////////////////
	ZeroMemory(&stParamUI, sizeof(UI_PARAM_UPDATE_T));


	/////////////////////////////////////////////////////////////////
	// ���ڵ� ������ ���� ///////////////////////////////////////////
	while (m_Comm[COMM_SCAN_1 + nCurrentScanIndex].ReadByte(&byRcvdPacket)) {

		// ������ ����
		szRcvdPacket[nCurrentScanIndex][nRcvdPacketIndex[nCurrentScanIndex]++]	= byRcvdPacket;

		// �ϳ��� ��Ŷ�� �ϼ��Ǹ� �ؼ�
		if (byRcvdPacket == 0x0D/* || byRcvdPacket == 0x0A*/) {

			// ���ڵ� ����
			szRcvdPacket[nCurrentScanIndex][nRcvdPacketIndex[nCurrentScanIndex] - 1] = '\0';
			CString	strReadCode(szRcvdPacket[nCurrentScanIndex]);
			//strReadCode.Remove(0x20);
			strReadCode.Remove(0x0D);
			strReadCode.Remove(0x0A);
			strReadCode = strReadCode.TrimLeft();
			strReadCode = strReadCode.TrimRight();
					
			// ���ڵ� ����
			if (strReadCode.GetLength() < MAX_STRINPUT_S) {
			
				SetBarcodeInfo(nCurrentScanIndex, strReadCode);
				MessageWindow(cDEBUG, _T("[%d] Barcode Scanned! [%s]"), nCurrentScanIndex, GetBarcodeInfo(nCurrentScanIndex));
				NormalMessage(TRUE, _T("BARCODE SCAN [%02d] = %s"), nCurrentScanIndex, GetBarcodeInfo(nCurrentScanIndex));

				// �ڵ� ���� ���̸�,
				if (m_stSystemStatus.bOnOperating && (nCurrentScanIndex == BCS_INPUT_1 || nCurrentScanIndex == BCS_INPUT_2)) {

					bOnUpdateUI				= TRUE;
					stParamUI.nUpdateID		= UI_PRODUCT_CODE_IN;
					stParamUI.nStationNo	= STATION_1;
					stParamUI.stProductCodeInfo.nStatusCodeInput	= BCD_SCAN_INPUT;
					_tcscpy_s(stParamUI.stProductCodeInfo.szCodeInput, MAX_STRINPUT_L, strReadCode);
				}
			}

			// ��Ŷ �ʱ�ȭ
			nRcvdPacketIndex[nCurrentScanIndex]	= 0;
		}

		// ��Ŷ �����÷ο� ����
		if (nRcvdPacketIndex[nCurrentScanIndex] >= COMM_PACKET_SIZE) {

			nRcvdPacketIndex[nCurrentScanIndex] = 0;
			break;
		}
	}

	if (++nCurrentScanIndex >= MAX_BCD_SCAN)	
		nCurrentScanIndex = 0;


	/////////////////////////////////////////////////////////////////
	// ������Ʈ UI //////////////////////////////////////////////////
	if (bOnUpdateUI) {

		PUI_PARAM_UPDATE_T	pstParamUI	= new (std::nothrow) UI_PARAM_UPDATE_T;
		if (pstParamUI) {

			*pstParamUI = stParamUI;

			if (m_pMainWnd && m_pMainWnd->GetSafeHwnd())
				m_pMainWnd->PostMessage(UM_MAIN_UPDATE_UI, (WPARAM)pstParamUI);
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� : CAN ��� ////////////////////////////////////////////////////////
void CMainApp::ProcessDeviceCAN(void)
{
	static	PCAN_PACKET_T			stPacket;
	static	LTimerHiresMsec			LTimerInterval[MAX_CAN_MESSAGE];
	

	/////////////////////////////////////////////////////////////////
	// CAN �޼��� ���� //////////////////////////////////////////////
	for (UINT nIndex = CID_BMS22; nIndex < MAX_CAN_MESSAGE; nIndex++) {
	
		if (m_stSystemStatus.bCAN_EnableTransmitData[nIndex] && LTimerInterval[nIndex].Verify()) {
		
			/////////////////////////////////////////////////////////
			// ��Ŷ ���� ////////////////////////////////////////////
			stPacket.stMessage.ID		= m_stCAN_TransmitData[nIndex].nCAN_ID;
			stPacket.stMessage.DLC		= m_stCAN_TransmitData[nIndex].nLength;
			stPacket.stMessage.MSGTYPE	= PCAN_MESSAGE_STANDARD;
			for (UINT nDataNo = 0; nDataNo < MAX_CAN_MSG_BYTE; nDataNo++)
				stPacket.stMessage.DATA[nDataNo] = m_stCAN_TransmitData[nIndex].abData[nDataNo];


			/////////////////////////////////////////////////////////
			// ��Ŷ ���� ////////////////////////////////////////////
			m_devCAN.SendPacket(stPacket);


			/////////////////////////////////////////////////////////
			// Ÿ�̸� ���� //////////////////////////////////////////
			LTimerInterval[nIndex].Start(m_stSystemStatus.nCAN_TransmitTimeInterval[nIndex]);
		}
	}
}







///////////////////////////////////////////////////////////////////////////////////////////////////
// �۾� ���μ��� üũ /////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ���� ���μ��� ������ �ʱ�ȭ ////////////////////////////////////////////////
void CMainApp::StationProcessDataInitialize(UINT nSTATION_NO, UINT nSTATION_SUB_NO, PROCESS_CTRL_T& PROCESS)
{
	/////////////////////////////////////////////////////////////////
	// �ý��� �÷��� �ʱ�ȭ /////////////////////////////////////////
	m_stSystemStatus.bOnAlarmStation[nSTATION_NO]	= FALSE;
	m_stSystemStatus.bOnMP_Error[nSTATION_NO]		= FALSE;


	/////////////////////////////////////////////////////////////////
	// ���� �÷��� �ʱ�ȭ ///////////////////////////////////////////
	m_stSystemStatus.bOnStationInitializeResult[nSTATION_NO][nSTATION_SUB_NO]	= TRUE;
	m_stSystemStatus.bOnStationProcessConveyor[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;
	m_stSystemStatus.bOnStationProcessStandby[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;
	m_stSystemStatus.bOnStationProcessRequest[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;
	m_stSystemStatus.bOnStationProcessOutput[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;
	m_stSystemStatus.bOnStationProcessComplete[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;
	m_stSystemStatus.bIsStationProcessLock[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;
	m_stSystemStatus.nStationProcessOption[nSTATION_NO][nSTATION_SUB_NO]		= STN_PROC_OPT_NONE;


	/////////////////////////////////////////////////////////////////
	// �۾� �÷��� �ʱ�ȭ ///////////////////////////////////////////
	m_stSystemStatus.bOnUserWarning[nSTATION_NO]		= FALSE;
	m_stSystemStatus.bOnUserSafety[nSTATION_NO]			= FALSE;
	m_stSystemStatus.bOnUserBuzzer[nSTATION_NO]			= FALSE;
	m_stSystemStatus.bOnUserLamp1[nSTATION_NO]			= FALSE;
	m_stSystemStatus.bOnUserLamp2[nSTATION_NO]			= FALSE;
	m_stSystemStatus.nCurrentWorkMessage[nSTATION_NO]	= WMSG_NONE;


	/////////////////////////////////////////////////////////////////
	// ���μ��� ������ �ʱ�ȭ ///////////////////////////////////////
	PROCESS.nSubProcess01Step		= 0;
	PROCESS.nSubProcess02Step		= 0;
	PROCESS.nSubProcess03Step		= 0;
	PROCESS.nSubProcess04Step		= 0;
	PROCESS.nSubProcess05Step		= 0;
	PROCESS.nRecoveryStep			= 0;
	PROCESS.nRecoveryStopStep		= 0;

	PROCESS.bOnPause				= FALSE;
	PROCESS.bOnInterLock			= FALSE;
	PROCESS.bOnDoorOpened			= FALSE;
	PROCESS.bOnProcessCycle			= FALSE;
	PROCESS.bOnMachineInitialize	= FALSE;

	PROCESS.bOnTactTimeStart		= FALSE;
	PROCESS.bIsTactTimeComplete		= FALSE;

	PROCESS.bOnLoadedProduct		= FALSE;
	PROCESS.bOnPickupProduct		= FALSE;
	PROCESS.bOnLoadedPallet			= FALSE;
	PROCESS.bIsReversedPallet		= FALSE;
	PROCESS.bIsLoadingPallet		= FALSE;
}


///////////////////////////////////////////////////////////////////////////////
// ���μ��� ������ �ʱ�ȭ /////////////////////////////////////////////////////
void CMainApp::ProcessDataInitialize(PROCESS_CTRL_T& PROCESS)
{
	PROCESS.bOnError				= FALSE;
	PROCESS.bOnUpdateUI				= FALSE;
	PROCESS.bIsUpdateSendMessage	= FALSE;
	
	PROCESS.pstErrorCode			= NULL;
	PROCESS.pstMBoxParam			= NULL;

	ZeroMemory(&PROCESS.stErrorCode, sizeof(ERROR_CODE_T));
	ZeroMemory(&PROCESS.stParamUI, sizeof(UI_PARAM_UPDATE_T));
}


///////////////////////////////////////////////////////////////////////////////
// �Ϲ� ///////////////////////////////////////////////////////////////////////
BOOL CMainApp::CheckProcessGeneral(UINT nSTATION_NO, PROCESS_CTRL_T& PROCESS)
{
	BOOL	bResult	= FALSE;


	/////////////////////////////////////////////////////////////////
	// ������Ʈ UI //////////////////////////////////////////////////
	if (PROCESS.bOnUpdateUI) {

		PUI_PARAM_UPDATE_T	pstParamUI = new UI_PARAM_UPDATE_T;
		if (pstParamUI) {

			*pstParamUI = PROCESS.stParamUI;

			if (m_pMainWnd && m_pMainWnd->GetSafeHwnd()) {

				if (PROCESS.bIsUpdateSendMessage)	m_pMainWnd->SendMessage(UM_MAIN_UPDATE_UI, (WPARAM)pstParamUI);
				else								m_pMainWnd->PostMessage(UM_MAIN_UPDATE_UI, (WPARAM)pstParamUI);
			}
		}

		bResult = TRUE;
	}


	/////////////////////////////////////////////////////////////////
	// ���� �߻� ////////////////////////////////////////////////////
	if (PROCESS.bOnError) {

		PROCESS.pstErrorCode = new ERROR_CODE_T;
		if (PROCESS.pstErrorCode)	*(PROCESS.pstErrorCode) = PROCESS.stErrorCode;

		// �ý��� �˶� ����
		m_stSystemStatus.bOnAlarmSystem = PROCESS.stErrorCode.bOnAlarmSystem;

		// ���� ����
		PROCESS.nCurrentStep = PROCESS.nRecoveryStep;

		// �ý��� �˶��� ��� �Ͻ� ����
		if (m_stSystemStatus.bOnAlarmSystem) {
		
			if (m_stSystemStatus.bOnOperating) {

				m_stSystemStatus.bOnPause = TRUE;

				if (m_pMainWnd && m_pMainWnd->GetSafeHwnd())
					m_pMainWnd->SendMessage(UM_MAIN_PAUSE);
			}
		
		} else {
		
			// ���� �˶� ����
			m_stSystemStatus.bOnAlarmStation[nSTATION_NO] = TRUE;
		}

		bResult = TRUE;
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// �ڵ� ���� üũ /////////////////////////////////////////////////////////////
BOOL CMainApp::CheckProcessOperating(PROCESS_CTRL_T& PROCESS)
{
	BOOL	bResult	= FALSE;


	if ((!m_stSystemStatus.bOnOperating && !PROCESS.bIsOperatingStop) ||
		(m_stSystemStatus.bOnOperating && PROCESS.bIsOperatingStop)) {

			PROCESS.nCurrentStep			= 0;
			PROCESS.nSubProcess01Step		= 0;
			PROCESS.nSubProcess02Step		= 0;
			PROCESS.nSubProcess03Step		= 0;
			PROCESS.nSubProcess04Step		= 0;
			PROCESS.nSubProcess05Step		= 0;
			PROCESS.nRecoveryStep			= 0;
			PROCESS.nRecoveryStopStep		= 0;

			PROCESS.bOnPause				= FALSE;
			PROCESS.bOnInterLock			= FALSE;
			PROCESS.bOnDoorOpened			= FALSE;
			PROCESS.bOnProcessCycle			= FALSE;
			PROCESS.bOnMachineInitialize	= FALSE;

			PROCESS.bOnOperatingStop		= FALSE;
			PROCESS.bIsStopReservated		= FALSE;
			PROCESS.bIsManualControlMode	= FALSE;

			PROCESS.bOnTactTimeStart		= FALSE;
			PROCESS.bIsTactTimeComplete		= FALSE;

			PROCESS.bOnLoadedProduct		= FALSE;
			PROCESS.bOnPickupProduct		= FALSE;
			PROCESS.bOnLoadedPallet			= FALSE;
			PROCESS.bIsReversedPallet		= FALSE;
			PROCESS.bIsLoadingPallet		= FALSE;

			PROCESS.pstModelProfile			= NULL;
			PROCESS.pstModelProfileConfig	= NULL;
			PROCESS.pstWorkInfo				= NULL;
			PROCESS.pstTestSetupInfo		= NULL;
			PROCESS.pstWorkPositionInfo		= NULL;
			PROCESS.pstStationSetupInfo		= NULL;
			PROCESS.pstStationProcessInfo	= NULL;
			PROCESS.pstMiscellaneousInfo	= NULL;

			bResult = TRUE;
	}

	PROCESS.bIsOperatingStop = !m_stSystemStatus.bOnOperating;


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// �Ͻ� ���� üũ /////////////////////////////////////////////////////////////
BOOL CMainApp::CheckProcessOperatingPause(UINT nSTATION_NO, PROCESS_CTRL_T& PROCESS)
{
	BOOL	bResult	= FALSE;


	/////////////////////////////////////////////////////////////////
	// ���� ����� ��� /////////////////////////////////////////////
	if (m_stSystemStatus.bIsManualControl[nSTATION_NO])
		return	bResult;


	/////////////////////////////////////////////////////////////////
	// �Ͻ� ���� üũ ///////////////////////////////////////////////
	if ((m_stSystemStatus.bOnPause || m_stSystemStatus.bOnAlarmStation[nSTATION_NO] || m_stSystemStatus.bOnAlarmSystem) && !PROCESS.bOnPause) {

		if (!PROCESS.bOnProcessCycle || m_stSystemStatus.bOnAlarmSystem) {

			PROCESS.nRecoveryStep				= PROCESS.nCurrentStep;
			PROCESS.nCurrentStep				= STEP_PAUSE;

			PROCESS.bOnPause					= TRUE;
			PROCESS.bOnMachineInitialize		= FALSE;

			PROCESS.stStationWorkInfo.nStatus	= (m_stSystemStatus.bOnAlarmStation[nSTATION_NO] || m_stSystemStatus.bOnAlarmSystem) ? STN_WORK_STATUS_ALARM : STN_WORK_STATUS_PAUSE;
		
			bResult = TRUE;
		}
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// ���� ���� üũ /////////////////////////////////////////////////////////////
BOOL CMainApp::CheckProcessOperatingStop(PROCESS_CTRL_T& PROCESS)
{
	BOOL	bResult	= FALSE;


	if (PROCESS.bOnOperatingStop) {

		PROCESS.bOnOperatingStop = FALSE;
		if (m_pMainWnd && m_pMainWnd->GetSafeHwnd())
			m_pMainWnd->PostMessage(UM_MAIN_STOP);

		bResult = TRUE;
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// ���� ���� üũ /////////////////////////////////////////////////////////////
BOOL CMainApp::CheckProcessOperatingStopReservated(UINT nSTATION_NO, UINT nSTATION_SUB_NO, PROCESS_CTRL_T& PROCESS)
{
	BOOL	bResult	= FALSE;


	if (m_stSystemStatus.bOnOperatingStopReservated && !PROCESS.bIsStopReservated) {
	
		if (!m_stSystemStatus.bIsStationProcessLock[nSTATION_NO][nSTATION_SUB_NO] && !PROCESS.bOnProcessCycle) {
		
			PROCESS.bIsStopReservated	= TRUE;
			PROCESS.nRecoveryStopStep	= PROCESS.nCurrentStep;
			PROCESS.nCurrentStep		= STEP_STN_WAIT_STOP;

			bResult = TRUE;
		}
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// ���� ��� üũ /////////////////////////////////////////////////////////////
BOOL CMainApp::CheckProcessManualControlMode(UINT nSTATION_NO, PROCESS_CTRL_T& PROCESS)
{
	BOOL	bResult	= FALSE;


	PROCESS.bOnManualControlMode  = FALSE;
	PROCESS.bOnManualControlMode |= m_stSystemStatus.bOnManualControl[nSTATION_NO];
	PROCESS.bOnManualControlMode |= m_stSystemStatus.bOnManualControlDIO;

	if (m_stSystemStatus.bOnOperating && nSTATION_NO >= STATION_1) {
	
		if (PROCESS.bOnManualControlMode && !PROCESS.bIsManualControlMode) {

			if ((!PROCESS.bOnProcessCycle && !m_stSystemStatus.bIsStationProcessLock[nSTATION_NO][0]) || m_stSystemStatus.bOnAlarmStation[nSTATION_NO]) {
		
				PROCESS.bIsManualControlMode = TRUE;
				PROCESS.nCurrentStep		 = 0;

				bResult = TRUE;
			}
		}
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// ��� �ʱ�ȭ üũ ///////////////////////////////////////////////////////////
BOOL CMainApp::CheckProcessMachineInitialize(PROCESS_CTRL_T& PROCESS)
{
	BOOL	bResult	= FALSE;


	if (m_stSystemStatus.bOnMachineInitialize && !PROCESS.bOnMachineInitialize) {

		PROCESS.bOnMachineInitialize	= TRUE;
		PROCESS.nRecoveryStep			= 0;
		PROCESS.nCurrentStep			= STEP_MC_INIT;

		bResult	= TRUE;
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// ��� ���� üũ /////////////////////////////////////////////////////////////
BOOL CMainApp::CheckProcessEmergencyStop(PROCESS_CTRL_T& PROCESS)
{
	BOOL	bResult	= FALSE;


	if (m_stSystemStatus.bOnEmergencyStop && !PROCESS.bOnPause) {

		PROCESS.nRecoveryStep			= PROCESS.nCurrentStep;
		PROCESS.nCurrentStep			= STEP_PAUSE;

		PROCESS.bOnPause				= TRUE;
		PROCESS.bOnMachineInitialize	= FALSE;
		
		bResult = TRUE;
	}


	return	bResult;
}








///////////////////////////////////////////////////////////////////////////////////////////////////
// ������ : ���� //////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
UINT CMainApp::ThreadFuncMain(LPVOID lpParam)
{
	CMainApp*			pMainApp			= (CMainApp*)lpParam;
	CDpsSystemConfig*	pSystemConfig		= pMainApp->GetSystemConfig();
	PSYSTEM_STATUS_T	pstSystemStatus		= pMainApp->GetSystemStatus();
	PERROR_CODE_T		pstErrorCode		= NULL;

	UINT				nThreadCount		= THREAD_COUNT_MAIN;
	UINT				nCurrentStep		= 100;
	UINT				nPreviousStep		= 0;

	UINT				nTypeLanguage		= pSystemConfig->GetTypeLanguage();
	UINT				nTypeMachine		= pSystemConfig->GetTypeMachine();
	UINT				nCurrentAxisNo		= MOTION_AXIS_1;

	CString				strValue			= _T("");

	LTimerMsec			LTimerThread;
	LTimerMsec			LTimerCheckRework;
	LTimerMsec			LTimerUpdateDIO;


	/////////////////////////////////////////////////////////////////
	// ������ ���� //////////////////////////////////////////////////
	while (TRUE) {


		/////////////////////////////////////////////////////////////
		// ������ ����Ī ////////////////////////////////////////////
		if (--nThreadCount == 0) {

			Sleep(1);
			nThreadCount = THREAD_COUNT_MAIN;
		}


		/////////////////////////////////////////////////////////////
		// DIO ����� ������Ʈ //////////////////////////////////////
		if (LTimerUpdateDIO.Verify()) {
		
			if (pMainApp->m_pDIOMonitorDlg && (pMainApp->m_pDIOMonitorDlg)->GetSafeHwnd()) {
			
				(pMainApp->m_pDIOMonitorDlg)->PostMessage(UM_DIO_MONITOR_V3_UPDATE);
				LTimerUpdateDIO.Start(100);
			}
		}


		/////////////////////////////////////////////////////////////
		// ������ ���� üũ /////////////////////////////////////////
		pMainApp->m_csExitThread[THREAD_MAIN].Lock();
		if (pMainApp->m_bExitThread[THREAD_MAIN]) {

			pMainApp->m_csExitThread[THREAD_MAIN].Unlock();
			break;
		}

		pMainApp->m_csExitThread[THREAD_MAIN].Unlock();


		/////////////////////////////////////////////////////////////
		// ���� ������ �÷��� üũ //////////////////////////////////
		if (!pstSystemStatus->bOnSysMainThreadStart)	continue;


		/////////////////////////////////////////////////////////////
		// ���� ���μ��� ////////////////////////////////////////////
		switch (nCurrentStep) {

			/////////////////////////////////////////////////////////
			// �⺻ ���μ��� : ��� �ʱ�ȭ //////////////////////////
			case	100		:
								pstErrorCode = pMainApp->ProcessMachineInit();
								nCurrentStep = 1000;
								break;


			/////////////////////////////////////////////////////////
			// ���� ���μ��� ////////////////////////////////////////
			case	1000	:
								pstErrorCode = pMainApp->ProcessMainWorkProcedure();
								nCurrentStep++;
								break;

			case	1001	:
								pstErrorCode = pMainApp->ProcessMainWorkTest();
								nCurrentStep++;
								break;

			case	1002	:
								//pstErrorCode = pMainApp->ProcessMainWorkVision();
								nCurrentStep = 2000;
								break;


			/////////////////////////////////////////////////////////
			// ���� ���μ��� ////////////////////////////////////////
			case	2000	:
								pstErrorCode = pMainApp->ProcessCommon();
								nCurrentStep = 2100;
								break;

			/////////////////////////////////////////////////////////

			case	2100	:
								if (nTypeMachine == MC_TYPE_1)	pstErrorCode = pMainApp->ProcessStation01();
								nCurrentStep++;
								break;

			case	2101	:
								if (nTypeMachine == MC_TYPE_2)	pstErrorCode = pMainApp->ProcessStation02();
								nCurrentStep = 3000;
								break;

			/////////////////////////////////////////////////////////

			case	3000	:
								nCurrentStep = 3100;
								break;

			/////////////////////////////////////////////////////////

			case	3100	:
								if (nTypeMachine == MC_TYPE_1)	pstErrorCode = pMainApp->ProcessStation01Parts();
								nCurrentStep++;
								break;

			case	3101	:
								if (nTypeMachine == MC_TYPE_2)	pstErrorCode = pMainApp->ProcessStation02Parts();
								nCurrentStep = 8000;
								break;


			/////////////////////////////////////////////////////////
			// ��Ÿ ���μ��� ////////////////////////////////////////
			case	8000	:
								pstErrorCode = pMainApp->ProcessDeviceLC();
								nCurrentStep = 8010;
								break;

			case	8010	:
								pMainApp->ProcessBarcodeScan();
								nCurrentStep = 8020;
								break;

			case	8020	:	
								pMainApp->ProcessLabelPrint(BCP_PRINT_1);
								nCurrentStep = 8100;
								break;

			/////////////////////////////////////////////////////////
			case	8100	:
								pMainApp->ProcessCheckEmergency();
								nCurrentStep = 8110;
								break;

			case	8110	:
								pMainApp->ProcessCheckDoorOpen();
								nCurrentStep = 8500;
								break;


			/////////////////////////////////////////////////////////
			// ��� ���μ��� ////////////////////////////////////////
			case	8500	:
								if (pstSystemStatus->bOnMachineInitialize) {
								
									nCurrentStep = 8510;
									break;
								}

								nCurrentStep = 8700;
								break;

			case	8510	:
								//pMainApp->ProcessMotionHomeSearch03(MOTION_RVX, HomeSensor);
								pMainApp->ProcessMotionHomeSearch01(MOTION_RVX);
								nCurrentStep++;
								break;

			case	8511	:
								//pMainApp->ProcessMotionHomeSearch03(MOTION_RVY, HomeSensor);				
								pMainApp->ProcessMotionHomeSearch01(MOTION_RVY);
								nCurrentStep++;
								break;

			case	8512	:
								//pMainApp->ProcessMotionHomeSearch03(MOTION_RVZ, HomeSensor);				
								pMainApp->ProcessMotionHomeSearch01(MOTION_RVZ);
								nCurrentStep = 8700;
								break;

			case	8700	:
								pMainApp->ProcessMotion();	
								nCurrentStep = 9000;
								break;


			/////////////////////////////////////////////////////////
			case	9000	:
								nCurrentStep = 100;
								break;
		}


		/////////////////////////////////////////////////////////////
		// �ý��� ���μ��� //////////////////////////////////////////


		/////////////////////////////////////////////////////////////
		// ���� �߻� ////////////////////////////////////////////////
		if (pstErrorCode) {

			// �˶� �̷� ���̾�α׿� �޼��� ����
			if (pMainApp->m_pSysHistoryDlg)		(pMainApp->m_pSysHistoryDlg)->SendMessage(UM_HISTORY_ON_ERROR, (WPARAM)pstErrorCode);

			// ���� �ڵ� �ʱ�ȭ
			pstErrorCode	= NULL;
		}
	}


	return	0;
}







///////////////////////////////////////////////////////////////////////////////////////////////////
// ������ : �ý��� ////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
UINT CMainApp::ThreadFuncSystem(LPVOID lpParam)
{
	CMainApp*			pMainApp			= (CMainApp*)lpParam;
	CDpsSystemConfig*	pSystemConfig		= pMainApp->GetSystemConfig();
	PSYSTEM_STATUS_T	pstSystemStatus		= pMainApp->GetSystemStatus();
	PERROR_CODE_T		pstErrorCode		= NULL;

	UINT				nThreadID			= THREAD_SYSTEM;
	UINT				nThreadCount		= THREAD_COUNT_SYSTEM;
	UINT				nCurrentStep		= 100;
	UINT				nPreviousStep		= 0;

	UINT				nTypeLanguage		= pSystemConfig->GetTypeLanguage();

	CString				strValue			= _T("");

	LTimerMsec			LTimerThread;


	/////////////////////////////////////////////////////////////////
	// ������ ���� //////////////////////////////////////////////////
	while (TRUE) {


		/////////////////////////////////////////////////////////////
		// Context Switching ////////////////////////////////////////
		if (--nThreadCount == 0) {

			Sleep(1);
			nThreadCount = THREAD_COUNT_SYSTEM;
		}


		/////////////////////////////////////////////////////////////
		// ������ ���� üũ /////////////////////////////////////////
		pMainApp->m_csExitThread[nThreadID].Lock();
		if (pMainApp->m_bExitThread[nThreadID]) {

			pMainApp->m_csExitThread[nThreadID].Unlock();
			break;
		}

		pMainApp->m_csExitThread[nThreadID].Unlock();


		/////////////////////////////////////////////////////////////
		// ���� ���μ��� ////////////////////////////////////////////
		switch (nCurrentStep) {

			case	100		:
								nCurrentStep = 1000;
								break;


			/////////////////////////////////////////////////////////
			// �ý��� ���μ��� //////////////////////////////////////
			case	1000	:
								pMainApp->ProcessErrorDetect();	
								nCurrentStep = 1010;
								break;

			case	1010	:
								pMainApp->ProcessCheckAirPressure();
								nCurrentStep = 1100;
								break;

			case	1100	:
								pMainApp->ProcessSystem();
								nCurrentStep = 9000;
								break;


			/////////////////////////////////////////////////////////
			case	9000	:
								nCurrentStep = 100;
								break;
		}


		/////////////////////////////////////////////////////////////
		// �ý��� ���μ��� //////////////////////////////////////////


		/////////////////////////////////////////////////////////////
		// ��Ÿ ���μ��� ////////////////////////////////////////////
		pMainApp->ProcessDeviceCAN();


		/////////////////////////////////////////////////////////////
		// ���� �߻� ////////////////////////////////////////////////
		if (pstErrorCode) {

			// �˶� �̷� ���̾�α׿� �޼��� ����
			if (pMainApp->m_pSysHistoryDlg)		(pMainApp->m_pSysHistoryDlg)->SendMessage(UM_HISTORY_ON_ERROR, (WPARAM)pstErrorCode);

			// ���� �ڵ� �ʱ�ȭ
			pstErrorCode	= NULL;
		}
	}


	return	0;
}






///////////////////////////////////////////////////////////////////////////////////////////////////
// ������ : ���� //////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
UINT CMainApp::ThreadFuncSub(LPVOID lpParam)
{
	PTHREAD_PARAM_T		pstParam			= (PTHREAD_PARAM_T)lpParam;
	CMainApp*			pMainApp			= (CMainApp*)pstParam->pMainApp;
	CDpsSystemConfig*	pSystemConfig		= pMainApp->GetSystemConfig();
	PSYSTEM_STATUS_T	pstSystemStatus		= pMainApp->GetSystemStatus();
	PERROR_CODE_T		pstErrorCode		= NULL;

	UINT				nThreadID			= pstParam->nThreadID;
	UINT				nThreadCount		= THREAD_COUNT_SUB;
	UINT				nCurrentStep		= 100;
	UINT				nPreviousStep		= 0;

	UINT				nTypeLanguage		= pSystemConfig->GetTypeLanguage();

	CString				strValue			= _T("");

	LTimerMsec			LTimerThread;


	/////////////////////////////////////////////////////////////////
	// ������ ���� //////////////////////////////////////////////////
	while (TRUE) {


		/////////////////////////////////////////////////////////////
		// Context Switching ////////////////////////////////////////
		if (--nThreadCount == 0) {

			Sleep(1);
			nThreadCount = THREAD_COUNT_SUB;
		}


		/////////////////////////////////////////////////////////////
		// ������ ���� üũ /////////////////////////////////////////
		pMainApp->m_csExitThread[nThreadID].Lock();
		if (pMainApp->m_bExitThread[nThreadID]) {

			pMainApp->m_csExitThread[nThreadID].Unlock();
			break;
		}

		pMainApp->m_csExitThread[nThreadID].Unlock();


		/////////////////////////////////////////////////////////////
		// ���� ���μ��� ////////////////////////////////////////////
		switch (nCurrentStep) {

			// ...
			case	100		:
								nCurrentStep = 200;
								break;

			// ���μ��� : ���� �˻�
			case	200		:
								pstErrorCode = pMainApp->ProcessMainWorkVision();
								nCurrentStep = 100;
								break;
		}


		/////////////////////////////////////////////////////////////
		// ���� �߻� ////////////////////////////////////////////////
		if (pstErrorCode) {

			// �˶� �̷� ���̾�α׿� �޼��� ����
			if (pMainApp->m_pSysHistoryDlg)		(pMainApp->m_pSysHistoryDlg)->SendMessage(UM_HISTORY_ON_ERROR, (WPARAM)pstErrorCode);

			// ���� �ڵ� �ʱ�ȭ
			pstErrorCode	= NULL;
		}
	}


	/////////////////////////////////////////////////////////////////
	// �Ķ���� ���� ////////////////////////////////////////////////
	delete	pstParam;


	return	0;
}






///////////////////////////////////////////////////////////////////////////////////////////////////
// ������ : ������ ���̽� /////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
UINT CMainApp::ThreadFuncDBMS(LPVOID lpParam)
{
	CMainApp*			pMainApp			= (CMainApp*)lpParam;
	CDpsSystemConfig*	pSystemConfig		= pMainApp->GetSystemConfig();
	PSYSTEM_STATUS_T	pstSystemStatus		= pMainApp->GetSystemStatus();
	PERROR_CODE_T		pstErrorCode		= NULL;

	UINT				nThreadID			= THREAD_DBMS;
	UINT				nThreadCount		= THREAD_COUNT_DBMS;
	UINT				nCurrentStep		= 100;
	UINT				nPreviousStep		= 0;

	UINT				nTypeLanguage		= pSystemConfig->GetTypeLanguage();

	CString				strValue			= _T("");

	LTimerMsec			LTimerThread;


	/////////////////////////////////////////////////////////////////
	// ������ ���� //////////////////////////////////////////////////
	while (TRUE) {


		/////////////////////////////////////////////////////////////
		// Context Switching ////////////////////////////////////////
		if (--nThreadCount == 0) {

			Sleep(1);
			nThreadCount = THREAD_COUNT_SYSTEM;
		}


		/////////////////////////////////////////////////////////////
		// ������ ���� üũ /////////////////////////////////////////
		pMainApp->m_csExitThread[nThreadID].Lock();
		if (pMainApp->m_bExitThread[nThreadID]) {

			pMainApp->m_csExitThread[nThreadID].Unlock();
			break;
		}

		pMainApp->m_csExitThread[nThreadID].Unlock();


		/////////////////////////////////////////////////////////////
		// ���� ���μ��� ////////////////////////////////////////////
		switch (nCurrentStep) {
		
			case	0		:
								break;
		}


		/////////////////////////////////////////////////////////////
		// ���� �߻� ////////////////////////////////////////////////
		if (pstErrorCode) {

			// �˶� �̷� ���̾�α׿� �޼��� ����
			if (pMainApp->m_pSysHistoryDlg)		(pMainApp->m_pSysHistoryDlg)->SendMessage(UM_HISTORY_ON_ERROR, (WPARAM)pstErrorCode);

			// ���� �ڵ� �ʱ�ȭ
			pstErrorCode	= NULL;
		}
	}


	return	0;
}
