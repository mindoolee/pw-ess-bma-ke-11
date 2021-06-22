/****************************************************************************
*****************************************************************************
**
** File Name
** ----------
**
** AXC.H
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

#ifndef __AXT_AXC_H__
#define __AXT_AXC_H__

#include "AXHS.h"
#include "AXHD.h"

#ifdef __cplusplus
extern "C" {
#endif    //__cplusplus

//========== ���� �� ��� ���� 
    // CNT ����� �ִ��� Ȯ��
    DWORD __stdcall AxcInfoIsCNTModule(DWORD *upStatus);
    
    // CNT ��� No Ȯ��
    DWORD __stdcall AxcInfoGetModuleNo(long lBoardNo, long lModulePos, long *lpModuleNo);
    
    // CNT ����� ����� ���� Ȯ��
    DWORD __stdcall AxcInfoGetModuleCount(long *lpModuleCount);

    // ������ ����� ī���� �Է� ä�� ���� Ȯ��
    DWORD __stdcall AxcInfoGetChannelCount(long lModuleNo, long *lpCount);
    
    // �ý��ۿ� ������ ī������ �� ä�� ���� Ȯ��
    DWORD __stdcall AxcInfoGetTotalChannelCount(long *lpChannelCount);    

    // ������ ��� ��ȣ�� ���̽� ���� ��ȣ, ��� ��ġ, ��� ID Ȯ��
    DWORD __stdcall AxcInfoGetModule(long lModuleNo, long *lpBoardNo, long *lpModulePos, DWORD *upModuleID);

    // �ش� ����� ��� ������ �������� ��ȯ�Ѵ�.
    DWORD __stdcall AxcInfoGetModuleStatus(long lModuleNo);

    DWORD __stdcall AxcInfoGetFirstChannelNoOfModuleNo(long lModuleNo, long *lpChannelNo);

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
    DWORD __stdcall AxcSignalSetEncInputMethod(long lChannelNo, DWORD dwMethod);

    // ī���� ����� Encoder �Է� ����� ���� �մϴ�.
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
    DWORD __stdcall AxcSignalGetEncInputMethod(long lChannelNo, DWORD* dwpUpMethod);

    // ī���� ����� Ʈ���Ÿ� ���� �մϴ�.
    // dwMode -->  0x00 : Latch
    // dwMode -->  0x01 : State
    // dwMode -->  0x02 : Special State    --> SIO-CN2CH ����
    // SIO-CN2CH�� ���
    // dwMode -->  0x00 : ���� ��ġ Ʈ���� �Ǵ� �ֱ� ��ġ Ʈ����.
    // ���� : ��ǰ���� ����� ���� �ٸ��� ������ �����Ͽ� ��� �ʿ�.
    // dwMode -->  0x01 : �ð� �ֱ� Ʈ����(AxcTriggerSetFreq�� ����)
    // SIO-HPC4�� ���
    // dwMode -->  0x00 : timer mode with counter & frequncy.
    // dwMode -->  0x01 : timer mode.
    // dwMode -->  0x02 : absolute mode[with fifo].
    // dwMode -->  0x03 : periodic mode.[Default]
    DWORD __stdcall AxcTriggerSetFunction(long lChannelNo, DWORD dwMode);

    // ī���� ����� Ʈ���� ������ Ȯ�� �մϴ�.
    // *dwMode -->  0x00 : Latch
    // *dwMode -->  0x01 : State
    // *dwMode -->  0x02 : Special State
    // SIO-CN2CH�� ���
    // *dwMode -->  0x00 : ���� ��ġ Ʈ���� �Ǵ� �ֱ� ��ġ Ʈ����.
    // ���� : ��ǰ���� ����� ���� �ٸ��� ������ �����Ͽ� ��� �ʿ�.
    // *dwMode -->  0x01 : �ð� �ֱ� Ʈ����(AxcTriggerSetFreq�� ����)
    // SIO-HPC4�� ���
    // *dwMode -->  0x00 : timer mode with counter & frequncy.
    // *dwMode -->  0x01 : timer mode.
    // *dwMode -->  0x02 : absolute mode[with fifo].
    // *dwMode -->  0x03 : periodic mode.[Default]
    DWORD __stdcall AxcTriggerGetFunction(long lChannelNo, DWORD* dwpMode);

    // dwUsage --> 0x00 : Trigger Not use
    // dwUsage --> 0x01 : Trigger use
    DWORD __stdcall AxcTriggerSetNotchEnable(long lChannelNo, DWORD dwUsage);

    // *dwUsage --> 0x00 : Trigger Not use
    // *dwUsage --> 0x01 : Trigger use
    DWORD __stdcall AxcTriggerGetNotchEnable(long lChannelNo, DWORD* dwpUsage);
    

    // ī���� ����� Capture �ؼ��� ���� �մϴ�.(External latch input polarity)
    // dwCapturePol --> 0x00 : Signal OFF -> ON
    // dwCapturePol --> 0x01 : Signal ON -> OFF
    DWORD __stdcall AxcSignalSetCaptureFunction(long lChannelNo, DWORD dwCapturePol);

    // ī���� ����� Capture �ؼ� ������ Ȯ�� �մϴ�.(External latch input polarity)
    // *dwCapturePol --> 0x00 : Signal OFF -> ON
    // *dwCapturePol --> 0x01 : Signal ON -> OFF
    DWORD __stdcall AxcSignalGetCaptureFunction(long lChannelNo, DWORD* dwpCapturePol);

    // ī���� ����� Capture ��ġ�� Ȯ�� �մϴ�.(External latch)
    // *dbpCapturePos --> Capture position ��ġ
    DWORD __stdcall AxcSignalGetCapturePos(long lChannelNo, double* dbpCapturePos);

    // ī���� ����� ī���� ���� Ȯ�� �մϴ�.
    // *dbpActPos --> ī���� ��
    DWORD __stdcall AxcStatusGetActPos(long lChannelNo, double* dbpActPos);

    // ī���� ����� ī���� ���� dbActPos ������ ���� �մϴ�.
    DWORD __stdcall AxcStatusSetActPos(long lChannelNo, double dbActPos);

    // ī���� ����� Ʈ���� ��ġ�� �����մϴ�.
    // ī���� ����� Ʈ���� ��ġ�� 2�������� ���� �� �� �ֽ��ϴ�.
    DWORD __stdcall AxcTriggerSetNotchPos(long lChannelNo, double dbLowerPos, double dbUpperPos);

    // ī���� ����� ������ Ʈ���� ��ġ�� Ȯ�� �մϴ�.
    DWORD __stdcall AxcTriggerGetNotchPos(long lChannelNo, double* dbpLowerPos, double* dbpUpperPos);

    // ī���� ����� Ʈ���� ����� ������ �մϴ�.
    // dwOutVal --> 0x00 : Ʈ���� ��� '0'
    // dwOutVal --> 0x01 : Ʈ���� ��� '1'
    DWORD __stdcall AxcTriggerSetOutput(long lChannelNo, DWORD dwOutVal);

    // ī���� ����� ���¸� Ȯ���մϴ�.
    // Bit '0' : Carry (ī���� ����ġ�� ���� �޽��� ���� ī���� ����ġ�� �Ѿ� 0�� �ٲ���� �� 1��ĵ�� ON���� �մϴ�.)
    // Bit '1' : Borrow (ī���� ����ġ�� ���� �޽��� ���� 0�� �Ѿ� ī���� ����ġ�� �ٲ���� �� 1��ĵ�� ON���� �մϴ�.)
    // Bit '2' : Trigger output status
    // Bit '3' : Latch input status
    DWORD __stdcall AxcStatusGetChannel(long lChannelNo, DWORD* dwpChannelStatus);


    // SIO-CN2CH ���� �Լ���
    //
    // ī���� ����� ��ġ ������ �����Ѵ�.
    // ���� ��ġ �̵����� ���� �޽� ������ �����ϴµ�,
    // ex) 1mm �̵��� 1000�� �ʿ��ϴٸ�dMoveUnitPerPulse = 0.001�� �Է��ϰ�,
    //     ���� ��� �Լ��� ��ġ�� ���õ� ���� mm ������ �����ϸ� �ȴ�.
    DWORD __stdcall AxcMotSetMoveUnitPerPulse(long lChannelNo, double dMoveUnitPerPulse);

    // ī���� ����� ��ġ ������ Ȯ���Ѵ�.
    DWORD __stdcall AxcMotGetMoveUnitPerPulse(long lChannelNo, double* dpMoveUnitPerPuls);

    // ī���� ����� ���ڴ� �Է� ī���͸� ���� ����� �����Ѵ�.
    // dwReverse --> 0x00 : �������� ����.
    // dwReverse --> 0x01 : ����.
    DWORD __stdcall AxcSignalSetEncReverse(long lChannelNo, DWORD dwReverse);

    // ī���� ����� ���ڴ� �Է� ī���͸� ���� ����� ������ Ȯ���Ѵ�.
    DWORD __stdcall AxcSignalGetEncReverse(long lChannelNo, DWORD* dwpReverse);

    // ī���� ����� Encoder �Է� ��ȣ�� �����Ѵ�.
    // dwSource -->  0x00 : 2(A/B)-Phase ��ȣ.
    // dwSource -->  0x01 : Z-Phase ��ȣ.(���⼺ ����.)
    DWORD  __stdcall AxcSignalSetEncSource(long lChannelNo, DWORD dwSource);

    // ī���� ����� Encoder �Է� ��ȣ ���� ������ Ȯ���Ѵ�.
    DWORD  __stdcall AxcSignalGetEncSource(long lChannelNo, DWORD* dwpSource);

    // ī���� ����� Ʈ���� ��� ���� �� ���� ���� �����Ѵ�.
    // ��ġ �ֱ� Ʈ���� ��ǰ�� ��� ��ġ �ֱ�� Ʈ���� ����� �߻���ų ���� �� ���� ���� �����Ѵ�.
    // ���� ��ġ Ʈ���� ��ǰ�� ��� Ram ���� ������ Ʈ���� ������ ���� ���� ��ġ�� �����Ѵ�.
    // ���� : AxcMotSetMoveUnitPerPulse�� ������ ����.
    // Note : ���Ѱ��� ���Ѱ����� �������� �����Ͽ��� �մϴ�.
    DWORD  __stdcall AxcTriggerSetBlockLowerPos(long lChannelNo, double dLowerPosition);

    // ī���� ����� Ʈ���� ��� ���� �� ���� ���� Ȯ���Ѵ�.
    DWORD  __stdcall AxcTriggerGetBlockLowerPos(long lChannelNo, double* dpLowerPosition);

    // ī���� ����� Ʈ���� ��� ���� �� ���� ���� �����Ѵ�.
    // ��ġ �ֱ� Ʈ���� ��ǰ�� ��� ��ġ �ֱ�� Ʈ���� ����� �߻���ų ���� �� ���� ���� �����Ѵ�.
    // ���� ��ġ Ʈ���� ��ǰ�� ��� Ʈ���� ������ ������ Ram �� ������ ������ Ʈ���� ������ ����Ǵ� ��ġ�� ���ȴ�.
    // ���� : AxcMotSetMoveUnitPerPulse�� ������ ����.
    // Note : ���Ѱ��� ���Ѱ����� ū���� �����Ͽ��� �մϴ�.
    DWORD  __stdcall AxcTriggerSetBlockUpperPos(long lChannelNo, double dUpperPosition);
    // ī���� ����� Ʈ���� ��� ���� �� ���� ���� �����Ѵ�.
    DWORD  __stdcall AxcTriggerGetBlockUpperPos(long lChannelNo, double* dpUpperrPosition);

    // ī���� ����� ��ġ �ֱ� ��� Ʈ���ſ� ���Ǵ� ��ġ �ֱ⸦ �����Ѵ�.
    // ���� : AxcMotSetMoveUnitPerPulse�� ������ ����.
    DWORD  __stdcall AxcTriggerSetPosPeriod(long lChannelNo, double dPeriod);

    // ī���� ����� ��ġ �ֱ� ��� Ʈ���ſ� ���Ǵ� ��ġ �ֱ⸦ Ȯ���Ѵ�.
    DWORD  __stdcall AxcTriggerGetPosPeriod(long lChannelNo, double* dpPeriod);

    // ī���� ����� ��ġ �ֱ� ��� Ʈ���� ���� ��ġ ������ ���� ��ȿ����� �����Ѵ�.
    // dwDirection -->  0x00 : ī������ ��/���� ���Ͽ� Ʈ���� �ֱ� ���� ���.
    // dwDirection -->  0x01 : ī���Ͱ� ���� �Ҷ��� Ʈ���� �ֱ� ���� ���.
    // dwDirection -->  0x01 : ī���Ͱ� ���� �Ҷ��� Ʈ���� �ֱ� ���� ���.
    DWORD  __stdcall AxcTriggerSetDirectionCheck(long lChannelNo, DWORD dwDirection);
    // ī���� ����� ��ġ �ֱ� ��� Ʈ���� ���� ��ġ ������ ���� ��ȿ��� ������ Ȯ���Ѵ�.
    DWORD  __stdcall AxcTriggerGetDirectionCheck(long lChannelNo, DWORD* dwpDirection);

    // ī���� ����� ��ġ �ֱ� ��� Ʈ���� ����� ����, ��ġ �ֱ⸦ �ѹ��� �����Ѵ�.
    // ��ġ ���� ���� :  AxcMotSetMoveUnitPerPulse�� ������ ����.
    DWORD  __stdcall AxcTriggerSetBlock(long lChannelNo, double dLower, double dUpper, double dABSod);

    // ī���� ����� ��ġ �ֱ� ��� Ʈ���� ����� ����, ��ġ �ֱ⸦ ������ �ѹ��� Ȯ���Ѵ�.
    DWORD  __stdcall AxcTriggerGetBlock(long lChannelNo, double *dpLower, double *dpUpper, double *dpABSod);

    // ī���� ����� Ʈ���� ��� �޽� ���� �����Ѵ�.
    // ���� : uSec
    DWORD  __stdcall AxcTriggerSetTime(long lChannelNo, double dTrigTime);

    // ī���� ����� Ʈ���� ��� �޽� �� ������ Ȯ���Ѵ�.
    DWORD  __stdcall AxcTriggerGetTime(long lChannelNo, double* dpTrigTime);

    // ī���� ����� Ʈ���� ��� �޽��� ��� ������ �����Ѵ�.
    // dwLevel -->  0x00 : Ʈ���� ��½� 'Low' ���� ���.
    // dwLevel -->  0x01 : Ʈ���� ��½� 'High' ���� ���.
    DWORD  __stdcall AxcTriggerSetLevel(long lChannelNo, DWORD dwLevel);
    // ī���� ����� Ʈ���� ��� �޽��� ��� ���� ������ Ȯ���Ѵ�.
    DWORD  __stdcall AxcTriggerGetLevel(long lChannelNo, DWORD* dwpLevel);

    // ī���� ����� ���ļ� Ʈ���� ��� ��ɿ� �ʿ��� ���ļ��� �����Ѵ�.
    // ���� : Hz, ���� : 1Hz ~ 500 kHz
    DWORD  __stdcall AxcTriggerSetFreq(long lChannelNo, DWORD dwFreqency);
    // ī���� ����� ���ļ� Ʈ���� ��� ��ɿ� �ʿ��� ���ļ��� ������ Ȯ���Ѵ�.
    DWORD  __stdcall AxcTriggerGetFreq(long lChannelNo, DWORD* dwpFreqency);

    // ī���� ����� ���� ä�ο� ���� ���� ��� ���� �����Ѵ�.
    // dwOutput ���� : 0x00 ~ 0x0F, �� ä�δ� 4���� ���� ���
    DWORD  __stdcall AxcSignalWriteOutput(long lChannelNo, DWORD dwOutput);

    // ī���� ����� ���� ä�ο� ���� ���� ��� ���� Ȯ���Ѵ�.
    DWORD  __stdcall AxcSignalReadOutput(long lChannelNo, DWORD* dwpOutput);

    // ī���� ����� ���� ä�ο� ���� ���� ��� ���� ��Ʈ ���� �����Ѵ�.
    // lBitNo ���� : 0 ~ 3, �� ä�δ� 4���� ���� ���
    DWORD  __stdcall AxcSignalWriteOutputBit(long lChannelNo, long lBitNo, DWORD uOnOff);
    // ī���� ����� ���� ä�ο� ���� ���� ��� ���� ��Ʈ ���� Ȯ�� �Ѵ�.
    // lBitNo ���� : 0 ~ 3
    DWORD  __stdcall AxcSignalReadOutputBit(long lChannelNo,long lBitNo, DWORD *upOnOff);

    // ī���� ����� ���� ä�ο� ���� ���� �Է� ���� Ȯ���Ѵ�.
    DWORD  __stdcall AxcSignalReadInput(long lChannelNo, DWORD* dwpInput);

    // ī���� ����� ���� ä�ο� ���� ���� �Է� ���� ��Ʈ ���� Ȯ�� �Ѵ�.
    // lBitNo ���� : 0 ~ 3
    DWORD  __stdcall AxcSignalReadInputBit(long lChannelNo, long lBitNo, DWORD *upOnOff);

    // ī���� ����� Ʈ���� ����� Ȱ��ȭ �Ѵ�.
    // ���� ������ ��ɿ� ���� Ʈ���� ����� ���������� ����� ������ �����Ѵ�.
    DWORD  __stdcall AxcTriggerSetEnable(long lChannelNo, DWORD dwUsage);

    // ī���� ����� Ʈ���� ��� Ȱ��ȭ ���� ������ Ȯ���ϴ�.
    DWORD  __stdcall AxcTriggerGetEnable(long lChannelNo, DWORD* dwpUsage);

    // ī���� ����� ������ġ Ʈ���� ����� ���� ������ RAM ������ Ȯ���Ѵ�.
    // dwAddr ���� : 0x0000 ~ 0x1FFFF;
    DWORD  __stdcall AxcTriggerReadAbsRamData(long lChannelNo, DWORD dwAddr, DWORD* dwpData);

    // ī���� ����� ������ġ Ʈ���� ����� ���� �ʿ��� RAM ������ �����Ѵ�.
    // dwAddr ���� : 0x0000 ~ 0x1FFFF;
    DWORD  __stdcall AxcTriggerWriteAbsRamData(long lChannelNo, DWORD dwAddr, DWORD dwData);

    // ī���� ����� ������ġ Ʈ���� ����� ���� �ʿ��� RAM ������ �ѹ��� �����Ѵ�.
    // dwTrigNum ���� : ~ 0x20000  *RTEX CNT2 �� ��� 0x200* 
    // dwDirection --> 0x0 : ���� Ʈ���� ��ġ�� ���� Ʈ���� ���� ���� �Է�. ��ġ�� �����ϴ� �������� Ʈ���� ��½� ���.
    // dwDirection --> 0x1 : ���� ī���Ϳ� ���� Ʈ���� ���� ���� �Է�. ��ġ�� �����ϴ� �������� Ʈ���� ��½� ���.
    DWORD  __stdcall AxcTriggerSetAbs(long lChannelNo, DWORD dwTrigNum, DWORD* dwTrigPos, DWORD dwDirection);

    // ī���� ����� ������ġ Ʈ���� ����� ���� �ʿ��� RAM ������ �ѹ��� �����Ѵ�.
    // dwTrigNum ���� : ~ 0x20000  *RTEX CNT2 �� ��� 0x200* 
    // dwDirection --> 0x0 : ���� Ʈ���� ��ġ�� ���� Ʈ���� ���� ���� �Է�. ��ġ�� �����ϴ� �������� Ʈ���� ��½� ���.
    // dwDirection --> 0x1 : ���� ī���Ϳ� ���� Ʈ���� ���� ���� �Է�. ��ġ�� �����ϴ� �������� Ʈ���� ��½� ���.
	// dTrigPos : ī���� ����� Ʈ���� Pos�� double ������ ���
	DWORD  __stdcall AxcTriggerSetAbsDouble(long lChannelNo, DWORD dwTrigNum, double* dTrigPos, DWORD dwDirection);


#ifdef __cplusplus
}
#endif    //__cplusplus

#endif    //__AXT_AXC_H__
