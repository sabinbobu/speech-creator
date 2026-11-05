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
#include "Dio.h"
#include "Port.h"

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

  ActivateTask(Os_TaskID_ExtendedTask);
  SetRelAlarm(Os_AlarmID_BasicTask, 1, 5);
  SetRelAlarm(Os_AlarmID_ExtendedTask_Event1, 2, 5);
  SetRelAlarm(Os_AlarmID_ExtendedTask_Event2, 4, 5);
  SetRelAlarm(Os_AlarmID_DemoCallback, 0, 10);
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
  (void)TerminateTask();
}

TASK(ExtendedTask)
{
  EventMaskType ev;

  for(;;)
  {
    WaitEvent(Os_EventID_ExtendedTask_Event1 | Os_EventID_ExtendedTask_Event2);
    GetEvent(Os_TaskID_ExtendedTask, &ev);
    ClearEvent(ev & (Os_EventID_ExtendedTask_Event1 | Os_EventID_ExtendedTask_Event2));

    if ((ev & Os_EventID_ExtendedTask_Event1) != (EventMaskType)0)
    {
      Dio_WriteChannel(DioConf_DioChannel_PA0_HSS_EN1, STD_HIGH);
    }

    if ((ev & Os_EventID_ExtendedTask_Event2) != (EventMaskType)0)
    {
      Dio_WriteChannel(DioConf_DioChannel_PA0_HSS_EN1, STD_LOW);
    }
  }
}

void Os_DemoCallback(void)
{
  (void)0u;
}

/*______ L O C A L - F U N C T I O N S _____________________________________*/

/*______ E N D _______________________________________________________________*/
