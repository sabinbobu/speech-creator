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
* \file     EcuM.c
*
* \brief    BSW EcuM wrapper template
*
* \descr    Minimal EcuM implementation
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "EcuM.h"
#include "EcuM_Internals.h"
#include "Os.h"

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/* EcuM internal module state */
STATIC VAR(EcuM_StateType, ECUM_VAR_NOINIT) EcuM_ModuleState;

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S ____________________________________*/
#define ECUM_START_SEC_CODE
#include "EcuM_MemMap.h"

/******************************************************************************/
/*!
* \brief        Initialize the ECU State Manager - init sequence I
*
* \param[in]    None
* \retval       None
*
* \pre          Hardware and basic drivers have been initialized by the bootloader.
* \post         BSW drivers are initialized and the OS is ready to be started.
*
* \req
* \details      Implements the startup phase before OS start.
*               Ref: AUTOSAR SWS_EcuM - EcuM_Init
*/
/******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_Init(void)
{
  /* Set the current state of the EcuM to STARTUP */
  EcuM_ModuleState = ECUM_STATE_STARTUP;

  /* Set the interrupts on ECUs with programmable interrupts */
  EcuM_AL_SetProgrammableInterrupts();

  /* Initialize BSW that do not use PostBuild parameters (DriverInitListZero). */
  EcuM_AL_DriverInitZero();

  /* Determine the Post-Build configuration */
  (void)EcuM_DeterminePbConfiguration();

  /* Initialize BSW that use PostBuild parameters */
  EcuM_AL_DriverInitOne();

  /* Start the OS */
  StartOS(ECUM_OS_MODE);
}

/******************************************************************************/
/*!
* \brief        Complete the ECU startup sequence - init sequence II
*
* \param[in]    None
* \retval       None
*
* \pre          EcuM_Init has been called and the OS is running.
* \post         The ECU is fully initialized and the RUN state is entered.
*
* \req
* \details      Implements the startup phase after OS start.
*               Ref: AUTOSAR SWS_EcuM - EcuM_StartupTwo
*/
/******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_StartupTwo(void)
{
  /* Initialization of the schedule Manager. */
  SchM_Init(ECUM_SCHM_CONFIG_POINTER);

  /* Initialization of the BswM. */
  /* Not implemented*/

  /* Initialize BSW that does not require RTE started */
  EcuM_AL_DriverInitTwo();

  /* Start Rte */
  (void)Rte_Start();

  /* Initialize BSW that does require RTE started */
  EcuM_AL_DriverInitThree();

  /* Set the current state of the EcuM to RUN */
  EcuM_ModuleState = ECUM_STATE_RUN;
}

#define ECUM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

/*______ L O C A L - F U N C T I O N S ______________________________________*/
