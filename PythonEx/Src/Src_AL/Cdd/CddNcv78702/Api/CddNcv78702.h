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
/// \file   CddNcv78702.h
///
/// \brief  API for CddNcv78702
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef CDD_NCV78702_2021_03_25_H_
#define CDD_NCV78702_2021_03_25_H_


//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <Std_Types.h>


//-----------------------------------------------------------------------------
// version
//-----------------------------------------------------------------------------
#define CDDNCV78702_VERSION_MAJOR   2
#define CDDNCV78702_VERSION_MINOR   0
#define CDDNCV78702_VERSION_PATCH   1


//-----------------------------------------------------------------------------
// release notes
//-----------------------------------------------------------------------------
// 2.0.1  Rounding of booster voltage
// 2.0.0  Booster startup based on supply voltage
//        RESET mechanisms
//        SPI error support
//        Thermal warning support
// 1.1.1  Bugix of booster voltage limitation
// 1.1.0  MPU support
// 1.0.0  Enhanced configuration capabilities
// 0.0.0  Initial version based on FLM3 implementation


//-----------------------------------------------------------------------------
// open issues
//-----------------------------------------------------------------------------
// Support for multiple booster chips still not complete --> not planned yet
// startup activation depending on supply voltage        --> to do
// Restart mechanism                                     --> to do
// SPI fault handling                                    --> to do


//-----------------------------------------------------------------------------
// Start declaration or definitions of functions
//-----------------------------------------------------------------------------
#define ctadCddBoost_START_SEC_CODE
#include <../Cfg/CddNcv78702_MemMap.h>

uint32 CddNcv78702_Init    (void);  
void   CddNcv78702_Shutdown(void);
void   CddNcv78702_SetBoosterVoltage(const uint32 ulIdx, const uint16 unVBoostTarget_mV);

boolean CddNcv78702_IsReset          (const uint32 ulIdx);
boolean CddNcv78702_IsSpiError       (const uint32 ulIdx);
boolean CddNcv78702_IsThermalShutDown(const uint32 ulIdx);
boolean CddNcv78702_IsThermalWarning (const uint32 ulIdx);

#define ctadCddBoost_STOP_SEC_CODE
#include <../Cfg/CddNcv78702_MemMap.h>
//-----------------------------------------------------------------------------
// End declaration or definitions of functions
//-----------------------------------------------------------------------------


#endif // CDD_NCV78702_2021_03_25_H_
