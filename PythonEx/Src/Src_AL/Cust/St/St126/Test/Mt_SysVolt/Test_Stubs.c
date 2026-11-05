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
#include <RteCommonTypes.h>


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

tNvmPara_CodingArea     Coding_Dummy = { 0u };
tParaFct0_Cmd           Coding_State = eParaFct0_CodingDataInvalid;
//=============================================================================
// Stub function parameter stubs
//=============================================================================
uint16                      Dem_SetEventStatus_Param1;
uint8                       Dem_SetEventStatus_Param2;
uint16                      Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;
uint32                      LPTMR0_GetTimeElapsed_Param1;
teRte_SysVolt_Results       Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1;
teRte_SysVolt_Results       Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1;
teRte_SysVolt_Results       Rte_Write_SysVolt_LedVoltRng0_sVoltRng_Param1;
tsRteCodingParameters       Rte_Read_CodM_SysVolt_Para_Param1;
tsRte_SysMon_VehNetState    Rte_Read_SysMon_VehNetState_Param1;
tsRte_SigPrep_ElecSupState  Rte_Read_SigPrep_ElecSupState_Param1;

//=============================================================================
 // Stub function returned value stubs
 //=============================================================================

uint32          LPTMR0_GetTimeElapsed_RetVal;
Std_ReturnType  Rte_Write_SysVolt_LedVoltRng0_sVoltRng_RetVal;
Std_ReturnType  Rte_Read_CodM_SysVolt_Para_RetVal;
Std_ReturnType  Rte_Read_SysMon_VehNetState_RetVal;
Std_ReturnType  Rte_Read_SigPrep_ElecSupState_RetVal;
Std_ReturnType  Rte_Read_CodM_SysVolt_Para_RetVal;



 //=============================================================================
// Stub function hit count variables
//=============================================================================

uint8 Dem_SetEventStatus_HitCount;
uint8 Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount;
uint8 LPTMR0_GetTimeElapsed_HitCount;
uint8 Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount;
uint8 Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount;
uint8 Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount;
uint8 Rte_Read_CodM_SysVolt_Para_HitCount;
uint8 Rte_Read_SysMon_VehNetState_HitCount;
uint8 Rte_Read_SigPrep_ElecSupState_HitCount;


//=============================================================================
// Stub function definitions
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CodM_SysVolt_Para
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CodM_SysVolt_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CodM_SysVolt_Para(tsRteCodingParameters* ppara1)
{
	Rte_Read_CodM_SysVolt_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
	Rte_Read_CodM_SysVolt_Para_Param1.eCodingState = Coding_State;
	*ppara1 = Rte_Read_CodM_SysVolt_Para_Param1;
	Rte_Read_CodM_SysVolt_Para_HitCount++;
	return Rte_Read_CodM_SysVolt_Para_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SigPrep_ElecSupState
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_SigPrep_ElecSupState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SigPrep_ElecSupState(tsRte_SigPrep_ElecSupState* ppara1)
{
	*ppara1 = Rte_Read_SigPrep_ElecSupState_Param1;
	Rte_Read_SigPrep_ElecSupState_HitCount++;
	return Rte_Read_SigPrep_ElecSupState_RetVal;
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
/// \brief  Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT
///
/// \param  Arg1
///
/// \return void
//-----------------------------------------------------------------------------
void Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(uint16* Arg1)
{
	*Arg1 = Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Param1;
	Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT_Hitcount++;
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
	return (LPTMR0_GetTimeElapsed_RetVal);
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SysVolt_FanVoltRng0_sVoltRng
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SysVolt_FanVoltRng0_sVoltRng
///
/// \param  eSetVoltageState
///
/// \return void
//-----------------------------------------------------------------------------
void Rte_Write_SysVolt_FanVoltRng0_sVoltRng(teRte_SysVolt_Results* eSetVoltageState)
{
	Rte_Write_SysVolt_FanVoltRng0_sVoltRng_Param1 = *eSetVoltageState;
	Rte_Write_SysVolt_FanVoltRng0_sVoltRng_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SysVolt_StepperVoltRng0_sVoltRng
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SysVolt_StepperVoltRng0_sVoltRng
///
/// \param  eSetVoltageState
///
/// \return void
//-----------------------------------------------------------------------------
void Rte_Write_SysVolt_StepperVoltRng0_sVoltRng(teRte_SysVolt_Results* eSetVoltageState)
{
	Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_Param1 = *eSetVoltageState;
	Rte_Write_SysVolt_StepperVoltRng0_sVoltRng_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_SysVolt_LedVoltRng0_sVoltRng
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_SysVolt_LedVoltRng0_sVoltRng
///
/// \param  eSetVoltageState
///
/// \return void
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_SysVolt_LedVoltRng0_sVoltRng(const teRte_SysVolt_Results* ppara1)
{
	Rte_Write_SysVolt_LedVoltRng0_sVoltRng_Param1 = *ppara1;
	Rte_Write_SysVolt_LedVoltRng0_sVoltRng_HitCount++;
	return Rte_Write_SysVolt_LedVoltRng0_sVoltRng_RetVal;
}
