#ifndef __AXT_DAXM_H__
#define __AXT_DAXM_H__

//#include "AXHS.h"
#include "../../AXL(Library)/C, C++/AXHS.h"

typedef DWORD    PASCAL EXPORT funcAxmInfoGetAxis(long lAxisNo, long *lpBoardNo, long *lpModulePos, DWORD *upModuleID);
typedef DWORD    PASCAL EXPORT funcAxmInfoIsMotionModule(DWORD *upStatus);
typedef DWORD    PASCAL EXPORT funcAxmInfoIsInvalidAxisNo(long lAxisNo);
typedef DWORD    PASCAL EXPORT funcAxmInfoGetAxisStatus(long lAxisNo);
typedef DWORD    PASCAL EXPORT funcAxmInfoGetAxisCount(long *lpAxisCount);
typedef DWORD    PASCAL EXPORT funcAxmInfoGetFirstAxisNo(long lBoardNo, long lModulePos, long *lpAxisNo);

typedef DWORD    PASCAL EXPORT funcAxmVirtualSetAxisNoMap(long lRealAxisNo, long lVirtualAxisNo);
typedef DWORD    PASCAL EXPORT funcAxmVirtualGetAxisNoMap(long lRealAxisNo, long *lpVirtualAxisNo);
typedef DWORD    PASCAL EXPORT funcAxmVirtualSetMultiAxisNoMap(long lSize, long *lpRealAxesNo, long *lpVirtualAxesNo);
typedef DWORD    PASCAL EXPORT funcAxmVirtualGetMultiAxisNoMap(long lSize, long *lpRealAxesNo, long *lpVirtualAxesNo);
typedef DWORD    PASCAL EXPORT funcAxmVirtualResetAxisMap();

typedef DWORD    PASCAL EXPORT funcAxmInterruptSetAxis(long lAxisNo, HWND hWnd, DWORD uMessage, AXT_INTERRUPT_PROC pProc, HANDLE *pEvent);
typedef DWORD    PASCAL EXPORT funcAxmInterruptSetAxisEnable(long lAxisNo, DWORD uUse);
typedef DWORD    PASCAL EXPORT funcAxmInterruptGetAxisEnable(long lAxisNo, DWORD *upUse);
typedef DWORD    PASCAL EXPORT funcAxmInterruptRead(long *lpAxisNo, DWORD *upFlag);
typedef DWORD    PASCAL EXPORT funcAxmInterruptReadAxisFlag(long lAxisNo, long lBank, DWORD *upFlag);
typedef DWORD    PASCAL EXPORT funcAxmInterruptSetUserEnable(long lAxisNo, long lBank, DWORD uInterruptNum);
typedef DWORD    PASCAL EXPORT funcAxmInterruptGetUserEnable(long lAxisNo, long lBank, DWORD *upInterruptNum);

typedef DWORD    PASCAL EXPORT funcAxmMotLoadParaAll(char *szFilePath);
typedef DWORD    PASCAL EXPORT funcAxmMotSaveParaAll(char *szFilePath);
typedef DWORD    PASCAL EXPORT funcAxmMotSetParaLoad(long lAxisNo, double dInitPos, double dInitVel, double dInitAccel, double dInitDecel);    
typedef DWORD    PASCAL EXPORT funcAxmMotGetParaLoad(long lAxisNo, double *dpInitPos, double *dpInitVel, double *dpInitAccel, double *dpInitDecel);    
typedef DWORD    PASCAL EXPORT funcAxmMotSetPulseOutMethod(long lAxisNo, DWORD uMethod);
typedef DWORD    PASCAL EXPORT funcAxmMotGetPulseOutMethod(long lAxisNo, DWORD *upMethod);
typedef DWORD    PASCAL EXPORT funcAxmMotSetEncInputMethod(long lAxisNo, DWORD uMethod);
typedef DWORD    PASCAL EXPORT funcAxmMotGetEncInputMethod(long lAxisNo, DWORD *upMethod);
typedef DWORD    PASCAL EXPORT funcAxmMotSetMoveUnitPerPulse(long lAxisNo, double dUnit, long lPulse);
typedef DWORD    PASCAL EXPORT funcAxmMotGetMoveUnitPerPulse(long lAxisNo, double *dpUnit, long *lpPulse);
typedef DWORD    PASCAL EXPORT funcAxmMotSetDecelMode(long lAxisNo, DWORD uMethod);
typedef DWORD    PASCAL EXPORT funcAxmMotGetDecelMode(long lAxisNo, DWORD *upMethod);
typedef DWORD    PASCAL EXPORT funcAxmMotSetRemainPulse(long lAxisNo, DWORD uData);
typedef DWORD    PASCAL EXPORT funcAxmMotGetRemainPulse(long lAxisNo, DWORD *upData);
typedef DWORD    PASCAL EXPORT funcAxmMotSetMaxVel(long lAxisNo, double dVel);
typedef DWORD    PASCAL EXPORT funcAxmMotGetMaxVel(long lAxisNo, double *dpVel);
typedef DWORD    PASCAL EXPORT funcAxmMotSetAbsRelMode(long lAxisNo, DWORD uAbsRelMode);
typedef DWORD    PASCAL EXPORT funcAxmMotGetAbsRelMode(long lAxisNo, DWORD *upAbsRelMode);
typedef DWORD    PASCAL EXPORT funcAxmMotSetProfileMode(long lAxisNo, DWORD uProfileMode);
typedef DWORD    PASCAL EXPORT funcAxmMotGetProfileMode(long lAxisNo, DWORD *upProfileMode);
typedef DWORD    PASCAL EXPORT funcAxmMotSetAccelUnit(long lAxisNo, DWORD uAccelUnit);
typedef DWORD    PASCAL EXPORT funcAxmMotGetAccelUnit(long lAxisNo, DWORD *upAccelUnit);
typedef DWORD    PASCAL EXPORT funcAxmMotSetMinVel(long lAxisNo, double dMinVel);
typedef DWORD    PASCAL EXPORT funcAxmMotGetMinVel(long lAxisNo, double *dpMinVel);
typedef DWORD    PASCAL EXPORT funcAxmMotSetAccelJerk(long lAxisNo, double dAccelJerk);
typedef DWORD    PASCAL EXPORT funcAxmMotGetAccelJerk(long lAxisNo, double *dpAccelJerk);
typedef DWORD    PASCAL EXPORT funcAxmMotSetDecelJerk(long lAxisNo, double dDecelJerk);
typedef DWORD    PASCAL EXPORT funcAxmMotGetDecelJerk(long lAxisNo, double *dpDecelJerk);
typedef DWORD    PASCAL EXPORT funcAxmMotSetProfilePriority(long lAxisNo, DWORD uPriority);
typedef DWORD    PASCAL EXPORT funcAxmMotGetProfilePriority(long lAxisNo, DWORD *upPriority);

typedef DWORD    PASCAL EXPORT funcAxmSignalSetZphaseLevel(long lAxisNo, DWORD uLevel);
typedef DWORD    PASCAL EXPORT funcAxmSignalGetZphaseLevel(long lAxisNo, DWORD *upLevel);
typedef DWORD    PASCAL EXPORT funcAxmSignalSetServoOnLevel(long lAxisNo, DWORD uLevel);
typedef DWORD    PASCAL EXPORT funcAxmSignalGetServoOnLevel(long lAxisNo, DWORD *upLevel);
typedef DWORD    PASCAL EXPORT funcAxmSignalSetServoAlarmResetLevel(long lAxisNo, DWORD uLevel);
typedef DWORD    PASCAL EXPORT funcAxmSignalGetServoAlarmResetLevel(long lAxisNo, DWORD *upLevel);
typedef DWORD    PASCAL EXPORT funcAxmSignalSetInpos(long lAxisNo, DWORD uUse);
typedef DWORD    PASCAL EXPORT funcAxmSignalGetInpos(long lAxisNo, DWORD *upUse);
typedef DWORD    PASCAL EXPORT funcAxmSignalReadInpos(long lAxisNo, DWORD *upStatus);
typedef DWORD    PASCAL EXPORT funcAxmSignalSetServoAlarm(long lAxisNo, DWORD uUse);
typedef DWORD    PASCAL EXPORT funcAxmSignalGetServoAlarm(long lAxisNo, DWORD *upUse);
typedef DWORD    PASCAL EXPORT funcAxmSignalReadServoAlarm(long lAxisNo, DWORD *upStatus);

typedef DWORD    PASCAL EXPORT funcAxmSignalSetLimit(long lAxisNo, DWORD uStopMode, DWORD uPositiveLevel, DWORD uNegativeLevel);
typedef DWORD    PASCAL EXPORT funcAxmSignalGetLimit(long lAxisNo, DWORD *upStopMode, DWORD *upPositiveLevel, DWORD *upNegativeLevel);
typedef DWORD    PASCAL EXPORT funcAxmSignalReadLimit(long lAxisNo, DWORD *upPositiveStatus, DWORD *upNegativeStatus);
typedef DWORD    PASCAL EXPORT funcAxmSignalSetSoftLimit(long lAxisNo, DWORD uUse, DWORD uStopMode, DWORD uSelection, double dPositivePos, double dNegativePos);
typedef DWORD    PASCAL EXPORT funcAxmSignalGetSoftLimit(long lAxisNo, DWORD *upUse, DWORD *upStopMode, DWORD *upSelection, double *dpPositivePos, double *dpNegativePos);
typedef DWORD    PASCAL EXPORT funcAxmSignalSetStop(long lAxisNo, DWORD uStopMode, DWORD uLevel);
typedef DWORD    PASCAL EXPORT funcAxmSignalGetStop(long lAxisNo, DWORD *upStopMode, DWORD *upLevel);
typedef DWORD    PASCAL EXPORT funcAxmSignalReadStop(long lAxisNo, DWORD *upStatus);
typedef DWORD    PASCAL EXPORT funcAxmSignalServoOn(long lAxisNo, DWORD uOnOff);
typedef DWORD    PASCAL EXPORT funcAxmSignalIsServoOn(long lAxisNo, DWORD *upOnOff);
typedef DWORD    PASCAL EXPORT funcAxmSignalServoAlarmReset(long lAxisNo, DWORD uOnOff);
typedef DWORD    PASCAL EXPORT funcAxmSignalWriteOutput(long lAxisNo, DWORD uValue);
typedef DWORD    PASCAL EXPORT funcAxmSignalReadOutput(long lAxisNo, DWORD *upValue);
typedef DWORD    PASCAL EXPORT funcAxmSignalWriteOutputBit(long lAxisNo, long lBitNo, DWORD uOnOff);
typedef DWORD    PASCAL EXPORT funcAxmSignalReadOutputBit(long lAxisNo, long lBitNo, DWORD *upOnOff);
typedef DWORD    PASCAL EXPORT funcAxmSignalReadInput(long lAxisNo, DWORD *upValue);
typedef DWORD    PASCAL EXPORT funcAxmSignalReadInputBit(long lAxisNo, long lBitNo, DWORD *upOn);
typedef DWORD    PASCAL EXPORT funcAxmSignalSetFilterBandwidth(long lAxisNo, DWORD uSignal, double dBandwidthUsec);

typedef DWORD    PASCAL EXPORT funcAxmStatusReadInMotion(long lAxisNo, DWORD *upStatus);
typedef DWORD    PASCAL EXPORT funcAxmStatusReadDrivePulseCount(long lAxisNo, long *lpPulse);
typedef DWORD    PASCAL EXPORT funcAxmStatusReadMotion(long lAxisNo, DWORD *upStatus);
typedef DWORD    PASCAL EXPORT funcAxmStatusReadStop(long lAxisNo, DWORD *upStatus);
typedef DWORD    PASCAL EXPORT funcAxmStatusReadMechanical(long lAxisNo, DWORD *upStatus);
typedef DWORD    PASCAL EXPORT funcAxmStatusReadVel(long lAxisNo, double *dpVel);
typedef DWORD    PASCAL EXPORT funcAxmStatusReadPosError(long lAxisNo, double *dpError);
typedef DWORD    PASCAL EXPORT funcAxmStatusReadDriveDistance(long lAxisNo, double *dpUnit);
typedef DWORD    PASCAL EXPORT funcAxmStatusSetPosType(long lAxisNo, DWORD uPosType, double dPositivePos, double dNegativePos);
typedef DWORD    PASCAL EXPORT funcAxmStatusGetPosType(long lAxisNo, DWORD *upPosType, double *dpPositivePos, double *dpNegativePos);
typedef DWORD    PASCAL EXPORT funcAxmStatusSetAbsOrgOffset(long lAxisNo, double dOrgOffsetPos);
typedef DWORD    PASCAL EXPORT funcAxmStatusSetActPos(long lAxisNo, double dPos);
typedef DWORD    PASCAL EXPORT funcAxmStatusGetActPos(long lAxisNo, double *dpPos);
typedef DWORD    PASCAL EXPORT funcAxmStatusSetCmdPos(long lAxisNo, double dPos);
typedef DWORD    PASCAL EXPORT funcAxmStatusGetCmdPos(long lAxisNo, double *dpPos);
typedef DWORD    PASCAL EXPORT funcAxmStatusSetPosMatch(long lAxisNo, double dPos);
typedef DWORD    PASCAL EXPORT funcAxmStatusReadMotionInfo(long lAxisNo, PMOTION_INFO pMI);
typedef DWORD    PASCAL EXPORT funcAxmStatusRequestServoAlarm(long lAxisNo);
typedef DWORD    PASCAL EXPORT funcAxmStatusReadServoAlarm(long lAxisNo, DWORD uReturnMode, DWORD *upAlarmCode);
typedef DWORD    PASCAL EXPORT funcAxmStatusGetServoAlarmString(long lAxisNo, DWORD uAlarmCode, long lAlarmStringSize, char *szAlarmString);
typedef DWORD    PASCAL EXPORT funcAxmStatusRequestServoAlarmHistory(long lAxisNo);
typedef DWORD    PASCAL EXPORT funcAxmStatusReadServoAlarmHistory(long lAxisNo, DWORD uReturnMode, long *lpCount, DWORD *upAlarmCode);
typedef DWORD    PASCAL EXPORT funcAxmStatusClearServoAlarmHistory(long lAxisNo);

typedef DWORD    PASCAL EXPORT funcAxmHomeSetSignalLevel(long lAxisNo, DWORD uLevel);
typedef DWORD    PASCAL EXPORT funcAxmHomeGetSignalLevel(long lAxisNo, DWORD *upLevel);
typedef DWORD    PASCAL EXPORT funcAxmHomeReadSignal(long lAxisNo, DWORD *upStatus);
typedef DWORD    PASCAL EXPORT funcAxmHomeSetMethod(long lAxisNo, long lHmDir, DWORD uHomeSignal, DWORD uZphas, double dHomeClrTime, double dHomeOffset);
typedef DWORD    PASCAL EXPORT funcAxmHomeGetMethod(long lAxisNo, long *lpHmDir, DWORD *upHomeSignal, DWORD *upZphas, double *dpHomeClrTime, double *dpHomeOffset);
typedef DWORD    PASCAL EXPORT funcAxmHomeSetFineAdjust(long lAxisNo, long lHmDir, DWORD uHomeSignal, DWORD uZphas, double dHomeClrTime, double dHomeOffset);
typedef DWORD    PASCAL EXPORT funcAxmHomeGetFineAdjust(long lAxisNo, long *lpHmDir, DWORD *upHomeSignal, DWORD *upZphas, double *dpHomeClrTime, double *dpHomeOffset);
typedef DWORD    PASCAL EXPORT funcAxmHomeSetVel(long lAxisNo, double dVelFirst, double dVelSecond, double dVelThird, double dVelLast, double dAccFirst, double dAccSecond);
typedef DWORD    PASCAL EXPORT funcAxmHomeGetVel(long lAxisNo, double *dpVelFirst, double *dpVelSecond, double *dpVelThird, double *dpVelLast, double *dpAccFirst, double *dpAccSecond);
typedef DWORD    PASCAL EXPORT funcAxmHomeSetStart(long lAxisNo);
typedef DWORD    PASCAL EXPORT funcAxmHomeSetResult(long lAxisNo, DWORD uHomeResult);
typedef DWORD    PASCAL EXPORT funcAxmHomeGetResult(long lAxisNo, DWORD *upHomeResult);
typedef DWORD    PASCAL EXPORT funcAxmHomeGetRate(long lAxisNo, DWORD *upHomeMainStepNumber, DWORD *upHomeStepNumber);

typedef DWORD    PASCAL EXPORT funcAxmMoveStartPos(long lAxisNo, double dPos, double dVel, double dAccel, double dDecel);
typedef DWORD    PASCAL EXPORT funcAxmMovePos(long lAxisNo, double dPos, double dVel, double dAccel, double dDecel);
typedef DWORD    PASCAL EXPORT funcAxmMoveVel(long lAxisNo, double dVel, double dAccel, double dDecel);
typedef DWORD    PASCAL EXPORT funcAxmMoveStartMultiVel(long lArraySize, long *lpAxesNo, double *dpVel, double *dpAccel, double *dpDecel);
typedef DWORD    PASCAL EXPORT funcAxmMoveStartMultiVelEx(long lArraySize, long *lpAxesNo, double *dpVel, double *dpAccel, double *dpDecel, DWORD dwSyncMode);
typedef DWORD    PASCAL EXPORT funcAxmMoveStartLineVel(long lArraySize, long *lpAxesNo, double *dpDis, double dVel, double dAccel, double dDecel);
typedef DWORD    PASCAL EXPORT funcAxmMoveSignalSearch(long lAxisNo, double dVel, double dAccel, long lDetectSignal, long lSignalEdge, long lSignalMethod);
typedef DWORD    PASCAL EXPORT funcAxmMoveSignalCapture(long lAxisNo, double dVel, double dAccel, long lDetectSignal, long lSignalEdge, long lTarget, long lSignalMethod);
typedef DWORD    PASCAL EXPORT funcAxmMoveGetCapturePos(long lAxisNo, double *dpCapPotition);
typedef DWORD    PASCAL EXPORT funcAxmMoveStartMultiPos(long lArraySize, long *lpAxisNo, double *dpPos, double *dpVel, double *dpAccel, double *dpDecel);
typedef DWORD    PASCAL EXPORT funcAxmMoveMultiPos(long lArraySize, long *lpAxisNo, double *dpPos, double *dpVel, double *dpAccel, double *dpDecel);

typedef DWORD    PASCAL EXPORT funcAxmMoveStartTorque(long lAxisNo, double dTorque, double dVel, DWORD dwAccFilterSel, DWORD dwGainSel, DWORD dwSpdLoopSel);
typedef DWORD    PASCAL EXPORT funcAxmMoveTorqueStop(long lAxisNo, DWORD dwMethod);

typedef DWORD    PASCAL EXPORT funcAxmMoveStartPosWithList(long lAxisNo, double dPosition, double *dpVel, double *dpAccel, double *dpDecel, long lListNum);
typedef DWORD    PASCAL EXPORT funcAxmMoveStartPosWithPosEvent(long lAxisNo, double dPos, double dVel, double dAccel, double dDecel, long lEventAxisNo, double dComparePosition, DWORD uPositionSource);

typedef DWORD    PASCAL EXPORT funcAxmMoveStop(long lAxisNo, double dDecel);
typedef DWORD    PASCAL EXPORT funcAxmMoveEStop(long lAxisNo);
typedef DWORD    PASCAL EXPORT funcAxmMoveSStop(long lAxisNo);

typedef DWORD    PASCAL EXPORT funcAxmOverridePos(long lAxisNo, double dOverridePos);
typedef DWORD    PASCAL EXPORT funcAxmOverrideSetMaxVel(long lAxisNo, double dOverrideMaxVel);
typedef DWORD    PASCAL EXPORT funcAxmOverrideVel(long lAxisNo, double dOverrideVel);
typedef DWORD    PASCAL EXPORT funcAxmOverrideAccelVelDecel(long lAxisNo, double dOverrideVelocity, double dMaxAccel, double dMaxDecel);
typedef DWORD    PASCAL EXPORT funcAxmOverrideVelAtPos(long lAxisNo, double dPos, double dVel, double dAccel, double dDecel,double dOverridePos, double dOverrideVel, long lTarget);
typedef DWORD    PASCAL EXPORT funcAxmOverrideVelAtMultiPos(long lAxisNo, double dPos, double dVel, double dAccel, double dDecel, long lArraySize, double* dpOverridePos, double* dpOverrideVel, long lTarget, DWORD dwOverrideMode);

typedef DWORD    PASCAL EXPORT funcAxmLinkSetMode(long lMasterAxisNo, long lSlaveAxisNo, double dSlaveRatio);
typedef DWORD    PASCAL EXPORT funcAxmLinkGetMode(long lMasterAxisNo, long *lpSlaveAxisNo, double *dpGearRatio);
typedef DWORD    PASCAL EXPORT funcAxmLinkResetMode(long lMasterAxisNo);

typedef DWORD    PASCAL EXPORT funcAxmGantrySetEnable(long lMasterAxisNo, long lSlaveAxisNo, DWORD uSlHomeUse, double dSlOffset, double dSlOffsetRange);
typedef DWORD    PASCAL EXPORT funcAxmGantryGetEnable(long lMasterAxisNo, DWORD *upSlHomeUse, double *dpSlOffset, double *dpSlORange, DWORD *upGatryOn);
typedef DWORD    PASCAL EXPORT funcAxmGantrySetDisable(long lMasterAxisNo, long lSlaveAxisNo);

typedef DWORD    PASCAL EXPORT funcAxmLineMove(long lCoord, double *dpEndPos, double dVel, double dAccel, double dDecel);

typedef DWORD    PASCAL EXPORT funcAxmCircleCenterMove(long lCoord, long *lAxisNo, double *dCenterPos, double *dEndPos, double dVel, double dAccel, double dDecel, DWORD uCWDir);
typedef DWORD    PASCAL EXPORT funcAxmCirclePointMove(long lCoord, long *lAxisNo, double *dMidPos, double *dEndPos, double dVel, double dAccel, double dDecel, long lArcCircle);
typedef DWORD    PASCAL EXPORT funcAxmCircleRadiusMove(long lCoord, long *lAxisNo, double dRadius, double *dEndPos, double dVel, double dAccel, double dDecel, DWORD uCWDir, DWORD uShortDistance);
typedef DWORD    PASCAL EXPORT funcAxmCircleAngleMove(long lCoord, long *lAxisNo, double *dCenterPos, double dAngle, double dVel, double dAccel, double dDecel, DWORD uCWDir);

typedef DWORD    PASCAL EXPORT funcAxmContiSetAxisMap(long lCoord, long lSize, long *lpAxesNo);
typedef DWORD    PASCAL EXPORT funcAxmContiGetAxisMap(long lCoord, long *lpSize, long *lpAxesNo);
typedef DWORD    PASCAL EXPORT funcAxmContiSetAbsRelMode(long lCoord, DWORD uAbsRelMode);
typedef DWORD    PASCAL EXPORT funcAxmContiGetAbsRelMode(long lCoord, DWORD *upAbsRelMode);
typedef DWORD    PASCAL EXPORT funcAxmContiReadFree(long lCoord, DWORD *upQueueFree);
typedef DWORD    PASCAL EXPORT funcAxmContiReadIndex(long lCoord, long *lpQueueIndex);
typedef DWORD    PASCAL EXPORT funcAxmContiWriteClear(long lCoord);
typedef DWORD    PASCAL EXPORT funcAxmContiBeginNode(long lCoord);
typedef DWORD    PASCAL EXPORT funcAxmContiEndNode(long lCoord);
typedef DWORD    PASCAL EXPORT funcAxmContiStart(long lCoord, DWORD dwProfileset, long lAngle); 
typedef DWORD    PASCAL EXPORT funcAxmContiIsMotion(long lCoord, DWORD *upInMotion);
typedef DWORD    PASCAL EXPORT funcAxmContiGetNodeNum(long lCoord, long *lpNodeNum);
typedef DWORD    PASCAL EXPORT funcAxmContiGetTotalNodeNum(long lCoord, long *lpNodeNum);

typedef DWORD    PASCAL EXPORT funcAxmTriggerSetTimeLevel(long lAxisNo, double dTrigTime, DWORD uTriggerLevel, DWORD uSelect, DWORD uInterrupt);
typedef DWORD    PASCAL EXPORT funcAxmTriggerGetTimeLevel(long lAxisNo, double *dpTrigTime, DWORD *upTriggerLevel, DWORD *upSelect, DWORD *upInterrupt);
typedef DWORD    PASCAL EXPORT funcAxmTriggerSetAbsPeriod(long lAxisNo, DWORD uMethod, double dPos);
typedef DWORD    PASCAL EXPORT funcAxmTriggerGetAbsPeriod(long lAxisNo, DWORD *upMethod, double *dpPos);
typedef DWORD    PASCAL EXPORT funcAxmTriggerSetBlock(long lAxisNo, double dStartPos, double dEndPos, double dPeriodPos);
typedef DWORD    PASCAL EXPORT funcAxmTriggerGetBlock(long lAxisNo, double *dpStartPos, double *dpEndPos, double *dpPeriodPos);
typedef DWORD    PASCAL EXPORT funcAxmTriggerOneShot(long lAxisNo);
typedef DWORD    PASCAL EXPORT funcAxmTriggerSetTimerOneshot(long lAxisNo, long lmSec);
typedef DWORD    PASCAL EXPORT funcAxmTriggerOnlyAbs(long lAxisNo,long lTrigNum, double* dpTrigPos);
typedef DWORD    PASCAL EXPORT funcAxmTriggerSetReset(long lAxisNo); 

typedef DWORD    PASCAL EXPORT funcAxmCrcSetMaskLevel(long lAxisNo, DWORD uLevel, DWORD uMethod);
typedef DWORD    PASCAL EXPORT funcAxmCrcGetMaskLevel(long lAxisNo, DWORD *upLevel, DWORD *upMethod);
typedef DWORD    PASCAL EXPORT funcAxmCrcSetOutput(long lAxisNo, DWORD uOnOff);
typedef DWORD    PASCAL EXPORT funcAxmCrcGetOutput(long lAxisNo, DWORD *upOnOff);

typedef DWORD    PASCAL EXPORT funcAxmMPGSetEnable(long lAxisNo, long lInputMethod, long lDriveMode, double dMPGPos, double dVel, double dAccel);
typedef DWORD    PASCAL EXPORT funcAxmMPGGetEnable(long lAxisNo, long *lpInputMethod, long *lpDriveMode, double *dpMPGPos, double *dpVel, double *dAccel);
typedef DWORD    PASCAL EXPORT funcAxmMPGSetRatio(long lAxisNo, DWORD uMPGnumerator, DWORD uMPGdenominator);
typedef DWORD    PASCAL EXPORT funcAxmMPGGetRatio(long lAxisNo, DWORD *upMPGnumerator, DWORD *upMPGdenominator);
typedef DWORD    PASCAL EXPORT funcAxmMPGReset(long lAxisNo);

typedef DWORD    PASCAL EXPORT funcAxmHelixCenterMove(long lCoord, double dCenterXPos, double dCenterYPos, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dAccel, double dDecel, DWORD uCWDir);
typedef DWORD    PASCAL EXPORT funcAxmHelixPointMove(long lCoord, double dMidXPos, double dMidYPos, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dAccel, double dDecel);
typedef DWORD    PASCAL EXPORT funcAxmHelixRadiusMove(long lCoord, double dRadius, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dAccel, double dDecel, DWORD uCWDir, DWORD uShortDistance);
typedef DWORD    PASCAL EXPORT funcAxmHelixAngleMove(long lCoord, double dCenterXPos, double dCenterYPos, double dAngle, double dZPos, double dVel, double dAccel, double dDecel, DWORD uCWDir);
typedef DWORD    PASCAL EXPORT funcAxmSplineWrite(long lCoord, long lPosSize, double *dpPosX, double *dpPosY, double dVel, double dAccel, double dDecel, double dPosZ, long lPointFactor);

typedef DWORD    PASCAL EXPORT funcAxmCompensationSet(long lAxisNo, long lNumEntry, double dStartPos, double *dpPosition, double *dpCorrection, DWORD uRollOver);
typedef DWORD    PASCAL EXPORT funcAxmCompensationGet(long lAxisNo, long *lpNumEntry, double *dpStartPos, double *dpPosition, double *dpCorrection, DWORD *upRollOver);
typedef DWORD    PASCAL EXPORT funcAxmCompensationEnable(long lAxisNo, DWORD uEnable);
typedef DWORD    PASCAL EXPORT funcAxmCompensationIsEnable(long lAxisNo, DWORD *upEnable);
typedef DWORD    PASCAL EXPORT funcAxmEcamSet(long lAxisNo, long lMasterAxis, long lNumEntry, double dMasterStartPos, double *dpMasterPos, double *dpSlavePos);
typedef DWORD    PASCAL EXPORT funcAxmEcamGet(long lAxisNo, long *lpMasterAxis, long *lpNumEntry, double *dpMasterStartPos, double *dpMasterPos, double *dpSlavePos);
typedef DWORD    PASCAL EXPORT funcAxmEcamEnableBySlave(long lAxisNo, DWORD uEnable);
typedef DWORD    PASCAL EXPORT funcAxmEcamIsSlaveEnable(long lAxisNo, DWORD *upEnable);
typedef DWORD    PASCAL EXPORT funcAxmEcamEnableByMaster(long lAxisNo, DWORD uEnable);

typedef DWORD    PASCAL EXPORT funcAxmStatusSetServoMonitor(long lAxisNo, DWORD dwSelMon, double dActionValue, DWORD dwAction);
typedef DWORD    PASCAL EXPORT funcAxmStatusGetServoMonitor(long lAxisNo, DWORD dwSelMon, double *dpActionValue, DWORD *dwpAction);
typedef DWORD    PASCAL EXPORT funcAxmStatusSetServoMonitorEnable(long lAxisNo, DWORD dwEnable);
typedef DWORD    PASCAL EXPORT funcAxmStatusGetServoMonitorEnable(long lAxisNo, DWORD *dwpEnable);
typedef DWORD    PASCAL EXPORT funcAxmStatusReadServoMonitorFlag(long lAxisNo, DWORD dwSelMon, DWORD *dwpMonitorFlag, double *dpMonitorValue);
typedef DWORD    PASCAL EXPORT funcAxmStatusReadServoMonitorValue(long lAxisNo, DWORD dwSelMon, double *dpMonitorValue);
typedef DWORD    PASCAL EXPORT funcAxmStatusSetReadServoLoadRatio(long lAxisNo, DWORD dwSelMon);
typedef DWORD    PASCAL EXPORT funcAxmStatusReadServoLoadRatio(long lAxisNo, double *dpMonitorValue);
typedef DWORD    PASCAL EXPORT funcAxmMotSetScaleCoeff(long lAxisNo, long lScaleCoeff);
typedef DWORD    PASCAL EXPORT funcAxmMotGetScaleCoeff(long lAxisNo, long *lpScaleCoeff);
typedef DWORD    PASCAL EXPORT funcAxmMoveSignalSearchEx(long lAxisNo, double dVel, double dAccel, long lDetectSignal, long lSignalEdge, long lSignalMethod);
typedef DWORD    PASCAL EXPORT funcAxmMoveToAbsPos(long lAxisNo, double dPos, double dVel, double dAccel, double dDecel);
typedef DWORD    PASCAL EXPORT funcAxmStatusReadVelEx(long lAxisNo, double *dpVel);
typedef DWORD    PASCAL EXPORT funcAxmGantrySetCompensationGain(long lMasterAxisNo, long lMasterGain, long lSlaveGain);
typedef DWORD    PASCAL EXPORT funcAxmGantryGetCompensationGain(long lMasterAxisNo, long *lpMasterGain, long *lpSlaveGain);
typedef DWORD    PASCAL EXPORT funcAxmMotSetElectricGearRatio(long lAxisNo, long lNumerator, long lDenominator);
typedef DWORD    PASCAL EXPORT funcAxmMotGetElectricGearRatio(long lAxisNo, long *lpNumerator, long *lpDenominator);
typedef DWORD    PASCAL EXPORT funcAxmMotSetTorqueLimit(long lAxisNo, double dbPluseDirTorqueLimit, double dbMinusDirTorqueLimit);
typedef DWORD    PASCAL EXPORT funcAxmMotGetTorqueLimit(long lAxisNo, double* dbpPluseDirTorqueLimit, double* dbpMinusDirTorqueLimit);
typedef DWORD    PASCAL EXPORT funcAxmOverridePosSetFunction(long lAxisNo, DWORD dwUsage, long lDecelPosRatio, double dReserved);
typedef DWORD    PASCAL EXPORT funcAxmOverridePosGetFunction(long lAxisNo, DWORD *dwpUsage, long *lpDecelPosRatio, double *dpReserved);

typedef DWORD    PASCAL EXPORT ServoCmdExecution(long lAxisNo, DWORD dwCommand, DWORD dwSize, DWORD *pdwExcData);
typedef DWORD    PASCAL EXPORT SignalSetInposRange(long lAxisNo, double dInposRange);
typedef DWORD    PASCAL EXPORT SignalGetInposRange(long lAxisNo, double *dpInposRange);
typedef DWORD    PASCAL EXPORT MotSetOverridePosMode(long lAxisNo, DWORD dwAbsRelMode);
typedef DWORD    PASCAL EXPORT MotGetOverridePosMode(long lAxisNo, DWORD *dwpAbsRelMode);
typedef DWORD    PASCAL EXPORT MotSetOverrideLinePosMode(long lCoordNo, DWORD dwAbsRelMode);
typedef DWORD    PASCAL EXPORT MotGetOverrideLinePosMode(long lCoordNo, DWORD *dwpAbsRelMode);
typedef DWORD    PASCAL EXPORT MoveStartPosEx(long lAxisNo, double dPos, double dVel, double dAccel, double dDecel, double dEndVel);
typedef DWORD    PASCAL EXPORT MovePosEx(long lAxisNo, double dPos, double dVel, double dAccel, double dDecel, double dEndVel);
typedef DWORD    PASCAL EXPORT MoveCoordStop(long lCoordNo, double dDecel); 
typedef DWORD    PASCAL EXPORT MoveCoordEStop(long lCoordNo);
typedef DWORD    PASCAL EXPORT MoveCoordSStop(long lCoordNo);
typedef DWORD    PASCAL EXPORT OverrideLinePos(long lCoordNo, double *dpOverridePos);
typedef DWORD    PASCAL EXPORT OverrideLineVel(long lCoordNo, double dOverrideVel, double *dpDistance);
typedef DWORD    PASCAL EXPORT OverrideLineAccelVelDecel(long lCoordNo, double dOverrideVelocity, double dMaxAccel, double dMaxDecel, double *dpDistance);
typedef DWORD    PASCAL EXPORT OverrideAccelVelDecelAtPos(long lAxisNo, double dPos, double dVel, double dAccel, double dDecel,double dOverridePos, double dOverrideVel, double dOverrideAccel, double dOverrideDecel, long lTarget);
typedef DWORD    PASCAL EXPORT EGearSet(long lMasterAxisNo, long lSize, long* lpSlaveAxisNo, double* dpGearRatio);
typedef DWORD    PASCAL EXPORT EGearGet(long lMasterAxisNo, long* lpSize, long* lpSlaveAxisNo, double* dpGearRatio);
typedef DWORD    PASCAL EXPORT EGearReset(long lMasterAxisNo);
typedef DWORD    PASCAL EXPORT EGearEnable(long lMasterAxisNo, DWORD dwEnable);
typedef DWORD    PASCAL EXPORT EGearIsEnable(long lMasterAxisNo, DWORD *dwpEnable);    
typedef DWORD    PASCAL EXPORT MotSetEndVel(long lAxisNo, double dEndVelocity);
typedef DWORD    PASCAL EXPORT MotGetEndVel(long lAxisNo, double *dpEndVelocity);

//---------------------------------------------------------//
extern funcAxmInfoGetAxis                       *AxmInfoGetAxis;
extern funcAxmInfoIsMotionModule                *AxmInfoIsMotionModule;
extern funcAxmInfoIsInvalidAxisNo               *AxmInfoIsInvalidAxisNo;
extern funcAxmInfoGetAxisStatus                 *AxmInfoGetAxisStatus;
extern funcAxmInfoGetAxisCount                  *AxmInfoGetAxisCount;
extern funcAxmInfoGetFirstAxisNo                *AxmInfoGetFirstAxisNo;

extern funcAxmVirtualSetAxisNoMap               *AxmVirtualSetAxisNoMap;
extern funcAxmVirtualGetAxisNoMap               *AxmVirtualGetAxisNoMap;
extern funcAxmVirtualSetMultiAxisNoMap          *AxmVirtualSetMultiAxisNoMap;
extern funcAxmVirtualGetMultiAxisNoMap          *AxmVirtualGetMultiAxisNoMap;
extern funcAxmVirtualResetAxisMap               *AxmVirtualResetAxisMap;

extern funcAxmInterruptSetAxis                  *AxmInterruptSetAxis;
extern funcAxmInterruptSetAxisEnable            *AxmInterruptSetAxisEnable;
extern funcAxmInterruptGetAxisEnable            *AxmInterruptGetAxisEnable;
extern funcAxmInterruptRead                     *AxmInterruptRead;
extern funcAxmInterruptReadAxisFlag             *AxmInterruptReadAxisFlag;
extern funcAxmInterruptSetUserEnable            *AxmInterruptSetUserEnable;
extern funcAxmInterruptGetUserEnable            *AxmInterruptGetUserEnable;

extern funcAxmMotLoadParaAll                    *AxmMotLoadParaAll;
extern funcAxmMotSaveParaAll                    *AxmMotSaveParaAll;
extern funcAxmMotSetParaLoad                    *AxmMotSetParaLoad;
extern funcAxmMotGetParaLoad                    *AxmMotGetParaLoad;
extern funcAxmMotSetPulseOutMethod              *AxmMotSetPulseOutMethod;
extern funcAxmMotGetPulseOutMethod              *AxmMotGetPulseOutMethod;
extern funcAxmMotSetEncInputMethod              *AxmMotSetEncInputMethod;
extern funcAxmMotGetEncInputMethod              *AxmMotGetEncInputMethod;
extern funcAxmMotSetMoveUnitPerPulse            *AxmMotSetMoveUnitPerPulse;
extern funcAxmMotGetMoveUnitPerPulse            *AxmMotGetMoveUnitPerPulse;
extern funcAxmMotSetDecelMode                   *AxmMotSetDecelMode;
extern funcAxmMotGetDecelMode                   *AxmMotGetDecelMode;
extern funcAxmMotSetRemainPulse                 *AxmMotSetRemainPulse;
extern funcAxmMotGetRemainPulse                 *AxmMotGetRemainPulse;
extern funcAxmMotSetMaxVel                      *AxmMotSetMaxVel;
extern funcAxmMotGetMaxVel                      *AxmMotGetMaxVel;
extern funcAxmMotSetAbsRelMode                  *AxmMotSetAbsRelMode;
extern funcAxmMotGetAbsRelMode                  *AxmMotGetAbsRelMode;
extern funcAxmMotSetProfileMode                 *AxmMotSetProfileMode;
extern funcAxmMotGetProfileMode                 *AxmMotGetProfileMode;
extern funcAxmMotSetAccelUnit                   *AxmMotSetAccelUnit;
extern funcAxmMotGetAccelUnit                   *AxmMotGetAccelUnit;
extern funcAxmMotSetMinVel                      *AxmMotSetMinVel;
extern funcAxmMotGetMinVel                      *AxmMotGetMinVel;
extern funcAxmMotSetAccelJerk                   *AxmMotSetAccelJerk;
extern funcAxmMotGetAccelJerk                   *AxmMotGetAccelJerk;
extern funcAxmMotSetDecelJerk                   *AxmMotSetDecelJerk;
extern funcAxmMotGetDecelJerk                   *AxmMotGetDecelJerk;
extern funcAxmMotSetProfilePriority             *AxmMotSetProfilePriority;
extern funcAxmMotGetProfilePriority             *AxmMotGetProfilePriority;

extern funcAxmSignalSetZphaseLevel              *AxmSignalSetZphaseLevel;
extern funcAxmSignalGetZphaseLevel              *AxmSignalGetZphaseLevel;
extern funcAxmSignalSetServoOnLevel             *AxmSignalSetServoOnLevel;
extern funcAxmSignalGetServoOnLevel             *AxmSignalGetServoOnLevel;
extern funcAxmSignalSetServoAlarmResetLevel     *AxmSignalSetServoAlarmResetLevel;
extern funcAxmSignalGetServoAlarmResetLevel     *AxmSignalGetServoAlarmResetLevel;
extern funcAxmSignalSetInpos                    *AxmSignalSetInpos;
extern funcAxmSignalGetInpos                    *AxmSignalGetInpos;
extern funcAxmSignalReadInpos                   *AxmSignalReadInpos;
extern funcAxmSignalSetServoAlarm               *AxmSignalSetServoAlarm;
extern funcAxmSignalGetServoAlarm               *AxmSignalGetServoAlarm;
extern funcAxmSignalReadServoAlarm              *AxmSignalReadServoAlarm;
extern funcAxmSignalSetLimit                    *AxmSignalSetLimit;
extern funcAxmSignalGetLimit                    *AxmSignalGetLimit;
extern funcAxmSignalReadLimit                   *AxmSignalReadLimit;
extern funcAxmSignalSetSoftLimit                *AxmSignalSetSoftLimit;
extern funcAxmSignalGetSoftLimit                *AxmSignalGetSoftLimit;
extern funcAxmSignalSetStop                     *AxmSignalSetStop;
extern funcAxmSignalGetStop                     *AxmSignalGetStop;
extern funcAxmSignalReadStop                    *AxmSignalReadStop;
extern funcAxmSignalServoOn                     *AxmSignalServoOn;
extern funcAxmSignalIsServoOn                   *AxmSignalIsServoOn;
extern funcAxmSignalServoAlarmReset             *AxmSignalServoAlarmReset;
extern funcAxmSignalWriteOutput                 *AxmSignalWriteOutput;
extern funcAxmSignalReadOutput                  *AxmSignalReadOutput;
extern funcAxmSignalWriteOutputBit              *AxmSignalWriteOutputBit;
extern funcAxmSignalReadOutputBit               *AxmSignalReadOutputBit;
extern funcAxmSignalReadInput                   *AxmSignalReadInput;
extern funcAxmSignalReadInputBit                *AxmSignalReadInputBit;
extern funcAxmSignalSetFilterBandwidth          *AxmSignalSetFilterBandwidth;

extern funcAxmStatusReadInMotion                *AxmStatusReadInMotion;
extern funcAxmStatusReadDrivePulseCount         *AxmStatusReadDrivePulseCount;
extern funcAxmStatusReadMotion                  *AxmStatusReadMotion;
extern funcAxmStatusReadStop                    *AxmStatusReadStop;
extern funcAxmStatusReadMechanical              *AxmStatusReadMechanical;
extern funcAxmStatusReadVel                     *AxmStatusReadVel;
extern funcAxmStatusReadPosError                *AxmStatusReadPosError;
extern funcAxmStatusReadDriveDistance           *AxmStatusReadDriveDistance;
extern funcAxmStatusSetPosType                  *AxmStatusSetPosType;
extern funcAxmStatusGetPosType                  *AxmStatusGetPosType;
extern funcAxmStatusSetAbsOrgOffset             *AxmStatusSetAbsOrgOffset;
extern funcAxmStatusSetActPos                   *AxmStatusSetActPos;
extern funcAxmStatusGetActPos                   *AxmStatusGetActPos;
extern funcAxmStatusSetCmdPos                   *AxmStatusSetCmdPos;
extern funcAxmStatusGetCmdPos                   *AxmStatusGetCmdPos;
extern funcAxmStatusSetPosMatch                 *AxmStatusSetPosMatch;
extern funcAxmStatusRequestServoAlarm           *AxmStatusRequestServoAlarm;
extern funcAxmStatusReadServoAlarm              *AxmStatusReadServoAlarm;
extern funcAxmStatusGetServoAlarmString         *AxmStatusGetServoAlarmString;
extern funcAxmStatusRequestServoAlarmHistory    *AxmStatusRequestServoAlarmHistory;
extern funcAxmStatusReadServoAlarmHistory       *AxmStatusReadServoAlarmHistory;
extern funcAxmStatusClearServoAlarmHistory      *AxmStatusClearServoAlarmHistory;

extern funcAxmHomeSetSignalLevel                *AxmHomeSetSignalLevel;
extern funcAxmHomeGetSignalLevel                *AxmHomeGetSignalLevel;
extern funcAxmHomeReadSignal                    *AxmHomeReadSignal;
extern funcAxmHomeSetMethod                     *AxmHomeSetMethod;
extern funcAxmHomeGetMethod                     *AxmHomeGetMethod;
extern funcAxmHomeSetFineAdjust                 *AxmHomeSetFineAdjust;
extern funcAxmHomeGetFineAdjust                 *AxmHomeGetFineAdjust;
extern funcAxmHomeSetVel                        *AxmHomeSetVel;
extern funcAxmHomeGetVel                        *AxmHomeGetVel;
extern funcAxmHomeSetStart                      *AxmHomeSetStart;
extern funcAxmHomeSetResult                     *AxmHomeSetResult;
extern funcAxmHomeGetResult                     *AxmHomeGetResult;
extern funcAxmHomeGetRate                       *AxmHomeGetRate;

extern funcAxmMoveStartPos                      *AxmMoveStartPos;
extern funcAxmMovePos                           *AxmMovePos;
extern funcAxmMoveVel                           *AxmMoveVel;
extern funcAxmMoveStartMultiVel                 *AxmMoveStartMultiVel;
extern funcAxmMoveStartMultiVelEx               *AxmMoveStartMultiVelEx;
extern funcAxmMoveStartLineVel                  *AxmMoveStartLineVel;
extern funcAxmMoveSignalSearch                  *AxmMoveSignalSearch;
extern funcAxmMoveSignalCapture                 *AxmMoveSignalCapture;
extern funcAxmMoveGetCapturePos                 *AxmMoveGetCapturePos;
extern funcAxmMoveStartMultiPos                 *AxmMoveStartMultiPos;
extern funcAxmMoveMultiPos                      *AxmMoveMultiPos;

extern funcAxmMoveStartTorque                   *AxmMoveStartTorque;
extern funcAxmMoveTorqueStop                    *AxmMoveTorqueStop;

extern funcAxmMoveStartPosWithList              *AxmMoveStartPosWithList;
extern funcAxmMoveStartPosWithPosEvent          *AxmMoveStartPosWithPosEvent ;

extern funcAxmMoveStop                          *AxmMoveStop;
extern funcAxmMoveEStop                         *AxmMoveEStop;
extern funcAxmMoveSStop                         *AxmMoveSStop;

extern funcAxmOverridePos                       *AxmOverridePos;
extern funcAxmOverrideSetMaxVel                 *AxmOverrideSetMaxVel;
extern funcAxmOverrideVel                       *AxmOverrideVel;
extern funcAxmOverrideAccelVelDecel             *AxmOverrideAccelVelDecel;
extern funcAxmOverrideVelAtPos                  *AxmOverrideVelAtPos;
extern funcAxmOverrideVelAtMultiPos             *AxmOverrideVelAtMultiPos;

extern funcAxmLinkSetMode                       *AxmLinkSetMode;
extern funcAxmLinkGetMode                       *AxmLinkGetMode;
extern funcAxmLinkResetMode                     *AxmLinkResetMode;

extern funcAxmGantrySetEnable                   *AxmGantrySetEnable;
extern funcAxmGantryGetEnable                   *AxmGantryGetEnable;
extern funcAxmGantrySetDisable                  *AxmGantrySetDisable;

extern funcAxmLineMove                          *AxmLineMove;

extern funcAxmCircleCenterMove                  *AxmCircleCenterMove;
extern funcAxmCirclePointMove                   *AxmCirclePointMove;
extern funcAxmCircleRadiusMove                  *AxmCircleRadiusMove;
extern funcAxmCircleAngleMove                   *AxmCircleAngleMove;

extern funcAxmContiSetAxisMap                   *AxmContiSetAxisMap;
extern funcAxmContiGetAxisMap                   *AxmContiGetAxisMap;
extern funcAxmContiSetAbsRelMode                *AxmContiSetAbsRelMode;
extern funcAxmContiGetAbsRelMode                *AxmContiGetAbsRelMode;
extern funcAxmContiReadFree                     *AxmContiReadFree;
extern funcAxmContiReadIndex                    *AxmContiReadIndex;
extern funcAxmContiWriteClear                   *AxmContiWriteClear;
extern funcAxmContiBeginNode                    *AxmContiBeginNode;
extern funcAxmContiEndNode                      *AxmContiEndNode;
extern funcAxmContiStart                        *AxmContiStart;
extern funcAxmContiIsMotion                     *AxmContiIsMotion;
extern funcAxmContiGetNodeNum                   *AxmContiGetNodeNum;
extern funcAxmContiGetTotalNodeNum              *AxmContiGetTotalNodeNum;

extern funcAxmTriggerSetTimeLevel               *AxmTriggerSetTimeLevel;
extern funcAxmTriggerGetTimeLevel               *AxmTriggerGetTimeLevel;
extern funcAxmTriggerSetAbsPeriod               *AxmTriggerSetAbsPeriod;
extern funcAxmTriggerGetAbsPeriod               *AxmTriggerGetAbsPeriod;
extern funcAxmTriggerSetBlock                   *AxmTriggerSetBlock;
extern funcAxmTriggerGetBlock                   *AxmTriggerGetBlock;
extern funcAxmTriggerOneShot                    *AxmTriggerOneShot;
extern funcAxmTriggerSetTimerOneshot            *AxmTriggerSetTimerOneshot;
extern funcAxmTriggerOnlyAbs                    *AxmTriggerOnlyAbs;
extern funcAxmTriggerSetReset                   *AxmTriggerSetReset;

extern funcAxmCrcSetMaskLevel                   *AxmCrcSetMaskLevel;
extern funcAxmCrcGetMaskLevel                   *AxmCrcGetMaskLevel;
extern funcAxmCrcSetOutput                      *AxmCrcSetOutput;
extern funcAxmCrcGetOutput                      *AxmCrcGetOutput;

extern funcAxmMPGSetEnable                      *AxmMPGSetEnable;
extern funcAxmMPGGetEnable                      *AxmMPGGetEnable;
extern funcAxmMPGSetRatio                       *AxmMPGSetRatio;
extern funcAxmMPGGetRatio                       *AxmMPGGetRatio;
extern funcAxmMPGReset                          *AxmMPGReset;

extern funcAxmHelixCenterMove                   *AxmHelixCenterMove;
extern funcAxmHelixPointMove                    *AxmHelixPointMove;
extern funcAxmHelixRadiusMove                   *AxmHelixRadiusMove;
extern funcAxmHelixAngleMove                    *AxmHelixAngleMove;

extern funcAxmSplineWrite                       *AxmSplineWrite;

extern funcAxmCompensationSet                   *AxmCompensationSet;
extern funcAxmCompensationGet                   *AxmCompensationGet;
extern funcAxmCompensationEnable                *AxmCompensationEnable;
extern funcAxmCompensationIsEnable              *AxmCompensationIsEnable; 

extern funcAxmEcamSet                           *AxmEcamSet;
extern funcAxmEcamGet                           *AxmEcamGet;
extern funcAxmEcamEnableBySlave                 *AxmEcamEnableBySlave;
extern funcAxmEcamIsSlaveEnable                 *AxmEcamIsSlaveEnable;
extern funcAxmEcamEnableByMaster                *AxmEcamEnableByMaster;

extern funcAxmStatusSetServoMonitor             *AxmStatusSetServoMonitor;
extern funcAxmStatusGetServoMonitor             *AxmStatusGetServoMonitor;
extern funcAxmStatusSetServoMonitorEnable       *AxmStatusSetServoMonitorEnable;
extern funcAxmStatusGetServoMonitorEnable       *AxmStatusGetServoMonitorEnable;
extern funcAxmStatusReadServoMonitorFlag        *AxmStatusReadServoMonitorFlag;
extern funcAxmStatusReadServoMonitorValue       *AxmStatusReadServoMonitorValue;
extern funcAxmStatusSetReadServoLoadRatio       *AxmStatusSetReadServoLoadRatio;
extern funcAxmStatusReadServoLoadRatio          *AxmStatusReadServoLoadRatio;
extern funcAxmMotSetScaleCoeff                  *AxmMotSetScaleCoeff;
extern funcAxmMotGetScaleCoeff                  *AxmMotGetScaleCoeff;
extern funcAxmMoveSignalSearchEx                *AxmMoveSignalSearchEx;
extern funcAxmMoveToAbsPos                      *AxmMoveToAbsPos;
extern funcAxmStatusReadVelEx                   *AxmStatusReadVelEx;
extern funcAxmGantrySetCompensationGain         *AxmGantrySetCompensationGain;
extern funcAxmGantryGetCompensationGain         *AxmGantryGetCompensationGain;

extern funcAxmMotSetElectricGearRatio           *AxmMotSetElectricGearRatio;
extern funcAxmMotGetElectricGearRatio           *AxmMotGetElectricGearRatio;
extern funcAxmMotSetTorqueLimit                 *AxmMotSetTorqueLimit;
extern funcAxmMotGetTorqueLimit                 *AxmMotGetTorqueLimit;
extern funcAxmOverridePosSetFunction            *AxmOverridePosSetFunction;
extern funcAxmOverridePosGetFunction            *AxmOverridePosGetFunction;

extern funcAxmServoCmdExecution                 *AxmServoCmdExecution;	
extern funcAxmSignalSetInposRange               *AxmSignalSetInposRange;
extern funcAxmSignalGetInposRange               *AxmSignalGetInposRange;
extern funcAxmMotSetOverridePosMode             *AxmMotSetOverridePosMode;
extern funcAxmMotGetOverridePosMode             *AxmMotGetOverridePosMode;
extern funcAxmMotSetOverrideLinePosMode         *AxmMotSetOverrideLinePosMode;
extern funcAxmMotGetOverrideLinePosMode         *AxmMotGetOverrideLinePosMode ;
extern funcAxmMoveStartPosEx                    *AxmMoveStartPosEx;
extern funcAxmMovePosEx                         *AxmMovePosEx;
extern funcAxmMoveCoordStop                     *AxmMoveCoordStop;
extern funcAxmMoveCoordEStop                    *AxmMoveCoordEStop;
extern funcAxmMoveCoordSStop                    *AxmMoveCoordSStop;
extern funcAxmOverrideLinePos                   *AxmOverrideLinePos;
extern funcAxmOverrideLineVel                   *AxmOverrideLineVel;
extern funcAxmOverrideLineAccelVelDecel         *AxmOverrideLineAccelVelDecel;
extern funcAxmOverrideAccelVelDecelAtPos        *AxmOverrideAccelVelDecelAtPos;
extern funcAxmEGearSet                          *AxmEGearSet;
extern funcAxmEGearGet                          *AxmEGearGet;
extern funcAxmEGearReset                        *AxmEGearReset;
extern funcAxmEGearEnable                       *AxmEGearEnable;
extern funcAxmEGearIsEnable                     *AxmEGearIsEnable;
extern funcAxmMotSetEndVel                      *AxmMotSetEndVel;
extern funcAxmMotGetEndVel                      *AxmMotGetEndVel;

BOOL LoadAXM();
BOOL FreeAXM();

#endif    __AXT_DAXM_H__
