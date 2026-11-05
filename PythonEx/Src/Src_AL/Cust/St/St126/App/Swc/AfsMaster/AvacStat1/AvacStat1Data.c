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
/// \file  AvacStat1Data.c
///
/// \brief  
///
/// \descr  
///
///         Additional information can be found in the design description 
///
/// \author Alf Traulsen  (taf2rt)
//-----------------------------------------------------------------------------

#include <Std_Types.h>
#include <Nvm.h>
#ifndef UNIT_TEST
#include <Rte.h>
#endif

#include "AvacStat1Data.h"

//=============================================================================
// variables
//=============================================================================

tNvmPara_CodingArea*  AvacStat1_pCodingArea;
STATIC_AL boolean               AvacStat1Data_boLowBeamOn = TRUE;

//=============================================================================
// functions prototype
//=============================================================================

STATIC_AL boolean AvacStat1Data_ParaFct0(tParaFct0_Cmd eCmd, tNvmPara_CodingArea* CONST_AL pData);

//-----------------------------------------------------------------------------
/// \brief Pitch_RteAccess_Get_CodingPara
///
/// \descr Wrapper function for Rte_Read_CodM_Pitch_Para
///
/// \param  psCodingParam
///
/// \return void
//-----------------------------------------------------------------------------
void AvacStat1Data_Get_CodingPara(tsAvacStat1_CodingParam *psCodingParam)
{
  tsRteCodingParameters psAvacStat1CodingParameters;

  //read coding
  (void)Rte_Read_CodM_Pitch_Para(&psAvacStat1CodingParameters);
  psCodingParam->eCodingState = psAvacStat1CodingParameters.eCodingState;
  psCodingParam->psCodingParameters_Blocks = psAvacStat1CodingParameters.psCodingParameters_Blocks;
}


//-----------------------------------------------------------------------------
/// \brief  AvacStat1Data_CodingDataValidation
///
/// \descr  get and handle coding parameters for Pitch module
///
/// \param  void
///
/// \return return validity of coding as TRUE
//-----------------------------------------------------------------------------
boolean AvacStat1Data_CodingDataValidation(void)
{
  tsAvacStat1_CodingParam sCodingParameters;
  //get coding data via RTE
  AvacStat1Data_Get_CodingPara(&sCodingParameters);
  //get coding data and return validity of this
  CONST_AL boolean boCodingValidity = AvacStat1Data_ParaFct0(sCodingParameters.eCodingState, sCodingParameters.psCodingParameters_Blocks);
  //return validity of coding
  return boCodingValidity;
}


//-----------------------------------------------------------------------------
/// \brief  AvacStat1Data_ParaFct0
///
/// \descr  this function get coding params and validity of coding data
///
/// \param  eCmd - valid/invalid, pData - coding params
///
/// \return coding validity
//-----------------------------------------------------------------------------
STATIC_AL boolean AvacStat1Data_ParaFct0(tParaFct0_Cmd eCmd, tNvmPara_CodingArea* CONST_AL pData)
{
  boolean boCodingValidity = FALSE;

  switch (eCmd)
  {
  case eParaFct0_CodingDataValid:
    AvacStat1_pCodingArea = pData;
    boCodingValidity = (AvacStat1_pCodingArea == NULL_PTR) ? FALSE : TRUE;
    break;
  case eParaFct0_CodingDataInvalid:
    boCodingValidity = FALSE;
    break;
  default:
    break;
  }

  return boCodingValidity;
}

void AvacStat1Data_Init(void)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief  AvacStat1Data_GetLowBeamOn
///
/// \descr  get low beam state
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
boolean AvacStat1Data_GetLowBeamOn(void)
{
  //tEnvConditionMsg EnvConditionMsg;
  //(void) Rte_Read_SigPrepRx_EnvConditionMsg_Port(&EnvConditionMsg);
  //
  //// if light is switched on physically, AVAC must be active.
  //if (EnvConditionMsg.State.LowBeam == 1U)
  //{
  return AvacStat1Data_boLowBeamOn;
  //}

#if (CFG_OPT_ENVCOND & CFG_EnvCond_SuppLoBmOnRq)  
  if (EnvConditionMsg.State.LowBeamOnReq == ON) 
  { 
    return TRUE; 
  }
#endif


  //return FALSE;
//PRQA S 5338 1 // Program architecture and code readability.
}

//-----------------------------------------------------------------------------
/// \brief  AvacStat1Data_GetAvacS_Ok()
///
/// \descr  
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
boolean AvacStat1Data_GetAvacS_Ok(void)
{
  //tEcuFuncCtrlMsg EcuFuncCtrlMsg;
  //(void) Rte_Read_SigPrepRx_EcuFuncCtrlMsg_Port(&EcuFuncCtrlMsg);
  //
  //if (EcuFuncCtrlMsg.Flags.ucOkFlags & LIT_EcuFuncOk_AvacS)
  //{
  //  return TRUE;
  //}
  //else
  //{
  //  return FALSE;
  //}
  //PRQA S 5338 1 // Program architecture and code readability.
  return TRUE;
}

//-----------------------------------------------------------------------------
/// \brief  AvacStat1Data_GetAvacS_En()
///
/// \descr  
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
boolean AvacStat1Data_GetAvacS_En(void)
{
  //tEcuFuncCtrlMsg EcuFuncCtrlMsg;
  //(void) Rte_Read_SigPrepRx_EcuFuncCtrlMsg_Port(&EcuFuncCtrlMsg);
  //
  //if (EcuFuncCtrlMsg.Flags.ucEnFlags & LIT_EcuFuncEn_AvacS)
  //{
  //  return TRUE;
  //}
  //else
  //{
  //  return FALSE;
  //}
  //PRQA S 5338 1 // Program architecture and code readability.
  return TRUE;
}

//-----------------------------------------------------------------------------
/// \brief  AvacStat1Data_GetPitch()
///
/// \descr  
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
void AvacStat1Data_ReadPitch(tAvacStat_Pitch* pPitch)
{
  tPitch0                          sPitchBhs;
  tsRte_SigPrep_VehiclePitchAngle  sPitchAmvar;

  // Read BHS data
  (void)Rte_Read_Pitch_Angle(&sPitchBhs);

  pPitch->nAngle     = sPitchBhs.nAngle;       // [0.1mrad] 
  pPitch->nHeightErr = sPitchBhs.nHeightErr;   // [0.1mrad]
  pPitch->eSigQty    = sPitchBhs.eSigQty;      // same definition of RTE and app
}

//-----------------------------------------------------------------------------
/// \brief  AvacStat1Data_GetSpeed()
///
/// \descr  
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
void AvacStat1Data_ReadSpeed(tAvacStat_Speed* pSpeed)
{
  //tSpeedMsg SpeedMsg;
  tsRte_SysMon_VehicleSpeed  SpeedMsg;
  tsRte_SigPrep_DynamicSigs  AccelPreDetectMsg;

  // read data from RTE
  (void)Rte_Read_SysMon_VehicleSpeed(&SpeedMsg);
  (void)Rte_Read_SigPrep_DynamicSigs(&AccelPreDetectMsg);

  // convert to app
  pSpeed->nSpeed = (sint16)SpeedMsg.eVehicleSpeed.unVehicleSpeed;               // [0.1 km/h]
  pSpeed->nAcceleration = (sint16)AccelPreDetectMsg.ePedalAcceleration.ucPedalAcceleration;//SpeedMsg.Acceleration;                 // [0.1 m/s^2]
  pSpeed->unMotion = 0;//SpeedMsg.Motion;              // same definition of RTE and app
  pSpeed->eSigQty = (teRte_SigQty)SpeedMsg.eSigQty;  // same definition of RTE and app
}

//-----------------------------------------------------------------------------
/// \brief  AvacStat1Data_SetOut()
///
/// \descr  
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
void AvacStat1Data_WriteAvacOut(const tAvacStat_Out* pAvacOut)
{
  tPositionOut  PosOut;
  sint16        nAngle; 

  // convert data from app
  PosOut.State = (uint8)pAvacOut->eSigQty;

  // convert internal Avac-Data [0.1mrad] to RTE-Data [0.01 deg]
  nAngle = pAvacOut->nAngle;
  nAngle = (nAngle >= 0) ? (sint16)((((sint32)nAngle * 180) + 157) / 314)
                         : (sint16)((((sint32)nAngle * 180) - 157) / 314);

  PosOut.Position[0].Ver   = nAngle;
  PosOut.Position[0].Hor   = 0;
  PosOut.Position[0].Width = 0u;


  // write data to RTE
  (void)Rte_Write_ppsAvacStat1Out_Port(&PosOut);
}

//-----------------------------------------------------------------------------
/// \brief  AvacStat1Data_WriteSpeedMode()
///
/// \descr  Wrapper function for Rte_Write_AvacStat1_SpeedMode
///
/// \param  pAvacSpeedMode
///
/// \return void 
//-----------------------------------------------------------------------------
void AvacStat1Data_WriteSpeedMode(const teAvacStat_SpeedMode* peAvacSpeedMode)
{
  teRte_DcmSpeedMode  eSpeedModeOut;

  switch (*peAvacSpeedMode)
  {
  case eLOW_SPEED:     {eSpeedModeOut = eDcm_LOW_SPEED; }   break;
  case eHIGH_SPEED:    {eSpeedModeOut = eDcm_HIGH_SPEED; }  break;
  default:             {eSpeedModeOut = eDcm_UNDEF_SPEED; } break;
  }

  // write data to RTE
  (void)Rte_Write_AvacStat1_SpeedMode(&eSpeedModeOut);
}

//-----------------------------------------------------------------------------
/// \brief AvacStat1Data_ReadAslPhase
///
/// \descr Wrapper function for Rte_Read_CtrlDcm_StatusParameters_Port
///
/// \param  psData
///
/// \return void
//-----------------------------------------------------------------------------
void AvacStat1Data_ReadAslPhase(teAvacStat1_LvlPhase* psData)
{
  tsRte_CtrlDcmStatusParams sAslPhase;
  (void)Rte_Read_CtrlDcm_StatusParameters_Port(&sAslPhase);

  switch (sAslPhase.eASL_PHASE)
  {
  case eDcmPhase_Adj:  {*psData = eAvacStat1State_Adj; }        break;
  case eDcmPhase_Fail: {*psData = eAvacStat1State_Fail; }       break;
  default:             {*psData = eAvacStat1State_Init; }       break;
  }
}
