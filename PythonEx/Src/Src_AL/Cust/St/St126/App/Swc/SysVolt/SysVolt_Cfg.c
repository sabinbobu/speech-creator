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
/// \file   SysVolt_Cfg.c
///
/// \brief  Config file
///
/// \descr  Project specific SysVolt configurations
///
/// \author Henrietta Futo (F31185D)
///         mailTo: henrietta-helena.futo[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include <SysVolt_RteAccess.h>
#include <SysVolt_Cfg.h>
#include <UtilUtility.h>

//=============================================================================
// variables
//=============================================================================

// Local stepper Config
STATIC_AL tsSysVolt_VoltageRangeSet SysVolt_asLevelVoltStp[] =
{
  // unVoltLevel_mV,  eVoltageRange
  { eSysVolt_eLow3  ,  7600u  /*[mV] */,SYSVOLT_DEFAULT_DEBTIME_DIR_WORSE_MS, SYSVOLT_DEFAULT_DEBTIME_DIR_BETTER_MS}, //       below  7,6 Volt we are in _eLow3 range.
  { eSysVolt_eLow2  ,  8600u  /*[mV] */,SYSVOLT_DEFAULT_DEBTIME_DIR_WORSE_MS, SYSVOLT_DEFAULT_DEBTIME_DIR_BETTER_MS  }, // > and below  8,6 Volt we are in _eLow2 range.
  { eSysVolt_eLow1  ,  9600u  /*[mV] */,SYSVOLT_DEFAULT_DEBTIME_DIR_WORSE_MS, SYSVOLT_DEFAULT_DEBTIME_DIR_BETTER_MS  }, // > and below  9,6 Volt we are in _eLow1 range.
  { eSysVolt_eNormal, 18700u  /*[mV] */,SYSVOLT_DEFAULT_DEBTIME_DIR_WORSE_MS, SYSVOLT_DEFAULT_DEBTIME_DIR_BETTER_MS  }, // > and below 18,7 Volt we are in _eNormal range.
  { eSysVolt_eHigh1 , 19700u  /*[mV] */,SYSVOLT_DEFAULT_DEBTIME_DIR_WORSE_MS, SYSVOLT_DEFAULT_DEBTIME_DIR_BETTER_MS  }, // > and below 19,7 Volt we are in _eHigh1 range.
  { eSysVolt_eHigh2 , SYSVOLT_GENERIC_LAST        }  // > else we are in _eHigh2 range.
};

// Local Fan Config
STATIC_AL tsSysVolt_VoltageRangeSet SysVolt_asLevelFan[] =
{
  // eVoltageRange, unRangeUpperLimit_mV
  { eSysVolt_eLow2,    7000u /*[mV]*/,SYSVOLT_FAN1_DEBTIME_MS, SYSVOLT_FAN1_DEBTIME_MS}, //       below  7,0 Volt we are in _eLow2 range.
  { eSysVolt_eLow1,    9000u /*[mV]*/,SYSVOLT_FAN1_DEBTIME_MS, SYSVOLT_FAN1_DEBTIME_MS }, // > and below  9,0 Volt we are in _eLow1 range.
  { eSysVolt_eNormal, 16000u /*[mV]*/,SYSVOLT_FAN1_DEBTIME_MS, SYSVOLT_FAN1_DEBTIME_MS }, // > and below 16,0 Volt we are in _eNormal range.
  { eSysVolt_eHigh1,  17000u /*[mV]*/,SYSVOLT_FAN1_DEBTIME_MS, SYSVOLT_FAN1_DEBTIME_MS }, // > and below 17,0 Volt we are in _eHigh1 range.
  { eSysVolt_eHigh2,  SYSVOLT_GENERIC_LAST }  // > else we are in _eHigh2 range.
};

// Local Vbat Diagnosis Config
STATIC_AL tsSysVolt_VoltageRangeSet SysVolt_asLevelLocalDiagVbat[] =
{
  // eVoltageRange, unRangeUpperLimit_mV
  { eSysVolt_eLow2,    8000u /*[mV]*/,SYSVOLT_DEFAULT_DEBTIME_DIR_WORSE_MS, SYSVOLT_DEFAULT_DEBTIME_DIR_BETTER_MS }, //       below  8,0 Volt we are in _eLow2 range.
  { eSysVolt_eLow1,    8200u /*[mV]*/,SYSVOLT_DEFAULT_DEBTIME_DIR_WORSE_MS, SYSVOLT_DEFAULT_DEBTIME_DIR_BETTER_MS }, // > and below  8,2 Volt we are in _eLow1 range.
  { eSysVolt_eNormal, 15800u /*[mV]*/,SYSVOLT_DEFAULT_DEBTIME_DIR_WORSE_MS, SYSVOLT_DEFAULT_DEBTIME_DIR_BETTER_MS }, // > and below 15,8 Volt we are in _eNormal range
  { eSysVolt_eHigh1,  16000u /*[mV]*/,SYSVOLT_DEFAULT_DEBTIME_DIR_WORSE_MS, SYSVOLT_DEFAULT_DEBTIME_DIR_BETTER_MS }, // > and below 16,0 Volt we are in _eHigh1 range.
  { eSysVolt_eHigh2,  SYSVOLT_GENERIC_LAST }, // > else we are in _eHigh2 range.
};

// Local LED Config
STATIC_AL tsSysVolt_VoltageRangeSet SysVolt_asLedVbat[] =
{
  // eVoltageRange, unRangeUpperLimit_mV
  { eSysVolt_eLow2,    6500u /*[mV]*/,SYSVOLT_LED_DEBTIME_DIR_WORSE_MS, SYSVOLT_LED_DEBTIME_DIR_BETTER_MS }, //       below  6,5 Volt we are in _eLow2 range.
  { eSysVolt_eLow1,    8000u /*[mV]*/,SYSVOLT_LED_DEBTIME_DIR_WORSE_MS, SYSVOLT_LED_DEBTIME_DIR_BETTER_MS }, // > and below  8,0 Volt we are in _eLow1 range.
  { eSysVolt_eNormal, SYSVOLT_GENERIC_LAST /*[mV]*/}, // > else we are in _eNormal range.
};

// Array holding the configuration for all configured modules
tsSysVolt_InVoltCfg SysVolt_Configs[eSysV_LastModule_Idx] =
{
  { SysVolt_asLevelVoltStp,
    UTIL_COUNTOF(SysVolt_asLevelVoltStp),
  SysVolt_RteAccess_Write_Stp_VoltState,
    SysVolt_RteAccess_Read_Vbat
  },
  { SysVolt_asLevelFan,
    UTIL_COUNTOF(SysVolt_asLevelFan),
    SysVolt_RteAccess_Write_Fan_VoltState,
    SysVolt_RteAccess_Read_Vbat
  },
  { SysVolt_asLevelLocalDiagVbat,
    UTIL_COUNTOF(SysVolt_asLevelLocalDiagVbat),
    SysVolt_LocalDiagVbat,
    SysVolt_RteAccess_Read_Vbat
  },
  { SysVolt_asLedVbat,
    UTIL_COUNTOF(SysVolt_asLedVbat),
    SysVolt_RteAccess_Write_Led_VoltState,
    SysVolt_RteAccess_Read_Vbat
  }
};

// EOF
