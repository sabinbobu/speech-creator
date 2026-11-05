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
/// \file  Adc_Drv.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef ADC_DRV_2021_03_17_H_
#define ADC_DRV_2021_03_17_H_


#include <Std_Types.h>
#include <../Cdd/CddAdc/Gen/CddAdc_Types.h>

Std_ReturnType CddAdc_Drv_InitAdc(tsCddAdc_CfgData sCfgData);
uint16 CddAdc_Drv_GetAdcRawValue(uint8 ucInputIx);

#endif // ADC_DRV_2021_03_17_H_
