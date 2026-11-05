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
/// \file  FctR_TgtPrep.c
///
/// \brief Defines the Signal Preparation functionality of Function Router (FctR).
///        Maps CAN signals to (an internal representation of) light functions.
///
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include "FctR_Cfg.h"
#include "FctR_Types.h"
#include "FctR_Tgt.h"
#include "FctR_Data.h"
#include "FctR_RteAccess.h"
#include "FctR_TgtPrep.h"
#include <Nvm.h>


//=============================================================================
// variables
//=============================================================================

STATIC_AL teFctR_EcuOperationgMode FctR_TgtPrep_eEcuOpMode;
STATIC_AL teFctR_EcuSide           FctR_TgtPrep_eEcuSide;
STATIC_AL teFctr_TiWarningMode     FctR_TgtPrep_eTiWarningMode;
STATIC_AL tsFctR_AfsSignals        FctR_TgtPrep_sAfsSignals;
STATIC_AL boolean                  FctR_TgtPrep_boTiStatus;
STATIC_AL boolean                  FctR_TgtPrep_boTiAutoMode_On;
STATIC_AL boolean                  FctR_TgtPrep_boTiCmd = TRUE;
STATIC_AL boolean                  FctR_TgtPrep_boHBCmd = FALSE;
STATIC_AL boolean                  FctR_TgtPrep_boLBCmd = FALSE;

// Timer for TI blinking in autonomous mode
STATIC_AL tUtilDebounceControl FctR_TgtPrep_sTiAutoModeTimer;
// Timer for delay TI not requested
STATIC_AL tUtilDebounceControl FctR_TgtPrep_TiDelayTimer;
// Requests for Prepared Light Functions
STATIC_AL tsFctR_TgtLgtReq FctR_TgtLgtReqPrep;


#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
//indicate timeout (TRUE) for sbl/cl frame
STATIC_AL boolean FctR_TgtPrep_boClSblTimeOut = FALSE;
//
STATIC_AL teFctR_LightFunctions FctR_eActLgtClSbl = LF_INIT;
STATIC_AL uint8 FctR_ucClSblTargetState = FCTR_CFG_SBL_CL_OFF;
#endif
//=============================================================================
// function prototypes
//=============================================================================

STATIC_AL void FctR_TgtLgt_Prep_Ti(boolean boPosReq, boolean boTiReq, boolean boTiScrollingReq);
STATIC_AL void FctR_TgtLgt_Prep_StdLgtFcts(tsFctR_StdLgtFctsReq sStdLgtFcts);

STATIC_AL boolean FctR_TgtPrep_PklHandling(teFctR_PklReq ePklReq);

STATIC_AL void FctR_TgtPrep_DiagDD00_ResetCmd(boolean boCurrentStatusReq);

STATIC_AL void FctR_TgtPrep_SetTiWarningMode(teFctR_EcuOperationgMode eEcuOpMode, tsFctR_TiReq sTiReq);
STATIC_AL void FctR_TgtLgt_WarningMode_Handling(tsFctR_TiReq sTiReq, boolean* boTiCmd, boolean* boTiScrollingCmd);
STATIC_AL void FctR_TgtLgt_AutonomMode_Handling(boolean* boTiCmd);
STATIC_AL void FctR_TgtLgt_PilotedMode_Handling(tsFctR_TiReq sTiReq, boolean* boTiCmd, boolean* boTiScrollingCmd);
STATIC_AL boolean FctR_TgtPrep_LbLossHandling(boolean boLbReq);

STATIC_AL boolean FctR_TgtPrep_SetTiLgtStatus(boolean boTiReq);

#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
STATIC_AL void FctR_TgtLgt_Prep_Aiming(boolean boAimReq, boolean boHbFlashReq);
STATIC_AL void FctR_TgtLgt_Prep_Lb_Full(boolean boLbReq);
STATIC_AL void FctR_TgtLgt_Prep_Hb_Full(tsFctR_StdLgtFctsReq sStdLgtFcts);
STATIC_AL void FctR_TgtLgt_Prep_ClSbl(boolean boClReq, boolean boSblReq);
#else
STATIC_AL void FctR_TgtLgt_Prep_Lb_Eco(tsFctR_StdLgtFctsReq sStdLgtFcts, boolean boLbReq);
STATIC_AL void FctR_TgtLgt_Prep_Hb_Eco(tsFctR_StdLgtFctsReq sStdLgtFcts);
#endif

//=============================================================================
// functions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtPrep_Init
///
/// \descr  Initialize variables used in FctR_TgtPrep file
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void FctR_TgtPrep_Init(void)
{
  FctR_TgtLgtReqPrep.Req.ulRaw = 0u;
  // Init TI Delay timer and reset the init state to Di_Sna to not start the timer
  UtilDebounceInit(&FctR_TgtPrep_TiDelayTimer, Di_Sna, UTILTIME_MSEC(FctR_GetDelayTiNotRequested()), 0u);
  FctR_TgtPrep_TiDelayTimer.eState = Di_Sna;
  // Init TI Autonomous mode timer and reset the init state to Di_Sna to not start the timer
  UtilDebounceInit(&FctR_TgtPrep_sTiAutoModeTimer, Di_Sna, 0u, UTILTIME_MSEC(FCTR_TI_BLINKING_PHASE));
  FctR_TgtPrep_sTiAutoModeTimer.eState = Di_Sna;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt_Prep_Ti
///
/// \descr  Maps Turn Indicator requests to TI light distributions
///
/// \param  boPosReq          - position light distribution request
///         boTiReq           - turn indicator request command
///         boTiScrollingReq  - scrolling turn indicator request command
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_TgtLgt_Prep_Ti(boolean boPosReq, boolean boTiReq, boolean boTiScrollingReq)
{
  boolean boTiLgtStatus;

  // Variable to store the TI light function status
 
  // Avoid QAC warning for ECO version
  (void)boTiScrollingReq;

  // Clear all TI bits
  FctR_TgtLgtReqPrep.Req.Bits.biTI_TurnIndicator = 0u;
  FctR_TgtLgtReqPrep.Req.Bits.biTI_TiCmdPos = 0u;
  FctR_TgtLgtReqPrep.Req.Bits.biTI_TiReqPos = 0u;

  boTiLgtStatus = FctR_TgtPrep_SetTiLgtStatus(boTiReq);

  if (boTiLgtStatus != FALSE)
  {
    if (boPosReq != FALSE)
    {
      FctR_TgtLgtReqPrep.Req.Bits.biTI_TiCmdPos = 1u;
    }
    else
    {
      FctR_TgtLgtReqPrep.Req.Bits.biTI_TurnIndicator = 1u;
    }
  }

  if (boTiReq != FALSE)
  {
    if (boPosReq != FALSE)
    {
      FctR_TgtLgtReqPrep.Req.Bits.biTI_TiReqPos = 1u;
    }
    else
    {
       
    }
  }
}


//-----------------------------------------------------------------------------
/// \brief  FctR_TgtPrep_SetTiLgtStatus
///
/// \descr  Sets the TI light function status based on TI request
///
/// \param  boTiReq - turn indicator request command
///
/// \return TI light function status: TRUE = active; FALSE = inactive
//-----------------------------------------------------------------------------
STATIC_AL boolean FctR_TgtPrep_SetTiLgtStatus(boolean boTiReq)
{
  // Variable to store the TI light function status
  static boolean boTiLgtStatus = FALSE;

  if (boTiReq != FALSE)
  {
    // Set TI light function status to active
    boTiLgtStatus = TRUE;
    // Reset TI delay timer
    FctR_TgtPrep_TiDelayTimer.eState = Di_Sna;
  }
  else
  {
    // Check timer status
    // When TI request is not active wait for FCTR_DELAY_TI_NOT_REQUESTED ms 
    // to confirm that TI is no more requested
    UtilDebounce(&FctR_TgtPrep_TiDelayTimer, TRUE);
  }

  // Check for timer timout
  if (FctR_TgtPrep_TiDelayTimer.eState == Di_On)
  {
    // Set TI light function status to inactive
    boTiLgtStatus = FALSE;
  }
  else
  {
    // Keep the TI light function status
  }

  return boTiLgtStatus;
}


//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt_Prep_StdLgtFcts
///
/// \descr  Evaluate the value of Standard light distributions signals
///
/// \param  sStdLgtFcts - requests for standard light functions
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_TgtLgt_Prep_StdLgtFcts(tsFctR_StdLgtFctsReq sStdLgtFcts)
{
  boolean boPklReq;
  static boolean boDrlFailMngt = FALSE;
  // Compute parking light request
  boPklReq = FctR_TgtPrep_PklHandling(sStdLgtFcts.ePkl_Req);

  //check ECU operation mode
  if (FctR_TgtPrep_eEcuOpMode == eEcu_NormalMode)
  {
    // Handle DRL and POS only in Normal mode
    boDrlFailMngt = FctR_SpecialBehaviorDrlPos() != FALSE ? TRUE : boDrlFailMngt;

    if ((sStdLgtFcts.boDrl_Req == FALSE) && (boDrlFailMngt != FALSE))
    {
      boDrlFailMngt = FctR_SpecialBehaviorDrlPos();
    }

    FctR_TgtLgtReqPrep.Req.Bits.biDRL_DaytimeRunningLight = (sStdLgtFcts.boDrl_Req == FALSE) ? 0u : ((boDrlFailMngt == FALSE) ? 1u : 0u);
    FctR_TgtLgtReqPrep.Req.Bits.biPOS_PositionLight       = (sStdLgtFcts.eSigQuality != eSig_Valid) ? 1u : ((sStdLgtFcts.boPos_Req != FALSE) ? 1u : 0u);
    FctR_TgtLgtReqPrep.Req.Bits.biPKL_ParkingLight        = (((boPklReq != FALSE) && (sStdLgtFcts.boPos_Req != FALSE) && (sStdLgtFcts.boDrl_Req == FALSE)) ? 1u : 0u);

  }
  else
  {
    // Do not handle DRL and POS in Off mode
    FctR_TgtLgtReqPrep.Req.Bits.biDRL_DaytimeRunningLight = 0u;
    FctR_TgtLgtReqPrep.Req.Bits.biPOS_PositionLight       = (boPklReq != FALSE ? 1u : 0u);
    FctR_TgtLgtReqPrep.Req.Bits.biPKL_ParkingLight        = (boPklReq != FALSE ? 1u : 0u);

  }

  FctR_TgtLgtReqPrep.Req.Bits.biSM_SideMarker           = (sStdLgtFcts.boSideM_Req != FALSE ? 1u : 0u);
#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
  FctR_TgtLgtReqPrep.Req.Bits.biFL_FogLight             = (sStdLgtFcts.boFog_Req != FALSE ? 1u : 0u);
#endif

}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtPrep_PklHandling
///
/// \descr  Compute the Parking Light request
///
/// \param  ePklReq - parking light request received from CAN
///
/// \return boRetVal - computed parking light request
//-----------------------------------------------------------------------------
STATIC_AL boolean FctR_TgtPrep_PklHandling(teFctR_PklReq ePklReq)
{
  // Assume the return value to be FALSE
  boolean boRetVal = FALSE;

  // static variable to track the parking light status
  static teFctR_PklReq ePklStatus = Pkl_Deactivated;

  // Only update ePklStatus if in normal mode
  if (FctR_TgtPrep_eEcuOpMode == eEcu_NormalMode)
  {
    ePklStatus = ePklReq;
  }

  // Simplified condition checking
  if ((FctR_TgtPrep_eEcuSide == eEcu_Left && ePklStatus == Pkl_Left) ||
    (FctR_TgtPrep_eEcuSide == eEcu_Right && ePklStatus == Pkl_Right))
  {
    boRetVal = TRUE;
  }

  return boRetVal;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtPrep_SetTiWarningMode
///
/// \descr  Set turn indicator warning mode
///
/// \param  eEcuOpMode - Ecu operation mode
/// \param  sTiReq     - Turn indicator request signals
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_TgtPrep_SetTiWarningMode(teFctR_EcuOperationgMode eEcuOpMode, tsFctR_TiReq sTiReq)
{
  // Set warning mode state
  if ((FctR_TgtPrep_eTiWarningMode == WarningMode_Piloted) && (eEcuOpMode == eEcu_NormalMode) &&
    (sTiReq.eTiWarnMode == WarningMode_Autonom) && (FALSE == sTiReq.boTi_Req)
    )
  {
    FctR_TgtPrep_eTiWarningMode = WarningMode_Autonom;
  }
  else if ((FctR_TgtPrep_eTiWarningMode == WarningMode_Autonom) && (eEcuOpMode == eEcu_NormalMode) &&
    (sTiReq.eTiWarnMode == WarningMode_Piloted) && (sTiReq.boTi_Req != FALSE)
    )
  {
    FctR_TgtPrep_eTiWarningMode = WarningMode_Piloted;
  }
  else
  {
    // Keep the warning mode state
  }
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt_WarningMode_Handling
///
/// \descr  Manage Turn Indicator modes
///
/// \param  sTiReq           - structure with TI signals received from CAN
/// \param  boTiCmd          - buffer to store Turn Indicator command
/// \param  boTiScrollingCmd - buffer to store TI Scrolling command
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_TgtLgt_WarningMode_Handling(tsFctR_TiReq sTiReq, boolean* boTiCmd, boolean* boTiScrollingCmd)
{
  if (FctR_TgtPrep_eTiWarningMode == WarningMode_Autonom)
  {
    FctR_TgtLgt_AutonomMode_Handling(boTiCmd);
  }
  else
  {
    FctR_TgtLgt_PilotedMode_Handling(sTiReq, boTiCmd, boTiScrollingCmd);
  }
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt_AutonomMode_Handling
///
/// \descr  Handles the TI Autonomous mode
///
/// \param  boTiCmd - buffer to store Turn Indicator command
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_TgtLgt_AutonomMode_Handling(boolean* boTiCmd)
{
  if (FctR_TgtPrep_boTiStatus != FALSE)
  {
    // Start autonomous mode with TI in low state
    if (FctR_TgtPrep_boTiAutoMode_On == FALSE)
    {
      *boTiCmd = FALSE;
      FctR_TgtPrep_boTiAutoMode_On = TRUE;
    }

    // Check timer status
    UtilDebounce(&FctR_TgtPrep_sTiAutoModeTimer, FALSE);

    if (FctR_TgtPrep_sTiAutoModeTimer.eState == Di_Off)
    {
      // Toggle turn indicator command when timeout
      *boTiCmd ^= TRUE;
      // Reset autonomous mode timer
      FctR_TgtPrep_sTiAutoModeTimer.eState = Di_Sna;
    }
    else
    {
      // Keep turn indicator command
    }
  }
  else
  {
    // Do not control the TI if Etat_Clignotants is not active
    *boTiCmd = FALSE;
  }
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt_PilotedMode_Handling
///
/// \descr  Handles the TI Piloted mode
///
/// \param  sTiReq           - structure with TI signals received from CAN
/// \param  boTiCmd          - buffer to store Turn Indicator command
/// \param  boTiScrollingCmd - buffer to store TI Scrolling command
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_TgtLgt_PilotedMode_Handling(tsFctR_TiReq sTiReq, boolean* boTiCmd, boolean* boTiScrollingCmd)
{
  // Get Turn Indicator command
  *boTiCmd = (sTiReq.boTi_Req != FALSE ? TRUE : FALSE);
#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
  // Get TI Scrolling command an keep the last value from Piloted Mode
  *boTiScrollingCmd = (sTiReq.boTiScrolling_Req != FALSE ? TRUE : FALSE);
#else
  *boTiScrollingCmd = FALSE;
#endif

  // Keep the last value of TI Status in Piloted Mode
  if (((FctR_TgtPrep_eEcuSide == eEcu_Left) && (sTiReq.eTiStatus == Ti_ActiveLeft)) ||
    ((FctR_TgtPrep_eEcuSide == eEcu_Right) && (sTiReq.eTiStatus == Ti_ActiveRight)) ||
    (sTiReq.eTiStatus == Ti_ActiveBoth)
    )
  {
    FctR_TgtPrep_boTiStatus = TRUE;
  }
  else
  {
    FctR_TgtPrep_boTiStatus = FALSE;
  }

  FctR_TgtPrep_boTiAutoMode_On = FALSE;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtPrep_GetTiCmdReq
///
/// \descr  Get TurnIndicator command request
///
/// \param  void
///
/// \return Turn indicator command request
//-----------------------------------------------------------------------------
boolean FctR_TgtPrep_GetTiCmdReq(void)
{
  tsRte_Ld_ActivationRoutineControl sLd_Diag;
  
  (void)Rte_Read_Diag_LdActivationRoutineControl(&sLd_Diag);
  
  if (sLd_Diag.boRequestStatus != FALSE)
  {
    FctR_TgtPrep_boTiCmd = ((sLd_Diag.uTgtLgtFct.Bits.biTI_TurnIndicator != 0U) || (sLd_Diag.uTgtLgtFct.Bits.biTI_TiCmdPos != 0U)) ? TRUE : FALSE;
  }

  FctR_TgtPrep_DiagDD00_ResetCmd(sLd_Diag.boRequestStatus);

  return FctR_TgtPrep_boTiCmd;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtPrep_GetTgtLgtReq
///
/// \descr  Get light functions request
///
/// \param  void
///
/// \return Light functions request
//-----------------------------------------------------------------------------
tsFctR_TgtLgtReq FctR_TgtPrep_GetTgtLgtReq(void)
{
  tsRte_Ld_ActivationRoutineControl sLd_Diag;
  
  (void)Rte_Read_Diag_LdActivationRoutineControl(&sLd_Diag);
  
  if (sLd_Diag.boRequestStatus != FALSE)
  {
    FctR_TgtLgtReqPrep.Req.ulRaw = sLd_Diag.uTgtLgtFct.ulRaw;
  }

  FctR_TgtPrep_DiagDD00_ResetCmd(sLd_Diag.boRequestStatus);

  return FctR_TgtLgtReqPrep;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtPrep_DiagDD00_ResetCmd
///
/// \descr  This function reset all lights in case of stop command from DD00 diag serv
///
/// \param  boCurrentStatusReq : diagnostic service request status
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_TgtPrep_DiagDD00_ResetCmd(boolean boCurrentStatusReq)
{
  static boolean boRequestStatus_PrvDiag = FALSE;
  //check if previous request from DD00 was active and now is deactivated
  if ((boRequestStatus_PrvDiag != FALSE) && (boCurrentStatusReq == FALSE))
  {
    boRequestStatus_PrvDiag = FALSE;
    FctR_TgtLgtReqPrep.Req.ulRaw = 0U;
  }

  boRequestStatus_PrvDiag = boCurrentStatusReq;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtPrep_LbLossHandling
///
/// \descr  SysMon is now doing this check
///
/// \param  boLbReq      - low beam request from CAN
///
/// \return Low beam request status (0 = OFF, 1 = ON)
//-----------------------------------------------------------------------------
STATIC_AL boolean FctR_TgtPrep_LbLossHandling(boolean boLbReq)
{
  static boolean boLbReqStatus = FALSE;

    boLbReqStatus = boLbReq;


  return boLbReqStatus;
}


//-----------------------------------------------------------------------------
/// \brief  FctR_TgtPrep_GetAimingMode
///
/// \descr  Get the value of Afs aiming mode
///
/// \param  -
///
/// \return boolean : Aiming Mode activation status
//-----------------------------------------------------------------------------
boolean FctR_TgtPrep_GetAimingMode(void)
{
  tsRte_Ld_ActivationRoutineControl sLd_Diag;
  
  (void)Rte_Read_Diag_LdActivationRoutineControl(&sLd_Diag);
  
  if (sLd_Diag.boRequestStatus != FALSE)
  {
    FctR_TgtPrep_sAfsSignals.boAimingMode_Activation = sLd_Diag.uTgtLgtFct.Bits.biHB_AimingMode;
  }

  FctR_TgtPrep_DiagDD00_ResetCmd(sLd_Diag.boRequestStatus);

  return FctR_TgtPrep_sAfsSignals.boAimingMode_Activation;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtPrep_Get_Hb_Cmd
///
/// \descr  return HB command
///
/// \param  void
///
/// \return boolean : High Beam Command status
//-----------------------------------------------------------------------------
boolean FctR_TgtPrep_Get_Hb_Cmd(void)
{
  return FctR_TgtPrep_boHBCmd;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtPrep_Get_Lb_Cmd
///
/// \descr  return LB command
///
/// \param  void
///
/// \return boolean Low Beam Command status
//-----------------------------------------------------------------------------
boolean FctR_TgtPrep_Get_Lb_Cmd(void)
{
  return FctR_TgtPrep_boLBCmd;
}

#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt_Prep_Aiming
///
/// \descr  Evaluate the value of Aiming Mode Activation request
///
/// \param  boAimReq     - request for Aiming Mode
///         boHbFlashReq - request for High Beam Flash
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_TgtLgt_Prep_Aiming(boolean boAimReq, boolean boHbFlashReq)
{
  // Clear Bit
  FctR_TgtLgtReqPrep.Req.Bits.biHB_AimingMode = 0u;

  if ((boAimReq != FALSE) && (boHbFlashReq == FALSE))
  {
    FctR_TgtLgtReqPrep.Req.Bits.biHB_AimingMode = 1u;
  }
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt_Prep_Lb_Full
///
/// \descr  Evaluate the value of LowBeam light distribution signals for FULL variant
///
/// \param  boLbReq     - request for low beam
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_TgtLgt_Prep_Lb_Full(boolean boLbReq)
{
  // Clear all LB bits
  FctR_TgtLgtReqPrep.Req.Bits.biLB_TownLight             = 0u;
  FctR_TgtLgtReqPrep.Req.Bits.biLB_Pedestrian            = 0u;
  FctR_TgtLgtReqPrep.Req.Bits.biLB_CountryLight          = 0u;
  FctR_TgtLgtReqPrep.Req.Bits.biLB_MotorwayLight         = 0u;
  FctR_TgtLgtReqPrep.Req.Bits.biLB_Boost                 = 0u;
  FctR_TgtLgtReqPrep.Req.Bits.biLB_AdverseWeather_RHD    = 0u;
  FctR_TgtLgtReqPrep.Req.Bits.biFoggyWeather_RHD         = 0u;
  FctR_TgtLgtReqPrep.Req.Bits.biLB_AdverseWeather_LHD    = 0u;
  FctR_TgtLgtReqPrep.Req.Bits.biFoggyWeather_LHD         = 0u;

  if (boLbReq != FALSE)
  {
    // Update requested light distribution based on AfsMode
    switch (FctR_TgtPrep_sAfsSignals.eAfsMode)
    {
      case Afs_Off:
      case Afs_Country:
        FctR_TgtLgtReqPrep.Req.Bits.biLB_CountryLight = 1u;
        break;
      case Afs_Town:
        if (FctR_TgtPrep_sAfsSignals.boPedestrian_Allowed != FALSE)
        {
          FctR_TgtLgtReqPrep.Req.Bits.biLB_Pedestrian = 1u;
        }
        else
        {
          FctR_TgtLgtReqPrep.Req.Bits.biLB_TownLight = 1u;
        }
        break;
      case Afs_Motorway:
        if (FctR_TgtPrep_sAfsSignals.boLbBoost_Allowed != FALSE)
        {
          FctR_TgtLgtReqPrep.Req.Bits.biLB_Boost = 1u;
        }
        else
        {
          FctR_TgtLgtReqPrep.Req.Bits.biLB_MotorwayLight = 1u;
        }
        break;
      case Afs_BadWeather_Lhd:
        FctR_TgtLgtReqPrep.Req.Bits.biLB_AdverseWeather_LHD = 1u;
        break;
      case Afs_BadWeather_Rhd:
        FctR_TgtLgtReqPrep.Req.Bits.biLB_AdverseWeather_RHD = 1u;
        break;
      case Afs_Foggy_Lhd:
        FctR_TgtLgtReqPrep.Req.Bits.biFoggyWeather_LHD = 1u;
        break;
      case Afs_Foggy_Rhd:
        FctR_TgtLgtReqPrep.Req.Bits.biFoggyWeather_RHD = 1u;
        break;
      default:
        FctR_TgtLgtReqPrep.Req.Bits.biLB_CountryLight = 1u;
        break;
    }
  }
  else
  {
    // No low beam light distribution requested
  }
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt_Prep_Hb_Full
///
/// \descr  Evaluate the value of HighBeam light distribution signals
///
/// \param  sStdLgtFcts - standard light functions signals
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_TgtLgt_Prep_Hb_Full(tsFctR_StdLgtFctsReq sStdLgtFcts)
{
  FctR_TgtLgtReqPrep.Req.Bits.biHB_FlashToPass = (sStdLgtFcts.boHbFlash_Req != FALSE) ? 1U : 0U;
  const boolean boGfhbFailure = FctR_RteAccess_Get_FailureGfHB();
  FctR_TgtLgtReqPrep.Req.Bits.biHB_HighBeam = ((sStdLgtFcts.boHb_Req != FALSE) && (sStdLgtFcts.boLb_Req != FALSE) && (boGfhbFailure == FALSE)) ? 1U : 0U;
  const boolean boHbb_Req = FctR_RteAccess_Read_HBB();
  FctR_TgtLgtReqPrep.Req.Bits.biHB_Boost = (boHbb_Req != FALSE) ? 1U : 0U;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt_Prep_ClSbl
///
/// \descr  Evaluate the value of Cornering Light and Static Bending Light signals
///
/// \param  boClReq  - CL  request
///         boSblReq - SBL request
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_TgtLgt_Prep_ClSbl(boolean boClReq, boolean boSblReq)
{
  boolean boCLSblInAfsMode = TRUE;
  FctR_eActLgtClSbl = LF_INIT;
  //FctR_sActClSblDimState.ucTargetState = FCTR_CFG_SBL_CL_OFF;
  //AFS mode selection
  switch (FctR_TgtPrep_GetAfsMode())
  {
  case Afs_Town:
    FctR_eActLgtClSbl = (FctR_TgtPrep_GetAfsPedestrian() != FALSE) ? LB_Pedestrian : LB_TownLight;
    FctR_ucClSblTargetState = (FctR_eActLgtClSbl == LB_Pedestrian) ? FCTR_CFG_SBL_CL_PEDESTRIAN : FCTR_CFG_SBL_CL_TOWN;
    break;
  case Afs_BadWeather_Lhd:
    FctR_eActLgtClSbl = LB_AdverseWeather_LHD;
    FctR_ucClSblTargetState = FCTR_CFG_SBL_CL_BAD_WEATHER;
    break;
  case Afs_BadWeather_Rhd:
    FctR_eActLgtClSbl = LB_AdverseWeather_RHD;
    FctR_ucClSblTargetState = FCTR_CFG_SBL_CL_BAD_WEATHER;
    break;
  case Afs_Foggy_Lhd:
    FctR_eActLgtClSbl = LB_FoggyWeather_LHD;
    FctR_ucClSblTargetState = FCTR_CFG_SBL_CL_FOGGY;
    break;
  case Afs_Foggy_Rhd:
    FctR_eActLgtClSbl = LB_FoggyWeather_RHD;
    FctR_ucClSblTargetState = FCTR_CFG_SBL_CL_FOGGY;
    break;
  default:
    FctR_ucClSblTargetState = FCTR_CFG_SBL_CL_OFF;
    boCLSblInAfsMode = FALSE;
    break;
  }

  if (boSblReq != FALSE)
  {
    FctR_eActLgtClSbl = SBL_StaticBendingLight;
    FctR_ucClSblTargetState = FCTR_CFG_SBL_CL_NOMINAL;
    boCLSblInAfsMode = FALSE;
  }
  else if (boClReq != FALSE)
  {
    FctR_eActLgtClSbl = CL_CorneringLight;
    FctR_ucClSblTargetState = FCTR_CFG_SBL_CL_NOMINAL;
    boCLSblInAfsMode = FALSE;
  }
  else
  {
    //do nothing
  }
  

  FctR_TgtLgtReqPrep.Req.Bits.biSBL_StaticBendingLight = ((boSblReq != FALSE) || ((boCLSblInAfsMode != FALSE) && (FctR_eActLgtClSbl != LF_INIT))) ? 1u : 0u;
  FctR_TgtLgtReqPrep.Req.Bits.biCL_CorneringLight      = ((boClReq  != FALSE) || ((boCLSblInAfsMode != FALSE) && (FctR_eActLgtClSbl != LF_INIT))) ? 1u : 0u;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtPrep_GetClSblTargetState
///
/// \descr  Get the value of Sbl_CL target state
///
/// \param  -
///
/// \return uint8 : SBL/CL target state
//-----------------------------------------------------------------------------
uint8 FctR_TgtPrep_GetClSblTargetState(void)
{
  tsRte_Ld_ActivationRoutineControl sLd_Diag;
  
  (void)Rte_Read_Diag_LdActivationRoutineControl(&sLd_Diag);
  
  if ((sLd_Diag.boRequestStatus != FALSE) && ((sLd_Diag.uTgtLgtFct.Bits.biCL_CorneringLight != 0U) || (sLd_Diag.uTgtLgtFct.Bits.biSBL_StaticBendingLight != 0U)))
  {
    FctR_ucClSblTargetState = FCTR_CFG_SBL_CL_NOMINAL;
  }

  FctR_TgtPrep_DiagDD00_ResetCmd(sLd_Diag.boRequestStatus);

  return FctR_ucClSblTargetState;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtPrep_GetClSbl_AfsLight
///
/// \descr  Get the value of Sbl_CL target state
///
/// \param  -
///
/// \return uint8 : SBL/CL state in AFs mode
//-----------------------------------------------------------------------------
teFctR_LightFunctions FctR_TgtPrep_GetClSbl_AfsLight(void)
{
  tsRte_Ld_ActivationRoutineControl sLd_Diag;
  
  (void)Rte_Read_Diag_LdActivationRoutineControl(&sLd_Diag);
  
  if ((sLd_Diag.boRequestStatus != FALSE) && ((sLd_Diag.uTgtLgtFct.Bits.biCL_CorneringLight != 0U) || (sLd_Diag.uTgtLgtFct.Bits.biSBL_StaticBendingLight != 0U)))
  {
    FctR_eActLgtClSbl = sLd_Diag.uTgtLgtFct.Bits.biCL_CorneringLight != 0U ? CL_CorneringLight : SBL_StaticBendingLight;
  }

  FctR_TgtPrep_DiagDD00_ResetCmd(sLd_Diag.boRequestStatus);

  return FctR_eActLgtClSbl;
}



//-----------------------------------------------------------------------------
/// \brief  FctR_TgtPrep_GetAfsMode
///
/// \descr  Get the value of Afs Mode signal
///
/// \param  -
///
/// \return teFctR_AfsMode : AFS Mode
//-----------------------------------------------------------------------------
teFctR_AfsMode FctR_TgtPrep_GetAfsMode(void)
{
  return FctR_TgtPrep_sAfsSignals.eAfsMode;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtPrep_GetAfsPedestrian
///
/// \descr  Get the value of Afs pedestrian signal
///
/// \param  -
///
/// \return boolean : Pedestrian Light Status Cmd
//-----------------------------------------------------------------------------
boolean FctR_TgtPrep_GetAfsPedestrian(void)
{
  return FctR_TgtPrep_sAfsSignals.boPedestrian_Allowed;
}


//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt_Prep_Full
///
/// \descr  Read data from RTE and set request flags and failure indication flags accordingly.
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void FctR_TgtLgt_Prep_Full(void)
{
  tsFctR_StdLgtFctsReq sStdLgtFctReq;
  tsFctR_TiReq         sTurnIndicatorReq;
  boolean              boClReq, boSblReq, boSblClSigQty, boLbReq;
  static boolean       boTiScrollingCmd;

  // Read Ecu operation mode
  (void)FctR_RteAccess_Read_PhaseVie(&FctR_TgtPrep_eEcuOpMode);
  // Read Ecu mounting side
  (void)FctR_RteAccess_Read_EcuSide(&FctR_TgtPrep_eEcuSide);

  (void)FctR_RteAccess_Read_AfsSignals(&FctR_TgtPrep_sAfsSignals);

  (void)FctR_RteAccess_Read_StdLgtFctReq(&sStdLgtFctReq);

  (void)FctR_RteAccess_Read_TiRequest(&sTurnIndicatorReq);
      
  (void)FctR_RteAccess_Read_ClSblRequest(&boClReq, &boSblReq, &boSblClSigQty);
  

  FctR_TgtPrep_boHBCmd = sStdLgtFctReq.boHb_Req;
  FctR_TgtPrep_boLBCmd = sStdLgtFctReq.boLb_Req;

  FctR_TgtPrep_boClSblTimeOut = boSblClSigQty;

  boLbReq = FctR_TgtPrep_LbLossHandling(sStdLgtFctReq.boLb_Req);
  FctR_TgtPrep_SetTiWarningMode(FctR_TgtPrep_eEcuOpMode, sTurnIndicatorReq);
  FctR_TgtLgt_WarningMode_Handling(sTurnIndicatorReq, &FctR_TgtPrep_boTiCmd, &boTiScrollingCmd);

  FctR_TgtLgt_Prep_Ti(sStdLgtFctReq.boPos_Req, FctR_TgtPrep_boTiCmd, boTiScrollingCmd);
  FctR_TgtLgt_Prep_StdLgtFcts(sStdLgtFctReq);
  FctR_TgtLgt_Prep_Aiming(FctR_TgtPrep_sAfsSignals.boAimingMode_Activation, sStdLgtFctReq.boHbFlash_Req);
  FctR_TgtLgt_Prep_Lb_Full(boLbReq);
  FctR_TgtLgt_Prep_Hb_Full(sStdLgtFctReq);
  FctR_TgtLgt_Prep_ClSbl(boClReq, boSblReq);

  (void)FctR_RteAccess_Write_TiWarningMode(FctR_TgtPrep_eTiWarningMode);

  // PRQA S 5324 1     // Function is maintainable and well-structured
}



//-----------------------------------------------------------------------------
/// \brief  FctR_TgtPrep_SblClTimeOutFrame
///
/// \descr  return Timeout flag for Sbl/Cl frame
///
/// \param  void
///
/// \return boolean : SBL/CL timeout flag
//-----------------------------------------------------------------------------
boolean FctR_TgtPrep_SblClTimeOutFrame(void)
{
  return FctR_TgtPrep_boClSblTimeOut;
}

#else

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt_Prep_Lb_Eco
///
/// \descr  Evaluate the value of LowBeam light distribution signals for ECO variant
///
/// \param  sStdLgtFcts - Structure with standard light requests
///         boLbReq     - low beam light request
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_TgtLgt_Prep_Lb_Eco(tsFctR_StdLgtFctsReq sStdLgtFcts, boolean boLbReq)
{
#if (FCTR_CFG_LSJ_PROX_HB_CAVITY == 1u)

  if ((boLbReq != FALSE) ||
      ((sStdLgtFcts.boHbFlash_Req != FALSE) && (sStdLgtFcts.boHb_Req != FALSE))
     )
  {
    FctR_TgtLgtReqPrep.Req.Bits.biLB_CountryLight = 1u;
  }
  else
  {
    FctR_TgtLgtReqPrep.Req.Bits.biLB_CountryLight = 0u;
  }

#elif (FCTR_CFG_LSJ_PROX_HB_CAVITY == 2u)

  if ((boLbReq != FALSE) || (sStdLgtFcts.boHbFlash_Req != FALSE))
  {
    FctR_TgtLgtReqPrep.Req.Bits.biLB_CountryLight = 1u;
  }
  else
  {
    FctR_TgtLgtReqPrep.Req.Bits.biLB_CountryLight = 0u;
  }

#endif
}

//-----------------------------------------------------------------------------
/// \brief FctR_TgtLgt_Prep_Hb_Eco
///
/// \descr Evaluate the value of HighBeam light distribution signals for ECO variant
///
/// \param sStdLgtFcts - standard light functions signals
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void FctR_TgtLgt_Prep_Hb_Eco(tsFctR_StdLgtFctsReq sStdLgtFcts)
{
  // Create mask containing all HighBeam light distributions
  const tuFctR_LgtFct Mask = { .Bits.biHB_HighBeam = 1u,
                               .Bits.biHB_FlashToPass = 1u,
  };

  // Clear all HB bits
  FctR_TgtLgtReqPrep.Req.ulRaw &= ~Mask.ulRaw;


  if (sStdLgtFcts.boHbFlash_Req != FALSE)
  {
    FctR_TgtLgtReqPrep.Req.Bits.biHB_FlashToPass = 1u;
  }
  else if (sStdLgtFcts.boHb_Req != FALSE)
  {
    FctR_TgtLgtReqPrep.Req.Bits.biHB_HighBeam = (sStdLgtFcts.boLb_Req != FALSE) ? 1U : 0U;
  }
  else
  {
    // No Hb light request
  }
}

//-----------------------------------------------------------------------------
/// \brief  FctR_TgtLgt_Prep_Eco
///
/// \descr  Read data from RTE and set request flags and failure indication flags accordingly.
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void FctR_TgtLgt_Prep_Eco(void)
{
  tsFctR_StdLgtFctsReq sStdLgtFctReq;
  tsFctR_TiReq         sTurnIndicatorReq;
  boolean              boLbReq;
  static boolean       boTiScrollingCmd;

  // Read Ecu operation mode
  (void)FctR_RteAccess_Read_PhaseVie(&FctR_TgtPrep_eEcuOpMode);
  // Read Ecu mounting side
  (void)FctR_RteAccess_Read_EcuSide(&FctR_TgtPrep_eEcuSide);

  (void)FctR_RteAccess_Read_StdLgtFctReq(&sStdLgtFctReq);

  (void)FctR_RteAccess_Read_TiRequest(&sTurnIndicatorReq);
  
  FctR_TgtPrep_boHBCmd = sStdLgtFctReq.boHb_Req;
  FctR_TgtPrep_boLBCmd = sStdLgtFctReq.boLb_Req;

  boLbReq = FctR_TgtPrep_LbLossHandling(sStdLgtFctReq.boLb_Req);
  FctR_TgtPrep_SetTiWarningMode(FctR_TgtPrep_eEcuOpMode, sTurnIndicatorReq);
  FctR_TgtLgt_WarningMode_Handling(sTurnIndicatorReq, &FctR_TgtPrep_boTiCmd, &boTiScrollingCmd);

  FctR_TgtLgt_Prep_Ti(sStdLgtFctReq.boPos_Req, FctR_TgtPrep_boTiCmd, FALSE);
  FctR_TgtLgt_Prep_StdLgtFcts(sStdLgtFctReq);
  FctR_TgtLgt_Prep_Lb_Eco(sStdLgtFctReq, boLbReq);
  FctR_TgtLgt_Prep_Hb_Eco(sStdLgtFctReq);
  
  (void)FctR_RteAccess_Write_TiWarningMode(FctR_TgtPrep_eTiWarningMode);

  // PRQA S 5324 1     // Function is maintainable and well-structured
}

#endif

// EOF
