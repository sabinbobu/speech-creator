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
* \file     AL_Filter.c
*
* \brief    AL filter Utility source file
*
* \descr    This module provides utilities (common APIs) for analog filtering
*
* \author   Francesco Di Noto
*
*/
/******************************************************************************/

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "AL_Filter.h"

/*______ L O C A L - D E F I N E S - D E C L A R A T I O N S _________________*/
/* Definition for init filter state */
#define AL_FILTER_INIT_DONE                                         (0x86421357U)

/*______ L O C A L - T Y P E S - D E C L A R A T I O N S _____________________*/

/*______ L O C A L - D A T A - D E F I N I T I O N S  ________________________*/

/*______ L O C A L - M A C R O S - D E C L A R A T I O N S ___________________*/

/*______ P R I V A T E - D A T A - D E F I N I T I O N S _____________________*/

/*______ G L O B A L - D A T A - D E F I N I T I O N S _______________________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ I M P O R T E D - F U N C T I O N S - D E F I N I T I O N S _________*/

/*______ G L O B A L - F U N C T I O N S - D E F I N I T I O N S _____________*/
#define AL_FILTER_START_SEC_CODE
#include "AL_FILTER_MemMap.h"

/******************************************************************************/
/*!
* \brief        AL_Filter_MeanFast(...)
*
* \param[in]    uint16(RawValue): input value
* \param[in]    void*(ParamPtr): pointer to filter structure
* \retval       uint16(RetVal): filter output value
*
* \details      Functions to average fast acquired samples
*               (faster than main function)
*
*
*/
/******************************************************************************/
FUNC(uint16, AL_FILTER_CODE) AL_Filter_MeanFast
(
  VAR(uint16, AUTOMATIC) RawValue,
  P2CONST(void, AUTOMATIC, AL_FILTER_APPL_CONST) ParamPtr
)
{
  /* Init local variables */
  /* Set MeanValue equal to 0 */
  uint32 MeanValue = 0U;
  /* Set AL_Filter_MeanFastParamType* MeanParamPtr equal to ((AL_Filter_MeanFastParamType*)ParamPtr) */
  /* PRQA S 316 ++ */ /* AL_Filter_001 */
  const AL_Filter_MeanFastParamType* MeanParamPtr = ((const AL_Filter_MeanFastParamType*)ParamPtr);
  /* PRQA S 316 -- */ /* AL_Filter_001 */

  /* RawValue value is not used for this type of filter: buffer already contains data to compute */
  (void)RawValue;
  
  /* Loop i from 0 to (i < MeanParamPtr->NumOfSamplesToMean )*/
  for (uint16 i = 0U; i < MeanParamPtr->NumOfSamplesToMean; i++)
  {
    /* Set MeanValue += (uint32)MeanParamPtr->RawSamplesBuffPtr[i] */
    MeanValue += (uint32)MeanParamPtr->RawSamplesBuffPtr[i];
  }
  
  /* Return mean value (MeanValue/MeanParamPtr->NumOfSamplesToMean)*/
  return ((uint16)(MeanValue/MeanParamPtr->NumOfSamplesToMean));
}

/******************************************************************************/
/*!
* \brief        AL_Filter_MeanSlow(...)
*
* \param[in]    uint16(RawValue): input value
* \param[in]    void*(ParamPtr): pointer to filter structure
* \retval       uint16(RetVal): filter output value
*
* \details      Functions to average slow acquired samples
*               (one sample per main function)
*
*
*/
/******************************************************************************/
FUNC(uint16, AL_FILTER_CODE) AL_Filter_MeanSlow
(
  VAR(uint16, AUTOMATIC) RawValue,
  P2CONST(void, AUTOMATIC, AL_FILTER_APPL_CONST) ParamPtr
)
{
  /* Init local variables */
  /* Set MeanValue equal to 0 */
  uint32 MeanValue = 0U;
  uint16 i;
  /* Set AL_Filter_MeanFastParamType* MeanParamPtr equal to ((AL_Filter_MeanFastParamType*)ParamPtr) */
  /* PRQA S 316 ++ */ /* AL_Filter_001 */
  const AL_Filter_MeanSlowParamType* MeanParamPtr = ((const AL_Filter_MeanSlowParamType*)ParamPtr);
  /* PRQA S 316 -- */ /* AL_Filter_001 */

  /* put RawValue in MeanParamPtr->RawSamplesBuffPtr */
  MeanParamPtr->RawSamplesBuffPtr[MeanParamPtr->RawSamplesBuffPtr[MeanParamPtr->NumOfSamplesToMean]] = RawValue;
  
  /* Loop i from 0 to (i < MeanParamPtr->NumOfSamplesToMean )*/
  for (i = 0U; i < MeanParamPtr->NumOfSamplesToMean; i++)
  {
    /* Set MeanValue += (uint32)MeanParamPtr->RawSamplesBuffPtr[i] */
    MeanValue += (uint32)(MeanParamPtr->RawSamplesBuffPtr[i]);
  }
  
  /* Set MeanParamPtr->RawSamplesBuffPtr[i] equal to (MeanParamPtr->RawSamplesBuffPtr[i] + 1U) %  MeanParamPtr->NumOfSamplesToMeanupdate */
  MeanParamPtr->RawSamplesBuffPtr[i] = (MeanParamPtr->RawSamplesBuffPtr[i] + 1U) %  MeanParamPtr->NumOfSamplesToMean;
  
  /* Return mean value (MeanValue/MeanParamPtr->NumOfSamplesToMean)*/
  return ((uint16)(MeanValue/MeanParamPtr->NumOfSamplesToMean));
}

/******************************************************************************/
/*!
* \brief        Order1Filter(...)
*
* \param[in]    uint16(RawValue): input value
* \param[in]    void*(ParamPtr): pointer to filter structure
* \retval       uint16(RetVal): filter output value
*
* \details      Low pass 1st order.
*               Y(n) = (1 - Beta) * X(n) + Beta * Y(n-1) ,   0 < Beta < 1
*               where Beta is normalized to 128 (1...127).
*               filter time constant = - (sampling time) / LN(Beta).
*               If eBeta == 0, the filter algorithm is skipped.
*               The filter storage is scaled by factor 512.
*/
/******************************************************************************/
FUNC(uint16, AL_FILTER_CODE) AL_Filter_Order1Filter
(
  VAR(uint16, AUTOMATIC) RawValue,
  P2CONST(void, AUTOMATIC, AL_FILTER_APPL_CONST) ParamPtr
)
{
  /* Init local variables */
  /* Set AL_Filter_Order1FilterParamType* MeanParamPtr equal to ((AL_Filter_Order1FilterParamType*)ParamPtr) */
  /* PRQA S 316 ++ */ /* AL_Filter_001 */
  const AL_Filter_Order1FilterParamType* MeanParamPtr = ((const AL_Filter_Order1FilterParamType*)ParamPtr);
  /* PRQA S 316 -- */ /* AL_Filter_001 */
  
  /* Is MeanParamPtr->UnscaledMeanValuePtr[1U] equal to AL_FILTER_INIT_DONE ? */
  if (MeanParamPtr->UnscaledMeanValuePtr[1U] == AL_FILTER_INIT_DONE)
  {
    /* Apply mean formula (Y(n) = (1 - Beta) * X(n) + Beta * Y(n-1)) */
    MeanParamPtr->UnscaledMeanValuePtr[0U] = (uint32) ((uint32) (((uint32) (MeanParamPtr->UnscaledMeanValuePtr[0U] * (uint8) MeanParamPtr->Beta) + (uint8) AL_FILTER_ROUND_BETA) >> AL_FILTER_BETA_SCALING)
                  + (uint32) ((uint16)((uint16) ((uint16) ((uint16)1U << AL_FILTER_BETA_SCALING) - (uint16) MeanParamPtr->Beta) * (uint16) AL_FILTER_RAW_SCALING) * (uint32) RawValue));
  }
  else
  {
    /* Init filter */
    /* Set MeanParamPtr->UnscaledMeanValuePtr[0U] equal to ((uint32)RawValue << AL_FILTER_STORAGE_SCALING) */
    MeanParamPtr->UnscaledMeanValuePtr[0U] = ((uint32)RawValue << AL_FILTER_STORAGE_SCALING);
    /* Set MeanParamPtr->UnscaledMeanValuePtr[1U] equal to AL_FILTER_INIT_DONE */
    MeanParamPtr->UnscaledMeanValuePtr[1U] = AL_FILTER_INIT_DONE;
  }
  /* Return Mean Value after scaling it */
  /* (MeanParamPtr->UnscaledMeanValuePtr[0U] + (uint16) 256u)) >> AL_FILTER_ROUND_STORAGE) */
  return (uint16)(((uint32) (MeanParamPtr->UnscaledMeanValuePtr[0U] + (uint16) AL_FILTER_ROUND_STORAGE)) >> AL_FILTER_STORAGE_SCALING);
}

#define AL_FILTER_STOP_SEC_CODE
#include "AL_FILTER_MemMap.h"

/*______ E N D _____ (AL_Filter.c) ___________________________________________*/

/******************************************************************************/
/* Misra Violation */
/******************************************************************************/
/* VIOLATION_ID         QA-C SUPPRESSION        RISK ANALYSIS
   AL_Filter_001        PRQA S 316              Required to manage several filter buffer structures
*/
/******************************************************************************/
