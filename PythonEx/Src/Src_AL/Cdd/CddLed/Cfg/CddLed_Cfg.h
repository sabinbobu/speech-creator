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
/// \file  CddLed_Cfg.h
///
/// \brief
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef CDD_LED_CFG_2021_03_02_H_
#define CDD_LED_CFG_2021_03_02_H_


//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

// number of LED channels
#define CDDLED_Cfg_NbOfChannels       12u

// simulation support
#define CDDLED_Cfg_Simulation

// voltage thresholds
#define CDDLED_Cfg_OffVoltThresh       2250u  // [mV] voltage threshold to detect OFF state
#define CDDLED_Cfg_ShortBatOffTime      360u  // [ms] time between 2 ON cycles to do ShortToVbat detection (360 instead of 350 for rounding effects)

// debouncing
#define CDDLED_Cfg_ThermShutdnDebounce  100u  // [ms] time for validation of thermal shutdown fault


#endif // CDD_LED_CFG_2021_03_02_H_
