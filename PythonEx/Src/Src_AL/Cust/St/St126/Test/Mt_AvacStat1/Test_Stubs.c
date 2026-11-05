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

uint16                    Dem_SetEventStatus_Param1;
uint8                     Dem_SetEventStatus_Param2;
NvM_BlockIdType           NvM_WriteBlock_Param1;
void*                     NvM_WriteBlock_Param2;
tsRte_SigPrep_DynamicSigs Rte_Read_SigPrep_DynamicSigs_Param1;
tsRte_CtrlDcmStatusParams Rte_Read_CtrlDcm_StatusParameters_Port_Param1;
tsRte_SysMon_VehicleSpeed Rte_Read_SysMon_VehicleSpeed_Param1;
tPitch0                   Rte_Read_Pitch_Angle_Param1;
tsRteCodingParameters     Rte_Read_CodM_Pitch_Para_Param1;
teRte_DcmSpeedMode        Rte_Write_AvacStat1_SpeedMode_Param1;
tPositionOut              Rte_Write_ppsAvacStat1Out_Port_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

Std_ReturnType  NvM_WriteBlock_RetVal;
Std_ReturnType  Rte_Read_SigPrep_DynamicSigs_RetVal;
Std_ReturnType  Rte_Read_CtrlDcm_StatusParameters_Port_RetVal;
Std_ReturnType  Rte_Read_SysMon_VehicleSpeed_RetVal;
Std_ReturnType  Rte_Read_Pitch_Angle_RetVal;
Std_ReturnType  Rte_Read_CodM_Pitch_Para_RetVal;
Std_ReturnType  Rte_Write_AvacStat1_SpeedMode_RetVal;
Std_ReturnType  Rte_Write_ppsAvacStat1Out_Port_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

uint8 Dem_SetEventStatus_HitCount;
uint8 NvM_WriteBlock_HitCount;
uint8 Rte_Read_SigPrep_DynamicSigs_HitCount;
uint8 Rte_Read_CtrlDcm_StatusParameters_Port_HitCount;
uint8 Rte_Read_SysMon_VehicleSpeed_HitCount;
uint8 Rte_Read_Pitch_Angle_HitCount;
uint8 Rte_Read_CodM_Pitch_Para_HitCount;
uint8 Rte_Write_AvacStat1_SpeedMode_HitCount;
uint8 Rte_Write_ppsAvacStat1Out_Port_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief Rte_Write_ppsAvacStat1Out_Port
///
/// \descr Stub function for Rte_Write_ppsAvacStat1Out_Port
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_ppsAvacStat1Out_Port(const tPositionOut* ppara1)
{
  Rte_Write_ppsAvacStat1Out_Port_Param1 = *ppara1;
  Rte_Write_ppsAvacStat1Out_Port_HitCount++;
  return Rte_Write_ppsAvacStat1Out_Port_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Write_AvacStat1_SpeedMode
///
/// \descr Stub function for Rte_Write_AvacStat1_SpeedMode
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_AvacStat1_SpeedMode(const teRte_DcmSpeedMode* ppara1)
{
  Rte_Write_AvacStat1_SpeedMode_Param1 = *ppara1;
  Rte_Write_AvacStat1_SpeedMode_HitCount++;
  return Rte_Write_AvacStat1_SpeedMode_RetVal;
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
/// \brief Rte_Read_SigPrep_DynamicSigs
///
/// \descr Stub function for Rte_Read_SigPrep_DynamicSigs
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_DynamicSigs(tsRte_SigPrep_DynamicSigs* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_DynamicSigs_Param1;
  Rte_Read_SigPrep_DynamicSigs_HitCount++;
  return Rte_Read_SigPrep_DynamicSigs_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlDcm_StatusParameters_Port
///
/// \descr Stub used to simulate the behaviour of Rte_Read_CtrlDcm_StatusParameters_Port
///
/// \param   *ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlDcm_StatusParameters_Port(tsRte_CtrlDcmStatusParams *ppara1)
{
  *ppara1 = Rte_Read_CtrlDcm_StatusParameters_Port_Param1;
  Rte_Read_CtrlDcm_StatusParameters_Port_HitCount++;
  return Rte_Read_CtrlDcm_StatusParameters_Port_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_SysMon_VehicleSpeed
///
/// \descr Stub function for Rte_Read_SysMon_VehicleSpeed
///
/// \param  *ppara1
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
/// \brief Rte_Read_Pitch_Angle
///
/// \descr Stub function for Rte_Read_Pitch_Angle
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Pitch_Angle(tPitch0* ppara1)
{
  *ppara1 = Rte_Read_Pitch_Angle_Param1;
  Rte_Read_Pitch_Angle_HitCount++;
  return Rte_Read_Pitch_Angle_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CodM_Pitch_Para
///
/// \descr Stub used to simulate the behaviour of  Rte_Read_CodM_Pitch_Para
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_CodM_Pitch_Para(tsRteCodingParameters *ppara1)
{
  *ppara1 = Rte_Read_CodM_Pitch_Para_Param1;
  Rte_Read_CodM_Pitch_Para_HitCount++;
  return  Rte_Read_CodM_Pitch_Para_RetVal;
}
