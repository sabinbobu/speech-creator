#ifndef OS_SCHEDULER_2013_01_03_H_
  #define OS_SCHEDULER_2013_01_03_H_
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
  /// \file   Os.h
  ///
  /// \brief  Generic multitasking scheduler in C.
  ///         The implementation features a round-robin function
  ///         call table based on fixed, predefined time slices.
  ///         A simple priority mechanism is implemented.
  ///
  /// \author  (ksc2rt)
  ///         mailTo:       christopher.kormanyos(at)al-lighting.com
  //-----------------------------------------------------------------------------

  // *****************************************************************************
  // includes
  // *****************************************************************************
  #include <Std_Types.h>

  // *****************************************************************************
  // types
  // *****************************************************************************
  #define AL_MAC_OS_TASK_ID
    // Generate the task enum list
    #include <OsSchedulerCfg.h>
  #undef  AL_MAC_OS_TASK_ID

  // This Operating System has an OSEK-like interface.
  typedef uint16_least              OsSchedulerEventMaskType;
  typedef OsSchedulerEventMaskType* OsSchedulerEventMaskRefType;

  // *****************************************************************************
  // function prototypes
  // *****************************************************************************
  #define AL_MAC_OS_TASK_PROTOTYPE
    // Generate the task function prototypes
    //lint -e451 Header file repeatedly included but does not have a standard include guard
    #include <OsSchedulerCfg.h>
    //lint +e451 Header file repeatedly included but does not have a standard include guard
  #undef  AL_MAC_OS_TASK_PROTOTYPE

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  void           OsSchedulerStartOs    (void);
  void           OsSchedulerStartupHook(void);
  Std_ReturnType OsSchedulerSetEvent   (OsSchedulerTaskIdType TaskIndex, OsSchedulerEventMaskType TaskEvent);
  Std_ReturnType OsSchedulerClearEvent (OsSchedulerEventMaskType TaskEvent);
  Std_ReturnType OsSchedulerGetEvent   (OsSchedulerTaskIdType TaskIndex, OsSchedulerEventMaskRefType TaskEventReference);

  void OsSchedulerDisableAllInterrupts(void);
  void OsSchedulerEnableAllInterrupts (void);

  #if defined(__cplusplus)
  }
  #endif

#endif // OS_SCHEDULER_2013_01_03_H_
