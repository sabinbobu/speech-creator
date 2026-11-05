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
/// \file  Adc_Drv.c
///
/// \brief Adc Driver header file (low access to the ADC pheripheric)
///
/// \author Stefan Tyirean (f75617c)
///         mailto: stefan.tyirean[at]marelli.com
///
/// \Date April 2021
///
//-----------------------------------------------------------------------------
#ifndef ADC_DRV_2021_03_17_H_
#define ADC_DRV_2021_03_17_H_

#include <Std_Types.h>
#include "Adc_TargetTypes.h"
#include <Adc.h>
#include <Cfg/Cfg.h>

#if !defined(UNIT_TEST)
#if defined CFG_SUPORT_ADC_EOL_CALIBRATION
#define ADC_DRV_SELF_CALIBRATION_OP   STD_OFF
#define ADC_DRV_EOL_CALIBRATION_OP    STD_ON
#else
#define ADC_DRV_SELF_CALIBRATION_OP   STD_ON
#define ADC_DRV_EOL_CALIBRATION_OP    STD_OFF
#endif
#else
#define ADC_DRV_SELF_CALIBRATION_OP   0xFFu
#define ADC_DRV_EOL_CALIBRATION_OP    0xFFu
#endif

Std_ReturnType Adc_Drv_InitAdc(CONST_AL tsAdc_CfgData* CONST_AL psCfgData);
uint16 Adc_Drv_GetAdcRawValue(uint8 ucInputIx);

#endif // ADC_DRV_2021_03_17_H_

// EOF
