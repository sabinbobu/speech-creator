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
/// \file  CddLed_Types.h
///
/// \brief
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef CDD_LED_TYPES_2021_12_13_H_
#define CDD_LED_TYPES_2021_12_13_H_


#include <Std_Types.h>
#include <../Cfg/CddLed_Cfg.h>


//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
// simulation interface (activated by compiler switch only)
#define CDDLED_SimulationPassword     0xC0DE1234u
#define CDDLED_SimulationDeactivated  0xDEADC0DEu


// bit positions for error storage
#define CDDLED_ErrListStart    0u  // start for searching
#define CDDLED_ThermShutdn     0u  //    ^    high
#define CDDLED_OverCurrent     1u  //  / | \   |
#define CDDLED_ShortToGnd      2u  //    |    priority
#define CDDLED_OpenLoad        3u  //    |     |
#define CDDLED_UnderVoltage    4u  //    |     |
#define CDDLED_OverVoltage     5u  //    |    low
#define CDDLED_ErrListStop     5u  // end for searching

#define CDDLED_ShortToUbat     6u  // ShortToUbat to handle separately
#define CDDLED_NotOffVoltage   7u  // voltage above OFF state
#define CDDLED_InputVoltLow    8u  // input voltage too low
#define CDDLED_ThermWarning    9u  // thermal warning
#define CDDLED_DriverInactive 10u  // indicating driver not in regulaton mode
#define CDDLED_NoSupport      11u  // not supported due to EFT data

// List of enums according to priority list above
#define CDDLED_InitErrList { eCddLed_ErrThermShutdn, eCddLed_ErrOverCurrent,  eCddLed_ErrShortToGnd, \
                             eCddLed_ErrOpenLoad,    eCddLed_ErrUnderVoltage, eCddLed_ErrOverVoltage }

#define CDDLED_Mask_16(x)      ((uint16)  ((uint32)1u << (x)) )  // "1" at bit position
#define CDDLED_Mask_32(x)      ((uint32)           1u << (x))    // "1" at bit position


//-----------------------------------------------------------------------------
// Types
//-----------------------------------------------------------------------------
// simulation interface (activated by compiler switch only)
typedef struct
{
  uint32 ulSimActivated;
  uint32 ulSimThermalShutdown;
  uint32 ulSimThermalWarning;
  uint32 ulSimOverCurrent;
  uint32 ulSimSpiError;
  uint16 aunSimVBoostMeas[CDDLED_Cfg_NbOfChannels];
}
tCddLed_Simulation_Data;


#endif // CDD_LED_TYPES_2021_12_13_H_
