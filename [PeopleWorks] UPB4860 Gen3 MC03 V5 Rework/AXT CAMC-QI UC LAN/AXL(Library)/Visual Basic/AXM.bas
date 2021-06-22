Attribute VB_Name = "AXM"
'****************************************************************************
'*****************************************************************************
'**
'** File Name
'** ----------
'**
'** AXM.BAS
'**
'** COPYRIGHT (c) AJINEXTEK Co., LTD
'**
'*****************************************************************************
'*****************************************************************************
'**
'** Description
'** -----------
'** Ajinextek Motion Library Header File
'**
'**
'*****************************************************************************
'*****************************************************************************
'**
'** Source Change Indices
'** ---------------------
'**
'** (None)
'**
'**
'*****************************************************************************
'*****************************************************************************
'**
'** Website
'** ---------------------
'**
'** http:'www.ajinextek.com
'**
'*****************************************************************************
'*****************************************************************************
'*
'========== ���� �� ��� Ȯ���Լ�(Info) - Infomation ================================================================
' �ش� ���� �����ȣ, ��� ��ġ, ��� ���̵� ��ȯ�Ѵ�.
Public Declare Function AxmInfoGetAxis Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpBoardNo As Long, ByRef lpModulePos As Long, ByRef upModuleID As Long) As Long
' ��� ����� �����ϴ��� ��ȯ�Ѵ�.
Public Declare Function AxmInfoIsMotionModule Lib "AXL.dll" (ByRef upStatus As Long) As Long
' �ش� ���� ��ȿ���� ��ȯ�Ѵ�.
Public Declare Function AxmInfoIsInvalidAxisNo Lib "AXL.dll" (ByVal lAxisNo As Long) As Long
' �ش� ���� ��� ������ �������� ��ȯ�Ѵ�.
Public Declare Function AxmInfoGetAxisStatus Lib "AXL.dll" (ByVal lAxisNo As Long) As Long
' �� ����, �ý��ۿ� ������ ��ȿ�� ��� ����� ��ȯ�Ѵ�.
Public Declare Function AxmInfoGetAxisCount Lib "AXL.dll" (ByRef lpAxisCount As Long) As Long
' �ش� ����/����� ù��° ���ȣ�� ��ȯ�Ѵ�.
Public Declare Function AxmInfoGetFirstAxisNo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef lpAxisNo As Long) As Long
' �ش� ������ ù��° ���ȣ�� ��ȯ�Ѵ�.
Public Declare Function AxmInfoGetBoardFirstAxisNo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef lpAxisNo As Long) As Long

'========= ���� �� �Լ� =============================================================================================
' �ʱ� ���¿��� AXM ��� �Լ��� ���ȣ ������ 0 ~ (���� �ý��ۿ� ������ ��� - 1) �������� ��ȿ������
' �� �Լ��� ����Ͽ� ���� ������ ���ȣ ��� ������ ���ȣ�� �ٲ� �� �ִ�.
' �� �Լ��� ���� �ý����� H/W ������� �߻��� ���� ���α׷��� �Ҵ�� ���ȣ�� �״�� �����ϰ� ���� ���� ����
' �������� ��ġ�� �����Ͽ� ����� ���� ������� �Լ��̴�.
' ���ǻ��� : ���� ���� ���� ���ȣ�� ���Ͽ� ���� ��ȣ�� ���� ���� �ߺ��ؼ� ������ ���
'            ���� ���ȣ�� ���� �ุ ���� ���ȣ�� ���� �� �� ������,
'            ������ ���� ������ ��ȣ�� ���ε� ���� ��� �Ұ����� ��찡 �߻� �� �� �ִ�.

' �������� �����Ѵ�.
Public Declare Function AxmVirtualSetAxisNoMap Lib "AXL.dll" (ByVal lRealAxisNo As Long, ByVal lVirtualAxisNo As Long) As Long
' ������ ����ä��(��) ��ȣ�� ��ȯ�Ѵ�.
Public Declare Function AxmVirtualGetAxisNoMap Lib "AXL.dll" (ByVal lRealAxisNo As Long, ByRef lpVirtualAxisNo As Long) As Long
' ��Ƽ �������� �����Ѵ�.
Public Declare Function AxmVirtualSetMultiAxisNoMap Lib "AXL.dll" (ByVal lSize As Long, ByRef lpRealAxesNo As Long, ByRef lpVirtualAxesNo As Long) As Long
' ������ ��Ƽ ����ä��(��) ��ȣ�� ��ȯ�Ѵ�.
Public Declare Function AxmVirtualGetMultiAxisNoMap Lib "AXL.dll" (ByVal lSize As Long, ByRef lpRealAxesNo As Long, ByRef lpVirtualAxesNo As Long) As Long
' ������ ������ �����Ѵ�.
Public Declare Function AxmVirtualResetAxisMap Lib "AXL.dll" () As Long

'========= ���ͷ�Ʈ ���� �Լ� =======================================================================================
' �ݹ� �Լ� ����� �̺�Ʈ �߻� ������ ��� �ݹ� �Լ��� ȣ�� ������ ���� ������ �̺�Ʈ�� �������� �� �ִ� ������ ������
' �ݹ� �Լ��� ������ ���� �� ������ ���� ���μ����� ��ü�Ǿ� �ְ� �ȴ�.
' ��, �ݹ� �Լ� ���� ���ϰ� �ɸ��� �۾��� ���� ��쿡�� ��뿡 ���Ǹ� ���Ѵ�.
' �̺�Ʈ ����� ��������� �̿��Ͽ� ���ͷ�Ʈ �߻����θ� ���������� �����ϰ� �ִٰ� ���ͷ�Ʈ�� �߻��ϸ�
' ó�����ִ� �������, ������ ������ ���� �ý��� �ڿ��� �����ϰ� �ִ� ������ ������
' ���� ������ ���ͷ�Ʈ�� �����ϰ� ó������ �� �ִ� ������ �ִ�.
' �Ϲ������δ� ���� ������ ������, ���ͷ�Ʈ�� ����ó���� �ֿ� ���ɻ��� ��쿡 ���ȴ�.
' �̺�Ʈ ����� �̺�Ʈ�� �߻� ���θ� �����ϴ� Ư�� �����带 ����Ͽ� ���� ���μ����� ������ ���۵ǹǷ�
' MultiProcessor �ý��۵�� �ڿ��� ���� ȿ�������� ����� �� �ְ� �Ǿ� Ư�� �����ϴ� ����̴�.
' ���ͷ�Ʈ �޽����� �޾ƿ��� ���Ͽ� ������ �޽��� �Ǵ� �ݹ� �Լ��� ����Ѵ�.
' (�޽��� �ڵ�, �޽��� ID, �ݹ��Լ�, ���ͷ�Ʈ �̺�Ʈ)
'    hWnd    : ������ �ڵ�, ������ �޼����� ������ ���. ������� ������ NULL�� �Է�.
'    wMsg    : ������ �ڵ��� �޼���, ������� �ʰų� ����Ʈ���� ����Ϸ��� 0�� �Է�.
'    proc    : ���ͷ�Ʈ �߻��� ȣ��� �Լ��� ������, ������� ������ NULL�� �Է�.
'    pEvent  : �̺�Ʈ ������� �̺�Ʈ �ڵ�
Public Declare Function AxmInterruptSetAxis Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal hWnd As Long, ByVal uMessage As Long, ByVal pProc As Long, ByRef pEvent As Long) As Long

' ���� ���� ���ͷ�Ʈ ��� ���θ� �����Ѵ�
' �ش� �࿡ ���ͷ�Ʈ ���� / Ȯ��
' uUse : ��� ���� => DISABLE(0), ENABLE(1)
Public Declare Function AxmInterruptSetAxisEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uUse As Long) As Long
' ���� ���� ���ͷ�Ʈ ��� ���θ� ��ȯ�Ѵ�
Public Declare Function AxmInterruptGetAxisEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upUse As Long) As Long

'���ͷ�Ʈ�� �̺�Ʈ ������� ����� ��� �ش� ���ͷ�Ʈ ���� �д´�.
Public Declare Function AxmInterruptRead Lib "AXL.dll" (ByRef lpAxisNo As Long, ByRef upFlag As Long) As Long
' �ش� ���� ���ͷ�Ʈ �÷��� ���� ��ȯ�Ѵ�.
Public Declare Function AxmInterruptReadAxisFlag Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lBank As Long, ByRef upFlag As Long) As Long

' ���� ���� ����ڰ� ������ ���ͷ�Ʈ �߻� ���θ� �����Ѵ�.
' lBank         : ���ͷ�Ʈ ��ũ ��ȣ (0 - 1) ��������.
' uInterruptNum : ���ͷ�Ʈ ��ȣ ���� ��Ʈ��ȣ�� ���� hex�� Ȥ�� define�Ȱ��� ����
' AXHS.h���Ͽ� INTERRUPT_BANK1, 2 DEF�� Ȯ���Ѵ�.
Public Declare Function AxmInterruptSetUserEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lBank As Long, ByVal lInterruptNum As Long) As Long
' ���� ���� ����ڰ� ������ ���ͷ�Ʈ �߻� ���θ� Ȯ���Ѵ�.
Public Declare Function AxmInterruptGetUserEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lBank As Long, ByRef upInterruptNum As Long) As Long

'======== ��� �Ķ��Ÿ ���� ========================================================================================
' AxmMotLoadParaAll�� ������ Load ��Ű�� ������ �ʱ� �Ķ��Ÿ ������ �⺻ �Ķ��Ÿ ����.
' ���� PC�� ���Ǵ� ����࿡ �Ȱ��� ����ȴ�. �⺻�Ķ��Ÿ�� �Ʒ��� ����.
' 00:AXIS_NO.             =0          01:PULSE_OUT_METHOD.    =4         02:ENC_INPUT_METHOD.    =3     03:INPOSITION.          =2
' 04:ALARM.               =1          05:NEG_END_LIMIT.       =1         06:POS_END_LIMIT.       =1     07:MIN_VELOCITY.        =1
' 08:MAX_VELOCITY.        =700000     09:HOME_SIGNAL.         =4         10:HOME_LEVEL.          =1     11:HOME_DIR.            =0
' 12:ZPHASE_LEVEL.        =1          13:ZPHASE_USE.          =0         14:STOP_SIGNAL_MODE.    =0     15:STOP_SIGNAL_LEVEL.   =1
' 16:HOME_FIRST_VELOCITY. =100        17:HOME_SECOND_VELOCITY.=100       18:HOME_THIRD_VELOCITY. =20    19:HOME_LAST_VELOCITY.  =1
' 20:HOME_FIRST_ACCEL.    =400        21:HOME_SECOND_ACCEL.   =400       22:HOME_END_CLEAR_TIME. =1000  23:HOME_END_OFFSET.     =0
' 24:NEG_SOFT_LIMIT.      =-134217728 25:POS_SOFT_LIMIT.      =134217727 26:MOVE_PULSE.          =1     27:MOVE_UNIT.           =1
' 28:INIT_POSITION.       =1000       29:INIT_VELOCITY.       =200       30:INIT_ACCEL.          =400   31:INIT_DECEL.          =400
' 32:INIT_ABSRELMODE.     =0          33:INIT_PROFILEMODE.    =4         34:SVON_LEVEL.          =1     35:ALARM_RESET_LEVEL.   =1
' 36:ENCODER_TYPE.        =1          37:SOFT_LIMIT_SEL.      =0         38:SOFT_LIMIT_STOP_MODE.=0     39:SOFT_LIMIT_ENABLE.   =0

' 00=[AXIS_NO             ]: �� (0�� ���� ������)
' 01=[PULSE_OUT_METHOD    ]: Pulse out method TwocwccwHigh = 6
' 02=[ENC_INPUT_METHOD    ]: disable = 0, 1ü�� = 1, 2ü�� = 2, 4ü�� = 3, �ἱ ���ù��� ��ü��(-).1ü�� = 11  2ü�� = 12  4ü�� = 13
' 03=[INPOSITION          ], 04=[ALARM     ], 05,06 =[END_LIMIT   ]  : 0 = B����, 1= A����, 2 = ������, 3 = �������� ����
' 07=[MIN_VELOCITY        ]: ���� �ӵ�(START VELOCITY)
' 08=[MAX_VELOCITY        ]: ����̹��� ������ �޾Ƶ��ϼ� �ִ� ���� �ӵ�. ���� �Ϲ� Servo�� 700k
' Ex> screw : 20mm pitch drive: 10000 pulse ����: 400w
' 09=[HOME_SIGNAL         ]: 4 - Home in0 , 0 :PosEndLimit , 1 : NegEndLimit ' _HOME_SIGNAL����.
' 10=[HOME_LEVEL          ]: 0 = B����, 1 = A����, 2 = ������, 3 = �������� ����
' 11=[HOME_DIR            ]: Ȩ ����(HOME DIRECTION) 1:+����, 0:-����
' 12=[ZPHASE_LEVEL        ]: 0 = B����, 1 = B����, 2 = ������, 3 = �������� ����
' 13=[ZPHASE_USE          ]: Z���뿩��. 0: ������ , 1: +����, 2: -����
' 14=[STOP_SIGNAL_MODE    ]: ESTOP, SSTOP ���� ��� 0:��������, 1:������
' 15=[STOP_SIGNAL_LEVEL   ]: ESTOP, SSTOP ��� ����.  0 = B����, 1 = A����, 2 = ������, 3 = �������� ����
' 16=[HOME_FIRST_VELOCITY ]: 1�������ӵ�
' 17=[HOME_SECOND_VELOCITY]: �����ļӵ�
' 18=[HOME_THIRD_VELOCITY ]: ������ �ӵ�
' 19=[HOME_LAST_VELOCITY  ]: index�˻��� �����ϰ� �˻��ϱ����� �ӵ�.
' 20=[HOME_FIRST_ACCEL    ]: 1�� ���ӵ� , 21=[HOME_SECOND_ACCEL   ] : 2�� ���ӵ�
' 22=[HOME_END_CLEAR_TIME ]: ���� �˻� Enc �� Set�ϱ� ���� ���ð�,  23=[HOME_END_OFFSET] : ���������� Offset��ŭ �̵�.
' 24=[NEG_SOFT_LIMIT      ]: - SoftWare Limit ���� �����ϸ� ������, 25=[POS_SOFT_LIMIT ]: + SoftWare Limit ���� �����ϸ� ������.
' 26=[MOVE_PULSE          ]: ����̹��� 1ȸ���� �޽���              , 27=[MOVE_UNIT  ]: ����̹� 1ȸ���� �̵��� ��:��ũ�� Pitch
' 28=[INIT_POSITION       ]: ������Ʈ ���� �ʱ���ġ  , ����ڰ� ���Ƿ� ��밡��
' 29=[INIT_VELOCITY       ]: ������Ʈ ���� �ʱ�ӵ�  , ����ڰ� ���Ƿ� ��밡��
' 30=[INIT_ACCEL          ]: ������Ʈ ���� �ʱⰡ�ӵ�, ����ڰ� ���Ƿ� ��밡��
' 31=[INIT_DECEL          ]: ������Ʈ ���� �ʱⰨ�ӵ�, ����ڰ� ���Ƿ� ��밡��
' 32=[INIT_ABSRELMODE     ]: ����(0)/���(1) ��ġ ����
' 33=[INIT_PROFILEMODE    ]: �������ϸ��(0 - 4) ���� ����
'                            '0': ��Ī Trapezode, '1': ���Ī Trapezode, '2': ��Ī Quasi-S Curve, '3':��Ī S Curve, '4':���Ī S Curve
' 34=[SVON_LEVEL          ]: 0 = B����, 1 = A����
' 35=[ALARM_RESET_LEVEL   ]: 0 = B����, 1 = A����
' 36=[ENCODER_TYPE        ]: 0 = TYPE_INCREMENTAL, 1 = TYPE_ABSOLUTE
' 37=[SOFT_LIMIT_SEL      ]: 0 = COMMAND, 1 = ACTUAL
' 38=[SOFT_LIMIT_STOP_MODE]: 0 = EMERGENCY_STOP, 1 = SLOWDOWN_STOP
' 39=[SOFT_LIMIT_ENABLE   ]: 0 = DISABLE, 1 = ENABLE

' AxmMotSaveParaAll�� ���� �Ǿ��� .mot������ �ҷ��´�. �ش� ������ ����ڰ� Edit �Ͽ� ��� �����ϴ�.
Public Declare Function AxmMotLoadParaAll Lib "AXL.dll" (ByVal szFilePath As String) As Long
' ����࿡ ���� ��� �Ķ��Ÿ�� �ະ�� �����Ѵ�. .mot���Ϸ� �����Ѵ�.
Public Declare Function AxmMotSaveParaAll Lib "AXL.dll" (ByVal szFilePath As String) As Long

' �Ķ��Ÿ 28 - 33������ ����ڰ� ���α׷�������  �� �Լ��� �̿��� ���� �Ѵ�
Public Declare Function AxmMotSetParaLoad Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dInitPos As Double, ByVal dInitVel As Double, ByVal dInitAccel As Double, ByVal dInitDecel As Double) As Long
' �Ķ��Ÿ 28 - 33������ ����ڰ� ���α׷�������  �� �Լ��� �̿��� Ȯ�� �Ѵ�.
Public Declare Function AxmMotGetParaLoad Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpInitPos As Double, ByRef dpInitVel As Double, ByRef dpInitAccel As Double, ByRef dpInitDecel As Double) As Long

' ���� ���� �޽� ��� ����� �����Ѵ�.
' uMethod  0 :OneHighLowHigh, 1 :OneHighHighLow, 2 :OneLowLowHigh, 3 :OneLowHighLow, 4 :TwoCcwCwHigh
'          5 :TwoCcwCwLow, 6 :TwoCwCcwHigh, 7 :TwoCwCcwLow, 8 :TwoPhase, 9 :TwoPhaseReverse
'    OneHighLowHigh             = 0x0,            ' 1�޽� ���, PULSE(Active High), ������(DIR=Low)  / ������(DIR=High)
'    OneHighHighLow             = 0x1,            ' 1�޽� ���, PULSE(Active High), ������(DIR=High) / ������(DIR=Low)
'    OneLowLowHigh              = 0x2,            ' 1�޽� ���, PULSE(Active Low),  ������(DIR=Low)  / ������(DIR=High)
'    OneLowHighLow              = 0x3,            ' 1�޽� ���, PULSE(Active Low),  ������(DIR=High) / ������(DIR=Low)
'    TwoCcwCwHigh               = 0x4,            ' 2�޽� ���, PULSE(CCW:������),  DIR(CW:������),  Active High
'    TwoCcwCwLow                = 0x5,            ' 2�޽� ���, PULSE(CCW:������),  DIR(CW:������),  Active Low
'    TwoCwCcwHigh               = 0x6,            ' 2�޽� ���, PULSE(CW:������),   DIR(CCW:������), Active High
'    TwoCwCcwLow                = 0x7,            ' 2�޽� ���, PULSE(CW:������),   DIR(CCW:������), Active Low
'    TwoPhase                   = 0x8,            ' 2��(90' ������),  PULSE lead DIR(CW: ������), PULSE lag DIR(CCW:������)
'    TwoPhaseReverse            = 0x9             ' 2��(90' ������),  PULSE lead DIR(CCW: ������), PULSE lag DIR(CW:������)
Public Declare Function AxmMotSetPulseOutMethod Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uMethod As Long) As Long
' ���� ���� �޽� ��� ��� ������ ��ȯ�Ѵ�,
Public Declare Function AxmMotGetPulseOutMethod Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upMethod As Long) As Long

' ���� ���� �ܺ�(Actual) ī��Ʈ�� ���� ���� ������ �����Ͽ� ���� ���� Encoder �Է� ����� �����Ѵ�.
'    uMethod : 0 - 7 ����.
'    ObverseUpDownMode          = 0x0,            ' ������ Up/Down
'    ObverseSqr1Mode            = 0x1,            ' ������ 1ü��
'    ObverseSqr2Mode            = 0x2,            ' ������ 2ü��
'    ObverseSqr4Mode            = 0x3,            ' ������ 4ü��
'    ReverseUpDownMode          = 0x4,            ' ������ Up/Down
'    ReverseSqr1Mode            = 0x5,            ' ������ 1ü��
'    ReverseSqr2Mode            = 0x6,            ' ������ 2ü��
'    ReverseSqr4Mode            = 0x7             ' ������ 4ü��
Public Declare Function AxmMotSetEncInputMethod Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uMethod As Long) As Long
' ���� ���� �ܺ�(Actual) ī��Ʈ�� ���� ���� ������ �����Ͽ� ���� ���� Encoder �Է� ����� ��ȯ�Ѵ�.
Public Declare Function AxmMotGetEncInputMethod Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upMethod As Long) As Long

' ���� �ӵ� ������ RPM(Revolution Per Minute)���� ���߰� �ʹٸ�.
' ex>   rpm ���:
' 4500 rpm ?
' unit/ pulse = 1 : 1�̸�      pulse/ sec �ʴ� �޽����� �Ǵµ�
' 4500 rpm�� ���߰� �ʹٸ�     4500 / 60 �� : 75ȸ��/ 1��
' ���Ͱ� 1ȸ���� �� �޽����� �˾ƾ� �ȴ�. �̰��� Encoder�� Z���� �˻��غ��� �˼��ִ�.
' 1ȸ��:1800 �޽���� 75 x 1800 = 135000 �޽��� �ʿ��ϰ� �ȴ�.
' AxmMotSetMoveUnitPerPulse�� Unit = 1, Pulse = 1800 �־� ���۽�Ų��.
' �������� : rpm���� �����ϰ� �ȴٸ� �ӵ��� ���ӵ� �� rpm������ �ٲ�� �ȴ�.

' ���� ���� �޽� �� �����̴� �Ÿ��� �����Ѵ�.
Public Declare Function AxmMotSetMoveUnitPerPulse Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dUnit As Double, ByVal lPulse As Long) As Long
' ���� ���� �޽� �� �����̴� �Ÿ��� ��ȯ�Ѵ�.
Public Declare Function AxmMotGetMoveUnitPerPulse Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpUnit As Double, ByRef lpPulse As Long) As Long

' ���� �࿡ ���� ���� ����Ʈ ���� ����� �����Ѵ�.
' uMethod : 0 -1 ����
' AutoDetect = 0x0 : �ڵ� ������.
' RestPulse  = 0x1 : ���� ������."
Public Declare Function AxmMotSetDecelMode Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uMethod As Long) As Long
' ���� ���� ���� ���� ����Ʈ ���� ����� ��ȯ�Ѵ�
Public Declare Function AxmMotGetDecelMode Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upMethod As Long) As Long

' ���� �࿡ ���� ���� ��忡�� �ܷ� �޽��� �����Ѵ�.
' �����: ���� AxmMotSetRemainPulse�� 500 �޽��� ����
'           AxmMoveStartPos�� ��ġ 10000�� ��������쿡 9500�޽�����
'           ���� �޽� 500��  AxmMotSetMinVel�� ������ �ӵ��� �����ϸ鼭 ���� �ȴ�.
Public Declare Function AxmMotSetRemainPulse Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uData As Long) As Long
' ���� ���� ���� ���� ��忡�� �ܷ� �޽��� ��ȯ�Ѵ�.
Public Declare Function AxmMotGetRemainPulse Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef updata As Long) As Long

' ���� �࿡ ��ӵ� ���� �Լ������� �ְ� �ӵ��� �����Ѵ�.
' ���ǻ��� : �Է� �ִ� �ӵ� ���� PPS�� �ƴ϶� UNIT �̴�.
' ex) �ִ� ��� ���ļ�(PCI-N804/404 : 10 MPPS)
' ex) �ִ� ��� Unit/Sec(PCI-N804/404 : 10MPPS * Unit/Pulse)
Public Declare Function AxmMotSetMaxVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double) As Long
' ���� ���� ��ӵ� ���� �Լ������� �ְ� �ӵ��� ��ȯ�Ѵ�.
Public Declare Function AxmMotGetMaxVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpVel As Double) As Long

' ���� ���� �̵� �Ÿ� ��� ��带 �����Ѵ�.
' uAbsRelMode : POS_ABS_MODE '0' - ���� ��ǥ��
'               POS_REL_MODE '1' - ��� ��ǥ��
Public Declare Function AxmMotSetAbsRelMode Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uAbsRelMode As Long) As Long
' ���� ���� ������ �̵� �Ÿ� ��� ��带 ��ȯ�Ѵ�
Public Declare Function AxmMotGetAbsRelMode Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upAbsRelMode As Long) As Long

' ���� ���� ���� �ӵ� �������� ��带 �����Ѵ�.
' ProfileMode : SYM_TRAPEZOIDE_MODE    '0' - ��Ī Trapezode
'               ASYM_TRAPEZOIDE_MODE   '1' - ���Ī Trapezode
'               QUASI_S_CURVE_MODE     '2' - ��Ī Quasi-S Curve
'               SYM_S_CURVE_MODE       '3' - ��Ī S Curve
'               ASYM_S_CURVE_MODE      '4' - ���Ī S Curve
Public Declare Function AxmMotSetProfileMode Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uProfileMode As Long) As Long
' ���� ���� ������ ���� �ӵ� �������� ��带 ��ȯ�Ѵ�.
Public Declare Function AxmMotGetProfileMode Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upProfileMode As Long) As Long

' ���� ���� ���ӵ� ������ �����Ѵ�.
' AccelUnit : UNIT_SEC2   '0' - ������ ������ unit/sec2 ���
'             SEC         '1' - ������ ������ sec ���
Public Declare Function AxmMotSetAccelUnit Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uAccelUnit As Long) As Long
' ���� ���� ������ ���ӵ������� ��ȯ�Ѵ�.
Public Declare Function AxmMotGetAccelUnit Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upAccelUnit As Long) As Long

' ���ǻ���: �ּҼӵ��� UNIT/PULSE ���� �۰��� ��� �ּҴ����� UNIT/PULSE�� ���߾����⶧���� �ּ� �ӵ��� UNIT/PULSE �� �ȴ�.
' ���� �࿡ �ʱ� �ӵ��� �����Ѵ�.
Public Declare Function AxmMotSetMinVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dMinVel As Double) As Long
' ���� ���� �ʱ� �ӵ��� ��ȯ�Ѵ�.
Public Declare Function AxmMotGetMinVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpMinVel As Double) As Long

' ���� ���� ���� ��ũ���� �����Ѵ�.[%].
Public Declare Function AxmMotSetAccelJerk Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dAccelJerk As Double) As Long
' ���� ���� ������ ���� ��ũ���� ��ȯ�Ѵ�.
Public Declare Function AxmMotGetAccelJerk Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpAccelJerk As Double) As Long

' ���� ���� ���� ��ũ���� �����Ѵ�.[%].
Public Declare Function AxmMotSetDecelJerk Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dDecelJerk As Double) As Long
' ���� ���� ������ ���� ��ũ���� ��ȯ�Ѵ�.
Public Declare Function AxmMotGetDecelJerk Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpDecelJerk As Double) As Long

' ���� ���� �ӵ� Profile������ �켱����(�ӵ� Or ���ӵ�)�� �����Ѵ�.
' Priority : PRIORITY_VELOCITY   '0' - �ӵ� Profile������ ������ �ӵ����� �������� �����(�Ϲ���� �� Spinner�� ���).
'            PRIORITY_ACCELTIME  '1' - �ӵ� Profile������ ������ �����ӽð��� �������� �����(��� ��� ���).
Public Declare Function AxmMotSetProfilePriority Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uPriority As Long) As Long
' ���� ���� �ӵ� Profile������ �켱����(�ӵ� Or ���ӵ�)�� ��ȯ�Ѵ�.
Public Declare Function AxmMotGetProfilePriority Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upPriority As Long) As Long

'=========== ����� ��ȣ ���� �����Լ� ==============================================================================
' ���� ���� Z �� Level�� �����Ѵ�.
' uLevel : LOW(0), HIGH(1)
Public Declare Function AxmSignalSetZphaseLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uLevel As Long) As Long
' ���� ���� Z �� Level�� ��ȯ�Ѵ�.
Public Declare Function AxmSignalGetZphaseLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upLevel As Long) As Long

' ���� ���� Servo-On��ȣ�� ��� ������ �����Ѵ�.
' uLevel : LOW(0), HIGH(1)
Public Declare Function AxmSignalSetServoOnLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uLevel As Long) As Long
' ���� ���� Servo-On��ȣ�� ��� ���� ������ ��ȯ�Ѵ�.
Public Declare Function AxmSignalGetServoOnLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upLevel As Long) As Long

' ���� ���� Servo-Alarm Reset ��ȣ�� ��� ������ �����Ѵ�.
' uLevel : LOW(0), HIGH(1)
Public Declare Function AxmSignalSetServoAlarmResetLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uLevel As Long) As Long
' ���� ���� Servo-Alarm Reset ��ȣ�� ��� ������ ������ ��ȯ�Ѵ�.
Public Declare Function AxmSignalGetServoAlarmResetLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upLevel As Long) As Long

' ���� ���� Inpositon ��ȣ ��� ���� �� ��ȣ �Է� ������ �����Ѵ�
' uLevel :LOW(0), HIGH(1), UNUSED(2), USED(3)
Public Declare Function AxmSignalSetInpos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uUse As Long) As Long
' ���� ���� Inpositon ��ȣ ��� ���� �� ��ȣ �Է� ������ ��ȯ�Ѵ�.
Public Declare Function AxmSignalGetInpos Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upUse As Long) As Long
' ���� ���� Inpositon ��ȣ �Է� ���¸� ��ȯ�Ѵ�.
Public Declare Function AxmSignalReadInpos Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long

' ���� ���� �˶� ��ȣ �Է� �� ��� ������ ��� ���� �� ��ȣ �Է� ������ �����Ѵ�.
' uLevel :LOW(0), HIGH(1), UNUSED(2), USED(3)
Public Declare Function AxmSignalSetServoAlarm Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uUse As Long) As Long
' ���� ���� �˶� ��ȣ �Է� �� ��� ������ ��� ���� �� ��ȣ �Է� ������ ��ȯ�Ѵ�.
Public Declare Function AxmSignalGetServoAlarm Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upUse As Long) As Long
' ���� ���� �˶� ��ȣ�� �Է� ������ ��ȯ�Ѵ�.
Public Declare Function AxmSignalReadServoAlarm Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long

' ���� ���� end limit sensor�� ��� ���� �� ��ȣ�� �Է� ������ �����Ѵ�.
' end limit sensor ��ȣ �Է� �� �������� �Ǵ� �������� ���� ������ �����ϴ�.
' uStopMode: EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
' uLevel :LOW(0), HIGH(1), UNUSED(2), USED(3)
Public Declare Function AxmSignalSetLimit Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uStopMode As Long, ByVal uPositiveLevel As Long, ByVal uNegativeLevel As Long) As Long
' ���� ���� end limit sensor�� ��� ���� �� ��ȣ�� �Է� ����, ��ȣ �Է� �� ������带 ��ȯ�Ѵ�
Public Declare Function AxmSignalGetLimit Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStopMode As Long, ByRef upPositiveLevel As Long, ByRef upNegativeLevel As Long) As Long
' �������� end limit sensor�� �Է� ���¸� ��ȯ�Ѵ�.
Public Declare Function AxmSignalReadLimit Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upPositiveStatus As Long, ByRef upNegativeStatus As Long) As Long

' ���� ���� Software limit�� ��� ����, ����� ī��Ʈ, �׸��� ���� ����� �����Ѵ�
' uUse       : DISABLE(0), ENABLE(1)
' uStopMode  : EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
' uSelection : COMMAND(0), ACTUAL(1)
' ���ǻ���: �����˻��� �� �Լ��� �̿��Ͽ� ����Ʈ���� ������ �̸� �����ؼ� ������ �����˻��� �����˻��� ���߿� ���߾�������쿡��  Enable�ȴ�.
Public Declare Function AxmSignalSetSoftLimit Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uUse As Long, ByVal uStopMode As Long, ByVal uSelection As Long, ByVal dPositivePos As Double, ByVal dNegativePos As Double) As Long
' ���� ���� Software limit�� ��� ����, ����� ī��Ʈ, �׸��� ���� ����� ��ȯ�Ѵ�
Public Declare Function AxmSignalGetSoftLimit Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upUse As Long, ByRef upStopMode As Long, ByRef upSelection As Long, ByRef dpPositivePos As Double, ByRef dpNegativePos As Double) As Long
' ���� ���� Software limit�� ���� ���¸� ��ȯ�Ѵ�.
Public Declare Function AxmSignalReadSoftLimit Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upPositiveStatus As Long, ByRef upNegativeStatus As Long) As Long

' ��� ���� ��ȣ�� ���� ��� (������/��������) �Ǵ� ��� ������ �����Ѵ�.
' uStopMode  : EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
' uLevel : LOW(0), HIGH(1), UNUSED(2), USED(3)
Public Declare Function AxmSignalSetStop Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uStopMode As Long, ByVal uLevel As Long) As Long
' ��� ���� ��ȣ�� ���� ��� (������/��������) �Ǵ� ��� ������ ��ȯ�Ѵ�.
Public Declare Function AxmSignalGetStop Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStopMode As Long, ByRef upLevel As Long) As Long
' ��� ���� ��ȣ�� �Է� ���¸� ��ȯ�Ѵ�.
Public Declare Function AxmSignalReadStop Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long

' ���� ���� Servo-On ��ȣ�� ����Ѵ�.
' uOnOff : FALSE(0), TRUE(1) ( ���� 0��¿� �ش��)
Public Declare Function AxmSignalServoOn Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uOnOff As Long) As Long
' ���� ���� Servo-On ��ȣ�� ��� ���¸� ��ȯ�Ѵ�.
Public Declare Function AxmSignalIsServoOn Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upOnOff As Long) As Long

' ���� ���� Servo-Alarm Reset ��ȣ�� ����Ѵ�.
' uOnOff : FALSE(0), TRUE(1) ( ���� 1��¿� �ش��)
Public Declare Function AxmSignalServoAlarmReset Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uOnOff As Long) As Long

' ���� ��°��� �����Ѵ�.
' uValue : Hex Value 0x00
Public Declare Function AxmSignalWriteOutput Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uValue As Long) As Long
' ���� ��°��� ��ȯ�Ѵ�.
Public Declare Function AxmSignalReadOutput Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upValue As Long) As Long

' lBitNo : Bit Number(0 - 4)
' uOnOff : FALSE(0), TRUE(1)
' ���� ��°��� ��Ʈ���� �����Ѵ�.
Public Declare Function AxmSignalWriteOutputBit Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lBitNo As Long, ByVal uOnOff As Long) As Long
' ���� ��°��� ��Ʈ���� ��ȯ�Ѵ�.
Public Declare Function AxmSignalReadOutputBit Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lBitNo As Long, ByRef upOnOff As Long) As Long

' ���� �Է°��� Hex������ ��ȯ�Ѵ�.
Public Declare Function AxmSignalReadInput Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upValue As Long) As Long
' lBitNo : Bit Number(0 - 4)
' ���� �Է°��� ��Ʈ���� ��ȯ�Ѵ�.
Public Declare Function AxmSignalReadInputBit Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lBitNo As Long, ByRef upOn As Long) As Long

' �Է½�ȣ���� ������ ���Ͱ���� �����Ѵ�.
' uSignal: END_LIMIT(0), INP_ALARM(1), UIN_00_01(2), UIN_02_04(3)
' dBandwidthUsec: 0.2uSec~26666usec
Public Declare Function AxmSignalSetFilterBandwidth Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uSignal As Long, ByVal dBandwidthUsec As Double) As Long

'========== ��� ������ �� �����Ŀ� ���� Ȯ���ϴ� �Լ�===============================================================
' (��������)���� ���� �޽� ��� ���¸� ��ȯ�Ѵ�.
Public Declare Function AxmStatusReadInMotion Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long

' (�޽� ī��Ʈ ��)�������� ���� ���� ���� ���� �޽� ī���� ���� ��ȯ�Ѵ�.
Public Declare Function AxmStatusReadDrivePulseCount Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpPulse As Long) As Long

' ���� ���� DriveStatus(����� ����) �������͸� ��ȯ�Ѵ�
' ���ǻ��� : �� ��ǰ���� �ϵ�������� ��ȣ�� �ٸ��⶧���� �Ŵ��� �� AXHS.xxx ������ �����ؾ��Ѵ�.
Public Declare Function AxmStatusReadMotion Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long

' ���� ���� EndStatus(���� ����) �������͸� ��ȯ�Ѵ�.
' ���ǻ��� : �� ��ǰ���� �ϵ�������� ��ȣ�� �ٸ��⶧���� �Ŵ��� �� AXHS.xxx ������ �����ؾ��Ѵ�.
Public Declare Function AxmStatusReadStop Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long

' ���� ���� Mechanical Signal Data(���� ������� ��ȣ����) �� ��ȯ�Ѵ�.
' ���ǻ��� : �� ��ǰ���� �ϵ�������� ��ȣ�� �ٸ��⶧���� �Ŵ��� �� AXHS.xxx ������ �����ؾ��Ѵ�.
Public Declare Function AxmStatusReadMechanical Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long

' ���� ���� ���� ���� �ӵ��� �о�´�.
Public Declare Function AxmStatusReadVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpVel As Double) As Long

' ���� ���� Command Pos�� Actual Pos�� ���� ��ȯ�Ѵ�.
Public Declare Function AxmStatusReadPosError Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpError As Double) As Long

' ���� ����̺�� �̵��ϴ�(�̵���) �Ÿ��� Ȯ�� �Ѵ�
Public Declare Function AxmStatusReadDriveDistance Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpUnit As Double) As Long

' ���� ���� ��ġ ���� ��� ����� ���Ͽ� �����Ѵ�.
' uPosType  : Actual position �� Command position �� ǥ�� ���
'    POSITION_LIMIT '0' - �⺻ ����, ��ü ���� ������ ����
'    POSITION_BOUND '1' - ��ġ ���� �ֱ���, dNegativePos ~ dPositivePos ������ ����
' ���ǻ���(PCI-Nx04�ش�)
' - BOUNT������ ī��Ʈ ���� Max���� �ʰ� �� �� Min���̵Ǹ� �ݴ�� Min���� �ʰ� �� �� Max���� �ȴ�.
' - �ٽø��� ���� ��ġ���� ������ �� �ۿ��� ī��Ʈ �� ���� ���� Min, Max���� ������� �ʴ´�.
Public Declare Function AxmStatusSetPosType Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uPosType As Long, ByVal dPositivePos As Double, ByVal dNegativePos As Double) As Long
' ���� ���� ��ġ ���� ��� ����� ���Ͽ� ��ȯ�Ѵ�.
Public Declare Function AxmStatusGetPosType Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upPosType As Long, ByRef dpPositivePos As Double, ByRef dpNegativePos As Double) As Long
' ���� ���� ����ġ ���ڴ� ���� Offset ��ġ�� �����Ѵ�.[PCI-R1604-MLII ����]
Public Declare Function AxmStatusSetAbsOrgOffset Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dOrgOffsetPos As Double) As Long

' ���� ���� Actual ��ġ�� �����Ѵ�.
Public Declare Function AxmStatusSetActPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double) As Long
' ���� ���� Actual ��ġ�� ��ȯ�Ѵ�.
Public Declare Function AxmStatusGetActPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpPos As Double) As Long

' ���� ���� Command ��ġ�� �����Ѵ�.
Public Declare Function AxmStatusSetCmdPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double) As Long
' ���� ���� Command ��ġ�� ��ȯ�Ѵ�.
Public Declare Function AxmStatusGetCmdPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpPos As Double) As Long
' ���� ���� Command ��ġ�� Actual ��ġ�� dPos ������ ��ġ ��Ų��.
Public Declare Function AxmStatusSetPosMatch Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double) As Long

' Network ��ǰ �����Լ�.
' ������ ���� �����ѿ� AlarmCode�� �о������ ����ϴ� �Լ�.
Public Declare Function AxmStatusRequestServoAlarm Lib "AXL.dll" (ByVal lAxisNo As Long) As Long
' ������ ���� ������ AlarmCode�� �о���� �Լ�.
' upAlarmCode      : �ش� �������� Alarm Code����
' uReturnMode      : �Լ��� ��ȯ ���������� ����
' [0-Immediate]    : �Լ� ���� �� �ٷ� ��ȯ
' [1-Blocking]     : ���������� ���� �˶� �ڵ带 ���� �� ���� ��ȯ��������
' [2-Non Blocking] : ���������� ���� �˶� �ڵ带 ���� �� ���� ��ȯ���������� ���α׷� Blocking��������
Public Declare Function AxmStatusReadServoAlarm Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uReturnMode As Long, ByRef upAlarmCode As Long) As Long
' ������ �����ڵ忡 �ش��ϴ� Alarm String�� �޾ƿ��� �Լ�
Public Declare Function AxmStatusGetServoAlarmString Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uAlarmCode As Long, ByVal lAlarmStringSize As Long, ByRef szAlarmString As String) As Long

' ������ ���� �����ѿ� Alarm History�� �о������ ����ϴ� �Լ�
Public Declare Function AxmStatusRequestServoAlarmHistory Lib "AXL.dll" (ByVal lAxisNo As Long) As Long
' ������ ���� ������ Alarm History�� �о���� �Լ�.
' lpCount          : ���� Alarm History ����
' upAlarmCode      : Alarm History�� ��ȯ�� �迭
' uReturnMode      : �Լ��� ��ȯ ���������� ����
' [0-Immediate]    : �Լ� ���� �� �ٷ� ��ȯ
' [1-Blocking]     : ���������� ���� �˶� �ڵ带 ���� �� ���� ��ȯ��������
' [2-Non Blocking] : ���������� ���� �˶� �ڵ带 ���� �� ���� ��ȯ���������� ���α׷� Blocking��������
Public Declare Function AxmStatusReadServoAlarmHistory Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uReturnMode As Long, ByRef lpCount As Long, ByRef upAlarmCode As Long) As Long
' ������ ���� ������ Alarm History�� Clear�Ѵ�.
Public Declare Function AxmStatusClearServoAlarmHistory Lib "AXL.dll" (ByVal lAxisNo As Long) As Long

'======== Ȩ���� �Լ�================================================================================================
' ���� ���� Home ���� Level �� �����Ѵ�.
' uLevel : LOW(0), HIGH(1)
Public Declare Function AxmHomeSetSignalLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uLevel As Long) As Long
' ���� ���� Home ���� Level �� ��ȯ�Ѵ�.
Public Declare Function AxmHomeGetSignalLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upLevel As Long) As Long
' ���� Ȩ ��ȣ �Է»��¸� Ȯ���Ѵ�. Ȩ��ȣ�� ����ڰ� ���Ƿ� AxmHomeSetMethod �Լ��� �̿��Ͽ� �����Ҽ��ִ�.
' �Ϲ������� Ȩ��ȣ�� ���� �Է� 0�� ����ϰ������� AxmHomeSetMethod �̿��ؼ� �ٲٸ� + , - Limit�� ����Ҽ����ִ�.
' upStatus : OFF(0), ON(1)
Public Declare Function AxmHomeReadSignal Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long

' �ش� ���� �����˻��� �����ϱ� ���ؼ��� �ݵ�� ���� �˻����� �Ķ��Ÿ���� �����Ǿ� �־�� �˴ϴ�.
' ���� MotionPara���� ������ �̿��� �ʱ�ȭ�� ���������� ����ƴٸ� ������ ������ �ʿ����� �ʴ�.
' �����˻� ��� �������� �˻� �������, �������� ����� ��ȣ, �������� Active Level, ���ڴ� Z�� ���� ���� ���� ���� �Ѵ�.
' ���ǻ��� : ������ �߸� ������ -�������� �����ص�  +�������� �����Ҽ� ������, Ȩ�� ã�µ� �־� ������ �ɼ��ִ�.
' (�ڼ��� ������ AxmMotSaveParaAll ���� �κ� ����)
' Ȩ������ AxmSignalSetHomeLevel ����Ѵ�.
' HClrTim : HomeClear Time : ���� �˻� Encoder �� Set�ϱ� ���� ���ð�
' HmDir(Ȩ ����): DIR_CCW (0) -���� , DIR_CW(1) +����
' HOffset - ���������� �̵��Ÿ�.
' uZphas: 1�� �����˻� �Ϸ� �� ���ڴ� Z�� ���� ���� ����  0: ������ , 1: HmDir�� �ݴ� ����, 2: HmDir�� ���� ����
' HmSig : PosEndLimit(0) -> +Limit
'         NegEndLimit(1) -> -Limit
'         HomeSensor (4) -> ��������(���� �Է� 0)
Public Declare Function AxmHomeSetMethod Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lHmDir As Long, ByVal uHomeSignal As Long, ByVal uZphas As Long, ByVal dHomeClrTime As Double, ByVal dHomeOffset As Double) As Long
' �����Ǿ��ִ� Ȩ ���� �Ķ��Ÿ���� ��ȯ�Ѵ�.
Public Declare Function AxmHomeGetMethod Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpHmDir As Long, ByRef upHomeSignal As Long, ByRef upZphas As Long, ByRef dpHomeClrTime As Double, ByRef dpHomeOffset As Double) As Long

' �����˻� ����� �̼������� �ϴ� �Լ�(�⺻������ �������� �ʾƵ���).
' dHomeDogDistance[500 pulse]: ù��° Step���� HomeDog�� ������ �����ƴ��� Ȯ���ϱ����� Dog���̸� �Է�.(������ AxmMotSetMoveUnitPerPulse�Լ��� ������ ����)
' lLevelScanTime[100msec]: 2��° Step(���������� ���������� ����)���� Level���¸� Ȯ���� Scan�ð��� ����(������ msec[1~1000]).
' dwFineSearchUse[USE]: �⺻ �����˻��� 5 Step�� ����ϴµ� 3 Step�� ����ϵ��� �����Ҷ� 0���� ����.
' dwHomeClrUse[USE]: �����˻� �� ���ɰ��� Encoder���� 0���� �ڵ� �������θ� ����.
Public Declare Function AxmHomeSetFineAdjust Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dHomeDogLength As Double, ByVal lLevelScanTime As Long, ByVal uFineSearchUse As Long, ByVal uHomeClrUse As Long) As Long
' �����Ǿ��ִ� Ȩ ���� �̼����� �Ķ��Ÿ���� ��ȯ�Ѵ�.
Public Declare Function AxmHomeGetFineAdjust Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpHomeDogLength As Double, ByRef lpLevelScanTime As Long, ByRef upFineSearchUse As Long, ByRef upHomeClrUse As Long) As Long

' ������ ������ �����ϰ� �˻��ϱ� ���� ���� �ܰ��� �������� �����Ѵ�. �̶� �� ���ǿ� ��� �� �ӵ��� �����Ѵ�.
' �� �ӵ����� �������� ���� �����˻� �ð���, �����˻� ���е��� �����ȴ�.
' �� ���Ǻ� �ӵ����� ������ �ٲ㰡�鼭 �� ���� �����˻� �ӵ��� �����ϸ� �ȴ�.
' (�ڼ��� ������ AxmMotSaveParaAll ���� �κ� ����)
' �����˻��� ���� �ӵ��� �����ϴ� �Լ�
' [dVelFirst]- 1�������ӵ�   [dVelSecond]-�����ļӵ�   [dVelThird]- ������ �ӵ�  [dvelLast]- index�˻��� �����ϰ� �˻��ϱ�����.
' [dAccFirst]- 1���������ӵ� [dAccSecond]-�����İ��ӵ�
Public Declare Function AxmHomeSetVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVelFirst As Double, ByVal dVelSecond As Double, ByVal dVelThird As Double, ByVal dVelLast As Double, ByVal dAccFirst As Double, ByVal dAccSecond As Double) As Long
' �����Ǿ��ִ� �����˻��� ���� �ӵ��� ��ȯ�Ѵ�.
Public Declare Function AxmHomeGetVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpVelFirst As Double, ByRef dpVelSecond As Double, ByRef dpVelThird As Double, ByRef dpVelLast As Double, ByRef dpAccFirst As Double, ByRef dpAccSecond As Double) As Long

' �����˻��� �����Ѵ�.
' �����˻� �����Լ��� �����ϸ� ���̺귯�� ���ο��� �ش����� �����˻��� ���� �� �����尡 �ڵ� �����Ǿ� �����˻��� ���������� ������ �� �ڵ� ����ȴ�.
' ���ǻ��� : �������� �ݴ������ ����Ʈ ������ ���͵� ��������� ������ ACTIVE���������� �����Ѵ�.
'            ���� �˻��� ���۵Ǿ� ��������� ����Ʈ ������ ������ ����Ʈ ������ �����Ǿ��ٰ� �����ϰ� �����ܰ�� ����ȴ�.
Public Declare Function AxmHomeSetStart Lib "AXL.dll" (ByVal lAxisNo As Long) As Long
' �����˻� ����� ����ڰ� ���Ƿ� �����Ѵ�.
' �����˻� �Լ��� �̿��� ���������� �����˻��� ����ǰ��� �˻� ����� HOME_SUCCESS�� �����˴ϴ�.
' �� �Լ��� ����ڰ� �����˻��� ���������ʰ� ����� ���Ƿ� ������ �� �ִ�.
' uHomeResult ����
' HOME_SUCCESS              = 0x01,    ' Ȩ �Ϸ�
' HOME_SEARCHING            = 0x02,    ' Ȩ�˻���
' HOME_ERR_GNT_RANGE        = 0x10,    ' Ȩ �˻� ������ ��������
' HOME_ERR_USER_BREAK       = 0x11,    ' �ӵ� ������ ���Ƿ� ��������� ���������
' HOME_ERR_VELOCITY         = 0x12,    ' �ӵ� ���� �߸��������
' HOME_ERR_AMP_FAULT        = 0x13,    ' ������ �˶� �߻� ����
' HOME_ERR_NEG_LIMIT        = 0x14,    ' (-)���� ������ (+)����Ʈ ���� ���� ����
' HOME_ERR_POS_LIMIT        = 0x15,    ' (+)���� ������ (-)����Ʈ ���� ���� ����
' HOME_ERR_NOT_DETECT       = 0x16,    ' ������ ��ȣ �������� �� �� ��� ����
' HOME_ERR_UNKNOWN          = 0xFF,
Public Declare Function AxmHomeSetResult Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uHomeResult As Long) As Long
' �����˻� ����� ��ȯ�Ѵ�.
' �����˻� �Լ��� �˻� ����� Ȯ���Ѵ�. �����˻��� ���۵Ǹ� HOME_SEARCHING���� �����Ǹ� �����˻��� �����ϸ� ���п����� �����ȴ�. ���� ������ ������ �� �ٽ� �����˻��� �����ϸ� �ȴ�.
Public Declare Function AxmHomeGetResult Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upHomeResult As Long) As Long

' �����˻� ������� ��ȯ�Ѵ�.
' �����˻� ���۵Ǹ� �������� Ȯ���� �� �ִ�. �����˻��� �Ϸ�Ǹ� �������ο� ������� 100�� ��ȯ�ϰ� �ȴ�. �����˻� �������δ� GetHome Result�Լ��� �̿��� Ȯ���� �� �ִ�.
' upHomeMainStepNumber : Main Step �������̴�.
' ��Ʈ�� FALSE�� ���upHomeMainStepNumber : 0 �϶��� ������ �ุ ��������̰� Ȩ �������� upHomeStepNumber ǥ���Ѵ�.
' ��Ʈ�� TRUE�� ��� upHomeMainStepNumber : 0 �϶��� ������ Ȩ�� ��������̰� ������ Ȩ �������� upHomeStepNumber ǥ���Ѵ�.
' ��Ʈ�� TRUE�� ��� upHomeMainStepNumber : 10 �϶��� �����̺� Ȩ�� ��������̰� ������ Ȩ �������� upHomeStepNumber ǥ���Ѵ�.
' upHomeStepNumber     : ������ �࿡���� �������� ǥ���Ѵ�.
' ��Ʈ�� FALSE�� ���  : ������ �ุ �������� ǥ���Ѵ�.
' ��Ʈ�� TRUE�� ��� ��������, �����̺��� ������ �������� ǥ�õȴ�.
Public Declare Function AxmHomeGetRate Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upHomeMainStepNumber As Long, ByRef upHomeStepNumber As Long) As Long

'========= ��ġ �����Լ� ============================================================================================
' ���ǻ���: ��ġ�� �����Ұ�� �ݵ�� UNIT/PULSE�� ���߾ �����Ѵ�.
'           ��ġ�� UNIT/PULSE ���� �۰��� ��� �ּҴ����� UNIT/PULSE�� ���߾����⶧���� ����ġ���� ������ �ɼ�����.

' ���� �ӵ� ������ RPM(Revolution Per Minute)���� ���߰� �ʹٸ�.
' ex>   rpm ���:
' 4500 rpm ?
' unit/ pulse = 1 : 1�̸�      pulse/ sec �ʴ� �޽����� �Ǵµ�
' 4500 rpm�� ���߰� �ʹٸ�     4500 / 60 �� : 75ȸ��/ 1��
' ���Ͱ� 1ȸ���� �� �޽����� �˾ƾ� �ȴ�. �̰��� Encoder�� Z���� �˻��غ��� �˼��ִ�.
' 1ȸ��:1800 �޽���� 75 x 1800 = 135000 �޽��� �ʿ��ϰ� �ȴ�.
' AxmMotSetMoveUnitPerPulse�� Unit = 1, Pulse = 1800 �־� ���۽�Ų��.

' ������ �Ÿ���ŭ �Ǵ� ��ġ���� �̵��Ѵ�.
' ���� ���� ���� ��ǥ/ �����ǥ �� ������ ��ġ���� ������ �ӵ��� �������� ������ �Ѵ�.
' �ӵ� ���������� AxmMotSetProfileMode �Լ����� �����Ѵ�.
' �޽��� ��µǴ� �������� �Լ��� �����.
' AxmMotSetAccelUnit(lAxisNo, 1) �ϰ�� dAccel -> dAccelTime , dDecel -> dDecelTime ���� �ٲ��.
Public Declare Function AxmMoveStartPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

' ������ �Ÿ���ŭ �Ǵ� ��ġ���� �̵��Ѵ�.
' ���� ���� ���� ��ǥ/�����ǥ�� ������ ��ġ���� ������ �ӵ��� �������� ������ �Ѵ�.
' �ӵ� ���������� AxmMotSetProfileMode �Լ����� �����Ѵ�.
' �޽� ����� ����Ǵ� �������� �Լ��� �����
Public Declare Function AxmMovePos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

' ������ �ӵ��� �����Ѵ�.
' ���� �࿡ ���Ͽ� ������ �ӵ��� �������� ���������� �ӵ� ��� ������ �Ѵ�.
' �޽� ����� ���۵Ǵ� �������� �Լ��� �����.
' Vel���� ����̸� CW, �����̸� CCW �������� ����.
Public Declare Function AxmMoveVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

' ������ ���࿡ ���Ͽ� ������ �ӵ��� �������� ���������� �ӵ� ��� ������ �Ѵ�.
' �޽� ����� ���۵Ǵ� �������� �Լ��� �����.
' Vel���� ����̸� CW, �����̸� CCW �������� ����.
Public Declare Function AxmMoveStartMultiVel Lib "AXL.dll" (ByVal lArraySize As Long, ByRef lpAxesNo As Long, ByRef dpVel As Double, ByRef dpAccel As Double, ByRef dpDecel As Double) As Long

' ������ ���࿡ ���Ͽ� ������ �ӵ��� ������, SyncMode�� ���� ���������� �ӵ� ��� ������ �Ѵ�.
' �޽� ����� ���۵Ǵ� �������� �Լ��� �����.
' Vel���� ����̸� CW, �����̸� CCW �������� ����.
' dwSyncMode    : ����������� ������(0), �������� ��ɸ� ���(1), �˶��� ���ؼ��� ���� ������ ���(2)
Public Declare Function AxmMoveStartMultiVelEx Lib "AXL.dll" (ByVal lArraySize As Long, ByRef lpAxesNo As Long, ByRef dpVel As Double, ByRef dpAccel As Double, ByRef dpDecel As Double, ByVal dwSyncMode As Long) As Long

' ������ ���࿡ ���Ͽ� ������ �ӵ��� �������� ���������� �ӵ� ��� ������ �Ѵ�.
' �޽� ����� ���۵Ǵ� �������� �Լ��� ����� Master����(Distance�� ���� ū) dVel�ӵ��� �����̸�, ������ ����� Distance������ �����δ�.
' �ӵ��� �ش� Chip�� �� ��ȣ�� ���� ���� ���� �ӵ��� ����
Public Declare Function AxmMoveStartLineVel Lib "AXL.dll" (ByVal lArraySize As Long, ByRef lpAxesNo As Long, ByRef dpDis As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

' Ư�� Input ��ȣ�� Edge�� �����Ͽ� ������ �Ǵ� ���������ϴ� �Լ�.
' lDetect Signal : edge ������ �Է� ��ȣ ����.
' lDetectSignal  : PosEndLimit(0), NegEndLimit(1), HomeSensor(4), EncodZPhase(5), UniInput02(6), UniInput03(7)
' Signal Edge    : ������ �Է� ��ȣ�� edge ���� ���� (rising or falling edge).
'                  SIGNAL_DOWN_EDGE(0), SIGNAL_UP_EDGE(1)
' ��������       : Vel���� ����̸� CW, �����̸� CCW.
' SignalMethod   : ������ EMERGENCY_STOP(0), �������� SLOWDOWN_STOP(1)
' ���ǻ���: SignalMethod�� EMERGENCY_STOP(0)�� ����Ұ�� �������� ���õǸ� ������ �ӵ��� ���� �������ϰԵȴ�.
'           lDetectSignal�� PosEndLimit , NegEndLimit(0,1) �� ã����� ��ȣ�Ƿ��� Active ���¸� �����ϰԵȴ�.
Public Declare Function AxmMoveSignalSearch Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal lDetectSignal As Long, ByVal lSignalEdge As Long, ByVal lSignalMethod As Long) As Long

' ���� �࿡�� ������ ��ȣ�� �����ϰ� �� ��ġ�� �����ϱ� ���� �̵��ϴ� �Լ��̴�.
' ���ϴ� ��ȣ�� ��� ã�� �����̴� �Լ� ã�� ��� �� ��ġ�� ������ѳ��� AxmGetCapturePos����Ͽ� �װ��� �д´�.
' Signal Edge   : ������ �Է� ��ȣ�� edge ���� ���� (rising or falling edge).
'                 SIGNAL_DOWN_EDGE(0), SIGNAL_UP_EDGE(1)
' ��������      : Vel���� ����̸� CW, �����̸� CCW.
' SignalMethod  : ������ EMERGENCY_STOP(0), �������� SLOWDOWN_STOP(1)
' lDetect Signal: edge ������ �Է� ��ȣ ����.SIGNAL_DOWN_EDGE(0), SIGNAL_UP_EDGE(1)
' lDetectSignal : PosEndLimit(0), NegEndLimit(1), HomeSensor(4), EncodZPhase(5), UniInput02(6), UniInput03(7)
' lTarget       : COMMAND(0), ACTUAL(1)
' ���ǻ���: SignalMethod�� EMERGENCY_STOP(0)�� ����Ұ�� �������� ���õǸ� ������ �ӵ��� ���� �������ϰԵȴ�.
'           lDetectSignal�� PosEndLimit , NegEndLimit(0,1) �� ã����� ��ȣ�Ƿ��� Active ���¸� �����ϰԵȴ�.
Public Declare Function AxmMoveSignalCapture Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal lDetectSignal As Long, ByVal lSignalEdge As Long, ByVal lTarget As Long, ByVal lSignalMethod As Long) As Long
' 'AxmMoveSignalCapture' �Լ����� ����� ��ġ���� Ȯ���ϴ� �Լ��̴�.
' ���ǻ���: �Լ� ���� ����� "AXT_RT_SUCCESS"�϶� ����� ��ġ�� ��ȿ�ϸ�, �� �Լ��� �ѹ� �����ϸ� ���� ��ġ���� �ʱ�ȭ�ȴ�.
Public Declare Function AxmMoveGetCapturePos Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpCapPotition As Double) As Long

' ������ �Ÿ���ŭ �Ǵ� ��ġ���� �̵��ϴ� �Լ�.
' �Լ��� �����ϸ� �ش� Motion ������ ������ �� Motion �� �Ϸ�ɶ����� ��ٸ��� �ʰ� �ٷ� �Լ��� ����������."
Public Declare Function AxmMoveStartMultiPos Lib "AXL.dll" (ByVal lArraySize As Long, ByRef lpAxisNo As Long, ByRef dpPos As Double, ByRef dpVel As Double, ByRef dpAccel As Double, ByRef dpDecel As Double, ByVal uStopMode As Long) As Long

' ������ ������ �Ÿ���ŭ �Ǵ� ��ġ���� �̵��Ѵ�.
' ���� ����� ���� ��ǥ�� ������ ��ġ���� ������ �ӵ��� �������� ������ �Ѵ�.
Public Declare Function AxmMoveMultiPos Lib "AXL.dll" (ByVal lArraySize As Long, ByRef lpAxisNo As Long, ByRef dpPos As Double, ByRef dpVel As Double, ByRef dpAccel As Double, ByRef dpDecel As Double, ByVal uStopMode As Long) As Long

' ������ ��ũ �� �ӵ� ������ ���͸� �����Ѵ�.(PCIR-1604-MLII/SIIIH, PCIe-Rxx04-SIIIH  ���� �Լ�)
' dTroque        : �ִ� ��� ��ũ�� ���� %��.
' ��������       : dTroque���� ����̸� CW, �����̸� CCW.
' dVel           : �ִ� ���� ���� �ӵ��� ���� %��.
' dwAccFilterSel : LINEAR_ACCDCEL(0), EXPO_ACCELDCEL(1), SCURVE_ACCELDECEL(2)
' dwGainSel      : GAIN_1ST(0), GAIN_2ND(1)
' dwSpdLoopSel   : PI_LOOP(0), P_LOOP(1)
Public Declare Function AxmMoveStartTorque Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dTorque As Double, ByVal dVel As Double, ByVal dwAccFilterSel As Long, ByVal dwGainSel As Long, ByVal dwSpdLoopSel As Long) As Long

' ���� ���� ��ũ ������ ���� �Ѵ�.
' AxmMoveStartTorque�� �ݵ�� AxmMoveTorqueStop�� �����Ͽ��� �Ѵ�.
Public Declare Function AxmMoveTorqueStop Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwMethod As Long) As Long

' ������ �Ÿ���ŭ �Ǵ� ��ġ���� �̵��Ѵ�.
' ���� ���� ���� ��ǥ/�����ǥ�� ������ ��ġ���� ������ �ӵ�/�������� ������ �Ѵ�.
' �ӵ� ���������� ���Ī ��ٸ��÷� �����˴ϴ�.
' �����ӵ� ���� ������ ����� �����˴ϴ�.
' dAccel != 0.0 �̰� dDecel == 0.0 �� ��� ���� �ӵ����� ���� ���� ���� �ӵ����� ����.
' dAccel != 0.0 �̰� dDecel != 0.0 �� ��� ���� �ӵ����� ���� �ӵ����� ������ ��� ���� ����.
' dAccel == 0.0 �̰� dDecel != 0.0 �� ��� ���� �ӵ����� ���� �ӵ����� ����.

' ������ ������ �����Ͽ��� �մϴ�.
' dVel[1] == dVel[3]�� �ݵ�� �����Ͽ��� �Ѵ�.
' dVel[2]�� ���� ���� ������ �߻��� �� �ֵ��� dPosition�� ����� ū���̾�� �Ѵ�.
' Ex) dPosition = 10000;
' dVel[0] = 300., dAccel[0] = 200., dDecel[0] = 0.;    <== ����
' dVel[1] = 500., dAccel[1] = 100., dDecel[1] = 0.;    <== ����
' dVel[2] = 700., dAccel[2] = 200., dDecel[2] = 250.;  <== ����, ���, ����
' dVel[3] = 500., dAccel[3] = 0.,   dDecel[3] = 150.;  <== ����
' dVel[4] = 200., dAccel[4] = 0.,   dDecel[4] = 350.;  <== ����
' �޽� ����� ����Ǵ� �������� �Լ��� �����
Public Declare Function AxmMoveStartPosWithList Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPosition As Double, ByRef dpVel As Double, ByRef dpAccel As Double, ByRef dpDecel As Double, ByVal lListNum As Long) As Long

' ������ �Ÿ���ŭ �Ǵ� ��ġ���� ��� ���� ��ġ�� ������ �� �̵��� �����Ѵ�.
' lEvnetAxisNo    : ���� ���� �߻� ��
' dComparePosition: ���� ���� �߻� ���� ���� �߻� ��ġ.
' uPositionSource : ���� ���� �߻� ���� ���� �߻� ��ġ ���� ���� => COMMAND(0), ACTUAL(1)
' ���� �� ��Ҵ� AxmMoveStop, AxmMoveEStop, AxmMoveSStop�� ���
' �̵� ��� ���� ���� �߻� ���� 4�� ���� �ϳ��� �׷�(2V04�� ��� ���� ���)�� �����Ͽ��� �մϴ�.
Public Declare Function AxmMoveStartPosWithPosEvent Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lEventAxisNo As Long, ByVal dComparePosition As Double, ByVal uPositionSource As Long) As Long

' ���� ���� ������ ���ӵ��� ���� ���� �Ѵ�.
' dDecel : ���� �� ��������
Public Declare Function AxmMoveStop Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dDecel As Double) As Long
' ���� ���� ������ ���ӵ��� ���� ���� �Ѵ�.(PCI-Nx04 ����)
' ���� ������ ���¿� ������� ��� ���� ���� �Լ��̸� ���ѵ� ������ ���Ͽ� ��� �����ϴ�.
' -- ��� ���� ���� : AxmMoveStartPos, AxmMoveVel, AxmLineMoveEx2.
' dDecel : ���� �� ��������
' ���� : ���������� ���� ���� ���������� ũ�ų� ���ƾ� �Ѵ�.
' ���� : ���� ������ �ð����� �Ͽ��� ��� ���� ���� ���� �ð����� �۰ų� ���ƾ� �Ѵ�.
Public Declare Function AxmMoveStopEx Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dDecel As Double) As Long
' ���� ���� �� ���� �Ѵ�.
Public Declare Function AxmMoveEStop Lib "AXL.dll" (ByVal lAxisNo As Long) As Long
' ���� ���� ���� �����Ѵ�.
Public Declare Function AxmMoveSStop Lib "AXL.dll" (ByVal lAxisNo As Long) As Long

'========= �������̵� �Լ� ==========================================================================================
' ��ġ �������̵� �Ѵ�.
' ���� ���� ������ ����Ǳ� �� ������ ��� �޽� ���� �����Ѵ�.
' ���ǻ��� : �������̵��� ��ġ�� �������� ���� ������ ��ġ�� ���������� Relative ������ ��ġ������ �־��ش�.
'            ���������� ���������� ��� �������̵带 ����Ҽ������� �ݴ�������� �������̵��Ұ�쿡�� �������̵带 ����Ҽ�����.
Public Declare Function AxmOverridePos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dOverridePos As Double) As Long

' ���� ���� �ӵ��������̵� �ϱ����� �������̵��� �ְ�ӵ��� �����Ѵ�.
' ������ : �ӵ��������̵带 5���Ѵٸ� ���߿� �ְ� �ӵ��� �����ؾߵȴ�.
Public Declare Function AxmOverrideSetMaxVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dOverrideMaxVel As Double) As Long
' �ӵ� �������̵� �Ѵ�.
' ���� ���� ���� �߿� �ӵ��� ���� �����Ѵ�. (�ݵ�� ��� �߿� ���� �����Ѵ�.)
' ������: AxmOverrideVel �Լ��� ����ϱ�����. AxmOverrideMaxVel �ְ�� �����Ҽ��ִ� �ӵ��� �����س��´�.
' EX> �ӵ��������̵带 �ι��Ѵٸ�
' 1. �ΰ��߿� ���� �ӵ��� AxmOverrideMaxVel ���� �ְ� �ӵ��� ����.
' 2. AxmMoveStartPos ���� ���� ���� ���� ��(Move�Լ� ��� ����)�� �ӵ��� ù��° �ӵ��� AxmOverrideVel ���� �����Ѵ�.
' 3. ���� ���� ���� ��(Move�Լ� ��� ����)�� �ӵ��� �ι�° �ӵ��� AxmOverrideVel ���� �����Ѵ�.
Public Declare Function AxmOverrideVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dOverrideVel As Double) As Long
' ���ӵ�, �ӵ�, ���ӵ���  �������̵� �Ѵ�.
' ���� ���� ���� �߿� ���ӵ�, �ӵ�, ���ӵ��� ���� �����Ѵ�. (�ݵ�� ��� �߿� ���� �����Ѵ�.)
' ������: AxmOverrideAccelVelDecel �Լ��� ����ϱ�����. AxmOverrideMaxVel �ְ�� �����Ҽ��ִ� �ӵ��� �����س��´�.
' EX> �ӵ��������̵带 �ι��Ѵٸ�
' 1. �ΰ��߿� ���� �ӵ��� AxmOverrideMaxVel ���� �ְ� �ӵ��� ����.
' 2. AxmMoveStartPos ���� ���� ���� ���� ��(Move�Լ� ��� ����)�� ���ӵ�, �ӵ�, ���ӵ��� ù��° �ӵ��� AxmOverrideAccelVelDecel ���� �����Ѵ�.
' 3. ���� ���� ���� ��(Move�Լ� ��� ����)�� ���ӵ�, �ӵ�, ���ӵ��� �ι�° �ӵ��� AxmOverrideAccelVelDecel ���� �����Ѵ�.
Public Declare Function AxmOverrideAccelVelDecel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dOverrideVel As Double, ByVal dMaxAccel As Double, ByVal dMaxDecel As Double) As Long
' ��� �������� �ӵ� �������̵� �Ѵ�.
' ��� ��ġ ������ �������̵��� �ӵ��� �Է½��� ����ġ���� �ӵ��������̵� �Ǵ� �Լ�
' lTarget : COMMAND(0), ACTUAL(1)
' ������: AxmOverrideVelAtPos �Լ��� ����ϱ�����. AxmOverrideMaxVel �ְ�� �����Ҽ��ִ� �ӵ��� �����س��´�.
Public Declare Function AxmOverrideVelAtPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal dOverridePos As Double, ByVal dOverrideVel As Double, ByVal lTarget As Long) As Long
' ������ �����鿡�� ������ �ӵ��� �������̵� �Ѵ�.
' lArraySize     : �������̵� �� ��ġ�� ������ ����.
' *dpOverridePos : �������̵� �� ��ġ�� �迭(lArraySize���� ������ �������� ���ų� ũ�� �����ؾߵ�)
' *dpOverrideVel : �������̵� �� ��ġ���� ���� �� �ӵ� �迭(lArraySize���� ������ �������� ���ų� ũ�� �����ؾߵ�)
' lTarget        : COMMAND(0), ACTUAL(1)
' dwOverrideMode : �������̵� ���� ����� ������.
'                : OVERRIDE_POS_START(0) ������ ��ġ���� ������ �ӵ��� �������̵� ������
'                : OVERRIDE_POS_END(1) ������ ��ġ���� ������ �ӵ��� �ǵ��� �̸� �������̵� ������
Public Declare Function AxmOverrideVelAtMultiPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lArraySize As Long, ByRef dpOverridePos As Double, ByRef dpOverrideVel As Double, ByVal lTarget As Long, ByVal dwOverrideMode As Long) As Long

' ������ �����鿡�� ������ �ӵ�/�����ӵ��� �������̵� �Ѵ�.(MLII ����)
' lArraySize     : �������̵� �� ��ġ�� ������ ����(�ִ� 5).
' *dpOverridePos : �������̵� �� ��ġ�� �迭(lArraySize���� ������ �������� ���ų� ũ�� �����ؾߵ�)
' *dpOverrideVel : �������̵� �� ��ġ���� ���� �� �ӵ� �迭(lArraySize���� ������ �������� ���ų� ũ�� �����ؾߵ�)
' *dpOverrideAccelDecel : �������̵� �� ��ġ���� ���� �� �����ӵ� �迭(lArraySize���� ������ �������� ���ų� ũ�� �����ؾߵ�)
' lTarget        : COMMAND(0), ACTUAL(1) 
' dwOverrideMode : �������̵� ���� ����� ������.
'                : OVERRIDE_POS_START(0) ������ ��ġ���� ������ �ӵ��� �������̵� ������  
'                : OVERRIDE_POS_END(1) ������ ��ġ���� ������ �ӵ��� �ǵ��� �̸� �������̵� ������
Public Declare Function AxmOverrideVelAtMultiPos2 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lArraySize As Long, ByRef dpOverridePos As Double, ByRef dpOverrideVel As Double, ByRef dpOverrideAccelDecel As Double, ByVal lTarget As Long, ByVal dwOverrideMode As Long) As Long


'========= ������, �����̺�  ����� ���� �Լ� =====================================================================
' Electric Gear ��忡�� Master ��� Slave ����� ���� �����Ѵ�.
' dSlaveRatio : �������࿡ ���� �����̺��� ����( 0 : 0% , 0.5 : 50%, 1 : 100%)
Public Declare Function AxmLinkSetMode Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByVal lSlaveAxisNo As Long, ByVal dSlaveRatio As Double) As Long
' Electric Gear ��忡�� ������ Master ��� Slave ����� ���� ��ȯ�Ѵ�.
Public Declare Function AxmLinkGetMode Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByVal lSlaveAxisNo As Long, ByRef dpGearRatio As Double) As Long
' Master ��� Slave�ణ�� ���ڱ��� ���� ���� �Ѵ�.
Public Declare Function AxmLinkResetMode Lib "AXL.dll" (ByVal lMasterAxisNo As Long) As Long

'======== ��Ʈ�� ���� �Լ�===========================================================================================
' ��Ǹ���� �� ���� �ⱸ������ Link�Ǿ��ִ� ��Ʈ�� �����ý��� ��� �����Ѵ�.
' �� �Լ��� �̿��� Master���� ��Ʈ�� ����� �����ϸ� �ش� Slave���� Master��� ����Ǿ� �����˴ϴ�.
' ���� ��Ʈ�� ���� ���� Slave�࿡ ��������̳� ���� ��ɵ��� ������ ��� ���õ˴ϴ�.
' uSlHomeUse     : �������� Ȩ��� ��� ( 0 - 2)
'             (0 : �����̺��� Ȩ�� �����ϰ� ���������� Ȩ�� ã�´�.)
'             (1 : �������� , �����̺��� Ȩ�� ã�´�. �����̺� dSlOffset �� �����ؼ� ������.)
'             (2 : �������� , �����̺��� Ȩ�� ã�´�. �����̺� dSlOffset �� �����ؼ� ��������.)
' dSlOffset      : �����̺��� �ɼ°�
' dSlOffsetRange : �����̺��� �ɼ°� ������ ����
' ���ǻ���       : ��Ʈ�� ENABLE�� �����̺����� ����� AxmStatusReadMotion �Լ��� Ȯ���ϸ� True(Motion ���� ��)�� Ȯ�εǾ� �������̴�.
'                  �����̺��࿡ AxmStatusReadMotion�� Ȯ�������� InMotion �� False�̸� Gantry Enable�� �ȵȰ��̹Ƿ� �˶� Ȥ�� ����Ʈ ���� ���� Ȯ���Ѵ�.
Public Declare Function AxmGantrySetEnable Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByVal lSlaveAxisNo As Long, ByVal uSlHomeUse As Long, ByVal dSlOffset As Double, ByVal dSlOffsetRange As Double) As Long

' Slave���� Offset���� �˾Ƴ��¹��.
' A. ������, �����̺긦 �ΰ��� �������� ��Ų��.
' B. AxmGantrySetEnable�Լ����� uSlHomeUse = 2�� ������ AxmHomeSetStart�Լ��� �̿��ؼ� Ȩ�� ã�´�.
' C. Ȩ�� ã�� ���� ���������� Command���� �о�� ��������� �����̺����� Ʋ���� Offset���� �����ִ�.
' D. Offset���� �о AxmGantrySetEnable�Լ��� dSlOffset���ڿ� �־��ش�.
' E. dSlOffset���� �־��ٶ� �������࿡ ���� �����̺� �� ���̱⶧���� ��ȣ�� �ݴ�� -dSlOffset �־��ش�.
' F. dSIOffsetRange �� Slave Offset�� Range ������ ���ϴµ� Range�� �Ѱ踦 �����Ͽ� �Ѱ踦 ����� ������ �߻���ų�� ����Ѵ�.
' G. AxmGantrySetEnable�Լ��� Offset���� �־�������  AxmGantrySetEnable�Լ����� uSlHomeUse = 1�� ������ AxmHomeSetStart�Լ��� �̿��ؼ� Ȩ�� ã�´�.

' ��Ʈ�� ������ �־� ����ڰ� ������ �Ķ��Ÿ�� ��ȯ�Ѵ�.
Public Declare Function AxmGantryGetEnable Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByRef upSlHomeUse As Long, ByRef dpSlOffset As Double, ByRef dpSlORange As Double, ByRef upGatryOn As Long) As Long
' ��� ����� �� ���� �ⱸ������ Link�Ǿ��ִ� ��Ʈ�� �����ý��� ��� �����Ѵ�.
Public Declare Function AxmGantrySetDisable Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByVal lSlaveAxisNo As Long) As Long

' PCI-Rxx04-MLII ����.
' ��� ����� �� ���� �ⱸ������ Link�Ǿ��ִ� ��Ʈ�� �����ý��� ���� �� ���� ���� ����� �����Ѵ�.
' lMasterGain, lSlaveGain : �� �ణ ��ġ ������ ���� ���� �� �ݿ� ������ % ������ �Է��Ѵ�.
' lMasterGain, lSlaveGain : 0�� �Է��ϸ� �� �ణ ��ġ ���� ���� ����� ������� ����. �⺻�� : 0%
Public Declare Function AxmGantrySetCompensationGain Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByVal lMasterGain As Long, ByVal lSlaveGain As Long) As Long
' ��� ����� �� ���� �ⱸ������ Link�Ǿ��ִ� ��Ʈ�� �����ý��� ���� �� ���� ���� ����� ������ Ȯ���Ѵ�.
Public Declare Function AxmGantryGetCompensationGain Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByRef lpMasterGain As Long, ByRef lpSlaveGain As Long) As Long

'Master �� Slave �� ��ġ���� ������ ���� �ϰ� ��ġ�������� �̻��̸� Read �Լ��� Status�� TRUE�� ��ȯ �Ѵ�.
'PCI-R1604 / PCI-R3200-MLIII ���� �Լ�
'lMasterAxisNo : Gantry Master Axis No
'dErrorRange : ��ġ���� ���� ���� ��
'uUse : ��� ����
'     ( 0 : Disable)
'     ( 1 : Normal ���)
'     ( 2 : Flag Latch ���)
'     ( 3 : Flag Latch ��� + Error �߻��� SSTOP)
'     ( 4 : Flag Latch ��� + Error �߻��� ESTOP)
Public Declare Function AxmGantrySetErrorRange Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByVal dErrorRange As Double, ByVal uUse As Long) As Long
' Master �� Slave ���� ��ġ���� ���� �������� ��ȯ�Ѵ�.
Public Declare Function AxmGantryGetErrorRange Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByRef dpErrorRange As Double, ByRef upUse As Long) As Long
' Master �� Slave ���� ��ġ������ �� ����� ��ȯ �Ѵ�.
' dwpStatus : FALSE(0) -> Master �� Slave ������ ��ġ������ ������ ������ ���� ���� �۴�. (�������)
'             TRUE(1) -> Master �� Slave ������ ��ġ������ ������ ������ ���� ���� ũ��. (���������)
' Gantry Enable && Master/Slave Servo On ���¸� ���� �� ���� AXT_RT_SUCCESS�� Return �Ѵ�.
' Latch ����� ��� AxmGantryReadErrorRangeComparePos�� ȣ�� �ؾ� Latch Flag�� Reset �ȴ�.
Public Declare Function AxmGantryReadErrorRangeStatus Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByRef dwpStatus As Long) As Long
'Master �� Slave ���� ��ġ�������� ��ȯ �Ѵ�.
'Flag Latch ��� �϶� ���� Error�� �߻� �Ǳ� ������ ���� Error�� �߻� ���� ���� ��ġ�������� ���� �Ѵ�.
'dwpStatus �� 1�� ���� Read �ؾ� �Ѵ�. ��� ComparePos �� Read �ϸ� ���ϰ� ���� �ɷ� �Լ� ����ӵ��� �������� �ȴ�.
Public Declare Function AxmGantryReadErrorRangeComparePos Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByRef dpComparePos As Double) As Long

'====�Ϲ� �����Լ� ==================================================================================================
' ���ǻ���1: AxmContiSetAxisMap�Լ��� �̿��Ͽ� ������Ŀ� ������������� ������ �ϸ鼭 ����ؾߵȴ�.
'           ��ȣ������ ��쿡�� �ݵ�� ������������� ��迭�� �־�� ���� �����ϴ�.
    
' ���ǻ���2: ��ġ�� �����Ұ�� �ݵ�� ��������� �����̺� ���� UNIT/PULSE�� ���߾ �����Ѵ�.
'           ��ġ�� UNIT/PULSE ���� �۰� ������ ��� �ּҴ����� UNIT/PULSE�� ���߾����⶧���� ����ġ���� ������ �ɼ�����.

' ���ǻ���3: ��ȣ ������ �Ұ�� �ݵ�� ��Ĩ������ ������ �ɼ������Ƿ�
'            4�೻������ �����ؼ� ����ؾߵȴ�.

' ���ǻ���4: ���� ���� ����/�߿� ������ ���� ����(+- Limit��ȣ, ���� �˶�, ������� ��)�� �߻��ϸ�
'            ���� ���⿡ ������� ������ �������� �ʰų� ���� �ȴ�.

' ���� ���� �Ѵ�.
' �������� �������� �����Ͽ� ���� ���� ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
' AxmContiBeginNode, AxmContiEndNode�� ���̻��� ������ ��ǥ�迡 �������� �������� �����Ͽ� ���� ���� �����ϴ� Queue�� �����Լ����ȴ�.
' ���� �������� ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmContiStart�Լ��� ����ؼ� �����Ѵ�.
Public Declare Function AxmLineMove Lib "AXL.dll" (ByVal lCoord As Long, ByRef dpEndPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

' 2�� ���� ���� ���� �Ѵ�.(Software ���)
' �������� �������� �����Ͽ� ���� ���� ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
Public Declare Function AxmLineMoveEx2 Lib "AXL.dll" (ByVal lCoord As Long, ByRef dpEndPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

' 2�� ��ȣ���� �Ѵ�.
' ������, �������� �߽����� �����Ͽ� ��ȣ ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
' AxmContiBeginNode, AxmContiEndNode, �� ���̻��� ������ ��ǥ�迡 ������, �������� �߽����� �����Ͽ� �����ϴ� ��ȣ ���� Queue�� �����Լ����ȴ�.
' �������� ��ȣ ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmContiStart�Լ��� ����ؼ� �����Ѵ�.
' lAxisNo = ���� �迭 , dCenterPos = �߽��� X,Y �迭 , dEndPos = ������ X,Y �迭.
' uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
Public Declare Function AxmCircleCenterMove Lib "AXL.dll" (ByVal lCoord As Long, ByRef lAxisNo As Long, ByRef dCenterPos As Double, ByRef dEndPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long) As Long

' �߰���, �������� �����Ͽ� ��ȣ ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
' AxmContiBeginNode, AxmContiEndNode�� ���̻��� ������ ��ǥ�迡 �߰���, �������� �����Ͽ� �����ϴ� ��ȣ ���� Queue�� �����Լ����ȴ�.
' �������� ��ȣ ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmContiStart�Լ��� ����ؼ� �����Ѵ�.
' lAxisNo = ���� �迭 , dMidPos = �߰��� X,Y �迭 , dEndPos = ������ X,Y �迭, lArcCircle = ��ũ(0), ��(1)
Public Declare Function AxmCirclePointMove Lib "AXL.dll" (ByVal lCoord As Long, ByRef lAxisNo As Long, ByRef dMidPos As Double, ByRef dEndPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lArcCircle As Long) As Long

' ������, �������� �������� �����Ͽ� ��ȣ ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
' AxmContiBeginNode, AxmContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, �������� �������� �����Ͽ� ��ȣ ���� �����ϴ� Queue�� �����Լ����ȴ�.
' �������� ��ȣ ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmContiStart�Լ��� ����ؼ� �����Ѵ�.
' lAxisNo = ���� �迭 , dRadius = ������, dEndPos = ������ X,Y �迭 , uShortDistance = ������(0), ū��(1)
' uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
Public Declare Function AxmCircleRadiusMove Lib "AXL.dll" (ByVal lCoord As Long, ByRef lAxisNo As Long, ByVal dRadius As Double, ByRef dEndPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long, ByVal uShortDistance As Long) As Long

' ������, ȸ�������� �������� �����Ͽ� ��ȣ ���� �����ϴ� �Լ��̴�. ���� ���� �� �Լ��� �����.
' AxmContiBeginNode, AxmContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, ȸ�������� �������� �����Ͽ� ��ȣ ���� �����ϴ� Queue�� �����Լ����ȴ�.
' �������� ��ȣ ���� ���� ������ ���� ���� Queue�� �����Ͽ� AxmContiStart�Լ��� ����ؼ� �����Ѵ�.
' lAxisNo = ���� �迭 , dCenterPos = �߽��� X,Y �迭 , dAngle = ����.
' uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
Public Declare Function AxmCircleAngleMove Lib "AXL.dll" (ByVal lCoord As Long, ByRef lAxisNo As Long, ByRef dCenterPos As Double, ByVal dAngle As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long) As Long

'====���� ���� �Լ� =================================================================================================
' ������ ��ǥ�迡 ���Ӻ��� �� ������ �����Ѵ�.
' (����� ��ȣ�� 0 ���� ����))
' ������: ������Ҷ��� �ݵ�� ���� ���ȣ�� ���� ���ں��� ū���ڸ� �ִ´�.
'         ������ ���� �Լ��� ����Ͽ��� �� �������ȣ�� ���� ���ȣ�� ���� �� ���� lpAxesNo�� ���� ���ؽ��� �Է��Ͽ��� �Ѵ�.
'         ������ ���� �Լ��� ����Ͽ��� �� �������ȣ�� �ش��ϴ� ���� ���ȣ�� �ٸ� ���̶�� �Ѵ�.
'         ���� ���� �ٸ� Coordinate�� �ߺ� �������� ���ƾ� �Ѵ�.
Public Declare Function AxmContiSetAxisMap Lib "AXL.dll" (ByVal lCoord As Long, ByVal lSize As Long, ByRef lpRealAxesNo As Long) As Long
'������ ��ǥ�迡 ���Ӻ��� �� ������ ��ȯ�Ѵ�.
Public Declare Function AxmContiGetAxisMap Lib "AXL.dll" (ByVal lCoord As Long, ByRef lpSize As Long, ByRef lpRealAxesNo As Long) As Long

' ������ ��ǥ�迡 ���Ӻ��� �� ����/��� ��带 �����Ѵ�.
' (������ : �ݵ�� ����� �ϰ� ��밡��)
' ���� ���� �̵� �Ÿ� ��� ��带 �����Ѵ�.
' uAbsRelMode : POS_ABS_MODE '0' - ���� ��ǥ��
'               POS_REL_MODE '1' - ��� ��ǥ��
Public Declare Function AxmContiSetAbsRelMode Lib "AXL.dll" (ByVal lCoord As Long, ByVal uAbsRelMode As Long) As Long
' ������ ��ǥ�迡 ���Ӻ��� �� ����/��� ��带 ��ȯ�Ѵ�.
Public Declare Function AxmContiGetAbsRelMode Lib "AXL.dll" (ByVal lCoord As Long, ByRef upAbsRelMode As Long) As Long

' ������ ��ǥ�迡 ���� ������ ���� ���� Queue�� ��� �ִ��� Ȯ���ϴ� �Լ��̴�.
Public Declare Function AxmContiReadFree Lib "AXL.dll" (ByVal lCoord As Long, ByRef upQueueFree As Long) As Long
' ������ ��ǥ�迡 ���� ������ ���� ���� Queue�� ����Ǿ� �ִ� ���� ���� ������ Ȯ���ϴ� �Լ��̴�.
Public Declare Function AxmContiReadIndex Lib "AXL.dll" (ByVal lCoord As Long, ByRef lpQueueIndex As Long) As Long

' ������ ��ǥ�迡 ���� ���� ������ ���� ����� ���� Queue�� ��� �����ϴ� �Լ��̴�.
Public Declare Function AxmContiWriteClear Lib "AXL.dll" (ByVal lCoord As Long) As Long

' ������ ��ǥ�迡 ���Ӻ������� ������ �۾����� ����� �����Ѵ�. ���Լ��� ȣ������,
' AxmContiEndNode�Լ��� ȣ��Ǳ� ������ ����Ǵ� ��� ����۾��� ���� ����� �����ϴ� ���� �ƴ϶� ���Ӻ��� ������� ��� �Ǵ� ���̸�,
' AxmContiStart �Լ��� ȣ��� �� ��μ� ��ϵȸ���� ������ ����ȴ�.
Public Declare Function AxmContiBeginNode Lib "AXL.dll" (ByVal lCoord As Long) As Long
' ������ ��ǥ�迡�� ���Ӻ����� ������ �۾����� ����� �����Ѵ�.
Public Declare Function AxmContiEndNode Lib "AXL.dll" (ByVal lCoord As Long) As Long

' ���� ���� ���� �Ѵ�.
' dwProfileset(CONTI_NODE_VELOCITY(0) : ���� ���� ���, CONTI_NODE_MANUAL(1) : �������� ���� ���, CONTI_NODE_AUTO(2) : �ڵ� �������� ����, 3 : �ӵ����� ��� ���)
Public Declare Function AxmContiStart Lib "AXL.dll" (ByVal lCoord As Long, ByVal dwProfileset As Long, ByVal lAngle As Long) As Long
' ������ ��ǥ�迡 ���� ���� ���� ������ Ȯ���ϴ� �Լ��̴�.
Public Declare Function AxmContiIsMotion Lib "AXL.dll" (ByVal lCoord As Long, ByRef upInMotion As Long) As Long

' ������ ��ǥ�迡 ���� ���� ���� �� ���� �������� ���� ���� �ε��� ��ȣ�� Ȯ���ϴ� �Լ��̴�.
Public Declare Function AxmContiGetNodeNum Lib "AXL.dll" (ByVal lCoord As Long, ByRef lpNodeNum As Long) As Long
' ������ ��ǥ�迡 ������ ���� ���� ���� �� �ε��� ������ Ȯ���ϴ� �Լ��̴�.
Public Declare Function AxmContiGetTotalNodeNum Lib "AXL.dll" (ByVal lCoord As Long, ByRef lpNodeNum As Long) As Long

'====================Ʈ���� �Լ� ====================================================================================
' ���ǻ���: Ʈ���� ��ġ�� �����Ұ�� �ݵ�� UNIT/PULSE�� ���߾ �����Ѵ�.
'           ��ġ�� UNIT/PULSE ���� �۰��� ��� �ּҴ����� UNIT/PULSE�� ���߾����⶧���� ����ġ�� ����Ҽ�����.

' ���� �࿡ Ʈ���� ����� ��� ����, ��� ����, ��ġ �񱳱�, Ʈ���� ��ȣ ���� �ð� �� Ʈ���� ��� ��带 �����Ѵ�.
' Ʈ���� ��� ����� ���ؼ��� ����  AxmTriggerSetTimeLevel �� ����Ͽ� ���� ��� ������ ���� �Ͽ��� �Ѵ�.
' dTrigTime       : Ʈ���� ��� �ð�, 1usec - �ִ� 50msec ( 1 - 50000 ���� ����)
' upTriggerLevel  : Ʈ���� ��� ���� ����  => LOW(0), HIGH(1)
' uSelect         : ����� ���� ��ġ       => COMMAND(0), ACTUAL(1)
' uInterrupt      : ���ͷ�Ʈ ����          => DISABLE(0), ENABLE(1)

' ���� �࿡ Ʈ���� ��ȣ ���� �ð� �� Ʈ���� ��� ����, Ʈ���� ��¹���� �����Ѵ�.
Public Declare Function AxmTriggerSetTimeLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dTrigTime As Double, ByVal uTriggerLevel As Long, ByVal uSelect As Long, ByVal uInterrupt As Long) As Long
' ���� �࿡ Ʈ���� ��ȣ ���� �ð� �� Ʈ���� ��� ����, Ʈ���� ��¹���� ��ȯ�Ѵ�.
Public Declare Function AxmTriggerGetTimeLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpTrigTime As Double, ByRef upTriggerLevel As Long, ByRef upSelect As Long, ByRef upInterrupt As Long) As Long

' ���� ���� Ʈ���� ��� ����� �����Ѵ�.
' uMethod : PERIOD_MODE      0x0 : ���� ��ġ�� �������� dPos�� ��ġ �ֱ�� ����� �ֱ� Ʈ���� ���
'           ABS_POS_MODE     0x1 : Ʈ���� ���� ��ġ���� Ʈ���� �߻�, ���� ��ġ ���
' dPos : �ֱ� ���ý� : ��ġ������ġ���� ����ϱ⶧���� �� ��ġ
'        ���� ���ý� : ����� �� ��ġ, �� ��ġ�Ͱ����� ������ ����� ������.
' ���ǻ���: AxmTriggerSetAbsPeriod�� �ֱ���� �����Ұ�� ó�� ����ġ�� ���� �ȿ� �����Ƿ� Ʈ���� ����� �ѹ� �߻��Ѵ�.
Public Declare Function AxmTriggerSetAbsPeriod Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uMethod As Long, ByVal dPos As Double) As Long
' ���� �࿡ Ʈ���� ����� ��� ����, ��� ����, ��ġ �񱳱�, Ʈ���� ��ȣ ���� �ð� �� Ʈ���� ��� ��带 ��ȯ�Ѵ�.
Public Declare Function AxmTriggerGetAbsPeriod Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upMethod As Long, ByRef dpPos As Double) As Long

' ����ڰ� ������ ������ġ���� ������ġ���� ������������ Ʈ���Ÿ� ��� �Ѵ�.
Public Declare Function AxmTriggerSetBlock Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dStartPos As Double, ByVal dEndPos As Double, ByVal dPeriodPos As Double) As Long
' 'AxmTriggerSetBlock' �Լ��� Ʈ���� ������ ���� �д´�..
Public Declare Function AxmTriggerGetBlock Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpStartPos As Double, ByRef dpEndPos As Double, ByRef dpPeriodPos As Double) As Long

' ����ڰ� �� ���� Ʈ���� �޽��� ����Ѵ�.
Public Declare Function AxmTriggerOneShot Lib "AXL.dll" (ByVal lAxisNo As Long) As Long
' ����ڰ� �� ���� Ʈ���� �޽��� �����Ŀ� ����Ѵ�.
Public Declare Function AxmTriggerSetTimerOneshot Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lmSec As Long) As Long
' ������ġ Ʈ���� ���Ѵ� ������ġ ����Ѵ�.
Public Declare Function AxmTriggerOnlyAbs Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lTrigNum As Long, ByRef dpTrigPos As Double) As Long
' Ʈ���� ������ �����Ѵ�.
Public Declare Function AxmTriggerSetReset Lib "AXL.dll" (ByVal lAxisNo As Long) As Long

'======== CRC( �ܿ� �޽� Ŭ���� �Լ�)================================================================================
'Level   : LOW(0), HIGH(1), UNUSED(2), USED(3)
'uMethod : �ܿ��޽� ���� ��� ��ȣ �޽� �� 0 - 6���� ��������.
'          0 : 30 uSec , 1 : 100 uSec, 2: 500 uSec, 3:1 mSec, 4:10 mSec, 5:50 mSec, 6:100 mSec
'���� �࿡ CRC ��ȣ ��� ���� �� ��� ������ �����Ѵ�.
Public Declare Function AxmCrcSetMaskLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uLevel As Long, ByVal lMethod As Long) As Long
' ���� ���� CRC ��ȣ ��� ���� �� ��� ������ ��ȯ�Ѵ�.
Public Declare Function AxmCrcGetMaskLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upLevel As Long, ByVal lMethod As Long) As Long

'uOnOff  : CRC ��ȣ�� Program���� �߻� ����  (FALSE(0),TRUE(1))
' ���� �࿡ CRC ��ȣ�� ������ �߻� ��Ų��.
Public Declare Function AxmCrcSetOutput Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uOnOff As Long) As Long
' ���� ���� CRC ��ȣ�� ������ �߻� ���θ� ��ȯ�Ѵ�.
Public Declare Function AxmCrcGetOutput Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upOnOff As Long) As Long

'======MPG(Manual Pulse Generation) �Լ�=============================================================================
' lInputMethod  : 0-3 ���� ��������. 0:OnePhase, 1:��� ����, 2:TwoPhase2, 3:TwoPhase4
' lDriveMode    : 0�� ��������(0 :MPG ���Ӹ�� )
' MPGPos        : MPG �Է½�ȣ���� �̵��ϴ� �Ÿ�
' MPGdenominator: MPG(���� �޽� �߻� ��ġ �Է�)���� �� ������ ��
' dMPGnumerator : MPG(���� �޽� �߻� ��ġ �Է�)���� �� ���ϱ� ��
' dwNumerator   : �ִ�(1 ����    64) ���� ���� ����
' dwDenominator : �ִ�(1 ����  4096) ���� ���� ����
' dMPGdenominator = 4096, MPGnumerator=1 �� �ǹ��ϴ� ����
' MPG �ѹ����� 200�޽��� �״�� 1:1�� 1�޽��� ����� �ǹ��Ѵ�.
' ���� dMPGdenominator = 4096, MPGnumerator=2 �� �������� 1:2�� 2�޽��� ����� �������ٴ��ǹ��̴�.
' ���⿡ MPG PULSE = ((Numerator) * (Denominator)/ 4096 ) Ĩ���ο� ��³����� �����̴�.
' ���ǻ���     : AxmStatusReadInMotion �Լ� ���� ����� �����Ѵ�.  (AxmMPGReset �ϱ� ������ ���� ���¿����� ��� ���� �� ����.)

' ���� �࿡ MPG ����̺� ���� �޽� ���� ��忡�� ����� �̵� �Ÿ�, ������� �� ���� ���� ���� �����Ѵ�.
Public Declare Function AxmMPGSetEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lInputMethod As Long, ByVal lDriveMode As Long, ByVal dMPGPos As Double, ByVal dVel As Double, ByVal dAccel As Double) As Long
' ���� �࿡ MPG �Է¹��, ����̺� ���� ���, �̵� �Ÿ�, MPG �ӵ� ���� ��ȯ�Ѵ�.
Public Declare Function AxmMPGGetEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpInputMethod As Long, ByRef lpDriveMode As Long, ByRef dpMPGPos As Double, ByRef dpVel As Double, ByRef dpAccel As Double) As Long

' PCI-Nx04 �Լ� ����.
' ���� �࿡ MPG ����̺� ���� ��忡�� ���޽��� �̵��� �޽� ������ �����Ѵ�.
Public Declare Function AxmMPGSetRatio Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uMPGnumerator As Long, ByVal uMPGdenominator As Long) As Long
' ���� �࿡ MPG ����̺� ���� ��忡�� ���޽��� �̵��� �޽� ������ ��ȯ�Ѵ�.
Public Declare Function AxmMPGGetRatio Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upMPGnumerator As Long, ByRef upMPGdenominator As Long) As Long
' ���� �࿡ MPG ����̺� ������ �����Ѵ�.
Public Declare Function AxmMPGReset Lib "AXL.dll" (ByVal lAxisNo As Long) As Long

'======= �︮�� �̵� ================================================================================================
' ���ǻ��� : Helix�� ���Ӻ��� ���� Spline, ���������� ��ȣ������ ���� ����Ҽ�����.

' ������ ��ǥ�迡 ������, �������� �߽����� �����Ͽ� �︮�� ���� �����ϴ� �Լ��̴�.
' AxmContiBeginNode, AxmContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, �������� �߽����� �����Ͽ� �︮�� ���Ӻ��� �����ϴ� �Լ��̴�.
' ��ȣ ���� ���� ������ ���� ���� Queue�� �����ϴ� �Լ��̴�. AxmContiStart�Լ��� ����ؼ� �����Ѵ�. (���Ӻ��� �Լ��� ���� �̿��Ѵ�)
' dCenterPos = �߽��� X,Y  , dEndPos = ������ X,Y .
' uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
Public Declare Function AxmHelixCenterMove Lib "AXL.dll" (ByVal lCoord As Long, ByVal dCenterXPos As Double, ByVal dCenterYPos As Double, ByVal dEndXPos As Double, ByVal dEndYPos As Double, ByVal dZPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long) As Long

' ������ ��ǥ�迡 ������, �������� �������� �����Ͽ� �︮�� ���� �����ϴ� �Լ��̴�.
' AxmContiBeginNode, AxmContiEndNode�� ���̻��� ������ ��ǥ�迡 �߰���, �������� �����Ͽ� �︮�ÿ��� ���� �����ϴ� �Լ��̴�.
' ��ȣ ���� ���� ������ ���� ���� Queue�� �����ϴ� �Լ��̴�. AxmContiStart�Լ��� ����ؼ� �����Ѵ�. (���Ӻ��� �Լ��� ���� �̿��Ѵ�.)
' dMidPos = �߰��� X,Y  , dEndPos = ������ X,Y
Public Declare Function AxmHelixPointMove Lib "AXL.dll" (ByVal lCoord As Long, ByVal dMidXPos As Double, ByVal dMidYPos As Double, ByVal dEndXPos As Double, ByVal dEndYPos As Double, ByVal dZPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

' ������ ��ǥ�迡 ������, �������� �������� �����Ͽ� �︮�� ���� �����ϴ� �Լ��̴�.
' AxmContiBeginNode, AxmContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, �������� �������� �����Ͽ� �︮�ÿ��� ���� �����ϴ� �Լ��̴�.
' ��ȣ ���� ���� ������ ���� ���� Queue�� �����ϴ� �Լ��̴�. AxmContiStart�Լ��� ����ؼ� �����Ѵ�. (���Ӻ��� �Լ��� ���� �̿��Ѵ�.)
' dRadius = ������, dEndPos = ������ X,Y  , uShortDistance = ������(0), ū��(1)
' uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
Public Declare Function AxmHelixRadiusMove Lib "AXL.dll" (ByVal lCoord As Long, ByVal dRadius As Double, ByVal dEndXPos As Double, ByVal dEndYPos As Double, ByVal dZPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long, ByVal uShortDistance As Long) As Long

' ������ ��ǥ�迡 ������, ȸ�������� �������� �����Ͽ� �︮�� ���� �����ϴ� �Լ��̴�
' AxmContiBeginNode, AxmContiEndNode�� ���̻��� ������ ��ǥ�迡 ������, ȸ�������� �������� �����Ͽ� �︮�ÿ��� ���� �����ϴ� �Լ��̴�.
' ��ȣ ���� ���� ������ ���� ���� Queue�� �����ϴ� �Լ��̴�. AxmContiStart�Լ��� ����ؼ� �����Ѵ�. (���Ӻ��� �Լ��� ���� �̿��Ѵ�.)
' dCenterPos = �߽��� X,Y  , dAngle = ����.
' uCWDir   DIR_CCW(0): �ݽð����, DIR_CW(1) �ð����
Public Declare Function AxmHelixAngleMove Lib "AXL.dll" (ByVal lCoord As Long, ByVal dCenterXPos As Double, ByVal dCenterYPos As Double, ByVal dAngle As Double, ByVal dZPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long) As Long

'======== ���ö��� �̵� =============================================================================================
' ���ǻ��� : Spline�� ���Ӻ��� ���� Helix , ���������� ��ȣ������ ���� ����Ҽ�����.

' AxmContiBeginNode, AxmContiEndNode�� ���̻�����.
' ���ö��� ���� ���� �����ϴ� �Լ��̴�. ��ȣ ���� ���� ������ ���� ���� Queue�� �����ϴ� �Լ��̴�.
' AxmContiStart�Լ��� ����ؼ� �����Ѵ�. (���Ӻ��� �Լ��� ���� �̿��Ѵ�.)
' lPosSize : �ּ� 3�� �̻�.
' 2������ ���� dPoZ���� 0���� �־��ָ� ��.
' 3������ ���� ������� 3���� dPosZ ���� �־��ش�.
Public Declare Function AxmSplineWrite Lib "AXL.dll" (ByVal lCoord As Long, ByVal lPosSize As Long, ByRef dpPosX As Double, ByRef dpPosY As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal dPosZ As Double, ByVal lPointFactor As Long) As Long

'======== PCI-R1604-MLII/SIIIH, PCIe-Rxx04-SIIIH ���� �Լ� ========================================================================================
' ��ġ ���� ���̺� ��ɿ� �ʿ��� ������ �����Ѵ�.
Public Declare Function AxmCompensationSet Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lNumEntry As Long, ByVal dStartPos As Double, ByRef dpPosition As Double, ByRef dpCorrection As Double, ByVal lRollOver As Long) As Long
' ��ġ ���� ���̺� ��� ���� ������ ��ȯ�Ѵ�.
Public Declare Function AxmCompensationGet Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpNumEntry As Long, ByRef dpStartPos As Double, ByRef dpPosition As Double, ByRef dpCorrection As Double, ByRef lpRollOver As Long) As Long

' ��ġ ���� ���̺� ����� ������θ� �����Ѵ�.
Public Declare Function AxmCompensationEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lEnable As Long) As Long
' ��ġ ���� ���̺� ����� ��������� ���� ���� ���¸� ��ȯ�Ѵ�.
Public Declare Function AxmCompensationIsEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpEnable As Long) As Long
' ���� ���� ��ġ������ �������� ��ȯ�Ѵ�.
Public Declare Function AxmCompensationGetCorrection Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpCorrection As Double) As Long

' Backlash�� ���õ� �������ϴ� �Լ�
' > lBacklashDir: Backlash ������ ������ ���� ������ ���� (�����˻� ����� �����ϰ� ������)  
'   - [0] -> Command Position���� (+)�������� ������ �� ������ backlash�� ������ 
'   - [1] -> Command Position���� (-)�������� ������ �� ������ backlash�� ������
'   - Ex1) lBacklashDir�� 0, backlash�� 0.01�� �� 0.0 -> 100.0���� ��ġ�̵� �� �� ���� �̵��ϴ� ��ġ�� 100.01�̵�
'   - Ex2) lBacklashDir�� 0, backlash�� 0.01�� �� 0.0 -> -100.0���� ��ġ�̵� �� �� ���� �̵��ϴ� ��ġ�� -100.0�̵�
'   �� NOTANDUM 
'   - ��Ȯ�� Backlash������ ���ؼ��� �����˻��� �������� Backlash�� ��ŭ (+)Or(-)�������� �̵� �� �� ������ �Ϸ��ϰ�
'     Backlash������ ����Ѵ�. �� �� Backlash�� ��ŭ (+)������ �ߴٸ� backlash_dir�� [1](-)��, (-)������ �ߴٸ�
'     backlash_dir�� [0](+)�� �����ϸ� �ȴ�.
' > dBacklash: �ⱸ�ο��� ���� ����� �ݴ�������� ������ȯ�� �߻��Ǵ� Backlash���� ������
' { RETURN VALUE } 
'   - [0] -> Backlash ������ �������� ��
Public Declare Function AxmCompensationSetBacklash Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lBacklashDir As Long, ByVal dBacklash As Double) As Long

' Backlash�� ���õ� ���� ������ ��ȯ�Ѵ�.
Public Declare Function AxmCompensationGetBacklash Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpBacklashDir As Long, ByRef dpBacklash As Double) As Long
' Backlash��������� ����/Ȯ���ϴ� �Լ�
' > dwEnable: Backlash���� ��������� ����
'   - [0]DISABLE -> Backlash������ ������    
'   - [1]ENABLE  -> Backlash������ �����
' { RETURN VALUE } 
'   - [0] -> Backlash ������ȯ�� �������� ��
Public Declare Function AxmCompensationEnableBacklash Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwEnable As Long) As Long
Public Declare Function AxmCompensationIsEnableBacklash Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpEnable As Long) As Long

' ECAM ��ɿ� �ʿ��� ������ �����Ѵ�.
Public Declare Function AxmEcamSet Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lMasterAxisNo As Long, ByVal lNumEntry As Long, ByVal dMasterStartPos As Double, ByRef dpMasterPos As Double, ByRef dpSlavePos As Double) As Long
' ECAM ��ɿ� �ʿ��� ������ CMD/ACT Source�� �Բ� �����Ѵ�. (PCIe-Rxx04-SIIIH ���� �Լ�)
Public Declare Function AxmEcamSetWithSource Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lMasterAxisNo As Long, ByVal lNumEntry As Long, ByVal dMasterStartPos As Double, ByRef dpMasterPos As Double, ByRef dpSlavePos As Double, ByRef dwSource As Long) As Long
' ECAM ��� ���� ������ ��ȯ�Ѵ�.
Public Declare Function AxmEcamGet Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpMasterAxisNo As Long, ByRef lpNumEntry As Long, ByRef dpMasterStartPos As Double, ByRef dpMasterPos As Double, ByRef dpSlavePos As Double) As Long
' ECAM ��� ���� ������ CMD/ACT Source�� �Բ� ��ȯ�Ѵ�. (PCIe-Rxx04-SIIIH ���� �Լ�)
Public Declare Function AxmEcamGetWithSource Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpMasterAxisNo As Long, ByRef lpNumEntry As Long, ByRef dpMasterStartPos As Double, ByRef dpMasterPos As Double, ByRef dpSlavePos As Double, ByRef dwpSource As Long) As Long


Public Declare Function AxmEcamEnableBySlave Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lEnable As Long) As Long
' ECAM ����� ��� ������ ������ Master �࿡ ����� ��� Slave �࿡ ���Ͽ� �����Ѵ�.
Public Declare Function AxmEcamEnableByMaster Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lEnable As Long) As Long
' ECAM ����� ��� ������ ���� ���� ���¸� ��ȯ�Ѵ�.
Public Declare Function AxmEcamIsSlaveEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpEnable As Long) As Long

'======== Servo Status Monitor ======================================================================================
' ���� ���� ���� ó�� ��ɿ� ���� �����Ѵ�.(MLII : Sigma-5, SIIIH : MR_J4_xxB ����)
' uSelMon(0~3) : ���� ���� ����.
'          [0] : Torque
'          [1] : Velocity of motor
'          [2] : Accel. of motor
'          [3] : Decel. of motor
'          [4] : Position error between Cmd. position and Act. position.
' uActionValue : �̻� ���� ���� ���� �� ����. �� ������ ���� ���� ���� �ǹ̰� ����.
'          [0] : uSelMon���� ������ ���� ������ ���Ͽ� ���� ó�� ���� ����.
'         [>0] : uSelMon���� ������ ���� ������ ���Ͽ� ���� ó�� ��� ����.
' uAction(0~3) : uActionValue �̻����� ���� ������ Ȯ�εǾ����� ����ó�� ��� ����.
'          [0] : Warning(setting flag only)
'          [1] : Warning(setting flag) + Slow-down stop
'          [2] : Warning(setting flag) + Emergency stop
'          [3] : Warning(setting flag) + Emergency stop + Servo-Off
' �� ����: 5���� SelMon ������ ���� ���� ����ó�� ������ �����ϸ�, ����� ����ó���� ���������� ���
'          �ݵ�� �ش� SelMon ������ ActionValue���� 0���� ������ ���ñ���� Disable �ص�.
Public Declare Function AxmStatusSetServoMonitor Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uSelMon As Long, ByVal dActionValue As Double, ByVal uAction As Long) As Long
' ���� ���� ���� ó�� ��ɿ� ���� ���� ���¸� ��ȯ�Ѵ�.(MLII : Sigma-5, SIIIH : MR_J4_xxB ����)
Public Declare Function AxmStatusGetServoMonitor Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uSelMon As Long, ByRef dpActionValue As Double, ByRef upAction As Long) As Long
' ���� ���� ���� ó�� ��ɿ� ���� ��� ������ �����Ѵ�.(MLII : Sigma-5, SIIIH : MR_J4_xxB ����)
Public Declare Function AxmStatusSetServoMonitorEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uEnable As Long) As Long
' ���� ���� ���� ó�� ��ɿ� ���� ��� ������ ��ȯ�Ѵ�.(MLII : Sigma-5, SIIIH : MR_J4_xxB ����)
Public Declare Function AxmStatusGetServoMonitorEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upEnable As Long) As Long

' ���� ���� ���� ó�� ��� ���� ��� �÷��� ���� ��ȯ�Ѵ�. �Լ� ���� �� �ڵ� �ʱ�ȭ.(MLII : Sigma-5, SIIIH : MR_J4_xxB ����)
Public Declare Function AxmStatusReadServoMonitorFlag Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uSelMon As Long, ByRef upMonitorFlag As Long, ByRef dpMonitorValue As Double) As Long
' ���� ���� ���� ó�� ����� ���� ���� ������ ��ȯ�Ѵ�.(MLII : Sigma-5, SIIIH : MR_J4_xxB ����)
Public Declare Function AxmStatusReadServoMonitorValue Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uSelMon As Long, ByRef dpMonitorValue As Double) As Long

' ���� ���� �������� ���� �� �ֵ��� ���� �մϴ�.(MLII : Sigma-5, SIIIH : MR_J4_xxB ����)
' dwSelMon = 0 : Accumulated load ratio
' dwSelMon = 1 : Regenerative load ratio
' dwSelMon = 2 : Reference Torque load ratio
Public Declare Function AxmStatusSetReadServoLoadRatio Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwSelMon As Long) As Long
' ���� ���� �������� ��ȯ�Ѵ�.(MLII : Sigma-5, SIIIH : MR_J4_xxB ����)
Public Declare Function AxmStatusReadServoLoadRatio Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpMonitorValue As Double) As Long

'======== PCI-R1604-RTEX ���� �Լ�==================================================================================
' RTEX A4Nx ���� Scale Coefficient�� �����Ѵ�.(RTEX, A4Nx ����)
Public Declare Function AxmMotSetScaleCoeff Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lScaleCoeff As Long) As Long
' RTEX A4Nx ���� Scale Coefficient �� Ȯ���Ѵ�.(RTEX, A4Nx ����)
Public Declare Function AxmMotGetScaleCoeff Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpScaleCoeff As Long) As Long
' Ư�� Input ��ȣ�� Edge�� �����Ͽ� ������ �Ǵ� ���������ϴ� �Լ�.
' lDetect Signal : edge ������ �Է� ��ȣ ����.
' lDetectSignal  : PosEndLimit(0), NegEndLimit(1), HomeSensor(4)
' Signal Edge    : ������ �Է� ��ȣ�� edge ���� ���� (rising or falling edge).
'                  SIGNAL_DOWN_EDGE(0), SIGNAL_UP_EDGE(1)
' ��������       : Vel���� ����̸� CW, �����̸� CCW.
' SignalMethod   : ������ EMERGENCY_STOP(0), �������� SLOWDOWN_STOP(1)
' ���ǻ���: SignalMethod�� EMERGENCY_STOP(0)�� ����Ұ�� �������� ���õǸ� ������ �ӵ��� ���� �������ϰԵȴ�.
'           PCI-Nx04�� ����� ��� lDetectSignal�� PosEndLimit , NegEndLimit(0,1) �� ã����� ��ȣ�Ƿ��� Active ���¸� �����ϰԵȴ�.
Public Declare Function AxmMoveSignalSearchEx Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal lDetectSignal As Long, ByVal lSignalEdge As Long, ByVal lSignalMethod As Long) As Long
'--------------------------------------------------------------------------------------------------------------------
'======== PCI-R1604-MLII/SIIIH, PCIe-Rxx04-SIIIH ���� �Լ� ==================================================================================
' ������ ���� ��ġ�� �̵��Ѵ�.
' �ӵ� ���������� ����� �������� �����Ѵ�.
'  �޽��� ��µǴ� �������� �Լ��� �����.
' �׻� ��ġ �� �ӵ�, �����ӵ��� ���� �����ϸ�, �ݴ���� ��ġ ���� ����� �����Ѵ�.
Public Declare Function AxmMoveToAbsPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long
' ���� ���� ���� ���� �ӵ��� �о�´�.
Public Declare Function AxmStatusReadVelEx Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpVel As Double) As Long

' ========  PCI-R1604-SIIIH, PCIe-Rxx04-SIIIH ���� �Լ� ==================================================================================
'  ���� ���� ���� ���� �����Ѵ�. ���� �� �� �ֹ߼� �޸𸮿� ���˴ϴ�.
'  �ʱ� ��(lNumerator : 4194304(2^22), lDenominator : 10000)
'  MR-J4-B�� ���� ���� ������ �� ������, ���� ����⿡�� �Ʒ��� �Լ��� ����Ͽ� �����Ͽ��� �մϴ�.
'  ���� �޽� �Է� ��� ���� ����̹�(MR-J4-A)�� �Ķ���� No.PA06, No.PA07�� �ش�.
'  ex1) 1 um�� ���� ������ ����. ���ӱ� ���� : 1/1. Rotary motor�� ������ Linear stage.
'  Encoder resulotion = 2^22
'  Ball screw pitch : 6 mm
'  ==> lNumerator = 2^22, lDenominator = 6000(6/0.001)
'  AxmMotSetMoveUnitPerPulse���� Unit/Pulse = 1/1�� �����Ͽ��ٸ�, ��� �Լ��� ��ġ ���� : um, �ӵ� ���� : um/sec, �����ӵ� �ܵ� : um/sec^2�� �ȴ�.
'  AxmMotSetMoveUnitPerPulse���� Unit/Pulse = 1/1000�� �����Ͽ��ٸ�, ��� �Լ��� ��ġ ���� : mm, �ӵ� ���� : mm/sec, �����ӵ� �ܵ� : mm/sec^2�� �ȴ�.
'  ex2) 0.01�� ȸ���� ���� ������ ����. ���ӱ� ���� : 1/1. Rotary motor�� ������ ȸ��ü ������.
'  Encoder resulotion = 2^22
'  1 ȸ�� : 360
'  ==> lNumerator = 2^22, lDenominator = 36000(360 / 0.01)
'  AxmMotSetMoveUnitPerPulse���� Unit/Pulse = 1/1�� �����Ͽ��ٸ�, ��� �Լ��� ��ġ ���� : 0.01��, �ӵ� ���� : 0.01��/sec, �����ӵ� �ܵ� : 0.01��/sec^2�� �ȴ�.
'  AxmMotSetMoveUnitPerPulse���� Unit/Pulse = 1/100�� �����Ͽ��ٸ�, ��� �Լ��� ��ġ ���� : 1��, �ӵ� ���� : 1��/sec, �����ӵ� �ܵ� : 1��/sec^2�� �ȴ�.
Public Declare Function AxmMotSetElectricGearRatio Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lNumerator As Long, ByVal lDenominator As Long) As Long
'  ���� ���� ���� ���� ������ Ȯ���Ѵ�.
Public Declare Function AxmMotGetElectricGearRatio Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpNumerator As Long, ByRef lpDenominator As Long) As Long

'  ���� ���� ��ũ ����Ʈ ���� ���� �մϴ�.
'  ������, ������ �������� ��ũ ���� �����ϴ� �Լ�.
'  ���� ���� 1 ~ 1000���� ����
'  �ִ� ��ũ�� 0.1% ������ ���� ��.
Public Declare Function AxmMotSetTorqueLimit Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dbPluseDirTorqueLimit As Double, ByVal dbMinusDirTorqueLimit As Double) As Long

'  ���� ���� ��ũ ����Ʈ ���� Ȯ�� �մϴ�.
'  ������, ������ �������� ��ũ ���� �о� ���� �Լ�.
'  ���� ���� 1 ~ 1000���� ����
'  �ִ� ��ũ�� 0.1% ������ ���� ��.
Public Declare Function AxmMotGetTorqueLimit Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dbpPluseDirTorqueLimit As Double, ByRef dbpMinusDirTorqueLimit As Double) As Long

'  ���� ���� AxmOverridePos�� ���� Ư�� ��� ��� ������ �����Ѵ�.
'  dwUsage        : AxmOverridPos ���� ���� ��ġ �Ǵ� ��� ��� ����.
'                   DISABLE(0) : Ư�� ��� ������� ����.
'                   ENABLE(1) : AxmMoveStartPos ������ ���� �� ��ġ ���� ���� ��ġ�� ���� �Ÿ��� lDecelPosRatio(%)�� �������� �Ǵ��Ѵ�.
'  lDecelPosRatio : ���� �Ÿ��� ���� %��.
'  dReserved      : ������� ����.
Public Declare Function AxmOverridePosSetFunction Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwUsage As Long, ByVal lDecelPosRatio As Long, ByVal dReserved As Double) As Long
'  ���� ���� AxmOverridePos�� ���� Ư�� ��� ��� ������ Ȯ�� �Ѵ�.
Public Declare Function AxmOverridePosGetFunction Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpUsage As Long, ByRef lpDecelPosRatio As Long, ByRef dpReserved As Double) As Long
' ======== PCI-R3200-MLIII ���� �Լ�==================================================================================
' M3 �����ѿ� Command Execution�� �����Ѵ�
Public Declare Function AxmServoCmdExecution Lib "AXL.dll" (ByVal lAxisNo As Interger, ByVal dwCommand As Long, ByVal dwSize As Long, ByRef pdwExcData As Long) As Long

' -------------------------------------------------------------------------------------------------------------------
' ======== SMP ���� �Լ� =============================================================================================
' Inposition ��ȣ�� Range�� �����Ѵ�. (dInposRange > 0)
Public Declare Function AxmSignalSetInposRange Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dInposRange As Double) As Long
' Inposition ��ȣ�� Range�� ��ȯ�Ѵ�.
Public Declare Function AxmSignalGetInposRange Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpInposRange As Double) As Long

' �������̵��Ҷ� ��ġ�Ӽ�(����/���)�� �����Ѵ�.
Public Declare Function AxmMotSetOverridePosMode Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwAbsRelMode As Long) As Long
' �������̵��Ҷ� ��ġ�Ӽ�(����/���)�� �о�´�.
Public Declare Function AxmMotGetOverridePosMode Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpAbsRelMode) As Long
' LineMove �������̵��Ҷ� ��ġ�Ӽ�(����/���)�� �����Ѵ�.
Public Declare Function AxmMotSetOverrideLinePosMode Lib "AXL.dll" (ByVal lCoordNo As Long, ByVal dwAbsRelMode As Long) As Long
Public Declare Function ��ġ�Ӽ�(����/���)�� �о�´�.
Public Declare Function AxmMotGetOverrideLinePosMode Lib "AXL.dll" (ByVal lCoordNo As Long, ByRef dwpAbsRelMode As Long) As Long

' AxmMoveStartPos�� �����ϸ� ����ӵ�(EndVel)�� �߰��Ǿ���.
Public Declare Function AxmMoveStartPosEx Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal dEndVel As Double) As Long
' AxmMovePos�� �����ϸ� ����ӵ�(EndVel)�� �߰��Ǿ���.
Public Declare Function AxmMovePosEx Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal dEndVel As Double) As Long

'Coordinate Motion�� ��λ󿡼� ��������(dDecel) ��Ų��.
Public Declare Function AxmMoveCoordStop Lib "AXL.dll" (ByVal lCoordNo As Long, ByVal dDecel As Double) As Long
' Coordinate Motion�� ������ ��Ų��.
Public Declare Function AxmMoveCoordEStop Lib "AXL.dll" (ByVal lCoordNo As Long) As Long
' Coordinate Motion�� ��λ󿡼� �������� ��Ų��.
Public Declare Function AxmMoveCoordSStop Lib "AXL.dll" (ByVal lCoordNo As Long) As Long

' AxmLineMove����� ��ġ�� �������̵� ��Ų��.
Public Declare Function AxmOverrideLinePos Lib "AXL.dll" (ByVal lCoordNo As Long, ByRef dpOverridePos As Double) As Long
' AxmLineMove����� �ӵ��� �������̵� ��Ų��. ������� �ӵ������� dpDistance�� �����ȴ�.
Public Declare Function AxmOverrideLineVel Lib "AXL.dll" (ByVal lCoordNo As Long, ByVal dOverrideVel, ByRef dpDistance As Double) As Long

' AxmLineMove����� �ӵ��� �������̵� ��Ų��.
' dMaxAccel  : �������̵� ���ӵ�
' dMaxDecel  : �������̵� ���ӵ�
' dpDistance : ������ �ӵ� ����
Public Declare Function AxmOverrideLineAccelVelDecel Lib "AXL.dll" (ByVal lCoordNo As Long, ByVal dOverrideVelocity As Double, ByVal dMaxAccel As Double, ByVal dMaxDecel As Double, ByRef dpDistance As Double) As Long
' AxmOverrideVelAtPos�� �߰������� AccelDecel�� �������̵� ��Ų��.
Public Declare Function AxmOverrideAccelVelDecelAtPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal dOverridePos As Double, ByVal dOverrideVel As Double, ByVal dOverrideAccel As Double, ByVal dOverrideDecel As Double, ByVal lTarget As Long) As Long

' �ϳ��� �������࿡ �ټ��� �����̺������ �����Ѵ�(Electronic Gearing).
' lMasterAxisNo : ��������
' lSize : �����̺��� ����(�ִ� 8)
' lpSlaveAxisNo : �����̺��� ��ȣ
' dpGearRatio : ���������� ���������ϴ� �����̺��� ����(0�� ����, 1 = 100%)
Public Declare Function AxmEGearSet Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByVal lSize As Long, ByRef lpSlaveAxisNo As Long, ByRef dpGearRatio As Double) As Long
' Electronic Gearing������ �о�´�.
Public Declare Function AxmEGearGet Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByRef lpSize As Long, ByRef lpSlaveAxisNo As Long, ByRef dpGearRatio As Double) As Long
' Electronic Gearing�� �����Ѵ�.
Public Declare Function AxmEGearReset Lib "AXL.dll" (ByVal lMasterAxisNo As Long) As Long
' Electronic Gearing�� Ȱ��/��Ȱ���Ѵ�.
Public Declare Function AxmEGearEnable Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByVal dwEnable As Long) As Long
' Electronic Gearing�� Ȱ��/��Ȱ�����¸� �о�´�.
Public Declare Function AxmEGearIsEnable Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByRef dwpEnable As Long) As Long

' ���ǻ���: �Է��� ����ӵ��� '0'�̸��̸� '0'����, 'AxmMotSetMaxVel'�� ������ �ִ�ӵ��� �ʰ��ϸ� 'MaxVel'�� �缳���ȴ�. 
' ���� �࿡ ����ӵ��� �����Ѵ�.
Public Declare Function AxmMotSetEndVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dEndVelocity As Double) As Long
' ���� ���� ����ӵ��� ��ȯ�Ѵ�.
Public Declare Function AxmMotGetEndVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpEndVelocity As Double) As Long
' -------------------------------------------------------------------------------------------------------------------