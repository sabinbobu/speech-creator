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
/// \file  Adc.c
///
/// \brief Mcal Adc interfaces/runnables definitions
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

#include "Adc.h"
#include "Adc_TargetTypes.h"
#include "Adc_Drv.h"
#include "Adc_Dma.h"

//====================================================================
// Global function definitions
//====================================================================

//-----------------------------------------------------------------------------
/// \brief Adc_Init
///
/// \descr Adc Initialization [Instances, DMA and channels based on ECU analog inputs]
///
/// \param  psAdcCfgData - Initialization data configuration which covers inputs setup
///                        Adc global configuration, DMA Job and RAM data storage for ADC values
///
/// \return void
//-----------------------------------------------------------------------------
void Adc_Init(CONST_AL tsAdc_CfgData* CONST_AL psAdcCfgData)
{
  // Check input config parameter
  if (psAdcCfgData != NULL_PTR)
  {
    // DMA Job initialization
    (void)Adc_Dma_InitDmaJob(psAdcCfgData);
    // Adc Instances and channels configuration
    (void)Adc_Drv_InitAdc(psAdcCfgData);
  }
  else
  {
    // NULL_PTR, Adc Init configuration shall be avoided
  }
}

//-----------------------------------------------------------------------------
/// \brief Adc_ReadGroup
///
/// \descr Function which returns ADC value based on input (pin order in input list)
///        Adc value returned is a value read from a specific RAM location (DMA source for ADC conversion)
///
/// \param  ucAdcIn - Adc Input Channel (based on IoHwAb Adc pin list)
///         unAdcValue - Adc Value
///
/// \return Std_ReturnType - always returns E_OK
//-----------------------------------------------------------------------------
Std_ReturnType Adc_ReadGroup(uint8 ucAdcIn, uint16* CONST_AL unAdcValue)
{
  // Read RAM location
  *unAdcValue =  Adc_Drv_GetAdcRawValue(ucAdcIn);

  // return OK
  return E_OK;
}

// EOF
