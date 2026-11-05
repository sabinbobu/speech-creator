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
/// \file  Icu_TargetTypes.h
///
/// \brief Here are defined the specific types used in the ICU module
///
/// \author Tanase Alexandru-Anton (F58375C)
///         mailTo:alexandru-anton.tanase[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef ICU_TARGET_TYPES_H_
#define ICU_TARGET_TYPES_H_

//=============================================================================
// includes
//=============================================================================

#include <Std_Types.h>
#include <Cfg/Cfg.h>

//=============================================================================
// defines
//=============================================================================


//=============================================================================
// data types
//=============================================================================

typedef struct
{
  void* icu_instance;
  void* icu_global_config;
  void* icu_info_config;
}tsIcu_ConfigInstanceMap;

typedef struct
{
  uint8                    ucCountOfIcuInstances;
  tsIcu_ConfigInstanceMap* sCfgCharacteristics;
}tsIcu_SpecificType;

typedef struct
{
  uint8 ucChannel;
  uint8 ucInstanceMapIdx;
  uint8 ucInstanceMapCh;
}tsIcu_ChannelMap;

#endif // ICU_TARGET_TYPES_H_
