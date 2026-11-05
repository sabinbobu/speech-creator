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
#include <Fee_TargetTypes.h>
#include <MemIf_Types.h>
#include <SysCrc_TargetTypes.h>
//=============================================================================
// Typedef
//=============================================================================

//=============================================================================
// Stub function declarations
//=============================================================================

Std_ReturnType Rte_Write_CodM_Anima_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_IoHwAbUser_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_FctR_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_SysMon_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_CddSwi_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_CddLed_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_SysVolt_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_CtrlFan_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_Rsens_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_CtrlLed_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_AppM_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_CddBoost_Para(tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Write_CodM_SigPrep_Para(const tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Read_CodM_Err_Para(const tsRteCodingParameters* ppara1);
void           SysCrc_RomSegs_GetCalibState(tsSysCrc_CalibGetStatus *psCalibState);

//=============================================================================
// Stub function parameter stubs
//=============================================================================

extern tsRteCodingParameters Rte_Write_CodM_Anima_Para_Param1;
extern tsRteCodingParameters Rte_Write_CodM_IoHwAbUser_Para_Param1;
extern tsRteCodingParameters Rte_Write_CodM_FctR_Para_Param1;
extern tsRteCodingParameters Rte_Write_CodM_SysMon_Para_Param1;
extern tsRteCodingParameters Rte_Write_CodM_CddSwi_Para_Param1;
extern tsRteCodingParameters Rte_Write_CodM_CddLed_Para_Param1;
extern tsRteCodingParameters Rte_Write_CodM_SysVolt_Para_Param1;
extern tsRteCodingParameters Rte_Write_CodM_CtrlFan_Para_Param1;
extern tsRteCodingParameters Rte_Write_CodM_Rsens_Para_Param1;
extern tsRteCodingParameters Rte_Write_CodM_CtrlLed_Para_Param1;
extern tsRteCodingParameters Rte_Write_CodM_AppM_Para_Param1;
extern tsRteCodingParameters Rte_Write_CodM_Dbl_Para_Param1;
extern tsRteCodingParameters Rte_Write_CodM_CddMlc_Para_Param1;
extern tsRteCodingParameters Rte_Write_CodM_CtrlPxl_Para_Param1;
extern tsRteCodingParameters Rte_Write_CodM_CddStp_Para_Param1;
extern tsRteCodingParameters Rte_Write_CodM_CtrlStp_Para_Param1;
extern tsRteCodingParameters Rte_Write_CodM_Adb_Mxb_Para_Param1;
extern tsRteCodingParameters Rte_Write_CodM_Adb_Pxa_Para_Param1;
extern tsRteCodingParameters Rte_Write_CodM_Pitch_Para_Param1;
extern tsRteCodingParameters Rte_Write_CodM_CddBoost_Para_Param1;
extern tsRteCodingParameters Rte_Write_CodM_SigPrep_Para_Param1;
extern tsRteCodingParameters Rte_Write_CodM_Err_Para_Param1;
extern tsSysCrc_CalibGetStatus SysCrc_RomSegs_GetCalibState_Param1;
extern boolean               Dem_Set_Init_Window_Param1;
extern uint16                Dem_SetEventStatus_Param1;
extern uint8                 Dem_SetEventStatus_Param2;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

extern boolean CddEft_DataValid_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

extern uint8 Rte_Write_CodM_Anima_Para_HitCount;
extern uint8 Rte_Write_CodM_IoHwAbUser_Para_HitCount;
extern uint8 Rte_Write_CodM_FctR_Para_HitCount;
extern uint8 Rte_Write_CodM_SysMon_Para_HitCount;
extern uint8 Rte_Write_CodM_CddSwi_Para_HitCount;
extern uint8 Rte_Write_CodM_CddLed_Para_HitCount;
extern uint8 Rte_Write_CodM_SysVolt_Para_HitCount;
extern uint8 Rte_Write_CodM_CtrlFan_Para_HitCount;
extern uint8 Rte_Write_CodM_Rsens_Para_HitCount;
extern uint8 Rte_Write_CodM_CtrlLed_Para_HitCount;
extern uint8 Rte_Write_CodM_AppM_Para_HitCount;
extern uint8 Rte_Write_CodM_CddBoost_Para_HitCount;
extern uint8 Rte_Write_CodM_Dbl_Para_HitCount;
extern uint8 Rte_Write_CodM_CddMlc_Para_HitCount;
extern uint8 Rte_Write_CodM_CtrlPxl_Para_HitCount;
extern uint8 Rte_Write_CodM_CddStp_Para_HitCount;
extern uint8 Rte_Write_CodM_CtrlStp_Para_HitCount;
extern uint8 Rte_Write_CodM_Adb_Mxb_Para_HitCount;
extern uint8 Rte_Write_CodM_Adb_Pxa_Para_HitCount;
extern uint8 Rte_Write_CodM_Pitch_Para_HitCount;
extern uint8 Rte_Write_CodM_SigPrep_Para_HitCount;
extern uint8 Rte_Write_CodM_Err_Para_HitCount;
extern uint8 SysCrc_RomSegs_GetCalibState_HitCount;
extern uint8 CddEft_DataValid_Hit_Count;
extern uint8 Dem_SetEventStatus_HitCount;
extern uint8 Dem_Set_Init_Window_HitCount;


#endif // TEST_STUBS_2023_08_25_H_
