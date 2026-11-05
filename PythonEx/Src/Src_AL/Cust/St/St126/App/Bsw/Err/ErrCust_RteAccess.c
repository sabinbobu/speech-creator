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
/// \file   ErrCust_RteAccess.c
///
/// \brief  encapsule RTE access
///
/// \descr  Functions used for the ErrCust RTE wrapper, for input/output 
///
/// \author 
///    
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================

#include <Bsw/Err/ErrCust_RteAccess.h>
#include <Bsw/Err/ErrCust_Types.h>

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \brief  ErrCust_RteAccess_Read_CtrlStp_ActStatStp
///
/// \descr  Read RTE wrapper to CtrlStp for Actual status data
///
/// \param  *psActStatStp
///
/// \return void
//-----------------------------------------------------------------------------
void ErrCust_RteAccess_Read_CtrlStp_ActStatStp(tsErrCust_TypesActStatStp *psActStatStp)
{
  tsRte_ActStatStp0 sActStatStp0;
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST) 
  // read RTE port for Stp data
  (void)Rte_Read_CtrlStp_ActStatStp_sVal_0(&sActStatStp0);
#endif

  (*psActStatStp).cStpPosDegree   = sActStatStp0.StatStp.cStatStpPosDegree;
  (*psActStatStp).ucStsAutoLvl    = (uint8)sActStatStp0.StatStp.eStatStpLevelStatus;
  (*psActStatStp).boStpLossLvl    = (sActStatStp0.StatStp.eStatStpStepLoss == eStepLossRisk) ? TRUE : FALSE;
  (*psActStatStp).boCommDefLvl    = sActStatStp0.StatStp.boStpCommDef;
  (*psActStatStp).boElecDefLvl    = (sActStatStp0.StatStp.eStatStpElectricDefect == eNoElectricalDefect) ? FALSE : TRUE;
  (*psActStatStp).boMoveLvlStp    = sActStatStp0.StatStp.boStpIsMoving;
  (*psActStatStp).boPosDefLvl     = sActStatStp0.StatStp.boStpPosDef;
  (*psActStatStp).boThermDefLvl   = (sActStatStp0.StatStp.eStatStpThermalState == eNoThermalWarning) ? FALSE : TRUE;
}

//-----------------------------------------------------------------------------
/// \brief  ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide
///
/// \descr  Read RTE wrapper to IoHwAbUser for headlamp side
///
/// \param  *peEcuSide
///
/// \return void
//-----------------------------------------------------------------------------
void ErrCust_RteAccess_Read_IoHwAbUser_GetMountingSide(teErrCust_Types_MountingSide *peEcuSide)
{
  teRte_MountingSide eMountingSide = { 0 };

  (void)Rte_Read_IoHwAbUser_GetMountingSide(&eMountingSide);

  switch (eMountingSide)
  {
  case eMountedLeft:
    *peEcuSide = eLeft;
    break;
  case eMountedRight:
    *peEcuSide = eRight;
    break;
  default:
    *peEcuSide = eUndef;
    break;
  }

}

//-----------------------------------------------------------------------------
/// \brief  ErrCust_RteAccess_Read_FctR_LgtFctErrState
///
/// \descr  Read RTE wrapper to FctR for Light Functions state
///
/// \param  *peErrCust_RteAccess_LgtFctState
///
/// \return void
//-----------------------------------------------------------------------------
void ErrCust_RteAccess_Read_FctR_LgtFctErrState(tsErrCust_LgtFctState *psErrCust_RteAccess_LgtFctState)
{
  tsRte_LgtFctState sLgtFctState;
  // Read Light Functions state
  (void)Rte_Read_FctR_LgtFctState(&sLgtFctState);

  psErrCust_RteAccess_LgtFctState->boLb_State = sLgtFctState.boLb_State != FALSE ? TRUE : FALSE;
  psErrCust_RteAccess_LgtFctState->boSbl_State = sLgtFctState.boSbl_State != FALSE ? TRUE : FALSE;
  psErrCust_RteAccess_LgtFctState->boTi_State = sLgtFctState.boTi_State != FALSE ? TRUE : FALSE;
  psErrCust_RteAccess_LgtFctState->boHb_State = sLgtFctState.boHb_State != FALSE ? TRUE : FALSE;
  psErrCust_RteAccess_LgtFctState->boGfHb_State = sLgtFctState.boGfHb_State != FALSE ? TRUE : FALSE;
  psErrCust_RteAccess_LgtFctState->boDrl_State = sLgtFctState.boDrl_State != FALSE ? TRUE : FALSE;
  psErrCust_RteAccess_LgtFctState->boPos_State = sLgtFctState.boPos_State != FALSE ? TRUE : FALSE;

}
//-----------------------------------------------------------------------------
/// \brief  ErrCust_RteAccess_Read_FctR_TI_FctErrState
///
/// \descr  Read RTE wrapper to FctR for Light Functions state
///
/// \param  *boErrCust_RteAccess_Lgt_TI_State
///
/// \return void
//-----------------------------------------------------------------------------
void ErrCust_RteAccess_Read_FctR_TI_FctErrState(boolean *boErrCust_RteAccess_Lgt_TI_State)
{
	boolean boLgt_TI_State;
	// Read Light TI state
	(void)Rte_Read_FctR_TiFailureStatus(&boLgt_TI_State);
  *boErrCust_RteAccess_Lgt_TI_State = boLgt_TI_State;
	
}
//-----------------------------------------------------------------------------
/// \brief  ErrCust_RteAccess_Read_FctR_LgtFctStatus
///
/// \descr  Read RTE wrapper to FctR for Light Functions status
///
/// \param  *peErrCust_RteAccess_LgtFctStatus
///
/// \return void
//-----------------------------------------------------------------------------
void ErrCust_RteAccess_Read_FctR_LgtFctStatus(tsErrCust_LgtFctStatus *psErrCust_RteAccess_LgtFctStatus)
{
  tsRte_LgtFctStatus sLgtFctStatus;
  // Read Light Functions Status
  (void)Rte_Read_FctR_LgtFctStatus(&sLgtFctStatus);

  psErrCust_RteAccess_LgtFctStatus->boLb_Status = sLgtFctStatus.boLb_Status != FALSE ? TRUE : FALSE;
  psErrCust_RteAccess_LgtFctStatus->boSbl_Status = sLgtFctStatus.boSbl_Status != FALSE ? TRUE : FALSE;
  psErrCust_RteAccess_LgtFctStatus->boTi_Status = sLgtFctStatus.boTi_Status != FALSE ? TRUE : FALSE;
  psErrCust_RteAccess_LgtFctStatus->boHb_Status = sLgtFctStatus.boHb_Status != FALSE ? TRUE : FALSE;
  psErrCust_RteAccess_LgtFctStatus->boGfHb_Status = sLgtFctStatus.boGfHb_Status != FALSE ? TRUE : FALSE;
  psErrCust_RteAccess_LgtFctStatus->boDrl_Status = sLgtFctStatus.boDrl_Status != FALSE ? TRUE : FALSE;
  psErrCust_RteAccess_LgtFctStatus->boPos_Status = sLgtFctStatus.boPos_Status != FALSE ? TRUE : FALSE;
  psErrCust_RteAccess_LgtFctStatus->boSM_Status = sLgtFctStatus.boSM_Status != FALSE ? TRUE : FALSE;
  psErrCust_RteAccess_LgtFctStatus->boFog_Status = sLgtFctStatus.boFog_Status != FALSE ? TRUE : FALSE;
}
//EOF
