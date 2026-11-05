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
/// \file  AvacInit.c
///
/// \brief  
///
/// \descr  
///
///         Additional information can be found in the design description 
///
/// \author Traulsen, Alf ALRT/EEG-CA * (taf2rt)
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#include <Nvm.h>
#include "AvacStat1Init.h"

//=============================================================================
// init data for Nvm-Parameter
//=============================================================================
#ifndef StatAvacPrj1INIT
  #define StatAvacPrj1INIT \
    { 1, 5, 255, 123, 120, 127, 8, 20, 10, 100, 1, {120, 123,   0,   0, 0} } // standard
//  { 1, 5, 255, 118, 113, 127, 8, 20, 10,  60, 1, {114, 117, 120, 123, 0} } // alternative (?)
#endif

#ifndef StatAvac1INIT
  #define StatAvac1INIT \
  {{0,0}, 10, 90, 30, 10, 10, 20, 100}
#endif

#ifndef StatAvacOp1INIT
  #define StatAvacOp1INIT \
    {0, AVAC_SAFETY_POS, 0}
#endif

const tisStatAvacPrj1Para     NvmInit_StatAvacPrj1ParaDefault = StatAvacPrj1INIT;
const tisStatAvac1Para        NvmInit_StatAvac1ParaDefault    = StatAvac1INIT;
const tisStatAvacOp1Data      NvmInit_StatAvacOp1DataDefault  = StatAvacOp1INIT;

