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
#include <assert.h>
#include "EcuM.h"
#include "EcuM_Internals.h"
#include "Det.h"
#include "Dem.h"
#include "swc_led.h"
#include "swc_adc_test.h"
#include "swc_gpt_test.h"
#include "swc_icu_test.h"
#include "swc_pwm_test.h"
#include "swc_spi_test.h"
#include "swc_fee_test.h"
#include "swc_nvm_tst.h"
#include "Mcu.h"
#include "Port.h"
#include "Pwm.h"
#include "Gpt.h"
#include "Adc.h"
#include "Icu.h"
#include "Fls.h"
#include "Fee.h"
#include "IoHwAb.h"
#include "NvM.h"
#include "EcuM_Interrupts.h"


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
#define PERIPHERAL_PWM_TIMG14_INDEX     (16U)
#define PERIPHERAL_PWM_TIMG8_INDEX      (17U)
#define PERIPHERAL_FLASHCTL_INDEX       (18U)
/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/
static const Mcu_ClockType clockSettings[] =
{
    PERIPHERAL_GPIO0_INDEX,
    PERIPHERAL_GPIO1_INDEX,
    PERIPHERAL_GPT_TIMG6_INDEX,
    PERIPHERAL_ADC0_INDEX,
    PERIPHERAL_ADC1_INDEX,
    PERIPHERAL_PWM_TIMG0_INDEX,
    PERIPHERAL_PWM_TIMGA0_INDEX,
    PERIPHERAL_PWM_TIMG12_INDEX,
    PERIPHERAL_PWM_TIMG14_INDEX,
    PERIPHERAL_PWM_TIMG8_INDEX,
    PERIPHERAL_SPI0_INDEX,
    PERIPHERAL_FLASHCTL_INDEX
};
uint8 clockIndex;
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

    /* Init clock peripheral */
    for (clockIndex = 0U; clockIndex < (sizeof(clockSettings) / sizeof(clockSettings[0])); clockIndex++)
    {
        Mcu_InitClock(clockSettings[clockIndex]);
    }
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
    Icu_Init(&Icu_Config);
    Fee_Init(NULL_PTR);
    Fls_Init(&Fls_Config);
    NvM_Init(NULL_PTR);
    IoHwAb_Init(NULL_PTR);
    EcuM_Interrupts_Init();
    //swc_led_init();
    //swc_spi_test_init();
    //swc_pwm_test_init();
    //swc_adc_test_init();
    //swc_icu_test_init();
    //swc_fee_test_init();
    //swc_nvm_tst_init();
    //swc_gpt_test_init();
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

void EcuM_CheckWakeup(EcuM_WakeupSourceType wakeupSource)
{
    (void)wakeupSource;
}

void EcuM_SetWakeupEvent(EcuM_WakeupSourceType sources)
{
    (void)sources;
}

Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId,
                               uint8 ErrorId)
{
    (void)ModuleId;
    (void)InstanceId;
    (void)ApiId;
    (void)ErrorId;
    return E_OK;
}

Std_ReturnType Det_ReportRuntimeError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId,
                                      uint8 ErrorId)
{
    (void)ModuleId;
    (void)InstanceId;
    (void)ApiId;
    (void)ErrorId;
    return E_OK;
}

Std_ReturnType Det_ReportTransientFault(uint16 ModuleId, uint8 InstanceId, uint8 ApiId,
                                        uint8 ErrorId)
{
    (void)ModuleId;
    (void)InstanceId;
    (void)ApiId;
    (void)ErrorId;
    return E_OK;
}

void Dem_ReportErrorStatus(Dem_EventIdType eventId, Dem_EventStatusType eventStatus)
{
    (void)eventId;
    if (eventStatus == DEM_EVENT_STATUS_FAILED)
    {
        assert(FALSE);
    }
}

void NvmJobEndNotification(void)
{
}

void NvmJobErrorNotification(void)
{
}

#define ECUM_STOP_SEC_CODE
#include "EcuM_MemMap.h"
/*______ L O C A L - F U N C T I O N S _____________________________________*/

/*______ E N D _______________________________________________________________*/
