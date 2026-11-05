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
/// \brief Adc Driver file (low access to the ADC pheripheric)
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

#include "Adc_Drv.h"
#include <UtilUtility.h>
#include <Std_Types.h>
#include "Adc_TargetTypes.h"

#if defined (CPU_S32K142)
  #include <S32K142.h>
#elif defined (CPU_S32K144)
  #include <S32K144.h>
#elif defined (CPU_S32K146)
  #include <S32K146.h>
#endif

#if defined (UNIT_TEST)
#include <Adc_reg_stubs.h>
#endif

//====================================================================
// Defines
//====================================================================


#define ADC_DRV_ADCH_INVALID_IN                     0x0000003Fu           // Invalid input for ADC channel
#define ADC_DRV_NUMBER_OF_ALT_CLOCKS                eADC_CLK_DIVIDE_1     // Clock divide by 1
#define ADC_DRV_CLOCK_FREQ_SOURCE                   40000000u             // LDM ADC pheripheral clock 40 MHz
#define ADC_DRV_CLOCK_FREQ_MIN_RUNTIME              20000000u             // ADC minimum peripheral clock suported 20 MHz
#define ADC_DRV_CLOCK_FREQ_MAX_RUNTIME              50000000u             // ADC maximum peripheral clock suported 50 MHz
#define ADC_DRV_RESET_SAMPLE_TIME_VALUE             12u                   // ADC sampling clock default value for ADC
#define ADC_DRV_SELF_CALIB_LOOP_BREAK               0xFFFFu               // Loop counter breaker for self-calibration
#define ADC_DRV_SW_READ_LOOP_BREAK                  0xFFFFu               // Loop counter breaker for SW conversion (COCO flag pooling)
#define ADC_DRV_READ_CONV_ERROR                     0xFFFFu               // Invalid ADC value (16 bit)
#define ADC_DRV_DIV_2                               2u                    // Divide by 2
#define ADC_DRV_DIV_4                               4u                    // Divide by 4
#define ADC_DRV_DIV_8                               8u                    // Divide by 8
// Register access usage
// Bit masks
// Bit postions
// Bit value ranges
#define ADC_DRV_SC1_IN_SEL_BIT_MASK                 0xFFFFFF80u
#define ADC_DRV_CFG1_CLK_DIV_BIT_MASK               0xFFFFFF9Fu
#define ADC_DRV_CFG1_RESOLUTION_BIT_MASK            0xFFFFFFF3u
#define ADC_DRV_CFG1_CLK_IN_BIT_MASK                0xFFFFFFFCu
#define ADC_DRV_CFG2_SMPL_NR_BIT_MASK               0xFFFFFF00u
#define ADC_DRV_SC2_TRIG_SEL_BIT_MASK               0xFFFFFFBFu
#define ADC_DRV_ADCOPT_TRIG_IN_ADC0_BIT_MASK        0xFFFFFFFEu
#define ADC_DRV_ADCOPT_TRIG_IN_ADC1_BIT_MASK        0xFFFFFEFFu
#define ADC_DRV_ADCOPT_PRETRIG_IN_ADC0_BIT_MASK     0xFFFFFFCFu
#define ADC_DRV_ADCOPT_PRETRIG_IN_ADC1_BIT_MASK     0xFFFFCFFFu
#define ADC_DRV_SC2_DMAEN_BIT_MASK                  0xFFFFFFFBu
#define ADC_DRV_SC2_REFSEL_BIT_MASK                 0xFFFFFFFCu
#define ADC_DRV_SC3_AVGEN_BIT_MASK                  0xFFFFFFFBu
#define ADC_DRV_SC3_AVGMODE_BIT_MASK                0xFFFFFFFCu
#define ADC_DRV_SC3_CONT_MODE_BIT_MASK              0xFFFFFFF7u
#define ADC_DRV_CHIPCTL_SUPEN_BIT_MASK              0xFFF7FFFFu
#define ADC_DRV_SC3_CAL_BIT_MASK                    0xFFFFFF7Fu
#define ADC_DRV_SC3_CAL_BIT_MASK_R                  0x00000001u
#define ADC_DRV_SC1_INSEL_BIT_MASK                  0xFFFFFFC0u
#define ADC_DRV_SC2_COCO_BIT_MASK                   0x00000001u
#define ADC_DRV_AVG_ENBL_BIT_MASK                   0x00000001u
#define ADC_DRV_AVG_MODE_BIT_MASK                   0x00000003u
#define ADC_DRV_TRG_MODE_BIT_MASK                   0x00000001u
#define ADC_DRV_SMPL_TIME_BIT_MASK                  0x000000FFu
#define ADC_DRV_CLK_DIV_BIT_MASK                    0x00000003u
#define ADC_DRV_SC1_IN_SEL_BIT_POS                  0u
#define ADC_DRV_SC1_CH_INT_ENBL_POS                 6u
#define ADC_DRV_CFG1_CLK_DIV_BIT_POS                5u
#define ADC_DRV_CFG1_RESOLUTION_BIT_POS             2u
#define ADC_DRV_CFG1_CLK_IN_BIT_POS                 0u
#define ADC_DRV_CFG2_SMPL_NR_BIT_POS                0u
#define ADC_DRV_SC2_TRIG_SEL_BIT_POS                6u
#define ADC_DRV_ADCOPT_TRIG_IN_ADC0_BIT_POS         0u
#define ADC_DRV_ADCOPT_TRIG_IN_ADC1_BIT_POS         8u
#define ADC_DRV_ADCOPT_PRETRIG_IN_ADC0_BIT_POS      4u
#define ADC_DRV_ADCOPT_PRETRIG_IN_ADC1_BIT_POS      12u
#define ADC_DRV_SC2_DMAEN_BIT_POS                   2u
#define ADC_DRV_SC2_REFSEL_BIT_POS                  0u
#define ADC_DRV_SC3_AVGEN_BIT_POS                   2u
#define ADC_DRV_SC3_AVGMODE_BIT_POS                 0u
#define ADC_DRV_SC3_CONT_MODE_BIT_POS               3u
#define ADC_DRV_CHIPCTL_SUPEN_BIT_POS               19u
#define ADC_DRV_SC3_CAL_BIT_POS                     7u
#define ADC_DRV_SC1_INSEL_BIT_POS                   0u
#define ADC_DRV_SC2_COCO_BIT_POS                    7u
#define ADC_DRV_AVG_ENBL_BIT_POS                    2u
#define ADC_DRV_AVG_MODE_BIT_POS                    0u
#define ADC_DRV_TRG_MODE_BIT_POS                    6u
#define ADC_DRV_SMPL_TIME_BIT_POS                   0u
#define ADC_DRV_CLK_DIV_BIT_POS                     5u
#define ADC_DRV_BIT_ENABLE                          1u
#define ADC_DRV_BIT_DISABLE                         0u
#define ADC_DRV_DIV_2                               2u
#define ADC_DRV_DIV_4                               4u
#define ADC_DRV_DIV_8                               8u
#define ADC_DRV_CFG1_CLK_DIV_BIT_MAX_VAL            0x3u
#define ADC_DRV_CFG2_SMPL_NR_BIT_MAX_VAL            0xFFu
#define DC_DRV_CFG1_RESOLUTION_BIT_MAX_VAL          0x3u
#define ADC_DRV_CFG1_CLK_IN_BIT_MAX_VAL             0x3u
#define ADC_DRV_SC2_TRIG_SEL_BIT_MAX_VAL            0x1u
#define ADC_DRV_ADCOPT_TRIG_IN_ADC0_BIT_MAX_VAL     0x1u
#define ADC_DRV_ADCOPT_TRIG_IN_ADC1_BIT_MAX_VAL     0x1u
#define ADC_DRV_ADCOPT_PRETRIG_IN_ADC0_BIT_MAX_VAL  0x3u
#define ADC_DRV_ADCOPT_PRETRIG_IN_ADC1_BIT_MAX_VAL  0x3u
#define ADC_DRV_SC2_DMAEN_BIT_MAX_VAL               0x1u
#define ADC_DRV_SC2_REFSEL_BIT_MAX_VAL              0x3u
#define ADC_DRV_SC3_AVGEN_BIT_VAL                   0x1u
#define ADC_DRV_SC3_AVGMODE_BIT_VAL                 0x3u
#define ADC_DRV_SC3_CONT_MODE_BIT_MAX_VAL           0x1u
#define ADC_DRV_CHIPCTL_SUPEN_BIT_MAX_VAL           0X1u
#define ADC_DRV_SC1_INSEL_BIT_MAX_VAL               0x3Fu
#define ADC_DRV_CALIB_REG_NR                        22u

//====================================================================
// Global variables
//====================================================================

STATIC_AL tsAdc_AdcChInCfgMap* Adc_Drv_psInputMap;

//====================================================================
// Local functions declaration
//====================================================================

STATIC_AL void            Adc_Drv_SetAdcClkDivider          (ADC_Type* CONST_AL psAdcInst, uint32 ulDividerVal);
STATIC_AL void            Adc_Drv_SetAdcSampleNr            (ADC_Type* CONST_AL psAdcInst, uint32 ulSmplNr);
STATIC_AL void            Adc_Drv_SetAdcResolution          (ADC_Type* CONST_AL psAdcInst, uint32 ulResolution);
STATIC_AL void            Adc_Drv_SetAdcClkIn               (ADC_Type* CONST_AL psAdcInst, uint32 ulClkIn);
STATIC_AL void            Adc_Drv_SetAdcTrgType             (ADC_Type* CONST_AL psAdcInst, uint32 ulTriggerTp);
STATIC_AL void            Adc_Drv_SetAdcTrgInput            (ADC_Type* CONST_AL psAdcInst, uint32 ulTriggerIn);
STATIC_AL void            Adc_Drv_SetAdcPreTrgInput         (ADC_Type* CONST_AL psAdcInst, uint32 ulPreTriggerIn);
STATIC_AL void            Adc_Drv_SetAdcDmaEnbl             (ADC_Type* CONST_AL psAdcInst, uint32 ulDmaEnbl);
STATIC_AL void            Adc_Drv_SetAdcRefSel              (ADC_Type* CONST_AL psAdcInst, uint32 ulRefSel);
STATIC_AL void            Adc_Drv_SetAdcAvgEnbl             (ADC_Type* CONST_AL psAdcInst, uint32 ulAvgEnbl);
STATIC_AL void            Adc_Drv_SetAdcAvgMode             (ADC_Type* CONST_AL psAdcInst, uint32 ulAvgMode);
STATIC_AL void            Adc_Drv_SetAdcContinousMode       (ADC_Type* CONST_AL psAdcInst, uint32 ulContinousMode);
STATIC_AL void            Adc_Drv_SetAdcSupplyEn            (ADC_Type* CONST_AL psAdcInst, uint32 ulSupplyEn);
STATIC_AL void            Adc_Drv_SetAdcChnInput            (CONST_AL tsAdc_AdcInputCfg* CONST_AL psAdcChInCfg, uint32 ulInputSel);
STATIC_AL boolean         Adc_Drv_GetAdcCompleteConvStat    (ADC_Type* CONST_AL psAdcInst);
STATIC_AL Std_ReturnType  Adc_Drv_ConfigAdc                 (CONST_AL tsAdc_AdcInstanceCfg * CONST_AL psAdcConfig);

#if !defined(UNIT_TEST)
#if (ADC_DRV_SELF_CALIBRATION_OP != STD_OFF)
STATIC_AL Std_ReturnType  Adc_Drv_AutoCalibration           (CONST_AL tsAdc_AdcInstanceCfg * CONST_AL psAdcConfig);
STATIC_AL void            Adc_Drv_SetAdcStartCalibration    (ADC_Type* CONST_AL psAdcInst);
STATIC_AL boolean         Adc_Drv_GetCalibrationStatus      (ADC_Type* CONST_AL psAdcInst);
#elif (ADC_DRV_EOL_CALIBRATION_OP != STD_OFF)
STATIC_AL Std_ReturnType  Adc_Drv_EolCalibration            (CONST_AL tsAdc_AdcInstanceCfg * CONST_AL psAdcConfig);
#else
#error "Error, ADC calibration strategy is not defined"
#endif
#else
STATIC_AL Std_ReturnType  Adc_Drv_AutoCalibration           (CONST_AL tsAdc_AdcInstanceCfg * CONST_AL psAdcConfig);
STATIC_AL void            Adc_Drv_SetAdcStartCalibration    (ADC_Type* CONST_AL psAdcInst);
STATIC_AL boolean         Adc_Drv_GetCalibrationStatus      (ADC_Type* CONST_AL psAdcInst);
STATIC_AL Std_ReturnType  Adc_Drv_EolCalibration            (CONST_AL tsAdc_AdcInstanceCfg * CONST_AL psAdcConfig);
#endif

STATIC_AL void            Adc_Drv_AdcChInit                 (CONST_AL tsAdc_AdcInputCfg* CONST_AL psAdcChInCfg);
STATIC_AL Std_ReturnType  Adc_Drv_SwReadChannel             (uint8 ucInput, tsAdc_AdcInputCfg CONST_AL sChnCfg[], uint16 * unAdcData);

//====================================================================
// Local functions definition
//====================================================================

//-----------------------------------------------------------------------------
/// \brief Adc_Drv_InitAdc
///
/// \descr ADC driver init function
///
/// \param  sCfgData - Configuration input data for ADC driver
///
/// \return Std_ReturnType - Returns E_OK
//-----------------------------------------------------------------------------
Std_ReturnType Adc_Drv_InitAdc(CONST_AL tsAdc_CfgData* CONST_AL psCfgData)
{
  // ADC instance/channel indexes
  uint8 ucAdcInstIndx = 0u;
  uint8 ucAdcChIdx = 0u;
  Std_ReturnType ucAdcSelfCalibRes = E_NOT_OK, ucAdcEolCalibRes = E_NOT_OK;

  // PRQA S 311 1 // Loss of const qualifier has no side effects
  Adc_Drv_psInputMap = (tsAdc_AdcChInCfgMap*)&psCfgData->sAdcInputChCfg;

  // Global config for Adc instances and self calibration sequence
  for (ucAdcInstIndx = 0u; ucAdcInstIndx < psCfgData->sAdcInstanceCfg.ucCfgLength; ucAdcInstIndx++)
  {
    // Global config for Adc instances
    (void)Adc_Drv_ConfigAdc(&psCfgData->sAdcInstanceCfg.psAdcInstCfg[ucAdcInstIndx]);

#if(ADC_DRV_EOL_CALIBRATION_OP != STD_OFF)

     // Check EOL calibration availability
    if ((psCfgData->sAdcInstanceCfg.psAdcInstCfg[ucAdcInstIndx].boEolCalib != FALSE) && (psCfgData->sAdcInstanceCfg.psAdcInstCfg[ucAdcInstIndx].pfCalibrationParm != NULL_PTR))
    {
      // Do EOL calibration
      ucAdcEolCalibRes = Adc_Drv_EolCalibration(&psCfgData->sAdcInstanceCfg.psAdcInstCfg[ucAdcInstIndx]);
    }
    else
    {
      // Calibration Failed - Ecu Uncoded, no other reactions need
    }

#endif

#if (ADC_DRV_SELF_CALIBRATION_OP != STD_OFF) || defined(UNIT_TEST)

    // EOL calibration failed or not supported
    if(ucAdcEolCalibRes != E_OK)
    {
      // Do Self Calibration
      ucAdcSelfCalibRes = Adc_Drv_AutoCalibration(&psCfgData->sAdcInstanceCfg.psAdcInstCfg[ucAdcInstIndx]);
    }
    else
    {
      // EOL calibration OK
    }

    // ADC calibration toatally failed 
    if ((ucAdcEolCalibRes != E_OK) && (ucAdcSelfCalibRes != E_OK))
    {
      // Do nothing, no reactions need
    }

#endif

  }

  // Init ADC channels present in channels configuration input
  for (ucAdcChIdx = 0u; ucAdcChIdx < psCfgData->sAdcInputChCfg.ucCfgLength; ucAdcChIdx++)
  {
    Adc_Drv_AdcChInit(&psCfgData->sAdcInputChCfg.psAdcInCfg[ucAdcChIdx]);
  }

  return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief Adc_Drv_ConfigAdc
///
/// \descr Adc Driver configuration (ADC0, ADC1 instances based on input instance config paramter)
///
/// \param  psAdcConfig - Adc Instance input configuration 
///
/// \return Std_ReturnType - E_OK - configuration successfull, E_NOK - configuration not successfull
//-----------------------------------------------------------------------------
STATIC_AL Std_ReturnType Adc_Drv_ConfigAdc(CONST_AL tsAdc_AdcInstanceCfg * CONST_AL psAdcConfig)
{
  // Set ADC clocking
  uint32  ulAdcClkFreq = ADC_DRV_CLOCK_FREQ_SOURCE;
  // Set implicitlyu return status as OK
  Std_ReturnType eRetStatus = E_OK;
  // PRQA S 306 1 // Cast needed for microcontroller registers access
  SIM_Type * CONST_AL psSimBaseAddr = SIM;
  // ADC instance initialized as NULL_PTR
  ADC_Type *psAdcInst = NULL_PTR;

  vuint32 ulRegRead = 0u;

  // Select which ADC instance need to be initialized
  // PRQA S 306 1 // Cast needed for microcontroller registers access
  psAdcInst = (psAdcConfig->ucAdcInst == 0u) ? ADC0 : ((psAdcConfig->ucAdcInst == 1u) ? ADC1 : NULL_PTR);

  // Find clocking source config
  ulAdcClkFreq = ulAdcClkFreq / (uint32)((uint32)1u << (uint32)(psAdcConfig->eClkDiv));

  // PRQA S 306 2 // Cast needed for microcontroller registers access
  // Return from init function if clocking condition is not met, supply voltage or ADC instance is invalid
  if ((psAdcConfig->eClkDiv < ADC_DRV_NUMBER_OF_ALT_CLOCKS) || (ulAdcClkFreq < ADC_DRV_CLOCK_FREQ_MIN_RUNTIME) || (ulAdcClkFreq > ADC_DRV_CLOCK_FREQ_MAX_RUNTIME) || (psAdcInst == NULL_PTR) ||
     ((psAdcConfig->ucAdcInst == 1u) && (psAdcConfig->boSupplyMonitoringEnable != FALSE)))
  {
    eRetStatus = E_NOT_OK;
  }
  else
  {
    // Keep Init config
  }

  // If basic conditions are met, init configuration continues
  if (eRetStatus == E_OK)
  {
    // Adc instance clock divide initialization
    Adc_Drv_SetAdcClkDivider(psAdcInst, (uint32)psAdcConfig->eClkDiv);
    // Adc sample time initialization
    Adc_Drv_SetAdcSampleNr(psAdcInst, (psAdcConfig->ulSampleTime > 0u) ? psAdcConfig->ulSampleTime : 1u);

    // Adc resolution initialization
    Adc_Drv_SetAdcResolution(psAdcInst, (uint32)psAdcConfig->eResolution);
    // Adc input clock initialization
    Adc_Drv_SetAdcClkIn(psAdcInst, (uint32)psAdcConfig->eInputClock);
    // Adc input trigger initialization
    Adc_Drv_SetAdcTrgType(psAdcInst, (uint32)psAdcConfig->eTrigger);

    // Adc trigger select initialization
    Adc_Drv_SetAdcTrgInput(psAdcInst, (uint32)psAdcConfig->eTriggerSel);
    // Adc pretrigger select initialization
    Adc_Drv_SetAdcPreTrgInput(psAdcInst, (uint32)psAdcConfig->ePreTriggerSel);

    // Adc DMA config initialization
    Adc_Drv_SetAdcDmaEnbl(psAdcInst, (psAdcConfig->boDmaEnable != FALSE) ? 1u : 0u);
    // Adc reference initialization
    Adc_Drv_SetAdcRefSel(psAdcInst, (uint32)psAdcConfig->eVoltageRef);

    // Adc average conversion config
    if (psAdcConfig->boAvgEnable != FALSE)
    {
      // Set number of samples to be averaged
      Adc_Drv_SetAdcAvgMode(psAdcInst, (uint32)psAdcConfig->eAverageCfg);
      // Average enable
      Adc_Drv_SetAdcAvgEnbl(psAdcInst, 1u);
    }
    else
    {
      // Average disable
      Adc_Drv_SetAdcAvgEnbl(psAdcInst, 0u);
    }

    // Adc continous convertion initialization
    Adc_Drv_SetAdcContinousMode(psAdcInst, (psAdcConfig->boContinuousConvEnable != FALSE) ? 1u : 0u);

    // Adc supply monitoring configuration only for ADC0
    Adc_Drv_SetAdcSupplyEn(psAdcInst, (psAdcConfig->boSupplyMonitoringEnable != FALSE) ? 1u : 0u);
  }
  else
  {
    // Return status is NOT_OK, skip
  }

  return (eRetStatus);

  // PRQA S 5324 1 // HIS metrics violation suppressed (STCAL = 13)
}


//-----------------------------------------------------------------------------
/// \brief Adc_Drv_AutoCalibration
///
/// \descr Adc Self Calibration Procedure
///
/// \param  Configuration input data for ADC driver
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
#if (ADC_DRV_SELF_CALIBRATION_OP != STD_OFF) || defined(UNIT_TEST)
STATIC_AL Std_ReturnType Adc_Drv_AutoCalibration(CONST_AL tsAdc_AdcInstanceCfg * CONST_AL psAdcConfig)
{
  ADC_Type *psAdcInst = NULL_PTR;
  // Set Adc Clk Frequence
  vuint32  ulAdcClkFreq = psAdcConfig->ulAdcFreq;
  // Clk divider to be applied
  vuint32 ulAdcClkDived_App = (vuint32)eADC_CLK_DIVIDE_1;
  // Auto Calibration return status
  Std_ReturnType eRetStatus = E_OK;
  // Auto calibration while breaker
  vuint32 ulAdcAutoCalBreakCnt = ADC_DRV_SELF_CALIB_LOOP_BREAK;
  // Get Average Enable Status
  vuint32 ulAdcAvgEnableStatus = 0u;
  // Get Average Mode
  vuint32 ulAdcAverageMode = 0u;
  // Get Trigger Mode
  vuint32 ulAdcTriggerMode = 0u;
  // Get Sample Time
  vuint32 ulAdcSampleTime = 0u;
  // Get current Adc Clk divide 
  vuint32 ulAdcClkDivide = 0u;

  // Select which ADC instance need to be initialized
  // PRQA S 306 1 // Cast needed for microcontroller registers access
  psAdcInst = (psAdcConfig->ucAdcInst == 0u) ? ADC0 : ((psAdcConfig->ucAdcInst == 1u) ? ADC1 : NULL_PTR);

  if (psAdcInst != NULL_PTR)
  {
    // Get Average Enable Status
    ulAdcAvgEnableStatus = (psAdcInst->SC3 >> ADC_DRV_AVG_ENBL_BIT_POS) & ADC_DRV_AVG_ENBL_BIT_MASK;
    // Get Average Mode
    ulAdcAverageMode = (psAdcInst->SC3 >> ADC_DRV_AVG_MODE_BIT_POS) & ADC_DRV_AVG_MODE_BIT_MASK;
    // Get Trigger Mode
    ulAdcTriggerMode = (psAdcInst->SC2 >> ADC_DRV_TRG_MODE_BIT_POS) & ADC_DRV_TRG_MODE_BIT_MASK;
    // Get Sample Time
    ulAdcSampleTime = (psAdcInst->CFG2 >> ADC_DRV_SMPL_TIME_BIT_POS) & ADC_DRV_SMPL_TIME_BIT_MASK;
    // Get current Adc Clk divide 
    ulAdcClkDivide = (psAdcInst->CFG1 >> ADC_DRV_CLK_DIV_BIT_POS) & ADC_DRV_CLK_DIV_BIT_MASK;

    // Set Adc conversion as average of 32 samples
    Adc_Drv_SetAdcAvgMode(psAdcInst, (uint32)eADC_AVERAGE_32);

    // Set Adc conversion average enable
    Adc_Drv_SetAdcAvgEnbl(psAdcInst, ADC_DRV_BIT_ENABLE);

    //Set Sw Trigger mode
    Adc_Drv_SetAdcTrgType(psAdcInst, (uint32)eADC_TRIGGER_SOFTWARE);

    // Set Sample Time value to the reset typical
    Adc_Drv_SetAdcSampleNr(psAdcInst, (uint32)ADC_DRV_RESET_SAMPLE_TIME_VALUE);

    // Reset all calibration registers
    psAdcInst->CLPS = (vuint32)0u;
    psAdcInst->CLP3 = (vuint32)0u;
    psAdcInst->CLP2 = (vuint32)0u;
    psAdcInst->CLP1 = (vuint32)0u;
    psAdcInst->CLP0 = (vuint32)0u;
    psAdcInst->CLPX = (vuint32)0u;
    psAdcInst->CLP9 = (vuint32)0u;

    // Set clock divider for auto calibration standard procedure
    if ((ulAdcClkFreq / (uint32)((uint32)1u << ulAdcClkDivide)) <= (ADC_DRV_CLOCK_FREQ_MAX_RUNTIME / ADC_DRV_DIV_2))
    {
      // Clock divider ok for auto calibration
    }
    else if ((ulAdcClkFreq / ADC_DRV_DIV_2) <= (ADC_DRV_CLOCK_FREQ_MAX_RUNTIME / ADC_DRV_DIV_2))
    {
      ulAdcClkDived_App = (uint32)eADC_CLK_DIVIDE_2;
    }
    else if ((ulAdcClkFreq / ADC_DRV_DIV_4) <= (ADC_DRV_CLOCK_FREQ_MAX_RUNTIME / ADC_DRV_DIV_2))
    {
      ulAdcClkDived_App = (uint32)eADC_CLK_DIVIDE_4;
    }
    else if ((ulAdcClkFreq / ADC_DRV_DIV_8) <= (ADC_DRV_CLOCK_FREQ_MAX_RUNTIME / ADC_DRV_DIV_2))
    {
      ulAdcClkDived_App = (uint32)eADC_CLK_DIVIDE_8;
    }
    else
    {
      // Something is wrong, divider cannot configured
      eRetStatus = E_NOT_OK;
    }

    // If clock divider config is ok, write new configuration otherwise keep the older one
    Adc_Drv_SetAdcClkDivider(psAdcInst, (eRetStatus == E_OK) ? ulAdcClkDived_App : ulAdcClkDivide);

    // Set calibration active flag
    Adc_Drv_SetAdcStartCalibration(psAdcInst);

    // Wait for complete auto calibration
    // PRQA S 3415 1 // No sides effects in this case. If counter reaches minimum value, function in not mandatory to be called
    while ((Adc_Drv_GetCalibrationStatus(psAdcInst) == FALSE) && (ulAdcAutoCalBreakCnt > 0u))
    {
      ulAdcAutoCalBreakCnt--;
    }

    // Auto Calibration is not set, report error
    eRetStatus = (ulAdcAutoCalBreakCnt == 0u) ? E_NOT_OK : eRetStatus;

    // Reverse Adc settings before self calibration (clock divide, average, tigger and sample nr)
    Adc_Drv_SetAdcClkDivider(psAdcInst, ulAdcClkDivide);
    Adc_Drv_SetAdcAvgMode(psAdcInst, ulAdcAverageMode);
    Adc_Drv_SetAdcAvgEnbl(psAdcInst, ulAdcAvgEnableStatus);
    Adc_Drv_SetAdcTrgType(psAdcInst, ulAdcTriggerMode);
    Adc_Drv_SetAdcSampleNr(psAdcInst, ulAdcSampleTime);
  }
  else
  {
    eRetStatus = E_NOT_OK;
  }
  
  return (eRetStatus);

  // PRQA S 5336 1 // STMIF = 5
}
#endif

//-----------------------------------------------------------------------------
/// \brief Adc_Drv_EolCalibration
///
/// \descr ADC EOL Calibration function
///
/// \param  psAdcConfig - Input ADC cfg which contains the EOL information
///
/// \return STATIC_AL Std_ReturnType
//-----------------------------------------------------------------------------
#if (ADC_DRV_EOL_CALIBRATION_OP != STD_OFF) || defined(UNIT_TEST)
STATIC_AL Std_ReturnType  Adc_Drv_EolCalibration(CONST_AL tsAdc_AdcInstanceCfg * CONST_AL psAdcConfig)
{
  uint32 ulAdc_Eol_StartParam_Addr  = 0u;
  boolean boEolCalibRet             = FALSE;
  volatile uint32* pulAdcRegDest    = NULL_PTR;
  volatile uint32* pulDest          = NULL_PTR;
  volatile uint16* punSource        = NULL_PTR;
  volatile ADC_Type *psAdcInst      = NULL_PTR;
  uint8_least ucErr_Cnt             = 0u;

  // Check ADC config
  if(psAdcConfig != NULL_PTR)
  {
    // Select which ADC instance need to be initialized
    // PRQA S 306 1 // Cast needed for microcontroller registers access
    psAdcInst = (psAdcConfig->ucAdcInst == 0u) ? ADC0 : ((psAdcConfig->ucAdcInst == 1u) ? ADC1 : NULL_PTR);
    // Check ADC instance
    if (psAdcInst != NULL_PTR)
    {
      // Get Calibration address
      boEolCalibRet = psAdcConfig->pfCalibrationParm(&ulAdc_Eol_StartParam_Addr);
      // If EOL parameters exist and address is valid
      // PRQA S 303 1 // Cast documented (volatile cast needed)
      if ((boEolCalibRet != FALSE) && ((vuint32*)ulAdc_Eol_StartParam_Addr != NULL_PTR))
      {
        // Get address of first ADC calibration register
        // PRQA S 310 1 // Cast documented (different type cast needed)
        pulAdcRegDest = (vuint32*)&psAdcInst->BASE_OFS;

        // Clear all ADC calibration registers
        for (uint8_least ucRegIdx = 0u; ucRegIdx < ADC_DRV_CALIB_REG_NR; ucRegIdx++)
        {
          // Calculate the address for each register
          pulDest = (vuint32*)pulAdcRegDest + ucRegIdx;
          // Write 0
          *pulDest = 0u;
        }

        // Go through all calibration registers
        for (uint8_least ucRegIdx = 0u; ucRegIdx < ADC_DRV_CALIB_REG_NR; ucRegIdx++)
        {
          // Calculate the address for each register (destination)
          pulDest = (vuint32*)pulAdcRegDest + ucRegIdx;
          // Calculate the input EOL address (Source address)
          // PRQA S 303 1 // Cast documented (volatile cast needed)
          punSource = (volatile uint16*)ulAdc_Eol_StartParam_Addr + ucRegIdx;
          // Update the calibration value
          *pulDest = (uint32)*punSource;
        }
      }
      else
      {
        // Increment error cnt
        ucErr_Cnt++;
      }
    }
    else
    {
      // Increment error cnt
      ucErr_Cnt++;
    }
  }
  else
  {
    // Increment error cnt
    ucErr_Cnt++;
  }

  return (ucErr_Cnt == 0u) ? E_OK : E_NOT_OK;
}
#endif

//-----------------------------------------------------------------------------
/// \brief Adc_Drv_AdcChInit
///
/// \descr ADC channels init procedure based on input configuration
///
/// \param  sAdcChInCfg - Adc Channels input configuration
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Adc_Drv_AdcChInit(CONST_AL tsAdc_AdcInputCfg* CONST_AL psAdcChInCfg)
{
  // Check input config parameter
  if (psAdcChInCfg != NULL_PTR)
  {
    // Get Adc Channel number
    uint8 ucAdcChannelNo = psAdcChInCfg->ucAdcCh;

    // Set Adc Ch to stop conversion mode
    Adc_Drv_SetAdcChnInput(psAdcChInCfg, ADC_DRV_ADCH_INVALID_IN);
    // Select input for Adc Channels
    Adc_Drv_SetAdcChnInput(psAdcChInCfg, (uint32)psAdcChInCfg->eInCh);
  }
  else
  {
    // NULL_PTR, Adc channels configuration shall be avoided
  }
}

//-----------------------------------------------------------------------------
/// \brief Adc_SwReadChannel
///
/// \descr ADC channel result SW read
///
/// \param  ucInput - Channel index
/// \param  sChnCfg - Channel Configuration
/// \param  unAdcData - Pointer to Adc Channel conversion Result
///
/// \return  Std_ReturnType - Conversion status
//-----------------------------------------------------------------------------
// PRQA S 3219 1 // Function not used. On the future it will be decided if it should be deleted or not
STATIC_AL Std_ReturnType Adc_Drv_SwReadChannel(uint8 ucInput, tsAdc_AdcInputCfg CONST_AL sChnCfg[], uint16 * unAdcData)
{
  ADC_Type *psAdcInst = NULL_PTR;
  // Read channel return status
  Std_ReturnType eRetStatus = E_OK;
  // Auto calibration while breaker
  vuint32 ulAdcSwReadBreakCnt = ADC_DRV_SW_READ_LOOP_BREAK;
  // Register number selector
  uint8 ucRegNo = 0u;
  // Input channel selector
  teAdc_InChMap eInChSel = eAdcDisabled;
  // Interrupt Enable
  boolean boChIntEnbl = FALSE;
  // Temp Register Value
  vuint32 ulRegValue = 0u;

  // Select which ADC instance need to be initialized
  // PRQA S 306 1 // Cast needed for microcontroller registers access
  psAdcInst = (sChnCfg[ucInput].ucAdcInst == 0u) ? ADC0 : ((sChnCfg[ucInput].ucAdcInst == 1u) ? ADC1 : NULL_PTR);

  // Check ADC instance and Channel validity
  if ((ucInput > Adc_Drv_psInputMap->ucCfgLength) || (psAdcInst == NULL_PTR))
  {
    // Input out of range, return
    eRetStatus = E_NOT_OK;
  }
  else
  {
    // Update Channel conversion Register (Only SC1 is suported)
    ucRegNo = 0u;
    // Extract Input Channel
    eInChSel = sChnCfg[ucInput].eInCh;
    // Interupt status
    boChIntEnbl = sChnCfg[ucInput].boIntEnbl;
    // Read SC1 register
    ulRegValue = psAdcInst->SC1[ucRegNo];

    ulRegValue &= ADC_DRV_SC1_IN_SEL_BIT_MASK;
    // Set Channel Input
    ulRegValue |=  ((uint32)eInChSel << ADC_DRV_SC1_IN_SEL_BIT_POS);
    // Set Channel Interrupt
    ulRegValue |=  ((boChIntEnbl != FALSE) ? (uint32)((uint32)ADC_DRV_BIT_ENABLE << ADC_DRV_SC1_CH_INT_ENBL_POS) : ADC_DRV_BIT_DISABLE);
    // Store SC1 register value
    psAdcInst->SC1[ucRegNo] = ulRegValue;

    // Wait for conversion complete
    // PRQA S 3415 1 // No sides effects in this case. If counter reaches minimum value, function in not mandatory to be called
    while ((Adc_Drv_GetAdcCompleteConvStat(psAdcInst) == FALSE) && (ulAdcSwReadBreakCnt > 0u))
    {
      ulAdcSwReadBreakCnt--;
    }

    if (ulAdcSwReadBreakCnt != 0u)
    {
      // Adc conversion Ok
      // Read ADC data
      *unAdcData = (uint16)psAdcInst->R[ucRegNo];
    }
    else
    {
      // Adc conversion too long, report error
      *unAdcData = ADC_DRV_READ_CONV_ERROR;
      eRetStatus = E_NOT_OK;
    }
  }

  // Return conversion value
  return (eRetStatus);
}

//-----------------------------------------------------------------------------
/// \brief Adc_Drv_GetAdcRawValue
///
/// \descr Read ADC conversion data based on Input Channel
///
/// \param  ucInputIx - Adc Channel Index
///
/// \return uint16 - Adc Raw value
//-----------------------------------------------------------------------------
uint16 Adc_Drv_GetAdcRawValue(uint8 ucInputIx)
{
  // Adc raw value
  uint16 unAdcRawVal = 0u;

  // Check Channel Index Validity
  if (Adc_Drv_psInputMap->ucCfgLength < ucInputIx)
  {
    // Return error in case of invalid channel
    unAdcRawVal = ADC_DRV_READ_CONV_ERROR;
  }
  else
  {
    // Read DMA RAM source address based on channel index
    unAdcRawVal = (uint16)*Adc_Drv_psInputMap->psAdcInCfg[ucInputIx].pulAdcData;
  }

  // Return ADC data
  return (unAdcRawVal);
}

//-----------------------------------------------------------------------------
/// \brief Adc_Drv_SetAdcClkDivider
///
/// \descr ADC clock divider set function
///
/// \param  psAdcInst - ADC instance (ADC0/ADC1)
/// \param  ulDividerVal - ADC Clk divider value
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Adc_Drv_SetAdcClkDivider(ADC_Type* CONST_AL psAdcInst, uint32 ulDividerVal)
{
  if ((psAdcInst != NULL_PTR) && (ulDividerVal <= ADC_DRV_CFG1_CLK_DIV_BIT_MAX_VAL))
  {
    // Read register CFG1
    vuint32 ulRegValue = psAdcInst->CFG1;
    // Clear bits over CLKDIV bitfield in CFG1 register
    ulRegValue &= ADC_DRV_CFG1_CLK_DIV_BIT_MASK;
    // Write Clk divider in CLKDIV bitfield
    ulRegValue |= (ulDividerVal << ADC_DRV_CFG1_CLK_DIV_BIT_POS);
    // Update CFG1 register
    psAdcInst->CFG1 = ulRegValue;
  }
  else
  {
    // ADC instance invalid, configuration wrong
  }
}

//-----------------------------------------------------------------------------
/// \brief Adc_Drv_SetAdcSampleNr
///
/// \descr ADC sampling set function
///
/// \param  psAdcInst - ADC instance (ADC0/ADC1)
/// \param  ulSmplNr - Sample Number
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Adc_Drv_SetAdcSampleNr(ADC_Type* CONST_AL psAdcInst, uint32 ulSmplNr)
{
  if ((psAdcInst != NULL_PTR) && (ulSmplNr <= ADC_DRV_CFG2_SMPL_NR_BIT_MAX_VAL))
  {
    // Read register CFG2
    vuint32 ulRegValue = psAdcInst->CFG2;

    // Clear bits over SMPL bitfield in CFG2 register
    ulRegValue &= ADC_DRV_CFG2_SMPL_NR_BIT_MASK;
    // Write Clk divider in SMPL bitfield 
    ulRegValue |= (ulSmplNr << ADC_DRV_CFG2_SMPL_NR_BIT_POS);
    // Update CFG2 register
    psAdcInst->CFG2 = ulRegValue;
  }
  else
  {
    // ADC instance invalid, configuration wrong
  }
}

//-----------------------------------------------------------------------------
/// \brief Adc_Drv_SetAdcResolution
///
/// \descr ADC resolution set function (10-12 bit result)
///
/// \param  psAdcInst - Adc Instance (ADC0/ADC1)
/// \param  ulResolution - Adc resolution value
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Adc_Drv_SetAdcResolution(ADC_Type* CONST_AL psAdcInst, uint32 ulResolution)
{
  if ((psAdcInst != NULL_PTR) && (ulResolution <= DC_DRV_CFG1_RESOLUTION_BIT_MAX_VAL))
  {
    // Read register CFG1
    vuint32 ulRegValue = psAdcInst->CFG1;
    // Clear bits over RES bitfield in CFG1 register
    ulRegValue &= ADC_DRV_CFG1_RESOLUTION_BIT_MASK;
    // Write Resolution in RES bitfield
    ulRegValue |= (ulResolution << ADC_DRV_CFG1_RESOLUTION_BIT_POS);
    // Update CFG1 register
    psAdcInst->CFG1 = ulRegValue;
  }
  else
  {
    // ADC instance invalid, configuration wrong
  }
}

//-----------------------------------------------------------------------------
/// \brief Adc_Drv_SetAdcClkIn
///
/// \descr ADC Input Clock Selectro function
///
/// \param  psAdcInst - ADC Instance (ADC0/ADC1)
/// \param  ulClkIn - Adc Clock In
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Adc_Drv_SetAdcClkIn(ADC_Type* CONST_AL psAdcInst, uint32 ulClkIn)
{
  if ((psAdcInst != NULL_PTR) && (ulClkIn <= ADC_DRV_CFG1_CLK_IN_BIT_MAX_VAL))
  {
    // Read register CFG1
    vuint32 ulRegValue = psAdcInst->CFG1;
    // Clear bits over CLKIN bitfield in CFG1 register
    ulRegValue &= ADC_DRV_CFG1_CLK_IN_BIT_MASK;
    // Write Clock In in CLKIN bitfield
    ulRegValue |= (ulClkIn << ADC_DRV_CFG1_CLK_IN_BIT_POS);
    // Update CFG1 register
    psAdcInst->CFG1 = ulRegValue;
  }
  else
  {
    // ADC instance invalid, configuration wrong
  }
}

//-----------------------------------------------------------------------------
/// \brief Adc_Drv_SetAdcTrgType
///
/// \descr ADC trigger configuration
///
/// \param  psAdcInst - ADC instance (ADC0/ADC1)
/// \param  ulTriggerTp - ADC trigger type
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Adc_Drv_SetAdcTrgType(ADC_Type* CONST_AL psAdcInst, uint32 ulTriggerTp)
{
  if ((psAdcInst != NULL_PTR) && (ulTriggerTp <= ADC_DRV_SC2_TRIG_SEL_BIT_MAX_VAL))
  {
    // Read register SC2
    vuint32 ulRegValue = psAdcInst->SC2;
    // Clear bits over TRIG_SEL bitfield in SC2 register
    ulRegValue &= ADC_DRV_SC2_TRIG_SEL_BIT_MASK;
    // Write Trigger Selector in TRIG_SEL bitfield
    ulRegValue |= (ulTriggerTp << ADC_DRV_SC2_TRIG_SEL_BIT_POS);
    // Update SC2 register
    psAdcInst->SC2 = ulRegValue;
  }
  else
  {
    // ADC instance invalid, configuration wrong
  }
}

//-----------------------------------------------------------------------------
/// \brief Adc_Drv_SetAdcTrgInput
///
/// \descr Adc Hw trigger input selector setting procedure
///
/// \param  psAdcInst - ADC instance (ADC0/ADC1)
/// \param  ulTriggerIn - Trigger Input value
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Adc_Drv_SetAdcTrgInput(ADC_Type* CONST_AL psAdcInst, uint32 ulTriggerIn)
{
  // Get SIM instance address
  // PRQA S 306 1 // Cast needed for microcontroller registers access
  SIM_Type * CONST_AL psSimBaseAddr = SIM;

  // Get ADCOP register value
  vuint32 ulRegValue = psSimBaseAddr->ADCOPT;

  // ADC0
  // PRQA S 306 1 // Cast needed for microcontroller registers access
  if ((psAdcInst == ADC0) && (ulTriggerIn <= ADC_DRV_ADCOPT_TRIG_IN_ADC0_BIT_MAX_VAL))
  {
    // Clear bits over TRIG_IN_ADC0 bitfield in ADCOPT register
    ulRegValue &= ADC_DRV_ADCOPT_TRIG_IN_ADC0_BIT_MASK;
    // Write Trigger input in TRIG_IN_ADC0 bitfield
    ulRegValue |= (ulTriggerIn << ADC_DRV_ADCOPT_TRIG_IN_ADC0_BIT_POS);
  }
  // ADC1
  // PRQA S 306 1 // Cast needed for microcontroller registers access
  else if ((psAdcInst == ADC1) && (ulTriggerIn <= ADC_DRV_ADCOPT_TRIG_IN_ADC1_BIT_MAX_VAL))
  {
    // Clear bits over TRIG_IN_ADC1 bitfield in ADCOPT register
    ulRegValue &= ADC_DRV_ADCOPT_TRIG_IN_ADC1_BIT_MASK;
    // Write Trigger input in TRIG_IN_ADC1 bitfield
    ulRegValue |= (ulTriggerIn << ADC_DRV_ADCOPT_TRIG_IN_ADC1_BIT_POS);
  }
  else
  {
    // Invalid ADC instance, invalid configuration
  }

  // Update ADCOPT register
  psSimBaseAddr->ADCOPT = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief Adc_Drv_SetAdcPreTrgInput
///
/// \descr Adc Hw pre-trigger input selector setting procedure
///
/// \param  psAdcInst - ADC instance (ADC0/ADC1)
/// \param  ulPreTriggerIn - Pretriger option value
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Adc_Drv_SetAdcPreTrgInput(ADC_Type* CONST_AL psAdcInst, uint32 ulPreTriggerIn)
{
  // Get SIM instance address
  // PRQA S 306 1 // Cast needed for microcontroller registers access
  SIM_Type * CONST_AL psSimBaseAddr = SIM;

  // Get ADCOP register value
  vuint32 ulRegValue = psSimBaseAddr->ADCOPT;

  // ADC0
  // PRQA S 306 1 // Cast needed for microcontroller registers access
  if ((psAdcInst == ADC0) && (ulPreTriggerIn <= ADC_DRV_ADCOPT_PRETRIG_IN_ADC0_BIT_MAX_VAL))
  {
    // Clear bits over PRETRIG_IN_ADC0 bitfield in ADCOPT register
    ulRegValue &= ADC_DRV_ADCOPT_PRETRIG_IN_ADC0_BIT_MASK;
    // Write Pre-Trigger input in PRETRIG_IN_ADC0 bitfield
    ulRegValue |= (ulPreTriggerIn << ADC_DRV_ADCOPT_PRETRIG_IN_ADC0_BIT_POS);
  }
  // ADC1
  // PRQA S 306 1 // Cast needed for microcontroller registers access
  else if ((psAdcInst == ADC1) && (ulPreTriggerIn <= ADC_DRV_ADCOPT_PRETRIG_IN_ADC1_BIT_MAX_VAL))
  {
    // Clear bits over PRETRIG_IN_ADC1 bitfield in ADCOPT register
    ulRegValue &= ADC_DRV_ADCOPT_PRETRIG_IN_ADC1_BIT_MASK;
    // Write Pre-Trigger input in PRETRIG_IN_ADC1 bitfield
    ulRegValue |= (ulPreTriggerIn << ADC_DRV_ADCOPT_PRETRIG_IN_ADC1_BIT_POS);
  }
  else
  {
    // Invalid ADC instance, invalid configuration
  }

  // Update ADCOPT register
  psSimBaseAddr->ADCOPT = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief Adc_Drv_SetAdcDmaEnbl
///
/// \descr Set ADC DMA enable bit
///
/// \param  psAdcInst - ADC instance (ADC0/ADC1)
/// \param  ulDmaEnbl - DMA enable bit
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Adc_Drv_SetAdcDmaEnbl(ADC_Type* CONST_AL psAdcInst, uint32 ulDmaEnbl)
{
  if ((psAdcInst != NULL_PTR) && (ulDmaEnbl <= ADC_DRV_SC2_DMAEN_BIT_MAX_VAL))
  {
    // Get SC2 register value
    vuint32 ulRegValue = psAdcInst->SC2;
    // Clear bits over DMAEN bitfield in SC2 register
    ulRegValue &= ADC_DRV_SC2_DMAEN_BIT_MASK;
    // Write DMA Enable in DMAEN bitfield
    ulRegValue |= (ulDmaEnbl << ADC_DRV_SC2_DMAEN_BIT_POS);
    // Update SC2 register
    psAdcInst->SC2 = ulRegValue;
  }
  else
  {
    // ADC instance invalid, configuration wrong
  }
}

//-----------------------------------------------------------------------------
/// \brief Adc_Drv_SetAdcRefSel
///
/// \descr Adc Reference selection Procedure
///
/// \param  psAdcInst - ADC instance (ADC0/ADC1)
/// \param  ulRefSel - Reference selector value
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Adc_Drv_SetAdcRefSel(ADC_Type* CONST_AL psAdcInst, uint32 ulRefSel)
{
  if ((psAdcInst != NULL_PTR) && (ulRefSel <= ADC_DRV_SC2_REFSEL_BIT_MAX_VAL))
  {
    // Get SC2 register value
    vuint32 ulRegValue = psAdcInst->SC2;
    // Clear bits over REFSEL bitfield in SC2 register
    ulRegValue &= ADC_DRV_SC2_REFSEL_BIT_MASK;
    // Write Reference Selector in REFSEL bitfield
    ulRegValue |= (ulRefSel << ADC_DRV_SC2_REFSEL_BIT_POS);
    // Update SC2 register
    psAdcInst->SC2 = ulRegValue;
  }
  else
  {
    // ADC instance invalid, configuration wrong
  }
}

//-----------------------------------------------------------------------------
/// \brief Adc_Drv_SetAdcAvgEnbl
///
/// \descr Adc average conversion enable procedure
///
/// \param  psAdcInst - ADC instance (ADC0/ADC1)
/// \param  ulAvgEnbl - Adc Average Conversion Enable Bit (Enable/Disable)
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Adc_Drv_SetAdcAvgEnbl(ADC_Type* CONST_AL psAdcInst, uint32 ulAvgEnbl)
{
  if ((psAdcInst != NULL_PTR) && (ulAvgEnbl <= ADC_DRV_SC3_AVGEN_BIT_VAL))
  {
    // Get SC3 register value
    vuint32 ulRegValue = psAdcInst->SC3;
    // Clear bits over AVGEN bitfield in SC3 register
    ulRegValue &= ADC_DRV_SC3_AVGEN_BIT_MASK;
    // Write Average Enable in AVGEN bitfield
    ulRegValue |= (ulAvgEnbl << ADC_DRV_SC3_AVGEN_BIT_POS);
    // Update SC3 register
    psAdcInst->SC3 = ulRegValue;
  }
  else
  {
    // ADC instance invalid, configuration wrong
  }
}

//-----------------------------------------------------------------------------
/// \brief Adc_Drv_SetAdcAvgMode
///
/// \descr Adc average conversion mode procedure
///
/// \param  psAdcInst - ADC instance (ADC0/ADC1)
/// \param  ulAvgMode - ADC conversion mode (4, 8, 16, 32 samples average)
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Adc_Drv_SetAdcAvgMode(ADC_Type* CONST_AL psAdcInst, uint32 ulAvgMode)
{
  if ((psAdcInst != NULL_PTR) && (ulAvgMode <= ADC_DRV_SC3_AVGMODE_BIT_VAL))
  {
    // Get SC3 register value
    vuint32 ulRegValue = psAdcInst->SC3;

    // Clear bits over AVGMODE bitfield in SC3 register
    ulRegValue &= ADC_DRV_SC3_AVGMODE_BIT_MASK;
    // Write Average Mode in AVGMODE bitfield
    ulRegValue |= (ulAvgMode << ADC_DRV_SC3_AVGMODE_BIT_POS);

    // Update SC3 register
    psAdcInst->SC3 = ulRegValue;
  }
  else
  {
    // ADC instance invalid, configuration wrong
  }
}

//-----------------------------------------------------------------------------
/// \brief Adc_Drv_SetAdcContinousMode
///
/// \descr Adc Continous Mode enable procedure
///
/// \param  psAdcInst - ADC instance (ADC0/ADC1)
/// \param  ulContinousMode - Adc Continous Mode enable bit value
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Adc_Drv_SetAdcContinousMode(ADC_Type* CONST_AL psAdcInst, uint32 ulContinousMode)
{
  if ((psAdcInst != NULL_PTR) && (ulContinousMode <= ADC_DRV_SC3_CONT_MODE_BIT_MAX_VAL))
  {
    // Get SC3 register value
    vuint32 ulRegValue = psAdcInst->SC3;

    // Clear bits over CONT_MODE bitfield in SC3 register
    ulRegValue &= ADC_DRV_SC3_CONT_MODE_BIT_MASK;
    // Write Continous Mode in CONT_MODE bitfield
    ulRegValue |= (ulContinousMode << ADC_DRV_SC3_CONT_MODE_BIT_POS);

    // Update SC3 register
    psAdcInst->SC3 = ulRegValue;
  }
  else
  {
    // ADC instance invalid, configuration wrong
  }
}

//-----------------------------------------------------------------------------
/// \brief Adc_Drv_SetAdcSupplyEn
///
/// \descr Adc Supply monitoring configuration
///
/// \param  psAdcInst - ADC instance (ADC0/ADC1)
/// \param  ulSupplyEn - Supply Enable Bit
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Adc_Drv_SetAdcSupplyEn(ADC_Type* CONST_AL psAdcInst, uint32 ulSupplyEn)
{
  // Get SIM instance address
  // PRQA S 306 1 // Cast needed for microcontroller registers access
  SIM_Type * CONST_AL psSimBaseAddr = SIM;

  // Get CHIPCTL register value
  vuint32 ulRegValue = psSimBaseAddr->CHIPCTL;

  // Supply monitoring available only for ADC0
  // PRQA S 306 1 // Cast needed for microcontroller registers access
  if ((psAdcInst == ADC0) && (ulSupplyEn <= ADC_DRV_CHIPCTL_SUPEN_BIT_MAX_VAL))
  {
    // Clear bits over SUPEN bitfield in CHIPCTL register
    ulRegValue &= ADC_DRV_CHIPCTL_SUPEN_BIT_MASK;
    // Write Supply monitoring in SUPEN bitfield
    ulRegValue |= (ulSupplyEn << ADC_DRV_CHIPCTL_SUPEN_BIT_POS);
  }
  else
  {
    // ADC1 doesn't support Supply Monitoring
  }

  // Update CHIPCTL register
  psSimBaseAddr->CHIPCTL = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief Adc_Drv_SetAdcStartCalibration
///
/// \descr Adc Start Hw Self Calibration procedure
///
/// \param  psAdcInst - ADC instance (ADC0/ADC1)
///
/// \return void
//-----------------------------------------------------------------------------
#if (ADC_DRV_SELF_CALIBRATION_OP != STD_OFF) || defined(UNIT_TEST)
STATIC_AL void Adc_Drv_SetAdcStartCalibration(ADC_Type* CONST_AL psAdcInst)
{
  // Get SC3 register value
  vuint32 ulRegValue = psAdcInst->SC3;

  // Clear bits over CAL bitfield in SC3 register
  ulRegValue &= ADC_DRV_SC3_CAL_BIT_MASK;
  // Write Supply monitoring in SUPEN bitfield
  ulRegValue |= (uint32)((uint32)ADC_DRV_BIT_ENABLE << ADC_DRV_SC3_CAL_BIT_POS);
  // Update SC3 register
  psAdcInst->SC3 = ulRegValue;
}
#endif

//-----------------------------------------------------------------------------
/// \brief Adc_Drv_GetCalibrationStatus
///
/// \descr Adc Self calibration status getter function
///
/// \param  psAdcInst - ADC instance (ADC0/ADC1)
///
/// \return boolean - ADC Self calibration status: TRUE - Self Calibration Complete,
///                                                FALSE - Self Calibration not complete or ongoing
//-----------------------------------------------------------------------------
#if (ADC_DRV_SELF_CALIBRATION_OP != STD_OFF) || defined(UNIT_TEST)
STATIC_AL boolean Adc_Drv_GetCalibrationStatus(ADC_Type* CONST_AL psAdcInst)
{
  // Return status of ADC self calibration
  return ((((psAdcInst->SC3 >> ADC_DRV_SC3_CAL_BIT_POS) & ADC_DRV_SC3_CAL_BIT_MASK_R) != ADC_DRV_BIT_DISABLE) ? FALSE : TRUE);
}
#endif

//-----------------------------------------------------------------------------
/// \brief Adc_Drv_SetAdcChnInput
///
/// \descr Adc Input Channel Configuration based on channel number and input pin
///
/// \param  sAdcChInCfg - ADC instance (ADC0/ADC1)
/// \param  ulInputSel - Input pin based on IoHwAb config list
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Adc_Drv_SetAdcChnInput(CONST_AL tsAdc_AdcInputCfg* CONST_AL psAdcChInCfg, uint32 ulInputSel)
{
  // ADC instance init
  ADC_Type *psAdcInst = NULL_PTR;
  // Get Adc Channel number
  uint8 ucAdcChannelNo = psAdcChInCfg->ucAdcCh;
  // Temp register value
  vuint32 ulRegValue = 0u;

  // Select which ADC instance need to be initialized
  // PRQA S 306 1 // Cast needed for microcontroller registers access
  psAdcInst = (psAdcChInCfg->ucAdcInst == 0u) ? ADC0 : ((psAdcChInCfg->ucAdcInst == 1u) ? ADC1 : NULL_PTR);

  // Adc instance valid
  if ((psAdcInst != NULL_PTR) && (ulInputSel <= ADC_DRV_SC1_INSEL_BIT_MAX_VAL))
  {
    // Get SC1[channel] register value
    ulRegValue = psAdcInst->SC1[ucAdcChannelNo];
    // Clear bits over INSEL bitfield in SC1[channel] register
    ulRegValue &= ADC_DRV_SC1_INSEL_BIT_MASK;
    // Write Chanell Input Selection in INSEL bitfield
    ulRegValue |= (ulInputSel << ADC_DRV_SC1_INSEL_BIT_POS);
    // Update SC1[channel] register
    psAdcInst->SC1[ucAdcChannelNo] = ulRegValue;
  }
  else
  {
    // Adc instance invalid (NULL_PTR), wrong configuration
  }
}

//-----------------------------------------------------------------------------
/// \brief Adc_Drv_GetAdcCompleteConvStat
///
/// \descr Adc Complete conversion flag getter procedure
///
/// \param  sAdcChInCfg - Input data config
///
/// \return boolean - Adc conversion complete status for specific Adc input
//-----------------------------------------------------------------------------
STATIC_AL boolean Adc_Drv_GetAdcCompleteConvStat(ADC_Type* CONST_AL psAdcInst)
{
  // Get SC2 register value
  vuint32 ulRegValue = psAdcInst->SC2;

  // Return ADC conversion complete status
  return (((psAdcInst->SC2 >> ADC_DRV_SC2_COCO_BIT_POS) & ADC_DRV_SC2_COCO_BIT_MASK) != ADC_DRV_BIT_DISABLE) ? TRUE : FALSE;
}

// EOF
