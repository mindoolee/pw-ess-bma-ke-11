'****************************************************************************
'*****************************************************************************
'**
'** File Name
'** -----------
'**
'** AXC.BAS
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

Attribute VB_Name = "AXC"
'//========== ���� �� ��� ���� 
    '// CNT ����� �ִ��� Ȯ��
Public Declare Function AxcInfoIsCNTModule Lib "AXL.dll" (ByRef upStatus As Long) As Long
    
    '// CNT ��� No Ȯ��
Public Declare Function AxcInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef lpModuleNo As Long) As Long
    
    '// CNT ����� ����� ���� Ȯ��
Public Declare Function AxcInfoGetModuleCount Lib "AXL.dll" (ByRef lpModuleCount As Long) As Long

    '// ������ ����� ī���� �Է� ä�� ���� Ȯ��
Public Declare Function AxcInfoGetChannelCount Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpCount As Long) As Long
    
    '// �ý��ۿ� ������ ī������ �� ä�� ���� Ȯ��
Public Declare Function AxcInfoGetTotalChannelCount Lib "AXL.dll" (ByRef lpChannelCount As Long) As Long

    '// ������ ��� ��ȣ�� ���̽� ���� ��ȣ, ��� ��ġ, ��� ID Ȯ��
Public Declare Function AxcInfoGetModule Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpBoardNo As Long, ByRef lpModulePos As Long, ByRef upModuleID As Long) As Long

    '// �ش� ����� ��� ������ �������� ��ȯ�Ѵ�.
Public Declare Function AxcInfoGetModuleStatus Lib "AXL.dll" (ByVal lModuleNo As Long) As Long

Public Declare Function AxcInfoGetFirstChannelNoOfModuleNo Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpChannelNo As Long) As Long

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
Public Declare Function AxcSignalSetEncInputMethod Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwMethod As Long) As Long

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
Public Declare Function AxcSignalGetEncInputMethod Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dwpUpMethod As Long) As Long

    '// ī���� ����� Ʈ���Ÿ� ���� �մϴ�.
    '// dwMode -->  0x00 : Latch
    '// dwMode -->  0x01 : State
    '// dwMode -->  0x02 : Special State    --> SIO-CN2CH ����
    '// SIO-CN2CH�� ���
    '// dwMode -->  0x00 : ���� ��ġ Ʈ���� �Ǵ� �ֱ� ��ġ Ʈ����.
    '// ���� : ��ǰ���� ����� ���� �ٸ��� ������ �����Ͽ� ��� �ʿ�.
    '// dwMode -->  0x01 : �ð� �ֱ� Ʈ����(AxcTriggerSetFreq�� ����)
Public Declare Function AxcTriggerSetFunction Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwMode As Long) As Long

    '// ī���� ����� Ʈ���� ������ Ȯ�� �մϴ�.
    '// *dwMode -->  0x00 : Latch
    '// *dwMode -->  0x01 : State
    '// *dwMode -->  0x02 : Special State
    '// dwMode -->  0x00 : ���� ��ġ Ʈ���� �Ǵ� �ֱ� ��ġ Ʈ����.
    '// ���� : ��ǰ���� ����� ���� �ٸ��� ������ �����Ͽ� ��� �ʿ�.
    '// dwMode -->  0x01 : �ð� �ֱ� Ʈ����(AxcTriggerSetFreq�� ����)
Public Declare Function AxcTriggerGetFunction Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dwpMode As Long) As Long

    '// dwUsage --> 0x00 : Trigger Not use
    '// dwUsage --> 0x01 : Trigger use
Public Declare Function AxcTriggerSetNotchEnable Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwUsage As Long) As Long

    '// *dwUsage --> 0x00 : Trigger Not use
    '// *dwUsage --> 0x01 : Trigger use
Public Declare Function AxcTriggerGetNotchEnable Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dwpUsage As Long) As Long
    

    '// ī���� ����� Captuer �ؼ��� ���� �մϴ�.(External latch input polarity)
    '// dwCapturePol --> 0x00 : Signal OFF -> ON
    '// dwCapturePol --> 0x01 : Signal ON -> OFF
Public Declare Function AxcSignalSetCaptureFunction Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwCapturePol As Long) As Long

    '// ī���� ����� Captuer �ؼ� ������ Ȯ�� �մϴ�.(External latch input polarity)
    '// *dwCapturePol --> 0x00 : Signal OFF -> ON
    '// *dwCapturePol --> 0x01 : Signal ON -> OFF
Public Declare Function AxcSignalGetCaptureFunction Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dwpCapturePol As Long) As Long

    '// ī���� ����� Captuer ��ġ�� Ȯ�� �մϴ�.(External latch)
    '// *dbpCapturePos --> Capture position ��ġ
Public Declare Function AxcSignalGetCapturePos Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dbpCapturePos As Double) As Long

    '// ī���� ����� ī���� ���� Ȯ�� �մϴ�.
    '// *dbpActPos --> ī���� ��
Public Declare Function AxcStatusGetActPos Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dbpActPos As Double) As Long

    '// ī���� ����� ī���� ���� dbActPos ������ ���� �մϴ�.
Public Declare Function AxcStatusSetActPos Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dbActPos As Double) As Long

    '// ī���� ����� Ʈ���� ��ġ�� �����մϴ�.
    '// ī���� ����� Ʈ���� ��ġ�� 2�������� ���� �� �� �ֽ��ϴ�.
Public Declare Function AxcTriggerSetNotchPos Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dbLowerPos As Double, ByVal dbUpperPos As Double) As Long

    '// ī���� ����� ������ Ʈ���� ��ġ�� Ȯ�� �մϴ�.
Public Declare Function AxcTriggerGetNotchPos Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dbpLowerPos As Double, ByRef dbpUpperPos As Double) As Long

    '// ī���� ����� Ʈ���� ����� ������ �մϴ�.
    '// dwOutVal --> 0x00 : Ʈ���� ��� '0'
    '// dwOutVal --> 0x01 : Ʈ���� ��� '1'
Public Declare Function AxcTriggerSetOutput Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwOutVal As Long) As Long

    '// ī���� ����� ���¸� Ȯ���մϴ�.
    '// Bit '0' : Carry (ī���� ����ġ�� ���� �޽��� ���� ī���� ����ġ�� �Ѿ� 0�� �ٲ���� �� 1��ĵ�� ON���� �մϴ�.)
    '// Bit '1' : Borrow (ī���� ����ġ�� ���� �޽��� ���� 0�� �Ѿ� ī���� ����ġ�� �ٲ���� �� 1��ĵ�� ON���� �մϴ�.)
    '// Bit '2' : Trigger output status
    '// Bit '3' : Latch input status
Public Declare Function AxcStatusGetChannel Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dwpChannelStatus As Long) As Long


    '// SIO-CN2CH ���� �Լ���
    '//
    '// ī���� ����� ��ġ ������ �����Ѵ�.
    '// ���� ��ġ �̵����� ���� �޽� ������ �����ϴµ�,
    '// ex) 1mm �̵��� 1000�� �ʿ��ϴٸ�dMoveUnitPerPulse = 0.001�� �Է��ϰ�,
    '//     ���� ��� �Լ��� ��ġ�� ���õ� ���� mm ������ �����ϸ� �ȴ�.
Public Declare Function AxcMotSetMoveUnitPerPulse Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dMoveUnitPerPulse As Double) As Long

    '// ī���� ����� ��ġ ������ Ȯ���Ѵ�.
Public Declare Function AxcMotGetMoveUnitPerPulse Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dpMoveUnitPerPuls As Double) As Long

    '// ī���� ����� ���ڴ� �Է� ī���͸� ���� ����� �����Ѵ�.
    '// dwReverse --> 0x00 : �������� ����.
    '// dwReverse --> 0x01 : ����.
Public Declare Function AxcSignalSetEncReverse Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwReverse As Long) As Long

    '// ī���� ����� ���ڴ� �Է� ī���͸� ���� ����� ������ Ȯ���Ѵ�.
Public Declare Function AxcSignalGetEncReverse Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dwpReverse As Long) As Long

    '// ī���� ����� Encoder �Է� ��ȣ�� �����Ѵ�.
    '// dwSource -->  0x00 : 2(A/B)-Phase ��ȣ.
    '// dwSource -->  0x01 : Z-Phase ��ȣ.(���⼺ ����.)
Public Declare Function AxcSignalSetEncSource Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwSource As Long) As Long

    '// ī���� ����� Encoder �Է� ��ȣ ���� ������ Ȯ���Ѵ�.
Public Declare Function AxcSignalGetEncSource Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dwpSource As Long) As Long

    '// ī���� ����� Ʈ���� ��� ���� �� ���� ���� �����Ѵ�.
    '// ��ġ �ֱ� Ʈ���� ��ǰ�� ��� ��ġ �ֱ�� Ʈ���� ����� �߻���ų ���� �� ���� ���� �����Ѵ�.
    '// ���� ��ġ Ʈ���� ��ǰ�� ��� Ram ���� ������ Ʈ���� ������ ���� ���� ��ġ�� �����Ѵ�.
    '// ���� : AxcMotSetMoveUnitPerPulse�� ������ ����.
    '// Note : ���Ѱ��� ���Ѱ����� �������� �����Ͽ��� �մϴ�.
Public Declare Function AxcTriggerSetBlockLowerPos Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dLowerPosition As Double) As Long

    '// ī���� ����� Ʈ���� ��� ���� �� ���� ���� Ȯ���Ѵ�.
Public Declare Function AxcTriggerGetBlockLowerPos Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dpLowerPosition As Double) As Long

    '// ī���� ����� Ʈ���� ��� ���� �� ���� ���� �����Ѵ�.
    '// ��ġ �ֱ� Ʈ���� ��ǰ�� ��� ��ġ �ֱ�� Ʈ���� ����� �߻���ų ���� �� ���� ���� �����Ѵ�.
    '// ���� ��ġ Ʈ���� ��ǰ�� ��� Ʈ���� ������ ������ Ram �� ������ ������ Ʈ���� ������ ����Ǵ� ��ġ�� ���ȴ�.
    '// ���� : AxcMotSetMoveUnitPerPulse�� ������ ����.
    '// Note : ���Ѱ��� ���Ѱ����� ū���� �����Ͽ��� �մϴ�.
Public Declare Function AxcTriggerSetBlockUpperPos Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dUpperPosition As Double) As Long
    '// ī���� ����� Ʈ���� ��� ���� �� ���� ���� �����Ѵ�.
Public Declare Function AxcTriggerGetBlockUpperPos Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dpUpperrPosition As Double) As Long

    '// ī���� ����� ��ġ �ֱ� ��� Ʈ���ſ� ���Ǵ� ��ġ �ֱ⸦ �����Ѵ�.
    '// ���� : AxcMotSetMoveUnitPerPulse�� ������ ����.
Public Declare Function AxcTriggerSetPosPeriod Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dPeriod As Double) As Long

    '// ī���� ����� ��ġ �ֱ� ��� Ʈ���ſ� ���Ǵ� ��ġ �ֱ⸦ Ȯ���Ѵ�.
Public Declare Function AxcTriggerGetPosPeriod Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dpPeriod As Double) As Long

    '// ī���� ����� ��ġ �ֱ� ��� Ʈ���� ���� ��ġ ������ ���� ��ȿ����� �����Ѵ�.
    '// dwDirection -->  0x00 : ī������ ��/���� ���Ͽ� Ʈ���� �ֱ� ���� ���.
    '// dwDirection -->  0x01 : ī���Ͱ� ���� �Ҷ��� Ʈ���� �ֱ� ���� ���.
    '// dwDirection -->  0x01 : ī���Ͱ� ���� �Ҷ��� Ʈ���� �ֱ� ���� ���.
Public Declare Function AxcTriggerSetDirectionCheck Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwDirection As Long) As Long
    '// ī���� ����� ��ġ �ֱ� ��� Ʈ���� ���� ��ġ ������ ���� ��ȿ��� ������ Ȯ���Ѵ�.
Public Declare Function AxcTriggerGetDirectionCheck Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dwpDirection As Long) As Long

    '// ī���� ����� ��ġ �ֱ� ��� Ʈ���� ����� ����, ��ġ �ֱ⸦ �ѹ��� �����Ѵ�.
    '// ��ġ ���� ���� :  AxcMotSetMoveUnitPerPulse�� ������ ����.
Public Declare Function AxcTriggerSetBlock Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dLower As Double, ByVal dUpper As Double, ByVal dABSod As Double) As Long

    '// ī���� ����� ��ġ �ֱ� ��� Ʈ���� ����� ����, ��ġ �ֱ⸦ ������ �ѹ��� Ȯ���Ѵ�.
Public Declare Function AxcTriggerGetBlock Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dpLower As Double, ByRef dpUpper As Double, ByRef dpABSod As Double) As Long

    '// ī���� ����� Ʈ���� ��� �޽� ���� �����Ѵ�.
    '// ���� : uSec
Public Declare Function AxcTriggerSetTime Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dTrigTime As Double) As Long

    '// ī���� ����� Ʈ���� ��� �޽� �� ������ Ȯ���Ѵ�.
Public Declare Function AxcTriggerGetTime Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dpTrigTime As Double) As Long

    '// ī���� ����� Ʈ���� ��� �޽��� ��� ������ �����Ѵ�.
    '// dwLevel -->  0x00 : Ʈ���� ��½� 'Low' ���� ���.
    '// dwLevel -->  0x00 : Ʈ���� ��½� 'High' ���� ���.
Public Declare Function AxcTriggerSetLevel Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwLevel As Long) As Long
    '// ī���� ����� Ʈ���� ��� �޽��� ��� ���� ������ Ȯ���Ѵ�.
Public Declare Function AxcTriggerGetLevel Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dwpLevel As Long) As Long

    '// ī���� ����� ���ļ� Ʈ���� ��� ��ɿ� �ʿ��� ���ļ��� �����Ѵ�.
    '// ���� : Hz, ���� : 1Hz ~ 500 kHz
Public Declare Function AxcTriggerSetFreq Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwFreqency As Long) As Long
    '// ī���� ����� ���ļ� Ʈ���� ��� ��ɿ� �ʿ��� ���ļ��� ������ Ȯ���Ѵ�.
Public Declare Function AxcTriggerGetFreq Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dwpFreqency As Long) As Long

    '// ī���� ����� ���� ä�ο� ���� ���� ��� ���� �����Ѵ�.
    '// dwOutput ���� : 0x00 ~ 0x0F, �� ä�δ� 4���� ���� ���
Public Declare Function AxcSignalWriteOutput Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwOutput As Long) As Long

    '// ī���� ����� ���� ä�ο� ���� ���� ��� ���� Ȯ���Ѵ�.
Public Declare Function AxcSignalReadOutput Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dwpOutput As Long) As Long

    '// ī���� ����� ���� ä�ο� ���� ���� ��� ���� ��Ʈ ���� �����Ѵ�.
    '// lBitNo ���� : 0 ~ 3, �� ä�δ� 4���� ���� ���
Public Declare Function AxcSignalWriteOutputBit Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal lBitNo As Long, ByVal uOnOff As Long) As Long
    '// ī���� ����� ���� ä�ο� ���� ���� ��� ���� ��Ʈ ���� Ȯ�� �Ѵ�.
    '// lBitNo ���� : 0 ~ 3
Public Declare Function AxcSignalReadOutputBit Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal lBitNo As Long, ByRef upOnOff As Long) As Long

    '// ī���� ����� ���� ä�ο� ���� ���� �Է� ���� Ȯ���Ѵ�.
Public Declare Function AxcSignalReadInput Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dwpInput As Long) As Long

    '// ī���� ����� ���� ä�ο� ���� ���� �Է� ���� ��Ʈ ���� Ȯ�� �Ѵ�.
    '// lBitNo ���� : 0 ~ 3
Public Declare Function AxcSignalReadInputBit Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal lBitNo As Long, ByRef upOnOff As Long) As Long

    '// ī���� ����� Ʈ���� ����� Ȱ��ȭ �Ѵ�.
    '// ���� ������ ��ɿ� ���� Ʈ���� ����� ���������� ����� ������ �����Ѵ�.
Public Declare Function AxcTriggerSetEnable Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwUsage As Long) As Long

    '// ī���� ����� Ʈ���� ��� Ȱ��ȭ ���� ������ Ȯ���ϴ�.
Public Declare Function AxcTriggerGetEnable Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dwpUsage As Long) As Long

    '// ī���� ����� ������ġ Ʈ���� ����� ���� ������ RAM ������ Ȯ���Ѵ�.
    '// dwAddr ���� : 0x0000 ~ 0x1FFFF;
Public Declare Function AxcTriggerReadAbsRamData Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwAddr As Long, ByRef dwpData As Long) As Long

    '// ī���� ����� ������ġ Ʈ���� ����� ���� �ʿ��� RAM ������ �����Ѵ�.
    '// dwAddr ���� : 0x0000 ~ 0x1FFFF;
Public Declare Function AxcTriggerWriteAbsRamData Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwAddr As Long, ByVal dwData As Long) As Long

    '// ī���� ����� ������ġ Ʈ���� ����� ���� �ʿ��� RAM ������ �ѹ��� �����Ѵ�.
    '// dwTrigNum ���� : ~ 0x20000, 
    '// dwDirection --> 0x0 : ���� Ʈ���� ��ġ�� ���� Ʈ���� ���� ���� �Է�. ��ġ�� �����ϴ� �������� Ʈ���� ��½� ���.
    '// dwDirection --> 0x1 : ���� ī���Ϳ� ���� Ʈ���� ���� ���� �Է�. ��ġ�� �����ϴ� �������� Ʈ���� ��½� ���.
Public Declare Function AxcTriggerSetAbs Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwTrigNum As Long, ByRef dwTrigPos As Long, ByVal dwDirection As Long) As Long