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
* \file     IoHwAb_Types.h
*
* \brief    BSW IoHwAb types
*
* \descr    Type definitions for IoHwAb module.
*
* \author   Matteo Pellassa
*
*/
/******************************************************************************/

#ifndef IOHWAB_TYPES_H
#define IOHWAB_TYPES_H

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "Std_Types.h"

#include "Adc.h"
#include "AL_Filter.h"

#include "Dio.h"

#include "Pwm.h"
#include "Icu.h"

/*______ G L O B A L - M A C R O _____________________________________________*/

/*______ L O C A L - M A C R O _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/
typedef void* IoHwAb_ConfigType;
typedef uint8 IoHwAb_ChannelIdType;
typedef uint32 IoHwAb_SourceIdType;

typedef enum
{
  IOHWAB_SOURCE_TYPE_MCAL_ADC = 0U,
  IOHWAB_SOURCE_TYPE_MCAL_DIO = 1U,
  IOHWAB_SOURCE_TYPE_MCAL_PWM = 2U,
  IOHWAB_SOURCE_TYPE_MCAL_ICU = 3U,
  IOHWAB_SOURCE_TYPE_EXTERNAL = 0xFFu,
} IoHwAb_SourceType;

/* ANALOG */
#define IOHWAB_ADC_SOURCEID(group, channel)  (IoHwAb_SourceIdType)(((group) << 8U) | ((channel) & 0xFFU))
#define IOHWAB_ADC_GET_GROUP(params)         ((Adc_GroupType)((params) >> 8U))
#define IOHWAB_ADC_GET_CHANNEL(params)       ((Adc_ChannelType)((params) & 0xFFU))

typedef uint16 IoHwAb_RawValueType;
typedef uint32 IoHwAb_ConvertedValueType;

typedef struct
{
  Adc_GroupType GroupId;
  Adc_ValueGroupType* ResBuffer;
} IoHwAb_AdcCfgType;

typedef enum
{
  IOHWAB_FILTER_NONE = 0U,
  IOHWAB_FILTER_MEAN_SLOW,
  IOHWAB_FILTER_MEAN_FAST,
  IOHWAB_FILTER_LOW_PASS,
} IoHwAb_AnalogFilterType;

typedef enum
{
  IOHWAB_CONVERSION_NONE = 0U,
  IOHWAB_CONVERSION_LINEAR,
  IOHWAB_CONVERSION_LINEARIZED,
} IoHwAb_AnalogConvType;

typedef struct
{
  IoHwAb_ConvertedValueType Offset;
  sint16 SlopeNum;
  uint8 SlopeDen;
} IoHwAb_AnalogLinearConvParamsType;

typedef struct
{
  IoHwAb_RawValueType Raw;
  IoHwAb_ConvertedValueType Conv;
  sint16 SlopeNum;
  uint8 SlopeDen;
} IoHwAb_AnalogLinearizedPointType;

typedef struct
{
  uint8 NumPoints;
  const IoHwAb_AnalogLinearizedPointType* Points;
} IoHwAb_AnalogLinearizedConvParamsType;

typedef struct
{
  IoHwAb_RawValueType Raw;
  IoHwAb_RawValueType RawFiltered;
  IoHwAb_ConvertedValueType ConvertedValue;
} IoHwAb_AnalogChannelType;

typedef struct
{
  IoHwAb_SourceType SourceType;
  IoHwAb_SourceIdType SourceId;
  IoHwAb_AnalogFilterType FilterType;
  void* FilterParams;
  IoHwAb_AnalogConvType ConvType;
  void* ConvParams;
} IoHwAb_AnalogChannelCfgType;



/* DIGITAL */
typedef enum
{
  IOHWAB_LEVEL_LOW = 0U,
  IOHWAB_LEVEL_HIGH,
} IoHwAb_LevelType;

typedef enum
{
  IOHWAB_DIRECTION_INPUT = 0U,
  IOHWAB_DIRECTION_OUTPUT,
  IOHWAB_DIRECTION_INOUT,
} IoHwAb_DigitalDirectionType;

typedef struct
{
  IoHwAb_DigitalDirectionType Direction;
  IoHwAb_SourceType SourceType;
  IoHwAb_SourceIdType SourceId;
} IoHwAb_DigitalChannelCfgType;



/* TIMING */
#define IOHWAB_ICU_SOURCEID(startup, mode, channel)  (IoHwAb_SourceIdType)(((startup) << 12U) | ((mode) << 8U) | (channel))
#define IOHWAB_ICU_GET_STARTUP(params)      ((uint8)((params) >> 12U) & 0x01u)
#define IOHWAB_ICU_GET_MODE(params)         ((Icu_MeasurementModeType)((params) >> 8U) & 0x0FU)
#define IOHWAB_ICU_GET_CHANNEL(params)      ((Icu_ChannelType)((params) & 0xFFU))

typedef uint16 IoHwAb_DutyCycleType;
typedef uint32 IoHwAb_PeriodType;

typedef enum
{
  IOHWAB_INTERACTION_ACTUATION = 0U,
  IOHWAB_INTERACTION_MEASUREMENT,
} IoHwAb_TimingInteractionType;

typedef struct
{
  IoHwAb_TimingInteractionType Interaction;
  IoHwAb_SourceType SourceType;
  IoHwAb_SourceIdType SourceId;
} IoHwAb_TimingChannelCfgType;

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/*______ L O C A L - F U N C T I O N S _______________________________________*/

#endif
/*______ E N D _______________________________________________________________*/
