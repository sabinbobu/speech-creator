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
* \file     Os_Wrapper_Cfg.h
*
* \brief    FuSaRTS OS configuration header
*
* \descr    Static configuration for low level FuSaRTS RTOS.
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

#ifndef OS_WRAPPER_CFG_H
#define OS_WRAPPER_CFG_H

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "Os_Cfg.h"
#include "cmsis_os2.h"

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

extern CONSTP2CONST(osTimerAttr_t, OS_CONST, OS_CONST) Os_AlarmAttributes[OS_ALARMID_COUNT];
extern CONSTP2CONST(osThreadAttr_t, OS_CONST, OS_CONST) Os_TaskAttributes[OS_TASKID_COUNT];

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/*______ L O C A L - F U N C T I O N S _______________________________________*/

#endif
/*______ E N D _______________________________________________________________*/
