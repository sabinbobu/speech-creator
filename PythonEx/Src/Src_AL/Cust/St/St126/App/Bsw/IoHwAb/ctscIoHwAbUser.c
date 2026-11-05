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
/// \file   ctscIoHwAbUser.c
///
/// \brief  
///
/// \descr  Init and Cyclic Runnables for IoHwAb
///
/// \author Futo Henrietta(F31185D)
///         mailTo:henrietta-helena.futo[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "ctscIoHwAbUser.h"
#include "IoHwAbUser.h"
#ifndef UNIT_TEST
#include <Rte.h>
#endif

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riIoHwAbUserInit)
SYS_LOAD_MEAS_VAR_DEC(rpIoHwAbUser_Cycle)
#endif

//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \brief Initialisation runnable
///
/// \descr initialisation runnable for IoHwAbUser
///        Call init function IoHwAbUser_Init()
///        Calling once at start up.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void riIoHwAbUserInit(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riIoHwAbUserInit)
#endif

    IoHwAbUser_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riIoHwAbUserInit)
#endif 
}

//-----------------------------------------------------------------------------
/// \brief  De-initialisation runnable.
///
/// \descr  Call de-initialize function IoHwAbUser_DeInit()
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void riIoHwAbUserDeInit(void)
{
  IoHwAbUser_DeInit();
}

//-----------------------------------------------------------------------------
/// \brief  Cyclic runnable
///
/// \descr  Call cyclic function for IoHwAbUser
///         Calling IoHwAbUser_Cycle() every 1 ms
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void rpIoHwAbUser_Cycle(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpIoHwAbUser_Cycle)
#endif

    IoHwAbUser_Cycle();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpIoHwAbUser_Cycle)
#endif 
}

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
//-----------------------------------------------------------------------------
/// \brief reIoHwAbUser_GetLssDiagnostic
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void reIoHwAbUser_GetLssDiagnostic(void)
{
  tScrollingPresent_Stat sLssDiagStatus;
  (void)Rte_Read_CddSwi_ScrollingOn_Stat(&sLssDiagStatus);
  IoHwAbUser_SetLSSDiagnostic(sLssDiagStatus.boScrollingTIPresent_Stat | sLssDiagStatus.boScrollingDRLPresent_Stat);
}
#endif

// EOF
