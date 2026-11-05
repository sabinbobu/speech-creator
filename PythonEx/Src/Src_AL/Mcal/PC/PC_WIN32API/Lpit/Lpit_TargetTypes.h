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
/// \file  Lpit_TargetTypes.h
///
/// \brief Lpit Types header file
///
/// \author Stefan Tyirean (f75617c)
///         mailto: stefan.tyirean[at]marelli.com
///
/// \Date April 2021
///
//-----------------------------------------------------------------------------
#ifndef LPIT_TYPES_2021_03_16_H_
#define LPIT_TYPES_2021_03_16_H_


#include <Std_Types.h>
#include <AL_Helper.h>
#include <Device_TargetTypes.h>


typedef struct
{
  uint8 ucLpitInst;
  boolean boEnableDebug;
  boolean boEnableDoze;
  boolean boEnableModule;
}tsLpit_LpitInstanceCfg;

typedef enum
{
  eLpit32PeriodicTimer = 0u,
  eDual16PeriodicTimer = 1u,
  eTriggerAcumulator = 2u,
  eTrigggerInCapt = 3u
}teLpit_LpitTimerMode;

typedef enum
{
  eExternalTiggers = 0u,
  eInternalTriggers = 1u
}teLpit_LpitTimerTrigSrc;

typedef enum
{
  eTimerCh0 = 0u,
  eTimerCh1 = 1u,
  eTimerCh2 = 2u,
  eTimerCh3 = 3u
}teLpit_LpitTimerTrigSel;

typedef struct
{
  uint8 ucLpitInst;
  uint8 ucChnNr;
  teLpit_LpitTimerMode eTimerMode;
  uint32 ulPeriod_Reg;
  teLpit_LpitTimerTrigSrc eTriggerSrc;
  teLpit_LpitTimerTrigSel eTriggerSel;
  boolean boReloadOnTrigger;
  boolean boStopOnInterrupt;
  boolean boStartOnTrigger;
  boolean boChainChannel;
  boolean boIntEnbl;
}tsLpit_LpitTmrCfg;

typedef struct
{
  CONST_AL tsLpit_LpitInstanceCfg* psLpitInstCfg;
  uint8 ucCfgLength;
}tsLpit_LpitInstCfgMap;

typedef struct
{
  CONST_AL tsLpit_LpitTmrCfg* sLpitTmrCfg;
  uint8 ucCfgLength;
}tsLpit_LpitTmrCfgMap;

typedef struct
{
  tsLpit_LpitInstCfgMap sLpitInstanceCfg;
  tsLpit_LpitTmrCfgMap sLpitTmrCfg;
}tsLpit_CfgData;

#endif // LPIT_TYPES_2021_03_16_H_

// EOF
