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
/// \file  Pitch_RteAccess.c
///
/// \brief This file is an RTE wrapper
///
/// \author Adrian Horlescu (F31197D)
///         mailTo:adrian-marian.horlescu[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#include "Pitch_RteAccess.h"
#ifndef UNIT_TEST
#include <RteCommonTypes.h>
#endif //UNIT_TEST


//=============================================================================
// getter functions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief Pitch_RteAccess_Get_VehicleSpeed
///
/// \descr Wrapper function for Rte_Read_SysMon_VehicleSpeed
///
/// \param  psData
///
/// \return void
//-----------------------------------------------------------------------------
void Pitch_RteAccess_Get_VehicleSpeed(tsPitch_VehicleSpeed* psData)
{
  tsRte_SysMon_VehicleSpeed sVehicleSpeed;
  (void)Rte_Read_SysMon_VehicleSpeed(&sVehicleSpeed);
  psData->eChksumTrmeDynUcFrein = sVehicleSpeed.eChksumTrmeDynUcFrein;
  psData->eCptProcess4B38D      = sVehicleSpeed.eCptProcess4B38D;
  psData->eSigQty               = sVehicleSpeed.eSigQty;
  psData->eVehicleSpeed         = sVehicleSpeed.eVehicleSpeed;
  psData->eVehicleSpeedDispo    = sVehicleSpeed.eVehicleSpeedDispo;
}

//-----------------------------------------------------------------------------
/// \brief Pitch_RteAccess_Get_VehNetState
///
/// \descr Wrapper function for Rte_Read_SysMon_VehNetState
///
/// \param  psData
///
/// \return void
//-----------------------------------------------------------------------------
void Pitch_RteAccess_Get_VehNetState(tsPitch_VehNetState* psData)
{
  tsRte_SysMon_VehNetState sVehNetState;
  (void)Rte_Read_SysMon_VehNetState(&sVehNetState);
  psData->eElectricNetworkState = sVehNetState.eElectricNetworkState;
  psData->eSigQty               = sVehNetState.eSigQty;
  psData->eVESMainState         = sVehNetState.eVESMainState;
}

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
//-----------------------------------------------------------------------------
/// \brief Pitch_RteAccess_Get_GetAdlPhase
///
/// \descr Wrapper function for Rte_Read_CtrlStp_Validation_Port
///
/// \param  psData
///
/// \return void
//-----------------------------------------------------------------------------
void Pitch_RteAccess_Get_GetAdlPhase(tePitch_LvlPhase* psData)
{
  tsRte_CtrlStpValidation sAdlPhase;
  (void)Rte_Read_CtrlStp_Validation_Port(&sAdlPhase);

  switch (sAdlPhase.eADL_PHASE)
  {
  case eStpState_Init:    {*psData = ePitchState_Init; }    break;
  case eStpState_Ref:     {*psData = ePitchState_Ref; }     break;
  case eStpState_Adj:     {*psData = ePitchState_Adj; }     break;
  case eStpState_Fail:    {*psData = ePitchState_Fail; }    break;
  case eStpState_STT:     {*psData = ePitchState_STT; }     break;
  case eStpState_Maxsize: {*psData = ePitchState_Maxsize; } break;
  default: break;
  }
}
#endif
#if defined(SAMPLE_ECO) || defined(UNIT_TEST)
//-----------------------------------------------------------------------------
/// \brief Pitch_RteAccess_Get_GetAdlPhase
///
/// \descr Wrapper function for Rte_Read_CtrlStp_Validation_Port
///
/// \param  psData
///
/// \return void
//-----------------------------------------------------------------------------
void Pitch_RteAccess_Get_GetAslPhase(tePitch_LvlPhase* psData)
{
  tsRte_CtrlDcmStatusParams sAslPhase;
  (void)Rte_Read_CtrlDcm_StatusParameters_Port(&sAslPhase);

  switch (sAslPhase.eASL_PHASE)
  {
  case eDcmPhase_Init:    {*psData = ePitchState_Init; }       break;
  case eDcmPhase_Adj:     {*psData = ePitchState_Adj; }        break;
  case eDcmPhase_Fail:    {*psData = ePitchState_Fail; }       break;
  default: break;
  }
}
#endif

//-----------------------------------------------------------------------------
/// \brief Pitch_RteAccess_Get_GetSens_Raw
///
/// \descr Wrapper function for Rte_Read_IoHwAb_GetSens_Raw
///
/// \param  aucCntSens
///
/// \return void
//-----------------------------------------------------------------------------
void Pitch_RteAccess_Get_GetSens_Raw(uint16* punCntSens)
{
  //PRQA S 310 1 // Cast needed
  (void)Rte_Read_IoHwAb_GetSens_Raw((tsRte_SensorRaw*)punCntSens);
}


//-----------------------------------------------------------------------------
/// \brief Pitch_RteAccess_Get_GetSens_Balanced
///
/// \descr Wrapper function for Rte_Read_IoHwAb_GetSens_Balanced
///
/// \param  alCntSens
///
/// \return void
//-----------------------------------------------------------------------------
void Pitch_RteAccess_Get_GetSens_Balanced(sint32* pslCntSens)
{
  //PRQA S 310 1 // Cast needed
  (void)Rte_Read_IoHwAb_GetSens_Balanced((tsRte_SensorBalance*)pslCntSens);
}


//-----------------------------------------------------------------------------
/// \brief Pitch_RteAccess_Get_VCCX1Voltage
///
/// \descr Wrapper for Pitch_RteAccess_Get_VCCX1Voltage
///
/// \param  punVccx1
///
/// \return void
//-----------------------------------------------------------------------------
void Pitch_RteAccess_Get_VCCX1Voltage(uint16* punVccx1)
{
  tiu16Voltage_mV unVccx1_Access;
  (void) Rte_Read_IoHwAb_VCCX1Voltage(&unVccx1_Access);
  *punVccx1 = (uint16)unVccx1_Access;

}


//-----------------------------------------------------------------------------
/// \brief Pitch_RteAccess_Get_CodingPara
///
/// \descr Wrapper function for Rte_Read_CodM_Pitch_Para
///
/// \param  psCodingParam
///
/// \return void
//-----------------------------------------------------------------------------
void Pitch_RteAccess_Get_CodingPara(tsPitch_CodingParam *psCodingParam)
{
  tsRteCodingParameters psPitchCodingParameters;

  //read coding
  (void)Rte_Read_CodM_Pitch_Para(&psPitchCodingParameters);
  psCodingParam->eCodingState = psPitchCodingParameters.eCodingState;
  psCodingParam->psCodingParameters_Blocks = psPitchCodingParameters.psCodingParameters_Blocks;
}


//=============================================================================
// setter functions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief Pitch_RteAccess_Set_Angle
///
/// \descr Wrapper function for Rte_Write_Pitch_Angle
///
/// \param  psPitch
///
/// \return void
//-----------------------------------------------------------------------------
void Pitch_RteAccess_Set_Angle(tsPitch* psPitch)
{
  tPitch0 sPitchAccess;

  sPitchAccess.eSigQty    = psPitch->eSigQty;
  sPitchAccess.nAngle     = psPitch->nAngle;
  sPitchAccess.nHeightErr = psPitch->nHeightErr;

  (void)Rte_Write_Pitch_Angle(&sPitchAccess);
}


//-----------------------------------------------------------------------------
/// \brief Pitch_RteAccess_Set_SensorFailureState
///
/// \descr Wrapper function for Rte_Write_PitchPlausState
///
/// \param  pePitch
///
/// \return void
//-----------------------------------------------------------------------------
void Pitch_RteAccess_Set_SensorFailureState(tePitchSensorState* pePitch)
{
  teRte_HlsSensorState ePitchSensorState;

  switch (*pePitch)
  {
  case eHLS_NO_FAILURE:     {ePitchSensorState = eNO_FAILURE; }     break;
  case eHLS_SENSOR_FAILURE: {ePitchSensorState = eSENSOR_FAILURE; } break;
  case eHLS_FROZEN_FAILURE: {ePitchSensorState = eFROZEN_FAILURE; } break;
  case eHLS_STORED_FAILURE: {ePitchSensorState = eSTORED_FAILURE; } break;
  default: break;
  }

  (void)Rte_Write_Pitch_PlausState(&ePitchSensorState);
}
//EOF
