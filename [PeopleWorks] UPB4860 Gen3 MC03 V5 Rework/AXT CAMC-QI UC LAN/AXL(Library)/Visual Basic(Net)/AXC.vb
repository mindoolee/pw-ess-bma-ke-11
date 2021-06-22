Option Strict Off
Option Explicit On
Module AXC
    '****************************************************************************
    '*****************************************************************************
    '**
    '** File Name
    '** -----------
    '**
    '** AXC.vb
    '**
    '** COPYRIGHT (c) AJINEXTEK Co., LTD
    '**
    '*****************************************************************************
    '*****************************************************************************
    '**
    '** Description
    '** -----------
    '** Ajinextek Counter Library Header File
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
    '//========== ���� �� ��� ���� 
    '// CNT ����� �ִ��� Ȯ��
    Public Declare Function AxcInfoIsCNTModule Lib "AXL.dll" (ByRef upStatus As Integer) As Integer

    '// CNT ��� No Ȯ��
    Public Declare Function AxcInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByRef lpModuleNo As Integer) As Integer

    '// CNT ����� ����� ���� Ȯ��
    Public Declare Function AxcInfoGetModuleCount Lib "AXL.dll" (ByRef lpModuleCount As Integer) As Integer

    '// ������ ����� ī���� �Է� ä�� ���� Ȯ��
    Public Declare Function AxcInfoGetChannelCount Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpCount As Integer) As Integer

    '// �ý��ۿ� ������ ī������ �� ä�� ���� Ȯ��
    Public Declare Function AxcInfoGetTotalChannelCount Lib "AXL.dll" (ByRef lpChannelCount As Integer) As Integer

    '// ������ ��� ��ȣ�� ���̽� ���� ��ȣ, ��� ��ġ, ��� ID Ȯ��
    Public Declare Function AxcInfoGetModule Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpBoardNo As Integer, ByRef lpModulePos As Integer, ByRef upModuleID As Integer) As Integer

    '// �ش� ����� ��� ������ �������� ��ȯ�Ѵ�.
    Public Declare Function AxcInfoGetModuleStatus Lib "AXL.dll" (ByVal lModuleNo As Integer) As Integer

    Public Declare Function AxcInfoGetFirstChannelNoOfModuleNo Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpChannelNo As Integer) As Integer

    '// ī���� ����� Encoder �Է� ����� ���� �մϴ�.
    '// dwMethod --> 0x00 : Sign and pulse, x1 multiplication
    '// dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
    '// dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
    '// dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
    '// dwMethod --> 0x08 : Sign and pulse, x2 multiplication
    '// dwMethod --> 0x09 : Increment and decrement pulses, x1 multiplication
    '// dwMethod --> 0x0A : Increment and decrement pulses, x2 multiplication
    '// SIO-CN2CH�� ���
    '// dwMethod --> 0x00 : Up/Down ���, A phase : �޽�, B phase : ����
    '// dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
    '// dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
    '// dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
    Public Declare Function AxcSignalSetEncInputMethod Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwMethod As Integer) As Integer

    '// ī���� ����� Encoder �Է� ����� ���� �մϴ�.
    '// *dwpUpMethod --> 0x00 : Sign and pulse, x1 multiplication
    '// *dwpUpMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
    '// *dwpUpMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
    '// *dwpUpMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
    '// *dwpUpMethod --> 0x08 : Sign and pulse, x2 multiplication
    '// *dwpUpMethod --> 0x09 : Increment and decrement pulses, x1 multiplication
    '// *dwpUpMethod --> 0x0A : Increment and decrement pulses, x2 multiplication
    '// SIO-CN2CH�� ���
    '// dwMethod --> 0x00 : Up/Down ���, A phase : �޽�, B phase : ����
    '// dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
    '// dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
    '// dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
    Public Declare Function AxcSignalGetEncInputMethod Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpUpMethod As Integer) As Integer

    '// ī���� ����� Ʈ���Ÿ� ���� �մϴ�.
    '// dwMode -->  0x00 : Latch
    '// dwMode -->  0x01 : State
    '// dwMode -->  0x02 : Special State    --> SIO-CN2CH ����
    '// SIO-CN2CH�� ���
    '// dwMode -->  0x00 : ���� ��ġ Ʈ���� �Ǵ� �ֱ� ��ġ Ʈ����.
    '// ���� : ��ǰ���� ����� ���� �ٸ��� ������ �����Ͽ� ��� �ʿ�.
    '// dwMode -->  0x01 : �ð� �ֱ� Ʈ����(AxcTriggerSetFreq�� ����)
    Public Declare Function AxcTriggerSetFunction Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwMode As Integer) As Integer

    '// ī���� ����� Ʈ���� ������ Ȯ�� �մϴ�.
    '// *dwMode -->  0x00 : Latch
    '// *dwMode -->  0x01 : State
    '// *dwMode -->  0x02 : Special State
    '// dwMode -->  0x00 : ���� ��ġ Ʈ���� �Ǵ� �ֱ� ��ġ Ʈ����.
    '// ���� : ��ǰ���� ����� ���� �ٸ��� ������ �����Ͽ� ��� �ʿ�.
    '// dwMode -->  0x01 : �ð� �ֱ� Ʈ����(AxcTriggerSetFreq�� ����)
    Public Declare Function AxcTriggerGetFunction Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpMode As Integer) As Integer

    '// dwUsage --> 0x00 : Trigger Not use
    '// dwUsage --> 0x01 : Trigger use
    Public Declare Function AxcTriggerSetNotchEnable Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwUsage As Integer) As Integer

    '// *dwUsage --> 0x00 : Trigger Not use
    '// *dwUsage --> 0x01 : Trigger use
    Public Declare Function AxcTriggerGetNotchEnable Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpUsage As Integer) As Integer


    '// ī���� ����� Captuer �ؼ��� ���� �մϴ�.(External latch input polarity)
    '// dwCapturePol --> 0x00 : Signal OFF -> ON
    '// dwCapturePol --> 0x01 : Signal ON -> OFF
    Public Declare Function AxcSignalSetCaptureFunction Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwCapturePol As Integer) As Integer

    '// ī���� ����� Captuer �ؼ� ������ Ȯ�� �մϴ�.(External latch input polarity)
    '// *dwCapturePol --> 0x00 : Signal OFF -> ON
    '// *dwCapturePol --> 0x01 : Signal ON -> OFF
    Public Declare Function AxcSignalGetCaptureFunction Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpCapturePol As Integer) As Integer

    '// ī���� ����� Captuer ��ġ�� Ȯ�� �մϴ�.(External latch)
    '// *dbpCapturePos --> Capture position ��ġ
    Public Declare Function AxcSignalGetCapturePos Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dbpCapturePos As Double) As Integer

    '// ī���� ����� ī���� ���� Ȯ�� �մϴ�.
    '// *dbpActPos --> ī���� ��
    Public Declare Function AxcStatusGetActPos Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dbpActPos As Double) As Integer

    '// ī���� ����� ī���� ���� dbActPos ������ ���� �մϴ�.
    Public Declare Function AxcStatusSetActPos Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dbActPos As Double) As Integer

    '// ī���� ����� Ʈ���� ��ġ�� �����մϴ�.
    '// ī���� ����� Ʈ���� ��ġ�� 2�������� ���� �� �� �ֽ��ϴ�.
    Public Declare Function AxcTriggerSetNotchPos Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dbLowerPos As Double, ByVal dbUpperPos As Double) As Integer

    '// ī���� ����� ������ Ʈ���� ��ġ�� Ȯ�� �մϴ�.
    Public Declare Function AxcTriggerGetNotchPos Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dbpLowerPos As Double, ByRef dbpUpperPos As Double) As Integer

    '// ī���� ����� Ʈ���� ����� ������ �մϴ�.
    '// dwOutVal --> 0x00 : Ʈ���� ��� '0'
    '// dwOutVal --> 0x01 : Ʈ���� ��� '1'
    Public Declare Function AxcTriggerSetOutput Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwOutVal As Integer) As Integer

    '// ī���� ����� ���¸� Ȯ���մϴ�.
    '// Bit '0' : Carry (ī���� ����ġ�� ���� �޽��� ���� ī���� ����ġ�� �Ѿ� 0�� �ٲ���� �� 1��ĵ�� ON���� �մϴ�.)
    '// Bit '1' : Borrow (ī���� ����ġ�� ���� �޽��� ���� 0�� �Ѿ� ī���� ����ġ�� �ٲ���� �� 1��ĵ�� ON���� �մϴ�.)
    '// Bit '2' : Trigger output status
    '// Bit '3' : Latch input status
    Public Declare Function AxcStatusGetChannel Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpChannelStatus As Integer) As Integer


    '// SIO-CN2CH ���� �Լ���
    '//
    '// ī���� ����� ��ġ ������ �����Ѵ�.
    '// ���� ��ġ �̵����� ���� �޽� ������ �����ϴµ�,
    '// ex) 1mm �̵��� 1000�� �ʿ��ϴٸ�dMoveUnitPerPulse = 0.001�� �Է��ϰ�,
    '//     ���� ��� �Լ��� ��ġ�� ���õ� ���� mm ������ �����ϸ� �ȴ�.
    Public Declare Function AxcMotSetMoveUnitPerPulse Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dMoveUnitPerPulse As Double) As Integer

    '// ī���� ����� ��ġ ������ Ȯ���Ѵ�.
    Public Declare Function AxcMotGetMoveUnitPerPulse Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dpMoveUnitPerPuls As Double) As Integer

    '// ī���� ����� ���ڴ� �Է� ī���͸� ���� ����� �����Ѵ�.
    '// dwReverse --> 0x00 : �������� ����.
    '// dwReverse --> 0x01 : ����.
    Public Declare Function AxcSignalSetEncReverse Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwReverse As Integer) As Integer

    '// ī���� ����� ���ڴ� �Է� ī���͸� ���� ����� ������ Ȯ���Ѵ�.
    Public Declare Function AxcSignalGetEncReverse Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpReverse As Integer) As Integer

    '// ī���� ����� Encoder �Է� ��ȣ�� �����Ѵ�.
    '// dwSource -->  0x00 : 2(A/B)-Phase ��ȣ.
    '// dwSource -->  0x01 : Z-Phase ��ȣ.(���⼺ ����.)
    Public Declare Function AxcSignalSetEncSource Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwSource As Integer) As Integer

    '// ī���� ����� Encoder �Է� ��ȣ ���� ������ Ȯ���Ѵ�.
    Public Declare Function AxcSignalGetEncSource Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpSource As Integer) As Integer

    '// ī���� ����� Ʈ���� ��� ���� �� ���� ���� �����Ѵ�.
    '// ��ġ �ֱ� Ʈ���� ��ǰ�� ��� ��ġ �ֱ�� Ʈ���� ����� �߻���ų ���� �� ���� ���� �����Ѵ�.
    '// ���� ��ġ Ʈ���� ��ǰ�� ��� Ram ���� ������ Ʈ���� ������ ���� ���� ��ġ�� �����Ѵ�.
    '// ���� : AxcMotSetMoveUnitPerPulse�� ������ ����.
    '// Note : ���Ѱ��� ���Ѱ����� �������� �����Ͽ��� �մϴ�.
    Public Declare Function AxcTriggerSetBlockLowerPos Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dLowerPosition As Double) As Integer

    '// ī���� ����� Ʈ���� ��� ���� �� ���� ���� Ȯ���Ѵ�.
    Public Declare Function AxcTriggerGetBlockLowerPos Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dpLowerPosition As Double) As Integer

    '// ī���� ����� Ʈ���� ��� ���� �� ���� ���� �����Ѵ�.
    '// ��ġ �ֱ� Ʈ���� ��ǰ�� ��� ��ġ �ֱ�� Ʈ���� ����� �߻���ų ���� �� ���� ���� �����Ѵ�.
    '// ���� ��ġ Ʈ���� ��ǰ�� ��� Ʈ���� ������ ������ Ram �� ������ ������ Ʈ���� ������ ����Ǵ� ��ġ�� ���ȴ�.
    '// ���� : AxcMotSetMoveUnitPerPulse�� ������ ����.
    '// Note : ���Ѱ��� ���Ѱ����� ū���� �����Ͽ��� �մϴ�.
    Public Declare Function AxcTriggerSetBlockUpperPos Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dUpperPosition As Double) As Integer
    '// ī���� ����� Ʈ���� ��� ���� �� ���� ���� �����Ѵ�.
    Public Declare Function AxcTriggerGetBlockUpperPos Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dpUpperrPosition As Double) As Integer

    '// ī���� ����� ��ġ �ֱ� ��� Ʈ���ſ� ���Ǵ� ��ġ �ֱ⸦ �����Ѵ�.
    '// ���� : AxcMotSetMoveUnitPerPulse�� ������ ����.
    Public Declare Function AxcTriggerSetPosPeriod Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dPeriod As Double) As Integer

    '// ī���� ����� ��ġ �ֱ� ��� Ʈ���ſ� ���Ǵ� ��ġ �ֱ⸦ Ȯ���Ѵ�.
    Public Declare Function AxcTriggerGetPosPeriod Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dpPeriod As Double) As Integer

    '// ī���� ����� ��ġ �ֱ� ��� Ʈ���� ���� ��ġ ������ ���� ��ȿ����� �����Ѵ�.
    '// dwDirection -->  0x00 : ī������ ��/���� ���Ͽ� Ʈ���� �ֱ� ���� ���.
    '// dwDirection -->  0x01 : ī���Ͱ� ���� �Ҷ��� Ʈ���� �ֱ� ���� ���.
    '// dwDirection -->  0x01 : ī���Ͱ� ���� �Ҷ��� Ʈ���� �ֱ� ���� ���.
    Public Declare Function AxcTriggerSetDirectionCheck Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwDirection As Integer) As Integer
    '// ī���� ����� ��ġ �ֱ� ��� Ʈ���� ���� ��ġ ������ ���� ��ȿ��� ������ Ȯ���Ѵ�.
    Public Declare Function AxcTriggerGetDirectionCheck Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpDirection As Integer) As Integer

    '// ī���� ����� ��ġ �ֱ� ��� Ʈ���� ����� ����, ��ġ �ֱ⸦ �ѹ��� �����Ѵ�.
    '// ��ġ ���� ���� :  AxcMotSetMoveUnitPerPulse�� ������ ����.
    Public Declare Function AxcTriggerSetBlock Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dLower As Double, ByVal dUpper As Double, ByVal dABSod As Double) As Integer

    '// ī���� ����� ��ġ �ֱ� ��� Ʈ���� ����� ����, ��ġ �ֱ⸦ ������ �ѹ��� Ȯ���Ѵ�.
    Public Declare Function AxcTriggerGetBlock Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dpLower As Double, ByRef dpUpper As Double, ByRef dpABSod As Double) As Integer

    '// ī���� ����� Ʈ���� ��� �޽� ���� �����Ѵ�.
    '// ���� : uSec
    Public Declare Function AxcTriggerSetTime Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dTrigTime As Double) As Integer

    '// ī���� ����� Ʈ���� ��� �޽� �� ������ Ȯ���Ѵ�.
    Public Declare Function AxcTriggerGetTime Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dpTrigTime As Double) As Integer

    '// ī���� ����� Ʈ���� ��� �޽��� ��� ������ �����Ѵ�.
    '// dwLevel -->  0x00 : Ʈ���� ��½� 'Low' ���� ���.
    '// dwLevel -->  0x00 : Ʈ���� ��½� 'High' ���� ���.
    Public Declare Function AxcTriggerSetLevel Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwLevel As Integer) As Integer
    '// ī���� ����� Ʈ���� ��� �޽��� ��� ���� ������ Ȯ���Ѵ�.
    Public Declare Function AxcTriggerGetLevel Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpLevel As Integer) As Integer

    '// ī���� ����� ���ļ� Ʈ���� ��� ��ɿ� �ʿ��� ���ļ��� �����Ѵ�.
    '// ���� : Hz, ���� : 1Hz ~ 500 kHz
    Public Declare Function AxcTriggerSetFreq Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwFreqency As Integer) As Integer
    '// ī���� ����� ���ļ� Ʈ���� ��� ��ɿ� �ʿ��� ���ļ��� ������ Ȯ���Ѵ�.
    Public Declare Function AxcTriggerGetFreq Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpFreqency As Integer) As Integer

    '// ī���� ����� ���� ä�ο� ���� ���� ��� ���� �����Ѵ�.
    '// dwOutput ���� : 0x00 ~ 0x0F, �� ä�δ� 4���� ���� ���
    Public Declare Function AxcSignalWriteOutput Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwOutput As Integer) As Integer

    '// ī���� ����� ���� ä�ο� ���� ���� ��� ���� Ȯ���Ѵ�.
    Public Declare Function AxcSignalReadOutput Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpOutput As Integer) As Integer

    '// ī���� ����� ���� ä�ο� ���� ���� ��� ���� ��Ʈ ���� �����Ѵ�.
    '// lBitNo ���� : 0 ~ 3, �� ä�δ� 4���� ���� ���
    Public Declare Function AxcSignalWriteOutputBit Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal lBitNo As Integer, ByVal uOnOff As Integer) As Integer
    '// ī���� ����� ���� ä�ο� ���� ���� ��� ���� ��Ʈ ���� Ȯ�� �Ѵ�.
    '// lBitNo ���� : 0 ~ 3
    Public Declare Function AxcSignalReadOutputBit Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal lBitNo As Integer, ByRef upOnOff As Integer) As Integer

    '// ī���� ����� ���� ä�ο� ���� ���� �Է� ���� Ȯ���Ѵ�.
    Public Declare Function AxcSignalReadInput Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpInput As Integer) As Integer

    '// ī���� ����� ���� ä�ο� ���� ���� �Է� ���� ��Ʈ ���� Ȯ�� �Ѵ�.
    '// lBitNo ���� : 0 ~ 3
    Public Declare Function AxcSignalReadInputBit Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal lBitNo As Integer, ByRef upOnOff As Integer) As Integer

    '// ī���� ����� Ʈ���� ����� Ȱ��ȭ �Ѵ�.
    '// ���� ������ ��ɿ� ���� Ʈ���� ����� ���������� ����� ������ �����Ѵ�.
    Public Declare Function AxcTriggerSetEnable Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwUsage As Integer) As Integer

    '// ī���� ����� Ʈ���� ��� Ȱ��ȭ ���� ������ Ȯ���ϴ�.
    Public Declare Function AxcTriggerGetEnable Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpUsage As Integer) As Integer

    '// ī���� ����� ������ġ Ʈ���� ����� ���� ������ RAM ������ Ȯ���Ѵ�.
    '// dwAddr ���� : 0x0000 ~ 0x1FFFF;
    Public Declare Function AxcTriggerReadAbsRamData Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwAddr As Integer, ByRef dwpData As Integer) As Integer

    '// ī���� ����� ������ġ Ʈ���� ����� ���� �ʿ��� RAM ������ �����Ѵ�.
    '// dwAddr ���� : 0x0000 ~ 0x1FFFF;
    Public Declare Function AxcTriggerWriteAbsRamData Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwAddr As Integer, ByVal dwData As Integer) As Integer

    '// ī���� ����� ������ġ Ʈ���� ����� ���� �ʿ��� RAM ������ �ѹ��� �����Ѵ�.
    '// dwTrigNum ���� : ~ 0x20000, 
    '// dwDirection --> 0x0 : ���� Ʈ���� ��ġ�� ���� Ʈ���� ���� ���� �Է�. ��ġ�� �����ϴ� �������� Ʈ���� ��½� ���.
    '// dwDirection --> 0x1 : ���� ī���Ϳ� ���� Ʈ���� ���� ���� �Է�. ��ġ�� �����ϴ� �������� Ʈ���� ��½� ���.
    Public Declare Function AxcTriggerSetAbs Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwTrigNum As Integer, ByRef dwTrigPos As Integer, ByVal dwDirection As Integer) As Integer

End Module