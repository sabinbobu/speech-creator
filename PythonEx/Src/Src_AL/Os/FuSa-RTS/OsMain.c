// *****************************************************************************
// OsMain.c
//
//
// *****************************************************************************

// -----------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "device_registers.h"           /* Device header */
#include "cmsis_os2.h"                  /* ::CMSIS:RTOS2 */
#include "rtx_os.h"
#include "RTX_Config.h"
#include "RTX_Config_CPUload.h"
#include "Rte_Chk.h"
#include "Os_Cfg.h"
#include "Os_MemMap.h"
#include "Os_Mpu.h"
#include "Os_SvcUser.h"
#include "Rte.h"


// -----------------------------------------------------------------------------
// preprocessor definitions
// -----------------------------------------------------------------------------
// set thread_Main to highest priority (keep in mind: OS_TIMER_THREAD_PRIO = oSPriorityHigh !)
#define OS_THREAD_PRIO_MAIN           osPriorityRealtime

#define OS_THREAD_PRIO_RTE_T_HH       osPriorityNormal7
#define OS_THREAD_PRIO_RTE_T_HL       osPriorityNormal6
#define OS_THREAD_PRIO_RTE_T_LH       osPriorityNormal5
#define OS_THREAD_PRIO_RTE_T_LL       osPriorityNormal4
#define OS_THREAD_PRIO_RTE_U_HH       osPriorityNormal3
#define OS_THREAD_PRIO_RTE_U_HL       osPriorityNormal2
#define OS_THREAD_PRIO_RTE_U_LH       osPriorityNormal1
#define OS_THREAD_PRIO_RTE_U_LL       osPriorityNormal

#define OS_MSGQUEUE_INIT_MSGCOUNT     1
#define OS_MSGQUEUE_INIT_TYPE         void*
#define OS_MSGQUEUE_INIT_MSGSIZE      sizeof(OS_MSGQUEUE_INIT_TYPE)


#if((RTE_SCHEDULE_POLICY != RTE_PREEMPT_FULL) && \
    (RTE_SCHEDULE_POLICY != RTE_PREEMPT_PART) && \
    (RTE_SCHEDULE_POLICY != RTE_PREEMPT_NONE))
  #error "Invalid RTE_SCHEDULE_POLICY value specified"
#endif

// -----------------------------------------------------------------------------
// typedefinitions
// -----------------------------------------------------------------------------
typedef enum
{
  #if(OS_TIMER_RTE_CYCLIC == 1)
  eOsTimer_Rte,
  #endif
  eOsTimer_Count
}eOsTimerID_t;

typedef enum
{
  eOsMsgQueue_InitTrusted,
  eOsMsgQueue_InitUntrusted,
  eOsMsgQueue_InitCount
}eOsMsgQueue_Init_t;

// -----------------------------------------------------------------------------
// function prototypes
// -----------------------------------------------------------------------------
static void Os_RtePrepare(void);
static void Os_RteTriggerInitRunnables(void);
static void Os_RteStart(void);

void osRtxMpuLoad(osThreadId_t threadID);
void thread_Main_func(void *argument);

//extern functions
void osFaultResume(void);

// -----------------------------------------------------------------------------
// vars, constants
// -----------------------------------------------------------------------------
volatile uint32_t   OsBusFaultCount  = 0;
volatile uint32_t   OsUsageFaultCount= 0;

#if(OS_TIMER_RTE_CYCLIC == 0)
bool                OsRteCyclic = false;
#endif

uint8_t OsMsgQueue_Memory_Init[eOsMsgQueue_InitCount][osRtxMessageQueueMemSize(OS_MSGQUEUE_INIT_MSGCOUNT, OS_MSGQUEUE_INIT_MSGSIZE)];


// -----------------------------------------------------------------------------
// OS-Object-IDs (filled during startup)
// -----------------------------------------------------------------------------
// Thread-IDs
osThreadId_t        OsMainThreadID;
osThreadId_t        OsRteThreadID[eRteThreadCount];

// Timer-IDs
osTimerId_t         OsTimerID[eOsTimer_Count];

// EventFlag-IDs
osEventFlagsId_t    OsEvtFlagID_RteThreads;

// Mutex-IDs
#if(RTE_SCHEDULE_POLICY == RTE_PREEMPT_NONE)
osMutexId_t         OsMutexID_RteSchedule;
#elif(RTE_SCHEDULE_POLICY == RTE_PREEMPT_PART)
osMutexId_t         OsMutexID_RteSchedule_T;
osMutexId_t         OsMutexID_RteSchedule_U;
osMutexId_t         OsMutexID_RtePortSR;
#elif(RTE_SCHEDULE_POLICY == RTE_PREEMPT_FULL)
osMutexId_t         OsMutexID_RtePortSR;
#endif

// MsgQueue-IDs
osMessageQueueId_t  OsMsgQueueID_Init[eOsMsgQueue_InitCount];

// -----------------------------------------------------------------------------
// OS-Object-ControlBlocks
// -----------------------------------------------------------------------------
// Thread-CBs
__attribute__((section(".bss.os.thread.cb")))
osRtxThread_t OsMainThreadTcb[1];

__attribute__((section(".bss.os.thread.cb")))
osRtxThread_t OsRteThreadTcb[eRteThreadCount];

// Timer-CBs
#if(OS_TIMER_RTE_CYCLIC == 1)
// *** memory space for Timer-Control-Blocks ***
__attribute__((section(".bss.os.timer.cb")))
osRtxTimer_t OsTimerCb[eOsTimer_Count];
#endif

// EventFlag-CBs
__attribute__((section(".bss.os.evflags.cb")))
osRtxEventFlags_t   OsEvtFlagCb_RteThreads[1];

// Mutex-CBs
#if(RTE_SCHEDULE_POLICY == RTE_PREEMPT_NONE)
__attribute__((section(".bss.os.mutex.cb")))
osRtxMutex_t   OsMutexCb_RteRunnableSync;
#elif(RTE_SCHEDULE_POLICY == RTE_PREEMPT_PART)
__attribute__((section(".bss.os.mutex.cb")))
osRtxMutex_t   OsMutexCb_RteRunnableSync_T;
__attribute__((section(".bss.os.mutex.cb")))
osRtxMutex_t   OsMutexCb_RteRunnableSync_U;
__attribute__((section(".bss.os.mutex.cb")))
osRtxMutex_t   OsMutexCb_RtePortSR;
#elif(RTE_SCHEDULE_POLICY == RTE_PREEMPT_FULL)
__attribute__((section(".bss.os.mutex.cb")))
osRtxMutex_t   OsMutexCb_RtePortSR;
#endif

// MsgQueue-CBs
__attribute__((section(".bss.os.msgqueue.cb")))
osRtxMessageQueue_t OsMsgQueueCb_Init[eOsMsgQueue_InitCount];

// -----------------------------------------------------------------------------
// OS-Thread-Stacks
// -----------------------------------------------------------------------------
__attribute__((section(".bss.thread_Main_stack")))
uint64_t thread_Main_stack[OS_MAIN_THREAD_STACKSIZE / 8];

#if(RTE_THREAD_T_HH > 0)
__attribute__((section(".bss.thread_T_HH_stack")))
uint64_t thread_T_HH_stack[RTE_THREAD_T_HH / 8];
#endif

#if(RTE_THREAD_T_HL > 0)
__attribute__((section(".bss.thread_T_HL_stack")))
uint64_t thread_T_HL_stack[RTE_THREAD_T_HL / 8];
#endif

#if(RTE_THREAD_T_LH > 0)
__attribute__((section(".bss.thread_T_LH_stack")))
uint64_t thread_T_LH_stack[RTE_THREAD_T_LH / 8];
#endif

#if(RTE_THREAD_T_LL > 0)
__attribute__((section(".bss.thread_T_LL_stack")))
uint64_t thread_T_LL_stack[RTE_THREAD_T_LL / 8];
#endif

#if(RTE_THREAD_U_HH > 0)
__attribute__((section(".bss.thread_U_HH_stack")))
uint64_t thread_U_HH_stack[RTE_THREAD_U_HH / 8];
#endif

#if(RTE_THREAD_U_HL > 0)
__attribute__((section(".bss.thread_U_HL_stack")))
uint64_t thread_U_HL_stack[RTE_THREAD_U_HL / 8];
#endif

#if(RTE_THREAD_U_LH > 0)
__attribute__((section(".bss.thread_U_LH_stack")))
uint64_t thread_U_LH_stack[RTE_THREAD_U_LH / 8];
#endif

#if(RTE_THREAD_U_LL > 0)
__attribute__((section(".bss.thread_U_LL_stack")))
uint64_t thread_U_LL_stack[RTE_THREAD_U_LL / 8];
#endif


// -----------------------------------------------------------------------------
// OS-Object-ConfigurationBlocks
// -----------------------------------------------------------------------------
// Thread-ConfigurationBlocks
const osThreadAttr_t thread_Main_attr = 
{
  .name       = OS_TXT_THREAD_MAIN,
  .attr_bits  = osThreadDetached | osThreadPrivileged | osThreadZone(eThread_MAIN_Zone),
  .cb_mem     = &OsMainThreadTcb[0],
  .cb_size    = sizeof(osRtxThread_t),
  .stack_mem  = &thread_Main_stack[0],
  .stack_size = sizeof(thread_Main_stack),
  .priority   = OS_THREAD_PRIO_MAIN
};

#if(RTE_THREAD_T_HH > 0)
const osThreadAttr_t thread_T_HH_attr = 
{
  .name       = OS_TXT_THREAD_T_HH,
  .attr_bits  = osThreadDetached | osThreadUnprivileged | osThreadZone(eThread_T_HH_Zone),
  .cb_mem     = &OsRteThreadTcb[eRteThread_T_HH],
  .cb_size    = sizeof(osRtxThread_t),
  .stack_mem  = &thread_T_HH_stack[0],
  .stack_size = sizeof(thread_T_HH_stack),
  .priority   = OS_THREAD_PRIO_RTE_T_HH
};
#endif

#if(RTE_THREAD_T_HL > 0)
const osThreadAttr_t thread_T_HL_attr = 
{
  .name       = OS_TXT_THREAD_T_HL,
  .attr_bits  = osThreadDetached | osThreadUnprivileged | osThreadZone(eThread_T_HL_Zone),
  .cb_mem     = &OsRteThreadTcb[eRteThread_T_HL],
  .cb_size    = sizeof(osRtxThread_t),
  .stack_mem  = &thread_T_HL_stack[0],
  .stack_size = sizeof(thread_T_HL_stack),
  .priority   = OS_THREAD_PRIO_RTE_T_HL
};
#endif

#if(RTE_THREAD_T_LH > 0)
const osThreadAttr_t thread_T_LH_attr = 
{
  .name       = OS_TXT_THREAD_T_LH,
  .attr_bits  = osThreadDetached | osThreadUnprivileged | osThreadZone(eThread_T_LH_Zone),
  .cb_mem     = &OsRteThreadTcb[eRteThread_T_LH],
  .cb_size    = sizeof(osRtxThread_t),
  .stack_mem  = &thread_T_LH_stack[0],
  .stack_size = sizeof(thread_T_LH_stack),
  .priority   = OS_THREAD_PRIO_RTE_T_LH
};
#endif

#if(RTE_THREAD_T_LL > 0)
const osThreadAttr_t thread_T_LL_attr = 
{
  .name       = OS_TXT_THREAD_T_LL,
  .attr_bits  = osThreadDetached | osThreadUnprivileged | osThreadZone(eThread_T_LL_Zone),
  .cb_mem     = &OsRteThreadTcb[eRteThread_T_LL],
  .cb_size    = sizeof(osRtxThread_t),
  .stack_mem  = &thread_T_LL_stack[0],
  .stack_size = sizeof(thread_T_LL_stack),
  .priority   = OS_THREAD_PRIO_RTE_T_LL
};
#endif

#if(RTE_THREAD_U_HH > 0)
const osThreadAttr_t thread_U_HH_attr = 
{
  .name       = OS_TXT_THREAD_U_HH,
  .attr_bits  = osThreadDetached | osThreadUnprivileged | osThreadZone(eThread_U_HH_Zone),
  .cb_mem     = &OsRteThreadTcb[eRteThread_U_HH],
  .cb_size    = sizeof(osRtxThread_t),
  .stack_mem  = &thread_U_HH_stack[0],
  .stack_size = sizeof(thread_U_HH_stack),
  .priority   = OS_THREAD_PRIO_RTE_U_HH
};
#endif

#if(RTE_THREAD_U_HL > 0)
const osThreadAttr_t thread_U_HL_attr = 
{
  .name       = OS_TXT_THREAD_U_HL,
  .attr_bits  = osThreadDetached | osThreadUnprivileged | osThreadZone(eThread_U_HL_Zone),
  .cb_mem     = &OsRteThreadTcb[eRteThread_U_HL],
  .cb_size    = sizeof(osRtxThread_t),
  .stack_mem  = &thread_U_HL_stack[0],
  .stack_size = sizeof(thread_U_HL_stack),
  .priority   = OS_THREAD_PRIO_RTE_U_HL
};
#endif

#if(RTE_THREAD_U_LH > 0)
const osThreadAttr_t thread_U_LH_attr = 
{
  .name       = OS_TXT_THREAD_U_LH,
  .attr_bits  = osThreadDetached | osThreadUnprivileged | osThreadZone(eThread_U_LH_Zone),
  .cb_mem     = &OsRteThreadTcb[eRteThread_U_LH],
  .cb_size    = sizeof(osRtxThread_t),
  .stack_mem  = &thread_U_LH_stack[0],
  .stack_size = sizeof(thread_U_LH_stack),
  .priority   = OS_THREAD_PRIO_RTE_U_LH
};
#endif

#if(RTE_THREAD_U_LL > 0)
const osThreadAttr_t thread_U_LL_attr = 
{
  .name       = OS_TXT_THREAD_U_LL,
  .attr_bits  = osThreadDetached | osThreadUnprivileged | osThreadZone(eThread_U_LL_Zone),
  .cb_mem     = &OsRteThreadTcb[eRteThread_U_LL],
  .cb_size    = sizeof(osRtxThread_t),
  .stack_mem  = &thread_U_LL_stack[0],
  .stack_size = sizeof(thread_U_LL_stack),
  .priority   = OS_THREAD_PRIO_RTE_U_LL
};
#endif

// Timer-ConfigurationBlocks
#if(OS_TIMER_RTE_CYCLIC == 1)
const osTimerAttr_t timer_RTE_attr = 
{
  .name       = OS_TXT_TIMER_RTE,
  .attr_bits  = 0,
  .cb_mem     = &OsTimerCb[eOsTimer_Rte],
  .cb_size    = sizeof(osRtxTimer_t)
};
#endif

// EventFlag-ConfigurationBlocks
const osEventFlagsAttr_t OS_EvtFlag_RteThreads_attr = 
{
  .name       = OS_TXT_EVTFLAG_RTE,
  .attr_bits  = 0,
  .cb_mem     = &OsEvtFlagCb_RteThreads[0],
  .cb_size    = sizeof(osRtxEventFlags_t)
};

// Mutex-ConfigurationBlocks
#if(RTE_SCHEDULE_POLICY == RTE_PREEMPT_NONE)
const osMutexAttr_t OS_Mutex_RteSchedule_attr = 
{
  .name       = OS_TXT_MUTEX_RTESYNC,
  .attr_bits  = osMutexPrioInherit,
  .cb_mem     = &OsMutexCb_RteRunnableSync,
  .cb_size    = sizeof(OsMutexCb_RteRunnableSync)
};
#elif(RTE_SCHEDULE_POLICY == RTE_PREEMPT_PART)
const osMutexAttr_t OS_Mutex_RteSchedule_T_attr = 
{
  .name       = OS_TXT_MUTEX_RTESYNC_T,
  .attr_bits  = osMutexPrioInherit,
  .cb_mem     = &OsMutexCb_RteRunnableSync_T,
  .cb_size    = sizeof(OsMutexCb_RteRunnableSync_T)
};
const osMutexAttr_t OS_Mutex_RteSchedule_U_attr = 
{
  .name       = OS_TXT_MUTEX_RTESYNC_U,
  .attr_bits  = osMutexPrioInherit,
  .cb_mem     = &OsMutexCb_RteRunnableSync_U,
  .cb_size    = sizeof(OsMutexCb_RteRunnableSync_U)
};
const osMutexAttr_t OS_Mutex_RtePortSR_attr = 
{
  .name       = OS_TXT_MUTEX_PORTSR,
  .attr_bits  = osMutexPrioInherit,
  .cb_mem     = &OsMutexCb_RtePortSR,
  .cb_size    = sizeof(OsMutexCb_RtePortSR)
};
#elif(RTE_SCHEDULE_POLICY == RTE_PREEMPT_FULL)
const osMutexAttr_t OS_Mutex_RtePortSR_attr = 
{
  .name       = OS_TXT_MUTEX_PORTSR,
  .attr_bits  = osMutexPrioInherit,
  .cb_mem     = &OsMutexCb_RtePortSR,
  .cb_size    = sizeof(OsMutexCb_RtePortSR)
};
#endif

// MsgQueue-ConfigurationBlocks
const osMessageQueueAttr_t OS_MsgQueue_Init_attr[eOsMsgQueue_InitCount] =
{
  {
    .name       = OS_TXT_MSGQUEUE_INIT_T,
    .attr_bits  = 0,
    .cb_mem     = &OsMsgQueueCb_Init[eOsMsgQueue_InitTrusted],
    .cb_size    = sizeof(osRtxMessageQueue_t),
    .mq_mem     = &OsMsgQueue_Memory_Init[eOsMsgQueue_InitTrusted][0],
    .mq_size    = sizeof(OsMsgQueue_Memory_Init[eOsMsgQueue_InitTrusted])
  },
  {
    .name       = OS_TXT_MSGQUEUE_INIT_U,
    .attr_bits  = 0,
    .cb_mem     = &OsMsgQueueCb_Init[eOsMsgQueue_InitUntrusted],
    .cb_size    = sizeof(osRtxMessageQueue_t),
    .mq_mem     = &OsMsgQueue_Memory_Init[eOsMsgQueue_InitUntrusted][0],
    .mq_size    = sizeof(OsMsgQueue_Memory_Init[eOsMsgQueue_InitUntrusted])
  }
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Os_InitHook
//
// 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
__attribute__((weak)) void Os_InitHook(void)
{
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Os_StartupHook
//
// 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
__attribute__((weak)) void Os_StartupHook(void)
{
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Os_ErrorHook
//
// 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
__attribute__((weak)) void Os_ErrorHook(void)
{
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Os_TickIrqHook
//
// 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
__attribute__((weak)) void Os_TickIrqHook(void)
{
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Os_Get_BusFaultCnt
//
// 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
uint32 Os_Get_BusFaultCnt(void)
{
  return OsBusFaultCount;
}

// OS_Tick_AcknowledgeIRQ
//
// SysTick Hook-Function (called on IRQ level)
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OS_Tick_AcknowledgeIRQ(void)
{
  Os_TickIrqHook();

  #if(OS_TIMER_RTE_CYCLIC == 0)
  if(OsRteCyclic)
  { 
    Rte_CalcCyclicRunnables(NULL);
  }
  #endif
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// BusFault_Handler
//
// This handler function is called in case of BusFault AND MemoryFault (MPU)!
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void BusFault_Handler(void)
{
    //dtg ERRORHANDLING
    OsBusFaultCount = (OsBusFaultCount < UINT32_MAX) ? OsBusFaultCount + 1 : UINT32_MAX;
    __ASM volatile (
        "ldr  r0,=osFaultResume       \n\t" // Before exiting the handler load and
        "bx   r0                      \n\t" // jump to osFaultResume
        );
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// UsageFault_Handler
//
// This handler function is called in case of UsageFault
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void UsageFault_Handler(void)
{
  for(;;)
  {
    //dtg ERRORHANDLING
    OsUsageFaultCount++;
  }
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Os_SvcAccessReg32
//
// SVC-User function to access peripheral registers in privileged mode
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
uint32_t Os_SvcAccessReg32(volatile uint32_t *pRegister, uint32_t ClrMask, uint32_t SetMask)
{
  uint32_t tmp;

  if((ClrMask != 0) || (SetMask != 0))
  {
    tmp = *pRegister;
    tmp &= (~ClrMask);
    tmp |= SetMask;
    *pRegister = tmp;
  }

  return *pRegister;
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Os_SvcIrqSafeMemcpy
//
// SVC-User function for IRQ-Safe memcpy in privileged mode
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Os_SvcIrqSafeMemcpy(void* pDest, const void* pSrc, uint32_t ulSize)
{
  uint32_t primask = __get_PRIMASK();
  
  __set_PRIMASK(1UL);

  memcpy(pDest, pSrc, ulSize);

  if(primask == 0)
  {
    __set_PRIMASK(0UL);
  }
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// main function
//
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
__NO_RETURN void StartOS(AppModeType Mode)
{
  uint8_t   Index;

  // enable separate handlers for usage- and bus-fault
  SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk | SCB_SHCSR_BUSFAULTENA_Msk; 

  Os_MpuInit();
  Os_AipsInit();
  
  // initialize OS
  osKernelInitialize();

  NVIC_SetPriorityGrouping(OS_NVIC_PRIOGROUPING);
  
  // prepare EventFlag for Rte-Threads
  OsEvtFlagID_RteThreads = osEventFlagsNew(&OS_EvtFlag_RteThreads_attr);
  
  // prepare Mutexes for RTE Scheduling Policy
#if(RTE_SCHEDULE_POLICY == RTE_PREEMPT_NONE)
  OsMutexID_RteSchedule   = osMutexNew(&OS_Mutex_RteSchedule_attr);
#elif(RTE_SCHEDULE_POLICY == RTE_PREEMPT_PART)
  OsMutexID_RteSchedule_T = osMutexNew(&OS_Mutex_RteSchedule_T_attr);
  OsMutexID_RteSchedule_U = osMutexNew(&OS_Mutex_RteSchedule_U_attr);
  OsMutexID_RtePortSR     = osMutexNew(&OS_Mutex_RtePortSR_attr);
#elif(RTE_SCHEDULE_POLICY == RTE_PREEMPT_FULL)
  OsMutexID_RtePortSR     = osMutexNew(&OS_Mutex_RtePortSR_attr);
#endif

  // prepare MessageQueues for Init-Runnables
  for(Index=0; Index < eOsMsgQueue_InitCount; Index++)
  {
    OsMsgQueueID_Init[Index] = osMessageQueueNew(OS_MSGQUEUE_INIT_MSGCOUNT, 
                                                 OS_MSGQUEUE_INIT_MSGSIZE, 
                                                 &OS_MsgQueue_Init_attr[Index]);
  }
  
  // prepare thread_Main
  OsMainThreadID = osThreadNew(thread_Main_func, NULL, &thread_Main_attr);

  // start OS
  if(osKernelGetState() == osKernelReady) 
  {
     osKernelStart();
  }

  for(;;);

  // the program will never reach this point!
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ShutdownOS
//
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void ShutdownOS(StatusType Error)
{
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// thread_Main_func
// 
// 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
__NO_RETURN void thread_Main_func(void *argument)
{
  (void)argument;
  
  OS_EVTREC2(OS_EVTREC_thread_Main_Start, (uint32_t)osThreadGetId(), 0UL);
  
  #if(OS_RTE_MONITOR == 1)
    RteMonitorBuffer[eThread_MAIN_Zone] = (pRunnable_t)thread_Main_func;
    RteMonitorActive = (pRunnable_t)thread_Main_func;
  #endif

  Os_RtePrepare();
  
  Os_RteTriggerInitRunnables();
  
  Os_RteStart();
  
  for(;;)
  {
    uint32_t  Flags;
    
    Flags = osThreadFlagsWait(0x7FFFFFFFUL, osFlagsWaitAny, osWaitForever);
    
    if((Flags & OS_EVTFLAG_MASK_ERROR) == 0)
    {
      // do something
    }
    else
    {
      OS_EVTREC2(OS_EVTREC_OsMain_Internal_Error, __LINE__, Flags);
      //dtg ERRORHANDLING
    }
  }
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Os_RtePrepare
// 
// 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void Os_RtePrepare(void)
{
  osMessageQueueId_t  MsgQueueID_Init[eOsMsgQueue_InitCount];

  OS_EVTREC2(OS_EVTREC_Os_RtePrepare, 0UL, 0UL);
  
  MsgQueueID_Init[eOsMsgQueue_InitTrusted]    = OsMsgQueueID_Init[eOsMsgQueue_InitTrusted];
  MsgQueueID_Init[eOsMsgQueue_InitUntrusted]  = OsMsgQueueID_Init[eOsMsgQueue_InitUntrusted];
  
  // create thread(s)
  #if(RTE_THREAD_T_HH > 0)
  extern void thread_T_HH_func(void *argument);
  OsRteThreadID[eRteThread_T_HH]  = osThreadNew(thread_T_HH_func, MsgQueueID_Init[eOsMsgQueue_InitTrusted], &thread_T_HH_attr);
  MsgQueueID_Init[eOsMsgQueue_InitTrusted] = NULL;
  #endif
  
  #if(RTE_THREAD_T_HL > 0)
  extern void thread_T_HL_func(void *argument);
  OsRteThreadID[eRteThread_T_HL]  = osThreadNew(thread_T_HL_func, MsgQueueID_Init[eOsMsgQueue_InitTrusted], &thread_T_HL_attr);
  MsgQueueID_Init[eOsMsgQueue_InitTrusted] = NULL;
  #endif

  #if(RTE_THREAD_T_LH > 0)
  extern void thread_T_LH_func(void *argument);
  OsRteThreadID[eRteThread_T_LH]  = osThreadNew(thread_T_LH_func, MsgQueueID_Init[eOsMsgQueue_InitTrusted], &thread_T_LH_attr);
  MsgQueueID_Init[eOsMsgQueue_InitTrusted] = NULL;
  #endif
  
  #if(RTE_THREAD_T_LL > 0)
  extern void thread_T_LL_func(void *argument);
  OsRteThreadID[eRteThread_T_LL]  = osThreadNew(thread_T_LL_func, MsgQueueID_Init[eOsMsgQueue_InitTrusted], &thread_T_LL_attr);
  MsgQueueID_Init[eOsMsgQueue_InitTrusted] = NULL;
  #endif
  
  #if(RTE_THREAD_U_HH > 0)
  extern void thread_U_HH_func(void *argument);
  OsRteThreadID[eRteThread_U_HH]  = osThreadNew(thread_U_HH_func, MsgQueueID_Init[eOsMsgQueue_InitUntrusted], &thread_U_HH_attr);
  MsgQueueID_Init[eOsMsgQueue_InitUntrusted] = NULL;
  #endif
  
  #if(RTE_THREAD_U_HL > 0)
  extern void thread_U_HL_func(void *argument);
  OsRteThreadID[eRteThread_U_HL]  = osThreadNew(thread_U_HL_func, MsgQueueID_Init[eOsMsgQueue_InitUntrusted], &thread_U_HL_attr);
  MsgQueueID_Init[eOsMsgQueue_InitUntrusted] = NULL;
  #endif

  #if(RTE_THREAD_U_LH > 0)
  extern void thread_U_LH_func(void *argument);
  OsRteThreadID[eRteThread_U_LH]  = osThreadNew(thread_U_LH_func, MsgQueueID_Init[eOsMsgQueue_InitUntrusted], &thread_U_LH_attr);
  MsgQueueID_Init[eOsMsgQueue_InitUntrusted] = NULL;
  #endif
  
  #if(RTE_THREAD_U_LL > 0)
  extern void thread_U_LL_func(void *argument);
  OsRteThreadID[eRteThread_U_LL]  = osThreadNew(thread_U_LL_func, MsgQueueID_Init[eOsMsgQueue_InitUntrusted], &thread_U_LL_attr);
  MsgQueueID_Init[eOsMsgQueue_InitUntrusted] = NULL;
  #endif
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Os_RteTriggerInitRunnables
// 
// 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void Os_RteTriggerInitRunnables(void)
{
  osStatus_t  Status;
  
  OS_EVTREC2(OS_EVTREC_Os_RteTriggerInitRunnables, 0UL, 0UL);
  
  if((Status = osThreadSetPriority(OsMainThreadID, osPriorityBelowNormal)) != osOK)
  {
    OS_EVTREC2(OS_EVTREC_OsMain_Internal_Error, __LINE__, (uint32_t)Status);
    //dtg ERRORHANDLING
  }
  
  Rte_TriggerInitRunnables(OsMsgQueueID_Init[eOsMsgQueue_InitTrusted],
                           OsMsgQueueID_Init[eOsMsgQueue_InitUntrusted]);
    
  if((Status = osThreadSetPriority(OsMainThreadID, OS_THREAD_PRIO_MAIN)) != osOK)
  {
    OS_EVTREC2(OS_EVTREC_OsMain_Internal_Error, __LINE__, (uint32_t)Status);
    //dtg ERRORHANDLING
  }
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Os_RteStart
// 
// 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void Os_RteStart(void)
{
  uint32_t Flags;
  
  OS_EVTREC2(OS_EVTREC_Os_RteStart, 0UL, 0UL);
  
  #if(OS_TIMER_RTE_CYCLIC == 1)
  osStatus_t  Status;
  
  OsTimerID[eOsTimer_Rte] = osTimerNew(Rte_CalcCyclicRunnables, osTimerPeriodic, NULL, &timer_RTE_attr);
  
  if(OsTimerID[eOsTimer_Rte] != NULL)
  {
    if((Status = osTimerStart(OsTimerID[eOsTimer_Rte], OS_TIMER_TIMETICKS)) != osOK)
    {
      //dtg ERROR: timer start failed
    }
  }
  else
  {
    //dtg ERROR: timer object creation failed
  }
  #else
  OsRteCyclic = true; 
  #endif
  
  // enable all RTE runnables
  Flags = osEventFlagsSet(OsEvtFlagID_RteThreads, OS_EVTFLAG_RTESTART);
  
  if((Flags & OS_EVTFLAG_MASK_ERROR) != 0)
  {
    OS_EVTREC2(OS_EVTREC_OsMain_Internal_Error, __LINE__, Flags);
    //dtg ERRORHANDLING
  }
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// osRtxIdleThread
// 
// 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
__NO_RETURN void osRtxIdleThread (void *argument) 
{
  (void)argument;

  #if(OS_RTE_MONITOR == 1)
    RteMonitorBuffer[eThread_IDLE_Zone] = (pRunnable_t)osRtxIdleThread;
    RteMonitorActive = (pRunnable_t)osRtxIdleThread;
  #endif

  OS_EVTREC2(OS_EVTREC_thread_Idle_Start, (uint32_t)osThreadGetId(), 0UL);

  RTX_IdleThreadSwitch_Notification();
  
  for (;;) {
    RTX_Custom_IdleTask();
  }
}