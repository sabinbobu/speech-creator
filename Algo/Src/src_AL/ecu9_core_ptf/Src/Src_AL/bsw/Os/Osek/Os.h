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
* \file     Os.h
*
* \brief    BSW Os wrapper
*
* \descr    OS module header file
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

#ifndef OS_H
#define OS_H

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "Os_Types.h"
#include "Os_Cfg.h"

/*______ G L O B A L - M A C R O _____________________________________________*/
/* OSEK Os_UserInterface */
#define TASK(TaskName)                             void Os_Task_##TaskName(void)

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/* OSEK task management */
extern FUNC(StatusType, OS_CODE) ActivateTask(TaskType TaskID);
extern FUNC(StatusType, OS_CODE) TerminateTask(void);
extern FUNC(StatusType, OS_CODE) ChainTask(TaskType TaskID);
extern FUNC(StatusType, OS_CODE) Schedule(void);
extern FUNC(StatusType, OS_CODE) GetTaskID(TaskRefType TaskID);
extern FUNC(StatusType, OS_CODE) GetTaskState(TaskType TaskID, TaskStateRefType State);

/* OSEK interrupt handling */
extern FUNC(void, OS_CODE) DisableAllInterrupts(void);
extern FUNC(void, OS_CODE) EnableAllInterrupts(void);
extern FUNC(void, OS_CODE) SuspendAllInterrupts(void);
extern FUNC(void, OS_CODE) ResumeAllInterrupts(void);
extern FUNC(void, OS_CODE) SuspendOSInterrupts(void);
extern FUNC(void, OS_CODE) ResumeOSInterrupts(void);

/* OSEK resource management */
extern FUNC(StatusType, OS_CODE) GetResource(ResourceType ResourceID);
extern FUNC(StatusType, OS_CODE) ReleaseResource(ResourceType ResourceID);

/* OSEK event control */
extern FUNC(StatusType, OS_CODE) SetEvent(TaskType TaskID, EventMaskType Mask);
extern FUNC(StatusType, OS_CODE) ClearEvent(EventMaskType Mask);
extern FUNC(StatusType, OS_CODE) GetEvent(TaskType TaskID, EventMaskRefType MaskPtr);
extern FUNC(StatusType, OS_CODE) WaitEvent(EventMaskType Mask);

/* OSEK alarms */
extern FUNC(StatusType, OS_CODE) GetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info);
extern FUNC(StatusType, OS_CODE) GetAlarm(AlarmType AlarmID, TickRefType Ticks);
extern FUNC(StatusType, OS_CODE) SetRelAlarm(AlarmType AlarmID, TickType Increment, TickType Cycle);
extern FUNC(StatusType, OS_CODE) SetAbsAlarm(AlarmType AlarmID, TickType Start, TickType Cycle);
extern FUNC(StatusType, OS_CODE) CancelAlarm(AlarmType AlarmID);

/* OSEK operating system execution control */
extern FUNC(AppModeType, OS_CODE) GetActiveApplicationMode(void);

/* StartOS public API */
extern FUNC(void, OS_CODE) StartOS(AppModeType Mode);

/* ShutdownOS public API */
extern FUNC(void, OS_CODE) ShutdownOS (StatusType Error);

/* OSEK hooks */
extern FUNC(void, OS_CODE) StartupHook(void);
extern FUNC(void, OS_CODE) ShutdownHook(StatusType Fatalerror);
extern FUNC(void, OS_CODE) ErrorHook(StatusType Error);
extern FUNC(void, OS_CODE) PreTaskHook(void);
extern FUNC(void, OS_CODE) PostTaskHook(void);

/* AutosarOS counter functions */
extern FUNC(StatusType, OS_CODE) GetCounterValue(CounterType CounterID, TickRefType Value);
extern FUNC(StatusType, OS_CODE) GetElapsedValue(CounterType CounterID, TickRefType Value, TickRefType ElapsedValue);

#endif
/*______ E N D _______________________________________________________________*/

