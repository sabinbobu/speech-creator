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
/// \file  SchM.c
///
/// \brief Schedule manager - Used to call the runnables with 1ms cycle time
///                           It contains the implementation of two tasks:
///                           SysVolt and Nvm
///
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include <Rte.h>

#include <Bsw/Sys/Load/SysLoad.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riSchM_Func_NonTrusted_Init)
SYS_LOAD_MEAS_VAR_DEC(rpSchM_Func_NonTrusted_Cycle)
#endif
//=============================================================================
// Function prototypes
//=============================================================================


//extern void rpNvM_Cycle0(void);
#include "ctaaNvm.h"

//extern void rpFee_Cycle0(void);
#include "ctaaFee.h"

//extern void riComStack1_Init(void);
//extern void rrpComStack1_Cycle0(void);
#include <Appl_LGM_Wrap.h>

//extern void rpDem_Cycle0(void);
#include "ctaaDem.h"

//extern void rpErrCust_Cycle0(void);
#include "ctaaErrCust.h"

//extern void riDeh_Init(void);
//extern void rpDeh_Cycle0(void);
#include "ctaaDeh.h"

//extern void riElecInt_Init(void);
//extern void rpElecInt_Cycle(void);
#include "ctaaElecInt.h"

#include <ctaaSigPrepRx.h>
#include <ctaaSigPrepTx.h>

//=============================================================================
// preprocessor definitions
//=============================================================================

#define SCHM_U_CYCLE           100u
#define SCHM_U_NVM_CYCLE         5u
#define SCHM_U_NVM_OFFSET        0u
#define SCHM_U_COM_CYCLE         5u
#define SCHM_U_COM_OFFSET        2u
#define SCHM_U_SIGPREPRX_CYCLE  10u
#define SCHM_U_SIGPREPRX_OFFSET  4u
#define SCHM_U_SIGPREPTX_CYCLE  10u
#define SCHM_U_SIGPREPTX_OFFSET  1u  // Transmission optimized, TX executed before COM Offset
#define SCHM_U_DEM_CYCLE        20u
#define SCHM_U_DEM_OFFSET        6u
#define SCHM_U_ERR_CYCLE       100u
#define SCHM_U_ERR_OFFSET        6u
#define SCHM_U_DEH_CYCLE         5u
#define SCHM_U_DEH_OFFSET        3u

//-----------------------------------------------------------------------------
/// \brief riSchM_Func_NonTrusted_Init
///
/// \descr Function which initialize modules with 1ms cycle time
///
/// \param 
///
/// \return
//-----------------------------------------------------------------------------
void riSchM_Func_NonTrusted_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riSchM_Func_NonTrusted_Init)
#endif

  riSigPrepRx_Init();

  riSigPrepTx_Init();

  riComStack1_Init();

  riDeh_Init();

  riElecInt_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riSchM_Func_NonTrusted_Init)
#endif
}


//-----------------------------------------------------------------------------
/// \brief rpSchM_Func_NonTrusted_Cycle
///
/// \descr Non trusted Os task called with 1ms periodicity
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void rpSchM_Func_NonTrusted_Cycle(void)
{
    static uint8 SchM_U_ucCycleCounter = 0u;
#ifdef SYS_LOAD_RUNNABLE
    SYS_LOAD_MEAS_BEGIN(rpSchM_Func_NonTrusted_Cycle)
#endif

    SchM_U_ucCycleCounter++;
    
    if (SchM_U_ucCycleCounter >= SCHM_U_CYCLE)
    {
        SchM_U_ucCycleCounter = 0u;
    }

    if ((SchM_U_ucCycleCounter % SCHM_U_NVM_CYCLE) == SCHM_U_NVM_OFFSET)
    {
        // call Nvm cyclic runnable
     //   rpNvM_Cycle0();

        // call Fee cyclic runnable
    //    rpFee_Cycle0();
    }

    if ((SchM_U_ucCycleCounter % SCHM_U_COM_CYCLE) == SCHM_U_COM_OFFSET)
    {
        rpComStack1_Cycle0();
    } 

    if ((SchM_U_ucCycleCounter % SCHM_U_SIGPREPRX_CYCLE) == SCHM_U_SIGPREPRX_OFFSET)
    {
        rpSigPrepRx_Cycle();
    }

    if ((SchM_U_ucCycleCounter % SCHM_U_SIGPREPTX_CYCLE) == SCHM_U_SIGPREPTX_OFFSET)
    {
        rpSigPrepTx_Cycle();
    }
      
    if ((SchM_U_ucCycleCounter % SCHM_U_DEM_CYCLE) == SCHM_U_DEM_OFFSET)
    {
        // call Dem cyclic runnable
        rpDem_Cycle0();
    }

    if ((SchM_U_ucCycleCounter % SCHM_U_ERR_CYCLE) == SCHM_U_ERR_OFFSET)
    {
        // call Err cyclic runnable
        rpErrCust_Cycle0();
    }

    if ((SchM_U_ucCycleCounter % SCHM_U_DEH_CYCLE) == SCHM_U_DEH_OFFSET)
    {
        // call Deh cyclic runnable
        rpDeh_Cycle0();

        // call EI cyclic runnable
        rpElecInt_Cycle();
    } 



#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpSchM_Func_NonTrusted_Cycle)
#endif
    //PRQA S 5310 1 // architecture and readabiltiy , architectural limitation on number of runnables that can be defined in RTE Generator with this OS lead to intermediar schedueler manager 
}
void rcMemoryProc(void)
{
		rpNvM_Cycle0();
		rpFee_Cycle0();
}

// EOF
