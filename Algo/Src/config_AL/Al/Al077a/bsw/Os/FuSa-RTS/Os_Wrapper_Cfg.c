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
* \file     Os_Wrapper_Cfg.c
*
* \brief    FuSaRTS OS configuration source file
*
* \descr    Static configuration for low level FuSaRTS RTOS.
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "Os_Wrapper_Cfg.h"
#include "Os_Cfg.h"
#include "rtx_os.h"
#include "cmsis_compiler.h"

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

#define OS_START_SEC_CONST
#include "Os_MemMap.h"

/* Define objects that are statically allocated for the timer */
__attribute__((section(".bss.os.timer.cb")))
STATIC CONST(osRtxTimer_t, OS_CONST) Os_Alarm_BasicTask_tcb;

/* Define the attributes used for timer creation */
STATIC CONST(osTimerAttr_t, OS_CONST) Os_Alarm_BasicTask_attr = 
{
  "BasicTask",
  0,
  (void*)&Os_Alarm_BasicTask_tcb,
  sizeof(Os_Alarm_BasicTask_tcb)
};

/* Define objects that are statically allocated for the timer */
__attribute__((section(".bss.os.timer.cb")))
STATIC CONST(osRtxTimer_t, OS_CONST) Os_Alarm_ExtendedEvent1_tcb;

/* Define the attributes used for timer creation */
STATIC CONST(osTimerAttr_t, OS_CONST) Os_Alarm_ExtendedEvent1_attr = 
{
  "ExtendedEvent1",
  0,
  (void*)&Os_Alarm_ExtendedEvent1_tcb,
  sizeof(Os_Alarm_ExtendedEvent1_tcb)
};

/* Define objects that are statically allocated for the timer */
__attribute__((section(".bss.os.timer.cb")))
STATIC CONST(osRtxTimer_t, OS_CONST) Os_Alarm_ExtendedEvent2_tcb;

/* Define the attributes used for timer creation */
STATIC CONST(osTimerAttr_t, OS_CONST) Os_Alarm_ExtendedEvent2_attr = 
{
  "ExtendedEvent2",
  0,
  (void*)&Os_Alarm_ExtendedEvent2_tcb,
  sizeof(Os_Alarm_ExtendedEvent2_tcb)
};

/* Define objects that are statically allocated for the timer */
__attribute__((section(".bss.os.timer.cb")))
STATIC CONST(osRtxTimer_t, OS_CONST) Os_Alarm_DemoCallback_tcb;

/* Define the attributes used for timer creation */
STATIC CONST(osTimerAttr_t, OS_CONST) Os_Alarm_DemoCallback_attr = 
{
  "DemoCallback",
  0,
  (void*)&Os_Alarm_DemoCallback_tcb,
  sizeof(Os_Alarm_DemoCallback_tcb)
};



/* Define objects that are statically allocated for the thread */
__attribute__((section(".bss.os.thread.cb")))
STATIC CONST(osRtxThread_t, OS_CONST) Os_Task_InitTask_tcb;

/* Reserve memory area for the thread's stacks */
STATIC uint64_t Os_Task_InitTask_stk[64];

/* Define the attributes used for thread creation */
STATIC CONST(osThreadAttr_t, OS_CONST)  Os_Task_InitTask_attr = 
{
  "InitTask",
  osThreadUnprivileged  |
  osThreadDetached,
  (void*)&Os_Task_InitTask_tcb,
  sizeof(Os_Task_InitTask_tcb),
  (void*)&Os_Task_InitTask_stk[0],
  sizeof(Os_Task_InitTask_stk),
  osPriorityNormal,
  0,
  0
};

/* Define objects that are statically allocated for the thread */
__attribute__((section(".bss.os.thread.cb")))
STATIC CONST(osRtxThread_t, OS_CONST) Os_Task_BasicTask_tcb;

/* Reserve memory area for the thread's stacks */
STATIC uint64_t Os_Task_BasicTask_stk[64];

/* Define the attributes used for thread creation */
STATIC CONST(osThreadAttr_t, OS_CONST)  Os_Task_BasicTask_attr = 
{
  "BasicTask",
  osThreadUnprivileged  |
  osThreadDetached,
  (void*)&Os_Task_BasicTask_tcb,
  sizeof(Os_Task_BasicTask_tcb),
  (void*)&Os_Task_BasicTask_stk[0],
  sizeof(Os_Task_BasicTask_stk),
  osPriorityNormal,
  0,
  0
};

/* Define objects that are statically allocated for the thread */
__attribute__((section(".bss.os.thread.cb")))
STATIC CONST(osRtxThread_t, OS_CONST) Os_Task_ExtendedTask_tcb;

/* Reserve memory area for the thread's stacks */
STATIC uint64_t Os_Task_ExtendedTask_stk[64];

/* Define the attributes used for thread creation */
STATIC CONST(osThreadAttr_t, OS_CONST)  Os_Task_ExtendedTask_attr = 
{
  "ExtendedTask",
  osThreadUnprivileged  |
  osThreadDetached,
  (void*)&Os_Task_ExtendedTask_tcb,
  sizeof(Os_Task_ExtendedTask_tcb),
  (void*)&Os_Task_ExtendedTask_stk[0],
  sizeof(Os_Task_ExtendedTask_stk),
  osPriorityNormal,
  0,
  0
};

#define OS_STOP_SEC_CONST
#include "Os_MemMap.h"

/*______ G L O B A L - D A T A _______________________________________________*/

#define OS_START_SEC_CONST
#include "Os_MemMap.h"

/* Array of timers' FuSa RTX attributes */
CONSTP2CONST(osTimerAttr_t, OS_CONST, OS_CONST) Os_AlarmAttributes[OS_ALARMID_COUNT] = 
{
  &Os_Alarm_BasicTask_attr,
  &Os_Alarm_ExtendedEvent1_attr,
  &Os_Alarm_ExtendedEvent2_attr,
  &Os_Alarm_DemoCallback_attr,
};

/* Array of threads' FuSa RTX attributes */
CONSTP2CONST(osThreadAttr_t, OS_CONST, OS_CONST) Os_TaskAttributes[OS_TASKID_COUNT] = 
{
  &Os_Task_InitTask_attr,
  &Os_Task_BasicTask_attr,
  &Os_Task_ExtendedTask_attr,
};

#define OS_STOP_SEC_CONST
#include "Os_MemMap.h"

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/
#define OS_START_SEC_CODE
#include "Os_MemMap.h"

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

/*______ L O C A L - F U N C T I O N S _______________________________________*/

/*______ E N D _______________________________________________________________*/
