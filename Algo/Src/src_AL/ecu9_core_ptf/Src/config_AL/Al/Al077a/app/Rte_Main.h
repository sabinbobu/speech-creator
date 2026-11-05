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
* \file     rte_main.h
*
* \brief    RTE main header
*
* \descr    Main RTE interface header providing application access to
*            RTE services, inter-runnable communication, and server callouts.
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

#ifndef RTE_MAIN_H
#define RTE_MAIN_H

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/
typedef void SchM_ConfigType;

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/
extern FUNC(void, RTE_CODE) SchM_Init(P2CONST(SchM_ConfigType, AUTOMATIC, RTE_CONST) ConfigPtr);
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Start(void);

#endif /* RTE_MAIN_H */
/*______ E N D _______________________________________________________________*/
