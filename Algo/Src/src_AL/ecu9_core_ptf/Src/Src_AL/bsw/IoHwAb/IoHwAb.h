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
* \file     IoHwAb.h
*
* \brief    BSW IoHwAb
*
* \descr    Header for IoHwAb module.
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

#ifndef IOHWAB_H
#define IOHWAB_H

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "IoHwAb_Types.h"
#include "IoHwAb_Cfg.h"

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/
extern FUNC(void, IOHWAB_CODE) IoHwAb_Init
(
  P2CONST(IoHwAb_ConfigType, AUTOMATIC, IOHWAB_APPL_DATA) ConfigPtr
);
extern FUNC(void, IOHWAB_CODE) IoHwAb_MainFunction(void);

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/*______ L O C A L - F U N C T I O N S _______________________________________*/

#endif
/*______ E N D _______________________________________________________________*/
