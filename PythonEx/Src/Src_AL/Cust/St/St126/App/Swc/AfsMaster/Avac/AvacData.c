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
/// \file  AvacData.c
///
/// \brief
///
/// \descr
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Alf Traulsen  (taf2rt)
///         mailTo:alf.traulsen[at]al-lighting.com
//-----------------------------------------------------------------------------

#include <Std_Types.h>
//#include <Bsw/Nvm/Nvm.h>
//#include <BSW/Nvm/NvmPara.h>

#ifndef UNIT_TEST
#include <Rte.h>
#endif

#include <Rte/RteCommonTypes.h>
#include "AvacData.h"
#include <Swc/AfsMaster/Avac/AvacAlgDyn1.h>
#include <Nvm.h>

// ----------------------------------------------------------------------------
// Defines
// ----------------------------------------------------------------------------
#define AMVAR_MAX  500
#define AMVAR_MIN -500
#define AMVAR_FILTER 6u

// ----------------------------------------------------------------------------
// Variables
// ----------------------------------------------------------------------------
//const  tNvmPara_CodingArea*  AvacData_pCodingArea;
          boolean               AvacData_boCodingValid         = TRUE;
          boolean               AvacData_boPitchConfigValid    = TRUE;
STATIC_AL boolean               AvacData_boUseDynamicLeveling  = TRUE;
          uint8                 AvacData_ucFilterStatic        = 250;
          uint8                 AvacData_ucGradientLimiterUp   = AVAC_StaticAngleGradNormal;
          uint8                 AvacData_ucGradientLimiterDown = AVAC_StaticAngleGradNormal;
STATIC_AL boolean               AvacData_boLowBeamOn           = TRUE;
          tNvmPara_AvacStpBlock AvacData_CodingData            = NVMPARA_AVACSTPBLOCK_INIT;


// PRQA S 3206 LWarnAvacData_ParaFct0 // Program architecture and readability
void AvacData_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData)
{
  if (eCmd == eParaFct0_CodingDataValid)
  {
    AvacData_CodingData = pData->AvacStp;
  }
  else
  {
    // leave init values
  }
}
// PRQA L:LWarnAvacData_ParaFct0


void AvacData_Init(void)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief  AvacData_GetLowBeamOn
///
/// \descr  get low beam state
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
// PRQA S 1505 LWarnAvacData_GetLowBeamOn // Program architecture and readability
boolean AvacData_GetLowBeamOn(void)
{
 /* tEnvConditionMsg EnvConditionMsg;
  (void) Rte_Read_SigPrepRx_EnvConditionMsg_Port(&EnvConditionMsg);

  // if light is switched on physically, AVAC must be active.
  if (EnvConditionMsg.State.LowBeam == 1U)
  {
    return TRUE;
  }

#if (CFG_OPT_ENVCOND & CFG_EnvCond_SuppLoBmOnRq)
  if (EnvConditionMsg.State.LowBeamOnReq == ON)
  {
    return TRUE;
  }
#endif

#if (CFG_OPT_AM & CFG_Am_HasExtCmd)
  if (IsEcuFuncCmdExt(Vacd, BbGetMessageEcuFuncCmdExt(), amPLAY))
  {
    return TRUE;
  }
#endif*/ //TO DO

  return AvacData_boLowBeamOn;

//PRQA S 5338 1 // Program architecture and code readability.
}
// PRQA L:LWarnAvacData_GetLowBeamOn

//-----------------------------------------------------------------------------
/// \brief  AvacData_GetAvacS_Ok()
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
// PRQA S 5338 LWarnAvacData_GetAvacS_Ok // Program architecture and readability
boolean AvacData_GetAvacS_Ok(void)
{
  /*tEcuFuncCtrlMsg EcuFuncCtrlMsg;
  (void) Rte_Read_SigPrepRx_EcuFuncCtrlMsg_Port(&EcuFuncCtrlMsg);

  if (EcuFuncCtrlMsg.Flags.ucOkFlags & LIT_EcuFuncOk_AvacS)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }*/ // TO DO

  return TRUE;

}
// PRQA L:LWarnAvacData_GetAvacS_Ok

//-----------------------------------------------------------------------------
/// \brief  AvacData_GetAvacS_En()
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
// PRQA S 5338 LWarnAvacData_GetAvacS_En // Program architecture and readability
boolean AvacData_GetAvacS_En(void)
{
  /*tEcuFuncCtrlMsg EcuFuncCtrlMsg;
  (void) Rte_Read_SigPrepRx_EcuFuncCtrlMsg_Port(&EcuFuncCtrlMsg);

  if (EcuFuncCtrlMsg.Flags.ucEnFlags & LIT_EcuFuncEn_AvacS)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }*/ //TO DO

  return TRUE;
}
// PRQA L:LWarnAvacData_GetAvacS_En

//-----------------------------------------------------------------------------
/// \brief  AvacData_GetAvacD_Ok()
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
boolean AvacData_GetAvacD_Ok(void)
{
  return TRUE; // tbd AfsMaster implementieren
}

//-----------------------------------------------------------------------------
/// \brief  AvacData_GetAvacD_En()
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
boolean AvacData_GetAvacD_En(void)
{
  return AvacData_boUseDynamicLeveling; // tbd AfsMaster implementieren
}

//-----------------------------------------------------------------------------
/// \brief  AvacData_ReadPitch()
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void AvacData_ReadPitch(tAvac_Pitch* pPitch)
{
  tPitch0                          sPitchBhs;
  tsRte_SigPrep_VehiclePitchAngle  sPitchAmvar;

  // Read BHS data
  (void)Rte_Read_Pitch_Angle(&sPitchBhs);
  // Read AMVAR data
  (void)Rte_Read_SigPrep_VehiclePitchAngle(&sPitchAmvar);

  if (NvmBlockDeltaPwmPara.eNVM_VAC_Input == eInput_HLS)
  {
    pPitch->nAngle     = sPitchBhs.nAngle;       // [0.1mrad] 
    pPitch->nHeightErr = sPitchBhs.nHeightErr;   // [0.1mrad]
    pPitch->eSigQty    = sPitchBhs.eSigQty;      // same definition of RTE and app
  }
  else if (NvmBlockDeltaPwmPara.eNVM_VAC_Input == eInput_CAN)
  {
    // Subtraction from  AMVAR_Current - AMVAR_Offset  => AMVAR_Normalized
    sPitchAmvar.eAssietteVehicule.nVehiclePitchAngle -= NvmBlockDeltaPwmPara.snVehicleAttitude;
    // convert RTE-Data [0.01 deg] to internal Avac-Data [0.1mrad]
    sPitchAmvar.eAssietteVehicule.nVehiclePitchAngle = (sPitchAmvar.eAssietteVehicule.nVehiclePitchAngle >= 0)
      ? (sint16)((((sint32)sPitchAmvar.eAssietteVehicule.nVehiclePitchAngle * 314) + 157) / 180)
      : (sint16)((((sint32)sPitchAmvar.eAssietteVehicule.nVehiclePitchAngle * 314) - 157) / 180);

    pPitch->nAngle     = (-1)*sPitchAmvar.eAssietteVehicule.nVehiclePitchAngle;   // [0.1mrad] 
    pPitch->nHeightErr = 0;                                                  // [0.1mrad]
    pPitch->eSigQty    = sPitchAmvar.eSigQty;                                // same definition of RTE and app
  }
  else
  {
    pPitch->nAngle  = 0;
    pPitch->eSigQty = sPitchAmvar.eSigQty;
  }
}

//-----------------------------------------------------------------------------
/// \brief  AvacData_ReadSpeed()
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void AvacData_ReadSpeed(tAvac_Speed* pSpeed)
{
  //tSpeedMsg SpeedMsg;
  //(void) Rte_Read_SigPrepRx_SpeedMsg_Port(&SpeedMsg); TO DO

  tsRte_SysMon_VehicleSpeed  SpeedMsg;
  tsRte_SigPrep_DynamicSigs  AccelPreDetectMsg;

  (void)Rte_Read_SysMon_VehicleSpeed(&SpeedMsg);
  (void)Rte_Read_SigPrep_DynamicSigs(&AccelPreDetectMsg);

  // convert to app
  pSpeed->nSpeed        = (sint16)SpeedMsg.eVehicleSpeed.unVehicleSpeed;               // [0.1 km/h]
  pSpeed->nAcceleration = (sint16)AccelPreDetectMsg.ePedalAcceleration.ucPedalAcceleration;//SpeedMsg.Acceleration;                 // [0.1 m/s^2]
  pSpeed->unMotion      = 0;//SpeedMsg.Motion;              // same definition of RTE and app
  pSpeed->eSigQty       = (teRte_SigQty)SpeedMsg.eSigQty;  // same definition of RTE and app
}

//-----------------------------------------------------------------------------
/// \brief  AvacData_ReadAccelPreDetect()
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void AvacData_ReadAccelPreDetect(tAvac_AccelPreDetect* pAccelPreDetect)
{
    tsRte_SigPrep_DynamicSigs  AccelPreDetectMsg;
    //(void) Rte_Read_SigPrepRx_AccelPreDetectMsg_Port(&AccelPreDetectMsg); TO DO

    (void)Rte_Read_SigPrep_DynamicSigs(&AccelPreDetectMsg);

  // convert to app
    pAccelPreDetect->nValue  = (sint16)AccelPreDetectMsg.ePedalAcceleration.ucPedalAcceleration;
    pAccelPreDetect->nDelta  = 0;//AccelPreDetectMsg.Delta;
    pAccelPreDetect->eSigQty = (teRte_SigQty)AccelPreDetectMsg.eSigQty;
}

//-----------------------------------------------------------------------------
/// \brief  AvacData_ReadBrakePreDetect()
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void AvacData_ReadBrakePreDetect(tAvac_BrakePreDetect* pBrakePreDetect)
{
    //tBrakePreDetectMsg  BrakePreDetectMsg;
    //(void) Rte_Read_SigPrepRx_BrakePreDetectMsg_Port(&BrakePreDetectMsg); TO DO

    tsRte_SigPrep_DynamicSigs  BrakePreDetectMsg;
    (void)Rte_Read_SigPrep_DynamicSigs(&BrakePreDetectMsg);

  // convert to app
    pBrakePreDetect->nValue  = (sint16)BrakePreDetectMsg.eBrakePressure.ucBrakePressure;
    pBrakePreDetect->nDelta  = 0;//BrakePreDetectMsg.Delta;
    pBrakePreDetect->eSigQty = (teRte_SigQty)BrakePreDetectMsg.eSigQty;
}

//-----------------------------------------------------------------------------
/// \brief  AvacData_WriteAvacOut()
///
/// \descr
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void AvacData_WriteAvacOut(const tAvac_Out* pAvacOut)
{
  tsPositionOut  sPosOut;
  sint16         snAngle;
  sint16    snPitchAmVar;

  snAngle = pAvacOut->nAngle;
  // convert internal Avac-Data [0.1mrad] to RTE-Data [0.01 deg]
  snAngle = (snAngle >= 0) ? (sint16)((((sint32)snAngle * 180) + 157) / 314)
    : (sint16)((((sint32)snAngle * 180) - 157) / 314);

  sPosOut.State = (uint8)pAvacOut->eSigQty;
  sPosOut.Position[0].Ver   = snAngle;
  sPosOut.Position[1].Ver   = snAngle;
  sPosOut.Position[0].Hor   = 0;
  sPosOut.Position[1].Hor   = 0;
  sPosOut.Position[0].Width = 0u;
  sPosOut.Position[1].Width = 0u;

  // write data to RTE
  (void)Rte_Write_ppsAvacOut(&sPosOut);
}
