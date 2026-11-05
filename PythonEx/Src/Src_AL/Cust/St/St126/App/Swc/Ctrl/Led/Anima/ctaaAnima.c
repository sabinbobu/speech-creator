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
/// \file  ctaaAnima.c
///
/// \brief  
///
/// \descr  
///
/// \author Georgiana Sevastre (F54430C)
///         mailTo:georgiana.sevastre[at]marelli.com
//-----------------------------------------------------------------------------

#include "Swc/Ctrl/Led/Anima/Anima.h"
#include "Anima_CodPrj.h"
#include "ctaaAnima.h"
#include <Util_Time.h>
#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(rpAppM_Cycle0)
SYS_LOAD_MEAS_VAR_DEC(riAppM_Init)
#endif

//-----------------------------------------------------------------------------
/// \brief riAnima_Init
///
/// \descr Init runnable for animation module
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void riAnima_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
	SYS_LOAD_MEAS_BEGIN(riAppM_Init)
#endif

  Anima_Init();

#ifdef SYS_LOAD_RUNNABLE
	SYS_LOAD_MEAS_END(riAppM_Init)
#endif
}

//-----------------------------------------------------------------------------
/// \brief rpAppM_Cycle0
///
/// \descr Cyclic runnable adapter for Anima
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void rpAnima_Cycle0(void)
{
#ifdef SYS_LOAD_RUNNABLE
	SYS_LOAD_MEAS_BEGIN(rpAppM_Cycle0)
#endif

  Anima_Cycle10();

#ifdef SYS_LOAD_RUNNABLE
	SYS_LOAD_MEAS_END(rpAppM_Cycle0)
#endif
}

//-----------------------------------------------------------------------------
/// \brief roAnima_ParaFct0
///
/// \descr Runnable adapter for Anima
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void roAnima_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
{
  Anima_ParaFct0(eCmd, pData);
}
