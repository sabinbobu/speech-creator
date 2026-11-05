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
/// \file   SysMonCheck.c
///
/// \brief  
///
/// \descr  Entry point for SysMonCheck runnable
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <SysMonCheck.h>
#include <SysMonCheck_Data.h>
#include <SysMonCheck_InternalCom.h>
#include <SysMonCheck_LedCtrl.h>
#include <SysMonCheck_LedDiag.h>
#include <SysMon_Types.h>
#include <SysMonRx_ASIL.h>
#include <Crc.h>
#include <SysMonCheck_Rte.h>
#include <SysMonRx_Callbacks.h>

#ifndef UNIT_TEST
#include <EcuM.h>
#include <LPTMR.h>
#endif

//-----------------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------------
#define SYSMONCHECK_DELAY_TIME_LB_MIN_BRIGHTNESS      (uint16)  70u // required 70ms for Low Beam
#define SYSMONCHECK_DELAY_TIME_TI_MIN_BRIGHTNESS      (uint16) 100u // required 100ms for Turn Indicator

#ifndef UNIT_TEST
// MPU recovery strategy
#define SYSMONCHECK_1MINUTE                                   6000u // 1 minute = (60s * 1000ms)/ 10ms_cycle_time
#else 
#define SYSMONCHECK_1MINUTE                                   60 // 1 minute = (60s * 1000ms)/ 10ms_cycle_time
#endif
#define SYSMONCHECK_INVALID_CONFIG 0xFFU //invalid configuration for Timers
#define SYSMONCHECK_TIMEOUT_NOT_OCCURED 0x00U //no timeout
#define SYSMONCHECK_IS_TIMEOUT 0x01U //timeout

#define SYSMONCHECK_NUMBER_OF_TI_TIMERS 2 //number of timers used in this file for Turn Indicator

#define SYSMONCHECK_DELAY_TI_NOT_REQUESTED 0
#define SYSMONCHECK_TI_FAULT_DETECTION 1

#define SYSMONCHECK_TI_FAULT_DETECTION_TIME_MS     340UL //(fault detection)

#ifdef UNIT_TEST
/// \brief Maximum value of \ref uint16_t type.
#define UINT16_MAX                65535u
uint16 STATIC_AL SysMon_UT_UIN16MAX;
#endif // UNIT_TEST

//-----------------------------------------------------------------------------
// local types
//-----------------------------------------------------------------------------
typedef struct
{
  //input
  boolean boReq_Input;
  TIMER ulTimeMs_Input;
  //internal
  TIMER ulCommandStart;
  boolean boStartStopTimer;
  boolean boTimeOut;
}tsSysMonCheck_TiTimerCfg;

//-----------------------------------------------------------------------------
// Local globals
//-----------------------------------------------------------------------------
STATIC_AL boolean  SysMonCheck_boInitialized = FALSE;

STATIC_AL tsRte_TgtLedSig0            SysMonCheck_aLedTarget[SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS];      // target info from CtrlLed
STATIC_AL tsRte_TgtLedSig0            SysMonCheck_aLedTargetTemp[SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS];  // temporary target info from CtrlLed
STATIC_AL tsRte_TgtLedSig0_ASIL       SysMonCheck_LedTarget_ASIL;                                         // Structure to be sent to CddLed
STATIC_AL tsRte_LedChFbit             SysMonCheck_LedChFbit;                                             // Structure of F-bits received from CtrlLed

STATIC_AL boolean                     SysMonCheck_boCrc32OverCoding = FALSE;
STATIC_AL tsSysMonCheck_FUSA_LB_ASIL  SysMonCheck_FUSA_LB_ASIL = {FALSE, SYSMON_LOWBEAM_OFF,       0u, FALSE};
STATIC_AL tsSysMonCheck_FUSA_TI_ASIL  SysMonCheck_FUSA_TI_ASIL = {SYSMON_TURNINDICATOR_OFF,        0u, FALSE};

// Diag feedback for DIAG_TI and DIAG_LB
STATIC_AL boolean                SysMonCheck_boCodingFailureDiagLowBeam       = FALSE;
STATIC_AL boolean                SysMonCheck_boCodingFailureDiagTurnIndicator = FALSE;
STATIC_AL volatile uint32        SysMonCheck_ulTimerFailureCnt                = 0u;
STATIC_AL boolean                SysMonCheck_boTurnIndicatorDiagStatus = FALSE;
STATIC_AL uint16                 SysMonCheck_unDELAY_TI_NOT_REQUESTED         = 0u;

STATIC_AL tSysMon_FuSaChannelsStatusReaction SysMonCheck_sFuSaChannelsStatusReaction;
STATIC_AL boolean				 SysMonCheck_boTICommandValue = FALSE;

// Internal Communication Errors
STATIC_AL tsRte_TgtLedSig0_FaultStatus_ASIL SysMonCheck_sTgtLed_FaultStatus_ASIL;

STATIC_AL tsSysMonCheck_TiTimerCfg SysMonCheck_sTiTimerCfg[SYSMONCHECK_NUMBER_OF_TI_TIMERS];
//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------
STATIC_AL void SysMonCheck_ReadRTE(void);
STATIC_AL void SysMonCheck_WriteRTE(void);
STATIC_AL void SysMonCheck_Cycle10ms_HandleLowBeamAndTurnIndicator(void);
STATIC_AL void SysMonCheck_Cycle10ms_HandleTurnIndicatorAndLowBeamDiagFeedback(void);
STATIC_AL void SysMonCheck_Cycle10ms_HandleTurnIndicatorFuSaBehaviour(boolean boTiCmd);
STATIC_AL void SysMonCheck_CheckMinPWMandCurrent(uint8 ucChannelIdx);
STATIC_AL void SysMonCheck_Set_CodingFailureDiagLowBeamStatus(boolean boDiagLbStatus);
STATIC_AL void SysMonCheck_Set_CodingFailureDiagTurnIndicatorStatus(boolean boDiagTiStatus);
STATIC_AL void SysMonCheck_Ti_DiagWindow(void);
STATIC_AL void SysMonCheck_TurnOffChannel(uint8 ucChannelIdx);
STATIC_AL void SysMonCheck_ResetLbStatusReaction(void);
STATIC_AL void SysMonCheck_ResetTiStatusReaction(void);
STATIC_AL void SysMonCheck_CodingFailureSetDiag(void);
STATIC_AL void SysMonCheck_EmergModeMinimumBrightnessCheck(void);
STATIC_AL void SysMonCheck_VerifyTiNonFuSaActivation(void);
STATIC_AL boolean SysMonCheck_TiDelayStatus(tsSysMonCheck_TiTimerCfg *sTiCfg, const sint8 scTiTimerSel);
STATIC_AL uint8 SysMonCheck_CtrlTiDelayStatus(const boolean boReqInput, const TIMER ulTimeMs, const sint8 scTiTimerSel);
//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------

/// ---------------------------------------------------------------------------
/// \func     SysMonCheck_Init
///
/// \brief    Init function of SysMonCheck
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void SysMonCheck_Init(void)
{
  // Coding validity check
  CONST_AL boolean boCodingValidity = SysMonCheck_Data_CodingDataValidation();

  // Check Coding Validity and load coding parameter for DELAY_TI_NOT_REQUESTED
  SysMonCheck_unDELAY_TI_NOT_REQUESTED = SysMonCheck_Data_CheckAndSetCodingData(boCodingValidity);

  // Reset Internal Communication Error Status
  SysMonCheck_InternalCom_Init();

  SysMonCheck_LedCtrl_Init((CONST_AL tsRte_TgtLedSig0*) &SysMonCheck_aLedTarget[0u], &SysMonCheck_LedTarget_ASIL);

  // Reset LED errors
  SysMonCheck_LedDiag_Init();

  // Reset Channel Reaction for TI and LB
  SysMonCheck_ResetLbStatusReaction();
  SysMonCheck_ResetTiStatusReaction();

  // Initialize temporary LED pwm and current holder
  for (uint8 ucIdx = 0u; ucIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS; ucIdx++)
  {
    SysMonCheck_aLedTargetTemp[ucIdx].unCurrent   = SYSMON_ZERO_VALUE;
    SysMonCheck_aLedTargetTemp[ucIdx].unDutyCycle = SYSMON_ZERO_VALUE;

    // Reset F-bit array
    SysMonCheck_LedChFbit.aboLedChFbit[ucIdx]    = FALSE;
  }

  SysMonCheck_boInitialized = TRUE;
}


/// ---------------------------------------------------------------------------
/// \func     SysMonCheck_Cycle0
///
/// \brief    Cyclic function of SysMonCheck
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void SysMonCheck_Cycle0(void)
{
  STATIC_UT(uint16, SysMonCheck_unMpuTest_1minute, 0U);
  boolean                           boCodingDataStatus = FALSE;
  boolean                           boAreFuSaParam_Invalid = FALSE;
  tSysMonCheck_Data_FuSaParamValid  eAreFuSaParamValid = SysMonCheck_Data_FuSaParamUnknown;

  // If configuration is lost or timer is not in free runing [timer used for systick]
  // Safety mechanism to avoid timer mallfunction
  if (LPTMR_Check_Config() != FALSE)
  {
    // Privilege switch in order to be able to update the LPTMR lost configuration
    EcuM_McuPrivilegeSwitch(1u);
    // Restore the configuration and start the timer again
    LPTMR_INIT(&LPTMR_Config);
    // Restore Handler mode (protection)
    EcuM_McuPrivilegeSwitch(0u);
    SysMonCheck_ulTimerFailureCnt++;
  }

  // MPU recovery strategy
  if (SysMonCheck_unMpuTest_1minute < SYSMONCHECK_1MINUTE)
  {
      // wait one minute
      SysMonCheck_unMpuTest_1minute++;
  }
  else
  {
      if (SysMonCheck_unMpuTest_1minute != (uint16)UINT16_MAX)
      {
          // after one minute passed, check the MPU Error Counter
          // use SysMonCheck_unMpuTest_1minute as flag to perform the check only once
          uint32 ulMpuErrorCounter;
#ifndef UNIT_TEST
          SysMonCheck_unMpuTest_1minute = UINT16_MAX;
#else 
          SysMonCheck_unMpuTest_1minute = SysMon_UT_UIN16MAX;
#endif
          (void)Rte_Read_MPU_ErrorCounter(&ulMpuErrorCounter);
          if (ulMpuErrorCounter == 0u)
          {
              // no errors detected, set DTC to pass
              Rte_Call_DemPrj_ReportErrorStatus((uint16)MPU_Error, DEM_EVENT_STATUS_PASSED);
          }
          else
          {
              // do nothing, the MPU Error is active. DTC was set to FAILED in BusFault_Handler
          }
      }
  }

  if (SysMonCheck_boInitialized != FALSE)
  {
    // Read RTE ports from CtrlLed
    SysMonCheck_ReadRTE();

    // Get FuSa coding parameters and their validity
    boCodingDataStatus = SysMonCheck_Data_CodingDataValidation();

    // Set the validity status of the coding parameters
    SysMonCheck_Data_SetCodingDataSatus(boCodingDataStatus);

    // Verify Internal Communication Error status
    SysMonCheck_InternalCom_Cycle();

    // Verify target info coming from CtrlLed and going to CddLed
    SysMonCheck_LedCtrl_Cycle();

    // Check if Coding Valid
    if (boCodingDataStatus != FALSE)
    {
      eAreFuSaParamValid = SysMonCheck_Data_AreFuSaParamValid();
      boAreFuSaParam_Invalid = SysMonCheck_Data_AreFuSaParam_Invalid();

      if ((eAreFuSaParamValid == SysMonCheck_Data_FuSaParamValid) || (boAreFuSaParam_Invalid != FALSE))
      {
        SysMonCheck_Cycle10ms_HandleLowBeamAndTurnIndicator();
      }

      // Check if there was a parameter problem at StartUp and set DIAG LB or TI to NOK in case of light request
      SysMonCheck_Cycle10ms_HandleTurnIndicatorAndLowBeamDiagFeedback();

      // Check integrity of FuSa coding parameters
      SysMonCheck_Data_Cycle10ms_FuSaMonitoring();

      // Perform error detection for Light sources
      SysMonCheck_LedDiag_Cycle();

      // Write RTE port for CddLed
      SysMonCheck_WriteRTE();
    }
    else
    {
      // Set DIAG_TI and DIAG_LB to NOK in case of Coding Failure
      SysMonCheck_CodingFailureSetDiag();
    }
  }
  else
  {
    // do nothing because SysMonCheck is not initialized
  }
} // PRQA S 5324 1 // Software Architecture


/// ---------------------------------------------------------------------------
/// \func     SysMonCheck_ReadRTE
///
/// \brief    Function to Read RTE ports from other modules.(CtrlLed)
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
STATIC_AL void SysMonCheck_ReadRTE(void)
{
  tsRte_TgtLedSig0_FaultStatus_ASIL  sTgtLed_FaultStatus;
  boolean                            boIsComErrActive = FALSE;

  // Read F-bit array from CtrlLed
  (void)Rte_Read_CtrlLed_LedChFbit(&SysMonCheck_LedChFbit);

  // Read target values from CtrlLed
  // PRQA S 310 1 // Software Architecture
  (void)Rte_Read_Cpm_TgtLedSig_sVal((tsRte_TgtLedSig0Arr*)&SysMonCheck_aLedTargetTemp[0u]);

  boIsComErrActive = SysMonCheck_InternalCom_IsComErrActive();

  if (boIsComErrActive == FALSE)
  {
    // pass the new values
    for (uint8 ucIdx = 0u; ucIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS; ucIdx++)
    {
      SysMonCheck_aLedTarget[ucIdx].unCurrent   = SysMonCheck_aLedTargetTemp[ucIdx].unCurrent;
      SysMonCheck_aLedTarget[ucIdx].unDutyCycle = SysMonCheck_aLedTargetTemp[ucIdx].unDutyCycle;
    }
  }
  else
  {
    // do not pass new values because we have CRC8 Rte errors
  }


  // Read Target Fault Status from CddLed
  (void)Rte_Read_CddLed_TgtLed_FaultStatus_ASIL(&sTgtLed_FaultStatus);

  // Check CRC8 of Internal Communication Rte port
  if (SysMonCheck_InternalCom_TgtLed_FaultStatus_ASIL_CheckCrc(&sTgtLed_FaultStatus) != FALSE)
  {
    // Data can be used by SysMon because the CRC matched with the one sent from CddLed
    SysMonCheck_sTgtLed_FaultStatus_ASIL = sTgtLed_FaultStatus;
  }
  else
  {
    // nothing to do, last vallid data is still used
  }
}


/// ---------------------------------------------------------------------------
/// \func     SysMonCheck_WriteRTE
///
/// \brief    Function to Write RTE ports for other modules.(CddLed)
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
STATIC_AL void SysMonCheck_WriteRTE(void)
{
  uint8   ucCrc        = 0u;
  uint32  ulSizeOfData = 0u;

  // Calculate Crc 8 bits 0x2F (x8 + x5 +x3 + x2 + x +1) to ASIL relevant RTE messages
  ulSizeOfData = sizeof(tsRte_TgtLedSig0) * CFG_LED_CHANNELS_NR;

  // PRQA S 310 1 // Software Architecture , intended behaviour
  ucCrc = Crc_CalculateCRC8H2F((const uint8*)&SysMonCheck_LedTarget_ASIL.asTgtVal[0u].unCurrent, ulSizeOfData, CRC_SEED_INIT_CRC8H2F_VAL);
  SysMonCheck_LedTarget_ASIL.ucCrc = ucCrc;

  (void)Rte_Write_SysMon_TgtLedSig_sVal(&SysMonCheck_LedTarget_ASIL);
}


/// ---------------------------------------------------------------------------
/// \func     SysMonCheck_TurnOffFusaChannels
///
/// \brief    Function to turn off the FuSa channels
///
/// \param    SysMonCheck_Data_tLFName - Channel type
///
/// \return   none
///
/// ---------------------------------------------------------------------------
void SysMonCheck_TurnOffFusaChannels(SysMonCheck_Data_tLFName eLEDChannelParamName)
{
  tSysMonCheck_Data_LedChParam* pLedChPram = SysMonCheck_Data_GetaLEDChParamPtr();

  for (uint8 ucChannelIdx = 0u; ucChannelIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS; ucChannelIdx++)
  {
    if (eLEDChannelParamName == pLedChPram[ucChannelIdx].eName)
    {
      // Removed after allignment with CABA Ionut
      // SysMonCheck_LedTarget_ASIL.asTgtVal[ucChannelIdx].unCurrent   = SYSMON_ZERO_VALUE;
      // SysMonCheck_aLedTarget[ucChannelIdx].unCurrent                = SYSMON_ZERO_VALUE;
      SysMonCheck_LedTarget_ASIL.asTgtVal[ucChannelIdx].unDutyCycle = SYSMON_ZERO_VALUE;
      SysMonCheck_aLedTarget[ucChannelIdx].unDutyCycle              = SYSMON_ZERO_VALUE;
    }
    else
    {
      // nothing to do for this channel
    }
  }
}


/// ---------------------------------------------------------------------------
/// \func     SysMonCheck_TurnOffChannel
///
/// \brief    Function to turn off a certain channel
///
/// \param    ucChannelIdx - Channel index
///
/// \return   none
///
/// ---------------------------------------------------------------------------
STATIC_AL void SysMonCheck_TurnOffChannel(uint8 ucChannelIdx)
{
  if (ucChannelIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS)
  {
    // Removed after allignment with CABA Ionut
    // SysMonCheck_LedTarget_ASIL.asTgtVal[ucChannelIdx].unCurrent   = SYSMON_ZERO_VALUE;
    // SysMonCheck_aLedTarget[ucChannelIdx].unCurrent                = SYSMON_ZERO_VALUE;
    SysMonCheck_LedTarget_ASIL.asTgtVal[ucChannelIdx].unDutyCycle = SYSMON_ZERO_VALUE;
    SysMonCheck_aLedTarget[ucChannelIdx].unDutyCycle              = SYSMON_ZERO_VALUE;
  }
  else
  {
    // nothing to do, invalid channel index
  }
}


/// ---------------------------------------------------------------------------
/// \func     SysMonCheck_Cycle10ms_HandleLowBeamAndTurnIndicator
///
/// \brief    Handle Low Beam and Turn Indicator requests
///
/// \param    void
///
/// \return   void
///
/// ---------------------------------------------------------------------------
STATIC_AL void SysMonCheck_Cycle10ms_HandleLowBeamAndTurnIndicator(void)
{
  SysMon_EnumLowBeamState         eSysMonCheck_LowBeamState        = SysMon_LowBeam_SNA_State;
  SysMon_EnumTurnIndicatorState   eSysMonCheck_TurnIndicatorState  = SysMon_TurnIndicator_Invalid_State;
  tSysMonCheck_Data_LedChParam*   pLedChPram = SysMonCheck_Data_GetaLEDChParamPtr();
  uint8                           ucFUSA_LB_FS_BEHAVIOUR_ASIL = SysMonCheck_Data_Get_ucFUSA_LB_FS_BEHAVIOUR_ASIL();
  uint8                           ucLowBeamRequest            = 0u;
  uint8                           ucTurnIndicatorRequest      = 0u;
  boolean                         boCrc32RamFailure           = FALSE;
  boolean                         boIsCodingDataValid         = FALSE;
  boolean                         boAreFuSaParam_Invalid      = FALSE;
  boolean                         boIsTurnIndEnabled          = FALSE;
  boolean                         boIsComErrActive            = FALSE;
  boolean                         boIsLowBeamEnabled          = FALSE;
  tSysMonCheck_Data_FuSaParamValid eAreFuSaParamValid    = SysMonCheck_Data_FuSaParamUnknown;

  boolean                         boIsLightSourceErrorFreeLb;
  boolean                         boIsLightSourceSpiErrorFreeLb;
  boolean                         boIsLightSourceErrorFreeTi;
  boolean                         boIsLightSourceSpiErrorFreeTi;

  // Read voltage ranges from SysVolt
  uint8                           ucVoltageRange = SYSMONCHECK_RTE_RE_GET_VOLTAGE_RANGE

  // Get Low Beam request and State value
  eSysMonCheck_LowBeamState   = SysMonRx_ASIL_GetLowBeamState();
  ucLowBeamRequest            = SysMonRx_ASIL_GetLowBeamValue();
  boIsComErrActive            = SysMonCheck_InternalCom_IsComErrActive();

  // Check OFF -> ON transition for Low Beam
  if (ucLowBeamRequest == SYSMON_LOWBEAM_ON)
  {
    if (SysMonCheck_FUSA_LB_ASIL.ucLowBeamCmd == SYSMON_LOWBEAM_OFF)
    {
      // Transition from OFF to ON
      SysMonCheck_FUSA_LB_ASIL.ucLowBeamCmd               = SYSMON_LOWBEAM_ON; 
      SysMonCheck_FUSA_LB_ASIL.startDelayTimerMonitor_MS  = TimerStart(UTILTIME_MSEC(SYSMONCHECK_DELAY_TIME_LB_MIN_BRIGHTNESS));
    }
    else
    {
      // nothing to do
    }
  }
  else
  {
    SysMonCheck_FUSA_LB_ASIL.ucLowBeamCmd = SYSMON_LOWBEAM_OFF;
  }

  SysMonCheck_FUSA_LB_ASIL.bostartDelayTimerMonitor_MS = TimerTimeout(SysMonCheck_FUSA_LB_ASIL.startDelayTimerMonitor_MS);

  // Minimal brightness check for low beam
  if ((SysMon_LowBeam_Valid_State == eSysMonCheck_LowBeamState) && (boIsComErrActive == FALSE) && (SysMonCheck_FUSA_LB_ASIL.ucLowBeamCmd == SYSMON_LOWBEAM_ON) && (SysMonCheck_FUSA_LB_ASIL.bostartDelayTimerMonitor_MS == TRUE))
  {
    // CRC32 ROM is good and coding is Valid
    boIsCodingDataValid    = SysMonCheck_Data_IsCodingDataValid();
    boAreFuSaParam_Invalid = SysMonCheck_Data_AreFuSaParam_Invalid();

    if ((boIsCodingDataValid != FALSE) && (boAreFuSaParam_Invalid == FALSE))
    {
      for (uint8 ucIdx = 0u; ucIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS; ucIdx++)
      {
        if (SysMonCheck_Data_eLF_LB_FuSa == pLedChPram[ucIdx].eName)
        {
          // Get electrical status of LED channel
          boIsLightSourceErrorFreeLb = SysMonCheck_LedDiag_IsLightSourceErrorFree(ucIdx);
          // Get Spi error status of LED channel
          boIsLightSourceSpiErrorFreeLb = SysMonCheck_LedDiag_IsLightSourceSpiErrorFree(ucIdx);

          if ((((boIsLightSourceErrorFreeLb != FALSE) && (SysMonCheck_FUSA_LB_ASIL.TurnAll_LB_FuSa_OFF == FALSE)) || 
              (boIsLightSourceSpiErrorFreeLb == FALSE)) &&
              ((ucFUSA_LB_FS_BEHAVIOUR_ASIL != 1u) || (SysMonCheck_LedChFbit.aboLedChFbit[ucIdx] != TRUE)))
          {
            //-- do not touch other channels
            SysMonCheck_CheckMinPWMandCurrent(ucIdx);
          }
          else
          {
            // If FUSA LB BEHAVIOUR is 1 , Turn OFF all LB FuSa channels
            SysMonCheck_FUSA_LB_ASIL.TurnAll_LB_FuSa_OFF = (ucFUSA_LB_FS_BEHAVIOUR_ASIL == 1u) ? TRUE : FALSE;
            // Turn OFF this LB FuSa channel
            SysMonCheck_TurnOffChannel(ucIdx);
            // Retain Channel Status Reaction
            SysMonCheck_sFuSaChannelsStatusReaction.boLb_FuSa_Idx[ucIdx] = TRUE;
          }
        }
        else
        {
          // nothing to do
        }
      }
    }
    else
    {
      // nothing to do
    }
  }
  else
  {
    // Reset for next low beam on request cycle
    SysMonCheck_FUSA_LB_ASIL.TurnAll_LB_FuSa_OFF = FALSE;
    // Reset the Status Reactions for Low Beam
    SysMonCheck_ResetLbStatusReaction();
  }

  // Check minimum brightness for low beam OR force OFF low beam in case of Emergency Operation Mode
  SysMonCheck_EmergModeMinimumBrightnessCheck();

  // Get Turn Indicator request and State value
  eSysMonCheck_TurnIndicatorState = SysMonRx_ASIL_GetTurnIndicatorState();
  ucTurnIndicatorRequest          = SysMonRx_ASIL_GetTurnIndicatorValue();

  // Check OFF -> ON transition for Turn Indicator
  if (ucTurnIndicatorRequest == SYSMON_TURNINDICATOR_ON)
  {
    if (SysMonCheck_FUSA_TI_ASIL.ucTurnIndicatorCmd == SYSMON_TURNINDICATOR_OFF)
    {
      // Transition from OFF to ON
      SysMonCheck_FUSA_TI_ASIL.ucTurnIndicatorCmd        = SYSMON_TURNINDICATOR_ON;
      SysMonCheck_FUSA_TI_ASIL.startDelayTimerMonitor_MS = TimerStart(UTILTIME_MSEC(SYSMONCHECK_DELAY_TIME_TI_MIN_BRIGHTNESS));
    }
    else
    {
      // nothing to do
    }
  }
  else
  {
    SysMonCheck_FUSA_TI_ASIL.ucTurnIndicatorCmd = SYSMON_TURNINDICATOR_OFF;

    // Check Turn Indicator in case of Non FuSa activation (Autonomous Mode or Animations)
    SysMonCheck_VerifyTiNonFuSaActivation();
  }

  SysMonCheck_FUSA_TI_ASIL.bostartDelayTimerMonitor_MS = TimerTimeout(SysMonCheck_FUSA_TI_ASIL.startDelayTimerMonitor_MS);

  // Minimal brightness check for Turn Indicator
  if ((SysMon_TurnIndicator_Valid_State == eSysMonCheck_TurnIndicatorState) && (SysMonCheck_FUSA_TI_ASIL.ucTurnIndicatorCmd == SYSMON_TURNINDICATOR_ON) && (SysMonCheck_FUSA_TI_ASIL.bostartDelayTimerMonitor_MS == TRUE))
  {
    // CRC32 ROM is good and coding is Valid
    boIsCodingDataValid    = SysMonCheck_Data_IsCodingDataValid();
    boAreFuSaParam_Invalid = SysMonCheck_Data_AreFuSaParam_Invalid();

    if ((boIsCodingDataValid != FALSE) && (boAreFuSaParam_Invalid == FALSE))
    {
      for (uint8 ucIdx = 0u; ucIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS; ucIdx++)
      {
        
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
        if ((SysMonCheck_Data_eLF_TI      == pLedChPram[ucIdx].eName) || 
            (SysMonCheck_Data_eLF_TI_SCRL == pLedChPram[ucIdx].eName))
#elif defined (CFG_VARIANT_ECO)
        if (SysMonCheck_Data_eLF_TI == pLedChPram[ucIdx].eName)
#endif // CFG_VARIANT_FULL
        {
          //-- do not touch other channels
          SysMonCheck_CheckMinPWMandCurrent(ucIdx);
        }
        else
        {
          // nothing to do
        }
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


  if (FALSE == SysMonCheck_Data_IsCodingDataValid())
  {
    if (SysMonCheck_Data_AreFuSaParamValid() == SysMonCheck_Data_FuSaParamValid)
    {
      SysMonCheck_TurnOffFusaChannels(SysMonCheck_Data_eLF_TI);
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
      SysMonCheck_TurnOffFusaChannels(SysMonCheck_Data_eLF_TI_SCRL);
#endif // CFG_VARIANT_FULL
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

  // If CRC32 ROM is corrupted, pass all values
  if (FALSE != SysMonCheck_Data_AreFuSaParam_Invalid())
  {
    for (uint8 ucIdx = 0u; ucIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS; ucIdx++)
    {
      SysMonCheck_LedTarget_ASIL.asTgtVal[ucIdx].unCurrent    = SysMonCheck_aLedTarget[ucIdx].unCurrent;
      SysMonCheck_LedTarget_ASIL.asTgtVal[ucIdx].unDutyCycle  = SysMonCheck_aLedTarget[ucIdx].unDutyCycle;
    }
  }
  else
  {
    // nothing to do
  }

  eAreFuSaParamValid     = SysMonCheck_Data_AreFuSaParamValid();
  boIsTurnIndEnabled     = SysMonCheck_Data_Get_IsTurnIndEnabled();
  boAreFuSaParam_Invalid = SysMonCheck_Data_AreFuSaParam_Invalid();
  boIsComErrActive       = SysMonCheck_InternalCom_IsComErrActive();
  // Get CRC32 over RAM Mirror failure status
  boCrc32RamFailure      = SysMonCheck_Data_Get_Crc32RamFailure();

  // Turn OFF Turn Indicator in case of errors or undervoltage
  if (((boIsTurnIndEnabled == FALSE) && (eAreFuSaParamValid == SysMonCheck_Data_FuSaParamValid)) ||
      (boCrc32RamFailure != FALSE) || 
      (boAreFuSaParam_Invalid != FALSE) ||
      (boIsComErrActive != FALSE) ||
      (ucVoltageRange == SYSMON_LOW2_VOLT))
  {
    SysMonCheck_TurnOffFusaChannels(SysMonCheck_Data_eLF_TI);
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
    SysMonCheck_TurnOffFusaChannels(SysMonCheck_Data_eLF_TI_SCRL);
#endif // CFG_VARIANT_FULL
  }
  else
  {
    // nothing to do
  }

  
  boIsLowBeamEnabled = SysMonCheck_Data_Get_IsLowBeamEnabled();
  eAreFuSaParamValid = SysMonCheck_Data_AreFuSaParamValid();

  if ((boIsLowBeamEnabled == FALSE) && (eAreFuSaParamValid == SysMonCheck_Data_FuSaParamValid))
  {
    SysMonCheck_TurnOffFusaChannels(SysMonCheck_Data_eLF_LB_FuSa);
  }
  else
  {
    // nothing to do
  }
} // PRQA S 5316, 5324, 5336, 5310, 5330 1 // Software Architecture (it will still change)


/// ---------------------------------------------------------------------------
/// \func     SysMonCheck_CheckMinPWMandCurrent
///
/// \brief    Check minimum brightness for a given channel
///
/// \param    ucChannelIdx - Channel number
///
/// \return   void
///
/// ---------------------------------------------------------------------------
STATIC_AL void SysMonCheck_CheckMinPWMandCurrent(uint8 ucChannelIdx)
{
  tSysMonCheck_Data_LedChParam* pLedChPram = SysMonCheck_Data_GetaLEDChParamPtr();

  if (SysMonCheck_LedTarget_ASIL.asTgtVal[ucChannelIdx].unCurrent < pLedChPram[ucChannelIdx].unMinCurrent)
  {
    SysMonCheck_LedTarget_ASIL.asTgtVal[ucChannelIdx].unCurrent = pLedChPram[ucChannelIdx].unMinCurrent;
  }
  else
  {
    // nothing to do
  }

  if (SysMonCheck_LedTarget_ASIL.asTgtVal[ucChannelIdx].unDutyCycle < pLedChPram[ucChannelIdx].unMinPwmDuty)
  {
    SysMonCheck_LedTarget_ASIL.asTgtVal[ucChannelIdx].unDutyCycle = pLedChPram[ucChannelIdx].unMinPwmDuty;
  }
  else
  {
    // nothing to do
  }
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_TriggerCddLed_LowBeam
///
/// \descr  Function to trigger directly CddLed in case of Emergency Operation Mode
///
/// \param  ucValue - What to do with the Light Function
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonCheck_TriggerCddLed_LowBeam(uint8 ucValue)
{
  tSysMonCheck_Data_LedChParam* pLedChPram = SysMonCheck_Data_GetaLEDChParamPtr();

  if (SysMonCheck_Data_FuSaParamValid == SysMonCheck_Data_AreFuSaParamValid())
  {
    for (uint8 ucIdx = 0u; ucIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS; ucIdx++)
    {
      if ((SysMonCheck_Data_eLF_LB_FuSa == pLedChPram[ucIdx].eName))
      {
        if (SYSMON_LOWBEAM_OFF == ucValue)
        {
          // Removed after allignment with CABA Ionut
          // SysMonCheck_LedTarget_ASIL.asTgtVal[ucIdx].unCurrent    = SYSMON_ZERO_VALUE;
          // SysMonCheck_aLedTarget[ucIdx].unCurrent                 = SYSMON_ZERO_VALUE;
          SysMonCheck_LedTarget_ASIL.asTgtVal[ucIdx].unDutyCycle  = SYSMON_ZERO_VALUE;
          SysMonCheck_aLedTarget[ucIdx].unDutyCycle               = SYSMON_ZERO_VALUE;
        }
        else
        {
          // Do not touch other channels
          SysMonCheck_CheckMinPWMandCurrent(ucIdx);
        }
      }
      else
      {
        // nothing to do
      }
    }
  }
  else
  {
    // nothing to do
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_TriggerCddLed_TurnIndicator_Off
///
/// \descr  Function to trigger directly CddLed in case of Emergency Operation Mode
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonCheck_TriggerCddLed_TurnIndicator_Off(void)
{
  tSysMonCheck_Data_LedChParam* pLedChPram = SysMonCheck_Data_GetaLEDChParamPtr();

  if (SysMonCheck_Data_FuSaParamValid == SysMonCheck_Data_AreFuSaParamValid())
  {
    for (uint8 ucIdx = 0u; ucIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS; ucIdx++)
    {
      
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
      if ((SysMonCheck_Data_eLF_TI == pLedChPram[ucIdx].eName) || 
          (SysMonCheck_Data_eLF_TI_SCRL == pLedChPram[ucIdx].eName))
#elif defined (CFG_VARIANT_ECO)
      if (SysMonCheck_Data_eLF_TI == pLedChPram[ucIdx].eName)
#endif // CFG_VARIANT_FULL
      {
        // Removed after allignment with CABA Ionut
        //SysMonCheck_LedTarget_ASIL.asTgtVal[ucIdx].unCurrent    = SYSMON_ZERO_VALUE;
        //SysMonCheck_aLedTarget[ucIdx].unCurrent                 = SYSMON_ZERO_VALUE;
        SysMonCheck_LedTarget_ASIL.asTgtVal[ucIdx].unDutyCycle  = SYSMON_ZERO_VALUE;
        SysMonCheck_aLedTarget[ucIdx].unDutyCycle               = SYSMON_ZERO_VALUE;
      }
      else
      {
        // nothing to do
      }
    }
  }
  else
  {
    // nothing to do
  }
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Cycle10ms_HandleTurnIndicatorAndLowBeamDiagFeedback
///
/// \descr  Function to handle the Turn Indicator and Low Beam diagnostic feedback
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonCheck_Cycle10ms_HandleTurnIndicatorAndLowBeamDiagFeedback(void)
{
  uint8    ucLowBeamRequest = 0u;
  uint8    ucTurnIndicatorRequest = 0u;
  boolean  boIsLowBeamEnabled       = TRUE;
  boolean  boIsTurnIndicatorEnabled = TRUE;
  boolean  boCrc32RamFailure        = FALSE;
  boolean  boCrc32RomFailure        = FALSE;
  boolean  boInternalComErr         = FALSE;

  // Get Low Beam request and if Low Beam is enabled
  ucLowBeamRequest    = SysMonRx_ASIL_GetLowBeamValue();
  boIsLowBeamEnabled  = SysMonCheck_Data_Get_IsLowBeamEnabled();

  // Get Turn Indicator request and State value
  ucTurnIndicatorRequest    = SysMonRx_ASIL_GetTurnIndicatorValue();
  boIsTurnIndicatorEnabled  = SysMonCheck_Data_Get_IsTurnIndEnabled();

  // Get CRC32 over ROM and RAM Mirror failure status
  boCrc32RamFailure = SysMonCheck_Data_Get_Crc32RamFailure();
  boCrc32RomFailure = SysMonCheck_Data_Get_Crc32RomFailure();

  // Get Internal Communication Error Status
  boInternalComErr = SysMonCheck_InternalCom_IsComErrActive();

  // Check if Low Beam is requested and if we have a failure on Low Beam parameters
  if ((ucLowBeamRequest == SYSMON_LOWBEAM_ON) && 
      ((boIsLowBeamEnabled == FALSE) || (boCrc32RamFailure != FALSE)) ||
      (boInternalComErr != FALSE))
  {
    SysMonCheck_Set_CodingFailureDiagLowBeamStatus(TRUE);
  }
  else
  {
    SysMonCheck_Set_CodingFailureDiagLowBeamStatus(FALSE);
  }

  // Check if Turn Indicator is requested and if we have a failure on Turn Indicator parameters
  if ((ucTurnIndicatorRequest == SYSMON_TURNINDICATOR_ON) && 
      ((boIsTurnIndicatorEnabled == FALSE) || (boCrc32RamFailure != FALSE) || (boCrc32RomFailure != FALSE)) ||
      (boInternalComErr != FALSE))
  {
    SysMonCheck_Set_CodingFailureDiagTurnIndicatorStatus(TRUE);
  }
  else
  {
    SysMonCheck_Set_CodingFailureDiagTurnIndicatorStatus(FALSE);
  }

  // Handle Turn Indicator diagnostic window
  SysMonCheck_Ti_DiagWindow();
} // PRQA S 5324 1 // Software Architecture


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Set_CodingFailureDiagLowBeamStatus
///
/// \descr  Function to set the coding failure for Diag Low Beam Status
///
/// \param  boDiagLbStatus
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonCheck_Set_CodingFailureDiagLowBeamStatus(boolean boDiagLbStatus)
{
  SysMonCheck_boCodingFailureDiagLowBeam = boDiagLbStatus;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Get_CodingFailureDiagLowBeamStatus
///
/// \descr  Function to get the coding failure for Diag Low Beam Status
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean SysMonCheck_Get_CodingFailureDiagLowBeamStatus(void)
{
  return SysMonCheck_boCodingFailureDiagLowBeam;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Set_CodingFailureDiagTurnIndicatorStatus
///
/// \descr  Function to set the coding failure for Diag Turn Indicator Status
///
/// \param  boDiagTiStatus
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonCheck_Set_CodingFailureDiagTurnIndicatorStatus(boolean boDiagTiStatus)
{
  SysMonCheck_boCodingFailureDiagTurnIndicator = boDiagTiStatus;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Get_CodingFailureDiagTurnIndicatorStatus
///
/// \descr  Function to get the coding failure for Diag Turn Indicator Status
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean SysMonCheck_Get_CodingFailureDiagTurnIndicatorStatus(void)
{
  return SysMonCheck_boCodingFailureDiagTurnIndicator;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Get_LbTiFuSa_OffStatus
///
/// \descr  Function to get the turning off in case of electrical errors
///
/// \param  void
///
/// \return tSysMon_FuSaChannelsStatusReaction
//-----------------------------------------------------------------------------
tSysMon_FuSaChannelsStatusReaction SysMonCheck_Get_LbTiFuSa_OffStatus(void)
{
  return SysMonCheck_sFuSaChannelsStatusReaction;
}

//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_TI_Diag_Status
///
/// \descr  Function get TI diag status
///
/// \param  void
///
/// \return SysMonCheck_boTurnIndicatorDiagStatus
//-----------------------------------------------------------------------------
boolean SysMonCheck_TI_Diag_Status(void)
{
  return SysMonCheck_boTurnIndicatorDiagStatus;
}

//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Ti_DiagWindow
///
/// \descr  Function to handle Diagnostitc TI status
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonCheck_Ti_DiagWindow(void)
{
  static boolean boTiFault                  = FALSE;
  static boolean boTiCommand                = FALSE;
  static boolean boTiCommandOff             = FALSE;
  static boolean boTiCommandOld             = FALSE;
  static uint8   ucTiTimersDelayStatus      = SYSMONCHECK_INVALID_CONFIG; //0xFF -> invalid configuration
  static uint8   ucTiTimersDelayStatusFault = SYSMONCHECK_INVALID_CONFIG; //0xFF -> invalid configuration
  uint8          ucTurnIndicatorStatus      = SYSMON_TURNINDICATOR_OFF;


  // Get Turn Indicator command value
  ucTurnIndicatorStatus = SysMonRx_ASIL_GetTurnIndicatorValue();

  const boolean boTiReq = (ucTurnIndicatorStatus == SYSMON_TURNINDICATOR_ON) ? TRUE : FALSE;

  // End of Turn Indicator request detection by using DELAY_TI_NOT_REQUESTED timer (500 ms default)
  ucTiTimersDelayStatus = SysMonCheck_CtrlTiDelayStatus((boTiReq != FALSE) ? FALSE : TRUE, SysMonCheck_unDELAY_TI_NOT_REQUESTED, SYSMONCHECK_DELAY_TI_NOT_REQUESTED);
  boTiCommandOff = (ucTiTimersDelayStatus != SYSMONCHECK_TIMEOUT_NOT_OCCURED) ? TRUE : (boTiReq != FALSE) ? FALSE : boTiCommandOff; // TI request is off for more than DELAY_TI_NOT_REQUESTED_TIME_MS
  
  //Get the value of TI value
  SysMonCheck_boTICommandValue = boTiCommandOff;

  // New request of Turn Indicator
  boTiCommand = (boTiReq != FALSE) ? TRUE : (boTiCommandOff != FALSE) ? FALSE : boTiCommand;

  // Handle TI in case of multiple channels need to be turned OFF and KEPT off
  SysMonCheck_Cycle10ms_HandleTurnIndicatorFuSaBehaviour(boTiCommand);

  // Get LED Diag status
  const boolean boTiErrFree = SysMonCheck_LedDiag_IsTiLightSourceErrorFree();

  // 340 ms debounce timer for fault detection time debounce based on customer bug ticket LDMO-3490 
  ucTiTimersDelayStatusFault = SysMonCheck_CtrlTiDelayStatus(((boTiCommand != FALSE) && (boTiErrFree != FALSE)) ? TRUE : FALSE, SYSMONCHECK_TI_FAULT_DETECTION_TIME_MS, SYSMONCHECK_TI_FAULT_DETECTION);
  const boolean boErrDetect = (ucTiTimersDelayStatusFault != SYSMONCHECK_TIMEOUT_NOT_OCCURED) ? TRUE : FALSE;

  // Check for Error Free condition removed based on customer bug ticket LDMO-3490 
  boTiFault = (boTiReq != FALSE) && (boTiErrFree == FALSE) ? TRUE : ((boTiCommand != FALSE) /*(boTiErrFree != FALSE)*/ && (boErrDetect != FALSE)) ? FALSE : boTiFault;

  // DIAG_TI going to CAN
  SysMonCheck_boTurnIndicatorDiagStatus = ((boTiFault != FALSE) && (boTiCommand != FALSE)) ? TRUE : ((boTiFault == FALSE) && (boTiCommand != FALSE) && (boTiCommandOld == FALSE)) ? FALSE : SysMonCheck_boTurnIndicatorDiagStatus;

  // Only update Old Command when 250ms have passed 
  if (((boErrDetect != FALSE) && (boTiCommand == TRUE) && (boTiCommandOld == FALSE)) ||
    ((boTiCommand == FALSE) && (boTiCommandOld != FALSE)))
  {
    boTiCommandOld = boTiCommand;
  }
  else
  {
    // nothing to do
  }
}

//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_CtrlTiDelayStatus
///
/// \descr  
///
/// \param   
///
/// \return uint8
//-----------------------------------------------------------------------------
STATIC_AL uint8 SysMonCheck_CtrlTiDelayStatus(const boolean boReqInput, const TIMER ulTimeMs, const sint8 scTiTimerSel)
{
  uint8 ucTiTimersDelayStatus = SYSMONCHECK_INVALID_CONFIG;
  if (scTiTimerSel < SYSMONCHECK_NUMBER_OF_TI_TIMERS)
  {
    SysMonCheck_sTiTimerCfg[scTiTimerSel].ulTimeMs_Input = ulTimeMs;
    SysMonCheck_sTiTimerCfg[scTiTimerSel].boReq_Input = boReqInput;
    ucTiTimersDelayStatus = SysMonCheck_TiDelayStatus(SysMonCheck_sTiTimerCfg, scTiTimerSel);
  }
  return ucTiTimersDelayStatus;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_TiDelayStatus
///
/// \descr  This function return TimeOut = TRUE based on sTiCfg TI Configurations
///
/// \param   *sTiCfg, scTiTimerSel
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean SysMonCheck_TiDelayStatus(tsSysMonCheck_TiTimerCfg *sTiCfg, const sint8 scTiTimerSel)
{
  if (sTiCfg[scTiTimerSel].boReq_Input != FALSE)
  {
    if (sTiCfg[scTiTimerSel].boStartStopTimer == FALSE)
    {
      sTiCfg[scTiTimerSel].ulCommandStart = UTILTIME_TIMER_START(UTILTIME_MSEC(sTiCfg[scTiTimerSel].ulTimeMs_Input));
      sTiCfg[scTiTimerSel].boStartStopTimer = TRUE;
    }
  }
  else
  {
    sTiCfg[scTiTimerSel].boTimeOut = FALSE;
    sTiCfg[scTiTimerSel].boStartStopTimer = FALSE;
  }

  if (sTiCfg[scTiTimerSel].boStartStopTimer != FALSE)
  {
    sTiCfg[scTiTimerSel].boTimeOut = UTILTIME_TIMER_TIMEOUT(sTiCfg[scTiTimerSel].ulCommandStart);
  }

  return sTiCfg[scTiTimerSel].boTimeOut;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Cycle10ms_HandleTurnIndicatorFuSaBehaviour
///
/// \descr  This function will turn OFF all TI channels if coding parameter 
///         FUSA_TI_FS_BEHAVIOUR_ASIL is set to 1
///
/// \param  boTiCmd - ON/OFF TI Command
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonCheck_Cycle10ms_HandleTurnIndicatorFuSaBehaviour(boolean boTiCmd)
{
  boolean boTurnAll_TI_FuSa_OFF         = FALSE;
  boolean boIsLightSourceErrorFreeTi    = FALSE;
  boolean boIsLightSourceSpiErrorFreeTi = FALSE;

  static tsSysMonCheck_FUSA_TI_ASIL_TURN_OFF sFusaTiTurnOff = { FALSE, FALSE };
  tSysMonCheck_Data_LedChParam* pLedChPram = SysMonCheck_Data_GetaLEDChParamPtr();
  uint8 ucFUSA_TI_FS_BEHAVIOUR_ASIL        = SysMonCheck_Data_Get_ucFUSA_TI_FS_BEHAVIOUR_ASIL();

  // Check OFF -> ON transition for Turn Indicator
  if (boTiCmd != FALSE)
  {
    if (sFusaTiTurnOff.boTurnIndicatorCmd == FALSE)
    {
      // Transition from OFF to ON
      sFusaTiTurnOff.boTurnIndicatorCmd = TRUE;
    }
    else
    {
      // nothing to do
    }
  }
  else
  {
    sFusaTiTurnOff.boTurnIndicatorCmd = FALSE;
  }

  // Check TI electrical error and turn OFF TI
  if (sFusaTiTurnOff.boTurnIndicatorCmd != FALSE)
  {
    for (uint8 ucIdx = 0u; ucIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS; ucIdx++)
    {
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
      if ((SysMonCheck_Data_eLF_TI == pLedChPram[ucIdx].eName) ||
        (SysMonCheck_Data_eLF_TI_SCRL == pLedChPram[ucIdx].eName))
#elif defined (CFG_VARIANT_ECO)
      if (SysMonCheck_Data_eLF_TI == pLedChPram[ucIdx].eName)
#endif // CFG_VARIANT_FULL
      {
        // Get electrical status of LED channel
        boIsLightSourceErrorFreeTi = SysMonCheck_LedDiag_IsLightSourceErrorFree(ucIdx);
        // Get Spi error status of LED channel
        boIsLightSourceSpiErrorFreeTi = SysMonCheck_LedDiag_IsLightSourceSpiErrorFree(ucIdx);

        if ((boIsLightSourceErrorFreeTi != FALSE) &&
          (boIsLightSourceSpiErrorFreeTi != FALSE) &&
          (sFusaTiTurnOff.TurnAll_TI_FuSa_OFF == FALSE))
        {
          // nothing to do, channel is OK
        }
        else
        {
          // If FUSA TI BEHAVIOUR is 1 , Turn OFF all TI channels
          sFusaTiTurnOff.TurnAll_TI_FuSa_OFF = (ucFUSA_TI_FS_BEHAVIOUR_ASIL == 1U) ? TRUE : FALSE;
          // Turn Off this TI Channel
          SysMonCheck_TurnOffChannel(ucIdx);
          // Retain Channel Status Reaction
          SysMonCheck_sFuSaChannelsStatusReaction.boTi_FuSa_Idx[ucIdx] = TRUE;
        }
      }
      else
      {
        // nothing to do , this is not a TI channel
      }
    }
  }
  else
  {
    // Reset for next Turn Indicator ON request cycle
    sFusaTiTurnOff.TurnAll_TI_FuSa_OFF = FALSE;
    // Reset the Status Reactions for Turn Indicator
    SysMonCheck_ResetTiStatusReaction();
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Get_TgtLed_FaultStatus_ASIL
///
/// \descr  Function to get the turning off in case of electrical errors
///
/// \param  void
///
/// \return boolean - TRUE = error present
///                 - FALSE = no error
//-----------------------------------------------------------------------------
boolean SysMonCheck_Get_TgtLed_FaultStatus_ASIL(void)
{
  return SysMonCheck_sTgtLed_FaultStatus_ASIL.boCrc8ErrorStatus;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_ResetLbStatusReaction
///
/// \descr  Function to reset the Low Beam status reaction channel
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonCheck_ResetLbStatusReaction(void)
{
  for (uint8 ucIdx = 0u; ucIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS; ucIdx++)
  {
    SysMonCheck_sFuSaChannelsStatusReaction.boLb_FuSa_Idx[ucIdx] = FALSE;
  }
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_ResetTiStatusReaction
///
/// \descr  Function to reset the Turn Indicator status reaction channel
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonCheck_ResetTiStatusReaction(void)
{
  for (uint8 ucIdx = 0u; ucIdx < SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS; ucIdx++)
  {
    SysMonCheck_sFuSaChannelsStatusReaction.boTi_FuSa_Idx[ucIdx] = FALSE;
  }
}

//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_GetTurnIndicatorCommandValue
///
/// \descr  Function to get the command value of TI
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean SysMonCheck_GetTurnIndicatorCommandValue(void)
{
  return SysMonCheck_boTICommandValue;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_CodingFailureSetDiag
///
/// \descr  In case of coding failure, set DIAG TI and LB to NOK
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonCheck_CodingFailureSetDiag(void)
{
  uint8    ucLowBeamRequest       = 0u;
  uint8    ucTurnIndicatorRequest = 0u;

  // Get Low Beam request
  ucLowBeamRequest        = SysMonRx_ASIL_GetLowBeamValue();
  // Get Turn Indicator request
  ucTurnIndicatorRequest  = SysMonRx_ASIL_GetTurnIndicatorValue();

  // Check if Low Beam is requested and set DIAG_LB to NOK
  if (ucLowBeamRequest == SYSMON_LOWBEAM_ON)
  {
    SysMonCheck_Set_CodingFailureDiagLowBeamStatus(TRUE);
  }
  else
  {
    SysMonCheck_Set_CodingFailureDiagLowBeamStatus(FALSE);
  }

  // Check if Turn Indicator is requested and set DIAG_TI to NOK
  if (ucTurnIndicatorRequest == SYSMON_TURNINDICATOR_ON)
  {
    SysMonCheck_Set_CodingFailureDiagTurnIndicatorStatus(TRUE);
  }
  else
  {
    SysMonCheck_Set_CodingFailureDiagTurnIndicatorStatus(FALSE);
  }
}


/// ---------------------------------------------------------------------------
/// \func     SysMonCheck_EmergModeMinimumBrightnessCheck
///
/// \brief    Check minimum brightness or turn OFF LB FuSa channel in case 
///           of Emergency Operation Mode.
///
/// \param    void
///
/// \return   void
/// ---------------------------------------------------------------------------
STATIC_AL void SysMonCheck_EmergModeMinimumBrightnessCheck(void)
{
  boolean  boLowBeamEnabledByEmergOp   = FALSE;
  boolean  boEmergencyOperationLowBeam = FALSE;

  // Get Low Beam in context of Emergency Operation Mode // LDMO-3383
  boLowBeamEnabledByEmergOp   = SysMonRx_ASIL_Get_boEmergencyOperation_FinalLowBeamStatus();
  boEmergencyOperationLowBeam = SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam();

  // Perform Check For Minimum Brightness in case of Emergency Operation Mode
  if ((boEmergencyOperationLowBeam != FALSE) && (boLowBeamEnabledByEmergOp != FALSE))
  {
    // Perform Minimum Brightness Check in case of Emergency Operation Mode Activation
    SysMonCheck_TriggerCddLed_LowBeam(SYSMON_LOWBEAM_ON);
  }
  else if ((boEmergencyOperationLowBeam != FALSE) && (boLowBeamEnabledByEmergOp == FALSE))
  {
    // Turn Off Low Beam
    SysMonCheck_TriggerCddLed_LowBeam(SYSMON_LOWBEAM_OFF);
  }
  else
  {
    // nothing to do
  }
}


/// ---------------------------------------------------------------------------
/// \func     SysMonCheck_VerifyTiNonFuSaActivation
///
/// \brief    Verify if TI is activated by Non FuSa activation and perform
///           bypass of Current and PWM values
///
/// \param    void
///
/// \return   void
/// ---------------------------------------------------------------------------
STATIC_AL void SysMonCheck_VerifyTiNonFuSaActivation(void)
{
  // Autonomous warning light carrier
  teSysMon_WarningMode   eWarningMode = eSysMon_PilotedMode;
  // Speed state
  SysMon_EnumSpeedState  eSpeedState = SysMon_Speed_0_State;
  
  // Get Autonomous warning light
  eWarningMode = SysMonRx_Callbacks_Get_AutonomMode();

  // Get Speed State
  eSpeedState = SysMonRx_ASIL_GetSpeedState();

  // If Vehicle Speed is over 5 km/h or Invalid AND if Warning Mode is in Piloted Mode
  if ((eSpeedState != SysMon_Speed_0_State) && (eWarningMode != eSysMon_AutonomMode))
  {
    // Force OFF TI channels because there is no request
    SysMonCheck_TurnOffFusaChannels(SysMonCheck_Data_eLF_TI);
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
    SysMonCheck_TurnOffFusaChannels(SysMonCheck_Data_eLF_TI_SCRL);
#endif // CFG_VARIANT_FULL
  }
  else
  {
    // nothing to do, light will be applied to channel
  }
}



// EOF
