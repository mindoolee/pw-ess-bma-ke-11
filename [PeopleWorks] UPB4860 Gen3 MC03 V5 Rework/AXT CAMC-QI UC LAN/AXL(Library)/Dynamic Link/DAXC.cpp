#include "stdafx.h"
#include "DAXC.h"

HINSTANCE    g_hAXC = NULL;

funcAxcInfoIsCNTModule                           *AxcInfoIsCNTModule;
funcAxcInfoGetModuleNo                           *AxcInfoGetModuleNo;
funcAxcInfoGetModuleCount                        *AxcInfoGetModuleCount;
funcAxcInfoGetChannelCount                       *AxcInfoGetChannelCount;
funcAxcInfoGetModule                             *AxcInfoGetModule;
funcAxcInfoGetModuleStatus                       *AxcInfoGetModuleStatus;
funcAxcInfoGetTotalChannelCount                  *AxcInfoGetTotalChannelCount;
funcAxcInfoGetFirstChannelNoOfModuleNo           *AxcInfoGetFirstChannelNoOfModuleNo;
funcAxcSignalSetEncInputMethod                   *AxcSignalSetEncInputMethod;
funcAxcSignalGetEncInputMethod                   *AxcSignalGetEncInputMethod;
funcAxcSignalSetCaptureFunction                  *AxcSignalSetCaptureFunction;
funcAxcSignalGetCaptureFunction                  *AxcSignalGetCaptureFunction;
funcAxcSignalGetCapturePos                       *AxcSignalGetCapturePos;
funcAxcSignalSetEncReverse                       *AxcSignalSetEncReverse;
funcAxcSignalGetEncReverse                       *AxcSignalGetEncReverse;
funcAxcSignalSetEncSource                        *AxcSignalSetEncSource;
funcAxcSignalGetEncSource                        *AxcSignalGetEncSource;
funcAxcSignalWriteOutput                         *AxcSignalWriteOutput;
funcAxcSignalReadOutput                          *AxcSignalReadOutput;
funcAxcSignalWriteOutputBit                      *AxcSignalWriteOutputBit;
funcAxcSignalReadOutputBit                       *AxcSignalReadOutputBit;
funcAxcSignalReadInput                           *AxcSignalReadInput;
funcAxcSignalReadInputBit                        *AxcSignalReadInputBit;
funcAxcMotSetMoveUnitPerPulse                    *AxcMotSetMoveUnitPerPulse;
funcAxcMotGetMoveUnitPerPulse                    *AxcMotGetMoveUnitPerPulse;
funcAxcStatusGetActPos                           *AxcStatusGetActPos;
funcAxcStatusSetActPos                           *AxcStatusSetActPos;
funcAxcStatusGetChannel                          *AxcStatusGetChannel;
funcAxcTriggerSetFunction                        *AxcTriggerSetFunction;
funcAxcTriggerGetFunction                        *AxcTriggerGetFunction;
funcAxcTriggerSetNotchPos                        *AxcTriggerSetNotchPos;
funcAxcTriggerGetNotchPos                        *AxcTriggerGetNotchPos;
funcAxcTriggerSetOutput                          *AxcTriggerSetOutput;
funcAxcTriggerSetBlockLowerPos                   *AxcTriggerSetBlockLowerPos;
funcAxcTriggerGetBlockLowerPos                   *AxcTriggerGetBlockLowerPos;
funcAxcTriggerSetBlockUpperPos                   *AxcTriggerSetBlockUpperPos;
funcAxcTriggerGetBlockUpperPos                   *AxcTriggerGetBlockUpperPos;
funcAxcTriggerSetPosPeriod                       *AxcTriggerSetPosPeriod;
funcAxcTriggerGetPosPeriod                       *AxcTriggerGetPosPeriod;
funcAxcTriggerSetDirectionCheck                  *AxcTriggerSetDirectionCheck;
funcAxcTriggerGetDirectionCheck                  *AxcTriggerGetDirectionCheck;
funcAxcTriggerSetBlock                           *AxcTriggerSetBlock;
funcAxcTriggerGetBlock                           *AxcTriggerGetBlock;
funcAxcTriggerSetTime                            *AxcTriggerSetTime;
funcAxcTriggerGetTime                            *AxcTriggerGetTime;
funcAxcTriggerSetLevel                           *AxcTriggerSetLevel;
funcAxcTriggerGetLevel                           *AxcTriggerGetLevel;
funcAxcTriggerSetFreq                            *AxcTriggerSetFreq;
funcAxcTriggerGetFreq                            *AxcTriggerGetFreq;
funcAxcTriggerSetEnable                          *AxcTriggerSetEnable;
funcAxcTriggerGetEnable                          *AxcTriggerGetEnable;
funcAxcTriggerReadAbsRamData                     *AxcTriggerReadAbsRamData;
funcAxcTriggerWriteAbsRamData                    *AxcTriggerWriteAbsRamData;
funcAxcTriggerSetAbs                             *AxcTriggerSetAbs;

BOOL LoadAXC()
{
    g_hAXC    = LoadLibrary("Axl.dll");

    if (g_hAXC)
    {
        AxcInfoIsCNTModule                            = (funcAxcInfoIsCNTModule *)GetProcAddress(g_hAXC, "AxcInfoIsCNTModule");
        AxcInfoGetModuleNo                            = (funcAxcInfoGetModuleNo *)GetProcAddress(g_hAXC, "AxcInfoGetModuleNo");
        AxcInfoGetModuleCount                         = (funcAxcInfoGetModuleCount *)GetProcAddress(g_hAXC, "AxcInfoGetModuleCount");
        AxcInfoGetChannelCount                        = (funcAxcInfoGetChannelCount *)GetProcAddress(g_hAXC, "AxcInfoGetChannelCount");
        AxcInfoGetModule                              = (funcAxcInfoGetModule *)GetProcAddress(g_hAXC, "AxcInfoGetModule");
        AxcInfoGetModuleStatus                        = (funcAxcInfoGetModuleStatus *)GetProcAddress(g_hAXC, "AxcInfoGetModuleStatus");
        AxcInfoGetTotalChannelCount                   = (funcAxcInfoGetTotalChannelCount *)GetProcAddress(g_hAXC, "AxcInfoGetTotalChannelCount");
        AxcInfoGetFirstChannelNoOfModuleNo            = (funcAxcInfoGetFirstChannelNoOfModuleNo *)GetProcAddress(g_hAXC, "funcAxcInfoGetFirstChannelNoOfModuleNo");
        
        AxcSignalSetEncInputMethod                    = (funcAxcSignalSetEncInputMethod *)GetProcAddress(g_hAXC, "AxcSignalSetEncInputMethod");
        AxcSignalGetEncInputMethod                    = (funcAxcSignalGetEncInputMethod *)GetProcAddress(g_hAXC, "AxcSignalGetEncInputMethod");
        AxcSignalSetCaptureFunction                   = (funcAxcSignalSetCaptureFunction *)GetProcAddress(g_hAXC, "AxcSignalSetCaptureFunction");
        AxcSignalGetCaptureFunction                   = (funcAxcSignalGetCaptureFunction *)GetProcAddress(g_hAXC, "AxcSignalGetCaptureFunction");
        AxcSignalGetCapturePos                        = (funcAxcSignalGetCapturePos *)GetProcAddress(g_hAXC, "AxcSignalGetCapturePos");
        AxcSignalSetEncReverse                        = (funcAxcSignalSetEncReverse *)GetProcAddress(g_hAXC, "AxcSignalSetEncReverse");
        AxcSignalGetEncReverse                        = (funcAxcSignalGetEncReverse *)GetProcAddress(g_hAXC, "AxcSignalGetEncReverse");
        AxcSignalSetEncSource                         = (funcAxcSignalSetEncSource *)GetProcAddress(g_hAXC, "AxcSignalSetEncSource");
        AxcSignalGetEncSource                         = (funcAxcSignalGetEncSource *)GetProcAddress(g_hAXC, "AxcSignalGetEncSource");
        AxcSignalWriteOutput                          = (funcAxcSignalWriteOutput *)GetProcAddress(g_hAXC, "AxcSignalWriteOutput");
        AxcSignalReadOutput                           = (funcAxcSignalReadOutput *)GetProcAddress(g_hAXC, "AxcSignalReadOutput");
        AxcSignalWriteOutputBit                       = (funcAxcSignalWriteOutputBit *)GetProcAddress(g_hAXC, "AxcSignalWriteOutputBit");
        AxcSignalReadOutputBit                        = (funcAxcSignalReadOutputBit *)GetProcAddress(g_hAXC, "AxcSignalReadOutputBit");
        AxcSignalReadInput                            = (funcAxcSignalReadInput *)GetProcAddress(g_hAXC, "AxcSignalReadInput");
        AxcSignalReadInputBit                         = (funcAxcSignalReadInputBit *)GetProcAddress(g_hAXC, "AxcSignalReadInputBit");

        AxcMotSetMoveUnitPerPulse                     = (funcAxcMotSetMoveUnitPerPulse *)GetProcAddress(g_hAXC, "AxcMotSetMoveUnitPerPulse");
        AxcMotGetMoveUnitPerPulse                     = (funcAxcMotGetMoveUnitPerPulse *)GetProcAddress(g_hAXC, "AxcMotGetMoveUnitPerPulse");
        
        AxcStatusGetActPos                            = (funcAxcStatusGetActPos *)GetProcAddress(g_hAXC, "AxcStatusGetActPos");
        AxcStatusSetActPos                            = (funcAxcStatusSetActPos *)GetProcAddress(g_hAXC, "AxcStatusSetActPos");
        AxcStatusGetChannel                           = (funcAxcStatusGetChannel *)GetProcAddress(g_hAXC, "AxcStatusGetChannel");

        AxcTriggerSetFunction                         = (funcAxcTriggerSetFunction *)GetProcAddress(g_hAXC, "AxcTriggerSetFunction");
        AxcTriggerGetFunction                         = (funcAxcTriggerGetFunction *)GetProcAddress(g_hAXC, "AxcTriggerGetFunction");
        AxcTriggerSetNotchPos                         = (funcAxcTriggerSetNotchPos *)GetProcAddress(g_hAXC, "AxcTriggerSetNotchPos");
        AxcTriggerGetNotchPos                         = (funcAxcTriggerGetNotchPos *)GetProcAddress(g_hAXC, "AxcTriggerGetNotchPos");
        AxcTriggerSetOutput                           = (funcAxcTriggerSetOutput *)GetProcAddress(g_hAXC, "AxcTriggerSetOutput");

        AxcTriggerSetNotchPos                         = (funcAxcTriggerSetNotchPos *)GetProcAddress(g_hAXC, "AxcTriggerSetNotchPos");
        AxcTriggerGetNotchPos                         = (funcAxcTriggerGetNotchPos *)GetProcAddress(g_hAXC, "AxcTriggerGetNotchPos");
        AxcTriggerSetBlockLowerPos                    = (funcAxcTriggerSetBlockLowerPos *)GetProcAddress(g_hAXC, "AxcTriggerSetBlockLowerPos");
        AxcTriggerGetBlockLowerPos                    = (funcAxcTriggerGetBlockLowerPos *)GetProcAddress(g_hAXC, "AxcTriggerGetBlockLowerPos");
        AxcTriggerSetBlockUpperPos                    = (funcAxcTriggerSetBlockUpperPos *)GetProcAddress(g_hAXC, "AxcTriggerSetBlockUpperPos");
        AxcTriggerGetBlockUpperPos                    = (funcAxcTriggerGetBlockUpperPos *)GetProcAddress(g_hAXC, "AxcTriggerGetBlockUpperPos");
        AxcTriggerSetPosPeriod                        = (funcAxcTriggerSetPosPeriod *)GetProcAddress(g_hAXC, "AxcTriggerSetPosPeriod");
        AxcTriggerGetPosPeriod                        = (funcAxcTriggerGetPosPeriod *)GetProcAddress(g_hAXC, "AxcTriggerGetPosPeriod");
        AxcTriggerSetDirectionCheck                   = (funcAxcTriggerSetDirectionCheck *)GetProcAddress(g_hAXC, "AxcTriggerSetDirectionCheck");
        AxcTriggerGetDirectionCheck                   = (funcAxcTriggerGetDirectionCheck *)GetProcAddress(g_hAXC, "AxcTriggerGetDirectionCheck");
        AxcTriggerSetBlock                            = (funcAxcTriggerSetBlock *)GetProcAddress(g_hAXC, "AxcTriggerSetBlock");
        AxcTriggerGetBlock                            = (funcAxcTriggerGetBlock *)GetProcAddress(g_hAXC, "AxcTriggerGetBlock");
        AxcTriggerSetTime                             = (funcAxcTriggerSetTime *)GetProcAddress(g_hAXC, "AxcTriggerSetTime");
        AxcTriggerGetTime                             = (funcAxcTriggerGetTime *)GetProcAddress(g_hAXC, "AxcTriggerGetTime");
        AxcTriggerSetLevel                            = (funcAxcTriggerSetLevel *)GetProcAddress(g_hAXC, "AxcTriggerSetLevel");
        AxcTriggerGetLevel                            = (funcAxcTriggerGetLevel *)GetProcAddress(g_hAXC, "AxcTriggerGetLevel");
        AxcTriggerSetFreq                             = (funcAxcTriggerSetFreq *)GetProcAddress(g_hAXC, "AxcTriggerSetFreq");
        AxcTriggerGetFreq                             = (funcAxcTriggerGetFreq *)GetProcAddress(g_hAXC, "AxcTriggerGetFreq");
        AxcTriggerSetEnable                           = (funcAxcTriggerSetEnable *)GetProcAddress(g_hAXC, "AxcTriggerSetEnable");
        AxcTriggerGetEnable                           = (funcAxcTriggerGetEnable *)GetProcAddress(g_hAXC, "AxcTriggerGetEnable");
        AxcTriggerReadAbsRamData                      = (funcAxcTriggerReadAbsRamData *)GetProcAddress(g_hAXC, "AxcTriggerReadAbsRamData");
        AxcTriggerWriteAbsRamData                     = (funcAxcTriggerWriteAbsRamData *)GetProcAddress(g_hAXC, "AxcTriggerWriteAbsRamData");
        AxcTriggerSetAbs                              = (funcAxcTriggerSetAbs *)GetProcAddress(g_hAXC, "AxcTriggerSetAbs");

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL FreeAXC()
{
    if (g_hAXC)
    {
        FreeLibrary(g_hAXC);
        g_hAXC     = NULL;

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}