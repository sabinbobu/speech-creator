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
* \descr    EcuM private header file
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

#ifndef ECUM_INTERNALS_H
#define ECUM_INTERNALS_H

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/
#define ECUM_START_SEC_CODE
#include "EcuM_MemMap.h"

extern FUNC(void, ECUM_CODE) EcuM_AL_SetProgrammableInterrupts(void);
extern FUNC(void, ECUM_CODE) EcuM_AL_DriverInitZero(void);
extern FUNC(EcuM_ConfigRefType, ECUM_CODE) EcuM_DeterminePbConfiguration(void);
extern FUNC(void, ECUM_CODE) EcuM_AL_DriverInitOne(void);
extern FUNC(void, ECUM_CODE) EcuM_AL_DriverInitTwo(void);
extern FUNC(void, ECUM_CODE) EcuM_AL_DriverInitThree(void);

#define ECUM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#endif /* ECUM_INTERNALS_H */
/*______ E N D _______________________________________________________________*/
