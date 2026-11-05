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
/// \file  Test_Ext.c
///
/// \brief Stub functions for access to software modules excluded from test
///
//-----------------------------------------------------------------------------
#include <Std_Types.h>
#include <CddTps92520_Eft.h>
#include <../Cfg/CddTps92520_Cfg.h>
#include <string.h>


//-----------------------------------------------------------------------------
// Stub variables
//-----------------------------------------------------------------------------
boolean EftDataValid_Used = TRUE;
boolean EftDataValid_Back = TRUE;

tCddTps92520_Eft_Calib      Eft_Calib_Used[CDDTPS92520_Cfg_NbOfDevices]     = CDDTPS92520_Eft_Calib_Default;
tCddTps92520_Eft_Calib      Eft_Calib_Back[CDDTPS92520_Cfg_NbOfDevices]     = CDDTPS92520_Eft_Calib_Default;

tCddTps92520_Eft_EcuVarCfg  Eft_EcuVarCfg_Used[CDDTPS92520_Cfg_NbOfDevices] = CDDTPS92520_Eft_EcuVarCfg_Default;
tCddTps92520_Eft_EcuVarCfg  Eft_EcuVarCfg_Back[CDDTPS92520_Cfg_NbOfDevices] = CDDTPS92520_Eft_EcuVarCfg_Default;

uint16                      LedPwm_Used[CDDTPS92520_Cfg_NbOfDevices];  // implicit zero initialized
uint16                      LedPwm_Back[CDDTPS92520_Cfg_NbOfDevices];


//-----------------------------------------------------------------------------
// Stub functions
//-----------------------------------------------------------------------------
void Test_SetEftDataValid(boolean boValid)
{
  EftDataValid_Used = boValid;
}

boolean Test_EftDataValid(void)
{
  return EftDataValid_Used;
}

tCddTps92520_Eft_Calib* Test_Eft_Calib(void)
{
  return Eft_Calib_Used;
}

tCddTps92520_Eft_EcuVarCfg* Test_Eft_EcuVarCfg(void)
{
  return Eft_EcuVarCfg_Used;
}

void Test_SetLedPwm(uint32 ulChn, uint16 unDuty)
{
  LedPwm_Used[ulChn] = unDuty;
}

uint16 Test_GetLedPwm(uint32 ulChn)
{
  return LedPwm_Used[ulChn];
}

void RestoreStubContents(void)
{
  EftDataValid_Used = EftDataValid_Back;

  memcpy(Eft_Calib_Used,     Eft_Calib_Back,     sizeof(Eft_Calib_Used));
  memcpy(Eft_EcuVarCfg_Used, Eft_EcuVarCfg_Back, sizeof(Eft_EcuVarCfg_Used));
  memcpy(LedPwm_Used,        LedPwm_Back,        sizeof(LedPwm_Used));
}
