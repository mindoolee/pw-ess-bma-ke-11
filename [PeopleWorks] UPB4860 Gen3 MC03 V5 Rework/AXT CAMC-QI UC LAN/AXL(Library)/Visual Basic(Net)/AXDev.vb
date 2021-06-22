Option Strict Off
Option Explicit On
Module AXDev    
    ' Board Number�� �̿��Ͽ� Board Address ã��
    Public Declare Function AxlGetBoardAddress Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef upBoardAddress As Integer) As Integer
    ' Board Number�� �̿��Ͽ� Board ID ã��
    Public Declare Function AxlGetBoardID Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef upBoardID As Integer) As Integer
    ' Board Number�� �̿��Ͽ� Board Version ã��
    Public Declare Function AxlGetBoardVersion Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef upBoardVersion As Integer) As Integer
    ' Board Number�� Module Position�� �̿��Ͽ� Module ID ã��
    Public Declare Function AxlGetModuleID Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByRef upModuleID As Integer) As Integer
    ' Board Number�� Module Position�� �̿��Ͽ� Module Version ã��
    Public Declare Function AxlGetModuleVersion Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByRef upModuleVersion As Integer) As Integer
    ' Board Number�� Module Position�� �̿��Ͽ� Network Node ���� Ȯ��
    Public Declare Function AxlGetModuleNodeInfo Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByRef upNetNo As Integer, ByRef upNodeAddr As Integer) As Integer

    ' Board�� ����� ���� Data Flash Write (PCI-R1604[RTEX master board]����)
    ' lPageAddr(0 ~ 199)
    ' lByteNum(1 ~ 120)
    ' ����) Flash�� ����Ÿ�� ������ ���� ���� �ð�(�ִ� 17mSec)�� �ҿ�Ǳ⶧���� ���� ����� ���� �ð��� �ʿ���.
    Public Declare Function AxlSetDataFlash Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lPageAddr As Integer, ByVal lBytesNum As Integer, ByRef bpSetData As Byte) As Integer

    ' Board�� ����� ���� Data Flash Read(PCI-R1604[RTEX master board]����)
    ' lPageAddr(0 ~ 199)
    ' lByteNum(1 ~ 120)
    Public Declare Function AxlGetDataFlash Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lPageAddr As Integer, ByVal lBytesNum As Integer, ByRef bpGetData As Byte) As Integer

    ' Board Number�� Module Position�� �̿��Ͽ� AIO Module Number ã��
    Public Declare Function AxaInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByRef lpModuleNo As Integer) As Integer
    ' Board Number�� Module Position�� �̿��Ͽ� DIO Module Number ã��
    Public Declare Function AxdInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByRef lpModuleNo As Integer) As Integer

    ' ���� �࿡ IPCOMMAND Setting
    Public Declare Function AxmSetCommand Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte) As Integer
    ' ���� �࿡ 8bit IPCOMMAND Setting
    Public Declare Function AxmSetCommandData08 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    ' ���� �࿡ 8bit IPCOMMAND ��������
    Public Declare Function AxmGetCommandData08 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer
    ' ���� �࿡ 16bit IPCOMMAND Setting
    Public Declare Function AxmSetCommandData16 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    ' ���� �࿡ 16bit IPCOMMAND ��������
    Public Declare Function AxmGetCommandData16 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer
    ' ���� �࿡ 24bit IPCOMMAND Setting
    Public Declare Function AxmSetCommandData24 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    ' ���� �࿡ 24bit IPCOMMAND ��������
    Public Declare Function AxmGetCommandData24 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer
    ' ���� �࿡ 32bit IPCOMMAND Setting
    Public Declare Function AxmSetCommandData32 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    ' ���� �࿡ 32bit IPCOMMAND ��������
    Public Declare Function AxmGetCommandData32 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer

    ' ���� �࿡ QICOMMAND Setting
    Public Declare Function AxmSetCommandQi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte) As Integer
    ' ���� �࿡ 8bit IPCOMMAND Setting
    Public Declare Function AxmSetCommandData08Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    ' ���� �࿡ 8bit IPCOMMAND ��������
    Public Declare Function AxmGetCommandData08Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer
    ' ���� �࿡ 16bit IPCOMMAND Setting
    Public Declare Function AxmSetCommandData16Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    ' ���� �࿡ 16bit IPCOMMAND ��������
    Public Declare Function AxmGetCommandData16Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer
    ' ���� �࿡ 24bit IPCOMMAND Setting
    Public Declare Function AxmSetCommandData24Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    ' ���� �࿡ 24bit IPCOMMAND ��������
    Public Declare Function AxmGetCommandData24Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer
    ' ���� �࿡ 32bit IPCOMMAND Setting
    Public Declare Function AxmSetCommandData32Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    ' ���� �࿡ 32bit IPCOMMAND ��������
    Public Declare Function AxmGetCommandData32Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer

    ' ���� �࿡ Port Data �������� - SMC-2V03
    Public Declare Function AxmGetPortData Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wOffset As Integer, ByRef upData As Integer) As Integer
    ' ���� �࿡ Port Data Setting - SMC-2V03
    Public Declare Function AxmSetPortData Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wOffset As Integer, ByRef dwData As Integer) As Integer
    ' ���� �࿡ Port Data �������� - PIC-N804/404
    Public Declare Function AxmGetPortDataQi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wOffset As Integer, ByRef upData As Integer) As Integer
    ' ���� �࿡ Port Data Setting - PCI-N804/404
    Public Declare Function AxmSetPortDataQi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wOffset As Integer, ByRef dwData As Integer) As Integer


    ' ���� �࿡ ��ũ��Ʈ�� �����Ѵ�. - IP
    ' sc    : ��ũ��Ʈ ��ȣ  Lib "AXL.dll" (1 - 4)
    ' event : �߻��� �̺�Ʈ SCRCON �� �����Ѵ�.
    '         �̺�Ʈ ���� �హ������, �̺�Ʈ �߻��� ��, �̺�Ʈ ���� 1,2 �Ӽ� �����Ѵ�.
    ' cmd   : � ������ �ٲܰ����� ���� SCRCMD�� �����Ѵ�.
    ' data  : � Data�� �ٲܰ����� ����
    Public Declare Function AxmSetScriptCaptionIp Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sc As Integer, ByVal event1 As Integer, ByVal data As Integer) As Integer
    ' ���� �࿡ ��ũ��Ʈ�� ��ȯ�Ѵ�. - IP
    Public Declare Function AxmGetScriptCaptionIp Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sc As Integer, ByRef event1 As Integer, ByRef data As Integer) As Integer

    ' ���� �࿡ ��ũ��Ʈ�� �����Ѵ�. - QI
    ' sc    : ��ũ��Ʈ ��ȣ  Lib "AXL.dll" (1 - 4)
    ' event : �߻��� �̺�Ʈ SCRCON �� �����Ѵ�.
    '         �̺�Ʈ ���� �హ������, �̺�Ʈ �߻��� ��, �̺�Ʈ ���� 1,2 �Ӽ� �����Ѵ�.
    ' cmd   : � ������ �ٲܰ����� ���� SCRCMD�� �����Ѵ�.
    ' data  : � Data�� �ٲܰ����� ����
    Public Declare Function AxmSetScriptCaptionQi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sc As Integer, ByVal event1 As Integer, ByVal cmd As Integer, ByVal data As Integer) As Integer
    ' ���� �࿡ ��ũ��Ʈ�� ��ȯ�Ѵ�. - QI
    Public Declare Function AxmGetScriptCaptionQi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sc As Integer, ByRef event1 As Integer, ByRef cmd As Integer, ByRef data As Integer) As Integer

    ' ���� �࿡ ��ũ��Ʈ ���� Queue Index�� Clear ��Ų��.
    ' uSelect IP.
    ' uSelect Lib "AXL.dll" (0): ��ũ��Ʈ Queue Index �� Clear�Ѵ�.
    '         Lib "AXL.dll" (1): ĸ�� Queue�� Index Clear�Ѵ�.

    ' uSelect QI.
    ' uSelect Lib "AXL.dll" (0): ��ũ��Ʈ Queue 1 Index �� Clear�Ѵ�.
    '         Lib "AXL.dll" (1): ��ũ��Ʈ Queue 2 Index �� Clear�Ѵ�.

    Public Declare Function AxmSetScriptCaptionQueueClear Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal uSelect As Integer) As Integer

    ' ���� �࿡ ��ũ��Ʈ ���� Queue�� Index ��ȯ�Ѵ�.
    ' uSelect IP
    ' uSelect Lib "AXL.dll" (0): ��ũ��Ʈ Queue Index�� �о�´�.
    '         Lib "AXL.dll" (1): ĸ�� Queue Index�� �о�´�.

    ' uSelect QI.
    ' uSelect Lib "AXL.dll" (0): ��ũ��Ʈ Queue 1 Index�� �о�´�.
    '         Lib "AXL.dll" (1): ��ũ��Ʈ Queue 2 Index�� �о�´�.

    Public Declare Function AxmGetScriptCaptionQueueCount Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef updata As Integer, ByVal uSelect As Integer) As Integer

    ' ���� �࿡ ��ũ��Ʈ ���� Queue�� Data���� ��ȯ�Ѵ�.
    ' uSelect IP
    ' uSelect Lib "AXL.dll" (0): ��ũ��Ʈ Queue Data �� �о�´�.
    '         Lib "AXL.dll" (1): ĸ�� Queue Data�� �о�´�.

    ' uSelect QI.
    ' uSelect Lib "AXL.dll" (0): ��ũ��Ʈ Queue 1 Data �о�´�.
    '         Lib "AXL.dll" (1): ��ũ��Ʈ Queue 2 Data �о�´�.

    Public Declare Function AxmGetScriptCaptionQueueDataCount Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef updata As Integer, ByVal uSelect As Integer) As Integer

    ' ���� ����Ÿ�� �о�´�.
    Public Declare Function AxmGetOptimizeDriveData Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dMinVel As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByRef wRangeData As Integer, ByRef wStartStopSpeedData As Integer, ByRef wObjectSpeedData As Integer, ByRef wAccelRate As Integer, ByRef wDecelRate As Integer) As Integer

    ' ���峻�� �������͸� Byte������ ���� �� Ȯ���Ѵ�.
    Public Declare Function AxmBoardWriteByte Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByVal byData As Byte) As Integer
    Public Declare Function AxmBoardReadByte Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByRef byData As Byte) As Integer

    ' ���峻�� �������͸� Word������ ���� �� Ȯ���Ѵ�.
    Public Declare Function AxmBoardWriteWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByVal wData As Integer) As Integer
    Public Declare Function AxmBoardReadWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByRef wData As Integer) As Integer

    ' ���峻�� �������͸� DWord������ ���� �� Ȯ���Ѵ�.
    Public Declare Function AxmBoardWriteDWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByVal dwData As Integer) As Integer
    Public Declare Function AxmBoardReadDWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByRef dwData As Integer) As Integer

    ' ���峻�� ��⿡ �������͸� Byte���� �� Ȯ���Ѵ�.
    Public Declare Function AxmModuleWriteByte Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByVal wOffset As Integer, ByVal byData As Byte) As Integer
    Public Declare Function AxmModuleReadByte Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByVal wOffset As Integer, ByRef byData As Byte) As Integer

    ' ���峻�� ��⿡ �������͸� Word���� �� Ȯ���Ѵ�.
    Public Declare Function AxmModuleWriteWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByVal wOffset As Integer, ByVal wData As Integer) As Integer
    Public Declare Function AxmModuleReadWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByVal wOffset As Integer, ByRef wData As Integer) As Integer

    ' ���峻�� ��⿡ �������͸� DWord���� �� Ȯ���Ѵ�.
    Public Declare Function AxmModuleWriteDWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByVal wOffset As Integer, ByVal dwData As Integer) As Integer
    Public Declare Function AxmModuleReadDWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByVal wOffset As Integer, ByRef dwData As Integer) As Integer


    ' �ܺ� ��ġ �񱳱⿡ ���� �����Ѵ�. Lib "AXL.dll" (Pos = Unit)
    Public Declare Function AxmStatusSetActComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dPos As Double) As Integer
    ' �ܺ� ��ġ �񱳱⿡ ���� ��ȯ�Ѵ�. Lib "AXL.dll" (Positon = Unit)
    Public Declare Function AxmStatusGetActComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dpPos As Double) As Integer

    ' ���� ��ġ �񱳱⿡ ���� �����Ѵ�. Lib "AXL.dll" (Pos = Unit)
    Public Declare Function AxmStatusSetCmdComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dPos As Double) As Integer
    ' ���� ��ġ �񱳱⿡ ���� ��ȯ�Ѵ�. Lib "AXL.dll" (Pos = Unit)
    Public Declare Function AxmStatusGetCmdComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dpPos As Double) As Integer

    '========== �߰� �Լ� =========================================================================================================

    ' ���� ���� �� �ӵ��� ������ ���Ѵ�� �����Ѵ�.
    ' �ӵ� ������� �Ÿ��� �־��־�� �Ѵ�.
    Public Declare Function AxmLineMoveVel Lib "AXL.dll" (ByVal lCoord As Integer, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Integer

    '========= ���� ��ġ ���� �Լ� Lib "AXL.dll" ( �ʵ�: IP������ , QI���� ��ɾ���)=========================================================================

    ' ���� ���� Sensor ��ȣ�� ��� ���� �� ��ȣ �Է� ������ �����Ѵ�.
    ' ��� ���� LOW Lib "AXL.dll" (0), HIGH Lib "AXL.dll" (1), UNUSED Lib "AXL.dll" (2), USED Lib "AXL.dll" (3)
    Public Declare Function AxmSensorSetSignal Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal uLevel As Integer) As Integer
    ' ���� ���� Sensor ��ȣ�� ��� ���� �� ��ȣ �Է� ������ ��ȯ�Ѵ�.
    Public Declare Function AxmSensorGetSignal Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef upLevel As Integer) As Integer
    ' ���� ���� Sensor ��ȣ�� �Է� ���¸� ��ȯ�Ѵ�
    Public Declare Function AxmSensorReadSignal Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef upStatus As Integer) As Integer

    ' ���� ���� ������ �ӵ��� �������� ���� ��ġ ����̹��� �����Ѵ�.
    ' Sensor ��ȣ�� Active level�Է� ���� ��� ��ǥ�� ������ �Ÿ���ŭ ������ �����Ѵ�.
    ' �޽��� ��µǴ� �������� �Լ��� �����.
    ' lMethod :  0 - �Ϲ� ����, 1 - ���� ��ȣ ���� ���� ���� ����. ��ȣ ���� �� �Ϲ� ����
    '            2 - ���� ����
    Public Declare Function AxmSensorMovePos Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lMethod As Integer) As Integer

    ' ���� ���� ������ �ӵ��� �������� ���� ��ġ ����̹��� �����Ѵ�.
    ' Sensor ��ȣ�� Active level�Է� ���� ��� ��ǥ�� ������ �Ÿ���ŭ ������ �����Ѵ�.
    ' �޽� ����� ����Ǵ� �������� �Լ��� �����.
    Public Declare Function AxmSensorStartMovePos Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lMethod As Integer) As Integer

    ' �����˻� ���ེ�� ��ȭ�� ����� ��ȯ�Ѵ�.
    ' lpStepCount      : ��ϵ� Step�� ����
    ' upMainStepNumber : ��ϵ� MainStepNumber ������ �迭����Ʈ
    ' upStepNumber     : ��ϵ� StepNumber ������ �迭����Ʈ
    ' upStepBranch     : ��ϵ� Step�� Branch ������ �迭����Ʈ
    ' ����: �迭������ 50���� ����
    Public Declare Function AxmHomeGetStepTrace Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef lpStepCount As Integer, ByRef upMainStepNumber As Integer, ByRef upStepNumber As Integer, ByRef upStepBranch As Integer) As Integer

    '=======�߰� Ȩ ��ġ  Lib "AXL.dll" (PI-N804/404���� �ش��.)=================================================================================
    ' ����ڰ� ������ ���� Ȩ���� �Ķ��Ÿ�� �����Ѵ�. Lib "AXL.dll" (QIĨ ���� �������� �̿�).
    ' uZphasCount : Ȩ �Ϸ��Ŀ� Z�� ī��Ʈ Lib "AXL.dll" (0 - 15)
    ' lHomeMode   : Ȩ ���� ��� Lib "AXL.dll" ( 0 - 12)
    ' lClearSet   : ��ġ Ŭ���� , �ܿ��޽� Ŭ���� ��� ����  Lib "AXL.dll" (0 - 3)
    '               0: ��ġŬ���� ������, �ܿ��޽� Ŭ���� ��� ����
    '               1: ��ġŬ���� �����, �ܿ��޽� Ŭ���� ��� ����
    '               2: ��ġŬ���� ������, �ܿ��޽� Ŭ���� �����
    '               3: ��ġŬ���� �����, �ܿ��޽� Ŭ���� �����.
    ' dOrgVel : Ȩ���� Org  Speed ����
    ' dLastVel: Ȩ���� Last Speed ����
    Public Declare Function AxmHomeSetConfig Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal uZphasCount As Integer, ByVal lHomeMode As Integer, ByVal lClearSet As Integer, ByVal dOrgVel As Double, ByVal dLastVel As Double, ByVal dLeavePos As Double) As Integer
    ' ����ڰ� ������ ���� Ȩ���� �Ķ��Ÿ�� ��ȯ�Ѵ�.
    Public Declare Function AxmHomeGetConfig Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef upZphasCount As Integer, ByRef lpHomeMode As Integer, ByRef lpClearSet As Integer, ByRef dpOrgVel As Double, ByRef dpLastVel As Double, ByRef dpLeavePos As Double) As Integer

    ' ����ڰ� ������ ���� Ȩ ��ġ�� �����Ѵ�.
    ' lHomeMode ���� ���� : 0 - 5 ����  Lib "AXL.dll" (Move Return�Ŀ� Search��  �����Ѵ�.)
    ' lHomeMode -1�� �״�� ���� HomeConfig���� ����Ѵ�� �״�� ������.
    ' ��������      : Vel���� ����̸� CW, �����̸� CCW.
    Public Declare Function AxmHomeSetMoveSearch Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Integer

    ' ����ڰ� ������ ���� Ȩ ������ �����Ѵ�.
    ' lHomeMode ���� ���� : 0 - 12 ����
    ' lHomeMode -1�� �״�� ���� HomeConfig���� ����Ѵ�� �״�� ������.
    ' ��������      : Vel���� ����̸� CW, �����̸� CCW.
    Public Declare Function AxmHomeSetMoveReturn Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Integer

    ' ����ڰ� ������ ���� Ȩ ��Ż�� �����Ѵ�.
    ' ��������      : Vel���� ����̸� CW, �����̸� CCW.
    Public Declare Function AxmHomeSetMoveLeave Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Integer

    ' ����ڰ� ������ ������ Ȩ ��ġ�� �����Ѵ�.
    ' lHomeMode ���� ���� : 0 - 5 ����  Lib "AXL.dll" (Move Return�Ŀ� Search��  �����Ѵ�.)
    ' lHomeMode -1�� �״�� ���� HomeConfig���� ����Ѵ�� �״�� ������.
    ' ��������      : Vel���� ����̸� CW, �����̸� CCW.
    Public Declare Function AxmHomeSetMultiMoveSearch Lib "AXL.dll" (ByVal lArraySize As Integer, ByRef lpAxesNo As Integer, ByRef dpVel As Double, ByRef dpAccel As Double, ByRef dpDecel As Double) As Integer

    '������ ��ǥ���� ���� �ӵ� �������� ��带 �����Ѵ�.
    '  Lib "AXL.dll" (������ : �ݵ�� ����� �ϰ� ��밡��)
    ' ProfileMode : '0' - ��Ī Trapezode
    '               '1' - ���Ī Trapezode
    '               '2' - ��Ī Quasi-S Curve
    '               '3' - ��Ī S Curve
    '               '4' - ���Ī S Curve
    Public Declare Function AxmContiSetProfileMode Lib "AXL.dll" (ByVal lCoord As Integer, ByVal uProfileMode As Integer) As Integer
    ' ������ ��ǥ���� ���� �ӵ� �������� ��带 ��ȯ�Ѵ�.
    Public Declare Function AxmContiGetProfileMode Lib "AXL.dll" (ByVal lCoord As Integer, ByRef upProfileMode As Integer) As Integer

    '========== DIO ���ͷ�Ʈ �÷��� ������Ʈ �б�
    ' ������ �Է� ���� ���, Interrupt Flag Register�� Offset ��ġ���� bit ������ ���ͷ�Ʈ �߻� ���� ���� ����
    Public Declare Function AxdiInterruptFlagReadBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer
    ' ������ �Է� ���� ���, Interrupt Flag Register�� Offset ��ġ���� byte ������ ���ͷ�Ʈ �߻� ���� ���� ����
    Public Declare Function AxdiInterruptFlagReadByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer
    ' ������ �Է� ���� ���, Interrupt Flag Register�� Offset ��ġ���� word ������ ���ͷ�Ʈ �߻� ���� ���� ����
    Public Declare Function AxdiInterruptFlagReadWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer
    ' ������ �Է� ���� ���, Interrupt Flag Register�� Offset ��ġ���� double word ������ ���ͷ�Ʈ �߻� ���� ���� ����
    Public Declare Function AxdiInterruptFlagReadDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer
    ' ��ü �Է� ���� ���, Interrupt Flag Register�� Offset ��ġ���� bit ������ ���ͷ�Ʈ �߻� ���� ���� ����
    Public Declare Function AxdiInterruptFlagRead Lib "AXL.dll" (ByVal lOffset As Integer, ByRef upValue As Integer) As Integer


    '========= �α� ���� �Լ� ==========================================================================================
    ' ���� �ڵ����� ������.
    ' ���� ���� �Լ� ���� ����� EzSpy���� ����͸� �� �� �ֵ��� ���� �Ǵ� �����ϴ� �Լ��̴�.
    ' uUse : ��� ���� => DISABLE Lib "AXL.dll" (0), ENABLE Lib "AXL.dll" (1)
    Public Declare Function AxmLogSetAxis Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal uUse As Integer) As Integer

    ' EzSpy������ ���� �� �Լ� ���� ��� ����͸� ���θ� Ȯ���ϴ� �Լ��̴�.
    Public Declare Function AxmLogGetAxis Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef upUse As Integer) As Integer

    '=========== �α� ��� ���� �Լ�
    '������ �Է� ä���� EzSpy�� �α� ��� ���θ� �����Ѵ�.
    Public Declare Function AxaiLogSetChannel Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal uUse As Integer) As Integer
    '������ �Է� ä���� EzSpy�� �α� ��� ���θ� Ȯ���Ѵ�.
    Public Declare Function AxaiLogGetChannel Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef upUse As Integer) As Integer

    '==������ ��� ä���� EzSpy �α� ���
    '������ ��� ä���� EzSpy�� �α� ��� ���θ� �����Ѵ�.
    Public Declare Function AxaoLogSetChannel Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal uUse As Integer) As Integer
    '������ ��� ä���� EzSpy�� �α� ��� ���θ� Ȯ���Ѵ�.
    Public Declare Function AxaoLogGetChannel Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef upUse As Integer) As Integer

    '==Log
    ' ������ ����� EzSpy�� �α� ��� ���� ����
    Public Declare Function AxdLogSetModule Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal uUse As Integer) As Integer
    ' ������ ����� EzSpy�� �α� ��� ���� Ȯ��
    Public Declare Function AxdLogGetModule Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef upUse As Integer) As Integer

    ' ������ ���尡 RTEX ����� �� �� ������ firmware ������ Ȯ���Ѵ�.
    Public Declare Function AxlGetFirmwareVersion Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal szVersion As String) As Integer
    ' ������ ����� Firmware�� ���� �Ѵ�.
    Public Declare Function AxlSetFirmwareCopy Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef wData As Integer, ByRef wCmdData As Integer) As Integer
    ' ������ ����� Firmware Update�� �����Ѵ�.
    Public Declare Function AxlSetFirmwareUpdate Lib "AXL.dll" (ByVal lBoardNo As Integer) As Integer
    ' ������ ������ ���� RTEX �ʱ�ȭ ���¸� Ȯ�� �Ѵ�.
    Public Declare Function AxlCheckStatus Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef dwStatus As Integer) As Integer
    ' ������ �࿡ RTEX Master board�� ���� ����� ���� �մϴ�.
    Public Declare Function AxlRtexUniversalCmd Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wCmd As Integer, ByVal wOffset As Integer, ByRef wData As Integer) As Integer
    ' ������ ���� RTEX ��� ����� �����Ѵ�.
    Public Declare Function AxmRtexSlaveCmd Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwCmdCode As Integer, ByVal dwTypeCode As Integer, ByVal dwIndexCode As Integer, ByVal dwCmdConfigure As Integer, ByVal dwValue As Integer) As Integer
    ' ������ �࿡ ������ RTEX ��� ����� ������� Ȯ���Ѵ�.
    Public Declare Function AxmRtexGetSlaveCmdResult Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwIndex As Integer, ByRef dwValue As Integer) As Integer
    ' ������ �࿡ RTEX ���� ������ Ȯ���Ѵ�.
    Public Declare Function AxmRtexGetAxisStatus Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwStatus As Integer) As Integer
    ' ������ �࿡ RTEX ��� ���� ������ Ȯ���Ѵ�. Lib "AXL.dll" (Actual position, Velocity, Torque)
    Public Declare Function AxmRtexGetAxisReturnData Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwReturn1 As Integer, ByRef dwReturn2 As Integer, ByRef dwReturn3 As Integer) As Integer
    ' ������ �࿡ RTEX Slave ���� ���� ���� ������ Ȯ���Ѵ�. Lib "AXL.dll" (mechanical, Inposition and etc)
    Public Declare Function AxmRtexGetAxisSlaveStatus Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwStatus As Integer) As Integer

    ' ������ �࿡ MLII Slave �࿡ ���� ��Ʈ�� ��ɾ �����Ѵ�.
    Public Declare Function AxmSetAxisCmd Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef tagCommand As Integer) As Integer
    ' ������ �࿡ MLII Slave �࿡ ���� ��Ʈ�� ����� ����� Ȯ���Ѵ�.
    Public Declare Function AxmGetAxisCmdResult Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef tagCommand As Integer) As Integer

    Public Declare Function AxlGetDpRamData Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wAddress As Integer, ByRef dwpRdData As Integer) As Integer
    Public Declare Function AxlBoardReadDpramWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByRef dwpRdData As Integer) As Integer

    Public Declare Function AxlSetSendBoardCommand Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal dwCommand As Integer, ByRef dwpSendData As Integer, ByVal dwLength As Integer) As Integer
    Public Declare Function AxlGetResponseBoardCommand Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef dwpReadData As Integer) As Integer

    ' Network Type Master ���忡�� Slave ���� Firmware Version�� �о� ���� �Լ�.
    ' ucaFirmwareVersion unsigned char ���� Array�� �����ϰ� ũ�Ⱑ 4�̻��� �ǵ��� ���� �ؾ� �Ѵ�.
    Public Declare Function AxmInfoGetFirmwareVersion Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef ucaFirmwareVersion As Integer) As Integer
    Public Declare Function AxaInfoGetFirmwareVersion Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef ucaFirmwareVersion As Integer) As Integer
    Public Declare Function AxdInfoGetFirmwareVersion Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef ucaFirmwareVersion As Integer) As Integer
   
    '======== PCI-R1604-MLII ���� �Լ�======================================================================
    ' INTERPOLATE and LATCH Command�� Option Field�� Torq Feed Forward�� ���� ���� �ϵ��� �մϴ�.
    ' �⺻���� MAX�� �����Ǿ� �ֽ��ϴ�.
    ' �������� 0 ~ 4000H���� ���� �� �� �ֽ��ϴ�.
    ' �������� 4000H�̻����� �����ϸ� ������ �� �̻����� �����ǳ� ������ 4000H���� ���� �˴ϴ�.
    Public Declare Function  AxmSetTorqFeedForward Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwTorqFeedForward As Integer) As Integer

    ' INTERPOLATE and LATCH Command�� Option Field�� Torq Feed Forward�� ���� �о���� �Լ� �Դϴ�.
    ' �⺻���� MAX�� �����Ǿ� �ֽ��ϴ�.
    Public Declare Function  AxmGetTorqFeedForward Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwpTorqFeedForward As Integer) As Integer

    ' INTERPOLATE and LATCH Command�� VFF Field�� Velocity Feed Forward�� ���� ���� �ϵ��� �մϴ�.
    ' �⺻���� '0'�� �����Ǿ� �ֽ��ϴ�.
    ' �������� 0 ~ FFFFH���� ���� �� �� �ֽ��ϴ�.
    Public Declare Function  AxmSetVelocityFeedForward Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwVelocityFeedForward As Integer) As Integer

    ' INTERPOLATE and LATCH Command�� VFF Field�� Velocity Feed Forward�� ���� �о���� �Լ� �Դϴ�.
    Public Declare Function AxmGetVelocityFeedForward Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwpVelocityFeedForward As Integer) As Integer

    ' Encoder type�� �����Ѵ�.
    ' �⺻���� 0(TYPE_INCREMENTAL)�� �����Ǿ� �ֽ��ϴ�.
    ' �������� 0 ~ 1���� ���� �� �� �ֽ��ϴ�.
    ' ������ : 0(TYPE_INCREMENTAL), 1(TYPE_ABSOLUTE).
    Public Declare Function AxmSignalSetEncoderType Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwEncoderType As Integer) As Integer

    ' Encoder type�� Ȯ���Ѵ�.
    Public Declare Function AxmSignalGetEncoderType Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwpEncoderType As Integer) As Integer

    ' Slave Firmware Update�� ���� �߰�
    ' Public Declare Function AxmSetSendAxisCommand Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wCommand As Integer, ByRef wpSendData As Integer, ByVal wLength As Integer) As Integer

    '======== PCI-R1604-RTEX, RTEX-PM ���� �Լ�============================================================== 
    ' ���� �Է� 2,3�� �Է½� JOG ���� �ӵ��� �����Ѵ�. 
    ' ������ ���õ� ��� ����(Ex, PulseOutMethod, MoveUnitPerPulse ��)���� �Ϸ�� ���� �ѹ��� �����Ͽ��� �Ѵ�
    Public Declare Function AxmMotSetUserMotion Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dVelocity As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Integer

    ' ���� �Է� 2,3�� �Է½� JOG ���� ���� ��� ���θ� �����Ѵ�.
    ' ������ :  0(DISABLE), 1(ENABLE
    Public Declare Function AxmMotSetUserMotionUsage Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwUsage As Integer) As Integer

    ' MPGP �Է��� ����Ͽ� Load/UnLoad ��ġ�� �ڵ����� �̵��ϴ� ��� ����.
    Public Declare Function AxmMotSetUserPosMotion Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dVelocity As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal dLoadPos As Double, ByVal dUnLoadPos As Double, ByVal dwFilter As Integer, ByVal dwDelay As Integer) As Integer

    ' MPGP �Է��� ����Ͽ� Load/UnLoad ��ġ�� �ڵ����� �̵��ϴ� ��� ����. 
    ' ������ :  0(DISABLE), 1(Position ��� A ���), 2(Position ��� B ���
    Public Declare Function AxmMotSetUserPosMotionUsage Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwUsage As Integer) As Integer
    '======================================================================================================== 

    '======== SIO-CN2CH, ���� ��ġ Ʈ���� ��� ��� ���� �Լ�================================================
    ' �޸� ������ ���� �Լ�
    Public Declare Function AxcKeWriteRamDataAddr Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwAddr As Integer, ByVal dwData As Integer) As Integer
    ' �޸� ������ �б� �Լ�
    Public Declare Function AxcKeReadRamDataAddr Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwAddr As Integer, ByRef dwpData As Integer) As Integer
    ' �޸� �ʱ�ȭ �Լ�
    Public Declare Function AxcKeResetRamDataAll Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dwData As Integer) As Integer
    ' Ʈ���� Ÿ�� �ƿ� ���� �Լ�
    Public Declare Function AxcTriggerSetTimeout Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwTimeout As Integer) As Integer
    ' Ʈ���� Ÿ�� �ƿ� Ȯ�� �Լ�
    Public Declare Function AxcTriggerGetTimeout Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpTimeout As Integer) As Integer
    ' Ʈ���� ��� ���� Ȯ�� �Լ�
    Public Declare Function AxcStatusGetWaitState Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpState As Integer) As Integer
    ' Ʈ���� ��� ���� ���� �Լ�
    Public Declare Function AxcStatusSetWaitState Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwState As Integer) As Integer
    
    ' ���� ä�ο� ��ɾ� ����.
    Public Declare Function AxcKeSetCommandData32 Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwCommand As Integer, ByVal dwData As Integer) As Integer
    ' ���� ä�ο� ��ɾ� ����.
    Public Declare Function AxcKeSetCommandData16 Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwCommand As Integer, ByVal wData As Integer) As Integer
    ' ���� ä���� �������� Ȯ��.
    Public Declare Function AxcKeGetCommandData32 Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwCommand As Integer, ByRef dwpData As Integer) As Integer
    ' ���� ä���� �������� Ȯ��.
    Public Declare Function AxcKeGetCommandData16 Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwCommand As Integer, ByRef wpData As Integer) As Integer
    
    '========================================================================================================

    '======== PCI-N804/N404 ����, Sequence Motion ===================================================================
    ' Sequence Motion�� �� ������ ���� �մϴ�. (�ּ� 1��)
    ' lSeqMapNo : �� ��ȣ ������ ��� Sequence Motion Index Point
    ' lSeqMapSize : �� ��ȣ ����
    ' long* LSeqAxesNo : �� ��ȣ ��
    Public Declare Function AxmSeqSetAxisMap Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByVal lSeqMapSize As Integer, ByRef lSeqAxesNo As Integer) As Integer
    Public Declare Function AxmSeqGetAxisMap Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByRef lSeqMapSize As Integer, ByRef lSeqAxesNo As Integer) As Integer

    ' Sequence Motion�� ����(Master) ���� ���� �մϴ�. 
    ' �ݵ�� AxmSeqSetAxisMap(...) �� ������ �� ������ �����Ͽ��� �մϴ�
    Public Declare Function AxmSeqSetMasterAxisNo Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByVal lMasterAxisNo As Integer) As Integer

    ' Sequence Motion�� Node ���� ������ ���̺귯���� �˸��ϴ�
    Public Declare Function AxmSeqBeginNode Lib "AXL.dll" (ByVal lSeqMapNo As Integer) As Integer

    ' Sequence Motion�� Node ���� ���Ḧ ���̺귯���� �˸��ϴ�
    Public Declare Function AxmSeqEndNode Lib "AXL.dll" (ByVal lSeqMapNo As Integer) As Integer
    ' Sequence Motion�� ������ ���� �մϴ�
    Public Declare Function AxmSeqStart Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByVal dwStartOption As Integer) As Integer

    ' Sequence Motion�� �� Profile Node ������ ���̺귯���� �Է� �մϴ�.
    ' ���� 1�� Sequence Motion�� ����ϴ���, *dPosition�� 1���� Array�� �����Ͽ� �ֽñ� �ٶ��ϴ�
    Public Declare Function AxmSeqAddNode Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByRef dPosition As Double, ByVal dVelocity As Double, ByVal dAcceleration As Double, ByVal dDeceleration As Double, ByVal dNextVelocity As Double) As Integer

    ' Sequence Motion�� ���� �� ���� ���� ���� Node Index�� �˷� �ݴϴ�
    Public Declare Function AxmSeqGetNodeNum Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByRef lCurNodeNo As Integer) As Integer

    ' Sequence Motion�� �� Node Count�� Ȯ�� �մϴ�
    Public Declare Function AxmSeqGetTotalNodeNum Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByRef lTotalNodeCnt As Integer) As Integer

    ' Sequence Motion�� ���� ���� ������ Ȯ�� �մϴ�.
    ' dwInMotion : 0(���� ����), 1(���� ��)
    Public Declare Function AxmSeqIsMotion Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByRef dwInMotion As Integer) As Integer

    ' Sequence Motion�� Memory�� Clear �մϴ�.
    ' AxmSeqSetAxisMap(...), AxmSeqSetMasterAxisNo(...) ���� ������ ���� �����˴ϴ�
    Public Declare Function AxmSeqWriteClear Lib "AXL.dll" (ByVal lSeqMapNo As Integer) As Integer

    ' Sequence Motion�� ������ ���� �մϴ�.
    ' dwStopMode : 0(EMERGENCY_STOP), 1(SLOWDOWN_STOP)
    Public Declare Function AxmSeqStop Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByVal dwStopMode As Integer) As Integer
    '========================================================================================================

End Module
