//****************************************************************************
//****************************************************************************
//**
//** File Name
//** ----------
//**
//** AXC.H
//**
//** COPYRIGHT (c) AJINEXTEK Co., LTD
//**
//*****************************************************************************
//*****************************************************************************
//**
//** Description
//** -----------
//** Ajinextek Counter Library Header File
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

unit AXC;

interface

uses Windows, Messages, AXHS;

//========== ���� �� ��� ���� 
    // CNT ����� �ִ��� Ȯ��
function AxcInfoIsCNTModule(upStatus : PDWord) : DWord; stdcall;
    
    // CNT ��� No Ȯ��
function AxcInfoGetModuleNo(lBoardNo : LongInt; lModulePos : LongInt; lpModuleNo : PLongInt) : DWord; stdcall;
    
    // CNT ����� ����� ���� Ȯ��
function AxcInfoGetModuleCount(lpModuleCount : PLongInt) : DWord; stdcall;

    // ������ ����� ī���� �Է� ä�� ���� Ȯ��
function AxcInfoGetChannelCount(lModuleNo : LongInt; lpCount : PLongInt) : DWord; stdcall;
    
    // �ý��ۿ� ������ ī������ �� ä�� ���� Ȯ��
function AxcInfoGetTotalChannelCount(lpChannelCount : PLongInt) : DWord; stdcall;    

    // ������ ��� ��ȣ�� ���̽� ���� ��ȣ, ��� ��ġ, ��� ID Ȯ��
function AxcInfoGetModule(lModuleNo : LongInt; lpBoardNo : PLongInt; lpModulePos : PLongInt; upModuleID : PDWord) : DWord; stdcall;

    // �ش� ����� ��� ������ �������� ��ȯ�Ѵ�.
function AxcInfoGetModuleStatus(lModuleNo : LongInt) : DWord; stdcall;

function AxcInfoGetFirstChannelNoOfModuleNo(lModuleNo : LongInt; lpChannelNo : PLongInt) : DWord; stdcall;

    // ī���� ����� Encoder �Է� ����� ���� �մϴ�.
    // dwMethod --> 0x00 : Sign and pulse, x1 multiplication
    // dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
    // dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
    // dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
    // dwMethod --> 0x08 : Sign and pulse, x2 multiplication
    // dwMethod --> 0x09 : Increment and decrement pulses, x1 multiplication
    // dwMethod --> 0x0A : Increment and decrement pulses, x2 multiplication
    // SIO-CN2CH/HPC4�� ���
    // dwMethod --> 0x00 : Up/Down ���, A phase : �޽�, B phase : ����
    // dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
    // dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
    // dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
function AxcSignalSetEncInputMethod(lChannelNo : LongInt; dwMethod : DWord) : DWord; stdcall;

    // ī���� ����� Encoder �Է� ����� ��ȯ �մϴ�.
    // *dwpUpMethod --> 0x00 : Sign and pulse, x1 multiplication
    // *dwpUpMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
    // *dwpUpMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
    // *dwpUpMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
    // *dwpUpMethod --> 0x08 : Sign and pulse, x2 multiplication
    // *dwpUpMethod --> 0x09 : Increment and decrement pulses, x1 multiplication
    // *dwpUpMethod --> 0x0A : Increment and decrement pulses, x2 multiplication
    // SIO-CN2CH/HPC4�� ���
    // dwMethod --> 0x00 : Up/Down ���, A phase : �޽�, B phase : ����
    // dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
    // dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
    // dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
function AxcSignalGetEncInputMethod(lChannelNo : LongInt; dwpUpMethod : PDWord) : DWord; stdcall;

    // ī���� ����� Ʈ���Ÿ� ���� �մϴ�.
    // dwMode -->  0x00 : Latch
    // dwMode -->  0x01 : State
    // dwMode -->  0x02 : Special State    --> SIO-CN2CH ����
    // SIO-CN2CH�� ���
    // dwMode -->  0x00 : ���� ��ġ Ʈ���� �Ǵ� �ֱ� ��ġ Ʈ����.
    // ���� : ��ǰ���� ����� ���� �ٸ��� ������ �����Ͽ� ��� �ʿ�.
    // dwMode -->  0x01 : �ð� �ֱ� Ʈ����(AxcTriggerSetFreq�� ����)
    // SIO-HPC4�� ���
    // dwMode -->  0x00 : absolute mode[with ram data].
    // dwMode -->  0x01 : timer mode.
    // dwMode -->  0x02 : absolute mode[with fifo].
    // dwMode -->  0x03 : periodic mode.[Default]
function AxcTriggerSetFunction(lChannelNo : LongInt; dwMode : DWord) : DWord; stdcall;

    // ī���� ����� Ʈ���� ������ Ȯ�� �մϴ�.
    // *dwMode -->  0x00 : Latch
    // *dwMode -->  0x01 : State
    // *dwMode -->  0x02 : Special State
    // dwMode -->  0x00 : ���� ��ġ Ʈ���� �Ǵ� �ֱ� ��ġ Ʈ����.
    // ���� : ��ǰ���� ����� ���� �ٸ��� ������ �����Ͽ� ��� �ʿ�.
    // dwMode -->  0x01 : �ð� �ֱ� Ʈ����(AxcTriggerSetFreq�� ����)
    // SIO-HPC4�� ���
    // dwMode -->  0x00 : absolute mode[with ram data].
    // dwMode -->  0x01 : timer mode.
    // dwMode -->  0x02 : absolute mode[with fifo].
    // dwMode -->  0x03 : periodic mode.[Default]
function AxcTriggerGetFunction(lChannelNo : LongInt; dwpMode : PDWord) : DWord; stdcall;

    // dwUsage --> 0x00 : Trigger Not use
    // dwUsage --> 0x01 : Trigger use
function AxcTriggerSetNotchEnable(lChannelNo : LongInt; dwUsage : DWord) : DWord; stdcall;

    // *dwUsage --> 0x00 : Trigger Not use
    // *dwUsage --> 0x01 : Trigger use
function AxcTriggerGetNotchEnable(lChannelNo : LongInt; dwpUsage : PDWord) : DWord; stdcall;
    

    // ī���� ����� Captuer �ؼ��� ���� �մϴ�.(External latch input polarity)
    // dwCapturePol --> 0x00 : Signal OFF -> ON
    // dwCapturePol --> 0x01 : Signal ON -> OFF
function AxcSignalSetCaptureFunction(lChannelNo : LongInt; dwCapturePol : DWord) : DWord; stdcall;

    // ī���� ����� Captuer �ؼ� ������ Ȯ�� �մϴ�.(External latch input polarity)
    // *dwCapturePol --> 0x00 : Signal OFF -> ON
    // *dwCapturePol --> 0x01 : Signal ON -> OFF
function AxcSignalGetCaptureFunction(lChannelNo : LongInt; dwpCapturePol : PDWord) : DWord; stdcall;

    // ī���� ����� Captuer ��ġ�� Ȯ�� �մϴ�.(External latch)
    // *dbpCapturePos --> Capture position ��ġ
function AxcSignalGetCapturePos(lChannelNo : LongInt; dbpCapturePos : PDouble) : DWord; stdcall;

    // ī���� ����� ī���� ���� Ȯ�� �մϴ�.
    // *dbpActPos --> ī���� ��
function AxcStatusGetActPos(lChannelNo : LongInt; dbpActPos : PDouble) : DWord; stdcall;

    // ī���� ����� ī���� ���� dbActPos ������ ���� �մϴ�.
function AxcStatusSetActPos(lChannelNo : LongInt; dbActPos : Double) : DWord; stdcall;

    // ī���� ����� Ʈ���� ��ġ�� �����մϴ�.
    // ī���� ����� Ʈ���� ��ġ�� 2�������� ���� �� �� �ֽ��ϴ�.
function AxcTriggerSetNotchPos(lChannelNo : LongInt; dbLowerPos : Double; dbUpperPos : Double) : DWord; stdcall;

    // ī���� ����� ������ Ʈ���� ��ġ�� Ȯ�� �մϴ�.
function AxcTriggerGetNotchPos(lChannelNo : LongInt; dbpLowerPos : PDouble; dbpUpperPos : PDouble) : DWord; stdcall;

    // ī���� ����� Ʈ���� ����� ������ �մϴ�.
    // dwOutVal --> 0x00 : Ʈ���� ��� '0'
    // dwOutVal --> 0x01 : Ʈ���� ��� '1'
function AxcTriggerSetOutput(lChannelNo : LongInt; dwOutVal : DWord) : DWord; stdcall;

    // ī���� ����� ���¸� Ȯ���մϴ�.
    // Bit '0' : Carry (ī���� ����ġ�� ���� �޽��� ���� ī���� ����ġ�� �Ѿ� 0�� �ٲ���� �� 1��ĵ�� ON���� �մϴ�.)
    // Bit '1' : Borrow (ī���� ����ġ�� ���� �޽��� ���� 0�� �Ѿ� ī���� ����ġ�� �ٲ���� �� 1��ĵ�� ON���� �մϴ�.)
    // Bit '2' : Trigger output status
    // Bit '3' : Latch input status
function AxcStatusGetChannel(lChannelNo : LongInt; dwpChannelStatus : DWord) : DWord; stdcall;


    // SIO-CN2CH ���� �Լ���
    //
    // ī���� ����� ��ġ ������ �����Ѵ�.
    // ���� ��ġ �̵����� ���� �޽� ������ �����ϴµ�,
    // ex) 1mm �̵��� 1000�� �ʿ��ϴٸ�dMoveUnitPerPulse = 0.001�� �Է��ϰ�,
    //     ���� ��� �Լ��� ��ġ�� ���õ� ���� mm ������ �����ϸ� �ȴ�.
function AxcMotSetMoveUnitPerPulse(lChannelNo : LongInt; dMoveUnitPerPulse : Double) : DWord; stdcall;

    // ī���� ����� ��ġ ������ Ȯ���Ѵ�.
function AxcMotGetMoveUnitPerPulse(lChannelNo : LongInt;  dpMoveUnitPerPuls : PDouble) : DWord; stdcall;

    // ī���� ����� ���ڴ� �Է� ī���͸� ���� ����� �����Ѵ�.
    // dwReverse --> 0x00 : �������� ����.
    // dwReverse --> 0x01 : ����.
function AxcSignalSetEncReverse(lChannelNo : LongInt; dwReverse : DWord) : DWord; stdcall;

    // ī���� ����� ���ڴ� �Է� ī���͸� ���� ����� ������ Ȯ���Ѵ�.
function AxcSignalGetEncReverse(lChannelNo : LongInt; dwpReverse : PDWord) : DWord; stdcall;

    // ī���� ����� Encoder �Է� ��ȣ�� �����Ѵ�.
    // dwSource -->  0x00 : 2(A/B)-Phase ��ȣ.
    // dwSource -->  0x01 : Z-Phase ��ȣ.(���⼺ ����.)
function AxcSignalSetEncSource(lChannelNo : LongInt; dwSource : DWord) : DWord; stdcall;

    // ī���� ����� Encoder �Է� ��ȣ ���� ������ Ȯ���Ѵ�.
function AxcSignalGetEncSource(lChannelNo : LongInt; dwpSource : PDWord) : DWord; stdcall;

    // ī���� ����� Ʈ���� ��� ���� �� ���� ���� �����Ѵ�.
    // ��ġ �ֱ� Ʈ���� ��ǰ�� ��� ��ġ �ֱ�� Ʈ���� ����� �߻���ų ���� �� ���� ���� �����Ѵ�.
    // ���� ��ġ Ʈ���� ��ǰ�� ��� Ram ���� ������ Ʈ���� ������ ���� ���� ��ġ�� �����Ѵ�.
    // ���� : AxcMotSetMoveUnitPerPulse�� ������ ����.
    // Note : ���Ѱ��� ���Ѱ����� �������� �����Ͽ��� �մϴ�.
function AxcTriggerSetBlockLowerPos(lChannelNo : LongInt; dLowerPosition : Double) : DWord; stdcall;

    // ī���� ����� Ʈ���� ��� ���� �� ���� ���� Ȯ���Ѵ�.
function AxcTriggerGetBlockLowerPos(lChannelNo : LongInt; dpLowerPosition : PDouble) : DWord; stdcall;

    // ī���� ����� Ʈ���� ��� ���� �� ���� ���� �����Ѵ�.
    // ��ġ �ֱ� Ʈ���� ��ǰ�� ��� ��ġ �ֱ�� Ʈ���� ����� �߻���ų ���� �� ���� ���� �����Ѵ�.
    // ���� ��ġ Ʈ���� ��ǰ�� ��� Ʈ���� ������ ������ Ram �� ������ ������ Ʈ���� ������ ����Ǵ� ��ġ�� ���ȴ�.
    // ���� : AxcMotSetMoveUnitPerPulse�� ������ ����.
    // Note : ���Ѱ��� ���Ѱ����� ū���� �����Ͽ��� �մϴ�.
function AxcTriggerSetBlockUpperPos(lChannelNo : LongInt; dUpperPosition : Double) : DWord; stdcall;
    // ī���� ����� Ʈ���� ��� ���� �� ���� ���� �����Ѵ�.
function AxcTriggerGetBlockUpperPos(lChannelNo : LongInt; dpUpperrPosition : PDouble) : DWord; stdcall;

    // ī���� ����� ��ġ �ֱ� ��� Ʈ���ſ� ���Ǵ� ��ġ �ֱ⸦ �����Ѵ�.
    // ���� : AxcMotSetMoveUnitPerPulse�� ������ ����.
function AxcTriggerSetPosPeriod(lChannelNo : LongInt; dPeriod : Double) : DWord; stdcall;

    // ī���� ����� ��ġ �ֱ� ��� Ʈ���ſ� ���Ǵ� ��ġ �ֱ⸦ Ȯ���Ѵ�.
function AxcTriggerGetPosPeriod(lChannelNo : LongInt; dpPeriod : PDouble) : DWord; stdcall;

    // ī���� ����� ��ġ �ֱ� ��� Ʈ���� ���� ��ġ ������ ���� ��ȿ����� �����Ѵ�.
    // dwDirection -->  0x00 : ī������ ��/���� ���Ͽ� Ʈ���� �ֱ� ���� ���.
    // dwDirection -->  0x01 : ī���Ͱ� ���� �Ҷ��� Ʈ���� �ֱ� ���� ���.
    // dwDirection -->  0x01 : ī���Ͱ� ���� �Ҷ��� Ʈ���� �ֱ� ���� ���.
function AxcTriggerSetDirectionCheck(lChannelNo : LongInt; dwDirection : DWord) : DWord; stdcall;
    // ī���� ����� ��ġ �ֱ� ��� Ʈ���� ���� ��ġ ������ ���� ��ȿ��� ������ Ȯ���Ѵ�.
function AxcTriggerGetDirectionCheck(lChannelNo : LongInt; dwpDirection : PDWord) : DWord; stdcall;

    // ī���� ����� ��ġ �ֱ� ��� Ʈ���� ����� ����, ��ġ �ֱ⸦ �ѹ��� �����Ѵ�.
    // ��ġ ���� ���� :  AxcMotSetMoveUnitPerPulse�� ������ ����.
function AxcTriggerSetBlock(lChannelNo : LongInt; dLower : Double; dUpper : Double; dABSod : Double) : DWord; stdcall;

    // ī���� ����� ��ġ �ֱ� ��� Ʈ���� ����� ����, ��ġ �ֱ⸦ ������ �ѹ��� Ȯ���Ѵ�.
function AxcTriggerGetBlock(lChannelNo : LongInt; dpLower : PDouble; dpUpper : PDouble; dpABSod : PDouble) : DWord; stdcall;

    // ī���� ����� Ʈ���� ��� �޽� ���� �����Ѵ�.
    // ���� : uSec
function AxcTriggerSetTime(lChannelNo : LongInt; dTrigTime : Double) : DWord; stdcall;

    // ī���� ����� Ʈ���� ��� �޽� �� ������ Ȯ���Ѵ�.
function AxcTriggerGetTime(lChannelNo : LongInt; dpTrigTime : PDouble) : DWord; stdcall;

    // ī���� ����� Ʈ���� ��� �޽��� ��� ������ �����Ѵ�.
    // dwLevel -->  0x00 : Ʈ���� ��½� 'Low' ���� ���.
    // dwLevel -->  0x00 : Ʈ���� ��½� 'High' ���� ���.
function AxcTriggerSetLevel(lChannelNo : LongInt; dwLevel : DWord) : DWord; stdcall;
    // ī���� ����� Ʈ���� ��� �޽��� ��� ���� ������ Ȯ���Ѵ�.
function AxcTriggerGetLevel(lChannelNo : LongInt; dwpLevel : PDWord) : DWord; stdcall;

    // ī���� ����� ���ļ� Ʈ���� ��� ��ɿ� �ʿ��� ���ļ��� �����Ѵ�.
    // ���� : Hz, ���� : 1Hz ~ 500 kHz
function AxcTriggerSetFreq(lChannelNo : LongInt; dwFreqency : DWord) : DWord; stdcall;
    // ī���� ����� ���ļ� Ʈ���� ��� ��ɿ� �ʿ��� ���ļ��� ������ Ȯ���Ѵ�.
function AxcTriggerGetFreq(lChannelNo : LongInt; dwpFreqency : PDWord) : DWord; stdcall;	

    // ī���� ����� ���� ä�ο� ���� ���� ��� ���� �����Ѵ�.
    // dwOutput ���� : 0x00 ~ 0x0F, �� ä�δ� 4���� ���� ���
function AxcSignalWriteOutput(lChannelNo : LongInt; dwOutput : DWord) : DWord; stdcall;

    // ī���� ����� ���� ä�ο� ���� ���� ��� ���� Ȯ���Ѵ�.
function AxcSignalReadOutput(lChannelNo : LongInt; dwpOutput : PDWord) : DWord; stdcall;

    // ī���� ����� ���� ä�ο� ���� ���� ��� ���� ��Ʈ ���� �����Ѵ�.
    // lBitNo ���� : 0 ~ 3, �� ä�δ� 4���� ���� ���
function AxcSignalWriteOutputBit(lChannelNo : LongInt; lBitNo : LongInt; uOnOff : DWord) : DWord; stdcall;
    // ī���� ����� ���� ä�ο� ���� ���� ��� ���� ��Ʈ ���� Ȯ�� �Ѵ�.
    // lBitNo ���� : 0 ~ 3
function AxcSignalReadOutputBit(lChannelNo : LongInt; lBitNo : LongInt; upOnOff : PDWord) : DWord; stdcall;

    // ī���� ����� ���� ä�ο� ���� ���� �Է� ���� Ȯ���Ѵ�.
function AxcSignalReadInput(lChannelNo : LongInt; dwpInput : PDWord) : DWord; stdcall;

    // ī���� ����� ���� ä�ο� ���� ���� �Է� ���� ��Ʈ ���� Ȯ�� �Ѵ�.
    // lBitNo ���� : 0 ~ 3
function AxcSignalReadInputBit(lChannelNo : LongInt; lBitNo : LongInt; upOnOff : PDWord) : DWord; stdcall;

    // ī���� ����� Ʈ���� ����� Ȱ��ȭ �Ѵ�.
    // ���� ������ ��ɿ� ���� Ʈ���� ����� ���������� ����� ������ �����Ѵ�.
function AxcTriggerSetEnable(lChannelNo : LongInt; dwUsage : DWord) : DWord; stdcall;

    // ī���� ����� Ʈ���� ��� Ȱ��ȭ ���� ������ Ȯ���ϴ�.
function AxcTriggerGetEnable(lChannelNo : LongInt; dwpUsage : PDWord) : DWord; stdcall;

    // ī���� ����� ������ġ Ʈ���� ����� ���� ������ RAM ������ Ȯ���Ѵ�.
    // dwAddr ���� : 0x0000 ~ 0x1FFFF;
function AxcTriggerReadAbsRamData(lChannelNo : LongInt; dwAddr : DWord; dwpData : PDWord) : DWord; stdcall;

    // ī���� ����� ������ġ Ʈ���� ����� ���� �ʿ��� RAM ������ �����Ѵ�.
    // dwAddr ���� : 0x0000 ~ 0x1FFFF;
function AxcTriggerWriteAbsRamData(lChannelNo : LongInt; dwAddr : DWord; dwData : DWord) : DWord; stdcall;

    // ī���� ����� ������ġ Ʈ���� ����� ���� �ʿ��� RAM ������ �ѹ��� �����Ѵ�.
    // dwTrigNum ���� : ~ 0x20000  *RTEX CNT2 �� ��� 0x200*
    // dwDirection --> 0x0 : ���� Ʈ���� ��ġ�� ���� Ʈ���� ���� ���� �Է�. ��ġ�� �����ϴ� �������� Ʈ���� ��½� ���.
    // dwDirection --> 0x1 : ���� ī���Ϳ� ���� Ʈ���� ���� ���� �Է�. ��ġ�� �����ϴ� �������� Ʈ���� ��½� ���.
function AxcTriggerSetAbs(lChannelNo : LongInt; dwTrigNum : DWord; dwTrigPos : PDWord; dwDirection : DWord) : DWord; stdcall;

implementation

const

    dll_name    = 'AXL.dll';

    function AxcInfoIsCNTModule; external dll_name name 'AxcInfoIsCNTModule';
    function AxcInfoGetModuleNo; external dll_name name 'AxcInfoGetModuleNo';
    function AxcInfoGetModuleCount; external dll_name name 'AxcInfoGetModuleCount';
    function AxcInfoGetChannelCount; external dll_name name 'AxcInfoGetChannelCount';
    function AxcInfoGetTotalChannelCount; external dll_name name 'AxcInfoGetTotalChannelCount';
    function AxcInfoGetModule; external dll_name name 'AxcInfoGetModule';
    function AxcInfoGetModuleStatus; external dll_name name 'AxcInfoGetModuleStatus';
    function AxcInfoGetFirstChannelNoOfModuleNo; external dll_name name 'AxcInfoGetFirstChannelNoOfModuleNo';
    function AxcSignalSetEncInputMethod; external dll_name name 'AxcSignalSetEncInputMethod';
    function AxcSignalGetEncInputMethod; external dll_name name 'AxcSignalGetEncInputMethod';
    function AxcTriggerSetFunction; external dll_name name 'AxcTriggerSetFunction';
    function AxcTriggerGetFunction; external dll_name name 'AxcTriggerGetFunction';
    function AxcTriggerSetNotchEnable; external dll_name name 'AxcTriggerSetNotchEnable';
    function AxcTriggerGetNotchEnable; external dll_name name 'AxcTriggerGetNotchEnable';
    function AxcSignalSetCaptureFunction; external dll_name name 'AxcSignalSetCaptureFunction';
    function AxcSignalGetCaptureFunction; external dll_name name 'AxcSignalGetCaptureFunction';
    function AxcSignalGetCapturePos; external dll_name name 'AxcSignalGetCapturePos';
    function AxcStatusGetActPos; external dll_name name 'AxcStatusGetActPos';
    function AxcStatusSetActPos; external dll_name name 'AxcStatusSetActPos';
    function AxcTriggerSetNotchPos; external dll_name name 'AxcTriggerSetNotchPos';
    function AxcTriggerGetNotchPos; external dll_name name 'AxcTriggerGetNotchPos';
    function AxcTriggerSetOutput; external dll_name name 'AxcTriggerSetOutput';
    function AxcStatusGetChannel; external dll_name name 'AxcStatusGetChannel';
    function AxcMotSetMoveUnitPerPulse; external dll_name name 'AxcMotSetMoveUnitPerPulse';
    function AxcMotGetMoveUnitPerPulse; external dll_name name 'AxcMotGetMoveUnitPerPulse';
    function AxcSignalSetEncReverse; external dll_name name 'AxcSignalSetEncReverse';
    function AxcSignalGetEncReverse; external dll_name name 'AxcSignalGetEncReverse';
    function AxcSignalSetEncSource; external dll_name name 'AxcSignalSetEncSource';
    function AxcSignalGetEncSource; external dll_name name 'AxcSignalGetEncSource';
    function AxcTriggerSetBlockLowerPos; external dll_name name 'AxcTriggerSetBlockLowerPos';
    function AxcTriggerGetBlockLowerPos; external dll_name name 'AxcTriggerGetBlockLowerPos';
    function AxcTriggerSetBlockUpperPos; external dll_name name 'AxcTriggerSetBlockUpperPos';
    function AxcTriggerGetBlockUpperPos; external dll_name name 'AxcTriggerGetBlockUpperPos';
    function AxcTriggerSetPosPeriod; external dll_name name 'AxcTriggerSetPosPeriod';
    function AxcTriggerGetPosPeriod; external dll_name name 'AxcTriggerGetPosPeriod';
    function AxcTriggerSetDirectionCheck; external dll_name name 'AxcTriggerSetDirectionCheck';
    function AxcTriggerGetDirectionCheck; external dll_name name 'AxcTriggerGetDirectionCheck';
    function AxcTriggerSetBlock; external dll_name name 'AxcTriggerSetBlock';
    function AxcTriggerGetBlock; external dll_name name 'AxcTriggerGetBlock';
    function AxcTriggerSetTime; external dll_name name 'AxcTriggerSetTime';
    function AxcTriggerGetTime; external dll_name name 'AxcTriggerGetTime';
    function AxcTriggerSetLevel; external dll_name name 'AxcTriggerSetLevel';
    function AxcTriggerGetLevel; external dll_name name 'AxcTriggerGetLevel';
    function AxcTriggerSetFreq; external dll_name name 'AxcTriggerSetFreq';
    function AxcTriggerGetFreq; external dll_name name 'AxcTriggerGetFreq';
    function AxcSignalWriteOutput; external dll_name name 'AxcSignalWriteOutput';
    function AxcSignalReadOutput; external dll_name name 'AxcSignalReadOutput';
    function AxcSignalWriteOutputBit; external dll_name name 'AxcSignalWriteOutputBit';
    function AxcSignalReadOutputBit; external dll_name name 'AxcSignalReadOutputBit';
    function AxcSignalReadInput; external dll_name name 'AxcSignalReadInput';
    function AxcSignalReadInputBit; external dll_name name 'AxcSignalReadInputBit';
    function AxcTriggerSetEnable; external dll_name name 'AxcTriggerSetEnable';
    function AxcTriggerGetEnable; external dll_name name 'AxcTriggerGetEnable';
    function AxcTriggerReadAbsRamData; external dll_name name 'AxcTriggerReadAbsRamData';
    function AxcTriggerWriteAbsRamData; external dll_name name 'AxcTriggerWriteAbsRamData';
    function AxcTriggerSetAbs; external dll_name name 'AxcTriggerSetAbs';
end.
