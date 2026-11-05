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
* \file     Os_MemMap.h
*
* \brief    OSEK OS memory mapping
*
* \descr    Memory mapping definitions for OSEK wrapper mapped to FuSaRTS/CMSIS-RTOS2.
*           This file handles linker section allocation for code and data.
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

#ifndef OS_MEMMAP_H
#define OS_MEMMAP_H

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - M A C R O _____________________________________________*/

#ifdef OS_START_SEC_CODE
  #undef OS_START_SEC_CODE
#endif

#ifdef OS_STOP_SEC_CODE
  #undef OS_STOP_SEC_CODE
#endif

#ifdef OS_START_SEC_VAR_NOINIT
  #undef OS_START_SEC_VAR_NOINIT
#endif

#ifdef OS_STOP_SEC_VAR_NOINIT
  #undef OS_STOP_SEC_VAR_NOINIT
#endif

#ifdef OS_START_SEC_VAR_INIT
  #undef OS_START_SEC_VAR_INIT
#endif

#ifdef OS_STOP_SEC_VAR_INIT
  #undef OS_STOP_SEC_VAR_INIT
#endif

#ifdef OS_START_SEC_CONST
  #undef OS_START_SEC_CONST
#endif

#ifdef OS_STOP_SEC_CONST
  #undef OS_STOP_SEC_CONST
#endif

#ifdef OS_START_SEC_CONFIG_DATA
  #undef OS_START_SEC_CONFIG_DATA
#endif

#ifdef OS_STOP_SEC_CONFIG_DATA
  #undef OS_STOP_SEC_CONFIG_DATA
#endif

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

#endif /* OS_MEMMAP_H */
