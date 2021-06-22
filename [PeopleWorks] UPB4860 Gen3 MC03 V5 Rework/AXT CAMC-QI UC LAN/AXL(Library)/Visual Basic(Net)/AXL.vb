Option Strict Off
Option Explicit On
Module AXL
    '****************************************************************************
    '*****************************************************************************
    '**
    '** File Name
    '** ----------
    '**
    '** AXL.BAS
    '**
    '** COPYRIGHT (c) AJINEXTEK Co., LTD
    '**
    '*****************************************************************************
    '*****************************************************************************
    '**
    '** Description
    '** -----------
    '** Ajinextek Library Header File
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


    '========== 라이브러리 초기화 =========================================================================

    ' 라이브러리 초기화
    Public Declare Function AxlOpen Lib "AXL.dll" (ByVal lIrqNo As Integer) As Integer
    ' 라이브러리 초기화시 하드웨어 칩에 리셋을 하지 않음.
    Public Declare Function AxlOpenNoReset Lib "AXL.dll" (ByVal lIrqNo As Integer) As Integer
    ' 라이브러리 사용을 종료
    Public Declare Function AxlClose Lib "AXL.dll" () As Byte
    ' 라이브러리가 초기화 되어 있는 지 확인
    Public Declare Function AxlIsOpened Lib "AXL.dll" () As Byte

    ' 인터럽트를 사용한다.
    Public Declare Function AxlInterruptEnable Lib "AXL.dll" () As Integer
    ' 인터럽트를 사용안한다.
    Public Declare Function AxlInterruptDisable Lib "AXL.dll" () As Integer

    '========== 라이브러리 및 베이스 보드 정보 ============================================================

    ' 등록된 베이스 보드의 개수 확인
    Public Declare Function AxlGetBoardCount Lib "AXL.dll" (ByRef lpBoardCount As Integer) As Integer
    ' 라이브러리 버전 확인
    Public Declare Function AxlGetLibVersion Lib "AXL.dll" (ByVal szVersion As Byte) As Integer
    ' Network제품의 각 모듈별 연결상태를 확인하는 함수
    Public Declare Function AxlGetModuleNodeStatus Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer) As Integer
    ' 해당 보드가 제어 가능한 상태인지 반환한다.
    Public Declare Function AxlGetBoardStatus Lib "AXL.dll" (ByVal lBoardNo As Integer) As Integer

    ' Network 제품의 Configuration Lock 상태를 반환한다.
    ' *wpLockMode  : DISABLE(0), ENABLE(1)
    Public Declare Function AxlGetLockMode Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef wpLockMode As Integer) As Integer

    '========== 로그 레벨 =================================================================================

    ' EzSpy에 출력할 메시지 레벨 설정
    ' uLevel : 0 - 3 설정
    ' LEVEL_NONE(0)    : 모든 메시지를 출력하지 않는다.
    ' LEVEL_ERROR(1)   : 에러가 발생한 메시지만 출력한다.
    ' LEVEL_RUNSTOP(2) : 모션에서 Run / Stop 관련 메시지를 출력한다.
    ' LEVEL_FUNCTION(3): 모든 메시지를 출력한다.
    Public Declare Function AxlSetLogLevel Lib "AXL.dll" (ByVal uLevel As Integer) As Integer
    ' EzSpy에 출력할 메시지 레벨 확인
    Public Declare Function AxlGetLogLevel Lib "AXL.dll" (ByRef upLevel As Integer) As Integer

    '========== MLIII =================================================================================
    ' Network제품의 각 모듈을 검색을 시작하는 함수
    Public Declare Function AxlScanStart Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lNet As Integer) As Integer
    ' Network제품 각 보드의 모든 모듈을 connect하는 함수
    Public Declare Function AxlBoardConnect Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lNet As Integer) As Integer
    ' Network제품 각 보드의 모든 모듈을 Disconnect하는 함수
    Public Declare Function AxlBoardDisconnect Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lNet As Integer) As Integer

End Module
