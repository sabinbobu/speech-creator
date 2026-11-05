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
* \file     Os_Cfg.h
*
* \brief    OSEK OS configuration header
*
* \descr    Static configuration tables used by Os_Wrapper.c.
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

#ifndef OS_CFG_H
#define OS_CFG_H

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "Os_Types.h"

/*______ G L O B A L - M A C R O _____________________________________________*/
#define OS_ERRORCHECK_EXTENDEDSTATUS                                    (STD_ON)

#define OS_SAFETYCLASS_KERNELPROTECT                                ((uint32)4U)

enum
{
  Os_TaskID_InitTask = 0U,
  Os_TaskID_BasicTask,
  Os_TaskID_ExtendedTask,
  OS_TASKID_COUNT
};

enum
{
  Os_AlarmID_BasicTask = 0U,
  Os_AlarmID_ExtendedTask_Event1,
  Os_AlarmID_ExtendedTask_Event2,
  Os_AlarmID_DemoCallback,
  OS_ALARMID_COUNT
};

#define Os_EventID_ExtendedTask_Event1                        ((EventMaskType)0x01U)
#define Os_EventID_ExtendedTask_Event2                        ((EventMaskType)0x02U)


/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef FUNC(void, OS_CODE) (*Os_TaskEntryType)(void);

typedef struct
{
  Os_TaskEntryType Entry;
} Os_ThreadCfgType;

typedef struct
{
  Os_ThreadCfgType Thread;
  AppModeType AutostartModes;
} Os_TaskCfgType;


struct Os_AlarmCfgType_Tag;
typedef struct Os_AlarmCfgType_Tag Os_AlarmCfgType;

typedef FUNC(void, OS_CODE) (*Os_AlarmActionType)
(
  P2CONST(Os_AlarmCfgType, AUTOMATIC, OS_CONST) AlarmConfig
);

typedef FUNC(void, OS_CODE) (*Os_AlarmUserCallbackType)(void);

struct Os_AlarmCfgType_Tag
{
  Os_AlarmActionType Action;
};

typedef struct
{
  Os_AlarmCfgType Alarm;
  TaskType TaskID;
  EventMaskType Mask;
} Os_AlarmSetEventCfgType;

typedef struct
{
  Os_AlarmCfgType Alarm;
  TaskType TaskID;
} Os_AlarmActivateTaskCfgType;

typedef struct
{
  Os_AlarmCfgType Alarm;
  Os_AlarmUserCallbackType Callback;
} Os_AlarmUserCallbackCfgType;

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

extern CONSTP2CONST(Os_TaskCfgType, OS_CONST, OS_CONST) Os_TaskRefs[OS_TASKID_COUNT];
extern CONSTP2CONST(Os_AlarmCfgType, OS_CONST, OS_CONST) Os_AlarmRefs[OS_ALARMID_COUNT];

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/
extern FUNC(void, OS_CODE) Os_Task_InitTask(void);
extern FUNC(void, OS_CODE) Os_Task_BasicTask(void);
extern FUNC(void, OS_CODE) Os_Task_ExtendedTask(void);

extern FUNC(void, OS_CODE) Os_DemoCallback(void);

#endif
/*______ E N D _______________________________________________________________*/
