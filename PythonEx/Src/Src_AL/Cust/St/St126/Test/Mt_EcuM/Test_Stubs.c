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
#include <ALUnitTest_UserInterface.h>
#include "Test_Stubs.h"

//=============================================================================
// Stub function parameter stubs
//=============================================================================

tieFeeState                             Fee_State;
MemIf_JobResultType                     Fee_JobResult;

teRte_WarningMode                       Rte_Read_FctR_TiWarningMode_Param1;
teRte_MountingSide                      Rte_Read_IoHwAbUser_GetMountingSide_Param1;
teRte_ReqLightState                     Rte_Read_SysMon_LowBeamCmd_Req_Param1;
uint8                                   WdgM_SetLocalCheckPoint_Param1;
Mcu_ClockType*                          Mcu_InitClock_Param1;
NvM_BlockIdType                         NvM_GetErrorStatus_Param1;
NvM_RequestResultType*                  NvM_GetErrorStatus_Param2;
CONST_AL sIcu_ConfigType*               Icu_Init_Param1;
CONST_AL tsAdc_CfgData* CONST_AL        Adc_Init_Param1;
CONST_AL tsPdb_CfgData* CONST_AL        Pdb_Init_Param1;
CONST_AL tsTrigMux_CfgData* CONST_AL    TrigMux_Init_Param1;
CONST_AL tsLpit_CfgData * CONST_AL      Lpit_Init_Param1;
tsRte_SysMonLgtFctsReq                  Rte_Read_SysMon_StdLgtFcts_Req_Param1;
tsRte_SysMonLgtTiReq                    Rte_Read_SysMon_StdLgtTi_Req_Param1;
uint32                                  LPTMR0_GetTimeElapsed_Param1;
uint16                                  Dem_SetEventStatus_Param1;
uint8                                   Dem_SetEventStatus_Param2;
boolean                                 Dem_Set_Init_Window_Param1;
IRQn_Type                               INT_SYS_SetPriority_Param1;
uint8_t                                 INT_SYS_SetPriority_Param2;
IRQn_Type                               INT_SYS_EnableIRQ_Param1;
AppModeType                             StartOS_Param1;
uint8   Rte_Read_SigPrep_SleepBSI_Param1;
uint8   Rte_Read_ElecInt_RequestRUN_Param1;
uint8   Rte_Read_ElecInt_ReleaseRUN_Param1;
uint8   Rte_Read_ElecInt_ReleasePOST_RUN_Param1;
uint8   Rte_Read_Diag_RequestPOST_RUN_Param1;
boolean Rte_Write_EcuM_Deinit_Param1;
uint32*  Rte_Write_MPU_ErrorCounter_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

Std_ReturnType          Rte_Read_FctR_TiWarningMode_RetVal;
Std_ReturnType          Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
SysMon_EnumLowBeamState SysMonRx_ASIL_GetLowBeamState_RetVal;
SysMon_EnumSpeedState   SysMonRx_ASIL_GetSpeedState_RetVal;
Std_ReturnType          Rte_Read_SysMon_LowBeamCmd_Req_RetVal;
Std_ReturnType          Mcu_InitClock_RetVal;
Std_ReturnType          NvM_GetErrorStatus_RetVal;
uint32                  LPTMR0_GetTimeElapsed_RetVal;
Std_ReturnType          Rte_Read_SysMon_StdLgtFcts_Req_RetVal;
Std_ReturnType          Rte_Read_SysMon_StdLgtTi_Req_RetVal;
bool                    Mcu_InitHasBeenCalled_RetVal;
Mcu_ResetType           Mcu_GetResetReason_RetVal;
boolean                 SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal;
Std_ReturnType          Rte_Read_SigPrep_SleepBSI_RetVal;
Std_ReturnType          Rte_Read_ElecInt_RequestRUN_RetVal;
Std_ReturnType          Rte_Read_ElecInt_ReleaseRUN_RetVal;
Std_ReturnType          Rte_Read_ElecInt_ReleasePOST_RUN_RetVal;
Std_ReturnType          Rte_Read_Diag_RequestPOST_RUN_RetVal;
uint32                  Os_Get_BusFaultCnt_RetVal;
uint32                  Rte_Write_MPU_ErrorCounter_RetVal;
Std_ReturnType          Rte_Write_EcuM_Deinit_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

uint8 Rte_Read_FctR_TiWarningMode_HitCount;
uint8 Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
uint8 CddSbc_SetWdgTimeoutModeAnd200ms_HitCount;
uint8 ENABLE_INTERRUPTS_HitCount;
uint8 SigPrepRx_ComM_DisableCallbacks_HitCount;
uint8 SysMonTx_ComM_DeactivateTxBuffer_HitCount;
uint8 SigPrepTx_ComM_ActivateTxBufer_HitCount;
uint8 SigPrepTx_ComM_DeactivateTxBuffer_HitCount;
uint8 SigPrepRx_ComM_EnableCallbacks_HitCount;
uint8 SysMonRx_ASIL_GetLowBeamState_HitCount;
uint8 SysMonRx_ASIL_GetSpeedState_HitCount;
uint8 SysMonRx_ComM_DisableCallbacks_HitCount;
uint8 SysMonTx_ComM_ActivateTxBufer_HitCount;
uint8 SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount;
uint8 SysMonRx_ComM_EnableCallbacks_HitCount;
uint8 Rte_Read_SysMon_LowBeamCmd_Req_HitCount;
uint8 WdgM_SetLocalCheckPoint_HitCount;
uint8 WdgM_ResetShaDataResetReason_HitCount;
uint8 Dem_ClearStartUpStatus_HitCount;
uint8 Mcu_InitClock_HitCount;
uint8 Icu_Init_HitCount;
uint8 INT_SYS_SetPriority_HitCount;
uint8 INT_SYS_EnableIRQGlobal_HitCount;
uint8 INT_SYS_EnableIRQ_HitCount;
uint8 StartOS_HitCount;
uint8 NvM_GetErrorStatus_HitCount;
uint8 Nvm_WriteAll_HitCount;
uint8 Mcu_PerformReset_HitCount;
uint8 LPTMR0_GetTimeElapsed_HitCount;
uint8 Dem_SetEventStatus_HitCount;
uint8 Dem_Set_Init_Window_HitCount;
uint8 Rte_Read_SysMon_StdLgtFcts_Req_HitCount;
uint8 Rte_Read_SysMon_StdLgtTi_Req_HitCount;
uint8 CddBoost_Shutdown_HitCount;
uint8 CddSbc_SetSleepMode_HitCount;
uint8 riNvM_Init_HitCount;
uint8 CddSpi_Stop_HitCount;
uint8 NvM_MainFunction_HitCount;
uint8 NvM_ReadAll_HitCount;
uint8 riDem_Init_HitCount;
uint8 riErrCust_Init_HitCount;
uint8 CddStp_Tsp_Init_HitCount;
uint8 CddSpi_Init_HitCount;
uint8 CddSbc_Init_HitCount;
uint8 SysVolt_Init_HitCount;
uint8 riFee_Init_HitCount;
uint8 CddDma_Init_HitCount;
uint8 Mcu_InitHasBeenCalled_HitCount;
uint8 Mcu_GetResetReason_HitCount;
uint8 StatM_Deinit_HitCount;
uint8 IoHwAbUser_InitGetMountingSide_HitCount;
uint8 Rte_Read_SigPrep_SleepBSI_HitCount;
uint8 Rte_Read_ElecInt_RequestRUN_HitCount;
uint8 Rte_Read_ElecInt_ReleaseRUN_HitCount;
uint8 Rte_Read_ElecInt_ReleasePOST_RUN_HitCount;
uint8 Rte_Read_Diag_RequestPOST_RUN_HitCount;
uint8 Os_Get_BusFaultCnt_HitCount;
uint8 Rte_Write_MPU_ErrorCounter_HitCount;
uint8 Rte_Write_EcuM_Deinit_HitCount;

//=============================================================================
// Global variable stubs ( registers, global variables from other modules which are referenced in the module )
//=============================================================================

Mcu_ClockType	       Mcu_ClockData;
LGM_BOOL             NM_CAN_b_SleepBSIframe;
boolean              Mcu_boInitHasBeenCalled;


//=============================================================================
// Stub function definitions
//=============================================================================

void EcuM_GetMcuPrivilegeStatus(void) {}
void EcuM_UserSwitch(void) {}
void EcuM_PrivilegeSwitch(void) {}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_FctR_TiWarningMode
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_FctR_TiWarningMode
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_FctR_TiWarningMode(teRte_WarningMode* ppara1)
{
  *ppara1 = Rte_Read_FctR_TiWarningMode_Param1;
  Rte_Read_FctR_TiWarningMode_HitCount++;

  return Rte_Read_FctR_TiWarningMode_RetVal;
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
/// \brief  CddSbc_SetWdgTimeoutModeAnd200ms
///
/// \descr  Stub function created to simulate the behaviour of CddSbc_SetWdgTimeoutModeAnd200ms
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void CddSbc_SetWdgTimeoutModeAnd200ms(void)
{
  CddSbc_SetWdgTimeoutModeAnd200ms_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  ENABLE_INTERRUPTS
///
/// \descr  Stub function created to simulate the behaviour of ENABLE_INTERRUPTS
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void ENABLE_INTERRUPTS(void)
{
  ENABLE_INTERRUPTS_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  SigPrepRx_ComM_DisableCallbacks
///
/// \descr  Stub function created to simulate the behaviour of SigPrepRx_ComM_DisableCallbacks
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrepRx_ComM_DisableCallbacks(void)
{
  SigPrepRx_ComM_DisableCallbacks_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  IoHwAbUser_InitGetMountingSide
///
/// \descr  Stub function created to simulate the behaviour of IoHwAbUser_InitGetMountingSide
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void IoHwAbUser_InitGetMountingSide(void)
{
  IoHwAbUser_InitGetMountingSide_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  SysMonTx_ComM_DeactivateTxBuffer
///
/// \descr  Stub function created to simulate the behaviour of SysMonTx_ComM_DeactivateTxBuffer
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonTx_ComM_DeactivateTxBuffer(void)
{
  SysMonTx_ComM_DeactivateTxBuffer_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  SigPrepTx_ComM_ActivateTxBufer
///
/// \descr  Stub function created to simulate the behaviour of SigPrepTx_ComM_ActivateTxBufer
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrepTx_ComM_ActivateTxBufer(void)
{
  SigPrepTx_ComM_ActivateTxBufer_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  SigPrepTx_ComM_DeactivateTxBuffer
///
/// \descr  Stub function created to simulate the behaviour of SigPrepTx_ComM_DeactivateTxBuffer
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrepTx_ComM_DeactivateTxBuffer(void)
{
  SigPrepTx_ComM_DeactivateTxBuffer_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  SigPrepRx_ComM_EnableCallbacks
///
/// \descr  Stub function created to simulate the behaviour of SigPrepRx_ComM_EnableCallbacks
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void SigPrepRx_ComM_EnableCallbacks(void)
{
  SigPrepRx_ComM_EnableCallbacks_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_GetLowBeamState
///
/// \descr  Stub function created to simulate the behaviour of SysMonRx_ASIL_GetLowBeamState
///
/// \param  void
///
/// \return SysMon_EnumLowBeamState
//-----------------------------------------------------------------------------
SysMon_EnumLowBeamState SysMonRx_ASIL_GetLowBeamState(void)
{
  SysMonRx_ASIL_GetLowBeamState_HitCount++;
  return SysMonRx_ASIL_GetLowBeamState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_GetSpeedState
///
/// \descr  Stub function created to simulate the behaviour of SysMonRx_ASIL_GetSpeedState
///
/// \param  void
///
/// \return SysMon_EnumSpeedState
//-----------------------------------------------------------------------------
SysMon_EnumSpeedState SysMonRx_ASIL_GetSpeedState(void)
{
  SysMonRx_ASIL_GetSpeedState_HitCount++;
  return SysMonRx_ASIL_GetSpeedState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ComM_DisableCallbacks
///
/// \descr  Stub function created to simulate the behaviour of SysMonRx_ComM_DisableCallbacks
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonRx_ComM_DisableCallbacks(void)
{
  SysMonRx_ComM_DisableCallbacks_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  SysMonTx_ComM_ActivateTxBufer
///
/// \descr  Stub function created to simulate the behaviour of SysMonTx_ComM_ActivateTxBufer
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonTx_ComM_ActivateTxBufer(void)
{
  SysMonTx_ComM_ActivateTxBufer_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam
///
/// \descr  Stub function created to simulate the behaviour of SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam
///
/// \param  boolean
///
/// \return void
//-----------------------------------------------------------------------------
boolean SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam(void)
{
  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_HitCount++;
  return SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  SysMonRx_ComM_EnableCallbacks
///
/// \descr  Stub function created to simulate the behaviour of SysMonRx_ComM_EnableCallbacks
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonRx_ComM_EnableCallbacks(void)
{
  SysMonRx_ComM_EnableCallbacks_HitCount++;
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
/// \brief  WdgM_SetLocalCheckPoint
///
/// \descr  Stub function created to simulate the behaviour of WdgM_SetLocalCheckPoint
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void WdgM_SetLocalCheckPoint(uint8 ucId)
{
  WdgM_SetLocalCheckPoint_Param1 = ucId;
  WdgM_SetLocalCheckPoint_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  WdgM_ResetShaDataResetReason
///
/// \descr  Stub function created to simulate the behaviour of WdgM_ResetShaDataResetReason
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void WdgM_ResetShaDataResetReason(void)
{
  WdgM_ResetShaDataResetReason_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Dem_ClearStartUpStatus
///
/// \descr  Stub function created to simulate the behaviour of Dem_ClearStartUpStatus
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void Dem_ClearStartUpStatus(void)
{
  Dem_ClearStartUpStatus_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief Dem_Set_Init_Window
///
/// \descr
///
/// \param  boWindowValue
///
/// \return void
//-----------------------------------------------------------------------------
void Dem_Set_Init_Window(boolean boWindowValue)
{
  Dem_Set_Init_Window_Param1 = boWindowValue;
  Dem_Set_Init_Window_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Mcu_InitClock
///
/// \descr  Stub function created to simulate the behaviour of Mcu_InitClock
///
/// \param  ClockSetting
///
/// \return Mcu_InitClock_RetVal
//-----------------------------------------------------------------------------
Std_ReturnType Mcu_InitClock(Mcu_ClockType* ClockSetting)
{
  *Mcu_InitClock_Param1 = *ClockSetting;
  Mcu_InitClock_HitCount++;
  return Mcu_InitClock_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  NvM_GetErrorStatus
///
/// \descr  Stub function created to simulate the behaviour of NvM_GetErrorStatus
///
/// \param  BlockId 
/// \param  *RequestResultPtr
///
/// \return NvM_GetErrorStatus_RetVal
//-----------------------------------------------------------------------------
Std_ReturnType NvM_GetErrorStatus(NvM_BlockIdType BlockId, NvM_RequestResultType *RequestResultPtr)
{
  NvM_GetErrorStatus_Param1 = BlockId;
  *RequestResultPtr = NvM_GetErrorStatus_Param2;
  NvM_GetErrorStatus_HitCount++;
  return NvM_GetErrorStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Icu_Init
///
/// \descr  Stub function created to simulate the behaviour of Icu_Init
///
/// \param  ConfigPtr
///
/// \return void
//-----------------------------------------------------------------------------
void Icu_Init(CONST_AL sIcu_ConfigType* ConfigPtr)
{
  Icu_Init_Param1 = ConfigPtr;
  Icu_Init_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  NvM_WriteAll
///
/// \descr  Stub function created to simulate the behaviour of NvM_WriteAll
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void NvM_WriteAll(void)
{
  Nvm_WriteAll_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Mcu_PerformReset
///
/// \descr  Stub function created to simulate the behaviour of Mcu_PerformReset
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void Mcu_PerformReset(void)
{
  Mcu_PerformReset_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief LPTMR0_GetTimeElapsed
///
/// \descr Stub function for LPTMR0_GetTimeElapsed
///
/// \param  ulStartValue
///
/// \return LPTMR0_GetTimeElapsed_RetVal
//-----------------------------------------------------------------------------
uint32 LPTMR0_GetTimeElapsed(const uint32 ulStartValue)
{
  LPTMR0_GetTimeElapsed_Param1 = ulStartValue;
  LPTMR0_GetTimeElapsed_HitCount++;
  return LPTMR0_GetTimeElapsed_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_StdLgtFcts_Req
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SysMon_StdLgtFcts_Req
///
/// \param  ppara1
///
/// \return Rte_Read_SysMon_StdLgtFcts_Req_RetVal
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_StdLgtFcts_Req(tsRte_SysMonLgtFctsReq* ppara1)
{
  *ppara1 = Rte_Read_SysMon_StdLgtFcts_Req_Param1;
  Rte_Read_SysMon_StdLgtFcts_Req_HitCount++;
  return Rte_Read_SysMon_StdLgtFcts_Req_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  INT_SYS_SetPriority
///
/// \descr  Stub function created to simulate the behaviour of INT_SYS_SetPriority
///
/// \param  irqNumber  
/// \param  priority
///
/// \return void
//-----------------------------------------------------------------------------
void INT_SYS_SetPriority(IRQn_Type irqNumber, uint8_t priority)
{
  INT_SYS_SetPriority_Param1 = irqNumber;
  INT_SYS_SetPriority_Param2 = priority;
  INT_SYS_SetPriority_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  INT_SYS_EnableIRQGlobal
///
/// \descr  Stub function created to simulate the behaviour of INT_SYS_EnableIRQGlobal
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void INT_SYS_EnableIRQGlobal(void)
{
  INT_SYS_EnableIRQGlobal_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  INT_SYS_EnableIRQ
///
/// \descr  Stub function created to simulate the behaviour of INT_SYS_EnableIRQ
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void INT_SYS_EnableIRQ(IRQn_Type irqNumber)
{
  INT_SYS_EnableIRQ_Param1 = irqNumber;
  INT_SYS_EnableIRQ_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  StartOS
///
/// \descr  Stub function created to simulate the behaviour of StartOS
///
/// \param  AppModeType
///
/// \return void
//-----------------------------------------------------------------------------
void StartOS(AppModeType Mode)
{
  StartOS_Param1 = Mode;
  StartOS_HitCount++;
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
/// \brief  CddBoost_Shutdown
///
/// \descr  Stub function created to simulate the behaviour of CddBoost_Shutdown
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void CddBoost_Shutdown(void)
{
  CddBoost_Shutdown_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CddSbc_SetSleepMode
///
/// \descr  Stub function created to simulate the behaviour of CddSbc_SetSleepMode
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void CddSbc_SetSleepMode(void)
{
  CddSbc_SetSleepMode_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  riNvM_Init
///
/// \descr  Stub function created to simulate the behaviour of riNvM_Init
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void riNvM_Init(void)
{
  riNvM_Init_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CddStp_Tsp_Init
///
/// \descr  Stub function created to simulate the behaviour of CddStp_Tsp_Init
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void CddStp_Tsp_Init(void)
{
  CddStp_Tsp_Init_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CddSpi_Stop
///
/// \descr  Stub function created to simulate the behaviour of CddSpi_Stop
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void CddSpi_Stop(void)
{
  CddSpi_Stop_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  NvM_MainFunction
///
/// \descr  Stub function created to simulate the behaviour of NvM_MainFunction
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void NvM_MainFunction(void)
{
  NvM_MainFunction_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  NvM_ReadAll
///
/// \descr  Stub function created to simulate the behaviour of NvM_ReadAll
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void NvM_ReadAll(void)
{
  NvM_ReadAll_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  riDem_Init
///
/// \descr  Stub function created to simulate the behaviour of riDem_Init
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void riDem_Init(void)
{
  riDem_Init_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  riErrCust_Init
///
/// \descr  Stub function created to simulate the behaviour of riErrCust_Init
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void riErrCust_Init(void)
{
  riErrCust_Init_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CddSpi_Init
///
/// \descr  Stub function created to simulate the behaviour of CddSpi_Init
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void CddSpi_Init(void)
{
  CddSpi_Init_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CddSbc_Init
///
/// \descr  Stub function created to simulate the behaviour of CddSbc_Init
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void CddSbc_Init(void)
{
  CddSbc_Init_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  SysVolt_Init
///
/// \descr  Stub function created to simulate the behaviour of SysVolt_Init
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void SysVolt_Init(void)
{
  SysVolt_Init_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  riFee_Init
///
/// \descr  Stub function created to simulate the behaviour of riFee_Init
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void riFee_Init(void)
{
  riFee_Init_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  CddDma_Init
///
/// \descr  Stub function created to simulate the behaviour of CddDma_Init
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void CddDma_Init(void)
{
  CddDma_Init_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Mcu_InitHasBeenCalled
///
/// \descr  Stub function created to simulate the behaviour of Mcu_InitHasBeenCalled
///
/// \param  
///
/// \return Mcu_InitHasBeenCalled_RetVal
//-----------------------------------------------------------------------------
bool Mcu_InitHasBeenCalled()
{
  Mcu_InitHasBeenCalled_HitCount++;
  return Mcu_InitHasBeenCalled_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Dem_SetEventStatus
///
/// \descr  Stub function created to simulate the behaviour of Dem_SetEventStatus
///
/// \param  unAlecId
/// \param  ucTestStatus
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
/// \brief StatM_Deinit
///
/// \descr Stub function created to simulate the behaviour of StatM_Deinit
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void StatM_Deinit(void)
{
  StatM_Deinit_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_SleepBSI
///
/// \descr  Stub function to simulate the behaviour of Rte_Read_SigPrep_SleepBSI
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_SleepBSI(uint8* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_SleepBSI_Param1;
  Rte_Read_SigPrep_SleepBSI_HitCount++;
  return Rte_Read_SigPrep_SleepBSI_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_ElecInt_RequestRUN
///
/// \descr  Stub function to simulate the behaviour of Rte_Read_ElecInt_RequestRUN
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_ElecInt_RequestRUN(uint8* ppara1)
{
  *ppara1 = Rte_Read_ElecInt_RequestRUN_Param1;
  Rte_Read_ElecInt_RequestRUN_HitCount++;
  return Rte_Read_ElecInt_RequestRUN_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_ElecInt_ReleaseRUN
///
/// \descr  Stub function to simulate the behaviour of Rte_Read_ElecInt_ReleaseRUN
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_ElecInt_ReleaseRUN(uint8* ppara1)
{
  *ppara1 = Rte_Read_ElecInt_ReleaseRUN_Param1;
  Rte_Read_ElecInt_ReleaseRUN_HitCount++;
  return Rte_Read_ElecInt_ReleaseRUN_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_ElecInt_ReleasePOST_RUN
///
/// \descr  Stub function to simulate the behaviour of Rte_Read_ElecInt_ReleasePOST_RUN
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_ElecInt_ReleasePOST_RUN(uint8* ppara1)
{
  *ppara1 = Rte_Read_ElecInt_ReleasePOST_RUN_Param1;
  Rte_Read_ElecInt_ReleasePOST_RUN_HitCount++;
  return Rte_Read_ElecInt_ReleasePOST_RUN_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Os_Get_BusFaultCnt
///
/// \descr  Stub function to simulate the behaviour of Os_Get_BusFaultCnt
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
uint32 Os_Get_BusFaultCnt(void)
{
  Os_Get_BusFaultCnt_HitCount++;
  return Os_Get_BusFaultCnt_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Write_MPU_ErrorCounter
///
/// \descr Stub function to simulate the behaviour of Rte_Write_MPU_ErrorCounter
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Write_MPU_ErrorCounter(uint32* ppara1)
{
  *Rte_Write_MPU_ErrorCounter_Param1 = *ppara1;
  Rte_Write_MPU_ErrorCounter_HitCount++;
  return Rte_Write_MPU_ErrorCounter_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_Diag_RequestPOST_RUN
///
/// \descr  Stub function to simulate the behaviour of Rte_Read_Diag_RequestPOST_RUN
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Diag_RequestPOST_RUN(uint8* ppara1)
{
  *ppara1 = Rte_Read_Diag_RequestPOST_RUN_Param1;
  Rte_Read_Diag_RequestPOST_RUN_HitCount++;
  return Rte_Read_Diag_RequestPOST_RUN_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_EcuM_Deinit
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_EcuM_Deinit
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_EcuM_Deinit(boolean ppara1)
{
  Rte_Write_EcuM_Deinit_Param1 = ppara1;
  Rte_Write_EcuM_Deinit_HitCount++;
  return Rte_Write_EcuM_Deinit_RetVal;
}
