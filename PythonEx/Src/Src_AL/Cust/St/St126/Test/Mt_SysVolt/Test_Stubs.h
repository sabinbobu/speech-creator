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
#include <Bsw/Dem/Dem.h>
#include <SysVolt_Cfg.h>
#include <Swc/CodM/CodM_Para.h>
#include <Swc/CodM/CodM_Types.h>
#include <RteCommonTypes.h>
#include <Nvm.h>
#include <CodM_Para.h>
#include <Std_Types.h>


//=============================================================================
// Stub function declarations
//=============================================================================
void           Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(uint16* Arg1);
void           Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus);
uint32         LPTMR0_GetTimeElapsed(const uint32 ulStartValue);
void           Rte_Write_SysVolt_StepperVoltRng0_sVoltRng(teRte_SysVolt_Results* eSetVoltageState);
void           Rte_Write_SysVolt_FanVoltRng0_sVoltRng(teRte_SysVolt_Results* eSetVoltageState);
Std_ReturnType Rte_Write_SysVolt_LedVoltRng0_sVoltRng(const teRte_SysVolt_Results* ppara1);
Std_ReturnType Rte_Read_CodM_SysVolt_Para(tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Read_SysMon_VehNetState(tsRte_SysMon_VehNetState* ppara1);
Std_ReturnType Rte_Read_SigPrep_ElecSupState(tsRte_SigPrep_ElecSupState* ppara1);


//=============================================================================
// Stub function parameter stubs
//=============================================================================
extern uint16                      Dem_SetEventStatus_Param1;
extern uint8                       Dem_SetEventStatus_Param2;
extern uint16                      Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;
extern uint32                      LPTMR0_GetTimeElapsed_Param1;
extern teRte_SysVolt_Results       Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1;
extern teRte_SysVolt_Results       Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1;
extern teRte_SysVolt_Results       Rte_Write_SysVolt_LedVoltRng0_sVoltRng_Param1;
extern tsRteCodingParameters       Rte_Read_CodM_SysVolt_Para_Param1;
extern tsRte_SysMon_VehNetState    Rte_Read_SysMon_VehNetState_Param1;
extern tsRte_SigPrep_ElecSupState  Rte_Read_SigPrep_ElecSupState_Param1;

extern tNvmPara_CodingArea     Coding_Dummy;
extern tParaFct0_Cmd           Coding_State;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
extern uint32          LPTMR0_GetTimeElapsed_RetVal;
extern Std_ReturnType  Rte_Write_SysVolt_LedVoltRng0_sVoltRng_RetVal;
extern Std_ReturnType  Rte_Read_CodM_SysVolt_Para_RetVal;
extern Std_ReturnType  Rte_Read_SysMon_VehNetState_RetVal;
extern Std_ReturnType  Rte_Read_SigPrep_ElecSupState_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
extern uint8 Dem_SetEventStatus_HitCount;
extern uint8 Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount;
extern uint8 LPTMR0_GetTimeElapsed_HitCount;
extern uint8 Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount;
extern uint8 Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount;
extern uint8 Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount;
extern uint8 Rte_Read_CodM_SysVolt_Para_HitCount;
extern uint8 Rte_Read_SysMon_VehNetState_HitCount;
extern uint8 Rte_Read_SigPrep_ElecSupState_HitCount;


#endif // TEST_STUBS_2023_08_25_H_
