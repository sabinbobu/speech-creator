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
/// \brief
///
//-----------------------------------------------------------------------------

#include "Adc_Drv.h"
#include <UtilUtility.h>
#include <../Cdd/CddAdc/Gen/CddAdc_Types.h>


#define CDDADC_ADCH_MASK            0x3Fu
#define CDDADC_PDB_IN_CLK_FREQ      48000000u  // FIR as sysclock
#define ADC_INSTANCES_NO            2u
#define NUMBER_OF_ALT_CLOCKS        eADC_CLK_DIVIDE_1
#define ADC_CLOCK_FREQ_SOURCE       80000000u
#define ADC_CLOCK_FREQ_MIN_RUNTIME  20000000u
#define ADC_CLOCK_FREQ_MAX_RUNTIME  50000000u
#define ADC_RESET_SAMPLE_TIME_VALUE 12u

static void CddAdc_Drv_SetAdcClkDivider(tsCddAdc_AdcReg* const psAdcInst, uint32 ulDividerVal);
static void CddAdc_Drv_SetAdcSampleNr(tsCddAdc_AdcReg* const psAdcInst, uint32 ulSmplNr);
static void CddAdc_Drv_SetAdcResolution(tsCddAdc_AdcReg* const psAdcInst, uint32 ulResolution);
static void CddAdc_Drv_SetAdcClkIn(tsCddAdc_AdcReg* const psAdcInst, uint32 ulClkIn);
static void CddAdc_Drv_SetAdcTrgType(tsCddAdc_AdcReg* const psAdcInst, uint32 ulTriggerTp);
static void CddAdc_Drv_SetAdcTrgInput(tsCddAdc_AdcReg* const psAdcInst, uint32 ulTriggerIn);
static void CddAdc_Drv_SetAdcPreTrgInput(tsCddAdc_AdcReg* const psAdcInst, uint32 ulPreTriggerIn);
static void CddAdc_Drv_SetAdcDmaEnbl(tsCddAdc_AdcReg* const psAdcInst, uint32 ulDmaEnbl);
static void CddAdc_Drv_SetAdcRefSel(tsCddAdc_AdcReg* const psAdcInst, uint32 ulRefSel);
static void CddAdc_Drv_SetAdcAvgEnbl(tsCddAdc_AdcReg* const psAdcInst, uint32 ulAvgEnbl);
static void CddAdc_Drv_SetAdcAvgMode(tsCddAdc_AdcReg* const psAdcInst, uint32 ulAvgMode);
static void CddAdc_Drv_SetAdcContinousMode(tsCddAdc_AdcReg* const psAdcInst, uint32 ulContinousMode);\
static void CddAdc_Drv_SetAdcSupplyEn(tsCddAdc_AdcReg* const psAdcInst, uint32 ulSupplyEn);
static void CddAdc_Drv_SetAdcStartCalibration(tsCddAdc_AdcReg* const psAdcInst);
static void CddAdc_Drv_SetAdcChnInput(const tsCddAdc_AdcInputCfg* const sAdcChInCfg, uint32 ulInputSel);
static boolean CddAdc_Drv_GetCalibrationStatus(tsCddAdc_AdcReg* const psAdcInst);
static boolean CddAdc_Drv_GetAdcCompleteConvStat(tsCddAdc_AdcReg* const psAdcInst);
static Std_ReturnType CddAdc_Drv_ConfigAdc(const tsCddAdc_AdcInstanceCfg * const sAdcConfig);
static Std_ReturnType CddAdc_Drv_AutoCalibration(const tsCddAdc_AdcInstanceCfg * const sAdcConfig);
static void CddAdc_Drv_AdcChInit(const tsCddAdc_AdcInputCfg* const sAdcChInCfg);
static Std_ReturnType CddAdc_Drv_SwReadChannel(uint8 ucInput, tsCddAdc_AdcInputCfg const sChnCfg[], uint16 * unAdcData);

static tsCddAdc_AdcChInCfgMap CddAdc_Drv_InputMap;

//-----------------------------------------------------------------------------
/// \brief CddAdc_InitAdc
///
/// \descr
///
/// \param  -
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType CddAdc_Drv_InitAdc(tsCddAdc_CfgData sCfgData)
{
  uint8 ucAdcInstIndx;
  uint8 ucAdcChIdx;

  CddAdc_Drv_InputMap = sCfgData.psAdcInputChCfg;

  // Global config for Adc instances and self calibration sequence
  for (ucAdcInstIndx = 0u; ucAdcInstIndx < sCfgData.psAdcInstanceCfg.ucCfgLength; ucAdcInstIndx++)
  {
    // Global config for Adc instances
    (void)CddAdc_Drv_ConfigAdc(&sCfgData.psAdcInstanceCfg.psAdcInstCfg[ucAdcInstIndx]);
    // Self calibration sequence
    (void)CddAdc_Drv_AutoCalibration(&sCfgData.psAdcInstanceCfg.psAdcInstCfg[ucAdcInstIndx]);
  }

  // Init ADC channels present in channels configuration input
  for (ucAdcChIdx = 0u; ucAdcChIdx < sCfgData.psAdcInputChCfg.ucCfgLength; ucAdcChIdx++)
  {
    CddAdc_Drv_AdcChInit(&sCfgData.psAdcInputChCfg.psAdcInCfg[ucAdcChIdx]);
  }

  return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_ConfigAdc
///
/// \descr
///
/// \param  sAdcConfig
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
static Std_ReturnType CddAdc_Drv_ConfigAdc(const tsCddAdc_AdcInstanceCfg * const sAdcConfig)
{
  uint32  ulAdcClkFreq = ADC_CLOCK_FREQ_SOURCE;
  Std_ReturnType eRetStatus = E_OK;
  tsCddAdc_SimReg * const psSimBaseAddr = SIM;
  vuint32 ulRegRead = 0u;

  ulAdcClkFreq = ulAdcClkFreq / (uint32)(1u << (uint32)(sAdcConfig->eClkDiv));

  if ((sAdcConfig->eClkDiv <= NUMBER_OF_ALT_CLOCKS) || (ulAdcClkFreq < ADC_CLOCK_FREQ_MIN_RUNTIME) || (ulAdcClkFreq > ADC_CLOCK_FREQ_MAX_RUNTIME) ||
    ((sAdcConfig->psAdcInst == ADC1) && (sAdcConfig->boSupplyMonitoringEnable != FALSE)))
  {
    eRetStatus = E_NOT_OK;
  }
  else
  {
    // Keep Init config
  }

  if (eRetStatus == E_OK)
  {
    // Adc instance clock divide initialization
    CddAdc_Drv_SetAdcClkDivider(sAdcConfig->psAdcInst, (uint32)sAdcConfig->eClkDiv);
    // Adc sample time initialization
    CddAdc_Drv_SetAdcSampleNr(sAdcConfig->psAdcInst, (sAdcConfig->ulSampleTime > 0u) ? sAdcConfig->ulSampleTime : 1u);

    // Adc resolution initialization
    CddAdc_Drv_SetAdcResolution(sAdcConfig->psAdcInst, (uint32)sAdcConfig->eResolution);
    // Adc input clock initialization
    CddAdc_Drv_SetAdcClkIn(sAdcConfig->psAdcInst, (uint32)sAdcConfig->eInputClock);
    // Adc input trigger initialization
    CddAdc_Drv_SetAdcTrgType(sAdcConfig->psAdcInst, (uint32)sAdcConfig->eTrigger);
    // Adc pretrigger select initialization

    // Adc trigger select initialization
    CddAdc_Drv_SetAdcTrgInput(sAdcConfig->psAdcInst, (uint32)sAdcConfig->eTriggerSel);
    CddAdc_Drv_SetAdcPreTrgInput(sAdcConfig->psAdcInst, (uint32)sAdcConfig->ePreTriggerSel);

    // Adc dma config initialization
    CddAdc_Drv_SetAdcDmaEnbl(sAdcConfig->psAdcInst, (sAdcConfig->boDmaEnable != FALSE) ? 1u : 0u);
    // Adc reference initialization
    CddAdc_Drv_SetAdcRefSel(sAdcConfig->psAdcInst, (uint32)sAdcConfig->eVoltageRef);

    // Adc average conversion config
    if (sAdcConfig->boAvgEnable != FALSE)
    {
      // Set number of samples t be averaged
      CddAdc_Drv_SetAdcAvgMode(sAdcConfig->psAdcInst, (uint32)sAdcConfig->eAverageCfg);
      // Average enable
      CddAdc_Drv_SetAdcAvgEnbl(sAdcConfig->psAdcInst, 1u);
    }
    else
    {
      // Average disable
      CddAdc_Drv_SetAdcAvgEnbl(sAdcConfig->psAdcInst, 0u);
    }

    // Adc continous convertion initialization
    CddAdc_Drv_SetAdcContinousMode(sAdcConfig->psAdcInst, (sAdcConfig->boContinuousConvEnable != FALSE) ? 1u : 0u);

    // Adc supply monitoring configuration only for ADC0
    CddAdc_Drv_SetAdcSupplyEn(sAdcConfig->psAdcInst, (sAdcConfig->boSupplyMonitoringEnable != FALSE) ? 1u : 0u);
  }
  else
  {
  }

  return (eRetStatus);
}


//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  sAdcConfig
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
static Std_ReturnType CddAdc_Drv_AutoCalibration(const tsCddAdc_AdcInstanceCfg * const sAdcConfig)
{
  // Set Adc Clk Frequence
  vuint32  ulAdcClkFreq = ADC_CLOCK_FREQ_SOURCE;
  // Clk divider to be applied
  vuint32 ulAdcClkDived_App = (vuint32)eADC_CLK_DIVIDE_1;
  // Auto Calibration return status
  Std_ReturnType eRetStatus = E_OK;
  // Auto calibration while breaker
  vuint32 ulAdcAutoCalBreakCnt = 0xFFFFu;
  // Get Average Enable Status
  vuint32 ulAdcAvgEnableStatus = (sAdcConfig->psAdcInst->SC3.Reg >> 2u) & 0x1u;
  // Get Average Mode
  vuint32 ulAdcAverageMode = (sAdcConfig->psAdcInst->SC3.Reg >> 0u) & 0x3u;
  // Get Trigger Mode
  vuint32 ulAdcTriggerMode = (sAdcConfig->psAdcInst->SC2.Reg >> 6u) & 0x1u;
  // Get Sample Time
  vuint32 ulAdcSampleTime = (sAdcConfig->psAdcInst->CFG2.Reg >> 0u) & 0xFFu;
  // Get current Adc Clk divide 
  vuint32 ulAdcClkDivide = (sAdcConfig->psAdcInst->CFG1.Reg >> 5u) & 0x3u;

  // Set Adc conversion as average of 32 samples.
  CddAdc_Drv_SetAdcAvgMode(sAdcConfig->psAdcInst, (uint32)eADC_AVERAGE_32);

  // Set Adc conversion average enable
  CddAdc_Drv_SetAdcAvgEnbl(sAdcConfig->psAdcInst, 1u);

  //Set Sw Trigger mode
  CddAdc_Drv_SetAdcTrgType(sAdcConfig->psAdcInst, (uint32)eADC_TRIGGER_SOFTWARE);

  // Set Sample Time value to the reset typical
  CddAdc_Drv_SetAdcSampleNr(sAdcConfig->psAdcInst, (uint32)ADC_RESET_SAMPLE_TIME_VALUE);

  // Reset all calibration registers
  sAdcConfig->psAdcInst->CLPS.Reg = (vuint32)0u;
  sAdcConfig->psAdcInst->CLP3.Reg = (vuint32)0u;
  sAdcConfig->psAdcInst->CLP2.Reg = (vuint32)0u;
  sAdcConfig->psAdcInst->CLP1.Reg = (vuint32)0u;
  sAdcConfig->psAdcInst->CLP0.Reg = (vuint32)0u;
  sAdcConfig->psAdcInst->CLPX.Reg = (vuint32)0u;
  sAdcConfig->psAdcInst->CLP9.Reg = (vuint32)0u;

  // Set clock divider for auto calibration
  if ((ulAdcClkFreq / (1u << ulAdcClkDivide)) <= (ADC_CLOCK_FREQ_MAX_RUNTIME / 2u))
  {
    // Clock divider ok for auto calibration
  }
  else if ((ulAdcClkFreq / 2u) <= (ADC_CLOCK_FREQ_MAX_RUNTIME / 2u))
  {
    ulAdcClkDived_App = (uint32)eADC_CLK_DIVIDE_2;
  }
  else if ((ulAdcClkFreq / 4u) <= (ADC_CLOCK_FREQ_MAX_RUNTIME / 2u))
  {
    ulAdcClkDived_App = (uint32)eADC_CLK_DIVIDE_4;
  }
  else if ((ulAdcClkFreq / 8u) <= (ADC_CLOCK_FREQ_MAX_RUNTIME / 2u))
  {
    ulAdcClkDived_App = (uint32)eADC_CLK_DIVIDE_8;
  }
  else
  {
    // Something is wrong, divider cannot configured
    eRetStatus = E_NOT_OK;
  }

  // If clock divider config is ok, write new configuration otherwise keep the older one
  CddAdc_Drv_SetAdcClkDivider(sAdcConfig->psAdcInst, (eRetStatus == E_OK) ? ulAdcClkDived_App : ulAdcClkDivide);

  // Set calibration active flag
  CddAdc_Drv_SetAdcStartCalibration(sAdcConfig->psAdcInst);

  // Wait for complete auto calibration
  while ((CddAdc_Drv_GetCalibrationStatus(sAdcConfig->psAdcInst) == FALSE) && (ulAdcAutoCalBreakCnt > 0u))
  {
    ulAdcAutoCalBreakCnt--;
  }

  // Auto Calibration is not set, report error
  eRetStatus = (ulAdcAutoCalBreakCnt == 0u) ? E_NOT_OK : eRetStatus;

  // Reverse Adc settings before self calibration (clock divide, average, tigger and sample nr)
  CddAdc_Drv_SetAdcClkDivider(sAdcConfig->psAdcInst, ulAdcClkDivide);
  CddAdc_Drv_SetAdcAvgMode(sAdcConfig->psAdcInst, ulAdcAverageMode);
  CddAdc_Drv_SetAdcAvgEnbl(sAdcConfig->psAdcInst, ulAdcAvgEnableStatus);
  CddAdc_Drv_SetAdcTrgType(sAdcConfig->psAdcInst, ulAdcTriggerMode);
  CddAdc_Drv_SetAdcSampleNr(sAdcConfig->psAdcInst, ulAdcSampleTime);

  return (eRetStatus);
}


//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  sAdcChInCfg
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_AdcChInit(const tsCddAdc_AdcInputCfg* const sAdcChInCfg)
{
  // Get Adc Channel number
  uint8 ucAdcChannelNo = sAdcChInCfg->ucAdcCh;

  // Set Adc Ch to stop conversion mode
  CddAdc_Drv_SetAdcChnInput(sAdcChInCfg, CDDADC_ADCH_MASK);
  // Select input for Adc Channels
  CddAdc_Drv_SetAdcChnInput(sAdcChInCfg, (uint32)sAdcChInCfg->eInCh);
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_SwReadChannel
///
/// \descr
///
/// \param  ucInput
/// \param  sChnCfg
///
/// \return STATIC_AL teCddAdc_AdcErrorStat
//-----------------------------------------------------------------------------
static Std_ReturnType CddAdc_Drv_SwReadChannel(uint8 ucInput, tsCddAdc_AdcInputCfg const sChnCfg[], uint16 * unAdcData)
{
  // Read channel return status
  Std_ReturnType eRetStatus = E_OK;
  // Auto calibration while breaker
  vuint32 ulAdcAutoCalBreakCnt = 0xFFFFu;
  // Register number selector
  uint8 ucRegNo;
  // Input channel selector
  teCddAdc_InChMap eInChSel;
  // Interrupt Enable
  boolean boChIntEnbl;
  //
  vuint32 ulRegValue = 0u;

  if (ucInput > CddAdc_Drv_InputMap.ucCfgLength)
  {
    // Input out of range
    eRetStatus = E_NOT_OK;
  }
  else
  {
    // Update Channel conversion Register (Only SC1 is suported)
    ucRegNo = 0u;
    eInChSel = sChnCfg[ucInput].eInCh;
    boChIntEnbl = sChnCfg[ucInput].boIntEnbl;
    ulRegValue = sChnCfg[ucInput].psAdcInst->SC1[ucRegNo].Reg;
    ulRegValue = ulRegValue & 0xFFFFFF80u;
    ulRegValue = ulRegValue | ((uint32)eInChSel << 0u);
    ulRegValue = ulRegValue | ((boChIntEnbl != FALSE) ? (1u << 6u) : 0u);
    sChnCfg[ucInput].psAdcInst->SC1[ucRegNo].Reg = ulRegValue;

    // wait for conversion complete
    while ((CddAdc_Drv_GetAdcCompleteConvStat(sChnCfg->psAdcInst) == FALSE) && (ulAdcAutoCalBreakCnt > 0u))
    {
      ulAdcAutoCalBreakCnt--;
    }

    if (ulAdcAutoCalBreakCnt != 0u)
    {
      // Adc conversion Ok
      *unAdcData = (uint16)sChnCfg[ucInput].psAdcInst->R[ucRegNo].Reg;
    }
    else
    {
      // Adc conversion too long, report error
      *unAdcData = 0xFFFF;
      eRetStatus = E_NOT_OK;
    }
  }

  return (eRetStatus);
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_GetAdcRawValue
///
/// \descr
///
/// \param  ucInputIx
///
/// \return uint16
//-----------------------------------------------------------------------------
uint16 CddAdc_Drv_GetAdcRawValue(uint8 ucInputIx)
{
  uint16 unAdcRawVal = 0u;

  if (CddAdc_Drv_InputMap.ucCfgLength < ucInputIx)
  {
    unAdcRawVal = 0xFFFFu;
  }
  else
  {
    unAdcRawVal = (uint16)*CddAdc_Drv_InputMap.psAdcInCfg[ucInputIx].pulAdcData;
  }

  return unAdcRawVal;
}


//-----------------------------------------------------------------------------
/// \brief CddAdc_Drv_SetAdcClkDivider
///
/// \descr
///
/// \param  [paramName]
///
/// \return [returnTyp]
//-----------------------------------------------------------------------------
static void CddAdc_Drv_SetAdcClkDivider(tsCddAdc_AdcReg* const psAdcInst, uint32 ulDividerVal)
{
  vuint32 ulRegValue = psAdcInst->CFG1.Reg;

  ulRegValue = ulRegValue & 0xFFFFF9Fu;
  ulRegValue = ulRegValue | (ulDividerVal << 5u);
  psAdcInst->CFG1.Reg = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_Drv_SetAdcSampleNr
///
/// \descr
///
/// \param  psAdcInst
/// \param  ulSmplNr
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_SetAdcSampleNr(tsCddAdc_AdcReg* const psAdcInst, uint32 ulSmplNr)
{
  vuint32 ulRegValue = psAdcInst->CFG2.Reg;

  ulRegValue = ulRegValue & 0xFFFFF00u;
  ulRegValue = ulRegValue | (ulSmplNr << 0u);
  psAdcInst->CFG2.Reg = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_Drv_SetAdcResolution
///
/// \descr
///
/// \param  psAdcInst
/// \param  ulResolution
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_SetAdcResolution(tsCddAdc_AdcReg* const psAdcInst, uint32 ulResolution)
{
  vuint32 ulRegValue = psAdcInst->CFG1.Reg;

  ulRegValue = ulRegValue & 0xFFFFFF3u;
  ulRegValue = ulRegValue | (ulResolution << 2u);
  psAdcInst->CFG1.Reg = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  psAdcInst
/// \param  ulClkIn
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_SetAdcClkIn(tsCddAdc_AdcReg* const psAdcInst, uint32 ulClkIn)
{
  vuint32 ulRegValue = psAdcInst->CFG1.Reg;

  ulRegValue = ulRegValue & 0xFFFFFFCu;
  ulRegValue = ulRegValue | (ulClkIn << 0u);
  psAdcInst->CFG1.Reg = ulRegValue;
}


//-----------------------------------------------------------------------------
/// \brief CddAdc_Drv_SetAdcTrgType
///
/// \descr
///
/// \param  psAdcInst
/// \param  ulTriggerTp
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_SetAdcTrgType(tsCddAdc_AdcReg* const psAdcInst, uint32 ulTriggerTp)
{
  vuint32 ulRegValue = psAdcInst->SC2.Reg;

  ulRegValue = ulRegValue & 0xFFFFFBFu;
  ulRegValue = ulRegValue | (ulTriggerTp << 6u);
  psAdcInst->SC2.Reg = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_Drv_SetAdcTrgInput
///
/// \descr
///
/// \param  psAdcInst
/// \param  ulTriggerIn
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_SetAdcTrgInput(tsCddAdc_AdcReg* const psAdcInst, uint32 ulTriggerIn)
{
  tsCddAdc_SimReg * const psSimBaseAddr = SIM;

  vuint32 ulRegValue = psSimBaseAddr->ADCOPT.Reg;

  if (psAdcInst == ADC0)
  {
    ulRegValue = ulRegValue & 0xFFFFFFFEu;
    ulRegValue = ulRegValue | (ulTriggerIn << 0u);
  }
  else
  {
    ulRegValue = ulRegValue & 0xFFFFFEFFu;
    ulRegValue = ulRegValue | (ulTriggerIn << 8u);
  }

  psSimBaseAddr->ADCOPT.Reg = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_Drv_SetAdcPreTrgInput
///
/// \descr
///
/// \param  psAdcInst
/// \param  ulPreTriggerIn
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_SetAdcPreTrgInput(tsCddAdc_AdcReg* const psAdcInst, uint32 ulPreTriggerIn)
{
  tsCddAdc_SimReg * const psSimBaseAddr = SIM;

  vuint32 ulRegValue = psSimBaseAddr->ADCOPT.Reg;

  if (psAdcInst == ADC0)
  {
    ulRegValue = ulRegValue & 0xFFFFFFCFu;
    ulRegValue = ulRegValue | (ulPreTriggerIn << 4u);
  }
  else
  {
    ulRegValue = ulRegValue & 0xFFFFCFFFu;
    ulRegValue = ulRegValue | (ulPreTriggerIn << 12u);
  }

  psSimBaseAddr->ADCOPT.Reg = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  psAdcInst
/// \param  ulDmaEnbl
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_SetAdcDmaEnbl(tsCddAdc_AdcReg* const psAdcInst, uint32 ulDmaEnbl)
{
  vuint32 ulRegValue = psAdcInst->SC2.Reg;

  ulRegValue = ulRegValue & 0xFFFFFFBu;
  ulRegValue = ulRegValue | (ulDmaEnbl << 2u);
  psAdcInst->SC2.Reg = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_Drv_SetAdcRefSel
///
/// \descr
///
/// \param  psAdcInst
/// \param  ulRefSel
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_SetAdcRefSel(tsCddAdc_AdcReg* const psAdcInst, uint32 ulRefSel)
{
  vuint32 ulRegValue = psAdcInst->SC2.Reg;

  ulRegValue = ulRegValue & 0xFFFFFFCu;
  ulRegValue = ulRegValue | (ulRefSel << 0u);
  psAdcInst->SC2.Reg = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  psAdcInst
/// \param  ulAvgEnbl
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_SetAdcAvgEnbl(tsCddAdc_AdcReg* const psAdcInst, uint32 ulAvgEnbl)
{
  vuint32 ulRegValue = psAdcInst->SC3.Reg;

  ulRegValue = ulRegValue & 0xFFFFFFBu;
  ulRegValue = ulRegValue | (ulAvgEnbl << 2u);
  psAdcInst->SC3.Reg = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  psAdcInst
/// \param  ulAvgMode
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_SetAdcAvgMode(tsCddAdc_AdcReg* const psAdcInst, uint32 ulAvgMode)
{
  vuint32 ulRegValue = psAdcInst->SC3.Reg;

  ulRegValue = ulRegValue & 0xFFFFFFCu;
  ulRegValue = ulRegValue | (ulAvgMode << 0u);
  psAdcInst->SC3.Reg = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  psAdcInst
/// \param  ulContinousMode
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_SetAdcContinousMode(tsCddAdc_AdcReg* const psAdcInst, uint32 ulContinousMode)
{
  vuint32 ulRegValue = psAdcInst->SC3.Reg;

  ulRegValue = ulRegValue & 0xFFFFFF7u;
  ulRegValue = ulRegValue | (ulContinousMode << 3u);
  psAdcInst->SC3.Reg = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_Drv_SetAdcSupplyEn
///
/// \descr
///
/// \param  psAdcInst
/// \param  ulSupplyEn
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_SetAdcSupplyEn(tsCddAdc_AdcReg* const psAdcInst, uint32 ulSupplyEn)
{
  tsCddAdc_SimReg * const psSimBaseAddr = SIM;

  vuint32 ulRegValue = psSimBaseAddr->CHIPCTL.Reg;

  if (psAdcInst == ADC0)
  {
    ulRegValue = ulRegValue & 0xFFF7FFFFu;
    ulRegValue = ulRegValue | (ulSupplyEn << 19u);
  }
  else
  {
    //
  }

  psSimBaseAddr->CHIPCTL.Reg = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  psAdcInst
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_SetAdcStartCalibration(tsCddAdc_AdcReg* const psAdcInst)
{
  vuint32 ulRegValue = psAdcInst->SC3.Reg;

  ulRegValue = ulRegValue & 0xFFFFF7Fu;
  ulRegValue = ulRegValue | (1u << 7u);
  psAdcInst->SC3.Reg = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_Drv_GetCalibrationStatus
///
/// \descr
///
/// \param  psAdcInst
///
/// \return boolean
//-----------------------------------------------------------------------------
static boolean CddAdc_Drv_GetCalibrationStatus(tsCddAdc_AdcReg* const psAdcInst)
{
  return ((((psAdcInst->SC3.Reg >> 8u) & 0x1u) != 0u) ? FALSE : TRUE);
}


//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  sAdcChInCfg
/// \param  ulInputSel
///
/// \return void
//-----------------------------------------------------------------------------
static void CddAdc_Drv_SetAdcChnInput(const tsCddAdc_AdcInputCfg* const sAdcChInCfg, uint32 ulInputSel)
{
  // Get Adc Channel number
  uint8 ucAdcChannelNo = sAdcChInCfg->ucAdcCh;

  vuint32 ulRegValue = sAdcChInCfg->psAdcInst->SC1[ucAdcChannelNo].Reg;

  ulRegValue = ulRegValue & 0xFFFFFFC0u;
  ulRegValue = ulRegValue | (ulInputSel << 0u);

  sAdcChInCfg->psAdcInst->SC1[ucAdcChannelNo].Reg = ulRegValue;
}

//-----------------------------------------------------------------------------
/// \brief CddAdc_Drv_GetAdcCompleteConvStat
///
/// \descr
///
/// \param  sAdcChInCfg
///
/// \return boolean
//-----------------------------------------------------------------------------
static boolean CddAdc_Drv_GetAdcCompleteConvStat(tsCddAdc_AdcReg* const psAdcInst)
{
  vuint32 ulRegValue = psAdcInst->SC2.Reg;

  return (((psAdcInst->SC2.Reg >> 7u) & 0x1u) != 0x0u) ? TRUE : FALSE;
}
// EOF
