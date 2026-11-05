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

//=============================================================================
// Typedefs
//=============================================================================
typedef struct
{
  uint8 ucEntityId;
  uint8 ucEntityCycleMs;
  uint8 uctHitCount;
}tsWdgM_CheckPoint;

//=============================================================================
// Defines
//=============================================================================
#define WDGM_ERROR_CNT_MAX    255u
#define WDGM_SHA_DATA_WDG_RESET_REASON_ADR     *(volatile uint16*)0x20002F46
#define WDGM_SHA_DATA_WDG_RESET_REASON_VAL     0x5A01u
#define WDGM_SHA_DATA_WDG_NORESET_REASON_VAL   0xA5FEu
#define WDGM_LOW_TIME_ACCEPTANCE_TIME_MS WdgM_Low_Time_Acceptance_Time
#define WDGM_HOOK_ENABLE  20212022

//=============================================================================
// Module global variables
//=============================================================================
extern uint32            WdgM_ulErrorStatus;
extern boolean           WdgM_boTriggerStatus;
extern volatile uint32   WdgM_ResetHookActivation;
extern tsWdgM_CheckPoint WdgM_asCheckPointsList[];
extern uint16 WdgM_unEmulate_SpecialHook_Enbl_Var;
extern uint16 WdgM_unEmulate_SpecialHook_Cnt_Var;

//=============================================================================
// Module function declarations
//=============================================================================
extern void riWdgM_Init(void);
extern void rpWdgM_Cycle0(void);
extern void WdgM_EntitySupervision(void);
extern void WdgM_Trigger(void);
extern void WdgM_SetLocalCheckPoint(uint8 ucId);
extern void WdgM_Init(void);
extern void WdgM_Cycle0(void);
extern void LPIT0_Ch1_IRQHandler(void);
extern void WdgM_ResetShaDataResetReason(void);

//=============================================================================
// Module function parameter stubs
//=============================================================================
uint8   WdgM_SetLocalCheckPoint_Param1;
uint32  ulWdgM_Sha_Data_address_Reset_Reason;

//=============================================================================
// Module static variables inside functions
//=============================================================================
boolean boFirstCallWdgCycleStatus;

#endif // TEST_2023_08_25_H_
