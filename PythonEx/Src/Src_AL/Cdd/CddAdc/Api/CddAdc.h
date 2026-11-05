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
/// \file  CddAdc.h
///
/// \brief
///
//-----------------------------------------------------------------------------

#include <Std_Types.h>

#ifndef CDD_ADC_2021_03_16_H_
#define CDD_ADC_2021_03_16_H_

void CddAdc_AdcInit(void);
Std_ReturnType Adc_ReadGroup(uint8 ucAdcIn, uint16* const unAdcValue);

#endif // CDD_ADC_2021_03_16_H_

// EOF
