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
/// \file  ctscWdgM.c
///
/// \brief
///
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------
#include "WdgM.h"
#include "ctscWdgM.h"
#include <Bsw/Sys/Load/SysLoad.h>

//-----------------------------------------------------------------------------
// Sysload Tags
//-----------------------------------------------------------------------------
#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riWdgM_Init)
SYS_LOAD_MEAS_VAR_DEC(rpWdgM_Cycle0)
#endif

//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \brief riWdgM_Init
///
/// \descr WdgM Init runnable
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void riWdgM_Init(void)
{
  WdgM_Init();
}


//-----------------------------------------------------------------------------
/// \brief rpWfdgM_Cycle0
///
/// \descr WdgM cuclic runnable
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void rpWdgM_Cycle0(void)
{
  WdgM_Cycle0();
}

// EOF
