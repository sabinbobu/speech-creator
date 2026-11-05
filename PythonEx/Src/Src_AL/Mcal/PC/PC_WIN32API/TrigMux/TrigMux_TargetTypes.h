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
/// \file  TrigMux_TargetTypes.h
///
/// \brief TrigMux Driver type definitions (low access to the TrigMux pheripheric)
///
/// \author Stefan Tyirean (f75617c)
///         mailto: stefan.tyirean[at]marelli.com
///
/// \Date April 2021
///
//-----------------------------------------------------------------------------
#ifndef TRIGMUX_TYPES_2021_03_16_H_
#define TRIGMUX_TYPES_2021_03_16_H_


//====================================================================
// Include files
//====================================================================

#include <Std_Types.h>
#include <AL_Helper.h>
#include <Device_TargetTypes.h>

//====================================================================
// Type data definitions
//====================================================================

typedef enum
{
  eTRGMUX_TRIG_SOURCE_DISABLED = 0u,
  eTRGMUX_TRIG_SOURCE_LPIT_CH0 = 17u,
  eTRGMUX_TRIG_SOURCE_LPIT_CH1 = 18u,
  eTRGMUX_TRIG_SOURCE_LPIT_CH2 = 19u,
  eTRGMUX_TRIG_SOURCE_LPIT_CH3 = 20u,
  eTRGMUX_TRIG_SOURCE_LPTMR0 = 21u,
  eTRGMUX_TRIG_SOURCE_FTM0_INIT_TRIG = 22u,
  eTRGMUX_TRIG_SOURCE_FTM0_EXT_TRIG = 23u,
  eTRGMUX_TRIG_SOURCE_FTM1_INIT_TRIG = 24u,
  eTRGMUX_TRIG_SOURCE_FTM1_EXT_TRIG = 25u,
  eTRGMUX_TRIG_SOURCE_FTM2_INIT_TRIG = 26u,
  eTRGMUX_TRIG_SOURCE_FTM2_EXT_TRIG = 27u,
  eTRGMUX_TRIG_SOURCE_FTM3_INIT_TRIG = 28u,
  eTRGMUX_TRIG_SOURCE_FTM3_EXT_TRIG = 29u,
  eTRGMUX_TRIG_SOURCE_ADC0_SC1A_COCO = 30u,
  eTRGMUX_TRIG_SOURCE_ADC0_SC1B_COCO = 31u,
  eTRGMUX_TRIG_SOURCE_ADC1_SC1A_COCO = 32u,
  eTRGMUX_TRIG_SOURCE_ADC1_SC1B_COCO = 33u,
  eTRGMUX_TRIG_SOURCE_PDB0_CH0_TRIG = 34u,
  eTRGMUX_TRIG_SOURCE_PDB0_PULSE_OUT = 36u,
  eTRGMUX_TRIG_SOURCE_PDB1_CH0_TRIG = 37u,
  eTRGMUX_TRIG_SOURCE_PDB1_PULSE_OUT = 39u,
  eTRGMUX_TRIG_SOURCE_SIM_SW_TRIG = 63u
}teTrigMux_TriggerMuxSource;


typedef enum
{
  eTRGMUX_TARGET_MODULE_TRGMUX_OUT0 = 4u,
  eTRGMUX_TARGET_MODULE_TRGMUX_OUT1 = 5u,
  eTRGMUX_TARGET_MODULE_TRGMUX_OUT2 = 6u,
  eTRGMUX_TARGET_MODULE_TRGMUX_OUT3 = 7u,
  eTRGMUX_TARGET_MODULE_TRGMUX_OUT4 = 8u,
  eTRGMUX_TARGET_MODULE_TRGMUX_OUT5 = 9u,
  eTRGMUX_TARGET_MODULE_TRGMUX_OUT6 = 10u,
  eTRGMUX_TARGET_MODULE_TRGMUX_OUT7 = 11u,
  eTRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA0 = 12u,
  eTRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA1 = 13u,
  eTRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA2 = 14u,
  eTRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA3 = 15u,
  eTRGMUX_TARGET_MODULE_ADC1_ADHWT_TLA0 = 16u,
  eTRGMUX_TARGET_MODULE_ADC1_ADHWT_TLA1 = 17u,
  eTRGMUX_TARGET_MODULE_ADC1_ADHWT_TLA2 = 18u,
  eTRGMUX_TARGET_MODULE_ADC1_ADHWT_TLA3 = 19u,
  eTRGMUX_TARGET_MODULE_CMP0_SAMPLE = 28u,
  eTRGMUX_TARGET_MODULE_PDB0_TRG_IN = 56u,
  eTRGMUX_TARGET_MODULE_PDB1_TRG_IN = 60u,
  eTRGMUX_TARGET_MODULE_LPTMR0_ALT0 = 100u
}teTrigMux_TriggerMuxTarget;

typedef struct
{
  uint8 ucTrigMuxInst;
  teTrigMux_TriggerMuxSource eTrigSource;
  teTrigMux_TriggerMuxTarget eTrigTarget;
  boolean boLock;
}tsTrigMux_TrigMuxCfg;

typedef struct
{
  CONST_AL tsTrigMux_TrigMuxCfg* CONST_AL psTrigMuxCfg;
  uint8 ucCfgLength;
}tsTrigMux_TrigMuxCfgMap;


typedef struct
{
  tsTrigMux_TrigMuxCfgMap sTrigMuxInstanceCfg;
}tsTrigMux_CfgData;

#endif // TRIGMUX_TARGETYPES_2021_03_16_H_

// EOF
