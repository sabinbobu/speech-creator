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
/// \file   LgtFctMgr_RteAccess.c
///
/// \brief  encapsule RTE access
///
/// \descr Functions used for the LgtFctMgr RTE wrapper, for input/output 
///
///
/// \author Catuna Catalin-Lucian F37430C
///         mail to <catalin-lucian.catuna[at]magnetimarelli.com>
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#include <CtrlStp_RteAccess.h>
#include <Nvm.h>


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_Read_EcuSide
///
/// \descr  Read Ecu mounting side from Rte
///
/// \param  eEcuSide - stores Ecu mounting side
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType CtrlStp_RteAccess_Read_EcuSide(teCtrlStp_MountingSide* eEcuSide)
{
  Std_ReturnType     ucReturnValue;
  teRte_MountingSide eMountingSide;

  ucReturnValue = Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);

  switch (eMountingSide)
  {
  case eMountedLeft:
    *eEcuSide = CtrlStp_eMountedLeft;
    break;
  case eMountedRight:
    *eEcuSide = CtrlStp_eMountedRight;
    break;
  default:
    *eEcuSide = CtrlStp_eMountedUndef;
    break;
  }

  return ucReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_ReadSpeed
///
/// \descr  reads speed
///
/// \param  boolean * boSpeedInvalid
///
/// \return uint16
//-----------------------------------------------------------------------------
uint16 CtrlStp_RteAccess_ReadSpeed(boolean * boSpeedInvalid)
{
  tsRte_SysMon_VehicleSpeed                 sSpeedMsg;
  uint16 unCtrlStpSpeed;

  //receive bb messages
  (void)Rte_Read_SysMon_VehicleSpeed(&sSpeedMsg);  

  if (sSpeedMsg.eSigQty == SIG_VALID && sSpeedMsg.eVehicleSpeedDispo == eVvhIndisp_SpeedInfoAvailable)
  {
    //PRQA S 4394 ++  // cast is needed
    unCtrlStpSpeed = (uint16)(sSpeedMsg.eVehicleSpeed.unVehicleSpeed);
    *boSpeedInvalid = FALSE;
  }
  else if ((sSpeedMsg.eSigQty == SIG_INVALID) || (sSpeedMsg.eSigQty == SIG_TIMEOUT) || (sSpeedMsg.eSigQty == SIG_E2E_CRCERR) || (sSpeedMsg.eSigQty == SIG_E2E_ALIVEERR))
  {
    *boSpeedInvalid = TRUE;
  }
  else
  {
    // keep previous value
  }

  return unCtrlStpSpeed;

}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_ReadVehicleElectricState
///
/// \descr  reads vechicle electric state
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 CtrlStp_RteAccess_ReadVehicleElectricState(void)
{
  tsRte_SysMon_VehNetState                 sVechStateMsg;
  uint8 ucCtrlStpVechElectricState;

  //receive bb messages
  (void)Rte_Read_SysMon_VehNetState(&sVechStateMsg);

  if (sVechStateMsg.eSigQty == SIG_VALID)
  {
    //PRQA S 4394 ++  // cast is needed
    ucCtrlStpVechElectricState = (uint8)(sVechStateMsg.eElectricNetworkState);
  }
  else if ((sVechStateMsg.eSigQty == SIG_INVALID) || (sVechStateMsg.eSigQty == SIG_TIMEOUT))
  {
    ucCtrlStpVechElectricState = (uint8)eInvalid;
  }
  else
  {
    // keep previous value
  }

  return ucCtrlStpVechElectricState;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_ReadVESMainState
///
/// \descr  reads vechicle electric state
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 CtrlStp_RteAccess_ReadVESMainState(void)
{
  tsRte_SysMon_VehNetState                 sVechStateMsg;
  uint8 ucCtrlStpVESMainState;

  //receive bb messages
  (void)Rte_Read_SysMon_VehNetState(&sVechStateMsg);

  if (sVechStateMsg.eSigQty == SIG_VALID)
  {
    //PRQA S 4394 ++  // cast is needed
    ucCtrlStpVESMainState = (uint8)(sVechStateMsg.eVESMainState);
  }
  else if (sVechStateMsg.eSigQty == SIG_TIMEOUT)
  {
    ucCtrlStpVESMainState = (uint8)VESState_Start; // REQ-0543628 B
  }
  else if (sVechStateMsg.eSigQty == SIG_INVALID)
  {
    ucCtrlStpVESMainState = (uint8)VESState_Invalid;
  }
  else
  {
    // keep previous value
  }

  return ucCtrlStpVESMainState;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_ReadAFSMode
///
/// \descr  reads AFS mode
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 CtrlStp_RteAccess_ReadAFSMode(void)
{
  tsRte_SysMonAfsSignals                 sAFSSignalsMsg;
  uint8 ucCtrlStpAfsMode;

  //receive bb messages
  (void)Rte_Read_SysMon_Afs_Signals(&sAFSSignalsMsg);

  if (sAFSSignalsMsg.eSigQty == SIG_VALID)
  {

    //PRQA S 4394 ++  // cast is needed
    ucCtrlStpAfsMode = (uint8)(sAFSSignalsMsg.eAfs_Mode);
  }
  else if ((sAFSSignalsMsg.eSigQty == SIG_INVALID) || (sAFSSignalsMsg.eSigQty == SIG_TIMEOUT))
  {
    ucCtrlStpAfsMode = (uint8)eCtrlAFS_Invalid;
  }
  else
  {
    // keep previous value
  }

  return ucCtrlStpAfsMode;
}


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_ReadGfhbCmd
///
/// \descr  reads GFHB - Glare free high beam command
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 CtrlStp_RteAccess_ReadGfhbCmd(void)
{
  tsRte_SysMonAfsSignals                 sAFSSignalsMsg;
  uint8 ucCtrlStpGfhbCmd;

  //receive bb messages
  (void)Rte_Read_SysMon_Afs_Signals(&sAFSSignalsMsg);  

  if (sAFSSignalsMsg.eSigQty == SIG_VALID)
  {
    //PRQA S 4394 ++  // cast is needed
    ucCtrlStpGfhbCmd = (uint8)(sAFSSignalsMsg.eGfhb_Cmd);
  }
  else if ((sAFSSignalsMsg.eSigQty == SIG_INVALID) || (sAFSSignalsMsg.eSigQty == SIG_TIMEOUT))
  {
    ucCtrlStpGfhbCmd = 0u;
  }
  else
  {
    // keep previous value
  }

  return ucCtrlStpGfhbCmd;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_ReadHbCmd
///
/// \descr  reads HB - high beam command
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 CtrlStp_RteAccess_ReadHbCmd(void)
{
  tsRte_SysMonLgtFctsReq                 sAFSLgtFctsReq;
  uint8 ucDblHbCmd;

  (void)Rte_Read_SysMon_StdLgtFcts_Req(&sAFSLgtFctsReq);

  if (sAFSLgtFctsReq.eSigQty == SIG_VALID)
  {
    ucDblHbCmd = (uint8)(sAFSLgtFctsReq.eHb_Request);
  }
  else if ((sAFSLgtFctsReq.eSigQty == SIG_INVALID) || (sAFSLgtFctsReq.eSigQty == SIG_TIMEOUT))
  {
    ucDblHbCmd = 0u;
  }
  else
  {
    // keep previous value
  }
  return ucDblHbCmd;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_ReadLbBoostAllowed
///
/// \descr  reads Autorization to activate boost led for low beam
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 CtrlStp_RteAccess_ReadLbBoostAllowed(void)
{
  tsRte_SysMonAfsSignals                 sAFSSignalsMsg;
  uint8 ucCtrlStpLowBeamBoostAllowed;

  //receive bb messages
  (void)Rte_Read_SysMon_Afs_Signals(&sAFSSignalsMsg);

  if (sAFSSignalsMsg.eSigQty == SIG_VALID)
  {
    //PRQA S 4394 ++  // cast is needed
    ucCtrlStpLowBeamBoostAllowed = (uint8)(sAFSSignalsMsg.eLbBoost_Allowed);
  }
  else if ((sAFSSignalsMsg.eSigQty == SIG_INVALID) || (sAFSSignalsMsg.eSigQty == SIG_TIMEOUT))
  {
    ucCtrlStpLowBeamBoostAllowed = 0u;
  }
  else
  {
    // keep previous value
  }

  return ucCtrlStpLowBeamBoostAllowed;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_ReadElectricalSuppState
///
/// \descr  reads TMC pressure
///
/// \param  void
///
/// \return uint16
//-----------------------------------------------------------------------------
teCtrlStp_EtatFee CtrlStp_RteAccess_ReadElectricalSuppState(void)
{
  tsRte_SigPrep_ElecSupState sElectricalSupplyStateMsg;
  teCtrlStp_EtatFee          eCtrlStpEtatFee;

  //receive bb messages
  (void)Rte_Read_SigPrep_ElecSupState(&sElectricalSupplyStateMsg);  

  if (sElectricalSupplyStateMsg.eSigQty == SIG_VALID)
  {
    switch (sElectricalSupplyStateMsg.eElectrSupplyState)
    {
    case eEtatFee_1_1:     {eCtrlStpEtatFee = CtrlStp_eEtatFee_1_1;     } break;
    case eEtatFee_1_2:     {eCtrlStpEtatFee = CtrlStp_eEtatFee_1_2;     } break;
    case eEtatFee_1_3c:    {eCtrlStpEtatFee = CtrlStp_eEtatFee_1_3c;    } break;
    case eEtatFee_1_3r:    {eCtrlStpEtatFee = CtrlStp_eEtatFee_1_3r;    } break;
    case eEtatFee_2_1:     {eCtrlStpEtatFee = CtrlStp_eEtatFee_2_1;     } break;
    case eEtatFee_3c_1:    {eCtrlStpEtatFee = CtrlStp_eEtatFee_3c_1;    } break;
    case eEtatFee_3r_1:    {eCtrlStpEtatFee = CtrlStp_eEtatFee_3r_1;    } break;
    case eEtatFee_4_1:     {eCtrlStpEtatFee = CtrlStp_eEtatFee_4_1;     } break;
    case eEtatFee_5_5:     {eCtrlStpEtatFee = CtrlStp_eEtatFee_5_5;     } break;
    case eEtatFee_1_3vr:   {eCtrlStpEtatFee = CtrlStp_eEtatFee_1_3vr;   } break;
    case eEtatFee_3vr_1:   {eCtrlStpEtatFee = CtrlStp_eEtatFee_3vr_1;   } break;
    case eEtatFee_Invalid: {eCtrlStpEtatFee = CtrlStp_eEtatFee_Invalid; } break;
    default: break;
    }
  }
  else if ((sElectricalSupplyStateMsg.eSigQty == SIG_INVALID) || (sElectricalSupplyStateMsg.eSigQty == SIG_TIMEOUT))
  {
    eCtrlStpEtatFee = CtrlStp_eEtatFee_Invalid;
  }
  else
  {
    // keep previous value
  }

  return eCtrlStpEtatFee;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_VehicleModeConfig
///
/// \descr  reads The state of vehicle configuration
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 CtrlStp_RteAccess_ReadVehicleModeConfig(void)
{
  tsRte_SigPrep_VehicleConfigSig                 sVehicleConfigSigMsg;
  uint8 ucCtrlStpVehicleModeCfg;

  //receive bb messages
  (void)Rte_Read_SigPrep_VehicleConfigSig(&sVehicleConfigSigMsg);  

  if (sVehicleConfigSigMsg.eSigQty == SIG_VALID)
  {
    ucCtrlStpVehicleModeCfg = (uint8)(sVehicleConfigSigMsg.eVehicleCfg);
  }
  else if (sVehicleConfigSigMsg.eSigQty == SIG_SNA)
  {
    // during init the signal is not available and shall be considered invalid (workaround for DIAG_LVL after wakeup)
    ucCtrlStpVehicleModeCfg = (uint8)eModeConfigVehicle_Invalid;
  }
  else
  {
    ucCtrlStpVehicleModeCfg = (uint8)eModeConfigVehicle_Invalid2;
  }

  return ucCtrlStpVehicleModeCfg;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_AvacCommand
///
/// \descr  reads The state of vehicle configuration
///
/// \param  sint16* snVerticalAngle, boolean* boTrainingState, uint8 ucMountingSide
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_RteAccess_ReadAvacCommand(sint16* snVerticalAngle, boolean* boVehAttitudeInvalid, uint8 ucMountingSide)
{
  tsPositionOut                 sPositionOutMsg;

  //receive bb messages
  (void)Rte_Read_ppsAvacOut(&sPositionOutMsg);

  if (sPositionOutMsg.State == (uint8)SIG_VALID)
  {
    //PRQA S 4394 ++  // cast is needed
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
/// \brief  CtrlStp_RteAccess_ReadSensorStatus
///
/// \descr  reads The state of the pitch sensors
///
/// \param  teCtrlStp_SensorState eSensorState
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_RteAccess_ReadSensorStatus(teCtrlStp_SensorState* eSensorState)
{
  teRte_HlsSensorState ePitchSensorState;

  //receive bb messages
  (void)Rte_Read_Pitch_PlausState(&ePitchSensorState);

  switch (ePitchSensorState)
  {
  case eNO_FAILURE:     {*eSensorState = CtrlStp_eHLS_NO_FAILURE;     } break;
  case eSENSOR_FAILURE: {*eSensorState = CtrlStp_eHLS_SENSOR_FAILURE; } break;
  case eFROZEN_FAILURE: {*eSensorState = CtrlStp_eHLS_FROZEN_FAILURE; } break;
  case eSTORED_FAILURE: {*eSensorState = CtrlStp_eHLS_STORED_FAILURE; } break;
  default: break;
  }

  if (NvmBlockDeltaPwmPara.eNVM_VAC_Input == eInput_CAN)
  {
    *eSensorState = CtrlStp_eHLS_NO_FAILURE;
  }
  else
  {
    // leave previous value
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_LevellingDiagStatus
///
/// \descr  reads diagnosis from slave stepper
///
/// \param  tsCtrlStp_LevellingDiagStatus* sLevellingDiagStatus
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_RteAccess_ReadLevellingDiagStatus(tsCtrlStp_LevellingDiagStatus* sLevellingDiagStatus)
{
  tsRte_LevellingDiagStatus sLevellingDiagStatusMsg;

  //receive bb messages
  (void)Rte_Read_SigPrep_LevellingDiagStatus(&sLevellingDiagStatusMsg); 

  sLevellingDiagStatus->eSigQty = (teCtrlStp_SigQty)(sLevellingDiagStatusMsg.eSigQty); //PRQA S 4322 ++  // cast is needed

  if (sLevellingDiagStatusMsg.eSigQty == SIG_VALID)
  {
    //PRQA S 4322 ++  // cast is needed
    sLevellingDiagStatus->eLvlElecR = (teCtrlStp_LvlElecR)(sLevellingDiagStatusMsg.eLvlElecR);
    sLevellingDiagStatus->eLvlTemperatureR = (teCtrlStp_LvlTemperatureR)(sLevellingDiagStatusMsg.eLvlTemperatureR);
    sLevellingDiagStatus->eLvlSteplossR = (teCtrlStp_LvlSteplossR)(sLevellingDiagStatusMsg.eLvlSteplossR);
    sLevellingDiagStatus->eLvlRefStateR = (teCtrlStp_LvlRefStateR)(sLevellingDiagStatusMsg.eLvlRefStateR);
    sLevellingDiagStatus->eLvlVoltR = (teCtrlStp_LvlVoltR)(sLevellingDiagStatusMsg.eLvlVoltR);
  }
  else if ((sLevellingDiagStatusMsg.eSigQty == SIG_INVALID) || (sLevellingDiagStatusMsg.eSigQty == SIG_TIMEOUT))
  {
    sLevellingDiagStatus->eLvlElecR = CtrlStp_eLvlElecR_OpenCircuit;
    sLevellingDiagStatus->eLvlTemperatureR = CtrlStp_eLvlTemperatureR_HighTemperatureShutdown;
    sLevellingDiagStatus->eLvlSteplossR = CtrlStp_eLvlSteplossR_SteplossRisk;
    sLevellingDiagStatus->eLvlRefStateR = CtrlStp_eLvlRefStateR_Invalid;
    sLevellingDiagStatus->eLvlVoltR = CtrlStp_eLvlVoltR_UnderVoltage;
  }
  else
  {
    // keep previous value
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_ReadLevellingFeedback
///
/// \descr  reads the feedback from slave stepper
///
/// \param  tsCtrlStp_LevellingFeedback* sLevellingFeedback
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_RteAccess_ReadLevellingFeedback(tsCtrlStp_LevellingFeedback* sLevellingFeedback)
{
  tsRte_LevellingFeedback sLevellingFeedbackMsg;

  //receive bb messages
  (void)Rte_Read_SigPrep_LevellingFeedback(&sLevellingFeedbackMsg); 

  sLevellingFeedback->eSigQty = (teCtrlStp_SigQty)(sLevellingFeedbackMsg.eSigQty);

  if (sLevellingFeedbackMsg.eSigQty == SIG_VALID)
  {
    //PRQA S 4394 ++  // cast is needed
    sLevellingFeedback->eRPosSignLvl = (teCtrlStp_SignPosLvlR)(sLevellingFeedbackMsg.eRPosSignLvl);
    sLevellingFeedback->ePositionSiteD.unRPosLvl = (sLevellingFeedbackMsg.ePositionSiteD.unRPosLvl);
  }
  else
  {
    // only signal quality is needed if not valid
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_LevellingTgtPos
///
/// \descr  reads target position
///
/// \param  tsCtrlStp_LevellingTgtPos* sLevellingTgtPos
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_RteAccess_ReadLevellingTgtPos(tsCtrlStp_LevellingTgtPos* sLevellingTgtPos)
{
  tsRte_LevellingTgtPos sLevellingTgtPosMsg;

  //receive bb messages
  (void)Rte_Read_SigPrep_LevellingTgtPos(&sLevellingTgtPosMsg);

  sLevellingTgtPos->eSigQty = (teCtrlStp_SigQty)(sLevellingTgtPosMsg.eSigQty);

  if (sLevellingTgtPosMsg.eSigQty == SIG_VALID)
  {
    //PRQA S 4394 ++  // cast is needed
    sLevellingTgtPos->eRCmdSignLvl = (teCtrlStp_SigneConsigneSiteD)sLevellingTgtPosMsg.eRCmdSignLvl;
    sLevellingTgtPos->eRCmdRefLvl = (teCtrlStp_CmdRefSiteD)sLevellingTgtPosMsg.eRCmdRefLvl;
    sLevellingTgtPos->eRCmdPosLvl.unRCmdPosLvl = sLevellingTgtPosMsg.eRCmdPosLvl.unRCmdPosLvl;
  }
  else
  {
    // only signal quality is needed if not valid
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_ReadppCddStpActual0_sStpActualValues
///
/// \descr  reads stepper driver status
///
/// \param  tsRte_CddStpActual* CtrlStp_ActAll
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_RteAccess_ReadppCddStpActual0_sStpActualValues(tsRte_CddStpActual* CtrlStp_ActAll)
{
  //receive bb messages
  (void)Rte_Read_ppCddStpActual0_sStpActualValues(CtrlStp_ActAll);

}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port
///
/// \descr  reads The state of vehicle configuration
///
/// \param  tsCtrlStp_LevellingTgtPos* tsLevellingSignals
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_RteAccess_ReadCtrlStp_MasterCommand_Port(tsCtrlStp_LevellingTgtPos* tsLevellingSignals)
{
  tsRte_LevellingTgtPos sLevellingTgtPosMsg;

  //receive bb messages
  (void)Rte_Read_CtrlStp_MasterCommand(&sLevellingTgtPosMsg); 

  tsLevellingSignals->eSigQty = (teCtrlStp_SigQty)sLevellingTgtPosMsg.eSigQty;

  if (sLevellingTgtPosMsg.eSigQty == SIG_VALID)
  {
    //PRQA S 4394 ++  // cast is needed
    tsLevellingSignals->eRCmdSignLvl = (teCtrlStp_SigneConsigneSiteD)sLevellingTgtPosMsg.eRCmdSignLvl;
    tsLevellingSignals->eRCmdRefLvl = (teCtrlStp_CmdRefSiteD)sLevellingTgtPosMsg.eRCmdRefLvl;
    tsLevellingSignals->eRCmdPosLvl.unRCmdPosLvl = sLevellingTgtPosMsg.eRCmdPosLvl.unRCmdPosLvl;
  }
  else
  {
    // do nothing
  }

}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_Write_DrvLedDiag_Port
///
/// \descr  reads The state of drvled diag port
///
/// \param  boolean boLvlError
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_RteAccess_Write_DrvLedDiag_Port(boolean boLvlError)
{
  tsRte_Hs6_Diag_Drvled_L_457 data = { 0 };

  (void)Rte_Read_DrvLedDiag(&data);

  data.eLevellingAdjustFault = (boLvlError == FALSE) ? eDiagLvl_Ok : eDiagLvl_Nok;

  //receive bb messages
  (void)Rte_Write_DrvLedDiag(&data);

}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_WriteCtrlStp_MasterCommand_Port
///
/// \descr  reads The state of stepper master command
///
/// \param  tsCtrlStp_LevellingTgtPos* tsLevellingSignals
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_RteAccess_WriteCtrlStp_MasterCommand_Port(tsCtrlStp_LevellingTgtPos* tsLevellingSignals)
{
  tsRte_LevellingTgtPos sLevellingTgtPosMsg;

  //PRQA S 4394 ++  // cast is needed
  sLevellingTgtPosMsg.eRCmdSignLvl = (teRte_SigneConsigneSiteD)tsLevellingSignals->eRCmdSignLvl;
  sLevellingTgtPosMsg.eRCmdRefLvl = (teRte_CmdRefSiteD)tsLevellingSignals->eRCmdRefLvl;
  sLevellingTgtPosMsg.eRCmdPosLvl.unRCmdPosLvl = tsLevellingSignals->eRCmdPosLvl.unRCmdPosLvl;

  //receive bb messages
  (void)Rte_Write_CtrlStp_MasterCommand(&sLevellingTgtPosMsg);

}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port
///
/// \descr  reads slave stepper diagnostic status
///
/// \param  tsCtrlStp_LevellingDiagStatus* tsLevellingDiagStatus
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_RteAccess_ReadCtrlStp_SlaveDiagStatus_Port(tsCtrlStp_LevellingDiagStatus* tsLevellingDiagStatus)
{
  tsRte_LevellingDiagStatus sLevellingDiagStatusMsg;

  //receive bb messages
  (void)Rte_Read_CtrlStp_SlaveDiagStatus(&sLevellingDiagStatusMsg);

  tsLevellingDiagStatus->eSigQty = (teCtrlStp_SigQty)(sLevellingDiagStatusMsg.eSigQty);

  if (sLevellingDiagStatusMsg.eSigQty == SIG_VALID)
  {
    //PRQA S 4394 ++  // cast is needed
    tsLevellingDiagStatus->eLvlElecR = (teCtrlStp_LvlElecR)(sLevellingDiagStatusMsg.eLvlElecR);
    tsLevellingDiagStatus->eLvlTemperatureR = (teCtrlStp_LvlTemperatureR)(sLevellingDiagStatusMsg.eLvlTemperatureR);
    tsLevellingDiagStatus->eLvlSteplossR = (teCtrlStp_LvlSteplossR)(sLevellingDiagStatusMsg.eLvlSteplossR);
    tsLevellingDiagStatus->eLvlRefStateR = (teCtrlStp_LvlRefStateR)(sLevellingDiagStatusMsg.eLvlRefStateR);
    tsLevellingDiagStatus->eLvlVoltR = (teCtrlStp_LvlVoltR)(sLevellingDiagStatusMsg.eLvlVoltR);
  }
  else
  {
    // only signal quality is needed if not valid
  }

}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port
///
/// \descr  writes slave stepper diagnostic status 
///
/// \param  tsCtrlStp_LevellingDiagStatus* tsLevellingDiagStatus
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_RteAccess_CtrlStp_WriteSlaveDiagStatus_Port(tsCtrlStp_LevellingDiagStatus* tsLevellingDiagStatus)
{
  tsRte_LevellingDiagStatus sLevellingDiagStatusMsg;

  //PRQA S 4394 ++  // cast is needed
  sLevellingDiagStatusMsg.eLvlElecR = (teLvlElecR)(tsLevellingDiagStatus->eLvlElecR);
  sLevellingDiagStatusMsg.eLvlTemperatureR = (teLvlTemperatureR)(tsLevellingDiagStatus->eLvlTemperatureR);
  sLevellingDiagStatusMsg.eLvlSteplossR = (teLvlSteplossR)(tsLevellingDiagStatus->eLvlSteplossR);
  sLevellingDiagStatusMsg.eLvlRefStateR = (teLvlRefStateR)(tsLevellingDiagStatus->eLvlRefStateR);
  sLevellingDiagStatusMsg.eLvlVoltR = (teLvlVoltR)(tsLevellingDiagStatus->eLvlVoltR);
  sLevellingDiagStatusMsg.eSigQty = (teRte_SigQty)(tsLevellingDiagStatus->eSigQty);

  (void)Rte_Write_CtrlStp_SlaveDiagStatus(&sLevellingDiagStatusMsg);

}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port
///
/// \descr  reads the feedback from slave stepper
///
/// \param  tsCtrlStp_LevellingFeedback* tsLevellingFeedback
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_RteAccess_CtrlStp_ReadSlaveFeedback_Port(tsCtrlStp_LevellingFeedback* tsLevellingFeedback)
{
  tsRte_LevellingFeedback sLevellingFeedbackMsg;

  //receive bb messages
  (void)Rte_Read_CtrlStp_SlaveFeedback(&sLevellingFeedbackMsg);

  tsLevellingFeedback->eSigQty = (teCtrlStp_SigQty)(sLevellingFeedbackMsg.eSigQty);

  if (sLevellingFeedbackMsg.eSigQty == SIG_VALID)
  {
    //PRQA S 4394 ++  // cast is needed
    tsLevellingFeedback->eRPosSignLvl = (teCtrlStp_SignPosLvlR)(sLevellingFeedbackMsg.eRPosSignLvl);
    tsLevellingFeedback->ePositionSiteD.unRPosLvl = (sLevellingFeedbackMsg.ePositionSiteD.unRPosLvl);
  }
  else
  {
    // only signal quality is needed if not valid
  }
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_WriteCtrlStp_SlaveFeedback_Port
///
/// \descr  writes slave stepper feedback port
///
/// \param  tsCtrlStp_LevellingFeedback* tsLevellingFeedback
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_RteAccess_WriteCtrlStp_SlaveFeedback_Port(tsCtrlStp_LevellingFeedback* tsLevellingFeedback)
{
  tsRte_LevellingFeedback sLevellingFeedbackMsg;

  //PRQA S 4394 ++  // cast is needed
  sLevellingFeedbackMsg.eRPosSignLvl = (teRte_SignPosLvlR)(tsLevellingFeedback->eRPosSignLvl);
  sLevellingFeedbackMsg.ePositionSiteD.unRPosLvl = (tsLevellingFeedback->ePositionSiteD.unRPosLvl);
  sLevellingFeedbackMsg.eSigQty = (teRte_SigQty)(tsLevellingFeedback->eSigQty);

  (void)Rte_Write_CtrlStp_SlaveFeedback(&sLevellingFeedbackMsg);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_WriteppCtrlStpTarget0_StpTargetValues
///
/// \descr  reads The state of vehicle configuration
///
/// \param  void
///
/// \return uint16
//-----------------------------------------------------------------------------
void CtrlStp_RteAccess_WriteppCtrlStpTarget0_StpTargetValues(tsRte_CtrlStpTarget* CtrlStp_TgtAll)
{
  //receive bb messages
  (void)Rte_Write_ppCtrlStpTarget0_StpTargetValues(CtrlStp_TgtAll);
}


//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0
///
/// \descr  reads actual status stepper
///
/// \param  tsCtrlStp_DiagStatus* CtrlStp_ActStatStp
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_RteAccess_ReadCtrlStp_ActStatStp_sVal_0(tsCtrlStp_DiagStatus* CtrlStp_ActStatStp)
{
  tsRte_ActStatStp0 CtrlStp_ActStatStp0;

  (void)Rte_Read_CtrlStp_ActStatStp_sVal_0(&CtrlStp_ActStatStp0);

  CtrlStp_ActStatStp->nStatStpPosVer      = CtrlStp_ActStatStp0.StatStp.nStatStpPosVer;
  CtrlStp_ActStatStp->cStatStpPosDegree   = CtrlStp_ActStatStp0.StatStp.cStatStpPosDegree;
  CtrlStp_ActStatStp->boStpIsMoving       = CtrlStp_ActStatStp0.StatStp.boStpIsMoving;
  CtrlStp_ActStatStp->boStpCommDef        = CtrlStp_ActStatStp0.StatStp.boStpCommDef;
  CtrlStp_ActStatStp->boStpPosDef         = CtrlStp_ActStatStp0.StatStp.boStpPosDef;
  CtrlStp_ActStatStp->eStatStpLevelStatus = (teCtrlStp_LvlStatus)CtrlStp_ActStatStp0.StatStp.eStatStpLevelStatus;

  switch (CtrlStp_ActStatStp0.StatStp.eStatStpStepLoss)
  {
  case eNoStepLoss:   {CtrlStp_ActStatStp->eStatStpStepLoss = CtrlStp_eLvlSteplossR_NoSteploss;   } break;
  case eStepLossRisk: {CtrlStp_ActStatStp->eStatStpStepLoss = CtrlStp_eLvlSteplossR_SteplossRisk; } break;
  default: break;
  }

  switch (CtrlStp_ActStatStp0.StatStp.eStatStpThermalState)
  {
  case eNoThermalWarning:      {CtrlStp_ActStatStp->eStatStpThermalState = CtrlStp_eLvlTemperatureR_NoWarning;               } break;
  case eColdTemperature:       {CtrlStp_ActStatStp->eStatStpThermalState = CtrlStp_eLvlTemperatureR_ColdTemperature;         } break;
  case eHighTemeratureWarning: {CtrlStp_ActStatStp->eStatStpThermalState = CtrlStp_eLvlTemperatureR_HighTemperatureWarning;  } break;
  case eHighTemperatureSD:     {CtrlStp_ActStatStp->eStatStpThermalState = CtrlStp_eLvlTemperatureR_HighTemperatureShutdown; } break;
  default: break;
  }

  switch (CtrlStp_ActStatStp0.StatStp.eStatStpElectricDefect)
  {
  case eNoElectricalDefect: {CtrlStp_ActStatStp->eStatStpElectricDefect = CtrlStp_eLvlElecR_NoDefect;     } break;
  case eOpenCircuitDefect:  {CtrlStp_ActStatStp->eStatStpElectricDefect = CtrlStp_eLvlElecR_OpenCircuit;  } break;
  case eShortCircuitDefect: {CtrlStp_ActStatStp->eStatStpElectricDefect = CtrlStp_eLvlElecR_ShortCircuit; } break;
  case eReservedElectrical: {CtrlStp_ActStatStp->eStatStpElectricDefect = CtrlStp_eLvlElecR_Reserved;     } break;
  default: break;
  }

  CtrlStp_ActStatStp->sValidationFrames.boLvl_Elec_Defect  = CtrlStp_ActStatStp0.sLvlValidationFrames.boLvl_Elec_Defect;
  CtrlStp_ActStatStp->sValidationFrames.boLvl_Moving       = CtrlStp_ActStatStp0.sLvlValidationFrames.boLvl_Moving;
  CtrlStp_ActStatStp->sValidationFrames.boLvl_StepLoss     = CtrlStp_ActStatStp0.sLvlValidationFrames.boLvl_StepLoss;
  CtrlStp_ActStatStp->sValidationFrames.boLvl_Temp_Defect  = CtrlStp_ActStatStp0.sLvlValidationFrames.boLvl_Temp_Defect;
  CtrlStp_ActStatStp->sValidationFrames.snLvl_Degree_Ctrl  = CtrlStp_ActStatStp0.sLvlValidationFrames.snLvl_Degree_Ctrl;
  CtrlStp_ActStatStp->sValidationFrames.snLvl_Pos_Feedback = CtrlStp_ActStatStp0.sLvlValidationFrames.snLvl_Pos_Feedback;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0
///
/// \descr  writes actual status stepper
///
/// \param  tsRte_ActStatStp0* CtrlStp_ActStatStp0
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_RteAccess_WriteCtrlStp_ActStatStp_sVal_0(tsCtrlStp_DiagStatus CtrlStp_ActStatStp)
{
  tsRte_ActStatStp0 CtrlStp_ActStatStp0;

  CtrlStp_ActStatStp0.StatStp.nStatStpPosVer = CtrlStp_ActStatStp.nStatStpPosVer;
  CtrlStp_ActStatStp0.StatStp.cStatStpPosDegree = CtrlStp_ActStatStp.cStatStpPosDegree;
  CtrlStp_ActStatStp0.StatStp.boStpIsMoving = CtrlStp_ActStatStp.boStpIsMoving;
  CtrlStp_ActStatStp0.StatStp.boStpCommDef = CtrlStp_ActStatStp.boStpCommDef;
  CtrlStp_ActStatStp0.StatStp.boStpPosDef = CtrlStp_ActStatStp.boStpPosDef;
  CtrlStp_ActStatStp0.StatStp.eStatStpLevelStatus = (teRte_StpLvlStatus)CtrlStp_ActStatStp.eStatStpLevelStatus; // PRQA S 4322 ++ // cast is needed, can't put into switch as it will be his metric violation

  switch (CtrlStp_ActStatStp.eStatStpStepLoss)
  {
  case CtrlStp_eLvlSteplossR_NoSteploss:   {CtrlStp_ActStatStp0.StatStp.eStatStpStepLoss = eNoStepLoss;   } break;
  case CtrlStp_eLvlSteplossR_SteplossRisk: {CtrlStp_ActStatStp0.StatStp.eStatStpStepLoss = eStepLossRisk; } break;
  default: break;
  }

  switch (CtrlStp_ActStatStp.eStatStpThermalState)
  {
  case CtrlStp_eLvlTemperatureR_NoWarning:               {CtrlStp_ActStatStp0.StatStp.eStatStpThermalState = eNoThermalWarning;      } break;
  case CtrlStp_eLvlTemperatureR_ColdTemperature:         {CtrlStp_ActStatStp0.StatStp.eStatStpThermalState = eColdTemperature;       } break;
  case CtrlStp_eLvlTemperatureR_HighTemperatureWarning:  {CtrlStp_ActStatStp0.StatStp.eStatStpThermalState = eHighTemeratureWarning; } break;
  case CtrlStp_eLvlTemperatureR_HighTemperatureShutdown: {CtrlStp_ActStatStp0.StatStp.eStatStpThermalState = eHighTemperatureSD;     } break;
  default: break;
  }

  switch (CtrlStp_ActStatStp.eStatStpElectricDefect)
  {
  case CtrlStp_eLvlElecR_NoDefect:     {CtrlStp_ActStatStp0.StatStp.eStatStpElectricDefect = eNoElectricalDefect; } break;
  case CtrlStp_eLvlElecR_OpenCircuit:  {CtrlStp_ActStatStp0.StatStp.eStatStpElectricDefect = eOpenCircuitDefect;  } break;
  case CtrlStp_eLvlElecR_ShortCircuit: {CtrlStp_ActStatStp0.StatStp.eStatStpElectricDefect = eShortCircuitDefect; } break;
  case CtrlStp_eLvlElecR_Reserved:     {CtrlStp_ActStatStp0.StatStp.eStatStpElectricDefect = eReservedElectrical; } break;
  default: break;
  }

  CtrlStp_ActStatStp0.sLvlValidationFrames.boLvl_Elec_Defect  = CtrlStp_ActStatStp.sValidationFrames.boLvl_Elec_Defect;
  CtrlStp_ActStatStp0.sLvlValidationFrames.boLvl_Moving       = CtrlStp_ActStatStp.sValidationFrames.boLvl_Moving;
  CtrlStp_ActStatStp0.sLvlValidationFrames.boLvl_StepLoss     = CtrlStp_ActStatStp.sValidationFrames.boLvl_StepLoss;
  CtrlStp_ActStatStp0.sLvlValidationFrames.boLvl_Temp_Defect  = CtrlStp_ActStatStp.sValidationFrames.boLvl_Temp_Defect;
  CtrlStp_ActStatStp0.sLvlValidationFrames.snLvl_Degree_Ctrl  = CtrlStp_ActStatStp.sValidationFrames.snLvl_Degree_Ctrl;
  CtrlStp_ActStatStp0.sLvlValidationFrames.snLvl_Pos_Feedback = CtrlStp_ActStatStp.sValidationFrames.snLvl_Pos_Feedback;

  //receive bb messages
  (void)Rte_Write_CtrlStp_ActStatStp_sVal_0(&CtrlStp_ActStatStp0);

}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_WriteCtrlStp_Validation_Port
///
/// \descr  Write values in the validation port
///
/// \param  sValidationParams
///
/// \return [void]
//-----------------------------------------------------------------------------
void CtrlStp_RteAccess_WriteCtrlStp_Validation_Port(tsCtrlStp_ValidationParameters* sValidationParams)
{
  tsRte_CtrlStpValidation sValidationParameters;

  if (sValidationParams != NULL_PTR)
  {
    switch (sValidationParams->eADL_MODE)
    {
    case CtrlStp_eSubModeUnavailable: {sValidationParameters.eADL_MODE = eStpSubModeUnavailable; } break;
    case CtrlStp_eSubModeAvailable: {sValidationParameters.eADL_MODE = eStpSubModeAvailable;   } break;
    case CtrlStp_eSubModeAftersale: {sValidationParameters.eADL_MODE = eStpSubModeAftersale;   } break;
    case CtrlStp_eSubModeFrozen: {sValidationParameters.eADL_MODE = eStpSubModeFrozen;      } break;
    case CtrlStp_eSubModeFactory: {sValidationParameters.eADL_MODE = eStpSubModeFactory;     } break;
    default: break;
    }

    switch (sValidationParams->eADL_PHASE)
    {
    case CtrlStp_eState_Init: {sValidationParameters.eADL_PHASE = eStpState_Init;    } break;
    case CtrlStp_eState_Ref: {sValidationParameters.eADL_PHASE = eStpState_Ref;     } break;
    case CtrlStp_eState_Adj: {sValidationParameters.eADL_PHASE = eStpState_Adj;     } break;
    case CtrlStp_eState_Fail: {sValidationParameters.eADL_PHASE = eStpState_Fail;    } break;
    case CtrlStp_eState_STT: {sValidationParameters.eADL_PHASE = eStpState_STT;     } break;
    case CtrlStp_eState_Maxsize: {sValidationParameters.eADL_PHASE = eStpState_Maxsize; } break;
    default: break;
    }

    switch (sValidationParams->eLvlAdjHeadlampFault_L)
    {
    case CtrlStp_eNo_Failure:         {sValidationParameters.eLvlAdjHeadlampFault_L = eStpNo_Failure;            } break;
    case CtrlStp_eFrozen_Failure:     {sValidationParameters.eLvlAdjHeadlampFault_L = eStpFrozen_Failure;        } break;
    case CtrlStp_eTransition_Failure: {sValidationParameters.eLvlAdjHeadlampFault_L = eStpTransition_Failure;    } break;
    default: break;
    }

    switch (sValidationParams->eLvlAdjHeadlampFault_R)
    {
    case CtrlStp_eNo_Failure:         {sValidationParameters.eLvlAdjHeadlampFault_R = eStpNo_Failure;            } break;
    case CtrlStp_eFrozen_Failure:     {sValidationParameters.eLvlAdjHeadlampFault_R = eStpFrozen_Failure;        } break;
    case CtrlStp_eTransition_Failure: {sValidationParameters.eLvlAdjHeadlampFault_R = eStpTransition_Failure;    } break;
    default: break;
    }

    sValidationParameters.snVehAttitudeFactory = NvmBlockDeltaPwmPara.snVehicleAttitude;
    sValidationParameters.boLvlAdjFunctFault_L = sValidationParams->boLvlAdjFunctionalFault_L;
    sValidationParameters.boLvlAdjFunctFault_R = sValidationParams->boLvlAdjFunctionalFault_R;
  }
  else
  {
    // use previous values
  }

  (void)Rte_Write_CtrlStp_Validation_Port(&sValidationParameters);
  //PRQA S 5310 2 // STCPTH exceeded and is necessary for this RTE port to be sent
  //PRQA S 5316 1 // STCYC exceeded and is necessary for this RTE port to be sent
}

//-----------------------------------------------------------------------------
/// \brief CtrlStp_RteAccess_ReadDiagStpControlRoutine
///
/// \descr Get Stp Routine Control Routine Status
///
/// \param  *psRoutineInfo - Stp Control routine data inputs
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_RteAccess_ReadDiagStpControlRoutine(tsCtrlStp_StepperRoutineControl* psRoutineInfo)
{
  // Translation variable from RTE ports
  tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE, eDID_Invalid, 0 };

  // Read Diag Control RTE port
  (void)Rte_Read_Stp_RoutineControl(&sStpRoutineInfo);

  // Get the info
  // Ack status
  psRoutineInfo->boRequestAckStatus = sStpRoutineInfo.boRequestAckStatus;
  // Request status
  psRoutineInfo->boRequestStatus = sStpRoutineInfo.boRequestStatus;
  // Diagnostic Control
  switch (sStpRoutineInfo.eStpControl)
  {
  case eStpControl_Start:   {psRoutineInfo->eStpControl = CtrlStp_eStpControl_Start;   } break;
  case eStpControl_Stop:    {psRoutineInfo->eStpControl = CtrlStp_eStpControl_Stop;    } break;
  case eStpControl_Results: {psRoutineInfo->eStpControl = CtrlStp_eStpControl_Results; } break;
  default:                  {psRoutineInfo->eStpControl = CtrlStp_eStpControl_Unknown; } break;
  }
  // Diagnostic Request
  switch (sStpRoutineInfo.eStpRequest)
  {
  case eMovementToTop:    {psRoutineInfo->eStpRequest = CtrlStp_eMovementToTop;    } break;
  case eMovementToBottom: {psRoutineInfo->eStpRequest = CtrlStp_eMovementToBottom; } break;
  case eMovementToZero:   {psRoutineInfo->eStpRequest = CtrlStp_eMovementToZero;   } break;
  case eSequence1:        {psRoutineInfo->eStpRequest = CtrlStp_eSequence1;        } break;
  case eSequence2:        {psRoutineInfo->eStpRequest = CtrlStp_eSequence2;        } break;
  default:                {psRoutineInfo->eStpRequest = CtrlStp_eStop;             } break;
  }
  // Diagnostic side to control
  switch (sStpRoutineInfo.eStpSide)
  {
  case eRightActuator: {psRoutineInfo->eStpSide = CtrlStp_eRightActuator; } break;
  case eLeftActuator:  {psRoutineInfo->eStpSide = CtrlStp_eLeftActuator;  } break;
  case eBothActuators: {psRoutineInfo->eStpSide = CtrlStp_eBothActuators; } break;
  default: break;
  }
  // Diagnostic code ID
  switch (sStpRoutineInfo.eStpDID)
  {
  case eDD05: {psRoutineInfo->eStpDID = CtrlStp_eDD05;    } break;
  case eDF10: {psRoutineInfo->eStpDID = CtrlStp_eDF10;    } break;
  case eDF11: {psRoutineInfo->eStpDID = CtrlStp_eDF11;    } break;
  case eDF12: {psRoutineInfo->eStpDID = CtrlStp_eDF12;    } break;
  case eDF13: {psRoutineInfo->eStpDID = CtrlStp_eDF13;    } break;
  default:    {psRoutineInfo->eStpDID = CtrlStp_eInvalid; } break;
  }
  // Position request
  psRoutineInfo->snPosRequest = sStpRoutineInfo.snPosRequest;
  // Read sequence start flag
  psRoutineInfo->ucStartSequence = sStpRoutineInfo.ucStartSequence;
  //PRQA S 5310 2 // STPTH is exceeded due to program architecture and readability
  //PRQA S 5316 1 // STCYC is exceeded due to program architecture and readability
}

//-----------------------------------------------------------------------------
/// \brief CtrlStp_RteAccess_WriteStpRoutineAck
///
/// \descr Acknowledge return for Diagnostic routine
///
/// \param  boolean boStatus
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_RteAccess_WriteStpRoutineAck(boolean boStatus)
{
  // Translation variable from RTE ports
  tsRte_StepperRoutineControl sStpRoutineInfo = { eStpControl_Unknown, eRightActuator, eMovementToZero, FALSE, FALSE };

  // Read Diag Control RTE port
  (void)Rte_Read_Stp_RoutineControl(&sStpRoutineInfo);

  // Update the Acnowledge status
  sStpRoutineInfo.boRequestAckStatus = boStatus;
  sStpRoutineInfo.boRequestStatus = FALSE;

  // Write Diag Control RTE port
  (void)Rte_Write_Stp_RoutineControl(&sStpRoutineInfo);
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_Read_350Lost_Status
///
/// \descr   get Frame 350 lost status via RTE
///
/// \param  *pboStatus
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlStp_RteAccess_Read_350Lost_Status(boolean* pboStatus)
{
  boolean  boStatus;

  (void)Rte_Read_DEM_350Lost_NotifyStatus(&boStatus);

  *pboStatus = boStatus;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlStp_RteAccess_MapParams
///
/// \descr  Mapps the coding parameter in order to acces the in CtrlStp
///
/// \param  [void]
///
/// \return [void]
//-----------------------------------------------------------------------------
void CtrlStp_RteAccess_MapParams(void)
{
 tsRteCodingParameters sCodingParameters;

 (void)Rte_Read_CodM_CtrlStp_Para(&sCodingParameters);

 CtrlStp_ParaFct0(sCodingParameters.eCodingState, sCodingParameters.psCodingParameters_Blocks);

}
