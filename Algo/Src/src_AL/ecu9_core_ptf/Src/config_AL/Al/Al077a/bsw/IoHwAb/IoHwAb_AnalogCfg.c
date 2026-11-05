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
* \file     IoHwAb_AnalogCfg.c
*
* \brief    IoHwAb analog configuration source file
*
* \descr    Static configuration for IoHwAb analog channels.
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "IoHwAb_AnalogCfg.h"

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/
/* ADC result buffers*/
STATIC VAR(Adc_ValueGroupType, IOHWAB_APPL_DATA) IoHwAb_AdcBuffer0[IOHWAB_ADC_NUM_OF_CHS];
STATIC VAR(Adc_ValueGroupType, IOHWAB_APPL_DATA) IoHwAb_AdcBuffer1[IOHWAB_ADC_NUM_OF_CHS];

//Input voltage with 82.5KOhm / 4.64KOhm parition, 3V3 VDD ADC -> 4095 raw = 61.975 V
//Vin [mV] = raw*61975/4095 ~ raw*30995/2048 = raw * 30995 >> 11
//Vin [mV] @ 4095 = 61975
STATIC CONST(IoHwAb_AnalogLinearConvParamsType, IOHWAB_CONST) IoHwAb_ConvParam_Linear1 =
{
  /* Offset */
  0,
  /* SlopeNum */
  30995,
  /* SlopeDen */
  11
};

//Input voltage with 82.5KOhm / 21KOhm parition, 3V3 VDD ADC -> 4095 raw = 16.264 V
//Vin [mV] = raw*16264/4095 ~ raw*32536/8192 = raw * 32536 >> 13
//Vin [mV] @ 4095 = 16264
STATIC CONST(IoHwAb_AnalogLinearConvParamsType, IOHWAB_CONST) IoHwAb_ConvParam_Linear2 =
{
  /* Offset */
  0,
  /* SlopeNum */
  32536,
  /* SlopeDen */
  13
};

/*______ G L O B A L - D A T A _______________________________________________*/
CONST(IoHwAb_AdcCfgType, IOHWAB_CONST) IoHwAb_AdcCfg[IOHWAB_ADC_NUM_OF_GROUPS] =
{
  {
    ADC_GROUP_ID_0,
    IoHwAb_AdcBuffer0,
  },
  {
    ADC_GROUP_ID_1,
    IoHwAb_AdcBuffer1,
  }
};

CONST(IoHwAb_AnalogChannelCfgType, IOHWAB_CONST) IoHwAb_AnalogChannelCfg[IOHWAB_NUM_OF_ANALOG_CHS] =
{
  /* PIN 7 -> PA14 -> ADC A0_12 */
  /* HW_IF_A0_12_EXT_4 -> AIN4 -> ANALOG4 */
  {
    IOHWAB_SOURCE_TYPE_MCAL_ADC,
    IOHWAB_ADC_SOURCEID(0U, 7U),
    IOHWAB_FILTER_NONE,
    NULL_PTR,
    IOHWAB_CONVERSION_NONE, //RBIN/NTC input requires conversion table
    NULL_PTR
  },
  /* PIN 8 -> PA15 -> ADC A1_0 */
  /* HW_IF_A1_0_ADIN_3 -> ADIN_3 -> LWR_SIGNAL*/
  {
    IOHWAB_SOURCE_TYPE_MCAL_ADC,
    IOHWAB_ADC_SOURCEID(1U, 0U),
    IOHWAB_FILTER_NONE,
    NULL_PTR,
    IOHWAB_CONVERSION_LINEAR,
    (void*)&IoHwAb_ConvParam_Linear2
  },
  /* PIN 9 -> PA16 -> ADC A1_1 */
  /* HW_IF_A1_1_EXT_6 -> AIN6 -> ANALOG6 */
  {
    IOHWAB_SOURCE_TYPE_MCAL_ADC,
    IOHWAB_ADC_SOURCEID(1U, 1U),
    IOHWAB_FILTER_NONE,
    NULL_PTR,
    IOHWAB_CONVERSION_NONE, //RBIN/NTC input requires conversion table
    NULL_PTR
  },
  /* PIN 10 -> PA17 -> ADC A1_2 */
  /* HW_IF_A1_2_EXT_1 -> AIN1 -> ANALOG1 */
  {
    IOHWAB_SOURCE_TYPE_MCAL_ADC,
    IOHWAB_ADC_SOURCEID(1U, 2U),
    IOHWAB_FILTER_NONE,
    NULL_PTR,
    IOHWAB_CONVERSION_NONE, //RBIN/NTC input requires conversion table
    NULL_PTR
  },
  /* PIN 11 -> PA18 -> ADC A1_3 */
  /* HW_IF_A1_3_LED3 -> LED3_A -> LED3 */
  {
    IOHWAB_SOURCE_TYPE_MCAL_ADC,
    IOHWAB_ADC_SOURCEID(1U, 3U),
    IOHWAB_FILTER_NONE,
    NULL_PTR,
    IOHWAB_CONVERSION_LINEAR,
    (void*)&IoHwAb_ConvParam_Linear1
  },
  /* PIN 18 -> PA22 -> ADC A0_7 */
  /* HW_IF_A0_7_ADIN_2 -> ADIN_2 -> HSS_2 */
  {
    IOHWAB_SOURCE_TYPE_MCAL_ADC,
    IOHWAB_ADC_SOURCEID(0U, 6U),
    IOHWAB_FILTER_NONE,
    NULL_PTR,
    IOHWAB_CONVERSION_LINEAR,
    (void*)&IoHwAb_ConvParam_Linear2
  },
  /* PIN 25 -> PA24 -> ADC A0_3 */
  /* HW_IF_A0_3_LED2 -> LED2_A -> LED2 */
  {
    IOHWAB_SOURCE_TYPE_MCAL_ADC,
    IOHWAB_ADC_SOURCEID(0U, 3U),
    IOHWAB_FILTER_NONE,
    NULL_PTR,
    IOHWAB_CONVERSION_LINEAR,
    (void*)&IoHwAb_ConvParam_Linear1
  },
  /* PIN 26 -> PA25 -> ADC A0_2 */
  /* HW_IF_A0_2_EXT_5 -> AIN5 -> ANALOG5 */
  {
    IOHWAB_SOURCE_TYPE_MCAL_ADC,
    IOHWAB_ADC_SOURCEID(0U, 2U),
    IOHWAB_FILTER_NONE,
    NULL_PTR,
    IOHWAB_CONVERSION_NONE, //RBIN/NTC input requires conversion table
    NULL_PTR
  },
  /* PIN 30 -> PA26 -> ADC A0_1 */
  /* HW_IF_A0_01_LED4 -> LED4_A -> LED4 */
  {
    IOHWAB_SOURCE_TYPE_MCAL_ADC,
    IOHWAB_ADC_SOURCEID(0U, 1U),
    IOHWAB_FILTER_NONE,
    NULL_PTR,
    IOHWAB_CONVERSION_LINEAR,
    (void*)&IoHwAb_ConvParam_Linear1
  },
  /* PIN 31 -> PA27 -> ADC A0_0 */
  /* HW_IF_A0_0_HSS_SENSE_1_2 -> SENS12 */
  {
    IOHWAB_SOURCE_TYPE_MCAL_ADC,
    IOHWAB_ADC_SOURCEID(0U, 0U),
    IOHWAB_FILTER_NONE,
    NULL_PTR,
    IOHWAB_CONVERSION_NONE, //???
    NULL_PTR
  },
  /* PIN 14 -> PB17 -> ADC A1_4 */
  /* HW_IF_A1_4_EXT_2 -> AIN2 -> ANALOG2 */
  {
    IOHWAB_SOURCE_TYPE_MCAL_ADC,
    IOHWAB_ADC_SOURCEID(1U, 4U),
    IOHWAB_FILTER_NONE,
    NULL_PTR,
    IOHWAB_CONVERSION_NONE, //RBIN/NTC input requires conversion table
    NULL_PTR
  },
  /* PIN 15 -> PB18 -> ADC A1_5 */
  /* HW_IF_A1_5_EXT_3 -> AIN3 -> ANALOG3 */
  {
    IOHWAB_SOURCE_TYPE_MCAL_ADC,
    IOHWAB_ADC_SOURCEID(1U, 5U),
    IOHWAB_FILTER_NONE,
    NULL_PTR,
    IOHWAB_CONVERSION_NONE, //RBIN/NTC input requires conversion table
    NULL_PTR
  },
  /* PIN 16 -> PB19 -> ADC A1_6 */
  /* HW_IF_A1_6_ADIN_1 -> ADIN_1 -> HSS_1 */
  {
    IOHWAB_SOURCE_TYPE_MCAL_ADC,
    IOHWAB_ADC_SOURCEID(1U, 6U),
    IOHWAB_FILTER_NONE,
    NULL_PTR,
    IOHWAB_CONVERSION_LINEAR,
    (void*)&IoHwAb_ConvParam_Linear2
  },
  /* PIN 19 -> PB20 -> ADC A0_6 */
  /* HW_IF_A0_6_PCB_NTC -> PCB_TEMP */
  {
    IOHWAB_SOURCE_TYPE_MCAL_ADC,
    IOHWAB_ADC_SOURCEID(0U, 5U),
    IOHWAB_FILTER_NONE,
    NULL_PTR,
    IOHWAB_CONVERSION_NONE, //RBIN/NTC input requires conversion table
    NULL_PTR
  },
  /* PIN 20 -> PB21 -> ADC A1_8 */
  /* HW_IF_A1_8_EXT_7 -> AIN7 -> ANALOG7 */
  {
    IOHWAB_SOURCE_TYPE_MCAL_ADC,
    IOHWAB_ADC_SOURCEID(1U, 7U),
    IOHWAB_FILTER_NONE,
    NULL_PTR,
    IOHWAB_CONVERSION_NONE, //RBIN/NTC input requires conversion table
    NULL_PTR
  },
  /* PIN 21 -> PB22 -> ADC A1_10 */
  /* HW_IF_A1_11_LED5 -> LED5_A -> LED5 */
  {
    IOHWAB_SOURCE_TYPE_MCAL_ADC,
    IOHWAB_ADC_SOURCEID(1U, 9U),
    IOHWAB_FILTER_NONE,
    NULL_PTR,
    IOHWAB_CONVERSION_LINEAR,
    (void*)&IoHwAb_ConvParam_Linear1
  },
  /* PIN 22 -> PB23 -> ADC A1_11 */
  /* HW_IF_A1_11_LED1 -> LED1_A -> LED1 */
  {
    IOHWAB_SOURCE_TYPE_MCAL_ADC,
    IOHWAB_ADC_SOURCEID(1U, 8U),
    IOHWAB_FILTER_NONE,
    NULL_PTR,
    IOHWAB_CONVERSION_LINEAR,
    (void*)&IoHwAb_ConvParam_Linear1
  },
  /* PIN 27 -> PB25 -> ADC A0_4 */
  /* HW_IF_A0_4_VBAT -> KL30 -> VBAT_DIAG */
  {
    IOHWAB_SOURCE_TYPE_MCAL_ADC,
    IOHWAB_ADC_SOURCEID(0U, 4U),
    IOHWAB_FILTER_NONE,
    NULL_PTR,
    IOHWAB_CONVERSION_LINEAR,
    (void*)&IoHwAb_ConvParam_Linear2
  },
  /* PIN 28 -> PB26 -> ADC A1_13 */
  /* HW_IF_A1_13_LR_DETECTION -> LR_DETECTION */
  {
    IOHWAB_SOURCE_TYPE_MCAL_ADC,
    IOHWAB_ADC_SOURCEID(1U, 10U),
    IOHWAB_FILTER_NONE,
    NULL_PTR,
    IOHWAB_CONVERSION_LINEAR,
    (void*)&IoHwAb_ConvParam_Linear2 //TBR
  },
  /* PIN 29 -> PB27 -> ADC A1_14 */
  /* HW_IF_A1_14_VBOOST -> VBOOST */
  {
    IOHWAB_SOURCE_TYPE_EXTERNAL,
    IOHWAB_ADC_SOURCEID(1U, 11U),
    IOHWAB_FILTER_NONE,
    NULL_PTR,
    IOHWAB_CONVERSION_LINEAR,
    (void*)&IoHwAb_ConvParam_Linear1
  },
};

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/
FUNC(IoHwAb_RawValueType, IOHWAB_CODE) IoHwAb_AnalogAcquireExternal
(
  VAR(IoHwAb_SourceIdType, AUTOMATIC) SourceId
)
{
  (void)SourceId;

  return 0;
}

/*______ L O C A L - F U N C T I O N S _______________________________________*/

/*______ E N D _______________________________________________________________*/
