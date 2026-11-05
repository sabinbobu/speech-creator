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

// Headers of the Module
#include <CddBoost.h>

//=============================================================================
// Typedef
//=============================================================================

//=============================================================================
// Stub function declarations
//=============================================================================
void CddNcv78702_Init(void);
void CddNcv78702_Shutdown(void);
void CddNcv78702_SetBoosterVoltage(const uint32 ulIdx, const uint16 unVBoostTarget_mV);

Std_ReturnType Rte_Write_CddBoost_BoostState(const tsRte_BoostState* ppara1);
Std_ReturnType Rte_Write_CddBoost_BoostStatus(const tCddBoostStatus* ppara1);

Std_ReturnType Rte_Read_CodM_CddBoost_Para(tsRteCodingParameters* ppara1);

//=============================================================================
// Stub function parameter stubs
//=============================================================================
extern tsRte_BoostState Rte_Write_CddBoost_BoostState_Param1;
extern tCddBoostStatus  Rte_Write_CddBoost_BoostStatus_Param1;

extern tsRteCodingParameters Rte_Read_CodM_CddBoost_Para_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
extern Std_ReturnType Rte_Write_CddBoost_BoostState_RetVal;
extern Std_ReturnType Rte_Write_CddBoost_BoostStatus_RetVal;

extern Std_ReturnType Rte_Read_CodM_CddBoost_Para_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
extern uint8 Rte_Write_CddBoost_BoostState_HitCount;
extern uint8 Rte_Write_CddBoost_BoostStatus_HitCount;

extern uint8 Rte_Read_CodM_CddBoost_Para_HitCount;

#endif // TEST_STUBS_2023_08_25_H_
