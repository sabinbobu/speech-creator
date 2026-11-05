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
/// \file  ctaaSchM_Untrusted_DehEI.c
///
/// \brief Schedule manager - Used to call the runnables with 20ms cycle time
///                           It contains the implementation for Electronic integration
///                           and Deh
///
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include <Rte.h>
#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riSchM_FuncNonTrusted_DehEI_Init)
SYS_LOAD_MEAS_VAR_DEC(rpSchM_Func_NonTrusted_DehEI_Cycle)
#endif
//=============================================================================
// Function prototypes
//=============================================================================

//extern void riDeh_Init(void);
//extern void rpDeh_Cycle0(void);
#include "ctaaDeh.h"

//extern void riElecInt_Init(void);
//extern void rpElecInt_Cycle(void);
#include "ctaaElecInt.h"
//=============================================================================
// preprocessor definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief riSchM_FuncNonTrusted_DehEI_Init
///
/// \descr Non trusted init runnable which initialize  Deh and Electronic Integration
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void riSchM_FuncNonTrusted_DehEI_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riSchM_FuncNonTrusted_DehEI_Init)
#endif

  riDeh_Init();

  riElecInt_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riSchM_FuncNonTrusted_DehEI_Init)
#endif
}


//-----------------------------------------------------------------------------
/// \brief rpSchM_Func_NonTrusted_DehEI_Cycle
///
/// \descr Cycle non trusted runnable for Deh and Electronic Integration 
///        with a periodicity of 10 ms
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void rpSchM_Func_NonTrusted_DehEI_Cycle(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpSchM_Func_NonTrusted_DehEI_Cycle)
#endif

  // call Deh cyclic runnable
  rpDeh_Cycle0();

  // call EI cyclic runnable
  rpElecInt_Cycle();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpSchM_Func_NonTrusted_DehEI_Cycle)
#endif
}


// EOF
