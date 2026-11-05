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
* \file     IoHwAb_Digital.c
*
* \brief    BSW IoHwAb digital
*
* \descr    Digital signals support for IoHwAb module.
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "IoHwAb.h"
#include "IoHwAb_Internals.h"

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/
FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_DigitalRead
(
  VAR(IoHwAb_DigitalChannelIdType, AUTOMATIC) ChId,
  P2VAR(IoHwAb_LevelType, AUTOMATIC, IOHWAB_APPL_DATA) LevelPtr
)
{
  /* Init local variables */
  Std_ReturnType RetVal = E_NOT_OK;

  if ((LevelPtr != NULL_PTR) && (ChId < IOHWAB_NUM_OF_DIGITAL_CHS) && (IoHwAb_DigitalChannelCfg[ChId].Direction != IOHWAB_DIRECTION_OUTPUT))
  {
    switch (IoHwAb_DigitalChannelCfg[ChId].SourceType)
    {
      case IOHWAB_SOURCE_TYPE_MCAL_DIO:
        *LevelPtr = (IoHwAb_LevelType)Dio_ReadChannel((Dio_ChannelType)IoHwAb_DigitalChannelCfg[ChId].SourceId);

        RetVal = E_OK;

        break;

      case IOHWAB_SOURCE_TYPE_EXTERNAL:
        *LevelPtr = IoHwAb_DigitalReadExternal(IoHwAb_DigitalChannelCfg[ChId].SourceId);

        RetVal = E_OK;

        break;

      default:
        break;
    }
  }

  return RetVal;
}

FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_DigitalWrite
(
  VAR(IoHwAb_DigitalChannelIdType, AUTOMATIC) ChId,
  VAR(IoHwAb_LevelType, AUTOMATIC) Level
)
{
  /* Init local variables */
  Std_ReturnType RetVal = E_NOT_OK;

  if ((ChId < IOHWAB_NUM_OF_DIGITAL_CHS) && (IoHwAb_DigitalChannelCfg[ChId].Direction != IOHWAB_DIRECTION_INPUT))
  {
    switch (IoHwAb_DigitalChannelCfg[ChId].SourceType)
    {
      case IOHWAB_SOURCE_TYPE_MCAL_DIO:
        Dio_WriteChannel((Dio_ChannelType)IoHwAb_DigitalChannelCfg[ChId].SourceId, (Dio_LevelType)Level);

        RetVal = E_OK;

        break;

      case IOHWAB_SOURCE_TYPE_EXTERNAL:
        IoHwAb_DigitalWriteExternal(IoHwAb_DigitalChannelCfg[ChId].SourceId, Level);

        RetVal = E_OK;

        break;

      default:
        break;
    }
  }

  return RetVal;
}

/*______ L O C A L - F U N C T I O N S _______________________________________*/

/*______ E N D _______________________________________________________________*/
