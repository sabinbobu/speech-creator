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
/// \file   ctaaSysMon.c
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
#include <Std_Types.h>
#include <ctaaSysMon.h>
#include <ctaaSysMonCheck.h>
#include <ctaaSysMon_E2E.h>
#include <ctaaSysMonRx.h>
#include <ctaaSysMonTx.h>
#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riSysMon_Init)
SYS_LOAD_MEAS_VAR_DEC(rcSysMon_Cycle1ms)
#endif

#define OFFSET_SYSMON_E2E    4u
#define OFFSET_SYSMON_CHECK  8u
#define OFFSET_SYSMON_RX     6u
#define OFFSET_SYSMON_TX     1u
#define CYCLE_SYSMON        10u

//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------

/// ---------------------------------------------------------------------------
/// \func     riSysMon_Init
///
/// \brief    Init runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void riSysMon_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
    SYS_LOAD_MEAS_BEGIN(riSysMon_Init)
#endif

    riSysMon_E2EInit();
    riSysMonRxInit();
    riSysMonTxInit();
    riSysMonCheckInit();

#ifdef SYS_LOAD_RUNNABLE
    SYS_LOAD_MEAS_END(riSysMon_Init)
#endif
}


/// ---------------------------------------------------------------------------
/// \func     rcSysMon_Cycle1ms
///
/// \brief    Cyclic runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void rcSysMon_Cycle1ms(void)
{
    static uint8 SysMon_ucTimeslot = 0u;
#ifdef SYS_LOAD_RUNNABLE
    SYS_LOAD_MEAS_BEGIN(rcSysMon_Cycle1ms)
#endif
    
    switch (SysMon_ucTimeslot) {
        case OFFSET_SYSMON_E2E: 
            rpSysMon_E2ECycle10ms(); 
            break;
        case OFFSET_SYSMON_RX: 
            rpSysMonRx_Cycle(); 
            break;
        case OFFSET_SYSMON_TX: 
            rpSysMonTx_Cycle(); 
            break;
        case OFFSET_SYSMON_CHECK:
            rpSysMonCheck_Cycle();
            break;
        default: 
            break;
    }
    
    SysMon_ucTimeslot++;
    if (SysMon_ucTimeslot >= CYCLE_SYSMON) {
        SysMon_ucTimeslot = 0u;
    }

#ifdef SYS_LOAD_RUNNABLE
    SYS_LOAD_MEAS_END(rcSysMon_Cycle1ms)
#endif
}

// EOF
