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
/// \file   ctscCddSbc.c
///
/// \brief  ctscCddSbc
///
/// \descr  Init and Cyclic Runnables for CddSbc
///
/// \author Diana Ursan
/// \e-mail: elena-diana.ursan[at]marelli.com
///
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <CddSbc.h>
#include <ctscCddSbc.h>
#include <Bsw/Sys/Load/SysLoad.h>
#ifndef UNIT_TEST
#include <Rte.h>
#endif

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(rpCddSbc_Cycle0)
#endif

//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/// \brief  riCddSbc_Init
///
/// \descr  CddSbc_Init init function
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void riCddSbc_Init(void) 
{
    //Not need for Release 2, Dummy function for the moment 
    //The initialization of CddSbc is doe at the beginning
    return;
}


//-----------------------------------------------------------------------------
/// \brief  rpCddSbc_Cycle0
///
/// \descr  CddSbc cycle function
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void rpCddSbc_Cycle0(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpCddSbc_Cycle0)
#endif

  CddSbc_Cycle0();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpCddSbc_Cycle0)
#endif
}

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
//-----------------------------------------------------------------------------
/// \brief reCddSbc_SetLssPwm
///
/// \descr Event runnable for LSS pwm duty cycle request
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void reCddSbc_SetLssPwm(void)
{
  // LSS PWM
  uint16 unLssPwm = 0u;
  // Rte read
  (void)Rte_Read_CddSwi_SetLssPwm_Req(&unLssPwm);
  // Set LSS PWM
  CddSbc_SetPWM(unLssPwm);
}
#endif

//EOF

