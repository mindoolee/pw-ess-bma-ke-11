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

//========== 보드 및 모듈 정보 
    // CNT 모듈이 있는지 확인
    DWORD __stdcall AxcInfoIsCNTModule(DWORD *upStatus);
    
    // CNT 모듈 No 확인
    DWORD __stdcall AxcInfoGetModuleNo(long lBoardNo, long lModulePos, long *lpModuleNo);
    
    // CNT 입출력 모듈의 개수 확인
    DWORD __stdcall AxcInfoGetModuleCount(long *lpModuleCount);

    // 지정한 모듈의 카운터 입력 채널 개수 확인
    DWORD __stdcall AxcInfoGetChannelCount(long lModuleNo, long *lpCount);
    
    // 시스템에 장착된 카운터의 전 채널 수를 확인
    DWORD __stdcall AxcInfoGetTotalChannelCount(long *lpChannelCount);    

    // 지정한 모듈 번호로 베이스 보드 번호, 모듈 위치, 모듈 ID 확인
    DWORD __stdcall AxcInfoGetModule(long lModuleNo, long *lpBoardNo, long *lpModulePos, DWORD *upModuleID);

    // 해당 모듈이 제어가 가능한 상태인지 반환한다.
    DWORD __stdcall AxcInfoGetModuleStatus(long lModuleNo);

    DWORD __stdcall AxcInfoGetFirstChannelNoOfModuleNo(long lModuleNo, long *lpChannelNo);

    // 카운터 모듈의 Encoder 입력 방식을 설정 합니다.
    // dwMethod --> 0x00 : Sign and pulse, x1 multiplication
    // dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
    // dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
    // dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
    // dwMethod --> 0x08 : Sign and pulse, x2 multiplication
    // dwMethod --> 0x09 : Increment and decrement pulses, x1 multiplication
    // dwMethod --> 0x0A : Increment and decrement pulses, x2 multiplication
    // SIO-CN2CH/HPC4의 경우
    // dwMethod --> 0x00 : Up/Down 방식, A phase : 펄스, B phase : 방향
    // dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
    // dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
    // dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
    DWORD __stdcall AxcSignalSetEncInputMethod(long lChannelNo, DWORD dwMethod);

    // 카운터 모듈의 Encoder 입력 방식을 설정 합니다.
    // *dwpUpMethod --> 0x00 : Sign and pulse, x1 multiplication
    // *dwpUpMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
    // *dwpUpMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
    // *dwpUpMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
    // *dwpUpMethod --> 0x08 : Sign and pulse, x2 multiplication
    // *dwpUpMethod --> 0x09 : Increment and decrement pulses, x1 multiplication
    // *dwpUpMethod --> 0x0A : Increment and decrement pulses, x2 multiplication
    // SIO-CN2CH/HPC4의 경우
    // dwMethod --> 0x00 : Up/Down 방식, A phase : 펄스, B phase : 방향
    // dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
    // dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
    // dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
    DWORD __stdcall AxcSignalGetEncInputMethod(long lChannelNo, DWORD* dwpUpMethod);

    // 카운터 모듈의 트리거를 설정 합니다.
    // dwMode -->  0x00 : Latch
    // dwMode -->  0x01 : State
    // dwMode -->  0x02 : Special State    --> SIO-CN2CH 전용
    // SIO-CN2CH의 경우
    // dwMode -->  0x00 : 절대 위치 트리거 또는 주기 위치 트리거.
    // 주의 : 제품마다 기능이 서로 다르기 때문에 구별하여 사용 필요.
    // dwMode -->  0x01 : 시간 주기 트리거(AxcTriggerSetFreq로 설정)
    // SIO-HPC4의 경우
    // dwMode -->  0x00 : timer mode with counter & frequncy.
    // dwMode -->  0x01 : timer mode.
    // dwMode -->  0x02 : absolute mode[with fifo].
    // dwMode -->  0x03 : periodic mode.[Default]
    DWORD __stdcall AxcTriggerSetFunction(long lChannelNo, DWORD dwMode);

    // 카운터 모듈의 트리거 설정을 확인 합니다.
    // *dwMode -->  0x00 : Latch
    // *dwMode -->  0x01 : State
    // *dwMode -->  0x02 : Special State
    // SIO-CN2CH의 경우
    // *dwMode -->  0x00 : 절대 위치 트리거 또는 주기 위치 트리거.
    // 주의 : 제품마다 기능이 서로 다르기 때문에 구별하여 사용 필요.
    // *dwMode -->  0x01 : 시간 주기 트리거(AxcTriggerSetFreq로 설정)
    // SIO-HPC4의 경우
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
    

    // 카운터 모듈의 Capture 극성을 설정 합니다.(External latch input polarity)
    // dwCapturePol --> 0x00 : Signal OFF -> ON
    // dwCapturePol --> 0x01 : Signal ON -> OFF
    DWORD __stdcall AxcSignalSetCaptureFunction(long lChannelNo, DWORD dwCapturePol);

    // 카운터 모듈의 Capture 극성 설정을 확인 합니다.(External latch input polarity)
    // *dwCapturePol --> 0x00 : Signal OFF -> ON
    // *dwCapturePol --> 0x01 : Signal ON -> OFF
    DWORD __stdcall AxcSignalGetCaptureFunction(long lChannelNo, DWORD* dwpCapturePol);

    // 카운터 모듈의 Capture 위치를 확인 합니다.(External latch)
    // *dbpCapturePos --> Capture position 위치
    DWORD __stdcall AxcSignalGetCapturePos(long lChannelNo, double* dbpCapturePos);

    // 카운터 모듈의 카운터 값을 확인 합니다.
    // *dbpActPos --> 카운터 값
    DWORD __stdcall AxcStatusGetActPos(long lChannelNo, double* dbpActPos);

    // 카운터 모듈의 카운터 값을 dbActPos 값으로 설정 합니다.
    DWORD __stdcall AxcStatusSetActPos(long lChannelNo, double dbActPos);

    // 카운터 모듈의 트리거 위치를 설정합니다.
    // 카운터 모듈의 트리거 위치는 2개까지만 설정 할 수 있습니다.
    DWORD __stdcall AxcTriggerSetNotchPos(long lChannelNo, double dbLowerPos, double dbUpperPos);

    // 카운터 모듈의 설정한 트리거 위치를 확인 합니다.
    DWORD __stdcall AxcTriggerGetNotchPos(long lChannelNo, double* dbpLowerPos, double* dbpUpperPos);

    // 카운터 모듈의 트리거 출력을 강제로 합니다.
    // dwOutVal --> 0x00 : 트리거 출력 '0'
    // dwOutVal --> 0x01 : 트리거 출력 '1'
    DWORD __stdcall AxcTriggerSetOutput(long lChannelNo, DWORD dwOutVal);

    // 카운터 모듈의 상태를 확인합니다.
    // Bit '0' : Carry (카운터 현재치가 덧셈 펄스에 의해 카운터 상한치를 넘어 0로 바뀌었을 때 1스캔만 ON으로 합니다.)
    // Bit '1' : Borrow (카운터 현재치가 뺄셈 펄스에 의해 0을 넘어 카운터 상한치로 바뀌었을 때 1스캔만 ON으로 합니다.)
    // Bit '2' : Trigger output status
    // Bit '3' : Latch input status
    DWORD __stdcall AxcStatusGetChannel(long lChannelNo, DWORD* dwpChannelStatus);


    // SIO-CN2CH 전용 함수군
    //
    // 카운터 모듈의 위치 단위를 설정한다.
    // 실제 위치 이동량에 대한 펄스 갯수를 설정하는데,
    // ex) 1mm 이동에 1000가 필요하다면dMoveUnitPerPulse = 0.001로 입력하고,
    //     이후 모든 함수의 위치와 관련된 값을 mm 단위로 설정하면 된다.
    DWORD __stdcall AxcMotSetMoveUnitPerPulse(long lChannelNo, double dMoveUnitPerPulse);

    // 카운터 모듈의 위치 단위를 확인한다.
    DWORD __stdcall AxcMotGetMoveUnitPerPulse(long lChannelNo, double* dpMoveUnitPerPuls);

    // 카운터 모듈의 엔코더 입력 카운터를 반전 기능을 설정한다.
    // dwReverse --> 0x00 : 반전하지 않음.
    // dwReverse --> 0x01 : 반전.
    DWORD __stdcall AxcSignalSetEncReverse(long lChannelNo, DWORD dwReverse);

    // 카운터 모듈의 엔코더 입력 카운터를 반전 기능을 설정을 확인한다.
    DWORD __stdcall AxcSignalGetEncReverse(long lChannelNo, DWORD* dwpReverse);

    // 카운터 모듈의 Encoder 입력 신호를 선택한다.
    // dwSource -->  0x00 : 2(A/B)-Phase 신호.
    // dwSource -->  0x01 : Z-Phase 신호.(방향성 없음.)
    DWORD  __stdcall AxcSignalSetEncSource(long lChannelNo, DWORD dwSource);

    // 카운터 모듈의 Encoder 입력 신호 선택 설정을 확인한다.
    DWORD  __stdcall AxcSignalGetEncSource(long lChannelNo, DWORD* dwpSource);

    // 카운터 모듈의 트리거 출력 범위 중 하한 값을 설정한다.
    // 위치 주기 트리거 제품의 경우 위치 주기로 트리거 출력을 발생시킬 범위 중 하한 값을 설정한다.
    // 절대 위치 트리거 제품의 경우 Ram 시작 번지의 트리거 정보의 적용 기준 위치를 설정한다.
    // 단위 : AxcMotSetMoveUnitPerPulse로 설정한 단위.
    // Note : 하한값은 상한값보다 작은값을 설정하여야 합니다.
    DWORD  __stdcall AxcTriggerSetBlockLowerPos(long lChannelNo, double dLowerPosition);

    // 카운터 모듈의 트리거 출력 범위 중 하한 값을 확인한다.
    DWORD  __stdcall AxcTriggerGetBlockLowerPos(long lChannelNo, double* dpLowerPosition);

    // 카운터 모듈의 트리거 출력 범위 중 상한 값을 설정한다.
    // 위치 주기 트리거 제품의 경우 위치 주기로 트리거 출력을 발생시킬 범위 중 상한 값을 설정한다.
    // 절대 위치 트리거 제품의 경우 트리거 정보가 설정된 Ram 의 마지막 번지의 트리거 정보가 적용되는 위치로 사용된다.
    // 단위 : AxcMotSetMoveUnitPerPulse로 설정한 단위.
    // Note : 상한값은 하한값보다 큰값을 설정하여야 합니다.
    DWORD  __stdcall AxcTriggerSetBlockUpperPos(long lChannelNo, double dUpperPosition);
    // 카운터 모듈의 트리거 출력 범위 중 하한 값을 설정한다.
    DWORD  __stdcall AxcTriggerGetBlockUpperPos(long lChannelNo, double* dpUpperrPosition);

    // 카운터 모듈의 위치 주기 모드 트리거에 사용되는 위치 주기를 설정한다.
    // 단위 : AxcMotSetMoveUnitPerPulse로 설정한 단위.
    DWORD  __stdcall AxcTriggerSetPosPeriod(long lChannelNo, double dPeriod);

    // 카운터 모듈의 위치 주기 모드 트리거에 사용되는 위치 주기를 확인한다.
    DWORD  __stdcall AxcTriggerGetPosPeriod(long lChannelNo, double* dpPeriod);

    // 카운터 모듈의 위치 주기 모드 트리거 사용시 위치 증감에 대한 유효기능을 설정한다.
    // dwDirection -->  0x00 : 카운터의 증/감에 대하여 트리거 주기 마다 출력.
    // dwDirection -->  0x01 : 카운터가 증가 할때만 트리거 주기 마다 출력.
    // dwDirection -->  0x01 : 카운터가 감소 할때만 트리거 주기 마다 출력.
    DWORD  __stdcall AxcTriggerSetDirectionCheck(long lChannelNo, DWORD dwDirection);
    // 카운터 모듈의 위치 주기 모드 트리거 사용시 위치 증감에 대한 유효기능 설정을 확인한다.
    DWORD  __stdcall AxcTriggerGetDirectionCheck(long lChannelNo, DWORD* dwpDirection);

    // 카운터 모듈의 위치 주기 모드 트리거 기능의 범위, 위치 주기를 한번에 설정한다.
    // 위치 설정 단위 :  AxcMotSetMoveUnitPerPulse로 설정한 단위.
    DWORD  __stdcall AxcTriggerSetBlock(long lChannelNo, double dLower, double dUpper, double dABSod);

    // 카운터 모듈의 위치 주기 모드 트리거 기능의 범위, 위치 주기를 설정을 한번에 확인한다.
    DWORD  __stdcall AxcTriggerGetBlock(long lChannelNo, double *dpLower, double *dpUpper, double *dpABSod);

    // 카운터 모듈의 트리거 출력 펄스 폭을 설정한다.
    // 단위 : uSec
    DWORD  __stdcall AxcTriggerSetTime(long lChannelNo, double dTrigTime);

    // 카운터 모듈의 트리거 출력 펄스 폭 설정을 확인한다.
    DWORD  __stdcall AxcTriggerGetTime(long lChannelNo, double* dpTrigTime);

    // 카운터 모듈의 트리거 출력 펄스의 출력 레벨을 설정한다.
    // dwLevel -->  0x00 : 트리거 출력시 'Low' 레벨 출력.
    // dwLevel -->  0x01 : 트리거 출력시 'High' 레벨 출력.
    DWORD  __stdcall AxcTriggerSetLevel(long lChannelNo, DWORD dwLevel);
    // 카운터 모듈의 트리거 출력 펄스의 출력 레벨 설정을 확인한다.
    DWORD  __stdcall AxcTriggerGetLevel(long lChannelNo, DWORD* dwpLevel);

    // 카운터 모듈의 주파수 트리거 출력 기능에 필요한 주파수를 설정한다.
    // 단위 : Hz, 범위 : 1Hz ~ 500 kHz
    DWORD  __stdcall AxcTriggerSetFreq(long lChannelNo, DWORD dwFreqency);
    // 카운터 모듈의 주파수 트리거 출력 기능에 필요한 주파수를 설정을 확인한다.
    DWORD  __stdcall AxcTriggerGetFreq(long lChannelNo, DWORD* dwpFreqency);

    // 카운터 모듈의 지정 채널에 대한 범용 출력 값을 설정한다.
    // dwOutput 범위 : 0x00 ~ 0x0F, 각 채널당 4개의 범용 출력
    DWORD  __stdcall AxcSignalWriteOutput(long lChannelNo, DWORD dwOutput);

    // 카운터 모듈의 지정 채널에 대한 범용 출력 값을 확인한다.
    DWORD  __stdcall AxcSignalReadOutput(long lChannelNo, DWORD* dwpOutput);

    // 카운터 모듈의 지정 채널에 대한 범용 출력 값을 비트 별로 설정한다.
    // lBitNo 범위 : 0 ~ 3, 각 채널당 4개의 범용 출력
    DWORD  __stdcall AxcSignalWriteOutputBit(long lChannelNo, long lBitNo, DWORD uOnOff);
    // 카운터 모듈의 지정 채널에 대한 범용 출력 값을 비트 별로 확인 한다.
    // lBitNo 범위 : 0 ~ 3
    DWORD  __stdcall AxcSignalReadOutputBit(long lChannelNo,long lBitNo, DWORD *upOnOff);

    // 카운터 모듈의 지정 채널에 대한 범용 입력 값을 확인한다.
    DWORD  __stdcall AxcSignalReadInput(long lChannelNo, DWORD* dwpInput);

    // 카운터 모듈의 지정 채널에 대한 범용 입력 값을 비트 별로 확인 한다.
    // lBitNo 범위 : 0 ~ 3
    DWORD  __stdcall AxcSignalReadInputBit(long lChannelNo, long lBitNo, DWORD *upOnOff);

    // 카운터 모듈의 트리거 출력을 활성화 한다.
    // 현재 설정된 기능에 따라 트리거 출력이 최종적으로 출력할 것인지 설정한다.
    DWORD  __stdcall AxcTriggerSetEnable(long lChannelNo, DWORD dwUsage);

    // 카운터 모듈의 트리거 출력 활설화 설정 내용을 확인하다.
    DWORD  __stdcall AxcTriggerGetEnable(long lChannelNo, DWORD* dwpUsage);

    // 카운터 모듈의 절대위치 트리거 기능을 위해 설정된 RAM 내용을 확인한다.
    // dwAddr 범위 : 0x0000 ~ 0x1FFFF;
    DWORD  __stdcall AxcTriggerReadAbsRamData(long lChannelNo, DWORD dwAddr, DWORD* dwpData);

    // 카운터 모듈의 절대위치 트리거 기능을 위해 필요한 RAM 내용을 설정한다.
    // dwAddr 범위 : 0x0000 ~ 0x1FFFF;
    DWORD  __stdcall AxcTriggerWriteAbsRamData(long lChannelNo, DWORD dwAddr, DWORD dwData);

    // 카운터 모듈의 절대위치 트리거 기능을 위해 필요한 RAM 내용을 한번에 설정한다.
    // dwTrigNum 범위 : ~ 0x20000  *RTEX CNT2 의 경우 0x200* 
    // dwDirection --> 0x0 : 하한 트리거 위치에 대한 트리거 정보 부터 입력. 위치가 증가하는 방향으로 트리거 출력시 사용.
    // dwDirection --> 0x1 : 상한 카운터에 대한 트리거 정보 부터 입력. 위치가 감소하는 방향으로 트리거 출력시 사용.
    DWORD  __stdcall AxcTriggerSetAbs(long lChannelNo, DWORD dwTrigNum, DWORD* dwTrigPos, DWORD dwDirection);

    // 카운터 모듈의 절대위치 트리거 기능을 위해 필요한 RAM 내용을 한번에 설정한다.
    // dwTrigNum 범위 : ~ 0x20000  *RTEX CNT2 의 경우 0x200* 
    // dwDirection --> 0x0 : 하한 트리거 위치에 대한 트리거 정보 부터 입력. 위치가 증가하는 방향으로 트리거 출력시 사용.
    // dwDirection --> 0x1 : 상한 카운터에 대한 트리거 정보 부터 입력. 위치가 감소하는 방향으로 트리거 출력시 사용.
	// dTrigPos : 카운터 모듈의 트리거 Pos를 double 형으로 사용
	DWORD  __stdcall AxcTriggerSetAbsDouble(long lChannelNo, DWORD dwTrigNum, double* dTrigPos, DWORD dwDirection);


#ifdef __cplusplus
}
#endif    //__cplusplus

#endif    //__AXT_AXC_H__
