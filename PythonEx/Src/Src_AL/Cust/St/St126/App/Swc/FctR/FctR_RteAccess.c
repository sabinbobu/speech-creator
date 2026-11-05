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
/// \file  FctR_RteAccess.c
///
/// \brief RTE wrappers for FctR module
///
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include "FctR_RteAccess.h"

//=============================================================================
// function prototypes
//=============================================================================

#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
STATIC_AL teFctR_AfsMode FctR_RteAccess_MapAfsMode(teRte_Ctrl_AFS eAfsMode);
STATIC_AL teFctR_GfHbCmd FctR_RteAccess_MapGfHbSignals(teRte_GfHb_Cmd eGfHbCmd);
STATIC_AL Std_ReturnType FctR_RteAccess_Write_GfHbCmd(teRte_GfHb_Cmd eGfHbCmd);
#endif

STATIC_AL teFctR_TiStatus FctR_RteAccess_MapTiStatus(teRte_EtatClignotants eTiStatus);
//=============================================================================
// functions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_Write_TgtLedsVal
///
/// \descr  Write target LEDs value to Rte port
///
/// \param  pData - pointer to the data structure with target values
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType FctR_RteAccess_Write_TgtLedsVal(tsRte_TgtLedVal0Arr pData)
{
  Std_ReturnType ucReturnValue;

  ucReturnValue = Rte_Write_FctR_TgtLed_sVal(&pData);

  return ucReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_Read_ActLedState
///
/// \descr  Read actual LEDs state from Rte port
///
/// \param  pData - pointer to the data structure with actual state
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType FctR_RteAccess_Read_ActLedState(tsRte_LedErrStateArr *pData)
{
  Std_ReturnType ucReturnValue;

  ucReturnValue = Rte_Read_CtrlLed_ActLed_sState(pData);

  return ucReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_Read_VehNetState
///
/// \descr  Read vehicle state from Rte
///
/// \param  pData - buffer to store vehicle state
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType FctR_RteAccess_Read_VehNetState(tsFctR_VehState *psData)
{
  Std_ReturnType            ucReturnValue;
  tsRte_SysMon_VehNetState  sVehState;

  ucReturnValue = Rte_Read_SysMon_VehNetState(&sVehState);

  if (sVehState.eSigQty == SIG_VALID)
  {
    switch (sVehState.eVESMainState)
    {
    case VESState_Stop:
      psData->eFctR_EtatPrincipSEV = eState_Stop;
      break;
    case VESState_Ignition:
      psData->eFctR_EtatPrincipSEV = eState_Contact;
      break;
    case VESState_Start:
      psData->eFctR_EtatPrincipSEV = eState_Start;
      break;
    default:
      psData->eFctR_EtatPrincipSEV = eState_InvalidSEV;
      break;
    }
    //PRQA S 4322 1 // cast is needed, the enum types are compatible
    psData->eFctR_EtatReseauElec = (teFctR_EtatReseauElec)sVehState.eElectricNetworkState;
  }


  return ucReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_Read_EngineState
///
/// \descr  Read the engine state from Rte
///
/// \param  pData - buffer to store engine state
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType FctR_RteAccess_Read_EngineState(teFctR_EngineState *pData)
{
  Std_ReturnType             ucReturnValue;
  tsRte_SigPrep_ElecSupState sElecSupplyState;

  ucReturnValue = Rte_Read_SigPrep_ElecSupState(&sElecSupplyState);

  switch (sElecSupplyState.eElectrSupplyState)
  {
  case eEtatFee_4_1:
    *pData = eEngineRunning;
    break;
  case eEtatFee_3c_1:
  case eEtatFee_3r_1:
    *pData = eSTT_Phase;
    break;
  default:
    *pData = eInvalid_State;
    break;
  }

  return ucReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_Write_LgtFctState
///
/// \descr  Write light functions state on Rte
///
/// \param  sState - structure with light functions state
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType FctR_RteAccess_Write_LgtFctState(tsFctR_LgtFctState sState)
{
  tsRte_LgtFctState sLgtFctState;
  Std_ReturnType    ucReturnValue;

  sLgtFctState.boDrl_State = sState.bDrl_Diag;
  sLgtFctState.boPos_State = sState.bPos_Diag;
  sLgtFctState.boLb_State = sState.bLb_Diag;
  sLgtFctState.boHb_State = sState.bHb_Diag;
  sLgtFctState.boTi_State = sState.bTi_Diag;

#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
  sLgtFctState.boGfHb_State = sState.bGfHb_Diag;
  sLgtFctState.boSbl_State = sState.bSbl_Diag;
#endif

  ucReturnValue = Rte_Write_FctR_LgtFctState(&sLgtFctState);

  return ucReturnValue;
}

#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_Get_FailureGfHB
///
/// \descr  Read LEDs volt ranges from Rte
///
/// \param  *pucSetVoltageState
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
boolean FctR_RteAccess_Get_FailureGfHB(void)
{
  tAdbOut AlhM_tAdbOut;
  boolean boFailureGfhb;
  (void)Rte_Read_ppsAdb_Out_sVal_4(&AlhM_tAdbOut);

  //6 = FAILURE
  boFailureGfhb = (AlhM_tAdbOut.State == 6U) ? TRUE : FALSE;

  return boFailureGfhb;
}
#endif
//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_Write_LgtFctState
///
/// \descr  Write light functions status on Rte
///
/// \param  uStatus - structure with light functions status
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType FctR_RteAccess_Write_LgtFctStatus(tuFctR_LgtFct uStatus)
{
  tsRte_LgtFctStatus sLgtFctStatus;
  Std_ReturnType     ucReturnValue;



  // Create mask containing all LowBeam light distributions
  const  tuFctR_LgtFct uLbMask = { .Bits.biLB_TownLight = 1u,
                                   .Bits.biLB_Pedestrian = 1u,
                                   .Bits.biLB_CountryLight = 1u,
                                   .Bits.biLB_MotorwayLight = 1u,
                                   .Bits.biLB_Boost = 1u,
                                   .Bits.biLB_AdverseWeather_RHD = 1u,
                                   .Bits.biFoggyWeather_RHD = 1u,
                                   .Bits.biLB_AdverseWeather_LHD = 1u,
                                   .Bits.biFoggyWeather_LHD = 1u
  };



  // Create mask containing all TurnIndicator light distributions
  const tuFctR_LgtFct uTiMask = { .Bits.biTI_TurnIndicator = 1u,
                                  .Bits.biTI_TiCmdPos = 1u,
                                  .Bits.biTI_TiReqPos = 1u,
  };



  // Create mask containing all HighBeam light distributions
  const tuFctR_LgtFct uHbMask = { .Bits.biHB_HighBeam = 1u,
                                                  .Bits.biHB_Boost = 1u,
                                                  .Bits.biHB_FlashToPass = 1u,
  };



  // Create mask containing all HighBeam light distributions
  const tuFctR_LgtFct uSblMask = { .Bits.biSBL_StaticBendingLight = 1u,
                                  .Bits.biCL_CorneringLight = 1u,
  };



  // Set LowBeam status
  sLgtFctStatus.boLb_Status = ((uStatus.ulRaw & uLbMask.ulRaw) != 0u ? TRUE : FALSE);
  // Set TurnIndicator status
  sLgtFctStatus.boTi_Status = ((uStatus.ulRaw & uTiMask.ulRaw) != 0u ? TRUE : FALSE);
  // Set DRL status
  sLgtFctStatus.boDrl_Status = (uStatus.Bits.biDRL_DaytimeRunningLight == 1u ? TRUE : FALSE);
  // Set POS status
  sLgtFctStatus.boPos_Status = (uStatus.Bits.biPOS_PositionLight == 1u ? TRUE : FALSE);
  // Set FOG status
  sLgtFctStatus.boFog_Status = (uStatus.Bits.biFL_FogLight == 1u) ? TRUE : FALSE;
  // Set SM status
  sLgtFctStatus.boSM_Status = (uStatus.Bits.biSM_SideMarker == 1u) ? TRUE : FALSE;
  // Set HB status
  sLgtFctStatus.boGfHb_Status = ((uStatus.ulRaw & uHbMask.ulRaw) != 0u ? TRUE : FALSE);
  //Set SBL status
  sLgtFctStatus.boSbl_Status = ((uStatus.ulRaw & uSblMask.ulRaw) != 0u ? TRUE : FALSE);
  // Set GFHB status
  sLgtFctStatus.boHb_Status = sLgtFctStatus.boGfHb_Status;

  //write rte port
  ucReturnValue = Rte_Write_FctR_LgtFctStatus(&sLgtFctStatus);

  return ucReturnValue;
}


//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_Read_StdLgtFctReq
///
/// \descr  Read standard ligh functions requests
///
/// \param  pData - buffer to store data read from Rte
///
/// \return Std_ReturnType
//----------------------------------------------------------------------------- 
Std_ReturnType FctR_RteAccess_Read_StdLgtFctReq(tsFctR_StdLgtFctsReq *pData)
{
  Std_ReturnType         ucReturnValue;
  tsRte_SysMonLgtFctsReq sStdLgtFctReq;
  teRte_ReqLightState    eLowBeamCmd;

  ucReturnValue = Rte_Read_SysMon_StdLgtFcts_Req(&sStdLgtFctReq);

  (void)Rte_Read_SysMon_LowBeamCmd_Req(&eLowBeamCmd);

  pData->boDrl_Req = (sStdLgtFctReq.eDrl_Request != ReqLighted_Off ? TRUE : FALSE);
  pData->boHbFlash_Req = (sStdLgtFctReq.eHbFlash_Request != ReqLighted_Off ? TRUE : FALSE);
  pData->boHb_Req = (sStdLgtFctReq.eHb_Request != ReqLighted_Off ? TRUE : FALSE);
  pData->boLb_Req = (eLowBeamCmd != ReqLighted_Off ? TRUE : FALSE);
  pData->boPos_Req = (sStdLgtFctReq.ePos_Request != ReqLighted_Off ? TRUE : FALSE);
  pData->boSideM_Req = (sStdLgtFctReq.eSideM_Request != ReqLighted_Off ? TRUE : FALSE);
#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
  pData->boFog_Req = (sStdLgtFctReq.eFog_Request != ReqLighted_Off ? TRUE : FALSE);
#endif

  switch (sStdLgtFctReq.eEtatFeuxStat)
  {
  case eEtatFeuxStationnement_LeftSide:
    pData->ePkl_Req = Pkl_Left;
    break;
  case eEtatFeuxStationnement_RightSide:
    pData->ePkl_Req = Pkl_Right;
    break;
  default:
    pData->ePkl_Req = Pkl_Deactivated;
    break;
  }

  pData->eSigQuality = ((sStdLgtFctReq.eSigQty != SIG_TIMEOUT) && (sStdLgtFctReq.eSigQty != SIG_E2E_CRCERR) && (sStdLgtFctReq.eSigQty != SIG_E2E_ALIVEERR)) ? eSig_Valid : eSig_Invalid;

  return ucReturnValue;
}


#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)

//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_Read_AfsSignals
///
/// \descr  Read Afs signals from Rte
///
/// \param  pData - buffer to store data read from Rte
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType FctR_RteAccess_Read_AfsSignals(tsFctR_AfsSignals *pData)
{
  Std_ReturnType         ucReturnValue;
  tsRte_SysMonAfsSignals sAfsSignals;

  ucReturnValue = Rte_Read_SysMon_Afs_Signals(&sAfsSignals);

  // Map Afs Mode
  pData->eAfsMode = FctR_RteAccess_MapAfsMode(sAfsSignals.eAfs_Mode);
  // Map GfHb command
  pData->eGfHbCmd = FctR_RteAccess_MapGfHbSignals(sAfsSignals.eGfhb_Cmd);

  pData->boLbBoost_Allowed = (sAfsSignals.eLbBoost_Allowed != eLowBeamBoostAllowed_False ? TRUE : FALSE);
  pData->boPedestrian_Allowed = (sAfsSignals.ePedestrian_Allowed != ePedestrianAllowed_False ? TRUE : FALSE);
  pData->boAimingMode_Activation = (sAfsSignals.eAimingMode_Activation != eAimingModeActivation_False ? TRUE : FALSE);

  // Write GfHb command to AdbMxb
  (void)FctR_RteAccess_Write_GfHbCmd(sAfsSignals.eGfhb_Cmd);

  return ucReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_ReadVehicleModeConfig
///
/// \descr  Read VehicleModeConfig from Rte
///
/// \param  pData - buffer to store data read from Rte
///
/// \return teFctR_ModeConfigVehicle
//-----------------------------------------------------------------------------
teFctR_ModeConfigVehicle FctR_RteAccess_ReadVehicleModeConfig(void)
{
  tsRte_SigPrep_VehicleConfigSig                 sVehicleConfigSigMsg;
  teFctR_ModeConfigVehicle eCtrlStpVehicleModeCfg;

  //receive bb messages
  (void)Rte_Read_SigPrep_VehicleConfigSig(&sVehicleConfigSigMsg);

  if (sVehicleConfigSigMsg.eSigQty == SIG_VALID)
  {
    //PRQA S 4322 1 // cast is needed
    eCtrlStpVehicleModeCfg = (teFctR_ModeConfigVehicle)(sVehicleConfigSigMsg.eVehicleCfg);
  }
  else
  {
    //PRQA S 4322 1 // cast is needed
    eCtrlStpVehicleModeCfg = (teFctR_ModeConfigVehicle)(eModeConfigVehicle_Invalid2);
  }

  return eCtrlStpVehicleModeCfg;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_MapAfsMode
///
/// \descr  Maps Afs Mode to local structure
///
/// \param  eInAfsMode - Afs Mode received from Rte
///
/// \return Afs mode mapped to local structure
//-----------------------------------------------------------------------------
STATIC_AL teFctR_AfsMode FctR_RteAccess_MapAfsMode(teRte_Ctrl_AFS eAfsMode)
{
  teFctR_AfsMode eRetVal;

  switch (eAfsMode)
  {
  case eCtrlAFS_AfsOff:
    eRetVal = Afs_Off;
    break;
  case eCtrlAFS_Country:
    eRetVal = Afs_Country;
    break;
  case eCtrlAFS_Town:
    eRetVal = Afs_Town;
    break;
  case eCtrlAFS_Motorway:
    eRetVal = Afs_Motorway;
    break;
  case eCtrlAFS_BadWeatherLhd:
    eRetVal = Afs_BadWeather_Lhd;
    break;
  case eCtrlAFS_BadWeatherRhd:
    eRetVal = Afs_BadWeather_Rhd;
    break;
  case eCtrlAFS_FoggyLhd:
    eRetVal = Afs_Foggy_Lhd;
    break;
  case eCtrlAFS_FoggyRhd:
    eRetVal = Afs_Foggy_Rhd;
    break;
  default:
    // Invalid value
    eRetVal = Afs_Invalid;
    break;
  }

  return eRetVal;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_MapGfHbSignals
///
/// \descr  Maps GfHb command to local structure
///
/// \param  eGfHbCmd - GfHb command received from Rte
///
/// \return GfHb command mapped to local structure
//-----------------------------------------------------------------------------
STATIC_AL teFctR_GfHbCmd FctR_RteAccess_MapGfHbSignals(teRte_GfHb_Cmd eGfHbCmd)
{
  teFctR_GfHbCmd eRetVal = GfHb_Off;

  switch (eGfHbCmd)
  {
  case eGfhbCmd_Off:
    eRetVal = GfHb_Off;
    break;
  case eGfhbCmd_CurtainAct:
    eRetVal = Curtain_Activation;
    break;
  case eGfhbCmd_On:
    eRetVal = GfHb_On;
    break;
  case eGfhbCmd_CurtainDeAct:
    eRetVal = Curtain_Deactivation;
    break;
  default:
    // Invalid value
    break;
  }

  return eRetVal;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_Write_GfHbCmd
///
/// \descr  Write GFHB command to Rte
///
/// \param  eGfHbCmd - GfHb command
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
STATIC_AL Std_ReturnType FctR_RteAccess_Write_GfHbCmd(teRte_GfHb_Cmd eGfHbCmd)
{
  Std_ReturnType ucReturnValue;

  ucReturnValue = Rte_Write_FctR_GfHbCmd(&eGfHbCmd);

  return ucReturnValue;
}

#endif


//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_Read_TiRequest
///
/// \descr  Read TurnIndicator request from Rte
///
/// \param  pData - buffer to store data read from Rte
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType FctR_RteAccess_Read_TiRequest(tsFctR_TiReq *pData)
{
  Std_ReturnType       ucReturnValue;
  tsRte_SysMonLgtTiReq sTiReqSignals;
  teRte_ReqLightState  eTurnIndicatorCmd;

  // Read Rte port
  ucReturnValue = Rte_Read_SysMon_StdLgtTi_Req(&sTiReqSignals);
  (void)Rte_Read_SysMon_TurnIndicatorCmd_Req(&eTurnIndicatorCmd);

  // Update the local structure
#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
  pData->boTiScrolling_Req = sTiReqSignals.eTi_Scrolling != eScrollingTI_Off ? TRUE : FALSE;
#endif
  pData->boTi_Req = eTurnIndicatorCmd != ReqLighted_Off ? TRUE : FALSE;
  pData->eTiWarnMode = (sTiReqSignals.eWarning_Mode != eWarningMode_PilotedWarningMode ? WarningMode_Autonom : WarningMode_Piloted);
  // Map Ti status
  pData->eTiStatus = FctR_RteAccess_MapTiStatus(sTiReqSignals.eEtat_Clignotants);

  return ucReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_MapTiStatus
///
/// \descr  Maps TurnIndicator status to local structure
///
/// \param  eTiStatus - Ti status received from Rte
///
/// \return Ti status mapped to local structure
//-----------------------------------------------------------------------------
STATIC_AL teFctR_TiStatus FctR_RteAccess_MapTiStatus(teRte_EtatClignotants eTiStatus)
{
  teFctR_TiStatus eRetVal = Ti_Inactive;

  switch (eTiStatus)
  {
  case eEtatClignotants_IndicatorInactive:
    eRetVal = Ti_Inactive;
    break;
  case eEtatClignotants_RightIndicatorActive:
    eRetVal = Ti_ActiveRight;
    break;
  case eEtatClignotants_LeftIndicatorActive:
    eRetVal = Ti_ActiveLeft;
    break;
  case eEtatClignotants_LeftAndRightIndicatorActive:
    eRetVal = Ti_ActiveBoth;
    break;
  default:
    // Invalid value
    break;
  }

  return eRetVal;
}

#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)

//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_Read_HBB
///
/// \descr  
///
/// \param  void
///
/// \return High Beam boost status
//-----------------------------------------------------------------------------
boolean FctR_RteAccess_Read_HBB(void)
{
  tAdbStatus sAdbStatus;
  (void)Rte_Read_Adb_StatusOut(&sAdbStatus);
  return sAdbStatus.HBBStatus;
}


//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_Read_ClSblRequest
///
/// \descr  Read CL and SBL request from Rte
///
/// \param  pboClReq  - buffer to store CL  request read from Rte
///         pboSblReq - buffer to store SBL request read from Rte
///         pboSblClSigQty - buffer to store SBL/CL Timeout status from Rte
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType FctR_RteAccess_Read_ClSblRequest(boolean *pboClReq, boolean* pboSblReq, boolean* pboSblClSigQty)
{
  Std_ReturnType           ucReturnValue;
  tsRte_SigPrepLgtClSblReq sClSblReq;

  ucReturnValue = Rte_Read_SigPrep_StdLgtClSbl_Req(&sClSblReq);

  *pboClReq = (sClSblReq.eCl_Request != ReqLighted_Off ? TRUE : FALSE);
  *pboSblReq = (sClSblReq.eSbl_Request != ReqLighted_Off ? TRUE : FALSE);
  *pboSblClSigQty = (sClSblReq.eSigQty == SIG_TIMEOUT) ? TRUE : FALSE;

  return ucReturnValue;
}

#endif


//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_Write_TiWarningMode
///
/// \descr  Write Autonomous Mode value on Rte port
///
/// \param  eTiWarningMode - Autonomous Mode
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType FctR_RteAccess_Write_TiWarningMode(teFctr_TiWarningMode eTiWarningMode)
{
  Std_ReturnType    ucReturnValue;
  teRte_WarningMode eWarningMode;

  eWarningMode = (eTiWarningMode != WarningMode_Piloted) ? eWarningMode_AutonomWarningMode : eWarningMode_PilotedWarningMode;

  ucReturnValue = Rte_Write_FctR_TiWarningMode(&eWarningMode);

  return ucReturnValue;
}

#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)

//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_Write_DblCmd
///
/// \descr  Write target Dbl value on Rte port
///
/// \param  boDblCmd - Dbl activation command
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType FctR_RteAccess_Write_DblCmd(teFctR_DblCommand eDblCmd)
{
  Std_ReturnType  ucReturnValue;
  tsRte_AfsDblCmd sTgtDblVal;

  sTgtDblVal.Primary = (uint8)eDblCmd;

  ucReturnValue = Rte_Write_FctR_AfsDblCmd(&sTgtDblVal);

  return ucReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_Write_AfsMode
///
/// \descr  Write Afs Mode on Rte port
///
/// \param  sTgtLgt          - structure with light functions request
///         eAfsModeReceived - Afs Mode signal receiven on CAN
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType FctR_RteAccess_Write_AfsMode(tsFctR_TgtLgtReq sTgtLgt, teFctR_AfsMode eAfsModeReceived, FctR_eAimingType eAimingMode)
{
  Std_ReturnType        ucReturnValue;
  teRte_AfsModeSig_sVal eAfsMode_Sig;
  tsRte_Ld_ActivationRoutineControl sLd_Diag;

  (void)Rte_Read_Diag_LdActivationRoutineControl(&sLd_Diag);

  if (eAimingMode != eAimingOff)
  {

    switch (eAimingMode)
    {
    case eBlinkOn:
      eAfsMode_Sig = eLb_to_PXA_Adjustment;
      break;

    case eBlinkOff:
      eAfsMode_Sig = eLb_to_PXA_Adjustment_Blink;
      break;

    case eAimOn:
      eAfsMode_Sig = eLb_to_PXA_Adjustment;
      break;

    default:
      break;
    }
  }
  else if ((sTgtLgt.Req.Bits.biLB_CountryLight == 1u) && ((eAfsModeReceived == Afs_Off) || (eAfsModeReceived == Afs_Invalid)))
  {
    eAfsMode_Sig = eLb_to_PXA_CountryLight;
  }
  else if (sTgtLgt.Req.Bits.biLB_TownLight == 1u)
  {
    eAfsMode_Sig = eLb_to_PXA_TownLight;
  }
  else if (sTgtLgt.Req.Bits.biLB_Pedestrian == 1u)
  {
    eAfsMode_Sig = eLb_to_PXA_Pedestrian;
  }
  else if (sTgtLgt.Req.Bits.biLB_CountryLight == 1u)
  {
    eAfsMode_Sig = eLb_to_PXA_CountryLight;
  }
  else if (sTgtLgt.Req.Bits.biLB_MotorwayLight == 1u)
  {
    eAfsMode_Sig = eLb_to_PXA_MotorwayLight;
  }
  else if (sTgtLgt.Req.Bits.biLB_Boost == 1u)
  {
    eAfsMode_Sig = eLb_to_PXA_LB_Boosted;
  }
  else if ((sTgtLgt.Req.Bits.biLB_AdverseWeather_LHD == 1u) && ((eAfsModeReceived == Afs_BadWeather_Lhd) || (sLd_Diag.boRequestStatus != FALSE)))
  {
    eAfsMode_Sig = eLb_to_PXA_BadWeather_Lhd;
  }
  else if ((sTgtLgt.Req.Bits.biLB_AdverseWeather_RHD == 1u) && ((eAfsModeReceived == Afs_BadWeather_Rhd) || (sLd_Diag.boRequestStatus != FALSE)))
  {
    eAfsMode_Sig = eLb_to_PXA_BadWeather_Rhd;
  }
  else if ((sTgtLgt.Req.Bits.biFoggyWeather_LHD == 1u) && ((eAfsModeReceived == Afs_Foggy_Lhd) || (sLd_Diag.boRequestStatus != FALSE)))
  {
    eAfsMode_Sig = eLb_to_PXA_Foggy_Lhd;
  }
  else if ((sTgtLgt.Req.Bits.biFoggyWeather_RHD == 1u) && ((eAfsModeReceived == Afs_Foggy_Rhd) || (sLd_Diag.boRequestStatus != FALSE)))
  {
    eAfsMode_Sig = eLb_to_PXA_Foggy_Rhd;
  }
  else
  {
    eAfsMode_Sig = eLb_to_PXA_AfsOff;
  }

  ucReturnValue = Rte_Write_FctR_AfsModeSig_sVal(&eAfsMode_Sig);

  return ucReturnValue;

  // PRQA S 5336 1     // Mapping to Rte structure OK
}
#endif

//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_Read_EcuSide
///
/// \descr  Read Ecu mounting side from Rte
///
/// \param  eEcuSide - stores Ecu mounting side
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType FctR_RteAccess_Read_EcuSide(teFctR_EcuSide* eEcuSide)
{
  Std_ReturnType     ucReturnValue;
  teRte_MountingSide eMountingSide;

  ucReturnValue = Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);

  switch (eMountingSide)
  {
  case eMountedLeft:
    *eEcuSide = eEcu_Left;
    break;
  case eMountedRight:
    *eEcuSide = eEcu_Right;
    break;
  default:
    *eEcuSide = eEcu_Undef;
    break;
  }

  return ucReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_Read_LedVoltRange
///
/// \descr  Read LEDs volt ranges from Rte
///
/// \param  *pucSetVoltageState
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType FctR_RteAccess_Read_LedVoltRange(uint8 *pucSetVoltageState)
{
  teRte_SysVolt_Results eSetVoltageState;
  Std_ReturnType ucReturnValue;
  ucReturnValue = Rte_Read_SysVolt_LedVoltRng0_sVoltRng(&eSetVoltageState);
  *pucSetVoltageState = (eSetVoltageState == SysVolt_eNormal) ? FCTR_NORMAL_VOLT : \
    (eSetVoltageState == SysVolt_eLow2) ? FCTR_LOW2_VOLT : \
    (eSetVoltageState == SysVolt_eLow1) ? FCTR_LOW1_VOLT : \
    FCTR_UNKNOWN_VOLT;

  return ucReturnValue;
}


//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_Read_PhaseVie
///
/// \descr  Read Ecu operating mode from Rte
///
/// \param  eEcuOpMode - stores Ecu operating mode
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType FctR_RteAccess_Read_PhaseVie(teFctR_EcuOperationgMode* eEcuOpMode)
{
  Std_ReturnType           ucReturnValue;
  tsRte_SysMon_LifePhases  sLifePhases;

  ucReturnValue = Rte_Read_SysMon_LifePhases(&sLifePhases);

  *eEcuOpMode = (sLifePhases.ePhaseVie == eNormalMode ? eEcu_NormalMode : eEcu_OffMode);

  return ucReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_Read_OV_Status
///
/// \descr   get Over voltage status via RTE
///
/// \param  *pboStatus
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType FctR_RteAccess_Read_OV_Status(boolean* pboStatus)
{
  Std_ReturnType           ucReturnValue;
  boolean  boStatus;

  ucReturnValue = Rte_Read_DEM_OV_NotifyStatus(&boStatus);

  *pboStatus = boStatus;

  return ucReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  FctR_RteAccess_Read_UV_Status
///
/// \descr   get Under voltage status via RTE
///
/// \param  *pboStatus
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType FctR_RteAccess_Read_UV_Status(boolean* pboStatus)
{
  Std_ReturnType           ucReturnValue;
  boolean  boStatus;

  ucReturnValue = Rte_Read_DEM_UV_NotifyStatus(&boStatus);

  *pboStatus = boStatus;

  return ucReturnValue;
}

// EOF
