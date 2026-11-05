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
/// \file  Test_Stubs.c
///
/// \brief Stub functions for access to software modules excluded from test
///
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================
#include "Test_Stubs.h"

//=============================================================================
// Global variable stubs
//=============================================================================

tNvmPara_CodingArea           Coding_Dummy = { 0u };
tParaFct0_Cmd                 Coding_State = eParaFct0_CodingDataInvalid;

//=============================================================================
// Stub function parameter stubs
//=============================================================================

/*Read*/
tsRte_SysMonLgtFctsReq              Rte_Read_SysMon_StdLgtFcts_Req_Param1;
tsRte_SysMonAfsSignals              Rte_Read_SysMon_Afs_Signals_Param1;
tsRte_SysMonLgtTiReq                Rte_Read_SysMon_StdLgtTi_Req_Param1;
tsRte_SigPrepLgtClSblReq            Rte_Read_SigPrep_StdLgtClSbl_Req_Param1;
teRte_MountingSide                  Rte_Read_IoHwAbUser_GetMountingSide_Param1;
teRte_SysVolt_Results               Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1;
tsRteCodingParameters               Rte_Read_CodM_FctR_Para_Param1;
tsRte_LedErrStateArr                Rte_Read_CtrlLed_ActLed_sState_Param1;
tsRte_SysMon_VehNetState            Rte_Read_SysMon_VehNetState_Param1;
teRte_ReqLightState                 Rte_Read_SysMon_LowBeamCmd_Req_Param1;
tsRte_SigPrep_VehicleConfigSig      Rte_Read_SigPrep_VehicleConfigSig_Param1;
tsRte_SysMon_LifePhases             Rte_Read_SysMon_LifePhases_Param1;
tsRte_SigPrep_ElecSupState          Rte_Read_SigPrep_ElecSupState_Param1;
teRte_ReqLightState                 Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1;
boolean                             Rte_Read_DEM_OV_NotifyStatus_Param1;
boolean                             Rte_Read_DEM_UV_NotifyStatus_Param1;
boolean                             Rte_Read_AdbMxb_Gfhb_Diag_Param1;
tsRte_Ld_ActivationRoutineControl   Rte_Read_Diag_LdActivationRoutineControl_Param1;
tAdbOut                             Rte_Read_ppsAdb_Out_sVal_4_Param1;
tAdbStatus                          Rte_Read_Adb_StatusOut_Param1;
tAdbOut                             Rte_Read_ppsAdb_Out_sVal_0_Param1;

/*Write*/
teRte_GfHb_Cmd                      Rte_Write_FctR_GfHbCmd_Param1;
tsRte_TgtLedVal0Arr                 Rte_Write_FctR_TgtLed_sVal_Param1;
tsRte_AfsDblCmd                     Rte_Write_FctR_AfsDblCmd_Param1;
teRte_AfsModeSig_sVal               Rte_Write_FctR_AfsModeSig_sVal_Param1;
tsRte_LgtFctState                   Rte_Write_FctR_LgtFctState_Param1;
tsRte_LgtFctStatus                  Rte_Write_FctR_LgtFctStatus_Param1;
teRte_WarningMode                   Rte_Write_FctR_TiWarningMode_Param1;
boolean                             Rte_Write_FctR_TiFailureStatus_Param1;
tuFctR_LgtFct                       Rte_Write_FctR_LgtDistStatus_Param1;
boolean                             Rte_Write_FctR_PXALightDistr_Fbit_Param1;

tUtilDebounceControl                UtilDebounceInit_Param1;
tieDigState                         UtilDebounceInit_Param2;
TIMER                               UtilDebounceInit_Param3;
TIMER                               UtilDebounceInit_Param4;

tUtilDebounceControl                UtilDebounce_Param1;
boolean                             UtilDebounce_Param2;
uint32                              LPTMR0_GetTimeElapsed_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

/*Read*/
Std_ReturnType    Rte_Read_SysMon_StdLgtFcts_Req_RetVal;
Std_ReturnType    Rte_Read_SysMon_Afs_Signals_RetVal;
Std_ReturnType    Rte_Read_SysMon_StdLgtTi_Req_RetVal;
Std_ReturnType    Rte_Read_SigPrep_StdLgtClSbl_Req_RetVal;
Std_ReturnType    Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
Std_ReturnType    Rte_Read_CodM_FctR_Para_RetVal;
Std_ReturnType    Rte_Read_SysVolt_LedVoltRng0_sVoltRng_RetVal;
Std_ReturnType    Rte_Read_CtrlLed_ActLed_sState_RetVal;
Std_ReturnType    Rte_Read_SysMon_VehNetState_RetVal;
Std_ReturnType    Rte_Read_SysMon_LowBeamCmd_Req_RetVal;
Std_ReturnType    Rte_Read_SigPrep_VehicleConfigSig_RetVal;
Std_ReturnType    Rte_Read_SysMon_LifePhases_RetVal;
Std_ReturnType    Rte_Read_SigPrep_ElecSupState_RetVal;
Std_ReturnType    Rte_Read_SysMon_TurnIndicatorCmd_Req_RetVal;
Std_ReturnType    Rte_Read_DEM_OV_NotifyStatus_RetVal;
Std_ReturnType    Rte_Read_DEM_UV_NotifyStatus_RetVal;
Std_ReturnType    Rte_Read_AdbMxb_Gfhb_Diag_RetVal;
Std_ReturnType    Rte_Read_Diag_LdActivationRoutineControl_RetVal;
Std_ReturnType    Rte_Read_Adb_StatusOut_RetVal;
Std_ReturnType    Rte_Read_ppsAdb_Out_sVal_0_RetVal;

/*Write*/
Std_ReturnType    Rte_Write_FctR_TgtLed_sVal_RetVal;
Std_ReturnType    Rte_Write_FctR_GfHbCmd_RetVal;
Std_ReturnType    Rte_Write_FctR_AfsDblCmd_RetVal;
Std_ReturnType    Rte_Write_FctR_AfsModeSig_sVal_RetVal;
Std_ReturnType    Rte_Write_FctR_LgtFctState_RetVal;
Std_ReturnType    Rte_Write_FctR_LgtFctStatus_RetVal;
Std_ReturnType    Rte_Write_FctR_TiWarningMode_RetVal;
Std_ReturnType    Rte_Write_FctR_TiFailureStatus_RetVal;
Std_ReturnType    Rte_Write_FctR_LgtDistStatus_RetVal;
Std_ReturnType    Rte_Write_FctR_PXALightDistr_Fbit_RetVal;
Std_ReturnType    Rte_Read_ppsAdb_Out_sVal_4_RetVal;

uint32            LPTMR0_GetTimeElapsed_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

/*Read*/
uint8    Rte_Read_SysMon_StdLgtFcts_Req_HitCount;
uint8    Rte_Read_SysMon_Afs_Signals_HitCount;
uint8    Rte_Read_SysMon_StdLgtTi_Req_HitCount;
uint8    Rte_Read_SigPrep_StdLgtClSbl_Req_HitCount;
uint8    Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
uint8    Rte_Read_CodM_FctR_Para_HitCount;
uint8    Rte_Read_SysVolt_LedVoltRng0_sVoltRng_HitCount;
uint8    Rte_Read_CtrlLed_ActLed_sState_HitCount;
uint8    Rte_Read_SysMon_VehNetState_HitCount;
uint8    Rte_Read_SysMon_LowBeamCmd_Req_HitCount;
uint8    Rte_Read_SigPrep_VehicleConfigSig_HitCount;
uint8    Rte_Read_SysMon_LifePhases_HitCount;
uint8    Rte_Read_SigPrep_ElecSupState_HitCount;
uint8    Rte_Read_SysMon_TurnIndicatorCmd_Req_HitCount;
uint8    Rte_Read_DEM_OV_NotifyStatus_HitCount;
uint8    Rte_Read_DEM_UV_NotifyStatus_HitCount;
uint8    Rte_Read_AdbMxb_Gfhb_Diag_HitCount;
uint8    Rte_Read_Diag_LdActivationRoutineControl_HitCount;
uint8    Rte_Read_Adb_StatusOut_HitCount;
uint8    Rte_Read_ppsAdb_Out_sVal_0_HitCount;

/*Write*/
uint8    Rte_Write_FctR_TgtLed_sVal_HitCount;
uint8    Rte_Write_FctR_GfHbCmd_HitCount;
uint8    Rte_Write_FctR_AfsDblCmd_HitCount;
uint8    Rte_Write_FctR_AfsModeSig_sVal_HitCount;
uint8    Rte_Write_FctR_LgtFctState_HitCount;
uint8    Rte_Write_FctR_LgtFctStatus_HitCount;
uint8    Rte_Write_FctR_TiWarningMode_HitCount;
uint8    Rte_Write_FctR_TiFailureStatus_HitCount;
uint8    Rte_Write_FctR_LgtDistStatus_HitCount;
uint8    Rte_Write_FctR_PXALightDistr_Fbit_HitCount;
uint8    Rte_Read_ppsAdb_Out_sVal_4_HitCount;


uint8    UtilDebounceInit_HitCount;
uint8    UtilDebounce_HitCount;
uint8    LPTMR0_GetTimeElapsed_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_Diag_LdActivationRoutineControl
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_Diag_LdActivationRoutineControl
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Diag_LdActivationRoutineControl(tsRte_Ld_ActivationRoutineControl* ppara1)
{
  *ppara1 = Rte_Read_Diag_LdActivationRoutineControl_Param1;
  Rte_Read_Diag_LdActivationRoutineControl_HitCount++;
  return Rte_Read_Diag_LdActivationRoutineControl_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysVolt_LedVoltRng0_sVoltRng
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysVolt_LedVoltRng0_sVoltRng
///
/// \param  ppara1
///
/// \return void
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysVolt_LedVoltRng0_sVoltRng(teRte_SysVolt_Results* ppara1)
{
  *ppara1 = Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1;
  Rte_Read_SysVolt_LedVoltRng0_sVoltRng_HitCount++;
  return Rte_Read_SysVolt_LedVoltRng0_sVoltRng_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_StdLgtFcts_Req
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_StdLgtFcts_Req
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_StdLgtFcts_Req(tsRte_SysMonLgtFctsReq* ppara1)
{
  *ppara1 = Rte_Read_SysMon_StdLgtFcts_Req_Param1;
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount++;

  return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_Afs_Signals
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_Afs_Signals
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_Afs_Signals(tsRte_SysMonAfsSignals* ppara1)
{
  *ppara1 = Rte_Read_SysMon_Afs_Signals_Param1;
  Rte_Read_SysMon_Afs_Signals_HitCount++;

  return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_StdLgtTi_Req
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_StdLgtTi_Req
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_StdLgtTi_Req(tsRte_SysMonLgtTiReq* ppara1)
{
  *ppara1 = Rte_Read_SysMon_StdLgtTi_Req_Param1;
  Rte_Read_SysMon_StdLgtTi_Req_HitCount++;

  return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_StdLgtClSbl_Req
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_StdLgtClSbl_Req
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_StdLgtClSbl_Req(tsRte_SigPrepLgtClSblReq* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_StdLgtClSbl_Req_Param1;
  Rte_Read_SigPrep_StdLgtClSbl_Req_HitCount++;

  return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_AdbMxb_Gfhb_Diag
///
/// \descr  stub function to simulate the behaviour of Rte_Read_AdbMxb_Gfhb_Diag
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_AdbMxb_Gfhb_Diag(boolean* ppara1)
{
  *ppara1 = Rte_Read_AdbMxb_Gfhb_Diag_Param1;
  Rte_Read_AdbMxb_Gfhb_Diag_HitCount++;
  return Rte_Read_AdbMxb_Gfhb_Diag_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_IoHwAbUser_GetMountingSide
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_IoHwAbUser_GetMountingSide
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1)
{
  *ppara1 = Rte_Read_IoHwAbUser_GetMountingSide_Param1;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount++;

  return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CodM_FctR_Para
///
/// \descr  Stub function created to simulate the behavior of Rte_Read_CodM_FctR_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CodM_FctR_Para(tsRteCodingParameters* ppara1)
{
  Rte_Read_CodM_FctR_Para_Param1.eCodingState = Coding_State;
  Rte_Read_CodM_FctR_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;

  *ppara1 = Rte_Read_CodM_FctR_Para_Param1;
  Rte_Read_CodM_FctR_Para_HitCount++;
  return Rte_Read_CodM_FctR_Para_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_VehNetState
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_VehNetState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_VehNetState(tsRte_SysMon_VehNetState* ppara1)
{
  *ppara1 = Rte_Read_SysMon_VehNetState_Param1;
  Rte_Read_SysMon_VehNetState_HitCount++;
  return Rte_Read_SysMon_VehNetState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_LowBeamCmd_Req
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_LowBeamCmd_Req
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_LowBeamCmd_Req(teRte_ReqLightState* ppara1)
{
  *ppara1 = Rte_Read_SysMon_LowBeamCmd_Req_Param1;
  Rte_Read_SysMon_LowBeamCmd_Req_HitCount++;
  return Rte_Read_SysMon_LowBeamCmd_Req_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_VehicleConfigSig
///
/// \descr  stub function to simulate the behaviour of Rte_Read_SigPrep_VehicleConfigSig
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_VehicleConfigSig(tsRte_SigPrep_VehicleConfigSig* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_VehicleConfigSig_Param1;
  Rte_Read_SigPrep_VehicleConfigSig_HitCount++;

  return Rte_Read_SigPrep_VehicleConfigSig_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_LifePhases
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_LifePhases
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_LifePhases(tsRte_SysMon_LifePhases* ppara1)
{
  *ppara1 = Rte_Read_SysMon_LifePhases_Param1;
  Rte_Read_SysMon_LifePhases_HitCount++;
  return Rte_Read_SysMon_LifePhases_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlLed_ActLed_sState
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CtrlLed_ActLed_sState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlLed_ActLed_sState(tsRte_LedErrStateArr* ppara1)
{
  for (uint32 ulIdx = 0u; ulIdx < sizeof(tsRte_LedErrStateArr); ulIdx++)
  {
    *((uint8*)(void*)ppara1 + ulIdx) = *((uint8*)(void*)&Rte_Read_CtrlLed_ActLed_sState_Param1 + ulIdx);
  }
  Rte_Read_CtrlLed_ActLed_sState_HitCount++;

  return Rte_Read_CtrlLed_ActLed_sState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_ElecSupState
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_ElecSupState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_ElecSupState(tsRte_SigPrep_ElecSupState* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_ElecSupState_Param1;
  Rte_Read_SigPrep_ElecSupState_HitCount++;
  return Rte_Read_SigPrep_ElecSupState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_TurnIndicatorCmd_Req
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_TurnIndicatorCmd_Req
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_TurnIndicatorCmd_Req(teRte_ReqLightState* ppara1)
{
  *ppara1 = Rte_Read_SysMon_TurnIndicatorCmd_Req_Param1;
  Rte_Read_SysMon_TurnIndicatorCmd_Req_HitCount++;
  return Rte_Read_SysMon_TurnIndicatorCmd_Req_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_DEM_OV_NotifyStatus
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_DEM_OV_NotifyStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_DEM_OV_NotifyStatus(boolean* ppara1)
{
  *ppara1 = Rte_Read_DEM_OV_NotifyStatus_Param1;
  Rte_Read_DEM_OV_NotifyStatus_HitCount++;
  return Rte_Read_DEM_OV_NotifyStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_DEM_UV_NotifyStatus
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_DEM_UV_NotifyStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_DEM_UV_NotifyStatus(boolean* ppara1)
{
  *ppara1 = Rte_Read_DEM_UV_NotifyStatus_Param1;
  Rte_Read_DEM_UV_NotifyStatus_HitCount++;
  return Rte_Read_DEM_UV_NotifyStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_ppsAdb_Out_sVal_4
///
/// \descr Stub function created to simulate the behaviour of Rte_Read_ppsAdb_Out_sVal_4
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_ppsAdb_Out_sVal_4(tAdbOut* ppara1)
{
  *ppara1 = Rte_Read_ppsAdb_Out_sVal_4_Param1;
  Rte_Read_ppsAdb_Out_sVal_4_HitCount++;
  return Rte_Read_ppsAdb_Out_sVal_4_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_Adb_StatusOut
///
/// \descr Stub function created to simulate the behaviour of Rte_Read_Adb_StatusOut
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Adb_StatusOut(tAdbStatus* ppara1)
{
  *ppara1 = Rte_Read_Adb_StatusOut_Param1;
  Rte_Read_Adb_StatusOut_HitCount++;
  return Rte_Read_Adb_StatusOut_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_ppsAdb_Out_sVal_0
///
/// \descr Stub function created to simulate the behaviour of Rte_Read_ppsAdb_Out_sVal_0
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_ppsAdb_Out_sVal_0(tAdbOut* ppara1)
{
  *ppara1 = Rte_Read_ppsAdb_Out_sVal_0_Param1;
  Rte_Read_ppsAdb_Out_sVal_0_HitCount++;
  return Rte_Read_ppsAdb_Out_sVal_0_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_FctR_LgtDistStatus
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_FctR_LgtDistStatus
///
/// \param  ppara1
///
/// \return void
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_FctR_LgtDistStatus(tuFctR_LgtFct ppara1)
{
  Rte_Write_FctR_LgtDistStatus_Param1 = ppara1;
  Rte_Write_FctR_LgtDistStatus_HitCount++;
  return RTE_E_OK;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_FctR_TgtLed_sVal
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_FctR_TgtLed_sVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_FctR_TgtLed_sVal(const tsRte_TgtLedVal0Arr* ppara1)
{
  Rte_Write_FctR_TgtLed_sVal_Param1 = *ppara1;
  Rte_Write_FctR_TgtLed_sVal_HitCount++;

  return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_FctR_AfsDblCmd
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_FctR_AfsDblCmd
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_FctR_AfsDblCmd(const tsRte_AfsDblCmd* ppara1)
{
  Rte_Write_FctR_AfsDblCmd_Param1 = *ppara1;
  Rte_Write_FctR_AfsDblCmd_HitCount++;

  return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_FctR_AfsModeSig_sVal
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_FctR_AfsModeSig_sVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_FctR_AfsModeSig_sVal(const teRte_AfsModeSig_sVal* ppara1)
{
  Rte_Write_FctR_AfsModeSig_sVal_Param1 = *ppara1;
  Rte_Write_FctR_AfsModeSig_sVal_HitCount++;

  return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_FctR_GfHbCmd
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_FctR_GfHbCmd
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_FctR_GfHbCmd(const teRte_GfHb_Cmd* ppara1)
{
  Rte_Write_FctR_GfHbCmd_Param1 = *ppara1;
  Rte_Write_FctR_GfHbCmd_HitCount++;

  return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_FctR_LgtFctState
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_FctR_LgtFctState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_FctR_LgtFctState(const tsRte_LgtFctState* ppara1)
{
  Rte_Write_FctR_LgtFctState_Param1 = *ppara1;
  Rte_Write_FctR_LgtFctState_HitCount++;
  return Rte_Write_FctR_LgtFctState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_FctR_LgtFctStatus
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_FctR_LgtFctStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_FctR_LgtFctStatus(const tsRte_LgtFctStatus* ppara1)
{
  Rte_Write_FctR_LgtFctStatus_Param1 = *ppara1;
  Rte_Write_FctR_LgtFctStatus_HitCount++;
  return Rte_Write_FctR_LgtFctStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_FctR_TiWarningMode
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_FctR_TiWarningMode
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_FctR_TiWarningMode(const teRte_WarningMode* ppara1)
{
  Rte_Write_FctR_TiWarningMode_Param1 = *ppara1;
  Rte_Write_FctR_TiWarningMode_HitCount++;
  return Rte_Write_FctR_TiWarningMode_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_FctR_TiFailureStatus
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_FctR_TiFailureStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_FctR_TiFailureStatus(const boolean* ppara1)
{
  Rte_Write_FctR_TiFailureStatus_Param1 = *ppara1;
  Rte_Write_FctR_TiFailureStatus_HitCount++;
  return Rte_Write_FctR_TiFailureStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_FctR_PXALightDistr_Fbit
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_FctR_PXALightDistr_Fbit
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_FctR_PXALightDistr_Fbit(const boolean* ppara1)
{
  Rte_Write_FctR_PXALightDistr_Fbit_Param1 = *ppara1;
  Rte_Write_FctR_PXALightDistr_Fbit_HitCount++;
  return Rte_Write_FctR_PXALightDistr_Fbit_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief LPTMR0_GetTimeElapsed
///
/// \descr Stub function for LPTMR0_GetTimeElapsed
///
/// \param  ulStartValue
///
/// \return uint32
//-----------------------------------------------------------------------------
uint32 LPTMR0_GetTimeElapsed(const uint32 ulStartValue)
{
  LPTMR0_GetTimeElapsed_Param1 = ulStartValue;
  LPTMR0_GetTimeElapsed_HitCount++;

  return LPTMR0_GetTimeElapsed_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  UtilDebounceInit
///
/// \descr  Stub function created to simulate the behaviour of UtilDebounceInit
///
/// \param  pCtrl
/// \param  eStateInit
/// \param  tOnDelay
/// \param  tOffDelay
///
/// \return void
//-----------------------------------------------------------------------------
void UtilDebounceInit(tUtilDebounceControl* const pCtrl, tieDigState eStateInit, TIMER tOnDelay, TIMER tOffDelay)
{
  UtilDebounceInit_Param1 = *pCtrl;
  UtilDebounceInit_Param2 = eStateInit;
  UtilDebounceInit_Param3 = tOnDelay;
  UtilDebounceInit_Param4 = tOffDelay;
  UtilDebounceInit_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  UtilDebounce
///
/// \descr  Stub function created to simulate the behaviour of UtilDebounce
///
/// \param  pCtrl
/// \param  boVal
///
/// \return void
//-----------------------------------------------------------------------------
void UtilDebounce(tUtilDebounceControl* const pCtrl, boolean boVal)
{
  UtilDebounce_Param1 = *pCtrl;
  UtilDebounce_Param2 = boVal;
  UtilDebounce_HitCount++;
}

