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
/// \file   ctaaFee.c
///
/// \brief  Init and Cyclic Runnables for NvM
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------


//=============================================================================
// includes
//=============================================================================

#ifndef UNIT_TEST
#include <Fee.h>
#else
#include <Fee_TargetTypes.h>
#endif
//#include <Bsw/WdgM/WdgM.h>
#include <ctaaFee.h>
//#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(rpFee_Cycle0)
#endif
//=============================================================================
// functions
//=============================================================================

/// ---------------------------------------------------------------------------
/// \func     riFee_Init
///
/// \brief    init runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void riFee_Init(void)
{
  // Initialize Fee 
  Fee_Init();

#ifndef UNIT_TEST
  do
  {
      Fee_MainFunction();

  } while (Fee_GetStatus() != MEMIF_IDLE);
#else
  Fee_MainFunction();     //needed because UT remains stuck due to do-while statement
#endif
}


/// ---------------------------------------------------------------------------
/// \func     rpFee_Cycle0
///
/// \brief    cyclic runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void rpFee_Cycle0(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpFee_Cycle0)
#endif

  Fee_MainFunction();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpFee_Cycle0)
#endif
}

// EOF

