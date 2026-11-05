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
/// \file   ctaaSysMonTx.c
///
/// \brief  
///
/// \descr  Init and Cyclic Runnables for SysMonTx
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <ctaaSysMonTx.h>
#include <SysMonTx.h>
#include <Bsw/Sys/Load/SysLoad.h>
#ifndef UNIT_TEST
#include <Rte.h>
#endif
#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riSysMonTxInit)
SYS_LOAD_MEAS_VAR_DEC(rpSysMonTx_Cycle)
#endif

//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------

/// ---------------------------------------------------------------------------
/// \func     riSysMonTxInit
///
/// \brief    Init runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void riSysMonTxInit(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riSysMonTxInit)
#endif

    SysMonTx_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riSysMonTxInit)
#endif
}


/// ---------------------------------------------------------------------------
/// \func     rpSysMonTx_Cycle
///
/// \brief    Cyclic runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void rpSysMonTx_Cycle(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpSysMonTx_Cycle)
#endif

    SysMonTx_Cycle0();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpSysMonTx_Cycle)
#endif
}


void reSysMonTx_ActivateTxBufer(void)
{
    boolean boEnable;
    (void)Rte_Read_ElecInt_ActivateTxBufer(&boEnable);
    if (boEnable == TRUE)
    {
        SysMonTx_ComM_ActivateTxBufer();
    }
    else
    {
        SysMonTx_ComM_DeactivateTxBuffer();
    }
}

// EOF
