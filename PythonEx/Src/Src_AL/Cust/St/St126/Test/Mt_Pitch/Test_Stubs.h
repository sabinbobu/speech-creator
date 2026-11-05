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


#include <RteCommonTypes.h>
#include <Nvm.h>
#include <CodM_Para.h>

//=============================================================================
// Typedef
//=============================================================================

//=============================================================================
// Stub function declarations
//=============================================================================


Std_ReturnType     Rte_Write_Pitch_PlausState(teRte_HlsSensorState* ppara1);
Std_ReturnType     Rte_Write_Pitch_Angle(tPitch0* ppara1);
Std_ReturnType     Rte_Read_CtrlStp_Validation_Port(tsRte_CtrlStpValidation* ppara1);
Std_ReturnType     Rte_Read_SysMon_VehicleSpeed(tsRte_SysMon_VehicleSpeed* ppara1);
Std_ReturnType     Rte_Read_SysMon_VehNetState(tsRte_SysMon_VehNetState* ppara1);
Std_ReturnType     Rte_Read_CodM_Pitch_Para(tsRteCodingParameters* ppara1);
Std_ReturnType     Rte_Read_IoHwAb_GetSens_Raw(tsRte_SensorRaw* ppara1);
Std_ReturnType     Rte_Read_IoHwAb_GetSens_Balanced(tsRte_SensorBalance* ppara1);
Std_ReturnType     Rte_Read_IoHwAb_VCCX1Voltage(tiu16Voltage_mV* ppara1);
Std_ReturnType     Rte_Read_CtrlDcm_StatusParameters_Port(tsRte_CtrlDcmStatusParams* ppara1);
uint32             LPTMR0_GetTimeElapsed(const uint32 ulStartValue);
void               Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus);
Std_ReturnType     NvM_WriteBlock(NvM_BlockIdType BlockId, void* NvM_SrcPtr);
Std_ReturnType     UTIL_ABS(const sint16 ppara1);


//=============================================================================
// Stub function parameter stubs
//=============================================================================

extern tNvmPara_CodingArea     Coding_Dummy;
extern tParaFct0_Cmd           Coding_State;

extern teRte_HlsSensorState          Rte_Write_Pitch_PlausState_Param1;
extern tPitch0                       Rte_Write_Pitch_Angle_Param1;
extern tsRte_CtrlStpValidation       Rte_Read_CtrlStp_Validation_Port_Param1;
extern tsRte_SysMon_VehicleSpeed     Rte_Read_SysMon_VehicleSpeed_Param1;
extern tsRte_SysMon_VehNetState      Rte_Read_SysMon_VehNetState_Param1;
extern tsRteCodingParameters         Rte_Read_CodM_Pitch_Para_Param1;
extern tsRte_SensorRaw               Rte_Read_IoHwAb_GetSens_Raw_Param1;
extern tsRte_SensorBalance           Rte_Read_IoHwAb_GetSens_Balanced_Param1;
extern tsRte_CtrlDcmStatusParams     Rte_Read_CtrlDcm_StatusParameters_Port_Param1;
extern tiu16Voltage_mV               Rte_Read_IoHwAb_VCCX1Voltage_Param1;
extern uint32                        LPTMR0_GetTimeElapsed_Param1;
extern uint16                        Dem_SetEventStatus_Param1;
extern uint8                         Dem_SetEventStatus_Param2;
extern NvM_BlockIdType               NvM_WriteBlock_Param1;
extern void* NvM_WriteBlock_Param2;
extern sint16                        UTIL_ABS_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

extern Std_ReturnType   Rte_Write_Pitch_PlausState_RetVal;
extern Std_ReturnType   Rte_Write_Pitch_Angle_RetVal;
extern Std_ReturnType   Rte_Read_CtrlStp_Validation_Port_RetVal;
extern Std_ReturnType   Rte_Read_SysMon_VehicleSpeed_RetVal;
extern Std_ReturnType   Rte_Read_SysMon_VehNetState_RetVal;
extern Std_ReturnType   Rte_Read_CodM_Pitch_Para_RetVal;
extern Std_ReturnType   Rte_Read_IoHwAb_GetSens_Raw_RetVal;
extern Std_ReturnType   Rte_Read_IoHwAb_GetSens_Balanced_RetVal;
extern Std_ReturnType   Rte_Read_IoHwAb_VCCX1Voltage_RetVal;
extern Std_ReturnType   Rte_Read_CtrlDcm_StatusParameters_Port_RetVal;
extern uint32           LPTMR0_GetTimeElapsed_RetVal;
extern uint16           Dem_SetEventStatus_RetVal;
extern uint8            Cod_Pitch_ErrCntMax_RetVal;
extern uint8            Pitch_ErrCntInc_RetVal;
extern uint8            Pitch_ErrCntDec_RetVal;
extern Std_ReturnType   NvM_WriteBlock_RetVal;
extern Std_ReturnType   UTIL_ABS_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

extern uint8  Rte_Write_Pitch_PlausState_HitCount;
extern uint8  Rte_Write_Pitch_Angle_HitCount;
extern uint8  Rte_Read_CtrlDcm_StatusParameters_Port_HitCount;
extern uint8  Rte_Read_CtrlStp_Validation_Port_HitCount;
extern uint8  Rte_Read_SysMon_VehicleSpeed_HitCount;
extern uint8  Rte_Read_SysMon_VehNetState_HitCount;
extern uint8  Rte_Read_CodM_Pitch_Para_HitCount;
extern uint8  Rte_Read_IoHwAb_GetSens_Raw_HitCount;
extern uint8  Rte_Read_IoHwAb_GetSens_Balanced_HitCount;
extern uint8  Rte_Read_IoHwAb_VCCX1Voltage_HitCount;
extern uint8  Rte_Read_SysMon_VehNetStat_HitCount;
extern uint8  LPTMR0_GetTimeElapsed_HitCount;
extern uint8  Dem_SetEventStatus_HitCount;
extern uint8  NvM_WriteBlock_HitCount;
extern uint8  UTIL_ABS_HitCount;


#endif // TEST_STUBS_2023_08_25_H_
