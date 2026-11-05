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
/// \file   CtrlSwi.c
///
/// \brief  Specific code for Cdd Switch
///
/// \author ZHAO, Kai ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef UNIT_TEST
#else
#ifndef RTE_ALLOW_CROSS_HEADER_INCLUSION
#define RTE_ALLOW_CROSS_HEADER_INCLUSION
#endif
#endif

//=============================================================================
// Standard / system header file includes
//=============================================================================
#include <AL_Helper.h>
//#include <IntegrationTest.h>
#include <Util_Time.h>
#include <ctaaCtrlSwi.h>

//=============================================================================
//  Project-specific header file includes
//=============================================================================
//#include <IoHwAbUser.h>
#include <CtrlSwi.h>
#include <CtrlSwi_Cfg.h>
#include <CtrlSwi_Types.h>
#include <UtilDebounce.h>
#include <CtrlSwiRteAccess.h>
#include <Nvm.h>
#ifndef UNIT_TEST
#include <CddEft.h>
#endif
//=============================================================================
//  definitions
//=============================================================================
#define CTRLSWI_TOTAL_NO_OF_FANS                       2u
#define CTRLSWI_MATURATION_T                           2000u
#define CTRLSWI_SH2GND_TMR                             0
#define CTRLSWI_OL_TMR                                 1
#define CTRLSWI_SH2VBAT_TMR                            2
#define CTRLSWI_NO_OF_TMR                              3u
// When the error Short2Gnd or OpenLoad during On is detected, the fan must retrie to switch On 5 times.
#define CTRLSWI_MAX_RETRIES_SHORT2GND                  5u
#define CTRLSWI_RETRY_DEB_TIME                         200u
#define CTRLSWI_MAX_HSS_EFT_CFG                        4u
#define PRIORITY_ANIMATION_NONE                     FALSE
#define TI_SCROLLING                                0U
//=============================================================================
// static variables
//=============================================================================
STATIC_AL uint8              CtrlSwi_ucDelayErrorDetectionTimer[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];
STATIC_AL uint16             CtrlSwi_ucDelaySwitchOnTimer[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];
STATIC_AL boolean            CtrlSwi_aboCddSwiTarget[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];
STATIC_AL tieHssState        CtrlSwi_aboAppMTargetState[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];
STATIC_AL tsRteHssTarget     CtrlSwi_CpmFanReq;
STATIC_AL tsRte_SwitchStatus CtrlSwi_aSwitchStatus[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS + 1u];
STATIC_AL tsRte_HssStatus    CtrlSwi_aHssStatus;
STATIC_AL tsRte_CpmHSS3Duty  CtrlSwi_sRgb_Sm_Req;

STATIC_AL tisCtrlSwiState        CtrlSwi_sState;
STATIC_AL tisCtrlSwiVoltState    CtrlSwi_sVoltState;
STATIC_AL tisDiagControl_CtrlSwi CtrlSwi_sDiagControl;
STATIC_AL tisCtrlSwiErrState     CtrlSwi_sErrState = { CTRLSWI_SERRSTATE_ERR_INIT, CTRLSWI_SERRSTATE_ERR_INIT, CTRLSWI_SERRSTATE_ERR_INIT, CTRLSWI_SERRSTATE_CNT_INIT , CTRLSWI_SERRSTATE_CNT_INIT , CTRLSWI_SERRSTATE_CNT_INIT };

STATIC_AL teRte_EtatFee    CtrlSwi_Get_ETAT_FEE(void);
STATIC_AL boolean          CtrlSwi_boCodingValid;

STATIC_AL uint16    CtrlSwi_aucSwitchOnDelay[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS] =
{
  CFG_CTRLSWI_SWITCH_ON_DELAY_HSS1,
#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
  CFG_CTRLSWI_SWITCH_ON_DELAY_HSS2,
#endif
  CFG_CTRLSWI_SWITCH_ON_DELAY_HSS3
};

STATIC_AL uint8 CtrlSwi_aErrorDebounce[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS] =
{
  CFG_CTRLSWI_HSS1_ERROR_DEBOUNCE,

#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
  CFG_CTRLSWI_HSS2_ERROR_DEBOUNCE,
#endif
  CFG_CTRLSWI_HSS3_ERROR_DEBOUNCE
};

// Coding validity check
STATIC_AL boolean                CtrlSwi_boIsCodingValid = TRUE;
// Coding variables
STATIC_AL tNvmPara_Fan1Block     CtrlSwi_sCodingParam;
STATIC_AL tNvmPara_Led1Block     CtrlSwi_sCodingLedParam;
STATIC_AL uint8                  CtrlSwi_ucDebounce9V;
STATIC_AL uint8                  CtrlSwi_ucDebounce18V;

// Error flags for all 3 errors: Sh2gnd, OpenLoad, Sh2Vbat
STATIC_AL teCtrlSwiErr_State     CtrlSwi_Sh2GndFlag;
STATIC_AL teCtrlSwiErr_State     CtrlSwi_OpenLoadFlag;
STATIC_AL teCtrlSwiErr_State     CtrlSwi_Sh2VbatFlag;

STATIC_AL uint8                  CtrlSwi_ucErrTimeout[CTRLSWI_NO_OF_TMR] = { 0U };

typedef struct
{
  //input
  boolean boReq_Input;
  TIMER ulTimeMs_Input;
  //internal
  TIMER ulCommandStart;
  boolean boStartStopTimer;
  boolean boTimeOut;
}tsCtrlSwi_TimerCfg;

STATIC_AL tsCtrlSwi_TimerCfg CtrlSwi_sTimerCfg[CTRLSWI_NO_OF_TMR];

#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
//STATIC_AL tsRte_Hss3Status       CtrlSwi_boHss3Errors = { 0U };
#endif

STATIC_AL tsRte_Hss3Status       CtrlSwi_boHss3Errors = { 0U };

//=============================================================================
// Function prototypes
//=============================================================================
STATIC_AL void    CtrlSwi_ReadRTEPorts(void);
STATIC_AL void    CtrlSwi_CheckExternalTakeover(uint8 ucHssChannel);
STATIC_AL void    CtrlSwi_OperateOutputWithVoltState(uint8 ucHssChannel);
STATIC_AL void    CtrlSwi_CheckDelayErrorDetectionTimer(uint8 ucHssChannel);
STATIC_AL void    CtrlSwi_CheckDelaySwitchOnTimer(uint8 ucHssChannel);
STATIC_AL void    CtrlSwi_DTCHandling(void);
STATIC_AL void    CtrlSwi_UpdateSh2GndFlag(void);
STATIC_AL void    CtrlSwi_UpdateOpenLoadFlag(void);
STATIC_AL void    CtrlSwi_UpdateSh2VbatFlag(void);

STATIC_AL void    CtrlSwi_Sh2GndHandlingFans(void);
STATIC_AL void    CtrlSwi_OpenLoadHandlingFans(void);
STATIC_AL void    CtrlSwi_Sh2VbatHandlingFans(void);
STATIC_AL void    CtrlSwi_UpdateSwitchOnTimeCounter(uint8 ucHssChannel);
STATIC_AL void    CtrlSwi_SwitchOutput(uint8 ucHssChannel, boolean boSwitch);
STATIC_AL void    CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start(uint8 ucChannelNo, uint8 ucSwitchOutput);
STATIC_AL void    CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop(uint8 ucChannelNo);

STATIC_AL void    CtrlSwi_Diag_CheckAllErrors(uint8 ucHssChannel, boolean boActualState, boolean boDiagDelayDisabled);
STATIC_AL void    CtrlSwi_Diag_CheckShort2GndDuringOn(uint8 ucHssChannel);
STATIC_AL void    CtrlSwi_Diag_CheckShort2VbatDuringOff(uint8 ucHssChannel);
STATIC_AL void    CtrlSwi_Diag_CheckOpenloadDuringOn(uint8 ucHssChannel);

STATIC_AL void    CtrlSwi_Diag_CheckSmRgbErrors(void);

STATIC_AL void    CtrlSwi_CheckErrRetryTimer(uint8 ucHssChannel);
STATIC_AL void    CtrlSwi_ErrRetryStatergy(uint8 ucHssChannel);

STATIC_AL uint8   CtrlSwi_ErrorTimers(const boolean boReqInput, const TIMER ulTimeMs, const sint8 scTiTimerSel);
STATIC_AL boolean CtrlSwi_HandleMaturationTime(tsCtrlSwi_TimerCfg *sTimersCfg, const sint8 scTimerSel);

#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
#define CTRLSWI_LSS_CH_NR   3u
STATIC_AL void CtrlSwi_HandleLSSErrors(void);
#endif


//=============================================================================
// Macros
//=============================================================================


//=============================================================================
// Function definitions
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief  Init-function to intialize High Side Switch Driver
///
/// \descr  CtrlSwi_Init() reads RTE-Ports of EftCrcStatus and EftData,
///         initializes static variables and RTE-Port ppCtrlSwiStatusError0
///         call RTE ppIoHwAbUserHssTarget0
///         Calling once at start up.
///
/// \param  none
///
/// \return none
//----------------------------------------------------------------------------- //
void CtrlSwi_Init(void)
{
  uint8 ucIdx;
  uint16 aunCddSwiTarget[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];
  tisHssStatusError atStatusError;

#ifndef UNIT_TEST
  //Get status of the CRC for the EFTData
  CtrlSwi_sState.boEftCrcStatus = EFT_DATA_VALID_STATUS;
#else
  CtrlSwi_sState.boEftCrcStatus = CddEft_DataValid();
#endif


  // Map the parameters from the coding data
  CtrlSwi_RteAccess_MapParams();

  if ((CtrlSwi_sState.boEftCrcStatus != FALSE) && (CtrlSwi_boCodingValid != FALSE))
  {
    for (ucIdx = 0u; ucIdx < CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS; ucIdx++)
    {
      // update the static variable of state. // Set the fan off at the init state
      CtrlSwi_sState.aboHssTargetState[ucIdx] = FALSE;

      // Set the fan off at the init state
      CtrlSwi_sState.aboHssActualState[ucIdx] = FALSE;
      // Err Status
      atStatusError.eStatOn[ucIdx] = (tieHssState)HSS_SNA;

      aunCddSwiTarget[ucIdx] = 0u;
      atStatusError.eStatSupported[ucIdx] = (tieSupportInfo)SUPPORT_YES;
      CtrlSwi_sVoltState.boSwitchOn[ucIdx] = TRUE;
      CtrlSwi_sVoltState.boRemainOn[ucIdx] = TRUE;
    }

      // set RTE-Port ppaseCddSwiTarget to switch of the HSS output.
      (void)Rte_Write_CtrlSwi_TgtValue_Fan1(&aunCddSwiTarget[FAN1]);
      (void)Rte_Write_CtrlSwi_TgtValue_SMRGB(&aunCddSwiTarget[RGB_SM]);
#if defined (CFG_VARIANT_FULL) || defined(UNIT_TEST)
      (void)Rte_Write_CtrlSwi_TgtValue_Fan2(&aunCddSwiTarget[FAN2]);
     
#endif

  }
  else
  {
    for (ucIdx = 0u; ucIdx < CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS; ucIdx++)
    {
      atStatusError.eStatSupported[ucIdx] = (tieSupportInfo)SUPPORT_UNKNOWN;
      atStatusError.eStatOn[ucIdx] = (tieHssState)HSS_DISABLED;
    }
  }

  // set RTE-Port ppaseCtrlSwiStatusError0 to update the actual state of the HSS output // Speak with the architect to create this port and update the Diag port from where is read the error status
  (void)Rte_Write_CtrlSwi_StatusErr(&atStatusError);
}


//-----------------------------------------------------------------------------
/// \brief  function to read the RTE-Ports
///
/// \descr  This function reads RTE-Ports to get the voltage states and values
///         ppSysVoltRanges0_boFanSwitchOn
///         ppSysVoltRanges0_boFanRemainOn
///         ppSysVoltRanges0_boErrorDiagEnabled
///         ppIoHwAbUserHssSense0_ulActual
///         ppAppMHssTarget0_aeSetting
///         ppCodMCodingDataStatus0
///         Calling cyclicaly every 10ms
///
/// \param  none
///
/// \return none
//-----------------------------------------------------------------------------
STATIC_AL void CtrlSwi_ReadRTEPorts(void)
{
  teRte_SysVolt_Results eFanSysVoltStatus;
  STATIC_UT(teRte_SysVolt_Results, ucFanLastOperatingVoltageRange, SysVolt_eUnknown);
  tsRte_VoltRng0        CtrlSwi_sFanNewFanOperationRange;
  static TIMER          CtrlSwi_tiDebounceControl_FanRng18V;
  static TIMER          CtrlSwi_tiDebounceControl_FanRng9V;

  // read RTE port ppSysVoltRanges0 to get the voltage state for the fan output.
  (void)Rte_Read_SysVolt_FanVoltRng0_sVoltRng(&eFanSysVoltStatus);

  // read RTE port ppareCddSwiStatus to get the status from CddSwi
  (void)Rte_Read_CddSwi_SwitchStatus(&CtrlSwi_aHssStatus);

  for (uint8 ucIdx = 0u; ucIdx < CTRLSWI_CFG_OUTPUTS_CNT; ucIdx++)
  {
#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
    CtrlSwi_aSwitchStatus[ucIdx] = CtrlSwi_aHssStatus.sSwitchStatus[ucIdx];
#else
    if (CtrlSwi_sCodingLedParam.LedConfigDRV13.FUSA_DRV13_NAME == HSS_SM || CtrlSwi_sCodingLedParam.LedConfigDRV13.FUSA_DRV13_NAME == HSS_DRL)
    {
      CtrlSwi_aSwitchStatus[RGB_SM] = CtrlSwi_aHssStatus.sSwitchStatus[ucIdx];
    }
    else if (CtrlSwi_sCodingParam.Fans_Presence.ucFan1Enabled != 0u)
    {
      CtrlSwi_aSwitchStatus[FAN1] = CtrlSwi_aHssStatus.sSwitchStatus[ucIdx];
    }
    else
    {
      //do nothing
    }
#endif
  }

  // read RTE-Port ppAppMHssTarget0 to get the target value of the HSS output
  (void)Rte_Read_CpmHssTarget0_sSetting(&CtrlSwi_CpmFanReq);
  (void)Rte_Read_Cpm_CtrlSwi_HSS3Target(&CtrlSwi_sRgb_Sm_Req);

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)

  // LSS status (OUT Fct)
  CtrlSwi_aSwitchStatus[CTRLSWI_LSS_CH_NR] = CtrlSwi_aHssStatus.sSwitchStatus[CTRLSWI_LSS_CH_NR];


  CtrlSwi_aboAppMTargetState[0] = CtrlSwi_CpmFanReq.aeSetting[0];
  CtrlSwi_aboAppMTargetState[1] = CtrlSwi_CpmFanReq.aeSetting[1];
  CtrlSwi_aboAppMTargetState[2] = (CtrlSwi_sRgb_Sm_Req.unDutyHSS3 != 0U) ? TRUE : FALSE;
#else
  CtrlSwi_aboAppMTargetState[0] = CtrlSwi_CpmFanReq.aeSetting[0];
  CtrlSwi_aboAppMTargetState[1] = (CtrlSwi_sRgb_Sm_Req.unDutyHSS3 != 0U) ? TRUE : FALSE;
#endif

  CtrlSwi_sFanNewFanOperationRange.eVoltRng = eFanSysVoltStatus;


  //PRQA S 5324 1 // compactness and readability
  // Check the new fan voltage operating range:
  switch (CtrlSwi_sFanNewFanOperationRange.eVoltRng)
  {
    //   // In case the voltage dropped below (see coding param) or rise above (see coding param), then:
  case SysVolt_eLow2:

    // Switch the Fan off to protect it:
    CtrlSwi_sVoltState.boSwitchOn[0] = FALSE;
    CtrlSwi_sVoltState.boRemainOn[0] = FALSE;
#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
    CtrlSwi_sVoltState.boSwitchOn[1] = FALSE;
    CtrlSwi_sVoltState.boRemainOn[1] = FALSE;
#endif
    CtrlSwi_sVoltState.boDiagEnabled = FALSE;

    break;

  case SysVolt_eHigh2:

      // Only if we come from a high1 range than the req shall be debounced with 200ms
      if (ucFanLastOperatingVoltageRange == SysVolt_eHigh1)
      {
        // Check if the fan's voltage range has been debounced: it has been low/high voltage state for long enough:
        CtrlSwi_tiDebounceControl_FanRng18V = TimerStart(UTILTIME_MSEC(CtrlSwi_ucDebounce18V));
      }
      else
      {
        if (TimerTimeout(CtrlSwi_tiDebounceControl_FanRng18V) != FALSE)
        {
          // Switch the Fan off to protect it:
          CtrlSwi_sVoltState.boSwitchOn[0] = FALSE;
          CtrlSwi_sVoltState.boRemainOn[0] = FALSE;
#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
          CtrlSwi_sVoltState.boSwitchOn[1] = FALSE;
          CtrlSwi_sVoltState.boRemainOn[1] = FALSE;
#endif
          CtrlSwi_sVoltState.boDiagEnabled = FALSE;
        }
        else
        {
          // wait
        }
      }

    break;

    // In case the fan supply voltage is between x and yV (see coding param):
  case SysVolt_eNormal:

    // Only if we come from a low2 range than the req shall be debounced with 200ms
    if (ucFanLastOperatingVoltageRange == SysVolt_eLow1)
    {
      // Check if the fan's voltage range has been debounced: it has been low/high voltage state for long enough:
      CtrlSwi_tiDebounceControl_FanRng9V = TimerStart(UTILTIME_MSEC(CtrlSwi_ucDebounce9V));
    }
    else
      {
        if (TimerTimeout(CtrlSwi_tiDebounceControl_FanRng9V) != FALSE)
        {
          // Switch the Fan off to protect it:
          CtrlSwi_sVoltState.boSwitchOn[0] = TRUE;
          CtrlSwi_sVoltState.boRemainOn[0] = TRUE;
#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
          CtrlSwi_sVoltState.boSwitchOn[1] = TRUE;
          CtrlSwi_sVoltState.boRemainOn[1] = TRUE;
#endif
          CtrlSwi_sVoltState.boDiagEnabled = TRUE;
        }
        else
        {
          // wait
        }
      }
    break;

    // When the fan operating voltage is between [(see coding param)] and/or [(see coding param)] V, then the fan cannot be switched on
    // no matter the request from either Thermo; it can only be switched off if it is required:
  case SysVolt_eHigh1:
  case SysVolt_eLow1:

     // Switch the Fan off to protect it:
   CtrlSwi_sVoltState.boSwitchOn[0] = FALSE;
   CtrlSwi_sVoltState.boRemainOn[0] = TRUE;
#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
   CtrlSwi_sVoltState.boSwitchOn[1] = FALSE;
   CtrlSwi_sVoltState.boRemainOn[1] = TRUE;
#endif
   CtrlSwi_sVoltState.boDiagEnabled = FALSE;

    break;

  default:
    // will reach here only if SysVolt sends the wrong fan operating voltage range.
    // In this case, just turn the fan OFF to be safe!
    CtrlSwi_sVoltState.boSwitchOn[0] = FALSE;
    CtrlSwi_sVoltState.boRemainOn[0] = FALSE;
    CtrlSwi_sVoltState.boSwitchOn[1] = FALSE;
    CtrlSwi_sVoltState.boRemainOn[1] = FALSE;
    CtrlSwi_sVoltState.boDiagEnabled = FALSE;

    break;
  }

  // save the last voltage state of the Fan
  // in order for the new range to be correctly compared next cycle:
  ucFanLastOperatingVoltageRange = CtrlSwi_sFanNewFanOperationRange.eVoltRng;

}
//-----------------------------------------------------------------------------
/// \brief  cyclic function to control the High Side Switch
///
/// \descr  CtrlSwi_Cycle() reads RTE-Port ppAppMHssTarget0 to get target value
///         processes Diagnose Control, writes RTE-Port ppCtrlSwiStatusError0,
///         call RTE ppIoHwAbUserHssTarget0
///         Calling cyclicaly every 10ms
///
/// \param  none
///
/// \return none
//-----------------------------------------------------------------------------
void CtrlSwi_Cycle0(void)
{
  tisHssStatusError atStatusError;
  uint8  aucErrorStates[ERRORTYPE_MAX];
  teRte_EtatFee  ucEtatFee = CtrlSwi_Get_ETAT_FEE();
  tRteCtrlSwi_ErrorFlags boSwiErrStates;
  tsRte_CpmHSS3Duty sRgb_Sm_Req;
  STATIC_AL tScrollingPresent_Stat  ScrollingPresent;
  tsRte_TgtAniArrScr            Swi_Anima_Scrolling;
  teRte_SateliteStatus eScrollingSatellite_Ctrl = eRte_ScrollingSatelite_Off;
  teRte_ScrollingTgt eDiagScrollingSatellite_Ctrl = eRte_eScrollingTgt_Off;
  boolean boScrollingTakeOver_Stat = FALSE;


#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
  tsRte_SysMonLgtTiReq   sTurnIndicatorReq = { 0 };
  uint16 aunCddSwiTarget[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS] = { 0u, 0u, 0u };
  (void)Rte_Read_AnimaScrollingActivation(&Swi_Anima_Scrolling);
#else
  uint16 aunCddSwiTarget[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS] = { 0u, 0u };
#endif

  if (CtrlSwi_sState.boEftCrcStatus != FALSE)
  {
    // read the RTE-port to get the voltage state from SysVolt and HssSense from IoHwAbUser
    CtrlSwi_ReadRTEPorts();
    for (uint8 ucIdx = 0u; ucIdx < CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS; ucIdx++)
    {
#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
      if (CtrlSwi_aSwitchStatus[ucIdx].ucHwState == CTRLSWI_CFG_HSS_SUPPORT)
#else
      if (CtrlSwi_aSwitchStatus[ucIdx].ucHwState == CTRLSWI_CFG_HSS_SUPPORT)
#endif
      {
#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
        // ucIx == FAN1 || FAN2
        if (ucIdx != RGB_SM)
        {
          // Check retry strategy
          // Check all error types of the corresponding output with actual state every 60ms ucIdx number
          CtrlSwi_Diag_CheckAllErrors(ucIdx, CtrlSwi_sState.aboHssActualState[ucIdx], CtrlSwi_sState.aboHssStateChangedDiagDisabled[ucIdx]);
          // Check retry strategy
          CtrlSwi_ErrRetryStatergy(ucIdx);
        }
        // ucIdx == RGB
        else
        {
          CtrlSwi_Diag_CheckSmRgbErrors();
        }
#else

        if ((CtrlSwi_sCodingLedParam.LedConfigDRV13.FUSA_DRV13_NAME == HSS_SM || CtrlSwi_sCodingLedParam.LedConfigDRV13.FUSA_DRV13_NAME == HSS_DRL) && (ucIdx == RGB_SM))
        {
          CtrlSwi_Diag_CheckSmRgbErrors();
        }
        else if ((CtrlSwi_sCodingParam.Fans_Presence.ucFan1Enabled != 0u) && (ucIdx == FAN1))   //If FAN
        {
          // Check retry strategy
          // Check all error types of the corresponding output with actual state every 60ms ucIdx number
          CtrlSwi_Diag_CheckAllErrors(ucIdx, CtrlSwi_sState.aboHssActualState[ucIdx], CtrlSwi_sState.aboHssStateChangedDiagDisabled[ucIdx]);
          // Check retry strategy
          CtrlSwi_ErrRetryStatergy(ucIdx);
        }
        else
        {
          // do nothing
        }
#endif
       

        // Ext TakeOver (Diagnosis)
        CtrlSwi_CheckExternalTakeover(ucIdx);

        CtrlSwi_OperateOutputWithVoltState(ucIdx);

        // prepare the actual state of RTE Port ppCtrlSwiStatusError0
        if (CtrlSwi_sState.aboHssActualState[ucIdx] == FALSE)
        {
          atStatusError.eStatOn[ucIdx] = (tieHssState)HSS_OFF;
          atStatusError.unStatCurrent[ucIdx] = 0U;
        }
        else
        {
          atStatusError.eStatOn[ucIdx] = (tieHssState)HSS_ON;
          atStatusError.unStatCurrent[ucIdx] = CtrlSwi_aSwitchStatus[ucIdx].unActCurrent; // (tiu16Current_mA)CtrlSwi_sState.aunHssCurrent[ucIdx];
          CtrlSwi_UpdateSwitchOnTimeCounter(ucIdx);
        }

        if (CtrlSwi_sVoltState.boDiagEnabled != FALSE)
        {
          if ((CtrlSwi_sState.aboHssTargetState[ucIdx] == FALSE) && (CtrlSwi_sState.aboErrOffPermanent[ucIdx] == FALSE))
          {
            atStatusError.eErrShortToGnd[ucIdx] = (tieError)CTRLSWI_CFG_ERR_SNA;
            atStatusError.eErrOpenLoad[ucIdx] = (tieError)CTRLSWI_CFG_ERR_SNA;
          }
          else
          {
            atStatusError.eErrShortToGnd[ucIdx] = (tieError)CtrlSwi_sErrState.ucErrShortToGnd[ucIdx];
            atStatusError.eErrOpenLoad[ucIdx] = (tieError)CtrlSwi_sErrState.ucErrOpenLoad[ucIdx];
          }
          atStatusError.eErrShortToVBat[ucIdx] = (tieError)CtrlSwi_sErrState.ucErrShortToVbat[ucIdx];
        }
        else
        {
          // set diagnose disabled
          atStatusError.eErrShortToGnd[ucIdx] = (tieError)CTRLSWI_CFG_ERR_SNA;
          atStatusError.eErrShortToVBat[ucIdx] = (tieError)CTRLSWI_CFG_ERR_SNA;
          atStatusError.eErrOpenLoad[ucIdx] = (tieError)CTRLSWI_CFG_ERR_SNA;
        }

        atStatusError.eStatSupported[ucIdx] = (tieSupportInfo)SUPPORT_YES;

        //aunCddSwiTarget[ucIdx] = (CtrlSwi_aboCddSwiTarget[ucIdx] == TRUE) ? (ucIdx == HSS3) ? (CtrlSwi_sRgb_Sm_Req.unDutyHSS3) : 32768u : 0u;
        if (CtrlSwi_aboCddSwiTarget[ucIdx] != FALSE)
        {
#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
          if (ucIdx == HSS3)
          {
            aunCddSwiTarget[ucIdx] = CtrlSwi_sRgb_Sm_Req.unDutyHSS3;
          }
          else
          {
            aunCddSwiTarget[ucIdx] = 32768u;
          }
#elif defined (SAMPLE_ECO)
          if ((CtrlSwi_sCodingLedParam.LedConfigDRV13.FUSA_DRV13_NAME == HSS_SM || CtrlSwi_sCodingLedParam.LedConfigDRV13.FUSA_DRV13_NAME == HSS_DRL) && (ucIdx == RGB_SM))    //SM/RGB/DRL
          {
            aunCddSwiTarget[ucIdx] = CtrlSwi_sRgb_Sm_Req.unDutyHSS3;
          }
          else if ((CtrlSwi_sCodingParam.Fans_Presence.ucFan1Enabled != 0u) && (ucIdx == FAN1))       //FAN
          {
            aunCddSwiTarget[ucIdx] = 32768u;
          }
          else
          {
            aunCddSwiTarget[ucIdx] = 0u;
          }
#endif
        }
        else
        {
          aunCddSwiTarget[ucIdx] = 0u;
        }
      }
      else //if (CtrlSwi_aSwitchStatus[ucIdx].ucHwState == CTRLSWI_CFG_HSS_SUPPORT)
      {
        atStatusError.eStatSupported[ucIdx] = (tieSupportInfo)SUPPORT_NO;
        atStatusError.eStatOn[ucIdx] = (tieHssState)HSS_DISABLED;
        atStatusError.eErrShortToGnd[ucIdx] = (tieError)CTRLSWI_CFG_ERR_SNA;
        atStatusError.eErrShortToVBat[ucIdx] = (tieError)CTRLSWI_CFG_ERR_SNA;
        atStatusError.eErrOpenLoad[ucIdx] = (tieError)CTRLSWI_CFG_ERR_SNA;
        atStatusError.unStatCurrent[ucIdx] = 0u;
        aunCddSwiTarget[ucIdx] = 0u;
        CtrlSwi_aSwitchStatus[ucIdx].ucErrShort2GND = CTRLSWI_CFG_ERR_SNA;
        CtrlSwi_aSwitchStatus[ucIdx].ucErrOpenLoad = CTRLSWI_CFG_ERR_SNA;
        CtrlSwi_aSwitchStatus[ucIdx].ucErrShort2VBAT = CTRLSWI_CFG_ERR_SNA;
        CtrlSwi_aSwitchStatus[ucIdx].ucHwState = CTRLSWI_CFG_HSS_NOSUPPORT;
        CtrlSwi_aSwitchStatus[ucIdx].unActCurrent = 0u;
        CtrlSwi_aSwitchStatus[ucIdx].unActVal = 0u;
      }
    }

    // set RTE-Port ppaseCddSwiTarget to switch of the HSS output.
    (void)Rte_Write_CtrlSwi_TgtValue_Fan1(&aunCddSwiTarget[FAN1]);
    (void)Rte_Write_CtrlSwi_TgtValue_SMRGB(&aunCddSwiTarget[RGB_SM]);
#if defined (CFG_VARIANT_FULL ) || defined(UNIT_TEST)
    (void)Rte_Write_CtrlSwi_TgtValue_Fan2(&aunCddSwiTarget[FAN2]);
   
#endif

    //Aici
  }
  else
  {
    for (uint8 ucIdx = 0u; ucIdx < CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS; ucIdx++)
    {
      atStatusError.eStatSupported[ucIdx] = (tieSupportInfo)SUPPORT_NO;
      atStatusError.eStatOn[ucIdx] = (tieHssState)HSS_DISABLED;
      atStatusError.eErrShortToGnd[ucIdx] = (tieError)CTRLSWI_CFG_ERR_SNA;
      atStatusError.eErrShortToVBat[ucIdx] = (tieError)CTRLSWI_CFG_ERR_SNA;
      atStatusError.eErrOpenLoad[ucIdx] = (tieError)CTRLSWI_CFG_ERR_SNA;
      atStatusError.unStatCurrent[ucIdx] = 0u;
      aunCddSwiTarget[ucIdx] = 0u;
      CtrlSwi_aSwitchStatus[ucIdx].ucErrShort2GND = CTRLSWI_CFG_ERR_SNA;
      CtrlSwi_aSwitchStatus[ucIdx].ucErrOpenLoad = CTRLSWI_CFG_ERR_SNA;
      CtrlSwi_aSwitchStatus[ucIdx].ucErrShort2VBAT = CTRLSWI_CFG_ERR_SNA;
      CtrlSwi_aSwitchStatus[ucIdx].ucHwState = CTRLSWI_CFG_HSS_NOSUPPORT;
      CtrlSwi_aSwitchStatus[ucIdx].unActCurrent = 0u;
      CtrlSwi_aSwitchStatus[ucIdx].unActVal = 0u;
    }
    (void)aucErrorStates;

  }


#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)

  // Report HSS3 status
  CtrlSwi_boHss3Errors.boHss3_Sh2GndStatus = (atStatusError.eErrShortToGnd[HSS3] == CTRLSWI_CFG_ERR_YES) ? TRUE : FALSE;
  CtrlSwi_boHss3Errors.boHss3_OpenLoadStatus = (atStatusError.eErrOpenLoad[HSS3] == CTRLSWI_CFG_ERR_YES) ? TRUE : FALSE;
  CtrlSwi_boHss3Errors.boHss3_Sh2VbatStatus = (atStatusError.eErrShortToVBat[HSS3] == CTRLSWI_CFG_ERR_YES) ? TRUE : FALSE;
  CtrlSwi_boHss3Errors.boHss3_Enabled = (atStatusError.eStatOn[HSS3] != HSS_OFF) ? TRUE : FALSE;

    (void)Rte_Write_CtrlSwi_Hss3StatusErr(&CtrlSwi_boHss3Errors);
#elif defined (CFG_VARIANT_ECO)
  // on eco
//if coding -> SM present
  //Vlad:


  if (CtrlSwi_sCodingLedParam.LedConfigDRV13.FUSA_DRV13_NAME == HSS_SM || CtrlSwi_sCodingLedParam.LedConfigDRV13.FUSA_DRV13_NAME == HSS_DRL)   //If SM present or DRL/POS
  {
    CtrlSwi_boHss3Errors.boHss3_Sh2GndStatus = (atStatusError.eErrShortToGnd[RGB_SM] == CTRLSWI_CFG_ERR_YES) ? TRUE : FALSE;
    CtrlSwi_boHss3Errors.boHss3_OpenLoadStatus = (atStatusError.eErrOpenLoad[RGB_SM] == CTRLSWI_CFG_ERR_YES) ? TRUE : FALSE;
    CtrlSwi_boHss3Errors.boHss3_Sh2VbatStatus = (atStatusError.eErrShortToVBat[RGB_SM] == CTRLSWI_CFG_ERR_YES) ? TRUE : FALSE;
    CtrlSwi_boHss3Errors.boHss3_Enabled = (atStatusError.eStatOn[RGB_SM] != HSS_OFF) ? TRUE : FALSE;
  }
  else   if ((CtrlSwi_sCodingParam.Fans_Presence.ucFan1Enabled != 0u))                //If FAN
  {
    CtrlSwi_boHss3Errors.boHss3_Sh2GndStatus = (atStatusError.eErrShortToGnd[FAN1] == CTRLSWI_CFG_ERR_YES) ? TRUE : FALSE;
    CtrlSwi_boHss3Errors.boHss3_OpenLoadStatus = (atStatusError.eErrOpenLoad[FAN1] == CTRLSWI_CFG_ERR_YES) ? TRUE : FALSE;
    CtrlSwi_boHss3Errors.boHss3_Sh2VbatStatus = (atStatusError.eErrShortToVBat[FAN1] == CTRLSWI_CFG_ERR_YES) ? TRUE : FALSE;
    CtrlSwi_boHss3Errors.boHss3_Enabled = (atStatusError.eStatOn[FAN1] != HSS_OFF) ? TRUE : FALSE;
  }
  else
  {
    //do nothing
  }
  (void)Rte_Write_CtrlSwi_Hss3StatusErr(&CtrlSwi_boHss3Errors);
#endif

  // set RTE-Port ppCtrlSwiStatusError0 to update the actual state of the HSS output.- In case we need it to be clarified (UDS?)
  (void)Rte_Write_CtrlSwi_StatusErr(&atStatusError);

  if (NvmBlockDeltaPwmPara.eNVM_Function_STT == eOptionSTT_Present)
  {
    //4_1 = Engine running // Etat_1_3 = STT Stop phase // Only if these conditions are true then diagnosis shall be realized
    if ((ucEtatFee == eEtatFee_4_1) || (ucEtatFee == eEtatFee_1_3c))
    {
      // set DTC
      CtrlSwi_DTCHandling();
    }
    else
    {
      // do not set dtcs when cranking is running
    }
  }
  else
  {
    //don't do diagnosis
  }

  // LSS control and diagnostic

#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
  (void)Rte_Read_CddSwi_ScrollingOn_Stat(&ScrollingPresent);
  (void)Rte_Read_Diag_TiScrollingTakeOver(&boScrollingTakeOver_Stat);

  if ((ScrollingPresent.boScrollingDRLPresent_Stat != FALSE)) //check if DRL Scrolling is requested
  {
    switch (Swi_Anima_Scrolling.unTgtAniScr[TI_SCROLLING])
    {
    case 1u:
      eScrollingSatellite_Ctrl = eRte_eScrollingSatelite_On_Scrolling_Off;
      break;
    case 2u:
      eScrollingSatellite_Ctrl = eRte_eScrollingSatelite_On_Scrolling_On;
      break;
    default:
      eScrollingSatellite_Ctrl = eRte_ScrollingSatelite_Off;
      break;
    }

  }
  else if ((ScrollingPresent.boScrollingTIPresent_Stat != FALSE) && (boScrollingTakeOver_Stat == FALSE)) //check if TI Scrolling is requested
  {

      (void)Rte_Read_SysMon_StdLgtTi_Req(&sTurnIndicatorReq);

      if ((sTurnIndicatorReq.eSigQty == SIG_VALID) && (sTurnIndicatorReq.eTi_Scrolling != eScrollingTI_Off))
      {
       
          eScrollingSatellite_Ctrl = eRte_eScrollingSatelite_On_Scrolling_On;
      }
      else if(Swi_Anima_Scrolling.unTgtAniScr[TI_SCROLLING] != (uint16)eRte_ScrollingSatelite_Off)
             {
               switch (Swi_Anima_Scrolling.unTgtAniScr[TI_SCROLLING]) //take the intensity from coding anima
               {
               case 1u:
                 eScrollingSatellite_Ctrl = eRte_eScrollingSatelite_On_Scrolling_Off;
                 break;
               case 2u:
                 eScrollingSatellite_Ctrl = eRte_eScrollingSatelite_On_Scrolling_On;
                 break;
               default:
                 eScrollingSatellite_Ctrl = eRte_ScrollingSatelite_Off;
                 break;
               }
             }
      else
      {
      // skip
      eScrollingSatellite_Ctrl = eRte_ScrollingSatelite_Off;
      }
  }
  else if ((ScrollingPresent.boScrollingTIPresent_Stat != FALSE) && (boScrollingTakeOver_Stat != FALSE))
  {
    //take value from diag routine and pass it to the driver
    (void)Rte_Read_Diag_Scrolling_TgtValue(&eDiagScrollingSatellite_Ctrl);

    switch (eDiagScrollingSatellite_Ctrl)
    {
    case eRte_eScrollingTgt_On_Scrolling_Off:
      eScrollingSatellite_Ctrl = eRte_eScrollingSatelite_On_Scrolling_Off;
      break;
    case eRte_eScrollingTgt_On_Scrolling_On:
      eScrollingSatellite_Ctrl = eRte_eScrollingSatelite_On_Scrolling_On;
      break;
    default:
      eScrollingSatellite_Ctrl = eRte_ScrollingSatelite_Off;
      break;
    }
  }
  else
  {
    //skip
    eScrollingSatellite_Ctrl = eRte_ScrollingSatelite_Off;
  }

  if (ScrollingPresent.boScrollingTIPresent_Stat != FALSE || ScrollingPresent.boScrollingDRLPresent_Stat != FALSE)
  {
    CtrlSwi_HandleLSSErrors();
  }

  (void)Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite(&eScrollingSatellite_Ctrl);
#endif

} // PRQA S 5316,5336,5324,5330,5310 1 // compactness and readability

//-----------------------------------------------------------------------------
/// \brief  operate the target value
///
/// \descr  This function operates the target value with external takeover value
///         and target value from APPM
///
/// \param  ucHssChannel     0: HSS1, 1: HSS2, 2: HSS3
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlSwi_CheckExternalTakeover(uint8 ucHssChannel)
{
  if (CtrlSwi_sDiagControl.teMode[ucHssChannel] == eDiagCtrl_CtrlSwi_Disabled)
  {
    if (CtrlSwi_sState.aboRetryStarted[ucHssChannel] != TRUE)
    {
      // update the static variable of target
      CtrlSwi_sState.aboHssTargetState[ucHssChannel] = (boolean)CtrlSwi_aboAppMTargetState[ucHssChannel];
    }
#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
    else if  ((ucHssChannel == FAN1) || (ucHssChannel == FAN2))
#else
    else if (ucHssChannel == FAN1)
#endif
    {
      CtrlSwi_sState.aboHssTargetState[ucHssChannel] = CtrlSwi_sState.aboRetryTarget[ucHssChannel];
    }
    else
    {
      // do nothing
    }
  }
  // diagnose control mode
  else //CtrlSwi_sDiagControl.teMode[ucHssChannel] == eDiagCtrl_CtrlSwi_Enabled
  {
    // update the static variable of target
    CtrlSwi_sState.aboHssTargetState[ucHssChannel] = CtrlSwi_sDiagControl.ucHssOutput[ucHssChannel];
  }
}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  [paramName]
///
/// \return [returnTyp]
//-----------------------------------------------------------------------------
STATIC_AL void CtrlSwi_ErrRetryStatergy(uint8 ucHssChannel)
{
  // Check if the error is set permanent
  if (CtrlSwi_sState.aboErrOffPermanent[ucHssChannel] == FALSE)
  {
    // Apply debounce time 500 * 10 ms
    CtrlSwi_CheckErrRetryTimer(ucHssChannel);
    // Check the request
    if (CtrlSwi_aboAppMTargetState[ucHssChannel] != FALSE)
    {
      // Check if the retry strategy has started
      if (CtrlSwi_sState.aboRetryStarted[ucHssChannel] == TRUE)
      {
        // Check if the retry strategy has reached 5 retries and the retry is still alowed
        if ((CtrlSwi_sState.aucRetryCounter[ucHssChannel] < CTRLSWI_MAX_RETRIES_SHORT2GND)
          && (CtrlSwi_sState.aboRetryAllowed[ucHssChannel] == TRUE))
        {
          // Set the flag on true
          CtrlSwi_sState.aboRetryTarget[ucHssChannel] = TRUE;
          // Increment the counter
          CtrlSwi_sState.aucRetryCounter[ucHssChannel]++;
          // Set the flag on false
          CtrlSwi_sState.aboRetryAllowed[ucHssChannel] = FALSE;
        }
        // Retry finished?
        else if (CtrlSwi_sState.aucRetryCounter[ucHssChannel] == CTRLSWI_MAX_RETRIES_SHORT2GND)
        {
          // Set the retry strategy in off
          CtrlSwi_sState.aboRetryTarget[ucHssChannel] = FALSE;
          // Set the permanent error
          CtrlSwi_sState.aboErrOffPermanent[ucHssChannel] = TRUE;
        }
        else
        {
          // do nothing
        }
      }
      else
      {
        //do nothing
      }

    }
    else
    {
      // The retry is off
      CtrlSwi_sState.aboRetryTarget[ucHssChannel] = FALSE;
      // Counter reset
      CtrlSwi_sState.aucRetryCounter[ucHssChannel] = 0u;
      // No retry started
      CtrlSwi_sState.aboRetryStarted[ucHssChannel] = FALSE;

      CtrlSwi_sState.aboRetryAllowed[ucHssChannel] = FALSE;
    }
  }
  else
  {
    // Retry can be started
    CtrlSwi_sState.aboRetryStarted[ucHssChannel] = TRUE;
    // Set the flag on false
    CtrlSwi_sState.aboRetryTarget[ucHssChannel] = FALSE;
  }
}// PRQA S 5336 1 // compactness and readability

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param  [paramName]
///
/// \return [returnTyp]
//-----------------------------------------------------------------------------
STATIC_AL void CtrlSwi_CheckErrRetryTimer(uint8 ucHssChannel)
{
  // Check if time has passed
  if (CtrlSwi_sState.aunRetryTimer[ucHssChannel] > 0u)
  {
    // Still counting timer is decremented
    CtrlSwi_sState.aunRetryTimer[ucHssChannel]--;

    // Timer expired
    if (CtrlSwi_sState.aunRetryTimer[ucHssChannel] == 0u)
    {
      //Retry is allowed
      CtrlSwi_sState.aboRetryAllowed[ucHssChannel] = TRUE;
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  update the error state of all the outputs and set DTC
///
/// \descr  This function sets the error state for the DTC event and
///         calls the DTC calls with the Passed and Failed.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlSwi_DTCHandling(void)
{
  // Handle all the errors by calling the specific function
  CtrlSwi_Sh2GndHandlingFans();
  CtrlSwi_OpenLoadHandlingFans();
  CtrlSwi_Sh2VbatHandlingFans();
}

//-----------------------------------------------------------------------------
/// \brief  update the statistic of HSS switch on time
///
/// \descr  This function increments the statitic counter in case of the HSS output has no error.
///
/// \param  ucHssChannel     0: HSS1, 1: HSS2, 2: HSS3
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlSwi_UpdateSwitchOnTimeCounter(uint8 ucHssChannel)
{
  boolean boErrActive = FALSE;

  if (((CtrlSwi_sErrState.ucErrShortToGnd[ucHssChannel]) == CTRLSWI_CFG_ERR_YES) || ((CtrlSwi_sErrState.ucErrOpenLoad[ucHssChannel]) == CTRLSWI_CFG_ERR_YES) || ((CtrlSwi_sErrState.ucErrShortToVbat[ucHssChannel]) == CTRLSWI_CFG_ERR_YES))
  {
    boErrActive = TRUE;
  }

  if (boErrActive == FALSE)
  {
    CtrlSwi_sState.aulHssStatisticOnTime[ucHssChannel] += UTILTIME_MSEC(10); // 10ms x 1000 = 10000us
  }
}

//-----------------------------------------------------------------------------
/// \brief Updates the error flag
///
/// \descr  Function which Updates the error flag for the Sh2Gnd
///
/// \param  void
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlSwi_UpdateSh2GndFlag(void)
{
#if defined (SAMPLE_ECO)
  if (CtrlSwi_sState.aboErrOffPermanent[FAN1] != FALSE)
#elif defined (SAMPLE_FULL) || defined (UNIT_TEST)
  if ((CtrlSwi_sState.aboErrOffPermanent[FAN1] != FALSE) || (CtrlSwi_sState.aboErrOffPermanent[FAN2] != FALSE))
#endif
  {
    // ERR YES
    CtrlSwi_Sh2GndFlag = eERR_YES;
  }
#if defined (SAMPLE_ECO)
  else if (CtrlSwi_aSwitchStatus[FAN1].ucErrShort2GND == CTRLSWI_CFG_ERR_SNA)
#elif defined (SAMPLE_FULL) || defined (UNIT_TEST)
  else if ((CtrlSwi_aSwitchStatus[FAN1].ucErrShort2GND == CTRLSWI_CFG_ERR_SNA) || (CtrlSwi_aSwitchStatus[FAN2].ucErrShort2GND == CTRLSWI_CFG_ERR_SNA))
#endif
  {
    // NO ERROR
    CtrlSwi_Sh2GndFlag = eERR_SNA;
  }
#if defined (SAMPLE_ECO)
  else if (CtrlSwi_aSwitchStatus[FAN1].ucErrShort2GND == CTRLSWI_CFG_ERR_NO)
#elif defined (SAMPLE_FULL) || defined (UNIT_TEST)
  else if ((CtrlSwi_aSwitchStatus[FAN1].ucErrShort2GND == CTRLSWI_CFG_ERR_NO) && (CtrlSwi_aSwitchStatus[FAN2].ucErrShort2GND == CTRLSWI_CFG_ERR_NO))
#endif
  {
    // NO ERROR
    CtrlSwi_Sh2GndFlag = eERR_NO;
  }
  else
  {

  }
}
//-----------------------------------------------------------------------------
/// \brief Updates the error flag
///
/// \descr  Function which Updates the error flag for the Open Load
///
/// \param  void
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlSwi_UpdateOpenLoadFlag(void)
{
#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
  if ((CtrlSwi_aSwitchStatus[FAN1].ucErrOpenLoad == CTRLSWI_CFG_ERR_YES) || (CtrlSwi_aSwitchStatus[FAN2].ucErrOpenLoad == CTRLSWI_CFG_ERR_YES))
#else
  if (CtrlSwi_aSwitchStatus[FAN1].ucErrOpenLoad == CTRLSWI_CFG_ERR_YES)
#endif
  {
    // ERR YES
    CtrlSwi_OpenLoadFlag = eERR_YES;
  }
#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
  else if ((CtrlSwi_aSwitchStatus[FAN1].ucErrOpenLoad == CTRLSWI_CFG_ERR_NO) || (CtrlSwi_aSwitchStatus[FAN2].ucErrOpenLoad == CTRLSWI_CFG_ERR_NO))
#else
  else if (CtrlSwi_aSwitchStatus[FAN1].ucErrOpenLoad == CTRLSWI_CFG_ERR_NO)
#endif
  {
    // NO ERROR
    CtrlSwi_OpenLoadFlag = eERR_NO;
  }
  else
  {
    // ERR SNA
    CtrlSwi_OpenLoadFlag = eERR_SNA;
  }

}
//-----------------------------------------------------------------------------
/// \brief Updates the error flag
///
/// \descr  Function which Updates the error flag for the Sh2Vbat
///
/// \param  void
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlSwi_UpdateSh2VbatFlag(void)
{
#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
  if ((CtrlSwi_aSwitchStatus[FAN1].ucErrShort2VBAT == CTRLSWI_CFG_ERR_YES) || (CtrlSwi_aSwitchStatus[FAN2].ucErrShort2VBAT == CTRLSWI_CFG_ERR_YES))
#else
    if (CtrlSwi_aSwitchStatus[FAN1].ucErrShort2VBAT == CTRLSWI_CFG_ERR_YES)
#endif
  {
    // ERR YES
    CtrlSwi_Sh2VbatFlag = eERR_YES;
  }
#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
  else if ((CtrlSwi_aSwitchStatus[FAN1].ucErrShort2VBAT == CTRLSWI_CFG_ERR_NO) || (CtrlSwi_aSwitchStatus[FAN2].ucErrShort2VBAT == CTRLSWI_CFG_ERR_NO))
#else
    else if (CtrlSwi_aSwitchStatus[FAN1].ucErrShort2VBAT == CTRLSWI_CFG_ERR_NO)
#endif
    {
    // NO ERROR
    CtrlSwi_Sh2VbatFlag = eERR_NO;
  }
  else
  {
    // ERR SNA
    CtrlSwi_Sh2VbatFlag = eERR_SNA;
  }

}

//-----------------------------------------------------------------------------
/// \brief Handles the DTC for Sh2Gnd and updates the error flag
///
/// \descr  Function which sets the DTC for Sh2Gnd and updates the error flag
///
/// \param  void
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlSwi_Sh2GndHandlingFans(void)
{
  // Map the status of the error
  CtrlSwi_UpdateSh2GndFlag();

  // Check the status of the error from CddSwitch
  switch (CtrlSwi_Sh2GndFlag)
  {
    // SNA
  case eERR_SNA:

    break;
    // ERR YES
  case eERR_YES:

    // Check if timer started
    if (CtrlSwi_ucErrTimeout[CTRLSWI_SH2GND_TMR] == 0u)
    {
      // Start timer
      CtrlSwi_ucErrTimeout[CTRLSWI_SH2GND_TMR] = CtrlSwi_ErrorTimers(TRUE, CTRLSWI_MATURATION_T, CTRLSWI_SH2GND_TMR);
    }
    else
    {
      // Set the DTC
      Rte_Call_DemPrj_ReportErrorStatus((uint16)Fan1_E_SC_GND, DEM_EVENT_STATUS_FAILED);
    }

    break;
    // ERR NO
  case eERR_NO:


    // Reset the DTC
    Rte_Call_DemPrj_ReportErrorStatus((uint16)Fan1_E_SC_GND, DEM_EVENT_STATUS_PASSED);

    // Reset timer
    CtrlSwi_ucErrTimeout[CTRLSWI_SH2GND_TMR] = 0U;

    // Reinit timer values
    (void)CtrlSwi_ErrorTimers(FALSE, CTRLSWI_MATURATION_T, CTRLSWI_SH2GND_TMR);
    break;

  default:

    break;
  }
}

//-----------------------------------------------------------------------------
/// \brief Handles the DTC for OpenLoad and updates the error flag
///
/// \descr  Function which sets the DTC for Sh2Gnd and updates the error flag
///
/// \param  void
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlSwi_OpenLoadHandlingFans(void)
{
  // Map the error status
  CtrlSwi_UpdateOpenLoadFlag();

  // Check the status of the error from CddSwitch
  switch (CtrlSwi_OpenLoadFlag)
  {
    // ERR YES
  case eERR_YES:

    // Check if timer started
    if (CtrlSwi_ucErrTimeout[CTRLSWI_OL_TMR] == 0u)
    {
      // Start timer
      CtrlSwi_ucErrTimeout[CTRLSWI_OL_TMR] = CtrlSwi_ErrorTimers(TRUE, CTRLSWI_MATURATION_T, CTRLSWI_OL_TMR);
    }
    else
    {
      // Set the DTC
      Rte_Call_DemPrj_ReportErrorStatus((uint16)Fan1_E_OC, DEM_EVENT_STATUS_FAILED);
    }

    break;
    // ERR NO
  case eERR_NO:

    // Reset timer
    CtrlSwi_ucErrTimeout[CTRLSWI_OL_TMR] = 0U;
    // Reinit timer values
    (void)CtrlSwi_ErrorTimers(FALSE, CTRLSWI_MATURATION_T, CTRLSWI_OL_TMR);
    // Remove the dtc
    Rte_Call_DemPrj_ReportErrorStatus((uint16)Fan1_E_OC, DEM_EVENT_STATUS_PASSED);
    break;

    // SNA
  default:

    break;
  }
}


//-----------------------------------------------------------------------------
/// \brief Handles the DTC for Short2VBAT and updates the error flag
///
/// \descr  Function which sets the DTC for Sh2Gnd and updates the error flag
///
/// \param  void
///
/// \return  void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlSwi_Sh2VbatHandlingFans(void)
{
  // Map the status of the error flag
  CtrlSwi_UpdateSh2VbatFlag();

  // Check the status of the error from CddSwitch
  switch (CtrlSwi_Sh2VbatFlag)
  {
    // ERR YES
  case eERR_YES:

    // Check if timer started
    if (CtrlSwi_ucErrTimeout[CTRLSWI_SH2VBAT_TMR] == 0u)
    {
      CtrlSwi_ucErrTimeout[CTRLSWI_SH2VBAT_TMR] = CtrlSwi_ErrorTimers(TRUE, CTRLSWI_MATURATION_T, CTRLSWI_SH2VBAT_TMR);
    }
    else
    {
      // Set the DTC
      Rte_Call_DemPrj_ReportErrorStatus((uint16)Fan1_E_SC_BAT, DEM_EVENT_STATUS_FAILED);
    }

    break;
    // ERR NO
  case eERR_NO:

    // Reset timer
    CtrlSwi_ucErrTimeout[CTRLSWI_SH2VBAT_TMR] = 0U;

    // Reinit timer values
    (void)CtrlSwi_ErrorTimers(FALSE, CTRLSWI_MATURATION_T, CTRLSWI_SH2VBAT_TMR);

    // Reset the dtc
    Rte_Call_DemPrj_ReportErrorStatus((uint16)Fan1_E_SC_BAT, DEM_EVENT_STATUS_PASSED);
    break;

    // SNA
  default:

    break;
  }
}
//-----------------------------------------------------------------------------
/// \brief  operate the output with voltage state
///
/// \descr  This function operates the corresponding HSS output with voltage state
///         of SwitchOn and RemainOn
///
/// \param  ucHssChannel     0: HSS1, 1: HSS2, 2: HSS3
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlSwi_OperateOutputWithVoltState(uint8 ucHssChannel)
{
  // Check the Target State
  if (CtrlSwi_sState.aboHssTargetState[ucHssChannel] != FALSE)
  {
    // Check the delay used for switch on
    CtrlSwi_CheckDelaySwitchOnTimer(ucHssChannel);
    CtrlSwi_CheckDelayErrorDetectionTimer(ucHssChannel);

    // Check if Sh2Gnd Active
    if (CtrlSwi_sState.aboHssShort2GNDDetected[ucHssChannel] != FALSE)
    {
      // Check the previous state with the actual state
      if (CtrlSwi_sState.aboPreTargestState[ucHssChannel] != CtrlSwi_sState.aboHssTargetState[ucHssChannel])
      {
        // set the new request
        CtrlSwi_sState.aboHssNewRequest[ucHssChannel] = TRUE;
      }
      else
      {
        // do nothing
      }
    }
    else
    {
      // do nothing
    }

    // if state OFF-->ON
    if ((CtrlSwi_sState.aboHssPreviousState[ucHssChannel] != CtrlSwi_sState.aboHssTargetState[ucHssChannel]))
    {
      // The error detection is disabled for 0.5s when the output is switched from OFF to ON
      CtrlSwi_ucDelayErrorDetectionTimer[ucHssChannel] = CFG_CTRLSWI_DELAY_ERROR_DETECTION_500ms;

      // DiagDisabled is set only for 500ms to true then it will be set to false again
      CtrlSwi_sState.aboHssStateChangedDiagDisabled[ucHssChannel] = TRUE;

      // If the request and the switch on delay was set on false
      if ((CtrlSwi_sVoltState.boSwitchOn[ucHssChannel] != FALSE) && (CtrlSwi_sState.aboHssSwitchOnDelay[ucHssChannel] == FALSE))
      {
        // If the sh2gnd error is not active
        if (CtrlSwi_sState.aboHssShort2GNDDetected[ucHssChannel] == FALSE)
        {
          // Switch on the fan
          CtrlSwi_SwitchOutput(ucHssChannel, TRUE);
        }
        else
        {
          // a new request is active
          if (CtrlSwi_sState.aboHssNewRequest[ucHssChannel] != FALSE)
          {
            // Set the new req on false
            CtrlSwi_sState.aboHssNewRequest[ucHssChannel] = FALSE;
            // Set the error status for the sh2gnd on false
            CtrlSwi_sState.aboHssShort2GNDDetected[ucHssChannel] = FALSE;
            // Switch on the FAN(s)
            CtrlSwi_SwitchOutput(ucHssChannel, TRUE);
          }
          else
          {
            //do nothing
          }
        }
      }
      else
      {
        // do nothing
      }
    }
    // if target ON --> ON
    else
    {
      // Check debounce time
      //CtrlSwi_CheckDelayErrorDetectionTimer(ucHssChannel);

      // If the actual state is set to false (actual state)
      if (CtrlSwi_sVoltState.boRemainOn[ucHssChannel] == FALSE)
      {
        // Switch of the FAN
        CtrlSwi_SwitchOutput(ucHssChannel, FALSE);
      }
      else
      {
        // If no error is detected
        if (CtrlSwi_sState.aboHssShort2GNDDetected[ucHssChannel] == FALSE)
        {
          // If short to GND is detected,  the output should be switched off.
          if ((CtrlSwi_sErrState.ucErrShortToGnd[ucHssChannel] == CTRLSWI_CFG_ERR_YES) && (CtrlSwi_sState.aboHssStateChangedDiagDisabled[ucHssChannel] == FALSE))
          {
            // Set the FAN off
            CtrlSwi_SwitchOutput(ucHssChannel, FALSE);

            // In case of RGB, do not update the actual state (avoid short to Gnd diagnostic stuck)
            // the output will be cut acording CtrlSwi_SwitchOutput(ucHssChannel, FALSE) above call
            if (ucHssChannel == RGB_SM)
            {
              CtrlSwi_sState.aboHssActualState[RGB_SM] = CtrlSwi_sState.aboHssPreviousState[RGB_SM];
            }

            // Sh2Gnd Error was detected and set to true
            CtrlSwi_sState.aboHssShort2GNDDetected[ucHssChannel] = TRUE;
            // Set retry timer
#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
            if ((ucHssChannel == FAN1) || (ucHssChannel == FAN2))
#else
            if(ucHssChannel == FAN1)
#endif
            {
              CtrlSwi_sState.aunRetryTimer[ucHssChannel] = CTRLSWI_RETRY_DEB_TIME;
              CtrlSwi_sState.aboRetryStarted[ucHssChannel] = TRUE;
              CtrlSwi_sState.aboRetryTarget[ucHssChannel] = FALSE;
            }
            else
            {
              //do nothing
            }
          }
          else
          {
            // Normal operation with no error detected
            CtrlSwi_SwitchOutput(ucHssChannel, TRUE);
          }
        }
        else
        {
          // If short to GND is detected and new request is not required.
          CtrlSwi_SwitchOutput(ucHssChannel, FALSE);
        }
      }
    }
  }
  else //CtrlSwi_sState.aboHssTargetState[ucHssChannel] == FALSE
  {
    // the req for the target ON --> OFF
    if ((CtrlSwi_sState.aboHssPreviousState[ucHssChannel] != CtrlSwi_sState.aboHssTargetState[ucHssChannel]))
    {
      // The error detection is disabled for 1s when the output is switched from ON to OFF
      CtrlSwi_ucDelayErrorDetectionTimer[ucHssChannel] = CFG_CTRLSWI_DELAY_ERROR_DETECTION_1s;

      // Set the debounce time to true to be checked
      CtrlSwi_sState.aboHssStateChangedDiagDisabled[ucHssChannel] = TRUE;
      // Set the delay switch on timer
      CtrlSwi_ucDelaySwitchOnTimer[ucHssChannel] = CtrlSwi_aucSwitchOnDelay[ucHssChannel];
      CtrlSwi_sState.aboHssSwitchOnDelay[ucHssChannel] = TRUE;
    }
    // target OFF --> OFF
    else
    {
      // Check the delay error timer
      CtrlSwi_CheckDelayErrorDetectionTimer(ucHssChannel);
      // Check the switch on err timer
      CtrlSwi_CheckDelaySwitchOnTimer(ucHssChannel);
    }
    // Set the fan on OFF
    CtrlSwi_SwitchOutput(ucHssChannel, FALSE);
  }

  // Keep the previous fan state
  CtrlSwi_sState.aboPreTargestState[ucHssChannel] = CtrlSwi_sState.aboHssTargetState[ucHssChannel];
  //PRQA S 5336 1 // program architecture and readability
}

//-----------------------------------------------------------------------------
/// \brief  set output with on/off
///
/// \descr  This function sets the corresponding HSS output with on/off
///
/// \param  ucHssChannel     0: HSS1, 1: HSS2, 2: HSS3
///         boSwitch         0: switch off, 1: switch on
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlSwi_SwitchOutput(uint8 ucHssChannel, boolean boSwitch)
{
  // Store the previous state
  CtrlSwi_sState.aboHssPreviousState[ucHssChannel] = CtrlSwi_sState.aboHssActualState[ucHssChannel];
  // Store the request for the driver
  CtrlSwi_aboCddSwiTarget[ucHssChannel] = boSwitch;
  // Store the actual state
  CtrlSwi_sState.aboHssActualState[ucHssChannel] = boSwitch;
}

//-----------------------------------------------------------------------------
/// \brief  Check if the error detection Delay timer is expired
///
/// \descr  This function handels the timer for the switch on delay
///
/// \param  ucHssChannel     0: HSS1, 1: HSS2, 2: HSS3
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlSwi_CheckDelayErrorDetectionTimer(uint8 ucHssChannel)
{
  // Check if time has passed
  if (CtrlSwi_ucDelayErrorDetectionTimer[ucHssChannel] > 0u)
  {
    // Still counting timer is decremented
    CtrlSwi_ucDelayErrorDetectionTimer[ucHssChannel]--;

    // Timer expired
    if (CtrlSwi_ucDelayErrorDetectionTimer[ucHssChannel] == 0u)
    {
      //Set the Diagnosis on off
      CtrlSwi_sState.aboHssStateChangedDiagDisabled[ucHssChannel] = FALSE;
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  Check if the Switch On Delay timer is expired
///
/// \descr  This function handels the timer for the switch on delay
///
/// \param  ucHssChannel     0: HSS1, 1: HSS2, 2: HSS3
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlSwi_CheckDelaySwitchOnTimer(uint8 ucHssChannel)
{
  // Check if time has passed
  if (CtrlSwi_ucDelaySwitchOnTimer[ucHssChannel] > 0u)
  {
    // Still counting timer is decremented
    CtrlSwi_ucDelaySwitchOnTimer[ucHssChannel]--;
    // Timer expired
    if (CtrlSwi_ucDelaySwitchOnTimer[ucHssChannel] == 0u)
    {
      //Set the Diagnosis on off
      CtrlSwi_sState.aboHssSwitchOnDelay[ucHssChannel] = FALSE;
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  diagnostic interface to switch the HSS outputs.
///
/// \descr  This function sets the corresponding HSS output with received target
///
/// \param  ucChannelNo     1: HSS1, 2: HSS2, 3: HSS3
///         ucSwitchOutput  0: switch off, 1: switch on
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start(uint8 ucChannelNo, uint8 ucSwitchOutput)
{
  uint8 ucHssChannel = 0u;

  if (ucChannelNo > 0u)
  {
    ucHssChannel = ucChannelNo - 1u;
  }
  if (ucHssChannel < CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS)
  {
    CtrlSwi_sDiagControl.teMode[ucHssChannel] = eDiagCtrl_CtrlSwi_Enabled;
    CtrlSwi_sDiagControl.ucHssOutput[ucHssChannel] = ucSwitchOutput;
    CtrlSwi_aucSwitchOnDelay[ucHssChannel] = CFG_CTRLSWI_DIAG_SWITCH_ON_DELAY_HSS;
  }
}

//-----------------------------------------------------------------------------
/// \brief  diagnostic interface to switch the HSS outputs.
///
/// \descr  This function sets the corresponding HSS output with received target
///
/// \param  ucChannelNo     1: HSS1, 2: HSS2, 3: HSS3
///         ucSwitchOutput  0: switch off, 1: switch on
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop(uint8 ucChannelNo)
{
  uint8 ucHssChannel = 0;

  if (ucChannelNo > 0u)
  {
    ucHssChannel = ucChannelNo - 1u;
  }
  if (ucHssChannel < CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS)
  {
    CtrlSwi_sDiagControl.teMode[ucHssChannel] = eDiagCtrl_CtrlSwi_Disabled;
    switch (ucHssChannel)
    {
    case HSS1:
      CtrlSwi_aucSwitchOnDelay[ucHssChannel] = CFG_CTRLSWI_SWITCH_ON_DELAY_HSS1;
      break;
    case HSS2:
      CtrlSwi_aucSwitchOnDelay[ucHssChannel] = CFG_CTRLSWI_SWITCH_ON_DELAY_HSS2;
      break;
    default: //case HSS3:
      CtrlSwi_aucSwitchOnDelay[ucHssChannel] = CFG_CTRLSWI_SWITCH_ON_DELAY_HSS3;
      break;
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief  diagnostic runnable
///
/// \descr  diagnostic runnable to control for the corresponding output with
///         received targaet
///
/// \param  ucChannelNo     1: HSS1, 2: HSS2, 3: HSS3
///         ucSwitchOutput  0: switch off, 1: switch on
///
/// \return void
//-----------------------------------------------------------------------------
void roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start(uint8 ucChannelNo, uint8 ucSwitchOutput)
{
  CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Start(ucChannelNo, ucSwitchOutput);
}

//-----------------------------------------------------------------------------
/// \brief  diagnostic runnable
///
/// \descr  diagnostic runnable to stop the takeover for the corresponding output
///
/// \param  ucChannelNo     1: HSS1, 2: HSS2, 3: HSS3
///
/// \return void
//-----------------------------------------------------------------------------
void roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop(uint8 ucChannelNo)
{
  CtrlSwi_ExtTakeoverSwitchHssOutputChannel0Stop(ucChannelNo);
}

//-----------------------------------------------------------------------------
/// \brief  deinitialize the High Side Switch driver before going to sleep
///
/// \descr  set the HSS-outputs and the SenseEnable (SEN) to LOW
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlSwi_DeInit(void)
{
  tisHssStatusError atStatusError;
  uint16 aunCddSwiTarget[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];

  for (uint8 ucIdx = 0; ucIdx < CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS; ucIdx++)
  {
    atStatusError.eStatSupported[ucIdx] = (tieSupportInfo)SUPPORT_SNA;
    atStatusError.eStatOn[ucIdx] = (tieHssState)HSS_OFF;
    atStatusError.eErrShortToGnd[ucIdx] = (tieError)CTRLSWI_CFG_ERR_SNA;
    atStatusError.eErrShortToVBat[ucIdx] = (tieError)CTRLSWI_CFG_ERR_SNA;
    atStatusError.eErrOpenLoad[ucIdx] = (tieError)CTRLSWI_CFG_ERR_SNA;
    aunCddSwiTarget[0] = 0u;
  }

  // set RTE-Port ppIoHwAbUserHssTarget0 to switch of the HSS output. - UNTIL Fan on eco it is f
  (void)Rte_Write_CtrlSwi_TgtValue_Fan1(&aunCddSwiTarget[FAN1]);
  (void)Rte_Write_CtrlSwi_TgtValue_SMRGB(&aunCddSwiTarget[RGB_SM]);
#if defined (CFG_VARIANT_FULL ) || defined(UNIT_TEST)
  (void)Rte_Write_CtrlSwi_TgtValue_Fan2(&aunCddSwiTarget[FAN2]);

#endif

  // set RTE-Port ppaseCtrlSwiStatusError0 update the actual state of the HSS output.
  (void)Rte_Write_CtrlSwi_StatusErr(&atStatusError);
}

//-----------------------------------------------------------------------------
/// \brief  Check SmRgb errors
///
/// \descr  This function calls the corresponding error detection function
///         according to the actual SM/RGB HSS3 state
///         Calling 30ms Cyclic
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlSwi_Diag_CheckSmRgbErrors(void)
{
  if (CtrlSwi_sState.aboHssStateChangedDiagDisabled[RGB_SM] == FALSE)
  {
    // Hss-output state is ON
    if (CtrlSwi_sState.aboHssActualState[RGB_SM] != FALSE)
    {
      // Short to GND diagnostic
      CtrlSwi_Diag_CheckShort2GndDuringOn(RGB_SM);

      // Alrady Vbat detected, no check for Open-Load (in this case OL will overwrite the Sh to Vbat Fault)
      if (CtrlSwi_sErrState.ucErrShortToVbat[RGB_SM] != CTRLSWI_CFG_ERR_YES)
      {
        // Open Load diagnostic
        CtrlSwi_Diag_CheckOpenloadDuringOn(RGB_SM);
      }
    }
    // Hss-output state is OFF
    else
    {
      // Short to Vbat diagnostic
      CtrlSwi_Diag_CheckShort2VbatDuringOff(RGB_SM);

      // Reset the other fault counters and status
      CtrlSwi_sErrState.ucErrShortToGnd[RGB_SM] = CTRLSWI_CFG_ERR_SNA;
      CtrlSwi_sErrState.ucErrOpenLoad[RGB_SM] = CTRLSWI_CFG_ERR_SNA;
      CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM] = 0u;
      CtrlSwi_sErrState.ucCntOpenLoad[RGB_SM] = 0u;
    }
  }
  else
  {
    CtrlSwi_sErrState.ucCntShortToVbat[RGB_SM] = 0u;
    CtrlSwi_sErrState.ucCntShortToGnd[RGB_SM] = 0u;
    CtrlSwi_sErrState.ucCntOpenLoad[RGB_SM] = 0u;
  }
}

//-----------------------------------------------------------------------------
/// \brief  Check all errors
///
/// \descr  This function calls the corresponding error detection function
///         according to the actual switch state
///         Calling 30ms Cyclic
///
/// \param  ucHssChannel         0: HSS1, 1: HSS2, 2: HSS3
///         boActualState        0: off,  1: on
///         boDiagDelayDisabled  0: not disabled,  1: disabled
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlSwi_Diag_CheckAllErrors(uint8 ucHssChannel, boolean boActualState, boolean boDiagDelayDisabled)
{
  if (boDiagDelayDisabled == FALSE)
  {
    // Hss-output state is ON
    if (boActualState != FALSE)
    {
      if (CtrlSwi_sState.aboErrOffPermanent[ucHssChannel] == FALSE)
      {
        CtrlSwi_Diag_CheckShort2GndDuringOn(ucHssChannel);
      }
      else
      {
        // The error still active
        CtrlSwi_sErrState.ucErrShortToGnd[ucHssChannel] = CTRLSWI_CFG_ERR_YES;
      }

      CtrlSwi_Diag_CheckOpenloadDuringOn(ucHssChannel);
    }
    // Hss-output state is OFF
    else
    {
      // to do if timer for delay of error detection is elapsed
      CtrlSwi_Diag_CheckShort2VbatDuringOff(ucHssChannel);

      // Check if the error status is permanent
      if (CtrlSwi_sState.aboErrOffPermanent[ucHssChannel] != FALSE)
      {
        CtrlSwi_sErrState.ucErrShortToGnd[ucHssChannel] = CTRLSWI_CFG_ERR_YES;
      }
      else
      {
        CtrlSwi_sErrState.ucErrShortToGnd[ucHssChannel] = CTRLSWI_CFG_ERR_SNA;
      }

      CtrlSwi_sErrState.ucErrOpenLoad[ucHssChannel] = CTRLSWI_CFG_ERR_SNA;
      CtrlSwi_sErrState.ucCntShortToGnd[ucHssChannel] = 0u;
      CtrlSwi_sErrState.ucCntOpenLoad[ucHssChannel] = 0u;
    }
  }
  else
  {
    CtrlSwi_sErrState.ucCntShortToVbat[ucHssChannel] = 0u;
    CtrlSwi_sErrState.ucCntShortToGnd[ucHssChannel] = 0u;
    CtrlSwi_sErrState.ucCntOpenLoad[ucHssChannel] = 0u;
  }


}

//-----------------------------------------------------------------------------
/// \brief  Check Short to Gnd error during the on-State
///
/// \descr  This function to check short to GND during on-state
///         Called by CtrlSwi_Diag_CheckAllErrors
///
/// \param  ucHssChannel         0: HSS1, 1: HSS2, 2: HSS3
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlSwi_Diag_CheckShort2GndDuringOn(uint8 ucHssChannel)
{

  // read RTE ports to get Short2GND error stauts
  if (CtrlSwi_aSwitchStatus[ucHssChannel].ucErrShort2GND == CTRLSWI_CFG_ERR_YES)
  {
    // Check if the counter has reached the time needed
    if (CtrlSwi_sErrState.ucCntShortToGnd[ucHssChannel] < CtrlSwi_aErrorDebounce[ucHssChannel])
    {
      // Update the counter
      CtrlSwi_sErrState.ucCntShortToGnd[ucHssChannel]++;
    }
    else
    {
      // Time has expired update the err state
      CtrlSwi_sErrState.ucErrShortToGnd[ucHssChannel] = CTRLSWI_CFG_ERR_YES;
      CtrlSwi_sErrState.ucErrShortToVbat[ucHssChannel] = CTRLSWI_CFG_ERR_NO;
      CtrlSwi_sErrState.ucErrOpenLoad[ucHssChannel] = CTRLSWI_CFG_ERR_NO;
      CtrlSwi_sErrState.ucCntShortToGnd[ucHssChannel] = CtrlSwi_aErrorDebounce[ucHssChannel];
    }
  }
  else if (CtrlSwi_aSwitchStatus[ucHssChannel].ucErrShort2GND == CTRLSWI_CFG_ERR_NO) // if not short to Gnd
  {
    if (CtrlSwi_sErrState.ucCntShortToGnd[ucHssChannel] > 0u)
    {
      // DEcrement the counter
      CtrlSwi_sErrState.ucCntShortToGnd[ucHssChannel]--;
    }
    else
    {
      // Time has expired and error was set to no
      CtrlSwi_sErrState.ucErrShortToGnd[ucHssChannel] = CTRLSWI_CFG_ERR_NO;
    }
  }
  else
  {
    // do nothing
  }
}

//-----------------------------------------------------------------------------
/// \brief  Check Openload error during the on-State
///
/// \descr  This function to check openload during on-state
///         Called by CtrlSwi_Diag_CheckAllErrors
///
/// \param  ucHssChannel         0: HSS1, 1: HSS2, 2: HSS3
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlSwi_Diag_CheckOpenloadDuringOn(uint8 ucHssChannel)
{
  if (CtrlSwi_aSwitchStatus[ucHssChannel].ucErrOpenLoad == CTRLSWI_CFG_ERR_YES)
  {
    // if the error short to VBAT is not detected in the previous off state
    if (CtrlSwi_sErrState.ucErrShortToVbat[ucHssChannel] != CTRLSWI_CFG_ERR_YES)
    {
      // Check if the counter has reached the time needed
      if (CtrlSwi_sErrState.ucCntOpenLoad[ucHssChannel] < CtrlSwi_aErrorDebounce[ucHssChannel])
      {
        // Update the counter
        CtrlSwi_sErrState.ucCntOpenLoad[ucHssChannel]++;
      }
      else
      {
        // Time has expired set the erro state
        CtrlSwi_sErrState.ucErrShortToGnd[ucHssChannel] = CTRLSWI_CFG_ERR_NO;
        CtrlSwi_sErrState.ucErrOpenLoad[ucHssChannel] = CTRLSWI_CFG_ERR_YES;
        CtrlSwi_sErrState.ucCntOpenLoad[ucHssChannel] = CtrlSwi_aErrorDebounce[ucHssChannel];
      }
    }
    //if the error short to VBAT is detected in the previous off state
    else
    {
      CtrlSwi_sErrState.ucErrShortToGnd[ucHssChannel] = CTRLSWI_CFG_ERR_NO;
      CtrlSwi_sErrState.ucErrOpenLoad[ucHssChannel] = CTRLSWI_CFG_ERR_NO;
    }
  }
  // if HssSense is not in the range of openload
  else if (CtrlSwi_aSwitchStatus[ucHssChannel].ucErrOpenLoad == CTRLSWI_CFG_ERR_NO)
  {
    // Time has expired?
    if (CtrlSwi_sErrState.ucCntOpenLoad[ucHssChannel] > 0u)
    {
      // Decrement the counter
      CtrlSwi_sErrState.ucCntOpenLoad[ucHssChannel]--;
    }
    else
    {
      // Set the error state time has expired
      CtrlSwi_sErrState.ucErrOpenLoad[ucHssChannel] = CTRLSWI_CFG_ERR_NO;
    }
    // Time has expired?
    if (CtrlSwi_sErrState.ucCntShortToVbat[ucHssChannel] > 0u)
    {
      // Decrement the counter
      CtrlSwi_sErrState.ucCntShortToVbat[ucHssChannel]--;
    }
    else
    {
      // Set the error state after the counter is finished
      CtrlSwi_sErrState.ucErrShortToVbat[ucHssChannel] = CTRLSWI_CFG_ERR_NO;
    }
  }
  else
  {
    // do nothing
  }
}

//-----------------------------------------------------------------------------
/// \brief  Check Short to Vbat error during the off-State
///
/// \descr  This function to check short to Vbat during on-state
///         Called by CtrlSwi_Diag_CheckAllErrors
///
/// \param  ucHssChannel         0: HSS1, 1: HSS2, 2: HSS3
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlSwi_Diag_CheckShort2VbatDuringOff(uint8 ucHssChannel)
{
  // if HssSense is in the range of short to Vbat
  if (CtrlSwi_aSwitchStatus[ucHssChannel].ucErrShort2VBAT == CTRLSWI_CFG_ERR_YES)
  {
    // Check if the counter has reached the time needed
    if (CtrlSwi_sErrState.ucCntShortToVbat[ucHssChannel] < CtrlSwi_aErrorDebounce[ucHssChannel])
    {
      // Still count
      CtrlSwi_sErrState.ucCntShortToVbat[ucHssChannel]++;
    }
    else
    {

      // Time has expired, set the error state
      CtrlSwi_sErrState.ucErrShortToGnd[ucHssChannel] = CTRLSWI_CFG_ERR_NO;
      CtrlSwi_sErrState.ucErrShortToVbat[ucHssChannel] = CTRLSWI_CFG_ERR_YES;
      CtrlSwi_sErrState.ucErrOpenLoad[ucHssChannel] = CTRLSWI_CFG_ERR_NO;
      CtrlSwi_sErrState.ucCntShortToVbat[ucHssChannel] = CtrlSwi_aErrorDebounce[ucHssChannel];
    }
  }
  // if HssSense is not in the range of short to Vbat
  else if (CtrlSwi_aSwitchStatus[ucHssChannel].ucErrShort2VBAT == CTRLSWI_CFG_ERR_NO)
  {
    // Check if counter has expired
    if (CtrlSwi_sErrState.ucCntShortToVbat[ucHssChannel] > 0u)
    {
      // Still counting
      CtrlSwi_sErrState.ucCntShortToVbat[ucHssChannel]--;
    }
    else
    {
      // Time expired, set error state
      CtrlSwi_sErrState.ucErrShortToVbat[ucHssChannel] = CTRLSWI_CFG_ERR_NO;
    }
  }
  else
  {
    // do nothing
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlSwi_Get_ETAT_FEE
///
/// \descr  this function returns status of ETAT_FEE
///
/// \param  void
///
/// \return eReturnValue - stores the state of the cranking profile
//-----------------------------------------------------------------------------
STATIC_AL teRte_EtatFee CtrlSwi_Get_ETAT_FEE(void)
{
  tsRte_SigPrep_ElecSupState  sElecSupState = { 0 };
  teRte_EtatFee               eReturnValue;
  sElecSupState.eElectrSupplyState = eEtatFee_1_1;

  sElecSupState.eSigQty = SIG_INIT; //Initialise the structure

  (void)Rte_Read_SigPrep_ElecSupState(&sElecSupState);

  if (sElecSupState.eSigQty == SIG_VALID)
  {
    eReturnValue = sElecSupState.eElectrSupplyState;
  }
  return eReturnValue;
}
//-----------------------------------------------------------------------------
/// \brief  Read coding data
///
/// \descr  Read coding data and store results in local variables
///
/// \param  tParaFct0_Cmd eCmd, tNvmPara_CodingArea*  pData
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlSwi_ParaFct0(tParaFct0_Cmd eCmd, tNvmPara_CodingArea*  pData)
{
  // Check if the coding is valid
  if (eCmd == eParaFct0_CodingDataValid)
  {
    // Map the FAN1 block
    CtrlSwi_sCodingParam = pData->Fan1;
    CtrlSwi_sCodingLedParam = pData->Led1;
    CtrlSwi_boCodingValid = TRUE;
    // Map the values needed for debounce
    CtrlSwi_ucDebounce9V = CtrlSwi_sCodingParam.FAN1_SUPPLY.ucFAN1_SUPPLY_ON_T_MIN;
    CtrlSwi_ucDebounce18V = CtrlSwi_sCodingParam.FAN1_SUPPLY.ucFAN1_SUPPLY_OFF_T_MAX;
  }
  else
  {
    // Set coding invalid
    CtrlSwi_boCodingValid = FALSE;
  }

}

//-----------------------------------------------------------------------------
/// \brief  CtrlSwi_HandleMaturationTime
///
/// \descr  This function return TimeOut = TRUE based on sTimersCfg Configurations
///
/// \param   *sTimersCfg, scTimerSel
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlSwi_HandleMaturationTime(tsCtrlSwi_TimerCfg *sTimersCfg, const sint8 scTimerSel)
{
  // Input request (start timer or reset)
  if (sTimersCfg[scTimerSel].boReq_Input != FALSE)
  {
    // Start Timer
    if (sTimersCfg[scTimerSel].boStartStopTimer == FALSE)
    {
      sTimersCfg[scTimerSel].ulCommandStart = UTILTIME_TIMER_START(UTILTIME_MSEC(sTimersCfg[scTimerSel].ulTimeMs_Input));
      sTimersCfg[scTimerSel].boStartStopTimer = TRUE;
    }
  }
  else
  {
    // Reset timer and reinit all timers values
    sTimersCfg[scTimerSel].boTimeOut = FALSE;
    sTimersCfg[scTimerSel].boStartStopTimer = FALSE;
    sTimersCfg[scTimerSel].ulCommandStart = 0U;
  }

  // Timer still running ?
  if (sTimersCfg[scTimerSel].boStartStopTimer != FALSE)
  {
    // Let it run
    sTimersCfg[scTimerSel].boTimeOut = UTILTIME_TIMER_TIMEOUT(sTimersCfg[scTimerSel].ulCommandStart);
  }

  return sTimersCfg[scTimerSel].boTimeOut;
}


//-----------------------------------------------------------------------------
/// \brief  CtrlSwi_ErrorTimers
///
/// \descr  Checks the timer status: start, running or reset the timer init values
///
/// \param  boReqInput, ulTimeMs, scTiTimerSel
///
/// \return uint8
//-----------------------------------------------------------------------------
STATIC_AL uint8 CtrlSwi_ErrorTimers(const boolean boReqInput, const TIMER ulTimeMs, const sint8 scTiTimerSel)
{
  uint8 ucTimersDelayStatus = 0xFFu;
  if (scTiTimerSel < (sint8)CTRLSWI_NO_OF_TMR)
  {
    CtrlSwi_sTimerCfg[scTiTimerSel].ulTimeMs_Input = ulTimeMs;
    CtrlSwi_sTimerCfg[scTiTimerSel].boReq_Input = boReqInput;
    ucTimersDelayStatus = CtrlSwi_HandleMaturationTime(CtrlSwi_sTimerCfg, scTiTimerSel);
  }
  return ucTimersDelayStatus;
}


#if defined (SAMPLE_FULL) || defined (UNIT_TEST)
STATIC_AL void CtrlSwi_HandleLSSErrors(void)
{
  if (CtrlSwi_aSwitchStatus[CTRLSWI_LSS_CH_NR].ucErrShort2GND != FALSE)
  {
    Rte_Call_DemPrj_ReportErrorStatus((uint16)OUTFCT_GPIO_TI_SCGND, DEM_EVENT_STATUS_FAILED);
  }
  else
  {
    Rte_Call_DemPrj_ReportErrorStatus((uint16)OUTFCT_GPIO_TI_SCGND, DEM_EVENT_STATUS_PASSED);
  }

  if (CtrlSwi_aSwitchStatus[CTRLSWI_LSS_CH_NR].ucErrShort2VBAT != FALSE)
  {
    Rte_Call_DemPrj_ReportErrorStatus((uint16)OUTFCT_GPIO_TI_SC_BAT, DEM_EVENT_STATUS_FAILED);
  }
  else
  {
    Rte_Call_DemPrj_ReportErrorStatus((uint16)OUTFCT_GPIO_TI_SC_BAT, DEM_EVENT_STATUS_PASSED);
  }
}
#endif

// EOF
