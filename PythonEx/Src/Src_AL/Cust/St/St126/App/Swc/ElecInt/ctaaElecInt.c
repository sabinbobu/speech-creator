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
/// \file  ctaaElecInt.c
///
/// \brief  ctaaElecInt
///
/// \descr  Init and Cyclic Runnables for Electronic Integration
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <ElecInt.h>
#include <ctaaElecInt.h>
#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riElecInt_Init)
SYS_LOAD_MEAS_VAR_DEC(rpElecInt_Cycle)
#endif

//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/// \brief  riElecInt_Init
///
/// \descr  ElecInt init function
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void riElecInt_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riElecInt_Init)
#endif

  ElecInt_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riElecInt_Init)
#endif
}


//-----------------------------------------------------------------------------
/// \brief  rpElecInt_Cycle
///
/// \descr  ElecInt cycle function
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void rpElecInt_Cycle(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpElecInt_Cycle)
#endif

  ElecInt_Cycle();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpElecInt_Cycle)
#endif
}

//EOF
