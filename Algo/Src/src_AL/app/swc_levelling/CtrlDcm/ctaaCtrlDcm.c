//*****************************************************************************
// (C) Marelli Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Marelli Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Marelli Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  ctaaCtrlDcm.c
///
/// \brief ctaa wrapper file for CtrlDcm module
///
//-----------------------------------------------------------------------------
#include "ctaaCtrlDcm.h"
#include "CtrlDcmSm.h"
#include "ILCU_LevellingAdapter.h" /* ILCU_PORT: replaces DPE-only <Bsw/Sys/Load/SysLoad.h> (SYS_LOAD_RUNNABLE not defined -> measurement compiled out) */

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riCtrlDcm_Init)
SYS_LOAD_MEAS_VAR_DEC(rpCtrlDcm_Cycle)
#endif

#if defined (CFG_VARIANT_ECO) || defined (UNIT_TEST)// Applicable only for ECO version
//-----------------------------------------------------------------------------
/// \brief  riCtrlDcm_Init
///
/// \descr   init function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void riCtrlDcm_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riCtrlDcmInit)
#endif

    CtrlDcm_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riCtrlDcmInit)
#endif
}

//-----------------------------------------------------------------------------
/// \brief  rpCtrlDcm_Cycle
///
/// \descr   20ms cycle function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void rpCtrlDcm_Cycle(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpCtrlDcm_Cycle)
#endif

  if (CtrlDcm_ReturnSide() == CtrlDcm_eMountedRight)
  {
    CtrlDcm_Slave_Cycle20ms();
  }
  else
  {
    CtrlDcm_Master_Cycle20ms();
  }

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpCtrlDcm_Cycle)
#endif
}
#endif // CFG_VARIANT_ECO
