Option Strict Off
Option Explicit On
Module AXA
    '****************************************************************************
    '*****************************************************************************
    '**
    '** File Name
    '** -----------
    '**
    '** AXA.BAS
    '**
    '** COPYRIGHT (c) AJINEXTEK Co., LTD
    '**
    '*****************************************************************************
    '*****************************************************************************
    '**
    '** Description
    '** -----------
    '** Ajinextek Analog Library Header File
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

    '========== ���� �� ��� ���� Ȯ�� �Լ� =================================================================================
    'AIO ����� �ִ��� Ȯ���Ѵ�
    Public Declare Function AxaInfoIsAIOModule Lib "AXL.dll" (ByRef upStatus As Integer) As Integer

    'AIO ��� No�� Ȯ���Ѵ�.
    Public Declare Function AxaInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByRef lpModuleNo As Integer) As Integer

    'AIO ����� ������ Ȯ���Ѵ�.
    Public Declare Function AxaInfoGetModuleCount Lib "AXL.dll" (ByRef lpModuleCount As Integer) As Integer

    '������ ����� �Է� ä�� ���� Ȯ���Ѵ�
    Public Declare Function AxaInfoGetInputCount Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpCount As Integer) As Integer

    '������ ����� ��� ä�� ���� Ȯ���Ѵ�.
    Public Declare Function AxaInfoGetOutputCount Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpCount As Integer) As Integer

    '������ ����� ù ��° ä�� ��ȣ�� Ȯ���Ѵ�. 
    Public Declare Function AxaInfoGetChannelNoOfModuleNo Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpChannelNo As Integer) As Integer

    '������ ����� ù ��° �Է� ä�� ��ȣ�� Ȯ���Ѵ�.(�Է� ���, �Է�/��� ���� ����)
    Public Declare Function AxaInfoGetChannelNoAdcOfModuleNo Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpChannelNo As Integer) As Integer

    '������ ����� ù ��° ��� ä�� ��ȣ�� Ȯ���Ѵ�.(��� ���, �Է�/��� ���� ����)
    Public Declare Function AxaInfoGetChannelNoDacOfModuleNo Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpChannelNo As Integer) As Integer

    '������ ��� ��ȣ�� ���̽� ���� ��ȣ, ��� ��ġ, ��� ID�� Ȯ���Ѵ�.
    Public Declare Function AxaInfoGetModule Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpBoardNo As Integer, ByRef lpModulePos As Integer, ByRef upModuleID As Integer) As Integer

    ' �ش� ����� ��� ������ �������� ��ȯ�Ѵ�.
    Public Declare Function AxaInfoGetModuleStatus Lib "AXL.dll" (ByVal lModuleNo As Integer) As Integer

    '========== �Է� ��� ���� �˻� �Լ� ====================================================================================
    '������ �Է� ä�� ��ȣ�� ��� ��ȣ�� Ȯ���Ѵ�.
    Public Declare Function AxaiInfoGetModuleNoOfChannelNo Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef lpModuleNo As Integer) As Integer

    '�Ƴ��α� �Է� ����� ��ü ä�� ������ Ȯ���Ѵ�.
    Public Declare Function AxaiInfoGetChannelCount Lib "AXL.dll" (ByRef lpChannelCount As Integer) As Integer

    '========== �Է� ��� ���ͷ�Ʈ/ä�� �̺�Ʈ ���� �� Ȯ�� �Լ� ============================================================
    '������ ä�ο� �̺�Ʈ �޽����� �޾ƿ��� ���Ͽ� ������ �޽���, �ݹ� �Լ� �Ǵ� �̺�Ʈ ����� ����Ѵ�. H/W Ÿ�̸�(Timer Trigger Mode, External Trigger Mode)�� �̿�, ������ ������ ���� ���۽�(AxaiHwStartMultiChannel ����)�� ����Ѵ�.
    ' ������ ��⿡ ���ͷ�Ʈ �޽����� �޾ƿ��� ���Ͽ� ������ �޽���, �ݹ� �Լ� �Ǵ� �̺�Ʈ ����� ���
    '========= ���ͷ�Ʈ ���� �Լ� ======================================================================================
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
    Public Declare Function AxaiEventSetChannel Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal hWnd As Integer, ByVal uMesssage As Integer, ByVal pProc As Integer, ByRef pEvent As Integer) As Integer

    '������ �Է� ä�ο� �̺�Ʈ ��� ������ �����Ѵ�.
    '======================================================'
    ' uUse       : DISABLE(0)    ' �̺�Ʈ ����
    '            : ENABLE(1)     ' �̺�Ʈ ����
    '======================================================'
    Public Declare Function AxaiEventSetChannelEnable Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal uUse As Integer) As Integer

    '������ �Է� ä���� �̺�Ʈ ��� ������ Ȯ���Ѵ�.
    '======================================================'
    ' *upUse     : DISABLE(0)    ' �̺�Ʈ ����
    '            : ENABLE(1)     ' �̺�Ʈ ����
    '======================================================'
    Public Declare Function AxaiEventGetChannelEnable Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef upUse As Integer) As Integer

    '������ ���� �Է� ä�ο� �̺�Ʈ ��� ������ �����Ѵ�.
    '======================================================'
    ' lSize      : ��� �� �Է� ä���� ����
    ' lpChannelNo: ����� ä�� ��ȣ�� �迭
    ' uUse       : DISABLE(0)    ' �̺�Ʈ ����
    '            : ENABLE(1)     ' �̺�Ʈ ����
    '======================================================'
    Public Declare Function AxaiEventSetMultiChannelEnable Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByVal uUse As Integer) As Integer

    '������ �Է� ä�ο� �̺�Ʈ ������ �����Ѵ�.
    '======================================================'
    ' uMask      : DATA_EMPTY(1) --> ���ۿ� �����Ͱ� ���� ��
    '            : DATA_MANY(2)  --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    '            : DATA_SMALL(3) --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    '            : DATA_FULL(4)  --> ���ۿ� �����Ͱ� �� á�� ��
    '======================================================'
    Public Declare Function AxaiEventSetChannelMask Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal uMask As Integer) As Integer

    '������ �Է� ä�ο� �̺�Ʈ ������ Ȯ���Ѵ�.
    '======================================================'
    ' *upMask    : DATA_EMPTY(1) --> ���ۿ� �����Ͱ� ���� ��
    '            : DATA_MANY(2)  --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    '            : DATA_SMALL(3) --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    '            : DATA_FULL(4)  --> ���ۿ� �����Ͱ� �� á�� ��
    '======================================================'
    Public Declare Function AxaiEventGetChannelMask Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef upMask As Integer) As Integer

    '������ ���� �Է� ä�ο� �̺�Ʈ ������ �����Ѵ�.
    '=============================================================================='
    ' lSize      : ��� �� �Է� ä���� ����
    ' lpChannelNo: ����� ä�� ��ȣ�� �迭
    ' uMask      : DATA_EMPTY(1) --> ���ۿ� �����Ͱ� ���� ��
    '            : DATA_MANY(2)  --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    '            : DATA_SMALL(3) --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    '            : DATA_FULL(4)  --> ���ۿ� �����Ͱ� �� á�� ��
    '=============================================================================='
    Public Declare Function AxaiEventSetMultiChannelMask Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByVal uMask As Integer) As Integer

    '�̺�Ʈ �߻� ��ġ�� Ȯ���Ѵ�.
    '=============================================================================='
    ' *upMode    : AIO_EVENT_DATA_UPPER(1) --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    '            : AIO_EVENT_DATA_LOWER(2) --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    '            : AIO_EVENT_DATA_FULL(3)  --> ���ۿ� �����Ͱ� �� á�� ��
    '            : AIO_EVENT_DATA_EMPTY(4) --> ���ۿ� �����Ͱ� ���� ��
    '=============================================================================='
    Public Declare Function AxaiEventRead Lib "AXL.dll" (ByRef lpChannelNo As Integer, ByRef upMode As Integer) As Integer

    '������ ����� ���ͷ�Ʈ ����ũ�� �����Ѵ�. 
    '�� �Լ��� ������ ��ȣ���ø� �� ��쿡 �ϵ����(���)�� FIFO ���� ����ڰ� ������ ũ���� ���۷� ���� ���ͷ�Ʈ�� ���� ������ �̵� ������ �����ϱ� ���� ���ȴ�. (SIO-AI4RB�� �������� �ʴ´�.)
    '=================================================================================================='
    ' uMask      : SCAN_END(1)       --> ���õ� ä�� ���  ADC ��ȯ�� �ѹ� �̷�� �� �� ���� ���ͷ�Ʈ�� �߻�
    '            : FIFO_HALF_FULL(2) --> ��⳻�� FIFO�� HALF�̻� á�� ��� ���� ���ͷ�Ʈ �߻�
    '=================================================================================================='
    Public Declare Function AxaiInterruptSetModuleMask Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal uMask As Integer) As Integer

    '������ ����� ���ͷ�Ʈ ����ũ�� Ȯ���Ѵ�.
    '=================================================================================================='
    ' *upMask    : SCAN_END(1)       --> ���õ� ä�� ���  ADC ��ȯ�� �ѹ� �̷�� �� �� ���� ���ͷ�Ʈ�� �߻�
    '            : FIFO_HALF_FULL(2) --> ��⳻�� FIFO�� HALF�̻� á�� ��� ���� ���ͷ�Ʈ �߻�
    '=================================================================================================='
    Public Declare Function AxaiInterruptGetModuleMask Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef upMask As Integer) As Integer

    '========== �Է� ��� �Ķ���� ���� �� Ȯ�� �Լ� ========================================================================
    '������ �Է� ä�ο� �Է� ���� ������ �����Ѵ�.
    '=================================================================================================='
    ' AI4RB
    ' dMinVolt   : -10V/-5V/0V�� ���� ����
    ' dMaxVolt   : 10V/5V/�� ���� ����
    '
    ' AI16Hx
    ' dMinVolt   : -10V ����
    ' dMaxVolt   : 10V ����
    '=================================================================================================='
    Public Declare Function AxaiSetRange Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dMinVolt As Double, ByVal dMaxVolt As Double) As Integer

    '������ �Է� ä���� �Է� ���� ������ Ȯ���Ѵ�.
    '=================================================================================================='
    ' AI4RB
    ' *dpMinVolt : -10V/-5V/0V�� ���� ����
    ' *dpMaxVolt : 10V/5V/�� ���� ����
    '
    ' AI16Hx
    ' *dpMaxVolt : -10V ����
    ' *dpMaxVolt : 10V ����
    '=================================================================================================='
    Public Declare Function AxaiGetRange Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dpMinVolt As Double, ByRef dpMaxVolt As Double) As Integer

    '������ ���� �Է� ��⿡ ��� �Է� ���� ������ �����Ѵ�.
    '==================================================================================================//
    ' lModuleNo   : ����� �Է� ��� ��ȣ
    '
    ' RTEX AI16F
    ' Mode -5~+5  : dMinVolt = -5, dMaxVolt = +5
    ' Mode -10~+10: dMinVolt = -10, dMaxVolt = +10
    '==================================================================================================//
    Public Declare Function AxaiSetRangeModule Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dMinVolt As Double, ByVal dMaxVolt As Double) As Long

    '������ ���� �Է� ��⿡ ��� �Է� ���� ������ Ȯ���Ѵ�.
    '==================================================================================================//
    ' lModuleNo   : ����� �Է� ��� ��ȣ
    '
    ' RTEX AI16F
    ' *dMinVolt   : -5V, -10V
    ' *dMaxVolt   : +5V, +10V
    '==================================================================================================//
    Public Declare Function AxaiGetRangeModule Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef dMinVolt As Double, ByRef dMaxVolt As Double) As Long

    '������ ���� �Է� ä�ο� ��� �Է� ���� ������ �����Ѵ�.
    '=================================================================================================='
    ' lSize       : ����� �Է� ä���� ����
    ' *lpChannelNo: ����� ä�� ��ȣ�� �迭
    '
    ' AI4RB
    ' dMinVolt    : -10V/-5V/0V�� ���� ����
    ' dMaxVolt    : 10V/5V/�� ���� ����
    '
    ' AI16Hx
    ' dMinVolt    : -10V
    ' dMaxVolt    : 10V
    '=================================================================================================='
    Public Declare Function AxaiSetMultiRange Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByVal dMinVolt As Double, ByVal dMaxVolt As Double) As Integer

    '������ �Է� ��⿡ Ʈ���� ��带 �����Ѵ�.
    '=================================================================================================='
    ' uTriggerMode: NORMAL_MODE(1)   --> ����ڰ� ���ϴ� ������ A/D��ȯ�ϴ� Software Trigger ��� 
    '             : TIMER_MODE(2)    --> H/W�� ���� Ŭ���� �̿��ؼ� A/D��ȯ�ϴ� Trigger ���
    '             : EXTERNAL_MODE(3) --> �ܺ� �Է´����� Ŭ���� �̿��ؼ� A/D��ȯ�ϴ� Trigger ���
    '=================================================================================================='
    Public Declare Function AxaiSetTriggerMode Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal uTriggerMode As Integer) As Integer

    '������ ��⿡ Ʈ���� ��带 Ȯ���Ѵ�.
    '=================================================================================================='
    ' *upTriggerMode : NORMAL_MODE(1)   --> ����ڰ� ���ϴ� ������ A/D��ȯ�ϴ� Software Trigger ��� 
    '                : TIMER_MODE(2)    --> H/W�� ���� Ŭ���� �̿��ؼ� A/D��ȯ�ϴ� Trigger ���
    '                : EXTERNAL_MODE(3) --> �ܺ� �Է´����� Ŭ���� �̿��ؼ� A/D��ȯ�ϴ� Trigger ���
    '=================================================================================================='
    Public Declare Function AxaiGetTriggerMode Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef upTriggerMode As Integer) As Integer

    '������ �Է¸���� Offset�� mVolt ����(mV)�� �����Ѵ�. �ִ� -100~100mVolt
    '=================================================================================================='
    ' dMiliVolt    : -100 ~ 100 
    '=================================================================================================='
    Public Declare Function AxaiSetModuleOffsetValue Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dMiliVolt As Double) As Integer

    '������ �Է¸���� Offset ���� Ȯ���Ѵ�. mVolt ����(mV)
    '=================================================================================================='
    ' *dpMiliVolt  : -100 ~ 100 
    '=================================================================================================='
    Public Declare Function AxaiGetModuleOffsetValue Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef dpMiliVolt As Double) As Integer

    '========== �Է� ��� A/D ��ȯ �Լ� =======================================================================================
    '����ڰ� ������ �Է� ä�ο� �Ƴ��α� �Է� ���� A/D��ȯ�� �� ���� ������ ��ȯ�Ѵ�.�� �Լ��� ����ϱ� ���� AxaiSetTriggerMode �Լ��� ����Ͽ� Normal Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
    Public Declare Function AxaiSwReadVoltage Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dpVolt As Double) As Integer

    '������ �Է� ä�ο� �Ƴ��α� �Է� ���� Digit ������ ��ȯ�Ѵ�. Normal Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
    Public Declare Function AxaiSwReadDigit Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef upDigit As Integer) As Integer

    '������ ���� �Է� ä�ο� �Ƴ��α� �Է� ���� ���� ������ ��ȯ�Ѵ�. Normal Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
    Public Declare Function AxaiSwReadMultiVoltage Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByRef dpVolt As Double) As Integer

    '������ ���� �Է� ä�ο� �Ƴ��α� �Է� ���� Digit ������ ��ȯ�Ѵ�. Normal Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
    Public Declare Function AxaiSwReadMultiDigit Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByRef upDigit As Integer) As Integer

    '������ ���� �Է� ä�ο� Immediate��带 ����ϱ� ���� ���� ���� �����Ѵ�. �� �Լ��� ����ϱ� ���� AxaiSetTriggerMode �Լ��� ����Ͽ� Timer Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
    Public Declare Function AxaiHwSetMultiAccess Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByRef lpWordSize As Integer) As Integer

    '������ ������ŭ A/D��ȯ �� ���� ���� ��ȯ�Ѵ�. �� �Լ��� ����ϱ� ���� AxaiHwSetMultiAccess�Լ��� �̿� �������� �����ؾ� �ϸ� , AxaSetTriggerModeAdc �Լ��� ����Ͽ� Timer Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
    Public Declare Function AxaiHwStartMultiAccess Lib "AXL.dll" (ByRef dpBuffer As Double) As Integer

    '������ ��⿡ ���ø� ������ ���ļ� ����(Hz)�� �����Ѵ�.
    '=================================================================================================='
    ' dSampleFreq    : 10 ~ 100000 
    '=================================================================================================='
    Public Declare Function AxaiHwSetSampleFreq Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dSampleFreq As Double) As Integer

    '������ ��⿡ ���ø� ������ ���ļ� ����(Hz)�� ������ ���� Ȯ���Ѵ�.
    '=================================================================================================='
    ' *dpSampleFreq  : 10 ~ 100000 
    '=================================================================================================='
    Public Declare Function AxaiHwGetSampleFreq Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef dpSampleFreq As Double) As Integer

    '������ ��⿡ ���ø� ������ �ð� ����(uSec)�� �����Ѵ�.
    '=================================================================================================='
    ' dSamplePeriod  : 100000 ~ 1000000000
    '=================================================================================================='
    Public Declare Function AxaiHwSetSamplePeriod Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dSamplePeriod As Double) As Integer

    '������ ��⿡ ���ø� ������ �ð� ����(uSec)�� ������ ���� Ȯ���Ѵ�.
    '=================================================================================================='
    ' *dpSamplePeriod: 100000 ~ 1000000000
    '=================================================================================================='
    Public Declare Function AxaiHwGetSamplePeriod Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef dpSamplePeriod As Double) As Integer

    '������ �Է� ä�ο� ���۰� Full�� á�� �� ���� ����� �����Ѵ�.
    '=================================================================================================='
    ' uFullMode  : NEW_DATA_KEEP(0)  --> ���ο� ������ ����
    '            : CURR_DATA_KEEP(1) --> ���� ������ ����
    '=================================================================================================='
    Public Declare Function AxaiHwSetBufferOverflowMode Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal uFullMode As Integer) As Integer

    '������ �Է� ä���� ���۰� Full�� á�� �� ���� ����� Ȯ���Ѵ�.
    '=================================================================================================='
    ' *upFullMode : NEW_DATA_KEEP(0)  --> ���ο� ������ ����
    '             : CURR_DATA_KEEP(1) --> ���� ������ ����
    '=================================================================================================='
    Public Declare Function AxaiHwGetBufferOverflowMode Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef upFullMode As Integer) As Integer

    '������ ���� �Է� ä�ο� ���۰� Full�� á�� �� ���� ����� �����Ѵ�.
    '=================================================================================================='
    ' uFullMode   : NEW_DATA_KEEP(0) --> ���ο� ������ ����
    '             : CURR_DATA_KEEP(1) --> ���� ������ ����
    '=================================================================================================='
    Public Declare Function AxaiHwSetMultiBufferOverflowMode Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByVal uFullMode As Integer) As Integer

    '������ �Է� ä�ο� ������ ���� ���� ���� ���� �����Ѵ�.
    Public Declare Function AxaiHwSetLimit Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal lLowLimit As Integer, ByVal lUpLimit As Integer) As Integer

    '������ �Է� ä�ο� ������ ���� ���� ���� ���� Ȯ���Ѵ�.
    Public Declare Function AxaiHwGetLimit Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef lpLowLimit As Integer, ByRef lpUpLimit As Integer) As Integer

    '������ ���� �Է� ä�ο� ������ ���� ���� ���� ���� �����Ѵ�.
    Public Declare Function AxaiHwSetMultiLimit Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByVal lLowLimit As Integer, ByVal lUpLimit As Integer) As Integer

    '������ ���� �Է� ä�ο� H/WŸ�̸Ӹ� �̿��� A/D��ȯ�� �����Ѵ�.
    Public Declare Function AxaiHwStartMultiChannel Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByVal lBuffSize As Integer) As Integer

    '������ ���� �Է� ä�ο� A/D��ȯ�� ���� �� ������ ������ŭ ���� ó���ؼ� �������� ��ȯ�Ѵ�.
    '=================================================================================================='
    ' lSize       : ����� �Է� ä���� ����
    ' *lpChannelNo: ����� ä�� ��ȣ�� �迭
    ' lFilterCount: Filtering�� �������� ����
    ' lBuffSize   : �� ä�ο� �Ҵ�Ǵ� ������ ����
    '=================================================================================================='
    Public Declare Function AxaiHwStartMultiFilter Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByVal lFilterCount As Integer, ByVal lBuffSize As Integer) As Integer

    'H/WŸ�̸Ӹ� �̿��� ���� ��ȣ A/D��ȯ�� �����Ѵ�.
    Public Declare Function AxaiHwStopMultiChannel Lib "AXL.dll" (ByVal lModuleNo As Integer) As Integer

    '������ �Է� ä���� �޸� ���ۿ� �����Ͱ� �� ������ �˻��Ѵ�.
    Public Declare Function AxaiHwReadDataLength Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef lpDataLength As Integer) As Integer

    '������ �Է� ä�ο� H/WŸ�̸Ӹ� �̿��Ͽ� A/D��ȯ�� ���� ���� ������ �д´�.
    Public Declare Function AxaiHwReadSampleVoltage Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef lpCount As Integer, ByRef dpVolt As Double) As Integer

    '������ �Է� ä�ο� H/WŸ�̸Ӹ� �̿��Ͽ� A/D��ȯ�� ���� Digit ������ �д´�.
    Public Declare Function AxaiHwReadSampleDigit Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef lpCount As Integer, ByRef upDigit As Integer) As Integer


    '========== �Է� ��� ���� ���� üũ �Լ� ===================================================================================
    '������ �Է� ä���� �޸� ���ۿ� �����Ͱ� ���� �� �˻��Ѵ�.
    '=================================================================================================='
    ' *upEmpty  : FALSE(0) --> �޸� ���ۿ� �����Ͱ� ���� ���
    '           : TRUE(1)  --> �޸� ���ۿ� �����Ͱ� ���� ���
    '=================================================================================================='
    Public Declare Function AxaiHwIsBufferEmpty Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef upEmpty As Integer) As Integer

    '������ �Է� ä���� �޸� ���ۿ� �����Ǿ� �ִ� ���� ������ �����Ͱ� ���� �� �˻��Ѵ�
    '=================================================================================================='
    ' *upUpper  : FALSE(0) --> �޸� ���ۿ� �����Ͱ� ���� ������ ���� ���
    '           : TRUE(1)  --> �޸� ���ۿ� �����Ͱ� ���� ������ ���� ���
    '=================================================================================================='
    Public Declare Function AxaiHwIsBufferUpper Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef upUpper As Integer) As Integer

    '������ �Է� ä���� �޸� ���ۿ� �����Ǿ� �ִ� ���� ������ �����Ͱ� ���� �� �˻��Ѵ�.
    '=================================================================================================='
    ' *upLower  : FALSE(0) --> �޸� ���ۿ� �����Ͱ� ���� ������ ���� ���
    '           : TRUE(1)  --> �޸� ���ۿ� �����Ͱ� ���� ������ ���� ���
    '=================================================================================================='
    Public Declare Function AxaiHwIsBufferLower Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef upLower As Integer) As Integer

    '==External Trigger Mode �Լ�
    '������ �Է¸���� ���õ� ä�ε��� �ܺ� Ʈ���� ��带 �����Ѵ�.
    '=================================================================================================='
    ' lSize            : ������ �Է� ��⿡�� �ܺ�Ʈ���Ÿ� ��� �� ä�ΰ���
    ' *lpChannelPos    : ������ �Է� ��⿡�� �ܺ�Ʈ���Ÿ� ��� �� ä���� Index
    Public Declare Function AxaiExternalStartADC Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lSize As Integer, ByRef lpChannelPos As Integer) As Integer
    '������ �Է¸���� �ܺ�Ʈ���� ��带 �����Ѵ�.  
    Public Declare Function AxaiExternalStopADC Lib "AXL.dll" (ByVal lModuleNo As Integer) As Integer
    '������ �Է¸���� Fifo���¸� ��ȯ�Ѵ�.
    '=================================================================================================='
    ' upStatus         : FIFO_DATA_EXIST(0)
    '                  : FIFO_DATA_EMPTY(1)
    '                  : FIFO_DATA_HALF(2)
    '                  : FIFO_DATA_FULL(6)
    '=================================================================================================='
    Public Declare Function AxaiExternalReadFifoStatus Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef upStatus As Integer) As Integer
    '������ �Է¸���� �ܺν�ȣ�� ���� ��ȯ�� A/D���� �о��.
    ' lSize            : ������ �Է� ��⿡�� ��ȯ�� A/D���� �о�� ä���� ����(AxaiExternalStartADC�� ����� ä�ΰ����� ���� �ؾߵ�)
    ' lpChannelPos     : ������ �Է� ��⿡�� ��ȯ�� A/D���� �о�� ä���� Index(AxaiExternalStartADC�� ����� ä���� Index�� ���� �ؾߵ�)
    ' lDataSize        : �ܺ�Ʈ���ſ� ���� A/D��ȯ�� ���� �ѹ��� �о� �� �ִ� ����Ÿ�� ����
    ' lBuffSize        : �ܺο���(����� Program) �Ҵ��� Data Buffer�� Size
    ' lStartDataPos    : �ܺο���(����� Program) �Ҵ��� Data Buffer�� ���� ���� �� ��ġ 
    ' dpVolt           : A/D��ȯ�� ���� �Ҵ� ���� 2���� �迭 ����Ʈ(dpVlot[Channel][Count])
    ' lpRetDataSize    : A/D��ȯ�� ���� Data Buffer�� ���� �Ҵ�� ����
    ' upStatus         : A/D��ȯ�� ���� Fifo(H/W Buffer)�� ���� ���� �� Fifo���¸� ��ȯ��.
    Public Declare Function AxaiExternalReadVoltage Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lSize As Integer, ByRef lpChannelPos As Integer, ByVal lDataSize As Integer, ByVal lBuffSize As Integer, ByVal lStartDataPos As Integer, ByRef dpVolt As Double, ByRef lpRetDataSize As Integer, ByRef upStatus As Integer) As Integer

    '========== ��� ��� ���� �˻� �Լ� ========================================================================================
    '������ ��� ä�� ��ȣ�� ��� ��ȣ�� Ȯ���Ѵ�.
    Public Declare Function AxaoInfoGetModuleNoOfChannelNo Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef lpModuleNo As Integer) As Integer

    '�Ƴ��α� ��� ����� ��ü ä�� ������ Ȯ���Ѵ�.
    Public Declare Function AxaoInfoGetChannelCount Lib "AXL.dll" (ByRef lpChannelCount As Integer) As Integer

    '========== ��� ��� ���� �� Ȯ�� �Լ� ========================================================================================
    '������ ��� ä�ο� ��� ���� ������ �����Ѵ�
    '=================================================================================================='
    ' AO4R, AO2Hx
    ' dMinVolt    : -10V
    ' dMaxVolt    : 10V
    '=================================================================================================='
    Public Declare Function AxaoSetRange Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dMinVolt As Double, ByVal dMaxVolt As Double) As Integer

    '������ ��� ä���� ��� ���� ������ Ȯ���Ѵ�.
    '=================================================================================================='
    ' AO4R, AO2Hx
    ' dMinVolt    : -10V
    ' dMaxVolt    : 10V
    '=================================================================================================='
    Public Declare Function AxaoGetRange Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dpMinVolt As Double, ByRef dpMaxVolt As Double) As Integer

    '������ ���� ��� ä�ο� ��� ���� ������ �����Ѵ�.
    '=================================================================================================='
    ' AO4R, AO2Hx
    ' dMinVolt    : -10V
    ' dMaxVolt    : 10V
    '=================================================================================================='
    Public Declare Function AxaoSetMultiRange Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByVal dMinVolt As Double, ByVal dMaxVolt As Double) As Integer

    '������ ��� ä�ο� �Էµ� ������ ��� �ȴ�.
    Public Declare Function AxaoWriteVoltage Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dVolt As Double) As Integer

    '������ ���� ��� ä�ο� �Էµ� ������ ��� �ȴ�.
    Public Declare Function AxaoWriteMultiVoltage Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByRef dpVolt As Double) As Integer

    '������ ��� ä�ο� ��µǴ� ���� ���� Ȯ���Ѵ�.
    Public Declare Function AxaoReadVoltage Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dpVolt As Double) As Integer

    '������ ���� ��� ä�ο� ��µǴ� ���� ���� Ȯ���Ѵ�.
    Public Declare Function AxaoReadMultiVoltage Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByRef dpVolt As Double) As Integer
End Module
