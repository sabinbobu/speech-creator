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
/// \file   Dio_TargetTypes.h
///
/// \brief  target-specific MCAL types of Dio.
///
//-----------------------------------------------------------------------------
#ifndef DIO_TARGET_TYPES_2021_02_18_H_
  #define DIO_TARGET_TYPES_2021_02_18_H_

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

  typedef uint32 Dio_PortType;

  typedef uint8 Dio_ChannelGroupType;

  #if defined(__cplusplus)
  }
  #endif

#endif // DIO_TARGET_TYPES_2021_02_18_H_
