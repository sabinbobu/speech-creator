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
#include <Swc/StatM/StatM.h>
#include <Swc/StatM/ctaaStatM.h>

//=============================================================================
// Typedefs
//=============================================================================

typedef uint16  NvM_BlockIdType;

//=============================================================================
// Defines
//=============================================================================

#define STATM_MAX_LED_CHN            12u
#define STATM_MAX_FAN_NR              2u
#define STATM_MAX_TEMP_ZONES         12u
#define STATM_TEMP_CLASSES            6u
#define STATM_NR_BUCKS                6u

#define STATM_CYCLES_IN_1S           10u
#define STATM_CYCLES_IN_10S          100u
#define UINT32_MAX                   4294967295U
#define UINT16_MAX                   65535u

#define STATM_STACK_INIT             0xFFFFu

#define STATM_LED_CHN                4u

#define STATM_TEMP_0                 0
#define STATM_TEMP_70                700
#define STATM_TEMP_90                900
#define STATM_TEMP_110               1100
#define STATM_TEMP_130               1300

#define STATM_ZONES                  12u

#define STATM_READ_FROM_NVM   TRUE

#define STATM_ENDOFSTACK_PATTERN_1   0xA5u
#define STATM_ENDOFSTACK_PATTERN_2   0x2Eu
#define STATM_ENDOFSTACK_PATTERN_3   0x5Au
#define STATM_ENDOFSTACK_PATTERN_4   0xE2u
#define STATM_NOTUSEDSTACK_PATTERN   0xCCu

#define STATM_STACK_INVALID          0xFFFEu

//=============================================================================
// Module global variables
//=============================================================================

// StatM.c
extern boolean StatM_boMeasureStack;
extern uint16 StatM_unUnusedStackTrusted_HH;
extern uint16 StatM_unUnusedStackUntrusted_HH;
extern uint16 StatM_unUnusedStackTrusted_percent_HH;
extern uint16 StatM_unUnusedStackUntrusted_percent_HH;
extern uint16 StatM_unUnusedStackTrusted_HL;
extern uint16 StatM_unUnusedStackUntrusted_HL;
extern uint16 StatM_unUnusedStackTrusted_percent_HL;
extern uint16 StatM_unUnusedStackUntrusted_percent_HL;
extern uint16 StatM_unUnusedStackTrusted_LH;
extern uint16 StatM_unUnusedStackUntrusted_LH;
extern uint16 StatM_unUnusedStackTrusted_percent_LH;
extern uint16 StatM_unUnusedStackUntrusted_percent_LH;
extern uint16 StatM_unUnusedStackTrusted_LL;
extern uint16 StatM_unUnusedStackUntrusted_LL;
extern uint16 StatM_unUnusedStackTrusted_percent_LL;
extern uint16 StatM_unUnusedStackUntrusted_percent_LL;
extern tstStatistics StatM_stStat;

//=============================================================================
// Module function declarations
//=============================================================================

// StatM.c
extern void StatM_Init(void);
extern void StatM_Cycle0(void);
extern void StatM_Deinit(void);
extern void StatM_ResetStatistics(void);
extern void StatM_ReadStatistics(tstStatistics *pstStats, boolean boFromNvM);
extern void StatM_WriteStatistics(void);

extern  void StatM__vEcuTimeProcessing(void);
extern  void StatM__vLedTimeProcessing(void);
#if defined CFG_VARIANT_FULL || defined(UNIT_TEST)
extern void StatM__vFanTimeProcessing(void);
extern void StatM__vStpTimeProcessing(void);
#endif
extern void StatM__vTempTimeProcessing(void);
extern void StatM__vTempClassProcessing(tsRte_PcbTemperatureMsg sTemp, uint8 *ucTempTime, uint32 *ulStatTempTime);
extern void StatM__vErrorCountersProcessing(void);

extern void StatM__vStackSizeMeasurement(void);
extern void StatM__vFanTimeProcessing(void);
extern boolean StatM__boCheckPatern(uint32 ulAddress);
extern uint16 StatM__unGetNumberFreeBytes(uint32 ulStartAdd, uint32 ulEndAdd);

//ctaaStatM
extern void riStatM_Init(void);
extern void rcStatM_Cycle10ms(void);
extern void reStatM_Deinit(void);
extern void reStatM_ResetStatistics(void);

//=============================================================================
// Module function parameter stubs
//=============================================================================

tsRte_PcbTemperatureMsg StatM__vTempClassProcessing_Param1;
uint8  StatM__vTempClassProcessing_Param2[STATM_TEMP_CLASSES];
uint32 StatM__vTempClassProcessing_Param3[STATM_TEMP_CLASSES];
tstStatistics *StatM_ReadStatistics_Param1;
boolean StatM_ReadStatistics_Param2;
uint32 StatM__boCheckPatern_Param1;
uint32 StatM__unGetNumberFreeBytes_Param1;
uint32 StatM__unGetNumberFreeBytes_Param2;

//=============================================================================
// Module function return value stubs
//=============================================================================

boolean StatM__boCheckPatern_RetVal;
uint16 StatM__unGetNumberFreeBytes_RetVal;

//=============================================================================
// Module static variables inside functions 
//=============================================================================

uint8 ucEcuOnTime;
uint8 ucLedOnTime[STATM_LED_CHN] = { 0u, 0u, 0u, 0u };
uint8 ucFan1OnTime;
uint8 ucFan2OnTime;
boolean  StatM_boWasMoving;
boolean  StatM_boStepLoss;
uint8 StatM_ucMoveTime;
uint8 StatM_ucHoldTime;

uint8 ucTempPCBTime[STATM_TEMP_CLASSES] = { 0u, 0u, 0u, 0u, 0u, 0u };
uint8 ucTempZoneTime[STATM_ZONES][STATM_TEMP_CLASSES] = {
    { 0u, 0u, 0u, 0u, 0u, 0u },
{ 0u, 0u, 0u, 0u, 0u, 0u },
{ 0u, 0u, 0u, 0u, 0u, 0u },
{ 0u, 0u, 0u, 0u, 0u, 0u },
{ 0u, 0u, 0u, 0u, 0u, 0u },
{ 0u, 0u, 0u, 0u, 0u, 0u },
{ 0u, 0u, 0u, 0u, 0u, 0u },
{ 0u, 0u, 0u, 0u, 0u, 0u },
{ 0u, 0u, 0u, 0u, 0u, 0u },
{ 0u, 0u, 0u, 0u, 0u, 0u },
{ 0u, 0u, 0u, 0u, 0u, 0u },
{ 0u, 0u, 0u, 0u, 0u, 0u }
};
uint8 StatM_ucTimeCount_stack;

#endif // TEST_2023_08_25_H_
