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
* \descr    Application RTE adapter for the IMU, SBC demo, and task schedule.
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "Std_Types.h"
#include "Os.h"
#include "Port.h"
#include "swc_sbc_demo.h"
#include "swc_imu.h"
#include "Rte_Imu.h"
#include "CddAsm330lhh.h"
#include "Can.h"
#include "Can_Cfg.h"
#include "Com.h"
#include "Com_Cfg.h"
#include "IoHwAb.h"
#include "Fee.h"
#include "SchM_NvM.h"

volatile Std_ReturnType Rte_ImuInitResult = E_NOT_OK;

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
  Std_ReturnType RetVal;

  swc_imu_init();
  RetVal = CddAsm330lhh_Init(&CddAsm330lhh_Config_Default);
  Rte_ImuInitResult = E_NOT_OK;
  return RetVal;
}

Std_ReturnType Rte_Read_ImuSensor_Sample(Rte_ImuSampleType* SamplePtr)
{
  CddAsm330lhh_ScaledDataType SensorData;

  if (SamplePtr == NULL_PTR)
  {
    return E_NOT_OK;
  }

  if (CddAsm330lhh_GetLatestSample(&SensorData) != E_OK)
  {
    return E_NOT_OK;
  }

  SamplePtr->AccelX_mg = SensorData.Ax_mg;
  SamplePtr->AccelY_mg = SensorData.Ay_mg;
  SamplePtr->AccelZ_mg = SensorData.Az_mg;
  SamplePtr->GyroX_mdps = SensorData.Gx_mdps;
  SamplePtr->GyroY_mdps = SensorData.Gy_mdps;
  SamplePtr->GyroZ_mdps = SensorData.Gz_mdps;
  SamplePtr->SamplePeriodMs = 10u;
  return E_OK;
}

Std_ReturnType Rte_Call_ImuSensor_StartRead(void)
{
  return CddAsm330lhh_StartRead();
}

Std_ReturnType Rte_Write_ImuAngles_Values(const Rte_ImuAnglesType* AnglesPtr)
{
  if (AnglesPtr == NULL_PTR)
  {
    return E_NOT_OK;
  }

  if ((Com_WriteSignal(COM_SIGNAL_ID_ROLL_ANGLE,
                       (uint32)(uint16)AnglesPtr->Roll_cdeg, 0u) != COM_STATUS_OK) ||
      (Com_WriteSignal(COM_SIGNAL_ID_PITCH_ANGLE,
                       (uint32)(uint16)AnglesPtr->Pitch_cdeg, 0u) != COM_STATUS_OK) ||
      (Com_WriteSignal(COM_SIGNAL_ID_YAW_ANGLE,
                       (uint32)(uint16)AnglesPtr->Yaw_cdeg, 0u) != COM_STATUS_OK))
  {
    return E_NOT_OK;
  }
  return E_OK;
}

TASK(BasicTask)
{
  IoHwAb_MainFunction();
  Fee_MainFunction();
  NvM_MainFunction();
  swc_sbc_demo_MainFunction();
  CddAsm330lhh_MainFunction();
  if (CddAsm330lhh_GetInitStatus() == CDDASM330LHH_INIT_READY)
  {
    Rte_ImuInitResult = E_OK;
  }
  else if (CddAsm330lhh_GetInitStatus() == CDDASM330LHH_INIT_FAILED)
  {
    Rte_ImuInitResult = E_NOT_OK;
  }
  swc_imu_MainFunction();
  Com_MainFunctionTx();
#if (CAN_RX_POLLING == STD_ON)
  Can_MainFunction_Read();
#endif
#if (CAN_TX_POLLING == STD_ON)
  Can_MainFunction_Write();
#endif
  
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
