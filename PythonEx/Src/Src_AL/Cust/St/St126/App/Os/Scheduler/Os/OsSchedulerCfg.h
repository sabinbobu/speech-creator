// ****************************************************************************
// NOTE: Do not implement any file guard.
// This file will be multiply included for the macro table generations.
// ****************************************************************************

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
/// \file  OsSchedulerCfg.h
///
/// \brief  
///
/// \descr  
///
/// \author Cosmin Cojocaru (f11501c)
///         mailTo:constantin-cosmin.cojocaru(at)marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \file  OsCfg.h
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================

#include <Std_Types.h>
#include <OsSchedulerMac.h>
#include <Sys/Idle/SysIdle.h>
#include <Util_Time.h>

#if !defined(OS_TASK_IDLE)
  #define OS_TASK_IDLE() SysIdle_OsIdleTask()
#endif

// *****************************************************************************
// Configure the operating system tasks.
// The offset represents the first call time
// of the tasks during start of the OS.
// The order of the tasks represents the
// task priority, where the 0th entry has
// the highest priority.
// *****************************************************************************

// *****************************************************************************
// Use prime numbers for offsets.
// Use Wolfram's alpha or Mathematica(R): Table[Prime[n], {n, 50, 4000, 50}]
// to obtain:
//   229,   541,   863,  1223,  1583,  1987,  2357,  2741,  3181,  3571,
//  3989,  4409,  4831,  5279,  5693,  6133,  6571,  6997,  7499,  7919,
//  8387,  8831,  9283,  9733, 10177, 10657, 11149, 11657, 12109, 12553,
// 13007, 13499, 13967, 14519, 14947, 15401, 15881, 16381, 16903, 17389,
// 17891, 18313, 18899, 19423, 19891, 20357, 20897, 21383, 21841, 22307,
// 22817, 23321, 23827, 24281, 24877, 25391, 25913, 26399, 26891, 27449,
// 27947, 28499, 28933, 29443, 30059, 30559, 31091, 31601, 32159, 32609,
// 33113, 33613, 34157, 34649, 35159, 35759, 36277, 36781, 37309, 37813
// *****************************************************************************

BEGIN_OS_TASK_MAP()
  //         Function                         Cycle [us]                        Offset [us]
  TASK_CFG( Appl_LGM_Wrap_LGM_Scheduler2,     UTILTIME_USEC(   5000U),          UTILTIME_USEC(  229U))
  TASK_CFG( Appl_LGM_Wrap_LGM_Scheduler1,     UTILTIME_USEC(   5000U),          UTILTIME_USEC(  521U))
  TASK_CFG( Appl_LGM_Wrap_Function_Test,      UTILTIME_USEC(  10000U),          UTILTIME_USEC( 1583U))
#ifdef CPU_S32K146
  TASK_CFG( CddMlcCycle,                      UTILTIME_USEC(  10000U),          UTILTIME_USEC( 1987U))
#endif
  TASK_CFG( CddSpi_Cyclic,                    UTILTIME_USEC(   1000U),          UTILTIME_USEC( 5693U))
  TASK_CFG( IoHwAbUser_Cycle0,                UTILTIME_USEC(   5000U),          UTILTIME_USEC( 6133U))
  TASK_CFG( IoHwAbUser_EmuVbatIrq,            UTILTIME_USEC(    312U),          UTILTIME_USEC( 6571U)) //just for emulating the timer interrupt until implemented
  TASK_CFG( SigPrepRx_Cycle0,                 UTILTIME_USEC(  10000U),          UTILTIME_USEC( 6997U))
  TASK_CFG( SigPrepTx_Cycle0,                 UTILTIME_USEC(   5000U),          UTILTIME_USEC( 7499U))
  TASK_CFG( SysMon_Cycle0,                    UTILTIME_USEC(  10000U),          UTILTIME_USEC( 7919U))
  TASK_CFG( SysVolt_Cycle1ms,                 UTILTIME_USEC(   1000U),          UTILTIME_USEC( 8831U))
  TASK_CFG( FctR_Cycle10ms,                   UTILTIME_USEC(  10000U),          UTILTIME_USEC( 9283U))
  TASK_CFG( Dbl_Cycle5ms,                     UTILTIME_USEC(  5000U),            UTILTIME_USEC( 9733))
  TASK_CFG( Dem_Cycle0,                       UTILTIME_USEC(  20000U),          UTILTIME_USEC( 9733U))
  TASK_CFG( ErrCust_Cycle0,                   UTILTIME_USEC(  20000U),          UTILTIME_USEC( 10657U))
  TASK_CFG(CddStp_10ms,                       UTILTIME_USEC(  10000U),          UTILTIME_USEC( 8387U))

  TASK_CFG( CtrlStp_Cycle10ms,                UTILTIME_USEC(  10000U),          UTILTIME_USEC( 15401U))
  TASK_CFG( CddSwi_Cycle,                     UTILTIME_USEC(   10000U),         UTILTIME_USEC( 8831U))
  TASK_CFG( CtrlFan_Cycle,                    UTILTIME_USEC(   10000U),         UTILTIME_USEC( 9283U))

  TASK_CFG( Mxb_Cycle0,                       UTILTIME_USEC(  20000U),          UTILTIME_USEC( 9733U))
END_OS_TASK_MAP()
