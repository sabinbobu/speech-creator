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
* \file     IoHwAb_Analog.c
*
* \brief    BSW IoHwAb analog
*
* \descr    Analog signals support for IoHwAb module.
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
/* Guard bit used for rounding (first bit following the LSB) */
#define GUARD(x)                                       (1U << ((x) - 1U))
/* Compute Y value given offset and slope (Y = m*X + q) */
#define LINEAR(value, k, shift, offset) (IoHwAb_ConvertedValueType)(((((sint32)value * k) + GUARD(shift)) >> (shift)) + (offset))

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/
STATIC VAR(IoHwAb_AnalogChannelType, IOHWAB_APPL_DATA) IoHwAb_AnalogChannel[IOHWAB_NUM_OF_ANALOG_CHS];

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/
STATIC FUNC(IoHwAb_RawValueType, IOHWAB_CODE) IoHwAb_AnalogAcquire
(
  VAR(IoHwAb_ChannelIdType, AUTOMATIC) ChIdx
);

STATIC FUNC(IoHwAb_RawValueType, IOHWAB_CODE) IoHwAb_AnalogAcquireMcal
(
  VAR(uint32, AUTOMATIC) SourceParams
);

STATIC FUNC(IoHwAb_RawValueType, IOHWAB_CODE) IoHwAb_AnalogFilter
(
  VAR(IoHwAb_ChannelIdType, AUTOMATIC) ChIdx,
  VAR(IoHwAb_RawValueType, AUTOMATIC) RawValue
);

STATIC FUNC(IoHwAb_ConvertedValueType, IOHWAB_CODE) IoHwAb_AnalogConvertLinear
(
  VAR(IoHwAb_RawValueType, AUTOMATIC) FilteredRawValue,
  P2CONST(void, AUTOMATIC, IOHWAB_CONST) ConvParams
);

STATIC FUNC(IoHwAb_ConvertedValueType, IOHWAB_CODE) IoHwAb_AnalogConvertLinearized
(
  VAR(IoHwAb_RawValueType, AUTOMATIC) FilteredRawValue,
  P2CONST(void, AUTOMATIC, IOHWAB_CONST) ConvParams
);

STATIC FUNC(IoHwAb_ConvertedValueType, IOHWAB_CODE) IoHwAb_AnalogConvert
(
  VAR(IoHwAb_ChannelIdType, AUTOMATIC) ChIdx,
  VAR(IoHwAb_RawValueType, AUTOMATIC) RawValue
);

/*______ G L O B A L - F U N C T I O N S _____________________________________*/
FUNC(void, IOHWAB_CODE) IoHwAb_AnalogInit(void)
{
  /* Init local variables */
  uint8 AdcGroupIdx;

  for (AdcGroupIdx = 0U; AdcGroupIdx < IOHWAB_ADC_NUM_OF_GROUPS; AdcGroupIdx++)
  {
    Adc_SetupResultBuffer(IoHwAb_AdcCfg[AdcGroupIdx].GroupId, IoHwAb_AdcCfg[AdcGroupIdx].ResBuffer);
  }
}

FUNC(void, IOHWAB_CODE) IoHwAb_AnalogMainFunction(void)
{
  /* Init local variables */
  IoHwAb_ChannelIdType ChIdx;

  for (ChIdx = 0U; ChIdx < IOHWAB_NUM_OF_ANALOG_CHS; ChIdx++)
  {
    IoHwAb_AnalogChannel[ChIdx].Raw = IoHwAb_AnalogAcquire(ChIdx);
    IoHwAb_AnalogChannel[ChIdx].RawFiltered = IoHwAb_AnalogFilter(ChIdx, IoHwAb_AnalogChannel[ChIdx].Raw);
    IoHwAb_AnalogChannel[ChIdx].ConvertedValue = IoHwAb_AnalogConvert(ChIdx, IoHwAb_AnalogChannel[ChIdx].RawFiltered);
  }
}

FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_AnalogReadConverted
(
  VAR(IoHwAb_AnalogChannelIdType, AUTOMATIC) ChId,
  P2VAR(IoHwAb_ConvertedValueType, AUTOMATIC, IOHWAB_APPL_DATA) OutPtr
)
{
  /* Init local variables */
  Std_ReturnType RetVal = E_NOT_OK;
  
  if((OutPtr != NULL_PTR) && (ChId < IOHWAB_NUM_OF_ANALOG_CHS))
  {
    *OutPtr = IoHwAb_AnalogChannel[ChId].ConvertedValue;

    RetVal = E_OK;
  }

  return RetVal;
}

FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_AnalogReadRaw
(
  VAR(IoHwAb_AnalogChannelIdType, AUTOMATIC) ChId,
  P2VAR(IoHwAb_RawValueType, AUTOMATIC, IOHWAB_APPL_DATA) OutPtr
)
{
  /* Init local variables */
  Std_ReturnType RetVal = E_NOT_OK;
  
  if((OutPtr != NULL_PTR) && (ChId < IOHWAB_NUM_OF_ANALOG_CHS))
  {
    *OutPtr = IoHwAb_AnalogChannel[ChId].Raw;

    RetVal = E_OK;
  }

  return RetVal;
}

/*______ L O C A L - F U N C T I O N S _______________________________________*/
STATIC FUNC(IoHwAb_RawValueType, IOHWAB_CODE) IoHwAb_AnalogAcquire
(
  VAR(IoHwAb_ChannelIdType, AUTOMATIC) ChIdx
)
{
  /* Init local variables */
  IoHwAb_RawValueType RawValue = 0U;

  switch (IoHwAb_AnalogChannelCfg[ChIdx].SourceType)
  {
    case IOHWAB_SOURCE_TYPE_MCAL_ADC:
      RawValue = IoHwAb_AnalogAcquireMcal(IoHwAb_AnalogChannelCfg[ChIdx].SourceId);
      break;

    case IOHWAB_SOURCE_TYPE_EXTERNAL:
      RawValue = IoHwAb_AnalogAcquireExternal(IoHwAb_AnalogChannelCfg[ChIdx].SourceId);
      break;

    default:
      break;
  }

  return RawValue;
}

STATIC FUNC(IoHwAb_RawValueType, IOHWAB_CODE) IoHwAb_AnalogAcquireMcal
(
  VAR(IoHwAb_SourceIdType, AUTOMATIC) SourceId
)
{
  /* Init local variables */
  Adc_GroupType GroupId = IOHWAB_ADC_GET_GROUP(SourceId);
  Adc_ChannelType ChannelId = IOHWAB_ADC_GET_CHANNEL(SourceId);

  return (IoHwAb_RawValueType)IoHwAb_AdcCfg[GroupId].ResBuffer[ChannelId];
}

STATIC FUNC(IoHwAb_RawValueType, IOHWAB_CODE) IoHwAb_AnalogFilter
(
  VAR(IoHwAb_ChannelIdType, AUTOMATIC) ChIdx,
  VAR(IoHwAb_RawValueType, AUTOMATIC) RawValue
)
{
  /* Init local variables */
  IoHwAb_RawValueType FilterOut = RawValue;

  switch (IoHwAb_AnalogChannelCfg[ChIdx].FilterType)
  {
    case IOHWAB_FILTER_MEAN_SLOW:
      FilterOut = AL_Filter_MeanSlow(RawValue, IoHwAb_AnalogChannelCfg[ChIdx].FilterParams);
      break;
    case IOHWAB_FILTER_MEAN_FAST:
      FilterOut = AL_Filter_MeanFast(RawValue, IoHwAb_AnalogChannelCfg[ChIdx].FilterParams);
      break;
    case IOHWAB_FILTER_LOW_PASS:
      FilterOut = AL_Filter_Order1Filter(RawValue, IoHwAb_AnalogChannelCfg[ChIdx].FilterParams);
      break;
    case IOHWAB_FILTER_NONE:
    default:
      break;
  }

  return FilterOut;
}

STATIC FUNC(IoHwAb_ConvertedValueType, IOHWAB_CODE) IoHwAb_AnalogConvert
(
  VAR(IoHwAb_ChannelIdType, AUTOMATIC) ChIdx,
  VAR(IoHwAb_RawValueType, AUTOMATIC) RawValue
)
{
  /* Init local variables */
  IoHwAb_ConvertedValueType ConvertedValue;

  switch (IoHwAb_AnalogChannelCfg[ChIdx].ConvType)
  {
    case IOHWAB_CONVERSION_LINEAR:
      ConvertedValue = IoHwAb_AnalogConvertLinear(RawValue, IoHwAb_AnalogChannelCfg[ChIdx].ConvParams);
      break;

    case IOHWAB_CONVERSION_LINEARIZED:
      ConvertedValue = IoHwAb_AnalogConvertLinearized(RawValue, IoHwAb_AnalogChannelCfg[ChIdx].ConvParams);
      break;

    case IOHWAB_CONVERSION_NONE:
    default:
      ConvertedValue = RawValue;
      break;
  }

  return ConvertedValue;
}

STATIC FUNC(IoHwAb_ConvertedValueType, IOHWAB_CODE) IoHwAb_AnalogConvertLinear
(
  VAR(IoHwAb_RawValueType, AUTOMATIC) RawValue,
  P2CONST(void, AUTOMATIC, IOHWAB_CONST) ConvParams
)
{
  /* Init local variables */
  IoHwAb_ConvertedValueType ConvertedValue;
  const IoHwAb_AnalogLinearConvParamsType* LinearParams;

  LinearParams = (const IoHwAb_AnalogLinearConvParamsType*)ConvParams;

  ConvertedValue = LINEAR(RawValue, LinearParams->SlopeNum, LinearParams->SlopeDen, LinearParams->Offset);

  return ConvertedValue;
}

STATIC FUNC(IoHwAb_ConvertedValueType, IOHWAB_CODE) IoHwAb_AnalogConvertLinearized
(
  VAR(IoHwAb_RawValueType, AUTOMATIC) RawValue,
  P2CONST(void, AUTOMATIC, IOHWAB_CONST) ConvParams
)
{
  /* Init local variables */
  IoHwAb_ConvertedValueType ConvertedValue;
  const IoHwAb_AnalogLinearizedConvParamsType* LinearizedParams;
  const IoHwAb_AnalogLinearizedPointType* Points;
  uint8 Idx;
  boolean EndLoop = FALSE;

  LinearizedParams = (const IoHwAb_AnalogLinearizedConvParamsType*)ConvParams;
  Points = LinearizedParams->Points;

  if (RawValue <= Points[0].Raw)
  {
    ConvertedValue = Points[0].Conv;
    EndLoop = TRUE;
  }

  if (RawValue >= Points[LinearizedParams->NumPoints - 1U].Raw)
  {
    ConvertedValue = Points[LinearizedParams->NumPoints - 1U].Conv;
    EndLoop = TRUE;
  }

  /* Linear search through segments */
  for (Idx = 0U; (Idx < (LinearizedParams->NumPoints - 1U)) && (EndLoop == FALSE); Idx++)
  {
    if (RawValue < Points[Idx + 1U].Raw)
    {
      ConvertedValue = LINEAR(RawValue - Points[Idx].Raw, Points[Idx].SlopeNum, Points[Idx].SlopeDen, Points[Idx].Conv);

      EndLoop = TRUE;
    }
  }

  return ConvertedValue;
}

/*______ E N D _______________________________________________________________*/

