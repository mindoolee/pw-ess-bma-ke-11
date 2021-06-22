/****************************************************************************
*****************************************************************************
**
** File Name
** ---------
**
** AXL.CS
**
** COPYRIGHT (c) AJINEXTEK Co., LTD
**
*****************************************************************************
*****************************************************************************
**
** Description
** -----------
** Ajinextek Library Header File
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

public class CAXL
{
//========== ���̺귯�� �ʱ�ȭ ========================================================================

    // ���̺귯�� �ʱ�ȭ
    [DllImport("AXL.dll")] public static extern uint AxlOpen(int lIrqNo);
    // ���̺귯�� �ʱ�ȭ�� �ϵ���� Ĩ�� ������ ���� ����.
    [DllImport("AXL.dll")] public static extern uint AxlOpenNoReset(uint lIrqNo);
    // ���̺귯�� ����� ����
    [DllImport("AXL.dll")] public static extern int  AxlClose();
    // ���̺귯���� �ʱ�ȭ �Ǿ� �ִ� �� Ȯ��
    [DllImport("AXL.dll")] public static extern int  AxlIsOpened();

    // ���ͷ�Ʈ�� ����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxlInterruptEnable();
    // ���ͷ�Ʈ�� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxlInterruptDisable();

//========== ���̺귯�� �� ���̽� ���� ���� ===========================================================

    // ��ϵ� ���̽� ������ ���� Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxlGetBoardCount(ref int lpBoardCount);
    // ���̺귯�� ���� Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxlGetLibVersion(ref byte szVersion);
    // Network��ǰ�� �� ��⺰ ������¸� Ȯ���ϴ� �Լ�
    [DllImport("AXL.dll")] public static extern uint AxlGetModuleNodeStatus(int nBoardNo, int nModulePos);
    // �ش� ���尡 ���� ������ �������� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxlGetBoardStatus(int nBoardNo);
    // Network ��ǰ�� Configuration Lock ���¸� ��ȯ�Ѵ�.
    // *wpLockMode  : DISABLE(0), ENABLE(1)
    [DllImport("AXL.dll")] public static extern uint AxlGetLockMode(int nBoardNo, ref uint upLockMode);

    [DllImport("AXL.dll")]
    public static extern uint AxlSetLockMode(int nBoardNo, uint upLockMode);

    // Network ��ǰ�� ScanTime ���¸� �����Ѵ�.
    [DllImport("AXL.dll")]
    public static extern uint AxlSetNetComTime(int nBoardNo, byte szNetComTime);

    // Network ��ǰ�� ScanTime ���¸� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")]
    public static extern uint AxlGetNetComTime(int nBoardNo, ref byte szNetComTime);
//========= �α� ���� =================================================================================

    // EzSpy�� ����� �޽��� ���� ����
    // uLevel : 0 - 3 ����
    // LEVEL_NONE(0)    : ��� �޽����� ������� �ʴ´�.
    // LEVEL_ERROR(1)   : ������ �߻��� �޽����� ����Ѵ�.
    // LEVEL_RUNSTOP(2) : ��ǿ��� Run / Stop ���� �޽����� ����Ѵ�.
    // LEVEL_FUNCTION(3): ��� �޽����� ����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxlSetLogLevel(uint uLevel);
    // EzSpy�� ����� �޽��� ���� Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxlGetLogLevel(ref uint upLevel);

//========== MLIII =================================================================================
    // Network��ǰ�� �� ����� �˻��� �����ϴ� �Լ�
    [DllImport("AXL.dll")] public static extern uint AxlScanStart(int lBoardNo, long lNet);
    // Network��ǰ �� ������ ��� ����� connect�ϴ� �Լ�
    [DllImport("AXL.dll")] public static extern uint AxlBoardConnect(int lBoardNo, long lNet);
    // Network��ǰ �� ������ ��� ����� Disconnect�ϴ� �Լ�
    [DllImport("AXL.dll")] public static extern uint AxlBoardDisconnect(int lBoardNo, long lNet);
}

