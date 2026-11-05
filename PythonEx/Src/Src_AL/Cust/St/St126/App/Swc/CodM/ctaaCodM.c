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
/// \file  ctaaCodM.c
///
/// \brief  
///
/// \descr  Calls the runnables for the CodM module.
///
///                 
/// \author Cretu Vlad (F78845C)
///         mailTo:vladut-ioan.cretu[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
// TBD Regarding SySLoad Tags
#include "CodM.h"
//#if (TYP_BUILD == CFG_Var_rta)
////#include <SysLoad.h>
//#endif

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(rpCodM_Cycle0)
SYS_LOAD_MEAS_VAR_DEC(riCodM_Init)
#endif
//=============================================================================
// functions
//=============================================================================

/// ---------------------------------------------------------------------------
/// \func     riCodM_Init
///
/// \brief    init runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void riCodM_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riCodM_Init)
#endif

  // Provide pointer to coding area.
  CodM_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riCodM_Init)
#endif
}

/// ---------------------------------------------------------------------------
/// \func     rpCodM_Cycle0
///
/// \brief    cyclic runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void rpCodM_Cycle0(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpCodM_Cycle0)
#endif

  CodM_Cycle0();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpCodM_Cycle0)
#endif
}

// EOF
