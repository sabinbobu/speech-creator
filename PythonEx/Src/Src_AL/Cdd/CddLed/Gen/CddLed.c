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
/// \file  CddLed.c
///
/// \brief Main file for LED driver
///        containing code that is independent on driver type
///
/// \descr  
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
// standard includes
#include <Std_Types.h>
#include <AL_Helper.h>

// module API (include path)
#include <CddLed.h>

// module includes (relative to API)
#include <../Cfg/CddLed_Cfg.h>
#include <../Cfg/CddLed_RoutCfg.h>
#include <../Gen/CddLed_Types.h>
#if defined (CFG_VARIANT_ECO)
#include <../Cdd/CddEft/Api/CddEft.h>
#endif

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#define CDDLED_CycleTime   20u                                                           // [us] cyclic runnable
#define CDDLED_ShortBatOffCntThresh (CDDLED_Cfg_ShortBatOffTime     / CDDLED_CycleTime)  // for ShortToVbat detection 
#define CDDLED_ThermShutdnCntThresh (CDDLED_Cfg_ThermShutdnDebounce / CDDLED_CycleTime)  // for TSD validation

// Needed because of booster voltage calculation in CddLed
#if defined (CFG_VARIANT_FULL) || defined(UNIT_TEST)
#define CDDLED_BoostVoltLimit       49000u //FULL
#else
#define CDDLED_BoostVoltLimit       ((EFT_ECUVARCFG_Ncv78702[0].ucVariant == 3u) ? 49000u : 62000u) //ECO
#endif

//-----------------------------------------------------------------------------
// Start definitions of initialized 16 bit variables
//-----------------------------------------------------------------------------
#define ctadCddLed_START_SEC_VAR_INIT_16
#include <../Cfg/CddLed_MemMap.h>

STATIC_AL uint16 CddLed_unInputVoltThreshold = 0u;  // minimum input voltage

#define ctadCddLed_STOP_SEC_VAR_INIT_16
#include <../Cfg/CddLed_MemMap.h>
//-----------------------------------------------------------------------------
// End definitions of initialized 16 bit variables
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Start definitions of initialized 32 bit variables
//-----------------------------------------------------------------------------
#define ctadCddLed_START_SEC_VAR_INIT_32
#include <../Cfg/CddLed_MemMap.h>

STATIC_AL uint32 CddLed_ulAvailMask     = 0u;  // mask indicating availability of channels
STATIC_AL uint32 CddLed_ulShortUbatMask = 0u;  // mask indicating active ShortToUbat measurement
STATIC_AL uint32 CddLed_ulOnMask        = 0u;  // mask indicating ON/OFF state

#define ctadCddLed_STOP_SEC_VAR_INIT_32
#include <../Cfg/CddLed_MemMap.h>
//-----------------------------------------------------------------------------
// End definitions of initialized 32 bit variables
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Start definitions of non initialized structures and unions or arrays variables
//-----------------------------------------------------------------------------
#define ctadCddLed_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <../Cfg/CddLed_MemMap.h>

STATIC_AL tCddLedTarget         CddLed_sTarget;                     // current and duty for LEDs
STATIC_AL tCddLedDriverSettings CddLed_Settings;                    // conditions needed for proper driver operation
STATIC_AL boolean CddLed_aboThermShutDn [CDDLED_Cfg_NbOfChannels];  // state of thermal shutdown fault
STATIC_AL boolean CddLed_aboOverCurrent [CDDLED_Cfg_NbOfChannels];  // state of overcurrent fault
STATIC_AL uint8   CddLed_aucThermShutDn [CDDLED_Cfg_NbOfChannels];  // debounce counter for thermal shutdown fault
STATIC_AL uint8   CddLed_aucOverCurrent [CDDLED_Cfg_NbOfChannels];  // debounce counter for overcurrent fault
STATIC_AL uint8   CddLed_aucOffCounter  [CDDLED_Cfg_NbOfChannels];  // counter to use for measurement delay in ShotToUbat
STATIC_AL uint16  CddLed_aunInputVoltage[CDDLED_Cfg_NbOfChannels];  // buck input voltages
STATIC_AL uint16  CddLed_aunLedVoltage  [CDDLED_Cfg_NbOfChannels];  // actual LED voltage
STATIC_AL uint16  CddLed_aunErrorList   [CDDLED_Cfg_NbOfChannels];  // list of error details

#define ctadCddLed_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <../Cfg/CddLed_MemMap.h>
//-----------------------------------------------------------------------------
// End definitions of non initialized structures and unions or arrays variables
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Start definitions of initialized structures and unions or arrays variables
//-----------------------------------------------------------------------------
#define ctadCddLed_START_SEC_VAR_INIT_UNSPECIFIED
#include <../Cfg/CddLed_MemMap.h>

#ifdef CDDLED_Cfg_Simulation
STATIC_AL volatile tCddLed_Simulation_Data CddLed_Simulation_Data = { .ulSimActivated = CDDLED_SimulationDeactivated };
#endif

#define ctadCddLed_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <../Cfg/CddLed_MemMap.h>
//-----------------------------------------------------------------------------
// End definitions of initialized structures and unions or arrays variables
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Start declaration or definitions of functions
//-----------------------------------------------------------------------------
#define ctadCddLed_START_SEC_CODE
#include <../Cfg/CddLed_MemMap.h>

STATIC_AL void    CddLed_EvaluateElectricalErrors(const uint32 ul);
STATIC_AL void    CddLed_EvaluateInternalErrors  (const uint32 ul);
STATIC_AL void    CddLed_EvaluateLedVoltage      (const uint32 ul);
STATIC_AL void    CddLed_EvaluateAuxVoltages     (const uint32 ul);
STATIC_AL void    CddLed_CreateErrStatus         (const uint32 ul, tCddLedStatus* const pStatus);
STATIC_AL void    CddLed_CreateChnStatus         (const uint32 ul, tCddLedStatus* const pStatus);
STATIC_AL void    CddLed_CreateAuxStatus         (const uint32 ul, tCddLedStatus* const pStatus);
STATIC_AL boolean CddLed_DebounceOvercurrent     (const uint32 ul, boolean boState);
STATIC_AL boolean CddLed_DebounceThermShutDn     (const uint32 ul, boolean boState);


//-----------------------------------------------------------------------------
/// \brief  Internal debouncing of thermal shutdown fault
///
/// \descr  This is an internal fault, so debouncing can be done locally
///
/// \param  ul
/// \param  boState
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CddLed_DebounceThermShutDn(const uint32 ul, boolean boState)
{
  if ((boState != FALSE) && (CddLed_aucThermShutDn[ul] < CDDLED_ThermShutdnCntThresh))
  {
    CddLed_aucThermShutDn[ul]++;
  }
  else if ((boState == FALSE) && (CddLed_aucThermShutDn[ul] > 0u))
  {
    CddLed_aucThermShutDn[ul]--;
  }
  else
  {
    // nothing to do
  }

  if (CddLed_aucThermShutDn[ul] >= CDDLED_ThermShutdnCntThresh)
  {
    CddLed_aboThermShutDn[ul] = TRUE;
  }

  return CddLed_aboThermShutDn[ul];
}


//-----------------------------------------------------------------------------
/// \brief  Internal debouncing of overcurrent fault
///
/// \descr  This is an internal fault, so debouncing can be done locally
///
/// \param  ul
/// \param  boState
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CddLed_DebounceOvercurrent(const uint32 ul, boolean boState)
{
  if ((boState != FALSE) && (CddLed_aucOverCurrent[ul] < CDDLED_Para_LED_OVERCURRENT_DEBOUNCE))
  {
    CddLed_aucOverCurrent[ul]++;
  }
  else if ((boState == FALSE) && (CddLed_aucOverCurrent[ul] > 0u))
  {
    CddLed_aucOverCurrent[ul]--;
  }
  else
  {
    // nothing to do
  }

  if (CddLed_aucOverCurrent[ul] >= CDDLED_Para_LED_OVERCURRENT_DEBOUNCE)
  {
    CddLed_aboOverCurrent[ul] = TRUE;
  }

  return CddLed_aboOverCurrent[ul];
}


//-----------------------------------------------------------------------------
/// \brief  EvaluateElectricalErrors
///
/// \descr  Clear error list entry
///         Add availability from EFT data
///         Check driver for electrical error information
///
/// \param  uint32 ul
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddLed_EvaluateElectricalErrors(const uint32 ul)
{
  uint32  ulIdxMask      = CDDLED_Mask_32(ul);             // mask for bitwise access of channel number

  boolean boDriverActive = CDDLED_Drv_IsDriverActive(ul);  //
  boolean boShortToGnd   = CDDLED_Drv_IsShortToGnd  (ul);  // call driver interface functions
  boolean boOpenLoad     = CDDLED_Drv_IsOpenLoad    (ul);  //

  CddLed_aunErrorList[ul] = 0u;  // delete list before filling

  if ((CddLed_ulAvailMask & CDDLED_Mask_32(ul)) == 0u)  // not available on HW
  {
    CddLed_aunErrorList[ul] |= CDDLED_Mask_16(CDDLED_NoSupport);
  }

  if ((CddLed_ulShortUbatMask & ulIdxMask) != 0u)  // short to Ubat condition checked separately
  {
    CddLed_aunErrorList[ul] |= CDDLED_Mask_16(CDDLED_ShortToUbat);
  }

  if (boDriverActive == FALSE)                     // driver not in current regulation mode
  {
    CddLed_aunErrorList[ul] |= CDDLED_Mask_16(CDDLED_DriverInactive);
  }

  if ((boShortToGnd != FALSE) && ((CddLed_Settings.ulDisableErrShortToGnd & ulIdxMask) == 0u))    // enabled and error occurred
  {
    CddLed_aunErrorList[ul] |= CDDLED_Mask_16(CDDLED_ShortToGnd);
  }

  if ((boOpenLoad != FALSE) && ((CddLed_Settings.ulDisableErrOpenLoad & ulIdxMask) == 0u))        // enabled and error occurred
  {
    CddLed_aunErrorList[ul] |= CDDLED_Mask_16(CDDLED_OpenLoad);
  }
}


//-----------------------------------------------------------------------------
/// \brief  EvaluateInternalErrors
///
/// \descr  Check driver for internal error information
///         Allow simulation of errors
///
/// \param  uint32 ul
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddLed_EvaluateInternalErrors(const uint32 ul)
{
  uint32 ulIdxMask = CDDLED_Mask_32(ul);                      // mask for bitwise access of channel number

  boolean boThermWarning = CDDLED_Drv_IsThermalWarning (ul);  // call driver interface functions
  boolean boThermShutDn  = CDDLED_Drv_IsThermalShutDown(ul);  //
  boolean boOverCurrent  = CDDLED_Drv_IsOvercurrent    (ul);  //

  boThermShutDn = CddLed_DebounceThermShutDn(ul, boThermShutDn);    // internal debouncing
  boOverCurrent = CddLed_DebounceOvercurrent(ul, boOverCurrent);

  if (boThermWarning != FALSE)                                                                    // theral warning occurred
  {
    CddLed_aunErrorList[ul] |= CDDLED_Mask_16(CDDLED_ThermWarning);
  }

  if ((boThermShutDn != FALSE) && ((CddLed_Settings.ulDisableErrThermalShutdown & ulIdxMask) == 0u))  // enabled and error occurred
  {
    CddLed_aunErrorList[ul] |= CDDLED_Mask_16(CDDLED_ThermShutdn);
  }

  if ((boOverCurrent != FALSE) && ((CddLed_Settings.ulDisableErrOverCurrent & ulIdxMask) == 0u))  // enabled and error occurred
  {
    CddLed_aunErrorList[ul] |= CDDLED_Mask_16(CDDLED_OverCurrent);
  }

#ifdef CDDLED_Cfg_Simulation
  if (CddLed_Simulation_Data.ulSimActivated == CDDLED_SimulationPassword)
  {
    if ((CddLed_Simulation_Data.ulSimThermalWarning & CDDLED_Mask_32(ul)) != 0u)  // check for bit indication error simulation
    {
      CddLed_aunErrorList[ul] |= CDDLED_Mask_16(CDDLED_ThermWarning);
    }

    if ((CddLed_Simulation_Data.ulSimThermalShutdown & CDDLED_Mask_32(ul)) != 0u)  // check for bit indication error simulation
    {
      CddLed_aunErrorList[ul] |= CDDLED_Mask_16(CDDLED_ThermShutdn);
    }

    if ((CddLed_Simulation_Data.ulSimOverCurrent & CDDLED_Mask_32(ul)) != 0u)  // check for bit indication error simulation
    {
      CddLed_aunErrorList[ul] |= CDDLED_Mask_16(CDDLED_OverCurrent);
    }
  }
#endif
}


//-----------------------------------------------------------------------------
/// \brief  Evaluate information based on LED voltage
///
/// \descr  Read LED voltage and compare to thresholds
///         Allow simulation of errors
///
/// \param  uint32 ul
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddLed_EvaluateLedVoltage(const uint32 ul)
{
  uint16 unLedVoltage;
  uint16 unUnderVoltageThreshold = (uint16)CDDLED_Para_FUSA_DRV_LED_UNDER_VOLTAGE(ul);
  uint16 unOverVoltageThreshold  = (uint16)CDDLED_Para_FUSA_DRV_LED_OVER_VOLTAGE (ul);
  uint16 unOffVoltageThreshold   = CDDLED_Cfg_OffVoltThresh;

  boolean boValid = CDDLED_Drv_GetLedVoltage_mV(ul, &unLedVoltage);  // get actual LED voltage

  if (boValid == FALSE)  // no voltage available
  {
    CddLed_aunLedVoltage[ul] = 0u;  // obsolete for ShortToUbat check
  }
  else
  {
    CddLed_aunLedVoltage[ul] = unLedVoltage;  // neened for ShortToUbat check

    if (unLedVoltage >= unOffVoltageThreshold)  // voltage not in OFF state
    {
      CddLed_aunErrorList[ul] |= CDDLED_Mask_16(CDDLED_NotOffVoltage);
    }

    if ((CddLed_Settings.ulDisableErrUnderVoltage & CDDLED_Mask_32(ul)) == 0u)
    {
      if (unLedVoltage < unUnderVoltageThreshold)  // voltage below expected value
      {
        CddLed_aunErrorList[ul] |= CDDLED_Mask_16(CDDLED_UnderVoltage);
      }
    }

    if ((CddLed_Settings.ulDisableErrOverVoltage & CDDLED_Mask_32(ul)) == 0u)
    {
      if (unLedVoltage > unOverVoltageThreshold)  // voltage above expected value
      {
        CddLed_aunErrorList[ul] |= CDDLED_Mask_16(CDDLED_OverVoltage);
      }
    }
  }
}


//-----------------------------------------------------------------------------
/// \brief  Evaluate information based on other voltage values
///
/// \descr  Read LED ON/OFF voltage and input voltage and compare to thresholds
///
/// \param  uint32 ul
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddLed_EvaluateAuxVoltages(const uint32 ul)
{
  CddLed_aunInputVoltage[ul] = CDDLED_Drv_GetInputVoltage_mV(ul);  // get input voltage and store value

#ifdef CDDLED_Cfg_Simulation
  if (CddLed_Simulation_Data.ulSimActivated == CDDLED_SimulationPassword)
  {
    if (CddLed_Simulation_Data.aunSimVBoostMeas[ul] != 0U) //don't used the replacement if it is invalid
    {
      CddLed_aunInputVoltage[ul] = CddLed_Simulation_Data.aunSimVBoostMeas[ul];  // overwrite by simulation data
    }
  }
#endif 
 
  if (CddLed_aunInputVoltage[ul] < CddLed_unInputVoltThreshold)     // low buck input voltage
  {
    CddLed_aunErrorList[ul] |= CDDLED_Mask_16(CDDLED_InputVoltLow);
  }
}


//-----------------------------------------------------------------------------
/// \brief  Create error status info
///
/// \descr  Determine error status based on ErrorList array
///
/// \param  uint32         ul      - channel index
///         tCddLedStatus* pStatus - pointer to status
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddLed_CreateErrStatus(const uint32 ul, tCddLedStatus* const pStatus)
{
  if ((CddLed_aunErrorList[ul] & CDDLED_Mask_16(CDDLED_NoSupport)) != 0u)  // this result is independent of target value
  {
    pStatus->aStatus[ul].Err = eCddLed_NoSupport;
  }
  else if (CDDLED_Drv_IsSpiError(ul) == TRUE)
  {
    pStatus->aStatus[ul].Err = eCddLed_ErrSpi;
  }
  else if ((CddLed_aunErrorList[ul] & CDDLED_Mask_16(CDDLED_ShortToUbat)) != 0u)  // this result may be true only if target != 0
  {
    pStatus->aStatus[ul].Err = eCddLed_ErrShortToUbat;
  }
  else if (CddLed_sTarget.aTarget[ul].unDutyCycle_1_32768 == 0u)
  {
    pStatus->aStatus[ul].Err = eCddLed_Disabled;
  }
  else  // check for errors to be evaluated at ON state
  {
    tCddLedErrStatus aStateList[1u + CDDLED_ErrListStop - CDDLED_ErrListStart] = CDDLED_InitErrList;  // list of all errors to be evaluated in ON state

    pStatus->aStatus[ul].Err = eCddLed_StatusOk;  // set to error free if no error is found

    for (uint32 ulBitPos = CDDLED_ErrListStart; ulBitPos <= CDDLED_ErrListStop; ulBitPos++)
    {
      if ((CddLed_aunErrorList[ul] & CDDLED_Mask_16(ulBitPos)) != 0u)
      {
        pStatus->aStatus[ul].Err = aStateList[ulBitPos];  // break if error with
        break;                                            // highest priority found
      }
    }
  }

  // PRQA S 5336 1 // STMIF>4 because of "else if" list
}


//-----------------------------------------------------------------------------
/// \brief  Create channel status info
///
/// \descr  Determine channel status based on ErrorList array
///
/// \param  uint32         ul      - channel index
///         tCddLedStatus* pStatus - pointer to status
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddLed_CreateChnStatus(const uint32 ul, tCddLedStatus* const pStatus)
{
  uint16 unActDuty = CDDLED_Drv_GetDutyCycle_1_32768(ul);

  if ( ( CddLed_sTarget.aTarget[ul].unDutyCycle_1_32768                  == 0u)   // Mandatory -> requested duty cycle = 0
    && ((CddLed_aunErrorList[ul] & CDDLED_Mask_16(CDDLED_NotOffVoltage)) == 0u)   // OffCond1  -> measured voltage below threshold
    && ( unActDuty                                                       == 0u) ) // OffCond2  -> confirmation from PWM generator
  {
    pStatus->aStatus[ul].Chn = eCddLed_ChnOff;
  }
  else if ( ((CddLed_aunErrorList  [ul] & CDDLED_Mask_16(CDDLED_UnderVoltage  )) == 0u)   // OnCond1 -> measured voltage above min threshold
         && ((CddLed_aunErrorList  [ul] & CDDLED_Mask_16(CDDLED_DriverInactive)) == 0u)   // OnCond3 -> current control status
         && ((CddLed_aunErrorList  [ul] & CDDLED_Mask_16(CDDLED_InputVoltLow  )) == 0u)   // OnCond5 -> booster status
         && (pStatus->aStatus      [ul].Err                 == eCddLed_StatusOk       )   // OnCond4 -> StatusOk includes overcurrent check
         && (CddLed_sTarget.aTarget[ul].unDutyCycle_1_32768 == unActDuty              ) ) // OnCond6 -> confirmation from PWM generator
  {
    pStatus->aStatus[ul].Chn = eCddLed_ChnOn;
  }
  else
  {
    pStatus->aStatus[ul].Chn = eCddLed_ChnUndef;
  }

}


//-----------------------------------------------------------------------------
/// \brief  Create aux. status info
///
/// \descr  Determine other components of status
///
/// \param  uint32         ul      - channel index
///         tCddLedStatus* pStatus - pointer to status
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CddLed_CreateAuxStatus(const uint32 ul, tCddLedStatus* const pStatus)
{
  if ((CddLed_aunErrorList[ul] & CDDLED_Mask_16(CDDLED_NoSupport)) != 0u)  // not available on HW
  {
    pStatus->aStatus[ul].unVLed                    = 0u;
    pStatus->aStatus[ul].TempData.boThermalWarning = FALSE;
    pStatus->aStatus[ul].Vin                       = eCddLed_VinUndef;
  }
  else
  {
    pStatus->aStatus[ul].unVLed  = CddLed_aunLedVoltage[ul];

    if ((CddLed_aunErrorList[ul] & CDDLED_Mask_16(CDDLED_ThermWarning)) != 0u)
    {
      pStatus->aStatus[ul].TempData.boThermalWarning = TRUE;
    }
    else
    {
      pStatus->aStatus[ul].TempData.boThermalWarning = FALSE;
    }

    if ((CddLed_aunErrorList[ul] & CDDLED_Mask_16(CDDLED_InputVoltLow)) != 0u)
    {
      pStatus->aStatus[ul].Vin = eCddLed_VinLo;
    }
    else
    {
      pStatus->aStatus[ul].Vin = eCddLed_VinOk;
    }    
  }
}


//-----------------------------------------------------------------------------
/// \brief
///
/// \descr  preliminary implementation
///
/// \param  -
///
/// \return tCddLedStatus* pointer to status of all channels
//-----------------------------------------------------------------------------
void CddLed_GetStatus(tCddLedStatus* pStatus)
{
  for (uint32 ul = 0u; ul < CDDLED_Cfg_NbOfChannels; ul++)
  {
    CddLed_EvaluateElectricalErrors(ul);  // evaluate "classical" error types
    CddLed_EvaluateInternalErrors  (ul);  // evaluate and add internal errors
    CddLed_EvaluateLedVoltage      (ul);  // evaluate and add conditions based on LED voltage
    CddLed_EvaluateAuxVoltages     (ul);  // evaluate and add conditions based on other voltages

    CddLed_CreateErrStatus(ul, pStatus);  // build status struct
    CddLed_CreateChnStatus(ul, pStatus);  // build status struct
    CddLed_CreateAuxStatus(ul, pStatus);  // build status struct
  }
}


//-----------------------------------------------------------------------------
/// \brief  Initialization
///
/// \descr  Initialize driver and get availability of drivers
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddLed_Init(void)
{
  CddLed_ulAvailMask = CDDLED_Drv_Init();  // initialize and check which channels are available
}


//-----------------------------------------------------------------------------
/// \brief  Function to update driver settings
///
/// \descr  Store settings for use in diagnostics
///
/// \param  tCddLedDriverSettings* pSettings
///
/// \return void
//-----------------------------------------------------------------------------
void CddLed_DriverSettings(tCddLedDriverSettings* pSettings)
{
  CddLed_Settings = *pSettings;
}


//-----------------------------------------------------------------------------
/// \brief  Function to update target values
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddLed_SetTarget(tCddLedTarget* pTarget)
{
  CddLed_sTarget = *pTarget;

  for (uint32 ul = 0u; ul < CDDLED_Cfg_NbOfChannels; ul++)
  {
    uint32 ulIdxMask    = CDDLED_Mask_32(ul);  // create masks according to actual index
    uint32 ulIdxMaskInv = ~ulIdxMask;          // create inverted mask

    if ((CddLed_ulAvailMask & ulIdxMask) != 0u)  // if channel is available on HW
    {
      if (CddLed_sTarget.aTarget[ul].unDutyCycle_1_32768 != 0u)    // ON requested
      {
        if ((CddLed_ulOnMask & ulIdxMask) == 0u)  // if the LED is OFF
        {
          uint32 ulSupplyVoltage_mV;
          uint32 ulSupplyVoltage_10uV_Lo;  // calculate based on 10us resolution to avoid division
          uint32 ulSupplyVoltage_10uV_Hi;
          uint32 ulLedVoltage_10uV = 100u * (uint32)CddLed_aunLedVoltage[ul];

          CddLed_aboThermShutDn [ul] = FALSE;  // reset internal error
          CddLed_aboOverCurrent [ul] = FALSE;
          CddLed_aucThermShutDn [ul] = 0u;
          CddLed_aucOverCurrent [ul] = 0u;

          (void)CDDLED_GetECUSupply(&ulSupplyVoltage_mV);

          ulSupplyVoltage_10uV_Lo = ulSupplyVoltage_mV * (100u - (uint32)CDDLED_Para_LED_SHORT_UBAT_RANGE);
          ulSupplyVoltage_10uV_Hi = ulSupplyVoltage_mV * (100u + (uint32)CDDLED_Para_LED_SHORT_UBAT_RANGE);

          if ( ((CddLed_Settings.ulDisableErrShortToUbat & ulIdxMask) == 0u)    // do not check if disabled
            && ( CddLed_aucOffCounter[ul]  ==  CDDLED_ShortBatOffCntThresh )    // do not check if OFF time too short
            && ( ulLedVoltage_10uV          >  ulSupplyVoltage_10uV_Lo     )
            && ( ulLedVoltage_10uV          <  ulSupplyVoltage_10uV_Hi     ) )  // LED voltage in range Ubat +-10% (parameter)
          {
            CddLed_ulShortUbatMask |= ulIdxMask;                  // store for usage in status 
            CddLed_sTarget.aTarget[ul].unDutyCycle_1_32768 = 0u;  // do not allow to switch on
          }
          else  // switch on allowed
          {
            CddLed_ulShortUbatMask &= ulIdxMaskInv; 
            CddLed_ulOnMask        |= ulIdxMask;
          }
        }
        else  // already ON
        {
          CddLed_aucOffCounter[ul] = 0u;  // reset to initiate delay after switching OFF
        }
      }
      else  // no request
      {
        CddLed_ulOnMask        &= ulIdxMaskInv;
        CddLed_ulShortUbatMask &= ulIdxMaskInv;
      }

      if ( (CddLed_aboThermShutDn [ul] == FALSE)    // no internal error
        && (CddLed_aboOverCurrent [ul] == FALSE) )  // 
      {
        CDDLED_Drv_SetDutyCycle(ul, CddLed_sTarget.aTarget[ul].unDutyCycle_1_32768);
      }
      else
      {
        CDDLED_Drv_SetDutyCycle(ul, 0u);
      }

      CDDLED_Drv_SetCurrent  (ul, CddLed_sTarget.aTarget[ul].unCurrent_mA);
    }
  }

  // PRQA S 5336 1 // STMIF>4 but clearly structured
}


//-----------------------------------------------------------------------------
/// \brief  Function to set parameters
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddLed_SetPara(boolean boValid)
{
  if (boValid != FALSE)
  {
    uint32 ulTargetVolt = 0u;

    for (uint32 ul = 0u; ul < CDDLED_Cfg_NbOfChannels; ul++)
    {
      uint32 ulVoltChn = CDDLED_Para_FUSA_DRV_LED_OVER_VOLTAGE(ul);

      if (ulTargetVolt < ulVoltChn)
      {
        ulTargetVolt = ulVoltChn;
      }
    }

    ulTargetVolt = ulTargetVolt + CDDLED_Para_BOOST_VOLT_HEADROOM;                                  // ulTargetVolt is now the target booster voltage

    if (ulTargetVolt > CDDLED_BoostVoltLimit)                                                       // use same limitation as in booster code
    {
      ulTargetVolt = CDDLED_BoostVoltLimit;
    }

    CddLed_unInputVoltThreshold = (uint16)(ulTargetVolt - CDDLED_Para_BOOST_VOLT_ERROR_THRESHOLD);  // CddLed_unInputVoltThreshold is the threshold for booster error detection
  }
}


//-----------------------------------------------------------------------------
/// \brief  Cyclic function which execute requested action every 20ms
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddLed_Cycle20ms(void)
{
  CDDLED_Drv_Cycle20ms();

  for (uint32 ul = 0u; ul < CDDLED_Cfg_NbOfChannels; ul++)
  {
    if (CddLed_aucOffCounter[ul] < CDDLED_ShortBatOffCntThresh)
    {
      CddLed_aucOffCounter[ul]++;
    }
  }
}

#define ctadCddLed_STOP_SEC_CODE
#include <../Cfg/CddLed_MemMap.h>
//-----------------------------------------------------------------------------
// End declaration or definitions of functions
//-----------------------------------------------------------------------------

