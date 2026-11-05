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
/// \file   SysMonCheck_LedDiag.c
///
/// \brief  
///
/// \descr  Cyclic Runnables for SysMonCheck_LedDiag
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <SysMon_Types.h>
#include <SysMonCheck_Rte.h>
#include <SysMonCheck_LedDiag.h>
#include <SysMonCheck_Data.h>
#include "SysMonCheck.h"

//-----------------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Static variable declarations
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Function prototypes
//-----------------------------------------------------------------------------
STATIC_AL uint8 SysMoncheck_LedDiag_ErrorHandler(uint8_fast ucCh, uint8 ucChStatus);
STATIC_AL uint8 SysMonCheck_LedDiag_ErrorDebounce(uint8_fast ucChId, uint8 ucErrStatus);
STATIC_AL boolean SysMonCheck_LedDiag_RetainErrorReaction(uint8_fast ucChannelIdx, tSysMon_FuSaChannelsStatusReaction sFuSaChannelsStatusReaction);

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------

STATIC_AL tsSysMon_ErrorHandler SysMonCheck_LedDiag_asErrorHandler[SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS] = { 0u };
STATIC_AL tsSysMon_Error        SysMonCheck_LedDiag_sLed_Debounce;
//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_LedDiag_Init
///
/// \descr  Init function for diagnostic check of LEDs
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonCheck_LedDiag_Init(void)
{
 
  for (uint8 ucChIdx = 0u; ucChIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS; ucChIdx++)
  {
    // Reset errors
    SysMonCheck_LedDiag_asErrorHandler[ucChIdx].ucLedState = SYSMON_DIAG_STATUS_ERR_OK;
    // Reset debounce timers
    SysMonCheck_LedDiag_sLed_Debounce.ucLed_Debounce[ucChIdx] = 0u;
  }

}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_LedDiag_Cycle
///
/// \descr  Cyclic function for diagnostic check of LEDs
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonCheck_LedDiag_Cycle(void)
{
	STATIC_UT(boolean, boGetDebounceCoding, TRUE);
  tSysMon_FuSaChannelsStatusReaction sFuSaChannelsStatusReaction;
  uint8_fast ucChannel = 0u;
  tsSysMon_aChannelState sChannelState;
  if (boGetDebounceCoding != FALSE)
  {
    SysMonCheck_LedDiag_sLed_Debounce = SysMonCheck_Data_Get_CodingDataDebounce();
    // Clear flag
    boGetDebounceCoding = FALSE;
  }
  else
  {
    // nothing to do
  }

  sFuSaChannelsStatusReaction = SysMonCheck_Get_LbTiFuSa_OffStatus();

  for (uint8_fast ucChannelIdx = 0u; ucChannelIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS; ucChannelIdx++)
  {
    SYSMONCHECK_RTE_RE_GET_LED_STATES(ucChannelIdx, &sChannelState)
    //error handler
    SysMonCheck_LedDiag_asErrorHandler[ucChannelIdx].ucLedState   = (SysMonCheck_LedDiag_RetainErrorReaction(ucChannelIdx, sFuSaChannelsStatusReaction) != FALSE) ?
                                                                                                                  SysMonCheck_LedDiag_asErrorHandler[ucChannelIdx].ucLedState :
                                                                                                                  SysMoncheck_LedDiag_ErrorHandler(ucChannelIdx, sChannelState.asChannelState[ucChannelIdx].ucChannelStatus);
   
    SysMonCheck_LedDiag_asErrorHandler[ucChannelIdx].boVinBoostOk = sChannelState.asChannelState[ucChannelIdx].boVinOk;
  }
  // Write information to CtrlLed
  SYSMONCHECK_RTE_RE_SET_LED_STATES(SysMonCheck_LedDiag_asErrorHandler)
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_LedDiag_RetainErrorReaction
///
/// \descr  Function to retain the last error reaction in case of LB FuSa or TI channel
///
/// \param  ucChannelIdx:                   - Channel Index
///         sFuSaChannelsStatusReaction:    - Structure containing LB and TI reaction status
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean SysMonCheck_LedDiag_RetainErrorReaction(uint8_fast ucChannelIdx, tSysMon_FuSaChannelsStatusReaction sFuSaChannelsStatusReaction)
{
  boolean boRet = FALSE;

  if ((sFuSaChannelsStatusReaction.boLb_FuSa_Idx[ucChannelIdx] == TRUE) ||
    (sFuSaChannelsStatusReaction.boTi_FuSa_Idx[ucChannelIdx] == TRUE))
  {
    boRet = TRUE;
  }
  else
  {
    //nothing to do
  }

  return boRet;
}


//-----------------------------------------------------------------------------
/// \brief  SysMoncheck_LedDiag_ErrorHandler
///
/// \descr  Cyclic function for diagnostic check of LEDs
///
/// \param  
///
/// \return uint8
//-----------------------------------------------------------------------------
STATIC_AL uint8 SysMoncheck_LedDiag_ErrorHandler(uint8_fast ucCh, uint8 ucChStatus)
{
  
  uint8  ucSysMon_ErrStatus = 0u;

  //check each error
  ucSysMon_ErrStatus = SysMonCheck_LedDiag_ErrorDebounce(ucCh, ucChStatus);

  return ucSysMon_ErrStatus;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_LedDiag_ErrorDebounce
///
/// \descr  Perform debounce on errors coming from CddLed
///
/// \param  ucChId, ucErrStatus
///
/// \return uint8
//-----------------------------------------------------------------------------
STATIC_AL uint8 SysMonCheck_LedDiag_ErrorDebounce(uint8_fast ucChId, uint8 ucErrStatus)
{
  STATIC_UT(tsSysMon_Diag_ErrHandler , asErrorHandler[SYSMON_CFG_MAX_BUCK_DRV] , { 0u });
  STATIC_UT(TIMER                    , ulCycleTimer[SYSMON_CFG_MAX_BUCK_DRV]   , { 0u });
  STATIC_UT(TIMER                    , ulGeneralTimer[SYSMON_CFG_MAX_BUCK_DRV] , { 0u });
            teSysMon_DebounceState     eDebounceState                          =    eCheckError;
            TIMER                      ulErrDebounceTime                       =    0u, ulErrorDebounced = 0u;
            boolean                    boErrorSetStatus                        =    FALSE;
            uint8                      ucErrStatus_Ret                         =    (ucErrStatus > SYSMON_DIAG_STATUS_LED_OFF) ? SYSMON_DIAG_STATUS_ERR_OK : SYSMON_DIAG_STATUS_LED_OFF;

  //get cycle count value 
  ulCycleTimer[ucChId] = (TimerGetTimeSince(ulGeneralTimer[ucChId]) / SYSMON_MS_CONVERTION);
  ulGeneralTimer[ucChId] = TimerGetTick();

  //this for handle the debounce time and error write status for each error occured
  for (uint8_fast ucErrId = 0u; ucErrId < SYSMON_DIAG_MAX_ERR_ARRAY; ucErrId++)
  {
    ulErrorDebounced = asErrorHandler[ucChId].asErrorState[ucErrId].ErrorDebounce;
    boErrorSetStatus = asErrorHandler[ucChId].asErrorState[ucErrId].boErrorWriteStatus;

    if ((ucErrStatus >= SYSMON_DIAG_START_ERR_CNT) && (ucErrId == (uint8)(ucErrStatus - SYSMON_DIAG_START_ERR_CNT)))
    {
      //selection of debounce time
      ulErrDebounceTime = ((ucErrStatus == SYSMON_DIAG_ERR_THERM_SHUT_DOWN) || (ucErrStatus == SYSMON_DIAG_ERR_OVER_CURRENT)) ? 20u : (ucErrStatus == SYSMON_DIAG_ERR_BOOST) ? 1000U : SysMonCheck_LedDiag_sLed_Debounce.ucLed_Debounce[ucChId];
      eDebounceState = ((ulErrorDebounced >= ulErrDebounceTime) && (boErrorSetStatus != FALSE)) ? eCheckError : \
        (ulErrorDebounced >= ulErrDebounceTime) ? eWriteError : eDoDebounce;
      //in case of error debounce has been set, reset the flag and go to error write state
      if (eDebounceState == eWriteError)
      {
        asErrorHandler[ucChId].asErrorState[ucErrId].boErrorWriteStatus = TRUE;
      }
    }
    else
    {
      eDebounceState = (ulErrorDebounced > 0u) ? eResetError : eCheckError;
    }

    //debounce states
    switch (eDebounceState)
    {
    case eDoDebounce:
      asErrorHandler[ucChId].asErrorState[ucErrId].ErrorDebounce += ulCycleTimer[ucChId];
      break;
    case eResetError:
      //cast to sint16 to avoid roll over of ErrorDebounce
      asErrorHandler[ucChId].asErrorState[ucErrId].ErrorDebounce = ((sint32)((sint32)asErrorHandler[ucChId].asErrorState[ucErrId].ErrorDebounce - (sint32)ulCycleTimer[ucChId]) <= 0)
                                                                 ? 0u : asErrorHandler[ucChId].asErrorState[ucErrId].ErrorDebounce - ulCycleTimer[ucChId];
      //check if error has been reset
      if (asErrorHandler[ucChId].asErrorState[ucErrId].ErrorDebounce == 0u)
      {
        //if error debounce has been reset, than reset the flag and write the new status for this error
        eDebounceState = eWriteError;
        asErrorHandler[ucChId].asErrorState[ucErrId].boErrorWriteStatus = FALSE;
        ucErrStatus = SYSMON_DIAG_STATUS_ERR_OK; //force to be ok in case it has other error
      }
      break;
      //case eCheckError:
    default:
      break;
    }

    //overwrite the status
    if (((eDebounceState == eWriteError) || (boErrorSetStatus != FALSE)) && (ucErrStatus > SYSMON_DIAG_STATUS_ERR_OK))
    {
       ucErrStatus_Ret = (uint8)ucErrId + SYSMON_DIAG_ERR_OPEN_LOAD;
       break;
    }
  }

  return ucErrStatus_Ret;
}


//-----------------------------------------------------------------------------
/// \brief  Return FALSE if one of the following electrical errors is active:
///           - Short to Gnd
///           - Open Load
///           - Short to Supply
///           - Thermal Shutdown
///           - Overrcurent
///
/// \descr  SysMonCheck_LedDiag_IsLightSourceErrorFree
///
/// \param  ucChIdx: Ligh source index [0..SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS]
///
/// \return boolean: true - no error active
///                 false - at least one error is active
//-----------------------------------------------------------------------------
boolean SysMonCheck_LedDiag_IsLightSourceErrorFree(uint8 ucChIdx)
{
  boolean boIsLightSourceErrorFree = TRUE;

  if (ucChIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS)
  {
    if (SysMonCheck_LedDiag_asErrorHandler[ucChIdx].ucLedState == SYSMON_DIAG_ERR_OPEN_LOAD ||
        SysMonCheck_LedDiag_asErrorHandler[ucChIdx].ucLedState == SYSMON_DIAG_ERR_SHORT_TO_GND ||
        SysMonCheck_LedDiag_asErrorHandler[ucChIdx].ucLedState == SYSMON_DIAG_ERR_SHORT_TO_BAT ||
        SysMonCheck_LedDiag_asErrorHandler[ucChIdx].ucLedState == SYSMON_DIAG_ERR_VOLTAGE_LOW ||
        SysMonCheck_LedDiag_asErrorHandler[ucChIdx].ucLedState == SYSMON_DIAG_ERR_VOLTAGE_HIGH ||
        SysMonCheck_LedDiag_asErrorHandler[ucChIdx].ucLedState == SYSMON_DIAG_ERR_THERM_SHUT_DOWN ||
        SysMonCheck_LedDiag_asErrorHandler[ucChIdx].ucLedState == SYSMON_DIAG_ERR_OVER_CURRENT ||
        SysMonCheck_LedDiag_asErrorHandler[ucChIdx].ucLedState == SYSMON_DIAG_ERR_CRC)
    {
      boIsLightSourceErrorFree = FALSE;
    }
    else
    {
      // nothig to do
    }
  }

  return boIsLightSourceErrorFree;
}


//-----------------------------------------------------------------------------
/// \brief  Return FALSE if SPI error is active:
///
/// \descr  SysMonCheck_LedDiag_IsLightSourceSpiErrorFree
///
/// \param  ucChIdx: Ligh source index [0..SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS]
///
/// \return boolean: true - no SPI error active
///                 false - SPI error present
//-----------------------------------------------------------------------------
boolean SysMonCheck_LedDiag_IsLightSourceSpiErrorFree(uint8 ucChIdx)
{
  boolean boIsLightSourceSpiErrorFree = TRUE;

  if (ucChIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS)
  {
    if (SysMonCheck_LedDiag_asErrorHandler[ucChIdx].ucLedState == SYSMON_DIAG_ERR_SPI)
    {
      boIsLightSourceSpiErrorFree = FALSE;
    }
    else
    {
      // nothig to do
    }
  }

  return boIsLightSourceSpiErrorFree;
}


//-----------------------------------------------------------------------------
/// \brief  Return FALSE if one of the following electrical errors is active for TI:
///           - Short to Gnd
///           - Open Load
///           - Short to Supply
///           - Thermal Shutdown
///           - Overrcurent
///           - SPI error
///
/// \descr  SysMonCheck_LedDiag_IsTiLightSourceErrorFree
///
/// \param  void
///
/// \return boolean: true - no error active
///                 false - at least one error is active
//-----------------------------------------------------------------------------
boolean SysMonCheck_LedDiag_IsTiLightSourceErrorFree(void)
{
  boolean boIsLightSourceErrorFree = TRUE;
  tSysMonCheck_Data_LedChParam*   pLedChPram = SysMonCheck_Data_GetaLEDChParamPtr();

  for (uint8 ucIdx = 0u; ucIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS; ucIdx++)
  {
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
    if ((pLedChPram[ucIdx].eName == SysMonCheck_Data_eLF_TI) ||
      (pLedChPram[ucIdx].eName == SysMonCheck_Data_eLF_TI_SCRL))
#elif defined (CFG_VARIANT_ECO)
    if (pLedChPram[ucIdx].eName == SysMonCheck_Data_eLF_TI)
#endif // CFG_VARIANT_FULL
    {
      if (SysMonCheck_LedDiag_asErrorHandler[ucIdx].ucLedState == SYSMON_DIAG_ERR_OPEN_LOAD ||
        SysMonCheck_LedDiag_asErrorHandler[ucIdx].ucLedState == SYSMON_DIAG_ERR_SHORT_TO_GND ||
        SysMonCheck_LedDiag_asErrorHandler[ucIdx].ucLedState == SYSMON_DIAG_ERR_SHORT_TO_BAT ||
        SysMonCheck_LedDiag_asErrorHandler[ucIdx].ucLedState == SYSMON_DIAG_ERR_VOLTAGE_LOW ||
        SysMonCheck_LedDiag_asErrorHandler[ucIdx].ucLedState == SYSMON_DIAG_ERR_VOLTAGE_HIGH ||
        SysMonCheck_LedDiag_asErrorHandler[ucIdx].ucLedState == SYSMON_DIAG_ERR_THERM_SHUT_DOWN ||
        SysMonCheck_LedDiag_asErrorHandler[ucIdx].ucLedState == SYSMON_DIAG_ERR_OVER_CURRENT ||
        SysMonCheck_LedDiag_asErrorHandler[ucIdx].ucLedState == SYSMON_DIAG_ERR_SPI ||
        SysMonCheck_LedDiag_asErrorHandler[ucIdx].ucLedState == SYSMON_DIAG_ERR_CRC ||
        SysMonCheck_LedDiag_asErrorHandler[ucIdx].ucLedState == SYSMON_DIAG_ERR_BOOST)
      {
        boIsLightSourceErrorFree = FALSE;
      }
      else
      {
        // nothig to do
      }
    }
    else
    {
      // nothing to do, channel is not TI
    }
  }

  return boIsLightSourceErrorFree;
}

// EOF

