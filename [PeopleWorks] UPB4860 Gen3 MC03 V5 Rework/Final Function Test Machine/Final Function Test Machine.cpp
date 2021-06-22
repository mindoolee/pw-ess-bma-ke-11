
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
// 프로그램 공유 섹션 설정 ////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma comment(linker, "/SECTION:.shr,RWS")
#pragma data_seg(".shr")
LONG	g_nProcessCount	= 0;
#pragma data_seg()







///////////////////////////////////////////////////////////////////////////////////////////////////
// CMainApp 클래스 ////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 메세지 맵 //////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CMainApp, CWinApp)

	/////////////////////////////////////////////////////////////////
	// 윈도우 메세지 ////////////////////////////////////////////////
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)

END_MESSAGE_MAP()


///////////////////////////////////////////////////////////////////////////////
// 클래스 생성 ////////////////////////////////////////////////////////////////
CMainApp::CMainApp()
{
	/////////////////////////////////////////////////////////////////
	// 다이얼로그 ///////////////////////////////////////////////////
	m_pDebugMonitorDlg		= NULL; 
	m_pMessageBoxDlg		= NULL;
	m_pSysDisplayDlg		= NULL;
	m_pSysMonitorDlg		= NULL;
	m_pSysHistoryDlg		= NULL;
	m_pDIOMonitorDlg		= NULL;
	m_pImageViewWnd			= NULL;

	ZeroMemory(m_pMCPSubPageDlg, sizeof(CMCPSubPageDlg*) * MAX_MCP_SUB_PAGE);


	/////////////////////////////////////////////////////////////////
	// 윈도우 ///////////////////////////////////////////////////////
	m_pSysStateMonitorWnd	= NULL;
	m_pProductionWnd		= NULL;
	m_pWorkInfoWnd			= NULL;
	m_pTimerWnd				= NULL;

	m_pTactTimerWndOverView	= NULL;
	ZeroMemory(m_pTactTimerWnd, sizeof(CDpsTimerWnd*) * MAX_STATION);


	/////////////////////////////////////////////////////////////////
	// 일반 /////////////////////////////////////////////////////////
	m_pDIOCtrl[DIO_CTRL_1]	= NULL;

	m_nTypeLanguage			= LANGUAGE_KOR;
	m_nTypeMachine			= MC_TYPE_1;

	ZeroMemory(&m_stSystemStatus, sizeof(SYSTEM_STATUS_T));
	ZeroMemory(m_pThread, sizeof(CWinThread*) * MAX_WORK_THREAD);


	/////////////////////////////////////////////////////////////////
	// 데이터 ///////////////////////////////////////////////////////
	for (UINT nStationNo = 0; nStationNo < MAX_STATION; nStationNo++) {
	
		m_strCurrentProductCode[nStationNo] = _T("");
	}

	m_pstTestProcedureData				= NULL;
	m_pstVisionProcedureData			= NULL;

	ZeroMemory(&m_stWorkStatus, sizeof(WORK_STATUS_T) * MAX_STATION);
	ZeroMemory(&m_stTestProcedureHeader, sizeof(TPRD_HEADER_T));
	ZeroMemory(&m_stVisionProcedureHeader, sizeof(VPRD_HEADER_T));


	/////////////////////////////////////////////////////////////////
	// CAN 통신 정보 ////////////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_CAN_SIGNAL_LIST; nIndex++)
		m_strCAN_MsgSignalValue[nIndex] = _T("");


	/////////////////////////////////////////////////////////////////
	// 비전 검사 ////////////////////////////////////////////////////
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
// 유일한 클래스 개체 /////////////////////////////////////////////////////////
CMainApp theApp;


///////////////////////////////////////////////////////////////////////////////
// 어플리케이션 초기화 ////////////////////////////////////////////////////////
BOOL CMainApp::InitInstance(void)
{
	/////////////////////////////////////////////////////////////////
	// 프로그램 중복 실행 방지 //////////////////////////////////////
	g_nProcessCount++;
	if (g_nProcessCount > 1) {

		if (m_nTypeLanguage == LANGUAGE_KOR)	AfxMessageBox(_T("프로그램이 이미 실행중입니다."));
		else									AfxMessageBox(_T("This Program is already running..."));

		return	FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// 리치 에디트 컨트롤러 초기화 //////////////////////////////////
	AfxInitRichEdit2();


	/////////////////////////////////////////////////////////////////
	// 어플리케이션 초기화 //////////////////////////////////////////
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize	= sizeof(InitCtrls);
	InitCtrls.dwICC		= ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	if (!DPS_InitApplication()) {

		m_MessageBox.ErrorMessage(NULL, _T("프로그램을 초기화할 수 없습니다."));
		return	FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// 클래스 초기화 ////////////////////////////////////////////////
	CWinApp::InitInstance();
	CShellManager* pShellManager = new CShellManager;								// 셀 관리자
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));	// 비주얼 관리자

	
	/////////////////////////////////////////////////////////////////
	// 레지스트리 설정 //////////////////////////////////////////////
	SetRegistryKey(_T("DPS Applications"));


	/////////////////////////////////////////////////////////////////
	// 메인 다이얼로그 생성 /////////////////////////////////////////
	CMainDlg* pDlgMain = new CMainDlg;
	if (pDlgMain) {

		///////////////////////////////////////////////////
		// 메인 다이얼로그 포인터 설정 ////////////////////
		m_pMainWnd	= pDlgMain;


		///////////////////////////////////////////////////
		// 시스템 초기화 다이얼로그 실행 //////////////////
		CInitializeDlg	dlg(m_pMainWnd);
		dlg.DoModal();


		///////////////////////////////////////////////////
		// 메인 다이얼로그 실행 ///////////////////////////
		INT_PTR nResponse = pDlgMain->DoModal();
		delete	pDlgMain;
		if (nResponse == -1) {
			
			TRACE(traceAppMsg, 0, "경고: 대화 상자를 만들지 못했으므로 응용 프로그램이 예기치 않게 종료됩니다.\n");
			TRACE(traceAppMsg, 0, "경고: 대화 상자에서 MFC 컨트롤을 사용하는 경우 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS를 수행할 수 없습니다.\n");
		}


		///////////////////////////////////////////////////
		// 매트록스 이미지 라이브러리 종료 ////////////////
		MatroxRelease();

	} else {

		AfxMessageBox(_T("프로그램을 실행할 수 없습니다."));
	}

	return FALSE;
}








///////////////////////////////////////////////////////////////////////////////////////////////////
// 프로그램 공용 //////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 어플리케이션 초기화 ////////////////////////////////////////////////////////
BOOL CMainApp::DPS_InitApplication(void)
{
	BOOL		bResult		= TRUE;
	CString		strFileName	= _T("");
	CString		strFilePath	= _T("");
	CFileFind	fileFinder;


	/////////////////////////////////////////////////////////////////
	// 프로그램 시작 시간 설정 //////////////////////////////////////
	::GetLocalTime(&m_stTimeAppStart);


	/////////////////////////////////////////////////////////////////
	// 시스템 환경 설정 초기화 //////////////////////////////////////
	m_SystemConfig.InitSystemConfig();

	m_nTypeLanguage = m_SystemConfig.GetTypeLanguage();					// 언어 형식
	m_nTypeMachine	= m_SystemConfig.GetTypeMachine();					// 장비 형식
	m_stSystemStatus.bOnTestMode = m_SystemConfig.IsTestMode();			// 테스트 모드


	/////////////////////////////////////////////////////////////////
	// 시스템 정보 로드 /////////////////////////////////////////////

	// 모션 축 정보 로드
	strFileName.Format(_T("%s\\%s"), DPS_GetCurrentAppDirectory(), _TFILE_MOTION_AXIS_INFO);
	if (fileFinder.FindFile(strFileName))	LoadMotionAxisInfo(FALSE);
	else									LoadMotionAxisInfo(TRUE);
	
	fileFinder.Close();


	/////////////////////////////////////////////////////////////////
	// 모델 프로파일 설정 ///////////////////////////////////////////
	m_ModelProfile.SetModelProfilePath(m_SystemConfig.GetWorkDirectory(DIR_MODEL_PROFILE));		// 기본 디렉토리 설정
	m_ModelProfile.SetModelProfileExtension(_MPF_EXTENSION);									// 확장자 설정
	m_ModelProfile.SetModelProfileSize(sizeof(MODEL_PROFILE_T));								// 모델 프로파일 크기 설정


	/////////////////////////////////////////////////////////////////
	// 공통 인터페이스 설정 /////////////////////////////////////////

	// 검사 결과 색상 설정
	m_LibInterface.SetTestResultColorSet(T_RESULT_NONE, CLR_BLUE_DARKEST, CLR_YELLOW_LIGHTEST);
	m_LibInterface.SetTestResultColorSet(T_RESULT_SUCCESS, CLR_BLUE_DARKEST, CLR_GREEN_LIGHTEST);
	m_LibInterface.SetTestResultColorSet(T_RESULT_FAILURE, CLR_WHITE, CLR_RED);
	m_LibInterface.SetTestResultColorSet(T_RESULT_ERROR, CLR_WHITE, CLR_RED);


	/////////////////////////////////////////////////////////////////
	// 모듈 정보 로드 ///////////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_MODULES; nIndex++)
		m_stSystemStatus.stIncludedModules[nIndex] = g_stIncludedModules[nIndex];


	/////////////////////////////////////////////////////////////////
	// 작업 디렉토리 생성 ///////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_WORK_DIR; nIndex++) {

		if (g_stSystemPath[nIndex].bEnableDIR && g_stSystemPath[nIndex].bCreateDIR) 
			CreateDirectory(m_SystemConfig.GetWorkDirectory(nIndex), NULL);
	}


	/////////////////////////////////////////////////////////////////
	// 서브 카운터 정보 로드 ////////////////////////////////////////
	LoadWorkSubCounter();


	/////////////////////////////////////////////////////////////////
	// 매트록스 이미지 라이브러리 초기화 ////////////////////////////
	bResult = MatroxInitialize();


	/////////////////////////////////////////////////////////////////
	// 디지털 I/O 컨트롤러 초기화 ///////////////////////////////////
	for (UINT nIndex = 0; nIndex < (MAX_DIO_CTRL * MAX_DIO_CH); nIndex++)
		SetDOStatus(DO_OFF, nIndex);


	/////////////////////////////////////////////////////////////////
	// 작업 스레드 시작 /////////////////////////////////////////////
	if (!StartWorkProcess()) {
		
		SErrorMessage(FALSE, _T("작업 스레드를 생성할 수 없습니다."));
		bResult = FALSE;
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// 어플리케이션 종료 //////////////////////////////////////////////////////////
void CMainApp::DPS_ExitApplication(void)
{
	/////////////////////////////////////////////////////////////////
	// 인터-록 체크 /////////////////////////////////////////////////
	//if (m_stSystemStatus.nDeviceStatus[SD_DIO_1] == DS_NORMAL) {



	//}


	/////////////////////////////////////////////////////////////////
	// 작업 프로세스 정지 ///////////////////////////////////////////
	StopWorkProcess();


	/////////////////////////////////////////////////////////////////
	// 디바이스 종료 ////////////////////////////////////////////////

	///////////////////////////////////////////////////////
	// 디지털 I/O 컨트롤러 초기화 /////////////////////////
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
	// 모션 컨트롤러 종료 /////////////////////////////////
	for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++)
		AxmSignalServoOn(nAxisNo, DISABLE);

	DPS_Delay_ms(100);

	// 모션 컨트롤러 연결 해제
	if (AxlIsOpened())	AxlClose();


	///////////////////////////////////////////////////////
	// 파워 서플라이 종료 /////////////////////////////////
	m_devPOWER.DeviceQuit();


	///////////////////////////////////////////////////////
	// CAN 컨버터 종료 ////////////////////////////////////
	m_devCAN.DeviceClose();
	CDpsPCAN::PCAN_FreeLibrary();


	/////////////////////////////////////////////////////////////////
	// 통신 종료 ////////////////////////////////////////////////////
	ConnectComm(FALSE);


	/////////////////////////////////////////////////////////////////
	// 시스템 환경 설정 저장 ////////////////////////////////////////
	m_SystemConfig.SaveSystemConfig(TRUE);


	/////////////////////////////////////////////////////////////////
	// 시스템 정보 저장 /////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////
	// 데이터 제거 //////////////////////////////////////////////////
	if (m_pstTestProcedureData != NULL)		delete []	m_pstTestProcedureData;
	if (m_pstVisionProcedureData != NULL)	delete []	m_pstVisionProcedureData;
}


///////////////////////////////////////////////////////////////////////////////
// 유효 라이센스 검사 /////////////////////////////////////////////////////////
BOOL CMainApp::CheckValidLicense(BOOL bOnPopupMessage /* = TRUE */)
{
	UINT		nLicenseCode	= DPS_LICENSE_SUCCESS;
	CString		strMessage		= _T("");


	/////////////////////////////////////////////////////////////////
	// 라이센스 검사 ////////////////////////////////////////////////
	nLicenseCode = DPS_CheckLicenseKey(m_stSystemStatus.stLicenseInfo);


	/////////////////////////////////////////////////////////////////
	// 모듈 정보 설정 ///////////////////////////////////////////////
	_stprintf_s(m_stSystemStatus.stIncludedModules[MODULE_MRE_LICENSE_KEY].szModuleVersion, MAX_STRINPUT_L, _T("%s"), m_stSystemStatus.stLicenseInfo.szLicenseInfo);


	/////////////////////////////////////////////////////////////////
	// 메세지 출력 //////////////////////////////////////////////////
	if (nLicenseCode != DPS_LICENSE_SUCCESS) {

		if (bOnPopupMessage)	m_MessageBox.Message(MB_ICONEXCLAMATION, _T("LICENSE ERROR!"), m_stSystemStatus.stLicenseInfo.szErrorMessage);
		else					ErrorMessage(TRUE, m_stSystemStatus.stLicenseInfo.szErrorMessage);
	}


	return	(nLicenseCode == DPS_LICENSE_SUCCESS) ? TRUE : FALSE;
}


///////////////////////////////////////////////////////////////////////////////
// 통신 연결/종료 /////////////////////////////////////////////////////////////
BOOL CMainApp::ConnectComm(BOOL bConn)
{
	BOOL			bConnectResult	= TRUE;
	BOOL			bResult			= FALSE;
	SYSTEM_CONFIG_T	stSystemConfig	= m_SystemConfig.GetSystemConfig();


	/////////////////////////////////////////////////////////////////
	// 통신 연결 ////////////////////////////////////////////////////
	if (bConn) {

		///////////////////////////////////////////////////
		// 디지털 I/O 컨트롤러 연결 ///////////////////////
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
		// 바코드 스캐너 연결 /////////////////////////////
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
		// 라벨 프린터 연결 ///////////////////////////////
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
		// 디지털 멀티미터 연결 ///////////////////////////
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
		// 파워 서플라이 연결 /////////////////////////////
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
		// 비전 카메라 연결 ///////////////////////////////
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
		// 로드셀 컨트롤러 연결 ///////////////////////////
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
		// 연결 실패 //////////////////////////////////////
		if (!bConnectResult) {

			ErrorMessage(FALSE, _T(""));

			if (m_nTypeLanguage == LANGUAGE_KOR) {

				for (UINT nIndex = 0; nIndex < MAX_DIO_CTRL; nIndex++) {

					if (m_stSystemStatus.nDeviceStatus[SD_DIO_1 + nIndex] == DS_DISCONNECT)		
						ErrorMessage(FALSE, _T("[COM%d] 디지털 I/O 컨트롤러 #%d 통신 포트를 사용할 수 없습니다."), stSystemConfig.nCommPort[COMM_DIO_1 + nIndex], nIndex + 1);
				}

				for (UINT nIndex = 0; nIndex < MAX_BCD_SCAN; nIndex++) {
				
					if (m_stSystemStatus.nDeviceStatus[SD_SCAN_1 + nIndex] == DS_DISCONNECT)		
						ErrorMessage(FALSE, _T("[COM%d] 바코드 스캐너 #%d 통신 포트를 사용할 수 없습니다."), stSystemConfig.nCommPort[COMM_SCAN_1 + nIndex], nIndex + 1);
				}

				for (UINT nIndex = 0; nIndex < MAX_BARCODE_PRINTER; nIndex++) {
				
					if (m_stSystemStatus.nDeviceStatus[SD_PRINT_1 + nIndex] == DS_DISCONNECT)		
						ErrorMessage(FALSE, _T("[COM%d] 라벨 프린터 #%d 통신 포트를 사용할 수 없습니다."), stSystemConfig.nCommPort[COMM_PRINT_1 + nIndex], nIndex + 1);
				}

				if (m_stSystemStatus.nDeviceStatus[SD_DEV_DMM] == DS_DISCONNECT)		
					ErrorMessage(FALSE, _T("[COM%d] 디지털 멀티미터 통신 포트를 사용할 수 없습니다."), stSystemConfig.nCommPort[COMM_DEV_DMM]);

				if (m_stSystemStatus.nDeviceStatus[SD_DEV_PS] == DS_DISCONNECT)		
					ErrorMessage(FALSE, _T("[COM%d] DC 파워 소스 통신 포트를 사용할 수 없습니다."), stSystemConfig.nCommPort[COMM_DEV_PS]);

				if (m_stSystemStatus.nDeviceStatus[SD_DEV_CAM] == DS_DISCONNECT)		
					ErrorMessage(FALSE, _T("[COM%d] 비전 카메라 통신 포트를 사용할 수 없습니다."), stSystemConfig.nCommPort[COMM_DEV_CAM]);

				for (UINT nIndex = 0; nIndex < MAX_LOADCELL_CONTROLLERS; nIndex++) {
				
					if (m_stSystemStatus.nDeviceStatus[SD_DEV_LCC_1 + nIndex] == DS_DISCONNECT)		
						ErrorMessage(FALSE, _T("[COM%d] 로드셀 컨트롤러 #%d 통신 포트를 사용할 수 없습니다."), stSystemConfig.nCommPort[COMM_DEV_LCC_1 + nIndex], nIndex + 1);
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
	// 통신 연결 해제 ///////////////////////////////////////////////
	} else {

		for (UINT nIndex = 0; nIndex < MAX_COMM; nIndex++)
			m_Comm[nIndex].DestroyComm();
	}


	return	bConnectResult;
}


///////////////////////////////////////////////////////////////////////////////
// 시스템 준비 상태 체크 //////////////////////////////////////////////////////
BOOL CMainApp::IsSystemReady(void)
{
	BOOL	bResult	= TRUE;


	/////////////////////////////////////////////////////////////////
	// 시스템 초기화 결과 ///////////////////////////////////////////
	bResult &= m_stSystemStatus.bResultSystemInitialize;


	/////////////////////////////////////////////////////////////////
	// 장비 초기화 결과 /////////////////////////////////////////////
	if (m_nTypeMachine == MC_TYPE_1)	bResult &= m_stSystemStatus.bResultMachineInitialize;


	/////////////////////////////////////////////////////////////////
	// 모델 프로파일 선택 ///////////////////////////////////////////
	bResult &= m_stSystemStatus.bIsSelectedProfile;


	/////////////////////////////////////////////////////////////////
	// 시스템 디바이스 상태 /////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_SYSTEM_DEVICE; nIndex++) {

		bResult &= (m_stSystemStatus.nDeviceStatus[nIndex] != DS_DISCONNECT && m_stSystemStatus.nDeviceStatus[nIndex] != DS_ERROR && m_stSystemStatus.nDeviceStatus[nIndex] != DS_NORESPONSE) ? TRUE : FALSE;
	}


	return	m_SystemConfig.IsSimulationMode() ? TRUE : bResult;
}


///////////////////////////////////////////////////////////////////////////////
// DIO : 출력 설정 ////////////////////////////////////////////////////////////
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
// DIO : 입력 설정 ////////////////////////////////////////////////////////////
BOOL CMainApp::GetDIStatus(UINT nPort)
{
	BOOL	bStatus	= FALSE;

	if (m_pDIOCtrl[DIO_CTRL_1]) {

		bStatus = m_pDIOCtrl[DIO_CTRL_1]->GetDIStatus(nPort);
	}

	return	bStatus;
}


///////////////////////////////////////////////////////////////////////////////
// 시스템 메세지 //////////////////////////////////////////////////////////////
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

			// 출력될 메세지에 CR+LF 추가
			if (bViewDate)	strMsg.Format(_T("%s\t%s\t%s\r\n"), CTime(CTime::GetCurrentTime()).Format(_T("%Y-%m-%d")), CTime(CTime::GetCurrentTime()).Format(_T("%H:%M:%S")), szMessage);
			else			strMsg.Format(_T("%s\r\n"), szMessage);

			// 검사 이력 다이얼로그에 메세지 출력
			m_pSysHistoryDlg->ViewSysMessage(strMsg, CLR_SYS_MSG_PROCESS);

			// 메인 다이얼로그로 전달
			PSYSTEM_MSG_T	pstSystemMsg	= new SYSTEM_MSG_T;
			if (pstSystemMsg) {

				ZeroMemory(pstSystemMsg, sizeof(SYSTEM_MSG_T));
				_stprintf_s(pstSystemMsg->szMessage, MAX_STRVALUE, _T("%s\r\n"), szMessage);
				pstSystemMsg->crTextColor	= CLR_SYS_MSG_PROCESS;

				if (m_pMainWnd->GetSafeHwnd())	m_pMainWnd->PostMessage(UM_MAIN_SYSTEM_MESSAGE, 0, (LPARAM)pstSystemMsg);
				else							delete pstSystemMsg;
			}

			// 메모리 해제
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

			// 출력될 메세지
			if (bViewDate)	strMsg.Format(_T("%s\t%s\t%s"), CTime(CTime::GetCurrentTime()).Format(_T("%Y-%m-%d")), CTime(CTime::GetCurrentTime()).Format(_T("%H:%M:%S")), szMessage);
			else			strMsg.Format(_T("%s"), szMessage);

			// 시스템 이력 다이얼로그에 메세지 출력
			m_pSysHistoryDlg->ViewSysMessage(strMsg, CLR_SYS_MSG_PROCESS);
			
			// 메인 다이얼로그로 전달
			PSYSTEM_MSG_T	pstSystemMsg	= new SYSTEM_MSG_T;
			if (pstSystemMsg) {

				ZeroMemory(pstSystemMsg, sizeof(SYSTEM_MSG_T));
				_stprintf_s(pstSystemMsg->szMessage, MAX_STRVALUE, _T("%s"), szMessage);
				pstSystemMsg->crTextColor	= CLR_SYS_MSG_PROCESS;

				if (m_pMainWnd->GetSafeHwnd())	m_pMainWnd->PostMessage(UM_MAIN_SYSTEM_MESSAGE, 0, (LPARAM)pstSystemMsg);
				else							delete pstSystemMsg;
			}

			// 메모리 해제
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

			// 출력될 메세지에 CR+LF 추가
			if (bViewDate)	strMsg.Format(_T("%s\t%s\t%s\r\n"), CTime(CTime::GetCurrentTime()).Format(_T("%Y-%m-%d")), CTime(CTime::GetCurrentTime()).Format(_T("%H:%M:%S")), szMessage);
			else			strMsg.Format(_T("%s\r\n"), szMessage);

			// 시스템 이력 다이얼로그에 메세지 출력
			m_pSysHistoryDlg->ViewSysMessage(strMsg, CLR_SYS_MSG_ERROR);
			m_pSysHistoryDlg->ViewErrMessage(strMsg, CLR_SYS_MSG_ERROR);

			// 메인 다이얼로그로 전달
			PSYSTEM_MSG_T	pstSystemMsg	= new SYSTEM_MSG_T;
			if (pstSystemMsg) {

				ZeroMemory(pstSystemMsg, sizeof(SYSTEM_MSG_T));
				_stprintf_s(pstSystemMsg->szMessage, MAX_STRVALUE, _T("%s\r\n"), szMessage);
				pstSystemMsg->crTextColor	= CLR_SYS_MSG_ERROR;

				if (m_pMainWnd->GetSafeHwnd())	m_pMainWnd->PostMessage(UM_MAIN_SYSTEM_MESSAGE, 0, (LPARAM)pstSystemMsg);
				else							delete pstSystemMsg;
			}

			// 메모리 해제
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

			// 말머리 추가
			if (m_nTypeLanguage == LANGUAGE_KOR)	strTemp.Format(_T("[시스템 오류] %s"), szMessage);
			else									strTemp.Format(_T("[SYSTEM ERROR] %s"), szMessage);

			// 출력될 메세지에 CR+LF 추가
			if (bViewDate)	strMsg.Format(_T("%s\t%s\t%s\r\n"), CTime(CTime::GetCurrentTime()).Format(_T("%Y-%m-%d")), CTime(CTime::GetCurrentTime()).Format(_T("%H:%M:%S")), strTemp);
			else			strMsg.Format(_T("%s\r\n"), strTemp);

			// 시스템 이력 다이얼로그에 메세지 출력
			m_pSysHistoryDlg->ViewSysMessage(strMsg, CLR_SYS_MSG_ERROR);
			m_pSysHistoryDlg->ViewErrMessage(strMsg, CLR_SYS_MSG_ERROR);

			// 메인 다이얼로그로 전달
			PSYSTEM_MSG_T	pstSystemMsg	= new SYSTEM_MSG_T;
			if (pstSystemMsg) {

				ZeroMemory(pstSystemMsg, sizeof(SYSTEM_MSG_T));
				_stprintf_s(pstSystemMsg->szMessage, MAX_STRVALUE, _T("%s\r\n"), szMessage);
				pstSystemMsg->crTextColor	= CLR_SYS_MSG_ERROR;

				if (m_pMainWnd->GetSafeHwnd())	m_pMainWnd->PostMessage(UM_MAIN_SYSTEM_MESSAGE, 0, (LPARAM)pstSystemMsg);
				else							delete pstSystemMsg;
			}

			// 메모리 해제
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

			// 말머리 추가
			if (m_nTypeLanguage == LANGUAGE_KOR)	strTemp.Format(_T("[디버그] %s"), szMessage);
			else									strTemp.Format(_T("[DEBUG] %s"), szMessage);

			// 출력될 메세지에 CR+LF 추가
			if (bViewDate)	strMsg.Format(_T("%s\t%s\t%s\r\n"), CTime(CTime::GetCurrentTime()).Format(_T("%Y-%m-%d")), CTime(CTime::GetCurrentTime()).Format(_T("%H:%M:%S")), strTemp);
			else			strMsg.Format(_T("%s\r\n"), strTemp);

			// 시스템 이력 다이얼로그에 메세지 출력
			m_pSysHistoryDlg->ViewSysMessage(strMsg, CLR_SYS_MSG_DEBUG);

			// 메인 다이얼로그로 전달
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

			// 메모리 해제
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

			// 출력될 메세지에 CR+LF 추가
			if (bViewDate)	strMsg.Format(_T("%s\t%s\t%s\r\n"), CTime(CTime::GetCurrentTime()).Format(_T("%Y-%m-%d")), CTime(CTime::GetCurrentTime()).Format(_T("%H:%M:%S")), szMessage);
			else			strMsg.Format(_T("%s\r\n"), szMessage);

			// 시스템 이력 다이얼로그에 메세지 출력
			m_pSysHistoryDlg->ViewSysMessage(strMsg, CLR_SYS_MSG_NORMAL);

			// 메모리 해제
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

			// 출력될 메세지
			if (bViewDate)	strMsg.Format(_T("%s\t%s\t%s"), CTime(CTime::GetCurrentTime()).Format(_T("%Y-%m-%d")), CTime(CTime::GetCurrentTime()).Format(_T("%H:%M:%S")), szMessage);
			else			strMsg.Format(_T("%s"), szMessage);

			// 시스템 이력 다이얼로그에 메세지 출력
			m_pSysHistoryDlg->ViewSysMessage(strMsg, CLR_SYS_MSG_NORMAL);

			// 메모리 해제
			delete[]	szMessage;

			return	TRUE;
		}
	}

	return	FALSE;
}


///////////////////////////////////////////////////////////////////////////////
// 디버그 메세지 //////////////////////////////////////////////////////////////
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

			// 출력될 메세지에 CR+LF 추가
			//strMsg.Format(_T("%s\r\n"), strMessage);

			// 메세지 윈도우에 출력
			m_pDebugMonitorDlg->Display(clrColor, szMessage);

			// 메모리 해제
			delete []	szMessage;

			return	TRUE;
		}
	}

	return	FALSE;
}







///////////////////////////////////////////////////////////////////////////////////////////////////
// 시뮬래이션 /////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////







///////////////////////////////////////////////////////////////////////////////////////////////////
// 작업 상태 //////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 작업 상태 초기화 ///////////////////////////////////////////////////////////
BOOL CMainApp::InitWorkStatus(UINT nStationNo)
{
	BOOL					bResult				= FALSE;

	PWORK_STATUS_T			pstWorkStatus		= &m_stWorkStatus[nStationNo];
	PMODEL_PROFILE_T		pstModelProfile		= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
	SYSTEM_CONFIG_T			stSystemConfig		= m_SystemConfig.GetSystemConfig();


	/////////////////////////////////////////////////////////////////
	// 작업 상태 초기화 /////////////////////////////////////////////
	ZeroMemory(pstWorkStatus, sizeof(WORK_STATUS_T));

	// 작업 결과 초기화
	pstWorkStatus->nResultFinal	= T_RESULT_SUCCESS;


	/////////////////////////////////////////////////////////////////
	// 작업 시간 초기화 /////////////////////////////////////////////
	::GetLocalTime(&pstWorkStatus->stTimeWorkStart);


	/////////////////////////////////////////////////////////////////
	// 성능 검사 데이터 초기화 //////////////////////////////////////
	m_arrFuncTestData.RemoveAll();
	m_arrContiMeasData.RemoveAll();


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// 비전 검사 초기화 ///////////////////////////////////////////////////////////
BOOL CMainApp::InitVisionTest(void)
{
	/////////////////////////////////////////////////////////////////
	// 비전 검사 초기화 /////////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_TEST_SHEET; nIndex++) {
	
		// 검사 이미지 버퍼 초기화
		if (m_MilImageInspection[nIndex] != M_NULL) {
		
			MbufFree(m_MilImageInspection[nIndex]);
			m_MilImageInspection[nIndex] = M_NULL;
		}

		// 검사 데이터 초기화
		m_arrVisionTestData[nIndex].RemoveAll();
	}


	return	TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// 작업 결과 디렉토리 생성 ////////////////////////////////////////////////////
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


	// 기본 저장 디렉토리 설정
	strDirSave = m_SystemConfig.GetWorkDirectory(DIR_SAVE_DATA);

	// 모델 디렉토리 생성
	strDirectory.Format(_T("%s\\%s"), strDirSave, DPS_GetFileInfo(stSystemConfig.szLastModelFile).szFileName);
	CreateDirectory(strDirectory, NULL);

	// 날짜 디렉토리 생성
	strDirectory.AppendFormat(_T("\\%s"), CTime(stProductionSystem.stTimeProduction).Format(_T("%Y-%m-%d")));
	CreateDirectory(strDirectory, NULL);

	// 제품 디렉토리 생성
	strProductCode = pstWorkStatus->szProductCode;
	if (strProductCode.IsEmpty())	strProductCode = _T("NOCODE");
	if (bIsMasterProduct)	strDirectory.AppendFormat(_T("\\(M)_%s_%s"), strProductCode, CTime(pstWorkStatus->stTimeWorkStart).Format(_T("%Y%m%d%H%M%S")));
	else					strDirectory.AppendFormat(_T("\\Inspection_%s_%s"), strProductCode, CTime(pstWorkStatus->stTimeWorkStart).Format(_T("%Y%m%d%H%M%S")));

	bResult = CreateDirectory(strDirectory, NULL);

	// 최종 디렉토리 설정
	_tcscpy_s(pstWorkStatus->szWorkDataSaveDirectory, MAX_STRFILE, strDirectory);


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// 작업 시트 저장 (성능 검사) /////////////////////////////////////////////////
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
	// 디렉토리 설정 ////////////////////////////////////////////////

	// 저장 디렉토리 설정
	strDirSave = m_SystemConfig.GetWorkDirectory(DIR_SAVE_DATA);

	// 모델 디렉토리 생성
	strDirectory.Format(_T("%s\\%s"), strDirSave, DPS_GetFileInfo(m_SystemConfig.GetLastModelProfile()).szFileName);
	CreateDirectory(strDirectory, NULL);

	// 날짜 디렉토리 생성
	strDirectory.AppendFormat(_T("\\%s"), CTime(stProductionSystem.stTimeProduction).Format(_T("%Y-%m-%d")));
	CreateDirectory(strDirectory, NULL);

	
	/////////////////////////////////////////////////////////////////
	// 파일 이름 설정 ///////////////////////////////////////////////
	strFileName.Format(_T("%s\\"), strDirectory);

	// 마스터 제품
	if (bIsMasterProduct)	strFileName.AppendFormat(_T("(M)_"));

	// 파일 이름 설정
	strFileName.AppendFormat(_T("%s_%s_%s"),	pstWorkStatus->szProductCode,
												CTime(pstWorkStatus->stTimeWorkStart).Format(_T("%Y%m%d_%H%M%S")),
												g_szTestResultEngS[pstWorkStatus->nResultFinal]);

	// 파일 확장자 설정
	strFileName.AppendFormat(_T(".CSV"));


	/////////////////////////////////////////////////////////////////
	// 데이터 저장 //////////////////////////////////////////////////
	TRY {

		if (bResult = fileSaveFile.Open(strFileName, CFile::modeCreate | CFile::modeWrite)) {

			/////////////////////////////////////////////////////////
			// 기본 헤더 정보 ///////////////////////////////////////
			strData.Empty();
			strData.AppendFormat(_T("\r\nOS EV CDM 최종 성능 검사 결과 보고서"));
			strData.AppendFormat(_T("\r\n\r\n"));


			/////////////////////////////////////////////////////////
			// 모델 프로파일 정보 ///////////////////////////////////
			strData.AppendFormat(_T("\r\n[모델 프로파일 정보]\r\n"));
			strData.AppendFormat(_T("모델 프로파일,%s\r\n"), DPS_GetFileInfo(m_SystemConfig.GetLastModelProfile()).szFileName);
			strData.AppendFormat(_T("모델 이름,%s\r\n"), pstModelProfile->stModelProfileInfo.szModelInfo[MI_MODEL_NAME]);


			/////////////////////////////////////////////////////////
			// 검사 정보 ////////////////////////////////////////////
			strData.AppendFormat(_T("\r\n[작업 정보]\r\n"));
			strData.AppendFormat(_T("LOT 시작,%s\r\n"), CTime(stProductionSystem.stTimeProduction).Format(_T("%Y년 %m월 %d일 %H시 %M분 %S초")));
			strData.AppendFormat(_T("검사 시각,%s\r\n"), CTime(pstWorkStatus->stTimeWorkStart).Format(_T("%Y년 %m월 %d일 %H시 %M분 %S초")));
			strData.AppendFormat(_T("검사 결과,%s\r\n"), g_szTestResult[pstWorkStatus->nResultFinal]);
			strData.AppendFormat(_T("제품 코드,%s\r\n"), pstWorkStatus->szProductCode);
			strData.AppendFormat(_T("출력 코드,%s\r\n"), pstWorkStatus->szOutputCode);


			/////////////////////////////////////////////////////////
			// 주 컬럼 작성 /////////////////////////////////////////
			strData.AppendFormat(_T("\r\n번호,커맨드,항목,결과,데이터,단위,하한값,상한값,파라미터,비고"));


			/////////////////////////////////////////////////////////
			// 파일에 저장 //////////////////////////////////////////
			CStringA	strSaveData(strData);
			fileSaveFile.SeekToBegin();
			fileSaveFile.Write(strSaveData, strSaveData.GetLength());
		}


		/////////////////////////////////////////////////////////////
		// 데이터를 저장 ////////////////////////////////////////////
		if (bResult) {

			INT					nDataMAX	= m_arrFuncTestData.GetCount();
			FUNC_TEST_DATA_T	stFuncTestData;

			// \n 삽입
			strData.Empty();
			strData.Format(_T("\r\n"));

			// 기본 검사 데이터
			for (INT nIndex = 0; nIndex < nDataMAX; nIndex++) {

				stFuncTestData = m_arrFuncTestData.GetAt(nIndex);

				// 번호
				strData.AppendFormat(_T("%d,"), nIndex + 1);

				// 커맨드
				strData.AppendFormat(_T("%s,"), g_stTestProcedureCommand[stFuncTestData.nCommand].szDescription[m_nTypeLanguage]);

				// 항목
				strData.AppendFormat(_T("%s,"), stFuncTestData.szName);

				// 결과
				strData.AppendFormat(_T("%s,"), g_szTestResultEng[stFuncTestData.nResult]);

				// 데이터
				strData.AppendFormat(_T("%s,"), stFuncTestData.szValue);

				// 단위
				strData.AppendFormat(_T("%s,"), stFuncTestData.szUnit);

				// 하한값
				strData.AppendFormat(_T("%s,"), stFuncTestData.szSpecMIN);

				// 상한값
				strData.AppendFormat(_T("%s,"), stFuncTestData.szSpecMAX);

				// 파라미터
				strData.AppendFormat(_T("%s,"), stFuncTestData.szParameters);
				strData.AppendFormat(_T("\r\n"));

				// CAN 데이터
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

			// 파일에 저장
			CStringA	strSaveData(strData);
			fileSaveFile.SeekToEnd();
			fileSaveFile.Write(strSaveData, strSaveData.GetLength());	
		}

		// 파일 종료
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
	// 디렉토리 설정 ////////////////////////////////////////////////

	// 저장 디렉토리 설정
	strDirSave = m_SystemConfig.GetWorkDirectory(DIR_SAVE_DATA);

	// 모델 디렉토리 생성
	strDirectory.Format(_T("%s\\%s"), strDirSave, DPS_GetFileInfo(m_SystemConfig.GetLastModelProfile()).szFileName);
	CreateDirectory(strDirectory, NULL);

	// 날짜 디렉토리 생성
	strDirectory.AppendFormat(_T("\\%s"), CTime(stProductionSystem.stTimeProduction).Format(_T("%Y-%m-%d")));
	CreateDirectory(strDirectory, NULL);

	
	/////////////////////////////////////////////////////////////////
	// 파일 이름 설정 ///////////////////////////////////////////////
	
	// 파일 이름 설정
	strFileName.Format(_T("%s\\InspectionReport_%s"), strDirectory, CTime(stProductionSystem.stTimeProduction).Format(_T("%H%M%S")));

	// 파일 확장자 설정
	strFileName.AppendFormat(_T(".CSV"));


	/////////////////////////////////////////////////////////////////
	// 데이터 저장 //////////////////////////////////////////////////
	TRY {

		/////////////////////////////////////////////////////////////
		// 새 파일 생성 /////////////////////////////////////////////
		if (!fileFinder.FindFile(strFileName)) {

			bResult = fileSaveFile.Open(strFileName, CFile::modeCreate | CFile::modeWrite);

		/////////////////////////////////////////////////////////////
		// 기존 파일이 있으면 추가로 기록 ///////////////////////////
		} else {

			bResult = fileSaveFile.Open(strFileName, CFile::modeWrite | CFile::modeNoTruncate);
		}


		/////////////////////////////////////////////////////////////
		// 헤더 저장 ////////////////////////////////////////////////
		{
			/////////////////////////////////////////////////////////
			// 기본 헤더 정보 ///////////////////////////////////////
			strData.Empty();
			strData.AppendFormat(_T("\r\nOS EV CDM 최종 성능 검사 결과 보고서"));
			strData.AppendFormat(_T("\r\n\r\n"));


			/////////////////////////////////////////////////////
			// 작업 정보 ////////////////////////////////////////
			strData.AppendFormat(_T("\r\n[작업 정보]\r\n"));
			strData.AppendFormat(_T("LOT 시작,%s\r\n"), CTime(stProductionSystem.stTimeProduction).Format(_T("%Y년 %m월 %d일 %H시 %M분 %S초")));


			/////////////////////////////////////////////////////////
			// 모델 프로파일 정보 ///////////////////////////////////
			strData.AppendFormat(_T("\r\n[모델 프로파일 정보]\r\n"));
			strData.AppendFormat(_T("모델 프로파일,%s\r\n"), DPS_GetFileInfo(m_SystemConfig.GetLastModelProfile()).szFileName);
			strData.AppendFormat(_T("모델 이름,%s\r\n"), pstModelProfile->stModelProfileInfo.szModelInfo[MI_MODEL_NAME]);
			strData.AppendFormat(_T("품번,%s\r\n"), pstModelProfile->stModelProfileInfo.szModelInfo[MI_PRODUCT_NO]);


			/////////////////////////////////////////////////////////
			// 검사 정보 ////////////////////////////////////////////
			strData.AppendFormat(_T("\r\n[검사 정보]\r\n"));
			strData.AppendFormat(_T("전체 수량,%10d\r\n"), stProductionInfo.nCountProduction);
			strData.AppendFormat(_T("양품 수량,%10d\r\n"), stProductionInfo.nCountProduction - stProductionInfo.nCountNG);
			strData.AppendFormat(_T("불량 수량,%10d\r\n"), stProductionInfo.nCountNG);


			/////////////////////////////////////////////////////////
			// 주 컬럼 작성 /////////////////////////////////////////
			strData.AppendFormat(_T("\r\n번호,검사 일자,검사 시각,제품 코드,검사 결과,출력 코드,비고"));


			/////////////////////////////////////////////////////////
			// 파일에 저장 //////////////////////////////////////////
			CStringA	strSaveData(strData);
			fileSaveFile.SeekToBegin();
			fileSaveFile.Write(strSaveData, strSaveData.GetLength());
		}


		/////////////////////////////////////////////////////////////
		// 데이터를 저장 ////////////////////////////////////////////
		if (bResult) {

			// \n 삽입
			strData.Empty();
			strData.Format(_T("\r\n"));

			// 번호
			strData.AppendFormat(_T("%d,"), stProductionInfo.nCountProduction);

			// 검사 일자
			strData.AppendFormat(_T("%s,"), CTime(pstWorkStatus->stTimeWorkStart).Format(_T("%Y-%m-%d")));

			// 검사 시각
			strData.AppendFormat(_T("%s,"), CTime(pstWorkStatus->stTimeWorkStart).Format(_T("%H:%M:%S")));

			// 제품 코드
			strData.AppendFormat(_T("%s,"), pstWorkStatus->szProductCode);

			// 검사 결과
			strData.AppendFormat(_T("%s,"), g_szTestResultEng[pstWorkStatus->nResultFinal]);

			// 출력 코드
			strData.AppendFormat(_T("%s,"), pstWorkStatus->szOutputCode);

			// 비고
			strData.AppendFormat(_T("%s,"), bIsMasterProduct ? _T("마스터 제품") : _T(""));


			// 파일에 저장
			CStringA	strSaveData(strData);
			fileSaveFile.SeekToEnd();
			fileSaveFile.Write(strSaveData, strSaveData.GetLength());	
		}

		// 파일 종료
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
	// 디렉토리 설정 ////////////////////////////////////////////////

	// 저장 디렉토리 설정
	strDirSave   = bIsMasterProduct ? m_SystemConfig.GetWorkDirectory(DIR_MASTER_DATA) : m_SystemConfig.GetWorkDirectory(DIR_EXPORT_DATA);
	strDirectory = strDirSave;

	// 모델 디렉토리 설정
	strDirectory.AppendFormat(_T("\\%s"), pstModelProfile->stModelProfileInfo.szModelInfo[MI_MODEL_NAME]);
	CreateDirectory(strDirectory, NULL);

	// 사양 디렉토리 설정
	strDirectory.AppendFormat(_T("\\%s"), pstModelProfile->stModelProfileInfo.szModelInfo[MI_SPECIFICATION]);
	CreateDirectory(strDirectory, NULL);

	// 날짜 디렉토리 생성
	if (!bIsMasterProduct)	timeCurrent = stProductionSystem.stTimeProduction;
	strDirectory.AppendFormat(_T("\\%s"), timeCurrent.Format(_T("%Y%m%d")));
	CreateDirectory(strDirectory, NULL);

	
	/////////////////////////////////////////////////////////////////
	// 파일 이름 설정 ///////////////////////////////////////////////
	strFileName.Format(_T("%s\\"), strDirectory);

	// 파일 이름 설정
	strFileName.Format(_T("%s\\%s_%10s_%s_%s_%c"),	strDirectory,
													pstWorkStatus->szProductCode,													// 제품 코드
													_T("XXXXXXXXXX"),																// 중요 데이터 값
													CTime(pstWorkStatus->stTimeWorkStart).Format(_T("%Y%m%d")),						// 작업 날짜
													CTime(pstWorkStatus->stTimeWorkStart).Format(_T("%H%M%S")),						// 작업 시간
													pstWorkStatus->nResultFinal == T_RESULT_SUCCESS ? TEXT('O') : TEXT('X'));		// 결과

	// 파일 확장자 설정
	strFileName.AppendFormat(_T(".TXT"));


	/////////////////////////////////////////////////////////////////
	// 데이터 저장 //////////////////////////////////////////////////
	TRY {

		if (bResult = fileSaveFile.Open(strFileName, CFile::modeCreate | CFile::modeWrite)) {

			/////////////////////////////////////////////////////////
			// 기본 헤더 정보 ///////////////////////////////////////
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
			// 검사 정보 ////////////////////////////////////////////
			strData.AppendFormat(_T("\r\n"));
			strData.AppendFormat(_T("검사 결과,%s\r\n"), g_szTestResult[pstWorkStatus->nResultFinal]);
			strData.AppendFormat(_T("제품 코드,%s\r\n"), pstWorkStatus->szProductCode);
			strData.AppendFormat(_T("출력 코드,%s\r\n"), pstWorkStatus->szOutputCode);


			/////////////////////////////////////////////////////////
			// 주 컬럼 작성 /////////////////////////////////////////
			strData.AppendFormat(_T("\r\n번호,커맨드,항목,결과,데이터,단위,하한값,상한값,파라미터,비고"));


			/////////////////////////////////////////////////////////
			// 파일에 저장 //////////////////////////////////////////
			CStringA	strSaveData(strData);
			fileSaveFile.SeekToBegin();
			fileSaveFile.Write(strSaveData, strSaveData.GetLength());
		}


		/////////////////////////////////////////////////////////////
		// 데이터를 저장 ////////////////////////////////////////////
		if (bResult) {

			INT					nDataMAX	= m_arrFuncTestData.GetCount();
			FUNC_TEST_DATA_T	stFuncTestData;

			// \n 삽입
			strData.Empty();
			strData.Format(_T("\r\n"));

			// 기본 검사 데이터
			for (INT nIndex = 0; nIndex < nDataMAX; nIndex++) {

				stFuncTestData = m_arrFuncTestData.GetAt(nIndex);

				// 번호
				strData.AppendFormat(_T("%d,"), nIndex + 1);

				// 커맨드
				strData.AppendFormat(_T("%s,"), g_stTestProcedureCommand[stFuncTestData.nCommand].szDescription[m_nTypeLanguage]);

				// 항목
				strData.AppendFormat(_T("%s,"), stFuncTestData.szName);

				// 결과
				strData.AppendFormat(_T("%s,"), g_szTestResultEng[stFuncTestData.nResult]);

				// 데이터
				strData.AppendFormat(_T("%s,"), stFuncTestData.szValue);

				// 단위
				strData.AppendFormat(_T("%s,"), stFuncTestData.szUnit);

				// 하한값
				strData.AppendFormat(_T("%s,"), stFuncTestData.szSpecMIN);

				// 상한값
				strData.AppendFormat(_T("%s,"), stFuncTestData.szSpecMAX);

				// 파라미터
				strData.AppendFormat(_T("%s,"), stFuncTestData.szParameters);
				strData.AppendFormat(_T("\r\n"));
			}

			// 파일에 저장
			CStringA	strSaveData(strData);
			fileSaveFile.SeekToEnd();
			fileSaveFile.Write(strSaveData, strSaveData.GetLength());	
		}

		// 파일 종료
		fileSaveFile.Close();

	} CATCH (CFileException, e) {
		e->ReportError();
	} END_CATCH


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// 비전 시트 저장 /////////////////////////////////////////////////////////////
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
	// 모델 정보 로드 ///////////////////////////////////////////////
	if (pstModelProfile == NULL)										return	FALSE;
	if (m_pstVisionProcedureData == NULL)								return	FALSE;
	if (m_stVisionProcedureHeader.nNumProcedureData <= nTestPointNo)	return	FALSE;

	pstStationSetup		= &pstModelProfile->stModelProfileConfig.stSpVisionSetupInfo;
	pstTestSetupInfo	= &pstStationSetup->stTestItemSetupInfo[nTestItemNo];
	pstProcedureData	= &m_pstVisionProcedureData[nTestPointNo];


	/////////////////////////////////////////////////////////////////
	// 디렉토리 설정 ////////////////////////////////////////////////

	// 기본 저장 디렉토리 설정
	strDirectory = pstWorkStatus->szWorkDataSaveDirectory;


	/////////////////////////////////////////////////////////////////
	// 파일 이름 설정 ///////////////////////////////////////////////

	// 파일 이름 설정
	strFileName.Format(_T("%s\\[T%02d] Vision Inspection Result"), strDirectory, nTestItemNo + 1);

	// 파일 확장자 설정
	strFileName.AppendFormat(_T(".CSV"));
	MessageWindow(cDEBUG, _T("VISION SAVE FILE = %s"), strFileName);


	/////////////////////////////////////////////////////////////////
	// 데이터 저장 //////////////////////////////////////////////////
	TRY {

		/////////////////////////////////////////////////////////////
		// 새 파일 생성 /////////////////////////////////////////////
		if (!fileFinder.FindFile(strFileName)) {

			if (bResult = fileSaveFile.Open(strFileName, CFile::modeCreate | CFile::modeWrite)) {

				/////////////////////////////////////////////////////
				// 기본 헤더 정보 ///////////////////////////////////
				strData.Empty();
				strData.AppendFormat(_T("\r\nVISION INSPECTION REPORT\r\n\r\n"));


				/////////////////////////////////////////////////////
				// 작업 정보 ////////////////////////////////////////
				strData.AppendFormat(_T("\r\n[WORK INFORMATIONS]\r\n"));
				strData.AppendFormat(_T("LOT START TIME,%s\r\n"), CTime(stProductionSystem.stTimeProduction).Format(_T("%Y-%m-%d %H:%M:%S")));
				strData.AppendFormat(_T("TEST DATE,%s\r\n"), timeCurrent.Format(_T("%Y-%m-%d")));
				strData.AppendFormat(_T("TEST TIME,%s\r\n"), timeCurrent.Format(_T("%H:%M:%S")));
				strData.AppendFormat(_T("TEST RESULT,%s\r\n"), g_szTestResultEng[pstWorkStatus->nResultFinal]);
				strData.AppendFormat(_T("TEST PROCEDURE,%s\r\n"), pstStationSetup->szVisionProcedureFile[nTestItemNo]);
				strData.AppendFormat(_T("PRODUCT CODE,%s\r\n"), pstWorkStatus->szProductCode);


				/////////////////////////////////////////////////////
				// 모델 프로파일 정보 ///////////////////////////////
				strData.AppendFormat(_T("\r\n[MODEL INFORMATIONS]\r\n"));
				strData.AppendFormat(_T("MODEL PROFILE,%s\r\n"), DPS_GetFileInfo(m_SystemConfig.GetLastModelProfile()).szFileName);
				strData.AppendFormat(_T("%s,%s\r\n"), g_stModelInfo[MI_MODEL_NAME].stName.szDescription[LANGUAGE_ENG], pstModelProfile->stModelProfileInfo.szModelInfo[MI_MODEL_NAME]);
				strData.AppendFormat(_T("%s,%s\r\n"), g_stModelInfo[MI_PRODUCT_NO].stName.szDescription[LANGUAGE_ENG], pstModelProfile->stModelProfileInfo.szModelInfo[MI_PRODUCT_NO]);
				strData.AppendFormat(_T("%s,%s\r\n"), g_stModelInfo[MI_SPECIFICATION].stName.szDescription[LANGUAGE_ENG], pstModelProfile->stModelProfileInfo.szModelInfo[MI_SPECIFICATION]);


				/////////////////////////////////////////////////////
				// 검사 정보 ////////////////////////////////////////
				strData.AppendFormat(_T("\r\n[INSPECTION INFORMATIONS]\r\n"));
				strData.AppendFormat(_T("TEST NAME,%s\r\n"), CString(pstTestSetupInfo->szUserDefName).IsEmpty() ? g_stTestSheetItem[pstTestSetupInfo->nTestSheetItem].szName[LANGUAGE_ENG] : pstTestSetupInfo->szUserDefName);
				strData.AppendFormat(_T("DELAY,%d\r\n"), pstTestSetupInfo->nValue[TSI_VALUE_COMMON_DELAY]);
				strData.AppendFormat(_T("SHUTTER SPEED,%d\r\n"), pstTestSetupInfo->nValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_CAMERA_SPEED]);
				strData.AppendFormat(_T("LIGHT VALUE,%d\r\n"), pstTestSetupInfo->nValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_LIGHT_VALUE_1]);
				strData.AppendFormat(_T("CAM POSITION (X),%.2f\r\n"), pstTestSetupInfo->dblValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_POSITION_1]);
				strData.AppendFormat(_T("CAM POSITION (Y),%.2f\r\n"), pstTestSetupInfo->dblValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_POSITION_2]);
				strData.AppendFormat(_T("CAM POSITION (Z),%.2f\r\n"), pstTestSetupInfo->dblValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_POSITION_3]);


				/////////////////////////////////////////////////////
				// 주 컬럼 작성 /////////////////////////////////////
				strData.AppendFormat(_T("\r\nNO,NAME,RESULT,VALUE,PARAMETERS,RETRY COUNT"));


				/////////////////////////////////////////////////////
				// 파일에 저장 //////////////////////////////////////
				//CStringA	strSaveData	= CW2A(strData, CP_UTF8);
				CStringA	strSaveData(strData);
				fileSaveFile.SeekToBegin();
				fileSaveFile.Write(strSaveData, strSaveData.GetLength());
			}

		/////////////////////////////////////////////////////////////
		// 기존 파일이 있으면 추가로 기록 ///////////////////////////
		} else {

			bResult = fileSaveFile.Open(strFileName, CFile::modeWrite | CFile::modeNoTruncate);
		}

		fileFinder.Close();


		/////////////////////////////////////////////////////////////
		// 데이터를 저장 ////////////////////////////////////////////
		if (bResult) {

			// \n 삽입
			strData.Empty();
			strData.Format(_T("\r\n"));

			// 번호
			strData.AppendFormat(_T("%lu,"), ++nItemNo);

			// 항목
			strData.AppendFormat(_T("%s,"), pstProcedureData->szName);

			// 결과
			strData.AppendFormat(_T("%s,"), g_szTestResultEng[stVisionTestData.nResult]);

			// 데이터
			strData.AppendFormat(_T("%.2f,"), stVisionTestData.dblValue);

			// 파라미터
			strData.AppendFormat(_T("%s,"), stVisionTestData.szParameters);

			// 재검사 횟수
			strValue.Empty();
			if (nInspectionCount)	strValue.Format(_T("%d"), nInspectionCount);
			else					strValue = _T("-");
			strData.AppendFormat(_T("%s"), strValue);
			
			// 파일에 저장
			//CStringA	strSaveData	= CW2A(strData, CP_UTF8);
			CStringA	strSaveData(strData);
			fileSaveFile.SeekToEnd();
			fileSaveFile.Write(strSaveData, strSaveData.GetLength());	
		}

		// 파일 종료
		if (bResult)	fileSaveFile.Close();

	} CATCH (CFileException, e) {
		e->ReportError();
	} END_CATCH


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// 사용자 메세지 설정 /////////////////////////////////////////////////////////
BOOL CMainApp::SetUserMessage(UINT nUserMessageID)
{
	if (m_stSystemStatus.nCurrentUserMessage >= UMSG_WARN_MACHINE_INITIALIZING)
		return	FALSE;

	m_stSystemStatus.nPreviousUserMessage = m_stSystemStatus.nCurrentUserMessage;
	m_stSystemStatus.nCurrentUserMessage  = nUserMessageID;

	return	TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// 서브 카운터 저장 ///////////////////////////////////////////////////////////
BOOL CMainApp::SaveWorkSubCounter(void)
{
	CString		strFileName		= _T("");
	BOOL		bFileResult		= TRUE;
	UINT		nRetryCount		= 0;
	CFile		fileWrite;


	TRY {

		/////////////////////////////////////////////////////////////
		// 파일 이름 설정 ///////////////////////////////////////////
		strFileName.Format(_T("%s\\%s"), DPS_GetCurrentAppDirectory(), _FILE_SUB_COUNTER_INFO);


		/////////////////////////////////////////////////////////////
		// 파일 저장 ////////////////////////////////////////////////
		while (TRUE) {

			if (bFileResult = fileWrite.Open(strFileName, CFile::modeCreate | CFile::modeWrite)) {

				fileWrite.Write(&m_stWorkSubCounter, sizeof(WORK_SUB_COUNT_T));
				fileWrite.Close();
			}

			// 성공이거나 재시도 횟수가 오버되면, 종료
			if (bFileResult || ++nRetryCount >= MAX_RETRY_COUNT)
				break;
		}

	} CATCH (CFileException, e) {
		e->ReportError();
	} END_CATCH


	return	bFileResult;
}


///////////////////////////////////////////////////////////////////////////////
// 서브 카운터 로드 ///////////////////////////////////////////////////////////
BOOL CMainApp::LoadWorkSubCounter(void)
{
	CString		strFileName		= _T("");
	BOOL		bFileResult		= TRUE;
	UINT		nRetryCount		= 0;
	UINT		nReadCount		= 0;
	CFile		fileRead;


	TRY {

		/////////////////////////////////////////////////////////////
		// 파일 이름 설정 ///////////////////////////////////////////
		strFileName.Format(_T("%s\\%s"), DPS_GetCurrentAppDirectory(), _FILE_SUB_COUNTER_INFO);


		/////////////////////////////////////////////////////////////
		// 파일 읽기 ////////////////////////////////////////////////
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

			// 성공이거나 재시도 횟수가 오버되면, 종료
			if (bFileResult || ++nRetryCount >= MAX_RETRY_COUNT)
				break;
		}

	} CATCH (CFileException, e) {
		e->ReportError();
	} END_CATCH


	return	bFileResult;
}


///////////////////////////////////////////////////////////////////////////////
// 제품 생산 날짜 코드 계산 ///////////////////////////////////////////////////
CString CMainApp::GetLOTDateCode(SYSTEMTIME stTime)
{
	CString		strCode = _T("");
	CString		strYear	= _T("");
	TCHAR		chCode	= 0;


	/////////////////////////////////////////////////////////////////
	// 연도 /////////////////////////////////////////////////////////
	strCode.AppendChar(TEXT('C') + stTime.wYear - 2007);


	/////////////////////////////////////////////////////////////////
	// 월 ///////////////////////////////////////////////////////////
	strCode.AppendChar(TEXT('A') + stTime.wMonth - 1);


	/////////////////////////////////////////////////////////////////
	// 일 ///////////////////////////////////////////////////////////
	if (stTime.wDay > 26)	strCode.AppendFormat(_T("%d"), stTime.wDay - 26);
	else					strCode.AppendFormat(_T("%c"), TEXT('A') + stTime.wDay - 1);


	return	strCode;
}


///////////////////////////////////////////////////////////////////////////////
// 마스터 검사 체크 ///////////////////////////////////////////////////////////
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
	// 마스터 제품 개수 체크 ////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_BCD_MASTER_CODE; nIndex++) {
	
		if (!CString(pstBasicSetupInfo->szMasterCode[nIndex]).IsEmpty())
			nNumMasterProduct++;
	}


	/////////////////////////////////////////////////////////////////
	// 마스터 검사 체크 /////////////////////////////////////////////
	if (nNumMasterProduct) {
	
		CString		strFileName	= _T("");
		CFileFind	fileFinder;


		for (UINT nIndex = 0; nIndex < MAX_BCD_MASTER_CODE; nIndex++) {
		
			if (!CString(pstBasicSetupInfo->szMasterCode[nIndex]).IsEmpty()) {
			
				// 파일 이름 설정
				strFileName.Empty();
				strFileName.Format(_T("%s\\%s\\%s\\%s\\*%s*.TXT"),	m_SystemConfig.GetWorkDirectory(DIR_MASTER_DATA), 
																	pstModelProfile->stModelProfileInfo.szModelInfo[MI_MODEL_NAME],
																	pstModelProfile->stModelProfileInfo.szModelInfo[MI_SPECIFICATION],
																	timeCurrent.Format(_T("%Y%m%d")),
																	pstBasicSetupInfo->szMasterCode[nIndex]);

				// 파일 검색
				bResult &= fileFinder.FindFile(strFileName);
				fileFinder.Close();
			}
		}
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// 바코드 스캐너 트리거 ///////////////////////////////////////////////////////
void CMainApp::SetTrigBarcode(UINT nID, BOOL bOnActivate /* = TRUE */)
{
	CComm*	pComm		= GetComm(COMM_SCAN_1 + nID);
	BYTE	byReadData	= 0;

	// 버퍼 초기화
	while (pComm->ReadByte(&byReadData));

	// 트리거 커맨드 전송
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
// 제품 코드 중복 체크 ////////////////////////////////////////////////////////
BOOL CMainApp::CheckProductCodeDuplicated(const CString& strProductCode, UINT nDIR_ID)
{
	BOOL		bResult			= TRUE;
	CString		strFileName		= _T("");

	CFileFind	fileFinder;


	/////////////////////////////////////////////////////////////////
	// 사용 유무 ////////////////////////////////////////////////////
	if (m_SystemConfig.UseSystemOption(SOPT_DISABLE_CHECK_DUPLICIATION_CODE))
		return	bResult;


	/////////////////////////////////////////////////////////////////
	// 파일 이름 설정 ///////////////////////////////////////////////
	strFileName.Format(_T("%s\\%s.INF"), m_SystemConfig.GetWorkDirectory(nDIR_ID), strProductCode);


	/////////////////////////////////////////////////////////////////
	// 파일 검색 ////////////////////////////////////////////////////
	if (fileFinder.FindFile(strFileName))	bResult = FALSE;

	fileFinder.Close();


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// 제품 코드 파일 저장 ////////////////////////////////////////////////////////
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
	// 파일 이름 설정 ///////////////////////////////////////////////
	strFileName.Format(_T("%s\\%s.INF"),	m_SystemConfig.GetWorkDirectory(nDIR_ID),
											stProductCodeInfo.szProductCode);


	/////////////////////////////////////////////////////////////////
	// 섹션 : 공통 정보 /////////////////////////////////////////////
	_tcscpy_s(szSection, MAX_STRVALUE, _T("COMMON"));

	// 생성 시간
	_stprintf_s(szValue, MAX_STRVALUE, _T("%s"), CTime(stProductCodeInfo.stTimeCreate).Format(_T("%Y-%m-%d,%H:%M:%S")));
	WritePrivateProfileString(szSection, _T("TIME_CREATE"), szValue, strFileName);

	// 수정 시간
	::GetLocalTime(&stProductCodeInfo.stTimeModify);
	_stprintf_s(szValue, MAX_STRVALUE, _T("%s"), CTime(stProductCodeInfo.stTimeModify).Format(_T("%Y-%m-%d,%H:%M:%S")));
	WritePrivateProfileString(szSection, _T("TIME_MODIFY"), szValue, strFileName);

	// 모델명
	_stprintf_s(szKeyName, MAX_STRVALUE, _T("MODEL_NAME"));
	WritePrivateProfileString(szSection, szKeyName, stProductCodeInfo.szModelName, strFileName);

	// 제품 코드
	_stprintf_s(szKeyName, MAX_STRVALUE, _T("PRODUCT_CODE"));
	WritePrivateProfileString(szSection, szKeyName, stProductCodeInfo.szProductCode, strFileName);

	// 작업 정보
	_stprintf_s(szValue, MAX_STRVALUE, _T("%d"), stProductCodeInfo.bIsWorkComplete);
	WritePrivateProfileString(szSection, _T("IS_WORK_COMPLETE"), szValue, strFileName);


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// 제품 코드 파일 로드 ////////////////////////////////////////////////////////
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
	// 초기화 ///////////////////////////////////////////////////////
	ZeroMemory(&stProductCodeInfo, sizeof(PRODUCT_CODE_INFO_T));


	/////////////////////////////////////////////////////////////////
	// 파일 이름 설정 ///////////////////////////////////////////////
	strFileName.Format(_T("%s\\%s.INF"),	m_SystemConfig.GetWorkDirectory(nDIR_ID),
											strProductCode);
	
	// 파일 존재 확인
	if (!fileFinder.FindFile(strFileName)) {

		fileFinder.Close();
		return	FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// 섹션 : 공통 정보 /////////////////////////////////////////////
	_tcscpy_s(szSection, MAX_STRVALUE, _T("COMMON"));

	// 생성 시간
	GetPrivateProfileString(szSection, _T("TIME_CREATE"), _T(""), szStringBuf, MAX_STRVALUE_L, strFileName);
	_stscanf_s(szStringBuf, _T("%d-%d-%d,%d:%d:%d"),	&stProductCodeInfo.stTimeCreate.wYear,
														&stProductCodeInfo.stTimeCreate.wMonth,
														&stProductCodeInfo.stTimeCreate.wDay,
														&stProductCodeInfo.stTimeCreate.wHour,
														&stProductCodeInfo.stTimeCreate.wMinute,
														&stProductCodeInfo.stTimeCreate.wSecond);

	// 수정 시간
	GetPrivateProfileString(szSection, _T("TIME_MODIFY"), _T(""), szStringBuf, MAX_STRVALUE_L, strFileName);
	_stscanf_s(szStringBuf, _T("%d-%d-%d,%d:%d:%d"),	&stProductCodeInfo.stTimeModify.wYear,
														&stProductCodeInfo.stTimeModify.wMonth,
														&stProductCodeInfo.stTimeModify.wDay,
														&stProductCodeInfo.stTimeModify.wHour,
														&stProductCodeInfo.stTimeModify.wMinute,
														&stProductCodeInfo.stTimeModify.wSecond);

	// 모델명
	_stprintf_s(szKeyName, MAX_STRVALUE, _T("MODEL_NAME"));
	GetPrivateProfileString(szSection, szKeyName, _T(""), szStringBuf, MAX_STRVALUE_L, strFileName);
	if (_tcslen(szStringBuf) < MAX_STRINPUT_L)	_tcscpy_s(stProductCodeInfo.szModelName, MAX_STRINPUT_L, szStringBuf);
	else										bResult = FALSE;

	// 제품 코드
	_stprintf_s(szKeyName, MAX_STRVALUE, _T("PRODUCT_CODE"));
	GetPrivateProfileString(szSection, szKeyName, _T(""), szStringBuf, MAX_STRVALUE_L, strFileName);
	if (_tcslen(szStringBuf) < MAX_STRINPUT_S)	_tcscpy_s(stProductCodeInfo.szProductCode, MAX_STRINPUT_S, szStringBuf);
	else										bResult = FALSE;

	// 작업 정보
	_stprintf_s(szKeyName, MAX_STRVALUE, _T("IS_WORK_COMPLETE"));
	GetPrivateProfileString(szSection, szKeyName, _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
	stProductCodeInfo.bIsWorkComplete = _ttoi(szStringBuf);


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// 제품 코드 파일 삭제 ////////////////////////////////////////////////////////
BOOL CMainApp::DeleteProductCodeFile(const CString& strProductCode, UINT nDIR_ID)
{
	BOOL		bResult			= TRUE;
	CString		strFileName		= _T("");
	CFileFind	fileFinder;


	/////////////////////////////////////////////////////////////////
	// 파일 이름 설정 ///////////////////////////////////////////////
	strFileName.Format(_T("%s\\%s.INF"), m_SystemConfig.GetWorkDirectory(nDIR_ID), strProductCode);


	/////////////////////////////////////////////////////////////////
	// 파일 삭제 ////////////////////////////////////////////////////
	if (fileFinder.FindFile(strFileName)) {

		bResult = DeleteFile(strFileName);
		fileFinder.Close();
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// 정보 파일 정리 /////////////////////////////////////////////////////////////
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
	// 파일 검색 ////////////////////////////////////////////////////
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
				
						// 마지막 수정일자를 기준으로 차일 계산
						timeSpan = timeCurrent - fileStatus.m_mtime;							

						// 제한 일수보다 적으면 삭제 안함
						if (timeSpan.GetDays() <= nDayLimit)
							bOnDelete = FALSE;
					//}
				}

				// 바코드 파일 제거
				if (bOnDelete)	DeleteFile(strFileName);
			}
		}

		fileFinder.Close();
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// 라벨 포맷 생성 /////////////////////////////////////////////////////////////
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
	// 시리얼 번호 설정 /////////////////////////////////////////////
	if (nCustomSerialNo == 0)	nSerialNo = stProductionInfo.nCountProduction - stProductionInfo.nCountNG;
	else						nSerialNo = nCustomSerialNo;


	/////////////////////////////////////////////////////////////////
	// 기본 라벨 오프셋 설정 ////////////////////////////////////////
	nBasisOffsetX = (INT)(stLabelPrintInfo.ptOffsetBasis.x * stLabelPrintInfo.nDotPerMillimeter);
	nBasisOffsetY = (INT)(stLabelPrintInfo.ptOffsetBasis.y * stLabelPrintInfo.nDotPerMillimeter);


	/////////////////////////////////////////////////////////////////
	// 헤더 /////////////////////////////////////////////////////////
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
	// 사용자 정의 포맷 설정 ////////////////////////////////////////
	strLabelData.AppendFormat(_T("^XA"));
	for (UINT nIndex = 0; nIndex < MAX_BCP_USER_FORMAT_USE; nIndex++) {
	
		if (pstUserFormat[nIndex].bUseFormat) {

			/////////////////////////////////////////////////////////
			// 기본 정보 설정 ///////////////////////////////////////
			nOffsetX		= nBasisOffsetX + (INT)(pstUserFormat[nIndex].ptOffset.x * stLabelPrintInfo.nDotPerMillimeter);
			nOffsetY		= nBasisOffsetY + (INT)(pstUserFormat[nIndex].ptOffset.y * stLabelPrintInfo.nDotPerMillimeter);
			bIsSkipFormat	= FALSE;


			/////////////////////////////////////////////////////////
			// 출력 방향 설정 ///////////////////////////////////////
			switch (pstUserFormat[nIndex].nOrientation) {
			
				case	BCP_ORI_NORMAL		:	chOrientation = TEXT('N');	break;
				case	BCP_ORI_ROTATE_90	:	chOrientation = TEXT('R');	break;
				case	BCP_ORI_ROTATE_180	:	chOrientation = TEXT('I');	break;
				case	BCP_ORI_ROTATE_270	:	chOrientation = TEXT('B');	break;
			}


			/////////////////////////////////////////////////////////
			// 필드 데이터 설정 /////////////////////////////////////
			strFieldData = pstUserFormat[nIndex].szFieldData;

			// 필드 형식 #1 (LOT DATE + SERIAL NO)
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

			// 필드 형식 #2 (LOT DATE)
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

			// 필드 형식 #3 (SERIAL NO 3-DIGIT)
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

			// 필드 형식 #4 (SERIAL NO 4-DIGIT)
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

			// 필드 형식 #5 (제품 누적 수량)
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

			// 리턴값 설정
			if (pStrRetValue != NULL && nRetIndex == nIndex)
				*pStrRetValue = strFieldData;


			/////////////////////////////////////////////////////////
			// 포맷 형식 별 설정 ////////////////////////////////////
			if (!bIsSkipFormat) {

				switch (pstUserFormat[nIndex].nTypeFormat) {
			
					/////////////////////////////////////////////////
					// 그래픽 ///////////////////////////////////////
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
					// 이미지 ///////////////////////////////////////
					case	BCP_UFI_TYPE_I	:
							{
								BCP_IMAGE_T		stObjectInfo = GetPrintImages(pstUserFormat[nIndex].nImageID);

								strLabelData.AppendFormat(_T("^FS^FO%d,%d"), (nOffsetX < 0 ? 0 : nOffsetX), (nOffsetY < 0 ? 0 : nOffsetY));
								strLabelData.AppendFormat(_T("^IM%s.BMP^FS"), DPS_GetFileInfo(stObjectInfo.szFontName).szFileName);
								strLabelData.AppendFormat(_T("^IL%s.BMP"), DPS_GetFileInfo(stObjectInfo.szFontName).szFileName);
							}

							break;

					/////////////////////////////////////////////////
					// 바코드 ///////////////////////////////////////
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
					// 텍스트 ///////////////////////////////////////
					case	BCP_UFI_TYPE_T	:
							{
								strLabelData.AppendFormat(_T("^FS^FO%d,%d"), (nOffsetX < 0 ? 0 : nOffsetX), (nOffsetY < 0 ? 0 : nOffsetY));
								strLabelData.AppendFormat(_T("^A%c%c,%d,%d"), pstUserFormat[nIndex].chFontName, chOrientation, pstUserFormat[nIndex].stFontSize.x, pstUserFormat[nIndex].stFontSize.y);
								strLabelData.AppendFormat(_T("^FD%s"), strFieldData);
							}

							break;

					/////////////////////////////////////////////////
					// 코드 /////////////////////////////////////////
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
	// 테일 /////////////////////////////////////////////////////////
	strLabelData.AppendFormat(_T("^FS"));
	strLabelData.AppendFormat(_T("^PQ%d"), nPrintQuantity);
	strLabelData.AppendFormat(_T("^FS"));
	strLabelData.AppendFormat(_T("^XZ"));


	/////////////////////////////////////////////////////////////////
	// 라벨 포맷 저장 ///////////////////////////////////////////////
	m_strLabelFormat[nBCP_NO].Empty();
	m_strLabelFormat[nBCP_NO] = strLabelData;


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// 라벨 프린터 그래픽 로드 ////////////////////////////////////////////////////
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
	// 초기화 ///////////////////////////////////////////////////////
	m_arrBCPGraphicList.RemoveAll();


	/////////////////////////////////////////////////////////////////
	// Zebra 그래픽 파일 검색 ///////////////////////////////////////
	strFileName.Format(_T("%s\\*.%s"), m_SystemConfig.GetWorkDirectory(DIR_BCP_OBJECTS), BCP_GRF_EXTENSION);
	bIsFile	= fileFinder.FindFile(strFileName);
	if (!bIsFile)	return	nNumGraphics;

	while (bIsFile) {

		bIsFile			= fileFinder.FindNextFile();
		strFileName		= fileFinder.GetFileName();
		strFilePath		= fileFinder.GetFilePath();
		
		// 파일 정보 로드
		CFile::GetStatus(strFilePath, fileStatus);
		if (fileStatus.m_size > 0) {
		
			ZeroMemory(&stGraphicInfo, sizeof(BCP_GRAPHIC_T));
			_tcscpy_s(stGraphicInfo.szFontName, MAX_STRINPUT_S, strFileName);
			m_arrBCPGraphicList.Add(stGraphicInfo);
			nNumGraphics++;

			NormalMessage(FALSE, _T("Loading Printer Graphics = %s"), stGraphicInfo.szFontName);
		}
	}

	// 파일 파인더 닫기
	fileFinder.Close();


	/////////////////////////////////////////////////////////////////
	// 그래픽 폰트 개수 설정 ////////////////////////////////////////
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
										
		// 그래픽 파일 이름 설정
		strFileName.Empty();
		strFileName.Format(_T("%s\\%s"), m_SystemConfig.GetWorkDirectory(DIR_BCP_OBJECTS), GetPrintGraphics(nIndex).szFontName);

		// 파일 열기
		if (bResult = filePrinter.Open(strFileName, CFile::modeRead)) {

			// 파일 로드
			strBuffer.Empty();
			while (filePrinter.ReadString(strRead))
				strBuffer += strRead;

			filePrinter.Close();

			// 프린터 데이터 전송
			m_Comm[COMM_PRINT_1 + nBCP_NO].TransmitString(FALSE, strBuffer);
			DPS_Delay_ms(BCP_DELAY_SETUP);
		
		} else break;
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// 라벨 프린터 이미지 로드 ////////////////////////////////////////////////////
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
	// 초기화 ///////////////////////////////////////////////////////
	m_arrBCPImageList.RemoveAll();


	/////////////////////////////////////////////////////////////////
	// Zebra 이미지 파일 검색 ///////////////////////////////////////
	strFileName.Format(_T("%s\\*.%s"), m_SystemConfig.GetWorkDirectory(DIR_BCP_OBJECTS), BCP_IMG_EXTENSION);
	bIsFile	= fileFinder.FindFile(strFileName);
	if (!bIsFile)	return	nNumImages;

	while (bIsFile) {

		bIsFile			= fileFinder.FindNextFile();
		strFileName		= fileFinder.GetFileName();
		strFilePath		= fileFinder.GetFilePath();
		
		// 파일 정보 로드
		CFile::GetStatus(strFilePath, fileStatus);
		if (fileStatus.m_size > 0) {
		
			ZeroMemory(&stImageInfo, sizeof(BCP_IMAGE_T));
			_tcscpy_s(stImageInfo.szFontName, MAX_STRINPUT_S, strFileName);
			m_arrBCPImageList.Add(stImageInfo);
			nNumImages++;

			NormalMessage(FALSE, _T("Loading Printer Images = %s"), stImageInfo.szFontName);
		}
	}

	// 파일 파인더 닫기
	fileFinder.Close();


	/////////////////////////////////////////////////////////////////
	// 그래픽 폰트 개수 설정 ////////////////////////////////////////
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
	// 버퍼 생성 ////////////////////////////////////////////////////
	pBuffer = new (std::nothrow) BYTE[MAX_BCP_IMAGE_BUFFER];
	if (pBuffer == NULL)	return	bResult;


	/////////////////////////////////////////////////////////////////
	// 이미지 로드 //////////////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < m_stSystemStatus.nPrintNumImages; nIndex++) {
										
		// 그래픽 파일 이름 설정
		strFileName.Empty();
		strFileName.Format(_T("%s\\%s"), m_SystemConfig.GetWorkDirectory(DIR_BCP_OBJECTS), GetPrintImages(nIndex).szFontName);

		// 파일 열기
		if (bResult = filePrinter.Open(strFileName, CFile::modeRead)) {

			// 파일 로드
			ZeroMemory(pBuffer, MAX_BCP_IMAGE_BUFFER);
			CFile::GetStatus(strFileName, fileStatus);
			filePrinter.Read(pBuffer, MAX_BCP_IMAGE_BUFFER);
			filePrinter.Close();

			// 프린터 데이터 전송
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
// 작업 프로시저 //////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 검사 프로시저 로드 /////////////////////////////////////////////////////////
BOOL CMainApp::LoadTestProcedure(void)
{
	PMODEL_PROFILE_T	pstModelProfile	= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
	BOOL				bResult			= FALSE;


	/////////////////////////////////////////////////////////////////
	// 프로시저 데이터 제거 /////////////////////////////////////////
	if (m_pstTestProcedureData != NULL)	{
		
		delete [] m_pstTestProcedureData;
		m_pstTestProcedureData = NULL;
	}


	/////////////////////////////////////////////////////////////////
	// 프로시저 로드 ////////////////////////////////////////////////
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
	// 체크 /////////////////////////////////////////////////////////
	if (strProcedureFile.IsEmpty() || !fileFinder.FindFile(strProcedureFile))	
		return	FALSE;


	/////////////////////////////////////////////////////////////////
	// 프로시저 파일 로드 ///////////////////////////////////////////
	fileRecord.SetFileName(strProcedureFile);
	
	// 헤더 로드
	if (bResult = fileRecord.ReadHeader(&stHeader, sizeof(TPRD_HEADER_T))) {

		nReadCount = stHeader.nNumProcedureData;

		// 프로시저 데이터 생성
		if (pstData != NULL) {

			(*pstData) = new (std::nothrow) TPRD_DATA_T[nReadCount];
			if ((*pstData) != NULL) {
		
				// 데이터 로드 (10개씩 로드)
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
// 검사 프로시저 저장 /////////////////////////////////////////////////////////
BOOL CMainApp::SaveTestProcedure(const CString& strProcedureFile, TPRD_HEADER_T& stHeader, PTPRD_DATA_T pstData /* = NULL */)
{
	BOOL			bResult		= FALSE;
	INT				nRetCode	= 0;
	UINT			nOffset		= 0;
	UINT			nWriteCount	= 0;
	CDpsFileRecord	fileRecord;


	/////////////////////////////////////////////////////////////////
	// 고유 코드 설정 ///////////////////////////////////////////////
	_tcscpy_s(stHeader.szUniqueCode, MAX_STRINPUT_L, _TPRD_UNIQUE_CODE);


	/////////////////////////////////////////////////////////////////
	// 프로시저 파일 저장 ///////////////////////////////////////////
	fileRecord.SetFileName(strProcedureFile);

	do {

		// 헤더 저장
		if (bResult = fileRecord.WriteHeader(&stHeader, sizeof(TPRD_HEADER_T))) {
		
			if (pstData != NULL) {

				// 데이터 저장 (10개씩 저장)
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

			nRetCode = m_MessageBox.Message(MB_RETRYCANCEL | MB_ICONERROR, _T("파일 저장 오류!"), _T("프로시저 파일 저장 중 오류가 발생했습니다."));
		}

	} while (!bResult && nRetCode == IDRETRY);


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// 비전 프로시저 로드 /////////////////////////////////////////////////////////
BOOL CMainApp::LoadVisionProcedure(UINT nTestItemNo)
{
	PMODEL_PROFILE_T	pstModelProfile	= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
	BOOL				bResult			= FALSE;


	/////////////////////////////////////////////////////////////////
	// 프로시저 데이터 제거 /////////////////////////////////////////
	if (m_pstVisionProcedureData != NULL)	{
		
		delete [] m_pstVisionProcedureData;
		m_pstVisionProcedureData = NULL;
	}


	/////////////////////////////////////////////////////////////////
	// 프로시저 로드 ////////////////////////////////////////////////
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
	// 체크 /////////////////////////////////////////////////////////
	if (strProcedureFile.IsEmpty() || !fileFinder.FindFile(strProcedureFile))	
		return	FALSE;


	/////////////////////////////////////////////////////////////////
	// 프로시저 파일 로드 ///////////////////////////////////////////
	fileRecord.SetFileName(strProcedureFile);
	
	// 헤더 로드
	if (bResult = fileRecord.ReadHeader(&stHeader, sizeof(VPRD_HEADER_T))) {

		nReadCount = stHeader.nNumProcedureData;

		// 프로시저 데이터 생성
		if (pstData != NULL) {

			(*pstData) = new (std::nothrow) VPRD_DATA_T[nReadCount];
			if ((*pstData) != NULL) {
		
				// 데이터 로드 (10개씩 로드)
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
// 비전 프로시저 저장 /////////////////////////////////////////////////////////
BOOL CMainApp::SaveVisionProcedure(const CString& strProcedureFile, VPRD_HEADER_T& stHeader, PVPRD_DATA_T pstData /* = NULL */)
{
	BOOL			bResult		= FALSE;
	INT				nRetCode	= 0;
	UINT			nOffset		= 0;
	UINT			nWriteCount	= 0;
	CDpsFileRecord	fileRecord;


	/////////////////////////////////////////////////////////////////
	// 고유 코드 설정 ///////////////////////////////////////////////
	_tcscpy_s(stHeader.szUniqueCode, MAX_STRINPUT_L, _VPRD_UNIQUE_CODE);


	/////////////////////////////////////////////////////////////////
	// 프로시저 파일 저장 ///////////////////////////////////////////
	fileRecord.SetFileName(strProcedureFile);

	do {

		// 헤더 저장
		if (bResult = fileRecord.WriteHeader(&stHeader, sizeof(VPRD_HEADER_T))) {
		
			if (pstData != NULL) {

				// 데이터 저장 (10개씩 저장)
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

			nRetCode = m_MessageBox.Message(MB_RETRYCANCEL | MB_ICONERROR, _T("파일 저장 오류!"), _T("프로시저 파일 저장 중 오류가 발생했습니다."));
		}

	} while (!bResult && nRetCode == IDRETRY);


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// CAN 메세지 프로세스 : 검증 /////////////////////////////////////////////////
BOOL CMainApp::TPRD_CAN_MSG_VERIFY_Process(PCAN_PACKET_T& stPacket, TPRD_CAN_MSG_T& stCAN_MSG)
{
	BOOL		bResult		= TRUE;
	BYTE		byDATA		= 0;


	/////////////////////////////////////////////////////////////////
	// 데이터 비교 //////////////////////////////////////////////////
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
// CAN 메세지 프로세스 ////////////////////////////////////////////////////////
BOOL CMainApp::TPRD_CAN_MSG_Process(TPRD_CAN_MSG_T& stCAN_MSG)
{
	USES_CONVERSION;

	BOOL		bResult		= TRUE;
	CString		strData		= _T("");
	SYSTEMTIME	stTimeCurrent;


	/////////////////////////////////////////////////////////////////
	// 초기화 ///////////////////////////////////////////////////////
	ZeroMemory(stCAN_MSG.abData, sizeof(BYTE) * MAX_CAN_MSG_BYTE);
	ZeroMemory(stCAN_MSG.abDataMask, sizeof(BYTE) * MAX_CAN_MSG_BYTE);
	GetLocalTime(&stTimeCurrent);


	/////////////////////////////////////////////////////////////////
	// CAN 데이터 ///////////////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_CAN_MSG_BYTE; nIndex++) {
	
		// 데이터 예약어 체크
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

		// HEX 변환
		stCAN_MSG.abData[nIndex] = (BYTE)DPS_HexToDec(W2A(stCAN_MSG.szData[nIndex]));
	}


	/////////////////////////////////////////////////////////////////
	// CAN 마스크 ///////////////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_CAN_MSG_BYTE; nIndex++) {

		// HEX 변환
		stCAN_MSG.abDataMask[nIndex] = (BYTE)DPS_HexToDec(W2A(stCAN_MSG.szDataMask[nIndex]));
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// CAN 메세지 프로세스 : 보안 엑세스 //////////////////////////////////////////
BOOL CMainApp::TPRD_CAN_MSG_SECURITY_Process(PCAN_PACKET_T& stPacket, TPRD_CAN_MSG_T& stCAN_MSG, UINT& nSecurityCode)
{
	USES_CONVERSION;

	BOOL		bResult		= TRUE;
	CString		strData		= _T("");


	/////////////////////////////////////////////////////////////////
	// 송신 모드 ////////////////////////////////////////////////////
	if (stCAN_MSG.nTypeMessage == CAN_MSG_TYPE_TX) {
	
		// SECURITY-KEY 삽입
// 		for (UINT nIndex = 0; nIndex < MPUSBCAN_MAX_CAN_BYTE; nIndex++) {
// 	
// 			// 데이터 예약어 체크
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
	// 수신 모드 ////////////////////////////////////////////////////
	if (stCAN_MSG.nTypeMessage == CAN_MSG_TYPE_RX) {
	
		// SEED-KEY 삽입
// 		for (UINT nIndex = 0; nIndex < MPUSBCAN_MAX_CAN_BYTE; nIndex++) {
// 	
// 			// 데이터 예약어 체크
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
// CAN 메세지 프로세스 : 데이터 ///////////////////////////////////////////////
BOOL CMainApp::TPRD_CAN_MSG_DATA_Process(PCAN_PACKET_T& stPacket, TPRD_CAN_MSG_T& stCAN_MSG, PBYTE pData, UINT& nLength)
{
	USES_CONVERSION;

	BOOL		bResult		= TRUE;
	BOOL		bOnData		= FALSE;
	CString		strData		= _T("");


	/////////////////////////////////////////////////////////////////
	// 초기화 ///////////////////////////////////////////////////////
	if (pData != NULL)	ZeroMemory(pData, nLength);
	nLength = 0;


	/////////////////////////////////////////////////////////////////
	// 송신 모드 ////////////////////////////////////////////////////
	if (stCAN_MSG.nTypeMessage == CAN_MSG_TYPE_TX) {

		// Not yet
	}


	/////////////////////////////////////////////////////////////////
	// 수신 모드 ////////////////////////////////////////////////////
	if (stCAN_MSG.nTypeMessage == CAN_MSG_TYPE_RX) {

		for (UINT nIndex = 0; nIndex < MAX_CAN_MSG_BYTE; nIndex++) {
	
			// 데이터 예약어 체크
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
// CAN 통신 정보 //////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 통신 정보 초기화 ///////////////////////////////////////////////////////////
void CMainApp::CAN_InitInformation(void)
{
	/////////////////////////////////////////////////////////////////
	// 플래그 초기화 ////////////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_CAN_MESSAGE; nIndex++)
		m_stSystemStatus.bCAN_EnableTransmitData[nIndex] = FALSE;


	/////////////////////////////////////////////////////////////////
	// 송신 데이터 초기화 ///////////////////////////////////////////
	ZeroMemory(m_stCAN_TransmitData, sizeof(CAN_MSG_DATA_INFO_T) * MAX_CAN_MESSAGE);
	for (UINT nIndex = 0; nIndex < MAX_CAN_MESSAGE; nIndex++) {
	
		m_stCAN_TransmitData[nIndex].nCAN_ID = g_stCAN_MsgInfo_ID[nIndex].nID;
		m_stCAN_TransmitData[nIndex].nLength = MAX_CAN_MSG_BYTE;
		m_stCAN_TransmitData[nIndex].nType	 = PCAN_MESSAGE_STANDARD;
	}


	/////////////////////////////////////////////////////////////////
	// 시그널 데이터 초기화 /////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_CAN_SIGNAL_LIST; nIndex++)
		m_strCAN_MsgSignalValue[nIndex].Empty();
}


///////////////////////////////////////////////////////////////////////////////
// 시그널 데이터 초기화 ///////////////////////////////////////////////////////
void CMainApp::CAN_ClearSignalValue(void)
{
	/////////////////////////////////////////////////////////////////
	// 데이터 초기화 ////////////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < MAX_CAN_SIGNAL_LIST; nIndex++)
		m_strCAN_MsgSignalValue[nIndex].Empty();


	/////////////////////////////////////////////////////////////////
	// 업데이트 /////////////////////////////////////////////////////
	CAN_UpdateSignalValue();
}


///////////////////////////////////////////////////////////////////////////////
// 시그널 데이터 업데이트 /////////////////////////////////////////////////////
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
// 모션 컨트롤러 //////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 모션 컨트롤러 레지스터 초기화 //////////////////////////////////////////////
void CMainApp::Motion_Initialize(void)
{
	/////////////////////////////////////////////////////////////////
	// 공통 설정 ////////////////////////////////////////////////////
	for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++) {

		// 서보 OFF
		AxmSignalSetServoOnLevel(nAxisNo, HIGH);
		AxmSignalServoOn(nAxisNo, DISABLE);
		AxmMoveEStop(nAxisNo);

		// 1 펄스당 0.01mm 이동 
		AxmMotSetMoveUnitPerPulse(nAxisNo, m_stMotionAxisInfo[nAxisNo].dblResolution, 1);

		// 기본 속도 설정
		AxmMotSetMinVel(nAxisNo, 1.0);
		AxmMotSetMaxVel(nAxisNo, m_stMotionAxisInfo[nAxisNo].dblSpeedMAX);
		AxmMotSetAccelUnit(nAxisNo, SEC);

		// COMMAND 펄스 출력 방식 (모터 회전 방향)
		AxmMotSetPulseOutMethod(nAxisNo, m_stMotionAxisInfo[nAxisNo].nPulseDirection == MAI_PULSE_DIR_CCWCW ? TwoCcwCwHigh : TwoCwCcwHigh);

		// 엔코더 펄스 입력형식
		AxmMotSetEncInputMethod(nAxisNo, m_stMotionAxisInfo[nAxisNo].nEncoderDirection == MAI_ENC_DIR_SQR4MODE ? ObverseSqr4Mode : ReverseSqr4Mode);

		// 소프트웨어 리미트 셋팅 (급정지)
		AxmSignalSetSoftLimit(nAxisNo, DISABLE, EMERGENCY_STOP, COMMAND, m_stMotionAxisInfo[nAxisNo].dblLimitPositivePos, m_stMotionAxisInfo[nAxisNo].dblLimitNegativePos);

		// 리미트 센서 액티브 레벨
		AxmSignalSetLimit(nAxisNo,	EMERGENCY_STOP, 
									m_stMotionAxisInfo[nAxisNo].nSensorLevelPLimit == MAI_ACT_LV_HIGH ? HIGH : (m_stMotionAxisInfo[nAxisNo].nSensorLevelPLimit == MAI_ACT_LV_LOW ? LOW : UNUSED), 
									m_stMotionAxisInfo[nAxisNo].nSensorLevelNLimit == MAI_ACT_LV_HIGH ? HIGH : (m_stMotionAxisInfo[nAxisNo].nSensorLevelNLimit == MAI_ACT_LV_LOW ? LOW : UNUSED)), 

		// 홈 센서 액티브 레벨
		AxmHomeSetSignalLevel(nAxisNo, m_stMotionAxisInfo[nAxisNo].nHomeSensorLogic == MAI_ACT_LV_HIGH ? HIGH : LOW);	

		// Z-Phase 액티브 레벨
		AxmSignalSetZphaseLevel(nAxisNo, HIGH);		

		// 인포지션 액티브 레벨
		AxmSignalSetInpos(nAxisNo, HIGH);		

		// 서보 알람 액티브 레벨
		AxmSignalSetServoAlarm(nAxisNo, m_stMotionAxisInfo[nAxisNo].nSensorLevelAlarm == MAI_ACT_LV_HIGH ? HIGH : (m_stMotionAxisInfo[nAxisNo].nSensorLevelAlarm == MAI_ACT_LV_LOW ? LOW : UNUSED));		

		// EMG-STOP 액티브 레벨
		AxmSignalSetStop(nAxisNo, EMERGENCY_STOP, UNUSED);					

		// 위치 카운터 초기화
		AxmStatusSetCmdPos(nAxisNo, 0);
		AxmStatusSetActPos(nAxisNo, 0);

		// 범용 출력 해제
		AxmSignalWriteOutputBit(nAxisNo, UIO_OUT2, DISABLE);
		AxmSignalWriteOutputBit(nAxisNo, UIO_OUT3, DISABLE);
		AxmSignalWriteOutputBit(nAxisNo, UIO_OUT4, DISABLE);
		AxmSignalWriteOutputBit(nAxisNo, UIO_OUT5, DISABLE);

		// 기타
		AxmMotSetAbsRelMode(nAxisNo, POS_REL_MODE);
		AxmMotSetProfileMode(nAxisNo, SYM_S_CURVE_MODE);
	}


	/////////////////////////////////////////////////////////////////
	// 개별 설정 ////////////////////////////////////////////////////
}


///////////////////////////////////////////////////////////////////////////////
// 모션 축 정보 저장 //////////////////////////////////////////////////////////
BOOL CMainApp::SaveMotionAxisInfo(BOOL bBinary /* = TRUE */)
{	
	CString		strFileName		= _T("");
	BOOL		bFileResult		= TRUE;
	


	/////////////////////////////////////////////////////////////////
	// 바이너리 저장 ////////////////////////////////////////////////
	if (bBinary) {

		UINT	nRetryCount	= 0;
		CFile	fileWrite;

		TRY {

			/////////////////////////////////////////////////////////
			// 파일 이름 설정 ///////////////////////////////////////
			strFileName.Format(_T("%s\\%s"), DPS_GetCurrentAppDirectory(), _BFILE_MOTION_AXIS_INFO);


			/////////////////////////////////////////////////////////
			// 파일 저장 ////////////////////////////////////////////
			while (TRUE) {

				if (bFileResult = fileWrite.Open(strFileName, CFile::modeCreate | CFile::modeWrite)) {

					for (UINT nIndex = 0; nIndex < MAX_MOTION_AXIS; nIndex++)
						fileWrite.Write(&m_stMotionAxisInfo[nIndex], sizeof(DPS_MOTION_AXIS_INFO_T));

					fileWrite.Close();
				}

				// 성공이거나 재시도 횟수가 오버되면, 종료
				if (bFileResult || ++nRetryCount >= MAX_RETRY_COUNT)
					break;
			}

		} CATCH (CFileException, e) {
			e->ReportError();
		} END_CATCH


	/////////////////////////////////////////////////////////////////
	// 텍스트 저장 //////////////////////////////////////////////////
	} else {
	
		TCHAR	szSection[MAX_STRVALUE];
		TCHAR	szValue[MAX_STRVALUE];
		TCHAR	szKeyName[MAX_STRVALUE];


		/////////////////////////////////////////////////////////////
		// 파일 이름 설정 ///////////////////////////////////////////
		strFileName.Format(_T("%s\\%s"), DPS_GetCurrentAppDirectory(), _TFILE_MOTION_AXIS_INFO);


		/////////////////////////////////////////////////////////////
		// 축 별로 저장 /////////////////////////////////////////////
		for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++) {
		
			// 섹션
			ZeroMemory(szSection, MAX_STRVALUE);
			_stprintf_s(szSection, MAX_STRVALUE, _T("AXIS %02d"), nAxisNo + 1);

			// 펄스 출력 방향
			_stprintf_s(szValue, MAX_STRVALUE, _T("%d"), m_stMotionAxisInfo[nAxisNo].nPulseDirection);
			WritePrivateProfileString(szSection, _T("PULSE_DIRECTION"), szValue, strFileName);

			// 엔코어 입력
			_stprintf_s(szValue, MAX_STRVALUE, _T("%d"), m_stMotionAxisInfo[nAxisNo].nEncoderDirection);
			WritePrivateProfileString(szSection, _T("ENCODER_DIRECTION"), szValue, strFileName);

			// 홈 센서 논리
			_stprintf_s(szValue, MAX_STRVALUE, _T("%d"), m_stMotionAxisInfo[nAxisNo].nHomeSensorLogic);
			WritePrivateProfileString(szSection, _T("HOME_SENSOR_LOGIC"), szValue, strFileName);

			// 센서 레벨 : P-LIMIT
			_stprintf_s(szValue, MAX_STRVALUE, _T("%d"), m_stMotionAxisInfo[nAxisNo].nSensorLevelPLimit);
			WritePrivateProfileString(szSection, _T("SENSOR_LEVEL_PLIMIT"), szValue, strFileName);

			// 센서 레벨 : N-LIMIT
			_stprintf_s(szValue, MAX_STRVALUE, _T("%d"), m_stMotionAxisInfo[nAxisNo].nSensorLevelNLimit);
			WritePrivateProfileString(szSection, _T("SENSOR_LEVEL_NLIMIT"), szValue, strFileName);

			// 센서 레벨 : 알람
			_stprintf_s(szValue, MAX_STRVALUE, _T("%d"), m_stMotionAxisInfo[nAxisNo].nSensorLevelAlarm);
			WritePrivateProfileString(szSection, _T("SENSOR_LEVEL_ALARM"), szValue, strFileName);

			// 제어 분해도
			_stprintf_s(szValue, MAX_STRVALUE, _T("%.12f"), m_stMotionAxisInfo[nAxisNo].dblResolution);
			WritePrivateProfileString(szSection, _T("RESOLUTION"), szValue, strFileName);

			// 소프트웨어 리미트
			_stprintf_s(szValue, MAX_STRVALUE, _T("%.2f"), m_stMotionAxisInfo[nAxisNo].dblLimitPositivePos);
			WritePrivateProfileString(szSection, _T("SOFT_LIMIT_POSITIVE"), szValue, strFileName);
			_stprintf_s(szValue, MAX_STRVALUE, _T("%.2f"), m_stMotionAxisInfo[nAxisNo].dblLimitNegativePos);
			WritePrivateProfileString(szSection, _T("SOFT_LIMIT_NEGATIVE"), szValue, strFileName);

			// 속도
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

			// 가감속 시간
			_stprintf_s(szValue, MAX_STRVALUE, _T("%.2f"), m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration);
			WritePrivateProfileString(szSection, _T("TIME_ACCELERATION"), szValue, strFileName);
			_stprintf_s(szValue, MAX_STRVALUE, _T("%.2f"), m_stMotionAxisInfo[nAxisNo].dblTimeAccelerationJog);
			WritePrivateProfileString(szSection, _T("TIME_ACCELERATION_JOG"), szValue, strFileName);

			// 안전 위치
			_stprintf_s(szValue, MAX_STRVALUE, _T("%.2f"), m_stMotionAxisInfo[nAxisNo].dblSafePositionMIN);
			WritePrivateProfileString(szSection, _T("POSITION_SAFE_MIN"), szValue, strFileName);
			_stprintf_s(szValue, MAX_STRVALUE, _T("%.2f"), m_stMotionAxisInfo[nAxisNo].dblSafePositionMAX);
			WritePrivateProfileString(szSection, _T("POSITION_SAFE_MAX"), szValue, strFileName);

			// 커스텀 위치
			for (UINT nIndex = 0; nIndex < MAX_MAI_CUSTOM_POSITION; nIndex++) {
			
				_stprintf_s(szKeyName, MAX_STRVALUE, _T("POSITION_CUSTOM_%02d"), nIndex + 1);
				_stprintf_s(szValue, MAX_STRVALUE, _T("%.2f"), m_stMotionAxisInfo[nAxisNo].dblCustomPosition[nIndex]);
				WritePrivateProfileString(szSection, szKeyName, szValue, strFileName);
			}
		}
	}


	/////////////////////////////////////////////////////////////////
	// 메세지 출력 //////////////////////////////////////////////////
	if (!bFileResult) {

		if (m_nTypeLanguage == LANGUAGE_KOR)	SErrorMessage(FALSE, _T("모션 축 정보를 저장할 수 없습니다."));
		else									SErrorMessage(FALSE, _T("Can NOT Save Motion Axis Information"));
	}


	return	bFileResult;
}


///////////////////////////////////////////////////////////////////////////////
// 모션 축 정보 로드 //////////////////////////////////////////////////////////
BOOL CMainApp::LoadMotionAxisInfo(BOOL bBinary /* = TRUE */)
{
	CString		strFileName		= _T("");
	BOOL		bFileResult		= TRUE;
	


	/////////////////////////////////////////////////////////////////
	// 바이너리 로드 ////////////////////////////////////////////////
	if (bBinary) {

		UINT	nRetryCount		= 0;
		UINT	nReadCount		= 0;
		CFile	fileRead;


		TRY {

			/////////////////////////////////////////////////////////
			// 파일 이름 설정 ///////////////////////////////////////
			strFileName.Format(_T("%s\\%s"), DPS_GetCurrentAppDirectory(), _BFILE_MOTION_AXIS_INFO);


			/////////////////////////////////////////////////////////
			// 파일 읽기 ////////////////////////////////////////////
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

				// 성공이거나 재시도 횟수가 오버되면, 종료
				if (bFileResult || ++nRetryCount >= MAX_RETRY_COUNT)
					break;
			}

		} CATCH (CFileException, e) {
			e->ReportError();
		} END_CATCH
	
	
	/////////////////////////////////////////////////////////////////
	// 텍스트 로드 //////////////////////////////////////////////////
	} else {
	
		TCHAR	szSection[MAX_STRVALUE];
		TCHAR	szStringBuf[MAX_STRVALUE_L];
		TCHAR	szKeyName[MAX_STRVALUE];


		/////////////////////////////////////////////////////////////
		// 파일 이름 설정 ///////////////////////////////////////////
		strFileName.Format(_T("%s\\%s"), DPS_GetCurrentAppDirectory(), _TFILE_MOTION_AXIS_INFO);


		/////////////////////////////////////////////////////////////
		// 축 별로 저장 /////////////////////////////////////////////
		for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++) {

			// 섹션
			ZeroMemory(szSection, MAX_STRVALUE);
			_stprintf_s(szSection, MAX_STRVALUE, _T("AXIS %02d"), nAxisNo + 1);

			// 펄스 출력 방향
			GetPrivateProfileString(szSection, _T("PULSE_DIRECTION"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].nPulseDirection		= _ttoi(szStringBuf);

			// 엔코더 입력
			GetPrivateProfileString(szSection, _T("ENCODER_DIRECTION"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].nEncoderDirection	= _ttoi(szStringBuf);
			 
			// 홈 센서 논리
			GetPrivateProfileString(szSection, _T("HOME_SENSOR_LOGIC"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].nHomeSensorLogic	= _ttoi(szStringBuf);

			// 센서 레벨 : P-LIMIT
			GetPrivateProfileString(szSection, _T("SENSOR_LEVEL_PLIMIT"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].nSensorLevelPLimit	= _ttoi(szStringBuf);

			// 센서 레벨 : N-LIMIT
			GetPrivateProfileString(szSection, _T("SENSOR_LEVEL_NLIMIT"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].nSensorLevelNLimit	= _ttoi(szStringBuf);

			// 센서 레벨 : 알람
			GetPrivateProfileString(szSection, _T("SENSOR_LEVEL_ALARM"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].nSensorLevelAlarm	= _ttoi(szStringBuf);

			// 제어 분해도
			GetPrivateProfileString(szSection, _T("RESOLUTION"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].dblResolution		= _ttof(szStringBuf);

			// 소프트웨어 리미트
			GetPrivateProfileString(szSection, _T("SOFT_LIMIT_POSITIVE"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].dblLimitPositivePos	= _ttof(szStringBuf);
			GetPrivateProfileString(szSection, _T("SOFT_LIMIT_NEGATIVE"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].dblLimitNegativePos	= _ttof(szStringBuf);

			// 속도
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

			// 가감속 시간
			GetPrivateProfileString(szSection, _T("TIME_ACCELERATION"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration		= _ttof(szStringBuf);
			GetPrivateProfileString(szSection, _T("TIME_ACCELERATION_JOG"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].dblTimeAccelerationJog	= _ttof(szStringBuf);

			// 안전 위치
			GetPrivateProfileString(szSection, _T("POSITION_SAFE_MIN"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].dblSafePositionMIN		= _ttof(szStringBuf);
			GetPrivateProfileString(szSection, _T("POSITION_SAFE_MAX"), _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
			m_stMotionAxisInfo[nAxisNo].dblSafePositionMAX		= _ttof(szStringBuf);

			// 커스텀 위치
			for (UINT nIndex = 0; nIndex < MAX_MAI_CUSTOM_POSITION; nIndex++) {
			
				_stprintf_s(szKeyName, MAX_STRVALUE, _T("POSITION_CUSTOM_%02d"), nIndex + 1);
				GetPrivateProfileString(szSection, szKeyName, _T("0"), szStringBuf, MAX_STRVALUE_L, strFileName);
				m_stMotionAxisInfo[nAxisNo].dblCustomPosition[nIndex]	= _ttof(szStringBuf);
			}
		}
	}


	/////////////////////////////////////////////////////////////////
	// 메세지 출력 //////////////////////////////////////////////////
	if (!bFileResult) {

		if (m_nTypeLanguage == LANGUAGE_KOR)	SErrorMessage(FALSE, _T("모션 축 정보를 로드할 수 없습니다."));
		else									SErrorMessage(FALSE, _T("Can NOT Load Motion Axis Information"));
	}


	return	bFileResult;
}


///////////////////////////////////////////////////////////////////////////////
// 모션 이동 : 상대 좌표 //////////////////////////////////////////////////////
BOOL CMainApp::Motion_Move(UINT nAxisNo, DOUBLE dblDistance, DOUBLE dblSpeed, BOOL bOnMessage /* = TRUE */)
{
	if (dblDistance != 0) {

		DWORD	dwRetCode	= 0;


		// 속도 설정
		dblSpeed = __min(dblSpeed, m_stMotionAxisInfo[nAxisNo].dblSpeedMAX);

		// 모션 이동
		AxmMotSetAbsRelMode(nAxisNo, POS_REL_MODE);
		AxmMotSetProfileMode(nAxisNo, SYM_TRAPEZOIDE_MODE);
		dwRetCode = AxmMoveStartPos(nAxisNo, dblDistance, dblSpeed, m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration, m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration);
		if (dwRetCode != AXT_RT_SUCCESS)	NormalMessage(TRUE, _T("Move::AxmMoveStartPos() Failure! RetCode = %d (%08X)"), dwRetCode, dwRetCode);

		// 메세지 출력
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

		// 속도 설정
		dblSpeed = __min(dblSpeed, m_stMotionAxisInfo[nAxisNo].dblSpeedMAX);

		// 모션 이동
		AxmMotSetAbsRelMode(nAxisNo, POS_REL_MODE);
		AxmMotSetProfileMode(nAxisNo, ASYM_S_CURVE_MODE);
		dwRetCode = AxmMoveStartPos(nAxisNo, dblDistance, dblSpeed, dblAccel, dblDecel);
		if (dwRetCode != AXT_RT_SUCCESS)	NormalMessage(TRUE, _T("MoveEx::AxmMoveStartPos() Failure! RetCode = %d (%08X)"), dwRetCode, dwRetCode);

		// 메세지 출력
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
// 모션 이동 : 절대 좌표 //////////////////////////////////////////////////////
BOOL CMainApp::Motion_MoveTo(UINT nAxisNo, DOUBLE dblPosition, DOUBLE dblSpeed, BOOL bOnMessage /* = TRUE */)
{
	DWORD	dwRetCode	= 0;

	// 속도 설정
	dblSpeed = __min(dblSpeed, m_stMotionAxisInfo[nAxisNo].dblSpeedMAX);

	// 모션 이동
	AxmMotSetAbsRelMode(nAxisNo, POS_ABS_MODE);
	AxmMotSetProfileMode(nAxisNo, SYM_TRAPEZOIDE_MODE);
	dwRetCode = AxmMoveStartPos(nAxisNo, dblPosition, dblSpeed, m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration, m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration);
	if (dwRetCode != AXT_RT_SUCCESS)	NormalMessage(TRUE, _T("MoveTo::AxmMoveStartPos() Failure! RetCode = %d (%08X)"), dwRetCode, dwRetCode);

	// 메세지 출력
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
// 모션 이동 : 속도 이동 //////////////////////////////////////////////////////
BOOL CMainApp::Motion_MoveVel(UINT nAxisNo, DOUBLE dblSpeed, DOUBLE dblAccelTime, UINT nDirection)
{
	// 속도 설정
	dblSpeed = __min(dblSpeed, m_stMotionAxisInfo[nAxisNo].dblSpeedMAX);
	if (nDirection == MOTION_CCW)	dblSpeed *= -1.0;

	// 모션 이동
	AxmMoveVel(nAxisNo, dblSpeed, dblAccelTime, dblAccelTime);

	return	TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// 모션 이동 : 2축 직선 보간 이동 /////////////////////////////////////////////
BOOL CMainApp::Motion_Move2X(LONG lCoord, UINT nAxisNo1, UINT nAxisNo2, DOUBLE dblPos1, DOUBLE dblPos2, DOUBLE dblSpeed, BOOL bOnMessage /* = TRUE */)
{
	LONG	lMapAxis[2];
	DOUBLE	dblPosition[2];
	DOUBLE	dblAccelTime	= 0;
	DWORD	dwStatus		= 0;
	BOOL	bSoftMode		= FALSE;
	BOOL	bResult			= FALSE;


	/////////////////////////////////////////////////////////////////
	// 모션 위치 설정 ///////////////////////////////////////////////
	lMapAxis[0]		= nAxisNo1;
	lMapAxis[1]		= nAxisNo2;

	dblPosition[0]	= dblPos1;
	dblPosition[1]	= dblPos2;


	/////////////////////////////////////////////////////////////////
	// 모션 속도 및 가속 시간 설정 //////////////////////////////////
	dblSpeed		= __min(dblSpeed, m_stMotionAxisInfo[lMapAxis[0]].dblSpeedMAX);
	dblSpeed		= __min(dblSpeed, m_stMotionAxisInfo[lMapAxis[1]].dblSpeedMAX);
	dblAccelTime	= __max(m_stMotionAxisInfo[lMapAxis[0]].dblTimeAcceleration, m_stMotionAxisInfo[lMapAxis[1]].dblTimeAcceleration);


	/////////////////////////////////////////////////////////////////
	// 모션 파라미터 설정 ///////////////////////////////////////////
	AxmContiWriteClear(lCoord);
	AxmContiSetAxisMap(lCoord, 2, lMapAxis);
	AxmContiSetProfileMode(lCoord, SYM_S_CURVE_MODE);
	AxmContiSetAbsRelMode(lCoord, POS_ABS_MODE);


	/////////////////////////////////////////////////////////////////
	// 리미트 체크 //////////////////////////////////////////////////
	BOOL	bEnableSoftLimit		= FALSE;
	DOUBLE	dblSoftLimitNegative	= 0;
	DOUBLE	dblSoftLimitPositive	= 0;
	DOUBLE	dblCurrentPosition		= 0;

	for (UINT nIndex = 0; nIndex < 2; nIndex++) {

		// 하드웨어 리미트 체크
		dwStatus = 0;
		AxmStatusReadMechanical(lMapAxis[nIndex], &dwStatus);

		if (dwStatus & 0x00000001)	bSoftMode = TRUE;		// + 리미트
		if (dwStatus & 0x00000002)	bSoftMode = TRUE;		// - 리미트

		// 소프트웨어 리미트 체크
		bEnableSoftLimit = Motion_GetSoftLimit(lMapAxis[nIndex], dblSoftLimitNegative, dblSoftLimitPositive);
		if (bEnableSoftLimit) {

			AxmStatusGetCmdPos(lMapAxis[nIndex], &dblCurrentPosition);
			MessageWindow(cDEBUG, _T("Move2X::SoftLimitNeg = %.2f, SoftLimitPos = %.2f, CurrPos = %.2f"), dblSoftLimitNegative, dblSoftLimitPositive, dblCurrentPosition);
			if (dblCurrentPosition <= dblSoftLimitNegative || dblCurrentPosition >= dblSoftLimitPositive)
				bSoftMode = TRUE;
		}
	}


	/////////////////////////////////////////////////////////////////
	// 모션 이동 ////////////////////////////////////////////////////
	if (bSoftMode) {

		// 일반 이동
		Motion_MoveTo(lMapAxis[0], dblPos1, m_stMotionAxisInfo[lMapAxis[0]].dblSpeedBase);
		Motion_MoveTo(lMapAxis[1], dblPos2, m_stMotionAxisInfo[lMapAxis[1]].dblSpeedBase);
		bOnMessage = FALSE;

	} else {

		// 하드웨어 보간을 사용하여 이동 : 보간 축에 리미트 센서가 걸려있으면, 하드웨어 보간이 지원되지 않음
		AxmContiBeginNode(lCoord);
		AxmLineMove(lCoord, dblPosition, dblSpeed, dblAccelTime, dblAccelTime);
		AxmContiEndNode(lCoord);

		DWORD	dwRetCode = AxmContiStart(lCoord, CONTI_NODE_VELOCITY, 0);
		MessageWindow(cDEBUG, _T("Move2X::AxmContiStart result = %d"), dwRetCode);

		// 보간 이동 실패 시 일반 이동
		if (dwRetCode != AXT_RT_SUCCESS) {
		
			NormalMessage(TRUE, _T("Move2X::AxmContiStart() Failure! RetCode = %d"), dwRetCode);
			Motion_MoveTo(lMapAxis[0], dblPos1, dblSpeed);
			Motion_MoveTo(lMapAxis[1], dblPos2, dblSpeed);
			bOnMessage = FALSE;
		}
	}


	/////////////////////////////////////////////////////////////////
	// 메세지 출력 //////////////////////////////////////////////////
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
// 모션 이동 : 3축 직선 보간 이동 /////////////////////////////////////////////
BOOL CMainApp::Motion_Move3X(LONG lCoord, UINT nAxisNo1, UINT nAxisNo2, UINT nAxisNo3, DOUBLE dblPos1, DOUBLE dblPos2, DOUBLE dblPos3, DOUBLE dblSpeed, BOOL bOnMessage /* = TRUE */)
{
	LONG	lMapAxis[3];
	DOUBLE	dblPosition[3];
	DOUBLE	dblAccelTime	= 0;
	DWORD	dwStatus		= 0;
	BOOL	bSoftMode		= FALSE;
	BOOL	bResult			= FALSE;


	/////////////////////////////////////////////////////////////////
	// 모션 위치 설정 ///////////////////////////////////////////////
	lMapAxis[0]		= nAxisNo1;
	lMapAxis[1]		= nAxisNo2;
	lMapAxis[2]		= nAxisNo3;

	dblPosition[0]	= dblPos1;
	dblPosition[1]	= dblPos2;
	dblPosition[2]	= dblPos3;


	/////////////////////////////////////////////////////////////////
	// 모션 속도 및 가속 시간 설정 //////////////////////////////////
	dblSpeed		= __min(dblSpeed, m_stMotionAxisInfo[lMapAxis[0]].dblSpeedMAX);
	dblSpeed		= __min(dblSpeed, m_stMotionAxisInfo[lMapAxis[1]].dblSpeedMAX);
	dblSpeed		= __min(dblSpeed, m_stMotionAxisInfo[lMapAxis[2]].dblSpeedMAX);
	dblAccelTime	= __max(m_stMotionAxisInfo[lMapAxis[0]].dblTimeAcceleration, m_stMotionAxisInfo[lMapAxis[1]].dblTimeAcceleration);
	dblAccelTime	= __max(dblAccelTime, m_stMotionAxisInfo[lMapAxis[2]].dblTimeAcceleration);


	/////////////////////////////////////////////////////////////////
	// 모션 파라미터 설정 ///////////////////////////////////////////
	AxmContiWriteClear(lCoord);
	AxmContiSetAxisMap(lCoord, 3, lMapAxis);
	AxmContiSetProfileMode(lCoord, SYM_S_CURVE_MODE);
	AxmContiSetAbsRelMode(lCoord, POS_ABS_MODE);


	/////////////////////////////////////////////////////////////////
	// 리미트 체크 //////////////////////////////////////////////////
	BOOL	bEnableSoftLimit		= FALSE;
	DOUBLE	dblSoftLimitNegative	= 0;
	DOUBLE	dblSoftLimitPositive	= 0;
	DOUBLE	dblCurrentPosition		= 0;

	for (UINT nIndex = 0; nIndex < 3; nIndex++) {

		// 하드웨어 리미트 체크
		dwStatus = 0;
		AxmStatusReadMechanical(lMapAxis[nIndex], &dwStatus);

		if (dwStatus & 0x00000001)	bSoftMode = TRUE;		// + 리미트
		if (dwStatus & 0x00000002)	bSoftMode = TRUE;		// - 리미트

		// 소프트웨어 리미트 체크
		bEnableSoftLimit = Motion_GetSoftLimit(lMapAxis[nIndex], dblSoftLimitNegative, dblSoftLimitPositive);
		if (bEnableSoftLimit) {

			AxmStatusGetCmdPos(lMapAxis[nIndex], &dblCurrentPosition);
			MessageWindow(cDEBUG, _T("Move3X::SoftLimitNeg = %.2f, SoftLimitPos = %.2f, CurrPos = %.2f"), dblSoftLimitNegative, dblSoftLimitPositive, dblCurrentPosition);
			if (dblCurrentPosition <= dblSoftLimitNegative || dblCurrentPosition >= dblSoftLimitPositive)
				bSoftMode = TRUE;
		}
	}


	/////////////////////////////////////////////////////////////////
	// 모션 이동 ////////////////////////////////////////////////////
	if (bSoftMode) {

		// 일반 이동
		Motion_MoveTo(lMapAxis[0], dblPos1, m_stMotionAxisInfo[lMapAxis[0]].dblSpeedBase);
		Motion_MoveTo(lMapAxis[1], dblPos2, m_stMotionAxisInfo[lMapAxis[1]].dblSpeedBase);
		Motion_MoveTo(lMapAxis[2], dblPos3, m_stMotionAxisInfo[lMapAxis[2]].dblSpeedBase);
		bOnMessage = FALSE;

	} else {

		// 하드웨어 보간을 사용하여 이동 : 보간 축에 리미트 센서가 걸려있으면, 하드웨어 보간이 지원되지 않음
		AxmContiBeginNode(lCoord);
		AxmLineMove(lCoord, dblPosition, dblSpeed, dblAccelTime, dblAccelTime);
		AxmContiEndNode(lCoord);

		DWORD	dwRetCode = AxmContiStart(lCoord, CONTI_NODE_VELOCITY, 0);
		MessageWindow(cDEBUG, _T("Move3X::AxmContiStart result = %d"), dwRetCode);

		// 보간 이동 실패 시 일반 이동
		if (dwRetCode != AXT_RT_SUCCESS) {
		
			NormalMessage(TRUE, _T("Move3X:AxmContiStart() Failure! RetCode = %d"), dwRetCode);
			Motion_MoveTo(lMapAxis[0], dblPos1, dblSpeed);
			Motion_MoveTo(lMapAxis[1], dblPos2, dblSpeed);
			Motion_MoveTo(lMapAxis[2], dblPos3, dblSpeed);
			bOnMessage = FALSE;
		}
	}


	/////////////////////////////////////////////////////////////////
	// 메세지 출력 //////////////////////////////////////////////////
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
// 모션 이동 : 다축 직선 보간 이동 ////////////////////////////////////////////
BOOL CMainApp::Motion_MoveNX(LONG lCoord, UINT nNumAxis, UINT* pAxisNo, DOUBLE* pPosition, DOUBLE dblSpeed, BOOL bOnMessage /* = TRUE */)
{
	PLONG	pMapAxis		= NULL;
	DOUBLE*	pMapPosition	= NULL;
	DOUBLE	dblAccelTime	= 0;
	DWORD	dwStatus		= 0;
	BOOL	bSoftMode		= FALSE;
	BOOL	bResult			= FALSE;


	/////////////////////////////////////////////////////////////////
	// 파라미터 체크 ////////////////////////////////////////////////
	if (nNumAxis <= 1)		return	FALSE;
	if (dblSpeed <= 0)		return	FALSE;
	if (pAxisNo == NULL)	return	FALSE;
	if (pPosition == NULL)	return	FALSE;


	/////////////////////////////////////////////////////////////////
	// 매핑 변수 할당 ///////////////////////////////////////////////
	pMapAxis = new (std::nothrow) LONG[nNumAxis];
	if (pMapAxis == NULL)	return	FALSE;

	pMapPosition = new (std::nothrow) DOUBLE[nNumAxis];
	if (pMapPosition == NULL) {
	
		delete [] pMapAxis;
		return	FALSE;
	}	


	/////////////////////////////////////////////////////////////////
	// 모션 위치 설정 ///////////////////////////////////////////////
	for (UINT nIndex = 0; nIndex < nNumAxis; nIndex++) {
	
		pMapAxis[nIndex]		= pAxisNo[nIndex];
		pMapPosition[nIndex]	= pPosition[nIndex];
	}


	/////////////////////////////////////////////////////////////////
	// 모션 속도 및 가속 시간 설정 //////////////////////////////////
	for (UINT nIndex = 0; nIndex < nNumAxis; nIndex++)
		dblSpeed = __min(dblSpeed, m_stMotionAxisInfo[pMapAxis[nIndex]].dblSpeedMAX);

	dblAccelTime = __max(m_stMotionAxisInfo[pMapAxis[0]].dblTimeAcceleration, m_stMotionAxisInfo[pMapAxis[1]].dblTimeAcceleration);
	for (UINT nIndex = 2; nIndex < nNumAxis; nIndex++)
		dblAccelTime = __max(dblAccelTime, m_stMotionAxisInfo[pMapAxis[nIndex]].dblTimeAcceleration);


	/////////////////////////////////////////////////////////////////
	// 모션 파라미터 설정 ///////////////////////////////////////////
	AxmContiWriteClear(lCoord);
	AxmContiSetAxisMap(lCoord, nNumAxis, pMapAxis);
	AxmContiSetProfileMode(lCoord, SYM_S_CURVE_MODE);
	AxmContiSetAbsRelMode(lCoord, POS_ABS_MODE);


	/////////////////////////////////////////////////////////////////
	// 리미트 체크 //////////////////////////////////////////////////
	BOOL	bEnableSoftLimit		= FALSE;
	DOUBLE	dblSoftLimitNegative	= 0;
	DOUBLE	dblSoftLimitPositive	= 0;
	DOUBLE	dblCurrentPosition		= 0;

	for (UINT nIndex = 0; nIndex < nNumAxis; nIndex++) {

		// 하드웨어 리미트 체크
		dwStatus = 0;
		AxmStatusReadMechanical(pMapAxis[nIndex], &dwStatus);

		if (dwStatus & 0x00000001)	bSoftMode = TRUE;		// + 리미트
		if (dwStatus & 0x00000002)	bSoftMode = TRUE;		// - 리미트

		// 소프트웨어 리미트 체크
		bEnableSoftLimit = Motion_GetSoftLimit(pMapAxis[nIndex], dblSoftLimitNegative, dblSoftLimitPositive);
		if (bEnableSoftLimit) {

			AxmStatusGetCmdPos(pMapAxis[nIndex], &dblCurrentPosition);
			MessageWindow(cDEBUG, _T("MoveNX::SoftLimitNeg = %.2f, SoftLimitPos = %.2f, CurrPos = %.2f"), dblSoftLimitNegative, dblSoftLimitPositive, dblCurrentPosition);
			if (dblCurrentPosition <= dblSoftLimitNegative || dblCurrentPosition >= dblSoftLimitPositive)
				bSoftMode = TRUE;
		}
	}


	/////////////////////////////////////////////////////////////////
	// 모션 이동 ////////////////////////////////////////////////////
	if (bSoftMode) {

		// 일반 이동
		for (UINT nIndex = 0; nIndex < nNumAxis; nIndex++)
			Motion_MoveTo(pMapAxis[nIndex], pMapPosition[nIndex], m_stMotionAxisInfo[pMapAxis[nIndex]].dblSpeedBase);

		bOnMessage = FALSE;

	} else {

		// 하드웨어 보간을 사용하여 이동 : 보간 축에 리미트 센서가 걸려있으면, 하드웨어 보간이 지원되지 않음
		AxmContiBeginNode(lCoord);
		AxmLineMove(lCoord, pMapPosition, dblSpeed, dblAccelTime, dblAccelTime);
		AxmContiEndNode(lCoord);

		DWORD	dwRetCode = AxmContiStart(lCoord, CONTI_NODE_VELOCITY, 0);
		MessageWindow(cDEBUG, _T("MoveNX::AxmContiStart result = %d"), dwRetCode);

		// 보간 이동 실패 시 일반 이동
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
	// 메세지 출력 //////////////////////////////////////////////////
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
// 모션 이동 완료 체크 ////////////////////////////////////////////////////////
BOOL CMainApp::Motion_Done(UINT nAxisNo)
{
	DWORD	dwStatus = 0;

	// 모션 상태 체크
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
// 안전 위치 체크 /////////////////////////////////////////////////////////////
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
// 커스텀 위치 체크 ///////////////////////////////////////////////////////////
BOOL CMainApp::Motion_CheckCustomPosition(UINT nPosition)
{
	BOOL	bResult				= TRUE;
	DOUBLE	dblOffset			= 0;
	DOUBLE	dblMotorPosition	= 0;


	for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++) {

		AxmStatusGetCmdPos(nAxisNo, &dblMotorPosition);
		dblOffset	= dblMotorPosition - m_stMotionAxisInfo[nAxisNo].dblCustomPosition[nPosition];

		// 0.02mm 오차율 적용
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


	// 커맨드 위치
	AxmStatusGetCmdPos(nAxisNo, &dblMotorCmdPos);

	// 인코더 위치
	AxmStatusGetActPos(nAxisNo, &dblMotorActPos);

	// 오프셋
	dblOffset = dblMotorActPos - dblPosition;

	// 오차율 적용
	if (abs(dblOffset) > dblTolerance) {

		NormalMessage(TRUE, _T("Motion_CheckCustomPosition:: AxisNo = %d, dblPosition = %.2f, CommandPos = %.2f, ActualPos = %.2f, dblOffset = %.2f"), nAxisNo + 1, dblPosition, dblMotorCmdPos, dblMotorActPos, dblOffset);

		bResult = FALSE;
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// 인-포지션 체크 /////////////////////////////////////////////////////////////
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
// 정지 상태 체크 /////////////////////////////////////////////////////////////
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
	// 정지 상태 체크 ///////////////////////////////////////////////
	dwRetCode = AxmStatusReadStop(nAxisNo, &dwStatusEnd);
	
	if (pStatus)	*pStatus = dwStatusEnd;


	/////////////////////////////////////////////////////////////////
	// 위치 정밀도 체크 /////////////////////////////////////////////
	do {

		bResult = TRUE;

		// 위치 체크
		AxmStatusGetActPos(nAxisNo, &dblActPos);
		AxmStatusGetCmdPos(nAxisNo, &dblCmdPos);

		// 외부/내부 엔코더 체크
		dblOffsetEnc = dblActPos - dblCmdPos;
		//if (abs(dblOffsetEnc) > 5.0)	bResult = FALSE;

		// 목표 위치 체크
		dblOffsetPos = dblDestPosition - dblCmdPos;
		if (abs(dblOffsetPos) > 1.0)	bResult = FALSE;

	} while (!bResult && ++nRetryCount <= MAX_RETRY_DEVICE);


	/////////////////////////////////////////////////////////////////
	// 메세지 출력 //////////////////////////////////////////////////
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
// 소프트 리미트 설정 /////////////////////////////////////////////////////////
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
// 모션 시그널 이벤트 설정 ////////////////////////////////////////////////////
//																			 //
// nAxisNo    : 축 번호														 //
// nSignalNo  : 입력 시그널 번호 (0 ~ 4)									 //
// nTypeEdge  : 검출 엣지 설정 (SIGNAL_DOWN_EDGE, SIGNAL_UP_EDGE)			 //
// nTypeCount : 위치 카운터 설정 (0 = Command, 1 = Actual)					 //
///////////////////////////////////////////////////////////////////////////////
BOOL CMainApp::Motion_SignalEventPositionStart(UINT nAxisNo, UINT nSignalNo, UINT nTypeEdge, UINT nTypeCount)
{
	DWORD	dwEvent		= 0;
	DWORD	dwCommand	= 0;
	LONG	lAxisQI		= (LONG)nAxisNo % 4;


	/////////////////////////////////////////////////////////////////
	// 파라미터 체크 ////////////////////////////////////////////////
	if (nSignalNo > 4)				return	FALSE;
	if (nTypeEdge > SIGNAL_UP_EDGE)	return	FALSE;
	if (nTypeCount > 1)				return	FALSE;


	/////////////////////////////////////////////////////////////////
	// 이벤트 설정 //////////////////////////////////////////////////
	switch (nSignalNo) {
	
		case	0	:	dwEvent = nTypeEdge == SIGNAL_UP_EDGE ? EVENT_QIUIO5RISING : EVENT_QIUIO5FALLING;	break;
		case	1	:	dwEvent = nTypeEdge == SIGNAL_UP_EDGE ? EVENT_QIUIO6RISING : EVENT_QIUIO6FALLING;	break;
		case	2	:	dwEvent = nTypeEdge == SIGNAL_UP_EDGE ? EVENT_QIUIO7RISING : EVENT_QIUIO7FALLING;	break;
		case	3	:	dwEvent = nTypeEdge == SIGNAL_UP_EDGE ? EVENT_QIUIO8RISING : EVENT_QIUIO8FALLING;	break;
		case	4	:	dwEvent = nTypeEdge == SIGNAL_UP_EDGE ? EVENT_QIUIO9RISING : EVENT_QIUIO9FALLING;	break;
	}


	/////////////////////////////////////////////////////////////////
	// 커맨드 설정 //////////////////////////////////////////////////
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
// 모션 시그널 이벤트 취소 ////////////////////////////////////////////////////
BOOL CMainApp::Motion_SignalEventPositionStop(UINT nAxisNo)
{
	DWORD dwData;

	AxmGetCommandData32Qi(nAxisNo, QiCQ4Read, &dwData);
	AxmSetCommandData32Qi(nAxisNo, QiINITSQWrite, 0x0008);

	return	TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// 모션 시그널 이벤트 위치 읽기 ///////////////////////////////////////////////
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
// 모션 시그널 이벤트 상태 체크 ///////////////////////////////////////////////
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
// 비전 검사 정보 /////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// MIL 초기화 /////////////////////////////////////////////////////////////////
BOOL CMainApp::MatroxInitialize(void)
{
	SYSTEM_CONFIG_T	stSystemConfig	= m_SystemConfig.GetSystemConfig();
	BOOL			bResult			= TRUE;
	CFileFind		fileFinder;


	/////////////////////////////////////////////////////////////////
	// MIL 초기화 ///////////////////////////////////////////////////
	try {

		/////////////////////////////////////////////////////////////
		// 어플리케이션 초기화 //////////////////////////////////////
		MappAlloc(M_DEFAULT, &m_MilApplication);
		if (m_MilApplication == M_NULL)	throw -1;


		/////////////////////////////////////////////////////////////
		// 시스템 초기화 ////////////////////////////////////////////
		MsysAlloc(stSystemConfig.szVisionSystemName, M_DEF_SYSTEM_NUM, M_COMPLETE, &m_MilSystem);
		if (m_MilSystem == M_NULL)		throw -1;


		/////////////////////////////////////////////////////////////
		// 디지타이저 초기화 ////////////////////////////////////////
		CString		strFileDCF	= _T("");

		m_MilNumberOfDigitizer = MsysInquire(m_MilSystem, M_DIGITIZER_NUM, NULL);
		if (m_MilNumberOfDigitizer && m_MilNumberOfDigitizer >= MAX_VISION_CHANNEL) {

			for (UINT nDigIndex = 0; nDigIndex < MAX_VISION_CHANNEL; nDigIndex++) {

				// DCF 파일 설정
				if (fileFinder.FindFile(stSystemConfig.szVisionCameraDCF[nDigIndex]))	strFileDCF.Format(_T("%s"), stSystemConfig.szVisionCameraDCF[nDigIndex]);
				else																	strFileDCF = _T("M_DEFAULT");

				// 디지타이저 생성
				MdigAlloc(m_MilSystem, M_DEV0 + stSystemConfig.nVisionDigitizerNo + nDigIndex, (MIL_TEXT_CHAR*)(LPCTSTR)strFileDCF, M_DEFAULT, &m_MilDigitizer[nDigIndex]);
				if (m_MilDigitizer[nDigIndex] == NULL)	throw -1;

				MdigInquire(m_MilDigitizer[nDigIndex], M_SIZE_X, &m_sizeFrame[nDigIndex].cx);
				MdigInquire(m_MilDigitizer[nDigIndex], M_SIZE_Y, &m_sizeFrame[nDigIndex].cy);
				MdigInquire(m_MilDigitizer[nDigIndex], M_SIZE_BAND, &m_MilDigitizerNbBands);

				if (m_sizeFrame[nDigIndex].cx > M_DEF_IMAGE_SIZE_X_MAX)		m_sizeFrame[nDigIndex].cx	= M_DEF_IMAGE_SIZE_X_MAX;
				if (m_sizeFrame[nDigIndex].cy > M_DEF_IMAGE_SIZE_Y_MAX) 	m_sizeFrame[nDigIndex].cy	= M_DEF_IMAGE_SIZE_Y_MAX;
			}

		} else {

			if (m_nTypeLanguage == LANGUAGE_KOR)	SErrorMessage(FALSE, _T("매트록스 디지타이저를 생성할 수 없습니다."));
			else									SErrorMessage(FALSE, _T("Can NOT Create Matrox Digitizer"));

			m_MilDigitizer[VISION_CH1]	= M_NULL;

			m_sizeFrame[VISION_CH1].cx	= M_DEF_IMAGE_SIZE_X_MAX;
			m_sizeFrame[VISION_CH1].cy	= M_DEF_IMAGE_SIZE_Y_MAX;
		}


		/////////////////////////////////////////////////////////////
		// MIL 오류 메세지 활성화 ///////////////////////////////////
		MappControl(M_ERROR, stSystemConfig.bOnVisionMessageDisplay ? M_PRINT_ENABLE : M_PRINT_DISABLE);


	/////////////////////////////////////////////////////////////////
	// MIL 초기화 실패 //////////////////////////////////////////////
	} catch (...) {

		MatroxRelease();
		bResult = FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// 메세지 출력 //////////////////////////////////////////////////
	if (!bResult) {

		if (m_nTypeLanguage == LANGUAGE_KOR)	SErrorMessage(FALSE, _T("매트록스 이미지 라이브러리를 초기화할 수 없습니다."));
		else									SErrorMessage(FALSE, _T("Matrox Image Library Initialize Failure!!"));
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// MIL 릴리즈 /////////////////////////////////////////////////////////////////
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
// 비전 이미지 캡쳐 ///////////////////////////////////////////////////////////
BOOL CMainApp::GrabVisionImage(UINT nVisionCH, UINT nTestItemNo)
{
	BOOL	bResult		= FALSE;


	/////////////////////////////////////////////////////////////////
	// 크리티컬 섹션 설정 ///////////////////////////////////////////
	m_csDigitizerGrabImage[nVisionCH].Lock();


	/////////////////////////////////////////////////////////////////
	// 이미지 버퍼 초기화 //////////////////////////////////////
	if (m_MilImageGrab[nVisionCH] != M_NULL) {

		MbufFree(m_MilImageGrab[nVisionCH]);
		m_MilImageGrab[nVisionCH] = M_NULL;
	}

	if (m_MilImageInspection[nTestItemNo] != M_NULL) {

		MbufFree(m_MilImageInspection[nTestItemNo]);
		m_MilImageInspection[nTestItemNo] = M_NULL;
	}


	/////////////////////////////////////////////////////////////////
	// MIL 비디오 윈도우 이미지 캡쳐 ////////////////////////////////
	if (theApp.m_pMilVideoWnd[nVisionCH]) {

		if (theApp.m_pMilVideoWnd[nVisionCH]->TakeGrabImageBuffer(&m_MilImageGrab[nVisionCH])) {

			/////////////////////////////////////////////////////////
			// 검사 이미지 버퍼 생성 ////////////////////////////////
			MbufAllocColor(	m_MilSystem, 
							m_MilDigitizerNbBands, 
							m_sizeFrame[nVisionCH].cx, 
							m_sizeFrame[nVisionCH].cy, 
							(8 + M_UNSIGNED), 
							M_IMAGE + M_DISP + M_PROC, 
							&m_MilImageInspection[nTestItemNo]);


			/////////////////////////////////////////////////////////
			// 검사 이미지 버퍼에 저장 //////////////////////////////
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
	// 크리티컬 섹션 해제 ///////////////////////////////////////////
	m_csDigitizerGrabImage[nVisionCH].Unlock();


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// 비전 이미지 저장 ///////////////////////////////////////////////////////////
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
	// 디스크 용량 체크 /////////////////////////////////////////////
	if (DPS_GetDiskInfo(DPS_GetCurrentAppDirectory(), stDiskInfo)) {

		ULONGLONG	ulFreeSize_MB = stDiskInfo.ulDiskFreeSize / 1024 / 1024;

		// 디스크 용량이 100MB 미만이면,
		if (ulFreeSize_MB <= 100) {

			if (m_nTypeLanguage == LANGUAGE_KOR)	SErrorMessage(TRUE, _T("디스크 용량이 부족하여 비전 이미지를 저장할 수 없습니다. [남은 공간 = %luMB]"), ulFreeSize_MB);
			else									SErrorMessage(TRUE, _T("Disk is FULL!! Can NOT Save Vision Image [Free Space = %luMB]"), ulFreeSize_MB);

			return	FALSE;
		}
	
	} else {

		if (m_nTypeLanguage == LANGUAGE_KOR)	SErrorMessage(TRUE, _T("디스크 정보를 로드할 수 없습니다."));
		else									SErrorMessage(TRUE, _T("Can NOT Load Disk Information"));

		return	FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// 파일 이름 설정 ///////////////////////////////////////////////
	if (bIsCommon) {

		// 저장 디렉토리 설정
		strDirSave = m_SystemConfig.GetWorkDirectory(DIR_WORK_PROCEDURE);

		// 모델 디렉토리 생성
		strDirectory.Format(_T("%s\\%s"), strDirSave, DPS_GetFileInfo(stSystemConfig.szLastModelFile).szFileName);
		CreateDirectory(strDirectory, NULL);
	
	} else {

		strDirectory = pstWorkStatus->szWorkDataSaveDirectory;
	}

	// 파일 이름 설정
	strFileName.Format(_T("%s\\[T%02d] Inspection Image"), strDirectory, nTestItemNo + 1);

	// 파일 확장자 설정
	if (bIsJPEG)	strFileName.AppendFormat(_T(".JPG"));
	else			strFileName.AppendFormat(_T(".BMP"));


	/////////////////////////////////////////////////////////////////
	// 이미지 저장 //////////////////////////////////////////////////
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
// 비전 카메라 커맨드 : 파라미터 저장 /////////////////////////////////////////
BOOL CMainApp::SaveVisionCameraParameters(UINT nVisionCH, UINT nChannelNo)
{
	CComm*		pComm		= GetComm(COMM_DEV_CAM);
	BYTE		byReadByte	= 0;
	UINT		nCommIndex	= 0;
	TCHAR		szReadBuffer[COMM_PACKET_SIZE];
	LTimerMsec	LTimerTimeOut;


	/////////////////////////////////////////////////////////////////
	// 커맨드 전송 //////////////////////////////////////////////////
	while (pComm->ReadByte(&byReadByte));
	pComm->TransmitString(FALSE, _T("USERSET-SAVE %d\r"), nChannelNo);
	DPS_Delay_ms(2000);
	LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_VISION_CAMERA));


	/////////////////////////////////////////////////////////////////
	// 응답 수신 ////////////////////////////////////////////////////
	ZeroMemory(szReadBuffer, sizeof(TCHAR) * COMM_PACKET_SIZE);
	while (!LTimerTimeOut.Verify()) {

		while (pComm->ReadByte(&byReadByte)) {

			szReadBuffer[nCommIndex++]	= byReadByte;
			if (byReadByte == 0x0D) {

				// CR + LF 문자 제거
				szReadBuffer[nCommIndex - 1] = '\0';
				nCommIndex = 0;

				// 데이터 분석
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
// 비전 카메라 커맨드 : 파라미터 로드 /////////////////////////////////////////
BOOL CMainApp::LoadVisionCameraParameters(UINT nVisionCH, UINT nChannelNo)
{
	CComm*		pComm		= GetComm(COMM_DEV_CAM);
	BYTE		byReadByte	= 0;
	UINT		nCommIndex	= 0;
	TCHAR		szReadBuffer[COMM_PACKET_SIZE];
	LTimerMsec	LTimerTimeOut;


	/////////////////////////////////////////////////////////////////
	// 커맨드 전송 //////////////////////////////////////////////////
	while (pComm->ReadByte(&byReadByte));
	pComm->TransmitString(FALSE, _T("USERSET-LOAD %d\r"), nChannelNo);
	LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_VISION_CAMERA));


	/////////////////////////////////////////////////////////////////
	// 응답 수신 ////////////////////////////////////////////////////
	ZeroMemory(szReadBuffer, sizeof(TCHAR) * COMM_PACKET_SIZE);
	while (!LTimerTimeOut.Verify()) {

		while (pComm->ReadByte(&byReadByte)) {

			szReadBuffer[nCommIndex++]	= byReadByte;
			if (byReadByte == 0x0D) {

				// CR + LF 문자 제거
				szReadBuffer[nCommIndex - 1] = '\0';
				nCommIndex = 0;

				// 데이터 분석
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
// 비전 카메라 커맨드 : 자동 화이트 밸런스 ////////////////////////////////////
BOOL CMainApp::SetVisionCameraAutoWhiteBalance(UINT nVisionCH, UINT nValue)
{
	CComm*		pComm		= GetComm(COMM_DEV_CAM);
	BYTE		byReadByte	= 0;
	UINT		nCommIndex	= 0;
	TCHAR		szReadBuffer[COMM_PACKET_SIZE];
	LTimerMsec	LTimerTimeOut;


	/////////////////////////////////////////////////////////////////
	// 커맨드 전송 //////////////////////////////////////////////////
	while (pComm->ReadByte(&byReadByte));
	pComm->TransmitString(FALSE, _T("WHITEBALANCE-AUTO %d\r"), nValue);
	DPS_Delay_ms(2000);
	LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_VISION_CAMERA));


	/////////////////////////////////////////////////////////////////
	// 응답 수신 ////////////////////////////////////////////////////
	ZeroMemory(szReadBuffer, sizeof(TCHAR) * COMM_PACKET_SIZE);
	while (!LTimerTimeOut.Verify()) {

		while (pComm->ReadByte(&byReadByte)) {

			szReadBuffer[nCommIndex++]	= byReadByte;
			if (byReadByte == 0x0D) {

				// CR + LF 문자 제거
				szReadBuffer[nCommIndex - 1] = '\0';
				nCommIndex = 0;

				// 데이터 분석
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
// 비전 카메라 커맨드 : 노출 설정 /////////////////////////////////////////////
BOOL CMainApp::SetVisionCameraExposure(UINT nVisionCH, UINT nValue)
{
	BYTE	byReadByte;

	while (m_Comm[COMM_DEV_CAM].ReadByte(&byReadByte));
	m_Comm[COMM_DEV_CAM].TransmitString(FALSE, _T("EXP %d\r"), nValue);

	return	TRUE;
}


///////////////////////////////////////////////////////////////////////////////
// 이미지 프로세스 : THRESHOLD ////////////////////////////////////////////////
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
	// 초기화 ///////////////////////////////////////////////////////
	ZeroMemory(&stResult, sizeof(VI_RESULT_THRESHOLD_T));

	stResult.nResultInspection = T_RESULT_ERROR;


	/////////////////////////////////////////////////////////////////
	// 파라미터 로드 ////////////////////////////////////////////////
	rectInspectionRegion	= stParam.rectInspectionArea;


	/////////////////////////////////////////////////////////////////
	// 검사 이미지 버퍼 생성 ////////////////////////////////////////
	MbufChild2d(stParam.MilImageInspection, 
				rectInspectionRegion.ptTopLeft.x + (INT)stOriginOffset.dblX,
				rectInspectionRegion.ptTopLeft.y + (INT)stOriginOffset.dblY,
				rectInspectionRegion.sizeRect.cx,
				rectInspectionRegion.sizeRect.cy,
				&MilImageInspection);

	if (MilImageInspection == M_NULL)		bResultProcess = FALSE;


	/////////////////////////////////////////////////////////////////
	// 그레이 스케일 이미지 버퍼 생성 ///////////////////////////////
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
	// THRESHOLD 이미지 버퍼 생성 ///////////////////////////////////
	if (bResultProcess) {

		MbufAllocColor(m_MilSystem, MIL_BAND_GRAY, sizeImage.cx, sizeImage.cy, (8 + M_UNSIGNED), MilBufferAttributes, &MilImageThreshold);
		if (MilImageThreshold == M_NULL)	bResultProcess = FALSE;;
	}


	/////////////////////////////////////////////////////////////////
	// 이미지 변환 //////////////////////////////////////////////////
	if (bResultProcess) {

		// THRESHOLD 변환
		MbufClear(MilImageThreshold, M_NULL);
		CDpsMilImageWnd::ConvertBinarize(MilImageGrayScale, MilImageThreshold, stParam.stInspectionInfo.stThresholdInfo);

		// 이미지 반전
		if (stParam.stInspectionInfo.bInvertImage)	CDpsMilImageWnd::InvertImage(MilImageThreshold);

		// 미세 영역 제거
		CDpsMilImageWnd::RemoveParticles(MilImageThreshold, MilImageThreshold, stParam.stInspectionInfo.nParticleRadius, M_BINARY);
	}

	
	/////////////////////////////////////////////////////////////////
	// 히스토그램 생성 //////////////////////////////////////////////
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
	// 판정 /////////////////////////////////////////////////////////
	if (bResultProcess) {

		UINT	nNumberOfPixel		= 0;
		DOUBLE	dblWhitePixelRatio	= 0;

		// 검사 영역 전체 픽셀 수
		nNumberOfPixel = rectInspectionRegion.sizeRect.cx * rectInspectionRegion.sizeRect.cy;

		// 화이트 픽셀 비율
		if ((UINT)HistValues[DMW_HIST_WHITE] == 0)	dblWhitePixelRatio = 0;
		else										dblWhitePixelRatio = (DOUBLE)((DOUBLE)HistValues[DMW_HIST_WHITE] / nNumberOfPixel) * 100.0;

		// 판정
		stResult.nResultRatioWhitePixel = stParam.bUseReverseJudgement ? T_RESULT_SUCCESS : T_RESULT_FAILURE;
		if ((UINT)(dblWhitePixelRatio * 100) >= (UINT)(stParam.stInspectionInfo.dblRatioWhitePixelMIN * 100) &&
			(UINT)(dblWhitePixelRatio * 100) <= (UINT)(stParam.stInspectionInfo.dblRatioWhitePixelMAX * 100))	
				stResult.nResultRatioWhitePixel = stParam.bUseReverseJudgement ? T_RESULT_FAILURE : T_RESULT_SUCCESS;

		// 최종 판정
		nResultInspection = T_RESULT_SUCCESS;
		if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultRatioWhitePixel;

		// 결과 저장
		stResult.dblRatioWhitePixel	= dblWhitePixelRatio;
		stResult.nResultInspection	= nResultInspection;

		// 프로세스 시간
		dwTimeProcess = GetTickCount() - dwTimeProcess;

		// 디버그 메세지
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
	// 검사 이미지 저장 /////////////////////////////////////////////
	if (bSaveClip && bResultProcess && stResult.nResultInspection != T_RESULT_SUCCESS) {
	
		PMODEL_PROFILE_T		pstModelProfile		= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
		PVPRD_DATA_T			pstVisionSetupInfo	= &m_pstVisionProcedureData[m_stSystemStatus.nCurrentVisionInspectionNo];
		UINT					nInspectionNo		= 0;
		CString					strFileName			= _T("");
		CFileFind				fileFinder;

		// 파일 이름 설정
		strFileName.Format(_T("%s\\T%02d_%02d_%s_%s.JPG"),	pstWorkStatus->szWorkDataSaveDirectory, 
															nTestItemNo + 1,
															m_stSystemStatus.nCurrentVisionInspectionNo + 1,
															g_szTestResultEngS[stResult.nResultInspection],
															pstVisionSetupInfo->szName);

		// 이미지 파일 저장
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
	// MIL 버퍼 제거 ////////////////////////////////////////////////
	if (MilImageThreshold)		MbufFree(MilImageThreshold);
	if (MilImageGrayScale)		MbufFree(MilImageGrayScale);
	if (MilImageInspection)		MbufFree(MilImageInspection);
	if (MilHistResult)			MimFree(MilHistResult);


	return	bResultProcess;
}


///////////////////////////////////////////////////////////////////////////////
// 이미지 프로세스 : 길이 측정 (THRESHOLD) ////////////////////////////////////
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
	// 초기화 ///////////////////////////////////////////////////////
	ZeroMemory(&stResult, sizeof(VI_RESULT_THRESHOLD_T));

	stResult.nResultInspection = T_RESULT_ERROR;

	MilImageThreshold[VI_THL_P1]	= M_NULL;
	MilImageThreshold[VI_THL_P2]	= M_NULL;


	/////////////////////////////////////////////////////////////////
	// 파라미터 로드 ////////////////////////////////////////////////
	rectInspectionRegion[VI_THL_P1]	= stParam.rectInspectionArea[VI_THL_P1];
	rectInspectionRegion[VI_THL_P2]	= stParam.rectInspectionArea[VI_THL_P2];


	/////////////////////////////////////////////////////////////////
	// 1번 포인트 위치 검출 /////////////////////////////////////////
	{
		/////////////////////////////////////////////////////////////
		// 검사 이미지 버퍼 생성 ////////////////////////////////////
		MbufChild2d(stParam.MilImageInspection, 
					rectInspectionRegion[VI_THL_P1].ptTopLeft.x + (INT)stOriginOffset.dblX,
					rectInspectionRegion[VI_THL_P1].ptTopLeft.y + (INT)stOriginOffset.dblY,
					rectInspectionRegion[VI_THL_P1].sizeRect.cx,
					rectInspectionRegion[VI_THL_P1].sizeRect.cy,
					&MilImageInspection);

		if (MilImageInspection == M_NULL)		bResultProcess = FALSE;
	

		/////////////////////////////////////////////////////////////
		// 그레이 스케일 이미지 버퍼 생성 ///////////////////////////
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
		// THRESHOLD 이미지 버퍼 생성 ///////////////////////////////
		if (bResultProcess) {

			MbufAllocColor(m_MilSystem, MIL_BAND_GRAY, sizeImage.cx, sizeImage.cy, (8 + M_UNSIGNED), MilBufferAttributes, &MilImageThreshold[VI_THL_P1]);
			if (MilImageThreshold[VI_THL_P1] == M_NULL)		bResultProcess = FALSE;;
		}


		/////////////////////////////////////////////////////////////
		// 이미지 변환 //////////////////////////////////////////////
		if (bResultProcess) {

			// THRESHOLD 변환
			MbufClear(MilImageThreshold[VI_THL_P1], M_NULL);
			CDpsMilImageWnd::ConvertBinarize(MilImageGrayScale, MilImageThreshold[VI_THL_P1], stParam.stInspectionInfo.stThresholdInfo[VI_THL_P1]);

			// 이미지 반전
			if (stParam.stInspectionInfo.bInvertImage[VI_THL_P1])	CDpsMilImageWnd::InvertImage(MilImageThreshold[VI_THL_P1]);

			// 미세 영역 제거
			CDpsMilImageWnd::RemoveParticles(MilImageThreshold[VI_THL_P1], MilImageThreshold[VI_THL_P1], stParam.stInspectionInfo.nParticleRadius[VI_THL_P1], M_BINARY);
		}


		/////////////////////////////////////////////////////////////
		// BLOB 검출 ////////////////////////////////////////////////
		if (bResultProcess) {

			BOOL	bFoundBlob	= FALSE;
		
			// Blob Feature List 생성
			MblobAllocFeatureList(m_MilSystem, &MilBlobFeatureList);
			MblobSelectFeature(MilBlobFeatureList, M_BOX);

			// Blob 결과 버퍼 생성
			MblobAllocResult(m_MilSystem, &MilBlobResult); 

			// Blob 처리
			MblobCalculate(MilImageThreshold[VI_THL_P1], M_NULL, MilBlobFeatureList, MilBlobResult); 

			// Blob 개수 수집
			MblobGetNumber(MilBlobResult, &MilTotalBlobs); 

			// Blob 결과 수집 및 위치 정보 저장 (가장 큰 BLOB을 검출)
			if (MilTotalBlobs > 0) {

				// Blob 결과 수집
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

				// 위치 정보 저장
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

						// BLOB 크기 계산
						nBlobSizeX				= (INT)(MilPosX_MAX[nIndex] - MilPosX_MIN[nIndex]);
						nBlobSizeY				= (INT)(MilPosY_MAX[nIndex] - MilPosY_MIN[nIndex]);
						pAreaBlobSize[nIndex]	= nBlobSizeX * nBlobSizeY;

						//MessageWindow(cDEBUG, _T("blob size = %d * %d = %d"), nBlobSizeX, nBlobSizeY, pAreaBlobSize[nIndex]);

						// BLOB 크기 제한 (MIN)
						if (stParam.stInspectionInfo.stSizeLimitBlob_MIN.cx) {
						
							if (nBlobSizeX < stParam.stInspectionInfo.stSizeLimitBlob_MIN.cx)
								continue;
						}

						if (stParam.stInspectionInfo.stSizeLimitBlob_MIN.cy) {
						
							if (nBlobSizeY < stParam.stInspectionInfo.stSizeLimitBlob_MIN.cy)
								continue;
						}

						// BLOB 크기 제한 (MAX)
						if (stParam.stInspectionInfo.stSizeLimitBlob_MAX.cx) {
						
							if (nBlobSizeX > stParam.stInspectionInfo.stSizeLimitBlob_MAX.cx)
								continue;
						}

						if (stParam.stInspectionInfo.stSizeLimitBlob_MAX.cy) {
						
							if (nBlobSizeY > stParam.stInspectionInfo.stSizeLimitBlob_MAX.cy)
								continue;
						}

						// 측정 모드
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
										// 가장 작은 BLOB 검색
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
										// 가장 큰 BLOB 검색
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

			// 프로세스 결과 설정
			bResultProcess = (stParam.stInspectionInfo.nModeMeasurement < VISION_THL_MODE_2P_TB) ? TRUE : bFoundBlob;

			// Blob 영역 제거
			MblobFree(MilBlobResult); 
			MblobFree(MilBlobFeatureList);

			// 이미지 버퍼 제거
			if (MilImageGrayScale)		{ MbufFree(MilImageGrayScale);	MilImageGrayScale  = M_NULL; }
			if (MilImageInspection)		{ MbufFree(MilImageInspection); MilImageInspection = M_NULL; }
		}
	}


	/////////////////////////////////////////////////////////////////
	// 2번 포인트 위치 검출 /////////////////////////////////////////
	if (bResultProcess && stParam.stInspectionInfo.nModeMeasurement >= VISION_THL_MODE_2P_TB) {

		/////////////////////////////////////////////////////////////
		// 검사 이미지 버퍼 생성 ////////////////////////////////////
		MbufChild2d(stParam.MilImageInspection, 
					rectInspectionRegion[VI_THL_P2].ptTopLeft.x + (INT)stOriginOffset.dblX,
					rectInspectionRegion[VI_THL_P2].ptTopLeft.y + (INT)stOriginOffset.dblY,
					rectInspectionRegion[VI_THL_P2].sizeRect.cx,
					rectInspectionRegion[VI_THL_P2].sizeRect.cy,
					&MilImageInspection);

		if (MilImageInspection == M_NULL)		bResultProcess = FALSE;
	

		/////////////////////////////////////////////////////////////
		// 그레이 스케일 이미지 버퍼 생성 ///////////////////////////
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
		// THRESHOLD 이미지 버퍼 생성 ///////////////////////////////
		if (bResultProcess) {

			MbufAllocColor(m_MilSystem, MIL_BAND_GRAY, sizeImage.cx, sizeImage.cy, (8 + M_UNSIGNED), MilBufferAttributes, &MilImageThreshold[VI_THL_P2]);
			if (MilImageThreshold[VI_THL_P2] == M_NULL)		bResultProcess = FALSE;;
		}


		/////////////////////////////////////////////////////////////
		// 이미지 변환 //////////////////////////////////////////////
		if (bResultProcess) {

			// THRESHOLD 변환
			MbufClear(MilImageThreshold[VI_THL_P2], M_NULL);
			CDpsMilImageWnd::ConvertBinarize(MilImageGrayScale, MilImageThreshold[VI_THL_P2], stParam.stInspectionInfo.stThresholdInfo[VI_THL_P2]);

			// 이미지 반전
			if (stParam.stInspectionInfo.bInvertImage[VI_THL_P2])	CDpsMilImageWnd::InvertImage(MilImageThreshold[VI_THL_P2]);

			// 미세 영역 제거
			CDpsMilImageWnd::RemoveParticles(MilImageThreshold[VI_THL_P2], MilImageThreshold[VI_THL_P2], stParam.stInspectionInfo.nParticleRadius[VI_THL_P2], M_BINARY);
		}


		/////////////////////////////////////////////////////////////
		// BLOB 검출 ////////////////////////////////////////////////
		if (bResultProcess) {

			BOOL	bFoundBlob	= FALSE;
		
			// Blob Feature List 생성
			MblobAllocFeatureList(m_MilSystem, &MilBlobFeatureList);
			MblobSelectFeature(MilBlobFeatureList, M_BOX);

			// Blob 결과 버퍼 생성
			MblobAllocResult(m_MilSystem, &MilBlobResult); 

			// Blob 처리
			MblobCalculate(MilImageThreshold[VI_THL_P2], M_NULL, MilBlobFeatureList, MilBlobResult); 

			// Blob 개수 수집
			MblobGetNumber(MilBlobResult, &MilTotalBlobs); 

			// Blob 결과 수집 및 위치 정보 저장 (가장 큰 BLOB을 검출)
			if (MilTotalBlobs > 0) {

				// Blob 결과 수집
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

				// 위치 정보 저장
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

						// 가장 큰 BLOB 검색
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

			// 프로세스 결과 설정
			bResultProcess = bFoundBlob;

			// Blob 영역 제거
			MblobFree(MilBlobResult); 
			MblobFree(MilBlobFeatureList);

			// 이미지 버퍼 제거
			if (MilImageGrayScale)		{ MbufFree(MilImageGrayScale);	MilImageGrayScale  = M_NULL; }
			if (MilImageInspection)		{ MbufFree(MilImageInspection); MilImageInspection = M_NULL; }
		}
	}


	/////////////////////////////////////////////////////////////////
	// 판정 /////////////////////////////////////////////////////////
	if (bResultProcess) {

		DOUBLE	dblOriginPixelCount	= 0;
		DOUBLE	dblMeasurement		= 0;

		// 픽셀 수 계산
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

		// 판정
		dblMeasurement		= dblOriginPixelCount * stParam.dblGainLength;
		nResultInspection	= stParam.bUseReverseJudgement ? T_RESULT_SUCCESS : T_RESULT_FAILURE;
		if ((UINT)(dblMeasurement * 100) >= (UINT)(stParam.stInspectionInfo.dblLengthSpecMIN * 100) &&
			(UINT)(dblMeasurement * 100) <= (UINT)(stParam.stInspectionInfo.dblLengthSpecMAX * 100))	
				nResultInspection = stParam.bUseReverseJudgement ? T_RESULT_FAILURE : T_RESULT_SUCCESS;

		// 결과 저장
		stResult.dblMeasurement		= dblMeasurement;
		stResult.nResultInspection	= nResultInspection;

		// 프로세스 시간
		dwTimeProcess = GetTickCount() - dwTimeProcess;

		// 디버그 메세지
// 		MessageWindow(cDEBUG, _T("----------------------------------------------------------------------------------------------------"));
// 		MessageWindow(cDEBUG, _T("ProcessImage_ThresholdLength::stParam.stInspectionInfo.dblLengthSpecMIN=%.2f"), stParam.stInspectionInfo.dblLengthSpecMIN);
// 		MessageWindow(cDEBUG, _T("ProcessImage_ThresholdLength::stParam.stInspectionInfo.dblLengthSpecMAX=%.2f"), stParam.stInspectionInfo.dblLengthSpecMAX);
// 		MessageWindow(cDEBUG, _T("ProcessImage_ThresholdLength::dblOriginPixelCount=%.2f"), dblOriginPixelCount);
// 		MessageWindow(cDEBUG, _T("ProcessImage_ThresholdLength::dblMeasurement=%.2f"), dblMeasurement);
// 		MessageWindow(cDEBUG, _T("ProcessImage_ThresholdLength::dwTimeProcess=%d"), dwTimeProcess);
// 		MessageWindow(cDEBUG, _T("----------------------------------------------------------------------------------------------------"));
	}


	/////////////////////////////////////////////////////////////////
	// 검사 이미지 저장 /////////////////////////////////////////////
	if (bSaveClip && bResultProcess && stResult.nResultInspection != T_RESULT_SUCCESS) {
	
		PMODEL_PROFILE_T		pstModelProfile		= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
		PVPRD_DATA_T			pstVisionSetupInfo	= &m_pstVisionProcedureData[m_stSystemStatus.nCurrentVisionInspectionNo];
		UINT					nInspectionNo		= 0;
		CString					strFileName			= _T("");
		CFileFind				fileFinder;

		for (UINT nIndex = 0; nIndex < VI_THL_MAX_POINT; nIndex++) {

			// 파일 이름 설정
			strFileName.Format(_T("%s\\T%02d_%02d_%s_%s_P%d.JPG"),	pstWorkStatus->szWorkDataSaveDirectory,
																	nTestItemNo + 1,
																	m_stSystemStatus.nCurrentVisionInspectionNo + 1,
																	g_szTestResultEngS[stResult.nResultInspection],
																	pstVisionSetupInfo->szName,
																	nIndex + 1);

			// 이미지 파일 저장
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
	// MIL 버퍼 제거 ////////////////////////////////////////////////
	if (MilImageThreshold[VI_THL_P1])		MbufFree(MilImageThreshold[VI_THL_P1]);
	if (MilImageThreshold[VI_THL_P2])		MbufFree(MilImageThreshold[VI_THL_P2]);


	return	bResultProcess;
}


///////////////////////////////////////////////////////////////////////////////
// 이미지 프로세스 : 패턴 매칭 ////////////////////////////////////////////////
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
	// 초기화 ///////////////////////////////////////////////////////
	ZeroMemory(&stResult, sizeof(VI_RESULT_PATTERN_T));

	stResult.nResultInspection = T_RESULT_ERROR;


	/////////////////////////////////////////////////////////////////
	// 파라미터 로드 ////////////////////////////////////////////////
	rectInspectionRegion	= stParam.rectInspectionArea;


	/////////////////////////////////////////////////////////////////
	// 원본 이미지 로드 및 그레이 스케일 변경 ///////////////////////
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
	// 검사 이미지 그레이 스케일 변경 ///////////////////////////////
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
	// 원본 패턴 검색 영역 버퍼 생성 ////////////////////////////////
	if (bResultProcess) {

		// 이미지 정보 로드
		MbufInquire(MilImageGrayOrigin, M_SIZE_X, &sizeImage.cx);
		MbufInquire(MilImageGrayOrigin, M_SIZE_Y, &sizeImage.cy);

		// 검색 영역 설정 (검사 영역 + 검색 범위)
		rectRegionSearch.left		= __max((LONG)(rectInspectionRegion.ptTopLeft.x - (LONG)stParam.stInspectionInfo.nPatternSearchRange), 0);
		rectRegionSearch.top		= __max((LONG)(rectInspectionRegion.ptTopLeft.y - (LONG)stParam.stInspectionInfo.nPatternSearchRange), 0);
		rectRegionSearch.right		= __min((LONG)(rectInspectionRegion.ptTopLeft.x + rectInspectionRegion.sizeRect.cx + (LONG)stParam.stInspectionInfo.nPatternSearchRange), sizeImage.cx);
		rectRegionSearch.bottom		= __min((LONG)(rectInspectionRegion.ptTopLeft.y + rectInspectionRegion.sizeRect.cy + (LONG)stParam.stInspectionInfo.nPatternSearchRange), sizeImage.cy);

		// 패턴 영역 설정 (검색 영역 내의 상대 영역)
		rectRegionPattern.left		= rectInspectionRegion.ptTopLeft.x - rectRegionSearch.left;
		rectRegionPattern.top		= rectInspectionRegion.ptTopLeft.y - rectRegionSearch.top;
		rectRegionPattern.right		= rectRegionPattern.left + rectInspectionRegion.sizeRect.cx;
		rectRegionPattern.bottom	= rectRegionPattern.top  + rectInspectionRegion.sizeRect.cy;

		// 버퍼 생성
		MbufChild2d(MilImageGrayOrigin, 
					rectRegionSearch.left, 
					rectRegionSearch.top, 
					rectRegionSearch.Width(), 
					rectRegionSearch.Height(), 
					&MilImageOriginSearch);

		if (MilImageOriginSearch == M_NULL)		bResultProcess = FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// 대상 패턴 검색 영역 버퍼 생성 ////////////////////////////////
	if (bResultProcess) {

		// 검색 영역 설정 (검사 영역 + 검색 범위)
		// 홈 위치 검출 시 오프셋을 적용할 수 있음.
		rectRegionSearch.left		= __max((LONG)(rectInspectionRegion.ptTopLeft.x + (INT)stOriginOffset.dblX - (LONG)stParam.stInspectionInfo.nPatternSearchRange), 0);
		rectRegionSearch.top		= __max((LONG)(rectInspectionRegion.ptTopLeft.y + (INT)stOriginOffset.dblY - (LONG)stParam.stInspectionInfo.nPatternSearchRange), 0);
		rectRegionSearch.right		= __min((LONG)(rectInspectionRegion.ptTopLeft.x + (INT)stOriginOffset.dblX + rectInspectionRegion.sizeRect.cx + (LONG)stParam.stInspectionInfo.nPatternSearchRange), sizeImage.cx);
		rectRegionSearch.bottom		= __min((LONG)(rectInspectionRegion.ptTopLeft.y + (INT)stOriginOffset.dblY + rectInspectionRegion.sizeRect.cy + (LONG)stParam.stInspectionInfo.nPatternSearchRange), sizeImage.cy);

		// 버퍼 생성
		MbufChild2d(MilImageGrayInspection, 
					rectRegionSearch.left, 
					rectRegionSearch.top, 
					rectRegionSearch.Width(), 
					rectRegionSearch.Height(), 
					&MilImageInspection);

		if (MilImageInspection == M_NULL)		bResultProcess = FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// 패턴 검색 ////////////////////////////////////////////////////
	if (bResultProcess) {

		bResultProcess = FALSE;

		// 패턴 등록
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

			// 패턴 검색 속도 설정
			switch (stParam.stInspectionInfo.nSpeed) {
			
				case	VISION_PTN_SPEED_HIGH		:	nSpeed = M_HIGH;		break;
				case	VISION_PTN_SPEED_LOW		:	nSpeed = M_LOW;			break;
				case	VISION_PTN_SPEED_MEDIUM		:	nSpeed = M_MEDIUM;		break;
				case	VISION_PTN_SPEED_VERY_HIGH	:	nSpeed = M_VERY_HIGH;	break;
				case	VISION_PTN_SPEED_VERY_LOW	:	nSpeed = M_VERY_LOW;	break;
			}

			// 패턴 검색 정밀도 설정
			switch (stParam.stInspectionInfo.nAccuracy) {
			
				case	VISION_PTN_ACCURACY_HIGH	:	nAccuracy = M_HIGH;		break;
				case	VISION_PTN_ACCURACY_LOW		:	nAccuracy = M_LOW;		break;
				case	VISION_PTN_ACCURACY_MEDIUM	:	nAccuracy = M_MEDIUM;	break;
			}

			// 패턴 검색 설정
			MpatSetSpeed(MilModel, nSpeed);
			MpatSetAccuracy(MilModel, nAccuracy);
			MpatSetAngle(MilModel, M_SEARCH_ANGLE_MODE, M_ENABLE);
			MpatSetAngle(MilModel, M_SEARCH_ANGLE_DELTA_NEG, 5);
			MpatSetAngle(MilModel, M_SEARCH_ANGLE_DELTA_POS, 5);
			MpatSetAngle(MilModel, M_SEARCH_ANGLE_ACCURACY, 1.0);
			MpatSetAngle(MilModel, M_SEARCH_ANGLE_INTERPOLATION_MODE, M_BILINEAR);
			MpatPreprocModel(MilImageOriginSearch, MilModel, M_DEFAULT);

			// 패턴 검색 결과 버퍼 생성
			MpatAllocResult(m_MilSystem, 1L, &MilPatResult);
			if (MilPatResult) {

				// 패턴 검색
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
	// 판정 /////////////////////////////////////////////////////////
	if (bResultProcess) {

		// 오프셋
		dblOffsetX = (DOUBLE)(MilPosX - MilOrgPosX);
		dblOffsetY = (DOUBLE)(MilPosY - MilOrgPosY);

		stResult.nResultOffsetX = T_RESULT_SUCCESS;
		if (!stParam.bUseReverseJudgement && (INT)abs((INT)(dblOffsetX * 100)) > (INT)(stParam.stInspectionInfo.flOffset.x * 100))
			stResult.nResultOffsetX = T_RESULT_FAILURE;

		stResult.nResultOffsetY = T_RESULT_SUCCESS;
		if (!stParam.bUseReverseJudgement && (INT)abs((INT)(dblOffsetY * 100)) > (INT)(stParam.stInspectionInfo.flOffset.y * 100))
			stResult.nResultOffsetY = T_RESULT_FAILURE;

		// 각도
		dblAngle = (DOUBLE)(abs(MilAngle) > 180 ? abs(MilAngle) - 360 : MilAngle);

		stResult.nResultAngle = T_RESULT_SUCCESS;
		if (!stParam.bUseReverseJudgement && (INT)abs((INT)(dblAngle * 100)) > (INT)(stParam.stInspectionInfo.dblAngle * 100))
			stResult.nResultAngle = T_RESULT_FAILURE;

		// 매칭율
		dblMatchScore = (DOUBLE)MilScore;

		stResult.nResultMatchScore = stParam.bUseReverseJudgement ? T_RESULT_FAILURE : T_RESULT_SUCCESS;
		if ((INT)(dblMatchScore * 100) < (INT)(stParam.stInspectionInfo.dblMatchScore * 100))
			stResult.nResultMatchScore = stParam.bUseReverseJudgement ? T_RESULT_SUCCESS : T_RESULT_FAILURE;

		// 최종 판정
		nResultInspection = T_RESULT_SUCCESS;
		if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultOffsetX;
		if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultOffsetY;
		if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultAngle;
		if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultMatchScore;

		// 결과 저장
		stResult.flOffset.x			= (FLOAT)dblOffsetX;
		stResult.flOffset.y			= (FLOAT)dblOffsetY;
		stResult.dblAngle			= dblAngle;
		stResult.dblMatchScore		= dblMatchScore;
		stResult.nResultInspection	= nResultInspection;

		// 프로세스 시간
		dwTimeProcess = GetTickCount() - dwTimeProcess;

		// 디버그 메세지
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
	// 검사 이미지 저장 /////////////////////////////////////////////
	if (bSaveClip && bResultProcess && stResult.nResultInspection != T_RESULT_SUCCESS) {
	
		PMODEL_PROFILE_T		pstModelProfile		= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
		PVPRD_DATA_T			pstVisionSetupInfo	= &m_pstVisionProcedureData[m_stSystemStatus.nCurrentVisionInspectionNo];
		UINT					nInspectionNo		= 0;
		CString					strFileName			= _T("");
		CFileFind				fileFinder;

		// 파일 이름 설정
		strFileName.Format(_T("%s\\T%02d_%02d_%s_%s.JPG"),	pstWorkStatus->szWorkDataSaveDirectory, 
															nTestItemNo + 1,
															m_stSystemStatus.nCurrentVisionInspectionNo + 1,
															g_szTestResultEngS[stResult.nResultInspection],
															pstVisionSetupInfo->szName);

		// 이미지 파일 저장
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
	// MIL 버퍼 제거 ////////////////////////////////////////////////
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
// 이미지 프로세스 : 모델 검색 ////////////////////////////////////////////////
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
	// 초기화 ///////////////////////////////////////////////////////
	ZeroMemory(&stResult, sizeof(VI_RESULT_MODEL_T));
	ZeroMemory(&stOffsetRecursive, sizeof(DPS_POINT2D_T));
	ZeroMemory(&stRangeRecursive, sizeof(DPS_POINT2D_T));

	stResult.nResultInspection = T_RESULT_ERROR;


	/////////////////////////////////////////////////////////////////
	// 파라미터 로드 ////////////////////////////////////////////////
	rectInspectionRegion	= stParam.rectInspectionArea;


	/////////////////////////////////////////////////////////////////
	// 모델 지오메트리 파일 체크 ////////////////////////////////////
	bResultProcess = FALSE;
	for (INT nIndex = 0; nIndex < stParam.stInspectionInfo.nNumberOfGeometryFile; nIndex++) {
	
		strFileName = stParam.stInspectionInfo.szFileGeometry[nIndex];
		if (!strFileName.IsEmpty() && fileFinder.FindFile(strFileName))
			bResultProcess = TRUE;

		fileFinder.Close();
	}


	/////////////////////////////////////////////////////////////////
	// 그레이 스케일 이미지 버퍼 생성 ///////////////////////////////
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
	// THRESHOLD 이미지 변환 ////////////////////////////////////////
	if (bResultProcess && stParam.stThresholdInfo.dblRatioWhitePixelMIN > 0) {

		MbufAllocColor(m_MilSystem, MIL_BAND_GRAY, sizeImage.cx, sizeImage.cy, (8 + M_UNSIGNED), MilBufferAttributes, &MilImageThreshold);
		if (MilImageThreshold == M_NULL)	bResultProcess = FALSE;
		else {

			// THRESHOLD 변환
			MbufClear(MilImageThreshold, M_NULL);
			CDpsMilImageWnd::ConvertBinarize(MilImageGrayInspection, MilImageThreshold, stParam.stThresholdInfo.stThresholdInfo);

			// 이미지 반전
			if (stParam.stThresholdInfo.bInvertImage)	CDpsMilImageWnd::InvertImage(MilImageThreshold);

			// 미세 영역 제거
			CDpsMilImageWnd::RemoveParticles(MilImageThreshold, MilImageThreshold, stParam.stThresholdInfo.nParticleRadius, M_BINARY);

			// 그레이 스케일 이미지 버퍼 해제 및 THRESHOLD 로 변경
			MbufFree(MilImageGrayInspection);
			MilImageGrayInspection = MilImageThreshold;
		}
	}


	/////////////////////////////////////////////////////////////////
	// 검출 시작 ////////////////////////////////////////////////////
	do {

		/////////////////////////////////////////////////////////////
		// 초기화 ///////////////////////////////////////////////////
		stResult.nResultInspection = T_RESULT_ERROR;

	
		/////////////////////////////////////////////////////////////
		// 대상 영역 버퍼 생성 //////////////////////////////////////
		if (bResultProcess) {

			// 이미지 정보 로드
			MbufInquire(stParam.MilImageInspection, M_SIZE_X, &sizeImage.cx);
			MbufInquire(stParam.MilImageInspection, M_SIZE_Y, &sizeImage.cy);

			// 검색 영역 설정
			rectRegionSearch.left		= __max(rectInspectionRegion.ptTopLeft.x + (LONG)stOriginOffset.dblX + (LONG)stOffsetRecursive.dblX + (LONG)stRangeRecursive.dblX, 0);
			rectRegionSearch.top		= __max(rectInspectionRegion.ptTopLeft.y + (LONG)stOriginOffset.dblY + (LONG)stOffsetRecursive.dblY + (LONG)stRangeRecursive.dblY, 0);
			rectRegionSearch.right		= __min(rectInspectionRegion.ptTopLeft.x + (LONG)stOriginOffset.dblX + (LONG)stOffsetRecursive.dblX + rectInspectionRegion.sizeRect.cx - (LONG)stRangeRecursive.dblX, sizeImage.cx);
			rectRegionSearch.bottom		= __min(rectInspectionRegion.ptTopLeft.y + (LONG)stOriginOffset.dblY + (LONG)stOffsetRecursive.dblY + rectInspectionRegion.sizeRect.cy - (LONG)stRangeRecursive.dblY, sizeImage.cy);

			// 버퍼 초기화
			if (MilImageInspection != M_NULL) {
			
				MbufFree(MilImageInspection);
				MilImageInspection = M_NULL;
			}

			// 버퍼 생성
			MbufChild2d(MilImageGrayInspection, 
						rectRegionSearch.left, 
						rectRegionSearch.top, 
						rectRegionSearch.Width(), 
						rectRegionSearch.Height(), 
						&MilImageInspection);

			if (MilImageInspection == M_NULL)		bResultProcess = FALSE;
		}


		/////////////////////////////////////////////////////////////////
		// 대상 모델 검색 ///////////////////////////////////////////////
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
							// 판정 /////////////////////////////////////
							for (INT nIndexModel = 0; nIndexModel < (INT)MilNumberOfResult; nIndexModel++) {
						
								// 오프셋
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

								// 각도
								dblAngle = (DOUBLE)MilAngle[nIndexModel];
								dblAngle = abs(dblAngle) > 180 ? abs(dblAngle) - 360 : dblAngle;

								stResult.nResultAngle = T_RESULT_SUCCESS;
								if (!stParam.bUseReverseJudgement && (INT)abs((INT)(dblAngle * 100)) > (INT)(stParam.stInspectionInfo.dblAngle * 100))
									stResult.nResultAngle = T_RESULT_FAILURE;

								// 매칭율
								dblMatchScore = (DOUBLE)MilScore[nIndexModel];

								stResult.nResultMatchScore = stParam.bUseReverseJudgement ? T_RESULT_FAILURE : T_RESULT_SUCCESS;
								if ((INT)(dblMatchScore * 100) < (INT)(stParam.stInspectionInfo.dblMatchScore * 100))
									stResult.nResultMatchScore = stParam.bUseReverseJudgement ? T_RESULT_SUCCESS : T_RESULT_FAILURE;

								// 최종 판정
								nResultInspection = T_RESULT_SUCCESS;
								if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultOffsetX;
								if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultOffsetY;
								if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultAngle;
								if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultMatchScore;
							
								// 합격이면 검색 종료
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

			// 결과 저장
			stResult.flOffset.x			= (FLOAT)dblOffsetX;
			stResult.flOffset.y			= (FLOAT)dblOffsetY;
			stResult.dblAngle			= dblAngle;
			stResult.dblMatchScore		= dblMatchScore;
			stResult.nResultInspection	= nResultInspection != T_RESULT_SUCCESS ? T_RESULT_FAILURE : nResultInspection;

			// 프로세스 시간
			dwTimeProcess = GetTickCount() - dwTimeProcess;

			//MessageWindow(cDEBUG, _T("ProcessImage_ModelFind::dwTimeProcess=%d"), dwTimeProcess);
			//MessageWindow(cDEBUG, _T("----------------------------------------------------------------------------------------------------"));

			// 순환 측정
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
	// 검출 영역 이미지 저장 ////////////////////////////////////////
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
	// 검사 이미지 저장 /////////////////////////////////////////////
	if (bSaveClip && bResultProcess && stResult.nResultInspection != T_RESULT_SUCCESS) {
	
		PMODEL_PROFILE_T		pstModelProfile		= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
		PVPRD_DATA_T			pstVisionSetupInfo	= &m_pstVisionProcedureData[m_stSystemStatus.nCurrentVisionInspectionNo];
		UINT					nInspectionNo		= 0;
		CString					strFileName			= _T("");
		CFileFind				fileFinder;

		// 파일 이름 설정
		strFileName.Format(_T("%s\\T%02d_%02d_%s_%s.JPG"),	pstWorkStatus->szWorkDataSaveDirectory, 
															nTestItemNo + 1,
															m_stSystemStatus.nCurrentVisionInspectionNo + 1,
															g_szTestResultEngS[stResult.nResultInspection],
															pstVisionSetupInfo->szName);

		// 이미지 파일 저장
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
	// MIL 버퍼 제거 ////////////////////////////////////////////////
	if (MilImageInspection != M_NULL)		{ MbufFree(MilImageInspection);		/*MessageWindow(cDEBUG, _T("ProcessImage_ModelFind::Release <MilImageInspection>"));*/ }
	if (MilImageGrayInspection != M_NULL)	{ MbufFree(MilImageGrayInspection);	/*MessageWindow(cDEBUG, _T("ProcessImage_ModelFind::Release <MilImageGrayInspection>"));*/ }


	return	bResultProcess;
}


///////////////////////////////////////////////////////////////////////////////
// 이미지 프로세스 : 컬러 분석 ////////////////////////////////////////////////
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
	// 초기화 ///////////////////////////////////////////////////////
	ZeroMemory(&stResult, sizeof(VI_RESULT_COLOR_T));

	stResult.nResultInspection = T_RESULT_ERROR;


	/////////////////////////////////////////////////////////////////
	// 파라미터 로드 ////////////////////////////////////////////////
	rectInspectionRegion	= stParam.rectInspectionArea;


	/////////////////////////////////////////////////////////////////
	// 컬러 지오메트리 파일 체크 ////////////////////////////////////
	bResultProcess = FALSE;
	for (INT nIndex = 0; nIndex < stParam.stInspectionInfo.nNumberOfGeometryFile; nIndex++) {
	
		strFileName = stParam.stInspectionInfo.szFileGeometry[nIndex];
		if (!strFileName.IsEmpty() && fileFinder.FindFile(strFileName))
			bResultProcess = TRUE;

		fileFinder.Close();
	}


	/////////////////////////////////////////////////////////////////
	// 검출 시작 ////////////////////////////////////////////////////
	stResult.nResultInspection = T_RESULT_ERROR;

	
	/////////////////////////////////////////////////////////////////
	// 대상 영역 버퍼 생성 //////////////////////////////////////////
	if (bResultProcess) {

		// 이미지 정보 로드
		MbufInquire(stParam.MilImageInspection, M_SIZE_X, &sizeImage.cx);
		MbufInquire(stParam.MilImageInspection, M_SIZE_Y, &sizeImage.cy);

		// 검색 영역 설정
		rectRegionSearch.left		= __max(rectInspectionRegion.ptTopLeft.x + (LONG)stOriginOffset.dblX, 0);
		rectRegionSearch.top		= __max(rectInspectionRegion.ptTopLeft.y + (LONG)stOriginOffset.dblY, 0);
		rectRegionSearch.right		= __min(rectInspectionRegion.ptTopLeft.x + (LONG)stOriginOffset.dblX + rectInspectionRegion.sizeRect.cx, sizeImage.cx);
		rectRegionSearch.bottom		= __min(rectInspectionRegion.ptTopLeft.y + (LONG)stOriginOffset.dblY + rectInspectionRegion.sizeRect.cy, sizeImage.cy);

		// 버퍼 초기화
		if (MilImageInspection != M_NULL) {
			
			MbufFree(MilImageInspection);
			MilImageInspection = M_NULL;
		}

		// 버퍼 생성
		MbufChild2d(stParam.MilImageInspection, 
					rectRegionSearch.left, 
					rectRegionSearch.top, 
					rectRegionSearch.Width(), 
					rectRegionSearch.Height(), 
					&MilImageInspection);

		if (MilImageInspection == M_NULL)		bResultProcess = FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// 대상 컬러 검색 ///////////////////////////////////////////////
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

							// 픽셀 수
							nPixelCount = (UINT)MilPixelCount;
							stResult.nResultPixelCount = T_RESULT_SUCCESS;
							//if (nPixelCount < stParam.stInspectionInfo.nPixelCount)
								//stResult.nResultPixelCount = T_RESULT_FAILURE;

							// 거리
							dblDistance = (DOUBLE)MilDistance;
							stResult.nResultDistance = T_RESULT_SUCCESS;
							//if (dblDistance < stParam.stInspectionInfo.dblDistance)
								//stResult.nResultDistance = T_RESULT_FAILURE;

							// 매칭율
							dblMatchScore = (DOUBLE)MilScore;
							stResult.nResultMatchScore = T_RESULT_SUCCESS;
							if ((INT)(dblMatchScore * 100) < (INT)(stParam.stInspectionInfo.dblMatchScore * 100))
								stResult.nResultMatchScore = T_RESULT_FAILURE;

							// 최종 판정
							nResultInspection = T_RESULT_SUCCESS;
							if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultPixelCount;
							if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultDistance;
							if (nResultInspection == T_RESULT_SUCCESS)	nResultInspection = stResult.nResultMatchScore;

							// 합격이면 분석 종료
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

		// 결과 저장
		stResult.nPixelCount		= nPixelCount;
		stResult.dblDistance		= dblDistance;
		stResult.dblMatchScore		= dblMatchScore;
		stResult.nResultInspection	= nResultInspection;

		// 프로세스 시간
		dwTimeProcess = GetTickCount() - dwTimeProcess;

		//MessageWindow(cDEBUG, _T("ProcessImage_ColorAnalysis::dwTimeProcess=%d"), dwTimeProcess);
		//MessageWindow(cDEBUG, _T("----------------------------------------------------------------------------------------------------"));
	}


	/////////////////////////////////////////////////////////////////
	// 검출 영역 이미지 저장 ////////////////////////////////////////
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
	// 검사 이미지 저장 /////////////////////////////////////////////
	if (bSaveClip && bResultProcess && stResult.nResultInspection != T_RESULT_SUCCESS) {
	
		PMODEL_PROFILE_T		pstModelProfile		= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
		PVPRD_DATA_T			pstVisionSetupInfo	= &m_pstVisionProcedureData[m_stSystemStatus.nCurrentVisionInspectionNo];
		UINT					nInspectionNo		= 0;
		CString					strFileName			= _T("");
		CFileFind				fileFinder;

		// 파일 이름 설정
		strFileName.Format(_T("%s\\T%02d_%02d_%s_%s.JPG"),	pstWorkStatus->szWorkDataSaveDirectory, 
															nTestItemNo + 1,
															m_stSystemStatus.nCurrentVisionInspectionNo + 1,
															g_szTestResultEngS[stResult.nResultInspection],
															pstVisionSetupInfo->szName);

		// 이미지 파일 저장
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
	// MIL 버퍼 제거 ////////////////////////////////////////////////
	if (MilImageInspection != M_NULL)		{ MbufFree(MilImageInspection);		/*MessageWindow(cDEBUG, _T("ProcessImage_ColorAnalysis::Release <MilImageInspection>"));*/ }


	return	bResultProcess;
}







///////////////////////////////////////////////////////////////////////////////////////////////////
// 비전 센서 유닛 정보 ////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 비전 프로그램 번호 선택 ////////////////////////////////////////////////////
BOOL CMainApp::VISION_SelectProgramNo(BOOL bEnable, INT nProgramNo /* = 0 */)
{
	/////////////////////////////////////////////////////////////////
	// 출력 활성화 //////////////////////////////////////////////////
	if (bEnable) {

		/////////////////////////////////////////////////////////////
		// 스케쥴 번호 체크 /////////////////////////////////////////
		if (nProgramNo < 0 || nProgramNo > MAX_VISION_PROGRAM_NO)
			return	FALSE;


		/////////////////////////////////////////////////////////////
		// 신호 설정 ////////////////////////////////////////////////
		SetDOStatus(nProgramNo & 0x01 ? DO_ON : DO_OFF, DO_SIG_S02_VISION_SELECT_0);
		SetDOStatus(nProgramNo & 0x02 ? DO_ON : DO_OFF, DO_SIG_S02_VISION_SELECT_1);
		SetDOStatus(nProgramNo & 0x04 ? DO_ON : DO_OFF, DO_SIG_S02_VISION_SELECT_2);
		SetDOStatus(nProgramNo & 0x08 ? DO_ON : DO_OFF, DO_SIG_S02_VISION_SELECT_3);
		SetDOStatus(nProgramNo & 0x10 ? DO_ON : DO_OFF, DO_SIG_S02_VISION_SELECT_4);


	/////////////////////////////////////////////////////////////////
	// 출력 비활성화 ////////////////////////////////////////////////
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
// 비젼 결과 가져오기 /////////////////////////////////////////////////////////
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
	// 결과 파일 로드 ///////////////////////////////////////////////
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
					strRead.Remove(' ');	// 공백 제거
					
					/////////////////////////////////////////////////
					_stprintf_s(szTemp, MAX_STRVALUE, _T("%s"), strRead);
					szToken	= _tcstok_s(szTemp, _T("\t"), &szType);
					if (szToken) {

						// 프로그램 번호
						if (_tcsncmp(szToken, _T("ProgramNo."), 10) == 0) {

							szToken	= _tcstok_s(NULL, _T("\t"), &szType);
							if (szToken) {
										
								nValue = _ttoi(szToken);
								stResult.nProgramNo = (UINT)nValue;
							}

							continue;
						}

						// 트리거 번호
						if (_tcsncmp(szToken, _T("TriggerNo."), 10) == 0) {

							szToken	= _tcstok_s(NULL, _T("\t"), &szType);
							if (szToken) {
										
								nValue = _ttoi(szToken);
								stResult.nTriggerNo = (UINT)nValue;
							}

							continue;
						}

						// 검사 시간
						if (_tcsncmp(szToken, _T("TIME[ms]"), 8) == 0) {

							szToken	= _tcstok_s(NULL, _T("\t"), &szType);
							if (szToken) {
										
								nValue = _ttoi(szToken);
								stResult.nTimeInspection = (UINT)nValue;
							}

							continue;
						}

						// 최종 결과
						if (_tcsncmp(szToken, _T("TotalStatus"), 11) == 0) {

							szToken	= _tcstok_s(NULL, _T("\t"), &szType);
							if (szToken) {
										
								if (_tcsncmp(szToken, _T("OK"), 2) == 0)	stResult.nResultFinal = T_RESULT_SUCCESS;
								else										stResult.nResultFinal = T_RESULT_FAILURE;
							}

							continue;
						}

						// 비전 위치 결과
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
// 비전 이미지 검색 ///////////////////////////////////////////////////////////
BOOL CMainApp::VISION_GetInspectionImage(CString& strFileName)
{
	BOOL			bIsFile			= FALSE;
	BOOL			bIsFoundImage	= FALSE;

	CDpsStringArray	strArrayFiles;
	CFileFind		fileFinder;


	/////////////////////////////////////////////////////////////////
	// 파일 검색 ////////////////////////////////////////////////////
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
	// 파일 정렬 ////////////////////////////////////////////////////
	if (strArrayFiles.GetCount()) {

		strArrayFiles.Sort(DPS_SORT_DESC);
		strFileName = strArrayFiles.GetAt(0);
	}


	return	bIsFoundImage;
}







///////////////////////////////////////////////////////////////////////////////////////////////////
// 작업 프로세스 //////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 작업 프로세스 시작 /////////////////////////////////////////////////////////
BOOL CMainApp::StartWorkProcess(void)
{
	PTHREAD_PARAM_T	pstParam	= NULL;
	BOOL			bResult		= TRUE;


	/////////////////////////////////////////////////////////////////
	// 메인 스레드 //////////////////////////////////////////////////
	m_bExitThread[THREAD_MAIN]	= FALSE;
	m_pThread[THREAD_MAIN]		= ::AfxBeginThread(ThreadFuncMain, this, THREAD_PRIORITY_NORMAL);
	if (m_pThread[THREAD_MAIN]) {
	
		m_pThread[THREAD_MAIN]->m_bAutoDelete = FALSE;
		bResult &= TRUE;
	
	} else {
	
		bResult = FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// 시스템 스레드 ////////////////////////////////////////////////
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
	// 시스템 스레드 ////////////////////////////////////////////////
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
// 작업 프로세스 정지 /////////////////////////////////////////////////////////
void CMainApp::StopWorkProcess(void)
{
	// 스레드 종료
	for (UINT nIndex = 0; nIndex < MAX_WORK_THREAD; nIndex++) {

		if (m_pThread[nIndex]) {

			// 스레드 종료
			m_csExitThread[nIndex].Lock();
			m_bExitThread[nIndex] = TRUE;
			m_csExitThread[nIndex].Unlock();

			// 스레드 종료 대기
			DWORD	dwRetCode = ::WaitForSingleObject(m_pThread[nIndex]->m_hThread, THREAD_WAIT_TIME);
			if (dwRetCode != WAIT_OBJECT_0) {

				// 강제 종료
				::TerminateThread(m_pThread[nIndex]->m_hThread, 0);
				CloseHandle(m_pThread[nIndex]->m_hThread);
			}

			// 스레드 객체 해제
			m_pThread[nIndex]->m_hThread = NULL;
			delete	m_pThread[nIndex];
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
// 프로세스 : 시스템 //////////////////////////////////////////////////////////
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
	// 변수 초기화 //////////////////////////////////////////////////
	ZeroMemory(&stParamUI, sizeof(UI_PARAM_UPDATE_T));

	nDO_SIG_TL_RED		= m_nTypeMachine == MC_TYPE_1 ? DO_SIG_TL1_RED : DO_SIG_TL2_RED;
	nDO_SIG_TL_YELLOW	= m_nTypeMachine == MC_TYPE_1 ? DO_SIG_TL1_YELLOW : DO_SIG_TL2_YELLOW;
	nDO_SIG_TL_GREEN	= m_nTypeMachine == MC_TYPE_1 ? DO_SIG_TL1_GREEN : DO_SIG_TL2_GREEN;
	nDO_SIG_TL_BUZZER	= m_nTypeMachine == MC_TYPE_1 ? DO_SIG_TL1_BUZZER : DO_SIG_TL2_BUZZER;


	/////////////////////////////////////////////////////////////////
	// 수동 제어 모드 ///////////////////////////////////////////////
	bOnManualControlMode  = FALSE;
	bOnManualControlMode |= m_stSystemStatus.bOnManualControlDIO;
	for (UINT nIndex = 0; nIndex < MAX_STATION; nIndex++)
		bOnManualControlMode |= m_stSystemStatus.bIsManualControl[nIndex];


	/////////////////////////////////////////////////////////////////
	// 알람 상태 설정 ///////////////////////////////////////////////
	bOnAlarm	= FALSE;
	bOnAlarm   |= m_stSystemStatus.bOnAlarmSystem;
	for (UINT nIndex = 0; nIndex < MAX_STATION; nIndex++)
		bOnAlarm |= m_stSystemStatus.bOnAlarmStation[nIndex];


	/////////////////////////////////////////////////////////////////
	// 시스템 상태 모니터 설정 //////////////////////////////////////
	if (m_pSysStateMonitorWnd) {

		if (m_stSystemStatus.bOnMachineInitialize)				m_pSysStateMonitorWnd->SetSystemState(S_STATE_MACHINE_INIT);					// 장비 초기화중
		else if (!m_stSystemStatus.bResultSystemInitialize)		m_pSysStateMonitorWnd->SetSystemState(S_STATE_SYSTEM_INIT_FAIL, TRUE);			// 시스템 초기화 실패
		else if (m_nTypeMachine == MC_TYPE_1 && !m_stSystemStatus.bResultMachineInitialize)	m_pSysStateMonitorWnd->SetSystemState(S_STATE_MACHINE_INIT_FAIL, TRUE);			// 장비 초기화 실패
		else if (m_stSystemStatus.bOnEmergencyStop)				m_pSysStateMonitorWnd->SetSystemState(S_STATE_EMERGENCY_STOP, TRUE);			// 비상 정지
		else if (m_stSystemStatus.bOnAirSupplyFail)				m_pSysStateMonitorWnd->SetSystemState(S_STATE_AIR_SUPPLY_FAIL, TRUE);			// 공압 공급 실패
		else if (bOnAlarm)										m_pSysStateMonitorWnd->SetSystemState(S_STATE_WARNING, TRUE);					// 시스템 알람
		else if (m_stSystemStatus.bOnDoorOpened)				m_pSysStateMonitorWnd->SetSystemState(S_STATE_DOOR_OPEN, TRUE);					// 도어 열림
		else if (m_stSystemStatus.bOnWaitForUser)				m_pSysStateMonitorWnd->SetSystemState(S_STATE_WAIT_USER);						// 사용자 입력 대기
		else if (m_stSystemStatus.bOnTestMode)					m_pSysStateMonitorWnd->SetSystemState(S_STATE_TEST_MODE);						// 테스트 모드
		else if (m_stSystemStatus.bOnPassDrive)					m_pSysStateMonitorWnd->SetSystemState(S_STATE_PASS_MODE);						// 패스 모드
		else if (bOnManualControlMode)							m_pSysStateMonitorWnd->SetSystemState(S_STATE_MANUAL_MODE);						// 수동 모드
		else if (m_stSystemStatus.bOnPause)						m_pSysStateMonitorWnd->SetSystemState(S_STATE_PAUSE);							// 일시 정지
		else if (m_stSystemStatus.bOnOperatingStopReservated)	m_pSysStateMonitorWnd->SetSystemState(S_STATE_OP_STOP_RESERVATE);				// 작업 정지 예약
		else if (m_stSystemStatus.bOnOperating)					m_pSysStateMonitorWnd->SetSystemState(S_STATE_OP_START);						// 작업 시작
		else													m_pSysStateMonitorWnd->SetSystemState(S_STATE_OP_STOP);							// 작업 정지
	}


	/////////////////////////////////////////////////////////////////
	// 타워램프 프로세스 ////////////////////////////////////////////

	///////////////////////////////////////////////////////
	// 시스템 알람 상태 ///////////////////////////////////
	if (m_stSystemStatus.bOnEmergencyStop || m_stSystemStatus.bOnAirSupplyFail || !m_stSystemStatus.bResultSystemInitialize) {

		SetDOStatus(DO_OFF, nDO_SIG_TL_YELLOW);

		// 적색 램프 점멸
		if (LTimerTLamp.Verify()) {

			bEnableTLamp = !bEnableTLamp;
			SetDOStatus(bEnableTLamp ? DO_ON : DO_OFF, nDO_SIG_TL_RED);
			LTimerTLamp.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_LAMP));
		}

	///////////////////////////////////////////////////////
	// 일반 알람 상태 /////////////////////////////////////
	} else if (bOnAlarm || m_stSystemStatus.bOnDoorOpened) {

		SetDOStatus(DO_OFF, nDO_SIG_TL_RED);

		// 황색 램프 점멸
		if (LTimerTLamp.Verify()) {

			bEnableTLamp = !bEnableTLamp;
			SetDOStatus(bEnableTLamp ? DO_ON : DO_OFF, nDO_SIG_TL_YELLOW);
			LTimerTLamp.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_LAMP));
		}

	///////////////////////////////////////////////////////
	// 사용자 입력 대기 상태 //////////////////////////////
	} else if (m_stSystemStatus.bOnWaitForUser) {

		SetDOStatus(DO_OFF, nDO_SIG_TL_RED);

		// 황색 램프 점멸
		if (LTimerTLamp.Verify()) {

			bEnableTLamp = !bEnableTLamp;
			SetDOStatus(bEnableTLamp ? DO_ON : DO_OFF, nDO_SIG_TL_YELLOW);
			LTimerTLamp.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_LAMP));
		}

	///////////////////////////////////////////////////////
	// 운전 상태 //////////////////////////////////////////
	} else if (m_stSystemStatus.bOnOperating) {

		SetDOStatus(DO_ON,  nDO_SIG_TL_GREEN);			// 녹색 램프 점등
		SetDOStatus(DO_OFF, nDO_SIG_TL_YELLOW);			// 황색 램프 소등
		SetDOStatus(DO_OFF, nDO_SIG_TL_RED);			// 적색 램프 소등

	///////////////////////////////////////////////////////
	// 기본 상태 //////////////////////////////////////////
	} else {

		SetDOStatus(DO_OFF, nDO_SIG_TL_YELLOW);			// 황색 램프 소등
		SetDOStatus(DO_OFF, nDO_SIG_TL_RED);			// 적색 램프 소등

		// 녹색 램프 점멸
		if (LTimerTLamp.Verify()) {

			bEnableTLamp = !bEnableTLamp;
			SetDOStatus(bEnableTLamp ? DO_ON : DO_OFF, nDO_SIG_TL_GREEN);
			LTimerTLamp.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_LAMP));
		}
	}


	/////////////////////////////////////////////////////////////////
	// 타워램프 부저 설정 ///////////////////////////////////////////
	if (m_stSystemStatus.bOnBuzzer) {

		// 부저 ON/OFF
		if (LTimerTBuzz.Verify()) {

			bEnableTBuzz = !bEnableTBuzz;
			SetDOStatus(bEnableTBuzz ? DO_ON : DO_OFF, nDO_SIG_TL_BUZZER);
			LTimerTBuzz.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_BUZZER));
		}

	} else {

		// 비프음 상태가 아니면, 부저 OFF
		if (!m_stSystemStatus.bOnBeep)	SetDOStatus(DO_OFF, nDO_SIG_TL_BUZZER);
	}


	/////////////////////////////////////////////////////////////////
	// 비프음 프로세스 //////////////////////////////////////////////
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
	// 업데이트 UI //////////////////////////////////////////////////
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
// 프로세스 : 오류 검출 ///////////////////////////////////////////////////////
void CMainApp::ProcessErrorDetect(void)
{
	static		LTimerTMsec		LTimerVacuum;

	BOOL						bOnUpdateUI	= FALSE;
	UI_PARAM_UPDATE_T			stParamUI;


	/////////////////////////////////////////////////////////////////
	// 변수 초기화 //////////////////////////////////////////////////
	ZeroMemory(&stParamUI, sizeof(UI_PARAM_UPDATE_T));


	/////////////////////////////////////////////////////////////////
	// 안전 센서 체크 ///////////////////////////////////////////////
	if (!m_SystemConfig.UseSystemOption(SOPT_DISABLE_SAFETY_AREA)) {
	
		// 스테이션 #1
		//m_stSystemStatus.bOnSafetyDetected[STATION_1][STN1_SUB_COMMON_1] = !GetDIStatus(DI_SENS_S10A_DETECT_SAFETY_1) | !GetDIStatus(DI_SENS_S10A_DETECT_SAFETY_2) | !GetDIStatus(DI_SENS_S10A_DETECT_SAFETY_3);
		//m_stSystemStatus.bOnSafetyDetected[STATION_1][STN1_SUB_COMMON_2] = !GetDIStatus(DI_SENS_S10B_DETECT_SAFETY_1) | !GetDIStatus(DI_SENS_S10A_DETECT_SAFETY_2) | !GetDIStatus(DI_SENS_S10B_DETECT_SAFETY_3);
			
	} else {
	
		ZeroMemory(m_stSystemStatus.bOnSafetyDetected, sizeof(BOOL) * MAX_STATION * MAX_SUB_STATION);
	}


	/////////////////////////////////////////////////////////////////
	// 불량함 FULL 감지 체크 ////////////////////////////////////////
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
	// 업데이트 UI //////////////////////////////////////////////////
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
// 프로세스 : 비상 체크 ///////////////////////////////////////////////////////
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
	// 스텝 프로세스 ////////////////////////////////////////////////
	switch (nCurrentStep) {

		case	0		:
							nCurrentStep = 100;
							break;

		case	100		:
							if (m_stSystemStatus.nDeviceStatus[SD_DIO_1] == DS_NORMAL) {

								nCurrentStep = 110;
								break;
							}

							// 비상 정지 플래그 해제
							m_stSystemStatus.bOnEmergencyStop = FALSE;

							nCurrentStep = 190;
							break;

		case	110		:
							if (!m_stSystemStatus.bOnEmergencyStop && bDI_EMERGENCY_STOP)		nCurrentStep = 120;
							else if (m_stSystemStatus.bOnEmergencyStop && !bDI_EMERGENCY_STOP)	nCurrentStep = 130;
							else																nCurrentStep = 190;

							break;

		// 오류 설정
		case	120		:
							// 비상 정지 플래그 설정
							m_stSystemStatus.bOnEmergencyStop = TRUE;

							// 사용자 메세지 설정
							m_stSystemStatus.nPreviousUserMessage	= UMSG_NONE;
							m_stSystemStatus.nCurrentUserMessage	= UMSG_ERROR_EMERGENCY_STOP;

							// 서보 모터 정지
							for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++) {

								Motion_Stop_E(nAxisNo);
								Motion_Stop_E(nAxisNo);
								AxmSignalServoOn(nAxisNo, DISABLE);
							}

							// 서보 브레이크 설정
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z1);
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z2);
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z3);
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z4);

							bOnError	 = TRUE;
							nCurrentStep = 190;
							break;

		// 오류 해제
		case	130		:
							// 비상 정지 플래그 해제
							m_stSystemStatus.bOnEmergencyStop = FALSE;

							// 사용자 메세지 초기화
							ClearUserMessage();

							bOnErrorClear = TRUE;
							nCurrentStep  = 190;
							break;

		case	190		:
							nCurrentStep = 0;
							break;
	}


	/////////////////////////////////////////////////////////////////
	// 오류 발생 ////////////////////////////////////////////////////
	if (bOnError) {

		PERROR_CODE_T pstErrorCode = new (std::nothrow) ERROR_CODE_T;
		if (pstErrorCode) {

			ZeroMemory(pstErrorCode, sizeof(ERROR_CODE_T));
			pstErrorCode->nErrorCode = ERROR_EMERGENCY_STOP;

			if (m_pSysHistoryDlg)	m_pSysHistoryDlg->SendMessage(UM_HISTORY_ON_ERROR, (WPARAM)pstErrorCode);
			else					delete	pstErrorCode;
		}

		// 일시 정지
		if (m_stSystemStatus.bOnOperating) {

			m_stSystemStatus.bOnPause = TRUE;
			if (m_pMainWnd && m_pMainWnd->GetSafeHwnd())
				m_pMainWnd->PostMessage(UM_MAIN_PAUSE);
		}
	}


	/////////////////////////////////////////////////////////////////
	// 오류 해제 ////////////////////////////////////////////////////
	if (bOnErrorClear) {

		if (m_pSysHistoryDlg) {

			if (m_stSystemStatus.nCurrentErrorCode == ERROR_AIR_PRESSURE)
				m_pSysHistoryDlg->PostMessage(UM_HISTORY_CLEAR);
		}
	}


	/////////////////////////////////////////////////////////////////
	// 스텝 모니터링 ////////////////////////////////////////////////
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
// 프로세스 : 공압 체크 ///////////////////////////////////////////////////////
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
	// 스텝 프로세스 ////////////////////////////////////////////////
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

							// 공압 오류 플래그 해제
							m_stSystemStatus.bOnAirSupplyFail = FALSE;

							nCurrentStep = 190;
							break;

		case	110		:
							if (!m_stSystemStatus.bOnAirSupplyFail && bDI_AIR_PRESSURE)			nCurrentStep = 120;
							else if (m_stSystemStatus.bOnAirSupplyFail && !bDI_AIR_PRESSURE)	nCurrentStep = 130;
							else																nCurrentStep = 190;

							break;

		// 오류 설정
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
							// 공압 오류 플래그 설정
							m_stSystemStatus.bOnAirSupplyFail = TRUE;

							bOnError	 = TRUE;
							nCurrentStep = 190;
							break;

		// 오류 해제
		case	130		:
							// 공압 오류 플래그 해제
							m_stSystemStatus.bOnAirSupplyFail = FALSE;

							bOnErrorClear = TRUE;
							nCurrentStep  = 190;
							break;

		case	190		:
							nCurrentStep = 0;
							break;
	}


	/////////////////////////////////////////////////////////////////
	// 오류 발생 ////////////////////////////////////////////////////
	if (bOnError) {

		PERROR_CODE_T pstErrorCode = new (std::nothrow) ERROR_CODE_T;
		if (pstErrorCode) {

			ZeroMemory(pstErrorCode, sizeof(ERROR_CODE_T));
			pstErrorCode->nErrorCode = ERROR_AIR_PRESSURE;

			if (m_pSysHistoryDlg)	m_pSysHistoryDlg->SendMessage(UM_HISTORY_ON_ERROR, (WPARAM)pstErrorCode);
			else					delete	pstErrorCode;
		}

		// 일시 정지
		if (m_stSystemStatus.bOnOperating) {

			m_stSystemStatus.bOnPause = TRUE;
			if (m_pMainWnd && m_pMainWnd->GetSafeHwnd())
				m_pMainWnd->PostMessage(UM_MAIN_PAUSE);
		}
	}


	/////////////////////////////////////////////////////////////////
	// 오류 해제 ////////////////////////////////////////////////////
	if (bOnErrorClear) {

		if (m_pSysHistoryDlg) {

			if (m_stSystemStatus.nCurrentErrorCode == ERROR_AIR_PRESSURE)
				m_pSysHistoryDlg->PostMessage(UM_HISTORY_CLEAR);
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
// 프로세스 : 도어 체크 ///////////////////////////////////////////////////////
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
	// 스텝 프로세스 ////////////////////////////////////////////////
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

							// 문열림 플래그 해제
							m_stSystemStatus.bOnDoorOpened = FALSE;

							nCurrentStep = 190;
							break;

		case	110		:
							if (!m_stSystemStatus.bOnDoorOpened && bDI_DOOR_OPEN)		nCurrentStep = 120;
							else if (m_stSystemStatus.bOnDoorOpened && !bDI_DOOR_OPEN)	nCurrentStep = 130;
							else														nCurrentStep = 190;

							break;

		// 오류 설정
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
							// 문열림 플래그 설정
							m_stSystemStatus.bOnDoorOpened = TRUE;

							bOnError     = TRUE;
							nCurrentStep = 190;
							break;

		// 오류 해제
		case	130		:
							// 문열림 플래그 해제
							m_stSystemStatus.bOnDoorOpened = FALSE;

							bOnErrorClear = TRUE;
							nCurrentStep  = 190;
							break;

		case	190		:
							nCurrentStep = 0;
							break;
	}


	/////////////////////////////////////////////////////////////////
	// 오류 발생 ////////////////////////////////////////////////////
	if (bOnError) {

		if (!GetDIStatus(DI_SIG_DOOR_OPENED_1))		ErrorMessage(TRUE, _T("%s::(X%03X) %s"), g_stSystemString[SYSSTR_MC_WARN_DOOR_OPENED].szDescription[m_nTypeLanguage], DI_SIG_DOOR_OPENED_1, g_stDIODescription[m_nTypeLanguage][DI_SIG_DOOR_OPENED_1].szInput);
		if (!GetDIStatus(DI_SIG_DOOR_OPENED_2))		ErrorMessage(TRUE, _T("%s::(X%03X) %s"), g_stSystemString[SYSSTR_MC_WARN_DOOR_OPENED].szDescription[m_nTypeLanguage], DI_SIG_DOOR_OPENED_2, g_stDIODescription[m_nTypeLanguage][DI_SIG_DOOR_OPENED_2].szInput);

		if (m_nTypeLanguage != LANGUAGE_KOR) {

			if (!GetDIStatus(DI_SIG_DOOR_OPENED_1))	ErrorMessage(TRUE, _T("%s::(X%03X) %s"), g_stSystemString[SYSSTR_MC_WARN_DOOR_OPENED].szDescription[LANGUAGE_KOR], DI_SIG_DOOR_OPENED_1, g_stDIODescription[LANGUAGE_KOR][DI_SIG_DOOR_OPENED_1].szInput);
			if (!GetDIStatus(DI_SIG_DOOR_OPENED_2))	ErrorMessage(TRUE, _T("%s::(X%03X) %s"), g_stSystemString[SYSSTR_MC_WARN_DOOR_OPENED].szDescription[LANGUAGE_KOR], DI_SIG_DOOR_OPENED_2, g_stDIODescription[LANGUAGE_KOR][DI_SIG_DOOR_OPENED_2].szInput);
		}

		// 일시 정지
		if (m_stSystemStatus.bOnOperating) {

			// 시스템 플래그 설정
			m_stSystemStatus.bOnBuzzer = TRUE;

// 			m_stSystemStatus.bOnPause = TRUE;
// 			if (m_pMainWnd && m_pMainWnd->GetSafeHwnd())
// 				m_pMainWnd->PostMessage(UM_MAIN_PAUSE);
		}
	}


	/////////////////////////////////////////////////////////////////
	// 오류 해제 ////////////////////////////////////////////////////
	if (bOnErrorClear) {

		// 일시 정지 해제
		if (m_stSystemStatus.bOnOperating) {

			// 시스템 플래그 해제
			m_stSystemStatus.bOnBuzzer = FALSE;

// 			m_stSystemStatus.bOnPause = FALSE;
// 			if (m_pMainWnd && m_pMainWnd->GetSafeHwnd())
// 				m_pMainWnd->PostMessage(UM_MAIN_PAUSE);
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
// 프로세스 : 모션 컨트롤 /////////////////////////////////////////////////////
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
	// 수동 제어 모드 설정 //////////////////////////////////////////
	bOnManualControlMode  = FALSE;
	bOnManualControlMode |= m_stSystemStatus.bOnManualControlDIO;
	for (UINT nIndex = 0; nIndex < MAX_STATION; nIndex++)
		bOnManualControlMode |= m_stSystemStatus.bIsManualControl[nIndex];


	/////////////////////////////////////////////////////////////////
	// 비상 정지 체크 ///////////////////////////////////////////////
	if (m_stSystemStatus.bOnEmergencyStop) {

		nCurrentStep	= 0;
		nMC_CurrentStep	= 0;
	
		// 수동 컨트롤 플래그 해제
		m_stSystemStatus.bOnMC_MotionMoveJog	= FALSE;
		ZeroMemory(m_stSystemStatus.bOnMC_MotionMove, sizeof(BOOL) * MAX_STATION);
		ZeroMemory(m_stSystemStatus.bOnMC_MotionMoveEx, sizeof(BOOL) * MAX_STATION);
		ZeroMemory(m_stSystemStatus.bOnMC_MotionMoveCustom, sizeof(BOOL) * MAX_STATION * MAX_MOTION_MC_MOVE);

		return;
	}


	/////////////////////////////////////////////////////////////////
	// 스텝 프로세스 ////////////////////////////////////////////////
	switch (nCurrentStep) {

		case	0		:
							nCurrentStep = 100;
							break;


		/////////////////////////////////////////////////////////
		// 모션 컨트롤러 오류 체크 //////////////////////////////
		case	100		:
							nCurrentStep = 110;
							break;


		/////////////////////////////////////////////////////////
		// 서보 모터 오류 체크 //////////////////////////////////
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
		// 현재 모터 위치 모니터링 //////////////////////////////////
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
							// 실제 위치 (외부 인코더 값)
							AxmStatusGetActPos(nCurrentAxisNo, &dblMotionPosition);
							m_stSystemStatus.dblMotionActualPosition[nCurrentAxisNo] = dblMotionPosition;
							
							// 커맨드 위치 (내부 카운트 값)
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
		// 모션 오류 ////////////////////////////////////////////////
		case	900		:
							// 서보 모터 정지
							for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++) {
								
								// 모터 급정지
								Motion_Stop_E(nAxisNo);
								Motion_Stop_E(nAxisNo);

								// 서보 모터 OFF
								AxmSignalServoOn(nAxisNo, DISABLE);
							}

							// 서보 브레이크 설정
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z1);
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z2);
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z3);
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z4);

							// 수동 컨트롤 플래그 해제
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

								// 플래그 해제
								m_stSystemStatus.bOnMotion_CheckServoMotorAlarm	= FALSE;
								m_stSystemStatus.bOnMotion_ReadCurrentPosition	= FALSE;
								for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++)
									m_stSystemStatus.bOnMotion_HomeSearchStart[nAxisNo]	= FALSE;

								nCurrentStep = 0;
							}

							break;
	}


	/////////////////////////////////////////////////////////////////
	// 수동 컨트롤 스텝 프로세스 ////////////////////////////////////
	if (bOnManualControlMode) {

		switch (nMC_CurrentStep) {

			case	0		:
								nMC_CurrentStep = 100;
								break;


			/////////////////////////////////////////////////////////
			// 모터 이동 : 기본 /////////////////////////////////////
			case	100		:
								if (m_stSystemStatus.bOnMC_MotionMove[STATION_1]) {

									m_stSystemStatus.bOnMC_MotionMoveResult[STATION_1] = FALSE;

									nMC_CurrentStep = 110;
									break;
								}

								nMC_CurrentStep = 200;
								break;

			// VZ 홈 위치 이동
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

			// VX, VY 목표 위치 보간 이동
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

			// VZ 목표 위치 이동
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

			// 모터 이동 성공
			case	180		:
								m_stSystemStatus.bOnMC_MotionMoveResult[STATION_1] = TRUE;

								nMC_CurrentStep = 190;
								break;

			// 완료
			case	190		:
								
								m_stSystemStatus.bOnMC_MotionMove[STATION_1] = FALSE;

								nMC_CurrentStep = 200;
								break;


			/////////////////////////////////////////////////////////
			case	200		:
								nMC_CurrentStep = 1000;
								break;


			/////////////////////////////////////////////////////////
			// 모터 이동 : 도어 열기 시작 ///////////////////////////
			case	1000	:
								if (m_stSystemStatus.bOnMC_MotionMoveCustom[STATION_1][MMC_MOVE_OPEN_BEGIN]) {

									m_stSystemStatus.bOnMC_MotionMoveResult[STATION_1] = FALSE;

									nMC_CurrentStep = 1010;
									break;
								}

								nMC_CurrentStep = 1100;
								break;

			// VZ 홈 위치 이동
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

			// VY 홈 위치 이동
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

			// VX, VZ 목표 위치 보간 이동
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

			// VY 목표 위치 이동
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

			// 모터 이동 성공
			case	1080	:
								m_stSystemStatus.bOnMC_MotionMoveResult[STATION_1] = TRUE;

								nMC_CurrentStep = 1090;
								break;

			// 완료
			case	1090	:
								m_stSystemStatus.bOnMC_MotionMoveCustom[STATION_1][MMC_MOVE_OPEN_BEGIN] = FALSE;

								nMC_CurrentStep = 1100;
								break;


			/////////////////////////////////////////////////////////
			// 모터 이동 : 도어 열기 완료 ///////////////////////////
			case	1100	:
								if (m_stSystemStatus.bOnMC_MotionMoveCustom[STATION_1][MMC_MOVE_OPEN_END]) {

									m_stSystemStatus.bOnMC_MotionMoveResult[STATION_1] = FALSE;

									nMC_CurrentStep = 1110;
									break;
								}

								nMC_CurrentStep = 1200;
								break;

			// VX, VY, VZ 목표 위치 보간 이동
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

			// 모터 이동 성공
			case	1180	:
								m_stSystemStatus.bOnMC_MotionMoveResult[STATION_1] = TRUE;

								nMC_CurrentStep = 1190;
								break;

			// 완료
			case	1190	:
								m_stSystemStatus.bOnMC_MotionMoveCustom[STATION_1][MMC_MOVE_OPEN_END] = FALSE;

								nMC_CurrentStep = 1200;
								break;


			/////////////////////////////////////////////////////////
			// 모터 이동 : 도어 닫기 시작 ///////////////////////////
			case	1200	:
								if (m_stSystemStatus.bOnMC_MotionMoveCustom[STATION_1][MMC_MOVE_CLOSE_BEGIN]) {

									m_stSystemStatus.bOnMC_MotionMoveResult[STATION_1] = FALSE;

									nMC_CurrentStep = 1210;
									break;
								}

								nMC_CurrentStep = 1300;
								break;

			// VZ 홈 위치 이동
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

			// VY 홈 위치 이동
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

			// VZ 목표 위치 이동
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

			// VX 목표 위치 이동
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

			// VX, VZ 목표 위치 보간 이동
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

			// VY 목표 위치 이동
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

			// 모터 이동 성공
			case	1280	:
								m_stSystemStatus.bOnMC_MotionMoveResult[STATION_1] = TRUE;

								nMC_CurrentStep = 1290;
								break;

			// 완료
			case	1290	:
								m_stSystemStatus.bOnMC_MotionMoveCustom[STATION_1][MMC_MOVE_CLOSE_BEGIN] = FALSE;

								nMC_CurrentStep = 1300;
								break;


			/////////////////////////////////////////////////////////
			// 모터 이동 : 도어 닫기 완료 ///////////////////////////
			case	1300	:
								if (m_stSystemStatus.bOnMC_MotionMoveCustom[STATION_1][MMC_MOVE_CLOSE_END]) {

									m_stSystemStatus.bOnMC_MotionMoveResult[STATION_1] = FALSE;

									nMC_CurrentStep = 1310;
									break;
								}

								nMC_CurrentStep = 1400;
								break;

			// VX, VY, VZ 목표 위치 보간 이동
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

			// 모터 이동 성공
			case	1380	:
								m_stSystemStatus.bOnMC_MotionMoveResult[STATION_1] = TRUE;

								nMC_CurrentStep = 1390;
								break;

			// 완료
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
			// 조그 이동 ////////////////////////////////////////////
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
	// 오류 발생 ////////////////////////////////////////////////////
	if (bOnError) {

		pstErrorCode = new ERROR_CODE_T;
		if (pstErrorCode) {

			*pstErrorCode = stErrorCode;

			// 알람 이력 다이얼로그에 메세지 전송
			if (m_pSysHistoryDlg)		m_pSysHistoryDlg->SendMessage(UM_HISTORY_ON_ERROR, (WPARAM)pstErrorCode);
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
// 프로세스 : 모션 원점 검출 #1 (ORG, PL, NL) /////////////////////////////////
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
	// 비상 정지 상태 ///////////////////////////////////////////////
	if (m_stSystemStatus.bOnEmergencyStop && !bOnPause[nAxisNo]) {

		bOnPause[nAxisNo]		= TRUE;
		nRecoveryStep[nAxisNo]	= 0;
		nCurrentStep[nAxisNo]	= STEP_EMG;

		return;
	}


	/////////////////////////////////////////////////////////////////
	// 스텝 프로세스 ////////////////////////////////////////////////
	switch (nCurrentStep[nAxisNo]) {

		case	0		:
							nCurrentStep[nAxisNo] = 100;
							break;


		/////////////////////////////////////////////////////////////
		// 대기 /////////////////////////////////////////////////////
		case	100		:
							if (m_stSystemStatus.bOnMotion_HomeSearchStart[nAxisNo]) {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_START].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// 소프트 리미트 해제
								Motion_SetSoftLimit(nAxisNo, FALSE);

								// 플래그 초기화
								m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo] = FALSE;

								// 원점 검출 타임아웃 설정
								LTimerTimeOut[nAxisNo].Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_HOME_SEARCH));

								nCurrentStep[nAxisNo] = 200;
							}

							break;


		/////////////////////////////////////////////////////////////
		// 원점 검출 ////////////////////////////////////////////////
		case	200		:
							nCurrentStep[nAxisNo]++;
							break;

		// 원점 검출 옵션
		case	201		:
							// P-LIMIT 우선 검출 옵션
							if (m_stSystemStatus.bOnMotion_HomeSearchOptionPLStop[nAxisNo]) {
							
								dblMotorSpeed[nAxisNo] = m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch;
								nCurrentStep[nAxisNo]  = 300;
								break;
							}

							// N-LIMIT 우선 검출 옵션
							if (m_stSystemStatus.bOnMotion_HomeSearchOptionNLStop[nAxisNo]) {
							
								dblMotorSpeed[nAxisNo] = m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch;
								nCurrentStep[nAxisNo]  = 400;
								break;
							}
							
							nCurrentStep[nAxisNo] = 210;
							break;

		// HOME 검색
		case	210		:
							AxmSignalReadLimit(nAxisNo, &dwStatusPositive[nAxisNo], &dwStatusNegative[nAxisNo]);
							AxmSignalReadInputBit(nAxisNo, 0, &dwStatusHome[nAxisNo]);
							
							// HOME/LIMIT 센서 감지
							if (dwStatusHome[nAxisNo]) {
							
								dblMotorSpeed[nAxisNo] = m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch;
								nCurrentStep[nAxisNo]  = 270;
							
							} else {
							
								dblMotorSpeed[nAxisNo] = m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch;
								nCurrentStep[nAxisNo]  = 220;
							}

							break;

		// (-) 방향으로 HOME 센서 상승 엣지 검출 후 감속 정지
		case	220		:
							AxmMoveSignalSearch(nAxisNo,
												dblMotorSpeed[nAxisNo] * (-1.0),					// 모터 속도						
												m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration,	// 가감속 시간
												HomeSensor,											// ORG
												SIGNAL_UP_EDGE,										// 상승 엣지
												SLOWDOWN_STOP);										// 감속 정지

							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Speed=%.2f"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_MOVE_NEG_UP_EDGE].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dblMotorSpeed[nAxisNo]);

							nCurrentStep[nAxisNo]++;
							break;

		case	221		:
							// 모터 이동 완료까지 대기
							if (!Motion_Done(nAxisNo))	break;

							// 서보 정지 상태 체크
							AxmStatusReadStop(nAxisNo, &dwStatusEnd[nAxisNo]);
							dwStatusEnd[nAxisNo] &= 0x1FFFF;

							// 모터 속도 설정
							dblMotorSpeed[nAxisNo] = 10.0;

							// 신호 검색 성공 정지
							if (!dwStatusEnd[nAxisNo] || dwStatusEnd[nAxisNo] & QIEND_STATUS_18 || dwStatusEnd[nAxisNo] & QIEND_STATUS_1) {

								// 역방향 리미트 정지 상태
								if (dwStatusEnd[nAxisNo] & QIEND_STATUS_1) {

									// 모터 속도 설정
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

		// (+) 방향으로 HOME 센서 하강 엣지 검출 후 감속 정지
		case	270		:
							AxmMoveSignalSearch(nAxisNo,
												dblMotorSpeed[nAxisNo],								// 모터 속도						
												m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration,	// 가감속 시간
												HomeSensor,											// ORG
												SIGNAL_DOWN_EDGE,									// 하강 엣지
												SLOWDOWN_STOP);										// 감속 정지

							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Speed=%.2f"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_MOVE_POS_DN_EDGE].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dblMotorSpeed[nAxisNo]);

							nCurrentStep[nAxisNo]++;
							break;

		case	271		:
							// 모터 이동 완료까지 대기
							if (!Motion_Done(nAxisNo))	break;

							// 서보 정지 상태 체크
							AxmStatusReadStop(nAxisNo, &dwStatusEnd[nAxisNo]);
							dwStatusEnd[nAxisNo] &= 0x1FFFF;

							// 모터 속도 설정
							dblMotorSpeed[nAxisNo] = 5.0;

							// 신호 검색 성공 정지
							if (!dwStatusEnd[nAxisNo] || dwStatusEnd[nAxisNo] & QIEND_STATUS_18 || dwStatusEnd[nAxisNo] & QIEND_STATUS_0) {

								// 정방향 리미트 정지 상태
								if (dwStatusEnd[nAxisNo] & QIEND_STATUS_0) {

									// 모터 속도 설정
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

		// (-) 방향으로 HOME 센서 상승 엣지 검출 후 급정지
		case	280		:
							AxmMoveSignalSearch(nAxisNo,
												dblMotorSpeed[nAxisNo] * (-1.0),					// 모터 속도
												m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration,	// 가감속 시간
												HomeSensor,											// ORG
												SIGNAL_UP_EDGE,										// 상승 엣지
												EMERGENCY_STOP);									// 급정지

							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Speed=%.2f"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_MOVE_NEG_UP_EDGE].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dblMotorSpeed[nAxisNo]);

							nCurrentStep[nAxisNo]++;
							break;

		case	281		:
							// 모터 이동 완료까지 대기
							if (!Motion_Done(nAxisNo))	break;

							// 서보 정지 상태 체크
							AxmStatusReadStop(nAxisNo, &dwStatusEnd[nAxisNo]);
							dwStatusEnd[nAxisNo] &= 0x1FFFF;

							// 신호 검색 성공 정지
							if (!dwStatusEnd[nAxisNo] || dwStatusEnd[nAxisNo] & QIEND_STATUS_18 || dwStatusEnd[nAxisNo] & QIEND_STATUS_1) {

								// 역방향 리미트 정지 상태
								if (dwStatusEnd[nAxisNo] & QIEND_STATUS_1) {

									// 모터 속도 설정
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

								// 원점 검출 결과 플래그 설정
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

		// HOME 검색 완료
		case	290		:
							// 모터 정지
							AxmMoveSStop(nAxisNo);
							AxmMoveSStop(nAxisNo);

							nCurrentStep[nAxisNo]++;
							break;

		case	291		:
							if (Motion_Done(nAxisNo))
								nCurrentStep[nAxisNo]++;
							
							break;

		case	292		:
							// 서보 모터 : OFF (파나소닉 앰프)
							//AxmSignalServoOn(nAxisNo, DISABLE);
							//LTimerProceed[nAxisNo].Start(1000);

							nCurrentStep[nAxisNo]++;
							break;

		case	293		:
							if (LTimerProceed[nAxisNo].Verify()) {

								// 위치 카운터 초기화
								AxmStatusSetCmdPos(nAxisNo, 0);
								AxmStatusSetActPos(nAxisNo, 0);

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_COMPLETE].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// 서보 모터 : ON (파나소닉 앰프)
								//AxmSignalServoOn(nAxisNo, ENABLE);

								nCurrentStep[nAxisNo] = 900;
							}

							break;


		/////////////////////////////////////////////////////////////
		// 원점 검출 옵션 : P-LIMIT 우선 검출 ///////////////////////
		case	300		:
							nCurrentStep[nAxisNo] = 310;
							break;
							
		// (+) 방향으로 정방향 리미트 센서 상승 엣지 검출 후 급정지
		case	310		:
							AxmMoveSignalSearch(nAxisNo,
												dblMotorSpeed[nAxisNo],								// 모터 속도						
												m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration,	// 가감속 시간
												PosEndLimit,										// 정방향 리미트
												SIGNAL_UP_EDGE,										// 상승 엣지
												EMERGENCY_STOP);									// 급정지

							TestMessage(TRUE,	_T("[AXIS:%02d] %s (P-LIMIT)::%s, Speed=%.2f"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_MOVE_POS_UP_EDGE].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dblMotorSpeed[nAxisNo]);

							nCurrentStep[nAxisNo]++;
							break;

		case	311		:
							// 모터 이동 완료까지 대기
							if (!Motion_Done(nAxisNo))	break;

							// 서보 정지 상태 체크
							AxmStatusReadStop(nAxisNo, &dwStatusEnd[nAxisNo]);
							dwStatusEnd[nAxisNo] &= 0x1FFFF;

							// 신호 검색 성공 정지
							if (!dwStatusEnd[nAxisNo] || dwStatusEnd[nAxisNo] & QIEND_STATUS_18 || dwStatusEnd[nAxisNo] & QIEND_STATUS_0) {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_STOP_LIMIT_POS].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// 원점 검출 결과 플래그 설정
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
		// 원점 검출 옵션 : N-LIMIT 우선 검출 ///////////////////////
		case	400		:
							nCurrentStep[nAxisNo] = 410;
							break;
							
		// (-) 방향으로 정방향 리미트 센서 상승 엣지 검출 후 급정지
		case	410		:
							AxmMoveSignalSearch(nAxisNo,
												dblMotorSpeed[nAxisNo] * (-1.0),					// 모터 속도						
												m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration,	// 가감속 시간
												NegEndLimit,										// 역방향 리미트
												SIGNAL_UP_EDGE,										// 상승 엣지
												EMERGENCY_STOP);									// 급정지

							TestMessage(TRUE,	_T("[AXIS:%02d] %s (N-LIMIT)::%s, Speed=%.2f"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_MOVE_NEG_UP_EDGE].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dblMotorSpeed[nAxisNo]);

							nCurrentStep[nAxisNo]++;
							break;

		case	411		:
							// 모터 이동 완료까지 대기
							if (!Motion_Done(nAxisNo))	break;

							// 서보 정지 상태 체크
							AxmStatusReadStop(nAxisNo, &dwStatusEnd[nAxisNo]);
							dwStatusEnd[nAxisNo] &= 0x1FFFF;

							// 신호 검색 성공 정지
							if (!dwStatusEnd[nAxisNo] || dwStatusEnd[nAxisNo] & QIEND_STATUS_18 || dwStatusEnd[nAxisNo] & QIEND_STATUS_1) {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_STOP_LIMIT_NEG].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// 원점 검출 결과 플래그 설정
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
		// 완료 /////////////////////////////////////////////////////
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

								// 소프트 리미트 설정
								Motion_SetSoftLimit(nAxisNo);
							}

							nCurrentStep[nAxisNo] = 0;
							break;


		/////////////////////////////////////////////////////////////
		// 비상 정지 스텝 ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop) {

									nCurrentStep[nAxisNo]	= nRecoveryStep[nAxisNo];
									bOnPause[nAxisNo]		= FALSE;
								}

								break;
	}


	/////////////////////////////////////////////////////////////////
	// 원점 검출 타임 아웃 체크 /////////////////////////////////////
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
// 프로세스 : 모션 원점 검출 #2 (PL, NL) //////////////////////////////////////
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
	// 비상 정지 상태 ///////////////////////////////////////////////
	if (m_stSystemStatus.bOnEmergencyStop && !bOnPause[nAxisNo]) {

		bOnPause[nAxisNo]		= TRUE;
		nRecoveryStep[nAxisNo]	= 0;
		nCurrentStep[nAxisNo]	= STEP_EMG;

		return;
	}


	/////////////////////////////////////////////////////////////////
	// 스텝 프로세스 ////////////////////////////////////////////////
	switch (nCurrentStep[nAxisNo]) {

		case	0		:
							nCurrentStep[nAxisNo] = 100;
							break;


		/////////////////////////////////////////////////////////////
		// 대기 /////////////////////////////////////////////////////
		case	100		:
							if (m_stSystemStatus.bOnMotion_HomeSearchStart[nAxisNo]) {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_START].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// 소프트 리미트 해제
								Motion_SetSoftLimit(nAxisNo, FALSE);

								// 플래그 초기화
								m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo] = FALSE;

								// 원점 검출 타임아웃 설정
								LTimerTimeOut[nAxisNo].Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_HOME_SEARCH));

								nCurrentStep[nAxisNo] = 200;
							}

							break;


		/////////////////////////////////////////////////////////////
		// 원점 검출 ////////////////////////////////////////////////
		case	200		:
							nCurrentStep[nAxisNo]++;
							break;

		// 원점 검출 옵션
		case	201		:
							// P-LIMIT 우선 검출 옵션
							if (m_stSystemStatus.bOnMotion_HomeSearchOptionPLStop[nAxisNo]) {
							
								dblMotorSpeed[nAxisNo] = m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch;
								nCurrentStep[nAxisNo]  = 300;
								break;
							}

							// N-LIMIT 우선 검출 옵션
							if (m_stSystemStatus.bOnMotion_HomeSearchOptionNLStop[nAxisNo]) {
							
								dblMotorSpeed[nAxisNo] = m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch;
								nCurrentStep[nAxisNo]  = 400;
								break;
							}
							
							nCurrentStep[nAxisNo] = 210;
							break;

		// LIMIT 검색 (N-LIMIT = HOME)
		case	210		:
							AxmSignalReadLimit(nAxisNo, &dwStatusPositive[nAxisNo], &dwStatusNegative[nAxisNo]);
							
							// N-LIMIT 센서 감지
							if (dwStatusNegative[nAxisNo]) {
							
								dblMotorSpeed[nAxisNo] = m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch;
								nCurrentStep[nAxisNo]  = 270;
							
							} else {
							
								dblMotorSpeed[nAxisNo] = m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch;
								nCurrentStep[nAxisNo]  = 220;
							}

							break;

		// (-) 방향으로 N-LIMIT 센서 상승 엣지 검출 후 감속 정지
		case	220		:
							AxmMoveSignalSearch(nAxisNo,
												dblMotorSpeed[nAxisNo] * (-1.0),					// 모터 속도						
												m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration,	// 가감속 시간
												NegEndLimit,										// N-LIMIT
												SIGNAL_UP_EDGE,										// 상승 엣지
												SLOWDOWN_STOP);										// 감속 정지

							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Speed=%.2f"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_MOVE_NEG_UP_EDGE].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dblMotorSpeed[nAxisNo]);

							nCurrentStep[nAxisNo]++;
							break;

		case	221		:
							// 모터 이동 완료까지 대기
							if (!Motion_Done(nAxisNo))	break;

							// 서보 정지 상태 체크
							AxmStatusReadStop(nAxisNo, &dwStatusEnd[nAxisNo]);
							dwStatusEnd[nAxisNo] &= 0x1FFFF;

							// 모터 속도 설정
							dblMotorSpeed[nAxisNo] = 10.0;

							// 신호 검색 성공 정지
							if (!dwStatusEnd[nAxisNo] || dwStatusEnd[nAxisNo] & QIEND_STATUS_18 || dwStatusEnd[nAxisNo] & QIEND_STATUS_1) {

								// 역방향 리미트 정지 상태
								if (dwStatusEnd[nAxisNo] & QIEND_STATUS_1) {

									// 모터 속도 설정
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

		// (+) 방향으로 N-LIMIT 센서 하강 엣지 검출 후 감속 정지
		case	270		:
							AxmMoveSignalSearch(nAxisNo,
												dblMotorSpeed[nAxisNo],								// 모터 속도						
												m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration,	// 가감속 시간
												NegEndLimit,										// N-LIMIT
												SIGNAL_DOWN_EDGE,									// 하강 엣지
												SLOWDOWN_STOP);										// 감속 정지

							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Speed=%.2f"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_MOVE_POS_DN_EDGE].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dblMotorSpeed[nAxisNo]);

							nCurrentStep[nAxisNo]++;
							break;

		case	271		:
							// 모터 이동 완료까지 대기
							if (!Motion_Done(nAxisNo))	break;

							// 서보 정지 상태 체크
							AxmStatusReadStop(nAxisNo, &dwStatusEnd[nAxisNo]);
							dwStatusEnd[nAxisNo] &= 0x1FFFF;

							// 모터 속도 설정
							dblMotorSpeed[nAxisNo] = 5.0;

							// 신호 검색 성공 정지
							if (!dwStatusEnd[nAxisNo] || dwStatusEnd[nAxisNo] & QIEND_STATUS_18 || dwStatusEnd[nAxisNo] & QIEND_STATUS_0) {

								// 정방향 리미트 정지 상태
								if (dwStatusEnd[nAxisNo] & QIEND_STATUS_0) {

									// 모터 속도 설정
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

		// (-) 방향으로 N-LIMIT 센서 상승 엣지 검출 후 급정지
		case	280		:
							AxmMoveSignalSearch(nAxisNo,
												dblMotorSpeed[nAxisNo] * (-1.0),					// 모터 속도
												m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration,	// 가감속 시간
												NegEndLimit,										// N-LIMIT
												SIGNAL_UP_EDGE,										// 상승 엣지
												EMERGENCY_STOP);									// 급정지

							TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s, Speed=%.2f"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_MOVE_NEG_UP_EDGE].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dblMotorSpeed[nAxisNo]);

							nCurrentStep[nAxisNo]++;
							break;

		case	281		:
							// 모터 이동 완료까지 대기
							if (!Motion_Done(nAxisNo))	break;

							// 서보 정지 상태 체크
							AxmStatusReadStop(nAxisNo, &dwStatusEnd[nAxisNo]);
							dwStatusEnd[nAxisNo] &= 0x1FFFF;

							// 신호 검색 성공 정지
							if (!dwStatusEnd[nAxisNo] || dwStatusEnd[nAxisNo] & QIEND_STATUS_18 || dwStatusEnd[nAxisNo] & QIEND_STATUS_1) {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_STOP_LIMIT_NEG].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// 원점 검출 결과 플래그 설정
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

		// HOME 검색 완료
		case	290		:
							// 모터 정지
							AxmMoveSStop(nAxisNo);
							AxmMoveSStop(nAxisNo);

							nCurrentStep[nAxisNo]++;
							break;

		case	291		:
							if (Motion_Done(nAxisNo))
								nCurrentStep[nAxisNo]++;
							
							break;

		case	292		:
							// 서보 모터 : OFF (파나소닉 앰프)
							//AxmSignalServoOn(nAxisNo, DISABLE);
							//LTimerProceed[nAxisNo].Start(1000);

							nCurrentStep[nAxisNo]++;
							break;

		case	293		:
							if (LTimerProceed[nAxisNo].Verify()) {

								// 위치 카운터 초기화
								AxmStatusSetCmdPos(nAxisNo, 0);
								AxmStatusSetActPos(nAxisNo, 0);

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_COMPLETE].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// 서보 모터 : ON (파나소닉 앰프)
								//AxmSignalServoOn(nAxisNo, ENABLE);

								nCurrentStep[nAxisNo] = 900;
							}

							break;


		/////////////////////////////////////////////////////////////
		// 원점 검출 옵션 : P-LIMIT 우선 검출 ///////////////////////
		case	300		:
							nCurrentStep[nAxisNo] = 310;
							break;
							
		// (+) 방향으로 정방향 리미트 센서 상승 엣지 검출 후 급정지
		case	310		:
							AxmMoveSignalSearch(nAxisNo,
												dblMotorSpeed[nAxisNo],								// 모터 속도						
												m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration,	// 가감속 시간
												PosEndLimit,										// 정방향 리미트
												SIGNAL_UP_EDGE,										// 상승 엣지
												EMERGENCY_STOP);									// 급정지

							TestMessage(TRUE,	_T("[AXIS:%02d] %s (P-LIMIT)::%s, Speed=%.2f"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_MOVE_POS_UP_EDGE].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dblMotorSpeed[nAxisNo]);

							nCurrentStep[nAxisNo]++;
							break;

		case	311		:
							// 모터 이동 완료까지 대기
							if (!Motion_Done(nAxisNo))	break;

							// 서보 정지 상태 체크
							AxmStatusReadStop(nAxisNo, &dwStatusEnd[nAxisNo]);
							dwStatusEnd[nAxisNo] &= 0x1FFFF;

							// 신호 검색 성공 정지
							if (!dwStatusEnd[nAxisNo] || dwStatusEnd[nAxisNo] & QIEND_STATUS_18 || dwStatusEnd[nAxisNo] & QIEND_STATUS_0) {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_STOP_LIMIT_POS].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// 원점 검출 결과 플래그 설정
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
		// 원점 검출 옵션 : N-LIMIT 우선 검출 ///////////////////////
		case	400		:
							nCurrentStep[nAxisNo] = 410;
							break;
							
		// (-) 방향으로 정방향 리미트 센서 상승 엣지 검출 후 급정지
		case	410		:
							AxmMoveSignalSearch(nAxisNo,
												dblMotorSpeed[nAxisNo] * (-1.0),					// 모터 속도						
												m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration,	// 가감속 시간
												NegEndLimit,										// 역방향 리미트
												SIGNAL_UP_EDGE,										// 상승 엣지
												EMERGENCY_STOP);									// 급정지

							TestMessage(TRUE,	_T("[AXIS:%02d] %s (N-LIMIT)::%s, Speed=%.2f"),	
												nAxisNo + 1,
												g_stSystemString[SYSSTR_MOTION_HOME_MOVE_NEG_UP_EDGE].szDescription[m_nTypeLanguage],
												g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage],
												dblMotorSpeed[nAxisNo]);

							nCurrentStep[nAxisNo]++;
							break;

		case	411		:
							// 모터 이동 완료까지 대기
							if (!Motion_Done(nAxisNo))	break;

							// 서보 정지 상태 체크
							AxmStatusReadStop(nAxisNo, &dwStatusEnd[nAxisNo]);
							dwStatusEnd[nAxisNo] &= 0x1FFFF;

							// 신호 검색 성공 정지
							if (!dwStatusEnd[nAxisNo] || dwStatusEnd[nAxisNo] & QIEND_STATUS_18 || dwStatusEnd[nAxisNo] & QIEND_STATUS_1) {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_STOP_LIMIT_NEG].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// 원점 검출 결과 플래그 설정
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
		// 완료 /////////////////////////////////////////////////////
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

								// 소프트 리미트 설정
								Motion_SetSoftLimit(nAxisNo);
							}

							nCurrentStep[nAxisNo] = 0;
							break;


		/////////////////////////////////////////////////////////////
		// 비상 정지 스텝 ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop) {

									nCurrentStep[nAxisNo]	= nRecoveryStep[nAxisNo];
									bOnPause[nAxisNo]		= FALSE;
								}

								break;
	}


	/////////////////////////////////////////////////////////////////
	// 원점 검출 타임 아웃 체크 /////////////////////////////////////
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
// 프로세스 : 모션 원점 검출 #3 (AXT 구동) ////////////////////////////////////
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
	// 비상 정지 상태 ///////////////////////////////////////////////
	if (m_stSystemStatus.bOnEmergencyStop && !bOnPause[nAxisNo]) {

		bOnPause[nAxisNo]		= TRUE;
		nRecoveryStep[nAxisNo]	= 0;
		nCurrentStep[nAxisNo]	= STEP_EMG;

		return;
	}


	/////////////////////////////////////////////////////////////////
	// 스텝 프로세스 ////////////////////////////////////////////////
	switch (nCurrentStep[nAxisNo]) {

		case	0		:
							nCurrentStep[nAxisNo] = 100;
							break;


		/////////////////////////////////////////////////////////////
		// 대기 /////////////////////////////////////////////////////
		case	100		:
							if (m_stSystemStatus.bOnMotion_HomeSearchStart[nAxisNo]) {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_START].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// 소프트 리미트 해제
								Motion_SetSoftLimit(nAxisNo, FALSE);

								// 플래그 초기화
								m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo] = FALSE;

								// 원점 검출 타임아웃 설정
								LTimerTimeOut[nAxisNo].Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_HOME_SEARCH));

								nCurrentStep[nAxisNo] = 110;
							}

							break;

		// 원점 검출 사용 유무
		case	110		:
							if (m_SystemConfig.UseMotionHomeSearch(nAxisNo)) {

								// BY1, BY2, HZ1, HZ2, LY1, LY2, HOME 위치 우선 이동
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

		// HOME 위치로 이동
		case	120		:
							{
								DWORD	dwStatusHome	= 0;


								// HOME 센서 체크
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
							
								// 서보 정지 상태 체크
								AxmStatusReadStop(nAxisNo, &dwStatusEnd[nAxisNo]);
								dwStatusEnd[nAxisNo] &= 0x1FFFF;

								// 신호 검색 성공 정지
								if (!dwStatusEnd[nAxisNo] || dwStatusEnd[nAxisNo] & QIEND_STATUS_18 || dwStatusEnd[nAxisNo] & QIEND_STATUS_1) {

									// 역방향 리미트 정지 상태
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
		// 원점 검출 ////////////////////////////////////////////////
		case	200		:
							nCurrentStep[nAxisNo] = 210;
							break;

		// 파라미터 설정
		case	210		:
							{
								// 메소드 설정
								AxmHomeSetMethod(nAxisNo,			
												 DIR_CCW,			// 초기 구동 방향
												 nSignalNo,			// 원점 신호
												 0,					// Z-Phas 사용 유무
												 500,				// 원점 검색 후 카운터 리셋 대기 시간
												 0);				// 원점 검색 후 오프셋 이동 위치
								
								// 속도 설정
								AxmHomeSetVel(nAxisNo, 
											  m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch,			// 초기 구동 속도 (원점 = OFF)
											  m_stMotionAxisInfo[nAxisNo].dblSpeedHomeSearch * 0.5,		// 초기 구동 속도 (원점 = ON)
											  10.0,														// 2차 검색 검출 속도
											  1.0,														// 마지막 검색 속도
											  m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration,			// 가감속 속도 (원점 = OFF)
											  m_stMotionAxisInfo[nAxisNo].dblTimeAcceleration);			// 가감속 속도 (원점 = ON)

								nCurrentStep[nAxisNo] = 220;		
							}

							break;

		// 원점 검색 시작
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

		// HOME 검색 완료
		case	290		:
							// 모터 정지
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
		// 완료 /////////////////////////////////////////////////////
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

		// 홈 위치 이동
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

		// 완료
		case	990		:
							// 소프트 리미트 설정
							Motion_SetSoftLimit(nAxisNo);

							nCurrentStep[nAxisNo] = 0;
							break;


		/////////////////////////////////////////////////////////////
		// 비상 정지 스텝 ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop) {

									nCurrentStep[nAxisNo]	= nRecoveryStep[nAxisNo];
									bOnPause[nAxisNo]		= FALSE;
								}

								break;
	}


	/////////////////////////////////////////////////////////////////
	// 원점 검출 타임 아웃 체크 /////////////////////////////////////
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
// 프로세스 : 모션 원점 검출 #4 (SMC 스테핑) //////////////////////////////////
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
	// 비상 정지 상태 ///////////////////////////////////////////////
	if (m_stSystemStatus.bOnEmergencyStop && !bOnPause[nAxisNo]) {

		bOnPause[nAxisNo]		= TRUE;
		nRecoveryStep[nAxisNo]	= 0;
		nCurrentStep[nAxisNo]	= STEP_EMG;

		return;
	}


	/////////////////////////////////////////////////////////////////
	// 스텝 프로세스 ////////////////////////////////////////////////
	switch (nCurrentStep[nAxisNo]) {

		case	0		:
							nCurrentStep[nAxisNo] = 100;
							break;


		/////////////////////////////////////////////////////////////
		// 대기 /////////////////////////////////////////////////////
		case	100		:
							if (m_stSystemStatus.bOnMotion_HomeSearchStart[nAxisNo]) {

								TestMessage(TRUE,	_T("[AXIS:%02d] %s::%s"),	
													nAxisNo + 1,
													g_stSystemString[SYSSTR_MOTION_HOME_START].szDescription[m_nTypeLanguage],
													g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

								// 소프트 리미트 해제
								Motion_SetSoftLimit(nAxisNo, FALSE);

								// 플래그 초기화
								m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo] = FALSE;

								// 원점 검출 타임아웃 설정
								LTimerTimeOut[nAxisNo].Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_HOME_SEARCH));

								nCurrentStep[nAxisNo] = 110;
							}

							break;

		// 원점 검출 사용 유무
		case	110		:
							if (m_SystemConfig.UseMotionHomeSearch(nAxisNo)) {
							
								nCurrentStep[nAxisNo] = 200;
								break;
							}

							m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo] = TRUE;

							nCurrentStep[nAxisNo] = 900;
							break;


		/////////////////////////////////////////////////////////////
		// 원점 검출 ////////////////////////////////////////////////
		case	200		:
							nCurrentStep[nAxisNo] = 210;

		// 준비 작업
		case	210		:
							// 원점 검출 시작 신호 해제
							AxmSignalWriteOutputBit(nAxisNo, UIO_OUT3, DISABLE);

							LTimerProceed[nAxisNo].Start(2000);

							nCurrentStep[nAxisNo]++;
							break;

		case	211		:
							if (LTimerProceed[nAxisNo].Verify())
								nCurrentStep[nAxisNo] = 220;

							break;

		// 알람 리셋
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

		// 준비 신호 대기
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

		// 원점 검색 시작
		case	240		:
							{
								// 원점 검출 시작 신호 출력
								AxmSignalWriteOutputBit(nAxisNo, UIO_OUT3, ENABLE);

								nCurrentStep[nAxisNo]++;		
							}

							break;

		case	241		:
							{
								DWORD	dwStatus	= 0;


								// 홈 시그널 검출
								AxmSignalReadInputBit(nAxisNo, 0, &dwStatus);
								if (dwStatus) {
								
									m_stSystemStatus.bOnMotion_ResultHomeSearch[nAxisNo] = TRUE;

									// 원점 검출 시작 신호 해제
									AxmSignalWriteOutputBit(nAxisNo, UIO_OUT3, DISABLE);

									nCurrentStep[nAxisNo] = 290;
								}

								// 원점 검출 중지
								if (!m_stSystemStatus.bOnMotion_HomeSearchStart[nAxisNo]) {

									// 원점 검출 시작 신호 해제
									AxmSignalWriteOutputBit(nAxisNo, UIO_OUT3, DISABLE);

									nCurrentStep[nAxisNo] = 0;
								}

								// 알람 체크
								AxmSignalReadServoAlarm(nAxisNo, &dwStatus);
								if (dwStatus) {

									NormalMessage(TRUE,	_T("[AXIS:%02d] SERVO ALARM STATUS::%s"),	
														nAxisNo + 1,
														g_stMotionAxisName[nAxisNo].stDescription.szDescription[m_nTypeLanguage]);

									nCurrentStep[nAxisNo] = 210;
								}
							}

							break;

		// HOME 검색 완료
		case	290		:
							// 모터 정지
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
		// 완료 /////////////////////////////////////////////////////
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

		// 홈 위치 이동
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

		// 완료
		case	990		:
							// 소프트 리미트 설정
							Motion_SetSoftLimit(nAxisNo);

							nCurrentStep[nAxisNo] = 0;
							break;


		/////////////////////////////////////////////////////////////
		// 비상 정지 스텝 ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop) {

									nCurrentStep[nAxisNo]	= nRecoveryStep[nAxisNo];
									bOnPause[nAxisNo]		= FALSE;
								}

								break;
	}


	/////////////////////////////////////////////////////////////////
	// 원점 검출 타임 아웃 체크 /////////////////////////////////////
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
// 프로세스 : 장비 초기화 /////////////////////////////////////////////////////
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
	// 변수 초기화 //////////////////////////////////////////////////
	ZeroMemory(&stErrorCode, sizeof(ERROR_CODE_T));
	ZeroMemory(&stParamUI, sizeof(UI_PARAM_UPDATE_T));


	/////////////////////////////////////////////////////////////////
	// 비상 정지 상태 ///////////////////////////////////////////////
	if (m_stSystemStatus.bOnEmergencyStop && !bOnPause) {

		bOnPause		= TRUE;
		nRecoveryStep	= 0;
		nCurrentStep	= STEP_EMG;

		return	NULL;
	}


	/////////////////////////////////////////////////////////////////
	// 스텝 프로세스 ////////////////////////////////////////////////
	switch (nCurrentStep) {

		/////////////////////////////////////////////////////////////
		// 대기 /////////////////////////////////////////////////////
		case	0		:
							if (m_stSystemStatus.bOnMachineInitialize) {

								TestMessage(TRUE, _T("%s"), g_stSystemString[SYSSTR_MC_INIT_START].szDescription[m_nTypeLanguage]);

								// 플래그 초기화
								m_stSystemStatus.bOnMotion_CheckServoMotorAlarm = FALSE;
								for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++)
									m_stSystemStatus.bOnMotion_HomeSearchStart[nAxisNo]	= FALSE;

								// 사용자 메세지 설정
								ClearUserMessage();
								m_stSystemStatus.nCurrentUserMessage = UMSG_WARN_MACHINE_INITIALIZING;

								// 장비 초기화 결과 초기화
								m_stSystemStatus.bResultMachineInitialize = FALSE;

								// 비프음 1회 출력
								m_stSystemStatus.nBeepCount = 1;

								nRetryCount  = 0;
								nCurrentStep = STEP_INIT_INIT;
							}

							break;	


		/////////////////////////////////////////////////////////////
		// 초기화 준비 //////////////////////////////////////////////
		case	STEP_INIT_INIT	:
									nCurrentStep = 110;
									break;

		// 장비 파츠 플래그 초기화
		case	110		:
							ZeroMemory(m_stSystemStatus.bOnMP_Error, sizeof(BOOL) * MAX_STATION);
							ZeroMemory(m_stSystemStatus.bOnSCP_MoveParts, sizeof(BOOL) * MAX_STATION * MAX_STATION_CONTROL);

							nCurrentStep = 190;
							break;

		// 완료
		case	190		:
							nCurrentStep = STEP_INIT_DEVICE;
							break;


		/////////////////////////////////////////////////////////////
		// 디바이스 초기화 //////////////////////////////////////////
		case	STEP_INIT_DEVICE	:
										nCurrentStep = 4200;
										break;

		// 디지털 멀티미터 초기화
		case	4200	:
							nIndexDevice = 0;

							nCurrentStep = 4210;
							break;

		case	4210	:
							TestMessage(TRUE,	_T("%s (DIGITAL MULTIMETER)"),	
												g_stSystemString[SYSSTR_MC_INIT_MEAS_DEVICE_START].szDescription[m_nTypeLanguage]);

							// 디바이스 체크
							if (m_stSystemStatus.nDeviceStatus[SD_DEV_DMM] != DS_NORMAL) {
							
								nCurrentStep = STEP_INIT_ERROR_DEV_DMM;
								break;
							}

							nCurrentStep = 4220;
							break;

		case	4220	:
							// 오류 해제
							if (!m_devDMM.SetSystemCommand(FLKDMM_SYS_CLS)) {

								nCurrentStep = STEP_INIT_ERROR_DEV_DMM;
								break;
							}

							LTimerSteady.Start(FLKDMM_DLY_SETUP);
							nCurrentStep = 4230;
							break;

		case	4230	:
							// 측정 모드 : DCV
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
							// 리모트 모드 설정
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

		// 완료
		case	4900	:
							nCurrentStep = STEP_INIT_STN;
							break;


		/////////////////////////////////////////////////////////////
		// 공정 초기화 //////////////////////////////////////////////
		case	STEP_INIT_STN	:
									TestMessage(TRUE, _T("%s"), g_stSystemString[SYSSTR_MC_INIT_STATION_START].szDescription[m_nTypeLanguage]);

									nCurrentStep = 210;
									break;

		case	210		:
							nCurrentStep = 230;
							break;
							
		// 공정 초기화
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
																
								// 모든 스테이션이 완료되면 다음 스텝으로 진행
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

		// 완료
		case	290		:
							TestMessage(TRUE, _T("%s"), g_stSystemString[SYSSTR_MC_INIT_STATION_COMPLETE].szDescription[m_nTypeLanguage]);

							nCurrentStep = STEP_INIT_MOTION;
							break;


		/////////////////////////////////////////////////////////////
		// 모션 초기화 //////////////////////////////////////////////
		case	STEP_INIT_MOTION	:
										TestMessage(TRUE, _T("%s"), g_stSystemString[SYSSTR_MC_INIT_MOTION_START].szDescription[m_nTypeLanguage]);

										nCurrentStep++;
										break;

		// 모션 컨트롤러 리셋
		case	401		:
							{
								// 모션 컨트롤러 재 연결
								//if (AxlIsOpened())	AxlClose();

								//LONG	lResult	= AxlOpen(7);
								//if (lResult == AXT_RT_SUCCESS) {

								//	nCurrentStep[nCHANNEL_NO]++;

								//} else {

								//	SErrorMessage(FALSE, _T("모션 컨트롤러를 리셋할 수 없습니다."));
								//	nCurrentStep[nCHANNEL_NO] = STEP_INIT_ERROR_MOTION;
								//}

								nCurrentStep++;
							}

							break;

		case	402		:
							// Z축 브레이커 설정
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z1);
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z2);
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z3);
							//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z4);
							//LTimerProceed.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));

							nCurrentStep = 410;
							break;

		// 서보 앰프 전원 공급 해제
		case	410		:
							if (LTimerProceed.Verify()) {

								SetDOStatus(DO_OFF, DO_SSR_SERVO_POWER_ON);
								LTimerProceed.Start(3000);
								
								nCurrentStep++;
							}

							break;

		// 모션 컨트롤러 레지스터 초기화
		case	411		:
							if (LTimerProceed.Verify()) {

								// 모션 컨트롤러 레지스터 초기화
								Motion_Initialize();
								LTimerProceed.Start(100);
								
								nCurrentStep++;
							}

							break;

		// 서보 앰프 전원 공급 설정
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

		// 서보 앰프 ALARM RESET ON
		case	414		:
							if (LTimerProceed.Verify()) {

								for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++)
									AxmSignalServoAlarmReset(nAxisNo, ENABLE);

								LTimerProceed.Start(500);
								nCurrentStep++;
							}

							break;

		// 서보 앰프 ALARM RESET OFF
		case	415		:
							if (LTimerProceed.Verify()) {

								for (UINT nAxisNo = 0; nAxisNo < MAX_MOTION_AXIS; nAxisNo++)
									AxmSignalServoAlarmReset(nAxisNo, DISABLE);

								LTimerProceed.Start(500);
								nCurrentStep = 420;
							}

							break;

		// 서보 모터 ON
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

								// Z축 브레이커 해제
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

		// 완료
		case	490		:
							// 서보 모터 알람 상태 체크 시작
							m_stSystemStatus.bOnMotion_CheckServoMotorAlarm = TRUE;

							nCurrentStep = STEP_INIT_STN_LOCK;
							break;


		/////////////////////////////////////////////////////////////
		// 작업존 인터록 ////////////////////////////////////////////
		case	STEP_INIT_STN_LOCK	:	
										nCurrentStep = 510;
										break;

		// 인터록 체크
		case	510		:
							nCurrentStep = 590;
							break;

		case	590		:
							nCurrentStep = STEP_INIT_HOME_SEARCH;
							break;


		/////////////////////////////////////////////////////////////
		// 원점 검출 ////////////////////////////////////////////////
		case	STEP_INIT_HOME_SEARCH	:
											nCurrentStep = 610;
											break;

		case	610		:
							// 원점 검출 결과 플래그 초기화
							for (UINT nIndex = 0; nIndex < MAX_MOTION_AXIS; nIndex++) {

								m_stSystemStatus.bOnMotion_HomeSearchStart[nIndex]			= FALSE;
								m_stSystemStatus.bOnMotion_ResultHomeSearch[nIndex]			= FALSE;
								m_stSystemStatus.bOnMotion_HomeSearchOptionPLStop[nIndex]	= FALSE;
								m_stSystemStatus.bOnMotion_HomeSearchOptionNLStop[nIndex]	= FALSE;
							}

							// 플래그 초기화
							bIsStepMoveHome = FALSE;

							nCurrentStep = 620;
							break;

		// VZ 원점 검출 시작
		case	620		:
							m_stSystemStatus.bOnMotion_HomeSearchStart[MOTION_RVZ]	= TRUE;

							nCurrentStep++;
							break;

		case	621		:
							if (!m_stSystemStatus.bOnMotion_HomeSearchStart[MOTION_RVZ]) {
							
								// 원점 검출 실패
								if (!m_stSystemStatus.bOnMotion_ResultHomeSearch[MOTION_RVZ]) {
								
									nCurrentStep = STEP_INIT_ERROR_MOTION;
									break;
								}

								nCurrentStep = 630;
							}

							break;

		// VY 원점 검출 시작
		case	630		:
							m_stSystemStatus.bOnMotion_HomeSearchStart[MOTION_RVY]	= TRUE;

							nCurrentStep++;
							break;

		case	631		:
							if (!m_stSystemStatus.bOnMotion_HomeSearchStart[MOTION_RVY]) {
							
								// 원점 검출 실패
								if (!m_stSystemStatus.bOnMotion_ResultHomeSearch[MOTION_RVY]) {
								
									nCurrentStep = STEP_INIT_ERROR_MOTION;
									break;
								}

								nCurrentStep++;
							}

							break;

		case	632		:
							// VY 대기 위치 이동
							Motion_MoveTo(MOTION_RVY, 
										  m_stMotionAxisInfo[MOTION_RVY].dblCustomPosition[MAI_CPOS_HOME], 
										  m_stMotionAxisInfo[MOTION_RVY].dblSpeedBase);

							nCurrentStep++;
							break;

		case	633		:
							if (Motion_Done(MOTION_RVY))
								nCurrentStep = 640;

							break;

		// VX 원점 검출 시작
		case	640		:
							m_stSystemStatus.bOnMotion_HomeSearchStart[MOTION_RVX]	= TRUE;

							nCurrentStep++;
							break;

		case	641		:
							if (!m_stSystemStatus.bOnMotion_HomeSearchStart[MOTION_RVX]) {
							
								// 원점 검출 실패
								if (!m_stSystemStatus.bOnMotion_ResultHomeSearch[MOTION_RVX]) {
								
									nCurrentStep = STEP_INIT_ERROR_MOTION;
									break;
								}

								nCurrentStep = 680;
							}

							break;

		// 기본 대기 위치로 이동
		case	680		:
							nCurrentStep++;
							break;

		case	681		:
							nCurrentStep = 690;
							break;

		// 완료
		case	690		:
							TestMessage(TRUE, _T("%s"), g_stSystemString[SYSSTR_MC_INIT_MOTION_COMPLETE].szDescription[m_nTypeLanguage]);

							nCurrentStep = STEP_INIT_STN_UNLOCK;
							break;


		/////////////////////////////////////////////////////////////
		// 작업존 인터록 해제 ///////////////////////////////////////
		case	STEP_INIT_STN_UNLOCK	:		
											nCurrentStep = 790;
											break;

		case	790		:
							nCurrentStep = STEP_INIT_SUCCESS;
							break;


		/////////////////////////////////////////////////////////////
		// 초기화 실패 //////////////////////////////////////////////
		case	STEP_INIT_ERROR	:
									// 비프음 2회 출력
									m_stSystemStatus.nBeepCount = 2;

									nCurrentStep = 1010;
									break;

		case	1010	:
							TestMessage(TRUE, _T("%s"), g_stSystemString[SYSSTR_MC_INIT_FAILURE].szDescription[m_nTypeLanguage]);

							nCurrentStep = STEP_INIT_DONE;
							break;

		// 디바이스 오류
		case	STEP_INIT_ERROR_DEV_BATT	:
		case	STEP_INIT_ERROR_DEV_DMM		:
												TestMessage(TRUE, _T("%s"), g_stSystemString[SYSSTR_MC_INIT_MEAS_DEVICE_FAILURE].szDescription[m_nTypeLanguage]);

												nCurrentStep = STEP_INIT_ERROR;
												break;

		// 스테이션 오류
		case	STEP_INIT_ERROR_STATION	:
											TestMessage(TRUE, _T("%s"), g_stSystemString[SYSSTR_MC_INIT_STATION_FAILURE].szDescription[m_nTypeLanguage]);

											nCurrentStep = STEP_INIT_ERROR;
											break;

		// 인터록 오류
		case	STEP_INIT_ERROR_INTERLK	:
											TestMessage(TRUE, _T("%s"),	g_stSystemString[SYSSTR_MC_INIT_INTLK_FAILURE].szDescription[m_nTypeLanguage]);

											nCurrentStep = STEP_INIT_ERROR;
											break;

		// 파츠 오류
		case	STEP_INIT_ERROR_PARTS	:
											TestMessage(TRUE, _T("%s"),	g_stSystemString[SYSSTR_MC_INIT_SEQUENCE_FAILURE].szDescription[m_nTypeLanguage]);

											// 오류 코드 설정
											stErrorCode.nErrorCode	= ERROR_MACHINE_SEQUENCE;
											stErrorCode.nProcessID	= PROCESS_INIT;
											bOnError				= TRUE;

											nCurrentStep = STEP_INIT_ERROR;
											break;

		// 모션 오류
		case	STEP_INIT_ERROR_MOTION	:
											TestMessage(TRUE, _T("%s"),	g_stSystemString[SYSSTR_MC_INIT_MOTION_FAILURE].szDescription[m_nTypeLanguage]);

											// 서보 모터 정지
											for (UINT nAxisNo = MOTION_AXIS_1; nAxisNo < MAX_MOTION_AXIS; nAxisNo++) {

												Motion_Stop_E(nAxisNo);
												Motion_Stop_E(nAxisNo);
												AxmSignalServoOn(nAxisNo, DISABLE);
											}

											// Z축 브레이커 설정
											//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z1);
											//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z2);
											//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z3);
											//SetDOStatus(DO_OFF, DO_RLY_SERVO_BREAK_OFF_Z4);

											nCurrentStep = STEP_INIT_ERROR;
											break;
	

		/////////////////////////////////////////////////////////////
		// 초기화 성공 //////////////////////////////////////////////
		case	STEP_INIT_SUCCESS	:
										// 비프음 1회 출력
										m_stSystemStatus.nBeepCount = 1;

										nCurrentStep = 2010;
										break;

		case	2010	:
							// 장비 초기화 결과 설정
							m_stSystemStatus.bResultMachineInitialize = TRUE;

							TestMessage(TRUE, _T("%s"), g_stSystemString[SYSSTR_MC_INIT_COMPLETE].szDescription[m_nTypeLanguage]);

							nCurrentStep = STEP_INIT_DONE;
							break;


		/////////////////////////////////////////////////////////////
		// 초기화 완료 //////////////////////////////////////////////
		case	STEP_INIT_DONE	:
									m_stSystemStatus.bOnMachineInitialize = FALSE;

									// 사용자 메세지 초기화
									ClearUserMessage();

									// 완료 메세지 전송
									m_pMainWnd->PostMessage(UM_MAIN_MACHINE_INITIALIZE, FALSE);

									nCurrentStep = 0;
									break;


		/////////////////////////////////////////////////////////////
		// 비상 정지 스텝 ///////////////////////////////////////////
		case	STEP_EMG	:
								// 플래그 초기화
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
	// 업데이트 UI //////////////////////////////////////////////////
	if (bOnUpdateUI) {

		PUI_PARAM_UPDATE_T		pstParamUI	= new UI_PARAM_UPDATE_T;
		if (pstParamUI) {

			*pstParamUI = stParamUI;

			if (m_pMainWnd && m_pMainWnd->GetSafeHwnd())
				m_pMainWnd->PostMessage(UM_MAIN_UPDATE_UI, (WPARAM)pstParamUI);
		}
	}


	/////////////////////////////////////////////////////////////////
	// 오류 발생 ////////////////////////////////////////////////////
	if (bOnError) {

		pstErrorCode = new ERROR_CODE_T;
		if (pstErrorCode)	*pstErrorCode = stErrorCode;
	}


	/////////////////////////////////////////////////////////////////
	// 스텝 모니터링 ////////////////////////////////////////////////
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
// 프로세스 : 메인 작업 (프로시저) ///////////////////////////////////////////
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
	// 프로세스 데이터 초기화 ///////////////////////////////////////
	ProcessDataInitialize(PROCESS);


	/////////////////////////////////////////////////////////////////
	// 자동 운전 시작/정지 초기화 ///////////////////////////////////
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
	// 장비 초기화 //////////////////////////////////////////////////
	if (CheckProcessMachineInitialize(PROCESS))
		return	NULL;


	/////////////////////////////////////////////////////////////////
	// 수동 제어 모드 ///////////////////////////////////////////////
	PROCESS.bOnManualControlMode = m_stSystemStatus.bIsManualControl[nSTATION_NO];


	/////////////////////////////////////////////////////////////////
	// 비상/일시 정지 상태 //////////////////////////////////////////
	if (CheckProcessEmergencyStop(PROCESS))					return	NULL;
	if (CheckProcessOperatingPause(nSTATION_NO, PROCESS))	return	NULL;


	/////////////////////////////////////////////////////////////////
	// 스텝 프로세스 ////////////////////////////////////////////////
	switch (PROCESS.nCurrentStep) {

		case	0		:
							PROCESS.nCurrentStep = 10;
							break;

		// 시스템 체크
		case	10		:
							if (IsSystemReady()) {
							
								PROCESS.nCurrentStep = 20;
							}
								
							break;

		// 프로세스 초기화
		case	20		:
							m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]				= FALSE;
							m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
							m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
							m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
							m_stSystemStatus.bIsMainProcessInitialized[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;

							PROCESS.nCurrentStep = 90;
							break;

		// 완료
		case	90		:
							PROCESS.nCurrentStep = STEP_WORK_STANDBY;
							break;


		/////////////////////////////////////////////////////////////
		// 초기화 ///////////////////////////////////////////////////
		case	STEP_WORK_INIT	:
									PROCESS.nCurrentStep = 110;
									break;

		// 플래그 초기화
		case	110		:
							PROCESS.nCurrentStep = 130;
							break;

		// 제어 신호 초기화
		case	130		:
							// 연결 릴레이 초기화
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

		// 공급 전압 해제
		case	140		:
							// 전원 공급 해제
							bSetupState				= FALSE;
							PROCESS.nCurrentStep	= STEP_WORK_SUB_SET_PS;
							PROCESS.nReturn03Step	= 150;
							break;

		// CAN 통신 초기화
		case	150		:
							// 통신 정보 초기화
							CAN_InitInformation();

							// 시그널 데이터 초기화
							CAN_ClearSignalValue();
							
							PROCESS.nCurrentStep = 190;
							break;

		// 완료
		case	190		:
							// 초기화 완료 플래그 설정
							m_stSystemStatus.bIsMainProcessInitialized[nSTATION_NO][nSTATION_SUB_NO] = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn01Step;
							break;


		/////////////////////////////////////////////////////////////
		// 대기 /////////////////////////////////////////////////////
		case	STEP_WORK_STANDBY	:
										PROCESS.nCurrentStep = 220;
										break;

		// 프로세스 대기
		case	220		:
							if (m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]) {

								m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;
								m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;

								PROCESS.nCurrentStep = 230;
								break;
							}

							PROCESS.nCurrentStep = STEP_WORK_STANDBY;
							break;
							
		// 모델 프로파일 로드
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

							SErrorMessage(TRUE, _T("[S%02d/%s] 모델 정보를 로드할 수 없습니다."),	nSTATION_NO, 
																									g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

							PROCESS.nCurrentStep = STEP_WORK_ERROR_SYSTEM;
							break;

		// 초기화
		case	280		:
							PROCESS.nCurrentStep	= STEP_WORK_INIT;
							PROCESS.nReturn01Step	= 290;
							break;

		// 완료
		case	290		:
							PROCESS.nCurrentStep = STEP_WORK_START;
							break;


		/////////////////////////////////////////////////////////////
		// 작업 /////////////////////////////////////////////////////
		case	STEP_WORK_START	:
									PROCESS.nCurrentStep = 410;
									break;

		// 준비
		case	410		:
							// 작업 정보 초기화
							bResultProcess				= TRUE;
							PROCESS.bOnInstantStop		= FALSE;
							PROCESS.nCurrentProcedureNo	= 0;
							PROCESS.nRetryCount			= 0;

							PROCESS.nCurrentStep = 420;
							break;

		// 작업 완료 체크
		case	420		:
							{
								BOOL	bIsStopProcess	= FALSE;

								// 작업 정지
								if (m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO])
									bIsStopProcess = TRUE;

								// 검사 완료
								if (PROCESS.nCurrentProcedureNo >= m_stTestProcedureHeader.nNumProcedureData)
									bIsStopProcess = TRUE;

								// 불합격 판정 시 검사 안함
								if (PROCESS.bOnInstantStop || (PROCESS.pstModelProfileConfig)->bWorkOption[WOPT_NG_STOP]) {
							
									if (!bResultProcess)	bIsStopProcess = TRUE;
								}

								PROCESS.nCurrentStep = bIsStopProcess ? 490 : 450;
							}

							break;

		// 1 행정 작업
		case	450		:
							PROCESS.nCurrentStep	= STEP_WORK_CYCLE;
							PROCESS.nReturn01Step	= 451;
							break;

		case	451		:
							PROCESS.nCurrentProcedureNo++;

							PROCESS.nCurrentStep = 420;
							break;

		// 완료
		case	490		:
							// 연결 릴레이 초기화
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

							// 전원 공급 해제
							bSetupState				= FALSE;
							PROCESS.nCurrentStep	= STEP_WORK_SUB_SET_PS;
							PROCESS.nReturn03Step	= STEP_WORK_DONE;
							break;


		/////////////////////////////////////////////////////////////
		// 완료 /////////////////////////////////////////////////////
		case	STEP_WORK_DONE	:
									PROCESS.nCurrentStep = 590;
									break;

		// 완료
		case	590		:
							// 메인 프로세스 완료
							m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;
							m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]	= bResultProcess;

							PROCESS.nCurrentStep = STEP_WORK_STANDBY;
							break;

		
		/////////////////////////////////////////////////////////////
		// 1 행정 작업 //////////////////////////////////////////////
		case	STEP_WORK_CYCLE	:
									PROCESS.nCurrentStep = 1010;
									break;

		case	1010	:
							// 도어 열림 체크
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							// 1 행정 플래그 설정
							PROCESS.bOnProcessCycle = TRUE;

							// 플래그 초기화
							PROCESS.nRetryCount			= 0;
							PROCESS.nResultInspection	= T_RESULT_SUCCESS;
							PROCESS.bOnUpdateWorkSheet	= FALSE;
														
							PROCESS.nCurrentStep = 1100;
							break;

		// 프로시저 커맨드
		case	1100	:
							{
								pstWorkProcedureData = &m_pstTestProcedureData[PROCESS.nCurrentProcedureNo];
								strParameters.Empty();
								strDataValue.Empty();

								// 최종 검사 데이터 초기화
								ZeroMemory(&stFunctionTestData, sizeof(FUNC_TEST_DATA_T));
								_tcscpy_s(stFunctionTestData.szName, MAX_STRINPUT_S, pstWorkProcedureData->szName);
								stFunctionTestData.nCommand	= pstWorkProcedureData->nCommand;

								// 커맨드 분기
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

		// 완료
		case	1900	:
							// 1 행정 플래그 해제
							PROCESS.bOnProcessCycle = FALSE;

							// 프로세스 결과 설정
							bResultProcess &= PROCESS.nResultInspection == T_RESULT_SUCCESS ? TRUE : FALSE;

							// 최종 검사 데이터 설정
							_tcscpy_s(stFunctionTestData.szParameters, MAX_STRVALUE, strParameters);
							m_arrFuncTestData.Add(stFunctionTestData);

							// 업데이트 UI
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
		// 서브 스텝 : 커맨드 - 환경 설정 ///////////////////////////
		case	STEP_WORK_SUB_CMD_SETUP_ENV	:
												MessageWindow(cDEBUG, _T("PROC::CMD_SETUP_ENV"));

												PROCESS.nCurrentStep = 2010;
												break;

		// 초기화
		case	2010	:
							PROCESS.nCurrentStep = 2050;
							break;

		// 공급 전압/전류 설정
		case	2050	:
							if (pstWorkProcedureData->bEnableValue[TPRD_DATA_VALUE_SET_ENV_SUPPLY_VOLTAGE] ||
								pstWorkProcedureData->bEnableValue[TPRD_DATA_VALUE_SET_ENV_SUPPLY_CURRENT]) {
								
								dblSetupValueVoltage	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_SET_ENV_SUPPLY_VOLTAGE];
								dblSetupValueCurrent	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_SET_ENV_SUPPLY_CURRENT];
								bSetupState				= TRUE;
								PROCESS.nCurrentStep	= STEP_WORK_SUB_SET_PS;
								PROCESS.nReturn03Step	= 2060;

								// 파라미터 설정
								strParameters.AppendFormat(_T("PS=%.2f/%.2f "), dblSetupValueVoltage, dblSetupValueCurrent);
								break;
							}

							PROCESS.nCurrentStep = 2060;
							break;

		// 계측기 모드 설정
		case	2060	:
							if (pstWorkProcedureData->bEnableValue[TPRD_DATA_VALUE_SET_ENV_DEV_MODE]) {

								if (LTimerSteadyDMM.Verify()) {

									// 오류 해제
									if (!m_devDMM.SetSystemCommand(AGDMM_SYS_CLS)) {

										ErrorMessage(TRUE, _T("디지털 멀티미터가 응답하지 않습니다."));
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

								// 측정 모드 설정
								if (!m_devDMM.SetMeasurementMode(nMode)) {

									ErrorMessage(TRUE, _T("디지털 멀티미터가 응답하지 않습니다."));
									PROCESS.nCurrentStep = STEP_WORK_ERROR_DEVICE;
									break;
								}

								LTimerSteadyDMM.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_DMM_CONTROL));

								PROCESS.nCurrentStep = 2100;
							}

							break;

		// 연결 모드 체크
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

								// 파라미터 설정
								strParameters.AppendFormat(_T("Mode=%s "), g_szConnectionModeShort[nMode]);

								PROCESS.nCurrentStep = PROCESS.nNextStep;
								break;
							}

							PROCESS.nCurrentStep = 2180;
							break;

		// 연결 모드 설정 : 저항 측정
		case	2110	:
							// 연결 릴레이 초기화
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
							
								// 저항 모드 설정
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_P);
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_N);
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_BATT);
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_IGN);

								PROCESS.nCurrentStep = 2190;
							}

							break;

		// 연결 모드 설정 : 전압 측정 (기본)
		case	2120	:
							// 전류계 바이패스 연결
							if (!GetDOStatus(DO_RLY_S01_BYPASS_ON)) {

								SetDOStatus(DO_ON, DO_RLY_S01_BYPASS_ON);
								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));
							}

							PROCESS.nCurrentStep++;
							break;

		case	2121	:
							if (LTimerSteady.Verify()) {
							
								// 전류 측정 모드 해제
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
							
								// 도어 연결 해제
								if (GetDOStatus(DO_RLY_S01_DOOR_CHECK)) {
					
									SetDOStatus(DO_OFF, DO_RLY_S01_DOOR_CHECK);
									LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));
								}

								PROCESS.nCurrentStep++;
							}
							
							break;

		case	2123	:
							if (LTimerSteady.Verify()) {
							
								// 전압 측정 모드 설정
								SetDOStatus(DO_ON, DO_RLY_S01_PRODUCT_POWER_ON);
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_P);
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_N);
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_BATT);
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_IGN);

								PROCESS.nCurrentStep = 2190;
							}
							
							break;

		// 연결 모드 설정 : 전압 측정 (도어)
		case	2130	:
							// 전류계 바이패스 연결
							if (!GetDOStatus(DO_RLY_S01_BYPASS_ON)) {

								SetDOStatus(DO_ON, DO_RLY_S01_BYPASS_ON);
								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));
							}

							PROCESS.nCurrentStep++;
							break;

		case	2131	:
							if (LTimerSteady.Verify()) {
							
								// 전류 측정 모드 해제
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
							
								// 제품 연결 해제
								if (GetDOStatus(DO_RLY_S01_CONN_P)) {
					
									SetDOStatus(DO_OFF, DO_RLY_S01_CONN_P);
									LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));
								}

								PROCESS.nCurrentStep++;
							}
							
							break;

		case	2133	:
							if (LTimerSteady.Verify()) {
							
								// 전압 측정 모드 설정
								SetDOStatus(DO_ON, DO_RLY_S01_PRODUCT_POWER_ON);
								SetDOStatus(DO_ON, DO_RLY_S01_DOOR_CHECK);
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_N);
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_BATT);
								SetDOStatus(DO_ON, DO_RLY_S01_CONN_IGN);

								PROCESS.nCurrentStep = 2190;
							}
							
							break;

		// 연결 모드 설정 : 전류 측정 (mA)
		case	2140	:
							// 전압 측정 단자 연결 해제
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

								// 전류계 바이패스 연결
								if (!theApp.GetDOStatus(DO_RLY_S01_BYPASS_ON)) {

									theApp.SetDOStatus(DO_ON, DO_RLY_S01_BYPASS_ON);
									LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));
								}

								PROCESS.nCurrentStep++;
							}
							
							break;	

		case	2142	:
							if (LTimerSteady.Verify()) {
							
								// 전류 측정 모드 초기화
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
							
								// 전류 측정 모드 설정
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
							
								// 전류계 바이패스 연결 해제
								if (GetDOStatus(DO_RLY_S01_BYPASS_ON)) {

									SetDOStatus(DO_OFF, DO_RLY_S01_BYPASS_ON);
								}

								PROCESS.nCurrentStep = 2190;
							}
							
							break;

		// 연결 모드 설정 : 전류 측정 (A)
		case	2150	:
							// 전압 측정 단자 연결 해제
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

								// 전류계 바이패스 연결
								if (!theApp.GetDOStatus(DO_RLY_S01_BYPASS_ON)) {

									theApp.SetDOStatus(DO_ON, DO_RLY_S01_BYPASS_ON);
									LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));
								}

								PROCESS.nCurrentStep++;
							}
							
							break;	

		case	2152	:
							if (LTimerSteady.Verify()) {
							
								// 전류 측정 모드 초기화
								if (GetDOStatus(DO_RLY_S01_RANGE_mA)) {

									SetDOStatus(DO_OFF, DO_RLY_S01_RANGE_mA);
									LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_RELAY));
								}

								PROCESS.nCurrentStep++;
							}
							
							break;

		case	2153	:
							if (LTimerSteady.Verify()) {
							
								// 전류 측정 모드 설정
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
							
								// 전류계 바이패스 연결 해제
								if (GetDOStatus(DO_RLY_S01_BYPASS_ON)) {

									SetDOStatus(DO_OFF, DO_RLY_S01_BYPASS_ON);
								}

								PROCESS.nCurrentStep = 2190;
							}
							
							break;

		// 연결 모드 설정 : 도어 잠금
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
							
								// mA 연결이 아닌 경우에만 동작
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

		// 연결 모드 설정 : 도어 잠금 해제
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
							
								// mA 연결이 아닌 경우에만 동작
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

		// 연결 릴레이 설정
		case	2180	:
							{
								BOOL	bEnable		= FALSE;
								UINT	nDATA_ID	= 0;


								// 배터리 신호
								nDATA_ID = TPRD_DATA_VALUE_SET_ENV_CONN_BATTERY;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
									SetDOStatus(bEnable ? DO_ON : DO_OFF, DO_RLY_S01_CONN_BATT);

									// 파라미터 설정
									strParameters.AppendFormat(_T("BATT=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
								}

								// IGN 신호
								nDATA_ID = TPRD_DATA_VALUE_SET_ENV_CONN_IGN;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									if (!GetDOStatus(DO_RLY_S01_RANGE_mA)) {

										bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
										SetDOStatus(bEnable ? DO_ON : DO_OFF, DO_RLY_S01_CONN_IGN);

										// 파라미터 설정
										strParameters.AppendFormat(_T("IGN=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
									
									} else {
									
										// 파라미터 설정
										strParameters.AppendFormat(_T("IGN=ERR "));
									}
								}

								PROCESS.nCurrentStep = 2190;
							}

							break;

		// 완료
		case	2190	:
							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// 서브 스텝 : 커맨드 - 통신 설정 ///////////////////////////
		case	STEP_WORK_SUB_CMD_SETUP_COMM	:
													MessageWindow(cDEBUG, _T("PROC::CMD_SETUP_COMM"));

													PROCESS.nCurrentStep = 2210;
													break;

		// 초기화
		case	2210	:
							PROCESS.nCurrentStep = 2250;
							break;

		// 메세지 전송 활성화
		case	2250	:
							{
								BOOL	bEnable		= FALSE;
								UINT	nDATA_ID	= 0;


								// BMS22
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_ENABLE_SEND_MSG_T01;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
									m_stSystemStatus.bCAN_EnableTransmitData[CID_BMS22] = bEnable;

									// 파라미터 설정
									strParameters.AppendFormat(_T("BMS22=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
								}

								// BMS4
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_ENABLE_SEND_MSG_T02;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
									m_stSystemStatus.bCAN_EnableTransmitData[CID_BMS4] = bEnable;

									// 파라미터 설정
									strParameters.AppendFormat(_T("BMS4=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
								}

								// OBC1
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_ENABLE_SEND_MSG_T03;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
									m_stSystemStatus.bCAN_EnableTransmitData[CID_OBC1] = bEnable;

									// 파라미터 설정
									strParameters.AppendFormat(_T("OBC1=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
								}

								// TMU1
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_ENABLE_SEND_MSG_T04;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
									m_stSystemStatus.bCAN_EnableTransmitData[CID_TMU1] = bEnable;

									// 파라미터 설정
									strParameters.AppendFormat(_T("TMU1=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
								}

								// VCU1
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_ENABLE_SEND_MSG_T05;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
									m_stSystemStatus.bCAN_EnableTransmitData[CID_VCU1] = bEnable;

									// 파라미터 설정
									strParameters.AppendFormat(_T("VCU1=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
								}

								// VCU19
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_ENABLE_SEND_MSG_T06;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
									m_stSystemStatus.bCAN_EnableTransmitData[CID_VCU19] = bEnable;

									// 파라미터 설정
									strParameters.AppendFormat(_T("VCU19=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
								}

								// CGW1
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_ENABLE_SEND_MSG_T07;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
									m_stSystemStatus.bCAN_EnableTransmitData[CID_CGW1] = bEnable;

									// 파라미터 설정
									strParameters.AppendFormat(_T("CGW1=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
								}

								// IGPM_EV1
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_ENABLE_SEND_MSG_T08;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
									m_stSystemStatus.bCAN_EnableTransmitData[CID_IGPM_EV1] = bEnable;

									// 파라미터 설정
									strParameters.AppendFormat(_T("IGPM_EV1=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
								}

								// MCU3
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_ENABLE_SEND_MSG_T09;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
									m_stSystemStatus.bCAN_EnableTransmitData[CID_MCU3] = bEnable;

									// 파라미터 설정
									strParameters.AppendFormat(_T("MCU3=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
								}

								// WHL_SPD11
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_ENABLE_SEND_MSG_T10;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									bEnable = (BOOL)pstWorkProcedureData->nValue[nDATA_ID];
									m_stSystemStatus.bCAN_EnableTransmitData[CID_WHL_SPD11] = bEnable;

									// 파라미터 설정
									strParameters.AppendFormat(_T("WHL_SPD11=%d "), pstWorkProcedureData->nValue[nDATA_ID]);
								}

								PROCESS.nCurrentStep = 2260;
							}

							break;

		// 시그널 상태 설정
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

									// 파라미터 설정
									strParameters.AppendFormat(_T("Bms_ChgSts=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// CR_BMS_DisplaySOC
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T01_S02;
								nSIG_ID	 = CR_BMS_DisplaySOC;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// 파라미터 설정
									strParameters.AppendFormat(_T("BMS_DisplaySOC=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// CF_Bms_ChgLamp
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T02_S01;
								nSIG_ID	 = CF_Bms_ChgLamp;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// 파라미터 설정
									strParameters.AppendFormat(_T("Bms_ChgLamp=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// CF_OBC_IG3_DRV_STATE
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T03_S01;
								nSIG_ID	 = CF_OBC_IG3_DRV_STATE;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// 파라미터 설정
									strParameters.AppendFormat(_T("OBC_IG3_DRV_STATE=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// CF_Tmu_IG3Rly
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T04_S01;
								nSIG_ID	 = CF_Tmu_IG3Rly;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// 파라미터 설정
									strParameters.AppendFormat(_T("Tmu_IG3Rly=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// CF_Vcu_EvRdy
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T05_S01;
								nSIG_ID	 = CF_Vcu_EvRdy;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// 파라미터 설정
									strParameters.AppendFormat(_T("Vcu_EvRdy=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// CF_VCU_IG3DrvSts
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T06_S01;
								nSIG_ID	 = CF_VCU_IG3DrvSts;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// 파라미터 설정
									strParameters.AppendFormat(_T("VCU_IG3DrvSts=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// CF_Gway_Ign1
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T07_S01;
								nSIG_ID	 = CF_Gway_Ign1;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// 파라미터 설정
									strParameters.AppendFormat(_T("Gway_Ign1=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// C_Ign3Rly
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T08_S01;
								nSIG_ID	 = C_Ign3Rly;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// 파라미터 설정
									strParameters.AppendFormat(_T("Ign3Rly=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// CR_Mcu_VehSpd_Kph
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T09_S01;
								nSIG_ID	 = CR_Mcu_VehSpd_Kph;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// 파라미터 설정
									strParameters.AppendFormat(_T("Mcu_VehSpd_Kph=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// CR_Mcu_VehSpdDec_Kph
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T09_S02;
								nSIG_ID	 = CR_Mcu_VehSpdDec_Kph;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// 파라미터 설정
									strParameters.AppendFormat(_T("Mcu_VehSpdDec_Kph=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// WHL_SPD_RL
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T10_S01;
								nSIG_ID	 = WHL_SPD_RL;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// 파라미터 설정
									strParameters.AppendFormat(_T("WHL_SPD_RL=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// WHL_SPD_RR
								nDATA_ID = TPRD_DATA_VALUE_SET_COMM_STS_SIGNAL_T10_S02;
								nSIG_ID	 = WHL_SPD_RR;
								if (pstWorkProcedureData->bEnableValue[nDATA_ID]) {
								
									m_strCAN_MsgSignalValue[nSIG_ID] = pstWorkProcedureData->szValue[nDATA_ID];

									// 파라미터 설정
									strParameters.AppendFormat(_T("WHL_SPD_RR=%s "), pstWorkProcedureData->szValue[nDATA_ID]);
								}

								// 시그널 데이터 업데이트
								CAN_UpdateSignalValue();

								PROCESS.nCurrentStep = 2390;
							}

							break;

		// 완료
		case	2390	:
							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// 서브 스텝 : 커맨드 - 단일 측정 ///////////////////////////
		case	STEP_WORK_SUB_CMD_MEAS	:
											MessageWindow(cDEBUG, _T("PROC::CMD_MEASUREMENT"));

											PROCESS.nCurrentStep = 2410;
											break;

		// 초기화
		case	2410	:
							// 플래그 초기화
							PROCESS.bResultMainProcess = FALSE;

							// 현재 프로시저 번호 설정
							m_stSystemStatus.nCurrentWorkProcedureNo = PROCESS.nCurrentProcedureNo;

							// 검사 시트 초기화
							ZeroMemory((PROCESS.pstWorkStatus)->stMeasSheet, sizeof(MEAS_SHEET_T) * MAX_TEST_SHEET);

							PROCESS.nCurrentStep = 2420;
							break;

		// 파라미터 설정
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

		// 검사 시작
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

		// 결과 설정
		case	2510	:
							{
								BOOL	bUseStopNG	= (BOOL)pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_USE_NG_STOP];
								DOUBLE	dblGain		= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_GAIN];
								DOUBLE	dblOffset	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_OFFSET];
								DOUBLE	dblSpecMIN	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_SPEC_L];
								DOUBLE	dblSpecMAX	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_SPEC_H];


								// 검사 데이터 설정
								stFunctionTestData.nResult = (PROCESS.pstWorkStatus)->stMeasSheet[0].nResult;
								_stprintf_s(stFunctionTestData.szValue, MAX_STRINPUT_S, _T("%.4f"), (PROCESS.pstWorkStatus)->stMeasSheet[0].dblMeasurementValue);
								_stprintf_s(stFunctionTestData.szSpecMIN, MAX_STRINPUT, _T("%.4f"), (PROCESS.pstWorkStatus)->stMeasSheet[0].dblSpecMIN);
								_stprintf_s(stFunctionTestData.szSpecMAX, MAX_STRINPUT, _T("%.4f"), (PROCESS.pstWorkStatus)->stMeasSheet[0].dblSpecMAX);
								_tcscpy_s(stFunctionTestData.szUnit, MAX_STRINPUT, (PROCESS.pstWorkStatus)->stMeasSheet[0].szUnit);

								// 검사 결과 설정
								PROCESS.nResultInspection = (PROCESS.pstWorkStatus)->stMeasSheet[0].nResult;

								// 불합격 판정 시 즉시 정지 옵션
								if (PROCESS.nResultInspection != T_RESULT_SUCCESS && bUseStopNG)
									PROCESS.bOnInstantStop = TRUE;

								PROCESS.nCurrentStep = 2580;
							}

							break;

		// 불합격 판정 시 재검사
		case	2580	:
							if (m_SystemConfig.UseSystemOption(SOPT_RETRY_WORK_NG)) {

								if (PROCESS.nResultInspection != T_RESULT_SUCCESS) {

									// 재시도 카운트 체크
									if (++PROCESS.nRetryCount <= m_SystemConfig.GetWorkRetryCount()) {

										// 플래그 초기화
										PROCESS.nResultInspection	= T_RESULT_SUCCESS;
										PROCESS.bOnInstantStop		= FALSE;
										PROCESS.bResultMainProcess	= FALSE;

										// 검사 시트 초기화
										ZeroMemory((PROCESS.pstWorkStatus)->stMeasSheet, sizeof(MEAS_SHEET_T) * MAX_TEST_SHEET);

										PROCESS.nCurrentStep = 2500;
										break;
									}
								}
							}

							PROCESS.nCurrentStep = 2590;
							break;

		// 완료
		case	2590	:
							// 작업 시트 업데이트 설정
							PROCESS.bOnUpdateWorkSheet = !pstWorkProcedureData->bOptions[TPRD_DATA_OPT_MEAS_UNUSE_UPDATE];
							if (PROCESS.nResultInspection != T_RESULT_SUCCESS)
								PROCESS.bOnUpdateWorkSheet = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// 서브 스텝 : 커맨드 - 연속 측정 ///////////////////////////
		case	STEP_WORK_SUB_CMD_MEAS_START	:
													MessageWindow(cDEBUG, _T("PROC::CMD_MEASUREMENT_START"));

													PROCESS.nCurrentStep = 2610;
													break;

		// 초기화
		case	2610	:
							// 플래그 초기화
							PROCESS.bResultMainProcess = FALSE;

							// 현재 프로시저 번호 설정
							m_stSystemStatus.nCurrentWorkProcedureNo = PROCESS.nCurrentProcedureNo;

							PROCESS.nCurrentStep = 2620;
							break;

		// 파라미터 설정
		case	2620	:
							{
								strParameters.AppendFormat(_T("Jdg_min=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_START_JUDGE_STOP_MIN]);
								strParameters.AppendFormat(_T("Jdg_max=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_START_JUDGE_STOP_MAX]);
								strParameters.AppendFormat(_T("Jdg=%lf "),		pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_JUDGE]);
								strParameters.AppendFormat(_T("D_Rng=%lf "),	pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_DEV_RANGE]);

								PROCESS.nCurrentStep = 2700;
							}

							break;

		// 검사 시작
		case	2700	:
							m_stSystemStatus.bOnMainProcess[nSTATION_NO][STN1_SUB_TEST] = TRUE;

							PROCESS.nCurrentStep = 2790;
							break;

		// 완료
		case	2790	:
							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// 서브 스텝 : 커맨드 - 측정 결과 ///////////////////////////
		case	STEP_WORK_SUB_CMD_MEAS_RESULT	:
													MessageWindow(cDEBUG, _T("PROC::CMD_MEASUREMENT_RESULT"));

													PROCESS.nCurrentStep = 2810;
													break;

		// 초기화
		case	2810	:
							// 플래그 초기화
							PROCESS.bResultMainProcess			= FALSE;
							PROCESS.dblValueRaw					= 0;
							PROCESS.dblValueMeasurement			= 0;
							PROCESS.dblValueMeasurementSUM		= 0;
							PROCESS.nIndexAverageMeasurement	= 0;

							// 검사 시트 초기화
							ZeroMemory((PROCESS.pstWorkStatus)->stMeasSheet, sizeof(MEAS_SHEET_T) * MAX_TEST_SHEET);

							PROCESS.nCurrentStep = 2820;
							break;

		// 파라미터 설정
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

		// 검사 완료 체크
		case	2900	:
							if (!m_stSystemStatus.bOnMainProcess[nSTATION_NO][STN1_SUB_TEST]) {
							
								PROCESS.bResultMainProcess = m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][STN1_SUB_TEST];

								PROCESS.nCurrentStep = 2910;
							}

							break;

		// 데이터 분석 (평균)
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

		// 데이터 분석 (시간)
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

		// 데이터 분석 (편차)
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

		// 데이터 분석 (최소값/최대값)
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

		// 결과 설정
		case	2980	:
							{
								BOOL	bUseStopNG	= (BOOL)pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_RESULT_USE_NG_STOP];
								DOUBLE	dblGain		= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_RESULT_GAIN];
								DOUBLE	dblOffset	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_RESULT_OFFSET];
								DOUBLE	dblSpecMIN	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_RESULT_SPEC_L];
								DOUBLE	dblSpecMAX	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_RESULT_SPEC_H];


								PROCESS.dblValueMeasurement	= (PROCESS.dblValueRaw * dblGain) + dblOffset;

								// 검사 결과 판정
								if (DPS_Round(PROCESS.dblValueMeasurement, 4) < DPS_Round(dblSpecMIN, 4) ||
									DPS_Round(PROCESS.dblValueMeasurement, 4) > DPS_Round(dblSpecMAX, 4))
										PROCESS.nResultInspection = T_RESULT_FAILURE;

								// 검사 데이터 설정
								stFunctionTestData.nResult = PROCESS.nResultInspection;
								_stprintf_s(stFunctionTestData.szValue, MAX_STRINPUT_S, _T("%.4f (%d)"), PROCESS.dblValueMeasurement, m_arrContiMeasData.GetCount());
								_stprintf_s(stFunctionTestData.szSpecMIN, MAX_STRINPUT, _T("%.4f"), dblSpecMIN);
								_stprintf_s(stFunctionTestData.szSpecMAX, MAX_STRINPUT, _T("%.4f"), dblSpecMAX);
								_tcscpy_s(stFunctionTestData.szUnit, MAX_STRINPUT, pstWorkProcedureData->szValue[TPRD_DATA_VALUE_MEAS_RESULT_UNIT]);

								// 불합격 판정 시 즉시 정지 옵션
								if (PROCESS.nResultInspection != T_RESULT_SUCCESS && bUseStopNG)
									PROCESS.bOnInstantStop = TRUE;

								PROCESS.nCurrentStep = 2990;
							}

							break;

		// 완료
		case	2990	:
							// 작업 시트 업데이트 설정
							PROCESS.bOnUpdateWorkSheet = !pstWorkProcedureData->bOptions[TPRD_DATA_OPT_MEAS_RESULT_UNUSE_UPDATE];
							if (PROCESS.nResultInspection != T_RESULT_SUCCESS)
								PROCESS.bOnUpdateWorkSheet = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// 서브 스텝 : 커맨드 - 일반 동작 ///////////////////////////
		case	STEP_WORK_SUB_CMD_ACTION_MOVE	:
													MessageWindow(cDEBUG, _T("PROC::CMD_ACTION_MOVE"));

													PROCESS.nCurrentStep = 3010;
													break;

		// 초기화
		case	3010	:
							// 작업 시트 위치 설정
							PROCESS.nCurrentWorkSheetNo = pstWorkProcedureData->nValue[TPRD_DATA_VALUE_ACT_WPS_NO] - 1;
							if (PROCESS.nCurrentWorkSheetNo > MAX_S01_WORK_POSITION_SHEET)
								PROCESS.nCurrentWorkSheetNo = WPS_S01_STANDBY;

							if (PROCESS.nCurrentWorkSheetNo >= WPS_S01_OPEN_BEGIN && PROCESS.nCurrentWorkSheetNo <= WPS_S01_CLOSE_END)
								PROCESS.nCurrentWorkSheetNo = WPS_S01_STANDBY;

							PROCESS.nCurrentStep = 3020;
							break;

		// 파라미터 설정
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

		// 도어 누름 유닛 : UP
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

		// 도어 누름 유닛 : DN
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

		// 도어 열림 유닛 : UP
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

		// 도어 열림 유닛 : DN
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

		// VZ 대기 위치 이동
		case	3100	:
							// 도어 열림 체크
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

		// VX, VY 목표 위치 보간 이동
		case	3110	:
							// 도어 열림 체크
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

		// VZ 목표 위치 이동
		case	3120	:
							// 도어 열림 체크
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

		// VZ 오프셋 이동
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

		// 지연 시간 설정
		case	3150	:
							LTimerProceed.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_ACT_DELAY]);

							PROCESS.nCurrentStep++;
							break;

		case	3151	:
							if (LTimerProceed.Verify())
								PROCESS.nCurrentStep = 3160;

							break;

		// VZ 대기 위치 이동
		case	3160	:
							if (!pstWorkProcedureData->bOptions[TPRD_DATA_OPT_ACT_UNUSE_HOME]) {

								PROCESS.nCurrentStep++;
								break;
							}

							PROCESS.nCurrentStep = 3170;
							break;

		case	3161	:
							// 도어 열림 체크
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

		// 완료
		case	3190	:
							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// 서브 스텝 : 커맨드 - 열기 동작 ///////////////////////////
		case	STEP_WORK_SUB_CMD_ACTION_OPEN	:
													MessageWindow(cDEBUG, _T("PROC::CMD_ACTION_OPEN"));

													PROCESS.nCurrentStep = 3210;
													break;

		// 초기화
		case	3210	:
							PROCESS.nCurrentStep = 3220;
							break;

		// 파라미터 설정
		case	3220	:
							{
								PROCESS.nCurrentStep = 3240;
							}

							break;

		// 현재 상태 체크
		case	3240	:
							if (/*GetDIStatus(DI_SENS_S01_DETECT_PRODUCT_DOOR) && */GetDIStatus(DI_SENS_S01_PRODUCT_DOOR_OPEN_UP)) {
							
								PROCESS.nCurrentStep = 3250;
								break;
							}

							// 결과 설정
							PROCESS.nResultInspection = T_RESULT_ERROR;

							// 도어 열림 유닛 : DN
							pOnSCP_MoveParts[SCP_S01_PRODUCT_DOOR_OPEN_DN] = TRUE;

							PROCESS.nCurrentStep = 3370;
							break;

		// VZ 대기 위치 이동
		case	3250	:
							// 도어 열림 체크
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

		// VY 대기 위치 이동
		case	3260	:
							// 도어 열림 체크
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

		// VX, VZ 목표 위치 보간 이동
		case	3270	:
							// 도어 열림 체크
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

		// VY 목표 위치 이동
		case	3280	:
							// 도어 열림 체크
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

		// 지연 시간 설정
		case	3300	:
							LTimerProceed.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_ACT_OPEN_DELAY]);

							PROCESS.nCurrentStep++;
							break;

		case	3301	:
							if (LTimerProceed.Verify())
								PROCESS.nCurrentStep = 3310;

							break;

		// 도어 열림 유닛 : DN
		case	3310	:
							pOnSCP_MoveParts[SCP_S01_PRODUCT_DOOR_OPEN_DN] = TRUE;

							PROCESS.nCurrentStep = 3320;
							break;

		// VX, VY, VZ 목표 위치 보간 이동
		case	3320	:
							// 도어 열림 체크
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

		// VY 대기 위치 이동
		case	3350	:
							// 도어 열림 체크
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

		// 도어 열림 체크
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

									// 결과 설정
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

		// 도어 열림 유닛 확인 : DN
		case	3370	:
							if (!pOnSCP_MoveParts[SCP_S01_PRODUCT_DOOR_OPEN_DN])
								PROCESS.nCurrentStep = 3380;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// 결과 설정
		case	3380	:
							{
								// 검사 데이터 설정
								stFunctionTestData.nResult = PROCESS.nResultInspection;

								PROCESS.nCurrentStep = 3390;
							}

							break;

		// 완료
		case	3390	:
							// 작업 시트 업데이트 설정
							PROCESS.bOnUpdateWorkSheet = !pstWorkProcedureData->bOptions[TPRD_DATA_OPT_ACT_OPEN_UNUSE_UPDATE];
							if (PROCESS.nResultInspection != T_RESULT_SUCCESS)
								PROCESS.bOnUpdateWorkSheet = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// 서브 스텝 : 커맨드 - 닫기 동작 ///////////////////////////
		case	STEP_WORK_SUB_CMD_ACTION_CLOSE	:
													MessageWindow(cDEBUG, _T("PROC::CMD_ACTION_CLOSE"));

													PROCESS.nCurrentStep = 3410;
													break;

		// 초기화
		case	3410	:
							PROCESS.nCurrentStep = 3420;
							break;

		// 파라미터 설정
		case	3420	:
							{
								PROCESS.nCurrentStep = 3440;
							}

							break;

		// 현재 상태 체크
		case	3440	:
							if (!GetDIStatus(DI_SENS_S01_DETECT_PRODUCT_DOOR)) {

								// 도어 열림 유닛 : UP
								pOnSCP_MoveParts[SCP_S01_PRODUCT_DOOR_OPEN_UP] = TRUE;
							
								PROCESS.nCurrentStep = 3460;
								break;
							}

							// 결과 설정
							PROCESS.nResultInspection = T_RESULT_ERROR;

							PROCESS.nCurrentStep = 3580;
							break;

		// VZ 대기 위치 이동 (스킵함)
		case	3450	:
							// 도어 열림 체크
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

		// VY 대기 위치 이동
		case	3460	:
							// 도어 열림 체크
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

		// VX, VZ 목표 위치 보간 이동
		case	3470	:
							// 도어 열림 체크
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

		// VY 목표 위치 이동
		case	3480	:
							// 도어 열림 체크
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

		// 도어 열림 유닛 확인 : UP
		case	3490	:
							if (!pOnSCP_MoveParts[SCP_S01_PRODUCT_DOOR_OPEN_UP])
								PROCESS.nCurrentStep = 3500;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// 지연 시간 설정
		case	3500	:
							LTimerProceed.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_ACT_CLOSE_DELAY]);

							PROCESS.nCurrentStep++;
							break;

		case	3501	:
							if (LTimerProceed.Verify())
								PROCESS.nCurrentStep = 3520;

							break;

		// VX, VY, VZ 목표 위치 보간 이동
		case	3520	:
							// 도어 열림 체크
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

		// VY 대기 위치 이동
		case	3550	:
							// 도어 열림 체크
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

		// 도어 열림 유닛 : DN
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

		// 도어 닫힘 체크
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

									// 결과 설정
									PROCESS.nResultInspection = T_RESULT_FAILURE;

									PROCESS.nCurrentStep = 3580;
								}

								break;
							}

							PROCESS.nCurrentStep = 3570;
							break;

		// 결과 설정
		case	3580	:
							{
								// 검사 데이터 설정
								stFunctionTestData.nResult = PROCESS.nResultInspection;

								PROCESS.nCurrentStep = 3590;
							}

							break;

		// 완료
		case	3590	:
							// 작업 시트 업데이트 설정
							PROCESS.bOnUpdateWorkSheet = !pstWorkProcedureData->bOptions[TPRD_DATA_OPT_ACT_CLOSE_UNUSE_UPDATE];
							if (PROCESS.nResultInspection != T_RESULT_SUCCESS)
								PROCESS.bOnUpdateWorkSheet = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// 서브 스텝 : 커맨드 - 상승 PUSH 검사 //////////////////////
		case	STEP_WORK_SUB_CMD_TEST_PUSH_UP	:
													MessageWindow(cDEBUG, _T("PROC::CMD_TEST_PUSH_UP"));

													PROCESS.nCurrentStep = 3610;
													break;

		// 초기화
		case	3610	:
							// 플래그 초기화
							PROCESS.dblValueRaw			= 0;
							PROCESS.dblValueMeasurement	= 0;
							bUseLoadCell				= (BOOL)pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA1_USE_LC];

							// 로드셀 채널 설정
							nCurrentLoadCellNo = pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA1_LCC_NO];
							if (nCurrentLoadCellNo >= MAX_LOADCELL_CHANNEL_USE)
								nCurrentLoadCellNo = LOADCELL_CH01;

							// 로드셀 데이터 초기화
							m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo]		= 0;
							m_stSystemStatus.dblPeakHoldDataLoadCell[nCurrentLoadCellNo]	= 0;

							PROCESS.nCurrentStep = 3620;
							break;

		// 파라미터 설정
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

		// 지연 시간
		case	3630	:
							LTimerProceed.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA1_DELAY]);

							PROCESS.nCurrentStep++;
							break;

		case	3631	:
							if (LTimerProceed.Verify())
								PROCESS.nCurrentStep = 3700;

							break;

		// 도어 열림 유닛 : UP
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

							// 검사 결과 설정
							PROCESS.nResultInspection = T_RESULT_ERROR;

							PROCESS.nCurrentStep = 3710;
							break;

		// 도어 열림 체크 (일반 모드)
		case	3710	:
							if (GetDIStatus(m_nTypeMachine == MC_TYPE_1 ? DI_SENS_S01_PRODUCT_DOOR_OPEN_UP : DI_SENS_S02_PRODUCT_DOOR_OPEN_UP)) {
							
								PROCESS.nCurrentStep = 3780;
								break;
							}

							if (LTimerTimeOut.Verify() || 
								(bUseLoadCell && m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo] > pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA1_JUDGE])) {
							
								// 검사 결과 설정
								PROCESS.nResultInspection = T_RESULT_FAILURE;

								PROCESS.nCurrentStep = 3750;
							}
							
							break;

		// 도어 열림 체크 (잠금 모드)
		case	3720	:
							if (GetDIStatus(m_nTypeMachine == MC_TYPE_1 ? DI_SENS_S01_PRODUCT_DOOR_OPEN_UP : DI_SENS_S02_PRODUCT_DOOR_OPEN_UP)) {

								// 검사 결과 설정
								PROCESS.nResultInspection = T_RESULT_FAILURE;
							
								PROCESS.nCurrentStep = 3750;
								break;
							}

							if (LTimerTimeOut.Verify() ||
								(bUseLoadCell && m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo] > pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA1_JUDGE])) {

								PROCESS.nCurrentStep = 3750;
							}
							
							break;

		// 도어 열림 유닛 : DN
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

		// 결과 설정
		case	3780	:
							{
								DOUBLE	dblGain		= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA1_GAIN];
								DOUBLE	dblOffset	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA1_OFFSET];
								DOUBLE	dblSpecMIN	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA1_SPEC_L];
								DOUBLE	dblSpecMAX	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA1_SPEC_H];


								PROCESS.dblValueRaw			= m_stSystemStatus.dblPeakHoldDataLoadCell[nCurrentLoadCellNo];
								PROCESS.dblValueMeasurement	= (PROCESS.dblValueRaw * dblGain) + dblOffset;

								// 검사 결과 판정
								if (bUseLoadCell) {

									if (DPS_Round(PROCESS.dblValueMeasurement, 2) < DPS_Round(dblSpecMIN, 2) ||
										DPS_Round(PROCESS.dblValueMeasurement, 2) > DPS_Round(dblSpecMAX, 2))
											PROCESS.nResultInspection = T_RESULT_FAILURE;
								}

								// 검사 데이터 설정
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

		// 완료
		case	3790	:
							// 작업 시트 업데이트 설정
							PROCESS.bOnUpdateWorkSheet = !pstWorkProcedureData->bOptions[TPRD_DATA_OPT_TA1_UNUSE_UPDATE];
							if (PROCESS.nResultInspection != T_RESULT_SUCCESS)
								PROCESS.bOnUpdateWorkSheet = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// 서브 스텝 : 커맨드 - 하강 PUSH 검사 #1 ///////////////////
		case	STEP_WORK_SUB_CMD_TEST_PUSH_1_DN	:
													MessageWindow(cDEBUG, _T("PROC::CMD_TEST_PUSH_DN_01"));

													PROCESS.nCurrentStep = 3810;
													break;

		// 초기화
		case	3810	:
							// 플래그 초기화
							PROCESS.dblValueRaw			= 0;
							PROCESS.dblValueMeasurement	= 0;
							nCurrentMessageNo			= TPRD_DATA_VALUE_TA2_CAN_MSG;
							nIndexTestDataCAN			= 0;

							// CAN 통신 초기화
							m_devCAN.ClearBuffer();

							// 로드셀 채널 설정
							nCurrentLoadCellNo = pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA2_LCC_NO];
							if (nCurrentLoadCellNo >= MAX_LOADCELL_CHANNEL_USE)
								nCurrentLoadCellNo = LOADCELL_CH01;

							// 로드셀 데이터 초기화
							m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo]		= 0;
							m_stSystemStatus.dblPeakHoldDataLoadCell[nCurrentLoadCellNo]	= 0;

							// CAN 수신 데이터 초기화
							if (pstWorkProcedureData->stCanValue[nCurrentMessageNo].bUsable)
								TPRD_CAN_MSG_Process(pstWorkProcedureData->stCanValue[nCurrentMessageNo]);

							PROCESS.nCurrentStep = 3820;
							break;

		// 파라미터 설정
		case	3820	:
							{
								strParameters.AppendFormat(_T("T_hld=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA2_HOLD]);
								strParameters.AppendFormat(_T("LC_no=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA2_LCC_NO]);

								PROCESS.nCurrentStep = 3830;
							}

							break;

		// 현재 상태 체크
		case	3830	:
							if (GetDIStatus(DI_SENS_S01_DETECT_PRODUCT_DOOR) && GetDIStatus(DI_SENS_S01_PRODUCT_DOOR_OPEN_DN)) {
							
								PROCESS.nCurrentStep = 3840;
								break;
							}

							// 결과 설정
							PROCESS.nResultInspection = T_RESULT_ERROR;

							PROCESS.nCurrentStep = 3980;
							break;

		// 지연 시간
		case	3840	:
							LTimerProceed.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA2_DELAY]);

							PROCESS.nCurrentStep++;
							break;

		case	3841	:
							if (LTimerProceed.Verify())
								PROCESS.nCurrentStep = 3850;

							break;

		// VZ 대기 위치 이동
		case	3850	:
							// 도어 열림 체크
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

		// VX, VY 목표 위치 보간 이동
		case	3860	:
							// 도어 열림 체크
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

		// VZ 목표 위치 이동
		case	3870	:
							// 도어 열림 체크
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

		// VZ 상대 위치 이동
		case	3900	:
							if (Motion_Done(MOTION_RVZ)) {
		
								DOUBLE	dblCurrentPosition	= 0;
								DOUBLE	dblLimitPositive	= 0;
								DOUBLE	dblPosition			= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA2_MOT_LIMIT];
								DOUBLE	dblSpeed			= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA2_MOT_SPEED];
								

								// 소프트 리미트 설정
								AxmStatusGetCmdPos(MOTION_RVZ, &dblCurrentPosition);
								dblLimitPositive = dblCurrentPosition + dblPosition;
								Motion_SetSoftLimit(MOTION_RVZ, m_stMotionAxisInfo[MOTION_RVZ].dblLimitNegativePos, dblLimitPositive);

								// 상대 좌표 이동
								Motion_Move(MOTION_RVZ, dblPosition, dblSpeed);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3901	:
							{
								BOOL	bResult	= TRUE;


								if (m_devCAN.ReadPacket(stReadPacket)) {

									if (stReadPacket.stMessage.ID == pstWorkProcedureData->stCanValue[nCurrentMessageNo].nCAN_ID) {

										// 디버그 메세지
										CString	strDebugMessage	= _T("");
										for (UINT nIndex = 0; nIndex < MAX_CAN_MSG_BYTE; nIndex++)	strDebugMessage.AppendFormat(_T("%02X "), stReadPacket.stMessage.DATA[nIndex]);
										NormalMessage(TRUE, _T("CAN READ => %s"), strDebugMessage);

										// 수신 데이터 검증
										if (TPRD_CAN_MSG_VERIFY_Process(stReadPacket, pstWorkProcedureData->stCanValue[nCurrentMessageNo])) {

											// 검사 데이터 설정
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

								// 로드셀 데이터 체크
								if (m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo] >= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA2_LC_LIMIT])
									bResult = FALSE;

								// 모터 이동 완료
								if (Motion_Done(MOTION_RVZ))
									bResult = FALSE;

								if (!bResult) {
									
									// 검사 결과 설정
									PROCESS.nResultInspection = T_RESULT_FAILURE;
									
									PROCESS.nCurrentStep = 3970;
								}
							}

							break;

		case	3902	:
							// 모터 정지
							Motion_Stop_E(MOTION_RVZ);

							// 소프트 리미트 초기화
							Motion_SetSoftLimit(MOTION_RVZ);

							PROCESS.nCurrentStep = 3910;
							break;

		// VZ 오프셋 (FORCE) 이동
		// VZ FORCE 위치 이동 (절대값 이동)
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

								// 로드셀 측정 안정화 시간
								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_MEASUREMENT_1));

								PROCESS.nCurrentStep++;
							}

							break;

		case	3912	:
							if (LTimerSteady.Verify()) {
							
								// 로드셀 데이터 저장
								PROCESS.dblValueRaw = m_stSystemStatus.dblPeakHoldDataLoadCell[nCurrentLoadCellNo];

								PROCESS.nCurrentStep = 3920;
							}

							break;

		// VZ PUSH 위치 이동 (절대값 이동)
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

		// VZ 목표 위치 이동
		case	3930	:
							// 도어 열림 체크
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

		// VZ 오프셋 (PUSH) 이동
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

		// 홀딩 시간 설정
		case	3950	:
							LTimerProceed.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA2_HOLD]);

							PROCESS.nCurrentStep++;
							break;

		case	3951	:
							if (LTimerProceed.Verify())
								PROCESS.nCurrentStep = 3970;

							break;

		// VZ 대기 위치 이동
		case	3970	:
							// 도어 열림 체크
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

		// 결과 설정
		case	3980	:
							{
								DOUBLE	dblGain		= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA2_GAIN];
								DOUBLE	dblOffset	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA2_OFFSET];
								DOUBLE	dblSpecMIN	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA2_SPEC_L];
								DOUBLE	dblSpecMAX	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA2_SPEC_H];


								PROCESS.dblValueMeasurement	= (PROCESS.dblValueRaw * dblGain) + dblOffset;

								// 검사 결과 판정
								if (DPS_Round(PROCESS.dblValueMeasurement, 2) < DPS_Round(dblSpecMIN, 2) ||
									DPS_Round(PROCESS.dblValueMeasurement, 2) > DPS_Round(dblSpecMAX, 2))
										PROCESS.nResultInspection = T_RESULT_FAILURE;

								// 검사 데이터 설정
								stFunctionTestData.nResult = PROCESS.nResultInspection;
								_stprintf_s(stFunctionTestData.szValue, MAX_STRINPUT_S, _T("%.2f"), PROCESS.dblValueMeasurement);
								_stprintf_s(stFunctionTestData.szSpecMIN, MAX_STRINPUT, _T("%.2f"), dblSpecMIN);
								_stprintf_s(stFunctionTestData.szSpecMAX, MAX_STRINPUT, _T("%.2f"), dblSpecMAX);
								_tcscpy_s(stFunctionTestData.szUnit, MAX_STRINPUT, pstWorkProcedureData->szValue[TPRD_DATA_VALUE_TA2_UNIT]);

								PROCESS.nCurrentStep = 3990;
							}

							break;

		// 완료
		case	3990	:
							// 작업 시트 업데이트 설정
							PROCESS.bOnUpdateWorkSheet = !pstWorkProcedureData->bOptions[TPRD_DATA_OPT_TA2_UNUSE_UPDATE];
							if (PROCESS.nResultInspection != T_RESULT_SUCCESS)
								PROCESS.bOnUpdateWorkSheet = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// 서브 스텝 : 커맨드 - 하강 PUSH 검사 #2 ///////////////////
		case	STEP_WORK_SUB_CMD_TEST_PUSH_2_DN	:
													MessageWindow(cDEBUG, _T("PROC::CMD_TEST_PUSH_DN_02"));

													PROCESS.nCurrentStep = 4610;
													break;

		// 초기화
		case	4610	:
							// 플래그 초기화
							PROCESS.dblValueRaw			= 0;
							PROCESS.dblValueMeasurement	= 0;
							nCurrentMessageNo			= TPRD_DATA_VALUE_TA3_CAN_MSG;
							nIndexTestDataCAN			= 0;

							// CAN 통신 초기화
							m_devCAN.ClearBuffer();

							// 로드셀 채널 설정
							nCurrentLoadCellNo = pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA3_LCC_NO];
							if (nCurrentLoadCellNo >= MAX_LOADCELL_CHANNEL_USE)
								nCurrentLoadCellNo = LOADCELL_CH01;

							// 로드셀 데이터 초기화
							m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo]		= 0;
							m_stSystemStatus.dblPeakHoldDataLoadCell[nCurrentLoadCellNo]	= 0;

							// CAN 수신 데이터 초기화
							if (pstWorkProcedureData->stCanValue[nCurrentMessageNo].bUsable)
								TPRD_CAN_MSG_Process(pstWorkProcedureData->stCanValue[nCurrentMessageNo]);

							PROCESS.nCurrentStep = 4620;
							break;

		// 파라미터 설정
		case	4620	:
							{
								strParameters.AppendFormat(_T("T_hld=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA3_HOLD]);
								strParameters.AppendFormat(_T("LC_no=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA3_LCC_NO]);
								strParameters.AppendFormat(_T("Jdg=%.2f "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA3_JUDGE]);

								PROCESS.nCurrentStep = 4630;
							}

							break;

		// 현재 상태 체크
		case	4630	:
							if (GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_1_UP) && GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_2_UP)) {
							
								PROCESS.nCurrentStep = 4640;
								break;
							}

							// 결과 설정
							PROCESS.nResultInspection = T_RESULT_ERROR;

							PROCESS.nCurrentStep = 4780;
							break;

		// 지연 시간
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

		// 도어 누름 유닛 #1 : DN
		case	4710	:
							SetDOStatus(DO_ON, DO_SOL_S02_PRODUCT_DOOR_PUSHER_1_DN);
							LTimerTimeOut.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA3_TIMEOUT]);

							PROCESS.nCurrentStep++;
							break;

		case	4711	:
							if (GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_1_DN)) {
							
								// 로드셀 측정 안정화 시간
								LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_MEASUREMENT_1));

								PROCESS.nCurrentStep = 4720;
								break;
							}

							if (LTimerTimeOut.Verify() || 
								m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo] > pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA3_LC_LIMIT]) {
							
								// 디버그 메세지 출력
								MessageWindow(cERROR, _T("LOADCELL OVERLOAD FAILURE!! (%.2f, %.2f)"), m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo], pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA3_LC_LIMIT]);

								// 도어 누름 유닛 #1 : UP
								SetDOStatus(DO_OFF, DO_SOL_S02_PRODUCT_DOOR_PUSHER_1_DN);

								// 검사 결과 설정
								PROCESS.nResultInspection = T_RESULT_FAILURE;

								PROCESS.nCurrentStep = 4780;
							}
							
							break;

		// 판정값 체크
		case	4720	:
							if (LTimerSteady.Verify()) {

								// 1차 판정값 체크
								if (m_stSystemStatus.dblPeakHoldDataLoadCell[nCurrentLoadCellNo] < pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA3_JUDGE]) {

									// 디버그 메세지 출력
									MessageWindow(cERROR, _T("PUSH #1 JUDGEMENT VALUE FAILURE!! (%.2f, %.2f)"), m_stSystemStatus.dblPeakHoldDataLoadCell[nCurrentLoadCellNo], pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA3_JUDGE]);
								
									// 검사 결과 설정
									PROCESS.nResultInspection = T_RESULT_FAILURE;

									PROCESS.nCurrentStep = 4780;
									break;
								}
							
								// 로드셀 데이터 저장
								PROCESS.dblValueRaw = m_stSystemStatus.dblPeakHoldDataLoadCell[nCurrentLoadCellNo];

								PROCESS.nCurrentStep = 4780;
							}

							break;

		// 결과 설정
		case	4780	:
							{
								DOUBLE	dblGain		= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA3_GAIN];
								DOUBLE	dblOffset	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA3_OFFSET];
								DOUBLE	dblSpecMIN	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA3_SPEC_L];
								DOUBLE	dblSpecMAX	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA3_SPEC_H];


								PROCESS.dblValueMeasurement	= (PROCESS.dblValueRaw * dblGain) + dblOffset;

								// 검사 결과 판정
								if (DPS_Round(PROCESS.dblValueMeasurement, 2) < DPS_Round(dblSpecMIN, 2) ||
									DPS_Round(PROCESS.dblValueMeasurement, 2) > DPS_Round(dblSpecMAX, 2))
										PROCESS.nResultInspection = T_RESULT_FAILURE;

								// 검사 데이터 설정
								stFunctionTestData.nResult = PROCESS.nResultInspection;
								_stprintf_s(stFunctionTestData.szValue, MAX_STRINPUT_S, _T("%.2f"), PROCESS.dblValueMeasurement);
								_stprintf_s(stFunctionTestData.szSpecMIN, MAX_STRINPUT, _T("%.2f"), dblSpecMIN);
								_stprintf_s(stFunctionTestData.szSpecMAX, MAX_STRINPUT, _T("%.2f"), dblSpecMAX);
								_tcscpy_s(stFunctionTestData.szUnit, MAX_STRINPUT, pstWorkProcedureData->szValue[TPRD_DATA_VALUE_TA3_UNIT]);

								PROCESS.nCurrentStep = 4790;
							}

							break;

		// 완료
		case	4790	:
							// 작업 시트 업데이트 설정
							PROCESS.bOnUpdateWorkSheet = !pstWorkProcedureData->bOptions[TPRD_DATA_OPT_TA3_UNUSE_UPDATE];
							if (PROCESS.nResultInspection != T_RESULT_SUCCESS)
								PROCESS.bOnUpdateWorkSheet = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// 서브 스텝 : 커맨드 - PUSH LOCK 검사 //////////////////////
		case	STEP_WORK_SUB_CMD_TEST_PUSH_LOCK	:
													MessageWindow(cDEBUG, _T("PROC::CMD_TEST_PUSH_LOCK"));

													PROCESS.nCurrentStep = 4810;
													break;

		// 초기화
		case	4810	:
							// 플래그 초기화
							PROCESS.dblValueRaw			= 0;
							PROCESS.dblValueMeasurement	= 0;
							nCurrentMessageNo			= TPRD_DATA_VALUE_TA4_CAN_MSG;
							nIndexTestDataCAN			= 0;

							// CAN 통신 초기화
							m_devCAN.ClearBuffer();

							// 로드셀 채널 설정
							nCurrentLoadCellNo = pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA4_LCC_NO];
							if (nCurrentLoadCellNo >= MAX_LOADCELL_CHANNEL_USE)
								nCurrentLoadCellNo = LOADCELL_CH01;

							// 로드셀 데이터 초기화
							m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo]		= 0;
							m_stSystemStatus.dblPeakHoldDataLoadCell[nCurrentLoadCellNo]	= 0;

							// CAN 수신 데이터 초기화
							if (pstWorkProcedureData->stCanValue[nCurrentMessageNo].bUsable)
								TPRD_CAN_MSG_Process(pstWorkProcedureData->stCanValue[nCurrentMessageNo]);

							PROCESS.nCurrentStep = 4820;
							break;

		// 파라미터 설정
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

		// 현재 상태 체크
		case	4830	:
							if (GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_1_DN) && GetDIStatus(DI_SENS_S02_PRODUCT_DOOR_PUSHER_2_UP)) {
							
								PROCESS.nCurrentStep = 4840;
								break;
							}

							// 결과 설정
							PROCESS.nResultInspection = T_RESULT_ERROR;

							PROCESS.nCurrentStep = 4880;
							break;

		// 지연 시간
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

		// 도어 누름 유닛 #2 : DN
		case	4910	:
							pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_2_DN]  = TRUE;
							m_stSystemStatus.nSCP_TimeDoorPushLockDown			= pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA4_TIMEOUT];

							PROCESS.nCurrentStep++;
							break;

		case	4911	:
							if (!pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_2_DN]) {
							
								// 홀딩 시간 설정
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

		// 도어 누름 유닛 #2 : UP
		case	4920	:
							pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_2_UP] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	4921	:
							if (!pOnSCP_MoveParts[SCP_S02_PRODUCT_DOOR_PUSHER_2_UP]) {
							
								if (pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA4_MODE] == 1) {

									// 로드셀 측정 안정화 시간
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
							
								// 로드셀 데이터 저장
								PROCESS.dblValueRaw = m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo];

								PROCESS.nCurrentStep = 4980;
							}

							break;

		// 결과 설정
		case	4980	:
							{
								DOUBLE	dblGain		= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA4_GAIN];
								DOUBLE	dblOffset	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA4_OFFSET];
								DOUBLE	dblSpecMIN	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA4_SPEC_L];
								DOUBLE	dblSpecMAX	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_TA4_SPEC_H];


								PROCESS.dblValueMeasurement	= (PROCESS.dblValueRaw * dblGain) + dblOffset;

								// 검사 결과 판정
								if (DPS_Round(PROCESS.dblValueMeasurement, 2) < DPS_Round(dblSpecMIN, 2) ||
									DPS_Round(PROCESS.dblValueMeasurement, 2) > DPS_Round(dblSpecMAX, 2))
										PROCESS.nResultInspection = T_RESULT_FAILURE;

								// 검사 데이터 설정
								stFunctionTestData.nResult = PROCESS.nResultInspection;
								_stprintf_s(stFunctionTestData.szValue, MAX_STRINPUT_S, _T("%.2f"), PROCESS.dblValueMeasurement);
								_stprintf_s(stFunctionTestData.szSpecMIN, MAX_STRINPUT, _T("%.2f"), dblSpecMIN);
								_stprintf_s(stFunctionTestData.szSpecMAX, MAX_STRINPUT, _T("%.2f"), dblSpecMAX);
								_tcscpy_s(stFunctionTestData.szUnit, MAX_STRINPUT, pstWorkProcedureData->szValue[TPRD_DATA_VALUE_TA4_UNIT]);

								PROCESS.nCurrentStep = 4990;
							}

							break;

		// 완료
		case	4990	:
							// 작업 시트 업데이트 설정
							PROCESS.bOnUpdateWorkSheet = pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA4_MODE] == 0 ? FALSE : !pstWorkProcedureData->bOptions[TPRD_DATA_OPT_TA4_UNUSE_UPDATE];
							if (PROCESS.nResultInspection != T_RESULT_SUCCESS)
								PROCESS.bOnUpdateWorkSheet = pstWorkProcedureData->nValue[TPRD_DATA_VALUE_TA4_MODE] == 0 ? FALSE : TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// 서브 스텝 : 커맨드 - 통신 검사 ///////////////////////////
		case	STEP_WORK_SUB_CMD_TEST_COMM	:
												MessageWindow(cDEBUG, _T("PROC::CMD_TEST_COMM"));

												PROCESS.nCurrentStep = 4010;
												break;

		// 초기화
		case	4010	:
							// 플래그 초기화
							nCurrentMessageNo	= TPRD_DATA_VALUE_TC_CAN_MSG;
							nIndexTestDataCAN	= 0;

							// CAN 통신 초기화
							m_devCAN.ClearBuffer();

							PROCESS.nCurrentStep = 4020;
							break;

		// 파라미터 설정
		case	4020	:
							{
								PROCESS.nCurrentStep = 4100;
							}

							break;

		// CAN 메세지 데이터 체크
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

		// CAN 메세지 송신
		case	4110	:
							ZeroMemory(&stSendPacket, sizeof(PCAN_PACKET_T));
							stSendPacket.stMessage.ID		= pstWorkProcedureData->stCanValue[nCurrentMessageNo].nCAN_ID;
							stSendPacket.stMessage.DLC		= pstWorkProcedureData->stCanValue[nCurrentMessageNo].nDLC;
							stSendPacket.stMessage.MSGTYPE	= PCAN_MESSAGE_STANDARD;
							memcpy_s(stSendPacket.stMessage.DATA, MAX_CAN_MSG_BYTE, pstWorkProcedureData->stCanValue[nCurrentMessageNo].abData, MAX_CAN_MSG_BYTE);
							m_devCAN.SendPacket(stSendPacket);
							 
							// 송신 타임 아웃 설정
							LTimerTimeOut.Start(pstWorkProcedureData->stCanValue[nCurrentMessageNo].nTimeout);

							// 검사 데이터 설정
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

		// CAN 메세지 수신
		case	4120	:
							// 수신 타임 아웃 설정
							LTimerTimeOut.Start(pstWorkProcedureData->stCanValue[nCurrentMessageNo].nTimeout);

							PROCESS.nCurrentStep++;
							break;

		case	4121	:
							if (m_devCAN.ReadPacket(stReadPacket)) {
								
								if (stReadPacket.stMessage.ID == pstWorkProcedureData->stCanValue[nCurrentMessageNo].nCAN_ID) {

									// 디버그 메세지
									CString	strDebugMessage = _T("");
									for (UINT nIndex = 0; nIndex < MAX_CAN_MSG_BYTE; nIndex++)	strDebugMessage.AppendFormat(_T("%02X "), stSendPacket.stMessage.DATA[nIndex]);
									NormalMessage(TRUE, _T("CAN SEND => %s"), strDebugMessage);

									strDebugMessage.Empty();
									for (UINT nIndex = 0; nIndex < MAX_CAN_MSG_BYTE; nIndex++)	strDebugMessage.AppendFormat(_T("%02X "), stReadPacket.stMessage.DATA[nIndex]);
									NormalMessage(TRUE, _T("CAN READ => %s"), strDebugMessage);

									// 수신 데이터 검증
									if (TPRD_CAN_MSG_VERIFY_Process(stReadPacket, pstWorkProcedureData->stCanValue[nCurrentMessageNo])) {

										// 검사 데이터 설정
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

							// 타임 아웃
							if (LTimerTimeOut.Verify()) {

								// 검사 데이터 설정
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

		// 불합격 판정 시 재검사
		case	4180	:
							if (m_SystemConfig.UseSystemOption(SOPT_RETRY_WORK_NG)) {

								if (PROCESS.nResultInspection != T_RESULT_SUCCESS) {

									// 재시도 카운트 체크
									if (++PROCESS.nRetryCount <= m_SystemConfig.GetWorkRetryCount()) {

										// 플래그 초기화
										PROCESS.nResultInspection = T_RESULT_SUCCESS;

										PROCESS.nCurrentStep = 4010;
										break;
									}
								}
							}

							PROCESS.nCurrentStep = 4190;
							break;

		// 완료
		case	4190	:
							// 검사 데이터 설정
							stFunctionTestData.nResult = PROCESS.nResultInspection;

							// 작업 시트 업데이트 설정
							PROCESS.bOnUpdateWorkSheet = !pstWorkProcedureData->bOptions[TPRD_DATA_OPT_TC_UNUSE_UPDATE];
							if (PROCESS.nResultInspection != T_RESULT_SUCCESS)
								PROCESS.bOnUpdateWorkSheet = TRUE;


							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// 서브 스텝 : 커맨드 - 비전 검사 (머신비전) ////////////////
		case	STEP_WORK_SUB_CMD_TEST_VISION_1	:
													MessageWindow(cDEBUG, _T("PROC::CMD_TEST_VISION_01"));

													PROCESS.nCurrentStep = 4210;
													break;

		// 초기화
		case	4210	:
							// 플래그 초기화
							PROCESS.bResultMainProcess = FALSE;

							// 현재 프로시저 번호 설정
							m_stSystemStatus.nCurrentWorkProcedureNo = PROCESS.nCurrentProcedureNo;

							// 비전 검사 항목 설정
							PROCESS.nCurrentWorkSheetNo = pstWorkProcedureData->nValue[TPRD_DATA_VALUE_VISION_01_TEST_NO] - 1;
							m_stSystemStatus.nMainProcessWorkIndex[nSTATION_NO][STN1_SUB_VISION] = PROCESS.nCurrentWorkSheetNo;

							// 검사 시트 초기화
							ZeroMemory((PROCESS.pstWorkStatus)->stMeasSheet, sizeof(MEAS_SHEET_T) * MAX_TEST_SHEET);

							PROCESS.nCurrentStep = 4220;
							break;

		// 파라미터 설정
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

		// 검사 시작
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

		// 결과 설정
		case	4310	:
							{
								// 검사 데이터 설정
								stFunctionTestData.nResult = (PROCESS.pstWorkStatus)->stMeasSheet[PROCESS.nCurrentWorkSheetNo].nResult;
								_stprintf_s(stFunctionTestData.szValue, MAX_STRINPUT_S, _T("%s"), PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].szUserDefName);

								// 검사 결과 설정
								PROCESS.nResultInspection = (PROCESS.pstWorkStatus)->stMeasSheet[PROCESS.nCurrentWorkSheetNo].nResult;

								PROCESS.nCurrentStep = 4390;
							}

							break;

		// 완료
		case	4390	:
							// 작업 시트 업데이트 설정
							PROCESS.bOnUpdateWorkSheet = !pstWorkProcedureData->bOptions[TPRD_DATA_OPT_VISION_01_UNUSE_UPDATE];
							if (PROCESS.nResultInspection != T_RESULT_SUCCESS)
								PROCESS.bOnUpdateWorkSheet = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// 서브 스텝 : 커맨드 - 비전 검사 (비전센서) ////////////////
		case	STEP_WORK_SUB_CMD_TEST_VISION_2	:
													MessageWindow(cDEBUG, _T("PROC::CMD_TEST_VISION_02"));

													PROCESS.nCurrentStep = 4410;
													break;

		// 초기화
		case	4410	:
							// 플래그 초기화
							PROCESS.bResultMainProcess	= FALSE;
							PROCESS.nUpdateWorkSheetNo	= m_stSystemStatus.nCurrentVisionWorkSheetUpdateNo;
							bOnVisionTrigged			= FALSE;

							// 현재 프로시저 번호 설정
							m_stSystemStatus.nCurrentWorkProcedureNo = PROCESS.nCurrentProcedureNo;

							// 비전 검사 항목 설정
							PROCESS.nCurrentWorkSheetNo = pstWorkProcedureData->nValue[TPRD_DATA_VALUE_VISION_02_PGM_NO];

							// 검사 시트 초기화
							ZeroMemory((PROCESS.pstWorkStatus)->stMeasSheet, sizeof(MEAS_SHEET_T) * MAX_TEST_SHEET);

							// 비전 이미지 삭제
							DPS_DeleteDirectory(m_SystemConfig.GetWorkDirectory(DIR_IMPORT_DATA), FALSE);

							// 비전 이미지 윈도우 초기화
							if (m_pMainWnd)	{
								
								m_stSystemStatus.bIsVisionImageWindowCleared = FALSE;
								m_pMainWnd->PostMessage(UM_VISION_CLEAR_IMAGE);
							}

							PROCESS.nCurrentStep = 4420;
							break;

		// 파라미터 설정
		case	4420	:
							{
								strParameters.AppendFormat(_T("Pgm_no=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_VISION_02_PGM_NO]);

								PROCESS.nCurrentStep = 4440;
							}

							break;

		// 비전 유닛 초기화
		case	4440	:
							// 비전 오류 체크
							if (GetDIStatus(DI_SIG_S02_VISION_ERROR)) {
							
								PROCESS.nResultInspection	= T_RESULT_ERROR;
								PROCESS.nCurrentStep		= 4580;
								break;
							}

							// 비전 프로그램 번호 설정
							VISION_SelectProgramNo(TRUE, PROCESS.nCurrentWorkSheetNo);
							LTimerSteady.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_VISION_SENSOR));

							PROCESS.nCurrentStep = 4500;
							break;

		// 검사 시작
		case	4500	:
							if (LTimerSteady.Verify()) {
							
								// 비전 시작
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
							
								// BUSY 체크
								if (!GetDIStatus(DI_SIG_S02_VISION_BUSY)) {
								
									if (GetDIStatus(DI_SIG_S02_VISION_RESULT))	PROCESS.nResultInspection = T_RESULT_SUCCESS;
									else										PROCESS.nResultInspection = T_RESULT_FAILURE;

									PROCESS.nCurrentStep++;
								}
							}

							break;

		case	4502	:
							{
								// 비전 이미지 파일 이름 설정
								strVisionImageName.Empty();
								strVisionImageName.Format(	_T("%s\\%05d_%02d_%s.BMP"),		
															m_SystemConfig.GetWorkDirectory(DIR_IMPORT_DATA),
															0,
															PROCESS.nCurrentWorkSheetNo,
															PROCESS.nResultInspection == T_RESULT_SUCCESS ? _T("OK") : _T("NG"));

								MessageWindow(cDEBUG, _T("VISION IMG=%s"), strVisionImageName);

								// 비젼 결과 파일 이름 설정
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

								// 비전 이미지 생성 체크
								if (fileFinderImage.FindFile(strVisionImageName) && fileFinderResult.FindFile(strVisionResultName)) {

									// 비젼 결과 가져오기
									if (!VISION_ImportResult(strVisionResultName, stVisionResult)) {

										PROCESS.nResultInspection = T_RESULT_ERROR;
									}

									// 결과 파일 복사
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

								// 타임 아웃
								if (LTimerTimeOut.Verify()) {

									// 결과 설정
									PROCESS.nResultInspection = T_RESULT_ERROR;
								
									// 메세지 출력
									if (m_nTypeLanguage == LANGUAGE_KOR)	ErrorMessage(TRUE, _T("비전 센서 이미지를 로드할 수 없습니다."));
									else									ErrorMessage(TRUE, _T("Vision Sensor Result Image Failure."));

									PROCESS.nCurrentStep++;
								}
							}

							break;

		case	4504	:
							// 비전 트리거 해제
							SetDOStatus(DO_OFF, DO_SIG_S02_VISION_TRIG);	

							PROCESS.nCurrentStep = 4520;
							break;

		// 이미지 설정
		case	4520	:
							if (PROCESS.nResultInspection != T_RESULT_ERROR) {

								// 이미지 업데이트
								if (m_MilImageInspection[PROCESS.nCurrentWorkSheetNo] != M_NULL) {

									MbufFree(m_MilImageInspection[PROCESS.nCurrentWorkSheetNo]);
									m_MilImageInspection[PROCESS.nCurrentWorkSheetNo] = M_NULL;
								}

								MbufImport((MIL_TEXT_CHAR*)(LPCTSTR)strVisionImageName, M_DEFAULT, M_RESTORE, m_MilSystem, &m_MilImageInspection[PROCESS.nCurrentWorkSheetNo]);

								// 이미지 윈도우에 로딩
								if (m_pMainWnd)	m_pMainWnd->SendMessage(UM_VISION_LOAD_IMAGE, VISION_CH1, (LPARAM)m_MilImageInspection[PROCESS.nCurrentWorkSheetNo]);

								// 상시 이미지 저장
								if (m_SystemConfig.UseSystemOption(SOPT_SAVE_VISION_IMAGE))			SaveVisionImage(PROCESS.nCurrentWorkSheetNo, FALSE);
								if (m_SystemConfig.UseSystemOption(SOPT_SAVE_VISION_IMAGE_JPEG))	SaveVisionImage(PROCESS.nCurrentWorkSheetNo, FALSE, TRUE);

								// 불합격 판정 시 비전 검사 이미지 저장
								if (m_SystemConfig.UseSystemOption(SOPT_SAVE_VISION_IMAGE_NG) && PROCESS.nResultInspection == T_RESULT_FAILURE)
									SaveVisionImage(PROCESS.nCurrentWorkSheetNo, FALSE);
							}

							PROCESS.nCurrentStep = 4580;
							break;

		// 결과 설정
		case	4580	:
							{
								// 검사 데이터 설정
								stFunctionTestData.nResult = PROCESS.nResultInspection;
								_stprintf_s(stFunctionTestData.szValue, MAX_STRINPUT_S, _T("%s"), pstWorkProcedureData->szName);

								// 검사 결과 설정
								(PROCESS.pstWorkStatus)->stMeasSheet[PROCESS.nCurrentWorkSheetNo].nResult = PROCESS.nResultInspection;

								PROCESS.nCurrentStep = 4590;
							}

							break;

		// 완료
		case	4590	:
							// 작업 시트 업데이트 설정
							PROCESS.bOnUpdateWorkSheet = !pstWorkProcedureData->bOptions[TPRD_DATA_OPT_VISION_02_UNUSE_UPDATE];
							if (PROCESS.nResultInspection != T_RESULT_SUCCESS)
								PROCESS.bOnUpdateWorkSheet = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// 서브 스텝 : 커맨드 - 시간 지연 ///////////////////////////
		case	STEP_WORK_SUB_CMD_DELAY	:
											MessageWindow(cDEBUG, _T("PROC::CMD_DELAY"));

											PROCESS.nCurrentStep = 5010;
											break;

		// 초기화
		case	5010	:
							PROCESS.nCurrentStep = 5020;
							break;

		// 파라미터 설정
		case	5020	:
							{
								strParameters.AppendFormat(_T("T_dly=%d "),	pstWorkProcedureData->nValue[TPRD_DATA_VALUE_DELAY_TIME]);

								PROCESS.nCurrentStep = 5050;
							}

							break;

		// 지연 시간 설정
		case	5050	:
							LTimerProceed.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_DELAY_TIME]);

							PROCESS.nCurrentStep++;
							break;

		case	5051	:
							if (LTimerProceed.Verify())
								PROCESS.nCurrentStep = 5190;

							break;

		// 완료
		case	5190	:
							// 검사 데이터 설정
							stFunctionTestData.nResult = PROCESS.nResultInspection;
							_stprintf_s(stFunctionTestData.szValue, MAX_STRINPUT_S, _T("%d"), pstWorkProcedureData->nValue[TPRD_DATA_VALUE_DELAY_TIME]);
							_tcscpy_s(stFunctionTestData.szUnit, MAX_STRINPUT, _T("msec"));

							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// 서브 스텝 : 파워 서플라이 설정 ///////////////////////////
		case	STEP_WORK_SUB_SET_PS	:
											MessageWindow(cDEBUG, _T("PROC::SUB-SET PS"));

											PROCESS.nCurrentStep = m_SystemConfig.IsSimulationMode() ? 6090 : 6010;
											break;

		// 초기화
		case	6010	:
							PROCESS.nRetryCount		= 0;
							PROCESS.nRetrySubCount	= 0;

							PROCESS.nCurrentStep = bSetupState ? 6020 : 6030;
							break;

		// 전압/전류 설정
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

									// 전압 소수점 1자리, 전류 소수점 2자리 비교
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

		// 출력 상태 설정
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
								
		// 오류
		case	6080	:
							// 메세지 출력
							ErrorMessage(TRUE, _T("파워소스가 응답하지 않습니다."));

							PROCESS.nCurrentStep = STEP_WORK_ERROR_DEVICE;
							break;

		// 완료
		case	6090	:
							PROCESS.nCurrentStep = PROCESS.nReturn03Step;
							break;


		/////////////////////////////////////////////////////////////
		// 서브 스텝 : 파워 서플라이 측정 ///////////////////////////
		case	STEP_WORK_SUB_GET_PS	:
											MessageWindow(cDEBUG, _T("PROC::SUB-GET PS"));

											PROCESS.nCurrentStep = 6110;
											break;

		// 초기화
		case	6110	:
							PROCESS.nRetryCount			= 0;
							PROCESS.nRetrySubCount		= 0;
							PROCESS.dblValueMeasurement	= 0;

							PROCESS.nCurrentStep = 6120;
							break;

		// 전압/전류 측정
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

		// 오류
		case	6180	:
							// 메세지 출력
							ErrorMessage(TRUE, _T("파워소스가 응답하지 않습니다."));

							PROCESS.nCurrentStep = STEP_WORK_ERROR_DEVICE;
							break;

		// 완료
		case	6190	:
							PROCESS.nCurrentStep = PROCESS.nReturn03Step;
							break;


		/////////////////////////////////////////////////////////////
		// 오류 /////////////////////////////////////////////////////
		case	STEP_WORK_ERROR	:
									PROCESS.bOnOperatingStop = TRUE;
									break;

		case	STEP_WORK_ERROR_PARTS	:
											PROCESS.bOnError				= TRUE;
											PROCESS.nRecoveryStep			= STEP_WORK_ERROR;
											PROCESS.stErrorCode.nErrorCode	= ERROR_MACHINE_SEQUENCE;
											PROCESS.stErrorCode.nProcessID	= PROCESS_MAIN_WORK_TEST;
											PROCESS.stErrorCode.nStationNo	= nSTATION_NO;

											// 디버그 메세지
											SDebugMessage(TRUE, _T("[P%d:%d] ERROR PARTS"), nSTATION_NO, nSTATION_SUB_NO + 1);
											break;

		case	STEP_WORK_ERROR_SYSTEM	:
											// 디버그 메세지
											SDebugMessage(TRUE, _T("[P%d:%d] ERROR SYSTEM"), nSTATION_NO, nSTATION_SUB_NO + 1);
											break;	

		case	STEP_WORK_ERROR_DEVICE	:
											// 디버그 메세지
											SDebugMessage(TRUE, _T("[P%d:%d] ERROR DEVICE"), nSTATION_NO, nSTATION_SUB_NO + 1);

											// 메세지 출력
											ErrorMessage(TRUE, _T("[P%d] NO RESPONSE DEVICE"), nSTATION_NO);

											// 프로세스 플래그 초기화
											m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]				= FALSE;
											m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
											m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
											m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
											m_stSystemStatus.bIsMainProcessInitialized[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;

											PROCESS.nCurrentStep = STEP_WORK_STANDBY;
											break;	


		/////////////////////////////////////////////////////////////
		// 일시 정지 스텝 ///////////////////////////////////////////
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

		// 스텝 복구
		case	20100	:
							PROCESS.nCurrentStep	= PROCESS.nRecoveryStep;
							PROCESS.bOnPause		= FALSE;
							break;


		/////////////////////////////////////////////////////////////
		// 비상 정지 스텝 ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop)	{

									PROCESS.nRecoveryStep	= 0;
									PROCESS.nCurrentStep	= STEP_PAUSE;
								}

								break;


		/////////////////////////////////////////////////////////////
		// 장비 초기화 스텝 /////////////////////////////////////////
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
	// 비전 시작 시그널 해제 ////////////////////////////////////////
	if (bOnVisionTrigged && LTimerSignal.Verify()) {
	
		SetDOStatus(DO_OFF, DO_SIG_S02_VISION_TRIG);
		bOnVisionTrigged = FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// 운전 정지 체크 ///////////////////////////////////////////////
	CheckProcessOperatingStop(PROCESS);


	/////////////////////////////////////////////////////////////////
	// 일반 /////////////////////////////////////////////////////////
	CheckProcessGeneral(nSTATION_NO, PROCESS);


	/////////////////////////////////////////////////////////////////
	// 스텝 모니터링 ////////////////////////////////////////////////
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
// 프로세스 : 메인 작업 (일반 검사) ///////////////////////////////////////////
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
	// 프로세스 데이터 초기화 ///////////////////////////////////////
	ProcessDataInitialize(PROCESS);


	/////////////////////////////////////////////////////////////////
	// 자동 운전 시작/정지 초기화 ///////////////////////////////////
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
	// 장비 초기화 //////////////////////////////////////////////////
	if (CheckProcessMachineInitialize(PROCESS))
		return	NULL;


	/////////////////////////////////////////////////////////////////
	// 수동 제어 모드 ///////////////////////////////////////////////
	PROCESS.bOnManualControlMode = m_stSystemStatus.bIsManualControl[nSTATION_NO];


	/////////////////////////////////////////////////////////////////
	// 비상/일시 정지 상태 //////////////////////////////////////////
	if (CheckProcessEmergencyStop(PROCESS))					return	NULL;
	if (CheckProcessOperatingPause(nSTATION_NO, PROCESS))	return	NULL;


	/////////////////////////////////////////////////////////////////
	// 스텝 프로세스 ////////////////////////////////////////////////
	switch (PROCESS.nCurrentStep) {

		case	0		:
							PROCESS.nCurrentStep = 10;
							break;

		// 시스템 체크
		case	10		:
							if (IsSystemReady()) {
							
								PROCESS.nCurrentStep = 20;
							}
								
							break;

		// 프로세스 초기화
		case	20		:
							m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]				= FALSE;
							m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
							m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
							m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
							m_stSystemStatus.bIsMainProcessInitialized[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;

							PROCESS.nCurrentStep = 90;
							break;

		// 완료
		case	90		:
							PROCESS.nCurrentStep = STEP_WORK_STANDBY;
							break;


		/////////////////////////////////////////////////////////////
		// 초기화 ///////////////////////////////////////////////////
		case	STEP_WORK_INIT	:
									PROCESS.nCurrentStep = 110;
									break;

		// 플래그 초기화
		case	110		:
							PROCESS.nCurrentStep = 130;
							break;

		// 제어 신호 초기화
		case	130		:
							PROCESS.nCurrentStep = 190;
							break;

		// 완료
		case	190		:
							// 초기화 완료 플래그 설정
							m_stSystemStatus.bIsMainProcessInitialized[nSTATION_NO][nSTATION_SUB_NO] = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn01Step;
							break;


		/////////////////////////////////////////////////////////////
		// 대기 /////////////////////////////////////////////////////
		case	STEP_WORK_STANDBY	:
										PROCESS.nCurrentStep = 220;
										break;

		// 프로세스 대기
		case	220		:
							if (m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO] ||
								m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]) {

								m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;
								m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;

								PROCESS.nCurrentStep = 230;
							}

							break;
							
		// 모델 프로파일 로드
		case	230		:
							PROCESS.pstModelProfile	= (PMODEL_PROFILE_T)m_ModelProfile.GetCurrentModel();
							PROCESS.pstWorkStatus	= GetWorkStatus(nSTATION_NO);

							if (PROCESS.pstModelProfile != NULL) {

								PROCESS.pstModelProfileConfig	= &((PROCESS.pstModelProfile)->stModelProfileConfig);
								PROCESS.pstWorkInfo				= &((PROCESS.pstModelProfileConfig)->stWorkInfo);
								
								PROCESS.nCurrentStep = 280;
								break;
							}

							SErrorMessage(TRUE, _T("[S%02d/%s] 모델 정보를 로드할 수 없습니다."),	nSTATION_NO, 
																									g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

							PROCESS.nCurrentStep = STEP_WORK_ERROR_SYSTEM;
							break;

		// 초기화
		case	280		:
							PROCESS.nCurrentStep	= STEP_WORK_INIT;
							PROCESS.nReturn01Step	= 290;
							break;

		// 완료
		case	290		:
							PROCESS.nCurrentStep = STEP_WORK_START;
							break;


		/////////////////////////////////////////////////////////////
		// 작업 /////////////////////////////////////////////////////
		case	STEP_WORK_START	:
									PROCESS.nCurrentStep = 410;
									break;

		// 준비
		case	410		:
							// 작업 정보 초기화
							bResultProcess				= TRUE;
							PROCESS.nRetryCount			= 0;
							PROCESS.nResultInspection	= T_RESULT_SUCCESS;

							// 프로시저 데이터 설정
							pstWorkProcedureData = &m_pstTestProcedureData[m_stSystemStatus.nCurrentWorkProcedureNo];

							PROCESS.nCurrentStep = 440;
							break;

		// 검사 지연 설정
		case	440		:
							LTimerSteady.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_DELAY]);
							
							PROCESS.nCurrentStep++;
							break;

		case	441		:
							if (LTimerSteady.Verify())
								PROCESS.nCurrentStep = 450;

							break;

		// 작업 완료 체크
		case	450		:
							{
								BOOL	bIsStopProcess	= FALSE;

								// 작업 정지
								if (m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO])
									bIsStopProcess = TRUE;

								PROCESS.nCurrentStep = bIsStopProcess ? 490 : 460;
							}

							break;

		// 작업 시작
		case	460		:
							// 검사 시간 설정
							LTimerTimeOutProcess.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_TIME]);

							// 단일 측정 모드
							if (m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO]) {
							
								PROCESS.nCurrentStep  = STEP_WORK_SUB_TEST;
								PROCESS.nReturn01Step = 490;
								break;
							}

							// 연속 측정 모드
							PROCESS.nCurrentStep  = STEP_WORK_SUB_TEST_EX;
							PROCESS.nReturn01Step = 490;
							break;

		// 완료
		case	490		:
							PROCESS.nCurrentStep = STEP_WORK_DONE;
							break;


		/////////////////////////////////////////////////////////////
		// 단일 측정 ////////////////////////////////////////////////
		case	STEP_WORK_SUB_TEST	:
										PROCESS.nCurrentStep = 2010;
										break;

		// 검사 준비
		case	2010	:
							{
								// 평균 측정 사용 여부
								PROCESS.bOnAverageMeasurement = (BOOL)pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_USE_AVG];

								// 평균 측정 모드
								if (PROCESS.bOnAverageMeasurement) {
								
									PROCESS.dblValueMeasurementSUM		= 0;
									PROCESS.nIndexAverageMeasurement	= 0;
								}

								PROCESS.nCurrentStep = 2050;
							}

							break;

		// 측정
		case	2050	:
							if (LTimerSteadyDMM.Verify()) {

								DOUBLE	dblRange	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_DEV_RANGE];

								if (!m_devDMM.GetMeasurementValue(stMeasurementData, dblRange)) {

									ErrorMessage(TRUE, _T("디지털 멀티미터가 응답하지 않습니다."));
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

								// 측정 간격 설정
								LTimerSteadyDMM.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_INTV]);

								PROCESS.nCurrentStep--;
							}

							break;

		// 판정
		case	2080	:
							{
								BOOL	bIsABS		= (BOOL)pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_USE_ABS];
								DOUBLE	dblGain		= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_GAIN];
								DOUBLE	dblOffset	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_OFFSET];
								DOUBLE	dblSpecMIN	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_SPEC_L];
								DOUBLE	dblSpecMAX	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_SPEC_H];
		
								PROCESS.dblValueRaw			= stMeasurementData.dblMeasValue;
								PROCESS.dblValueMeasurement	= (PROCESS.dblValueRaw * dblGain) + dblOffset;

								// 절대값 판정
								if (bIsABS)		PROCESS.dblValueMeasurement = abs(PROCESS.dblValueMeasurement);

								// 검사 결과 판정
								if (DPS_Round(PROCESS.dblValueMeasurement, 4) < DPS_Round(dblSpecMIN, 4) ||
									DPS_Round(PROCESS.dblValueMeasurement, 4) > DPS_Round(dblSpecMAX, 4))
										PROCESS.nResultInspection = T_RESULT_FAILURE;

								// 검사 결과 설정
								(PROCESS.pstWorkStatus)->stMeasSheet[0].dblRawValue			= PROCESS.dblValueRaw;
								(PROCESS.pstWorkStatus)->stMeasSheet[0].dblMeasurementValue	= PROCESS.dblValueMeasurement;
								(PROCESS.pstWorkStatus)->stMeasSheet[0].dblSpecMIN			= dblSpecMIN;
								(PROCESS.pstWorkStatus)->stMeasSheet[0].dblSpecMAX			= dblSpecMAX;
								(PROCESS.pstWorkStatus)->stMeasSheet[0].nResult				= PROCESS.nResultInspection;
								_tcscpy_s((PROCESS.pstWorkStatus)->stMeasSheet[0].szUnit, MAX_STRINPUT, pstWorkProcedureData->szValue[TPRD_DATA_VALUE_MEAS_UNIT]);

								PROCESS.nCurrentStep = 2090;
							}

							break;

		// 완료
		case	2090	:
							PROCESS.nCurrentStep = PROCESS.nReturn01Step;
							break;


		/////////////////////////////////////////////////////////////
		// 연속 측정 ////////////////////////////////////////////////
		case	STEP_WORK_SUB_TEST_EX	:
											PROCESS.nCurrentStep = 2110;
											break;

		// 검사 준비
		case	2110	:
							{
								// 연속 측정 데이터 초기화
								m_arrContiMeasData.RemoveAll();

								// 타임 스탬프 초기화
								LCounterMeasurement.Reset();

								PROCESS.nCurrentStep = 2150;
							}

							break;

		// 측정
		case	2150	:
							if (LTimerSteadyDMM.Verify()) {

								DOUBLE	dblRange	= pstWorkProcedureData->dblValue[TPRD_DATA_VALUE_MEAS_START_DEV_RANGE];

								if (!m_devDMM.GetMeasurementValue(stMeasurementData, dblRange)) {

									ErrorMessage(TRUE, _T("디지털 멀티미터가 응답하지 않습니다."));
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

								// 검사 데이터 저장
								ZeroMemory(&stMeasData, sizeof(CONTI_MEAS_DATA_T));
								stMeasData.dblValue		= PROCESS.dblValueMeasurement;
								stMeasData.nTimeStamp	= LCounterMeasurement.GetCounterMsec();
								m_arrContiMeasData.Add(stMeasData);

								// 판정값 정지 (최소값)
								if (bOnJudgeStopMIN && PROCESS.dblValueMeasurement < dblValueJudge)
									bOnMeasStop = TRUE;

								// 판정값 정지 (최대값)
								if (bOnJudgeStopMAX && PROCESS.dblValueMeasurement > dblValueJudge)
									bOnMeasStop = TRUE;

								// 검사 시간 체크
								if (bOnMeasStop || LTimerTimeOutProcess.Verify()) {

									stMeasurementData.dblMeasValue = PROCESS.dblValueMeasurementSUM / (DOUBLE)PROCESS.nIndexAverageMeasurement;
									MessageWindow(cDEBUG, _T("[MEAS_CONTI] Count = %d"), m_arrContiMeasData.GetCount());

									PROCESS.nCurrentStep = 2190;
									break;
								}

								// 측정 간격 설정
								LTimerSteadyDMM.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_MEAS_START_INTV]);

								PROCESS.nCurrentStep--;
							}

							break;

		// 완료
		case	2190	:
							PROCESS.nCurrentStep = PROCESS.nReturn01Step;
							break;


		/////////////////////////////////////////////////////////////
		// 완료 /////////////////////////////////////////////////////
		case	STEP_WORK_DONE	:
									PROCESS.nCurrentStep = 590;
									break;

		// 완료
		case	590		:
							// 메인 프로세스 완료
							m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;
							m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;
							m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]	= bResultProcess;

							PROCESS.nCurrentStep = STEP_WORK_STANDBY;
							break;


		/////////////////////////////////////////////////////////////
		// 오류 /////////////////////////////////////////////////////
		case	STEP_WORK_ERROR	:
									PROCESS.bOnOperatingStop = TRUE;
									break;

		case	STEP_WORK_ERROR_PARTS	:
											PROCESS.bOnError				= TRUE;
											PROCESS.nRecoveryStep			= STEP_WORK_ERROR;
											PROCESS.stErrorCode.nErrorCode	= ERROR_MACHINE_SEQUENCE;
											PROCESS.stErrorCode.nProcessID	= PROCESS_MAIN_WORK_TEST;
											PROCESS.stErrorCode.nStationNo	= nSTATION_NO;

											// 디버그 메세지
											SDebugMessage(TRUE, _T("[P%d:%d] ERROR PARTS"), nSTATION_NO, nSTATION_SUB_NO + 1);
											break;

		case	STEP_WORK_ERROR_SYSTEM	:
											// 디버그 메세지
											SDebugMessage(TRUE, _T("[P%d:%d] ERROR SYSTEM"), nSTATION_NO, nSTATION_SUB_NO + 1);
											break;	

		case	STEP_WORK_ERROR_DEVICE	:
											// 디버그 메세지
											SDebugMessage(TRUE, _T("[P%d:%d] ERROR DEVICE"), nSTATION_NO, nSTATION_SUB_NO + 1);

											// 메세지 출력
											ErrorMessage(TRUE, _T("[P%d] NO RESPONSE DEVICE"), nSTATION_NO);

											// 프로세스 플래그 초기화
											m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]				= FALSE;
											m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
											m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
											m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
											m_stSystemStatus.bIsMainProcessInitialized[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;

											PROCESS.nCurrentStep = STEP_WORK_STANDBY;
											break;	


		/////////////////////////////////////////////////////////////
		// 일시 정지 스텝 ///////////////////////////////////////////
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

		// 스텝 복구
		case	20100	:
							PROCESS.nCurrentStep	= PROCESS.nRecoveryStep;
							PROCESS.bOnPause		= FALSE;
							break;


		/////////////////////////////////////////////////////////////
		// 비상 정지 스텝 ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop)	{

									PROCESS.nRecoveryStep	= 0;
									PROCESS.nCurrentStep	= STEP_PAUSE;
								}

								break;


		/////////////////////////////////////////////////////////////
		// 장비 초기화 스텝 /////////////////////////////////////////
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
	// 운전 정지 체크 ///////////////////////////////////////////////
	CheckProcessOperatingStop(PROCESS);


	/////////////////////////////////////////////////////////////////
	// 일반 /////////////////////////////////////////////////////////
	CheckProcessGeneral(nSTATION_NO, PROCESS);


	/////////////////////////////////////////////////////////////////
	// 스텝 모니터링 ////////////////////////////////////////////////
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
// 프로세스 : 메인 작업 (비전 검사) ///////////////////////////////////////////
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
	// 프로세스 데이터 초기화 ///////////////////////////////////////
	ProcessDataInitialize(PROCESS);


	/////////////////////////////////////////////////////////////////
	// 자동 운전 시작/정지 초기화 ///////////////////////////////////
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
	// 장비 초기화 //////////////////////////////////////////////////
	if (CheckProcessMachineInitialize(PROCESS))
		return	NULL;


	/////////////////////////////////////////////////////////////////
	// 수동 제어 모드 ///////////////////////////////////////////////
	PROCESS.bOnManualControlMode = m_stSystemStatus.bIsManualControl[nSTATION_NO];


	/////////////////////////////////////////////////////////////////
	// 비상/일시 정지 상태 //////////////////////////////////////////
	if (CheckProcessEmergencyStop(PROCESS))					return	NULL;
	if (CheckProcessOperatingPause(nSTATION_NO, PROCESS))	return	NULL;


	/////////////////////////////////////////////////////////////////
	// 스텝 프로세스 ////////////////////////////////////////////////
	switch (PROCESS.nCurrentStep) {

		case	0		:
							PROCESS.nCurrentStep = 10;
							break;

		// 시스템 체크
		case	10		:
							if (IsSystemReady()) {
							
								PROCESS.nCurrentStep = 20;
							}
								
							break;

		// 프로세스 초기화
		case	20		:
							m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]				= FALSE;
							m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
							m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
							m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
							m_stSystemStatus.bIsMainProcessInitialized[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;

							PROCESS.nCurrentStep = 90;
							break;

		// 완료
		case	90		:
							PROCESS.nCurrentStep = STEP_WORK_STANDBY;
							break;


		/////////////////////////////////////////////////////////////
		// 초기화 ///////////////////////////////////////////////////
		case	STEP_WORK_INIT	:
									PROCESS.nCurrentStep = 110;
									break;

		// 플래그 초기화
		case	110		:
							PROCESS.nCurrentStep = 190;
							break;

		// 완료
		case	190		:
							// 초기화 완료 플래그 설정
							m_stSystemStatus.bIsMainProcessInitialized[nSTATION_NO][nSTATION_SUB_NO] = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn01Step;
							break;


		/////////////////////////////////////////////////////////////
		// 대기 /////////////////////////////////////////////////////
		case	STEP_WORK_STANDBY	:
										PROCESS.nCurrentStep = 220;
										break;

		// 프로세스 대기
		case	220		:
							if (m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO] ||
								m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]) {

								m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;
								m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;

								PROCESS.nCurrentStep = 230;
							}

							break;
							
		// 모델 프로파일 로드
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

							SErrorMessage(TRUE, _T("[S%02d/%s] 모델 정보를 로드할 수 없습니다."),	nSTATION_NO, 
																									g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

							PROCESS.nCurrentStep = STEP_WORK_ERROR_SYSTEM;
							break;

		// 초기화
		case	280		:
							PROCESS.nCurrentStep	= STEP_WORK_INIT;
							PROCESS.nReturn01Step	= 290;
							break;

		// 완료
		case	290		:
							PROCESS.nCurrentStep = STEP_WORK_START;
							break;


		/////////////////////////////////////////////////////////////
		// 작업 /////////////////////////////////////////////////////
		case	STEP_WORK_START	:
									PROCESS.nCurrentStep = 410;
									break;

		// 준비
		case	410		:
							// 작업 정보 초기화
							PROCESS.nRetryCount			= 0;
							PROCESS.nCurrentWorkSheetNo	= m_stSystemStatus.nMainProcessWorkIndex[nSTATION_NO][nSTATION_SUB_NO];
							PROCESS.nUpdateWorkSheetNo	= m_stSystemStatus.nCurrentVisionWorkSheetUpdateNo;
							PROCESS.bOnRetryInspection	= FALSE;
							bResultProcess				= TRUE;

							// 작업 프로시저 데이터 설정
							pstWorkProcedureData = &m_pstTestProcedureData[m_stSystemStatus.nCurrentWorkProcedureNo];

							// 검사 시간 설정
							LTimerTimeOutProcess.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_VISION_01_TIME]);

							PROCESS.nCurrentStep = 450;
							break;

		// 작업 완료 체크
		case	450		:
							{
								BOOL	bIsStopProcess	= FALSE;

								// 작업 정지
								if (m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO])
									bIsStopProcess = TRUE;

								// 작업 완료
								if (PROCESS.nCurrentWorkSheetNo >= PROCESS.nNumWorkSheetItem) {

									bResultProcess = FALSE;

									PROCESS.nCurrentStep = 490;
									break;
								}

								PROCESS.nCurrentStep = bIsStopProcess ? 480 : 460;
							}

							break;

		// 1 행정 작업
		case	460		:
							PROCESS.nCurrentStep	= STEP_WORK_CYCLE;
							PROCESS.nReturn01Step	= 461;
							break;

		case	461		:
							PROCESS.nCurrentStep = 470;
							break;

		// 검사 모드 체크
		case	470		:
							// 연속 검사 모드이고, 불합격 판정일 경우 재검사
							if (m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO] && !bResultProcess && !LTimerTimeOutProcess.Verify()) {
							
								// 플래그 초기화
								bResultProcess				= TRUE;
								PROCESS.bOnRetryInspection	= TRUE;

								// 검사 간격 설정
								LTimerProceed.Start(pstWorkProcedureData->nValue[TPRD_DATA_VALUE_VISION_01_INTV]);

								PROCESS.nCurrentStep++;
								break;
							}

							// 불합격 판정 시 비전 검사 이미지 저장
							if (m_SystemConfig.UseSystemOption(SOPT_SAVE_VISION_IMAGE_NG) && !bResultProcess)
								SaveVisionImage(PROCESS.nCurrentWorkSheetNo, FALSE);

							// 현재 비전 검사 작업 시트 업데이트 번호 설정
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

		// 완료
		case	490		:
							PROCESS.nCurrentStep = STEP_WORK_DONE;
							break;


		/////////////////////////////////////////////////////////////
		// 완료 /////////////////////////////////////////////////////
		case	STEP_WORK_DONE	:
									PROCESS.nCurrentStep = 590;
									break;

		// 완료
		case	590		:
							// 메인 프로세스 완료
							m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;
							m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;
							m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]	= bResultProcess;

							PROCESS.nCurrentStep = STEP_WORK_STANDBY;
							break;


		/////////////////////////////////////////////////////////////
		// 1 행정 작업 //////////////////////////////////////////////
		case	STEP_WORK_CYCLE	:
									PROCESS.nCurrentStep = 1010;
									break;

		case	1010	:
							// 도어 열림 체크
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							// 1 행정 플래그 설정
							PROCESS.bOnProcessCycle = TRUE;

							// 플래그 초기화
							PROCESS.nRetryCount			= 0;
							PROCESS.nResultInspection	= T_RESULT_SUCCESS;
														
							PROCESS.nCurrentStep = 1100;
							break;

		// 검사 조건별 분기
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

									// 업데이트 UI
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

		// 완료
		case	1900	:
							// 프로세스 결과 설정
							bResultProcess &= PROCESS.nResultInspection == T_RESULT_SUCCESS ? TRUE : FALSE;

							// 작업 상태 정보 설정
							(PROCESS.pstWorkStatus)->stMeasSheet[PROCESS.nCurrentWorkSheetNo].nResult = PROCESS.nResultInspection;
							MessageWindow(cDEBUG, _T("VISION_%02d = %d"), PROCESS.nCurrentWorkSheetNo, PROCESS.nResultInspection);

							// 업데이트 UI
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
							// 1 행정 플래그 해제
							PROCESS.bOnProcessCycle = FALSE;

							PROCESS.nCurrentStep = PROCESS.nReturn01Step;
							break;


		/////////////////////////////////////////////////////////////
		// 서브 스텝 : 검사 항목 - 비전 검사 ////////////////////////
		case	STEP_WORK_SUB_TSI_VISION	:
												PROCESS.nCurrentStep = 2010;
												break;

		// 초기화
		case	2010	:
							// 업데이트 UI
							PROCESS.bOnUpdateUI						= TRUE;
							PROCESS.stParamUI.nUpdateID				= UI_VISION_SHEET;
							PROCESS.stParamUI.nStationNo			= nSTATION_NO;
							PROCESS.stParamUI.stWorkSheet.bOnClear	= TRUE;

							// 비전 원점 정보 초기화
							ZeroMemory(&m_stSystemStatus.stVisionOriginOffset, sizeof(DPS_POINT2D_T));

							// 비전 이미지 윈도우 초기화
							if (m_pMainWnd)	{
								
								m_stSystemStatus.bIsVisionImageWindowCleared = FALSE;
								m_pMainWnd->PostMessage(UM_VISION_CLEAR_IMAGE);
							}

							// 플래그 초기화
							PROCESS.bOnRetryInspection	= FALSE;
							bOnOriginDetectFailure		= FALSE;
							bOnSaveVisionImage			= TRUE;
							nCurrentVisionCH			= VISION_CH1;
							m_stSystemStatus.nCurrentVisionInspectionNo = 0;

							PROCESS.nCurrentStep = m_SystemConfig.IsSimulationMode() ? 2050 : 2020;
							break;

		// 검사 준비
		case	2020	:
							// 카메라 노출 설정
							if (!m_SystemConfig.IsSimulationMode()) {

								UINT	nValueExposure	= PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].nValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_CAMERA_SPEED];

								SetVisionCameraExposure(nCurrentVisionCH, nValueExposure);
								MessageWindow(cDEBUG, _T("SET EXPOSURE = %d"), nValueExposure);
								
								nRcvdPacketIndex[nCurrentVisionCH]	= 0;
								bReceiveData[nCurrentVisionCH]		= FALSE;
								LTimerTimeOut.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_TOUT_VISION_CAMERA));								
							}

							// 보간 이동 모드
							if (pstWorkProcedureData->nValue[TPRD_DATA_VALUE_VISION_01_MOVE_MODE]) {
							
								PROCESS.nCurrentStep = 2030;
								break;
							}

							PROCESS.nCurrentStep++;
							break;

		case	2021	:
							// 도어 열림 체크
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							// VZ 대기 위치 이동
							if (Motion_Done(MOTION_RVZ)) {

								Motion_MoveTo(MOTION_RVZ, m_stMotionAxisInfo[MOTION_RVZ].dblCustomPosition[MAI_CPOS_HOME], m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}											

							break;

		case	2022	:
							// 작업 위치 이동 확인
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
							// 도어 열림 체크
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							// VX, VY 작업 위치 이동
							if (Motion_Done(MOTION_RVX) && Motion_Done(MOTION_RVY)) {

								Motion_Move2X(0, MOTION_RVX, MOTION_RVY,
											  PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_POSITION_1],
											  PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_POSITION_2],
											  m_stMotionAxisInfo[MOTION_RVX].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}											

							break;

		case	2024	:
							// 작업 위치 이동 확인
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
							// 도어 열림 체크
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							// VZ 작업 위치 이동
							if (Motion_Done(MOTION_RVZ)) {

								DOUBLE	dblPosition	= PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_MAX + TSI1_VALUE_01_POSITION_3];

								Motion_MoveTo(MOTION_RVZ, dblPosition, m_stMotionAxisInfo[MOTION_RVZ].dblSpeedBase);

								PROCESS.nCurrentStep++;
							}											

							break;

		case	2026	:
							// 작업 위치 이동 확인
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
							// 도어 열림 체크
							PROCESS.bOnDoorOpened = !GetDIStatus(DI_SIG_DOOR_OPENED_1) | !GetDIStatus(DI_SIG_DOOR_OPENED_2);
							if (m_stSystemStatus.bOnDoorOpened && PROCESS.bOnDoorOpened)
								break;

							// VX, VY, VZ 작업 위치 보간 이동
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
							// 작업 위치 이동 확인
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

		// 준비 완료 체크
		case	2040	:
							// 비전 카메라 설정 확인
							if (m_SystemConfig.IsSimulationMode() || bReceiveData[nCurrentVisionCH]) {
							
								PROCESS.nCurrentStep = 2050;
								break;
							}

							// 타임 아웃
							if (LTimerTimeOut.Verify()) {
							
								PROCESS.nCurrentStep = STEP_WORK_ERROR_DEVICE;
							}

							break;

		// 비전 프로시저 로드
		case	2050	:
							{
								if (!LoadVisionProcedure(PROCESS.nCurrentWorkSheetNo)) {
								
									ErrorMessage(TRUE, _T("비전 검사 프로시저 [%d]를 불러올 수 없습니다."), PROCESS.nCurrentWorkSheetNo);
									PROCESS.nCurrentStep = STEP_WORK_ERROR_SYSTEM;
									break;
								}

								PROCESS.nCurrentStep = 2060;
							}

							break;

		// 검사 지연 설정
		case	2060	:
							LTimerSteady.Start(PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].nValue[TSI_VALUE_COMMON_DELAY]);

							PROCESS.nCurrentStep++;
							break;

		case	2061	:
							if (LTimerSteady.Verify())
								PROCESS.nCurrentStep = 2100;

							break;

		// 카메라 영상 캡쳐
		case	2100	:
							// 도어 열림 체크
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

										SErrorMessage(TRUE, _T("비전 카메라 [%d] 이미지를 가져올 수 없습니다."), nCurrentVisionCH + 1);

										PROCESS.nResultInspection = T_RESULT_ERROR;
										PROCESS.nCurrentStep = 2190;
										break;
									}

									// 비전 검사 이미지 저장
									if (bOnSaveVisionImage) {

										if (m_SystemConfig.UseSystemOption(SOPT_SAVE_VISION_IMAGE))			SaveVisionImage(PROCESS.nCurrentWorkSheetNo, FALSE);
										if (m_SystemConfig.UseSystemOption(SOPT_SAVE_VISION_IMAGE_JPEG))	SaveVisionImage(PROCESS.nCurrentWorkSheetNo, FALSE, TRUE);

										// 마지막 이미지 상시 저장
										SaveVisionImage(PROCESS.nCurrentWorkSheetNo, FALSE, FALSE, TRUE);
									}
								}

								PROCESS.nCurrentStep++;
							}

							break;

		case	2101	:
							// 이미지 윈도우에 로딩
							if (m_pMainWnd)	m_pMainWnd->SendMessage(UM_VISION_LOAD_IMAGE, nCurrentVisionCH, (LPARAM)m_MilImageInspection[PROCESS.nCurrentWorkSheetNo]);

							// 비전 캡쳐 완료 플래그 설정
							m_stSystemStatus.bIsVisionCaptureComplete[nCurrentVisionCH] = TRUE;

							PROCESS.nCurrentStep = 2110;
							break;

		// 비전 검사 시작
		case	2110	:
							{
								VISION_TEST_DATA_T stVisionTestData;

								if (m_pstVisionProcedureData[m_stSystemStatus.nCurrentVisionInspectionNo].bUsePoint) {
							
									if (!PROCESS.bOnRetryInspection) {

										PROCESS.nCurrentStep++;
										break;
								
									} else {

										// 합격 포인트가 아니면 검사 진행
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
							
		// 검사 항목 변경
		case	2120	:
							if (++m_stSystemStatus.nCurrentVisionInspectionNo >= m_stVisionProcedureHeader.nNumProcedureData) {

								// 비전 이미지 윈도우 업데이트
								if (m_pMilImageWnd)	m_pMilImageWnd->SendMessage(UM_DPS_MIL_WND_IMAGE_UPDATE_WINDOW);
							
								PROCESS.nCurrentStep = 2130;
								break;
							}

							// 원점 검출 실패 시
							if (bOnOriginDetectFailure) {
							
								PROCESS.nCurrentStep = 2130;
								break;
							}

							PROCESS.nCurrentStep = 2110;
							break;

		// 불합격 판정 시 재검사
		case	2130	:
							if (m_SystemConfig.UseSystemOption(SOPT_RETRY_WORK_NG) && !PROCESS.bOnManualControlMode) {

								if (PROCESS.nResultInspection != T_RESULT_SUCCESS) {

									// 플래그 설정
									PROCESS.bOnRetryInspection	= TRUE;
									bOnSaveVisionImage			= bOnOriginDetectFailure;
									bOnOriginDetectFailure		= FALSE;
									m_stSystemStatus.nCurrentVisionInspectionNo	= 0;

									// 재시도 카운트 체크
									if (++PROCESS.nRetryCount >= m_SystemConfig.GetWorkRetryCount()) {

										PROCESS.nCurrentStep = 2180;
										break;
									}

									// 플래그 초기화
									PROCESS.nResultInspection = T_RESULT_SUCCESS;

									// 업데이트
									PROCESS.bOnUpdateUI						= TRUE;
									PROCESS.stParamUI.nUpdateID				= UI_VISION_SHEET;
									PROCESS.stParamUI.nStationNo			= nSTATION_NO;
									PROCESS.stParamUI.stWorkSheet.bOnClear	= TRUE;

									// 비전 이미지 캡쳐 안정화 시간
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

		// 완료
		case	2190	:
							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// 서브 스텝 : 비전 검사 ////////////////////////////////////
		case	STEP_WORK_SUB_TSI_VISION_EX	:
												PROCESS.nCurrentStep = 3010;
												break;

		// 준비 작업
		case	3010	:
							// 플래그 초기화
							nResultVision		= T_RESULT_SUCCESS;
							nRetryOriginDetect	= 0;
							ZeroMemory(&stRectInspection, sizeof(DMW_USER_RECT_T));

							// 프로시저 데이터 설정
							pstVisionProcedureData = &m_pstVisionProcedureData[m_stSystemStatus.nCurrentVisionInspectionNo];

							PROCESS.nCurrentStep = 3100;
							break;

		// 검사 모드 : THRESHOLD
		case	3100	:
							if (pstVisionProcedureData->nInspectionMode == VI_MODE_THRESHOLD) {
							
								if (pstVisionProcedureData->nNumberOfVisionRegion) {

									// 파라미터 설정
									ZeroMemory(&stParamThreshold, sizeof(VI_PARAM_THRESHOLD_T));
									stParamThreshold.MilImageInspection		= m_MilImageInspection[PROCESS.nCurrentWorkSheetNo];
									stParamThreshold.rectInspectionArea		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo;
									stParamThreshold.stInspectionInfo		= pstVisionProcedureData->stInspection_Threshold;
									stParamThreshold.bUseReverseJudgement	= pstVisionProcedureData->bOptions[VOPT_REVERSE_JUDGEMENT];

									// 이미지 프로세스 실행
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

		// 검사 모드 : 길이 측정 (THRESHOLD)
		case	3110	:
							if (pstVisionProcedureData->nInspectionMode == VI_MODE_THRESHOLD_LENGTH) {
							
								if (pstVisionProcedureData->nNumberOfVisionRegion) {

									// 파라미터 설정
									ZeroMemory(&stParamThresholdLength, sizeof(VI_PARAM_THRESHOLD_LENGTH_T));
									stParamThresholdLength.MilImageInspection				= m_MilImageInspection[PROCESS.nCurrentWorkSheetNo];
									stParamThresholdLength.rectInspectionArea[VI_THL_P1]	= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo;
									stParamThresholdLength.rectInspectionArea[VI_THL_P2]	= pstVisionProcedureData->stVisionRegionInfo[1].stRegionInfo;
									stParamThresholdLength.stInspectionInfo					= pstVisionProcedureData->stInspection_ThresholdLength;
									stParamThresholdLength.dblGainLength					= m_SystemConfig.GetVisionLengthGain(nCurrentVisionCH);
									stParamThresholdLength.bUseReverseJudgement				= pstVisionProcedureData->bOptions[VOPT_REVERSE_JUDGEMENT];

									// 이미지 프로세스 실행
									ProcessImage_ThresholdLength(	PROCESS.nCurrentWorkSheetNo, 
																	nSTATION_NO, 
																	m_stSystemStatus.stVisionOriginOffset,
																	stParamThresholdLength, 
																	stResultThresholdLength);

									nResultVision = stResultThresholdLength.nResultInspection;

									// 원점 검출 포인트
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

											// 디버그 메세지
											MessageWindow(cDEBUG, _T("[P:%02d] 원점 검출 = x%.2f, y%.2f, a%.2f"),	m_stSystemStatus.nCurrentVisionInspectionNo + 1,
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

		// 검사 모드 : 패턴 매칭
		case	3120	:
							if (pstVisionProcedureData->nInspectionMode == VI_MODE_PATTERN) {

								if (pstVisionProcedureData->nNumberOfVisionRegion) {

									// 파라미터 설정
									ZeroMemory(&stParamPatternMatch, sizeof(VI_PARAM_PATTERN_T));
									stParamPatternMatch.MilImageInspection		= m_MilImageInspection[PROCESS.nCurrentWorkSheetNo];
									stParamPatternMatch.rectInspectionArea		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo;
									stParamPatternMatch.stInspectionInfo		= pstVisionProcedureData->stInspection_PatternMatch;
									stParamPatternMatch.bUseReverseJudgement	= pstVisionProcedureData->bOptions[VOPT_REVERSE_JUDGEMENT];
									_stprintf_s(stParamPatternMatch.szFileOriginImage, MAX_STRFILE_M, _T("%s"), m_stVisionProcedureHeader.szFileOriginImage);

									// 이미지 프로세스 실행
									ProcessImage_PatternMatch(	PROCESS.nCurrentWorkSheetNo, 
																nSTATION_NO, 
																m_stSystemStatus.stVisionOriginOffset,
																stParamPatternMatch, 
																stResultPatternMatch);

									nResultVision = stResultPatternMatch.nResultInspection;

									// 원점 검출 포인트
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

											// 디버그 메세지
											MessageWindow(cDEBUG, _T("[P:%02d] 원점 검출 = x%.2f, y%.2f, a%.2f"),	m_stSystemStatus.nCurrentVisionInspectionNo + 1,
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

		// 검사 모드 : 모델 검색
		case	3130	:
							if (pstVisionProcedureData->nInspectionMode == VI_MODE_MODEL_FINDER) {

								if (pstVisionProcedureData->nNumberOfVisionRegion) {

									// 검사 영역 설정
									if (!pstVisionProcedureData->bOptions[VOPT_ORIGIN_POINT] ||
										(pstVisionProcedureData->bOptions[VOPT_ORIGIN_POINT] && !nRetryOriginDetect)) {

										stOriginDetectArea  = pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo;
										stOriginDetectModel = pstVisionProcedureData->stInspection_ModelFind;
									}

									// 파라미터 설정
									ZeroMemory(&stParamModelFind, sizeof(VI_PARAM_MODEL_T));
									stParamModelFind.MilImageInspection			= m_MilImageInspection[PROCESS.nCurrentWorkSheetNo];
									stParamModelFind.rectInspectionArea			= stOriginDetectArea;
									stParamModelFind.stInspectionInfo			= stOriginDetectModel;
									stParamModelFind.stThresholdInfo			= pstVisionProcedureData->stInspection_Threshold;
									stParamModelFind.bUseReverseJudgement		= pstVisionProcedureData->bOptions[VOPT_REVERSE_JUDGEMENT];
									stParamModelFind.bUseRecursiveMeasurement	= pstVisionProcedureData->bOptions[VOPT_RECURSIVE_MEASUREMENT];
									_stprintf_s(stParamModelFind.szFileOriginImage, MAX_STRFILE_M, _T("%s"), m_stVisionProcedureHeader.szFileOriginImage);

									// 이미지 프로세스 실행
									ProcessImage_ModelFind(	PROCESS.nCurrentWorkSheetNo, 
															nSTATION_NO, 
															m_stSystemStatus.stVisionOriginOffset,
															stParamModelFind, 
															stResultModelFind);

									nResultVision = stResultModelFind.nResultInspection;

									// 원점 검출 포인트
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

											// 디버그 메세지
											MessageWindow(cDEBUG, _T("[P:%02d] 원점 검출 = x%.2f, y%.2f, a%.2f"),	m_stSystemStatus.nCurrentVisionInspectionNo + 1,
																													m_stSystemStatus.stVisionOriginOffset.dblX,
																													m_stSystemStatus.stVisionOriginOffset.dblY,
																													m_stSystemStatus.stVisionOriginOffset.dblAngle);
									
										} else {

											if (++nRetryOriginDetect <= MAX_VISION_ORIGIN_RETRY) {

												switch (nRetryOriginDetect) {
											
													case	1	:
																	// 검출 영역을 X방향으로 (-) 이동
																	stOriginDetectArea.ptTopLeft.x		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.x - VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.x	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.x - VISION_ORIGIN_OFFSET;
																	break;

													case	2	:
																	// 검출 영역을 X방향으로 (+) 이동
																	stOriginDetectArea.ptTopLeft.x		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.x + VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.x	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.x + VISION_ORIGIN_OFFSET;
																	break;

													case	3	:
																	// 검출 영역을 Y방향으로 (-) 이동
																	stOriginDetectArea.ptTopLeft.x		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.x;
																	stOriginDetectArea.ptTopLeft.y		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.y - VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.x	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.x;
																	stOriginDetectModel.flOffset_M.y	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.y - VISION_ORIGIN_OFFSET;
																	break;

													case	4	:
																	// 검출 영역을 Y방향으로 (+) 이동
																	stOriginDetectArea.ptTopLeft.x		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.x;
																	stOriginDetectArea.ptTopLeft.y		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.y + VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.x	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.x;
																	stOriginDetectModel.flOffset_M.y	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.y + VISION_ORIGIN_OFFSET;
																	break;

													case	5	:
																	// 검출 영역을 X방향으로 (-), Y방향으로 (-) 이동
																	stOriginDetectArea.ptTopLeft.x		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.x - VISION_ORIGIN_OFFSET;
																	stOriginDetectArea.ptTopLeft.y		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.y - VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.x	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.x - VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.y	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.y - VISION_ORIGIN_OFFSET;
																	break;

													case	6	:
																	// 검출 영역을 X방향으로 (-), Y방향으로 (+) 이동
																	stOriginDetectArea.ptTopLeft.x		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.x - VISION_ORIGIN_OFFSET;
																	stOriginDetectArea.ptTopLeft.y		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.y + VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.x	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.x - VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.y	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.y + VISION_ORIGIN_OFFSET;
																	break;

													case	7	:
																	// 검출 영역을 X방향으로 (+), Y방향으로 (-) 이동
																	stOriginDetectArea.ptTopLeft.x		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.x + VISION_ORIGIN_OFFSET;
																	stOriginDetectArea.ptTopLeft.y		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.y - VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.x	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.x + VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.y	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.y - VISION_ORIGIN_OFFSET;
																	break;

													case	8	:
																	// 검출 영역을 X방향으로 (+), Y방향으로 (+) 이동
																	stOriginDetectArea.ptTopLeft.x		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.x + VISION_ORIGIN_OFFSET;
																	stOriginDetectArea.ptTopLeft.y		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo.ptTopLeft.y + VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.x	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.x + VISION_ORIGIN_OFFSET;
																	stOriginDetectModel.flOffset_M.y	= pstVisionProcedureData->stInspection_ModelFind.flOffset_M.y + VISION_ORIGIN_OFFSET;
																	break;
												}

												// 메세지 출력
												ErrorMessage(TRUE, _T("[P:%02d] 비전 원점 검출을 재시도합니다. (%d)"), m_stSystemStatus.nCurrentVisionInspectionNo + 1, nRetryOriginDetect);
												break;
											}

											// 원점 검출 실패
											bOnOriginDetectFailure = TRUE;
										}
									}
								}

								PROCESS.nCurrentStep = 3180;
								break;
							}

							PROCESS.nCurrentStep = 3140;
							break;

		// 검사 모드 : 컬러 분석
		case	3140	:
							if (pstVisionProcedureData->nInspectionMode == VI_MODE_COLOR_ANALYSIS) {

								if (pstVisionProcedureData->nNumberOfVisionRegion) {

									// 파라미터 설정
									ZeroMemory(&stParamColorAnalysis, sizeof(VI_PARAM_COLOR_T));
									stParamColorAnalysis.MilImageInspection		= m_MilImageInspection[PROCESS.nCurrentWorkSheetNo];
									stParamColorAnalysis.rectInspectionArea		= pstVisionProcedureData->stVisionRegionInfo[0].stRegionInfo;
									stParamColorAnalysis.stInspectionInfo		= pstVisionProcedureData->stInspection_ColorAnalysis;
									stParamColorAnalysis.bUseReverseJudgement	= pstVisionProcedureData->bOptions[VOPT_REVERSE_JUDGEMENT];

									// 이미지 프로세스 실행
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

		// 검사 모드 : 없음
		case	3170	:
							SErrorMessage(TRUE, _T("[P:%02d] 비전 검출 모드가 정의되어 있지 않습니다."), m_stSystemStatus.nCurrentVisionInspectionNo + 1);

							nResultVision			= T_RESULT_ERROR;
							PROCESS.nCurrentStep	= 3200;
							break;

		// 검사 영역 표시
		case	3180	:
							if (m_pMilImageWnd) {

								// 불량이거나 양품 표시 옵션을 사용할 경우
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

		// 검사 결과 설정
		case	3200	:
							{
								DOUBLE				dblGain			= PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_GAIN];
								DOUBLE				dblOffset		= PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_OFFSET];
								DOUBLE				dblJudgement	= PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_JUDGE];
								DOUBLE				dblSpecMIN		= PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_SPEC_L];
								DOUBLE				dblSpecMAX		= PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].dblValue[TSI_VALUE_COMMON_SPEC_H];

								CString				strParameters	= _T("");
								VISION_TEST_DATA_T	stVisionTestData;


								// 검사 항목 결과 설정
								if (PROCESS.nResultInspection == T_RESULT_SUCCESS)
									PROCESS.nResultInspection = nResultVision;

								// 불량 그룹 설정
								if (nResultVision != T_RESULT_SUCCESS) {

									//(PROCESS.pstWorkStatus)->nGroupNG = pstVisionProcedureData->nGroupNG;
									//MessageWindow(cDEBUG, _T("[T%d%d] NG-GROUP = %d"), nSTATION_NO + 1, nSTATION_SUB_NO + 1, (PROCESS.pstWorkStatus)->nGroupNG);
								}
								
								// 검사 파라미터 설정
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

																			// 판정값 체크
																			if (dblJudgement != 0.0)
																				PROCESS.dblValueMeasurement = dblJudgement - PROCESS.dblValueMeasurement;

																			// 검사 결과 판정
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

								// 검사 결과 저장
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

								// 업데이트
								PROCESS.bOnUpdateUI					= TRUE;
								PROCESS.stParamUI.nUpdateID			= UI_VISION_SHEET;
								PROCESS.stParamUI.nStationNo		= nSTATION_NO;
								PROCESS.stParamUI.stWorkSheet.nTestItem				= PROCESS.pstTestSetupInfo[PROCESS.nCurrentWorkSheetNo].nTestSheetItem;
								PROCESS.stParamUI.stWorkSheet.nWorkPosition			= PROCESS.nCurrentWorkSheetNo;
								PROCESS.stParamUI.stWorkSheet.nWorkStatus			= WORK_STATE_COMPLETE;
								PROCESS.stParamUI.stWorkSheet.nIndexVisionTestData	= m_stSystemStatus.nCurrentVisionInspectionNo;

								// 비전 시트 저장
								SaveVisionSheet(PROCESS.nCurrentWorkSheetNo, 
												m_stSystemStatus.nCurrentVisionInspectionNo,
												stVisionTestData,
												PROCESS.nRetryCount);
							}

							PROCESS.nCurrentStep = 3300;
							break;

		// 완료
		case	3300	:
							PROCESS.nCurrentStep = PROCESS.nReturn03Step;
							break;


		/////////////////////////////////////////////////////////////
		// 오류 /////////////////////////////////////////////////////
		case	STEP_WORK_ERROR	:
									PROCESS.bOnOperatingStop = TRUE;
									break;

		case	STEP_WORK_ERROR_PARTS	:
											PROCESS.bOnError				= TRUE;
											PROCESS.nRecoveryStep			= STEP_WORK_ERROR;
											PROCESS.stErrorCode.nErrorCode	= ERROR_MACHINE_SEQUENCE;
											PROCESS.stErrorCode.nProcessID	= PROCESS_MAIN_WORK_VISION;
											PROCESS.stErrorCode.nStationNo	= nSTATION_NO;

											// 디버그 메세지
											SDebugMessage(TRUE, _T("[P%d:%d] ERROR PARTS"), nSTATION_NO, nSTATION_SUB_NO + 1);
											break;

		case	STEP_WORK_ERROR_SYSTEM	:
											// 디버그 메세지
											SDebugMessage(TRUE, _T("[P%d:%d] ERROR SYSTEM"), nSTATION_NO, nSTATION_SUB_NO + 1);
											break;	

		case	STEP_WORK_ERROR_DEVICE	:
											// 디버그 메세지
											SDebugMessage(TRUE, _T("[P%d:%d] ERROR DEVICE"), nSTATION_NO, nSTATION_SUB_NO + 1);

											// 메세지 출력
											ErrorMessage(TRUE, _T("[P%d] NO RESPONSE CAMERA"), nSTATION_NO);

											// 프로세스 플래그 초기화
											m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]				= FALSE;
											m_stSystemStatus.bOnMainProcessStop[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
											m_stSystemStatus.bOnMainProcessOnce[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
											m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO]			= FALSE;
											m_stSystemStatus.bIsMainProcessInitialized[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;

											PROCESS.nCurrentStep = STEP_WORK_STANDBY;
											break;	


		/////////////////////////////////////////////////////////////
		// 일시 정지 스텝 ///////////////////////////////////////////
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

		// 스텝 복구
		case	20100	:
							PROCESS.nCurrentStep	= PROCESS.nRecoveryStep;
							PROCESS.bOnPause		= FALSE;
							break;


		/////////////////////////////////////////////////////////////
		// 비상 정지 스텝 ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop)	{

									PROCESS.nRecoveryStep	= 0;
									PROCESS.nCurrentStep	= STEP_PAUSE;
								}

								break;


		/////////////////////////////////////////////////////////////
		// 장비 초기화 스텝 /////////////////////////////////////////
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
	// 데이터 수신 //////////////////////////////////////////////////
	for (UINT nVisionCH = 0; nVisionCH < MAX_VISION_CHANNEL; nVisionCH++) {

		while (m_Comm[COMM_DEV_CAM + nVisionCH].ReadByte(&byReadByte)) {

			// 데이터 저장
			szRcvdPacket[nVisionCH][nRcvdPacketIndex[nVisionCH]++] = byReadByte;

			// 하나의 패킷이 완성되면 해석
			if (byReadByte == COMM_ETX_F) {

				USES_CONVERSION;
				szRcvdPacket[nVisionCH][nRcvdPacketIndex[nVisionCH] - 1] = '\0';
				MessageWindow(cDEBUG, _T("[CAM%d->] %s"), nVisionCH + 1, A2W(szRcvdPacket[nVisionCH]));
				
				// 상태 체크
				if (strncmp(szRcvdPacket[nVisionCH], "OK", 2))	
					bReceiveData[nVisionCH] = TRUE;

				// 패킷 초기화
				nRcvdPacketIndex[nVisionCH] = 0;
			}

			// 패킷 오버플로우 방지
			if (nRcvdPacketIndex[nVisionCH] >= COMM_PACKET_SIZE) {

				nRcvdPacketIndex[nVisionCH] = 0;
				break;
			}
		}
	}


	/////////////////////////////////////////////////////////////////
	// 운전 정지 체크 ///////////////////////////////////////////////
	CheckProcessOperatingStop(PROCESS);


	/////////////////////////////////////////////////////////////////
	// 일반 /////////////////////////////////////////////////////////
	PROCESS.bIsUpdateSendMessage = TRUE;
	CheckProcessGeneral(nSTATION_NO, PROCESS);


	/////////////////////////////////////////////////////////////////
	// 스텝 모니터링 ////////////////////////////////////////////////
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
// 프로세스 : 공통 ////////////////////////////////////////////////////////////
PERROR_CODE_T CMainApp::ProcessCommon(void)
{
	return	NULL;
}


///////////////////////////////////////////////////////////////////////////////
// 프로세스 : 공정 #01 - 검사 공정 (OS) ///////////////////////////////////////
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
	// 프로세스 데이터 초기화 ///////////////////////////////////////
	ProcessDataInitialize(PROCESS);


	/////////////////////////////////////////////////////////////////
	// 자동 운전 시작/정지 초기화 ///////////////////////////////////
	CheckProcessOperating(PROCESS);


	/////////////////////////////////////////////////////////////////
	// 장비 초기화 //////////////////////////////////////////////////
	if (CheckProcessMachineInitialize(PROCESS))
		return	NULL;


	/////////////////////////////////////////////////////////////////
	// 작업 정지 예약 ///////////////////////////////////////////////
	if (CheckProcessOperatingStopReservated(nSTATION_NO, nSTATION_SUB_NO, PROCESS))
		return	NULL;


	/////////////////////////////////////////////////////////////////
	// 수동 제어 모드 ///////////////////////////////////////////////
	if (CheckProcessManualControlMode(nSTATION_NO, PROCESS))
		return	NULL;
	

	/////////////////////////////////////////////////////////////////
	// 비상/일시 정지 상태 //////////////////////////////////////////
	if (CheckProcessEmergencyStop(PROCESS))					return	NULL;
	if (CheckProcessOperatingPause(nSTATION_NO, PROCESS))	return	NULL;


	/////////////////////////////////////////////////////////////////
	// 스텝 프로세스 ////////////////////////////////////////////////
	switch (PROCESS.nCurrentStep) {

		case	0		:
							PROCESS.nCurrentStep = 10;
							break;

		// 시스템 체크
		case	10		:
							if (IsSystemReady()) {
							
								PROCESS.nCurrentStep = 20;
							}
								
							break;

		// 플래그 초기화
		case	20		:
							// 공정 프로세스 데이터 초기화
							StationProcessDataInitialize(nSTATION_NO, nSTATION_SUB_NO, PROCESS);

							PROCESS.nCurrentStep = 30;
							break;

		// 유닛 초기화
		case	30		:
							// 바코드 스캐너 트리거 해제
							SetTrigBarcode(nBCS_INPUT_M, FALSE);
							SetTrigBarcode(nBCS_INPUT_A, FALSE);

							PROCESS.nCurrentStep = 40;
							break;

		// 공정 상태 설정
		case	40		:
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_NONE;

							PROCESS.nCurrentStep = 50;
							break;

		// 자동 운전 체크
		case	50		:
							if (m_stSystemStatus.bOnOperating) {

								PROCESS.nCurrentStep = 60;
							}

							break;

		// 모델 프로파일 로드
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

							SErrorMessage(TRUE, _T("[S%02d/%s] 모델 정보를 로드할 수 없습니다."),	nSTATION_NO, 
																									g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

							PROCESS.nCurrentStep = STEP_STN_ERROR_SYSTEM;
							break;

		// 완료
		case	90		:
							PROCESS.nCurrentStep	= STEP_STN_INIT;
							PROCESS.nReturn01Step	= STEP_STN_STANDBY;
							break;


		/////////////////////////////////////////////////////////////
		// 초기화 ///////////////////////////////////////////////////
		case	STEP_STN_INIT	:
									PROCESS.nCurrentStep = 110;
									break;

		// 플래그 초기화
		case	110		:
							m_stSystemStatus.bOnStationInitializeResult[nSTATION_NO][nSTATION_SUB_NO]	= TRUE;
							m_stSystemStatus.bIsStationProcessLock[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;

							PROCESS.nCurrentStep = 120;
							break;

		// 공정 상태 설정
		case	120		:
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_NONE;

							// 업데이트 UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_STATUS_STATION;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;

							PROCESS.nCurrentStep = 130;
							break;

		// 유닛 초기화
		case	130		:
							// 연결 릴레이 초기화
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
							
							// 바코드 스캐너 트리거 해제
							SetTrigBarcode(nBCS_INPUT_M, FALSE);
							SetTrigBarcode(nBCS_INPUT_A, FALSE);

							PROCESS.nCurrentStep = 140;
							break;

		// 작업 대기 위치 이동
		case	140		:
							if (!PROCESS.bOnMachineInitialize) {

								PROCESS.nCurrentStep	= STEP_STN_HOME;
								PROCESS.nReturn02Step	= 150;
								break;
							}

							PROCESS.nCurrentStep = 150;
							break;

		// 작업 유닛 초기화
		case	150		:
							if (!PROCESS.bOnMachineInitialize) {

								PROCESS.nCurrentStep	= STEP_STN_SUB_01;
								PROCESS.nReturn02Step	= 190;
								break;
							}

							PROCESS.nCurrentStep = 190;
							break;

		// 완료
		case	190		:
							// 초기화 완료 플래그 설정
							m_stSystemStatus.bOnStationInitializeComplete[nSTATION_NO][nSTATION_SUB_NO] = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn01Step;
							break;


		/////////////////////////////////////////////////////////////
		// 대기 위치 이동 ///////////////////////////////////////////
		case	STEP_STN_HOME	:
									PROCESS.nCurrentStep = 410;
									break;

		// 인터록 체크
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

		// VY 안전 위치 체크
		case	420		:
							if (!Motion_CheckSafePosition(MOTION_RVY, FALSE, TRUE)) {
							
								PROCESS.nCurrentStep++;
								break;
							}

							PROCESS.nCurrentStep = 450;
							break;

		case	421		:
							// 안전 위치 최대 위치로 저속 이동
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

		// VZ 대기 위치 이동
		case	450		:
							// 도어 열림 체크
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

		// VY 대기 위치 이동
		case	460		:
							// 도어 열림 체크
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

		// VX 대기 위치 이동
		case	470		:
							// 도어 열림 체크
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

		// 완료
		case	490		:
							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// 작업 유닛 초기화 /////////////////////////////////////////
		case	STEP_STN_SUB_01	:
									PROCESS.nCurrentStep = 8010;
									break;

		// 준비 작업
		case	8010	:
							PROCESS.nCurrentStep = 8020;
							break;

		// 프로브 가이드 : OFF
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

		// 프로브 : OFF
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

		// 도어 열림 유닛 : DN
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

		// 제품 감지 체크
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

		// 제품 도어 열림 체크
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

		// 로딩 유닛 : FWD
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

		// 완료
		case	8090	:
							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// 제품 도어 열림 체크 //////////////////////////////////////
		case	STEP_STN_SUB_02	:
									PROCESS.nCurrentStep = 8110;
									break;

		// 준비 작업
		case	8110	:
							// 플래그 초기화
							PROCESS.bOnInterLock = FALSE;

							PROCESS.nCurrentStep = 8120;
							break;

		// 로딩 유닛 : BWD
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

		// 도어 열림 유닛 : UP
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
							
								// 플래그 설정
								PROCESS.bOnInterLock = TRUE;

								PROCESS.nCurrentStep = 8140;
							}

							break;

		// 도어 열림 유닛 : DN
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

		// 로딩 유닛 : FWD
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

		// 완료
		case	8190	:
							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// 제품 도어 닫기 ///////////////////////////////////////////
		case	STEP_STN_SUB_03	:
									PROCESS.nCurrentStep = 8210;
									break;

		// 준비 작업
		case	8210	:
							PROCESS.nCurrentStep = 8220;
							break;

		// VZ 대기 위치 이동
		case	8220	:
							// 도어 열림 체크
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

		// VY 대기 위치 이동
		case	8230	:
							// 도어 열림 체크
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

		// VX, VZ 목표 위치 보간 이동 (도어 닫기 시작)
		case	8240	:
							// 도어 열림 체크
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

		// VY 목표 위치 이동 (도어 닫기 시작)
		case	8250	:
							// 도어 열림 체크
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
		
		// VX, VY, VZ 목표 위치 보간 이동 (도어 닫기 종료)
		case	8260	:
							// 도어 열림 체크
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

		// 완료
		case	8290	:
							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// 메세지 박스 출력 /////////////////////////////////////////
		case	STEP_STN_MESSAGE_BOX_01	:
											PROCESS.nCurrentStep = 9010;
											break;

		case	9010	:
							// 메세지 박스가 출력 상태 체크
							if (!m_stSystemStatus.bIsDisplayMessageBox) {
							
								m_stSystemStatus.bIsDisplayMessageBox = TRUE;

								PROCESS.nCurrentStep++;
							}

							break;

		case	9011	:
							// 시스템 플래그 설정
							m_stSystemStatus.bOnWaitForUser			= TRUE;				// 사용자 입력 대기 설정
							m_stSystemStatus.bOnBuzzer				= TRUE;				// 경고음 출력
							m_stSystemStatus.nMessageBoxButtonCode	= MBOX_BCODE_NONE;	// 버튼 코드 초기화

							// 메세지 박스 생성
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

							// 비프음 2회 출력
							m_stSystemStatus.nBeepCount = 2;

							SErrorMessage(TRUE, _T("[S%02d/%s] 메세지 박스를 생성할 수 없습니다."),	nSTATION_NO + 1, 
																									g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

							PROCESS.nCurrentStep = 9013;
							break;

		case	9012	:
							if (m_stSystemStatus.nMessageBoxButtonCode != MBOX_BCODE_NONE) {

								// 버튼 0 : 확인
								if (m_stSystemStatus.nMessageBoxButtonCode == MBOX_BCODE_0) {

									PROCESS.nCurrentStep++;
									break;
								} 

								// 버튼 1 : 경고음 해제
								if (m_stSystemStatus.nMessageBoxButtonCode == MBOX_BCODE_1) {

									m_stSystemStatus.bOnBuzzer				= FALSE;			// 경고음 해제
									m_stSystemStatus.nMessageBoxButtonCode	= MBOX_BCODE_NONE;	// 버튼 코드 초기화
								}
							}

							break;
								
		case	9013	:
							// 메세지 박스 출력 플래그 해제
							m_stSystemStatus.bIsDisplayMessageBox = FALSE;

							// 메세지 박스 감추기	
							m_pMessageBoxDlg->SendMessage(UM_DPS_DLG_MESSAGE_BOX_SHOWHIDE, SW_HIDE, NULL);

							// 시스템 플래그 설정
							m_stSystemStatus.bOnWaitForUser	= FALSE;	// 사용자 입력 대기 해제
							m_stSystemStatus.bOnBuzzer		= FALSE;	// 경고음 해제

							PROCESS.nCurrentStep = 9090;
							break;

		// 완료
		case	9090	:
							PROCESS.nCurrentStep = PROCESS.nReturn03Step;
							break;


		/////////////////////////////////////////////////////////////
		// 제품 코드 체크 ///////////////////////////////////////////
		case	STEP_STN_SCAN_CODE	:
										PROCESS.nCurrentStep = 6010;
										break;

		// 제품 코드 체크
		case	6010	:
							{
								CString		strProductCodeM		= GetBarcodeInfo(nBCS_INPUT_M);
								CString		strProductCodeA		= GetBarcodeInfo(nBCS_INPUT_A);
								CString		strProductCode		= _T("");
								BOOL		bOnErrorProduct		= FALSE;
								UINT		nCodeStatus			= BCD_SCAN_NONE;
								UINT		nCodeWorkNG			= WORK_NG_NONE;


								// 스캔 코드 설정
								strProductCode = strProductCodeM;
								if (strProductCode.IsEmpty())	strProductCode = strProductCodeA;

								// 마스터 제품 코드 체크
								PROCESS.bIsMasterProduct = FALSE;
								if (!strProductCode.IsEmpty()) {
								
									for (UINT nIndex = 0; nIndex < MAX_BCD_MASTER_CODE; nIndex++) {
									
										if (strProductCode.Compare(((PSP_WI_BASIC_SETUP_T)PROCESS.pstStationSetupInfo)->szMasterCode[nIndex]) == 0)
											PROCESS.bIsMasterProduct = TRUE;
									}

									if (PROCESS.bIsMasterProduct) {
									
										// 메세지 출력
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

								// 제품 코드 체크
								if (!PROCESS.bIsMasterProduct && (PROCESS.pstModelProfileConfig)->bWorkOption[WOPT_USE_SCAN_CODE]) {
								
									// 제품 코드 없음
									if (bOnCheckProductCodeEmpty && strProductCode.IsEmpty()) {
									
										// 메세지 출력
										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_INPUT].szDescription[m_nTypeLanguage]);

										if (m_nTypeLanguage != LANGUAGE_KOR) {

											ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																					g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																					g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_INPUT].szDescription[LANGUAGE_KOR]);
										}
	
										// 코드 상태 설정
										nCodeStatus		= BCD_SCAN_EMPTY;
										bOnErrorProduct	= TRUE;
									
									// 제품 코드 있음
									} else {

										CString		strInputFormat	= (PROCESS.pstWorkInfo)->szWorkInfoValue[WI_ITEM_BCD_INPUT_FORMAT];
									
										// 제품 코드 포맷 체크
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

										// 제품 코드 중복 체크
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

									// 제품 코드 오류
									if (bOnErrorProduct) {
									
										// 업데이트 UI
										PROCESS.bOnUpdateUI				= TRUE;
										PROCESS.stParamUI.nUpdateID		= UI_PRODUCT_CODE_IN;
										PROCESS.stParamUI.nStationNo	= nSTATION_NO;
										PROCESS.stParamUI.stProductCodeInfo.nStatusCodeInput = nCodeStatus;
										_tcscpy_s(PROCESS.stParamUI.stProductCodeInfo.szCodeInput, MAX_STRINPUT_L, strProductCode);

										// 비프음 출력
										m_stSystemStatus.nBeepCount = 2;

										// 플래그 설정
										bOnErrorProductCode = TRUE;

										PROCESS.nCurrentStep = 6090;
										break;
									}
								}

								if (!strProductCode.IsEmpty()) {
								
									// 현재 제품 코드 설정
									SetCurrentProductCode(nSTATION_NO, strProductCode);

									PROCESS.nCurrentStep = 6020;
									break;
								}

								PROCESS.nCurrentStep = 6090;
							}

							break;

		// 마스터 검사 체크
		case	6020	:
							if (!PROCESS.bIsMasterProduct && m_SystemConfig.UseSystemOption(SOPT_ENABLE_CHECK_MASTER_TEST)) {
		
								if (!CheckMasterTest()) {

									// 메세지 출력
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[SYSSTR_MC_WARN_MASTER_TEST].szDescription[m_nTypeLanguage]);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[SYSSTR_MC_WARN_MASTER_TEST].szDescription[LANGUAGE_KOR]);
									}
								
									// 비프음 출력
									m_stSystemStatus.nBeepCount = 2;

									// 현재 제품 코드 초기화
									ClearCurrentProductCode(nSTATION_NO);

									// 사용자 메세지 설정
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

								// 사용자 메세지 복원
								if (PROCESS.bOnSetUserMessage)	
									RestoreUserMessage();

								// 플래그 설정
								bOnErrorProductCode = TRUE;

								PROCESS.nCurrentStep = 6090;
							}

							break;

		// 완료
		case	6090	:
							PROCESS.nCurrentStep = PROCESS.nReturn03Step;
							break;


		/////////////////////////////////////////////////////////////
		// 대기 /////////////////////////////////////////////////////
		case	STEP_STN_STANDBY	:
										// 시작 옵션 대기
										if (m_stSystemStatus.bOnStationProcessStart)
											PROCESS.nCurrentStep = 210;

										break;

		// 공정 상태 설정
		case	210		:
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_STANDBY;

							// 업데이트 UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_STATUS_STATION;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;

							PROCESS.nCurrentStep = 220;
							break;

		// 준비 작업
		case	220		:
							// 사용자 메세지 설정
							SetUserMessage(UMSG_STANDBY);

							// 바코드 정보 초기화
							ClearBarcodeInfo(nBCS_INPUT_M);
							ClearBarcodeInfo(nBCS_INPUT_A);
							ClearCurrentProductCode(nSTATION_NO);

							PROCESS.nCurrentStep = 230;
							break;

		// 시작 버튼 입력 체크
		case	230		:
							if (!GetDIStatus(DI_BTN_S01_START))
								PROCESS.nCurrentStep++;
							
							break;

		case	231		:
							if (GetDIStatus(DI_BTN_S01_START)) {
							
								// 버튼 입력 지연
								LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_PUSH_BUTTON));

								PROCESS.nCurrentStep++;
								break;
							}

							// 시뮬래이션 모드
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

		// 라벨 발행 여부 체크
		case	235		:
								if (m_stSystemStatus.stPrintStatus[BCP_PRINT_1].bIsLabelWaiting) {

									// 메세지 출력
									if (m_nTypeLanguage == LANGUAGE_KOR)	ErrorMessage(TRUE, _T("[S%02d/%s] 라벨이 이미 발행되어 있습니다."),	nSTATION_NO, g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);
									else									ErrorMessage(TRUE, _T("[S%02d/%s] LABEL IS ALREADY ISSUED."),	nSTATION_NO, g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);
									
									// 비프음 출력
									m_stSystemStatus.nBeepCount = 2;

									PROCESS.nCurrentStep = 230;
									break;
								}

								PROCESS.nCurrentStep = 240;
								break;

		// 제품 감지 및 클램프, PIN S/W 체크
		case	240		:
							// 제품 및 PIN S/W 감지 체크
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

									// 메세지 출력
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[nSystemMessageID].szDescription[m_nTypeLanguage]);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[nSystemMessageID].szDescription[m_nTypeLanguage]);
									}

									// 비프음 출력
									m_stSystemStatus.nBeepCount = 2;

									PROCESS.nCurrentStep = 230;
								}

								break;
							}

							PROCESS.nCurrentStep = 240;
							break;

		case	245		:
							// 제품 클램프 체크
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

									// 메세지 출력
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CLAMP].szDescription[m_nTypeLanguage]);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CLAMP].szDescription[m_nTypeLanguage]);
									}

									// 비프음 출력
									m_stSystemStatus.nBeepCount = 2;

									PROCESS.nCurrentStep = 230;
								}

								break;
							}

							PROCESS.nCurrentStep = 245;
							break;

		// 오류 체크
		case	250		:
							{
								BOOL		bIsErrorState	= FALSE;
								UINT		nUserMessageID	= 0;
								CString		strErrorMessage	= _T("");


								// 초기화
								strMessage.Empty();

								// 프로브 카운터 체크
								if (!bIsErrorState) {

									bIsErrorState |= m_stSystemStatus.bIsFullProbeCounter[nSTATION_NO];

									if (bIsErrorState) {

										strMessage.AppendFormat(_T(" %s\n %s\n"), g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage], g_stSystemString[SYSSTR_MC_WARN_EXPIRE_PROBE].szDescription[m_nTypeLanguage]);
										strMessage.AppendFormat(_T(" %s"), g_stSystemString[SYSSTR_MC_WARN_EXPIRE_PROBE_COMMENT].szDescription[m_nTypeLanguage]);
										strErrorMessage		= g_stSystemString[SYSSTR_MC_WARN_EXPIRE_PROBE_COMMENT].szDescription[m_nTypeLanguage];
										nUserMessageID		= UMSG_WARN_PROBE_COUNT_EXPIRED;
									}
								}

								// 오류 처리
								if (bIsErrorState) {

									// 메세지 출력
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			strErrorMessage);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[SYSSTR_MC_WARN_EXPIRE_PROBE_COMMENT].szDescription[LANGUAGE_KOR]);
									}

									// 사용자 메세지 설정
									PROCESS.bOnSetUserMessage = SetUserMessage(nUserMessageID);

									PROCESS.nCurrentStep	= STEP_STN_MESSAGE_BOX_01;
									PROCESS.nReturn03Step	= 251;
									break;
								}

								PROCESS.nCurrentStep = 260;
							}

							break;

		case	251		:
							// 사용자 메세지 복원
							if (PROCESS.bOnSetUserMessage)	
								RestoreUserMessage();

							PROCESS.nCurrentStep--;
							break;

		// 제품 코드 체크 (수동 스캔)
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

		// 제품 도어 열림 체크
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
							
									// 메세지 출력
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[SYSSTR_MC_WARN_PRODUCT_DOOR_OPENED].szDescription[m_nTypeLanguage]);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[SYSSTR_MC_WARN_PRODUCT_DOOR_OPENED].szDescription[m_nTypeLanguage]);
									}

									// 비프음 출력
									m_stSystemStatus.nBeepCount = 2;

									// 타이머 설정
									LTimerProceed.Start(m_SystemConfig.GetDelaySystem(DLY_SYS_INTV_USER_WARNING_MESSAGE));
								}

								break;
							}

							PROCESS.nCurrentStep = 270;
							break;

		// 제품 도어 상태 불량
		case	280		:
							// 메세지 출력
							ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																	g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																	g_stSystemString[SYSSTR_MC_WARN_PRODUCT_DOOR_STATUS].szDescription[m_nTypeLanguage]);

							if (m_nTypeLanguage != LANGUAGE_KOR) {

								ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																		g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																		g_stSystemString[SYSSTR_MC_WARN_PRODUCT_DOOR_STATUS].szDescription[m_nTypeLanguage]);
							}

							// 비프음 출력
							m_stSystemStatus.nBeepCount = 2;

							// 사용자 메세지 설정
							SetUserMessage(UMSG_WARN_PRODUCT_DOOR_LOCK);
							LTimerProceed.Start(m_SystemConfig.GetDelaySystem(DLY_SYS_ACTION_SHOW_USER_MESSAGE));

							// 택-타임 정지
							m_pTactTimerWnd[nSTATION_NO]->PostMessage(UM_TACT_TIMER_STATE, TACT_STOP);

							PROCESS.nCurrentStep++;
							break;

		case	281		:
							if (LTimerProceed.Verify()) {
							
								// 사용자 메세지 설정
								RestoreUserMessage();
								SetUserMessage(UMSG_STANDBY);

								PROCESS.nCurrentStep = 230;
							}

							break;

		// 완료
		case	290		:
							// 비프음 출력
							m_stSystemStatus.nBeepCount = 1;

							// 사용자 메세지 설정
							SetUserMessage(UMSG_PREPARING);

							// 업데이트 UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_WORK_SHEET_01 | UI_WORK_SHEET_02 | UI_VISION_SHEET | UI_PRODUCT_CODE_OUT;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;
							PROCESS.stParamUI.stWorkSheet.bOnClear	= TRUE;

							// 택-타임 시작
							m_pTactTimerWnd[nSTATION_NO]->PostMessage(UM_TACT_TIMER_STATE, TACT_PROCEED);

							PROCESS.nCurrentStep  = STEP_STN_SUB_02;
							PROCESS.nReturn02Step = 291;
							break;

		case	291		:
							PROCESS.nCurrentStep = PROCESS.bOnInterLock ? 280 : STEP_STN_WORK;
							break;


		/////////////////////////////////////////////////////////////
		// 작업 /////////////////////////////////////////////////////
		case	STEP_STN_WORK	:
									PROCESS.nCurrentStep = 2010;
									break;

		// 공정 상태 설정
		case	2010	:
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_PROCEED;

							// 업데이트 UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_STATUS_STATION;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;

							PROCESS.nCurrentStep = 2050;
							break;

		// 제품 코드 체크 (자동 스캔)
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

								// 메세지 출력
								NormalMessage(TRUE, _T("[%s] AUTO SCAN PRODUCT CODE = %s"),	g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage], 
																							GetBarcodeInfo(nBCS_INPUT_A));

								bOnCheckProductCodeEmpty = TRUE;
								bOnErrorProductCode		 = FALSE;

								PROCESS.nCurrentStep	 = STEP_STN_SCAN_CODE;
								PROCESS.nReturn03Step	 = 2053;
								break;
							}

							// 스캔 타임 아웃
							if (LTimerTimeOutScan.Verify()) {

								// 바코드 스캐너 트리거 해제
								SetTrigBarcode(nBCS_INPUT_A, FALSE);
								LTimerSteadyScan.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_BCD_CONTROL));

								if (++PROCESS.nRetryCount >= MAX_RETRY_BCD_SCAN) {

									// 메세지 출력
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_SCAN].szDescription[m_nTypeLanguage]);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_SCAN].szDescription[LANGUAGE_KOR]);
									}

									// 비프음 출력
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

		// 로딩 유닛 : FWD
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

		// 준비 작업
		case	2100	:
							// 작업 상태 정보 초기화
							InitWorkStatus(nSTATION_NO);
							_tcscpy_s((PROCESS.pstWorkStatus)->szProductCode, MAX_STRINPUT_S, GetCurrentProductCode(nSTATION_NO));

							// 비전 검사 초기화
							InitVisionTest();

							// 현재 비전 검사 작업 시트 업데이트 번호 초기화
							m_stSystemStatus.nCurrentVisionWorkSheetUpdateNo = 0;

							// 상세 보기 인터록 설정
							m_stSystemStatus.bOnInterlockViewDetail = TRUE;

							// 작업 결과 디렉토리 생성
							CreateWorkResultDirectory(nSTATION_NO);

							// 비전 이미지 윈도우 초기화
							if (m_pMainWnd)	{
								
								m_stSystemStatus.bIsVisionImageWindowCleared = FALSE;
								m_pMainWnd->PostMessage(UM_VISION_CLEAR_IMAGE);
							}

							PROCESS.nCurrentStep = 2110;
							break;

		// 프로브 가이드 : ON
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

		// 프로브 : ON
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

		// 메인 작업 시작
		case	2200	:
							// 프로세스 잠금 설정
							m_stSystemStatus.bIsStationProcessLock[nSTATION_NO][nSTATION_SUB_NO] = TRUE;

							// 메인 프로세스 시작
							m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	2201	:
							if (!m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]) {

								// 메인 프로세스 결과 설정
								PROCESS.bResultMainProcess = m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO];

								PROCESS.nCurrentStep = 2250;
							}

							break;

		// 언로딩
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

		// 대기 위치 이동
		case	2280	:
							PROCESS.nCurrentStep  = STEP_STN_HOME;
							PROCESS.nReturn02Step = 2290;
							break;

		// 메인 작업 불합격 시 재작업
		case	2290	:
							// 기능 제외

							PROCESS.nCurrentStep = 2300;
							break;

		// 제품 도어 열림 체크
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

		// 제품 도어 닫기
		case	2310	:
							PROCESS.nCurrentStep  = STEP_STN_SUB_03;
							PROCESS.nReturn02Step = 2320;
							break;

		// 대기 위치 이동
		case	2320	:
							PROCESS.nCurrentStep  = STEP_STN_HOME;
							PROCESS.nReturn02Step = 2330;
							break;

		// 로딩 유닛 : FWD
		case	2330	:
							pOnSCP_MoveParts[SCP_S01_LOADING_FWD] = TRUE;

							PROCESS.nCurrentStep = 2380;
							break;

		// 작업 결과 설정
		case	2380	:
							// 작업 상태 정보 설정
							(PROCESS.pstWorkStatus)->nResultFinal = PROCESS.bResultMainProcess ? T_RESULT_SUCCESS : T_RESULT_FAILURE;

							// 프로세스 잠금 해제
							m_stSystemStatus.bIsStationProcessLock[nSTATION_NO][nSTATION_SUB_NO] = FALSE;

							// 택-타임 정지
							m_pTactTimerWnd[nSTATION_NO]->PostMessage(UM_TACT_TIMER_STATE, TACT_STOP);

							// 생산 수량 설정
							if (!PROCESS.bIsMasterProduct) {

								m_pProductionWnd->SetCumulativeCount();
								m_pProductionWnd->SetProductionCount(PROCESS.bResultMainProcess);
							}

							PROCESS.nCurrentStep++;
							break;
		
		case	2381	:
							// 라벨 출력 설정
							if (!m_SystemConfig.IsTestMode() && !PROCESS.bIsMasterProduct && m_stSystemStatus.bUsePrintLabel && PROCESS.bResultMainProcess) {

								UINT		nPrintQuantity	= 1;
								CString		strOutputCode	= _T("");
							

								if (nPrintQuantity) {

									// 라벨 포맷 생성
									CreateLabelFormat(BCP_PRINT_1, *PROCESS.pstLabelPrintInfo, nPrintQuantity, 0, &strOutputCode);
									_tcscpy_s((PROCESS.pstWorkStatus)->szOutputCode, MAX_STRINPUT_S, strOutputCode);

									// 업데이트 UI
									PROCESS.bOnUpdateUI				= TRUE;
									PROCESS.stParamUI.nUpdateID		= UI_PRODUCT_CODE_OUT;
									PROCESS.stParamUI.nStationNo	= nSTATION_NO;
									_tcscpy_s(PROCESS.stParamUI.stProductCodeInfo.szCodeOutput, MAX_STRINPUT_L, strOutputCode);

									// 라벨 출력 시작
									m_stSystemStatus.bOnPrintLabel[BCP_PRINT_1]	= TRUE;
								}
							}

							PROCESS.nCurrentStep++;
							break;

		case	2382	:
							// 작업 시트 저장
							SaveWorkSheet01(PROCESS.bIsMasterProduct);
							SaveWorkSheet01T(PROCESS.bIsMasterProduct);
							SaveWorkSheetERP_01(PROCESS.bIsMasterProduct);

							// 제품 코드 파일 생성
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

							// 서브 카운터 설정
							m_stWorkSubCounter.nCountStation[nSTATION_NO]++;
							SaveWorkSubCounter();

							// 공정 상태 설정
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_COMPLETE;

							// 상세 보기 인터록 해제
							m_stSystemStatus.bOnInterlockViewDetail = FALSE;

							// 업데이트 UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_STATUS_STATION | UI_SUB_COUNTER;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;

							// 사용자 메세지 설정
							SetUserMessage(UMSG_COMPLETE);

							PROCESS.nCurrentStep = 2390;
							break;

		// 로딩 유닛 확인 : FWD
		case	2390	:
							if (!pOnSCP_MoveParts[SCP_S01_LOADING_FWD])
								PROCESS.nCurrentStep = 2400;

							if (m_stSystemStatus.bOnMP_Error[nSTATION_NO])
								PROCESS.nCurrentStep = STEP_STN_ERROR_PARTS;

							break;

		// 불합격 판정 시 사용자 배출
		case	2400	:
							if (!m_SystemConfig.IsTestMode() && !PROCESS.bIsMasterProduct && (PROCESS.pstWorkStatus)->nResultFinal != T_RESULT_SUCCESS) {
							
								PROCESS.nCurrentStep	= STEP_STN_USER_UNLOAD;
								PROCESS.nReturn01Step	= 2900;
								break;
							}

							// 비프음 출력 (합격 판정 시)
							m_stSystemStatus.nBeepCount = 3;

							PROCESS.nCurrentStep = 2410;
							break;

		// 라벨 출력 확인
		case	2410	:
							if (!m_stSystemStatus.bOnPrintLabel[BCP_PRINT_1])
								PROCESS.nCurrentStep = 2800;
							
							break;

		// 제품 제거 확인
		case	2800	:
							if (m_SystemConfig.IsTestMode())
								PROCESS.nCurrentStep = 2900;

							if (!GetDIStatus(DI_SENS_S01_DETECT_PRODUCT) && !GetDIStatus(DI_SENS_S01_CLAMP_1_ON) && !GetDIStatus(DI_SENS_S01_CLAMP_1_ON))
								PROCESS.nCurrentStep = 2900;

							break;

		// 완료
		case	2900	:
							// 공정 상태 설정
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_NONE;

							// 업데이트 UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_STATUS_STATION;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;

							// 마스터 검사 완료 설정
							m_stSystemStatus.bIsMasterTestComplete = CheckMasterTest();

							PROCESS.nCurrentStep = m_SystemConfig.IsTestMode() ? 290 : STEP_STN_STANDBY;
							break;


		/////////////////////////////////////////////////////////////
		// 사용자 배출 //////////////////////////////////////////////
		case	STEP_STN_USER_UNLOAD	:
											PROCESS.nCurrentStep = 3020;
											break;

		// 메세지 박스 출력
		case	3020	:
							// 메세지 박스가 출력 상태 체크
							if (!m_stSystemStatus.bIsDisplayMessageBox) {
							
								m_stSystemStatus.bIsDisplayMessageBox = TRUE;

								PROCESS.nCurrentStep++;
							}

							break;

		case	3021	:
							// 메세지 출력
							ErrorMessage(TRUE, _T("[S%02d/%s] 불량 제품을 제거 후 불량함에 투입해 주십시오."), nSTATION_NO + 1, g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

							// 시스템 플래그 설정
							m_stSystemStatus.bOnWaitForUser			= TRUE;				// 사용자 입력 대기 설정
							m_stSystemStatus.bOnBuzzer				= TRUE;				// 경고음 출력
							m_stSystemStatus.nMessageBoxButtonCode	= MBOX_BCODE_NONE;	// 버튼 코드 초기화

							// 메세지 박스 생성
							PROCESS.pstMBoxParam = new MBOX_PARAM_T;
							if (PROCESS.pstMBoxParam) {

								CString		strValue = _T("");

								strValue.AppendFormat(_T("\n [사용자 불량 배출]\n\n"));
								strValue.AppendFormat(_T(" 최종 성능 검사 불합격 제품입니다.\n"));
								strValue.AppendFormat(_T(" 제품을 제거 후 불량함에 투입해 주십시오."));
	
								ZeroMemory(PROCESS.pstMBoxParam, sizeof(MBOX_PARAM_T));
								_stprintf_s((PROCESS.pstMBoxParam)->szButtonTitle[MBOX_BUTTON_0], MAX_STRINPUT, _T("경고음 해제\n(ESC)"));
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

							// 비프음 2회 출력
							m_stSystemStatus.nBeepCount	= 2;

							SErrorMessage(TRUE, _T("[S%02d/%s] 메세지 박스를 생성할 수 없습니다."),	nSTATION_NO + 1, 
																									g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

							PROCESS.nCurrentStep++;
							break;

		case	3022	:
							if (m_stSystemStatus.nMessageBoxButtonCode != MBOX_BCODE_NONE) {

								// 버튼 1 : 경고음 해제
								if (m_stSystemStatus.nMessageBoxButtonCode == MBOX_BCODE_0) {

									m_stSystemStatus.bOnBuzzer				= FALSE;			// 경고음 해제
									m_stSystemStatus.nMessageBoxButtonCode	= MBOX_BCODE_NONE;	// 버튼 코드 초기화
								}
							}

							// 불량함 투입 체크
							if (!GetDIStatus(DI_SENS_S01_DETECT_PRODUCT) && 
								!GetDIStatus(DI_SENS_S01_CLAMP_1_ON) && 
								!GetDIStatus(DI_SENS_S01_CLAMP_1_ON) &&
								(m_SystemConfig.UseSystemOption(SOPT_DISABLE_CHECK_NG_BOX) || GetDIStatus(DI_SENS_S01_DETECT_NG_BOX))) {

								// 메세지 출력
								ErrorMessage(TRUE, _T("[S%02d/%s] 불량함에 제품 투입이 완료되었습니다."), nSTATION_NO + 1, g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3023	:
							// 메세지 박스 출력 플래그 해제
							m_stSystemStatus.bIsDisplayMessageBox = FALSE;

							// 메세지 박스 감추기	
							m_pMessageBoxDlg->SendMessage(UM_DPS_DLG_MESSAGE_BOX_SHOWHIDE, SW_HIDE, NULL);

							// 시스템 플래그 설정
							m_stSystemStatus.bOnWaitForUser	= FALSE;	// 사용자 입력 대기 해제
							m_stSystemStatus.bOnBuzzer		= FALSE;	// 경고음 해제

							PROCESS.nCurrentStep = 3090;
							break;

		// 완료
		case	3090	:
							PROCESS.nCurrentStep = PROCESS.nReturn01Step;
							break;


		/////////////////////////////////////////////////////////////
		// 작업 정지 예약 ///////////////////////////////////////////
		case	STEP_STN_WAIT_STOP	:
										if (!m_stSystemStatus.bOnOperatingStopReservated) {

											PROCESS.bIsStopReservated	= FALSE;
											PROCESS.nCurrentStep		= PROCESS.nRecoveryStopStep;
										}

										break;


		/////////////////////////////////////////////////////////////
		// 오류 /////////////////////////////////////////////////////
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

											// 디버그 메세지
											SDebugMessage(TRUE, _T("[S%02d] ERROR PARTS"), nSTATION_NO);
											break;

		case	STEP_STN_ERROR_SYSTEM	:
											// 디버그 메세지
											SDebugMessage(TRUE, _T("[S%02d] ERROR SYSTEM"), nSTATION_NO);
											break;


		/////////////////////////////////////////////////////////////
		// 일시 정지 스텝 ///////////////////////////////////////////
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

		// 스텝 복구
		case	20100	:
							PROCESS.nCurrentStep	= PROCESS.nRecoveryStep;
							PROCESS.bOnPause		= FALSE;
							break;


		/////////////////////////////////////////////////////////////
		// 비상 정지 스텝 ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop)	{

									PROCESS.nRecoveryStep	= 0;
									PROCESS.nCurrentStep	= 20001;
								}

								break;


		/////////////////////////////////////////////////////////////
		// 장비 초기화 스텝 /////////////////////////////////////////
		case	STEP_MC_INIT	:
									PROCESS.nCurrentStep = 22010;
									break;

		case	22010	:
							// 공정 초기화
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
	// 운전 정지 체크 ///////////////////////////////////////////////
	CheckProcessOperatingStop(PROCESS);


	/////////////////////////////////////////////////////////////////
	// 일반 /////////////////////////////////////////////////////////
	CheckProcessGeneral(nSTATION_NO, PROCESS);


	/////////////////////////////////////////////////////////////////
	// 스텝 모니터링 ////////////////////////////////////////////////
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
// 프로세스 : 공정 #02 - 검사 공정 (SK) ///////////////////////////////////////
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
	// 프로세스 데이터 초기화 ///////////////////////////////////////
	ProcessDataInitialize(PROCESS);


	/////////////////////////////////////////////////////////////////
	// 자동 운전 시작/정지 초기화 ///////////////////////////////////
	CheckProcessOperating(PROCESS);


	/////////////////////////////////////////////////////////////////
	// 장비 초기화 //////////////////////////////////////////////////
	if (CheckProcessMachineInitialize(PROCESS))
		return	NULL;


	/////////////////////////////////////////////////////////////////
	// 작업 정지 예약 ///////////////////////////////////////////////
	if (CheckProcessOperatingStopReservated(nSTATION_NO, nSTATION_SUB_NO, PROCESS))
		return	NULL;


	/////////////////////////////////////////////////////////////////
	// 수동 제어 모드 ///////////////////////////////////////////////
	if (CheckProcessManualControlMode(nSTATION_NO, PROCESS))
		return	NULL;
	

	/////////////////////////////////////////////////////////////////
	// 비상/일시 정지 상태 //////////////////////////////////////////
	if (CheckProcessEmergencyStop(PROCESS))					return	NULL;
	if (CheckProcessOperatingPause(nSTATION_NO, PROCESS))	return	NULL;


	/////////////////////////////////////////////////////////////////
	// 스텝 프로세스 ////////////////////////////////////////////////
	switch (PROCESS.nCurrentStep) {

		case	0		:
							PROCESS.nCurrentStep = 10;
							break;

		// 시스템 체크
		case	10		:
							if (IsSystemReady()) {
							
								PROCESS.nCurrentStep = 20;
							}
								
							break;

		// 플래그 초기화
		case	20		:
							// 공정 프로세스 데이터 초기화
							StationProcessDataInitialize(nSTATION_NO, nSTATION_SUB_NO, PROCESS);

							PROCESS.nCurrentStep = 30;
							break;

		// 유닛 초기화
		case	30		:
							// 바코드 스캐너 트리거 해제
							SetTrigBarcode(nBCS_INPUT_M, FALSE);
							SetTrigBarcode(nBCS_INPUT_A, FALSE);

							PROCESS.nCurrentStep = 40;
							break;

		// 공정 상태 설정
		case	40		:
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_NONE;

							PROCESS.nCurrentStep = 50;
							break;

		// 자동 운전 체크
		case	50		:
							if (m_stSystemStatus.bOnOperating) {

								PROCESS.nCurrentStep = 60;
							}

							break;

		// 모델 프로파일 로드
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

							SErrorMessage(TRUE, _T("[S%02d/%s] 모델 정보를 로드할 수 없습니다."),	nSTATION_NO, 
																									g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

							PROCESS.nCurrentStep = STEP_STN_ERROR_SYSTEM;
							break;

		// 완료
		case	90		:
							PROCESS.nCurrentStep	= STEP_STN_INIT;
							PROCESS.nReturn01Step	= STEP_STN_STANDBY;
							break;


		/////////////////////////////////////////////////////////////
		// 초기화 ///////////////////////////////////////////////////
		case	STEP_STN_INIT	:
									PROCESS.nCurrentStep = 110;
									break;

		// 플래그 초기화
		case	110		:
							m_stSystemStatus.bOnStationInitializeResult[nSTATION_NO][nSTATION_SUB_NO]	= TRUE;
							m_stSystemStatus.bIsStationProcessLock[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;

							PROCESS.nCurrentStep = 120;
							break;

		// 공정 상태 설정
		case	120		:
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_NONE;

							// 업데이트 UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_STATUS_STATION;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;

							PROCESS.nCurrentStep = 130;
							break;

		// 유닛 초기화
		case	130		:
							// 연결 릴레이 초기화
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

							// 비전 트리거 해제
							SetDOStatus(DO_OFF, DO_SIG_S02_VISION_TRIG);	
							
							// 바코드 스캐너 트리거 해제
							SetTrigBarcode(nBCS_INPUT_M, FALSE);
							SetTrigBarcode(nBCS_INPUT_A, FALSE);

							PROCESS.nCurrentStep = 140;
							break;

		// 작업 대기 위치 이동
		case	140		:
							PROCESS.nCurrentStep = 150;
							break;

		// 작업 유닛 초기화
		case	150		:
							if (!PROCESS.bOnMachineInitialize) {

								PROCESS.nCurrentStep	= STEP_STN_SUB_01;
								PROCESS.nReturn02Step	= 190;
								break;
							}

							PROCESS.nCurrentStep = 190;
							break;

		// 완료
		case	190		:
							// 초기화 완료 플래그 설정
							m_stSystemStatus.bOnStationInitializeComplete[nSTATION_NO][nSTATION_SUB_NO] = TRUE;

							PROCESS.nCurrentStep = PROCESS.nReturn01Step;
							break;


		/////////////////////////////////////////////////////////////
		// 작업 유닛 초기화 /////////////////////////////////////////
		case	STEP_STN_SUB_01	:
									PROCESS.nCurrentStep = 8010;
									break;

		// 준비 작업
		case	8010	:
							PROCESS.nCurrentStep = 8020;
							break;

		// 제품 도어 누름 : UP
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

		// 프로브 : OFF
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

		// 도어 열림 유닛 : DN
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

		// 완료
		case	8090	:
							PROCESS.nCurrentStep = PROCESS.nReturn02Step;
							break;


		/////////////////////////////////////////////////////////////
		// 메세지 박스 출력 /////////////////////////////////////////
		case	STEP_STN_MESSAGE_BOX_01	:
											PROCESS.nCurrentStep = 9010;
											break;

		case	9010	:
							// 메세지 박스가 출력 상태 체크
							if (!m_stSystemStatus.bIsDisplayMessageBox) {
							
								m_stSystemStatus.bIsDisplayMessageBox = TRUE;

								PROCESS.nCurrentStep++;
							}

							break;

		case	9011	:
							// 시스템 플래그 설정
							m_stSystemStatus.bOnWaitForUser			= TRUE;				// 사용자 입력 대기 설정
							m_stSystemStatus.bOnBuzzer				= TRUE;				// 경고음 출력
							m_stSystemStatus.nMessageBoxButtonCode	= MBOX_BCODE_NONE;	// 버튼 코드 초기화

							// 메세지 박스 생성
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

							// 비프음 2회 출력
							m_stSystemStatus.nBeepCount = 2;

							SErrorMessage(TRUE, _T("[S%02d/%s] 메세지 박스를 생성할 수 없습니다."),	nSTATION_NO + 1, 
																									g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

							PROCESS.nCurrentStep = 9013;
							break;

		case	9012	:
							if (m_stSystemStatus.nMessageBoxButtonCode != MBOX_BCODE_NONE) {

								// 버튼 0 : 확인
								if (m_stSystemStatus.nMessageBoxButtonCode == MBOX_BCODE_0) {

									PROCESS.nCurrentStep++;
									break;
								} 

								// 버튼 1 : 경고음 해제
								if (m_stSystemStatus.nMessageBoxButtonCode == MBOX_BCODE_1) {

									m_stSystemStatus.bOnBuzzer				= FALSE;			// 경고음 해제
									m_stSystemStatus.nMessageBoxButtonCode	= MBOX_BCODE_NONE;	// 버튼 코드 초기화
								}
							}

							break;
								
		case	9013	:
							// 메세지 박스 출력 플래그 해제
							m_stSystemStatus.bIsDisplayMessageBox = FALSE;

							// 메세지 박스 감추기	
							m_pMessageBoxDlg->SendMessage(UM_DPS_DLG_MESSAGE_BOX_SHOWHIDE, SW_HIDE, NULL);

							// 시스템 플래그 설정
							m_stSystemStatus.bOnWaitForUser	= FALSE;	// 사용자 입력 대기 해제
							m_stSystemStatus.bOnBuzzer		= FALSE;	// 경고음 해제

							PROCESS.nCurrentStep = 9090;
							break;

		// 완료
		case	9090	:
							PROCESS.nCurrentStep = PROCESS.nReturn03Step;
							break;


		/////////////////////////////////////////////////////////////
		// 제품 코드 체크 ///////////////////////////////////////////
		case	STEP_STN_SCAN_CODE	:
										PROCESS.nCurrentStep = 6010;
										break;

		// 제품 코드 체크
		case	6010	:
							{
								CString		strProductCodeM		= GetBarcodeInfo(nBCS_INPUT_M);
								CString		strProductCodeA		= GetBarcodeInfo(nBCS_INPUT_A);
								CString		strProductCode		= _T("");
								BOOL		bOnErrorProduct		= FALSE;
								UINT		nCodeStatus			= BCD_SCAN_NONE;
								UINT		nCodeWorkNG			= WORK_NG_NONE;


								// 스캔 코드 설정
								strProductCode = strProductCodeM;
								if (strProductCode.IsEmpty())	strProductCode = strProductCodeA;

								// 마스터 제품 코드 체크
								PROCESS.bIsMasterProduct = FALSE;
								if (!strProductCode.IsEmpty()) {
								
									for (UINT nIndex = 0; nIndex < MAX_BCD_MASTER_CODE; nIndex++) {
									
										if (strProductCode.Compare(((PSP_WI_BASIC_SETUP_T)PROCESS.pstStationSetupInfo)->szMasterCode[nIndex]) == 0)
											PROCESS.bIsMasterProduct = TRUE;
									}

									if (PROCESS.bIsMasterProduct) {
									
										// 메세지 출력
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

								// 제품 코드 체크
								if (!PROCESS.bIsMasterProduct && (PROCESS.pstModelProfileConfig)->bWorkOption[WOPT_USE_SCAN_CODE]) {
								
									// 제품 코드 없음
									if (bOnCheckProductCodeEmpty && strProductCode.IsEmpty()) {
									
										// 메세지 출력
										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_INPUT].szDescription[m_nTypeLanguage]);

										if (m_nTypeLanguage != LANGUAGE_KOR) {

											ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																					g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																					g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_INPUT].szDescription[LANGUAGE_KOR]);
										}
	
										// 코드 상태 설정
										nCodeStatus		= BCD_SCAN_EMPTY;
										bOnErrorProduct	= TRUE;
									
									// 제품 코드 있음
									} else {

										CString		strInputFormat	= (PROCESS.pstWorkInfo)->szWorkInfoValue[WI_ITEM_BCD_INPUT_FORMAT];
									
										// 제품 코드 포맷 체크
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

										// 제품 코드 중복 체크
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

									// 제품 코드 오류
									if (bOnErrorProduct) {
									
										// 업데이트 UI
										PROCESS.bOnUpdateUI				= TRUE;
										PROCESS.stParamUI.nUpdateID		= UI_PRODUCT_CODE_IN;
										PROCESS.stParamUI.nStationNo	= nSTATION_NO;
										PROCESS.stParamUI.stProductCodeInfo.nStatusCodeInput = nCodeStatus;
										_tcscpy_s(PROCESS.stParamUI.stProductCodeInfo.szCodeInput, MAX_STRINPUT_L, strProductCode);

										// 비프음 출력
										m_stSystemStatus.nBeepCount = 2;

										// 플래그 설정
										bOnErrorProductCode = TRUE;

										PROCESS.nCurrentStep = 6090;
										break;
									}
								}

								if (!strProductCode.IsEmpty()) {
								
									// 현재 제품 코드 설정
									SetCurrentProductCode(nSTATION_NO, strProductCode);

									PROCESS.nCurrentStep = 6020;
									break;
								}

								PROCESS.nCurrentStep = 6090;
							}

							break;

		// 마스터 검사 체크
		case	6020	:
							if (!PROCESS.bIsMasterProduct && m_SystemConfig.UseSystemOption(SOPT_ENABLE_CHECK_MASTER_TEST)) {
		
								if (!CheckMasterTest()) {

									// 메세지 출력
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[SYSSTR_MC_WARN_MASTER_TEST].szDescription[m_nTypeLanguage]);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[SYSSTR_MC_WARN_MASTER_TEST].szDescription[LANGUAGE_KOR]);
									}
								
									// 비프음 출력
									m_stSystemStatus.nBeepCount = 2;

									// 현재 제품 코드 초기화
									ClearCurrentProductCode(nSTATION_NO);

									// 사용자 메세지 설정
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

								// 사용자 메세지 복원
								if (PROCESS.bOnSetUserMessage)	
									RestoreUserMessage();

								// 플래그 설정
								bOnErrorProductCode = TRUE;

								PROCESS.nCurrentStep = 6090;
							}

							break;

		// 완료
		case	6090	:
							PROCESS.nCurrentStep = PROCESS.nReturn03Step;
							break;


		/////////////////////////////////////////////////////////////
		// 대기 /////////////////////////////////////////////////////
		case	STEP_STN_STANDBY	:
										// 시작 옵션 대기
										if (m_stSystemStatus.bOnStationProcessStart)
											PROCESS.nCurrentStep = 210;

										break;

		// 공정 상태 설정
		case	210		:
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_STANDBY;

							// 업데이트 UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_STATUS_STATION;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;

							PROCESS.nCurrentStep = 220;
							break;

		// 준비 작업
		case	220		:
							// 사용자 메세지 설정
							SetUserMessage(UMSG_STANDBY);

							// 바코드 정보 초기화
							ClearBarcodeInfo(nBCS_INPUT_M);
							ClearBarcodeInfo(nBCS_INPUT_A);
							ClearCurrentProductCode(nSTATION_NO);

							PROCESS.nCurrentStep = 230;
							break;

		// 시작 버튼 입력 체크
		case	230		:
							if (!GetDIStatus(DI_BTN_S02_START))
								PROCESS.nCurrentStep++;
							
							break;

		case	231		:
							if (GetDIStatus(DI_BTN_S02_START)) {
							
								// 버튼 입력 지연
								LTimerSensor.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_PUSH_BUTTON));

								PROCESS.nCurrentStep++;
								break;
							}

							// 시뮬래이션 모드
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

		// 라벨 발행 여부 체크
		case	235		:
								if (m_stSystemStatus.stPrintStatus[BCP_PRINT_1].bIsLabelWaiting) {

									// 메세지 출력
									if (m_nTypeLanguage == LANGUAGE_KOR)	ErrorMessage(TRUE, _T("[S%02d/%s] 라벨이 이미 발행되어 있습니다."),	nSTATION_NO, g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);
									else									ErrorMessage(TRUE, _T("[S%02d/%s] LABEL IS ALREADY ISSUED."),	nSTATION_NO, g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);
									
									// 비프음 출력
									m_stSystemStatus.nBeepCount = 2;

									PROCESS.nCurrentStep = 230;
									break;
								}

								PROCESS.nCurrentStep = 240;
								break;

		// 제품 감지 및 클램프 체크, PIN S/W 체크
		case	240		:
							// 제품 및 PIN S/W 감지 체크
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

									// 메세지 출력
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[nSystemMessageID].szDescription[m_nTypeLanguage]);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[nSystemMessageID].szDescription[m_nTypeLanguage]);
									}

									// 비프음 출력
									m_stSystemStatus.nBeepCount = 2;

									PROCESS.nCurrentStep = 230;
								}

								break;
							}

							PROCESS.nCurrentStep = 240;
							break;

		case	245		:
							// 제품 클램프 체크
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

									// 메세지 출력
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CLAMP].szDescription[m_nTypeLanguage]);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CLAMP].szDescription[m_nTypeLanguage]);
									}

									// 비프음 출력
									m_stSystemStatus.nBeepCount = 2;

									PROCESS.nCurrentStep = 230;
								}

								break;
							}

							PROCESS.nCurrentStep = 245;
							break;

		// 오류 체크
		case	250		:
							{
								BOOL		bIsErrorState	= FALSE;
								UINT		nUserMessageID	= 0;
								CString		strErrorMessage	= _T("");


								// 초기화
								strMessage.Empty();

								// 프로브 카운터 체크
								if (!bIsErrorState) {

									bIsErrorState |= m_stSystemStatus.bIsFullProbeCounter[nSTATION_NO];

									if (bIsErrorState) {

										strMessage.AppendFormat(_T(" %s\n %s\n"), g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage], g_stSystemString[SYSSTR_MC_WARN_EXPIRE_PROBE].szDescription[m_nTypeLanguage]);
										strMessage.AppendFormat(_T(" %s"), g_stSystemString[SYSSTR_MC_WARN_EXPIRE_PROBE_COMMENT].szDescription[m_nTypeLanguage]);
										strErrorMessage		= g_stSystemString[SYSSTR_MC_WARN_EXPIRE_PROBE_COMMENT].szDescription[m_nTypeLanguage];
										nUserMessageID		= UMSG_WARN_PROBE_COUNT_EXPIRED;
									}
								}

								// 오류 처리
								if (bIsErrorState) {

									// 메세지 출력
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			strErrorMessage);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[SYSSTR_MC_WARN_EXPIRE_PROBE_COMMENT].szDescription[LANGUAGE_KOR]);
									}

									// 사용자 메세지 설정
									PROCESS.bOnSetUserMessage = SetUserMessage(nUserMessageID);

									PROCESS.nCurrentStep	= STEP_STN_MESSAGE_BOX_01;
									PROCESS.nReturn03Step	= 251;
									break;
								}

								PROCESS.nCurrentStep = 260;
							}

							break;

		case	251		:
							// 사용자 메세지 복원
							if (PROCESS.bOnSetUserMessage)	
								RestoreUserMessage();

							PROCESS.nCurrentStep--;
							break;

		// 제품 코드 체크 (수동 스캔)
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

		// 제품 도어 열림 체크
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
							
									// 메세지 출력
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[SYSSTR_MC_WARN_PRODUCT_DOOR_OPENED].szDescription[m_nTypeLanguage]);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[SYSSTR_MC_WARN_PRODUCT_DOOR_OPENED].szDescription[m_nTypeLanguage]);
									}

									// 비프음 출력
									m_stSystemStatus.nBeepCount = 2;

									// 타이머 설정
									LTimerProceed.Start(m_SystemConfig.GetDelaySystem(DLY_SYS_INTV_USER_WARNING_MESSAGE));
								}

								break;
							}

							PROCESS.nCurrentStep = 270;
							break;

		// 제품 도어 상태 불량
		case	280		:
							// 메세지 출력
							ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																	g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																	g_stSystemString[SYSSTR_MC_WARN_PRODUCT_DOOR_STATUS].szDescription[m_nTypeLanguage]);

							if (m_nTypeLanguage != LANGUAGE_KOR) {

								ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO, 
																		g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																		g_stSystemString[SYSSTR_MC_WARN_PRODUCT_DOOR_STATUS].szDescription[m_nTypeLanguage]);
							}

							// 비프음 출력
							m_stSystemStatus.nBeepCount = 2;

							// 사용자 메세지 설정
							SetUserMessage(UMSG_WARN_PRODUCT_DOOR_LOCK);
							LTimerProceed.Start(m_SystemConfig.GetDelaySystem(DLY_SYS_ACTION_SHOW_USER_MESSAGE));

							// 택-타임 정지
							m_pTactTimerWnd[nSTATION_NO]->PostMessage(UM_TACT_TIMER_STATE, TACT_STOP);

							PROCESS.nCurrentStep++;
							break;

		case	281		:
							if (LTimerProceed.Verify()) {
							
								// 사용자 메세지 설정
								RestoreUserMessage();
								SetUserMessage(UMSG_STANDBY);

								PROCESS.nCurrentStep = 230;
							}

							break;

		// 완료
		case	290		:
							// 비프음 출력
							m_stSystemStatus.nBeepCount = 1;

							// 사용자 메세지 설정
							SetUserMessage(UMSG_PREPARING);

							// 업데이트 UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_WORK_SHEET_01 | UI_WORK_SHEET_02 | UI_VISION_SHEET | UI_PRODUCT_CODE_OUT;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;
							PROCESS.stParamUI.stWorkSheet.bOnClear	= TRUE;

							// 택-타임 시작
							m_pTactTimerWnd[nSTATION_NO]->PostMessage(UM_TACT_TIMER_STATE, TACT_PROCEED);

							PROCESS.nCurrentStep  = STEP_STN_SUB_01;
							PROCESS.nReturn02Step = 291;
							break;

		case	291		:
							PROCESS.nCurrentStep = PROCESS.bOnInterLock ? 280 : STEP_STN_WORK;
							break;


		/////////////////////////////////////////////////////////////
		// 작업 /////////////////////////////////////////////////////
		case	STEP_STN_WORK	:
									PROCESS.nCurrentStep = 2010;
									break;

		// 공정 상태 설정
		case	2010	:
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_PROCEED;

							// 업데이트 UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_STATUS_STATION;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;

							PROCESS.nCurrentStep = 2050;
							break;

		// 제품 코드 체크 (자동 스캔)
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

								// 메세지 출력
								NormalMessage(TRUE, _T("[%s] AUTO SCAN PRODUCT CODE = %s"),	g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage], 
																							GetBarcodeInfo(nBCS_INPUT_A));

								bOnCheckProductCodeEmpty = TRUE;
								bOnErrorProductCode		 = FALSE;

								PROCESS.nCurrentStep	 = STEP_STN_SCAN_CODE;
								PROCESS.nReturn03Step	 = 2053;
								break;
							}

							// 스캔 타임 아웃
							if (LTimerTimeOutScan.Verify()) {

								// 바코드 스캐너 트리거 해제
								SetTrigBarcode(nBCS_INPUT_A, FALSE);
								LTimerSteadyScan.Start(m_SystemConfig.GetDelayControl(DLY_CTRL_STEADY_BCD_CONTROL));

								if (++PROCESS.nRetryCount >= MAX_RETRY_BCD_SCAN) {

									// 메세지 출력
									ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																			g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage],
																			g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_SCAN].szDescription[m_nTypeLanguage]);

									if (m_nTypeLanguage != LANGUAGE_KOR) {

										ErrorMessage(TRUE, _T("[S%02d/%s] %s"),	nSTATION_NO + 1, 
																				g_stStationName[nSTATION_NO].szDescription[LANGUAGE_KOR],
																				g_stSystemString[SYSSTR_MC_WARN_PRODUCT_CODE_SCAN].szDescription[LANGUAGE_KOR]);
									}

									// 비프음 출력
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

		// 준비 작업
		case	2100	:
							// 작업 상태 정보 초기화
							InitWorkStatus(nSTATION_NO);
							_tcscpy_s((PROCESS.pstWorkStatus)->szProductCode, MAX_STRINPUT_S, GetCurrentProductCode(nSTATION_NO));

							// 비전 검사 초기화
							InitVisionTest();

							// 현재 비전 검사 작업 시트 업데이트 번호 초기화
							m_stSystemStatus.nCurrentVisionWorkSheetUpdateNo = 0;

							// 상세 보기 인터록 설정
							m_stSystemStatus.bOnInterlockViewDetail = TRUE;

							// 작업 결과 디렉토리 생성
							CreateWorkResultDirectory(nSTATION_NO);

							// 비전 이미지 윈도우 초기화
							if (m_pMainWnd)	{
								
								m_stSystemStatus.bIsVisionImageWindowCleared = FALSE;
								m_pMainWnd->PostMessage(UM_VISION_CLEAR_IMAGE);
							}

							PROCESS.nCurrentStep = 2120;
							break;

		// 프로브 : ON
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

		// 메인 작업 시작
		case	2200	:
							// 프로세스 잠금 설정
							m_stSystemStatus.bIsStationProcessLock[nSTATION_NO][nSTATION_SUB_NO] = TRUE;

							// 메인 프로세스 시작
							m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO] = TRUE;

							PROCESS.nCurrentStep++;
							break;

		case	2201	:
							if (!m_stSystemStatus.bOnMainProcess[nSTATION_NO][nSTATION_SUB_NO]) {

								// 메인 프로세스 결과 설정
								PROCESS.bResultMainProcess = m_stSystemStatus.bIsMainProcessResult[nSTATION_NO][nSTATION_SUB_NO];

								PROCESS.nCurrentStep = 2250;
							}

							break;

		// 언로딩
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

		// 메인 작업 불합격 시 재작업
		case	2290	:
							// 기능 제외

							PROCESS.nCurrentStep = 2300;
							break;

		// ...?
		case	2300	:
							PROCESS.nCurrentStep = 2380;
							break;

		// 작업 결과 설정
		case	2380	:
							// 작업 상태 정보 설정
							(PROCESS.pstWorkStatus)->nResultFinal = PROCESS.bResultMainProcess ? T_RESULT_SUCCESS : T_RESULT_FAILURE;

							// 프로세스 잠금 해제
							m_stSystemStatus.bIsStationProcessLock[nSTATION_NO][nSTATION_SUB_NO] = FALSE;

							// 택-타임 정지
							m_pTactTimerWnd[nSTATION_NO]->PostMessage(UM_TACT_TIMER_STATE, TACT_STOP);

							// 생산 수량 설정
							if (!PROCESS.bIsMasterProduct) {

								m_pProductionWnd->SetCumulativeCount();
								m_pProductionWnd->SetProductionCount(PROCESS.bResultMainProcess);
							}

							PROCESS.nCurrentStep++;
							break;
		
		case	2381	:
							// 라벨 출력 설정
							if (!m_SystemConfig.IsTestMode() && !PROCESS.bIsMasterProduct && m_stSystemStatus.bUsePrintLabel && PROCESS.bResultMainProcess) {

								UINT		nPrintQuantity	= 1;
								CString		strOutputCode	= _T("");
							

								if (nPrintQuantity) {

									// 라벨 포맷 생성
									CreateLabelFormat(BCP_PRINT_1, *PROCESS.pstLabelPrintInfo, nPrintQuantity, 0, &strOutputCode);
									_tcscpy_s((PROCESS.pstWorkStatus)->szOutputCode, MAX_STRINPUT_S, strOutputCode);

									// 업데이트 UI
									PROCESS.bOnUpdateUI				= TRUE;
									PROCESS.stParamUI.nUpdateID		= UI_PRODUCT_CODE_OUT;
									PROCESS.stParamUI.nStationNo	= nSTATION_NO;
									_tcscpy_s(PROCESS.stParamUI.stProductCodeInfo.szCodeOutput, MAX_STRINPUT_L, strOutputCode);

									// 라벨 출력 시작
									m_stSystemStatus.bOnPrintLabel[BCP_PRINT_1]	= TRUE;
								}
							}

							PROCESS.nCurrentStep++;
							break;

		case	2382	:
							// 작업 시트 저장
							SaveWorkSheet01(PROCESS.bIsMasterProduct);
							SaveWorkSheet01T(PROCESS.bIsMasterProduct);
							SaveWorkSheetERP_01(PROCESS.bIsMasterProduct);

							// 제품 코드 파일 생성
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

							// 서브 카운터 설정
							m_stWorkSubCounter.nCountStation[nSTATION_NO]++;
							SaveWorkSubCounter();

							// 상세 보기 인터록 해제
							m_stSystemStatus.bOnInterlockViewDetail = FALSE;

							// 공정 상태 설정
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_COMPLETE;

							// 업데이트 UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_STATUS_STATION | UI_SUB_COUNTER;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;

							// 사용자 메세지 설정
							SetUserMessage(UMSG_COMPLETE);

							PROCESS.nCurrentStep = 2400;
							break;

		// 불합격 판정 시 사용자 배출
		case	2400	:
							if (!m_SystemConfig.IsTestMode() && !PROCESS.bIsMasterProduct && (PROCESS.pstWorkStatus)->nResultFinal != T_RESULT_SUCCESS) {
							
								PROCESS.nCurrentStep	= STEP_STN_USER_UNLOAD;
								PROCESS.nReturn01Step	= 2900;
								break;
							}

							// 비프음 출력 (합격 판정 시)
							m_stSystemStatus.nBeepCount = 3;

							PROCESS.nCurrentStep = 2410;
							break;

		// 라벨 출력 확인
		case	2410	:
							if (!m_stSystemStatus.bOnPrintLabel[BCP_PRINT_1])
								PROCESS.nCurrentStep = 2800;
							
							break;

		// 제품 제거 확인
		case	2800	:
							if (m_SystemConfig.IsTestMode())
								PROCESS.nCurrentStep = 2900;

							if (!GetDIStatus(DI_SENS_S02_DETECT_PRODUCT) && !GetDIStatus(DI_SENS_S02_CLAMP_1_ON) && !GetDIStatus(DI_SENS_S02_CLAMP_1_ON))
								PROCESS.nCurrentStep = 2900;

							break;

		// 완료
		case	2900	:
							// 공정 상태 설정
							m_stSystemStatus.nStationStatus[nSTATION_NO][nSTATION_SUB_NO] = STN_STATUS_NONE;

							// 업데이트 UI
							PROCESS.bOnUpdateUI				= TRUE;
							PROCESS.stParamUI.nUpdateID		= UI_STATUS_STATION;
							PROCESS.stParamUI.nStationNo	= nSTATION_NO;

							// 마스터 검사 완료 설정
							m_stSystemStatus.bIsMasterTestComplete = CheckMasterTest();

							PROCESS.nCurrentStep = m_SystemConfig.IsTestMode() ? 290 : STEP_STN_STANDBY;
							break;


		/////////////////////////////////////////////////////////////
		// 사용자 배출 //////////////////////////////////////////////
		case	STEP_STN_USER_UNLOAD	:
											PROCESS.nCurrentStep = 3020;
											break;

		// 메세지 박스 출력
		case	3020	:
							// 메세지 박스가 출력 상태 체크
							if (!m_stSystemStatus.bIsDisplayMessageBox) {
							
								m_stSystemStatus.bIsDisplayMessageBox = TRUE;

								PROCESS.nCurrentStep++;
							}

							break;

		case	3021	:
							// 메세지 출력
							ErrorMessage(TRUE, _T("[S%02d/%s] 불량 제품을 제거 후 불량함에 투입해 주십시오."), nSTATION_NO + 1, g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

							// 시스템 플래그 설정
							m_stSystemStatus.bOnWaitForUser			= TRUE;				// 사용자 입력 대기 설정
							m_stSystemStatus.bOnBuzzer				= TRUE;				// 경고음 출력
							m_stSystemStatus.nMessageBoxButtonCode	= MBOX_BCODE_NONE;	// 버튼 코드 초기화

							// 메세지 박스 생성
							PROCESS.pstMBoxParam = new MBOX_PARAM_T;
							if (PROCESS.pstMBoxParam) {

								CString		strValue = _T("");

								strValue.AppendFormat(_T("\n [사용자 불량 배출]\n\n"));
								strValue.AppendFormat(_T(" 최종 성능 검사 불합격 제품입니다.\n"));
								strValue.AppendFormat(_T(" 제품을 제거 후 불량함에 투입해 주십시오."));
	
								ZeroMemory(PROCESS.pstMBoxParam, sizeof(MBOX_PARAM_T));
								_stprintf_s((PROCESS.pstMBoxParam)->szButtonTitle[MBOX_BUTTON_0], MAX_STRINPUT, _T("경고음 해제\n(ESC)"));
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

							// 비프음 2회 출력
							m_stSystemStatus.nBeepCount	= 2;

							SErrorMessage(TRUE, _T("[S%02d/%s] 메세지 박스를 생성할 수 없습니다."),	nSTATION_NO + 1, 
																									g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

							PROCESS.nCurrentStep++;
							break;

		case	3022	:
							if (m_stSystemStatus.nMessageBoxButtonCode != MBOX_BCODE_NONE) {

								// 버튼 1 : 경고음 해제
								if (m_stSystemStatus.nMessageBoxButtonCode == MBOX_BCODE_0) {

									m_stSystemStatus.bOnBuzzer				= FALSE;			// 경고음 해제
									m_stSystemStatus.nMessageBoxButtonCode	= MBOX_BCODE_NONE;	// 버튼 코드 초기화
								}
							}

							// 불량함 투입 체크
							if (!GetDIStatus(DI_SENS_S02_DETECT_PRODUCT) && 
								!GetDIStatus(DI_SENS_S02_CLAMP_1_ON) && 
								!GetDIStatus(DI_SENS_S02_CLAMP_1_ON) &&
								(m_SystemConfig.UseSystemOption(SOPT_DISABLE_CHECK_NG_BOX) || GetDIStatus(DI_SENS_S02_DETECT_NG_BOX))) {

								// 메세지 출력
								ErrorMessage(TRUE, _T("[S%02d/%s] 불량함에 제품 투입이 완료되었습니다."), nSTATION_NO + 1, g_stStationName[nSTATION_NO].szDescription[m_nTypeLanguage]);

								PROCESS.nCurrentStep++;
							}

							break;

		case	3023	:
							// 메세지 박스 출력 플래그 해제
							m_stSystemStatus.bIsDisplayMessageBox = FALSE;

							// 메세지 박스 감추기	
							m_pMessageBoxDlg->SendMessage(UM_DPS_DLG_MESSAGE_BOX_SHOWHIDE, SW_HIDE, NULL);

							// 시스템 플래그 설정
							m_stSystemStatus.bOnWaitForUser	= FALSE;	// 사용자 입력 대기 해제
							m_stSystemStatus.bOnBuzzer		= FALSE;	// 경고음 해제

							PROCESS.nCurrentStep = 3090;
							break;

		// 완료
		case	3090	:
							PROCESS.nCurrentStep = PROCESS.nReturn01Step;
							break;


		/////////////////////////////////////////////////////////////
		// 작업 정지 예약 ///////////////////////////////////////////
		case	STEP_STN_WAIT_STOP	:
										if (!m_stSystemStatus.bOnOperatingStopReservated) {

											PROCESS.bIsStopReservated	= FALSE;
											PROCESS.nCurrentStep		= PROCESS.nRecoveryStopStep;
										}

										break;


		/////////////////////////////////////////////////////////////
		// 오류 /////////////////////////////////////////////////////
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

											// 디버그 메세지
											SDebugMessage(TRUE, _T("[S%02d] ERROR PARTS"), nSTATION_NO);
											break;

		case	STEP_STN_ERROR_SYSTEM	:
											// 디버그 메세지
											SDebugMessage(TRUE, _T("[S%02d] ERROR SYSTEM"), nSTATION_NO);
											break;


		/////////////////////////////////////////////////////////////
		// 일시 정지 스텝 ///////////////////////////////////////////
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

		// 스텝 복구
		case	20100	:
							PROCESS.nCurrentStep	= PROCESS.nRecoveryStep;
							PROCESS.bOnPause		= FALSE;
							break;


		/////////////////////////////////////////////////////////////
		// 비상 정지 스텝 ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop)	{

									PROCESS.nRecoveryStep	= 0;
									PROCESS.nCurrentStep	= 20001;
								}

								break;


		/////////////////////////////////////////////////////////////
		// 장비 초기화 스텝 /////////////////////////////////////////
		case	STEP_MC_INIT	:
									PROCESS.nCurrentStep = 22010;
									break;

		case	22010	:
							// 공정 초기화
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
	// 운전 정지 체크 ///////////////////////////////////////////////
	CheckProcessOperatingStop(PROCESS);


	/////////////////////////////////////////////////////////////////
	// 일반 /////////////////////////////////////////////////////////
	CheckProcessGeneral(nSTATION_NO, PROCESS);


	/////////////////////////////////////////////////////////////////
	// 스텝 모니터링 ////////////////////////////////////////////////
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
// 프로세스 (파츠) : 공통 /////////////////////////////////////////////////////
PERROR_CODE_T CMainApp::ProcessCommonParts(void)
{
	return	NULL;
}


///////////////////////////////////////////////////////////////////////////////
// 프로세스 (파츠) : 공정 #01 - 검사 공정 (OS) ////////////////////////////////
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
	// 프로세스 데이터 초기화 ///////////////////////////////////////
	ProcessDataInitialize(PROCESS);


	/////////////////////////////////////////////////////////////////
	// 자동 운전 시작/정지 초기화 ///////////////////////////////////
	if (CheckProcessOperating(PROCESS) || m_SystemConfig.IsSimulationMode()) {
	
		ZeroMemory(pOnSCP_MoveParts, sizeof(BOOL) * nPARTS_COUNT);
	}


	/////////////////////////////////////////////////////////////////
	// 수동 제어 모드 ///////////////////////////////////////////////
	if (CheckProcessManualControlMode(nSTATION_NO, PROCESS)) {
	
		ZeroMemory(pOnSCP_MoveParts, sizeof(BOOL) * nPARTS_COUNT);
	}


	/////////////////////////////////////////////////////////////////
	// 비상/일시 정지 상태 //////////////////////////////////////////
	if (CheckProcessEmergencyStop(PROCESS))					return	NULL;
	if (CheckProcessOperatingPause(nSTATION_NO, PROCESS))	return	NULL;
	

	/////////////////////////////////////////////////////////////////
	// 스텝 프로세스 ////////////////////////////////////////////////
	switch (PROCESS.nCurrentStep) {

		case	0		:
							PROCESS.nCurrentStep = 10;
							break;


		/////////////////////////////////////////////////////////////
		// 인덱스 ///////////////////////////////////////////////////
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
		// 로딩 유닛 ////////////////////////////////////////////////

		// FWD
		case	1100	:
							if (LTimerInterLock.Verify()) {

								if (!GetDIStatus(DI_SENS_S01_LOADING_FWD)) {

									// 인터-록 체크
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

							// 실린더 타임아웃
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

									// 인터-록 체크
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

							// 실린더 타임아웃
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
		// 프로브 ///////////////////////////////////////////////////

		// ON
		case	2100	:
							if (LTimerInterLock.Verify()) {

								if (!GetDIStatus(DI_SENS_S01_PROBE_ON)) {

									// 인터-록 체크
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

							// 실린더 타임아웃
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

									// 인터-록 체크
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

							// 실린더 타임아웃
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
		// 프로브 가이드 ////////////////////////////////////////////

		// ON
		case	2200	:
							if (LTimerInterLock.Verify()) {

								if (m_SystemConfig.UseSystemOption(SOPT_ENABLE_PROBE_GUIDE_UNIT) && !GetDIStatus(DI_SENS_S01_PROBE_ON)) {

									// 인터-록 체크
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

							// 실린더 타임아웃
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

									// 인터-록 체크
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

							// 실린더 타임아웃
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
		// 제품 도어 열림 ///////////////////////////////////////////

		// UP
		case	3100	:
							if (LTimerInterLock.Verify()) {

								if (TRUE) {

									// 인터-록 체크
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

							// 실린더 타임아웃
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

									// 인터-록 체크
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

							// 실린더 타임아웃
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
		// 언로딩 ///////////////////////////////////////////////////
		case	6000	:
							if (LTimerInterLock.Verify()) {

								if (TRUE) {

									// 인터-록 체크
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

							// 실린더 타임아웃
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
		// 일시 정지 스텝 ///////////////////////////////////////////
		case	STEP_PAUSE	:
								if (m_stSystemStatus.bOnEmergencyStop) {

									PROCESS.nCurrentStep = STEP_EMG;
									break;
								}

								if (!m_stSystemStatus.bOnPause && !m_stSystemStatus.bOnAlarmSystem && !m_stSystemStatus.bOnAlarmStation[nSTATION_NO])		
									PROCESS.nCurrentStep = 20001;

								break;

		// 스텝 복구
		case	20001	:
							PROCESS.nCurrentStep	= PROCESS.nRecoveryStep;
							PROCESS.bOnPause		= FALSE;
							break;


		/////////////////////////////////////////////////////////////
		// 비상 정지 스텝 ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop)	{

									ZeroMemory(pOnSCP_MoveParts, sizeof(BOOL) * nPARTS_COUNT);

									PROCESS.nRecoveryStep	= 0;
									PROCESS.nCurrentStep	= STEP_PAUSE;
								}

								break;
	}


	/////////////////////////////////////////////////////////////////
	// 인터-록 오류 /////////////////////////////////////////////////
	if (PROCESS.bOnInterLock) {
	
		if (m_nTypeLanguage == LANGUAGE_KOR)	ErrorMessage(TRUE, _T("[S%02d] 인터-록 오류!"), nSTATION_NO);
		else									ErrorMessage(TRUE, _T("[S%02d] INTER-LOCK ERROR!"), nSTATION_NO);

		PROCESS.bOnInterLock = FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// 오류 발생 ////////////////////////////////////////////////////
	if (PROCESS.bOnError) {

		PROCESS.pstErrorCode = new (std::nothrow) ERROR_CODE_T;
		if (PROCESS.pstErrorCode)	*(PROCESS.pstErrorCode) = PROCESS.stErrorCode;

		if (!m_stSystemStatus.bOnOperating) {

			PROCESS.nCurrentStep = 0;
			m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
			ZeroMemory(pOnSCP_MoveParts, sizeof(BOOL) * nPARTS_COUNT);

		} else {

			// 복귀 스텝
			PROCESS.nCurrentStep = PROCESS.nRecoveryStep;

			// 공정 알람 설정
			m_stSystemStatus.bOnAlarmStation[nSTATION_NO] = TRUE;

			// 일시 정지
// 			m_stSystemStatus.bOnPause = TRUE;	
// 			if (m_pMainWnd && m_pMainWnd->GetSafeHwnd())
// 				m_pMainWnd->PostMessage(UM_MAIN_PAUSE);
		}
	}


	return	PROCESS.pstErrorCode;
}


///////////////////////////////////////////////////////////////////////////////
// 프로세스 (파츠) : 공정 #02 - 검사 공정 (SK) ////////////////////////////////
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
	// 프로세스 데이터 초기화 ///////////////////////////////////////
	ProcessDataInitialize(PROCESS);


	/////////////////////////////////////////////////////////////////
	// 자동 운전 시작/정지 초기화 ///////////////////////////////////
	if (CheckProcessOperating(PROCESS) || m_SystemConfig.IsSimulationMode()) {
	
		ZeroMemory(pOnSCP_MoveParts, sizeof(BOOL) * nPARTS_COUNT);
	}


	/////////////////////////////////////////////////////////////////
	// 수동 제어 모드 ///////////////////////////////////////////////
	if (CheckProcessManualControlMode(nSTATION_NO, PROCESS)) {
	
		ZeroMemory(pOnSCP_MoveParts, sizeof(BOOL) * nPARTS_COUNT);
	}


	/////////////////////////////////////////////////////////////////
	// 비상/일시 정지 상태 //////////////////////////////////////////
	if (CheckProcessEmergencyStop(PROCESS))					return	NULL;
	if (CheckProcessOperatingPause(nSTATION_NO, PROCESS))	return	NULL;
	

	/////////////////////////////////////////////////////////////////
	// 스텝 프로세스 ////////////////////////////////////////////////
	switch (PROCESS.nCurrentStep) {

		case	0		:
							PROCESS.nCurrentStep = 10;
							break;


		/////////////////////////////////////////////////////////////
		// 인덱스 ///////////////////////////////////////////////////
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
		// 제품 도어 누름 #1 ////////////////////////////////////////

		// UP
		case	1100	:
							if (LTimerInterLock.Verify()) {

								if (TRUE) {

									// 인터-록 체크
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

							// 실린더 타임아웃
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

									// 인터-록 체크
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

							// 실린더 타임아웃
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
		// 제품 도어 누름 #2 ////////////////////////////////////////

		// UP
		case	1200	:
							if (LTimerInterLock.Verify()) {

								if (TRUE) {

									// 인터-록 체크
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

							// 실린더 타임아웃
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

									// 인터-록 체크
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

							// 실린더 타임아웃
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
		// 제품 도어 누름 (A) ///////////////////////////////////////

		// UP
		case	1300	:
							if (LTimerInterLock.Verify()) {

								if (TRUE) {

									// 인터-록 체크
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

							// 실린더 타임아웃
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

									// 인터-록 체크
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

							// 실린더 타임아웃
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
		// 프로브 ///////////////////////////////////////////////////

		// ON
		case	2100	:
							if (LTimerInterLock.Verify()) {

								if (TRUE) {

									// 인터-록 체크
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

							// 실린더 타임아웃
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

									// 인터-록 체크
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

							// 실린더 타임아웃
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
		// 제품 도어 열림 ///////////////////////////////////////////

		// UP
		case	3100	:
							if (LTimerInterLock.Verify()) {

								if (TRUE) {

									// 인터-록 체크
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

							// 실린더 타임아웃
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

									// 인터-록 체크
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

							// 실린더 타임아웃
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
		// 언로딩 ///////////////////////////////////////////////////
		case	6000	:
							if (LTimerInterLock.Verify()) {

								if (TRUE) {

									// 인터-록 체크
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

							// 실린더 타임아웃
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
		// 일시 정지 스텝 ///////////////////////////////////////////
		case	STEP_PAUSE	:
								if (m_stSystemStatus.bOnEmergencyStop) {

									PROCESS.nCurrentStep = STEP_EMG;
									break;
								}

								if (!m_stSystemStatus.bOnPause && !m_stSystemStatus.bOnAlarmSystem && !m_stSystemStatus.bOnAlarmStation[nSTATION_NO])		
									PROCESS.nCurrentStep = 20001;

								break;

		// 스텝 복구
		case	20001	:
							PROCESS.nCurrentStep	= PROCESS.nRecoveryStep;
							PROCESS.bOnPause		= FALSE;
							break;


		/////////////////////////////////////////////////////////////
		// 비상 정지 스텝 ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop)	{

									ZeroMemory(pOnSCP_MoveParts, sizeof(BOOL) * nPARTS_COUNT);

									PROCESS.nRecoveryStep	= 0;
									PROCESS.nCurrentStep	= STEP_PAUSE;
								}

								break;
	}


	/////////////////////////////////////////////////////////////////
	// 인터-록 오류 /////////////////////////////////////////////////
	if (PROCESS.bOnInterLock) {
	
		if (m_nTypeLanguage == LANGUAGE_KOR)	ErrorMessage(TRUE, _T("[S%02d] 인터-록 오류!"), nSTATION_NO);
		else									ErrorMessage(TRUE, _T("[S%02d] INTER-LOCK ERROR!"), nSTATION_NO);

		PROCESS.bOnInterLock = FALSE;
	}


	/////////////////////////////////////////////////////////////////
	// 오류 발생 ////////////////////////////////////////////////////
	if (PROCESS.bOnError) {

		PROCESS.pstErrorCode = new (std::nothrow) ERROR_CODE_T;
		if (PROCESS.pstErrorCode)	*(PROCESS.pstErrorCode) = PROCESS.stErrorCode;

		if (!m_stSystemStatus.bOnOperating) {

			PROCESS.nCurrentStep = 0;
			m_stSystemStatus.bOnMP_Error[nSTATION_NO] = TRUE;
			ZeroMemory(pOnSCP_MoveParts, sizeof(BOOL) * nPARTS_COUNT);

		} else {

			// 복귀 스텝
			PROCESS.nCurrentStep = PROCESS.nRecoveryStep;

			// 공정 알람 설정
			m_stSystemStatus.bOnAlarmStation[nSTATION_NO] = TRUE;

			// 일시 정지
// 			m_stSystemStatus.bOnPause = TRUE;	
// 			if (m_pMainWnd && m_pMainWnd->GetSafeHwnd())
// 				m_pMainWnd->PostMessage(UM_MAIN_PAUSE);
		}
	}


	return	PROCESS.pstErrorCode;
}








///////////////////////////////////////////////////////////////////////////////////////////////////
// 기타 프로세스 //////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 프로세스 : 디바이스 (LOADCELL) /////////////////////////////////////////////
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
	// 프로세스 데이터 초기화 ///////////////////////////////////////
	ProcessDataInitialize(PROCESS);


	/////////////////////////////////////////////////////////////////
	// 스텝 프로세스 ////////////////////////////////////////////////
	switch (PROCESS.nCurrentStep) {

		case	0		:
							// LOADCELL 측정 대기 시간 설정
							LTimerProceed.Start(m_SystemConfig.GetDelaySystem(DLY_SYS_WAIT_LC_MEASUREMENT_START));

							// 통신 버퍼 초기화
							m_Comm[COMM_DEV_LCC_1].ClearBuffer();
							m_Comm[COMM_DEV_LCC_2].ClearBuffer();
							m_Comm[COMM_DEV_LCC_3].ClearBuffer();

							// 플래그 초기화
							nCurrentLoadCellNo	= LOADCELL_CH01;

							// 로드셀 데이터 초기화
							for (UINT nIndex = 0; nIndex < MAX_LOADCELL_CHANNEL_USE; nIndex++) {

								m_stSystemStatus.nStatusLoadCellData[nIndex]	= LCDT_STABLE;
								m_stSystemStatus.dblMeasurementLoadCell[nIndex]	= 0;
							
								bOnReceiveData[nIndex] = FALSE;
								LTimerTimeOut[nIndex].Start(m_SystemConfig.GetDelaySystem(DLY_SYS_TOUT_LOADCELL_DATA));
							}

							PROCESS.nCurrentStep = 110;
							break;

		// 로드셀 형식 구분
		case	110		:
							if (LTimerProceed.Verify()) {

								UINT	nTypeLoadCell	= m_SystemConfig.GetLoadCellType();

								if (nTypeLoadCell == LOADCELL_TYPE_STREAM)	
									PROCESS.nCurrentStep = 200;
							}

							break;


		/////////////////////////////////////////////////////////////
		// 로드셀 측정 (스트림 모드) ////////////////////////////////
		case	200		:
							if (!m_SystemConfig.UseSystemOption(SOPT_DISABLE_LOADCELL_01 + nCurrentLoadCellNo)) {

								if (m_stSystemStatus.nDeviceStatus[SD_DEV_LCC_1 + nCurrentLoadCellNo] == DS_NONE ||
									m_stSystemStatus.nDeviceStatus[SD_DEV_LCC_1 + nCurrentLoadCellNo] == DS_NORMAL ||
									m_stSystemStatus.nDeviceStatus[SD_DEV_LCC_1 + nCurrentLoadCellNo] == DS_CONNECT) {

									// 데이터 수신 체크
									if (bOnReceiveData[nCurrentLoadCellNo]) {
							
										bOnReceiveData[nCurrentLoadCellNo] = FALSE;
										LTimerTimeOut[nCurrentLoadCellNo].Start(m_SystemConfig.GetDelaySystem(DLY_SYS_TOUT_LOADCELL_DATA));

										// 피크 데이터 설정
										if (m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo] > m_stSystemStatus.dblPeakHoldDataLoadCell[nCurrentLoadCellNo])
											m_stSystemStatus.dblPeakHoldDataLoadCell[nCurrentLoadCellNo] = m_stSystemStatus.dblMeasurementLoadCell[nCurrentLoadCellNo];
									}

									// 타임 아웃
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
		// 일시 정지 스텝 ///////////////////////////////////////////
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

		// 스텝 복구
		case	20100	:
							PROCESS.nCurrentStep	= PROCESS.nRecoveryStep;
							PROCESS.bOnPause		= FALSE;
							break;


		/////////////////////////////////////////////////////////////
		// 비상 정지 스텝 ///////////////////////////////////////////
		case	STEP_EMG	:
								if (!m_stSystemStatus.bOnEmergencyStop)	{

									PROCESS.nRecoveryStep	= 0;
									PROCESS.nCurrentStep	= 20001;
								}

								break;
	}


	/////////////////////////////////////////////////////////////////
	// 로드셀 데이터 수신 ///////////////////////////////////////////
	for (UINT nLoadCellNo = 0; nLoadCellNo < MAX_LOADCELL_CHANNEL_USE; nLoadCellNo++) {
	
		while (m_Comm[COMM_DEV_LCC_1 + nLoadCellNo].ReadByte(&byReadByte)) {

			// 데이터 저장
			szRcvdPacket[nLoadCellNo][nRcvdPacketIndex[nLoadCellNo]++] = byReadByte;

			// 하나의 패킷이 완성되면 해석
			if (byReadByte == COMM_LF_F && szRcvdPacket[nLoadCellNo][nRcvdPacketIndex[nLoadCellNo] - 2] == COMM_CR_F) {
			
				USES_CONVERSION;

				szRcvdPacket[nLoadCellNo][nRcvdPacketIndex[nLoadCellNo] - 2] = '\0';
				m_stSystemStatus.nDeviceStatus[SD_DEV_LCC_1 + nLoadCellNo]   = DS_NORMAL;

				/////////////////////////////////////////////////////
				// 스트림 모드 //////////////////////////////////////
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

					// 플래그 설정
					bOnReceiveData[nLoadCellNo] = bIsCorrectData;

				/////////////////////////////////////////////////////
				// 커맨드 모드 //////////////////////////////////////
				} else {
				
					UINT	nID		= m_SystemConfig.GetLoadCellID(nLoadCellNo);
					UINT	nReadID	= 0;
					CHAR	szTemp[10];

					// ID 체크
					strncpy_s(szTemp, 10, szRcvdPacket[nLoadCellNo] + 2, 3);
					nReadID = atoi(szTemp);
					if (nReadID == nID) {
					
						m_stSystemStatus.dblPeakHoldDataLoadCell[nLoadCellNo]	= atof(szRcvdPacket[nLoadCellNo] + 6) * m_SystemConfig.GetGainLoadCellData(nLoadCellNo);
						m_stSystemStatus.bOnReceivedLoadCellData[nLoadCellNo]	= TRUE;
					}
				}

				// 패킷 초기화
				nRcvdPacketIndex[nLoadCellNo] = 0;
			}

			// 패킷 오버플로우 방지
			if (nRcvdPacketIndex[nLoadCellNo] >= COMM_PACKET_SIZE) {

				nRcvdPacketIndex[nLoadCellNo] = 0;
				break;
			}
		}
	}


	/////////////////////////////////////////////////////////////////
	// 일반 /////////////////////////////////////////////////////////
	CheckProcessGeneral(0, PROCESS);


	/////////////////////////////////////////////////////////////////
	// 스텝 모니터링 ////////////////////////////////////////////////
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
// 프로세스 : 라벨 프린터 /////////////////////////////////////////////////////
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
	// 바코드 프린터 연결 안됨 //////////////////////////////////////
	if (m_stSystemStatus.nDeviceStatus[SD_PRINT_1 + nBCP_NO] == DS_NONE || m_stSystemStatus.nDeviceStatus[SD_PRINT_1 + nBCP_NO] == DS_DISCONNECT)
		return	NULL;


	/////////////////////////////////////////////////////////////////
	// 변수 초기화 //////////////////////////////////////////////////
	ZeroMemory(&stErrorCode, sizeof(ERROR_CODE_T));


	/////////////////////////////////////////////////////////////////
	// 바코드 프린터 리셋 ///////////////////////////////////////////
	if (m_stSystemStatus.bOnResetLabelPrinter[nBCP_NO]) {

		// 패킷 전송
		nRcvdPacketIndex[nBCP_NO]	= 0;
		//m_Comm[COMM_PRINT].TransmitString(FALSE, _T("{WR|}"));

		// 리셋 타이머 설정
		LTimerStandby[nBCP_NO].Start(5000);

		m_stSystemStatus.bOnResetLabelPrinter[nBCP_NO] = FALSE;
		return	NULL;
	}


	/////////////////////////////////////////////////////////////////
	// 대기 타이머 체크 /////////////////////////////////////////////
	if (!LTimerStandby[nBCP_NO].Verify())	return	NULL;


	/////////////////////////////////////////////////////////////////
	// 스텝 프로세스 ////////////////////////////////////////////////
	switch (nCurrentStep[nBCP_NO]) {

		/////////////////////////////////////////////////////////////
		// 대기 상태 ////////////////////////////////////////////////
		case	0		:
							// 플래그 초기화
							bIsCheckStatus[nBCP_NO]	= FALSE;

							nCurrentStep[nBCP_NO] = 10;
							break;
								
		case	10		:
							if (m_stSystemStatus.bOnPrintLabel[nBCP_NO]) {

								// 초기화
								nPrintRetryCount[nBCP_NO]	= 0;
								nRetryCount[nBCP_NO]		= 0;

								nCurrentStep[nBCP_NO] = 100;
								break;
							}

							// 상태 체크
							if (LTimerInterval[nBCP_NO].Verify()) {
							
								bIsCheckStatus[nBCP_NO]	= TRUE;
								nCurrentStep[nBCP_NO]	= 100;
							}

							break;


		/////////////////////////////////////////////////////////////
		// 상태 체크 ////////////////////////////////////////////////

		// 바코드 프린터 상태 체크
		case	100		:
							if (LTimerSteady[nBCP_NO].Verify()) {

								// 프린터 상태 초기화
								ZeroMemory(&m_stSystemStatus.stPrintStatus[nBCP_NO], sizeof(PRINT_STATUS_T));

								// 패킷 전송
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
								
									// 상태 체크 간격 설정
									LTimerInterval[nBCP_NO].Start(m_SystemConfig.GetDelayControl(DLY_CTRL_INTV_READ_BCP_STATUS));

									nCurrentStep[nBCP_NO] = 0;
									break;
								}

								nCurrentStep[nBCP_NO]++;
								break;
							}

							// 타임 아웃
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

		// 바코드 프린터 상태 체크
		case	102		:
							{
								CString		strMsg			= _T("");
								BOOL		bOnErrorStatus	= FALSE;


								if (m_stSystemStatus.stPrintStatus[nBCP_NO].bIsPaperOut) {
									
									if (m_nTypeLanguage == LANGUAGE_KOR)	strMsg.Format(_T("용지가 없습니다."));
									else									strMsg.Format(_T("PAPER OUT"));

									bOnErrorStatus = TRUE;

								} else if (m_stSystemStatus.stPrintStatus[nBCP_NO].bIsRibbonOut) {
									
									if (m_nTypeLanguage == LANGUAGE_KOR)	strMsg.Format(_T("리본 오류"));
									else									strMsg.Format(_T("RIBBON OUT"));

									bOnErrorStatus = TRUE;

								} else if (m_stSystemStatus.stPrintStatus[nBCP_NO].bIsHeadUpPosition) {
									
									if (m_nTypeLanguage == LANGUAGE_KOR)	strMsg.Format(_T("헤드가 열려있습니다."));
									else									strMsg.Format(_T("HEAD UP POSITION"));

									bOnErrorStatus = TRUE;

								} else if (m_stSystemStatus.stPrintStatus[nBCP_NO].bIsPauseActive) {
									
									if (m_nTypeLanguage == LANGUAGE_KOR)	strMsg.Format(_T("일시 정지 상태입니다."));
									else									strMsg.Format(_T("PAUSE ACTIVE"));

									bOnErrorStatus = TRUE;
								
								} else if (m_stSystemStatus.stPrintStatus[nBCP_NO].bIsLabelWaiting) {
									
									if (m_nTypeLanguage == LANGUAGE_KOR)	strMsg.Format(_T("라벨이 이미 발행되어 있습니다."));
									else									strMsg.Format(_T("LABEL IS ALREADY ISSUED"));

									bOnErrorStatus = TRUE;
								}

								if (bOnErrorStatus) {

									// 메세지 출력
									ErrorMessage(TRUE, _T("[LABEL PRINTER #%d ERROR] %s"), nBCP_NO + 1, strMsg);

									// 메세지 박스 설정
									strMessageBox[nBCP_NO] = strMsg;

									nCurrentStep[nBCP_NO] = STEP_ERROR;
									break;
								}

								nCurrentStep[nBCP_NO] = 200;
							}

							break;


		/////////////////////////////////////////////////////////////
		// 바코드 출력 //////////////////////////////////////////////

		// 바코드 데이터 생성 및 출력
		case	200		:
							if (!m_strLabelFormat[nBCP_NO].IsEmpty()) {

								// 패킷 전송
								nRcvdPacketIndex[nBCP_NO]	= 0;
								nRetryCount[nBCP_NO]		= 0;
								pComm->ClearBuffer();
								pComm->TransmitString(FALSE, m_strLabelFormat[nBCP_NO]);

								// 발급 지연 시간 설정
								LTimerSteady[nBCP_NO].Start(m_SystemConfig.GetDelayControl(DLY_CTRL_WAIT_LABEL_ISSUE));

								// 발급 타임 아웃
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

		// 상태 수신 및 체크
		case	210		:
							// 프린터 상태 초기화
							ZeroMemory(&m_stSystemStatus.stPrintStatus[nBCP_NO], sizeof(PRINT_STATUS_T));
							nPrintRetryCount[nBCP_NO] = 0;

							// 패킷 전송
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

								// 프린터 상태 체크
								if (!m_stSystemStatus.stPrintStatus[nBCP_NO].bIsPaperOut && !m_stSystemStatus.stPrintStatus[nBCP_NO].bIsRibbonOut &&
									!m_stSystemStatus.stPrintStatus[nBCP_NO].bIsHeadUpPosition && !m_stSystemStatus.stPrintStatus[nBCP_NO].bIsPauseActive) {

										m_stSystemStatus.bOnPrintLabelResult[nBCP_NO] = TRUE;

										nCurrentStep[nBCP_NO] = 900;
										break;
								}

								// 발급 타임 아웃
								if (LTimerTimeOutIssue[nBCP_NO].Verify()) {

									if (m_nTypeLanguage == LANGUAGE_KOR)	ErrorMessage(TRUE, _T("[라벨 프린터 #%d 오류] 라벨 출력을 완료할 수 없습니다."), nBCP_NO + 1);
									else 									ErrorMessage(TRUE, _T("[LABEL PRINTER #%d ERROR] LABEL ISSUE FAILURE"), nBCP_NO + 1);

									nCurrentStep[nBCP_NO] = 800;
								}

								break;
							}

							// 타임 아웃
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
		// 오류 /////////////////////////////////////////////////////
		case	800		:
							// 프린터 리셋
							m_stSystemStatus.bOnResetLabelPrinter[nBCP_NO]	= TRUE;
							
							// 라벨 출력 결과 설정
							m_stSystemStatus.bOnPrintLabelResult[nBCP_NO]	= FALSE;

							// 비프음 2회 출력
							m_stSystemStatus.nBeepCount = 2;

							bOnRcvdPacket[nBCP_NO]	= FALSE;
							nRetryCount[nBCP_NO]	= 0;
							nCurrentStep[nBCP_NO]	= 900;
							break;


		/////////////////////////////////////////////////////////
		// 출력 완료 ////////////////////////////////////////////
		case	900		:
							m_stSystemStatus.bOnPrintLabel[nBCP_NO]	= FALSE;
							nCurrentStep[nBCP_NO] = 0;
							break;


		/////////////////////////////////////////////////////////////
		// 오류 메세지 //////////////////////////////////////////////
		case	STEP_ERROR	:
								nCurrentStep[nBCP_NO] = 90010;
								break;

		case	90010	:
							nCurrentStep[nBCP_NO] = 90020;
							break;

		// 메세지 박스 출력
		case	90020	:
							// 메세지 박스가 출력 상태 체크
							if (!m_stSystemStatus.bIsDisplayMessageBox) {
							
								m_stSystemStatus.bIsDisplayMessageBox = TRUE;

								nCurrentStep[nBCP_NO]++;
							}

							break;

		case	90021	:
							{
								// 시스템 플래그 설정
								m_stSystemStatus.nMessageBoxButtonCode	= MBOX_BCODE_NONE;	// 버튼 코드 초기화
								m_stSystemStatus.bOnBuzzer				= TRUE;				// 경고음 출력
								m_stSystemStatus.bOnWaitForUser			= TRUE;				// 사용자 입력 대기 설정

								// 메세지 박스 생성
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

								// 비프음 2회 출력
								m_stSystemStatus.nBeepCount = 2;

								SErrorMessage(TRUE, _T("[BCP] 메세지 박스를 생성할 수 없습니다."));
							}

							nCurrentStep[nBCP_NO] = 90090;
							break;

		case	90022	:
							if (m_stSystemStatus.nMessageBoxButtonCode != MBOX_BCODE_NONE) {
							
								// 버튼 0 : 재시도
								if (m_stSystemStatus.nMessageBoxButtonCode == MBOX_BCODE_0) {

									nCurrentStep[nBCP_NO] = 90090;
									break;
								}

								// 버튼 1 : 경고음 해제
								if (m_stSystemStatus.nMessageBoxButtonCode == MBOX_BCODE_1) {

									m_stSystemStatus.bOnBuzzer				= FALSE;			// 경고음 해제
									m_stSystemStatus.nMessageBoxButtonCode	= MBOX_BCODE_NONE;	// 버튼 코드 초기화
								}
							}

							// 메세지 박스가 종료될 경우
							if (!m_stSystemStatus.bIsDisplayMessageBox)
								nCurrentStep[nBCP_NO] = 90090;

							break;

		// 완료
		case	90090	:
							// 메세지 박스 출력 플래그 해제
							m_stSystemStatus.bIsDisplayMessageBox = FALSE;

							// 메세지 박스 감추기	
							m_pMessageBoxDlg->SendMessage(UM_DPS_DLG_MESSAGE_BOX_SHOWHIDE, SW_HIDE, NULL);

							// 시스템 플래그 설정
							m_stSystemStatus.bOnWaitForUser	= FALSE;	// 사용자 입력 대기 해제
							m_stSystemStatus.bOnBuzzer		= FALSE;	// 경고음 해제

							nCurrentStep[nBCP_NO] = 0;
							break;
	}


	/////////////////////////////////////////////////////////////////
	// 프린터 상태 수신 체크 ////////////////////////////////////////
	while (pComm->ReadByte(&byReadByte)) {

		// STX 체크
		if (byReadByte == COMM_STD_STX_F)
			nRcvdPacketIndex[nBCP_NO] = 0;

		// 데이터 저장
		szRcvdPacket[nBCP_NO][nRcvdPacketIndex[nBCP_NO]++] = byReadByte;

		// 하나의 패킷이 완성되면 해석
		if (byReadByte == 0x0A && szRcvdPacket[nBCP_NO][nRcvdPacketIndex[nBCP_NO] - 2] == 0x0D) {

			USES_CONVERSION;

			// 문자열 변환
			szRcvdPacket[nBCP_NO][0] = 0x20;
			szRcvdPacket[nBCP_NO][nRcvdPacketIndex[nBCP_NO] - 2] = '\0';

			// 장치 상태 체크
			m_stSystemStatus.nDeviceStatus[SD_PRINT_1 + nBCP_NO] = DS_NORMAL;

			// 프린트 상태 정보 버퍼 초기화
			nStatusIndex[nBCP_NO] = 0;
			ZeroMemory(szStatusBuffer[nBCP_NO], BCP_STATUS_STRING1_LEN * BCP_STATUS_INFO_LEN);

			// 토큰 분리
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

			// 패킷 수신 플래그 설정
			bOnRcvdPacket[nBCP_NO] = bResult;

			// 패킷 초기화
			nRcvdPacketIndex[nBCP_NO] = 0;
		}

		// 패킷 오버플로우 방지
		if (nRcvdPacketIndex[nBCP_NO] >= COMM_PACKET_SIZE) {
			
			nRcvdPacketIndex[nBCP_NO] = 0;
			break;
		}
	}


	/////////////////////////////////////////////////////////////////
	// 오류 발생 ////////////////////////////////////////////////////
	if (bOnError) {

		pstErrorCode = new ERROR_CODE_T;
		if (pstErrorCode)	*pstErrorCode = stErrorCode;

		// 운전 중이면,
		if (m_stSystemStatus.bOnOperating) {

			// 복귀 스텝
			nCurrentStep[nBCP_NO] = nRecoveryStep[nBCP_NO];
		
		} else {

			m_stSystemStatus.bOnPrintLabel[nBCP_NO] = FALSE;
			nCurrentStep[nBCP_NO] = 0;
		}
	}


	return	pstErrorCode;
}


///////////////////////////////////////////////////////////////////////////////
// 프로세스 : 바코드 스캔 /////////////////////////////////////////////////////
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
	// 바코드 데이터 수신 ///////////////////////////////////////////
	while (m_Comm[COMM_SCAN_1 + nCurrentScanIndex].ReadByte(&byRcvdPacket)) {

		// 데이터 저장
		szRcvdPacket[nCurrentScanIndex][nRcvdPacketIndex[nCurrentScanIndex]++]	= byRcvdPacket;

		// 하나의 패킷이 완성되면 해석
		if (byRcvdPacket == 0x0D/* || byRcvdPacket == 0x0A*/) {

			// 바코드 설정
			szRcvdPacket[nCurrentScanIndex][nRcvdPacketIndex[nCurrentScanIndex] - 1] = '\0';
			CString	strReadCode(szRcvdPacket[nCurrentScanIndex]);
			//strReadCode.Remove(0x20);
			strReadCode.Remove(0x0D);
			strReadCode.Remove(0x0A);
			strReadCode = strReadCode.TrimLeft();
			strReadCode = strReadCode.TrimRight();
					
			// 바코드 설정
			if (strReadCode.GetLength() < MAX_STRINPUT_S) {
			
				SetBarcodeInfo(nCurrentScanIndex, strReadCode);
				MessageWindow(cDEBUG, _T("[%d] Barcode Scanned! [%s]"), nCurrentScanIndex, GetBarcodeInfo(nCurrentScanIndex));
				NormalMessage(TRUE, _T("BARCODE SCAN [%02d] = %s"), nCurrentScanIndex, GetBarcodeInfo(nCurrentScanIndex));

				// 자동 운전 중이면,
				if (m_stSystemStatus.bOnOperating && (nCurrentScanIndex == BCS_INPUT_1 || nCurrentScanIndex == BCS_INPUT_2)) {

					bOnUpdateUI				= TRUE;
					stParamUI.nUpdateID		= UI_PRODUCT_CODE_IN;
					stParamUI.nStationNo	= STATION_1;
					stParamUI.stProductCodeInfo.nStatusCodeInput	= BCD_SCAN_INPUT;
					_tcscpy_s(stParamUI.stProductCodeInfo.szCodeInput, MAX_STRINPUT_L, strReadCode);
				}
			}

			// 패킷 초기화
			nRcvdPacketIndex[nCurrentScanIndex]	= 0;
		}

		// 패킷 오버플로우 방지
		if (nRcvdPacketIndex[nCurrentScanIndex] >= COMM_PACKET_SIZE) {

			nRcvdPacketIndex[nCurrentScanIndex] = 0;
			break;
		}
	}

	if (++nCurrentScanIndex >= MAX_BCD_SCAN)	
		nCurrentScanIndex = 0;


	/////////////////////////////////////////////////////////////////
	// 업데이트 UI //////////////////////////////////////////////////
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
// 프로세스 : CAN 통신 ////////////////////////////////////////////////////////
void CMainApp::ProcessDeviceCAN(void)
{
	static	PCAN_PACKET_T			stPacket;
	static	LTimerHiresMsec			LTimerInterval[MAX_CAN_MESSAGE];
	

	/////////////////////////////////////////////////////////////////
	// CAN 메세지 전송 //////////////////////////////////////////////
	for (UINT nIndex = CID_BMS22; nIndex < MAX_CAN_MESSAGE; nIndex++) {
	
		if (m_stSystemStatus.bCAN_EnableTransmitData[nIndex] && LTimerInterval[nIndex].Verify()) {
		
			/////////////////////////////////////////////////////////
			// 패킷 생성 ////////////////////////////////////////////
			stPacket.stMessage.ID		= m_stCAN_TransmitData[nIndex].nCAN_ID;
			stPacket.stMessage.DLC		= m_stCAN_TransmitData[nIndex].nLength;
			stPacket.stMessage.MSGTYPE	= PCAN_MESSAGE_STANDARD;
			for (UINT nDataNo = 0; nDataNo < MAX_CAN_MSG_BYTE; nDataNo++)
				stPacket.stMessage.DATA[nDataNo] = m_stCAN_TransmitData[nIndex].abData[nDataNo];


			/////////////////////////////////////////////////////////
			// 패킷 전송 ////////////////////////////////////////////
			m_devCAN.SendPacket(stPacket);


			/////////////////////////////////////////////////////////
			// 타이머 설정 //////////////////////////////////////////
			LTimerInterval[nIndex].Start(m_stSystemStatus.nCAN_TransmitTimeInterval[nIndex]);
		}
	}
}







///////////////////////////////////////////////////////////////////////////////////////////////////
// 작업 프로세스 체크 /////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 공정 프로세스 데이터 초기화 ////////////////////////////////////////////////
void CMainApp::StationProcessDataInitialize(UINT nSTATION_NO, UINT nSTATION_SUB_NO, PROCESS_CTRL_T& PROCESS)
{
	/////////////////////////////////////////////////////////////////
	// 시스템 플래그 초기화 /////////////////////////////////////////
	m_stSystemStatus.bOnAlarmStation[nSTATION_NO]	= FALSE;
	m_stSystemStatus.bOnMP_Error[nSTATION_NO]		= FALSE;


	/////////////////////////////////////////////////////////////////
	// 공정 플래그 초기화 ///////////////////////////////////////////
	m_stSystemStatus.bOnStationInitializeResult[nSTATION_NO][nSTATION_SUB_NO]	= TRUE;
	m_stSystemStatus.bOnStationProcessConveyor[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;
	m_stSystemStatus.bOnStationProcessStandby[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;
	m_stSystemStatus.bOnStationProcessRequest[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;
	m_stSystemStatus.bOnStationProcessOutput[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;
	m_stSystemStatus.bOnStationProcessComplete[nSTATION_NO][nSTATION_SUB_NO]	= FALSE;
	m_stSystemStatus.bIsStationProcessLock[nSTATION_NO][nSTATION_SUB_NO]		= FALSE;
	m_stSystemStatus.nStationProcessOption[nSTATION_NO][nSTATION_SUB_NO]		= STN_PROC_OPT_NONE;


	/////////////////////////////////////////////////////////////////
	// 작업 플래그 초기화 ///////////////////////////////////////////
	m_stSystemStatus.bOnUserWarning[nSTATION_NO]		= FALSE;
	m_stSystemStatus.bOnUserSafety[nSTATION_NO]			= FALSE;
	m_stSystemStatus.bOnUserBuzzer[nSTATION_NO]			= FALSE;
	m_stSystemStatus.bOnUserLamp1[nSTATION_NO]			= FALSE;
	m_stSystemStatus.bOnUserLamp2[nSTATION_NO]			= FALSE;
	m_stSystemStatus.nCurrentWorkMessage[nSTATION_NO]	= WMSG_NONE;


	/////////////////////////////////////////////////////////////////
	// 프로세스 데이터 초기화 ///////////////////////////////////////
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
// 프로세스 데이터 초기화 /////////////////////////////////////////////////////
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
// 일반 ///////////////////////////////////////////////////////////////////////
BOOL CMainApp::CheckProcessGeneral(UINT nSTATION_NO, PROCESS_CTRL_T& PROCESS)
{
	BOOL	bResult	= FALSE;


	/////////////////////////////////////////////////////////////////
	// 업데이트 UI //////////////////////////////////////////////////
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
	// 오류 발생 ////////////////////////////////////////////////////
	if (PROCESS.bOnError) {

		PROCESS.pstErrorCode = new ERROR_CODE_T;
		if (PROCESS.pstErrorCode)	*(PROCESS.pstErrorCode) = PROCESS.stErrorCode;

		// 시스템 알람 설정
		m_stSystemStatus.bOnAlarmSystem = PROCESS.stErrorCode.bOnAlarmSystem;

		// 복귀 스텝
		PROCESS.nCurrentStep = PROCESS.nRecoveryStep;

		// 시스템 알람일 경우 일시 정지
		if (m_stSystemStatus.bOnAlarmSystem) {
		
			if (m_stSystemStatus.bOnOperating) {

				m_stSystemStatus.bOnPause = TRUE;

				if (m_pMainWnd && m_pMainWnd->GetSafeHwnd())
					m_pMainWnd->SendMessage(UM_MAIN_PAUSE);
			}
		
		} else {
		
			// 공정 알람 설정
			m_stSystemStatus.bOnAlarmStation[nSTATION_NO] = TRUE;
		}

		bResult = TRUE;
	}


	return	bResult;
}


///////////////////////////////////////////////////////////////////////////////
// 자동 운전 체크 /////////////////////////////////////////////////////////////
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
// 일시 정지 체크 /////////////////////////////////////////////////////////////
BOOL CMainApp::CheckProcessOperatingPause(UINT nSTATION_NO, PROCESS_CTRL_T& PROCESS)
{
	BOOL	bResult	= FALSE;


	/////////////////////////////////////////////////////////////////
	// 수동 모드일 경우 /////////////////////////////////////////////
	if (m_stSystemStatus.bIsManualControl[nSTATION_NO])
		return	bResult;


	/////////////////////////////////////////////////////////////////
	// 일시 정지 체크 ///////////////////////////////////////////////
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
// 운전 정지 체크 /////////////////////////////////////////////////////////////
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
// 정지 예약 체크 /////////////////////////////////////////////////////////////
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
// 수동 모드 체크 /////////////////////////////////////////////////////////////
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
// 장비 초기화 체크 ///////////////////////////////////////////////////////////
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
// 비상 정지 체크 /////////////////////////////////////////////////////////////
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
// 스레드 : 메인 //////////////////////////////////////////////////////////////////////////////////
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
	// 스레드 루프 //////////////////////////////////////////////////
	while (TRUE) {


		/////////////////////////////////////////////////////////////
		// 스레드 스위칭 ////////////////////////////////////////////
		if (--nThreadCount == 0) {

			Sleep(1);
			nThreadCount = THREAD_COUNT_MAIN;
		}


		/////////////////////////////////////////////////////////////
		// DIO 모니터 업데이트 //////////////////////////////////////
		if (LTimerUpdateDIO.Verify()) {
		
			if (pMainApp->m_pDIOMonitorDlg && (pMainApp->m_pDIOMonitorDlg)->GetSafeHwnd()) {
			
				(pMainApp->m_pDIOMonitorDlg)->PostMessage(UM_DIO_MONITOR_V3_UPDATE);
				LTimerUpdateDIO.Start(100);
			}
		}


		/////////////////////////////////////////////////////////////
		// 스레드 종료 체크 /////////////////////////////////////////
		pMainApp->m_csExitThread[THREAD_MAIN].Lock();
		if (pMainApp->m_bExitThread[THREAD_MAIN]) {

			pMainApp->m_csExitThread[THREAD_MAIN].Unlock();
			break;
		}

		pMainApp->m_csExitThread[THREAD_MAIN].Unlock();


		/////////////////////////////////////////////////////////////
		// 메인 스레드 플래그 체크 //////////////////////////////////
		if (!pstSystemStatus->bOnSysMainThreadStart)	continue;


		/////////////////////////////////////////////////////////////
		// 스텝 프로세스 ////////////////////////////////////////////
		switch (nCurrentStep) {

			/////////////////////////////////////////////////////////
			// 기본 프로세스 : 장비 초기화 //////////////////////////
			case	100		:
								pstErrorCode = pMainApp->ProcessMachineInit();
								nCurrentStep = 1000;
								break;


			/////////////////////////////////////////////////////////
			// 메인 프로세스 ////////////////////////////////////////
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
			// 공정 프로세스 ////////////////////////////////////////
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
			// 기타 프로세스 ////////////////////////////////////////
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
			// 모션 프로세스 ////////////////////////////////////////
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
		// 시스템 프로세스 //////////////////////////////////////////


		/////////////////////////////////////////////////////////////
		// 오류 발생 ////////////////////////////////////////////////
		if (pstErrorCode) {

			// 알람 이력 다이얼로그에 메세지 전송
			if (pMainApp->m_pSysHistoryDlg)		(pMainApp->m_pSysHistoryDlg)->SendMessage(UM_HISTORY_ON_ERROR, (WPARAM)pstErrorCode);

			// 오류 코드 초기화
			pstErrorCode	= NULL;
		}
	}


	return	0;
}







///////////////////////////////////////////////////////////////////////////////////////////////////
// 스레드 : 시스템 ////////////////////////////////////////////////////////////////////////////////
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
	// 스레드 루프 //////////////////////////////////////////////////
	while (TRUE) {


		/////////////////////////////////////////////////////////////
		// Context Switching ////////////////////////////////////////
		if (--nThreadCount == 0) {

			Sleep(1);
			nThreadCount = THREAD_COUNT_SYSTEM;
		}


		/////////////////////////////////////////////////////////////
		// 스레드 종료 체크 /////////////////////////////////////////
		pMainApp->m_csExitThread[nThreadID].Lock();
		if (pMainApp->m_bExitThread[nThreadID]) {

			pMainApp->m_csExitThread[nThreadID].Unlock();
			break;
		}

		pMainApp->m_csExitThread[nThreadID].Unlock();


		/////////////////////////////////////////////////////////////
		// 스텝 프로세스 ////////////////////////////////////////////
		switch (nCurrentStep) {

			case	100		:
								nCurrentStep = 1000;
								break;


			/////////////////////////////////////////////////////////
			// 시스템 프로세스 //////////////////////////////////////
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
		// 시스템 프로세스 //////////////////////////////////////////


		/////////////////////////////////////////////////////////////
		// 기타 프로세스 ////////////////////////////////////////////
		pMainApp->ProcessDeviceCAN();


		/////////////////////////////////////////////////////////////
		// 오류 발생 ////////////////////////////////////////////////
		if (pstErrorCode) {

			// 알람 이력 다이얼로그에 메세지 전송
			if (pMainApp->m_pSysHistoryDlg)		(pMainApp->m_pSysHistoryDlg)->SendMessage(UM_HISTORY_ON_ERROR, (WPARAM)pstErrorCode);

			// 오류 코드 초기화
			pstErrorCode	= NULL;
		}
	}


	return	0;
}






///////////////////////////////////////////////////////////////////////////////////////////////////
// 스레드 : 서브 //////////////////////////////////////////////////////////////////////////////////
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
	// 스레드 루프 //////////////////////////////////////////////////
	while (TRUE) {


		/////////////////////////////////////////////////////////////
		// Context Switching ////////////////////////////////////////
		if (--nThreadCount == 0) {

			Sleep(1);
			nThreadCount = THREAD_COUNT_SUB;
		}


		/////////////////////////////////////////////////////////////
		// 스레드 종료 체크 /////////////////////////////////////////
		pMainApp->m_csExitThread[nThreadID].Lock();
		if (pMainApp->m_bExitThread[nThreadID]) {

			pMainApp->m_csExitThread[nThreadID].Unlock();
			break;
		}

		pMainApp->m_csExitThread[nThreadID].Unlock();


		/////////////////////////////////////////////////////////////
		// 스텝 프로세스 ////////////////////////////////////////////
		switch (nCurrentStep) {

			// ...
			case	100		:
								nCurrentStep = 200;
								break;

			// 프로세스 : 비전 검사
			case	200		:
								pstErrorCode = pMainApp->ProcessMainWorkVision();
								nCurrentStep = 100;
								break;
		}


		/////////////////////////////////////////////////////////////
		// 오류 발생 ////////////////////////////////////////////////
		if (pstErrorCode) {

			// 알람 이력 다이얼로그에 메세지 전송
			if (pMainApp->m_pSysHistoryDlg)		(pMainApp->m_pSysHistoryDlg)->SendMessage(UM_HISTORY_ON_ERROR, (WPARAM)pstErrorCode);

			// 오류 코드 초기화
			pstErrorCode	= NULL;
		}
	}


	/////////////////////////////////////////////////////////////////
	// 파라미터 제거 ////////////////////////////////////////////////
	delete	pstParam;


	return	0;
}






///////////////////////////////////////////////////////////////////////////////////////////////////
// 스레드 : 데이터 베이스 /////////////////////////////////////////////////////////////////////////
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
	// 스레드 루프 //////////////////////////////////////////////////
	while (TRUE) {


		/////////////////////////////////////////////////////////////
		// Context Switching ////////////////////////////////////////
		if (--nThreadCount == 0) {

			Sleep(1);
			nThreadCount = THREAD_COUNT_SYSTEM;
		}


		/////////////////////////////////////////////////////////////
		// 스레드 종료 체크 /////////////////////////////////////////
		pMainApp->m_csExitThread[nThreadID].Lock();
		if (pMainApp->m_bExitThread[nThreadID]) {

			pMainApp->m_csExitThread[nThreadID].Unlock();
			break;
		}

		pMainApp->m_csExitThread[nThreadID].Unlock();


		/////////////////////////////////////////////////////////////
		// 스텝 프로세스 ////////////////////////////////////////////
		switch (nCurrentStep) {
		
			case	0		:
								break;
		}


		/////////////////////////////////////////////////////////////
		// 오류 발생 ////////////////////////////////////////////////
		if (pstErrorCode) {

			// 알람 이력 다이얼로그에 메세지 전송
			if (pMainApp->m_pSysHistoryDlg)		(pMainApp->m_pSysHistoryDlg)->SendMessage(UM_HISTORY_ON_ERROR, (WPARAM)pstErrorCode);

			// 오류 코드 초기화
			pstErrorCode	= NULL;
		}
	}


	return	0;
}
