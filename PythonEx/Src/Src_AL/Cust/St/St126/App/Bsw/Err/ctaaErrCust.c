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
/// \file  ctaaErrCust.c
///
/// \brief  ctaaErrCust
///
/// \descr  Init and Cyclic Runnables for ErrCust
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <ErrCust.h>
#include <ctaaErrCust.h>
#include <Bsw/Sys/Load/SysLoad.h>
#include <EcuM.h>

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riErrCust_Init)
SYS_LOAD_MEAS_VAR_DEC(rpErrCust_Cycle0)
#endif

#if (CFG_DEV_HOOK_EN == 1u) || defined (UNIT_TEST)
#define ERRCUST_MPU_ACCESS_FAULT_HOOK_ACTIVATION      20212022u
STATIC_AL volatile uint32 ErrCust_ulMPU_Trigger_Fault_Hook = 0u;
#endif

//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/// \brief  riErrCust_Init
///
/// \descr  ErrCust init function
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void riErrCust_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riErrCust_Init)
#endif

    ErrCust_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riErrCust_Init)
#endif 
}


//-----------------------------------------------------------------------------
/// \brief  rpErrCust_Cycle0
///
/// \descr  ErrCust cycle function
///
/// \param  void
///
/// \return void 
//-----------------------------------------------------------------------------
void rpErrCust_Cycle0(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpErrCust_Cycle0)
#endif

 // MPU Fault hook
#if (CFG_DEV_HOOK_EN == 1u) || defined (UNIT_TEST)

    // Trusted address getter pointer
    uint32 *pulErrCust_MPU_Address_Fault = NULL_PTR;

    // Check hook activation
    if (ErrCust_ulMPU_Trigger_Fault_Hook == ERRCUST_MPU_ACCESS_FAULT_HOOK_ACTIVATION)
    {
      // Reset hook to avoid locking to the MPU error
      ErrCust_ulMPU_Trigger_Fault_Hook = 0u;
      // Get trusted address
      // PRQA S 316 1 // program architecture and readability - intentionally no modification of existing code
      pulErrCust_MPU_Address_Fault = (uint32*)EcuM_Get_Mpu_Test_Hook_Address();
      // write dummy data
      *pulErrCust_MPU_Address_Fault = 2022u;
    }
#endif


    ErrCust_Cycle0();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpErrCust_Cycle0)
#endif
}

//EOF
