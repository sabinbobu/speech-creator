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
// Stub function parameter stubs
//=============================================================================
tsRte_TgtLedSig0_ASIL                   Rte_Write_SysMon_TgtLedSig_sVal_Param1;
tsRte_SysMonLgtTiReq                    Rte_Write_SysMon_StdLgtTi_Req_Param1;
tsRte_SysMonLgtFctsReq                  Rte_Write_SysMon_StdLgtFcts_Req_Param1;
tsRte_SysMonAfsSignals                  Rte_Write_SysMon_Afs_Signals_Param1;
tsRte_SysMon_LifePhases                 Rte_Write_SysMon_LifePhases_Param1;
tsRte_SysMon_VehNetState                Rte_Write_SysMon_VehNetState_Param1;
tsRte_SysMon_VehicleSpeed               Rte_Write_SysMon_VehicleSpeed_Param1;
teRte_ReqLightState                     Rte_Write_SysMon_LowBeamCmd_Req_Param1;
teRte_ReqLightState                     Rte_Write_SysMon_TurnIndicatorCmd_Req_Param1;
tsRte_LedStates                         Rte_Write_CddLed_LedState_Param1;
tsRte_SysMon_LedStates                  Rte_Write_SysMon_LedState_Param1;
TE_Bool                                 Rte_Write_SysMon_SetDiagMux_Param1;
tSysMon_SendFrame457                    Rte_Write_SysMon_SendFrame457_Param1;
tSysMon_SendFrame477                    Rte_Write_SysMon_SendFrame477_Param1;
tsRte_TgtLedSig0Arr                     Rte_Read_Cpm_TgtLedSig_sVal_Param1;
tsRte_SysMonLgtTiReq                    Rte_Read_SysMon_StdLgtTi_Req_Param1;
tsRte_SysMonLgtFctsReq                  Rte_Read_SysMon_StdLgtFcts_Req_Param1;
teRte_MountingSide                      Rte_Read_IoHwAbUser_GetMountingSide_Param1;
tsRte_SysMonAfsSignals                  Rte_Read_SysMon_Afs_Signals_Param1;
tsRte_SysMon_LifePhases                 Rte_Read_SysMon_LifePhases_Param1;
tsRte_SysMon_VehNetState                Rte_Read_SysMon_VehNetState_Param1;
tsRte_SysMon_VehicleSpeed               Rte_Read_SysMon_VehicleSpeed_Param1;
tsRte_Hs6_Diag_Drvled_L_457             Rte_Read_DrvLedDiag_Param1;
tsRte_Hs6_Diag_Drvled_R_477             Rte_Read_DrvLedDiagR_Param1;
tsRte_Hs6_Diag_Drvled_BendingBeamFault  Rte_Read_Dbl_SysMonTx_FullStatus_Param1;
boolean                                 Rte_Read_CodM_SysMon_CRC32_Param1;
tsRteCodingParameters                   Rte_Read_CodM_SysMon_Para_Param1;
teRte_ReqLightState                     Rte_Read_SysMon_LowBeamCmd_Req_Param1;
tsRte_LedStates                         Rte_Read_CddLed_LedState_Param1;
boolean                                 Rte_Read_AdbMxb_Gfhb_Diag_Param1;
tsRte_LgtFctState                       Rte_Read_FctR_LgtFctState_Param1;
tsRte_SigPrep_VehicleConfigSig          Rte_Read_SigPrep_VehicleConfigSig_Param1;
uint32                                  Rte_Read_MPU_ErrorCounter_Param1;
tsRte_TgtLedSig0_FaultStatus_ASIL       Rte_Read_CddLed_TgtLed_FaultStatus_ASIL_Param1;
boolean                                 Rte_Read_FctR_TiFailureStatus_Param1;
tsRte_SigPrep_ElecSupState              Rte_Read_SigPrep_ElecSupState_Param1;
tHS6_COMMANDES_VSM_036                  Rte_Read_SigPrep_HS6_COMMANDES_VSM_036_Received_Param1;
tHS6_DAT_BSI_432                        Rte_Read_SigPrep_HS6_DAT_BSI_432_Received_Param1;
tHS6_DAT_VSM_2AE                        Rte_Read_SigPrep_HS6_DAT_VSM_2AE_Received_Param1;
tHS6_DAT_VSM_34E                        Rte_Read_SigPrep_HS6_DAT_VSM_34E_Received_Param1;
tHS6_DYN_ABR_38D                        Rte_Read_SigPrep_HS6_DYN_ABR_38D_Received_Param1;
NM_ModeType                             Rte_Read_SigPrep_NMMode_Param1;
boolean                                 Rte_Read_ElecInt_EnableCallbacks_Param1;
boolean                                 Rte_Read_ElecInt_ActivateTxBufer_Param1;
tsRte_BoostState                        Rte_Read_CddBoost_BoostState_Param1;
teRte_SysVolt_Results                   Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1;
tsRte_LedChFbit                         Rte_Read_CtrlLed_LedChFbit_Param1;
uint8                                   EcuM_McuPrivilegeSwitch_Param1;
LPTMR_ConfigType                        LPTMR_INIT_Param1_Val;
LPTMR_ConfigType*                       LPTMR_INIT_Param1 = &LPTMR_INIT_Param1_Val;
Tu8_Int                                 DAPI_BSIAckState_Param1;
TE_Bool                                 Rte_Write_SysMon_SetDiagMux_Param1;
DAPI_TE_ConfigMode                      DAPI_SetConfigMode_Param1;
DAPI_TE_MainStatus                      DAPI_SetMainStatus_Param1;
Tu32_Int                                DAPI_SyncModule_Param1;
TE_Bool                                 DAPI_RemoveAllDE_Param1;
LGM_MessageIdentifier                   LGM_SendMessage_Param1;
UINT8                                   LGM_SendMessage_Param2;
uint32                                  LPTMR0_GetTimeElapsed_Param1;
uint16                                  Dem_SetEventStatus_Param1;
uint8                                   Dem_SetEventStatus_Param2;
uint8*                                  Crc_CalculateCRC32P4_Param1;
uint32                                  Crc_CalculateCRC32P4_Param2;
uint32                                  Crc_CalculateCRC32P4_Param3;
uint8*                                  Crc_CalculateCRC8H2F_Param1;
uint32                                  Crc_CalculateCRC8H2F_Param2;
uint8                                   Crc_CalculateCRC8H2F_Param3;
NM_ModeType                             NM_GetMode_Param1;
Tu8_Int                                 EEPL_GetRawState_Param1;
EECO_TEP_ProfileOneChunkStatusPtr       EEPL_GetRawState_Param2;


//=============================================================================
// Stub function returned value stubs
//=============================================================================
Std_ReturnType    Rte_Write_SysMon_TgtLedSig_sVal_RetVal;
Std_ReturnType    Rte_Write_SysMon_StdLgtTi_Req_RetVal;
Std_ReturnType    Rte_Write_SysMon_StdLgtFcts_Req_RetVal;
Std_ReturnType    Rte_Write_SysMon_Afs_Signals_RetVal;
Std_ReturnType    Rte_Write_SysMon_LifePhases_RetVal;
Std_ReturnType    Rte_Write_SysMon_VehNetState_RetVal;
Std_ReturnType    Rte_Write_SysMon_VehicleSpeed_RetVal;
Std_ReturnType    Rte_Write_SysMon_LowBeamCmd_Req_RetVal;
Std_ReturnType    Rte_Write_SysMon_TurnIndicatorCmd_Req_RetVal;
Std_ReturnType    Rte_Write_SysMon_LedState_RetVal;
Std_ReturnType    Rte_Write_DEM_SetEvent_MasterPort_RetVal;
Std_ReturnType    Rte_Write_SysMon_SetDiagMux_RetVal;
Std_ReturnType    Rte_Write_SysMon_SendFrame457_RetVal;
Std_ReturnType    Rte_Write_SysMon_SendFrame477_RetVal;
Std_ReturnType    Rte_Read_Cpm_TgtLedSig_sVal_RetVal;
Std_ReturnType    Rte_Read_SysMon_StdLgtTi_Req_RetVal;
Std_ReturnType    Rte_Read_SysMon_StdLgtFcts_Req_RetVal;
Std_ReturnType    Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
Std_ReturnType    Rte_Read_SysMon_Afs_Signals_RetVal;
Std_ReturnType    Rte_Read_SysMon_LifePhases_RetVal;
Std_ReturnType    Rte_Read_SysMon_VehNetState_RetVal;
Std_ReturnType    Rte_Read_SysMon_VehicleSpeed_RetVal;
Std_ReturnType    Rte_Read_DrvLedDiag_RetVal;
Std_ReturnType    Rte_Read_DrvLedDiagR_RetVal;
Std_ReturnType    Rte_Read_Dbl_SysMonTx_FullStatus_RetVal;
Std_ReturnType    Rte_Read_CodM_SysMon_CRC32_RetVal;
Std_ReturnType    Rte_Read_CodM_SysMon_Para_RetVal;
Std_ReturnType    Rte_Read_SysMon_LowBeamCmd_Req_RetVal;
Std_ReturnType    Rte_Read_CddLed_LedState_RetVal;
Std_ReturnType    Rte_Read_AdbMxb_Gfhb_Diag_RetVal;
Std_ReturnType    Rte_Read_FctR_LgtFctState_RetVal;
Std_ReturnType    Rte_Read_DEM_SetEvent_MasterPort_RetVal;
Std_ReturnType    Rte_Read_SigPrep_VehicleConfigSig_RetVal;
Std_ReturnType    Rte_Read_MPU_ErrorCounter_RetVal;
Std_ReturnType    Rte_Read_CddLed_TgtLed_FaultStatus_ASIL_RetVal;
Std_ReturnType    Rte_Read_FctR_TiFailureStatus_RetVal;
Std_ReturnType    Rte_Read_SigPrep_ElecSupState_RetVal;
Std_ReturnType    Rte_Read_SigPrep_HS6_COMMANDES_VSM_036_Received_RetVal;
Std_ReturnType    Rte_Read_SigPrep_HS6_DAT_BSI_432_Received_RetVal;
Std_ReturnType    Rte_Read_SigPrep_HS6_DAT_VSM_2AE_Received_RetVal;
Std_ReturnType    Rte_Read_SigPrep_HS6_DAT_VSM_34E_Received_RetVal;
Std_ReturnType    Rte_Read_SigPrep_HS6_DYN_ABR_38D_Received_RetVal;
Std_ReturnType    Rte_Read_SigPrep_NMMode_RetVal;
Std_ReturnType    Rte_Read_ElecInt_EnableCallbacks_RetVal;
Std_ReturnType    Rte_Read_ElecInt_ActivateTxBufer_RetVal;
Std_ReturnType    Rte_Read_CddBoost_BoostState_RetVal;
Std_ReturnType    Rte_Read_SysVolt_LedVoltRng0_sVoltRng_RetVal;
Std_ReturnType    Rte_Read_CtrlLed_LedChFbit_RetVal;
IL_StatusType     LGM_SendMessage_RetVal;
uint32            LPTMR0_GetTimeElapsed_RetVal;
TE_ReturnType     EEPR_MainFunction_RetVal;
uint32            Crc_CalculateCRC32P4_RetVal;
uint8             Crc_CalculateCRC8H2F_RetVal;
boolean           LPTMR_Check_Config_RetVal;
NM_ErrorCodeType  NM_GetMode_RetVal;
boolean           CddEft_DataValid_RetVal;
TE_ReturnType     EEPL_GetRawState_RetVal;


//=============================================================================
// Stub function hit count variables
//=============================================================================
uint8   Rte_Write_SysMon_TgtLedSig_sVal_HitCount;
uint8   Rte_Write_SysMon_StdLgtTi_Req_HitCount;
uint8   Rte_Write_SysMon_StdLgtFcts_Req_HitCount;
uint8   Rte_Write_SysMon_Afs_Signals_HitCount;
uint8   Rte_Write_SysMon_LifePhases_HitCount;
uint8   Rte_Write_SysMon_VehNetState_HitCount;
uint8   Rte_Write_SysMon_VehicleSpeed_HitCount;
uint8   Rte_Write_SysMon_LowBeamCmd_Req_HitCount;
uint8   Rte_Write_SysMon_TurnIndicatorCmd_Req_HitCount;
uint8   Rte_Write_SysMon_LedState_HitCount;
uint8   Rte_Write_DEM_SetEvent_MasterPort_HitCount;
uint8   Rte_Write_SysMon_SetDiagMux_HitCount;
uint8   Rte_Write_SysMon_SendFrame457_HitCount;
uint8   Rte_Write_SysMon_SendFrame477_HitCount;
uint8   Rte_Read_Cpm_TgtLedSig_sVal_HitCount;
uint8   Rte_Read_SysMon_StdLgtTi_Req_HitCount;
uint8   Rte_Read_SysMon_StdLgtFcts_Req_HitCount;
uint8   Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
uint8   Rte_Read_SysMon_Afs_Signals_HitCount;
uint8   Rte_Read_SysMon_LifePhases_HitCount;
uint8   Rte_Read_SysMon_VehNetState_HitCount;
uint8   Rte_Read_SysMon_VehicleSpeed_HitCount;
uint8   Rte_Read_DrvLedDiag_HitCount;
uint8   Rte_Read_DrvLedDiagR_HitCount;
uint8   Rte_Read_Dbl_SysMonTx_FullStatus_HitCount;
uint8   Rte_Read_CodM_SysMon_CRC32_HitCount;
uint8   Rte_Read_CodM_SysMon_Para_HitCount;
uint8   Rte_Read_SysMon_LowBeamCmd_Req_HitCount;
uint8   Rte_Read_CddLed_LedState_HitCount;
uint8   Rte_Read_AdbMxb_Gfhb_Diag_HitCount;
uint8   Rte_Read_FctR_LgtFctState_HitCount;
uint8   Rte_Read_DEM_SetEvent_MasterPort_HitCount;
uint8   Rte_Read_SigPrep_VehicleConfigSig_HitCount;
uint8   Rte_Read_MPU_ErrorCounter_HitCount;
uint8   Rte_Read_CddLed_TgtLed_FaultStatus_ASIL_HitCount;
uint8   Rte_Read_FctR_TiFailureStatus_HitCount;
uint8   Rte_Read_SigPrep_ElecSupState_HitCount;
uint8   Rte_Read_SigPrep_HS6_COMMANDES_VSM_036_Received_HitCount;
uint8   Rte_Read_SigPrep_HS6_DAT_BSI_432_Received_HitCount;
uint8   Rte_Read_SigPrep_HS6_DAT_VSM_2AE_Received_HitCount;
uint8   Rte_Read_SigPrep_HS6_DAT_VSM_34E_Received_HitCount;
uint8   Rte_Read_SigPrep_HS6_DYN_ABR_38D_Received_HitCount;
uint8   Rte_Read_SigPrep_NMMode_HitCount;
uint8   Rte_Read_ElecInt_EnableCallbacks_HitCount;
uint8   Rte_Read_ElecInt_ActivateTxBufer_HitCount;
uint8   Rte_Read_CddBoost_BoostState_HitCount;
uint8   Rte_Read_SysVolt_LedVoltRng0_sVoltRng_HitCount;
uint8   Rte_Read_CtrlLed_LedChFbit_HitCount;
uint8   EEPR_Init_HitCount;
uint8   EEPR_MainFunction_HitCount;
uint8   EEPL_GetRawState_HitCount;
uint8   Dem_SetEventStatus_HitCount;
uint8   DAPI_BSIAckState_HitCount;
uint8   Rte_Write_SysMon_SetDiagMux_HitCount;
uint8   DAPI_SetConfigMode_HitCount;
uint8   DAPI_SetMainStatus_HitCount;
uint8   DAPI_SyncModule_HitCount;
uint32  DAPI_RemoveAllDE_HitCount;
uint8   LGM_SendMessage_HitCount;
uint8   LPTMR0_GetTimeElapsed_HitCount;
uint8   Crc_CalculateCRC32P4_HitCount;
uint8   LPTMR_Check_Config_HitCount;
uint8   EcuM_McuPrivilegeSwitch_HitCount;
uint8   LPTMR_INIT_HitCount;
uint8   Crc_CalculateCRC8H2F_HitCount;
uint8   NM_GetMode_HitCount;
uint8   CddEft_DataValid_HitCount;
uint8   LGM_HS6_COMMANDES_VSM_036_Received_HitCount;
uint8   LGM_HS6_COMMANDES_VSM_036_NotReceived_HitCount;
uint8   LGM_HS6_DAT_BSI_432_Received_HitCount;
uint8   LGM_HS6_DAT_BSI_432_NotReceived_HitCount;
uint8   LGM_HS6_DYN_ABR_38D_Received_HitCount;
uint8   LGM_HS6_DYN_ABR_38D_NotReceived_HitCount;
uint8   LGM_HS6_DIAG_DRVLED_Sent_HitCount;
uint8   LGM_HS6_DIAG_DRVLED_NotSent_HitCount;
uint8   LGM_HS6_DAT_VSM_2AE_Received_HitCount;
uint8   LGM_HS6_DAT_VSM_2AE_NotReceived_HitCount;
uint8   LGM_HS6_DAT_VSM_34E_Received_HitCount;
uint8   LGM_HS6_DAT_VSM_34E_NotReceived_HitCount;


//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  EEPL_GetRawState
///
/// \descr  Stub function created to simulate the behaviour of EEPL_GetRawState
///
/// \param - PIu8_ChunkId
///        - POE_ChunkState
///
/// \return  TE_ReturnType
//-----------------------------------------------------------------------------
TE_ReturnType EEPL_GetRawState(Tu8_Int const PIu8_ChunkId, EECO_TEP_ProfileOneChunkStatusPtr const POE_ChunkState)
{
  EEPL_GetRawState_Param1 = PIu8_ChunkId;
  EEPL_GetRawState_Param2 = POE_ChunkState;
  EEPL_GetRawState_HitCount++;

  return EEPL_GetRawState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  EEPR_Init
///
/// \descr  Stub function created to simulate the behaviour of EEPR_Init
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void EEPR_Init(void)
{
  EEPR_Init_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  EEPR_MainFunction
///
/// \descr  Stub function created to simulate the behaviour of EEPR_MainFunction
///
/// \param  void
///
/// \return TE_ReturnType
//-----------------------------------------------------------------------------
TE_ReturnType EEPR_MainFunction(void)
{
  EEPR_MainFunction_HitCount++;

  return EEPR_MainFunction_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  CddEft_DataValid
///
/// \descr  Stub function created to simulate the behaviour of CddEft_DataValid
///
/// \param  void
///
/// \return TE_ReturnType
//-----------------------------------------------------------------------------
boolean CddEft_DataValid(void)
{
  CddEft_DataValid_HitCount++;

  return CddEft_DataValid_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CodM_SysMon_CRC32
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CodM_SysMon_CRC32
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CodM_SysMon_Para(tsRteCodingParameters* ppara1)
{
  *ppara1 = Rte_Read_CodM_SysMon_Para_Param1;
  Rte_Read_CodM_SysMon_Para_HitCount++;

  return Rte_Read_CodM_SysMon_Para_RetVal;
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
/// \brief  Rte_Read_CodM_SysMon_CRC32
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CodM_SysMon_CRC32
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CodM_SysMon_CRC32(boolean* ppara1)
{
  *ppara1 = Rte_Read_CodM_SysMon_CRC32_Param1;
  Rte_Read_CodM_SysMon_CRC32_HitCount++;

  return Rte_Read_CodM_SysMon_CRC32_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_Dbl_SysMonTx_FullStatus
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_Dbl_SysMonTx_FullStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Dbl_SysMonTx_FullStatus(tsRte_Hs6_Diag_Drvled_BendingBeamFault* ppara1)
{
  *ppara1 = Rte_Read_Dbl_SysMonTx_FullStatus_Param1;
  Rte_Read_Dbl_SysMonTx_FullStatus_HitCount++;

  return Rte_Read_Dbl_SysMonTx_FullStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SysMon_TurnIndicatorCmd_Req
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SysMon_TurnIndicatorCmd_Req
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SysMon_TurnIndicatorCmd_Req(const teRte_ReqLightState* ppara1)
{
  Rte_Write_SysMon_TurnIndicatorCmd_Req_Param1 = *ppara1;
  Rte_Write_SysMon_TurnIndicatorCmd_Req_HitCount++;

  return Rte_Write_SysMon_TurnIndicatorCmd_Req_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SysMon_LowBeamCmd_Req
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SysMon_LowBeamCmd_Req
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SysMon_LowBeamCmd_Req(const teRte_ReqLightState* ppara1)
{
  Rte_Write_SysMon_LowBeamCmd_Req_Param1 = *ppara1;
  Rte_Write_SysMon_LowBeamCmd_Req_HitCount++;

  return Rte_Write_SysMon_LowBeamCmd_Req_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_DrvLedDiag
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_DrvLedDiag
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_DrvLedDiag(tsRte_Hs6_Diag_Drvled_L_457* ppara1)
{
  *ppara1 = Rte_Read_DrvLedDiag_Param1;
  Rte_Read_DrvLedDiag_HitCount++;

  return Rte_Read_DrvLedDiag_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_DrvLedDiagR
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_DrvLedDiagR
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_DrvLedDiagR(tsRte_Hs6_Diag_Drvled_R_477* ppara1)
{
  *ppara1 = Rte_Read_DrvLedDiagR_Param1;
  Rte_Read_DrvLedDiagR_HitCount++;

  return Rte_Read_DrvLedDiagR_RetVal;
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
  LPTMR0_GetTimeElapsed_HitCount++;
  LPTMR0_GetTimeElapsed_Param1 = ulStartValue;

  return (LPTMR0_GetTimeElapsed_RetVal);
}

//-----------------------------------------------------------------------------
/// \brief  LGM_SendMessage
///
/// \descr  Stub function created to simulate the behaviour of LGM_SendMessage
///
/// \param  ID
/// \param  dataRef
///
/// \return void
//-----------------------------------------------------------------------------
IL_StatusType LGM_SendMessage(LGM_MessageIdentifier ID, const UINT8* const dataRef)
{
  LGM_SendMessage_Param1 = ID;
  LGM_SendMessage_Param2 = *dataRef;
  LGM_SendMessage_HitCount++;

  return LGM_SendMessage_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_VehicleSpeed
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_VehicleSpeed
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_VehicleSpeed(tsRte_SysMon_VehicleSpeed* ppara1)
{
  *ppara1 = Rte_Read_SysMon_VehicleSpeed_Param1;
  Rte_Read_SysMon_VehicleSpeed_HitCount++;

  return Rte_Read_SysMon_VehicleSpeed_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SysMon_VehicleSpeed
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SysMon_VehicleSpeed
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SysMon_VehicleSpeed(const tsRte_SysMon_VehicleSpeed* ppara1)
{
  Rte_Write_SysMon_VehicleSpeed_Param1 = *ppara1;
  Rte_Write_SysMon_VehicleSpeed_HitCount++;

  return Rte_Write_SysMon_VehicleSpeed_RetVal;
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
/// \brief  Rte_Write_SysMon_VehNetState
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SysMon_VehNetState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SysMon_VehNetState(const tsRte_SysMon_VehNetState* ppara1)
{
  Rte_Write_SysMon_VehNetState_Param1 = *ppara1;
  Rte_Write_SysMon_VehNetState_HitCount++;

  return Rte_Write_SysMon_VehNetState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  DAPI_BSIAckState
///
/// \descr  Stub function created to simulate the behaviour of DAPI_BSIAckState
///
/// \param  PIu8_AckCode
///
/// \return void
//-----------------------------------------------------------------------------
void DAPI_BSIAckState(const Tu8_Int PIu8_AckCode)
{
  DAPI_BSIAckState_Param1 = PIu8_AckCode;
  DAPI_BSIAckState_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  DAPI_SetDiagMux
///
/// \descr  Stub function created to simulate the behaviour of DAPI_SetDiagMux
///
/// \param  PIE_DiagMuxOn
///
/// \return void
//-----------------------------------------------------------------------------
void DAPI_SetDiagMux(const TE_Bool PIE_DiagMuxOn)
{
  Rte_Write_SysMon_SetDiagMux_Param1 = PIE_DiagMuxOn;
  Rte_Write_SysMon_SetDiagMux_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  DAPI_SetConfigMode
///
/// \descr  Stub function created to simulate the behaviour of DAPI_SetConfigMode
///
/// \param  PIE_ConfigMode
///
/// \return void
//-----------------------------------------------------------------------------
void DAPI_SetConfigMode(DAPI_TE_ConfigMode PIE_ConfigMode)
{
  DAPI_SetConfigMode_Param1 = PIE_ConfigMode;
  DAPI_SetConfigMode_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  DAPI_SetMainStatus
///
/// \descr  Stub function created to simulate the behaviour of DAPI_SetMainStatus
///
/// \param  PIE_value
///
/// \return void
//-----------------------------------------------------------------------------
void DAPI_SetMainStatus(const DAPI_TE_MainStatus PIE_value)
{
  DAPI_SetMainStatus_Param1 = PIE_value;
  DAPI_SetMainStatus_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  DAPI_SyncModule
///
/// \descr  Stub function created to simulate the behaviour of DAPI_SyncModule
///
/// \param  PIu32_DateVehicle
///
/// \return void
//-----------------------------------------------------------------------------
void DAPI_SyncModule(const Tu32_Int PIu32_DateVehicle)
{
  DAPI_SyncModule_Param1 = PIu32_DateVehicle;
  DAPI_SyncModule_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SysMon_Afs_Signals
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SysMon_Afs_Signals
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SysMon_Afs_Signals(const tsRte_SysMonAfsSignals* ppara1)
{
  Rte_Write_SysMon_Afs_Signals_Param1 = *ppara1;
  Rte_Write_SysMon_Afs_Signals_HitCount++;

  return Rte_Write_SysMon_Afs_Signals_RetVal;
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

  return Rte_Read_SysMon_Afs_Signals_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SysMon_LifePhases
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SysMon_LifePhases
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SysMon_LifePhases(tsRte_SysMon_LifePhases* ppara1)
{
  Rte_Write_SysMon_LifePhases_Param1 = *ppara1;
  Rte_Write_SysMon_LifePhases_HitCount++;

  return Rte_Write_SysMon_LifePhases_RetVal;
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
/// \brief  Rte_Write_SysMon_TgtLedSig_sVal
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SysMon_TgtLedSig_sVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SysMon_TgtLedSig_sVal(const tsRte_TgtLedSig0_ASIL* ppara1)
{
  Rte_Write_SysMon_TgtLedSig_sVal_Param1 = *ppara1;
  Rte_Write_SysMon_TgtLedSig_sVal_HitCount++;

  return Rte_Write_SysMon_TgtLedSig_sVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SysMon_StdLgtTi_Req
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SysMon_StdLgtTi_Req
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SysMon_StdLgtTi_Req(const tsRte_SysMonLgtTiReq* ppara1)
{
  Rte_Write_SysMon_StdLgtTi_Req_Param1 = *ppara1;
  Rte_Write_SysMon_StdLgtTi_Req_HitCount++;

  return Rte_Write_SysMon_StdLgtTi_Req_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SysMon_StdLgtFcts_Req
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SysMon_StdLgtFcts_Req
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SysMon_StdLgtFcts_Req(const tsRte_SysMonLgtFctsReq* ppara1)
{
  Rte_Write_SysMon_StdLgtFcts_Req_Param1 = *ppara1;
  Rte_Write_SysMon_StdLgtFcts_Req_HitCount++;

  return Rte_Write_SysMon_StdLgtFcts_Req_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_Cpm_TgtLedSig_sVal
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_Cpm_TgtLedSig_sVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Cpm_TgtLedSig_sVal(tsRte_TgtLedSig0Arr* ppara1)
{
  for (uint32 ulIdx = 0u; ulIdx < sizeof(tsRte_TgtLedSig0Arr); ulIdx++)
  {
    *((uint8*)(void*)ppara1 + ulIdx) = *((uint8*)(void*)&Rte_Read_Cpm_TgtLedSig_sVal_Param1 + ulIdx);
  }
  Rte_Read_Cpm_TgtLedSig_sVal_HitCount++;

  return Rte_Read_Cpm_TgtLedSig_sVal_RetVal;
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

  return Rte_Read_SysMon_StdLgtTi_Req_RetVal;
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

  return Rte_Read_SysMon_StdLgtFcts_Req_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CddLed_LedState
///
/// \descr  stub function to simulate the behaviour of Rte_Read_CddLed_LedState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CddLed_LedState(tsRte_LedStates* ppara1)
{
  *ppara1 = Rte_Read_CddLed_LedState_Param1;
  Rte_Read_CddLed_LedState_HitCount++;

  return Rte_Read_CddLed_LedState_RetVal;
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
/// \brief  Rte_Read_FctR_LgtFctState
///
/// \descr  stub function to simulate the behaviour of Rte_Read_FctR_LgtFctState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_FctR_LgtFctState(tsRte_LgtFctState* ppara1)
{
  *ppara1 = Rte_Read_FctR_LgtFctState_Param1;
  Rte_Read_FctR_LgtFctState_HitCount++;

  return Rte_Read_FctR_LgtFctState_RetVal;
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
/// \brief  Rte_Read_MPU_ErrorCounter
///
/// \descr  stub function to simulate the behaviour of Rte_Read_MPU_ErrorCounter
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_MPU_ErrorCounter(uint32* ppara1)
{
  *ppara1 = Rte_Read_MPU_ErrorCounter_Param1;
  Rte_Read_MPU_ErrorCounter_HitCount++;

  return Rte_Read_MPU_ErrorCounter_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_FctR_TiFailureStatus
///
/// \descr  stub function to simulate the behaviour of Rte_Read_FctR_TiFailureStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_FctR_TiFailureStatus(boolean* ppara1)
{
  *ppara1 = Rte_Read_FctR_TiFailureStatus_Param1;
  Rte_Read_FctR_TiFailureStatus_HitCount++;

  return Rte_Read_FctR_TiFailureStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_ElecSupState
///
/// \descr  stub function to simulate the behaviour of Rte_Read_SigPrep_ElecSupState
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
/// \brief  Rte_Read_MPU_ErrorCounter
///
/// \descr  stub function to simulate the behaviour of Rte_Read_MPU_ErrorCounter
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CddLed_TgtLed_FaultStatus_ASIL(tsRte_TgtLedSig0_FaultStatus_ASIL* ppara1)
{
  *ppara1 = Rte_Read_CddLed_TgtLed_FaultStatus_ASIL_Param1;
  Rte_Read_CddLed_TgtLed_FaultStatus_ASIL_HitCount++;

  return Rte_Read_CddLed_TgtLed_FaultStatus_ASIL_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SysMon_LedState
///
/// \descr  stub function to simulate the behaviour of Rte_Write_SysMon_LedState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SysMon_LedState(const tsRte_SysMon_LedStates* ppara1)
{
  Rte_Write_SysMon_LedState_Param1 = *ppara1;
  Rte_Write_SysMon_LedState_HitCount++;

  return Rte_Write_SysMon_LedState_RetVal;
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

  return Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Dem_SetEventStatus
///
/// \descr  Stub function created to simulate the behaviour of E2E checks on the
///
/// \param  unAlecId        : ID of the DTC to be set
/// \param  ucTestStatus    : evaluated status of the DTC
///
/// \return void
//-----------------------------------------------------------------------------
void Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus)
{
  Dem_SetEventStatus_Param1 = unAlecId;
  Dem_SetEventStatus_Param2 = ucTestStatus;
  Dem_SetEventStatus_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Crc_CalculateCRC32P4
///
/// \descr  Stub function created to simulate the behaviour of Crc_CalculateCRC32P4
///
/// \param  DataPtr
/// \param  Length
/// \param  StartValue32
///
/// \return Crc_CalculateCRC32P4_RetVal
//-----------------------------------------------------------------------------
uint32 Crc_CalculateCRC32P4(CONST_AL uint8 *DataPtr, CONST_AL uint32 Length, CONST_AL uint32 StartValue32)
{
  Crc_CalculateCRC32P4_Param1 = DataPtr;
  Crc_CalculateCRC32P4_Param2 = Length;
  Crc_CalculateCRC32P4_Param3 = StartValue32;
  Crc_CalculateCRC32P4_HitCount++;

  return Crc_CalculateCRC32P4_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief LPTMR_Check_Config
///
/// \descr Stub function created to simulate the behaviour of Crc_CalculateCRC32P4
///
/// \param  -
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean LPTMR_Check_Config(void)
{
  LPTMR_Check_Config_HitCount++;

  return LPTMR_Check_Config_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief EcuM_McuPrivilegeSwitch
///
/// \descr Stub function created to simulate the behaviour of EcuM_McuPrivilegeSwitch
///
/// \param  ppara1
///
/// \return void
//-----------------------------------------------------------------------------
void EcuM_McuPrivilegeSwitch(uint8 ppara1)
{
  EcuM_McuPrivilegeSwitch_Param1 = ppara1;
  EcuM_McuPrivilegeSwitch_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief LPTMR_INIT
///
/// \descr Stub function created to simulate the behaviour of LPTMR_INIT
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void LPTMR_INIT(const LPTMR_ConfigType* pparam1)
{
  *LPTMR_INIT_Param1 = *pparam1;
  LPTMR_INIT_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Crc_CalculateCRC8H2F
///
/// \descr  Stub function created to simulate the behaviour of Crc_CalculateCRC8H2F
///
/// \param  pucCrc_DataPtr
/// \param  ulCrc_Length
/// \param  ulCrc_StartValue32
///
/// \return Crc_CalculateCRC8H2F_RetVal
//-----------------------------------------------------------------------------
uint8 Crc_CalculateCRC8H2F(CONST_AL uint8 *DataPtr, CONST_AL uint32 Length, CONST_AL uint8  StartValue8)
{
  Crc_CalculateCRC8H2F_Param1 = DataPtr;
  Crc_CalculateCRC8H2F_Param2 = Length;
  Crc_CalculateCRC8H2F_Param3 = StartValue8;
  Crc_CalculateCRC8H2F_HitCount++;

  return Crc_CalculateCRC8H2F_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  NM_GetMode
///
/// \descr  Stub function created to simulate the behaviour of NM_GetMode
///
/// \param  p_NMMode
///
/// \return NM_ErrorCodeType
//-----------------------------------------------------------------------------
NM_ErrorCodeType NM_GetMode(NM_ModeType * p_NMMode)
{
  *p_NMMode = NM_GetMode_Param1;
  NM_GetMode_HitCount++;

  return NM_GetMode_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_COMMANDES_VSM_036_Received
///
/// \descr  Stub function to simulate the behaviour of LGM_HS6_COMMANDES_VSM_036_Received
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_COMMANDES_VSM_036_Received(void)
{
  LGM_HS6_COMMANDES_VSM_036_Received_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_COMMANDES_VSM_036_NotReceived
///
/// \descr  Stub function to simulate the behaviour of LGM_HS6_COMMANDES_VSM_036_NotReceived
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_COMMANDES_VSM_036_NotReceived(void)
{
  LGM_HS6_COMMANDES_VSM_036_NotReceived_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_BSI_432_Received
///
/// \descr  Stub function to simulate the behaviour of LGM_HS6_DAT_BSI_432_Received
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_BSI_432_Received(void)
{
  LGM_HS6_DAT_BSI_432_Received_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_ABR_38D_Received
///
/// \descr  Stub function to simulate the behaviour of LGM_HS6_DYN_ABR_38D_Received
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_ABR_38D_Received(void)
{
  LGM_HS6_DYN_ABR_38D_Received_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DYN_ABR_38D_NotReceived
///
/// \descr  Stub function to simulate the behaviour of LGM_HS6_DYN_ABR_38D_NotReceived
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DYN_ABR_38D_NotReceived(void)
{
  LGM_HS6_DYN_ABR_38D_NotReceived_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DIAG_DRVLED_Sent
///
/// \descr  Stub function to simulate the behaviour of LGM_HS6_DIAG_DRVLED_Sent
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DIAG_DRVLED_Sent(void)
{
  LGM_HS6_DIAG_DRVLED_Sent_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DIAG_DRVLED_NotSent
///
/// \descr  Stub function to simulate the behaviour of LGM_HS6_DIAG_DRVLED_NotSent
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DIAG_DRVLED_NotSent(void)
{
  LGM_HS6_DIAG_DRVLED_NotSent_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_VSM_2AE_Received
///
/// \descr  Stub function to simulate the behaviour of LGM_HS6_DAT_VSM_2AE_Received
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_VSM_2AE_Received(void)
{
  LGM_HS6_DAT_VSM_2AE_Received_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_VSM_2AE_NotReceived
///
/// \descr  Stub function to simulate the behaviour of LGM_HS6_DAT_VSM_2AE_NotReceived
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_VSM_2AE_NotReceived(void)
{
  LGM_HS6_DAT_VSM_2AE_NotReceived_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_VSM_34E_Received
///
/// \descr  Stub function to simulate the behaviour of LGM_HS6_DAT_VSM_34E_Received
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_VSM_34E_Received(void)
{
  LGM_HS6_DAT_VSM_34E_Received_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_VSM_34E_NotReceived
///
/// \descr  Stub function to simulate the behaviour of LGM_HS6_DAT_VSM_34E_NotReceived
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_VSM_34E_NotReceived(void)
{
  LGM_HS6_DAT_VSM_34E_NotReceived_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  LGM_HS6_DAT_BSI_432_NotReceived
///
/// \descr  Stub function to simulate the behaviour of LGM_HS6_DAT_BSI_432_NotReceived
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LGM_HS6_DAT_BSI_432_NotReceived(void)
{
  LGM_HS6_DAT_BSI_432_NotReceived_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SysMon_SetDiagMux
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_SysMon_SetDiagMux
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SysMon_SetDiagMux(TE_Bool ppara1)
{
  Rte_Write_SysMon_SetDiagMux_Param1 = ppara1;
  Rte_Write_SysMon_SetDiagMux_HitCount++;

  return Rte_Write_SysMon_SetDiagMux_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SysMon_SendFrame457
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_SysMon_SendFrame457
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SysMon_SendFrame457(const tSysMon_SendFrame457* ppara1)
{
  Rte_Write_SysMon_SendFrame457_Param1 = *ppara1;
  Rte_Write_SysMon_SendFrame457_HitCount++;

  return Rte_Write_SysMon_SendFrame457_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SysMon_SendFrame477
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_SysMon_SendFrame477
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SysMon_SendFrame477(const tSysMon_SendFrame477* ppara1)
{
  Rte_Write_SysMon_SendFrame477_Param1 = *ppara1;
  Rte_Write_SysMon_SendFrame477_HitCount++;

  return Rte_Write_SysMon_SendFrame477_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_HS6_COMMANDES_VSM_036_Received
///
/// \descr  Stub function to simulate the behaviour of Rte_Read_SigPrep_HS6_COMMANDES_VSM_036_Received
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_HS6_COMMANDES_VSM_036_Received(tHS6_COMMANDES_VSM_036* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_HS6_COMMANDES_VSM_036_Received_Param1;
  Rte_Read_SigPrep_HS6_COMMANDES_VSM_036_Received_HitCount++;

  return Rte_Read_SigPrep_HS6_COMMANDES_VSM_036_Received_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_HS6_DAT_BSI_432_Received
///
/// \descr  Stub function to simulate the behaviour of Rte_Read_SigPrep_HS6_DAT_BSI_432_Received
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_HS6_DAT_BSI_432_Received(tHS6_DAT_BSI_432* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_HS6_DAT_BSI_432_Received_Param1;
  Rte_Read_SigPrep_HS6_DAT_BSI_432_Received_HitCount++;

  return Rte_Read_SigPrep_HS6_DAT_BSI_432_Received_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_HS6_DAT_VSM_2AE_Received
///
/// \descr  Stub function to simulate the behaviour of Rte_Read_SigPrep_HS6_DAT_VSM_2AE_Received
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_HS6_DAT_VSM_2AE_Received(tHS6_DAT_VSM_2AE* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_HS6_DAT_VSM_2AE_Received_Param1;
  Rte_Read_SigPrep_HS6_DAT_VSM_2AE_Received_HitCount++;

  return Rte_Read_SigPrep_HS6_DAT_VSM_2AE_Received_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_HS6_DAT_VSM_34E_Received
///
/// \descr  Stub function to simulate the behaviour of Rte_Read_SigPrep_HS6_DAT_VSM_34E_Received
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_HS6_DAT_VSM_34E_Received(tHS6_DAT_VSM_34E* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_HS6_DAT_VSM_34E_Received_Param1;
  Rte_Read_SigPrep_HS6_DAT_VSM_34E_Received_HitCount++;

  return Rte_Read_SigPrep_HS6_DAT_VSM_34E_Received_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_HS6_DYN_ABR_38D_Received
///
/// \descr  Stub function to simulate the behaviour of Rte_Read_SigPrep_HS6_DYN_ABR_38D_Received
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_HS6_DYN_ABR_38D_Received(tHS6_DYN_ABR_38D* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_HS6_DYN_ABR_38D_Received_Param1;
  Rte_Read_SigPrep_HS6_DYN_ABR_38D_Received_HitCount++;

  return Rte_Read_SigPrep_HS6_DYN_ABR_38D_Received_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_NMMode
///
/// \descr  Stub function to simulate the behaviour of Rte_Read_SigPrep_NMMode
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_NMMode(NM_ModeType* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_NMMode_Param1;
  Rte_Read_SigPrep_NMMode_HitCount++;

  return Rte_Read_SigPrep_NMMode_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_ElecInt_EnableCallbacks
///
/// \descr  Stub function to simulate the behaviour of Rte_Read_ElecInt_EnableCallbacks
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_ElecInt_EnableCallbacks(boolean* ppara1)
{
  *ppara1 = Rte_Read_ElecInt_EnableCallbacks_Param1;
  Rte_Read_ElecInt_EnableCallbacks_HitCount++;

  return Rte_Read_ElecInt_EnableCallbacks_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_ElecInt_ActivateTxBufer
///
/// \descr  Stub function to simulate the behaviour of Rte_Read_ElecInt_ActivateTxBufer
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_ElecInt_ActivateTxBufer(boolean* ppara1)
{
  *ppara1 = Rte_Read_ElecInt_ActivateTxBufer_Param1;
  Rte_Read_ElecInt_ActivateTxBufer_HitCount++;

  return Rte_Read_ElecInt_ActivateTxBufer_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CddBoost_BoostState
///
/// \descr  Stub function to simulate the behaviour of Rte_Read_CddBoost_BoostState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CddBoost_BoostState(tsRte_BoostState* ppara1)
{
  *ppara1 = Rte_Read_CddBoost_BoostState_Param1;
  Rte_Read_CddBoost_BoostState_HitCount++;

  return Rte_Read_CddBoost_BoostState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_SysVolt_LedVoltRng0_sVoltRng
///
/// \descr  Stub function to simulate the behavior of Rte_Read_SysVolt_LedVoltRng0_sVoltRng
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysVolt_LedVoltRng0_sVoltRng(teRte_SysVolt_Results* ppara1)
{
  *ppara1 = Rte_Read_SysVolt_LedVoltRng0_sVoltRng_Param1;
  Rte_Read_SysVolt_LedVoltRng0_sVoltRng_HitCount++;

  return Rte_Read_SysVolt_LedVoltRng0_sVoltRng_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_CtrlLed_LedChFbit
///
/// \descr  Stub function to simulate the behavior of Rte_Read_CtrlLed_LedChFbit
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlLed_LedChFbit(tsRte_LedChFbit* ppara1)
{
  *ppara1 = Rte_Read_CtrlLed_LedChFbit_Param1;
  Rte_Read_CtrlLed_LedChFbit_HitCount++;

  return Rte_Read_CtrlLed_LedChFbit_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  DAPI_RemoveAllDE
///
/// \descr  Stub function created to simulate the behaviour of DAPI_RemoveAllDE
///
/// \param  PIE_RemoveState
///
/// \return void
//-----------------------------------------------------------------------------
void DAPI_RemoveAllDE(const TE_Bool PIE_RemoveState)
{
  DAPI_RemoveAllDE_Param1 = PIE_RemoveState;
  DAPI_RemoveAllDE_HitCount++;
}


// EOF
