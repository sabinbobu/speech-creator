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
/// \file   ctaaSysVolt.c
///
/// \brief  Swc SysVolt runnables
///
/// \descr  Init and Cyclic runnable of SysVolt
///
/// \author Henrietta Futo (F31185D)
///         mailTo: henrietta-helena.futo[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// file includes
//=============================================================================

#include <SysVolt.h>
#include <ctaaSysVolt.h>
#include <Cfg/Cfg.h>
#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riSysVoltInit)
SYS_LOAD_MEAS_VAR_DEC(rpSysVolt_Cycle)
#endif

//=============================================================================
// Function definitions
//=============================================================================

/// ---------------------------------------------------------------------------
/// \func     void riSysVoltInit(void)
///
/// \brief    SysVolt init runnable called out from RTE (EcuM Start-Up 2 phase)
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void riSysVoltInit(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riSysVoltInit)
#endif

  SysVolt_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riSysVoltInit)
#endif
}

/// ---------------------------------------------------------------------------
/// \func     rpSysVolt_Cycle
///
/// \brief    SysVolt cyclic runnable called out from RTE (SchM 1ms task)
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void rpSysVolt_Cycle(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpSysVolt_Cycle)
#endif

  SysVolt_Cycle();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpSysVolt_Cycle)
#endif
}

// EOF
