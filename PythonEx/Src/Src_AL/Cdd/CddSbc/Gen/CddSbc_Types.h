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
/// \file  
///
/// \brief
///
/// \descr  
///
/// \author
///
//-----------------------------------------------------------------------------
#ifndef CDD_SBC_H_
#define CDD_SBC_H_

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
typedef enum
{
  eNoResetMCU = 0,                       // No Reset
  ePowerOnResetMCU,                      // MCU PowerOnReset
  eWatchdogResetMCU,                     // MCU Watchdog Reset
  eSoftwareReset,                        // Software Reset
  ePLLReset,                             // PLL Reset
  eECCReset,                             // ECC Reset
  eMCUSelfTestReset,                     // MCU Self-test Reset
  eUnderVoltage,                         // MCU Under Voltage
  eOtherReasons
}teCddSbc_MCUResetType;

typedef enum
{
  eNoResetSBC = 0,                       // No Reset
  ePowerOnResetSBC,                      // SBC PowerOnReset
  eCANWakeUpReset,                       // Can Wake Up Reset
  eWatchdogReset,                        // SBC watchdog
  eInputWakeUpReset                      // Input Wake Up Reset
}teCddSbc_SBCResetType;

typedef enum
{
  eRESET_SNA = 0,
  eRESET_UNDEFINED,
  eRESET_POWER_ON,
  eRESET_CAN_WAKEUP,
  eRESET_SOFTWARE,
  eRESET_WATCHDOG,
  eRESET_PLL_ERROR,
  eRESET_ECC_ERROR,
  eRESET_UNDER_VOLTAGE,
  eRESET_MPU_SELFTEST_ERROR,
  eRESET_INPUT_WAKEUP,
}teCddSbc_ResetReason;

#endif

//EOF
