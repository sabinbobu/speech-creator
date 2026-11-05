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
/// \file   SysMonCheck_Data.c
///
/// \brief  
///
/// \descr  Functions for data manipulation in SysMonCheck
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <SysMonCheck_Data.h>
#include <SysMonCheck.h>
#include <SysMon_Types.h>
#include <CodM_Para.h>
#include <Crc.h>
#include <SysMonCheck_LedDiag.h>

//-----------------------------------------------------------------------------
// Static variable declarations
//-----------------------------------------------------------------------------
STATIC_AL tSysMonCheck_Data_LedChParam      SysMonCheck_Data_aLedChParam[SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS];
STATIC_AL boolean                           SysMonCheck_Data_boIsCodingDataValid = FALSE;
STATIC_AL tSysMonCheck_Data_FuSaParamValid  SysMonCheck_Data_eAreFuSaParamValid = SysMonCheck_Data_FuSaParamUnknown;
STATIC_AL boolean                           SysMonCheck_Data_boFuSaIntegrityCheckPerformed = FALSE;
STATIC_AL tSysMonCheck_Data_FuSaParam       SysMonCheck_Data_FuSaParam_raw;
STATIC_AL tsSysMonCheck_Data_EftData        SysMonCheck_Data_sEftData;

// Coding Data
STATIC_AL tsRteCodingParameters             SysMonCheck_Data_sCodingParam;
CONST_AL  tNvmPara_CodingArea*              SysMonCheck_Data_pCodingArea = NULL_PTR;
STATIC_AL tsSysMon_Error                    SysMonCheck_Data_sLed_Debounce;

STATIC_AL boolean                           SysMonCheck_Data_IsLowBeamEnabled = TRUE;
STATIC_AL boolean                           SysMonCheck_Data_IsTurnIndEnabled = TRUE;
STATIC_AL boolean                           SysMonCheck_Data_boAreFuSaParam_Invalid = FALSE;

STATIC_AL boolean                           SysMonCheck_Data_boCrc32OverCoding = FALSE;
STATIC_AL uint32                            SysMonCheck_Data_ulComputedFusaCrc = 0u;

STATIC_AL boolean                           SysMonCheck_Data_boCrc32RamFail = FALSE;
STATIC_AL boolean                           SysMonCheck_Data_boCrc32RomFail = FALSE;

// Status of Turn Indicator Scrolling presence
STATIC_AL boolean                           SysMonCheck_Data_boIsTiScrollingPresent = FALSE;

// Timer used to set the restart the CRC check over RAM mirror every 200 ms
STATIC_AL TIMER SysMonCheck_Data_ulCrcRamMirror_us = 0u;

//-----------------------------------------------------------------------------
// Function prototypes
//-----------------------------------------------------------------------------
STATIC_AL void                      SysMonCheck_Data_Init(void);
STATIC_AL void                      SysMonCheck_Data_FuSaCodingIntegrityCheck(void);
STATIC_AL boolean                   SysMonCheck_Data_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData);
STATIC_AL void                      SysMonCheck_Data_GetFusaParam(tSysMonCheck_Data_FuSaParam * CONST_AL pFuSaParam, tsSysMon_Error * CONST_AL pErrorDebounce);
STATIC_AL boolean                   SysMonCheck_Data_CheckCrcForFuSaParameters(void);
STATIC_AL boolean                   SysMonCheck_Data_FuSaParamRangeCheckLB(void);
STATIC_AL boolean                   SysMonCheck_Data_FuSaParamRangeCheckTI(void);
STATIC_AL boolean                   SysMonCheck_Data_IsNbOfFuSaChannelsAllowed(void);
STATIC_AL boolean                   SysMonCheck_Data_AreAllLedChSupportedByHw(void);
STATIC_AL void                      SysMonCheck_Data_ComputeFuSaParam(void);
STATIC_AL SysMonCheck_Data_tLFName  SysMonCheck_Data_GetLFName(uint8 ucLFIndex);
STATIC_AL uint16                    SysMonCheck_Data_GetMinPwmDuty(uint8 ucLFIndex);
STATIC_AL uint16                    SysMonCheck_Data_GetMinCurrent(uint8 ucLFIndex);
STATIC_AL uint32                    SysMonCheck_Data_GetLedOverVoltValue(uint8 ucLFIndex);
STATIC_AL uint32                    SysMonCheck_Data_GetLedUnderVoltValue(uint8 ucLFIndex);
STATIC_AL uint32                    SysMonCheck_Data_CalcComputedFuSaParamCrc32(void);
STATIC_AL void                      SysMonCheck_Data_RamMCodingMirrorCheck(void);
STATIC_AL void                      SysMonCheck_Data_GetEftData(tsSysMonCheck_Data_EftData * CONST_AL pEftData);
STATIC_AL void                      SysMonCheck_Data_CheckEFT_ECUVARCFG_LED(void);
STATIC_AL void                      SysMonCheck_Data_Set_Crc32RamFailure(boolean boCrc32RamFail);
STATIC_AL void                      SysMonCheck_Data_Set_Crc32RomFailure(boolean boCrc32RomFail);

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
STATIC_AL boolean                   SysMonCheck_Data_IsTiScrollingPresent(void);
#endif // CFG_VARIANT_FULL


//-----------------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------------
#define SYSMONCHECK_DATA_SCALE_VOLTAGE_UINT8_UINT32(x) ((uint32)((uint32)(x) * 51U * 1000u / 255u ))
#define SYSMONCHECK_DATA_UINT8_0_5PERCENT_TO_PERCENT(x) (uint16)((uint16)(x)/2u)

//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_CodingDataValidation
///
/// \descr  Get and handle coding parameters for SysMonCheck module
///
/// \param  void
///
/// \return return validity of coding as TRUE
//-----------------------------------------------------------------------------
boolean SysMonCheck_Data_CodingDataValidation(void)
{
  //get coding data via RTE
  (void)Rte_Read_CodM_SysMon_Para(&SysMonCheck_Data_sCodingParam);
  //get coding data and return validity of this
  CONST_AL boolean boCodingValidity = SysMonCheck_Data_ParaFct0(SysMonCheck_Data_sCodingParam.eCodingState, SysMonCheck_Data_sCodingParam.psCodingParameters_Blocks);
  //return validity of coding
  return boCodingValidity;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_ParaFct0
///
/// \descr  This function gets coding params and validity of coding data 
///
/// \param  eCmd - valid/invalid, pData - coding params
///
/// \return coding validity
//-----------------------------------------------------------------------------
STATIC_AL boolean SysMonCheck_Data_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData)
{
  boolean boCodingValidity = FALSE;

  switch (eCmd)
  {
  case eParaFct0_CodingDataValid:
    boCodingValidity = TRUE;
    SysMonCheck_Data_pCodingArea = pData;
    break;
  case eParaFct0_CodingDataInvalid:
    boCodingValidity = FALSE;
    break;
  default:
    break;
  }
  return boCodingValidity;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_SetCodingDataSatus
///
/// \descr  Set the validity status of the coding parameters.
///         In case the validity status switches from invalid to valid, coding parameters
///         are loaded or reloaded.
///
/// \param  boIsCodingDataValid
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonCheck_Data_SetCodingDataSatus(boolean boIsCodingDataValid)
{
  // If coding data switch from Invalid to valid
  if ((boIsCodingDataValid != FALSE)
    && (SysMonCheck_Data_boIsCodingDataValid == FALSE))
  {
    //Trigger loading or reloading of parameters
    SysMonCheck_Data_Init();

    // Reset Integrity check flag in order to recheck the new FuSa coding param
    // in case of recodding during runtime. Use case for HIL test purposes.
    SysMonCheck_Data_boFuSaIntegrityCheckPerformed = FALSE;
    SysMonCheck_Data_eAreFuSaParamValid = SysMonCheck_Data_FuSaParamUnknown;
  }
  else
  {
    // nothing to do
  }
  //Set the current status of coding data
  SysMonCheck_Data_boIsCodingDataValid = boIsCodingDataValid;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_Init
///
/// \descr  Initialized the coding parameters
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonCheck_Data_Init(void)
{
  SysMonCheck_Data_IsLowBeamEnabled = TRUE;
  SysMonCheck_Data_IsTurnIndEnabled = TRUE;

  // Reset EFT Data Validity
  SysMonCheck_Data_sEftData.boEftDataValid = FALSE;

  for (uint8 ucChIdx = 0u; ucChIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS; ucChIdx++)
  {
    // Reset debounce timers
    SysMonCheck_Data_sLed_Debounce.ucLed_Debounce[ucChIdx]  = 0u;

    // Reset EFT data
    SysMonCheck_Data_sEftData.aucAssignedOutput[ucChIdx]    = 0u;
    SysMonCheck_Data_sEftData.aunImax[ucChIdx]              = 0u;
  }
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_Cycle10ms_FuSaMonitoring
///
/// \descr  Verify integrity of coding parameters
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonCheck_Data_Cycle10ms_FuSaMonitoring(void)
{
  if (SysMonCheck_Data_boIsCodingDataValid != FALSE)
  {
    // FuSa parameters integrity is checked once at startup
    if (SysMonCheck_Data_boFuSaIntegrityCheckPerformed == FALSE)
    {
      SysMonCheck_Data_FuSaCodingIntegrityCheck();
      SysMonCheck_Data_boFuSaIntegrityCheckPerformed = TRUE;
    }
    else
    {
      // Check for CRC32 check at startup over ROM FuSa Coding area
      if (SysMonCheck_Data_boCrc32RomFail == FALSE)
      {
        // Check every 200 ms to see if the CRC over the RAM coding mirror is consistent
        SysMonCheck_Data_RamMCodingMirrorCheck();
      }
      else
      {
        // nothing to do because CRC32 at startup has failed
      }
    }
  }
  else
  {
    SysMonCheck_Data_eAreFuSaParamValid = SysMonCheck_Data_FuSaParamInvalid;
  }
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_FuSaCodingIntegrityCheck
///
/// \descr  Integrity check of FUSA coding parameters
///         Shall be performed only one time at start up
///         Checks for CRC32, HW support configuration and number of configured LowBeam and TurnIndicator channels:
///
///  Number of configured channels  DTC Status           LB and TI Status
///         LB + TI > 6              Active              LB and TI disabled
///         LB + TI < 6              Inactive            LB and TI Enabled
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonCheck_Data_FuSaCodingIntegrityCheck(void)
{
  // Read FuSa coding parameters
  SysMonCheck_Data_GetFusaParam(&SysMonCheck_Data_FuSaParam_raw, &SysMonCheck_Data_sLed_Debounce);

  // Get CRC32 over FuSa coding block from CodM
  SysMonCheck_Data_boCrc32OverCoding = SysMonCheck_Data_CheckCrcForFuSaParameters();

  // Get EFT Data
  SysMonCheck_Data_GetEftData(&SysMonCheck_Data_sEftData);

  // Perform range check on TI FuSa coding parameters
  boolean SysMonCheck_Data_bFuSaParamRangeCheckTI = SysMonCheck_Data_FuSaParamRangeCheckTI();
  // Perform range check on LB FuSa coding parameters
  boolean SysMonCheck_Data_bFuSaParamRangeCheckLB = SysMonCheck_Data_FuSaParamRangeCheckLB();
  // Perform check on number of FuSa channels allowed
  boolean SysMonCheck_Data_bIsNbOfFuSiChannelsAllowed = SysMonCheck_Data_IsNbOfFuSaChannelsAllowed();

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  // Perform check if TI_SCRL is present in Coding Data
  SysMonCheck_Data_boIsTiScrollingPresent = SysMonCheck_Data_IsTiScrollingPresent();
#endif // CFG_VARIANT_FULL

  // CRC check of FuSa coding parameters
  if (SysMonCheck_Data_boCrc32OverCoding != FALSE)
  {
    // Validate CRC32 over ROM check
    SysMonCheck_Data_Set_Crc32RomFailure(FALSE);

    // CRC check sucessful, check if the number of coded FuSa relevant channels does not exceeds 6
    if (SysMonCheck_Data_AreAllLedChSupportedByHw() != FALSE) // If all Led Channels are populated on HW
    {
      // All FuSa relevant channels are supported by the hardware

      // Compute raw FuSa coding parameters
      SysMonCheck_Data_ComputeFuSaParam();
      // Only after this point, the other parts of SysMon are allowed to use FUSA parameters
      SysMonCheck_Data_eAreFuSaParamValid = SysMonCheck_Data_FuSaParamValid;

      // Perform a range check on specific FUSI coding parameters
      if ((SysMonCheck_Data_bFuSaParamRangeCheckTI != FALSE) && (SysMonCheck_Data_bFuSaParamRangeCheckLB != FALSE) && (SysMonCheck_Data_bIsNbOfFuSiChannelsAllowed != FALSE))
      {
        // Fusi coding parameter integrity check successful !
        SysMonCheck_Data_boAreFuSaParam_Invalid = FALSE;
      }
      else // at least one FuSi parameter is not in the expected range
      {
        if ((SysMonCheck_Data_bFuSaParamRangeCheckTI == FALSE) || (SysMonCheck_Data_bIsNbOfFuSiChannelsAllowed == FALSE))
        {
          // Turn Off TI channels
          SysMonCheck_TurnOffFusaChannels(SysMonCheck_Data_eLF_TI);
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
          SysMonCheck_TurnOffFusaChannels(SysMonCheck_Data_eLF_TI_SCRL);
#endif // CFG_VARIANT_FULL
          SysMonCheck_Data_IsTurnIndEnabled = FALSE;
        }
        else
        {
          // nothing to do
        }

        if ((SysMonCheck_Data_bFuSaParamRangeCheckLB == FALSE) || (SysMonCheck_Data_bIsNbOfFuSiChannelsAllowed == FALSE))
        {
          // Turn Off Low Beam FuSa channels
          SysMonCheck_TurnOffFusaChannels(SysMonCheck_Data_eLF_LB_FuSa);
          SysMonCheck_Data_IsLowBeamEnabled = FALSE;
        }
        else
        {
          // nothing to do
        }
      }
    }
    else // At least one coded LED channel is not populated on HW
    {
      //All light source channels are disabled in SysMon_LedCtrl_Cycle()
      SysMonCheck_Data_eAreFuSaParamValid = SysMonCheck_Data_FuSaParamInvalid;
      // Turn Off Turn Indicator
      SysMonCheck_Data_IsTurnIndEnabled = FALSE;
      // Turn Off Low Beam
      SysMonCheck_Data_IsLowBeamEnabled = FALSE;
    }
  }
  else // CRC does not match
  {
    //All light source channels are disabled in SysMon_LedCtrl_Cycle()
    SysMonCheck_Data_eAreFuSaParamValid      = SysMonCheck_Data_FuSaParamInvalid;
    SysMonCheck_Data_boAreFuSaParam_Invalid  = TRUE;
    SysMonCheck_Data_Set_Crc32RomFailure(TRUE);
  }

  // Check EFT LED channel maximum current
  SysMonCheck_Data_CheckEFT_ECUVARCFG_LED();
} // PRQA S 5324, 5336 1 // Readability


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_GetFusaParam
///
/// \descr  Get the parameters from Coding into the RAM mirror
///
/// \param  pFuSaParam
///         pErrorDebounce
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonCheck_Data_GetFusaParam(tSysMonCheck_Data_FuSaParam * CONST_AL pFuSaParam, tsSysMon_Error * CONST_AL pErrorDebounce)
{
  for (uint8 ucDRVIdx = 0u; ucDRVIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS; ucDRVIdx++)
  {
    pFuSaParam->aucFUSA_DRVxx_NAMES_ASIL[ucDRVIdx]             = SysMonCheck_Data_pCodingArea->Led1.FUSAConfig.FUSA_DRV01_NAMES[ucDRVIdx];
    pFuSaParam->aucFUSA_DRVxx_LED_UNDER_VOLTAGE_ASIL[ucDRVIdx] = SysMonCheck_Data_pCodingArea->Led1.FUSAConfig.FUSA_DRV01_LED_UNDER_VOLTAGE[ucDRVIdx];
    pFuSaParam->aucFUSA_DRVxx_LED_OVER_VOLTAGE_ASIL[ucDRVIdx]  = SysMonCheck_Data_pCodingArea->Led1.FUSAConfig.FUSA_DRV01_LED_OVER_VOLTAGE[ucDRVIdx];
    pFuSaParam->aucFUSA_DRVxx_MIN_PWM_ASIL[ucDRVIdx]           = SysMonCheck_Data_pCodingArea->Led1.FUSAConfig.FUSA_DRV01_MIN_PWM[ucDRVIdx];
    pFuSaParam->aunFUSA_DRVxx_MIN_CURRENT_ASIL[ucDRVIdx]       = SysMonCheck_Data_pCodingArea->Led1.FUSAConfig.FUSA_MIN_CURRENT_DRVS[ucDRVIdx];
  }

  pFuSaParam->ucFUSA_LB_FS_BEHAVIOUR_ASIL = SysMonCheck_Data_pCodingArea->Led1.FUSAConfig.FUSA_LB_FS_BEHAVIOUR;
  pFuSaParam->ucFUSA_TI_FS_BEHAVIOUR_ASIL = SysMonCheck_Data_pCodingArea->Led1.FUSAConfig.FUSA_TI_FS_BEHAVIOUR;

  pErrorDebounce->ucLed_Debounce[0u]  = SysMonCheck_Data_pCodingArea->Led1.LedConfigDRV01.DRV01_LED_ERROR_DEBOUNCE;
  pErrorDebounce->ucLed_Debounce[1u]  = SysMonCheck_Data_pCodingArea->Led1.LedConfigDRV02.DRV02_LED_ERROR_DEBOUNCE;
  pErrorDebounce->ucLed_Debounce[2u]  = SysMonCheck_Data_pCodingArea->Led1.LedConfigDRV03.DRV03_LED_ERROR_DEBOUNCE;
  pErrorDebounce->ucLed_Debounce[3u]  = SysMonCheck_Data_pCodingArea->Led1.LedConfigDRV04.DRV04_LED_ERROR_DEBOUNCE;
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  pErrorDebounce->ucLed_Debounce[4u]  = SysMonCheck_Data_pCodingArea->Led1.LedConfigDRV05.DRV05_LED_ERROR_DEBOUNCE;
  pErrorDebounce->ucLed_Debounce[5u]  = SysMonCheck_Data_pCodingArea->Led1.LedConfigDRV06.DRV06_LED_ERROR_DEBOUNCE;
  pErrorDebounce->ucLed_Debounce[6u]  = SysMonCheck_Data_pCodingArea->Led1.LedConfigDRV07.DRV07_LED_ERROR_DEBOUNCE;
  pErrorDebounce->ucLed_Debounce[7u]  = SysMonCheck_Data_pCodingArea->Led1.LedConfigDRV08.DRV08_LED_ERROR_DEBOUNCE;
  pErrorDebounce->ucLed_Debounce[8u]  = SysMonCheck_Data_pCodingArea->Led1.LedConfigDRV09.DRV09_LED_ERROR_DEBOUNCE;
  pErrorDebounce->ucLed_Debounce[9u]  = SysMonCheck_Data_pCodingArea->Led1.LedConfigDRV10.DRV10_LED_ERROR_DEBOUNCE;
  pErrorDebounce->ucLed_Debounce[10u] = SysMonCheck_Data_pCodingArea->Led1.LedConfigDRV11.DRV11_LED_ERROR_DEBOUNCE;
  pErrorDebounce->ucLed_Debounce[11u] = SysMonCheck_Data_pCodingArea->Led1.LedConfigDRV12.DRV12_LED_ERROR_DEBOUNCE;
#endif // CFG_VARIANT_FULL
}


//-----------------------------------------------------------------------------
/// \brief SysMonCheck_Data_CheckCrcForFuSaParameters
///
/// \descr Check CRC32 over FuSa coding block
///
/// \param  void
///
/// \return STATIC_AL boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean SysMonCheck_Data_CheckCrcForFuSaParameters(void)
{
  CONST_AL uint8 *psFuSaBlockTrgetAddr = &SysMonCheck_Data_pCodingArea->Led1.FUSAConfig.FUSA_DRV01_NAMES[0];
  uint32 ulCrc32FromFuSaBlock = (uint32)((uint32)SysMonCheck_Data_pCodingArea->Led1.FUSAConfig.CRC32_0 +
    (uint32)((uint32)SysMonCheck_Data_pCodingArea->Led1.FUSAConfig.CRC32_1 << 8u) +
    (uint32)((uint32)SysMonCheck_Data_pCodingArea->Led1.FUSAConfig.CRC32_2 << 16u) +
    (uint32)((uint32)SysMonCheck_Data_pCodingArea->Led1.FUSAConfig.CRC32_3 << 24u));

  uint32  ulCrc32Calculated = Crc_CalculateCRC32P4((const uint8*)psFuSaBlockTrgetAddr, SYSMON_FUSA_DATA_LENGTH, SYSMON_INIT_CRC32_VAL);
  boolean boCrcCalculationResult = FALSE;

  // Compare Crc
  if (ulCrc32FromFuSaBlock != ulCrc32Calculated)
  {
    // CRC32 calculated over FuSa block is different than CRC32 saved in Coding Block
    boCrcCalculationResult = FALSE;
  }
  else
  {
    // CRC32 calculation is Valid
    boCrcCalculationResult = TRUE;
  }

  return boCrcCalculationResult;
}


//-----------------------------------------------------------------------------
/// \brief    SysMonCheck_Data_FuSaParamRangeCheckLB
///
/// \descr    Check the range of the FuSa coding parameters for Low Beam
///
/// \param    void
///
/// \return   boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean SysMonCheck_Data_FuSaParamRangeCheckLB(void)
{
  boolean boFuSaParamRangeCheckPassed = TRUE;
  uint8   ucDrvIdx    = 0u;

  // If FUSA_LB_FS_BEHAVIOUR_ASIL not in range [0,1]
  if (SysMonCheck_Data_FuSaParam_raw.ucFUSA_LB_FS_BEHAVIOUR_ASIL >= FUSA_FS_BEHAVIOUR_ASIL_INVALID)
  {
    // Range check failed
    boFuSaParamRangeCheckPassed = FALSE;
  }
  else
  {
    // Range check successful
  }

  // If FUSA_DRVxx_MIN_PWM_ASIL [1..200] or FUSA_DRVxx_MIN_CURRENT_ASIL [1..3000] not in range
  while ((boFuSaParamRangeCheckPassed == TRUE) && (ucDrvIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS))
  {
    if (SysMonCheck_Data_FuSaParam_raw.aucFUSA_DRVxx_NAMES_ASIL[ucDrvIdx] == (uint8)SysMonCheck_Data_eLF_LB_FuSa)
    {
      if ((SysMonCheck_Data_FuSaParam_raw.aucFUSA_DRVxx_MIN_PWM_ASIL[ucDrvIdx] == FUSA_DRVxx_MIN_PWM_ASIL_INVALID_LOW) ||
          (SysMonCheck_Data_FuSaParam_raw.aucFUSA_DRVxx_MIN_PWM_ASIL[ucDrvIdx] >= FUSA_DRVxx_MIN_PWM_ASIL_INVALID_HIGH) ||
          (SysMonCheck_Data_FuSaParam_raw.aunFUSA_DRVxx_MIN_CURRENT_ASIL[ucDrvIdx] == FUSA_DRVxx_MIN_CURRENT_ASIL_INVALID_LOW) ||
          (SysMonCheck_Data_FuSaParam_raw.aunFUSA_DRVxx_MIN_CURRENT_ASIL[ucDrvIdx] >= FUSA_DRVxx_MIN_CURRENT_ASIL_INVALID_HIGH))
      {
        // Range check failed
        boFuSaParamRangeCheckPassed = FALSE;
      }
      else
      {
        // Range check successful
      }
    }
    else
    {
      // Range check not needed for not FuSa relevant channel
    }
    //Increment Drv Index
    ucDrvIdx++;
  }

  // return TRUE if all FuSa parameters are in expected range
  return boFuSaParamRangeCheckPassed;
}


//-----------------------------------------------------------------------------
/// \brief    SysMonCheck_Data_FuSaParamRangeCheckTI
///
/// \descr    Check the range of the FuSa coding parameters for Turn Indicator
///
/// \param    void
///
/// \return   boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean SysMonCheck_Data_FuSaParamRangeCheckTI(void)
{
  boolean boFuSaParamRangeCheckPassed = TRUE;
  uint8   ucDrvIdx = 0u;

  // If FUSA_TI_FS_BEHAVIOUR_ASIL not in range [0,1]
  if (SysMonCheck_Data_FuSaParam_raw.ucFUSA_TI_FS_BEHAVIOUR_ASIL >= FUSA_FS_BEHAVIOUR_ASIL_INVALID)
  {
    // Range check failed
    boFuSaParamRangeCheckPassed = FALSE;
  }
  else
  {
    // Range check successful
  }

  // If FUSA_DRVxx_MIN_PWM_ASIL [1..200] or FUSA_DRVxx_MIN_CURRENT_ASIL [1..3000] not in range
  while ((boFuSaParamRangeCheckPassed == TRUE) && (ucDrvIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS))
  {
    
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
    if ((SysMonCheck_Data_FuSaParam_raw.aucFUSA_DRVxx_NAMES_ASIL[ucDrvIdx] == (uint8)SysMonCheck_Data_eLF_TI) ||
        (SysMonCheck_Data_FuSaParam_raw.aucFUSA_DRVxx_NAMES_ASIL[ucDrvIdx] == (uint8)SysMonCheck_Data_eLF_TI_SCRL))
#elif defined (CFG_VARIANT_ECO)
      if (SysMonCheck_Data_FuSaParam_raw.aucFUSA_DRVxx_NAMES_ASIL[ucDrvIdx] == (uint8)SysMonCheck_Data_eLF_TI)
#endif // CFG_VARIANT_FULL
    {
      if ((SysMonCheck_Data_FuSaParam_raw.aucFUSA_DRVxx_MIN_PWM_ASIL[ucDrvIdx] == FUSA_DRVxx_MIN_PWM_ASIL_INVALID_LOW) ||
          (SysMonCheck_Data_FuSaParam_raw.aucFUSA_DRVxx_MIN_PWM_ASIL[ucDrvIdx] >= FUSA_DRVxx_MIN_PWM_ASIL_INVALID_HIGH) ||
          (SysMonCheck_Data_FuSaParam_raw.aunFUSA_DRVxx_MIN_CURRENT_ASIL[ucDrvIdx] == FUSA_DRVxx_MIN_CURRENT_ASIL_INVALID_LOW) ||
          (SysMonCheck_Data_FuSaParam_raw.aunFUSA_DRVxx_MIN_CURRENT_ASIL[ucDrvIdx] >= FUSA_DRVxx_MIN_CURRENT_ASIL_INVALID_HIGH))
      {
        // Range check failed
        boFuSaParamRangeCheckPassed = FALSE;
      }
      else
      {
        // Range check successful
      }
    }
    else
    {
      // Range check not needed for not FuSa relevant channel
    }
    //Increment Drv Index
    ucDrvIdx++;
  }

  // return TRUE if all FUSI parameters are in expected range
  return boFuSaParamRangeCheckPassed;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_IsNbOfFuSaChannelsAllowed
///
/// \descr  Return FALSE if the number of coded FuSi relevant channels exceeds 6 (3 for lB, 3 for TI)
///
/// \param  -
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean SysMonCheck_Data_IsNbOfFuSaChannelsAllowed(void)
{
  uint8   ucNbOfFuSaLowBeamChannels = 0u;
  uint8   ucNbOfFuSaTurnIndChannels = 0u;
  boolean boIsNbofFuSaChannelsAllowed = TRUE;

  for (uint8 ucDrvIdx = 0u; ucDrvIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS; ucDrvIdx++)
  {
    if (SysMonCheck_Data_FuSaParam_raw.aucFUSA_DRVxx_NAMES_ASIL[ucDrvIdx] == (uint8)SysMonCheck_Data_eLF_LB_FuSa)
    {
      ucNbOfFuSaLowBeamChannels += 1u;
    }
    else
    {
      // Channel is not coded as FuSa relevant channel
    }

    
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
    if ((SysMonCheck_Data_FuSaParam_raw.aucFUSA_DRVxx_NAMES_ASIL[ucDrvIdx] == (uint8)SysMonCheck_Data_eLF_TI) ||
        (SysMonCheck_Data_FuSaParam_raw.aucFUSA_DRVxx_NAMES_ASIL[ucDrvIdx] == (uint8)SysMonCheck_Data_eLF_TI_SCRL))
#elif defined (CFG_VARIANT_ECO)
    if (SysMonCheck_Data_FuSaParam_raw.aucFUSA_DRVxx_NAMES_ASIL[ucDrvIdx] == (uint8)SysMonCheck_Data_eLF_TI)
#endif // CFG_VARIANT_FULL
    {
      ucNbOfFuSaTurnIndChannels += 1u;
    }
    else
    {
      // Channel is not coded as FuSa relevant channel
    }
  }

  if ((ucNbOfFuSaLowBeamChannels + ucNbOfFuSaTurnIndChannels) > SYSMONCHECK_DATA_MAX_LBFUSI_AND_TI_CHANNELS)
  {
    boIsNbofFuSaChannelsAllowed = FALSE;
  }
  else
  {
    // Do nothing. Number of coded FuSa relevant channel <= 6 for TI and LB
  }

  return boIsNbofFuSaChannelsAllowed;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_AreAllLedChSupportedByHw
///
/// \descr  Return FALSE if at least one LED channel is not supported by hardware
///         or if the EFT data is not valid
///
/// \param  -
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean SysMonCheck_Data_AreAllLedChSupportedByHw(void)
{
  boolean boAreAllLedChSupportedByHw = TRUE;
  uint8   ucDrvIdx = 0u;

  // Check EFT CRC failure
  if (SysMonCheck_Data_sEftData.boEftDataValid != FALSE)
  {
    while ((boAreAllLedChSupportedByHw == TRUE) && (ucDrvIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS))
    {
      if ((SysMonCheck_Data_sEftData.aucAssignedOutput[ucDrvIdx] == SYSMONCHECK_DATA_CHANNEL_NOT_SUPPORTED) &&
        (SysMonCheck_Data_FuSaParam_raw.aucFUSA_DRVxx_NAMES_ASIL[ucDrvIdx] != (uint8)SysMonCheck_Data_eLFNotUsed))
      {
        // Found a LED channel that is not supported
        boAreAllLedChSupportedByHw = FALSE;
      }
      else
      {
        // LED channel is supported by HW
      }

      // Increment Drv index
      ucDrvIdx++;
    }
  }
  else
  {
    // EFT data is not valid
    boAreAllLedChSupportedByHw = FALSE;
  }

  // Return FALSE if at least one LED channel is not supported by HW or if EFT data invalid
  return boAreAllLedChSupportedByHw;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_ComputeFuSaParam
///
/// \descr  Compute FuSa coding parameters based on measuring units
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonCheck_Data_ComputeFuSaParam(void)
{
  for (uint8 ucDrvIdx = 0u; ucDrvIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS; ucDrvIdx++)
  {
    SysMonCheck_Data_aLedChParam[ucDrvIdx].eName                = SysMonCheck_Data_GetLFName(ucDrvIdx);
    SysMonCheck_Data_aLedChParam[ucDrvIdx].unMinPwmDuty         = SysMonCheck_Data_GetMinPwmDuty(ucDrvIdx);
    SysMonCheck_Data_aLedChParam[ucDrvIdx].unMinCurrent         = SysMonCheck_Data_GetMinCurrent(ucDrvIdx);
    SysMonCheck_Data_aLedChParam[ucDrvIdx].ulLedOverVoltValue   = SysMonCheck_Data_GetLedOverVoltValue(ucDrvIdx);
    SysMonCheck_Data_aLedChParam[ucDrvIdx].ulLedUnderVoltValue  = SysMonCheck_Data_GetLedUnderVoltValue(ucDrvIdx);
  }

  SysMonCheck_Data_ulComputedFusaCrc = SysMonCheck_Data_CalcComputedFuSaParamCrc32();
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_GetLFName
///
/// \descr  Get the FUSI_LMxx_NAME_ASIL coding parameter
///
/// \param  ucLFIndex
///
/// \return SysMonCheck_Data_tLFName
//-----------------------------------------------------------------------------
STATIC_AL SysMonCheck_Data_tLFName SysMonCheck_Data_GetLFName(uint8 ucLFIndex)
{
  const SysMonCheck_Data_tLFName aeLFName[(uint8)SysMonCheck_Data_eLFNameCount] =
  {
    SysMonCheck_Data_eLFNotUsed,
    SysMonCheck_Data_eLF_LB,
    SysMonCheck_Data_eLF_LB_FuSa,
    SysMonCheck_Data_eLF_HB,
    SysMonCheck_Data_eLF_DRL_POS,
    SysMonCheck_Data_eLF_DRL_POS_SCRL,
    SysMonCheck_Data_eLF_TI,
    SysMonCheck_Data_eLF_TI_SCRL,
    SysMonCheck_Data_eLF_SM,
    SysMonCheck_Data_eLF_RGB,
    SysMonCheck_Data_eLF_FOG,
    SysMonCheck_Data_eLF_LB_BOOST,
    SysMonCheck_Data_eLF_HB_BOOST,
    SysMonCheck_Data_eLF_CL,
    SysMonCheck_Data_eLF_PXL,
    SysMonCheck_Data_eLF_MXB
  };

  uint8 ucFUSA_DRVxx_NAMES_ASIL = 0u;

  SysMonCheck_Data_tLFName eLFName = SysMonCheck_Data_eLFNotUsed;

  if (ucLFIndex < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS)
  {
    ucFUSA_DRVxx_NAMES_ASIL = SysMonCheck_Data_FuSaParam_raw.aucFUSA_DRVxx_NAMES_ASIL[ucLFIndex];
  }
  else
  {
    //Do nothing light source index not valid
  }

  //If the read coding parameter is valid
  if (ucFUSA_DRVxx_NAMES_ASIL < (uint8)SysMonCheck_Data_eLFNameCount)
  {
    eLFName = aeLFName[ucFUSA_DRVxx_NAMES_ASIL];
  }
  else
  {
    //Do nothing. Coding parameter value is invalid
  }

  return eLFName;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_GetMinPwmDuty
///
/// \descr  Get the Minimum PWM value
///
/// \param  ucLFIndex
///
/// \return uint16
//-----------------------------------------------------------------------------
STATIC_AL uint16 SysMonCheck_Data_GetMinPwmDuty(uint8 ucLFIndex)
{
  uint8 ucFUSA_DRVxx_MIN_PWM_ASIL = 0u;

  if (ucLFIndex < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS)
  {
    ucFUSA_DRVxx_MIN_PWM_ASIL = SysMonCheck_Data_FuSaParam_raw.aucFUSA_DRVxx_MIN_PWM_ASIL[ucLFIndex];
  }
  else
  {
    // nothing to do
  }

  return SYSMON_SCALE_PERCENT_TO_UINT16(SYSMONCHECK_DATA_UINT8_0_5PERCENT_TO_PERCENT(ucFUSA_DRVxx_MIN_PWM_ASIL));
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_GetMinCurrent
///
/// \descr  Get the Minimum Current value
///
/// \param  ucLFIndex
///
/// \return uint16
//-----------------------------------------------------------------------------
STATIC_AL uint16 SysMonCheck_Data_GetMinCurrent(uint8 ucLFIndex)
{
  uint16 unFUSA_DRVxx_MIN_CURRENT_ASIL = 0u;

  if (ucLFIndex < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS)
  {
    unFUSA_DRVxx_MIN_CURRENT_ASIL = SysMonCheck_Data_FuSaParam_raw.aunFUSA_DRVxx_MIN_CURRENT_ASIL[ucLFIndex];
  }
  else
  {
    // nothing to do
  }
  return (unFUSA_DRVxx_MIN_CURRENT_ASIL);
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_GetLedOverVoltValue
///
/// \descr  Get the coding paramater DRVxx_LED_OVER_VOLTAGE_ASIL and convert
///         it to uint32 type with 1mV resolution
///
/// \param  ucLFIndex
///
/// \return uint32
//-----------------------------------------------------------------------------
STATIC_AL uint32 SysMonCheck_Data_GetLedOverVoltValue(uint8 ucLFIndex)
{
  uint8 ucDRVxx_LED_OVER_VOLTAGE = 0u;

  if (ucLFIndex < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS)
  {
    ucDRVxx_LED_OVER_VOLTAGE = SysMonCheck_Data_FuSaParam_raw.aucFUSA_DRVxx_LED_OVER_VOLTAGE_ASIL[ucLFIndex];
  }
  else
  {
    // nothing to do
  }

  return SYSMONCHECK_DATA_SCALE_VOLTAGE_UINT8_UINT32(ucDRVxx_LED_OVER_VOLTAGE);
}


//-----------------------------------------------------------------------------
/// \brief SysMonCheck_Data_GetLedUnderVoltValue
///
/// \descr  Get the coding parameter DRVxx_LED_UNDER_VOLTAGE and convert it
///         to uint32 1mV resolution
///
/// \param  ucLFIndex
///
/// \return uint32
//-----------------------------------------------------------------------------
STATIC_AL uint32 SysMonCheck_Data_GetLedUnderVoltValue(uint8 ucLFIndex)
{
  uint8 ucDRVxx_LED_UNDER_VOLTAGE = 0u;

  if (ucLFIndex < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS)
  {
    ucDRVxx_LED_UNDER_VOLTAGE = SysMonCheck_Data_FuSaParam_raw.aucFUSA_DRVxx_LED_UNDER_VOLTAGE_ASIL[ucLFIndex];
  }
  else
  {
    // nothing to do
  }

  return SYSMONCHECK_DATA_SCALE_VOLTAGE_UINT8_UINT32(ucDRVxx_LED_UNDER_VOLTAGE);
}


//-----------------------------------------------------------------------------
/// \brief SysMonCheck_Data_CalcComputedFuSaParamCrc32
///
/// \descr  Calculate the CRC32 over the RAM coding mirror
///
/// \param  void
///
/// \return uint32
//-----------------------------------------------------------------------------
STATIC_AL uint32 SysMonCheck_Data_CalcComputedFuSaParamCrc32(void)
{
  // Calculate size of RAM coding mirror
  uint32 ulSizeOfParameters = sizeof(tSysMonCheck_Data_LedChParam) * SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS;

  // Get pointer to the RAM coding mirror
  tSysMonCheck_Data_LedChParam* psLedChParam = SysMonCheck_Data_GetaLEDChParamPtr();

  // Calculate CRC over RAM coding mirror
  // PRQA S 310 1 // Software Architecture , intended behaviour
  uint32  ulCrc32Calculated = Crc_CalculateCRC32P4((const uint8*)psLedChParam, ulSizeOfParameters, SYSMON_INIT_CRC32_VAL);

  return ulCrc32Calculated;
}


//-----------------------------------------------------------------------------
/// \brief SysMonCheck_Data_RamMCodingMirrorCheck
///
/// \descr  Check every 200 ms if the CRC over the RAM Coding Mirror was corrupted
///         or not, and get coding parameters again in case it is corrupted.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonCheck_Data_RamMCodingMirrorCheck(void)
{
  STATIC_UT(boolean, boCodingRamCheck, TRUE);

  // Check if 200 ms have passed
  if (boCodingRamCheck == TRUE)
  {
    // Get time stamp
    SysMonCheck_Data_ulCrcRamMirror_us = TimerGetTick();
    // Set flag to indicate that a check has already started
    boCodingRamCheck = FALSE;
  }
  else
  {
    if (TimerGetTimeSince(SysMonCheck_Data_ulCrcRamMirror_us) >= UTILTIME_MSEC(SYSMONCHECK_DATA_CRC_RAM_CHECK_MS))
    {
      // Check the new CRC of computed FuSa parameters
      if (SysMonCheck_Data_ulComputedFusaCrc != SysMonCheck_Data_CalcComputedFuSaParamCrc32())
      {
        // Copy the coding parameters of the FuSa data block into the local RAM area
        SysMonCheck_Data_ComputeFuSaParam();
        // TI shall be deactivated in case of CRC32 RAM failure and DIAG_TI and DIAG_LB shall be set to NOK
        SysMonCheck_Data_Set_Crc32RamFailure(TRUE);
      }
      else
      {
        // CRC32 RAM is used for DIAG_TI and DIAG_LB
        SysMonCheck_Data_Set_Crc32RamFailure(FALSE);
      }

      // Trigger the start of a new check every 200 ms
      boCodingRamCheck = TRUE;
    }
    else
    {
      // nothing to do because the timer has not reached it's target value
    }
  }
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_GetaLEDChParamPtr
///
/// \descr  Get the pointer of the coding parameter related to Light source channels
///
/// \param  void
///
/// \return tSysMonCheck_Data_LedChParam *
//-----------------------------------------------------------------------------
tSysMonCheck_Data_LedChParam* SysMonCheck_Data_GetaLEDChParamPtr(void)
{
  return &SysMonCheck_Data_aLedChParam[0];
}


//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  Return if the Fusa coding parameters are valid or not.
///
/// \param  -
///
/// \return boolean
//-----------------------------------------------------------------------------
tSysMonCheck_Data_FuSaParamValid SysMonCheck_Data_AreFuSaParamValid(void)
{
  return SysMonCheck_Data_eAreFuSaParamValid;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_IsCodingDataValid
///
/// \descr  Return the current validity of coding data for SySMon
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean SysMonCheck_Data_IsCodingDataValid(void)
{
  return SysMonCheck_Data_boIsCodingDataValid;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_AreFuSaParam_Invalid
///
/// \descr  Return if the FuSa coding parameters are valid or not for LB.
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean SysMonCheck_Data_AreFuSaParam_Invalid(void)
{
  return SysMonCheck_Data_boAreFuSaParam_Invalid;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_IsTurnIndicatorFuSa
///
/// \descr  Return if the channel is a Turn Indicator FuSa channel
///
/// \param  ucFuSaIdx
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean SysMonCheck_Data_IsTurnIndicatorFuSa(uint8 ucFuSaIdx)
{
  boolean boLF_TI_FuSa = FALSE;

  if (ucFuSaIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS)
  {
    
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
    if ((SysMonCheck_Data_eLF_TI == SysMonCheck_Data_aLedChParam[ucFuSaIdx].eName) ||
        (SysMonCheck_Data_eLF_TI_SCRL == SysMonCheck_Data_aLedChParam[ucFuSaIdx].eName))
#elif defined (CFG_VARIANT_ECO)
    if (SysMonCheck_Data_eLF_TI == SysMonCheck_Data_aLedChParam[ucFuSaIdx].eName)
#endif // CFG_VARIANT_FULL
    {
      boLF_TI_FuSa = TRUE;
    }
    else
    {
      // nothing to do
    }
  }
  else
  {
    boLF_TI_FuSa = FALSE;
  }

  return  boLF_TI_FuSa;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_Get_ucFUSA_LB_FS_BEHAVIOUR_ASIL
///
/// \descr  Return the Low Beam behaviour in case of FuSa LB
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 SysMonCheck_Data_Get_ucFUSA_LB_FS_BEHAVIOUR_ASIL(void)
{
  return SysMonCheck_Data_FuSaParam_raw.ucFUSA_LB_FS_BEHAVIOUR_ASIL;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_Get_ucFUSA_TI_FS_BEHAVIOUR_ASIL
///
/// \descr  Return the Turn Indicator behaviour in case of TI
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 SysMonCheck_Data_Get_ucFUSA_TI_FS_BEHAVIOUR_ASIL(void)
{
  return SysMonCheck_Data_FuSaParam_raw.ucFUSA_TI_FS_BEHAVIOUR_ASIL;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_Get_IsLowBeamEnabled
///
/// \descr  Return if Low Beam is enabled
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean SysMonCheck_Data_Get_IsLowBeamEnabled(void)
{
  return SysMonCheck_Data_IsLowBeamEnabled;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_Get_IsTurnIndEnabled
///
/// \descr  Return if Turn Indicator is enabled
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean SysMonCheck_Data_Get_IsTurnIndEnabled(void)
{
  return SysMonCheck_Data_IsTurnIndEnabled;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_CheckEFT_ECUVARCFG_LED
///
/// \descr  Read EFT data and populate a local structure
///
/// \param  pEftData
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonCheck_Data_GetEftData(tsSysMonCheck_Data_EftData * CONST_AL pEftData)
{
  uint8   ucEftDataIdx = 0u;
  boolean boEftDataValid = FALSE;

  // Check EFT Data Validity
  if (SYSMONCHECK_DATA_EftDataValid() != FALSE)
  {
    // Set EFT Data Validity to TRUE
    pEftData->boEftDataValid = TRUE;

    for (uint8 ucDev = 0u; ucDev < SYSMONCHECK_DATA_Cfg_NbOfDevices; ucDev++)
    {
      for (uint8 ucChn = 0u; ucChn < SYSMONCHECK_DATA_Cfg_NbOfChannels; ucChn++)
      {
        // Get value of Channel Assigned Output
        pEftData->aucAssignedOutput[ucEftDataIdx] = SYSMONCHECK_DATA_ECUVARCFG_ucAssignedOutput(ucDev, ucChn);

        // Get value of Channel Maximum Current
        pEftData->aunImax[ucEftDataIdx] = SYSMONCHECK_DATA_ECUVARCFG_unImax(ucDev, ucChn);

        // Increment index for Eft Data Structure
        ++ucEftDataIdx;
      }
    }
  }
  else
  {
    // Set EFT Data Validity to FALSE
    pEftData->boEftDataValid = FALSE;
  }
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_CheckEFT_ECUVARCFG_LED
///
/// \descr  Read EFT data and check if channel maximum current is smaller
///         than current intensity from Coding Data.
///         Disable TI or LB FuSa channels in case of error.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonCheck_Data_CheckEFT_ECUVARCFG_LED(void)
{
  for (uint8 ucDrvIdx = 0u; ucDrvIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS; ucDrvIdx++)
  {
    // Check if LED channel is mounted on ECU
    if (SysMonCheck_Data_sEftData.aucAssignedOutput[ucDrvIdx] != SYSMONCHECK_DATA_CHANNEL_NOT_SUPPORTED)
    {
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
      if ((SysMonCheck_Data_FuSaParam_raw.aucFUSA_DRVxx_NAMES_ASIL[ucDrvIdx] == (uint8)SysMonCheck_Data_eLF_TI) ||
          (SysMonCheck_Data_FuSaParam_raw.aucFUSA_DRVxx_NAMES_ASIL[ucDrvIdx] == (uint8)SysMonCheck_Data_eLF_TI_SCRL))
#elif defined (CFG_VARIANT_ECO)
      if (SysMonCheck_Data_FuSaParam_raw.aucFUSA_DRVxx_NAMES_ASIL[ucDrvIdx] == (uint8)SysMonCheck_Data_eLF_TI)
#endif // CFG_VARIANT_FULL
      {
        // If target current greater than allowed current in EFT
        if (SysMonCheck_Data_aLedChParam[ucDrvIdx].unMinCurrent > SysMonCheck_Data_sEftData.aunImax[ucDrvIdx])
        {
          // Limit the current to Imax configured in EFT
          // Turn Off Turn Indicator
          SysMonCheck_Data_IsTurnIndEnabled = FALSE;
        }
        else
        {
          // nothing to do
        }
      }
      else if (SysMonCheck_Data_FuSaParam_raw.aucFUSA_DRVxx_NAMES_ASIL[ucDrvIdx] == (uint8)SysMonCheck_Data_eLF_LB_FuSa)
      {
        // If target current greater than allowed current in EFT
        if (SysMonCheck_Data_aLedChParam[ucDrvIdx].unMinCurrent > SysMonCheck_Data_sEftData.aunImax[ucDrvIdx])
        {
          // Turn Off Low Beam
          SysMonCheck_Data_IsLowBeamEnabled = FALSE;
        }
        else
        {
          // nothing to do
        }
      }
      else
      {
        // nothing to do
      }
    }
    else
    {
      // nothing to do
    }
  }
} // PRQA S 5336 1 // SW Design and readability


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_Set_Crc32RamFailure
///
/// \descr  function to set the status of the CRC32 RAM check
///
/// \param  boCrc32RamFail
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonCheck_Data_Set_Crc32RamFailure(boolean boCrc32RamFail)
{
  SysMonCheck_Data_boCrc32RamFail = boCrc32RamFail;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_Get_Crc32RamFailure
///
/// \descr  function to get the status of the CRC32 RAM check
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean SysMonCheck_Data_Get_Crc32RamFailure(void)
{
  return SysMonCheck_Data_boCrc32RamFail;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_Set_Crc32RomFailure
///
/// \descr  function to set the status of the CRC32 ROM check
///
/// \param  boCrc32RomFail
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonCheck_Data_Set_Crc32RomFailure(boolean boCrc32RomFail)
{
  SysMonCheck_Data_boCrc32RomFail = boCrc32RomFail;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_Get_Crc32RomFailure
///
/// \descr  function to get the status of the CRC32 ROM check
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean SysMonCheck_Data_Get_Crc32RomFailure(void)
{
  return SysMonCheck_Data_boCrc32RomFail;
}


/// ---------------------------------------------------------------------------
/// \func     SysMonCheck_Data_GetCrc32IntegrityCheck
///
/// \brief    Return CRC32 integrity check over FuSa coding block
///
/// \param    void
///
/// \return   boolean
///
/// ---------------------------------------------------------------------------
boolean SysMonCheck_Data_GetCrc32IntegrityCheck(void)
{
  return SysMonCheck_Data_boCrc32OverCoding;
}


#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_Get_TiScrollingPresent
///
/// \descr  Function to get the status if TI Scrolling is Present
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean SysMonCheck_Data_Get_TiScrollingPresent(void)
{
  return SysMonCheck_Data_boIsTiScrollingPresent;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_IsTiScrollingPresent
///
/// \descr  Perform check if TI_SCRL is present in Coding Data
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean SysMonCheck_Data_IsTiScrollingPresent(void)
{
  boolean boIsTiScrlPresent = FALSE;

  for (uint8 ucDrvIdx = 0u; ucDrvIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS; ucDrvIdx++)
  {
    if (SysMonCheck_Data_FuSaParam_raw.aucFUSA_DRVxx_NAMES_ASIL[ucDrvIdx] == (uint8)SysMonCheck_Data_eLF_TI_SCRL)
    {
      boIsTiScrlPresent = TRUE;
    }
    else
    {
      // Channel is not coded as TI_SCRL
    }
  }

  return boIsTiScrlPresent;
}
#endif // CFG_VARIANT_FULL


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_Get_CodingDataDebounce
///
/// \descr  Function to get debounce values from coding
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
tsSysMon_Error SysMonCheck_Data_Get_CodingDataDebounce(void)
{
  return SysMonCheck_Data_sLed_Debounce;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_CheckAndSetCodingData
///
/// \descr Check Coding Validity and get coding data
///
/// \param  boIsCodingDataValid
///
/// \return uin16
//-----------------------------------------------------------------------------
uint16 SysMonCheck_Data_CheckAndSetCodingData(boolean boIsCodingDataValid)
{
  uint16 unDelayTiNotRequested = SYSMON_DELAY_TI_NOT_REQUESTED;

  // If coding data is valid
  if (boIsCodingDataValid != FALSE)
  {
    // Get DELAY_TI_NOT_REQUESTED from coding
    unDelayTiNotRequested = SysMonCheck_Data_pCodingArea->Led1.BasicFunctions.unDELAY_TI_NOT_REQUESTED;
  }
  else
  {
    // Coding is corrupted, Default value is used for DELAY_TI_NOT_REQUESTED
  }

  return unDelayTiNotRequested;
}

// EOF
