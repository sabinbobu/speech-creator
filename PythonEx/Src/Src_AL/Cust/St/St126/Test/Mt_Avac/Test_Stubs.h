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
/// \file  Test_Stubs.h
///
/// \brief Stub functions prototypes for access to software modules excluded from test
///        including stub parameters
///
//-----------------------------------------------------------------------------
#ifndef TEST_STUBS_2023_08_25_H_
#define TEST_STUBS_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================

#include <AL_Helper.h>

//#include "Test.h"
#include <Rte/RteCommonTypes.h>
#include <Swc\AfsMaster\Avac\AvacTypes.h>

//=============================================================================
// Typedef
//=============================================================================

typedef sint32 ORDER1_Filter;

//=============================================================================
// Stub function declarations
//=============================================================================

Std_ReturnType Order1Filter(ORDER1_Filter* const ppara1, const sint16 ppara2, const uint16 ppara3);
Std_ReturnType Order1FilterValue(const ORDER1_Filter* const ppara1);
Std_ReturnType Order1FilterInit(ORDER1_Filter* const ppara1, const sint16 ppara2);

Std_ReturnType Rte_Read_SigPrep_VehiclePitchAngle(tsRte_SigPrep_VehiclePitchAngle* ppara1);
Std_ReturnType Rte_Read_SigPrep_DynamicSigs(tsRte_SigPrep_DynamicSigs* ppara1);
Std_ReturnType Rte_Read_Pitch_Angle(tAvac_Pitch* ppara1);
Std_ReturnType Rte_Read_SysMon_VehicleSpeed(tsRte_SysMon_VehicleSpeed* ppara1);
Std_ReturnType Rte_Read_SysMon_VehNetState(tsRte_SysMon_VehNetState* ppara1);
Std_ReturnType Rte_Write_ppsAvacOut(tsPositionOut* ppara1);
Std_ReturnType Rte_Read_CodM_CtrlStp_Para(tsRteCodingParameters* ppara1);

Std_ReturnType UTIL_ABS(const sint16 ppara1);
uint16         Order1FilterGetCoef(const uint16 unSamplimgTime, const uint16 unFilterTime);
void           Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus);

//=============================================================================
// Stub function parameter stubs
//=============================================================================

extern uint16                          Order1FilterGetCoef_Param1;
extern uint16                          Order1FilterGetCoef_Param2;
extern ORDER1_Filter                   Order1Filter_Param1;
extern sint16                          Order1Filter_Param2;
extern uint16                          Order1Filter_Param3;
extern ORDER1_Filter                   Order1FilterValue_Param1;
extern ORDER1_Filter                   Order1FilterInit_Param1;
extern sint16                          Order1FilterInit_Param2;

extern tsRte_SigPrep_VehiclePitchAngle Rte_Read_SigPrep_VehiclePitchAngle_Param1;
extern tsRte_SigPrep_DynamicSigs       Rte_Read_SigPrep_DynamicSigs_Param1;
extern tAvac_Pitch                     Rte_Read_Pitch_Angle_Param1;
extern tsRte_SysMon_VehicleSpeed       Rte_Read_SysMon_VehicleSpeed_Param1;
extern tsRte_SysMon_VehNetState        Rte_Read_SysMon_VehNetState_Param1;
extern tsPositionOut                   Rte_Write_ppsAvacOut_Param1;

extern sint16                          UTIL_ABS_Param1;
 
extern sint16                          AvacUtil_SignalLimiter_Param1;
extern sint16                          AvacUtil_SignalLimiter_Param2;
extern sint16                          AvacUtil_SignalLimiter_Param3;
extern sint16                          AvacUtil_RateLimiter_Param1;
extern sint16                          AvacUtil_RateLimiter_Param2;
extern sint16                          AvacUtil_RateLimiter_Param3;
extern sint16                          AvacUtil_RateLimiter_Param4;

extern uint16          Dem_SetEventStatus_Param1;
extern uint8           Dem_SetEventStatus_Param2;
 
extern tsRteCodingParameters Rte_Read_CodM_CtrlStp_Para_Param1;

extern uint16 Order1FilterGetCoef_Param1;
extern uint16 Order1FilterGetCoef_Param2;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

extern Std_ReturnType UTIL_ABS_RetVal;
extern sint16         Order1FilterValue_RetVal;
extern sint16         AvacUtil_SignalLimiter_RetVal;

extern Std_ReturnType Rte_Read_Pitch_Angle_RetVal;
extern Std_ReturnType Rte_Read_SysMon_VehicleSpeed_RetVal;
extern Std_ReturnType Rte_Read_SysMon_VehNetState_RetVal;
extern Std_ReturnType Rte_Write_ppsAvacOut_RetVal;
extern Std_ReturnType Rte_Read_CodM_CtrlStp_Para_RetVal;
extern Std_ReturnType Order1FilterGetCoef_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

extern uint8 Order1FilterGetCoef_HitCount;
extern uint8 Order1Filter_HitCount;
extern uint8 Order1FilterValue_HitCount;
extern uint8 Order1FilterInit_HitCount;
extern uint8 Rte_Read_Pitch_Angle_HitCount;
extern uint8 Rte_Read_SigPrep_VehiclePitchAngle_HitCount;
extern uint8 Rte_Read_SigPrep_VehicleSpeed_HitCount;
extern uint8 Rte_Read_SigPrep_DynamicSigs_HitCount;
extern uint8 Rte_Write_ppsAvacOut_HitCount;
extern uint8 Rte_Read_SysMon_VehicleSpeed_HitCount;
extern uint8 Rte_Read_SysMon_VehNetState_HitCount;
extern uint8 Rte_Write_ppsAvacOut_HitCount;
extern uint8 UTIL_ABS_HitCount;
extern uint8 Dem_SetEventStatus_HitCount;
extern uint8 Rte_Read_CodM_CtrlStp_Para_HitCount;

#endif // TEST_STUBS_2023_08_25_H_
