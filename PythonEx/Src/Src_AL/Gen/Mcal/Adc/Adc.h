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
/// \file  Adc.h
///
/// \brief Mcal Adc interfaces/runnables
///
/// \author Stefan Tyirean (f75617c)
///         mailto: stefan.tyirean[at]marelli.com
///
/// \Date April 2021
///
//-----------------------------------------------------------------------------

#include <Std_Types.h>
#include <Adc_TargetTypes.h>
#include <AL_Helper.h>

#ifndef CDD_ADC_2021_03_16_H_
#define CDD_ADC_2021_03_16_H_

#if defined(__cplusplus)
extern "C"
{
#endif

  // Adc data structure for ADC init procedure
  extern CONST_AL tsAdc_CfgData Adc_sAdcCfgData;

  // ADC init (EcuM in start-up phase)
  void Adc_Init(CONST_AL tsAdc_CfgData* CONST_AL psAdcCfgData);
  // Adc data read by IoHwAb base on specific input (pin)
  Std_ReturnType Adc_ReadGroup(uint8 ucAdcIn, uint16* CONST_AL unAdcValue);

#if defined(__cplusplus)
}
#endif

#endif // CDD_ADC_2021_03_16_H_

// EOF
