// *****************************************************************************
// Os_Chk.h
// *****************************************************************************

#ifndef __OS_CHK_H
#define __OS_CHK_H


// -----------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------
#include "RTX_Config.h"


// -----------------------------------------------------------------------------
// preprocessor definitions
// ***** DO NOT CHANGE THE FOLLOWING DEFINITIONS !!! *****
// -----------------------------------------------------------------------------
// MPU Process ID's
#define OS_PID_SYSTEM         0U
#define OS_PID_TRUSTED        1U
#define OS_PID_UNTRUSTED      2U

#if OS_IDLE_THREAD_ZONE != 0
  #error RTX_Config.h : configure OS_IDLE_THREAD_ZONE = 0
#endif

#if OS_TIMER_THREAD_ZONE != 1
  #error RTX_Config.h : configure OS_TIMER_THREAD_ZONE = 1
#endif

#define OS_THREAD_INDEX_BITS  2U

// -----------------------------------------------------------------------------
// type definitions
// -----------------------------------------------------------------------------
// eThread_XYZ_Zone:
// 0y00000000
//         ** - OS_THREAD_INDEX_BITS (2 LSB)
//       ** --- PID (Process Identifier, 2 Bits)
typedef enum
{
  eThread_IDLE_Zone   =  0,   // PID = 0 (System), OS_IDLE_THREAD_ZONE  = 0 (RTX_Config.h)
  eThread_TIMER_Zone  =  1,   // PID = 0 (System), OS_TIMER_THREAD_ZONE = 1 (RTX_Config.h)
  eThread_MAIN_Zone   =  2,   // PID = 0 (System)
  eThread_NONE_Zone   =  3,   // PID = 0 (System)
  eThread_T_LL_Zone   =  4,   // PID = 1 (Trusted)
  eThread_T_LH_Zone   =  5,   // PID = 1 (Trusted)
  eThread_T_HL_Zone   =  6,   // PID = 1 (Trusted)
  eThread_T_HH_Zone   =  7,   // PID = 1 (Trusted)
  eThread_U_LL_Zone   =  8,   // PID = 2 (Untrusted)
  eThread_U_LH_Zone   =  9,   // PID = 2 (Untrusted)
  eThread_U_HL_Zone   = 10,   // PID = 2 (Untrusted)
  eThread_U_HH_Zone   = 11,   // PID = 2 (Untrusted)
  eThread_BufferCount = 12
}eThreadZone_t;


// debug settings for use on eval-board
#if(OS_USE_EVALBOARD == 1)
  void Os_ToggleTestPin(void);
  #define OS_TOGGLE_TESTPIN  Os_ToggleTestPin();
#else
  #define OS_TOGGLE_TESTPIN
#endif

// check configuration in case of TimerThread triggered scheduler
#ifndef OS_TIMER_RTE_CYCLIC
  #define OS_TIMER_RTE_CYCLIC 0
#endif

#ifndef OS_RTE_MONITOR
  #define OS_RTE_MONITOR      0
#endif

#if(OS_TIMER_RTE_CYCLIC == 0)
  #if((OS_TIMER_THREAD_STACK_SIZE != 0) || (OS_TIMER_CB_QUEUE != 0))
    #error "Disable Timer-Thread in RtxConfig.h: Set OS_TIMER_THREAD_STACK_SIZE and  OS_TIMER_CB_QUEUE = 0"
  #endif
#else
  #define OS_TIMER_TIMETICKS        1
  #if((OS_TIMER_THREAD_STACK_SIZE == 0) || (OS_TIMER_CB_QUEUE == 0))
    #error "Enable Timer-Thread in RtxConfig.h: Set OS_TIMER_THREAD_STACK_SIZE and OS_TIMER_CB_QUEUE > 0"
  #endif
#endif

// optimize memory layout for non-debugging versions
#if(OS_OPTIMIZE_FLASH == 1)
  #define OS_TXT_THREAD_MAIN      NULL
  #define OS_TXT_THREAD_T_HH      NULL
  #define OS_TXT_THREAD_T_HL      NULL
  #define OS_TXT_THREAD_T_LH      NULL
  #define OS_TXT_THREAD_T_LL      NULL
  #define OS_TXT_THREAD_U_HH      NULL
  #define OS_TXT_THREAD_U_HL      NULL
  #define OS_TXT_THREAD_U_LH      NULL
  #define OS_TXT_THREAD_U_LL      NULL
  #define OS_TXT_TIMER_RTE        NULL
  #define OS_TXT_EVTFLAG_RTE      NULL
  #if(RTE_SCHEDULE_POLICY == RTE_PREEMPT_FULL)
  #define OS_TXT_MUTEX_PORTSR     NULL
  #elif(RTE_SCHEDULE_POLICY == RTE_PREEMPT_PART)
  #define OS_TXT_MUTEX_PORTSR     NULL
  #define OS_TXT_MUTEX_RTESYNC_T  NULL
  #define OS_TXT_MUTEX_RTESYNC_U  NULL
  #elif(RTE_SCHEDULE_POLICY == RTE_PREEMPT_NONE)
  #define OS_TXT_MUTEX_RTESYNC    NULL
  #endif
  #define OS_TXT_MSGQUEUE_INIT_T  NULL
  #define OS_TXT_MSGQUEUE_INIT_U  NULL
#else
  #define OS_TXT_THREAD_MAIN      "thread_Main"
  #define OS_TXT_THREAD_T_HH      "thread_T_HH"
  #define OS_TXT_THREAD_T_HL      "thread_T_HL"
  #define OS_TXT_THREAD_T_LH      "thread_T_LH"
  #define OS_TXT_THREAD_T_LL      "thread_T_LL"
  #define OS_TXT_THREAD_U_HH      "thread_U_HH"
  #define OS_TXT_THREAD_U_HL      "thread_U_HL"
  #define OS_TXT_THREAD_U_LH      "thread_U_LH"
  #define OS_TXT_THREAD_U_LL      "thread_U_LL"
  #define OS_TXT_TIMER_RTE        "timer_RTE"
  #define OS_TXT_EVTFLAG_RTE      "evtflag_RTE"
  #if(RTE_SCHEDULE_POLICY == RTE_PREEMPT_FULL)
  #define OS_TXT_MUTEX_PORTSR     "mutex_PORTSR"
  #elif(RTE_SCHEDULE_POLICY == RTE_PREEMPT_PART)
  #define OS_TXT_MUTEX_PORTSR     "mutex_PORTSR"
  #define OS_TXT_MUTEX_RTESYNC_T  "mutex_RTESYNC_T"
  #define OS_TXT_MUTEX_RTESYNC_U  "mutex_RTESYNC_U"
  #elif(RTE_SCHEDULE_POLICY == RTE_PREEMPT_NONE)
  #define OS_TXT_MUTEX_RTESYNC    "mutex_RTESYNC"
  #endif
  #define OS_TXT_MSGQUEUE_INIT_T  "msgqueue_INIT_T"
  #define OS_TXT_MSGQUEUE_INIT_U  "msgqueue_INIT_U"
#endif

// *** EventRecorder checks/settings/includes ***
  #include "Os_EvtRec.h"
  #include "Rte_EvtRec.h"

  #if defined(EVTREC_ENABLE_SWC) && (EVTREC_ENABLE_SWC != EventRecordNone)
    #include "Swc_EvtRec.h"
  #endif
//#endif

#endif // __OS_CHK_H
