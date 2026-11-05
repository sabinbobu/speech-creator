//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written 
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************

///----------------------------------------------------------------------------
/// \file   Can_TargetTypes.h
///
/// \brief  target-specific MCAL types of Can.
///
//-----------------------------------------------------------------------------
#ifndef CAN_TARGET_TYPES_2021_02_18_H_
  #define CAN_TARGET_TYPES_2021_02_18_H_

  //=============================================================================
  // Includes
  //=============================================================================
  #include <Std_Types.h>

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  //=============================================================================
  // Public functions declarations
  //=============================================================================

  typedef uint8 Can_SpecificType;

  #if defined(__cplusplus)
  }
  #endif

#endif // CAN_TARGET_TYPES_2021_02_18_H_
