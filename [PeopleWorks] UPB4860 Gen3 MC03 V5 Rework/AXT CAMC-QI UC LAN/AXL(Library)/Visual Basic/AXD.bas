'****************************************************************************
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
'** http:'www.ajinextek.com
'**
'*****************************************************************************
'*****************************************************************************
'*

Attribute VB_Name = "AXD"

'========== ���� �� ��� ���� =================================================================='
' DIO ����� �ִ��� Ȯ��
Public Declare Function AxdInfoIsDIOModule Lib "AXL.dll" (ByRef upStatus As Long) As Long

' DIO ����� �ִ��� Ȯ��
Public Declare Function AxdInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef lpModuleNo As Long) As Long

' DIO ����� ����� ���� Ȯ��
Public Declare Function AxdInfoGetModuleCount Lib "AXL.dll" (ByRef lpModuleCount As Long) As Long

' ������ ����� �Է� ���� ���� Ȯ��
Public Declare Function AxdInfoGetInputCount Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpCount As Long) As Long

' ������ ����� ��� ���� ���� Ȯ��
Public Declare Function AxdInfoGetOutputCount Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpCount As Long) As Long

' ������ ��� ��ȣ�� ���̽� ���� ��ȣ, ��� ��ġ, ��� ID Ȯ��
Public Declare Function AxdInfoGetModule Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpBoardNo As Long, ByRef lpModulePos As Long, ByRef upModuleID As Long) As Long

' �ش� ����� ��� ������ �������� ��ȯ�Ѵ�.
Public Declare Function AxdInfoGetModuleStatus Lib "AXL.dll" (ByVal lModuleNo As Long) As Long

'========== ���ͷ�Ʈ ���� Ȯ�� ================================================================='
' ������ ��⿡ ���ͷ�Ʈ �޽����� �޾ƿ��� ���Ͽ� ������ �޽���, �ݹ� �Լ� �Ǵ� �̺�Ʈ ����� ���
'========= ���ͷ�Ʈ ���� �Լ� =============================================================='
' �ݹ� �Լ� ����� �̺�Ʈ �߻� ������ ��� �ݹ� �Լ��� ȣ�� ������ ���� ������ �̺�Ʈ�� �������� �� �ִ� ������ ������
' �ݹ� �Լ��� ������ ���� �� ������ ���� ���μ����� ��ü�Ǿ� �ְ� �ȴ�.
' ��, �ݹ� �Լ� ���� ���ϰ� �ɸ��� �۾��� ���� ��쿡�� ��뿡 ���Ǹ� ���Ѵ�. 
' �̺�Ʈ ����� ��������� �̿��Ͽ� ���ͷ�Ʈ �߻����θ� ���������� �����ϰ� �ִٰ� ���ͷ�Ʈ�� �߻��ϸ� 
' ó�����ִ� �������, ������ ������ ���� �ý��� �ڿ��� �����ϰ� �ִ� ������ ������
' ���� ������ ���ͷ�Ʈ�� �����ϰ� ó������ �� �ִ� ������ �ִ�.
' �Ϲ������δ� ���� ������ ������, ���ͷ�Ʈ�� ����ó���� �ֿ� ���ɻ��� ��쿡 ���ȴ�. 
' �̺�Ʈ ����� �̺�Ʈ�� �߻� ���θ� �����ϴ� Ư�� �����带 ����Ͽ� ���� ���μ����� ������ ���۵ǹǷ�
' MultiProcessor �ý��۵�� �ڿ��� ���� ȿ�������� ����� �� �ְ� �Ǿ� Ư�� �����ϴ� ����̴�.
' ���ͷ�Ʈ �޽����� �޾ƿ��� ���Ͽ� ������ �޽��� �Ǵ� �ݹ� �Լ��� ����Ѵ�.
' (�޽��� �ڵ�, �޽��� ID, �ݹ��Լ�, ���ͷ�Ʈ �̺�Ʈ)
'    hWnd    : ������ �ڵ�, ������ �޼����� ������ ���. ������� ������ NULL�� �Է�.
'    uMessage: ������ �ڵ��� �޼���, ������� �ʰų� ����Ʈ���� ����Ϸ��� 0�� �Է�.
'    proc    : ���ͷ�Ʈ �߻��� ȣ��� �Լ��� ������, ������� ������ NULL�� �Է�.
'    pEvent  : �̺�Ʈ ������� �̺�Ʈ �ڵ�
Public Declare Function AxdiInterruptSetModule Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal hWnd As Long, ByVal uMessage As Long, ByVal pProc As Long, ByRef pEvent As Long) As Long

' ������ ����� ���ͷ�Ʈ ��� ���� ����
'======================================================'
' uUse       : DISABLE(0)    ' ���ͷ�Ʈ ����
'            : ENABLE(1)     ' ���ͷ�Ʈ ����
'=================================================='
Public Declare Function AxdiInterruptSetModuleEnable Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal uUse As Long) As Long

' ������ ����� ���ͷ�Ʈ ��� ���� Ȯ��
' ====================================================='
'  *upUse    : DISABLE(0)    '  ���ͷ�Ʈ ����
'            : ENABLE(1)     '  ���ͷ�Ʈ ����
' ====================================================='
Public Declare Function AxdiInterruptGetModuleEnable Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef upUse As Long) As Long

' ���ͷ�Ʈ �߻� ��ġ Ȯ��
Public Declare Function AxdiInterruptRead Lib "AXL.dll" (ByRef lpModuleNo As Long, ByRef upFlag As Long) As Long

'========== ���ͷ�Ʈ ��� / �ϰ� ���� ���� Ȯ�� ================================================'
' ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� bit ������ ��� �Ǵ� �ϰ� ���� ���� ����
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : �Է� ������ ���� Offset ��ġ
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' uValue     : DISABLE(0)
'            : ENABLE(1)
'==========================================================================================='
Public Declare Function AxdiInterruptEdgeSetBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByVal uValue As Long) As Long

' ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� byte ������ ��� �Ǵ� �ϰ� ���� ���� ����
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : �Է� ������ ���� Offset ��ġ
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' uValue     : 0x00 ~ 0x0FF ('1'�� Setting �� �κ� ���ͷ�Ʈ ����)
'==========================================================================================='
Public Declare Function AxdiInterruptEdgeSetByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByVal uValue As Long) As Long

' ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� word ������ ��� �Ǵ� �ϰ� ���� ���� ����
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : �Է� ������ ���� Offset ��ġ
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' uValue     : 0x00 ~ 0x0FFFF ('1'�� Setting �� �κ� ���ͷ�Ʈ ����)
'==========================================================================================='
Public Declare Function AxdiInterruptEdgeSetWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByVal uValue As Long) As Long

' ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� double word ������ ��� �Ǵ� �ϰ� ���� ���� ����
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : �Է� ������ ���� Offset ��ġ
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' uValue     : 0x00 ~ 0x0FFFFFFFF ('1'�� Setting �� �κ� ���ͷ�Ʈ ����)
'==========================================================================================='
Public Declare Function AxdiInterruptEdgeSetDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByVal uValue As Long) As Long

' ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� bit ������ ��� �Ǵ� �ϰ� ���� ���� Ȯ��
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : �Է� ������ ���� Offset ��ġ
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' *upValue   : 0x00 ~ 0x0FF ('1'�� Setting �� �κ� ���ͷ�Ʈ ����)
'==========================================================================================='
Public Declare Function AxdiInterruptEdgeGetBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByRef upValue As Long) As Long

' ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� byte ������ ��� �Ǵ� �ϰ� ���� ���� Ȯ��
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : �Է� ������ ���� Offset ��ġ
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' *upValue   : 0x00 ~ 0x0FF ('1'�� Setting �� �κ� ���ͷ�Ʈ ����)
'==========================================================================================='
Public Declare Function AxdiInterruptEdgeGetByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByRef upValue As Long) As Long

' ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� word ������ ��� �Ǵ� �ϰ� ���� ���� Ȯ��
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : �Է� ������ ���� Offset ��ġ
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' *upValue   : 0x00 ~ 0x0FFFFFFFF ('1'�� Setting �� �κ� ���ͷ�Ʈ ����)
'==========================================================================================='
Public Declare Function AxdiInterruptEdgeGetWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByRef upValue As Long) As Long

' ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� double word ������ ��� �Ǵ� �ϰ� ���� ���� Ȯ��
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : �Է� ������ ���� Offset ��ġ
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' *upValue   : 0x00 ~ 0x0FFFFFFFF ('1'�� Setting �� �κ� ���ͷ�Ʈ ����)
'==========================================================================================='
Public Declare Function AxdiInterruptEdgeGetDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByRef upValue As Long) As Long

' ��ü �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� bit ������ ��� �Ǵ� �ϰ� ���� ���� ����
'==============================================================================================='
' lOffset    : �Է� ������ ���� Offset ��ġ
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' uValue     : DISABLE(0)
'            : ENABLE(1)
'==========================================================================================='
Public Declare Function AxdiInterruptEdgeSet Lib "AXL.dll" (ByVal lOffset As Long, ByVal uMode As Long, ByVal uValue As Long) As Long

' ��ü �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset �������� bit ������ ��� �Ǵ� �ϰ� ���� ���� Ȯ��
'==============================================================================================='
' lOffset    : �Է� ������ ���� Offset ��ġ
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' *upValue   : DISABLE(0)
'            : ENABLE(1)
'==========================================================================================='
Public Declare Function AxdiInterruptEdgeGet Lib "AXL.dll" (ByVal lOffset As Long, ByVal uMode As Long, ByRef upValue As Long) As Long

'========== ����� ���� ���� Ȯ�� =============================================================='

' ������ ��, ��� ���� ����� Offset ��ġ���� bit ������ ������ ������ ����
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : �Է� ������ ���� Offset ��ġ
' uLevel     : LOW(0)
'            : HIGH(1)
'==========================================================================================='
Public Declare Function AxdiLevelSetInportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' ������ ��, ��� ���� ����� Offset ��ġ���� byte ������ ������ ������ ����
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : �Է� ������ ���� Offset ��ġ
' uLevel     : 0x00 ~ 0x0FF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
'==========================================================================================='
Public Declare Function AxdiLevelSetInportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' ������ ��, ��� ���� ����� Offset ��ġ���� word ������ ������ ������ ����
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : �Է� ������ ���� Offset ��ġ
' uLevel     : 0x00 ~ 0x0FFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
'==========================================================================================='
Public Declare Function AxdiLevelSetInportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' ������ ��, ��� ���� ����� Offset ��ġ���� double word ������ ������ ������ ����
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : �Է� ������ ���� Offset ��ġ
' uLevel     : 0x00 ~ 0x0FFFFFFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
'==========================================================================================='
Public Declare Function AxdiLevelSetInportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' ������ ��, ��� ���� ����� Offset ��ġ���� bit ������ ������ ������ Ȯ��
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : �Է� ������ ���� Offset ��ġ
' *upLevel   : LOW(0)
'            : HIGH(1)
'==========================================================================================='
Public Declare Function AxdiLevelGetInportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long

' ������ ��, ��� ���� ����� Offset ��ġ���� byte ������ ������ ������ Ȯ��
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : �Է� ������ ���� Offset ��ġ
' *upLevel   : 0x00 ~ 0x0FF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
'==========================================================================================='
Public Declare Function AxdiLevelGetInportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long

' ������ ��, ��� ���� ����� Offset ��ġ���� word ������ ������ ������ Ȯ��
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : �Է� ������ ���� Offset ��ġ
' *upLevel   : 0x00 ~ 0x0FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
'==========================================================================================='
Public Declare Function AxdiLevelGetInportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long

' ������ ��, ��� ���� ����� Offset ��ġ���� double word ������ ������ ������ Ȯ��
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : �Է� ������ ���� Offset ��ġ
' *upLevel   : 0x00 ~ 0x0FFFFFFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
'==========================================================================================='
Public Declare Function AxdiLevelGetInportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long

' ��ü ��, ��� ���� ����� Offset ��ġ���� bit ������ ������ ������ ����
'==============================================================================================='
' lOffset    : �Է� ������ ���� Offset ��ġ
' uLevel     : LOW(0)
'            : HIGH(1)
'==========================================================================================='
Public Declare Function AxdiLevelSetInport Lib "AXL.dll" (ByVal lOffset As Long, ByVal uLevel As Long) As Long

' ��ü ��, ��� ���� ����� Offset ��ġ���� bit ������ ������ ������ Ȯ��
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : �Է� ������ ���� Offset ��ġ
' *upLevel   : LOW(0)
'            : HIGH(1)
'==========================================================================================='
Public Declare Function AxdiLevelGetInport Lib "AXL.dll" (ByVal lOffset As Long, ByRef upLevel As Long) As Long

' ������ ��, ��� ���� ����� Offset ��ġ���� bit ������ ������ ������ ����
' ������ ��� ���� ����� Offset ��ġ���� bit ������ ������ ������ ����
'==========================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : ��� ������ ���� Offset ��ġ
' uLevel     : LOW(0)
'            : HIGH(1)
'==========================================================================================='
Public Declare Function AxdoLevelSetOutportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' ������ ��, ��� ���� ����� Offset ��ġ���� byte ������ ������ ������ ����
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : ��� ������ ���� Offset ��ġ
' uLevel     : 0x00 ~ 0x0FF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
'==========================================================================================='
Public Declare Function AxdoLevelSetOutportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' ������ ��, ��� ���� ����� Offset ��ġ���� word ������ ������ ������ ����
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : ��� ������ ���� Offset ��ġ
' uLevel     : 0x00 ~ 0x0FFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
'==========================================================================================='
Public Declare Function AxdoLevelSetOutportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' ������ ��, ��� ���� ����� Offset ��ġ���� double word ������ ������ ������ ����
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : ��� ������ ���� Offset ��ġ
' uLevel     : 0x00 ~ 0x0FFFFFFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
'==========================================================================================='
Public Declare Function AxdoLevelSetOutportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' ������ ��, ��� ���� ����� Offset ��ġ���� bit ������ ������ ������ Ȯ��
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : ��� ������ ���� Offset ��ġ
' *upLevel   : LOW(0)
'            : HIGH(1)
'==========================================================================================='
Public Declare Function AxdoLevelGetOutportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long

' ������ ��, ��� ���� ����� Offset ��ġ���� byte ������ ������ ������ Ȯ��
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : ��� ������ ���� Offset ��ġ
' uLevel     : 0x00 ~ 0x0FF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
'==========================================================================================='
Public Declare Function AxdoLevelGetOutportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long

' ������ ��, ��� ���� ����� Offset ��ġ���� word ������ ������ ������ Ȯ��
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : ��� ������ ���� Offset ��ġ
' uLevel     : 0x00 ~ 0x0FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
'==========================================================================================='
Public Declare Function AxdoLevelGetOutportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long

' ������ ��, ��� ���� ����� Offset ��ġ���� double word ������ ������ ������ Ȯ��
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : ��� ������ ���� Offset ��ġ
' uLevel     : 0x00 ~ 0x0FFFFFFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
'==========================================================================================='
Public Declare Function AxdoLevelGetOutportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long

' ��ü ��, ��� ���� ����� Offset ��ġ���� bit ������ ������ ������ ����
'==============================================================================================='
' lOffset    : ��� ������ ���� Offset ��ġ
' uLevel     : LOW(0)
'            : HIGH(1)
'==========================================================================================='
Public Declare Function AxdoLevelSetOutport Lib "AXL.dll" (ByVal lOffset As Long, ByVal uLevel As Long) As Long

' ��ü ��, ��� ���� ����� Offset ��ġ���� bit ������ ������ ������ Ȯ��
'==============================================================================================='
' lOffset    : ��� ������ ���� Offset ��ġ
' *upLevel   : LOW(0)
'            : HIGH(1)
'==========================================================================================='
Public Declare Function AxdoLevelGetOutport Lib "AXL.dll" (ByVal lOffset As Long, ByRef upLevel As Long) As Long
'========== ����� ��Ʈ ���� �б� =============================================================='

' ��ü ��� ���� ����� Offset ��ġ���� bit ������ �����͸� ���
'==============================================================================================='
' lOffset    : ��� ������ ���� Offset ��ġ
' uLevel     : LOW(0)
'            : HIGH(1)
'==========================================================================================='
Public Declare Function AxdoWriteOutport Lib "AXL.dll" (ByVal lOffset As Long, ByVal uValue As Long) As Long

' ������ ��� ���� ����� Offset ��ġ���� bit ������ �����͸� ���
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : ��� ������ ���� Offset ��ġ
' uLevel     : LOW(0)
'            : HIGH(1)
'==========================================================================================='
Public Declare Function AxdoWriteOutportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long

' ������ ��� ���� ����� Offset ��ġ���� byte ������ �����͸� ���
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : ��� ������ ���� Offset ��ġ
' uValue     : 0x00 ~ 0x0FF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
'==========================================================================================='
Public Declare Function AxdoWriteOutportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long

' ������ ��� ���� ����� Offset ��ġ���� word ������ �����͸� ���
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : ��� ������ ���� Offset ��ġ
' uValue     : 0x00 ~ 0x0FFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
'==========================================================================================='
Public Declare Function AxdoWriteOutportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long

' ������ ��� ���� ����� Offset ��ġ���� double word ������ �����͸� ���
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : ��� ������ ���� Offset ��ġ
' uValue     : 0x00 ~ 0x0FFFFFFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
'==========================================================================================='
Public Declare Function AxdoWriteOutportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long

' ��ü ��� ���� ����� Offset ��ġ���� bit ������ �����͸� �б�
'==============================================================================================='
' lOffset    : ��� ������ ���� Offset ��ġ
' *upLevel   : LOW(0)
'            : HIGH(1)
'==========================================================================================='
Public Declare Function AxdoReadOutport Lib "AXL.dll" (ByVal lOffset As Long, ByRef upValue As Long) As Long

' ������ ��� ���� ����� Offset ��ġ���� bit ������ �����͸� �б�
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : ��� ������ ���� Offset ��ġ
' *upLevel   : LOW(0)
'            : HIGH(1)
'==========================================================================================='
Public Declare Function AxdoReadOutportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' ������ ��� ���� ����� Offset ��ġ���� byte ������ �����͸� �б�
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : ��� ������ ���� Offset ��ġ
' *upValue   : 0x00 ~ 0x0FF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
'==========================================================================================='
Public Declare Function AxdoReadOutportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' ������ ��� ���� ����� Offset ��ġ���� word ������ �����͸� �б�
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : ��� ������ ���� Offset ��ġ
' *upValue   : 0x00 ~ 0x0FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
'==========================================================================================='
Public Declare Function AxdoReadOutportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' ������ ��� ���� ����� Offset ��ġ���� double word ������ �����͸� �б�
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : ��� ������ ���� Offset ��ġ
' *upValue   : 0x00 ~ 0x0FFFFFFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
'==========================================================================================='
Public Declare Function AxdoReadOutportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' ��ü �Է� ���� ����� Offset ��ġ���� bit ������ �����͸� �б�
'==============================================================================================='
' lOffset    : �Է� ������ ���� Offset ��ġ
' *upValue   : LOW(0)
'            : HIGH(1)
'==========================================================================================='
Public Declare Function AxdiReadInport Lib "AXL.dll" (ByVal lOffset As Long, ByRef upValue As Long) As Long

' ������ �Է� ���� ����� Offset ��ġ���� bit ������ �����͸� �б�
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : �Է� ������ ���� Offset ��ġ
' *upValue   : LOW(0)
'            : HIGH(1)
'==========================================================================================='
Public Declare Function AxdiReadInportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' ������ �Է� ���� ����� Offset ��ġ���� byte ������ �����͸� �б�
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : �Է� ������ ���� Offset ��ġ
' *upValue   : 0x00 ~ 0x0FF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
'==========================================================================================='
Public Declare Function AxdiReadInportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' ������ �Է� ���� ����� Offset ��ġ���� word ������ �����͸� �б�
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : �Է� ������ ���� Offset ��ġ
' *upValue   : 0x00 ~ 0x0FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
'==========================================================================================='
Public Declare Function AxdiReadInportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' ������ �Է� ���� ����� Offset ��ġ���� double word ������ �����͸� �б�
'==============================================================================================='
' lModuleNo  : ��� ��ȣ
' lOffset    : �Է� ������ ���� Offset ��ġ
' *upValue   : 0x00 ~ 0x0FFFFFFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
'==========================================================================================='
Public Declare Function AxdiReadInportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

'== MLII �� M-Systems DIO(R7 series) ���� �Լ�.
' ������ ��⿡ ������ �Է� ������ Ȯ�� ��� ����� Offset ��ġ���� bit ������ �����͸� �б�
'==============================================================================================='
' lModuleNo   : ��� ��ȣ
' lOffset     : �Է� ������ ���� Offset ��ġ(0~15)
' *upValue    : LOW(0)
'             : HIGH(1)
'==============================================================================================='
Public Declare Function AxdReadExtInportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' ������ ��⿡ ������ �Է� ������ Ȯ�� ��� ����� Offset ��ġ���� byte ������ �����͸� �б�
'==============================================================================================='
' lModuleNo   : ��� ��ȣ
' lOffset     : �Է� ������ ���� Offset ��ġ(0~1)
' *upValue    : 0x00 ~ 0x0FF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
'==============================================================================================='
Public Declare Function AxdReadExtInportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' ������ ��⿡ ������ �Է� ������ Ȯ�� ��� ����� Offset ��ġ���� word ������ �����͸� �б�
'==============================================================================================='
' lModuleNo   : ��� ��ȣ
' lOffset     : �Է� ������ ���� Offset ��ġ(0)
' *upValue    : 0x00 ~ 0x0FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
'==============================================================================================='
Public Declare Function AxdReadExtInportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' ������ ��⿡ ������ �Է� ������ Ȯ�� ��� ����� Offset ��ġ���� dword ������ �����͸� �б�
'==============================================================================================='
' lModuleNo   : ��� ��ȣ
' lOffset     : �Է� ������ ���� Offset ��ġ(0)
' *upValue    : 0x00 ~ 0x00000FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
'==============================================================================================='
Public Declare Function AxdReadExtInportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� bit ������ �����͸� �б�
'==============================================================================================='
' lModuleNo   : ��� ��ȣ
' lOffset     : ��� ������ ���� Offset ��ġ(0~15)
' *upValue    : LOW(0)
'             : HIGH(1)
'==============================================================================================='
Public Declare Function AxdReadExtOutportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� byte ������ �����͸� �б�
'==============================================================================================='
' lModuleNo   : ��� ��ȣ
' lOffset     : ��� ������ ���� Offset ��ġ(0~1)
' *upValue    : 0x00 ~ 0x0FF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
'==============================================================================================='
Public Declare Function AxdReadExtOutportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� word ������ �����͸� �б�
'==============================================================================================='
' lModuleNo   : ��� ��ȣ
' lOffset     : ��� ������ ���� Offset ��ġ(0)
' *upValue    : 0x00 ~ 0x0FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
'==============================================================================================='
Public Declare Function AxdReadExtOutportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� dword ������ �����͸� �б�
'==============================================================================================='
' lModuleNo   : ��� ��ȣ
' lOffset     : ��� ������ ���� Offset ��ġ(0)
' *upValue    : 0x00 ~ 0x00000FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
'==============================================================================================='
Public Declare Function AxdReadExtOutportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� bit ������ ������ ���
'==============================================================================================='
' lModuleNo   : ��� ��ȣ
' lOffset     : ��� ������ ���� Offset ��ġ
' uValue      : LOW(0)
'             : HIGH(1)
'==============================================================================================='
Public Declare Function AxdWriteExtOutportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long

' ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� byte ������ ������ ���
'==============================================================================================='
' lModuleNo   : ��� ��ȣ
' lOffset     : ��� ������ ���� Offset ��ġ(0~1)
' uValue      : 0x00 ~ 0x0FF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
'==============================================================================================='
Public Declare Function AxdWriteExtOutportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long

' ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� word ������ ������ ���
'==============================================================================================='
' lModuleNo   : ��� ��ȣ
' lOffset     : ��� ������ ���� Offset ��ġ(0)
' uValue    : 0x00 ~ 0x0FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
'==============================================================================================='
Public Declare Function AxdWriteExtOutportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long

' ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� dword ������ ������ ���
'==============================================================================================='
' lModuleNo   : ��� ��ȣ
' lOffset     : ��� ������ ���� Offset ��ġ(0)
' uValue    : 0x00 ~ 0x00000FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
'==============================================================================================='
Public Declare Function AxdWriteExtOutportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long

' ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� bit ������ ������ ������ ����
'==============================================================================================='
' lModuleNo   : ��� ��ȣ
' lOffset     : �Է� ������ ���� Offset ��ġ(0~15)
' uLevel      : LOW(0)
'             : HIGH(1)
'==============================================================================================='
Public Declare Function AxdLevelSetExtportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� byte ������ ������ ������ ����
'==============================================================================================='
' lModuleNo   : ��� ��ȣ
' lOffset     : �Է� ������ ���� Offset ��ġ(0~1)
' uLevel      : 0x00 ~ 0xFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
'==============================================================================================='
Public Declare Function AxdLevelSetExtportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� word ������ ������ ������ ����
'==============================================================================================='
' lModuleNo   : ��� ��ȣ
' lOffset     : �Է� ������ ���� Offset ��ġ(0)
' uLevel      : 0x00 ~ 0xFFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
'==============================================================================================='
Public Declare Function AxdLevelSetExtportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� dword ������ ������ ������ ����
'==============================================================================================='
' lModuleNo   : ��� ��ȣ
' lOffset     : �Է� ������ ���� Offset ��ġ(0)
' uLevel      : 0x00 ~ 0x0000FFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
'==============================================================================================='
Public Declare Function AxdLevelSetExtportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� bit ������ ������ ���� Ȯ��
'==============================================================================================='
' lModuleNo   : ��� ��ȣ
' lOffset     : �Է� ������ ���� Offset ��ġ(0~15)
' *upLevel      : LOW(0)
'             : HIGH(1)
'==============================================================================================='
Public Declare Function AxdLevelGetExtportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal upLevel As Long) As Long

' ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� byte ������ ������ ���� Ȯ��
'==============================================================================================='
' lModuleNo   : ��� ��ȣ
' lOffset     : �Է� ������ ���� Offset ��ġ(0~1)
' *upLevel      : 0x00 ~ 0xFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
'==============================================================================================='
Public Declare Function AxdLevelGetExtportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal upLevel As Long) As Long

' ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� word ������ ������ ���� Ȯ��
'==============================================================================================='
' lModuleNo   : ��� ��ȣ
' lOffset     : �Է� ������ ���� Offset ��ġ(0)
' *upLevel      : 0x00 ~ 0xFFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
'==============================================================================================='
Public Declare Function AxdLevelGetExtportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal upLevel As Long) As Long

' ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� dword ������ ������ ���� Ȯ��
'==============================================================================================='
' lModuleNo   : ��� ��ȣ
' lOffset     : �Է� ������ ���� Offset ��ġ(0)
' *upLevel      : 0x00 ~ 0x0000FFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
'==============================================================================================='
Public Declare Function AxdLevelGetExtportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal upLevel As Long) As Long

'========== ��� �Լ� =========================================================================='
' ������ �Է� ���� ����� Offset ��ġ���� ��ȣ�� Off���� On���� �ٲ������ Ȯ��
'==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' *upValue   : FALSE(0)
    '            : TRUE(1)
    '==========================================================================================='
Public Declare Function AxdiIsPulseOn Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' ������ �Է� ���� ����� Offset ��ġ���� ��ȣ�� On���� Off���� �ٲ������ Ȯ��
'==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' *upValue   : FALSE(0)
    '            : TRUE(1)
    '==========================================================================================='
Public Declare Function AxdiIsPulseOff Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' ������ �Է� ���� ����� Offset ��ġ���� ��ȣ�� count ��ŭ ȣ��� ���� On ���·� �����ϴ��� Ȯ��
'==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
    ' *upValue   : FALSE(0)
    '            : TRUE(1)
    ' lStart     : 1(���� ȣ��)
    '            : 0(�ݺ� ȣ��)
    '==========================================================================================='
Public Declare Function AxdiIsOn Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal lCount As Long, ByRef upValue As Long, ByVal lStart As Long) As Long

' ������ �Է� ���� ����� Offset ��ġ���� ��ȣ�� count ��ŭ ȣ��� ���� Off ���·� �����ϴ��� Ȯ��
'==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
    ' *upValue   : FALSE(0)
    '            : TRUE(1)
    ' lStart     : 1(���� ȣ��)
    '            : 0(�ݺ� ȣ��)
    '==========================================================================================='
Public Declare Function AxdiIsOff Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal lCount As Long, ByRef upValue As Long, ByVal lStart As Long) As Long

' ������ ��� ���� ����� Offset ��ġ���� ������ mSec���� On�� �����ϴٰ� Off ��Ŵ
'==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
    ' lmSec      : 1 ~ 30000
    '==========================================================================================='
Public Declare Function AxdoOutPulseOn Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal lmSec As Long) As Long

' ������ ��� ���� ����� Offset ��ġ���� ������ mSec���� Off�� �����ϴٰ� On ��Ŵ
'==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
    ' lmSec      : 1 ~ 30000
    '==========================================================================================='
Public Declare Function AxdoOutPulseOff Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal lmSec As Long) As Long

' ������ ��� ���� ����� Offset ��ġ���� ������ Ƚ��, ������ �������� ����� �� ������ ��»��¸� ������
'==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' lInitState: Off(0)
    '            : On(1)
    ' lmSecOn    : 1 ~ 30000
    ' lmSecOff   : 1 ~ 30000
    ' lCount     : 1 ~ 0x7FFFFFFF(2147483647)
    '            : -1 ���� ���
    '==========================================================================================='
Public Declare Function AxdoToggleStart Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal lInitState As Long, ByVal lmSecOn As Long, ByVal lmSecOff As Long, ByVal lCount As Long) As Long

' ������ ��� ���� ����� Offset ��ġ���� ������� ����� ������ ��ȣ ���·� ���� ��Ŵ
'==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' uOnOff     : Off(0)
    '            : On(1)
    '==========================================================================================='
Public Declare Function AxdoToggleStop Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uOnOff As Long) As Long

' ������ ��� ����� Network�� ���� ���� ��� ��� ���¸� ��� Byte ������ �����Ѵ�.
'==============================================================================================='
' lModuleNo   : ��� ��ȣ
' dwSize      : ���� �� Byte ��(ex. RTEX-DB32 : 2, RTEX-DO32 : 4)
' dwaSetValue : ���� �� ���� ��(Default�� Network ���� ���� �� ���� ����)
'             : 0 --> Network ���� ���� �� ���� ����
'             : 1 --> On
'             : 2 --> Off
'==============================================================================================='
Public Declare Function AxdoSetNetworkErrorAct Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dwSize As Long, ByRef dwaSetValue As Long) As Long

Public Declare Function AxdSetContactNum Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dwInputNum As Long, ByVal dwOutputNum As Long) As Long

Public Declare Function AxdGetContactNum Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef dwpInputNum As Long, ByRef dwpOutputNum As Long) As Long