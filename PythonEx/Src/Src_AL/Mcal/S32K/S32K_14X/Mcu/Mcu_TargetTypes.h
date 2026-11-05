#ifndef MCU_CFG_2015_01_29_H
#define MCU_CFG_2015_01_29_H

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
/// \file  Mcu_TargetTypes.h
///
/// \brief  Mcu configuration file for Pb21
///
/// \descr  This file contains the Mcu configuration for Pb21.
///
/// \author Ramona-Andreea Bolboaca (f33613c)
///         mailTo:ramona-andreea.bolboaca(at)magnetimarelli.com
//-----------------------------------------------------------------------------
//=============================================================================
// Includes
//=============================================================================
#include <Std_Types.h>
//#include <S32K146_features.h>
//=============================================================================
// Defines
//=============================================================================

typedef struct Mcu_ClockSpecificType
{
  void** clockConfigsPtr;
  void** callbacksPtr;
} Mcu_ClockSpecificType;

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

#endif // MCU_CFG_2015_01_29_H
