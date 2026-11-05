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
/// \file  Lpit_Cfg.c
///
/// \brief Project related Lpit configuration
///
/// \author Stefan Tyirean (f75617c)
///         mailto: stefan.tyirean[at]marelli.com
///
/// \Date April 2021
///
//-----------------------------------------------------------------------------

#include <Lpit.h>
#include <UtilUtility.h>
#include <Std_Types.h>

// LPIT CLK frequency
#define LPIT_INPUT_CLK_FREQ           16000000u

// PDB period 5ms
// STP interrupt at 10ms
// 16000 * Input Clck [16Mhz]
#define PDB_DIVIDER              8000u // 8Khz  (125us) Trigger for PDB0/PDB1
#define STP_DIVIDER              100u  // 100Hz (10ms) timer interrupt for stepper
#define PDB_TRG_PERIOD          LPIT_INPUT_CLK_FREQ / PDB_DIVIDER
#define STP_TMR_PERIOD          LPIT_INPUT_CLK_FREQ / STP_DIVIDER
#define WDG_TRIG_TMR_PERIOD     2880250u // 180ms

// Lpit Instances Configuration (Only LPIT0)
STATIC_AL CONST_AL tsLpit_LpitInstanceCfg Lpit_asLpitInstCfg[] =
{ /*Instance, Debug Enbl,  Doze Enbl    Module Enbl*/
  {   0u,       FALSE,      FALSE,         TRUE }
};

// Lpit Chanels Configuration
STATIC_AL CONST_AL tsLpit_LpitTmrCfg Lpit_asLpitTmrCfg[] =
{
  /*Instance, Channel,      Mode,                Period Ticks,        Trigger Mode,      Trigger Sel,    ROT,     SOI,    SOT,    Chain,  Int Enbl*/
  {   0u,       0u,   eLpit32PeriodicTimer,     STP_TMR_PERIOD,       eExternalTiggers,     eTimerCh0,    FALSE,    TRUE,   FALSE,  FALSE,    TRUE  },    // LPIT0 CH0 (CddStp)
  {   0u,       1u,   eLpit32PeriodicTimer,     WDG_TRIG_TMR_PERIOD,  eExternalTiggers,     eTimerCh1,    TRUE,     FALSE,   FALSE,  FALSE,    TRUE  },    // LPIT0 CH1 (Sbc Watchdog Trigger)
  {   0u,       3u,   eLpit32PeriodicTimer,     PDB_TRG_PERIOD,       eExternalTiggers,     eTimerCh3,    FALSE,    FALSE,  FALSE,  FALSE,    FALSE }     // LPIT0 CH3 (PDB0_1 - ADC)
};

// Extern data configuration passed to Lpit Init function
const tsLpit_CfgData Lpit_sLpitDatatCfg =
{
  /*     Config array,                count*/
  { &Lpit_asLpitInstCfg[0], countof(Lpit_asLpitInstCfg) },
  { &Lpit_asLpitTmrCfg[0],  countof(Lpit_asLpitTmrCfg)  }
};

// EOF
