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

Attribute VB_Name = "AXA"
'========== ���� �� ��� ���� Ȯ�� �Լ� =================================================================================
    'AIO ����� �ִ��� Ȯ���Ѵ�
Public Declare Function AxaInfoIsAIOModule Lib "AXL.dll" (ByRef upStatus As Long) As Long

    'AIO ��� No�� Ȯ���Ѵ�.
Public Declare Function AxaInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef lpModuleNo As Long) As Long

    'AIO ����� ������ Ȯ���Ѵ�.
Public Declare Function AxaInfoGetModuleCount Lib "AXL.dll" (ByRef lpModuleCount As Long) As Long

    '������ ����� �Է� ä�� ���� Ȯ���Ѵ�
Public Declare Function AxaInfoGetInputCount Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpCount As Long) As Long

    '������ ����� ��� ä�� ���� Ȯ���Ѵ�.
Public Declare Function AxaInfoGetOutputCount Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpCount As Long) As Long

    '������ ����� ù ��° ä�� ��ȣ�� Ȯ���Ѵ�. 
Public Declare Function AxaInfoGetChannelNoOfModuleNo Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpChannelNo As Long) As Long

    '������ ����� ù ��° �Է� ä�� ��ȣ�� Ȯ���Ѵ�.(�Է� ���, �Է�/��� ���� ����)
Public Declare Function AxaInfoGetChannelNoAdcOfModuleNo Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpChannelNo As Long) As Long

    '������ ����� ù ��° ��� ä�� ��ȣ�� Ȯ���Ѵ�.(��� ���, �Է�/��� ���� ����)
Public Declare Function AxaInfoGetChannelNoDacOfModuleNo Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpChannelNo As Long) As Long

    '������ ��� ��ȣ�� ���̽� ���� ��ȣ, ��� ��ġ, ��� ID�� Ȯ���Ѵ�.
Public Declare Function AxaInfoGetModule Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpBoardNo As Long, ByRef lpModulePos As Long, ByRef upModuleID As Long) As Long

    ' �ش� ����� ��� ������ �������� ��ȯ�Ѵ�.
Public Declare Function AxaInfoGetModuleStatus Lib "AXL.dll" (ByVal lModuleNo As Long) As Long

'========== �Է� ��� ���� �˻� �Լ� ====================================================================================
    '������ �Է� ä�� ��ȣ�� ��� ��ȣ�� Ȯ���Ѵ�.
Public Declare Function AxaiInfoGetModuleNoOfChannelNo Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef lpModuleNo As Long) As Long

    '�Ƴ��α� �Է� ����� ��ü ä�� ������ Ȯ���Ѵ�.
Public Declare Function AxaiInfoGetChannelCount Lib "AXL.dll" (ByRef lpChannelCount As Long) As Long

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
Public Declare Function AxaiEventSetChannel Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal hWnd As Long, ByVal uMesssage As Long, ByVal pProc As Long, ByRef pEvent As Long) As Long

    '������ �Է� ä�ο� �̺�Ʈ ��� ������ �����Ѵ�.
    '======================================================'
    ' uUse       : DISABLE(0)    ' �̺�Ʈ ����
    '            : ENABLE(1)     ' �̺�Ʈ ����
    '======================================================'
Public Declare Function AxaiEventSetChannelEnable Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal uUse As Long) As Long

    '������ �Է� ä���� �̺�Ʈ ��� ������ Ȯ���Ѵ�.
    '======================================================'
    ' *upUse    : DISABLE(0)    ' �̺�Ʈ ����
    '           : ENABLE(1)     ' �̺�Ʈ ����
    '======================================================'
Public Declare Function AxaiEventGetChannelEnable Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef upUse As Long) As Long

    '������ ���� �Է� ä�ο� �̺�Ʈ ��� ������ �����Ѵ�.
    '======================================================'
    ' lSize          : ��� �� �Է� ä���� ����
    ' lpChannelNo    : ����� ä�� ��ȣ�� �迭
    ' uUse           : DISABLE(0)    ' �̺�Ʈ ����
    '                : ENABLE(1)     ' �̺�Ʈ ����
    '======================================================'
Public Declare Function AxaiEventSetMultiChannelEnable Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByVal uUse As Long) As Long

    '������ �Է� ä�ο� �̺�Ʈ ������ �����Ѵ�.
    '======================================================'
    ' uMask  : DATA_EMPTY(1) --> ���ۿ� �����Ͱ� ���� ��
    '        : DATA_MANY(2)  --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    '        : DATA_SMALL(3) --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    '        : DATA_FULL(4)  --> ���ۿ� �����Ͱ� �� á�� ��
    '======================================================'
Public Declare Function AxaiEventSetChannelMask Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal uMask As Long) As Long

    '������ �Է� ä�ο� �̺�Ʈ ������ Ȯ���Ѵ�.
    '======================================================'
    ' *upMask    : DATA_EMPTY(1) --> ���ۿ� �����Ͱ� ���� ��
    '            : DATA_MANY(2)  --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    '            : DATA_SMALL(3) --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    '            : DATA_FULL(4)  --> ���ۿ� �����Ͱ� �� á�� ��
    '======================================================'
Public Declare Function AxaiEventGetChannelMask Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef upMask As Long) As Long

    '������ ���� �Է� ä�ο� �̺�Ʈ ������ �����Ѵ�.
    '=============================================================================='
    ' lSize       : ��� �� �Է� ä���� ����
    ' lpChannelNo : ����� ä�� ��ȣ�� �迭
    ' uMask       : DATA_EMPTY(1) --> ���ۿ� �����Ͱ� ���� ��
    '             : DATA_MANY(2)  --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    '             : DATA_SMALL(3) --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    '             : DATA_FULL(4)  --> ���ۿ� �����Ͱ� �� á�� ��
    '=============================================================================='
Public Declare Function AxaiEventSetMultiChannelMask Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByVal uMask As Long) As Long

    '�̺�Ʈ �߻� ��ġ�� Ȯ���Ѵ�.
    '=============================================================================='
    ' *upMode    : AIO_EVENT_DATA_UPPER(1) --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    '            : AIO_EVENT_DATA_LOWER(2) --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    '            : AIO_EVENT_DATA_FULL(3)  --> ���ۿ� �����Ͱ� �� á�� ��
    '            : AIO_EVENT_DATA_EMPTY(4) --> ���ۿ� �����Ͱ� ���� ��
    '=============================================================================='
Public Declare Function AxaiEventRead Lib "AXL.dll" (ByRef lpChannelNo As Long, ByRef upMode As Long) As Long

    '������ ����� ���ͷ�Ʈ ����ũ�� �����Ѵ�. 
    '�� �Լ��� ������ ��ȣ���ø� �� ��쿡 �ϵ����(���)�� FIFO ���� ����ڰ� ������ ũ���� ���۷� ���� ���ͷ�Ʈ�� ���� ������ �̵� ������ �����ϱ� ���� ���ȴ�. (SIO-AI4RB�� �������� �ʴ´�.)
    '=================================================================================================='
    ' uMask    : SCAN_END(1)       --> ���õ� ä�� ���  ADC ��ȯ�� �ѹ� �̷�� �� �� ���� ���ͷ�Ʈ�� �߻�
    '          : FIFO_HALF_FULL(2) --> ��⳻�� FIFO�� HALF�̻� á�� ��� ���� ���ͷ�Ʈ �߻�
    '=================================================================================================='
Public Declare Function AxaiInterruptSetModuleMask Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal uMask As Long) As Long

    '������ ����� ���ͷ�Ʈ ����ũ�� Ȯ���Ѵ�.
    '=================================================================================================='
    ' *upMask    : SCAN_END(1)       --> ���õ� ä�� ���  ADC ��ȯ�� �ѹ� �̷�� �� �� ���� ���ͷ�Ʈ�� �߻�
    '            : FIFO_HALF_FULL(2) --> ��⳻�� FIFO�� HALF�̻� á�� ��� ���� ���ͷ�Ʈ �߻�
    '=================================================================================================='
Public Declare Function AxaiInterruptGetModuleMask Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef upMask As Long) As Long

'========== �Է� ��� �Ķ���� ���� �� Ȯ�� �Լ� ========================================================================
    '������ �Է� ä�ο� �Է� ���� ������ �����Ѵ�.
    '=================================================================================================='
    ' AI4RB
    ' dMinVolt    : -10V/-5V/0V�� ���� ����
    ' dMaxVolt    : 10V/5V/�� ���� ����
    '
    ' AI16Hx
    ' dMinVolt    : -10V ����
    ' dMaxVolt    : 10V ����
    '=================================================================================================='
Public Declare Function AxaiSetRange Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dMinVolt As Double, ByVal dMaxVolt As Double) As Long

    '������ �Է� ä���� �Է� ���� ������ Ȯ���Ѵ�.
    '=================================================================================================='
    ' AI4RB
    ' *dpMinVolt    : -10V/-5V/0V�� ���� ����
    ' *dpMaxVolt    : 10V/5V/�� ���� ����
    '
    ' AI16Hx
    ' *dpMaxVolt    : -10V ����
    ' *dpMaxVolt    : 10V ����
    '=================================================================================================='
Public Declare Function AxaiGetRange Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dpMinVolt As Double, ByRef dpMaxVolt As Double) As Long

    '������ ���� �Է� ä�ο� ��� �Է� ���� ������ �����Ѵ�.
    '=================================================================================================='
    ' lSize         : ����� �Է� ä���� ����
    ' *lpChannelNo  : ����� ä�� ��ȣ�� �迭
    '
    ' AI4RB
    ' dMinVolt      : -10V/-5V/0V�� ���� ����
    ' dMaxVolt      : 10V/5V/�� ���� ����
    '
    ' AI16Hx
    ' dMinVolt      : -10V
    ' dMaxVolt      : 10V
    '=================================================================================================='
Public Declare Function AxaiSetMultiRange Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByVal dMinVolt As Double, ByVal dMaxVolt As Double) As Long

    '������ �Է� ��⿡ Ʈ���� ��带 �����Ѵ�.
    '=================================================================================================='
    ' uTriggerMode  : NORMAL_MODE(1)   --> ����ڰ� ���ϴ� ������ A/D��ȯ�ϴ� Software Trigger ��� 
    '               : TIMER_MODE(2)    --> H/W�� ���� Ŭ���� �̿��ؼ� A/D��ȯ�ϴ� Trigger ���
    '               : EXTERNAL_MODE(3) --> �ܺ� �Է´����� Ŭ���� �̿��ؼ� A/D��ȯ�ϴ� Trigger ���
    '=================================================================================================='
Public Declare Function AxaiSetTriggerMode Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal uTriggerMode As Long) As Long

    '������ ��⿡ Ʈ���� ��带 Ȯ���Ѵ�.
    '=================================================================================================='
    ' *upTriggerMode: NORMAL_MODE(1)   --> ����ڰ� ���ϴ� ������ A/D��ȯ�ϴ� Software Trigger ��� 
    '               : TIMER_MODE(2)    --> H/W�� ���� Ŭ���� �̿��ؼ� A/D��ȯ�ϴ� Trigger ���
    '               : EXTERNAL_MODE(3) --> �ܺ� �Է´����� Ŭ���� �̿��ؼ� A/D��ȯ�ϴ� Trigger ���
    '=================================================================================================='
Public Declare Function AxaiGetTriggerMode Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef upTriggerMode As Long) As Long

    '������ �Է¸���� Offset�� mVolt ����(mV)�� �����Ѵ�. �ִ� -100~100mVolt
    '=================================================================================================='
    ' dMiliVolt     : -100 ~ 100 
    '=================================================================================================='
Public Declare Function AxaiSetModuleOffsetValue Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dMiliVolt As Double) As Long

    '������ �Է¸���� Offset ���� Ȯ���Ѵ�. mVolt ����(mV)
    '=================================================================================================='
    ' *dpMiliVolt   : -100 ~ 100 
    '=================================================================================================='
Public Declare Function AxaiGetModuleOffsetValue Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef dpMiliVolt As Double) As Long 

'========== �Է� ��� A/D ��ȯ �Լ� =======================================================================================
    '����ڰ� ������ �Է� ä�ο� �Ƴ��α� �Է� ���� A/D��ȯ�� �� ���� ������ ��ȯ�Ѵ�.�� �Լ��� ����ϱ� ���� AxaiSetTriggerMode �Լ��� ����Ͽ� Normal Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
Public Declare Function AxaiSwReadVoltage Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dpVolt As Double) As Long

    '������ �Է� ä�ο� �Ƴ��α� �Է� ���� Digit ������ ��ȯ�Ѵ�. Normal Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
Public Declare Function AxaiSwReadDigit Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef upDigit As Long) As Long

    '������ ���� �Է� ä�ο� �Ƴ��α� �Է� ���� ���� ������ ��ȯ�Ѵ�. Normal Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
Public Declare Function AxaiSwReadMultiVoltage Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByRef dpVolt As Double) As Long

    '������ ���� �Է� ä�ο� �Ƴ��α� �Է� ���� Digit ������ ��ȯ�Ѵ�. Normal Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
Public Declare Function AxaiSwReadMultiDigit Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByRef upDigit As Long) As Long

    '������ ���� �Է� ä�ο� Immediate��带 ����ϱ� ���� ���� ���� �����Ѵ�. �� �Լ��� ����ϱ� ���� AxaiSetTriggerMode �Լ��� ����Ͽ� Timer Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
Public Declare Function AxaiHwSetMultiAccess Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByRef lpWordSize As Long) As Long

    '������ ������ŭ A/D��ȯ �� ���� ���� ��ȯ�Ѵ�. �� �Լ��� ����ϱ� ���� AxaiHwSetMultiAccess�Լ��� �̿� �������� �����ؾ� �ϸ� , AxaSetTriggerModeAdc �Լ��� ����Ͽ� Timer Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
Public Declare Function AxaiHwStartMultiAccess Lib "AXL.dll" (ByRef dpBuffer As Double) As Long

    '������ ��⿡ ���ø� ������ ���ļ� ����(Hz)�� �����Ѵ�.
    '=================================================================================================='
    ' dSampleFreq    : 10 ~ 100000 
    '=================================================================================================='
Public Declare Function AxaiHwSetSampleFreq Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dSampleFreq As Double) As Long

    '������ ��⿡ ���ø� ������ ���ļ� ����(Hz)�� ������ ���� Ȯ���Ѵ�.
    '=================================================================================================='
    ' *dpSampleFreq  : 10 ~ 100000 
    '=================================================================================================='
Public Declare Function AxaiHwGetSampleFreq Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef dpSampleFreq As Double) As Long

    '������ ��⿡ ���ø� ������ �ð� ����(uSec)�� �����Ѵ�.
    '=================================================================================================='
    ' dSamplePeriod  : 100000 ~ 1000000000
    '=================================================================================================='
Public Declare Function AxaiHwSetSamplePeriod Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dSamplePeriod As Double) As Long

    '������ ��⿡ ���ø� ������ �ð� ����(uSec)�� ������ ���� Ȯ���Ѵ�.
    '=================================================================================================='
    ' *dpSamplePeriod: 100000 ~ 1000000000
    '=================================================================================================='
Public Declare Function AxaiHwGetSamplePeriod Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef dpSamplePeriod As Double) As Long

    '������ �Է� ä�ο� ���۰� Full�� á�� �� ���� ����� �����Ѵ�.
    '=================================================================================================='
    ' uFullMode  : NEW_DATA_KEEP(0)  --> ���ο� ������ ����
    '            : CURR_DATA_KEEP(1) --> ���� ������ ����
    '=================================================================================================='
Public Declare Function AxaiHwSetBufferOverflowMode Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal uFullMode As Long) As Long

    '������ �Է� ä���� ���۰� Full�� á�� �� ���� ����� Ȯ���Ѵ�.
    '=================================================================================================='
    ' *upFullMode: NEW_DATA_KEEP(0)  --> ���ο� ������ ����
    '            : CURR_DATA_KEEP(1) --> ���� ������ ����
    '=================================================================================================='
Public Declare Function AxaiHwGetBufferOverflowMode Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef upFullMode As Long) As Long

    '������ ���� �Է� ä�ο� ���۰� Full�� á�� �� ���� ����� �����Ѵ�.
    '=================================================================================================='
    ' uFullMode  : NEW_DATA_KEEP(0)  --> ���ο� ������ ����
    '            : CURR_DATA_KEEP(1) --> ���� ������ ����
    '=================================================================================================='
Public Declare Function AxaiHwSetMultiBufferOverflowMode Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByVal uFullMode As Long) As Long

    '������ �Է� ä�ο� ������ ���� ���� ���� ���� �����Ѵ�.
Public Declare Function AxaiHwSetLimit Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal lLowLimit As Long, ByVal lUpLimit As Long) As Long

    '������ �Է� ä�ο� ������ ���� ���� ���� ���� Ȯ���Ѵ�.
Public Declare Function AxaiHwGetLimit Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef lpLowLimit As Long, ByRef lpUpLimit As Long) As Long

    '������ ���� �Է� ä�ο� ������ ���� ���� ���� ���� �����Ѵ�.
Public Declare Function AxaiHwSetMultiLimit Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByVal lLowLimit As Long, ByVal lUpLimit As Long) As Long

    '������ ���� �Է� ä�ο� H/WŸ�̸Ӹ� �̿��� A/D��ȯ�� �����Ѵ�.
Public Declare Function AxaiHwStartMultiChannel Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByVal lBuffSize As Long) As Long

    '������ ���� �Է� ä�ο� A/D��ȯ�� ���� �� ������ ������ŭ ���� ó���ؼ� �������� ��ȯ�Ѵ�.
    '=================================================================================================='
    ' lSize         : ����� �Է� ä���� ����
    ' *lpChannelNo  : ����� ä�� ��ȣ�� �迭
    ' lFilterCount  : Filtering�� �������� ����
    ' lBuffSize     : �� ä�ο� �Ҵ�Ǵ� ������ ����
    '=================================================================================================='
Public Declare Function AxaiHwStartMultiFilter Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByVal lFilterCount As Long, ByVal lBuffSize As Long) As Long

    'H/WŸ�̸Ӹ� �̿��� ���� ��ȣ A/D��ȯ�� �����Ѵ�.
Public Declare Function AxaiHwStopMultiChannel Lib "AXL.dll" (ByVal lModuleNo As Long) As Long

    '������ �Է� ä���� �޸� ���ۿ� �����Ͱ� �� ������ �˻��Ѵ�.
Public Declare Function AxaiHwReadDataLength Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef lpDataLength As Long) As Long

    '������ �Է� ä�ο� H/WŸ�̸Ӹ� �̿��Ͽ� A/D��ȯ�� ���� ���� ������ �д´�.
Public Declare Function AxaiHwReadSampleVoltage Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef lpCount As Long, ByRef dpVolt As Double) As Long

    '������ �Է� ä�ο� H/WŸ�̸Ӹ� �̿��Ͽ� A/D��ȯ�� ���� Digit ������ �д´�.
Public Declare Function AxaiHwReadSampleDigit Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef lpCount As Long, ByRef upDigit As Long) As Long


'========== �Է� ��� ���� ���� üũ �Լ� =============================================================
    '������ �Է� ä���� �޸� ���ۿ� �����Ͱ� ���� �� �˻��Ѵ�.
    '=================================================================================================='
    ' *upEmpty  : FALSE(0) --> �޸� ���ۿ� �����Ͱ� ���� ���
    '           : TRUE(1)  --> �޸� ���ۿ� �����Ͱ� ���� ���
    '=================================================================================================='
Public Declare Function AxaiHwIsBufferEmpty Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef upEmpty As Long) As Long

    '������ �Է� ä���� �޸� ���ۿ� �����Ǿ� �ִ� ���� ������ �����Ͱ� ���� �� �˻��Ѵ�
    '=================================================================================================='
    ' *upUpper  : FALSE(0) --> �޸� ���ۿ� �����Ͱ� ���� ������ ���� ���
    '           : TRUE(1)  --> �޸� ���ۿ� �����Ͱ� ���� ������ ���� ���
    '=================================================================================================='
Public Declare Function AxaiHwIsBufferUpper Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef upUpper As Long) As Long

    '������ �Է� ä���� �޸� ���ۿ� �����Ǿ� �ִ� ���� ������ �����Ͱ� ���� �� �˻��Ѵ�.
    '=================================================================================================='
    ' *upLower  : FALSE(0) --> �޸� ���ۿ� �����Ͱ� ���� ������ ���� ���
    '           : TRUE(1)  --> �޸� ���ۿ� �����Ͱ� ���� ������ ���� ���
    '=================================================================================================='
Public Declare Function AxaiHwIsBufferLower Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef upLower As Long) As Long

'==External Trigger Mode �Լ�
    '������ �Է¸���� ���õ� ä�ε��� �ܺ� Ʈ���� ��带 �����Ѵ�.
    '=================================================================================================='
    ' lSize            : ������ �Է� ��⿡�� �ܺ�Ʈ���Ÿ� ��� �� ä�ΰ���
    ' *lpChannelPos    : ������ �Է� ��⿡�� �ܺ�Ʈ���Ÿ� ��� �� ä���� Index
Public Declare Function AxaiExternalStartADC Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lSize As Long, ByRef lpChannelPos As Long) As Long
    '������ �Է¸���� �ܺ�Ʈ���� ��带 �����Ѵ�.  
Public Declare Function AxaiExternalStopADC Lib "AXL.dll" (ByVal lModuleNo As Long) As Long
    '������ �Է¸���� Fifo���¸� ��ȯ�Ѵ�.
    '=================================================================================================='
    ' upStatus         : FIFO_DATA_EXIST(0)
    '                  : FIFO_DATA_EMPTY(1)
    '                  : FIFO_DATA_HALF(2)
    '                  : FIFO_DATA_FULL(6)
    '=================================================================================================='
Public Declare Function AxaiExternalReadFifoStatus Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef upStatus As Long) As Long
    '������ �Է¸���� �ܺν�ȣ�� ���� ��ȯ�� A/D���� �о��.
    ' lSize            : ������ �Է� ��⿡�� ��ȯ�� A/D���� �о�� ä���� ����(AxaiExternalStartADC�� ����� ä�ΰ����� ���� �ؾߵ�)
    ' lpChannelPos     : ������ �Է� ��⿡�� ��ȯ�� A/D���� �о�� ä���� Index(AxaiExternalStartADC�� ����� ä���� Index�� ���� �ؾߵ�)
    ' lDataSize        : �ܺ�Ʈ���ſ� ���� A/D��ȯ�� ���� �ѹ��� �о� �� �ִ� ����Ÿ�� ����
    ' lBuffSize        : �ܺο���(����� Program) �Ҵ��� Data Buffer�� Size
    ' lStartDataPos    : �ܺο���(����� Program) �Ҵ��� Data Buffer�� ���� ���� �� ��ġ 
    ' dpVolt           : A/D��ȯ�� ���� �Ҵ� ���� 2���� �迭 ����Ʈ(dpVlot[Channel][Count])
    ' lpRetDataSize    : A/D��ȯ�� ���� Data Buffer�� ���� �Ҵ�� ����
    ' upStatus         : A/D��ȯ�� ���� Fifo(H/W Buffer)�� ���� ���� �� Fifo���¸� ��ȯ��.
Public Declare Function AxaiExternalReadVoltage Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lSize As Long, ByRef lpChannelPos As Long, ByVal lDataSize As Long, ByVal lBuffSize As Long, ByVal lStartDataPos As Long, ByRef dpVolt As Double, ByRef lpRetDataSize As Long, ByRef upStatus As Long) As Long

'========== ��� ��� ���� �˻� �Լ� ==================================================================
    '������ ��� ä�� ��ȣ�� ��� ��ȣ�� Ȯ���Ѵ�.
Public Declare Function AxaoInfoGetModuleNoOfChannelNo Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef lpModuleNo As Long) As Long

    '�Ƴ��α� ��� ����� ��ü ä�� ������ Ȯ���Ѵ�.
Public Declare Function AxaoInfoGetChannelCount Lib "AXL.dll" (ByRef lpChannelCount As Long) As Long

'========== ��� ��� ���� �� Ȯ�� �Լ� ===============================================================
    '������ ��� ä�ο� ��� ���� ������ �����Ѵ�
    '=================================================================================================='
    ' AO4R, AO2Hx
    ' dMinVolt    : -10V
    ' dMaxVolt    : 10V
    '=================================================================================================='
Public Declare Function AxaoSetRange Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dMinVolt As Double, ByVal dMaxVolt As Double) As Long

    '������ ��� ä���� ��� ���� ������ Ȯ���Ѵ�.
    '=================================================================================================='
    ' AO4R, AO2Hx
    ' dMinVolt    : -10V
    ' dMaxVolt    : 10V
    '=================================================================================================='
Public Declare Function AxaoGetRange Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dpMinVolt As Double, ByRef dpMaxVolt As Double) As Long

    '������ ���� ��� ä�ο� ��� ���� ������ �����Ѵ�.
    '=================================================================================================='
    ' AO4R, AO2Hx
    ' dMinVolt    : -10V
    ' dMaxVolt    : 10V
    '=================================================================================================='
Public Declare Function AxaoSetMultiRange Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByVal dMinVolt As Double, ByVal dMaxVolt As Double) As Long

    '������ ��� ä�ο� �Էµ� ������ ��� �ȴ�.
Public Declare Function AxaoWriteVoltage Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dVolt As Double) As Long

    '������ ���� ��� ä�ο� �Էµ� ������ ��� �ȴ�.
Public Declare Function AxaoWriteMultiVoltage Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByRef dpVolt As Double) As Long

    '������ ��� ä�ο� ��µǴ� ���� ���� Ȯ���Ѵ�.
Public Declare Function AxaoReadVoltage Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dpVolt As Double) As Long

    '������ ���� ��� ä�ο� ��µǴ� ���� ���� Ȯ���Ѵ�.
Public Declare Function AxaoReadMultiVoltage Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByRef dpVolt As Double) As Long
