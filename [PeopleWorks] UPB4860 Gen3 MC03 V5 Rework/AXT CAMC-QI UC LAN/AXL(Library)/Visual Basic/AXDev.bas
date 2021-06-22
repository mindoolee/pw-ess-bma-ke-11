Attribute VB_Name = "AXDev"

' Board Number�� �̿��Ͽ� Board Address ã��
Public Declare Function AxlGetBoardAddress Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef upBoardAddress As Long) As Long
' Board Number�� �̿��Ͽ� Board ID ã��
Public Declare Function AxlGetBoardID Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef upBoardID As Long) As Long
' Board Number�� �̿��Ͽ� Board Version ã��
Public Declare Function AxlGetBoardVersion Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef upBoardVersion As Long) As Long
' Board Number�� Module Position�� �̿��Ͽ� Module ID ã��
Public Declare Function AxlGetModuleID Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef upModuleID As Long) As Long
' Board Number�� Module Position�� �̿��Ͽ� Module Version ã��
Public Declare Function AxlGetModuleVersion Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef upModuleVersion As Long) As Long
' Board Number�� Module Position�� �̿��Ͽ� Network Node ���� Ȯ��
Public Declare Function AxlGetModuleNodeInfo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef upNetNo As Long, ByRef upNodeAddr As Long) As Long

' Board�� ����� ���� Data Flash Write (PCI-R1604[RTEX master board]����)
' lPageAddr(0 ~ 199)
' lByteNum(1 ~ 120)
' ����) Flash�� ����Ÿ�� ������ ���� ���� �ð�(�ִ� 17mSec)�� �ҿ�Ǳ⶧���� ���� ����� ���� �ð��� �ʿ���.
Public Declare Function AxlSetDataFlash Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lPageAddr As Long, ByVal lBytesNum As Long, ByRef bpSetData As Byte) As Long

' Board�� ����� ���� Data Flash Read(PCI-R1604[RTEX master board]����)
' lPageAddr(0 ~ 199)
' lByteNum(1 ~ 120)
Public Declare Function AxlGetDataFlash Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lPageAddr As Long, ByVal lBytesNum As Long, ByRef bpGetData As Byte) As Long

' Board Number�� Module Position�� �̿��Ͽ� AIO Module Number ã��
Public Declare Function AxaInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef lpModuleNo As Long) As Long
' Board Number�� Module Position�� �̿��Ͽ� DIO Module Number ã��
Public Declare Function AxdInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef lpModuleNo As Long) As Long

' ���� �࿡ IPCOMMAND Setting
Public Declare Function AxmSetCommand Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte) As Long
' ���� �࿡ 8bit IPCOMMAND Setting
Public Declare Function AxmSetCommandData08 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' ���� �࿡ 8bit IPCOMMAND ��������
Public Declare Function AxmGetCommandData08 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef updata As Long) As Long
' ���� �࿡ 16bit IPCOMMAND Setting
Public Declare Function AxmSetCommandData16 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' ���� �࿡ 16bit IPCOMMAND ��������
Public Declare Function AxmGetCommandData16 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef updata As Long) As Long
' ���� �࿡ 24bit IPCOMMAND Setting
Public Declare Function AxmSetCommandData24 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' ���� �࿡ 24bit IPCOMMAND ��������
Public Declare Function AxmGetCommandData24 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef updata As Long) As Long
' ���� �࿡ 32bit IPCOMMAND Setting
Public Declare Function AxmSetCommandData32 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' ���� �࿡ 32bit IPCOMMAND ��������
Public Declare Function AxmGetCommandData32 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef updata As Long) As Long

' ���� �࿡ QICOMMAND Setting
Public Declare Function AxmSetCommandQi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte) As Long
' ���� �࿡ 8bit IPCOMMAND Setting
Public Declare Function AxmSetCommandData08Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' ���� �࿡ 8bit IPCOMMAND ��������
Public Declare Function AxmGetCommandData08Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef updata As Long) As Long
' ���� �࿡ 16bit IPCOMMAND Setting
Public Declare Function AxmSetCommandData16Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' ���� �࿡ 16bit IPCOMMAND ��������
Public Declare Function AxmGetCommandData16Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef updata As Long) As Long
' ���� �࿡ 24bit IPCOMMAND Setting
Public Declare Function AxmSetCommandData24Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' ���� �࿡ 24bit IPCOMMAND ��������
Public Declare Function AxmGetCommandData24Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef updata As Long) As Long
' ���� �࿡ 32bit IPCOMMAND Setting
Public Declare Function AxmSetCommandData32Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' ���� �࿡ 32bit IPCOMMAND ��������
Public Declare Function AxmGetCommandData32Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef updata As Long) As Long

' ���� �࿡ Port Data �������� - SMC-2V03
Public Declare Function AxmGetPortData Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wOffset As Long, ByRef updata As Long) As Long
' ���� �࿡ Port Data Setting - SMC-2V03
Public Declare Function AxmSetPortData Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wOffset As Long, ByRef dwData As Long) As Long
' ���� �࿡ Port Data �������� - PIC-N804/404
Public Declare Function AxmGetPortDataQi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wOffset As Long, ByRef updata As Long) As Long
' ���� �࿡ Port Data Setting - PCI-N804/404
Public Declare Function AxmSetPortDataQi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wOffset As Long, ByRef dwData As Long) As Long

' ���� �࿡ ��ũ��Ʈ�� �����Ѵ�. - IP
' sc    : ��ũ��Ʈ ��ȣ  Lib "AXL.dll" (1 - 4)
' event : �߻��� �̺�Ʈ SCRCON �� �����Ѵ�.
'         �̺�Ʈ ���� �హ������, �̺�Ʈ �߻��� ��, �̺�Ʈ ���� 1,2 �Ӽ� �����Ѵ�.
' cmd   : � ������ �ٲܰ����� ���� SCRCMD�� �����Ѵ�.
' data  : � Data�� �ٲܰ����� ����
Public Declare Function AxmSetScriptCaptionIp Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sc As Long, ByVal event1 As Long, ByVal data As Long) As Long
' ���� �࿡ ��ũ��Ʈ�� ��ȯ�Ѵ�. - IP
Public Declare Function AxmGetScriptCaptionIp Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sc As Long, ByRef event1 As Long, ByRef data As Long) As Long

' ���� �࿡ ��ũ��Ʈ�� �����Ѵ�. - QI
' sc    : ��ũ��Ʈ ��ȣ  Lib "AXL.dll" (1 - 4)
' event : �߻��� �̺�Ʈ SCRCON �� �����Ѵ�.
'         �̺�Ʈ ���� �హ������, �̺�Ʈ �߻��� ��, �̺�Ʈ ���� 1,2 �Ӽ� �����Ѵ�.
' cmd   : � ������ �ٲܰ����� ���� SCRCMD�� �����Ѵ�.
' data  : � Data�� �ٲܰ����� ����
Public Declare Function AxmSetScriptCaptionQi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sc As Long, ByVal event1 As Long, ByVal cmd As Long, ByVal data As Long) As Long
' ���� �࿡ ��ũ��Ʈ�� ��ȯ�Ѵ�. - QI
Public Declare Function AxmGetScriptCaptionQi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sc As Long, ByRef event1 As Long, ByRef cmd As Long, ByRef data As Long) As Long

' ���� �࿡ ��ũ��Ʈ ���� Queue Index�� Clear ��Ų��.
' uSelect IP.
' uSelect Lib "AXL.dll" (0): ��ũ��Ʈ Queue Index �� Clear�Ѵ�.
'         Lib "AXL.dll" (1): ĸ�� Queue�� Index Clear�Ѵ�.

' uSelect QI.
' uSelect Lib "AXL.dll" (0): ��ũ��Ʈ Queue 1 Index �� Clear�Ѵ�.
'         Lib "AXL.dll" (1): ��ũ��Ʈ Queue 2 Index �� Clear�Ѵ�.

Public Declare Function AxmSetScriptCaptionQueueClear Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uSelect As Long) As Long

' ���� �࿡ ��ũ��Ʈ ���� Queue�� Index ��ȯ�Ѵ�.
' uSelect IP
' uSelect Lib "AXL.dll" (0): ��ũ��Ʈ Queue Index�� �о�´�.
'         Lib "AXL.dll" (1): ĸ�� Queue Index�� �о�´�.

' uSelect QI.
' uSelect Lib "AXL.dll" (0): ��ũ��Ʈ Queue 1 Index�� �о�´�.
'         Lib "AXL.dll" (1): ��ũ��Ʈ Queue 2 Index�� �о�´�.

Public Declare Function AxmGetScriptCaptionQueueCount Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef updata As Long, ByVal uSelect As Long) As Long

' ���� �࿡ ��ũ��Ʈ ���� Queue�� Data���� ��ȯ�Ѵ�.
' uSelect IP
' uSelect Lib "AXL.dll" (0): ��ũ��Ʈ Queue Data �� �о�´�.
'         Lib "AXL.dll" (1): ĸ�� Queue Data�� �о�´�.

' uSelect QI.
' uSelect Lib "AXL.dll" (0): ��ũ��Ʈ Queue 1 Data �о�´�.
'         Lib "AXL.dll" (1): ��ũ��Ʈ Queue 2 Data �о�´�.

Public Declare Function AxmGetScriptCaptionQueueDataCount Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef updata As Long, ByVal uSelect As Long) As Long

' ���� ����Ÿ�� �о�´�.
Public Declare Function AxmGetOptimizeDriveData Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dMinVel As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByRef wRangeData As Long, ByRef wStartStopSpeedData As Long, ByRef wObjectSpeedData As Long, ByRef wAccelRate As Long, ByRef wDecelRate As Long) As Long

' ���峻�� �������͸� Byte������ ���� �� Ȯ���Ѵ�.
Public Declare Function AxmBoardWriteByte Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByVal byData As Byte) As Long
Public Declare Function AxmBoardReadByte Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByRef byData As Byte) As Long

' ���峻�� �������͸� Word������ ���� �� Ȯ���Ѵ�.
Public Declare Function AxmBoardWriteWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByVal wData As Long) As Long
Public Declare Function AxmBoardReadWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByRef wData As Long) As Long

' ���峻�� �������͸� DWord������ ���� �� Ȯ���Ѵ�.
Public Declare Function AxmBoardWriteDWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByVal dwData As Long) As Long
Public Declare Function AxmBoardReadDWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByRef dwData As Long) As Long

' ���峻�� ��⿡ �������͸� Byte���� �� Ȯ���Ѵ�.
Public Declare Function AxmModuleWriteByte Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByVal byData As Byte) As Long
Public Declare Function AxmModuleReadByte Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByRef byData As Byte) As Long

' ���峻�� ��⿡ �������͸� Word���� �� Ȯ���Ѵ�.
Public Declare Function AxmModuleWriteWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByVal wData As Long) As Long
Public Declare Function AxmModuleReadWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByRef wData As Long) As Long

' ���峻�� ��⿡ �������͸� DWord���� �� Ȯ���Ѵ�.
Public Declare Function AxmModuleWriteDWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByVal dwData As Long) As Long
Public Declare Function AxmModuleReadDWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByRef dwData As Long) As Long


' �ܺ� ��ġ �񱳱⿡ ���� �����Ѵ�. Lib "AXL.dll" (Pos = Unit)
Public Declare Function AxmStatusSetActComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double) As Long
' �ܺ� ��ġ �񱳱⿡ ���� ��ȯ�Ѵ�. Lib "AXL.dll" (Positon = Unit)
Public Declare Function AxmStatusGetActComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpPos As Double) As Long

' ���� ��ġ �񱳱⿡ ���� �����Ѵ�. Lib "AXL.dll" (Pos = Unit)
Public Declare Function AxmStatusSetCmdComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double) As Long
' ���� ��ġ �񱳱⿡ ���� ��ȯ�Ѵ�. Lib "AXL.dll" (Pos = Unit)
Public Declare Function AxmStatusGetCmdComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpPos As Double) As Long

'========== �߰� �Լ� =========================================================================================================

' ���� ���� �� �ӵ��� ������ ���Ѵ�� �����Ѵ�.
' �ӵ� ������� �Ÿ��� �־��־�� �Ѵ�.
Public Declare Function AxmLineMoveVel Lib "AXL.dll" (ByVal lCoord As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

'========= ���� ��ġ ���� �Լ� Lib "AXL.dll" ( �ʵ�: IP������ , QI���� ��ɾ���)=========================================================================

' ���� ���� Sensor ��ȣ�� ��� ���� �� ��ȣ �Է� ������ �����Ѵ�.
' ��� ���� LOW Lib "AXL.dll" (0), HIGH Lib "AXL.dll" (1), UNUSED Lib "AXL.dll" (2), USED Lib "AXL.dll" (3)
Public Declare Function AxmSensorSetSignal Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uLevel As Long) As Long
' ���� ���� Sensor ��ȣ�� ��� ���� �� ��ȣ �Է� ������ ��ȯ�Ѵ�.
Public Declare Function AxmSensorGetSignal Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upLevel As Long) As Long
' ���� ���� Sensor ��ȣ�� �Է� ���¸� ��ȯ�Ѵ�
Public Declare Function AxmSensorReadSignal Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long

' ���� ���� ������ �ӵ��� �������� ���� ��ġ ����̹��� �����Ѵ�.
' Sensor ��ȣ�� Active level�Է� ���� ��� ��ǥ�� ������ �Ÿ���ŭ ������ �����Ѵ�.
' �޽��� ��µǴ� �������� �Լ��� �����.
' lMethod :  0 - �Ϲ� ����, 1 - ���� ��ȣ ���� ���� ���� ����. ��ȣ ���� �� �Ϲ� ����
'            2 - ���� ����
Public Declare Function AxmSensorMovePos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lMethod As Long) As Long

' ���� ���� ������ �ӵ��� �������� ���� ��ġ ����̹��� �����Ѵ�.
' Sensor ��ȣ�� Active level�Է� ���� ��� ��ǥ�� ������ �Ÿ���ŭ ������ �����Ѵ�.
' �޽� ����� ����Ǵ� �������� �Լ��� �����.
Public Declare Function AxmSensorStartMovePos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lMethod As Long) As Long

' �����˻� ���ེ�� ��ȭ�� ����� ��ȯ�Ѵ�.
' lpStepCount      : ��ϵ� Step�� ����
' upMainStepNumber : ��ϵ� MainStepNumber ������ �迭����Ʈ
' upStepNumber     : ��ϵ� StepNumber ������ �迭����Ʈ
' upStepBranch     : ��ϵ� Step�� Branch ������ �迭����Ʈ
' ����: �迭������ 50���� ����
Public Declare Function AxmHomeGetStepTrace Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpStepCount As Long, ByRef upMainStepNumber As Long, ByRef upStepNumber As Long, ByRef upStepBranch As Long) As Long

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
Public Declare Function AxmHomeSetConfig Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uZphasCount As Long, ByVal lHomeMode As Long, ByVal lClearSet As Long, ByVal dOrgVel As Double, ByVal dLastVel As Double, ByVal dLeavePos As Double) As Long
' ����ڰ� ������ ���� Ȩ���� �Ķ��Ÿ�� ��ȯ�Ѵ�.
Public Declare Function AxmHomeGetConfig Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upZphasCount As Long, ByRef lpHomeMode As Long, ByRef lpClearSet As Long, ByRef dpOrgVel As Double, ByRef dpLastVel As Double, ByRef dpLeavePos As Double) As Long

' ����ڰ� ������ ���� Ȩ ��ġ�� �����Ѵ�.
' lHomeMode ���� ���� : 0 - 5 ����  Lib "AXL.dll" (Move Return�Ŀ� Search��  �����Ѵ�.)
' lHomeMode -1�� �״�� ���� HomeConfig���� ����Ѵ�� �״�� ������.
' ��������      : Vel���� ����̸� CW, �����̸� CCW.
Public Declare Function AxmHomeSetMoveSearch Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

' ����ڰ� ������ ���� Ȩ ������ �����Ѵ�.
' lHomeMode ���� ���� : 0 - 12 ����
' lHomeMode -1�� �״�� ���� HomeConfig���� ����Ѵ�� �״�� ������.
' ��������      : Vel���� ����̸� CW, �����̸� CCW.
Public Declare Function AxmHomeSetMoveReturn Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

' ����ڰ� ������ ���� Ȩ ��Ż�� �����Ѵ�.
' ��������      : Vel���� ����̸� CW, �����̸� CCW.
Public Declare Function AxmHomeSetMoveLeave Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

' ����ڰ� ������ ������ Ȩ ��ġ�� �����Ѵ�.
' lHomeMode ���� ���� : 0 - 5 ����  Lib "AXL.dll" (Move Return�Ŀ� Search��  �����Ѵ�.)
' lHomeMode -1�� �״�� ���� HomeConfig���� ����Ѵ�� �״�� ������.
' ��������      : Vel���� ����̸� CW, �����̸� CCW.
Public Declare Function AxmHomeSetMultiMoveSearch Lib "AXL.dll" (ByVal lArraySize As Long, ByRef lpAxesNo As Long, ByRef dpVel As Double, ByRef dpAccel As Double, ByRef dpDecel As Double) As Long

'������ ��ǥ���� ���� �ӵ� �������� ��带 �����Ѵ�.
'  Lib "AXL.dll" (������ : �ݵ�� ����� �ϰ� ��밡��)
' ProfileMode : '0' - ��Ī Trapezode
'               '1' - ���Ī Trapezode
'               '2' - ��Ī Quasi-S Curve
'               '3' - ��Ī S Curve
'               '4' - ���Ī S Curve
Public Declare Function AxmContiSetProfileMode Lib "AXL.dll" (ByVal lCoord As Long, ByVal uProfileMode As Long) As Long
' ������ ��ǥ���� ���� �ӵ� �������� ��带 ��ȯ�Ѵ�.
Public Declare Function AxmContiGetProfileMode Lib "AXL.dll" (ByVal lCoord As Long, ByRef upProfileMode As Long) As Long

'========== DIO ���ͷ�Ʈ �÷��� ������Ʈ �б�
' ������ �Է� ���� ���, Interrupt Flag Register�� Offset ��ġ���� bit ������ ���ͷ�Ʈ �߻� ���� ���� ����
Public Declare Function AxdiInterruptFlagReadBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long
' ������ �Է� ���� ���, Interrupt Flag Register�� Offset ��ġ���� byte ������ ���ͷ�Ʈ �߻� ���� ���� ����
Public Declare Function AxdiInterruptFlagReadByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long
' ������ �Է� ���� ���, Interrupt Flag Register�� Offset ��ġ���� word ������ ���ͷ�Ʈ �߻� ���� ���� ����
Public Declare Function AxdiInterruptFlagReadWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long
' ������ �Է� ���� ���, Interrupt Flag Register�� Offset ��ġ���� double word ������ ���ͷ�Ʈ �߻� ���� ���� ����
Public Declare Function AxdiInterruptFlagReadDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long
' ��ü �Է� ���� ���, Interrupt Flag Register�� Offset ��ġ���� bit ������ ���ͷ�Ʈ �߻� ���� ���� ����
Public Declare Function AxdiInterruptFlagRead Lib "AXL.dll" (ByVal lOffset As Long, ByRef upValue As Long) As Long

'========= �α� ���� �Լ� ==========================================================================================
' ���� �ڵ����� ������.
' ���� ���� �Լ� ���� ����� EzSpy���� ����͸� �� �� �ֵ��� ���� �Ǵ� �����ϴ� �Լ��̴�.
' uUse : ��� ���� => DISABLE Lib "AXL.dll" (0), ENABLE Lib "AXL.dll" (1)
Public Declare Function AxmLogSetAxis Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uUse As Long) As Long

' EzSpy������ ���� �� �Լ� ���� ��� ����͸� ���θ� Ȯ���ϴ� �Լ��̴�.
Public Declare Function AxmLogGetAxis Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upUse As Long) As Long

'=========== �α� ��� ���� �Լ�
'������ �Է� ä���� EzSpy�� �α� ��� ���θ� �����Ѵ�.
Public Declare Function AxaiLogSetChannel Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal uUse As Long) As Long
'������ �Է� ä���� EzSpy�� �α� ��� ���θ� Ȯ���Ѵ�.
Public Declare Function AxaiLogGetChannel Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef upUse As Long) As Long

'==������ ��� ä���� EzSpy �α� ���
'������ ��� ä���� EzSpy�� �α� ��� ���θ� �����Ѵ�.
Public Declare Function AxaoLogSetChannel Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal uUse As Long) As Long
'������ ��� ä���� EzSpy�� �α� ��� ���θ� Ȯ���Ѵ�.
Public Declare Function AxaoLogGetChannel Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef upUse As Long) As Long

'==Log
' ������ ����� EzSpy�� �α� ��� ���� ����
Public Declare Function AxdLogSetModule Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal uUse As Long) As Long
' ������ ����� EzSpy�� �α� ��� ���� Ȯ��
Public Declare Function AxdLogGetModule Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef upUse As Long) As Long

' ������ ���尡 RTEX ����� �� �� ������ firmware ������ Ȯ���Ѵ�.
Public Declare Function AxlGetFirmwareVersion Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal szVersion As String) As Long
' ������ ����� Firmware�� ���� �Ѵ�.
Public Declare Function AxlSetFirmwareCopy Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef wData As Long, ByRef wCmdData As Long) As Long
' ������ ����� Firmware Update�� �����Ѵ�.
Public Declare Function AxlSetFirmwareUpdate Lib "AXL.dll" (ByVal lBoardNo As Long) As Long
' ������ ������ ���� RTEX �ʱ�ȭ ���¸� Ȯ�� �Ѵ�.
Public Declare Function AxlCheckStatus Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef dwStatus As Long) As Long
' ������ �࿡ RTEX Master board�� ���� ����� ���� �մϴ�.
Public Declare Function AxlRtexUniversalCmd Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wCmd As Long, ByVal wOffset As Long, ByRef wData As Long) As Long
' ������ ���� RTEX ��� ����� �����Ѵ�.
Public Declare Function AxmRtexSlaveCmd Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwCmdCode As Long, ByVal dwTypeCode As Long, ByVal dwIndexCode As Long, ByVal dwCmdConfigure As Long, ByVal dwValue As Long) As Long
' ������ �࿡ ������ RTEX ��� ����� ������� Ȯ���Ѵ�.
Public Declare Function AxmRtexGetSlaveCmdResult Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwIndex As Long, ByRef dwValue As Long) As Long
' ������ �࿡ RTEX ���� ������ Ȯ���Ѵ�.
Public Declare Function AxmRtexGetAxisStatus Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwStatus As Long) As Long
' ������ �࿡ RTEX ��� ���� ������ Ȯ���Ѵ�. Lib "AXL.dll" (Actual position, Velocity, Torque)
Public Declare Function AxmRtexGetAxisReturnData Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwReturn1 As Long, ByRef dwReturn2 As Long, ByRef dwReturn3 As Long) As Long
' ������ �࿡ RTEX Slave ���� ���� ���� ������ Ȯ���Ѵ�. Lib "AXL.dll" (mechanical, Inposition and etc)
Public Declare Function AxmRtexGetAxisSlaveStatus Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwStatus As Long) As Long

' ������ �࿡ MLII Slave �࿡ ���� ��Ʈ�� ��ɾ �����Ѵ�.
Public Declare Function AxmSetAxisCmd Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef tagCommand As Long) As Long
' ������ �࿡ MLII Slave �࿡ ���� ��Ʈ�� ����� ����� Ȯ���Ѵ�.
Public Declare Function AxmGetAxisCmdResult Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef tagCommand As Long) As Long

Public Declare Function AxlGetDpRamData Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wAddress As Long, ByRef dwpRdData As Long) As Long
Public Declare Function AxlBoardReadDpramWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByRef dwpRdData As Long) As Long

Public Declare Function AxlSetSendBoardCommand Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal dwCommand As Long, ByRef dwpSendData As Long, ByVal dwLength As Long) As Long
Public Declare Function AxlGetResponseBoardCommand Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef dwpReadData As Long) As Long

' Network Type Master ���忡�� Slave ���� Firmware Version�� �о� ���� �Լ�.
' ucaFirmwareVersion unsigned char ���� Array�� �����ϰ� ũ�Ⱑ 4�̻��� �ǵ��� ���� �ؾ� �Ѵ�.
Public Declare Function AxmInfoGetFirmwareVersion Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef ucaFirmwareVersion As Long) As Long
Public Declare Function AxaInfoGetFirmwareVersion Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef ucaFirmwareVersion As Long) As Long
Public Declare Function AxdInfoGetFirmwareVersion Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef ucaFirmwareVersion As Long) As Long

'======== PCI-R1604-MLII ���� �Լ�=========================================================================== 
' INTERPOLATE and LATCH Command�� Option Field�� Torq Feed Forward�� ���� ���� �ϵ��� �մϴ�.
' �⺻���� MAX�� �����Ǿ� �ֽ��ϴ�.
' �������� 0 ~ 4000H���� ���� �� �� �ֽ��ϴ�.
' �������� 4000H�̻����� �����ϸ� ������ �� �̻����� �����ǳ� ������ 4000H���� ���� �˴ϴ�.
Public Declare Function  AxmSetTorqFeedForward Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwTorqFeedForward As Long) As Long

' INTERPOLATE and LATCH Command�� Option Field�� Torq Feed Forward�� ���� �о���� �Լ� �Դϴ�.
' �⺻���� MAX�� �����Ǿ� �ֽ��ϴ�.
Public Declare Function  AxmGetTorqFeedForward Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpTorqFeedForward As Long) As Long

' INTERPOLATE and LATCH Command�� VFF Field�� Velocity Feed Forward�� ���� ���� �ϵ��� �մϴ�.
' �⺻���� '0'�� �����Ǿ� �ֽ��ϴ�.
' �������� 0 ~ FFFFH���� ���� �� �� �ֽ��ϴ�.
Public Declare Function  AxmSetVelocityFeedForward Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwVelocityFeedForward As Long) As Long

' INTERPOLATE and LATCH Command�� VFF Field�� Velocity Feed Forward�� ���� �о���� �Լ� �Դϴ�.
Public Declare Function  AxmGetVelocityFeedForward Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpVelocityFeedForward As Long) As Long

' Encoder type�� �����Ѵ�.
' �⺻���� 0(TYPE_INCREMENTAL)�� �����Ǿ� �ֽ��ϴ�.
' �������� 0 ~ 1���� ���� �� �� �ֽ��ϴ�.
' ������ : 0(TYPE_INCREMENTAL), 1(TYPE_ABSOLUTE).
Public Declare Function AxmSignalSetEncoderType Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwEncoderType As Long) As Long

' Encoder type�� Ȯ���Ѵ�.
Public Declare Function AxmSignalGetEncoderType Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpEncoderType As Long) As Long

' Slave Firmware Update�� ���� �߰�
' Public Declare Function AxmSetSendAxisCommand Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wCommand As Long, ByRef wpSendData As Long, ByVal wLength As Long) As Long


'======== PCI-R1604-RTEX, RTEX-PM ���� �Լ�============================================================== 
' ���� �Է� 2,3�� �Է½� JOG ���� �ӵ��� �����Ѵ�. 
' ������ ���õ� ��� ����(Ex, PulseOutMethod, MoveUnitPerPulse ��)���� �Ϸ�� ���� �ѹ��� �����Ͽ��� �Ѵ�
Public Declare Function AxmMotSetUserMotion Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVelocity As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

' ���� �Է� 2,3�� �Է½� JOG ���� ���� ��� ���θ� �����Ѵ�.
' ������ :  0(DISABLE), 1(ENABLE
Public Declare Function AxmMotSetUserMotionUsage Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwUsage As Long) As Long

' MPGP �Է��� ����Ͽ� Load/UnLoad ��ġ�� �ڵ����� �̵��ϴ� ��� ����.
Public Declare Function AxmMotSetUserPosMotion Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVelocity As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal dLoadPos As Double, ByVal dUnLoadPos As Double, ByVal dwFilter As Long, ByVal dwDelay As Long) As Long

' MPGP �Է��� ����Ͽ� Load/UnLoad ��ġ�� �ڵ����� �̵��ϴ� ��� ����. 
' ������ :  0(DISABLE), 1(Position ��� A ���), 2(Position ��� B ���
Public Declare Function AxmMotSetUserPosMotionUsage Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwUsage As Long) As Long
'======================================================================================================== 

'======== SIO-CN2CH, ���� ��ġ Ʈ���� ��� ��� ���� �Լ�================================================
' �޸� ������ ���� �Լ�
Public Declare Function AxcKeWriteRamDataAddr Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwAddr As Long, ByVal dwData As Long) As Long
' �޸� ������ �б� �Լ�
Public Declare Function AxcKeReadRamDataAddr Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwAddr As Long, ByRef dwpData As Long) As Long
' �޸� �ʱ�ȭ �Լ�
Public Declare Function AxcKeResetRamDataAll Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dwData As Long) As Long
' Ʈ���� Ÿ�� �ƿ� ���� �Լ�
Public Declare Function AxcTriggerSetTimeout Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwTimeout As Long) As Long
' Ʈ���� Ÿ�� �ƿ� Ȯ�� �Լ�
Public Declare Function AxcTriggerGetTimeout Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dwpTimeout As Long) As Long
' Ʈ���� ��� ���� Ȯ�� �Լ�
Public Declare Function AxcStatusGetWaitState Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dwpState As Long) As Long
' Ʈ���� ��� ���� ���� �Լ�
Public Declare Function AxcStatusSetWaitState Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwState As Long) As Long

' ���� ä�ο� ��ɾ� ����.
Public Declare Function AxcKeSetCommandData32 Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwCommand As Long, ByVal dwData As Long) As Long
' ���� ä�ο� ��ɾ� ����.
Public Declare Function AxcKeSetCommandData16 Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwCommand As Long, ByVal wData As Long) As Long
' ���� ä���� �������� Ȯ��.
Public Declare Function AxcKeGetCommandData32 Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwCommand As Long, ByRef dwpData As Long) As Long
' ���� ä���� �������� Ȯ��.
Public Declare Function AxcKeGetCommandData16 Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwCommand As Long, ByRef wpData As Long) As Long
'========================================================================================================

'======== PCI-N804/N404 ����, Sequence Motion ===================================================================
' Sequence Motion�� �� ������ ���� �մϴ�. (�ּ� 1��)
' lSeqMapNo : �� ��ȣ ������ ��� Sequence Motion Index Point
' lSeqMapSize : �� ��ȣ ����
' long* LSeqAxesNo : �� ��ȣ ��
Public Declare Function AxmSeqSetAxisMap Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByVal lSeqMapSize As Long, ByRef lSeqAxesNo As Long) As Long
Public Declare Function AxmSeqGetAxisMap Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByRef lSeqMapSize As Long, ByRef lSeqAxesNo As Long) As Long

' Sequence Motion�� ����(Master) ���� ���� �մϴ�. 
' �ݵ�� AxmSeqSetAxisMap(...) �� ������ �� ������ �����Ͽ��� �մϴ�
Public Declare Function AxmSeqSetMasterAxisNo Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByVal lMasterAxisNo As Long) As Long

' Sequence Motion�� Node ���� ������ ���̺귯���� �˸��ϴ�
Public Declare Function AxmSeqBeginNode Lib "AXL.dll" (ByVal lSeqMapNo) As Long

' Sequence Motion�� Node ���� ���Ḧ ���̺귯���� �˸��ϴ�
Public Declare Function AxmSeqEndNode Lib "AXL.dll" (ByVal lSeqMapNo) As Long
' Sequence Motion�� ������ ���� �մϴ�
Public Declare Function AxmSeqStart Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByVal dwStartOption As Long) As Long

' Sequence Motion�� �� Profile Node ������ ���̺귯���� �Է� �մϴ�.
' ���� 1�� Sequence Motion�� ����ϴ���, *dPosition�� 1���� Array�� �����Ͽ� �ֽñ� �ٶ��ϴ�
Public Declare Function AxmSeqAddNode Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByRef dPosition As Double, ByVal dVelocity As Double, ByVal dAcceleration As Double, ByVal dDeceleration As Double, ByVal dNextVelocity As Double) As Long

' Sequence Motion�� ���� �� ���� ���� ���� Node Index�� �˷� �ݴϴ�
Public Declare Function AxmSeqGetNodeNum Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByRef lCurNodeNo As Long) As Long

' Sequence Motion�� �� Node Count�� Ȯ�� �մϴ�
Public Declare Function AxmSeqGetTotalNodeNum Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByRef lTotalNodeCnt As Long) As Long

' Sequence Motion�� ���� ���� ������ Ȯ�� �մϴ�.
' dwInMotion : 0(���� ����), 1(���� ��)
Public Declare Function AxmSeqIsMotion Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByRef dwInMotion As Long) As Long

' Sequence Motion�� Memory�� Clear �մϴ�.
' AxmSeqSetAxisMap(...), AxmSeqSetMasterAxisNo(...) ���� ������ ���� �����˴ϴ�
Public Declare Function AxmSeqWriteClear Lib "AXL.dll" (ByVal lSeqMapNo) As Long

' Sequence Motion�� ������ ���� �մϴ�.
' dwStopMode : 0(EMERGENCY_STOP), 1(SLOWDOWN_STOP)
Public Declare Function AxmSeqStop Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByVal dwStopMode As Long) As Long
'========================================================================================================