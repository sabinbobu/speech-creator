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
/// \file  SysLoad_Mac.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef SYS_LOAD_MAC_2019_12_11_H_
#define SYS_LOAD_MAC_2019_12_11_H_
//=============================================================================
//  Includes
//=============================================================================

#include <Bsw/Sys/Load/SysLoad_Cfg.h>

//=============================================================================
//  Macros
//=============================================================================

#if (SYS_LOAD_MEASUREMENT_TYPE == MEASURE_RUNNABLE)
#define SYS_LOAD_RUNNABLE
#elif(SYS_LOAD_MEASUREMENT_TYPE == MEASURE_ISR)
#define SYS_LOAD_ISR
#elif(SYS_LOAD_MEASUREMENT_TYPE == MEASURE_TASK)
#define SYS_LOAD_TASK
#elif(SYS_LOAD_MEASUREMENT_TYPE == MEASURE_STACK)
#define SYS_LOAD_STACK
#elif(SYS_LOAD_MEASUREMENT_TYPE == MEASURE_RUNNABLE_PERIOD_ONLY)
#define SYS_LOAD_RUNNABLE_PERIOD_ONLY
#define SYS_LOAD_RUNNABLE
#else
#error "The valid configuration parameters are: MEASURE_RUNNABLE, MEASURE_ISR, MEASURE_TASK!"
#endif

#define SYS_LOAD_FILTER 4200000000u
#define SYS_LOAD_MEAS_VAR(x) SysLoad_##x##_Var

#if (defined(SYS_LOAD_ISR) || defined(SYS_LOAD_TASK) || defined(SYS_LOAD_STACK) || (defined(SYS_LOAD_RUNNABLE) && !defined(SYS_LOAD_RUNNABLE_PERIOD_ONLY)))

#define SYS_LOAD_MEAS_VAR_DEC(x) tSysLoad_MeasurementResults SysLoad_##x##_Var;                                               \
                                  extern volatile uint32 tiSysLoad_ExecutionOrder_Number;                                     \
                                  static volatile TIMER tiSysLoad_##x##_PeriodSum_us = 0u;                                    \
                                  static volatile TIMER tiSysLoad_##x##_TimerStart = 0u;                                      \
                                  static volatile TIMER tiSysLoad_##x##_RunTimeDuration = 0u;                                 \
                                  static volatile TIMER tiSysLoad_##x##_RunTimeDuration_ThisCycle = 0u;                       \
                                  static volatile TIMER tiSysLoad_##x##_RunTimeDurationOverall = 0u;                          \
                                  static volatile uint32 ulCounter_##x = 0u;                                                  \
                                  static volatile uint32 tiSysLoad_ExecutedThisCycle_Counter_##x = 0u;                        \
                                  static volatile boolean boSysLoad_##x##_ExecuteOnceFlag = FALSE;

#define SYS_LOAD_MEAS_STACK_VAR_DEC(x) static volatile uint32 SysLoad_##x##_StackUsageInBytes;

#define SYS_LOAD_MEAS_STACK(x) SysLoad_##x##_StackUsageInBytes = Os_GetTaskStackUsage(x);

#define SYS_LOAD_MEAS_BEGIN(x)                                                                                                          \
                                                                                                                                        \
                                                                                                                                        \
  ulCounter_##x++;                                                                                                                      \
  tiSysLoad_ExecutedThisCycle_Counter_##x++;                                                                                            \
                                                                                                                                        \
  if (ulCounter_##x != 1u)                                                                                                              \
  {                                                                                                                                     \
   tiSysLoad_##x##_PeriodSum_us = (TIMER)(tiSysLoad_##x##_PeriodSum_us + TimerGetTimeSince(tiSysLoad_##x##_TimerStart));                \
   SYS_LOAD_MEAS_VAR(x).tiCallPeriodAverageOverall_us = tiSysLoad_##x##_PeriodSum_us / ulCounter_##x;                                   \
  }                                                                                                                                     \
                                                                                                                                        \
  if (boSysLoad_##x##_ExecuteOnceFlag == FALSE)                                                                                         \
  {                                                                                                                                     \
   SysLoad_##x##_Var.tiFirstCallTimeStamp_us = TimerGetTick();                                                                          \
   tiSysLoad_ExecutionOrder_Number++;                                                                                                   \
   SysLoad_##x##_Var.tiSysLoad_ExecutionOrder_Number = tiSysLoad_ExecutionOrder_Number;                                                 \
   boSysLoad_##x##_ExecuteOnceFlag = TRUE;                                                                                              \
  }                                                                                                                                     \
                                                                                                                                        \
  tiSysLoad_##x##_TimerStart = TimerGetTick();



#define SYS_LOAD_MEAS_END(x)                                                                                                            \
                                                                                                                                        \
  tiSysLoad_##x##_RunTimeDuration = TimerGetTimeSince(tiSysLoad_##x##_TimerStart);                                                      \
  tiSysLoad_##x##_RunTimeDuration_ThisCycle = tiSysLoad_##x##_RunTimeDuration_ThisCycle + tiSysLoad_##x##_RunTimeDuration;              \
  tiSysLoad_##x##_RunTimeDurationOverall = tiSysLoad_##x##_RunTimeDurationOverall + tiSysLoad_##x##_RunTimeDuration;                    \
  if (ulCounter_##x == 1u)                                                                                                              \
  {                                                                                                                                     \
   SYS_LOAD_MEAS_VAR(x).tiRunTimeMinOverall_us = tiSysLoad_##x##_RunTimeDuration;                                                       \
   SYS_LOAD_MEAS_VAR(x).tiFirstExecutionRunTime_us = tiSysLoad_##x##_RunTimeDuration;                                                   \
  }                                                                                                                                     \
  SYS_LOAD_MEAS_VAR(x).tiRunTimeAverageOverall_us = tiSysLoad_##x##_RunTimeDurationOverall / ulCounter_##x;                             \
  if (tiSysLoad_##x##_RunTimeDuration > SYS_LOAD_FILTER)                                                                                \
  {                                                                                                                                     \
   tiSysLoad_##x##_RunTimeDuration = SYS_LOAD_MEAS_VAR(x).tiRunTimeMaxOverall_us;                                                       \
  }                                                                                                                                     \
  SYS_LOAD_MEAS_VAR(x).tiRunTimeMaxOverall_us = UTIL_MAX(tiSysLoad_##x##_RunTimeDuration, SYS_LOAD_MEAS_VAR(x).tiRunTimeMaxOverall_us); \
  SYS_LOAD_MEAS_VAR(x).tiRunTimeMinOverall_us = UTIL_MIN(tiSysLoad_##x##_RunTimeDuration, SYS_LOAD_MEAS_VAR(x).tiRunTimeMinOverall_us);

#endif


#define SYS_LOAD_MEAS_VAR_DEC_TASKS static uint32 SysLoad_Curent_Slot_Time;                                                                            \
                                    static uint32 SysLoad_MaxSlotTime;                                                                                 \
                                    static uint32 SysLoad_Cycle_Counter;                                                                               \
                                    static uint32 SysLoad_SlotAverage;                                                                                 \
                                    static uint32 SysLoad_SlotSum;                                                                                     \
                                    static boolean SysLoad_boFirst = TRUE;                                                                             \
                                    static uint32 SysLoad_Start, SysLoad_Stop, SysLoad_Diff;                                                           \
                                    static uint32 SysLoad_TaskLoad_Sum_ThisCycle, SysLoad_TaskLoad_OverallSum;                                         \
                                    static uint32 SysLoad_TaskLoad_Average;                                                                            \
                                    static uint32 SysLoad_TaskLoad_Max;                                                                                \
                                    static uint32 SysLoad_IdleTask_Percentage;                                                                         \
                                    static uint32 SysLoad_Idle_Tasks_Missed, SysLoad_Idle_Tasks_Missed_Per_Total_Cycles;                               \
                                    static uint32 SysLoad_CPU_Load, SysLoad_CPU_Load_Average, SysLoad_CPU_Load_Sum;

#ifdef SYS_LOAD_RUNNABLE_PERIOD_ONLY

#define SYS_LOAD_MEAS_VAR_DEC(x) tSysLoad_MeasurementResults SysLoad_##x##_Var;                                               \
                                  static volatile TIMER tiSysLoad_##x##_PeriodSum_us = 0u;                                    \
                                  static volatile TIMER tiSysLoad_##x##_TimerStart = 0u;                                      \
                                  static volatile uint32 ulCounter_##x = 0u;                                                  \

#define SYS_LOAD_MEAS_BEGIN(x)                                                                                                          \
                                                                                                                                        \
                                                                                                                                        \
  ulCounter_##x++;                                                                                                                      \
                                                                                                                                        \
  if (ulCounter_##x != 1u)                                                                                                              \
  {                                                                                                                                     \
   tiSysLoad_##x##_PeriodSum_us = (TIMER)(tiSysLoad_##x##_PeriodSum_us + TimerGetTimeSince(tiSysLoad_##x##_TimerStart));                \
   SYS_LOAD_MEAS_VAR(x).tiCallPeriodAverageOverall_us = tiSysLoad_##x##_PeriodSum_us / ulCounter_##x;                                   \
  }                                                                                                                                     \
                                                                                                                                        \
  tiSysLoad_##x##_TimerStart = TimerGetTick();

#define SYS_LOAD_MEAS_END(x)

#endif


#ifdef SYS_LOAD_TASK

extern uint32 Gpt_Trusted_GetTimeElapsed(void);

#define SYS_LOAD_MEAS_TASK_CPU_LOAD SysLoad_Cycle_Counter++;                                                                                        \
if (SysLoad_boFirst == FALSE)                                                                                                                       \
{                                                                                                                                                   \
  SysLoad_Stop = Gpt_Trusted_GetTimeElapsed();                                                                                                      \
  SysLoad_Diff = SysLoad_Stop - SysLoad_Start;                                                                                                      \
  SysLoad_MaxSlotTime = UTIL_MAX(SysLoad_Diff, SysLoad_MaxSlotTime);                                                                                \
  SysLoad_SlotSum += SysLoad_Diff;                                                                                                                  \
  SysLoad_SlotAverage = SysLoad_SlotSum / SysLoad_Cycle_Counter;                                                                                    \
}                                                                                                                                                   \
SysLoad_TaskLoad_Sum_ThisCycle = 0u;                                                                                                                \
if (tiSysLoad_ExecutedThisCycle_Counter_Os_Task_UserDefined_Idle > 0u)                                                                              \
{                                                                                                                                                   \
  SysLoad_TaskLoad_Sum_ThisCycle += tiSysLoad_Os_Task_UserDefined_Idle_RunTimeDuration_ThisCycle;                                                   \
}                                                                                                                                                   \
if (tiSysLoad_ExecutedThisCycle_Counter_Os_Task_taskRTE_H > 0u)                                                                                     \
{                                                                                                                                                   \
  SysLoad_TaskLoad_Sum_ThisCycle += tiSysLoad_Os_Task_taskRTE_H_RunTimeDuration_ThisCycle;                                                          \
}                                                                                                                                                   \
if (tiSysLoad_ExecutedThisCycle_Counter_Os_Task_taskRTE_L > 0u)                                                                                     \
{                                                                                                                                                   \
  SysLoad_TaskLoad_Sum_ThisCycle += tiSysLoad_Os_Task_taskRTE_L_RunTimeDuration_ThisCycle;                                                          \
}                                                                                                                                                   \
if (tiSysLoad_ExecutedThisCycle_Counter_Os_Task_taskSchM_NonTrusted > 0u)                                                                           \
{                                                                                                                                                   \
  SysLoad_TaskLoad_Sum_ThisCycle += tiSysLoad_Os_Task_taskSchM_NonTrusted_RunTimeDuration_ThisCycle;                                                \
}                                                                                                                                                   \
if (tiSysLoad_ExecutedThisCycle_Counter_Os_Task_taskSchM_Trusted > 0u)                                                                              \
{                                                                                                                                                   \
  SysLoad_TaskLoad_Sum_ThisCycle += tiSysLoad_Os_Task_taskSchM_Trusted_RunTimeDuration_ThisCycle;                                                   \
}                                                                                                                                                   \
                                                                                                                                                    \
                                                                                                                                                    \
SysLoad_TaskLoad_OverallSum += SysLoad_TaskLoad_Sum_ThisCycle;                                                                                      \
                                                                                                                                                    \
if (tiSysLoad_ExecutedThisCycle_Counter_Os_Task_UserDefined_Idle > 0u)                                                                              \
{                                                                                                                                                   \
  SysLoad_IdleTask_Percentage = (tiSysLoad_Os_Task_UserDefined_Idle_RunTimeDuration_ThisCycle * 100) / SysLoad_TaskLoad_Sum_ThisCycle;              \
}                                                                                                                                                   \
else                                                                                                                                                \
{                                                                                                                                                   \
  SysLoad_IdleTask_Percentage = 0u;                                                                                                                 \
}                                                                                                                                                   \
                                                                                                                                                    \
SysLoad_CPU_Load = 100 - SysLoad_IdleTask_Percentage;                                                                                               \
SysLoad_CPU_Load_Sum = SysLoad_CPU_Load_Sum + SysLoad_CPU_Load;                                                                                     \
SysLoad_CPU_Load_Average = SysLoad_CPU_Load_Sum  /SysLoad_Cycle_Counter;                                                                            \
                                                                                                                                                    \
SysLoad_TaskLoad_Average = SysLoad_TaskLoad_OverallSum / SysLoad_Cycle_Counter;                                                                     \
SysLoad_TaskLoad_Max = UTIL_MAX(SysLoad_TaskLoad_Max, SysLoad_TaskLoad_Sum_ThisCycle);                                                              \
SysLoad_Idle_Tasks_Missed = SysLoad_Cycle_Counter - ulCounter_Os_Task_UserDefined_Idle;                                                             \
SysLoad_Idle_Tasks_Missed_Per_Total_Cycles = SysLoad_Cycle_Counter / ulCounter_Os_Task_UserDefined_Idle;                                            \
SysLoad_boFirst = FALSE;                                                                                                                            \
SysLoad_Start = Gpt_Trusted_GetTimeElapsed();                                                                                                       \
                                                                                                                                                    \
tiSysLoad_Os_Task_UserDefined_Idle_RunTimeDuration_ThisCycle = 0u;                                                                                  \
tiSysLoad_Os_Task_taskRTE_H_RunTimeDuration_ThisCycle = 0u;                                                                                         \
tiSysLoad_Os_Task_taskRTE_L_RunTimeDuration_ThisCycle = 0u;                                                                                         \
tiSysLoad_Os_Task_taskSchM_NonTrusted_RunTimeDuration_ThisCycle = 0u;                                                                               \
tiSysLoad_Os_Task_taskSchM_Trusted_RunTimeDuration_ThisCycle = 0u;                                                                                  \
tiSysLoad_ExecutedThisCycle_Counter_Os_Task_UserDefined_Idle = 0u;                                                                                  \
tiSysLoad_ExecutedThisCycle_Counter_Os_Task_taskRTE_H = 0u;                                                                                         \
tiSysLoad_ExecutedThisCycle_Counter_Os_Task_taskRTE_L = 0u;                                                                                         \
tiSysLoad_ExecutedThisCycle_Counter_Os_Task_taskSchM_NonTrusted = 0u;                                                                               \
tiSysLoad_ExecutedThisCycle_Counter_Os_Task_taskSchM_Trusted = 0u;

#define SYS_LOAD_TASK_MEAS_BEGIN(x)                                                                                                     \
                                                                                                                                        \
                                                                                                                                        \
  ulCounter_##x++;                                                                                                                      \
  tiSysLoad_ExecutedThisCycle_Counter_##x++;                                                                                            \
                                                                                                                                        \
  if (ulCounter_##x != 1u)                                                                                                              \
  {                                                                                                                                     \
   tiSysLoad_##x##_PeriodSum_us = (TIMER)(tiSysLoad_##x##_PeriodSum_us + (Gpt_Trusted_GetTimeElapsed() - tiSysLoad_##x##_TimerStart));  \
   SYS_LOAD_MEAS_VAR(x).tiCallPeriodAverageOverall_us = tiSysLoad_##x##_PeriodSum_us / ulCounter_##x;                                   \
  }                                                                                                                                     \
                                                                                                                                        \
  if (boSysLoad_##x##_ExecuteOnceFlag == FALSE)                                                                                         \
  {                                                                                                                                     \
   SysLoad_##x##_Var.tiFirstCallTimeStamp_us = Gpt_Trusted_GetTimeElapsed();                                                            \
   boSysLoad_##x##_ExecuteOnceFlag = TRUE;                                                                                              \
  }                                                                                                                                     \
                                                                                                                                        \
  tiSysLoad_##x##_TimerStart = Gpt_Trusted_GetTimeElapsed();



#define SYS_LOAD_TASK_MEAS_END(x)                                                                                                       \
                                                                                                                                        \
  tiSysLoad_##x##_RunTimeDuration = Gpt_Trusted_GetTimeElapsed() - tiSysLoad_##x##_TimerStart;                                          \
  tiSysLoad_##x##_RunTimeDuration_ThisCycle = tiSysLoad_##x##_RunTimeDuration_ThisCycle + tiSysLoad_##x##_RunTimeDuration;              \
  tiSysLoad_##x##_RunTimeDurationOverall = tiSysLoad_##x##_RunTimeDurationOverall + tiSysLoad_##x##_RunTimeDuration;                    \
  if (ulCounter_##x == 1u)                                                                                                              \
  {                                                                                                                                     \
   SYS_LOAD_MEAS_VAR(x).tiRunTimeMinOverall_us = tiSysLoad_##x##_RunTimeDuration;                                                       \
   SYS_LOAD_MEAS_VAR(x).tiFirstExecutionRunTime_us = tiSysLoad_##x##_RunTimeDuration;                                                   \
  }                                                                                                                                     \
  SYS_LOAD_MEAS_VAR(x).tiRunTimeAverageOverall_us = tiSysLoad_##x##_RunTimeDurationOverall / ulCounter_##x;                             \
  if (tiSysLoad_##x##_RunTimeDuration > SYS_LOAD_FILTER)                                                                                \
  {                                                                                                                                     \
   tiSysLoad_##x##_RunTimeDuration = SYS_LOAD_MEAS_VAR(x).tiRunTimeMaxOverall_us;                                                       \
  }                                                                                                                                     \
  SYS_LOAD_MEAS_VAR(x).tiRunTimeMaxOverall_us = UTIL_MAX(tiSysLoad_##x##_RunTimeDuration, SYS_LOAD_MEAS_VAR(x).tiRunTimeMaxOverall_us); \
  SYS_LOAD_MEAS_VAR(x).tiRunTimeMinOverall_us = UTIL_MIN(tiSysLoad_##x##_RunTimeDuration, SYS_LOAD_MEAS_VAR(x).tiRunTimeMinOverall_us);

#endif

#endif // SYS_LOAD_MAC_2019_12_11_H_
