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
/// \file  WdgM_Types.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef WDGM_TYPES_2022_01_10_H_
#define WDGM_TYPES_2022_01_10_H_

#include <Std_Types.h>

typedef struct
{
  const uint8 ucEntityId;
  const uint8 ucEntityCycleMs;
  uint8 uctHitCount;
}tsWdgM_CheckPoint;

#endif // WDGM_TYPES_2022_01_10_H_
