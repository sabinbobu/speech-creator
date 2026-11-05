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
///  \file    DblIdle.h
///
///  \author  Bernd Dreier  Bernd.Dreier@al-lighting.com
///           ported by     VORNICU Tony - EEG-PM4 (F63906B)
///                         mailTo:tony.vornicu@al-lighting.com
///
///  \owner   Ralf Sondershaus Ralf.Sondershaus@al-lighting.com
///
///  \date    05.04.2007
///
///  \brief   idle control for DBL (dead zone)
///
///  \descr   idle control for DBL (dead zone)
///
/// ---------------------------------------------------------------------------
#ifndef DBL_IDLE_2021_11_02_H_
#define DBL_IDLE_2021_11_02_H_

//=============================================================================
// includes
//=============================================================================
  #include <Cfg/Cfg.h>
  #include <Std_Types.h>
 
  #if (CFG_TYP_CL_LR06 != CFG_Cl_None)

    /// transforms the input curvature signal into a biased curvature signal
    sint32 ClIdleSignal(sint32 nC, sint32 nIdleRange);

    #if ( !(CFG_OPT_CL & CFG_Cl_IdleRangeAlg2) )
      /// calculates the idle range of the system
      sint32 ClIdleRange(sint32 nC, sint32 nCg);
    #else
      /// idle range calculation in dependency of vehicle speed
      sint32 ClIdleRange(sint32 nV, sint32 nC, sint32 nCg, uint8 ucSc);
    #endif

  #endif // (CFG_TYP_CL_LR06 != CFG_Cl_None)

#endif // DBL_IDLE_2021_11_02_H_
