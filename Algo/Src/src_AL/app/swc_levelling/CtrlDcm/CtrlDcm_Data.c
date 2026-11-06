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
/// \file  CtrlDcm_Data.c
///
/// \brief Access for CtrlDcm to coding data
///
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
//#include <IntegrationTest.h>
#include "CtrlDcm_Data.h"
#include "CtrlDcm_RteAccess.h"
#include "ILCU_LevellingAdapter.h" /* ILCU_PORT: replaces DPE-only <Nvm.h> */

//-----------------------------------------------------------------------------
// local types
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// variables
//-----------------------------------------------------------------------------
//STATIC_AL tCtrlStp_CodingData CtrlStp_CodingData;

STATIC_AL tNvmPara_AvacStpBlock CtrlDcm_CodingData = NVMPARA_AVACSTPBLOCK_INIT;
STATIC_AL sint16 CtrlDcm_snMin_ASL_Adjust  = 0;
STATIC_AL sint16 CtrlDcm_snMax_ASL_Adjust  = 0;
STATIC_AL sint8  CtrlDcm_scSafety_Position = 0;
STATIC_AL tNvmPara_AvacStp_DCMotorData     CtrlDcm_sDCMotorData = { 0 };

//-----------------------------------------------------------------------------
// interface functions
//-----------------------------------------------------------------------------
sint8   Cod_DcmMinVehAtt(void) { return CtrlDcm_CodingData.DCMotorData.scMin_Vehicle_Attitude; }//[0.1 deg]
sint8   Cod_DcmMaxVehAtt(void) { return CtrlDcm_CodingData.DCMotorData.scMax_Vehicle_Attitude; }//[0.1 deg]
sint16  Cod_DcmMinAdjASL(void) { return CtrlDcm_snMin_ASL_Adjust; }
sint16  Cod_DcmMaxAdjASL(void) { return CtrlDcm_snMax_ASL_Adjust; }
sint16  Cod_DcmSp(void)        { return (sint16)CtrlDcm_scSafety_Position; }
uint8   Cod_DcmVehAttThrStill(void)     { return CtrlDcm_CodingData.DCMotorData.ucVEHICLE_ATTITUDE_ADJUSTEMENT_THRESHOLD_STANDSTILL; }
uint8   Cod_DcmFrozenVehSpeedASL(void)  { return CtrlDcm_CodingData.DCMotorData.ucASL_FROZEN_VEH_SPEED; }
boolean Cod_DcmEnable(void)             { return (NvmBlockDeltaPwmPara.eASL_Present != eASL_Absent) ? TRUE : FALSE; }
uint8   Cod_DcmVehAttThrMotion(void)    { return CtrlDcm_CodingData.DCMotorData.ucVEHICLE_ATTITUDE_ADJUSTEMENT_THRESHOLD_MOTION; }
uint8   Cod_DcmMotionDelayASL(void)     { return CtrlDcm_CodingData.DCMotorData.ucASL_MOTION_DELAY; }

//-----------------------------------------------------------------------------
/// \brief  Check if coding data are available
///
/// \descr  Check also EFT data (in this case coding data is illegal)
///         and mounting side (needed to select coding data)
///
/// \param  pMountingSide
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CtrlDcm_CodingDataReady(teCtrlDcm_MountingSide* pMountingSide)
{
  boolean         boRet = FALSE;

  tsRteCodingParameters sCodingParameters;

  (void)Rte_Read_CodM_Pitch_Para(&sCodingParameters);

  if ((((uint8)*pMountingSide == (uint8)eMountedLeft) || ((uint8)*pMountingSide == (uint8)eMountedRight))
    && (sCodingParameters.eCodingState == eParaFct0_CodingDataValid))
  {
    boRet = TRUE;
  }

  return boRet;

}


//-----------------------------------------------------------------------------
/// \brief  Read coding data
///
/// \descr  Read coding data and store results in local variables
///         Do scaling calculations if needed
///
/// \param  MountingSide
///
/// \return void
//-----------------------------------------------------------------------------
void CtrlDcm_ParaFct0 (tParaFct0_Cmd eCmd, tNvmPara_CodingArea*  pData)
{
  (void)pData;

  teCtrlDcm_MountingSide eMountingSide;

  (void)CtrlDcm_RteAccess_Read_EcuSide(&eMountingSide);

  if (eCmd == eParaFct0_CodingDataValid)
  {
    CtrlDcm_CodingData = pData->AvacStp;
  }
  else
  {
   // leave init values
  }
  
  if (eMountingSide == CtrlDcm_eMountedLeft)
  {
    CtrlDcm_snMin_ASL_Adjust  = CtrlDcm_CodingData.DCMotorData.snMin_ASL_Adjust_Left;
    CtrlDcm_snMax_ASL_Adjust  = CtrlDcm_CodingData.DCMotorData.snMax_ASL_Adjust_Left;
    CtrlDcm_scSafety_Position = CtrlDcm_CodingData.DCMotorData.scSafety_Position_Left;
  }
  else if (eMountingSide == CtrlDcm_eMountedRight)
  {
    CtrlDcm_snMin_ASL_Adjust  = CtrlDcm_CodingData.DCMotorData.snMin_ASL_Adjust_Right;
    CtrlDcm_snMax_ASL_Adjust  = CtrlDcm_CodingData.DCMotorData.snMax_ASL_Adjust_Right;
    CtrlDcm_scSafety_Position = CtrlDcm_CodingData.DCMotorData.scSafety_Position_Right;
  }
  else
  {
    // no behavior
  }
}

