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
/// \file   ctaaSysMonRx.c
///
/// \brief  
///
/// \descr  Init and Cyclic Runnables for SysMon
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <ctaaSysMonRx.h>
#include <SysMonRx.h>
#include <Bsw/Sys/Load/SysLoad.h>
#ifndef UNIT_TEST
#include <Rte.h>
#endif
#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riSysMonRxInit)
SYS_LOAD_MEAS_VAR_DEC(rpSysMonRx_Cycle)
#endif

//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------

/// ---------------------------------------------------------------------------
/// \func     riSysMonRxInit
///
/// \brief    Init runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void riSysMonRxInit(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riSysMonRxInit)
#endif

  SysMonRx_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riSysMonRxInit)
#endif
}


/// ---------------------------------------------------------------------------
/// \func     rpSysMonRx_Cycle
///
/// \brief    Cyclic runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void rpSysMonRx_Cycle(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpSysMonRx_Cycle)
#endif

  SysMonRx_Cycle0();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpSysMonRx_Cycle)
#endif
}


void reSysMonRx_EnableCallbacks(void)
{
    boolean boEnable;
    (void)Rte_Read_ElecInt_EnableCallbacks(&boEnable);
    if (boEnable == TRUE)
    {
        SysMonRx_ComM_EnableCallbacks();
    }
    else
    {
        SysMonRx_ComM_DisableCallbacks();
    }
}

// EOF
