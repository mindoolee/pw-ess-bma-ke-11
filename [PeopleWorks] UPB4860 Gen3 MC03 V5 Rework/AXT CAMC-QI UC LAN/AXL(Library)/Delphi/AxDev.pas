unit AXDev;

interface

uses Windows, Messages, AXHD;

// Board Number를 이용하여 Board Address 찾기
function AxlGetBoardAddress (lBoardNo : LongInt; upBoardAddress : PDWord) : DWord; stdcall;
// Board Number를 이용하여 Board ID 찾기
function AxlGetBoardID (lBoardNo : LongInt; upBoardID : PDWord) : DWord; stdcall;
// Board Number를 이용하여 Board Version 찾기
function AxlGetBoardVersion (lBoardNo : LongInt; upBoardVersion : PDWord) : DWord; stdcall;
// Board Number와 Module Position을 이용하여 Module ID 찾기
function AxlGetModuleID (lBoardNo : LongInt; lModulePos : LongInt; upModuleID : PDWord) : DWord; stdcall;
// Board Number와 Module Position을 이용하여 Module Version 찾기
function AxlGetModuleVersion (lBoardNo : LongInt; lModulePos : LongInt; upModuleVersion : PDWord) : DWord; stdcall;
// Board Number와 Module Position을 이용하여 Network Node 정보 확인
function AxlGetModuleNodeInfo(lBoardNo : LongInt; lModulePos : LongInt; lpNetNo : PLongInt; upNodeAddr : PDWord) : DWord; stdcall;

// Board에 내장된 범용 Data Flash Write (PCI-R1604[RTEX master board]전용)
// lPageAddr(0 ~ 199)
// lByteNum(1 ~ 120)
// 주의) Flash에 데이타를 기입할 때는 일정 시간(최대 17mSec)이 소요되기때문에 연속 쓰기시 지연 시간이 필요함.
function AxlSetDataFlash (lBoardNo : LongInt; lPageAddr : LongInt; lBytesNum : LongInt; bpSetData : PByte) : DWord; stdcall;
// Board에 내장된 범용 Data Flash Read(PCI-R1604[RTEX master board]전용)
// lPageAddr(0 ~ 199)
// lByteNum(1 ~ 120)
function AxlGetDataFlash (lBoardNo : LongInt; lPageAddr : LongInt; lBytesNum : LongInt; bpSetData : PByte) : DWord; stdcall;

// Board Number와 Module Position을 이용하여 AIO Module Number 찾기
function AxaInfoGetModuleNo (lBoardNo : LongInt; lModulePos : LongInt; lpModuleNo : PLongInt) : DWord; stdcall;
// Board Number와 Module Position을 이용하여 DIO Module Number 찾기
function AxdInfoGetModuleNo (lBoardNo : LongInt; lModulePos : LongInt; lpModuleNo : PLongInt) : DWord; stdcall;

// 지정 축에 IPCOMMAND Setting
function AxmSetCommand (lAxisNo : LongInt; sCommand : Byte) : DWord; stdcall;
// 지정 축에 8bit IPCOMMAND Setting
function AxmSetCommandData08 (lAxisNo : LongInt; sCommand : Byte; uData : DWord) : DWord; stdcall;
// 지정 축에 8bit IPCOMMAND 가져오기
function AxmGetCommandData08 (lAxisNo : LongInt; sCommand : Byte; upData : PDWord) : DWord; stdcall;
// 지정 축에 16bit IPCOMMAND Setting
function AxmSetCommandData16 (lAxisNo : LongInt; sCommand : Byte; uData : DWord) : DWord; stdcall;
// 지정 축에 16bit IPCOMMAND 가져오기
function AxmGetCommandData16 (lAxisNo : LongInt; sCommand : Byte; upData : PDWord) : DWord; stdcall;
// 지정 축에 24bit IPCOMMAND Setting
function AxmSetCommandData24 (lAxisNo : LongInt; sCommand : Byte; uData : DWord) : DWord; stdcall;
// 지정 축에 24bit IPCOMMAND 가져오기
function AxmGetCommandData24 (lAxisNo : LongInt; sCommand : Byte; upData : PDWord) : DWord; stdcall;
// 지정 축에 32bit IPCOMMAND Setting
function AxmSetCommandData32 (lAxisNo : LongInt; sCommand : Byte; uData : DWord) : DWord; stdcall;
// 지정 축에 32bit IPCOMMAND 가져오기
function AxmGetCommandData32 (lAxisNo : LongInt; sCommand : Byte; upData : PDWord) : DWord; stdcall;

// 지정 축에 QICOMMAND Setting
function AxmSetCommandQi (lAxisNo : LongInt; sCommand : Byte) : DWord; stdcall;
// 지정 축에 8bit IPCOMMAND Setting
function AxmSetCommandData08Qi (lAxisNo : LongInt; sCommand : Byte; uData : DWord) : DWord; stdcall;
// 지정 축에 8bit IPCOMMAND 가져오기
function AxmGetCommandData08Qi (lAxisNo : LongInt; sCommand : Byte; upData : PDWord) : DWord; stdcall;
// 지정 축에 16bit IPCOMMAND Setting
function AxmSetCommandData16Qi (lAxisNo : LongInt; sCommand : Byte; uData : DWord) : DWord; stdcall;
// 지정 축에 16bit IPCOMMAND 가져오기
function AxmGetCommandData16Qi (lAxisNo : LongInt; sCommand : Byte; upData : PDWord) : DWord; stdcall;
// 지정 축에 24bit IPCOMMAND Setting
function AxmSetCommandData24Qi (lAxisNo : LongInt; sCommand : Byte; uData : DWord) : DWord; stdcall;
// 지정 축에 24bit IPCOMMAND 가져오기
function AxmGetCommandData24Qi (lAxisNo : LongInt; sCommand : Byte; upData : PDWord) : DWord; stdcall;
// 지정 축에 32bit IPCOMMAND Setting
function AxmSetCommandData32Qi (lAxisNo : LongInt; sCommand : Byte; uData : DWord) : DWord; stdcall;
// 지정 축에 32bit IPCOMMAND 가져오기
function AxmGetCommandData32Qi (lAxisNo : LongInt; sCommand : Byte; upData : PDWord) : DWord; stdcall;

// 지정 축에 Port Data 가져오기 - IP
function AxmGetPortData(lAxisNo : LongInt; wOffset : WORD; upData : PDWord) : DWord; stdcall;
// 지정 축에 Port Data Setting - IP
function AxmSetPortData(lAxisNo : LongInt; wOffset : WORD; uData : DWord) : DWord; stdcall;

// 지정 축에 Port Data 가져오기 - QI
function AxmGetPortDataQi(lAxisNo : LongInt; wOffset : WORD; upData : PDWord) : DWord; stdcall;
// 지정 축에 Port Data Setting - QI
function AxmSetPortDataQi(lAxisNo : LongInt; wOffset : WORD; uData : DWord) : DWord; stdcall;

// 지정 축에 스크립트를 설정한다. - IP
// sc    : 스크립트 번호 (1 - 4)
// event : 발생할 이벤트 SCRCON 을 정의한다.
//         이벤트 설정 축갯수설정, 이벤트 발생할 축, 이벤트 내용 1,2 속성 설정한다.
// cmd   : 어떤 내용을 바꿀것인지 선택 SCRCMD를 정의한다.
// data  : 어떤 Data를 바꿀것인지 선택
function AxmSetScriptCaptionIp(lAxisNo : LongInt; sc : LongInt; event : DWord; data : DWord) : DWord; stdcall;
// 지정 축에 스크립트를 반환한다. - IP
function AxmGetScriptCaptionIp(lAxisNo : LongInt; sc : LongInt; event : PDWord; data : PDWord) : DWord; stdcall;

// 지정 축에 스크립트를 설정한다. - QI
// sc    : 스크립트 번호 (1 - 4)
// event : 발생할 이벤트 SCRCON 을 정의한다.
//         이벤트 설정 축갯수설정, 이벤트 발생할 축, 이벤트 내용 1,2 속성 설정한다.
// cmd   : 어떤 내용을 바꿀것인지 선택 SCRCMD를 정의한다.
// data  : 어떤 Data를 바꿀것인지 선택
function AxmSetScriptCaptionQi(lAxisNo : LongInt; sc : LongInt; event : DWord; cmd : DWord; data : DWord) : DWord; stdcall;
// 지정 축에 스크립트를 반환한다. - QI
function AxmGetScriptCaptionQi(lAxisNo : LongInt; sc : LongInt; event : PDWord; cmd : PDWord; data : PDWord) : DWord; stdcall;

// 지정 축에 스크립트 내부 Queue Index를 Clear 시킨다.
// uSelect IP. 
// uSelect(0): 스크립트 Queue Index 를 Clear한다.
//        (1): 캡션 Queue를 Index Clear한다.

// uSelect QI. 
// uSelect(0): 스크립트 Queue 1 Index 을 Clear한다.
//        (1): 스크립트 Queue 2 Index 를 Clear한다.

function AxmSetScriptCaptionQueueClear(lAxisNo : LongInt; uSelect : DWord) : DWord; stdcall;

// 지정 축에 스크립트 내부 Queue의 Index 반환한다. 
// uSelect IP
// uSelect(0): 스크립트 Queue Index를 읽어온다.
//        (1): 캡션 Queue Index를 읽어온다.

// uSelect QI. 
// uSelect(0): 스크립트 Queue 1 Index을 읽어온다.
//        (1): 스크립트 Queue 2 Index를 읽어온다.
function AxmGetScriptCaptionQueueCount(lAxisNo : LongInt; updata : PDWord; uSelect : DWord) : DWord; stdcall;

// 지정 축에 스크립트 내부 Queue의 Data갯수 반환한다. 
// uSelect IP
// uSelect(0): 스크립트 Queue Data 를 읽어온다.
//        (1): 캡션 Queue Data를 읽어온다.

// uSelect QI.
// uSelect(0): 스크립트 Queue 1 Data 읽어온다.
//        (1): 스크립트 Queue 2 Data 읽어온다.
function AxmGetScriptCaptionQueueDataCount(lAxisNo : LongInt; updata : PDWord; uSelect : DWord) : DWord; stdcall;

// 내부 데이타를 읽어온다.
function AxmGetOptimizeDriveData(lAxisNo : LongInt; dMinVel : Double; dVel : Double; dAccel : Double; dDecel : Double; 
        wRangeData : PWord; wStartStopSpeedData : PWord; wObjectSpeedData : PWord; wAccelRate : PWord; wDecelRate : PWord) : DWord; stdcall;

// 보드내에 레지스터를 Byte단위로 설정 및 확인한다.
function AxmBoardWriteByte(lBoardNo : LongInt; wOffset : Word; byData : Byte) : DWord; stdcall;
function AxmBoardReadByte(lBoardNo : LongInt; wOffset : Word; byData : PByte) : DWord; stdcall;

// 보드내에 레지스터를 Word단위로 설정 및 확인한다.
function AxmBoardWriteWord(lBoardNo : LongInt; wOffset : Word; wData : Word) : DWord; stdcall;
function AxmBoardReadWord(lBoardNo : LongInt; wOffset : Word; wData : PWord) : DWord; stdcall;

// 보드내에 레지스터를 DWord단위로 설정 및 확인한다.
function AxmBoardWriteDWord(lBoardNo : LongInt; wOffset : Word; dwData : DWord) : DWord; stdcall;
function AxmBoardReadDWord(lBoardNo : LongInt; wOffset : Word; dwData : PDWord) : DWord; stdcall;

// 보드내에 모듈에 레지스터를 Byte설정 및 확인한다.
function AxmModuleWriteByte(lBoardNo : LongInt; lModulePos : LongInt; wOffset : Word; byData : Byte) : DWord; stdcall;
function AxmModuleReadByte(lBoardNo : LongInt; lModulePos : LongInt; wOffset : Word; byData : PByte) : DWord; stdcall;

// 보드내에 모듈에 레지스터를 Word설정 및 확인한다.
function AxmModuleWriteWord(lBoardNo : LongInt; lModulePos : LongInt; wOffset : Word; wData : Word) : DWord; stdcall;
function AxmModuleReadWord(lBoardNo : LongInt; lModulePos : LongInt; wOffset : Word; wData : PWord) : DWord; stdcall;

// 보드내에 모듈에 레지스터를 DWord설정 및 확인한다.
function AxmModuleWriteDWord(lBoardNo : LongInt; lModulePos : LongInt; wOffset : Word; dwData : DWord) : DWord; stdcall;
function AxmModuleReadDWord(lBoardNo : LongInt; lModulePos : LongInt; wOffset : Word; dwData : PDWord) : DWord; stdcall;

// 외부 위치 비교기에 값을 설정한다.(Pos = Unit)
function AxmStatusSetActComparatorPos(lAxisNo : LongInt; dPos : Double) : DWord; stdcall;
// 외부 위치 비교기에 값을 반환한다.(Positon = Unit)
function AxmStatusGetActComparatorPos(lAxisNo : LongInt; dpPos : PDouble) : DWord; stdcall;

// 내부 위치 비교기에 값을 설정한다.(Pos = Unit)
function AxmStatusSetCmdComparatorPos(lAxisNo : LongInt; dPos : Double) : DWord; stdcall;
// 내부 위치 비교기에 값을 반환한다.(Pos = Unit)
function AxmStatusGetCmdComparatorPos(lAxisNo : LongInt; dpPos : PDouble) : DWord; stdcall;

//======= 추가 함수 =========================================================================================================

// 직선 보간 을 속도만 가지고 무한대로 증가한다.
// 속도 비율대로 거리를 넣어주어야 한다. 
function AxmLineMoveVel(lCoord : LongInt; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;

//========= 센서 위치 구동 함수( 필독: IP만가능 , QI에는 기능없음)=========================================================================

// 지정 축의 Sensor 신호의 사용 유무 및 신호 입력 레벨을 설정한다.
// 사용 유무 LOW(0), HIGH(1), UNUSED(2), USED(3)
function AxmSensorSetSignal(lAxisNo : LongInt; uLevel : DWord) : DWord; stdcall;
// 지정 축의 Sensor 신호의 사용 유무 및 신호 입력 레벨을 반환한다.
function AxmSensorGetSignal(lAxisNo : LongInt; upLevel : PDWord) : DWord; stdcall;
// 지정 축의 Sensor 신호의 입력 상태를 반환한다
function AxmSensorReadSignal(lAxisNo : LongInt; upStatus : PDWord) : DWord; stdcall;

// 지정 축의 설정된 속도와 가속율로 센서 위치 드라이버를 구동한다.
// Sensor 신호의 Active level입력 이후 상대 좌표로 설정된 거리만큼 구동후 정지한다.
// 펄스가 출력되는 시점에서 함수를 벗어난다.
// lMethod :  0 - 일반 구동, 1 - 센서 신호 검출 전은 저속 구동. 신호 검출 후 일반 구동
//            2 - 저속 구동
function AxmSensorMovePos(lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double; lMethod : LongInt) : DWord; stdcall;

// 지정 축의 설정된 속도와 가속율로 센서 위치 드라이버를 구동한다.
// Sensor 신호의 Active level입력 이후 상대 좌표로 설정된 거리만큼 구동후 정지한다.
// 펄스 출력이 종료되는 시점에서 함수를 벗어난다.
function AxmSensorStartMovePos(lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double; lMethod : LongInt) : DWord; stdcall;

// 원점검색 진행스탭 변화의 기록을 반환한다.
// lpStepCount      : 기록된 Step의 개수
// upMainStepNumber : 기록된 MainStepNumber 정보의 배열포인트
// upStepNumber     : 기록된 StepNumber 정보의 배열포인트
// upStepBranch     : 기록된 Step별 Branch 정보의 배열포인트
// 주의: 배열개수는 50개로 고정
function AxmHomeGetStepTrace(lAxisNo : LongInt; lpStepCount : PLongInt; upMainStepNumber : PDWord; upStepNumber : PDWord; upStepBranch : PDWord) : DWord; stdcall;

//=======추가 홈 서치 (PI-N804/404에만 해당됨.)=================================================================================
// 사용자가 지정한 축의 홈설정 파라메타를 설정한다.(QI칩 전용 레지스터 이용).
// uZphasCount : 홈 완료후에 Z상 카운트(0 - 15)
// lHomeMode   : 홈 설정 모드( 0 - 12)
// lClearSet   : 위치 클리어 , 잔여펄스 클리어 사용 선택 (0 - 3)
//               0: 위치클리어 사용않함, 잔여펄스 클리어 사용 안함
//                 1: 위치클리어 사용함, 잔여펄스 클리어 사용 안함
//               2: 위치클리어 사용안함, 잔여펄스 클리어 사용함
//               3: 위치클리어 사용함, 잔여펄스 클리어 사용함.
// dOrgVel : 홈관련 Org  Speed 설정 
// dLastVel: 홈관련 Last Speed 설정 
function AxmHomeSetConfig(lAxisNo : LongInt; uZphasCount : DWord; lHomeMode : LongInt; lClearSet : LongInt; dOrgVel : Double; dLastVel : Double; dLeavePos : Double) : DWord; stdcall;
// 사용자가 지정한 축의 홈설정 파라메타를 반환한다.
function AxmHomeGetConfig(lAxisNo : LongInt; upZphasCount : PDword; lpHomeMode : PLongInt; lpClearSet : PLongInt; dpOrgVel : PDouble; dpLastVel : PDouble; dpLeavePos : PDouble) : DWord; stdcall;

// 사용자가 지정한 축의 홈 서치를 시작한다.
// lHomeMode 사용시 설정 : 0 - 5 설정 (Move Return후에 Search를  시작한다.)
// lHomeMode -1로 그대로 사용시 HomeConfig에서 사용한대로 그대로 설정됨.
// 구동방향      : Vel값이 양수이면 CW, 음수이면 CCW.
function AxmHomeSetMoveSearch(lAxisNo : LongInt; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;

// 사용자가 지정한 축의 홈 리턴을 시작한다.
// lHomeMode 사용시 설정 : 0 - 12 설정 
// lHomeMode -1로 그대로 사용시 HomeConfig에서 사용한대로 그대로 설정됨.
// 구동방향      : Vel값이 양수이면 CW, 음수이면 CCW.
function AxmHomeSetMoveReturn(lAxisNo : LongInt; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;

// 사용자가 지정한 축의 홈 이탈을 시작한다.
// 구동방향      : Vel값이 양수이면 CW, 음수이면 CCW.
function AxmHomeSetMoveLeave(lAxisNo : LongInt; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;

// 사용자가 지정한 다축의 홈 서치을 시작한다.
// lHomeMode 사용시 설정 : 0 - 5 설정 (Move Return후에 Search를  시작한다.)
// lHomeMode -1로 그대로 사용시 HomeConfig에서 사용한대로 그대로 설정됨.
// 구동방향      : Vel값이 양수이면 CW, 음수이면 CCW.
function AxmHomeSetMultiMoveSearch(lArraySize : LongInt; lpAxesNo : PLongInt; dpVel : PDouble; dpAccel : PDouble; dpDecel : PDouble) : DWord; stdcall;

//지정된 좌표계의 구동 속도 프로파일 모드를 설정한다.
// (주의점 : 반드시 축맵핑 하고 사용가능)
  // ProfileMode : '0' - 대칭 Trapezode
  //               '1' - 비대칭 Trapezode
  //               '2' - 대칭 Quasi-S Curve
  //               '3' - 대칭 S Curve
  //               '4' - 비대칭 S Curve
function AxmContiSetProfileMode(lCoord : LongInt; uProfileMode : DWord) : DWord; stdcall;
// 지정된 좌표계의 구동 속도 프로파일 모드를 반환한다.
function AxmContiGetProfileMode(lCoord : LongInt; upProfileMode : PDWord) : DWord; stdcall;

//========== DIO 인터럽트 플래그 레지스트 읽기
// 지정한 입력 접점 모듈, Interrupt Flag Register의 Offset 위치에서 bit 단위로 인터럽트 발생 상태 값을 읽음
function AxdiInterruptFlagReadBit(lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;
// 지정한 입력 접점 모듈, Interrupt Flag Register의 Offset 위치에서 byte 단위로 인터럽트 발생 상태 값을 읽음
function AxdiInterruptFlagReadByte(lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;
// 지정한 입력 접점 모듈, Interrupt Flag Register의 Offset 위치에서 word 단위로 인터럽트 발생 상태 값을 읽음
function AxdiInterruptFlagReadWord(lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;
// 지정한 입력 접점 모듈, Interrupt Flag Register의 Offset 위치에서 double word 단위로 인터럽트 발생 상태 값을 읽음
function AxdiInterruptFlagReadDword(lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;
// 전체 입력 접점 모듈, Interrupt Flag Register의 Offset 위치에서 bit 단위로 인터럽트 발생 상태 값을 읽음
function AxdiInterruptFlagRead(lOffset : LongInt; upValue : PDWord) : DWord; stdcall;


//========= 로그 관련 함수 ==========================================================================================    
// 현재 자동으로 설정됨.
// 설정 축의 함수 실행 결과를 EzSpy에서 모니터링 할 수 있도록 설정 또는 해제하는 함수이다.
// uUse : 사용 유무 => DISABLE(0), ENABLE(1)
function AxmLogSetAxis(lAxisNo : LongInt; uUse : DWord) : DWord; stdcall;

// EzSpy에서의 설정 축 함수 실행 결과 모니터링 여부를 확인하는 함수이다.
function AxmLogGetAxis(lAxisNo : LongInt; upUse : PDWord) : DWord; stdcall;

//aaaaaaaa=== 로그 출력 관련 함수
//지정한 입력 채널의 EzSpy에 로그 출력 여부를 설정한다.
function AxaiLogSetChannel(lChannelNo : LongInt; uUse : DWord) : DWord; stdcall;
//지정한 입력 채널의 EzSpy에 로그 출력 여부를 확인한다.
function AxaiLogGetChannel(lChannelNo : LongInt; upUse : PDWord) : DWord; stdcall;

//==지정한 출력 채널의 EzSpy 로그 출력 
//지정한 출력 채널의 EzSpy에 로그 출력 여부를 설정한다.
function AxaoLogSetChannel(lChannelNo : LongInt; uUse : DWord) : DWord; stdcall;
//지정한 출력 채널의 EzSpy에 로그 출력 여부를 확인한다.
function AxaoLogGetChannel(lChannelNo : LongInt; upUse : PDWord) : DWord; stdcall;

//==Log
// 지정한 모듈의 EzSpy에 로그 출력 여부 설정
function AxdLogSetModule(lModuleNo : LongInt; uUse : DWord) : DWord; stdcall;
// 지정한 모듈의 EzSpy에 로그 출력 여부 확인
function AxdLogGetModule(lModuleNo : LongInt; upUse : PDWord) : DWord; stdcall;

// 지정한 보드가 RTEX 모드일 때 그 보드의 firmware 버전을 확인한다.
function AxlGetFirmwareVersion(lBoardNo : LongInt; szVersion : PChar) : DWord; stdcall;
// 지정한 보드로 Firmware를 전송 한다.
function AxlSetFirmwareCopy(lBoardNo : LongInt; wData : PWord; wCmdData : PWord) : DWord; stdcall;
// 지정한 보드로 Firmware Update를 수행한다.
function AxlSetFirmwareUpdate(lBoardNo : LongInt) : DWord; stdcall;
// 지정한 보드의 현재 RTEX 초기화 상태를 확인 한다.
function AxlCheckStatus(lBoardNo : LongInt; dwStatus : PDWord) : DWord; stdcall;
// 지정한 축에 RTEX Master board에 범용 명령을 실행 합니다.
function AxlRtexUniversalCmd(lBoardNo : LongInt; wCmd : Word; wOffset : Word; wData : PWord) : DWord; stdcall;
// 지정한 축의 RTEX 통신 명령을 실행한다.
function AxmRtexSlaveCmd(lAxisNo : LongInt; dwCmdCode : DWord; dwTypeCode : DWord; dwIndexCode : DWord; dwCmdConfigure : DWord; dwValue : DWord) : DWord; stdcall;
// 지정한 축에 실행한 RTEX 통신 명령의 결과값을 확인한다.
function AxmRtexGetSlaveCmdResult(lAxisNo : LongInt; dwIndex : PDWord; dwValue : PDWord) : DWord; stdcall;
// 지정한 축에 RTEX 상태 정보를 확인한다.
function AxmRtexGetAxisStatus(lAxisNo : LongInt; dwStatus : PDWord) : DWord; stdcall;
// 지정한 축에 RTEX 통신 리턴 정보를 확인한다.(Actual position, Velocity, Torque)
function AxmRtexGetAxisReturnData(lAxisNo : LongInt;  dwReturn1 : PDWord; dwReturn2 : PDWord; dwReturn3 : PDWord) : DWord; stdcall;
// 지정한 축에 RTEX Slave 축의 현재 상태 정보를 확인한다.(mechanical, Inposition and etc)
function AxmRtexGetAxisSlaveStatus(lAxisNo : LongInt; dwStatus : PDWord) : DWord; stdcall;

// 지정한 축에 MLII Slave 축에 범용 네트웍 명령어를 기입한다.
function AxmSetAxisCmd(lAxisNo : LongInt; tagCommand : PDWord) : DWord; stdcall;
// 지정한 축에 MLII Slave 축에 범용 네트웍 명령의 결과를 확인한다.
function AxmGetAxisCmdResult(lAxisNo : LongInt; tagCommand : PDWORD) : DWord; stdcall;

function AxlGetDpRamData(lBoardNo : LongInt; wAddress : Word; dwpRdData : PDWord) : DWord; stdcall;
function AxlBoardReadDpramWord(lBoardNo : LongInt; wOffset : Word; dwpRdData : PDWord) : DWord; stdcall;

function AxlSetSendBoardCommand(lBoardNo : LongInt; dwCommand : DWord; dwpSendData : PDWord; dwLength : DWord) : DWord; stdcall;
function AxlGetResponseBoardCommand(lBoardNo : LongInt; dwpReadData : PDWord) : DWord; stdcall;

// Network Type Master 보드에서 Slave 들의 Firmware Version을 읽어 오는 함수.
// ucaFirmwareVersion unsigned char 형의 Array로 선언하고 크기가 4이상이 되도록 선언 해야 한다.
function AxmInfoGetFirmwareVersion(lAxisNo : LongInt;  ucaFirmwareVersion : PWord) : DWord; stdcall;
function AxaInfoGetFirmwareVersion(lModuleNo : LongInt; ucaFirmwareVersion : PWord) : DWord; stdcall;
function AxdInfoGetFirmwareVersion(lModuleN : LongInt; ucaFirmwareVersion : PWord) : DWord; stdcall;
    
//======== PCI-R1604-MLII 전용 함수=========================================================================== 
// INTERPOLATE and LATCH Command의 Option Field의 Torq Feed Forward의 값을 설정 하도록 합니다.
// 기본값은 MAX로 설정되어 있습니다.
// 설정값은 0 ~ 4000H까지 설정 할 수 있습니다.
// 설정값은 4000H이상으로 설정하면 설정은 그 이상으로 설정되나 동작은 4000H값이 적용 됩니다.
function AxmSetTorqFeedForward(lAxisNo : LongInt; dwTorqFeedForward : DWord) : DWord; stdcall;

// INTERPOLATE and LATCH Command의 Option Field의 Torq Feed Forward의 값을 읽어오는 함수 입니다.
// 기본값은 MAX로 설정되어 있습니다.
function AxmGetTorqFeedForward(lAxisNo : LongInt; dwpTorqFeedForward : PDWord) : DWord; stdcall;

// INTERPOLATE and LATCH Command의 VFF Field의 Velocity Feed Forward의 값을 설정 하도록 합니다.
// 기본값은 '0'로 설정되어 있습니다.
// 설정값은 0 ~ FFFFH까지 설정 할 수 있습니다.
function AxmSetVelocityFeedForward(lAxisNo : LongInt; dwVelocityFeedForward : DWord) : DWord; stdcall;

// INTERPOLATE and LATCH Command의 VFF Field의 Velocity Feed Forward의 값을 읽어오는 함수 입니다.
function AxmGetVelocityFeedForward(lAxisNo : LongInt; dwpVelocityFeedForward : PDWord) : DWord; stdcall;

// Encoder type을 설정한다.
// 기본값은 0(TYPE_INCREMENTAL)로 설정되어 있습니다.
// 설정값은 0 ~ 1까지 설정 할 수 있습니다.
// 설정값 : 0(TYPE_INCREMENTAL), 1(TYPE_ABSOLUTE).
function AxmSignalSetEncoderType(lAxisNo : LongInt; dwEncoderType : DWord) : DWord; stdcall;

// Encoder type을 확인한다.
function AxmSignalGetEncoderType(lAxisNo : LongInt; dwpEncoderType : PDWord) : DWord; stdcall;

// Slave Firmware Update를 위해 추가
//function AxmSetSendAxisCommand(lAxisNo : LongInt; wCommand : Word; wpSendData : PDWord; wLength : Word) : DWord; stdcall;

//======== PCI-R1604-RTEX, RTEX-PM 전용 함수============================================================== 
// 범용 입력 2,3번 입력시 JOG 구동 속도를 설정한다. 
// 구동에 관련된 모든 설정(Ex, PulseOutMethod, MoveUnitPerPulse 등)들이 완료된 이후 한번만 실행하여야 한다.
function AxmMotSetUserMotion(lAxisNo : LongInt; dVelocity : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;

// 범용 입력 2,3번 입력시 JOG 구동 동작 사용 가부를 설정한다.
// 설정값 :  0(DISABLE), 1(ENABLE)
function AxmMotSetUserMotionUsage(lAxisNo: LongInt; dwUsage : DWord) : DWord; stdcall;

// MPGP 입력을 사용하여 Load/UnLoad 위치를 자동으로 이동하는 기능 설정. 
function  AxmMotSetUserPosMotion(lAxisNo : LongInt; dVelocity : Double; dAccel : Double; dDecel : Double; dLoadPos : Double; dUnLoadPos : Double; dwFilter : DWord; dwDelay : DWord) : DWord; stdcall;

// MPGP 입력을 사용하여 Load/UnLoad 위치를 자동으로 이동하는 기능 설정. 
// 설정값 :  0(DISABLE), 1(Position 기능 A 사용), 2(Position 기능 B 사용)
function  AxmMotSetUserPosMotionUsage(lAxisNo : LongInt; dwUsage : DWord) : DWord; stdcall;
//======================================================================================================== 

//======== SIO-CN2CH, 절대 위치 트리거 기능 모듈 전용 함수================================================ 
function AxcKeWriteRamDataAddr(lChannelNo : LongInt; dwAddr : DWord; dwData : DWord) : DWord; stdcall;
function AxcKeReadRamDataAddr(lChannelNo : LongInt; dwAddr : DWord; dwpData : PDWord) : DWord; stdcall;
function AxcKeResetRamDataAll(lModuleNo : LongInt; dwData : DWord) : DWord; stdcall;
function AxcTriggerSetTimeout(lChannelNo : LongInt; dwTimeout : DWord) : DWord; stdcall;
function AxcTriggerGetTimeout(lChannelNo : LongInt; dwpTimeout : PDWord) : DWord; stdcall;
function AxcStatusGetWaitState(lChannelNo : LongInt; dwpState : PDWord) : DWord; stdcall;
function AxcStatusSetWaitState(lChannelNo : LongInt; dwState : DWord) : DWord; stdcall;
//======================================================================================================== 
	
//======== PCI-N804/N404 전용, Sequence Motion ===================================================================
// Sequence Motion의 축 정보를 설정 합니다. (최소 1축)
// lSeqMapNo : 축 번호 정보를 담는 Sequence Motion Index Point
// lSeqMapSize : 축 번호 갯수
// long* LSeqAxesNo : 축 번호 배열
function AxmSeqSetAxisMap(lSeqMapNo : LongInt; lSeqMapSize : LongInt; lSeqAxesNo : PLongInt) : DWord; stdcall;
function AxmSeqGetAxisMap(lSeqMapNo : LongInt; lSeqMapSize : PLongInt; lSeqAxesNo : PLongInt) : DWord; stdcall;

// Sequence Motion의 기준(Master) 축을 설정 합니다. 
// 반드시 AxmSeqSetAxisMap(...) 에 설정된 축 내에서 설정하여야 합니다.
function AxmSeqSetMasterAxisNo(lSeqMapNo : LongInt; lMasterAxisNo : LongInt) : DWord; stdcall;

// Sequence Motion의 Node 적재 시작을 라이브러리에 알립니다.
function AxmSeqBeginNode(lSeqMapNo : LongInt) : DWord; stdcall;

// Sequence Motion의 Node 적재 종료를 라이브러리에 알립니다.
function AxmSeqEndNode(lSeqMapNo : LongInt) : DWord; stdcall;

// Sequence Motion의 구동을 시작 합니다.
function AxmSeqStart(lSeqMapNo : LongInt; dwStartOption : DWord) : DWord; stdcall;

// Sequence Motion의 각 Profile Node 정보를 라이브러리에 입력 합니다.
// 만약 1축 Sequence Motion을 사용하더라도, *dPosition는 1개의 Array로 지정하여 주시기 바랍니다.
function AxmSeqAddNode(lSeqMapNo : LongInt; dPosition : PDouble; dVelocity : Double; dAcceleration : Double; dDeceleration : Double; dNextVelocity : Double) : DWord; stdcall;

// Sequence Motion이 구동 시 현재 실행 중인 Node Index를 알려 줍니다.
function AxmSeqGetNodeNum(lSeqMapNo : LongInt; lCurNodeNo : PLongInt) : DWord; stdcall;

// Sequence Motion의 총 Node Count를 확인 합니다.
function AxmSeqGetTotalNodeNum(lSeqMapNo : LongInt; lTotalNodeCnt : PLongInt) : DWord; stdcall;

// Sequence Motion이 현재 구동 중인지 확인 합니다.
// dwInMotion : 0(구동 종료), 1(구동 중)
function AxmSeqIsMotion(lSeqMapNo : LongInt; dwInMotion : PDWord) : DWord; stdcall;

// Sequence Motion의 Memory를 Clear 합니다.
// AxmSeqSetAxisMap(...), AxmSeqSetMasterAxisNo(...) 에서 설정된 값은 유지됩니다.
function AxmSeqWriteClear(lSeqMapNo : LongInt) : DWord; stdcall;

// Sequence Motion의 구동을 종료 합니다.
// dwStopMode : 0(EMERGENCY_STOP), 1(SLOWDOWN_STOP) 
function AxmSeqStop(lSeqMapNo : LongInt; dwStopMode : DWord) : DWord; stdcall;
//======================================================================================================== 


implementation
const

    dll_name    = 'AXL.dll';

    function AxlGetBoardAddress; external dll_name name 'AxlGetBoardAddress';
    function AxlGetBoardID; external dll_name name 'AxlGetBoardID';
    function AxlGetBoardVersion; external dll_name name 'AxlGetBoardVersion';
    function AxlGetModuleID; external dll_name name 'AxlGetModuleID';
    function AxlGetModuleVersion; external dll_name name 'AxlGetModuleVersion';
    function AxlGetModuleNodeInfo; external dll_name name 'AxlGetModuleNodeInfo';        
    function AxlSetDataFlash; external dll_name name 'AxlSetDataFlash';
    function AxlGetDataFlash; external dll_name name 'AxlGetDataFlash';        
    function AxaInfoGetModuleNo; external dll_name name 'AxaInfoGetModuleNo';
    function AxdInfoGetModuleNo; external dll_name name 'AxdInfoGetModuleNo';    
    function AxmSetCommand; external dll_name name 'AxmSetCommand';
    function AxmSetCommandData08; external dll_name name 'AxmSetCommandData08';
    function AxmGetCommandData08; external dll_name name 'AxmGetCommandData08';
    function AxmSetCommandData16; external dll_name name 'AxmSetCommandData16';
    function AxmGetCommandData16; external dll_name name 'AxmGetCommandData16';
    function AxmSetCommandData24; external dll_name name 'AxmSetCommandData24';
    function AxmGetCommandData24; external dll_name name 'AxmGetCommandData24';
    function AxmSetCommandData32; external dll_name name 'AxmSetCommandData32';
    function AxmGetCommandData32; external dll_name name 'AxmGetCommandData32';    
    function AxmSetCommandQi; external dll_name name 'AxmSetCommandQi';
    function AxmSetCommandData08Qi; external dll_name name 'AxmSetCommandData08Qi';
    function AxmGetCommandData08Qi; external dll_name name 'AxmGetCommandData08Qi';
    function AxmSetCommandData16Qi; external dll_name name 'AxmSetCommandData16Qi';
    function AxmGetCommandData16Qi; external dll_name name 'AxmGetCommandData16Qi';
    function AxmSetCommandData24Qi; external dll_name name 'AxmSetCommandData24Qi';
    function AxmGetCommandData24Qi; external dll_name name 'AxmGetCommandData24Qi';
    function AxmSetCommandData32Qi; external dll_name name 'AxmSetCommandData32Qi';
    function AxmGetCommandData32Qi; external dll_name name 'AxmGetCommandData32Qi';    
    function AxmGetPortData; external dll_name name 'AxmGetPortData';
    function AxmSetPortData; external dll_name name 'AxmSetPortData';
    function AxmGetPortDataQi; external dll_name name 'AxmGetPortDataQi';
    function AxmSetPortDataQi; external dll_name name 'AxmSetPortDataQi';    
    function AxmSetScriptCaptionIp; external dll_name name 'AxmSetScriptCaptionIp';
    function AxmGetScriptCaptionIp; external dll_name name 'AxmGetScriptCaptionIp';
    function AxmSetScriptCaptionQi; external dll_name name 'AxmSetScriptCaptionQi';
    function AxmGetScriptCaptionQi; external dll_name name 'AxmGetScriptCaptionQi';
    function AxmSetScriptCaptionQueueClear; external dll_name name 'AxmSetScriptCaptionQueueClear';
    function AxmGetScriptCaptionQueueCount; external dll_name name 'AxmGetScriptCaptionQueueCount';
    function AxmGetScriptCaptionQueueDataCount; external dll_name name 'AxmGetScriptCaptionQueueDataCount';
    function AxmGetOptimizeDriveData; external dll_name name  'AxmGetOptimizeDriveData';
    function AxmBoardWriteByte; external dll_name name 'AxmBoardWriteByte'; 
    function AxmBoardReadByte; external dll_name name 'AxmBoardReadByte'; 
    function AxmBoardWriteWord; external dll_name name 'AxmBoardWriteWord'; 
    function AxmBoardReadWord; external dll_name name 'AxmBoardReadWord'; 
    function AxmBoardWriteDWord; external dll_name name 'AxmBoardWriteDWord'; 
    function AxmBoardReadDWord; external dll_name name 'AxmBoardReadDWord'; 
    function AxmModuleWriteByte; external dll_name name 'AxmModuleWriteByte'; 
    function AxmModuleReadByte; external dll_name name 'AxmModuleReadByte'; 
    function AxmModuleWriteWord; external dll_name name 'AxmModuleWriteWord'; 
    function AxmModuleReadWord; external dll_name name 'AxmModuleReadWord'; 
    function AxmModuleWriteDWord; external dll_name name 'AxmModuleWriteDWord'; 
    function AxmModuleReadDWord; external dll_name name 'AxmModuleReadDWord'; 
    function AxmStatusSetActComparatorPos; external dll_name name 'AxmStatusSetActComparatorPos'; 
    function AxmStatusGetActComparatorPos; external dll_name name 'AxmStatusGetActComparatorPos'; 
    function AxmStatusSetCmdComparatorPos; external dll_name name 'AxmStatusSetCmdComparatorPos'; 
    function AxmStatusGetCmdComparatorPos; external dll_name name 'AxmStatusGetCmdComparatorPos'; 
    function AxmLineMoveVel; external dll_name name 'AxmLineMoveVel'; 
    function AxmSensorSetSignal; external dll_name name 'AxmSensorSetSignal'; 
    function AxmSensorGetSignal; external dll_name name 'AxmSensorGetSignal'; 
    function AxmSensorReadSignal; external dll_name name 'AxmSensorReadSignal'; 
    function AxmSensorMovePos; external dll_name name 'AxmSensorMovePos'; 
    function AxmSensorStartMovePos; external dll_name name 'AxmSensorStartMovePos'; 
    function AxmHomeGetStepTrace; external dll_name name 'AxmHomeGetStepTrace'; 
    function AxmHomeSetConfig; external dll_name name 'AxmHomeSetConfig'; 
    function AxmHomeGetConfig; external dll_name name 'AxmHomeGetConfig'; 
    function AxmHomeSetMoveSearch; external dll_name name 'AxmHomeSetMoveSearch'; 
    function AxmHomeSetMoveReturn; external dll_name name 'AxmHomeSetMoveReturn'; 
    function AxmHomeSetMoveLeave; external dll_name name 'AxmHomeSetMoveLeave'; 
    function AxmHomeSetMultiMoveSearch; external dll_name name 'AxmHomeSetMultiMoveSearch'; 
    function AxmContiSetProfileMode; external dll_name name 'AxmContiSetProfileMode'; 
    function AxmContiGetProfileMode; external dll_name name 'AxmContiGetProfileMode'; 
    function AxdiInterruptFlagReadBit; external dll_name name 'AxdiInterruptFlagReadBit'; 
    function AxdiInterruptFlagReadByte; external dll_name name 'AxdiInterruptFlagReadByte'; 
    function AxdiInterruptFlagReadWord; external dll_name name 'AxdiInterruptFlagReadWord'; 
    function AxdiInterruptFlagReadDword; external dll_name name 'AxdiInterruptFlagReadDword'; 
    function AxdiInterruptFlagRead; external dll_name name 'AxdiInterruptFlagRead'; 
    function AxmLogSetAxis; external dll_name name 'AxmLogSetAxis'; 
    function AxmLogGetAxis; external dll_name name 'AxmLogGetAxis'; 
    function AxaiLogSetChannel; external dll_name name 'AxaiLogSetChannel'; 
    function AxaiLogGetChannel; external dll_name name 'AxaiLogGetChannel'; 
    function AxaoLogSetChannel; external dll_name name 'AxaoLogSetChannel'; 
    function AxaoLogGetChannel; external dll_name name 'AxaoLogGetChannel'; 
    function AxdLogSetModule; external dll_name name 'AxdLogSetModule'; 
    function AxdLogGetModule; external dll_name name 'AxdLogGetModule'; 
    function AxlGetFirmwareVersion; external dll_name name 'AxlGetFirmwareVersion'; 
    function AxlSetFirmwareCopy; external dll_name name 'AxlSetFirmwareCopy'; 
    function AxlSetFirmwareUpdate; external dll_name name 'AxlSetFirmwareUpdate'; 
    function AxlCheckStatus; external dll_name name 'AxlCheckStatus'; 
    function AxlRtexUniversalCmd; external dll_name name 'AxlRtexUniversalCmd'; 
    function AxmRtexSlaveCmd; external dll_name name 'AxmRtexSlaveCmd'; 
    function AxmRtexGetSlaveCmdResult; external dll_name name 'AxmRtexGetSlaveCmdResult'; 
    function AxmRtexGetAxisStatus; external dll_name name 'AxmRtexGetAxisStatus'; 
    function AxmRtexGetAxisReturnData; external dll_name name 'AxmRtexGetAxisReturnData'; 
    function AxmRtexGetAxisSlaveStatus; external dll_name name 'AxmRtexGetAxisSlaveStatus'; 
    function AxmSetAxisCmd; external dll_name name 'AxmSetAxisCmd'; 
    function AxmGetAxisCmdResult; external dll_name name 'AxmGetAxisCmdResult'; 
    function AxlGetDpRamData; external dll_name name 'AxlGetDpRamData'; 
    function AxlBoardReadDpramWord; external dll_name name 'AxlBoardReadDpramWord'; 
    function AxlSetSendBoardCommand; external dll_name name 'AxlSetSendBoardCommand'; 
    function AxlGetResponseBoardCommand; external dll_name name 'AxlGetResponseBoardCommand'; 
    function AxmInfoGetFirmwareVersion; external dll_name name 'AxmInfoGetFirmwareVersion'; 
    function AxaInfoGetFirmwareVersion; external dll_name name 'AxaInfoGetFirmwareVersion'; 
    function AxdInfoGetFirmwareVersion; external dll_name name 'AxdInfoGetFirmwareVersion'; 
    function AxmSetTorqFeedForward; external dll_name name 'AxmSetTorqFeedForward'; 
    function AxmGetTorqFeedForward; external dll_name name 'AxmGetTorqFeedForward'; 
    function AxmSetVelocityFeedForward; external dll_name name 'AxmSetVelocityFeedForward'; 
    function AxmGetVelocityFeedForward; external dll_name name 'AxmGetVelocityFeedForward'; 
    function AxmSignalSetEncoderType; external dll_name name 'AxmSignalSetEncoderType'; 
    function AxmSignalGetEncoderType; external dll_name name 'AxmSignalGetEncoderType'; 
    //function AxmSetSendAxisCommand; external dll_name name 'AxmSetSendAxisCommand';    
    function AxmMotSetUserMotion; external dll_name name 'AxmMotSetUserMotion';
    function AxmMotSetUserMotionUsage; external dll_name name 'AxmMotSetUserMotionUsage';
    function AxmMotSetUserPosMotion; external dll_name name 'AxmMotSetUserPosMotion';
    function AxmMotSetUserPosMotionUsage; external dll_name name 'AxmMotSetUserPosMotionUsage';
    function AxcKeWriteRamDataAddr; external dll_name name 'AxcKeWriteRamDataAddr';
    function AxcKeReadRamDataAddr; external dll_name name 'AxcKeReadRamDataAddr';
    function AxcKeResetRamDataAll; external dll_name name 'AxcKeResetRamDataAll';
    function AxcTriggerSetTimeout; external dll_name name 'AxcTriggerSetTimeout';
    function AxcTriggerGetTimeout; external dll_name name 'AxcTriggerGetTimeout';
    function AxcStatusGetWaitState; external dll_name name 'AxcStatusGetWaitState';
    function AxcStatusSetWaitState; external dll_name name 'AxcStatusSetWaitState';
    function AxmSeqSetAxisMap; external dll_name name 'AxmSeqSetAxisMap';
    function AxmSeqGetAxisMap; external dll_name name 'AxmSeqGetAxisMap';
    function AxmSeqSetMasterAxisNo; external dll_name name 'AxmSeqSetMasterAxisNo';
    function AxmSeqBeginNode; external dll_name name 'AxmSeqBeginNode';
    function AxmSeqEndNode; external dll_name name 'AxmSeqEndNode';
    function AxmSeqStart; external dll_name name 'AxmSeqStart';
    function AxmSeqAddNode; external dll_name name 'AxmSeqAddNode';
    function AxmSeqGetNodeNum; external dll_name name 'AxmSeqGetNodeNum';
    function AxmSeqGetTotalNodeNum; external dll_name name 'AxmSeqGetTotalNodeNum';
    function AxmSeqIsMotion; external dll_name name 'AxmSeqIsMotion';
    function AxmSeqWriteClear; external dll_name name 'AxmSeqWriteClear';
    function AxmSeqStop; external dll_name name 'AxmSeqStop';
end.
