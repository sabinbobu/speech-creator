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
* \file     Os_Cfg.c
*
* \brief    OSEK OS configuration source file
*
* \descr    Static configuration tables used by Os_Wrapper.c.
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "Os_Internals.h"
#include "Os_Cfg.h"

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

#define OS_START_SEC_CONST
#include "Os_MemMap.h"

STATIC CONST(Os_TaskCfgType, OS_CONST) Os_TaskCfg_InitTask = 
{
  /* .Thread */
  {
    /* .Entry */ Os_Task_InitTask
  },
  /* .AutostartModes */ OSDEFAULTAPPMODE
};

STATIC CONST(Os_TaskCfgType, OS_CONST) Os_TaskCfg_BasicTask = 
{
  /* .Thread */
  {
    /* .Entry */ Os_Task_BasicTask
  },
  /* .AutostartModes */ 0U
};

STATIC CONST(Os_TaskCfgType, OS_CONST) Os_TaskCfg_ExtendedTask = 
{
  /* .Thread */
  {
    /* .Entry */ Os_Task_ExtendedTask
  },
  /* .AutostartModes */ 0U
};



STATIC CONST(Os_AlarmActivateTaskCfgType, OS_CONST) Os_AlarmCfg_BasicTask = 
{
  /* .Alarm */
  {
    /* .Action */ &Os_AlarmActionActivateTask
  },
  /* TaskID */ Os_TaskID_BasicTask
};

STATIC CONST(Os_AlarmSetEventCfgType, OS_CONST) Os_AlarmCfg_ExtendedEvent1 = 
{
  /* .Alarm */
  {
    /* .Action */ &Os_AlarmActionSetEvent
  },
  /* TaskID */ Os_TaskID_ExtendedTask,
  /* Mask   */ Os_EventID_ExtendedTask_Event1
};

STATIC CONST(Os_AlarmSetEventCfgType, OS_CONST) Os_AlarmCfg_ExtendedEvent2 = 
{
  /* .Alarm */
  {
    /* .Action */ &Os_AlarmActionSetEvent
  },
  /* TaskID */ Os_TaskID_ExtendedTask,
  /* Mask   */ Os_EventID_ExtendedTask_Event2
};

STATIC CONST(Os_AlarmUserCallbackCfgType, OS_CONST) Os_AlarmCfg_DemoCallback = 
{
  /* .Alarm */
  {
    /* .Action */ &Os_AlarmActionCallUserCallback
  },
  /* Callback */ Os_DemoCallback
};

#define OS_STOP_SEC_CONST
#include "Os_MemMap.h"

/*______ G L O B A L - D A T A _______________________________________________*/

#define OS_START_SEC_CONST
#include "Os_MemMap.h"

CONSTP2CONST(Os_AlarmCfgType, OS_CONST, OS_CONST) Os_AlarmRefs[OS_ALARMID_COUNT] =
{
  &(Os_AlarmCfg_BasicTask.Alarm),
  &(Os_AlarmCfg_ExtendedEvent1.Alarm),
  &(Os_AlarmCfg_ExtendedEvent2.Alarm),
  &(Os_AlarmCfg_DemoCallback.Alarm)
};

CONSTP2CONST(Os_TaskCfgType, OS_CONST, OS_CONST) Os_TaskRefs[OS_TASKID_COUNT] =
{
  &(Os_TaskCfg_InitTask),
  &(Os_TaskCfg_BasicTask),
  &(Os_TaskCfg_ExtendedTask),
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
