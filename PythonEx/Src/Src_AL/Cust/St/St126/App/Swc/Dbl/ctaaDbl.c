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
/// \file   ctaaDbl.c
///
/// \brief  Dbl (Dynamic Bending Light)
///
/// \descr  Dbl control functions
///
///
/// \author Garmann, Norbert ALRT/EEG-PM4 (gan2rt)
///         mailTo:Norbert.Garmann[at]al-lighting.com
//-----------------------------------------------------------------------------

#include "ctaaDbl.h"
#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riDbl_Init)
SYS_LOAD_MEAS_VAR_DEC(rpDbl_Cycle)
#endif

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)// Applicable only for FULL version
//-----------------------------------------------------------------------------
/// \brief  Dbl Initialization
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void riDbl_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riDbl_Init)
#endif

    Dbl_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riDbl_Init)
#endif 
}

//-----------------------------------------------------------------------------
/// \brief  Cyclic runnable for Dbl at 20ms
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void rpDbl_Cycle(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpDbl_Cycle)
#endif

  Dbl_Cycle();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpDbl_Cycle)
#endif
}
#endif // CFG_VARIANT_FULL
