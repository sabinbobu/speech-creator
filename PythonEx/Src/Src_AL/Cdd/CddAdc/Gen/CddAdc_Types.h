////*****************************************************************************
//// (C) Automotive Lighting Reutlingen GmbH
////     Tuebinger Strasse 123, 72762 Reutlingen, Germany
////
//// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
//// This work shall not be copied, reproduced, used, modified, transferred
//// or its information shall not be disclosed without the prior written
//// authorization of Automotive Lighting Reutlingen GmbH.
////*****************************************************************************
////-----------------------------------------------------------------------------
///// \file  CddAdc_Types.h
/////
///// \brief
/////
////-----------------------------------------------------------------------------
//#ifndef CDD_ADC_TYPES_2021_03_16_H_
//#define CDD_ADC_TYPES_2021_03_16_H_
//
//
//#include <Std_Types.h>
//#include <../Cdd/CddAdc/S32K/S32K_14X/_146/CddAdc_S32K_14X_146_Reg_Types.h>
//
//
//typedef volatile uint32 vuint32;
//
//typedef enum
//{
//  eAdc_Ok = 0U,
//  eAdc_Nok
//}teCddAdc_AdcErrorStat;
//
//typedef enum
//{
//  eADC_PCB = 0u,
//  eADC_EXT_1,
//  eADC_EXT_2,
//  eADC_EXT_3,
//  eADC_EXT_4,
//  eADC_EXT_5,
//  eADC_EXT_6,
//  eADC_EXT_7,
//  eADC_EXT_8,
//  eADC_EXT_9,
//  eADC_EXT_10,
//  eADC_EXT_11,
//  eADC_EXT_12,
//  eADC_EXT_13,
//  eADC_EXT_14,
//  eADC_VBAT,
//  eADC_ST_SENS,
//  eADC_LR,
//  eADC_VCCX1,
//  eADC_VCCX2,
//  eADC_SENSE_1_2,
//  eADC_SENSE_3,
//  eADC_OUT_FCT,
//}teCddAdc_AdcChannelIx;
//
//typedef enum
//{
//  eExtCh0 = 0u,
//  eExtCh1 = 1u,
//  eExtCh2 = 2u,
//  eExtCh3 = 3u,
//  eExtCh4 = 4u,
//  eExtCh5 = 5u,
//  eExtCh6 = 6u,
//  eExtCh7 = 7u,
//  eExtCh8 = 8u,
//  eExtCh9 = 9u,
//  eExtCh10 = 10u,
//  eExtCh11 = 11u,
//  eExtCh12 = 12u,
//  eExtCh13 = 13u,
//  eExtCh14 = 14u,
//  eExtCh15 = 15u,
//  eIntCh0 = 21u,
//  eIntCh1 = 22u,
//  eIntCh2 = 23u,
//  eBandGap = 27u,
//  eIntCh3 = 28u,
//  eVrefH = 29u,
//  eVrefL = 30u,
//  eExtCh16 = 32u,
//  eExtCh17 = 33u,
//  eExtCh18 = 34u,
//  eExtCh19 = 35u,
//  eExtCh20 = 36u,
//  eExtCh21 = 37u,
//  eExtCh22 = 38u,
//  eExtCh23 = 39u,
//  eExtCh24 = 40u,
//  eExtCh25 = 41u,
//  eExtCh26 = 42u,
//  eExtCh27 = 42u,
//  eExtCh28 = 44u,
//  eExtCh29 = 45u,
//  eExtCh30 = 46u,
//  eExtCh32 = 47u,
//  eDisabled = 63u
//}teCddAdc_InChMap;
//
//typedef enum
//{
//  eAdc_Inst_0 = 0u,
//  eAdc_Inst_1,
//}teCddAdc_AdcInstance;
//
//typedef struct
//{
//  teCddAdc_AdcChannelIx eInSelAdc;
//  tsCddAdc_AdcReg* const psAdcInst;
//  uint8 ucAdcCh;
//  teCddAdc_InChMap eInCh;
//  boolean boIntEnbl;
//  tsCddAdc_PdbReg* const psPdbInst;
//  uint8 ucPdbChannel;
//  uint32 ulPdbChnInDelayOffset_Reg;
//  boolean boPdbTriggerOutput;
//  boolean boPdbBack2Back;
//  boolean boPdbAdcChnEnbl;
//  uint32* const pulAdcData;
//}tsCddAdc_AdcInputCfg;
//
//// Clock division setup
//typedef enum
//{
//  eADC_CLK_DIVIDE_1 = 0u,   /*!< Input clock divided by 1. */
//  eADC_CLK_DIVIDE_2 = 1u,   /*!< Input clock divided by 2. */
//  eADC_CLK_DIVIDE_4 = 2u,   /*!< Input clock divided by 4. */
//  eADC_CLK_DIVIDE_8 = 3u    /*!< Input clock divided by 8. */
//} teCddAdc_AdcClkCfg;
//
//// Adc Resolution setup
//typedef enum
//{
//  eADC_RESOLUTION_8BIT   = 0u,    /*!< 8-bit resolution mode */
//  eADC_RESOLUTION_12BIT  = 1u,   /*!< 12-bit resolution mode */
//  eADC_RESOLUTION_10BIT  = 2u    /*!< 10-bit resolution mode */
//} teCddAdc_AdcResCfg;
//
//// Adc Input Clk Setup
//typedef enum
//{
//  eADC_CLK_ALT_1 = 0u,  /*!< Input clock alternative 1. */
//  eADC_CLK_ALT_2 = 1u,  /*!< Input clock alternative 2. */
//  eADC_CLK_ALT_3 = 2u,  /*!< Input clock alternative 3. */
//  eADC_CLK_ALT_4 = 3u   /*!< Input clock alternative 4. */
//} teCddAdc_AdcInClkCfg;
//
//// Adc Input Trigger Setup
//typedef enum
//{
//  eADC_TRIGGER_SOFTWARE = 0u,   /*!< Software trigger. */
//  eADC_TRIGGER_HARDWARE = 1u    /*!< Hardware trigger. */
//} teCddAdc_AdcInTrigCfg;
//
//// Adc Input PreTrigger Selector Setup
//typedef enum
//{
//  eADC_PRETRIGGER_SEL_PDB = 0u,      /*!< PDB pretrigger selected. */
//  eADC_PRETRIGGER_SEL_TRGMUX = 1u,   /*!< TRGMUX pretrigger selected. */
//  eADC_PRETRIGGER_SEL_SW = 2u        /*!< Software pretrigger selected. */
//} teCddAdc_AdcInPreTrigSelCfg;
//
//// Adc Input Trigger Selector Setup
//typedef enum
//{
//  eADC_TRIGGER_SEL_PDB = 0u,      /*!< PDB trigger selected. */
//  eADC_TRIGGER_SEL_TRGMUX = 1u    /*!< TRGMUX trigger selected. */
//} teCddAdc_AdcInTrigSelCfg;
//
//// Adc Reference Voltage Setup
//typedef enum
//{
//  eADC_VOLTAGEREF_VREF = 0u,    /*!< VrefH and VrefL as Voltage reference. */
//  eADC_VOLTAGEREF_VALT = 1u     /*!< ValtH and ValtL as Voltage reference. */
//} teCddAdc_AdcRefVoltCfg;
//
//typedef enum
//{
//  eADC_AVERAGE_4 = 0u,     /*!< Hardware average of 4 samples. */
//  eADC_AVERAGE_8 = 1u,     /*!< Hardware average of 8 samples. */
//  eADC_AVERAGE_16 = 2u,     /*!< Hardware average of 16 samples. */
//  eADC_AVERAGE_32 = 3u      /*!< Hardware average of 32 samples. */
//} teCddAdc_AdcAverageCfg;
//
//typedef enum
//{
//  eImidiately = 0u,
//  eModulusMatch = 1u,
//  eTriggered = 2u,
//  eBoth = 3u
//}teCddAdc_PdbLdModCfg;
//
//typedef enum
//{
//  eMulBy1 = 0u,
//  eMulBy2 = 1u,
//  eMulBy4 = 2u,
//  eMulBy8 = 3u,
//  eMulBy16 = 4u,
//  eMulBy32 = 5u,
//  eMulBy64 = 6u,
//  eMulby128 = 7u
//}teCddAdc_PdbPrescalerCfg;
//
//typedef enum
//{
//  eMultiplier1 = 0u,
//  eMultiplier10 = 1u,
//  eMultiplier20 = 2u,
//  eMultiplier40 = 3u
//}teCddAdc_PdbMultiplierCfg;
//
//typedef enum
//{
//  eTrigMuxIn = 0u,
//  eTrigSw = 15u
//}teCddAdc_PdbTriggerCfg;
//
//typedef struct
//{
//  tsCddAdc_PdbReg* const psPdbInst;
//  teCddAdc_PdbLdModCfg eLdMod;
//  boolean boIntEnable;
//  boolean boDmaEnable;
//  teCddAdc_PdbPrescalerCfg ePrescaler;
//  teCddAdc_PdbMultiplierCfg eMul;
//  teCddAdc_PdbTriggerCfg eTrigger;
//  boolean boContinousMode;
//  uint32 ulPdbPeriod_Reg;
//  uint32 ulIntDmaTrigTime_Reg;
//  boolean boModEnbl;
//}tsCddAdc_PdbInstanceCfg;
//
//typedef struct
//{
//  tsCddAdc_AdcReg* const psAdcInst;            /*!< Adc Instance */
//  teCddAdc_AdcClkCfg eClkDiv;                  /*!< Divider of the input clock for the ADC */
//  uint8 ulSampleTime;                          /*!< Sample time in AD Clocks */
//  teCddAdc_AdcResCfg eResolution;              /*!< ADC resolution (8,10,12 bit) */
//  teCddAdc_AdcInClkCfg eInputClock;            /*!< Input clock source */
//  teCddAdc_AdcInTrigCfg eTrigger;              /*!< ADC trigger type (software, hardware) - affects only the first control channel */
//  teCddAdc_AdcInPreTrigSelCfg ePreTriggerSel;  /*!< Pretrigger source selected from Trigger Latching and Arbitration Unit - affects only the first 4 control channels */
//  teCddAdc_AdcInTrigSelCfg eTriggerSel;        /*!< Trigger source selected from Trigger Latching and Arbitration Unit */
//  boolean boDmaEnable;                         /*!< Enable DMA for the ADC */
//  teCddAdc_AdcRefVoltCfg eVoltageRef;          /*!< Voltage reference used */
//  boolean boContinuousConvEnable;              /*!< Enable Continuous conversions */
//  boolean boSupplyMonitoringEnable;            /*!< Only available for ADC 0. Enable internal supply monitoring - enables measurement of ADC_INPUTCHAN_SUPPLY_ sources. */
//  boolean boAvgEnable;                         /*!< Average Enable */
//  teCddAdc_AdcAverageCfg eAverageCfg;          /*!< Average Cfg */
//} tsCddAdc_AdcInstanceCfg;
//
//typedef struct
//{
//  tsCddAdc_LpitReg* const psLpitInst;
//  boolean boEnableDebug;
//  boolean boEnableDoze;
//}tsCddAdc_LpitInstanceCfg;
//
//typedef enum
//{
//  eLpit32PeriodicTimer = 0u,
//  eDual16PeriodicTimer = 1u,
//  eTriggerAcumulator = 2u,
//  eTrigggerInCapt = 3u
//}teCddAdc_LpitTimerMode;
//
//typedef enum
//{
//  eExternalTiggers = 0u,
//  eInternalTriggers = 1u
//}teCddAdc_LpitTimerTrigSrc;
//
//typedef enum
//{
//  eTimerCh0 = 0u,
//  eTimerCh1 = 1u,
//  eTimerCh2 = 2u,
//  eTimerCh3 = 3u
//}teCddAdc_LpitTimerTrigSel;
//
//typedef struct
//{
//  tsCddAdc_LpitReg* const psLpitInst;
//  uint8 ucChnNr;
//  teCddAdc_LpitTimerMode eTimerMode;
//  uint32 ulPeriod_Reg;
//  teCddAdc_LpitTimerTrigSrc eTriggerSrc;
//  teCddAdc_LpitTimerTrigSel eTriggerSel;
//  boolean boReloadOnTrigger;
//  boolean boStopOnInterrupt;
//  boolean boStartOnTrigger;
//  boolean boChainChannel;
//  boolean boIntEnbl;
//}tsCddAdc_LpitTmrCfg;
//
//typedef enum
//{
//  eTRGMUX_TRIG_SOURCE_DISABLED = 0u,
//  eTRGMUX_TRIG_SOURCE_LPIT_CH0 = 17u,
//  eTRGMUX_TRIG_SOURCE_LPIT_CH1 = 18u,
//  eTRGMUX_TRIG_SOURCE_LPIT_CH2 = 19u,
//  eTRGMUX_TRIG_SOURCE_LPIT_CH3 = 20u,
//  eTRGMUX_TRIG_SOURCE_LPTMR0 = 21u,
//  eTRGMUX_TRIG_SOURCE_FTM0_INIT_TRIG = 22u,
//  eTRGMUX_TRIG_SOURCE_FTM0_EXT_TRIG = 23u,
//  eTRGMUX_TRIG_SOURCE_FTM1_INIT_TRIG = 24u,
//  eTRGMUX_TRIG_SOURCE_FTM1_EXT_TRIG = 25u,
//  eTRGMUX_TRIG_SOURCE_FTM2_INIT_TRIG = 26u,
//  eTRGMUX_TRIG_SOURCE_FTM2_EXT_TRIG = 27u,
//  eTRGMUX_TRIG_SOURCE_FTM3_INIT_TRIG = 28u,
//  eTRGMUX_TRIG_SOURCE_FTM3_EXT_TRIG = 29u,
//  eTRGMUX_TRIG_SOURCE_ADC0_SC1A_COCO = 30u,
//  eTRGMUX_TRIG_SOURCE_ADC0_SC1B_COCO = 31u,
//  eTRGMUX_TRIG_SOURCE_ADC1_SC1A_COCO = 32u,
//  eTRGMUX_TRIG_SOURCE_ADC1_SC1B_COCO = 33u,
//  eTRGMUX_TRIG_SOURCE_PDB0_CH0_TRIG = 34u,
//  eTRGMUX_TRIG_SOURCE_PDB0_PULSE_OUT = 36u,
//  eTRGMUX_TRIG_SOURCE_PDB1_CH0_TRIG = 37u,
//  eTRGMUX_TRIG_SOURCE_PDB1_PULSE_OUT = 39u,
//  eTRGMUX_TRIG_SOURCE_SIM_SW_TRIG = 63u
//}teCddAdc_TriggerMuxSource;
//
//
//typedef enum
//{
//  eTRGMUX_TARGET_MODULE_TRGMUX_OUT0 = 4u,
//  eTRGMUX_TARGET_MODULE_TRGMUX_OUT1 = 5u,
//  eTRGMUX_TARGET_MODULE_TRGMUX_OUT2 = 6u,
//  eTRGMUX_TARGET_MODULE_TRGMUX_OUT3 = 7u,
//  eTRGMUX_TARGET_MODULE_TRGMUX_OUT4 = 8u,
//  eTRGMUX_TARGET_MODULE_TRGMUX_OUT5 = 9u,
//  eTRGMUX_TARGET_MODULE_TRGMUX_OUT6 = 10u,
//  eTRGMUX_TARGET_MODULE_TRGMUX_OUT7 = 11u,
//  eTRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA0 = 12u,
//  eTRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA1 = 13u,
//  eTRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA2 = 14u,
//  eTRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA3 = 15u,
//  eTRGMUX_TARGET_MODULE_ADC1_ADHWT_TLA0 = 16u,
//  eTRGMUX_TARGET_MODULE_ADC1_ADHWT_TLA1 = 17u,
//  eTRGMUX_TARGET_MODULE_ADC1_ADHWT_TLA2 = 18u,
//  eTRGMUX_TARGET_MODULE_ADC1_ADHWT_TLA3 = 19u,
//  eTRGMUX_TARGET_MODULE_CMP0_SAMPLE = 28u,
//  eTRGMUX_TARGET_MODULE_PDB0_TRG_IN = 56u,
//  eTRGMUX_TARGET_MODULE_PDB1_TRG_IN = 60u,
//  eTRGMUX_TARGET_MODULE_LPTMR0_ALT0 = 100u
//}teCddAdc_TriggerMuxTarget;
//
//typedef struct
//{
//  tsCddAdc_TrgMuxReg* const psTrigMuxInst;
//  teCddAdc_TriggerMuxSource eTrigSource;
//  teCddAdc_TriggerMuxTarget eTrigTarget;
//  boolean boLock;
//}tsCddAdc_TrigMuxCfg;
//
//typedef struct
//{
//  uint32* pulAdc0Source;
//  uint32* pulAdc0Target;
//  uint16 unAdc0DataSize;
//  uint32* pulAdc1Source;
//  uint32* pulAdc1Target;
//  uint16 unAdc1DataSize;
//}tsCddAdc_DmaTriggerCfg;
//
//typedef struct
//{
//  tsCddAdc_AdcInstanceCfg* const psAdcInstCfg;
//  uint8 ucCfgLength;
//}tsCddAdc_AdcInstCfgMap;
//
//typedef struct
//{
//  tsCddAdc_AdcInputCfg* const psAdcInCfg;
//  uint8 ucCfgLength;
//}tsCddAdc_AdcChInCfgMap;
//
//typedef struct
//{
//  uint32* const pulAdcDataOut;
//  uint8 ucCfgLength;
//}tsCddAdc_AdcDataOutMap;
//
//typedef struct
//{
//  tsCddAdc_PdbInstanceCfg* const psPdbInstCfg;
//  uint8 ucCfgLength;
//}tsCddAdc_PdbInstCfgMap;
//
//typedef struct
//{
//  tsCddAdc_LpitInstanceCfg* const psLpitInstCfg;
//  uint8 ucCfgLength;
//}tsCddAdc_LpitInstCfgMap;
//
//typedef struct
//{
//  tsCddAdc_LpitTmrCfg* const psLpitTmrCfg;
//  uint8 ucCfgLength;
//}tsCddAdc_LpitTmrCfgMap;
//
//typedef struct
//{
//  tsCddAdc_TrigMuxCfg* const psTrigMuxCfg;
//  uint8 ucCfgLength;
//}tsCddAdc_TrigMuxCfgMap;
//
//
//typedef struct
//{
//  tsCddAdc_AdcInstCfgMap psAdcInstanceCfg;
//  tsCddAdc_AdcChInCfgMap psAdcInputChCfg;
//  tsCddAdc_AdcDataOutMap psAdcDataOut;
//  tsCddAdc_PdbInstCfgMap psPdbInstanceCfg;
//  tsCddAdc_LpitInstCfgMap psLpitInstanceCfg;
//  tsCddAdc_LpitTmrCfgMap psLpitTmrCfg;
//  tsCddAdc_TrigMuxCfgMap psTrigMuxInstanceCfg;
//}tsCddAdc_CfgData;
//
//#endif // CDD_ADC_TYPES_2021_03_16_H_
//
//// EOF
//
