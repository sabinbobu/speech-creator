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
tsRte_BoostState Rte_Write_CddBoost_BoostState_Param1;
tCddBoostStatus  Rte_Write_CddBoost_BoostStatus_Param1;

tsRteCodingParameters Rte_Read_CodM_CddBoost_Para_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
Std_ReturnType Rte_Write_CddBoost_BoostState_RetVal;
Std_ReturnType Rte_Write_CddBoost_BoostStatus_RetVal;

Std_ReturnType Rte_Read_CodM_CddBoost_Para_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
uint8 Rte_Write_CddBoost_BoostState_HitCount;
uint8 Rte_Write_CddBoost_BoostStatus_HitCount;

uint8 Rte_Read_CodM_CddBoost_Para_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================
void CddNcv78702_Init(void) {}

void CddNcv78702_Shutdown(void) {}

void CddNcv78702_SetBoosterVoltage(const uint32 ulIdx, const uint16 unVBoostTarget_mV)
{
  (void)ulIdx; (void)unVBoostTarget_mV;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CddBoost_BoostState
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_CddBoost_BoostState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CddBoost_BoostState(const tsRte_BoostState* ppara1)
{
  Rte_Write_CddBoost_BoostState_Param1 = *ppara1;
  Rte_Write_CddBoost_BoostState_HitCount++;
  return Rte_Write_CddBoost_BoostState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CddBoost_BoostState
///
/// \descr  Stub function to simulate the behaviour of Rte_Write_CddBoost_BoostState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CddBoost_BoostStatus(const tCddBoostStatus* ppara1)
{
  Rte_Write_CddBoost_BoostStatus_Param1 = *ppara1;
  Rte_Write_CddBoost_BoostStatus_HitCount++;
  return Rte_Write_CddBoost_BoostStatus_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CodM_CddBoost_Para
///
/// \descr  Stub function to simulate the behaviour of Rte_Read_CodM_CddBoost_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CodM_CddBoost_Para(tsRteCodingParameters* ppara1)
{
  *ppara1 = Rte_Read_CodM_CddBoost_Para_Param1;
  Rte_Read_CodM_CddBoost_Para_HitCount++;
  return Rte_Read_CodM_CddBoost_Para_RetVal;
}

