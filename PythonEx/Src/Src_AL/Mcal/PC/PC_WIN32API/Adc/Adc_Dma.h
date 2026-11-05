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
/// \file  Adc_Dma.h
///
/// \brief Adc DMA setup header file
///
/// \author Stefan Tyirean (f75617c)
///         mailto: stefan.tyirean[at]marelli.com
///
/// \Date April 2021
///
//-----------------------------------------------------------------------------
#ifndef DMA_JOB_2021_03_16_H_
#define DMA_JOB_2021_03_16_H_

//====================================================================
// Include files
//====================================================================

#include <Std_Types.h>
#include "Adc_TargetTypes.h"
#include <Adc.h>

//====================================================================
// Function declarations
//====================================================================

Std_ReturnType Adc_Dma_InitDmaJob(CONST_AL tsAdc_CfgData* CONST_AL psAdcCfgData);

#endif // DMA_JOB_2021_03_16_H_

// EOF
