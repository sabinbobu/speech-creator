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
/// \file  Lpit.h
///
/// \brief Mcal Lpit interfaces/runnables
///
/// \author Stefan Tyirean (f75617c)
///         mailto: stefan.tyirean[at]marelli.com
///
/// \Date April 2021
///
//-----------------------------------------------------------------------------
#ifndef LPIT_2021_03_24_H_
#define LPIT_2021_03_24_H_

#include <Std_Types.h>
#include <Lpit_TargetTypes.h>
#include <AL_Helper.h>

#if defined(__cplusplus)
extern "C"
{
#endif

  // Lpit data structure for Lpit init procedure
  extern CONST_AL tsLpit_CfgData Lpit_sLpitDatatCfg;

  // Lpit init (EcuM in start-up phase)
  void    Lpit_Init                 (CONST_AL tsLpit_CfgData * CONST_AL psLpitCfgIn);
  void    Lpit_LpitSetTmrEnblBit    (CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulEnblBit);
  void    Lpit_LpitSetTmrChCompVal  (CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulCompVal);
  void    Lpit_LpitSetTmrChIntEnbl  (CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulIntEnbl);
  uint32  Lpit_LpitReturnCount      (CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr);
  void    Lpit_LpitClearTimeout     (CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr);
  void    Lpit_ClearInterruptFlag   (uint8 ucTimerInst, uint8 ucTimerCh);
  void    Lpit_TmrChannelEnable     (uint8 ucTimerInst, uint8 ucTimerCh);

#if defined(__cplusplus)
  }
#endif

#endif // LPIT_2021_03_24_H_

// EOF
