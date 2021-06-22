unit AXDev;

interface

uses Windows, Messages, AXHD;

// Board Number�� �̿��Ͽ� Board Address ã��
function AxlGetBoardAddress (lBoardNo : LongInt; upBoardAddress : PDWord) : DWord; stdcall;
// Board Number�� �̿��Ͽ� Board ID ã��
function AxlGetBoardID (lBoardNo : LongInt; upBoardID : PDWord) : DWord; stdcall;
// Board Number�� �̿��Ͽ� Board Version ã��
function AxlGetBoardVersion (lBoardNo : LongInt; upBoardVersion : PDWord) : DWord; stdcall;
// Board Number�� Module Position�� �̿��Ͽ� Module ID ã��
function AxlGetModuleID (lBoardNo : LongInt; lModulePos : LongInt; upModuleID : PDWord) : DWord; stdcall;
// Board Number�� Module Position�� �̿��Ͽ� Module Version ã��
function AxlGetModuleVersion (lBoardNo : LongInt; lModulePos : LongInt; upModuleVersion : PDWord) : DWord; stdcall;
// Board Number�� Module Position�� �̿��Ͽ� Network Node ���� Ȯ��
function AxlGetModuleNodeInfo(lBoardNo : LongInt; lModulePos : LongInt; lpNetNo : PLongInt; upNodeAddr : PDWord) : DWord; stdcall;

// Board�� ����� ���� Data Flash Write (PCI-R1604[RTEX master board]����)
// lPageAddr(0 ~ 199)
// lByteNum(1 ~ 120)
// ����) Flash�� ����Ÿ�� ������ ���� ���� �ð�(�ִ� 17mSec)�� �ҿ�Ǳ⶧���� ���� ����� ���� �ð��� �ʿ���.
function AxlSetDataFlash (lBoardNo : LongInt; lPageAddr : LongInt; lBytesNum : LongInt; bpSetData : PByte) : DWord; stdcall;
// Board�� ����� ���� Data Flash Read(PCI-R1604[RTEX master board]����)
// lPageAddr(0 ~ 199)
// lByteNum(1 ~ 120)
function AxlGetDataFlash (lBoardNo : LongInt; lPageAddr : LongInt; lBytesNum : LongInt; bpSetData : PByte) : DWord; stdcall;

// Board Number�� Module Position�� �̿��Ͽ� AIO Module Number ã��
function AxaInfoGetModuleNo (lBoardNo : LongInt; lModulePos : LongInt; lpModuleNo : PLongInt) : DWord; stdcall;
// Board Number�� Module Position�� �̿��Ͽ� DIO Module Number ã��
function AxdInfoGetModuleNo (lBoardNo : LongInt; lModulePos : LongInt; lpModuleNo : PLongInt) : DWord; stdcall;

// ���� �࿡ IPCOMMAND Setting
function AxmSetCommand (lAxisNo : LongInt; sCommand : Byte) : DWord; stdcall;
// ���� �࿡ 8bit IPCOMMAND Setting
function AxmSetCommandData08 (lAxisNo : LongInt; sCommand : Byte; uData : DWord) : DWord; stdcall;
// ���� �࿡ 8bit IPCOMMAND ��������
function AxmGetCommandData08 (lAxisNo : LongInt; sCommand : Byte; upData : PDWord) : DWord; stdcall;
// ���� �࿡ 16bit IPCOMMAND Setting
function AxmSetCommandData16 (lAxisNo : LongInt; sCommand : Byte; uData : DWord) : DWord; stdcall;
// ���� �࿡ 16bit IPCOMMAND ��������
function AxmGetCommandData16 (lAxisNo : LongInt; sCommand : Byte; upData : PDWord) : DWord; stdcall;
// ���� �࿡ 24bit IPCOMMAND Setting
function AxmSetCommandData24 (lAxisNo : LongInt; sCommand : Byte; uData : DWord) : DWord; stdcall;
// ���� �࿡ 24bit IPCOMMAND ��������
function AxmGetCommandData24 (lAxisNo : LongInt; sCommand : Byte; upData : PDWord) : DWord; stdcall;
// ���� �࿡ 32bit IPCOMMAND Setting
function AxmSetCommandData32 (lAxisNo : LongInt; sCommand : Byte; uData : DWord) : DWord; stdcall;
// ���� �࿡ 32bit IPCOMMAND ��������
function AxmGetCommandData32 (lAxisNo : LongInt; sCommand : Byte; upData : PDWord) : DWord; stdcall;

// ���� �࿡ QICOMMAND Setting
function AxmSetCommandQi (lAxisNo : LongInt; sCommand : Byte) : DWord; stdcall;
// ���� �࿡ 8bit IPCOMMAND Setting
function AxmSetCommandData08Qi (lAxisNo : LongInt; sCommand : Byte; uData : DWord) : DWord; stdcall;
// ���� �࿡ 8bit IPCOMMAND ��������
function AxmGetCommandData08Qi (lAxisNo : LongInt; sCommand : Byte; upData : PDWord) : DWord; stdcall;
// ���� �࿡ 16bit IPCOMMAND Setting
function AxmSetCommandData16Qi (lAxisNo : LongInt; sCommand : Byte; uData : DWord) : DWord; stdcall;
// ���� �࿡ 16bit IPCOMMAND ��������
function AxmGetCommandData16Qi (lAxisNo : LongInt; sCommand : Byte; upData : PDWord) : DWord; stdcall;
// ���� �࿡ 24bit IPCOMMAND Setting
function AxmSetCommandData24Qi (lAxisNo : LongInt; sCommand : Byte; uData : DWord) : DWord; stdcall;
// ���� �࿡ 24bit IPCOMMAND ��������
function AxmGetCommandData24Qi (lAxisNo : LongInt; sCommand : Byte; upData : PDWord) : DWord; stdcall;
// ���� �࿡ 32bit IPCOMMAND Setting
function AxmSetCommandData32Qi (lAxisNo : LongInt; sCommand : Byte; uData : DWord) : DWord; stdcall;
// ���� �࿡ 32bit IPCOMMAND ��������
function AxmGetCommandData32Qi (lAxisNo : LongInt; sCommand : Byte; upData : PDWord) : DWord; stdcall;

// ���� �࿡ Port Data �������� - IP
function AxmGetPortData(lAxisNo : LongInt; wOffset : WORD; upData : PDWord) : DWord; stdcall;
// ���� �࿡ Port Data Setting - IP
function AxmSetPortData(lAxisNo : LongInt; wOffset : WORD; uData : DWord) : DWord; stdcall;

// ���� �࿡ Port Data �������� - QI
function AxmGetPortDataQi(lAxisNo : LongInt; wOffset : WORD; upData : PDWord) : DWord; stdcall;
// ���� �࿡ Port Data Setting - QI
function AxmSetPortDataQi(lAxisNo : LongInt; wOffset : WORD; uData : DWord) : DWord; stdcall;

// ���� �࿡ ��ũ��Ʈ�� �����Ѵ�. - IP
// sc    : ��ũ��Ʈ ��ȣ (1 - 4)
// event : �߻��� �̺�Ʈ SCRCON �� �����Ѵ�.
//         �̺�Ʈ ���� �హ������, �̺�Ʈ �߻��� ��, �̺�Ʈ ���� 1,2 �Ӽ� �����Ѵ�.
// cmd   : � ������ �ٲܰ����� ���� SCRCMD�� �����Ѵ�.
// data  : � Data�� �ٲܰ����� ����
function AxmSetScriptCaptionIp(lAxisNo : LongInt; sc : LongInt; event : DWord; data : DWord) : DWord; stdcall;
// ���� �࿡ ��ũ��Ʈ�� ��ȯ�Ѵ�. - IP
function AxmGetScriptCaptionIp(lAxisNo : LongInt; sc : LongInt; event : PDWord; data : PDWord) : DWord; stdcall;

// ���� �࿡ ��ũ��Ʈ�� �����Ѵ�. - QI
// sc    : ��ũ��Ʈ ��ȣ (1 - 4)
// event : �߻��� �̺�Ʈ SCRCON �� �����Ѵ�.
//         �̺�Ʈ ���� �హ������, �̺�Ʈ �߻��� ��, �̺�Ʈ ���� 1,2 �Ӽ� �����Ѵ�.
// cmd   : � ������ �ٲܰ����� ���� SCRCMD�� �����Ѵ�.
// data  : � Data�� �ٲܰ����� ����
function AxmSetScriptCaptionQi(lAxisNo : LongInt; sc : LongInt; event : DWord; cmd : DWord; data : DWord) : DWord; stdcall;
// ���� �࿡ ��ũ��Ʈ�� ��ȯ�Ѵ�. - QI
function AxmGetScriptCaptionQi(lAxisNo : LongInt; sc : LongInt; event : PDWord; cmd : PDWord; data : PDWord) : DWord; stdcall;

// ���� �࿡ ��ũ��Ʈ ���� Queue Index�� Clear ��Ų��.
// uSelect IP. 
// uSelect(0): ��ũ��Ʈ Queue Index �� Clear�Ѵ�.
//        (1): ĸ�� Queue�� Index Clear�Ѵ�.

// uSelect QI. 
// uSelect(0): ��ũ��Ʈ Queue 1 Index �� Clear�Ѵ�.
//        (1): ��ũ��Ʈ Queue 2 Index �� Clear�Ѵ�.

function AxmSetScriptCaptionQueueClear(lAxisNo : LongInt; uSelect : DWord) : DWord; stdcall;

// ���� �࿡ ��ũ��Ʈ ���� Queue�� Index ��ȯ�Ѵ�. 
// uSelect IP
// uSelect(0): ��ũ��Ʈ Queue Index�� �о�´�.
//        (1): ĸ�� Queue Index�� �о�´�.

// uSelect QI. 
// uSelect(0): ��ũ��Ʈ Queue 1 Index�� �о�´�.
//        (1): ��ũ��Ʈ Queue 2 Index�� �о�´�.
function AxmGetScriptCaptionQueueCount(lAxisNo : LongInt; updata : PDWord; uSelect : DWord) : DWord; stdcall;

// ���� �࿡ ��ũ��Ʈ ���� Queue�� Data���� ��ȯ�Ѵ�. 
// uSelect IP
// uSelect(0): ��ũ��Ʈ Queue Data �� �о�´�.
//        (1): ĸ�� Queue Data�� �о�´�.

// uSelect QI.
// uSelect(0): ��ũ��Ʈ Queue 1 Data �о�´�.
//        (1): ��ũ��Ʈ Queue 2 Data �о�´�.
function AxmGetScriptCaptionQueueDataCount(lAxisNo : LongInt; updata : PDWord; uSelect : DWord) : DWord; stdcall;

// ���� ����Ÿ�� �о�´�.
function AxmGetOptimizeDriveData(lAxisNo : LongInt; dMinVel : Double; dVel : Double; dAccel : Double; dDecel : Double; 
        wRangeData : PWord; wStartStopSpeedData : PWord; wObjectSpeedData : PWord; wAccelRate : PWord; wDecelRate : PWord) : DWord; stdcall;

// ���峻�� �������͸� Byte������ ���� �� Ȯ���Ѵ�.
function AxmBoardWriteByte(lBoardNo : LongInt; wOffset : Word; byData : Byte) : DWord; stdcall;
function AxmBoardReadByte(lBoardNo : LongInt; wOffset : Word; byData : PByte) : DWord; stdcall;

// ���峻�� �������͸� Word������ ���� �� Ȯ���Ѵ�.
function AxmBoardWriteWord(lBoardNo : LongInt; wOffset : Word; wData : Word) : DWord; stdcall;
function AxmBoardReadWord(lBoardNo : LongInt; wOffset : Word; wData : PWord) : DWord; stdcall;

// ���峻�� �������͸� DWord������ ���� �� Ȯ���Ѵ�.
function AxmBoardWriteDWord(lBoardNo : LongInt; wOffset : Word; dwData : DWord) : DWord; stdcall;
function AxmBoardReadDWord(lBoardNo : LongInt; wOffset : Word; dwData : PDWord) : DWord; stdcall;

// ���峻�� ��⿡ �������͸� Byte���� �� Ȯ���Ѵ�.
function AxmModuleWriteByte(lBoardNo : LongInt; lModulePos : LongInt; wOffset : Word; byData : Byte) : DWord; stdcall;
function AxmModuleReadByte(lBoardNo : LongInt; lModulePos : LongInt; wOffset : Word; byData : PByte) : DWord; stdcall;

// ���峻�� ��⿡ �������͸� Word���� �� Ȯ���Ѵ�.
function AxmModuleWriteWord(lBoardNo : LongInt; lModulePos : LongInt; wOffset : Word; wData : Word) : DWord; stdcall;
function AxmModuleReadWord(lBoardNo : LongInt; lModulePos : LongInt; wOffset : Word; wData : PWord) : DWord; stdcall;

// ���峻�� ��⿡ �������͸� DWord���� �� Ȯ���Ѵ�.
function AxmModuleWriteDWord(lBoardNo : LongInt; lModulePos : LongInt; wOffset : Word; dwData : DWord) : DWord; stdcall;
function AxmModuleReadDWord(lBoardNo : LongInt; lModulePos : LongInt; wOffset : Word; dwData : PDWord) : DWord; stdcall;

// �ܺ� ��ġ �񱳱⿡ ���� �����Ѵ�.(Pos = Unit)
function AxmStatusSetActComparatorPos(lAxisNo : LongInt; dPos : Double) : DWord; stdcall;
// �ܺ� ��ġ �񱳱⿡ ���� ��ȯ�Ѵ�.(Positon = Unit)
function AxmStatusGetActComparatorPos(lAxisNo : LongInt; dpPos : PDouble) : DWord; stdcall;

// ���� ��ġ �񱳱⿡ ���� �����Ѵ�.(Pos = Unit)
function AxmStatusSetCmdComparatorPos(lAxisNo : LongInt; dPos : Double) : DWord; stdcall;
// ���� ��ġ �񱳱⿡ ���� ��ȯ�Ѵ�.(Pos = Unit)
function AxmStatusGetCmdComparatorPos(lAxisNo : LongInt; dpPos : PDouble) : DWord; stdcall;

//======= �߰� �Լ� =========================================================================================================

// ���� ���� �� �ӵ��� ������ ���Ѵ�� �����Ѵ�.
// �ӵ� ������� �Ÿ��� �־��־�� �Ѵ�. 
function AxmLineMoveVel(lCoord : LongInt; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;

//========= ���� ��ġ ���� �Լ�( �ʵ�: IP������ , QI���� ��ɾ���)=========================================================================

// ���� ���� Sensor ��ȣ�� ��� ���� �� ��ȣ �Է� ������ �����Ѵ�.
// ��� ���� LOW(0), HIGH(1), UNUSED(2), USED(3)
function AxmSensorSetSignal(lAxisNo : LongInt; uLevel : DWord) : DWord; stdcall;
// ���� ���� Sensor ��ȣ�� ��� ���� �� ��ȣ �Է� ������ ��ȯ�Ѵ�.
function AxmSensorGetSignal(lAxisNo : LongInt; upLevel : PDWord) : DWord; stdcall;
// ���� ���� Sensor ��ȣ�� �Է� ���¸� ��ȯ�Ѵ�
function AxmSensorReadSignal(lAxisNo : LongInt; upStatus : PDWord) : DWord; stdcall;

// ���� ���� ������ �ӵ��� �������� ���� ��ġ ����̹��� �����Ѵ�.
// Sensor ��ȣ�� Active level�Է� ���� ��� ��ǥ�� ������ �Ÿ���ŭ ������ �����Ѵ�.
// �޽��� ��µǴ� �������� �Լ��� �����.
// lMethod :  0 - �Ϲ� ����, 1 - ���� ��ȣ ���� ���� ���� ����. ��ȣ ���� �� �Ϲ� ����
//            2 - ���� ����
function AxmSensorMovePos(lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double; lMethod : LongInt) : DWord; stdcall;

// ���� ���� ������ �ӵ��� �������� ���� ��ġ ����̹��� �����Ѵ�.
// Sensor ��ȣ�� Active level�Է� ���� ��� ��ǥ�� ������ �Ÿ���ŭ ������ �����Ѵ�.
// �޽� ����� ����Ǵ� �������� �Լ��� �����.
function AxmSensorStartMovePos(lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double; lMethod : LongInt) : DWord; stdcall;

// �����˻� ���ེ�� ��ȭ�� ����� ��ȯ�Ѵ�.
// lpStepCount      : ��ϵ� Step�� ����
// upMainStepNumber : ��ϵ� MainStepNumber ������ �迭����Ʈ
// upStepNumber     : ��ϵ� StepNumber ������ �迭����Ʈ
// upStepBranch     : ��ϵ� Step�� Branch ������ �迭����Ʈ
// ����: �迭������ 50���� ����
function AxmHomeGetStepTrace(lAxisNo : LongInt; lpStepCount : PLongInt; upMainStepNumber : PDWord; upStepNumber : PDWord; upStepBranch : PDWord) : DWord; stdcall;

//=======�߰� Ȩ ��ġ (PI-N804/404���� �ش��.)=================================================================================
// ����ڰ� ������ ���� Ȩ���� �Ķ��Ÿ�� �����Ѵ�.(QIĨ ���� �������� �̿�).
// uZphasCount : Ȩ �Ϸ��Ŀ� Z�� ī��Ʈ(0 - 15)
// lHomeMode   : Ȩ ���� ���( 0 - 12)
// lClearSet   : ��ġ Ŭ���� , �ܿ��޽� Ŭ���� ��� ���� (0 - 3)
//               0: ��ġŬ���� ������, �ܿ��޽� Ŭ���� ��� ����
//                 1: ��ġŬ���� �����, �ܿ��޽� Ŭ���� ��� ����
//               2: ��ġŬ���� ������, �ܿ��޽� Ŭ���� �����
//               3: ��ġŬ���� �����, �ܿ��޽� Ŭ���� �����.
// dOrgVel : Ȩ���� Org  Speed ���� 
// dLastVel: Ȩ���� Last Speed ���� 
function AxmHomeSetConfig(lAxisNo : LongInt; uZphasCount : DWord; lHomeMode : LongInt; lClearSet : LongInt; dOrgVel : Double; dLastVel : Double; dLeavePos : Double) : DWord; stdcall;
// ����ڰ� ������ ���� Ȩ���� �Ķ��Ÿ�� ��ȯ�Ѵ�.
function AxmHomeGetConfig(lAxisNo : LongInt; upZphasCount : PDword; lpHomeMode : PLongInt; lpClearSet : PLongInt; dpOrgVel : PDouble; dpLastVel : PDouble; dpLeavePos : PDouble) : DWord; stdcall;

// ����ڰ� ������ ���� Ȩ ��ġ�� �����Ѵ�.
// lHomeMode ���� ���� : 0 - 5 ���� (Move Return�Ŀ� Search��  �����Ѵ�.)
// lHomeMode -1�� �״�� ���� HomeConfig���� ����Ѵ�� �״�� ������.
// ��������      : Vel���� ����̸� CW, �����̸� CCW.
function AxmHomeSetMoveSearch(lAxisNo : LongInt; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;

// ����ڰ� ������ ���� Ȩ ������ �����Ѵ�.
// lHomeMode ���� ���� : 0 - 12 ���� 
// lHomeMode -1�� �״�� ���� HomeConfig���� ����Ѵ�� �״�� ������.
// ��������      : Vel���� ����̸� CW, �����̸� CCW.
function AxmHomeSetMoveReturn(lAxisNo : LongInt; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;

// ����ڰ� ������ ���� Ȩ ��Ż�� �����Ѵ�.
// ��������      : Vel���� ����̸� CW, �����̸� CCW.
function AxmHomeSetMoveLeave(lAxisNo : LongInt; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;

// ����ڰ� ������ ������ Ȩ ��ġ�� �����Ѵ�.
// lHomeMode ���� ���� : 0 - 5 ���� (Move Return�Ŀ� Search��  �����Ѵ�.)
// lHomeMode -1�� �״�� ���� HomeConfig���� ����Ѵ�� �״�� ������.
// ��������      : Vel���� ����̸� CW, �����̸� CCW.
function AxmHomeSetMultiMoveSearch(lArraySize : LongInt; lpAxesNo : PLongInt; dpVel : PDouble; dpAccel : PDouble; dpDecel : PDouble) : DWord; stdcall;

//������ ��ǥ���� ���� �ӵ� �������� ��带 �����Ѵ�.
// (������ : �ݵ�� ����� �ϰ� ��밡��)
  // ProfileMode : '0' - ��Ī Trapezode
  //               '1' - ���Ī Trapezode
  //               '2' - ��Ī Quasi-S Curve
  //               '3' - ��Ī S Curve
  //               '4' - ���Ī S Curve
function AxmContiSetProfileMode(lCoord : LongInt; uProfileMode : DWord) : DWord; stdcall;
// ������ ��ǥ���� ���� �ӵ� �������� ��带 ��ȯ�Ѵ�.
function AxmContiGetProfileMode(lCoord : LongInt; upProfileMode : PDWord) : DWord; stdcall;

//========== DIO ���ͷ�Ʈ �÷��� ������Ʈ �б�
// ������ �Է� ���� ���, Interrupt Flag Register�� Offset ��ġ���� bit ������ ���ͷ�Ʈ �߻� ���� ���� ����
function AxdiInterruptFlagReadBit(lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;
// ������ �Է� ���� ���, Interrupt Flag Register�� Offset ��ġ���� byte ������ ���ͷ�Ʈ �߻� ���� ���� ����
function AxdiInterruptFlagReadByte(lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;
// ������ �Է� ���� ���, Interrupt Flag Register�� Offset ��ġ���� word ������ ���ͷ�Ʈ �߻� ���� ���� ����
function AxdiInterruptFlagReadWord(lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;
// ������ �Է� ���� ���, Interrupt Flag Register�� Offset ��ġ���� double word ������ ���ͷ�Ʈ �߻� ���� ���� ����
function AxdiInterruptFlagReadDword(lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;
// ��ü �Է� ���� ���, Interrupt Flag Register�� Offset ��ġ���� bit ������ ���ͷ�Ʈ �߻� ���� ���� ����
function AxdiInterruptFlagRead(lOffset : LongInt; upValue : PDWord) : DWord; stdcall;


//========= �α� ���� �Լ� ==========================================================================================    
// ���� �ڵ����� ������.
// ���� ���� �Լ� ���� ����� EzSpy���� ����͸� �� �� �ֵ��� ���� �Ǵ� �����ϴ� �Լ��̴�.
// uUse : ��� ���� => DISABLE(0), ENABLE(1)
function AxmLogSetAxis(lAxisNo : LongInt; uUse : DWord) : DWord; stdcall;

// EzSpy������ ���� �� �Լ� ���� ��� ����͸� ���θ� Ȯ���ϴ� �Լ��̴�.
function AxmLogGetAxis(lAxisNo : LongInt; upUse : PDWord) : DWord; stdcall;

//aaaaaaaa=== �α� ��� ���� �Լ�
//������ �Է� ä���� EzSpy�� �α� ��� ���θ� �����Ѵ�.
function AxaiLogSetChannel(lChannelNo : LongInt; uUse : DWord) : DWord; stdcall;
//������ �Է� ä���� EzSpy�� �α� ��� ���θ� Ȯ���Ѵ�.
function AxaiLogGetChannel(lChannelNo : LongInt; upUse : PDWord) : DWord; stdcall;

//==������ ��� ä���� EzSpy �α� ��� 
//������ ��� ä���� EzSpy�� �α� ��� ���θ� �����Ѵ�.
function AxaoLogSetChannel(lChannelNo : LongInt; uUse : DWord) : DWord; stdcall;
//������ ��� ä���� EzSpy�� �α� ��� ���θ� Ȯ���Ѵ�.
function AxaoLogGetChannel(lChannelNo : LongInt; upUse : PDWord) : DWord; stdcall;

//==Log
// ������ ����� EzSpy�� �α� ��� ���� ����
function AxdLogSetModule(lModuleNo : LongInt; uUse : DWord) : DWord; stdcall;
// ������ ����� EzSpy�� �α� ��� ���� Ȯ��
function AxdLogGetModule(lModuleNo : LongInt; upUse : PDWord) : DWord; stdcall;

// ������ ���尡 RTEX ����� �� �� ������ firmware ������ Ȯ���Ѵ�.
function AxlGetFirmwareVersion(lBoardNo : LongInt; szVersion : PChar) : DWord; stdcall;
// ������ ����� Firmware�� ���� �Ѵ�.
function AxlSetFirmwareCopy(lBoardNo : LongInt; wData : PWord; wCmdData : PWord) : DWord; stdcall;
// ������ ����� Firmware Update�� �����Ѵ�.
function AxlSetFirmwareUpdate(lBoardNo : LongInt) : DWord; stdcall;
// ������ ������ ���� RTEX �ʱ�ȭ ���¸� Ȯ�� �Ѵ�.
function AxlCheckStatus(lBoardNo : LongInt; dwStatus : PDWord) : DWord; stdcall;
// ������ �࿡ RTEX Master board�� ���� ����� ���� �մϴ�.
function AxlRtexUniversalCmd(lBoardNo : LongInt; wCmd : Word; wOffset : Word; wData : PWord) : DWord; stdcall;
// ������ ���� RTEX ��� ����� �����Ѵ�.
function AxmRtexSlaveCmd(lAxisNo : LongInt; dwCmdCode : DWord; dwTypeCode : DWord; dwIndexCode : DWord; dwCmdConfigure : DWord; dwValue : DWord) : DWord; stdcall;
// ������ �࿡ ������ RTEX ��� ����� ������� Ȯ���Ѵ�.
function AxmRtexGetSlaveCmdResult(lAxisNo : LongInt; dwIndex : PDWord; dwValue : PDWord) : DWord; stdcall;
// ������ �࿡ RTEX ���� ������ Ȯ���Ѵ�.
function AxmRtexGetAxisStatus(lAxisNo : LongInt; dwStatus : PDWord) : DWord; stdcall;
// ������ �࿡ RTEX ��� ���� ������ Ȯ���Ѵ�.(Actual position, Velocity, Torque)
function AxmRtexGetAxisReturnData(lAxisNo : LongInt;  dwReturn1 : PDWord; dwReturn2 : PDWord; dwReturn3 : PDWord) : DWord; stdcall;
// ������ �࿡ RTEX Slave ���� ���� ���� ������ Ȯ���Ѵ�.(mechanical, Inposition and etc)
function AxmRtexGetAxisSlaveStatus(lAxisNo : LongInt; dwStatus : PDWord) : DWord; stdcall;

// ������ �࿡ MLII Slave �࿡ ���� ��Ʈ�� ��ɾ �����Ѵ�.
function AxmSetAxisCmd(lAxisNo : LongInt; tagCommand : PDWord) : DWord; stdcall;
// ������ �࿡ MLII Slave �࿡ ���� ��Ʈ�� ����� ����� Ȯ���Ѵ�.
function AxmGetAxisCmdResult(lAxisNo : LongInt; tagCommand : PDWORD) : DWord; stdcall;

function AxlGetDpRamData(lBoardNo : LongInt; wAddress : Word; dwpRdData : PDWord) : DWord; stdcall;
function AxlBoardReadDpramWord(lBoardNo : LongInt; wOffset : Word; dwpRdData : PDWord) : DWord; stdcall;

function AxlSetSendBoardCommand(lBoardNo : LongInt; dwCommand : DWord; dwpSendData : PDWord; dwLength : DWord) : DWord; stdcall;
function AxlGetResponseBoardCommand(lBoardNo : LongInt; dwpReadData : PDWord) : DWord; stdcall;

// Network Type Master ���忡�� Slave ���� Firmware Version�� �о� ���� �Լ�.
// ucaFirmwareVersion unsigned char ���� Array�� �����ϰ� ũ�Ⱑ 4�̻��� �ǵ��� ���� �ؾ� �Ѵ�.
function AxmInfoGetFirmwareVersion(lAxisNo : LongInt;  ucaFirmwareVersion : PWord) : DWord; stdcall;
function AxaInfoGetFirmwareVersion(lModuleNo : LongInt; ucaFirmwareVersion : PWord) : DWord; stdcall;
function AxdInfoGetFirmwareVersion(lModuleN : LongInt; ucaFirmwareVersion : PWord) : DWord; stdcall;
    
//======== PCI-R1604-MLII ���� �Լ�=========================================================================== 
// INTERPOLATE and LATCH Command�� Option Field�� Torq Feed Forward�� ���� ���� �ϵ��� �մϴ�.
// �⺻���� MAX�� �����Ǿ� �ֽ��ϴ�.
// �������� 0 ~ 4000H���� ���� �� �� �ֽ��ϴ�.
// �������� 4000H�̻����� �����ϸ� ������ �� �̻����� �����ǳ� ������ 4000H���� ���� �˴ϴ�.
function AxmSetTorqFeedForward(lAxisNo : LongInt; dwTorqFeedForward : DWord) : DWord; stdcall;

// INTERPOLATE and LATCH Command�� Option Field�� Torq Feed Forward�� ���� �о���� �Լ� �Դϴ�.
// �⺻���� MAX�� �����Ǿ� �ֽ��ϴ�.
function AxmGetTorqFeedForward(lAxisNo : LongInt; dwpTorqFeedForward : PDWord) : DWord; stdcall;

// INTERPOLATE and LATCH Command�� VFF Field�� Velocity Feed Forward�� ���� ���� �ϵ��� �մϴ�.
// �⺻���� '0'�� �����Ǿ� �ֽ��ϴ�.
// �������� 0 ~ FFFFH���� ���� �� �� �ֽ��ϴ�.
function AxmSetVelocityFeedForward(lAxisNo : LongInt; dwVelocityFeedForward : DWord) : DWord; stdcall;

// INTERPOLATE and LATCH Command�� VFF Field�� Velocity Feed Forward�� ���� �о���� �Լ� �Դϴ�.
function AxmGetVelocityFeedForward(lAxisNo : LongInt; dwpVelocityFeedForward : PDWord) : DWord; stdcall;

// Encoder type�� �����Ѵ�.
// �⺻���� 0(TYPE_INCREMENTAL)�� �����Ǿ� �ֽ��ϴ�.
// �������� 0 ~ 1���� ���� �� �� �ֽ��ϴ�.
// ������ : 0(TYPE_INCREMENTAL), 1(TYPE_ABSOLUTE).
function AxmSignalSetEncoderType(lAxisNo : LongInt; dwEncoderType : DWord) : DWord; stdcall;

// Encoder type�� Ȯ���Ѵ�.
function AxmSignalGetEncoderType(lAxisNo : LongInt; dwpEncoderType : PDWord) : DWord; stdcall;

// Slave Firmware Update�� ���� �߰�
//function AxmSetSendAxisCommand(lAxisNo : LongInt; wCommand : Word; wpSendData : PDWord; wLength : Word) : DWord; stdcall;

//======== PCI-R1604-RTEX, RTEX-PM ���� �Լ�============================================================== 
// ���� �Է� 2,3�� �Է½� JOG ���� �ӵ��� �����Ѵ�. 
// ������ ���õ� ��� ����(Ex, PulseOutMethod, MoveUnitPerPulse ��)���� �Ϸ�� ���� �ѹ��� �����Ͽ��� �Ѵ�.
function AxmMotSetUserMotion(lAxisNo : LongInt; dVelocity : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;

// ���� �Է� 2,3�� �Է½� JOG ���� ���� ��� ���θ� �����Ѵ�.
// ������ :  0(DISABLE), 1(ENABLE)
function AxmMotSetUserMotionUsage(lAxisNo: LongInt; dwUsage : DWord) : DWord; stdcall;

// MPGP �Է��� ����Ͽ� Load/UnLoad ��ġ�� �ڵ����� �̵��ϴ� ��� ����. 
function  AxmMotSetUserPosMotion(lAxisNo : LongInt; dVelocity : Double; dAccel : Double; dDecel : Double; dLoadPos : Double; dUnLoadPos : Double; dwFilter : DWord; dwDelay : DWord) : DWord; stdcall;

// MPGP �Է��� ����Ͽ� Load/UnLoad ��ġ�� �ڵ����� �̵��ϴ� ��� ����. 
// ������ :  0(DISABLE), 1(Position ��� A ���), 2(Position ��� B ���)
function  AxmMotSetUserPosMotionUsage(lAxisNo : LongInt; dwUsage : DWord) : DWord; stdcall;
//======================================================================================================== 

//======== SIO-CN2CH, ���� ��ġ Ʈ���� ��� ��� ���� �Լ�================================================ 
function AxcKeWriteRamDataAddr(lChannelNo : LongInt; dwAddr : DWord; dwData : DWord) : DWord; stdcall;
function AxcKeReadRamDataAddr(lChannelNo : LongInt; dwAddr : DWord; dwpData : PDWord) : DWord; stdcall;
function AxcKeResetRamDataAll(lModuleNo : LongInt; dwData : DWord) : DWord; stdcall;
function AxcTriggerSetTimeout(lChannelNo : LongInt; dwTimeout : DWord) : DWord; stdcall;
function AxcTriggerGetTimeout(lChannelNo : LongInt; dwpTimeout : PDWord) : DWord; stdcall;
function AxcStatusGetWaitState(lChannelNo : LongInt; dwpState : PDWord) : DWord; stdcall;
function AxcStatusSetWaitState(lChannelNo : LongInt; dwState : DWord) : DWord; stdcall;
//======================================================================================================== 
	
//======== PCI-N804/N404 ����, Sequence Motion ===================================================================
// Sequence Motion�� �� ������ ���� �մϴ�. (�ּ� 1��)
// lSeqMapNo : �� ��ȣ ������ ��� Sequence Motion Index Point
// lSeqMapSize : �� ��ȣ ����
// long* LSeqAxesNo : �� ��ȣ �迭
function AxmSeqSetAxisMap(lSeqMapNo : LongInt; lSeqMapSize : LongInt; lSeqAxesNo : PLongInt) : DWord; stdcall;
function AxmSeqGetAxisMap(lSeqMapNo : LongInt; lSeqMapSize : PLongInt; lSeqAxesNo : PLongInt) : DWord; stdcall;

// Sequence Motion�� ����(Master) ���� ���� �մϴ�. 
// �ݵ�� AxmSeqSetAxisMap(...) �� ������ �� ������ �����Ͽ��� �մϴ�.
function AxmSeqSetMasterAxisNo(lSeqMapNo : LongInt; lMasterAxisNo : LongInt) : DWord; stdcall;

// Sequence Motion�� Node ���� ������ ���̺귯���� �˸��ϴ�.
function AxmSeqBeginNode(lSeqMapNo : LongInt) : DWord; stdcall;

// Sequence Motion�� Node ���� ���Ḧ ���̺귯���� �˸��ϴ�.
function AxmSeqEndNode(lSeqMapNo : LongInt) : DWord; stdcall;

// Sequence Motion�� ������ ���� �մϴ�.
function AxmSeqStart(lSeqMapNo : LongInt; dwStartOption : DWord) : DWord; stdcall;

// Sequence Motion�� �� Profile Node ������ ���̺귯���� �Է� �մϴ�.
// ���� 1�� Sequence Motion�� ����ϴ���, *dPosition�� 1���� Array�� �����Ͽ� �ֽñ� �ٶ��ϴ�.
function AxmSeqAddNode(lSeqMapNo : LongInt; dPosition : PDouble; dVelocity : Double; dAcceleration : Double; dDeceleration : Double; dNextVelocity : Double) : DWord; stdcall;

// Sequence Motion�� ���� �� ���� ���� ���� Node Index�� �˷� �ݴϴ�.
function AxmSeqGetNodeNum(lSeqMapNo : LongInt; lCurNodeNo : PLongInt) : DWord; stdcall;

// Sequence Motion�� �� Node Count�� Ȯ�� �մϴ�.
function AxmSeqGetTotalNodeNum(lSeqMapNo : LongInt; lTotalNodeCnt : PLongInt) : DWord; stdcall;

// Sequence Motion�� ���� ���� ������ Ȯ�� �մϴ�.
// dwInMotion : 0(���� ����), 1(���� ��)
function AxmSeqIsMotion(lSeqMapNo : LongInt; dwInMotion : PDWord) : DWord; stdcall;

// Sequence Motion�� Memory�� Clear �մϴ�.
// AxmSeqSetAxisMap(...), AxmSeqSetMasterAxisNo(...) ���� ������ ���� �����˴ϴ�.
function AxmSeqWriteClear(lSeqMapNo : LongInt) : DWord; stdcall;

// Sequence Motion�� ������ ���� �մϴ�.
// dwStopMode : 0(EMERGENCY_STOP), 1(SLOWDOWN_STOP) 
function AxmSeqStop(lSeqMapNo : LongInt; dwStopMode : DWord) : DWord; stdcall;
//======================================================================================================== 


implementation
const

    dll_name    = 'AXL.dll';

    function AxlGetBoardAddress; external dll_name name 'AxlGetBoardAddress';
    function AxlGetBoardID; external dll_name name 'AxlGetBoardID';
    function AxlGetBoardVersion; external dll_name name 'AxlGetBoardVersion';
    function AxlGetModuleID; external dll_name name 'AxlGetModuleID';
    function AxlGetModuleVersion; external dll_name name 'AxlGetModuleVersion';
    function AxlGetModuleNodeInfo; external dll_name name 'AxlGetModuleNodeInfo';        
    function AxlSetDataFlash; external dll_name name 'AxlSetDataFlash';
    function AxlGetDataFlash; external dll_name name 'AxlGetDataFlash';        
    function AxaInfoGetModuleNo; external dll_name name 'AxaInfoGetModuleNo';
    function AxdInfoGetModuleNo; external dll_name name 'AxdInfoGetModuleNo';    
    function AxmSetCommand; external dll_name name 'AxmSetCommand';
    function AxmSetCommandData08; external dll_name name 'AxmSetCommandData08';
    function AxmGetCommandData08; external dll_name name 'AxmGetCommandData08';
    function AxmSetCommandData16; external dll_name name 'AxmSetCommandData16';
    function AxmGetCommandData16; external dll_name name 'AxmGetCommandData16';
    function AxmSetCommandData24; external dll_name name 'AxmSetCommandData24';
    function AxmGetCommandData24; external dll_name name 'AxmGetCommandData24';
    function AxmSetCommandData32; external dll_name name 'AxmSetCommandData32';
    function AxmGetCommandData32; external dll_name name 'AxmGetCommandData32';    
    function AxmSetCommandQi; external dll_name name 'AxmSetCommandQi';
    function AxmSetCommandData08Qi; external dll_name name 'AxmSetCommandData08Qi';
    function AxmGetCommandData08Qi; external dll_name name 'AxmGetCommandData08Qi';
    function AxmSetCommandData16Qi; external dll_name name 'AxmSetCommandData16Qi';
    function AxmGetCommandData16Qi; external dll_name name 'AxmGetCommandData16Qi';
    function AxmSetCommandData24Qi; external dll_name name 'AxmSetCommandData24Qi';
    function AxmGetCommandData24Qi; external dll_name name 'AxmGetCommandData24Qi';
    function AxmSetCommandData32Qi; external dll_name name 'AxmSetCommandData32Qi';
    function AxmGetCommandData32Qi; external dll_name name 'AxmGetCommandData32Qi';    
    function AxmGetPortData; external dll_name name 'AxmGetPortData';
    function AxmSetPortData; external dll_name name 'AxmSetPortData';
    function AxmGetPortDataQi; external dll_name name 'AxmGetPortDataQi';
    function AxmSetPortDataQi; external dll_name name 'AxmSetPortDataQi';    
    function AxmSetScriptCaptionIp; external dll_name name 'AxmSetScriptCaptionIp';
    function AxmGetScriptCaptionIp; external dll_name name 'AxmGetScriptCaptionIp';
    function AxmSetScriptCaptionQi; external dll_name name 'AxmSetScriptCaptionQi';
    function AxmGetScriptCaptionQi; external dll_name name 'AxmGetScriptCaptionQi';
    function AxmSetScriptCaptionQueueClear; external dll_name name 'AxmSetScriptCaptionQueueClear';
    function AxmGetScriptCaptionQueueCount; external dll_name name 'AxmGetScriptCaptionQueueCount';
    function AxmGetScriptCaptionQueueDataCount; external dll_name name 'AxmGetScriptCaptionQueueDataCount';
    function AxmGetOptimizeDriveData; external dll_name name  'AxmGetOptimizeDriveData';
    function AxmBoardWriteByte; external dll_name name 'AxmBoardWriteByte'; 
    function AxmBoardReadByte; external dll_name name 'AxmBoardReadByte'; 
    function AxmBoardWriteWord; external dll_name name 'AxmBoardWriteWord'; 
    function AxmBoardReadWord; external dll_name name 'AxmBoardReadWord'; 
    function AxmBoardWriteDWord; external dll_name name 'AxmBoardWriteDWord'; 
    function AxmBoardReadDWord; external dll_name name 'AxmBoardReadDWord'; 
    function AxmModuleWriteByte; external dll_name name 'AxmModuleWriteByte'; 
    function AxmModuleReadByte; external dll_name name 'AxmModuleReadByte'; 
    function AxmModuleWriteWord; external dll_name name 'AxmModuleWriteWord'; 
    function AxmModuleReadWord; external dll_name name 'AxmModuleReadWord'; 
    function AxmModuleWriteDWord; external dll_name name 'AxmModuleWriteDWord'; 
    function AxmModuleReadDWord; external dll_name name 'AxmModuleReadDWord'; 
    function AxmStatusSetActComparatorPos; external dll_name name 'AxmStatusSetActComparatorPos'; 
    function AxmStatusGetActComparatorPos; external dll_name name 'AxmStatusGetActComparatorPos'; 
    function AxmStatusSetCmdComparatorPos; external dll_name name 'AxmStatusSetCmdComparatorPos'; 
    function AxmStatusGetCmdComparatorPos; external dll_name name 'AxmStatusGetCmdComparatorPos'; 
    function AxmLineMoveVel; external dll_name name 'AxmLineMoveVel'; 
    function AxmSensorSetSignal; external dll_name name 'AxmSensorSetSignal'; 
    function AxmSensorGetSignal; external dll_name name 'AxmSensorGetSignal'; 
    function AxmSensorReadSignal; external dll_name name 'AxmSensorReadSignal'; 
    function AxmSensorMovePos; external dll_name name 'AxmSensorMovePos'; 
    function AxmSensorStartMovePos; external dll_name name 'AxmSensorStartMovePos'; 
    function AxmHomeGetStepTrace; external dll_name name 'AxmHomeGetStepTrace'; 
    function AxmHomeSetConfig; external dll_name name 'AxmHomeSetConfig'; 
    function AxmHomeGetConfig; external dll_name name 'AxmHomeGetConfig'; 
    function AxmHomeSetMoveSearch; external dll_name name 'AxmHomeSetMoveSearch'; 
    function AxmHomeSetMoveReturn; external dll_name name 'AxmHomeSetMoveReturn'; 
    function AxmHomeSetMoveLeave; external dll_name name 'AxmHomeSetMoveLeave'; 
    function AxmHomeSetMultiMoveSearch; external dll_name name 'AxmHomeSetMultiMoveSearch'; 
    function AxmContiSetProfileMode; external dll_name name 'AxmContiSetProfileMode'; 
    function AxmContiGetProfileMode; external dll_name name 'AxmContiGetProfileMode'; 
    function AxdiInterruptFlagReadBit; external dll_name name 'AxdiInterruptFlagReadBit'; 
    function AxdiInterruptFlagReadByte; external dll_name name 'AxdiInterruptFlagReadByte'; 
    function AxdiInterruptFlagReadWord; external dll_name name 'AxdiInterruptFlagReadWord'; 
    function AxdiInterruptFlagReadDword; external dll_name name 'AxdiInterruptFlagReadDword'; 
    function AxdiInterruptFlagRead; external dll_name name 'AxdiInterruptFlagRead'; 
    function AxmLogSetAxis; external dll_name name 'AxmLogSetAxis'; 
    function AxmLogGetAxis; external dll_name name 'AxmLogGetAxis'; 
    function AxaiLogSetChannel; external dll_name name 'AxaiLogSetChannel'; 
    function AxaiLogGetChannel; external dll_name name 'AxaiLogGetChannel'; 
    function AxaoLogSetChannel; external dll_name name 'AxaoLogSetChannel'; 
    function AxaoLogGetChannel; external dll_name name 'AxaoLogGetChannel'; 
    function AxdLogSetModule; external dll_name name 'AxdLogSetModule'; 
    function AxdLogGetModule; external dll_name name 'AxdLogGetModule'; 
    function AxlGetFirmwareVersion; external dll_name name 'AxlGetFirmwareVersion'; 
    function AxlSetFirmwareCopy; external dll_name name 'AxlSetFirmwareCopy'; 
    function AxlSetFirmwareUpdate; external dll_name name 'AxlSetFirmwareUpdate'; 
    function AxlCheckStatus; external dll_name name 'AxlCheckStatus'; 
    function AxlRtexUniversalCmd; external dll_name name 'AxlRtexUniversalCmd'; 
    function AxmRtexSlaveCmd; external dll_name name 'AxmRtexSlaveCmd'; 
    function AxmRtexGetSlaveCmdResult; external dll_name name 'AxmRtexGetSlaveCmdResult'; 
    function AxmRtexGetAxisStatus; external dll_name name 'AxmRtexGetAxisStatus'; 
    function AxmRtexGetAxisReturnData; external dll_name name 'AxmRtexGetAxisReturnData'; 
    function AxmRtexGetAxisSlaveStatus; external dll_name name 'AxmRtexGetAxisSlaveStatus'; 
    function AxmSetAxisCmd; external dll_name name 'AxmSetAxisCmd'; 
    function AxmGetAxisCmdResult; external dll_name name 'AxmGetAxisCmdResult'; 
    function AxlGetDpRamData; external dll_name name 'AxlGetDpRamData'; 
    function AxlBoardReadDpramWord; external dll_name name 'AxlBoardReadDpramWord'; 
    function AxlSetSendBoardCommand; external dll_name name 'AxlSetSendBoardCommand'; 
    function AxlGetResponseBoardCommand; external dll_name name 'AxlGetResponseBoardCommand'; 
    function AxmInfoGetFirmwareVersion; external dll_name name 'AxmInfoGetFirmwareVersion'; 
    function AxaInfoGetFirmwareVersion; external dll_name name 'AxaInfoGetFirmwareVersion'; 
    function AxdInfoGetFirmwareVersion; external dll_name name 'AxdInfoGetFirmwareVersion'; 
    function AxmSetTorqFeedForward; external dll_name name 'AxmSetTorqFeedForward'; 
    function AxmGetTorqFeedForward; external dll_name name 'AxmGetTorqFeedForward'; 
    function AxmSetVelocityFeedForward; external dll_name name 'AxmSetVelocityFeedForward'; 
    function AxmGetVelocityFeedForward; external dll_name name 'AxmGetVelocityFeedForward'; 
    function AxmSignalSetEncoderType; external dll_name name 'AxmSignalSetEncoderType'; 
    function AxmSignalGetEncoderType; external dll_name name 'AxmSignalGetEncoderType'; 
    //function AxmSetSendAxisCommand; external dll_name name 'AxmSetSendAxisCommand';    
    function AxmMotSetUserMotion; external dll_name name 'AxmMotSetUserMotion';
    function AxmMotSetUserMotionUsage; external dll_name name 'AxmMotSetUserMotionUsage';
    function AxmMotSetUserPosMotion; external dll_name name 'AxmMotSetUserPosMotion';
    function AxmMotSetUserPosMotionUsage; external dll_name name 'AxmMotSetUserPosMotionUsage';
    function AxcKeWriteRamDataAddr; external dll_name name 'AxcKeWriteRamDataAddr';
    function AxcKeReadRamDataAddr; external dll_name name 'AxcKeReadRamDataAddr';
    function AxcKeResetRamDataAll; external dll_name name 'AxcKeResetRamDataAll';
    function AxcTriggerSetTimeout; external dll_name name 'AxcTriggerSetTimeout';
    function AxcTriggerGetTimeout; external dll_name name 'AxcTriggerGetTimeout';
    function AxcStatusGetWaitState; external dll_name name 'AxcStatusGetWaitState';
    function AxcStatusSetWaitState; external dll_name name 'AxcStatusSetWaitState';
    function AxmSeqSetAxisMap; external dll_name name 'AxmSeqSetAxisMap';
    function AxmSeqGetAxisMap; external dll_name name 'AxmSeqGetAxisMap';
    function AxmSeqSetMasterAxisNo; external dll_name name 'AxmSeqSetMasterAxisNo';
    function AxmSeqBeginNode; external dll_name name 'AxmSeqBeginNode';
    function AxmSeqEndNode; external dll_name name 'AxmSeqEndNode';
    function AxmSeqStart; external dll_name name 'AxmSeqStart';
    function AxmSeqAddNode; external dll_name name 'AxmSeqAddNode';
    function AxmSeqGetNodeNum; external dll_name name 'AxmSeqGetNodeNum';
    function AxmSeqGetTotalNodeNum; external dll_name name 'AxmSeqGetTotalNodeNum';
    function AxmSeqIsMotion; external dll_name name 'AxmSeqIsMotion';
    function AxmSeqWriteClear; external dll_name name 'AxmSeqWriteClear';
    function AxmSeqStop; external dll_name name 'AxmSeqStop';
end.
