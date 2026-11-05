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
/// \file   Mcu_TargetTypes.h
///
/// \brief  target-specific MCAL types of Mcu.
///
//-----------------------------------------------------------------------------
#ifndef MCU_TARGET_TYPES_2021_02_18_H_
  #define MCU_TARGET_TYPES_2021_02_18_H_

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

  typedef uint8 Mcu_ClockSpecificType;

  typedef enum
  {
    MCU_RESET_UNDEFINED,
    MCU_WATCHDOG_RESET,
    MCU_POWER_ON_RESET,
    MCU_STOP_ACKNOWLEDGE_ERROR_RESET,
    MCU_MDM_AP_SYSTEM_RESET_REQUEST,
    MCU_SOFTWARE_RESET,
    MCU_CORE_LOCKUP,
    MCU_JTAG_GENERATED_RESET,
    MCU_EXTERNAL_PIN_RESET,
    MCU_CMU_LOSS_OF_CLOCK_RESET,
    MCU_LOSS_OF_LOCK_RESET,
    MCU_LOSS_OF_CLOCK_RESET,
    MCU_LOW_VOLTAGE_DETECT_OR_HIGH_VOLTAGE_DETECT_RESET
  }Mcu_ResetType;

  #if defined(__cplusplus)
  }
  #endif

#endif // MCU_TARGET_TYPES_2021_02_18_H_
