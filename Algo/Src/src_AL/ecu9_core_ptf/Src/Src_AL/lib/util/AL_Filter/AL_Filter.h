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
* \file     AL_Filter.h
*
* \brief    AL filter Utility header file
*
* \descr    AL filter Utility (common APIs) for analog filtering
*
* \author   Francesco Di Noto
*
*/
/******************************************************************************/

#ifndef AL_FILTER_H
#define AL_FILTER_H

/* _____ I N C L U D E - F I L E S ___________________________________________*/
#include "Std_Types.h"

/* _____ G L O B A L - D E F I N E - D E C L A R A T I O N S _________________*/
/* Definition for Order first filter buffer size */
#define AL_FILTER_LOWPASS_BUFF_SIZE                                         (2U)

#define AL_FILTER_STORAGE_SCALING                                           (9U)
#define AL_FILTER_ROUND_STORAGE                                             (256U)
#define AL_FILTER_ROUND_BETA                                                (64U)
#define AL_FILTER_BETA_SCALING                                              (7U)
#define AL_FILTER_RAW_SCALING                                               (4U)

/* _____ G L O B A L - T Y P E S - D E C L A R A T I O N S ___________________*/
/* Type definition for filtering value type */
typedef uint16 AL_Filter_FilterValueType;

/* Type definition to abstract filtering functions */
typedef uint16(*AL_Filter_FncType)
(
  VAR(uint16, AUTOMATIC) RawValue,
  P2CONST(void, AUTOMATIC, AL_FILTER_APPL_CONST) ParamPtr
);

/* Type definition for function mean fast parameter */
typedef struct AL_Filter_MeanFastParamType_st
{
  uint16* RawSamplesBuffPtr;
  
  uint8 NumOfSamplesToMean;
  
} AL_Filter_MeanFastParamType;

/* Type definition for function mean parameter */
typedef struct AL_Filter_MeanSlowParamType_st
{
  uint16* RawSamplesBuffPtr;
  
  uint8 NumOfSamplesToMean;
  
} AL_Filter_MeanSlowParamType;

/* order 1 filter Beta Values in range 1 : 127  */
/*  beta = 128 * e^( -T/TAU) where Tau expressed as Ntimes*T */
typedef enum AL_Filter_Order1FilterBetaType_en
{
  AL_Filter_Beta_1x   =  47,
  AL_Filter_Beta_2x   =  78,
  AL_Filter_Beta_3x   =  92,
  AL_Filter_Beta_4x   = 100,
  AL_Filter_Beta_5x   = 105,
  AL_Filter_Beta_6x   = 108,
  AL_Filter_Beta_8x   = 113,
  AL_Filter_Beta_10x  = 116,
  AL_Filter_Beta_12x  = 118,
  AL_Filter_Beta_15x  = 120,
  AL_Filter_Beta_20x  = 122,
  AL_Filter_Beta_25x  = 123,
  AL_Filter_Beta_30x  = 124,
  AL_Filter_Beta_40x  = 125,
  AL_Filter_Beta_60x  = 126,
  AL_Filter_Beta_130x = 127
  
} AL_Filter_Order1FilterBetaType;

/* Type definition for function Order1Filter parameter */
typedef struct AL_Filter_Order1FilterParamType_st
{
  uint32* UnscaledMeanValuePtr;
  
  AL_Filter_Order1FilterBetaType Beta;
  
} AL_Filter_Order1FilterParamType;

/* _____ G L O B A L - D A T A - D E F I N I T I O N S _______________________*/

/* _____ G L O B A L - M A C R O S - D E C L A R A T I O N S _________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/
#define AL_FILTER_START_SEC_CODE
#include "AL_FILTER_MemMap.h"

extern FUNC(uint16, AL_FILTER_CODE) AL_Filter_MeanFast
(
  VAR(uint16, AUTOMATIC) RawValue,
  P2CONST(void, AUTOMATIC, AL_FILTER_APPL_CONST) ParamPtr
);

extern FUNC(uint16, AL_FILTER_CODE) AL_Filter_MeanSlow
(
  VAR(uint16, AUTOMATIC) RawValue,
  P2CONST(void, AUTOMATIC, AL_FILTER_APPL_CONST) ParamPtr
);

extern FUNC(uint16, AL_FILTER_CODE) AL_Filter_Order1Filter
(
  VAR(uint16, AUTOMATIC) RawValue,
  P2CONST(void, AUTOMATIC, AL_FILTER_APPL_CONST) ParamPtr
);

#define AL_FILTER_STOP_SEC_CODE
#include "AL_FILTER_MemMap.h"

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

#endif

/*______ E N D _____ (AL_Filter.h) ___________________________________________*/
