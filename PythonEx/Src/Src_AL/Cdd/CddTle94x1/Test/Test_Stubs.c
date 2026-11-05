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
uint32 LPTMR0_GetTimeElapsed_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
uint32          LPTMR0_GetTimeElapsed_RetVal;
tiu16Voltage_mV IoHwAbUser_Read_VCCX1_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
uint32 LPTMR0_GetTimeElapsed_HitCount;
uint32 IoHwAbUser_Read_VCCX1_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

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

//-----------------------------------------------------------------------------
/// \brief IoHwAbUser_Read_VCCX1
///
/// \descr Stub function for IoHwAbUser_Read_VCCX1
///
/// \param  void
///
/// \return tiu16Voltage_mV
//-----------------------------------------------------------------------------
tiu16Voltage_mV IoHwAbUser_Read_VCCX1(void)
{
  IoHwAbUser_Read_VCCX1_HitCount++;

  return IoHwAbUser_Read_VCCX1_RetVal;
}


