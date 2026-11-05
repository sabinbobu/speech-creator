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
/// \file  Wdg.c
///
/// \brief Source file for Internal Wdg module.
///
/// \author Cretu Vladut-Ioan, ALRO-CJ
//-----------------------------------------------------------------------------
//=============================================================================
// Includes
//=============================================================================
#include <Wdg.h>
#include "Wdg_hw_access.h"
#include <interrupt_manager.h>
#include <Std_Types.h>
#include <AL_Helper.h>
//=============================================================================
// Private Macros
//=============================================================================
/// Watchdog used instance
#define WDG_INSTANCE          ((uint32) 0)

/// The 32-bit value used for resetting the WDOG counter
#define WDG_TRIGGER_VALUE           ((uint32)0xB480A602U)

/// The minimum value of the timeout register
#define WDG_MINIMUM_TIMEOUT_VALUE   ((uint16)0x0U)

//-----------------------------------------------------------------------------
/// \brief  Watchdog Timer Hardware Access
///         Provides low-level access to all hardware features of the WDG.
/// \param  base: WDG base pointer
/// \retval None
/// \note   The dummy read is used in order to make sure that any write to the
///         WDG registers will be started only after the write of the unlock
///         value was completed.
//-----------------------------------------------------------------------------
#define WDG_UNLOCK(base)    \
{ \
  (base)->CNT = WDG_UNLOCK_VALUE; \
  (void)(base)->CNT; \
}
//=============================================================================
// Private Variables
//=============================================================================
// Constant used to store the base address of the Watchdog configuration
// registers
// PRQA S 306  1 // pointer cast needed. Peripheric source address is needed
STATIC_AL WDOG_Type* Wdg_asBaseAddrPtr[WDOG_INSTANCE_COUNT] = { (WDOG_Type*)WDOG_BASE };
// Variable which will store the configuration for the watchdog
STATIC_AL uint32 Wdg_ulControlStatusReg = 0u;
// Variable which will store the value of the counter registers
STATIC_AL uint16 Wdg_ulCounterReg = 0u;


//=============================================================================
// Exported Variables
//=============================================================================

//=============================================================================
// Private Functions Declaration
//=============================================================================


//=============================================================================
// Functions
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief  Configures all WDOG registers.
/// \param  tsTimeoutPtr: contains the configuration of Wdg
/// \retval WDG_ERR_NO in case of success; a proper error value otherwise
//-----------------------------------------------------------------------------
void Wdg_Init(Wdg_InstanceType* tsTimeoutPtr)
{
    uint32 ulRegTemp = 0u;

    // Disable global interrupt
    INT_SYS_DisableIRQGlobal();

    // Variable used to configure Control and Status register
    Wdg_ulControlStatusReg =  WDOG_CS_STOP(tsTimeoutPtr->uControlStatus_Reg.sCtrlSts_Reg.bOpMode_Stop) |
                              WDOG_CS_WAIT(tsTimeoutPtr->uControlStatus_Reg.sCtrlSts_Reg.bOpMode_Wait) | 
                              WDOG_CS_DBG(tsTimeoutPtr->uControlStatus_Reg.sCtrlSts_Reg.bOpMode_Dbg)   |
                              WDOG_CS_TST(tsTimeoutPtr->uControlStatus_Reg.sCtrlSts_Reg.bTest)         |
                              WDOG_CS_UPDATE(tsTimeoutPtr->uControlStatus_Reg.sCtrlSts_Reg.bUpdateEnable) |
                              WDOG_CS_INT(tsTimeoutPtr->uControlStatus_Reg.sCtrlSts_Reg.bInterruptEnable) |
                              WDOG_CS_EN(tsTimeoutPtr->uControlStatus_Reg.sCtrlSts_Reg.bWdgEnable)     |
                              WDOG_CS_CLK(tsTimeoutPtr->uControlStatus_Reg.sCtrlSts_Reg.bClockSource)  |
                              WDOG_CS_PRES(tsTimeoutPtr->uControlStatus_Reg.sCtrlSts_Reg.bPrescaler)   |
                              WDOG_CS_CMD32EN(tsTimeoutPtr->uControlStatus_Reg.sCtrlSts_Reg.bCMD32EN)  | 
                              WDOG_CS_FLG(tsTimeoutPtr->uControlStatus_Reg.sCtrlSts_Reg.bFlg)          |
                              WDOG_CS_WIN(tsTimeoutPtr->uControlStatus_Reg.sCtrlSts_Reg.bWinEnable );

    // Put the counter value in the total value reg
    Wdg_ulCounterReg = tsTimeoutPtr->uTimeout_Value_Reg.sTotal_Counter_Register.bTOVAL_VALUE;
      
    // Set the unlock sequence
    Wdg_asBaseAddrPtr[WDG_INSTANCE]->CNT = 0xD928C520u;

    //Wait until watchdog is unlocked
    while (ulRegTemp == 0u)
    {
      ulRegTemp = Wdg_asBaseAddrPtr[WDG_INSTANCE]->CS & (uint32)((uint32)1 << 11u);
    }

    // Copy the configuration to Control Status reg
    Wdg_asBaseAddrPtr[0u]->CS  = Wdg_ulControlStatusReg;

    // Set timeout
    Wdg_SetTimeout(Wdg_ulCounterReg);

    // Enable global interrupt
    INT_SYS_EnableIRQGlobal();
}

//-----------------------------------------------------------------------------
/// \brief  Set time value of the WDG timeout
/// \param  timeout: value of the WDG timeout
/// \return This function returns nothing.
/// \retval None
//-----------------------------------------------------------------------------
void Wdg_SetTimeout(uint16 unTimeout)
{
  // Unlock watchdog to access registers
  WDG_UNLOCK(Wdg_asBaseAddrPtr[WDG_INSTANCE]);
  // Set watchdog timout value
  Wdg_asBaseAddrPtr[WDG_INSTANCE]->TOVAL = unTimeout;
}

//-----------------------------------------------------------------------------
/// \brief  Get the value of the WDG counter
/// \return This function returns the value of the WDG counter.
/// \retval None
//-----------------------------------------------------------------------------
uint32 Wdg_GetCounter(void)
{
  return Wdg_asBaseAddrPtr[WDG_INSTANCE]->CNT;
}

//-----------------------------------------------------------------------------
/// \brief  This function resets the Watchdog
/// \return This function returns nothing.
/// \retval None
//-----------------------------------------------------------------------------
void Wdg_Trigger(void)
{
  Wdg_asBaseAddrPtr[WDG_INSTANCE]->CNT = WDG_TRIGGER_VALUE;
}

// EOF
