Attribute VB_Name = "AXDev"

' Board Number를 이용하여 Board Address 찾기
Public Declare Function AxlGetBoardAddress Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef upBoardAddress As Long) As Long
' Board Number를 이용하여 Board ID 찾기
Public Declare Function AxlGetBoardID Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef upBoardID As Long) As Long
' Board Number를 이용하여 Board Version 찾기
Public Declare Function AxlGetBoardVersion Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef upBoardVersion As Long) As Long
' Board Number와 Module Position을 이용하여 Module ID 찾기
Public Declare Function AxlGetModuleID Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef upModuleID As Long) As Long
' Board Number와 Module Position을 이용하여 Module Version 찾기
Public Declare Function AxlGetModuleVersion Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef upModuleVersion As Long) As Long
' Board Number와 Module Position을 이용하여 Network Node 정보 확인
Public Declare Function AxlGetModuleNodeInfo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef upNetNo As Long, ByRef upNodeAddr As Long) As Long

' Board에 내장된 범용 Data Flash Write (PCI-R1604[RTEX master board]전용)
' lPageAddr(0 ~ 199)
' lByteNum(1 ~ 120)
' 주의) Flash에 데이타를 기입할 때는 일정 시간(최대 17mSec)이 소요되기때문에 연속 쓰기시 지연 시간이 필요함.
Public Declare Function AxlSetDataFlash Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lPageAddr As Long, ByVal lBytesNum As Long, ByRef bpSetData As Byte) As Long

' Board에 내장된 범용 Data Flash Read(PCI-R1604[RTEX master board]전용)
' lPageAddr(0 ~ 199)
' lByteNum(1 ~ 120)
Public Declare Function AxlGetDataFlash Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lPageAddr As Long, ByVal lBytesNum As Long, ByRef bpGetData As Byte) As Long

' Board Number와 Module Position을 이용하여 AIO Module Number 찾기
Public Declare Function AxaInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef lpModuleNo As Long) As Long
' Board Number와 Module Position을 이용하여 DIO Module Number 찾기
Public Declare Function AxdInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef lpModuleNo As Long) As Long

' 지정 축에 IPCOMMAND Setting
Public Declare Function AxmSetCommand Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte) As Long
' 지정 축에 8bit IPCOMMAND Setting
Public Declare Function AxmSetCommandData08 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' 지정 축에 8bit IPCOMMAND 가져오기
Public Declare Function AxmGetCommandData08 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef updata As Long) As Long
' 지정 축에 16bit IPCOMMAND Setting
Public Declare Function AxmSetCommandData16 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' 지정 축에 16bit IPCOMMAND 가져오기
Public Declare Function AxmGetCommandData16 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef updata As Long) As Long
' 지정 축에 24bit IPCOMMAND Setting
Public Declare Function AxmSetCommandData24 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' 지정 축에 24bit IPCOMMAND 가져오기
Public Declare Function AxmGetCommandData24 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef updata As Long) As Long
' 지정 축에 32bit IPCOMMAND Setting
Public Declare Function AxmSetCommandData32 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' 지정 축에 32bit IPCOMMAND 가져오기
Public Declare Function AxmGetCommandData32 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef updata As Long) As Long

' 지정 축에 QICOMMAND Setting
Public Declare Function AxmSetCommandQi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte) As Long
' 지정 축에 8bit IPCOMMAND Setting
Public Declare Function AxmSetCommandData08Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' 지정 축에 8bit IPCOMMAND 가져오기
Public Declare Function AxmGetCommandData08Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef updata As Long) As Long
' 지정 축에 16bit IPCOMMAND Setting
Public Declare Function AxmSetCommandData16Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' 지정 축에 16bit IPCOMMAND 가져오기
Public Declare Function AxmGetCommandData16Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef updata As Long) As Long
' 지정 축에 24bit IPCOMMAND Setting
Public Declare Function AxmSetCommandData24Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' 지정 축에 24bit IPCOMMAND 가져오기
Public Declare Function AxmGetCommandData24Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef updata As Long) As Long
' 지정 축에 32bit IPCOMMAND Setting
Public Declare Function AxmSetCommandData32Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' 지정 축에 32bit IPCOMMAND 가져오기
Public Declare Function AxmGetCommandData32Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef updata As Long) As Long

' 지정 축에 Port Data 가져오기 - SMC-2V03
Public Declare Function AxmGetPortData Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wOffset As Long, ByRef updata As Long) As Long
' 지정 축에 Port Data Setting - SMC-2V03
Public Declare Function AxmSetPortData Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wOffset As Long, ByRef dwData As Long) As Long
' 지정 축에 Port Data 가져오기 - PIC-N804/404
Public Declare Function AxmGetPortDataQi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wOffset As Long, ByRef updata As Long) As Long
' 지정 축에 Port Data Setting - PCI-N804/404
Public Declare Function AxmSetPortDataQi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wOffset As Long, ByRef dwData As Long) As Long

' 지정 축에 스크립트를 설정한다. - IP
' sc    : 스크립트 번호  Lib "AXL.dll" (1 - 4)
' event : 발생할 이벤트 SCRCON 을 정의한다.
'         이벤트 설정 축갯수설정, 이벤트 발생할 축, 이벤트 내용 1,2 속성 설정한다.
' cmd   : 어떤 내용을 바꿀것인지 선택 SCRCMD를 정의한다.
' data  : 어떤 Data를 바꿀것인지 선택
Public Declare Function AxmSetScriptCaptionIp Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sc As Long, ByVal event1 As Long, ByVal data As Long) As Long
' 지정 축에 스크립트를 반환한다. - IP
Public Declare Function AxmGetScriptCaptionIp Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sc As Long, ByRef event1 As Long, ByRef data As Long) As Long

' 지정 축에 스크립트를 설정한다. - QI
' sc    : 스크립트 번호  Lib "AXL.dll" (1 - 4)
' event : 발생할 이벤트 SCRCON 을 정의한다.
'         이벤트 설정 축갯수설정, 이벤트 발생할 축, 이벤트 내용 1,2 속성 설정한다.
' cmd   : 어떤 내용을 바꿀것인지 선택 SCRCMD를 정의한다.
' data  : 어떤 Data를 바꿀것인지 선택
Public Declare Function AxmSetScriptCaptionQi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sc As Long, ByVal event1 As Long, ByVal cmd As Long, ByVal data As Long) As Long
' 지정 축에 스크립트를 반환한다. - QI
Public Declare Function AxmGetScriptCaptionQi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sc As Long, ByRef event1 As Long, ByRef cmd As Long, ByRef data As Long) As Long

' 지정 축에 스크립트 내부 Queue Index를 Clear 시킨다.
' uSelect IP.
' uSelect Lib "AXL.dll" (0): 스크립트 Queue Index 를 Clear한다.
'         Lib "AXL.dll" (1): 캡션 Queue를 Index Clear한다.

' uSelect QI.
' uSelect Lib "AXL.dll" (0): 스크립트 Queue 1 Index 을 Clear한다.
'         Lib "AXL.dll" (1): 스크립트 Queue 2 Index 를 Clear한다.

Public Declare Function AxmSetScriptCaptionQueueClear Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uSelect As Long) As Long

' 지정 축에 스크립트 내부 Queue의 Index 반환한다.
' uSelect IP
' uSelect Lib "AXL.dll" (0): 스크립트 Queue Index를 읽어온다.
'         Lib "AXL.dll" (1): 캡션 Queue Index를 읽어온다.

' uSelect QI.
' uSelect Lib "AXL.dll" (0): 스크립트 Queue 1 Index을 읽어온다.
'         Lib "AXL.dll" (1): 스크립트 Queue 2 Index를 읽어온다.

Public Declare Function AxmGetScriptCaptionQueueCount Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef updata As Long, ByVal uSelect As Long) As Long

' 지정 축에 스크립트 내부 Queue의 Data갯수 반환한다.
' uSelect IP
' uSelect Lib "AXL.dll" (0): 스크립트 Queue Data 를 읽어온다.
'         Lib "AXL.dll" (1): 캡션 Queue Data를 읽어온다.

' uSelect QI.
' uSelect Lib "AXL.dll" (0): 스크립트 Queue 1 Data 읽어온다.
'         Lib "AXL.dll" (1): 스크립트 Queue 2 Data 읽어온다.

Public Declare Function AxmGetScriptCaptionQueueDataCount Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef updata As Long, ByVal uSelect As Long) As Long

' 내부 데이타를 읽어온다.
Public Declare Function AxmGetOptimizeDriveData Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dMinVel As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByRef wRangeData As Long, ByRef wStartStopSpeedData As Long, ByRef wObjectSpeedData As Long, ByRef wAccelRate As Long, ByRef wDecelRate As Long) As Long

' 보드내에 레지스터를 Byte단위로 설정 및 확인한다.
Public Declare Function AxmBoardWriteByte Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByVal byData As Byte) As Long
Public Declare Function AxmBoardReadByte Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByRef byData As Byte) As Long

' 보드내에 레지스터를 Word단위로 설정 및 확인한다.
Public Declare Function AxmBoardWriteWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByVal wData As Long) As Long
Public Declare Function AxmBoardReadWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByRef wData As Long) As Long

' 보드내에 레지스터를 DWord단위로 설정 및 확인한다.
Public Declare Function AxmBoardWriteDWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByVal dwData As Long) As Long
Public Declare Function AxmBoardReadDWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByRef dwData As Long) As Long

' 보드내에 모듈에 레지스터를 Byte설정 및 확인한다.
Public Declare Function AxmModuleWriteByte Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByVal byData As Byte) As Long
Public Declare Function AxmModuleReadByte Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByRef byData As Byte) As Long

' 보드내에 모듈에 레지스터를 Word설정 및 확인한다.
Public Declare Function AxmModuleWriteWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByVal wData As Long) As Long
Public Declare Function AxmModuleReadWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByRef wData As Long) As Long

' 보드내에 모듈에 레지스터를 DWord설정 및 확인한다.
Public Declare Function AxmModuleWriteDWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByVal dwData As Long) As Long
Public Declare Function AxmModuleReadDWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByRef dwData As Long) As Long


' 외부 위치 비교기에 값을 설정한다. Lib "AXL.dll" (Pos = Unit)
Public Declare Function AxmStatusSetActComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double) As Long
' 외부 위치 비교기에 값을 반환한다. Lib "AXL.dll" (Positon = Unit)
Public Declare Function AxmStatusGetActComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpPos As Double) As Long

' 내부 위치 비교기에 값을 설정한다. Lib "AXL.dll" (Pos = Unit)
Public Declare Function AxmStatusSetCmdComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double) As Long
' 내부 위치 비교기에 값을 반환한다. Lib "AXL.dll" (Pos = Unit)
Public Declare Function AxmStatusGetCmdComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpPos As Double) As Long

'========== 추가 함수 =========================================================================================================

' 직선 보간 을 속도만 가지고 무한대로 증가한다.
' 속도 비율대로 거리를 넣어주어야 한다.
Public Declare Function AxmLineMoveVel Lib "AXL.dll" (ByVal lCoord As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

'========= 센서 위치 구동 함수 Lib "AXL.dll" ( 필독: IP만가능 , QI에는 기능없음)=========================================================================

' 지정 축의 Sensor 신호의 사용 유무 및 신호 입력 레벨을 설정한다.
' 사용 유무 LOW Lib "AXL.dll" (0), HIGH Lib "AXL.dll" (1), UNUSED Lib "AXL.dll" (2), USED Lib "AXL.dll" (3)
Public Declare Function AxmSensorSetSignal Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uLevel As Long) As Long
' 지정 축의 Sensor 신호의 사용 유무 및 신호 입력 레벨을 반환한다.
Public Declare Function AxmSensorGetSignal Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upLevel As Long) As Long
' 지정 축의 Sensor 신호의 입력 상태를 반환한다
Public Declare Function AxmSensorReadSignal Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long

' 지정 축의 설정된 속도와 가속율로 센서 위치 드라이버를 구동한다.
' Sensor 신호의 Active level입력 이후 상대 좌표로 설정된 거리만큼 구동후 정지한다.
' 펄스가 출력되는 시점에서 함수를 벗어난다.
' lMethod :  0 - 일반 구동, 1 - 센서 신호 검출 전은 저속 구동. 신호 검출 후 일반 구동
'            2 - 저속 구동
Public Declare Function AxmSensorMovePos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lMethod As Long) As Long

' 지정 축의 설정된 속도와 가속율로 센서 위치 드라이버를 구동한다.
' Sensor 신호의 Active level입력 이후 상대 좌표로 설정된 거리만큼 구동후 정지한다.
' 펄스 출력이 종료되는 시점에서 함수를 벗어난다.
Public Declare Function AxmSensorStartMovePos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lMethod As Long) As Long

' 원점검색 진행스탭 변화의 기록을 반환한다.
' lpStepCount      : 기록된 Step의 개수
' upMainStepNumber : 기록된 MainStepNumber 정보의 배열포인트
' upStepNumber     : 기록된 StepNumber 정보의 배열포인트
' upStepBranch     : 기록된 Step별 Branch 정보의 배열포인트
' 주의: 배열개수는 50개로 고정
Public Declare Function AxmHomeGetStepTrace Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpStepCount As Long, ByRef upMainStepNumber As Long, ByRef upStepNumber As Long, ByRef upStepBranch As Long) As Long

'=======추가 홈 서치  Lib "AXL.dll" (PI-N804/404에만 해당됨.)=================================================================================
' 사용자가 지정한 축의 홈설정 파라메타를 설정한다. Lib "AXL.dll" (QI칩 전용 레지스터 이용).
' uZphasCount : 홈 완료후에 Z상 카운트 Lib "AXL.dll" (0 - 15)
' lHomeMode   : 홈 설정 모드 Lib "AXL.dll" ( 0 - 12)
' lClearSet   : 위치 클리어 , 잔여펄스 클리어 사용 선택  Lib "AXL.dll" (0 - 3)
'               0: 위치클리어 사용않함, 잔여펄스 클리어 사용 안함
'               1: 위치클리어 사용함, 잔여펄스 클리어 사용 안함
'               2: 위치클리어 사용안함, 잔여펄스 클리어 사용함
'               3: 위치클리어 사용함, 잔여펄스 클리어 사용함.
' dOrgVel : 홈관련 Org  Speed 설정
' dLastVel: 홈관련 Last Speed 설정
Public Declare Function AxmHomeSetConfig Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uZphasCount As Long, ByVal lHomeMode As Long, ByVal lClearSet As Long, ByVal dOrgVel As Double, ByVal dLastVel As Double, ByVal dLeavePos As Double) As Long
' 사용자가 지정한 축의 홈설정 파라메타를 반환한다.
Public Declare Function AxmHomeGetConfig Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upZphasCount As Long, ByRef lpHomeMode As Long, ByRef lpClearSet As Long, ByRef dpOrgVel As Double, ByRef dpLastVel As Double, ByRef dpLeavePos As Double) As Long

' 사용자가 지정한 축의 홈 서치를 시작한다.
' lHomeMode 사용시 설정 : 0 - 5 설정  Lib "AXL.dll" (Move Return후에 Search를  시작한다.)
' lHomeMode -1로 그대로 사용시 HomeConfig에서 사용한대로 그대로 설정됨.
' 구동방향      : Vel값이 양수이면 CW, 음수이면 CCW.
Public Declare Function AxmHomeSetMoveSearch Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

' 사용자가 지정한 축의 홈 리턴을 시작한다.
' lHomeMode 사용시 설정 : 0 - 12 설정
' lHomeMode -1로 그대로 사용시 HomeConfig에서 사용한대로 그대로 설정됨.
' 구동방향      : Vel값이 양수이면 CW, 음수이면 CCW.
Public Declare Function AxmHomeSetMoveReturn Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

' 사용자가 지정한 축의 홈 이탈을 시작한다.
' 구동방향      : Vel값이 양수이면 CW, 음수이면 CCW.
Public Declare Function AxmHomeSetMoveLeave Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

' 사용자가 지정한 다축의 홈 서치을 시작한다.
' lHomeMode 사용시 설정 : 0 - 5 설정  Lib "AXL.dll" (Move Return후에 Search를  시작한다.)
' lHomeMode -1로 그대로 사용시 HomeConfig에서 사용한대로 그대로 설정됨.
' 구동방향      : Vel값이 양수이면 CW, 음수이면 CCW.
Public Declare Function AxmHomeSetMultiMoveSearch Lib "AXL.dll" (ByVal lArraySize As Long, ByRef lpAxesNo As Long, ByRef dpVel As Double, ByRef dpAccel As Double, ByRef dpDecel As Double) As Long

'지정된 좌표계의 구동 속도 프로파일 모드를 설정한다.
'  Lib "AXL.dll" (주의점 : 반드시 축맵핑 하고 사용가능)
' ProfileMode : '0' - 대칭 Trapezode
'               '1' - 비대칭 Trapezode
'               '2' - 대칭 Quasi-S Curve
'               '3' - 대칭 S Curve
'               '4' - 비대칭 S Curve
Public Declare Function AxmContiSetProfileMode Lib "AXL.dll" (ByVal lCoord As Long, ByVal uProfileMode As Long) As Long
' 지정된 좌표계의 구동 속도 프로파일 모드를 반환한다.
Public Declare Function AxmContiGetProfileMode Lib "AXL.dll" (ByVal lCoord As Long, ByRef upProfileMode As Long) As Long

'========== DIO 인터럽트 플래그 레지스트 읽기
' 지정한 입력 접점 모듈, Interrupt Flag Register의 Offset 위치에서 bit 단위로 인터럽트 발생 상태 값을 읽음
Public Declare Function AxdiInterruptFlagReadBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long
' 지정한 입력 접점 모듈, Interrupt Flag Register의 Offset 위치에서 byte 단위로 인터럽트 발생 상태 값을 읽음
Public Declare Function AxdiInterruptFlagReadByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long
' 지정한 입력 접점 모듈, Interrupt Flag Register의 Offset 위치에서 word 단위로 인터럽트 발생 상태 값을 읽음
Public Declare Function AxdiInterruptFlagReadWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long
' 지정한 입력 접점 모듈, Interrupt Flag Register의 Offset 위치에서 double word 단위로 인터럽트 발생 상태 값을 읽음
Public Declare Function AxdiInterruptFlagReadDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long
' 전체 입력 접점 모듈, Interrupt Flag Register의 Offset 위치에서 bit 단위로 인터럽트 발생 상태 값을 읽음
Public Declare Function AxdiInterruptFlagRead Lib "AXL.dll" (ByVal lOffset As Long, ByRef upValue As Long) As Long

'========= 로그 관련 함수 ==========================================================================================
' 현재 자동으로 설정됨.
' 설정 축의 함수 실행 결과를 EzSpy에서 모니터링 할 수 있도록 설정 또는 해제하는 함수이다.
' uUse : 사용 유무 => DISABLE Lib "AXL.dll" (0), ENABLE Lib "AXL.dll" (1)
Public Declare Function AxmLogSetAxis Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uUse As Long) As Long

' EzSpy에서의 설정 축 함수 실행 결과 모니터링 여부를 확인하는 함수이다.
Public Declare Function AxmLogGetAxis Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upUse As Long) As Long

'=========== 로그 출력 관련 함수
'지정한 입력 채널의 EzSpy에 로그 출력 여부를 설정한다.
Public Declare Function AxaiLogSetChannel Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal uUse As Long) As Long
'지정한 입력 채널의 EzSpy에 로그 출력 여부를 확인한다.
Public Declare Function AxaiLogGetChannel Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef upUse As Long) As Long

'==지정한 출력 채널의 EzSpy 로그 출력
'지정한 출력 채널의 EzSpy에 로그 출력 여부를 설정한다.
Public Declare Function AxaoLogSetChannel Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal uUse As Long) As Long
'지정한 출력 채널의 EzSpy에 로그 출력 여부를 확인한다.
Public Declare Function AxaoLogGetChannel Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef upUse As Long) As Long

'==Log
' 지정한 모듈의 EzSpy에 로그 출력 여부 설정
Public Declare Function AxdLogSetModule Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal uUse As Long) As Long
' 지정한 모듈의 EzSpy에 로그 출력 여부 확인
Public Declare Function AxdLogGetModule Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef upUse As Long) As Long

' 지정한 보드가 RTEX 모드일 때 그 보드의 firmware 버전을 확인한다.
Public Declare Function AxlGetFirmwareVersion Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal szVersion As String) As Long
' 지정한 보드로 Firmware를 전송 한다.
Public Declare Function AxlSetFirmwareCopy Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef wData As Long, ByRef wCmdData As Long) As Long
' 지정한 보드로 Firmware Update를 수행한다.
Public Declare Function AxlSetFirmwareUpdate Lib "AXL.dll" (ByVal lBoardNo As Long) As Long
' 지정한 보드의 현재 RTEX 초기화 상태를 확인 한다.
Public Declare Function AxlCheckStatus Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef dwStatus As Long) As Long
' 지정한 축에 RTEX Master board에 범용 명령을 실행 합니다.
Public Declare Function AxlRtexUniversalCmd Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wCmd As Long, ByVal wOffset As Long, ByRef wData As Long) As Long
' 지정한 축의 RTEX 통신 명령을 실행한다.
Public Declare Function AxmRtexSlaveCmd Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwCmdCode As Long, ByVal dwTypeCode As Long, ByVal dwIndexCode As Long, ByVal dwCmdConfigure As Long, ByVal dwValue As Long) As Long
' 지정한 축에 실행한 RTEX 통신 명령의 결과값을 확인한다.
Public Declare Function AxmRtexGetSlaveCmdResult Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwIndex As Long, ByRef dwValue As Long) As Long
' 지정한 축에 RTEX 상태 정보를 확인한다.
Public Declare Function AxmRtexGetAxisStatus Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwStatus As Long) As Long
' 지정한 축에 RTEX 통신 리턴 정보를 확인한다. Lib "AXL.dll" (Actual position, Velocity, Torque)
Public Declare Function AxmRtexGetAxisReturnData Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwReturn1 As Long, ByRef dwReturn2 As Long, ByRef dwReturn3 As Long) As Long
' 지정한 축에 RTEX Slave 축의 현재 상태 정보를 확인한다. Lib "AXL.dll" (mechanical, Inposition and etc)
Public Declare Function AxmRtexGetAxisSlaveStatus Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwStatus As Long) As Long

' 지정한 축에 MLII Slave 축에 범용 네트웍 명령어를 기입한다.
Public Declare Function AxmSetAxisCmd Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef tagCommand As Long) As Long
' 지정한 축에 MLII Slave 축에 범용 네트웍 명령의 결과를 확인한다.
Public Declare Function AxmGetAxisCmdResult Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef tagCommand As Long) As Long

Public Declare Function AxlGetDpRamData Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wAddress As Long, ByRef dwpRdData As Long) As Long
Public Declare Function AxlBoardReadDpramWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByRef dwpRdData As Long) As Long

Public Declare Function AxlSetSendBoardCommand Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal dwCommand As Long, ByRef dwpSendData As Long, ByVal dwLength As Long) As Long
Public Declare Function AxlGetResponseBoardCommand Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef dwpReadData As Long) As Long

' Network Type Master 보드에서 Slave 들의 Firmware Version을 읽어 오는 함수.
' ucaFirmwareVersion unsigned char 형의 Array로 선언하고 크기가 4이상이 되도록 선언 해야 한다.
Public Declare Function AxmInfoGetFirmwareVersion Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef ucaFirmwareVersion As Long) As Long
Public Declare Function AxaInfoGetFirmwareVersion Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef ucaFirmwareVersion As Long) As Long
Public Declare Function AxdInfoGetFirmwareVersion Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef ucaFirmwareVersion As Long) As Long

'======== PCI-R1604-MLII 전용 함수=========================================================================== 
' INTERPOLATE and LATCH Command의 Option Field의 Torq Feed Forward의 값을 설정 하도록 합니다.
' 기본값은 MAX로 설정되어 있습니다.
' 설정값은 0 ~ 4000H까지 설정 할 수 있습니다.
' 설정값은 4000H이상으로 설정하면 설정은 그 이상으로 설정되나 동작은 4000H값이 적용 됩니다.
Public Declare Function  AxmSetTorqFeedForward Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwTorqFeedForward As Long) As Long

' INTERPOLATE and LATCH Command의 Option Field의 Torq Feed Forward의 값을 읽어오는 함수 입니다.
' 기본값은 MAX로 설정되어 있습니다.
Public Declare Function  AxmGetTorqFeedForward Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpTorqFeedForward As Long) As Long

' INTERPOLATE and LATCH Command의 VFF Field의 Velocity Feed Forward의 값을 설정 하도록 합니다.
' 기본값은 '0'로 설정되어 있습니다.
' 설정값은 0 ~ FFFFH까지 설정 할 수 있습니다.
Public Declare Function  AxmSetVelocityFeedForward Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwVelocityFeedForward As Long) As Long

' INTERPOLATE and LATCH Command의 VFF Field의 Velocity Feed Forward의 값을 읽어오는 함수 입니다.
Public Declare Function  AxmGetVelocityFeedForward Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpVelocityFeedForward As Long) As Long

' Encoder type을 설정한다.
' 기본값은 0(TYPE_INCREMENTAL)로 설정되어 있습니다.
' 설정값은 0 ~ 1까지 설정 할 수 있습니다.
' 설정값 : 0(TYPE_INCREMENTAL), 1(TYPE_ABSOLUTE).
Public Declare Function AxmSignalSetEncoderType Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwEncoderType As Long) As Long

' Encoder type을 확인한다.
Public Declare Function AxmSignalGetEncoderType Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpEncoderType As Long) As Long

' Slave Firmware Update를 위해 추가
' Public Declare Function AxmSetSendAxisCommand Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wCommand As Long, ByRef wpSendData As Long, ByVal wLength As Long) As Long


'======== PCI-R1604-RTEX, RTEX-PM 전용 함수============================================================== 
' 범용 입력 2,3번 입력시 JOG 구동 속도를 설정한다. 
' 구동에 관련된 모든 설정(Ex, PulseOutMethod, MoveUnitPerPulse 등)들이 완료된 이후 한번만 실행하여야 한다
Public Declare Function AxmMotSetUserMotion Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVelocity As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

' 범용 입력 2,3번 입력시 JOG 구동 동작 사용 가부를 설정한다.
' 설정값 :  0(DISABLE), 1(ENABLE
Public Declare Function AxmMotSetUserMotionUsage Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwUsage As Long) As Long

' MPGP 입력을 사용하여 Load/UnLoad 위치를 자동으로 이동하는 기능 설정.
Public Declare Function AxmMotSetUserPosMotion Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVelocity As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal dLoadPos As Double, ByVal dUnLoadPos As Double, ByVal dwFilter As Long, ByVal dwDelay As Long) As Long

' MPGP 입력을 사용하여 Load/UnLoad 위치를 자동으로 이동하는 기능 설정. 
' 설정값 :  0(DISABLE), 1(Position 기능 A 사용), 2(Position 기능 B 사용
Public Declare Function AxmMotSetUserPosMotionUsage Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwUsage As Long) As Long
'======================================================================================================== 

'======== SIO-CN2CH, 절대 위치 트리거 기능 모듈 전용 함수================================================
' 메모리 데이터 쓰기 함수
Public Declare Function AxcKeWriteRamDataAddr Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwAddr As Long, ByVal dwData As Long) As Long
' 메모리 데이터 읽기 함수
Public Declare Function AxcKeReadRamDataAddr Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwAddr As Long, ByRef dwpData As Long) As Long
' 메모리 초기화 함수
Public Declare Function AxcKeResetRamDataAll Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dwData As Long) As Long
' 트리거 타임 아웃 설정 함수
Public Declare Function AxcTriggerSetTimeout Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwTimeout As Long) As Long
' 트리거 타임 아웃 확인 함수
Public Declare Function AxcTriggerGetTimeout Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dwpTimeout As Long) As Long
' 트리거 대기 상태 확인 함수
Public Declare Function AxcStatusGetWaitState Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dwpState As Long) As Long
' 트리거 대기 상태 설정 함수
Public Declare Function AxcStatusSetWaitState Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwState As Long) As Long

' 지정 채널에 명령어 기입.
Public Declare Function AxcKeSetCommandData32 Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwCommand As Long, ByVal dwData As Long) As Long
' 지정 채널에 명령어 기입.
Public Declare Function AxcKeSetCommandData16 Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwCommand As Long, ByVal wData As Long) As Long
' 지정 채널의 레지스터 확인.
Public Declare Function AxcKeGetCommandData32 Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwCommand As Long, ByRef dwpData As Long) As Long
' 지정 채널의 레지스터 확인.
Public Declare Function AxcKeGetCommandData16 Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwCommand As Long, ByRef wpData As Long) As Long
'========================================================================================================

'======== PCI-N804/N404 전용, Sequence Motion ===================================================================
' Sequence Motion의 축 정보를 설정 합니다. (최소 1축)
' lSeqMapNo : 축 번호 정보를 담는 Sequence Motion Index Point
' lSeqMapSize : 축 번호 갯수
' long* LSeqAxesNo : 축 번호 배
Public Declare Function AxmSeqSetAxisMap Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByVal lSeqMapSize As Long, ByRef lSeqAxesNo As Long) As Long
Public Declare Function AxmSeqGetAxisMap Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByRef lSeqMapSize As Long, ByRef lSeqAxesNo As Long) As Long

' Sequence Motion의 기준(Master) 축을 설정 합니다. 
' 반드시 AxmSeqSetAxisMap(...) 에 설정된 축 내에서 설정하여야 합니다
Public Declare Function AxmSeqSetMasterAxisNo Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByVal lMasterAxisNo As Long) As Long

' Sequence Motion의 Node 적재 시작을 라이브러리에 알립니다
Public Declare Function AxmSeqBeginNode Lib "AXL.dll" (ByVal lSeqMapNo) As Long

' Sequence Motion의 Node 적재 종료를 라이브러리에 알립니다
Public Declare Function AxmSeqEndNode Lib "AXL.dll" (ByVal lSeqMapNo) As Long
' Sequence Motion의 구동을 시작 합니다
Public Declare Function AxmSeqStart Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByVal dwStartOption As Long) As Long

' Sequence Motion의 각 Profile Node 정보를 라이브러리에 입력 합니다.
' 만약 1축 Sequence Motion을 사용하더라도, *dPosition는 1개의 Array로 지정하여 주시기 바랍니다
Public Declare Function AxmSeqAddNode Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByRef dPosition As Double, ByVal dVelocity As Double, ByVal dAcceleration As Double, ByVal dDeceleration As Double, ByVal dNextVelocity As Double) As Long

' Sequence Motion이 구동 시 현재 실행 중인 Node Index를 알려 줍니다
Public Declare Function AxmSeqGetNodeNum Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByRef lCurNodeNo As Long) As Long

' Sequence Motion의 총 Node Count를 확인 합니다
Public Declare Function AxmSeqGetTotalNodeNum Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByRef lTotalNodeCnt As Long) As Long

' Sequence Motion이 현재 구동 중인지 확인 합니다.
' dwInMotion : 0(구동 종료), 1(구동 중)
Public Declare Function AxmSeqIsMotion Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByRef dwInMotion As Long) As Long

' Sequence Motion의 Memory를 Clear 합니다.
' AxmSeqSetAxisMap(...), AxmSeqSetMasterAxisNo(...) 에서 설정된 값은 유지됩니다
Public Declare Function AxmSeqWriteClear Lib "AXL.dll" (ByVal lSeqMapNo) As Long

' Sequence Motion의 구동을 종료 합니다.
' dwStopMode : 0(EMERGENCY_STOP), 1(SLOWDOWN_STOP)
Public Declare Function AxmSeqStop Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByVal dwStopMode As Long) As Long
'========================================================================================================