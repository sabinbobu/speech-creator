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
* \file     Os.h
*
* \brief    BSW Os wrapper
*
* \descr    OS module private header file
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

#ifndef OS_INTERNALS_H
#define OS_INTERNALS_H

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "Os_Types.h"
#include "Os_Cfg.h"

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/
extern FUNC(void, OS_CODE) Os_AlarmActionSetEvent ( P2CONST(Os_AlarmCfgType, AUTOMATIC, OS_CONST) AlarmConfig);
extern FUNC(void, OS_CODE) Os_AlarmActionActivateTask ( P2CONST(Os_AlarmCfgType, AUTOMATIC, OS_CONST) AlarmConfig);
extern FUNC(void, OS_CODE) Os_AlarmActionCallUserCallback ( P2CONST(Os_AlarmCfgType, AUTOMATIC, OS_CONST) AlarmConfig);

#endif
/*______ E N D _______________________________________________________________*/

