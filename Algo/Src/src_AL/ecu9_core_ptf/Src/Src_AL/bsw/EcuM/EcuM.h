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
* \file     EcuM.h
*
* \brief    BSW EcuM wrapper header
*
* \descr    Ecum header file
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

#ifndef ECUM_H
#define ECUM_H

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "EcuM_Types.h"
#include "EcuM_Cfg.h"

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/
#define ECUM_START_SEC_CODE
#include "EcuM_MemMap.h"

extern FUNC(void, ECUM_CODE) EcuM_Init(void);
extern FUNC(void, ECUM_CODE) EcuM_StartupTwo(void);

#define ECUM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#endif /* ECUM_H */
