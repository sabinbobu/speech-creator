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
/// \file  Test.h
///
/// \brief This file contains functions prototypes of the tested module, 
///        including functions parameters and global variables
///
//-----------------------------------------------------------------------------
#ifndef TEST_2023_08_25_H_
#define TEST_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>

// Headers of the Module
#include <CddLed.h>
#include <../Gen/CddLed_Types.h>
#include <../Cfg/CddLed_Cfg.h>
#include <../Cfg/CddLed_RoutCfg.h>

//=============================================================================
// Typedefs
//=============================================================================

//=============================================================================
// Defines
//=============================================================================
#define TEST_Chn0               0u  // LED channel numbers
#define TEST_Chn1               1u
#define TEST_Chn2               2u
#define TEST_Chn3               3u

//=============================================================================
// Module global variables
//=============================================================================
extern tCddLedTarget         CddLed_sTarget;      // current and duty for LEDs
extern tCddLedDriverSettings CddLed_Settings;     // conditions needed for proper driver operation

extern uint32  CddLed_ulAvailMask;  // mask indicating availability of channels
extern boolean CddLed_aboThermShutDn[CDDLED_Cfg_NbOfChannels];  // state of thermal shutdown fault
extern boolean CddLed_aboOverCurrent[CDDLED_Cfg_NbOfChannels];  // state of overcurrent fault
extern uint8   CddLed_aucThermShutDn[CDDLED_Cfg_NbOfChannels];  // debounce counter for thermal shutdown fault
extern uint8   CddLed_aucOverCurrent[CDDLED_Cfg_NbOfChannels];  // debounce counter for overcurrent fault
extern uint8   CddLed_aucOffCounter[CDDLED_Cfg_NbOfChannels];  // counter to use for measurement delay in ShotToUbat
extern uint16  CddLed_aunInputVoltage[CDDLED_Cfg_NbOfChannels];  // buck input voltages
extern uint16  CddLed_aunLedVoltage[CDDLED_Cfg_NbOfChannels];  // actual LED voltage
extern uint16  CddLed_aunErrorList[CDDLED_Cfg_NbOfChannels];  // list of error details

extern uint16  CddLed_unInputVoltThreshold;  // minimum input voltage
extern uint32  CddLed_ulShortUbatMask;       // mask indicating active ShortToUbat measurement
extern uint32  CddLed_ulOnMask;              // bitmask to store ON/OFF state

#ifdef CDDLED_Cfg_Simulation
extern volatile tCddLed_Simulation_Data CddLed_Simulation_Data;
#endif

//=============================================================================
// Module function declarations
//=============================================================================
extern void    CddLed_EvaluateElectricalErrors(const uint32 ul);
extern void    CddLed_EvaluateInternalErrors(const uint32 ul);
extern void    CddLed_EvaluateLedVoltage(const uint32 ul);
extern void    CddLed_EvaluateAuxVoltages(const uint32 ul);
extern void    CddLed_CreateErrStatus(const uint32 ul, tCddLedStatus* const pStatus);
extern void    CddLed_CreateChnStatus(const uint32 ul, tCddLedStatus* const pStatus);
extern void    CddLed_CreateAuxStatus(const uint32 ul, tCddLedStatus* const pStatus);
extern boolean CddLed_DebounceOvercurrent(const uint32 ul, boolean boState);
extern boolean CddLed_DebounceThermShutDn(const uint32 ul, boolean boState);


//=============================================================================
// Module function parameter stubs
//=============================================================================

//=============================================================================
// Module function return value stubs
//=============================================================================

//=============================================================================
// Module static variables inside functions 
//=============================================================================

//=============================================================================
// Global variable stubs
//=============================================================================
tCddLedStatus Test_Status;

#endif // TEST_2023_08_25_H_
