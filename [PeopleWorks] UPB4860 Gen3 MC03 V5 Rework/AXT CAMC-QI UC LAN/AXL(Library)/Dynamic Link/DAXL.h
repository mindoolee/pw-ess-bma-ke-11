#ifndef __AXT_DAXL_H__
#define __AXT_DAXL_H__

//#include "AXHS.h"
#include "../../AXL(Library)/C, C++/AXHS.h"

typedef DWORD   PASCAL EXPORT funcAxlOpen(long lIrqNo);
typedef DWORD   PASCAL EXPORT funcAxlOpenNoReset(long lIrqNo);
typedef BOOL    PASCAL EXPORT funcAxlClose();
typedef BOOL    PASCAL EXPORT funcAxlIsOpened();
typedef DWORD   PASCAL EXPORT funcAxlInterruptEnable();
typedef DWORD   PASCAL EXPORT funcAxlInterruptDisable();
typedef DWORD   PASCAL EXPORT funcAxlGetBoardCount(long *lpBoardCount);
typedef DWORD   PASCAL EXPORT funcAxlGetLibVersion(char *szVersion);
typedef DWORD   PASCAL EXPORT funcAxlGetModuleNodeStatus(long lBoardNo, long lModulePos);
typedef DWORD   PASCAL EXPORT funcAxlGetBoardStatus(long lBoardNo);
typedef DWORD   PASCAL EXPORT funcAxlGetLockMode(long lBoardNO, WORD *wpLockMode);
typedef DWORD   PASCAL EXPORT funcAxlSetLogLevel(DWORD uLevel);
typedef DWORD   PASCAL EXPORT funcAxlGetLogLevel(DWORD *upLevel);

typedef DWORD   PASCAL EXPORT funcAxlScanStart(long lBoardNo, long lNet);
typedef DWORD   PASCAL EXPORT funcAxlBoardConnect(long lBoardNo, long lNet);
typedef DWORD   PASCAL EXPORT funcAxlBoardDisconnect(long lBoardNo, long lNet);
//---------------------------------------------------------//
extern funcAxlOpen                *AxlOpen;
extern funcAxlOpenNoReset         *AxlOpenNoReset;
extern funcAxlClose               *AxlClose;
extern funcAxlIsOpened            *AxlIsOpened;
extern funcAxlInterruptEnable     *AxlInterruptEnable;
extern funcAxlInterruptDisable    *AxlInterruptDisable;
extern funcAxlGetBoardCount       *AxlGetBoardCount;
extern funcAxlGetLibVersion       *AxlGetLibVersion;
extern funcAxlGetModuleNodeStatus *AxlGetModuleNodeStatus; 
extern funcAxlGetBoardStatus      *AxlGetBoardStatus; 
extern funcAxlGetLockMode         *AxlGetLockMode;
extern funcAxlSetLogLevel         *AxlSetLogLevel;
extern funcAxlGetLogLevel         *AxlGetLogLevel;

extern funcAxlGetLogLevel         *AxlScanStart;
extern funcAxlGetLogLevel         *AxlBoardConnect;
extern funcAxlGetLogLevel         *AxlBoardDisconnect;

BOOL LoadAXL();
BOOL FreeAXL();

#endif    __AXT_DAXL_H__
