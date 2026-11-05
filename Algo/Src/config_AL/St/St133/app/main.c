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
* \file     main.c
*
* \brief    Main module
*
* \descr    This module contains user's application entry point
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "EcuM.h"
#include "Os.h"
#include "swc_led.h"

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/* Redefine ArmCLib's _platform_post_stackheap_init function to manage 
   OS kernel internally */
void _platform_post_stackheap_init (void)
{
  (void)0u;
}

/******************************************************************************/
/*!
* \brief        Project main function
*
* \param[in]    None
* \param[out]   None
* \retval       None
*
* \pre          None
* \post         None
*
* \details      Calls EcuM_Init
*/
/******************************************************************************/
int main(void)
{
  EcuM_Init();
}

/* Init task */
TASK(InitTask)
{
  EcuM_StartupTwo();
  
  (void)TerminateTask();
}
