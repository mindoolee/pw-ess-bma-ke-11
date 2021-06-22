/****************************************************************************
*****************************************************************************
**
** File Name
** ---------
**
** AXDev.CS
**
** COPYRIGHT (c) AJINEXTEK Co., LTD
**
*****************************************************************************
*****************************************************************************
**
** Description
** -----------
** Ajinextek Develop Library Header File
** 
**
*****************************************************************************
*****************************************************************************
**
** Source Change Indices
** ---------------------
**
** (None)
**
*****************************************************************************
*****************************************************************************
**
** Website
** ---------------------
**
** http://www.ajinextek.com
**
*****************************************************************************
*****************************************************************************
*/

using System.Runtime.InteropServices;

public class CAXDev
{

//========== 보드 및 모듈 확인함수(Info) - Infomation =================================================================================

    // Board Number를 이용하여 Board Address 찾기
    [DllImport("AXL.dll")] public static extern uint AxlGetBoardAddress(int nBoardNo, ref uint upBoardAddress);
    // Board Number를 이용하여 Board ID 찾기
    [DllImport("AXL.dll")] public static extern uint AxlGetBoardID(int nBoardNo, ref uint upBoardID);
    // Board Number를 이용하여 Board Version 찾기
    [DllImport("AXL.dll")] public static extern uint AxlGetBoardVersion(int nBoardNo, ref uint upBoardVersion);
    // Board Number와 Module Position을 이용하여 Module ID 찾기
    [DllImport("AXL.dll")] public static extern uint AxlGetModuleID(int nBoardNo, int nModulePos, ref uint upModuleID);
    // Board Number와 Module Position을 이용하여 Module Version 찾기
    [DllImport("AXL.dll")] public static extern uint AxlGetModuleVersion(int nBoardNo, int nModulePos, ref uint upModuleVersion);
    // Board Number와 Module Position을 이용하여 Network Node 정보 확인
    [DllImport("AXL.dll")] public static extern uint AxlGetModuleNodeInfo(int nBoardNo, int nModulePos, ref uint upNetNo, ref uint upNodeAddr);

    // Board에 내장된 범용 Data Flash Write (PCI-R1604[RTEX master board]전용)
    // lPageAddr(0 ~ 199)
    // lByteNum(1 ~ 120)
    // 주의) Flash에 데이타를 기입할 때는 일정 시간(최대 17mSec)이 소요되기때문에 연속 쓰기시 지연 시간이 필요함.
    [DllImport("AXL.dll")] public static extern uint AxlSetDataFlash(int lBoardNo, int lPageAddr, int lBytesNum, ref uint upSetData);

    // Board에 내장된 ESTOP 외부 입력 신호를 이용한 InterLock 기능 사용 유무 및 디지털 필터 상수값 정의 (PCI-Rxx00[MLIII master board]전용)
    // 1. 사용 유무
    //	  설명: 기능 사용 설정후 외부에서 ESTOP 신호 인가시 보드에 연결된 모션 제어 노드에 대해서 ESTOP 구동 명령 실행	
    //    0: 기능 사용하지 않음(기본 설정값)
    //    1: 기능 사용
    // 2. 디지털 필터 값
    //      입력 필터 상수 설정 범위 1 ~ 40, 단위 msec
	// Board 에 dwInterLock, dwDigFilterVal을 이용하여 EstopInterLock 기능 설정
	[DllImport("AXL.dll")] public static extern uint AxlSetEStopInterLock(int lBoardNo, uint dwInterLock, uint dwDigFilterVal);
	// Board에 설정된 dwInterLock, dwDigFilterVal 정보를 가져오기
	[DllImport("AXL.dll")] public static extern uint AxlGetEStopInterLock(int lBoardNo, ref uint dwInterLock, ref uint dwDigFilterVal);
	// Board에 입력된 EstopInterLock 신호를 읽는다.
	[DllImport("AXL.dll")] public static extern uint AxlReadEStopInterLock(int lBoardNo, ref uint dwInterLock);
        
    // Board에 내장된 범용 Data Flash Read(PCI-R1604[RTEX master board]전용)
    // lPageAddr(0 ~ 199)
    // lByteNum(1 ~ 120)
    [DllImport("AXL.dll")] public static extern uint AxlGetDataFlash(int lBoardNo, int lPageAddr, int lBytesNum, ref uint upGetData);

    // Board Number와 Module Position을 이용하여 AIO Module Number 찾기
    [DllImport("AXL.dll")] public static extern uint AxaInfoGetModuleNo(int nBoardNo, int nModulePos, ref int npModuleNo);
    // Board Number와 Module Position을 이용하여 DIO Module Number 찾기
    [DllImport("AXL.dll")] public static extern uint AxdInfoGetModuleNo(int nBoardNo, int nModulePos, ref int npModuleNo);

    // 지정 축에 byte Setting
    [DllImport("AXL.dll")] public static extern uint AxmSetCommand(int nAxisNo, byte sCommand);
    // 지정 축에 8bit byte Setting
    [DllImport("AXL.dll")] public static extern uint AxmSetCommandData08(int nAxisNo, byte sCommand, uint uData);
    // 지정 축에 8bit byte 가져오기
    [DllImport("AXL.dll")] public static extern uint AxmGetCommandData08(int nAxisNo, byte sCommand, ref uint upData);
    // 지정 축에 16bit byte Setting
    [DllImport("AXL.dll")] public static extern uint AxmSetCommandData16(int nAxisNo, byte sCommand, uint uData);
    // 지정 축에 16bit byte 가져오기
    [DllImport("AXL.dll")] public static extern uint AxmGetCommandData16(int nAxisNo, byte sCommand, ref uint upData);
    // 지정 축에 24bit byte Setting
    [DllImport("AXL.dll")] public static extern uint AxmSetCommandData24(int nAxisNo, byte sCommand, uint uData);
    // 지정 축에 24bit byte 가져오기
    [DllImport("AXL.dll")] public static extern uint AxmGetCommandData24(int nAxisNo, byte sCommand, ref uint upData);
    // 지정 축에 32bit byte Setting
    [DllImport("AXL.dll")] public static extern uint AxmSetCommandData32(int nAxisNo, byte sCommand, uint uData);
    // 지정 축에 32bit byte 가져오기
    [DllImport("AXL.dll")] public static extern uint AxmGetCommandData32(int nAxisNo, byte sCommand, ref uint upData);
    
    // 지정 축에 byte Setting
    [DllImport("AXL.dll")] public static extern uint AxmSetCommandQi(int nAxisNo, byte sCommand);
    // 지정 축에 8bit byte Setting
    [DllImport("AXL.dll")] public static extern uint AxmSetCommandData08Qi(int nAxisNo, byte sCommand, uint uData);
    // 지정 축에 8bit byte 가져오기
    [DllImport("AXL.dll")] public static extern uint AxmGetCommandData08Qi(int nAxisNo, byte sCommand, ref uint upData);
    // 지정 축에 16bit byte Setting
    [DllImport("AXL.dll")] public static extern uint AxmSetCommandData16Qi(int nAxisNo, byte sCommand, uint uData);
    // 지정 축에 16bit byte 가져오기
    [DllImport("AXL.dll")] public static extern uint AxmGetCommandData16Qi(int nAxisNo, byte sCommand, ref uint upData);
    // 지정 축에 24bit byte Setting
    [DllImport("AXL.dll")] public static extern uint AxmSetCommandData24Qi(int nAxisNo, byte sCommand, uint uData);
    // 지정 축에 24bit byte 가져오기
    [DllImport("AXL.dll")] public static extern uint AxmGetCommandData24Qi(int nAxisNo, byte sCommand, ref uint upData);
    // 지정 축에 32bit byte Setting
    [DllImport("AXL.dll")] public static extern uint AxmSetCommandData32Qi(int nAxisNo, byte sCommand, uint uData);
    // 지정 축에 32bit byte 가져오기
    [DllImport("AXL.dll")] public static extern uint AxmGetCommandData32Qi(int nAxisNo, byte sCommand, ref uint upData);
    
    // 지정 축에 Port Data 가져오기 - IP
    [DllImport("AXL.dll")] public static extern uint AxmGetPortData(int nAxisNo,  uint wOffset, ref uint upData);
    // 지정 축에 Port Data Setting - IP
    [DllImport("AXL.dll")] public static extern uint AxmSetPortData(int nAxisNo, uint wOffset, uint dwData);

    // 지정 축에 Port Data 가져오기 - QI
    [DllImport("AXL.dll")] public static extern uint AxmGetPortDataQi(int nAxisNo, uint byOffset, ref uint wData);
    // 지정 축에 Port Data Setting - QI
    [DllImport("AXL.dll")] public static extern uint AxmSetPortDataQi(int nAxisNo, uint byOffset, uint wData);
        
    // 지정 축에 스크립트를 설정한다. - IP
    // sc    : 스크립트 번호 (1 - 4)
    // event : 발생할 이벤트 SCRCON 을 정의한다.
    //         이벤트 설정 축갯수설정, 이벤트 발생할 축, 이벤트 내용 1,2 속성 설정한다.
    // cmd   : 어떤 내용을 바꿀것인지 선택 SCRCMD를 정의한다.
    // data  : 어떤 Data를 바꿀것인지 선택
    [DllImport("AXL.dll")] public static extern uint AxmSetScriptCaptionIp(int nAxisNo, int sc, uint uEvent, uint data);
    // 지정 축에 스크립트를 반환한다. - IP
    [DllImport("AXL.dll")] public static extern uint AxmGetScriptCaptionIp(int nAxisNo, int sc, ref uint uEvent, ref uint data);

    // 지정 축에 스크립트를 설정한다. - QI
    // sc    : 스크립트 번호 (1 - 4)
    // event : 발생할 이벤트 SCRCON 을 정의한다.
    //         이벤트 설정 축갯수설정, 이벤트 발생할 축, 이벤트 내용 1,2 속성 설정한다.
    // cmd   : 어떤 내용을 바꿀것인지 선택 SCRCMD를 정의한다.
    // data  : 어떤 Data를 바꿀것인지 선택
    [DllImport("AXL.dll")] public static extern uint AxmSetScriptCaptionQi(int nAxisNo, int sc, uint uEvent, uint cmd, uint data);
    // 지정 축에 스크립트를 반환한다. - QI
    [DllImport("AXL.dll")] public static extern uint AxmGetScriptCaptionQi(int nAxisNo, int sc, ref uint uEvent, ref uint cmd, ref uint data);

    // 지정 축에 스크립트 내부 Queue Index를 Clear 시킨다.
    // uSelect IP. 
    // uSelect(0): 스크립트 Queue Index 를 Clear한다.
    //        (1): 캡션 Queue를 Index Clear한다.

    // uSelect QI. 
    // uSelect(0): 스크립트 Queue 1 Index 을 Clear한다.
    //        (1): 스크립트 Queue 2 Index 를 Clear한다.

    [DllImport("AXL.dll")] public static extern uint AxmSetScriptCaptionQueueClear(int nAxisNo, uint uSelect);
    
    // 지정 축에 스크립트 내부 Queue의 Index 반환한다. 
    // uSelect IP
    // uSelect(0): 스크립트 Queue Index를 읽어온다.
    //        (1): 캡션 Queue Index를 읽어온다.

    // uSelect QI. 
    // uSelect(0): 스크립트 Queue 1 Index을 읽어온다.
    //        (1): 스크립트 Queue 2 Index를 읽어온다.

    [DllImport("AXL.dll")] public static extern uint AxmGetScriptCaptionQueueCount(int nAxisNo, ref uint updata, uint uSelect);

    // 지정 축에 스크립트 내부 Queue의 Data갯수 반환한다. 
    // uSelect IP
    // uSelect(0): 스크립트 Queue Data 를 읽어온다.
    //        (1): 캡션 Queue Data를 읽어온다.

    // uSelect QI.
    // uSelect(0): 스크립트 Queue 1 Data 읽어온다.
    //        (1): 스크립트 Queue 2 Data 읽어온다.

    [DllImport("AXL.dll")] public static extern uint AxmGetScriptCaptionQueueDataCount(int nAxisNo, ref uint updata, uint uSelect);

    // 내부 데이타를 읽어온다.
    [DllImport("AXL.dll")] public static extern uint AxmGetOptimizeDriveData(int nAxisNo, double dMinVel, double dVel, double dAccel, double  dDecel, 
            ref uint wRangeData, ref uint wStartStopSpeedData, ref uint wObjectSpeedData, ref uint wAccelRate, ref uint wDecelRate);

    // 보드내에 레지스터를 Byte단위로 설정 및 확인한다.
    [DllImport("AXL.dll")] public static extern uint AxmBoardWriteByte(int nBoardNo, uint wOffset, byte byData);
    [DllImport("AXL.dll")] public static extern uint AxmBoardReadByte(int nBoardNo, uint wOffset, ref byte byData);

    // 보드내에 레지스터를 Word단위로 설정 및 확인한다.
    [DllImport("AXL.dll")] public static extern uint AxmBoardWriteWord(int nBoardNo, uint wOffset, uint wData);
    [DllImport("AXL.dll")] public static extern uint AxmBoardReadWord(int nBoardNo, uint wOffset, ref ushort wData);

    // 보드내에 레지스터를 DWord단위로 설정 및 확인한다.
    [DllImport("AXL.dll")] public static extern uint AxmBoardWriteDWord(int nBoardNo, uint wOffset, uint dwData);
    [DllImport("AXL.dll")] public static extern uint AxmBoardReadDWord(int nBoardNo, uint wOffset, ref uint dwData);

    // 보드내에 모듈에 레지스터를 Byte설정 및 확인한다.
    [DllImport("AXL.dll")] public static extern uint AxmModuleWriteByte(int nBoardNo, int nModulePos, uint wOffset, byte byData);
    [DllImport("AXL.dll")] public static extern uint AxmModuleReadByte(int nBoardNo, int nModulePos, uint wOffset, ref byte byData);

    // 보드내에 모듈에 레지스터를 Word설정 및 확인한다.
    [DllImport("AXL.dll")] public static extern uint AxmModuleWriteWord(int nBoardNo, int nModulePos, uint wOffset, uint wData);
    [DllImport("AXL.dll")] public static extern uint AxmModuleReadWord(int nBoardNo, int nModulePos, uint wOffset, ref ushort wData);

    // 보드내에 모듈에 레지스터를 DWord설정 및 확인한다.
    [DllImport("AXL.dll")] public static extern uint AxmModuleWriteDWord(int nBoardNo, int nModulePos, uint wOffset, uint dwData);
    [DllImport("AXL.dll")] public static extern uint AxmModuleReadDWord(int nBoardNo, int nModulePos, uint wOffset, ref uint dwData);
    

    // 외부 위치 비교기에 값을 설정한다.(Pos = Unit)
    [DllImport("AXL.dll")] public static extern uint AxmStatusSetActComparatorPos(int nAxisNo, double dPos);
    // 외부 위치 비교기에 값을 반환한다.(Positon = Unit)
    [DllImport("AXL.dll")] public static extern uint AxmStatusGetActComparatorPos(int nAxisNo, ref double dpPos);

    // 내부 위치 비교기에 값을 설정한다.(Pos = Unit)
    [DllImport("AXL.dll")] public static extern uint AxmStatusSetCmdComparatorPos(int nAxisNo, double dPos);
    // 내부 위치 비교기에 값을 반환한다.(Pos = Unit)
    [DllImport("AXL.dll")] public static extern uint AxmStatusGetCmdComparatorPos(int nAxisNo, ref double dpPos);
    
//========== 추가 함수 =========================================================================================================
    
    // 직선 보간 을 속도만 가지고 무한대로 증가한다.
    // 속도 비율대로 거리를 넣어주어야 한다. 
    [DllImport("AXL.dll")] public static extern uint AxmLineMoveVel(int nCoord, double dVel, double dAccel, double dDecel);

//========= 센서 위치 구동 함수( 필독: IP만가능 , QI에는 기능없음)==============================================================
    
    // 지정 축의 Sensor 신호의 사용 유무 및 신호 입력 레벨을 설정한다.
    // 사용 유무 LOW(0), HIGH(1), UNUSED(2), USED(3)
    [DllImport("AXL.dll")] public static extern uint AxmSensorSetSignal(int nAxisNo, uint uLevel);
    // 지정 축의 Sensor 신호의 사용 유무 및 신호 입력 레벨을 반환한다.
    [DllImport("AXL.dll")] public static extern uint AxmSensorGetSignal(int nAxisNo, ref uint upLevel);
    // 지정 축의 Sensor 신호의 입력 상태를 반환한다
    [DllImport("AXL.dll")] public static extern uint AxmSensorReadSignal(int nAxisNo, ref uint upStatus);
    
    // 지정 축의 설정된 속도와 가속율로 센서 위치 드라이버를 구동한다.
    // Sensor 신호의 Active level입력 이후 상대 좌표로 설정된 거리만큼 구동후 정지한다.
    // 펄스가 출력되는 시점에서 함수를 벗어난다.
    // lMethod :  0 - 일반 구동, 1 - 센서 신호 검출 전은 저속 구동. 신호 검출 후 일반 구동
    //            2 - 저속 구동
    [DllImport("AXL.dll")] public static extern uint AxmSensorMovePos(int nAxisNo, double dPos, double dVel, double dAccel, double dDecel, int nMethod);

    // 지정 축의 설정된 속도와 가속율로 센서 위치 드라이버를 구동한다.
    // Sensor 신호의 Active level입력 이후 상대 좌표로 설정된 거리만큼 구동후 정지한다.
    // 펄스 출력이 종료되는 시점에서 함수를 벗어난다.
    [DllImport("AXL.dll")] public static extern uint AxmSensorStartMovePos(int nAxisNo, double dPos, double dVel, double dAccel, double dDecel, int nMethod);

    // 원점검색 진행스탭 변화의 기록을 반환한다.
    // *lpStepCount      : 기록된 Step의 개수
    // *upMainStepNumber : 기록된 MainStepNumber 정보의 배열포인트
    // *upStepNumber     : 기록된 StepNumber 정보의 배열포인트
    // *upStepBranch     : 기록된 Step별 Branch 정보의 배열포인트
    // 주의: 배열개수는 50개로 고정
    [DllImport("AXL.dll")] public static extern uint AxmHomeGetStepTrace(int nAxisNo, ref uint upStepCount, ref uint upMainStepNumber, ref uint upStepNumber, ref uint upStepBranch);

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
    [DllImport("AXL.dll")] public static extern uint AxmHomeSetConfig(int nAxisNo, uint uZphasCount, int nHomeMode, int nClearSet, double dOrgVel, double dLastVel, double dLeavePos);
    // 사용자가 지정한 축의 홈설정 파라메타를 반환한다.
    [DllImport("AXL.dll")] public static extern uint AxmHomeGetConfig(int nAxisNo, ref uint upZphasCount, ref int npHomeMode, ref int npClearSet, ref double dpOrgVel, ref double dpLastVel, ref double dpLeavePos); //KKJ(070215)
    
    // 사용자가 지정한 축의 홈 서치를 시작한다.
    // lHomeMode 사용시 설정 : 0 - 5 설정 (Move Return후에 Search를  시작한다.)
    // lHomeMode -1로 그대로 사용시 HomeConfig에서 사용한대로 그대로 설정됨.
    // 구동방향      : Vel값이 양수이면 CW, 음수이면 CCW.
    [DllImport("AXL.dll")] public static extern uint AxmHomeSetMoveSearch(int nAxisNo, double dVel, double dAccel, double dDecel);

    // 사용자가 지정한 축의 홈 리턴을 시작한다.
    // lHomeMode 사용시 설정 : 0 - 12 설정 
    // lHomeMode -1로 그대로 사용시 HomeConfig에서 사용한대로 그대로 설정됨.
    // 구동방향      : Vel값이 양수이면 CW, 음수이면 CCW.
    [DllImport("AXL.dll")] public static extern uint AxmHomeSetMoveReturn(int nAxisNo, double dVel, double dAccel, double dDecel);
    
    // 사용자가 지정한 축의 홈 이탈을 시작한다.
    // 구동방향      : Vel값이 양수이면 CW, 음수이면 CCW.
    [DllImport("AXL.dll")] public static extern uint AxmHomeSetMoveLeave(int nAxisNo, double dVel, double dAccel, double dDecel);

    // 사용자가 지정한 다축의 홈 서치을 시작한다.
    // lHomeMode 사용시 설정 : 0 - 5 설정 (Move Return후에 Search를  시작한다.)
    // lHomeMode -1로 그대로 사용시 HomeConfig에서 사용한대로 그대로 설정됨.
    // 구동방향      : Vel값이 양수이면 CW, 음수이면 CCW.
    [DllImport("AXL.dll")] public static extern uint AxmHomeSetMultiMoveSearch(int nArraySize, ref int npAxesNo, ref double dpVel, ref double dpAccel, ref double dpDecel);

    //지정된 좌표계의 구동 속도 프로파일 모드를 설정한다.
    // (주의점 : 반드시 축맵핑 하고 사용가능)
    // ProfileMode : '0' - 대칭 Trapezode
    //               '1' - 비대칭 Trapezode
    //               '2' - 대칭 Quasi-S Curve
    //               '3' - 대칭 S Curve
    //               '4' - 비대칭 S Curve
    [DllImport("AXL.dll")] public static extern uint AxmContiSetProfileMode(int nCoord, uint uProfileMode);
    // 지정된 좌표계의 구동 속도 프로파일 모드를 반환한다.
    [DllImport("AXL.dll")] public static extern uint AxmContiGetProfileMode(int nCoord, ref uint upProfileMode);

    //========== DIO 인터럽트 플래그 레지스트 읽기
    // 지정한 입력 접점 모듈, Interrupt Flag Register의 Offset 위치에서 bit 단위로 인터럽트 발생 상태 값을 읽음
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptFlagReadBit(int nModuleNo, int nOffset, ref uint upValue);
    // 지정한 입력 접점 모듈, Interrupt Flag Register의 Offset 위치에서 byte 단위로 인터럽트 발생 상태 값을 읽음
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptFlagReadByte(int nModuleNo, int nOffset, ref uint upValue);
    // 지정한 입력 접점 모듈, Interrupt Flag Register의 Offset 위치에서 word 단위로 인터럽트 발생 상태 값을 읽음
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptFlagReadWord(int nModuleNo, int nOffset, ref uint upValue);
    // 지정한 입력 접점 모듈, Interrupt Flag Register의 Offset 위치에서 double word 단위로 인터럽트 발생 상태 값을 읽음
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptFlagReadDword(int nModuleNo, int nOffset, ref uint upValue);
    // 전체 입력 접점 모듈, Interrupt Flag Register의 Offset 위치에서 bit 단위로 인터럽트 발생 상태 값을 읽음
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptFlagRead(int nOffset, ref uint upValue);

    //========= 로그 관련 함수 ==========================================================================================
    // 현재 자동으로 설정됨.
    // 설정 축의 함수 실행 결과를 EzSpy에서 모니터링 할 수 있도록 설정 또는 해제하는 함수이다.
    // uUse : 사용 유무 => DISABLE(0), ENABLE(1)
    [DllImport("AXL.dll")] public static extern uint AxmLogSetAxis(int nAxisNo, uint uUse);
    
    // EzSpy에서의 설정 축 함수 실행 결과 모니터링 여부를 확인하는 함수이다.
    [DllImport("AXL.dll")] public static extern uint AxmLogGetAxis(int nAxisNo, ref uint upUse);

//=========== 로그 출력 관련 함수
    //지정한 입력 채널의 EzSpy에 로그 출력 여부를 설정한다.
    [DllImport("AXL.dll")] public static extern uint AxaiLogSetChannel(int nChannelNo, uint uUse);
    //지정한 입력 채널의 EzSpy에 로그 출력 여부를 확인한다.
    [DllImport("AXL.dll")] public static extern uint AxaiLogGetChannel(int nChannelNo, ref uint upUse);

//==지정한 출력 채널의 EzSpy 로그 출력 
    //지정한 출력 채널의 EzSpy에 로그 출력 여부를 설정한다.
    [DllImport("AXL.dll")] public static extern uint AxaoLogSetChannel(int nChannelNo, uint uUse);
    //지정한 출력 채널의 EzSpy에 로그 출력 여부를 확인한다.
    [DllImport("AXL.dll")] public static extern uint AxaoLogGetChannel(int nChannelNo, ref uint upUse);

//==Log
    // 지정한 모듈의 EzSpy에 로그 출력 여부 설정
    [DllImport("AXL.dll")] public static extern uint AxdLogSetModule(int nModuleNo, uint uUse);
    // 지정한 모듈의 EzSpy에 로그 출력 여부 확인
    [DllImport("AXL.dll")] public static extern uint AxdLogGetModule(int nModuleNo, ref uint upUse);

    // 지정한 보드가 RTEX 모드일 때 그 보드의 firmware 버전을 확인한다.
    [DllImport("AXL.dll")] public static extern uint AxlGetFirmwareVersion(int nBoardNo, ref char szVersion);
    // 지정한 보드로 Firmware를 전송 한다.
    [DllImport("AXL.dll")] public static extern uint AxlSetFirmwareCopy(int nBoardNo, ref ushort wData, ref ushort wCmdData);
    // 지정한 보드로 Firmware Update를 수행한다.
    [DllImport("AXL.dll")] public static extern uint AxlSetFirmwareUpdate(int nBoardNo);
    // 지정한 보드의 현재 RTEX 초기화 상태를 확인 한다.
    [DllImport("AXL.dll")] public static extern uint AxlCheckStatus(int nBoardNo, ref uint dwStatus);
    // 지정한 축에 RTEX Master board에 범용 명령을 실행 합니다.
    [DllImport("AXL.dll")] public static extern uint AxlRtexUniversalCmd(int nBoardNo, ushort wCmd, ushort wOffset, ref ushort wData);
    // 지정한 축의 RTEX 통신 명령을 실행한다.
    [DllImport("AXL.dll")] public static extern uint AxmRtexSlaveCmd(int nAxisNo, uint dwCmdCode, uint dwTypeCode, uint dwIndexCode, uint dwCmdConfigure, uint dwValue);
    // 지정한 축에 실행한 RTEX 통신 명령의 결과값을 확인한다.
    [DllImport("AXL.dll")] public static extern uint AxmRtexGetSlaveCmdResult(int nAxisNo, ref uint dwIndex, ref uint dwValue);
    // 지정한 축에 RTEX 상태 정보를 확인한다.
    [DllImport("AXL.dll")] public static extern uint AxmRtexGetAxisStatus(int nAxisNo, ref uint dwStatus);
    // 지정한 축에 RTEX 통신 리턴 정보를 확인한다.(Actual position, Velocity, Torque)
    [DllImport("AXL.dll")] public static extern uint AxmRtexGetAxisReturnData(int nAxisNo,  ref uint dwReturn1, ref uint dwReturn2, ref uint dwReturn3);
    // 지정한 축에 RTEX Slave 축의 현재 상태 정보를 확인한다.(mechanical, Inposition and etc)
    [DllImport("AXL.dll")] public static extern uint AxmRtexGetAxisSlaveStatus(int nAxisNo,  ref uint dwStatus);
    // 지정한 축에 MLII Slave 축에 범용 네트웍 명령어를 기입한다.
    [DllImport("AXL.dll")] public static extern uint AxmSetAxisCmd(int nAxisNo, ref uint tagCommand);
    // 지정한 축에 MLII Slave 축에 범용 네트웍 명령의 결과를 확인한다.
    [DllImport("AXL.dll")] public static extern uint AxmGetAxisCmdResult(int nAxisNo, ref uint tagCommand);
    
    [DllImport("AXL.dll")] public static extern uint AxlGetDpRamData(int nBoardNo, ushort uAddress, ref uint upRdData);
    [DllImport("AXL.dll")] public static extern uint AxlBoardReadDpramWord(int nBoardNo, ushort uOffset, ref uint upRdData);

    [DllImport("AXL.dll")] public static extern uint AxlSetSendBoardCommand(int nBoardNo, uint uCommand, ref uint upSendData, uint uLength);
    [DllImport("AXL.dll")] public static extern uint AxlGetResponseBoardCommand(int nBoardNo, ref uint upReadData);

    // Network Type Master 보드에서 Slave 들의 Firmware Version을 읽어 오는 함수.
    // ucaFirmwareVersion unsigned char 형의 Array로 선언하고 크기가 4이상이 되도록 선언 해야 한다.
    [DllImport("AXL.dll")] public static extern uint AxmInfoGetFirmwareVersion(int nAxisNo, ref ushort ucaFirmwareVersion);
    [DllImport("AXL.dll")] public static extern uint AxaInfoGetFirmwareVersion(int nModuleNo, ref ushort ucaFirmwareVersion);
    [DllImport("AXL.dll")] public static extern uint AxdInfoGetFirmwareVersion(int nModuleNo, ref ushort ucaFirmwareVersion);

//======== PCI-R1604-MLII 전용 함수=========================================================================== 
    // INTERPOLATE and LATCH Command의 Option Field의 Torq Feed Forward의 값을 설정 하도록 합니다.
    // 기본값은 MAX로 설정되어 있습니다.
    // 설정값은 0 ~ 4000H까지 설정 할 수 있습니다.
    // 설정값은 4000H이상으로 설정하면 설정은 그 이상으로 설정되나 동작은 4000H값이 적용 됩니다.
    [DllImport("AXL.dll")] public static extern uint AxmSetTorqFeedForward(int nAxisNo, uint uTorqFeedForward);
 
    // INTERPOLATE and LATCH Command의 Option Field의 Torq Feed Forward의 값을 읽어오는 함수 입니다.
    // 기본값은 MAX로 설정되어 있습니다.
    [DllImport("AXL.dll")] public static extern uint AxmGetTorqFeedForward(int nAxisNo, ref uint upTorqFeedForward);
 
    // INTERPOLATE and LATCH Command의 VFF Field의 Velocity Feed Forward의 값을 설정 하도록 합니다.
    // 기본값은 '0'로 설정되어 있습니다.
    // 설정값은 0 ~ FFFFH까지 설정 할 수 있습니다.
    [DllImport("AXL.dll")] public static extern uint AxmSetVelocityFeedForward(int nAxisNo, uint uVelocityFeedForward);
 
    // INTERPOLATE and LATCH Command의 VFF Field의 Velocity Feed Forward의 값을 읽어오는 함수 입니다.
    [DllImport("AXL.dll")] public static extern uint AxmGetVelocityFeedForward(int nAxisNo, ref uint upVelocityFeedForward);

    // Encoder type을 설정한다.
    // 기본값은 0(TYPE_INCREMENTAL)로 설정되어 있습니다.
    // 설정값은 0 ~ 1까지 설정 할 수 있습니다.
    // 설정값 : 0(TYPE_INCREMENTAL), 1(TYPE_ABSOLUTE).
    [DllImport("AXL.dll")] public static extern uint AxmSignalSetEncoderType(int lAxisNo, uint uEncoderType);

    // Encoder type을 확인한다.
    [DllImport("AXL.dll")] public static extern uint AxmSignalGetEncoderType(int lAxisNo, ref uint upEncoderType);

    // Slave Firmware Update를 위해 추가
    //[DllImport("AXL.dll")] public static extern uint AxmSetSendAxisCommand(long lAxisNo, WORD wCommand, WORD* wpSendData, WORD wLength);

    //======== PCI-R1604-RTEX, RTEX-PM 전용 함수============================================================== 
    // 범용 입력 2,3번 입력시 JOG 구동 속도를 설정한다. 
    // 구동에 관련된 모든 설정(Ex, PulseOutMethod, MoveUnitPerPulse 등)들이 완료된 이후 한번만 실행하여야 한다.
    [DllImport("AXL.dll")] public static extern uint AxmMotSetUserMotion(int lAxisNo, double dVelocity, double dAccel, double dDecel);

    // 범용 입력 2,3번 입력시 JOG 구동 동작 사용 가부를 설정한다.
    // 설정값 :  0(DISABLE), 1(ENABLE)
    [DllImport("AXL.dll")] public static extern uint AxmMotSetUserMotionUsage(int lAxisNo, uint dwUsage);

    // MPGP 입력을 사용하여 Load/UnLoad 위치를 자동으로 이동하는 기능 설정. 
    [DllImport("AXL.dll")] public static extern uint AxmMotSetUserPosMotion(int lAxisNo, double dVelocity, double dAccel, double dDecel, double dLoadPos, double dUnLoadPos, uint dwFilter, uint dwDelay);

    // MPGP 입력을 사용하여 Load/UnLoad 위치를 자동으로 이동하는 기능 설정. 
    // 설정값 :  0(DISABLE), 1(Position 기능 A 사용), 2(Position 기능 B 사용)
    [DllImport("AXL.dll")] public static extern uint AxmMotSetUserPosMotionUsage(int lAxisNo, uint dwUsage);
    //======================================================================================================== 

    //======== SIO-CN2CH, 절대 위치 트리거 기능 모듈 전용 함수================================================ 
    // 메모리 데이터 쓰기 함수
    [DllImport("AXL.dll")] public static extern uint AxcKeWriteRamDataAddr(int lChannelNo, uint dwAddr, uint dwData);
    // 메모리 데이터 읽기 함수
    [DllImport("AXL.dll")] public static extern uint AxcKeReadRamDataAddr(int lChannelNo, uint dwAddr, ref uint dwpData);
    // 메모리 초기화 함수
    [DllImport("AXL.dll")] public static extern uint AxcKeResetRamDataAll(int lModuleNo, uint dwData);
    // 트리거 타임 아웃 설정 함수
    [DllImport("AXL.dll")] public static extern uint AxcTriggerSetTimeout(int lChannelNo, uint dwTimeout);
    // 트리거 타임 아웃 확인 함수
    [DllImport("AXL.dll")] public static extern uint AxcTriggerGetTimeout(int lChannelNo, ref uint dwpTimeout);
    // 트리거 대기 상태 확인 함수
    [DllImport("AXL.dll")] public static extern uint AxcStatusGetWaitState(int lChannelNo, ref uint dwpState);
    // 트리거 대기 상태 설정 함수
    [DllImport("AXL.dll")] public static extern uint AxcStatusSetWaitState(int lChannelNo, uint dwState);
    
    //지정 채널에 명령어 기입
    [DllImport("AXL.dll")] public static extern uint AxcKeSetCommandData32(int lChannelNo, uint dwCommand, uint dwData);
    
    //지정 채널에 명령어 기입
    [DllImport("AXL.dll")] public static extern uint AxcKeSetCommandData16(int lChannelNo, uint dwCommand, uint wData); 
    
    //지정 채널의 레지스터 확인
    [DllImport("AXL.dll")] public static extern uint AxcKeGetCommandData32(int lChannelNo, uint dwCommand, ref uint dwpData);
    
    //지정 채널의 레지스터 확인
    [DllImport("AXL.dll")] public static extern uint AxcKeGetCommandData16(int lChannelNo, uint dwCommand, ref uint wpData); 
    
    //======================================================================================================== 
	
    //======== PCI-N804/N404 전용, Sequence Motion ===================================================================
    // Sequence Motion의 축 정보를 설정 합니다. (최소 1축)
    // lSeqMapNo : 축 번호 정보를 담는 Sequence Motion Index Point
    // lSeqMapSize : 축 번호 갯수
    // long* LSeqAxesNo : 축 번호 배열
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqSetAxisMap(int lSeqMapNo, int lSeqMapSize, ref int lSeqAxesNo);
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqGetAxisMap(int lSeqMapNo, ref int lSeqMapSize, ref int lSeqAxesNo);

    // Sequence Motion의 기준(Master) 축을 설정 합니다. 
    // 반드시 AxmSeqSetAxisMap(...) 에 설정된 축 내에서 설정하여야 합니다.
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqSetMasterAxisNo(int lSeqMapNo, int lMasterAxisNo);

    // Sequence Motion의 Node 적재 시작을 라이브러리에 알립니다.
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqBeginNode(int lSeqMapNo);

    // Sequence Motion의 Node 적재 종료를 라이브러리에 알립니다.
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqEndNode(int lSeqMapNo);

    // Sequence Motion의 구동을 시작 합니다.
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqStart(int lSeqMapNo, ref uint dwStartOption);

    // Sequence Motion의 각 Profile Node 정보를 라이브러리에 입력 합니다.
    // 만약 1축 Sequence Motion을 사용하더라도, *dPosition는 1개의 Array로 지정하여 주시기 바랍니다.
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqAddNode(int lSeqMapNo, ref double dPosition, double dVelocity, double dAcceleration, double dDeceleration, double dNextVelocity);

    // Sequence Motion이 구동 시 현재 실행 중인 Node Index를 알려 줍니다.
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqGetNodeNum(int lSeqMapNo, ref int lCurNodeNo);

    // Sequence Motion의 총 Node Count를 확인 합니다.
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqGetTotalNodeNum(int lSeqMapNo, ref int lTotalNodeCnt);

    // Sequence Motion이 현재 구동 중인지 확인 합니다.
    // dwInMotion : 0(구동 종료), 1(구동 중)
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqIsMotion(int lSeqMapNo, ref uint dwInMotion);

    // Sequence Motion의 Memory를 Clear 합니다.
    // AxmSeqSetAxisMap(...), AxmSeqSetMasterAxisNo(...) 에서 설정된 값은 유지됩니다.
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqWriteClear(int lSeqMapNo);

    // Sequence Motion의 구동을 종료 합니다.
    // dwStopMode : 0(EMERGENCY_STOP), 1(SLOWDOWN_STOP) 
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqStop(int lSeqMapNo, uint dwStopMode);
    //======================================================================================================== 
}
