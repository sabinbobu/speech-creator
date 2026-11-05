// *****************************************************************************
// Os_Main.h
// *****************************************************************************

#ifndef __OS_MAIN_H
#define __OS_MAIN_H


// -----------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------
#include "Os_Cfg.h"
#include "Os_Mpu.h"
#include "rtx_os.h"
#include "Rte_Chk.h"



// -----------------------------------------------------------------------------
// preprocessor definitions
// -----------------------------------------------------------------------------
#define OS_EVTFLAG_MASK_ERROR   0x80000000UL
#define OS_EVTFLAG_RTESTART     0x00000001UL


// -----------------------------------------------------------------------------
// externals
// -----------------------------------------------------------------------------
extern osThreadId_t       OsMainThreadID;
extern osThreadId_t       OsRteThreadID[eRteThreadCount];
extern osEventFlagsId_t   OsEvtFlagID_RteThreads;
#if(RTE_SCHEDULE_POLICY == RTE_PREEMPT_NONE)
extern osMutexId_t        OsMutexID_RteSchedule;
#elif(RTE_SCHEDULE_POLICY == RTE_PREEMPT_PART)
extern osMutexId_t        OsMutexID_RteSchedule_T;
extern osMutexId_t        OsMutexID_RteSchedule_U;
extern osMutexId_t        OsMutexID_RtePortSR;
#elif(RTE_SCHEDULE_POLICY == RTE_PREEMPT_FULL)
extern osMutexId_t        OsMutexID_RtePortSR;
#endif


// -----------------------------------------------------------------------------
// function prototypes
// -----------------------------------------------------------------------------
uint32_t  Os_SvcAccessReg32(volatile uint32_t *pRegister, uint32_t ClrMask, uint32_t SetMask);
void      Os_SvcIrqSafeMemcpy(void* pDest, const void* pSrc, uint32_t ulSize);
__NO_RETURN void StartOS(AppModeType Mode);


#endif // __OS_MAIN_H

