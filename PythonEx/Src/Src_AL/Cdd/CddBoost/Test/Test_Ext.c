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
#include <../Cfg/CddBoost_Cfg.h>
#include <Std_Types.h>
#include <Test_Ext.h>

//-----------------------------------------------------------------------------
// Stub variables
//-----------------------------------------------------------------------------
tPara_CodingArea applicationCodingData = { { { 30u, 50u, 50u }, { 50u, 10u, 15u, 5u },
  { { 0u,   0u, 0u, 50u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u },
    { 0u, 185u, 0u,  0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } } } };  // booster voltage will be (185 * .2 + 30/10 - 50/10)V = 37V


boolean EftDataValid_Used = TRUE;
boolean EftDataValid_Back = TRUE;

uint16  Test_unEcuVolt           = 13000u;
boolean Test_aboIsReset          [CDDBOOST_Cfg_NbOfChannels] = { FALSE };
boolean Test_aboIsSpiError       [CDDBOOST_Cfg_NbOfChannels] = { FALSE };
boolean Test_aboIsThermalShutDown[CDDBOOST_Cfg_NbOfChannels] = { FALSE };
boolean Test_aboIsThermalWarning [CDDBOOST_Cfg_NbOfChannels] = { FALSE };


//-----------------------------------------------------------------------------
// Stub functions
//-----------------------------------------------------------------------------
void Test_SetEftDataValid(boolean boValid)
{
  EftDataValid_Used = boValid;
}

void RestoreStubContents(void)
{
  EftDataValid_Used = EftDataValid_Back;

  //memcpy(LedPwm_Used,        LedPwm_Back,        sizeof(LedPwm_Used));
}

uint32 Test_Driver_Init(void)
{
  return 1u;
}

boolean Test_IsReset          (uint32 ulIdx) {  return Test_aboIsReset          [ulIdx]; }
boolean Test_IsSpiError       (uint32 ulIdx) {  return Test_aboIsSpiError       [ulIdx]; }
boolean Test_IsThermalShutDown(uint32 ulIdx) {  return Test_aboIsThermalShutDown[ulIdx]; }
boolean Test_IsThermalWarning (uint32 ulIdx) {  return Test_aboIsThermalWarning [ulIdx]; }

void Test_SetReset          (uint32 ulIdx, boolean boReset)  {  Test_aboIsReset          [ulIdx] = boReset;  }
void Test_SetSpiError       (uint32 ulIdx, boolean boSpiErr) {  Test_aboIsSpiError       [ulIdx] = boSpiErr; }
void Test_SetThermalShutDown(uint32 ulIdx, boolean boTSD)    {  Test_aboIsThermalShutDown[ulIdx] = boTSD;    }
void Test_SetThermalWarning (uint32 ulIdx, boolean boTW)     {  Test_aboIsThermalWarning [ulIdx] = boTW;     }

void Test_GetECUSupply(uint32* pulVolt) {  *pulVolt = Test_unEcuVolt; }
void Test_SetECUSupply(uint32 ulVolt)   {  Test_unEcuVolt = ulVolt;   }
