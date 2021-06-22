#include "stdafx.h"
#include "DAXDev.h"

HINSTANCE   g_hAXDev = NULL;

funcAxlGetBoardAddress                      *AxlGetBoardAddress;
funcAxlGetBoardID                           *AxlGetBoardID;
funcAxlGetBoardVersion                      *AxlGetBoardVersion;
funcAxlGetModuleID                          *AxlGetModuleID;
funcAxlGetModuleVersion                     *AxlGetModuleVersion;
funcAxlGetModuleNodeInfo                    *AxlGetModuleNodeInfo;

funcAxlSetDataFlash                         *AxlSetDataFlash; 
funcAxlGetDataFlash                         *AxlGetDataFlash;

funcAxaInfoGetModuleNo                      *AxaInfoGetModuleNo;
funcAxdInfoGetModuleNo                      *AxdInfoGetModuleNo;

funcAxmSetCommand                           *AxmSetCommand;
funcAxmSetCommandData08                     *AxmSetCommandData08;
funcAxmGetCommandData08                     *AxmGetCommandData08;
funcAxmSetCommandData16                     *AxmSetCommandData16;
funcAxmGetCommandData16                     *AxmGetCommandData16;
funcAxmSetCommandData24                     *AxmSetCommandData24;
funcAxmGetCommandData24                     *AxmGetCommandData24;
funcAxmSetCommandData32                     *AxmSetCommandData32;
funcAxmGetCommandData32                     *AxmGetCommandData32;

funcAxmSetCommandQi                         *AxmSetCommandQi;
funcAxmSetCommandData08Qi                   *AxmSetCommandData08Qi;
funcAxmGetCommandData08Qi                   *AxmGetCommandData08Qi;
funcAxmSetCommandData16Qi                   *AxmSetCommandData16Qi;
funcAxmGetCommandData16Qi                   *AxmGetCommandData16Qi;
funcAxmSetCommandData24Qi                   *AxmSetCommandData24Qi;
funcAxmGetCommandData24Qi                   *AxmGetCommandData24Qi;
funcAxmSetCommandData32Qi                   *AxmSetCommandData32Qi;
funcAxmGetCommandData32Qi                   *AxmGetCommandData32Qi;

funcAxmGetPortData                          *AxmGetPortData;
funcAxmSetPortData                          *AxmSetPortData;
funcAxmGetPortDataQi                        *AxmGetPortDataQi;
funcAxmSetPortDataQi                        *AxmSetPortDataQi;

funcAxmSetScriptCaptionIp                   *AxmSetScriptCaptionIp;
funcAxmGetScriptCaptionIp                   *AxmGetScriptCaptionIp;
funcAxmSetScriptCaptionQi                   *AxmSetScriptCaptionQi;
funcAxmGetScriptCaptionQi                   *AxmGetScriptCaptionQi;
funcAxmSetScriptCaptionQueueClear           *AxmSetScriptCaptionQueueClear;
funcAxmGetScriptCaptionQueueCount           *AxmGetScriptCaptionQueueCount;
funcAxmGetScriptCaptionQueueDataCount       *AxmGetScriptCaptionQueueDataCount;

funcAxmGetOptimizeDriveData                 *AxmGetOptimizeDriveData;
funcAxmBoardWriteByte                       *AxmBoardWriteByte;
funcAxmBoardReadByte                        *AxmBoardReadByte;
funcAxmBoardWriteWord                       *AxmBoardWriteWord;
funcAxmBoardReadWord                        *AxmBoardReadWord;
funcAxmBoardWriteDWord                      *AxmBoardWriteDWord;
funcAxmBoardReadDWord                       *AxmBoardReadDWord;

funcAxmModuleWriteByte                      *AxmModuleWriteByte;
funcAxmModuleReadByte                       *AxmModuleReadByte;
funcAxmModuleWriteWord                      *AxmModuleWriteWord;
funcAxmModuleReadWord                       *AxmModuleReadWord;
funcAxmModuleWriteDWord                     *AxmModuleWriteDWord;
funcAxmModuleReadDWord                      *AxmModuleReadDWord;

funcAxmStatusSetActComparatorPos            *AxmStatusSetActComparatorPos;
funcAxmStatusGetActComparatorPos            *AxmStatusGetActComparatorPos;
funcAxmStatusSetCmdComparatorPos            *AxmStatusSetCmdComparatorPos;
funcAxmStatusGetCmdComparatorPos            *AxmStatusGetCmdComparatorPos;
funcAxmLineMoveVel                          *AxmLineMoveVel;
funcAxmSensorSetSignal                      *AxmSensorSetSignal;
funcAxmSensorGetSignal                      *AxmSensorGetSignal;
funcAxmSensorReadSignal                     *AxmSensorReadSignal;
funcAxmSensorMovePos                        *AxmSensorMovePos;
funcAxmSensorStartMovePos                   *AxmSensorStartMovePos;

funcAxmHomeGetStepTrace                     *AxmHomeGetStepTrace;
funcAxmHomeSetConfig                        *AxmHomeSetConfig;
funcAxmHomeGetConfig                        *AxmHomeGetConfig;
funcAxmHomeSetMoveSearch                    *AxmHomeSetMoveSearch;
funcAxmHomeSetMoveReturn                    *AxmHomeSetMoveReturn;
funcAxmHomeSetMoveLeave                     *AxmHomeSetMoveLeave;
funcAxmHomeSetMultiMoveSearch               *AxmHomeSetMultiMoveSearch;
funcAxmContiSetProfileMode                  *AxmContiSetProfileMode;
funcAxmContiGetProfileMode                  *AxmContiGetProfileMode;
funcAxmMoveProfilePos                       *AxmMoveProfilePos;
funcAxdiInterruptFlagReadBit                *AxdiInterruptFlagReadBit;
funcAxdiInterruptFlagReadByte               *AxdiInterruptFlagReadByte;
funcAxdiInterruptFlagReadWord               *AxdiInterruptFlagReadWord;
funcAxdiInterruptFlagReadDword              *AxdiInterruptFlagReadDword;
funcAxdiInterruptFlagRead                   *AxdiInterruptFlagRead;
funcAxmLogSetAxis                           *AxmLogSetAxis;
funcAxmLogGetAxis                           *AxmLogGetAxis;
funcAxaiLogSetChannel                       *AxaiLogSetChannel;
funcAxaiLogGetChannel                       *AxaiLogGetChannel;
funcAxaoLogSetChannel                       *AxaoLogSetChannel;
funcAxaoLogGetChannel                       *AxaoLogGetChannel;
funcAxdLogSetModule                         *AxdLogSetModule;
funcAxdLogGetModule                         *AxdLogGetModule;

funcAxlGetFirmwareVersion                   *AxlGetFirmwareVersion;
funcAxlSetFirmwareCopy                      *AxlSetFirmwareCopy;
funcAxlSetFirmwareUpdate                    *AxlSetFirmwareUpdate;
funcAxlCheckStatus                          *AxlCheckStatus;

funcAxlRtexUniversalCmd                     *AxlRtexUniversalCmd;
funcAxmRtexSlaveCmd                         *AxmRtexSlaveCmd;
funcAxmRtexGetSlaveCmdResult                *AxmRtexGetSlaveCmdResult;
funcAxmRtexGetAxisStatus                    *AxmRtexGetAxisStatus;
funcAxmRtexGetAxisReturnData                *AxmRtexGetAxisReturnData;
funcAxmRtexGetAxisSlaveStatus               *AxmRtexGetAxisSlaveStatus;

funcAxmSetAxisCmd                           *AxmSetAxisCmd;
funcAxmGetAxisCmdResult                     *AxmGetAxisCmdResult;
funcAxlGetDpRamData                         *AxlGetDpRamData;
funcAxlBoardReadDpramWord                   *AxlBoardReadDpramWord;
funcAxlSetSendBoardCommand                  *AxlSetSendBoardCommand;
funcAxlGetResponseBoardCommand              *AxlGetResponseBoardCommand;
funcAxmInfoGetFirmwareVersion               *AxmInfoGetFirmwareVersion;
funcAxaInfoGetFirmwareVersion               *AxaInfoGetFirmwareVersion;
funcAxdInfoGetFirmwareVersion               *AxdInfoGetFirmwareVersion;
funcAxmSetTorqFeedForward                   *AxmSetTorqFeedForward;
funcAxmGetTorqFeedForward                   *AxmGetTorqFeedForward;
funcAxmSetVelocityFeedForward               *AxmSetVelocityFeedForward;
funcAxmGetVelocityFeedForward               *AxmGetVelocityFeedForward;

funcAxmSignalSetEncoderType                 *AxmSignalSetEncoderType;
funcAxmSignalGetEncoderType                 *AxmSignalGetEncoderType;
funcAxmSetSendAxisCommand                   *AxmSetSendAxisCommand;

funcAxmMotSetUserMotion                     *AxmMotSetUserMotion;
funcAxmMotSetUserMotionUsage                *AxmMotSetUserMotionUsage;
funcAxmMotSetUserPosMotion                  *AxmMotSetUserPosMotion;
funcAxmMotSetUserPosMotionUsage             *AxmMotSetUserPosMotionUsage;
funcAxcKeWriteRamDataAddr                   *AxcKeWriteRamDataAddr;
funcAxcKeReadRamDataAddr                    *AxcKeReadRamDataAddr;
funcAxcKeResetRamDataAll                    *AxcKeResetRamDataAll;
funcAxcTriggerSetTimeout                    *AxcTriggerSetTimeout;
funcAxcTriggerGetTimeout                    *AxcTriggerGetTimeout;
funcAxcStatusGetWaitState                   *AxcStatusGetWaitState;
funcAxcStatusSetWaitState                   *AxcStatusSetWaitState;
funcAxmSeqSetAxisMap                        *AxmSeqSetAxisMap;
funcAxmSeqGetAxisMap                        *AxmSeqGetAxisMap;
funcAxmSeqSetMasterAxisNo                   *AxmSeqSetMasterAxisNo;
funcAxmSeqBeginNode                         *AxmSeqBeginNode;
funcAxmSeqEndNode                           *AxmSeqEndNode;
funcAxmSeqStart                             *AxmSeqStart;
funcAxmSeqAddNode                           *AxmSeqAddNode;
funcAxmSeqGetNodeNum                        *AxmSeqGetNodeNum;
funcAxmSeqGetTotalNodeNum                   *AxmSeqGetTotalNodeNum;
funcAxmSeqIsMotion                          *AxmSeqIsMotion;
funcAxmSeqWriteClear                        *AxmSeqWriteClear;
funcAxmSeqStop                              *AxmSeqStop;

BOOL LoadAXDev()
{
    g_hAXDev    = LoadLibrary("Axl.dll");
    if (g_hAXDev)
    {
        AxlGetBoardAddress                  = (funcAxlGetBoardAddress *)GetProcAddress(g_hAXDev, "AxlGetBoardAddress");
        AxlGetBoardID                       = (funcAxlGetBoardID *)GetProcAddress(g_hAXDev, "AxlGetBoardID");
        AxlGetBoardVersion                  = (funcAxlGetBoardVersion *)GetProcAddress(g_hAXDev, "AxlGetBoardVersion");
        AxlGetModuleID                      = (funcAxlGetModuleID *)GetProcAddress(g_hAXDev, "AxlGetModuleID");
        AxlGetModuleVersion                 = (funcAxlGetModuleVersion *)GetProcAddress(g_hAXDev, "AxlGetModuleVersion");
        AxlGetModuleNodeInfo                = (funcAxlGetModuleNodeInfo *)GetProcAddress(g_hAXDev, "AxlGetModuleNodeInfo");
        AxlSetDataFlash                     = (funcAxlSetDataFlash *)GetProcAddress(g_hAXDev, "AxlSetDataFlash");
        AxlGetDataFlash                     = (funcAxlGetDataFlash *)GetProcAddress(g_hAXDev, "AxlGetDataFlash");
        AxaInfoGetModuleNo                  = (funcAxaInfoGetModuleNo *)GetProcAddress(g_hAXDev, "AxaInfoGetModuleNo");
        AxdInfoGetModuleNo                  = (funcAxdInfoGetModuleNo *)GetProcAddress(g_hAXDev, "AxdInfoGetModuleNo");
        AxmSetCommand                       = (funcAxmSetCommand *)GetProcAddress(g_hAXDev, "AxmSetCommand");
        AxmSetCommandData08                 = (funcAxmSetCommandData08 *)GetProcAddress(g_hAXDev, "AxmSetCommandData08");
        AxmGetCommandData08                 = (funcAxmGetCommandData08 *)GetProcAddress(g_hAXDev, "AxmGetCommandData08");
        AxmSetCommandData16                 = (funcAxmSetCommandData16 *)GetProcAddress(g_hAXDev, "AxmSetCommandData16");
        AxmGetCommandData16                 = (funcAxmGetCommandData16 *)GetProcAddress(g_hAXDev, "AxmGetCommandData16");
        AxmSetCommandData24                 = (funcAxmSetCommandData24 *)GetProcAddress(g_hAXDev, "AxmSetCommandData24");
        AxmGetCommandData24                 = (funcAxmGetCommandData24 *)GetProcAddress(g_hAXDev, "AxmGetCommandData24");
        AxmSetCommandData32                 = (funcAxmSetCommandData32 *)GetProcAddress(g_hAXDev, "AxmSetCommandData32");
        AxmGetCommandData32                 = (funcAxmGetCommandData32 *)GetProcAddress(g_hAXDev, "AxmGetCommandData32");
        AxmSetCommandQi                     = (funcAxmSetCommandQi *)GetProcAddress(g_hAXDev, "AxmSetCommandQi");
        AxmSetCommandData08Qi               = (funcAxmSetCommandData08Qi *)GetProcAddress(g_hAXDev, "AxmSetCommandData08Qi");
        AxmGetCommandData08Qi               = (funcAxmGetCommandData08Qi *)GetProcAddress(g_hAXDev, "AxmGetCommandData08Qi");
        AxmSetCommandData16Qi               = (funcAxmSetCommandData16Qi *)GetProcAddress(g_hAXDev, "AxmSetCommandData16Qi");
        AxmGetCommandData16Qi               = (funcAxmGetCommandData16Qi *)GetProcAddress(g_hAXDev, "AxmGetCommandData16Qi");
        AxmSetCommandData24Qi               = (funcAxmSetCommandData24Qi *)GetProcAddress(g_hAXDev, "AxmSetCommandData24Qi");
        AxmGetCommandData24Qi               = (funcAxmGetCommandData24Qi *)GetProcAddress(g_hAXDev, "AxmGetCommandData24Qi");
        AxmSetCommandData32Qi               = (funcAxmSetCommandData32Qi *)GetProcAddress(g_hAXDev, "AxmSetCommandData32Qi");
        AxmGetCommandData32Qi               = (funcAxmGetCommandData32Qi *)GetProcAddress(g_hAXDev, "AxmGetCommandData32Qi");
        AxmGetPortData                      = (funcAxmGetPortData *)GetProcAddress(g_hAXDev, "AxmGetPortData");
        AxmSetPortData                      = (funcAxmSetPortData *)GetProcAddress(g_hAXDev, "AxmSetPortData");
        AxmGetPortDataQi                    = (funcAxmGetPortDataQi *)GetProcAddress(g_hAXDev, "AxmGetPortDataQi");
        AxmSetPortDataQi                    = (funcAxmSetPortDataQi *)GetProcAddress(g_hAXDev, "AxmSetPortDataQi");
        AxmSetScriptCaptionIp               = (funcAxmSetScriptCaptionIp *)GetProcAddress(g_hAXDev, "AxmSetScriptCaptionIp");
        AxmGetScriptCaptionIp               = (funcAxmGetScriptCaptionIp *)GetProcAddress(g_hAXDev, "AxmGetScriptCaptionIp");
        AxmSetScriptCaptionQi               = (funcAxmSetScriptCaptionQi *)GetProcAddress(g_hAXDev, "AxmSetScriptCaptionQi");
        AxmGetScriptCaptionQi               = (funcAxmGetScriptCaptionQi *)GetProcAddress(g_hAXDev, "AxmGetScriptCaptionQi");
        AxmSetScriptCaptionQueueClear       = (funcAxmSetScriptCaptionQueueClear *)GetProcAddress(g_hAXDev, "AxmSetScriptCaptionQueueClear");
        AxmGetScriptCaptionQueueCount       = (funcAxmGetScriptCaptionQueueCount *)GetProcAddress(g_hAXDev, "AxmGetScriptCaptionQueueCount");
        AxmGetScriptCaptionQueueDataCount   = (funcAxmGetScriptCaptionQueueDataCount *)GetProcAddress(g_hAXDev, "AxmGetScriptCaptionQueueDataCount");
        AxmGetOptimizeDriveData             = (funcAxmGetOptimizeDriveData *)GetProcAddress(g_hAXDev, "AxmGetOptimizeDriveData");
        AxmBoardWriteByte                   = (funcAxmBoardWriteByte *)GetProcAddress(g_hAXDev, "AxmBoardWriteByte");
        AxmBoardReadByte                    = (funcAxmBoardReadByte *)GetProcAddress(g_hAXDev, "AxmBoardReadByte");
        AxmBoardWriteWord                   = (funcAxmBoardWriteWord *)GetProcAddress(g_hAXDev, "AxmBoardWriteWord");
        AxmBoardReadWord                    = (funcAxmBoardReadWord *)GetProcAddress(g_hAXDev, "AxmBoardReadWord");
        AxmBoardWriteDWord                  = (funcAxmBoardWriteDWord *)GetProcAddress(g_hAXDev, "AxmBoardWriteDWord");
        AxmBoardReadDWord                   = (funcAxmBoardReadDWord *)GetProcAddress(g_hAXDev, "AxmBoardReadDWord");
        AxmModuleWriteByte                  = (funcAxmModuleWriteByte *)GetProcAddress(g_hAXDev, "AxmModuleWriteByte");
        AxmModuleReadByte                   = (funcAxmModuleReadByte *)GetProcAddress(g_hAXDev, "AxmModuleReadByte");
        AxmModuleWriteWord                  = (funcAxmModuleWriteWord *)GetProcAddress(g_hAXDev, "AxmModuleWriteWord");
        AxmModuleReadWord                   = (funcAxmModuleReadWord *)GetProcAddress(g_hAXDev, "AxmModuleReadWord");
        AxmModuleWriteDWord                 = (funcAxmModuleWriteDWord *)GetProcAddress(g_hAXDev, "AxmModuleWriteDWord");
        AxmModuleReadDWord                  = (funcAxmModuleReadDWord *)GetProcAddress(g_hAXDev, "AxmModuleReadDWord");
        AxmStatusSetActComparatorPos        = (funcAxmStatusSetActComparatorPos *)GetProcAddress(g_hAXDev, "AxmStatusSetActComparatorPos");
        AxmStatusGetActComparatorPos        = (funcAxmStatusGetActComparatorPos *)GetProcAddress(g_hAXDev, "AxmStatusGetActComparatorPos");
        AxmStatusSetCmdComparatorPos        = (funcAxmStatusSetCmdComparatorPos *)GetProcAddress(g_hAXDev, "AxmStatusSetCmdComparatorPos");
        AxmStatusGetCmdComparatorPos        = (funcAxmStatusGetCmdComparatorPos *)GetProcAddress(g_hAXDev, "AxmStatusGetCmdComparatorPos");
        AxmLineMoveVel                      = (funcAxmLineMoveVel *)GetProcAddress(g_hAXDev, "AxmLineMoveVel");
        AxmSensorSetSignal                  = (funcAxmSensorSetSignal *)GetProcAddress(g_hAXDev, "AxmSensorSetSignal");
        AxmSensorGetSignal                  = (funcAxmSensorGetSignal *)GetProcAddress(g_hAXDev, "AxmSensorGetSignal");
        AxmSensorReadSignal                 = (funcAxmSensorReadSignal *)GetProcAddress(g_hAXDev, "AxmSensorReadSignal");
        AxmSensorMovePos                    = (funcAxmSensorMovePos *)GetProcAddress(g_hAXDev, "AxmSensorMovePos");
        AxmSensorStartMovePos               = (funcAxmSensorStartMovePos *)GetProcAddress(g_hAXDev, "AxmSensorStartMovePos");
        AxmHomeGetStepTrace                 = (funcAxmHomeGetStepTrace *)GetProcAddress(g_hAXDev, "AxmHomeGetStepTrace");
        AxmHomeSetConfig                    = (funcAxmHomeSetConfig *)GetProcAddress(g_hAXDev, "AxmHomeSetConfig");
        AxmHomeGetConfig                    = (funcAxmHomeGetConfig *)GetProcAddress(g_hAXDev, "AxmHomeGetConfig");
        AxmHomeSetMoveSearch                = (funcAxmHomeSetMoveSearch *)GetProcAddress(g_hAXDev, "AxmHomeSetMoveSearch");
        AxmHomeSetMoveReturn                = (funcAxmHomeSetMoveReturn *)GetProcAddress(g_hAXDev, "AxmHomeSetMoveReturn");
        AxmHomeSetMoveLeave                 = (funcAxmHomeSetMoveLeave *)GetProcAddress(g_hAXDev, "AxmHomeSetMoveLeave");
        AxmHomeSetMultiMoveSearch           = (funcAxmHomeSetMultiMoveSearch *)GetProcAddress(g_hAXDev, "AxmHomeSetMultiMoveSearch");
        AxmContiSetProfileMode              = (funcAxmContiSetProfileMode *)GetProcAddress(g_hAXDev, "AxmContiSetProfileMode");
        AxmContiGetProfileMode              = (funcAxmContiGetProfileMode *)GetProcAddress(g_hAXDev, "AxmContiGetProfileMode");
        AxmMoveProfilePos                   = (funcAxmMoveProfilePos *)GetProcAddress(g_hAXDev, "AxmMoveProfilePos");
        AxdiInterruptFlagReadBit            = (funcAxdiInterruptFlagReadBit *)GetProcAddress(g_hAXDev, "AxdiInterruptFlagReadBit");
        AxdiInterruptFlagReadByte           = (funcAxdiInterruptFlagReadByte *)GetProcAddress(g_hAXDev, "AxdiInterruptFlagReadByte");
        AxdiInterruptFlagReadWord           = (funcAxdiInterruptFlagReadWord *)GetProcAddress(g_hAXDev, "AxdiInterruptFlagReadWord");
        AxdiInterruptFlagReadDword          = (funcAxdiInterruptFlagReadDword *)GetProcAddress(g_hAXDev, "AxdiInterruptFlagReadDword");
        AxdiInterruptFlagRead               = (funcAxdiInterruptFlagRead *)GetProcAddress(g_hAXDev, "AxdiInterruptFlagRead");
        AxmLogSetAxis                       = (funcAxmLogSetAxis *)GetProcAddress(g_hAXDev, "AxmLogSetAxis");
        AxmLogGetAxis                       = (funcAxmLogGetAxis *)GetProcAddress(g_hAXDev, "AxmLogGetAxis");
        AxaiLogSetChannel                   = (funcAxaiLogSetChannel *)GetProcAddress(g_hAXDev, "AxaiLogSetChannel");
        AxaiLogGetChannel                   = (funcAxaiLogGetChannel *)GetProcAddress(g_hAXDev, "AxaiLogGetChannel");
        AxaoLogSetChannel                   = (funcAxaoLogSetChannel *)GetProcAddress(g_hAXDev, "AxaoLogSetChannel");
        AxaoLogGetChannel                   = (funcAxaoLogGetChannel *)GetProcAddress(g_hAXDev, "AxaoLogGetChannel");
        AxdLogSetModule                     = (funcAxdLogSetModule *)GetProcAddress(g_hAXDev, "AxdLogSetModule");
        AxdLogGetModule                     = (funcAxdLogGetModule *)GetProcAddress(g_hAXDev, "AxdLogGetModule");
        AxlGetFirmwareVersion               = (funcAxlGetFirmwareVersion *)GetProcAddress(g_hAXDev, "AxlGetFirmwareVersion");
        AxlSetFirmwareCopy                  = (funcAxlSetFirmwareCopy *)GetProcAddress(g_hAXDev, "AxlSetFirmwareCopy");
        AxlSetFirmwareUpdate                = (funcAxlSetFirmwareUpdate *)GetProcAddress(g_hAXDev, "AxlSetFirmwareUpdate");
        AxlCheckStatus                      = (funcAxlCheckStatus *)GetProcAddress(g_hAXDev, "AxlCheckStatus");
        AxlRtexUniversalCmd                 = (funcAxlRtexUniversalCmd *)GetProcAddress(g_hAXDev, "AxlRtexUniversalCmd");
        AxmRtexSlaveCmd                     = (funcAxmRtexSlaveCmd *)GetProcAddress(g_hAXDev, "AxmRtexSlaveCmd");
        AxmRtexGetSlaveCmdResult            = (funcAxmRtexGetSlaveCmdResult *)GetProcAddress(g_hAXDev, "AxmRtexGetSlaveCmdResult");
        AxmRtexGetAxisStatus                = (funcAxmRtexGetAxisStatus *)GetProcAddress(g_hAXDev, "AxmRtexGetAxisStatus");
        AxmRtexGetAxisReturnData            = (funcAxmRtexGetAxisReturnData *)GetProcAddress(g_hAXDev, "AxmRtexGetAxisReturnData");
        AxmRtexGetAxisSlaveStatus           = (funcAxmRtexGetAxisSlaveStatus *)GetProcAddress(g_hAXDev, "AxmRtexGetAxisSlaveStatus");
        AxmSetAxisCmd                       = (funcAxmSetAxisCmd *)GetProcAddress(g_hAXDev, "AxmSetAxisCmd");
        AxmGetAxisCmdResult                 = (funcAxmGetAxisCmdResult *)GetProcAddress(g_hAXDev, "AxmGetAxisCmdResult");
        AxlGetDpRamData                     = (funcAxlGetDpRamData *)GetProcAddress(g_hAXDev, "AxlGetDpRamData");
        AxlBoardReadDpramWord               = (funcAxlBoardReadDpramWord *)GetProcAddress(g_hAXDev, "AxlBoardReadDpramWord");
        AxlSetSendBoardCommand              = (funcAxlSetSendBoardCommand *)GetProcAddress(g_hAXDev, "AxlSetSendBoardCommand");
        AxlGetResponseBoardCommand          = (funcAxlGetResponseBoardCommand *)GetProcAddress(g_hAXDev, "AxlGetResponseBoardCommand");
        AxmInfoGetFirmwareVersion           = (funcAxmInfoGetFirmwareVersion *)GetProcAddress(g_hAXDev, "AxmInfoGetFirmwareVersion");
        AxaInfoGetFirmwareVersion           = (funcAxaInfoGetFirmwareVersion *)GetProcAddress(g_hAXDev, "AxaInfoGetFirmwareVersion");
        AxdInfoGetFirmwareVersion           = (funcAxdInfoGetFirmwareVersion *)GetProcAddress(g_hAXDev, "AxdInfoGetFirmwareVersion");
        AxmSetTorqFeedForward               = (funcAxmSetTorqFeedForward *)GetProcAddress(g_hAXDev, "AxmSetTorqFeedForward");
        AxmGetTorqFeedForward               = (funcAxmGetTorqFeedForward *)GetProcAddress(g_hAXDev, "AxmGetTorqFeedForward");
        AxmSetVelocityFeedForward           = (funcAxmSetVelocityFeedForward *)GetProcAddress(g_hAXDev, "AxmSetVelocityFeedForward");
        AxmGetVelocityFeedForward           = (funcAxmGetVelocityFeedForward *)GetProcAddress(g_hAXDev, "AxmGetVelocityFeedForward");
        AxmSignalSetEncoderType             = (funcAxmSignalSetEncoderType *)GetProcAddress(g_hAXDev, "AxmSignalSetEncoderType");
        AxmSignalGetEncoderType             = (funcAxmSignalGetEncoderType *)GetProcAddress(g_hAXDev, "AxmSignalGetEncoderType");
        AxmSetSendAxisCommand               = (funcAxmSetSendAxisCommand *)GetProcAddress(g_hAXDev, "AxmSetSendAxisCommand");
        AxmMotSetUserMotion                 = (funcAxmMotSetUserMotion *)GetProcAddress(g_hAXDev, "AxmMotSetUserMotion");
        AxmMotSetUserMotionUsage            = (funcAxmMotSetUserMotionUsage *)GetProcAddress(g_hAXDev, "AxmMotSetUserMotionUsage");
        AxmMotSetUserPosMotion              = (funcAxmMotSetUserPosMotion *)GetProcAddress(g_hAXDev, "AxmMotSetUserPosMotion");
        AxmMotSetUserPosMotionUsage         = (funcAxmMotSetUserPosMotionUsage *)GetProcAddress(g_hAXDev, "AxmMotSetUserPosMotionUsage");
        AxcKeWriteRamDataAddr               = (funcAxcKeWriteRamDataAddr *)GetProcAddress(g_hAXDev, "AxcKeWriteRamDataAddr");
        AxcKeReadRamDataAddr                = (funcAxcKeReadRamDataAddr *)GetProcAddress(g_hAXDev, "AxcKeReadRamDataAddr");
        AxcKeResetRamDataAll                = (funcAxcKeResetRamDataAll *)GetProcAddress(g_hAXDev, "AxcKeResetRamDataAll");
        AxcTriggerSetTimeout                = (funcAxcTriggerSetTimeout *)GetProcAddress(g_hAXDev, "AxcTriggerSetTimeout");
        AxcTriggerGetTimeout                = (funcAxcTriggerGetTimeout *)GetProcAddress(g_hAXDev, "AxcTriggerGetTimeout");
        AxcStatusGetWaitState               = (funcAxcStatusGetWaitState *)GetProcAddress(g_hAXDev, "AxcStatusGetWaitState");
        AxcStatusSetWaitState               = (funcAxcStatusSetWaitState *)GetProcAddress(g_hAXDev, "AxcStatusSetWaitState");
        AxmSeqSetAxisMap                    = (funcAxmSeqSetAxisMap *)GetProcAddress(g_hAXDev, "AxmSeqSetAxisMap");
        AxmSeqGetAxisMap                    = (funcAxmSeqGetAxisMap *)GetProcAddress(g_hAXDev, "AxmSeqGetAxisMap");
        AxmSeqSetMasterAxisNo               = (funcAxmSeqSetMasterAxisNo *)GetProcAddress(g_hAXDev, "AxmSeqSetMasterAxisNo");
        AxmSeqBeginNode                     = (funcAxmSeqBeginNode *)GetProcAddress(g_hAXDev, "AxmSeqBeginNode");
        AxmSeqEndNode                       = (funcAxmSeqEndNode *)GetProcAddress(g_hAXDev, "AxmSeqEndNode");
        AxmSeqStart                         = (funcAxmSeqStart *)GetProcAddress(g_hAXDev, "AxmSeqStart");
        AxmSeqAddNode                       = (funcAxmSeqAddNode *)GetProcAddress(g_hAXDev, "AxmSeqAddNode");
        AxmSeqGetNodeNum                    = (funcAxmSeqGetNodeNum *)GetProcAddress(g_hAXDev, "AxmSeqGetNodeNum");
        AxmSeqGetTotalNodeNum               = (funcAxmSeqGetTotalNodeNum *)GetProcAddress(g_hAXDev, "AxmSeqGetTotalNodeNum");
        AxmSeqIsMotion                      = (funcAxmSeqIsMotion *)GetProcAddress(g_hAXDev, "AxmSeqIsMotion");
        AxmSeqWriteClear                    = (funcAxmSeqWriteClear *)GetProcAddress(g_hAXDev, "AxmSeqWriteClear");
        AxmSeqStop                          = (funcAxmSeqStop *)GetProcAddress(g_hAXDev, "AxmSeqStop");

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL FreeAXDev()
{
    if (g_hAXDev)
    {
        FreeLibrary(g_hAXDev);
        g_hAXDev = NULL;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
