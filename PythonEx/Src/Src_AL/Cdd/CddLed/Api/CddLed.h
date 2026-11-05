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
/// \file   CddLed.h
///
/// \brief  API for CddLed
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef CDD_LED_2021_03_02_H_
#define CDD_LED_2021_03_02_H_


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <Std_Types.h>
#include <../Cfg/CddLed_Cfg.h>


//-----------------------------------------------------------------------------
// version
//-----------------------------------------------------------------------------
#define CDDLED_VERSION_MAJOR   2
#define CDDLED_VERSION_MINOR   0
#define CDDLED_VERSION_PATCH   0


//-----------------------------------------------------------------------------
// release notes
//-----------------------------------------------------------------------------
// 2.0.0  SPI error support
//        Modification of voltage interface
//        Remove On/Off voltage support
// 1.3.0  Full error support except SPI and CRC error
// 1.2.0  MPU support
// 1.1.0  Change of coding data format
// 1.0.0  Support of ErrUnderVoltage and ErrShortToUbat
//        Suppression of errors using new API function CddLed_DriverSettings() 
// 0.1.0  Simple support of status (ShortToGnd and OpenLoad)
// 0.0.0  Initial version based on FLM3 implementation


//-----------------------------------------------------------------------------
// open issues
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------
#define CDDLED_MaxDuty   32768u  // max. PWM duty cycle (100%)


//-----------------------------------------------------------------------------
// types
//-----------------------------------------------------------------------------
// error status
typedef enum
{
  eCddLed_NoSupport       = 0,  // not supported due to EFT data
  eCddLed_Reset           = 1,  // still in "reset" state
  eCddLed_Disabled        = 2,  // LED off
  eCddLed_DiagIdle        = 3,  // normal operation, no test
  eCddLed_StatusOk        = 4,  // normal operation
  eCddLed_ErrOpenLoad     = 5,  // open load
  eCddLed_ErrShortToGnd   = 6,  // short to GND
  eCddLed_ErrShortToUbat  = 7,  // short to Ubat
  eCddLed_ErrUnderVoltage = 8,  // voltage of LED string too low
  eCddLed_ErrOverVoltage  = 9,  // voltage of LED string too high
  eCddLed_ErrThermShutdn  = 10,  // thermal shutdown
  eCddLed_ErrOverCurrent  = 11,  // overcurrent
  eCddLed_ErrSpi          = 12   // SPI error
} tCddLedErrStatus;


// channel status (on/off)
typedef enum
{
  eCddLed_ChnUndef = 0,  // state not clear
  eCddLed_ChnOff   = 1,  // clearly off
  eCddLed_ChnOn    = 2   // clearly on
} tCddLedChnStatus;

// input voltage status (measured booster voltage)
typedef enum
{
  eCddLed_VinUndef = 0,  // input voltage state unknown
  eCddLed_VinLo    = 1,  // input voltage low
  eCddLed_VinOk    = 2,  // input voltage ok
  eCddLed_VinHi    = 3   // input voltage high
} tCddLedVinStatus;

// temperature information
typedef struct
{
  boolean boThermalWarning;  // thermal warning indication
} tCddLedTempData;

// buck status
typedef struct
{
  uint16           unVLed;       // LED voltage
  tCddLedErrStatus Err;          // error status
  tCddLedChnStatus Chn;          // channel ststus (on/off status)
  tCddLedVinStatus Vin;          // buck input voltage status (this is the booster voltage in typical projects)
  tCddLedTempData  TempData;     // temperature information
  uint16           unActVin;     // actual buck input voltage value
  uint16           unActDuty;    // actual duty cycle
  uint16           unActCurrent; // actual LED current
} tCddLedStatusVal;

// full status (all channels)
typedef struct
{
  tCddLedStatusVal aStatus[CDDLED_Cfg_NbOfChannels];
} tCddLedStatus;

// driver settings to disable specific error types
typedef struct
{
uint32 ulDisableErrShortToGnd;
uint32 ulDisableErrOpenLoad;
uint32 ulDisableErrShortToUbat;
uint32 ulDisableErrUnderVoltage;
uint32 ulDisableErrOverVoltage;
uint32 ulDisableErrThermalShutdown;
uint32 ulDisableErrOverCurrent;
uint32 ulDisableErrSpi;
uint32 ulDisableErrE2E;
}tCddLedDriverSettings;

// target values
typedef struct
{
  uint16 unCurrent_mA;
  uint16 unDutyCycle_1_32768;
}tCddLedTargetVal;

// target values (all channels)
typedef struct
{
  tCddLedTargetVal aTarget[CDDLED_Cfg_NbOfChannels];
} tCddLedTarget;


//-----------------------------------------------------------------------------
// Start declaration or definitions of functions
//-----------------------------------------------------------------------------
#define ctadCddLed_START_SEC_CODE
#include <../Cfg/CddLed_MemMap.h>

void   CddLed_Init          (void);
void   CddLed_SetPara       (boolean boValid);
void   CddLed_Cycle20ms     (void);
void   CddLed_DriverSettings(tCddLedDriverSettings* pSettings);
void   CddLed_SetTarget     (tCddLedTarget*         pTarget);
void   CddLed_GetStatus     (tCddLedStatus*         pStatus);

#define ctadCddLed_STOP_SEC_CODE
#include <../Cfg/CddLed_MemMap.h>
//-----------------------------------------------------------------------------
// End declaration or definitions of functions
//-----------------------------------------------------------------------------

#endif // CDD_LED_2021_03_02_H_
