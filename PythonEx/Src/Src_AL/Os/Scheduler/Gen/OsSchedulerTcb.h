#ifndef OS_SCHEDULER_TCB_2013_01_03_H_
  #define OS_SCHEDULER_TCB_2013_01_03_H_
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
  /// \file   OsTCB.h
  ///
  /// \brief  Generic multitasking scheduler in C.
  ///         This header contains the OS task control block definition.
  //-----------------------------------------------------------------------------

  // *****************************************************************************
  // includes
  // *****************************************************************************
  #include <OsScheduler.h>
  #include <Util_Time.h>

  // *****************************************************************************
  // types
  // *****************************************************************************
  typedef void(*function_type)(void);
  typedef TIMER OsSchedulerTimerType;

  typedef struct OsSchedulerTcbConstRomPart
  {
    const function_type        function;
    const function_type        initfunc;
    const OsSchedulerTimerType cycle;
    const OsSchedulerTimerType offset;
  }
  OsSchedulerTcbConstRomPart;

  typedef struct OsSchedulerTcbVariableRamPart
  {
    OsSchedulerTimerType     timer;
    OsSchedulerEventMaskType event;
  }
  OsSchedulerTcbVariableRamPart;

#endif // OS_SCHEDULER_TCB_2013_01_03_H_
