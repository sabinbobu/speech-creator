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
/// \file  ctaaSchM_CddLedBoost.c
///
/// \brief Schedule manager for CddLed and CddBoost
///
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include <Rte.h>
#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riSchM_CddLedBoost_Func_Init)
SYS_LOAD_MEAS_VAR_DEC(rpSchM_CddLedBoost_Func_Cycle)
#endif

//=============================================================================
// Function prototypes
//=============================================================================

//extern void riCddLedInit(void);
//extern void rpCddLed_Cycle(void);
#include "CddLed_Adapter.h"

//extern void rpCddBoost_Cycle(void);
//extern void riCddBoostInit(void);
#include "CddBoost_Adapter.h"

//=============================================================================
// preprocessor definitions
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief riSchM_CddLedBoost_Func_Init
///
/// \descr Function which initialize CddLed and CddBoost
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void riSchM_CddLedBoost_Func_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riSchM_CddLedBoost_Func_Init)
#endif

  //riCddLedInit();
  //riCddBoostInit();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riSchM_CddLedBoost_Func_Init)
#endif
}


//-----------------------------------------------------------------------------
/// \brief rpSchM_CddLedBoost_Func_Cycle
///
/// \descr CddLed and CddBoost Cyclic runnables with 5ms periodicity
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void rpSchM_CddLedBoost_Func_Cycle(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpSchM_CddLedBoost_Func_Cycle)
#endif

  //rpCddLed_Cycle();
  //rpCddBoost_Cycle();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpSchM_CddLedBoost_Func_Cycle)
#endif
}

// EOF
