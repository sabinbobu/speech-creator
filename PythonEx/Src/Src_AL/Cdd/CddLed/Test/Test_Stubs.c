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
tsRte_TgtLedSig0_ASIL Rte_Read_SysMon_TgtLedSig_sVal_Param1;
tsRteCodingParameters Rte_Read_CodM_CddLed_Para_Param1;
tsRte_ChLedSettings   Rte_Read_CtrlLed_LedSettings_sVal_Param1;
tsRte_LedStates       Rte_Write_CddLed_LedState_Param1;
tCddLedStatus         Rte_Write_CddLed_Status_Param1;
tsRte_TgtLedSig0_FaultStatus_ASIL Rte_Write_CddLed_TgtLed_FaultStatus_ASIL_Param1;
uint8                 SysMonCheck_Data_IsTurnIndicatorFuSa_Param1;

uint8*                Crc_CalculateCRC8H2F_Param1;
uint32                Crc_CalculateCRC8H2F_Param2;
uint8                 Crc_CalculateCRC8H2F_Param3;
uint32                LPTMR0_GetTimeElapsed_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
Std_ReturnType  Rte_Read_SysMon_TgtLedSig_sVal_RetVal;
Std_ReturnType  Rte_Read_CodM_CddLed_Para_RetVal;
Std_ReturnType  Rte_Read_CtrlLed_LedSettings_sVal_RetVal;
Std_ReturnType  Rte_Write_CddLed_LedState_RetVal;
Std_ReturnType  Rte_Write_CddLed_Status_RetVal;
Std_ReturnType  Rte_Write_CddLed_TgtLed_FaultStatus_ASIL_RetVal;
boolean         SysMonCheck_Data_IsTurnIndicatorFuSa_RetVal;
uint8           Crc_CalculateCRC8H2F_RetVal;
uint32          LPTMR0_GetTimeElapsed_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
uint8 Rte_Read_SysMon_TgtLedSig_sVal_HitCount;
uint8 Rte_Read_CodM_CddLed_Para_HitCount;
uint8 Rte_Read_CtrlLed_LedSettings_sVal_HitCount;
uint8 Rte_Write_CddLed_LedState_HitCount;
uint8 Rte_Write_CddLed_Status_HitCount;
uint8 Rte_Write_CddLed_TgtLed_FaultStatus_ASIL_HitCount;

uint8   SysMonCheck_Data_IsTurnIndicatorFuSa_HitCount;
uint8   Crc_CalculateCRC8H2F_HitCount;
uint8   LPTMR0_GetTimeElapsed_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_SysMon_TgtLedSig_sVal
///
/// \descr  stub function to simulate the behaviour of Rte_Read_SysMon_TgtLedSig_sVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_SysMon_TgtLedSig_sVal(tsRte_TgtLedSig0_ASIL* ppara1)
{
  *ppara1 = Rte_Read_SysMon_TgtLedSig_sVal_Param1;
  Rte_Read_SysMon_TgtLedSig_sVal_HitCount++;
  return Rte_Read_SysMon_TgtLedSig_sVal_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CodM_CddLed_Para
///
/// \descr  stub function to simulate the behaviour of Rte_Read_CodM_CddLed_Para
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CodM_CddLed_Para(tsRteCodingParameters* ppara1)
{
  *ppara1 = Rte_Read_CodM_CddLed_Para_Param1;
  Rte_Read_CodM_CddLed_Para_HitCount++;
  return Rte_Read_CodM_CddLed_Para_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Read_CtrlLed_LedSettings_sVal
///
/// \descr  stub function to simulate the behaviour of Rte_Read_CtrlLed_LedSettings_sVal
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Read_CtrlLed_LedSettings_sVal(tsRte_ChLedSettings* ppara1)
{
  *ppara1 = Rte_Read_CtrlLed_LedSettings_sVal_Param1;
  Rte_Read_CtrlLed_LedSettings_sVal_HitCount++;
  return Rte_Read_CtrlLed_LedSettings_sVal_RetVal;
}


//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CddLed_LedState
///
/// \descr  stub function to simulate the behaviour of Rte_Write_CddLed_LedState
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CddLed_LedState(const tsRte_LedStates* ppara1)
{
  Rte_Write_CddLed_LedState_Param1 = *ppara1;
  Rte_Write_CddLed_LedState_HitCount++;
  return Rte_Write_CddLed_LedState_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CddLed_Status
///
/// \descr  stub function to simulate the behaviour of Rte_Write_CddLed_Status
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CddLed_Status(const tCddLedStatus* ppara1)
{
  Rte_Write_CddLed_Status_Param1 = *ppara1;
  Rte_Write_CddLed_Status_HitCount++;
  return Rte_Write_CddLed_Status_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Rte_Write_CddLed_TgtLed_FaultStatus_ASIL
///
/// \descr  stub function to simulate the behaviour of Rte_Write_CddLed_TgtLed_FaultStatus_ASIL
///
/// \param  ppara1
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Rte_Write_CddLed_TgtLed_FaultStatus_ASIL(const tsRte_TgtLedSig0_FaultStatus_ASIL* ppara1)
{
  Rte_Write_CddLed_TgtLed_FaultStatus_ASIL_Param1 = *ppara1;
  Rte_Write_CddLed_TgtLed_FaultStatus_ASIL_HitCount++;
  return Rte_Write_CddLed_TgtLed_FaultStatus_ASIL_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_Data_IsTurnIndicatorFuSa
///
/// \descr  stub function to simulate the behaviour of SysMonCheck_Data_IsTurnIndicatorFuSa
///
/// \param  ppara1
///
/// \boolean Std_ReturnType
//-----------------------------------------------------------------------------
boolean SysMonCheck_Data_IsTurnIndicatorFuSa(uint8 ucFuSaIdx)
{
  SysMonCheck_Data_IsTurnIndicatorFuSa_Param1 = ucFuSaIdx;
  SysMonCheck_Data_IsTurnIndicatorFuSa_HitCount++;
  return SysMonCheck_Data_IsTurnIndicatorFuSa_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Crc_CalculateCRC8H2F
///
/// \descr  Stub function created to simulate the behaviour of Crc_CalculateCRC8H2F
///
/// \param  pucCrc_DataPtr
/// \param  ulCrc_Length
/// \param  ulCrc_StartValue32
///
/// \return Crc_CalculateCRC8H2F_RetVal
//-----------------------------------------------------------------------------
uint8 Crc_CalculateCRC8H2F(CONST_AL uint8 *DataPtr, CONST_AL uint32 Length, CONST_AL uint8  StartValue8)
{
  Crc_CalculateCRC8H2F_Param1 = DataPtr;
  Crc_CalculateCRC8H2F_Param2 = Length;
  Crc_CalculateCRC8H2F_Param3 = StartValue8;

  Crc_CalculateCRC8H2F_HitCount++;

  return Crc_CalculateCRC8H2F_RetVal;
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
  LPTMR0_GetTimeElapsed_Param1 = ulStartValue;
  LPTMR0_GetTimeElapsed_HitCount++;

  return LPTMR0_GetTimeElapsed_RetVal;
}

