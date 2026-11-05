//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
/// ---------------------------------------------------------------------------
///
///  \file    Dblc.c
///
///  \author  Bernd Dreier  Bernd.Dreier[at]al-lighting.com
///           ported by     VORNICU Tony - EEG-PM4 (F63906B)
///                         mailTo:tony.vornicu[at]al-lighting.com
///
///  \owner   Bernd Dreier   Bernd.Dreier[at]al-lighting.com
///
///  \date    26.06.2003
///
///  \brief   dynamic bending light control 
///
///  \descr   dynamic bending light control 
///
/// ---------------------------------------------------------------------------

#include <Cfg/Cfg.h>
#include "Dblc.h"
#include "DblcSm.h"
#ifndef UNIT_TEST
#include <Rte.h>
#endif
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version

/// ---------------------------------------------------------------------------
///
/// \brief       dynamic bending light init
///
/// \descr       dynamic bending light init
///
/// ---------------------------------------------------------------------------
void Dbl_Init(void)
{
  DblcSm_Init();
}

/// ---------------------------------------------------------------------------
///
/// \func        void Dbl_Cycle(void)  
///
/// \brief       dynamic bending light control
///
/// \descr       dynamic bending light control\n
///              sampling time 20ms\n
///              function copies Bb Messages to local variables 
///              and calls DBLC state machine 
///
/// \dot
///
///    digraph G 
///    {
///      Off        -> Normal;
///      Normal     -> Hold;
///      Normal     -> Off;
///      Hold       -> Normal;
///      Hold       -> Off;
///      Off         [color=red,    style=filled];
///      Normal      [color=green,  style=filled];
///      Hold        [color=yellow, style=filled];
///    }
/// \enddot
/// 
/// \callgraph 
/// ---------------------------------------------------------------------------
void Dbl_Cycle(void)
{
  if(Dbl_sCodingParam.eCodingState != eParaFct0_CodingDataInvalid)
  { 
  Dbl_Curvature_SigQty_INV();
  Dbl_ReadEnvironmentSignals();
  Dbl_ReadInputSignals();
  Dbl_DefOfFailure();
  Dbl_DetectMode();
  Dbl_UseMode();
  Dbl_UseSubMode();
  Dbl_Write_OutputValues();
  Dbl_HbActive();
  }
  else
  {
    // LDM Stays uncoded
  }
}   // PRQA S 5324  // HIS metrics violation suppressed (STCAL = 8)
#endif
