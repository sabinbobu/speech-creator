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
/// \file TrigMux.c
///
/// \brief Mcal TrigMux interfaces/runnables definitions
///
/// \author Stefan Tyirean (f75617c)
///         mailto: stefan.tyirean[at]marelli.com
///
/// \Date April 2021
///
//-----------------------------------------------------------------------------

//====================================================================
// Include files
//====================================================================

#include "TrigMux.h"
#include "TrigMux_Drv.h"
#include "TrigMux_TargetTypes.h"

//====================================================================
// Global function definitions
//====================================================================

//-----------------------------------------------------------------------------
/// \brief TrigMux_Init
///
/// \descr TrigMus Initialization [Instances and channels input/output]
///
/// \param  sTrigMuxCfgData - TrigMux configuration data received at init
///
/// \return void
//-----------------------------------------------------------------------------
void TrigMux_Init(CONST_AL tsTrigMux_CfgData* CONST_AL psTrigMuxCfgData)
{
  // Check input config parameter
  if (psTrigMuxCfgData != NULL_PTR)
  {
    // TrigMux Driver Init
    (void)TrigMux_Drv_Init(psTrigMuxCfgData);
  }
  else
  {
    // NULL_PTR, trigmux configuration shall be avoided
  }
}

// EOF
