/****************************************************************************
*****************************************************************************
**
** File Name
** ---------
**
** AXD.CS
**
** COPYRIGHT (c) AJINEXTEK Co., LTD
**
*****************************************************************************
*****************************************************************************
**
** Description
** -----------
** Ajinextek Digital Library Header File
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

using System;
using System.Runtime.InteropServices;

public class CAXD
{
//========== ���� �� ��� ���� =================================================================================

    // DIO ����� �ִ��� Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxdInfoIsDIOModule(ref uint upStatus);
    
    // DIO ��� No Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxdInfoGetModuleNo(int lBoardNo, int lModulePos, ref int lpModuleNo);
    
    // DIO ����� ����� ���� Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxdInfoGetModuleCount(ref int lpModuleCount);
    
    // ������ ����� �Է� ���� ���� Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxdInfoGetInputCount(int lModuleNo, ref int lpCount);
    
    // ������ ����� ��� ���� ���� Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxdInfoGetOutputCount(int lModuleNo, ref int lpCount);
    
    // ������ ��� ��ȣ�� ���̽� ���� ��ȣ, ��� ��ġ, ��� ID Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxdInfoGetModule(int lModuleNo, ref int lpBoardNo, ref int lpModulePos, ref uint upModuleID);

    // �ش� ����� ��� ������ �������� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxdInfoGetModuleStatus(int lModuleNo);

//========== ���ͷ�Ʈ ���� Ȯ�� =================================================================================

    // ������ ��⿡ ���ͷ�Ʈ �޽����� �޾ƿ��� ���Ͽ� ������ �޽���, �ݹ� �Լ� �Ǵ� �̺�Ʈ ����� ���
    //========= ���ͷ�Ʈ ���� �Լ� ======================================================================================
    // �ݹ� �Լ� ����� �̺�Ʈ �߻� ������ ��� �ݹ� �Լ��� ȣ�� ������ ���� ������ �̺�Ʈ�� �������� �� �ִ� ������ ������
    // �ݹ� �Լ��� ������ ���� �� ������ ���� ���μ����� ��ü�Ǿ� �ְ� �ȴ�.
    // ��, �ݹ� �Լ� ���� ���ϰ� �ɸ��� �۾��� ���� ��쿡�� ��뿡 ���Ǹ� ���Ѵ�. 
    // �̺�Ʈ ����� ��������� �̿��Ͽ� ���ͷ�Ʈ �߻����θ� ���������� �����ϰ� �ִٰ� ���ͷ�Ʈ�� �߻��ϸ� 
    // ó�����ִ� �������, ������ ������ ���� �ý��� �ڿ��� �����ϰ� �ִ� ������ ������
    // ���� ������ ���ͷ�Ʈ�� �����ϰ� ó������ �� �ִ� ������ �ִ�.
    // �Ϲ������δ� ���� ������ ������, ���ͷ�Ʈ�� ����ó���� �ֿ� ���ɻ��� ��쿡 ���ȴ�. 
    // �̺�Ʈ ����� �̺�Ʈ�� �߻� ���θ� �����ϴ� Ư�� �����带 ����Ͽ� ���� ���μ����� ������ ���۵ǹǷ�
    // MultiProcessor �ý��۵�� �ڿ��� ���� ȿ�������� ����� �� �ְ� �Ǿ� Ư�� �����ϴ� ����̴�.
    // ���ͷ�Ʈ �޽����� �޾ƿ��� ���Ͽ� ������ �޽��� �Ǵ� �ݹ� �Լ��� ����Ѵ�.
    // (�޽��� �ڵ�, �޽��� ID, �ݹ��Լ�, ���ͷ�Ʈ �̺�Ʈ)
    //    hWnd            : ������ �ڵ�, ������ �޼����� ������ ���. ������� ������ NULL�� �Է�.
    //    uMessage        : ������ �ڵ��� �޼���, ������� �ʰų� ����Ʈ���� ����Ϸ��� 0�� �Է�.
    //    proc            : ���ͷ�Ʈ �߻��� ȣ��� �Լ��� ������, ������� ������ NULL�� �Է�.
    //    pEvent          : �̺�Ʈ ������� �̺�Ʈ �ڵ�
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptSetModule(int lModuleNo, IntPtr hWnd, uint uMessage, CAXHS.AXT_INTERRUPT_PROC pProc, ref uint pEvent);
    
    // ������ ����� ���ͷ�Ʈ ��� ���� ����
    //======================================================//
    // uUse        : DISABLE(0)    // ���ͷ�Ʈ ����
    //             : ENABLE(1)     // ���ͷ�Ʈ ����
    //======================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptSetModuleEnable(int lModuleNo, uint uUse);
    
    // ������ ����� ���ͷ�Ʈ ��� ���� Ȯ��
    //======================================================//
    // *upUse      : DISABLE(0)    // ���ͷ�Ʈ ����
    //             : ENABLE(1)     // ���ͷ�Ʈ ����
    //======================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptGetModuleEnable(int lModuleNo, ref uint upUse);
    
    // ���ͷ�Ʈ �߻� ��ġ Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptRead(ref int lpModuleNo, ref uint upFlag);

//========== ���ͷ�Ʈ ��� / �ϰ� ���� ���� Ȯ�� =================================================================================
    // ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� bit ������ ��� �Ǵ� �ϰ� ���� ���� ����
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // uMode        : DOWN_EDGE(0)
    //              : UP_EDGE(1)
    // uValue       : DISABLE(0)
    //              : ENABLE(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptEdgeSetBit(int lModuleNo, int lOffset, uint uMode, uint uValue);
    
    // ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� byte ������ ��� �Ǵ� �ϰ� ���� ���� ����
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // uMode        : DOWN_EDGE(0)
    //              : UP_EDGE(1)
    // uValue       : 0x00 ~ 0x0FF ('1'�� Setting �� �κ� ���ͷ�Ʈ ����)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptEdgeSetByte(int lModuleNo, int lOffset, uint uMode, uint uValue);
    
    // ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� word ������ ��� �Ǵ� �ϰ� ���� ���� ����
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // uMode        : DOWN_EDGE(0)
    //              : UP_EDGE(1)
    // uValue       : 0x00 ~ 0x0FFFF ('1'�� Setting �� �κ� ���ͷ�Ʈ ����)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptEdgeSetWord(int lModuleNo, int lOffset, uint uMode, uint uValue);
    
    // ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� double word ������ ��� �Ǵ� �ϰ� ���� ���� ����
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // uMode        : DOWN_EDGE(0)
    //              : UP_EDGE(1)
    // uValue       : 0x00 ~ 0x0FFFFFFFF ('1'�� Setting �� �κ� ���ͷ�Ʈ ����)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptEdgeSetDword(int lModuleNo, int lOffset, uint uMode, uint uValue);
    
    // ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� bit ������ ��� �Ǵ� �ϰ� ���� ���� Ȯ��
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // uMode        : DOWN_EDGE(0)
    //              : UP_EDGE(1)
    // *upValue     : 0x00 ~ 0x0FF ('1'�� Setting �� �κ� ���ͷ�Ʈ ����)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptEdgeGetBit(int lModuleNo, int lOffset, uint uMode, ref uint upValue);
    
    // ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� byte ������ ��� �Ǵ� �ϰ� ���� ���� Ȯ��
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // uMode        : DOWN_EDGE(0)
    //              : UP_EDGE(1)
    // *upValue     : 0x00 ~ 0x0FF ('1'�� Setting �� �κ� ���ͷ�Ʈ ����)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptEdgeGetByte(int lModuleNo, int lOffset, uint uMode, ref uint upValue);
    
    // ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� word ������ ��� �Ǵ� �ϰ� ���� ���� Ȯ��
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // uMode        : DOWN_EDGE(0)
    //              : UP_EDGE(1)
    // *upValue     : 0x00 ~ 0x0FFFFFFFF ('1'�� Setting �� �κ� ���ͷ�Ʈ ����)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptEdgeGetWord(int lModuleNo, int lOffset, uint uMode, ref uint upValue);
    
    // ������ �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� double word ������ ��� �Ǵ� �ϰ� ���� ���� Ȯ��
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // uMode        : DOWN_EDGE(0)
    //              : UP_EDGE(1)
    // *upValue     : 0x00 ~ 0x0FFFFFFFF ('1'�� Setting �� �κ� ���ͷ�Ʈ ����)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptEdgeGetDword(int lModuleNo, int lOffset, uint uMode, ref uint upValue);
    
    // ��ü �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset ��ġ���� bit ������ ��� �Ǵ� �ϰ� ���� ���� ����
    //===============================================================================================//
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // uMode        : DOWN_EDGE(0)
    //              : UP_EDGE(1)
    // uValue       : DISABLE(0)
    //              : ENABLE(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptEdgeSet(int lOffset, uint uMode, uint uValue);
    
    // ��ü �Է� ���� ���, Interrupt Rising / Falling Edge register�� Offset �������� bit ������ ��� �Ǵ� �ϰ� ���� ���� Ȯ��
    //===============================================================================================//
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // uMode        : DOWN_EDGE(0)
    //              : UP_EDGE(1)
    // *upValue     : DISABLE(0)
    //              : ENABLE(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiInterruptEdgeGet(int lOffset, uint uMode, ref uint upValue);

//========== ����� ���� ���� Ȯ�� =================================================================================
//==�Է� ���� ���� Ȯ��
    // ������ �Է� ���� ����� Offset ��ġ���� bit ������ ������ ������ ����
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // uLevel       : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiLevelSetInportBit(int lModuleNo, int lOffset, uint uLevel);
    
    // ������ �Է� ���� ����� Offset ��ġ���� byte ������ ������ ������ ����
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // uLevel       : 0x00 ~ 0x0FF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiLevelSetInportByte(int lModuleNo, int lOffset, uint uLevel);
    
    // ������ �Է� ���� ����� Offset ��ġ���� word ������ ������ ������ ����
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // uLevel       : 0x00 ~ 0x0FFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiLevelSetInportWord(int lModuleNo, int lOffset, uint uLevel);
    
    // ������ �Է� ���� ����� Offset ��ġ���� double word ������ ������ ������ ����
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // uLevel       : 0x00 ~ 0x0FFFFFFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiLevelSetInportDword(int lModuleNo, int lOffset, uint uLevel);
    
    // ������ �Է� ���� ����� Offset ��ġ���� bit ������ ������ ������ Ȯ��
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // *upLevel     : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiLevelGetInportBit(int lModuleNo, int lOffset, ref uint upLevel);
    
    // ������ �Է� ���� ����� Offset ��ġ���� byte ������ ������ ������ Ȯ��
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // *upLevel     : 0x00 ~ 0x0FF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiLevelGetInportByte(int lModuleNo, int lOffset, ref uint upLevel);
    
    // ������ �Է� ���� ����� Offset ��ġ���� word ������ ������ ������ Ȯ��
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // *upLevel     : 0x00 ~ 0x0FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiLevelGetInportWord(int lModuleNo, int lOffset, ref uint upLevel);
    
    // ������ �Է� ���� ����� Offset ��ġ���� double word ������ ������ ������ Ȯ��
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // *upLevel     : 0x00 ~ 0x0FFFFFFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiLevelGetInportDword(int lModuleNo, int lOffset, ref uint upLevel);
    
    // ��ü �Է� ���� ����� Offset ��ġ���� bit ������ ������ ������ ����
    //===============================================================================================//
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // uLevel       : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiLevelSetInport(int lOffset, uint uLevel);
    
    // ��ü �Է� ���� ����� Offset ��ġ���� bit ������ ������ ������ Ȯ��
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // *upLevel     : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiLevelGetInport(int lOffset, ref uint upLevel);
    
//==��� ���� ���� Ȯ��
    // ������ ��� ���� ����� Offset ��ġ���� bit ������ ������ ������ ����
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : ��� ������ ���� Offset ��ġ
    // uLevel       : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoLevelSetOutportBit(int lModuleNo, int lOffset, uint uLevel);
    
    // ������ ��� ���� ����� Offset ��ġ���� byte ������ ������ ������ ����
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : ��� ������ ���� Offset ��ġ
    // uLevel       : 0x00 ~ 0x0FF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoLevelSetOutportByte(int lModuleNo, int lOffset, uint uLevel);
    
    // ������ ��� ���� ����� Offset ��ġ���� word ������ ������ ������ ����
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : ��� ������ ���� Offset ��ġ
    // uLevel       : 0x00 ~ 0x0FFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoLevelSetOutportWord(int lModuleNo, int lOffset, uint uLevel);
    
    // ������ ��� ���� ����� Offset ��ġ���� double word ������ ������ ������ ����
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : ��� ������ ���� Offset ��ġ
    // uLevel       : 0x00 ~ 0x0FFFFFFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoLevelSetOutportDword(int lModuleNo, int lOffset, uint uLevel);
    
    // ������ ��� ���� ����� Offset ��ġ���� bit ������ ������ ������ Ȯ��
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : ��� ������ ���� Offset ��ġ
    // *upLevel     : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoLevelGetOutportBit(int lModuleNo, int lOffset, ref uint upLevel);
    
    // ������ ��� ���� ����� Offset ��ġ���� byte ������ ������ ������ Ȯ��
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : ��� ������ ���� Offset ��ġ
    // uLevel       : 0x00 ~ 0x0FF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoLevelGetOutportByte(int lModuleNo, int lOffset, ref uint upLevel);
    
    // ������ ��� ���� ����� Offset ��ġ���� word ������ ������ ������ Ȯ��
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : ��� ������ ���� Offset ��ġ
    // uLevel       : 0x00 ~ 0x0FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoLevelGetOutportWord(int lModuleNo, int lOffset, ref uint upLevel);
    
    // ������ ��� ���� ����� Offset ��ġ���� double word ������ ������ ������ Ȯ��
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : ��� ������ ���� Offset ��ġ
    // uLevel       : 0x00 ~ 0x0FFFFFFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoLevelGetOutportDword(int lModuleNo, int lOffset, ref uint upLevel);
    
    // ��ü ��� ���� ����� Offset ��ġ���� bit ������ ������ ������ ����
    //===============================================================================================//
    // lOffset      : ��� ������ ���� Offset ��ġ
    // uLevel       : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoLevelSetOutport(int lOffset, uint uLevel);
    
    // ��ü ��� ���� ����� Offset ��ġ���� bit ������ ������ ������ Ȯ��
    //===============================================================================================//
    // lOffset      : ��� ������ ���� Offset ��ġ
    // *upLevel     : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoLevelGetOutport(int lOffset, ref uint upLevel);
    
//========== ����� ��Ʈ ���� �б� =================================================================================
//==��� ��Ʈ ����
    // ��ü ��� ���� ����� Offset ��ġ���� bit ������ �����͸� ���
    //===============================================================================================//
    // lOffset      : ��� ������ ���� Offset ��ġ
    // uLevel       : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoWriteOutport(int lOffset, uint uValue);
    
    // ������ ��� ���� ����� Offset ��ġ���� bit ������ �����͸� ���
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : ��� ������ ���� Offset ��ġ
    // uLevel       : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoWriteOutportBit(int lModuleNo, int lOffset, uint uValue);
    
    // ������ ��� ���� ����� Offset ��ġ���� byte ������ �����͸� ���
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : ��� ������ ���� Offset ��ġ
    // uValue       : 0x00 ~ 0x0FF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoWriteOutportByte(int lModuleNo, int lOffset, uint uValue);
    
    // ������ ��� ���� ����� Offset ��ġ���� word ������ �����͸� ���
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : ��� ������ ���� Offset ��ġ
    // uValue       : 0x00 ~ 0x0FFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoWriteOutportWord(int lModuleNo, int lOffset, uint uValue);
    
    // ������ ��� ���� ����� Offset ��ġ���� double word ������ �����͸� ���
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : ��� ������ ���� Offset ��ġ
    // uValue       : 0x00 ~ 0x0FFFFFFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoWriteOutportDword(int lModuleNo, int lOffset, uint uValue);
    
//==��� ��Ʈ �б�    
    // ��ü ��� ���� ����� Offset ��ġ���� bit ������ �����͸� �б�
    //===============================================================================================//
    // lOffset      : ��� ������ ���� Offset ��ġ
    // *upLevel     : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoReadOutport(int lOffset, ref uint upValue);
    
    // ������ ��� ���� ����� Offset ��ġ���� bit ������ �����͸� �б�
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : ��� ������ ���� Offset ��ġ
    // *upLevel     : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoReadOutportBit(int lModuleNo, int lOffset, ref uint upValue);
    
    // ������ ��� ���� ����� Offset ��ġ���� byte ������ �����͸� �б�
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : ��� ������ ���� Offset ��ġ
    // *upValue     : 0x00 ~ 0x0FF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoReadOutportByte(int lModuleNo, int lOffset, ref uint upValue);
    
    // ������ ��� ���� ����� Offset ��ġ���� word ������ �����͸� �б�
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : ��� ������ ���� Offset ��ġ
    // *upValue     : 0x00 ~ 0x0FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoReadOutportWord(int lModuleNo, int lOffset, ref uint upValue);
    
    // ������ ��� ���� ����� Offset ��ġ���� double word ������ �����͸� �б�
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : ��� ������ ���� Offset ��ġ
    // *upValue     : 0x00 ~ 0x0FFFFFFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoReadOutportDword(int lModuleNo, int lOffset, ref uint upValue);
    
//==�Է� ��Ʈ �ϱ�    
    // ��ü �Է� ���� ����� Offset ��ġ���� bit ������ �����͸� �б�
    //===============================================================================================//
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // *upValue     : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiReadInport(int lOffset, ref uint upValue);
    
    // ������ �Է� ���� ����� Offset ��ġ���� bit ������ �����͸� �б�
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // *upValue     : LOW(0)
    //              : HIGH(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiReadInportBit(int lModuleNo, int lOffset, ref uint upValue);
    
    // ������ �Է� ���� ����� Offset ��ġ���� byte ������ �����͸� �б�
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // *upValue     : 0x00 ~ 0x0FF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiReadInportByte(int lModuleNo, int lOffset, ref uint upValue);
    
    // ������ �Է� ���� ����� Offset ��ġ���� word ������ �����͸� �б�
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // *upValue     : 0x00 ~ 0x0FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiReadInportWord(int lModuleNo, int lOffset, ref uint upValue);
    
    // ������ �Է� ���� ����� Offset ��ġ���� double word ������ �����͸� �б�
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // *upValue     : 0x00 ~ 0x0FFFFFFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiReadInportDword(int lModuleNo, int lOffset, ref uint upValue);

    //== MLII �� M-Systems DIO(R7 series) ���� �Լ�.
    // ������ ��⿡ ������ �Է� ������ Ȯ�� ��� ����� Offset ��ġ���� bit ������ �����͸� �б�
    //===============================================================================================//
    // lModuleNo   : ��� ��ȣ
    // lOffset     : �Է� ������ ���� Offset ��ġ(0~15)
    // *upValue    : LOW(0)
    //             : HIGH(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdReadExtInportBit(int lModuleNo, int lOffset, ref uint upValue);

    // ������ ��⿡ ������ �Է� ������ Ȯ�� ��� ����� Offset ��ġ���� byte ������ �����͸� �б�
    //===============================================================================================//
    // lModuleNo   : ��� ��ȣ
    // lOffset     : �Է� ������ ���� Offset ��ġ(0~1)
    // *upValue    : 0x00 ~ 0x0FF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdReadExtInportByte(int lModuleNo, int lOffset, ref uint upValue);

    // ������ ��⿡ ������ �Է� ������ Ȯ�� ��� ����� Offset ��ġ���� word ������ �����͸� �б�
    //===============================================================================================//
    // lModuleNo   : ��� ��ȣ
    // lOffset     : �Է� ������ ���� Offset ��ġ(0)
    // *upValue    : 0x00 ~ 0x0FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdReadExtInportWord(int lModuleNo, int lOffset, ref uint upValue);

    // ������ ��⿡ ������ �Է� ������ Ȯ�� ��� ����� Offset ��ġ���� dword ������ �����͸� �б�
    //===============================================================================================//
    // lModuleNo   : ��� ��ȣ
    // lOffset     : �Է� ������ ���� Offset ��ġ(0)
    // *upValue    : 0x00 ~ 0x00000FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdReadExtInportDword(int lModuleNo, int lOffset, ref uint upValue);

    // ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� bit ������ �����͸� �б�
    //===============================================================================================//
    // lModuleNo   : ��� ��ȣ
    // lOffset     : ��� ������ ���� Offset ��ġ(0~15)
    // *upValue    : LOW(0)
    //             : HIGH(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdReadExtOutportBit(int lModuleNo, int lOffset, ref uint upValue);

    // ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� byte ������ �����͸� �б�
    //===============================================================================================//
    // lModuleNo   : ��� ��ȣ
    // lOffset     : ��� ������ ���� Offset ��ġ(0~1)
    // *upValue    : 0x00 ~ 0x0FF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdReadExtOutportByte(int lModuleNo, int lOffset, ref uint upValue);

    // ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� word ������ �����͸� �б�
    //===============================================================================================//
    // lModuleNo   : ��� ��ȣ
    // lOffset     : ��� ������ ���� Offset ��ġ(0)
    // *upValue    : 0x00 ~ 0x0FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdReadExtOutportWord(int lModuleNo, int lOffset, ref uint upValue);

    // ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� dword ������ �����͸� �б�
    //===============================================================================================//
    // lModuleNo   : ��� ��ȣ
    // lOffset     : ��� ������ ���� Offset ��ġ(0)
    // *upValue    : 0x00 ~ 0x00000FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdReadExtOutportDword(int lModuleNo, int lOffset, ref uint upValue);

    // ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� bit ������ ������ ���
    //===============================================================================================//
    // lModuleNo   : ��� ��ȣ
    // lOffset     : ��� ������ ���� Offset ��ġ
    // uValue      : LOW(0)
    //             : HIGH(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdWriteExtOutportBit(int lModuleNo, int lOffset, uint uValue);

    // ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� byte ������ ������ ���
    //===============================================================================================//
    // lModuleNo   : ��� ��ȣ
    // lOffset     : ��� ������ ���� Offset ��ġ(0~1)
    // uValue      : 0x00 ~ 0x0FF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdWriteExtOutportByte(int lModuleNo, int lOffset, uint uValue);

    // ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� word ������ ������ ���
    //===============================================================================================//
    // lModuleNo   : ��� ��ȣ
    // lOffset     : ��� ������ ���� Offset ��ġ(0)
    // uValue    : 0x00 ~ 0x0FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdWriteExtOutportWord(int lModuleNo, int lOffset, uint uValue);

    // ������ ��⿡ ������ ��� ������ Ȯ�� ��� ����� Offset ��ġ���� dword ������ ������ ���
    //===============================================================================================//
    // lModuleNo   : ��� ��ȣ
    // lOffset     : ��� ������ ���� Offset ��ġ(0)
    // uValue    : 0x00 ~ 0x00000FFFF('1'�� ���� ��Ʈ�� HIGH, '0'���� ���� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdWriteExtOutportDword(int lModuleNo, int lOffset, uint uValue);

    // ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� bit ������ ������ ������ ����
    //===============================================================================================//
    // lModuleNo   : ��� ��ȣ
    // lOffset     : �Է� ������ ���� Offset ��ġ(0~15)
    // uLevel      : LOW(0)
    //             : HIGH(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdLevelSetExtportBit(int lModuleNo, int lOffset, uint uLevel);

    // ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� byte ������ ������ ������ ����
    //===============================================================================================//
    // lModuleNo   : ��� ��ȣ
    // lOffset     : �Է� ������ ���� Offset ��ġ(0~1)
    // uLevel      : 0x00 ~ 0xFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdLevelSetExtportByte(int lModuleNo, int lOffset, uint uLevel);

    // ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� word ������ ������ ������ ����
    //===============================================================================================//
    // lModuleNo   : ��� ��ȣ
    // lOffset     : �Է� ������ ���� Offset ��ġ(0)
    // uLevel      : 0x00 ~ 0xFFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdLevelSetExtportWord(int lModuleNo, int lOffset, uint uLevel);

    // ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� dword ������ ������ ������ ����
    //===============================================================================================//
    // lModuleNo   : ��� ��ȣ
    // lOffset     : �Է� ������ ���� Offset ��ġ(0)
    // uLevel      : 0x00 ~ 0x0000FFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdLevelSetExtportDword(int lModuleNo, int lOffset, uint uLevel);

    // ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� bit ������ ������ ���� Ȯ��
    //===============================================================================================//
    // lModuleNo   : ��� ��ȣ
    // lOffset     : �Է� ������ ���� Offset ��ġ(0~15)
    // *upLevel      : LOW(0)
    //             : HIGH(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdLevelGetExtportBit(int lModuleNo, int lOffset, ref uint upLevel);

    // ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� byte ������ ������ ���� Ȯ��
    //===============================================================================================//
    // lModuleNo   : ��� ��ȣ
    // lOffset     : �Է� ������ ���� Offset ��ġ(0~1)
    // *upLevel      : 0x00 ~ 0xFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdLevelGetExtportByte(int lModuleNo, int lOffset, ref uint upLevel);

    // ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� word ������ ������ ���� Ȯ��
    //===============================================================================================//
    // lModuleNo   : ��� ��ȣ
    // lOffset     : �Է� ������ ���� Offset ��ġ(0)
    // *upLevel      : 0x00 ~ 0xFFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdLevelGetExtportWord(int lModuleNo, int lOffset, ref uint upLevel);

    // ������ ��⿡ ������ ��/��� ������ Ȯ�� ��� ����� Offset ��ġ���� dword ������ ������ ���� Ȯ��
    //===============================================================================================//
    // lModuleNo   : ��� ��ȣ
    // lOffset     : �Է� ������ ���� Offset ��ġ(0)
    // *upLevel      : 0x00 ~ 0x0000FFFF('1'�� ���� �� ��Ʈ�� HIGH, '0'���� ���� �� ��Ʈ�� LOW)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdLevelGetExtportDword(int lModuleNo, int lOffset, ref uint upLevel);
    
//========== ��� �Լ� =================================================================================
    // ������ �Է� ���� ����� Offset ��ġ���� ��ȣ�� Off���� On���� �ٲ������ Ȯ��
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // *upValue     : FALSE(0)
    //              : TRUE(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiIsPulseOn(int lModuleNo, int lOffset, ref uint upValue);
    
    // ������ �Է� ���� ����� Offset ��ġ���� ��ȣ�� On���� Off���� �ٲ������ Ȯ��
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // *upValue     : FALSE(0)
    //              : TRUE(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiIsPulseOff(int lModuleNo, int lOffset, ref uint upValue);
    
    // ������ �Է� ���� ����� Offset ��ġ���� ��ȣ�� count ��ŭ ȣ��� ���� On ���·� �����ϴ��� Ȯ��
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : �Է� ������ ���� Offset ��ġ
    // lCount       : 0 ~ 0x7FFFFFFF(2147483647)
    // *upValue     : FALSE(0)
    //              : TRUE(1)
    // lStart       : 1(���� ȣ��)
    //              : 0(�ݺ� ȣ��)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiIsOn(int lModuleNo, int lOffset, int lCount, ref uint upValue, int lStart);
    
    // ������ �Է� ���� ����� Offset ��ġ���� ��ȣ�� count ��ŭ ȣ��� ���� Off ���·� �����ϴ��� Ȯ��
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : ��� ������ ���� Offset ��ġ
    // lCount       : 0 ~ 0x7FFFFFFF(2147483647)
    // *upValue     : FALSE(0)
    //              : TRUE(1)
    // lStart       : 1(���� ȣ��)
    //              : 0(�ݺ� ȣ��)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdiIsOff(int lModuleNo, int lOffset, int lCount, ref uint upValue, int lStart);
    
    // ������ ��� ���� ����� Offset ��ġ���� ������ mSec���� On�� �����ϴٰ� Off ��Ŵ
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : ��� ������ ���� Offset ��ġ
    // lCount       : 0 ~ 0x7FFFFFFF(2147483647)
    // lmSec        : 1 ~ 30000
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoOutPulseOn(int lModuleNo, int lOffset, int lmSec);
    
    // ������ ��� ���� ����� Offset ��ġ���� ������ mSec���� Off�� �����ϴٰ� On ��Ŵ
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : ��� ������ ���� Offset ��ġ
    // lCount       : 0 ~ 0x7FFFFFFF(2147483647)
    // lmSec        : 1 ~ 30000
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoOutPulseOff(int lModuleNo, int lOffset, int lmSec);
    
    // ������ ��� ���� ����� Offset ��ġ���� ������ Ƚ��, ������ �������� ����� �� ������ ��»��¸� ������
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : ��� ������ ���� Offset ��ġ
    // lInitState   : Off(0)
    //              : On(1)
    // lmSecOn      : 1 ~ 30000
    // lmSecOff     : 1 ~ 30000
    // lCount       : 1 ~ 0x7FFFFFFF(2147483647)
    //              : -1 ���� ���
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoToggleStart(int lModuleNo, int lOffset, int lInitState, int lmSecOn, int lmSecOff, int lCount);
    
    // ������ ��� ���� ����� Offset ��ġ���� ������� ����� ������ ��ȣ ���·� ���� ��Ŵ
    //===============================================================================================//
    // lModuleNo    : ��� ��ȣ
    // lOffset      : ��� ������ ���� Offset ��ġ
    // uOnOff       : Off(0)
    //              : On(1)
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoToggleStop(int lModuleNo, int lOffset, uint uOnOff);

    // ������ ��� ����� Network�� ���� ���� ��� ��� ���¸� ��� Byte ������ �����Ѵ�.
    //===============================================================================================//
    // lModuleNo   : ��� ��ȣ
    // dwSize      : ���� �� Byte ��(ex. RTEX-DB32 : 2, RTEX-DO32 : 4)
    // dwaSetValue : ���� �� ���� ��(Default�� Network ���� ���� �� ���� ����)
    //             : 0 --> Network ���� ���� �� ���� ����
    //             : 1 --> On
    //             : 2 --> Off
    //===============================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxdoSetNetworkErrorAct(int lModuleNo, uint dwSize, ref uint dwaSetValue);

    [DllImport("AXL.dll")] public static extern uint AxdSetContactNum(int lModuleNo, uint dwInputNum, uint dwOutputNum);

    [DllImport("AXL.dll")] public static extern uint AxdGetContactNum(int lModuleNo, ref uint dwpInputNum, ref uint dwpOutputNum);
}

