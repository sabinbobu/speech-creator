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
/// \file   CddBoost.h
///
/// \brief  API for CddBoost
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef CDD_BOOST_2021_03_03_H_
#define CDD_BOOST_2021_03_03_H_


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <Std_Types.h>
#include <../Cfg/CddBoost_Cfg.h>


//-----------------------------------------------------------------------------
// version
//-----------------------------------------------------------------------------
#define CDDBOOST_VERSION_MAJOR   2
#define CDDBOOST_VERSION_MINOR   0
#define CDDBOOST_VERSION_PATCH   0


//-----------------------------------------------------------------------------
// release notes
//-----------------------------------------------------------------------------
// 2.0.0  Booster startup based on supply voltage
//        RESET mechanisms
//        SPI error support
//        Thermal warning support
//        Remove CRC from API
// 1.0.0  MPU support
// 0.2.0  Initial version based on FLM3 implementation


//-----------------------------------------------------------------------------
// types
//-----------------------------------------------------------------------------
// error status
typedef enum
{
  eCddBoost_NoSupport      = 0,  // not supported due to EFT data
  eCddBoost_Reset          = 1,  // still in "reset" state
  eCddBoost_DiagIdle       = 2,  // normal operation, no test
  eCddBoost_StatusOk       = 3,  // normal operation
  eCddBoost_ErrVoltLo      = 4,  // voltage below threshold
  eCddBoost_ErrVoltHi      = 5,  // voltage above threshold
  eCddBoost_ErrThermShutdn = 6,  // thermal shutdown
  eCddBoost_ErrSpi         = 7   // SPI error
} tCddBoostErrStatus;

// full status (all channels)
typedef struct
{
  tCddBoostErrStatus aStatus          [CDDBOOST_Cfg_NbOfChannels];
  boolean            aboThermalWarning[CDDBOOST_Cfg_NbOfChannels];
} tCddBoostStatus;

// target values
typedef struct
{
  uint16 aunBoostVolt_mV[CDDBOOST_Cfg_NbOfChannels];
} tCddBoostTarget;


//-----------------------------------------------------------------------------
// Start declaration or definitions of functions
//-----------------------------------------------------------------------------
#define ctadCddBoost_START_SEC_CODE
#include <../Cfg/CddBoost_MemMap.h>

void   CddBoost_Init     (void);
void   CddBoost_SetPara  (boolean boValid);
void   CddBoost_Cycle20ms(void);
void   CddBoost_SetTarget(tCddBoostTarget* pTarget);
void   CddBoost_GetStatus(tCddBoostStatus* pStatus);
void   CddBoost_Shutdown (void);

#define ctadCddBoost_STOP_SEC_CODE
#include <../Cfg/CddBoost_MemMap.h>
//-----------------------------------------------------------------------------
// End declaration or definitions of functions
//-----------------------------------------------------------------------------


#endif // CDD_BOOST_2021_03_03_H_
