//*****************************************************************************
// (C) Marelli Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Marelli Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Marelli Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  CtrlDcm_RteAccess.c
///
/// \brief Functions used for the CtrlDcm RTE wrapper, for input/output 
///
//-----------------------------------------------------------------------------


//=============================================================================
// includes
//=============================================================================
#include "CtrlDcm_RteAccess.h"
#include "CtrlDcmSm.h"
#include "ILCU_LevellingAdapter.h" /* ILCU_PORT: replaces DPE-only <Nvm.h> */


//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_RteAccess_Read_EcuSide
///
/// \descr  Read Ecu mounting side from Rte
///
/// \param  eEcuSide - stores Ecu mounting side
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType CtrlDcm_RteAccess_Read_EcuSide(teCtrlDcm_MountingSide* eEcuSide)
{
  Std_ReturnType     ucReturnValue;
  teRte_MountingSide eMountingSide;

  ucReturnValue = Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);

  switch (eMountingSide)
  {
  case eMountedLeft:
    *eEcuSide = CtrlDcm_eMountedLeft;
    break;
  case eMountedRight:
    *eEcuSide = CtrlDcm_eMountedRight;
    break;
  default:
    *eEcuSide = CtrlDcm_eMountedUndef;
    break;
  }

  return ucReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_RteAccess_ReadSpeed
///
/// \descr  reads speed
///
/// \param  boolean * boSpeedInvalid
///
/// \return uint16
//-----------------------------------------------------------------------------
uint16 CtrlDcm_RteAccess_ReadSpeed(boolean * boSpeedInvalid)
{
  tsRte_SysMon_VehicleSpeed                 sSpeedMsg;
  uint16 unCtrlDcmSpeed;

  //receive bb messages
  (void)Rte_Read_SysMon_VehicleSpeed(&sSpeedMsg);  

  if ((sSpeedMsg.eSigQty == SIG_VALID) && (sSpeedMsg.eVehicleSpeedDispo == eVvhIndisp_SpeedInfoAvailable))
  {
    unCtrlDcmSpeed = (uint16)(sSpeedMsg.eVehicleSpeed.unVehicleSpeed);
    *boSpeedInvalid = FALSE;
  }
  else if ((sSpeedMsg.eSigQty == SIG_INVALID) || (sSpeedMsg.eSigQty == SIG_TIMEOUT))
  {
    *boSpeedInvalid = TRUE;
  }
  else
  {
    // keep previous value
  }

  return unCtrlDcmSpeed;

}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_RteAccess_ReadVehicleElectricState
///
/// \descr  reads vechicle electric state
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 CtrlDcm_RteAccess_ReadVehicleElectricState(void)
{
  tsRte_SysMon_VehNetState                 sVechStateMsg;
  uint8 ucCtrlDcmVechElectricState;

  //receive bb messages
  (void)Rte_Read_SysMon_VehNetState(&sVechStateMsg);

  if (sVechStateMsg.eSigQty == SIG_VALID)
  {
    ucCtrlDcmVechElectricState = (uint8)(sVechStateMsg.eElectricNetworkState);
  }
  else if ((sVechStateMsg.eSigQty == SIG_INVALID) || (sVechStateMsg.eSigQty == SIG_TIMEOUT))
  {
    ucCtrlDcmVechElectricState = (uint8)eInvalid;
  }
  else
  {
    // keep previous value
  }

  return ucCtrlDcmVechElectricState;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_RteAccess_ReadVESMainState
///
/// \descr  reads vechicle electric state
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 CtrlDcm_RteAccess_ReadVESMainState(void)
{
  tsRte_SysMon_VehNetState                 sVechStateMsg;
  uint8 ucCtrlDcmVESMainState;

  //receive bb messages
  (void)Rte_Read_SysMon_VehNetState(&sVechStateMsg);

  if (sVechStateMsg.eSigQty == SIG_VALID)
  {
    ucCtrlDcmVESMainState = (uint8)(sVechStateMsg.eVESMainState);
  }
  else if (sVechStateMsg.eSigQty == SIG_TIMEOUT)
  {
    ucCtrlDcmVESMainState = (uint8)VESState_Start; // REQ-0543628 B
  }
  else if (sVechStateMsg.eSigQty == SIG_INVALID)
  {
      ucCtrlDcmVESMainState = (uint8)VESState_Invalid;
  }
  else
  {
    // keep previous value
  }

  return ucCtrlDcmVESMainState;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_RteAccess_VehicleModeConfig
///
/// \descr  reads The state of vehicle configuration
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 CtrlDcm_RteAccess_ReadVehicleModeConfig(void)
{
  tsRte_SigPrep_VehicleConfigSig                 sVehicleConfigSigMsg;
  uint8 ucCtrlDcmVehicleModeCfg;

  //receive bb messages
  (void)Rte_Read_SigPrep_VehicleConfigSig(&sVehicleConfigSigMsg);  

  if (sVehicleConfigSigMsg.eSigQty == SIG_VALID)
  {
    ucCtrlDcmVehicleModeCfg = (uint8)(sVehicleConfigSigMsg.eVehicleCfg);
  }
  else if (sVehicleConfigSigMsg.eSigQty == SIG_SNA)
  {
    // during init the signal is not available and shall be considered invalid (workaround for DIAG_LVL after wakeup)
    ucCtrlDcmVehicleModeCfg = (uint8)eModeConfigVehicle_Invalid;
  }
  else
  {
    ucCtrlDcmVehicleModeCfg = (uint8)eModeConfigVehicle_Invalid2;
  }

  return ucCtrlDcmVehicleModeCfg;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_RteAccess_AvacCommand
///
/// \descr  reads The state of vehicle configuration
///
/// \param  sint16* snVerticalAngle, boolean* boTrainingState, uint8 ucMountingSide
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_RteAccess_ReadAvacCommand(sint16* snVerticalAngle, boolean* boVehAttitudeInvalid, uint8 ucMountingSide)
{
  tPositionOut sPositionOutMsg;

  //receive bb messages
  (void)Rte_Read_ppsAvacStat1Out_Port(&sPositionOutMsg);

  if (sPositionOutMsg.State == (uint8)SIG_VALID)
  {
    *snVerticalAngle      = (sPositionOutMsg.Position[ucMountingSide].Ver);
    *boVehAttitudeInvalid = FALSE;
  }
  else if ((sPositionOutMsg.State == (uint8)SIG_INVALID) || (sPositionOutMsg.State == (uint8)SIG_TIMEOUT))
  {
    *boVehAttitudeInvalid = TRUE;
  }
  else
  {
    // keep current values
  }
}


//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_RteAccess_ReadDriverErrors
///
/// \descr  reads errors sent by CddDcm
///
/// \param  teCtrlDcm_SensorState eSensorState
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_RteAccess_ReadDriverErrors(tsCtrlDcm_ErrorStatus* eErrorState)
{
  tsRte_DcmStatusError ePitchSensorState;

  //receive bb messages
  (void)Rte_Read_CddDcm_ErrorStatus(&ePitchSensorState);

  eErrorState->boElecBAT = ePitchSensorState.boElecBAT;
  eErrorState->boElecGND = ePitchSensorState.boElecGND;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_RteAccess_ReadSensorStatus
///
/// \descr  reads The state of the pitch sensors
///
/// \param  teCtrlDcm_SensorState eSensorState
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_RteAccess_ReadSensorStatus(teCtrlDcm_SensorState* eSensorState)
{
  teRte_HlsSensorState ePitchSensorState;

  //receive bb messages
  (void)Rte_Read_Pitch_PlausState(&ePitchSensorState);

  switch (ePitchSensorState)
  {
  case eNO_FAILURE:     {*eSensorState = CtrlDcm_eHLS_NO_FAILURE;     } break;
  case eSENSOR_FAILURE: {*eSensorState = CtrlDcm_eHLS_SENSOR_FAILURE; } break;
  case eFROZEN_FAILURE: {*eSensorState = CtrlDcm_eHLS_FROZEN_FAILURE; } break;
  case eSTORED_FAILURE: {*eSensorState = CtrlDcm_eHLS_STORED_FAILURE; } break;
  default: break;
  }

  if (NvmBlockDeltaPwmPara.eNVM_VAC_Input == eInput_CAN)
  {
    *eSensorState = CtrlDcm_eHLS_NO_FAILURE;
  }
  else
  {
    // leave previous value
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_RteAccess_LevellingTgtPos
///
/// \descr  reads target position
///
/// \param  tsCtrlDcm_LevellingTgtPos* sLevellingTgtPos
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_RteAccess_ReadLevellingTgtPos(tsCtrlDcm_LevellingTgtPos* sLevellingTgtPos)
{
  tsRte_LevellingTgtPos sLevellingTgtPosMsg;

  //receive bb messages
  (void)Rte_Read_SigPrep_LevellingTgtPos(&sLevellingTgtPosMsg);

  sLevellingTgtPos->eSigQty = (teCtrlDcm_SigQty)(sLevellingTgtPosMsg.eSigQty); // PRQA S 4322 // cast is needed, same signal quality is used

  if (sLevellingTgtPosMsg.eSigQty == SIG_VALID)
  {
    switch (sLevellingTgtPosMsg.eRCmdSignLvl)
    {
    case eSigneConsigneSiteD_Positive: {sLevellingTgtPos->eRCmdSignLvl = CtrlDcm_eSigneConsigneSiteD_Positive; } break;
    case eSigneConsigneSiteD_Negativ:  {sLevellingTgtPos->eRCmdSignLvl = CtrlDcm_eSigneConsigneSiteD_Negativ;  } break;
    default: break;
    }
    sLevellingTgtPos->eRCmdPosLvl.unRCmdPosLvl = sLevellingTgtPosMsg.eRCmdPosLvl.unRCmdPosLvl;
  }
  else
  {
    // only signal quality is needed if not valid
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port
///
/// \descr  reads The state of vehicle configuration
///
/// \param  tsCtrlDcm_LevellingTgtPos* tsLevellingSignals
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_RteAccess_ReadCtrlDcm_MasterCommand_Port(tsCtrlDcm_LevellingTgtPos* tsLevellingSignals)
{
  tsRte_LevellingTgtPos sLevellingTgtPosMsg;

  //receive bb messages
  (void)Rte_Read_CtrlDcm_MasterCommand(&sLevellingTgtPosMsg);

  tsLevellingSignals->eSigQty = (teCtrlDcm_SigQty)sLevellingTgtPosMsg.eSigQty; // PRQA S 4322 // cast is needed, same signal quality is used

  if (sLevellingTgtPosMsg.eSigQty == SIG_VALID)
  {
    switch (sLevellingTgtPosMsg.eRCmdSignLvl)
    {
    case eSigneConsigneSiteD_Positive: {tsLevellingSignals->eRCmdSignLvl = CtrlDcm_eSigneConsigneSiteD_Positive; } break;
    case eSigneConsigneSiteD_Negativ:  {tsLevellingSignals->eRCmdSignLvl = CtrlDcm_eSigneConsigneSiteD_Negativ;  } break;
    default: break;
    }
    tsLevellingSignals->eRCmdPosLvl.unRCmdPosLvl = sLevellingTgtPosMsg.eRCmdPosLvl.unRCmdPosLvl;
  }
  else
  {
    // do nothing
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_RteAccess_Write_DrvLedDiag_Port
///
/// \descr  reads The state of drvled diag port
///
/// \param  boolean boLvlError
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_RteAccess_Write_DrvLedDiag_Port(boolean boLvlError)
{
  tsRte_Hs6_Diag_Drvled_L_457 data          = { 0 };
  teCtrlDcm_MountingSide      eMountingSide = CtrlDcm_ReturnSide();
  boolean                     boParamReady  = CtrlDcm_CodingDataReady(&eMountingSide);
  boolean                     boCondEnabled = CtrlDcm_CondEnabled();
  boolean                     boAslEnabled  = ((boParamReady != FALSE) && (boCondEnabled != FALSE)) ? TRUE : FALSE;

  (void)Rte_Read_DrvLedDiag(&data);

  if (boAslEnabled != FALSE)
  {
    data.eLevellingAdjustFault = (boLvlError == FALSE) ? eDiagLvl_Ok : eDiagLvl_Nok;
  }
  else
  {
    data.eLevellingAdjustFault = eDiagLvl_Ok;
  }

  //receive bb messages
  (void)Rte_Write_DrvLedDiag(&data);

}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_RteAccess_Write_DrvLedDiagR_Port
///
/// \descr  reads The state of drvled diag port
///
/// \param  boolean boLvlError
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_RteAccess_Write_DrvLedDiagR_Port(boolean boLvlError)
{
  tsRte_Hs6_Diag_Drvled_R_477 data          = { 0 };
  teCtrlDcm_MountingSide      eMountingSide = CtrlDcm_ReturnSide();
  boolean                     boParamReady  = CtrlDcm_CodingDataReady(&eMountingSide);
  boolean                     boCondEnabled = CtrlDcm_CondEnabled();
  boolean                     boAslEnabled  = ((boParamReady != FALSE) && (boCondEnabled != FALSE)) ? TRUE : FALSE;

  (void)Rte_Read_DrvLedDiagR(&data);

  if (boAslEnabled != FALSE)
  {
    data.eLevellingAdjustFaultR = (boLvlError == FALSE) ? eDiagLvl_Ok : eDiagLvl_Nok;
  }
  else
  {
    data.eLevellingAdjustFaultR = eDiagLvl_Ok;
  }

  //receive bb messages
  (void)Rte_Write_DrvLedDiagR(&data);

}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_RteAccess_Write_DrvLedDiagR_Port
///
/// \descr  reads The state of drvled diag port
///
/// \param  boolean boLvlError
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_RteAccess_Read_DrvLedDiagR_Port(tsCtrlDcm_LevellingDiagStatus* sLvlError)
{
  tsRte_DcmDiagStatusR data = { 0 };

  (void)Rte_Read_SigPrep_DcmDiagStatusR(&data);

  sLvlError->eSigQty    = (teCtrlDcm_SigQty)data.eSigQty; // PRQA S 4322 // cast is needed, same signal quality is used
  sLvlError->boDiagLvlR = (data.eLevellingAdjustFaultR == eDiagLvl_Nok) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port
///
/// \descr  reads The state of DC Motor master command
///
/// \param  tsCtrlDcm_LevellingTgtPos* tsLevellingSignals
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_RteAccess_WriteCtrlDcm_MasterCommand_Port(tsCtrlDcm_LevellingTgtPos* tsLevellingSignals)
{
  tsRte_LevellingTgtPos sLevellingTgtPosMsg;

  switch (tsLevellingSignals->eRCmdSignLvl)
  {
  case CtrlDcm_eSigneConsigneSiteD_Positive: {sLevellingTgtPosMsg.eRCmdSignLvl = eSigneConsigneSiteD_Positive; } break;
  case CtrlDcm_eSigneConsigneSiteD_Negativ:  {sLevellingTgtPosMsg.eRCmdSignLvl = eSigneConsigneSiteD_Negativ;  } break;
  default: break;
  }
  sLevellingTgtPosMsg.eRCmdPosLvl.unRCmdPosLvl = tsLevellingSignals->eRCmdPosLvl.unRCmdPosLvl;

  //receive bb messages
  (void)Rte_Write_CtrlDcm_MasterCommand(&sLevellingTgtPosMsg);

}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_RteAccess_WriteppCtrlDcmTarget0_DcmTargetValues
///
/// \descr  reads The state of vehicle configuration
///
/// \param  void
///
/// \return uint16
//-----------------------------------------------------------------------------
void CtrlDcm_RteAccess_WriteppCtrlDcmTarget0_DcmTargetValues(tsCtrlDcm_TargetValues* CtrlDcm_TgtAll)
{
  tsRte_CtrlDcmTarget sTargetValues;

  sTargetValues.sDcmTarget.boStop    = CtrlDcm_TgtAll->sDcmTarget.boStop;
  sTargetValues.sDcmTarget.nPosition = CtrlDcm_TgtAll->sDcmTarget.nPosition;

  //write target values
  (void)Rte_Write_ppCtrlDcmTarget0_DcmTargetValues(&sTargetValues);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_RteAccess_ReadCtrlDcm_ActStatDcm_sVal_0
///
/// \descr  reads actual status DC Motor
///
/// \param  tsCtrlDcm_DiagStatus* CtrlDcm_ActStatDcm
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_RteAccess_ReadCtrlDcm_ActStatDcm_sVal_0(tsCtrlDcm_DiagStatus* CtrlDcm_ActStatDcm)
{
  (void)CtrlDcm_ActStatDcm;
  /*tbd for Validation Frames*/
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_RteAccess_WriteCtrlDcm_ActStatDcm_sVal_0
///
/// \descr  writes actual status DC Motor
///
/// \param  tsRte_ActStatDcm0* CtrlDcm_ActStatDcm0
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_RteAccess_WriteCtrlDcm_ActStatDcm_sVal_0(tsCtrlDcm_DiagStatus CtrlDcm_ActStatDcm)
{
  /*tbd for Validation Frames*/
  (void)CtrlDcm_ActStatDcm;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port
///
/// \descr  Write values in the DCM status port
///
/// \param  sStatusParams
///
/// \return [void]
//-----------------------------------------------------------------------------
void CtrlDcm_RteAccess_WriteCtrlDcm_StatusParameters_Port(tsCtrlDcm_DcmStatusParameters* sStatusParams)
{
  tsRte_CtrlDcmStatusParams sStatusParameters;

  if (sStatusParams != NULL_PTR)
  {
    switch (sStatusParams->eASL_MODE)
    {
    case CtrlDcm_eModeUnavailable: {sStatusParameters.eASL_MODE = eDcmModeUnavailable; } break;
    case CtrlDcm_eModeAvailable:   {sStatusParameters.eASL_MODE = eDcmModeAvailable;   } break;
    case CtrlDcm_eModeFrozen:      {sStatusParameters.eASL_MODE = eDcmModeFrozen;      } break;
    case CtrlDcm_eModeFactory:     {sStatusParameters.eASL_MODE = eDcmModeFactory;     } break;
    default: break;
    }

    switch (sStatusParams->eASL_PHASE)
    {
    case CtrlDcm_ePhase_Init: {sStatusParameters.eASL_PHASE = eDcmPhase_Init; } break;
    case CtrlDcm_ePhase_Adj:  {sStatusParameters.eASL_PHASE = eDcmPhase_Adj;  } break;
    case CtrlDcm_ePhase_Fail: {sStatusParameters.eASL_PHASE = eDcmPhase_Fail; } break;
    default: break;
    }

   
    sStatusParameters.snVehAttitudeFactory      = NvmBlockDeltaPwmPara.snVehicleAttitude;
    sStatusParameters.boLvlAdjFunctionalFault_L = sStatusParams->boLvlAdjFunctionalFault_L;
    sStatusParameters.boLvlAdjFunctionalFault_R = sStatusParams->boLvlAdjFunctionalFault_R;
    sStatusParameters.boLvlAdjHeadlampFault     = sStatusParams->boLvlAdjHeadlampFault;
  }
  else
  {
    // use previous values
  }

  (void)Rte_Write_CtrlDcm_StatusParameters_Port(&sStatusParameters);
}

//-----------------------------------------------------------------------------
/// \brief CtrlDcm_RteAccess_ReadDiagDcmControlRoutine
///
/// \descr Get Dcm Routine Control Routine Status
///
/// \param  *psRoutineInfo - Dcm Control routine data inputs
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_RteAccess_ReadDiagDcmControlRoutine(tsCtrlDcm_DcMotorRoutineControl* psRoutineInfo)
{
  // Translation variable from RTE ports
  tsRte_DcMotorRoutineControl sDcmRoutineInfo = { eDcmControl_Unknown, eDcmRightActuator, eDcmMovementToZero, FALSE, FALSE, eDcmDID_Invalid, 0u };

  // Read Diag Control RTE port
  (void)Rte_Read_Dcm_RoutineControl(&sDcmRoutineInfo);

  // Get the info
  // Ack status
  psRoutineInfo->boRequestAckStatus = sDcmRoutineInfo.boRequestAckStatus;
  // Request status
  psRoutineInfo->boRequestStatus = sDcmRoutineInfo.boRequestStatus;
  // Diagnostic Control
  switch (sDcmRoutineInfo.eDcmControl)
  {
  case eDcmControl_Start:   {psRoutineInfo->eDcmControl = CtrlDcm_eDcmControl_Start;   } break;
  case eDcmControl_Stop:    {psRoutineInfo->eDcmControl = CtrlDcm_eDcmControl_Stop;    } break;
  case eDcmControl_Results: {psRoutineInfo->eDcmControl = CtrlDcm_eDcmControl_Results; } break;
  default:                  {psRoutineInfo->eDcmControl = CtrlDcm_eDcmControl_Unknown; } break;
  }
  // Diagnostic Request
  switch (sDcmRoutineInfo.eDcmRequest)
  {
  case eDcmMovementToTop:    {psRoutineInfo->eDcmRequest = CtrlDcm_eMovementToTop;    } break;
  case eDcmMovementToBottom: {psRoutineInfo->eDcmRequest = CtrlDcm_eMovementToBottom; } break;
  case eDcmMovementToZero:   {psRoutineInfo->eDcmRequest = CtrlDcm_eMovementToZero;   } break;
  case eDcmSequence1:        {psRoutineInfo->eDcmRequest = CtrlDcm_eSequence1;        } break;
  case eDcmSequence2:        {psRoutineInfo->eDcmRequest = CtrlDcm_eSequence2;        } break;
  default:                   {psRoutineInfo->eDcmRequest = CtrlDcm_eStop;             } break;
  }
  // Diagnostic side to control
  switch (sDcmRoutineInfo.eDcmSide)
  {
  case eDcmRightActuator: {psRoutineInfo->eDcmSide = CtrlDcm_eRightActuator; } break;
  case eDcmLeftActuator:  {psRoutineInfo->eDcmSide = CtrlDcm_eLeftActuator;  } break;
  case eDcmBothActuators: {psRoutineInfo->eDcmSide = CtrlDcm_eBothActuators; } break;
  default: break;
  }
  // Diagnostic code ID
  switch (sDcmRoutineInfo.eDcmDID)
  {
  case eDD06: {psRoutineInfo->eDcmDID = CtrlDcm_eDD06;    } break;
  default:    {psRoutineInfo->eDcmDID = CtrlDcm_eInvalid; } break;
  }
  // Position request
  psRoutineInfo->ucPosRequest = sDcmRoutineInfo.ucPosRequest;
  // Read sequence start flag
  psRoutineInfo->ucStartSequence = sDcmRoutineInfo.ucStartSequence;
  //PRQA S 5310 1 // STPTH is exceeded due to program architecture and readability
}

//-----------------------------------------------------------------------------
/// \brief CtrlDcm_RteAccess_WriteDcmRoutineAck
///
/// \descr Acknowledge return for Diagnostic routine
///
/// \param  boolean boStatus
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_RteAccess_WriteDcmRoutineAck(boolean boStatus)
{
  // Translation variable from RTE ports
  tsRte_DcMotorRoutineControl sDcmRoutineInfo = { eDcmControl_Unknown, eDcmRightActuator, eDcmMovementToZero, FALSE, FALSE, eDD06, 0u, 0u };

  // Read Diag Control RTE port
  (void)Rte_Read_Dcm_RoutineControl(&sDcmRoutineInfo);

  // Update the Acnowledge status-
  sDcmRoutineInfo.boRequestAckStatus = boStatus;
  sDcmRoutineInfo.boRequestStatus    = FALSE;

  // Write Diag Control RTE port
  (void)Rte_Write_Dcm_RoutineControl(&sDcmRoutineInfo);
}


//-----------------------------------------------------------------------------
/// \brief  CtrlDcm_RteAccess_MapParams
///
/// \descr  Mapps the coding parameter in order to acces the in CtrlDcm
///
/// \param  [void]
///
/// \return [void]
//-----------------------------------------------------------------------------
void CtrlDcm_RteAccess_MapParams(void)
{
  tsRteCodingParameters sCodingParameters;

 //read coding
 (void)Rte_Read_CodM_Pitch_Para(&sCodingParameters);

 CtrlDcm_ParaFct0(sCodingParameters.eCodingState, sCodingParameters.psCodingParameters_Blocks);

}
