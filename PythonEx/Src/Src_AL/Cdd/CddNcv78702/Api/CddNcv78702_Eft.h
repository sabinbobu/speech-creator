//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file   CddNcv78702_Eft.h
///
/// \brief  CddNcv78702 Eft data (calibration and configuration)
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef CDD_NCV78702_EFT_2021_03_25_H_
#define CDD_NCV78702_EFT_2021_03_25_H_


#include <../Cfg/CddNcv78702_Cfg.h>


// Possible configurations: single/dual
#define CDDNCV78702_EFT_BoosterNone     0u
#define CDDNCV78702_EFT_BoosterSingle   1u
#define CDDNCV78702_EFT_BoosterDual     2u


typedef struct
{
  uint16 unVFactor;  // mV / digit
  sint16 nVOffset;   // mV
  uint32 ulReserved;
} tCddNcv78702_Eft_Calib;


typedef struct
{
  uint8  ucBoostCfg;   // booster configuration
  uint8  ucVariant;    // driver variant
  uint16 unVFactor;    // mV / digit
  sint16 nVOffset;     // mV
  uint8  ucReserved1;  // driver variant
  uint8  ucReserved2;
} tCddNcv78702_Eft_EcuVarCfg;



#endif // CDD_NCV78702_EFT_2021_03_25_H_
