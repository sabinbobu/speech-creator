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
  {
    IOHWAB_DIRECTION_OUTPUT,
    IOHWAB_SOURCE_TYPE_MCAL_DIO,
    (IoHwAb_SourceIdType)DioConf_DioChannel_HW_IF_PA3_EN_LWR,
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
