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
/// \file  ctaaPitch.c
///
/// \brief
///
/// \descr
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Ott, Peter ALRT/EEG-PM2 * (otp2rt)
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#include "Pitch.h"


#ifdef SYS_LOAD_RUNNABLE
#include <Bsw/Sys/Load/SysLoad.h>
SYS_LOAD_MEAS_VAR_DEC(riCtrlLed_Init)
SYS_LOAD_MEAS_VAR_DEC(rpCtrlLed_Cycle0)
#endif

void riPitch_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riPitch_Init)
#endif

  Pitch_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riPitch_Init)
#endif
}

void rpPitch_Cycle0(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(Pitch_Cycle0)
#endif

    Pitch_Cycle0();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(Pitch_Cycle0)
#endif
}
