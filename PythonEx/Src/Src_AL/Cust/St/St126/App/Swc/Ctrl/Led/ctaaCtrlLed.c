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
/// \file  ctaaCtrlLed.c
///
/// \brief  Runnables definitions of CtrlLed module
///
/// \author Caba Ionut-Stefan (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
//-----------------------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================
#include "CtrlLed.h"
#include "ctaaCtrlLed.h"

#ifdef SYS_LOAD_RUNNABLE
#include <Bsw/Sys/Load/SysLoad.h>

SYS_LOAD_MEAS_VAR_DEC(riCtrlLed_Init)
SYS_LOAD_MEAS_VAR_DEC(rpCtrlLed_Cycle0)
#endif

//=============================================================================
// functions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief riCtrlLed_Init
///
/// \descr Init runnable for CtrlLed
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void riCtrlLed_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riCtrlLed_Init)
#endif

    CtrlLed_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riCtrlLed_Init)
#endif
}

//-----------------------------------------------------------------------------
/// \brief rpCtrlLed_Cycle0
///
/// \descr Cyclic runnable adapter for CtrlLed
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void rpCtrlLed_Cycle0(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpCtrlLed_Cycle0)
#endif

    CtrlLed_Cycle0();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpCtrlLed_Cycle0)
#endif
}
