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
* \file     EcuM_Callout_Stubs.c
*
* \brief    EcuM Callout stub implementation
*
* \descr    Implementation of EcuM callout functions (AL driver callouts and
*            flexible hooks) that are called by the EcuM state machine
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "Std_Types.h"
#include "EcuM.h"
#include "EcuM_Internals.h"
#include "swc_led.h"
#include "Mcu.h"
#include "Port.h"
#include "Pwm.h"
#include "Gpt.h"
#include "Adc.h"

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/
#define PERIPHERAL_GPIO0_INDEX          (0U)
#define PERIPHERAL_GPIO1_INDEX          (1U)
#define PERIPHERAL_PWM_TIMG0_INDEX      (3U)
#define PERIPHERAL_PWM_TIMG12_INDEX     (4U)
#define PERIPHERAL_PWM_TIMGA0_INDEX     (5U)
#define PERIPHERAL_GPT_TIMG6_INDEX      (6U)
#define PERIPHERAL_PWM_TIMGA1_INDEX     (7U)
#define PERIPHERAL_PWM_TIMG9_INDEX      (8U)
#define PERIPHERAL_PWM_TIMG7_INDEX      (9U)
#define PERIPHERAL_ADC0_INDEX           (11U)
#define PERIPHERAL_ADC1_INDEX           (12U)
#define PERIPHERAL_SPI0_INDEX           (13U)
#define PERIPHERAL_PWM_TIMG14_INDEX     (18U)
/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S ____________________________________*/
#define ECUM_START_SEC_CODE
#include "EcuM_MemMap.h"

/******************************************************************************/
/*!
* \brief        Set programmable interrupts
*
* \param[in]    None
* \retval       None
*
* \pre          Hardware is initialized
* \post         Programmable interrupts are configured
*
* \req
* \details      On ECUs with programmable interrupt priorities, these priorities
*               must be set before the OS is started
*/
/******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_AL_SetProgrammableInterrupts(void)
{
}

/******************************************************************************/
/*!
* \brief        Determine PostBuild configuration
*
* \param[in]    None
* \retval       None
*
* \pre          AL drivers from DriverInitZero are initialized
* \post         PostBuild configuration is selected and available
*
* \req
* \details      In the case of Post-Build Loadable or Selectable the EcuM gets
*               the global configuration pointer via this callout.
*/
/******************************************************************************/
FUNC(EcuM_ConfigRefType, ECUM_CODE) EcuM_DeterminePbConfiguration(void)
{
  return NULL_PTR;
}

/******************************************************************************/
/*!
* \brief        AL Driver Initialization - Phase Zero
*
* \param[in]    None
* \retval       None
*
* \pre          EcuM state is STARTUP_ZERO
* \post         AL drivers are ready for NvM operations
*
* \req
* \details      This callout is invoked early in the PreOS Sequence during EcuM_Init()
*/
/******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_AL_DriverInitZero(void)
{
    Mcu_Init(&Mcu_Config);

    Mcu_InitClock(PERIPHERAL_GPIO0_INDEX);
    Mcu_InitClock(PERIPHERAL_GPIO1_INDEX);

    Mcu_InitClock(PERIPHERAL_GPT_TIMG6_INDEX);
    Mcu_InitClock(PERIPHERAL_GPT_TIMG6_INDEX);
    Mcu_InitClock(PERIPHERAL_ADC0_INDEX);
    Mcu_InitClock(PERIPHERAL_ADC1_INDEX);
    
    Mcu_InitClock(PERIPHERAL_PWM_TIMG0_INDEX);
    Mcu_InitClock(PERIPHERAL_PWM_TIMGA0_INDEX);
    Mcu_InitClock(PERIPHERAL_PWM_TIMG12_INDEX);
    //Mcu_InitClock(PERIPHERAL_PWM_TIMGA1_INDEX);
    //Mcu_InitClock(PERIPHERAL_PWM_TIMG9_INDEX);
    //Mcu_InitClock(PERIPHERAL_PWM_TIMG7_INDEX);

    Mcu_InitClock(PERIPHERAL_SPI0_INDEX);
}

/******************************************************************************/
/*!
* \brief        AL Driver Initialization - Phase One
*
* \param[in]    None
* \retval       None
*
* \pre          EcuM state is STARTUP_ONE
* \pre          NvM data has been read
* \post         AL drivers are ready for OS and application execution
*
* \req
* \details      This callout is invoked late in the PreOS Sequence during EcuM_Init()
*/
/******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_AL_DriverInitOne(void)
{
    Port_Init(&Port_Config_IO);
    Port_Init(&Port_Config_ADC);
    Port_Init(&Port_Config_PWM_ICU);
    Port_Init(&Port_Config_SPI);
    Gpt_Init(&Gpt_Config);
    Adc_Init(&AdcConfigSet);
    Pwm_Init(&Pwm_Config);

    swc_led_init();
}

/******************************************************************************/
/*!
* \brief        AL Driver Initialization - Phase Two
*
* \param[in]    None
* \retval       None
*
* \pre          EcuM state is STARTUP_TWO
* \pre          OS scheduler is running
* \post         AL drivers are fully initialized and operational
*
* \req
* \details      This callout is invoked during EcuM_StartupTwo(), prior the Rte is started
*/
/******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_AL_DriverInitTwo(void)
{
}

/******************************************************************************/
/*!
* \brief        AL Driver Initialization - Phase Three
*
* \param[in]    None
* \retval       None
*
* \pre          EcuM state is STARTUP_TWO or RUN
* \pre          AL drivers from phases 0, 1, and 2 are initialized
* \post         AL driver subsystem is fully operational
*
* \req
* \details      This callout is invoked during EcuM_StartupTwo(), after the Rte is started.
*/
/******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_AL_DriverInitThree(void)
{
}

#define ECUM_STOP_SEC_CODE
#include "EcuM_MemMap.h"
/*______ L O C A L - F U N C T I O N S _____________________________________*/

/*______ E N D _______________________________________________________________*/
