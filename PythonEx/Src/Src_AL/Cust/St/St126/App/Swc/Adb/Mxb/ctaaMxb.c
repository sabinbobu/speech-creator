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
/// \file   ctaaMxb.c
///
/// \brief  MXB (Matrix Beam)
///
/// \descr  Adb control functions for MXB Model
///
///         Additional information can be found in the design description
///        
///
/// \author Vornicu, Tony ALRT/EEG (F63906B)
///         mailTo:tony.vornicu@marelli.com
//-----------------------------------------------------------------------------

#include <CodM.h>
#include <AL_Helper.h>

#include "AdbMxb4.h"
#include "AdbMxb4Data.h"
#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riMxb_Init)
SYS_LOAD_MEAS_VAR_DEC(rpMxb_Cycle0)
#endif

//-----------------------------------------------------------------------------
/// \brief  Mxb coding parameters
///
/// \param  eCmd (coding data valid / invalid)
/// \param  pData (pointer to coding data ram copy)
///
/// \return void
//-----------------------------------------------------------------------------
void roAdb_ParaFct0(CONST_AL tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData)
{
  AdbMxb4Data_ParaFct0(eCmd, pData);
}

//-----------------------------------------------------------------------------
/// \brief  riMxb_Init Mxb Initialization
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void riMxb_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riMxb_Init)
#endif

  AdbMxb4Data_Init();
  AdbMxb4_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riMxb_Init)
#endif
}

//-----------------------------------------------------------------------------
/// \brief  rpMxb_Cycle0 Cyclic runnable for Mxb
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void rpMxb_Cycle0(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpMxb_Cycle0)
#endif

  AdbMxb4_Cycle0();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpMxb_Cycle0)
#endif
}