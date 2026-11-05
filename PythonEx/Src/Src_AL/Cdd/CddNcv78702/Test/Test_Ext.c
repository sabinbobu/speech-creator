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
#include <string.h>
#include <Test_Ext.h>
#include <../Cfg/CddNcv78702_Cfg.h>



//-----------------------------------------------------------------------------
// Stub variables
//-----------------------------------------------------------------------------
boolean EftDataValid_Used = TRUE;
boolean EftDataValid_Back = TRUE;

tCddNcv78702_Eft_Calib      Eft_Calib_Used[CDDNCV78702_Cfg_NbOfDevices] = CDDNCV78702_Eft_Calib_Default;
tCddNcv78702_Eft_Calib      Eft_Calib_Back[CDDNCV78702_Cfg_NbOfDevices] = CDDNCV78702_Eft_Calib_Default;

tCddNcv78702_Eft_EcuVarCfg  Eft_EcuVarCfg_Used[CDDNCV78702_Cfg_NbOfDevices] = CDDNCV78702_Eft_EcuVarCfg_Default;
tCddNcv78702_Eft_EcuVarCfg  Eft_EcuVarCfg_Back[CDDNCV78702_Cfg_NbOfDevices] = CDDNCV78702_Eft_EcuVarCfg_Default;

boolean boBoostEn_Used = FALSE;
boolean boBoostEn_Back = FALSE;
boolean boPwmEn_Used   = FALSE;
boolean boPwmEn_Back   = FALSE;

uint16  aunSpiMsg_Used[CDDNCV78702_Cfg_NbOfDevices];
uint16  aunSpiMsg_Back[CDDNCV78702_Cfg_NbOfDevices];

uint8   Test_SpiIdx = 0u;

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

tCddNcv78702_Eft_Calib* Test_Eft_Calib(void)
{
  return Eft_Calib_Used;
}

tCddNcv78702_Eft_EcuVarCfg* Test_Eft_EcuVarCfg(void)
{
  return Eft_EcuVarCfg_Used;
}

void Test_SetBoosterEn(boolean boEnable)
{
  boBoostEn_Used = boEnable;
}

boolean Test_GetBoosterEn(void)
{
  return boBoostEn_Used;
}

void Test_SetBoosterPwm(boolean boEnable)
{
  boPwmEn_Used = boEnable;
}

boolean Test_GetBoosterPwmEn(void)
{
  return boPwmEn_Used;
}

void Test_TransferMsg(uint8 ucDevice, uint16* punData)
{
  aunSpiMsg_Used[ucDevice] = *punData;
}

uint16  Test_GetTransferMsg(uint8 ucDevice)
{
  return aunSpiMsg_Used[ucDevice]; 
}


void RestoreStubContents(void)
{
  EftDataValid_Used = EftDataValid_Back;

  memcpy(Eft_Calib_Used,      Eft_Calib_Back,     sizeof(Eft_Calib_Used));
  memcpy(Eft_EcuVarCfg_Used,  Eft_EcuVarCfg_Back, sizeof(Eft_EcuVarCfg_Used));
  memcpy(&boBoostEn_Used,     &boBoostEn_Back,    sizeof(boBoostEn_Used));
  memcpy(&boPwmEn_Used,       &boPwmEn_Back,      sizeof(boPwmEn_Used));
  memcpy(aunSpiMsg_Used,      aunSpiMsg_Back,     sizeof(aunSpiMsg_Used));
}
