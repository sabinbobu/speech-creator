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
#ifndef TEST_EXT_2021_08_13_H_
#define TEST_EXT_2021_08_13_H_


#include <Std_Types.h>
#include <CddTps92520_Eft.h>


// API access
#define CDDTPS92520_EftDataValid()                             Test_EftDataValid()

// calibration
#define CDDTPS92520_CALIB_unIFactor(Device,Channel)            Test_Eft_Calib()[Device].aDrv[Channel].unIFactor
#define CDDTPS92520_CALIB_nIOffset(Device,Channel)             Test_Eft_Calib()[Device].aDrv[Channel].nIOffset

// configuration
#define CDDTPS92520_ECUVARCFG_ucDrvType(Device)                Test_Eft_EcuVarCfg()[Device].ucDrvType
#define CDDTPS92520_ECUVARCFG_ucAssignedOutput(Device,Channel) Test_Eft_EcuVarCfg()[Device].aDrv[Channel].ucAssignedOutput
#define CDDTPS92520_ECUVARCFG_ucPmax(Device,Channel)           Test_Eft_EcuVarCfg()[Device].aDrv[Channel].ucPmax
#define CDDTPS92520_ECUVARCFG_unImax(Device,Channel)           Test_Eft_EcuVarCfg()[Device].aDrv[Channel].unImax
#define CDDTPS92520_ECUVARCFG_unImin(Device,Channel)           Test_Eft_EcuVarCfg()[Device].aDrv[Channel].unImin

// Access to IoHwAbUser
#define CDDTPS92520_SetLedChannelPwm_1_32768(Channel,Duty)     Test_SetLedPwm(Channel, Duty)
#define CDDTPS92520_GetLedChannelPwm_1_32768(Channel)          Test_GetLedPwm(Channel)


boolean                     Test_EftDataValid(void);
void                        Test_SetEftDataValid(boolean boValid);

void                        Test_SetLedPwm(uint32 ulChn, uint16 unDuty);
uint16                      Test_GetLedPwm(uint32 ulChn);

tCddTps92520_Eft_Calib*     Test_Eft_Calib(void);
tCddTps92520_Eft_EcuVarCfg* Test_Eft_EcuVarCfg(void);


void RestoreStubContents(void);


#endif // TEST_EXT_2021_08_13_H_
