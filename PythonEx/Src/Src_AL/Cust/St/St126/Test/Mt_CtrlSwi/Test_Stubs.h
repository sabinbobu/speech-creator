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
#include <Swc/Ctrl/Switch/CtrlSwi_Types.h>
#include <Swc/Ctrl/Switch/CtrlSwi_Cfg.h>
#include <CodM_Types.h>
#include <Bsw/NvM/NvM_Para.h>

//=============================================================================
// Stub function declarations
//=============================================================================
Std_ReturnType               Rte_Write_CodM_CtrlFan_Para(const tsRteCodingParameters *ppara1);
Std_ReturnType               Rte_Write_CtrlSwi_TgtValue_Fan1(const uint16 *ppara1);
Std_ReturnType               Rte_Write_CtrlSwi_TgtValue_Fan2(const uint16 *ppara1);
Std_ReturnType               Rte_Write_CtrlSwi_HssStatus(const tRteCtrlSwi_ErrorFlags *ppara1);
Std_ReturnType               Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite(const teRte_SateliteStatus* ppara1);
Std_ReturnType               Rte_Write_CtrlSwi_Hss3StatusErr(const tsRte_Hss3Status* ppara1);
Std_ReturnType               Rte_Read_SysVolt_FanVoltRng0_sVoltRng(teRte_SysVolt_Results *ppara1);
Std_ReturnType               Rte_Read_CddSwi_SwitchStatus(tsRte_HssStatus *ppara1);
Std_ReturnType               Rte_Read_SigPrep_ElecSupState(tsRte_SigPrep_ElecSupState *ppara1);
Std_ReturnType               Rte_Read_CddSwi_ScrollingOn_Stat(tScrollingPresent_Stat* ppara1);
Std_ReturnType               Rte_Read_SysMon_StdLgtTi_Req(tsRte_SysMonLgtTiReq* ppara1);
Std_ReturnType               Rte_Read_Diag_TiScrollingTakeOverp(boolean* ppara1);
Std_ReturnType               Rte_Read_CpmHssTarget0_sSetting(tsRteHssTarget* ppara1);
Std_ReturnType               Rte_Read_Cpm_CtrlSwi_HSS3Target(tsRte_CpmHSS3Duty* ppara1);
Std_ReturnType               Rte_Read_AnimaScrollingActivation(tsRte_TgtAniArrScr* ppara1);
uint32                       LPTMR0_GetTimeElapsed(const uint32 ulStartValue);
void                         Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus);

//=============================================================================
// Stub function parameter stubs
//=============================================================================
tsRteCodingParameters        Rte_Write_CodM_CtrlFan_Para_Param1;
uint16                       Rte_Write_CtrlSwi_TgtValue_Fan1_Param1;
uint16                       Rte_Write_CtrlSwi_TgtValue_Fan2_Param1;
tRteCtrlSwi_ErrorFlags       Rte_Write_CtrlSwi_HssStatus_Param1;
tisHssStatusError            Rte_Write_CtrlSwi_StatusErr_Param1;
uint16                       Rte_Write_CtrlSwi_TgtValue_Fan1_Param1;
tRteSwitchTgtVal             Rte_Write_CtrlSwi_TgtValue_SMRGB_Param1;
teRte_SateliteStatus         Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite_Param1;
tsRte_Hss3Status             Rte_Write_CtrlSwi_Hss3StatusErr_Param1;
tsRteCodingParameters        Rte_Read_CodM_CtrlFan_Para_Param1;
teRte_SysVolt_Results        Rte_Read_SysVolt_FanVoltRng0_sVoltRng_Param1;
tsRte_HssStatus              Rte_Read_CddSwi_SwitchStatus_Param1;
tsRte_SigPrep_ElecSupState   Rte_Read_SigPrep_ElecSupState_Param1;
tScrollingPresent_Stat       Rte_Read_CddSwi_ScrollingOn_Stat_Param1;
tsRte_SysMonLgtTiReq         Rte_Read_SysMon_StdLgtTi_Req_Param1;
boolean                      Rte_Read_Diag_TiScrollingTakeOver_Param1;
tsRteHssTarget               Rte_Read_CpmHssTarget0_sSetting_Param1;
tsRte_CpmHSS3Duty            Rte_Read_Cpm_CtrlSwi_HSS3Target_Param1;
uint32                       LPTMR0_GetTimeElapsed_Param1;
uint16                       Dem_SetEventStatus_Param1;
uint8	                       Dem_SetEventStatus_Param2;
tsRte_TgtAniArrScr           Rte_Read_AnimaScrollingActivation_Param1;
teRte_ScrollingTgt           Rte_Read_Diag_Scrolling_TgtValue_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
Std_ReturnType               Rte_Write_CodM_CtrlFan_Para_RetVal;
Std_ReturnType               Rte_Write_CtrlSwi_TgtValue_Fan1_RetVal;
Std_ReturnType               Rte_Write_CtrlSwi_TgtValue_Fan2_RetVal;
Std_ReturnType               Rte_Write_CtrlSwi_HssStatus_RetVal;
Std_ReturnType               Rte_Write_CtrlSwi_StatusErr_RetVal;
Std_ReturnType               Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite_RetVal;
Std_ReturnType               Rte_Write_CtrlSwi_Hss3StatusErr_RetVal;
Std_ReturnType               Rte_Read_CodM_CtrlFan_Para_RetVal;
Std_ReturnType               Rte_Read_SysVolt_FanVoltRng0_sVoltRng_RetVal;
Std_ReturnType               Rte_Read_CddSwi_SwitchStatus_RetVal;
Std_ReturnType               Rte_Read_SigPrep_ElecSupState_RetVal;
Std_ReturnType               Rte_Read_CddSwi_ScrollingOn_Stat_RetVal;
Std_ReturnType               Rte_Read_SysMon_StdLgtTi_Req_RetVal;
Std_ReturnType               Rte_Read_Diag_TiScrollingTakeOver_RetVal;
Std_ReturnType               Rte_Read_CpmHssTarget0_sSetting_RetVal;
Std_ReturnType               Rte_Read_Cpm_CtrlSwi_HSS3Target_RetVal;
Std_ReturnType               Rte_Read_AnimaScrollingActivation_RetVal;
Std_ReturnType               Rte_Read_Diag_Scrolling_TgtValue_RetVal;
uint32                       LPTMR0_GetTimeElapsed_RetVal;
uint8                        Dem_SetEventStatus_Retval;
uint8                        CtrlSwi_Get_ETAT_FEE_Ret_Val;
boolean                      CtrlSwi_DataValid_RetVal;
uint8                        Rte_Write_CtrlSwi_TgtValue_SMRGB_RetVal;
uint8                        CtrlSwi_ErrorTimers_RetVal;
boolean                      CtrlSwi_HandleMaturationTime_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
uint8                        Rte_Write_CodM_CtrlFan_Para_HitCount;
uint8                        Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount;
uint8                        Rte_Write_CtrlSwi_TgtValue_Fan2_HitCount;
uint8                        Rte_Write_CtrlSwi_HssStatus_HitCount;
uint8                        Rte_Write_CtrlSwi_TgtValue_Fan1_HitCount;
uint8                        Rte_Write_CtrlSwi_TgtValue_SMRGB_HitCount;
uint8                        Rte_Write_CtrlSwi_StatusErr_HitCount;
uint8                        Rte_Write_CtrlSwi_TgtValue_ScrollingSatelite_HitCount;
uint8                        Rte_Write_CtrlSwi_Hss3StatusErr_HitCount;
uint8                        Rte_Read_CodM_CtrlFan_Para_HitCount;
uint8                        Rte_Read_SysVolt_FanVoltRng0_sVoltRng_HitCount;
uint8                        Rte_Read_CddSwi_SwitchStatus_HitCount;
uint8                        Rte_Read_SigPrep_ElecSupState_HitCount;
uint8                        Rte_Read_CddSwi_ScrollingOn_Stat_HitCount;
uint8                        Rte_Read_SysMon_StdLgtTi_Req_HitCount;
uint8                        Rte_Read_Diag_TiScrollingTakeOver_HitCount;
uint8                        Rte_Read_CpmHssTarget0_sSetting_HitCount;
uint8                        Rte_Read_Cpm_CtrlSwi_HSS3Target_HitCount;
uint8                        LPTMR0_GetTimeElapsed_HitCount;
uint8                        Dem_SetEventStatus_HitCount;
uint8                        CtrlSwi_DataValid_Hit_Count;
uint8                        Rte_Read_AnimaScrollingActivation_Hit_Count;
uint8                        Rte_Read_Diag_Scrolling_TgtValue_HitCount;

#endif // TEST_STUBS_2023_08_25_H_

// EOF