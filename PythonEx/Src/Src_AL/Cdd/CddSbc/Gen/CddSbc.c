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
/// \file  CddSbc.c
///
/// \brief  SBC complex device driver
///
/// \descr  System Basic Chip
///
/// \author Diana Ursan
///         mailTo: elena-diana.ursan[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// Standard / system header file includes
//=============================================================================

//=============================================================================
//  Project-specific header file includes
//=============================================================================
#include <CddSbc.h>
#include <CddSbc_Cfg.h>
#include <CddSbc_Router.h>
#include <CddTle94x1.h>
#include <CddTle94x1_Types.h>
#include <CddSbc_Types.h>
#include <../../St126/Cdd/CddSbc/CddSbc_Cfg.h>

#if (CDDSBC_CFG_GPIO == STD_ON)
STATIC_AL uint16 CddSbc_unPWM_Val = 0u;
#endif

#if (CDDSBC_CFG_INIT_OPERATION == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  API function to initialize SBC complex device driver.
///
/// \descr  Calls the hardware specific function to initialize SBC.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddSbc_Init(void)
{
  CddSbc_Rou_Init();
}

#endif

#if (CDDSBC_CFG_INIT_OPERATION == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  API function to de-initialize SBC complex device driver.
///
/// \descr  Calls the hardware specific de-init function.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddSbc_DeInit(void)
{
  CddSbc_Rou_DeInit();
}
#endif

//-----------------------------------------------------------------------------
/// \brief  CddSbc_Cycle0
///
/// \descr  Used to call cyclic the requirend functions.(cycle time 20ms)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
#if (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON)
void CddSbc_Cycle0(void)
{
  CddSbc_Rou_Cycle0();
}

#if (CDDSBC_CFG_WK_INPUT == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  API function to get wakeup pin pegel
///
/// \descr  Calls the hardware specific function to get wakeup pin pegel
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
boolean CddSbc_GetWakeUpStatus(void)
{
  return CddSbc_Rou_GetWakeUpStatus();
}
#endif //CDDSBC_CFG_WK_INPUT == STD_ON
#endif //CDDSBC_CFG_CYCLIC_OPERATION == STD_ON

#if (CDDSBC_CFG_SLEEPMODE == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  API function to set SBC into Sleep Mode.
///
/// \descr  Calls the hardware specific function  to set SBC into Sleep Mode.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddSbc_SetSleepMode(void)
{
  CddSbc_Rou_SetSleepMode();
}
#endif

#if (CDDSBC_CFG_CAN_OPERATION == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  API function to set specific SBC CAN transceiver to different modes
///
/// \descr  Calls the hardware specific function to set specific CAN transceiver to a certain function mode
///
/// \param  uint8 ucCanChannel - indicates SBC CAN channel
///         uint8 ucCanMode - indicates SBC CAN transceiver mode
///
/// \return void
//-----------------------------------------------------------------------------
void CddSbc_SetCanMode(uint8 ucCanChannel, uint8 ucCanMode)
{
  CddSbc_Rou_SetCanMode(ucCanChannel, ucCanMode);
}
#endif

#if (CDDSBC_CFG_CAN_OPERATION == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  API function to get specific SBC CAN transceiver to different modes
///
/// \descr  Calls the hardware specific function to get can mode of specific CAN transceiver
///
/// \param  uint8 ucCanChannel - indicates SBC CAN channel
///
/// \return uint8 ucCanMode - indicates SBC CAN transceiver mode
//-----------------------------------------------------------------------------
uint8 CddSbc_GetCanMode(uint8 ucCanChannel)
{
  return CddSbc_Rou_GetCanMode(ucCanChannel);
}
#endif

#if (CDDSBC_CFG_CAN_OPERATION == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddSbc_GetCanUV
///
/// \descr  API function to get the undervoltage bit of CAN bus
///
/// \param  void
///
/// \return uint8 ucCanMode -indicates SBC CAN transceiver mode
//-----------------------------------------------------------------------------
uint8 CddSbc_GetCanUV(void)
{
  return CddSbc_Rou_GetCanUV();
}
#endif


#if (CDDSBC_CFG_STORE_RESETREASON == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  API function to get the reset reason
///
/// \descr  Calls the hardware specific function to get the reset reason
///
/// \param  -
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 CddSbc_GetResetReason(void)
{
  //MCU reset reason
  uint8 ucResetReason = (uint8)eRESET_SNA;
  uint8 ucSBCResetReason;

  // get SBC reset reason
  ucSBCResetReason = CddSbc_Rou_GetSBCResetReason();

  switch (ucSBCResetReason)
  {
  case (uint8)ePowerOnResetSBC:
    ucResetReason = (uint8)eRESET_POWER_ON;
    break;
  case (uint8)eWatchdogReset:
    ucResetReason = (uint8)eRESET_WATCHDOG;
    break;
  case (uint8)eCANWakeUpReset:
    ucResetReason = (uint8)eRESET_CAN_WAKEUP;
    break;
  case (uint8)eInputWakeUpReset:
    ucResetReason = (uint8)eRESET_INPUT_WAKEUP;
    break;
  default:
    //do nothing
    break;
  }
  return ucResetReason;
}
#endif

#if (CDDSBC_CFG_WATCHDOG == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddSbc_SetWdgWindowModeAnd10ms
///
/// \descr  API function to set the watchdog with window mode and 10ms
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddSbc_SetWdgWindowModeAnd10ms(void)
{
  CddSbc_Rou_SetWdgWindowModeAnd10ms();
}
#endif

#if (CDDSBC_CFG_WATCHDOG == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddSbc_SetWdgWindowModeAnd200ms
///
/// \descr  API function to set the watchdog with window mode and 200ms
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddSbc_SetWdgWindowModeAnd200ms(void)
{
  CddSbc_Rou_SetWdgWindowModeAnd200ms();
}
#endif

#if (CDDSBC_CFG_WATCHDOG == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddSbc_SetWdgTimeoutModeAnd200ms
///
/// \descr  API function to set the watchdog with timeout mode and 200ms
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddSbc_SetWdgTimeoutModeAnd200ms(void)
{
  CddSbc_Rou_SetWdgTimeoutModeAnd200ms();
}
#endif

#if (CDDSBC_CFG_GPIO == STD_ON)
///-----------------------------------------------------------------------------
/// \brief  CddSbc_SetPWM
///
/// \descr Set PWM on FO GPIO
///
/// \param  unPWMDutyCycle - PWM value [0..10000]
///
/// \return void
///-----------------------------------------------------------------------------
void CddSbc_SetPWM(uint16 unPWMDutyCycle)
{
  CddSbc_Rou_SetPWM(unPWMDutyCycle);
  CddSbc_unPWM_Val = unPWMDutyCycle;
}

//-----------------------------------------------------------------------------
/// \brief CddSbc_GetPWM
///
/// \descr OUT DCT PWM getter
///
/// \param  ucMode - 0u - Local PWM config, 1u - SBC register set
///
/// \return uint16 - PWM value [0..10000]
//-----------------------------------------------------------------------------
uint16 CddSbc_GetPWM(uint8 ucMode)
{
  uint16 unReturnVal;

  // 0 - Read the local PWM set (faster mode) - error diagnostic
  if (ucMode == 0u)
  {
    unReturnVal = CddSbc_unPWM_Val;
  }
  // > 0 - Read the internal SBC PWM set (slower mode) - PWM read by diagnostic
  else
  {
    // 0..100 scaling
    unReturnVal = (uint16)(((uint32)CddTle94x1_GetPWM() * 10000u) / 255u);
  }

  return unReturnVal;
}
#endif
