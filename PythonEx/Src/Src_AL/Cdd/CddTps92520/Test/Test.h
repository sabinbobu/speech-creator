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
#include "AL_Helper.h"

// Headers of the Module
#include <CddTps92520.h>
#include <CddTps92520_Cb.h>
#include <../Gen/CddTps92520_Com.h>
#include <../Cfg/CddTps92520_Cfg.h>
#include <../Cfg/CddTps92520_RoutCfg.h>
#include <../Gen/CddTps92520_Sched.h>

//=============================================================================
// Typedefs
//=============================================================================


//=============================================================================
// Defines
//=============================================================================
#define TEST_ChannelMask     0x0Fu  // default mask for testing
#define TEST_Chip0              0u  // chip numbers
#define TEST_Chip1              1u
#define TEST_Chip2              2u
#define TEST_Chip3              3u
#define TEST_Chip4              4u
#define TEST_Chip5              5u
#define TEST_ChipIdx0           0u  // index numbers within chip
#define TEST_ChipIdx1           1u
#define TEST_Chn0               0u  // LED channel numbers
#define TEST_Chn1               1u
#define TEST_Chn2               2u
#define TEST_Chn3               3u
#define TEST_ChnIllegal        12u
#define TEST_EftDisabled        0u  // Eft settings for enabling/disabling chips/channels
#define TEST_EftEnabled         1u

#define AD_Range  64.61f   // [V]

//=============================================================================
// Module global variables
//=============================================================================
extern uint16  CddTps92520_aunTgtDutyCycle[CDDTPS92520_CFG_NO_OF_CHANNELS];  // target duty cycle
extern uint16  CddTps92520_aunTgtCurrent[CDDTPS92520_CFG_NO_OF_CHANNELS];  // target current
extern boolean CddTps92520_aboMultiLed[CDDTPS92520_CFG_NO_OF_CHANNELS];  // indication of string with at least 2 LEDs
extern uint16  CddTps92520_aunInputVoltage[CDDTPS92520_CFG_NO_OF_CHANNELS];  // buck input (typ. booster) voltage
extern uint16  CddTps92520_aunLedVoltage[CDDTPS92520_CFG_NO_OF_CHANNELS];  // LED string voltage
extern uint16  CddTps92520_unSchedIx;
extern tCddTps92520_DataMirror CddTps92520_DataMirror;

extern boolean  CddTps92520_aboEnable[CDDTPS92520_CFG_NO_OF_CHANNELS];
extern boolean  CddTps92520_aboDriverActiveStatus[CDDTPS92520_CFG_NO_OF_CHANNELS];
extern boolean  CddTps92520_aboOpenLoadStatus[CDDTPS92520_CFG_NO_OF_CHANNELS];
extern boolean  CddTps92520_aboShortToGndStatus[CDDTPS92520_CFG_NO_OF_CHANNELS];
extern boolean  CddTps92520_aboOvercurrentStatus[CDDTPS92520_CFG_NO_OF_CHANNELS];
extern boolean  CddTps92520_aboThermalShtDwnStatus[CDDTPS92520_CFG_NO_OF_CHANNELS];
extern boolean  CddTps92520_aboThermalWarningStatus[CDDTPS92520_CFG_NO_OF_CHANNELS];

//=============================================================================
// Module function declarations
//=============================================================================
extern uint16 CddTps92520_RawToMillivolt(const uint32 ulRaw);
extern void   CddTps92520_MeasureInputVoltage(void);
extern void   CddTps92520_MeasureLedVoltage(void);
extern uint16 CddTps92520_CalcCHxIADJ(const uint32 ulChnIdx, const uint16 unCurrent);
extern uint16 CddTps92520_CalcAndAddParity(const uint16 unCmd, const uint16 unAddr, const uint16 unData);


//=============================================================================
// Module function parameter stubs
//=============================================================================


//=============================================================================
// Module function return value stubs
//=============================================================================


#endif // TEST_2023_08_25_H_
