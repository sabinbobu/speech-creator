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
/// \file  ctaaSchM_Untrusted_DtcStorage.c
///
/// \brief Schedule manager - Used to call the runnables with 20ms cycle time
///                           It contains the implementation of storage DTC and ALEC
///                           in Nvm
///
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include <Rte.h>
#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riSchM_FuncNonTrusted_DtcStorage_Init)
SYS_LOAD_MEAS_VAR_DEC(rpSchM_Func_NonTrusted_DtcStorage_Cycle)
#endif

//=============================================================================
// Function prototypes
//=============================================================================

//extern void riDem_Init(void);
//extern void rpDem_Cycle0(void);
#include "ctaaDem.h"

//extern void riErrCust_Init(void);
//extern void rpErrCust_Cycle0(void);
#include "ctaaErrCust.h"

//=============================================================================
// preprocessor definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief riSchM_FuncNonTrusted_DtcStorage_Init
///
/// \descr Non trusted init runnable which initialize  modules used for DTC storage,
///        Dem and Err
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void riSchM_FuncNonTrusted_DtcStorage_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riSchM_FuncNonTrusted_DtcStorage_Init)
#endif

  //riDem_Init();

  //riErrCust_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riSchM_FuncNonTrusted_DtcStorage_Init)
#endif
// PRQA S 5334 1 // riDem_Init() and riErrCust_Init() are called from STARTUP_TWO
}


//-----------------------------------------------------------------------------
/// \brief rpSchM_Func_NonTrusted_Cycle
///
/// \descr Cycle runnable which call cycle runnables for modules which are used for DTC storage
///        with a periodicity of 20 ms, Dem and Err
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void rpSchM_Func_NonTrusted_DtcStorage_Cycle(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpSchM_Func_NonTrusted_DtcStorage_Cycle)
#endif

  // call Dem cyclic runnable
  rpDem_Cycle0();

  // call Err cyclic runnable
  rpErrCust_Cycle0();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpSchM_Func_NonTrusted_DtcStorage_Cycle)
#endif
}


// EOF
