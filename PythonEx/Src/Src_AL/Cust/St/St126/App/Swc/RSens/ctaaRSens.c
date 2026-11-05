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
/// \file  ctaaRSens.c
///
/// \brief  
///
/// \descr  
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Sergej Immel  (F55102A)
///         mailTo:sergej.immel[at]al-lighting.com
//-----------------------------------------------------------------------------

#include "RSens.h"
#include <Util_Time.h>
#include <CodM.h>
#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(rpRSens_Cycle0)
SYS_LOAD_MEAS_VAR_DEC(riRSens_Init)
#endif

void riRSens_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
	SYS_LOAD_MEAS_BEGIN(riRSens_Init)
#endif

  RSens_Init();

#ifdef SYS_LOAD_RUNNABLE
	SYS_LOAD_MEAS_END(riRSens_Init)
#endif
}

void rpRSens_Cycle0(void)
{
#ifdef SYS_LOAD_RUNNABLE
	SYS_LOAD_MEAS_BEGIN(rpRSens_Cycle0)
#endif

  RSens_Cycle0();

#ifdef SYS_LOAD_RUNNABLE
	SYS_LOAD_MEAS_END(rpRSens_Cycle0)
#endif
}

// to be used
//void roRSens_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
//{
//
//  RSens_ParaFct0(eCmd, pData);
//
//}
