#include "stdafx.h"
#include "DAXD.h"

HINSTANCE    g_hAXD = NULL;

funcAxdInfoIsDIOModule                  *AxdInfoIsDIOModule;
funcAxdInfoGetModuleNo                  *AxdInfoGetModuleNo;
funcAxdInfoGetModuleCount               *AxdInfoGetModuleCount;
funcAxdInfoGetInputCount                *AxdInfoGetInputCount;
funcAxdInfoGetOutputCount               *AxdInfoGetOutputCount;
funcAxdInfoGetModule                    *AxdInfoGetModule;
funcAxdInfoGetModuleStatus              *AxdInfoGetModuleStatus;
funcAxdiInterruptSetModule              *AxdiInterruptSetModule;
funcAxdiInterruptSetModuleEnable        *AxdiInterruptSetModuleEnable;
funcAxdiInterruptGetModuleEnable        *AxdiInterruptGetModuleEnable;
funcAxdiInterruptRead                   *AxdiInterruptRead;
funcAxdiInterruptEdgeSetBit             *AxdiInterruptEdgeSetBit;
funcAxdiInterruptEdgeSetByte            *AxdiInterruptEdgeSetByte;
funcAxdiInterruptEdgeSetWord            *AxdiInterruptEdgeSetWord;
funcAxdiInterruptEdgeSetDword           *AxdiInterruptEdgeSetDword;
funcAxdiInterruptEdgeGetBit             *AxdiInterruptEdgeGetBit;
funcAxdiInterruptEdgeGetByte            *AxdiInterruptEdgeGetByte;
funcAxdiInterruptEdgeGetWord            *AxdiInterruptEdgeGetWord;
funcAxdiInterruptEdgeGetDword           *AxdiInterruptEdgeGetDword;
funcAxdiInterruptEdgeSet                *AxdiInterruptEdgeSet;
funcAxdiInterruptEdgeGet                *AxdiInterruptEdgeGet;
funcAxdiLevelSetInportBit               *AxdiLevelSetInportBit;
funcAxdiLevelSetInportByte              *AxdiLevelSetInportByte;
funcAxdiLevelSetInportWord              *AxdiLevelSetInportWord;
funcAxdiLevelSetInportDword             *AxdiLevelSetInportDword;
funcAxdiLevelGetInportBit               *AxdiLevelGetInportBit;
funcAxdiLevelGetInportByte              *AxdiLevelGetInportByte;
funcAxdiLevelGetInportWord              *AxdiLevelGetInportWord;
funcAxdiLevelGetInportDword             *AxdiLevelGetInportDword;
funcAxdiLevelSetInport                  *AxdiLevelSetInport;
funcAxdiLevelGetInport                  *AxdiLevelGetInport;
funcAxdoLevelSetOutportBit              *AxdoLevelSetOutportBit;
funcAxdoLevelSetOutportByte             *AxdoLevelSetOutportByte;
funcAxdoLevelSetOutportWord             *AxdoLevelSetOutportWord;
funcAxdoLevelSetOutportDword            *AxdoLevelSetOutportDword;
funcAxdoLevelGetOutportBit              *AxdoLevelGetOutportBit;
funcAxdoLevelGetOutportByte             *AxdoLevelGetOutportByte;
funcAxdoLevelGetOutportWord             *AxdoLevelGetOutportWord;
funcAxdoLevelGetOutportDword            *AxdoLevelGetOutportDword;
funcAxdoLevelSetOutport                 *AxdoLevelSetOutport;
funcAxdoLevelGetOutport                 *AxdoLevelGetOutport;
funcAxdoWriteOutport                    *AxdoWriteOutport;
funcAxdoWriteOutportBit                 *AxdoWriteOutportBit;
funcAxdoWriteOutportByte                *AxdoWriteOutportByte;
funcAxdoWriteOutportWord                *AxdoWriteOutportWord;
funcAxdoWriteOutportDword               *AxdoWriteOutportDword;
funcAxdoReadOutport                     *AxdoReadOutport;
funcAxdoReadOutportBit                  *AxdoReadOutportBit;
funcAxdoReadOutportByte                 *AxdoReadOutportByte;
funcAxdoReadOutportWord                 *AxdoReadOutportWord;
funcAxdoReadOutportDword                *AxdoReadOutportDword;
funcAxdiReadInport                      *AxdiReadInport;
funcAxdiReadInportBit                   *AxdiReadInportBit;
funcAxdiReadInportByte                  *AxdiReadInportByte;
funcAxdiReadInportWord                  *AxdiReadInportWord;
funcAxdiReadInportDword                 *AxdiReadInportDword;
funcAxdReadExtInportBit                 *AxdReadExtInportBit;
funcAxdReadExtInportByte                *AxdReadExtInportByte;
funcAxdReadExtInportWord                *AxdReadExtInportWord;
funcAxdReadExtInportDword               *AxdReadExtInportDword;
funcAxdReadExtOutportBit                *AxdReadExtOutportBit;
funcAxdReadExtOutportByte               *AxdReadExtOutportByte;
funcAxdReadExtOutportWord               *AxdReadExtOutportWord;
funcAxdReadExtOutportDword              *AxdReadExtOutportDword;
funcAxdWriteExtOutportBit               *AxdWriteExtOutportBit;
funcAxdWriteExtOutportByte              *AxdWriteExtOutportByte;
funcAxdWriteExtOutportWord              *AxdWriteExtOutportWord;
funcAxdWriteExtOutportDword             *AxdWriteExtOutportDword;
funcAxdLevelSetExtportBit               *AxdLevelSetExtportBit;
funcAxdLevelSetExtportByte              *AxdLevelSetExtportByte;
funcAxdLevelSetExtportWord              *AxdLevelSetExtportWord;
funcAxdLevelSetExtportDWord             *AxdLevelSetExtportDWord;
funcAxdLevelGetExtportBit               *AxdLevelGetExtportBit;
funcAxdLevelGetExtportByte              *AxdLevelGetExtportByte;
funcAxdLevelGetExtportWord              *AxdLevelGetExtportWord;
funcAxdLevelGetExtportDword             *AxdLevelGetExtportDword;

funcAxdiIsPulseOn                       *AxdiIsPulseOn;
funcAxdiIsPulseOff                      *AxdiIsPulseOff;
funcAxdiIsOn                            *AxdiIsOn;
funcAxdiIsOff                           *AxdiIsOff;
funcAxdoOutPulseOn                      *AxdoOutPulseOn;
funcAxdoOutPulseOff                     *AxdoOutPulseOff;
funcAxdoToggleStart                     *AxdoToggleStart;
funcAxdoToggleStop                      *AxdoToggleStop;
funcAxdoSetNetworkErrorAct              *AxdoSetNetworkErrorAct;
funcAxdSetContactNum                    *AxdSetContactNum;
funcAxdGetContactNum                    *AxdGetContactNum;


BOOL LoadAXD()
{
    g_hAXD    = LoadLibrary("Axl.dll");
    if (g_hAXD)
    {
        AxdInfoIsDIOModule              = (funcAxdInfoIsDIOModule *)GetProcAddress(g_hAXD, "AxdInfoIsDIOModule");
        AxdInfoGetModuleNo              = (funcAxdInfoGetModuleNo *)GetProcAddress(g_hAXD, "AxdInfoGetModuleNo");
        AxdInfoGetModuleCount           = (funcAxdInfoGetModuleCount *)GetProcAddress(g_hAXD, "AxdInfoGetModuleCount");
        AxdInfoGetInputCount            = (funcAxdInfoGetInputCount *)GetProcAddress(g_hAXD, "AxdInfoGetInputCount");
        AxdInfoGetOutputCount           = (funcAxdInfoGetOutputCount *)GetProcAddress(g_hAXD, "AxdInfoGetOutputCount");
        AxdInfoGetModule                = (funcAxdInfoGetModule *)GetProcAddress(g_hAXD, "AxdInfoGetModule");
        AxdInfoGetModuleStatus          = (funcAxdInfoGetModuleStatus *)GetProcAddress(g_hAXD, "AxdInfoGetModuleStatus");
        AxdiInterruptSetModule          = (funcAxdiInterruptSetModule *)GetProcAddress(g_hAXD, "AxdiInterruptSetModule");
        AxdiInterruptSetModuleEnable    = (funcAxdiInterruptSetModuleEnable *)GetProcAddress(g_hAXD, "AxdiInterruptSetModuleEnable");
        AxdiInterruptGetModuleEnable    = (funcAxdiInterruptGetModuleEnable *)GetProcAddress(g_hAXD, "AxdiInterruptGetModuleEnable");
        AxdiInterruptRead               = (funcAxdiInterruptRead *)GetProcAddress(g_hAXD, "AxdiInterruptRead");
        AxdiInterruptEdgeSetBit         = (funcAxdiInterruptEdgeSetBit *)GetProcAddress(g_hAXD, "AxdiInterruptEdgeSetBit");
        AxdiInterruptEdgeSetByte        = (funcAxdiInterruptEdgeSetByte *)GetProcAddress(g_hAXD, "AxdiInterruptEdgeSetByte");
        AxdiInterruptEdgeSetWord        = (funcAxdiInterruptEdgeSetWord *)GetProcAddress(g_hAXD, "AxdiInterruptEdgeSetWord");
        AxdiInterruptEdgeSetDword       = (funcAxdiInterruptEdgeSetDword *)GetProcAddress(g_hAXD, "AxdiInterruptEdgeSetDword");
        AxdiInterruptEdgeGetBit         = (funcAxdiInterruptEdgeGetBit *)GetProcAddress(g_hAXD, "AxdiInterruptEdgeGetBit");
        AxdiInterruptEdgeGetByte        = (funcAxdiInterruptEdgeGetByte *)GetProcAddress(g_hAXD, "AxdiInterruptEdgeGetByte");
        AxdiInterruptEdgeGetWord        = (funcAxdiInterruptEdgeGetWord *)GetProcAddress(g_hAXD, "AxdiInterruptEdgeGetWord");
        AxdiInterruptEdgeGetDword       = (funcAxdiInterruptEdgeGetDword *)GetProcAddress(g_hAXD, "AxdiInterruptEdgeGetDword");
        AxdiInterruptEdgeSet            = (funcAxdiInterruptEdgeSet *)GetProcAddress(g_hAXD, "AxdiInterruptEdgeSet");
        AxdiInterruptEdgeGet            = (funcAxdiInterruptEdgeGet *)GetProcAddress(g_hAXD, "AxdiInterruptEdgeGet");
        AxdiLevelSetInportBit           = (funcAxdiLevelSetInportBit *)GetProcAddress(g_hAXD, "AxdiLevelSetInportBit");
        AxdiLevelSetInportByte          = (funcAxdiLevelSetInportByte *)GetProcAddress(g_hAXD, "AxdiLevelSetInportByte");
        AxdiLevelSetInportWord          = (funcAxdiLevelSetInportWord *)GetProcAddress(g_hAXD, "AxdiLevelSetInportWord");
        AxdiLevelSetInportDword         = (funcAxdiLevelSetInportDword *)GetProcAddress(g_hAXD, "AxdiLevelSetInportDword");
        AxdiLevelGetInportBit           = (funcAxdiLevelGetInportBit *)GetProcAddress(g_hAXD, "AxdiLevelGetInportBit");
        AxdiLevelGetInportByte          = (funcAxdiLevelGetInportByte *)GetProcAddress(g_hAXD, "AxdiLevelGetInportByte");
        AxdiLevelGetInportWord          = (funcAxdiLevelGetInportWord *)GetProcAddress(g_hAXD, "AxdiLevelGetInportWord");
        AxdiLevelGetInportDword         = (funcAxdiLevelGetInportDword *)GetProcAddress(g_hAXD, "AxdiLevelGetInportDword");
        AxdiLevelSetInport              = (funcAxdiLevelSetInport *)GetProcAddress(g_hAXD, "AxdiLevelSetInport");
        AxdiLevelGetInport              = (funcAxdiLevelGetInport *)GetProcAddress(g_hAXD, "AxdiLevelGetInport");
        AxdoLevelSetOutportBit          = (funcAxdoLevelSetOutportBit *)GetProcAddress(g_hAXD, "AxdoLevelSetOutportBit");
        AxdoLevelSetOutportByte         = (funcAxdoLevelSetOutportByte *)GetProcAddress(g_hAXD, "AxdoLevelSetOutportByte");
        AxdoLevelSetOutportWord         = (funcAxdoLevelSetOutportWord *)GetProcAddress(g_hAXD, "AxdoLevelSetOutportWord");
        AxdoLevelSetOutportDword        = (funcAxdoLevelSetOutportDword *)GetProcAddress(g_hAXD, "AxdoLevelSetOutportDword");
        AxdoLevelGetOutportBit          = (funcAxdoLevelGetOutportBit *)GetProcAddress(g_hAXD, "AxdoLevelGetOutportBit");
        AxdoLevelGetOutportByte         = (funcAxdoLevelGetOutportByte *)GetProcAddress(g_hAXD, "AxdoLevelGetOutportByte");
        AxdoLevelGetOutportWord         = (funcAxdoLevelGetOutportWord *)GetProcAddress(g_hAXD, "AxdoLevelGetOutportWord");
        AxdoLevelGetOutportDword        = (funcAxdoLevelGetOutportDword *)GetProcAddress(g_hAXD, "AxdoLevelGetOutportDword");
        AxdoLevelSetOutport             = (funcAxdoLevelSetOutport *)GetProcAddress(g_hAXD, "AxdoLevelSetOutport");
        AxdoLevelGetOutport             = (funcAxdoLevelGetOutport *)GetProcAddress(g_hAXD, "AxdoLevelGetOutport");
        AxdoWriteOutport                = (funcAxdoWriteOutport *)GetProcAddress(g_hAXD, "AxdoWriteOutport");
        AxdoWriteOutportBit             = (funcAxdoWriteOutportBit *)GetProcAddress(g_hAXD, "AxdoWriteOutportBit");
        AxdoWriteOutportByte            = (funcAxdoWriteOutportByte *)GetProcAddress(g_hAXD, "AxdoWriteOutportByte");
        AxdoWriteOutportWord            = (funcAxdoWriteOutportWord *)GetProcAddress(g_hAXD, "AxdoWriteOutportWord");
        AxdoWriteOutportDword           = (funcAxdoWriteOutportDword *)GetProcAddress(g_hAXD, "AxdoWriteOutportDword");
        AxdoReadOutport                 = (funcAxdoReadOutport *)GetProcAddress(g_hAXD, "AxdoReadOutport");
        AxdoReadOutportBit              = (funcAxdoReadOutportBit *)GetProcAddress(g_hAXD, "AxdoReadOutportBit");
        AxdoReadOutportByte             = (funcAxdoReadOutportByte *)GetProcAddress(g_hAXD, "AxdoReadOutportByte");
        AxdoReadOutportWord             = (funcAxdoReadOutportWord *)GetProcAddress(g_hAXD, "AxdoReadOutportWord");
        AxdoReadOutportDword            = (funcAxdoReadOutportDword *)GetProcAddress(g_hAXD, "AxdoReadOutportDword");
        AxdiReadInport                  = (funcAxdiReadInport *)GetProcAddress(g_hAXD, "AxdiReadInport");
        AxdiReadInportBit               = (funcAxdiReadInportBit *)GetProcAddress(g_hAXD, "AxdiReadInportBit");
        AxdiReadInportByte              = (funcAxdiReadInportByte *)GetProcAddress(g_hAXD, "AxdiReadInportByte");
        AxdiReadInportWord              = (funcAxdiReadInportWord *)GetProcAddress(g_hAXD, "AxdiReadInportWord");
        AxdiReadInportDword             = (funcAxdiReadInportDword *)GetProcAddress(g_hAXD, "AxdiReadInportDword");
        AxdReadExtInportBit             = (funcAxdReadExtInportBit *)GetProcAddress(g_hAXD, "AxdReadExtInportBit");
        AxdReadExtInportByte            = (funcAxdReadExtInportByte *)GetProcAddress(g_hAXD, "AxdReadExtInportByte");
        AxdReadExtInportWord            = (funcAxdReadExtInportWord *)GetProcAddress(g_hAXD, "AxdReadExtInportWord");
        AxdReadExtInportDword           = (funcAxdReadExtInportDword *)GetProcAddress(g_hAXD, "AxdReadExtInportDword");
        AxdReadExtOutportBit            = (funcAxdReadExtOutportBit *)GetProcAddress(g_hAXD, "AxdReadExtOutportBit");
        AxdReadExtOutportByte           = (funcAxdReadExtOutportByte *)GetProcAddress(g_hAXD, "AxdReadExtOutportByte");
        AxdReadExtOutportWord           = (funcAxdReadExtOutportWord *)GetProcAddress(g_hAXD, "AxdReadExtOutportWord");
        AxdReadExtOutportDword          = (funcAxdReadExtOutportDword *)GetProcAddress(g_hAXD, "AxdReadExtOutportDword");
        AxdWriteExtOutportBit           = (funcAxdWriteExtOutportBit *)GetProcAddress(g_hAXD, "AxdWriteExtOutportBit");
        AxdWriteExtOutportByte          = (funcAxdWriteExtOutportByte *)GetProcAddress(g_hAXD, "AxdWriteExtOutportByte");
        AxdWriteExtOutportWord          = (funcAxdWriteExtOutportWord *)GetProcAddress(g_hAXD, "AxdWriteExtOutportWord");
        AxdWriteExtOutportDword         = (funcAxdWriteExtOutportDword *)GetProcAddress(g_hAXD, "AxdWriteExtOutportDword");
        AxdLevelSetExtportBit           = (funcAxdLevelSetExtportBit *)GetProcAddress(g_hAXD, "AxdLevelSetExtportBit");
        AxdLevelSetExtportByte          = (funcAxdLevelSetExtportByte *)GetProcAddress(g_hAXD, "AxdLevelSetExtportByte");
        AxdLevelSetExtportWord          = (funcAxdLevelSetExtportWord *)GetProcAddress(g_hAXD, "AxdLevelSetExtportWord");
        AxdLevelSetExtportDWord         = (funcAxdLevelSetExtportDWord *)GetProcAddress(g_hAXD, "AxdLevelSetExtportDWord");
        AxdLevelGetExtportBit           = (funcAxdLevelGetExtportBit *)GetProcAddress(g_hAXD, "AxdLevelGetExtportBit");
        AxdLevelGetExtportByte          = (funcAxdLevelGetExtportByte *)GetProcAddress(g_hAXD, "AxdLevelGetExtportByte");
        AxdLevelGetExtportWord          = (funcAxdLevelGetExtportWord *)GetProcAddress(g_hAXD, "AxdLevelGetExtportWord");
        AxdLevelGetExtportDword         = (funcAxdLevelGetExtportDword *)GetProcAddress(g_hAXD, "AxdLevelGetExtportDword");
        AxdiIsPulseOn                   = (funcAxdiIsPulseOn *)GetProcAddress(g_hAXD, "AxdiIsPulseOn");
        AxdiIsPulseOff                  = (funcAxdiIsPulseOff *)GetProcAddress(g_hAXD, "AxdiIsPulseOff");
        AxdiIsOn                        = (funcAxdiIsOn    *)GetProcAddress(g_hAXD, "AxdiIsOn");
        AxdiIsOff                       = (funcAxdiIsOff *)GetProcAddress(g_hAXD, "AxdiIsOff");
        AxdoOutPulseOn                  = (funcAxdoOutPulseOn *)GetProcAddress(g_hAXD, "AxdoOutPulseOn");
        AxdoOutPulseOff                 = (funcAxdoOutPulseOff *)GetProcAddress(g_hAXD, "AxdoOutPulseOff");
        AxdoToggleStart                 = (funcAxdoToggleStart *)GetProcAddress(g_hAXD, "AxdoToggleStart");
        AxdoToggleStop                  = (funcAxdoToggleStop *)GetProcAddress(g_hAXD, "AxdoToggleStop");
        AxdoSetNetworkErrorAct          = (funcAxdoSetNetworkErrorAct *)GetProcAddress(g_hAXD, "AxdoSetNetworkErrorAct");
        AxdSetContactNum                = (funcAxdSetContactNum *)GetProcAddress(g_hAXD, "AxdSetContactNum");
        AxdGetContactNum                = (funcAxdGetContactNum *)GetProcAddress(g_hAXD, "AxdGetContactNum");
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL FreeAXD()
{
    if (g_hAXD)
    {
        FreeLibrary(g_hAXD);
        g_hAXD     = NULL;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
