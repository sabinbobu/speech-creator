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
* \file     Os_Wrapper.c
*
* \brief    BSW Os wrapper template
*
* \descr    Template implementation collecting the main OSEK-like wrapper APIs
*            by operation (OSEK 2.2.3 chapter 12 order).
*
*            API summary (OSEK chapter 12 order):
*            Task Management:
*              ActivateTask                    FuSaRTS: osThreadResume
*                                              gap: OSEK status semantics need translation
*              TerminateTask                   FuSaRTS: osThreadSuspend(osThreadGetId())
*                                              gap: running-context semantics need translation
*              ChainTask                       FuSaRTS: osThreadSuspend + osThreadResume(next)
*                                              gap: atomic chain behavior needs translation
*              Schedule                        FuSaRTS: osThreadYield
*              GetTaskID                       FuSaRTS: osThreadGetId
*              GetTaskState                    FuSaRTS: osThreadGetState
*                                              gap: state model translation is required
*            Interrupt Handling:
*              DisableAllInterrupts            FuSaRTS: __disable_irq()
*              EnableAllInterrupts             FuSaRTS: __enable_irq()
*              SuspendAllInterrupts            FuSaRTS: __disable_irq() + nesting counter
*                                              gap: nesting state must be maintained
*              ResumeAllInterrupts             FuSaRTS: nesting counter + __enable_irq()
*                                              gap: nesting state must be maintained
*              SuspendOSInterrupts             FuSaRTS: __set_BASEPRI()
*                                              gap: interrupt threshold handling must be defined
*              ResumeOSInterrupts              FuSaRTS: __set_BASEPRI(0)
*                                              gap: interrupt threshold handling must be defined
*            Resource Management:
*              GetResource                     FuSaRTS: osMutexAcquire
*                                              gap: priority ceiling / ownership semantics must be preserved
*              ReleaseResource                 FuSaRTS: osMutexRelease
*                                              gap: ownership semantics must be preserved
*            Event Control:
*              SetEvent                        FuSaRTS: osThreadFlagsSet
*                                              gap: task-event semantics need translation
*              ClearEvent                      FuSaRTS: osThreadFlagsClear
*                                              gap: calling-task semantics need translation
*              GetEvent                        FuSaRTS: osThreadFlagsGet
*                                              gap: task-event shadow state may be required
*              WaitEvent                       FuSaRTS: osThreadFlagsWait
*                                              gap: OSEK wait semantics and clear behavior need translation
*            Alarms:
*              GetAlarmBase                    FuSaRTS: static alarm configuration tables
*                                              gap: counter/alarm metadata must be provided by the wrapper
*              GetAlarm                        FuSaRTS: osTimerIsRunning + kernel tick accounting
*                                              gap: remaining ticks are not returned by CMSIS directly
*              SetRelAlarm                     FuSaRTS: osTimerStart
*                                              gap: first-shot and cycle handling must be emulated
*              SetAbsAlarm                     FuSaRTS: osTimerStart + osKernelGetTickCount
*                                              gap: absolute-to-relative conversion must be implemented
*              CancelAlarm                     FuSaRTS: osTimerStop
*            Operating System Execution Control:
*              GetActiveApplicationMode        FuSaRTS: module-local application mode state
*                                              gap: current mode storage must be implemented
*              StartOS                         FuSaRTS: osKernelInitialize + osKernelStart
*                                              gap: init sequencing and error reporting must be aligned
*              ShutdownOS                      FuSaRTS: safe-state shutdown path
*                                              gap: shutdown behavior after hook return is implementation specific
*            Hooks:
*              StartupHook                     FuSaRTS: weak hook entry point
*              ShutdownHook                    FuSaRTS: weak hook entry point
*              ErrorHook                       FuSaRTS: weak hook entry point
*              PreTaskHook                     FuSaRTS: weak hook entry point
*              PostTaskHook                    FuSaRTS: weak hook entry point
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "Os_Wrapper.h"
#include "Os.h"
#include "Os_Internals.h"
#include "RTE_Components.h"
#include CMSIS_device_header

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

typedef struct
{
  osTimerId_t Alarm;
  uint8 FirstRun;
  TickType Cycle;
} Os_AlarmInfoType;

typedef struct
{
  osThreadId_t Tasks[OS_TASKID_COUNT];
  Os_AlarmInfoType Alarms[OS_ALARMID_COUNT];
} Os_OsekToCmsisMapType;

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

#define OS_START_SEC_VAR_INIT
#include "Os_MemMap.h"

STATIC VAR(Os_OsekToCmsisMapType, OS_VAR_NOINIT) Os_OsekToCmsisMap;
STATIC VAR(uint16, OS_VAR_NOINIT) Os_InterruptNestingCounter = 0U;
STATIC VAR(AppModeType, OS_VAR_NOINIT) Os_AppMode = OSDEFAULTAPPMODE;
STATIC VAR(uint8, OS_VAR_NOINIT) Os_InterruptReturnToUser = 0U;

#define OS_STOP_SEC_VAR_INIT
#include "Os_MemMap.h"

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/
STATIC FUNC(uint32, OS_CODE) Os_GoToSupervisor(void);
STATIC FUNC(uint32, OS_CODE) Os_GoToUser(void);
STATIC INLINE FUNC(osStatus_t, OS_CODE) Os_InitTasks(void);
STATIC FUNC(void, OS_CODE) Os_TaskCode(void* param);
STATIC INLINE FUNC(osStatus_t, OS_CODE) Os_InitAlarms(void);
STATIC FUNC(void, OS_CODE) Os_AlarmCallback(void * param);
STATIC INLINE FUNC(osStatus_t, OS_CODE) Os_InitResources(void);
STATIC INLINE FUNC(StatusType, OS_CODE) Os_MapCmsisToOsekStatus(osStatus_t Status);
STATIC INLINE FUNC(StatusType, OS_CODE) Os_MapCmsisToOsekFlagError(uint32_t FlagError);
STATIC INLINE FUNC(TaskStateType, OS_CODE) Os_MapCmsisToOsekTaskState(osThreadState_t TaskState);

/*______ G L O B A L - F U N C T I O N S _____________________________________*/
#define OS_START_SEC_CODE
#include "Os_MemMap.h"

/******************************************************************************/
/*!
* \brief        Activate a task
*
* \param[in]    TaskType(TaskID): task identifier.
* \retval       StatusType: service return code.
*
* \pre          OS is initialized and the task identifier is valid.
* \post         The task is moved toward READY state if activation succeeds.
*
* \req
* \details      The task <TaskID> is transferred from the suspended state into the ready state.
*               The operating system ensures that the task code is being executed from the first statement.
*               Ref: fusa_thread_management.html - UR_TM_5 (consequences of forced resume)
*                    group__CMSIS__RTOS__ThreadMgmt.html - osThreadResume
*/
/******************************************************************************/
FUNC(StatusType, OS_CODE) ActivateTask(TaskType TaskID)
{
  /* Init local variables */
  StatusType RetVal = E_OK;
  osStatus_t CmsisStatus;

#if OS_ERRORCHECK_EXTENDEDSTATUS
  /* Is TaskID invalid? */
  if (TaskID >= (TaskType)OS_TASKID_COUNT)
  {
    /* Set error */
    RetVal = E_OS_ID;
  }
  else
#endif
  {
    /* Call CMSIS-RTOS API */
    CmsisStatus = osThreadResume(Os_OsekToCmsisMap.Tasks[TaskID]);

    /* Convert CMSIS error status */
    RetVal = Os_MapCmsisToOsekStatus(CmsisStatus);
  }

  /* Return */
  return  RetVal;
}

/******************************************************************************/
/*!
* \brief        Terminate the current task
*
* \param[in]    None
* \retval       StatusType: service return code.
*
* \pre          The calling context is a valid task.
* \post         The current task is transitioned to suspended state.
*
* \req
* \details      This service causes the termination of the calling task.
*               The calling task is transferred from the running state into the suspended state.
*               Ref: fusa_thread_management.html - UR_TM_3 (release resources before termination)
*                                                - UR_TM_6 (consequences of suspending blocked thread)
*                    group__CMSIS__RTOS__ThreadMgmt.html - osThreadSuspend
*/
/******************************************************************************/
FUNC(StatusType, OS_CODE) TerminateTask(void)
{
  /* Init local variables */
  StatusType RetVal = E_OK;
  osStatus_t CmsisStatus;

  /* Call CMSIS-RTOS API */
  CmsisStatus = osThreadSuspend(osThreadGetId());

  /* Convert CMSIS error status */
  RetVal = Os_MapCmsisToOsekStatus(CmsisStatus);

  /* Return */
  return  RetVal;
}

/******************************************************************************/
/*!
* \brief        Chain the current task to another task
*
* \param[in]    TaskType(TaskID): next task identifier.
* \retval       StatusType: service return code.
*
* \pre          The calling context is a valid task and the destination task
*               identifier is valid.
* \post         The current task is terminated and the destination task is
*               activated if the service succeeds.
*
* \req
* \details      This service causes the termination of the calling task.
*               After termination of the calling task a succeeding task <TaskID> is activated.
*               Ref: fusa_thread_management.html - UR_TM_3, UR_TM_5
*                    group__CMSIS__RTOS__ThreadMgmt.html - osThreadResume, osThreadSuspend
*/
/******************************************************************************/
FUNC(StatusType, OS_CODE) ChainTask(TaskType TaskID)
{
  (void)TaskID;
  return (StatusType)0U;

  /* Not implemented */
}

/******************************************************************************/
/*!
* \brief        Schedule the next ready task
*
* \param[in]    None
* \retval       StatusType: service return code.
*
* \pre          OS scheduler is active.
* \post         Processor control may be yielded to another ready task.
*
* \req
* \details      If a higher-priority task is ready, the current task is put into the ready state and the higher-priority task is executed.
*               Otherwise the calling task is continued.
*               Ref: group__CMSIS__RTOS__ThreadMgmt.html - osThreadYield
*/
/******************************************************************************/
FUNC(StatusType, OS_CODE) Schedule(void)
{
  /* Init local variables */
  StatusType RetVal = E_OK;
  osStatus_t CmsisStatus;

  /* Call CMSIS-RTOS API - it always returns osOK */
  CmsisStatus = osThreadYield();

  /* Convert CMSIS error status */
  RetVal = Os_MapCmsisToOsekStatus(CmsisStatus);

  /* Return */
  return  RetVal;
}


/******************************************************************************/
/*!
* \brief        Get the ID of the current task
*
* \param[in]    TaskRefType(TaskID): pointer to task identifier output.
* \retval       StatusType: service return code.
*
* \pre          The service is called from task context and TaskID is not NULL.
* \post         The current task identifier is written to TaskID if the service succeeds.
*
* \req
* \details      The service GetTaskID returns the identification of the currently running task.
*               Ref: group__CMSIS__RTOS__ThreadMgmt.html - osThreadGetId
*                    The current CMSIS thread ID is mapped back to the generated OSEK task table
*/
/******************************************************************************/
FUNC(StatusType, OS_CODE) GetTaskID(TaskRefType TaskID)
{
  /* Init local variables */
  StatusType RetVal = E_OK;
  uint8 SearchFlag = E_NOT_OK;
  osThreadId_t CurrentThread;
  TaskType TaskIndex;

#if OS_ERRORCHECK_EXTENDEDSTATUS
  if(TaskID == NULL)
  {
    RetVal = E_OS_VALUE;
  }
  else
#endif
  {
    /* Retrieve current running thread */
    CurrentThread = osThreadGetId();

    /* Are there still configured tasks to loop on? */
    for (TaskIndex = 0U; (TaskIndex < OS_TASKID_COUNT) && (SearchFlag == E_NOT_OK); TaskIndex++)
    {
      /* Is the ID the current one? */
      if (Os_OsekToCmsisMap.Tasks[TaskIndex] == CurrentThread)
      {
        /* Return the thread's ID */
        *TaskID = TaskIndex;

        /* End search */
        SearchFlag = E_OK;
      }
    }

    /* Was matching task not found? */
    if (SearchFlag == E_NOT_OK)
    {
      /* Return invalid task */
      *TaskID = INVALID_TASK;
      RetVal = E_OS_ID;
    }
  }

  /* Return */
  return  RetVal;
}

/******************************************************************************/
/*! 
* \brief        Get the state of a task
*
* \param[in]    TaskType(TaskID): task identifier.
* \param[in]    TaskStateRefType(State): pointer to task state output.
* \retval       StatusType: service return code.
*
* \pre          Task identifier is valid and output pointer is not NULL.
* \post         The current task state is written to State if the service succeeds.
*
* \req
* \details      The service GetTaskState returns the state of the task <TaskID> at the time of calling GetTaskState.
*               Ref: group__CMSIS__RTOS__ThreadMgmt.html - osThreadGetState
*                    The CMSIS osThreadState_t values must be translated to the OSEK
*                    TaskStateType values (RUNNING, READY, WAITING, SUSPENDED)
*/
/******************************************************************************/
FUNC(StatusType, OS_CODE) GetTaskState(TaskType TaskID, TaskStateRefType State)
{
  /* Init local variables */
  StatusType RetVal = E_OK;
  osThreadState_t TaskState;

#if OS_ERRORCHECK_EXTENDEDSTATUS
  if (TaskID >= (TaskType)OS_TASKID_COUNT)
  {
    /* Set error */
    RetVal =  E_OS_ID;
  }
  else if(State == NULL)
  {
    /* Set error */
    RetVal =  E_OS_VALUE;
  }
  else
#endif
  {
    /* Get CMSIS-RTOS thread state */
    TaskState = osThreadGetState(Os_OsekToCmsisMap.Tasks[TaskID]);

    /* Translate CMSIS thread state to OSEK task state */
    *State = Os_MapCmsisToOsekTaskState(TaskState);
  }

  return RetVal;
}

/******************************************************************************/
/*!
* \brief        Disable all interrupts
*
* \param[in]    None
* \retval       None
*
* \pre          None
* \post         All maskable interrupts are disabled.
*
* \req
* \details      This service disables all interrupts for which the hardware supports disabling.
*               The state before is saved for the EnableAllInterrupts call.
*               Ref: fusa_RTOS_calls_from_isr.html - RTOS calls from ISR
*                    fusa_system.html - System level considerations
*                    Maps to __disable_irq() (CMSIS-Core)
*/
/******************************************************************************/
FUNC(void, OS_CODE) DisableAllInterrupts(void)
{
  /* Init local variables */
  uint32 ReturnToUser;

  /* Go to supervisor mode */
  ReturnToUser = Os_GoToSupervisor();

  /* Disable all interrupts */
  __disable_irq();

  /* Mode change was performed? */
  /* NOTE: Os_GoToUser() uses SVC #2, which is blocked by PRIMASK after __disable_irq(). */
  /* The return to user mode is therefore deferred to EnableAllInterrupts(),             */
  /* after __enable_irq() restores SVC availability.                                    */
  if (ReturnToUser == 1U)
  {
    /* Defer return to user mode */
    Os_InterruptReturnToUser = 1U;
  }
}

/******************************************************************************/
/*!
* \brief        Enable all interrupts
*
* \param[in]    None
* \retval       None
*
* \pre          None
* \post         All maskable interrupts are enabled according to the current
*               platform state.
*
* \req
* \details      This service restores the state saved by DisableAllInterrupts.
*               Ref: fusa_RTOS_calls_from_isr.html - RTOS calls from ISR
*                    Maps to __enable_irq() (CMSIS-Core)
*/
/******************************************************************************/
FUNC(void, OS_CODE) EnableAllInterrupts(void)
{
  /* Init local variables */
  uint32 ReturnToUser;

  /* Go to supervisor mode (required to call __enable_irq) */
  /* If already in supervisor mode after DisableAllInterrupts, this returns 0 */
  ReturnToUser = Os_GoToSupervisor();

  /* Enable all interrupts */
  __enable_irq();

  /* Return to user mode if:
   * - EnableAllInterrupts was called directly from user mode (ReturnToUser == 1U), OR
   * - DisableAllInterrupts had deferred the return to user mode (Os_InterruptReturnToUser == 1U) */
  if ((ReturnToUser == 1U) || (Os_InterruptReturnToUser == 1U))
  {
    /* Return to user mode */
    Os_GoToUser();
    Os_InterruptReturnToUser = 0U;
  }
}

/******************************************************************************/
/*!
* \brief        Suspend all interrupts
*
* \param[in]    None
* \retval       None
*
* \pre          None
* \post         Interrupt suspension nesting level is increased.
*
* \req
* \details      This service saves the recognition status of all interrupts and disables all interrupts
*               for which the hardware supports disabling.
*               Ref: fusa_RTOS_calls_from_isr.html - RTOS calls from ISR
*                    Requires nesting counter; use __disable_irq() + counter increment
*/
/******************************************************************************/
FUNC(void, OS_CODE) SuspendAllInterrupts(void)
{
  /* Is the first call of this service? */
  if(Os_InterruptNestingCounter == 0U)
  {
    DisableAllInterrupts();
  }

  /* Increment nesting counter */
  Os_InterruptNestingCounter++;
}

/******************************************************************************/
/*!
* \brief        Resume all interrupts
*
* \param[in]    None
* \retval       None
*
* \pre          SuspendAllInterrupts has been called previously.
* \post         Interrupt suspension nesting level is decreased.
*
* \req
* \details      This service restores the recognition status of all interrupts saved by the SuspendAllInterrupts service.
*               Ref: fusa_RTOS_calls_from_isr.html - RTOS calls from ISR
*                    Decrement nesting counter; call __enable_irq() only when counter reaches zero
*/
/******************************************************************************/
FUNC(void, OS_CODE) ResumeAllInterrupts(void)
{
  /* Has SuspendAllInterrupts been called before? */
  if(Os_InterruptNestingCounter > 0U)
  {
    /* Decrement nesting counter */
    Os_InterruptNestingCounter--;
  }

  /* Should interrupts be restored? */
  if(Os_InterruptNestingCounter == 0U)
  {
    /* Restore interrupt */
    EnableAllInterrupts();
  }
}

/******************************************************************************/
/*!
* \brief        Suspend OS interrupts
*
* \param[in]    None
* \retval       None
*
* \pre          None
* \post         OS managed interrupt sources are masked.
*
* \req
* \details      This service saves the recognition status of interrupts of category 2 and disables the recognition of these interrupts.
*               Ref: fusa_RTOS_calls_from_isr.html - RTOS calls from ISR
*                    Maps to __set_BASEPRI() masking interrupts at or below OS threshold
*/
/******************************************************************************/
FUNC(void, OS_CODE) SuspendOSInterrupts(void)
{
  /* Not implemented */
}

/******************************************************************************/
/*!
* \brief        Resume OS interrupts
*
* \param[in]    None
* \retval       None
*
* \pre          SuspendOSInterrupts has been called previously.
* \post         OS managed interrupt sources are unmasked.
*
* \req
* \details      This service restores the recognition status of interrupts saved by the SuspendOSInterrupts service.
*               Ref: fusa_RTOS_calls_from_isr.html - RTOS calls from ISR
*                    Maps to __set_BASEPRI(0) to unmask OS-managed interrupts
*/
/******************************************************************************/
FUNC(void, OS_CODE) ResumeOSInterrupts(void)
{
  /* Not implemented */
}

/******************************************************************************/
/*!
* \brief        Acquire a resource
*
* \param[in]    ResourceType(ResourceID): resource identifier.
* \retval       StatusType: service return code.
*
* \pre          Resource identifier is valid.
* \post         The resource is locked by the caller if the service succeeds.
*
* \req
* \details      This call serves to enter critical sections in the code that are assigned to the resource referenced by <ResID>.
*               A critical section shall always be left using ReleaseResource.
*               Ref: fusa_mutex_management.html - Mutex Management considerations
*                    fusa_thread_management.html - UR_TM_4 (priority inheritance / PCP)
*                    group__CMSIS__RTOS__MutexMgmt.html - osMutexAcquire
*/
/******************************************************************************/
FUNC(StatusType, OS_CODE) GetResource(ResourceType ResourceID)
{
  (void)ResourceID;
  return (StatusType)0U;
}

/******************************************************************************/
/*!
* \brief        Release a resource
*
* \param[in]    ResourceType(ResourceID): resource identifier.
* \retval       StatusType: service return code.
*
* \pre          Resource identifier is valid and the caller owns the resource.
* \post         The resource is released if the service succeeds.
*
* \req
* \details      ReleaseResource is the counterpart of GetResource and serves to leave critical sections in the code
*               that are assigned to the resource referenced by <ResID>.
*               Ref: fusa_mutex_management.html - Mutex Management considerations
*                    group__CMSIS__RTOS__MutexMgmt.html - osMutexRelease
*/
/******************************************************************************/
FUNC(StatusType, OS_CODE) ReleaseResource(ResourceType ResourceID)
{
  (void)ResourceID;
  return (StatusType)0U;
}

/******************************************************************************/
/*!
* \brief        Set an event mask on a task
*
* \param[in]    TaskType(TaskID): task identifier.
* \param[in]    EventMaskType(Mask): event mask to set.
* \retval       StatusType: service return code.
*
* \pre          The destination task is valid and supports event handling.
* \post         The requested event bits are set for the destination task
*               if the service succeeds.
*
* \req
* \details      The events of task <TaskID> are set according to the event mask <Mask>.
*               Calling SetEvent causes the task <TaskID> to be transferred to the ready state, if it was waiting
*               for at least one of the events specified in <Mask>.
*               Ref: group__CMSIS__RTOS__ThreadFlagsMgmt.html - osThreadFlagsSet
*                    fusa_RTOS_calls_from_isr.html - osThreadFlagsSet is ISR-safe
*/
/******************************************************************************/
FUNC(StatusType, OS_CODE) SetEvent(TaskType TaskID, EventMaskType Mask)
{
  /* Init local variables */
  StatusType RetVal = E_OK;
  uint32_t CmsisRetVal;

#if OS_ERRORCHECK_EXTENDEDSTATUS
  /* Is TaskID invalid? */
  if (TaskID >= (TaskType)OS_TASKID_COUNT)
  {
    /* Set error */
    RetVal = E_OS_ID;
  }
  else
#endif
  {
    /* Call CMSIS-RTOS API */
    CmsisRetVal = osThreadFlagsSet(Os_OsekToCmsisMap.Tasks[TaskID], Mask);

    /* Convert CMSIS error status */
    RetVal = Os_MapCmsisToOsekFlagError(CmsisRetVal);
  }

  /* Return */
  return  RetVal;
}

/******************************************************************************/
/*!
* \brief        Clear event bits of the calling task
*
* \param[in]    EventMaskType(Mask): event mask to clear.
* \retval       StatusType: service return code.
*
* \pre          The calling context is a task that supports event handling.
* \post         The requested event bits are cleared if the service succeeds.
*
* \req
* \details      The events of the extended task calling ClearEvent are cleared according to the event mask <Mask>.
*               Ref: group__CMSIS__RTOS__ThreadFlagsMgmt.html - osThreadFlagsClear
*                    Only valid for the currently running thread
*/
/******************************************************************************/
FUNC(StatusType, OS_CODE) ClearEvent(EventMaskType Mask)
{
  /* Init local variables */
  StatusType RetVal = E_OK;
  uint32_t CmsisRetVal;

  /* Call CMSIS-RTOS API */
  CmsisRetVal = osThreadFlagsClear(Mask);

  /* Convert CMSIS error status */
  RetVal = Os_MapCmsisToOsekFlagError(CmsisRetVal);

  /* Return */
  return  RetVal;
}

/******************************************************************************/
/*!
* \brief        Get event mask of a task
*
* \param[in]    TaskType(TaskID): task identifier.
* \param[in]    EventMaskRefType(Mask): pointer to event mask output.
* \retval       StatusType: service return code.
*
* \pre          Input identifier and output pointer are valid.
* \post         The current event mask is written if the service succeeds.
*
* \req
* \details      This service returns the current state of all event bits of the task <TaskID>, not the events that the task is waiting for.
*               The current status of the event mask of task <TaskID> is copied to <Event>.
*               Limitation: OSEK implementation support only to retrieve events for the current task.
*               Ref: group__CMSIS__RTOS__ThreadFlagsMgmt.html - osThreadFlagsGet (current thread only)
*                    For a task other than the running one the wrapper must maintain a shadow copy of the event mask
*                    in its internal task table
*/
/******************************************************************************/
FUNC(StatusType, OS_CODE) GetEvent(TaskType TaskID, EventMaskRefType Mask)
{
   (void)TaskID; /* Not used in this implementation */

  /* Init local variables */
  StatusType RetVal = E_OK;

#if OS_ERRORCHECK_EXTENDEDSTATUS
  if(Mask == NULL)
  {
    /* Set error */
    RetVal = E_OS_VALUE;
  }
  else
#endif
  {
    /* Call CMSIS-RTOS API */
    *Mask = osThreadFlagsGet();
  }

  /* Return */
  return  RetVal;
}

/******************************************************************************/
/*!
* \brief        Wait for one or more events
*
* \param[in]    EventMaskType(Mask): event mask to wait for.
* \retval       StatusType: service return code.
*
* \pre          The calling context is an extended task.
* \post         The task remains blocked until one of the requested events
*               is available.
*
* \req
* \details      The state of the calling task is set to waiting, unless at least one of the events specified in <Mask>
*               has already been set.
*               Ref: group__CMSIS__RTOS__ThreadFlagsMgmt.html - osThreadFlagsWait
*                    fusa_rtx_start.html - UR_SI_2 (requires kernel started)
*                    Use osFlagsWaitAny to match OSEK OR semantics
*/
/******************************************************************************/
FUNC(StatusType, OS_CODE) WaitEvent(EventMaskType Mask)
{
  /* Init local variables */
  StatusType RetVal = E_OK;
  uint32_t CmsisRetVal;

  /* Call CMSIS-RTOS API */
  CmsisRetVal = osThreadFlagsWait(Mask, osFlagsWaitAny | osFlagsNoClear, osWaitForever);

  /* Is CMIS call faulty */
  RetVal = Os_MapCmsisToOsekFlagError(CmsisRetVal);

  /* Return */
  return  RetVal;
}

/******************************************************************************/
/*!
* \brief        Get static alarm base information
*
* \param[in]    AlarmType(AlarmID): alarm identifier.
* \param[in]    AlarmBaseRefType(Info): pointer to alarm base information.
* \retval       StatusType: service return code.
*
* \pre          Alarm identifier and output pointer are valid.
* \post         Static alarm base information is written if the service
*               succeeds.
*
* \req
* \details      The system service GetAlarmBase reads the alarm base characteristics.
*               The return value <Info> is a structure in which the information of data type AlarmBaseType is stored.
*               Ref: config_rtx5.html - Timer Configuration (OS_TIMER_CB_QUEUE)
*                    No direct CMSIS equivalent; return data from static alarm/counter configuration tables
*                    generated at project level
*/
/******************************************************************************/
FUNC(StatusType, OS_CODE) GetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info)
{
#if OS_ERRORCHECK_EXTENDEDSTATUS
  if (AlarmID >= (AlarmType)OS_ALARMID_COUNT)
  {
    /* Set error */
    return E_OS_ID;
  }
  else if (Info == NULL)
  {
    /* Set error */
    return E_OS_VALUE;
  }
  else
#endif
  {
    (void)AlarmID;
    (void)Info;

    /* Not implemented */
    return (StatusType)0U;
  }
}

/******************************************************************************/
/*!
* \brief        Get remaining alarm ticks
*
* \param[in]    AlarmType(AlarmID): alarm identifier.
* \param[in]    TickRefType(Ticks): pointer to remaining ticks.
* \retval       StatusType: service return code.
*
* \pre          Alarm identifier and output pointer are valid.
* \post         Remaining ticks are written if the service succeeds.
*
* \req
* \details      The system service GetAlarm returns the relative value in ticks before the alarm <AlarmID> expires.
*               Ref: group__CMSIS__RTOS__TimerMgmt.html - osTimerIsRunning
*                    group__CMSIS__RTOS__KernelCtrl.html - osKernelGetTickCount
*                    CMSIS has no API to query remaining timer ticks; the wrapper must track start time
*                    and expiry tick internally
*/
/******************************************************************************/
FUNC(StatusType, OS_CODE) GetAlarm(AlarmType AlarmID, TickRefType Ticks)
{
#if OS_ERRORCHECK_EXTENDEDSTATUS
  if (AlarmID >= (AlarmType)OS_ALARMID_COUNT)
  {
    /* Set error */
    return E_OS_ID;
  }
  else if (Ticks == NULL)
  {
    /* Set error */
    return E_OS_VALUE;
  }
  else
#endif
  {
    (void)AlarmID;
    (void)Ticks;

    /* Not implemented */
    return (StatusType)0U;
  }
}

/******************************************************************************/
/*!
* \brief        Start a relative alarm
*
* \param[in]    AlarmType(AlarmID): alarm identifier.
* \param[in]    TickType(Increment): relative start tick.
* \param[in]    TickType(Cycle): cycle tick.
* \retval       StatusType: service return code.
*
* \pre          Alarm identifier is valid.
* \post         The alarm is armed relative to the current counter value if
*               the service succeeds.
*
* \req
* \details      The system service occupies the alarm <AlarmID> element.
*               After <increment> ticks have elapsed, the task assigned to the alarm <AlarmID> is activated
*               or the assigned event is set or the alarm-callback routine is called.
*               Ref: fusa_timer_management.html - Timer Management (UR_TI_1..6)
*                    group__CMSIS__RTOS__TimerMgmt.html - osTimerStart
*                    CMSIS does not natively support different first-shot and cycle times; a one-shot timer
*                    restarted from its callback is required
*/
/******************************************************************************/
FUNC(StatusType, OS_CODE) SetRelAlarm(AlarmType AlarmID, TickType Increment, TickType Cycle)
{
  /* Init local variables */
  StatusType RetVal = E_OK;
  osStatus_t CmsisStatus;
  TickType FirstCycle;

#if OS_ERRORCHECK_EXTENDEDSTATUS
  /* Is AlarmID invalid? */
  if (AlarmID >= (AlarmType)OS_ALARMID_COUNT)
  {
    /* Set error */
    RetVal = E_OS_ID;
  }
  else
#endif
  {
    /* Is timer already running? */
    if (osTimerIsRunning(Os_OsekToCmsisMap.Alarms[AlarmID].Alarm) != 0U)
    {
      /* Set error */
      RetVal = E_OS_STATE;
    }
    else
    {
      /* Is increment used? */
      if (Increment > 0U)
      {
        /* The first cycle is equal to increment */
        FirstCycle = Increment;
      }
      else
      {
        /* The first cycle is equal to cycle */
        FirstCycle = Cycle;
      }
      
      /* Call CMSIS-RTOS API */
      CmsisStatus = osTimerStart(Os_OsekToCmsisMap.Alarms[AlarmID].Alarm, FirstCycle);

      /* Convert CMSIS error status */
      RetVal = Os_MapCmsisToOsekStatus(CmsisStatus);

      /* Is call succesful? */
      if(RetVal == E_OK)
      {
        /* Set alarm properties*/
        Os_OsekToCmsisMap.Alarms[AlarmID].FirstRun = (Increment > 0U) ? 1U : 0U;
        Os_OsekToCmsisMap.Alarms[AlarmID].Cycle = Cycle;
      }
    }
  }

  /* Return */
  return  RetVal;
}

/******************************************************************************/
/*!
* \brief        Start an absolute alarm
*
* \param[in]    AlarmType(AlarmID): alarm identifier.
* \param[in]    TickType(Start): absolute start tick.
* \param[in]    TickType(Cycle): cycle tick.
* \retval       StatusType: service return code.
*
* \pre          Alarm identifier is valid.
* \post         The alarm is armed relative to the configured counter base if
*               the service succeeds.
*
* \req
* \details      The system service occupies the alarm <AlarmID> element.
*               When <start> ticks are reached, the task assigned to the alarm <AlarmID> is activated
*               or the assigned event is set or the alarm-callback routine is called.
*               Ref: fusa_timer_management.html - Timer Management (UR_TI_1..6)
*                    group__CMSIS__RTOS__TimerMgmt.html - osTimerStart
*                    group__CMSIS__RTOS__KernelCtrl.html - osKernelGetTickCount (to compute offset)
*/
/******************************************************************************/
FUNC(StatusType, OS_CODE) SetAbsAlarm(AlarmType AlarmID, TickType Start, TickType Cycle)
{
#if OS_ERRORCHECK_EXTENDEDSTATUS
  if (AlarmID >= (AlarmType)OS_ALARMID_COUNT)
  {
    /* Set error */
    return E_OS_ID;
  }
  else
#endif
  {
    (void)AlarmID;
    (void)Start;
    (void)Cycle;

    /* Not implemented */
    return (StatusType)0U;
  }
}

/******************************************************************************/
/*!
* \brief        Cancel an alarm
*
* \param[in]    AlarmType(AlarmID): alarm identifier.
* \retval       StatusType: service return code.
*
* \pre          Alarm identifier is valid.
* \post         The selected alarm is stopped if the service succeeds.
*
* \req
* \details      The system service cancels the alarm <AlarmID>.
*               Ref: group__CMSIS__RTOS__TimerMgmt.html - osTimerStop
*/
/******************************************************************************/
FUNC(StatusType, OS_CODE) CancelAlarm(AlarmType AlarmID)
{
  /* Init local variables */
  StatusType RetVal = E_OK;
  osStatus_t CmsisStatus;

#if OS_ERRORCHECK_EXTENDEDSTATUS
  /* Is AlarmID invalid? */
  if (AlarmID >= (AlarmType)OS_ALARMID_COUNT)
  {
    /* Set error */
    RetVal = E_OS_ID;
  }
  else
#endif
  {
    /* Is timer already running? */
    if (osTimerIsRunning(Os_OsekToCmsisMap.Alarms[AlarmID].Alarm) == 0U)
    {
      /* Set error */
      RetVal = E_OS_NOFUNC;
    }
    else
    {
      /* Call CMSIS-RTOS API */
      CmsisStatus = osTimerStop(Os_OsekToCmsisMap.Alarms[AlarmID].Alarm);

      /* Convert CMSIS error status */
      RetVal = Os_MapCmsisToOsekStatus(CmsisStatus);

      /* Is call succesful? */
      if(RetVal == E_OK)
      {
        /* Clear alarm properties */
        Os_OsekToCmsisMap.Alarms[AlarmID].FirstRun = 0U;
        Os_OsekToCmsisMap.Alarms[AlarmID].Cycle = 0U;
      }
    }
  }

  /* Return */
  return  RetVal;
}

/******************************************************************************/
/*!
* \brief        Get the active application mode
*
* \param[in]    None
* \retval       AppModeType: active application mode.
*
* \pre          StartOS has been called.
* \post         None
*
* \req
* \details      This service returns the current application mode.
*               It may be used to write mode dependent code.
*               Ref: theory_of_operation.html - General OS design context
*                    No direct CMSIS-RTOS2 equivalent; wrapper must store the mode chosen at StartOS
*                    into a module-local variable
*/
/******************************************************************************/
FUNC(AppModeType, OS_CODE) GetActiveApplicationMode(void)
{
   /*Currently Mode is not implemented*/
  return Os_AppMode;
}

/******************************************************************************/
/*!
* \brief        Start the Os
*
* \param[in]    AppModeType(Mode): application mode.
* \retval       None
*
* \pre          No execution of init is done before.
* \post         None
*
* \req
* \details      The user can call this system service to start the operating system in a specific mode.
*               Ref: fusa_rtx_start.html - Start and Initialization (UR_SI_1..8)
*                    cre_rtx_proj.html - Creating an RTX project (init sequence example)
*                    group__CMSIS__RTOS__KernelCtrl.html - osKernelInitialize, osKernelStart
*/
/******************************************************************************/
FUNC(void, OS_CODE) StartOS(AppModeType Mode)
{
  /* Init local variables */
  osStatus_t Status = osOK;

  Os_AppMode = Mode;

  /* Update system Core clock */
  SystemCoreClockUpdate();

  /* Is system core clock not initialized? */
  if (SystemCoreClock == 0U)
  {
    /* Set OS error */
    Status = osError;
  }

  /* Is RTOS status OK? */
  if (Status == osOK)
  {
    /* Is the RTOS kernel inactive? */
    if(osKernelGetState() == osKernelInactive)
    {
      /* Initialize the RTOS kernel */
      Status = osKernelInitialize();
    }
    else
    {
      /* Set OS error */
      Status = osError;
    }
  }

  /* Is RTOS status OK? */
  if (Status == osOK)
  {
    /* Create OS alarms */
    Status |= Os_InitAlarms();

    /* Create OS tasks */
    Status |= Os_InitTasks();

    /* Create OS resources */
    Status |= Os_InitResources();
  }

  /* Is RTOS status OK? */
  if (Status == osOK)
  {
    /* Call StartupHook */
    /* OSEK 2.2.3 ch 11.3 */
    StartupHook();

    /* Inhibit creation of new privileged threads */
    /* UR_PI_PRIV_4 */
    Status = osThreadProtectPrivileged();
  }

  /* Is RTOS status OK? */
  if (Status == osOK)
  {
    /* Configure kernel access protection */
    /* UR_PI_SC_2 */
    Status = osKernelProtect(OS_SAFETYCLASS_KERNELPROTECT);
  }

  /* Is RTOS status OK? */
  if (Status == osOK)
  {
    /* Is the RTOS kernel ready? */
    if (osKernelGetState() == osKernelReady)
    {
      /* Start the RTOS kernel */
      Status = osKernelStart();
    }
    else
    {
      /* Set OS error */
      Status = osError;
    }
  }

  /* OS fails if it comes here */
  ErrorHook(E_OS_STATE);
  ShutdownOS(E_OS_STATE);
}

/******************************************************************************/
/*!
* \brief        Shutdown the Os
*
* \param[in]    StatusType(Error): error occured.
* \retval       None
*
* \pre          No execution of init is done before.
* \post         None
*
* \req
* \details      The user can call this system service to abort the overall system (e.g. emergency off).
*               The operating system also calls this function internally, if it has reached an undefined internal state
*               and is no longer ready to run.
*               Ref: fusa_rtx_start.html - UR_SI_2 (APIs requiring kernel started)
*                    group__CMSIS__RTOS__KernelCtrl.html - no osKernelStop exists; use safe state
*/
/******************************************************************************/
FUNC(void, OS_CODE) ShutdownOS(StatusType Error)
{
  (void)Error;

  /* Call ShutdownHook */
  /* OSEK 2.2.3 ch 13.7.2.3 */
  ShutdownHook(Error);
}

/******************************************************************************/
/*!
* \brief        Startup hook
*
* \param[in]    None
* \retval       None
*
* \pre          OS initialization has completed and scheduling has not yet
*               started.
* \post         None
*
* \req
* \details      This hook routine is called by the operating system at the end of the operating system initialisation
*               and before the scheduler is running.
*               Ref: fusa_rtx_start.html - UR_SI_1 (init before kernel start)
*                    cre_rtx_proj.html - Startup hook placement in project
*/
/******************************************************************************/
__WEAK FUNC(void, OS_CODE) StartupHook(void)
{
}

/******************************************************************************/
/*!
* \brief        Shutdown hook
*
* \param[in]    StatusType(Fatalerror): shutdown reason.
* \retval       None
*
* \pre          Shutdown sequence has been requested.
* \post         None
*
* \req
* \details      This hook routine is called by the operating system when the OS service ShutdownOS has been called.
*               This routine is called during the operating system shut down.
*               Ref: fusa_rtx_start.html - Startup/shutdown considerations
*                    group__CMSIS__RTOS__KernelCtrl.html - no osKernelStop; safe state pattern
*/
/******************************************************************************/
__WEAK FUNC(void, OS_CODE) ShutdownHook(StatusType Fatalerror)
{
  (void)Fatalerror;
}

/******************************************************************************/
/*!
* \brief        Error hook
*
* \param[in]    StatusType(Error): service error code.
* \retval       None
*
* \pre          An OS service error has been detected.
* \post         None
*
* \req
* \details      This hook routine is called by the operating system at the end of a system service which returns StatusType
*               not equal E_OK. It is called before returning to the task level.
*               Ref: fusa_rtx_return_codes.html - FuSa RTX return codes
*                    group__CMSIS__RTOS__Definitions.html - osStatus_t values
*/
/******************************************************************************/
__WEAK FUNC(void, OS_CODE) ErrorHook(StatusType Error)
{
  (void)Error;
}

/******************************************************************************/
/*!
* \brief        Pre-task hook
*
* \param[in]    None
* \retval       None
*
* \pre          A task is about to start or resume execution.
* \post         None
*
* \req
* \details      This hook routine is called by the operating system before executing a new task, but after the transition
*               of the task to the running state.
*               Ref: fusa_thread_management.html - Thread Management (UR_TM_1..10)
*/
/******************************************************************************/
__WEAK FUNC(void, OS_CODE) PreTaskHook(void)
{
}

/******************************************************************************/
/*!
* \brief        Post-task hook
*
* \param[in]    None
* \retval       None
*
* \pre          A task is about to terminate, block or yield logical control.
* \post         None
*
* \req
* \details      This hook routine is called by the operating system after executing the current task, but before leaving
*               the task's running state.
*               Ref: fusa_thread_management.html - UR_TM_3 (ensure resources released before task terminates/suspends)
*/
/******************************************************************************/
__WEAK FUNC(void, OS_CODE) PostTaskHook(void)
{
}

/******************************************************************************/
/*!
* \brief        Get counter current value
*
* \param[in]    CounterType(CounterID): counter identifier.
* \param[in]    TickRefType(Value): pointer to counter value output.
* \retval       StatusType: service return code.
*
* \pre          Counter identifier and output pointer are valid.
* \post         The current counter value is written to Value if the service
*               succeeds.
*
* \req
* \details      This service returns the current value of the selected OS counter.
*               Ref: Uses kernel system timer counter
*/
/******************************************************************************/
FUNC(StatusType, OS_CODE) GetCounterValue(CounterType CounterID, TickRefType Value)
{
  /* Init local variables */
  StatusType RetVal = E_OK;

  /* Is output pointer invalid? */
  if (Value == NULL_PTR)
  {
    RetVal = E_OS_VALUE;
  }
  else
  {
    *Value = (TickType)osKernelGetSysTimerCount();
  }

  /* Return */
  return RetVal;
}

/******************************************************************************/
/*!
* \brief        Get elapsed counter value
*
* \param[in]    CounterType(CounterID): counter identifier.
* \param[in]    TickRefType(Value): pointer to previous counter value input.
* \param[in]    TickRefType(ElapsedValue): pointer to elapsed value output.
* \retval       StatusType: service return code.
*
* \pre          Counter identifier and pointers are valid.
* \post         ElapsedValue is updated with elapsed ticks and Value is updated
*               with the current counter value if the service succeeds.
*
* \req
*
* \details      This service computes elapsed ticks with unsigned modular arithmetic to naturally handle a single counter wrap.
*/
/******************************************************************************/
FUNC(StatusType, OS_CODE) GetElapsedValue(CounterType CounterID, TickRefType Value, TickRefType ElapsedValue)
{
  /* Init local variables */
  StatusType RetVal = E_OK;
  TickType CurrentValue;

  /* Are output pointers invalid? */
  if ((Value == NULL_PTR) || (ElapsedValue == NULL_PTR))
  {
    RetVal = E_OS_VALUE;
  }
  else
  {
    CurrentValue = (TickType)osKernelGetSysTimerCount();
    *ElapsedValue = CurrentValue - *Value;
    *Value = CurrentValue;
  }

  /* Return */
  return RetVal;
}

/******************************************************************************/
/*!
* \brief        Alarm action handler for set event alarms.
*
* \param[in]    Os_AlarmConfigType(AlarmConfig): alarm data.
* \retval       None
*
* \pre          No execution of init is done before.
* \post         None
*
* \req          
* \details      This is a callback function, which is called by the alarm 
*               management. It is called, if an alarm expires, which has 
*               OsAlarmAction configured to be OsAlarmSetEvent.
*/
/******************************************************************************/
FUNC(void, OS_CODE) Os_AlarmActionSetEvent
(
  P2CONST(Os_AlarmCfgType, AUTOMATIC, OS_CONST) AlarmConfig
)
{
   P2CONST(Os_AlarmSetEventCfgType, AUTOMATIC, OS_CONST) alarm;

   /* Get alarm data from configuration */
   alarm = (P2CONST(Os_AlarmSetEventCfgType, AUTOMATIC, OS_CONST))AlarmConfig; /*PRQA S 310*/ /*OS_WRAPPER_001*/

   /* Set event flag for task linked to alarm */
   (void)osThreadFlagsSet(Os_OsekToCmsisMap.Tasks[(alarm->TaskID)], (alarm->Mask));
}

/******************************************************************************/
/*!
* \brief        Alarm action handler for activate task alarms.
*
* \param[in]    Os_AlarmCfgType(AlarmConfig): alarm data.
* \retval       None
*
* \pre          No execution of init is done before.
* \post         None
*
* \req          
* \details      This is a callback function, which is called by the alarm 
*               management. It is called, if an alarm expires, which has 
*               OsAlarmAction configured to be OsAlarmActivateTask.
*/
/******************************************************************************/
FUNC(void, OS_CODE) Os_AlarmActionActivateTask
(
  P2CONST(Os_AlarmCfgType, AUTOMATIC, OS_CONST) AlarmConfig
)
{
   P2CONST(Os_AlarmActivateTaskCfgType, AUTOMATIC, OS_CONST) alarm;

   /* Get alarm data from configuration */
   alarm = (P2CONST(Os_AlarmActivateTaskCfgType, AUTOMATIC, OS_CONST))AlarmConfig; /*PRQA S 310*/ /*OS_WRAPPER_001*/
    
   /* Resume task linked to alarm */
   (void)osThreadResume(Os_OsekToCmsisMap.Tasks[(alarm->TaskID)]); // Task shall be extended for compatibility
}

/******************************************************************************/
/*!
* \brief        Alarm action handler for activate user callback.
*
* \param[in]    Os_AlarmCfgType(AlarmConfig): alarm data.
* \retval       None
*
* \pre          No execution of init is done before.
* \post         None
*
* \req          
* \details      This is a callback function, which is called by the alarm 
*               management. It is called, if an alarm expires, which has 
*               OsAlarmAction configured to be OsAlarmCallUserCallback.
*/
/******************************************************************************/
FUNC(void, OS_CODE) Os_AlarmActionCallUserCallback
(
  P2CONST(Os_AlarmCfgType, AUTOMATIC, OS_CONST) AlarmConfig
)
{
  P2CONST(Os_AlarmUserCallbackCfgType, AUTOMATIC, OS_CONST) alarm;
  /* Get alarm data from configuration */
  alarm = (P2CONST(Os_AlarmUserCallbackCfgType, AUTOMATIC, OS_CONST))AlarmConfig; /*PRQA S 310*/ /*OS_WRAPPER_001*/

  /* Call User callback */
  alarm->Callback();
}

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

/*______ L O C A L - F U N C T I O N S _______________________________________*/

/******************************************************************************/
/*!
* \brief        Function used to enter to supervisor mode.
*
* \param[in]    None
* \retval       None
*
* \pre          No execution of init is done before.
* \post         None
*
* \req          
* \details      Check if it's needed to switch to supervisor mode and make the
*               switch. Return 1 if switch was done
*/
/******************************************************************************/
STATIC FUNC(uint32, OS_CODE) Os_GoToSupervisor(void) /*PRQA S 3006*/ /*OS_WRAPPER_006*/
{
  uint32 ControlRegValue;
  uint32 AipsRegValue;
  uint32 SwitchToSupervisor;

  /* if it's 0 then Thread mode is already in supervisor mode */
  ControlRegValue = __get_CONTROL();
  /* if it's 0 the core is in Thread mode, otherwise in Handler mode */
  AipsRegValue = __get_IPSR();

  /* if core is already in supervisor mode for Thread mode, or running form Handler mode, there is no need to make the switch */
  if((0UL == (ControlRegValue & 1U)) || (0UL < (AipsRegValue & 0xFFU)))
  {
    SwitchToSupervisor = 0U;
  }
  else
  {
    SwitchToSupervisor = 1U;
    __asm volatile("SVC #1" : :);
  }

  return SwitchToSupervisor;
}

/******************************************************************************/
/*!
* \brief        Function used to enter to user mode.
*
* \param[in]    None
* \retval       None
*
* \pre          No execution of init is done before.
* \post         None
*
* \req          
* \details      Function used to switch to user mode
*/
/******************************************************************************/
STATIC FUNC(uint32, OS_CODE) Os_GoToUser(void)
{
  __asm volatile("SVC #2" : :);
  return E_OK;
}

/******************************************************************************/
/*!
* \brief        Initialize Os Tasks
*
* \param[in]    None
* \retval       osStatus_t: return code
*
* \pre          No execution of init is done before.
* \post         None
*
* \req
* \details      This function initialize Os Tasks. Needed to reduce StartOs complexity
*/
/******************************************************************************/
STATIC INLINE FUNC(osStatus_t, OS_CODE) Os_InitTasks(void)
{
  /* Ref: group__CMSIS__RTOS__ThreadMgmt.html - osThreadNew */

  /* Init local variables */
  osStatus_t RetVal = osOK;
  TaskType TaskID;

  /* Create all Os task instances */
  for (TaskID = 0; (TaskID < (TaskType)OS_TASKID_COUNT) && (RetVal == osOK); TaskID++)
  {
    /* Call new thread function */
    Os_OsekToCmsisMap.Tasks[TaskID] = osThreadNew
    (
      Os_TaskCode,
      (void*)(Os_TaskRefs[TaskID]),
      Os_TaskAttributes[TaskID]
    ); /*PRQA S 306*/ /*OS_WRAPPER_002*/

    /* Is task creation faulty? */
    if (Os_OsekToCmsisMap.Tasks[TaskID] == NULL)
    {
      /* Set error */
      RetVal = osError;
    }

    /* Is task not autostarted? */
    if ((Os_TaskRefs[TaskID]->AutostartModes & Os_AppMode) == 0U)
    {
      /* Suspend task */
      RetVal |= osThreadSuspend(Os_OsekToCmsisMap.Tasks[TaskID]);
    }
  }

  return RetVal;
}

/******************************************************************************/
/*!
* \brief        Task action handler.
*
* \param[in]    void(param): task data.
* \retval       None
*
* \pre          No execution of init is done before.
* \post         None
*
* \req          
* \details      This function calls the task entry point. It is within an infinite 
*               loop to ensure that the task is not deleted after completion.
*/
/******************************************************************************/
STATIC FUNC(void, OS_CODE) Os_TaskCode(void* param)
{
  /* Ref: group__CMSIS__RTOS__ThreadMgmt.html - Thread Lifecycle */

  /* Call task entry-point */
  for (;;)
  {
    ((const Os_TaskCfgType*)(param))->Thread.Entry(); /*PRQA S 305*/ /*OS_WRAPPER_005*/ /*PRQA S 306*/ /*OS_WRAPPER_002*/
  }
}

/******************************************************************************/
/*!
* \brief        Initialize Os Alarms
*
* \param[in]    None
* \retval       osStatus_t: return code
*
* \pre          No execution of init is done before.
* \post         None
*
* \req
* \details      This function initialize Os alarms. Needed to reduce StartOs complexity.
*               Only periodic alarms are generated, one shot alarms are supported by SetRelAlarm.
*/
/******************************************************************************/
STATIC INLINE FUNC(osStatus_t, OS_CODE) Os_InitAlarms(void)
{
  /* Ref: group__CMSIS__RTOS__TimerMgmt.html - osTimerNew */

  /* Init local variables */
  osStatus_t RetVal = osOK;
  AlarmType AlarmID;

  /* Create all Os alarm instances */
  for (AlarmID = 0; (AlarmID < (AlarmType)OS_ALARMID_COUNT) && (RetVal == osOK); AlarmID++)
  {
    /* Call new alarm function */
    Os_OsekToCmsisMap.Alarms[AlarmID].Alarm = osTimerNew
    (
      Os_AlarmCallback,
      osTimerPeriodic,
      (void*)(Os_AlarmRefs[AlarmID]),
      Os_AlarmAttributes[AlarmID]
    ); /*PRQA S 306*/ /*OS_WRAPPER_002*/

    /* Is alarm creation faulty? */
    if (Os_OsekToCmsisMap.Alarms[AlarmID].Alarm == NULL)
    {
      /* Set error */
      RetVal = osError;
    }
  }

  return RetVal;
}

/******************************************************************************/
/*!
* \brief        Alarm action handler.
*
* \param[in]    void(param): alarm data.
* \retval       None
*
* \pre          No execution of init is done before.
* \post         None
*
* \req          
* \details      This is a callback function, which is called by the alarm 
*               management.
*/
/******************************************************************************/
STATIC FUNC(void, OS_CODE) Os_AlarmCallback(void * param)
{
  /* Init local variables */
  const Os_AlarmCfgType* AlarmCfg = (const Os_AlarmCfgType*)(param);

  /* Is this the first run of a cyclic alarm? */
  if(Os_OsekToCmsisMap.Alarms[AlarmCfg->Id].FirstRun == 1U)
  {
    /* Set first run to false */
    Os_OsekToCmsisMap.Alarms[AlarmCfg->Id].FirstRun = 0U;

    /* Stop the alarm */
    (void)osTimerStop(Os_OsekToCmsisMap.Alarms[AlarmCfg->Id].Alarm);

    /* Is alarm cyclic? */
    if(Os_OsekToCmsisMap.Alarms[AlarmCfg->Id].Cycle > 0U)
    {
      /* Restart the alarm with cycle time */
      (void)osTimerStart(Os_OsekToCmsisMap.Alarms[AlarmCfg->Id].Alarm,Os_OsekToCmsisMap.Alarms[AlarmCfg->Id].Cycle);
    }
  }

  /* Perform alarm action */
  AlarmCfg->Action(AlarmCfg);
}

/******************************************************************************/
/*!
* \brief        Initialize Os Resources
*
* \param[in]    None
* \retval       osStatus_t: return code
*
* \pre          No execution of init is done before.
* \post         None
*
* \req
* \details      This function initialize Os resources. Needed to reduce StartOs complexity
*/
/******************************************************************************/
STATIC INLINE FUNC(osStatus_t, OS_CODE) Os_InitResources(void)
{
  /* Not implemented */
  return osOK;
}

/* Helper function to map CMSIS-RTOS status to OSEK status */
/* Should return always E_OK if extended error status is disabled */
STATIC INLINE FUNC(StatusType, OS_CODE) Os_MapCmsisToOsekStatus(osStatus_t Status)
{
  StatusType RetVal = E_OK;

#if OS_ERRORCHECK_EXTENDEDSTATUS
  switch(Status)
  {
    case osOK:
      RetVal = E_OK;
      break;
    case osErrorISR:
      RetVal = E_OS_CALLEVEL;
      break;
    case osErrorResource:
      RetVal = E_OS_RESOURCE;
      break;
    case osErrorParameter:
      RetVal = E_OS_ID;
      break;
    case osErrorTimeout:
    case osErrorNoMemory:
    case osErrorSafetyClass:
    case osError:
    default:
      RetVal = E_OS_STATE;
      break;
  }
#endif

  return RetVal;
}

/* Helper function to map CMSIS-RTOS status to OSEK status */
/* Should return always E_OK if extended error status is disabled */
STATIC INLINE FUNC(StatusType, OS_CODE) Os_MapCmsisToOsekFlagError(uint32_t FlagError)
{
  StatusType RetVal = E_OK;

#if OS_ERRORCHECK_EXTENDEDSTATUS
  switch(FlagError)
  {
    case osFlagsErrorResource:
      RetVal = E_OS_RESOURCE;
      break;
    case osFlagsErrorISR:
      RetVal = E_OS_CALLEVEL;
      break;
    case osFlagsErrorParameter:
      RetVal = E_OS_ID;
      break;
    case osFlagsErrorTimeout:
    case osFlagsErrorUnknown:
      RetVal = E_OS_STATE;
      break;
    default:
      RetVal = E_OK;
      break;
  }
#endif

  return RetVal;
}

/* Helper function to map CMSIS-RTOS task state to OSEK task state */
STATIC INLINE FUNC(TaskStateType, OS_CODE) Os_MapCmsisToOsekTaskState(osThreadState_t TaskState)
{
  TaskStateType RetVal;

  switch (TaskState)
  {
    case osThreadRunning:
      RetVal = RUNNING;
      break;
    case osThreadReady:
      RetVal = READY;
      break;
    case osThreadBlocked:
      RetVal = WAITING;
      break;
    case osThreadTerminated:
    case osThreadInactive:
      RetVal = SUSPENDED;
      break;
    default:
      RetVal = INVALID_TASK;
      break;
  }
  
  return RetVal;
}