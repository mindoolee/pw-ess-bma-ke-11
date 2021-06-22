Option Strict Off
Option Explicit On
Module AXD
    '*****************************************************************************
    '*****************************************************************************
    '**
    '** File Name
    '** ----------
    '**
    '** AXD.BAS
    '**
    '** COPYRIGHT (c) AJINEXTEK Co., LTD
    '**
    '*****************************************************************************
    '*****************************************************************************
    '**
    '** Description
    '** -----------
    '** Ajinextek Digital Library Header File
    '** 
    '**
    '*****************************************************************************
    '*****************************************************************************
    '**
    '** Source Change Indices
    '** ---------------------
    '** 
    '** (None)
    '**
    '**
    '*****************************************************************************
    '*****************************************************************************
    '**
    '** Website
    '** ---------------------
    '**
    '** http://www.ajinextek.com
    '**
    '*****************************************************************************
    '*****************************************************************************
    '*


    '========== 보드 및 모듈 정보 =================================================================='

    ' DIO 모듈이 있는지 확인
    Public Declare Function AxdInfoIsDIOModule Lib "AXL.dll" (ByRef upStatus As Integer) As Integer

    ' DIO 모듈이 있는지 확인
    Public Declare Function AxdInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByRef lpModuleNo As Integer) As Integer

    ' DIO 입출력 모듈의 개수 확인
    Public Declare Function AxdInfoGetModuleCount Lib "AXL.dll" (ByRef lpModuleCount As Integer) As Integer

    ' 지정한 모듈의 입력 접점 개수 확인
    Public Declare Function AxdInfoGetInputCount Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpCount As Integer) As Integer

    ' 지정한 모듈의 출력 접점 개수 확인
    Public Declare Function AxdInfoGetOutputCount Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpCount As Integer) As Integer

    ' 지정한 모듈 번호로 베이스 보드 번호, 모듈 위치, 모듈 ID 확인
    Public Declare Function AxdInfoGetModule Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpBoardNo As Integer, ByRef lpModulePos As Integer, ByRef upModuleID As Integer) As Integer

    ' 해당 모듈이 제어가 가능한 상태인지 반환한다.
    Public Declare Function AxdInfoGetModuleStatus Lib "AXL.dll" (ByVal lModuleNo As Integer) As Integer

    '========== 인터럽트 설정 확인 ================================================================='
    ' 지정한 모듈에 인터럽트 메시지를 받아오기 위하여 윈도우 메시지, 콜백 함수 또는 이벤트 방식을 사용
    ' 지정한 모듈에 인터럽트 메시지를 받아오기 위하여 윈도우 메시지, 콜백 함수 또는 이벤트 방식을 사용
    '========= 인터럽트 관련 함수 =================================================================='
    ' 콜백 함수 방식은 이벤트 발생 시점에 즉시 콜백 함수가 호출 됨으로 가장 빠르게 이벤트를 통지받을 수 있는 장점이 있으나
    ' 콜백 함수가 완전히 종료 될 때까지 메인 프로세스가 정체되어 있게 된다.
    ' 즉, 콜백 함수 내에 부하가 걸리는 작업이 있을 경우에는 사용에 주의를 요한다. 
    ' 이벤트 방식은 쓰레드등을 이용하여 인터럽트 발생여부를 지속적으로 감시하고 있다가 인터럽트가 발생하면 
    ' 처리해주는 방법으로, 쓰레드 등으로 인해 시스템 자원을 점유하고 있는 단점이 있지만
    ' 가장 빠르게 인터럽트를 검출하고 처리해줄 수 있는 장점이 있다.
    ' 일반적으로는 많이 쓰이지 않지만, 인터럽트의 빠른처리가 주요 관심사인 경우에 사용된다. 
    ' 이벤트 방식은 이벤트의 발생 여부를 감시하는 특정 쓰레드를 사용하여 메인 프로세스와 별개로 동작되므로
    ' MultiProcessor 시스템등에서 자원을 가장 효율적으로 사용할 수 있게 되어 특히 권장하는 방식이다.
    ' 인터럽트 메시지를 받아오기 위하여 윈도우 메시지 또는 콜백 함수를 사용한다.
    ' (메시지 핸들, 메시지 ID, 콜백함수, 인터럽트 이벤트)
    '    hWnd    : 윈도우 핸들, 윈도우 메세지를 받을때 사용. 사용하지 않으면 NULL을 입력.
    '    uMessage: 윈도우 핸들의 메세지, 사용하지 않거나 디폴트값을 사용하려면 0을 입력.
    '    proc    : 인터럽트 발생시 호출될 함수의 포인터, 사용하지 않으면 NULL을 입력.
    '    pEvent  : 이벤트 방법사용시 이벤트 핸들
    Public Declare Function AxdiInterruptSetModule Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal hWnd As Integer, ByVal uMessage As Integer, ByVal pProc As Integer, ByRef pEvent As Integer) As Integer

    ' 지정한 모듈의 인터럽트 사용 유무 설정
    '======================================================'
    ' uUse       : DISABLE(0)    ' 인터럽트 해제
    '            : ENABLE(1)     ' 인터럽트 설정
    '======================================================'
    Public Declare Function AxdiInterruptSetModuleEnable Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal uUse As Integer) As Integer

    ' 지정한 모듈의 인터럽트 사용 유무 확인
    ' ======================================================' 
    '  *upUse    : DISABLE(0)    '  인터럽트 해제
    '            : ENABLE(1)     '  인터럽트 설정
    ' ======================================================' 
    Public Declare Function AxdiInterruptGetModuleEnable Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef upUse As Integer) As Integer

    ' 인터럽트 발생 위치 확인
    Public Declare Function AxdiInterruptRead Lib "AXL.dll" (ByRef lpModuleNo As Integer, ByRef upFlag As Integer) As Integer

    '========== 인터럽트 상승 / 하강 에지 설정 확인 ================================================'
    ' 지정한 입력 접점 모듈, Interrupt Rising / Falling Edge register의 Offset 위치에서 bit 단위로 상승 또는 하강 에지 값을 설정
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' uValue     : DISABLE(0)
    '            : ENABLE(1)
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeSetBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByVal uValue As Integer) As Integer

    ' 지정한 입력 접점 모듈, Interrupt Rising / Falling Edge register의 Offset 위치에서 byte 단위로 상승 또는 하강 에지 값을 설정
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' uValue     : 0x00 ~ 0x0FF ('1'로 Setting 된 부분 인터럽트 설정)
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeSetByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByVal uValue As Integer) As Integer

    ' 지정한 입력 접점 모듈, Interrupt Rising / Falling Edge register의 Offset 위치에서 word 단위로 상승 또는 하강 에지 값을 설정
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' uValue     : 0x00 ~ 0x0FFFF ('1'로 Setting 된 부분 인터럽트 설정)
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeSetWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByVal uValue As Integer) As Integer

    ' 지정한 입력 접점 모듈, Interrupt Rising / Falling Edge register의 Offset 위치에서 double word 단위로 상승 또는 하강 에지 값을 설정
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' uValue     : 0x00 ~ 0x0FFFFFFFF ('1'로 Setting 된 부분 인터럽트 설정)
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeSetDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByVal uValue As Integer) As Integer

    ' 지정한 입력 접점 모듈, Interrupt Rising / Falling Edge register의 Offset 위치에서 bit 단위로 상승 또는 하강 에지 값을 확인
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' *upValue   : 0x00 ~ 0x0FF ('1'로 Setting 된 부분 인터럽트 설정)
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeGetBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByRef upValue As Integer) As Integer

    ' 지정한 입력 접점 모듈, Interrupt Rising / Falling Edge register의 Offset 위치에서 byte 단위로 상승 또는 하강 에지 값을 확인
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' *upValue   : 0x00 ~ 0x0FF ('1'로 Setting 된 부분 인터럽트 설정)
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeGetByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByRef upValue As Integer) As Integer

    ' 지정한 입력 접점 모듈, Interrupt Rising / Falling Edge register의 Offset 위치에서 word 단위로 상승 또는 하강 에지 값을 확인
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' *upValue   : 0x00 ~ 0x0FFFFFFFF ('1'로 Setting 된 부분 인터럽트 설정)
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeGetWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByRef upValue As Integer) As Integer

    ' 지정한 입력 접점 모듈, Interrupt Rising / Falling Edge register의 Offset 위치에서 double word 단위로 상승 또는 하강 에지 값을 확인
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' *upValue   : 0x00 ~ 0x0FFFFFFFF ('1'로 Setting 된 부분 인터럽트 설정)
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeGetDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByRef upValue As Integer) As Integer

    ' 전체 입력 접점 모듈, Interrupt Rising / Falling Edge register의 Offset 위치에서 bit 단위로 상승 또는 하강 에지 값을 설정
    '==============================================================================================='
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' uValue     : DISABLE(0)
    '            : ENABLE(1)
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeSet Lib "AXL.dll" (ByVal lOffset As Integer, ByVal uMode As Integer, ByVal uValue As Integer) As Integer

    ' 전체 입력 접점 모듈, Interrupt Rising / Falling Edge register의 Offset 위정에서 bit 단위로 상승 또는 하강 에지 값을 확인
    '==============================================================================================='
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' *upValue   : DISABLE(0)
    '            : ENABLE(1)
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeGet Lib "AXL.dll" (ByVal lOffset As Integer, ByVal uMode As Integer, ByRef upValue As Integer) As Integer

    '========== 입출력 레벨 설정 확인 =================================================================================

    ' 지정한 입, 출력 접점 모듈의 Offset 위치에서 bit 단위로 데이터 레벨을 설정
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' uLevel     : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdiLevelSetInportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' 지정한 입, 출력 접점 모듈의 Offset 위치에서 byte 단위로 데이터 레벨을 설정
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' uLevel     : 0x00 ~ 0x0FF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdiLevelSetInportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' 지정한 입, 출력 접점 모듈의 Offset 위치에서 word 단위로 데이터 레벨을 설정
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' uLevel     : 0x00 ~ 0x0FFFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdiLevelSetInportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' 지정한 입, 출력 접점 모듈의 Offset 위치에서 double word 단위로 데이터 레벨을 설정
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' uLevel     : 0x00 ~ 0x0FFFFFFFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdiLevelSetInportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' 지정한 입, 출력 접점 모듈의 Offset 위치에서 bit 단위로 데이터 레벨을 확인
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' *upLevel   : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdiLevelGetInportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer

    ' 지정한 입, 출력 접점 모듈의 Offset 위치에서 byte 단위로 데이터 레벨을 확인
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' *upLevel   : 0x00 ~ 0x0FF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdiLevelGetInportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer

    ' 지정한 입, 출력 접점 모듈의 Offset 위치에서 word 단위로 데이터 레벨을 확인
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' *upLevel   : 0x00 ~ 0x0FFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdiLevelGetInportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer

    ' 지정한 입, 출력 접점 모듈의 Offset 위치에서 double word 단위로 데이터 레벨을 확인
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' *upLevel   : 0x00 ~ 0x0FFFFFFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdiLevelGetInportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer

    ' 전체 입, 출력 접점 모듈의 Offset 위치에서 bit 단위로 데이터 레벨을 설정
    '==============================================================================================='
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' uLevel     : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdiLevelSetInport Lib "AXL.dll" (ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' 전체 입, 출력 접점 모듈의 Offset 위치에서 bit 단위로 데이터 레벨을 확인
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' *upLevel   : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdiLevelGetInport Lib "AXL.dll" (ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer

    ' 지정한 입, 출력 접점 모듈의 Offset 위치에서 bit 단위로 데이터 레벨을 설정
    ' 지정한 출력 접점 모듈의 Offset 위치에서 bit 단위로 데이터 레벨을 설정
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' uLevel     : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoLevelSetOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' 지정한 입, 출력 접점 모듈의 Offset 위치에서 byte 단위로 데이터 레벨을 설정
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' uLevel     : 0x00 ~ 0x0FF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdoLevelSetOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' 지정한 입, 출력 접점 모듈의 Offset 위치에서 word 단위로 데이터 레벨을 설정
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' uLevel     : 0x00 ~ 0x0FFFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdoLevelSetOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' 지정한 입, 출력 접점 모듈의 Offset 위치에서 double word 단위로 데이터 레벨을 설정
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' uLevel     : 0x00 ~ 0x0FFFFFFFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdoLevelSetOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' 지정한 입, 출력 접점 모듈의 Offset 위치에서 bit 단위로 데이터 레벨을 확인
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' *upLevel   : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoLevelGetOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer

    ' 지정한 입, 출력 접점 모듈의 Offset 위치에서 byte 단위로 데이터 레벨을 확인
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' uLevel     : 0x00 ~ 0x0FF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdoLevelGetOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer

    ' 지정한 입, 출력 접점 모듈의 Offset 위치에서 word 단위로 데이터 레벨을 확인
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' uLevel     : 0x00 ~ 0x0FFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdoLevelGetOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer

    ' 지정한 입, 출력 접점 모듈의 Offset 위치에서 double word 단위로 데이터 레벨을 확인
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' uLevel     : 0x00 ~ 0x0FFFFFFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdoLevelGetOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer

    ' 전체 입, 출력 접점 모듈의 Offset 위치에서 bit 단위로 데이터 레벨을 설정
    '==============================================================================================='
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' uLevel     : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoLevelSetOutport Lib "AXL.dll" (ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' 전체 입, 출력 접점 모듈의 Offset 위치에서 bit 단위로 데이터 레벨을 확인
    '==============================================================================================='
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' *upLevel   : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoLevelGetOutport Lib "AXL.dll" (ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer
    '========== 입출력 포트 쓰기 읽기 =================================================================================

    ' 전체 출력 접점 모듈의 Offset 위치에서 bit 단위로 데이터를 출력
    '==============================================================================================='
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' uLevel     : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoWriteOutport Lib "AXL.dll" (ByVal lOffset As Integer, ByVal uValue As Integer) As Integer

    ' 지정한 출력 접점 모듈의 Offset 위치에서 bit 단위로 데이터를 출력
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' uLevel     : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoWriteOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer

    ' 지정한 출력 접점 모듈의 Offset 위치에서 byte 단위로 데이터를 출력
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' uValue     : 0x00 ~ 0x0FF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdoWriteOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer

    ' 지정한 출력 접점 모듈의 Offset 위치에서 word 단위로 데이터를 출력
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' uValue     : 0x00 ~ 0x0FFFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdoWriteOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer

    ' 지정한 출력 접점 모듈의 Offset 위치에서 double word 단위로 데이터를 출력
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' uValue     : 0x00 ~ 0x0FFFFFFFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdoWriteOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer

    ' 전체 출력 접점 모듈의 Offset 위치에서 bit 단위로 데이터를 읽기
    '==============================================================================================='
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' *upLevel   : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoReadOutport Lib "AXL.dll" (ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' 지정한 출력 접점 모듈의 Offset 위치에서 bit 단위로 데이터를 읽기
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' *upLevel   : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoReadOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' 지정한 출력 접점 모듈의 Offset 위치에서 byte 단위로 데이터를 읽기
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' *upValue   : 0x00 ~ 0x0FF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdoReadOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' 지정한 출력 접점 모듈의 Offset 위치에서 word 단위로 데이터를 읽기
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' *upValue   : 0x00 ~ 0x0FFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdoReadOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' 지정한 출력 접점 모듈의 Offset 위치에서 double word 단위로 데이터를 읽기
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' *upValue   : 0x00 ~ 0x0FFFFFFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdoReadOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' 전체 입력 접점 모듈의 Offset 위치에서 bit 단위로 데이터를 읽기
    '==============================================================================================='
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' *upValue   : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdiReadInport Lib "AXL.dll" (ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' 지정한 입력 접점 모듈의 Offset 위치에서 bit 단위로 데이터를 읽기
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' *upValue   : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdiReadInportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' 지정한 입력 접점 모듈의 Offset 위치에서 byte 단위로 데이터를 읽기
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' *upValue   : 0x00 ~ 0x0FF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdiReadInportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' 지정한 입력 접점 모듈의 Offset 위치에서 word 단위로 데이터를 읽기
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' *upValue   : 0x00 ~ 0x0FFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdiReadInportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' 지정한 입력 접점 모듈의 Offset 위치에서 double word 단위로 데이터를 읽기
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' *upValue   : 0x00 ~ 0x0FFFFFFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdiReadInportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    '== MLII 용 M-Systems DIO(R7 series) 전용 함수.
    ' 지정한 모듈에 장착된 입력 접점용 확장 기능 모듈의 Offset 위치에서 bit 단위로 데이터를 읽기
    '==============================================================================================='
    ' lModuleNo   : 모듈 번호
    ' lOffset     : 입력 접점에 대한 Offset 위치(0~15)
    ' *upValue    : LOW(0)
    '             : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdReadExtInportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' 지정한 모듈에 장착된 입력 접점용 확장 기능 모듈의 Offset 위치에서 byte 단위로 데이터를 읽기
    '==============================================================================================='
    ' lModuleNo   : 모듈 번호
    ' lOffset     : 입력 접점에 대한 Offset 위치(0~1)
    ' *upValue    : 0x00 ~ 0x0FF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdReadExtInportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' 지정한 모듈에 장착된 입력 접점용 확장 기능 모듈의 Offset 위치에서 word 단위로 데이터를 읽기
    '==============================================================================================='
    ' lModuleNo   : 모듈 번호
    ' lOffset     : 입력 접점에 대한 Offset 위치(0)
    ' *upValue    : 0x00 ~ 0x0FFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdReadExtInportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' 지정한 모듈에 장착된 입력 접점용 확장 기능 모듈의 Offset 위치에서 dword 단위로 데이터를 읽기
    '==============================================================================================='
    ' lModuleNo   : 모듈 번호
    ' lOffset     : 입력 접점에 대한 Offset 위치(0)
    ' *upValue    : 0x00 ~ 0x00000FFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdReadExtInportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' 지정한 모듈에 장착된 출력 접점용 확장 기능 모듈의 Offset 위치에서 bit 단위로 데이터를 읽기
    '==============================================================================================='
    ' lModuleNo   : 모듈 번호
    ' lOffset     : 출력 접점에 대한 Offset 위치(0~15)
    ' *upValue    : LOW(0)
    '             : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdReadExtOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' 지정한 모듈에 장착된 출력 접점용 확장 기능 모듈의 Offset 위치에서 byte 단위로 데이터를 읽기
    '==============================================================================================='
    ' lModuleNo   : 모듈 번호
    ' lOffset     : 출력 접점에 대한 Offset 위치(0~1)
    ' *upValue    : 0x00 ~ 0x0FF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdReadExtOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' 지정한 모듈에 장착된 출력 접점용 확장 기능 모듈의 Offset 위치에서 word 단위로 데이터를 읽기
    '==============================================================================================='
    ' lModuleNo   : 모듈 번호
    ' lOffset     : 출력 접점에 대한 Offset 위치(0)
    ' *upValue    : 0x00 ~ 0x0FFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdReadExtOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' 지정한 모듈에 장착된 출력 접점용 확장 기능 모듈의 Offset 위치에서 dword 단위로 데이터를 읽기
    '==============================================================================================='
    ' lModuleNo   : 모듈 번호
    ' lOffset     : 출력 접점에 대한 Offset 위치(0)
    ' *upValue    : 0x00 ~ 0x00000FFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdReadExtOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' 지정한 모듈에 장착된 출력 접점용 확장 기능 모듈의 Offset 위치에서 bit 단위로 데이터 출력
    '==============================================================================================='
    ' lModuleNo   : 모듈 번호
    ' lOffset     : 출력 접점에 대한 Offset 위치
    ' uValue      : LOW(0)
    '             : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdWriteExtOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer

    ' 지정한 모듈에 장착된 출력 접점용 확장 기능 모듈의 Offset 위치에서 byte 단위로 데이터 출력
    '==============================================================================================='
    ' lModuleNo   : 모듈 번호
    ' lOffset     : 출력 접점에 대한 Offset 위치(0~1)
    ' uValue      : 0x00 ~ 0x0FF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdWriteExtOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer

    ' 지정한 모듈에 장착된 출력 접점용 확장 기능 모듈의 Offset 위치에서 word 단위로 데이터 출력
    '==============================================================================================='
    ' lModuleNo   : 모듈 번호
    ' lOffset     : 출력 접점에 대한 Offset 위치(0)
    ' uValue    : 0x00 ~ 0x0FFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdWriteExtOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer

    ' 지정한 모듈에 장착된 출력 접점용 확장 기능 모듈의 Offset 위치에서 dword 단위로 데이터 출력
    '==============================================================================================='
    ' lModuleNo   : 모듈 번호
    ' lOffset     : 출력 접점에 대한 Offset 위치(0)
    ' uValue    : 0x00 ~ 0x00000FFFF('1'로 읽힌 비트는 HIGH, '0'으로 읽힌 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdWriteExtOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer

    ' 지정한 모듈에 장착된 입/출력 접점용 확장 기능 모듈의 Offset 위치에서 bit 단위로 데이터 레벨을 설정
    '==============================================================================================='
    ' lModuleNo   : 모듈 번호
    ' lOffset     : 입력 접점에 대한 Offset 위치(0~15)
    ' uLevel      : LOW(0)
    '             : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdLevelSetExtportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' 지정한 모듈에 장착된 입/출력 접점용 확장 기능 모듈의 Offset 위치에서 byte 단위로 데이터 레벨을 설정
    '==============================================================================================='
    ' lModuleNo   : 모듈 번호
    ' lOffset     : 입력 접점에 대한 Offset 위치(0~1)
    ' uLevel      : 0x00 ~ 0xFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdLevelSetExtportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' 지정한 모듈에 장착된 입/출력 접점용 확장 기능 모듈의 Offset 위치에서 word 단위로 데이터 레벨을 설정
    '==============================================================================================='
    ' lModuleNo   : 모듈 번호
    ' lOffset     : 입력 접점에 대한 Offset 위치(0)
    ' uLevel      : 0x00 ~ 0xFFFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdLevelSetExtportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' 지정한 모듈에 장착된 입/출력 접점용 확장 기능 모듈의 Offset 위치에서 dword 단위로 데이터 레벨을 설정
    '==============================================================================================='
    ' lModuleNo   : 모듈 번호
    ' lOffset     : 입력 접점에 대한 Offset 위치(0)
    ' uLevel      : 0x00 ~ 0x0000FFFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdLevelSetExtportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' 지정한 모듈에 장착된 입/출력 접점용 확장 기능 모듈의 Offset 위치에서 bit 단위로 데이터 레벨 확인
    '==============================================================================================='
    ' lModuleNo   : 모듈 번호
    ' lOffset     : 입력 접점에 대한 Offset 위치(0~15)
    ' *upLevel      : LOW(0)
    '             : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdLevelGetExtportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal upLevel As Integer) As Integer

    ' 지정한 모듈에 장착된 입/출력 접점용 확장 기능 모듈의 Offset 위치에서 byte 단위로 데이터 레벨 확인
    '==============================================================================================='
    ' lModuleNo   : 모듈 번호
    ' lOffset     : 입력 접점에 대한 Offset 위치(0~1)
    ' *upLevel      : 0x00 ~ 0xFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdLevelGetExtportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal upLevel As Integer) As Integer

    ' 지정한 모듈에 장착된 입/출력 접점용 확장 기능 모듈의 Offset 위치에서 word 단위로 데이터 레벨 확인
    '==============================================================================================='
    ' lModuleNo   : 모듈 번호
    ' lOffset     : 입력 접점에 대한 Offset 위치(0)
    ' *upLevel      : 0x00 ~ 0xFFFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdLevelGetExtportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal upLevel As Integer) As Integer

    ' 지정한 모듈에 장착된 입/출력 접점용 확장 기능 모듈의 Offset 위치에서 dword 단위로 데이터 레벨 확인
    '==============================================================================================='
    ' lModuleNo   : 모듈 번호
    ' lOffset     : 입력 접점에 대한 Offset 위치(0)
    ' *upLevel      : 0x00 ~ 0x0000FFFF('1'로 설정 된 비트는 HIGH, '0'으로 설정 된 비트는 LOW)
    '==============================================================================================='
    Public Declare Function AxdLevelGetExtportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal upLevel As Integer) As Integer

    '========== 고급 함수 =================================================================================
    ' 지정한 입력 접점 모듈의 Offset 위치에서 신호가 Off에서 On으로 바뀌었는지 확인
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' *upValue   : FALSE(0)
    '            : TRUE(1)
    '==============================================================================================='
    Public Declare Function AxdiIsPulseOn Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' 지정한 입력 접점 모듈의 Offset 위치에서 신호가 On에서 Off으로 바뀌었는지 확인
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' *upValue   : FALSE(0)
    '            : TRUE(1)
    '==============================================================================================='
    Public Declare Function AxdiIsPulseOff Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' 지정한 입력 접점 모듈의 Offset 위치에서 신호가 count 만큼 호출될 동안 On 상태로 유지하는지 확인
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 입력 접점에 대한 Offset 위치
    ' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
    ' *upValue   : FALSE(0)
    '            : TRUE(1)
    ' lStart     : 1(최초 호출)
    '            : 0(반복 호출)
    '==============================================================================================='
    Public Declare Function AxdiIsOn Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal lCount As Integer, ByRef upValue As Integer, ByVal lStart As Integer) As Integer

    ' 지정한 입력 접점 모듈의 Offset 위치에서 신호가 count 만큼 호출될 동안 Off 상태로 유지하는지 확인
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
    ' *upValue   : FALSE(0)
    '            : TRUE(1)
    ' lStart     : 1(최초 호출)
    '            : 0(반복 호출)
    '==============================================================================================='
    Public Declare Function AxdiIsOff Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal lCount As Integer, ByRef upValue As Integer, ByVal lStart As Integer) As Integer

    ' 지정한 출력 접점 모듈의 Offset 위치에서 설정한 mSec동안 On을 유지하다가 Off 시킴
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
    ' lmSec      : 1 ~ 30000
    '==============================================================================================='
    Public Declare Function AxdoOutPulseOn Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal lmSec As Integer) As Integer

    ' 지정한 출력 접점 모듈의 Offset 위치에서 설정한 mSec동안 Off를 유지하다가 On 시킴
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
    ' lmSec      : 1 ~ 30000
    '==============================================================================================='
    Public Declare Function AxdoOutPulseOff Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal lmSec As Integer) As Integer

    ' 지정한 출력 접점 모듈의 Offset 위치에서 설정한 횟수, 설정한 간격으로 토글한 후 원래의 출력상태를 유지함
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' lInitState: Off(0)
    '            : On(1)
    ' lmSecOn    : 1 ~ 30000
    ' lmSecOff   : 1 ~ 30000
    ' lCount     : 1 ~ 0x7FFFFFFF(2147483647)
    '            : -1 무한 토글
    '==============================================================================================='
    Public Declare Function AxdoToggleStart Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal lInitState As Integer, ByVal lmSecOn As Integer, ByVal lmSecOff As Integer, ByVal lCount As Integer) As Integer

    ' 지정한 출력 접점 모듈의 Offset 위치에서 토글중인 출력을 설정한 신호 상태로 정지 시킴
    '==============================================================================================='
    ' lModuleNo  : 모듈 번호
    ' lOffset    : 출력 접점에 대한 Offset 위치
    ' uOnOff     : Off(0)
    '            : On(1)
    '==============================================================================================='
    Public Declare Function AxdoToggleStop Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uOnOff As Integer) As Integer

    ' 지정한 출력 모듈의 Network이 끊어 졌을 경우 출력 상태를 출력 Byte 단위로 설정한다.
    '==============================================================================================='
    ' lModuleNo   : 모듈 번호
    ' dwSize      : 설정 할 Byte 수(ex. RTEX-DB32 : 2, RTEX-DO32 : 4)
    ' dwaSetValue : 설정 할 변수 값(Default는 Network 끊어 지기 전 상태 유지)
    '             : 0 --> Network 끊어 지기 전 상태 유지
    '             : 1 --> On
    '             : 2 --> Off
    '==============================================================================================='
    Public Declare Function AxdoSetNetworkErrorAct Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dwSize As Integer, ByRef dwaSetValue As Integer) As Integer

    Public Declare Function AxdSetContactNum Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dwInputNum As Integer, ByVal dwOutputNum As Integer) As Integer

    Public Declare Function AxdGetContactNum Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef dwpInputNum As Integer, ByRef dwpOutputNum As Integer) As Integer

End Module
