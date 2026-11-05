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
/// \file  SysMonCheck_InternalCom.c
///
/// \brief Check and manage internal communication errors
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================
#include <SysMonCheck_InternalCom.h>
#include <SysMonCheck.h>
#include <Crc.h>

//=============================================================================
// Local globals
//=============================================================================
STATIC_AL boolean SysMonCheck_InternalCom_boLedStateCrcError_ASIL          = FALSE;
STATIC_AL boolean SysMonCheck_InternalCom_boTgtLed_FaultStatus_ASIL        = FALSE;
STATIC_AL boolean SysMonCheck_InternalCom_boTgtLed_FaultStatus_SysMon_ASIL = FALSE;
STATIC_AL boolean SysMonCheck_InternalCom_boInternalComErrActive           = FALSE;

#if (CFG_DEV_HOOK_EN == 1u)
#define SYSMON_CRC8_RTE_HOOK_KEY       0x5A5AA5A5u
STATIC_AL volatile uint32 SysMonCheck_InternalCom_ulTesterHookActivation1 = 0u;
STATIC_AL volatile uint32 SysMonCheck_InternalCom_ulTesterHookActivation2 = 0u;
#endif

//=============================================================================
// functions prototype
//=============================================================================
STATIC_AL void SysMonCheck_InternalCom_SetInternalComErrActive(boolean boStatus);


//=============================================================================
// functions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_InternalCom_LedState_CheckCrc
///
/// \descr  Calculate the CRC of the data received over Rte port and check if 
///         it is matching with the CRC contained in the Rte port itself.
///
/// \param  pLedStates_ASIL - pointer to structure containing the LED Error Status
///
/// \return boolean: true - if CRC matches
///                 false - if CRC is not consistent
//-----------------------------------------------------------------------------
boolean SysMonCheck_InternalCom_LedState_CheckCrc(tsRte_LedStates* pLedStates_ASIL)
{
  STATIC_UT(boolean, boCrcFailure, FALSE);
  STATIC_UT(TIMER,   ulCrcTimer,      0u);
  boolean boIsCrcOk     = FALSE;
  uint8   ucCrc         = 0u;
  uint32  ulSizeOfData  = 0u;

  ulSizeOfData = sizeof(tsRte_ChLedStates) * CFG_LED_CHANNELS_NR;

  // PRQA S 310 1 // Software Architecture , intended behaviour
  ucCrc = Crc_CalculateCRC8H2F((const uint8*)&pLedStates_ASIL->aLedStates[0u].eLedErrStatus, ulSizeOfData, CRC_SEED_INIT_CRC8H2F_VAL);

  // Developer test using hook in order to corrupt the CRC8 between Rte ports
#if (CFG_DEV_HOOK_EN == 1u)
  if (SysMonCheck_InternalCom_ulTesterHookActivation1 == SYSMON_CRC8_RTE_HOOK_KEY)
  {
    pLedStates_ASIL->ucCrc += 1u;
  }
  else
  {
    // nothing to do
  }
#endif

  // If calculated Crc is matching the transmitted one
  if (ucCrc == pLedStates_ASIL->ucCrc)
  {
    // Set return flag to true
    boIsCrcOk = TRUE;

    // Reset Rte CRC8 failure flag
    boCrcFailure = FALSE;

    // Reset the CRC8 Rte Error flag for LED Error Status
    SysMonCheck_InternalCom_boLedStateCrcError_ASIL = FALSE;
  }
  else
  {
    // Crc not equal as the recieved one
    // First time appearance of Rte CRC8 error
    if (boCrcFailure == FALSE)
    {
      // Get time stamp
      ulCrcTimer = TimerGetTick();
      // Set CRC8 Failure flag
      boCrcFailure = TRUE;
    }
    else
    {
      if (TimerGetTimeSince(ulCrcTimer) >= UTILTIME_MSEC(INTERNALCOM_CRC8_RTE_ERROR_MS))
      {
        // Set the CRC8 Rte Error flag for LED Error Status
        SysMonCheck_InternalCom_boLedStateCrcError_ASIL = TRUE;
      }
      else
      {
        // nothing to do
      }
    }
  }

  return boIsCrcOk;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_InternalCom_TgtLed_FaultStatus_ASIL_CheckCrc
///
/// \descr  Calculate the CRC of the data received over Rte port and check if 
///         it is matching with the CRC contained in the Rte port itself.
///
/// \param  pLedStates_ASIL - pointer to structure containing the Target Value Fault Status
///
/// \return boolean: true - if CRC matches
///                 false - if CRC is not consistent
//-----------------------------------------------------------------------------
boolean SysMonCheck_InternalCom_TgtLed_FaultStatus_ASIL_CheckCrc(tsRte_TgtLedSig0_FaultStatus_ASIL* pTgtLed_FaultStatus_ASIL)
{
  STATIC_UT(boolean, boCrcFailure, FALSE);
  STATIC_UT(TIMER,   ulCrcTimer,      0u);
  boolean boIsCrcOk    = FALSE;
  uint8   ucCrc        = 0u;
  uint32  ulSizeOfData = 0u;

  ulSizeOfData = sizeof(boolean);

  // PRQA S 310 1 // Software Architecture , intended behaviour
  ucCrc = Crc_CalculateCRC8H2F((const uint8*)&pTgtLed_FaultStatus_ASIL->boCrc8ErrorStatus, ulSizeOfData, CRC_SEED_INIT_CRC8H2F_VAL);

  // Developer test using hook in order to corrupt the CRC8 between Rte ports
#if (CFG_DEV_HOOK_EN == 1u)
  if (SysMonCheck_InternalCom_ulTesterHookActivation2 == SYSMON_CRC8_RTE_HOOK_KEY)
  {
    pTgtLed_FaultStatus_ASIL->ucCrc += 1u;
  }
  else
  {
    // nothing to do
  }
#endif

  // If calculated Crc is matching the transmitted one
  if (ucCrc == pTgtLed_FaultStatus_ASIL->ucCrc)
  {
    // Set return flag to true
    boIsCrcOk = TRUE;

    // Reset Rte CRC8 failure flag
    boCrcFailure = FALSE;

    // Reset the CRC8 Rte Error flag for Target Value Fault Status
    SysMonCheck_InternalCom_boTgtLed_FaultStatus_ASIL = FALSE;
  }
  else
  {
    // Crc not equal as the recieved one
    // First time appearance of Rte CRC8 error
    if (boCrcFailure == FALSE)
    {
      // Get time stamp
      ulCrcTimer = TimerGetTick();
      // Set CRC8 Failure flag
      boCrcFailure = TRUE;
    }
    else
    {
      if (TimerGetTimeSince(ulCrcTimer) >= UTILTIME_MSEC(INTERNALCOM_CRC8_RTE_ERROR_MS))
      {
        // Set the CRC8 Rte Error flag for Target Value Fault Status
        SysMonCheck_InternalCom_boTgtLed_FaultStatus_ASIL = TRUE;
      }
      else
      {
        // nothing to do
      }
    }
  }

  return boIsCrcOk;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_InternalCom_Init
///
/// \descr  Init function for Internal Communication Error checking
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonCheck_InternalCom_Init(void)
{
  SysMonCheck_InternalCom_boLedStateCrcError_ASIL           = FALSE;
  SysMonCheck_InternalCom_boTgtLed_FaultStatus_ASIL         = FALSE;
  SysMonCheck_InternalCom_boTgtLed_FaultStatus_SysMon_ASIL  = FALSE;
  SysMonCheck_InternalCom_boInternalComErrActive            = FALSE;
}

//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_InternalCom_Cycle
///
/// \descr  Cyclic function for Internal Communication Error checking
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void SysMonCheck_InternalCom_Cycle(void)
{
  SysMonCheck_InternalCom_boTgtLed_FaultStatus_SysMon_ASIL = SysMonCheck_Get_TgtLed_FaultStatus_ASIL();

  // Evaluate CRC8 Rte errors
  if ((SysMonCheck_InternalCom_boTgtLed_FaultStatus_SysMon_ASIL != FALSE) ||
      (SysMonCheck_InternalCom_boLedStateCrcError_ASIL != FALSE) ||
      (SysMonCheck_InternalCom_boTgtLed_FaultStatus_ASIL != FALSE))
  {
    // Set Internal Communication Error Status
    SysMonCheck_InternalCom_SetInternalComErrActive(TRUE);
  }
  else
  {
    // Clear Internal Communication Error Status
    SysMonCheck_InternalCom_SetInternalComErrActive(FALSE);
  }
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_InternalCom_SetInternalComErrActive
///
/// \descr  Set/Clear the final status of the Internal Communication Error
///
/// \param  boStatus - true  = error active
///                  - false = no error is active
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void SysMonCheck_InternalCom_SetInternalComErrActive(boolean boStatus)
{
  SysMonCheck_InternalCom_boInternalComErrActive = boStatus;
}


//-----------------------------------------------------------------------------
/// \brief  SysMonCheck_InternalCom_IsComErrActive
///
/// \descr  Get the final status of the Internal Communication Error
///
/// \param  void
///
/// \return boolean  - true  = error active
///                  - false = no error is active
//-----------------------------------------------------------------------------
 boolean SysMonCheck_InternalCom_IsComErrActive(void)
{
  return SysMonCheck_InternalCom_boInternalComErrActive;
}


// EOF
