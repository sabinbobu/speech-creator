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

uint16                          Order1FilterGetCoef_Param1;
uint16                          Order1FilterGetCoef_Param2;
ORDER1_Filter                   Order1Filter_Param1;
sint16                          Order1Filter_Param2;
uint16                          Order1Filter_Param3;
ORDER1_Filter                   Order1FilterValue_Param1;
ORDER1_Filter                   Order1FilterInit_Param1;
sint16                          Order1FilterInit_Param2;

tsRte_SigPrep_VehiclePitchAngle Rte_Read_SigPrep_VehiclePitchAngle_Param1;
tsRte_SigPrep_DynamicSigs       Rte_Read_SigPrep_DynamicSigs_Param1;
tAvac_Pitch                     Rte_Read_Pitch_Angle_Param1;
tsRte_SysMon_VehicleSpeed       Rte_Read_SysMon_VehicleSpeed_Param1;
tsRte_SysMon_VehNetState        Rte_Read_SysMon_VehNetState_Param1;
tsPositionOut                   Rte_Write_ppsAvacOut_Param1;

sint16                          UTIL_ABS_Param1;

sint16                          AvacUtil_SignalLimiter_Param1;
sint16                          AvacUtil_SignalLimiter_Param2;
sint16                          AvacUtil_SignalLimiter_Param3;
sint16                          AvacUtil_RateLimiter_Param1;
sint16                          AvacUtil_RateLimiter_Param2;
sint16                          AvacUtil_RateLimiter_Param3;
sint16                          AvacUtil_RateLimiter_Param4;

uint16          Dem_SetEventStatus_Param1;
uint8           Dem_SetEventStatus_Param2;

tsRteCodingParameters Rte_Read_CodM_CtrlStp_Para_Param1;

uint16 Order1FilterGetCoef_Param1;
uint16 Order1FilterGetCoef_Param2;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

Std_ReturnType UTIL_ABS_RetVal;
sint16         Order1FilterValue_RetVal;
sint16         AvacUtil_SignalLimiter_RetVal;

Std_ReturnType Rte_Read_Pitch_Angle_RetVal;
Std_ReturnType Rte_Read_SysMon_VehicleSpeed_RetVal;
Std_ReturnType Rte_Read_SysMon_VehNetState_RetVal;
Std_ReturnType Rte_Write_ppsAvacOut_RetVal;
Std_ReturnType Rte_Read_CodM_CtrlStp_Para_RetVal;
Std_ReturnType Order1FilterGetCoef_RetVal;


//=============================================================================
// Stub function hit count variables
//=============================================================================

uint8 Order1FilterGetCoef_HitCount;
uint8 Order1Filter_HitCount;
uint8 Order1FilterValue_HitCount;
uint8 Order1FilterInit_HitCount;
uint8 Rte_Read_Pitch_Angle_HitCount;
uint8 Rte_Read_SigPrep_VehiclePitchAngle_HitCount;
uint8 Rte_Read_SigPrep_VehicleSpeed_HitCount;
uint8 Rte_Read_SigPrep_DynamicSigs_HitCount;
uint8 Rte_Write_ppsAvacOut_HitCount;
uint8 Rte_Read_SysMon_VehicleSpeed_HitCount;
uint8 Rte_Read_SysMon_VehNetState_HitCount;
uint8 Rte_Write_ppsAvacOut_HitCount;
uint8 UTIL_ABS_HitCount;
uint8 Dem_SetEventStatus_HitCount;
uint8 Rte_Read_CodM_CtrlStp_Para_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief Order1FilterGetCoef
///
/// \descr Stub function for Order1FilterGetCoef
///
/// \param  unSamplimgTime
/// \param  unFilterTime
///
/// \return 
//-----------------------------------------------------------------------------
uint16 Order1FilterGetCoef(const uint16 unSamplimgTime, const uint16 unFilterTime)
{
  Order1FilterGetCoef_Param1 = unSamplimgTime;
  Order1FilterGetCoef_Param2 = unFilterTime;

  Order1FilterGetCoef_HitCount++;

  return Order1FilterGetCoef_RetVal;
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
/// \brief Rte_Write_ppsAvacOut
///
/// \descr Stub function for Rte_Write_ppsAvacOut
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_ppsAvacOut(tsPositionOut* ppara1)
{
  Rte_Write_ppsAvacOut_Param1 = *ppara1;
  Rte_Write_ppsAvacOut_HitCount++;
  return Rte_Write_ppsAvacOut_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_SysMon_VehNetState
///
/// \descr Stub function for Rte_Read_SysMon_VehNetState
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
/// \brief Rte_Read_Pitch_Angle
///
/// \descr Stub function for Rte_Write_ppsAvacOut
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_Pitch_Angle(tAvac_Pitch* ppara1)
{
  *ppara1 = Rte_Read_Pitch_Angle_Param1;
  Rte_Read_Pitch_Angle_HitCount++;
  return Rte_Read_Pitch_Angle_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Order1Filter
///
/// \descr Stub function for Order1Filter
///
/// \param  *ppara1
/// \param  ppara2
/// \param  ppara3
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Order1Filter(ORDER1_Filter* const ppara1, const sint16 ppara2, const uint16 ppara3)
{
  Order1Filter_Param1 = *ppara1;
  Order1Filter_Param2 = ppara2;
  Order1Filter_Param3 = ppara3;
  Order1Filter_HitCount++;

  return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief Order1FilterValue
///
/// \descr Stub function for Order1FilterValue
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Order1FilterValue(const ORDER1_Filter* const ppara1)
{
  Order1FilterValue_Param1 = *ppara1;
  Order1FilterValue_HitCount++;

  return Order1FilterValue_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Order1FilterInit
///
/// \descr Stub function for Order1FilterInit
///
/// \param  *ppara1
/// \param  ppara2
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Order1FilterInit(ORDER1_Filter* const ppara1, const sint16 ppara2)
{
  Order1FilterInit_Param1 = *ppara1;
  Order1FilterInit_Param2 = ppara2;
  Order1FilterInit_HitCount++;

  return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_SigPrep_VehiclePitchAngle
///
/// \descr Stub function for Rte_Read_SigPrep_VehiclePitchAngle
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_VehiclePitchAngle(tsRte_SigPrep_VehiclePitchAngle* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_VehiclePitchAngle_Param1;
  Rte_Read_SigPrep_VehiclePitchAngle_HitCount++;
  return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_SigPrep_DynamicSigs
///
/// \descr Stub function for Rte_Read_SigPrep_DynamicSigs
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_DynamicSigs(tsRte_SigPrep_DynamicSigs* ppara1)
{
  *ppara1 = Rte_Read_SigPrep_DynamicSigs_Param1;
  Rte_Read_SigPrep_DynamicSigs_HitCount++;
  return E_OK;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CodM_CtrlStp_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CodM_CtrlStp_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CodM_CtrlStp_Para(tsRteCodingParameters* ppara1)
{
  *ppara1 = Rte_Read_CodM_CtrlStp_Para_Param1;
  Rte_Read_CodM_CtrlStp_Para_HitCount++;
  return Rte_Read_CodM_CtrlStp_Para_RetVal;
}

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
