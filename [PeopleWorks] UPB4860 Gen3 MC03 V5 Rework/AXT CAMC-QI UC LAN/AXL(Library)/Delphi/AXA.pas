//****************************************************************************
//****************************************************************************
//**
//** File Name
//** ----------
//**
//** AXA.PAS
//**
//** COPYRIGHT (c) AJINEXTEK Co., LTD
//**
//*****************************************************************************
//*****************************************************************************
//**
//** Description
//** -----------
//** Ajinextek Analog Library Header File
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

unit AXA;

interface

uses Windows, Messages, AXHS;
//========== 보드 및 모듈 정보 확인 함수 =================================================================================
    //AIO 모듈이 있는지 확인한다
function AxaInfoIsAIOModule (upStatus : PDWord) : DWord; stdcall;

    //모듈 No를 확인한다.
function AxaInfoGetModuleNo (lBoardNo: LongInt; lModulePos :  LongInt; lpModuleNo :  PLongInt) : DWord; stdcall;

    //AIO 모듈의 개수를 확인한다.
function AxaInfoGetModuleCount (lpModuleCount : PLongInt) : DWord; stdcall;

    //지정한 모듈의 입력 채널 수를 확인한다
function AxaInfoGetInputCount (lModuleNo : LongInt; lpCount : PLongInt) : DWord; stdcall;

    //지정한 모듈의 출력 채널 수를 확인한다.
function AxaInfoGetOutputCount (lModuleNo : LongInt; lpCount : PLongInt) : DWord; stdcall;

    //지정한 모듈의 첫 번째 채널 번호를 확인한다. 
function AxaInfoGetChannelNoOfModuleNo (lModuleNo : LongInt; lpChannelNo : PLongInt) : DWord; stdcall;

    //지정한 모듈의 첫 번째 입력 채널 번호를 확인한다.(입력 모듈, 입력/출력 통합 모듈용)
function AxaInfoGetChannelNoAdcOfModuleNo (lModuleNo : LongInt; lpChannelNo : PLongInt) : DWord; stdcall;

    //지정한 모듈의 첫 번째 출력 채널 번호를 확인한다.(출력 모듈, 입력/출력 통합 모듈용)
function AxaInfoGetChannelNoDacOfModuleNo (lModuleNo : LongInt; lpChannelNo : PLongInt) : DWord; stdcall;

    //지정한 모듈 번호로 베이스 보드 번호, 모듈 위치, 모듈 ID를 확인한다.
function AxaInfoGetModule (lModuleNo : LongInt; lpBoardNo : PLongInt; lpModulePos : PLongInt; upModuleID : PDWord) : DWord; stdcall;

    // 해당 모듈이 제어가 가능한 상태인지 반환한다.
function AxaInfoGetModuleStatus(lModuleNo : LongInt) : DWord; stdcall;

//========== 입력 모듈 정보 검색 함수 ====================================================================================
    //지정한 입력 채널 번호로 모듈 번호를 확인한다.
function AxaiInfoGetModuleNoOfChannelNo (lChannelNo : LongInt; lpModuleNo : PLongInt) : DWord; stdcall;

    //아날로그 입력 모듈의 전체 채널 개수를 확인한다.
function AxaiInfoGetChannelCount (lpChannelCount : PLongInt) : DWord; stdcall;

//========== 입력 모듈 인터럽트/채널 이벤트 설정 및 확인 함수 ============================================================
    //지정한 채널에 이벤트 메시지를 받아오기 위하여 윈도우 메시지, 콜백 함수 또는 이벤트 방식을 사용한다. H/W 타이머(Timer Trigger Mode, External Trigger Mode)를 이용, 연속적 데이터 수집 동작시(AxaiHwStartMultiChannel 참조)에 사용한다.
    // 지정한 모듈에 인터럽트 메시지를 받아오기 위하여 윈도우 메시지, 콜백 함수 또는 이벤트 방식을 사용
    //========= 인터럽트 관련 함수 ======================================================================================
    // 콜백 함수 방식은 이벤트 발생 시점에 즉시 콜백 함수가 호출 됨으로 가장 빠르게 이벤트를 통지받을 수 있는 장점이 있으나
    // 콜백 함수가 완전히 종료 될 때까지 메인 프로세스가 정체되어 있게 된다.
    // 즉, 콜백 함수 내에 부하가 걸리는 작업이 있을 경우에는 사용에 주의를 요한다. 
    // 이벤트 방식은 쓰레드등을 이용하여 인터럽트 발생여부를 지속적으로 감시하고 있다가 인터럽트가 발생하면 
    // 처리해주는 방법으로, 쓰레드 등으로 인해 시스템 자원을 점유하고 있는 단점이 있지만
    // 가장 빠르게 인터럽트를 검출하고 처리해줄 수 있는 장점이 있다.
    // 일반적으로는 많이 쓰이지 않지만, 인터럽트의 빠른처리가 주요 관심사인 경우에 사용된다. 
    // 이벤트 방식은 이벤트의 발생 여부를 감시하는 특정 쓰레드를 사용하여 메인 프로세스와 별개로 동작되므로
    // MultiProcessor 시스템등에서 자원을 가장 효율적으로 사용할 수 있게 되어 특히 권장하는 방식이다.
    // 인터럽트 메시지를 받아오기 위하여 윈도우 메시지 또는 콜백 함수를 사용한다.
    // (메시지 핸들, 메시지 ID, 콜백함수, 인터럽트 이벤트)
    //    hWnd    : 윈도우 핸들, 윈도우 메세지를 받을때 사용. 사용하지 않으면 NULL을 입력.
    //    uMessage: 윈도우 핸들의 메세지, 사용하지 않거나 디폴트값을 사용하려면 0을 입력.
    //    proc    : 인터럽트 발생시 호출될 함수의 포인터, 사용하지 않으면 NULL을 입력.
    //    pEvent  : 이벤트 방법사용시 이벤트 핸들
function AxaiEventSetChannel (lChannelNo : LongInt; hWnd : HWND; uMesssage : DWord; pProc : AXT_EVENT_PROC; pEvent : PDWord) : DWord; stdcall;

    //지정한 입력 채널에 이벤트 사용 유무를 설정한다.
    //======================================================//
    // uUse       : DISABLE(0)    // 이벤트 해제
    //            : ENABLE(1)     // 이벤트 설정
    //======================================================//
function AxaiEventSetChannelEnable (lChannelNo : LongInt; uUse : DWord) : DWord; stdcall;

    //지정한 입력 채널의 이벤트 사용 유무를 확인한다.
    //======================================================//
    // *upUse     : DISABLE(0)    // 이벤트 해제
    //            : ENABLE(1)     // 이벤트 설정
    //======================================================//
function AxaiEventGetChannelEnable (lChannelNo : LongInt; upUse : PDWord) : DWord; stdcall;

    //지정한 여러 입력 채널에 이벤트 사용 유무를 설정한다.
    //======================================================//
    // lSize      : 사용 할 입력 채널의 갯수
    // lpChannelNo: 사용할 채널 번호의 배열
    // uUse       : DISABLE(0)    // 이벤트 해제
    //            : ENABLE(1)     // 이벤트 설정
    //======================================================//
function AxaiEventSetMultiChannelEnable (lSize : LongInt; lpChannelNo : PLongInt; uUse : DWord) : DWord; stdcall;

    //지정한 입력 채널에 이벤트 종류를 설정한다.
    //======================================================//
    // uMask      : DATA_EMPTY(1) --> 버퍼에 데이터가 없을 때
    //            : DATA_MANY(2)  --> 버퍼에 데이터가 상한 설정 값보다 많아질 때
    //            : DATA_SMALL(3) --> 버퍼에 데이터가 하한 설정 값보다 적어질 때
    //            : DATA_FULL(4)  --> 버퍼에 데이터가 꽉 찼을 때
    //======================================================//
function AxaiEventSetChannelMask (lChannelNo : LongInt; uMask : DWord) : DWord; stdcall;

    //지정한 입력 채널에 이벤트 종류를 확인한다.
    //======================================================//
    // *upMask    : DATA_EMPTY(1) --> 버퍼에 데이터가 없을 때
    //            : DATA_MANY(2)  --> 버퍼에 데이터가 상한 설정 값보다 많아질 때
    //            : DATA_SMALL(3) --> 버퍼에 데이터가 하한 설정 값보다 적어질 때
    //            : DATA_FULL(4)  --> 버퍼에 데이터가 꽉 찼을 때
    //======================================================//
function AxaiEventGetChannelMask (lChannelNo : LongInt; upMask : PDWord) : DWord; stdcall;

    //지정한 여러 입력 채널에 이벤트 종류를 설정한다.
    //==============================================================================//
    // lSize      : 사용 할 입력 채널의 갯수
    // lpChannelNo: 사용할 채널 번호의 배열
    // uMask      : DATA_EMPTY(1) --> 버퍼에 데이터가 없을 때
    //            : DATA_MANY(2)  --> 버퍼에 데이터가 상한 설정 값보다 많아질 때
    //            : DATA_SMALL(3) --> 버퍼에 데이터가 하한 설정 값보다 적어질 때
    //            : DATA_FULL(4)  --> 버퍼에 데이터가 꽉 찼을 때
    //==============================================================================//
function AxaiEventSetMultiChannelMask (lSize : LongInt; lpChannelNo : PLongInt; uMask : DWord) : DWord; stdcall;

    //이벤트 발생 위치를 확인한다.
    //==============================================================================//
    // *upMode    : AIO_EVENT_DATA_UPPER(1) --> 버퍼에 데이터가 상한 설정 값보다 많아질 때
    //            : AIO_EVENT_DATA_LOWER(2) --> 버퍼에 데이터가 하한 설정 값보다 적어질 때
    //            : AIO_EVENT_DATA_FULL(3)  --> 버퍼에 데이터가 꽉 찼을 때
    //            : AIO_EVENT_DATA_EMPTY(4) --> 버퍼에 데이터가 없을 때
    //==============================================================================//
function AxaiEventRead (lpChannelNo : PLongInt; upMode : PDWord) : DWord; stdcall;

    //지정한 모듈의 인터럽트 마스크를 설정한다. 이 함수는 연속적 신호감시를 할 경우에 하드웨어(모듈)의 FIFO 에서 사용자가 지정한 크기의 버퍼로 내부 인터럽트를 통한 데이터 이동 시점을 지정하기 위해 사용된다. (SIO-AI4RB는 지원하지 않는다.)
    //==================================================================================================//
    // uMask       : SCAN_END(1)       --> 셋팅된 채널 모두  ADC 변환이 한번 이루어 질 때 마다 인터럽트가 발생
    //             : FIFO_HALF_FULL(2) --> 모듈내의 FIFO가 HALF이상 찼을 경우 내부 인터럽트 발생
    //==================================================================================================//
function AxaiInterruptSetModuleMask(lpChannelNo : PLongInt; uMask : Dword) : DWord; stdcall;
    
    //지정한 모듈의 인터럽트 마스크를 확인한다.
    //==================================================================================================//
    // *upMask     : SCAN_END(1)       --> 셋팅된 채널 모두  ADC 변환이 한번 이루어 질 때 마다 인터럽트가 발생
    //             : FIFO_HALF_FULL(2) --> 모듈내의 FIFO가 HALF이상 찼을 경우 내부 인터럽트 발생
    //==================================================================================================//
function  AxaiInterruptGetModuleMask(lpChannelNo : PLongInt; upMask : PDWord) : DWord; stdcall;

    //지정한 모듈의 인터럽트 마스크를 설정한다. 이 함수는 연속적 신호감시를 할 경우에 하드웨어(모듈)의 FIFO 에서 사용자가 지정한 크기의 버퍼로 내부 인터럽트를 통한 데이터 이동 시점을 지정하기 위해 사용된다. (SIO-AI4RB는 지원하지 않는다.)
    //==================================================================================================//
    // uMask      : SCAN_END(1)       --> 셋팅된 채널 모두  ADC 변환이 한번 이루어 질 때 마다 인터럽트가 발생
    //            : FIFO_HALF_FULL(2) --> 모듈내의 FIFO가 HALF이상 찼을 경우 내부 인터럽트 발생
    //==================================================================================================//
function AxaSetMoudleInterruptMaskAdc (lModuleNo : LongInt; uMask : DWord) : DWord; stdcall;

    //지정한 모듈의 인터럽트 마스크를 확인한다.
    //==================================================================================================//
    // *upMask    : SCAN_END(1)       --> 셋팅된 채널 모두  ADC 변환이 한번 이루어 질 때 마다 인터럽트가 발생
    //            : FIFO_HALF_FULL(2) --> 모듈내의 FIFO가 HALF이상 찼을 경우 내부 인터럽트 발생
    //==================================================================================================//
function AxaGetMoudleInterruptMaskAdc (lModuleNo : LongInt; upMask : PDWord) : DWord; stdcall;

//========== 입력 모듈 파라미터 설정 및 확인 함수 ======================================================
    //지정한 입력 채널에 입력 전압 범위를 설정한다.
    //==================================================================================================//
    // AI4RB
    // dMinVolt    : -10V/-5V/0V로 설정 가능
    // dMaxVolt    : 10V/5V/로 설정 가능
    //
    // AI16Hx
    // dMinVolt    : -10V 고정
    // dMaxVolt    : 10V 고정
    //==================================================================================================//
function AxaiSetRange (lChannelNo : LongInt; dMinVolt : Double; dMaxVolt : Double) : DWord; stdcall;

    //지정한 입력 채널의 입력 전압 범위를 확인한다.
    //==================================================================================================//
    // AI4RB
    // *dpMinVolt  : -10V/-5V/0V로 설정 가능
    // *dpMaxVolt  : 10V/5V/로 설정 가능
    //
    // AI16Hx
    // *dpMaxVolt  : -10V 고정
    // *dpMaxVolt  : 10V 고정
    //==================================================================================================//
function AxaiGetRange (lChannelNo : LongInt; dpMinVolt : PDouble; dpMaxVolt : PDouble) : DWord; stdcall;

    //지정한 여러 입력 모듈에 허용 입력 전압 범위를 설정한다.
    //==================================================================================================//
    // lModuleNo   : 사용할 입력 모듈 번호
    //
    // RTEX AI16F
    // Mode -5~+5  : dMinVolt = -5, dMaxVolt = +5
    // Mode -10~+10: dMinVolt = -10, dMaxVolt = +10
    //==================================================================================================//
function  AxaiSetRangeModule(lModuleNo : LongInt; dMinVolt : Double; dMaxVolt : Double) : DWord; stdcall;

    //지정한 여러 입력 모듈에 허용 입력 전압 범위를 확인한다.
    //==================================================================================================//
    // lModuleNo   : 사용할 입력 모듈 번호
    //
    // RTEX AI16F
    // *dMinVolt   : -5V, -10V
    // *dMaxVolt   : +5V, +10V
    //==================================================================================================//
function  AxaiGetRangeModule(lModuleNo : LongInt; dpMinVolt : PDouble; dpMaxVolt : PDouble) : DWord; stdcall;

    //지정한 여러 입력 채널에 허용 입력 전압 범위를 설정한다.
    //==================================================================================================//
    // lSize       : 사용할 입력 채널의 개수
    // *lpChannelNo: 사용할 채널 번호의 배열
    //
    // AI4RB
    // dMinVolt    : -10V/-5V/0V로 설정 가능
    // dMaxVolt    : 10V/5V/로 설정 가능
    //
    // AI16Hx
    // dMinVolt    : -10V
    // dMaxVolt    : 10V
    //==================================================================================================//
function AxaiSetMultiRange (lSize : LongInt; lpChannelNo : PLongInt; dMinVolt : Double; dMaxVolt : Double) : DWord; stdcall;

    //지정한 입력 모듈에 트리거 모드를 설정한다.
    //==================================================================================================//
    // uTriggerMode: NORMAL_MODE(1)   --> 사용자가 원하는 시점에 A/D변환하는 Software Trigger 방식 
    //             : TIMER_MODE(2)    --> H/W의 내부 클럭을 이용해서 A/D변환하는 Trigger 방식
    //             : EXTERNAL_MODE(3) --> 외부 입력단자의 클럭을 이용해서 A/D변환하는 Trigger 방식
    //==================================================================================================//
function AxaiSetTriggerMode (lModuleNo : LongInt; uTriggerMode : DWord) : DWord; stdcall;

    //지정한 모듈에 트리거 모드를 확인한다.
    //==================================================================================================//
    // *upTriggerMode : NORMAL_MODE(1) --> 사용자가 원하는 시점에 A/D변환하는 Software Trigger 방식 
    //                : TIMER_MODE(2) --> H/W의 내부 클럭을 이용해서 A/D변환하는 Trigger 방식
    //                : EXTERNAL_MODE(3) --> 외부 입력단자의 클럭을 이용해서 A/D변환하는 Trigger 방식
    //==================================================================================================//
function AxaiGetTriggerMode (lModuleNo : LongInt; upTriggerMode : PDWord) : DWord; stdcall;

    //지정한 입력모듈의 Offset을 mVolt 단위(mV)로 설정한다. 최대 -100~100mVolt
    //==================================================================================================//
    // dMiliVolt      : -100 ~ 100 
    //==================================================================================================//
function AxaiSetModuleOffsetValue(lModuleNo : LongInt; dMiliVolt : Double) : DWord; stdcall;

    //지정한 입력모듈의 Offset 값을 확인한다. mVolt 단위(mV)
    //==================================================================================================//
    // *dpMiliVolt    : -100 ~ 100 
    //==================================================================================================//
function AxaiGetModuleOffsetValue(lModuleNo : LongInt; dpMiliVolt : PDouble) : DWord; stdcall;

//========== 입력 모듈 A/D 변환 함수 ===================================================================
    //사용자가 지정한 입력 채널에 아날로그 입력 값을 A/D변환한 후 전압 값으로 반환한다.이 함수를 사용하기 전에 AxaiSetTriggerMode 함수를 사용하여 Normal Trigger Mode로 설정되어 있어야 한다.
function AxaiSwReadVoltage (lChannelNo : LongInt; dpVolt : PDouble) : DWord; stdcall;

    //지정한 입력 채널에 아날로그 입력 값을 Digit 값으로 반환한다. Normal Trigger Mode로 설정되어 있어야 한다.
function AxaiSwReadDigit (lChannelNo : LongInt; upDigit : PDWord) : DWord; stdcall;

    //지정한 여러 입력 채널에 아날로그 입력 값을 전압 값으로 반환한다. Normal Trigger Mode로 설정되어 있어야 한다.
function AxaiSwReadMultiVoltage (lSize : LongInt; lpChannelNo : PLongInt; dpVolt : PDouble) : DWord; stdcall;

    //지정한 여러 입력 채널에 아날로그 입력 값을 Digit 값으로 반환한다. Normal Trigger Mode로 설정되어 있어야 한다.
function AxaiSwReadMultiDigit (lSize : LongInt; lpChannelNo : PLongInt; upDigit : PDWord) : DWord; stdcall;

    //지정한 여러 입력 채널에 Immediate모드를 사용하기 위해 설정 값을 설정한다. 이 함수를 사용하기 전에 AxaiSetTriggerMode 함수를 사용하여 Timer Trigger Mode로 설정되어 있어야 한다.
function AxaiHwSetMultiAccess (lSize : LongInt; lpChannelNo : PLongInt; lpWordSize : PLongInt) : DWord; stdcall;

    //지정한 개수만큼 A/D변환 후 전압 값을 반환한다. 이 함수를 사용하기 전에 AxaiHwSetMultiAccess함수를 이용 설정값을 지정해야 하며 , AxaSetTriggerModeAdc 함수를 사용하여 Timer Trigger Mode로 설정되어 있어야 한다.
function AxaiHwStartMultiAccess (dpBuffer : PDouble) : DWord; stdcall;

    //지정한 모듈에 샘플링 간격을 주파수(Hz) 단위로 설정한다.
    //==================================================================================================//
    // dSampleFreq     : 10 ~ 100000 
    //==================================================================================================//
function AxaiHwSetSampleFreq (lModuleNo : LongInt; dSampleFreq : Double) : DWord; stdcall;

    //지정한 모듈에 샘플링 간격을 주파수(Hz) 단위로 설정된 값을 확인한다.
    //==================================================================================================//
    // *dpSampleFreq   : 10 ~ 100000 
    //==================================================================================================//
function AxaiHwGetSampleFreq (lModuleNo : LongInt; dpSampleFreq : PDouble) : DWord; stdcall;

    //지정한 모듈에 샘플링 간격을 시간 단위(uSec)로 설정한다.
    //==================================================================================================//
    // dSamplePeriod   : 100000 ~ 1000000000
    //==================================================================================================//
function AxaiHwSetSamplePeriod (lModuleNo : LongInt; dSamplePeriod : Double) : DWord; stdcall;

    //지정한 모듈에 샘플링 간격을 시간 단위(uSec)로 설정된 값을 확인한다.
    //==================================================================================================//
    // *dpSamplePeriod : 100000 ~ 1000000000
    //==================================================================================================//
function AxaiHwGetSamplePeriod (lModuleNo : LongInt; dpSamplePeriod : PDouble) : DWord; stdcall;

    //지정한 입력 채널에 버퍼가 Full로 찼을 때 관리 방식을 설정한다.
    //==================================================================================================//
    // uFullMode       : NEW_DATA_KEEP(0)  --> 새로운 데이터 유지
    //                 : CURR_DATA_KEEP(1) --> 이전 데이터 유지
    //==================================================================================================//
function AxaiHwSetBufferOverflowMode (lChannelNo : LongInt; uFullMode : DWord) : DWord; stdcall;

    //지정한 입력 채널이 버퍼가 Full로 찼을 때 관리 방식을 확인한다.
    //==================================================================================================//
    // *upFullMode     : NEW_DATA_KEEP(0)  --> 새로운 데이터 유지
    //                 : CURR_DATA_KEEP(1) --> 이전 데이터 유지
    //==================================================================================================//
function AxaiHwGetBufferOverflowMode (lChannelNo : LongInt; upFullMode : PDWord) : DWord; stdcall;

    //지정한 여러 입력 채널에 버퍼가 Full로 찼을 때 관리 방식을 설정한다.
    //==================================================================================================//
    // uFullMode       : NEW_DATA_KEEP(0)  --> 새로운 데이터 유지
    //                 : CURR_DATA_KEEP(1) --> 이전 데이터 유지
    //==================================================================================================//
function AxaiHwSetMultiBufferOverflowMode (lSize : LongInt; lpChannelNo : PLongInt; uFullMode : DWord) : DWord; stdcall;

    //지정한 입력 채널에 버퍼의 상한 값과 하한 값을 설정한다.
function AxaiHwSetLimit (lChannelNo : LongInt; lLowLimit : LongInt; lUpLimit : LongInt) : DWord; stdcall;

    //지정한 입력 채널에 버퍼의 상한 값과 하한 값을 확인한다.
function AxaiHwGetLimit (lChannelNo : LongInt; lpLowLimit : PLongInt; lpUpLimit : PLongInt) : DWord; stdcall;

    //지정한 여러 입력 채널에 버퍼의 상한 값과 하한 값을 설정한다.
function AxaiHwSetMultiLimit (lSize : LongInt; lpChannelNo : PLongInt; lLowLimit : LongInt; lUpLimit : LongInt) : DWord; stdcall;

    //지정한 여러 입력 채널에 H/W타이머를 이용한 A/D변환을 시작한다.
function AxaiHwStartMultiChannel (lSize : LongInt; lpChannelNo : PLongInt; lBuffSize : LongInt) : DWord; stdcall;

    //지정한 여러 입력 채널에 A/D변환을 시작 후 지정한 개수만큼 필터 처리해서 전압으로 반환한다.
    //==================================================================================================//
    // lSize        : 사용할 입력 채널의 개수
    // *lpChannelNo : 사용할 채널 번호의 배열
    // lFilterCount : Filtering할 데이터의 개수
    // lBuffSize    : 각 채널에 할당되는 버퍼의 개수
    //==================================================================================================//
function AxaiHwStartMultiFilter (lSize : LongInt; lpChannelNo : PLongInt; lFilterCount : LongInt; lBuffSize : LongInt) : DWord; stdcall;

    //H/W타이머를 이용한 연속 신호 A/D변환을 중지한다.
function AxaiHwStopMultiChannel (lModuleNo : LongInt) : DWord; stdcall;

    //지정한 입력 채널의 메모리 버퍼에 데이터가 몇 개인지 검사한다.
function AxaiHwReadDataLength (lChannelNo : LongInt; lpDataLength : PLongInt) : DWord; stdcall;

    //지정한 입력 채널에 H/W타이머를 이용하여 A/D변환된 값을 전압 값으로 읽는다.
function AxaiHwReadSampleVoltage (lChannelNo : LongInt; lSize : PLongInt; dpVolt : PDouble) : DWord; stdcall;

    //지정한 입력 채널에 H/W타이머를 이용하여 A/D변환된 값을 Digit 값으로 읽는다.
function AxaiHwReadSampleDigit (lChannelNo : LongInt; lSize : PLongInt; upDigit : PDWord) : DWord; stdcall;

//========== 입력 모듈 버퍼 상태 체크 함수 ===================================================================================
    //지정한 입력 채널의 메모리 버퍼에 데이터가 없는 지 검사한다.
    //==================================================================================================//
    // *upEmpty     : FALSE(0) --> 메모리 버퍼에 데이터가 있을 경우
    //              : TRUE(1)  --> 메모리 버퍼에 데이터가 없을 경우
    //==================================================================================================//
function AxaiHwIsBufferEmpty (lChannelNo : LongInt; upEmpty : PDWord) : DWord; stdcall;

    //지정한 입력 채널의 메모리 버퍼에 설정되어 있는 상한 값보다 데이터가 많은 지 검사한다
    //==================================================================================================//
    // *upUpper     : FALSE(0) --> 메모리 버퍼에 데이터가 상한 값보다 적을 경우
    //              : TRUE(1)  --> 메모리 버퍼에 데이터가 상한 값보다 많을 경우
    //==================================================================================================//
function AxaiHwIsBufferUpper (lChannelNo : LongInt; upUpper : PDWord) : DWord; stdcall;

    //지정한 입력 채널의 메모리 버퍼에 설정되어 있는 하한 값보다 데이터가 적은 지 검사한다.
    //==================================================================================================//
    // *upLower     : FALSE(0) --> 메모리 버퍼에 데이터가 하한 값보다 많을 경우
    //              : TRUE(1)  --> 메모리 버퍼에 데이터가 하한 값보다 적을 경우
    //==================================================================================================//
function AxaiHwIsBufferLower (lChannelNo : LongInt; upLower : PDWord) : DWord; stdcall;

//==External Trigger Mode 함수
    //지정한 입력모듈의 선택된 채널들의 외부 트리거 모드를 시작한다.
    //==================================================================================================//
    // lSize            : 지정한 입력 모듈에서 외부트리거를 사용 할 채널갯수
    // *lpChannelPos    : 지정한 입력 모듈에서 외부트리거를 사용 할 채널의 Index
function AxaiExternalStartADC(lModuleNo : LongInt; lSize : LongInt; lpChannelPos : PLongInt) : DWord; stdcall;
    //지정한 입력모듈의 외부트리거 모드를 정지한다.  
function AxaiExternalStopADC(lModuleNo : LongInt) : DWord; stdcall;
    //지정한 입력모듈의 Fifo상태를 반환한다.
    //==================================================================================================//
    // *dwpStatus       : FIFO_DATA_EXIST(0)
    //                  : FIFO_DATA_EMPTY(1)
    //                  : FIFO_DATA_HALF(2)
    //                  : FIFO_DATA_FULL(6)
    //==================================================================================================//
function AxaiExternalReadFifoStatus(lModuleNo : LongInt; dwpStatus : PDWord) : DWord; stdcall;
    //지정한 입력모듈의 외부신호에 의해 변환된 A/D값을 읽어옴.
    // lSize            : 지정한 입력 모듈에서 변환된 A/D값을 읽어올 채널의 갯수(AxaiExternalStartADC에 사용한 채널갯수와 동일 해야됨)
    // *lpChannelPos    : 지정한 입력 모듈에서 변환된 A/D값을 읽어올 채널의 Index(AxaiExternalStartADC에 사용한 채널의 Index와 동일 해야됨)
    // lDataSize        : 외부트리거에 의해 A/D변환된 값을 한번에 읽어 올 최대 데이타의 갯수
    // lBuffSize        : 외부에서(사용자 Program) 할당한 Data Buffer의 Size
    // lStartDataPos    : 외부에서(사용자 Program) 할당한 Data Buffer에 저장 시작 할 위치 
    // *dpVolt[]        : A/D변환된 값을 할당 받을 2차원 배열 포인트(dpVlot[Channel][Count])
    // *lpRetDataSize   : A/D변환된 값이 Data Buffer에 실제 할당된 갯수
    // *dwpStatus       : A/D변환된 값을 Fifo(H/W Buffer)로 부터 읽을 때 Fifo상태를 반환함.
function AxaiExternalReadVoltage(lModuleNo : LongInt; lSize : LongInt; lpChannelPos : PLongInt; lDataSize : LongInt; lBuffSize : LongInt; lStartDataPos : LongInt; dpVolt : PDouble; lpRetDataSize : PLongInt; dwpStatus : PLongInt) : DWord; stdcall;

//========== 출력 모듈 정보 검색 함수 ========================================================================================
    //지정한 출력 채널 번호로 모듈 번호를 확인한다.
function AxaoInfoGetModuleNoOfChannelNo (lChannelNo : LongInt; lpModuleNo : PLongInt) : DWord; stdcall;

    //아날로그 출력 모듈의 전체 채널 개수를 확인한다.
function AxaoInfoGetChannelCount (lpChannelCount : PLongInt) : DWord; stdcall;

//========== 출력 모듈 설정 및 확인 함수 ========================================================================================
    //지정한 출력 채널에 출력 전압 범위를 설정한다
    //==================================================================================================//
    // AO4R, AO2Hx
    // dMinVolt    : -10V
    // dMaxVolt    : 10V
    //==================================================================================================//
function AxaoSetRange (lChannelNo : LongInt; dMinVolt : Double; dMaxVolt : Double) : DWord; stdcall;

    //지정한 출력 채널의 출력 전압 범위를 확인한다.
    //==================================================================================================//
    // AO4R, AO2Hx
    // *dpMinVolt  : -10V
    // *dpMaxVolt  : 10V
    //==================================================================================================//
function AxaoGetRange (lChannelNo : LongInt; dpMinVolt : PDouble; dpMaxVolt : PDouble) : DWord; stdcall;

    //지정한 여러 출력 채널에 출력 전압 범위를 설정한다.
    //==================================================================================================//
    // AO4R, AO2Hx
    // dMinVolt    : -10V
    // dMaxVolt    : 10V
    //==================================================================================================//
function AxaoSetMultiRange (lSize : LongInt; lpChannelNo : PLongInt; dMinVolt : Double; dMaxVolt : Double) : DWord; stdcall;

    //지정한 출력 채널에 입력된 전압이 출력 된다.
function AxaoWriteVoltage (lChannelNo : LongInt; dVolt : Double) : DWord; stdcall;

    //지정한 여러 출력 채널에 입력된 전압이 출력 된다.
function AxaoWriteMultiVoltage (lSize : LongInt; lpChannelNo : PLongInt; dpVolt : PDouble) : DWord; stdcall;

    //지정한 출력 채널에 출력되는 전압 값을 확인한다.
function AxaoReadVoltage (lChannelNo : LongInt; dpVolt : PDouble) : DWord; stdcall;

    //지정한 여러 출력 채널에 출력되는 전압 값을 확인한다.
function AxaoReadMultiVoltage (lSize : LongInt; lpChannelNo : PLongInt; dpVolt : PDouble) : DWord; stdcall;

implementation

const

    dll_name    = 'AXL.dll';

    function AxaInfoIsAIOModule; external dll_name name 'AxaInfoIsAIOModule';
    function AxaInfoGetModuleNo; external dll_name name 'AxaInfoGetModuleNo';
    function AxaInfoGetModuleCount; external dll_name name 'AxaInfoGetModuleCount';
    function AxaInfoGetInputCount; external dll_name name 'AxaInfoGetInputCount';
    function AxaInfoGetOutputCount; external dll_name name 'AxaInfoGetOutputCount';
    function AxaInfoGetChannelNoOfModuleNo; external dll_name name 'AxaInfoGetChannelNoOfModuleNo';
    function AxaInfoGetChannelNoAdcOfModuleNo; external dll_name name 'AxaInfoGetChannelNoAdcOfModuleNo';
    function AxaInfoGetChannelNoDacOfModuleNo; external dll_name name 'AxaInfoGetChannelNoDacOfModuleNo';
    function AxaInfoGetModule; external dll_name name 'AxaInfoGetModule';
    function AxaInfoGetModuleStatus; external dll_name name 'AxaInfoGetModuleStatus';
    function AxaiInfoGetModuleNoOfChannelNo; external dll_name name 'AxaiInfoGetModuleNoOfChannelNo';
    function AxaiInfoGetChannelCount; external dll_name name 'AxaiInfoGetChannelCount';
    function AxaiEventSetChannel; external dll_name name 'AxaiEventSetChannel';
    function AxaiEventSetChannelEnable; external dll_name name 'AxaiEventSetChannelEnable';
    function AxaiEventGetChannelEnable; external dll_name name 'AxaiEventGetChannelEnable';
    function AxaiEventSetMultiChannelEnable; external dll_name name 'AxaiEventSetMultiChannelEnable';
    function AxaiEventSetChannelMask; external dll_name name 'AxaiEventSetChannelMask';
    function AxaiEventGetChannelMask; external dll_name name 'AxaiEventGetChannelMask';
    function AxaiEventSetMultiChannelMask; external dll_name name 'AxaiEventSetMultiChannelMask';
    function AxaiEventRead; external dll_name name 'AxaiEventRead';
    function AxaiInterruptSetModuleMask; external dll_name name 'AxaiInterruptSetModuleMask';
    function AxaiInterruptGetModuleMask; external dll_name name 'AxaiInterruptGetModuleMask';
    function AxaiSetRange; external dll_name name 'AxaiSetRange';
    function AxaiGetRange; external dll_name name 'AxaiGetRange';
    function AxaiSetRangeModule; external dll_name name 'AxaiSetRangeModule';
    function AxaiGetRangeModule; external dll_name name 'AxaiGetRangeModule';
    function AxaiSetMultiRange; external dll_name name 'AxaiSetMultiRange';
    function AxaiSetTriggerMode; external dll_name name 'AxaiSetTriggerMode';
    function AxaiGetTriggerMode; external dll_name name 'AxaiGetTriggerMode';
    function AxaiSwReadVoltage; external dll_name name 'AxaiSwReadVoltage';
    function AxaiSwReadDigit; external dll_name name 'AxaiSwReadDigit';
    function AxaiSwReadMultiVoltage; external dll_name name 'AxaiSwReadMultiVoltage';
    function AxaiSwReadMultiDigit; external dll_name name 'AxaiSwReadMultiDigit';
    function AxaiHwSetMultiAccess; external dll_name name 'AxaiHwSetMultiAccess';
    function AxaiHwStartMultiAccess; external dll_name name 'AxaiHwStartMultiAccess';
    function AxaiHwSetSampleFreq; external dll_name name 'AxaiHwSetSampleFreq';
    function AxaiHwGetSampleFreq; external dll_name name 'AxaiHwGetSampleFreq';
    function AxaiHwSetSamplePeriod; external dll_name name 'AxaiHwSetSamplePeriod';
    function AxaiHwGetSamplePeriod; external dll_name name 'AxaiHwGetSamplePeriod';
    function AxaiHwSetBufferOverflowMode; external dll_name name 'AxaiHwSetBufferOverflowMode';
    function AxaiHwGetBufferOverflowMode; external dll_name name 'AxaiHwGetBufferOverflowMode';
    function AxaiHwSetMultiBufferOverflowMode; external dll_name name 'AxaiHwSetMultiBufferOverflowMode';
    function AxaiHwSetLimit; external dll_name name 'AxaiHwSetLimit';
    function AxaiHwGetLimit; external dll_name name 'AxaiHwGetLimit';
    function AxaiHwSetMultiLimit; external dll_name name 'AxaiHwSetMultiLimit';
    function AxaiHwStartMultiChannel; external dll_name name 'AxaiHwStartMultiChannel';
    function AxaiHwStartMultiFilter; external dll_name name 'AxaiHwStartMultiFilter';
    function AxaiHwStopMultiChannel; external dll_name name 'AxaiHwStopMultiChannel';
    function AxaiHwReadDataLength; external dll_name name 'AxaiHwReadDataLength';
    function AxaiHwReadSampleVoltage; external dll_name name 'AxaiHwReadSampleVoltage';
    function AxaiHwReadSampleDigit; external dll_name name 'AxaiHwReadSampleDigit';
    function AxaiHwIsBufferEmpty; external dll_name name 'AxaiHwIsBufferEmpty';
    function AxaiHwIsBufferUpper; external dll_name name 'AxaiHwIsBufferUpper';
    function AxaiHwIsBufferLower; external dll_name name 'AxaiHwIsBufferLower';
    function AxaiExternalStartADC; external dll_name name 'AxaiExternalStartADC';
    function AxaiExternalStopADC; external dll_name name 'AxaiExternalStopADC';
    function AxaiExternalReadFifoStatus; external dll_name name 'AxaiExternalReadFifoStatus';
    function AxaiExternalReadVoltage; external dll_name name 'AxaiExternalReadVoltage';    
    function AxaoInfoGetModuleNoOfChannelNo; external dll_name name 'AxaoInfoGetModuleNoOfChannelNo';
    function AxaoInfoGetChannelCount; external dll_name name 'AxaoInfoGetChannelCount';
    function AxaoSetRange; external dll_name name 'AxaoSetRange';
    function AxaoGetRange; external dll_name name 'AxaoGetRange';
    function AxaoSetMultiRange; external dll_name name 'AxaoSetMultiRange';
    function AxaoWriteVoltage; external dll_name name 'AxaoWriteVoltage';
    function AxaoWriteMultiVoltage; external dll_name name 'AxaoWriteMultiVoltage';
    function AxaoReadVoltage; external dll_name name 'AxaoReadVoltage';
    function AxaoReadMultiVoltage; external dll_name name 'AxaoReadMultiVoltage';
    function AxaSetMoudleInterruptMaskAdc; external dll_name name 'AxaSetMoudleInterruptMaskAdc';
    function AxaGetMoudleInterruptMaskAdc; external dll_name name 'AxaGetMoudleInterruptMaskAdc';
    function AxaiSetModuleOffsetValue; external dll_name name 'AxaiSetModuleOffsetValue';
    function AxaiGetModuleOffsetValue; external dll_name name 'AxaiGetModuleOffsetValue';
end.
