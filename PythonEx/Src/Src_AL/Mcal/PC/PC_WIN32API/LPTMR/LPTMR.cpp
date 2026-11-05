#include <LPTMR.h>
#include <Cfg/Cfg.h>
#include <stddef.h>
#include <string.h>
#include <UtilUtility.h>


namespace
{
  bool& LPTMR_InitHasBeenCalled()
  {
    static bool boLPTMR_InitHasBeenCalled;

    return boLPTMR_InitHasBeenCalled;
  }
}

static uint32 ulLPTMR0_MicrosecondTimer;

void LPTMR_INIT(const LPTMR_ConfigType*)
{
  LPTMR_InitHasBeenCalled() = true;
}

#ifndef UNIT_TEST // Not Applicable for UNIT TEST
uint32 LPTMR0_GetTimeElapsed(const uint32 ulStartValue)
{
  return ulLPTMR0_MicrosecondTimer - ulStartValue;
}
#endif

