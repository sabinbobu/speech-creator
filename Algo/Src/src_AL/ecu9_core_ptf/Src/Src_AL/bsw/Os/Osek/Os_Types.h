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
* \file     Os_Types.h
*
* \brief    OSEK type definitions
*
* \descr    OSEK 2.2.3 standard type definitions and error codes.
*           This file defines the basic types required by the OSEK standard.
*           Implementation-specific types are in Os_Wrapper.h
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

#ifndef OS_TYPES_H
#define OS_TYPES_H

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "Std_Types.h"

/*______ G L O B A L - M A C R O _____________________________________________*/

/* Error codes (OSEK 2.2.3 standard) */
#ifndef E_OK
#define E_OK                                    ((StatusType)0x00U)  /* No error occurred */
#endif
#define E_OS_ACCESS                             ((StatusType)0x01U)  /* Access denied - insufficient priority */
#define E_OS_CALLEVEL                           ((StatusType)0x02U)  /* Call level error - invalid context */
#define E_OS_ID                                 ((StatusType)0x03U)  /* Invalid task/alarm/resource/counter ID */
#define E_OS_LIMIT                              ((StatusType)0x04U)  /* Task activation limit exceeded */
#define E_OS_NOFUNC                             ((StatusType)0x05U)  /* OS object not in use */
#define E_OS_RESOURCE                           ((StatusType)0x06U)  /* Resource occupied during scheduling */
#define E_OS_STATE                              ((StatusType)0x07U)  /* Invalid state for operation */
#define E_OS_VALUE                              ((StatusType)0x08U)  /* Parameter value out of range */

#define OSDEFAULTAPPMODE                        ((AppModeType)0x01U) /* Default application mode */

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/* Status information type */
typedef uint8 StatusType;

/* Task identifier type */
typedef uint8 TaskType;

/* Task identifier reference type */
typedef P2VAR(TaskType, TYPEDEF, AUTOMATIC) TaskRefType;

/* Task scheduling state type */
typedef enum
{
  RUNNING,              /* Task is currently executing */
  READY,                /* Task is ready to run but waiting for CPU */
  WAITING,              /* Task waits for at least one event */
  SUSPENDED,            /* Task is inactive and can be activated */
  INVALID_TASK = 0xFFu  /* Task not initialized or invalid */
} TaskStateType;

/* Task scheduling state reference type */
typedef P2VAR(TaskStateType, TYPEDEF, AUTOMATIC) TaskStateRefType;

/* Resource identifier type */
typedef uint8 ResourceType;

/* Event mask type (set of events) */
typedef uint32 EventMaskType;

/* Event mask reference type */
typedef P2VAR(EventMaskType, TYPEDEF, AUTOMATIC) EventMaskRefType;

/* Timer tick type (counter value) */
typedef uint32 TickType;

/* Timer tick reference type */
typedef P2VAR(TickType, TYPEDEF, AUTOMATIC) TickRefType;

/* Alarm base information structure */
typedef struct
{
  TickType maxallowedvalue;  /* Maximum allowed counter value (in ticks) */
  TickType ticksperbase;     /* Number of ticks per counter unit */
  TickType mincycle;         /* Minimum allowed cycle time for cyclic alarms (ticks) */
} AlarmBaseType;

/* Alarm base information reference type */
typedef P2VAR(AlarmBaseType, TYPEDEF, AUTOMATIC) AlarmBaseRefType;

/* Alarm identifier type */
typedef uint8 AlarmType;

/* Application execution mode identifier */
typedef uint8 AppModeType;

/* OS service identifier type (for ErrorHook) - OSEK 2.2.3 chapter 12 order */
typedef enum
{
  OSServiceId_ActivateTask,
  OSServiceId_TerminateTask,
  OSServiceId_ChainTask,
  OSServiceId_Schedule,
  OSServiceId_GetTaskID,
  OSServiceId_GetTaskState,
  OSServiceId_DisableAllInterrupts,
  OSServiceId_EnableAllInterrupts,
  OSServiceId_SuspendAllInterrupts,
  OSServiceId_ResumeAllInterrupts,
  OSServiceId_SuspendOSInterrupts,
  OSServiceId_ResumeOSInterrupts,
  OSServiceId_GetResource,
  OSServiceId_ReleaseResource,
  OSServiceId_SetEvent,
  OSServiceId_ClearEvent,
  OSServiceId_GetEvent,
  OSServiceId_WaitEvent,
  OSServiceId_GetAlarmBase,
  OSServiceId_GetAlarm,
  OSServiceId_SetRelAlarm,
  OSServiceId_SetAbsAlarm,
  OSServiceId_CancelAlarm,
  OSServiceId_GetActiveApplicationMode,
  OSServiceId_StartOS,
  OSServiceId_ShutdownOS
} OSServiceIdType;

typedef uint8 CounterType;

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/*______ L O C A L - F U N C T I O N S _______________________________________*/

#endif /* OS_TYPES_H */
/*______ E N D _______________________________________________________________*/
