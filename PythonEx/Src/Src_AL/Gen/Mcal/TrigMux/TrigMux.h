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
/// \file TrigMux.h
///
/// \brief Mcal TrigMux interfaces/runnables
///
/// \author Stefan Tyirean (f75617c)
///         mailto: stefan.tyirean[at]marelli.com
///
/// \Date April 2021
///
//-----------------------------------------------------------------------------
#ifndef TRIG_MUX_2021_03_24_H_
#define TRIG_MUX_2021_03_24_H_

#include <TrigMux_TargetTypes.h>
#include <AL_Helper.h>

#if defined(__cplusplus)
extern "C"
{
#endif

  // TrigMux data structure for TrigMux init procedure
  extern CONST_AL tsTrigMux_CfgData TrigMux_sTrigMuxDatatCfg;

 // TrigMux init (EcuM in start-up phase)
  void TrigMux_Init(CONST_AL tsTrigMux_CfgData* CONST_AL psTrigMuxCfgData);

#if defined(__cplusplus)
}
#endif

#endif // TRIG_MUX_2021_03_24_H_

// EOF
