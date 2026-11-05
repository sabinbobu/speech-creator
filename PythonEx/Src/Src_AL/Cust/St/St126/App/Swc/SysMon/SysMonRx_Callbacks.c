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
/// \file   SysMonRx_Callbacks.c
///
/// \brief  Input Frame Rx Callbacks
///
/// \descr  Input Frame Rx Callbacks [Init, Receprion Event, Time-out error, Checksum/Cnt Error]
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <SysMonRx_Callbacks.h>
#include <SysMonRx.h>

#include <SysMon_E2E.h>
#include <LgmDEHMainAPI.h>

#ifdef UNIT_TEST
#include <LgmEIMMainAPI.h>
#include <ConfigE2E.h>
#endif // UNIT_TEST


 //-----------------------------------------------------------------------------
 // variables
 //-----------------------------------------------------------------------------
STATIC_AL tsSysMonRx_LowBeamSignal         SysMonRx_Callbacks_sLowBeamSignal        = { 0u, SIG_SNA };
STATIC_AL tsSysMonRx_LifePhaseSignal       SysMonRx_Callbacks_sLifePhaseSignal      = { eWake, SIG_SNA };
STATIC_AL teSysMonRx_SpeedSignal           SysMonRx_Callbacks_sSpeedSignal          = { 0u, SIG_SNA };
STATIC_AL teRte_SigQty                     SysMonRx_Callbacks_eVESMainStateSignal   = SIG_SNA;
STATIC_AL tsSysMonRx_TurnIndicatorSignal   SysMonRx_Callbacks_sTurnIndicatorSignal  = { 0u, SIG_SNA };
// Variable which returns value state of DiagMuxOnPwt signal (value and signal valid quality status)
STATIC_AL tsSysMon_DiagMuxState            SysMon_RxCallbacks_sDiagMuxOnPwtState = { FALSE, FALSE };
 
STATIC_AL EECO_TE_ProfileOneChunkStatus    SysMonRx_Callbacks_pte_ChunkStateE2E;

// Raw data of 0x38D Rx frame 
STATIC_AL uint8                            SysMonRx_Callbacks_aucRaw38DFrame[SYSMONRX_CALLBACKS_LENGTH_38D];
STATIC_AL boolean                          SysMonRx_Callbacks_boTiDegarde = FALSE;
// LDMO-2759 Flag for the first frame check of Process Counter 0x38D
STATIC_AL boolean                          SysMonRx_Callbacks_boFirstFrameRec = TRUE;

STATIC_AL tsSysMonRx_TimerCfg              SysMonRx_Callbacks_sTimerCfg[SYSMONRX_CALLBACKS_NUMBER_OF_TIMERS];

// Variable used for Autonomous Mode
STATIC_AL teSysMon_WarningMode             SysMonRx_Callbacks_eTiWarningMode = eSysMon_PilotedMode;

 //-----------------------------------------------------------------------------
 // funtion prototypes
 //-----------------------------------------------------------------------------
STATIC_AL teRte_SigQty            SysMonRx_Callbacks_EvaluateCrcAndAliveDtcs(teRte_SigQty eSigQty, teRte_SigQty eOldSigQty);
STATIC_AL uint8                   SysMonRx_Callbacks_Compute_TurnIndicatorCmd(uint8 ucTiCmd);
STATIC_AL teRte_ModeConfigVehicle SysMonRx_Callbacks_Compute_ConfigVhl(uint8 ucConfigVhl);
STATIC_AL void                    SysMonRx_Callbacks_RangeCheck_LightDynAbr(tsRte_SysMon_VehicleSpeed *psOutputSig, tsSysMon_RxSpeedFrmCheck sInputSig, teRte_SigQty *peSigQty);
STATIC_AL void                    SysMonRx_Callbacks_Compute_EletricalNetworkState(tsRte_SysMon_VehNetState *psOutputSig, uint8 ucInputSig);
STATIC_AL teRte_SigQty            SysMonRx_Callbacks_Compute_VESMainState(tsRte_SysMon_VehNetState *psOutputSig, uint8 ucInputSig);
STATIC_AL boolean                 SysMonRx_Callbacks_CheckSumCheck(const uint8 ucRxData[], uint8 ucDLC);
STATIC_AL boolean                 SysMonRx_Callbacks_ProcessCntCheck(const uint8 ucCmpProc);
STATIC_AL boolean                 SysMonRx_Callbacks_Hb_Cmd_OtherCond(void);
STATIC_AL void                    SysMonRx_Callbacks_RangeCheck_PhaseVie(tsRte_SysMon_LifePhases *psOutputSig, uint8 ucPhaseVie, teRte_SigQty *pSigQty);
STATIC_AL boolean                 SysMonRx_Callbacks_LossFrame_TimerCheck(boolean *pboStartTimer, uint8 ucFrameName);
STATIC_AL void                    SysMonRx_Callbacks_Compute_AutonomMode(tsRte_SysMonLgtTiReq sAutonomReq, uint8 ucTiReq);

STATIC_AL boolean                 SysMonRx_Callbacks_Timeout(CONST_AL boolean boReqInput, CONST_AL TIMER ulTimeMs, CONST_AL uint8 ucTiTimerSel);
STATIC_AL boolean                 SysMonRx_Callbacks_HandleDelayStatus(tsSysMonRx_TimerCfg *psTimersCfg, CONST_AL uint8 ucTimerSel);

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
STATIC_AL void           SysMonRx_Callbacks_Compute_AfsMode(tsRte_SysMonAfsSignals *psOutputSig, uint8 ucAfsMode);
STATIC_AL teRte_GfHb_Cmd SysMonRx_Callbacks_Compute_GfhbCmd(uint8 ucGfhbCmd);
#endif // CFG_VARIANT_FULL

 //-----------------------------------------------------------------------------
 // functions
 //-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
/// \brief SysMon_RxCallbacks_HS6_DAT_VSM_2AE
///
/// \descr Handling of 0x2AE receive CAN frame
///
/// \param  eSysMonRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SysMon_RxCallbacks_HS6_DAT_VSM_2AE(teSysMon_RxFrameState eSysMonRxState)
{
  uint8  ucWarningMode           = 0u;
  uint8  ucEtatClignotants       = 0u;
  uint8  ucLeftTurnIndicatorCmd  = 0u;
  uint8  ucRightTurnIndicatorCmd = 0u;
  uint8  ucTurnIndicatorCmdInUse = SYSMON_TURNINDICATOR_OFF;
  teRte_SigQty eSigQtyTi         = SIG_INIT;
  STATIC_UT(boolean, boTimerStatus, FALSE);

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  uint8  ucTurnIndicatorScrolling = 0u;
#endif // CFG_VARIANT_FULL

  tsRte_SysMonLgtTiReq   sTurnIndicatorReq  = { 0 };
  teRte_MountingSide     eMountingSide      = { 0 };

  tHS6_DAT_VSM_2AE stData;
  (void)Rte_Read_SigPrep_HS6_DAT_VSM_2AE_Received(&stData);

  boTimerStatus = (eSysMonRxState != eSysMonFrmTimeOut) ? FALSE : boTimerStatus;

  // Get headlamp mounting side
  eMountingSide = SysMonRx_GetMountingSide();

  sTurnIndicatorReq.eSigQty = SIG_INIT; //Initialise the structure
  
  (void)Rte_Read_SysMon_StdLgtTi_Req(&sTurnIndicatorReq);

  switch (eSysMonRxState)
  {
    case eSysMonFrameInit:
      // Set signal quality for RTE port as SNA
      sTurnIndicatorReq.eSigQty = SIG_SNA;
      eSigQtyTi                 = SIG_SNA;

      sTurnIndicatorReq.eWarning_Mode = eWarningMode_PilotedWarningMode;
      sTurnIndicatorReq.eEtat_Clignotants = eEtatClignotants_IndicatorInactive;

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
      sTurnIndicatorReq.eTi_Scrolling = eScrollingTI_Off;
#endif // CFG_VARIANT_FULL
      break;

    case eSysMonFrmEvent:
      // Reset DTC U014087 - frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_VSM_2AE_ID, DEM_EVENT_STATUS_PASSED);

      // Read Left and Right TI CAN signals
      ucLeftTurnIndicatorCmd  = stData.ucLeftTurnIndicatorCmd;
      ucRightTurnIndicatorCmd = stData.ucRightTurnIndicatorCmd;
      ucWarningMode           = stData.ucWarningMode;
      ucEtatClignotants       = stData.ucEtatClignotants;

      // Compute Warning mode
      sTurnIndicatorReq.eWarning_Mode = (ucWarningMode != SYSMON_RX_ZERO_VALUE) ? eWarningMode_AutonomWarningMode : eWarningMode_PilotedWarningMode;

      // Compute Status of indicators
      switch (ucEtatClignotants)
      {
        case SYSMON_RX_ETAT_CLIGNO_RIGHT_IND_ACTIVE:          { sTurnIndicatorReq.eEtat_Clignotants = eEtatClignotants_RightIndicatorActive;        }  break;
        case SYSMON_RX_ETAT_CLIGNO_LEFT_IND_ACTIVE:           { sTurnIndicatorReq.eEtat_Clignotants = eEtatClignotants_LeftIndicatorActive;         }  break;
        case SYSMON_RX_ETAT_CLIGNO_LEFT_AND_RIGHT_IND_ACTIVE: { sTurnIndicatorReq.eEtat_Clignotants = eEtatClignotants_LeftAndRightIndicatorActive; }  break;
        default:                                              { sTurnIndicatorReq.eEtat_Clignotants = eEtatClignotants_IndicatorInactive;           }  break;
      }

      // The Application shall use the TI command relevant for it's mounted side
      ucTurnIndicatorCmdInUse = (eMountingSide != eMountedLeft) ? ucRightTurnIndicatorCmd : ucLeftTurnIndicatorCmd;

      // Compute the TI command
      ucTurnIndicatorCmdInUse = SysMonRx_Callbacks_Compute_TurnIndicatorCmd(ucTurnIndicatorCmdInUse);

      // Compute TI error/not known states and set the Signal Quality to Valid/Invalid
      if (ucTurnIndicatorCmdInUse != SYSMON_TURNINDICATOR_INVALID)
      {
        sTurnIndicatorReq.eSigQty = SIG_VALID;
        eSigQtyTi                 = SIG_VALID;

        // Clear DTC U1218-81 - invalid data
        Rte_Call_DemPrj_ReportErrorStatus((uint16)TI_INVALID_DATA_2AE, DEM_EVENT_STATUS_PASSED);
      }
      else
      {
        sTurnIndicatorReq.eSigQty = SIG_INVALID;
        eSigQtyTi                 = SIG_INVALID;

        // Set DTC U1218-81 - invalid data
        Rte_Call_DemPrj_ReportErrorStatus((uint16)TI_INVALID_DATA_2AE, DEM_EVENT_STATUS_FAILED);
      }

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
      ucTurnIndicatorScrolling = stData.ucTurnIndicatorScrolling;

      // Compute Scrolling TI activation
      sTurnIndicatorReq.eTi_Scrolling = (ucTurnIndicatorScrolling != SYSMON_RX_ZERO_VALUE) ? eScrollingTI_On : eScrollingTI_Off;
#endif // CFG_VARIANT_FULL
      break;

    case eSysMonFrmTimeOut:
      // Check 2 seconds timeout before setting SigQty to TIMEOUT
      if (SysMonRx_Callbacks_LossFrame_TimerCheck(&boTimerStatus, CANRX_HS6_DAT_VSM_2AE) == TRUE)
      {
        sTurnIndicatorReq.eWarning_Mode = eWarningMode_PilotedWarningMode;
        sTurnIndicatorReq.eEtat_Clignotants = eEtatClignotants_IndicatorInactive;

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
        sTurnIndicatorReq.eTi_Scrolling = eScrollingTI_Off;
#endif // CFG_VARIANT_FULL

        // Set signal quality for RTE port as time-out
        sTurnIndicatorReq.eSigQty = SIG_TIMEOUT;
        // Set DTC U014087 - frame lost
        Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_VSM_2AE_ID, DEM_EVENT_STATUS_FAILED);
      };

      // Set signal quality for FuSa reaction as time-out
      eSigQtyTi = SIG_TIMEOUT;
      break;

    default:
      break;
  }

  // Compute Autonomous Mode
  SysMonRx_Callbacks_Compute_AutonomMode(sTurnIndicatorReq, ucTurnIndicatorCmdInUse);

  // Pass the Signal Quality and Turn Indicator values to SysMonRx_ASIL for TurnIndicator State Interface evaluation
  SysMonRx_Callbacks_sTurnIndicatorSignal.ucTurnIndicatorValue = ucTurnIndicatorCmdInUse;
  SysMonRx_Callbacks_sTurnIndicatorSignal.eTurnIndicatorSigQty = eSigQtyTi;

  (void)Rte_Write_SysMon_StdLgtTi_Req(&sTurnIndicatorReq);
} // PRQA S 5324, 5330 1 // Software Architecture



//-----------------------------------------------------------------------------
/// \brief SysMon_RxCallbacks_HS6_DAT_VSM_34E
///
/// \descr Handling of 0x34E receive CAN frame
///
/// \param  eSysMonRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SysMon_RxCallbacks_HS6_DAT_VSM_34E(teSysMon_RxFrameState eSysMonRxState)
{
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  uint8  ucFrontFogBeamCmd       = 0u;
  uint8  ucAfsModeCmd            = 0u;
  uint8  ucGfhbCmd               = 0u;
  uint8  ucLowBeamBoostAllowed   = 0u;
  uint8  ucPedestrianAllowed     = 0u;
  uint8  ucAimingModeActivation  = 0u;
  uint8  ucMotorwayDetection     = 0u;

  tsRte_SysMonAfsSignals  dataAfsSignals = { 0 };

  dataAfsSignals.eSigQty = SIG_INIT; //Initialise the structure
#endif // CFG_VARIANT_FULL

  uint8  ucDayTimeRunningLightCmd = 0u;
  uint8  ucLowBeamCmd             = 0u;
  uint8  ucHighBeamCmd            = 0u;
  uint8  ucSideMarkerCmd          = 0u;
  uint8  ucFrontPositionCmd       = 0u;
  uint8  ucHeadlampFlashBeamCmd   = 0u;
  uint8  ucEtatFeuxStationnement  = 0u;
  uint8  ucConfigVhl              = 0u;

  teRte_SigQty eSigQtyLowBeam = SIG_INIT;

  tsRte_SysMonLgtFctsReq  dataLgtFctsReq  = { 0 };
  teRte_MountingSide      eMountingSide   = { 0 };
  teRte_ReqLightState     eLowBeamReq     = ReqLighted_Off;
  STATIC_UT(boolean, boTimerStatus, FALSE);

  tHS6_DAT_VSM_34E stData;
  (void)Rte_Read_SigPrep_HS6_DAT_VSM_34E_Received(&stData);

  boTimerStatus = (eSysMonRxState != eSysMonFrmTimeOut) ? FALSE : boTimerStatus;

  dataLgtFctsReq.eSigQty = SIG_INIT; //Initialise the structure

  // Get headlamp mounting side
  eMountingSide = SysMonRx_GetMountingSide();

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  (void)Rte_Read_SysMon_Afs_Signals(&dataAfsSignals);
#endif // CFG_VARIANT_FULL

  (void)Rte_Read_SysMon_LowBeamCmd_Req(&eLowBeamReq);
  (void)Rte_Read_SysMon_StdLgtFcts_Req(&dataLgtFctsReq);

  ucLowBeamCmd = (eLowBeamReq == ReqLighted_Off) ? FALSE : TRUE;

  switch (eSysMonRxState)
    {
    case eSysMonFrameInit:
      // Set signal quality for RTE ports as SNA
      dataLgtFctsReq.eSigQty = SIG_SNA;
      eSigQtyLowBeam         = SIG_SNA;
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
      dataAfsSignals.eSigQty = SIG_SNA;
#endif // CFG_VARIANT_FULL
      break;

    case eSysMonFrmEvent:
      // Reset DTC U014087 - frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_VSM_34E_ID, DEM_EVENT_STATUS_PASSED);

      // Read CAN signals
      ucLowBeamCmd              = (eMountingSide != eMountedRight) ? stData.ucLowBeamCmd[0] : stData.ucLowBeamCmd[1];
      ucDayTimeRunningLightCmd  = (eMountingSide != eMountedRight) ? stData.ucDayTimeRunningLightCmd[0] : stData.ucDayTimeRunningLightCmd[1];
      ucHighBeamCmd             = (eMountingSide != eMountedRight) ? stData.ucHighBeamCmd[0] : stData.ucHighBeamCmd[1];
      ucSideMarkerCmd           = (eMountingSide != eMountedRight) ? stData.ucSideMarkerCmd[0] : stData.ucSideMarkerCmd[1];
      ucFrontPositionCmd        = (eMountingSide != eMountedRight) ? stData.ucFrontPositionCmd[0] : stData.ucFrontPositionCmd[1];
      const boolean boSkipHbCmd = SysMonRx_Callbacks_Hb_Cmd_OtherCond();
      dataLgtFctsReq.eDrl_Request   = (ucDayTimeRunningLightCmd != SYSMON_RX_ZERO_VALUE) ? ReqLighted_On : ReqLighted_Off;
      dataLgtFctsReq.eHb_Request    = ((ucHighBeamCmd           != SYSMON_RX_ZERO_VALUE) && (boSkipHbCmd == FALSE) && (ucLowBeamCmd != SYSMON_RX_ZERO_VALUE)) ? ReqLighted_On : ReqLighted_Off;
      dataLgtFctsReq.eSideM_Request = (ucSideMarkerCmd          != SYSMON_RX_ZERO_VALUE) ? ReqLighted_On : ReqLighted_Off;
      dataLgtFctsReq.ePos_Request   = (ucFrontPositionCmd       != SYSMON_RX_ZERO_VALUE) ? ReqLighted_On : ReqLighted_Off;

      ucHeadlampFlashBeamCmd = stData.ucHeadlampFlashBeamCmd;

      // Compute High Beam Flash request
      dataLgtFctsReq.eHbFlash_Request = (ucHeadlampFlashBeamCmd != SYSMON_RX_ZERO_VALUE) ? ReqLighted_On : ReqLighted_Off;

      ucEtatFeuxStationnement = stData.ucEtatFeuxStationnement;

      // Compute Parking light state
      switch (ucEtatFeuxStationnement)
      {
        case SYSMON_RX_ETAT_FEUX_STAT_DEACTIVATED:  { dataLgtFctsReq.eEtatFeuxStat = eEtatFeuxStationnement_Deactivated; }  break;
        case SYSMON_RX_ETAT_FEUX_STAT_LEFT_SIDE:    { dataLgtFctsReq.eEtatFeuxStat = eEtatFeuxStationnement_LeftSide;    }  break;
        case SYSMON_RX_ETAT_FEUX_STAT_RIGHT_SIDE:   { dataLgtFctsReq.eEtatFeuxStat = eEtatFeuxStationnement_RightSide;   }  break;
        default:                                    { dataLgtFctsReq.eEtatFeuxStat = eEtatFeuxStationnement_Invalid;     }  break;
      }

      // Compute Vehicle Configuration
      ucConfigVhl = stData.ucConfigVhl;
      dataLgtFctsReq.eConfigVhl = SysMonRx_Callbacks_Compute_ConfigVhl(ucConfigVhl);

      //call E2E protection to check the Pdu Status and Set signal quality for RTE port as valid
      eSigQtyLowBeam = SysMon_E2EGetChunkState(CONF_AS_PduPara[0].u8_PduDataChunksIdListAddress[0], &SysMonRx_Callbacks_pte_ChunkStateE2E);

      // Check DTCs for CRC and E2E
      dataLgtFctsReq.eSigQty = SysMonRx_Callbacks_EvaluateCrcAndAliveDtcs(eSigQtyLowBeam, dataLgtFctsReq.eSigQty);

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
      ucFrontFogBeamCmd     = (eMountingSide != eMountedRight) ? stData.ucFrontFogBeamCmd[0] : stData.ucFrontFogBeamCmd[1];
      dataLgtFctsReq.eFog_Request = (ucFrontFogBeamCmd != SYSMON_RX_ZERO_VALUE) ? ReqLighted_On : ReqLighted_Off;

      // Compute AFS mode
      ucAfsModeCmd = stData.ucAfsModeCmd;
      SysMonRx_Callbacks_Compute_AfsMode(&dataAfsSignals, ucAfsModeCmd);

      // Compute GFHB command
      ucGfhbCmd = stData.ucGfhbCmd;
      dataAfsSignals.eGfhb_Cmd = SysMonRx_Callbacks_Compute_GfhbCmd(ucGfhbCmd);

      ucLowBeamBoostAllowed = stData.ucLowBeamBoostAllowed;

      // Compute autorization to activate boost led for low beam
      dataAfsSignals.eLbBoost_Allowed = (ucLowBeamBoostAllowed != SYSMON_RX_ZERO_VALUE) ? eLowBeamBoostAllowed_True : eLowBeamBoostAllowed_False;

      ucPedestrianAllowed = stData.ucPedestrianAllowed;

      // Compute activation condition of AFS pedestrian mode
      dataAfsSignals.ePedestrian_Allowed = (ucPedestrianAllowed != SYSMON_RX_ZERO_VALUE) ? ePedestrianAllowed_True : ePedestrianAllowed_False;

      ucAimingModeActivation = stData.ucAimingModeActivation;

      // Compute activation request of the aiming mode
      dataAfsSignals.eAimingMode_Activation = (ucAimingModeActivation != SYSMON_RX_ZERO_VALUE) ? eAimingModeActivation_True : eAimingModeActivation_False;

      ucMotorwayDetection = stData.ucMotorwayDetection;

      // Compute activation request of the aiming mode
      dataAfsSignals.eMotorway_Detection = (ucMotorwayDetection != SYSMON_RX_ZERO_VALUE) ? eMotorwayDetection_True : eMotorwayDetection_False;

#endif // CFG_VARIANT_FULL

      // Check if CRC or Alive Counter is invalid
      if ((dataLgtFctsReq.eSigQty == SIG_E2E_CRCERR) || (dataLgtFctsReq.eSigQty == SIG_E2E_ALIVEERR))
      {
        // Deactivate all light functions
        dataLgtFctsReq.eDrl_Request     = ReqLighted_Off;
        dataLgtFctsReq.eHbFlash_Request = ReqLighted_Off;
        dataLgtFctsReq.eHb_Request      = ReqLighted_Off;
        dataLgtFctsReq.ePos_Request     = ReqLighted_Off;
        dataLgtFctsReq.eSideM_Request   = ReqLighted_Off;
        dataLgtFctsReq.eEtatFeuxStat    = eEtatFeuxStationnement_Deactivated;
        dataLgtFctsReq.eConfigVhl       = eModeConfigVehicle_Client;

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
        dataLgtFctsReq.eFog_Request           = ReqLighted_Off;
        dataAfsSignals.eAfs_Mode              = eCtrlAFS_Invalid;
        dataAfsSignals.eGfhb_Cmd              = eGfhbCmd_Off;
        dataAfsSignals.eLbBoost_Allowed       = eLowBeamBoostAllowed_False;
        dataAfsSignals.ePedestrian_Allowed    = ePedestrianAllowed_False;
        dataAfsSignals.eAimingMode_Activation = eAimingModeActivation_False;
        dataAfsSignals.eMotorway_Detection    = eMotorwayDetection_False;

        // Set signal quality for RTE port as CRC/Alive Error
        dataAfsSignals.eSigQty = dataLgtFctsReq.eSigQty;
#endif // CFG_VARIANT_FULL
      }
      else
      {
        // nothing to do
      }

      break;

    case eSysMonFrmTimeOut:
      // Check 2 seconds timeout before setting SigQty to TIMEOUT
      if (SysMonRx_Callbacks_LossFrame_TimerCheck(&boTimerStatus, CANRX_HS6_DAT_VSM_34E) == TRUE)
      {
        dataLgtFctsReq.eDrl_Request     = ReqLighted_Off;
        dataLgtFctsReq.eHbFlash_Request = ReqLighted_Off;
        dataLgtFctsReq.eHb_Request      = ReqLighted_Off;
        dataLgtFctsReq.ePos_Request     = ReqLighted_Off;
        dataLgtFctsReq.eSideM_Request   = ReqLighted_Off;
        dataLgtFctsReq.eEtatFeuxStat    = eEtatFeuxStationnement_Deactivated;
        dataLgtFctsReq.eConfigVhl       = eModeConfigVehicle_Client;

        // Set signal quality for RTE port as time-out
        dataLgtFctsReq.eSigQty = SIG_TIMEOUT;

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
        dataLgtFctsReq.eFog_Request           = ReqLighted_Off;
        dataAfsSignals.eAfs_Mode              = eCtrlAFS_Invalid;
        dataAfsSignals.eGfhb_Cmd              = eGfhbCmd_Off;
        dataAfsSignals.eLbBoost_Allowed       = eLowBeamBoostAllowed_False;
        dataAfsSignals.ePedestrian_Allowed    = ePedestrianAllowed_False;
        dataAfsSignals.eAimingMode_Activation = eAimingModeActivation_False;
        dataAfsSignals.eMotorway_Detection    = eMotorwayDetection_False;

        // Set signal quality for RTE port as time-out
        dataAfsSignals.eSigQty = SIG_TIMEOUT;
#endif // CFG_VARIANT_FULL

        // Set DTC U014087 - frame lost
        Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_VSM_34E_ID, DEM_EVENT_STATUS_FAILED);
      };

      // Set signal quality for FuSa reaction as time-out
      eSigQtyLowBeam = SIG_TIMEOUT;
    
      break;

    default:
      break;
  }

  // Pass the Signal Quality and Low Beam values to SysMonRx_ASIL for LowBeam State Interface evaluation
  SysMonRx_Callbacks_sLowBeamSignal.ucLowBeamValue = ucLowBeamCmd;
  SysMonRx_Callbacks_sLowBeamSignal.eLowBeamSigQty = eSigQtyLowBeam;

  (void)Rte_Write_SysMon_StdLgtFcts_Req(&dataLgtFctsReq);
#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
  (void)Rte_Write_SysMon_Afs_Signals(&dataAfsSignals);
#endif // CFG_VARIANT_FULL
  // PRQA S 5324, 5330 1 // program architecture and readability
}



//-----------------------------------------------------------------------------
/// \brief SysMon_RxCallbacks_HS6_COMMANDES_VSM_036
///
/// \descr Handling of 0x36 receive CAN frame
///
/// \param  eSysMonRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SysMon_RxCallbacks_HS6_COMMANDES_VSM_036(teSysMon_RxFrameState eSysMonRxState)
{
  uint8   ucPhaseVie      = 0u;
  uint8   ucInterdMemoDef = 0u;
  TE_Bool ucDemEffacDef   = E_FALSE;
  TE_Bool ucDiagMux       = E_FALSE;

  STATIC_UT(boolean, boDemEfacTrig, TRUE);
  STATIC_UT(uint8,   ucDemEfacCnt, 0u);

  teRte_SigQty eSigQtyPhaseVie = SIG_INIT;

  tsRte_SysMon_LifePhases  sLifePhases = { 0 };
  STATIC_UT(boolean, boTimerStatus, FALSE);

  tHS6_COMMANDES_VSM_036 stData;
  (void)Rte_Read_SigPrep_HS6_COMMANDES_VSM_036_Received(&stData);

  boTimerStatus = (eSysMonRxState != eSysMonFrmTimeOut) ? FALSE : boTimerStatus;

  sLifePhases.eSigQty = SIG_INIT; //Initialise the structure

  (void)Rte_Read_SysMon_LifePhases(&sLifePhases);

  switch (eSysMonRxState)
  {
    case eSysMonFrameInit:
      // Set signal quality for RTE port as SNA
      sLifePhases.eSigQty = SIG_SNA;
      eSigQtyPhaseVie     = SIG_SNA;
      // Initialize values
      sLifePhases.ePhaseVie       = eWake;
      sLifePhases.eDemEffacDef    = eNoRequest;
      sLifePhases.eDiagMuxOnBody  = eNoAuthorization;
      sLifePhases.eInterdMemoDef  = eMemorisationAuthorized;
      // Set DiagMuxOn Signal quality status as false
      SysMon_RxCallbacks_sDiagMuxOnPwtState.boDiagMuxSigStatus = FALSE;

      break;

    case eSysMonFrmEvent:

      // Read CAN signals
      ucPhaseVie      = stData.ucPhaseVie;
      ucInterdMemoDef = stData.ucInterdMemoDef;
      ucDemEffacDef   = (stData.ucDemEffacDef != SYSMON_RX_ZERO_VALUE) ? E_TRUE : E_FALSE;
      ucDiagMux       = (stData.ucDiagMux != SYSMON_RX_ZERO_VALUE) ? E_TRUE : E_FALSE;

      // Set DIAG_MUX_ON in the DEH module
      //DAPI_SetDiagMux(ucDiagMux);
      (void)Rte_Write_SysMon_SetDiagMux(ucDiagMux);

      // Diag Mux on Rte
      sLifePhases.eDiagMuxOnBody = (ucDiagMux != E_FALSE) ? eAuthorization : eNoAuthorization;
      // Diag Mux On Pwt Signal
      SysMon_RxCallbacks_sDiagMuxOnPwtState.boDiagMuxValue = (ucDiagMux != E_FALSE) ? TRUE : FALSE;
      // Set DiagMuxOn Sig quality valid status as true
      SysMon_RxCallbacks_sDiagMuxOnPwtState.boDiagMuxSigStatus = TRUE;

      // Compute Life phases value
      SysMonRx_Callbacks_RangeCheck_PhaseVie(&sLifePhases, ucPhaseVie, &eSigQtyPhaseVie);

      // Compute Faults memorizing forbidden
      sLifePhases.eInterdMemoDef = (ucInterdMemoDef != SYSMON_RX_ZERO_VALUE) ? eMemorisationForbidden : eMemorisationAuthorized;

      // Compute Global fault clearing request
      sLifePhases.eDemEffacDef = (ucDemEffacDef != E_FALSE) ? eClearingRequest : eNoRequest;

      //Check if the API RemoveDE was called 3 times
      if((boDemEfacTrig != FALSE) && (ucDemEffacDef == E_TRUE) && (ucDemEfacCnt < 3u))
      {
        // Verifify if there is a Clear DEM events
        DAPI_RemoveAllDE(ucDemEffacDef);
        ucDemEfacCnt++;
        
        //If the API was called 3 times, go out of function
        if (ucDemEfacCnt == 3u)
        {
          boDemEfacTrig = FALSE;
        }
      }
      else if ((boDemEfacTrig == FALSE) && (ucDemEffacDef != E_TRUE))
      {
        boDemEfacTrig = TRUE; 
        ucDemEfacCnt = 0u;
      }
      else
      {
        // skip clear dtc request
      }

      break;

    case eSysMonFrmTimeOut:
      // Check 2 seconds timeout before setting SigQty to TIMEOUT
      if (SysMonRx_Callbacks_LossFrame_TimerCheck(&boTimerStatus, CANRX_HS6_COMMANDES_VSM_036) == TRUE)
      {
        sLifePhases.ePhaseVie       = eNormalMode;
        sLifePhases.eInterdMemoDef  = eMemorisationForbidden;
        sLifePhases.eDemEffacDef    = eNoRequest;
        sLifePhases.eDiagMuxOnBody  = eNoAuthorization;

        // Set signal quality for RTE port as time-out
        sLifePhases.eSigQty         = SIG_TIMEOUT;
        // Set DiagMuxOn Sig quality valid status as false
        SysMon_RxCallbacks_sDiagMuxOnPwtState.boDiagMuxSigStatus = FALSE;
      };

      // Set signal quality for FuSa reaction as time-out
      eSigQtyPhaseVie = SIG_TIMEOUT;
      break;

    default:
      break;
  }

  // Pass the Signal Quality and Life Phase values to SysMonRx_ASIL for LifePhase State Interface evaluation
  SysMonRx_Callbacks_sLifePhaseSignal.eLifePhaseValue  = sLifePhases.ePhaseVie;
  SysMonRx_Callbacks_sLifePhaseSignal.eLifePhaseSigQty = eSigQtyPhaseVie;

  (void)Rte_Write_SysMon_LifePhases(&sLifePhases);
}



//-----------------------------------------------------------------------------
/// \brief SysMon_RxCallbacks_HS6_DAT_BSI_432
///
/// \descr Handling of 0x432 receive CAN frame
///
/// \param  eSysMonRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SysMon_RxCallbacks_HS6_DAT_BSI_432(teSysMon_RxFrameState eSysMonRxState)
{
  uint8  ucVESMainState         = 0u;
  uint8  ucElectricNetworkState = 0u;

  teRte_SigQty eSigQtyVESMainState = SIG_INIT;

  //DAPI_TE_MainStatus        eVESMainState = 0; // not needed anymore, see [LDMO-2182]
  tsRte_SysMon_VehNetState  sVehNetState = { 0 };
  STATIC_UT(boolean, boTimerStatus, FALSE);

  tHS6_DAT_BSI_432 stData;
  (void)Rte_Read_SigPrep_HS6_DAT_BSI_432_Received(&stData);

  boTimerStatus = (eSysMonRxState != eSysMonFrmTimeOut) ? FALSE : boTimerStatus;

  sVehNetState.eSigQty = SIG_INIT; //Initialise the structure

  (void)Rte_Read_SysMon_VehNetState(&sVehNetState);

  switch (eSysMonRxState)
  {
    case eSysMonFrameInit:
      // Set signal quality for RTE port as SNA
      sVehNetState.eSigQty = SIG_SNA;
      eSigQtyVESMainState  = SIG_SNA;
      break;

    case eSysMonFrmEvent:
      // Set DTC U014087 - frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_BSI_432_ID, DEM_EVENT_STATUS_PASSED);

      // Read CAN signals
      ucVESMainState          = stData.ucVESMainState;
      ucElectricNetworkState  = stData.ucElectricNetworkState;

      // Compute VES Main State
      eSigQtyVESMainState = SysMonRx_Callbacks_Compute_VESMainState(&sVehNetState, ucVESMainState);

      // Update SEV Main Status in DEH module
      // The state of the contact should not be sent anymore due to change of req [LDMO-2182]
      //DAPI_SetMainStatus(eVESMainState);

      // Compute Electric network state
      SysMonRx_Callbacks_Compute_EletricalNetworkState(&sVehNetState, ucElectricNetworkState);

      // Check DTC for ETAT_PRINCIP_SEV and ETAT_RESEAU_ELEC invalid values
      if ((sVehNetState.eVESMainState == VESState_Invalid) ||
          (sVehNetState.eElectricNetworkState == eInvalid))
      {
        // Set DTC U0140-87 - Ignition invalid data
        Rte_Call_DemPrj_ReportErrorStatus((uint16)IGNITION_INVALID_DATA_432, DEM_EVENT_STATUS_FAILED);
      }
      else
      {
        // Clear DTC U0140-87 - Ignition invalid data
        Rte_Call_DemPrj_ReportErrorStatus((uint16)IGNITION_INVALID_DATA_432, DEM_EVENT_STATUS_PASSED);
      }
      break;

    case eSysMonFrmTimeOut:
      // Check 2 seconds timeout before setting SigQty to TIMEOUT
      if (SysMonRx_Callbacks_LossFrame_TimerCheck(&boTimerStatus, CANRX_HS6_DAT_BSI_432) == TRUE)
      {
        sVehNetState.eVESMainState          = VESState_Start;
        sVehNetState.eElectricNetworkState  = eInvalid;

        // Set signal quality for RTE port as time-out
        sVehNetState.eSigQty = SIG_TIMEOUT;
        // Set DTC U014087 - frame lost
        Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DAT_BSI_432_ID, DEM_EVENT_STATUS_FAILED);
      };

      // Set signal quality for FuSa reaction as time-out
      eSigQtyVESMainState = SIG_TIMEOUT;

      break;

    default:
      break;
  }

  // Pass the Signal Quality to SysMonRx_ASIL for VESMainState State Interface evaluation
  SysMonRx_Callbacks_eVESMainStateSignal = eSigQtyVESMainState;
  SysMonRx_Callbacks_boTiDegarde = ((sVehNetState.eElectricNetworkState == eTI_DEGRADE) || (sVehNetState.eElectricNetworkState == eTI_DISPO_DEM)) ? TRUE : FALSE;

  (void)Rte_Write_SysMon_VehNetState(&sVehNetState);
}


//-----------------------------------------------------------------------------
/// \brief SysMon_RxCallbacks_HS6_DYN_ABR_38D
///
/// \descr Handling of 0x38D receive CAN frame
///
/// \param  eSysMonRxState: Callback event [Frame Update, TimeOut, Init, Crc or Cnt Fail]
///
/// \return void
//-----------------------------------------------------------------------------
void SysMon_RxCallbacks_HS6_DYN_ABR_38D(teSysMon_RxFrameState eSysMonRxState)
{
  uint8                      ucVehicleSpeedDispo = 0u;
  tsSysMon_RxSpeedFrmCheck   sFrmSpeedInfo = { 0u, eVvhIndisp_Invalid };
  tsRte_SysMon_VehicleSpeed  sVehSpeed = { 0 };
  tsRte_SysMon_VehNetState   sVehNetState = { 0 };
  teRte_SigQty               eSigQtySpeed = SIG_INIT;
  STATIC_UT(boolean, boTimerStatus, FALSE);

  tHS6_DYN_ABR_38D stData;
  (void)Rte_Read_SigPrep_HS6_DYN_ABR_38D_Received(&stData);
  (void)Rte_Read_SysMon_VehNetState(&sVehNetState); //read ETAT_PRINCIP_SEV

  boTimerStatus = (eSysMonRxState != eSysMonFrmTimeOut) ? FALSE : boTimerStatus;

  sVehSpeed.eSigQty = SIG_INIT; //Initialise the structure

  (void)Rte_Read_SysMon_VehicleSpeed(&sVehSpeed);

  switch (eSysMonRxState)
  {
    case eSysMonFrameInit:
      // Set signal quality for RTE port as SNA
      sVehSpeed.eSigQty    = SIG_SNA;
      sVehSpeed.eSigQtyDbl = SIG_SNA;
      eSigQtySpeed         = SIG_SNA;

      break;

    case eSysMonFrmEvent:
      // Reset DTC U111387 - frame lost
      Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DYN_ABR_38D_ID, DEM_EVENT_STATUS_PASSED);

      // Read CAN signals
      sFrmSpeedInfo.unVehicleSpeed                            = stData.unVehicleSpeed;
      ucVehicleSpeedDispo                                     = stData.ucVehicleSpeedDispo;
      sVehSpeed.eChksumTrmeDynUcFrein.ucChksumTrmeDynUcFrein  = stData.ucChksumTrmeDynUcFrein;
      sVehSpeed.eCptProcess4B38D.ucCptProcess4B38D            = stData.ucCptProcess4B38D;

      // Compute Vehicle speed unavailability flag
      switch (ucVehicleSpeedDispo)
      {
        case SYSMON_RX_VVH_INDISP_AVAILABLE:    { sFrmSpeedInfo.eVehicleSpeedDispo = eVvhIndisp_SpeedInfoAvailable;   }  break;
        case SYSMON_RX_VVH_INDISP_UNAVAILABLE:  { sFrmSpeedInfo.eVehicleSpeedDispo = eVvhIndisp_SpeedInfoUnavailable; }  break;
        default:                                { sFrmSpeedInfo.eVehicleSpeedDispo = eVvhIndisp_Invalid;              }  break;
      }

      // Check signals range
      SysMonRx_Callbacks_RangeCheck_LightDynAbr(&sVehSpeed, sFrmSpeedInfo, &eSigQtySpeed);
      break;

    case eSysMonFrmTimeOut:
      // Check 2 seconds timeout before setting SigQty to TIMEOUT
      if (SysMonRx_Callbacks_LossFrame_TimerCheck(&boTimerStatus, CANRX_HS6_DYN_ABR_38D) == TRUE)
      {
        sVehSpeed.eVehicleSpeed.unVehicleSpeed  = SYSMON_RX_INVALID_VITESSE_VEHICULE_ROUES;
        sVehSpeed.eVehicleSpeedDispo            = eVvhIndisp_Invalid;
        sFrmSpeedInfo.eVehicleSpeedDispo        = eVvhIndisp_Invalid;

        // Set signal quality for RTE port as time-out
        sVehSpeed.eSigQty                       = SIG_TIMEOUT;
        sVehSpeed.eSigQtyDbl                    = SIG_TIMEOUT;

        if (sVehNetState.eVESMainState != VESState_Stop)
        {
          // Set DTC U111387 - frame lost
          Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_DYN_ABR_38D_ID, DEM_EVENT_STATUS_FAILED);
        }
        else
        {
          //do not set any DTC whwn ETAT_PRINCIPE_SEV == STOP
        }
      };

      // Set signal quality for FuSa reaction as time-out
      eSigQtySpeed = SIG_TIMEOUT;

      break;

    default:
      break;
  }

  // Pass the Signal Quality to SysMonRx_ASIL for Speed State Interface evaluation
  SysMonRx_Callbacks_sSpeedSignal.unSpeedValue  = sVehSpeed.eVehicleSpeed.unVehicleSpeed;
  SysMonRx_Callbacks_sSpeedSignal.eSpeedSigQty  = eSigQtySpeed;

  (void)Rte_Write_SysMon_VehicleSpeed(&sVehSpeed);
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_Compute_ConfigVhl
///
/// \descr  Compute Vehicle Configuration Command
///
/// \param  ucConfigVhl  - input signal received on CAN
///
/// \return teRte_ModeConfigVehicle
//-----------------------------------------------------------------------------
STATIC_AL teRte_ModeConfigVehicle SysMonRx_Callbacks_Compute_ConfigVhl(uint8 ucConfigVhl)
{
  teRte_ModeConfigVehicle  eRetConfigVhl = eModeConfigVehicle_Invalid;

  switch (ucConfigVhl)
  {
    case SYSMON_RX_VEHICLE_CONFIG_FITTING:  { eRetConfigVhl = eModeConfigVehicle_Montage;     }  break;
    case SYSMON_RX_VEHICLE_CONFIG_PLANT:    { eRetConfigVhl = eModeConfigVehicle_Usine;       }  break;
    case SYSMON_RX_VEHICLE_CONFIG_CHECK:    { eRetConfigVhl = eModeConfigVehicle_Controle;    }  break;
    case SYSMON_RX_VEHICLE_CONFIG_STORAGE:  { eRetConfigVhl = eModeConfigVehicle_Stockage;    }  break;
    case SYSMON_RX_VEHICLE_CONFIG_CLIENT:   { eRetConfigVhl = eModeConfigVehicle_Client;      }  break;
    case SYSMON_RX_VEHICLE_CONFIG_SHOWROOM: { eRetConfigVhl = eModeConfigVehicle_Showroom;    }  break;
    case SYSMON_RX_VEHICLE_CONFIG_APV:      { eRetConfigVhl = eModeConfigVehicle_AfterMarket; }  break;
    default:                                { eRetConfigVhl = eModeConfigVehicle_Invalid;     }  break;
  }
  return (eRetConfigVhl);
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_Compute_EletricalNetworkState
///
/// \descr  Compute Electrical Network State Command
///
/// \param  ucElecNetState  - input signal received on CAN
///
/// \return teRte_EtatReseauElec
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_Callbacks_Compute_EletricalNetworkState(tsRte_SysMon_VehNetState *psOutputSig, uint8 ucInputSig)
{
  teRte_EtatReseauElec eElecNetState = eInvalid;
  STATIC_UT(boolean, boTimerStatus, FALSE);

  switch (ucInputSig)
  {
    case SYSMON_RX_ETAT_RESEAU_ELEC_TI_NOMINAL:   { eElecNetState = eTI_NOMINAL;   }  break;
    case SYSMON_RX_ETAT_RESEAU_ELEC_TI_DEGRADE:   { eElecNetState = eTI_DEGRADE;   }  break;
    case SYSMON_RX_ETAT_RESEAU_ELEC_TI_DISPO_DEM: { eElecNetState = eTI_DISPO_DEM; }  break;
    case SYSMON_RX_ETAT_RESEAU_ELEC_DEMARRAGE:    { eElecNetState = eDEMARRAGE;    }  break;
    case SYSMON_RX_ETAT_RESEAU_ELEC_REDEMARRAGE:  { eElecNetState = eREDEMARRAGE;  }  break;
    case SYSMON_RX_ETAT_RESEAU_ELEC_TA_NOMINAL:   { eElecNetState = eTA_NOMINAL;   }  break;
    case SYSMON_RX_ETAT_RESEAU_ELEC_TA_DEGRADE:   { eElecNetState = eTA_DEGRADE;   }  break;
    case SYSMON_RX_ETAT_RESEAU_ELEC_TA_SECU:      { eElecNetState = eTA_SECU;      }  break;
    default:                                      { eElecNetState = eInvalid;      }  break;
  }
  
  // Range check the signal
  if (eElecNetState == eInvalid)
  {
    // Check 2 seconds timeout before setting SigQty to INVALID
    if (SysMonRx_Callbacks_LossFrame_TimerCheck(&boTimerStatus, CANRX_ELEC_NET_STATE_ID) == TRUE)
    {
      // Store invalid Electrical Network State value after 2 seconds debounce
      psOutputSig->eElectricNetworkState = eElecNetState;
    };
  }
  else
  {
    // Reset Timer Status
    boTimerStatus = FALSE;

    // Store Electrical Network State value
    psOutputSig->eElectricNetworkState = eElecNetState;
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_Compute_VESMainState
///
/// \descr  Compute VES Main State
///
/// \param  *psOutputSig - output signal after range check
///          ucInputSig  - input signal received on CAN
///
/// \return teRte_SigQty
//-----------------------------------------------------------------------------
STATIC_AL teRte_SigQty SysMonRx_Callbacks_Compute_VESMainState(tsRte_SysMon_VehNetState *psOutputSig, uint8 ucInputSig)
{
  teRte_SigQty          eSigQtyVESMainState = SIG_INIT;
  teRte_EtatPrincipSEV  eVESMainState       = VESState_Stop;

  STATIC_UT(boolean, boTimerStatus, FALSE);

  switch (ucInputSig)
  {
    case SYSMON_RX_ETAT_PRINCIP_SEV_STOP: //Arret
      eVESMainState = VESState_Stop;
      //eVESMainState               = DAPI_E_MS_STOP; // not needed anymore, see [LDMO-2182]

      // Set signal quality for FuSa reaction as valid
      eSigQtyVESMainState = SIG_VALID;
      break;

    case SYSMON_RX_ETAT_PRINCIP_SEV_IGNITION:
      eVESMainState = VESState_Ignition;
      //eVESMainState               = DAPI_E_MS_IGNITION; // not needed anymore, see [LDMO-2182]

      // Set signal quality for FuSa reaction as valid
      eSigQtyVESMainState = SIG_VALID;
      break;

    case SYSMON_RX_ETAT_PRINCIP_SEV_START:
      eVESMainState = VESState_Start;
      //eVESMainState               = DAPI_E_MS_START; // not needed anymore, see [LDMO-2182]

      // Set signal quality for FuSa reaction as valid
      eSigQtyVESMainState = SIG_VALID;
      break;

    default:
      eVESMainState = VESState_Invalid;
      //eVESMainState               = DAPI_E_MS_RESERVED; // not needed anymore, see [LDMO-2182]

      // Set signal quality for FuSa reaction as invalid
      eSigQtyVESMainState = SIG_INVALID;
      break;
  }

  // Range check the signal
  if (eVESMainState == VESState_Invalid)
  {
    // Check 2 seconds timeout before setting SigQty to INVALID
    if (SysMonRx_Callbacks_LossFrame_TimerCheck(&boTimerStatus, CANRX_VES_MAIN_STATE_ID) == TRUE)
    {
      // Store invalid VES Main State value after 2 seconds debounce
      psOutputSig->eVESMainState = eVESMainState;

      // Set signal quality for RTE port as valid
      psOutputSig->eSigQty = SIG_INVALID;
    };
  }
  else
  {
    // Reset Timer Status
    boTimerStatus = FALSE;

    // Store VES Main State value
    psOutputSig->eVESMainState = eVESMainState;

    // Set signal quality for RTE ports as valid
    psOutputSig->eSigQty = SIG_VALID;
  }

  return eSigQtyVESMainState;
}



#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_Compute_AfsMode
///
/// \descr  Compute AFS Mode Command
///
/// \param  *psOutputSig - output signal after range check
///          ucAfsMode   - input signal received on CAN
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_Callbacks_Compute_AfsMode(tsRte_SysMonAfsSignals *psOutputSig, uint8 ucAfsMode)
{
  teRte_Ctrl_AFS  eRetAfsMode = eCtrlAFS_Invalid;
  STATIC_UT(boolean, boTimerStatus, FALSE);

  switch (ucAfsMode)
  {
    case SYSMON_RX_CTRL_AFS_AFS_OFF:          { eRetAfsMode = eCtrlAFS_AfsOff;        }  break;
    case SYSMON_RX_CTRL_AFS_COUNTRY:          { eRetAfsMode = eCtrlAFS_Country;       }  break;
    case SYSMON_RX_CTRL_AFS_MOTORWAY:         { eRetAfsMode = eCtrlAFS_Motorway;      }  break;
    case SYSMON_RX_CTRL_AFS_TOWN:             { eRetAfsMode = eCtrlAFS_Town;          }  break;
    case SYSMON_RX_CTRL_AFS_BAD_WEATHER_LHD:  { eRetAfsMode = eCtrlAFS_BadWeatherLhd; }  break;
    case SYSMON_RX_CTRL_AFS_BAD_WEATHER_RHD:  { eRetAfsMode = eCtrlAFS_BadWeatherRhd; }  break;
    case SYSMON_RX_CTRL_AFS_FOGGY_LHD:        { eRetAfsMode = eCtrlAFS_FoggyLhd;      }  break;
    case SYSMON_RX_CTRL_AFS_FOGGY_RHD:        { eRetAfsMode = eCtrlAFS_FoggyRhd;      }  break;
    default:                                  { eRetAfsMode = eCtrlAFS_Invalid;       }  break;
  }
  
  // Set Signal Quality to Valid/Invalid and Set/Clear DTC for invalid data
  if (eRetAfsMode == eCtrlAFS_Invalid)
  {
    // Check 2 seconds timeout before setting SigQty to INVALID
    if (SysMonRx_Callbacks_LossFrame_TimerCheck(&boTimerStatus, CANRX_AFS_MODE_CMD_ID) == TRUE)
    {
      // Set signal quality factor as invalid
      psOutputSig->eSigQty = SIG_INVALID;

      // Store new value of AFS Command
      psOutputSig->eAfs_Mode = eRetAfsMode;

      // Set DTC U1218-81 - AFS MODE CMD invalid data
      Rte_Call_DemPrj_ReportErrorStatus((uint16)INVALID_DATA_34E, DEM_EVENT_STATUS_FAILED);
    };
  }
  else
  {
    // Reset Timer Status
    boTimerStatus = FALSE;

    // Store new value of AFS Command
    psOutputSig->eAfs_Mode = eRetAfsMode;

    // Set signal quality factor as valid
    psOutputSig->eSigQty = SIG_VALID;

    // Clear DTC U1218-81 - AFS MODE CMD invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)INVALID_DATA_34E, DEM_EVENT_STATUS_PASSED);
  }
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_Compute_GfhbCmd
///
/// \descr  Compute Glare Free High Beam Command
///
/// \param  ucGfhbCmd  - input signal received on CAN
///
/// \return teRte_GfHb_Cmd
//-----------------------------------------------------------------------------
STATIC_AL teRte_GfHb_Cmd SysMonRx_Callbacks_Compute_GfhbCmd(uint8 ucGfhbCmd)
{
  teRte_GfHb_Cmd  eRetGfhbCmd = eGfhbCmd_Off;

  switch (ucGfhbCmd)
  {
    case SYSMON_RX_GFHB_CURTAIN_ACTIVATION:   { eRetGfhbCmd = eGfhbCmd_CurtainAct;   }  break;
    case SYSMON_RX_GFHB_ON:                   { eRetGfhbCmd = eGfhbCmd_On;           }  break;
    case SYSMON_RX_GFHB_CURTAIN_DEACTIVATION: { eRetGfhbCmd = eGfhbCmd_CurtainDeAct; }  break;
    default:                                  { eRetGfhbCmd = eGfhbCmd_Off;          }  break;
  }
  return (eRetGfhbCmd);
}
#endif // CFG_VARIANT_FULL



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_RangeCheck_LightDynAbr
///
/// \descr  Check range of VITESSE_VEHICULE_ROUES and VVH_INDISP signals, validate it and set DTC in case of signal out of range
///
/// \param  *psOutputSig - output signal after range check
///          sInputSig   - input signal received on CAN
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_Callbacks_RangeCheck_LightDynAbr(tsRte_SysMon_VehicleSpeed *psOutputSig, tsSysMon_RxSpeedFrmCheck sInputSig, teRte_SigQty *peSigQty)
{
  // Variable for Checksum over frame 0x38D
  boolean boCrcValidStatus = FALSE;
  // Variable for Process Counter over frame 0x38D
  boolean boProcessCntValid = FALSE;
  // Failure flag for Speed Availability
  boolean boSpeedDispoValid = TRUE;
  // Failure flag for Vehicle Speed value
  boolean boVehicleSpeedValid = TRUE;
  // Check if Speed and Speed Dispo are invalid
  boolean boTimeOutFlag = FALSE;
  // Counter for CHECK_SUM error
  STATIC_UT(uint8, ucCheckSumFrameCounter, 0u);
  // Flag for Setting DTC of CHK_SUM
  STATIC_UT(boolean, boChkSumDTCSet, FALSE);
  // Counter for PROC_COUNTER error
  STATIC_UT(uint8, ucProcCounter, 0u);
  // Flag for Setting DTC of PROC_COUNTER
  STATIC_UT(boolean, boProcCounterDTCSet, FALSE);
  // Counter for valid signal qualifier
  STATIC_UT(uint8, ucValidSigQtyCounter, 0u);

  tHS6_DYN_ABR_38D stData;
  (void)Rte_Read_SigPrep_HS6_DYN_ABR_38D_Received(&stData);

  // Check VvhIndisp signal validity
  if (sInputSig.eVehicleSpeedDispo == eVvhIndisp_SpeedInfoAvailable)
  {
    // Reset Speed Availability Failure flag
    boSpeedDispoValid = TRUE;
  }
  else
  {
    // Set Speed Availability Failure flag
    boSpeedDispoValid = FALSE;
    // Set Signal Quality to Invalid for FuSa reaction
    *peSigQty = SIG_INVALID;
  }

  // Speed Vehicle Availability needs to be sent over RTE port to Dbl
  psOutputSig->eVehicleSpeedDispo = sInputSig.eVehicleSpeedDispo;

  // Check VitesseVehiculeRoues signal validity
  if (SYSMON_RX_INVALID_VITESSE_VEHICULE_ROUES == sInputSig.unVehicleSpeed)
  {
    // Set Vehicle Speed Failure flag
    boVehicleSpeedValid = FALSE;
    // Set Signal Quality to Invalid for FuSa reaction
    *peSigQty = SIG_INVALID;
  }
  else
  {
    // Reset Vehicle Speed Failure flag
    boVehicleSpeedValid = TRUE;
  }

  SysMonRx_Callbacks_aucRaw38DFrame[SYSMONRX_CALLBACKS_38D_RAW_FIRST]   = stData.aucCHKSUM[SYSMONRX_CALLBACKS_38D_RAW_FIRST];
  SysMonRx_Callbacks_aucRaw38DFrame[SYSMONRX_CALLBACKS_38D_RAW_SECOND]  = stData.aucCHKSUM[SYSMONRX_CALLBACKS_38D_RAW_SECOND];
  SysMonRx_Callbacks_aucRaw38DFrame[SYSMONRX_CALLBACKS_38D_RAW_THIRD]   = stData.aucCHKSUM[SYSMONRX_CALLBACKS_38D_RAW_THIRD];
  SysMonRx_Callbacks_aucRaw38DFrame[SYSMONRX_CALLBACKS_38D_RAW_FOURTH]  = stData.aucCHKSUM[SYSMONRX_CALLBACKS_38D_RAW_FOURTH];
  SysMonRx_Callbacks_aucRaw38DFrame[SYSMONRX_CALLBACKS_38D_RAW_FIFTH]   = stData.aucCHKSUM[SYSMONRX_CALLBACKS_38D_RAW_FIFTH];
  SysMonRx_Callbacks_aucRaw38DFrame[SYSMONRX_CALLBACKS_38D_RAW_SIXTH]   = stData.aucCHKSUM[SYSMONRX_CALLBACKS_38D_RAW_SIXTH];
  SysMonRx_Callbacks_aucRaw38DFrame[SYSMONRX_CALLBACKS_38D_RAW_SEVENTH] = stData.aucCHKSUM[SYSMONRX_CALLBACKS_38D_RAW_SEVENTH];
  SysMonRx_Callbacks_aucRaw38DFrame[SYSMONRX_CALLBACKS_38D_RAW_EIGTH]   = stData.aucCHKSUM[SYSMONRX_CALLBACKS_38D_RAW_EIGTH];

  // Check the value of CheckSum over Data (sum of all 4 bit nibble of data + checksum + init value must be 0xF)
  boCrcValidStatus = SysMonRx_Callbacks_CheckSumCheck(SysMonRx_Callbacks_aucRaw38DFrame, sizeof(SysMonRx_Callbacks_aucRaw38DFrame));

  // Check Process Counter (Incremented by each new frame received)
  boProcessCntValid = SysMonRx_Callbacks_ProcessCntCheck(psOutputSig->eCptProcess4B38D.ucCptProcess4B38D);

  // Check performed to confirm if the checksum of the data received is correct to 0xF
  if (boCrcValidStatus == FALSE)
  {
    // Set Signal Quality to CRC error for FuSa reaction
    *peSigQty  = SIG_E2E_CRCERR;
    
    // Increment counter of failed Chk_Sum
    if (ucCheckSumFrameCounter < SYSMONRX_CALLBACKS_INVALID_CHKSUM_NBFRAMES_PASSED)
    {
      ucCheckSumFrameCounter++;
    }
    // After 50 frames passed ( ~2sec) and no DTC was set before, set just once the DTC for HS6_38D_CALC_CHKSUM_ID failed
    else if((ucCheckSumFrameCounter == SYSMONRX_CALLBACKS_INVALID_CHKSUM_NBFRAMES_PASSED) && (boChkSumDTCSet == FALSE))
    {
      // Set DTC U0315-82/83
      Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_38D_CALC_CHKSUM_ID, DEM_EVENT_STATUS_FAILED);

      // Set flag to prevent of setting DTC continously
      boChkSumDTCSet = TRUE;

      // Set Signal Quality to CRC error for other functionalities
      psOutputSig->eSigQty    = SIG_E2E_CRCERR;
      psOutputSig->eSigQtyDbl = SIG_E2E_CRCERR;

      // Set Valid Signal Quality Counter to 50 (40ms x 50 = 2000ms)
      ucValidSigQtyCounter = SYSMONRX_CALLBACKS_INVALID_CHKSUM_NBFRAMES_PASSED;
    }
    else
    {
      //do nothing
    }
  }
  else if (boProcessCntValid == FALSE)
  {
    // Set Signal Quality to Alive Counter error for FuSa reaction
    *peSigQty = SIG_E2E_ALIVEERR;

    // Increment counter of failed Process_Counter
    if (ucProcCounter < SYSMONRX_CALLBACKS_INVALID_PROCCNT_NBFRAMES_PASSED)
    {
      ucProcCounter++;
    }
    // After 50 frames passed ( ~2sec) and no DTC was set before, set just once the DTC for HS6_38D_PROC_COUNTER_ID failed
    else if ((ucProcCounter == SYSMONRX_CALLBACKS_INVALID_PROCCNT_NBFRAMES_PASSED) && (boProcCounterDTCSet == FALSE))
    {
      // Set DTC U0315-82/83
      Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_38D_PROC_COUNTER_ID, DEM_EVENT_STATUS_FAILED);

      // Set flag to prevent of setting DTC continously
      boProcCounterDTCSet = TRUE;

      // Set Signal Quality to Alive Counter error for other functionalities
      psOutputSig->eSigQty    = SIG_E2E_ALIVEERR;
      psOutputSig->eSigQtyDbl = SIG_E2E_ALIVEERR;

      // Set Valid Signal Quality Counter to 50 (40ms x 50 = 2000ms)
      ucValidSigQtyCounter = SYSMONRX_CALLBACKS_INVALID_PROCCNT_NBFRAMES_PASSED;
    }
    else
    {
      //do nothing
    }
  }
  else if (boVehicleSpeedValid == FALSE)
  {
    // wait 2s before setting signal quality t2 Vehicle Speed Invalid
    boTimeOutFlag = SysMonRx_Callbacks_Timeout(TRUE, SYSMONRX_CALLBACKS_SPEED_INVALID, SYSMONRX_CALLBACKS_VEH_SPEED_TIMER);

    if (boTimeOutFlag != FALSE)
    {
      // Set Signal Quality to Invalid
      psOutputSig->eSigQty     = SIG_INVALID;
      psOutputSig->eSigQtyDbl  = SIG_INVALID;

      // Set Valid Signal Quality Counter to 50 (40ms x 50 = 2000ms)
      ucValidSigQtyCounter = SYSMONRX_CALLBACKS_INVALID_SPEED_NBFRAMES_PASSED;

      // Set DTC U121381
      Rte_Call_DemPrj_ReportErrorStatus((uint16)Wheel_vehicle_speed_ID, DEM_EVENT_STATUS_FAILED);
    }
    else
    {
      // keep old SIG Quality Factor
    }
  }
  else if (boSpeedDispoValid == FALSE)
  {
    // wait 2s before setting signal quality t3 Vehicle Speed Availability Invalid
    boTimeOutFlag = SysMonRx_Callbacks_Timeout(TRUE, SYSMONRX_CALLBACKS_SPEED_INVALID, SYSMONRX_CALLBACKS_VVH_DISP_TIMER);

    if (boTimeOutFlag != FALSE)
    {
      // Set Signal Quality to Invalid
      psOutputSig->eSigQty = SIG_INVALID;

      // Set Valid Signal Quality Counter to 50 (40ms x 50 = 2000ms)
      ucValidSigQtyCounter = SYSMONRX_CALLBACKS_INVALID_SPEED_NBFRAMES_PASSED;

      // Set DTC U121381
      Rte_Call_DemPrj_ReportErrorStatus((uint16)Unavailable_speed_ID, DEM_EVENT_STATUS_FAILED);
    }
    else
    {
      // keep old SIG Quality Factor
    }
  }
  else
  {
    // Set Signal Quality to Valid for FuSa interface
    *peSigQty            = SIG_VALID;

    // Store vehicle speed value
    psOutputSig->eVehicleSpeed.unVehicleSpeed = sInputSig.unVehicleSpeed;

    // Reset DTC U121381 - Invalid speed
    Rte_Call_DemPrj_ReportErrorStatus((uint16)Wheel_vehicle_speed_ID, DEM_EVENT_STATUS_PASSED);
    // Reset DTC U121381 - Unavailable speed
    Rte_Call_DemPrj_ReportErrorStatus((uint16)Unavailable_speed_ID, DEM_EVENT_STATUS_PASSED);

    // Reset timers for Invalid Speed and Invalid Speed Availability
    (void)SysMonRx_Callbacks_Timeout(FALSE, SYSMONRX_CALLBACKS_SPEED_INVALID, SYSMONRX_CALLBACKS_VEH_SPEED_TIMER);
    (void)SysMonRx_Callbacks_Timeout(FALSE, SYSMONRX_CALLBACKS_SPEED_INVALID, SYSMONRX_CALLBACKS_VVH_DISP_TIMER);

    // When no error, decrement failed Chk_Sum counter 
    if (ucCheckSumFrameCounter > 0u)
    {
      ucCheckSumFrameCounter--;
    }
    // when no error present for 50 frames(~2sec) and flag for DTC was set, Reset DTC just once
    else if((ucCheckSumFrameCounter == 0u) && (boChkSumDTCSet != FALSE))
    {
      // Clear DTC U0315-82/83
      Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_38D_CALC_CHKSUM_ID, DEM_EVENT_STATUS_PASSED);
      // Reset flag
      boChkSumDTCSet = FALSE;
    }
    else
    {
      //do nothing
    }

    // When no error, decrement failed Process_Counter counter 
    if (ucProcCounter > 0u)
    {
      ucProcCounter--;
    }
    // when no error present for 50 frames(~2sec) and flag for DTC was set, Reset DTC just once
    else if ((ucProcCounter == 0u) && (boProcCounterDTCSet != FALSE))
    {
      // Clear DTC U0315-82/83
      Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_38D_PROC_COUNTER_ID, DEM_EVENT_STATUS_PASSED);
      // Reset flag
      boProcCounterDTCSet = FALSE;
    }
    else
    {
      //do nothing
    }

    // Validate signal quality for Non FuSa activities after 2 seconds (50 x 40 ms)
    if (ucValidSigQtyCounter > 0u)
    {
      ucValidSigQtyCounter--;
    }
    else
    {
      // Set Signal Quality to Valid for Non FuSa activities
      psOutputSig->eSigQty    = SIG_VALID;
      psOutputSig->eSigQtyDbl = SIG_VALID;
      ucValidSigQtyCounter = 0u;
    }
  }
} // PRQA S 5310, 5316, 5330, 5336 1 // Software Architecture - program architecture and readability



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_EvaluateCrcAndAliveDtcs
///
/// \descr  Function to evaluate the CRC and Alive Counter DTCs for frame 0x34E
///
/// \param  eSigQty - Signal Quality of frame 0x34E
/// \param  eOldSigQty - Old Value of Signal Quality of frame 0x34E
///
/// \return teRte_SigQty
//-----------------------------------------------------------------------------
STATIC_AL teRte_SigQty SysMonRx_Callbacks_EvaluateCrcAndAliveDtcs(teRte_SigQty eSigQty, teRte_SigQty eOldSigQty)
{
  // Get old value of Signal Quality
  teRte_SigQty eSigQtyReturn = eOldSigQty;
  // Check if CRC or Alive Counter is invalid
  boolean boTimeOutFlag = FALSE;

  switch (eSigQty)
  {
  case SIG_E2E_CRCERR: 
      // wait 2s before setting signal quality t0 CRC
      boTimeOutFlag = SysMonRx_Callbacks_Timeout(TRUE, SYSMONRX_CALLBACKS_CRCERR_TIMEOUT, SYSMONRX_CALLBACKS_CRCERR_TIMER);

      if (boTimeOutFlag != FALSE)
      {
        eSigQtyReturn = SIG_E2E_CRCERR;

        // Set DTC U131882 - Calculated Checksum  not corresponding with received one in CAN frame 0x34E
        Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_34E_CALC_CHKSUM_ID, DEM_EVENT_STATUS_FAILED);
      }
      else
      {
        // keep old SIG Quality Factor
      }

      // Reset DTC U131882 - Calculated Process Counter not corresponding with received one in CAN frame 0x34E
      Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_34E_PROC_COUNTER_ID, DEM_EVENT_STATUS_PASSED);

      break;
  case SIG_E2E_ALIVEERR: 
      // wait 2s before setting signal quality t1 Alive Counter
      boTimeOutFlag = SysMonRx_Callbacks_Timeout(TRUE, SYSMONRX_CALLBACKS_ALIVEERR_TIMEOUT, SYSMONRX_CALLBACKS_ALIVEERR_TIMER);

      if (boTimeOutFlag != FALSE)
      {
        eSigQtyReturn = SIG_E2E_ALIVEERR;

        // Set DTC U131882 - Calculated Process Counter not corresponding with received one in CAN frame 0x34E
        Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_34E_PROC_COUNTER_ID, DEM_EVENT_STATUS_FAILED);
      }
      else
      {
        // keep old SIG Quality Factor
      }

       // Reset DTC U131882 - Calculated Checksum  not corresponding with received one in CAN frame 0x34E
       Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_34E_CALC_CHKSUM_ID, DEM_EVENT_STATUS_PASSED);

       break;
  case SIG_VALID: 
      // reset timers
      (void)SysMonRx_Callbacks_Timeout(FALSE, SYSMONRX_CALLBACKS_CRCERR_TIMEOUT, SYSMONRX_CALLBACKS_CRCERR_TIMER);
      (void)SysMonRx_Callbacks_Timeout(FALSE, SYSMONRX_CALLBACKS_ALIVEERR_TIMEOUT, SYSMONRX_CALLBACKS_ALIVEERR_TIMER);
      eSigQtyReturn = SIG_VALID;

       // Reset DTC U131882 - Calculated Process Counter not corresponding with received one in CAN frame 0x34E
       Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_34E_PROC_COUNTER_ID, DEM_EVENT_STATUS_PASSED);
       // Reset DTC U131882 - Calculated Checksum  not corresponding with received one in CAN frame 0x34E
       Rte_Call_DemPrj_ReportErrorStatus((uint16)HS6_34E_CALC_CHKSUM_ID, DEM_EVENT_STATUS_PASSED);
      break;
  default: 
      // Nothing to do
      break;
  }
  return eSigQtyReturn;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_Timeout
///
/// \descr  This function returns timer status
///
/// \param  boReqInput, ulTimeMs, scTiTimerSel
///
/// \return uint8
//-----------------------------------------------------------------------------
STATIC_AL boolean SysMonRx_Callbacks_Timeout(CONST_AL boolean boReqInput, CONST_AL TIMER ulTimeMs, CONST_AL uint8 ucTiTimerSel)
{
    boolean boTimerTimeoutStatus = FALSE;
    if (ucTiTimerSel < SYSMONRX_CALLBACKS_NUMBER_OF_TIMERS)
    {
        SysMonRx_Callbacks_sTimerCfg[ucTiTimerSel].ulTimeMs_Input = ulTimeMs;
        SysMonRx_Callbacks_sTimerCfg[ucTiTimerSel].boReq_Input = boReqInput;
        boTimerTimeoutStatus = SysMonRx_Callbacks_HandleDelayStatus(SysMonRx_Callbacks_sTimerCfg, ucTiTimerSel);
    }
    return boTimerTimeoutStatus;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_HandleDelayStatus
///
/// \descr  This function return TimeOut = TRUE based on sTimersCfg Configurations
///
/// \param  *sTimersCfg, scTimerSel
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL boolean SysMonRx_Callbacks_HandleDelayStatus(tsSysMonRx_TimerCfg *psTimersCfg, CONST_AL uint8 ucTimerSel)
{
    // Input request (start timer or reset)
    if (psTimersCfg[ucTimerSel].boReq_Input != FALSE)
    {
        // Start Timer
        if (psTimersCfg[ucTimerSel].boStartStopTimer == FALSE)
        {
            psTimersCfg[ucTimerSel].ulCommandStart = UTILTIME_TIMER_START(UTILTIME_MSEC(psTimersCfg[ucTimerSel].ulTimeMs_Input));
            psTimersCfg[ucTimerSel].boStartStopTimer = TRUE;
        }
    }
    else
    {
        // Reset timer and reinit all timers values
        psTimersCfg[ucTimerSel].boTimeOut = FALSE;
        psTimersCfg[ucTimerSel].boStartStopTimer = FALSE;
        psTimersCfg[ucTimerSel].ulCommandStart = 0u;
    }

    // Timer still running ?
    if (psTimersCfg[ucTimerSel].boStartStopTimer != FALSE)
    {
        // Let it run
        psTimersCfg[ucTimerSel].boTimeOut = UTILTIME_TIMER_TIMEOUT(psTimersCfg[ucTimerSel].ulCommandStart);
    }

    return psTimersCfg[ucTimerSel].boTimeOut;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_Compute_TurnIndicatorCmd
///
/// \descr  Validate the value of the Turn Indicator based on input CAN signals
///
/// \param  ucTiCmd - Turn Indicator command received on CAN frame HS6_DAT_VSM_2AE
///
/// \return uint8   - Turn Indicator valid value
//-----------------------------------------------------------------------------
STATIC_AL uint8 SysMonRx_Callbacks_Compute_TurnIndicatorCmd(uint8 ucTiCmd)
{
  uint8 ucComputedTiCmd = 0u;

  switch (ucTiCmd)
  {
    case SYSMON_RX_TURN_INDICATOR_ON:
      ucComputedTiCmd = SYSMON_TURNINDICATOR_ON;
      break;
    case SYSMON_RX_TURN_INDICATOR_OFF:
      ucComputedTiCmd = SYSMON_TURNINDICATOR_OFF;
      break;
    default:
      ucComputedTiCmd = SYSMON_TURNINDICATOR_INVALID;
      break;
  }

  // Return validated Turn Indicator Command
  return ucComputedTiCmd;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_GetLowBeamSignal
///
/// \descr  Get the Low Beam value and Signal Quality
///
/// \param *pucValue  - Signal Value
/// \param *peSigQty  - Signal Quality
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonRx_Callbacks_GetLowBeamSignal(uint8 *pucValue, teRte_SigQty *peSigQty)
{
  // Return the Low Beam value and Signal Quality
  *pucValue = SysMonRx_Callbacks_sLowBeamSignal.ucLowBeamValue;
  *peSigQty = SysMonRx_Callbacks_sLowBeamSignal.eLowBeamSigQty;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_GetLifePhaseSignal
///
/// \descr  Get the Life Phase value and Signal Quality
///
/// \param *peValue   - Signal Value
/// \param *peSigQty  - Signal Quality
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonRx_Callbacks_GetLifePhaseSignal(teRte_PhaseVie *peValue, teRte_SigQty *peSigQty)
{
  // Return the Life phase value and Signal Quality
  *peValue  = SysMonRx_Callbacks_sLifePhaseSignal.eLifePhaseValue;
  *peSigQty = SysMonRx_Callbacks_sLifePhaseSignal.eLifePhaseSigQty;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_GetSpeedSignal
///
/// \descr  Get the Speed Value and Signal Quality
///
/// \param *punSpeedValue  - Speed Value
/// \param *peSigQty       - Signal Quality
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonRx_Callbacks_GetSpeedSignal(uint16 *punSpeedValue, teRte_SigQty *peSigQty)
{
  // Return the Life phase value and Signal Quality
  *punSpeedValue  = SysMonRx_Callbacks_sSpeedSignal.unSpeedValue;
  *peSigQty       = SysMonRx_Callbacks_sSpeedSignal.eSpeedSigQty;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_GetVESMainStateSignal
///
/// \descr  Get the VESMainState Signal Quality
///
/// \param *peSigQty  - Signal Quality
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonRx_Callbacks_GetVESMainStateSignal(teRte_SigQty *peSigQty)
{
  // Return the VESMainState Signal Quality
  *peSigQty = SysMonRx_Callbacks_eVESMainStateSignal;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_GetTurnIndicatorSignal
///
/// \descr  Get the Turn Indicator value and Signal Quality
///
/// \param *pucValue  - Signal Value
/// \param *peSigQty  - Signal Quality
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonRx_Callbacks_GetTurnIndicatorSignal(uint8 *pucValue, teRte_SigQty *peSigQty)
{
  // Return the Low Beam value and Signal Quality
  *pucValue = SysMonRx_Callbacks_sTurnIndicatorSignal.ucTurnIndicatorValue;
  *peSigQty = SysMonRx_Callbacks_sTurnIndicatorSignal.eTurnIndicatorSigQty;
}

//-----------------------------------------------------------------------------
/// \brief SysMonRx_GetDiagMuxState
///
/// \descr DiagMuxOnPwt Signal Getter (Value and Signal Validity)
///
/// \param *pboValue      - Signal Value
/// \param *pboSigStatus  - Signal Validity
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonRx_Callbacks_GetDiagMuxState(boolean *pboValue)
{
  *pboValue = SysMon_RxCallbacks_sDiagMuxOnPwtState.boDiagMuxValue;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_CheckSumCheck
///
/// \descr  Checks crc of CAN frame 0x38D
///
/// \param  ucRxData    Can frame data
/// \param  ucDLC       Can frame dlc
///
/// \return boolean     TRUE:  CHKSUM I.O.
///                     FALSE: CHKSUM N.I.O.
//-----------------------------------------------------------------------------
STATIC_AL boolean SysMonRx_Callbacks_CheckSumCheck(const uint8 ucRxData[], uint8 ucDLC)
{
  // Variable is returned by function, at start execution it is FALSE
  boolean boChkSumStatus = FALSE;
  // Data counter
  uint8   ucPntData = 0u;
  // Checksum variable
  uint8   ucChkSum = 0u;

  for (ucPntData = 0u; ucPntData < ucDLC; ucPntData++)
  {
    // Add all 4 bit nibble (2 x Can Dlc)
    ucChkSum = (uint8)(ucChkSum + (ucRxData[ucPntData] & SYSMONRX_CALLBACKS_LOWNIBBLE) + ((ucRxData[ucPntData] >> SYSMONRX_CALLBACKS_NIBBLELGTH) & SYSMONRX_CALLBACKS_LOWNIBBLE));
  }
  
  // Checksum + Checksum init value must be 0xF (Req)
  if (((ucChkSum + SYSMONRX_CALLBACKS_CHKINI_38D) & SYSMONRX_CALLBACKS_LOWNIBBLE) == SYSMONRX_CALLBACKS_CHKOK)
  {
    boChkSumStatus = TRUE;
  }
  else
  {
    // boChkSumConfirmed stay FALSE
  }
 
  return boChkSumStatus;
}



//-----------------------------------------------------------------------------
/// \brief  SigPrepRx_ProcessCntCheck
///
/// \descr  checks process counter of a can frame
///
/// \param  ucCmpProc       Actual process counter
///
/// \return boolean     TRUE:  Compteur Process I.O.
///                     FALSE: Compteur Process N.I.O.
//-----------------------------------------------------------------------------
STATIC_AL boolean SysMonRx_Callbacks_ProcessCntCheck(const uint8 ucCmpProc)
{
  STATIC_UT(uint8, ucProccesCounterOld, 0u);
  boolean  boCmpProcConfirmed   = FALSE;

  // First frame for Process counter synchronization
  if (SysMonRx_Callbacks_boFirstFrameRec != FALSE)
  {
    ucProccesCounterOld = (ucCmpProc == 0u) ? 15u : (ucCmpProc - 1u);
    SysMonRx_Callbacks_boFirstFrameRec = FALSE;
  }
  else
  {
    // Since this is not first 38D frame received, skip this
  }

  // Check process counter (Xn = (Xn-1 + 1) mod 16)
  if (ucCmpProc == ((ucProccesCounterOld + 1u) & SYSMONRX_CALLBACKS_LOWNIBBLE))
  {
    boCmpProcConfirmed = TRUE;
  }
  else
  {
    // boCmpProcConfirmed kept FALSE
  }

  // Xn-1 = Xn mod 16
  ucProccesCounterOld = ucCmpProc & SYSMONRX_CALLBACKS_LOWNIBBLE;

  return boCmpProcConfirmed;
}



//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_Hb_Cmd_OtherCond
///
/// \descr  Check conditions in order to activate High Beam or not
///
/// \param  void
///
/// \return boolean     TRUE:  Activate High Beam
///                     FALSE: Do not activate High Beam
//-----------------------------------------------------------------------------
STATIC_AL boolean SysMonRx_Callbacks_Hb_Cmd_OtherCond(void)
{
  tsRte_SigPrep_VehicleConfigSig  sVehConfigSig = { 0 };

  (void)Rte_Read_SigPrep_VehicleConfigSig(&sVehConfigSig);

  /* REQ REQ-0550663 B GFHB - HB/GFHB features for GFHB_HB_MODE = Customer(when MODE_CONFIG_VHL = Client / Control/ Storage / ShowRoom ) */
  return (((sVehConfigSig.eVehicleCfg == eModeConfigVehicle_Client) || (sVehConfigSig.eVehicleCfg == eModeConfigVehicle_Controle) || (sVehConfigSig.eVehicleCfg == eModeConfigVehicle_Stockage) || (sVehConfigSig.eVehicleCfg == eModeConfigVehicle_Showroom)) && (SysMonRx_Callbacks_boTiDegarde != FALSE)) ? TRUE : FALSE;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_RangeCheck_PhaseVie
///
/// \descr  Range check for PHASE_VIE value and set DTC in case of invalid value
///
/// \param  psOutputSig  - Pointer to structure
///         ucPhaseVie   - Phase vie value received on CAN
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_Callbacks_RangeCheck_PhaseVie(tsRte_SysMon_LifePhases *psOutputSig, uint8 ucPhaseVie, teRte_SigQty *pSigQty)
{
  NM_ModeType       eNMMode;

  // Get NM Mode from NM Stack
  eNMMode = SysMonRx_getNMMode();

  switch (ucPhaseVie)
  {
  case SYSMON_RX_PHASE_VIE_STANDBY:

    if (eNMMode == VEILLE)
    {
      psOutputSig->ePhaseVie = eStandBy;
    }
    else
    {
      // forbidden transition , keep last value
    }

    // Set signal quality for RTE port as valid
    psOutputSig->eSigQty = SIG_VALID;
    // Set signal quality for FuSa reaction as valid
    *pSigQty             = SIG_VALID;
    break;

  case SYSMON_RX_PHASE_VIE_NORMAL_MODE:

    if (eNMMode == NM_NORMAL)
    {
      psOutputSig->ePhaseVie = eNormalMode;
    }
    else
    {
      // forbidden transition , keep last value
    }

    // Set signal quality for RTE port as valid
    psOutputSig->eSigQty = SIG_VALID;
    // Set signal quality for FuSa reaction as valid
    *pSigQty             = SIG_VALID;
    break;

  case SYSMON_RX_PHASE_VIE_SWITCH_TO_STANDBY:

    if (eNMMode == MISE_EN_VEILLE)
    {
      psOutputSig->ePhaseVie = eSwitchToStadby;
    }
    else
    {
      // forbidden transition , keep last value
    }

    // Set signal quality for RTE port as valid
    psOutputSig->eSigQty = SIG_VALID;
    // Set signal quality for FuSa reaction as valid
    *pSigQty             = SIG_VALID;
    break;

  case SYSMON_RX_PHASE_VIE_WAKE_UP:

    if (eNMMode == REVEIL)
    {
      psOutputSig->ePhaseVie = eWake;
    }
    else
    {
      // forbidden transition , keep last value
    }

    // Set signal quality for RTE port as valid
    psOutputSig->eSigQty = SIG_VALID;
    // Set signal quality for FuSa reaction as valid
    *pSigQty             = SIG_VALID;
    break;

  case SYSMON_RX_PHASE_VIE_COM_OFF:

    if (eNMMode == COM_OFF)
    {
      psOutputSig->ePhaseVie = eCOM_OFF;
    }
    else
    {
      // forbidden transition , keep last value
    }

    // Set signal quality for RTE port as valid
    psOutputSig->eSigQty = SIG_VALID;
    // Set signal quality for FuSa reaction as valid
    *pSigQty             = SIG_VALID;
    break;

  default:

    psOutputSig->ePhaseVie = eNormalMode;
    // Set signal quality for RTE port as invalid
    psOutputSig->eSigQty   = SIG_INVALID;
    // Set signal quality for FuSa reaction as invalid
    *pSigQty               = SIG_INVALID;
    break;
  }

  // Check DTC for PHASE_VIE invalid value
  if (psOutputSig->eSigQty != SIG_INVALID)
  {
    // Reset DTC U1218-81 - invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)PHASEVIE_INVALID_DATA_036, DEM_EVENT_STATUS_PASSED);
  }
  else
  {
    // Set DTC U1218-81 - invalid data
    Rte_Call_DemPrj_ReportErrorStatus((uint16)PHASEVIE_INVALID_DATA_036, DEM_EVENT_STATUS_FAILED);
  }
}


//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_ResetSigQty
///
/// \descr  Reset Signal Quality factor in case of Sleep Request
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonRx_Callbacks_ResetSigQty(void)
{
  SysMonRx_Callbacks_sLowBeamSignal.eLowBeamSigQty             = SIG_SNA;
  SysMonRx_Callbacks_sSpeedSignal.eSpeedSigQty                 = SIG_SNA;
  SysMonRx_Callbacks_eVESMainStateSignal                       = SIG_SNA;
  SysMonRx_Callbacks_sTurnIndicatorSignal.eTurnIndicatorSigQty = SIG_SNA;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_LossFrame_TimerCheck
///
/// \descr  Check timers in case of loss frame timeout
///
/// \param  pboStartTimer - pointer to start/stop flag
///         ucFrameName   - frame nr. 
///
/// \return teRte_ClusterSubTypeX
//-----------------------------------------------------------------------------
STATIC_AL boolean SysMonRx_Callbacks_LossFrame_TimerCheck(boolean *pboStartTimer, uint8 ucFrameName)
{
  boolean boTimeout = FALSE;

  STATIC_UT(TIMER, ulTimersFrameLost[CANRX_NR_EVENTS], { 0u });

  if (*pboStartTimer == FALSE)
  {
    ulTimersFrameLost[ucFrameName] = UTILTIME_TIMER_START(UTILTIME_MSEC(SYSMON_FS_TIMEOUT_MS));
    *pboStartTimer = TRUE;
  }
  else
  {
    boTimeout = UTILTIME_TIMER_TIMEOUT(ulTimersFrameLost[ucFrameName]);
  }

  return boTimeout;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_UpdateDeactivationStatus
///
/// \descr  Update deactivation status flag
///
/// \param  boDeactStatus - Deactivation Status flag
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonRx_Callbacks_UpdateDeactivationStatus(boolean boDeactStatus)
{
  SysMonRx_Callbacks_boFirstFrameRec = boDeactStatus;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_Compute_AutonomMode
///
/// \descr  Compute the Autonomous Mode
///
/// \param  sAutonomReq - Signals received on CAN frame 0x2AE
///         ucTiReq     - TI CAN signal
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonRx_Callbacks_Compute_AutonomMode(tsRte_SysMonLgtTiReq sAutonomReq, uint8 ucTiReq)
{
  // Set warning mode state
  if ((SysMonRx_Callbacks_eTiWarningMode == eSysMon_PilotedMode) && (SysMonRx_Callbacks_sLifePhaseSignal.eLifePhaseValue == eNormalMode) &&
      (sAutonomReq.eWarning_Mode == eWarningMode_AutonomWarningMode) && (ucTiReq == SYSMON_TURNINDICATOR_OFF))
  {
    SysMonRx_Callbacks_eTiWarningMode = eSysMon_AutonomMode;
  }
  else if ((SysMonRx_Callbacks_eTiWarningMode == eSysMon_AutonomMode) && (SysMonRx_Callbacks_sLifePhaseSignal.eLifePhaseValue == eNormalMode) &&
           (sAutonomReq.eWarning_Mode == eWarningMode_PilotedWarningMode) && (ucTiReq == SYSMON_TURNINDICATOR_ON))
  {
    SysMonRx_Callbacks_eTiWarningMode = eSysMon_PilotedMode;
  }
  else
  {
    // Keep the warning mode state
  }
}


//-----------------------------------------------------------------------------
/// \brief  SysMonRx_Callbacks_Get_AutonomMode
///
/// \descr  Return the Warning Mode
///
/// \param  void
///
/// \return teSysMon_WarningMode
//-----------------------------------------------------------------------------
teSysMon_WarningMode SysMonRx_Callbacks_Get_AutonomMode(void)
{
  return SysMonRx_Callbacks_eTiWarningMode;
}


// EOF
