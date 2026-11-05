//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  Adc_Dma.c
///
/// \brief Adc DMA setup
///
/// \author Stefan Tyirean (f75617c)
///         mailto: stefan.tyirean[at]marelli.com
///
/// \Date April 2021
///
//-----------------------------------------------------------------------------

//====================================================================
// Include files
//====================================================================

#include "Adc_Dma.h"
#include <UtilUtility.h>
#include "Adc_TargetTypes.h"
#include "CddDma.h"

#if defined (CPU_S32K142)
  #include <S32K142.h>
#elif defined (CPU_S32K144)
  #include <S32K144.h>
#elif defined (CPU_S32K146)
  #include <S32K146.h>
#endif

#if defined (UNIT_TEST)
#include "Adc_reg_stubs.h"
#endif

//====================================================================
// Defines
//====================================================================

#define ADC_DMA_INVALID_CH                16u

//====================================================================
// Local function declaration
//====================================================================

STATIC_AL void Adc_Dma_SetDmaParam(CONST_AL tsAdc_CfgData* CONST_AL psAdcCfgData, tsAdc_DmaTriggerCfg * CONST_AL psDmaCfg);


//====================================================================
// Global function definition
//====================================================================

//-----------------------------------------------------------------------------
/// \brief Adc_InitDmaJob
///
/// \descr Adc Dma Job configuration (source, destination and transfer count)
///
/// \param  psAdcCfgData - Global ADC data configuration which includes DMA information
///
/// \return Std_ReturnType - Dma Job initialization status
//-----------------------------------------------------------------------------
Std_ReturnType Adc_Dma_InitDmaJob(CONST_AL tsAdc_CfgData* CONST_AL psAdcCfgData)
{
  // Local DMA config extraction setup
  tsCddDma_Parameter sAdc0DmaParam, sAdc1DmaParam;
  // Input DMA setup
  tsAdc_DmaTriggerCfg sDmaCfg = { NULL_PTR, NULL_PTR, 0u, NULL_PTR, NULL_PTR, 0u };
  // Local DMA configuration status
  boolean boDmaCfgValid = TRUE;

  // Extract DMA config based on ADC config data
  Adc_Dma_SetDmaParam(psAdcCfgData, &sDmaCfg);

  // Init Local DMA config
  sAdc0DmaParam.pulSourceAddress = sDmaCfg.pulAdc0Source;
  sAdc0DmaParam.pulTargetAddress = sDmaCfg.pulAdc0Target;
  sAdc0DmaParam.unRepetitions    = sDmaCfg.unAdc0DataSize;
  sAdc1DmaParam.pulSourceAddress = sDmaCfg.pulAdc1Source;
  sAdc1DmaParam.pulTargetAddress = sDmaCfg.pulAdc1Target;
  sAdc1DmaParam.unRepetitions    = sDmaCfg.unAdc1DataSize;

  // Check ADC0 DMA config
  if ((sAdc0DmaParam.pulSourceAddress != NULL_PTR) && (sAdc0DmaParam.pulTargetAddress != NULL_PTR) && (sAdc0DmaParam.unRepetitions != 0u))
  {
    // DMA Job config for ADC0
    // Keep status TRUE
    CddDma_StartJob(ADC_ADC0_DMA_CONV_CH, &sAdc0DmaParam, NULL_PTR);
  }
  else
  {
    // Set status FALSE
    boDmaCfgValid = FALSE;
  }

  // Check ADC1 DMA config
  if ((sAdc1DmaParam.pulSourceAddress != NULL_PTR) && (sAdc1DmaParam.pulTargetAddress != NULL_PTR) && (sAdc1DmaParam.unRepetitions != 0u))
  {
    // DMA Job config for ADC0
    // Keep status TRUE
    CddDma_StartJob(ADC_ADC1_DMA_CONV_CH, &sAdc1DmaParam, NULL_PTR);
    boDmaCfgValid = TRUE;
  }
  else
  {
    // Skip for function return
  }

  // Return DMA config status
  return ((boDmaCfgValid != FALSE) ? E_OK : E_NOT_OK);
}

//-----------------------------------------------------------------------------
/// \brief Adc_Dma_SetDmaParam
///
/// \descr Dma configuration extraction from global Adc data init
///
/// \param  psAdcCfgData - Pointer to global Adc Data structure init configuration
///         psDmaCfg     - Pointer to Dma Configuration extract Input
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Adc_Dma_SetDmaParam(CONST_AL tsAdc_CfgData* CONST_AL psAdcCfgData, tsAdc_DmaTriggerCfg* CONST_AL psDmaCfg)
{
  // Local counters to found how many channel are used for each ADC instance [ADC0, ADC1]
  uint16 unAdc0LoopCnt = 0u, unAdc1LoopCnt = 0u;
  // Source and Destination Addresses for DMA transfer [ADC0 and ADC1]
  uint32 * pulAdc0SrcAddr, *pulAdc1SrcAddr, *pulAdc0TrgtAddr, *pulAdc1TrgtAddr;
  // First ADC channel used [ADC0 and ADC1], 255 value is invalid
  uint8 ucMinAdc0Ch = ADC_DMA_INVALID_CH, ucMinAdc1Ch = ADC_DMA_INVALID_CH;
  // ADC channel indexes
  uint8 ucIdxAdc0Ch = 0u, ucIdxAdc1Ch = 0u;
  uint8 ucInChIdx;

  for (ucInChIdx = 0u; ucInChIdx < psAdcCfgData->sAdcInputChCfg.ucCfgLength; ucInChIdx++)
  {
    // ADC0 Instance
    if (psAdcCfgData->sAdcInputChCfg.psAdcInCfg[ucInChIdx].ucAdcInst == 0u) 
    {
      // Find minimum channel
      if (psAdcCfgData->sAdcInputChCfg.psAdcInCfg[ucInChIdx].ucAdcCh < ucMinAdc0Ch)
      {
        ucMinAdc0Ch = psAdcCfgData->sAdcInputChCfg.psAdcInCfg[ucInChIdx].ucAdcCh;
        ucIdxAdc0Ch = ucInChIdx;
      }
      else
      {
        // skip if actual channels index is grater than minimum
      }
      // Count the ADC0 valid channels
      unAdc0LoopCnt = (psAdcCfgData->sAdcInputChCfg.psAdcInCfg[ucInChIdx].ucAdcCh < ADC_DMA_INVALID_CH) ? unAdc0LoopCnt+1u : unAdc0LoopCnt;
    }
    // ADC1 Instance
    else
    {
      // Find minimum channel
      if (psAdcCfgData->sAdcInputChCfg.psAdcInCfg[ucInChIdx].ucAdcCh < ucMinAdc1Ch) 
      {
        ucMinAdc1Ch = psAdcCfgData->sAdcInputChCfg.psAdcInCfg[ucInChIdx].ucAdcCh;
        ucIdxAdc1Ch = ucInChIdx;
      }
      else
      {
        // skip if actual channels index is grater than minimum
      }
      // Count the ADC1 valid channels
      unAdc1LoopCnt = (psAdcCfgData->sAdcInputChCfg.psAdcInCfg[ucInChIdx].ucAdcCh < ADC_DMA_INVALID_CH) ? unAdc1LoopCnt + 1u : unAdc1LoopCnt;
    }
  }

  // Adc valid chhannels count reflects DMA transfer length
  psDmaCfg->unAdc0DataSize = unAdc0LoopCnt;
  psDmaCfg->unAdc1DataSize = unAdc1LoopCnt;

  // Based on minimum channel index, return DMA source and destination addresses
  // ADC0
  if (ucMinAdc0Ch != ADC_DMA_INVALID_CH)
  {
    // PRQA S 306, 310, 311, 312  1 // pointer cast needed. Peripheric source address is needed
    psDmaCfg->pulAdc0Source = (uint32*)&ADC0->R[ucMinAdc0Ch];
    psDmaCfg->pulAdc0Target = psAdcCfgData->sAdcInputChCfg.psAdcInCfg[ucIdxAdc0Ch].pulAdcData;
  }
  else
  {
    // If minimum channel is invalid, addresses are NULL
    psDmaCfg->pulAdc0Source = NULL_PTR;
    psDmaCfg->pulAdc0Target = NULL_PTR;
  }

  // Based on minimum channel index, return DMA source and destination addresses
  // ADC0
  if (ucMinAdc1Ch != ADC_DMA_INVALID_CH)
  {
    // PRQA S 306, 310, 311, 312  1 // pointer cast needed. Peripheric source address is needed
    psDmaCfg->pulAdc1Source = (uint32*)&ADC1->R[ucMinAdc1Ch];
    psDmaCfg->pulAdc1Target = psAdcCfgData->sAdcInputChCfg.psAdcInCfg[ucIdxAdc1Ch].pulAdcData;
  }
  else
  {
    // If minimum channel is invalid, addresses are NULL
    psDmaCfg->pulAdc1Source = NULL_PTR;
    psDmaCfg->pulAdc1Target = NULL_PTR;
  }
}
// EOF
