/****************************************************************************
*****************************************************************************
**
** File Name
** ---------
**
** AXM.CS
**
** COPYRIGHT (c) AJINEXTEK Co., LTD
**
*****************************************************************************
*****************************************************************************
**
** Description
** -----------
** Ajinextek Motion Library Header File
** 
**
*****************************************************************************
*****************************************************************************
**
** Source Change IndicesAxmStatusGetCmdPos
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

public class CAXM
{
    //========== ���� �� ��� Ȯ���Լ�(Info) - Infomation ===============================================================
    // �ش� ���� �����ȣ, ��� ��ġ, ��� ���̵� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmInfoGetAxis(int nAxisNo, ref int npBoardNo, ref int npModulePos, ref uint upModuleID);
    // ��� ����� �����ϴ��� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmInfoIsMotionModule(ref uint upStatus);
    // �ش� ���� ��ȿ���� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmInfoIsInvalidAxisNo(int nAxisNo);
    // �ش� ���� ��� ������ �������� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmInfoGetAxisStatus(int nAxisNo);
    // �� ����, �ý��ۿ� ������ ��ȿ�� ��� ����� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmInfoGetAxisCount(ref int npAxisCount);
    // �ش� ����/����� ù��° ���ȣ�� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmInfoGetFirstAxisNo(int nBoardNo, int nModulePos, ref int npAxisNo);
    // �ش� ������ ù��° ���ȣ�� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmInfoGetBoardFirstAxisNo(int lBoardNo, int lModulePos, ref int lpAxisNo);

    //========= ���� �� �Լ� ============================================================================================
    // �ʱ� ���¿��� AXM ��� �Լ��� ���ȣ ������ 0 ~ (���� �ý��ۿ� ������ ��� - 1) �������� ��ȿ������
    // �� �Լ��� ����Ͽ� ���� ������ ���ȣ ��� ������ ���ȣ�� �ٲ� �� �ִ�.
    // �� �Լ��� ���� �ý����� H/W ������� �߻��� ���� ���α׷��� �Ҵ�� ���ȣ�� �״�� �����ϰ� ���� ���� ���� 
    // �������� ��ġ�� �����Ͽ� ����� ���� ������� �Լ��̴�.
    // ���ǻ��� : ���� ���� ���� ���ȣ�� ���Ͽ� ���� ��ȣ�� ���� ���� �ߺ��ؼ� ������ ��� 
    //            ���� ���ȣ�� ���� �ุ ���� ���ȣ�� ���� �� �� ������, 
    //            ������ ���� ������ ��ȣ�� ���ε� ���� ��� �Ұ����� ��찡 �߻� �� �� �ִ�.

    // �������� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmVirtualSetAxisNoMap(int nRealAxisNo, int nVirtualAxisNo);
    // ������ ����ä��(��) ��ȣ�� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmVirtualGetAxisNoMap(int nRealAxisNo, ref int npVirtualAxisNo);
    // ��Ƽ �������� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmVirtualSetMultiAxisNoMap(int nSize, int[] npRealAxesNo, int[] npVirtualAxesNo);
    // ������ ��Ƽ ����ä��(��) ��ȣ�� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmVirtualGetMultiAxisNoMap(int nSize, ref int npRealAxesNo, ref int npVirtualAxesNo);
    // ������ ������ �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmVirtualResetAxisMap();

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
    //    wMsg    : ������ �ڵ��� �޼���, ������� �ʰų� ����Ʈ���� ����Ϸ��� 0�� �Է�.
    //    proc    : ���ͷ�Ʈ �߻��� ȣ��� �Լ��� ������, ������� ������ NULL�� �Է�.
    //    pEvent  : �̺�Ʈ ������� �̺�Ʈ �ڵ�
    [DllImport("AXL.dll")] public static extern uint AxmInterruptSetAxis(int nAxisNo, uint hWnd, uint uMessage, CAXHS.AXT_INTERRUPT_PROC pProc, ref uint pEvent);

    // ���� ���� ���ͷ�Ʈ ��� ���θ� �����Ѵ�
    // �ش� �࿡ ���ͷ�Ʈ ���� / Ȯ��
    // uUse : ��� ���� => DISABLE(0), ENABLE(1)
    [DllImport("AXL.dll")] public static extern uint AxmInterruptSetAxisEnable(int nAxisNo, uint uUse);
    // ���� ���� ���ͷ�Ʈ ��� ���θ� ��ȯ�Ѵ�
    [DllImport("AXL.dll")] public static extern uint AxmInterruptGetAxisEnable(int nAxisNo, ref uint upUse);

    //���ͷ�Ʈ�� �̺�Ʈ ������� ����� ��� �ش� ���ͷ�Ʈ ���� �д´�.
    [DllImport("AXL.dll")] public static extern uint AxmInterruptRead(ref int npAxisNo, ref uint upFlag);

    // �ش� ���� ���ͷ�Ʈ �÷��� ���� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmInterruptReadAxisFlag(int nAxisNo, int nBank, ref uint upFlag);

    // ���� ���� ����ڰ� ������ ���ͷ�Ʈ �߻� ���θ� �����Ѵ�.
    // lBank         : ���ͷ�Ʈ ��ũ ��ȣ (0 - 1) ��������.
    // uInterruptNum : ���ͷ�Ʈ ��ȣ ���� ��Ʈ��ȣ�� ���� hex�� Ȥ�� define�Ȱ��� ����
    // AXHS.h���Ͽ� INTERRUPT_BANK1, 2 DEF�� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmInterruptSetUserEnable(int nAxisNo, int lBank, uint uInterruptNum);

    // ���� ���� ����ڰ� ������ ���ͷ�Ʈ �߻� ���θ� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmInterruptGetUserEnable(int nAxisNo, int lBank, ref uint upInterruptNum);

    //======== ��� �Ķ��Ÿ ���� =======================================================================================
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
    [DllImport("AXL.dll")] public static extern uint AxmMotLoadParaAll(string szFilePath);
    // ����࿡ ���� ��� �Ķ��Ÿ�� �ະ�� �����Ѵ�. .mot���Ϸ� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMotSaveParaAll(string szFilePath);

    // �Ķ��Ÿ 28 - 31������ ����ڰ� ���α׷�������  �� �Լ��� �̿��� ���� �Ѵ�
    [DllImport("AXL.dll")] public static extern uint AxmMotSetParaLoad(int nAxisNo, double InitPos, double InitVel, double InitAccel, double InitDecel);
    // �Ķ��Ÿ 28 - 31������ ����ڰ� ���α׷�������  �� �Լ��� �̿��� Ȯ�� �Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMotGetParaLoad(int nAxisNo, ref double InitPos, ref double InitVel, ref double InitAccel, ref double InitDecel);

    // ���� ���� �޽� ��� ����� �����Ѵ�.
    // uMethod  0 :OneHighLowHigh, 1 :OneHighHighLow, 2 :OneLowLowHigh, 3 :OneLowHighLow, 4 :TwoCcwCwHigh
    //          5 :TwoCcwCwLow, 6 :TwoCwCcwHigh, 7 :TwoCwCcwLow, 8 :TwoPhase, 9 :TwoPhaseReverse
    //        OneHighLowHigh                = 0x0,                    // 1�޽� ���, PULSE(Active High), ������(DIR=Low)  / ������(DIR=High)
    //        OneHighHighLow                = 0x1,                    // 1�޽� ���, PULSE(Active High), ������(DIR=High) / ������(DIR=Low)
    //        OneLowLowHigh                 = 0x2,                    // 1�޽� ���, PULSE(Active Low),  ������(DIR=Low)  / ������(DIR=High)
    //        OneLowHighLow                 = 0x3,                    // 1�޽� ���, PULSE(Active Low),  ������(DIR=High) / ������(DIR=Low)
    //        TwoCcwCwHigh                  = 0x4,                    // 2�޽� ���, PULSE(CCW:������),  DIR(CW:������),  Active High
    //        TwoCcwCwLow                   = 0x5,                    // 2�޽� ���, PULSE(CCW:������),  DIR(CW:������),  Active Low
    //        TwoCwCcwHigh                  = 0x6,                    // 2�޽� ���, PULSE(CW:������),   DIR(CCW:������), Active High
    //        TwoCwCcwLow                   = 0x7,                    // 2�޽� ���, PULSE(CW:������),   DIR(CCW:������), Active Low
    //        TwoPhase                      = 0x8,                    // 2��(90' ������),  PULSE lead DIR(CW: ������), PULSE lag DIR(CCW:������)
    //        TwoPhaseReverse               = 0x9                     // 2��(90' ������),  PULSE lead DIR(CCW: ������), PULSE lag DIR(CW:������)
    [DllImport("AXL.dll")] public static extern uint AxmMotSetPulseOutMethod(int nAxisNo, uint uMethod);
    // ���� ���� �޽� ��� ��� ������ ��ȯ�Ѵ�,
    [DllImport("AXL.dll")] public static extern uint AxmMotGetPulseOutMethod(int nAxisNo, ref uint upMethod);

    // ���� ���� �ܺ�(Actual) ī��Ʈ�� ���� ���� ������ �����Ͽ� ���� ���� Encoder �Է� ����� �����Ѵ�.
    // uMethod : 0 - 7 ����.
    //        ObverseUpDownMode             = 0x0,                     // ������ Up/Down
    //        ObverseSqr1Mode               = 0x1,                     // ������ 1ü��
    //        ObverseSqr2Mode               = 0x2,                     // ������ 2ü��
    //        ObverseSqr4Mode               = 0x3,                     // ������ 4ü��
    //        ReverseUpDownMode             = 0x4,                     // ������ Up/Down
    //        ReverseSqr1Mode               = 0x5,                     // ������ 1ü��
    //        ReverseSqr2Mode               = 0x6,                     // ������ 2ü��
    //        ReverseSqr4Mode               = 0x7                      // ������ 4ü��
    [DllImport("AXL.dll")] public static extern uint AxmMotSetEncInputMethod(int nAxisNo, uint uMethod);
    // ���� ���� �ܺ�(Actual) ī��Ʈ�� ���� ���� ������ �����Ͽ� ���� ���� Encoder �Է� ����� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMotGetEncInputMethod(int nAxisNo, ref uint upMethod);

    // ���� �ӵ� ������ RPM(Revolution Per Minute)���� ���߰� �ʹٸ�.
    // ex>        rpm ���:
    // 4500 rpm ?
    // unit/ pulse = 1 : 1�̸�      pulse/ sec �ʴ� �޽����� �Ǵµ�
    // 4500 rpm�� ���߰� �ʹٸ�     4500 / 60 �� : 75ȸ��/ 1��
    // ���Ͱ� 1ȸ���� �� �޽����� �˾ƾ� �ȴ�. �̰��� Encoder�� Z���� �˻��غ��� �˼��ִ�.
    // 1ȸ��:1800 �޽���� 75 x 1800 = 135000 �޽��� �ʿ��ϰ� �ȴ�.
    // AxmMotSetMoveUnitPerPulse�� Unit = 1, Pulse = 1800 �־� ���۽�Ų��.
    // �������� : rpm���� �����ϰ� �ȴٸ� �ӵ��� ���ӵ� �� rpm������ �ٲ�� �ȴ�.

    // ���� ���� �޽� �� �����̴� �Ÿ��� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMotSetMoveUnitPerPulse(int nAxisNo, double dUnit, int nPulse);
    // ���� ���� �޽� �� �����̴� �Ÿ��� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMotGetMoveUnitPerPulse(int nAxisNo, ref double dpUnit, ref int npPulse);

    // ���� �࿡ ���� ���� ����Ʈ ���� ����� �����Ѵ�.
    // uMethod : 0 -1 ����
    // AutoDetect = 0x0 : �ڵ� ������.
    // RestPulse  = 0x1 : ���� ������.
    [DllImport("AXL.dll")] public static extern uint AxmMotSetDecelMode(int nAxisNo, uint uMethod);
    // ���� ���� ���� ���� ����Ʈ ���� ����� ��ȯ�Ѵ�        
    [DllImport("AXL.dll")] public static extern uint AxmMotGetDecelMode(int nAxisNo, ref uint upMethod);

    // ���� �࿡ ���� ���� ��忡�� �ܷ� �޽��� �����Ѵ�.
    // �����: ���� AxmMotSetRemainPulse�� 500 �޽��� ����
    //           AxmMoveStartPos�� ��ġ 10000�� ��������쿡 9500�޽����� 
    //           ���� �޽� 500��  AxmMotSetMinVel�� ������ �ӵ��� �����ϸ鼭 ���� �ȴ�.
    [DllImport("AXL.dll")] public static extern uint AxmMotSetRemainPulse(int nAxisNo, uint uData);
    // ���� ���� ���� ���� ��忡�� �ܷ� �޽��� ��ȯ�Ѵ�.        
    [DllImport("AXL.dll")] public static extern uint AxmMotGetRemainPulse(int nAxisNo, ref uint upData);

    // ���� �࿡ ��ӵ� ���� �Լ������� �ְ� �ӵ��� �����Ѵ�.
    // ���ǻ��� : �Է� �ִ� �ӵ� ���� PPS�� �ƴ϶� UNIT �̴�.
    // ex) �ִ� ��� ���ļ�(PCI-N804/404 : 10 MPPS)
    // ex) �ִ� ��� Unit/Sec(PCI-N804/404 : 10MPPS * Unit/Pulse)
    [DllImport("AXL.dll")] public static extern uint AxmMotSetMaxVel(int nAxisNo, double dVel);
    // ���� ���� ��ӵ� ���� �Լ������� �ְ� �ӵ��� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMotGetMaxVel(int nAxisNo, ref double dpVel);

    // ���� ���� �̵� �Ÿ� ��� ��带 �����Ѵ�.
    // uAbsRelMode : POS_ABS_MODE '0' - ���� ��ǥ��
    //               POS_REL_MODE '1' - ��� ��ǥ��
    [DllImport("AXL.dll")] public static extern uint AxmMotSetAbsRelMode(int nAxisNo, uint uAbsRelMode);
    // ���� ���� ������ �̵� �Ÿ� ��� ��带 ��ȯ�Ѵ�
    [DllImport("AXL.dll")] public static extern uint AxmMotGetAbsRelMode(int nAxisNo, ref uint upAbsRelMode);

    // ���� ���� ���� �ӵ� �������� ��带 �����Ѵ�.
    // ProfileMode : SYM_TRAPEZOIDE_MODE    '0' - ��Ī Trapezode
    //               ASYM_TRAPEZOIDE_MODE   '1' - ���Ī Trapezode
    //               QUASI_S_CURVE_MODE     '2' - ��Ī Quasi-S Curve
    //               SYM_S_CURVE_MODE       '3' - ��Ī S Curve
    //               ASYM_S_CURVE_MODE      '4' - ���Ī S Curve
    //               SYM_TRAP_M3_SW_MODE    '5' - ��Ī Trapezode : MLIII ���� S/W Profile
    //               ASYM_TRAP_M3_SW_MODE   '6' - ���Ī Trapezode : MLIII ���� S/W Profile
    //               SYM_S_M3_SW_MODE       '7' - ��Ī S Curve : MLIII ���� S/W Profile
    //               ASYM_S_M3_SW_MODE      '8' - asymmetric S Curve : MLIII ���� S/W Profile
    [DllImport("AXL.dll")] public static extern uint AxmMotSetProfileMode(int lAxisNo, uint uProfileMode);
    // ���� ���� ������ ���� �ӵ� �������� ��带 ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMotGetProfileMode(int nAxisNo, ref uint upProfileMode);

    // ���� ���� ���ӵ� ������ �����Ѵ�.
    // AccelUnit : UNIT_SEC2   '0' - ������ ������ unit/sec2 ���
    //             SEC         '1' - ������ ������ sec ���
    [DllImport("AXL.dll")] public static extern uint AxmMotSetAccelUnit(int nAxisNo, uint uAccelUnit);
    // ���� ���� ������ ���ӵ������� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMotGetAccelUnit(int nAxisNo, ref uint upAccelUnit);

    // ���ǻ���: �ּҼӵ��� UNIT/PULSE ���� �۰��� ��� �ּҴ����� UNIT/PULSE�� ���߾����⶧���� �ּ� �ӵ��� UNIT/PULSE �� �ȴ�.
    // ���� �࿡ �ʱ� �ӵ��� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMotSetMinVel(int nAxisNo, double dMinVelocity);
    // ���� ���� �ʱ� �ӵ��� ��ȯ�Ѵ�
    [DllImport("AXL.dll")] public static extern uint AxmMotGetMinVel(int nAxisNo, ref double dpMinVelocity);

    // ���� ���� ���� ��ũ���� �����Ѵ�.[%].
    [DllImport("AXL.dll")] public static extern uint AxmMotSetAccelJerk(int nAxisNo, double dAccelJerk);
    // ���� ���� ������ ���� ��ũ���� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMotGetAccelJerk(int nAxisNo, ref double dpAccelJerk);

    // ���� ���� ���� ��ũ���� �����Ѵ�.[%].
    [DllImport("AXL.dll")] public static extern uint AxmMotSetDecelJerk(int nAxisNo, double dDecelJerk);
    // ���� ���� ������ ���� ��ũ���� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMotGetDecelJerk(int nAxisNo, ref double dpDecelJerk);

    // ���� ���� �ӵ� Profile������ �켱����(�ӵ� Or ���ӵ�)�� �����Ѵ�.
    // Priority : PRIORITY_VELOCITY   '0' - �ӵ� Profile������ ������ �ӵ����� �������� �����(�Ϲ���� �� Spinner�� ���).
    //            PRIORITY_ACCELTIME  '1' - �ӵ� Profile������ ������ �����ӽð��� �������� �����(��� ��� ���).
    [DllImport("AXL.dll")] public static extern uint AxmMotSetProfilePriority(int nAxisNo, uint uPriority);
    // ���� ���� �ӵ� Profile������ �켱����(�ӵ� Or ���ӵ�)�� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMotGetProfilePriority(int nAxisNo, ref uint upPriority);

    //=========== ����� ��ȣ ���� �����Լ� =============================================================================
    // ���� ���� Z �� Level�� �����Ѵ�.
    // uLevel : LOW(0), HIGH(1)
    [DllImport("AXL.dll")] public static extern uint AxmSignalSetZphaseLevel(int nAxisNo, uint uLevel);
    // ���� ���� Z �� Level�� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmSignalGetZphaseLevel(int nAxisNo, ref uint upLevel);

    // ���� ���� Servo-On��ȣ�� ��� ������ �����Ѵ�.
    // uLevel : LOW(0), HIGH(1)
    [DllImport("AXL.dll")] public static extern uint AxmSignalSetServoOnLevel(int nAxisNo, uint uLevel);
    // ���� ���� Servo-On��ȣ�� ��� ���� ������ ��ȯ�Ѵ�.        
    [DllImport("AXL.dll")] public static extern uint AxmSignalGetServoOnLevel(int nAxisNo, ref uint upLevel);

    // ���� ���� Servo-Alarm Reset ��ȣ�� ��� ������ �����Ѵ�.
    // uLevel : LOW(0), HIGH(1)
    [DllImport("AXL.dll")] public static extern uint AxmSignalSetServoAlarmResetLevel(int nAxisNo, uint uLevel);
    // ���� ���� Servo-Alarm Reset ��ȣ�� ��� ������ ������ ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmSignalGetServoAlarmResetLevel(int nAxisNo, ref uint upLevel);

    // ���� ���� Inpositon ��ȣ ��� ���� �� ��ȣ �Է� ������ �����Ѵ�
    // uLevel : LOW(0), HIGH(1), UNUSED(2), USED(3)        
    [DllImport("AXL.dll")] public static extern uint AxmSignalSetInpos(int nAxisNo, uint uUse);
    // ���� ���� Inpositon ��ȣ ��� ���� �� ��ȣ �Է� ������ ��ȯ�Ѵ�.        
    [DllImport("AXL.dll")] public static extern uint AxmSignalGetInpos(int nAxisNo, ref uint upUse);
    // ���� ���� Inpositon ��ȣ �Է� ���¸� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmSignalReadInpos(int nAxisNo, ref uint upStatus);

    // ���� ���� �˶� ��ȣ �Է� �� ��� ������ ��� ���� �� ��ȣ �Է� ������ �����Ѵ�.
    // uLevel : LOW(0), HIGH(1), UNUSED(2), USED(3)
    [DllImport("AXL.dll")] public static extern uint AxmSignalSetServoAlarm(int nAxisNo, uint uUse);
    // ���� ���� �˶� ��ȣ �Է� �� ��� ������ ��� ���� �� ��ȣ �Է� ������ ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmSignalGetServoAlarm(int nAxisNo, ref uint upUse);
    // ���� ���� �˶� ��ȣ�� �Է� ������ ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmSignalReadServoAlarm(int nAxisNo, ref uint upStatus);

    // ���� ���� end limit sensor�� ��� ���� �� ��ȣ�� �Է� ������ �����Ѵ�. 
    // end limit sensor ��ȣ �Է� �� �������� �Ǵ� �������� ���� ������ �����ϴ�.
    // uStopMode: EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
    // uPositiveLevel, uNegativeLevel : LOW(0), HIGH(1), UNUSED(2), USED(3)
    [DllImport("AXL.dll")] public static extern uint AxmSignalSetLimit(int nAxisNo, uint uStopMode, uint uPositiveLevel, uint uNegativeLevel);
    // ���� ���� end limit sensor�� ��� ���� �� ��ȣ�� �Է� ����, ��ȣ �Է� �� ������带 ��ȯ�Ѵ�
    [DllImport("AXL.dll")] public static extern uint AxmSignalGetLimit(int nAxisNo, ref uint upStopMode, ref uint upPositiveLevel, ref uint upNegativeLevel);
    // �������� end limit sensor�� �Է� ���¸� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmSignalReadLimit(int nAxisNo, ref uint upPositiveStatus, ref uint upNegativeStatus);

    // ���� ���� Software limit�� ��� ����, ����� ī��Ʈ, �׸��� ���� ����� �����Ѵ�
    // uUse       : DISABLE(0), ENABLE(1)
    // uStopMode  : EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
    // uSelection : COMMAND(0), ACTUAL(1)
    // ���ǻ���: �����˻��� �� �Լ��� �̿��Ͽ� ����Ʈ���� ������ �̸� �����ؼ� ������ �����˻��� �����˻��� ���߿� ���߾�������쿡��  Enable�ȴ�. 
    [DllImport("AXL.dll")] public static extern uint AxmSignalSetSoftLimit(int nAxisNo, uint uUse, uint uStopMode, uint uSelection, double dPositivePos, double dNegativePos);
    // ���� ���� Software limit�� ��� ����, ����� ī��Ʈ, �׸��� ���� ����� ��ȯ�Ѵ�
    [DllImport("AXL.dll")] public static extern uint AxmSignalGetSoftLimit(int nAxisNo, ref uint upUse, ref uint upStopMode, ref uint upSelection, ref double dpPositivePos, ref double dpNegativePos);
    // ���� ���� Software limit�� ���� ���¸� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmSignalReadSoftLimit(int nAxisNo, ref uint upPositiveStatus, ref uint upNegativeStatus);

    // ��� ���� ��ȣ�� ���� ��� (������/��������) �Ǵ� ��� ������ �����Ѵ�.
    // uStopMode  : EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
    // uLevel : LOW(0), HIGH(1), UNUSED(2), USED(3)
    [DllImport("AXL.dll")] public static extern uint AxmSignalSetStop(int nAxisNo, uint uStopMode, uint uLevel);
    // ��� ���� ��ȣ�� ���� ��� (������/��������) �Ǵ� ��� ������ ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmSignalGetStop(int nAxisNo, ref uint upStopMode, ref uint upLevel);
    // ��� ���� ��ȣ�� �Է� ���¸� ��ȯ�Ѵ�.        
    [DllImport("AXL.dll")] public static extern uint AxmSignalReadStop(int nAxisNo, ref uint upStatus);

    // ���� ���� Servo-On ��ȣ�� ����Ѵ�.
    // uOnOff : FALSE(0), TRUE(1) ( ���� 0��¿� �ش��)
    [DllImport("AXL.dll")] public static extern uint AxmSignalServoOn(int nAxisNo, uint uOnOff);
    // ���� ���� Servo-On ��ȣ�� ��� ���¸� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmSignalIsServoOn(int nAxisNo, ref uint upOnOff);

    // ���� ���� Servo-Alarm Reset ��ȣ�� ����Ѵ�.
    // uOnOff : FALSE(0), TRUE(1) ( ���� 1��¿� �ش��)
    [DllImport("AXL.dll")] public static extern uint AxmSignalServoAlarmReset(int nAxisNo, uint uOnOff);

    // ���� ��°��� �����Ѵ�.
    // uValue : Hex Value 0x00
    [DllImport("AXL.dll")] public static extern uint AxmSignalWriteOutput(int nAxisNo, uint uValue);
    // ���� ��°��� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmSignalReadOutput(int nAxisNo, ref uint upValue);

    // lBitNo : Bit Number(0 - 4)
    // uOnOff : FALSE(0), TRUE(1)
    // ���� ��°��� ��Ʈ���� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmSignalWriteOutputBit(int nAxisNo, int nBitNo, uint uOn);
    // ���� ��°��� ��Ʈ���� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmSignalReadOutputBit(int nAxisNo, int nBitNo, ref uint upOn);

    // ���� �Է°��� Hex������ ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmSignalReadInput(int nAxisNo, ref uint upValue);

    // lBitNo : Bit Number(0 - 4)
    // ���� �Է°��� ��Ʈ���� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmSignalReadInputBit(int nAxisNo, int nBitNo, ref uint upOn);

    // �Է½�ȣ���� ������ ���Ͱ���� �����Ѵ�.
    // uSignal: END_LIMIT(0), INP_ALARM(1), UIN_00_01(2), UIN_02_04(3)
    // dBandwidthUsec: 0.2uSec~26666usec
    [DllImport("AXL.dll")] public static extern uint AxmSignalSetFilterBandwidth(int nAxisNo, uint uSignal, double dBandwidthUsec);

    //========== ��� ������ �� �����Ŀ� ���� Ȯ���ϴ� �Լ�======================================================
    // (��������)��� ���� ���ΰ��� Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxmStatusReadInMotion(int nAxisNo, ref uint upStatus);

    //  (�޽� ī��Ʈ ��)�������� ���� ��µ� �޽� ī���� ���� Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxmStatusReadDrivePulseCount(int nAxisNo, ref int npPulse);

    // DriveStatus �������͸� Ȯ��
    // ���ǻ��� : �� ��ǰ���� �ϵ�������� ��ȣ�� �ٸ��⶧���� �Ŵ��� �� AXHS.xxx ������ �����ؾ��Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmStatusReadMotion(int nAxisNo, ref uint upStatus);

    // EndStatus �������͸� Ȯ��
    // ���ǻ��� : �� ��ǰ���� �ϵ�������� ��ȣ�� �ٸ��⶧���� �Ŵ��� �� AXHS.xxx ������ �����ؾ��Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmStatusReadStop(int nAxisNo, ref uint upStatus);

    // Mechanical �������͸� Ȯ��
    // ���ǻ��� : �� ��ǰ���� �ϵ�������� ��ȣ�� �ٸ��⶧���� �Ŵ��� �� AXHS.xxx ������ �����ؾ��Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmStatusReadMechanical(int nAxisNo, ref uint upStatus);

    // ���� �ӵ��� �о� �´�
    [DllImport("AXL.dll")] public static extern uint AxmStatusReadVel(int nAxisNo, ref double dpVelocity);

    // Command Pos�� Actual Pos�� ���� Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxmStatusReadPosError(int nAxisNo, ref double dpError);

    // ���� ����̺��� �̵� �Ÿ��� Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxmStatusReadDriveDistance(int nAxisNo, ref double dpUnit);

    // ���� ���� ��ġ ���� ��� ����� ���Ͽ� �����Ѵ�.
    // uPosType  : Actual position �� Command position �� ǥ�� ���
    //    POSITION_LIMIT '0' - �⺻ ����, ��ü ���� ������ ����
    //    POSITION_BOUND '1' - ��ġ ���� �ֱ���, dNegativePos ~ dPositivePos ������ ����
    // ���ǻ���(PCI-Nx04�ش�)
    // - BOUNT������ ī��Ʈ ���� Max���� �ʰ� �� �� Min���̵Ǹ� �ݴ�� Min���� �ʰ� �� �� Max���� �ȴ�.
    // - �ٽø��� ���� ��ġ���� ������ �� �ۿ��� ī��Ʈ �� ���� ���� Min, Max���� ������� �ʴ´�.
    [DllImport("AXL.dll")] public static extern uint AxmStatusSetPosType(int nAxisNo, uint uPosType, double dPositivePos, double dNegativePos);
    // ���� ���� ��ġ ���� ��� ����� ���Ͽ� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmStatusGetPosType(int nAxisNo, ref uint upPosType, ref double dpPositivePos, ref double dpNegativePos);
    // ���� ���� ����ġ ���ڴ� ���� Offset ��ġ�� �����Ѵ�.[PCI-R1604-MLII ����]
    [DllImport("AXL.dll")] public static extern uint AxmStatusSetAbsOrgOffset(int nAxisNo, double dOrgOffsetPos);

    // ���� ���� Actual ��ġ�� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmStatusSetActPos(int nAxisNo, double dPos);
    // ���� ���� Actual ��ġ�� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmStatusGetActPos(int nAxisNo, ref double dpPos);

    // ���� ���� Command ��ġ�� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmStatusSetCmdPos(int nAxisNo, double dPos);
    // ���� ���� Command ��ġ�� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmStatusGetCmdPos(int nAxisNo, ref double dpPos);
    // ���� ���� Command ��ġ�� Actual ��ġ�� dPos ������ ��ġ ��Ų��.
    [DllImport("AXL.dll")] public static extern uint AxmStatusSetPosMatch(int nAxisNo, double dPos);

    // ���� ���� ��� ����(Cmd, Act, Driver Status, Mechanical Signal, Universal Signal)�� �ѹ��� Ȯ�� �� �� �ִ�.
    // MOTION_INFO ����ü�� uMask �������� ��� ���� ������ �����Ѵ�.
    // uMask : ��� ���� ǥ��(6bit) - ex) uMask = 0x1F ���� �� ��� ���¸� ǥ����.
    // ����ڰ� ������ Level(In/Out)�� �ݿ����� ����.
    //    [0]        |    Command Position Read
    //    [1]        |    Actual Position Read
    //    [2]        |    Mechanical Signal Read
    //    [3]        |    Driver Status Read
    //    [4]        |    Universal Signal Input Read
    //               |    Universal Signal Output Read
    [DllImport("AXL.dll")] public static extern uint AxmStatusReadMotionInfo(int nAxisNo, ref MOTION_INFO MI);

    // Network ��ǰ �����Լ�.
    // ������ ���� �����ѿ� AlarmCode�� �о������ ����ϴ� �Լ�.
    [DllImport("AXL.dll")] public static extern uint AxmStatusRequestServoAlarm(int nAxisNo);
    // ������ ���� ������ AlarmCode�� �о���� �Լ�.
    // upAlarmCode      : �ش� �������� Alarm Code����
    // MR_J4_xxB  : ���� 16Bit : �˶��ڵ� 2 digit�� 10���� ��, ���� 16Bit : �˶� �� �ڵ� 1 digit 10���� ��
    // uReturnMode      : �Լ��� ��ȯ ���������� ����[SIIIH(MR-J4-xxB)�� ������� ����]
    // [0-Immediate]    : �Լ� ���� �� �ٷ� ��ȯ
    // [1-Blocking]     : ���������� ���� �˶� �ڵ带 ���� �� ���� ��ȯ��������
    // [2-Non Blocking] : ���������� ���� �˶� �ڵ带 ���� �� ���� ��ȯ���������� ���α׷� Blocking��������
    [DllImport("AXL.dll")] public static extern uint AxmStatusReadServoAlarm(int nAxisNo, uint uReturnMode, ref uint upAlarmCode);
    // ������ �����ڵ忡 �ش��ϴ� Alarm String�� �޾ƿ��� �Լ�
    [DllImport("AXL.dll")] public static extern uint AxmStatusGetServoAlarmString(int nAxisNo, uint uAlarmCode, int nAlarmStringSize, byte[] szAlarmString);

    // ������ ���� �����ѿ� Alarm History�� �о������ ����ϴ� �Լ�
    [DllImport("AXL.dll")] public static extern uint AxmStatusRequestServoAlarmHistory(int nAxisNo);
    // ������ ���� ������ Alarm History�� �о���� �Լ�.
    // lpCount          : ���� Alarm History ���� 
    // upAlarmCode      : Alarm History�� ��ȯ�� �迭
    // uReturnMode      : �Լ��� ��ȯ ���������� ����
    // [0-Immediate]    : �Լ� ���� �� �ٷ� ��ȯ
    // [1-Blocking]     : ���������� ���� �˶� �ڵ带 ���� �� ���� ����� ��ȯ��������
    // [2-Non Blocking] : ���������� ���� �˶� �ڵ带 ���� �� ���� ����� ��ȯ���������� ���α׷� Blocking��������(������ �޼��� ���ο��� ó����)
    [DllImport("AXL.dll")] public static extern uint AxmStatusReadServoAlarmHistory(int nAxisNo, uint uReturnMode, ref int npCount, ref uint upAlarmCode);
    // ������ ���� ������ Alarm History�� Clear�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmStatusClearServoAlarmHistory(int nAxisNo);

    //======== Ȩ���� �Լ�===============================================================================================
    // ���� ���� Home ���� Level �� �����Ѵ�.
    // uLevel : LOW(0), HIGH(1)
    [DllImport("AXL.dll")] public static extern uint AxmHomeSetSignalLevel(int nAxisNo, uint uLevel);
    // ���� ���� Home ���� Level �� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmHomeGetSignalLevel(int nAxisNo, ref uint upLevel);
    // ���� Ȩ ��ȣ �Է»��¸� Ȯ���Ѵ�. Ȩ��ȣ�� ����ڰ� ���Ƿ� AxmHomeSetMethod �Լ��� �̿��Ͽ� �����Ҽ��ִ�.
    // �Ϲ������� Ȩ��ȣ�� ���� �Է� 0�� ����ϰ������� AxmHomeSetMethod �̿��ؼ� �ٲٸ� + , - Limit�� ����Ҽ����ִ�.
    // upStatus : OFF(0), ON(1)
    [DllImport("AXL.dll")] public static extern uint AxmHomeReadSignal(int nAxisNo, ref uint upStatus);

    // �ش� ���� �����˻��� �����ϱ� ���ؼ��� �ݵ�� ���� �˻����� �Ķ��Ÿ���� �����Ǿ� �־�� �˴ϴ�. 
    // ���� MotionPara���� ������ �̿��� �ʱ�ȭ�� ���������� ����ƴٸ� ������ ������ �ʿ����� �ʴ�. 
    // �����˻� ��� �������� �˻� �������, �������� ����� ��ȣ, �������� Active Level, ���ڴ� Z�� ���� ���� ���� ���� �Ѵ�.
    // ���ǻ��� : ������ �߸� ������ -�������� �����ص�  +�������� �����Ҽ� ������, Ȩ�� ã�µ� �־� ������ �ɼ��ִ�.
    // (�ڼ��� ������ AxmMotSaveParaAll ���� �κ� ����)
    // Ȩ������ AxmSignalSetHomeLevel ����Ѵ�.
    // HClrTim : HomeClear Time : ���� �˻� Encoder �� Set�ϱ� ���� ���ð� 
    // HmDir(Ȩ ����): DIR_CCW (0) -���� , DIR_CW(1) +����
    // HOffset - ���������� �̵��Ÿ�.
    // uZphas: 1�� �����˻� �Ϸ� �� ���ڴ� Z�� ���� ���� ����  0: ������ , 1: Hmdir�� �ݴ� ����, 2: Hmdir�� ���� ����
    // HmSig : PosEndLimit(0) -> +Limit
    //         NegEndLimit(1) -> -Limit
    //         HomeSensor (4) -> ��������(���� �Է� 0)
    [DllImport("AXL.dll")] public static extern uint AxmHomeSetMethod(int nAxisNo, int nHmDir, uint uHomeSignal, uint uZphas, double dHomeClrTime, double dHomeOffset);
    // �����Ǿ��ִ� Ȩ ���� �Ķ��Ÿ���� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmHomeGetMethod(int nAxisNo, ref int nHmDir, ref uint uHomeSignal, ref uint uZphas, ref double dHomeClrTime, ref double dHomeOffset);

    // �����˻� ����� �̼������� �ϴ� �Լ�(�⺻������ �������� �ʾƵ���).
    // dHomeDogDistance[500 pulse]: ù��° Step���� HomeDog�� ������ �����ƴ��� Ȯ���ϱ����� Dog���̸� �Է�.(������ AxmMotSetMoveUnitPerPulse�Լ��� ������ ����)
    // lLevelScanTime[100msec]: 2��° Step(���������� ���������� ����)���� Level���¸� Ȯ���� Scan�ð��� ����(������ msec[1~1000]).
    // uFineSearchUse[USE]: �⺻ �����˻��� 5 Step�� ����ϴµ� 3 Step�� ����ϵ��� �����Ҷ� 0���� ����.
    // uHomeClrUse[USE]: �����˻� �� ���ɰ��� Encoder���� 0���� �ڵ� �������θ� ����.
    [DllImport("AXL.dll")] public static extern uint AxmHomeSetFineAdjust(int nAxisNo, double dHomeDogLength, uint lLevelScanTime, uint uFineSearchUse, uint uHomeClrUse);
    // �����Ǿ��ִ� Ȩ ���� �̼����� �Ķ��Ÿ���� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmHomeGetFineAdjust(int nAxisNo, ref double dpHomeDogLength, ref uint lpLevelScanTime, ref uint upFineSearchUse, ref uint upHomeClrUse);

    // ������ ������ �����ϰ� �˻��ϱ� ���� ���� �ܰ��� �������� �����Ѵ�. �̶� �� ���ǿ� ��� �� �ӵ��� �����Ѵ�. 
    // �� �ӵ����� �������� ���� �����˻� �ð���, �����˻� ���е��� �����ȴ�. 
    // �� ���Ǻ� �ӵ����� ������ �ٲ㰡�鼭 �� ���� �����˻� �ӵ��� �����ϸ� �ȴ�. 
    // (�ڼ��� ������ AxmMotSaveParaAll ���� �κ� ����)
    // �����˻��� ���� �ӵ��� �����ϴ� �Լ�
    // [dVelFirst]- 1�������ӵ�   [dVelSecond]-�����ļӵ�   [dVelThird]- ������ �ӵ�  [dvelLast]- index�˻��� �����ϰ� �˻��ϱ�����. 
    // [dAccFirst]- 1���������ӵ� [dAccSecond]-�����İ��ӵ� 
    [DllImport("AXL.dll")] public static extern uint AxmHomeSetVel(int nAxisNo, double dVelFirst, double dVelSecond, double dVelThird, double dvelLast, double dAccFirst, double dAccSecond);
    // �����Ǿ��ִ� �����˻��� ���� �ӵ��� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmHomeGetVel(int nAxisNo, ref double dVelFirst, ref double dVelSecond, ref double dVelThird, ref double dvelLast, ref double dAccFirst, ref double dAccSecond);

    // �����˻��� �����Ѵ�.
    // �����˻� �����Լ��� �����ϸ� ���̺귯�� ���ο��� �ش����� �����˻��� ���� �� �����尡 �ڵ� �����Ǿ� �����˻��� ���������� ������ �� �ڵ� ����ȴ�.
    // ���ǻ��� : �������� �ݴ������ ����Ʈ ������ ���͵� ��������� ������ ACTIVE���������� �����Ѵ�.
    //            ���� �˻��� ���۵Ǿ� ��������� ����Ʈ ������ ������ ����Ʈ ������ �����Ǿ��ٰ� �����ϰ� �����ܰ�� ����ȴ�.
    [DllImport("AXL.dll")] public static extern uint AxmHomeSetStart(int nAxisNo);
    // �����˻� ����� ����ڰ� ���Ƿ� �����Ѵ�.
    // �����˻� �Լ��� �̿��� ���������� �����˻��� ����ǰ��� �˻� ����� HOME_SUCCESS�� �����˴ϴ�.
    // �� �Լ��� ����ڰ� �����˻��� ���������ʰ� ����� ���Ƿ� ������ �� �ִ�. 
    // uHomeResult ����
    // HOME_SUCCESS                             = 0x01        // Ȩ �Ϸ�
    // HOME_SEARCHING                           = 0x02        // Ȩ�˻���
    // HOME_ERR_GNT_RANGE                       = 0x10        // Ȩ �˻� ������ ��������
    // HOME_ERR_USER_BREAK                      = 0x11        // �ӵ� ������ ���Ƿ� ��������� ���������
    // HOME_ERR_VELOCITY                        = 0x12        // �ӵ� ���� �߸��������
    // HOME_ERR_AMP_FAULT                       = 0x13        // ������ �˶� �߻� ����
    // HOME_ERR_NEG_LIMIT                       = 0x14        // (-)���� ������ (+)����Ʈ ���� ���� ����
    // HOME_ERR_POS_LIMIT                       = 0x15        // (+)���� ������ (-)����Ʈ ���� ���� ����
    // HOME_ERR_NOT_DETECT                      = 0x16        // ������ ��ȣ �������� �� �� ��� ����
    // HOME_ERR_UNKNOWN                         = 0xFF        
    [DllImport("AXL.dll")] public static extern uint AxmHomeSetResult(int nAxisNo, uint uHomeResult);
    // �����˻� ����� ��ȯ�Ѵ�.
    // �����˻� �Լ��� �˻� ����� Ȯ���Ѵ�. �����˻��� ���۵Ǹ� HOME_SEARCHING���� �����Ǹ� �����˻��� �����ϸ� ���п����� �����ȴ�. ���� ������ ������ �� �ٽ� �����˻��� �����ϸ� �ȴ�.
    [DllImport("AXL.dll")] public static extern uint AxmHomeGetResult(int nAxisNo, ref uint upHomeResult);

    // �����˻� ������� ��ȯ�Ѵ�.
    // �����˻� ���۵Ǹ� �������� Ȯ���� �� �ִ�. �����˻��� �Ϸ�Ǹ� �������ο� ������� 100�� ��ȯ�ϰ� �ȴ�. �����˻� �������δ� GetHome Result�Լ��� �̿��� Ȯ���� �� �ִ�.
    // upHomeMainStepNumber : Main Step �������̴�. 
    // ��Ʈ�� FALSE�� ���upHomeMainStepNumber : 0 �϶��� ������ �ุ ��������̰� Ȩ �������� upHomeStepNumber ǥ���Ѵ�.
    // ��Ʈ�� TRUE�� ��� upHomeMainStepNumber : 0 �϶��� ������ Ȩ�� ��������̰� ������ Ȩ �������� upHomeStepNumber ǥ���Ѵ�.
    // ��Ʈ�� TRUE�� ��� upHomeMainStepNumber : 10 �϶��� �����̺� Ȩ�� ��������̰� ������ Ȩ �������� upHomeStepNumber ǥ���Ѵ�.
    // upHomeStepNumber     : ������ �࿡���� �������� ǥ���Ѵ�. 
    // ��Ʈ�� FALSE�� ���  : ������ �ุ �������� ǥ���Ѵ�.
    // ��Ʈ�� TRUE�� ��� ��������, �����̺��� ������ �������� ǥ�õȴ�.
    [DllImport("AXL.dll")] public static extern uint AxmHomeGetRate(int nAxisNo, ref uint upHomeMainStepNumber, ref uint upHomeStepNumber);

    //========= ��ġ �����Լ� ===========================================================================================
    // ���ǻ���: ��ġ�� �����Ұ�� �ݵ�� UNIT/PULSE�� ���߾ �����Ѵ�.
    //           ��ġ�� UNIT/PULSE ���� �۰��� ��� �ּҴ����� UNIT/PULSE�� ���߾����⶧���� ����ġ���� ������ �ɼ�����.

    // ���� �ӵ� ������ RPM(Revolution Per Minute)���� ���߰� �ʹٸ�.
    // ex>        rpm ���:
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
    [DllImport("AXL.dll")] public static extern uint AxmMoveStartPos(int nAxisNo, double dPos, double dVel, double dAccel, double dDecel);

    // ������ �Ÿ���ŭ �Ǵ� ��ġ���� �̵��Ѵ�.
    // ���� ���� ���� ��ǥ/�����ǥ�� ������ ��ġ���� ������ �ӵ��� �������� ������ �Ѵ�.
    // �ӵ� ���������� AxmMotSetProfileMode �Լ����� �����Ѵ�. 
    // �޽� ����� ����Ǵ� �������� �Լ��� �����
    [DllImport("AXL.dll")] public static extern uint AxmMovePos(int nAxisNo, double dPos, double dVel, double dAccel, double dDecel);

    // ������ �ӵ��� �����Ѵ�.
    // ���� �࿡ ���Ͽ� ������ �ӵ��� �������� ���������� �ӵ� ��� ������ �Ѵ�. 
    // �޽� ����� ���۵Ǵ� �������� �Լ��� �����.
    // Vel���� ����̸� CW, �����̸� CCW �������� ����.
    [DllImport("AXL.dll")] public static extern uint AxmMoveVel(int nAxisNo, double dVel, double dAccel, double dDecel);

    // ������ ���࿡ ���Ͽ� ������ �ӵ��� �������� ���������� �ӵ� ��� ������ �Ѵ�.
    // �޽� ����� ���۵Ǵ� �������� �Լ��� �����.
    // Vel���� ����̸� CW, �����̸� CCW �������� ����.
    [DllImport("AXL.dll")] public static extern uint AxmMoveStartMultiVel(int lArraySize, int[] lpAxesNo, double[] dVel, double[] dAccel, double[] dDecel);

    // ������ ���࿡ ���Ͽ� ������ �ӵ��� ������, SyncMode�� ���� ���������� �ӵ� ��� ������ �Ѵ�.
    // �޽� ����� ���۵Ǵ� �������� �Լ��� �����.
    // Vel���� ����̸� CW, �����̸� CCW �������� ����.
    // uSyncMode    : ����������� ������(0), �������� ��ɸ� ���(1), �˶��� ���ؼ��� ���� ������ ���(2)
    [DllImport("AXL.dll")] public static extern uint AxmMoveStartMultiVelEx(int lArraySize, int[] lpAxesNo, double[] dpVel, double[] dpAccel, double[] dpDecel, uint uSyncMode);

    // ������ ���࿡ ���Ͽ� ������ �ӵ��� �������� ���������� �ӵ� ��� ������ �Ѵ�.
    // �޽� ����� ���۵Ǵ� �������� �Լ��� ����� Master����(Distance�� ���� ū) dVel�ӵ��� �����̸�, ������ ����� Distance������ �����δ�. 
    // �ӵ��� �ش� Chip�� �� ��ȣ�� ���� ���� ���� �ӵ��� ����
    [DllImport("AXL.dll")] public static extern uint AxmMoveStartLineVel(int lArraySize, int[] lpAxesNo, double[] dpDis, double dVel, double dAccel, double dDecel);

    // Ư�� Input ��ȣ�� Edge�� �����Ͽ� ������ �Ǵ� ���������ϴ� �Լ�.
    // lDetect Signal : edge ������ �Է� ��ȣ ����.
    // lDetectSignal  : PosEndLimit(0), NegEndLimit(1), HomeSensor(4), EncodZPhase(5), UniInput02(6), UniInput03(7)
    // Signal Edge    : ������ �Է� ��ȣ�� edge ���� ���� (rising or falling edge).
    //                  SIGNAL_DOWN_EDGE(0), SIGNAL_UP_EDGE(1)
    // ��������      : Vel���� ����̸� CW, �����̸� CCW.
    // SignalMethod  : ������ EMERGENCY_STOP(0), �������� SLOWDOWN_STOP(1)
    // ���ǻ���: SignalMethod�� EMERGENCY_STOP(0)�� ����Ұ�� �������� ���õǸ� ������ �ӵ��� ���� �������ϰԵȴ�.
    //          PCI-Nx04�� ����� ��� lDetectSignal�� PosEndLimit , NegEndLimit(0,1) �� ã����� ��ȣ�Ƿ��� Active ���¸� �����ϰԵȴ�.
    [DllImport("AXL.dll")] public static extern uint AxmMoveSignalSearch(int nAxisNo, double dVel, double dAccel, int nDetectSignal, int nSignalEdge, int nSignalMethod);

    // Ư�� Input ��ȣ�� Edge�� �����Ͽ� ����ڰ� ������ ��ġ ����ŭ �̵��ϴ� �Լ�.(MLIII : Sigma-5/7 ����)
    // dVel           : ���� �ӵ� ����, ����̸� CW, �����̸� CCW.
	// dAccel         : ���� ���ӵ� ����
	// dDecel         : ���� ���ӵ� ����, �Ϲ������� dAccel�� 50��� ������.
    // lDetectSignal  : HomeSensor(4)
    // dDis           : �Է� ��ȣ�� ���� ��ġ�� �������� ����ڰ� ������ ��ġ��ŭ ��� ������.
    // ���ǻ���:        
	//          - ��������� �ݴ� �������� dDis �� �Է½� ���������� ���� �� �� ����.
    //          - �ӵ��� ������, dDis ���� ���� ��� ���Ͱ� ��ȣ �����ؼ� ������ ���Ŀ� ���� ��ġ�� ���� ���ؼ� ���������� ������ �� ����
	//          - �ش� �Լ��� ����ϱ� ���� ���� ������ �ݵ�� LOW �Ǵ� HIGH�� �����Ǿ� �־����.
    [DllImport("AXL.dll")] public static extern uint AxmMoveSignalSearchAtDis(int nAxisNo, double dVel, double dAccel, double dDecel, int nDetectSignal, double dDis);

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
    //           PCI-Nx04�� ����� ��� lDetectSignal�� PosEndLimit , NegEndLimit(0,1) �� ã����� ��ȣ�Ƿ��� Active ���¸� �����ϰԵȴ�.
    [DllImport("AXL.dll")] public static extern uint AxmMoveSignalCapture(int nAxisNo, double dVel, double dAccel, int nDetectSignal, int nSignalEdge, int nTarget, int nSignalMethod);
    // 'AxmMoveSignalCapture' �Լ����� ����� ��ġ���� Ȯ���ϴ� �Լ��̴�.
    // ���ǻ���: �Լ� ���� ����� "AXT_RT_SUCCESS"�϶� ����� ��ġ�� ��ȿ�ϸ�, �� �Լ��� �ѹ� �����ϸ� ���� ��ġ���� �ʱ�ȭ�ȴ�.
    [DllImport("AXL.dll")] public static extern uint AxmMoveGetCapturePos(int nAxisNo, ref double dpCapPos);

    // "������ �Ÿ���ŭ �Ǵ� ��ġ���� �̵��ϴ� �Լ�.
    // �Լ��� �����ϸ� �ش� Motion ������ ������ �� Motion �� �Ϸ�ɶ����� ��ٸ��� �ʰ� �ٷ� �Լ��� ����������."
    [DllImport("AXL.dll")] public static extern uint AxmMoveStartMultiPos(int nArraySize, int[] nAxisNo, double[] dPos, double[] dVel, double[] dAccel, double[] dDecel);

    // ������ ������ �Ÿ���ŭ �Ǵ� ��ġ���� �̵��Ѵ�.
    // ���� ����� ���� ��ǥ�� ������ ��ġ���� ������ �ӵ��� �������� ������ �Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMoveMultiPos(int nArraySize, int[] nAxisNo, double[] dPos, double[] dVel, double[] dAccel, double[] dDecel);

    // ������ ��ũ �� �ӵ� ������ ���͸� �����Ѵ�.(PCIR-1604-MLII/SIIIH, PCIe-Rxx04-SIIIH  ���� �Լ�)
    // dTroque        : �ִ� ��� ��ũ�� ���� %��.     
    // ��������       : dTroque���� ����̸� CW, �����̸� CCW.
    // dVel           : �ִ� ���� ���� �ӵ��� ���� %��.
    // uAccFilterSel  : LINEAR_ACCDCEL(0), EXPO_ACCELDCEL(1), SCURVE_ACCELDECEL(2)
    // uGainSel       : GAIN_1ST(0), GAIN_2ND(1)
    // uSpdLoopSel    : PI_LOOP(0), P_LOOP(1)
    [DllImport("AXL.dll")] public static extern uint AxmMoveStartTorque(int lAxisNo, double dTorque, double dVel, uint uAccFilterSel, uint uGainSel, uint uSpdLoopSel);

    // ���� ���� ��ũ ������ ���� �Ѵ�.
    // AxmMoveStartTorque�� �ݵ�� AxmMoveTorqueStop�� �����Ͽ��� �Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMoveTorqueStop(int lAxisNo, uint uMethod);

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
    [DllImport("AXL.dll")] public static extern uint AxmMoveStartPosWithList(int lAxisNo, double dPosition, double[] dpVel, double[] dpAccel, double[] dpDecel, int lListNum);

    // ������ �Ÿ���ŭ �Ǵ� ��ġ���� ��� ���� ��ġ�� ������ �� �̵��� �����Ѵ�.
    // lEvnetAxisNo    : ���� ���� �߻� ��
    // dComparePosition: ���� ���� �߻� ���� ���� �߻� ��ġ.
    // uPositionSource : ���� ���� �߻� ���� ���� �߻� ��ġ ���� ���� => COMMAND(0), ACTUAL(1)
    // ���� �� ��Ҵ� AxmMoveStop, AxmMoveEStop, AxmMoveSStop�� ���
    // �̵� ��� ���� ���� �߻� ���� 4�� ���� �ϳ��� �׷�(2V04�� ��� ���� ���)�� �����Ͽ��� �մϴ�.
    [DllImport("AXL.dll")] public static extern uint AxmMoveStartPosWithPosEvent(int lAxisNo, double dPos, double dVel, double dAccel, double dDecel, int lEventAxisNo, double dComparePosition, uint uPositionSource);

    // ���� ���� ������ ���ӵ��� ���� ���� �Ѵ�.
    // dDecel : ���� �� ��������
    [DllImport("AXL.dll")] public static extern uint AxmMoveStop(int nAxisNo, double dDecel);
        // ���� ���� ������ ���ӵ��� ���� ���� �Ѵ�.(PCI-Nx04 ����)
    // ���� ������ ���¿� ������� ��� ���� ���� �Լ��̸� ���ѵ� ������ ���Ͽ� ��� �����ϴ�.
    // -- ��� ���� ���� : AxmMoveStartPos, AxmMoveVel, AxmLineMoveEx2.
    // dDecel : ���� �� ��������
    // ���� : ���������� ���� ���� ���������� ũ�ų� ���ƾ� �Ѵ�.
    // ���� : ���� ������ �ð����� �Ͽ��� ��� ���� ���� ���� �ð����� �۰ų� ���ƾ� �Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMoveStopEx(int lAxisNo, double dDecel);
    // ���� ���� �� ���� �Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMoveEStop(int nAxisNo);
    // ���� ���� ���� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMoveSStop(int nAxisNo);

    //========= �������̵� �Լ� =========================================================================================
    // ��ġ �������̵� �Ѵ�.
    // ���� ���� ������ ����Ǳ� �� ������ ��� �޽� ���� �����Ѵ�.
    // ���ǻ���: �������̵��� ��ġ�� �������� ���� ������ ��ġ�� ���������� Relative ������ ��ġ������ �־��ش�.
    //           ���������� ���������� ��� �������̵带 ����Ҽ������� �ݴ�������� �������̵��Ұ�쿡�� �������̵带 ����Ҽ�����.
    [DllImport("AXL.dll")] public static extern uint AxmOverridePos(int nAxisNo, double dOverridePos);

    // ���� ���� �ӵ��������̵� �ϱ����� �������̵��� �ְ�ӵ��� �����Ѵ�.
    // ������ : �ӵ��������̵带 5���Ѵٸ� ���߿� �ְ� �ӵ��� �����ؾߵȴ�. 
    [DllImport("AXL.dll")] public static extern uint AxmOverrideSetMaxVel(int nAxisNo, double dOverrideMaxVel);
    // �ӵ� �������̵� �Ѵ�.
    // ���� ���� ���� �߿� �ӵ��� ���� �����Ѵ�. (�ݵ�� ��� �߿� ���� �����Ѵ�.)
    // ������: AxmOverrideVel �Լ��� ����ϱ�����. AxmOverrideMaxVel �ְ�� �����Ҽ��ִ� �ӵ��� �����س��´�.
    // EX> �ӵ��������̵带 �ι��Ѵٸ� 
    // 1. �ΰ��߿� ���� �ӵ��� AxmOverrideMaxVel ���� �ְ� �ӵ��� ����.
    // 2. AxmMoveStartPos ���� ���� ���� ���� ��(Move�Լ� ��� ����)�� �ӵ��� ù��° �ӵ��� AxmOverrideVel ���� �����Ѵ�.
    // 3. ���� ���� ���� ��(Move�Լ� ��� ����)�� �ӵ��� �ι�° �ӵ��� AxmOverrideVel ���� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmOverrideVel(int nAxisNo, double dOverrideVelocity);
    // ���ӵ�, �ӵ�, ���ӵ���  �������̵� �Ѵ�.
    // ���� ���� ���� �߿� ���ӵ�, �ӵ�, ���ӵ��� ���� �����Ѵ�. (�ݵ�� ��� �߿� ���� �����Ѵ�.)
    // ������: AxmOverrideAccelVelDecel �Լ��� ����ϱ�����. AxmOverrideMaxVel �ְ�� �����Ҽ��ִ� �ӵ��� �����س��´�.
    // EX> �ӵ��������̵带 �ι��Ѵٸ� 
    // 1. �ΰ��߿� ���� �ӵ��� AxmOverrideMaxVel ���� �ְ� �ӵ��� ����.
    // 2. AxmMoveStartPos ���� ���� ���� ���� ��(Move�Լ� ��� ����)�� ���ӵ�, �ӵ�, ���ӵ��� ù��° �ӵ��� AxmOverrideAccelVelDecel ���� �����Ѵ�.
    // 3. ���� ���� ���� ��(Move�Լ� ��� ����)�� ���ӵ�, �ӵ�, ���ӵ��� �ι�° �ӵ��� AxmOverrideAccelVelDecel ���� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmOverrideAccelVelDecel(int nAxisNo, double dOverrideVelocity, double dMaxAccel, double dMaxDecel);
    // ��� �������� �ӵ� �������̵� �Ѵ�.
    // ��� ��ġ ������ �������̵��� �ӵ��� �Է½��� ����ġ���� �ӵ��������̵� �Ǵ� �Լ�
    // lTarget : COMMAND(0), ACTUAL(1)
    // ������: AxmOverrideVelAtPos �Լ��� ����ϱ�����. AxmOverrideMaxVel �ְ�� �����Ҽ��ִ� �ӵ��� �����س��´�.
    [DllImport("AXL.dll")] public static extern uint AxmOverrideVelAtPos(int nAxisNo, double dPos, double dVel, double dAccel, double dDecel, double dOverridePos, double dOverrideVelocity, int nTarget);
    // ������ �����鿡�� ������ �ӵ��� �������̵� �Ѵ�.
    // lArraySize     : �������̵� �� ��ġ�� ������ ����.
    // *dpOverridePos : �������̵� �� ��ġ�� �迭(lArraySize���� ������ �������� ���ų� ũ�� �����ؾߵ�)
    // *dpOverrideVel : �������̵� �� ��ġ���� ���� �� �ӵ� �迭(lArraySize���� ������ �������� ���ų� ũ�� �����ؾߵ�)
    // lTarget        : COMMAND(0), ACTUAL(1) 
    // uOverrideMode : �������̵� ���� ����� ������.
    //                : OVERRIDE_POS_START(0) ������ ��ġ���� ������ �ӵ��� �������̵� ������        
    //                : OVERRIDE_POS_END(1) ������ ��ġ���� ������ �ӵ��� �ǵ��� �̸� �������̵� ������
    [DllImport("AXL.dll")] public static extern uint AxmOverrideVelAtMultiPos(int nAxisNo, double dPos, double dVel, double dAccel, double dDecel, int nArraySize, double[] dpOverridePos, double[] dpOverrideVel, int nTarget, uint uOverrideMode);

    // ������ �����鿡�� ������ �ӵ�/�����ӵ��� �������̵� �Ѵ�.(MLII ����)
    // lArraySize     : �������̵� �� ��ġ�� ������ ����(�ִ� 5).
    // *dpOverridePos : �������̵� �� ��ġ�� �迭(lArraySize���� ������ �������� ���ų� ũ�� �����ؾߵ�)
    // *dpOverrideVel : �������̵� �� ��ġ���� ���� �� �ӵ� �迭(lArraySize���� ������ �������� ���ų� ũ�� �����ؾߵ�)
    // *dpOverrideAccelDecel : �������̵� �� ��ġ���� ���� �� �����ӵ� �迭(lArraySize���� ������ �������� ���ų� ũ�� �����ؾߵ�)
    // lTarget        : COMMAND(0), ACTUAL(1) 
    // dwOverrideMode : �������̵� ���� ����� ������.
    //                : OVERRIDE_POS_START(0) ������ ��ġ���� ������ �ӵ��� �������̵� ������  
    //                : OVERRIDE_POS_END(1) ������ ��ġ���� ������ �ӵ��� �ǵ��� �̸� �������̵� ������
    [DllImport("AXL.dll")] public static extern uint AxmOverrideVelAtMultiPos2(int lAxisNo, double dPos, double dVel, double dAccel, double dDecel, int lArraySize, double[] dpOverridePos, double[] dpOverrideVel, double[] dpOverrideAccelDecel, int lTarget, uint dwOverrideMode);
    
    //========= ������, �����̺�  ����� ���� �Լ� ====================================================================
    // Electric Gear ��忡�� Master ��� Slave ����� ���� �����Ѵ�.
    // dSlaveRatio : �������࿡ ���� �����̺��� ����( 0 : 0% , 0.5 : 50%, 1 : 100%)
    [DllImport("AXL.dll")] public static extern uint AxmLinkSetMode(int nMasterAxisNo, int nSlaveAxisNo, double dSlaveRatio);
    // Electric Gear ��忡�� ������ Master ��� Slave ����� ���� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmLinkGetMode(int nMasterAxisNo, ref uint nSlaveAxisNo, ref double dpGearRatio);
    // Master ��� Slave�ణ�� ���ڱ��� ���� ���� �Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmLinkResetMode(int nMasterAxisNo);

    //======== ��Ʈ�� ���� �Լ�==========================================================================================
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
    [DllImport("AXL.dll")] public static extern uint AxmGantrySetEnable(int nMasterAxisNo, int nSlaveAxisNo, uint uSlHomeUse, double dSlOffset, double dSlOffsetRange);

    // Slave���� Offset���� �˾Ƴ��¹��.
    // A. ������, �����̺긦 ��� �������� ��Ų��.                 
    // B. AxmGantrySetEnable�Լ����� uSlHomeUse = 2�� ������ AxmHomeSetStart�Լ��� �̿��ؼ� Ȩ�� ã�´�. 
    // C. Ȩ�� ã�� ���� ���������� Command���� �о�� ��������� �����̺����� Ʋ���� Offset���� �����ִ�.
    // D. Offset���� �о AxmGantrySetEnable�Լ��� dSlOffset���ڿ� �־��ش�. 
    // E. dSlOffset���� �־��ٶ� �������࿡ ���� �����̺� �� ���̱⶧���� ��ȣ�� �ݴ�� -dSlOffset �־��ش�.
    // F. dSIOffsetRange �� Slave Offset�� Range ������ ���ϴµ� Range�� �Ѱ踦 �����Ͽ� �Ѱ踦 ����� ������ �߻���ų�� ����Ѵ�.
    // G. AxmGantrySetEnable�Լ��� Offset���� �־�������  AxmGantrySetEnable�Լ����� uSlHomeUse = 1�� ������ AxmHomeSetStart�Լ��� �̿��ؼ� Ȩ�� ã�´�.

    // ��Ʈ�� ������ �־� ����ڰ� ������ �Ķ��Ÿ�� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmGantryGetEnable(int nMasterAxisNo, ref uint upSlHomeUse, ref double dpSlOffset, ref double dSlORange, ref uint uGatryOn);
    // ��� ����� �� ���� �ⱸ������ Link�Ǿ��ִ� ��Ʈ�� �����ý��� ��� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmGantrySetDisable(int nMasterAxisNo, int nSlaveAxisNo);

    // PCI-Rxx04-MLII ����.
    // ��� ����� �� ���� �ⱸ������ Link�Ǿ��ִ� ��Ʈ�� �����ý��� ���� �� ���� ���� ����� �����Ѵ�.
    // lMasterGain, lSlaveGain : �� �ణ ��ġ ������ ���� ���� �� �ݿ� ������ % ������ �Է��Ѵ�.
    // lMasterGain, lSlaveGain : 0�� �Է��ϸ� �� �ణ ��ġ ���� ���� ����� ������� ����. �⺻�� : 0%
    [DllImport("AXL.dll")] public static extern uint AxmGantrySetCompensationGain(int lMasterAxisNo, int lMasterGain, int lSlaveGain);
    // ��� ����� �� ���� �ⱸ������ Link�Ǿ��ִ� ��Ʈ�� �����ý��� ���� �� ���� ���� ����� ������ Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmGantryGetCompensationGain(int lMasterAxisNo, ref int lMasterGain, ref int lSlaveGain);

    // Master �� Slave �� ���� ������ ���� �ϰ� �������� �̻��̸� Read �Լ��� Status�� TRUE�� ��ȯ �Ѵ�.
    // PCI-R1604 / PCI-R3200-MLIII ���� �Լ�
    // lMasterAxisNo : Gantry Master Axis No
    // dErrorRange : ���� ���� ���� �� 0~2147483647 (����� �Է� ���� �Է½� 1170 Error Code Return)
    // uUse : ��� ����
    //      ( 0 : Disable)
    //      ( 1 : User ���� ���)
	//      ( 2 : Flag Latch ���)
	//      ( 3 : Flag Latch ��� + Error �߻��� SSTOP)
    //      ( 4 : Flag Latch ��� + Error �߻��� ESTOP)
    [DllImport("AXL.dll")] public static extern uint AxmGantrySetErrorRange(int lMasterAxisNo, double dErrorRange, uint uUse);
    // Master �� Slave ���� ���� ���� �������� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmGantryGetErrorRange(int lMasterAxisNo, ref double dpErrorRange, ref uint upUse);
    // Master �� Slave ���� ������ �� ����� ��ȯ �Ѵ�.
    // dwpStatus : FALSE(0) -> Master �� Slave ������ ���������� ������ �������� ���� �۴�. (�������)
    //             TRUE(1) -> Master �� Slave ������ ���������� ������ �������� ���� ũ��. (���������)
    // AxmGantryReadErrorRangeStatus �Լ��� ��� InMotion && Gantry Enable && Master/Slave Servo On ���¸� ���� �� ����
    // AXT_RT_SUCCESS�� Return �ϸ� ���� ���¸� �������� ������ Error Code�� Return �Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmGantryReadErrorRangeStatus(int lMasterAxisNo, ref uint dwpStatus);
    // Master �� Slave ���� �������� ��ȯ �Ѵ�.
    // Flag Latch ��� �϶� Latch �� ���� ����ڰ� �о� �� �� ���� Error�� �߻� �Ǳ� ������ Error�� �߻� ���� ���� ���� ���� �ϰ� �˴ϴ�.
    [DllImport("AXL.dll")] public static extern uint AxmGantryReadErrorRangeComparePos(int lMasterAxisNo, ref double dpComparePos);

    //====�Ϲ� �����Լ� =================================================================================================
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
    [DllImport("AXL.dll")] public static extern uint AxmLineMove(int lCoord, double[] dPos, double dVel, double dAccel, double dDecel);

    // 2�� ���� ���� ���� �Ѵ�.(Software ���)
    // �������� �������� �����Ͽ� ���� ���� ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
    [DllImport("AXL.dll")] public static extern uint AxmLineMoveEx2(int lCoord, double[] dpEndPos, double dVel, double dAccel, double dDecel);

    // 2�� ��ȣ���� �Ѵ�.
    // ������, �������� �߽����� �����Ͽ� ��ȣ ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
    // AxmContiBeginNode, AxmContiEndNode, �� ���̻��� ������ ��ǥ�迡 ������, �������� �߽����� �����Ͽ� �����ϴ� ��ȣ ���� Queue�� �����Լ����ȴ�.
    // �������� ��ȣ ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmContiStart�Լ��� ����ؼ� �����Ѵ�.
    // lAxisNo = ���� �迭 , dCenterPos = �߽��� X,Y �迭 , dEndPos = ������ X,Y �迭.
    // uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
    [DllImport("AXL.dll")] public static extern uint AxmCircleCenterMove(int lCoord, int[] lAxisNo, double[] dCenterPos, double[] dEndPos, double dVel, double dAccel, double dDecel, uint uCWDir);

    // �߰���, �������� �����Ͽ� ��ȣ ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
    // AxmContiBeginNode, AxmContiEndNode�� ���̻��� ������ ��ǥ�迡 �߰���, �������� �����Ͽ� �����ϴ� ��ȣ ���� Queue�� �����Լ����ȴ�.
    // �������� ��ȣ ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmContiStart�Լ��� ����ؼ� �����Ѵ�.
    // lAxisNo = ���� �迭 , dMidPos = �߰��� X,Y �迭 , dEndPos = ������ X,Y �迭, lArcCircle = ��ũ(0), ��(1)
    [DllImport("AXL.dll")] public static extern uint AxmCirclePointMove(int lCoord, int[] lAxisNo, double[] dMidPos, double[] dEndPos, double dVel, double dAccel, double dDecel, int lArcCircle);

    // ������, �������� �������� �����Ͽ� ��ȣ ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
    // AxmContiBeginNode, AxmContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, �������� �������� �����Ͽ� ��ȣ ���� �����ϴ� Queue�� �����Լ����ȴ�.
    // �������� ��ȣ ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmContiStart�Լ��� ����ؼ� �����Ѵ�.
    // lAxisNo = ���� �迭 , dRadius = ������, dEndPos = ������ X,Y �迭 , uShortDistance = ������(0), ū��(1)
    // uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
    [DllImport("AXL.dll")] public static extern uint AxmCircleRadiusMove(int lCoord, int[] lAxisNo, double dRadius, double[] dEndPos, double dVel, double dAccel, double dDecel, uint uCWDir, uint uShortDistance);

    // ������, ȸ�������� �������� �����Ͽ� ��ȣ ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
    // AxmContiBeginNode, AxmContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, ȸ�������� �������� �����Ͽ� ��ȣ ���� �����ϴ� Queue�� �����Լ����ȴ�.
    // �������� ��ȣ ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmContiStart�Լ��� ����ؼ� �����Ѵ�.
    // lAxisNo = ���� �迭 , dCenterPos = �߽��� X,Y �迭 , dAngle = ����.
    // uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
    [DllImport("AXL.dll")] public static extern uint AxmCircleAngleMove(int lCoord, int[] lAxisNo, double[] dCenterPos, double dAngle, double dVel, double dAccel, double dDecel, uint uCWDir);

    //====���� ���� �Լ� ================================================================================================
    // ������ ��ǥ�迡 ���Ӻ��� �� ������ �����Ѵ�.
    // (����� ��ȣ�� 0 ���� ����))
    // ������: ������Ҷ��� �ݵ�� ���� ���ȣ�� ���� ���ں��� ū���ڸ� �ִ´�.
    //         ������ ���� �Լ��� ����Ͽ��� �� �������ȣ�� ���� ���ȣ�� ���� �� ���� lpAxesNo�� ���� ���ؽ��� �Է��Ͽ��� �Ѵ�.
    //         ������ ���� �Լ��� ����Ͽ��� �� �������ȣ�� �ش��ϴ� ���� ���ȣ�� �ٸ� ���̶�� �Ѵ�.
    //         ���� ���� �ٸ� Coordinate�� �ߺ� �������� ���ƾ� �Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmContiSetAxisMap(int lCoord, uint lSize, int[] lpRealAxesNo);
    //������ ��ǥ�迡 ���Ӻ��� �� ������ ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmContiGetAxisMap(int lCoord, ref uint lSize, ref int lpRealAxesNo);

    // ������ ��ǥ�迡 ���Ӻ��� �� ����/��� ��带 �����Ѵ�.
    // (������ : �ݵ�� ����� �ϰ� ��밡��)
    // ���� ���� �̵� �Ÿ� ��� ��带 �����Ѵ�.
    // uAbsRelMode : POS_ABS_MODE '0' - ���� ��ǥ��
    //               POS_REL_MODE '1' - ��� ��ǥ��
    [DllImport("AXL.dll")] public static extern uint AxmContiSetAbsRelMode(int lCoord, uint uAbsRelMode);
    // ������ ��ǥ�迡 ���Ӻ��� �� ����/��� ��带 ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmContiGetAbsRelMode(int lCoord, ref uint upAbsRelMode);

    // ������ ��ǥ�迡 ���� ������ ���� ���� Queue�� ��� �ִ��� Ȯ���ϴ� �Լ��̴�.
    [DllImport("AXL.dll")] public static extern uint AxmContiReadFree(int lCoord, ref uint upQueueFree);
    // ������ ��ǥ�迡 ���� ������ ���� ���� Queue�� ����Ǿ� �ִ� ���� ���� ������ Ȯ���ϴ� �Լ��̴�.
    [DllImport("AXL.dll")] public static extern uint AxmContiReadIndex(int lCoord, ref int npQueueIndex);

    // ������ ��ǥ�迡 ���� ���� ������ ���� ����� ���� Queue�� ��� �����ϴ� �Լ��̴�.
    [DllImport("AXL.dll")] public static extern uint AxmContiWriteClear(int lCoord);

    // ������ ��ǥ�迡 ���Ӻ������� ������ �۾����� ����� �����Ѵ�. ���Լ��� ȣ������,
    // AxmContiEndNode�Լ��� ȣ��Ǳ� ������ ����Ǵ� ��� ����۾��� ���� ����� �����ϴ� ���� �ƴ϶� ���Ӻ��� ������� ��� �Ǵ� ���̸�,
    // AxmContiStart �Լ��� ȣ��� �� ��μ� ��ϵȸ���� ������ ����ȴ�.
    [DllImport("AXL.dll")] public static extern uint AxmContiBeginNode(int lCoord);
    // ������ ��ǥ�迡�� ���Ӻ����� ������ �۾����� ����� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmContiEndNode(int lCoord);

    // ���� ���� ���� �Ѵ�.
    // uProfileset(CONTI_NODE_VELOCITY(0) : ���� ���� ���, CONTI_NODE_MANUAL(1) : �������� ���� ���, CONTI_NODE_AUTO(2) : �ڵ� �������� ����, 3 : �ӵ����� ��� ���) 
    [DllImport("AXL.dll")] public static extern uint AxmContiStart(int lCoord, uint uProfileset, int lAngle);
    // ������ ��ǥ�迡 ���� ���� ���� ������ Ȯ���ϴ� �Լ��̴�.
    [DllImport("AXL.dll")] public static extern uint AxmContiIsMotion(int lCoord, ref uint upInMotion);

    // ������ ��ǥ�迡 ���� ���� ���� �� ���� �������� ���� ���� �ε��� ��ȣ�� Ȯ���ϴ� �Լ��̴�.
    [DllImport("AXL.dll")] public static extern uint AxmContiGetNodeNum(int lCoord, ref int npNodeNum);
    // ������ ��ǥ�迡 ������ ���� ���� ���� �� �ε��� ������ Ȯ���ϴ� �Լ��̴�.
    [DllImport("AXL.dll")] public static extern uint AxmContiGetTotalNodeNum(int lCoord, ref int npNodeNum);

    //====================Ʈ���� �Լ� ===================================================================================
    // ���ǻ���: Ʈ���� ��ġ�� �����Ұ�� �ݵ�� UNIT/PULSE�� ���߾ �����Ѵ�.
    //           ��ġ�� UNIT/PULSE ���� �۰��� ��� �ּҴ����� UNIT/PULSE�� ���߾����⶧���� ����ġ�� ����Ҽ�����.

    // ���� �࿡ Ʈ���� ����� ��� ����, ��� ����, ��ġ �񱳱�, Ʈ���� ��ȣ ���� �ð� �� Ʈ���� ��� ��带 �����Ѵ�.
    // Ʈ���� ��� ����� ���ؼ��� ����  AxmTriggerSetTimeLevel �� ����Ͽ� ���� ��� ������ ���� �Ͽ��� �Ѵ�.
    // dTrigTime : Ʈ���� ��� �ð�, 1usec - �ִ� 50msec ( 1 - 50000 ���� ����)
    // upTriggerLevel  : Ʈ���� ��� ���� ���� => LOW(0), HIGH(1)
    // uSelect         : ����� ���� ��ġ      => COMMAND(0), ACTUAL(1)
    // uInterrupt      : ���ͷ�Ʈ ����         => DISABLE(0), ENABLE(1)

    // ���� �࿡ Ʈ���� ��ȣ ���� �ð� �� Ʈ���� ��� ����, Ʈ���� ��¹���� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmTriggerSetTimeLevel(int lAxisNo, double dTrigTime, uint uTriggerLevel, uint uSelect, uint uInterrupt);
    // ���� �࿡ Ʈ���� ��ȣ ���� �ð� �� Ʈ���� ��� ����, Ʈ���� ��¹���� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmTriggerGetTimeLevel(int lAxisNo, ref double dTrigTime, ref uint uTriggerLevel, ref uint uSelect, ref uint uInterrupt);

    // ���� ���� Ʈ���� ��� ����� �����Ѵ�.
    // uMethod : PERIOD_MODE  0x0 : ���� ��ġ�� �������� dPos�� ��ġ �ֱ�� ����� �ֱ� Ʈ���� ���
    //           ABS_POS_MODE 0x1 : Ʈ���� ���� ��ġ���� Ʈ���� �߻�, ���� ��ġ ���
    // dPos : �ֱ� ���ý� : ��ġ������ġ���� ����ϱ⶧���� �� ��ġ
    //        ���� ���ý� : ����� �� ��ġ, �� ��ġ�Ͱ����� ������ ����� ������. 
    // ���ǻ���: AxmTriggerSetAbsPeriod�� �ֱ���� �����Ұ�� ó�� ����ġ�� ���� �ȿ� �����Ƿ� Ʈ���� ����� �ѹ� �߻��Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmTriggerSetAbsPeriod(int nAxisNo, uint uMethod, double dPos);
    // ���� �࿡ Ʈ���� ����� ��� ����, ��� ����, ��ġ �񱳱�, Ʈ���� ��ȣ ���� �ð� �� Ʈ���� ��� ��带 ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmTriggerGetAbsPeriod(int nAxisNo, ref uint upMethod, ref double dpPos);

    // ����ڰ� ������ ������ġ���� ������ġ���� ������������ Ʈ���Ÿ� ��� �Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmTriggerSetBlock(int nAxisNo, double dStartPos, double dEndPos, double dPeriodPos);
    // 'AxmTriggerSetBlock' �Լ��� Ʈ���� ������ ���� �д´�..
    [DllImport("AXL.dll")] public static extern uint AxmTriggerGetBlock(int nAxisNo, ref double dpStartPos, ref double dpEndPos, ref double dpPeriodPos);

    // ����ڰ� �� ���� Ʈ���� �޽��� ����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmTriggerOneShot(int nAxisNo);
    // ����ڰ� �� ���� Ʈ���� �޽��� �����Ŀ� ����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmTriggerSetTimerOneshot(int nAxisNo, int mSec);
    // ������ġ Ʈ���� ���Ѵ� ������ġ ����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmTriggerOnlyAbs(int nAxisNo, int nTrigNum, double[] dTrigPos);
    // Ʈ���� ������ �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmTriggerSetReset(int nAxisNo);

    //======== CRC( �ܿ� �޽� Ŭ���� �Լ�)===============================================================================
    // Level   : LOW(0), HIGH(1), UNUSED(2), USED(3)
    // uMethod : �ܿ��޽� ���� ��� ��ȣ �޽� �� 0 - 7���� ��������.
    //           0 : 30 uSec , 1 : 100 uSec, 2: 500 uSec, 3:1 mSec, 4:10 mSec, 5:50 mSec, 6:100 mSec
    //���� �࿡ CRC ��ȣ ��� ���� �� ��� ������ �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmCrcSetMaskLevel(int nAxisNo, uint uLevel, uint uMethod);
    // ���� ���� CRC ��ȣ ��� ���� �� ��� ������ ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmCrcGetMaskLevel(int nAxisNo, ref uint upLevel, ref uint upMethod);

    //uOnOff  : CRC ��ȣ�� Program���� �߻� ����  (FALSE(0),TRUE(1))
    // ���� �࿡ CRC ��ȣ�� ������ �߻� ��Ų��.
    [DllImport("AXL.dll")] public static extern uint AxmCrcSetOutput(int nAxisNo, uint uOnOff);
    // ���� ���� CRC ��ȣ�� ������ �߻� ���θ� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmCrcGetOutput(int nAxisNo, ref uint upOnOff);

    //======MPG(Manual Pulse Generation) �Լ�============================================================================
    // lInputMethod  : 0-3 ���� ��������. 0:OnePhase, 1:��� ����, 2:TwoPhase2, 3:TwoPhase4
    // lDriveMode    : 0�� �������� (0 :MPG ���Ӹ��)
    // MPGPos        : MPG �Է½�ȣ���� �̵��ϴ� �Ÿ�
    // MPGdenominator: MPG(���� �޽� �߻� ��ġ �Է�)���� �� ������ ��
    // dMPGnumerator : MPG(���� �޽� �߻� ��ġ �Է�)���� �� ���ϱ� ��
    // uNumerator    : �ִ�(1 ����    64) ���� ���� ����
    // uDenominator  : �ִ�(1 ����  4096) ���� ���� ����
    // dMPGdenominator = 4096, MPGnumerator=1 �� �ǹ��ϴ� ���� 
    // MPG �ѹ����� 200�޽��� �״�� 1:1�� 1�޽��� ����� �ǹ��Ѵ�. 
    // ���� dMPGdenominator = 4096, MPGnumerator=2 �� �������� 1:2�� 2�޽��� ����� �������ٴ��ǹ��̴�. 
    // ���⿡ MPG PULSE = ((Numerator) * (Denominator)/ 4096 ) Ĩ���ο� ��³����� �����̴�.
    // ���ǻ���     : AxmStatusReadInMotion �Լ� ���� ����� �����Ѵ�.  (AxmMPGReset �ϱ� ������ ���� ���¿����� ��� ���� �� ����.)

    // ���� �࿡ MPG �Է¹��, ����̺� ���� ���, �̵� �Ÿ�, MPG �ӵ� ���� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMPGSetEnable(int nAxisNo, int nInputMethod, int nDriveMode, double dMPGPos, double dVel, double dAccel);
    // ���� �࿡ MPG �Է¹��, ����̺� ���� ���, �̵� �Ÿ�, MPG �ӵ� ���� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMPGGetEnable(int nAxisNo, ref int npInputMethod, ref int npDriveMode, ref double dpMPGPos, ref double dpVel);

    // PCI-Nx04 �Լ� ����.
    // ���� �࿡ MPG ����̺� ���� ��忡�� ���޽��� �̵��� �޽� ������ �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMPGSetRatio(int nAxisNo, double dMPGnumerator, double dMPGdenominator);
    // ���� �࿡ MPG ����̺� ���� ��忡�� ���޽��� �̵��� �޽� ������ ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMPGGetRatio(int nAxisNo, ref double dMPGnumerator, ref double dMPGdenominator);

    // ���� �࿡ MPG ����̺� ������ �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMPGReset(int nAxisNo);

    //======= �︮�� �̵� ===============================================================================================
    // ���ǻ��� : Helix�� ���Ӻ��� ���� Spline, ���������� ��ȣ������ ���� ����Ҽ�����.

    // ������ ��ǥ�迡 ������, �������� �߽����� �����Ͽ� �︮�� ���� �����ϴ� �Լ��̴�.
    // AxmContiBeginNode, AxmContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, �������� �߽����� �����Ͽ� �︮�� ���Ӻ��� �����ϴ� �Լ��̴�. 
    // ��ȣ ���� ���� ������ ���� ���� Queue�� �����ϴ� �Լ��̴�. AxmContiStart�Լ��� ����ؼ� �����Ѵ�. (���Ӻ��� �Լ��� ���� �̿��Ѵ�)
    // dCenterPos = �߽��� X,Y  , dEndPos = ������ X,Y
    // uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
    [DllImport("AXL.dll")] public static extern uint AxmHelixCenterMove(int lCoord, double dCenterXPos, double dCenterYPos, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dAccel, double dDecel, uint uCWDir);

    // ������ ��ǥ�迡 ������, �������� �������� �����Ͽ� �︮�� ���� �����ϴ� �Լ��̴�. 
    // AxmContiBeginNode, AxmContiEndNode�� ���̻��� ������ ��ǥ�迡 �߰���, �������� �����Ͽ� �︮�ÿ��� ���� �����ϴ� �Լ��̴�. 
    // ��ȣ ���� ���� ������ ���� ���� Queue�� �����ϴ� �Լ��̴�. AxmContiStart�Լ��� ����ؼ� �����Ѵ�. (���Ӻ��� �Լ��� ���� �̿��Ѵ�.)
    // dMidPos = �߰��� X,Y  , dEndPos = ������ X,Y
    [DllImport("AXL.dll")] public static extern uint AxmHelixPointMove(int lCoord, double dMidXPos, double dMidYPos, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dAccel, double dDecel);

    // ������ ��ǥ�迡 ������, �������� �������� �����Ͽ� �︮�� ���� �����ϴ� �Լ��̴�.
    // AxmContiBeginNode, AxmContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, �������� �������� �����Ͽ� �︮�ÿ��� ���� �����ϴ� �Լ��̴�. 
    // ��ȣ ���� ���� ������ ���� ���� Queue�� �����ϴ� �Լ��̴�. AxmContiStart�Լ��� ����ؼ� �����Ѵ�. (���Ӻ��� �Լ��� ���� �̿��Ѵ�.)
    // dRadius = ������, dEndPos = ������ X,Y  , uShortDistance = ������(0), ū��(1)
    // uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
    [DllImport("AXL.dll")] public static extern uint AxmHelixRadiusMove(int lCoord, double dRadius, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dAccel, double dDecel, uint uCWDir, uint uShortDistance);

    // ������ ��ǥ�迡 ������, ȸ�������� �������� �����Ͽ� �︮�� ���� �����ϴ� �Լ��̴�
    // AxmContiBeginNode, AxmContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, ȸ�������� �������� �����Ͽ� �︮�ÿ��� ���� �����ϴ� �Լ��̴�. 
    // ��ȣ ���� ���� ������ ���� ���� Queue�� �����ϴ� �Լ��̴�. AxmContiStart�Լ��� ����ؼ� �����Ѵ�. (���Ӻ��� �Լ��� ���� �̿��Ѵ�.)
    //dCenterPos = �߽��� X,Y  , dAngle = ����.
    // uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
    [DllImport("AXL.dll")] public static extern uint AxmHelixAngleMove(int lCoord, double dCenterXPos, double dCenterYPos, double dAngle, double dZPos, double dVel, double dAccel, double dDecel, uint uCWDir);

    //======== ���ö��� �̵� ============================================================================================
    // ���ǻ��� : Spline�� ���Ӻ��� ���� Helix , ���������� ��ȣ������ ���� ����Ҽ�����.

    // AxmContiBeginNode, AxmContiEndNode�� ���̻�����. 
    // ���ö��� ���� ���� �����ϴ� �Լ��̴�. ��ȣ ���� ���� ������ ���� ���� Queue�� �����ϴ� �Լ��̴�.
    // AxmContiStart�Լ��� ����ؼ� �����Ѵ�. (���Ӻ��� �Լ��� ���� �̿��Ѵ�.)
    // lPosSize : �ּ� 3�� �̻�.
    // 2������ ���� dPoZ���� 0���� �־��ָ� ��.
    // 3������ ���� ������� 3���� dPosZ ���� �־��ش�.
    [DllImport("AXL.dll")] public static extern uint AxmSplineWrite(int lCoord, int lPosSize, double[] dPosX, double[] dPosY, double dVel, double dAccel, double dDecel, double dPosZ, int lPointFactor);

    //======== PCI-R1604-MLII/SIIIH, PCIe-Rxx04-SIIIH ���� �Լ� ================================================================================== 
    // ��ġ ���� ���̺� ��ɿ� �ʿ��� ������ �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmCompensationSet(int nAxisNo, int nNumEntry, double dStartPos, ref double dpPosition, ref double dpCorrection, uint uRollOver);
    // ��ġ ���� ���̺� ��� ���� ������ ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmCompensationGet(int nAxisNo, ref int npNumEntry, ref double dpStartPos, ref double dpPosition, ref double dpCorrection, ref uint upRollOver);

    // ��ġ ���� ���̺� ����� ������θ� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmCompensationEnable(int nAxisNo, uint uEnable);
    // ��ġ ���� ���̺� ����� ��������� ���� ���� ���¸� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmCompensationIsEnable(int nAxisNo, ref uint upEnable);
    // ���� ���� ��ġ������ �������� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmCompensationGetCorrection(int lAxisNo, ref double dpCorrection);


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
    [DllImport("AXL.dll")] public static extern uint AxmCompensationSetBacklash(int lAxisNo, int lBacklashDir, double dBacklash);
	// Backlash�� ���õ� ���� ������ ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmCompensationGetBacklash(int lAxisNo, ref int lpBacklashDir, ref double dpBacklash);
	// Backlash��������� ����/Ȯ���ϴ� �Լ�
	// > dwEnable: Backlash���� ��������� ����
	//   - [0]DISABLE -> Backlash������ ������    
	//   - [1]ENABLE  -> Backlash������ �����
	// { RETURN VALUE } 
	//   - [0] -> Backlash ������ȯ�� �������� ��
    //   - [4303] -> Backlash ��������� �����Ǿ��������� ��
    [DllImport("AXL.dll")] public static extern uint AxmCompensationEnableBacklash(int lAxisNo, uint dwEnable);
    [DllImport("AXL.dll")] public static extern uint AxmCompensationIsEnableBacklash(int lAxisNo, ref uint dwpEnable);
   	// Backlash��������� ����� �� Backlash�� ��ŭ �¿�� �̵��Ͽ� �ⱸ���� ��ġ�� �ڵ� ������(���� �� ���� ���� �ѹ� �����)
	// > dVel: �̵� �ӵ�[unit / sec]
	// > dAccel: �̵����ӵ�[unit / sec^2]
	// > dAccel: �̵����ӵ�[unit / sec^2]
	// > dWaitTime: Backlash �縸ŭ ���� �� ������ ��ġ�� �ǵ��ƿñ� ������ ���ð�[msec]
	// { RETURN VALUE } 
	//   - [0]    -> Backlash ������ ���� ��ġ������ �������� ��
	//   - [4303] -> Backlash ��������� �����Ǿ��������� ��
    [DllImport("AXL.dll")] public static extern uint AxmCompensationSetLocating(int lAxisNo, double dVel, double dAccel, double dDecel, double dWaitTime);	

    // ECAM ��ɿ� �ʿ��� ������ �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmEcamSet(int nAxisNo, int nMasterAxisNo, int nNumEntry, double dMasterStartPos, ref double dpMasterPos, ref double dpSlavePos);
	// ECAM ��ɿ� �ʿ��� ������ CMD/ACT Source�� �Բ� �����Ѵ�. (PCIe-Rxx04-SIIIH ���� �Լ�)
	[DllImport("AXL.dll")] public static extern uint AxmEcamSetWithSource(int lAxisNo, int lMasterAxis, int lNumEntry, double dMasterStartPos, ref double dpMasterPos, ref double dpSlavePos, uint dwSource);
    // ECAM ��� ���� ������ ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmEcamGet(int nAxisNo, ref int npMasterAxisNo, ref int npNumEntry, ref double dpMasterStartPos, ref double dpMasterPos, ref double dpSlavePos);
	// ECAM ��� ���� ������ CMD/ACT Source�� �Բ� ��ȯ�Ѵ�. (PCIe-Rxx04-SIIIH ���� �Լ�)
	[DllImport("AXL.dll")] public static extern uint AxmEcamGetWithSource(int lAxisNo, ref int lpMasterAxis, ref int lpNumEntry, ref double dpMasterStartPos, ref double dpMasterPos, ref double dpSlavePos, ref uint dwpSource);

    // ECAM ����� ��� ������ �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmEcamEnableBySlave(int nAxisNo, uint uEnable);
    // ECAM ����� ��� ������ ������ Master �࿡ ����� ��� Slave �࿡ ���Ͽ� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmEcamEnableByMaster(int nAxisNo, uint uEnable);
    // ECAM ����� ��� ������ ���� ���� ���¸� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmEcamIsSlaveEnable(int nAxisNo, ref uint upEnable);

    //======== Servo Status Monitor =====================================================================================
    // ���� ���� ���� ó�� ��ɿ� ���� �����Ѵ�.(MLII : Sigma-5, SIIIH : MR_J4_xxB ����)
    // uSelMon(0~3) : ���� ���� ����.
    //          [0] : Torque 
    //          [1] : Velocity of motor
    //          [2] : Accel. of motor
    //          [3] : Decel. of motor
    //          [4] : Position error between Cmd. position and Act. position.
    // uActionValue : �̻� ���� ���� ���� �� ����. �� ������ ���� ���� ���� �ǹ̰� ����.
    //          [0] : uSelMon���� ������ ���� ������ ���Ͽ� ���� ó�� ���� ����.
    //         [>0] : uSelMon���� ������ ���� ������ ���Ͽ� ���� ó�� ��� ����.
    // uAction(0~3) : uActionValue �̻����� ���� ������ Ȯ�εǾ����� ����ó�� ��� ����.
    //          [0] : Warning(setting flag only) 
    //          [1] : Warning(setting flag) + Slow-down stop
    //          [2] : Warning(setting flag) + Emergency stop
    //          [3] : Warning(setting flag) + Emergency stop + Servo-Off
    // �� ����: 5���� SelMon ������ ���� ���� ����ó�� ������ �����ϸ�, ����� ����ó���� ���������� ���
    //          �ݵ�� �ش� SelMon ������ ActionValue���� 0���� ������ ���ñ���� Disable �ص�.
    [DllImport("AXL.dll")] public static extern uint AxmStatusSetServoMonitor(int nAxisNo, uint uSelMon, double dActionValue, uint uAction);
    // ���� ���� ���� ó�� ��ɿ� ���� ���� ���¸� ��ȯ�Ѵ�.(MLII : Sigma-5, SIIIH : MR_J4_xxB ����)
    [DllImport("AXL.dll")] public static extern uint AxmStatusGetServoMonitor(int nAxisNo, uint uSelMon, ref double dpActionValue, ref uint upAction);
    // ���� ���� ���� ó�� ��ɿ� ���� ��� ������ �����Ѵ�.(MLII : Sigma-5, SIIIH : MR_J4_xxB ����)
    [DllImport("AXL.dll")] public static extern uint AxmStatusSetServoMonitorEnable(int nAxisNo, uint uEnable);
    // ���� ���� ���� ó�� ��ɿ� ���� ��� ������ ��ȯ�Ѵ�.(MLII : Sigma-5, SIIIH : MR_J4_xxB ����)
    [DllImport("AXL.dll")] public static extern uint AxmStatusGetServoMonitorEnable(int nAxisNo, ref uint upEnable);

    // ���� ���� ���� ó�� ��� ���� ��� �÷��� ���� ��ȯ�Ѵ�. �Լ� ���� �� �ڵ� �ʱ�ȭ.(MLII : Sigma-5, SIIIH : MR_J4_xxB ����)
    [DllImport("AXL.dll")] public static extern uint AxmStatusReadServoMonitorFlag(int nAxisNo, uint uSelMon, ref uint upMonitorFlag, ref double dpMonitorValue);
    // ���� ���� ���� ó�� ����� ���� ���� ������ ��ȯ�Ѵ�.(MLII : Sigma-5, SIIIH : MR_J4_xxB ����)
    [DllImport("AXL.dll")] public static extern uint AxmStatusReadServoMonitorValue(int nAxisNo, uint uSelMon, ref double dpMonitorValue);
    // ���� ���� �������� ���� �� �ֵ��� ���� �մϴ�.(MLII : Sigma-5, SIIIH : MR_J4_xxB ����)
    // (MLII, Sigma-5, dwSelMon : 0 ~ 2) ==
    //     [0] : Accumulated load ratio
    //     [1] : Regenerative load ratio
    //     [2] : Reference Torque load ratio
    // (SIIIH, MR_J4_xxB, dwSelMon : 0 ~ 4) ==
    //     [0] : Assumed load inertia ratio(0.1times)
    //     [1] : Regeneration load factor(%)
    //     [2] : Effective load factor(%)
    //     [3] : Peak load factor(%)
    //     [4] : Current feedback(0.1%)	
    [DllImport("AXL.dll")] public static extern uint AxmStatusSetReadServoLoadRatio(int lAxisNo, uint dwSelMon);
     // ���� ���� �������� ��ȯ�Ѵ�.(MLII : Sigma-5, SIIIH : MR_J4_xxB ����)
    [DllImport("AXL.dll")] public static extern uint AxmStatusReadServoLoadRatio(int lAxisNo, ref double dpMonitorValue);

//======== PCI-R1604-RTEX ���� �Լ�==================================================================================
    // RTEX A4Nx ���� Scale Coefficient�� �����Ѵ�.(RTEX, A4Nx ����)
    [DllImport("AXL.dll")] public static extern uint AxmMotSetScaleCoeff(int nAxisNo, int lScaleCoeff);
    // RTEX A4Nx ���� Scale Coefficient �� Ȯ���Ѵ�.(RTEX, A4Nx ����)
    [DllImport("AXL.dll")] public static extern uint AxmMotGetScaleCoeff(int nAxisNo, ref int lpScaleCoeff);
    // Ư�� Input ��ȣ�� Edge�� �����Ͽ� ������ �Ǵ� ���������ϴ� �Լ�.
    // lDetect Signal : edge ������ �Է� ��ȣ ����.
    // lDetectSignal  : PosEndLimit(0), NegEndLimit(1), HomeSensor(4), EncodZPhase(5), UniInput02(6), UniInput03(7)
    // Signal Edge    : ������ �Է� ��ȣ�� edge ���� ���� (rising or falling edge).
    //                  SIGNAL_DOWN_EDGE(0), SIGNAL_UP_EDGE(1)
    // ��������      : Vel���� ����̸� CW, �����̸� CCW.
    // SignalMethod  : ������ EMERGENCY_STOP(0), �������� SLOWDOWN_STOP(1)
    // ���ǻ���: SignalMethod�� EMERGENCY_STOP(0)�� ����Ұ�� �������� ���õǸ� ������ �ӵ��� ���� �������ϰԵȴ�.
    //          PCI-Nx04�� ����� ��� lDetectSignal�� PosEndLimit , NegEndLimit(0,1) �� ã����� ��ȣ�Ƿ��� Active ���¸� �����ϰԵȴ�.
    [DllImport("AXL.dll")] public static extern uint AxmMoveSignalSearchEx(int nAxisNo, double dVel, double dAccel, int nDetectSignal, int nSignalEdge, int nSignalMethod);
//-------------------------------------------------------------------------------------------------------------------

//======== PCI-R1604-MLII/SIIIH, PCIe-Rxx04-SIIIH ���� �Լ� ==================================================================================
    // ������ ���� ��ġ�� �̵��Ѵ�.
    // �ӵ� ���������� ����� �������� �����Ѵ�.
    // �޽��� ��µǴ� �������� �Լ��� �����.
    // �׻� ��ġ �� �ӵ�, �����ӵ��� ���� �����ϸ�, �ݴ���� ��ġ ���� ����� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMoveToAbsPos(int lAxisNo, double dPos, double dVel, double dAccel, double dDecel);
    // ���� ���� ���� ���� �ӵ��� �о�´�.
    [DllImport("AXL.dll")] public static extern uint AxmStatusReadVelEx(int lAxisNo, ref double dpVel);
//-------------------------------------------------------------------------------------------------------------------

//========  PCI-R1604-SIIIH, PCIe-Rxx04-SIIIH ���� �Լ� ==================================================================================
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
    [DllImport("AXL.dll")] public static extern uint AxmMotSetElectricGearRatio(int lAxisNo, int lNumerator, int lDenominator);
    // ���� ���� ���� ���� ������ Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMotGetElectricGearRatio(int lAxisNo, ref int lpNumerator, ref int lpDenominator);

    // ���� ���� ��ũ ����Ʈ ���� ���� �մϴ�.
    // ������, ������ �������� ��ũ ���� �����ϴ� �Լ�. 
    // ���� ���� 1 ~ 1000���� ����
    // �ִ� ��ũ�� 0.1% ������ ���� ��.
    [DllImport("AXL.dll")] public static extern uint AxmMotSetTorqueLimit(int lAxisNo, double dbPluseDirTorqueLimit, double dbMinusDirTorqueLimit);

    // ���� ���� ��ũ ����Ʈ ���� Ȯ�� �մϴ�.
    // ������, ������ �������� ��ũ ���� �о� ���� �Լ�.
    // ���� ���� 1 ~ 1000���� ����
    // �ִ� ��ũ�� 0.1% ������ ���� ��.
    [DllImport("AXL.dll")] public static extern uint AxmMotGetTorqueLimit(int lAxisNo, ref double dbpPluseDirTorqueLimit, ref double dbpMinusDirTorqueLimit);

    // ���� ���� AxmOverridePos�� ���� Ư�� ��� ��� ������ �����Ѵ�.
    // dwUsage        : AxmOverridPos ���� ���� ��ġ �Ǵ� ��� ��� ����.
    //                  DISABLE(0) : Ư�� ��� ������� ����.
    //                  ENABLE(1) : AxmMoveStartPos ������ ���� �� ��ġ ���� ���� ��ġ�� ���� �Ÿ��� lDecelPosRatio(%)�� �������� �Ǵ��Ѵ�.
    // lDecelPosRatio : ���� �Ÿ��� ���� %��.
    // dReserved      : ������� ����.
    [DllImport("AXL.dll")] public static extern uint AxmOverridePosSetFunction(int lAxisNo, uint dwUsage, int lDecelPosRatio, double dReserved);
    // ���� ���� AxmOverridePos�� ���� Ư�� ��� ��� ������ Ȯ�� �Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmOverridePosGetFunction(int lAxisNo, ref uint dwpUsage, ref int lpDecelPosRatio, ref double dpReserved);

//-------------------------------------------------------------------------------------------------------------------

//======== PCI-R3200-MLIII ���� �Լ�==================================================================================
    // �ܷ� ���� ����(VST) Ư�� �Լ�    
	// ������� �ݵ�� �ڵ� ���ؼ� ���� �Ҵ��� �ؾ��ϸ�, �ڵ� �Ѱ��� 1���� �ุ ������ �ؾ��Ѵ�.
	// �Ʒ� �Լ� �������� �ݵ�� Servo ON ���¿��� ����Ѵ�.
	// lCoordnate        : �Է� ���� ���� �ڵ� ��ȣ�� �Է��Ѵ�. �� ���庰 ù��° ���� 10��°�� �ڵ� ���� �Ҵ��ؼ� ����ؾ� �Ѵ�.
	//                     MLIII ������ ����� ���� ��ȣ�� �������� 16 ~ 31���� ���� ���� ���������� 16�� �����ȴ�.
	//                     MLIII B/D 0 : 16 ~ 31
	//                     MLIII B/D 1 : 31 ~ 47
	// cISTSize          : �Է� ���� ��� ���ļ� ������ ���ؼ� �Է��Ѵ�. 1�� ���� �����ؼ� ����Ѵ�.
	// dbpFrequency,	 : 10H ~ 500Hz
	//                     1�� ���ļ� ���� �������� �Է��Ѵ�.(�����ĺ��� ������).
	// dbpDampingRatio   : 0.001 ~ 0.9
	// dwpImpulseCount   : 2 ~ 5
    [DllImport("AXL.dll")] public static extern uint AxmAdvVSTSetParameter(int lCoordinate, uint dwISTSize, double[] dbpFrequency, double[] dbpDampingRatio, ref uint dwpImpulseCount);
    [DllImport("AXL.dll")] public static extern uint AxmAdvVSTGetParameter(int lCoordinate, ref uint dwpISTSize, double[] dbpFrequency, double[] dbpDampingRatio, ref uint dwpImpulseCount);
    // lCoordnate        : �Է� ���� �ڵ� ��ȣ�� �Է��Ѵ�.
    // dwISTEnable       : �Է� ���� ��� ������ �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmAdvVSTSetEnabele(int lCoordinate, uint dwISTEnable);
    [DllImport("AXL.dll")] public static extern uint AxmAdvVSTGetEnabele(int lCoordinate, ref uint dwISTEnable);

//====�Ϲ� �����Լ� =================================================================================================	
    // ���� ���� �Ѵ�.
    // �������� �������� �����Ͽ� ���� ���� ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
    // AxmAdvContiBeginNode, AxmAdvContiEndNode�� ���̻��� ������ ��ǥ�迡 �������� �������� �����Ͽ� ���� ���� �����ϴ� Queue�� �����Լ����ȴ�. 
    // ���� �������� ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmAdvContiStart�Լ��� ����ؼ� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmAdvLineMove(int lCoordinate, double[] dPosition, double dMaxVelocity, double dStartVel, double dStopVel, double dMaxAccel, double dMaxDecel);
    // ������ ��ǥ�迡 �������� �������� �����ϴ� ���� ���� ���� �������̵��ϴ� �Լ��̴�.
    // ���� �������� ���������� ������ �ӵ� �� ��ġ�� ���� ���� �������̵� �ϸ�, ���� ��忡 ���� ���� ���� ���� ���൵ �����Ѵ�.
    // IOverrideMode = 0�� ���, �������� ������ ����, ��ȣ ������ ������� ���� ���� ��忡�� ���� �������� ��� �������̵� �ǰ�, 
    // IOverrideMode = 1�̸� ���� ���� ��� ������ ������ ���������� ���ʷ� ����ȴ�.
    // IOverrideMode = 1�� �� �Լ��� ȣ���Ҷ����� �ּ� 1������ �ִ� 8������ �������̵� ť�� �����Ǹ鼭 �ڵ������� ������ �Ǹ�, ���� �� �������� IOverrideMode = 0���� �� �Լ��� ȣ��Ǹ�
    // ���������� �������̵� ť�� �ִ� ���� �������� ���Ӻ��� ť�� ����ǰ�, ���� �������̵� ������ ������ ����� ���Ӻ����� ���������� ����ȴ�.
    [DllImport("AXL.dll")] public static extern uint AxmAdvOvrLineMove(int lCoordinate, double[] dPosition, double dMaxVelocity, double dStartVel, double dStopVel, double dMaxAccel, double dMaxDecel, int lOverrideMode);
    // 2�� ��ȣ���� �Ѵ�.
    // ������, �������� �߽����� �����Ͽ� ��ȣ ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
    // AxmAdvContiBeginNode, AxmAdvContiEndNode, �� ���̻��� ������ ��ǥ�迡 ������, �������� �߽����� �����Ͽ� �����ϴ� ��ȣ ���� Queue�� �����Լ����ȴ�.
    // �������� ��ȣ ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmAdvContiStart�Լ��� ����ؼ� �����Ѵ�.
    // lAxisNo = ���� �迭 , dCenterPos = �߽��� X,Y �迭 , dEndPos = ������ X,Y �迭.
    // uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
    [DllImport("AXL.dll")] public static extern uint AxmAdvCircleCenterMove(int lCoord, int[] lAxisNo, double[] dCenterPos, double[] dEndPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, uint uCWDir);
    // �߰���, �������� �����Ͽ� ��ȣ ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
    // AxmAdvContiBeginNode, AxmAdvContiEndNode�� ���̻��� ������ ��ǥ�迡 �߰���, �������� �����Ͽ� �����ϴ� ��ȣ ���� Queue�� �����Լ����ȴ�.
    // �������� ��ȣ ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmAdvContiStart�Լ��� ����ؼ� �����Ѵ�.
    // lAxisNo = ���� �迭 , dMidPos = �߰��� X,Y �迭 , dEndPos = ������ X,Y �迭, lArcCircle = ��ũ(0), ��(1)
    [DllImport("AXL.dll")] public static extern uint AxmAdvCirclePointMove(int lCoord, int[] lAxisNo, double[] dMidPos, double[] dEndPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, int lArcCircle);
    // ������, ȸ�������� �������� �����Ͽ� ��ȣ ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
    // AxmAdvContiBeginNode, AxmAdvContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, ȸ�������� �������� �����Ͽ� ��ȣ ���� �����ϴ� Queue�� �����Լ����ȴ�.
    // �������� ��ȣ ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmAdvContiStart�Լ��� ����ؼ� �����Ѵ�.
    // lAxisNo = ���� �迭 , dCenterPos = �߽��� X,Y �迭 , dAngle = ����.
    // uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
    [DllImport("AXL.dll")] public static extern uint AxmAdvCircleAngleMove(int lCoord, int[] lAxisNo, double[] dCenterPos, double dAngle, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, uint uCWDir);
    // ������, �������� �������� �����Ͽ� ��ȣ ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
    // AxmAdvContiBeginNode, AxmAdvContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, �������� �������� �����Ͽ� ��ȣ ���� �����ϴ� Queue�� �����Լ����ȴ�.
    // �������� ��ȣ ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmAdvContiStart�Լ��� ����ؼ� �����Ѵ�.
    // lAxisNo = ���� �迭 , dRadius = ������, dEndPos = ������ X,Y �迭 , uShortDistance = ������(0), ū��(1)
    // uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
    [DllImport("AXL.dll")] public static extern uint AxmAdvCircleRadiusMove(int lCoord, int[] lAxisNo, double dRadius, double[] dEndPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, uint uCWDir, uint uShortDistance);
    // ������ ��ǥ�迡 �������� �������� �����Ͽ� 2�� ��ȣ ���� �������̵� �����Ѵ�.
    // ���� �������� ���������� ������ �ӵ� �� ��ġ�� ��ȣ ���� �������̵� �ϸ�, ���� ��忡 ���� ��ȣ ���� ���� ���൵ �����Ѵ�.
    // IOverrideMode = 0�� ���, �������� ������ ����, ��ȣ ������ ������� ���� ���� ��忡�� ��ȣ �������� ��� �������̵� �ǰ�, 
    // IOverrideMode = 1�̸� ���� ���� ��� ������ ������ ��ȣ������ ���ʷ� ����ȴ�.
    // IOverrideMode = 1�� �� �Լ��� ȣ���Ҷ����� �ּ� 1������ �ִ� 8������ �������̵� ť�� �����Ǹ鼭 �ڵ������� ������ �Ǹ�, ���� �� �������� IOverrideMode = 0���� �� �Լ��� ȣ��Ǹ�
    // ���������� �������̵� ť�� �ִ� ���� �������� ���Ӻ��� ť�� ����ǰ�, ��ȣ �������̵� ������ ������ ����� ���Ӻ����� ���������� ����ȴ�.
    [DllImport("AXL.dll")] public static extern uint AxmAdvOvrCircleRadiusMove(int lCoord, int[] lAxisNo, double dRadius, double[] dEndPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, uint uCWDir, uint uShortDistance, int lOverrideMode);

//======= �︮�� �̵� ===============================================================================================
    // ���ǻ��� : Helix�� ���Ӻ��� ���� Spline, ���������� ��ȣ������ ���� ����Ҽ�����.
    
    // ������ ��ǥ�迡 ������, �������� �߽����� �����Ͽ� �︮�� ���� �����ϴ� �Լ��̴�.
    // AxmAdvContiBeginNode, AxmAdvContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, �������� �߽����� �����Ͽ� �︮�� ���Ӻ��� �����ϴ� �Լ��̴�. 
    // ��ȣ ���� ���� ������ ���� ���� Queue�� �����ϴ� �Լ��̴�. AxmAdvContiStart�Լ��� ����ؼ� �����Ѵ�. (���Ӻ��� �Լ��� ���� �̿��Ѵ�)
    // dCenterPos = �߽��� X,Y  , dEndPos = ������ X,Y .
    // uCWDir DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����    	
    [DllImport("AXL.dll")] public static extern uint AxmAdvHelixCenterMove(int lCoord, double dCenterXPos, double dCenterYPos, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, uint uCWDir);
    // ������ ��ǥ�迡 ������, �������� �������� �����Ͽ� �︮�� ���� �����ϴ� �Լ��̴�. 
    // AxmAdvContiBeginNode, AxmAdvContiEndNode�� ���̻��� ������ ��ǥ�迡 �߰���, �������� �����Ͽ� �︮�ÿ��� ���� �����ϴ� �Լ��̴�. 
    // ��ȣ ���� ���� ������ ���� ���� Queue�� �����ϴ� �Լ��̴�. AxmAdvContiStart�Լ��� ����ؼ� �����Ѵ�. (���Ӻ��� �Լ��� ���� �̿��Ѵ�.)
    // dMidPos = �߰��� X,Y  , dEndPos = ������ X,Y 
    [DllImport("AXL.dll")] public static extern uint AxmAdvHelixPointMove(int lCoord, double dMidXPos, double dMidYPos, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel);
    // ������ ��ǥ�迡 ������, ȸ�������� �������� �����Ͽ� �︮�� ���� �����ϴ� �Լ��̴�
    // AxmAdvContiBeginNode, AxmAdvContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, ȸ�������� �������� �����Ͽ� �︮�ÿ��� ���� �����ϴ� �Լ��̴�. 
    // ��ȣ ���� ���� ������ ���� ���� Queue�� �����ϴ� �Լ��̴�. AxmAdvContiStart�Լ��� ����ؼ� �����Ѵ�. (���Ӻ��� �Լ��� ���� �̿��Ѵ�.)
    //dCenterPos = �߽��� X,Y  , dAngle = ����.
    // uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
    [DllImport("AXL.dll")] public static extern uint AxmAdvHelixAngleMove(int lCoord, double dCenterXPos, double dCenterYPos, double dAngle, double dZPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, uint uCWDir);
    // ������ ��ǥ�迡 ������, �������� �������� �����Ͽ� �︮�� ���� �����ϴ� �Լ��̴�.
    // AxmAdvContiBeginNode, AxmAdvContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, �������� �������� �����Ͽ� �︮�ÿ��� ���� �����ϴ� �Լ��̴�. 
    // ��ȣ ���� ���� ������ ���� ���� Queue�� �����ϴ� �Լ��̴�. AxmAdvContiStart�Լ��� ����ؼ� �����Ѵ�. (���Ӻ��� �Լ��� ���� �̿��Ѵ�.)
    // dRadius = ������, dEndPos = ������ X,Y  , uShortDistance = ������(0), ū��(1)
    // uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����   
    [DllImport("AXL.dll")] public static extern uint AxmAdvHelixRadiusMove(int lCoord, double dRadius, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, uint uCWDir, uint uShortDistance);
    // ������ ��ǥ�迡 �������� �������� �����Ͽ� 3�� �︮�� ���� �������̵� �����Ѵ�.
    // ���� �������� ���������� ������ �ӵ� �� ��ġ�� �︮�� ���� �������̵� �ϸ�, ���� ��忡 ���� �︮�� ���� ���� ���൵ �����Ѵ�.
    // IOverrideMode = 0�� ���, �������� ������ ����, ��ȣ ������ ������� ���� ���� ��忡�� �︮�� �������� ��� �������̵� �ǰ�, 
    // IOverrideMode = 1�̸� ���� ���� ��� ������ ������ �︮�� ������ ���ʷ� ����ȴ�.
    // IOverrideMode = 1�� �� �Լ��� ȣ���Ҷ����� �ּ� 1������ �ִ� 8������ �������̵� ť�� �����Ǹ鼭 �ڵ������� ������ �Ǹ�, ���� �� �������� IOverrideMode = 0���� �� �Լ��� ȣ��Ǹ�
    // ���������� �������̵� ť�� �ִ� ���� �������� ���Ӻ��� ť�� ����ǰ�, �︮�� �������̵� ������ ������ ����� ���Ӻ����� ���������� ����ȴ�.
    [DllImport("AXL.dll")] public static extern uint AxmAdvOvrHelixRadiusMove(int lCoord, double dRadius, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, uint uCWDir, uint uShortDistance, int lOverrideMode);

//====�Ϲ� �����Լ� =================================================================================================
    // ���� ������ ���� �����Ѵ�.
    // �������� �������� �����Ͽ� ���� ���� ������ ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
    // AxmAdvContiBeginNode, AxmAdvContiEndNode�� ���̻��� ������ ��ǥ�迡 �������� �������� �����Ͽ� ���� ���� �����ϴ� Queue�� �����Լ����ȴ�. 
    // ���� �������� ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmAdvContiStart�Լ��� ����ؼ� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmAdvScriptLineMove(int lCoordinate, double[] dPosition, double dMaxVelocity, double dStartVel, double dStopVel, double dMaxAccel, double dMaxDecel, uint dwScript, int lScirptAxisNo, double dScriptPos);
    // ������ ��ǥ�迡 �������� �������� �����ϴ� ���� ���� ���� �������̵带 ���� �����ϴ� �Լ��̴�.
    // ���� �������� ���������� ������ �ӵ� �� ��ġ�� ���� ���� �������̵带 ���� ���� �ϸ�, ���� ��忡 ���� ���� ���� ���� ������ �����Ѵ�.
    // IOverrideMode = 0�� ���, �������� ������ ����, ��ȣ ������ ������� ���� ���� ��忡�� ���� �������� ��� �������̵� �ǰ�, 
    // IOverrideMode = 1�̸� ���� ���� ��� ������ ������ ���������� ���ʷ� ����ȴ�.
    // IOverrideMode = 1�� �� �Լ��� ȣ���Ҷ����� �ּ� 1������ �ִ� 8������ �������̵� ť�� �����Ǹ鼭 �ڵ������� ������ �Ǹ�, ���� �� �������� IOverrideMode = 0���� �� �Լ��� ȣ��Ǹ�
    // ���������� �������̵� ť�� �ִ� ���� �������� ���Ӻ��� ť�� ����ǰ�, ���� �������̵� ������ ������ ����� ���Ӻ����� ���������� ����ȴ�.
    [DllImport("AXL.dll")] public static extern uint AxmAdvScriptOvrLineMove(int lCoordinate, double[] dPosition, double dMaxVelocity, double dStartVel, double dStopVel, double dMaxAccel, double dMaxDecel, int lOverrideMode, uint dwScript, int lScirptAxisNo, double dScriptPos);
    // 2�� ��ȣ������ ���� �����Ѵ�.
    // ������, �������� �߽����� �����Ͽ� ��ȣ ������ ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
    // AxmAdvContiBeginNode, AxmAdvContiEndNode, �� ���̻��� ������ ��ǥ�迡 ������, �������� �߽����� �����Ͽ� �����ϴ� ��ȣ ���� Queue�� �����Լ����ȴ�.
    // �������� ��ȣ ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmAdvContiStart�Լ��� ����ؼ� �����Ѵ�.
    // lAxisNo = ���� �迭 , dCenterPos = �߽��� X,Y �迭 , dEndPos = ������ X,Y �迭.
    // uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
    [DllImport("AXL.dll")] public static extern uint AxmAdvScriptCircleCenterMove(int lCoord, int[] lAxisNo, double[] dCenterPos, double[] dEndPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, uint uCWDir, uint dwScript, int lScirptAxisNo, double dScriptPos);
    // �߰���, �������� �����Ͽ� ��ȣ ������ ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
    // AxmAdvContiBeginNode, AxmAdvContiEndNode�� ���̻��� ������ ��ǥ�迡 �߰���, �������� �����Ͽ� �����ϴ� ��ȣ ���� Queue�� �����Լ����ȴ�.
    // �������� ��ȣ ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmAdvContiStart�Լ��� ����ؼ� �����Ѵ�.
    // lAxisNo = ���� �迭 , dMidPos = �߰��� X,Y �迭 , dEndPos = ������ X,Y �迭, lArcCircle = ��ũ(0), ��(1)
    [DllImport("AXL.dll")] public static extern uint AxmAdvScriptCirclePointMove(int lCoord, int[] lAxisNo, double[] dMidPos, double[] dEndPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, int lArcCircle, uint dwScript, int lScirptAxisNo, double dScriptPos);
    // ������, ȸ�������� �������� �����Ͽ� ��ȣ ������ ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
    // AxmAdvContiBeginNode, AxmAdvContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, ȸ�������� �������� �����Ͽ� ��ȣ ���� �����ϴ� Queue�� �����Լ����ȴ�.
    // �������� ��ȣ ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmAdvContiStart�Լ��� ����ؼ� �����Ѵ�.
    // lAxisNo = ���� �迭 , dCenterPos = �߽��� X,Y �迭 , dAngle = ����.
    // uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
    [DllImport("AXL.dll")] public static extern uint AxmAdvScriptCircleAngleMove(int lCoord, int[] lAxisNo, double[] dCenterPos, double dAngle, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, uint uCWDir, uint dwScript, int lScirptAxisNo, double dScriptPos);
    // ������, �������� �������� �����Ͽ� ��ȣ ������ ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
    // AxmAdvContiBeginNode, AxmAdvContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, �������� �������� �����Ͽ� ��ȣ ���� �����ϴ� Queue�� �����Լ����ȴ�.
    // �������� ��ȣ ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmAdvContiStart�Լ��� ����ؼ� �����Ѵ�.
    // lAxisNo = ���� �迭 , dRadius = ������, dEndPos = ������ X,Y �迭 , uShortDistance = ������(0), ū��(1)
    // uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
    [DllImport("AXL.dll")] public static extern uint AxmAdvScriptCircleRadiusMove(int lCoord, int[] lAxisNo, double dRadius, double[] dEndPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, uint uCWDir, uint uShortDistance, uint dwScript, int lScirptAxisNo, double dScriptPos);
    // ������ ��ǥ�迡 �������� �������� �����Ͽ� 2�� ��ȣ ���� �������̵带 ���� �����Ѵ�.
    // ���� �������� ���������� ������ �ӵ� �� ��ġ�� ��ȣ ���� �������̵��� ���� �����ϸ�, ���� ��忡 ���� ��ȣ ���� ���� ������ �����Ѵ�.
    // IOverrideMode = 0�� ���, �������� ������ ����, ��ȣ ������ ������� ���� ���� ��忡�� ��ȣ �������� ��� �������̵� �ǰ�, 
    // IOverrideMode = 1�̸� ���� ���� ��� ������ ������ ��ȣ������ ���ʷ� ����ȴ�.
    // IOverrideMode = 1�� �� �Լ��� ȣ���Ҷ����� �ּ� 1������ �ִ� 8������ �������̵� ť�� �����Ǹ鼭 �ڵ������� ������ �Ǹ�, ���� �� �������� IOverrideMode = 0���� �� �Լ��� ȣ��Ǹ�
    // ���������� �������̵� ť�� �ִ� ���� �������� ���Ӻ��� ť�� ����ǰ�, ��ȣ �������̵� ������ ������ ����� ���Ӻ����� ���������� ����ȴ�.
    [DllImport("AXL.dll")] public static extern uint AxmAdvScriptOvrCircleRadiusMove(int lCoord, int[] lAxisNo, double dRadius, double[] dEndPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, uint uCWDir, uint uShortDistance, int lOverrideMode, uint dwScript, int lScirptAxisNo, double dScriptPos);

//======= �︮�� �̵� ===============================================================================================
    // ���ǻ��� : Helix�� ���Ӻ��� ���� Spline, ���������� ��ȣ������ ���� ����Ҽ�����.

    // ������ ��ǥ�迡 ������, �������� �߽����� �����Ͽ� �︮�� ������ ���� �����ϴ� �Լ��̴�.
    // AxmAdvContiBeginNode, AxmAdvContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, �������� �߽����� �����Ͽ� �︮�� ���Ӻ����� ���� �����ϴ� �Լ��̴�. 
    // ��ȣ ���� ���� ������ ���� ���� Queue�� �����ϴ� �Լ��̴�. AxmAdvContiStart�Լ��� ����ؼ� �����Ѵ�. (���Ӻ��� �Լ��� ���� �̿��Ѵ�)
    // dCenterPos = �߽��� X,Y  , dEndPos = ������ X,Y .
    // uCWDir DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����	
    [DllImport("AXL.dll")] public static extern uint AxmAdvScriptHelixCenterMove(int lCoord, double dCenterXPos, double dCenterYPos, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, uint uCWDir, uint dwScript, int lScirptAxisNo, double dScriptPos);
    // ������ ��ǥ�迡 ������, �������� �������� �����Ͽ� �︮�� ������ ���� �����ϴ� �Լ��̴�. 
    // AxmAdvContiBeginNode, AxmAdvContiEndNode�� ���̻��� ������ ��ǥ�迡 �߰���, �������� �����Ͽ� �︮�ÿ��� ������ ���� �����ϴ� �Լ��̴�. 
    // ��ȣ ���� ���� ������ ���� ���� Queue�� �����ϴ� �Լ��̴�. AxmAdvContiStart�Լ��� ����ؼ� �����Ѵ�. (���Ӻ��� �Լ��� ���� �̿��Ѵ�.)
    // dMidPos = �߰��� X,Y  , dEndPos = ������ X,Y
    [DllImport("AXL.dll")] public static extern uint AxmAdvScriptHelixPointMove(int lCoord, double dMidXPos, double dMidYPos, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, uint dwScript, int lScirptAxisNo, double dScriptPos);
    // ������ ��ǥ�迡 ������, ȸ�������� �������� �����Ͽ� �︮�� ������ ���� �����ϴ� �Լ��̴�
    // AxmAdvContiBeginNode, AxmAdvContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, ȸ�������� �������� �����Ͽ� �︮�ÿ��� ������ ���� �����ϴ� �Լ��̴�. 
    // ��ȣ ���� ���� ������ ���� ���� Queue�� �����ϴ� �Լ��̴�. AxmAdvContiStart�Լ��� ����ؼ� �����Ѵ�. (���Ӻ��� �Լ��� ���� �̿��Ѵ�.)
    //dCenterPos = �߽��� X,Y  , dAngle = ����.
    // uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
    [DllImport("AXL.dll")] public static extern uint AxmAdvScriptHelixAngleMove(int lCoord, double dCenterXPos, double dCenterYPos, double dAngle, double dZPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, uint uCWDir, uint dwScript, int lScirptAxisNo, double dScriptPos);
    // ������ ��ǥ�迡 ������, �������� �������� �����Ͽ� �︮�� ������ ���� �����ϴ� �Լ��̴�.
    // AxmAdvContiBeginNode, AxmAdvContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, �������� �������� �����Ͽ� �︮�ÿ��� ������ ���� �����ϴ� �Լ��̴�. 
    // ��ȣ ���� ���� ������ ���� ���� Queue�� �����ϴ� �Լ��̴�. AxmAdvContiStart�Լ��� ����ؼ� �����Ѵ�. (���Ӻ��� �Լ��� ���� �̿��Ѵ�.)
    // dRadius = ������, dEndPos = ������ X,Y  , uShortDistance = ������(0), ū��(1)
    // uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����  
    [DllImport("AXL.dll")] public static extern uint AxmAdvScriptHelixRadiusMove(int lCoord, double dRadius, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, uint uCWDir, uint uShortDistance, uint dwScript, int lScirptAxisNo, double dScriptPos);
    // ������ ��ǥ�迡 �������� �������� �����Ͽ� 3�� �︮�� ���� �������̵带 ���� �����Ѵ�.
    // ���� �������� ���������� ������ �ӵ� �� ��ġ�� �︮�� ���� �������̵带 ���� �����Ѵ�.
    // IOverrideMode = 0�� ���, �������� ������ ����, ��ȣ ������ ������� ���� ���� ��忡�� �︮�� �������� ��� �������̵� �ǰ�, 
    // IOverrideMode = 1�̸� ���� ���� ��� ������ ������ �︮�� ������ ���ʷ� ����ȴ�.
    // IOverrideMode = 1�� �� �Լ��� ȣ���Ҷ����� �ּ� 1������ �ִ� 8������ �������̵� ť�� �����Ǹ鼭 �ڵ������� ������ �Ǹ�, ���� �� �������� IOverrideMode = 0���� �� �Լ��� ȣ��Ǹ�
    // ���������� �������̵� ť�� �ִ� ���� �������� ���Ӻ��� ť�� ����ǰ�, �︮�� �������̵� ������ ������ ����� ���Ӻ����� ���������� ����ȴ�.
    [DllImport("AXL.dll")] public static extern uint AxmAdvScriptOvrHelixRadiusMove(int lCoord, double dRadius, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, uint uCWDir, uint uShortDistance, int lOverrideMode, uint dwScript, int lScirptAxisNo, double dScriptPos);

//====���� ���� �Լ� ================================================================================================
    // ������ ��ǥ�迡 ���� ���� ���� �� ���� �������� ���� ���� �ε��� ��ȣ�� Ȯ���ϴ� �Լ��̴�.
    [DllImport("AXL.dll")] public static extern uint AxmAdvContiGetNodeNum(int lCoordinate, ref int lpNodeNum);
    // ������ ��ǥ�迡 ������ ���� ���� ���� �� �ε��� ������ Ȯ���ϴ� �Լ��̴�.
    [DllImport("AXL.dll")] public static extern uint AxmAdvContiGetTotalNodeNum(int lCoordinate, ref int lpNodeNum);
    // ������ ��ǥ�迡 ���� ������ ���� ���� Queue�� ����Ǿ� �ִ� ���� ���� ������ Ȯ���ϴ� �Լ��̴�.
    [DllImport("AXL.dll")] public static extern uint AxmAdvContiReadIndex(int lCoordinate, ref int lpQueueIndex);
    // ������ ��ǥ�迡 ���� ������ ���� ���� Queue�� ��� �ִ��� Ȯ���ϴ� �Լ��̴�.
    [DllImport("AXL.dll")] public static extern uint AxmAdvContiReadFree(int lCoordinate, ref uint upQueueFree);
    // ������ ��ǥ�迡 ���� ���� ������ ���� ����� ���� Queue�� ��� �����ϴ� �Լ��̴�.
    [DllImport("AXL.dll")] public static extern uint AxmAdvContiWriteClear(int lCoordinate);
    // ������ ��ǥ�迡 ���� ���� �������̵� ������ ���� ����� �������̵�� ť�� ��� �����ϴ� �Լ��̴�.
    [DllImport("AXL.dll")] public static extern uint AxmAdvOvrContiWriteClear(int lCoordinate);
    // ���� ���� ���� �Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmAdvContiStart(int lCoord, uint dwProfileset, int lAngle); 
    // ���� ���� ���� �Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmAdvContiStop(int lCoordinate, double dDecel);
    //������ ��ǥ�迡 ���Ӻ��� �� ������ �����Ѵ�.
    //(����� ��ȣ�� 0 ���� ����))
    // ������:  ������Ҷ��� �ݵ�� ���� ���ȣ�� ���� ���ں��� ū���ڸ� �ִ´�.
    //          ������ ���� �Լ��� ����Ͽ��� �� �������ȣ�� ���� ���ȣ�� ���� �� ���� lpAxesNo�� ���� ���ؽ��� �Է��Ͽ��� �Ѵ�.
    //          ������ ���� �Լ��� ����Ͽ��� �� �������ȣ�� �ش��ϴ� ���� ���ȣ�� �ٸ� ���̶�� �Ѵ�.
    //          ���� ���� �ٸ� Coordinate�� �ߺ� �������� ���ƾ� �Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmAdvContiSetAxisMap(int lCoord, int lSize, int[] lpAxesNo);
    //������ ��ǥ�迡 ���Ӻ��� �� ������ ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmAdvContiGetAxisMap(int lCoord, ref int lpSize, ref int lpAxesNo);
    // ������ ��ǥ�迡 ���Ӻ��� �� ����/��� ��带 �����Ѵ�.
    // (������ : �ݵ�� ����� �ϰ� ��밡��)
    // ���� ���� �̵� �Ÿ� ��� ��带 �����Ѵ�.
    //uAbsRelMode : POS_ABS_MODE '0' - ���� ��ǥ��
    //              POS_REL_MODE '1' - ��� ��ǥ��
    [DllImport("AXL.dll")] public static extern uint AxmAdvContiSetAbsRelMode(int lCoord, uint uAbsRelMode);
    // ������ ��ǥ�迡 ���Ӻ��� �� ����/��� ��带 ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmAdvContiGetAbsRelMode(int lCoord, ref uint uAbsRelMode);
    // ������ ��ǥ�迡 ���� ���� ���� ������ Ȯ���ϴ� �Լ��̴�.
    [DllImport("AXL.dll")] public static extern uint AxmAdvContiIsMotion(int lCoordinate, ref uint upInMotion);
    // ������ ��ǥ�迡 ���Ӻ������� ������ �۾����� ����� �����Ѵ�. ���Լ��� ȣ������,
    // AxmAdvContiEndNode�Լ��� ȣ��Ǳ� ������ ����Ǵ� ��� ����۾��� ���� ����� �����ϴ� ���� �ƴ϶� ���Ӻ��� ������� ��� �Ǵ� ���̸�,
    // AxmAdvContiStart �Լ��� ȣ��� �� ��μ� ��ϵȸ���� ������ ����ȴ�.
    [DllImport("AXL.dll")] public static extern uint AxmAdvContiBeginNode(int lCoord);
    // ������ ��ǥ�迡�� ���Ӻ����� ������ �۾����� ����� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmAdvContiEndNode(int lCoord);
    
    // ������ ������ ������ ���ӵ��� ���� ���� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMoveMultiStop(int lArraySize, int[] lpAxesNo, double[] dMaxDecel);
    // ������ ������ ���� �� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMoveMultiEStop(int lArraySize, int[] lpAxesNo);
    // ������ ������ ���� ���� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMoveMultiSStop(int lArraySize, int[] lpAxesNo);

    // ������ ���� ���� ���� �ӵ��� �о�´�.
    [DllImport("AXL.dll")] public static extern uint AxmStatusReadActVel(int lAxisNo, ref double dpVel);          //2010.10.11
    // ���� Ÿ�� �����̺� ����� SVCMD_STAT Ŀ�ǵ� ���� �д´�.
    [DllImport("AXL.dll")] public static extern uint AxmStatusReadServoCmdStat(int lAxisNo, ref uint upStatus);
    // ���� Ÿ�� �����̺� ����� SVCMD_CTRL Ŀ�ǵ� ���� �д´�.
    [DllImport("AXL.dll")] public static extern uint AxmStatusReadServoCmdCtrl(int lAxisNo, ref uint upStatus);
    
    // ��Ʈ�� ������ ������ ��� �����̺� �� ���� ��ġ ���� ���� ������ ���� �Ѱ谪�� ��ȯ�Ѵ�.    
    [DllImport("AXL.dll")] public static extern uint AxmGantryGetMstToSlvOverDist(int lAxisNo, ref double dpPosition);
    // ��Ʈ�� ������ ������ ��� �����̺� �� ���� ��ġ ���� ���� ���� �Ѱ谪�� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmGantrySetMstToSlvOverDist(int lAxisNo, double dPosition);

    // ���� ���� �˶� ��ȣ�� �ڵ� ���¸� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmSignalReadServoAlarmCode(int lAxisNo, ref ushort upCodeStatus);
    
    // ���� Ÿ�� �����̺� ����� ��ǥ�� ������ �ǽ��Ѵ�. (MLIII ����)
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoCoordinatesSet(int lAxisNo, uint dwPosData, uint dwPos_sel, uint dwRefe);
    // ���� Ÿ�� �����̺� ����� �극��ũ �۵� ��ȣ�� ����Ѵ�. (MLIII ����)
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoBreakOn(int lAxisNo);
    // ���� Ÿ�� �����̺� ����� �극��ũ �۵� ��ȣ�� �����Ѵ�. (MLIII ����)
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoBreakOff(int lAxisNo);
    // ���� Ÿ�� �����̺� ����� 
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoConfig(int lAxisNo, uint dwCfMode);
    // ���� Ÿ�� �����̺� ����� ���� ���� �ʱ�ȭ�� �䱸�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoSensOn(int lAxisNo);
    // ���� Ÿ�� �����̺� ����� �������� OFF�� �䱸�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoSensOff(int lAxisNo);
    // ���� Ÿ�� �����̺� ����� SMON Ŀ�ǵ带 �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoSmon(int lAxisNo);
    // ���� Ÿ�� �����̺� ����� ����� ������ ����� ��ȣ�� ���¸� �д´�.
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoGetSmon(int lAxisNo, ref uint pbParam);
    // ���� Ÿ�� �����̺� ��⿡ ���� ON�� �䱸�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoSvOn(int lAxisNo);
    // ���� Ÿ�� �����̺� ��⿡ ���� OFF�� �䱸�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoSvOff(int lAxisNo);
    // ���� Ÿ�� �����̺� ��Ⱑ ������ ���� ��ġ�� �����̵��� �ǽ��Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoInterpolate(int lAxisNo, uint dwTPOS, uint dwVFF, uint dwTFF, uint dwTLIM);
    // ���� Ÿ�� �����̺� ��Ⱑ ������ ��ġ�� ��ġ�̼��� �ǽ��Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoPosing(int lAxisNo, uint dwTPOS, uint dwSPD, uint dwACCR, uint dwDECR, uint dwTLIM);
    // ���� Ÿ�� �����̺� ��Ⱑ ������ �̵��ӵ��� �����̼��� �ǽ��Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoFeed(int lAxisNo, uint dwSPD, uint dwACCR, uint dwDECR, uint dwTLIM);
    // ���� Ÿ�� �����̺� ��Ⱑ �̼��� �ܺ� ��ġ���� ��ȣ�� �Է¿� ���� ��ġ�̼��� �ǽ��Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoExFeed(int lAxisNo, uint dwSPD, uint dwACCR, uint dwDECR, uint dwTLIM, uint dwExSig1, uint dwExSig2);
    // ���� Ÿ�� �����̺� ��Ⱑ �ܺ� ��ġ���� ��ȣ �Է¿� ���� ��ġ�̼��� �ǽ��Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoExPosing(int lAxisNo, uint dwTPOS, uint dwSPD, uint dwACCR, uint dwDECR, uint dwTLIM, uint dwExSig1, uint dwExSig2);
    // ���� Ÿ�� �����̺� ��Ⱑ ���� ���͸� �ǽ��Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoZret(int lAxisNo, uint dwSPD, uint dwACCR, uint dwDECR, uint dwTLIM, uint dwExSig1, uint dwExSig2, uint bHomeDir, uint bHomeType);
    // ���� Ÿ�� �����̺� ��Ⱑ �ӵ���� �ǽ��Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoVelctrl(int lAxisNo, uint dwTFF, uint dwVREF, uint dwACCR, uint dwDECR, uint dwTLIM);
    // ���� Ÿ�� �����̺� ��Ⱑ ��ũ��� �ǽ��Ѵ�.    
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoTrqctrl(int lAxisNo, uint dwVLIM, int lTQREF);
    // bmode 0x00 : common parameters ram
    // bmode 0x01 : common parameters flash
    // bmode 0x10 : device parameters ram
    // bmode 0x11 : device parameters flash
    // ���� Ÿ�� �����̺� ����� ������ Ư�� �Ķ���� �������� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoGetParameter(int lAxisNo, uint wNo, uint bSize, uint bMode, ref uint pbParam);
    // ���� Ÿ�� �����̺� ����� ������ Ư�� �Ķ���� ���� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoSetParameter(int lAxisNo, uint wNo, uint bSize, uint bMode, ref uint pbParam);

    // M3 �����ѿ� Command Execution�� �����Ѵ�
    [DllImport("AXL.dll")] public static extern uint AxmServoCmdExecution(int lAxisNo, uint dwCommand, uint dwSize, ref uint pdwExcData);
    // ���� Ÿ�� �����̺� ����� ������ ��ũ ���� ���� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoGetTorqLimit(int lAxisNo, ref uint dwpTorqLimit);
    // ���� Ÿ�� �����̺� ��⿡ ��ũ ���� ���� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoSetTorqLimit(int lAxisNo, uint dwTorqLimit);

    // ���� Ÿ�� �����̺� ��⿡ ������ SVCMD_IO Ŀ�ǵ� ���� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoGetSendSvCmdIOOutput(int lAxisNo, ref uint dwData);
    // ���� Ÿ�� �����̺� ��⿡ SVCMD_IO Ŀ�ǵ� ���� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoSetSendSvCmdIOOutput(int lAxisNo, uint dwData);
  
    // ���� Ÿ�� �����̺� ��⿡ ������ SVCMD_CTRL Ŀ�ǵ� ���� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoGetSvCmdCtrl(int lAxisNo, ref uint dwData);
    // ���� Ÿ�� �����̺� ��⿡ SVCMD_CTRL Ŀ�ǵ� ���� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmM3ServoSetSvCmdCtrl(int lAxisNo, uint dwData);

    // MLIII adjustment operation�� ���� �Ѵ�.
    // dwReqCode == 0x1005 : parameter initialization : 20sec
    // dwReqCode == 0x1008 : absolute encoder reset   : 5sec
    // dwReqCode == 0x100E : automatic offset adjustment of motor current detection signals  : 5sec
    // dwReqCode == 0x1013 : Multiturn limit setting  : 5sec
	[DllImport("AXL.dll")] public static extern uint AxmM3AdjustmentOperation(int lAxisNo, uint dwReqCode);
    // ���� �� �߰� ����͸� ä�κ� ���� ���� �����Ѵ�.
	[DllImport("AXL.dll")] public static extern uint AxmM3ServoSetMonSel(int lAxisNo, uint dwMon0, uint dwMon1, uint dwMon2);
    // ���� �� �߰� ����͸� ä�κ� ���� ���� ��ȯ�Ѵ�.
	[DllImport("AXL.dll")] public static extern uint AxmM3ServoGetMonSel(int lAxisNo, ref uint upMon0, ref uint upMon1, ref uint upMon2);
    // ���� �� �߰� ����͸� ä�κ� ���� ���� �������� ���� ���¸� ��ȯ�Ѵ�.
	[DllImport("AXL.dll")] public static extern uint AxmM3ServoReadMonData(int lAxisNo, uint dwMonSel, ref uint dwpMonData);
    // ������ ��ũ �� ����
	[DllImport("AXL.dll")] public static extern uint AxmAdvTorqueContiSetAxisMap(int lCoord, int lSize, int[] lpAxesNo, uint dwTLIM, uint dwConMode);
	// 2014.04.28
	// ��ũ �������� ���� �Ķ����
	[DllImport("AXL.dll")] public static extern uint AxmM3ServoSetTorqProfile(int lCoord, int lAxisNo, int TorqueSign, uint dwVLIM, uint dwProfileMode, uint dwStdTorq, uint dwStopTorq);
    // ��ũ �������� Ȯ�� �Ķ����
	[DllImport("AXL.dll")] public static extern uint AxmM3ServoGetTorqProfile(int lCoord, int lAxisNo, ref int lpTorqueSign, ref uint updwVLIM, ref uint upProfileMode, ref uint upStdTorq, ref uint upStopTorq);
//-------------------------------------------------------------------------------------------------------------------
    	//======== SMP ���� �Լ� =======================================================================================
    // Inposition ��ȣ�� Range�� �����Ѵ�. (dInposRange > 0)
    [DllImport("AXL.dll")] public static extern uint AxmSignalSetInposRange(int lAxisNo, double dInposRange);
    // Inposition ��ȣ�� Range�� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmSignalGetInposRange(int lAxisNo, ref double dpInposRange);

    // �������̵��Ҷ� ��ġ�Ӽ�(����/���)�� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMotSetOverridePosMode(int lAxisNo, uint dwAbsRelMode);
    // �������̵��Ҷ� ��ġ�Ӽ�(����/���)�� �о�´�.
    [DllImport("AXL.dll")] public static extern uint AxmMotGetOverridePosMode(int lAxisNo, ref uint dwpAbsRelMode);
    // LineMove �������̵��Ҷ� ��ġ�Ӽ�(����/���)�� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMotSetOverrideLinePosMode(int lCoordNo, uint dwAbsRelMode);
    // LineMove �������̵��Ҷ� ��ġ�Ӽ�(����/���)�� �о�´�.
    [DllImport("AXL.dll")] public static extern uint AxmMotGetOverrideLinePosMode(int lCoordNo, ref uint dwpAbsRelMode);

    // AxmMoveStartPos�� �����ϸ� ����ӵ�(EndVel)�� �߰��Ǿ���.
    [DllImport("AXL.dll")] public static extern uint AxmMoveStartPosEx(int lAxisNo, double dPos, double dVel, double dAccel, double dDecel, double dEndVel);
    // AxmMovePos�� �����ϸ� ����ӵ�(EndVel)�� �߰��Ǿ���.
    [DllImport("AXL.dll")] public static extern uint AxmMovePosEx(int lAxisNo, double dPos, double dVel, double dAccel, double dDecel, double dEndVel);

    // Coordinate Motion�� ��λ󿡼� ��������(dDecel) ��Ų��.
    [DllImport("AXL.dll")] public static extern uint AxmMoveCoordStop(int lCoordNo, double dDecel); 
    // Coordinate Motion�� ������ ��Ų��.
    [DllImport("AXL.dll")] public static extern uint AxmMoveCoordEStop(int lCoordNo);
    // Coordinate Motion�� ��λ󿡼� �������� ��Ų��.
    [DllImport("AXL.dll")] public static extern uint AxmMoveCoordSStop(int lCoordNo);

    // AxmLineMove����� ��ġ�� �������̵� ��Ų��.
    [DllImport("AXL.dll")] public static extern uint AxmOverrideLinePos(int lCoordNo, ref double dpOverridePos);
    // AxmLineMove����� �ӵ��� �������̵� ��Ų��. ������� �ӵ������� dpDistance�� �����ȴ�.
    [DllImport("AXL.dll")] public static extern uint AxmOverrideLineVel(int lCoordNo, double dOverrideVel, ref double dpDistance);

    // AxmLineMove����� �ӵ��� �������̵� ��Ų��.
    // dMaxAccel  : �������̵� ���ӵ�
    // dMaxDecel  : �������̵� ���ӵ�
    // dpDistance : ������ �ӵ� ����
    [DllImport("AXL.dll")] public static extern uint AxmOverrideLineAccelVelDecel(int lCoordNo, double dOverrideVelocity, double dMaxAccel, double dMaxDecel, ref double dpDistance);
    // AxmOverrideVelAtPos�� �߰������� AccelDecel�� �������̵� ��Ų��.
    [DllImport("AXL.dll")] public static extern uint AxmOverrideAccelVelDecelAtPos(int lAxisNo, double dPos, double dVel, double dAccel, double dDecel, double dOverridePos, double dOverrideVel, double dOverrideAccel, double dOverrideDecel, int lTarget);

    // �ϳ��� �������࿡ �ټ��� �����̺������ �����Ѵ�(Electronic Gearing).
    // lMasterAxisNo : ��������
    // lSize : �����̺��� ����(�ִ� 8)
    // lpSlaveAxisNo : �����̺��� ��ȣ
    // dpGearRatio : ���������� ���������ϴ� �����̺��� ����(0�� ����, 1 = 100%)
    [DllImport("AXL.dll")] public static extern uint AxmEGearSet(int lMasterAxisNo, int lSize, ref int lpSlaveAxisNo, ref double dpGearRatio);
    // Electronic Gearing������ �о�´�.
    [DllImport("AXL.dll")] public static extern uint AxmEGearGet(int lMasterAxisNo, ref int lpSize, ref int lpSlaveAxisNo, ref double dpGearRatio);
    // Electronic Gearing�� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmEGearReset(int lMasterAxisNo);
    // Electronic Gearing�� Ȱ��/��Ȱ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmEGearEnable(int lMasterAxisNo, uint dwEnable);
    // Electronic Gearing�� Ȱ��/��Ȱ�����¸� �о�´�.
    [DllImport("AXL.dll")] public static extern uint AxmEGearIsEnable(int lMasterAxisNo, ref uint dwpEnable);    

    // ���ǻ���: �Է��� ����ӵ��� '0'�̸��̸� '0'����, 'AxmMotSetMaxVel'�� ������ �ִ�ӵ��� �ʰ��ϸ� 'MaxVel'�� �缳���ȴ�. 
    // ���� �࿡ ����ӵ��� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMotSetEndVel(int lAxisNo, double dEndVelocity);
    // ���� ���� ����ӵ��� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxmMotGetEndVel(int lAxisNo, ref double dpEndVelocity);

}
