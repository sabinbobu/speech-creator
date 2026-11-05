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
#include "Adc_reg_stubs.h"


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
  
  // Return DMA config status
  return E_OK;
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
  return;
}
// EOF
