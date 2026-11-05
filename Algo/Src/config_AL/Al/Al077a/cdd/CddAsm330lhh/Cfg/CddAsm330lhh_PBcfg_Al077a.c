/*
*****************************************************************************
* (C) Automotive Lighting Italy S.r.l.
*     Venaria Reale (TO), Italy
*****************************************************************************
* File: CddAsm330lhh_PBcfg_Al077a.c
* Description:
*   Default post-build configuration instance for ASM330LHH CDD.
*****************************************************************************
*/

#include <Std_Types.h>
#include <../Api/CddAsm330lhh.h>

#define ctadCddAsm330lhh_START_SEC_CONST_ROM_UNSPECIFIED
#include <../Cfg/CddAsm330lhh_MemMap.h>

/*
*****************************************************************************
* Object: CddAsm330lhh_Config_Default
* Purpose:
*   Safe default configuration used as a baseline during integration.
*****************************************************************************
*/
const CddAsm330lhh_ConfigType CddAsm330lhh_Config_Default =
{
  TRUE,
  TRUE,
  {
    CDDASM330LHH_ODR_104HZ,
    CDDASM330LHH_ACCEL_FS_4G
  },
  {
    CDDASM330LHH_ODR_104HZ,
    CDDASM330LHH_GYRO_FS_500DPS
  }
};

#define ctadCddAsm330lhh_STOP_SEC_CONST_ROM_UNSPECIFIED
#include <../Cfg/CddAsm330lhh_MemMap.h>
