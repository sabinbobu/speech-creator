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
/// \file   ctaaSysCrc.c
///
/// \brief  Init and Cyclic Runnables for SysCrc
///
/// \author Cruciu Denis-Mihai (F31196D)
///         mailTo: denis-mihai.cruciu[at]marelli.com
//-----------------------------------------------------------------------------


//=============================================================================
// includes
//=============================================================================

#ifndef UNIT_TEST
#include <SysCrc.h>
#else
#include <SysCrc_TargetTypes.h>
#endif
#include <ctaaSysCrc.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riSysCrc_Init)
SYS_LOAD_MEAS_VAR_DEC(rpSysCrc_Cycle0)
#endif

//=============================================================================
// functions
//=============================================================================

/// ---------------------------------------------------------------------------
/// \func     riSysCrc_Init
///
/// \brief    init runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void riSysCrc_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
    SYS_LOAD_MEAS_BEGIN(riSysCrc_Init)
#endif
  return;
#ifdef SYS_LOAD_RUNNABLE
    SYS_LOAD_MEAS_BEGIN(riSysCrc_Init)
#endif
}


/// ---------------------------------------------------------------------------
/// \func     rpSysCrc_Cycle0
///
/// \brief    cyclic runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void rpSysCrc_Cycle0(void)
{
#ifdef SYS_LOAD_RUNNABLE
    SYS_LOAD_MEAS_BEGIN(rpSysCrc_Cycle0)
#endif

  SysCrc_RomSegs_DoCRC();

#ifdef SYS_LOAD_RUNNABLE
    SYS_LOAD_MEAS_END(rpSysCrc_Cycle0)
#endif

}

// EOF

