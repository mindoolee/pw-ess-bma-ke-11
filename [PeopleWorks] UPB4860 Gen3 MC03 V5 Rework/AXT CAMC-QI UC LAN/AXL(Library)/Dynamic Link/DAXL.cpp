#include "stdafx.h"
#include "DAXL.h"

HINSTANCE    g_hAXL = NULL;

funcAxlOpen                     *AxlOpen;
funcAxlOpenNoReset              *AxlOpenNoReset;
funcAxlClose                    *AxlClose;
funcAxlIsOpened                 *AxlIsOpened;
funcAxlInterruptEnable          *AxlInterruptEnable;
funcAxlInterruptDisable         *AxlInterruptDisable;
funcAxlGetBoardCount            *AxlGetBoardCount;
funcAxlGetLibVersion            *AxlGetLibVersion;
funcAxlGetModuleNodeStatus      *AxlGetModuleNodeStatus;
funcAxlGetBoardStatus           *AxlGetBoardStatus;
funcAxlGetLockMode              *AxlGetLockMode;
funcAxlSetLogLevel              *AxlSetLogLevel;
funcAxlGetLogLevel              *AxlGetLogLevel;
funcAxlScanStart                *AxlScanStart;
funcAxlBoardConnect             *AxlBoardConnect;
funcAxlBoardDisconnect          *AxlBoardDisconnect;

BOOL LoadAXL()
{
    g_hAXL    = LoadLibrary("Axl.dll");

    if (g_hAXL)
    {
        AxlOpen                 = (funcAxlOpen *)GetProcAddress(g_hAXL, "AxlOpen");
        AxlOpenNoReset          = (funcAxlOpenNoReset *)GetProcAddress(g_hAXL, "AxlOpenNoReset");
        AxlClose                = (funcAxlClose *)GetProcAddress(g_hAXL, "AxlClose");
        AxlIsOpened             = (funcAxlIsOpened *)GetProcAddress(g_hAXL, "AxlIsOpened");
        AxlInterruptEnable      = (funcAxlInterruptEnable *)GetProcAddress(g_hAXL, "AxlInterruptEnable");
        AxlInterruptDisable     = (funcAxlInterruptDisable *)GetProcAddress(g_hAXL, "AxlInterruptDisable");
        AxlGetBoardCount        = (funcAxlGetBoardCount *)GetProcAddress(g_hAXL, "AxlGetBoardCount");
        AxlGetLibVersion        = (funcAxlGetLibVersion *)GetProcAddress(g_hAXL, "AxlGetLibVersion");
        AxlGetModuleNodeStatus  = (funcAxlGetModuleNodeStatus *)GetProcAddress(g_hAXL, "AxlGetModuleNodeStatus");
        AxlGetBoardStatus       = (funcAxlGetBoardStatus *)GetProcAddress(g_hAXL, "AxlGetBoardStatus");
        AxlGetLockMode          = (funcAxlGetLockMode *)GetProcAddress(g_hAXL, "AxlGetLockMode");
        AxlSetLogLevel          = (funcAxlSetLogLevel *)GetProcAddress(g_hAXL, "AxlSetLogLevel");
        AxlGetLogLevel          = (funcAxlGetLogLevel *)GetProcAddress(g_hAXL, "AxlGetLogLevel");

		AxlScanStart            = (funcAxlScanStart *)GetProcAddress(g_hAXL, "AxlScanStart");
		AxlBoardConnect         = (funcAxlBoardConnect *)GetProcAddress(g_hAXL, "AxlBoardConnect");
		AxlBoardDisconnect      = (funcAxlBoardDisconnect *)GetProcAddress(g_hAXL, "AxlBoardDisconnect");
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL FreeAXL()
{
    if (g_hAXL)
    {
        FreeLibrary(g_hAXL);
        g_hAXL     = NULL;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
