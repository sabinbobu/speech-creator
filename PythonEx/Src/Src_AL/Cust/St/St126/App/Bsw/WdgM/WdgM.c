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
/// \file   WdgM.c
///
/// \brief  Watchdog manager
///
/// \descr  WdgM is responsible for handle the watchdog and corresponding tests
///
/// \author Cretu Vladut-Ioan
///         mailTo:vladut-ioan.cretu[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#include <Wdg.h>
#include <Std_Types.h>
#include <AL_Helper.h>
#include "WdgM_Types.h"
#include "WdgM.h"
#ifndef UNIT_TEST
#include <CddSbc.h>
#include <Lpit.h>
#endif

////=============================================================================
//// defines
////=============================================================================

#define WDM_TIMER_TRIGGER_TIME_MS 100u
#define WDGM_LOW_TIME_ACCEPTANCE_TIME_MS 80u
#define WDGM_HIGH_TIME_ACCEPTANCE_TIME_MS 120u

#define WDGM_ERROR_INCERMENT  10u
#define WDGM_ERROR_DECREMENT  1u
#define WDGM_ERROR_CNT_MAX    255u
#define WDGM_ERROR_CNT_MIN    0u

#if (CFG_DEV_HOOK_EN == 1u) || defined (UNIT_TEST)
#define WDGM_HOOK_ENABLE  20212022u
#if !defined (UNIT_TEST)
#define WDGM_SHA_DATA_WDG_SPECIAL_HOOK_ENBL_VAL     *(volatile uint16*)0x20002F54u
#define WDGM_SHA_DATA_WDG_SPECIAL_HOOK_CNT_VAL      *(volatile uint16*)0x20002F58u
#else
STATIC_AL uint16 WdgM_unEmulate_SpecialHook_Enbl_Var = 0u;
STATIC_AL uint16 WdgM_unEmulate_SpecialHook_Cnt_Var  = 0u;
#define WDGM_SHA_DATA_WDG_SPECIAL_HOOK_ENBL_VAL     WdgM_unEmulate_SpecialHook_Enbl_Var
#define WDGM_SHA_DATA_WDG_SPECIAL_HOOK_CNT_VAL      WdgM_unEmulate_SpecialHook_Cnt_Var
#endif
#endif

#ifndef UNIT_TEST
#define WDGM_SHA_DATA_WDG_RESET_REASON_ADR     *(volatile uint16*)0x20002F46u
#else
extern uint32 ulWdgM_Sha_Data_address_Reset_Reason;
#define WDGM_SHA_DATA_WDG_RESET_REASON_ADR  ulWdgM_Sha_Data_address_Reset_Reason
#endif
#define WDGM_SHA_DATA_WDG_RESET_REASON_VAL     0x5A01u
#define WDGM_SHA_DATA_WDG_NORESET_REASON_VAL   0xA5FEu



//=============================================================================
// variables
//=============================================================================

STATIC_AL uint32 WdgM_ulErrorStatus = 0u;
STATIC_AL boolean WdgM_boTriggerStatus = TRUE;
#if (CFG_DEV_HOOK_EN == 1u) || defined (UNIT_TEST)
STATIC_AL volatile uint32 WdgM_ResetHookActivation = 0u;
#endif

//=============================================================================
// functions
//=============================================================================

STATIC_AL void WdgM_Trigger(void);
STATIC_AL void WdgM_ResetTrigger(void);

// Watchdog checkponts definition
STATIC_AL tsWdgM_CheckPoint WdgM_asCheckPointsList[] =
{
  // SysMonRx CheckPoint
  {0x0u,    10u,    0u},
  // EcuM CheckPoint
  {0x1u,    1u,     0u}
};

//-----------------------------------------------------------------------------
/// \brief WdgM_SetLocalCheckPoint
///
/// \descr Update checkpoint counter
///
/// \param  ucId - checkpoint Id
///
/// \return void
//-----------------------------------------------------------------------------
void WdgM_SetLocalCheckPoint(uint8 ucId)
{
  // Update Checkpoint counter
  WdgM_asCheckPointsList[ucId].uctHitCount++;
}


//-----------------------------------------------------------------------------
/// \brief WdgM_EntitySupervision
///
/// \descr Entity supervision of wdg manager
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void WdgM_EntitySupervision(void)
{
  // Entity index (checkpoint)
  uint8_least ucIndx = 0u;
  // First call of WdgM cycle (counter error suppresion for first cycle call) 
#ifndef UNIT_TEST
  static boolean boFirstCallWdgCycleStatus = TRUE;
#else
  extern  boolean boFirstCallWdgCycleStatus;
#endif // !UNIT_TEST

  // Not the first call of WdgM
  if (boFirstCallWdgCycleStatus == FALSE)
  {
    // Check the checkpoints
    for (ucIndx = 0u; ucIndx < sizeof(WdgM_asCheckPointsList) / sizeof(WdgM_asCheckPointsList[0]); ucIndx++)
    {
      // Is the checkpoint counter not in range
      if ((WdgM_asCheckPointsList[ucIndx].uctHitCount < WDGM_LOW_TIME_ACCEPTANCE_TIME_MS / WdgM_asCheckPointsList[ucIndx].ucEntityCycleMs) ||
         (WdgM_asCheckPointsList[ucIndx].uctHitCount > WDGM_HIGH_TIME_ACCEPTANCE_TIME_MS / WdgM_asCheckPointsList[ucIndx].ucEntityCycleMs))
      {
        // Increment the error
        WdgM_ulErrorStatus = ((WdgM_ulErrorStatus + WDGM_ERROR_INCERMENT) < WDGM_ERROR_CNT_MAX) ? WdgM_ulErrorStatus + WDGM_ERROR_INCERMENT : WDGM_ERROR_CNT_MAX;
      }
      else
      {
        // Decrement the error
        WdgM_ulErrorStatus = (WdgM_ulErrorStatus > WDGM_ERROR_CNT_MIN) ? WdgM_ulErrorStatus - WDGM_ERROR_DECREMENT : WDGM_ERROR_CNT_MIN;
      }

      // Reset the hitcount of current checkpoint
      WdgM_asCheckPointsList[ucIndx].uctHitCount = 0u;
    }
  }
  else
  {
    // First Call status changed to False
    boFirstCallWdgCycleStatus = FALSE;

    // Reset all hitcount counters to 0
    for (ucIndx = 0u; ucIndx < sizeof(WdgM_asCheckPointsList) / sizeof(WdgM_asCheckPointsList[0]); ucIndx++)
    {
      WdgM_asCheckPointsList[ucIndx].uctHitCount = 0u;
    }
  }
}

//-----------------------------------------------------------------------------
/// \brief WdgM_Init
///
/// \descr Wdg manager init runnable
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void WdgM_Init(void)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief WdgM_Cycle0
///
/// \descr Wdg manager cyclic runnable
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void WdgM_Cycle0(void)
{
  // Hook for Watchdog reset (activation)

#if (CFG_DEV_HOOK_EN == 1u) || defined (UNIT_TEST)
  // PRQA S 303 WDG_HOOK_MEM_ACCESS // direct memory access
  if (WdgM_ResetHookActivation == WDGM_HOOK_ENABLE)
  {

    WDGM_SHA_DATA_WDG_SPECIAL_HOOK_ENBL_VAL = (uint16)0x5A01u;
    WDGM_SHA_DATA_WDG_SPECIAL_HOOK_CNT_VAL = 0u;

    // Reset Hook variable
    WdgM_ResetHookActivation = 0u;
    // stuck code hook
#ifndef UNIT_TEST
    WdgM_ResetTrigger();
#endif
  }

  if ((WDGM_SHA_DATA_WDG_SPECIAL_HOOK_ENBL_VAL == (uint16)0x5A01u) && (WDGM_SHA_DATA_WDG_SPECIAL_HOOK_CNT_VAL < 10u))
  {
    WDGM_SHA_DATA_WDG_SPECIAL_HOOK_CNT_VAL = WDGM_SHA_DATA_WDG_SPECIAL_HOOK_CNT_VAL + 1u;

#ifndef UNIT_TEST
    WdgM_ResetTrigger();
#endif
  }
  else if ((WDGM_SHA_DATA_WDG_SPECIAL_HOOK_ENBL_VAL == (uint16)0x5A01u) && (WDGM_SHA_DATA_WDG_SPECIAL_HOOK_CNT_VAL >= 10u))
  {
    WDGM_SHA_DATA_WDG_SPECIAL_HOOK_ENBL_VAL = 0u;
    WDGM_SHA_DATA_WDG_SPECIAL_HOOK_CNT_VAL = 0u;
  }
  else
  {
    //skip
  }
  // PRQA L: WDG_HOOK_MEM_ACCESS
#endif
  
  // Set global semaphore to detect WdgM stuck in execution
  WdgM_boTriggerStatus = FALSE;
  // Supervision of sw entities
  WdgM_EntitySupervision();
}

//-----------------------------------------------------------------------------
/// \brief  Trigger the watchdog
///
/// \descr  Trigger the SBC wathdog window mode
///
/// \param  void 
///
/// \return void 
//-----------------------------------------------------------------------------
STATIC_AL void WdgM_Trigger(void)
{
  // Call SBC driver for a watchdog trigger
  CddSbc_SetWdgWindowModeAnd200ms();
}


//-----------------------------------------------------------------------------
/// \brief LPIT0_Ch1_IRQHandler
///
/// \descr lpit 0 ch1 ISR handler with 180ms cyclic time
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void LPIT0_Ch1_IRQHandler(void)
{
  // Clear timer interrupt flag
  Lpit_ClearInterruptFlag(0u, 1u);

  // Check the Global Error status and the semaphore (WdgM cycle stuck execution)
  if ((WdgM_ulErrorStatus < WDGM_ERROR_CNT_MAX) && (WdgM_boTriggerStatus == FALSE))
  {
    // Watchdog trigger
    WdgM_Trigger();
  }
  else
  {
    // write Share data memory patern for external watchdog reset reason
    // PRQA S 303 1 // program architecture and readability - Cast between a pointer to volatile object and an integral type wanted and documented
    WDGM_SHA_DATA_WDG_RESET_REASON_ADR = WDGM_SHA_DATA_WDG_RESET_REASON_VAL;
  }

  // Set trigger status as true
  WdgM_boTriggerStatus = TRUE;
}

#if  !defined (UNIT_TEST) && (CFG_DEV_HOOK_EN == 1u)
//-----------------------------------------------------------------------------
/// \brief WdgM_ResetTrigger
///
/// \descr Infinite loop for watchdog error detection
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
// PRQA S 3006 1 // program architecture and readability - while (1) no sens optimization avoided
STATIC_AL void WdgM_ResetTrigger(void)
{
  while (1)
  {
    __asm volatile ("nop");
  }
}

#endif // !UNIT_TEST / CFG_DEV_HOOK_EN

//-----------------------------------------------------------------------------
/// \brief WdgM_ResetShaDataResetReason
///
/// \descr Share data memory reset reason clear
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void WdgM_ResetShaDataResetReason(void)
{
  // PRQA S 303 1 // program architecture and readability - Cast between a pointer to volatile object and an integral type wanted and documented
  WDGM_SHA_DATA_WDG_RESET_REASON_ADR = WDGM_SHA_DATA_WDG_NORESET_REASON_VAL;
}

// EOF
