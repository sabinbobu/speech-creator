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
/// \file   CddTps92520_Eft.h
///
/// \brief  CddTps92520 Eft data (calibration and configuration)
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef CDD_TPS92520_EFT_2021_01_22_H_
#define CDD_TPS92520_EFT_2021_01_22_H_


#include <Std_Types.h>
#include <../Cfg/CddTps92520_Cfg.h>


typedef struct
{
  uint16 unIFactor;
  sint16 nIOffset;
} tCddTps92520_CalDrv;

typedef struct
{
  uint32 ulReserved;
  tCddTps92520_CalDrv aDrv[2];
} tCddTps92520_Eft_Calib;


typedef struct
{
  uint8  ucAssignedOutput;
  uint8  ucPmax;
  uint16 unImax;
  uint16 unImin;
  uint8  ucReserved1;
  uint8  ucReserved2;
} tCddTps92520_DrvCfg;

typedef struct
{
  uint8                ucDrvType;       // driver variant
  uint8                ucReserved1;
  uint8                ucReserved2;
  uint8                ucReserved3;
  tCddTps92520_DrvCfg  aDrv[2];
} tCddTps92520_Eft_EcuVarCfg;



#endif // CDD_TPS92520_EFT_2021_01_22_H_
