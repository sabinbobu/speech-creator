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
/// \file  CddTps92520_RoutCfg.h
///
/// \brief  Routing configuration of CddTps92520 module
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef CDD_TPS92520_ROUT_CFG_2021_06_29_H_
#define CDD_TPS92520_ROUT_CFG_2021_06_29_H_


#ifdef UNIT_TEST

#include <Test_Ext.h>

#else

#include <CddEft.h>
#include <Pwm.h>


//-----------------------------------------------------------------------------
// Access to EFT data
//-----------------------------------------------------------------------------
// API access
#define CDDTPS92520_EftDataValid()                CddEft_DataValid()  //CddEft_DataValid()

// calibration
#define CDDTPS92520_CALIB_unIFactor(Device,Channel)            EFT_CALIB_Tps92520[Device].aDrv[Channel].unIFactor
#define CDDTPS92520_CALIB_nIOffset(Device,Channel)             EFT_CALIB_Tps92520[Device].aDrv[Channel].nIOffset

// configuration
#define CDDTPS92520_ECUVARCFG_ucDrvType(Device)                EFT_ECUVARCFG_Tps92520[Device].ucDrvType
#define CDDTPS92520_ECUVARCFG_ucAssignedOutput(Device,Channel) EFT_ECUVARCFG_Tps92520[Device].aDrv[Channel].ucAssignedOutput
#define CDDTPS92520_ECUVARCFG_ucPmax(Device,Channel)           EFT_ECUVARCFG_Tps92520[Device].aDrv[Channel].ucPmax
#define CDDTPS92520_ECUVARCFG_unImax(Device,Channel)           EFT_ECUVARCFG_Tps92520[Device].aDrv[Channel].unImax
#define CDDTPS92520_ECUVARCFG_unImin(Device,Channel)           EFT_ECUVARCFG_Tps92520[Device].aDrv[Channel].unImin


//-----------------------------------------------------------------------------
// Access to IoHwAbUser
//-----------------------------------------------------------------------------
#define CDDTPS92520_SetLedChannelPwm_1_32768(Channel,Duty)   Pwm_SetDutyCycle(Channel, Duty)

#define CDDTPS92520_GetLedChannelPwm_1_32768(Channel)      CddTps92520_aunTgtDutyCycle[Channel]   // temporary
//#define CDDTPS92520_GetLedChannelPwm_1_32768(Channel)      IoHwAbUser_GetLedChannelPwm(Channel)

#endif

#endif // CDD_TPS92520_ROUT_CFG_2021_06_29_H_
