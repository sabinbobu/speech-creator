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
/// \file   ctaaAdbPxa3.c
///
/// \brief  Adb (Adaptive Driving Beam)
///
/// \descr  
///
///         Additional information can be found in the design description (Link:
///
/// \author Brindusa Brudariu  (F61134C)
///         mailTo:brindusa-giorgiana.brudariu[at]marelli.com
//-----------------------------------------------------------------------------


//#include <Swc/CodM/CodM.h>
//#include <Swc/CodM/CodM_Para.h>

#include "AdbPxa3.h"
#include "AdbPxa3Data.h"
#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(rpAdbPxa3_Cycle0)
SYS_LOAD_MEAS_VAR_DEC(riAdbPxa3_Init)
#endif

//-----------------------------------------------------------------------------
/// \brief  Adb coding parameters
///
/// \param  eCmd (coding data valid / invalid)
/// \param  pData (pointer to coding data ram copy)
///
/// \return void
//-----------------------------------------------------------------------------
void roAdbPxa3_ParaFct0(CONST_AL tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData)
{
  (void) eCmd;
  (void) pData;
  AdbPxa3Data_ParaFct0(eCmd, pData);
}

//-----------------------------------------------------------------------------
/// \brief riAdbPxa3_Init
///
/// \descr Init runnable for AdbPxa3
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void riAdbPxa3_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riAdbPxa3_Init)
#endif

  AdbPxa3Data_Init();
  AdbPxa3_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riAdbPxa3_Init)
#endif
}

//-----------------------------------------------------------------------------
/// \brief rpAdbPxa3_Cycle0
///
/// \descr Cycle function for AdbPxa3
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void rpAdbPxa3_Cycle0(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpAdbPxa3_Cycle0)
#endif

  AdbPxa3_Cycle0();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpAdbPxa3_Cycle0)
#endif
}
