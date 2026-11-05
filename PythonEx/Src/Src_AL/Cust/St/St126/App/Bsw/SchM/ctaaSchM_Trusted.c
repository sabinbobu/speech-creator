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
/// \file  ctaaSchM_Trusted.c
///
/// \brief Schedule manager - Used to call the runnables with 1ms cycle time
///                           It contains the implementation of two tasks:
///                           CddSpi and IoHwAb
///
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include <Rte.h>
#include <Bsw/Sys/Load/SysLoad.h>


#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riSchM_Func_Trusted_Init)
SYS_LOAD_MEAS_VAR_DEC(rpSchM_Func_Trusted_Cycle)
#endif
//=============================================================================
// Function prototypes
//=============================================================================

//extern void rpIoHwAbUser_Cycle(void);
#include "ctscIoHwAbUser.h"

//extern void rpEcuM_Cycle0(void);
#include "ctscEcuM.h"

#include <ctaaSysCrc.h>

#include "ctscWdgM.h"

//=============================================================================
// preprocessor definitions
//=============================================================================

#define SCHM_T_CYCLE           100u
#define SCHM_T_CRC_CYCLE       100u
#define SCHM_T_CRC_OFFSET       31u
#define SCHM_T_WDG_CYCLE       100u
#define SCHM_T_WDG_OFFSET        1u

//-----------------------------------------------------------------------------
/// \brief riSchM_Func_Trusted_Init
///
/// \descr Init runnable which initialize the following trusted modules,
///        CddSpi and IoHwAb
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void riSchM_Func_Trusted_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riSchM_Func_Trusted_Init)
#endif

  riIoHwAbUserInit();

  riSysCrc_Init();

  riWdgM_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riSchM_Func_Trusted_Init)
#endif
}

//-----------------------------------------------------------------------------
/// \brief rpSchM_Func_Trusted_Cycle
///
/// \descr Cycle runnable for CddSpi and IoHwAb with a periodicity of 1ms
///
/// \param  none
///
/// \return void
//-----------------------------------------------------------------------------
void rpSchM_Func_Trusted_Cycle(void)
{
  static uint8 SchM_T_ucCycleCounter = 0u;
#ifdef SYS_LOAD_RUNNABLE
    SYS_LOAD_MEAS_BEGIN(rpSchM_Func_Trusted_Cycle)
#endif

  SchM_T_ucCycleCounter++;

  if (SchM_T_ucCycleCounter >= SCHM_T_CYCLE)
  {
      SchM_T_ucCycleCounter = 0u;
  }

  rpEcuM_Cycle0();

  // call Io Hw Ab cyclic runnable
  rpIoHwAbUser_Cycle();

  if ((SchM_T_ucCycleCounter % SCHM_T_CRC_CYCLE) == SCHM_T_CRC_OFFSET)
  {
      rpSysCrc_Cycle0();
  }

  if ((SchM_T_ucCycleCounter % SCHM_T_WDG_CYCLE) == SCHM_T_WDG_OFFSET)
  {
      rpWdgM_Cycle0();
  }

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpSchM_Func_Trusted_Cycle)
#endif
}

// EOF
