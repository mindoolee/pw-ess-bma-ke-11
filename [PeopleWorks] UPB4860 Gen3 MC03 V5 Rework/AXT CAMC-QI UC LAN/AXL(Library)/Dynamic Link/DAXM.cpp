#include "stdafx.h"
#include "DAXM.h"

HINSTANCE    g_hAXM = NULL;

funcAxmInfoGetAxis                          *AxmInfoGetAxis;
funcAxmInfoIsMotionModule                   *AxmInfoIsMotionModule;
funcAxmInfoIsInvalidAxisNo                  *AxmInfoIsInvalidAxisNo;
funcAxmInfoGetAxisStatus                    *AxmInfoGetAxisStatus;
funcAxmInfoGetAxisCount                     *AxmInfoGetAxisCount;
funcAxmInfoGetFirstAxisNo                   *AxmInfoGetFirstAxisNo;

funcAxmVirtualSetAxisNoMap                  *AxmVirtualSetAxisNoMap;
funcAxmVirtualGetAxisNoMap                  *AxmVirtualGetAxisNoMap;
funcAxmVirtualSetMultiAxisNoMap             *AxmVirtualSetMultiAxisNoMap;
funcAxmVirtualGetMultiAxisNoMap             *AxmVirtualGetMultiAxisNoMap;
funcAxmVirtualResetAxisMap                  *AxmVirtualResetAxisMap;

funcAxmInterruptSetAxis                     *AxmInterruptSetAxis;
funcAxmInterruptSetAxisEnable               *AxmInterruptSetAxisEnable;
funcAxmInterruptGetAxisEnable               *AxmInterruptGetAxisEnable;
funcAxmInterruptRead                        *AxmInterruptRead;
funcAxmInterruptReadAxisFlag                *AxmInterruptReadAxisFlag;
funcAxmInterruptSetUserEnable               *AxmInterruptSetUserEnable;
funcAxmInterruptGetUserEnable               *AxmInterruptGetUserEnable;

funcAxmMotLoadParaAll                       *AxmMotLoadParaAll;
funcAxmMotSaveParaAll                       *AxmMotSaveParaAll;
funcAxmMotSetParaLoad                       *AxmMotSetParaLoad;
funcAxmMotGetParaLoad                       *AxmMotGetParaLoad;
funcAxmMotSetPulseOutMethod                 *AxmMotSetPulseOutMethod;
funcAxmMotGetPulseOutMethod                 *AxmMotGetPulseOutMethod;
funcAxmMotSetEncInputMethod                 *AxmMotSetEncInputMethod;
funcAxmMotGetEncInputMethod                 *AxmMotGetEncInputMethod;
funcAxmMotSetMoveUnitPerPulse               *AxmMotSetMoveUnitPerPulse;
funcAxmMotGetMoveUnitPerPulse               *AxmMotGetMoveUnitPerPulse;
funcAxmMotSetDecelMode                      *AxmMotSetDecelMode;
funcAxmMotGetDecelMode                      *AxmMotGetDecelMode;
funcAxmMotSetRemainPulse                    *AxmMotSetRemainPulse;
funcAxmMotGetRemainPulse                    *AxmMotGetRemainPulse;
funcAxmMotSetMaxVel                         *AxmMotSetMaxVel;
funcAxmMotGetMaxVel                         *AxmMotGetMaxVel;
funcAxmMotSetAbsRelMode                     *AxmMotSetAbsRelMode;
funcAxmMotGetAbsRelMode                     *AxmMotGetAbsRelMode;
funcAxmMotSetProfileMode                    *AxmMotSetProfileMode;
funcAxmMotGetProfileMode                    *AxmMotGetProfileMode;
funcAxmMotSetAccelUnit                      *AxmMotSetAccelUnit;
funcAxmMotGetAccelUnit                      *AxmMotGetAccelUnit;
funcAxmMotSetMinVel                         *AxmMotSetMinVel;
funcAxmMotGetMinVel                         *AxmMotGetMinVel;
funcAxmMotSetAccelJerk                      *AxmMotSetAccelJerk;
funcAxmMotGetAccelJerk                      *AxmMotGetAccelJerk;
funcAxmMotSetDecelJerk                      *AxmMotSetDecelJerk;
funcAxmMotGetDecelJerk                      *AxmMotGetDecelJerk;
funcAxmMotSetProfilePriority                *AxmMotSetProfilePriority;
funcAxmMotGetProfilePriority                *AxmMotGetProfilePriority;

funcAxmSignalSetZphaseLevel                 *AxmSignalSetZphaseLevel;
funcAxmSignalGetZphaseLevel                 *AxmSignalGetZphaseLevel;
funcAxmSignalSetServoOnLevel                *AxmSignalSetServoOnLevel;
funcAxmSignalGetServoOnLevel                *AxmSignalGetServoOnLevel;
funcAxmSignalSetServoAlarmResetLevel        *AxmSignalSetServoAlarmResetLevel;
funcAxmSignalGetServoAlarmResetLevel        *AxmSignalGetServoAlarmResetLevel;
funcAxmSignalSetInpos                       *AxmSignalSetInpos;
funcAxmSignalGetInpos                       *AxmSignalGetInpos;
funcAxmSignalReadInpos                      *AxmSignalReadInpos;
funcAxmSignalSetServoAlarm                  *AxmSignalSetServoAlarm;
funcAxmSignalGetServoAlarm                  *AxmSignalGetServoAlarm;
funcAxmSignalReadServoAlarm                 *AxmSignalReadServoAlarm;
funcAxmSignalSetLimit                       *AxmSignalSetLimit;
funcAxmSignalGetLimit                       *AxmSignalGetLimit;
funcAxmSignalReadLimit                      *AxmSignalReadLimit;
funcAxmSignalSetSoftLimit                   *AxmSignalSetSoftLimit;
funcAxmSignalGetSoftLimit                   *AxmSignalGetSoftLimit;

funcAxmSignalSetStop                        *AxmSignalSetStop;
funcAxmSignalGetStop                        *AxmSignalGetStop;
funcAxmSignalReadStop                       *AxmSignalReadStop;
funcAxmSignalServoOn                        *AxmSignalServoOn;
funcAxmSignalIsServoOn                      *AxmSignalIsServoOn;
funcAxmSignalServoAlarmReset                *AxmSignalServoAlarmReset;
funcAxmSignalWriteOutput                    *AxmSignalWriteOutput;
funcAxmSignalReadOutput                     *AxmSignalReadOutput;
funcAxmSignalWriteOutputBit                 *AxmSignalWriteOutputBit;
funcAxmSignalReadOutputBit                  *AxmSignalReadOutputBit;
funcAxmSignalReadInput                      *AxmSignalReadInput;
funcAxmSignalReadInputBit                   *AxmSignalReadInputBit;
funcAxmSignalSetFilterBandwidth             *AxmSignalSetFilterBandwidth;

funcAxmStatusReadInMotion                   *AxmStatusReadInMotion;
funcAxmStatusReadDrivePulseCount            *AxmStatusReadDrivePulseCount;
funcAxmStatusReadMotion                     *AxmStatusReadMotion;
funcAxmStatusReadStop                       *AxmStatusReadStop;
funcAxmStatusReadMechanical                 *AxmStatusReadMechanical;
funcAxmStatusReadVel                        *AxmStatusReadVel;
funcAxmStatusReadPosError                   *AxmStatusReadPosError;
funcAxmStatusReadDriveDistance              *AxmStatusReadDriveDistance;
funcAxmStatusSetPosType                     *AxmStatusSetPosType;
funcAxmStatusGetPosType                     *AxmStatusGetPosType;
funcAxmStatusSetAbsOrgOffset                *AxmStatusSetAbsOrgOffset;
funcAxmStatusSetActPos                      *AxmStatusSetActPos;
funcAxmStatusGetActPos                      *AxmStatusGetActPos;
funcAxmStatusSetCmdPos                      *AxmStatusSetCmdPos;
funcAxmStatusGetCmdPos                      *AxmStatusGetCmdPos;
funcAxmStatusSetPosMatch                    *AxmStatusSetPosMatch;
funcAxmStatusRequestServoAlarm              *AxmStatusRequestServoAlarm;
funcAxmStatusReadServoAlarm                 *AxmStatusReadServoAlarm;
funcAxmStatusGetServoAlarmString            *AxmStatusGetServoAlarmString;
funcAxmStatusRequestServoAlarmHistory       *AxmStatusRequestServoAlarmHistory; 
funcAxmStatusReadServoAlarmHistory          *AxmStatusReadServoAlarmHistory;
funcAxmStatusClearServoAlarmHistory         *AxmStatusClearServoAlarmHistory;

funcAxmHomeSetSignalLevel                   *AxmHomeSetSignalLevel;
funcAxmHomeGetSignalLevel                   *AxmHomeGetSignalLevel;
funcAxmHomeReadSignal                       *AxmHomeReadSignal;
funcAxmHomeSetMethod                        *AxmHomeSetMethod;
funcAxmHomeGetMethod                        *AxmHomeGetMethod;
funcAxmHomeSetFineAdjust                    *AxmHomeSetFineAdjust;
funcAxmHomeGetFineAdjust                    *AxmHomeGetFineAdjust;
funcAxmHomeSetVel                           *AxmHomeSetVel;
funcAxmHomeGetVel                           *AxmHomeGetVel;
funcAxmHomeSetStart                         *AxmHomeSetStart;
funcAxmHomeSetResult                        *AxmHomeSetResult;
funcAxmHomeGetResult                        *AxmHomeGetResult;
funcAxmHomeGetRate                          *AxmHomeGetRate;

funcAxmMoveStartPos                         *AxmMoveStartPos;
funcAxmMovePos                              *AxmMovePos;
funcAxmMoveVel                              *AxmMoveVel;
funcAxmMoveStartMultiVel                    *AxmMoveStartMultiVel;
funcAxmMoveStartMultiVelEx                  *AxmMoveStartMultiVelEx;
funcAxmMoveStartLineVel                     *AxmMoveStartLineVel;
funcAxmMoveSignalSearch                     *AxmMoveSignalSearch;
funcAxmMoveSignalCapture                    *AxmMoveSignalCapture;
funcAxmMoveGetCapturePos                    *AxmMoveGetCapturePos;
funcAxmMoveStartMultiPos                    *AxmMoveStartMultiPos;
funcAxmMoveMultiPos                         *AxmMoveMultiPos;

funcAxmMoveStartTorque                      *AxmMoveStartTorque;
funcAxmMoveTorqueStop                       *AxmMoveTorqueStop;

funcAxmMoveStartPosWithList                 *AxmMoveStartPosWithList;
funcAxmMoveStartPosWithPosEvent             *AxmMoveStartPosWithPosEvent;

funcAxmMoveStop                             *AxmMoveStop;
funcAxmMoveEStop                            *AxmMoveEStop;
funcAxmMoveSStop                            *AxmMoveSStop;

funcAxmOverridePos                          *AxmOverridePos;
funcAxmOverrideSetMaxVel                    *AxmOverrideSetMaxVel;
funcAxmOverrideVel                          *AxmOverrideVel;
funcAxmOverrideAccelVelDecel                *AxmOverrideAccelVelDecel;
funcAxmOverrideVelAtPos                     *AxmOverrideVelAtPos;
funcAxmOverrideVelAtMultiPos                *AxmOverrideVelAtMultiPos;

funcAxmLinkSetMode                          *AxmLinkSetMode;
funcAxmLinkGetMode                          *AxmLinkGetMode;
funcAxmLinkResetMode                        *AxmLinkResetMode;

funcAxmGantrySetEnable                      *AxmGantrySetEnable;
funcAxmGantryGetEnable                      *AxmGantryGetEnable;
funcAxmGantrySetDisable                     *AxmGantrySetDisable;

funcAxmLineMove                             *AxmLineMove;

funcAxmCircleCenterMove                     *AxmCircleCenterMove;
funcAxmCirclePointMove                      *AxmCirclePointMove;
funcAxmCircleRadiusMove                     *AxmCircleRadiusMove;
funcAxmCircleAngleMove                      *AxmCircleAngleMove;

funcAxmContiSetAxisMap                      *AxmContiSetAxisMap;
funcAxmContiGetAxisMap                      *AxmContiGetAxisMap;
funcAxmContiSetAbsRelMode                   *AxmContiSetAbsRelMode;
funcAxmContiGetAbsRelMode                   *AxmContiGetAbsRelMode;
funcAxmContiReadFree                        *AxmContiReadFree;
funcAxmContiReadIndex                       *AxmContiReadIndex;
funcAxmContiWriteClear                      *AxmContiWriteClear;
funcAxmContiBeginNode                       *AxmContiBeginNode;
funcAxmContiEndNode                         *AxmContiEndNode;
funcAxmContiStart                           *AxmContiStart;
funcAxmContiIsMotion                        *AxmContiIsMotion;
funcAxmContiGetNodeNum                      *AxmContiGetNodeNum;
funcAxmContiGetTotalNodeNum                 *AxmContiGetTotalNodeNum;

funcAxmTriggerSetTimeLevel                  *AxmTriggerSetTimeLevel;
funcAxmTriggerGetTimeLevel                  *AxmTriggerGetTimeLevel;
funcAxmTriggerSetAbsPeriod                  *AxmTriggerSetAbsPeriod;
funcAxmTriggerGetAbsPeriod                  *AxmTriggerGetAbsPeriod;
funcAxmTriggerSetBlock                      *AxmTriggerSetBlock;
funcAxmTriggerGetBlock                      *AxmTriggerGetBlock;
funcAxmTriggerOneShot                       *AxmTriggerOneShot;
funcAxmTriggerSetTimerOneshot               *AxmTriggerSetTimerOneshot;
funcAxmTriggerOnlyAbs                       *AxmTriggerOnlyAbs;
funcAxmTriggerSetReset                      *AxmTriggerSetReset;

funcAxmCrcSetMaskLevel                      *AxmCrcSetMaskLevel;
funcAxmCrcGetMaskLevel                      *AxmCrcGetMaskLevel;
funcAxmCrcSetOutput                         *AxmCrcSetOutput;
funcAxmCrcGetOutput                         *AxmCrcGetOutput;

funcAxmMPGSetEnable                         *AxmMPGSetEnable;
funcAxmMPGGetEnable                         *AxmMPGGetEnable;
funcAxmMPGSetRatio                          *AxmMPGSetRatio;
funcAxmMPGGetRatio                          *AxmMPGGetRatio;
funcAxmMPGReset                             *AxmMPGReset;

funcAxmHelixCenterMove                      *AxmHelixCenterMove;
funcAxmHelixPointMove                       *AxmHelixPointMove;
funcAxmHelixRadiusMove                      *AxmHelixRadiusMove;
funcAxmHelixAngleMove                       *AxmHelixAngleMove;

funcAxmSplineWrite                          *AxmSplineWrite;

funcAxmCompensationSet                      *AxmCompensationSet;
funcAxmCompensationGet                      *AxmCompensationGet;
funcAxmCompensationEnable                   *AxmCompensationEnable;
funcAxmCompensationIsEnable                 *AxmCompensationIsEnable; 

funcAxmEcamSet                              *AxmEcamSet;
funcAxmEcamGet                              *AxmEcamGet;
funcAxmEcamEnableBySlave                    *AxmEcamEnableBySlave;
funcAxmEcamIsSlaveEnable                    *AxmEcamIsSlaveEnable;
funcAxmEcamEnableByMaster                   *AxmEcamEnableByMaster;

funcAxmStatusSetServoMonitor                *AxmStatusSetServoMonitor;
funcAxmStatusGetServoMonitor                *AxmStatusGetServoMonitor;
funcAxmStatusSetServoMonitorEnable          *AxmStatusSetServoMonitorEnable;
funcAxmStatusGetServoMonitorEnable          *AxmStatusGetServoMonitorEnable;
funcAxmStatusReadServoMonitorFlag           *AxmStatusReadServoMonitorFlag;
funcAxmStatusReadServoMonitorValue          *AxmStatusReadServoMonitorValue;
funcAxmStatusSetReadServoLoadRatio          *AxmStatusSetReadServoLoadRatio;
funcAxmStatusReadServoLoadRatio             *AxmStatusReadServoLoadRatio;
funcAxmMotSetScaleCoeff                     *AxmMotSetScaleCoeff;
funcAxmMotGetScaleCoeff                     *AxmMotGetScaleCoeff;
funcAxmMoveSignalSearchEx                   *AxmMoveSignalSearchEx;
funcAxmMoveToAbsPos                         *AxmMoveToAbsPos;
funcAxmStatusReadVelEx                      *AxmStatusReadVelEx;
funcAxmGantrySetCompensationGain            *AxmGantrySetCompensationGain;
funcAxmGantryGetCompensationGain            *AxmGantryGetCompensationGain;

funcAxmMotSetElectricGearRatio              *AxmMotSetElectricGearRatio;
funcAxmMotGetElectricGearRatio              *AxmMotGetElectricGearRatio;
funcAxmMotSetTorqueLimit                    *AxmMotSetTorqueLimit;
funcAxmMotGetTorqueLimit                    *AxmMotGetTorqueLimit;
funcAxmOverridePosSetFunction               *AxmOverridePosSetFunction;
funcAxmOverridePosGetFunction               *AxmOverridePosGetFunction;

funcAxmServoCmdExecution                     *AxmServoCmdExecution;	
funcAxmSignalSetInposRange                   *AxmSignalSetInposRange;
funcAxmSignalGetInposRange                   *AxmSignalGetInposRange;
funcAxmMotSetOverridePosMode                 *AxmMotSetOverridePosMode;
funcAxmMotGetOverridePosMode                 *AxmMotGetOverridePosMode;
funcAxmMotSetOverrideLinePosMode             *AxmMotSetOverrideLinePosMode;
funcAxmMotGetOverrideLinePosMode             *AxmMotGetOverrideLinePosMode ;
funcAxmMoveStartPosEx                        *AxmMoveStartPosEx;
funcAxmMovePosEx                             *AxmMovePosEx;
funcAxmMoveCoordStop                         *AxmMoveCoordStop;
funcAxmMoveCoordEStop                        *AxmMoveCoordEStop;
funcAxmMoveCoordSStop                        *AxmMoveCoordSStop;
funcAxmOverrideLinePos                       *AxmOverrideLinePos;
funcAxmOverrideLineVel                       *AxmOverrideLineVel;
funcAxmOverrideLineAccelVelDecel             *AxmOverrideLineAccelVelDecel;
funcAxmOverrideAccelVelDecelAtPos            *AxmOverrideAccelVelDecelAtPos;
funcAxmEGearSet                              *AxmEGearSet;
funcAxmEGearGet                              *AxmEGearGet;
funcAxmEGearReset                            *AxmEGearReset;
funcAxmEGearEnable                           *AxmEGearEnable;
funcAxmEGearIsEnable                         *AxmEGearIsEnable;
funcAxmMotSetEndVel                          *AxmMotSetEndVel;
funcAxmMotGetEndVel                          *AxmMotGetEndVel;

BOOL LoadAXM()
{
    g_hAXM    = LoadLibrary("Axl.dll");
    if (g_hAXM)
    {
        AxmInfoGetAxis                      = (funcAxmInfoGetAxis *)GetProcAddress(g_hAXM, "AxmInfoGetAxis");
        AxmInfoIsMotionModule               = (funcAxmInfoIsMotionModule *)GetProcAddress(g_hAXM, "AxmInfoIsMotionModule");
        AxmInfoIsInvalidAxisNo              = (funcAxmInfoIsInvalidAxisNo *)GetProcAddress(g_hAXM, "AxmInfoIsInvalidAxisNo");
        AxmInfoGetAxisStatus                = (funcAxmInfoGetAxisStatus *)GetProcAddress(g_hAXM, "AxmInfoGetAxisStatus");
        AxmInfoGetAxisCount                 = (funcAxmInfoGetAxisCount *)GetProcAddress(g_hAXM, "AxmInfoGetAxisCount");
        AxmInfoGetFirstAxisNo               = (funcAxmInfoGetFirstAxisNo *)GetProcAddress(g_hAXM, "AxmInfoGetFirstAxisNo");

        AxmVirtualSetAxisNoMap              = (funcAxmVirtualSetAxisNoMap *)GetProcAddress(g_hAXM, "AxmVirtualSetAxisNoMap");
        AxmVirtualGetAxisNoMap              = (funcAxmVirtualGetAxisNoMap *)GetProcAddress(g_hAXM, "AxmVirtualGetAxisNoMap");
        AxmVirtualSetMultiAxisNoMap         = (funcAxmVirtualSetMultiAxisNoMap *)GetProcAddress(g_hAXM, "AxmVirtualSetMultiAxisNoMap");
        AxmVirtualGetMultiAxisNoMap         = (funcAxmVirtualGetMultiAxisNoMap *)GetProcAddress(g_hAXM, "AxmVirtualGetMultiAxisNoMap");
        AxmVirtualResetAxisMap              = (funcAxmVirtualResetAxisMap *)GetProcAddress(g_hAXM, "AxmVirtualResetAxisMap");

        AxmInterruptSetAxis                 = (funcAxmInterruptSetAxis *)GetProcAddress(g_hAXM, "AxmInterruptSetAxis");
        AxmInterruptSetAxisEnable           = (funcAxmInterruptSetAxisEnable *)GetProcAddress(g_hAXM, "AxmInterruptSetAxisEnable");
        AxmInterruptGetAxisEnable           = (funcAxmInterruptGetAxisEnable *)GetProcAddress(g_hAXM, "AxmInterruptGetAxisEnable");
        AxmInterruptRead                    = (funcAxmInterruptRead *)GetProcAddress(g_hAXM, "AxmInterruptRead");
        AxmInterruptReadAxisFlag            = (funcAxmInterruptReadAxisFlag *)GetProcAddress(g_hAXM, "AxmInterruptReadAxisFlag");
        AxmInterruptSetUserEnable           = (funcAxmInterruptSetUserEnable *)GetProcAddress(g_hAXM, "AxmInterruptSetUserEnable");
        AxmInterruptGetUserEnable           = (funcAxmInterruptGetUserEnable *)GetProcAddress(g_hAXM, "AxmInterruptGetUserEnable");

        AxmMotLoadParaAll                   = (funcAxmMotLoadParaAll *)GetProcAddress(g_hAXM, "AxmMotLoadParaAll");
        AxmMotSaveParaAll                   = (funcAxmMotSaveParaAll *)GetProcAddress(g_hAXM, "AxmMotSaveParaAll");
        AxmMotSetParaLoad                   = (funcAxmMotSetParaLoad *)GetProcAddress(g_hAXM, "AxmMotSetParaLoad");
        AxmMotGetParaLoad                   = (funcAxmMotGetParaLoad *)GetProcAddress(g_hAXM, "AxmMotGetParaLoad");
        AxmMotSetPulseOutMethod             = (funcAxmMotSetPulseOutMethod *)GetProcAddress(g_hAXM, "AxmMotSetPulseOutMethod");
        AxmMotGetPulseOutMethod             = (funcAxmMotGetPulseOutMethod *)GetProcAddress(g_hAXM, "AxmMotGetPulseOutMethod");
        AxmMotSetEncInputMethod             = (funcAxmMotSetEncInputMethod *)GetProcAddress(g_hAXM, "AxmMotSetEncInputMethod");
        AxmMotGetEncInputMethod             = (funcAxmMotGetEncInputMethod *)GetProcAddress(g_hAXM, "AxmMotGetEncInputMethod");
        AxmMotSetMoveUnitPerPulse           = (funcAxmMotSetMoveUnitPerPulse *)GetProcAddress(g_hAXM, "AxmMotSetMoveUnitPerPulse");
        AxmMotGetMoveUnitPerPulse           = (funcAxmMotGetMoveUnitPerPulse *)GetProcAddress(g_hAXM, "AxmMotGetMoveUnitPerPulse");
        AxmMotSetDecelMode                  = (funcAxmMotSetDecelMode *)GetProcAddress(g_hAXM, "AxmMotSetDecelMode");
        AxmMotGetDecelMode                  = (funcAxmMotGetDecelMode *)GetProcAddress(g_hAXM, "AxmMotGetDecelMode");
        AxmMotSetRemainPulse                = (funcAxmMotSetRemainPulse *)GetProcAddress(g_hAXM, "AxmMotSetRemainPulse");
        AxmMotGetRemainPulse                = (funcAxmMotGetRemainPulse *)GetProcAddress(g_hAXM, "AxmMotGetRemainPulse");
        AxmMotSetMaxVel                     = (funcAxmMotSetMaxVel *)GetProcAddress(g_hAXM, "AxmMotSetMaxVel");
        AxmMotGetMaxVel                     = (funcAxmMotGetMaxVel *)GetProcAddress(g_hAXM, "AxmMotGetMaxVel");
        AxmMotSetAbsRelMode                 = (funcAxmMotSetAbsRelMode *)GetProcAddress(g_hAXM, "AxmMotSetAbsRelMode");
        AxmMotGetAbsRelMode                 = (funcAxmMotGetAbsRelMode *)GetProcAddress(g_hAXM, "AxmMotGetAbsRelMode");
        AxmMotSetProfileMode                = (funcAxmMotSetProfileMode *)GetProcAddress(g_hAXM, "AxmMotSetProfileMode");
        AxmMotGetProfileMode                = (funcAxmMotGetProfileMode *)GetProcAddress(g_hAXM, "AxmMotGetProfileMode");
        AxmMotSetAccelUnit                  = (funcAxmMotSetAccelUnit *)GetProcAddress(g_hAXM, "AxmMotSetAccelUnit");
        AxmMotGetAccelUnit                  = (funcAxmMotGetAccelUnit *)GetProcAddress(g_hAXM, "AxmMotGetAccelUnit");
        AxmMotSetMinVel                     = (funcAxmMotSetMinVel *)GetProcAddress(g_hAXM, "AxmMotSetMinVel");
        AxmMotGetMinVel                     = (funcAxmMotGetMinVel *)GetProcAddress(g_hAXM, "AxmMotGetMinVel");
        AxmMotSetAccelJerk                  = (funcAxmMotSetAccelJerk *)GetProcAddress(g_hAXM, "AxmMotSetAccelJerk");
        AxmMotGetAccelJerk                  = (funcAxmMotGetAccelJerk *)GetProcAddress(g_hAXM, "AxmMotGetAccelJerk");
        AxmMotSetDecelJerk                  = (funcAxmMotSetDecelJerk *)GetProcAddress(g_hAXM, "AxmMotSetDecelJerk");
        AxmMotGetDecelJerk                  = (funcAxmMotGetDecelJerk *)GetProcAddress(g_hAXM, "AxmMotGetDecelJerk");
        AxmMotSetProfilePriority            = (funcAxmMotSetProfilePriority *)GetProcAddress(g_hAXM, "AxmMotSetProfilePriority");
        AxmMotGetProfilePriority            = (funcAxmMotGetProfilePriority *)GetProcAddress(g_hAXM, "AxmMotGetProfilePriority");

        AxmSignalSetZphaseLevel             = (funcAxmSignalSetZphaseLevel *)GetProcAddress(g_hAXM, "AxmSignalSetZphaseLevel");
        AxmSignalGetZphaseLevel             = (funcAxmSignalGetZphaseLevel *)GetProcAddress(g_hAXM, "AxmSignalGetZphaseLevel");
        AxmSignalSetServoOnLevel            = (funcAxmSignalSetServoOnLevel *)GetProcAddress(g_hAXM, "AxmSignalSetServoOnLevel");
        AxmSignalGetServoOnLevel            = (funcAxmSignalGetServoOnLevel *)GetProcAddress(g_hAXM, "AxmSignalGetServoOnLevel");
        AxmSignalSetServoAlarmResetLevel    = (funcAxmSignalSetServoAlarmResetLevel *)GetProcAddress(g_hAXM, "AxmSignalSetServoAlarmResetLevel");
        AxmSignalGetServoAlarmResetLevel    = (funcAxmSignalGetServoAlarmResetLevel *)GetProcAddress(g_hAXM, "AxmSignalGetServoAlarmResetLevel");
        AxmSignalSetInpos                   = (funcAxmSignalSetInpos *)GetProcAddress(g_hAXM, "AxmSignalSetInpos");
        AxmSignalGetInpos                   = (funcAxmSignalGetInpos *)GetProcAddress(g_hAXM, "AxmSignalGetInpos");
        AxmSignalReadInpos                  = (funcAxmSignalReadInpos *)GetProcAddress(g_hAXM, "AxmSignalReadInpos");
        AxmSignalSetServoAlarm              = (funcAxmSignalSetServoAlarm *)GetProcAddress(g_hAXM, "AxmSignalSetServoAlarm");
        AxmSignalGetServoAlarm              = (funcAxmSignalGetServoAlarm *)GetProcAddress(g_hAXM, "AxmSignalGetServoAlarm");
        AxmSignalReadServoAlarm             = (funcAxmSignalReadServoAlarm *)GetProcAddress(g_hAXM, "AxmSignalReadServoAlarm");
        AxmSignalSetLimit                   = (funcAxmSignalSetLimit *)GetProcAddress(g_hAXM, "AxmSignalSetLimit");
        AxmSignalGetLimit                   = (funcAxmSignalGetLimit *)GetProcAddress(g_hAXM, "AxmSignalGetLimit");
        AxmSignalReadLimit                  = (funcAxmSignalReadLimit *)GetProcAddress(g_hAXM, "AxmSignalReadLimit");
        AxmSignalSetSoftLimit               = (funcAxmSignalSetSoftLimit *)GetProcAddress(g_hAXM, "AxmSignalSetSoftLimit");
        AxmSignalGetSoftLimit               = (funcAxmSignalGetSoftLimit *)GetProcAddress(g_hAXM, "AxmSignalGetSoftLimit");
        AxmSignalSetStop                    = (funcAxmSignalSetStop *)GetProcAddress(g_hAXM, "AxmSignalSetStop");
        AxmSignalGetStop                    = (funcAxmSignalGetStop *)GetProcAddress(g_hAXM, "AxmSignalGetStop");
        AxmSignalReadStop                   = (funcAxmSignalReadStop *)GetProcAddress(g_hAXM, "AxmSignalReadStop");
        AxmSignalServoOn                    = (funcAxmSignalServoOn *)GetProcAddress(g_hAXM, "AxmSignalServoOn");
        AxmSignalIsServoOn                  = (funcAxmSignalIsServoOn *)GetProcAddress(g_hAXM, "AxmSignalIsServoOn");
        AxmSignalServoAlarmReset            = (funcAxmSignalServoAlarmReset *)GetProcAddress(g_hAXM, "AxmSignalServoAlarmReset");
        AxmSignalWriteOutput                = (funcAxmSignalWriteOutput *)GetProcAddress(g_hAXM, "AxmSignalWriteOutput");
        AxmSignalReadOutput                 = (funcAxmSignalReadOutput *)GetProcAddress(g_hAXM, "AxmSignalReadOutput");
        AxmSignalWriteOutputBit             = (funcAxmSignalWriteOutputBit *)GetProcAddress(g_hAXM, "AxmSignalWriteOutputBit");
        AxmSignalReadOutputBit              = (funcAxmSignalReadOutputBit *)GetProcAddress(g_hAXM, "AxmSignalReadOutputBit");
        AxmSignalReadInput                  = (funcAxmSignalReadInput *)GetProcAddress(g_hAXM, "AxmSignalReadInput");
        AxmSignalReadInputBit               = (funcAxmSignalReadInputBit *)GetProcAddress(g_hAXM, "AxmSignalReadInputBit");
        AxmSignalSetFilterBandwidth         = (funcAxmSignalSetFilterBandwidth *)GetProcAddress(g_hAXM, "AxmSignalSetFilterBandwidth");
        
        AxmStatusReadInMotion               = (funcAxmStatusReadInMotion *)GetProcAddress(g_hAXM, "AxmStatusReadInMotion");
        AxmStatusReadDrivePulseCount        = (funcAxmStatusReadDrivePulseCount *)GetProcAddress(g_hAXM, "AxmStatusReadDrivePulseCount");
        AxmStatusReadMotion                 = (funcAxmStatusReadMotion *)GetProcAddress(g_hAXM, "AxmStatusReadMotion");
        AxmStatusReadStop                   = (funcAxmStatusReadStop *)GetProcAddress(g_hAXM, "AxmStatusReadStop");
        AxmStatusReadMechanical             = (funcAxmStatusReadMechanical *)GetProcAddress(g_hAXM, "AxmStatusReadMechanical");
        AxmStatusReadVel                    = (funcAxmStatusReadVel *)GetProcAddress(g_hAXM, "AxmStatusReadVel");
        AxmStatusReadPosError               = (funcAxmStatusReadPosError *)GetProcAddress(g_hAXM, "AxmStatusReadPosError");
        AxmStatusReadDriveDistance          = (funcAxmStatusReadDriveDistance *)GetProcAddress(g_hAXM, "AxmStatusReadDriveDistance");
        AxmStatusSetPosType                 = (funcAxmStatusSetPosType *)GetProcAddress(g_hAXM, "AxmStatusSetPosType");
        AxmStatusGetPosType                 = (funcAxmStatusGetPosType *)GetProcAddress(g_hAXM, "AxmStatusGetPosType");
        AxmStatusSetAbsOrgOffset            = (funcAxmStatusSetAbsOrgOffset *)GetProcAddress(g_hAXM, "AxmStatusSetAbsOrgOffset");
        AxmStatusSetActPos                  = (funcAxmStatusSetActPos *)GetProcAddress(g_hAXM, "AxmStatusSetActPos");
        AxmStatusGetActPos                  = (funcAxmStatusGetActPos *)GetProcAddress(g_hAXM, "AxmStatusGetActPos");
        AxmStatusSetCmdPos                  = (funcAxmStatusSetCmdPos *)GetProcAddress(g_hAXM, "AxmStatusSetCmdPos");
        AxmStatusGetCmdPos                  = (funcAxmStatusGetCmdPos *)GetProcAddress(g_hAXM, "AxmStatusGetCmdPos");
        AxmStatusSetPosMatch                = (funcAxmStatusSetPosMatch *)GetProcAddress(g_hAXM, "AxmStatusSetPosMatch");
        AxmStatusRequestServoAlarm          = (funcAxmStatusRequestServoAlarm *)GetProcAddress(g_hAXM, "AxmStatusRequestServoAlarm");
        AxmStatusReadServoAlarm             = (funcAxmStatusReadServoAlarm *)GetProcAddress(g_hAXM, "AxmStatusReadServoAlarm");
        AxmStatusGetServoAlarmString        = (funcAxmStatusGetServoAlarmString *)GetProcAddress(g_hAXM, "AxmStatusGetServoAlarmString");
        AxmStatusRequestServoAlarmHistory   = (funcAxmStatusRequestServoAlarmHistory *)GetProcAddress(g_hAXM, "AxmStatusRequestServoAlarmHistory");
        AxmStatusReadServoAlarmHistory      = (funcAxmStatusReadServoAlarmHistory *)GetProcAddress(g_hAXM, "AxmStatusReadServoAlarmHistory");
        AxmStatusClearServoAlarmHistory     = (funcAxmStatusClearServoAlarmHistory *)GetProcAddress(g_hAXM, "AxmStatusClearServoAlarmHistory");

        AxmHomeSetSignalLevel               = (funcAxmHomeSetSignalLevel *)GetProcAddress(g_hAXM, "AxmHomeSetSignalLevel");
        AxmHomeGetSignalLevel               = (funcAxmHomeGetSignalLevel *)GetProcAddress(g_hAXM, "AxmHomeGetSignalLevel");
        AxmHomeReadSignal                   = (funcAxmHomeReadSignal *)GetProcAddress(g_hAXM, "AxmHomeReadSignal");
        AxmHomeSetMethod                    = (funcAxmHomeSetMethod *)GetProcAddress(g_hAXM, "AxmHomeSetMethod");
        AxmHomeGetMethod                    = (funcAxmHomeGetMethod *)GetProcAddress(g_hAXM, "AxmHomeGetMethod");
        AxmHomeSetFineAdjust                = (funcAxmHomeSetFineAdjust *)GetProcAddress(g_hAXM, "AxmHomeSetFineAdjust");
        AxmHomeGetFineAdjust                = (funcAxmHomeGetFineAdjust *)GetProcAddress(g_hAXM, "AxmHomeGetFineAdjust");
        AxmHomeSetVel                       = (funcAxmHomeSetVel *)GetProcAddress(g_hAXM, "AxmHomeSetVel");
        AxmHomeGetVel                       = (funcAxmHomeGetVel *)GetProcAddress(g_hAXM, "AxmHomeGetVel");
        AxmHomeSetStart                     = (funcAxmHomeSetStart *)GetProcAddress(g_hAXM, "AxmHomeSetStart");
        AxmHomeSetResult                    = (funcAxmHomeSetResult *)GetProcAddress(g_hAXM, "AxmHomeSetResult");
        AxmHomeGetResult                    = (funcAxmHomeGetResult *)GetProcAddress(g_hAXM, "AxmHomeGetResult");
        AxmHomeGetRate                      = (funcAxmHomeGetRate *)GetProcAddress(g_hAXM, "AxmHomeGetRate");
        
        AxmMoveStartPos                     = (funcAxmMoveStartPos *)GetProcAddress(g_hAXM, "AxmMoveStartPos");
        AxmMovePos                          = (funcAxmMovePos *)GetProcAddress(g_hAXM, "AxmMovePos");
        AxmMoveVel                          = (funcAxmMoveVel *)GetProcAddress(g_hAXM, "AxmMoveVel");
        AxmMoveStartMultiVel                = (funcAxmMoveStartMultiVel *)GetProcAddress(g_hAXM, "AxmMoveStartMultiVel");
        AxmMoveStartMultiVelEx              = (funcAxmMoveStartMultiVelEx *)GetProcAddress(g_hAXM, "AxmMoveStartMultiVelEx");
        AxmMoveStartLineVel                 = (funcAxmMoveStartLineVel *)GetProcAddress(g_hAXM, "AxmMoveStartLineVel");
        AxmMoveSignalSearch                 = (funcAxmMoveSignalSearch *)GetProcAddress(g_hAXM, "AxmMoveSignalSearch");
        AxmMoveSignalCapture                = (funcAxmMoveSignalCapture *)GetProcAddress(g_hAXM, "AxmMoveSignalCapture");
        AxmMoveGetCapturePos                = (funcAxmMoveGetCapturePos *)GetProcAddress(g_hAXM, "AxmMoveGetCapturePos");
        AxmMoveStartMultiPos                = (funcAxmMoveStartMultiPos *)GetProcAddress(g_hAXM, "AxmMoveStartMultiPos");
        AxmMoveMultiPos                     = (funcAxmMoveMultiPos *)GetProcAddress(g_hAXM, "AxmMoveMultiPos");

        AxmMoveStartTorque                  = (funcAxmMoveStartTorque *)GetProcAddress(g_hAXM, "AxmMoveStartTorque");
        AxmMoveTorqueStop                   = (funcAxmMoveTorqueStop *)GetProcAddress(g_hAXM, "AxmMoveTorqueStop");

        AxmMoveStartPosWithList             = (funcAxmMoveStartPosWithList *)GetProcAddress(g_hAXM, "AxmMoveStartPosWithList");
        AxmMoveStartPosWithPosEvent         = (funcAxmMoveStartPosWithPosEvent *)GetProcAddress(g_hAXM, "AxmMoveStartPosWithPosEvent");

        AxmMoveStop                         = (funcAxmMoveStop *)GetProcAddress(g_hAXM, "AxmMoveStop");
        AxmMoveEStop                        = (funcAxmMoveEStop *)GetProcAddress(g_hAXM, "AxmMoveEStop");
        AxmMoveSStop                        = (funcAxmMoveSStop *)GetProcAddress(g_hAXM, "AxmMoveSStop");
        
        AxmOverridePos                      = (funcAxmOverridePos *)GetProcAddress(g_hAXM, "AxmOverridePos");
        AxmOverrideSetMaxVel                = (funcAxmOverrideSetMaxVel *)GetProcAddress(g_hAXM, "AxmOverrideSetMaxVel");
        AxmOverrideVel                      = (funcAxmOverrideVel *)GetProcAddress(g_hAXM, "AxmOverrideVel");
        AxmOverrideAccelVelDecel            = (funcAxmOverrideAccelVelDecel *)GetProcAddress(g_hAXM, "AxmOverrideAccelVelDecel");
        AxmOverrideVelAtPos                 = (funcAxmOverrideVelAtPos *)GetProcAddress(g_hAXM, "AxmOverrideVelAtPos");
        AxmOverrideVelAtMultiPos            = (funcAxmOverrideVelAtMultiPos *)GetProcAddress(g_hAXM, "AxmOverrideVelAtMultiPos");

        AxmLinkSetMode                      = (funcAxmLinkSetMode *)GetProcAddress(g_hAXM, "AxmLinkSetMode");
        AxmLinkGetMode                      = (funcAxmLinkGetMode *)GetProcAddress(g_hAXM, "AxmLinkGetMode");
        AxmLinkResetMode                    = (funcAxmLinkResetMode *)GetProcAddress(g_hAXM, "AxmLinkResetMode");
        AxmGantrySetEnable                  = (funcAxmGantrySetEnable *)GetProcAddress(g_hAXM, "AxmGantrySetEnable");
        AxmGantryGetEnable                  = (funcAxmGantryGetEnable *)GetProcAddress(g_hAXM, "AxmGantryGetEnable");
        AxmGantrySetDisable                 = (funcAxmGantrySetDisable *)GetProcAddress(g_hAXM, "AxmGantrySetDisable");
        
        AxmLineMove                         = (funcAxmLineMove *)GetProcAddress(g_hAXM, "AxmLineMove");
        
        AxmCircleCenterMove                 = (funcAxmCircleCenterMove *)GetProcAddress(g_hAXM, "AxmCircleCenterMove");
        AxmCirclePointMove                  = (funcAxmCirclePointMove *)GetProcAddress(g_hAXM, "AxmCirclePointMove");
        AxmCircleRadiusMove                 = (funcAxmCircleRadiusMove *)GetProcAddress(g_hAXM, "AxmCircleRadiusMove");
        AxmCircleAngleMove                  = (funcAxmCircleAngleMove *)GetProcAddress(g_hAXM, "AxmCircleAngleMove");
        AxmContiSetAxisMap                  = (funcAxmContiSetAxisMap *)GetProcAddress(g_hAXM, "AxmContiSetAxisMap");
        AxmContiGetAxisMap                  = (funcAxmContiGetAxisMap *)GetProcAddress(g_hAXM, "AxmContiGetAxisMap");
        AxmContiSetAbsRelMode               = (funcAxmContiSetAbsRelMode *)GetProcAddress(g_hAXM, "AxmContiSetAbsRelMode");
        AxmContiGetAbsRelMode               = (funcAxmContiGetAbsRelMode *)GetProcAddress(g_hAXM, "AxmContiGetAbsRelMode");
        AxmContiReadFree                    = (funcAxmContiReadFree *)GetProcAddress(g_hAXM, "AxmContiReadFree");
        AxmContiReadIndex                   = (funcAxmContiReadIndex *)GetProcAddress(g_hAXM, "AxmContiReadIndex");
        AxmContiWriteClear                  = (funcAxmContiWriteClear *)GetProcAddress(g_hAXM, "AxmContiWriteClear");
        AxmContiBeginNode                   = (funcAxmContiBeginNode *)GetProcAddress(g_hAXM, "AxmContiBeginNode");
        AxmContiEndNode                     = (funcAxmContiEndNode *)GetProcAddress(g_hAXM, "AxmContiEndNode");
        AxmContiStart                       = (funcAxmContiStart *)GetProcAddress(g_hAXM, "AxmContiStart");
        AxmContiIsMotion                    = (funcAxmContiIsMotion *)GetProcAddress(g_hAXM, "AxmContiIsMotion");
        AxmContiGetNodeNum                  = (funcAxmContiGetNodeNum *)GetProcAddress(g_hAXM, "AxmContiGetNodeNum");
        AxmContiGetTotalNodeNum             = (funcAxmContiGetTotalNodeNum *)GetProcAddress(g_hAXM, "AxmContiGetTotalNodeNum");
        
        AxmTriggerSetTimeLevel              = (funcAxmTriggerSetTimeLevel *)GetProcAddress(g_hAXM, "AxmTriggerSetTimeLevel");
        AxmTriggerGetTimeLevel              = (funcAxmTriggerGetTimeLevel *)GetProcAddress(g_hAXM, "AxmTriggerGetTimeLevel");
        AxmTriggerSetAbsPeriod              = (funcAxmTriggerSetAbsPeriod *)GetProcAddress(g_hAXM, "AxmTriggerSetAbsPeriod");
        AxmTriggerGetAbsPeriod              = (funcAxmTriggerGetAbsPeriod *)GetProcAddress(g_hAXM, "AxmTriggerGetAbsPeriod");
        AxmTriggerSetBlock                  = (funcAxmTriggerSetBlock *)GetProcAddress(g_hAXM, "AxmTriggerSetBlock");
        AxmTriggerGetBlock                  = (funcAxmTriggerGetBlock *)GetProcAddress(g_hAXM, "AxmTriggerGetBlock");
        AxmTriggerOneShot                   = (funcAxmTriggerOneShot *)GetProcAddress(g_hAXM, "AxmTriggerOneShot");
        AxmTriggerSetTimerOneshot           = (funcAxmTriggerSetTimerOneshot *)GetProcAddress(g_hAXM, "AxmTriggerSetTimerOneshot");
        AxmTriggerOnlyAbs                   = (funcAxmTriggerOnlyAbs *)GetProcAddress(g_hAXM, "AxmTriggerOnlyAbs");
        AxmTriggerSetReset                  = (funcAxmTriggerSetReset *)GetProcAddress(g_hAXM, "AxmTriggerSetReset");

        AxmCrcSetMaskLevel                  = (funcAxmCrcSetMaskLevel *)GetProcAddress(g_hAXM, "AxmCrcSetMaskLevel");
        AxmCrcGetMaskLevel                  = (funcAxmCrcGetMaskLevel *)GetProcAddress(g_hAXM, "AxmCrcGetMaskLevel");
        AxmCrcSetOutput                     = (funcAxmCrcSetOutput *)GetProcAddress(g_hAXM, "AxmCrcSetOutput");
        AxmCrcGetOutput                     = (funcAxmCrcGetOutput *)GetProcAddress(g_hAXM, "AxmCrcGetOutput");

        AxmMPGSetEnable                     = (funcAxmMPGSetEnable *)GetProcAddress(g_hAXM, "AxmMPGSetEnable");
        AxmMPGGetEnable                     = (funcAxmMPGGetEnable *)GetProcAddress(g_hAXM, "AxmMPGGetEnable");
        AxmMPGSetRatio                      = (funcAxmMPGSetRatio *)GetProcAddress(g_hAXM, "AxmMPGSetRatio");
        AxmMPGGetRatio                      = (funcAxmMPGGetRatio *)GetProcAddress(g_hAXM, "AxmMPGGetRatio");
        AxmMPGReset                         = (funcAxmMPGReset *)GetProcAddress(g_hAXM, "AxmMPGReset");
        AxmHelixCenterMove                  = (funcAxmHelixCenterMove *)GetProcAddress(g_hAXM, "AxmHelixCenterMove");
        AxmHelixPointMove                   = (funcAxmHelixPointMove *)GetProcAddress(g_hAXM, "AxmHelixPointMove");
        AxmHelixRadiusMove                  = (funcAxmHelixRadiusMove *)GetProcAddress(g_hAXM, "AxmHelixRadiusMove");
        AxmHelixAngleMove                   = (funcAxmHelixAngleMove *)GetProcAddress(g_hAXM, "AxmHelixAngleMove");

        AxmSplineWrite                      = (funcAxmSplineWrite *)GetProcAddress(g_hAXM, "AxmSplineWrite");

        AxmCompensationSet                  = (funcAxmCompensationSet *)GetProcAddress(g_hAXM, "AxmCompensationSet");
        AxmCompensationGet                  = (funcAxmCompensationGet *)GetProcAddress(g_hAXM, "AxmCompensationGet");
        AxmCompensationEnable               = (funcAxmCompensationEnable *)GetProcAddress(g_hAXM, "AxmCompensationEnable");
        AxmCompensationIsEnable             = (funcAxmCompensationIsEnable *)GetProcAddress(g_hAXM, "AxmCompensationIsEnable");

        AxmEcamSet                          = (funcAxmEcamSet *)GetProcAddress(g_hAXM, "AxmEcamSet");
        AxmEcamGet                          = (funcAxmEcamGet *)GetProcAddress(g_hAXM, "AxmEcamGet");
        AxmEcamEnableBySlave                = (funcAxmEcamEnableBySlave *)GetProcAddress(g_hAXM, "AxmEcamEnableBySlave");
        AxmEcamIsSlaveEnable                = (funcAxmEcamIsSlaveEnable *)GetProcAddress(g_hAXM, "AxmEcamIsSlaveEnable");
        AxmEcamEnableByMaster               = (funcAxmEcamEnableByMaster *)GetProcAddress(g_hAXM, "AxmEcamEnableByMaster");

        AxmStatusSetServoMonitor            = (funcAxmStatusSetServoMonitor *)GetProcAddress(g_hAXM, "AxmStatusSetServoMonitor");
        AxmStatusGetServoMonitor            = (funcAxmStatusGetServoMonitor *)GetProcAddress(g_hAXM, "AxmStatusGetServoMonitor");
        AxmStatusSetServoMonitorEnable      = (funcAxmStatusSetServoMonitorEnable *)GetProcAddress(g_hAXM, "AxmStatusSetServoMonitorEnable");
        AxmStatusGetServoMonitorEnable      = (funcAxmStatusGetServoMonitorEnable *)GetProcAddress(g_hAXM, "AxmStatusGetServoMonitorEnable");
        AxmStatusReadServoMonitorFlag       = (funcAxmStatusReadServoMonitorFlag *)GetProcAddress(g_hAXM, "AxmStatusReadServoMonitorFlag");
        AxmStatusReadServoMonitorValue      = (funcAxmStatusReadServoMonitorValue *)GetProcAddress(g_hAXM, "AxmStatusReadServoMonitorValue");
        AxmStatusSetReadServoLoadRatio      = (funcAxmStatusSetReadServoLoadRatio *)GetProcAddress(g_hAXM, "AxmStatusSetReadServoLoadRatio");
        AxmStatusReadServoLoadRatio         = (funcAxmStatusReadServoLoadRatio *)GetProcAddress(g_hAXM, "AxmStatusReadServoLoadRatio");
        AxmMotSetScaleCoeff                 = (funcAxmMotSetScaleCoeff *)GetProcAddress(g_hAXM, "AxmMotSetScaleCoeff");
        AxmMotGetScaleCoeff                 = (funcAxmMotGetScaleCoeff *)GetProcAddress(g_hAXM, "AxmMotGetScaleCoeff");
        AxmMoveSignalSearchEx               = (funcAxmMoveSignalSearchEx *)GetProcAddress(g_hAXM, "AxmMoveSignalSearchEx");
        AxmMoveToAbsPos                     = (funcAxmMoveToAbsPos *)GetProcAddress(g_hAXM, "AxmMoveToAbsPos");
        AxmStatusReadVelEx                  = (funcAxmStatusReadVelEx *)GetProcAddress(g_hAXM, "AxmStatusReadVelEx");
        AxmGantrySetCompensationGain        = (funcAxmGantrySetCompensationGain *)GetProcAddress(g_hAXM, "AxmGantrySetCompensationGain");
        AxmGantryGetCompensationGain        = (funcAxmGantryGetCompensationGain *)GetProcAddress(g_hAXM, "AxmGantryGetCompensationGain");

        AxmMotSetElectricGearRatio          = (funcAxmMotSetElectricGearRatio *)GetProcAddress(g_hAXM, "AxmMotSetElectricGearRatio");
        AxmMotGetElectricGearRatio          = (funcAxmMotGetElectricGearRatio *)GetProcAddress(g_hAXM, "AxmMotGetElectricGearRatio");
        AxmMotSetTorqueLimit                = (funcAxmMotSetTorqueLimit *)GetProcAddress(g_hAXM, "AxmMotSetTorqueLimit");
        AxmMotGetTorqueLimit                = (funcAxmMotGetTorqueLimit *)GetProcAddress(g_hAXM, "AxmMotGetTorqueLimit");
        AxmOverridePosSetFunction           = (funcAxmOverridePosSetFunction *)GetProcAddress(g_hAXM, "AxmOverridePosSetFunction");
        AxmOverridePosGetFunction           = (funcAxmOverridePosGetFunction *)GetProcAddress(g_hAXM, "AxmOverridePosGetFunction");
		
        AxmServoCmdExecution                = (funcAxmServoCmdExecution *)GetProcAddress(g_hAXM, "AxmServoCmdExecution");
        AxmSignalSetInposRange              = (funcAxmSignalSetInposRange *)GetProcAddress(g_hAXM, "AxmSignalSetInposRange");
        AxmSignalGetInposRange              = (funcAxmSignalGetInposRange *)GetProcAddress(g_hAXM, "AxmSignalGetInposRange");
        AxmMotSetOverridePosMode            = (funcAxmMotSetOverridePosMode *)GetProcAddress(g_hAXM, "AxmMotSetOverridePosMode");
        AxmMotGetOverridePosMode            = (funcAxmMotGetOverridePosMode *)GetProcAddress(g_hAXM, "AxmMotGetOverridePosMode");
        AxmMotSetOverrideLinePosMode        = (funcAxmMotSetOverrideLinePosMode *)GetProcAddress(g_hAXM, "AxmMotSetOverrideLinePosMode");
        AxmMotGetOverrideLinePosMode        = (funcAxmMotGetOverrideLinePosMode *)GetProcAddress(g_hAXM, "AxmMotGetOverrideLinePosMode");
        AxmMoveStartPosEx                   = (funcAxmMoveStartPosEx *)GetProcAddress(g_hAXM, "AxmMoveStartPosEx");
        AxmMovePosEx                        = (funcAxmMovePosEx *)GetProcAddress(g_hAXM, "AxmMovePosEx");
        AxmMoveCoordStop                    = (funcAxmMoveCoordStop *)GetProcAddress(g_hAXM, "AxmMoveCoordStop");
        AxmMoveCoordEStop                   = (funcAxmMoveCoordEStop *)GetProcAddress(g_hAXM, "AxmMoveCoordEStop");
        AxmMoveCoordSStop                   = (funcAxmMoveCoordSStop *)GetProcAddress(g_hAXM, "AxmMoveCoordSStop");
        AxmOverrideLinePos                  = (funcAxmOverrideLinePos *)GetProcAddress(g_hAXM, "AxmOverrideLinePos");
        AxmOverrideLineVel                  = (funcAxmOverrideLineVel *)GetProcAddress(g_hAXM, "AxmOverrideLineVel");
        AxmOverrideLineAccelVelDecel        = (funcAxmOverrideLineAccelVelDecel *)GetProcAddress(g_hAXM, "AxmOverrideLineAccelVelDecel");
        AxmOverrideAccelVelDecelAtPos       = (funcAxmOverrideAccelVelDecelAtPos *)GetProcAddress(g_hAXM, "AxmOverrideAccelVelDecelAtPos");
        AxmEGearSet                         = (funcAxmEGearSet *)GetProcAddress(g_hAXM, "AxmEGearSet");
        AxmEGearGet                         = (funcAxmEGearGet *)GetProcAddress(g_hAXM, "AxmEGearGet");
        AxmEGearReset                       = (funcAxmEGearReset *)GetProcAddress(g_hAXM, "AxmEGearReset");
        AxmEGearEnable                      = (funcAxmEGearEnable *)GetProcAddress(g_hAXM, "AxmEGearEnable");
        AxmEGearIsEnable                    = (funcAxmEGearIsEnable *)GetProcAddress(g_hAXM, "AxmEGearIsEnable");
        AxmMotSetEndVel                     = (funcAxmMotSetEndVel *)GetProcAddress(g_hAXM, "AxmMotSetEndVel");
        AxmMotGetEndVel                     = (funcAxmMotGetEndVel *)GetProcAddress(g_hAXM, "AxmMotGetEndVel");

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL FreeAXM()
{
    if (g_hAXM)
    {
        FreeLibrary(g_hAXM);
        g_hAXM = NULL;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
