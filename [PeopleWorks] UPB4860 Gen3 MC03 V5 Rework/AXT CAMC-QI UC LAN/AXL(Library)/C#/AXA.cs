/****************************************************************************
*****************************************************************************
**
** File Name
** ----------
**
** AXA.CS
**
** COPYRIGHT (c) AJINEXTEK Co., LTD
**
*****************************************************************************
*****************************************************************************
**
** Description
** -----------
** Ajinextek Analog Library Header File
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

using System;
using System.Runtime.InteropServices;

public class CAXA
{
//========== ���� �� ��� ���� Ȯ�� �Լ� =============================================================
    //AIO ����� �ִ��� Ȯ���Ѵ�    
    [DllImport("AXL.dll")] public static extern uint AxaInfoIsAIOModule(ref uint upStatus);
    
    //��� No�� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaInfoGetModuleNo(int lBoardNo, int lModulePos, ref int lpModuleNo);
    
    //AIO ����� ������ Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaInfoGetModuleCount(ref int lpModuleCount);
    
    //������ ����� �Է� ä�� ���� Ȯ���Ѵ�
    [DllImport("AXL.dll")] public static extern uint AxaInfoGetInputCount(int lModuleNo, ref int lpCount);
    
    //������ ����� ��� ä�� ���� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaInfoGetOutputCount(int lModuleNo, ref int lpCount);

    //������ ����� ù ��° ä�� ��ȣ�� Ȯ���Ѵ�.(�Է� ����,��� ���� ����)
    [DllImport("AXL.dll")] public static extern uint AxaInfoGetChannelNoOfModuleNo(int lModuleNo, ref int lpChannelNo);
    
    //������ ����� ù ��° �Է� ä�� ��ȣ�� Ȯ���Ѵ�.(�Է� ���, �Է�/��� ���� ����)
    [DllImport("AXL.dll")] public static extern uint AxaInfoGetChannelNoAdcOfModuleNo(int lModuleNo, ref int lpChannelNo);

    //������ ����� ù ��° ��� ä�� ��ȣ�� Ȯ���Ѵ�.(��� ���, �Է�/��� ���� ����)
    [DllImport("AXL.dll")] public static extern uint AxaInfoGetChannelNoDacOfModuleNo(int lModuleNo, ref int lpChannelNo);
    
    //������ ��� ��ȣ�� ���̽� ���� ��ȣ, ��� ��ġ, ��� ID�� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaInfoGetModule(int lModuleNo, ref int lpBoardNo, ref int lpModulePos, ref uint upModuleID);
    
    // �ش� ����� ��� ������ �������� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaInfoGetModuleStatus(int lModuleNo);
    
//========== �Է� ��� ���� �˻� �Լ� ================================================================
    //������ �Է� ä�� ��ȣ�� ��� ��ȣ�� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaiInfoGetModuleNoOfChannelNo(int lChannelNo, ref int lpModuleNo);
    
    //�Ƴ��α� �Է� ����� ��ü ä�� ������ Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaiInfoGetChannelCount(ref int lpChannelCount);

    //========== �Է� ��� ���ͷ�Ʈ/ä�� �̺�Ʈ ���� �� Ȯ�� �Լ� ====================================
    //������ ä�ο� �̺�Ʈ �޽����� �޾ƿ��� ���Ͽ� ������ �޽���, �ݹ� �Լ� �Ǵ� �̺�Ʈ ����� ����Ѵ�. H/W Ÿ�̸�(Timer Trigger Mode, External Trigger Mode)�� �̿�, ������ ������ ���� ���۽�(AxaStartMultiChannelAdc ����)�� ����Ѵ�.
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
    [DllImport("AXL.dll")] public static extern uint AxaiEventSetChannel(int lModuleNo, IntPtr hWnd, uint uMessage, CAXHS.AXT_INTERRUPT_PROC pProc, ref uint pEvent);
    
    //������ �Է� ä�ο� �̺�Ʈ ��� ������ �����Ѵ�.
    //======================================================
    // uUse        : DISABLE(0)    // �̺�Ʈ ����
    //             : ENABLE(1)     // �̺�Ʈ ����
    //======================================================
    [DllImport("AXL.dll")] public static extern uint AxaiEventSetChannelEnable(int lChannelNo, uint uUse);
    
    //������ �Է� ä���� �̺�Ʈ ��� ������ Ȯ���Ѵ�.
    //======================================================
    // *upUse      : DISABLE(0)    // �̺�Ʈ ����
    //             : ENABLE(1)     // �̺�Ʈ ����
    //======================================================
    [DllImport("AXL.dll")] public static extern uint AxaiEventGetChannelEnable(int lChannelNo, ref uint upUse);
    
    //������ ���� �Է� ä�ο� �̺�Ʈ ��� ������ �����Ѵ�.
    //======================================================
    // lSize       : ��� �� �Է� ä���� ����
    // lpChannelNo : ����� ä�� ��ȣ�� �迭
    // uUse        : DISABLE(0)    // �̺�Ʈ ����
    //             : ENABLE(1)     // �̺�Ʈ ����
    //======================================================
    [DllImport("AXL.dll")] public static extern uint AxaiEventSetMultiChannelEnable(int lSize, int[] lpChannelNo, uint uUse);
    
    //������ �Է� ä�ο� �̺�Ʈ ������ �����Ѵ�.
    //======================================================
    // uMask       : DATA_EMPTY(1) --> ���ۿ� �����Ͱ� ���� ��
    //             : DATA_MANY(2)  --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    //             : DATA_SMALL(3) --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    //             : DATA_FULL(4)  --> ���ۿ� �����Ͱ� �� á�� ��
    //======================================================
    [DllImport("AXL.dll")] public static extern uint AxaiEventSetChannelMask(int lChannelNo, uint uMask);
    
    //������ �Է� ä�ο� �̺�Ʈ ������ Ȯ���Ѵ�.
    //======================================================
    // *upMask     : DATA_EMPTY(1) --> ���ۿ� �����Ͱ� ���� ��
    //             : DATA_MANY(2)  --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    //             : DATA_SMALL(3) --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    //             : DATA_FULL(4)  --> ���ۿ� �����Ͱ� �� á�� ��
    //======================================================
    [DllImport("AXL.dll")] public static extern uint AxaiEventGetChannelMask(int lChannelNo, ref uint upMask);
    
    //������ ���� �Է� ä�ο� �̺�Ʈ ������ �����Ѵ�.
    //======================================================
    // lSize       : ��� �� �Է� ä���� ����
    // lpChannelNo : ����� ä�� ��ȣ�� �迭
    // uMask       : DATA_EMPTY(1) --> ���ۿ� �����Ͱ� ���� ��
    //             : DATA_MANY(2)  --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    //             : DATA_SMALL(3) --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    //             : DATA_FULL(4)  --> ���ۿ� �����Ͱ� �� á�� ��
    //======================================================
    [DllImport("AXL.dll")] public static extern uint AxaiEventSetMultiChannelMask(int lSize, int[] lpChannelNo, uint uMask);
    
    //�̺�Ʈ �߻� ��ġ�� Ȯ���Ѵ�.
    //======================================================
    // *upMode     : AIO_EVENT_DATA_UPPER(1) --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    //             : AIO_EVENT_DATA_LOWER(2) --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    //             : AIO_EVENT_DATA_FULL(3)  --> ���ۿ� �����Ͱ� �� á�� ��
    //             : AIO_EVENT_DATA_EMPTY(4) --> ���ۿ� �����Ͱ� ���� ��
    //======================================================
    [DllImport("AXL.dll")] public static extern uint AxaiEventRead(ref int lpChannelNo, ref uint upMode);
    
    //������ ����� ���ͷ�Ʈ ����ũ�� �����Ѵ�. �� �Լ��� ������ ��ȣ���ø� �� ��쿡 �ϵ����(���)�� FIFO ���� ����ڰ� 
    //������ ũ���� ���۷� ���� ���ͷ�Ʈ�� ���� ������ �̵� ������ �����ϱ� ���� ���ȴ�. (SIO-AI4RB�� �������� �ʴ´�.)
    //==================================================================================================//
    // uMask       : SCAN_END(1)       --> ���õ� ä�� ���  ADC ��ȯ�� �ѹ� �̷�� �� �� ���� ���ͷ�Ʈ�� �߻�
    //             : FIFO_HALF_FULL(2) --> ��⳻�� FIFO�� HALF�̻� á�� ��� ���� ���ͷ�Ʈ �߻�
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaiInterruptSetModuleMask(int lModuleNo, uint uMask);
    
    //������ ����� ���ͷ�Ʈ ����ũ�� Ȯ���Ѵ�.
    //==================================================================================================//
    // *upMask     : SCAN_END(1)       --> ���õ� ä�� ���  ADC ��ȯ�� �ѹ� �̷�� �� �� ���� ���ͷ�Ʈ�� �߻�
    //             : FIFO_HALF_FULL(2) --> ��⳻�� FIFO�� HALF�̻� á�� ��� ���� ���ͷ�Ʈ �߻�
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaiInterruptGetModuleMask(int lModuleNo, ref uint upMask);
    
//========== �Է� ��� �Ķ���� ���� �� Ȯ�� �Լ� ========================================================================
    //������ �Է� ä�ο� �Է� ���� ������ �����Ѵ�.
    //==================================================================================================//
    // AI4RB
    // dMinVolt    : -10V/-5V�� ���� ����
    // dMaxVolt    : 10V/5V/�� ���� ����
    //
    // AI16Hx
    // dMinVolt    : -10V ����
    // dMaxVolt    : 10V ����
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaiSetRange(int lChannelNo, double dMinVolt, double dMaxVolt);
    
    //������ �Է� ä���� �Է� ���� ������ Ȯ���Ѵ�.
    //==================================================================================================//
    // AI4RB
    // *dpMinVolt  : -10V/-5V�� ���� ����
    // *dpMaxVolt  : 10V/5V/�� ���� ����
    //
    // AI16Hx
    // *dpMaxVolt  : -10V ����
    // *dpMaxVolt  : 10V ����
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaiGetRange(int lChannelNo, ref double dpMinVolt, ref double dpMaxVolt);

    //������ ���� �Է� ��⿡ ��� �Է� ���� ������ �����Ѵ�.
    //==================================================================================================//
    // lModuleNo   : ����� �Է� ��� ��ȣ
    //
    // RTEX AI16F
    // Mode -5~+5  : dMinVolt = -5, dMaxVolt = +5
    // Mode -10~+10: dMinVolt = -10, dMaxVolt = +10
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaiSetRangeModule(int lModuleNo, double dMinVolt, double dMaxVolt);

    //������ ���� �Է� ��⿡ ��� �Է� ���� ������ Ȯ���Ѵ�.
    //==================================================================================================//
    // lModuleNo   : ����� �Է� ��� ��ȣ
    //
    // RTEX AI16F
    // *dMinVolt   : -5V, -10V
    // *dMaxVolt   : +5V, +10V
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaiGetRangeModule(int lModuleNo, ref double dMinVolt, ref double dMaxVolt);
    
    //������ ���� �Է� ä�ο� ��� �Է� ���� ������ �����Ѵ�.
    //==================================================================================================//
    // lSize        : ����� �Է� ä���� ����
    // *lpChannelNo : ����� ä�� ��ȣ�� �迭
    //
    // AI4RB
    // dMinVolt    : -10V/-5V�� ���� ����
    // dMaxVolt    : 10V/5V/�� ���� ����
    //
    // AI16Hx
    // dMinVolt    : -10V
    // dMaxVolt    : 10V
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaiSetMultiRange(int lSize, int[] lpChannelNo, double dMinVolt, double dMaxVolt);
    
    //������ �Է� ��⿡ Ʈ���� ��带 �����Ѵ�.
    //==================================================================================================//
    // uTriggerMode : NORMAL_MODE(1)   --> ����ڰ� ���ϴ� ������ A/D��ȯ�ϴ� Software Trigger ��� 
    //              : TIMER_MODE(2)    --> H/W�� ���� Ŭ���� �̿��ؼ� A/D��ȯ�ϴ� Trigger ���
    //              : EXTERNAL_MODE(3) --> �ܺ� �Է´����� Ŭ���� �̿��ؼ� A/D��ȯ�ϴ� Trigger ���
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaiSetTriggerMode(int lModuleNo, uint uTriggerMode);
    
    //������ ��⿡ Ʈ���� ��带 Ȯ���Ѵ�.
    //==================================================================================================//
    // *upTriggerMode : NORMAL_MODE(1)   --> ����ڰ� ���ϴ� ������ A/D��ȯ�ϴ� Software Trigger ��� 
    //                : TIMER_MODE(2)    --> H/W�� ���� Ŭ���� �̿��ؼ� A/D��ȯ�ϴ� Trigger ���
    //                : EXTERNAL_MODE(3) --> �ܺ� �Է´����� Ŭ���� �̿��ؼ� A/D��ȯ�ϴ� Trigger ���
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaiGetTriggerMode(int lModuleNo, ref uint upTriggerMode);
    
    //������ �Է¸���� Offset�� mVolt ����(mV)�� �����Ѵ�. �ִ� -100~100mVolt
    //==================================================================================================//
    // dMiliVolt    : -100 ~ 100 
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaiSetModuleOffsetValue(int lModuleNo, double dMiliVolt);
    
    //������ �Է¸���� Offset ���� Ȯ���Ѵ�. mVolt ����(mV)
    //==================================================================================================//
    // *dpMiliVolt  : -100 ~ 100 
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaiGetModuleOffsetValue(int lModuleNo, ref double dpMiliVolt); 

    //========== �Է� ��� A/D ��ȯ �Լ�
    //==Software Trigger Mode �Լ�
    //����ڰ� ������ �Է� ä�ο� �Ƴ��α� �Է� ���� A/D��ȯ�� �� ���� ������ ��ȯ�Ѵ�.�� �Լ��� ����ϱ� ���� AxaSetTriggerModeAdc �Լ��� ����Ͽ� Normal Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaiSwReadVoltage(int lChannelNo, ref double dpVolt);
    
    //������ �Է� ä�ο� �Ƴ��α� �Է� ���� Digit ������ ��ȯ�Ѵ�. Normal Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaiSwReadDigit(int lChannelNo, ref uint upDigit);
    
    //������ ���� �Է� ä�ο� �Ƴ��α� �Է� ���� ���� ������ ��ȯ�Ѵ�. Normal Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaiSwReadMultiVoltage(int lSize, int[] lpChannelNo, double[] dpVolt);
    
    //������ ���� �Է� ä�ο� �Ƴ��α� �Է� ���� Digit ������ ��ȯ�Ѵ�. Normal Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaiSwReadMultiDigit(int lSize, int[] lpChannelNo, uint[] upDigit);
    
    //������ ���� �Է� ä�ο� Immediate��带 ����ϱ� ���� ���� ���� �����Ѵ�. �� �Լ��� ����ϱ� ���� AxaSetTriggerModeAdc �Լ��� ����Ͽ� Timer Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaiHwSetMultiAccess(int lSize, int[] lpChannelNo, int[] lpWordSize);
    
    //������ ������ŭ A/D��ȯ �� ���� ���� ��ȯ�Ѵ�. �� �Լ��� ����ϱ� ���� AxaiHwSetMultiAccess�Լ��� �̿� �������� �����ؾ� �ϸ� , AxaSetTriggerModeAdc �Լ��� ����Ͽ� Timer Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
    // [DllImport("AXL.dll")] public static extern uint AxaiHwStartMultiAccess(ref double[] dpBuffer);
    [DllImport("AXL.dll")] public static extern uint AxaiHwStartMultiAccess(double[,] dpBuffer);
    
    //������ ��⿡ ���ø� ������ ���ļ� ������ �����Ѵ�.
    //==================================================================================================//
    // dSampleFreq    : 10 ~ 100000 
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaiHwSetSampleFreq(int lModuleNo, double dSampleFreq);
    
    //������ ��⿡ ���ø� ������ ���ļ� ������ ������ ���� Ȯ���Ѵ�.
    //==================================================================================================//
    // *dpSampleFreq  : 10 ~ 100000 
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaiHwGetSampleFreq(int lModuleNo, ref double dpSampleFreq);
    
    //������ ��⿡ ���ø� ������ �ð� ����(uSec)�� �����Ѵ�.
    //==================================================================================================//
    // dSamplePeriod  : 100000 ~ 1000000000
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaiHwSetSamplePeriod(int lModuleNo, double dSamplePeriod);
    
    //������ ��⿡ ���ø� ������ �ð� ����(uSec)�� ������ ���� Ȯ���Ѵ�.
    //==================================================================================================//
    // *dpSamplePeriod: 100000 ~ 1000000000
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaiHwGetSamplePeriod(int lModuleNo, ref double dpSamplePeriod);
    
    //������ �Է� ä�ο� ���۰� Full�� á�� �� ���� ����� �����Ѵ�.
    //==================================================================================================//
    // uFullMode      : NEW_DATA_KEEP(0) --> ���ο� ������ ����
    //                : CURR_DATA_KEEP(1) --> ���� ������ ����
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaiHwSetBufferOverflowMode(int lChannelNo, uint uFullMode);
    
    //������ �Է� ä���� ���۰� Full�� á�� �� ���� ����� Ȯ���Ѵ�.
    //==================================================================================================//
    // *upFullMode    : NEW_DATA_KEEP(0) --> ���ο� ������ ����
    //                : CURR_DATA_KEEP(1) --> ���� ������ ����
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaiHwGetBufferOverflowMode(int lChannelNo, ref uint upFullMode);
    
    //������ ���� �Է� ä�ο� ���۰� Full�� á�� �� ���� ����� �����Ѵ�.
    //==================================================================================================//
    // uFullMode      : NEW_DATA_KEEP(0) --> ���ο� ������ ����
    //                : CURR_DATA_KEEP(1) --> ���� ������ ����
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaiHwSetMultiBufferOverflowMode(int lSize, int[] lpChannelNo, uint uFullMode);
    
    //������ �Է� ä�ο� ������ ���� ���� ���� ���� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaiHwSetLimit(int lChannelNo, int lLowLimit, int lUpLimit);
    
    //������ �Է� ä�ο� ������ ���� ���� ���� ���� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaiHwGetLimit(int lChannelNo, ref int lpLowLimit, ref int lpUpLimit);
    
    //������ ���� �Է� ä�ο� ������ ���� ���� ���� ���� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaiHwSetMultiLimit(int lSize, int[] lpChannelNo, int lLowLimit, int lUpLimit);
    
    //������ ���� �Է� ä�ο� H/WŸ�̸Ӹ� �̿��� A/D��ȯ�� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaiHwStartMultiChannel(int lSize, int[] lpChannelNo, int lBuffSize);
    
    //������ ���� �Է� ä�ο� A/D��ȯ�� ���� �� ������ ������ŭ ���� ó���ؼ� �������� ��ȯ�Ѵ�.
    //==================================================================================================//
    // lSize          : ����� �Է� ä���� ����
    // *lpChannelNo   : ����� ä�� ��ȣ�� �迭
    // lFilterCount   : Filtering�� �������� ����
    // lBuffSize      : �� ä�ο� �Ҵ�Ǵ� ������ ����
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaiHwStartMultiFilter(int lSize, int[] lpChannelNo, int lFilterCount, int lBuffSize);
    
    //H/WŸ�̸Ӹ� �̿��� ���� ��ȣ A/D��ȯ�� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaiHwStopMultiChannel(int lModuleNo);
    
    //������ �Է� ä���� �޸� ���ۿ� �����Ͱ� �� ������ �˻��Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaiHwReadDataLength(int lChannelNo, ref int lpDataLength);
    
    //������ �Է� ä�ο� H/WŸ�̸Ӹ� �̿��Ͽ� A/D��ȯ�� ���� ���� ������ �д´�.
    [DllImport("AXL.dll")] public static extern uint AxaiHwReadSampleVoltage(int lChannelNo, ref int lpSize, ref double dpVolt);
    
    //������ �Է� ä�ο� H/WŸ�̸Ӹ� �̿��Ͽ� A/D��ȯ�� ���� Digit ������ �д´�.
    [DllImport("AXL.dll")] public static extern uint AxaiHwReadSampleDigit(int lChannelNo, ref int lpSize, ref uint upDigit);

//========== �Է� ��� ���� ���� üũ �Լ� ===============================================================================
    //������ �Է� ä���� �޸� ���ۿ� �����Ͱ� ���� �� �˻��Ѵ�.
    //==================================================================================================//
    // *upEmpty       : FALSE(0) --> �޸� ���ۿ� �����Ͱ� ���� ���
    //                : TRUE(1)  --> �޸� ���ۿ� �����Ͱ� ���� ���
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaiHwIsBufferEmpty(int lChannelNo, ref uint upEmpty);
    
    //������ �Է� ä���� �޸� ���ۿ� �����Ǿ� �ִ� ���� ������ �����Ͱ� ���� �� �˻��Ѵ�
    //==================================================================================================//
    // *upUpper       : FALSE(0) --> �޸� ���ۿ� �����Ͱ� ���� ������ ���� ���
    //                : TRUE(1)  --> �޸� ���ۿ� �����Ͱ� ���� ������ ���� ���
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaiHwIsBufferUpper(int lChannelNo, ref uint upUpper);
    
    //������ �Է� ä���� �޸� ���ۿ� �����Ǿ� �ִ� ���� ������ �����Ͱ� ���� �� �˻��Ѵ�.
    //==================================================================================================//
    // *upLower       : FALSE(0) --> �޸� ���ۿ� �����Ͱ� ���� ������ ���� ���
    //                : TRUE(1)  --> �޸� ���ۿ� �����Ͱ� ���� ������ ���� ���
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaiHwIsBufferLower(int lChannelNo, ref uint upLower);

//==External Trigger Mode �Լ�
    //������ �Է¸���� ���õ� ä�ε��� �ܺ� Ʈ���� ��带 �����Ѵ�.
    //==================================================================================================//
    // lSize          : ������ �Է� ��⿡�� �ܺ�Ʈ���Ÿ� ��� �� ä�ΰ���
    // *lpChannelPos  : ������ �Է� ��⿡�� �ܺ�Ʈ���Ÿ� ��� �� ä���� Index
    [DllImport("AXL.dll")] public static extern uint AxaiExternalStartADC(int lModuleNo, int lSize, ref int lpChannelPos);

    //������ �Է¸���� �ܺ�Ʈ���� ��带 �����Ѵ�.  
    [DllImport("AXL.dll")] public static extern uint AxaiExternalStopADC(int lModuleNo);

    //������ �Է¸���� Fifo���¸� ��ȯ�Ѵ�.
    //==================================================================================================//
    // *dwpStatus     : FIFO_DATA_EXIST(0)
    //                : FIFO_DATA_EMPTY(1)
    //                : FIFO_DATA_HALF(2)
    //                : FIFO_DATA_FULL(6)
    //==================================================================================================//    
    [DllImport("AXL.dll")] public static extern uint AxaiExternalReadFifoStatus(int lModuleNo, ref uint upStatus);

    //������ �Է¸���� �ܺν�ȣ�� ���� ��ȯ�� A/D���� �о��.
    // lSize          : ������ �Է� ��⿡�� ��ȯ�� A/D���� �о�� ä���� ����(AxaiExternalStartADC�� ����� ä�ΰ����� ���� �ؾߵ�)
    // *lpChannelPos  : ������ �Է� ��⿡�� ��ȯ�� A/D���� �о�� ä���� Index(AxaiExternalStartADC�� ����� ä���� Index�� ���� �ؾߵ�)
    // lDataSize      : �ܺ�Ʈ���ſ� ���� A/D��ȯ�� ���� �ѹ��� �о� �� �ִ� ����Ÿ�� ����
    // lBuffSize      : �ܺο���(����� Program) �Ҵ��� Data Buffer�� Size
    // lStartDataPos  : �ܺο���(����� Program) �Ҵ��� Data Buffer�� ���� ���� �� ��ġ 
    // *dpVolt[]      : A/D��ȯ�� ���� �Ҵ� ���� 2���� �迭 ����Ʈ(dpVlot[Channel][Count])
    // *lpRetDataSize : A/D��ȯ�� ���� Data Buffer�� ���� �Ҵ�� ����
    // *dwpStatus     : A/D��ȯ�� ���� Fifo(H/W Buffer)�� ���� ���� �� Fifo���¸� ��ȯ��.
    [DllImport("AXL.dll")] public static extern uint AxaiExternalReadVoltage(int lModuleNo, int lSize, ref int lpChannelPos, int lDataSize, int lBuffSize, int lStartDataPos, double[,] dpVolt, ref int lpRetDataSize, ref uint upStatus);
	
//========== ��� ��� ���� �˻� �Լ� ====================================================================================
    //������ ��� ä�� ��ȣ�� ��� ��ȣ�� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaoInfoGetModuleNoOfChannelNo(int lChannelNo, ref int lpModuleNo);
    
    //�Ƴ��α� ��� ����� ��ü ä�� ������ Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaoInfoGetChannelCount(ref int lpChannelCount);

//========== ��� ��� ���� �� Ȯ�� �Լ� =================================================================================
    //������ ��� ä�ο� ��� ���� ������ �����Ѵ�
    //==================================================================================================//
    // AXT_SIO_RAO4RB
    // dMinVolt    : -10V
    // dMaxVolt    : 10V
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaoSetRange(int lChannelNo, double dMinVolt, double dMaxVolt);
    
    //������ ��� ä���� ��� ���� ������ Ȯ���Ѵ�.
    //==================================================================================================//
    // AXT_SIO_RAO4RB
    // *dpMinVolt    : -10V
    // *dpMaxVolt    : 10V
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaoGetRange(int lChannelNo, ref double dpMinVolt, ref double dpMaxVolt);
    
    //������ ���� ��� ä�ο� ��� ���� ������ �����Ѵ�.
    //==================================================================================================//
    // AO4R, AO2Hx
    // dMinVolt    : -10V
    // dMaxVolt    : 10V
    //==================================================================================================//
    [DllImport("AXL.dll")] public static extern uint AxaoSetMultiRange(int lSize, int[] lpChannelNo, double dMinVolt, double dMaxVolt);
    
    //������ ��� ä�ο� �Էµ� ������ ��� �ȴ�.
    [DllImport("AXL.dll")] public static extern uint AxaoWriteVoltage(int lChannelNo, double dVolt);
    
    //������ ���� ��� ä�ο� �Էµ� ������ ��� �ȴ�.
    [DllImport("AXL.dll")] public static extern uint AxaoWriteMultiVoltage(int lSize, int[] lpChannelNo, double[] dpVolt);
    
    //������ ��� ä�ο� ��µǴ� ���� ���� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaoReadVoltage(int lChannelNo, ref double dpVolt);
    
    //������ ���� ��� ä�ο� ��µǴ� ���� ���� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxaoReadMultiVoltage(int lSize, int[] lpChannelNo, double[] dpVolt);
}

