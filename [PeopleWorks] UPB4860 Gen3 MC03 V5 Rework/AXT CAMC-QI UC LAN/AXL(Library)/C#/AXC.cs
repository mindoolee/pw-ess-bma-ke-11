/****************************************************************************
*****************************************************************************
**
** File Name
** ----------
**
** AXC.CS
**
** COPYRIGHT (c) AJINEXTEK Co., LTD
**
*****************************************************************************
*****************************************************************************
**
** Description
** -----------
** Ajinextek Counter Library Header File
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

public class CAXC
{
//========== ���� �� ��� ���� 
    // CNT ����� �ִ��� Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxcInfoIsCNTModule(ref uint upStatus);
    
    // CNT ��� No Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxcInfoGetModuleNo(int lBoardNo, int lModulePos, ref int lpModuleNo);
    
    // CNT ����� ����� ���� Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxcInfoGetModuleCount(ref int lpModuleCount);

    // ������ ����� ī���� �Է� ä�� ���� Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxcInfoGetChannelCount(int lModuleNo, ref int lpCount);
    
    // �ý��ۿ� ������ ī������ �� ä�� ���� Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxcInfoGetTotalChannelCount(ref int lpChannelCount);    

    // ������ ��� ��ȣ�� ���̽� ���� ��ȣ, ��� ��ġ, ��� ID Ȯ��
    [DllImport("AXL.dll")] public static extern uint AxcInfoGetModule(int lModuleNo, ref int lpBoardNo, ref int lpModulePos, ref uint upModuleID);

    // �ش� ����� ��� ������ �������� ��ȯ�Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxcInfoGetModuleStatus(int lModuleNo);

    [DllImport("AXL.dll")] public static extern uint AxcInfoGetFirstChannelNoOfModuleNo(int lModuleNo, ref int lpChannelNo);

    // ī���� ����� Encoder �Է� ����� ���� �մϴ�.
    // dwMethod --> 0x00 : Sign and pulse, x1 multiplication
    // dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
    // dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
    // dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
    // dwMethod --> 0x08 : Sign and pulse, x2 multiplication
    // dwMethod --> 0x09 : Increment and decrement pulses, x1 multiplication
    // dwMethod --> 0x0A : Increment and decrement pulses, x2 multiplication
    // SIO-CN2CH�� ���
    // dwMethod --> 0x00 : Up/Down ���, A phase : �޽�, B phase : ����
    // dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
    // dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
    // dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
    [DllImport("AXL.dll")] public static extern uint AxcSignalSetEncInputMethod(int lChannelNo, uint dwMethod);

    // ī���� ����� Encoder �Է� ����� ���� �մϴ�.
    // *dwpUpMethod --> 0x00 : Sign and pulse, x1 multiplication
    // *dwpUpMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
    // *dwpUpMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
    // *dwpUpMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
    // *dwpUpMethod --> 0x08 : Sign and pulse, x2 multiplication
    // *dwpUpMethod --> 0x09 : Increment and decrement pulses, x1 multiplication
    // *dwpUpMethod --> 0x0A : Increment and decrement pulses, x2 multiplication
    // SIO-CN2CH�� ���
    // dwMethod --> 0x00 : Up/Down ���, A phase : �޽�, B phase : ����
    // dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
    // dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
    // dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
    [DllImport("AXL.dll")] public static extern uint AxcSignalGetEncInputMethod(int lChannelNo, ref uint dwpUpMethod);

    // ī���� ����� Ʈ���Ÿ� ���� �մϴ�.
    // dwMode -->  0x00 : Latch
    // dwMode -->  0x01 : State
    // dwMode -->  0x02 : Special State    --> SIO-CN2CH ����
    // SIO-CN2CH�� ���
    // dwMode -->  0x00 : ���� ��ġ Ʈ���� �Ǵ� �ֱ� ��ġ Ʈ����.
    // ���� : ��ǰ���� ����� ���� �ٸ��� ������ �����Ͽ� ��� �ʿ�.
    // dwMode -->  0x01 : �ð� �ֱ� Ʈ����(AxcTriggerSetFreq�� ����)
    [DllImport("AXL.dll")] public static extern uint AxcTriggerSetFunction(int lChannelNo, uint dwMode);

    // ī���� ����� Ʈ���� ������ Ȯ�� �մϴ�.
    // *dwMode -->  0x00 : Latch
    // *dwMode -->  0x01 : State
    // *dwMode -->  0x02 : Special State
    // dwMode -->  0x00 : ���� ��ġ Ʈ���� �Ǵ� �ֱ� ��ġ Ʈ����.
    // ���� : ��ǰ���� ����� ���� �ٸ��� ������ �����Ͽ� ��� �ʿ�.
    // dwMode -->  0x01 : �ð� �ֱ� Ʈ����(AxcTriggerSetFreq�� ����)
    [DllImport("AXL.dll")] public static extern uint AxcTriggerGetFunction(int lChannelNo, ref uint dwpMode);

    // dwUsage --> 0x00 : Trigger Not use
    // dwUsage --> 0x01 : Trigger use
    [DllImport("AXL.dll")] public static extern uint AxcTriggerSetNotchEnable(int lChannelNo, uint dwUsage);

    // *dwUsage --> 0x00 : Trigger Not use
    // *dwUsage --> 0x01 : Trigger use
    [DllImport("AXL.dll")] public static extern uint AxcTriggerGetNotchEnable(int lChannelNo, ref uint dwpUsage);
    

    // ī���� ����� Captuer �ؼ��� ���� �մϴ�.(External latch input polarity)
    // dwCapturePol --> 0x00 : Signal OFF -> ON
    // dwCapturePol --> 0x01 : Signal ON -> OFF
    [DllImport("AXL.dll")] public static extern uint AxcSignalSetCaptureFunction(int lChannelNo, uint dwCapturePol);

    // ī���� ����� Captuer �ؼ� ������ Ȯ�� �մϴ�.(External latch input polarity)
    // *dwCapturePol --> 0x00 : Signal OFF -> ON
    // *dwCapturePol --> 0x01 : Signal ON -> OFF
    [DllImport("AXL.dll")] public static extern uint AxcSignalGetCaptureFunction(int lChannelNo, ref uint dwpCapturePol);

    // ī���� ����� Captuer ��ġ�� Ȯ�� �մϴ�.(External latch)
    // *dbpCapturePos --> Capture position ��ġ
    [DllImport("AXL.dll")] public static extern uint AxcSignalGetCapturePos(int lChannelNo, ref double dbpCapturePos);

    // ī���� ����� ī���� ���� Ȯ�� �մϴ�.
    // *dbpActPos --> ī���� ��
    [DllImport("AXL.dll")] public static extern uint AxcStatusGetActPos(int lChannelNo, ref double dbpActPos);

    // ī���� ����� ī���� ���� dbActPos ������ ���� �մϴ�.
    [DllImport("AXL.dll")] public static extern uint AxcStatusSetActPos(int lChannelNo, double dbActPos);

    // ī���� ����� Ʈ���� ��ġ�� �����մϴ�.
    // ī���� ����� Ʈ���� ��ġ�� 2�������� ���� �� �� �ֽ��ϴ�.
    [DllImport("AXL.dll")] public static extern uint AxcTriggerSetNotchPos(int lChannelNo, double dbLowerPos, double dbUpperPos);

    // ī���� ����� ������ Ʈ���� ��ġ�� Ȯ�� �մϴ�.
    [DllImport("AXL.dll")] public static extern uint AxcTriggerGetNotchPos(int lChannelNo, ref double dbpLowerPos, ref double dbpUpperPos);

    // ī���� ����� Ʈ���� ����� ������ �մϴ�.
    // dwOutVal --> 0x00 : Ʈ���� ��� '0'
    // dwOutVal --> 0x01 : Ʈ���� ��� '1'
    [DllImport("AXL.dll")] public static extern uint AxcTriggerSetOutput(int lChannelNo, uint dwOutVal);

    // ī���� ����� ���¸� Ȯ���մϴ�.
    // Bit '0' : Carry (ī���� ����ġ�� ���� �޽��� ���� ī���� ����ġ�� �Ѿ� 0�� �ٲ���� �� 1��ĵ�� ON���� �մϴ�.)
    // Bit '1' : Borrow (ī���� ����ġ�� ���� �޽��� ���� 0�� �Ѿ� ī���� ����ġ�� �ٲ���� �� 1��ĵ�� ON���� �մϴ�.)
    // Bit '2' : Trigger output status
    // Bit '3' : Latch input status
    [DllImport("AXL.dll")] public static extern uint AxcStatusGetChannel(int lChannelNo, ref uint dwpChannelStatus);


    // SIO-CN2CH ���� �Լ���
    //
    // ī���� ����� ��ġ ������ �����Ѵ�.
    // ���� ��ġ �̵����� ���� �޽� ������ �����ϴµ�,
    // ex) 1mm �̵��� 1000�� �ʿ��ϴٸ�dMoveUnitPerPulse = 0.001�� �Է��ϰ�,
    //     ���� ��� �Լ��� ��ġ�� ���õ� ���� mm ������ �����ϸ� �ȴ�.
    [DllImport("AXL.dll")] public static extern uint AxcMotSetMoveUnitPerPulse(int lChannelNo, double dMoveUnitPerPulse);

    // ī���� ����� ��ġ ������ Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxcMotGetMoveUnitPerPulse(int lChannelNo, ref double dpMoveUnitPerPuls);

    // ī���� ����� ���ڴ� �Է� ī���͸� ���� ����� �����Ѵ�.
    // dwReverse --> 0x00 : �������� ����.
    // dwReverse --> 0x01 : ����.
    [DllImport("AXL.dll")] public static extern uint AxcSignalSetEncReverse(int lChannelNo, uint dwReverse);

    // ī���� ����� ���ڴ� �Է� ī���͸� ���� ����� ������ Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxcSignalGetEncReverse(int lChannelNo, ref uint dwpReverse);

    // ī���� ����� Encoder �Է� ��ȣ�� �����Ѵ�.
    // dwSource -->  0x00 : 2(A/B)-Phase ��ȣ.
    // dwSource -->  0x01 : Z-Phase ��ȣ.(���⼺ ����.)
    [DllImport("AXL.dll")] public static extern uint AxcSignalSetEncSource(int lChannelNo, uint dwSource);

    // ī���� ����� Encoder �Է� ��ȣ ���� ������ Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxcSignalGetEncSource(int lChannelNo, ref uint dwpSource);

    // ī���� ����� Ʈ���� ��� ���� �� ���� ���� �����Ѵ�.
    // ��ġ �ֱ� Ʈ���� ��ǰ�� ��� ��ġ �ֱ�� Ʈ���� ����� �߻���ų ���� �� ���� ���� �����Ѵ�.
    // ���� ��ġ Ʈ���� ��ǰ�� ��� Ram ���� ������ Ʈ���� ������ ���� ���� ��ġ�� �����Ѵ�.
    // ���� : AxcMotSetMoveUnitPerPulse�� ������ ����.
    // Note : ���Ѱ��� ���Ѱ����� �������� �����Ͽ��� �մϴ�.
    [DllImport("AXL.dll")] public static extern uint AxcTriggerSetBlockLowerPos(int lChannelNo, double dLowerPosition);

    // ī���� ����� Ʈ���� ��� ���� �� ���� ���� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxcTriggerGetBlockLowerPos(int lChannelNo, ref double dpLowerPosition);

    // ī���� ����� Ʈ���� ��� ���� �� ���� ���� �����Ѵ�.
    // ��ġ �ֱ� Ʈ���� ��ǰ�� ��� ��ġ �ֱ�� Ʈ���� ����� �߻���ų ���� �� ���� ���� �����Ѵ�.
    // ���� ��ġ Ʈ���� ��ǰ�� ��� Ʈ���� ������ ������ Ram �� ������ ������ Ʈ���� ������ ����Ǵ� ��ġ�� ���ȴ�.
    // ���� : AxcMotSetMoveUnitPerPulse�� ������ ����.
    // Note : ���Ѱ��� ���Ѱ����� ū���� �����Ͽ��� �մϴ�.
    [DllImport("AXL.dll")] public static extern uint AxcTriggerSetBlockUpperPos(int lChannelNo, double dUpperPosition);
    // ī���� ����� Ʈ���� ��� ���� �� ���� ���� �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxcTriggerGetBlockUpperPos(int lChannelNo, ref double dpUpperrPosition);

    // ī���� ����� ��ġ �ֱ� ��� Ʈ���ſ� ���Ǵ� ��ġ �ֱ⸦ �����Ѵ�.
    // ���� : AxcMotSetMoveUnitPerPulse�� ������ ����.
    [DllImport("AXL.dll")] public static extern uint AxcTriggerSetPosPeriod(int lChannelNo, double dPeriod);

    // ī���� ����� ��ġ �ֱ� ��� Ʈ���ſ� ���Ǵ� ��ġ �ֱ⸦ Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxcTriggerGetPosPeriod(int lChannelNo, ref double dpPeriod);

    // ī���� ����� ��ġ �ֱ� ��� Ʈ���� ���� ��ġ ������ ���� ��ȿ����� �����Ѵ�.
    // dwDirection -->  0x00 : ī������ ��/���� ���Ͽ� Ʈ���� �ֱ� ���� ���.
    // dwDirection -->  0x01 : ī���Ͱ� ���� �Ҷ��� Ʈ���� �ֱ� ���� ���.
    // dwDirection -->  0x01 : ī���Ͱ� ���� �Ҷ��� Ʈ���� �ֱ� ���� ���.
    [DllImport("AXL.dll")] public static extern uint AxcTriggerSetDirectionCheck(int lChannelNo, uint dwDirection);
    // ī���� ����� ��ġ �ֱ� ��� Ʈ���� ���� ��ġ ������ ���� ��ȿ��� ������ Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxcTriggerGetDirectionCheck(int lChannelNo, ref uint dwpDirection);

    // ī���� ����� ��ġ �ֱ� ��� Ʈ���� ����� ����, ��ġ �ֱ⸦ �ѹ��� �����Ѵ�.
    // ��ġ ���� ���� :  AxcMotSetMoveUnitPerPulse�� ������ ����.
    [DllImport("AXL.dll")] public static extern uint AxcTriggerSetBlock(int lChannelNo, double dLower, double dUpper, double dABSod);

    // ī���� ����� ��ġ �ֱ� ��� Ʈ���� ����� ����, ��ġ �ֱ⸦ ������ �ѹ��� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxcTriggerGetBlock(int lChannelNo, ref double dpLower, ref double dpUpper, ref double dpABSod);

    // ī���� ����� Ʈ���� ��� �޽� ���� �����Ѵ�.
    // ���� : uSec
    [DllImport("AXL.dll")] public static extern uint AxcTriggerSetTime(int lChannelNo, double dTrigTime);

    // ī���� ����� Ʈ���� ��� �޽� �� ������ Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxcTriggerGetTime(int lChannelNo, ref double dpTrigTime);

    // ī���� ����� Ʈ���� ��� �޽��� ��� ������ �����Ѵ�.
    // dwLevel -->  0x00 : Ʈ���� ��½� 'Low' ���� ���.
    // dwLevel -->  0x00 : Ʈ���� ��½� 'High' ���� ���.
    [DllImport("AXL.dll")] public static extern uint AxcTriggerSetLevel(int lChannelNo, uint dwLevel);
    // ī���� ����� Ʈ���� ��� �޽��� ��� ���� ������ Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxcTriggerGetLevel(int lChannelNo, ref uint dwpLevel);

    // ī���� ����� ���ļ� Ʈ���� ��� ��ɿ� �ʿ��� ���ļ��� �����Ѵ�.
    // ���� : Hz, ���� : 1Hz ~ 500 kHz
    [DllImport("AXL.dll")] public static extern uint AxcTriggerSetFreq(int lChannelNo, uint dwFreqency);
    // ī���� ����� ���ļ� Ʈ���� ��� ��ɿ� �ʿ��� ���ļ��� ������ Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxcTriggerGetFreq(int lChannelNo, ref uint dwpFreqency);	

    // ī���� ����� ���� ä�ο� ���� ���� ��� ���� �����Ѵ�.
    // dwOutput ���� : 0x00 ~ 0x0F, �� ä�δ� 4���� ���� ���
    [DllImport("AXL.dll")] public static extern uint AxcSignalWriteOutput(int lChannelNo, uint dwOutput);

    // ī���� ����� ���� ä�ο� ���� ���� ��� ���� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxcSignalReadOutput(int lChannelNo, ref uint dwpOutput);

    // ī���� ����� ���� ä�ο� ���� ���� ��� ���� ��Ʈ ���� �����Ѵ�.
    // lBitNo ���� : 0 ~ 3, �� ä�δ� 4���� ���� ���
    [DllImport("AXL.dll")] public static extern uint AxcSignalWriteOutputBit(int lChannelNo, int lBitNo, uint uOnOff);
    // ī���� ����� ���� ä�ο� ���� ���� ��� ���� ��Ʈ ���� Ȯ�� �Ѵ�.
    // lBitNo ���� : 0 ~ 3
    [DllImport("AXL.dll")] public static extern uint AxcSignalReadOutputBit(int lChannelNo, int lBitNo, ref uint upOnOff);

    // ī���� ����� ���� ä�ο� ���� ���� �Է� ���� Ȯ���Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxcSignalReadInput(int lChannelNo, ref uint dwpInput);

    // ī���� ����� ���� ä�ο� ���� ���� �Է� ���� ��Ʈ ���� Ȯ�� �Ѵ�.
    // lBitNo ���� : 0 ~ 3
    [DllImport("AXL.dll")] public static extern uint AxcSignalReadInputBit(int lChannelNo, int lBitNo, ref uint upOnOff);

    // ī���� ����� Ʈ���� ����� Ȱ��ȭ �Ѵ�.
    // ���� ������ ��ɿ� ���� Ʈ���� ����� ���������� ����� ������ �����Ѵ�.
    [DllImport("AXL.dll")] public static extern uint AxcTriggerSetEnable(int lChannelNo, uint dwUsage);

    // ī���� ����� Ʈ���� ��� Ȱ��ȭ ���� ������ Ȯ���ϴ�.
    [DllImport("AXL.dll")] public static extern uint AxcTriggerGetEnable(int lChannelNo, ref uint dwpUsage);

    // ī���� ����� ������ġ Ʈ���� ����� ���� ������ RAM ������ Ȯ���Ѵ�.
    // dwAddr ���� : 0x0000 ~ 0x1FFFF;
    [DllImport("AXL.dll")] public static extern uint AxcTriggerReadAbsRamData(int lChannelNo, uint dwAddr, ref uint dwpData);

    // ī���� ����� ������ġ Ʈ���� ����� ���� �ʿ��� RAM ������ �����Ѵ�.
    // dwAddr ���� : 0x0000 ~ 0x1FFFF;
    [DllImport("AXL.dll")] public static extern uint AxcTriggerWriteAbsRamData(int lChannelNo, uint dwAddr, uint dwData);

    // ī���� ����� ������ġ Ʈ���� ����� ���� �ʿ��� RAM ������ �ѹ��� �����Ѵ�.
    // dwTrigNum ���� : ~ 0x20000, 
    // dwDirection --> 0x0 : ���� Ʈ���� ��ġ�� ���� Ʈ���� ���� ���� �Է�. ��ġ�� �����ϴ� �������� Ʈ���� ��½� ���.
    // dwDirection --> 0x1 : ���� ī���Ϳ� ���� Ʈ���� ���� ���� �Է�. ��ġ�� �����ϴ� �������� Ʈ���� ��½� ���.
    [DllImport("AXL.dll")] public static extern uint AxcTriggerSetAbs(int lChannelNo, uint dwTrigNum, ref uint dwTrigPos, uint dwDirection);

    // ī���� ����� ������ġ Ʈ���� ����� ���� �ʿ��� RAM ������ �ѹ��� �����Ѵ�.
    // dwTrigNum ���� : ~ 0x20000  *RTEX CNT2 �� ��� 0x200* 
    // dwDirection --> 0x0 : ���� Ʈ���� ��ġ�� ���� Ʈ���� ���� ���� �Է�. ��ġ�� �����ϴ� �������� Ʈ���� ��½� ���.
    // dwDirection --> 0x1 : ���� ī���Ϳ� ���� Ʈ���� ���� ���� �Է�. ��ġ�� �����ϴ� �������� Ʈ���� ��½� ���.
	// dTrigPos : ī���� ����� Ʈ���� Pos�� double ������ ���
    [DllImport("AXL.dll")] public static extern uint AxcTriggerSetAbsDouble(int lChannelNo, uint dwTrigNum, ref double* dTrigPos, uint dwDirection);
}

