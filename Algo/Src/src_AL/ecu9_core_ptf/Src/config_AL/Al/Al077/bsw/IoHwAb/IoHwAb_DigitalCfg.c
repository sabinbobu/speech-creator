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
* \file     IoHwAb_DigitalCfg.c
*
* \brief    IoHwAb digital configuration source file
*
* \descr    Static configuration for IoHwAb digital channels.
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "IoHwAb_DigitalCfg.h"

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/
/* TODO: replace placeholder with real digital channels as they are assigned (SourceId = Dio_ChannelType) */
CONST(IoHwAb_DigitalChannelCfgType, IOHWAB_CONST) IoHwAb_DigitalChannelCfg[IOHWAB_NUM_OF_DIGITAL_CHS] =
{
  /* PIN 33 -> PA0 */
  /* HW_IF_PA0_HSS_1_EN -> HSS IN0 */
  {
    IOHWAB_DIRECTION_OUTPUT,
    IOHWAB_SOURCE_TYPE_MCAL_DIO,
    (IoHwAb_SourceIdType)DioConf_DioChannel_PA0_HSS_EN1,
  },
  /* PIN 34 -> PA1 */
  /* HW_IF_PA1_HSS_SEL_1 -> HSS DSEL */
  {
    IOHWAB_DIRECTION_OUTPUT,
    IOHWAB_SOURCE_TYPE_MCAL_DIO,
    (IoHwAb_SourceIdType)DioConf_DioChannel_PA1_HSS_SEL,
  },
  /* PIN 43 -> PA3 */
  /* HW_IF_PA3_EN_LWR -> LWR EN_LWR */
  {
    IOHWAB_DIRECTION_OUTPUT,
    IOHWAB_SOURCE_TYPE_MCAL_DIO,
    (IoHwAb_SourceIdType)DioConf_DioChannel_PA3_EN_LWR,
  },
  /* PIN 36 -> PA29 */
  /* HW_IF_PA29_HSS_2_EN -> HSS IN1 */
  {
    IOHWAB_DIRECTION_OUTPUT,
    IOHWAB_SOURCE_TYPE_MCAL_DIO,
    (IoHwAb_SourceIdType)DioConf_DioChannel_PA29_HSS_EN2,
  },
  /* PIN 37 -> PA30 */
  /* HW_IF_PA30_HSS_SEN -> HSS DEN */
  {
    IOHWAB_DIRECTION_OUTPUT,
    IOHWAB_SOURCE_TYPE_MCAL_DIO,
    (IoHwAb_SourceIdType)DioConf_DioChannel_PA30_HSS_SEN,
  },
  /* PIN 52 -> PB4 */
  /* HW_IF_PB4_5V0_EN -> 5V0_EN */
  {
    IOHWAB_DIRECTION_OUTPUT,
    IOHWAB_SOURCE_TYPE_MCAL_DIO,
    (IoHwAb_SourceIdType)DioConf_DioChannel_PB4_5V0_EN,
  },
  /* PIN 53 -> PB5 */
  /* HW_IF_PB5_5V0_PG -> 5V0_PG */
  {
    IOHWAB_DIRECTION_INPUT,
    IOHWAB_SOURCE_TYPE_MCAL_DIO,
    (IoHwAb_SourceIdType)DioConf_DioChannel_PB5_5V0_PG,
  },
};

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/
extern FUNC(void, IOHWAB_CODE) IoHwAb_DigitalWriteExternal
(
  VAR(IoHwAb_SourceIdType, AUTOMATIC) SourceId,
  VAR(IoHwAb_LevelType, AUTOMATIC) Level
)
{
  (void)SourceId;
  (void)Level;
}

extern FUNC(IoHwAb_LevelType, IOHWAB_CODE) IoHwAb_DigitalReadExternal
(
  VAR(IoHwAb_SourceIdType, AUTOMATIC) SourceId
)
{
  (void)SourceId;
  
  return IOHWAB_LEVEL_LOW;
}

/*______ L O C A L - F U N C T I O N S _______________________________________*/

/*______ E N D _______________________________________________________________*/
