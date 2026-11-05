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
/// \author Futo Henrietta-Helena F31185D
///         mail to <henrietta-helena.futo[at]magnetimarelli.com>
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include <Std_Types.h>
#include "Dbl_RteAccess.h"
#include "Dblc.h"
#include "DblcSm.h"
#include "DblData.h"
#include <Cfg/Cfg.h>
#ifndef UNIT_TEST
#include <Rte.h>
#endif

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST)// Applicable only for FULL version
//=============================================================================
// defines
//=============================================================================

#define DBL_RTEACCESS_STEERINGANGLEFACTOR      1400 // default factor for steering wheel angle in case of failed input parameters
#define DBL_RTEACCESS_SIDES_NB                   2u // left + right headlamp count

//=============================================================================
// functions 
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief Dbl_Read_PhaseVie
///
/// \descr  Read Ecu operating mode from Rte
///
/// \param  void
///
/// \return boolean - return the status for the flag that indicate if the ecu is in normal mode and the quality is valid
//-----------------------------------------------------------------------------
boolean Dbl_Read_PhaseVie(void)
{
  tsRte_SysMon_LifePhases  sLifePhases;
  boolean                  boReturnValue = FALSE;

  (void)Rte_Read_SysMon_LifePhases(&sLifePhases);

  if ((sLifePhases.ePhaseVie == (eNormalMode)) && (sLifePhases.eSigQty == SIG_VALID))
  {
    boReturnValue = TRUE;
  }
  return boReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_ReadDblCmd
///
/// \descr  reads dbl state command
///
/// \param  void
///
/// \return teRte_PrimaryCmd
//-----------------------------------------------------------------------------
uint8 Dbl_RteAccess_ReadDblCmd(void)
{
  tsRte_AfsDblCmd       sDblMCmdMsg = { 0u };
  uint8 ucLbDiversity = CodDblDiversityParam();
  uint8 ucDblCmd = 0;

  (void)Rte_Read_FctR_AfsDblCmd(&sDblMCmdMsg);

  if (sDblMCmdMsg.Primary == 1u && (ucLbDiversity == (uint8)Dbl_eAUC_01 || ucLbDiversity == (uint8)Dbl_eAUC_03))
  {
    ucDblCmd = (uint8)ePLAY_DBL;
  }
  else
  {
    ucDblCmd = (uint8)eSTOP_DBL;
  }
	  
  return ucDblCmd;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_ReadSwimRate
///
/// \descr  reads swim rate 
///
/// \param  void
///
/// \return teRte_PrimaryCmd
//-----------------------------------------------------------------------------
tsDbl_SwiRateLimMsg Dbl_RteAccess_ReadSwimRate(void)
{
  tsRte_SwiRateLimMsg sSwiRateLim = { 0 };
  tsDbl_SwiRateLimMsg sDblLimits = { 0 };

  // read back limits from black board
 (void)Rte_Read_AfsDbl_SwiRateLimMsg(&sSwiRateLim);

  for (uint8 ucIdx = 0u; ucIdx < DBL_RTEACCESS_SIDES_NB; ucIdx++)
  {
    sDblLimits.nLimit[ucIdx] = sSwiRateLim.nLimit[ucIdx];
  }
  return sDblLimits;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_ReadSpeed
///
/// \descr  reads speed
///
/// \param  void
///
/// \return uint32
//-----------------------------------------------------------------------------
uint32 Dbl_RteAccess_ReadSpeed(void)
{
  tsRte_SysMon_VehicleSpeed                 sSpeedMsg = { 0 };
  static uint32 ulDblSpeed = 0u;
  static boolean boSpeedQuality_NOk = FALSE;

  // the vehicle speed is unknown (VITESSE_VEHICULE_ROUES = Invalid and VITESSE_VEHICULE_ROUES_DISPO = Indisponible or Invalid)

  (void)Rte_Read_SysMon_VehicleSpeed(&sSpeedMsg);

  switch (sSpeedMsg.eSigQtyDbl)
  {
  case SIG_VALID:
    if (sSpeedMsg.eVehicleSpeedDispo == eVvhIndisp_SpeedInfoAvailable)
    {
      boSpeedQuality_NOk = FALSE;
    }
    else
    {
      // do nothing
    }

    break;

  case SIG_TIMEOUT:
  case SIG_E2E_CRCERR:
  case SIG_E2E_ALIVEERR:
    boSpeedQuality_NOk = TRUE;
    break;

  case SIG_INVALID:
    if (sSpeedMsg.eVehicleSpeedDispo != eVvhIndisp_SpeedInfoAvailable) 
    {
      boSpeedQuality_NOk = TRUE;
    }
    else
    {
      // do nothing
    }
    break;

  default:
    // nothing to do
    break;
  }
  if (boSpeedQuality_NOk == FALSE)
  {
    ulDblSpeed = (uint32)(sSpeedMsg.eVehicleSpeed.unVehicleSpeed / DBL_SPEED_COEF); // PRQA S  4391 // Cast is needed
  }
  else  
  {
    ulDblSpeed = DBL_MAX_SPEED;
  }

  return ulDblSpeed;
}


//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_ReadDynBendingBeamFaultR
///
/// \descr  reads dyn bending fault for right
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
teDbl_DynBendingBeamFault Dbl_RteAccess_ReadDynBendingBeamFaultR(void)
{
  tsRte_BendingBeamFault_OtherHL                 sDynBendingBeamFaultRMsg = { 0 };
  teDbl_DynBendingBeamFault eDynBendingBeamFaultR = eDbl_DynBendingBeamFault_False;

  (void)Rte_Read_SigPrepRx_Dbl_RightStatus(&sDynBendingBeamFaultRMsg);

  if (sDynBendingBeamFaultRMsg.eSigQty == SIG_VALID)
  {
    switch (sDynBendingBeamFaultRMsg.eDynBendingBeamFault)
    {
    case eDynBendingBeamFault_False:
      eDynBendingBeamFaultR = eDbl_DynBendingBeamFault_False;
      break;
    case eDynBendingBeamFault_True:
      eDynBendingBeamFaultR = eDbl_DynBendingBeamFault_True;
      break;
    default:
      eDynBendingBeamFaultR = eDbl_DynBendingBeamFault_Unavailable;
      break;
    }
  }
  else if ((sDynBendingBeamFaultRMsg.eSigQty == SIG_INVALID) || (sDynBendingBeamFaultRMsg.eSigQty == SIG_TIMEOUT))
  {
    eDynBendingBeamFaultR = eDbl_DynBendingBeamFault_True;
  }
  else
  {
    eDynBendingBeamFaultR = eDbl_DynBendingBeamFault_SNA;
  }
  return eDynBendingBeamFaultR;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_ReadDynBendingBeamFaultL
///
/// \descr  reads dyn bending fault for left
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
teDbl_DynBendingBeamFault Dbl_RteAccess_ReadDynBendingBeamFaultL(void)
{
  tsRte_BendingBeamFault_OtherHL                 sDynBendingBeamFaultLMsg = { 0 };
  teDbl_DynBendingBeamFault eDynBendingBeamFaultL = eDbl_DynBendingBeamFault_False;

  (void)Rte_Read_SigPrepRx_Dbl_LeftStatus(&sDynBendingBeamFaultLMsg);

  if (sDynBendingBeamFaultLMsg.eSigQty == SIG_VALID)
  {
    switch (sDynBendingBeamFaultLMsg.eDynBendingBeamFault)
    {
    case eDynBendingBeamFault_False:
      eDynBendingBeamFaultL = eDbl_DynBendingBeamFault_False;
      break;
    case eDynBendingBeamFault_True:
      eDynBendingBeamFaultL = eDbl_DynBendingBeamFault_True;
      break;
    default:
      eDynBendingBeamFaultL = eDbl_DynBendingBeamFault_Unavailable;
      break;
    }
  }
  else if ((sDynBendingBeamFaultLMsg.eSigQty == SIG_INVALID) || (sDynBendingBeamFaultLMsg.eSigQty == SIG_TIMEOUT))
  {
    eDynBendingBeamFaultL = eDbl_DynBendingBeamFault_True;
  }
  else
  {
    eDynBendingBeamFaultL = eDbl_DynBendingBeamFault_SNA;
  }
  return eDynBendingBeamFaultL;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_ReadSteeringType
///
/// \descr  reads steering type
///
/// \param  void
///
/// \return uint16
//-----------------------------------------------------------------------------
teDbl_TypeDir Dbl_RteAccess_ReadSteeringType(void)
{
  tsRte_SigPrep_DynamicSigs                 sDynamicSigsMsg = { 0 };
  teDbl_TypeDir                             ucDbleSteeringType = eDBL_TypeDir_SteeringLeft;

  (void)Rte_Read_SigPrep_DynamicSigs(&sDynamicSigsMsg); 

  switch (sDynamicSigsMsg.eSteeringType)
  {
  case eTypeDir_SteeringRight:
	  ucDbleSteeringType = eDBL_TypeDir_SteeringRight;
	  break;
  case eTypeDir_SteeringLeft:
	  ucDbleSteeringType = eDBL_TypeDir_SteeringLeft;
	  break;
  case eTypeDir_Invalid:
	  ucDbleSteeringType = eDBL_TypeDir_Invalid;
	  break;
  default:
	  break;
  }
  return ucDbleSteeringType;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_ReadEnvCondition
///
/// \descr  reads environment condition
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean Dbl_RteAccess_ReadEnvCondition(void)
{
  tsRte_SigPrep_EnvCondition                 sEnvCondMsg = { 0 };
  boolean boDblLightInhib = FALSE;

  (void)Rte_Read_SigPrep_EnvCondition(&sEnvCondMsg); 

  if (sEnvCondMsg.eSigQty == SIG_VALID)
  {
    boDblLightInhib = (boolean)(sEnvCondMsg.eDblInhibition);
  }
  else
  {
    boDblLightInhib = DBL_MAX_INHIB;
  }

  return boDblLightInhib;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_ReadCurvature
///
/// \descr  reads curvature 
///
/// \param  void
///
/// \return sint32
//-----------------------------------------------------------------------------
teRte_SigQty Dbl_RteAccess_ReadCurvature(sint32* nCurvature)
{
  tsRte_SigPrep_VehPathCurvature sDblCurvature = { 0 };

  (void)Rte_Read_SigPrep_VehPathCurvature(&sDblCurvature);
  
  if (sDblCurvature.eSigQty == SIG_VALID)
  {
	  sDblCurvature.eVehiclePathCurvature.nVehiclePathCurvature = sDblCurvature.eVehiclePathCurvature.nVehiclePathCurvature >= DBL_POSITIVE_CURVATURE_LIMIT ? DBL_POSITIVE_CURVATURE_LIMIT : sDblCurvature.eVehiclePathCurvature.nVehiclePathCurvature;
	  sDblCurvature.eVehiclePathCurvature.nVehiclePathCurvature = sDblCurvature.eVehiclePathCurvature.nVehiclePathCurvature <= DBL_NEGATIVE_CURVATURE_LIMIT ? DBL_NEGATIVE_CURVATURE_LIMIT : sDblCurvature.eVehiclePathCurvature.nVehiclePathCurvature;
  }
    
  *nCurvature = DBL_CURVE_OUTSIDE_HL_FACTOR_ADAPTION(sDblCurvature.eVehiclePathCurvature.nVehiclePathCurvature);// PRQA S 4490  // Signed number should be multiplied with an unsigned coef
  return sDblCurvature.eSigQty;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_ReadReverseGearStatus
///
/// \descr  gets reverse gear status
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean Dbl_RteAccess_ReadReverseGearStatus(void)
{
  tsRte_SigPrep_VehicleConfigSig   sReverseGearStatus;
  boolean                            boReverseStatus;
  boolean                            boReturnValue = TRUE;

  (void)Rte_Read_SigPrep_VehicleConfigSig(&sReverseGearStatus); 

  switch (sReverseGearStatus.eSigQty)
  {
  case SIG_VALID:
  case SIG_TIMEOUT:

	  boReverseStatus = (boolean)sReverseGearStatus.eEtatMar;
	  break;

  default:

	  break;
  }
  if (boReverseStatus == (boolean)eEtatMar_Forward)
  {
	  boReturnValue = FALSE;
  }
  return boReturnValue;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_ReadVehicleModeConfig
///
/// \descr  reads The state of vehicle configuration
///
/// \param  void
///
/// \return uint16
//-----------------------------------------------------------------------------
uint8 Dbl_RteAccess_ReadVehicleModeConfig(void)
{
  tsRte_SigPrep_VehicleConfigSig                 sVehicleConfigSigMsg;
  uint8 ucDblVehicleModeCfg;

  //receive bb messages
  (void)Rte_Read_SigPrep_VehicleConfigSig(&sVehicleConfigSigMsg); 

  switch (sVehicleConfigSigMsg.eSigQty)
  {
  case SIG_VALID:
  case SIG_TIMEOUT:

    ucDblVehicleModeCfg = (uint8)(sVehicleConfigSigMsg.eVehicleCfg);
    break;

  default:
    ucDblVehicleModeCfg = (uint8)eModeConfigVehicle_Invalid2;
    break;
  }


  return ucDblVehicleModeCfg;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_ReadVESMainState
///
/// \descr  reads vechicle electric state
///
/// \param  void
///
/// \return teDbl_EtatPrincipSEV
//-----------------------------------------------------------------------------
teDbl_EtatPrincipSEV Dbl_RteAccess_ReadVESMainState(void)
{
  tsRte_SysMon_VehNetState                 sVechStateMsg;
  teDbl_EtatPrincipSEV eDblVESMainState;

  (void)Rte_Read_SysMon_VehNetState(&sVechStateMsg); 

  switch (sVechStateMsg.eSigQty)
  {
  case SIG_VALID:
  case SIG_TIMEOUT:
    //PRQA S 4322 ++  // cast is needed
    eDblVESMainState = (teDbl_EtatPrincipSEV)sVechStateMsg.eVESMainState;
    break;
  default:
    eDblVESMainState = eDBL_VESState_Invalid;
    break;
  }
  return eDblVESMainState;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_ReadVehicleElectricState
///
/// \descr  reads vechicle electric state
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
tsDbl_VehNetState Dbl_RteAccess_ReadVehicleElectricState(void)
{
  tsRte_SysMon_VehNetState                 sVechStateMsg;
  tsDbl_VehNetState                 sDblVechElectricState = { 0 };

  (void)Rte_Read_SysMon_VehNetState(&sVechStateMsg); 

  switch (sVechStateMsg.eSigQty)
  {
  case SIG_VALID:
  case SIG_TIMEOUT:
    //PRQA S 4394 ++  // cast is needed
    sDblVechElectricState.eElectricNetworkState = (teDbl_EtatReseauElec)(sVechStateMsg.eElectricNetworkState);
    break;
  default:
    sDblVechElectricState.eElectricNetworkState = eDblTI_NOMINAL;
    break;
  }
  sDblVechElectricState.eSigQty = (teDbl_VehNetStateSigQty)sVechStateMsg.eSigQty;
  return sDblVechElectricState;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_WriteDblOutput
///
/// \descr  writes dbl output
///
/// \param  sint16 nAngle, uint8 ucState
///
/// \return void
//-----------------------------------------------------------------------------
void Dbl_RteAccess_WriteDblOutput(tsDbl_SwivellingOut nAngle, uint8 ucState, teDbl_eSubMode eMode)
{
 tsRte_DblOut sDblOutMsg;
 teRte_DblSubMode eDblMode;

 sDblOutMsg.SwivelAngle[0] = nAngle.SwivellingAngle[0].Hor;
 sDblOutMsg.SwivelAngle[1] = nAngle.SwivellingAngle[1].Hor;
  sDblOutMsg.DblState = (teRte_DblStatMain)ucState;  // PRQA S 4342  // Cast is needed
  eDblMode = (teRte_DblSubMode)eMode; // PRQA S 4322  // Cast is needed

  (void)Rte_Write_Dbl_SwivellingOut(&sDblOutMsg);
  (void)Rte_Write_Dbl_Mode(&eDblMode);
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_WriteDblSysMonTx_FullStatus
///
/// \descr  writes dbl fault status for full variant
///
/// \param  boolean eFailureStatus
///
/// \return void
//-----------------------------------------------------------------------------
void Dbl_RteAccess_WriteDblSysMonTx_FullStatus(boolean boFailureStatus)
{
  tsRte_Hs6_Diag_Drvled_BendingBeamFault sDblFault;

  //PRQA S 4394 , 4342 ++  // cast is needed
  sDblFault.eDynamicBendingBeamFault = (teDiagDbl)boFailureStatus;

  (void)Rte_Write_Dbl_SysMonTx_FullStatus(&sDblFault);
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus
///
/// \descr  writes dbl fault status for full variant
///
/// \param  boolean eFailureStatus
///
/// \return void
//-----------------------------------------------------------------------------
void Dbl_RteAccess_WriteDblSigPrepTx_LeftRightStatus(teDbl_MountingSide eSide, boolean boStatus)
{
  tsRte_BendingBeamFault_OtherHL sDblFaultFromOtherHL;

  //PRQA S 4442 ++  // cast is needed
  sDblFaultFromOtherHL.eDynBendingBeamFault = (teRte_DynBendingBeamFault)boStatus;
  sDblFaultFromOtherHL.eSigQty = SIG_VALID;

  if (eSide == Dbl_eMountedLeft)
  {
    (void)Rte_Write_Dbl_SigPrepTx_LeftStatus(&sDblFaultFromOtherHL);
  }
  else
  {
    (void)Rte_Write_Dbl_SigPrepTx_RightStatus(&sDblFaultFromOtherHL);
  }
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_ReadDblOutput
///
/// \descr  reads output angle of dbl
///
/// \param  void 
///
/// \return sint16 swivelangle
//-----------------------------------------------------------------------------
tsDbl_SwivellingOut Dbl_RteAccess_ReadDblOutput(void)
{
  tsRte_DblOut sDblOutMsg = { 0 };
  tsDbl_SwivellingOut sDBlOutPut = { 0 };

  (void)Rte_Read_Dbl_SwivellingOut(&sDblOutMsg); 

  sDBlOutPut.SwivellingAngle[0].Hor = sDblOutMsg.SwivelAngle[0];
  sDBlOutPut.SwivellingAngle[1].Hor = sDblOutMsg.SwivelAngle[1];

  return sDBlOutPut;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_ReadDblTrafficSide
///
/// \descr  reads traffic wheel drive side
///
/// \param  void 
///
/// \return teTraffic
//-----------------------------------------------------------------------------
teTraffic Dbl_RteAccess_ReadDblTrafficSide(void)
{
  tsRte_SigPrep_DynamicSigs sTrafficSideRegion = { 0 };
  teTraffic                 eRegion;

  (void)Rte_Read_SigPrep_DynamicSigs(&sTrafficSideRegion);

  // map region
  switch (sTrafficSideRegion.eSteeringType)
  {
  case   eTypeDir_SteeringRight:
    eRegion = RightHandTraffic;
    break;

  case eTypeDir_SteeringLeft:
    eRegion = LeftHandTraffic;
    break;

  default:
    break;
  }
  return eRegion;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_Read_EcuSide
///
/// \descr  Read Ecu mounting side from Rte
///
/// \param  eEcuSide - stores Ecu mounting side
///
/// \return void
//-----------------------------------------------------------------------------
void Dbl_RteAccess_Read_EcuSide(teDbl_MountingSide* eEcuSide)
{
  teRte_MountingSide eMountingSide = { 0 };

  (void)Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);

  switch (eMountingSide)
  {
  case eMountedLeft:
    *eEcuSide = Dbl_eMountedLeft;
    break;
  case eMountedRight:
    *eEcuSide = Dbl_eMountedRight;
    break;
  default:
    *eEcuSide = Dbl_eMountedRight;
    break;
  }
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_WriteDriveSituation
///
/// \descr  writes driving situation 
///
/// \param  uint8 ucDblDriveSit - raw data of curent driving situation
///
/// \return void
//-----------------------------------------------------------------------------
void Dbl_RteAccess_WriteDriveSituation(uint8 ucDblDriveSit)
{
  tsRte_AfsDblDriveSituation sDblDriveSit = { 0 };

  (void)Rte_Read_AfsDbl_DblDriveSit(&sDblDriveSit); 

  sDblDriveSit.ucData = ucDblDriveSit;

  (void)Rte_Write_AfsDbl_DblDriveSit(&sDblDriveSit); 
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_ReadGfhbCmd
///
/// \descr  reads GFHB - Glare free high beam command
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 Dbl_RteAccess_ReadGfhbCmd(void)
{
  tsRte_SysMonAfsSignals                 sAFSSignalsMsg;
  uint8 ucDblGfhbCmd;

  (void)Rte_Read_SysMon_Afs_Signals(&sAFSSignalsMsg);

  if (sAFSSignalsMsg.eSigQty == SIG_VALID)
  {
    //PRQA S 4394 ++  // cast is needed
    ucDblGfhbCmd = (uint8)(sAFSSignalsMsg.eGfhb_Cmd);
  }
  else
  {
    ucDblGfhbCmd = 0u;
  }
  return ucDblGfhbCmd;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_ReadGfhbCmd
///
/// \descr  reads GFHB - Glare free high beam command
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 Dbl_RteAccess_ReadHbCmd(void)
{
  tsRte_SysMonLgtFctsReq                 sAFSLgtFctsReq;
  uint8 ucDblHbCmd;

  (void)Rte_Read_SysMon_StdLgtFcts_Req(&sAFSLgtFctsReq);

  if (sAFSLgtFctsReq.eSigQty == SIG_VALID)
  {
    //PRQA S 4394 ++  // cast is needed
    ucDblHbCmd = (uint8)(sAFSLgtFctsReq.eHb_Request);
  }
  else
  {
    ucDblHbCmd = 0u;
  }
  return ucDblHbCmd;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_ReadFlashBeamCmd
///
/// \descr  reads GFHB - Glare free high beam command
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 Dbl_RteAccess_ReadFlashBeamCmd(void)
{
  tsRte_SysMonLgtFctsReq  sAFSLgtFctsReq = { 0 };
  uint8 ucDblFlashBeamCmd;

  (void)Rte_Read_SysMon_StdLgtFcts_Req(&sAFSLgtFctsReq);

  if (sAFSLgtFctsReq.eSigQty == SIG_VALID)
  {
    //PRQA S 4394 ++  // cast is needed
    ucDblFlashBeamCmd = (uint8)(sAFSLgtFctsReq.eHbFlash_Request);
  }
  else
  {
    ucDblFlashBeamCmd = 0u;
  }
  return ucDblFlashBeamCmd;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_WriteSwimRate
///
/// \descr  writes swim rate
///
/// \param  void
///
/// \return teRte_PrimaryCmd
//-----------------------------------------------------------------------------
void Dbl_RteAccess_WriteSwimRate(tsDbl_SwiRateLimMsg sDblLimits)
{
  tsRte_SwiRateLimMsg sSwiRateLim = { 0 };

  for (uint8 idx = 0u; idx < DBL_RTEACCESS_SIDES_NB; idx++)
  {
    sSwiRateLim.nLimit[idx] = sDblLimits.nLimit[idx];
  }

  (void)Rte_Write_AfsDbl_SwiRateLimMsg(&sSwiRateLim); 
}


//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_ReadYawSpeed
///
/// \descr  Get the Vehicle lateral speed
///
/// \param  -
///
/// \return sYawSpeed
//-----------------------------------------------------------------------------
tsDbl_YawSpeed Dbl_RteAccess_ReadYawSpeed(void)
{
  tsRte_SigPrep_YawSpeed sCanInput = { 0 };
  tsDbl_YawSpeed sYawSpeed = { 0 };
  (void)Rte_Read_SigPrep_YawSpeed(&sCanInput);

  if ((sCanInput.eSigQty == SIG_TIMEOUT) || (sCanInput.eSigQty == SIG_INVALID))
  {
    sYawSpeed.eYawSpeed.nYawSpeed = 0;
    sYawSpeed.eSigQty = Dbl_SIG_INVALID;
  }
  else
  {
    sYawSpeed.eYawSpeed.nYawSpeed = sCanInput.eYawSpeed.nYawSpeed;
    sYawSpeed.eSigQty = Dbl_SIG_VALID;
  }
  return sYawSpeed;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_ReadSteeringWheelAngle
///
/// \descr  Get the steering wheel angle value
///
/// \param  -
///
/// \return sSteeringWheelAngle
//-----------------------------------------------------------------------------
tsDbl_SteeringWheelAngle  Dbl_RteAccess_ReadSteeringWheelAngle(void)
{
  tsRte_SigPrep_SteeringWheelAngle sCanInput = { 0 };
  tsDbl_SteeringWheelAngle sSteeringWheelAngle = { 0 };

  (void)Rte_Read_SigPrep_SteeringWheelAngle(&sCanInput);

  if ((sCanInput.eSigQty == SIG_TIMEOUT) || (sCanInput.eSigQty == SIG_INVALID))
  {
    sSteeringWheelAngle.nSteeringWheelAngle = 0;
    sSteeringWheelAngle.eSigQty = Dbl_SIG_INVALID;
  }
  else
  {
    sSteeringWheelAngle.nSteeringWheelAngle = sCanInput.nSteeringWheelAngle;
    sSteeringWheelAngle.eSigQty = Dbl_SIG_VALID;
  }
  return sSteeringWheelAngle;
}

//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_ReadVehicleSpeed
///
/// \descr  Get the Vehicle vehicle speed value
///
/// \param  -
///
/// \return sSpeedMsg
//-----------------------------------------------------------------------------
tsDbl_VehicleSpeed  Dbl_RteAccess_ReadVehicleSpeed(void)
{
  tsRte_SysMon_VehicleSpeed sCanInput = { 0 };
  static tsDbl_VehicleSpeed   sSpeedMsg = { 0 };

  (void)Rte_Read_SysMon_VehicleSpeed(&sCanInput);

  if ((sCanInput.eSigQtyDbl == SIG_TIMEOUT) || (sCanInput.eSigQtyDbl == SIG_E2E_CRCERR) || (sCanInput.eSigQtyDbl == SIG_E2E_ALIVEERR) ||
    ((sCanInput.eSigQtyDbl == SIG_INVALID) && (sCanInput.eVehicleSpeedDispo != eVvhIndisp_SpeedInfoUnavailable)))
  {
    sSpeedMsg.eVehicleSpeed.unVehicleSpeed = 0;
    sSpeedMsg.eSigQty = Dbl_SIG_INVALID;
  }
  else if (((sCanInput.eSigQtyDbl == SIG_VALID) && (sCanInput.eVehicleSpeedDispo == eVvhIndisp_SpeedInfoAvailable)) ||
           ((sCanInput.eSigQtyDbl == SIG_INVALID) && (sCanInput.eVehicleSpeedDispo == eVvhIndisp_SpeedInfoUnavailable)))
  {
    sSpeedMsg.eVehicleSpeed.unVehicleSpeed = sCanInput.eVehicleSpeed.unVehicleSpeed;
    sSpeedMsg.eSigQty = Dbl_SIG_VALID;
  }
  else
  {
    // nothing to do
  }
  return sSpeedMsg;
}


//-----------------------------------------------------------------------------
/// \brief  Dbl_RteAccess_ReadVehicleElectricState
///
/// \descr  reads vechicle electric state
///
/// \param  void
///
/// \return uint8
//-----------------------------------------------------------------------------
teDbl_SigQty Dbl_RteAccess_ReadEtatReseauElec(void)
{
  tsRte_SysMon_VehNetState                 sVechStateMsg;
  teDbl_SigQty sRetSigQty;
  (void)Rte_Read_SysMon_VehNetState(&sVechStateMsg);
  switch (sVechStateMsg.eSigQty)
  {
  case SIG_VALID:
  case SIG_INIT :
  case SIG_SNA  :
    if (sVechStateMsg.eElectricNetworkState != eInvalid)
    {
      sRetSigQty = Dbl_SIG_VALID;
    }
    else
    {
      sRetSigQty = Dbl_SIG_INVALID;
    }
    break;

  default:
    sRetSigQty = Dbl_SIG_INVALID;
    break;
  }
  return sRetSigQty;
}

#endif // CFG_VARIANT_FULL
