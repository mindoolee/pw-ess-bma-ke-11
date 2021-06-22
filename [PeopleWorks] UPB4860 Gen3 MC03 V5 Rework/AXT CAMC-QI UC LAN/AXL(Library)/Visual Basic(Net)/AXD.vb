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


    '========== ���� �� ��� ���� =================================================================='

    ' DIO ����� �ִ��� Ȯ��
    Public Declare Function AxdInfoIsDIOModule Lib "AXL.dll" (ByRef upStatus As Integer) As Integer

    ' DIO ����� �ִ��� Ȯ��
    Public Declare Function AxdInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByRef lpModuleNo As Integer) As Integer

    ' DIO ����� ����� ���� Ȯ��
    Public Declare Function AxdInfoGetModuleCount Lib "AXL.dll" (ByRef lpModuleCount As Integer) As Integer

    ' ������ ����� �Է� ���� ���� Ȯ��
    Public Declare Function AxdInfoGetInputCount Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpCount As Integer) As Integer

    ' ������ ����� ��� ���� ���� Ȯ��
    Public Declare Function AxdInfoGetOutputCount Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpCount As Integer) As Integer

    ' ������ ��� ��ȣ�� ���̽� ���� ��ȣ, ��� ��ġ, ��� ID Ȯ��
    Public Declare Function AxdInfoGetModule Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpBoardNo As Integer, ByRef lpModulePos As Integer, ByRef upModuleID As Integer) As Integer

    ' �ش� ����� ��� ������ �������� ��ȯ�Ѵ�.
    Public Declare Function AxdInfoGetModuleStatus Lib "AXL.dll" (ByVal lModuleNo As Integer) As Integer

    '========== ���ͷ�Ʈ ���� Ȯ�� ================================================================='
    ' ������ ��⿡ ���ͷ�Ʈ �޽����� �޾ƿ��� ���Ͽ� ������ �޽���, �ݹ� �Լ� �Ǵ� �̺�Ʈ ����� ���
    ' ������ ��⿡ ���ͷ�Ʈ �޽����� �޾ƿ��� ���Ͽ� ������ �޽���, �ݹ� �Լ� �Ǵ� �̺�Ʈ ����� ���
    '========= ���ͷ�Ʈ ���� �Լ� =================================================================='
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
    Public Declare Function AxdiInterruptSetModule Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal hWnd As Integer, ByVal uMessage As Integer, ByVal pProc As Integer, ByRef pEvent As Integer) As Integer

    ' ������ ����� ���ͷ�Ʈ ��� ���� ����
    '======================================================'
    ' uUse       : DISABLE(0)    ' ���ͷ�Ʈ ����
    '            : ENABLE(1)     ' ���ͷ�Ʈ ����
    '======================================================'
    Public Declare Function AxdiInterruptSetModuleEnable Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal uUse As Integer) As Integer

    ' ������ ����� ���ͷ�Ʈ ��� ���� Ȯ��
    ' ======================================================' 
    '  *upUse    : DISABLE(0)    '  ���ͷ�Ʈ ����
    '            : ENABLE(1)     '  ���ͷ�Ʈ ����
    ' ======================================================' 
    Public Declare Function AxdiInterruptGetModuleEnable Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef upUse As Integer) As Integer

    ' ���ͷ�Ʈ �߻� ��ġ Ȯ��
    Public Declare Function AxdiInterruptRead Lib "AXL.dll" (ByRef lpModuleNo As Integer, ByRef upFlag As Integer) As Integer

    '========== ���ͷ�Ʈ ��� / �ϰ� ���� ���� Ȯ�� ================================================'
    ' ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� bit ������ ��� �Ǵ� �ϰ� ���� ���� ����
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' uValue     : DISABLE(0)
    '            : ENABLE(1)
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeSetBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByVal uValue As Integer) As Integer

    ' ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� byte ������ ��� �Ǵ� �ϰ� ���� ���� ����
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' uValue     : 0x00 ~ 0x0FF ('1'�� Setting �� �κ� ���ͷ�Ʈ ����)
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeSetByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByVal uValue As Integer) As Integer

    ' ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� word ������ ��� �Ǵ� �ϰ� ���� ���� ����
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' uValue     : 0x00 ~ 0x0FFFF ('1'�� Setting �� �κ� ���ͷ�Ʈ ����)
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeSetWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByVal uValue As Integer) As Integer

    ' ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� double word ������ ��� �Ǵ� �ϰ� ���� ���� ����
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' uValue     : 0x00 ~ 0x0FFFFFFFF ('1'�� Setting �� �κ� ���ͷ�Ʈ ����)
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeSetDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByVal uValue As Integer) As Integer

    ' ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� bit ������ ��� �Ǵ� �ϰ� ���� ���� Ȯ��
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' *upValue   : 0x00 ~ 0x0FF ('1'�� Setting �� �κ� ���ͷ�Ʈ ����)
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeGetBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByRef upValue As Integer) As Integer

    ' ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� byte ������ ��� �Ǵ� �ϰ� ���� ���� Ȯ��
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' *upValue   : 0x00 ~ 0x0FF ('1'�� Setting �� �κ� ���ͷ�Ʈ ����)
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeGetByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByRef upValue As Integer) As Integer

    ' ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� word ������ ��� �Ǵ� �ϰ� ���� ���� Ȯ��
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' *upValue   : 0x00 ~ 0x0FFFFFFFF ('1'�� Setting �� �κ� ���ͷ�Ʈ ����)
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeGetWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByRef upValue As Integer) As Integer

    ' ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� double word ������ ��� �Ǵ� �ϰ� ���� ���� Ȯ��
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' *upValue   : 0x00 ~ 0x0FFFFFFFF ('1'�� Setting �� �κ� ���ͷ�Ʈ ����)
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeGetDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByRef upValue As Integer) As Integer

    ' ��ü �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� bit ������ ��� �Ǵ� �ϰ� ���� ���� ����
    '==============================================================================================='
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' uValue     : DISABLE(0)
    '            : ENABLE(1)
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeSet Lib "AXL.dll" (ByVal lOffset As Integer, ByVal uMode As Integer, ByVal uValue As Integer) As Integer

    ' ��ü �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset �������� bit ������ ��� �Ǵ� �ϰ� ���� ���� Ȯ��
    '==============================================================================================='
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' *upValue   : DISABLE(0)
    '            : ENABLE(1)
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeGet Lib "AXL.dll" (ByVal lOffset As Integer, ByVal uMode As Integer, ByRef upValue As Integer) As Integer

    '========== ����� ���� ���� Ȯ�� =================================================================================

    ' ������ ��, ��� ���� ����� Offset ��ġ���� bit ������ ������ ������ ����
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' uLevel     : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdiLevelSetInportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' ������ ��, ��� ���� ����� Offset ��ġ���� byte ������ ������ ������ ����
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' uLevel     : 0x00 ~ 0x0FF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdiLevelSetInportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' ������ ��, ��� ���� ����� Offset ��ġ���� word ������ ������ ������ ����
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' uLevel     : 0x00 ~ 0x0FFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdiLevelSetInportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' ������ ��, ��� ���� ����� Offset ��ġ���� double word ������ ������ ������ ����
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' uLevel     : 0x00 ~ 0x0FFFFFFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdiLevelSetInportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' ������ ��, ��� ���� ����� Offset ��ġ���� bit ������ ������ ������ Ȯ��
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' *upLevel   : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdiLevelGetInportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer

    ' ������ ��, ��� ���� ����� Offset ��ġ���� byte ������ ������ ������ Ȯ��
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' *upLevel   : 0x00 ~ 0x0FF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdiLevelGetInportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer

    ' ������ ��, ��� ���� ����� Offset ��ġ���� word ������ ������ ������ Ȯ��
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' *upLevel   : 0x00 ~ 0x0FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdiLevelGetInportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer

    ' ������ ��, ��� ���� ����� Offset ��ġ���� double word ������ ������ ������ Ȯ��
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' *upLevel   : 0x00 ~ 0x0FFFFFFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdiLevelGetInportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer

    ' ��ü ��, ��� ���� ����� Offset ��ġ���� bit ������ ������ ������ ����
    '==============================================================================================='
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' uLevel     : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdiLevelSetInport Lib "AXL.dll" (ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' ��ü ��, ��� ���� ����� Offset ��ġ���� bit ������ ������ ������ Ȯ��
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' *upLevel   : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdiLevelGetInport Lib "AXL.dll" (ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer

    ' ������ ��, ��� ���� ����� Offset ��ġ���� bit ������ ������ ������ ����
    ' ������ ��� ���� ����� Offset ��ġ���� bit ������ ������ ������ ����
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' uLevel     : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoLevelSetOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' ������ ��, ��� ���� ����� Offset ��ġ���� byte ������ ������ ������ ����
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' uLevel     : 0x00 ~ 0x0FF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdoLevelSetOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' ������ ��, ��� ���� ����� Offset ��ġ���� word ������ ������ ������ ����
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' uLevel     : 0x00 ~ 0x0FFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdoLevelSetOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' ������ ��, ��� ���� ����� Offset ��ġ���� double word ������ ������ ������ ����
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' uLevel     : 0x00 ~ 0x0FFFFFFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdoLevelSetOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' ������ ��, ��� ���� ����� Offset ��ġ���� bit ������ ������ ������ Ȯ��
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' *upLevel   : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoLevelGetOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer

    ' ������ ��, ��� ���� ����� Offset ��ġ���� byte ������ ������ ������ Ȯ��
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' uLevel     : 0x00 ~ 0x0FF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdoLevelGetOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer

    ' ������ ��, ��� ���� ����� Offset ��ġ���� word ������ ������ ������ Ȯ��
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' uLevel     : 0x00 ~ 0x0FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdoLevelGetOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer

    ' ������ ��, ��� ���� ����� Offset ��ġ���� double word ������ ������ ������ Ȯ��
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' uLevel     : 0x00 ~ 0x0FFFFFFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdoLevelGetOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer

    ' ��ü ��, ��� ���� ����� Offset ��ġ���� bit ������ ������ ������ ����
    '==============================================================================================='
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' uLevel     : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoLevelSetOutport Lib "AXL.dll" (ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' ��ü ��, ��� ���� ����� Offset ��ġ���� bit ������ ������ ������ Ȯ��
    '==============================================================================================='
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' *upLevel   : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoLevelGetOutport Lib "AXL.dll" (ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer
    '========== ����� ��Ʈ ���� �б� =================================================================================

    ' ��ü ��� ���� ����� Offset ��ġ���� bit ������ �����͸� ���
    '==============================================================================================='
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' uLevel     : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoWriteOutport Lib "AXL.dll" (ByVal lOffset As Integer, ByVal uValue As Integer) As Integer

    ' ������ ��� ���� ����� Offset ��ġ���� bit ������ �����͸� ���
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' uLevel     : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoWriteOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer

    ' ������ ��� ���� ����� Offset ��ġ���� byte ������ �����͸� ���
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' uValue     : 0x00 ~ 0x0FF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdoWriteOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer

    ' ������ ��� ���� ����� Offset ��ġ���� word ������ �����͸� ���
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' uValue     : 0x00 ~ 0x0FFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdoWriteOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer

    ' ������ ��� ���� ����� Offset ��ġ���� double word ������ �����͸� ���
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' uValue     : 0x00 ~ 0x0FFFFFFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdoWriteOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer

    ' ��ü ��� ���� ����� Offset ��ġ���� bit ������ �����͸� �б�
    '==============================================================================================='
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' *upLevel   : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoReadOutport Lib "AXL.dll" (ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' ������ ��� ���� ����� Offset ��ġ���� bit ������ �����͸� �б�
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' *upLevel   : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoReadOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' ������ ��� ���� ����� Offset ��ġ���� byte ������ �����͸� �б�
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' *upValue   : 0x00 ~ 0x0FF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdoReadOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' ������ ��� ���� ����� Offset ��ġ���� word ������ �����͸� �б�
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' *upValue   : 0x00 ~ 0x0FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdoReadOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' ������ ��� ���� ����� Offset ��ġ���� double word ������ �����͸� �б�
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' *upValue   : 0x00 ~ 0x0FFFFFFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdoReadOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' ��ü �Է� ���� ����� Offset ��ġ���� bit ������ �����͸� �б�
    '==============================================================================================='
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' *upValue   : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdiReadInport Lib "AXL.dll" (ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' ������ �Է� ���� ����� Offset ��ġ���� bit ������ �����͸� �б�
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' *upValue   : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdiReadInportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' ������ �Է� ���� ����� Offset ��ġ���� byte ������ �����͸� �б�
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' *upValue   : 0x00 ~ 0x0FF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdiReadInportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' ������ �Է� ���� ����� Offset ��ġ���� word ������ �����͸� �б�
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' *upValue   : 0x00 ~ 0x0FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdiReadInportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' ������ �Է� ���� ����� Offset ��ġ���� double word ������ �����͸� �б�
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' *upValue   : 0x00 ~ 0x0FFFFFFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdiReadInportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    '== MLII �� M-Systems DIO(R7 series) ���� �Լ�.
    ' ������ ��⿡ ������ �Է� ������ Ȯ�� ��� ����� Offset ��ġ���� bit ������ �����͸� �б�
    '==============================================================================================='
    ' lModuleNo   : ��� ��ȣ
    ' lOffset     : �Է� ������ ���� Offset ��ġ(0~15)
    ' *upValue    : LOW(0)
    '             : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdReadExtInportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' ������ ��⿡ ������ �Է� ������ Ȯ�� ��� ����� Offset ��ġ���� byte ������ �����͸� �б�
    '==============================================================================================='
    ' lModuleNo   : ��� ��ȣ
    ' lOffset     : �Է� ������ ���� Offset ��ġ(0~1)
    ' *upValue    : 0x00 ~ 0x0FF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdReadExtInportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' ������ ��⿡ ������ �Է� ������ Ȯ�� ��� ����� Offset ��ġ���� word ������ �����͸� �б�
    '==============================================================================================='
    ' lModuleNo   : ��� ��ȣ
    ' lOffset     : �Է� ������ ���� Offset ��ġ(0)
    ' *upValue    : 0x00 ~ 0x0FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdReadExtInportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' ������ ��⿡ ������ �Է� ������ Ȯ�� ��� ����� Offset ��ġ���� dword ������ �����͸� �б�
    '==============================================================================================='
    ' lModuleNo   : ��� ��ȣ
    ' lOffset     : �Է� ������ ���� Offset ��ġ(0)
    ' *upValue    : 0x00 ~ 0x00000FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdReadExtInportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� bit ������ �����͸� �б�
    '==============================================================================================='
    ' lModuleNo   : ��� ��ȣ
    ' lOffset     : ��� ������ ���� Offset ��ġ(0~15)
    ' *upValue    : LOW(0)
    '             : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdReadExtOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� byte ������ �����͸� �б�
    '==============================================================================================='
    ' lModuleNo   : ��� ��ȣ
    ' lOffset     : ��� ������ ���� Offset ��ġ(0~1)
    ' *upValue    : 0x00 ~ 0x0FF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdReadExtOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� word ������ �����͸� �б�
    '==============================================================================================='
    ' lModuleNo   : ��� ��ȣ
    ' lOffset     : ��� ������ ���� Offset ��ġ(0)
    ' *upValue    : 0x00 ~ 0x0FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdReadExtOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� dword ������ �����͸� �б�
    '==============================================================================================='
    ' lModuleNo   : ��� ��ȣ
    ' lOffset     : ��� ������ ���� Offset ��ġ(0)
    ' *upValue    : 0x00 ~ 0x00000FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdReadExtOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� bit ������ ������ ���
    '==============================================================================================='
    ' lModuleNo   : ��� ��ȣ
    ' lOffset     : ��� ������ ���� Offset ��ġ
    ' uValue      : LOW(0)
    '             : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdWriteExtOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer

    ' ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� byte ������ ������ ���
    '==============================================================================================='
    ' lModuleNo   : ��� ��ȣ
    ' lOffset     : ��� ������ ���� Offset ��ġ(0~1)
    ' uValue      : 0x00 ~ 0x0FF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdWriteExtOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer

    ' ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� word ������ ������ ���
    '==============================================================================================='
    ' lModuleNo   : ��� ��ȣ
    ' lOffset     : ��� ������ ���� Offset ��ġ(0)
    ' uValue    : 0x00 ~ 0x0FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdWriteExtOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer

    ' ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� dword ������ ������ ���
    '==============================================================================================='
    ' lModuleNo   : ��� ��ȣ
    ' lOffset     : ��� ������ ���� Offset ��ġ(0)
    ' uValue    : 0x00 ~ 0x00000FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdWriteExtOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer

    ' ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� bit ������ ������ ������ ����
    '==============================================================================================='
    ' lModuleNo   : ��� ��ȣ
    ' lOffset     : �Է� ������ ���� Offset ��ġ(0~15)
    ' uLevel      : LOW(0)
    '             : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdLevelSetExtportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� byte ������ ������ ������ ����
    '==============================================================================================='
    ' lModuleNo   : ��� ��ȣ
    ' lOffset     : �Է� ������ ���� Offset ��ġ(0~1)
    ' uLevel      : 0x00 ~ 0xFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdLevelSetExtportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� word ������ ������ ������ ����
    '==============================================================================================='
    ' lModuleNo   : ��� ��ȣ
    ' lOffset     : �Է� ������ ���� Offset ��ġ(0)
    ' uLevel      : 0x00 ~ 0xFFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdLevelSetExtportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� dword ������ ������ ������ ����
    '==============================================================================================='
    ' lModuleNo   : ��� ��ȣ
    ' lOffset     : �Է� ������ ���� Offset ��ġ(0)
    ' uLevel      : 0x00 ~ 0x0000FFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdLevelSetExtportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� bit ������ ������ ���� Ȯ��
    '==============================================================================================='
    ' lModuleNo   : ��� ��ȣ
    ' lOffset     : �Է� ������ ���� Offset ��ġ(0~15)
    ' *upLevel      : LOW(0)
    '             : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdLevelGetExtportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal upLevel As Integer) As Integer

    ' ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� byte ������ ������ ���� Ȯ��
    '==============================================================================================='
    ' lModuleNo   : ��� ��ȣ
    ' lOffset     : �Է� ������ ���� Offset ��ġ(0~1)
    ' *upLevel      : 0x00 ~ 0xFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdLevelGetExtportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal upLevel As Integer) As Integer

    ' ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� word ������ ������ ���� Ȯ��
    '==============================================================================================='
    ' lModuleNo   : ��� ��ȣ
    ' lOffset     : �Է� ������ ���� Offset ��ġ(0)
    ' *upLevel      : 0x00 ~ 0xFFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdLevelGetExtportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal upLevel As Integer) As Integer

    ' ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� dword ������ ������ ���� Ȯ��
    '==============================================================================================='
    ' lModuleNo   : ��� ��ȣ
    ' lOffset     : �Է� ������ ���� Offset ��ġ(0)
    ' *upLevel      : 0x00 ~ 0x0000FFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    '==============================================================================================='
    Public Declare Function AxdLevelGetExtportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal upLevel As Integer) As Integer

    '========== ��� �Լ� =================================================================================
    ' ������ �Է� ���� ����� Offset ��ġ���� ��ȣ�� Off���� On���� �ٲ������ Ȯ��
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' *upValue   : FALSE(0)
    '            : TRUE(1)
    '==============================================================================================='
    Public Declare Function AxdiIsPulseOn Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' ������ �Է� ���� ����� Offset ��ġ���� ��ȣ�� On���� Off���� �ٲ������ Ȯ��
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' *upValue   : FALSE(0)
    '            : TRUE(1)
    '==============================================================================================='
    Public Declare Function AxdiIsPulseOff Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' ������ �Է� ���� ����� Offset ��ġ���� ��ȣ�� count ��ŭ ȣ��� ���� On ���·� �����ϴ��� Ȯ��
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : �Է� ������ ���� Offset ��ġ
    ' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
    ' *upValue   : FALSE(0)
    '            : TRUE(1)
    ' lStart     : 1(���� ȣ��)
    '            : 0(�ݺ� ȣ��)
    '==============================================================================================='
    Public Declare Function AxdiIsOn Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal lCount As Integer, ByRef upValue As Integer, ByVal lStart As Integer) As Integer

    ' ������ �Է� ���� ����� Offset ��ġ���� ��ȣ�� count ��ŭ ȣ��� ���� Off ���·� �����ϴ��� Ȯ��
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
    ' *upValue   : FALSE(0)
    '            : TRUE(1)
    ' lStart     : 1(���� ȣ��)
    '            : 0(�ݺ� ȣ��)
    '==============================================================================================='
    Public Declare Function AxdiIsOff Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal lCount As Integer, ByRef upValue As Integer, ByVal lStart As Integer) As Integer

    ' ������ ��� ���� ����� Offset ��ġ���� ������ mSec���� On�� �����ϴٰ� Off ��Ŵ
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
    ' lmSec      : 1 ~ 30000
    '==============================================================================================='
    Public Declare Function AxdoOutPulseOn Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal lmSec As Integer) As Integer

    ' ������ ��� ���� ����� Offset ��ġ���� ������ mSec���� Off�� �����ϴٰ� On ��Ŵ
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
    ' lmSec      : 1 ~ 30000
    '==============================================================================================='
    Public Declare Function AxdoOutPulseOff Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal lmSec As Integer) As Integer

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
    '==============================================================================================='
    Public Declare Function AxdoToggleStart Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal lInitState As Integer, ByVal lmSecOn As Integer, ByVal lmSecOff As Integer, ByVal lCount As Integer) As Integer

    ' ������ ��� ���� ����� Offset ��ġ���� ������� ����� ������ ��ȣ ���·� ���� ��Ŵ
    '==============================================================================================='
    ' lModuleNo  : ��� ��ȣ
    ' lOffset    : ��� ������ ���� Offset ��ġ
    ' uOnOff     : Off(0)
    '            : On(1)
    '==============================================================================================='
    Public Declare Function AxdoToggleStop Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uOnOff As Integer) As Integer

    ' ������ ��� ����� Network�� ���� ���� ��� ��� ���¸� ��� Byte ������ �����Ѵ�.
    '==============================================================================================='
    ' lModuleNo   : ��� ��ȣ
    ' dwSize      : ���� �� Byte ��(ex. RTEX-DB32 : 2, RTEX-DO32 : 4)
    ' dwaSetValue : ���� �� ���� ��(Default�� Network ���� ���� �� ���� ����)
    '             : 0 --> Network ���� ���� �� ���� ����
    '             : 1 --> On
    '             : 2 --> Off
    '==============================================================================================='
    Public Declare Function AxdoSetNetworkErrorAct Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dwSize As Integer, ByRef dwaSetValue As Integer) As Integer

    Public Declare Function AxdSetContactNum Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dwInputNum As Integer, ByVal dwOutputNum As Integer) As Integer

    Public Declare Function AxdGetContactNum Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef dwpInputNum As Integer, ByRef dwpOutputNum As Integer) As Integer

End Module
