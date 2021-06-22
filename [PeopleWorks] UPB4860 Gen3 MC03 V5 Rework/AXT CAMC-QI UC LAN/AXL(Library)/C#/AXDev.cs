/****************************************************************************
*****************************************************************************
**
** File Name
** ---------
**
** AXDev.CS
**
** COPYRIGHT (c) AJINEXTEK Co., LTD
**
*****************************************************************************
*****************************************************************************
**
** Description
** -----------
** Ajinextek Develop Library Header File
** 
**
*****************************************************************************
*****************************************************************************
**
** Source Change Indices
** ---------------------
**
** (None)
**
*****************************************************************************
*****************************************************************************
**
** Website
** ---------------------
**
** http://www.ajinextek.com
**
*****************************************************************************
*****************************************************************************
*/

using System.Runtime.InteropServices;

public class CAXDev
{

//========== ���� �� ��� Ȯ���Լ�(Info) - Infomation =================================================================================

    // Board Number�� �̿��Ͽ� Board Address ã��
    [DllImport("AXL.dll")] public static extern uint AxlGetBoardAddress(int nBoardNo, ref uint upBoardAddress);
    // Board Number�� �̿��Ͽ� Board ID ã��
    [DllImport("AXL.dll")] public static extern uint AxlGetBoardID(int nBoardNo, ref uint upBoardID);
    // Board Number�� �̿��Ͽ� Board Version ã��
    [DllImport("AXL.dll")] public static extern uint AxlGetBoardVersion(int nBoardNo, ref uint upBoardVersion);
    // Board Number�� Module Position�� �̿��Ͽ� Module ID ã��
    [DllImport("AXL.dll")] public static extern uint AxlGetModuleID(int nBoardNo, int nModulePos, ref uint upModuleID);
    // Board Number�� Module Position�� �̿��Ͽ� Module Version ã��
    [DllImport("AXL.dll")] public static extern uint AxlGetModuleVersion(int nBoardNo, int nModulePos, ref uint upModuleVersion);
    // Board Number�� Module Position�� �̿��Ͽ� Network Node ���� Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxlGetModuleNodeInfo(int nBoardNo, int nModulePos, ref uint upNetNo, ref uint upNodeAddr);

    // Board�� ����� ���� Data Flash Write (PCI-R1604[RTEX master board]����)
    // lPageAddr(0 ~ 199)
    // lByteNum(1 ~ 120)
    // ����) Flash�� ����Ÿ�� ������ ���� ���� �ð�(�ִ� 17mSec)�� �ҿ�Ǳ⶧���� ���� ����� ���� �ð��� �ʿ���.
    [DllImport("AXL.dll")] public static extern uint AxlSetDataFlash(int lBoardNo, int lPageAddr, int lBytesNum, ref uint upSetData);

    // Board�� ����� ESTOP �ܺ� �Է� ��ȣ�� �̿��� InterLock ��� ��� ���� �� ������ ���� ����� ���� (PCI-Rxx00[MLIII master board]����)
    // 1. ��� ����
    //	  ����: ��� ��� ������ �ܺο��� ESTOP ��ȣ �ΰ��� ���忡 ����� ��� ���� ��忡 ���ؼ� ESTOP ���� ��� ����	
    //    0: ��� ������� ����(�⺻ ������)
    //    1: ��� ���
    // 2. ������ ���� ��
    //      �Է� ���� ��� ���� ���� 1 ~ 40, ���� msec
	// Board �� dwInterLock, dwDigFilterVal�� �̿��Ͽ� EstopInterLock ��� ����
	[DllImport("AXL.dll")] public static extern uint AxlSetEStopInterLock(int lBoardNo, uint dwInterLock, uint dwDigFilterVal);
	// Board�� ������ dwInterLock, dwDigFilterVal ������ ��������
	[DllImport("AXL.dll")] public static extern uint AxlGetEStopInterLock(int lBoardNo, ref uint dwInterLock, ref uint dwDigFilterVal);
	// Board�� �Էµ� EstopInterLock ��ȣ�� �д´�.
	[DllImport("AXL.dll")] public static extern uint AxlReadEStopInterLock(int lBoardNo, ref uint dwInterLock);
        
    // Board�� ����� ���� Data Flash Read(PCI-R1604[RTEX master board]����)
    // lPageAddr(0 ~ 199)
    // lByteNum(1 ~ 120)
    [DllImport("AXL.dll")] public static extern uint AxlGetDataFlash(int lBoardNo, int lPageAddr, int lBytesNum, ref uint upGetData);

    // Board Number�� Module Position�� �̿��Ͽ� AIO Module Number ã��
    [DllImport("AXL.dll")] public static extern uint AxaInfoGetModuleNo(int nBoardNo, int nModulePos, ref int npModuleNo);
    // Board Number�� Module Position�� �̿��Ͽ� DIO Module Number ã��
    [DllImport("AXL.dll")] public static extern uint AxdInfoGetModuleNo(int nBoardNo, int nModulePos, ref int npModuleNo);

    // ���� �࿡ byte Setting
    [DllImport("AXL.dll")] public static extern uint AxmSetCommand(int nAxisNo, byte sCommand);
    // ���� �࿡ 8bit byte Setting
    [DllImport("AXL.dll")] public static extern uint AxmSetCommandData08(int nAxisNo, byte sCommand, uint uData);
    // ���� �࿡ 8bit byte ��������
    [DllImport("AXL.dll")] public static extern uint AxmGetCommandData08(int nAxisNo, byte sCommand, ref uint upData);
    // ���� �࿡ 16bit byte Setting
    [DllImport("AXL.dll")] public static extern uint AxmSetCommandData16(int nAxisNo, byte sCommand, uint uData);
    // ���� �࿡ 16bit byte ��������
    [DllImport("AXL.dll")] public static extern uint AxmGetCommandData16(int nAxisNo, byte sCommand, ref uint upData);
    // ���� �࿡ 24bit byte Setting
    [DllImport("AXL.dll")] public static extern uint AxmSetCommandData24(int nAxisNo, byte sCommand, uint uData);
    // ���� �࿡ 24bit byte ��������
    [DllImport("AXL.dll")] public static extern uint AxmGetCommandData24(int nAxisNo, byte sCommand, ref uint upData);
    // ���� �࿡ 32bit byte Setting
    [DllImport("AXL.dll")] public static extern uint AxmSetCommandData32(int nAxisNo, byte sCommand, uint uData);
    // ���� �࿡ 32bit byte ��������
    [DllImport("AXL.dll")] public static extern uint AxmGetCommandData32(int nAxisNo, byte sCommand, ref uint upData);
    
    // ���� �࿡ byte Setting
    [DllImport("AXL.dll")] public static extern uint AxmSetCommandQi(int nAxisNo, byte sCommand);
    // ���� �࿡ 8bit byte Setting
    [DllImport("AXL.dll")] public static extern uint AxmSetCommandData08Qi(int nAxisNo, byte sCommand, uint uData);
    // ���� �࿡ 8bit byte ��������
    [DllImport("AXL.dll")] public static extern uint AxmGetCommandData08Qi(int nAxisNo, byte sCommand, ref uint upData);
    // ���� �࿡ 16bit byte Setting
    [DllImport("AXL.dll")] public static extern uint AxmSetCommandData16Qi(int nAxisNo, byte sCommand, uint uData);
    // ���� �࿡ 16bit byte ��������
    [DllImport("AXL.dll")] public static extern uint AxmGetCommandData16Qi(int nAxisNo, byte sCommand, ref uint upData);
    // ���� �࿡ 24bit byte Setting
    [DllImport("AXL.dll")] public static extern uint AxmSetCommandData24Qi(int nAxisNo, byte sCommand, uint uData);
    // ���� �࿡ 24bit byte ��������
    [DllImport("AXL.dll")] public static extern uint AxmGetCommandData24Qi(int nAxisNo, byte sCommand, ref uint upData);
    // ���� �࿡ 32bit byte Setting
    [DllImport("AXL.dll")] public static extern uint AxmSetCommandData32Qi(int nAxisNo, byte sCommand, uint uData);
    // ���� �࿡ 32bit byte ��������
    [DllImport("AXL.dll")] public static extern uint AxmGetCommandData32Qi(int nAxisNo, byte sCommand, ref uint upData);
    
    // ���� �࿡ Port Data �������� - IP
    [DllImport("AXL.dll")] public static extern uint AxmGetPortData(int nAxisNo,  uint wOffset, ref uint upData);
    // ���� �࿡ Port Data Setting - IP
    [DllImport("AXL.dll")] public static extern uint AxmSetPortData(int nAxisNo, uint wOffset, uint dwData);

    // ���� �࿡ Port Data �������� - QI
    [DllImport("AXL.dll")] public static extern uint AxmGetPortDataQi(int nAxisNo, uint byOffset, ref uint wData);
    // ���� �࿡ Port Data Setting - QI
    [DllImport("AXL.dll")] public static extern uint AxmSetPortDataQi(int nAxisNo, uint byOffset, uint wData);
        
    // ���� �࿡ ��ũ��Ʈ�� �����Ѵ�. - IP
    // sc    : ��ũ��Ʈ ��ȣ (1 - 4)
    // event : �߻��� �̺�Ʈ SCRCON �� �����Ѵ�.
    //         �̺�Ʈ ���� �హ������, �̺�Ʈ �߻��� ��, �̺�Ʈ ���� 1,2 �Ӽ� �����Ѵ�.
    // cmd   : � ������ �ٲܰ����� ���� SCRCMD�� �����Ѵ�.
    // data  : � Data�� �ٲܰ����� ����
    [DllImport("AXL.dll")] public static extern uint AxmSetScriptCaptionIp(int nAxisNo, int sc, uint uEvent, uint data);
    // ���� �࿡ ��ũ��Ʈ�� ��ȯ�Ѵ�. - IP
    [DllImport("AXL.dll")] public static extern uint AxmGetScriptCaptionIp(int nAxisNo, int sc, ref uint uEvent, ref uint data);

    // ���� �࿡ ��ũ��Ʈ�� �����Ѵ�. - QI
    // sc    : ��ũ��Ʈ ��ȣ (1 - 4)
    // event : �߻��� �̺�Ʈ SCRCON �� �����Ѵ�.
    //         �̺�Ʈ ���� �హ������, �̺�Ʈ �߻��� ��, �̺�Ʈ ���� 1,2 �Ӽ� �����Ѵ�.
    // cmd   : � ������ �ٲܰ����� ���� SCRCMD�� �����Ѵ�.
    // data  : � Data�� �ٲܰ����� ����
    [DllImport("AXL.dll")] public static extern uint AxmSetScriptCaptionQi(int nAxisNo, int sc, uint uEvent, uint cmd, uint data);
    // ���� �࿡ ��ũ��Ʈ�� ��ȯ�Ѵ�. - QI
    [DllImport("AXL.dll")] public static extern uint AxmGetScriptCaptionQi(int nAxisNo, int sc, ref uint uEvent, ref uint cmd, ref uint data);

    // ���� �࿡ ��ũ��Ʈ ���� Queue Index�� Clear ��Ų��.
    // uSelect IP. 
    // uSelect(0): ��ũ��Ʈ Queue Index �� Clear�Ѵ�.
    //        (1): ĸ�� Queue�� Index Clear�Ѵ�.

    // uSelect QI. 
    // uSelect(0): ��ũ��Ʈ Queue 1 Index �� Clear�Ѵ�.
    //        (1): ��ũ��Ʈ Queue 2 Index �� Clear�Ѵ�.

    [DllImport("AXL.dll")] public static extern uint AxmSetScriptCaptionQueueClear(int nAxisNo, uint uSelect);
    
    // ���� �࿡ ��ũ��Ʈ ���� Queue�� Index ��ȯ�Ѵ�. 
    // uSelect IP
    // uSelect(0): ��ũ��Ʈ Queue Index�� �о�´�.
    //        (1): ĸ�� Queue Index�� �о�´�.

    // uSelect QI. 
    // uSelect(0): ��ũ��Ʈ Queue 1 Index�� �о�´�.
    //        (1): ��ũ��Ʈ Queue 2 Index�� �о�´�.

    [DllImport("AXL.dll")] public static extern uint AxmGetScriptCaptionQueueCount(int nAxisNo, ref uint updata, uint uSelect);

    // ���� �࿡ ��ũ��Ʈ ���� Queue�� Data���� ��ȯ�Ѵ�. 
    // uSelect IP
    // uSelect(0): ��ũ��Ʈ Queue Data �� �о�´�.
    //        (1): ĸ�� Queue Data�� �о�´�.

    // uSelect QI.
    // uSelect(0): ��ũ��Ʈ Queue 1 Data �о�´�.
    //        (1): ��ũ��Ʈ Queue 2 Data �о�´�.

    [DllImport("AXL.dll")] public static extern uint AxmGetScriptCaptionQueueDataCount(int nAxisNo, ref uint updata, uint uSelect);

    // ���� ����Ÿ�� �о�´�.
    [DllImport("AXL.dll")] public static extern uint AxmGetOptimizeDriveData(int nAxisNo, double dMinVel, double dVel, double dAccel, double  dDecel, 
            ref uint wRangeData, ref uint wStartStopSpeedData, ref uint wObjectSpeedData, ref uint wAccelRate, ref uint wDecelRate);

    // ���峻�� �������͸� Byte������ ���� �� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmBoardWriteByte(int nBoardNo, uint wOffset, byte byData);
    [DllImport("AXL.dll")] public static extern uint AxmBoardReadByte(int nBoardNo, uint wOffset, ref byte byData);

    // ���峻�� �������͸� Word������ ���� �� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmBoardWriteWord(int nBoardNo, uint wOffset, uint wData);
    [DllImport("AXL.dll")] public static extern uint AxmBoardReadWord(int nBoardNo, uint wOffset, ref ushort wData);

    // ���峻�� �������͸� DWord������ ���� �� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmBoardWriteDWord(int nBoardNo, uint wOffset, uint dwData);
    [DllImport("AXL.dll")] public static extern uint AxmBoardReadDWord(int nBoardNo, uint wOffset, ref uint dwData);

    // ���峻�� ��⿡ �������͸� Byte���� �� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmModuleWriteByte(int nBoardNo, int nModulePos, uint wOffset, byte byData);
    [DllImport("AXL.dll")] public static extern uint AxmModuleReadByte(int nBoardNo, int nModulePos, uint wOffset, ref byte byData);

    // ���峻�� ��⿡ �������͸� Word���� �� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmModuleWriteWord(int nBoardNo, int nModulePos, uint wOffset, uint wData);
    [DllImport("AXL.dll")] public static extern uint AxmModuleReadWord(int nBoardNo, int nModulePos, uint wOffset, ref ushort wData);

    // ���峻�� ��⿡ �������͸� DWord���� �� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmModuleWriteDWord(int nBoardNo, int nModulePos, uint wOffset, uint dwData);
    [DllImport("AXL.dll")] public static extern uint AxmModuleReadDWord(int nBoardNo, int nModulePos, uint wOffset, ref uint dwData);
    

    // �ܺ� ��ġ �񱳱⿡ ���� �����Ѵ�.(Pos = Unit)
    [DllImport("AXL.dll")] public static extern uint AxmStatusSetActComparatorPos(int nAxisNo, double dPos);
    // �ܺ� ��ġ �񱳱⿡ ���� ��ȯ�Ѵ�.(Positon = Unit)
    [DllImport("AXL.dll")] public static extern uint AxmStatusGetActComparatorPos(int nAxisNo, ref double dpPos);

    // ���� ��ġ �񱳱⿡ ���� �����Ѵ�.(Pos = Unit)
    [DllImport("AXL.dll")] public static extern uint AxmStatusSetCmdComparatorPos(int nAxisNo, double dPos);
    // ���� ��ġ �񱳱⿡ ���� ��ȯ�Ѵ�.(Pos = Unit)
    [DllImport("AXL.dll")] public static extern uint AxmStatusGetCmdComparatorPos(int nAxisNo, ref double dpPos);
    
//========== �߰� �Լ� =========================================================================================================
    
    // ���� ���� �� �ӵ��� ������ ���Ѵ�� �����Ѵ�.
    // �ӵ� ������� �Ÿ��� �־��־�� �Ѵ�. 
    [DllImport("AXL.dll")] public static extern uint AxmLineMoveVel(int nCoord, double dVel, double dAccel, double dDecel);

//========= ���� ��ġ ���� �Լ�( �ʵ�: IP������ , QI���� ��ɾ���)==============================================================
    
    // ���� ���� Sensor ��ȣ�� ��� ���� �� ��ȣ �Է� ������ �����Ѵ�.
    // ��� ���� LOW(0), HIGH(1), UNUSED(2), USED(3)
    [DllImport("AXL.dll")] public static extern uint AxmSensorSetSignal(int nAxisNo, uint uLevel);
    // ���� ���� Sensor ��ȣ�� ��� ���� �� ��ȣ �Է� ������ ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmSensorGetSignal(int nAxisNo, ref uint upLevel);
    // ���� ���� Sensor ��ȣ�� �Է� ���¸� ��ȯ�Ѵ�
    [DllImport("AXL.dll")] public static extern uint AxmSensorReadSignal(int nAxisNo, ref uint upStatus);
    
    // ���� ���� ������ �ӵ��� �������� ���� ��ġ ����̹��� �����Ѵ�.
    // Sensor ��ȣ�� Active level�Է� ���� ��� ��ǥ�� ������ �Ÿ���ŭ ������ �����Ѵ�.
    // �޽��� ��µǴ� �������� �Լ��� �����.
    // lMethod :  0 - �Ϲ� ����, 1 - ���� ��ȣ ���� ���� ���� ����. ��ȣ ���� �� �Ϲ� ����
    //            2 - ���� ����
    [DllImport("AXL.dll")] public static extern uint AxmSensorMovePos(int nAxisNo, double dPos, double dVel, double dAccel, double dDecel, int nMethod);

    // ���� ���� ������ �ӵ��� �������� ���� ��ġ ����̹��� �����Ѵ�.
    // Sensor ��ȣ�� Active level�Է� ���� ��� ��ǥ�� ������ �Ÿ���ŭ ������ �����Ѵ�.
    // �޽� ����� ����Ǵ� �������� �Լ��� �����.
    [DllImport("AXL.dll")] public static extern uint AxmSensorStartMovePos(int nAxisNo, double dPos, double dVel, double dAccel, double dDecel, int nMethod);

    // �����˻� ���ེ�� ��ȭ�� ����� ��ȯ�Ѵ�.
    // *lpStepCount      : ��ϵ� Step�� ����
    // *upMainStepNumber : ��ϵ� MainStepNumber ������ �迭����Ʈ
    // *upStepNumber     : ��ϵ� StepNumber ������ �迭����Ʈ
    // *upStepBranch     : ��ϵ� Step�� Branch ������ �迭����Ʈ
    // ����: �迭������ 50���� ����
    [DllImport("AXL.dll")] public static extern uint AxmHomeGetStepTrace(int nAxisNo, ref uint upStepCount, ref uint upMainStepNumber, ref uint upStepNumber, ref uint upStepBranch);

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
    [DllImport("AXL.dll")] public static extern uint AxmHomeSetConfig(int nAxisNo, uint uZphasCount, int nHomeMode, int nClearSet, double dOrgVel, double dLastVel, double dLeavePos);
    // ����ڰ� ������ ���� Ȩ���� �Ķ��Ÿ�� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmHomeGetConfig(int nAxisNo, ref uint upZphasCount, ref int npHomeMode, ref int npClearSet, ref double dpOrgVel, ref double dpLastVel, ref double dpLeavePos); //KKJ(070215)
    
    // ����ڰ� ������ ���� Ȩ ��ġ�� �����Ѵ�.
    // lHomeMode ���� ���� : 0 - 5 ���� (Move Return�Ŀ� Search��  �����Ѵ�.)
    // lHomeMode -1�� �״�� ���� HomeConfig���� ����Ѵ�� �״�� ������.
    // ��������      : Vel���� ����̸� CW, �����̸� CCW.
    [DllImport("AXL.dll")] public static extern uint AxmHomeSetMoveSearch(int nAxisNo, double dVel, double dAccel, double dDecel);

    // ����ڰ� ������ ���� Ȩ ������ �����Ѵ�.
    // lHomeMode ���� ���� : 0 - 12 ���� 
    // lHomeMode -1�� �״�� ���� HomeConfig���� ����Ѵ�� �״�� ������.
    // ��������      : Vel���� ����̸� CW, �����̸� CCW.
    [DllImport("AXL.dll")] public static extern uint AxmHomeSetMoveReturn(int nAxisNo, double dVel, double dAccel, double dDecel);
    
    // ����ڰ� ������ ���� Ȩ ��Ż�� �����Ѵ�.
    // ��������      : Vel���� ����̸� CW, �����̸� CCW.
    [DllImport("AXL.dll")] public static extern uint AxmHomeSetMoveLeave(int nAxisNo, double dVel, double dAccel, double dDecel);

    // ����ڰ� ������ ������ Ȩ ��ġ�� �����Ѵ�.
    // lHomeMode ���� ���� : 0 - 5 ���� (Move Return�Ŀ� Search��  �����Ѵ�.)
    // lHomeMode -1�� �״�� ���� HomeConfig���� ����Ѵ�� �״�� ������.
    // ��������      : Vel���� ����̸� CW, �����̸� CCW.
    [DllImport("AXL.dll")] public static extern uint AxmHomeSetMultiMoveSearch(int nArraySize, ref int npAxesNo, ref double dpVel, ref double dpAccel, ref double dpDecel);

    //������ ��ǥ���� ���� �ӵ� �������� ��带 �����Ѵ�.
    // (������ : �ݵ�� ����� �ϰ� ��밡��)
    // ProfileMode : '0' - ��Ī Trapezode
    //               '1' - ���Ī Trapezode
    //               '2' - ��Ī Quasi-S Curve
    //               '3' - ��Ī S Curve
    //               '4' - ���Ī S Curve
    [DllImport("AXL.dll")] public static extern uint AxmContiSetProfileMode(int nCoord, uint uProfileMode);
    // ������ ��ǥ���� ���� �ӵ� �������� ��带 ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmContiGetProfileMode(int nCoord, ref uint upProfileMode);

    //========== DIO ���ͷ�Ʈ �÷��� ������Ʈ �б�
    // ������ �Է� ���� ���, Interrupt Flag Register�� Offset ��ġ���� bit ������ ���ͷ�Ʈ �߻� ���� ���� ����
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptFlagReadBit(int nModuleNo, int nOffset, ref uint upValue);
    // ������ �Է� ���� ���, Interrupt Flag Register�� Offset ��ġ���� byte ������ ���ͷ�Ʈ �߻� ���� ���� ����
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptFlagReadByte(int nModuleNo, int nOffset, ref uint upValue);
    // ������ �Է� ���� ���, Interrupt Flag Register�� Offset ��ġ���� word ������ ���ͷ�Ʈ �߻� ���� ���� ����
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptFlagReadWord(int nModuleNo, int nOffset, ref uint upValue);
    // ������ �Է� ���� ���, Interrupt Flag Register�� Offset ��ġ���� double word ������ ���ͷ�Ʈ �߻� ���� ���� ����
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptFlagReadDword(int nModuleNo, int nOffset, ref uint upValue);
    // ��ü �Է� ���� ���, Interrupt Flag Register�� Offset ��ġ���� bit ������ ���ͷ�Ʈ �߻� ���� ���� ����
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptFlagRead(int nOffset, ref uint upValue);

    //========= �α� ���� �Լ� ==========================================================================================
    // ���� �ڵ����� ������.
    // ���� ���� �Լ� ���� ����� EzSpy���� ����͸� �� �� �ֵ��� ���� �Ǵ� �����ϴ� �Լ��̴�.
    // uUse : ��� ���� => DISABLE(0), ENABLE(1)
    [DllImport("AXL.dll")] public static extern uint AxmLogSetAxis(int nAxisNo, uint uUse);
    
    // EzSpy������ ���� �� �Լ� ���� ��� ����͸� ���θ� Ȯ���ϴ� �Լ��̴�.
    [DllImport("AXL.dll")] public static extern uint AxmLogGetAxis(int nAxisNo, ref uint upUse);

//=========== �α� ��� ���� �Լ�
    //������ �Է� ä���� EzSpy�� �α� ��� ���θ� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaiLogSetChannel(int nChannelNo, uint uUse);
    //������ �Է� ä���� EzSpy�� �α� ��� ���θ� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaiLogGetChannel(int nChannelNo, ref uint upUse);

//==������ ��� ä���� EzSpy �α� ��� 
    //������ ��� ä���� EzSpy�� �α� ��� ���θ� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaoLogSetChannel(int nChannelNo, uint uUse);
    //������ ��� ä���� EzSpy�� �α� ��� ���θ� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaoLogGetChannel(int nChannelNo, ref uint upUse);

//==Log
    // ������ ����� EzSpy�� �α� ��� ���� ����
    [DllImport("AXL.dll")] public static extern uint AxdLogSetModule(int nModuleNo, uint uUse);
    // ������ ����� EzSpy�� �α� ��� ���� Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxdLogGetModule(int nModuleNo, ref uint upUse);

    // ������ ���尡 RTEX ����� �� �� ������ firmware ������ Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxlGetFirmwareVersion(int nBoardNo, ref char szVersion);
    // ������ ����� Firmware�� ���� �Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxlSetFirmwareCopy(int nBoardNo, ref ushort wData, ref ushort wCmdData);
    // ������ ����� Firmware Update�� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxlSetFirmwareUpdate(int nBoardNo);
    // ������ ������ ���� RTEX �ʱ�ȭ ���¸� Ȯ�� �Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxlCheckStatus(int nBoardNo, ref uint dwStatus);
    // ������ �࿡ RTEX Master board�� ���� ����� ���� �մϴ�.
    [DllImport("AXL.dll")] public static extern uint AxlRtexUniversalCmd(int nBoardNo, ushort wCmd, ushort wOffset, ref ushort wData);
    // ������ ���� RTEX ��� ����� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmRtexSlaveCmd(int nAxisNo, uint dwCmdCode, uint dwTypeCode, uint dwIndexCode, uint dwCmdConfigure, uint dwValue);
    // ������ �࿡ ������ RTEX ��� ����� ������� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmRtexGetSlaveCmdResult(int nAxisNo, ref uint dwIndex, ref uint dwValue);
    // ������ �࿡ RTEX ���� ������ Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmRtexGetAxisStatus(int nAxisNo, ref uint dwStatus);
    // ������ �࿡ RTEX ��� ���� ������ Ȯ���Ѵ�.(Actual position, Velocity, Torque)
    [DllImport("AXL.dll")] public static extern uint AxmRtexGetAxisReturnData(int nAxisNo,  ref uint dwReturn1, ref uint dwReturn2, ref uint dwReturn3);
    // ������ �࿡ RTEX Slave ���� ���� ���� ������ Ȯ���Ѵ�.(mechanical, Inposition and etc)
    [DllImport("AXL.dll")] public static extern uint AxmRtexGetAxisSlaveStatus(int nAxisNo,  ref uint dwStatus);
    // ������ �࿡ MLII Slave �࿡ ���� ��Ʈ�� ��ɾ �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmSetAxisCmd(int nAxisNo, ref uint tagCommand);
    // ������ �࿡ MLII Slave �࿡ ���� ��Ʈ�� ����� ����� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmGetAxisCmdResult(int nAxisNo, ref uint tagCommand);
    
    [DllImport("AXL.dll")] public static extern uint AxlGetDpRamData(int nBoardNo, ushort uAddress, ref uint upRdData);
    [DllImport("AXL.dll")] public static extern uint AxlBoardReadDpramWord(int nBoardNo, ushort uOffset, ref uint upRdData);

    [DllImport("AXL.dll")] public static extern uint AxlSetSendBoardCommand(int nBoardNo, uint uCommand, ref uint upSendData, uint uLength);
    [DllImport("AXL.dll")] public static extern uint AxlGetResponseBoardCommand(int nBoardNo, ref uint upReadData);

    // Network Type Master ���忡�� Slave ���� Firmware Version�� �о� ���� �Լ�.
    // ucaFirmwareVersion unsigned char ���� Array�� �����ϰ� ũ�Ⱑ 4�̻��� �ǵ��� ���� �ؾ� �Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmInfoGetFirmwareVersion(int nAxisNo, ref ushort ucaFirmwareVersion);
    [DllImport("AXL.dll")] public static extern uint AxaInfoGetFirmwareVersion(int nModuleNo, ref ushort ucaFirmwareVersion);
    [DllImport("AXL.dll")] public static extern uint AxdInfoGetFirmwareVersion(int nModuleNo, ref ushort ucaFirmwareVersion);

//======== PCI-R1604-MLII ���� �Լ�=========================================================================== 
    // INTERPOLATE and LATCH Command�� Option Field�� Torq Feed Forward�� ���� ���� �ϵ��� �մϴ�.
    // �⺻���� MAX�� �����Ǿ� �ֽ��ϴ�.
    // �������� 0 ~ 4000H���� ���� �� �� �ֽ��ϴ�.
    // �������� 4000H�̻����� �����ϸ� ������ �� �̻����� �����ǳ� ������ 4000H���� ���� �˴ϴ�.
    [DllImport("AXL.dll")] public static extern uint AxmSetTorqFeedForward(int nAxisNo, uint uTorqFeedForward);
 
    // INTERPOLATE and LATCH Command�� Option Field�� Torq Feed Forward�� ���� �о���� �Լ� �Դϴ�.
    // �⺻���� MAX�� �����Ǿ� �ֽ��ϴ�.
    [DllImport("AXL.dll")] public static extern uint AxmGetTorqFeedForward(int nAxisNo, ref uint upTorqFeedForward);
 
    // INTERPOLATE and LATCH Command�� VFF Field�� Velocity Feed Forward�� ���� ���� �ϵ��� �մϴ�.
    // �⺻���� '0'�� �����Ǿ� �ֽ��ϴ�.
    // �������� 0 ~ FFFFH���� ���� �� �� �ֽ��ϴ�.
    [DllImport("AXL.dll")] public static extern uint AxmSetVelocityFeedForward(int nAxisNo, uint uVelocityFeedForward);
 
    // INTERPOLATE and LATCH Command�� VFF Field�� Velocity Feed Forward�� ���� �о���� �Լ� �Դϴ�.
    [DllImport("AXL.dll")] public static extern uint AxmGetVelocityFeedForward(int nAxisNo, ref uint upVelocityFeedForward);

    // Encoder type�� �����Ѵ�.
    // �⺻���� 0(TYPE_INCREMENTAL)�� �����Ǿ� �ֽ��ϴ�.
    // �������� 0 ~ 1���� ���� �� �� �ֽ��ϴ�.
    // ������ : 0(TYPE_INCREMENTAL), 1(TYPE_ABSOLUTE).
    [DllImport("AXL.dll")] public static extern uint AxmSignalSetEncoderType(int lAxisNo, uint uEncoderType);

    // Encoder type�� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmSignalGetEncoderType(int lAxisNo, ref uint upEncoderType);

    // Slave Firmware Update�� ���� �߰�
    //[DllImport("AXL.dll")] public static extern uint AxmSetSendAxisCommand(long lAxisNo, WORD wCommand, WORD* wpSendData, WORD wLength);

    //======== PCI-R1604-RTEX, RTEX-PM ���� �Լ�============================================================== 
    // ���� �Է� 2,3�� �Է½� JOG ���� �ӵ��� �����Ѵ�. 
    // ������ ���õ� ��� ����(Ex, PulseOutMethod, MoveUnitPerPulse ��)���� �Ϸ�� ���� �ѹ��� �����Ͽ��� �Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMotSetUserMotion(int lAxisNo, double dVelocity, double dAccel, double dDecel);

    // ���� �Է� 2,3�� �Է½� JOG ���� ���� ��� ���θ� �����Ѵ�.
    // ������ :  0(DISABLE), 1(ENABLE)
    [DllImport("AXL.dll")] public static extern uint AxmMotSetUserMotionUsage(int lAxisNo, uint dwUsage);

    // MPGP �Է��� ����Ͽ� Load/UnLoad ��ġ�� �ڵ����� �̵��ϴ� ��� ����. 
    [DllImport("AXL.dll")] public static extern uint AxmMotSetUserPosMotion(int lAxisNo, double dVelocity, double dAccel, double dDecel, double dLoadPos, double dUnLoadPos, uint dwFilter, uint dwDelay);

    // MPGP �Է��� ����Ͽ� Load/UnLoad ��ġ�� �ڵ����� �̵��ϴ� ��� ����. 
    // ������ :  0(DISABLE), 1(Position ��� A ���), 2(Position ��� B ���)
    [DllImport("AXL.dll")] public static extern uint AxmMotSetUserPosMotionUsage(int lAxisNo, uint dwUsage);
    //======================================================================================================== 

    //======== SIO-CN2CH, ���� ��ġ Ʈ���� ��� ��� ���� �Լ�================================================ 
    // �޸� ������ ���� �Լ�
    [DllImport("AXL.dll")] public static extern uint AxcKeWriteRamDataAddr(int lChannelNo, uint dwAddr, uint dwData);
    // �޸� ������ �б� �Լ�
    [DllImport("AXL.dll")] public static extern uint AxcKeReadRamDataAddr(int lChannelNo, uint dwAddr, ref uint dwpData);
    // �޸� �ʱ�ȭ �Լ�
    [DllImport("AXL.dll")] public static extern uint AxcKeResetRamDataAll(int lModuleNo, uint dwData);
    // Ʈ���� Ÿ�� �ƿ� ���� �Լ�
    [DllImport("AXL.dll")] public static extern uint AxcTriggerSetTimeout(int lChannelNo, uint dwTimeout);
    // Ʈ���� Ÿ�� �ƿ� Ȯ�� �Լ�
    [DllImport("AXL.dll")] public static extern uint AxcTriggerGetTimeout(int lChannelNo, ref uint dwpTimeout);
    // Ʈ���� ��� ���� Ȯ�� �Լ�
    [DllImport("AXL.dll")] public static extern uint AxcStatusGetWaitState(int lChannelNo, ref uint dwpState);
    // Ʈ���� ��� ���� ���� �Լ�
    [DllImport("AXL.dll")] public static extern uint AxcStatusSetWaitState(int lChannelNo, uint dwState);
    
    //���� ä�ο� ��ɾ� ����
    [DllImport("AXL.dll")] public static extern uint AxcKeSetCommandData32(int lChannelNo, uint dwCommand, uint dwData);
    
    //���� ä�ο� ��ɾ� ����
    [DllImport("AXL.dll")] public static extern uint AxcKeSetCommandData16(int lChannelNo, uint dwCommand, uint wData); 
    
    //���� ä���� �������� Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxcKeGetCommandData32(int lChannelNo, uint dwCommand, ref uint dwpData);
    
    //���� ä���� �������� Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxcKeGetCommandData16(int lChannelNo, uint dwCommand, ref uint wpData); 
    
    //======================================================================================================== 
	
    //======== PCI-N804/N404 ����, Sequence Motion ===================================================================
    // Sequence Motion�� �� ������ ���� �մϴ�. (�ּ� 1��)
    // lSeqMapNo : �� ��ȣ ������ ��� Sequence Motion Index Point
    // lSeqMapSize : �� ��ȣ ����
    // long* LSeqAxesNo : �� ��ȣ �迭
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqSetAxisMap(int lSeqMapNo, int lSeqMapSize, ref int lSeqAxesNo);
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqGetAxisMap(int lSeqMapNo, ref int lSeqMapSize, ref int lSeqAxesNo);

    // Sequence Motion�� ����(Master) ���� ���� �մϴ�. 
    // �ݵ�� AxmSeqSetAxisMap(...) �� ������ �� ������ �����Ͽ��� �մϴ�.
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqSetMasterAxisNo(int lSeqMapNo, int lMasterAxisNo);

    // Sequence Motion�� Node ���� ������ ���̺귯���� �˸��ϴ�.
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqBeginNode(int lSeqMapNo);

    // Sequence Motion�� Node ���� ���Ḧ ���̺귯���� �˸��ϴ�.
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqEndNode(int lSeqMapNo);

    // Sequence Motion�� ������ ���� �մϴ�.
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqStart(int lSeqMapNo, ref uint dwStartOption);

    // Sequence Motion�� �� Profile Node ������ ���̺귯���� �Է� �մϴ�.
    // ���� 1�� Sequence Motion�� ����ϴ���, *dPosition�� 1���� Array�� �����Ͽ� �ֽñ� �ٶ��ϴ�.
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqAddNode(int lSeqMapNo, ref double dPosition, double dVelocity, double dAcceleration, double dDeceleration, double dNextVelocity);

    // Sequence Motion�� ���� �� ���� ���� ���� Node Index�� �˷� �ݴϴ�.
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqGetNodeNum(int lSeqMapNo, ref int lCurNodeNo);

    // Sequence Motion�� �� Node Count�� Ȯ�� �մϴ�.
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqGetTotalNodeNum(int lSeqMapNo, ref int lTotalNodeCnt);

    // Sequence Motion�� ���� ���� ������ Ȯ�� �մϴ�.
    // dwInMotion : 0(���� ����), 1(���� ��)
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqIsMotion(int lSeqMapNo, ref uint dwInMotion);

    // Sequence Motion�� Memory�� Clear �մϴ�.
    // AxmSeqSetAxisMap(...), AxmSeqSetMasterAxisNo(...) ���� ������ ���� �����˴ϴ�.
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqWriteClear(int lSeqMapNo);

    // Sequence Motion�� ������ ���� �մϴ�.
    // dwStopMode : 0(EMERGENCY_STOP), 1(SLOWDOWN_STOP) 
    [DllImport("AXL.dll")]
    public static extern uint AxmSeqStop(int lSeqMapNo, uint dwStopMode);
    //======================================================================================================== 
}
