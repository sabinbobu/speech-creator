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
* \file     rte.c
*
* \brief    Application RTE (Runtime Environment) module
*
* \descr    Stub for Autosar RTE. Placeholder containing definitions required by
*           other modules.
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "Std_Types.h"
#include "Os.h"
#include "Com.h"
#include "Port.h"
#include "swc_fee_test.h"
#include "swc_nvm_tst.h"
#include "swc_sbc_demo.h"
#include "swc_can_demo.h"
#include "IoHwAb.h"
#include "Fee.h"
#include "SchM_NvM.h"

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S ____________________________________*/

/******************************************************************************/
/*!
* \brief        Initialize the Scheduler Manager
*
* \param[in]    ConfigPtr  Pointer to SchM configuration structure
* \retval       None
*
* \pre          EcuM_StartupTwo has been called
* \post         SchM is initialized and schedulers are ready
*
* \req
* \details      Initialize all schedulers and timing sources.
*               Ref: AUTOSAR SWS_SchM - SchM_Init
*/
/******************************************************************************/
FUNC(void, RTE_CODE) SchM_Init(P2CONST(void, AUTOMATIC, RTE_CONST) ConfigPtr)
{
  (void)(ConfigPtr);

  SetRelAlarm(Os_AlarmID_BasicTask, 1, 5);
}

/******************************************************************************/
/*!
* \brief        Start the RTE
*
* \param[in]    None
* \retval       E_OK if successful, E_NOT_OK otherwise
*
* \pre          SchM_Init has been called
* \post         RTE is running and communication is enabled
*
* \req
* \details      Start the RTE (Runtime Environment) for inter-runnable
*               communication and service interfaces.
*               Ref: AUTOSAR SWS_RTE - Rte_Start
*/
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Start(void)
{
  Std_ReturnType RetVal = E_OK;
  return RetVal;
}

TASK(BasicTask)
{
  IoHwAb_MainFunction();
  Fee_MainFunction();
  NvM_MainFunction();
  Com_MainFunctionTx();
  swc_sbc_demo_MainFunction();
  swc_can_demo_MainFunction();
  
  //swc_fee_test_runnable();
  //swc_spi_test_runnable();
  //swc_pwm_test_runnable();
  //swc_adc_test_runnable();
  //swc_icu_test_runnable();
  //swc_fee_test_runnable();
  //swc_nvm_tst_runnable();
  (void)TerminateTask();
}

TASK(ExtendedTask)
{
  (void)TerminateTask();
}

void Os_DemoCallback(void)
{
}

/*______ L O C A L - F U N C T I O N S _____________________________________*/

/*______ E N D _______________________________________________________________*/
