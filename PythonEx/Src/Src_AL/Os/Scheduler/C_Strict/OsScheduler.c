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
/// \file   Os.c
///
/// \brief  Generic multitasking scheduler (strict) in C.
///
/// \author  (ksc2rt)
///         mailTo:       christopher.kormanyos(at)al-lighting.com
//-----------------------------------------------------------------------------

// *****************************************************************************
// includes
// *****************************************************************************
#include <Std_Types.h>
#include <Irq/HalIrq.h>
#include <OsScheduler.h>
#include <OsSchedulerTcb.h>
#include <Sys/Idle/SysIdle.h>

// *****************************************************************************
// types
// *****************************************************************************


// *****************************************************************************
// global and static variables
// *****************************************************************************

#define AL_MAC_OS_TASK_RAM
// Generate the task RAM struct ...
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <OsSchedulerCfg.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
#undef  AL_MAC_OS_TASK_RAM

#define AL_MAC_OS_TASK_ROM
// Generate the task ROM struct ...
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <OsSchedulerCfg.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
#undef  AL_MAC_OS_TASK_ROM

static uint8_least Os_ucTaskIndex;

// *****************************************************************************
// macros
// *****************************************************************************


// *****************************************************************************
// functions
// *****************************************************************************
/// ---------------------------------------------------------------------------
/// \func     Std_ReturnType OsSchedulerSetEvent(OsSchedulerTaskIdType id, OsSchedulerEventMaskType ev)
///
/// \brief    Sets the value of the event for the task with
///              the task ID tID.
/// ---------------------------------------------------------------------------
Std_ReturnType OsSchedulerSetEvent(OsSchedulerTaskIdType TaskIndex, OsSchedulerEventMaskType TaskEvent)
{
  Std_ReturnType tyStatusResult;

  if(TaskIndex < OsSchedulerTaskMax_ID)
  {
    HalIrqDisableAll();
    OsScheduler_aTcbVariableRamPart[(uint8_least) TaskIndex].event |= TaskEvent;
    HalIrqEnableAll();

    tyStatusResult = E_OK;
  }
  else
  {
    tyStatusResult = E_NOT_OK;
  }

  return tyStatusResult;
}

/// ---------------------------------------------------------------------------
/// \func     Std_ReturnType OsSchedulerClearEvent(OsEventMaskType ev)
///
/// \brief    Clears the value of the event for the task within
///           the function is called. The main calculation work is done
///           outside of the disable interrupt region.
/// ---------------------------------------------------------------------------
Std_ReturnType OsSchedulerClearEvent(OsSchedulerEventMaskType TaskEvent)
{
  Std_ReturnType tyStatusResult;

  if(Os_ucTaskIndex < (uint8_least) OsSchedulerTaskMax_ID)
  {
    OsSchedulerEventMaskType MyClearMask = (OsSchedulerEventMaskType) ~TaskEvent;

    HalIrqDisableAll();
    OsScheduler_aTcbVariableRamPart[Os_ucTaskIndex].event &= MyClearMask;
    HalIrqEnableAll();

    tyStatusResult = E_OK;
  }
  else
  {
    tyStatusResult = E_NOT_OK;
  }

  return tyStatusResult;
}

/// ---------------------------------------------------------------------------
/// \func     Std_ReturnType OsSchedulerGetEvent(OsSchedulerTaskIdType id, OsSchedulerEventMaskRefType ev)
///
/// \brief    Fetches the value of the event for the task with
///           the task ID id.
///
/// ---------------------------------------------------------------------------
Std_ReturnType OsSchedulerGetEvent(OsSchedulerTaskIdType TaskIndex, OsSchedulerEventMaskRefType TaskEventReference)
{
  Std_ReturnType tyStatusResult;

  if(TaskIndex < OsSchedulerTaskMax_ID)
  {
    *TaskEventReference = OsScheduler_aTcbVariableRamPart[(uint8_least) TaskIndex].event;

    tyStatusResult = E_OK;
  }
  else
  {
    *TaskEventReference = (OsSchedulerEventMaskType) 0U;

    tyStatusResult = E_NOT_OK;
  }

  return tyStatusResult;
}

/// ---------------------------------------------------------------------------
/// \func     static void OsSchedulerTaskInit(void)
///
/// \brief    Call the init-function of each task
///
/// ---------------------------------------------------------------------------
static void OsSchedulerTaskInit(void)
{
  uint8_least TaskIndex;

  for(TaskIndex = (uint8_least) 0U; TaskIndex < (uint8_least) OsSchedulerTaskMax_ID; TaskIndex++)
  {
    OsScheduler_aTcbConstRomPart[TaskIndex].initfunc();
  }
}

/// ---------------------------------------------------------------------------
/// \func     static void OsSchedulerTaskSync(void)
///
/// \brief    Synchronize the task start of execution.
///           Adjust the first call time for each task such that this time is equal
///           to the current value of the tick.
///           This ensures that the first call time of each task will take place
///           according to the initialized value of the start offset.
/// ---------------------------------------------------------------------------
static void OsSchedulerTaskSync(void)
{
  uint8_least TaskIndex;

  HalIrqDisableAll();

  const OsSchedulerTimerType tySynchronizationTimeNow = (OsSchedulerTimerType) UTILTIME_TIMER_START(0U);

  for(TaskIndex = (uint8_least) 0U; TaskIndex < (uint8_least) OsSchedulerTaskMax_ID; TaskIndex++)
  {
    OsScheduler_aTcbVariableRamPart[TaskIndex].timer =   tySynchronizationTimeNow
                                                       + OsScheduler_aTcbConstRomPart[TaskIndex].offset;
  }

  HalIrqEnableAll();
}

/// ---------------------------------------------------------------------------
/// \func     void OsSchedulerStartOs(void)
///
/// \brief    Start the function table multitasking and run it forever
///
/// ---------------------------------------------------------------------------
void OsSchedulerStartOs(void)
{
  OsSchedulerStartupHook();

  OsSchedulerTaskInit();
  OsSchedulerTaskSync();

  // Run the the multitasking scheduler forever.
  for(;;)
  {
    boolean boAnyTaskIsReady = FALSE;

    // Get a snapshot of a single time-point to be used for all
    // task-timeout checks in the inner loop of the scheduler.
    const OsSchedulerTimerType tyTimeoutCheckTimeNow = (OsSchedulerTimerType) UTILTIME_TIMER_START(0U);

    // PRQA S 2461 1 // Program architecture
    for(Os_ucTaskIndex = (uint8_least) 0U; (boAnyTaskIsReady == (boolean) FALSE) && (Os_ucTaskIndex < (uint8_least) OsSchedulerTaskMax_ID); ++Os_ucTaskIndex)
    {
      // Check for a task event.
      const boolean boTaskHasEvent = (boolean) ((OsScheduler_aTcbVariableRamPart[Os_ucTaskIndex].event != (OsSchedulerEventMaskType) 0U) ? TRUE : FALSE);

      // Check for a task timeout.
      const boolean boTaskCycleTimeIsZero =
        (boolean) ((OsScheduler_aTcbConstRomPart[Os_ucTaskIndex].cycle == (OsSchedulerTimerType) 0U)
                    ? (boolean) TRUE
                    : (boolean) FALSE);

      const boolean boTaskHasTimeout =
        (boolean) ((boTaskCycleTimeIsZero != (boolean) FALSE)
                      ? (boolean) FALSE
                      : UTILTIME_TIMER_TIMEOUT_OF_CUSTOM_TICK(OsScheduler_aTcbVariableRamPart[Os_ucTaskIndex].timer,
                                                              tyTimeoutCheckTimeNow));

      // Task can be either cyclic, or event-driven, or a combination of both.
      const boolean boHasEventOrTimeout =
        (boolean) ((   (boTaskHasEvent   != (boolean) FALSE)
                    || (boTaskHasTimeout != (boolean) FALSE)) ? (boolean) TRUE : (boolean) FALSE);

      if(boHasEventOrTimeout != (boolean) FALSE)
      {
        // Call task because of a timeout, an event or both.
        OsScheduler_aTcbConstRomPart[Os_ucTaskIndex].function();

        if(boTaskHasTimeout != (boolean) FALSE)
        {
          OsScheduler_aTcbVariableRamPart[Os_ucTaskIndex].timer += OsScheduler_aTcbConstRomPart[Os_ucTaskIndex].cycle;
        }

        // Priority mechanism.
        boAnyTaskIsReady = (boolean) TRUE;
      }
    }

    if(boAnyTaskIsReady == (boolean) FALSE)
    {
      // No ready task has been found.
      // Service the idle task.
      OS_TASK_IDLE();
    }
  }
}


/// ---------------------------------------------------------------------------
/// \func     void OsEnableAllInterrupts (void)
///
/// \brief    Enable all interrupts
///
/// ---------------------------------------------------------------------------
void OsSchedulerEnableAllInterrupts (void) { HalIrqEnableAll(); }

/// ---------------------------------------------------------------------------
/// \func     void OsDisableAllInterrupts(void)
///
/// \brief    Disable all interrupts
///
/// ---------------------------------------------------------------------------
void OsSchedulerDisableAllInterrupts(void) { HalIrqDisableAll(); }
