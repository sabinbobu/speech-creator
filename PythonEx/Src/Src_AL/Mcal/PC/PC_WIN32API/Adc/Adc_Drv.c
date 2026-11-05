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
#include "Adc_TargetTypes.h"
#include "Adc_reg_stubs.h"


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

//====================================================================
// Global variables
//====================================================================

STATIC_AL tsAdc_AdcChInCfgMap* Adc_Drv_psInputMap;

//====================================================================
// Local functions declaration
//====================================================================

STATIC_AL void            Adc_Drv_SetAdcClkDivider(ADC_Type* CONST_AL psAdcInst, uint32 ulDividerVal);
STATIC_AL void            Adc_Drv_SetAdcSampleNr(ADC_Type* CONST_AL psAdcInst, uint32 ulSmplNr);
STATIC_AL void            Adc_Drv_SetAdcResolution(ADC_Type* CONST_AL psAdcInst, uint32 ulResolution);
STATIC_AL void            Adc_Drv_SetAdcClkIn(ADC_Type* CONST_AL psAdcInst, uint32 ulClkIn);
STATIC_AL void            Adc_Drv_SetAdcTrgType(ADC_Type* CONST_AL psAdcInst, uint32 ulTriggerTp);
STATIC_AL void            Adc_Drv_SetAdcTrgInput(ADC_Type* CONST_AL psAdcInst, uint32 ulTriggerIn);
STATIC_AL void            Adc_Drv_SetAdcPreTrgInput(ADC_Type* CONST_AL psAdcInst, uint32 ulPreTriggerIn);
STATIC_AL void            Adc_Drv_SetAdcDmaEnbl(ADC_Type* CONST_AL psAdcInst, uint32 ulDmaEnbl);
STATIC_AL void            Adc_Drv_SetAdcRefSel(ADC_Type* CONST_AL psAdcInst, uint32 ulRefSel);
STATIC_AL void            Adc_Drv_SetAdcAvgEnbl(ADC_Type* CONST_AL psAdcInst, uint32 ulAvgEnbl);
STATIC_AL void            Adc_Drv_SetAdcAvgMode(ADC_Type* CONST_AL psAdcInst, uint32 ulAvgMode);
STATIC_AL void            Adc_Drv_SetAdcContinousMode(ADC_Type* CONST_AL psAdcInst, uint32 ulContinousMode);
STATIC_AL void            Adc_Drv_SetAdcSupplyEn(ADC_Type* CONST_AL psAdcInst, uint32 ulSupplyEn);
STATIC_AL void            Adc_Drv_SetAdcStartCalibration(ADC_Type* CONST_AL psAdcInst);
STATIC_AL void            Adc_Drv_SetAdcChnInput(CONST_AL tsAdc_AdcInputCfg* CONST_AL psAdcChInCfg, uint32 ulInputSel);
STATIC_AL boolean         Adc_Drv_GetCalibrationStatus(ADC_Type* CONST_AL psAdcInst);
STATIC_AL boolean         Adc_Drv_GetAdcCompleteConvStat(ADC_Type* CONST_AL psAdcInst);
STATIC_AL Std_ReturnType  Adc_Drv_ConfigAdc(CONST_AL tsAdc_AdcInstanceCfg * CONST_AL psAdcConfig);
STATIC_AL Std_ReturnType  Adc_Drv_AutoCalibration(CONST_AL tsAdc_AdcInstanceCfg * CONST_AL psAdcConfig);
STATIC_AL void            Adc_Drv_AdcChInit(CONST_AL tsAdc_AdcInputCfg* CONST_AL psAdcChInCfg);
STATIC_AL Std_ReturnType  Adc_Drv_SwReadChannel(uint8 ucInput, tsAdc_AdcInputCfg CONST_AL sChnCfg[], uint16 * unAdcData);

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
 
  return  E_OK;

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
STATIC_AL Std_ReturnType Adc_Drv_AutoCalibration(CONST_AL tsAdc_AdcInstanceCfg * CONST_AL psAdcConfig)
{

  return E_OK;

}

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
  return;
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
  return E_OK;
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
  
  // Return ADC data
  return 0u;
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
  return;
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
  return;
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
  return;
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
  return;
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
  return 0;
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
  return 0;
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
  return 0;
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
  return;
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
  return;
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
  return;
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
  return;
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
  return;
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
  return;
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
STATIC_AL void Adc_Drv_SetAdcStartCalibration(ADC_Type* CONST_AL psAdcInst)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief Adc_Drv_GetCalibrationStatus
///
/// \descr Adc Self calibration status getter function
///
/// \param  psAdcInst - ADC instance (ADC0/ADC1)
///
/// \return boolean - ADC Self calibration status: TRUE - Self Calibration Complete,
///                                               FALSE - Self Calibration not complete or ongoing
//-----------------------------------------------------------------------------
STATIC_AL boolean Adc_Drv_GetCalibrationStatus(ADC_Type* CONST_AL psAdcInst)
{
  // Return status of ADC self calibration
  return TRUE;
}

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
  return;
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
  // Return ADC conversion complete status
  return TRUE;
}

// EOF
