// *****************************************************************************
// Rte.h
//
// 
// *****************************************************************************

#ifndef __RTE_H
#define __RTE_H


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// includes
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "stdint.h"
#include "stdbool.h"
#include "Os_Types.h"
#include "Os_Cfg.h"
#include "rtx_os.h"
#include <Rte_Cfg.h>
#include <UtilUtility.h>


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// preprocessor definitions
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// do NOT change the following definitions!!!
#define RTE_PREEMPT_FULL     0  // full preemptive RTE runnable scheduling
#define RTE_PREEMPT_NONE     1  // cooperative RTE runnable scheduling
#define RTE_PREEMPT_PART     2  // partly preemptive RTE runnable scheduling

#define BITSET8(x)              ((uint8_t)0x80 >> (x))
#define BITSET16(x)             ((uint16_t)0x8000 >> (x))
#define BITSET32(x)             ((uint32_t)0x80000000 >> (x))

#if( RTECYC_RunnableCount <= 8)    // BitIndex = 0..7
  #define CYCLIC_TABLE_TYPE     uint8_t
  #define CYCLIC_TABLE_ENTRY(x) ((uint32_t)RTE_CyclicTable[x] << 24)
  #define CYCLIC(x)             BITSET8(x)
#elif RTECYC_RunnableCount <= 16   // BitIndex = 0..15
  #define CYCLIC_TABLE_TYPE     uint16_t
  #define CYCLIC_TABLE_ENTRY(x) ((uint32_t)RTE_CyclicTable[x] << 16)
  #define CYCLIC(x)             BITSET16(x)
#elif RTECYC_RunnableCount <= 32   // BitIndex = 0..31
  #define CYCLIC_TABLE_TYPE     uint32_t
  #define CYCLIC_TABLE_ENTRY(x) (RTE_CyclicTable[x])
  #define CYCLIC(x)             BITSET32(x)
#else
  #error "Number of cyclic runnables is too large"
#endif

// Rte API return values
#define RTE_E_OK                (0U)
#define RTE_E_INVALID           (1U)
#define RTE_E_NEVER_RECEIVED  (133U)

//dtg
#define RUNNABLE_TRIGGER_ENTRY
#define RUNNABLE_TRIGGER_EXIT

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// type definitions
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef void (*pRunnable_t)(void);


typedef enum
{
  eRteSafety_Trusted,
  eRteSafety_Untrusted,
  eRteSafety_Unknown
}eRteSafety_t;

typedef struct
{
  pRunnable_t   pRteRunnableInit;
  eRteSafety_t  eRteSafety;
}RteRunnableInit_t;

typedef enum
{
  #if(RTE_THREAD_T_HH > 0)
  eRteThread_T_HH,
  #endif
  #if(RTE_THREAD_T_HL > 0)
  eRteThread_T_HL,
  #endif
  #if(RTE_THREAD_T_LH > 0)
  eRteThread_T_LH,
  #endif
  #if(RTE_THREAD_T_LL > 0)
  eRteThread_T_LL,
  #endif
  #if(RTE_THREAD_U_HH > 0)
  eRteThread_U_HH,
  #endif
  #if(RTE_THREAD_U_HL > 0)
  eRteThread_U_HL,
  #endif
  #if(RTE_THREAD_U_LH > 0)
  eRteThread_U_LH,
  #endif
  #if(RTE_THREAD_U_LL > 0)
  eRteThread_U_LL,
  #endif
  eRteThreadCount
}eRteThreadIndex_t;

typedef struct
{
  uint32_t  ThreadIndex;
  uint32_t  ThreadFlag;
}RteThreadCyclic_t;

typedef struct
{
  uint32_t  ThreadIndex;
  uint32_t  ThreadFlag;
}RteThreadPortSR_t;

typedef uint32 tRtePortId;
typedef tRtePortId    tRtePortIndex;


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// externals
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if(OS_RTE_MONITOR == 1)
  extern volatile pRunnable_t RteMonitorActive;
  extern volatile pRunnable_t RteMonitorBuffer[];
#endif



// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// function prototypes
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Rte_CalcCyclicRunnables(void *arg);
void Rte_TriggerInitRunnables(osMessageQueueId_t MsgQueueID_Trusted, 
                              osMessageQueueId_t MsgQueueID_Untrusted);

void Rte_PortSR_Trigger(eRteThreadIndex_t ThreadIndex, uint32_t ThreadFlag);

void Rte_PortSR_SetInitFlag_T(eRtePortSR_T_t FlagID);
bool Rte_PortSR_GetInitFlag_T(eRtePortSR_T_t FlagID);

void Rte_PortSR_SetInitFlag_U(eRtePortSR_U_t FlagID);
bool Rte_PortSR_GetInitFlag_U(eRtePortSR_U_t FlagID);

void Rte_PortSR_Copy(void* pDest, const void* pSrc, uint32_t count);
void Rte_PortSR_CopyISR(void* pDest, const void* pSrc, uint32_t count);
void Rte_PortSR_CopyThread(void* pDest, const void* pSrc, uint32_t size);


#endif // __RTE_H