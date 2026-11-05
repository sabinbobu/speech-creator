/******************************************************************************/
/*
| (C) Marelli Automotive Lighting - ALIT-TO                                    |
|     Strada del Drosso 29, 10135 Torino (IT)                                  |
|                                                                              |
| Marelli Automotive Lighting owns all the rights to this work.                |
| This work shall not be copied, reproduced, used, modified, transferred       |
| or its information shall not be disclosed without the prior written          |
| authorization of Marelli Automotive Lighting.                                |
*/
/******************************************************************************/
/*!
* \file     Os_Wrapper.h
*
* \brief    BSW Os wrapper template
*
* \descr    Template header containing a complete list of OSEK-like wrapper
*            APIs grouped by operation (OSEK 2.2.3 chapter 12 order).
*
*            Summary (OSEK chapter 12 order):
*            Task Management:
*              ActivateTask [FuSaRTS: osThreadResume, gap: OSEK status semantics need translation]
*              TerminateTask [FuSaRTS: osThreadSuspend(osThreadGetId()), gap: running-context semantics need translation]
*              ChainTask [FuSaRTS: osThreadSuspend + osThreadResume(next), gap: atomic chain behavior needs translation]
*              Schedule [FuSaRTS: osThreadYield]
*              GetTaskID [FuSaRTS: osThreadGetId]
*              GetTaskState [FuSaRTS: osThreadGetState, gap: state model translation is required]
*            Interrupt Handling:
*              DisableAllInterrupts [FuSaRTS: __disable_irq()]
*              EnableAllInterrupts [FuSaRTS: __enable_irq()]
*              SuspendAllInterrupts [FuSaRTS: __disable_irq() + nesting counter, gap: nesting state must be maintained]
*              ResumeAllInterrupts [FuSaRTS: nesting counter + __enable_irq(), gap: nesting state must be maintained]
*              SuspendOSInterrupts [FuSaRTS: __set_BASEPRI(), gap: interrupt threshold handling must be defined]
*              ResumeOSInterrupts [FuSaRTS: __set_BASEPRI(0), gap: interrupt threshold handling must be defined]
*            Resource Management:
*              GetResource [FuSaRTS: osMutexAcquire, gap: priority ceiling / ownership semantics must be preserved]
*              ReleaseResource [FuSaRTS: osMutexRelease, gap: ownership semantics must be preserved]
*            Event Control:
*              SetEvent [FuSaRTS: osThreadFlagsSet, gap: task-event semantics need translation]
*              ClearEvent [FuSaRTS: osThreadFlagsClear, gap: calling-task semantics need translation]
*              GetEvent [FuSaRTS: osThreadFlagsGet, gap: task-event shadow state may be required]
*              WaitEvent [FuSaRTS: osThreadFlagsWait, gap: OSEK wait semantics and clear behavior need translation]
*            Alarms:
*              GetAlarmBase [FuSaRTS: static alarm configuration tables, gap: counter/alarm metadata must be provided]
*              GetAlarm [FuSaRTS: osTimerIsRunning + kernel tick accounting, gap: remaining ticks are not returned directly]
*              SetRelAlarm [FuSaRTS: osTimerStart, gap: first-shot and cycle handling must be emulated]
*              SetAbsAlarm [FuSaRTS: osTimerStart + osKernelGetTickCount, gap: absolute-to-relative conversion must be implemented]
*              CancelAlarm [FuSaRTS: osTimerStop]
*            Operating System Execution Control:
*              GetActiveApplicationMode [FuSaRTS: module-local application mode state, gap: current mode storage must be implemented]
*              StartOS [FuSaRTS: osKernelInitialize + osKernelStart, gap: init sequencing and error reporting must be aligned]
*              ShutdownOS [FuSaRTS: safe-state shutdown path, gap: shutdown behavior after hook return is implementation specific]
*            Hooks:
*              StartupHook [FuSaRTS: weak hook entry point]
*              ShutdownHook [FuSaRTS: weak hook entry point]
*              ErrorHook [FuSaRTS: weak hook entry point]
*              PreTaskHook [FuSaRTS: weak hook entry point]
*              PostTaskHook [FuSaRTS: weak hook entry point]
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

#ifndef OS_WRAPPER_H
#define OS_WRAPPER_H

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "Os_Wrapper_Cfg.h"
/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/
#define OS_START_SEC_CODE
#include "Os_MemMap.h"

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/*______ L O C A L - F U N C T I O N S _______________________________________*/

#endif
/*______ E N D _______________________________________________________________*/