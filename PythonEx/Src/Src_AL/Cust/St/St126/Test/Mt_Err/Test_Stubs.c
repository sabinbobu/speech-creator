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
MemIf_JobResultType                    Fee_JobResult;
tieFeeState                            Fee_State;
tsRte_SigPrep_VehiclePitchAngle        sVehPitchAngle;
tDem_aEventStatus_type                 Dem_astEventStatus[DEM_CONFIG_ENTRY_MAX];
tsRte_SysMon_VehNetState               Rte_Read_SysMon_VehNetState_Param1;
teRte_MountingSide                     Rte_Read_IoHwAbUser_GetMountingSide_Param1;
tsRte_SigPrep_VehiclePitchAngle        Rte_Read_SigPrep_VehiclePitchAngle_Param1;
tiu32Voltage_mV                        Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;
tsRte_SysMon_VehicleSpeed              Rte_Read_SysMon_VehicleSpeed_Param1;
tsRte_OdometerTotal                    Rte_Read_SigPrep_OdometerTotal_Param1;
tsRte_SensorRaw                        Rte_Read_IoHwAb_GetSens_Raw_Param1;
boolean                                Dem_ClearAlec_Param1;
uint16                                 Dem_ClearAlec_Param2;
tsRte_ActStatStp0                      Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1;
tsRte_LgtFctState                      Rte_Read_FctR_LgtFctState_Param1;
boolean                                Rte_Read_FctR_TiFailureStatus_Param1;
tsRte_LgtFctStatus                     Rte_Read_FctR_LgtFctStatus_Param1;
uint16                                 Dem_boEventPassed_Param1;
uint32                                 LPTMR0_GetTimeElapsed_Param1;
NvM_BlockIdType                        NvM_WriteBlock_Param1;
void*                                  NvM_WriteBlock_Param2;
tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_00_Param1;
tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_01_Param1;
tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_02_Param1;
tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_03_Param1;
tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_04_Param1;
tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_05_Param1;
tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_06_Param1;
tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_07_Param1;
tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_08_Param1;
tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_09_Param1;
tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_10_Param1;
tsRte_Binning0                         Rte_Read_RSens_BinningClass_sVal_11_Param1;
tsRte_NTCTemperature                   Rte_Read_RSens_ThermzoneTemperatures_Param1;
tsRteCodingParameters                  Rte_Read_CodM_Err_Para_Param1;
tsRte_CtrlLed_ChStatesDiag             Rte_Read_CtrlLed_ChState_Param1;
tsRteNTCBinInData                      Rte_Read_RSens_NTC_BIN_Input_Errors_Param1;


//=============================================================================
// Stub function returned value stubs
//=============================================================================
Std_ReturnType                         Rte_Read_SysMon_VehNetState_RetVal;
Std_ReturnType                         Rte_Read_SigPrep_VehiclePitchAngle_RetVal;
Std_ReturnType                         Rte_Read_SysMon_VehicleSpeed_RetVal;
Std_ReturnType                         Rte_Read_SigPrep_OdometerTotal_RetVal;
Std_ReturnType                         Rte_Read_IoHwAb_GetSens_Raw_RetVal;
Std_ReturnType                         Rte_Read_CtrlStp_ActStatStp_sVal_0_RetVal;
Std_ReturnType                         Rte_Read_FctR_LgtFctState_RetVal;
Std_ReturnType                         Rte_Read_FctR_TiFailureStatus_RetVal;
Std_ReturnType                         Rte_Read_FctR_LgtFctStatus_RetVal;
Std_ReturnType                         NvM_WriteBlock_RetVal;
uint32                                 LPTMR0_GetTimeElapsed_RetVal;
uint8                                  Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
boolean                                Dem_boEventPassed_RetVal;
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_00_RetVal;
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_01_RetVal;
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_02_RetVal;
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_03_RetVal;
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_04_RetVal;
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_05_RetVal;
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_06_RetVal;
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_07_RetVal;
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_08_RetVal;
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_09_RetVal;
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_10_RetVal;
Std_ReturnType                         Rte_Read_RSens_BinningClass_sVal_11_RetVal;
uint8                                  Rte_Read_RSens_ThermzoneTemperatures_RetVal;
Std_ReturnType                         Rte_Read_CodM_Err_Para_RetVal;
Std_ReturnType                         Rte_Read_CtrlLed_ChState_RetVal;
Std_ReturnType                         Rte_Read_RSens_NTC_BIN_Input_Errors_RetVal;


//=============================================================================
// Stub function hit count variables
//=============================================================================
uint8                                  EcuM_Get_Mpu_Test_Hook_Address_HitCount;
uint8                                  Rte_Read_SysMon_VehNetState_HitCount;
uint8                                  Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
uint8                                  Rte_Read_SigPrep_VehiclePitchAngle_HitCount;
uint8                                  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount;
uint8                                  Rte_Read_SysMon_VehicleSpeed_HitCount;
uint8                                  Rte_Read_SigPrep_OdometerTotal_HitCount;
uint8                                  Rte_Read_IoHwAb_GetSens_Raw_HitCount;
uint8                                  Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount;
uint8                                  Rte_Read_FctR_LgtFctState_HitCount;
uint8                                  Rte_Read_FctR_TiFailureStatus_HitCount;
uint8                                  Rte_Read_FctR_LgtFctStatus_HitCount;
uint8                                  Dem_ClearAlec_HitCount;
uint8                                  Dem_boEventPassed_HitCount;
uint8                                  LPTMR0_GetTimeElapsed_HitCount;
uint8                                  NvM_WriteBlock_HitCount;
uint8                                  Rte_Read_RSens_BinningClass_sVal_00_HitCount;
uint8                                  Rte_Read_RSens_BinningClass_sVal_01_HitCount;
uint8                                  Rte_Read_RSens_BinningClass_sVal_02_HitCount;
uint8                                  Rte_Read_RSens_BinningClass_sVal_03_HitCount;
uint8                                  Rte_Read_RSens_BinningClass_sVal_04_HitCount;
uint8                                  Rte_Read_RSens_BinningClass_sVal_05_HitCount;
uint8                                  Rte_Read_RSens_BinningClass_sVal_06_HitCount;
uint8                                  Rte_Read_RSens_BinningClass_sVal_07_HitCount;
uint8                                  Rte_Read_RSens_BinningClass_sVal_08_HitCount;
uint8                                  Rte_Read_RSens_BinningClass_sVal_09_HitCount;
uint8                                  Rte_Read_RSens_BinningClass_sVal_10_HitCount;
uint8                                  Rte_Read_RSens_BinningClass_sVal_11_HitCount;
uint8                                  Rte_Read_RSens_ThermzoneTemperatures_HitCount;
uint8                                  Rte_Read_CodM_Err_Para_HitCount;
uint8                                  Rte_Read_CtrlLed_ChState_HitCount;
uint8                                  Rte_Read_RSens_NTC_BIN_Input_Errors_HitCount;


//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  EcuM_Get_Mpu_Test_Hook_Address
///
/// \descr  Stub function created to simulate the behaviour of EcuM_Get_Mpu_Test_Hook_Address
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void * EcuM_Get_Mpu_Test_Hook_Address(void)
{
  EcuM_Get_Mpu_Test_Hook_Address_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Dem_ClearAlec
///
/// \descr  Stub function created to simulate the behaviour of Dem_ClearAlec
///
/// \param  boAllAlecs, unDemIndex
///
/// \return void
//-----------------------------------------------------------------------------
void Dem_ClearAlec(boolean boAllAlecs, uint16 unDemIndex)
{
  boAllAlecs = Dem_ClearAlec_Param1;
  unDemIndex = Dem_ClearAlec_Param2;
  Dem_ClearAlec_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Dem_boEventPassed
///
/// \descr  Stub function created to simulate the behaviour of Dem_boEventPassed
///
/// \param  unEventIdx
///
/// \return void
//-----------------------------------------------------------------------------
boolean Dem_boEventPassed(uint16 unEventIdx)
{
  unEventIdx = Dem_boEventPassed_Param1;
  Dem_boEventPassed_HitCount++;

  return Dem_boEventPassed_RetVal;
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
/// \brief  Rte_Read_IoHwAbUser_GetMountingSide
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_IoHwAbUser_GetMountingSide
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//----------------------------------------------------------------------------
Std_ReturnType Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1)
{
  *ppara1 = Rte_Read_IoHwAbUser_GetMountingSide_Param1;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount++;

  return Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_VehiclePitchAngle
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_VehiclePitchAngle
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_VehiclePitchAngle(tsRte_SigPrep_VehiclePitchAngle* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_VehiclePitchAngle_Param1;
  Rte_Read_SigPrep_VehiclePitchAngle_HitCount++;

  return Rte_Read_SigPrep_VehiclePitchAngle_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT
///
/// \descr Stub function to simulate the behavior of Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT
///
/// \param  ppara1
///
/// \return void
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(tiu32Voltage_mV* ppara1)
{
  *ppara1 = Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;
  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_SysMon_VehicleSpeed
///
/// \descr Stub function for Rte_Read_SysMon_VehicleSpeed
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
/// \brief  Rte_Read_SigPrep_OdometerTotal
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_OdometerTotal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_OdometerTotal(tsRte_OdometerTotal* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_OdometerTotal_Param1;
  Rte_Read_SigPrep_OdometerTotal_HitCount++;

  return Rte_Read_SigPrep_OdometerTotal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_IoHwAb_GetSens_Raw
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_IoHwAb_GetSens_Raw
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_IoHwAb_GetSens_Raw(tsRte_SensorRaw* ppara1)
{
  *ppara1 = Rte_Read_IoHwAb_GetSens_Raw_Param1;
  Rte_Read_IoHwAb_GetSens_Raw_HitCount++;

  return Rte_Read_IoHwAb_GetSens_Raw_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlStp_ActStatStp_sVal_0
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CtrlStp_ActStatStp_sVal_0
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlStp_ActStatStp_sVal_0(tsRte_ActStatStp0* ppara1)
{
  *ppara1 = Rte_Read_CtrlStp_ActStatStp_sVal_0_Param1;
  Rte_Read_CtrlStp_ActStatStp_sVal_0_HitCount++;

  return Rte_Read_CtrlStp_ActStatStp_sVal_0_RetVal;
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
/// \brief  Rte_Read_FctR_TiFailureStatus
///
/// \descr  stub function to simulate the behaviour of Rte_Read_FctR_LgtFctStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_FctR_LgtFctStatus(tsRte_LgtFctStatus* ppara1)
{
  *ppara1 = Rte_Read_FctR_LgtFctStatus_Param1;
  Rte_Read_FctR_LgtFctStatus_HitCount++;

  return Rte_Read_FctR_LgtFctStatus_RetVal;
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

  return LPTMR0_GetTimeElapsed_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  NvM_WriteBlock
///
/// \descr  Stub function created to simulate the behaviour of NvM_WriteBlock
///
/// \param  - BlockId, NvM_SrcPtr
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType NvM_WriteBlock(NvM_BlockIdType BlockId, void* NvM_SrcPtr)
{
  NvM_WriteBlock_Param1 = BlockId;
  NvM_WriteBlock_Param2 = NvM_SrcPtr;
  NvM_WriteBlock_HitCount++;

  return NvM_WriteBlock_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_00
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_RSens_BinningClass_sVal_00
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_00(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_00_Param1;
  Rte_Read_RSens_BinningClass_sVal_00_HitCount++;

  return Rte_Read_RSens_BinningClass_sVal_00_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_01
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_RSens_BinningClass_sVal_01
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_01(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_01_Param1;
  Rte_Read_RSens_BinningClass_sVal_01_HitCount++;

  return Rte_Read_RSens_BinningClass_sVal_01_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_02
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_RSens_BinningClass_sVal_02
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_02(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_02_Param1;
  Rte_Read_RSens_BinningClass_sVal_02_HitCount++;

  return Rte_Read_RSens_BinningClass_sVal_02_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_03
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_RSens_BinningClass_sVal_03
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_03(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_03_Param1;
  Rte_Read_RSens_BinningClass_sVal_03_HitCount++;

  return Rte_Read_RSens_BinningClass_sVal_03_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_04
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_RSens_BinningClass_sVal_04
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_04(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_04_Param1;
  Rte_Read_RSens_BinningClass_sVal_04_HitCount++;

  return Rte_Read_RSens_BinningClass_sVal_04_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_05
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_RSens_BinningClass_sVal_05
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_05(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_05_Param1;
  Rte_Read_RSens_BinningClass_sVal_05_HitCount++;

  return Rte_Read_RSens_BinningClass_sVal_05_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_06
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_RSens_BinningClass_sVal_06
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_06(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_06_Param1;
  Rte_Read_RSens_BinningClass_sVal_06_HitCount++;

  return Rte_Read_RSens_BinningClass_sVal_06_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_07
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_RSens_BinningClass_sVal_07
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_07(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_07_Param1;
  Rte_Read_RSens_BinningClass_sVal_07_HitCount++;

  return Rte_Read_RSens_BinningClass_sVal_07_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_08
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_RSens_BinningClass_sVal_08
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_08(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_08_Param1;
  Rte_Read_RSens_BinningClass_sVal_08_HitCount++;

  return Rte_Read_RSens_BinningClass_sVal_08_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_09
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_RSens_BinningClass_sVal_09
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_09(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_09_Param1;
  Rte_Read_RSens_BinningClass_sVal_09_HitCount++;

  return Rte_Read_RSens_BinningClass_sVal_09_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_10
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_RSens_BinningClass_sVal_10
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_10(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_10_Param1;
  Rte_Read_RSens_BinningClass_sVal_10_HitCount++;

  return Rte_Read_RSens_BinningClass_sVal_10_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_BinningClass_sVal_11
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_RSens_BinningClass_sVal_11
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_BinningClass_sVal_11(tsRte_Binning0* ppara1)
{
  *ppara1 = Rte_Read_RSens_BinningClass_sVal_11_Param1;
  Rte_Read_RSens_BinningClass_sVal_11_HitCount++;

  return Rte_Read_RSens_BinningClass_sVal_11_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_ThermzoneTemperatures
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_RSens_ThermzoneTemperatures
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_ThermzoneTemperatures(tsRte_NTCTemperature* ppara1)
{
  *ppara1 = Rte_Read_RSens_ThermzoneTemperatures_Param1;
  Rte_Read_RSens_ThermzoneTemperatures_HitCount++;
  return Rte_Read_RSens_ThermzoneTemperatures_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CodM_Err_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CodM_Err_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CodM_Err_Para(tsRteCodingParameters* ppara1)
{
  *ppara1 = Rte_Read_CodM_Err_Para_Param1;
  Rte_Read_CodM_Err_Para_HitCount++;

  return Rte_Read_CodM_Err_Para_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_NTC_BIN_Input_Errors
///
/// \descr  Stub function created to simulate the behavior of Rte_Read_RSens_NTC_BIN_Input_Errors
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_NTC_BIN_Input_Errors(tsRteNTCBinInData* ppara1)
{
  *ppara1 = Rte_Read_RSens_NTC_BIN_Input_Errors_Param1;
  Rte_Read_RSens_NTC_BIN_Input_Errors_HitCount++;
  return Rte_Read_RSens_NTC_BIN_Input_Errors_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlLed_ChState
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CtrlLed_ChState
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------

Std_ReturnType Rte_Read_CtrlLed_ChState(tsRte_CtrlLed_ChStatesDiag* ppara1)
{
  *ppara1 = Rte_Read_CtrlLed_ChState_Param1;
  Rte_Read_CtrlLed_ChState_HitCount++;
  return Rte_Read_CtrlLed_ChState_RetVal;
}

// EOF
