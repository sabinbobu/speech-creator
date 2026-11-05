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
/// \file  CddNcv78702_RoutCfg.h
///
/// \brief  Routing configuration of CddNcv78702 module
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef CDD_NCV78702_ROUT_CFG_2021_06_29_H_
#define CDD_NCV78702_ROUT_CFG_2021_06_29_H_


#ifdef UNIT_TEST

#include <Test_Ext.h>

#else

#include <CddEft.h>
#include <IoHwAbUser.h>
#include <CddSpi.h>



//-----------------------------------------------------------------------------
// Access to EFT data
//-----------------------------------------------------------------------------
// API access
#define CDDNCV78702_EftDataValid()                CddEft_DataValid() 

// calibration
#define CDDNCV78702_CALIB_nVOffset(Device)        EFT_CALIB_Ncv78702[Device].nVOffset
#define CDDNCV78702_CALIB_unVFactor(Device)       EFT_CALIB_Ncv78702[Device].unVFactor

// configuration
#define CDDNCV78702_ECUVARCFG_nVOffset(Device)    EFT_ECUVARCFG_Ncv78702[Device].nVOffset
#define CDDNCV78702_ECUVARCFG_unVFactor(Device)   EFT_ECUVARCFG_Ncv78702[Device].unVFactor
#define CDDNCV78702_ECUVARCFG_ucVariant(Device)   EFT_ECUVARCFG_Ncv78702[Device].ucVariant
#define CDDNCV78702_ECUVARCFG_ucBoostCfg(Device)  EFT_ECUVARCFG_Ncv78702[Device].ucBoostCfg


//-----------------------------------------------------------------------------
// Access to IoHwAbUser
//-----------------------------------------------------------------------------
#define CDDNCV78702_SetBoosterEn(Enable)   IoHwAbUser_SetBoostMode(Enable) //Dio_WriteChannel (0u, (Enable == TRUE) ? 1u : 0u)
#define CDDNCV78702_SetBoosterPwm(Enable)  //IoHwAbUser_SetBoosterPwm(Enable) //PRQA S 5334 // architecture


//-----------------------------------------------------------------------------
// Access to CddSpi
//-----------------------------------------------------------------------------
#define CDDNCV78702_TransferMsg(Device, Data)  CddSpi_TransferMsg(Device, Data)

#endif // UNIT TEST

#endif // CDD_NCV78702_ROUT_CFG_2021_06_29_H_
