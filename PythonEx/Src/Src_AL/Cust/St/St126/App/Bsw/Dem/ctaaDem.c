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
/// \file  ctaaDem.c
///
/// \brief  
///
/// \descr  Init and Cyclic Runnables for SysMon
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <Dem.h>
#include <ctaaDem.h>
#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riDem_Init)
SYS_LOAD_MEAS_VAR_DEC(rpDem_Cycle0)
#endif

//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/// \brief  riDem_Init
///
/// \descr  Dem init function
///
/// \param  -
///
/// \return void 
//-----------------------------------------------------------------------------
void riDem_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riDem_Init)
#endif

  Dem_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riDem_Init)
#endif
}

//-----------------------------------------------------------------------------
/// \brief  rpDem_Cycle0
///
/// \descr  Dem task function
///
/// \param  -
///
/// \return void 
//-----------------------------------------------------------------------------
void rpDem_Cycle0(void)
{
#ifdef SYS_LOAD_RUNNABLE
    SYS_LOAD_MEAS_BEGIN(rpDem_Cycle0)
#endif

    Dem_Task();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpDem_Cycle0)
#endif
}

// EOF
