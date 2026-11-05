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
/// \file  ctaaDeh.c
///
/// \brief  ctaaDeh
///
/// \descr  Init and Cyclic Runnables for Deh
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <Deh.h>
#include <ctaaDeh.h>
#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riDeh_Init)
SYS_LOAD_MEAS_VAR_DEC(rpDeh_Cycle0)
#endif

//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/// \brief  riDeh_Init
///
/// \descr  Deh init function
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void riDeh_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riDeh_Init)
#endif

    Deh_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riDeh_Init)
#endif
}


//-----------------------------------------------------------------------------
/// \brief  rpDeh_Cycle0
///
/// \descr  Deh cycle function
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void rpDeh_Cycle0(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpDeh_Cycle0)
#endif

  Deh_Cycle0();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpDeh_Cycle0)
#endif
}

//EOF
