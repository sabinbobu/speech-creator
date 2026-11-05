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

tNvmPara_CodingArea     Coding_Dummy = { 0 };
tParaFct0_Cmd           Coding_State = eParaFct0_CodingDataInvalid;

teRte_HlsSensorState          Rte_Write_Pitch_PlausState_Param1;
tPitch0                       Rte_Write_Pitch_Angle_Param1;
tsRte_CtrlStpValidation       Rte_Read_CtrlStp_Validation_Port_Param1;
tsRte_SysMon_VehicleSpeed     Rte_Read_SysMon_VehicleSpeed_Param1;
tsRte_SysMon_VehNetState      Rte_Read_SysMon_VehNetState_Param1;
tsRteCodingParameters         Rte_Read_CodM_Pitch_Para_Param1;
tsRte_SensorRaw               Rte_Read_IoHwAb_GetSens_Raw_Param1;
tsRte_SensorBalance           Rte_Read_IoHwAb_GetSens_Balanced_Param1;
tsRte_CtrlDcmStatusParams     Rte_Read_CtrlDcm_StatusParameters_Port_Param1;
tiu16Voltage_mV               Rte_Read_IoHwAb_VCCX1Voltage_Param1;
uint32                        LPTMR0_GetTimeElapsed_Param1;
uint16                        Dem_SetEventStatus_Param1;
uint8                         Dem_SetEventStatus_Param2;
NvM_BlockIdType               NvM_WriteBlock_Param1;
void* NvM_WriteBlock_Param2;
sint16                        UTIL_ABS_Param1;


//=============================================================================
// Stub function returned value stubs
//=============================================================================

Std_ReturnType   Rte_Write_Pitch_PlausState_RetVal;
Std_ReturnType   Rte_Write_Pitch_Angle_RetVal;
Std_ReturnType   Rte_Read_CtrlStp_Validation_Port_RetVal;
Std_ReturnType   Rte_Read_SysMon_VehicleSpeed_RetVal;
Std_ReturnType   Rte_Read_SysMon_VehNetState_RetVal;
Std_ReturnType   Rte_Read_CodM_Pitch_Para_RetVal;
Std_ReturnType   Rte_Read_IoHwAb_GetSens_Raw_RetVal;
Std_ReturnType   Rte_Read_IoHwAb_GetSens_Balanced_RetVal;
Std_ReturnType   Rte_Read_IoHwAb_VCCX1Voltage_RetVal;
Std_ReturnType   Rte_Read_CtrlDcm_StatusParameters_Port_RetVal;
uint32           LPTMR0_GetTimeElapsed_RetVal;
uint16           Dem_SetEventStatus_RetVal;
uint8            Cod_Pitch_ErrCntMax_RetVal;
uint8            Pitch_ErrCntInc_RetVal;
uint8            Pitch_ErrCntDec_RetVal;
Std_ReturnType   NvM_WriteBlock_RetVal;
Std_ReturnType   UTIL_ABS_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

uint8  Rte_Write_Pitch_PlausState_HitCount;
uint8  Rte_Write_Pitch_Angle_HitCount;
uint8  Rte_Read_CtrlDcm_StatusParameters_Port_HitCount;
uint8  Rte_Read_CtrlStp_Validation_Port_HitCount;
uint8  Rte_Read_SysMon_VehicleSpeed_HitCount;
uint8  Rte_Read_SysMon_VehNetState_HitCount;
uint8  Rte_Read_CodM_Pitch_Para_HitCount;
uint8  Rte_Read_IoHwAb_GetSens_Raw_HitCount;
uint8  Rte_Read_IoHwAb_GetSens_Balanced_HitCount;
uint8  Rte_Read_IoHwAb_VCCX1Voltage_HitCount;
uint8  Rte_Read_SysMon_VehNetStat_HitCount;
uint8  LPTMR0_GetTimeElapsed_HitCount;
uint8  Dem_SetEventStatus_HitCount;
uint8  NvM_WriteBlock_HitCount;
uint8  UTIL_ABS_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief UTIL_ABS
///
/// \descr Stub function for UTIL_ABS
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType UTIL_ABS(const sint16 ppara1)
{
  UTIL_ABS_Param1 = ppara1;
  UTIL_ABS_HitCount++;
  return UTIL_ABS_RetVal;
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
/// \brief  Rte_Write_Pitch_PlausState
///
/// \descr Stub used to simulate the behaviour of Rte_Write_Pitch_PlausState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Pitch_PlausState(teRte_HlsSensorState* ppara1)
{

  Rte_Write_Pitch_PlausState_Param1 = *ppara1;
  Rte_Write_Pitch_PlausState_HitCount++;
  return  Rte_Write_Pitch_PlausState_RetVal;

}
//-----------------------------------------------------------------------------
/// \brief Rte_Write_Pitch_Angle
///
/// \descr Stub used to simulate the behaviour of Rte_Write_Pitch_Angle
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_Pitch_Angle(tPitch0* ppara1)
{
  Rte_Write_Pitch_Angle_Param1 = *ppara1;
  Rte_Write_Pitch_Angle_HitCount++;
  return  Rte_Write_Pitch_Angle_RetVal;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlStp_Validation_Port
///
/// \descr Stub used to simulate the behaviour of Rte_Read_CtrlStp_Validation_Port
///
/// \param   ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlStp_Validation_Port(tsRte_CtrlStpValidation* ppara1)
{
  *ppara1 = Rte_Read_CtrlStp_Validation_Port_Param1;
  Rte_Read_CtrlStp_Validation_Port_HitCount++;
  return Rte_Read_CtrlStp_Validation_Port_RetVal;

}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlDcm_StatusParameters_Port
///
/// \descr Stub used to simulate the behaviour of Rte_Read_CtrlDcm_StatusParameters_Port
///
/// \param   ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlDcm_StatusParameters_Port(tsRte_CtrlDcmStatusParams* ppara1)
{
  *ppara1 = Rte_Read_CtrlDcm_StatusParameters_Port_Param1;
  Rte_Read_CtrlDcm_StatusParameters_Port_HitCount++;
  return Rte_Read_CtrlDcm_StatusParameters_Port_RetVal;

}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_SysMon_VehicleSpeed
///
/// \descr Stub used to simulate the behaviour ofRte_Read_SysMon_VehicleSpeed
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

//-----------------------------------------------------------------------------
/// \brief Rte_Read_SysMon_VehNetState
///
/// \descr Stub used to simulate the behaviour of Rte_Read_SysMon_VehNetState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_VehNetState(tsRte_SysMon_VehNetState* ppara1)
{
  *ppara1 = Rte_Read_SysMon_VehNetState_Param1;
  Rte_Read_SysMon_VehNetState_HitCount++;
  return Rte_Read_SysMon_VehNetState_RetVal;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CodM_Pitch_Para
///
/// \descr Stub used to simulate the behaviour of  Rte_Read_CodM_Pitch_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_CodM_Pitch_Para(tsRteCodingParameters* ppara1)
{
  Rte_Read_CodM_Pitch_Para_Param1.eCodingState = Coding_State;
  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;

  *ppara1 = Rte_Read_CodM_Pitch_Para_Param1;
  Rte_Read_CodM_Pitch_Para_HitCount++;
  return  Rte_Read_CodM_Pitch_Para_RetVal;

}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_IoHwAb_GetSens_Raw
///
/// \descr Stub used to simulate the behaviour of Rte_Read_IoHwAb_GetSens_Raw
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------

Std_ReturnType  Rte_Read_IoHwAb_GetSens_Raw(tsRte_SensorRaw* ppara1)
{
  *ppara1 = Rte_Read_IoHwAb_GetSens_Raw_Param1;
  Rte_Read_IoHwAb_GetSens_Raw_HitCount++;
  return Rte_Read_IoHwAb_GetSens_Raw_RetVal;

}
//-----------------------------------------------------------------------------
/// \brief Rte_Read_IoHwAb_GetSens_Balanced
///
/// \descr Stub used to simulate the behaviour of Rte_Read_IoHwAb_GetSens_Balanced
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------

Std_ReturnType  Rte_Read_IoHwAb_GetSens_Balanced(tsRte_SensorBalance* ppara1)
{
  *ppara1 = Rte_Read_IoHwAb_GetSens_Balanced_Param1;
  Rte_Read_IoHwAb_GetSens_Balanced_HitCount++;
  return Rte_Read_IoHwAb_GetSens_Balanced_RetVal;
}
//-----------------------------------------------------------------------------
/// \brief  Rte_Read_IoHwAb_VCCX1Voltage
///
/// \descr Stub used to simulate the behaviour of  Rte_Read_IoHwAb_VCCX1Voltage
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_IoHwAb_VCCX1Voltage(tiu16Voltage_mV* ppara1)
{
  *ppara1 = Rte_Read_IoHwAb_VCCX1Voltage_Param1;
  Rte_Read_IoHwAb_VCCX1Voltage_HitCount++;
  return Rte_Read_IoHwAb_VCCX1Voltage_RetVal;
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
//-----------------------------------------------------------------------------
/// \brief  Dem_SetEventStatus
///
/// \descr  Stub function created to simulate the behaviour of Dem_SetEventStatus function
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
  return Dem_SetEventStatus_RetVal;
}

