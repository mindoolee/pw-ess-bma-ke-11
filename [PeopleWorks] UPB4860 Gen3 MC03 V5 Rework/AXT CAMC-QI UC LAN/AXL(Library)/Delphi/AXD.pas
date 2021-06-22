//*****************************************************************************
//*****************************************************************************
//**
//** File Name
//** ----------
//**
//** AXD.PAS
//**
//** COPYRIGHT (c) AJINEXTEK Co., LTD
//**
//*****************************************************************************
//*****************************************************************************
//**
//** Description
//** -----------
//** Ajinextek Digital Library Header File
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

unit AXD;

interface

uses Windows, Messages, AXHS;

//========== 보드 및 모듈 정보 =================================================================================

// DIO 모듈이 있는지 확인
function AxdInfoIsDIOModule (upStatus : PDWord) : DWord; stdcall;

// DIO 모듈 No 확인
function AxdInfoGetModuleNo (lBoardNo : LongInt; lModulePos : LongInt; lpModuleNo : PLongInt) : DWord; stdcall;

// DIO 입출력 모듈의 개수 확인
function AxdInfoGetModuleCount (lpModuleCount : PLongInt) : DWord; stdcall;

// 지정한 모듈의 입력 접점 개수 확인
function AxdInfoGetInputCount (lModuleNo : LongInt; lpCount : PLongInt) : DWord; stdcall;

// 지정한 모듈의 출력 접점 개수 확인
function AxdInfoGetOutputCount (lModuleNo : LongInt; lpCount : PLongInt) : DWord; stdcall;

// 지정한 모듈 번호로 베이스 보드 번호, 모듈 위치, 모듈 ID 확인
function AxdInfoGetModule (lModuleNo : LongInt; lpBoardNo : PLongInt; lpModulePos : PLongInt; upModuleID : PDWord) : DWord; stdcall;

// 해당 모듈이 제어가 가능한 상태인지 반환한다.
function AxdInfoGetModuleStatus(lModuleNo : LongInt) : DWord; stdcall;

//========== 인터럽트 설정 확인 =================================================================================
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
function AxdiInterruptSetModule (lModuleNo : LongInt; hWnd : HWND; uMessage : DWord; pProc : AXT_INTERRUPT_PROC; pEvent : PDWord) : DWord; stdcall;

// 지정한 모듈의 인터럽트 사용 유무 설정
    //======================================================//
    // uUse       : DISABLE(0)    // 인터럽트 해제
    //            : ENABLE(1)     // 인터럽트 설정
    //======================================================//
function AxdiInterruptSetModuleEnable (lModuleNo : LongInt; uUse : DWord) : DWord; stdcall;

// 지정한 모듈의 인터럽트 사용 유무 확인
    //======================================================//
    // *upUse    : DISABLE(0)    // 인터럽트 해제
    //           : ENABLE(1)     // 인터럽트 설정
    //======================================================//
function AxdiInterruptGetModuleEnable (lModuleNo : LongInt; upUse : PDWord) : DWord; stdcall;

// 인터럽트 발생 위치 확인
function AxdiInterruptRead (lpModuleNo : PLongInt; upFlag : PDWord) : DWord; stdcall;

//========== 인터럽트 상승 / 하강 에지 설정 확인 =================================================================================
// 지정한 입력 접점 모듈, Interrupt Rising / Falling Edge register의 Offset 위치에서 bit 단위로 상승 또는 하강 에지 값을 설정
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // uMode        : DOWN_EDGE(0)
    //              : UP_EDGE(1)
    // uValue       : DISABLE(0)
    //              : ENABLE(1)
    //===============================================================================================//
function AxdiInterruptEdgeSetBit (lModuleNo : LongInt; lOffset : LongInt; uMode : DWord; uValue : DWord) : DWord; stdcall;

// 지정한 입력 접점 모듈, Interrupt Rising / Falling Edge register의 Offset 위치에서 byte 단위로 상승 또는 하강 에지 값을 설정
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // uMode        : DOWN_EDGE(0)
    //              : UP_EDGE(1)
    // uValue       : 0x00 ~ 0x0FF ('1'로 Setting 된 부분 인터럽트 설정)
    //===============================================================================================//
function AxdiInterruptEdgeSetByte (lModuleNo : LongInt; lOffset : LongInt; uMode : DWord; uValue : DWord) : DWord; stdcall;

// 지정한 입력 접점 모듈, Interrupt Rising / Falling Edge register의 Offset 위치에서 word 단위로 상승 또는 하강 에지 값을 설정
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // uMode        : DOWN_EDGE(0)
    //              : UP_EDGE(1)
    // uValue       : 0x00 ~ 0x0FFFF ('1'로 Setting 된 부분 인터럽트 설정)
    //===============================================================================================//
function AxdiInterruptEdgeSetWord (lModuleNo : LongInt; lOffset : LongInt; uMode : DWord; uValue : DWord) : DWord; stdcall;

// 지정한 입력 접점 모듈, Interrupt Rising / Falling Edge register의 Offset 위치에서 double word 단위로 상승 또는 하강 에지 값을 설정
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // uMode        : DOWN_EDGE(0)
    //              : UP_EDGE(1)
    // uValue       : 0x00 ~ 0x0FFFFFFFF ('1'로 Setting 된 부분 인터럽트 설정)
    //===============================================================================================//
function AxdiInterruptEdgeSetDword (lModuleNo : LongInt; lOffset : LongInt; uMode : DWord; uValue : DWord) : DWord; stdcall;

// 지정한 입력 접점 모듈, Interrupt Rising / Falling Edge register의 Offset 위치에서 bit 단위로 상승 또는 하강 에지 값을 확인
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // uMode        : DOWN_EDGE(0)
    //              : UP_EDGE(1)
    // *upValue     : 0x00 ~ 0x0FF ('1'로 Setting 된 부분 인터럽트 설정)
    //===============================================================================================//
function AxdiInterruptEdgeGetBit (lModuleNo : LongInt; lOffset : LongInt; uMode : DWord; upValue : PDWord) : DWord; stdcall;

// 지정한 입력 접점 모듈, Interrupt Rising / Falling Edge register의 Offset 위치에서 byte 단위로 상승 또는 하강 에지 값을 확인
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // uMode        : DOWN_EDGE(0)
    //              : UP_EDGE(1)
    // *upValue     : 0x00 ~ 0x0FF ('1'로 Setting 된 부분 인터럽트 설정)
    //===============================================================================================//
function AxdiInterruptEdgeGetByte (lModuleNo : LongInt; lOffset : LongInt; uMode : DWord; upValue : PDWord) : DWord; stdcall;

// 지정한 입력 접점 모듈, Interrupt Rising / Falling Edge register의 Offset 위치에서 word 단위로 상승 또는 하강 에지 값을 확인
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // uMode        : DOWN_EDGE(0)
    //              : UP_EDGE(1)
    // *upValue     : 0x00 ~ 0x0FFFFFFFF ('1'로 Setting 된 부분 인터럽트 설정)
    //===============================================================================================//
function AxdiInterruptEdgeGetWord (lModuleNo : LongInt; lOffset : LongInt; uMode : DWord; upValue : PDWord) : DWord; stdcall;

// 지정한 입력 접점 모듈, Interrupt Rising / Falling Edge register의 Offset 위치에서 double word 단위로 상승 또는 하강 에지 값을 확인
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // uMode        : DOWN_EDGE(0)
    //              : UP_EDGE(1)
    // *upValue     : 0x00 ~ 0x0FFFFFFFF ('1'로 Setting 된 부분 인터럽트 설정)
    //===============================================================================================//
function AxdiInterruptEdgeGetDword (lModuleNo : LongInt; lOffset : LongInt; uMode : DWord; upValue : PDWord) : DWord; stdcall;

// 전체 입력 접점 모듈, Interrupt Rising / Falling Edge register의 Offset 위치에서 bit 단위로 상승 또는 하강 에지 값을 설정
    //===============================================================================================//
    // lOffset      : 입력 접점에 대한 Offset 위치
    // uMode        : DOWN_EDGE(0)
    //              : UP_EDGE(1)
    // uValue       : DISABLE(0)
    //              : ENABLE(1)
    //===============================================================================================//
function AxdiInterruptEdgeSet (lOffset : LongInt; uMode : DWord; uValue : DWord) : DWord; stdcall;

// 전체 입력 접점 모듈, Interrupt Rising / Falling Edge register의 Offset 위정에서 bit 단위로 상승 또는 하강 에지 값을 확인
    //===============================================================================================//
    // lOffset      : 입력 접점에 대한 Offset 위치
    // uMode        : DOWN_EDGE(0)
    //              : UP_EDGE(1)
    // *upValue     : DISABLE(0)
    //              : ENABLE(1)
    //===============================================================================================//
function AxdiInterruptEdgeGet (lOffset : LongInt; uMode : DWord; upValue : PDWord) : DWord; stdcall;

//========== 입출력 레벨 설정 확인 =================================================================================
//==입력 레벨 설정 확인
// 지정한 입력 접점 모듈의 Offset 위치에서 bit 단위로 데이터 레벨을 설정
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // uLevel       : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
function AxdiLevelSetInportBit (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;

// 지정한 입력 접점 모듈의 Offset 위치에서 byte 단위로 데이터 레벨을 설정
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // uLevel       : 0x00 ~ 0x0FF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    //===============================================================================================//
function AxdiLevelSetInportByte (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;

// 지정한 입력 접점 모듈의 Offset 위치에서 word 단위로 데이터 레벨을 설정
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // uLevel       : 0x00 ~ 0x0FFFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    //===============================================================================================//
function AxdiLevelSetInportWord (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;

// 지정한 입력 접점 모듈의 Offset 위치에서 double word 단위로 데이터 레벨을 설정
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // uLevel       : 0x00 ~ 0x0FFFFFFFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    //===============================================================================================//
function AxdiLevelSetInportDword (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;

// 지정한 입력 접점 모듈의 Offset 위치에서 bit 단위로 데이터 레벨을 확인
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // *upLevel     : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
function AxdiLevelGetInportBit (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;

// 지정한 입력 접점 모듈의 Offset 위치에서 byte 단위로 데이터 레벨을 확인
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // *upLevel     : 0x00 ~ 0x0FF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    //===============================================================================================//
function AxdiLevelGetInportByte (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;

// 지정한 입력 접점 모듈의 Offset 위치에서 word 단위로 데이터 레벨을 확인
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // *upLevel     : 0x00 ~ 0x0FFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    //===============================================================================================//
function AxdiLevelGetInportWord (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;

// 지정한 입력 접점 모듈의 Offset 위치에서 double word 단위로 데이터 레벨을 확인
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // *upLevel     : 0x00 ~ 0x0FFFFFFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    //===============================================================================================//
function AxdiLevelGetInportDword (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;

// 전체 입력 접점 모듈의 Offset 위치에서 bit 단위로 데이터 레벨을 설정
    //===============================================================================================//
    // lOffset      : 입력 접점에 대한 Offset 위치
    // uLevel       : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
function AxdiLevelSetInport (lOffset : LongInt; uLevel : DWord) : DWord; stdcall;

// 전체 입력 접점 모듈의 Offset 위치에서 bit 단위로 데이터 레벨을 확인
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // *upLevel     : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
function AxdiLevelGetInport (lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;

//==출력 레벨 설정 확인
// 지정한 출력 접점 모듈의 Offset 위치에서 bit 단위로 데이터 레벨을 설정
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 출력 접점에 대한 Offset 위치
    // uLevel       : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
function AxdoLevelSetOutportBit (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;

// 지정한 출력 접점 모듈의 Offset 위치에서 byte 단위로 데이터 레벨을 설정
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 출력 접점에 대한 Offset 위치
    // uLevel       : 0x00 ~ 0x0FF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    //===============================================================================================//
function AxdoLevelSetOutportByte (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;

// 지정한 출력 접점 모듈의 Offset 위치에서 word 단위로 데이터 레벨을 설정
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 출력 접점에 대한 Offset 위치
    // uLevel       : 0x00 ~ 0x0FFFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    //===============================================================================================//
function AxdoLevelSetOutportWord (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;

// 지정한 출력 접점 모듈의 Offset 위치에서 double word 단위로 데이터 레벨을 설정
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 출력 접점에 대한 Offset 위치
    // uLevel       : 0x00 ~ 0x0FFFFFFFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    //===============================================================================================//
function AxdoLevelSetOutportDword (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;

// 지정한 출력 접점 모듈의 Offset 위치에서 bit 단위로 데이터 레벨을 확인
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 출력 접점에 대한 Offset 위치
    // *upLevel     : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
function AxdoLevelGetOutportBit (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;

// 지정한 출력 접점 모듈의 Offset 위치에서 byte 단위로 데이터 레벨을 확인
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 출력 접점에 대한 Offset 위치
    // uLevel       : 0x00 ~ 0x0FF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    //===============================================================================================//
function AxdoLevelGetOutportByte (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;

// 지정한 출력 접점 모듈의 Offset 위치에서 word 단위로 데이터 레벨을 확인
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 출력 접점에 대한 Offset 위치
    // uLevel       : 0x00 ~ 0x0FFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    //===============================================================================================//
function AxdoLevelGetOutportWord (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;

// 지정한 출력 접점 모듈의 Offset 위치에서 double word 단위로 데이터 레벨을 확인
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 출력 접점에 대한 Offset 위치
    // uLevel       : 0x00 ~ 0x0FFFFFFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    //===============================================================================================//
function AxdoLevelGetOutportDword (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;

// 전체 출력 접점 모듈의 Offset 위치에서 bit 단위로 데이터 레벨을 설정
    //===============================================================================================//
    // lOffset      : 출력 접점에 대한 Offset 위치
    // uLevel       : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
function AxdoLevelSetOutport (lOffset : LongInt; uLevel : DWord) : DWord; stdcall;

// 전체 출력 접점 모듈의 Offset 위치에서 bit 단위로 데이터 레벨을 확인
    //===============================================================================================//
    // lOffset      : 출력 접점에 대한 Offset 위치
    // *upLevel     : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
function AxdoLevelGetOutport (lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;

//========== 입출력 포트 쓰기 읽기 =================================================================================
//==출력 포트 쓰기
// 전체 출력 접점 모듈의 Offset 위치에서 bit 단위로 데이터를 출력
    //===============================================================================================//
    // lOffset      : 출력 접점에 대한 Offset 위치
    // uLevel       : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
function AxdoWriteOutport (lOffset : LongInt; uValue : DWord) : DWord; stdcall;

// 지정한 출력 접점 모듈의 Offset 위치에서 bit 단위로 데이터를 출력
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 출력 접점에 대한 Offset 위치
    // uLevel       : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
function AxdoWriteOutportBit (lModuleNo : LongInt; lOffset : LongInt; uValue : DWord) : DWord; stdcall;

// 지정한 출력 접점 모듈의 Offset 위치에서 byte 단위로 데이터를 출력
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 출력 접점에 대한 Offset 위치
    // uValue       : 0x00 ~ 0x0FF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    //===============================================================================================//
function AxdoWriteOutportByte (lModuleNo : LongInt; lOffset : LongInt; uValue : DWord) : DWord; stdcall;

// 지정한 출력 접점 모듈의 Offset 위치에서 word 단위로 데이터를 출력
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 출력 접점에 대한 Offset 위치
    // uValue       : 0x00 ~ 0x0FFFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    //===============================================================================================//
function AxdoWriteOutportWord (lModuleNo : LongInt; lOffset : LongInt; uValue : DWord) : DWord; stdcall;

// 지정한 출력 접점 모듈의 Offset 위치에서 double word 단위로 데이터를 출력
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 출력 접점에 대한 Offset 위치
    // uValue       : 0x00 ~ 0x0FFFFFFFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    //===============================================================================================//
function AxdoWriteOutportDword (lModuleNo : LongInt; lOffset : LongInt; uValue : DWord) : DWord; stdcall;

//==출력 포트 읽기
// 전체 출력 접점 모듈의 Offset 위치에서 bit 단위로 데이터를 읽기
    //===============================================================================================//
    // lOffset      : 출력 접점에 대한 Offset 위치
    // *upLevel     : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
function AxdoReadOutport (lOffset : LongInt; upValue : PDWord) : DWord; stdcall;

// 지정한 출력 접점 모듈의 Offset 위치에서 bit 단위로 데이터를 읽기
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 출력 접점에 대한 Offset 위치
    // *upLevel     : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
function AxdoReadOutportBit (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;

// 지정한 출력 접점 모듈의 Offset 위치에서 byte 단위로 데이터를 읽기
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 출력 접점에 대한 Offset 위치
    // *upValue     : 0x00 ~ 0x0FF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    //===============================================================================================//
function AxdoReadOutportByte (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;

// 지정한 출력 접점 모듈의 Offset 위치에서 word 단위로 데이터를 읽기
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 출력 접점에 대한 Offset 위치
    // *upValue     : 0x00 ~ 0x0FFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    //===============================================================================================//
function AxdoReadOutportWord (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;

// 지정한 출력 접점 모듈의 Offset 위치에서 double word 단위로 데이터를 읽기
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 출력 접점에 대한 Offset 위치
    // *upValue     : 0x00 ~ 0x0FFFFFFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    //===============================================================================================//
function AxdoReadOutportDword (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;

//==입력 포트 읽기
// 전체 입력 접점 모듈의 Offset 위치에서 bit 단위로 데이터를 읽기
    //===============================================================================================//
    // lOffset      : 입력 접점에 대한 Offset 위치
    // *upValue     : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
function AxdiReadInport (lOffset : LongInt; upValue : PDWord) : DWord; stdcall;

// 지정한 입력 접점 모듈의 Offset 위치에서 bit 단위로 데이터를 읽기
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // *upValue     : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
function AxdiReadInportBit (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;

// 지정한 입력 접점 모듈의 Offset 위치에서 byte 단위로 데이터를 읽기
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // *upValue     : 0x00 ~ 0x0FF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    //===============================================================================================//
function AxdiReadInportByte (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;

// 지정한 입력 접점 모듈의 Offset 위치에서 word 단위로 데이터를 읽기
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // *upValue     : 0x00 ~ 0x0FFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    //===============================================================================================//
function AxdiReadInportWord (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;

// 지정한 입력 접점 모듈의 Offset 위치에서 double word 단위로 데이터를 읽기
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // *upValue     : 0x00 ~ 0x0FFFFFFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    //===============================================================================================//
function AxdiReadInportDword (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;

//== MLII 용 M-Systems DIO(R7 series) 전용 함수.
// 지정한 모듈에 장착된 입력 접점용 확장 기능 모듈의 Offset 위치에서 bit 단위로 데이터를 읽기
    //===============================================================================================//
    // lModuleNo   : 모듈 번호
    // lOffset     : 입력 접점에 대한 Offset 위치(0~15)
    // *upValue    : LOW(0)
    //             : HIGH(1)
    //===============================================================================================//
function AxdReadExtInportBit (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;

// 지정한 모듈에 장착된 입력 접점용 확장 기능 모듈의 Offset 위치에서 byte 단위로 데이터를 읽기
    //===============================================================================================//
    // lModuleNo   : 모듈 번호
    // lOffset     : 입력 접점에 대한 Offset 위치(0~1)
    // *upValue    : 0x00 ~ 0x0FF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    //===============================================================================================//
function AxdReadExtInportByte (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;

// 지정한 모듈에 장착된 입력 접점용 확장 기능 모듈의 Offset 위치에서 word 단위로 데이터를 읽기
    //===============================================================================================//
    // lModuleNo   : 모듈 번호
    // lOffset     : 입력 접점에 대한 Offset 위치(0)
    // *upValue    : 0x00 ~ 0x0FFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    //===============================================================================================//
function AxdReadExtInportWord (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;

// 지정한 모듈에 장착된 입력 접점용 확장 기능 모듈의 Offset 위치에서 dword 단위로 데이터를 읽기
    //===============================================================================================//
    // lModuleNo   : 모듈 번호
    // lOffset     : 입력 접점에 대한 Offset 위치(0)
    // *upValue    : 0x00 ~ 0x00000FFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    //===============================================================================================//
function AxdReadExtInportDword (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;

// 지정한 모듈에 장착된 출력 접점용 확장 기능 모듈의 Offset 위치에서 bit 단위로 데이터를 읽기
    //===============================================================================================//
    // lModuleNo   : 모듈 번호
    // lOffset     : 출력 접점에 대한 Offset 위치(0~15)
    // *upValue    : LOW(0)
    //             : HIGH(1)
    //===============================================================================================//
function AxdReadExtOutportBit (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;

// 지정한 모듈에 장착된 출력 접점용 확장 기능 모듈의 Offset 위치에서 byte 단위로 데이터를 읽기
    //===============================================================================================//
    // lModuleNo   : 모듈 번호
    // lOffset     : 출력 접점에 대한 Offset 위치(0~1)
    // *upValue    : 0x00 ~ 0x0FF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    //===============================================================================================//
function AxdReadExtOutportByte (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;

// 지정한 모듈에 장착된 출력 접점용 확장 기능 모듈의 Offset 위치에서 word 단위로 데이터를 읽기
    //===============================================================================================//
    // lModuleNo   : 모듈 번호
    // lOffset     : 출력 접점에 대한 Offset 위치(0)
    // *upValue    : 0x00 ~ 0x0FFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    //===============================================================================================//
function AxdReadExtOutportWord (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;

// 지정한 모듈에 장착된 출력 접점용 확장 기능 모듈의 Offset 위치에서 dword 단위로 데이터를 읽기
    //===============================================================================================//
    // lModuleNo   : 모듈 번호
    // lOffset     : 출력 접점에 대한 Offset 위치(0)
    // *upValue    : 0x00 ~ 0x00000FFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    //===============================================================================================//
function AxdReadExtOutportDword (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;

// 지정한 모듈에 장착된 출력 접점용 확장 기능 모듈의 Offset 위치에서 bit 단위로 데이터 출력
    //===============================================================================================//
    // lModuleNo   : 모듈 번호
    // lOffset     : 출력 접점에 대한 Offset 위치
    // uValue      : LOW(0)
    //             : HIGH(1)
    //===============================================================================================//
function AxdWriteExtOutportBit (lModuleNo : LongInt; lOffset : LongInt; uValue : DWord) : DWord; stdcall;

// 지정한 모듈에 장착된 출력 접점용 확장 기능 모듈의 Offset 위치에서 byte 단위로 데이터 출력
    //===============================================================================================//
    // lModuleNo   : 모듈 번호
    // lOffset     : 출력 접점에 대한 Offset 위치(0~1)
    // uValue      : 0x00 ~ 0x0FF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    //===============================================================================================//
function AxdWriteExtOutportByte (lModuleNo : LongInt; lOffset : LongInt; uValue : DWord) : DWord; stdcall;

// 지정한 모듈에 장착된 출력 접점용 확장 기능 모듈의 Offset 위치에서 word 단위로 데이터 출력
    //===============================================================================================//
    // lModuleNo   : 모듈 번호
    // lOffset     : 출력 접점에 대한 Offset 위치(0)
    // uValue    : 0x00 ~ 0x0FFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    //===============================================================================================//
function AxdWriteExtOutportWord (lModuleNo : LongInt; lOffset : LongInt; uValue : DWord) : DWord; stdcall;

// 지정한 모듈에 장착된 출력 접점용 확장 기능 모듈의 Offset 위치에서 dword 단위로 데이터 출력
    //===============================================================================================//
    // lModuleNo   : 모듈 번호
    // lOffset     : 출력 접점에 대한 Offset 위치(0)
    // uValue    : 0x00 ~ 0x00000FFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    //===============================================================================================//
function AxdWriteExtOutportDword (lModuleNo : LongInt; lOffset : LongInt; uValue : DWord) : DWord; stdcall;

// 지정한 모듈에 장착된 입/출력 접점용 확장 기능 모듈의 Offset 위치에서 bit 단위로 데이터 레벨을 설정
    //===============================================================================================//
    // lModuleNo   : 모듈 번호
    // lOffset     : 입력 접점에 대한 Offset 위치(0~15)
    // uLevel      : LOW(0)
    //             : HIGH(1)
    //===============================================================================================//
function AxdLevelSetExtportBit (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;

// 지정한 모듈에 장착된 입/출력 접점용 확장 기능 모듈의 Offset 위치에서 byte 단위로 데이터 레벨을 설정
    //===============================================================================================//
    // lModuleNo   : 모듈 번호
    // lOffset     : 입력 접점에 대한 Offset 위치(0~1)
    // uLevel      : 0x00 ~ 0xFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    //===============================================================================================//
function AxdLevelSetExtportByte (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;

// 지정한 모듈에 장착된 입/출력 접점용 확장 기능 모듈의 Offset 위치에서 word 단위로 데이터 레벨을 설정
    //===============================================================================================//
    // lModuleNo   : 모듈 번호
    // lOffset     : 입력 접점에 대한 Offset 위치(0)
    // uLevel      : 0x00 ~ 0xFFFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    //===============================================================================================//
function AxdLevelSetExtportWord (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;

// 지정한 모듈에 장착된 입/출력 접점용 확장 기능 모듈의 Offset 위치에서 dword 단위로 데이터 레벨을 설정
    //===============================================================================================//
    // lModuleNo   : 모듈 번호
    // lOffset     : 입력 접점에 대한 Offset 위치(0)
    // uLevel      : 0x00 ~ 0x0000FFFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    //===============================================================================================//
function AxdLevelSetExtportDword (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;

// 지정한 모듈에 장착된 입/출력 접점용 확장 기능 모듈의 Offset 위치에서 bit 단위로 데이터 레벨 확인
    //===============================================================================================//
    // lModuleNo   : 모듈 번호
    // lOffset     : 입력 접점에 대한 Offset 위치(0~15)
    // *upLevel      : LOW(0)
    //             : HIGH(1)
    //===============================================================================================//
function AxdLevelGetExtportBit (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;                              

// 지정한 모듈에 장착된 입/출력 접점용 확장 기능 모듈의 Offset 위치에서 byte 단위로 데이터 레벨 확인
    //===============================================================================================//
    // lModuleNo   : 모듈 번호
    // lOffset     : 입력 접점에 대한 Offset 위치(0~1)
    // *upLevel      : 0x00 ~ 0xFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    //===============================================================================================//
function AxdLevelGetExtportByte (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;

// 지정한 모듈에 장착된 입/출력 접점용 확장 기능 모듈의 Offset 위치에서 word 단위로 데이터 레벨 확인
    //===============================================================================================//
    // lModuleNo   : 모듈 번호
    // lOffset     : 입력 접점에 대한 Offset 위치(0)
    // *upLevel      : 0x00 ~ 0xFFFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    //===============================================================================================//
function AxdLevelGetExtportWord (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;

// 지정한 모듈에 장착된 입/출력 접점용 확장 기능 모듈의 Offset 위치에서 dword 단위로 데이터 레벨 확인
    //===============================================================================================//
    // lModuleNo   : 모듈 번호
    // lOffset     : 입력 접점에 대한 Offset 위치(0)
    // *upLevel      : 0x00 ~ 0x0000FFFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    //===============================================================================================//
function AxdLevelGetExtportDword (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;

//========== 고급 함수 =================================================================================
// 지정한 입력 접점 모듈의 Offset 위치에서 신호가 Off에서 On으로 바뀌었는지 확인
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // *upValue     : FALSE(0)
    //              : TRUE(1)
    //===============================================================================================//
function AxdiIsPulseOn (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;

// 지정한 입력 접점 모듈의 Offset 위치에서 신호가 On에서 Off으로 바뀌었는지 확인
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // *upValue     : FALSE(0)
    //              : TRUE(1)
    //===============================================================================================//
function AxdiIsPulseOff (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;

// 지정한 입력 접점 모듈의 Offset 위치에서 신호가 count 만큼 호출될 동안 On 상태로 유지하는지 확인
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 입력 접점에 대한 Offset 위치
    // lCount       : 0 ~ 0x7FFFFFFF(2147483647)
    // *upValue     : FALSE(0)
    //              : TRUE(1)
    // lStart       : 1(최초 호출)
    //              : 0(반복 호출)
    //===============================================================================================//
function AxdiIsOn (lModuleNo : LongInt; lOffset : LongInt; lCount : LongInt; upValue : PDWord; lStart : LongInt) : DWord; stdcall;

// 지정한 입력 접점 모듈의 Offset 위치에서 신호가 count 만큼 호출될 동안 Off 상태로 유지하는지 확인
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 출력 접점에 대한 Offset 위치
    // lCount       : 0 ~ 0x7FFFFFFF(2147483647)
    // *upValue     : FALSE(0)
    //              : TRUE(1)
    // lStart       : 1(최초 호출)
    //              : 0(반복 호출)
    //===============================================================================================//
function AxdiIsOff (lModuleNo : LongInt; lOffset : LongInt; lCount : LongInt; upValue : PDWord; lStart : LongInt) : DWord; stdcall;

// 지정한 출력 접점 모듈의 Offset 위치에서 설정한 mSec동안 On을 유지하다가 Off 시킴
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 출력 접점에 대한 Offset 위치
    // lCount       : 0 ~ 0x7FFFFFFF(2147483647)
    // lmSec        : 1 ~ 30000
    //===============================================================================================//
function AxdoOutPulseOn (lModuleNo : LongInt; lOffset : LongInt; lmSec : LongInt) : DWord; stdcall;

// 지정한 출력 접점 모듈의 Offset 위치에서 설정한 mSec동안 Off를 유지하다가 On 시킴
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 출력 접점에 대한 Offset 위치
    // lCount       : 0 ~ 0x7FFFFFFF(2147483647)
    // lmSec        : 1 ~ 30000
    //===============================================================================================//
function AxdoOutPulseOff (lModuleNo : LongInt; lOffset : LongInt; lmSec : LongInt) : DWord; stdcall;

// 지정한 출력 접점 모듈의 Offset 위치에서 설정한 횟수, 설정한 간격으로 토글한 후 원래의 출력상태를 유지함
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 출력 접점에 대한 Offset 위치
    // lInitState   : Off(0)
    //              : On(1)
    // lmSecOn      : 1 ~ 30000
    // lmSecOff     : 1 ~ 30000
    // lCount       : 1 ~ 0x7FFFFFFF(2147483647)
    //              : -1 무한 토글
    //===============================================================================================//
function AxdoToggleStart (lModuleNo : LongInt; lOffset : LongInt; lInitState : LongInt; lmSecOn : LongInt; lmSecOff : LongInt; lCount : LongInt) : DWord; stdcall;

// 지정한 출력 접점 모듈의 Offset 위치에서 토글중인 출력을 설정한 신호 상태로 정지 시킴
    //===============================================================================================//
    // lModuleNo    : 모듈 번호
    // lOffset      : 출력 접점에 대한 Offset 위치
    // uOnOff       : Off(0)
    //              : On(1)
    //===============================================================================================//
function AxdoToggleStop (lModuleNo : LongInt; lOffset : LongInt; uOnOff : DWord) : DWord; stdcall;


 // 지정한 출력 모듈의 Network이 끊어 졌을 경우 출력 상태를 출력 Byte 단위로 설정한다.
    //===============================================================================================//
    // lModuleNo   : 모듈 번호
    // dwSize      : 설정 할 Byte 수(ex. RTEX-DB32 : 2, RTEX-DO32 : 4)
    // dwaSetValue : 설정 할 변수 값(Default는 Network 끊어 지기 전 상태 유지)
    //             : 0 --> Network 끊어 지기 전 상태 유지
    //             : 1 --> On
    //             : 2 --> Off
    //===============================================================================================//
function AxdoSetNetworkErrorAct(lModuleNo: LongInt; dwSize : DWord; dwaSetValue : PDWord) : DWord; stdcall;

function AxdSetContactNum(lModuleNo : LongInt; dwInputNum : DWord; dwOutputNum : DWord) : DWord; stdcall;

function AxdGetContactNum(lModuleNo : LongInt; dwpInputNum : PDWord; dwpOutputNum : PDWord) : DWord; stdcall;

implementation

const

    dll_name    = 'AXL.dll';

    function AxdInfoIsDIOModule; external dll_name name 'AxdInfoIsDIOModule';
    function AxdInfoGetModuleNo; external dll_name name 'AxdInfoGetModuleNo';
    function AxdInfoGetModuleCount; external dll_name name 'AxdInfoGetModuleCount';
    function AxdInfoGetInputCount; external dll_name name 'AxdInfoGetInputCount';
    function AxdInfoGetOutputCount; external dll_name name 'AxdInfoGetOutputCount';
    function AxdInfoGetModule; external dll_name name 'AxdInfoGetModule';
    function AxdInfoGetModuleStatus; external dll_name name 'AxdInfoGetModuleStatus';
    function AxdiInterruptSetModule; external dll_name name 'AxdiInterruptSetModule';
    function AxdiInterruptSetModuleEnable; external dll_name name 'AxdiInterruptSetModuleEnable';
    function AxdiInterruptGetModuleEnable; external dll_name name 'AxdiInterruptGetModuleEnable';
    function AxdiInterruptRead; external dll_name name 'AxdiInterruptRead';
    function AxdiInterruptEdgeSetBit; external dll_name name 'AxdiInterruptEdgeSetBit';
    function AxdiInterruptEdgeSetByte; external dll_name name 'AxdiInterruptEdgeSetByte';
    function AxdiInterruptEdgeSetWord; external dll_name name 'AxdiInterruptEdgeSetWord';
    function AxdiInterruptEdgeSetDword; external dll_name name 'AxdiInterruptEdgeSetDword';
    function AxdiInterruptEdgeGetBit; external dll_name name 'AxdiInterruptEdgeGetBit';
    function AxdiInterruptEdgeGetByte; external dll_name name 'AxdiInterruptEdgeGetByte';
    function AxdiInterruptEdgeGetWord; external dll_name name 'AxdiInterruptEdgeGetWord';
    function AxdiInterruptEdgeGetDword; external dll_name name 'AxdiInterruptEdgeGetDword';
    function AxdiInterruptEdgeSet; external dll_name name 'AxdiInterruptEdgeSet';
    function AxdiInterruptEdgeGet; external dll_name name 'AxdiInterruptEdgeGet';
    function AxdiLevelSetInportBit; external dll_name name 'AxdiLevelSetInportBit';
    function AxdiLevelSetInportByte; external dll_name name 'AxdiLevelSetInportByte';
    function AxdiLevelSetInportWord; external dll_name name 'AxdiLevelSetInportWord';
    function AxdiLevelSetInportDword; external dll_name name 'AxdiLevelSetInportDword';
    function AxdiLevelGetInportBit; external dll_name name 'AxdiLevelGetInportBit';
    function AxdiLevelGetInportByte; external dll_name name 'AxdiLevelGetInportByte';
    function AxdiLevelGetInportWord; external dll_name name 'AxdiLevelGetInportWord';
    function AxdiLevelGetInportDword; external dll_name name 'AxdiLevelGetInportDword';
    function AxdiLevelSetInport; external dll_name name 'AxdiLevelSetInport';
    function AxdiLevelGetInport; external dll_name name 'AxdiLevelGetInport';
    function AxdoLevelSetOutportBit; external dll_name name 'AxdoLevelSetOutportBit';
    function AxdoLevelSetOutportByte; external dll_name name 'AxdoLevelSetOutportByte';
    function AxdoLevelSetOutportWord; external dll_name name 'AxdoLevelSetOutportWord';
    function AxdoLevelSetOutportDword; external dll_name name 'AxdoLevelSetOutportDword';
    function AxdoLevelGetOutportBit; external dll_name name 'AxdoLevelGetOutportBit';
    function AxdoLevelGetOutportByte; external dll_name name 'AxdoLevelGetOutportByte';
    function AxdoLevelGetOutportWord; external dll_name name 'AxdoLevelGetOutportWord';
    function AxdoLevelGetOutportDword; external dll_name name 'AxdoLevelGetOutportDword';
    function AxdoLevelSetOutport; external dll_name name 'AxdoLevelSetOutport';
    function AxdoLevelGetOutport; external dll_name name 'AxdoLevelGetOutport';
    function AxdoWriteOutport; external dll_name name 'AxdoWriteOutport';
    function AxdoWriteOutportBit; external dll_name name 'AxdoWriteOutportBit';
    function AxdoWriteOutportByte; external dll_name name 'AxdoWriteOutportByte';
    function AxdoWriteOutportWord; external dll_name name 'AxdoWriteOutportWord';
    function AxdoWriteOutportDword; external dll_name name 'AxdoWriteOutportDword';
    function AxdoReadOutport; external dll_name name 'AxdoReadOutport';
    function AxdoReadOutportBit; external dll_name name 'AxdoReadOutportBit';
    function AxdoReadOutportByte; external dll_name name 'AxdoReadOutportByte';
    function AxdoReadOutportWord; external dll_name name 'AxdoReadOutportWord';
    function AxdoReadOutportDword; external dll_name name 'AxdoReadOutportDword';
    function AxdiReadInport; external dll_name name 'AxdiReadInport';
    function AxdiReadInportBit; external dll_name name 'AxdiReadInportBit';
    function AxdiReadInportByte; external dll_name name 'AxdiReadInportByte';
    function AxdiReadInportWord; external dll_name name 'AxdiReadInportWord';
    function AxdiReadInportDword; external dll_name name 'AxdiReadInportDword';
    function AxdReadExtInportBit; external dll_name name 'AxdReadExtInportBit';
    function AxdReadExtInportByte; external dll_name name 'AxdReadExtInportByte';
    function AxdReadExtInportWord; external dll_name name 'AxdReadExtInportWord';
    function AxdReadExtInportDword; external dll_name name 'AxdReadExtInportDword';
    function AxdReadExtOutportBit; external dll_name name 'AxdReadExtOutportBit';
    function AxdReadExtOutportByte; external dll_name name 'AxdReadExtOutportByte';
    function AxdReadExtOutportWord; external dll_name name 'AxdReadExtOutportWord';
    function AxdReadExtOutportDword; external dll_name name 'AxdReadExtOutportDword';
    function AxdWriteExtOutportBit; external dll_name name 'AxdWriteExtOutportBit';
    function AxdWriteExtOutportByte; external dll_name name 'AxdWriteExtOutportByte';
    function AxdWriteExtOutportWord; external dll_name name 'AxdWriteExtOutportWord';
    function AxdWriteExtOutportDword; external dll_name name 'AxdWriteExtOutportDword';
    function AxdLevelSetExtportBit; external dll_name name 'AxdLevelSetExtportBit';
    function AxdLevelSetExtportByte; external dll_name name 'AxdLevelSetExtportByte';
    function AxdLevelSetExtportWord; external dll_name name 'AxdLevelSetExtportWord';
    function AxdLevelSetExtportDword; external dll_name name 'AxdLevelSetExtportDword';
    function AxdLevelGetExtportBit; external dll_name name 'AxdLevelGetExtportBit';
    function AxdLevelGetExtportByte; external dll_name name 'AxdLevelGetExtportByte';
    function AxdLevelGetExtportWord; external dll_name name 'AxdLevelGetExtportWord';
    function AxdLevelGetExtportDword; external dll_name name 'AxdLevelGetExtportDword';    
    function AxdiIsPulseOn; external dll_name name 'AxdiIsPulseOn';
    function AxdiIsPulseOff; external dll_name name 'AxdiIsPulseOff';
    function AxdiIsOn; external dll_name name 'AxdiIsOn';
    function AxdiIsOff; external dll_name name 'AxdiIsOff';
    function AxdoOutPulseOn; external dll_name name 'AxdoOutPulseOn';
    function AxdoOutPulseOff; external dll_name name 'AxdoOutPulseOff';
    function AxdoToggleStart; external dll_name name 'AxdoToggleStart';
    function AxdoToggleStop; external dll_name name 'AxdoToggleStop';
    function AxdoSetNetworkErrorAct; external dll_name name 'AxdoSetNetworkErrorAct';
    function AxdSetContactNum; external dll_name name 'AxdSetContactNum';
    function AxdGetContactNum; external dll_name name 'AxdGetContactNum';
end.
