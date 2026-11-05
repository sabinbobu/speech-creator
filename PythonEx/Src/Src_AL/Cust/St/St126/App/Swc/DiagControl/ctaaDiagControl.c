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
/// \file  ctaaDiagControl.c
///
/// \brief Diagnostic Control runnables
///
/// \author Tyirean Stefan F75617C
///         mail to <stefan.tyirean[at]magnetimarelli.com>
//-----------------------------------------------------------------------------
#include <Bsw/Sys/Load/SysLoad.h>
#include "ctaaDiagControl.h"
#include "DiagControl.h"

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_VAR_DEC(riDiagControl_Init)
  SYS_LOAD_MEAS_VAR_DEC(rpDiagControl_Cycle0)
#endif

//-----------------------------------------------------------------------------
/// \brief riDiagControl_Init
///
/// \descr Init Runable of Diagnostic Control Swc
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void riDiagControl_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
    SYS_LOAD_MEAS_BEGIN(riDiagControl_Init)
#endif

  DiagControl_Init();

#ifdef SYS_LOAD_RUNNABLE
    SYS_LOAD_MEAS_END(riDiagControl_Init)
#endif
}

//-----------------------------------------------------------------------------
/// \brief rpDiagControl_Cycle0
///
/// \descr Cyclic Runable of Diagnostic Control Swc
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void rpDiagControl_Cycle0(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpDiagControl_Cycle0)
#endif

  DiagControl_Cycle0();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpDiagControl_Cycle0)
#endif
}

// EOF
