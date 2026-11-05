/*
*****************************************************************************
* (C) Automotive Lighting Italy S.r.l.
*     Venaria Reale (TO), Italy
*****************************************************************************
* File: CddAsm330lhh_Eft.h
* Description:
*   EFT-oriented calibration and ECU-variant structures used by the module.
*****************************************************************************
*/

#ifndef CDD_ASM330LHH_EFT_2026_07_07_H_
#define CDD_ASM330LHH_EFT_2026_07_07_H_

#include <Std_Types.h>

/*
*****************************************************************************
* Structure: CddAsm330lhh_EftCalibType
* Purpose  : Static offsets used to align sensor output to vehicle coordinates.
*****************************************************************************
*/
typedef struct
{
  sint16 AccelBiasX_mg;
  sint16 AccelBiasY_mg;
  sint16 AccelBiasZ_mg;
  sint16 GyroBiasX_mdps;
  sint16 GyroBiasY_mdps;
  sint16 GyroBiasZ_mdps;
} CddAsm330lhh_EftCalibType;

/*
*****************************************************************************
* Structure: CddAsm330lhh_EftEcuVarCfgType
* Purpose  : Variant-specific mounting and reserved configuration fields.
*****************************************************************************
*/
typedef struct
{
  uint8 SensorMountingId;
  uint8 Reserved0;
  uint8 Reserved1;
  uint8 Reserved2;
} CddAsm330lhh_EftEcuVarCfgType;

#endif /* CDD_ASM330LHH_EFT_2026_07_07_H_ */
