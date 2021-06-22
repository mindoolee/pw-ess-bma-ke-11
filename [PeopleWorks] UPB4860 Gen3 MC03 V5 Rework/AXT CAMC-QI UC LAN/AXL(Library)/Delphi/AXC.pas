//****************************************************************************
//****************************************************************************
//**
//** File Name
//** ----------
//**
//** AXC.H
//**
//** COPYRIGHT (c) AJINEXTEK Co., LTD
//**
//*****************************************************************************
//*****************************************************************************
//**
//** Description
//** -----------
//** Ajinextek Counter Library Header File
//** 
//**
//*****************************************************************************
//*****************************************************************************
//**
//** Source Change Indices
//** ---------------------
//** 
//** (None)
//**
//**
//*****************************************************************************
//*****************************************************************************
//**
//** Website
//** ---------------------
//**
//** http://www.ajinextek.com
//**
//*****************************************************************************
//*****************************************************************************

unit AXC;

interface

uses Windows, Messages, AXHS;

//========== 보드 및 모듈 정보 
    // CNT 모듈이 있는지 확인
function AxcInfoIsCNTModule(upStatus : PDWord) : DWord; stdcall;
    
    // CNT 모듈 No 확인
function AxcInfoGetModuleNo(lBoardNo : LongInt; lModulePos : LongInt; lpModuleNo : PLongInt) : DWord; stdcall;
    
    // CNT 입출력 모듈의 개수 확인
function AxcInfoGetModuleCount(lpModuleCount : PLongInt) : DWord; stdcall;

    // 지정한 모듈의 카운터 입력 채널 개수 확인
function AxcInfoGetChannelCount(lModuleNo : LongInt; lpCount : PLongInt) : DWord; stdcall;
    
    // 시스템에 장착된 카운터의 전 채널 수를 확인
function AxcInfoGetTotalChannelCount(lpChannelCount : PLongInt) : DWord; stdcall;    

    // 지정한 모듈 번호로 베이스 보드 번호, 모듈 위치, 모듈 ID 확인
function AxcInfoGetModule(lModuleNo : LongInt; lpBoardNo : PLongInt; lpModulePos : PLongInt; upModuleID : PDWord) : DWord; stdcall;

    // 해당 모듈이 제어가 가능한 상태인지 반환한다.
function AxcInfoGetModuleStatus(lModuleNo : LongInt) : DWord; stdcall;

function AxcInfoGetFirstChannelNoOfModuleNo(lModuleNo : LongInt; lpChannelNo : PLongInt) : DWord; stdcall;

    // 카운터 모듈의 Encoder 입력 방식을 설정 합니다.
    // dwMethod --> 0x00 : Sign and pulse, x1 multiplication
    // dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
    // dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
    // dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
    // dwMethod --> 0x08 : Sign and pulse, x2 multiplication
    // dwMethod --> 0x09 : Increment and decrement pulses, x1 multiplication
    // dwMethod --> 0x0A : Increment and decrement pulses, x2 multiplication
    // SIO-CN2CH/HPC4의 경우
    // dwMethod --> 0x00 : Up/Down 방식, A phase : 펄스, B phase : 방향
    // dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
    // dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
    // dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
function AxcSignalSetEncInputMethod(lChannelNo : LongInt; dwMethod : DWord) : DWord; stdcall;

    // 카운터 모듈의 Encoder 입력 방식을 반환 합니다.
    // *dwpUpMethod --> 0x00 : Sign and pulse, x1 multiplication
    // *dwpUpMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
    // *dwpUpMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
    // *dwpUpMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
    // *dwpUpMethod --> 0x08 : Sign and pulse, x2 multiplication
    // *dwpUpMethod --> 0x09 : Increment and decrement pulses, x1 multiplication
    // *dwpUpMethod --> 0x0A : Increment and decrement pulses, x2 multiplication
    // SIO-CN2CH/HPC4의 경우
    // dwMethod --> 0x00 : Up/Down 방식, A phase : 펄스, B phase : 방향
    // dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
    // dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
    // dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
function AxcSignalGetEncInputMethod(lChannelNo : LongInt; dwpUpMethod : PDWord) : DWord; stdcall;

    // 카운터 모듈의 트리거를 설정 합니다.
    // dwMode -->  0x00 : Latch
    // dwMode -->  0x01 : State
    // dwMode -->  0x02 : Special State    --> SIO-CN2CH 전용
    // SIO-CN2CH의 경우
    // dwMode -->  0x00 : 절대 위치 트리거 또는 주기 위치 트리거.
    // 주의 : 제품마다 기능이 서로 다르기 때문에 구별하여 사용 필요.
    // dwMode -->  0x01 : 시간 주기 트리거(AxcTriggerSetFreq로 설정)
    // SIO-HPC4의 경우
    // dwMode -->  0x00 : absolute mode[with ram data].
    // dwMode -->  0x01 : timer mode.
    // dwMode -->  0x02 : absolute mode[with fifo].
    // dwMode -->  0x03 : periodic mode.[Default]
function AxcTriggerSetFunction(lChannelNo : LongInt; dwMode : DWord) : DWord; stdcall;

    // 카운터 모듈의 트리거 설정을 확인 합니다.
    // *dwMode -->  0x00 : Latch
    // *dwMode -->  0x01 : State
    // *dwMode -->  0x02 : Special State
    // dwMode -->  0x00 : 절대 위치 트리거 또는 주기 위치 트리거.
    // 주의 : 제품마다 기능이 서로 다르기 때문에 구별하여 사용 필요.
    // dwMode -->  0x01 : 시간 주기 트리거(AxcTriggerSetFreq로 설정)
    // SIO-HPC4의 경우
    // dwMode -->  0x00 : absolute mode[with ram data].
    // dwMode -->  0x01 : timer mode.
    // dwMode -->  0x02 : absolute mode[with fifo].
    // dwMode -->  0x03 : periodic mode.[Default]
function AxcTriggerGetFunction(lChannelNo : LongInt; dwpMode : PDWord) : DWord; stdcall;

    // dwUsage --> 0x00 : Trigger Not use
    // dwUsage --> 0x01 : Trigger use
function AxcTriggerSetNotchEnable(lChannelNo : LongInt; dwUsage : DWord) : DWord; stdcall;

    // *dwUsage --> 0x00 : Trigger Not use
    // *dwUsage --> 0x01 : Trigger use
function AxcTriggerGetNotchEnable(lChannelNo : LongInt; dwpUsage : PDWord) : DWord; stdcall;
    

    // 카운터 모듈의 Captuer 극성을 설정 합니다.(External latch input polarity)
    // dwCapturePol --> 0x00 : Signal OFF -> ON
    // dwCapturePol --> 0x01 : Signal ON -> OFF
function AxcSignalSetCaptureFunction(lChannelNo : LongInt; dwCapturePol : DWord) : DWord; stdcall;

    // 카운터 모듈의 Captuer 극성 설정을 확인 합니다.(External latch input polarity)
    // *dwCapturePol --> 0x00 : Signal OFF -> ON
    // *dwCapturePol --> 0x01 : Signal ON -> OFF
function AxcSignalGetCaptureFunction(lChannelNo : LongInt; dwpCapturePol : PDWord) : DWord; stdcall;

    // 카운터 모듈의 Captuer 위치를 확인 합니다.(External latch)
    // *dbpCapturePos --> Capture position 위치
function AxcSignalGetCapturePos(lChannelNo : LongInt; dbpCapturePos : PDouble) : DWord; stdcall;

    // 카운터 모듈의 카운터 값을 확인 합니다.
    // *dbpActPos --> 카운터 값
function AxcStatusGetActPos(lChannelNo : LongInt; dbpActPos : PDouble) : DWord; stdcall;

    // 카운터 모듈의 카운터 값을 dbActPos 값으로 설정 합니다.
function AxcStatusSetActPos(lChannelNo : LongInt; dbActPos : Double) : DWord; stdcall;

    // 카운터 모듈의 트리거 위치를 설정합니다.
    // 카운터 모듈의 트리거 위치는 2개까지만 설정 할 수 있습니다.
function AxcTriggerSetNotchPos(lChannelNo : LongInt; dbLowerPos : Double; dbUpperPos : Double) : DWord; stdcall;

    // 카운터 모듈의 설정한 트리거 위치를 확인 합니다.
function AxcTriggerGetNotchPos(lChannelNo : LongInt; dbpLowerPos : PDouble; dbpUpperPos : PDouble) : DWord; stdcall;

    // 카운터 모듈의 트리거 출력을 강제로 합니다.
    // dwOutVal --> 0x00 : 트리거 출력 '0'
    // dwOutVal --> 0x01 : 트리거 출력 '1'
function AxcTriggerSetOutput(lChannelNo : LongInt; dwOutVal : DWord) : DWord; stdcall;

    // 카운터 모듈의 상태를 확인합니다.
    // Bit '0' : Carry (카운터 현재치가 덧셈 펄스에 의해 카운터 상한치를 넘어 0로 바뀌었을 때 1스캔만 ON으로 합니다.)
    // Bit '1' : Borrow (카운터 현재치가 뺄셈 펄스에 의해 0을 넘어 카운터 상한치로 바뀌었을 때 1스캔만 ON으로 합니다.)
    // Bit '2' : Trigger output status
    // Bit '3' : Latch input status
function AxcStatusGetChannel(lChannelNo : LongInt; dwpChannelStatus : DWord) : DWord; stdcall;


    // SIO-CN2CH 전용 함수군
    //
    // 카운터 모듈의 위치 단위를 설정한다.
    // 실제 위치 이동량에 대한 펄스 갯수를 설정하는데,
    // ex) 1mm 이동에 1000가 필요하다면dMoveUnitPerPulse = 0.001로 입력하고,
    //     이후 모든 함수의 위치와 관련된 값을 mm 단위로 설정하면 된다.
function AxcMotSetMoveUnitPerPulse(lChannelNo : LongInt; dMoveUnitPerPulse : Double) : DWord; stdcall;

    // 카운터 모듈의 위치 단위를 확인한다.
function AxcMotGetMoveUnitPerPulse(lChannelNo : LongInt;  dpMoveUnitPerPuls : PDouble) : DWord; stdcall;

    // 카운터 모듈의 엔코더 입력 카운터를 반전 기능을 설정한다.
    // dwReverse --> 0x00 : 반전하지 않음.
    // dwReverse --> 0x01 : 반전.
function AxcSignalSetEncReverse(lChannelNo : LongInt; dwReverse : DWord) : DWord; stdcall;

    // 카운터 모듈의 엔코더 입력 카운터를 반전 기능을 설정을 확인한다.
function AxcSignalGetEncReverse(lChannelNo : LongInt; dwpReverse : PDWord) : DWord; stdcall;

    // 카운터 모듈의 Encoder 입력 신호를 선택한다.
    // dwSource -->  0x00 : 2(A/B)-Phase 신호.
    // dwSource -->  0x01 : Z-Phase 신호.(방향성 없음.)
function AxcSignalSetEncSource(lChannelNo : LongInt; dwSource : DWord) : DWord; stdcall;

    // 카운터 모듈의 Encoder 입력 신호 선택 설정을 확인한다.
function AxcSignalGetEncSource(lChannelNo : LongInt; dwpSource : PDWord) : DWord; stdcall;

    // 카운터 모듈의 트리거 출력 범위 중 하한 값을 설정한다.
    // 위치 주기 트리거 제품의 경우 위치 주기로 트리거 출력을 발생시킬 범위 중 하한 값을 설정한다.
    // 절대 위치 트리거 제품의 경우 Ram 시작 번지의 트리거 정보의 적용 기준 위치를 설정한다.
    // 단위 : AxcMotSetMoveUnitPerPulse로 설정한 단위.
    // Note : 하한값은 상한값보다 작은값을 설정하여야 합니다.
function AxcTriggerSetBlockLowerPos(lChannelNo : LongInt; dLowerPosition : Double) : DWord; stdcall;

    // 카운터 모듈의 트리거 출력 범위 중 하한 값을 확인한다.
function AxcTriggerGetBlockLowerPos(lChannelNo : LongInt; dpLowerPosition : PDouble) : DWord; stdcall;

    // 카운터 모듈의 트리거 출력 범위 중 상한 값을 설정한다.
    // 위치 주기 트리거 제품의 경우 위치 주기로 트리거 출력을 발생시킬 범위 중 상한 값을 설정한다.
    // 절대 위치 트리거 제품의 경우 트리거 정보가 설정된 Ram 의 마지막 번지의 트리거 정보가 적용되는 위치로 사용된다.
    // 단위 : AxcMotSetMoveUnitPerPulse로 설정한 단위.
    // Note : 상한값은 하한값보다 큰값을 설정하여야 합니다.
function AxcTriggerSetBlockUpperPos(lChannelNo : LongInt; dUpperPosition : Double) : DWord; stdcall;
    // 카운터 모듈의 트리거 출력 범위 중 하한 값을 설정한다.
function AxcTriggerGetBlockUpperPos(lChannelNo : LongInt; dpUpperrPosition : PDouble) : DWord; stdcall;

    // 카운터 모듈의 위치 주기 모드 트리거에 사용되는 위치 주기를 설정한다.
    // 단위 : AxcMotSetMoveUnitPerPulse로 설정한 단위.
function AxcTriggerSetPosPeriod(lChannelNo : LongInt; dPeriod : Double) : DWord; stdcall;

    // 카운터 모듈의 위치 주기 모드 트리거에 사용되는 위치 주기를 확인한다.
function AxcTriggerGetPosPeriod(lChannelNo : LongInt; dpPeriod : PDouble) : DWord; stdcall;

    // 카운터 모듈의 위치 주기 모드 트리거 사용시 위치 증감에 대한 유효기능을 설정한다.
    // dwDirection -->  0x00 : 카운터의 증/감에 대하여 트리거 주기 마다 출력.
    // dwDirection -->  0x01 : 카운터가 증가 할때만 트리거 주기 마다 출력.
    // dwDirection -->  0x01 : 카운터가 감소 할때만 트리거 주기 마다 출력.
function AxcTriggerSetDirectionCheck(lChannelNo : LongInt; dwDirection : DWord) : DWord; stdcall;
    // 카운터 모듈의 위치 주기 모드 트리거 사용시 위치 증감에 대한 유효기능 설정을 확인한다.
function AxcTriggerGetDirectionCheck(lChannelNo : LongInt; dwpDirection : PDWord) : DWord; stdcall;

    // 카운터 모듈의 위치 주기 모드 트리거 기능의 범위, 위치 주기를 한번에 설정한다.
    // 위치 설정 단위 :  AxcMotSetMoveUnitPerPulse로 설정한 단위.
function AxcTriggerSetBlock(lChannelNo : LongInt; dLower : Double; dUpper : Double; dABSod : Double) : DWord; stdcall;

    // 카운터 모듈의 위치 주기 모드 트리거 기능의 범위, 위치 주기를 설정을 한번에 확인한다.
function AxcTriggerGetBlock(lChannelNo : LongInt; dpLower : PDouble; dpUpper : PDouble; dpABSod : PDouble) : DWord; stdcall;

    // 카운터 모듈의 트리거 출력 펄스 폭을 설정한다.
    // 단위 : uSec
function AxcTriggerSetTime(lChannelNo : LongInt; dTrigTime : Double) : DWord; stdcall;

    // 카운터 모듈의 트리거 출력 펄스 폭 설정을 확인한다.
function AxcTriggerGetTime(lChannelNo : LongInt; dpTrigTime : PDouble) : DWord; stdcall;

    // 카운터 모듈의 트리거 출력 펄스의 출력 레벨을 설정한다.
    // dwLevel -->  0x00 : 트리거 출력시 'Low' 레벨 출력.
    // dwLevel -->  0x00 : 트리거 출력시 'High' 레벨 출력.
function AxcTriggerSetLevel(lChannelNo : LongInt; dwLevel : DWord) : DWord; stdcall;
    // 카운터 모듈의 트리거 출력 펄스의 출력 레벨 설정을 확인한다.
function AxcTriggerGetLevel(lChannelNo : LongInt; dwpLevel : PDWord) : DWord; stdcall;

    // 카운터 모듈의 주파수 트리거 출력 기능에 필요한 주파수를 설정한다.
    // 단위 : Hz, 범위 : 1Hz ~ 500 kHz
function AxcTriggerSetFreq(lChannelNo : LongInt; dwFreqency : DWord) : DWord; stdcall;
    // 카운터 모듈의 주파수 트리거 출력 기능에 필요한 주파수를 설정을 확인한다.
function AxcTriggerGetFreq(lChannelNo : LongInt; dwpFreqency : PDWord) : DWord; stdcall;	

    // 카운터 모듈의 지정 채널에 대한 범용 출력 값을 설정한다.
    // dwOutput 범위 : 0x00 ~ 0x0F, 각 채널당 4개의 범용 출력
function AxcSignalWriteOutput(lChannelNo : LongInt; dwOutput : DWord) : DWord; stdcall;

    // 카운터 모듈의 지정 채널에 대한 범용 출력 값을 확인한다.
function AxcSignalReadOutput(lChannelNo : LongInt; dwpOutput : PDWord) : DWord; stdcall;

    // 카운터 모듈의 지정 채널에 대한 범용 출력 값을 비트 별로 설정한다.
    // lBitNo 범위 : 0 ~ 3, 각 채널당 4개의 범용 출력
function AxcSignalWriteOutputBit(lChannelNo : LongInt; lBitNo : LongInt; uOnOff : DWord) : DWord; stdcall;
    // 카운터 모듈의 지정 채널에 대한 범용 출력 값을 비트 별로 확인 한다.
    // lBitNo 범위 : 0 ~ 3
function AxcSignalReadOutputBit(lChannelNo : LongInt; lBitNo : LongInt; upOnOff : PDWord) : DWord; stdcall;

    // 카운터 모듈의 지정 채널에 대한 범용 입력 값을 확인한다.
function AxcSignalReadInput(lChannelNo : LongInt; dwpInput : PDWord) : DWord; stdcall;

    // 카운터 모듈의 지정 채널에 대한 범용 입력 값을 비트 별로 확인 한다.
    // lBitNo 범위 : 0 ~ 3
function AxcSignalReadInputBit(lChannelNo : LongInt; lBitNo : LongInt; upOnOff : PDWord) : DWord; stdcall;

    // 카운터 모듈의 트리거 출력을 활성화 한다.
    // 현재 설정된 기능에 따라 트리거 출력이 최종적으로 출력할 것인지 설정한다.
function AxcTriggerSetEnable(lChannelNo : LongInt; dwUsage : DWord) : DWord; stdcall;

    // 카운터 모듈의 트리거 출력 활설화 설정 내용을 확인하다.
function AxcTriggerGetEnable(lChannelNo : LongInt; dwpUsage : PDWord) : DWord; stdcall;

    // 카운터 모듈의 절대위치 트리거 기능을 위해 설정된 RAM 내용을 확인한다.
    // dwAddr 범위 : 0x0000 ~ 0x1FFFF;
function AxcTriggerReadAbsRamData(lChannelNo : LongInt; dwAddr : DWord; dwpData : PDWord) : DWord; stdcall;

    // 카운터 모듈의 절대위치 트리거 기능을 위해 필요한 RAM 내용을 설정한다.
    // dwAddr 범위 : 0x0000 ~ 0x1FFFF;
function AxcTriggerWriteAbsRamData(lChannelNo : LongInt; dwAddr : DWord; dwData : DWord) : DWord; stdcall;

    // 카운터 모듈의 절대위치 트리거 기능을 위해 필요한 RAM 내용을 한번에 설정한다.
    // dwTrigNum 범위 : ~ 0x20000  *RTEX CNT2 의 경우 0x200*
    // dwDirection --> 0x0 : 하한 트리거 위치에 대한 트리거 정보 부터 입력. 위치가 증가하는 방향으로 트리거 출력시 사용.
    // dwDirection --> 0x1 : 상한 카운터에 대한 트리거 정보 부터 입력. 위치가 감소하는 방향으로 트리거 출력시 사용.
function AxcTriggerSetAbs(lChannelNo : LongInt; dwTrigNum : DWord; dwTrigPos : PDWord; dwDirection : DWord) : DWord; stdcall;

implementation

const

    dll_name    = 'AXL.dll';

    function AxcInfoIsCNTModule; external dll_name name 'AxcInfoIsCNTModule';
    function AxcInfoGetModuleNo; external dll_name name 'AxcInfoGetModuleNo';
    function AxcInfoGetModuleCount; external dll_name name 'AxcInfoGetModuleCount';
    function AxcInfoGetChannelCount; external dll_name name 'AxcInfoGetChannelCount';
    function AxcInfoGetTotalChannelCount; external dll_name name 'AxcInfoGetTotalChannelCount';
    function AxcInfoGetModule; external dll_name name 'AxcInfoGetModule';
    function AxcInfoGetModuleStatus; external dll_name name 'AxcInfoGetModuleStatus';
    function AxcInfoGetFirstChannelNoOfModuleNo; external dll_name name 'AxcInfoGetFirstChannelNoOfModuleNo';
    function AxcSignalSetEncInputMethod; external dll_name name 'AxcSignalSetEncInputMethod';
    function AxcSignalGetEncInputMethod; external dll_name name 'AxcSignalGetEncInputMethod';
    function AxcTriggerSetFunction; external dll_name name 'AxcTriggerSetFunction';
    function AxcTriggerGetFunction; external dll_name name 'AxcTriggerGetFunction';
    function AxcTriggerSetNotchEnable; external dll_name name 'AxcTriggerSetNotchEnable';
    function AxcTriggerGetNotchEnable; external dll_name name 'AxcTriggerGetNotchEnable';
    function AxcSignalSetCaptureFunction; external dll_name name 'AxcSignalSetCaptureFunction';
    function AxcSignalGetCaptureFunction; external dll_name name 'AxcSignalGetCaptureFunction';
    function AxcSignalGetCapturePos; external dll_name name 'AxcSignalGetCapturePos';
    function AxcStatusGetActPos; external dll_name name 'AxcStatusGetActPos';
    function AxcStatusSetActPos; external dll_name name 'AxcStatusSetActPos';
    function AxcTriggerSetNotchPos; external dll_name name 'AxcTriggerSetNotchPos';
    function AxcTriggerGetNotchPos; external dll_name name 'AxcTriggerGetNotchPos';
    function AxcTriggerSetOutput; external dll_name name 'AxcTriggerSetOutput';
    function AxcStatusGetChannel; external dll_name name 'AxcStatusGetChannel';
    function AxcMotSetMoveUnitPerPulse; external dll_name name 'AxcMotSetMoveUnitPerPulse';
    function AxcMotGetMoveUnitPerPulse; external dll_name name 'AxcMotGetMoveUnitPerPulse';
    function AxcSignalSetEncReverse; external dll_name name 'AxcSignalSetEncReverse';
    function AxcSignalGetEncReverse; external dll_name name 'AxcSignalGetEncReverse';
    function AxcSignalSetEncSource; external dll_name name 'AxcSignalSetEncSource';
    function AxcSignalGetEncSource; external dll_name name 'AxcSignalGetEncSource';
    function AxcTriggerSetBlockLowerPos; external dll_name name 'AxcTriggerSetBlockLowerPos';
    function AxcTriggerGetBlockLowerPos; external dll_name name 'AxcTriggerGetBlockLowerPos';
    function AxcTriggerSetBlockUpperPos; external dll_name name 'AxcTriggerSetBlockUpperPos';
    function AxcTriggerGetBlockUpperPos; external dll_name name 'AxcTriggerGetBlockUpperPos';
    function AxcTriggerSetPosPeriod; external dll_name name 'AxcTriggerSetPosPeriod';
    function AxcTriggerGetPosPeriod; external dll_name name 'AxcTriggerGetPosPeriod';
    function AxcTriggerSetDirectionCheck; external dll_name name 'AxcTriggerSetDirectionCheck';
    function AxcTriggerGetDirectionCheck; external dll_name name 'AxcTriggerGetDirectionCheck';
    function AxcTriggerSetBlock; external dll_name name 'AxcTriggerSetBlock';
    function AxcTriggerGetBlock; external dll_name name 'AxcTriggerGetBlock';
    function AxcTriggerSetTime; external dll_name name 'AxcTriggerSetTime';
    function AxcTriggerGetTime; external dll_name name 'AxcTriggerGetTime';
    function AxcTriggerSetLevel; external dll_name name 'AxcTriggerSetLevel';
    function AxcTriggerGetLevel; external dll_name name 'AxcTriggerGetLevel';
    function AxcTriggerSetFreq; external dll_name name 'AxcTriggerSetFreq';
    function AxcTriggerGetFreq; external dll_name name 'AxcTriggerGetFreq';
    function AxcSignalWriteOutput; external dll_name name 'AxcSignalWriteOutput';
    function AxcSignalReadOutput; external dll_name name 'AxcSignalReadOutput';
    function AxcSignalWriteOutputBit; external dll_name name 'AxcSignalWriteOutputBit';
    function AxcSignalReadOutputBit; external dll_name name 'AxcSignalReadOutputBit';
    function AxcSignalReadInput; external dll_name name 'AxcSignalReadInput';
    function AxcSignalReadInputBit; external dll_name name 'AxcSignalReadInputBit';
    function AxcTriggerSetEnable; external dll_name name 'AxcTriggerSetEnable';
    function AxcTriggerGetEnable; external dll_name name 'AxcTriggerGetEnable';
    function AxcTriggerReadAbsRamData; external dll_name name 'AxcTriggerReadAbsRamData';
    function AxcTriggerWriteAbsRamData; external dll_name name 'AxcTriggerWriteAbsRamData';
    function AxcTriggerSetAbs; external dll_name name 'AxcTriggerSetAbs';
end.
