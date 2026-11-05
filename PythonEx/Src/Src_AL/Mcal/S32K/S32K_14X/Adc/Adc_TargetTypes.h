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
/// \file  Adc_TargetTypes.h
///
/// \brief Adc Types header file
///
/// \author Stefan Tyirean (f75617c)
///         mailto: stefan.tyirean[at]marelli.com
///
/// \Date April 2021
///
//-----------------------------------------------------------------------------
#ifndef ADC_TYPES_2021_03_16_H_
#define ADC_TYPES_2021_03_16_H_

#include "Std_Types.h"
#include <AL_Helper.h>

typedef enum
{
  eAdc_Ok = 0u,
  eAdc_Nok
}teAdc_AdcErrorStat;

typedef enum
{
  eADC_PCB = 0u,
  eADC_EXT_1,
  eADC_EXT_2,
  eADC_EXT_3,
  eADC_EXT_4,
  eADC_EXT_5,
  eADC_EXT_6,
  eADC_EXT_7,
  eADC_EXT_8,
  eADC_EXT_9,
  eADC_EXT_10,
  eADC_EXT_11,
  eADC_EXT_12,
  eADC_EXT_13,
  eADC_EXT_14,
  eADC_VBAT,
  eADC_ST_SENS,
  eADC_LR,
  eADC_VCCX1,
  eADC_VCCX2,
  eADC_SENSE_1_2,
  eADC_SENSE_3,
  eADC_OUT_FCT,
  eADC_DC_OUT_1,
}teAdc_AdcChannelIx;

typedef enum
{
  eAdcExtCh0 = 0u,
  eAdcExtCh1 = 1u,
  eAdcExtCh2 = 2u,
  eAdcExtCh3 = 3u,
  eAdcExtCh4 = 4u,
  eAdcExtCh5 = 5u,
  eAdcExtCh6 = 6u,
  eAdcExtCh7 = 7u,
  eAdcExtCh8 = 8u,
  eAdcExtCh9 = 9u,
  eAdcExtCh10 = 10u,
  eAdcExtCh11 = 11u,
  eAdcExtCh12 = 12u,
  eAdcExtCh13 = 13u,
  eAdcExtCh14 = 14u,
  eAdcExtCh15 = 15u,
  eAdcIntCh0 = 21u,
  eAdcIntCh1 = 22u,
  eAdcIntCh2 = 23u,
  eAdcBandGap = 27u,
  eAdcIntCh3 = 28u,
  eAdcVrefH = 29u,
  eAdcVrefL = 30u,
  eAdcExtCh16 = 32u,
  eAdcExtCh17 = 33u,
  eAdcExtCh18 = 34u,
  eAdcExtCh19 = 35u,
  eAdcExtCh20 = 36u,
  eAdcExtCh21 = 37u,
  eAdcExtCh22 = 38u,
  eAdcExtCh23 = 39u,
  eAdcExtCh24 = 40u,
  eAdcExtCh25 = 41u,
  eAdcExtCh26 = 42u,
  eAdcExtCh27 = 42u,
  eAdcExtCh28 = 44u,
  eAdcExtCh29 = 45u,
  eAdcExtCh30 = 46u,
  eAdcExtCh32 = 47u,
  eAdcDisabled = 63u
}teAdc_InChMap;

typedef enum
{
  eAdc_Inst_0 = 0u,
  eAdc_Inst_1,
}teAdc_AdcInstance;

typedef struct
{
  teAdc_AdcChannelIx eInSelAdc;
  uint8 ucAdcInst;
  uint8 ucAdcCh;
  teAdc_InChMap eInCh;
  boolean boIntEnbl;
  uint32* CONST_AL pulAdcData;
}tsAdc_AdcInputCfg;

// Clock division setup
typedef enum
{
  eADC_CLK_DIVIDE_1 = 0u,   /*!< Input clock divided by 1. */
  eADC_CLK_DIVIDE_2 = 1u,   /*!< Input clock divided by 2. */
  eADC_CLK_DIVIDE_4 = 2u,   /*!< Input clock divided by 4. */
  eADC_CLK_DIVIDE_8 = 3u    /*!< Input clock divided by 8. */
} teAdc_AdcClkCfg;

// Adc Resolution setup
typedef enum
{
  eADC_RESOLUTION_8BIT   = 0u,   /*!< 8-bit resolution mode */
  eADC_RESOLUTION_12BIT  = 1u,   /*!< 12-bit resolution mode */
  eADC_RESOLUTION_10BIT  = 2u    /*!< 10-bit resolution mode */
} teAdc_AdcResCfg;

// Adc Input Clk Setup
typedef enum
{
  eADC_CLK_ALT_1 = 0u,  /*!< Input clock alternative 1. */
  eADC_CLK_ALT_2 = 1u,  /*!< Input clock alternative 2. */
  eADC_CLK_ALT_3 = 2u,  /*!< Input clock alternative 3. */
  eADC_CLK_ALT_4 = 3u   /*!< Input clock alternative 4. */
} teAdc_AdcInClkCfg;

// Adc Input Trigger Setup
typedef enum
{
  eADC_TRIGGER_SOFTWARE = 0u,   /*!< Software trigger. */
  eADC_TRIGGER_HARDWARE = 1u    /*!< Hardware trigger. */
} teAdc_AdcInTrigCfg;

// Adc Input PreTrigger Selector Setup
typedef enum
{
  eADC_PRETRIGGER_SEL_PDB = 0u,      /*!< PDB pretrigger selected. */
  eADC_PRETRIGGER_SEL_TRGMUX = 1u,   /*!< TRGMUX pretrigger selected. */
  eADC_PRETRIGGER_SEL_SW = 2u        /*!< Software pretrigger selected. */
} teAdc_AdcInPreTrigSelCfg;

// Adc Input Trigger Selector Setup
typedef enum
{
  eADC_TRIGGER_SEL_PDB = 0u,      /*!< PDB trigger selected. */
  eADC_TRIGGER_SEL_TRGMUX = 1u    /*!< TRGMUX trigger selected. */
} teAdc_AdcInTrigSelCfg;

// Adc Reference Voltage Setup
typedef enum
{
  eADC_VOLTAGEREF_VREF = 0u,    /*!< VrefH and VrefL as Voltage reference. */
  eADC_VOLTAGEREF_VALT = 1u     /*!< ValtH and ValtL as Voltage reference. */
} teAdc_AdcRefVoltCfg;

typedef enum
{
  eADC_AVERAGE_4 = 0u,      /*!< Hardware average of 4 samples. */
  eADC_AVERAGE_8 = 1u,      /*!< Hardware average of 8 samples. */
  eADC_AVERAGE_16 = 2u,     /*!< Hardware average of 16 samples. */
  eADC_AVERAGE_32 = 3u      /*!< Hardware average of 32 samples. */
} teAdc_AdcAverageCfg;

typedef struct
{
  uint8 ucAdcInst;                              /*!< Adc Instance */
  teAdc_AdcClkCfg eClkDiv;                      /*!< Divider of the input clock for the ADC */
  uint8 ulSampleTime;                           /*!< Sample time in AD Clocks */
  teAdc_AdcResCfg eResolution;                  /*!< ADC resolution (8,10,12 bit) */
  teAdc_AdcInClkCfg eInputClock;                /*!< Input clock source */
  teAdc_AdcInTrigCfg eTrigger;                  /*!< ADC trigger type (software, hardware) - affects only the first control channel */
  teAdc_AdcInPreTrigSelCfg ePreTriggerSel;      /*!< Pretrigger source selected from Trigger Latching and Arbitration Unit - affects only the first 4 control channels */
  teAdc_AdcInTrigSelCfg eTriggerSel;            /*!< Trigger source selected from Trigger Latching and Arbitration Unit */
  boolean boDmaEnable;                          /*!< Enable DMA for the ADC */
  teAdc_AdcRefVoltCfg eVoltageRef;              /*!< Voltage reference used */
  boolean boContinuousConvEnable;               /*!< Enable Continuous conversions */
  boolean boSupplyMonitoringEnable;             /*!< Only available for ADC 0. Enable internal supply monitoring - enables measurement of ADC_INPUTCHAN_SUPPLY_ sources. */
  boolean boAvgEnable;                          /*!< Average Enable */
  teAdc_AdcAverageCfg eAverageCfg;              /*!< Average Cfg */
  uint32 ulAdcFreq;                             //LDM ADC pheripheral clock 40 MHz
  boolean boEolCalib;                           //ADC EOL self calibration
  boolean (*pfCalibrationParm)(uint32* pvStart);  // Calibration struct getter 
} tsAdc_AdcInstanceCfg;

typedef struct
{
  uint32* pulAdc0Source;      /*!<Adc0 Dma Source Address*/
  uint32* pulAdc0Target;      /*!<Adc0 Dma Destination Address*/
  uint16 unAdc0DataSize;      /*!<Adc0 Dma transfer size*/
  uint32* pulAdc1Source;      /*!<Adc1 Dma Source Address*/
  uint32* pulAdc1Target;      /*!<Adc1 Dma Source Address*/
  uint16 unAdc1DataSize;      /*!<Adc1 Dma transfer size*/
}tsAdc_DmaTriggerCfg;

typedef struct
{
  CONST_AL tsAdc_AdcInstanceCfg* CONST_AL psAdcInstCfg;   /*!<Adc Instance config*/
  uint8 ucCfgLength;                                      /*!<Adc Instance config length*/
}tsAdc_AdcInstCfgMap;

typedef struct
{
  CONST_AL tsAdc_AdcInputCfg* CONST_AL psAdcInCfg;        /*!<Adc input channel config*/
  uint8 ucCfgLength;                                      /*!<Adc input channel config length*/
}tsAdc_AdcChInCfgMap;

typedef struct
{
  uint32* CONST_AL pulAdcDataOut;                         /*!<Adc RAM data conversion*/
  uint8 ucCfgLength;                                      /*!<Adc RAM data conversion length*/
}tsAdc_AdcDataOutMap;


typedef struct
{
  tsAdc_AdcInstCfgMap sAdcInstanceCfg;            /*!<Adc Instance config*/
  tsAdc_AdcChInCfgMap sAdcInputChCfg;             /*!<Adc input channel config*/
  tsAdc_AdcDataOutMap sAdcDataOut;                /*!<Adc RAM data conversion*/
}tsAdc_CfgData;

#endif // CDD_ADC_TYPES_2021_03_16_H_

// EOF
