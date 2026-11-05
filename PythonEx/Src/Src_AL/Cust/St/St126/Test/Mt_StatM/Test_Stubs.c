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

tCddLedStatus                    Rte_Read_CddLed_Status_Param1;
tsRte_LedStates                  Rte_Read_CddLed_LedState_Param1;
tCddBoostStatus                  Rte_Read_CddBoost_BoostStatus_Param1;
tsRte_PcbTemperatureMsg          Rte_Read_RSens_PcbTemperature_Param1;
uint8                            Rte_Write_StatM_StackUsage_Param1;
NvM_BlockIdType                  NvM_WriteBlock_Param1;
void*                            NvM_WriteBlock_Param2;
tsRte_NTCTemperature             Rte_Read_RSens_ThermzoneTemperatures_Param1;
tsRte_HssStatus                  Rte_Read_CddSwi_SwitchStatus_Param1;
tsRte_CddStpActual               Rte_Read_ppCddStpActual0_sStpActualValues_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

Std_ReturnType Rte_Read_CddLed_Status_Param1_RetVal;
Std_ReturnType Rte_Read_CddLed_LedState_Param1_RetVal;
Std_ReturnType Rte_Read_CddBoost_BoostStatus_Param1_RetVal;
Std_ReturnType Rte_Read_RSens_PcbTemperature_RetVal;
Std_ReturnType Rte_Write_StatM_StackUsage_RetVal;
Std_ReturnType NvM_WriteBlock_RetVal;
Std_ReturnType Rte_Read_RSens_ThermzoneTemperatures_RetVal;
Std_ReturnType Rte_Read_CddSwi_SwitchStatus_RetVal;
Std_ReturnType Rte_Read_ppCddStpActual0_sStpActualValues_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

uint8 Rte_Read_CddLed_Status_HitCount;
uint8 Rte_Read_CddLed_LedState_HitCount;
uint8 Rte_Read_CddBoost_BoostStatus_HitCount;
uint8 Rte_Read_RSens_PcbTemperature_HitCount;
uint8 Rte_Write_StatM_StackUsage_HitCount;
uint8 NvM_WriteBlock_HitCount;
uint8 Rte_Read_RSens_ThermzoneTemperatures_HitCount;
uint8 Rte_Read_CddSwi_SwitchStatus_HitCount;
uint8 Rte_Read_ppCddStpActual0_sStpActualValues_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CddLed_Status
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CddLed_Status
///
/// \param  - ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CddLed_Status(tCddLedStatus* ppara1)
{
    *ppara1 = Rte_Read_CddLed_Status_Param1;
    Rte_Read_CddLed_Status_HitCount++;
    return Rte_Read_CddLed_Status_Param1_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CddLed_LedState
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CddLed_LedState
///
/// \param  - ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CddLed_LedState(tsRte_LedStates* ppara1)
{
    *ppara1 = Rte_Read_CddLed_LedState_Param1;
    Rte_Read_CddLed_LedState_HitCount++;
    return Rte_Read_CddLed_LedState_Param1_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CddBoost_BoostStatus
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_CddBoost_BoostStatus
///
/// \param  - ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CddBoost_BoostStatus(tCddBoostStatus* ppara1)
{
    *ppara1 = Rte_Read_CddBoost_BoostStatus_Param1;
    Rte_Read_CddBoost_BoostStatus_HitCount++;
    return Rte_Read_CddBoost_BoostStatus_Param1_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_PcbTemperature
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_RSens_PcbTemperature
///
/// \param  - ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_PcbTemperature(tsRte_PcbTemperatureMsg* ppara1)
{
    *ppara1 = Rte_Read_RSens_PcbTemperature_Param1;
    Rte_Read_RSens_PcbTemperature_HitCount++;
    return Rte_Read_RSens_PcbTemperature_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_StatM_StackUsage
///
/// \descr  Stub function created to simulate the behaviour of Rte_Write_StatM_StackUsage
///
/// \param  - para1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_StatM_StackUsage(uint8 para1)
{
    Rte_Write_StatM_StackUsage_Param1 = para1;
    Rte_Write_StatM_StackUsage_HitCount++;
    return  Rte_Write_StatM_StackUsage_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  NvM_WriteBlock
///
/// \descr  Stub function created to simulate the behaviour of NvM_WriteBlock
///
/// \param  - BlockId, NvM_SrcPtr
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType NvM_WriteBlock(NvM_BlockIdType BlockId, void* NvM_SrcPtr)
{
    NvM_WriteBlock_Param1 = BlockId;
    NvM_WriteBlock_Param2 = NvM_SrcPtr;
    NvM_WriteBlock_HitCount++;
    return NvM_WriteBlock_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_RSens_ThermzoneTemperatures
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_RSens_ThermzoneTemperatures
///
/// \param  *ppara1
///
/// \return Std_ReturnType
//----------------------------------------------------------------------------
Std_ReturnType Rte_Read_RSens_ThermzoneTemperatures(tsRte_NTCTemperature* ppara1)
{
    *ppara1 = Rte_Read_RSens_ThermzoneTemperatures_Param1;
    Rte_Read_RSens_ThermzoneTemperatures_HitCount++;
    return Rte_Read_RSens_ThermzoneTemperatures_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief Rte_Read_CddSwi_SwitchStatus
/// 
/// \descr  Stub function to simulate the behavoiur of Rte_Read_CddSwi_SwitchStatus
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CddSwi_SwitchStatus(tsRte_HssStatus *ppara1)
{
    *ppara1 = Rte_Read_CddSwi_SwitchStatus_Param1;
    Rte_Read_CddSwi_SwitchStatus_HitCount++;
    return Rte_Read_CddSwi_SwitchStatus_RetVal;

}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_ppCddStpActual0_sStpActualValues
///
/// \descr  Stub function created to simulate the behaviour of Rte_Read_ppCddStpActual0_sStpActualValues
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_ppCddStpActual0_sStpActualValues(tsRte_CddStpActual* ppara1)
{
    *ppara1 = Rte_Read_ppCddStpActual0_sStpActualValues_Param1;
    Rte_Read_ppCddStpActual0_sStpActualValues_HitCount++;
    return Rte_Read_ppCddStpActual0_sStpActualValues_RetVal;
}

