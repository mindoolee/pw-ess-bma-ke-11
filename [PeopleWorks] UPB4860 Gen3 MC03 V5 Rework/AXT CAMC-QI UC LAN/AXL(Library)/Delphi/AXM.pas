//*****************************************************************************
//*****************************************************************************
//**
//** File Name
//** ----------
//**
//** AXM.PAS
//**
//** COPYRIGHT (c) AJINEXTEK Co., LTD
//**
//*****************************************************************************
//*****************************************************************************
//**
//** Description
//** -----------
//** Ajinextek Motion Library Header File
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

unit AXM;
interface
uses Windows, Messages, AXHS;

//========== ���� �� ��� Ȯ���Լ�(Info) - Infomation =================================================================
// �ش� ���� �����ȣ, ��� ��ġ, ��� ���̵� ��ȯ�Ѵ�.
function AxmInfoGetAxis (lAxisNo : LongInt; lpBoardNo : PLongInt; lpModulePos : PLongInt; upModuleID : PDWord) : DWord; stdcall;
// ��� ����� �����ϴ��� ��ȯ�Ѵ�.
function AxmInfoIsMotionModule (upStatus : PDWord) : DWord; stdcall;
// �ش� ���� ��ȿ���� ��ȯ�Ѵ�.
function AxmInfoIsInvalidAxisNo (lAxisNo : LongInt) : DWord; stdcall;
// �ش� ���� ��� ������ �������� ��ȯ�Ѵ�.
function AxmInfoGetAxisStatus (lAxisNo : LongInt) : DWord; stdcall;
// �� ����, �ý��ۿ� ������ ��ȿ�� ��� ����� ��ȯ�Ѵ�.
function AxmInfoGetAxisCount (lpAxisCount : PLongInt) : DWord; stdcall;
// �ش� ����/����� ù��° ���ȣ�� ��ȯ�Ѵ�.
function AxmInfoGetFirstAxisNo (lBoardNo : LongInt; lModulePos : LongInt; lpAxisNo : PLongInt) : DWord; stdcall;
// �ش� ������ ù��° ���ȣ�� ��ȯ�Ѵ�.
function AxmInfoGetBoardFirstAxisNo (lBoardNo : LongInt; lModulePos : LongInt; lpAxisNo : PLongInt) : DWord; stdcall;

//========= ���� �� �Լ� ==============================================================================================
// �ʱ� ���¿��� AXM ��� �Լ��� ���ȣ ������ 0 ~ (���� �ý��ۿ� ������ ��� - 1) �������� ��ȿ������
// �� �Լ��� ����Ͽ� ���� ������ ���ȣ ��� ������ ���ȣ�� �ٲ� �� �ִ�.
// �� �Լ��� ���� �ý����� H/W ������� �߻��� ���� ���α׷��� �Ҵ�� ���ȣ�� �״�� �����ϰ� ���� ���� ����
// �������� ��ġ�� �����Ͽ� ����� ���� ������� �Լ��̴�.
// ���ǻ��� : ���� ���� ���� ���ȣ�� ���Ͽ� ���� ��ȣ�� ���� ���� �ߺ��ؼ� ������ ���
//            ���� ���ȣ�� ���� �ุ ���� ���ȣ�� ���� �� �� ������,
//            ������ ���� ������ ��ȣ�� ���ε� ���� ��� �Ұ����� ��찡 �߻� �� �� �ִ�.

// �������� �����Ѵ�.
function AxmVirtualSetAxisNoMap (lRealAxisNo : LongInt; lVirtualAxisNo : LongInt) : DWord; stdcall;
// ������ ����ä��(��) ��ȣ�� ��ȯ�Ѵ�.
function AxmVirtualGetAxisNoMap (lRealAxisNo : LongInt; lpVirtualAxisNo : PLongInt) : DWord; stdcall;
// ��Ƽ �������� �����Ѵ�.
function AxmVirtualSetMultiAxisNoMap (lSize : LongInt; lpRealAxesNo : PLongInt; lpVirtualAxesNo : PLongInt) : DWord; stdcall;
// ������ ��Ƽ ����ä��(��) ��ȣ�� ��ȯ�Ѵ�.
function AxmVirtualGetMultiAxisNoMap (lSize : LongInt; lpRealAxesNo : PLongInt; lpVirtualAxesNo : PLongInt) : DWord; stdcall;
// ������ ������ �����Ѵ�.
function AxmVirtualResetAxisMap () : DWord; stdcall;

//========= ���ͷ�Ʈ ���� �Լ� ========================================================================================
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
//    wMsg    : ������ �ڵ��� �޼���, ������� �ʰų� ����Ʈ���� ����Ϸ��� 0�� �Է�.
//    proc    : ���ͷ�Ʈ �߻��� ȣ��� �Լ��� ������, ������� ������ NULL�� �Է�.
//    pEvent  : �̺�Ʈ ������� �̺�Ʈ �ڵ�
// Ex)   
// procedure AxtInterruptProc(lActiveNo : LongInt; dwFlag : DWord); stdcall;
// begin
//     ... ;
// end;
function AxmInterruptSetAxis (lAxisNo : LongInt; hWnd : HWND; uMessage : DWord; pProc : AXT_INTERRUPT_PROC; pEvent : PDWord) : DWord; stdcall;

// ���� ���� ���ͷ�Ʈ ��� ���θ� �����Ѵ�
// �ش� �࿡ ���ͷ�Ʈ ���� / Ȯ��
// uUse : ��� ���� => DISABLE(0), ENABLE(1)
function AxmInterruptSetAxisEnable (lAxisNo : LongInt; uUse : DWord) : DWord; stdcall;
// ���� ���� ���ͷ�Ʈ ��� ���θ� ��ȯ�Ѵ�
function AxmInterruptGetAxisEnable (lAxisNo : LongInt; upUse : PDWord) : DWord; stdcall;

//���ͷ�Ʈ�� �̺�Ʈ ������� ����� ��� �ش� ���ͷ�Ʈ ���� �д´�.
function AxmInterruptRead (lpAxisNo : PLongInt; upFlag : PDWord) : DWord; stdcall;    
// �ش� ���� ���ͷ�Ʈ �÷��� ���� ��ȯ�Ѵ�.
function AxmInterruptReadAxisFlag (lAxisNo : LongInt; lBank : LongInt; upFlag : PDWord) : DWord; stdcall;

// ���� ���� ����ڰ� ������ ���ͷ�Ʈ �߻� ���θ� �����Ѵ�.
// lBank         : ���ͷ�Ʈ ��ũ ��ȣ (0 - 1) ��������.
// uInterruptNum : ���ͷ�Ʈ ��ȣ ���� ��Ʈ��ȣ�� ���� hex�� Ȥ�� define�Ȱ��� ����
// AXHS.h���Ͽ� INTERRUPT_BANK1, 2 DEF�� Ȯ���Ѵ�.
function AxmInterruptSetUserEnable (lAxisNo : LongInt; lBank : LongInt; uInterruptNum : DWord) : DWord; stdcall;
// ���� ���� ����ڰ� ������ ���ͷ�Ʈ �߻� ���θ� Ȯ���Ѵ�.
function AxmInterruptGetUserEnable (lAxisNo : LongInt; lBank : LongInt; upInterruptNum : PDWord) : DWord; stdcall;

//======== ��� �Ķ��Ÿ ���� =========================================================================================
// AxmMotLoadParaAll�� ������ Load ��Ű�� ������ �ʱ� �Ķ��Ÿ ������ �⺻ �Ķ��Ÿ ����. 
// ���� PC�� ���Ǵ� ����࿡ �Ȱ��� ����ȴ�. �⺻�Ķ��Ÿ�� �Ʒ��� ����. 
// 00:AXIS_NO.             =0          01:PULSE_OUT_METHOD.    =4         02:ENC_INPUT_METHOD.    =3     03:INPOSITION.          =2
// 04:ALARM.               =1          05:NEG_END_LIMIT.       =1         06:POS_END_LIMIT.       =1     07:MIN_VELOCITY.        =1
// 08:MAX_VELOCITY.        =700000     09:HOME_SIGNAL.         =4         10:HOME_LEVEL.          =1     11:HOME_DIR.            =0
// 12:ZPHASE_LEVEL.        =1          13:ZPHASE_USE.          =0         14:STOP_SIGNAL_MODE.    =0     15:STOP_SIGNAL_LEVEL.   =1
// 16:HOME_FIRST_VELOCITY. =100        17:HOME_SECOND_VELOCITY.=100       18:HOME_THIRD_VELOCITY. =20    19:HOME_LAST_VELOCITY.  =1
// 20:HOME_FIRST_ACCEL.    =400        21:HOME_SECOND_ACCEL.   =400       22:HOME_END_CLEAR_TIME. =1000  23:HOME_END_OFFSET.     =0
// 24:NEG_SOFT_LIMIT.      =-134217728 25:POS_SOFT_LIMIT.      =134217727 26:MOVE_PULSE.          =1     27:MOVE_UNIT.           =1
// 28:INIT_POSITION.       =1000       29:INIT_VELOCITY.       =200       30:INIT_ACCEL.          =400   31:INIT_DECEL.          =400
// 32:INIT_ABSRELMODE.     =0          33:INIT_PROFILEMODE.    =4         34:SVON_LEVEL.          =1     35:ALARM_RESET_LEVEL.   =1
// 36:ENCODER_TYPE.        =1          37:SOFT_LIMIT_SEL.      =0         38:SOFT_LIMIT_STOP_MODE.=0     39:SOFT_LIMIT_ENABLE.   =0

// 00=[AXIS_NO             ]: �� (0�� ���� ������)
// 01=[PULSE_OUT_METHOD    ]: Pulse out method TwocwccwHigh = 6
// 02=[ENC_INPUT_METHOD    ]: disable = 0, 1ü�� = 1, 2ü�� = 2, 4ü�� = 3, �ἱ ���ù��� ��ü��(-).1ü�� = 11  2ü�� = 12  4ü�� = 13
// 03=[INPOSITION          ], 04=[ALARM     ], 05,06 =[END_LIMIT   ]  : 0 = B����, 1= A����, 2 = ������, 3 = �������� ����
// 07=[MIN_VELOCITY        ]: ���� �ӵ�(START VELOCITY)
// 08=[MAX_VELOCITY        ]: ����̹��� ������ �޾Ƶ��ϼ� �ִ� ���� �ӵ�. ���� �Ϲ� Servo�� 700k
// Ex> screw : 20mm pitch drive: 10000 pulse ����: 400w
// 09=[HOME_SIGNAL         ]: 4 - Home in0 , 0 :PosEndLimit , 1 : NegEndLimit // _HOME_SIGNAL����.
// 10=[HOME_LEVEL          ]: 0 = B����, 1 = A����, 2 = ������, 3 = �������� ����
// 11=[HOME_DIR            ]: Ȩ ����(HOME DIRECTION) 1:+����, 0:-����
// 12=[ZPHASE_LEVEL        ]: 0 = B����, 1 = B����, 2 = ������, 3 = �������� ����
// 13=[ZPHASE_USE          ]: Z���뿩��. 0: ������ , 1: +����, 2: -���� 
// 14=[STOP_SIGNAL_MODE    ]: ESTOP, SSTOP ���� ��� 0:��������, 1:������ 
// 15=[STOP_SIGNAL_LEVEL   ]: ESTOP, SSTOP ��� ����.  0 = B����, 1 = A����, 2 = ������, 3 = �������� ���� 
// 16=[HOME_FIRST_VELOCITY ]: 1�������ӵ� 
// 17=[HOME_SECOND_VELOCITY]: �����ļӵ� 
// 18=[HOME_THIRD_VELOCITY ]: ������ �ӵ� 
// 19=[HOME_LAST_VELOCITY  ]: index�˻��� �����ϰ� �˻��ϱ����� �ӵ�. 
// 20=[HOME_FIRST_ACCEL    ]: 1�� ���ӵ� , 21=[HOME_SECOND_ACCEL   ] : 2�� ���ӵ� 
// 22=[HOME_END_CLEAR_TIME ]: ���� �˻� Enc �� Set�ϱ� ���� ���ð�,  23=[HOME_END_OFFSET] : ���������� Offset��ŭ �̵�.
// 24=[NEG_SOFT_LIMIT      ]: - SoftWare Limit ���� �����ϸ� ������, 25=[POS_SOFT_LIMIT ]: + SoftWare Limit ���� �����ϸ� ������.
// 26=[MOVE_PULSE          ]: ����̹��� 1ȸ���� �޽���              , 27=[MOVE_UNIT  ]: ����̹� 1ȸ���� �̵��� ��:��ũ�� Pitch
// 28=[INIT_POSITION       ]: ������Ʈ ���� �ʱ���ġ  , ����ڰ� ���Ƿ� ��밡��
// 29=[INIT_VELOCITY       ]: ������Ʈ ���� �ʱ�ӵ�  , ����ڰ� ���Ƿ� ��밡��
// 30=[INIT_ACCEL          ]: ������Ʈ ���� �ʱⰡ�ӵ�, ����ڰ� ���Ƿ� ��밡��
// 31=[INIT_DECEL          ]: ������Ʈ ���� �ʱⰨ�ӵ�, ����ڰ� ���Ƿ� ��밡��
// 32=[INIT_ABSRELMODE     ]: ����(0)/���(1) ��ġ ����
// 33=[INIT_PROFILEMODE    ]: �������ϸ��(0 - 4) ���� ����
//                            '0': ��Ī Trapezode, '1': ���Ī Trapezode, '2': ��Ī Quasi-S Curve, '3':��Ī S Curve, '4':���Ī S Curve
// 34=[SVON_LEVEL          ]: 0 = B����, 1 = A����
// 35=[ALARM_RESET_LEVEL   ]: 0 = B����, 1 = A����
// 36=[ENCODER_TYPE        ]: 0 = TYPE_INCREMENTAL, 1 = TYPE_ABSOLUTE
// 37=[SOFT_LIMIT_SEL      ]: 0 = COMMAND, 1 = ACTUAL
// 38=[SOFT_LIMIT_STOP_MODE]: 0 = EMERGENCY_STOP, 1 = SLOWDOWN_STOP
// 39=[SOFT_LIMIT_ENABLE   ]: 0 = DISABLE, 1 = ENABLE

// AxmMotSaveParaAll�� ���� �Ǿ��� .mot������ �ҷ��´�. �ش� ������ ����ڰ� Edit �Ͽ� ��� �����ϴ�.
function AxmMotLoadParaAll (szFilePath : PChar) : DWord; stdcall;
// ����࿡ ���� ��� �Ķ��Ÿ�� �ະ�� �����Ѵ�. .mot���Ϸ� �����Ѵ�.
function AxmMotSaveParaAll (szFilePath : PChar) : DWord; stdcall;

// �Ķ��Ÿ 28 - 31������ ����ڰ� ���α׷�������  �� �Լ��� �̿��� ���� �Ѵ�
function AxmMotSetParaLoad (lAxisNo : LongInt; dInitPos : Double; dInitVel : Double; dInitAccel : Double; dInitDecel : Double) : DWord; stdcall;
// �Ķ��Ÿ 28 - 31������ ����ڰ� ���α׷�������  �� �Լ��� �̿��� Ȯ�� �Ѵ�.
function AxmMotGetParaLoad (lAxisNo : LongInt; dpInitPos : PDouble; dpInitVel : PDouble; dpInitAccel : PDouble; dpInitDecel : PDouble) : DWord; stdcall;

// ���� ���� �޽� ��� ����� �����Ѵ�.
// uMethod  0 :OneHighLowHigh, 1 :OneHighHighLow, 2 :OneLowLowHigh, 3 :OneLowHighLow, 4 :TwoCcwCwHigh
//          5 :TwoCcwCwLow, 6 :TwoCwCcwHigh, 7 :TwoCwCcwLow, 8 :TwoPhase, 9 :TwoPhaseReverse
// OneHighLowHigh        = 0x0,        // 1�޽� ���, PULSE(Active High), ������(DIR=Low)  / ������(DIR=High)
// OneHighHighLow        = 0x1,        // 1�޽� ���, PULSE(Active High), ������(DIR=High) / ������(DIR=Low)
// OneLowLowHigh         = 0x2,        // 1�޽� ���, PULSE(Active Low),  ������(DIR=Low)  / ������(DIR=High)
// OneLowHighLow         = 0x3,        // 1�޽� ���, PULSE(Active Low),  ������(DIR=High) / ������(DIR=Low)
// TwoCcwCwHigh          = 0x4,        // 2�޽� ���, PULSE(CCW:������),  DIR(CW:������),  Active High
// TwoCcwCwLow           = 0x5,        // 2�޽� ���, PULSE(CCW:������),  DIR(CW:������),  Active Low
// TwoCwCcwHigh          = 0x6,        // 2�޽� ���, PULSE(CW:������),   DIR(CCW:������), Active High
// TwoCwCcwLow           = 0x7,        // 2�޽� ���, PULSE(CW:������),   DIR(CCW:������), Active Low
// TwoPhase              = 0x8,        // 2��(90' ������),  PULSE lead DIR(CW: ������), PULSE lag DIR(CCW:������)
// TwoPhaseReverse       = 0x9         // 2��(90' ������),  PULSE lead DIR(CCW: ������), PULSE lag DIR(CW:������)
function AxmMotSetPulseOutMethod (lAxisNo : LongInt; uMethod : DWord) : DWord; stdcall;
// ���� ���� �޽� ��� ��� ������ ��ȯ�Ѵ�,
function AxmMotGetPulseOutMethod (lAxisNo : LongInt; upMethod : PDWord) : DWord; stdcall;

// ���� ���� �ܺ�(Actual) ī��Ʈ�� ���� ���� ������ �����Ͽ� ���� ���� Encoder �Է� ����� �����Ѵ�.
// uMethod : 0 - 7 ����.
// ObverseUpDownMode     = 0x0,        // ������ Up/Down
// ObverseSqr1Mode       = 0x1,        // ������ 1ü��
// ObverseSqr2Mode       = 0x2,        // ������ 2ü��
// ObverseSqr4Mode       = 0x3,        // ������ 4ü��
// ReverseUpDownMode     = 0x4,        // ������ Up/Down
// ReverseSqr1Mode       = 0x5,        // ������ 1ü��
// ReverseSqr2Mode       = 0x6,        // ������ 2ü��
// ReverseSqr4Mode       = 0x7         // ������ 4ü��
function AxmMotSetEncInputMethod (lAxisNo : LongInt; uMethod : DWord) : DWord; stdcall;
// ���� ���� �ܺ�(Actual) ī��Ʈ�� ���� ���� ������ �����Ͽ� ���� ���� Encoder �Է� ����� ��ȯ�Ѵ�.
function AxmMotGetEncInputMethod (lAxisNo : LongInt; upMethod : PDWord) : DWord; stdcall;

// ���� �ӵ� ������ RPM(Revolution Per Minute)���� ���߰� �ʹٸ�.
// ex>    rpm ���:
// 4500 rpm ?
// unit/ pulse = 1 : 1�̸�      pulse/ sec �ʴ� �޽����� �Ǵµ�
// 4500 rpm�� ���߰� �ʹٸ�     4500 / 60 �� : 75ȸ��/ 1��
// ���Ͱ� 1ȸ���� �� �޽����� �˾ƾ� �ȴ�. �̰��� Encoder�� Z���� �˻��غ��� �˼��ִ�.
// 1ȸ��:1800 �޽���� 75 x 1800 = 135000 �޽��� �ʿ��ϰ� �ȴ�.
// AxmMotSetMoveUnitPerPulse�� Unit = 1, Pulse = 1800 �־� ���۽�Ų��.
// �������� : rpm���� �����ϰ� �ȴٸ� �ӵ��� ���ӵ� �� rpm������ �ٲ�� �ȴ�.

// ���� ���� �޽� �� �����̴� �Ÿ��� �����Ѵ�.
function AxmMotSetMoveUnitPerPulse (lAxisNo : LongInt; dUnit : Double; lPulse : LongInt) : DWord; stdcall;
// ���� ���� �޽� �� �����̴� �Ÿ��� ��ȯ�Ѵ�.
function AxmMotGetMoveUnitPerPulse (lAxisNo : LongInt; dpUnit : PDouble; lpPulse : PLongInt) : DWord; stdcall;

// ���� �࿡ ���� ���� ����Ʈ ���� ����� �����Ѵ�.
// uMethod : 0 -1 ����
// AutoDetect = 0x0 : �ڵ� ������.
// RestPulse  = 0x1 : ���� ������.
function AxmMotSetDecelMode (lAxisNo : LongInt; uMethod : DWord) : DWord; stdcall;
// ���� ���� ���� ���� ����Ʈ ���� ����� ��ȯ�Ѵ�
function AxmMotGetDecelMode (lAxisNo : LongInt; upMethod : PDWord) : DWord; stdcall;

// ���� �࿡ ���� ���� ��忡�� �ܷ� �޽��� �����Ѵ�.
// �����: ���� AxmMotSetRemainPulse�� 500 �޽��� ����
//           AxmMoveStartPos�� ��ġ 10000�� ��������쿡 9500�޽����� 
//           ���� �޽� 500��  AxmMotSetMinVel�� ������ �ӵ��� �����ϸ鼭 ���� �ȴ�.
function AxmMotSetRemainPulse (lAxisNo : LongInt; uData : DWord) : DWord; stdcall;
// ���� ���� ���� ���� ��忡�� �ܷ� �޽��� ��ȯ�Ѵ�.
function AxmMotGetRemainPulse (lAxisNo : LongInt; upData : PDWord) : DWord; stdcall;

// ���� �࿡ ��ӵ� ���� �Լ������� �ְ� �ӵ��� �����Ѵ�.
// ���ǻ��� : �Է� �ִ� �ӵ� ���� PPS�� �ƴ϶� UNIT �̴�.
// ex) �ִ� ��� ���ļ�(PCI-N804/404 : 10 MPPS)
// ex) �ִ� ��� Unit/Sec(PCI-N804/404 : 10MPPS * Unit/Pulse)
function AxmMotSetMaxVel (lAxisNo : LongInt; dVel : Double) : DWord; stdcall;
// ���� ���� ��ӵ� ���� �Լ������� �ְ� �ӵ��� ��ȯ�Ѵ�.
function AxmMotGetMaxVel (lAxisNo : LongInt; dpVel : PDouble) : DWord; stdcall;

// ���� ���� �̵� �Ÿ� ��� ��带 �����Ѵ�.
// uAbsRelMode : POS_ABS_MODE '0' - ���� ��ǥ��
//              POS_REL_MODE '1' - ��� ��ǥ��
function AxmMotSetAbsRelMode (lAxisNo : LongInt; uAbsRelMode : DWord) : DWord; stdcall;
// ���� ���� ������ �̵� �Ÿ� ��� ��带 ��ȯ�Ѵ�
function AxmMotGetAbsRelMode (lAxisNo : LongInt; upAbsRelMode : PDWord) : DWord; stdcall;

// ���� ���� ���� �ӵ� �������� ��带 �����Ѵ�.
// ProfileMode : SYM_TRAPEZOIDE_MODE    '0' - ��Ī Trapezode
//               ASYM_TRAPEZOIDE_MODE   '1' - ���Ī Trapezode
//               QUASI_S_CURVE_MODE     '2' - ��Ī Quasi-S Curve
//               SYM_S_CURVE_MODE       '3' - ��Ī S Curve
//               ASYM_S_CURVE_MODE      '4' - ���Ī S Curve
function AxmMotSetProfileMode (lAxisNo : LongInt; uProfileMode : DWord) : DWord; stdcall;
// ���� ���� ������ ���� �ӵ� �������� ��带 ��ȯ�Ѵ�.
function AxmMotGetProfileMode (lAxisNo : LongInt; upProfileMode : PDWord) : DWord; stdcall;

// ���� ���� ���ӵ� ������ �����Ѵ�.
// AccelUnit : UNIT_SEC2   '0' - ������ ������ unit/sec2 ���
//             SEC         '1' - ������ ������ sec ���
function AxmMotSetAccelUnit (lAxisNo : LongInt; uAccelUnit : DWord) : DWord; stdcall;
// ���� ���� ������ ���ӵ������� ��ȯ�Ѵ�.
function AxmMotGetAccelUnit (lAxisNo : LongInt; upAccelUnit : PDWord) : DWord; stdcall;

// ���ǻ���: �ּҼӵ��� UNIT/PULSE ���� �۰��� ��� �ּҴ����� UNIT/PULSE�� ���߾����⶧���� �ּ� �ӵ��� UNIT/PULSE �� �ȴ�.
// ���� �࿡ �ʱ� �ӵ��� �����Ѵ�.
function AxmMotSetMinVel (lAxisNo : LongInt; dMinVel : Double) : DWord; stdcall;
// ���� ���� �ʱ� �ӵ��� ��ȯ�Ѵ�.
function AxmMotGetMinVel (lAxisNo : LongInt; dpMinVel : PDouble) : DWord; stdcall;

// ���� ���� ���� ��ũ���� �����Ѵ�.[%].
function AxmMotSetAccelJerk (lAxisNo : LongInt; dAccelJerk : Double) : DWord; stdcall;
// ���� ���� ������ ���� ��ũ���� ��ȯ�Ѵ�.
function AxmMotGetAccelJerk (lAxisNo : LongInt; dpAccelJerk : PDouble) : DWord; stdcall;

// ���� ���� ���� ��ũ���� �����Ѵ�.[%].
function AxmMotSetDecelJerk (lAxisNo : LongInt; dDecelJerk : Double) : DWord; stdcall;
// ���� ���� ������ ���� ��ũ���� ��ȯ�Ѵ�.
function AxmMotGetDecelJerk (lAxisNo : LongInt; dpDecelJerk : PDouble) : DWord; stdcall;

// ���� ���� �ӵ� Profile������ �켱����(�ӵ� Or ���ӵ�)�� �����Ѵ�.
// Priority : PRIORITY_VELOCITY   '0' - �ӵ� Profile������ ������ �ӵ����� �������� �����(�Ϲ���� �� Spinner�� ���).
//            PRIORITY_ACCELTIME  '1' - �ӵ� Profile������ ������ �����ӽð��� �������� �����(��� ��� ���).
function AxmMotSetProfilePriority(lAxisNo : LongInt; uPriority : DWord) : DWord; stdcall;
// ���� ���� �ӵ� Profile������ �켱����(�ӵ� Or ���ӵ�)�� ��ȯ�Ѵ�.
function AxmMotGetProfilePriority(lAxisNo : LongInt; upPriority : PDWord) : DWord; stdcall;

//=========== ����� ��ȣ ���� �����Լ� ===============================================================================
// ���� ���� Z �� Level�� �����Ѵ�.
// uLevel : LOW(0), HIGH(1)
function AxmSignalSetZphaseLevel (lAxisNo : LongInt; uLevel : DWord) : DWord; stdcall;
// ���� ���� Z �� Level�� ��ȯ�Ѵ�.
function AxmSignalGetZphaseLevel (lAxisNo : LongInt; upLevel : PDWord) : DWord; stdcall;

// ���� ���� Servo-On��ȣ�� ��� ������ �����Ѵ�.
// uLevel : LOW(0), HIGH(1)
function AxmSignalSetServoOnLevel (lAxisNo : LongInt; uLevel : DWord) : DWord; stdcall;
// ���� ���� Servo-On��ȣ�� ��� ���� ������ ��ȯ�Ѵ�.
function AxmSignalGetServoOnLevel (lAxisNo : LongInt; upLevel : PDWord) : DWord; stdcall;

// ���� ���� Servo-Alarm Reset ��ȣ�� ��� ������ �����Ѵ�.
// uLevel : LOW(0), HIGH(1)
function AxmSignalSetServoAlarmResetLevel (lAxisNo : LongInt; uLevel : DWord) : DWord; stdcall;
// ���� ���� Servo-Alarm Reset ��ȣ�� ��� ������ ������ ��ȯ�Ѵ�.
function AxmSignalGetServoAlarmResetLevel (lAxisNo : LongInt; upLevel : PDWord) : DWord; stdcall;

// ���� ���� Inpositon ��ȣ ��� ���� �� ��ȣ �Է� ������ �����Ѵ�
// uLevel : LOW(0), HIGH(1), UNUSED(2), USED(3)
function AxmSignalSetInpos (lAxisNo : LongInt; uUse : DWord) : DWord; stdcall;
// ���� ���� Inpositon ��ȣ ��� ���� �� ��ȣ �Է� ������ ��ȯ�Ѵ�.
function AxmSignalGetInpos (lAxisNo : LongInt; upUse : PDWord) : DWord; stdcall;
// ���� ���� Inpositon ��ȣ �Է� ���¸� ��ȯ�Ѵ�.
function AxmSignalReadInpos (lAxisNo : LongInt; upStatus : PDWord) : DWord; stdcall;

// ���� ���� �˶� ��ȣ �Է� �� ��� ������ ��� ���� �� ��ȣ �Է� ������ �����Ѵ�.
// uLevel : LOW(0), HIGH(1), UNUSED(2), USED(3)
function AxmSignalSetServoAlarm (lAxisNo : LongInt; uUse : DWord) : DWord; stdcall;
// ���� ���� �˶� ��ȣ �Է� �� ��� ������ ��� ���� �� ��ȣ �Է� ������ ��ȯ�Ѵ�.
function AxmSignalGetServoAlarm (lAxisNo : LongInt; upUse : PDWord) : DWord; stdcall;
// ���� ���� �˶� ��ȣ�� �Է� ������ ��ȯ�Ѵ�.
function AxmSignalReadServoAlarm (lAxisNo : LongInt; upStatus : PDWord) : DWord; stdcall;

// ���� ���� end limit sensor�� ��� ���� �� ��ȣ�� �Է� ������ �����Ѵ�. 
// end limit sensor ��ȣ �Է� �� �������� �Ǵ� �������� ���� ������ �����ϴ�.
// uStopMode: EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
// uPositiveLevel, uNegativeLevel : LOW(0), HIGH(1), UNUSED(2), USED(3)
function AxmSignalSetLimit (lAxisNo : LongInt; uStopMode : DWord; uPositiveLevel : DWord; uNegativeLevel : DWord) : DWord; stdcall;
// ���� ���� end limit sensor�� ��� ���� �� ��ȣ�� �Է� ����, ��ȣ �Է� �� ������带 ��ȯ�Ѵ�
function AxmSignalGetLimit (lAxisNo : LongInt; upStopMode : PDWord; upPositiveLevel : PDWord; upNegativeLevel : PDWord) : DWord; stdcall;
// �������� end limit sensor�� �Է� ���¸� ��ȯ�Ѵ�.
function AxmSignalReadLimit (lAxisNo : LongInt; upPositiveStatus : PDWord; upNegativeStatus : PDWord) : DWord; stdcall;

// ���� ���� Software limit�� ��� ����, ����� ī��Ʈ, �׸��� ���� ����� �����Ѵ�
// uUse       : DISABLE(0), ENABLE(1)
// uStopMode  : EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
// uSelection : COMMAND(0), ACTUAL(1)
// ���ǻ���: �����˻��� �� �Լ��� �̿��Ͽ� ����Ʈ���� ������ �̸� �����ؼ� ������ �����˻��� �����˻��� ���߿� ���߾�������쿡��  Enable�ȴ�.
function AxmSignalSetSoftLimit (lAxisNo : LongInt; uUse : DWord; uStopMode : DWord; uSelection : DWord; dPositivePos : Double; dNegativePos : Double) : DWord; stdcall;
// ���� ���� Software limit�� ��� ����, ����� ī��Ʈ, �׸��� ���� ����� ��ȯ�Ѵ�
function AxmSignalGetSoftLimit (lAxisNo : LongInt; upUse : PDWord; upStopMode : PDWord; upSelection : PDWord; dpPositivePos : PDouble; dpNegativePos : PDouble) : DWord; stdcall;
// ���� ���� Software limit�� ���� ���¸� ��ȯ�Ѵ�.
function AxmSignalReadSoftLimit(lAxisNo : LongInt; upPositiveStatus : PDWord; upNegativeStatus : PDWord) : DWord; stdcall;

// ��� ���� ��ȣ�� ���� ��� (������/��������) �Ǵ� ��� ������ �����Ѵ�.
// uStopMode  : EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
// uLevel : LOW(0), HIGH(1), UNUSED(2), USED(3)
function AxmSignalSetStop (lAxisNo : LongInt; uStopMode : DWord; uLevel : DWord) : DWord; stdcall;
// ��� ���� ��ȣ�� ���� ��� (������/��������) �Ǵ� ��� ������ ��ȯ�Ѵ�.
function AxmSignalGetStop (lAxisNo : LongInt; upStopMode : PDWord; upLevel : PDWord) : DWord; stdcall;
// ��� ���� ��ȣ�� �Է� ���¸� ��ȯ�Ѵ�.
function AxmSignalReadStop (lAxisNo : LongInt; upStatus : PDWord) : DWord; stdcall;

// ���� ���� Servo-On ��ȣ�� ����Ѵ�.
// uOnOff : FALSE(0), TRUE(1) ( ���� 0��¿� �ش��)
function AxmSignalServoOn (lAxisNo : LongInt; uOnOff : DWord) : DWord; stdcall;
// ���� ���� Servo-On ��ȣ�� ��� ���¸� ��ȯ�Ѵ�.
function AxmSignalIsServoOn (lAxisNo : LongInt; upOnOff : PDWord) : DWord; stdcall;

// ���� ���� Servo-Alarm Reset ��ȣ�� ����Ѵ�.
// uOnOff : FALSE(0), TRUE(1) ( ���� 1��¿� �ش��)
function AxmSignalServoAlarmReset (lAxisNo : LongInt; uOnOff : DWord) : DWord; stdcall;

// ���� ��°��� �����Ѵ�.
// uValue : Hex Value 0x00
function AxmSignalWriteOutput (lAxisNo : LongInt; uValue : DWord) : DWord; stdcall;
// ���� ��°��� ��ȯ�Ѵ�.
function AxmSignalReadOutput (lAxisNo : LongInt; upValue : PDWord) : DWord; stdcall;

// lBitNo : Bit Number(0 - 4)
// uOnOff : FALSE(0), TRUE(1)
// ���� ��°��� ��Ʈ���� �����Ѵ�.
function AxmSignalWriteOutputBit (lAxisNo : LongInt; lBitNo : LongInt; uOnOff : DWord) : DWord; stdcall;
// ���� ��°��� ��Ʈ���� ��ȯ�Ѵ�.
function AxmSignalReadOutputBit (lAxisNo : LongInt; lBitNo : LongInt; upOnOff : PDWord) : DWord; stdcall;

// ���� �Է°��� Hex������ ��ȯ�Ѵ�.
function AxmSignalReadInput (lAxisNo : LongInt; upValue : PDWord) : DWord; stdcall;
// lBitNo : Bit Number(0 - 4)
// ���� �Է°��� ��Ʈ���� ��ȯ�Ѵ�.
function AxmSignalReadInputBit (lAxisNo : LongInt; lBitNo : LongInt; upOn : PDWord) : DWord; stdcall;

// �Է½�ȣ���� ������ ���Ͱ���� �����Ѵ�.
// uSignal: END_LIMIT(0), INP_ALARM(1), UIN_00_01(2), UIN_02_04(3)
// dBandwidthUsec: 0.2uSec~26666uSec
function AxmSignalSetFilterBandwidth(lAxisNo : LongInt; uSignal : DWord; dBandwidthUsec : Double) : DWord; stdcall;

//========== ��� ������ �� �����Ŀ� ���� Ȯ���ϴ� �Լ�================================================================
// (��������)���� ���� �޽� ��� ���¸� ��ȯ�Ѵ�.
function AxmStatusReadInMotion (lAxisNo : LongInt; upStatus : PDWord) : DWord; stdcall;

// (��������)�������� ���� ���� ���� ���� �޽� ī���� ���� ��ȯ�Ѵ�.
function AxmStatusReadDrivePulseCount (lAxisNo : LongInt; lpPulse : PLongInt) : DWord; stdcall;    

// ���� ���� DriveStatus(����� ����) �������͸� ��ȯ�Ѵ�
// ���ǻ��� : �� ��ǰ���� �ϵ�������� ��ȣ�� �ٸ��⶧���� �Ŵ��� �� AXHS.xxx ������ �����ؾ��Ѵ�.
function AxmStatusReadMotion (lAxisNo : LongInt; upStatus : PDWord) : DWord; stdcall;    

// ���� ���� EndStatus(���� ����) �������͸� ��ȯ�Ѵ�.
// ���ǻ��� : �� ��ǰ���� �ϵ�������� ��ȣ�� �ٸ��⶧���� �Ŵ��� �� AXHS.xxx ������ �����ؾ��Ѵ�.
function AxmStatusReadStop (lAxisNo : LongInt; upStatus : PDWord) : DWord; stdcall;    

// ���� ���� Mechanical Signal Data(���� ������� ��ȣ����) �� ��ȯ�Ѵ�.
// ���ǻ��� : �� ��ǰ���� �ϵ�������� ��ȣ�� �ٸ��⶧���� �Ŵ��� �� AXHS.xxx ������ �����ؾ��Ѵ�.
function AxmStatusReadMechanical (lAxisNo : LongInt; upStatus : PDWord) : DWord; stdcall;    

// ���� ���� ���� ���� �ӵ��� �о�´�.
function AxmStatusReadVel (lAxisNo : LongInt; dpVel : PDouble) : DWord; stdcall;    

// ���� ���� Command Pos�� Actual Pos�� ���� ��ȯ�Ѵ�.
function AxmStatusReadPosError (lAxisNo : LongInt; dpError : PDouble) : DWord; stdcall;    

// ���� ����̺�� �̵��ϴ�(�̵���) �Ÿ��� Ȯ�� �Ѵ�
function AxmStatusReadDriveDistance (lAxisNo : LongInt; dpUnit : PDouble) : DWord; stdcall;

// ���� ���� ��ġ ���� ��� ����� ���Ͽ� �����Ѵ�.
// uPosType  : Actual position �� Command position �� ǥ�� ���
//    POSITION_LIMIT '0' - �⺻ ����, ��ü ���� ������ ����
//    POSITION_BOUND '1' - ��ġ ���� �ֱ���, dNegativePos ~ dPositivePos ������ ����
// ���ǻ���(PCI-Nx04�ش�)
// - BOUNT������ ī��Ʈ ���� Max���� �ʰ� �� �� Min���̵Ǹ� �ݴ�� Min���� �ʰ� �� �� Max���� �ȴ�.
// - �ٽø��� ���� ��ġ���� ������ �� �ۿ��� ī��Ʈ �� ���� ���� Min, Max���� ������� �ʴ´�.
function AxmStatusSetPosType(lAxisNo : LongInt; uPosType : DWord; dPositivePos : Double; dNegativePos : Double) : DWord; stdcall;
// ���� ���� ��ġ ���� ��� ����� ���Ͽ� ��ȯ�Ѵ�.
function AxmStatusGetPosType(lAxisNo : LongInt; upPosType : PDWord; dpPositivePos : PDouble; dpNegativePos : PDouble) : DWord; stdcall;
// ���� ���� ����ġ ���ڴ� ���� Offset ��ġ�� �����Ѵ�.[PCI-R1604-MLII ����]
function AxmStatusSetAbsOrgOffset(lAxisNo : LongInt; dOrgOffsetPos : Double) : DWord; stdcall;

// ���� ���� Actual ��ġ�� �����Ѵ�.
function AxmStatusSetActPos (lAxisNo : LongInt; dPos : Double) : DWord; stdcall;
// ���� ���� Actual ��ġ�� ��ȯ�Ѵ�.
function AxmStatusGetActPos (lAxisNo : LongInt; dpPos : PDouble) : DWord; stdcall;

// ���� ���� Command ��ġ�� �����Ѵ�.
function AxmStatusSetCmdPos (lAxisNo : LongInt; dPos : Double) : DWord; stdcall;
// ���� ���� Command ��ġ�� ��ȯ�Ѵ�.
function AxmStatusGetCmdPos (lAxisNo : LongInt; dpPos : PDouble) : DWord; stdcall;
// ���� ���� Command ��ġ�� Actual ��ġ�� dPos ������ ��ġ ��Ų��.
function AxmStatusSetPosMatch(lAxisNo : LongInt; dPos : Double) : DWord; stdcall;

// Network ��ǰ �����Լ�.
// ������ ���� �����ѿ� AlarmCode�� �о������ ����ϴ� �Լ�.
function AxmStatusRequestServoAlarm(lAxisNo : LongInt) : DWord; stdcall;   
// ������ ���� ������ AlarmCode�� �о���� �Լ�.
// upAlarmCode      : �ش� �������� Alarm Code����
// uReturnMode      : �Լ��� ��ȯ ���������� ����
// [0-Immediate]    : �Լ� ���� �� �ٷ� ��ȯ
// [1-Blocking]     : ���������� ���� �˶� �ڵ带 ���� �� ���� ��ȯ��������
// [2-Non Blocking] : ���������� ���� �˶� �ڵ带 ���� �� ���� ��ȯ���������� ���α׷� Blocking��������
function AxmStatusReadServoAlarm(lAxisNo : LongInt; uReturnMode : DWord; upAlarmCode : PDWord) : DWord; stdcall;
// ������ �����ڵ忡 �ش��ϴ� Alarm String�� �޾ƿ��� �Լ�
function AxmStatusGetServoAlarmString(lAxisNo : LongInt; uAlarmCode : DWord; lAlarmStringSize : LongInt; szAlarmString : PChar) : DWord; stdcall;  

// ������ ���� �����ѿ� Alarm History�� �о������ ����ϴ� �Լ�
function AxmStatusRequestServoAlarmHistory(lAxisNo : LongInt) : DWord; stdcall;  
// ������ ���� ������ Alarm History�� �о���� �Լ�.    
// lpCount          : ���� Alarm History ���� 
// upAlarmCode      : Alarm History�� ��ȯ�� �迭   
// uReturnMode      : �Լ��� ��ȯ ���������� ����
// [0-Immediate]    : �Լ� ���� �� �ٷ� ��ȯ
// [1-Blocking]     : ���������� ���� �˶� �ڵ带 ���� �� ���� ��ȯ��������
// [2-Non Blocking] : ���������� ���� �˶� �ڵ带 ���� �� ���� ��ȯ���������� ���α׷� Blocking��������
function AxmStatusReadServoAlarmHistory(lAxisNo : LongInt; uReturnMode : DWord; lpCount : PLongInt; upAlarmCode : PDWord) : DWord; stdcall;  
// ������ ���� ������ Alarm History�� Clear�Ѵ�.
function AxmStatusClearServoAlarmHistory(lAxisNo : LongInt) : DWord; stdcall;  

//======== Ȩ���� �Լ�=================================================================================================
// ���� ���� Home ���� Level �� �����Ѵ�.
// uLevel : LOW(0), HIGH(1)
function AxmHomeSetSignalLevel (lAxisNo : LongInt; uLevel : DWord) : DWord; stdcall;
// ���� ���� Home ���� Level �� ��ȯ�Ѵ�.
function AxmHomeGetSignalLevel (lAxisNo : LongInt; upLevel : PDWord) : DWord; stdcall;
// ���� Ȩ ��ȣ �Է»��¸� Ȯ���Ѵ�. Ȩ��ȣ�� ����ڰ� ���Ƿ� AxmHomeSetMethod �Լ��� �̿��Ͽ� �����Ҽ��ִ�.
// �Ϲ������� Ȩ��ȣ�� ���� �Է� 0�� ����ϰ������� AxmHomeSetMethod �̿��ؼ� �ٲٸ� + , - Limit�� ����Ҽ����ִ�.
// upStatus : OFF(0), ON(1)
function AxmHomeReadSignal (lAxisNo : LongInt; upStatus : PDWord) : DWord; stdcall;

// �ش� ���� �����˻��� �����ϱ� ���ؼ��� �ݵ�� ���� �˻����� �Ķ��Ÿ���� �����Ǿ� �־�� �˴ϴ�. 
// ���� MotionPara���� ������ �̿��� �ʱ�ȭ�� ���������� ����ƴٸ� ������ ������ �ʿ����� �ʴ�. 
// �����˻� ��� �������� �˻� �������, �������� ����� ��ȣ, �������� Active Level, ���ڴ� Z�� ���� ���� ���� ���� �Ѵ�.
// ���ǻ��� : ������ �߸� ������ -�������� �����ص�  +�������� �����Ҽ� ������, Ȩ�� ã�µ� �־� ������ �ɼ��ִ�.
// (�ڼ��� ������ AxmMotSaveParaAll ���� �κ� ����)
// Ȩ������ AxmSignalSetHomeLevel ����Ѵ�.
// HClrTim : HomeClear Time : ���� �˻� Encoder �� Set�ϱ� ���� ���ð� 
// HmDir(Ȩ ����): DIR_CCW (0) -���� , DIR_CW(1) +����
// HOffset - ���������� �̵��Ÿ�.
// uZphas: 1�� �����˻� �Ϸ� �� ���ڴ� Z�� ���� ���� ����  0: ������ , 1: HmDir�� �ݴ� ����, 2: HmDir�� ���� ����
// HmSig : PosEndLimit(0) -> +Limit
//         NegEndLimit(1) -> -Limit
//         HomeSensor (4) -> ��������(���� �Է� 0)
function AxmHomeSetMethod (lAxisNo : LongInt; lHmDir : LongInt; uHomeSignal : DWord; uZphas : DWord; dHomeClrTime : Double; dHomeOffset : Double) : DWord; stdcall;
// �����Ǿ��ִ� Ȩ ���� �Ķ��Ÿ���� ��ȯ�Ѵ�.
function AxmHomeGetMethod (lAxisNo : LongInt; lpHmDir : PLongInt; upHomeSignal : PDWord; upZphas : PDWord; dpHomeClrTime : PDouble; dpHomeOffset : PDouble) : DWord; stdcall;

// �����˻� ����� �̼������� �ϴ� �Լ�(�⺻������ �������� �ʾƵ���).
// dHomeDogDistance[500 pulse]: ù��° Step���� HomeDog�� ������ �����ƴ��� Ȯ���ϱ����� Dog���̸� �Է�.(������ AxmMotSetMoveUnitPerPulse�Լ��� ������ ����)
// lLevelScanTime[100msec]: 2��° Step(���������� ���������� ����)���� Level���¸� Ȯ���� Scan�ð��� ����(������ msec[1~1000]).
// dwFineSearchUse[USE]: �⺻ �����˻��� 5 Step�� ����ϴµ� 3 Step�� ����ϵ��� �����Ҷ� 0���� ����.
// dwHomeClrUse[USE]: �����˻� �� ���ɰ��� Encoder���� 0���� �ڵ� �������θ� ����.
function AxmHomeSetFineAdjust(lAxisNo : LongInt; dHomeDogLength : Double; lLevelScanTime : LongInt; uFineSearchUse : DWord; uHomeClrUse : DWord) : DWord; stdcall;
// �����Ǿ��ִ� Ȩ ���� �̼����� �Ķ��Ÿ���� ��ȯ�Ѵ�.
function AxmHomeGetFineAdjust(lAxisNo : LongInt; dpHomeDogLength : PDouble; lpLevelScanTime : PLongInt; upFineSearchUse : PDWord; upHomeClrUse : PDWord) : DWord; stdcall;

// ������ ������ �����ϰ� �˻��ϱ� ���� ���� �ܰ��� �������� �����Ѵ�. �̶� �� ���ǿ� ��� �� �ӵ��� �����Ѵ�. 
// �� �ӵ����� �������� ���� �����˻� �ð���, �����˻� ���е��� �����ȴ�. 
// �� ���Ǻ� �ӵ����� ������ �ٲ㰡�鼭 �� ���� �����˻� �ӵ��� �����ϸ� �ȴ�. 
// (�ڼ��� ������ AxmMotSaveParaAll ���� �κ� ����)
// �����˻��� ���� �ӵ��� �����ϴ� �Լ�
// [dVelFirst]- 1�������ӵ�   [dVelSecond]-�����ļӵ�   [dVelThird]- ������ �ӵ�  [dvelLast]- index�˻��� �����ϰ� �˻��ϱ�����. 
// [dAccFirst]- 1���������ӵ� [dAccSecond]-�����İ��ӵ� 
function AxmHomeSetVel (lAxisNo : LongInt; dVelFirst : Double; dVelSecond : Double; dVelThird : Double; dVelLast : Double; dAccFirst : Double; dAccSecond : Double) : DWord; stdcall;
// �����Ǿ��ִ� �����˻��� ���� �ӵ��� ��ȯ�Ѵ�.
function AxmHomeGetVel (lAxisNo : LongInt; dpVelFirst : PDouble; dpVelSecond : PDouble; dpVelThird : PDouble; dpVelLast : PDouble; dpAccFirst : PDouble; dpAccSecond : PDouble) : DWord; stdcall;

// �����˻��� �����Ѵ�.
// �����˻� �����Լ��� �����ϸ� ���̺귯�� ���ο��� �ش����� �����˻��� ���� �� �����尡 �ڵ� �����Ǿ� �����˻��� ���������� ������ �� �ڵ� ����ȴ�.
// ���ǻ��� : �������� �ݴ������ ����Ʈ ������ ���͵� ��������� ������ ACTIVE���������� �����Ѵ�.
//            ���� �˻��� ���۵Ǿ� ��������� ����Ʈ ������ ������ ����Ʈ ������ �����Ǿ��ٰ� �����ϰ� �����ܰ�� ����ȴ�.
function AxmHomeSetStart (lAxisNo : LongInt) : DWord; stdcall;
// �����˻� ����� ����ڰ� ���Ƿ� �����Ѵ�.
// �����˻� �Լ��� �̿��� ���������� �����˻��� ����ǰ��� �˻� ����� HOME_SUCCESS�� �����˴ϴ�.
// �� �Լ��� ����ڰ� �����˻��� ���������ʰ� ����� ���Ƿ� ������ �� �ִ�. 
// uHomeResult ����
// HOME_SUCCESS                 = 0x01  // Ȩ �Ϸ�
// HOME_SEARCHING               = 0x02  // Ȩ�˻���
// HOME_ERR_GNT_RANGE           = 0x10  // Ȩ �˻� ������ ��������
// HOME_ERR_USER_BREAK          = 0x11  // �ӵ� ������ ���Ƿ� ��������� ���������
// HOME_ERR_VELOCITY            = 0x12  // �ӵ� ���� �߸��������
// HOME_ERR_AMP_FAULT           = 0x13  // ������ �˶� �߻� ����
// HOME_ERR_NEG_LIMIT           = 0x14  // (-)���� ������ (+)����Ʈ ���� ���� ����
// HOME_ERR_POS_LIMIT           = 0x15  // (+)���� ������ (-)����Ʈ ���� ���� ����
// HOME_ERR_NOT_DETECT          = 0x16  // ������ ��ȣ �������� �� �� ��� ����
// HOME_ERR_UNKNOWN             = 0xFF    
function AxmHomeSetResult (lAxisNo : LongInt; uHomeResult : DWord) : DWord; stdcall;
// �����˻� ����� ��ȯ�Ѵ�.
// �����˻� �Լ��� �˻� ����� Ȯ���Ѵ�. �����˻��� ���۵Ǹ� HOME_SEARCHING���� �����Ǹ� �����˻��� �����ϸ� ���п����� �����ȴ�. ���� ������ ������ �� �ٽ� �����˻��� �����ϸ� �ȴ�.
function AxmHomeGetResult (lAxisNo : LongInt; upHomeResult : PDWord) : DWord; stdcall;

// �����˻� ������� ��ȯ�Ѵ�.
// �����˻� ���۵Ǹ� �������� Ȯ���� �� �ִ�. �����˻��� �Ϸ�Ǹ� �������ο� ������� 100�� ��ȯ�ϰ� �ȴ�. �����˻� �������δ� GetHome Result�Լ��� �̿��� Ȯ���� �� �ִ�.
// upHomeMainStepNumber : Main Step �������̴�. 
// ��Ʈ�� FALSE�� ���upHomeMainStepNumber : 0 �϶��� ������ �ุ ��������̰� Ȩ �������� upHomeStepNumber ǥ���Ѵ�.
// ��Ʈ�� TRUE�� ��� upHomeMainStepNumber : 0 �϶��� ������ Ȩ�� ��������̰� ������ Ȩ �������� upHomeStepNumber ǥ���Ѵ�.
// ��Ʈ�� TRUE�� ��� upHomeMainStepNumber : 10 �϶��� �����̺� Ȩ�� ��������̰� ������ Ȩ �������� upHomeStepNumber ǥ���Ѵ�.
// upHomeStepNumber     : ������ �࿡���� �������� ǥ���Ѵ�. 
// ��Ʈ�� FALSE�� ���  : ������ �ุ �������� ǥ���Ѵ�.
// ��Ʈ�� TRUE�� ��� ��������, �����̺��� ������ �������� ǥ�õȴ�.
function AxmHomeGetRate (lAxisNo : LongInt; upHomeMainStepNumber : PDWord; upHomeStepNumber : PDWord) : DWord; stdcall;

//========= ��ġ �����Լ� =============================================================================================
// ���ǻ���: ��ġ�� �����Ұ�� �ݵ�� UNIT/PULSE�� ���߾ �����Ѵ�.
//           ��ġ�� UNIT/PULSE ���� �۰��� ��� �ּҴ����� UNIT/PULSE�� ���߾����⶧���� ����ġ���� ������ �ɼ�����.

// ���� �ӵ� ������ RPM(Revolution Per Minute)���� ���߰� �ʹٸ�.
// ex>    rpm ���:
// 4500 rpm ?
// unit/ pulse = 1 : 1�̸�      pulse/ sec �ʴ� �޽����� �Ǵµ�
// 4500 rpm�� ���߰� �ʹٸ�     4500 / 60 �� : 75ȸ��/ 1��
// ���Ͱ� 1ȸ���� �� �޽����� �˾ƾ� �ȴ�. �̰��� Encoder�� Z���� �˻��غ��� �˼��ִ�.
// 1ȸ��:1800 �޽���� 75 x 1800 = 135000 �޽��� �ʿ��ϰ� �ȴ�.
// AxmMotSetMoveUnitPerPulse�� Unit = 1, Pulse = 1800 �־� ���۽�Ų��. 

// ������ �Ÿ���ŭ �Ǵ� ��ġ���� �̵��Ѵ�.
// ���� ���� ���� ��ǥ/ �����ǥ �� ������ ��ġ���� ������ �ӵ��� �������� ������ �Ѵ�.
// �ӵ� ���������� AxmMotSetProfileMode �Լ����� �����Ѵ�.
// �޽��� ��µǴ� �������� �Լ��� �����.
// AxmMotSetAccelUnit(lAxisNo, 1) �ϰ�� dAccel -> dAccelTime , dDecel -> dDecelTime ���� �ٲ��.
function AxmMoveStartPos (lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;

// ������ �Ÿ���ŭ �Ǵ� ��ġ���� �̵��Ѵ�.
// ���� ���� ���� ��ǥ/�����ǥ�� ������ ��ġ���� ������ �ӵ��� �������� ������ �Ѵ�.
// �ӵ� ���������� AxmMotSetProfileMode �Լ����� �����Ѵ�. 
// �޽� ����� ����Ǵ� �������� �Լ��� �����
function AxmMovePos (lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;

// ������ �ӵ��� �����Ѵ�.
// ���� �࿡ ���Ͽ� ������ �ӵ��� �������� ���������� �ӵ� ��� ������ �Ѵ�. 
// �޽� ����� ���۵Ǵ� �������� �Լ��� �����.
// Vel���� ����̸� CW, �����̸� CCW �������� ����.
function AxmMoveVel (lAxisNo : LongInt; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;

// ������ ���࿡ ���Ͽ� ������ �ӵ��� �������� ���������� �ӵ� ��� ������ �Ѵ�.
// �޽� ����� ���۵Ǵ� �������� �Լ��� �����.
// Vel���� ����̸� CW, �����̸� CCW �������� ����.
function AxmMoveStartMultiVel (lArraySize : LongInt; lpAxesNo : PLongInt; dpVel : PDouble; dpAccel : PDouble; dpDecel : PDouble) : DWord; stdcall;

// ������ ���࿡ ���Ͽ� ������ �ӵ��� ������, SyncMode�� ���� ���������� �ӵ� ��� ������ �Ѵ�.
// �޽� ����� ���۵Ǵ� �������� �Լ��� �����.
// Vel���� ����̸� CW, �����̸� CCW �������� ����.
// dwSyncMode    : ����������� ������(0), �������� ��ɸ� ���(1), �˶��� ���ؼ��� ���� ������ ���(2)
function AxmMoveStartMultiVelEx(lArraySize : LongInt; lpAxesNo : PLongInt; dpVel : PDouble; dpAccel : PDouble; dpDecel : PDouble; dwSyncMode : DWord) : DWord; stdcall;

// ������ ���࿡ ���Ͽ� ������ �ӵ��� �������� ���������� �ӵ� ��� ������ �Ѵ�.
// �޽� ����� ���۵Ǵ� �������� �Լ��� ����� Master����(Distance�� ���� ū) dVel�ӵ��� �����̸�, ������ ����� Distance������ �����δ�. 
// �ӵ��� �ش� Chip�� �� ��ȣ�� ���� ���� ���� �ӵ��� ����
function AxmMoveStartLineVel(lArraySize : LongInt; lpAxesNo : PLongInt; dpDis : PDouble; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;

// Ư�� Input ��ȣ�� Edge�� �����Ͽ� ������ �Ǵ� ���������ϴ� �Լ�.
// lDetect Signal : edge ������ �Է� ��ȣ ����.
// lDetectSignal  : PosEndLimit(0), NegEndLimit(1), HomeSensor(4), EncodZPhase(5), UniInput02(6), UniInput03(7)
// Signal Edge    : ������ �Է� ��ȣ�� edge ���� ���� (rising or falling edge).
//                  SIGNAL_DOWN_EDGE(0), SIGNAL_UP_EDGE(1)
// ��������       : Vel���� ����̸� CW, �����̸� CCW.
// SignalMethod   : ������ EMERGENCY_STOP(0), �������� SLOWDOWN_STOP(1)
// ���ǻ���: SignalMethod�� EMERGENCY_STOP(0)�� ����Ұ�� �������� ���õǸ� ������ �ӵ��� ���� �������ϰԵȴ�.
//           lDetectSignal�� PosEndLimit , NegEndLimit(0,1) �� ã����� ��ȣ�Ƿ��� Active ���¸� �����ϰԵȴ�.
function AxmMoveSignalSearch (lAxisNo : LongInt; dVel : Double; dAccel : Double; lDetectSignal : LongInt; lSignalEdge : LongInt; lSignalMethod : LongInt) : DWord; stdcall;    

// ���� �࿡�� ������ ��ȣ�� �����ϰ� �� ��ġ�� �����ϱ� ���� �̵��ϴ� �Լ��̴�.
// ���ϴ� ��ȣ�� ��� ã�� �����̴� �Լ� ã�� ��� �� ��ġ�� ������ѳ��� AxmGetCapturePos����Ͽ� �װ��� �д´�.
// Signal Edge   : ������ �Է� ��ȣ�� edge ���� ���� (rising or falling edge).
//                 SIGNAL_DOWN_EDGE(0), SIGNAL_UP_EDGE(1)
// ��������      : Vel���� ����̸� CW, �����̸� CCW.
// SignalMethod  : ������ EMERGENCY_STOP(0), �������� SLOWDOWN_STOP(1)
// lDetect Signal: edge ������ �Է� ��ȣ ����.SIGNAL_DOWN_EDGE(0), SIGNAL_UP_EDGE(1)
//                 ���� 8bit�� ���Ͽ� �⺻ ����(0), Software ����(1) �� ������ �� �ִ�. SMP Board(PCIe-Rxx05-MLIII) ����
// lDetectSignal : PosEndLimit(0), NegEndLimit(1), HomeSensor(4), EncodZPhase(5), UniInput02(6), UniInput03(7)
// lTarget       : COMMAND(0), ACTUAL(1)
// ���ǻ���: SignalMethod�� EMERGENCY_STOP(0)�� ����Ұ�� �������� ���õǸ� ������ �ӵ��� ���� �������ϰԵȴ�.
//           lDetectSignal�� PosEndLimit , NegEndLimit(0,1) �� ã����� ��ȣ�Ƿ��� Active ���¸� �����ϰԵȴ�.
function AxmMoveSignalCapture (lAxisNo : LongInt; dVel : Double; dAccel : Double; lDetectSignal : LongInt; lSignalEdge : LongInt; lTarget : LongInt; lSignalMethod : LongInt) : DWord; stdcall;
// 'AxmMoveSignalCapture' �Լ����� ����� ��ġ���� Ȯ���ϴ� �Լ��̴�.
// ���ǻ���: �Լ� ���� ����� "AXT_RT_SUCCESS"�϶� ����� ��ġ�� ��ȿ�ϸ�, �� �Լ��� �ѹ� �����ϸ� ���� ��ġ���� �ʱ�ȭ�ȴ�.
function AxmMoveGetCapturePos (lAxisNo : LongInt; dpCapPotition : PDouble) : DWord; stdcall;

// ������ �Ÿ���ŭ �Ǵ� ��ġ���� �̵��ϴ� �Լ�.
// �Լ��� �����ϸ� �ش� Motion ������ ������ �� Motion �� �Ϸ�ɶ����� ��ٸ��� �ʰ� �ٷ� �Լ��� ����������.
function AxmMoveStartMultiPos (lArraySize : LongInt; lpAxisNo : PLongInt; dpPos : PDouble; dpVel : PDouble; dpAccel : PDouble; dpDecel : PDouble) : DWord; stdcall;    

// ������ ������ �Ÿ���ŭ �Ǵ� ��ġ���� �̵��Ѵ�.
// ���� ����� ���� ��ǥ�� ������ ��ġ���� ������ �ӵ��� �������� ������ �Ѵ�.
function AxmMoveMultiPos (lArraySize : LongInt; lpAxisNo : PLongInt; dpPos : PDouble; dpVel : PDouble; dpAccel : PDouble; dpDecel : PDouble) : DWord; stdcall;

// ������ ��ũ �� �ӵ� ������ ���͸� �����Ѵ�.(PCIR-1604-MLII/SIIIH, PCIe-Rxx04-SIIIH  ���� �Լ�)
// dTroque        : �ִ� ��� ��ũ�� ���� %��.     
// ��������       : dTroque���� ����̸� CW, �����̸� CCW.
// dVel           : �ִ� ���� ���� �ӵ��� ���� %��.
// dwAccFilterSel : LINEAR_ACCDCEL(0), EXPO_ACCELDCEL(1), SCURVE_ACCELDECEL(2)
// dwGainSel      : GAIN_1ST(0), GAIN_2ND(1)
// dwSpdLoopSel   : PI_LOOP(0), P_LOOP(1)
function AxmMoveStartTorque(lAxisNo : LongInt; dTorque : Double; dVel : Double; dwAccFilterSel : DWord; dwGainSel : DWord; dwSpdLoopSel : DWord) : DWord; stdcall;

// ���� ���� ��ũ ������ ���� �Ѵ�.
// AxmMoveStartTorque�� �ݵ�� AxmMoveTorqueStop�� �����Ͽ��� �Ѵ�.
function AxmMoveTorqueStop(lAxisNo : LongInt; dwMethod : DWord) : DWord; stdcall;

// ������ �Ÿ���ŭ �Ǵ� ��ġ���� �̵��Ѵ�.
// ���� ���� ���� ��ǥ/�����ǥ�� ������ ��ġ���� ������ �ӵ�/�������� ������ �Ѵ�.
// �ӵ� ���������� ���Ī ��ٸ��÷� �����˴ϴ�.
// �����ӵ� ���� ������ ����� �����˴ϴ�.
// dAccel != 0.0 �̰� dDecel == 0.0 �� ��� ���� �ӵ����� ���� ���� ���� �ӵ����� ����.
// dAccel != 0.0 �̰� dDecel != 0.0 �� ��� ���� �ӵ����� ���� �ӵ����� ������ ��� ���� ����.
// dAccel == 0.0 �̰� dDecel != 0.0 �� ��� ���� �ӵ����� ���� �ӵ����� ����.

// ������ ������ �����Ͽ��� �մϴ�.
// dVel[1] == dVel[3]�� �ݵ�� �����Ͽ��� �Ѵ�.
// dVel[2]�� ���� ���� ������ �߻��� �� �ֵ��� dPosition�� ����� ū���̾�� �Ѵ�.
// Ex) dPosition = 10000;
// dVel[0] = 300., dAccel[0] = 200., dDecel[0] = 0.;    <== ����
// dVel[1] = 500., dAccel[1] = 100., dDecel[1] = 0.;    <== ����
// dVel[2] = 700., dAccel[2] = 200., dDecel[2] = 250.;  <== ����, ���, ����
// dVel[3] = 500., dAccel[3] = 0.,   dDecel[3] = 150.;  <== ����
// dVel[4] = 200., dAccel[4] = 0.,   dDecel[4] = 350.;  <== ����
// �޽� ����� ����Ǵ� �������� �Լ��� �����
function AxmMoveStartPosWithList(lAxisNo : LongInt; dPosition : Double; dpVel : PDouble; dpAccel : PDouble; dpDecel : PDouble; lListNum : LongInt) : DWord; stdcall;


// ������ �Ÿ���ŭ �Ǵ� ��ġ���� ��� ���� ��ġ�� ������ �� �̵��� �����Ѵ�.
// lEvnetAxisNo    : ���� ���� �߻� ��
// dComparePosition: ���� ���� �߻� ���� ���� �߻� ��ġ.
// uPositionSource : ���� ���� �߻� ���� ���� �߻� ��ġ ���� ���� => COMMAND(0), ACTUAL(1)
// ���� �� ��Ҵ� AxmMoveStop, AxmMoveEStop, AxmMoveSStop�� ���
// �̵� ��� ���� ���� �߻� ���� 4�� ���� �ϳ��� �׷�(2V04�� ��� ���� ���)�� �����Ͽ��� �մϴ�.
function AxmMoveStartPosWithPosEvent(lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDccel : Double; lEventAxisNo : LongInt; dComparePosition : Double; uPositionSource : DWord) : DWord; stdcall;

// ���� ���� ������ ���ӵ��� ���� ���� �Ѵ�.
// dDecel : ���� �� ��������
function AxmMoveStop (lAxisNo : LongInt; dDecel : Double) : DWord; stdcall;
// ���� ���� ������ ���ӵ��� ���� ���� �Ѵ�.(PCI-Nx04 ����)
// ���� ������ ���¿� ������� ��� ���� ���� �Լ��̸� ���ѵ� ������ ���Ͽ� ��� �����ϴ�.
// -- ��� ���� ���� : AxmMoveStartPos, AxmMoveVel, AxmLineMoveEx2.
// dDecel : ���� �� ��������
// ���� : ���������� ���� ���� ���������� ũ�ų� ���ƾ� �Ѵ�.
// ���� : ���� ������ �ð����� �Ͽ��� ��� ���� ���� ���� �ð����� �۰ų� ���ƾ� �Ѵ�.
function AxmMoveStopEx(lAxisNo : LongInt; dDecel : Double): DWord; stdcall;
// ���� ���� �� ���� �Ѵ�.
function AxmMoveEStop (lAxisNo : LongInt) : DWord; stdcall;
// ���� ���� ���� �����Ѵ�.
function AxmMoveSStop (lAxisNo : LongInt) : DWord; stdcall;

//========= �������̵� �Լ� ===========================================================================================
// ��ġ �������̵� �Ѵ�.
// ���� ���� ������ ����Ǳ� �� ������ ��� �޽� ���� �����Ѵ�.
// PCI-Nx04 �������ǻ��� : �������̵��� ��ġ�� �������� ���� ������ ��ġ�� ���������� Relative ������ ��ġ������ �־��ش�.
//                           ���������� ���������� ��� �������̵带 ����Ҽ������� �ݴ�������� �������̵��Ұ�쿡�� �������̵带 ����Ҽ�����.
function AxmOverridePos (lAxisNo : LongInt; dOverridePos : Double) : DWord; stdcall;

// ���� ���� �ӵ��������̵� �ϱ����� �������̵��� �ְ�ӵ��� �����Ѵ�.
// ������ : �ӵ��������̵带 5���Ѵٸ� ���߿� �ְ� �ӵ��� �����ؾߵȴ�. 
function AxmOverrideSetMaxVel (lAxisNo : LongInt; dOverrideMaxVel : Double) : DWord; stdcall;    
// �ӵ� �������̵� �Ѵ�.
// ���� ���� ���� �߿� �ӵ��� ���� �����Ѵ�. (�ݵ�� ��� �߿� ���� �����Ѵ�.)
// ������: AxmOverrideVel �Լ��� ����ϱ�����. AxmOverrideMaxVel �ְ�� �����Ҽ��ִ� �ӵ��� �����س��´�.
// EX> �ӵ��������̵带 �ι��Ѵٸ� 
// 1. �ΰ��߿� ���� �ӵ��� AxmOverrideMaxVel ���� �ְ� �ӵ��� ����.
// 2. AxmMoveStartPos ���� ���� ���� ���� ��(Move�Լ� ��� ����)�� �ӵ��� ù��° �ӵ��� AxmOverrideVel ���� �����Ѵ�.
// 3. ���� ���� ���� ��(Move�Լ� ��� ����)�� �ӵ��� �ι�° �ӵ��� AxmOverrideVel ���� �����Ѵ�.
function AxmOverrideVel (lAxisNo : LongInt; dOverrideVel : Double) : DWord; stdcall;    
// ���ӵ�, �ӵ�, ���ӵ���  �������̵� �Ѵ�.
// ���� ���� ���� �߿� ���ӵ�, �ӵ�, ���ӵ��� ���� �����Ѵ�. (�ݵ�� ��� �߿� ���� �����Ѵ�.)
// ������: AxmOverrideAccelVelDecel �Լ��� ����ϱ�����. AxmOverrideMaxVel �ְ�� �����Ҽ��ִ� �ӵ��� �����س��´�.
// EX> �ӵ��������̵带 �ι��Ѵٸ� 
// 1. �ΰ��߿� ���� �ӵ��� AxmOverrideMaxVel ���� �ְ� �ӵ��� ����.
// 2. AxmMoveStartPos ���� ���� ���� ���� ��(Move�Լ� ��� ����)�� ���ӵ�, �ӵ�, ���ӵ��� ù��° �ӵ��� AxmOverrideAccelVelDecel ���� �����Ѵ�.
// 3. ���� ���� ���� ��(Move�Լ� ��� ����)�� ���ӵ�, �ӵ�, ���ӵ��� �ι�° �ӵ��� AxmOverrideAccelVelDecel ���� �����Ѵ�.
function AxmOverrideAccelVelDecel (lAxisNo : LongInt; dOverrideVel : Double; dMaxAccel : Double; dMaxDecel : Double) : DWord; stdcall;
// ��� �������� �ӵ� �������̵� �Ѵ�.
// ��� ��ġ ������ �������̵��� �ӵ��� �Է½��� ����ġ���� �ӵ��������̵� �Ǵ� �Լ�
// lTarget : COMMAND(0), ACTUAL(1)
// ������: AxmOverrideVelAtPos �Լ��� ����ϱ�����. AxmOverrideMaxVel �ְ�� �����Ҽ��ִ� �ӵ��� �����س��´�.
function AxmOverrideVelAtPos (lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double; dOverridePos : Double; dOverrideVel : Double; lTarget : LongInt) : DWord; stdcall;    
// ������ �����鿡�� ������ �ӵ��� �������̵� �Ѵ�.
// lArraySize     : �������̵� �� ��ġ�� ������ ����.
// *dpOverridePos : �������̵� �� ��ġ�� �迭(lArraySize���� ������ �������� ���ų� ũ�� �����ؾߵ�)
// *dpOverrideVel : �������̵� �� ��ġ���� ���� �� �ӵ� �迭(lArraySize���� ������ �������� ���ų� ũ�� �����ؾߵ�)
// lTarget        : COMMAND(0), ACTUAL(1) 
// uOverrideMode  : �������̵� ���� ����� ������.
//                : OVERRIDE_POS_START(0) ������ ��ġ���� ������ �ӵ��� �������̵� ������        
//                : OVERRIDE_POS_END(1) ������ ��ġ���� ������ �ӵ��� �ǵ��� �̸� �������̵� ������
function AxmOverrideVelAtMultiPos (lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double; lArraySize : LongInt; dpOverridePos : PDouble; dpOverrideVel : PDouble; lTarget : LongInt; uOverrideMode : DWord) : DWord; stdcall;

// ������ �����鿡�� ������ �ӵ�/�����ӵ��� �������̵� �Ѵ�.(MLII ����)
// lArraySize     : �������̵� �� ��ġ�� ������ ����(�ִ� 5).
// *dpOverridePos : �������̵� �� ��ġ�� �迭(lArraySize���� ������ �������� ���ų� ũ�� �����ؾߵ�)
// *dpOverrideVel : �������̵� �� ��ġ���� ���� �� �ӵ� �迭(lArraySize���� ������ �������� ���ų� ũ�� �����ؾߵ�)
// *dpOverrideAccelDecel : �������̵� �� ��ġ���� ���� �� �����ӵ� �迭(lArraySize���� ������ �������� ���ų� ũ�� �����ؾߵ�)
// lTarget        : COMMAND(0), ACTUAL(1) 
// dwOverrideMode : �������̵� ���� ����� ������.
//                : OVERRIDE_POS_START(0) ������ ��ġ���� ������ �ӵ��� �������̵� ������  
//                : OVERRIDE_POS_END(1) ������ ��ġ���� ������ �ӵ��� �ǵ��� �̸� �������̵� ������
function AxmOverrideVelAtMultiPos2 (lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double; lArraySize : LongInt; dpOverridePos : PDouble; dpOverrideVel : PDouble; lTarget : LongInt; uOverrideMode : DWord) : DWord; stdcall;

//========= ������, �����̺�  ����� ���� �Լ� ======================================================================
// Electric Gear ��忡�� Master ��� Slave ����� ���� �����Ѵ�.
// dSlaveRatio : �������࿡ ���� �����̺��� ����( 0 : 0% , 0.5 : 50%, 1 : 100%)
function AxmLinkSetMode (lMasterAxisNo : LongInt; lSlaveAxisNo : LongInt; dSlaveRatio : Double) : DWord; stdcall;
// Electric Gear ��忡�� ������ Master ��� Slave ����� ���� ��ȯ�Ѵ�.
function AxmLinkGetMode (lMasterAxisNo : LongInt; lpSlaveAxisNo : PLongInt; dpGearRatio : PDouble) : DWord; stdcall;
// Master ��� Slave�ణ�� ���ڱ��� ���� ���� �Ѵ�.
function AxmLinkResetMode (lMasterAxisNo : LongInt) : DWord; stdcall;

//======== ��Ʈ�� ���� �Լ�============================================================================================
// ��Ǹ���� �� ���� �ⱸ������ Link�Ǿ��ִ� ��Ʈ�� �����ý��� ��� �����Ѵ�. 
// �� �Լ��� �̿��� Master���� ��Ʈ�� ����� �����ϸ� �ش� Slave���� Master��� ����Ǿ� �����˴ϴ�. 
// ���� ��Ʈ�� ���� ���� Slave�࿡ ��������̳� ���� ��ɵ��� ������ ��� ���õ˴ϴ�.
// uSlHomeUse     : �������� Ȩ��� ��� ( 0 - 2)
//             (0 : �����̺��� Ȩ�� �����ϰ� ���������� Ȩ�� ã�´�.)
//             (1 : �������� , �����̺��� Ȩ�� ã�´�. �����̺� dSlOffset �� �����ؼ� ������.)
//             (2 : �������� , �����̺��� Ȩ�� ã�´�. �����̺� dSlOffset �� �����ؼ� ��������.)
// dSlOffset      : �����̺��� �ɼ°�
// dSlOffsetRange : �����̺��� �ɼ°� ������ ����
// ���ǻ���       : ��Ʈ�� ENABLE�� �����̺����� ����� AxmStatusReadMotion �Լ��� Ȯ���ϸ� True(Motion ���� ��)�� Ȯ�εǾ� �������̴�. 
//                  �����̺��࿡ AxmStatusReadMotion�� Ȯ�������� InMotion �� False�̸� Gantry Enable�� �ȵȰ��̹Ƿ� �˶� Ȥ�� ����Ʈ ���� ���� Ȯ���Ѵ�.
function AxmGantrySetEnable (lMasterAxisNo : LongInt; lSlaveAxisNo : LongInt; uSlHomeUse : DWord; dSlOffset : Double; dSlOffsetRange : Double) : DWord; stdcall;

// Slave���� Offset���� �˾Ƴ��¹��.
// A. ������, �����̺긦 �ΰ��� �������� ��Ų��.         
// B. AxmGantrySetEnable�Լ����� uSlHomeUse = 2�� ������ AxmHomeSetStart�Լ��� �̿��ؼ� Ȩ�� ã�´�. 
// C. Ȩ�� ã�� ���� ���������� Command���� �о�� ��������� �����̺����� Ʋ���� Offset���� �����ִ�.
// D. Offset���� �о AxmGantrySetEnable�Լ��� dSlOffset���ڿ� �־��ش�. 
// E. dSlOffset���� �־��ٶ� �������࿡ ���� �����̺� �� ���̱⶧���� ��ȣ�� �ݴ�� -dSlOffset �־��ش�.
// F. dSIOffsetRange �� Slave Offset�� Range ������ ���ϴµ� Range�� �Ѱ踦 �����Ͽ� �Ѱ踦 ����� ������ �߻���ų�� ����Ѵ�.        
// G. AxmGantrySetEnable�Լ��� Offset���� �־�������  AxmGantrySetEnable�Լ����� uSlHomeUse = 1�� ������ AxmHomeSetStart�Լ��� �̿��ؼ� Ȩ�� ã�´�.         

// ��Ʈ�� ������ �־� ����ڰ� ������ �Ķ��Ÿ�� ��ȯ�Ѵ�.
function AxmGantryGetEnable (lMasterAxisNo : LongInt; upSlHomeUse : PDWord; dpSlOffset : PDouble; dpSlORange : PDouble; upGatryOn : PDWord) : DWord; stdcall;
// ��� ����� �� ���� �ⱸ������ Link�Ǿ��ִ� ��Ʈ�� �����ý��� ��� �����Ѵ�.
function AxmGantrySetDisable (lMasterAxisNo : LongInt; lSlaveAxisNo : LongInt) : DWord; stdcall;

// PCI-Rxx04-MLII ����.
// ��� ����� �� ���� �ⱸ������ Link�Ǿ��ִ� ��Ʈ�� �����ý��� ���� �� ���� ���� ����� �����Ѵ�.
// lMasterGain, lSlaveGain : �� �ణ ��ġ ������ ���� ���� �� �ݿ� ������ % ������ �Է��Ѵ�.
// lMasterGain, lSlaveGain : 0�� �Է��ϸ� �� �ణ ��ġ ���� ���� ����� ������� ����. �⺻�� : 0%
function AxmGantrySetCompensationGain (lMasterAxisNo : LongInt; lMasterGain : LongInt; lSlaveGain : LongInt) : DWord; stdcall;
// ��� ����� �� ���� �ⱸ������ Link�Ǿ��ִ� ��Ʈ�� �����ý��� ���� �� ���� ���� ����� ������ Ȯ���Ѵ�.
function AxmGantryGetCompensationGain (lMasterAxisNo : LongInt; lpMasterGain : PLongInt; lpSlaveGain : PLongInt) : DWord; stdcall;

// Master �� Slave �� ��ġ���� ������ ���� �ϰ� ��ġ�������� �̻��̸� Read �Լ��� Status�� TRUE�� ��ȯ �Ѵ�.
// PCI-R1604 / PCI-R3200-MLIII ���� �Լ�
// lMasterAxisNo : Gantry Master Axis No
// dErrorRange : ��ġ���� ���� ���� ��
// uUse : ��� ����
//      ( 0 : Disable)
//      ( 1 : Normal ���)
//      ( 2 : Flag Latch ���)
//      ( 3 : Flag Latch ��� + Error �߻��� SSTOP)
//      ( 4 : Flag Latch ��� + Error �߻��� ESTOP)
function AxmGantrySetErrorRange(lMasterAxisNo : LongInt; dErrorRange : Double; uUse : DWord) : DWord; stdcall;
// Master �� Slave ���� ��ġ���� ���� �������� ��ȯ�Ѵ�.
function AxmGantryGetErrorRange(lMasterAxisNo : LongInt; dpErrorRange : PDouble; upUse : PDWord) : DWord; stdcall;
// Master �� Slave ���� ��ġ������ �� ����� ��ȯ �Ѵ�.
// dwpStatus : FALSE(0) -> Master �� Slave ������ ��ġ������ ������ ������ ���� ���� �۴�. (�������)
//             TRUE(1) -> Master �� Slave ������ ��ġ������ ������ ������ ���� ���� ũ��. (���������)
// Gantry Enable && Master/Slave Servo On ���¸� ���� �� ���� AXT_RT_SUCCESS�� Return �Ѵ�.
// Latch ����� ��� AxmGantryReadErrorRangeComparePos�� ȣ�� �ؾ� Latch Flag�� Reset �ȴ�.
function AxmGantryReadErrorRangeStatus(lMasterAxisNo : LongInt; dwpStatus : PDWord) : DWord; stdcall;
// Master �� Slave ���� ��ġ�������� ��ȯ �Ѵ�.
// Flag Latch ��� �϶� ���� Error�� �߻� �Ǳ� ������ ���� Error�� �߻� ���� ���� ��ġ�������� ���� �Ѵ�.
// dwpStatus �� 1�� ���� Read �ؾ� �Ѵ�. ��� ComparePos �� Read �ϸ� ���ϰ� ���� �ɷ� �Լ� ����ӵ��� �������� �ȴ�.
function AxmGantryReadErrorRangeComparePos(lMasterAxisNo : LongInt; dpComparePos : PDouble) : DWord; stdcall;

//====�Ϲ� �����Լ� ===================================================================================================
// ���ǻ���1: AxmContiSetAxisMap�Լ��� �̿��Ͽ� ������Ŀ� ������������� ������ �ϸ鼭 ����ؾߵȴ�.
//           ��ȣ������ ��쿡�� �ݵ�� ������������� ��迭�� �־�� ���� �����ϴ�.
    
// ���ǻ���2: ��ġ�� �����Ұ�� �ݵ�� ��������� �����̺� ���� UNIT/PULSE�� ���߾ �����Ѵ�.
//           ��ġ�� UNIT/PULSE ���� �۰� ������ ��� �ּҴ����� UNIT/PULSE�� ���߾����⶧���� ����ġ���� ������ �ɼ�����.

// ���ǻ���3: ��ȣ ������ �Ұ�� �ݵ�� ��Ĩ������ ������ �ɼ������Ƿ� 
//            4�೻������ �����ؼ� ����ؾߵȴ�.

// ���ǻ���4: ���� ���� ����/�߿� ������ ���� ����(+- Limit��ȣ, ���� �˶�, ������� ��)�� �߻��ϸ� 
//            ���� ���⿡ ������� ������ �������� �ʰų� ���� �ȴ�.

// ���� ���� �Ѵ�.
// �������� �������� �����Ͽ� ���� ���� ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
// AxmContiBeginNode, AxmContiEndNode�� ���̻��� ������ ��ǥ�迡 �������� �������� �����Ͽ� ���� ���� �����ϴ� Queue�� �����Լ����ȴ�. 
// ���� �������� ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmContiStart�Լ��� ����ؼ� �����Ѵ�.
function AxmLineMove (lCoord : LongInt; dpEndPos : PDouble; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;

// 2�� ���� ���� ���� �Ѵ�.(Software ���)
// �������� �������� �����Ͽ� ���� ���� ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
function AxmLineMoveEx2(lCoord : LongInt; dpEndPos : PDouble; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;

// 2�� ��ȣ���� �Ѵ�.
// ������, �������� �߽����� �����Ͽ� ��ȣ ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
// AxmContiBeginNode, AxmContiEndNode, �� ���̻��� ������ ��ǥ�迡 ������, �������� �߽����� �����Ͽ� �����ϴ� ��ȣ ���� Queue�� �����Լ����ȴ�.
// �������� ��ȣ ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmContiStart�Լ��� ����ؼ� �����Ѵ�.
// lAxisNo = ���� �迭 , dCenterPos = �߽��� X,Y �迭 , dEndPos = ������ X,Y �迭.
// uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
function AxmCircleCenterMove (lCoord : LongInt; lAxisNo : PLongInt; dCenterPos : PDouble; dEndPos : PDouble; dVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord) : DWord; stdcall;

// �߰���, �������� �����Ͽ� ��ȣ ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
// AxmContiBeginNode, AxmContiEndNode�� ���̻��� ������ ��ǥ�迡 �߰���, �������� �����Ͽ� �����ϴ� ��ȣ ���� Queue�� �����Լ����ȴ�.
// �������� ��ȣ ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmContiStart�Լ��� ����ؼ� �����Ѵ�.
// lAxisNo = ���� �迭 , dMidPos = �߰��� X,Y �迭 , dEndPos = ������ X,Y �迭, lArcCircle = ��ũ(0), ��(1)
function AxmCirclePointMove (lCoord : LongInt; lAxisNo : PLongInt; dMidPos : PDouble; dEndPos : PDouble; dVel : Double; dAccel : Double; dDecel : Double; lArcCircle : LongInt) : DWord; stdcall;

// ������, �������� �������� �����Ͽ� ��ȣ ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
// AxmContiBeginNode, AxmContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, �������� �������� �����Ͽ� ��ȣ ���� �����ϴ� Queue�� �����Լ����ȴ�.
// �������� ��ȣ ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmContiStart�Լ��� ����ؼ� �����Ѵ�.
// lAxisNo = ���� �迭 , dRadius = ������, dEndPos = ������ X,Y �迭 , uShortDistance = ������(0), ū��(1)
// uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
function AxmCircleRadiusMove (lCoord : LongInt; lAxisNo : PLongInt; dRadius : Double; dEndPos : PDouble; dVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord; uShortDistance : DWord) : DWord; stdcall;

// ������, ȸ�������� �������� �����Ͽ� ��ȣ ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
// AxmContiBeginNode, AxmContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, ȸ�������� �������� �����Ͽ� ��ȣ ���� �����ϴ� Queue�� �����Լ����ȴ�.
// �������� ��ȣ ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmContiStart�Լ��� ����ؼ� �����Ѵ�.
// lAxisNo = ���� �迭 , dCenterPos = �߽��� X,Y �迭 , dAngle = ����.
// uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
function AxmCircleAngleMove (lCoord : LongInt; lAxisNo : PLongInt; dCenterPos : PDouble; dAngle : Double; dVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord) : DWord; stdcall;

//====���� ���� �Լ� ==================================================================================================
// ������ ��ǥ�迡 ���Ӻ��� �� ������ �����Ѵ�.
// (����� ��ȣ�� 0 ���� ����))
// ������: ������Ҷ��� �ݵ�� ���� ���ȣ�� ���� ���ں��� ū���ڸ� �ִ´�.
//         ������ ���� �Լ��� ����Ͽ��� �� �������ȣ�� ���� ���ȣ�� ���� �� ���� lpAxesNo�� ���� ���ؽ��� �Է��Ͽ��� �Ѵ�.
//         ������ ���� �Լ��� ����Ͽ��� �� �������ȣ�� �ش��ϴ� ���� ���ȣ�� �ٸ� ���̶�� �Ѵ�.
//         ���� ���� �ٸ� Coordinate�� �ߺ� �������� ���ƾ� �Ѵ�.
function AxmContiSetAxisMap (lCoord : LongInt; lSize : LongInt; lpRealAxesNo : PLongInt) : DWord; stdcall;
//������ ��ǥ�迡 ���Ӻ��� �� ������ ��ȯ�Ѵ�.
function AxmContiGetAxisMap (lCoord : LongInt; lpSize : PLongInt; lpRealAxesNo : PLongInt) : DWord; stdcall;    
    
// ������ ��ǥ�迡 ���Ӻ��� �� ����/��� ��带 �����Ѵ�.
// (������ : �ݵ�� ����� �ϰ� ��밡��)
// ���� ���� �̵� �Ÿ� ��� ��带 �����Ѵ�.
// uAbsRelMode : POS_ABS_MODE '0' - ���� ��ǥ��
//               POS_REL_MODE '1' - ��� ��ǥ��
function AxmContiSetAbsRelMode (lCoord : LongInt; uAbsRelMode : DWord) : DWord; stdcall;
// ������ ��ǥ�迡 ���Ӻ��� �� ����/��� ��带 ��ȯ�Ѵ�.
function AxmContiGetAbsRelMode (lCoord : LongInt; upAbsRelMode : PDWord) : DWord; stdcall;

// ������ ��ǥ�迡 ���� ������ ���� ���� Queue�� ��� �ִ��� Ȯ���ϴ� �Լ��̴�.
function AxmContiReadFree (lCoord : LongInt; upQueueFree : PDWord) : DWord; stdcall;
// ������ ��ǥ�迡 ���� ������ ���� ���� Queue�� ����Ǿ� �ִ� ���� ���� ������ Ȯ���ϴ� �Լ��̴�.
function AxmContiReadIndex (lCoord : LongInt; lpQueueIndex : PLongInt) : DWord; stdcall;

// ������ ��ǥ�迡 ���� ���� ������ ���� ����� ���� Queue�� ��� �����ϴ� �Լ��̴�.
function AxmContiWriteClear (lCoord : LongInt) : DWord; stdcall;

// ������ ��ǥ�迡 ���Ӻ������� ������ �۾����� ����� �����Ѵ�. ���Լ��� ȣ������,
// AxmContiEndNode�Լ��� ȣ��Ǳ� ������ ����Ǵ� ��� ����۾��� ���� ����� �����ϴ� ���� �ƴ϶� ���Ӻ��� ������� ��� �Ǵ� ���̸�,
// AxmContiStart �Լ��� ȣ��� �� ��μ� ��ϵȸ���� ������ ����ȴ�.
function AxmContiBeginNode (lCoord : LongInt) : DWord; stdcall;
// ������ ��ǥ�迡�� ���Ӻ����� ������ �۾����� ����� �����Ѵ�.
function AxmContiEndNode (lCoord : LongInt) : DWord; stdcall;

// ���� ���� ���� �Ѵ�.
// dwProfileset(CONTI_NODE_VELOCITY(0) : ���� ���� ���, CONTI_NODE_MANUAL(1) : �������� ���� ���, CONTI_NODE_AUTO(2) : �ڵ� �������� ����, 3 : �ӵ����� ��� ���) 
function AxmContiStart (lCoord : LongInt; dwProfileset : DWord; lAngle : LongInt) : DWord; stdcall;
// ������ ��ǥ�迡 ���� ���� ���� ������ Ȯ���ϴ� �Լ��̴�.
function AxmContiIsMotion (lCoord : LongInt; upInMotion : PDWord) : DWord; stdcall;

// ������ ��ǥ�迡 ���� ���� ���� �� ���� �������� ���� ���� �ε��� ��ȣ�� Ȯ���ϴ� �Լ��̴�.
function AxmContiGetNodeNum (lCoord : LongInt; lpNodeNum : PLongInt) : DWord; stdcall;
// ������ ��ǥ�迡 ������ ���� ���� ���� �� �ε��� ������ Ȯ���ϴ� �Լ��̴�.
function AxmContiGetTotalNodeNum (lCoord : LongInt; lpNodeNum : PLongInt) : DWord; stdcall;

//====================Ʈ���� �Լ� =====================================================================================
// ���ǻ���: Ʈ���� ��ġ�� �����Ұ�� �ݵ�� UNIT/PULSE�� ���߾ �����Ѵ�.
//           ��ġ�� UNIT/PULSE ���� �۰��� ��� �ּҴ����� UNIT/PULSE�� ���߾����⶧���� ����ġ�� ����Ҽ�����.

// ���� �࿡ Ʈ���� ����� ��� ����, ��� ����, ��ġ �񱳱�, Ʈ���� ��ȣ ���� �ð� �� Ʈ���� ��� ��带 �����Ѵ�.
// Ʈ���� ��� ����� ���ؼ��� ����  AxmTriggerSetTimeLevel �� ����Ͽ� ���� ��� ������ ���� �Ͽ��� �Ѵ�.
// dTrigTime  : Ʈ���� ��� �ð�, 1usec - �ִ� 50msec ( 1 - 50000 ���� ����)
// upTriggerLevel  : Ʈ���� ��� ���� ����  => LOW(0), HIGH(1)
// uSelect         : ����� ���� ��ġ       => COMMAND(0), ACTUAL(1)
// uInterrupt      : ���ͷ�Ʈ ����          => DISABLE(0), ENABLE(1)

// ���� �࿡ Ʈ���� ��ȣ ���� �ð� �� Ʈ���� ��� ����, Ʈ���� ��¹���� �����Ѵ�.
function AxmTriggerSetTimeLevel (lAxisNo : LongInt; dTrigTime : Double; uTriggerLevel : DWord; uSelect : DWord; uInterrupt : DWord) : DWord; stdcall;
// ���� �࿡ Ʈ���� ��ȣ ���� �ð� �� Ʈ���� ��� ����, Ʈ���� ��¹���� ��ȯ�Ѵ�.
function AxmTriggerGetTimeLevel (lAxisNo : LongInt; dpTrigTime : PDouble; upTriggerLevel : PDWord; upSelect : PDWord; upInterrupt : PDWord) : DWord; stdcall;    

// ���� ���� Ʈ���� ��� ����� �����Ѵ�.
// uMethod : PERIOD_MODE      0x0 : ���� ��ġ�� �������� dPos�� ��ġ �ֱ�� ����� �ֱ� Ʈ���� ���
//           ABS_POS_MODE     0x1 : Ʈ���� ���� ��ġ���� Ʈ���� �߻�, ���� ��ġ ���
// dPos : �ֱ� ���ý� : ��ġ������ġ���� ����ϱ⶧���� �� ��ġ
//        ���� ���ý� : ����� �� ��ġ, �� ��ġ�Ͱ����� ������ ����� ������. 
// ���ǻ���: AxmTriggerSetAbsPeriod�� �ֱ���� �����Ұ�� ó�� ����ġ�� ���� �ȿ� �����Ƿ� Ʈ���� ����� �ѹ� �߻��Ѵ�.
function AxmTriggerSetAbsPeriod (lAxisNo : LongInt; uMethod : DWord; dPos : Double) : DWord; stdcall;
// ���� �࿡ Ʈ���� ����� ��� ����, ��� ����, ��ġ �񱳱�, Ʈ���� ��ȣ ���� �ð� �� Ʈ���� ��� ��带 ��ȯ�Ѵ�.
function AxmTriggerGetAbsPeriod (lAxisNo : LongInt; upMethod : PDWord; dpPos : PDouble) : DWord; stdcall;

// ����ڰ� ������ ������ġ���� ������ġ���� ������������ Ʈ���Ÿ� ��� �Ѵ�.
function AxmTriggerSetBlock (lAxisNo : LongInt; dStartPos : Double; dEndPos : Double; dPeriodPos : Double) : DWord; stdcall;
// 'AxmTriggerSetBlock' �Լ��� Ʈ���� ������ ���� �д´�..
function AxmTriggerGetBlock (lAxisNo : LongInt; dpStartPos : PDouble; dpEndPos : PDouble; dpPeriodPos : PDouble) : DWord; stdcall;

// ����ڰ� �� ���� Ʈ���� �޽��� ����Ѵ�.
function AxmTriggerOneShot (lAxisNo : LongInt) : DWord; stdcall;
// ����ڰ� �� ���� Ʈ���� �޽��� �����Ŀ� ����Ѵ�.
function AxmTriggerSetTimerOneshot (lAxisNo : LongInt; lmSec : LongInt) : DWord; stdcall;
// ������ġ Ʈ���� ���Ѵ� ������ġ ����Ѵ�.
function AxmTriggerOnlyAbs (lAxisNo : LongInt; lTrigNum : LongInt; dpTrigPos : PDouble) : DWord; stdcall;
// Ʈ���� ������ �����Ѵ�.
function AxmTriggerSetReset (lAxisNo : LongInt) : DWord; stdcall;

//======== CRC( �ܿ� �޽� Ŭ���� �Լ�)=================================================================================
// Level   : LOW(0), HIGH(1), UNUSED(2), USED(3)
// uMethod : �ܿ��޽� ���� ��� ��ȣ �޽� �� 0 - 7���� ��������.
//           0 : 30 uSec , 1 : 100 uSec, 2: 500 uSec, 3:1 mSec, 4:10 mSec, 5:50 mSec, 6:100 mSec
//���� �࿡ CRC ��ȣ ��� ���� �� ��� ������ �����Ѵ�.
function AxmCrcSetMaskLevel (lAxisNo : LongInt; uLevel : Dword; lMethod : Dword) : DWord; stdcall;
// ���� ���� CRC ��ȣ ��� ���� �� ��� ������ ��ȯ�Ѵ�.
function AxmCrcGetMaskLevel (lAxisNo : LongInt; upLevel : PDWord; upMethod : PDword) : DWord; stdcall;

//uOnOff  : CRC ��ȣ�� Program���� �߻� ����  (FALSE(0),TRUE(1))
// ���� �࿡ CRC ��ȣ�� ������ �߻� ��Ų��.
function AxmCrcSetOutput (lAxisNo : LongInt; uOnOff : DWord) : DWord; stdcall;
// ���� ���� CRC ��ȣ�� ������ �߻� ���θ� ��ȯ�Ѵ�.
function AxmCrcGetOutput (lAxisNo : LongInt; upOnOff : PDWord) : DWord; stdcall;    

//======MPG(Manual Pulse Generation) �Լ�==============================================================================
// lInputMethod : 0-3 ���� ��������. 0:OnePhase, 1:��� ���� , 2:TwoPhase2, 3:TwoPhase4
// lDriveMode   : 0�� ��������(0 :MPG ���Ӹ��)
// MPGPos       : MPG �Է½�ȣ���� �̵��ϴ� �Ÿ�
// MPGdenominator: MPG(���� �޽� �߻� ��ġ �Է�)���� �� ������ ��
// dMPGnumerator : MPG(���� �޽� �߻� ��ġ �Է�)���� �� ���ϱ� ��
// dwNumerator   : �ִ�(1 ����    64) ���� ���� ����
// dwDenominator : �ִ�(1 ����  4096) ���� ���� ����
// dMPGdenominator = 4096, MPGnumerator=1 �� �ǹ��ϴ� ���� 
// MPG �ѹ����� 200�޽��� �״�� 1:1�� 1�޽��� ����� �ǹ��Ѵ�. 
// ���� dMPGdenominator = 4096, MPGnumerator=2 �� �������� 1:2�� 2�޽��� ����� �������ٴ��ǹ��̴�. 
// ���⿡ MPG PULSE = ((Numerator) * (Denominator)/ 4096 ) Ĩ���ο� ��³����� �����̴�.
// ���ǻ���     : AxmStatusReadInMotion �Լ� ���� ����� �����Ѵ�.  (AxmMPGReset �ϱ� ������ ���� ���¿����� ��� ���� �� ����.)

// ���� �࿡ MPG �Է¹��, ����̺� ���� ���, �̵� �Ÿ�, MPG �ӵ� ���� �����Ѵ�.
function AxmMPGSetEnable (lAxisNo : LongInt; lInputMethod : LongInt; lDriveMode : LongInt; dMPGPos : Double; dVel : Double; dAcc : Double) : DWord; stdcall;
// ���� �࿡ MPG �Է¹��, ����̺� ���� ���, �̵� �Ÿ�, MPG �ӵ� ���� ��ȯ�Ѵ�.
function AxmMPGGetEnable (lAxisNo : LongInt; lpInputMethod : PLongInt; lpDriveMode : PLongInt; dpMPGPos : PDouble; dpVel : PDouble) : DWord; stdcall;

// PCI-Nx04 �Լ� ����.
// ���� �࿡ MPG ����̺� ���� ��忡�� ���޽��� �̵��� �޽� ������ �����Ѵ�.
function AxmMPGSetRatio (lAxisNo : LongInt; dMPGnumerator : Double; dMPGdenominator : Double) : DWord; stdcall;
// ���� �࿡ MPG ����̺� ���� ��忡�� ���޽��� �̵��� �޽� ������ ��ȯ�Ѵ�.
function AxmMPGGetRatio (lAxisNo : LongInt; dpMPGnumerator : PDouble; dpMPGdenominator : PDouble) : DWord; stdcall;
// ���� �࿡ MPG ����̺� ������ �����Ѵ�.
function AxmMPGReset (lAxisNo : LongInt) : DWord; stdcall;    

//======= �︮�� �̵� =================================================================================================
// ���ǻ��� : Helix�� ���Ӻ��� ���� Spline, ���������� ��ȣ������ ���� ����Ҽ�����.

// ������ ��ǥ�迡 ������, �������� �߽����� �����Ͽ� �︮�� ���� �����ϴ� �Լ��̴�.
// AxmContiBeginNode, AxmContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, �������� �߽����� �����Ͽ� �︮�� ���Ӻ��� �����ϴ� �Լ��̴�. 
// ��ȣ ���� ���� ������ ���� ���� Queue�� �����ϴ� �Լ��̴�. AxmContiStart�Լ��� ����ؼ� �����Ѵ�. (���Ӻ��� �Լ��� ���� �̿��Ѵ�)
// dCenterPos = �߽��� X,Y  , dEndPos = ������ X,Y .
// uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
function AxmHelixCenterMove (lCoord : LongInt; dCenterXPos : Double; dCenterYPos : Double; dEndXPos : Double; dEndYPos : Double; dZPos : Double; dVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord) : DWord; stdcall;

// ������ ��ǥ�迡 ������, �������� �������� �����Ͽ� �︮�� ���� �����ϴ� �Լ��̴�. 
// AxmContiBeginNode, AxmContiEndNode�� ���̻��� ������ ��ǥ�迡 �߰���, �������� �����Ͽ� �︮�ÿ��� ���� �����ϴ� �Լ��̴�. 
// ��ȣ ���� ���� ������ ���� ���� Queue�� �����ϴ� �Լ��̴�. AxmContiStart�Լ��� ����ؼ� �����Ѵ�. (���Ӻ��� �Լ��� ���� �̿��Ѵ�.)
// dMidPos = �߰��� X,Y  , dEndPos = ������ X,Y 
function AxmHelixPointMove (lCoord : LongInt; dMidXPos : Double; dMidYPos : Double; dEndXPos : Double; dEndYPos : Double; dZPos : Double; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;

// ������ ��ǥ�迡 ������, �������� �������� �����Ͽ� �︮�� ���� �����ϴ� �Լ��̴�.
// AxmContiBeginNode, AxmContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, �������� �������� �����Ͽ� �︮�ÿ��� ���� �����ϴ� �Լ��̴�. 
// ��ȣ ���� ���� ������ ���� ���� Queue�� �����ϴ� �Լ��̴�. AxmContiStart�Լ��� ����ؼ� �����Ѵ�. (���Ӻ��� �Լ��� ���� �̿��Ѵ�.)
// dRadius = ������, dEndPos = ������ X,Y  , uShortDistance = ������(0), ū��(1)
// uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
function AxmHelixRadiusMove (lCoord : LongInt; dRadius : Double; dEndXPos : Double; dEndYPos : Double; dZPos : Double; dVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord; uShortDistance : DWord) : DWord; stdcall;

// ������ ��ǥ�迡 ������, ȸ�������� �������� �����Ͽ� �︮�� ���� �����ϴ� �Լ��̴�
// AxmContiBeginNode, AxmContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, ȸ�������� �������� �����Ͽ� �︮�ÿ��� ���� �����ϴ� �Լ��̴�. 
// ��ȣ ���� ���� ������ ���� ���� Queue�� �����ϴ� �Լ��̴�. AxmContiStart�Լ��� ����ؼ� �����Ѵ�. (���Ӻ��� �Լ��� ���� �̿��Ѵ�.)
//dCenterPos = �߽��� X,Y  , dAngle = ����.
// uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
function AxmHelixAngleMove (lCoord : LongInt; dCenterXPos : Double; dCenterYPos : Double; dAngle : Double; dZPos : Double; dVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord) : DWord; stdcall;

//======== ���ö��� �̵� ==============================================================================================
// ���ǻ��� : Spline�� ���Ӻ��� ���� Helix , ���������� ��ȣ������ ���� ����Ҽ�����.

// AxmContiBeginNode, AxmContiEndNode�� ���̻�����. 
// ���ö��� ���� ���� �����ϴ� �Լ��̴�. ��ȣ ���� ���� ������ ���� ���� Queue�� �����ϴ� �Լ��̴�.
// AxmContiStart�Լ��� ����ؼ� �����Ѵ�. (���Ӻ��� �Լ��� ���� �̿��Ѵ�.)    
// lPosSize : �ּ� 3�� �̻�.
// 2������ ���� dPoZ���� 0���� �־��ָ� ��.
// 3������ ���� ������� 3���� dPosZ ���� �־��ش�.
function AxmSplineWrite (lCoord : LongInt; lPosSize : LongInt; dpPosX : PDouble; dpPosY : PDouble; dVel : Double; dAccel : Double; dDecel : Double; dPosZ : Double; lPointFactor : LongInt) : DWord; stdcall;    

//======== PCI-R1604-MLII/SIIIH, PCIe-Rxx04-SIIIH ���� �Լ� ====================================================================================
// ��ġ ���� ���̺� ��ɿ� �ʿ��� ������ �����Ѵ�.
function AxmCompensationSet (lAxisNo : LongInt; lNumEntry : LongInt; dStartPos : Double; dpPosition : PDouble; dpCorrection : PDouble; lRollOver : LongInt) : DWord; stdcall;
// ��ġ ���� ���̺� ��� ���� ������ ��ȯ�Ѵ�.
function AxmCompensationGet (lAxisNo : LongInt; lpNumEntry : PLongInt; dpStartPos : PDouble; dpPosition : PDouble; dpCorrection : PDouble; lpRollOver : PLongInt) : DWord; stdcall;

// ��ġ ���� ���̺� ����� ������θ� �����Ѵ�.
function AxmCompensationEnable (lAxisNo : LongInt; lEnable : LongInt) : DWord; stdcall;
// ��ġ ���� ���̺� ����� ��������� ���� ���� ���¸� ��ȯ�Ѵ�.
function AxmCompensationIsEnable (lAxisNo : LongInt; lpEnable : PLongInt) : DWord; stdcall;
// ���� ���� ��ġ������ �������� ��ȯ�Ѵ�.
function AxmCompensationGetCorrection(lAxisNo : LongInt; dpCorrection : PDouble) : DWord; stdcall;

// Backlash�� ���õ� �������ϴ� �Լ�
// > lBacklashDir: Backlash ������ ������ ���� ������ ���� (�����˻� ����� �����ϰ� ������)  
//   - [0] -> Command Position���� (+)�������� ������ �� ������ backlash�� ������ 
//   - [1] -> Command Position���� (-)�������� ������ �� ������ backlash�� ������
//   - Ex1) lBacklashDir�� 0, backlash�� 0.01�� �� 0.0 -> 100.0���� ��ġ�̵� �� �� ���� �̵��ϴ� ��ġ�� 100.01�̵�
//   - Ex2) lBacklashDir�� 0, backlash�� 0.01�� �� 0.0 -> -100.0���� ��ġ�̵� �� �� ���� �̵��ϴ� ��ġ�� -100.0�̵�
//   �� NOTANDUM 
//   - ��Ȯ�� Backlash������ ���ؼ��� �����˻��� �������� Backlash�� ��ŭ (+)Or(-)�������� �̵� �� �� ������ �Ϸ��ϰ�
//     Backlash������ ����Ѵ�. �� �� Backlash�� ��ŭ (+)������ �ߴٸ� backlash_dir�� [1](-)��, (-)������ �ߴٸ�
//     backlash_dir�� [0](+)�� �����ϸ� �ȴ�.
// > dBacklash: �ⱸ�ο��� ���� ����� �ݴ�������� ������ȯ�� �߻��Ǵ� Backlash���� ������
// { RETURN VALUE } 
//   - [0] -> Backlash ������ �������� ��
function AxmCompensationSetBacklash(lAxisNo : LongInt; lBacklashDir : LongInt; dBacklash : Double) : DWord; stdcall;
// Backlash�� ���õ� ���� ������ ��ȯ�Ѵ�.
function AxmCompensationGetBacklash(lAxisNo : LongInt;, lpBacklashDir : PLongInt; dpBacklash : PDouble) : DWord; stdcall;
// Backlash��������� ����/Ȯ���ϴ� �Լ�
// > dwEnable: Backlash���� ��������� ����
//   - [0]DISABLE -> Backlash������ ������    
//   - [1]ENABLE  -> Backlash������ �����
// { RETURN VALUE } 
//   - [0] -> Backlash ������ȯ�� �������� ��
function AxmCompensationEnableBacklash(lAxisNo : LongInt; dwEnable : DWord) : DWord; stdcall;
function AxmCompensationIsEnableBacklash(lAxisNo : LongInt; dwpEnable : PDWord) : DWord; stdcall;

// ECAM ��ɿ� �ʿ��� ������ �����Ѵ�.
function AxmEcamSet (lAxisNo : LongInt; lMasterAxis : LongInt; lNumEntry : LongInt; dMasterStartPos : Double; dpMasterPos : PDouble; dpSlavePos : PDouble) : DWord; stdcall;
// ECAM ��ɿ� �ʿ��� ������ CMD/ACT Source�� �Բ� �����Ѵ�. (PCIe-Rxx04-SIIIH ���� �Լ�)
function AxmEcamSetWithSource(lAxisNo : LongInt; lMasterAxis : LongInt; lNumEntry : LongInt; dMasterStartPos : Double; dpMasterPos : PDouble; dpSlavePos : PDouble;  dwSource : DWord) : DWord; stdcall;
// ECAM ��� ���� ������ ��ȯ�Ѵ�.
function AxmEcamGet (lAxisNo : LongInt; lpMasterAxis : PLongInt; lpNumEntry : PLongInt; dpMasterStartPos : PDouble; dpMasterPos : PDouble; dpSlavePos : PDouble) : DWord; stdcall;
// ECAM ��� ���� ������ CMD/ACT Source�� �Բ� ��ȯ�Ѵ�. (PCIe-Rxx04-SIIIH ���� �Լ�)
function AxmEcamGetWithSource(lAxisNo : LongInt; lpMasterAxis : PLongInt; lpNumEntry : PLongInt; dpMasterStartPos : PDouble; dpMasterPos : PDouble; dpSlavePos : PDouble; dwpSource : PDWord) : DWord; stdcall;

// ECAM ����� ��� ������ �����Ѵ�.
function AxmEcamEnableBySlave (lAxisNo : LongInt; lEnable : LongInt) : DWord; stdcall;
// ECAM ����� ��� ������ ������ Master �࿡ ����� ��� Slave �࿡ ���Ͽ� �����Ѵ�.
function AxmEcamEnableByMaster (lAxisNo : LongInt; lEnable : LongInt) : DWord; stdcall;
// ECAM ����� ��� ������ ���� ���� ���¸� ��ȯ�Ѵ�.
function AxmEcamIsSlaveEnable (lAxisNo : LongInt; lpEnable : PLongInt) : DWord; stdcall;

//======== Servo Status Monitor =======================================================================================
// ���� ���� ���� ó�� ��ɿ� ���� �����Ѵ�.(MLII : Sigma-5, SIIIH : MR_J4_xxB ����)
// dwSelMon(0~3): ���� ���� ����.
//          [0] : Torque 
//          [1] : Velocity of motor
//          [2] : Accel. of motor
//          [3] : Decel. of motor
//          [4] : Position error between Cmd. position and Act. position.
// dwActionValue: �̻� ���� ���� ���� �� ����. �� ������ ���� ���� ���� �ǹ̰� ����.
//          [0] : dwSelMon���� ������ ���� ������ ���Ͽ� ���� ó�� ���� ����.
//         [>0] : dwSelMon���� ������ ���� ������ ���Ͽ� ���� ó�� ��� ����.
// dwAction(0~3): dwActionValue �̻����� ���� ������ Ȯ�εǾ����� ����ó�� ��� ����.
//          [0] : Warning(setting flag only) 
//          [1] : Warning(setting flag) + Slow-down stop
//          [2] : Warning(setting flag) + Emergency stop
//          [3] : Warning(setting flag) + Emergency stop + Servo-Off
// �� ����: 5���� SelMon ������ ���� ���� ����ó�� ������ �����ϸ�, ����� ����ó���� ���������� ���
//          �ݵ�� �ش� SelMon ������ ActionValue���� 0���� ������ ���ñ���� Disable �ص�.
function AxmStatusSetServoMonitor(lAxisNo : LongInt; dwSelMon : DWord; dActionValue : Double; dwAction : DWord) : DWord; stdcall;
// ���� ���� ���� ó�� ��ɿ� ���� ���� ���¸� ��ȯ�Ѵ�.(MLII : Sigma-5, SIIIH : MR_J4_xxB ����)
function AxmStatusGetServoMonitor(lAxisNo : LongInt; dwSelMon : DWord; dpActionValue : PDouble; dwpAction : PDWord) : DWord; stdcall;
// ���� ���� ���� ó�� ��ɿ� ���� ��� ������ �����Ѵ�.(MLII : Sigma-5, SIIIH : MR_J4_xxB ����)
function AxmStatusSetServoMonitorEnable(lAxisNo : LongInt; dwEnable : DWord) : DWord; stdcall;
// ���� ���� ���� ó�� ��ɿ� ���� ��� ������ ��ȯ�Ѵ�.(MLII : Sigma-5, SIIIH : MR_J4_xxB ����)
function AxmStatusGetServoMonitorEnable(lAxisNo : LongInt; dwpEnable : PDWord) : DWord; stdcall;

// ���� ���� ���� ó�� ��� ���� ��� �÷��� ���� ��ȯ�Ѵ�. �Լ� ���� �� �ڵ� �ʱ�ȭ.(MLII, Sigma-5 ����)
function AxmStatusReadServoMonitorFlag(lAxisNo : LongInt; dwSelMon : DWord; dwpMonitorFlag : PDWord; dpMonitorValue : PDouble) : DWord; stdcall;
// ���� ���� ���� ó�� ����� ���� ���� ������ ��ȯ�Ѵ�.(MLII : Sigma-5, SIIIH : MR_J4_xxB ����)
function AxmStatusReadServoMonitorValue(lAxisNo : LongInt; dwSelMon : DWord; dpMonitorValue : PDouble) : DWord; stdcall;
// ���� ���� �������� ���� �� �ֵ��� ���� �մϴ�.(MLII : Sigma-5, SIIIH : MR_J4_xxB ����)
// dwSelMon = 0 : Accumulated load ratio
// dwSelMon = 1 : Regenerative load ratio
// dwSelMon = 2 : Reference Torque load ratio
function AxmStatusSetReadServoLoadRatio(lAxisNo : LongInt; dwSelMon : DWord) : DWord; stdcall;
// ���� ���� �������� ��ȯ�Ѵ�.(MLII, Sigma-5 ����)
function AxmStatusReadServoLoadRatio(lAxisNo : LongInt; dpMonitorValue : PDouble) : DWord; stdcall;

//======== PCI-R1604-RTEX ���� �Լ�====================================================================================
// RTEX A4Nx ���� Scale Coefficient�� �����Ѵ�.(RTEX, A4Nx ����)
function AxmMotSetScaleCoeff(lAxisNo : LongInt; lScaleCoeff : LongInt) : DWord; stdcall;
// RTEX A4Nx ���� Scale Coefficient �� Ȯ���Ѵ�.(RTEX, A4Nx ����)
function AxmMotGetScaleCoeff(lAxisNo : LongInt; lpScaleCoeff : PLongInt) : DWord; stdcall;

// Ư�� Input ��ȣ�� Edge�� �����Ͽ� ������ �Ǵ� ���������ϴ� �Լ�.
// lDetect Signal : edge ������ �Է� ��ȣ ����.
// lDetectSignal  : PosEndLimit(0), NegEndLimit(1), HomeSensor(4)
// Signal Edge    : ������ �Է� ��ȣ�� edge ���� ���� (rising or falling edge).
//                  SIGNAL_DOWN_EDGE(0), SIGNAL_UP_EDGE(1)
// ��������       : Vel���� ����̸� CW, �����̸� CCW.
// SignalMethod   : ������ EMERGENCY_STOP(0), �������� SLOWDOWN_STOP(1)
// ���ǻ���: SignalMethod�� EMERGENCY_STOP(0)�� ����Ұ�� �������� ���õǸ� ������ �ӵ��� ���� �������ϰԵȴ�.
//           PCI-Nx04�� ����� ��� lDetectSignal�� PosEndLimit , NegEndLimit(0,1) �� ã����� ��ȣ�Ƿ��� Active ���¸� �����ϰԵȴ�.
function AxmMoveSignalSearchEx(lAxisNo : LongInt; dVel : Double; dAccel : Double; lDetectSignal : LongInt; lSignalEdge : LongInt; lSignalMethod : LongInt) : DWord; stdcall;
//---------------------------------------------------------------------------------------------------------------------

//======== PCI-R1604-MLII/SIIIH, PCIe-Rxx04-SIIIH ���� �Լ� ==================================================================================
// ������ ���� ��ġ�� �̵��Ѵ�.
// �ӵ� ���������� ����� �������� �����Ѵ�.
// �޽��� ��µǴ� �������� �Լ��� �����.
// �׻� ��ġ �� �ӵ�, �����ӵ��� ���� �����ϸ�, �ݴ���� ��ġ ���� ����� �����Ѵ�.
function AxmMoveToAbsPos(lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;
// ���� ���� ���� ���� �ӵ��� �о�´�.
function AxmStatusReadVelEx(lAxisNo : LongInt; dVel : Double; dAccel : Double; lDetectSignal : LongInt; lSignalEdge : LongInt; lSignalMethod : LongInt) : DWord; stdcall;

//======== PCI-R1604-SIIIH, PCIe-Rxx04-SIIIH ���� �Լ� ==================================================================================
// ���� ���� ���� ���� �����Ѵ�. ���� �� �� �ֹ߼� �޸𸮿� ���˴ϴ�.
// �ʱ� ��(lNumerator : 4194304(2^22), lDenominator : 10000)
// MR-J4-B�� ���� ���� ������ �� ������, ���� ����⿡�� �Ʒ��� �Լ��� ����Ͽ� �����Ͽ��� �մϴ�.
// ���� �޽� �Է� ��� ���� ����̹�(MR-J4-A)�� �Ķ���� No.PA06, No.PA07�� �ش�.
// ex1) 1 um�� ���� ������ ����. ���ӱ� ���� : 1/1. Rotary motor�� ������ Linear stage.
// Encoder resulotion = 2^22
// Ball screw pitch : 6 mm
// ==> lNumerator = 2^22, lDenominator = 6000(6/0.001)
// AxmMotSetMoveUnitPerPulse���� Unit/Pulse = 1/1�� �����Ͽ��ٸ�, ��� �Լ��� ��ġ ���� : um, �ӵ� ���� : um/sec, �����ӵ� �ܵ� : um/sec^2�� �ȴ�.
// AxmMotSetMoveUnitPerPulse���� Unit/Pulse = 1/1000�� �����Ͽ��ٸ�, ��� �Լ��� ��ġ ���� : mm, �ӵ� ���� : mm/sec, �����ӵ� �ܵ� : mm/sec^2�� �ȴ�.
// ex2) 0.01�� ȸ���� ���� ������ ����. ���ӱ� ���� : 1/1. Rotary motor�� ������ ȸ��ü ������.
// Encoder resulotion = 2^22
// 1 ȸ�� : 360
// ==> lNumerator = 2^22, lDenominator = 36000(360 / 0.01)
// AxmMotSetMoveUnitPerPulse���� Unit/Pulse = 1/1�� �����Ͽ��ٸ�, ��� �Լ��� ��ġ ���� : 0.01��, �ӵ� ���� : 0.01��/sec, �����ӵ� �ܵ� : 0.01��/sec^2�� �ȴ�.
// AxmMotSetMoveUnitPerPulse���� Unit/Pulse = 1/100�� �����Ͽ��ٸ�, ��� �Լ��� ��ġ ���� : 1��, �ӵ� ���� : 1��/sec, �����ӵ� �ܵ� : 1��/sec^2�� �ȴ�.
function AxmMotSetElectricGearRatio(lAxisNo : LongInt; lNumerator  : LongInt; lDenominator : LongInt) : DWord; stdcall;

// ���� ���� ���� ���� ������ Ȯ���Ѵ�.
function AxmMotGetElectricGearRatio(lAxisNo : LongInt; lpNumerator : PLongInt; lpDenominator : PLongInt) : DWord; stdcall;

// ���� ���� ��ũ ����Ʈ ���� ���� �մϴ�.
// ������, ������ �������� ��ũ ���� �����ϴ� �Լ�.
// ���� ���� 1 ~ 1000���� ����
// �ִ� ��ũ�� 0.1% ������ ���� ��.
function AxmMotSetTorqueLimit(lAxisNo : LongInt; dbPluseDirTorqueLimit : Double; dbMinusDirTorqueLimit : Double) : DWord; stdcall;

// ���� ���� ��ũ ����Ʈ ���� Ȯ�� �մϴ�.
// ������, ������ �������� ��ũ ���� �о� ���� �Լ�.
// ���� ���� 1 ~ 1000���� ����
// �ִ� ��ũ�� 0.1% ������ ���� ��.
function AxmMotGetTorqueLimit(lAxisNo : LongInt; dbpPluseDirTorqueLimit : PDouble; dbpMinusDirTorqueLimit : PDouble) : DWord; stdcall;

// ���� ���� AxmOverridePos�� ���� Ư�� ��� ��� ������ �����Ѵ�.
// dwUsage        : AxmOverridPos ���� ���� ��ġ �Ǵ� ��� ��� ����.
//                  DISABLE(0) : Ư�� ��� ������� ����.
//                  ENABLE(1) : AxmMoveStartPos ������ ���� �� ��ġ ���� ���� ��ġ�� ���� �Ÿ��� lDecelPosRatio(%)�� �������� �Ǵ��Ѵ�.
// lDecelPosRatio : ���� �Ÿ��� ���� %��.
// dReserved      : ������� ����.
function AxmOverridePosSetFunction(lAxisNo : LongInt; dwUsage : DWord; lDecelPosRatio: LongInt; dReserved : Double) : DWord; stdcall;

// ���� ���� AxmOverridePos�� ���� Ư�� ��� ��� ������ Ȯ�� �Ѵ�.
function AxmOverridePosGetFunction(lAxisNo : LongInt; dwpUsage : PDWord; lpDecelPosRatio: PLongInt; dpReserved : PDouble) : DWord; stdcall;

// M3 �����ѿ� Command Execution�� �����Ѵ�
function AxmServoCmdExecution(lAxisNo : LongInt; dwCommand : DWord; dwSize : DWord; pdwExcData : PDWord);

//======== SMP ���� �Լ� =======================================================================================
// Inposition ��ȣ�� Range�� �����Ѵ�. (dInposRange > 0)
function AxmSignalSetInposRange(lAxisNo : LongInt; dInposRange : Double);
// Inposition ��ȣ�� Range�� ��ȯ�Ѵ�.
function AxmSignalGetInposRange(lAxisNo : LongInt; dpInposRange : PDouble);

// �������̵��Ҷ� ��ġ�Ӽ�(����/���)�� �����Ѵ�.
function AxmMotSetOverridePosMode(lAxisNo : LongInt; dwAbsRelMode : DWord);
// �������̵��Ҷ� ��ġ�Ӽ�(����/���)�� �о�´�.
function AxmMotGetOverridePosMode(lAxisNo : LongInt; dwpAbsRelMode : PDWord);
// LineMove �������̵��Ҷ� ��ġ�Ӽ�(����/���)�� �����Ѵ�.
function AxmMotSetOverrideLinePosMode(lCoordNo : LongInt; dwAbsRelMode : DWord);
// LineMove �������̵��Ҷ� ��ġ�Ӽ�(����/���)�� �о�´�.
function AxmMotGetOverrideLinePosMode(lCoordNo : LongInt; dwpAbsRelMode : PDWord);

// AxmMoveStartPos�� �����ϸ� ����ӵ�(EndVel)�� �߰��Ǿ���.
function AxmMoveStartPosEx(lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double; dEndVel : Double);
// AxmMovePos�� �����ϸ� ����ӵ�(EndVel)�� �߰��Ǿ���.
function AxmMovePosEx(lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double; dEndVel : Double);

// Coordinate Motion�� ��λ󿡼� ��������(dDecel) ��Ų��.
function AxmMoveCoordStop(lCoordNo : LongInt; dDecel : Double); 
// Coordinate Motion�� ������ ��Ų��.
function AxmMoveCoordEStop(lCoordNo : LongInt);
// Coordinate Motion�� ��λ󿡼� �������� ��Ų��.
function AxmMoveCoordSStop(lCoordNo : LongInt);

// AxmLineMove����� ��ġ�� �������̵� ��Ų��.
function AxmOverrideLinePos(lCoordNo : LongInt; dpOverridePos : PDouble);
// AxmLineMove����� �ӵ��� �������̵� ��Ų��. ������� �ӵ������� dpDistance�� �����ȴ�.
function AxmOverrideLineVel(lCoordNo : LongInt; dOverrideVel : Double; dpDistance : PDouble);

// AxmLineMove����� �ӵ��� �������̵� ��Ų��.
// dMaxAccel  : �������̵� ���ӵ�
// dMaxDecel  : �������̵� ���ӵ�
// dpDistance : ������ �ӵ� ����
function AxmOverrideLineAccelVelDecel(lCoordNo : LongInt; dOverrideVelocity : Double; dMaxAccel : Double; dMaxDecel : Double dpDistance : PDouble);
// AxmOverrideVelAtPos�� �߰������� AccelDecel�� �������̵� ��Ų��.
function AxmOverrideAccelVelDecelAtPos(lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double; dOverridePos : Double; dOverrideVel : Double; dOverrideAccel : Double; dOverrideDecel : Double; lTarget : LongInt);

// �ϳ��� �������࿡ �ټ��� �����̺������ �����Ѵ�(Electronic Gearing).
// lMasterAxisNo : ��������
// lSize : �����̺��� ����(�ִ� 8)
// lpSlaveAxisNo : �����̺��� ��ȣ
// dpGearRatio : ���������� ���������ϴ� �����̺��� ����(0�� ����, 1 = 100%)
function AxmEGearSet(lMasterAxisNo : LongInt; lSize : LongInt; lpSlaveAxisNo : LongInt; dpGearRatio : PDouble);
// Electronic Gearing������ �о�´�.
function AxmEGearGet(lMasterAxisNo : LongInt; lpSize : PLongInt, lpSlaveAxisNo : PLongInt; dpGearRatio : PDouble);
// Electronic Gearing�� �����Ѵ�.
function AxmEGearReset(lMasterAxisNo : LongInt);
// Electronic Gearing�� Ȱ��/��Ȱ���Ѵ�.
function AxmEGearEnable(lMasterAxisNo : LongInt; dwEnable : DWord);
// Electronic Gearing�� Ȱ��/��Ȱ�����¸� �о�´�.
function AxmEGearIsEnable(lMasterAxisNo : LongInt; dwpEnable : PDWord);    

// ���ǻ���: �Է��� ����ӵ��� '0'�̸��̸� '0'����, 'AxmMotSetMaxVel'�� ������ �ִ�ӵ��� �ʰ��ϸ� 'MaxVel'�� �缳���ȴ�. 
// ���� �࿡ ����ӵ��� �����Ѵ�.
function AxmMotSetEndVel(lAxisNo : LongInt; dEndVelocity : Double);
// ���� ���� ����ӵ��� ��ȯ�Ѵ�.
function AxmMotGetEndVel(lAxisNo : LongInt; dpEndVelocity : PDouble);


//------------------------------------------------------------------------------------------------------------------

implementation

const

    dll_name    = 'Axl.dll';

    function AxmInfoGetAxis; external dll_name name 'AxmInfoGetAxis';
    function AxmInfoIsMotionModule; external dll_name name 'AxmInfoIsMotionModule';
    function AxmInfoIsInvalidAxisNo; external dll_name name 'AxmInfoIsInvalidAxisNo';
    function AxmInfoGetAxisStatus; external dll_name name 'AxmInfoGetAxisStatus';    
    function AxmInfoGetAxisCount; external dll_name name 'AxmInfoGetAxisCount';
    function AxmInfoGetFirstAxisNo; external dll_name name 'AxmInfoGetFirstAxisNo';
    function AxmInfoGetBoardFirstAxisNo ; external dll_name name 'AxmInfoGetBoardFirstAxisNo ';

    function AxmVirtualSetAxisNoMap; external dll_name name 'AxmVirtualSetAxisNoMap';
    function AxmVirtualGetAxisNoMap; external dll_name name 'AxmVirtualGetAxisNoMap';
    function AxmVirtualSetMultiAxisNoMap; external dll_name name 'AxmVirtualSetMultiAxisNoMap';
    function AxmVirtualGetMultiAxisNoMap; external dll_name name 'AxmVirtualGetMultiAxisNoMap';
    function AxmVirtualResetAxisMap; external dll_name name 'AxmVirtualResetAxisMap';

    function AxmInterruptSetAxis; external dll_name name 'AxmInterruptSetAxis';
    function AxmInterruptSetAxisEnable; external dll_name name 'AxmInterruptSetAxisEnable';
    function AxmInterruptGetAxisEnable; external dll_name name 'AxmInterruptGetAxisEnable';
    function AxmInterruptRead; external dll_name name 'AxmInterruptRead';
    function AxmInterruptReadAxisFlag; external dll_name name 'AxmInterruptReadAxisFlag';
    function AxmInterruptSetUserEnable; external dll_name name 'AxmInterruptSetUserEnable';
    function AxmInterruptGetUserEnable; external dll_name name 'AxmInterruptGetUserEnable';

    function AxmMotLoadParaAll; external dll_name name 'AxmMotLoadParaAll';
    function AxmMotSaveParaAll; external dll_name name 'AxmMotSaveParaAll';
    function AxmMotSetParaLoad; external dll_name name 'AxmMotSetParaLoad';
    function AxmMotGetParaLoad; external dll_name name 'AxmMotGetParaLoad';
    function AxmMotSetPulseOutMethod; external dll_name name 'AxmMotSetPulseOutMethod';
    function AxmMotGetPulseOutMethod; external dll_name name 'AxmMotGetPulseOutMethod';
    function AxmMotSetEncInputMethod; external dll_name name 'AxmMotSetEncInputMethod';
    function AxmMotGetEncInputMethod; external dll_name name 'AxmMotGetEncInputMethod';
    function AxmMotSetMoveUnitPerPulse; external dll_name name 'AxmMotSetMoveUnitPerPulse';
    function AxmMotGetMoveUnitPerPulse; external dll_name name 'AxmMotGetMoveUnitPerPulse';
    function AxmMotSetDecelMode; external dll_name name 'AxmMotSetDecelMode';
    function AxmMotGetDecelMode; external dll_name name 'AxmMotGetDecelMode';
    function AxmMotSetRemainPulse; external dll_name name 'AxmMotSetRemainPulse';
    function AxmMotGetRemainPulse; external dll_name name 'AxmMotGetRemainPulse';
    function AxmMotSetMaxVel; external dll_name name 'AxmMotSetMaxVel';
    function AxmMotGetMaxVel; external dll_name name 'AxmMotGetMaxVel';
    function AxmMotSetAbsRelMode; external dll_name name 'AxmMotSetAbsRelMode';
    function AxmMotGetAbsRelMode; external dll_name name 'AxmMotGetAbsRelMode';
    function AxmMotSetProfileMode; external dll_name name 'AxmMotSetProfileMode';
    function AxmMotGetProfileMode; external dll_name name 'AxmMotGetProfileMode';
    function AxmMotSetAccelUnit; external dll_name name 'AxmMotSetAccelUnit';
    function AxmMotGetAccelUnit; external dll_name name 'AxmMotGetAccelUnit';
    function AxmMotSetMinVel; external dll_name name 'AxmMotSetMinVel';
    function AxmMotGetMinVel; external dll_name name 'AxmMotGetMinVel';
    function AxmMotSetAccelJerk; external dll_name name 'AxmMotSetAccelJerk';
    function AxmMotGetAccelJerk; external dll_name name 'AxmMotGetAccelJerk';
    function AxmMotSetDecelJerk; external dll_name name 'AxmMotSetDecelJerk';
    function AxmMotGetDecelJerk; external dll_name name 'AxmMotGetDecelJerk';
    function AxmMotSetProfilePriority; external dll_name name 'AxmMotSetProfilePriority';
    function AxmMotGetProfilePriority; external dll_name name 'AxmMotGetProfilePriority';

    function AxmSignalSetZphaseLevel; external dll_name name 'AxmSignalSetZphaseLevel';
    function AxmSignalGetZphaseLevel; external dll_name name 'AxmSignalGetZphaseLevel';
    function AxmSignalSetServoOnLevel; external dll_name name 'AxmSignalSetServoOnLevel';
    function AxmSignalGetServoOnLevel; external dll_name name 'AxmSignalGetServoOnLevel';
    function AxmSignalSetServoAlarmResetLevel; external dll_name name 'AxmSignalSetServoAlarmResetLevel';
    function AxmSignalGetServoAlarmResetLevel; external dll_name name 'AxmSignalGetServoAlarmResetLevel';
    function AxmSignalSetInpos; external dll_name name 'AxmSignalSetInpos';
    function AxmSignalGetInpos; external dll_name name 'AxmSignalGetInpos';
    function AxmSignalReadInpos; external dll_name name 'AxmSignalReadInpos';
    function AxmSignalSetServoAlarm; external dll_name name 'AxmSignalSetServoAlarm';
    function AxmSignalGetServoAlarm; external dll_name name 'AxmSignalGetServoAlarm';
    function AxmSignalReadServoAlarm; external dll_name name 'AxmSignalReadServoAlarm';
    function AxmSignalSetLimit; external dll_name name 'AxmSignalSetLimit';
    function AxmSignalGetLimit; external dll_name name 'AxmSignalGetLimit';
    function AxmSignalReadLimit; external dll_name name 'AxmSignalReadLimit';
    function AxmSignalSetSoftLimit; external dll_name name 'AxmSignalSetSoftLimit';
    function AxmSignalGetSoftLimit; external dll_name name 'AxmSignalGetSoftLimit';
    function AxmSignalReadSoftLimit; external dll_name name 'AxmSignalReadSoftLimit';
    function AxmSignalSetStop; external dll_name name 'AxmSignalSetStop';
    function AxmSignalGetStop; external dll_name name 'AxmSignalGetStop';
    function AxmSignalReadStop; external dll_name name 'AxmSignalReadStop';
    function AxmSignalServoOn; external dll_name name 'AxmSignalServoOn';
    function AxmSignalIsServoOn; external dll_name name 'AxmSignalIsServoOn';
    function AxmSignalServoAlarmReset; external dll_name name 'AxmSignalServoAlarmReset';
    function AxmSignalWriteOutput; external dll_name name 'AxmSignalWriteOutput';
    function AxmSignalReadOutput; external dll_name name 'AxmSignalReadOutput';
    function AxmSignalWriteOutputBit; external dll_name name 'AxmSignalWriteOutputBit';
    function AxmSignalReadOutputBit; external dll_name name 'AxmSignalReadOutputBit';
    function AxmSignalReadInput; external dll_name name 'AxmSignalReadInput';
    function AxmSignalReadInputBit; external dll_name name 'AxmSignalReadInputBit';
    function AxmSignalSetFilterBandwidth; external dll_name name 'AxmSignalSetFilterBandwidth';

    function AxmStatusReadInMotion; external dll_name name 'AxmStatusReadInMotion';
    function AxmStatusReadDrivePulseCount; external dll_name name 'AxmStatusReadDrivePulseCount';
    function AxmStatusReadMotion; external dll_name name 'AxmStatusReadMotion';
    function AxmStatusReadStop; external dll_name name 'AxmStatusReadStop';
    function AxmStatusReadMechanical; external dll_name name 'AxmStatusReadMechanical';
    function AxmStatusReadVel; external dll_name name 'AxmStatusReadVel';
    function AxmStatusReadPosError; external dll_name name 'AxmStatusReadPosError';
    function AxmStatusReadDriveDistance; external dll_name name 'AxmStatusReadDriveDistance';
    function AxmStatusSetPosType; external dll_name name 'AxmStatusSetPosType';
    function AxmStatusGetPosType; external dll_name name 'AxmStatusGetPosType';
    function AxmStatusSetAbsOrgOffset; external dll_name name 'AxmStatusSetAbsOrgOffset';
    function AxmStatusSetActPos; external dll_name name 'AxmStatusSetActPos';
    function AxmStatusGetActPos; external dll_name name 'AxmStatusGetActPos';
    function AxmStatusSetCmdPos; external dll_name name 'AxmStatusSetCmdPos';
    function AxmStatusGetCmdPos; external dll_name name 'AxmStatusGetCmdPos';
    function AxmStatusSetPosMatch; external dll_name name 'AxmStatusSetPosMatch';
    function AxmStatusRequestServoAlarm; external dll_name name 'AxmStatusRequestServoAlarm';
    function AxmStatusReadServoAlarm; external dll_name name 'AxmStatusReadServoAlarm';
    function AxmStatusGetServoAlarmString; external dll_name name 'AxmStatusGetServoAlarmString';
    function AxmStatusRequestServoAlarmHistory; external dll_name name 'AxmStatusRequestServoAlarmHistory';
    function AxmStatusReadServoAlarmHistory; external dll_name name 'AxmStatusReadServoAlarmHistory';
    function AxmStatusClearServoAlarmHistory; external dll_name name 'AxmStatusClearServoAlarmHistory';

    function AxmHomeSetSignalLevel; external dll_name name 'AxmHomeSetSignalLevel';
    function AxmHomeGetSignalLevel; external dll_name name 'AxmHomeGetSignalLevel';
    function AxmHomeReadSignal; external dll_name name 'AxmHomeReadSignal';
    function AxmHomeSetMethod; external dll_name name 'AxmHomeSetMethod';
    function AxmHomeGetMethod; external dll_name name 'AxmHomeGetMethod';
    function AxmHomeSetFineAdjust; external dll_name name 'AxmHomeSetFineAdjust';
    function AxmHomeGetFineAdjust; external dll_name name 'AxmHomeGetFineAdjust';
    function AxmHomeSetVel; external dll_name name 'AxmHomeSetVel';
    function AxmHomeGetVel; external dll_name name 'AxmHomeGetVel';
    function AxmHomeSetStart; external dll_name name 'AxmHomeSetStart';
    function AxmHomeSetResult; external dll_name name 'AxmHomeSetResult';
    function AxmHomeGetResult; external dll_name name 'AxmHomeGetResult';
    function AxmHomeGetRate; external dll_name name 'AxmHomeGetRate';

    function AxmMoveStartPos; external dll_name name 'AxmMoveStartPos';
    function AxmMovePos; external dll_name name 'AxmMovePos';
    function AxmMoveVel; external dll_name name 'AxmMoveVel';
    function AxmMoveStartMultiVel; external dll_name name 'AxmMoveStartMultiVel';
    function AxmMoveStartMultiVelEx; external dll_name name 'AxmMoveStartMultiVelEx';    
    function AxmMoveStartLineVel; external dll_name name 'AxmMoveStartLineVel';
    function AxmMoveSignalSearch; external dll_name name 'AxmMoveSignalSearch';
    function AxmMoveSignalCapture; external dll_name name 'AxmMoveSignalCapture';
    function AxmMoveGetCapturePos; external dll_name name 'AxmMoveGetCapturePos';
    function AxmMoveStartMultiPos; external dll_name name 'AxmMoveStartMultiPos';
    function AxmMoveMultiPos; external dll_name name 'AxmMoveMultiPos';

    function AxmMoveStartTorque; external dll_name name 'AxmMoveStartTorque';
    function AxmMoveTorqueStop; external dll_name name 'AxmMoveTorqueStop';

    function AxmMoveStartPosWithList; external dll_name name 'AxmMoveStartPosWithList';
    function AxmMoveStartPosWithPosEvent; external dll_name name 'AxmMoveStartPosWithPosEvent';

    function AxmMoveStop; external dll_name name 'AxmMoveStop';
    function AxmMoveEStop; external dll_name name 'AxmMoveEStop';
    function AxmMoveSStop; external dll_name name 'AxmMoveSStop';

    function AxmOverridePos; external dll_name name 'AxmOverridePos';
    function AxmOverrideSetMaxVel; external dll_name name 'AxmOverrideSetMaxVel';
    function AxmOverrideVel; external dll_name name 'AxmOverrideVel';
    function AxmOverrideAccelVelDecel; external dll_name name 'AxmOverrideAccelVelDecel';
    function AxmOverrideVelAtPos; external dll_name name 'AxmOverrideVelAtPos';
    function AxmOverrideVelAtMultiPos; external dll_name name 'AxmOverrideVelAtMultiPos';

    function AxmLinkSetMode; external dll_name name 'AxmLinkSetMode';
    function AxmLinkGetMode; external dll_name name 'AxmLinkGetMode';
    function AxmLinkResetMode; external dll_name name 'AxmLinkResetMode';

    function AxmGantrySetEnable; external dll_name name 'AxmGantrySetEnable';
    function AxmGantryGetEnable; external dll_name name 'AxmGantryGetEnable';
    function AxmGantrySetDisable; external dll_name name 'AxmGantrySetDisable';
    function AxmGantrySetCompensationGain; external dll_name name 'AxmGantrySetCompensationGain';
    function AxmGantryGetCompensationGain; external dll_name name 'AxmGantryGetCompensationGain';
    function AxmGantrySetErrorRange; external dll_name name 'AxmGantrySetErrorRange';
    function AxmGantryGetErrorRange; external dll_name name 'AxmGantryGetErrorRange';
    function AxmGantryReadErrorRangeStatus; external dll_name name 'AxmGantryReadErrorRangeStatus';
    function AxmGantryReadErrorRangeComparePos; external dll_name name 'AxmGantryReadErrorRangeComparePos';

    function AxmLineMove; external dll_name name 'AxmLineMove';
    
    function AxmCircleCenterMove; external dll_name name 'AxmCircleCenterMove';
    function AxmCirclePointMove; external dll_name name 'AxmCirclePointMove';
    function AxmCircleRadiusMove; external dll_name name 'AxmCircleRadiusMove';
    function AxmCircleAngleMove; external dll_name name 'AxmCircleAngleMove';

    function AxmContiSetAxisMap; external dll_name name 'AxmContiSetAxisMap';
    function AxmContiGetAxisMap; external dll_name name 'AxmContiGetAxisMap';
    function AxmContiSetAbsRelMode; external dll_name name 'AxmContiSetAbsRelMode';
    function AxmContiGetAbsRelMode; external dll_name name 'AxmContiGetAbsRelMode';
    function AxmContiReadFree; external dll_name name 'AxmContiReadFree';
    function AxmContiReadIndex; external dll_name name 'AxmContiReadIndex';
    function AxmContiWriteClear; external dll_name name 'AxmContiWriteClear';
    function AxmContiBeginNode; external dll_name name 'AxmContiBeginNode';
    function AxmContiEndNode; external dll_name name 'AxmContiEndNode';
    function AxmContiStart; external dll_name name 'AxmContiStart';
    function AxmContiIsMotion; external dll_name name 'AxmContiIsMotion';
    function AxmContiGetNodeNum; external dll_name name 'AxmContiGetNodeNum';
    function AxmContiGetTotalNodeNum; external dll_name name 'AxmContiGetTotalNodeNum';

    function AxmTriggerSetTimeLevel; external dll_name name 'AxmTriggerSetTimeLevel';
    function AxmTriggerGetTimeLevel; external dll_name name 'AxmTriggerGetTimeLevel';
    function AxmTriggerSetAbsPeriod; external dll_name name 'AxmTriggerSetAbsPeriod';
    function AxmTriggerGetAbsPeriod; external dll_name name 'AxmTriggerGetAbsPeriod';
    function AxmTriggerSetBlock; external dll_name name 'AxmTriggerSetBlock';
    function AxmTriggerGetBlock; external dll_name name 'AxmTriggerGetBlock';
    function AxmTriggerOneShot; external dll_name name 'AxmTriggerOneShot';
    function AxmTriggerSetTimerOneshot; external dll_name name 'AxmTriggerSetTimerOneshot';
    function AxmTriggerOnlyAbs; external dll_name name 'AxmTriggerOnlyAbs';
    function AxmTriggerSetReset; external dll_name name 'AxmTriggerSetReset';

    function AxmCrcSetMaskLevel; external dll_name name 'AxmCrcSetMaskLevel';
    function AxmCrcGetMaskLevel; external dll_name name 'AxmCrcGetMaskLevel';
    function AxmCrcSetOutput; external dll_name name 'AxmCrcSetOutput';
    function AxmCrcGetOutput; external dll_name name 'AxmCrcGetOutput';

    function AxmMPGSetEnable; external dll_name name 'AxmMPGSetEnable';
    function AxmMPGGetEnable; external dll_name name 'AxmMPGGetEnable';
    function AxmMPGSetRatio; external dll_name name 'AxmMPGSetRatio';
    function AxmMPGGetRatio; external dll_name name 'AxmMPGGetRatio';
    function AxmMPGReset; external dll_name name 'AxmMPGReset';

    function AxmHelixCenterMove; external dll_name name 'AxmHelixCenterMove';
    function AxmHelixPointMove; external dll_name name 'AxmHelixPointMove';
    function AxmHelixRadiusMove; external dll_name name 'AxmHelixRadiusMove';
    function AxmHelixAngleMove; external dll_name name 'AxmHelixAngleMove';

    function AxmSplineWrite; external dll_name name 'AxmSplineWrite';

    function AxmCompensationSet; external dll_name name 'AxmCompensationSet';
    function AxmCompensationGet; external dll_name name 'AxmCompensationGet';
    function AxmCompensationEnable; external dll_name name 'AxmCompensationEnable';
    function AxmCompensationIsEnable; external dll_name name 'AxmCompensationIsEnable';

    function AxmEcamSet; external dll_name name 'AxmEcamSet';
    function AxmEcamGet; external dll_name name 'AxmEcamGet';
    function AxmEcamEnableBySlave; external dll_name name 'AxmEcamEnableBySlave';
    function AxmEcamEnableByMaster; external dll_name name 'AxmEcamEnableByMaster';
    function AxmEcamIsSlaveEnable; external dll_name name 'AxmEcamIsSlaveEnable';   
    
    function AxmStatusSetServoMonitor; external dll_name name 'AxmStatusSetServoMonitor';   
    function AxmStatusGetServoMonitor; external dll_name name 'AxmStatusGetServoMonitor';   
    function AxmStatusSetServoMonitorEnable; external dll_name name 'AxmStatusSetServoMonitorEnable';   
    function AxmStatusGetServoMonitorEnable; external dll_name name 'AxmStatusGetServoMonitorEnable';   
    function AxmStatusReadServoMonitorFlag; external dll_name name 'AxmStatusReadServoMonitorFlag';   
    function AxmStatusReadServoMonitorValue; external dll_name name 'AxmStatusReadServoMonitorValue';
    function AxmStatusSetReadServoLoadRatio; external dll_name name 'AxmStatusSetReadServoLoadRatio';
    function AxmStatusReadServoLoadRatio; external dll_name name 'AxmStatusReadServoLoadRatio'; 
    function AxmMotSetScaleCoeff; external dll_name name 'AxmMotSetScaleCoeff';   
    function AxmMotGetScaleCoeff; external dll_name name 'AxmMotGetScaleCoeff';   
    function AxmMoveSignalSearchEx; external dll_name name 'AxmMoveSignalSearchEx';
    function AxmMoveToAbsPos; external dll_name name 'AxmMoveToAbsPos';
    function AxmStatusReadVelEx; external dll_name name 'AxmStatusReadVelEx';
    
    function AxmMotSetElectricGearRatio; external dll_name name 'AxmMotSetElectricGearRatio';
    function AxmMotGetElectricGearRatio; external dll_name name 'AxmMotGetElectricGearRatio';
    function AxmMotSetTorqueLimit; external dll_name name 'AxmMotSetTorqueLimit';
    function AxmMotGetTorqueLimit; external dll_name name 'AxmMotGetTorqueLimit';
    function AxmOverridePosSetFunction; external dll_name name 'AxmOverridePosSetFunction';
    function AxmOverridePosGetFunction; external dll_name name 'AxmOverridePosGetFunction';	
    
    function AxmMoveStopEx; external dll_name name 'AxmMoveStopEx';
    function AxmLineMoveEx2; external dll_name name 'AxmLineMoveEx2';
    function AxmCompensationGetCorrection; external dll_name name 'AxmCompensationGetCorrection';
    function AxmEcamSetWithSource; external dll_name name 'AxmEcamSetWithSource';
    function AxmEcamGetWithSource; external dll_name name 'AxmEcamGetWithSource';
    function AxmOverrideVelAtMultiPos2; external dll_name name 'AxmOverrideVelAtMultiPos2';

    function AxmServoCmdExecution; external dll_name name 'AxmServoCmdExecution';	

    function AxmSignalSetInposRange; external dll_name name 'AxmSignalSetInposRange';
    function AxmSignalGetInposRange; external dll_name name 'AxmSignalGetInposRange';
    function AxmMotSetOverridePosMode; external dll_name name 'AxmMotSetOverridePosMode';
    function AxmMotGetOverridePosMode; external dll_name name 'AxmMotGetOverridePosMode';
    function AxmMotSetOverrideLinePosMode; external dll_name name 'AxmMotSetOverrideLinePosMode';
    function AxmMotGetOverrideLinePosMode; external dll_name name 'AxmMotGetOverrideLinePosMode';
    function AxmMoveStartPosEx; external dll_name name 'AxmMoveStartPosEx';
    function AxmMovePosEx; external dll_name name 'AxmMovePosEx';
    function AxmMoveCoordStop; external dll_name name 'AxmMoveCoordStop';
    function AxmMoveCoordEStop; external dll_name name 'AxmMoveCoordEStop';
    function AxmMoveCoordSStop; external dll_name name 'AxmMoveCoordSStop';
    function AxmOverrideLinePos; external dll_name name 'AxmOverrideLinePos';
    function AxmOverrideLineVel; external dll_name name 'AxmOverrideLineVel';
    function AxmOverrideLineAccelVelDecel; external dll_name name 'AxmOverrideLineAccelVelDecel';
    function AxmOverrideAccelVelDecelAtPos; external dll_name name 'AxmOverrideAccelVelDecelAtPos';
    function AxmEGearSet; external dll_name name 'AxmEGearSet';
    function AxmEGearGet; external dll_name name 'AxmEGearGet';
    function AxmEGearReset; external dll_name name 'AxmEGearReset';
    function AxmEGearEnable; external dll_name name 'AxmEGearEnable';
    function AxmEGearIsEnable; external dll_name name 'AxmEGearIsEnable';
    function AxmMotSetEndVel; external dll_name name 'AxmMotSetEndVel';
    function AxmMotGetEndVel; external dll_name name 'AxmMotGetEndVel';
       
end.
