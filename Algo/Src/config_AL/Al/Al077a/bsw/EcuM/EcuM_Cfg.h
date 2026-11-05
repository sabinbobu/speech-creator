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
* \file     EcuM_Cfg.h
*
* \brief    EcuM configuration header
*
* \descr    Configuration definitions for the EcuM module including:
*            - Number of sleep modes and wakeup sources
*            - User identifiers and run/post-run counters
*            - Shutdown sequence timing
*            - Application hooks and callout configuration
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

#ifndef ECUM_CFG_H
#define ECUM_CFG_H

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "Std_Types.h"
#include "Os.h"
#include "Rte_Main.h"

/*______ G L O B A L - M A C R O _____________________________________________*/
#define ECUM_OS_MODE                                            OSDEFAULTAPPMODE

#define ECUM_SCHM_CONFIG_POINTER                                        NULL_PTR

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/
typedef void EcuM_ConfigType;

typedef P2CONST(EcuM_ConfigType, AUTOMATIC, ECUM_CONST) EcuM_ConfigRefType;

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

#endif /* ECUM_CFG_H */
/*______ E N D _______________________________________________________________*/
