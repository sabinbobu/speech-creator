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
* \file     IoHwAb_TimingCfg.c
*
* \brief    IoHwAb timing configuration source file
*
* \descr    Static configuration for IoHwAb timing channels.
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "IoHwAb_TimingCfg.h"

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/
CONST(IoHwAb_TimingChannelCfgType, IOHWAB_CONST) IoHwAb_TimingChannelCfg[IOHWAB_NUM_OF_TIMING_CHS] =
{
  /* PIN 42 -> PA2 -> TIMG9 C1 */
  /* HW_IF_TIMG9_C1_CTRL_LWR -> CTRL_LWR */
  {
    IOHWAB_INTERACTION_ACTUATION,
    IOHWAB_SOURCE_TYPE_MCAL_PWM,
    (IoHwAb_SourceIdType)PWM_TIMG_CHANNEL17,
  },
  /* PIN 55 -> PA9 -> TIMG12 C3 */
  /* HW_IF_TIMG12_C3_GPIO_SENS_2 -> GPIO_SENS_2 */
  {
    IOHWAB_INTERACTION_MEASUREMENT,
    IOHWAB_SOURCE_TYPE_MCAL_ICU,
    IOHWAB_ICU_SOURCEID(STD_OFF, ICU_MODE_SIGNAL_MEASUREMENT, ICU_TIM_CHANNEL21),
  },
  /* PIN 56 -> PA10 -> TIMA1 C0 */
  /* HW_IF_TIMA1_C0_LEDCTRL_3 -> LEDCTRL3 */
  {
    IOHWAB_INTERACTION_ACTUATION,
    IOHWAB_SOURCE_TYPE_MCAL_PWM,
    (IoHwAb_SourceIdType)PWM_TIMA_CHANNEL14,
  },
  /* PIN 57 -> PA11 -> TIMA1 C0 */
  /* HW_IF_TIMA1_C0_LEDCTRL_5 -> LEDCTRL5 */
  {
    IOHWAB_INTERACTION_ACTUATION,
    IOHWAB_SOURCE_TYPE_MCAL_PWM,
    (IoHwAb_SourceIdType)PWM_TIMA_CHANNEL15,
  },
  /* PIN 39 -> PA31 -> TIMG7 C1 */
  /* HW_IF_TIMG7_C1_LEDCNTRL_2 -> LEDCTRL2 */
  {
    IOHWAB_INTERACTION_ACTUATION,
    IOHWAB_SOURCE_TYPE_MCAL_PWM,
    (IoHwAb_SourceIdType)PWM_TIMG_CHANNEL5,
  },
  /* PIN 59 -> PB7 -> TIMG12 C1 */
  /* HW_IF_TIMG12_C1_LEDCTRL_1 -> LEDCTRL1 */
  {
    IOHWAB_INTERACTION_ACTUATION,
    IOHWAB_SOURCE_TYPE_MCAL_PWM,
    (IoHwAb_SourceIdType)PWM_TIMG_CHANNEL9,
  },
  /* PIN 60 -> PB8 -> TIMA0 C0 */
  /* HW_IF_TIMA0_C0_LEDCTRL_4 -> LEDCTRL4 */
  {
    IOHWAB_INTERACTION_ACTUATION,
    IOHWAB_SOURCE_TYPE_MCAL_PWM,
    (IoHwAb_SourceIdType)PWM_TIMA_CHANNEL10,
  },
  /* PIN 61 -> PB9 -> TIMA0 C0 */
  /* HW_IF_TIMA0_C0_LEDCTRL_6 -> LEDCTRL6 */
  {
    IOHWAB_INTERACTION_ACTUATION,
    IOHWAB_SOURCE_TYPE_MCAL_PWM,
    (IoHwAb_SourceIdType)PWM_TIMA_CHANNEL11,
  },
  /* PIN 62 -> PB10 -> TIMG8 C1 */
  /* HW_IF_TIMG8_C1_GPIO_SENS_1 -> GPIO_SENS_1 */
  {
    IOHWAB_INTERACTION_MEASUREMENT,
    IOHWAB_SOURCE_TYPE_MCAL_ICU,
    IOHWAB_ICU_SOURCEID(STD_OFF, ICU_MODE_SIGNAL_MEASUREMENT, ICU_TIM_CHANNEL6),
  },
  /* PIN 63 -> PB11 -> TIMG0 C1 */
  /* HW_IF_TIMG0_C1_BSTSYNC -> */
  {
    IOHWAB_INTERACTION_ACTUATION,
    IOHWAB_SOURCE_TYPE_MCAL_PWM,
    (IoHwAb_SourceIdType)PWM_TIMG_CHANNEL1,
  },
};

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/
FUNC(void, IOHWAB_CODE) IoHwAb_SetDutyCycleExternal
(
  VAR(IoHwAb_SourceIdType, AUTOMATIC) SourceId,
  VAR(IoHwAb_DutyCycleType, AUTOMATIC) DutyCycle
)
{
  (void)SourceId;
  (void)DutyCycle;
}

FUNC(void, IOHWAB_CODE)IoHwAb_GetDutyCycleExternal
(
  VAR(IoHwAb_SourceIdType, AUTOMATIC) SourceId,
  P2VAR(IoHwAb_DutyCycleType, AUTOMATIC, IOHWAB_APPL_DATA) DutyCycle
)
{
  (void)SourceId;
  (void)DutyCycle;
}
/*______ L O C A L - F U N C T I O N S _______________________________________*/

/*______ E N D _______________________________________________________________*/