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
#include <Std_Types.h>
#include <RteCommonTypes.h>
#include <Bsw/Nvm/NvM_Para.h>
#include "CddLed.h"
#include <../CddBoost/Api/CddBoost.h>
#include <Nvm.h>

//=============================================================================
// Typedef
//=============================================================================

//=============================================================================
// Stub function declarations
//=============================================================================

Std_ReturnType Rte_Read_CddLed_Status(tCddLedStatus* ppara1);
Std_ReturnType Rte_Read_CddLed_LedState(tsRte_LedStates* ppara1);
Std_ReturnType Rte_Read_CddBoost_BoostStatus(tCddBoostStatus* ppara1);
Std_ReturnType Rte_Read_RSens_PcbTemperature(tsRte_PcbTemperatureMsg* ppara1);
Std_ReturnType Rte_Write_StatM_StackUsage(uint8 para1);
Std_ReturnType NvM_WriteBlock(NvM_BlockIdType BlockId, void* NvM_SrcPtr);
Std_ReturnType Rte_Read_RSens_ThermzoneTemperatures(tsRte_NTCTemperature* ppara1);
Std_ReturnType Rte_Read_CddSwi_SwitchStatus(tsRte_HssStatus *ppara1);
Std_ReturnType Rte_Read_ppCddStpActual0_sStpActualValues(tsRte_CddStpActual* ppara1);

//=============================================================================
// Stub function parameter stubs
//=============================================================================

extern tCddLedStatus                    Rte_Read_CddLed_Status_Param1;
extern tsRte_LedStates                  Rte_Read_CddLed_LedState_Param1;
extern tCddBoostStatus                  Rte_Read_CddBoost_BoostStatus_Param1;
extern tsRte_PcbTemperatureMsg          Rte_Read_RSens_PcbTemperature_Param1;
extern uint8                            Rte_Write_StatM_StackUsage_Param1;
extern NvM_BlockIdType                  NvM_WriteBlock_Param1;
extern void*                            NvM_WriteBlock_Param2;
extern tsRte_NTCTemperature             Rte_Read_RSens_ThermzoneTemperatures_Param1;
extern tsRte_HssStatus                  Rte_Read_CddSwi_SwitchStatus_Param1;
extern tsRte_CddStpActual               Rte_Read_ppCddStpActual0_sStpActualValues_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

extern Std_ReturnType Rte_Read_CddLed_Status_Param1_RetVal;
extern Std_ReturnType Rte_Read_CddLed_LedState_Param1_RetVal;
extern Std_ReturnType Rte_Read_CddBoost_BoostStatus_Param1_RetVal;
extern Std_ReturnType Rte_Read_RSens_PcbTemperature_RetVal;
extern Std_ReturnType Rte_Write_StatM_StackUsage_RetVal;
extern Std_ReturnType NvM_WriteBlock_RetVal;
extern Std_ReturnType Rte_Read_RSens_ThermzoneTemperatures_RetVal;
extern Std_ReturnType Rte_Read_CddSwi_SwitchStatus_RetVal;
extern Std_ReturnType Rte_Read_ppCddStpActual0_sStpActualValues_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

extern uint8 Rte_Read_CddLed_Status_HitCount;
extern uint8 Rte_Read_CddLed_LedState_HitCount;
extern uint8 Rte_Read_CddBoost_BoostStatus_HitCount;
extern uint8 Rte_Read_RSens_PcbTemperature_HitCount;
extern uint8 Rte_Write_StatM_StackUsage_HitCount;
extern uint8 NvM_WriteBlock_HitCount;
extern uint8 Rte_Read_RSens_ThermzoneTemperatures_HitCount;
extern uint8 Rte_Read_CddSwi_SwitchStatus_HitCount;
extern uint8 Rte_Read_ppCddStpActual0_sStpActualValues_HitCount;

#endif // TEST_STUBS_2023_08_25_H_
