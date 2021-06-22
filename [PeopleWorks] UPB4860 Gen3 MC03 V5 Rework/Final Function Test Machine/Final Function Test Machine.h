
///////////////////////////////////////////////////////////////////////////////////////////////////
//																								 //
// Project			:	OS EV CDM Final Function Test Machine									 //
// Custommer		:	DongAh																	 //
// IDE				:	Microsoft Visual Studio 2013											 //
// Created Date		:	2018. 02. 27.															 //
// Modified Date	:	2019. 01. 26.															 //
// Programmer		:	DiMPLe(TM)																 //
//																								 //
// Final Function Test Machine.h																 //
//																								 //
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __AFXWIN_H__
#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif





///////////////////////////////////////////////////////////////////////////////////////////////////
// Includes ///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "Resource.h"				// 리소스 파일







///////////////////////////////////////////////////////////////////////////////////////////////////
// CMainApp 클래스 ////////////////////////////////////////////////////////////////////////////////
class CMainApp : public CWinApp
{

///////////////////////////////////////////////////////////////////////////////
// 프로그램 공용 //////////////////////////////////////////////////////////////
public:
	CDpsLibInterface			m_LibInterface;
	CDpsMessageBox				m_MessageBox;

	CDebugMonitorDlg*			m_pDebugMonitorDlg;
	CDpsDIOMonitorV3Dlg*		m_pDIOMonitorDlg;
	CMessageBoxDlg*				m_pMessageBoxDlg;
	CSysDisplayDlg*				m_pSysDisplayDlg;
	CSysMonitorDlg*				m_pSysMonitorDlg;
	CSysHistoryDlg*				m_pSysHistoryDlg;
	CMCPSubPageDlg*				m_pMCPSubPageDlg[MAX_MCP_SUB_PAGE];

	CDpsSysStateMonitorWnd*		m_pSysStateMonitorWnd;
	CDpsProductionV2Wnd*		m_pProductionWnd;
	CDpsWorkInfoWnd*			m_pWorkInfoWnd;
	CDpsTimerWnd*				m_pTimerWnd;
	CDpsTimerWnd*				m_pTactTimerWndOverView;
	CDpsTimerWnd*				m_pTactTimerWnd[MAX_STATION];
	CDpsImageViewWnd*			m_pImageViewWnd;

	CMreDIOCtrl*				m_pDIOCtrl[MAX_DIO_CTRL];
	CComm						m_Comm[MAX_COMM];
	CDpsPCAN					m_devCAN;
	CDpsFlukeDMM				m_devDMM;
	CDpsODAPower				m_devPOWER;
	
	SYSTEMTIME					m_stTimeAppStart;											// 프로그램 시작 시간
	UINT						m_nTypeLanguage;											// 언어 형식
	UINT						m_nTypeMachine;												// 장비 형식

public:
	CWnd*						GetMainWnd(void)											{ return m_pMainWnd; }
	CDpsLibInterface*			GetDpsLibInterface(void)									{ return &m_LibInterface; }
	CComm*						GetComm(UINT nCommID)										{ return &m_Comm[nCommID]; }
	CMreDIOCtrl*				GetDIOCtrl(UINT nDIO_NO)									{ return m_pDIOCtrl[nDIO_NO]; }
	SYSTEMTIME					GetAppStartTime(void)										{ return m_stTimeAppStart; }

	void						SetTypeLanguage(UINT nTypeLanguage)							{ m_nTypeLanguage = nTypeLanguage; }

public:
	BOOL						DPS_InitApplication(void);
	void						DPS_ExitApplication(void);

	BOOL						CheckValidLicense(BOOL bOnPopupMessage = TRUE);
	BOOL						ConnectComm(BOOL bConn);
	BOOL						IsSystemReady(void);

public:
	void						SetDOStatus(UINT nSwitch, UINT nPort);
	BOOL						GetDOStatus(UINT nPort);
	BOOL						GetDIStatus(UINT nPort);

public:
	BOOL						TestMessage(BOOL bViewDate, LPCTSTR lpszFormat,...);		// 시스템 메세지
	BOOL						TestMessageL(BOOL bViewDate, LPCTSTR lpszFormat,...);
	BOOL						ErrorMessage(BOOL bViewDate, LPCTSTR lpszFormat,...);
	BOOL						SErrorMessage(BOOL bViewDate, LPCTSTR lpszFormat,...);
	BOOL						SDebugMessage(BOOL bViewDate, LPCTSTR lpszFormat,...);
	BOOL						NormalMessage(BOOL bViewDate, LPCTSTR lpszFormat,...);
	BOOL						NormalMessageL(BOOL bViewDate, LPCTSTR lpszFormat,...);

	BOOL						MessageWindow(COLORREF clrColor, LPCTSTR lpszFormat,...);	// 디버그 메세지


///////////////////////////////////////////////////////////////////////////////
// 시뮬래이션 /////////////////////////////////////////////////////////////////






///////////////////////////////////////////////////////////////////////////////
// 모델 정보 //////////////////////////////////////////////////////////////////
protected:
	CDpsModelProfileEx			m_ModelProfile;

public:
	CDpsModelProfileEx*			GetModelProfile(void)											{ return &m_ModelProfile; }
	

///////////////////////////////////////////////////////////////////////////////
// 작업 상태 //////////////////////////////////////////////////////////////////
protected:
	WORK_STATUS_T				m_stWorkStatus[MAX_STATION];
	WORK_SUB_COUNT_T			m_stWorkSubCounter;

	CString						m_strCurrentProductCode[MAX_STATION];
	CString						m_strBarcodeInfo[MAX_BCD_SCAN];
	CString						m_strLabelFormat[MAX_BARCODE_PRINTER];

	MACHINE_SHARED_INFO_T		m_stMachineSharedInfo;
	CDpsStringArray				m_listProductCodeNG;

	CArray	<FUNC_TEST_DATA_T, FUNC_TEST_DATA_T&>		m_arrFuncTestData;
	CArray	<VISION_TEST_DATA_T, VISION_TEST_DATA_T&>	m_arrVisionTestData[MAX_TEST_SHEET];
	CArray	<CONTI_MEAS_DATA_T, CONTI_MEAS_DATA_T&>		m_arrContiMeasData;

	CArray	<BCP_GRAPHIC_T, BCP_GRAPHIC_T>				m_arrBCPGraphicList;
	CArray	<BCP_IMAGE_T, BCP_IMAGE_T>					m_arrBCPImageList;

public:
	BOOL						InitWorkStatus(UINT nStationNo);
	BOOL						InitVisionTest(void);

	BOOL						CreateWorkResultDirectory(UINT nStationNo, BOOL bIsMasterProduct = FALSE);
	BOOL						SaveWorkSheet01(BOOL bIsMasterProduct = FALSE);
	BOOL						SaveWorkSheet01T(BOOL bIsMasterProduct = FALSE);
	BOOL						SaveWorkSheetERP_01(BOOL bIsMasterProduct = FALSE);
	BOOL						SaveVisionSheet(UINT nTestItemNo, UINT nTestPointNo, VISION_TEST_DATA_T& stVisionTestData, UINT nInspectionCount);
	BOOL						SaveResultData01(BOOL bIsMasterProduct = FALSE);

	BOOL						SetUserMessage(UINT nUserMessageID);
	void						RestoreUserMessage(void)										{ m_stSystemStatus.nCurrentUserMessage = m_stSystemStatus.nPreviousUserMessage; }
	void						ClearUserMessage(void)											{ m_stSystemStatus.nCurrentUserMessage = m_stSystemStatus.nPreviousUserMessage = UMSG_NONE; }

public:
	PWORK_STATUS_T				GetWorkStatus(UINT nStationNo)									{ return &m_stWorkStatus[nStationNo]; }
	PWORK_SUB_COUNT_T			GetWorkSubCounter(void)											{ return &m_stWorkSubCounter; }
	FUNC_TEST_DATA_T			GetFuncTestData(UINT nIndex)									{ return m_arrFuncTestData.GetAt(nIndex); }
	BCP_GRAPHIC_T&				GetPrintGraphics(UINT nIndex)									{ return m_arrBCPGraphicList.GetAt(nIndex); }
	BCP_IMAGE_T&				GetPrintImages(UINT nIndex)										{ return m_arrBCPImageList.GetAt(nIndex); }

	VISION_TEST_DATA_T&			GetVisionTestData(UINT nTestItemNo, UINT nIndex)				{ return m_arrVisionTestData[nTestItemNo].GetAt(nIndex); }
	UINT						GetVisionTestDataCount(UINT nTestItemNo)						{ return m_arrVisionTestData[nTestItemNo].GetCount(); }

	void						SetTrigBarcode(UINT nID, BOOL bOnActivate = TRUE);
	void						ClearBarcodeInfo(UINT nID)										{ m_strBarcodeInfo[nID].Empty(); }
	void						SetBarcodeInfo(UINT nID, const CString& strBarcode)				{ m_strBarcodeInfo[nID] = strBarcode; }
	CString						GetBarcodeInfo(UINT nID)										{ return m_strBarcodeInfo[nID]; }

	void						ClearCurrentProductCode(UINT nStationNo)									{ m_strCurrentProductCode[nStationNo].Empty(); }
	void						SetCurrentProductCode(UINT nStationNo, const CString& strProductCode)		{ m_strCurrentProductCode[nStationNo] = strProductCode; }
	CString						GetCurrentProductCode(UINT nStationNo)										{ return m_strCurrentProductCode[nStationNo]; }

	BOOL						CheckProductCodeDuplicated(const CString& strProductCode, UINT nDIR_ID);
	BOOL						DeleteProductCodeFile(const CString& strProductCode, UINT nDIR_ID);
	BOOL						SaveProductCodeFile(PRODUCT_CODE_INFO_T& stProductCodeInfo, UINT nDIR_ID, BOOL bOnAdvanced = TRUE);
	BOOL						LoadProductCodeFile(const CString& strProductCode, PRODUCT_CODE_INFO_T& stProductCodeInfo, UINT nDIR_ID);
	BOOL						CleanInformationFile(UINT nDIR_ID);
	BOOL						CleanInformationFile(const CString& strPath);

	CString						GetLabelFormat(UINT nBCP_NO)									{ return m_strLabelFormat[nBCP_NO]; }
	BOOL						CheckMasterTest(void);
	CString						GetLOTDateCode(SYSTEMTIME stTime);
	BOOL						CreateLabelFormat(UINT nBCP_NO, LABEL_PRINT_INFO_T& stLabelPrintInfo, UINT nPrintQuantity = 1, UINT nRetIndex = 0, CString* pStrRetValue = NULL, UINT nCustomSerialNo = 0, PBCP_FIXED_FIELD_INFO_T pstFixedFieldData = NULL);
	UINT						LoadZebraGraphics(void);
	UINT						LoadZebraImages(void);	
	BOOL						TransmitZebraGraphics(UINT nBCP_NO);
	BOOL						TransmitZebraImages(UINT nBCP_NO);
	
	BOOL						SaveWorkSubCounter(void);
	BOOL						LoadWorkSubCounter(void);


///////////////////////////////////////////////////////////////////////////////
// 작업 프로시저 //////////////////////////////////////////////////////////////
protected:
	TPRD_HEADER_T				m_stTestProcedureHeader;
	PTPRD_DATA_T				m_pstTestProcedureData;

	VPRD_HEADER_T				m_stVisionProcedureHeader;
	PVPRD_DATA_T				m_pstVisionProcedureData;

	CDpsStringArray				m_strSelectProcedureWorkSheet;
	CDpsStringArray				m_strSelectProcedureVisionSheet;

public:
	BOOL						LoadTestProcedure(void);
	BOOL						LoadTestProcedure(const CString& strProcedureFile, TPRD_HEADER_T& stHeader, PTPRD_DATA_T* pstData = NULL);
	BOOL						SaveTestProcedure(const CString& strProcedureFile, TPRD_HEADER_T& stHeader, PTPRD_DATA_T pstData = NULL);

	BOOL						LoadVisionProcedure(UINT nTestItemNo);
	BOOL						LoadVisionProcedure(const CString& strProcedureFile, VPRD_HEADER_T& stHeader, PVPRD_DATA_T* pstData = NULL);
	BOOL						SaveVisionProcedure(const CString& strProcedureFile, VPRD_HEADER_T& stHeader, PVPRD_DATA_T pstData = NULL);

	void						ClearSelectProcedureWorkSheet(void)								{ m_strSelectProcedureWorkSheet.RemoveAll(); }
	void						AddSelectProcedureWorkSheet(const CString& strValue)			{ m_strSelectProcedureWorkSheet.Add(strValue); }
	CString						GetSelectProcedureWorkSheet(UINT nIndex)						{ return m_strSelectProcedureWorkSheet.GetAt(nIndex); }
	UINT						GetSelectProcedureWorkSheetCount(void)							{ return (UINT)m_strSelectProcedureWorkSheet.GetCount(); }

	void						ClearSelectProcedureVisionSheet(void)							{ m_strSelectProcedureVisionSheet.RemoveAll(); }
	void						AddSelectProcedureVisionSheet(const CString& strValue)			{ m_strSelectProcedureVisionSheet.Add(strValue); }
	CString						GetSelectProcedureVisionSheet(UINT nIndex)						{ return m_strSelectProcedureVisionSheet.GetAt(nIndex); }
	UINT						GetSelectProcedureVisionSheetCount(void)						{ return (UINT)m_strSelectProcedureVisionSheet.GetCount(); }

	BOOL						TPRD_CAN_MSG_Process(TPRD_CAN_MSG_T& stCAN_MSG);
	BOOL						TPRD_CAN_MSG_VERIFY_Process(PCAN_PACKET_T& stPacket, TPRD_CAN_MSG_T& stCAN_MSG);
	BOOL						TPRD_CAN_MSG_SECURITY_Process(PCAN_PACKET_T& stPacket, TPRD_CAN_MSG_T& stCAN_MSG, UINT& nSecurityCode);
	BOOL						TPRD_CAN_MSG_DATA_Process(PCAN_PACKET_T& stPacket, TPRD_CAN_MSG_T& stCAN_MSG, PBYTE pData, UINT& nLength);


///////////////////////////////////////////////////////////////////////////////
// CAN 통신 정보 //////////////////////////////////////////////////////////////
protected:
	CAN_MSG_DATA_INFO_T			m_stCAN_TransmitData[MAX_CAN_MESSAGE];
	CString						m_strCAN_MsgSignalValue[MAX_CAN_SIGNAL_LIST];

public:
	void						CAN_InitInformation(void);

	CAN_MSG_DATA_INFO_T&		CAN_GetTransmitData(UINT nIndex)								{ return m_stCAN_TransmitData[nIndex]; }
	void						CAN_SetTransmitData(UINT nIndex, CAN_MSG_DATA_INFO_T stData)	{ m_stCAN_TransmitData[nIndex] = stData; }

	void						CAN_SetSignalValue(UINT nIndex, const CString& strValue)		{ m_strCAN_MsgSignalValue[nIndex] = strValue; }
	CString						CAN_GetSignalValue(UINT nIndex)									{ return m_strCAN_MsgSignalValue[nIndex]; }

	void						CAN_ClearSignalValue(void);
	void						CAN_UpdateSignalValue(void);


///////////////////////////////////////////////////////////////////////////////
// 데이터 베이스 //////////////////////////////////////////////////////////////
protected:
	CCriticalSection			m_csListDataBase;

public:



///////////////////////////////////////////////////////////////////////////////
// 시스템 상태 ////////////////////////////////////////////////////////////////
protected:
	SYSTEM_STATUS_T				m_stSystemStatus;

public:
	PSYSTEM_STATUS_T			GetSystemStatus(void)											{ return &m_stSystemStatus; }


///////////////////////////////////////////////////////////////////////////////
// 시스템 환경 설정 ///////////////////////////////////////////////////////////
protected:
	CDpsSystemConfig			m_SystemConfig;

public:
	CDpsSystemConfig*			GetSystemConfig(void)											{ return &m_SystemConfig; }


///////////////////////////////////////////////////////////////////////////////
// 모션 컨트롤러 //////////////////////////////////////////////////////////////
protected:
	DPS_MOTION_AXIS_INFO_T		m_stMotionAxisInfo[MAX_MOTION_AXIS];

public:
	BOOL						Motion_Move(UINT nAxisNo, DOUBLE dblDistance, DOUBLE dblSpeed, BOOL bOnMessage = TRUE);
	BOOL						Motion_MoveEx(UINT nAxisNo, DOUBLE dblDistance, DOUBLE dblSpeed, DOUBLE dblAccel, DOUBLE dblDecel, BOOL bOnMessage = TRUE);
	BOOL						Motion_MoveTo(UINT nAxisNo, DOUBLE dblPosition, DOUBLE dblSpeed, BOOL bOnMessage = TRUE);
	BOOL						Motion_MoveVel(UINT nAxisNo, DOUBLE dblSpeed, DOUBLE dblAccelTime, UINT nDirection);

	BOOL						Motion_Move2X(LONG lCoord, UINT nAxisNo1, UINT nAxisNo2, DOUBLE dblPos1, DOUBLE dblPos2, DOUBLE dblSpeed, BOOL bOnMessage = TRUE);
	BOOL						Motion_Move3X(LONG lCoord, UINT nAxisNo1, UINT nAxisNo2, UINT nAxisNo3, DOUBLE dblPos1, DOUBLE dblPos2, DOUBLE dblPos3, DOUBLE dblSpeed, BOOL bOnMessage = TRUE);
	BOOL						Motion_MoveNX(LONG lCoord, UINT nNumAxis, UINT* pAxisNo, DOUBLE* pPosition, DOUBLE dblSpeed, BOOL bOnMessage = TRUE);

	BOOL						Motion_Done(UINT nAxisNo);
	BOOL						Motion_DoneAll(void);
	
	BOOL						Motion_CheckSafePosition(UINT nAxisNo, DOUBLE dblPosition);
	BOOL						Motion_CheckSafePosition(UINT nAxisNo, BOOL bIsMIN = TRUE, BOOL bIsMAX = TRUE);
	BOOL						Motion_CheckCustomPosition(UINT nPosition);
	BOOL						Motion_CheckCustomPosition(UINT nAxisNo, DOUBLE dblPosition, DOUBLE dblTolerance = 0.01);
	BOOL						Motion_CheckInPosition(UINT nAxisNo, DOUBLE dblPositionMIN, DOUBLE dblPositionMAX);
	BOOL						Motion_CheckInPosition(UINT nAxisNo, DOUBLE dblMotorPosition, DOUBLE dblPositionMIN, DOUBLE dblPositionMAX);
	BOOL						Motion_CheckStopStatus(UINT nAxisNo, DOUBLE dblDestPosition, BOOL bOnMessage = TRUE, DWORD* pStatus = NULL);

	void						Motion_SetSoftLimit(UINT nAxisNo, BOOL bEnable = TRUE);
	void						Motion_SetSoftLimit(UINT nAxisNo, DOUBLE dblLimitNegativePos, DOUBLE dblLimitPositivePos);
	BOOL						Motion_GetSoftLimit(UINT nAxisNo, DOUBLE& dblLimitNegativePos, DOUBLE& dblLimitPositivePos);

	BOOL						Motion_SignalEventPositionStart(UINT nAxisNo, UINT nSignalNo, UINT nTypeEdge, UINT nTypeCount);
	BOOL						Motion_SignalEventPositionStop(UINT nAxisNo);
	BOOL						Motion_SignalEvantReadPosition(UINT nAxisNo, DOUBLE* pPosition);
	BOOL						Motion_SignalEventReadStatus(UINT nAxisNo, PINT pStatus);

	void						Motion_Stop_S(UINT nAxisNo)												{ AxmMoveSStop(nAxisNo); }
	void						Motion_Stop_E(UINT nAxisNo)												{ AxmMoveEStop(nAxisNo); }

public:
	void						SetMotionAxisInfo(UINT nAxisNo, DPS_MOTION_AXIS_INFO_T stInfo)			{ m_stMotionAxisInfo[nAxisNo] = stInfo; }
	DPS_MOTION_AXIS_INFO_T		GetMotionAxisInfo(UINT nAxisNo)											{ return m_stMotionAxisInfo[nAxisNo]; }

	void						Motion_Initialize(void);												// 모션 컨트롤러 초기화
	BOOL						SaveMotionAxisInfo(BOOL bBinary = TRUE);								// 모션 축 정보 저장
	BOOL						LoadMotionAxisInfo(BOOL bBinary = TRUE);


///////////////////////////////////////////////////////////////////////////////
// 비전 검사 정보 /////////////////////////////////////////////////////////////
protected:
	MIL_ID						m_MilApplication;														// MIL 어플리케이션
	MIL_ID						m_MilSystem;															// MIL 시스템
	MIL_ID						m_MilDigitizer[MAX_VISION_CHANNEL];										// MIL 디지타이저

	MIL_ID						m_MilImageGrab[MAX_VISION_CHANNEL];										// 캡쳐 이미지 버퍼
	MIL_ID						m_MilImageInspection[MAX_TEST_SHEET];									// 검사 이미지 버퍼

	MIL_INT						m_MilDigitizerNbBands;													// Number of input color bands of the digitizer
	MIL_INT						m_MilNumberOfDigitizer;													// Number of digitizers available on the system
	MIL_INT64					m_MilBufferAttributes;													// Buffer attributes that will be allocated

	CSize						m_sizeFrame[MAX_VISION_CHANNEL];										// 디지타이저 프레임 크기
	CCriticalSection			m_csDigitizerGrabImage[MAX_VISION_CHANNEL];								// 크리티컬 섹션 : 카메라 이미지 캡쳐

public:
	CDpsMilVideoWnd*			m_pMilVideoWnd[MAX_VISION_CHANNEL];										// MIL 비디오 윈도우
	CDpsMilImageWnd*			m_pMilImageWnd;															// MIL 이미지 윈도우

public:
	BOOL						MatroxInitialize(void);													// Initialize MIL Library
	void						MatroxRelease(void);													// Release MIL Library

	MIL_ID						GetMilSystem(void)														{ return m_MilSystem; }
	MIL_ID						GetMilDigitizer(UINT nVisionCH)											{ return m_MilDigitizer[nVisionCH]; }
	MIL_ID						GetMilImageInspection(UINT nTestItemNo)									{ return m_MilImageInspection[nTestItemNo]; }

	CSize						GetSizeFrame(UINT nVisionCH)											{ return m_sizeFrame[nVisionCH]; }

public:
	BOOL						GrabVisionImage(UINT nVisionCH, UINT nTestItemNo);
	BOOL						SaveVisionImage(UINT nTestItemNo, BOOL bGrayScale = TRUE, BOOL bIsJPEG = FALSE, BOOL bIsCommon = FALSE);

public:
	BOOL						SaveVisionCameraParameters(UINT nVisionCH, UINT nChannelNo);
	BOOL						LoadVisionCameraParameters(UINT nVisionCH, UINT nChannelNo);
	BOOL						SetVisionCameraAutoWhiteBalance(UINT nVisionCH, UINT nValue);
	BOOL						SetVisionCameraExposure(UINT nVisionCH, UINT nValue);

public:
	BOOL						ProcessImage_Threshold(UINT nTestItemNo, UINT nTestStationNo, DPS_POINT2D_T stOriginOffset, VI_PARAM_THRESHOLD_T& stParam, VI_RESULT_THRESHOLD_T& stResult, BOOL bSaveClip = TRUE);
	BOOL						ProcessImage_ThresholdLength(UINT nTestItemNo, UINT nTestStationNo, DPS_POINT2D_T stOriginOffset, VI_PARAM_THRESHOLD_LENGTH_T& stParam, VI_RESULT_THRESHOLD_LENGTH_T& stResult, BOOL bSaveClip = TRUE);
	BOOL						ProcessImage_PatternMatch(UINT nTestItemNo, UINT nTestStationNo, DPS_POINT2D_T stOriginOffset, VI_PARAM_PATTERN_T& stParam, VI_RESULT_PATTERN_T& stResult, BOOL bSaveClip = TRUE);
	BOOL						ProcessImage_ModelFind(UINT nTestItemNo, UINT nTestStationNo, DPS_POINT2D_T stOriginOffset, VI_PARAM_MODEL_T& stParam, VI_RESULT_MODEL_T& stResult, BOOL bSaveClip = TRUE);
	BOOL						ProcessImage_ColorAnalysis(UINT nTestItemNo, UINT nTestStationNo, DPS_POINT2D_T stOriginOffset, VI_PARAM_COLOR_T& stParam, VI_RESULT_COLOR_T& stResult, BOOL bSaveClip = TRUE);


///////////////////////////////////////////////////////////////////////////////
// 비전 센서 유닛 /////////////////////////////////////////////////////////////
protected:

public:
	BOOL						VISION_SelectProgramNo(BOOL bEnable, INT nProgramNo = 0);
	BOOL						VISION_ImportResult(const CString& strFileName, VISION_RESULT_T& stResult);
	BOOL						VISION_GetInspectionImage(CString& strFileName);


///////////////////////////////////////////////////////////////////////////////
// 작업 프로세스 //////////////////////////////////////////////////////////////
protected:
	CWinThread*					m_pThread[MAX_WORK_THREAD];
	CCriticalSection			m_csExitThread[MAX_WORK_THREAD];
	volatile BOOL				m_bExitThread[MAX_WORK_THREAD];

protected:
	void						StationProcessDataInitialize(UINT nSTATION_NO, UINT nSTATION_SUB_NO, PROCESS_CTRL_T& PROCESS);
	void						ProcessDataInitialize(PROCESS_CTRL_T& PROCESS);
	BOOL						CheckProcessGeneral(UINT nSTATION_NO, PROCESS_CTRL_T& PROCESS);
	BOOL						CheckProcessOperating(PROCESS_CTRL_T& PROCESS);
	BOOL						CheckProcessOperatingPause(UINT nSTATION_NO, PROCESS_CTRL_T& PROCESS);
	BOOL						CheckProcessOperatingStop(PROCESS_CTRL_T& PROCESS);
	BOOL						CheckProcessOperatingStopReservated(UINT nSTATION_NO, UINT nSTATION_SUB_NO, PROCESS_CTRL_T& PROCESS);
	BOOL						CheckProcessManualControlMode(UINT nSTATION_NO, PROCESS_CTRL_T& PROCESS);
	BOOL						CheckProcessMachineInitialize(PROCESS_CTRL_T& PROCESS);
	BOOL						CheckProcessEmergencyStop(PROCESS_CTRL_T& PROCESS);

public:
	BOOL						StartWorkProcess(void);
	void						StopWorkProcess(void);

public:
	static	UINT				ThreadFuncMain(LPVOID lpParam);									// 스레드 : 메인
	static	UINT				ThreadFuncSystem(LPVOID lpParam);								// 스레드 : 시스템
	static	UINT				ThreadFuncSub(LPVOID lpParam);									// 스레드 : 서브
	static	UINT				ThreadFuncDBMS(LPVOID lpParam);									// 스레드 : 데이터베이스

public:

	///////////////////////////////////////////////////////////////////////////
	// 시스템 프로세스 ////////////////////////////////////////////////////////
	void						ProcessSystem(void);											// 프로세스 : 시스템
	void						ProcessSystemSub01(UINT nSTATION_NO);
	void						ProcessErrorDetect(void);										// 프로세스 : 오류 검출
	
	void						ProcessCheckEmergency(void);									// 프로세스 : 비상 체크
	void						ProcessCheckAirPressure(void);									// 프로세스 : 공압 체크
	void						ProcessCheckDoorOpen(void);										// 프로세스 : 도어 체크

	void						ProcessMotion(void);											// 프로세스 : 모션 컨트롤
	void						ProcessMotionHomeSearch01(UINT nAxisNo);						// 프로세스 : 모션 원점 검출 (기본)
	void						ProcessMotionHomeSearch02(UINT nAxisNo);						// 프로세스 : 모션 원점 검출 (N-LIMIT 원점)
	void						ProcessMotionHomeSearch03(UINT nAxisNo, UINT nSignalNo);		// 프로세스 : 모션 원점 검출 (AXT 구동)
	void						ProcessMotionHomeSearch04(UINT nAxisNo);						// 프로세스 : 모션 원점 검출 (SMC 스테핑)


	///////////////////////////////////////////////////////////////////////////
	// 작업 프로세스 //////////////////////////////////////////////////////////
	PERROR_CODE_T				ProcessMachineInit(void);										// 장비 초기화

	PERROR_CODE_T				ProcessMainWorkProcedure(void);									// 메인 작업 : 프로시저
	PERROR_CODE_T				ProcessMainWorkTest(void);										// 메인 작업 : 일반 검사
	PERROR_CODE_T				ProcessMainWorkVision(void);									// 메인 작업 : 비전 검사

	PERROR_CODE_T				ProcessCommon(void);											// 프로세스 : 공통
	PERROR_CODE_T				ProcessCommonParts(void);

	PERROR_CODE_T				ProcessStation01(void);											// 프로세스 : 검사 공정 (OS)
	PERROR_CODE_T				ProcessStation02(void);											// 프로세스 : 검사 공정 (SK)
	PERROR_CODE_T				ProcessStation01Parts(void);
	PERROR_CODE_T				ProcessStation02Parts(void);


	///////////////////////////////////////////////////////////////////////////
	// 기타 프로세스 //////////////////////////////////////////////////////////
	PERROR_CODE_T				ProcessDeviceLC(void);											// 프로세스 : 디바이스 (LOADCELL)
	PERROR_CODE_T				ProcessLabelPrint(UINT nBCP_NO);								// 프로세스 : 라벨 프린터
	void						ProcessBarcodeScan(void);										// 프로세스 : 바코드 스캔
	void						ProcessDeviceCAN(void);											// 프로세스 : CAN 통신


///////////////////////////////////////////////////////////////////////////////
// 클래스 기본 ////////////////////////////////////////////////////////////////
public:
	CMainApp(void);

public:
	virtual BOOL				InitInstance(void);

	DECLARE_MESSAGE_MAP()
};


///////////////////////////////////////////////////////////////////////////////
// 고유 객체 //////////////////////////////////////////////////////////////////
extern CMainApp theApp;