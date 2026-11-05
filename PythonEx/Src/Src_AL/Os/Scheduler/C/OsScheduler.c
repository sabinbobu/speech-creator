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
/// \brief  Generic multitasking scheduler in C.
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
#include <Os/OsSchedulerCfg.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
#undef  AL_MAC_OS_TASK_RAM

#define AL_MAC_OS_TASK_ROM
// Generate the task ROM struct ...
//lint -e451 Header file repeatedly included but does not have a standard include guard
#include <Os/OsSchedulerCfg.h>
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
/// \func     Std_ReturnType OsSchedulerClearEvent(OsSchedulerEventMaskType ev)
///
/// \brief    Clears the value of the event for the task within
///           the function is called. The main calculation work is done
///           outside of the disable interrupt region.
/// ---------------------------------------------------------------------------
Std_ReturnType OsClearEvent(OsSchedulerEventMaskType TaskEvent)
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

  for(TaskIndex = (uint8_least) 0U; TaskIndex < (uint8_least) OsSchedulerTaskMax_ID; TaskIndex++)
  {
    OsScheduler_aTcbVariableRamPart[TaskIndex].timer = UTILTIME_TIMER_START(OsScheduler_aTcbConstRomPart[TaskIndex].offset);
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
    // PRQA S 2461 1 // Program architecture
    for(Os_ucTaskIndex = (uint8_least) 0U; Os_ucTaskIndex < (uint8_least) OsSchedulerTaskMax_ID; ++Os_ucTaskIndex)
    {
      // Check for timeout and event.
      boolean IsTaskTimeout = UTILTIME_TIMER_TIMEOUT(OsScheduler_aTcbVariableRamPart[Os_ucTaskIndex].timer);
      boolean IsTaskEvent   = (boolean) ((OsScheduler_aTcbVariableRamPart[Os_ucTaskIndex].event != (OsSchedulerEventMaskType) 0U) ? TRUE : FALSE);

      if(   (IsTaskTimeout != (boolean) FALSE)
         || (IsTaskEvent   != (boolean) FALSE))
      {
        // Call task because of a timeout, an event or both.
        OsScheduler_aTcbConstRomPart[Os_ucTaskIndex].function();

        // Increment the task's interval timer for a timeout.
        if(IsTaskTimeout != (boolean) FALSE)
        {
          OsScheduler_aTcbVariableRamPart[Os_ucTaskIndex].timer += OsScheduler_aTcbConstRomPart[Os_ucTaskIndex].cycle;
        }

        // Priority mechanism.
        break;
      }
      else
      {
        // No ready task has been found. Service the idle task.
        OS_TASK_IDLE();
      }
    }
  }
}


/// ---------------------------------------------------------------------------
/// \func     void OsSchedulerEnableAllInterrupts (void)
///
/// \brief    Enable all interrupts
///
/// ---------------------------------------------------------------------------
void OsSchedulerEnableAllInterrupts (void) { HalIrqEnableAll(); }

/// ---------------------------------------------------------------------------
/// \func     void OsSchedulerDisableAllInterrupts(void)
///
/// \brief    Disable all interrupts
///
/// ---------------------------------------------------------------------------
void OsSchedulerDisableAllInterrupts(void) { HalIrqDisableAll(); }
