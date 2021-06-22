//****************************************************************************
//****************************************************************************
//**
//** File Name
//** ----------
//**
//** AXA.PAS
//**
//** COPYRIGHT (c) AJINEXTEK Co., LTD
//**
//*****************************************************************************
//*****************************************************************************
//**
//** Description
//** -----------
//** Ajinextek Analog Library Header File
//** 
//**
//*****************************************************************************
//*****************************************************************************
//**
//** Source Change Indices
//** ---------------------
//** 
//** (None)
//**
//**
//*****************************************************************************
//*****************************************************************************
//**
//** Website
//** ---------------------
//**
//** http://www.ajinextek.com
//**
//*****************************************************************************
//*****************************************************************************

unit AXA;

interface

uses Windows, Messages, AXHS;
//========== ���� �� ��� ���� Ȯ�� �Լ� =================================================================================
    //AIO ����� �ִ��� Ȯ���Ѵ�
function AxaInfoIsAIOModule (upStatus : PDWord) : DWord; stdcall;

    //��� No�� Ȯ���Ѵ�.
function AxaInfoGetModuleNo (lBoardNo: LongInt; lModulePos :  LongInt; lpModuleNo :  PLongInt) : DWord; stdcall;

    //AIO ����� ������ Ȯ���Ѵ�.
function AxaInfoGetModuleCount (lpModuleCount : PLongInt) : DWord; stdcall;

    //������ ����� �Է� ä�� ���� Ȯ���Ѵ�
function AxaInfoGetInputCount (lModuleNo : LongInt; lpCount : PLongInt) : DWord; stdcall;

    //������ ����� ��� ä�� ���� Ȯ���Ѵ�.
function AxaInfoGetOutputCount (lModuleNo : LongInt; lpCount : PLongInt) : DWord; stdcall;

    //������ ����� ù ��° ä�� ��ȣ�� Ȯ���Ѵ�. 
function AxaInfoGetChannelNoOfModuleNo (lModuleNo : LongInt; lpChannelNo : PLongInt) : DWord; stdcall;

    //������ ����� ù ��° �Է� ä�� ��ȣ�� Ȯ���Ѵ�.(�Է� ���, �Է�/��� ���� ����)
function AxaInfoGetChannelNoAdcOfModuleNo (lModuleNo : LongInt; lpChannelNo : PLongInt) : DWord; stdcall;

    //������ ����� ù ��° ��� ä�� ��ȣ�� Ȯ���Ѵ�.(��� ���, �Է�/��� ���� ����)
function AxaInfoGetChannelNoDacOfModuleNo (lModuleNo : LongInt; lpChannelNo : PLongInt) : DWord; stdcall;

    //������ ��� ��ȣ�� ���̽� ���� ��ȣ, ��� ��ġ, ��� ID�� Ȯ���Ѵ�.
function AxaInfoGetModule (lModuleNo : LongInt; lpBoardNo : PLongInt; lpModulePos : PLongInt; upModuleID : PDWord) : DWord; stdcall;

    // �ش� ����� ��� ������ �������� ��ȯ�Ѵ�.
function AxaInfoGetModuleStatus(lModuleNo : LongInt) : DWord; stdcall;

//========== �Է� ��� ���� �˻� �Լ� ====================================================================================
    //������ �Է� ä�� ��ȣ�� ��� ��ȣ�� Ȯ���Ѵ�.
function AxaiInfoGetModuleNoOfChannelNo (lChannelNo : LongInt; lpModuleNo : PLongInt) : DWord; stdcall;

    //�Ƴ��α� �Է� ����� ��ü ä�� ������ Ȯ���Ѵ�.
function AxaiInfoGetChannelCount (lpChannelCount : PLongInt) : DWord; stdcall;

//========== �Է� ��� ���ͷ�Ʈ/ä�� �̺�Ʈ ���� �� Ȯ�� �Լ� ============================================================
    //������ ä�ο� �̺�Ʈ �޽����� �޾ƿ��� ���Ͽ� ������ �޽���, �ݹ� �Լ� �Ǵ� �̺�Ʈ ����� ����Ѵ�. H/W Ÿ�̸�(Timer Trigger Mode, External Trigger Mode)�� �̿�, ������ ������ ���� ���۽�(AxaiHwStartMultiChannel ����)�� ����Ѵ�.
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
    //    hWnd    : ������ �ڵ�, ������ �޼����� ������ ���. ������� ������ NULL�� �Է�.
    //    uMessage: ������ �ڵ��� �޼���, ������� �ʰų� ����Ʈ���� ����Ϸ��� 0�� �Է�.
    //    proc    : ���ͷ�Ʈ �߻��� ȣ��� �Լ��� ������, ������� ������ NULL�� �Է�.
    //    pEvent  : �̺�Ʈ ������� �̺�Ʈ �ڵ�
function AxaiEventSetChannel (lChannelNo : LongInt; hWnd : HWND; uMesssage : DWord; pProc : AXT_EVENT_PROC; pEvent : PDWord) : DWord; stdcall;

    //������ �Է� ä�ο� �̺�Ʈ ��� ������ �����Ѵ�.
    //======================================================//
    // uUse       : DISABLE(0)    // �̺�Ʈ ����
    //            : ENABLE(1)     // �̺�Ʈ ����
    //======================================================//
function AxaiEventSetChannelEnable (lChannelNo : LongInt; uUse : DWord) : DWord; stdcall;

    //������ �Է� ä���� �̺�Ʈ ��� ������ Ȯ���Ѵ�.
    //======================================================//
    // *upUse     : DISABLE(0)    // �̺�Ʈ ����
    //            : ENABLE(1)     // �̺�Ʈ ����
    //======================================================//
function AxaiEventGetChannelEnable (lChannelNo : LongInt; upUse : PDWord) : DWord; stdcall;

    //������ ���� �Է� ä�ο� �̺�Ʈ ��� ������ �����Ѵ�.
    //======================================================//
    // lSize      : ��� �� �Է� ä���� ����
    // lpChannelNo: ����� ä�� ��ȣ�� �迭
    // uUse       : DISABLE(0)    // �̺�Ʈ ����
    //            : ENABLE(1)     // �̺�Ʈ ����
    //======================================================//
function AxaiEventSetMultiChannelEnable (lSize : LongInt; lpChannelNo : PLongInt; uUse : DWord) : DWord; stdcall;

    //������ �Է� ä�ο� �̺�Ʈ ������ �����Ѵ�.
    //======================================================//
    // uMask      : DATA_EMPTY(1) --> ���ۿ� �����Ͱ� ���� ��
    //            : DATA_MANY(2)  --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    //            : DATA_SMALL(3) --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    //            : DATA_FULL(4)  --> ���ۿ� �����Ͱ� �� á�� ��
    //======================================================//
function AxaiEventSetChannelMask (lChannelNo : LongInt; uMask : DWord) : DWord; stdcall;

    //������ �Է� ä�ο� �̺�Ʈ ������ Ȯ���Ѵ�.
    //======================================================//
    // *upMask    : DATA_EMPTY(1) --> ���ۿ� �����Ͱ� ���� ��
    //            : DATA_MANY(2)  --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    //            : DATA_SMALL(3) --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    //            : DATA_FULL(4)  --> ���ۿ� �����Ͱ� �� á�� ��
    //======================================================//
function AxaiEventGetChannelMask (lChannelNo : LongInt; upMask : PDWord) : DWord; stdcall;

    //������ ���� �Է� ä�ο� �̺�Ʈ ������ �����Ѵ�.
    //==============================================================================//
    // lSize      : ��� �� �Է� ä���� ����
    // lpChannelNo: ����� ä�� ��ȣ�� �迭
    // uMask      : DATA_EMPTY(1) --> ���ۿ� �����Ͱ� ���� ��
    //            : DATA_MANY(2)  --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    //            : DATA_SMALL(3) --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    //            : DATA_FULL(4)  --> ���ۿ� �����Ͱ� �� á�� ��
    //==============================================================================//
function AxaiEventSetMultiChannelMask (lSize : LongInt; lpChannelNo : PLongInt; uMask : DWord) : DWord; stdcall;

    //�̺�Ʈ �߻� ��ġ�� Ȯ���Ѵ�.
    //==============================================================================//
    // *upMode    : AIO_EVENT_DATA_UPPER(1) --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    //            : AIO_EVENT_DATA_LOWER(2) --> ���ۿ� �����Ͱ� ���� ���� ������ ������ ��
    //            : AIO_EVENT_DATA_FULL(3)  --> ���ۿ� �����Ͱ� �� á�� ��
    //            : AIO_EVENT_DATA_EMPTY(4) --> ���ۿ� �����Ͱ� ���� ��
    //==============================================================================//
function AxaiEventRead (lpChannelNo : PLongInt; upMode : PDWord) : DWord; stdcall;

    //������ ����� ���ͷ�Ʈ ����ũ�� �����Ѵ�. �� �Լ��� ������ ��ȣ���ø� �� ��쿡 �ϵ����(���)�� FIFO ���� ����ڰ� ������ ũ���� ���۷� ���� ���ͷ�Ʈ�� ���� ������ �̵� ������ �����ϱ� ���� ���ȴ�. (SIO-AI4RB�� �������� �ʴ´�.)
    //==================================================================================================//
    // uMask       : SCAN_END(1)       --> ���õ� ä�� ���  ADC ��ȯ�� �ѹ� �̷�� �� �� ���� ���ͷ�Ʈ�� �߻�
    //             : FIFO_HALF_FULL(2) --> ��⳻�� FIFO�� HALF�̻� á�� ��� ���� ���ͷ�Ʈ �߻�
    //==================================================================================================//
function AxaiInterruptSetModuleMask(lpChannelNo : PLongInt; uMask : Dword) : DWord; stdcall;
    
    //������ ����� ���ͷ�Ʈ ����ũ�� Ȯ���Ѵ�.
    //==================================================================================================//
    // *upMask     : SCAN_END(1)       --> ���õ� ä�� ���  ADC ��ȯ�� �ѹ� �̷�� �� �� ���� ���ͷ�Ʈ�� �߻�
    //             : FIFO_HALF_FULL(2) --> ��⳻�� FIFO�� HALF�̻� á�� ��� ���� ���ͷ�Ʈ �߻�
    //==================================================================================================//
function  AxaiInterruptGetModuleMask(lpChannelNo : PLongInt; upMask : PDWord) : DWord; stdcall;

    //������ ����� ���ͷ�Ʈ ����ũ�� �����Ѵ�. �� �Լ��� ������ ��ȣ���ø� �� ��쿡 �ϵ����(���)�� FIFO ���� ����ڰ� ������ ũ���� ���۷� ���� ���ͷ�Ʈ�� ���� ������ �̵� ������ �����ϱ� ���� ���ȴ�. (SIO-AI4RB�� �������� �ʴ´�.)
    //==================================================================================================//
    // uMask      : SCAN_END(1)       --> ���õ� ä�� ���  ADC ��ȯ�� �ѹ� �̷�� �� �� ���� ���ͷ�Ʈ�� �߻�
    //            : FIFO_HALF_FULL(2) --> ��⳻�� FIFO�� HALF�̻� á�� ��� ���� ���ͷ�Ʈ �߻�
    //==================================================================================================//
function AxaSetMoudleInterruptMaskAdc (lModuleNo : LongInt; uMask : DWord) : DWord; stdcall;

    //������ ����� ���ͷ�Ʈ ����ũ�� Ȯ���Ѵ�.
    //==================================================================================================//
    // *upMask    : SCAN_END(1)       --> ���õ� ä�� ���  ADC ��ȯ�� �ѹ� �̷�� �� �� ���� ���ͷ�Ʈ�� �߻�
    //            : FIFO_HALF_FULL(2) --> ��⳻�� FIFO�� HALF�̻� á�� ��� ���� ���ͷ�Ʈ �߻�
    //==================================================================================================//
function AxaGetMoudleInterruptMaskAdc (lModuleNo : LongInt; upMask : PDWord) : DWord; stdcall;

//========== �Է� ��� �Ķ���� ���� �� Ȯ�� �Լ� ======================================================
    //������ �Է� ä�ο� �Է� ���� ������ �����Ѵ�.
    //==================================================================================================//
    // AI4RB
    // dMinVolt    : -10V/-5V/0V�� ���� ����
    // dMaxVolt    : 10V/5V/�� ���� ����
    //
    // AI16Hx
    // dMinVolt    : -10V ����
    // dMaxVolt    : 10V ����
    //==================================================================================================//
function AxaiSetRange (lChannelNo : LongInt; dMinVolt : Double; dMaxVolt : Double) : DWord; stdcall;

    //������ �Է� ä���� �Է� ���� ������ Ȯ���Ѵ�.
    //==================================================================================================//
    // AI4RB
    // *dpMinVolt  : -10V/-5V/0V�� ���� ����
    // *dpMaxVolt  : 10V/5V/�� ���� ����
    //
    // AI16Hx
    // *dpMaxVolt  : -10V ����
    // *dpMaxVolt  : 10V ����
    //==================================================================================================//
function AxaiGetRange (lChannelNo : LongInt; dpMinVolt : PDouble; dpMaxVolt : PDouble) : DWord; stdcall;

    //������ ���� �Է� ��⿡ ��� �Է� ���� ������ �����Ѵ�.
    //==================================================================================================//
    // lModuleNo   : ����� �Է� ��� ��ȣ
    //
    // RTEX AI16F
    // Mode -5~+5  : dMinVolt = -5, dMaxVolt = +5
    // Mode -10~+10: dMinVolt = -10, dMaxVolt = +10
    //==================================================================================================//
function  AxaiSetRangeModule(lModuleNo : LongInt; dMinVolt : Double; dMaxVolt : Double) : DWord; stdcall;

    //������ ���� �Է� ��⿡ ��� �Է� ���� ������ Ȯ���Ѵ�.
    //==================================================================================================//
    // lModuleNo   : ����� �Է� ��� ��ȣ
    //
    // RTEX AI16F
    // *dMinVolt   : -5V, -10V
    // *dMaxVolt   : +5V, +10V
    //==================================================================================================//
function  AxaiGetRangeModule(lModuleNo : LongInt; dpMinVolt : PDouble; dpMaxVolt : PDouble) : DWord; stdcall;

    //������ ���� �Է� ä�ο� ��� �Է� ���� ������ �����Ѵ�.
    //==================================================================================================//
    // lSize       : ����� �Է� ä���� ����
    // *lpChannelNo: ����� ä�� ��ȣ�� �迭
    //
    // AI4RB
    // dMinVolt    : -10V/-5V/0V�� ���� ����
    // dMaxVolt    : 10V/5V/�� ���� ����
    //
    // AI16Hx
    // dMinVolt    : -10V
    // dMaxVolt    : 10V
    //==================================================================================================//
function AxaiSetMultiRange (lSize : LongInt; lpChannelNo : PLongInt; dMinVolt : Double; dMaxVolt : Double) : DWord; stdcall;

    //������ �Է� ��⿡ Ʈ���� ��带 �����Ѵ�.
    //==================================================================================================//
    // uTriggerMode: NORMAL_MODE(1)   --> ����ڰ� ���ϴ� ������ A/D��ȯ�ϴ� Software Trigger ��� 
    //             : TIMER_MODE(2)    --> H/W�� ���� Ŭ���� �̿��ؼ� A/D��ȯ�ϴ� Trigger ���
    //             : EXTERNAL_MODE(3) --> �ܺ� �Է´����� Ŭ���� �̿��ؼ� A/D��ȯ�ϴ� Trigger ���
    //==================================================================================================//
function AxaiSetTriggerMode (lModuleNo : LongInt; uTriggerMode : DWord) : DWord; stdcall;

    //������ ��⿡ Ʈ���� ��带 Ȯ���Ѵ�.
    //==================================================================================================//
    // *upTriggerMode : NORMAL_MODE(1) --> ����ڰ� ���ϴ� ������ A/D��ȯ�ϴ� Software Trigger ��� 
    //                : TIMER_MODE(2) --> H/W�� ���� Ŭ���� �̿��ؼ� A/D��ȯ�ϴ� Trigger ���
    //                : EXTERNAL_MODE(3) --> �ܺ� �Է´����� Ŭ���� �̿��ؼ� A/D��ȯ�ϴ� Trigger ���
    //==================================================================================================//
function AxaiGetTriggerMode (lModuleNo : LongInt; upTriggerMode : PDWord) : DWord; stdcall;

    //������ �Է¸���� Offset�� mVolt ����(mV)�� �����Ѵ�. �ִ� -100~100mVolt
    //==================================================================================================//
    // dMiliVolt      : -100 ~ 100 
    //==================================================================================================//
function AxaiSetModuleOffsetValue(lModuleNo : LongInt; dMiliVolt : Double) : DWord; stdcall;

    //������ �Է¸���� Offset ���� Ȯ���Ѵ�. mVolt ����(mV)
    //==================================================================================================//
    // *dpMiliVolt    : -100 ~ 100 
    //==================================================================================================//
function AxaiGetModuleOffsetValue(lModuleNo : LongInt; dpMiliVolt : PDouble) : DWord; stdcall;

//========== �Է� ��� A/D ��ȯ �Լ� ===================================================================
    //����ڰ� ������ �Է� ä�ο� �Ƴ��α� �Է� ���� A/D��ȯ�� �� ���� ������ ��ȯ�Ѵ�.�� �Լ��� ����ϱ� ���� AxaiSetTriggerMode �Լ��� ����Ͽ� Normal Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
function AxaiSwReadVoltage (lChannelNo : LongInt; dpVolt : PDouble) : DWord; stdcall;

    //������ �Է� ä�ο� �Ƴ��α� �Է� ���� Digit ������ ��ȯ�Ѵ�. Normal Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
function AxaiSwReadDigit (lChannelNo : LongInt; upDigit : PDWord) : DWord; stdcall;

    //������ ���� �Է� ä�ο� �Ƴ��α� �Է� ���� ���� ������ ��ȯ�Ѵ�. Normal Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
function AxaiSwReadMultiVoltage (lSize : LongInt; lpChannelNo : PLongInt; dpVolt : PDouble) : DWord; stdcall;

    //������ ���� �Է� ä�ο� �Ƴ��α� �Է� ���� Digit ������ ��ȯ�Ѵ�. Normal Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
function AxaiSwReadMultiDigit (lSize : LongInt; lpChannelNo : PLongInt; upDigit : PDWord) : DWord; stdcall;

    //������ ���� �Է� ä�ο� Immediate��带 ����ϱ� ���� ���� ���� �����Ѵ�. �� �Լ��� ����ϱ� ���� AxaiSetTriggerMode �Լ��� ����Ͽ� Timer Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
function AxaiHwSetMultiAccess (lSize : LongInt; lpChannelNo : PLongInt; lpWordSize : PLongInt) : DWord; stdcall;

    //������ ������ŭ A/D��ȯ �� ���� ���� ��ȯ�Ѵ�. �� �Լ��� ����ϱ� ���� AxaiHwSetMultiAccess�Լ��� �̿� �������� �����ؾ� �ϸ� , AxaSetTriggerModeAdc �Լ��� ����Ͽ� Timer Trigger Mode�� �����Ǿ� �־�� �Ѵ�.
function AxaiHwStartMultiAccess (dpBuffer : PDouble) : DWord; stdcall;

    //������ ��⿡ ���ø� ������ ���ļ�(Hz) ������ �����Ѵ�.
    //==================================================================================================//
    // dSampleFreq     : 10 ~ 100000 
    //==================================================================================================//
function AxaiHwSetSampleFreq (lModuleNo : LongInt; dSampleFreq : Double) : DWord; stdcall;

    //������ ��⿡ ���ø� ������ ���ļ�(Hz) ������ ������ ���� Ȯ���Ѵ�.
    //==================================================================================================//
    // *dpSampleFreq   : 10 ~ 100000 
    //==================================================================================================//
function AxaiHwGetSampleFreq (lModuleNo : LongInt; dpSampleFreq : PDouble) : DWord; stdcall;

    //������ ��⿡ ���ø� ������ �ð� ����(uSec)�� �����Ѵ�.
    //==================================================================================================//
    // dSamplePeriod   : 100000 ~ 1000000000
    //==================================================================================================//
function AxaiHwSetSamplePeriod (lModuleNo : LongInt; dSamplePeriod : Double) : DWord; stdcall;

    //������ ��⿡ ���ø� ������ �ð� ����(uSec)�� ������ ���� Ȯ���Ѵ�.
    //==================================================================================================//
    // *dpSamplePeriod : 100000 ~ 1000000000
    //==================================================================================================//
function AxaiHwGetSamplePeriod (lModuleNo : LongInt; dpSamplePeriod : PDouble) : DWord; stdcall;

    //������ �Է� ä�ο� ���۰� Full�� á�� �� ���� ����� �����Ѵ�.
    //==================================================================================================//
    // uFullMode       : NEW_DATA_KEEP(0)  --> ���ο� ������ ����
    //                 : CURR_DATA_KEEP(1) --> ���� ������ ����
    //==================================================================================================//
function AxaiHwSetBufferOverflowMode (lChannelNo : LongInt; uFullMode : DWord) : DWord; stdcall;

    //������ �Է� ä���� ���۰� Full�� á�� �� ���� ����� Ȯ���Ѵ�.
    //==================================================================================================//
    // *upFullMode     : NEW_DATA_KEEP(0)  --> ���ο� ������ ����
    //                 : CURR_DATA_KEEP(1) --> ���� ������ ����
    //==================================================================================================//
function AxaiHwGetBufferOverflowMode (lChannelNo : LongInt; upFullMode : PDWord) : DWord; stdcall;

    //������ ���� �Է� ä�ο� ���۰� Full�� á�� �� ���� ����� �����Ѵ�.
    //==================================================================================================//
    // uFullMode       : NEW_DATA_KEEP(0)  --> ���ο� ������ ����
    //                 : CURR_DATA_KEEP(1) --> ���� ������ ����
    //==================================================================================================//
function AxaiHwSetMultiBufferOverflowMode (lSize : LongInt; lpChannelNo : PLongInt; uFullMode : DWord) : DWord; stdcall;

    //������ �Է� ä�ο� ������ ���� ���� ���� ���� �����Ѵ�.
function AxaiHwSetLimit (lChannelNo : LongInt; lLowLimit : LongInt; lUpLimit : LongInt) : DWord; stdcall;

    //������ �Է� ä�ο� ������ ���� ���� ���� ���� Ȯ���Ѵ�.
function AxaiHwGetLimit (lChannelNo : LongInt; lpLowLimit : PLongInt; lpUpLimit : PLongInt) : DWord; stdcall;

    //������ ���� �Է� ä�ο� ������ ���� ���� ���� ���� �����Ѵ�.
function AxaiHwSetMultiLimit (lSize : LongInt; lpChannelNo : PLongInt; lLowLimit : LongInt; lUpLimit : LongInt) : DWord; stdcall;

    //������ ���� �Է� ä�ο� H/WŸ�̸Ӹ� �̿��� A/D��ȯ�� �����Ѵ�.
function AxaiHwStartMultiChannel (lSize : LongInt; lpChannelNo : PLongInt; lBuffSize : LongInt) : DWord; stdcall;

    //������ ���� �Է� ä�ο� A/D��ȯ�� ���� �� ������ ������ŭ ���� ó���ؼ� �������� ��ȯ�Ѵ�.
    //==================================================================================================//
    // lSize        : ����� �Է� ä���� ����
    // *lpChannelNo : ����� ä�� ��ȣ�� �迭
    // lFilterCount : Filtering�� �������� ����
    // lBuffSize    : �� ä�ο� �Ҵ�Ǵ� ������ ����
    //==================================================================================================//
function AxaiHwStartMultiFilter (lSize : LongInt; lpChannelNo : PLongInt; lFilterCount : LongInt; lBuffSize : LongInt) : DWord; stdcall;

    //H/WŸ�̸Ӹ� �̿��� ���� ��ȣ A/D��ȯ�� �����Ѵ�.
function AxaiHwStopMultiChannel (lModuleNo : LongInt) : DWord; stdcall;

    //������ �Է� ä���� �޸� ���ۿ� �����Ͱ� �� ������ �˻��Ѵ�.
function AxaiHwReadDataLength (lChannelNo : LongInt; lpDataLength : PLongInt) : DWord; stdcall;

    //������ �Է� ä�ο� H/WŸ�̸Ӹ� �̿��Ͽ� A/D��ȯ�� ���� ���� ������ �д´�.
function AxaiHwReadSampleVoltage (lChannelNo : LongInt; lSize : PLongInt; dpVolt : PDouble) : DWord; stdcall;

    //������ �Է� ä�ο� H/WŸ�̸Ӹ� �̿��Ͽ� A/D��ȯ�� ���� Digit ������ �д´�.
function AxaiHwReadSampleDigit (lChannelNo : LongInt; lSize : PLongInt; upDigit : PDWord) : DWord; stdcall;

//========== �Է� ��� ���� ���� üũ �Լ� ===================================================================================
    //������ �Է� ä���� �޸� ���ۿ� �����Ͱ� ���� �� �˻��Ѵ�.
    //==================================================================================================//
    // *upEmpty     : FALSE(0) --> �޸� ���ۿ� �����Ͱ� ���� ���
    //              : TRUE(1)  --> �޸� ���ۿ� �����Ͱ� ���� ���
    //==================================================================================================//
function AxaiHwIsBufferEmpty (lChannelNo : LongInt; upEmpty : PDWord) : DWord; stdcall;

    //������ �Է� ä���� �޸� ���ۿ� �����Ǿ� �ִ� ���� ������ �����Ͱ� ���� �� �˻��Ѵ�
    //==================================================================================================//
    // *upUpper     : FALSE(0) --> �޸� ���ۿ� �����Ͱ� ���� ������ ���� ���
    //              : TRUE(1)  --> �޸� ���ۿ� �����Ͱ� ���� ������ ���� ���
    //==================================================================================================//
function AxaiHwIsBufferUpper (lChannelNo : LongInt; upUpper : PDWord) : DWord; stdcall;

    //������ �Է� ä���� �޸� ���ۿ� �����Ǿ� �ִ� ���� ������ �����Ͱ� ���� �� �˻��Ѵ�.
    //==================================================================================================//
    // *upLower     : FALSE(0) --> �޸� ���ۿ� �����Ͱ� ���� ������ ���� ���
    //              : TRUE(1)  --> �޸� ���ۿ� �����Ͱ� ���� ������ ���� ���
    //==================================================================================================//
function AxaiHwIsBufferLower (lChannelNo : LongInt; upLower : PDWord) : DWord; stdcall;

//==External Trigger Mode �Լ�
    //������ �Է¸���� ���õ� ä�ε��� �ܺ� Ʈ���� ��带 �����Ѵ�.
    //==================================================================================================//
    // lSize            : ������ �Է� ��⿡�� �ܺ�Ʈ���Ÿ� ��� �� ä�ΰ���
    // *lpChannelPos    : ������ �Է� ��⿡�� �ܺ�Ʈ���Ÿ� ��� �� ä���� Index
function AxaiExternalStartADC(lModuleNo : LongInt; lSize : LongInt; lpChannelPos : PLongInt) : DWord; stdcall;
    //������ �Է¸���� �ܺ�Ʈ���� ��带 �����Ѵ�.  
function AxaiExternalStopADC(lModuleNo : LongInt) : DWord; stdcall;
    //������ �Է¸���� Fifo���¸� ��ȯ�Ѵ�.
    //==================================================================================================//
    // *dwpStatus       : FIFO_DATA_EXIST(0)
    //                  : FIFO_DATA_EMPTY(1)
    //                  : FIFO_DATA_HALF(2)
    //                  : FIFO_DATA_FULL(6)
    //==================================================================================================//
function AxaiExternalReadFifoStatus(lModuleNo : LongInt; dwpStatus : PDWord) : DWord; stdcall;
    //������ �Է¸���� �ܺν�ȣ�� ���� ��ȯ�� A/D���� �о��.
    // lSize            : ������ �Է� ��⿡�� ��ȯ�� A/D���� �о�� ä���� ����(AxaiExternalStartADC�� ����� ä�ΰ����� ���� �ؾߵ�)
    // *lpChannelPos    : ������ �Է� ��⿡�� ��ȯ�� A/D���� �о�� ä���� Index(AxaiExternalStartADC�� ����� ä���� Index�� ���� �ؾߵ�)
    // lDataSize        : �ܺ�Ʈ���ſ� ���� A/D��ȯ�� ���� �ѹ��� �о� �� �ִ� ����Ÿ�� ����
    // lBuffSize        : �ܺο���(����� Program) �Ҵ��� Data Buffer�� Size
    // lStartDataPos    : �ܺο���(����� Program) �Ҵ��� Data Buffer�� ���� ���� �� ��ġ 
    // *dpVolt[]        : A/D��ȯ�� ���� �Ҵ� ���� 2���� �迭 ����Ʈ(dpVlot[Channel][Count])
    // *lpRetDataSize   : A/D��ȯ�� ���� Data Buffer�� ���� �Ҵ�� ����
    // *dwpStatus       : A/D��ȯ�� ���� Fifo(H/W Buffer)�� ���� ���� �� Fifo���¸� ��ȯ��.
function AxaiExternalReadVoltage(lModuleNo : LongInt; lSize : LongInt; lpChannelPos : PLongInt; lDataSize : LongInt; lBuffSize : LongInt; lStartDataPos : LongInt; dpVolt : PDouble; lpRetDataSize : PLongInt; dwpStatus : PLongInt) : DWord; stdcall;

//========== ��� ��� ���� �˻� �Լ� ========================================================================================
    //������ ��� ä�� ��ȣ�� ��� ��ȣ�� Ȯ���Ѵ�.
function AxaoInfoGetModuleNoOfChannelNo (lChannelNo : LongInt; lpModuleNo : PLongInt) : DWord; stdcall;

    //�Ƴ��α� ��� ����� ��ü ä�� ������ Ȯ���Ѵ�.
function AxaoInfoGetChannelCount (lpChannelCount : PLongInt) : DWord; stdcall;

//========== ��� ��� ���� �� Ȯ�� �Լ� ========================================================================================
    //������ ��� ä�ο� ��� ���� ������ �����Ѵ�
    //==================================================================================================//
    // AO4R, AO2Hx
    // dMinVolt    : -10V
    // dMaxVolt    : 10V
    //==================================================================================================//
function AxaoSetRange (lChannelNo : LongInt; dMinVolt : Double; dMaxVolt : Double) : DWord; stdcall;

    //������ ��� ä���� ��� ���� ������ Ȯ���Ѵ�.
    //==================================================================================================//
    // AO4R, AO2Hx
    // *dpMinVolt  : -10V
    // *dpMaxVolt  : 10V
    //==================================================================================================//
function AxaoGetRange (lChannelNo : LongInt; dpMinVolt : PDouble; dpMaxVolt : PDouble) : DWord; stdcall;

    //������ ���� ��� ä�ο� ��� ���� ������ �����Ѵ�.
    //==================================================================================================//
    // AO4R, AO2Hx
    // dMinVolt    : -10V
    // dMaxVolt    : 10V
    //==================================================================================================//
function AxaoSetMultiRange (lSize : LongInt; lpChannelNo : PLongInt; dMinVolt : Double; dMaxVolt : Double) : DWord; stdcall;

    //������ ��� ä�ο� �Էµ� ������ ��� �ȴ�.
function AxaoWriteVoltage (lChannelNo : LongInt; dVolt : Double) : DWord; stdcall;

    //������ ���� ��� ä�ο� �Էµ� ������ ��� �ȴ�.
function AxaoWriteMultiVoltage (lSize : LongInt; lpChannelNo : PLongInt; dpVolt : PDouble) : DWord; stdcall;

    //������ ��� ä�ο� ��µǴ� ���� ���� Ȯ���Ѵ�.
function AxaoReadVoltage (lChannelNo : LongInt; dpVolt : PDouble) : DWord; stdcall;

    //������ ���� ��� ä�ο� ��µǴ� ���� ���� Ȯ���Ѵ�.
function AxaoReadMultiVoltage (lSize : LongInt; lpChannelNo : PLongInt; dpVolt : PDouble) : DWord; stdcall;

implementation

const

    dll_name    = 'AXL.dll';

    function AxaInfoIsAIOModule; external dll_name name 'AxaInfoIsAIOModule';
    function AxaInfoGetModuleNo; external dll_name name 'AxaInfoGetModuleNo';
    function AxaInfoGetModuleCount; external dll_name name 'AxaInfoGetModuleCount';
    function AxaInfoGetInputCount; external dll_name name 'AxaInfoGetInputCount';
    function AxaInfoGetOutputCount; external dll_name name 'AxaInfoGetOutputCount';
    function AxaInfoGetChannelNoOfModuleNo; external dll_name name 'AxaInfoGetChannelNoOfModuleNo';
    function AxaInfoGetChannelNoAdcOfModuleNo; external dll_name name 'AxaInfoGetChannelNoAdcOfModuleNo';
    function AxaInfoGetChannelNoDacOfModuleNo; external dll_name name 'AxaInfoGetChannelNoDacOfModuleNo';
    function AxaInfoGetModule; external dll_name name 'AxaInfoGetModule';
    function AxaInfoGetModuleStatus; external dll_name name 'AxaInfoGetModuleStatus';
    function AxaiInfoGetModuleNoOfChannelNo; external dll_name name 'AxaiInfoGetModuleNoOfChannelNo';
    function AxaiInfoGetChannelCount; external dll_name name 'AxaiInfoGetChannelCount';
    function AxaiEventSetChannel; external dll_name name 'AxaiEventSetChannel';
    function AxaiEventSetChannelEnable; external dll_name name 'AxaiEventSetChannelEnable';
    function AxaiEventGetChannelEnable; external dll_name name 'AxaiEventGetChannelEnable';
    function AxaiEventSetMultiChannelEnable; external dll_name name 'AxaiEventSetMultiChannelEnable';
    function AxaiEventSetChannelMask; external dll_name name 'AxaiEventSetChannelMask';
    function AxaiEventGetChannelMask; external dll_name name 'AxaiEventGetChannelMask';
    function AxaiEventSetMultiChannelMask; external dll_name name 'AxaiEventSetMultiChannelMask';
    function AxaiEventRead; external dll_name name 'AxaiEventRead';
    function AxaiInterruptSetModuleMask; external dll_name name 'AxaiInterruptSetModuleMask';
    function AxaiInterruptGetModuleMask; external dll_name name 'AxaiInterruptGetModuleMask';
    function AxaiSetRange; external dll_name name 'AxaiSetRange';
    function AxaiGetRange; external dll_name name 'AxaiGetRange';
    function AxaiSetRangeModule; external dll_name name 'AxaiSetRangeModule';
    function AxaiGetRangeModule; external dll_name name 'AxaiGetRangeModule';
    function AxaiSetMultiRange; external dll_name name 'AxaiSetMultiRange';
    function AxaiSetTriggerMode; external dll_name name 'AxaiSetTriggerMode';
    function AxaiGetTriggerMode; external dll_name name 'AxaiGetTriggerMode';
    function AxaiSwReadVoltage; external dll_name name 'AxaiSwReadVoltage';
    function AxaiSwReadDigit; external dll_name name 'AxaiSwReadDigit';
    function AxaiSwReadMultiVoltage; external dll_name name 'AxaiSwReadMultiVoltage';
    function AxaiSwReadMultiDigit; external dll_name name 'AxaiSwReadMultiDigit';
    function AxaiHwSetMultiAccess; external dll_name name 'AxaiHwSetMultiAccess';
    function AxaiHwStartMultiAccess; external dll_name name 'AxaiHwStartMultiAccess';
    function AxaiHwSetSampleFreq; external dll_name name 'AxaiHwSetSampleFreq';
    function AxaiHwGetSampleFreq; external dll_name name 'AxaiHwGetSampleFreq';
    function AxaiHwSetSamplePeriod; external dll_name name 'AxaiHwSetSamplePeriod';
    function AxaiHwGetSamplePeriod; external dll_name name 'AxaiHwGetSamplePeriod';
    function AxaiHwSetBufferOverflowMode; external dll_name name 'AxaiHwSetBufferOverflowMode';
    function AxaiHwGetBufferOverflowMode; external dll_name name 'AxaiHwGetBufferOverflowMode';
    function AxaiHwSetMultiBufferOverflowMode; external dll_name name 'AxaiHwSetMultiBufferOverflowMode';
    function AxaiHwSetLimit; external dll_name name 'AxaiHwSetLimit';
    function AxaiHwGetLimit; external dll_name name 'AxaiHwGetLimit';
    function AxaiHwSetMultiLimit; external dll_name name 'AxaiHwSetMultiLimit';
    function AxaiHwStartMultiChannel; external dll_name name 'AxaiHwStartMultiChannel';
    function AxaiHwStartMultiFilter; external dll_name name 'AxaiHwStartMultiFilter';
    function AxaiHwStopMultiChannel; external dll_name name 'AxaiHwStopMultiChannel';
    function AxaiHwReadDataLength; external dll_name name 'AxaiHwReadDataLength';
    function AxaiHwReadSampleVoltage; external dll_name name 'AxaiHwReadSampleVoltage';
    function AxaiHwReadSampleDigit; external dll_name name 'AxaiHwReadSampleDigit';
    function AxaiHwIsBufferEmpty; external dll_name name 'AxaiHwIsBufferEmpty';
    function AxaiHwIsBufferUpper; external dll_name name 'AxaiHwIsBufferUpper';
    function AxaiHwIsBufferLower; external dll_name name 'AxaiHwIsBufferLower';
    function AxaiExternalStartADC; external dll_name name 'AxaiExternalStartADC';
    function AxaiExternalStopADC; external dll_name name 'AxaiExternalStopADC';
    function AxaiExternalReadFifoStatus; external dll_name name 'AxaiExternalReadFifoStatus';
    function AxaiExternalReadVoltage; external dll_name name 'AxaiExternalReadVoltage';    
    function AxaoInfoGetModuleNoOfChannelNo; external dll_name name 'AxaoInfoGetModuleNoOfChannelNo';
    function AxaoInfoGetChannelCount; external dll_name name 'AxaoInfoGetChannelCount';
    function AxaoSetRange; external dll_name name 'AxaoSetRange';
    function AxaoGetRange; external dll_name name 'AxaoGetRange';
    function AxaoSetMultiRange; external dll_name name 'AxaoSetMultiRange';
    function AxaoWriteVoltage; external dll_name name 'AxaoWriteVoltage';
    function AxaoWriteMultiVoltage; external dll_name name 'AxaoWriteMultiVoltage';
    function AxaoReadVoltage; external dll_name name 'AxaoReadVoltage';
    function AxaoReadMultiVoltage; external dll_name name 'AxaoReadMultiVoltage';
    function AxaSetMoudleInterruptMaskAdc; external dll_name name 'AxaSetMoudleInterruptMaskAdc';
    function AxaGetMoudleInterruptMaskAdc; external dll_name name 'AxaGetMoudleInterruptMaskAdc';
    function AxaiSetModuleOffsetValue; external dll_name name 'AxaiSetModuleOffsetValue';
    function AxaiGetModuleOffsetValue; external dll_name name 'AxaiGetModuleOffsetValue';
end.
