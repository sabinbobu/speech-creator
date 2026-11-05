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
/// \file  Test_Ext.h
///
/// \brief Stub functions for access to software modules excluded from test
///
//-----------------------------------------------------------------------------
#ifndef TEST_EXT_2021_08_19_H_
#define TEST_EXT_2021_08_19_H_


#include <Std_Types.h>
#include <CddNcv78702_Eft.h>


//-----------------------------------------------------------------------------
// Access to EFT data
//-----------------------------------------------------------------------------
// API access
#define CDDNCV78702_EftDataValid()                Test_EftDataValid()

// calibration
#define CDDNCV78702_CALIB_nVOffset(Device)        Test_Eft_Calib()[Device].nVOffset
#define CDDNCV78702_CALIB_unVFactor(Device)       Test_Eft_Calib()[Device].unVFactor

// configuration
#define CDDNCV78702_ECUVARCFG_nVOffset(Device)    Test_Eft_EcuVarCfg()[Device].nVOffset
#define CDDNCV78702_ECUVARCFG_unVFactor(Device)   Test_Eft_EcuVarCfg()[Device].unVFactor
#define CDDNCV78702_ECUVARCFG_ucVariant(Device)   Test_Eft_EcuVarCfg()[Device].ucVariant
#define CDDNCV78702_ECUVARCFG_ucBoostCfg(Device)  Test_Eft_EcuVarCfg()[Device].ucBoostCfg


//-----------------------------------------------------------------------------
// Access to IoHwAbUser
//-----------------------------------------------------------------------------
#define CDDNCV78702_SetBoosterEn(Enable)          Test_SetBoosterEn(Enable)
#define CDDNCV78702_SetBoosterPwm(Enable)         Test_SetBoosterPwm(Enable)

//-----------------------------------------------------------------------------
// Access to CddSpi
//-----------------------------------------------------------------------------
#define CDDNCV78702_TransferMsg(Device, Data)     Test_TransferMsg(Device, Data)
#define CDDSPI_DEVICE(Index)                      Test_SpiIdx
#define BOOST                                     0u

// access to BOOST overvoltage treshold
#define CDDNCV78702_Cfg_60V_BOOST_OVERVOLTSD_THR  92u  // LDM.SYRS.32449



boolean                     Test_EftDataValid(void);
void                        Test_SetEftDataValid(boolean boValid);

tCddNcv78702_Eft_Calib*     Test_Eft_Calib(void);
tCddNcv78702_Eft_EcuVarCfg* Test_Eft_EcuVarCfg(void);

void                        Test_SetBoosterEn(boolean boEnable);
boolean                     Test_GetBoosterEn(void);

void                        Test_SetBoosterPwm(boolean boEnable);
boolean                     Test_GetBoosterPwmEn(void);

void                        Test_TransferMsg(uint8 ucDevice, uint16* punData);
uint16                      Test_GetTransferMsg(uint8 ucDevice);

extern uint8   Test_SpiIdx;

void RestoreStubContents(void);


#endif // TEST_EXT_2021_08_19_H_
