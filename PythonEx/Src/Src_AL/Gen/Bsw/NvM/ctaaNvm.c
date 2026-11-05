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
/// \file  ctaaNvm.c
///
/// \brief  Init and cyclic runnables for NvM module
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-------------------------------------------------------
//-----------------------------------------------------------------------------


//=============================================================================
// includes
//=============================================================================

#include <Nvm.h>
#include <ctaaNvm.h>
#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riNvM_Init)
SYS_LOAD_MEAS_VAR_DEC(rpNvM_Cycle0)
#endif


STATIC_AL boolean NvM_boInitialized = FALSE;

//=============================================================================
// functions
//=============================================================================

/// ---------------------------------------------------------------------------
/// \func     riNvmM_Init
///
/// \brief    init runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void riNvM_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riNvM_Init)
#endif

  // Initialize NvM
  NvM_Init();
  NvM_boInitialized = TRUE;

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riNvM_Init)
#endif
}


/// ---------------------------------------------------------------------------
/// \func     rpNvm_Cycle0
///
/// \brief    cyclic runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void rpNvM_Cycle0(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpNvM_Cycle0)
#endif

  if (FALSE == NvM_boInitialized)
  {
    NvM_Init();
    NvM_boInitialized = TRUE;
  }

  NvM_MainFunction();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpNvM_Cycle0)
#endif
}


// EOF

