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
/// \file  ctaaFctR.c
///
/// \brief Runnables definitions of FctR module
///
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include <Std_Types.h>
#include "FctR.h"
#include "ctaaFctR.h"
#include <CodM.h>
#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(rpFctR_Cycle)
SYS_LOAD_MEAS_VAR_DEC(riFctRInit)
SYS_LOAD_MEAS_VAR_DEC(StatM_Cycle0)
#endif

//=============================================================================
// functions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  riFctRInit
///
/// \descr  Init runnable for FctR module
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void riFctRInit(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riFctRInit)
#endif

  FctR_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riFctRInit)
#endif
}

//-----------------------------------------------------------------------------
/// \brief  rpFctR_Cycle
///
/// \descr  Cyclic runnable for FctR module
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void rpFctR_Cycle(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpFctR_Cycle)
#endif

  FctR_Cycle();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpFctR_Cycle)
#endif

}

////-----------------------------------------------------------------------------
///// \brief  roFctR_ParaFct0
/////
///// \descr
/////
///// \param  eCmd  -
/////         pData -
/////
///// \return void
////-----------------------------------------------------------------------------
//void roFctR_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//  FctR_ParaFct0(eCmd, pData);
//}

// EOF
