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
/// \file   ctaaStatM.c
///
/// \brief  
///
/// \descr  Init and Cyclic Runnables for StatM
///
/// \author Liviu Topliceanu (F03343C)
///         mailTo:liviu.topliceanu[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <Swc/StatM/ctaaStatM.h>
#include <Swc/StatM/StatM.h>
#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riStatM_Init)
SYS_LOAD_MEAS_VAR_DEC(rcStatM__Cycle10ms)
SYS_LOAD_MEAS_VAR_DEC(reStatM_Deinit)
SYS_LOAD_MEAS_VAR_DEC(reStatM_ResetStatistics)
#endif


//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------

/// ---------------------------------------------------------------------------
/// \func     riStatM_Init
///
/// \brief    Init runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void riStatM_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
    SYS_LOAD_MEAS_BEGIN(riStatM_Init)
#endif

    StatM_Init();

#ifdef SYS_LOAD_RUNNABLE
    SYS_LOAD_MEAS_END(riStatM_Init)
#endif
}


/// ---------------------------------------------------------------------------
/// \func     rcStatM_Cycle10ms
///
/// \brief    Cyclic runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void rcStatM_Cycle10ms(void)
{
#ifdef SYS_LOAD_RUNNABLE
    SYS_LOAD_MEAS_BEGIN(rcStatM_Cycle10ms)
#endif
    
    StatM_Cycle0();
	
#ifdef SYS_LOAD_RUNNABLE
    SYS_LOAD_MEAS_END(rcStatM_Cycle10ms)
#endif
}


/// ---------------------------------------------------------------------------
/// \func     reStatM_Deinit
///
/// \brief    Event runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void reStatM_Deinit(void)
{
#ifdef SYS_LOAD_RUNNABLE
    SYS_LOAD_MEAS_BEGIN(reStatM_Deinit)
#endif

        StatM_Deinit();

#ifdef SYS_LOAD_RUNNABLE
    SYS_LOAD_MEAS_END(reStatM_Deinit)
#endif
}


void reStatM_ResetStatistics(void)
{
#ifdef SYS_LOAD_RUNNABLE
    SYS_LOAD_MEAS_BEGIN(reStatM_ResetStatistics)
#endif

        StatM_ResetStatistics();

#ifdef SYS_LOAD_RUNNABLE
    SYS_LOAD_MEAS_END(reStatM_ResetStatistics)
#endif
}
// EOF
