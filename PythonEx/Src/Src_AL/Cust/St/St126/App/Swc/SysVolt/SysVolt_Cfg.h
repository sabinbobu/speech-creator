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
/// \file   SysVolt_Cfg.h
///
/// \brief  Config header file
///
/// \descr  Project specific SysVolt configurations header
///
/// \author Henrietta Futo (F31185D)
///         mailTo: henrietta-helena.futo[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __SYS_VOLT_PRJ_CFG_H__
#define __SYS_VOLT_PRJ_CFG_H__

//=============================================================================
// Includes
//=============================================================================

#include <SysVolt.h>

//=============================================================================
// Macros
//=============================================================================

#define SYSVOLT_GENERIC_LAST                                      0xFFFFu // Termination value for voltage level arrays
#define SYSVOLT_DEFAULT_DEBTIME_DIR_WORSE_MS                      20u // Debounce time for switching to worse voltage range [ms]
#define SYSVOLT_DEFAULT_DEBTIME_DIR_BETTER_MS                     20u // Debounce time for switching to better voltage range [ms]
#define SYSVOLT_FAN1_DEBTIME_MS                                   0u // Debounce time for switching to better voltage range for fan[ms]
#define SYSVOLT_ZERO_DEBTIME                                      0u // Debounce time for switching to better voltage range for fan[ms]
#define SYSVOLT_LED_DEBTIME_DIR_WORSE_MS                          20u // Debounce time for switching to worse voltage range for led[ms]
#define SYSVOLT_LED_DEBTIME_DIR_BETTER_MS                         20u // Debounce time for switching to better voltage range for led[ms]
#define SYSVOLT_CRANCKING_DEBTIME_DIR_TIME_MS                     300u // Debounce time for Vbat (300ms to avoid crancking unintented under/overvoltage)


//=============================================================================
// Extern variables
//=============================================================================

// This is taken by SysVolt.c for system Volt processing

extern tsSysVolt_InVoltCfg SysVolt_Configs[];

#endif // __SYS_VOLT_PRJ_CFG_H__

// EOF
