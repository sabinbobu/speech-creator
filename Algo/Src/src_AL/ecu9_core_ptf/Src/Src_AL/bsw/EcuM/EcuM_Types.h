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
* \file     EcuM_Types.h
*
* \brief    BSW EcuM type definitions
*
* \descr    Type header containing the AUTOSAR EcuM data type definitions
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

#ifndef ECUM_TYPES_H
#define ECUM_TYPES_H

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "Std_Types.h"

/*______ G L O B A L - M A C R O _____________________________________________*/
/* EcuM state types */
#define ECUM_SUBSTATE_MASK                                               (0x0Fu)
#define ECUM_STATE_STARTUP                                               (0x10u)
#define ECUM_STATE_WAKEUP                                                (0x20u)
#define ECUM_STATE_RUN                                                   (0x30u)
#define ECUM_STATE_SHUTDOWN                                              (0x40u)
#define ECUM_STATE_SLEEP                                                 (0x50u)

#define ECUM_STATE_ERROR                                                 (0xFFu)

/* EcuM reset types */
#define ECUM_RESET_MCU                                                   (0x00u)
#define ECUM_RESET_WDG                                                   (0x01u)
#define ECUM_RESET_IO                                                    (0x02u)

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/
typedef uint8 EcuM_StateType;
typedef uint8 EcuM_ResetType;

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

typedef uint32 EcuM_WakeupSourceType;
/*______ L O C A L - D A T A _________________________________________________*/

#endif /* ECUM_TYPES_H */
/*______ E N D _______________________________________________________________*/
