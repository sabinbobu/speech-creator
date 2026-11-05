// *****************************************************************************
// Rte.c
//
// 
// *****************************************************************************


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// includes
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "cmsis_armclang.h"   // needed for __LDREXW, __STREXW
#include "arm_acle.h"         // needed for __clz() intrinsic
#include "cmsis_os2.h"
#include "Os_Main.h"
#include "Os_SvcUser.h"
#include "Rte_Chk.h"
#include "Rte_EvtRec.h"


#if __ARM_FEATURE_CLZ != 1
#error "This implementation uses ARM instruction "clz"
#endif


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// preprocessor definitions
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define THREADFLAGMASK(x)       ((uint32_t)0x40000000UL >> (x))
#define THREADFLAGANY           0x7FFFFFFFUL

#define BIT32_INDEX(bitnr)      (bitnr / 32)
#define BIT32_MASK(bitnr)       (0x00000001UL << (bitnr % 32))

#define RTE_ERRORHANDLER(x)   //dtg ERRORHANDLING

#define CONCAT3int(x1, x2, x3) x1 ## x2 ## x3
#define CONCAT3(x1, x2, x3) CONCAT3int(x1, x2, x3)

#define RTE_RUNNABLE_SYNC_TIMEOUT  osWaitForever
#define RTE_PORTSR_SYNC_TIMEOUT    osWaitForever

#if(RTE_SCHEDULE_POLICY == RTE_PREEMPT_NONE)
#define RTE_RUNNABLE_SYNC_T_ENTRY  osMutexAcquire(OsMutexID_RteSchedule, RTE_RUNNABLE_SYNC_TIMEOUT);
#define RTE_RUNNABLE_SYNC_T_EXIT   osMutexRelease(OsMutexID_RteSchedule);
#define RTE_RUNNABLE_SYNC_U_ENTRY  osMutexAcquire(OsMutexID_RteSchedule, RTE_RUNNABLE_SYNC_TIMEOUT);
#define RTE_RUNNABLE_SYNC_U_EXIT   osMutexRelease(OsMutexID_RteSchedule);
#define RTE_PORTSR_SYNC_ENTRY
#define RTE_PORTSR_SYNC_EXIT
#elif(RTE_SCHEDULE_POLICY == RTE_PREEMPT_PART)
#define RTE_RUNNABLE_SYNC_T_ENTRY  osMutexAcquire(OsMutexID_RteSchedule_T, RTE_RUNNABLE_SYNC_TIMEOUT);
#define RTE_RUNNABLE_SYNC_T_EXIT   osMutexRelease(OsMutexID_RteSchedule_T);
#define RTE_RUNNABLE_SYNC_U_ENTRY  osMutexAcquire(OsMutexID_RteSchedule_U, RTE_RUNNABLE_SYNC_TIMEOUT);
#define RTE_RUNNABLE_SYNC_U_EXIT   osMutexRelease(OsMutexID_RteSchedule_U);
#define RTE_PORTSR_SYNC_ENTRY      osMutexAcquire(OsMutexID_RtePortSR, RTE_PORTSR_SYNC_TIMEOUT);
#define RTE_PORTSR_SYNC_EXIT       osMutexRelease(OsMutexID_RtePortSR);
#elif(RTE_SCHEDULE_POLICY == RTE_PREEMPT_FULL)
#define RTE_RUNNABLE_SYNC_T_ENTRY
#define RTE_RUNNABLE_SYNC_T_EXIT
#define RTE_RUNNABLE_SYNC_U_ENTRY
#define RTE_RUNNABLE_SYNC_U_EXIT
#define RTE_PORTSR_SYNC_ENTRY      osMutexAcquire(OsMutexID_RtePortSR, RTE_PORTSR_SYNC_TIMEOUT);
#define RTE_PORTSR_SYNC_EXIT       osMutexRelease(OsMutexID_RtePortSR);
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// external declarations
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
extern const RteRunnableInit_t  RTE_RunnableInit[]; 
extern const uint8_t            RTE_RunnableInitCount;
extern const RteThreadCyclic_t  RTE_ThreadCyclic[];
extern const CYCLIC_TABLE_TYPE  RTE_CyclicTable[];
extern const uint8_t            RTE_CyclicTableCount;
  
extern const pRunnable_t RTE_Runnable_T_HH_func[eRteThreadFlag_T_HH_Count];
extern const pRunnable_t RTE_Runnable_T_HL_func[eRteThreadFlag_T_HL_Count];
extern const pRunnable_t RTE_Runnable_T_LH_func[eRteThreadFlag_T_LH_Count];
extern const pRunnable_t RTE_Runnable_T_LL_func[eRteThreadFlag_T_LL_Count];
extern const pRunnable_t RTE_Runnable_U_HH_func[eRteThreadFlag_U_HH_Count];
extern const pRunnable_t RTE_Runnable_U_HL_func[eRteThreadFlag_U_HL_Count];
extern const pRunnable_t RTE_Runnable_U_LH_func[eRteThreadFlag_U_LH_Count];
extern const pRunnable_t RTE_Runnable_U_LL_func[eRteThreadFlag_U_LL_Count];


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// function prototypes
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void Rte_Prestart(osMessageQueueId_t MsgQueueID);
  
// -----------------------------------------------------------------------------
// constants
// -----------------------------------------------------------------------------
const RteRunnableInit_t RTE_RunnableInitEnd[1] = 
{
  { NULL, eRteSafety_Unknown },
};

// -----------------------------------------------------------------------------
// vars
// -----------------------------------------------------------------------------
__attribute__((section(".bss.RtePortSR_T")))
uint32_t RtePortSRInitFlags_T[((eRtePortSR_T_Count/32)+1)];

__attribute__((section(".bss.RtePortSR_U")))
uint32_t RtePortSRInitFlags_U[((eRtePortSR_U_Count/32)+1)];

#if(OS_RTE_MONITOR == 1)
__attribute__((section(".bss.RteMonitor")))
  volatile pRunnable_t RteMonitorActive;
__attribute__((section(".bss.RteMonitor")))
  volatile pRunnable_t RteMonitorBuffer[eThread_BufferCount];
#endif


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// atomic_setmask32
// 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void atomic_setmask32(uint32_t *mem, uint32_t msk) __attribute__((always_inline));
static void atomic_setmask32(uint32_t *mem, uint32_t msk)
{
  register uint32_t val, res;
 
  __ASM volatile (
  ".syntax unified\n"
  "1:\n\t"
    "ldrex %[val],[%[mem]]\n\t"
    "orrs  %[val],%[val],%[msk]\n\t"
    "strex %[res],%[val],[%[mem]]\n\t"
    "cbz   %[res],2f\n\t"
    "b     1b\n"
  "2:"
  : [val] "=&l" (val),
    [res] "=&l" (res)
  : [mem] "r"   (mem),
    [msk] "r"   (msk)
  : "cc", "memory"
  );
}

static bool IsIrqMode(void) __attribute__((always_inline));
static bool IsIrqMode(void)
{
  return (__get_IPSR() != 0U);
}

/// Check if IRQ is Masked
/// \return     true=masked, false=not masked
static bool IsIrqMasked(void)  __attribute__((always_inline));
static bool IsIrqMasked(void)
{
#if   ((defined(__ARM_ARCH_7M__)      && (__ARM_ARCH_7M__      != 0)) || \
       (defined(__ARM_ARCH_7EM__)     && (__ARM_ARCH_7EM__     != 0)) || \
       (defined(__ARM_ARCH_8M_MAIN__) && (__ARM_ARCH_8M_MAIN__ != 0)))
  return ((__get_PRIMASK() != 0U) || (__get_BASEPRI() != 0U));
#else
  return  (__get_PRIMASK() != 0U);
#endif
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Rte_PortSR_SetInitFlag_T
// 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Rte_PortSR_SetInitFlag_T(eRtePortSR_T_t FlagID)
{
  volatile uint32_t* flag = &RtePortSRInitFlags_T[BIT32_INDEX(FlagID)];
  uint32_t  mask = BIT32_MASK(FlagID);
  uint32_t  newval;
  
  if((*flag & mask) == 0)
  {
    atomic_setmask32(&RtePortSRInitFlags_T[BIT32_INDEX(FlagID)], BIT32_MASK(FlagID));
  }
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Rte_PortSR_GetInitFlag_T
// 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool Rte_PortSR_GetInitFlag_T(eRtePortSR_T_t FlagID)
{
  return ((RtePortSRInitFlags_T[BIT32_INDEX(FlagID)] & BIT32_MASK(FlagID)) != 0);
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Rte_PortSR_SetInitFlag_U
// 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Rte_PortSR_SetInitFlag_U(eRtePortSR_U_t FlagID)
{
  volatile uint32_t* flag = &RtePortSRInitFlags_U[BIT32_INDEX(FlagID)];
  uint32_t  mask = BIT32_MASK(FlagID);
  uint32_t  newval;
  
  if((*flag & mask) == 0)
  {
    atomic_setmask32(&RtePortSRInitFlags_U[BIT32_INDEX(FlagID)], BIT32_MASK(FlagID));
  }
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Rte_PortSR_GetInitFlag_U
// 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool Rte_PortSR_GetInitFlag_U(eRtePortSR_U_t FlagID)
{
  return ((RtePortSRInitFlags_U[BIT32_INDEX(FlagID)] & BIT32_MASK(FlagID)) != 0);
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Rte_PortSR_CopyThread
// 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Rte_PortSR_CopyThread(void* pDest, const void* pSrc, uint32_t size)
{
  RTE_PORTSR_SYNC_ENTRY
  memcpy(pDest, pSrc, size);
  RTE_PORTSR_SYNC_EXIT
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Rte_PortSR_CopyISR
// 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Rte_PortSR_Copy(void* pDest, const void* pSrc, uint32_t ulSize)
{
  // check if already in ISR or interrupts disabled/masked
  if(IsIrqMode() || IsIrqMasked()) 
  {
    memcpy(pDest, pSrc, ulSize);
  }
  else
  {
    SvcIrqSafeMemcpy(pDest, pSrc, ulSize);
  }
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Rte_EventTrigger
// 
// 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Rte_PortSR_Trigger(eRteThreadIndex_t ThreadIndex, uint32_t ThreadFlag)
{
  if(ThreadIndex < eRteThreadCount)
  {
    int32_t result = osThreadFlagsSet(OsRteThreadID[ThreadIndex], THREADFLAGMASK(ThreadFlag));

    if((result & OS_EVTFLAG_MASK_ERROR) == 0)
    {
      //dtg RTE_EVTREC2(RTE_EVTREC_Cyclic_ThreadFlagsSet, (uint32_t)ThreadID, THREADFLAGMASK(ThreadFlag));
    }
    else
    {
      // ERROR: osThreadFlagsSet is returning ErrorCode
      RTE_ERRORHANDLER(__LINE__);
    }
  }
  else
  {
    // ERROR: ThreadIndex out of range (0..eRteThreadCount)
    RTE_ERRORHANDLER(__LINE__);
  }
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Rte_CalcCyclicRunnables
// param1 = unspecified parameter
// return = none
// This function has to be called periodically with period = 1msec
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Rte_CalcCyclicRunnables(void *arg)
{
  static uint8_t  RteCyclicTableIndex = 0;
  uint32_t        RteCyclicTableFlag; 
  uint8_t         CyclicIndex;
  
  (void)arg;
  
  // RteCyclicTableIndex wrap-around
  if(RteCyclicTableIndex >= RTE_CyclicTableCount)
  {
    RteCyclicTableIndex = 0;
  }
  
  RteCyclicTableFlag = CYCLIC_TABLE_ENTRY(RteCyclicTableIndex++);
  
  // calculate CyclicIndex out of RteCyclicTableFlag 
  // clz() = CountLeadingZeroes (=32 if no more bit is set)
  while((CyclicIndex = __clz(RteCyclicTableFlag)) < 32)
  {
    if(CyclicIndex < RTECYC_RunnableCount)
    {
      // calculate ThreadIndex out of CyclicIndex
      uint32_t ThreadIndex = RTE_ThreadCyclic[CyclicIndex].ThreadIndex;
      
      if(ThreadIndex < eRteThreadCount)
      {
        // calculate ThreadID out of ThreadIndex
        osThreadId_t ThreadID = OsRteThreadID[ThreadIndex];   //dtg
        
        if(ThreadID != NULL)
        {
          uint32_t ThreadFlag = RTE_ThreadCyclic[CyclicIndex].ThreadFlag;
          
          if(ThreadFlag < 31)
          {
            int32_t result = osThreadFlagsSet(ThreadID, THREADFLAGMASK(ThreadFlag));
            
            if((result & OS_EVTFLAG_MASK_ERROR) == 0)
            {
              //dtg RTE_EVTREC2(RTE_EVTREC_Cyclic_ThreadFlagsSet, (uint32_t)ThreadID, THREADFLAGMASK(ThreadFlag));
            }
            else
            {
              // ERROR: osThreadFlagsSet is returning ErrorCode
              RTE_EVTREC2(RTE_EVTREC_Cyclic_ThreadFlagsSet_Error, (uint32_t)ThreadID, THREADFLAGMASK(ThreadFlag));
              RTE_ERRORHANDLER(__LINE__);
            }
          }
          else
          {
            // ERROR: ThreadFlag out of possible range (0..30)
            RTE_EVTREC2(RTE_EVTREC_Cyclic_ThreadFlagRange_Error, (uint32_t)ThreadID, (uint32_t)ThreadFlag);
            RTE_ERRORHANDLER(__LINE__);
          }
        }
        else
        {
          // ERROR: ThreadID (stored at osThreadNew()) is invalid
          RTE_EVTREC2(RTE_EVTREC_Cyclic_ThreadID_Error, (uint32_t)ThreadIndex, (uint32_t)ThreadID);
          RTE_ERRORHANDLER(__LINE__);
        }
      }
      else
      {
        // ERROR: ThreadIndex out of range (0..eRteThreadCount)
        RTE_EVTREC2(RTE_EVTREC_Cyclic_ThreadIndex_Error, (uint32_t)CyclicIndex, (uint32_t)ThreadIndex);
        RTE_ERRORHANDLER(__LINE__);
      }
      
      // clear flag in RteCyclicTableFlag just handled
      RteCyclicTableFlag &= (~BITSET32(CyclicIndex));
    }
    else
    {
      // ERROR: CyclicIndex out of range (0..RTE_CYCLIC_RUNNABLE_COUNT)
      RTE_EVTREC2(RTE_EVTREC_Cyclic_CyclicIndex_Error, (uint32_t)RteCyclicTableFlag, (uint32_t)CyclicIndex);
      RTE_ERRORHANDLER(__LINE__);
    }
  }
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Rte_TriggerInitRunnables
// 
// 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Rte_TriggerInitRunnables(osMessageQueueId_t MsgQueueID_Trusted, 
                              osMessageQueueId_t MsgQueueID_Untrusted)
{
  osStatus_t  Status;
  uint32_t    Index;
  
  for(Index=0; Index < RTE_RunnableInitCount; Index++)
  {
    switch(RTE_RunnableInit[Index].eRteSafety)
    {
      case eRteSafety_Trusted:
        Status = osMessageQueuePut(MsgQueueID_Trusted, 
                                   &RTE_RunnableInit[Index].pRteRunnableInit, 
                                   0, 
                                   osWaitForever);
        if(Status != osOK)
        {
          RTE_EVTREC2(RTE_EVTREC_Thread_Internal_Error, __LINE__, 0UL);
          //dtg ERRORHANDLING
        }
        break;
      
      case eRteSafety_Untrusted:
        Status = osMessageQueuePut(MsgQueueID_Untrusted, 
                                   &RTE_RunnableInit[Index].pRteRunnableInit, 
                                   0, 
                                   osWaitForever);
        if(Status != osOK)
        {
          RTE_EVTREC2(RTE_EVTREC_Thread_Internal_Error, __LINE__, 0UL);
          //dtg ERRORHANDLING
        }
        break;
      
      default:
        RTE_EVTREC2(RTE_EVTREC_Thread_Internal_Error, __LINE__, 0UL);
        //dtg ERRORHANDLING
        break;
    }
  }
  
  // put final message into msgqueue
  Status = osMessageQueuePut(MsgQueueID_Trusted, &RTE_RunnableInitEnd[0].pRteRunnableInit, 0, osWaitForever);
  if(Status != osOK)
  {
    RTE_EVTREC2(RTE_EVTREC_Thread_Internal_Error, __LINE__, 0UL);
    //dtg ERRORHANDLING
  }

  // put final message into msgqueue
  Status = osMessageQueuePut(MsgQueueID_Untrusted, &RTE_RunnableInitEnd[0].pRteRunnableInit, 0, osWaitForever);
  if(Status != osOK)
  {
    RTE_EVTREC2(RTE_EVTREC_Thread_Internal_Error, __LINE__, 0UL);
    //dtg ERRORHANDLING
  }  
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Rte_Prestart
// 
// 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void Rte_Prestart(osMessageQueueId_t MsgQueueID)
{
  uint32_t    Flags;
  pRunnable_t RunnableInit;
  osStatus_t  Status;
  
  // check if this thread is handling Init-Runnables
  if(MsgQueueID != NULL)
  {
    do
    {
      // wait for Init-Runnable pointer, given in message-queue
      if((Status = osMessageQueueGet(MsgQueueID, &RunnableInit, NULL, osWaitForever)) == osOK)   //dtg
      {
        // check if RunnableInitEnd was received
        if(RunnableInit != NULL)
        {
          RTE_EVTREC2(RTE_EVTREC_Thread_RunnableInitCall, (uint32_t)osThreadGetId(), (uint32_t)RunnableInit);
          
          #if(OS_RTE_MONITOR == 1)
            RteMonitorActive = RunnableInit;
          #endif
          
          // call given Init-Runnable
          RunnableInit();
          
          #if(OS_RTE_MONITOR == 1)
            RteMonitorActive = (pRunnable_t)0;
          #endif
        }
      }
      else
      {
        //dtg ERRORHANDLING
        RTE_EVTREC2(RTE_EVTREC_Thread_Internal_Error, __LINE__, 0UL);
        RunnableInit = NULL;
      }
    }while(RunnableInit != NULL);
  }
  
  // wait for RteStart
  Flags = osEventFlagsWait(OsEvtFlagID_RteThreads, OS_EVTFLAG_RTESTART, (osFlagsWaitAll | osFlagsNoClear), osWaitForever);
 
  if((Flags & OS_EVTFLAG_MASK_ERROR) == 0)
  {
    if((Flags & OS_EVTFLAG_RTESTART) != 0)
    {
    }
    else
    {
      RTE_EVTREC2(RTE_EVTREC_Thread_Internal_Error, __LINE__, 0UL);
      //dtg ERRORHANDLING
    }
  }
  else
  {
    RTE_EVTREC2(RTE_EVTREC_Thread_Internal_Error, __LINE__, 0UL);
    //dtg ERRORHANDLING
  }
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// thread_X_YZ_func implementations
// 
// 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if(RTE_THREAD_T_HH > 0)
  #define THREAD_NAME   T_HH
  #include "Rte_Mac.h"
#endif

#if(RTE_THREAD_T_HL > 0)
  #define THREAD_NAME   T_HL
  #include "Rte_Mac.h"
#endif

#if(RTE_THREAD_T_LH > 0)
  #define THREAD_NAME   T_LH
  #include "Rte_Mac.h"
#endif

#if(RTE_THREAD_T_LL > 0)
  #define THREAD_NAME   T_LL
  #include "Rte_Mac.h"
#endif

#if(RTE_THREAD_U_HH > 0)
  #define THREAD_NAME   U_HH
  #include "Rte_Mac.h"
#endif

#if(RTE_THREAD_U_HL > 0)
  #define THREAD_NAME   U_HL
  #include "Rte_Mac.h"
#endif

#if(RTE_THREAD_U_LH > 0)
  #define THREAD_NAME   U_LH
  #include "Rte_Mac.h"
#endif

#if(RTE_THREAD_U_LL > 0)
  #define THREAD_NAME   U_LL
  #include "Rte_Mac.h"
#endif



/***
#if(RTE_THREAD_T_HH > 0)
__NO_RETURN void thread_T_HH_func(void *argument)
{
  uint32_t Flags, Index;

  RTE_EVTREC2(RTE_EVTREC_thread_T_HH_Start, (uint32_t)osThreadGetId(), (uint32_t)argument);
  
  Rte_Prestart((osMessageQueueId_t)argument);
  
  for(;;)
  {
    Flags = osThreadFlagsWait(THREADFLAGANY, osFlagsWaitAny, osWaitForever);
    
    if((Flags & OS_EVTFLAG_MASK_ERROR) == 0)
    {
      // Index = 0..30 (or 31 if all flags are cleared)
      while((Index = (__clz(Flags)-1)) < 31)
      {
        if(Index < eRteThreadFlag_T_HH_Count)
        {
          RTE_EVTREC2(RTE_EVTREC_Thread_T_HH_Runnable, (uint32_t)Index, (uint32_t)RTE_Runnable_T_HH_func[(Index)]);
          RTE_Runnable_T_HH_func[(Index)]();
        }
        else
        {
          RTE_EVTREC2(RTE_EVTREC_Thread_T_HH_Index_Error, (uint32_t)Flags, (uint32_t)Index);
          RTE_ERRORHANDLER(__LINE__);
        }
        
        Flags &= (~THREADFLAGMASK(Index));
      }
    }
    else
    {
      RTE_EVTREC2(RTE_EVTREC_Thread_Internal_Error, __LINE__, 0UL);
      RTE_ERRORHANDLER(__LINE__);
    }
  }
}
#endif
***/


