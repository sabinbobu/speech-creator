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
/// \file  CddAdc_Cfg.h
///
/// \brief
///
//-----------------------------------------------------------------------------

#include <../Cdd/CddAdc/Gen/CddAdc_Mac.h>
#include <../Cdd/CddAdc/Gen/CddAdc_Types.h>

BEGIN_LPIT_INSTANCE_CFG_MAP
  LPIT_INST_CFG(LPIT0, FALSE, FALSE)
END_LPIT_INSTANCE_CFG_MAP

BEGIN_LPIT_CHN_MAP_CFG
  LPIT_CHN_MAP_CFG(LPIT0,   0u,   eLpit32PeriodicTimer,   16000u,  eExternalTiggers,   eTimerCh0,    FALSE,    FALSE,  FALSE,  FALSE,  FALSE)
END_LPIT_CHN_MAP_CFG

BEGIN_TRIGMUX_CHN_CFG
  TRGMUX_CHN_MAP_CFG(TRGMUX,  eTRGMUX_TRIG_SOURCE_LPIT_CH0,   eTRGMUX_TARGET_MODULE_PDB0_TRG_IN,    FALSE)
  TRGMUX_CHN_MAP_CFG(TRGMUX,  eTRGMUX_TRIG_SOURCE_LPIT_CH0,   eTRGMUX_TARGET_MODULE_PDB1_TRG_IN,    FALSE)
END_TRIGMUX_CHN_CFG

BEGIN_ADC_INSTANCE_CFG_MAP
  ADC_INST_CFG(ADC0, eADC_CLK_DIVIDE_2, 20u, eADC_RESOLUTION_12BIT, eADC_CLK_ALT_1, eADC_TRIGGER_HARDWARE, eADC_PRETRIGGER_SEL_PDB, eADC_TRIGGER_SEL_PDB, TRUE, eADC_VOLTAGEREF_VREF, FALSE, FALSE, TRUE, eADC_AVERAGE_32)
  ADC_INST_CFG(ADC1, eADC_CLK_DIVIDE_2, 20u, eADC_RESOLUTION_12BIT, eADC_CLK_ALT_1, eADC_TRIGGER_HARDWARE, eADC_PRETRIGGER_SEL_PDB, eADC_TRIGGER_SEL_PDB, TRUE, eADC_VOLTAGEREF_VREF, FALSE, FALSE, TRUE, eADC_AVERAGE_32)
END_ADC_INSTANCE_CFG_MAP

BEGIN_PDB_INSTANCE_CFG_MAP
  PDB_INST_CFG(PDB0,  eImidiately,  FALSE,  FALSE,    eMulBy16,   eMultiplier20,    eTrigMuxIn,     FALSE,      240u,     240u,     TRUE)
  PDB_INST_CFG(PDB1,  eImidiately,  FALSE,  FALSE,    eMulBy16,   eMultiplier20,    eTrigMuxIn,     FALSE,      240u,     240u,     TRUE)
END_PDB_INSTANCE_CFG_MAP

BEGIN_ADC_CHN_MAP_CFG
  ADC_IN_CH_MAP_CFG(eADC_PCB,       ADC1,     0u,     eExtCh3,    FALSE,      PDB1,     0u,      10u,     TRUE,     FALSE,    TRUE,     &CddAdc_aulAdcChData[11])
  ADC_IN_CH_MAP_CFG(eADC_EXT_1,     ADC0,     0u,     eExtCh11,   FALSE,      PDB0,     0u,      20u,     TRUE,     FALSE,    TRUE,     &CddAdc_aulAdcChData[0] )
  ADC_IN_CH_MAP_CFG(eADC_EXT_2,     ADC0,     1u,     eExtCh9,    FALSE,      PDB0,     0u,       0u,     TRUE,     TRUE,     TRUE,     &CddAdc_aulAdcChData[1] )
  ADC_IN_CH_MAP_CFG(eADC_EXT_3,     ADC0,     2u,     eExtCh8,    FALSE,      PDB0,     0u,       0u,     TRUE,     TRUE,     TRUE,     &CddAdc_aulAdcChData[2] )
  ADC_IN_CH_MAP_CFG(eADC_EXT_4,     ADC0,     3u,     eExtCh15,   FALSE,      PDB0,     0u,       0u,     TRUE,     TRUE,     TRUE,     &CddAdc_aulAdcChData[3] )
  ADC_IN_CH_MAP_CFG(eADC_EXT_5,     ADC0,     4u,     eExtCh14,   FALSE,      PDB0,     0u,       0u,     TRUE,     TRUE,     TRUE,     &CddAdc_aulAdcChData[4] )
  ADC_IN_CH_MAP_CFG(eADC_EXT_6,     ADC0,     5u,     eExtCh13,   FALSE,      PDB0,     0u,       0u,     TRUE,     TRUE,     TRUE,     &CddAdc_aulAdcChData[5] )
  ADC_IN_CH_MAP_CFG(eADC_EXT_7,     ADC0,     6u,     eExtCh12,   FALSE,      PDB0,     0u,       0u,     TRUE,     TRUE,     TRUE,     &CddAdc_aulAdcChData[6] )
  ADC_IN_CH_MAP_CFG(eADC_EXT_8,     ADC0,     7u,     eExtCh2,    FALSE,      PDB0,     0u,       0u,     TRUE,     TRUE,     TRUE,     &CddAdc_aulAdcChData[7] )
  ADC_IN_CH_MAP_CFG(eADC_EXT_9,     ADC1,     1u,     eExtCh0,    FALSE,      PDB1,     0u,       0u,     TRUE,     TRUE,     TRUE,     &CddAdc_aulAdcChData[12])
  ADC_IN_CH_MAP_CFG(eADC_EXT_10,    ADC1,     2u,     eExtCh8,    FALSE,      PDB1,     0u,       0u,     TRUE,     TRUE,     TRUE,     &CddAdc_aulAdcChData[13])
  ADC_IN_CH_MAP_CFG(eADC_EXT_11,    ADC0,     8u,     eExtCh10,   FALSE,      PDB0,     1u,     120u,     TRUE,     FALSE,    TRUE,     &CddAdc_aulAdcChData[8] )
  ADC_IN_CH_MAP_CFG(eADC_EXT_12,    ADC1,     3u,     eExtCh14,   FALSE,      PDB1,     0u,       0u,     TRUE,     TRUE,     TRUE,     &CddAdc_aulAdcChData[14])
  ADC_IN_CH_MAP_CFG(eADC_EXT_13,    ADC1,     4u,     eExtCh9,    FALSE,      PDB1,     0u,       0u,     TRUE,     TRUE,     TRUE,     &CddAdc_aulAdcChData[15])
  ADC_IN_CH_MAP_CFG(eADC_EXT_14,    ADC1,     5u,     eExtCh13,   FALSE,      PDB1,     0u,       0u,     TRUE,     TRUE,     TRUE,     &CddAdc_aulAdcChData[16])
  ADC_IN_CH_MAP_CFG(eADC_VBAT,      ADC1,     6u,     eExtCh6,    FALSE,      PDB1,     0u,       0u,     TRUE,     TRUE,     TRUE,     &CddAdc_aulAdcChData[17])
  ADC_IN_CH_MAP_CFG(eADC_ST_SENS,   ADC1,     7u,     eExtCh7,    FALSE,      PDB1,     0u,       0u,     TRUE,     TRUE,     TRUE,     &CddAdc_aulAdcChData[18])
  ADC_IN_CH_MAP_CFG(eADC_LR,        ADC1,     8u,     eExtCh2,    FALSE,      PDB1,     1u,     130u,     TRUE,     FALSE,    TRUE,     &CddAdc_aulAdcChData[19])
  ADC_IN_CH_MAP_CFG(eADC_VCCX1,     ADC1,     9u,     eExtCh1,    FALSE,      PDB1,     1u,       0u,     TRUE,     TRUE,     TRUE,     &CddAdc_aulAdcChData[20])
  ADC_IN_CH_MAP_CFG(eADC_VCCX2,     ADC1,    10u,     eExtCh10,   FALSE,      PDB1,     1u,       0u,     TRUE,     TRUE,     TRUE,     &CddAdc_aulAdcChData[21])
  ADC_IN_CH_MAP_CFG(eADC_SENSE_1_2, ADC0,     9u,     eExtCh1,    FALSE,      PDB0,     1u,       0u,     TRUE,     TRUE,     TRUE,     &CddAdc_aulAdcChData[9] )
  ADC_IN_CH_MAP_CFG(eADC_SENSE_3,   ADC1,    11u,     eExtCh15,   FALSE,      PDB1,     1u,       0u,     TRUE,     TRUE,     TRUE,     &CddAdc_aulAdcChData[22])
  ADC_IN_CH_MAP_CFG(eADC_OUT_FCT,   ADC0,    10u,     eExtCh0,    FALSE,      PDB0,     1u,       0u,     TRUE,     TRUE,     TRUE,     &CddAdc_aulAdcChData[10])
END_ADC_CHN_MAP_CFG

// EOF
