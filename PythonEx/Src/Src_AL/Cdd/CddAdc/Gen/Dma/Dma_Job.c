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
/// \file  Dma_Job.c
///
/// \brief
///
//-----------------------------------------------------------------------------

#include "Dma_Job.h"
#include <UtilUtility.h>
#include <../Cdd/CddAdc/Gen/CddAdc_Types.h>
#include <../Cdd/CddDma/Api/CddDma.h>

static void CddAdc_SetDmaParam(tsCddAdc_CfgData sCfgData, tsCddAdc_DmaTriggerCfg * const sDmaCfg);

//-----------------------------------------------------------------------------
/// \brief CddAdc_InitDma
///
/// \descr
///
/// \param  -
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType CddAdc_InitDmaJob(tsCddAdc_CfgData sCfgData)
{
  tsCddDma_Parameter sAdc0DmaParam, sAdc1DmaParam;
  tsCddAdc_DmaTriggerCfg sDmaCfg = { NULL_PTR, NULL_PTR, 0u, NULL_PTR, NULL_PTR, 0u };

  boolean boDmaCfgValid = TRUE;

  CddAdc_SetDmaParam(sCfgData, &sDmaCfg);

  sAdc0DmaParam.pulSourceAddress = sDmaCfg.pulAdc0Source;
  sAdc0DmaParam.pulTargetAddress = sDmaCfg.pulAdc0Target;
  sAdc0DmaParam.unRepetitions    = sDmaCfg.unAdc0DataSize;
  sAdc1DmaParam.pulSourceAddress = sDmaCfg.pulAdc1Source;
  sAdc1DmaParam.pulTargetAddress = sDmaCfg.pulAdc1Target;
  sAdc1DmaParam.unRepetitions    = sDmaCfg.unAdc1DataSize;

  if ((sAdc0DmaParam.pulSourceAddress != NULL_PTR) && (sAdc0DmaParam.pulTargetAddress != NULL_PTR) && (sAdc0DmaParam.unRepetitions != 0u))
  {
    CddDma_EnableHwTrigger(CDDADC_ADC0_DMA_CONV_CH, TRUE);
    CddDma_StartJob(CDDADC_ADC0_DMA_CONV_CH, &sAdc0DmaParam, NULL_PTR);
  }
  else
  {
    boDmaCfgValid = FALSE;
  }

  if ((sAdc1DmaParam.pulSourceAddress != NULL_PTR) && (sAdc1DmaParam.pulTargetAddress != NULL_PTR) && (sAdc1DmaParam.unRepetitions != 0u))
  {
    CddDma_EnableHwTrigger(CDDADC_ADC1_DMA_CONV_CH, TRUE);
    CddDma_StartJob(CDDADC_ADC1_DMA_CONV_CH, &sAdc1DmaParam, NULL_PTR);
    boDmaCfgValid = TRUE;
  }
  else
  {
    // Skip for function return
  }

  return ((boDmaCfgValid != FALSE) ? E_OK : E_NOT_OK);
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_SetDmaParam
///
/// \descr
///
/// \param  sDmaCfg
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
static void CddAdc_SetDmaParam(tsCddAdc_CfgData sCfgData, tsCddAdc_DmaTriggerCfg* const sDmaCfg)
{
  uint32 ulAdc0LoopCnt = 0u, ulAdc1LoopCnt = 0u;
  uint32 * pulAdc0SrcAddr, *pulAdc1SrcAddr, *pulAdc0TrgtAddr, *pulAdc1TrgtAddr;
  uint8 ucMinAdc0Ch = 255u, ucMinAdc1Ch = 255u;
  uint8 ucIdxAdc0Ch = 0u, ucIdxAdc1Ch = 0u;
  uint8 ucInChIdx;

  for (ucInChIdx = 0u; ucInChIdx < sCfgData.psAdcInputChCfg.ucCfgLength; ucInChIdx++)
  {
    if (sCfgData.psAdcInputChCfg.psAdcInCfg[ucInChIdx].psAdcInst == ADC0)
    {
      if (sCfgData.psAdcInputChCfg.psAdcInCfg[ucInChIdx].ucAdcCh < ucMinAdc0Ch)
      {
        ucMinAdc0Ch = sCfgData.psAdcInputChCfg.psAdcInCfg[ucInChIdx].ucAdcCh;
        ucIdxAdc0Ch = ucInChIdx;
      }
      else
      {
        // skip
      }
      ulAdc0LoopCnt++;
    }
    else
    {
      if (sCfgData.psAdcInputChCfg.psAdcInCfg[ucInChIdx].ucAdcCh < ucMinAdc1Ch)
      {
        ucMinAdc1Ch = sCfgData.psAdcInputChCfg.psAdcInCfg[ucInChIdx].ucAdcCh;
        ucIdxAdc1Ch = ucInChIdx;
      }
      else
      {
        // skip
      }
      ulAdc1LoopCnt++;
    }
  }

  sDmaCfg->unAdc0DataSize = ulAdc0LoopCnt;
  sDmaCfg->unAdc1DataSize = ulAdc1LoopCnt;

  if (ucMinAdc0Ch != 255u)
  {
    sDmaCfg->pulAdc0Source = (uint32*)&sCfgData.psAdcInputChCfg.psAdcInCfg[ucIdxAdc0Ch].psAdcInst->R[ucMinAdc0Ch].Reg;
    sDmaCfg->pulAdc0Target = sCfgData.psAdcInputChCfg.psAdcInCfg[ucIdxAdc0Ch].pulAdcData;
  }
  else
  {
    sDmaCfg->pulAdc0Source = NULL_PTR;
    sDmaCfg->pulAdc1Source = NULL_PTR;
  }

  if (ucMinAdc1Ch != 255u)
  {
    sDmaCfg->pulAdc1Source = (uint32*)&sCfgData.psAdcInputChCfg.psAdcInCfg[ucIdxAdc1Ch].psAdcInst->R[ucMinAdc1Ch].Reg;
    sDmaCfg->pulAdc1Target = sCfgData.psAdcInputChCfg.psAdcInCfg[ucIdxAdc1Ch].pulAdcData;
  }
  else
  {
    sDmaCfg->pulAdc0Source = NULL_PTR;
    sDmaCfg->pulAdc1Source = NULL_PTR;
  }
}

// EOF
