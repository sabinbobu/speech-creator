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
/// \file   CddSbc_Router.c
///
/// \brief  Specific code for CddSbc Router
///
/// \author Diana Ursan
/// \e-mail: elena-diana.ursan[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================
#include <Std_Types.h>
#include <Cfg/Cfg.h>
#include <CddSbc.h>
#include <CddSbc_Cfg.h>
#include <CddSbc_Router.h>
#include <CddTle94x1.h>
#include <../../St126/Cdd/CddSbc/CddSbc_Cfg.h>

//=============================================================================
// Defines and Typedef
//=============================================================================

//=============================================================================
//  Static variable declarations
//=============================================================================

STATIC_AL uint8 CddSbc_ucWdgTriggerStat = 0u;

//=============================================================================
// Function prototypes
//=============================================================================

//=============================================================================
// Macros
//=============================================================================


//=============================================================================
// Function definitions
//=============================================================================

#if (CDDSBC_CFG_INIT_OPERATION == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddSbc_Rou_Init
///
/// \descr  Function that calls the initialization function from CddTl294x1
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddSbc_Rou_Init(void)
{
  CddTle94x1_Init();
}

//-----------------------------------------------------------------------------
/// \brief  CddSbc_Rou_DeInit
///
/// \descr  Function that calls the de initialization function from CddTl294x1.
///         Dummy function for now.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddSbc_Rou_DeInit(void)
{
  CddTle94x1_DeInit();
}
#endif

#if (CDDSBC_CFG_SLEEPMODE == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddSbc_Rou_SetSleepMode
///
/// \descr  Function to set the ECU in sleep mode.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void CddSbc_Rou_SetSleepMode(void)
{
  CddTle94x1_SetSleepMode();
}
#endif

#if (CDDSBC_CFG_CAN_OPERATION == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddSbc_Rou_SetCanMode
///
/// \descr  set can mode
///
/// \param  uint8 ucCanChannel    - indicates SBC CAN channel
///         uint8 ucCanMode       - indicates SBC CAN transceiver mode
///
/// \return void
//-----------------------------------------------------------------------------
void    CddSbc_Rou_SetCanMode(uint8 ucCanChannel, uint8 ucCanMode)
{
  CddTle94x1_SetCanMode(ucCanChannel, ucCanMode);
}

//-----------------------------------------------------------------------------
/// \brief  CddSbc_Rou_GetCanMode
///
/// \descr  get can mode
///
/// \param  uint8 ucCanChannel    - indicates SBC CAN channel
///
/// \return uint8 ucCanMode       - indicates SBC CAN transceiver mode
//-----------------------------------------------------------------------------
uint8   CddSbc_Rou_GetCanMode(uint8 ucCanChannel)
{
  return CddTle94x1_GetCanMode(ucCanChannel);
}

//-----------------------------------------------------------------------------
/// \brief  CddSbc_Rou_GetCanUV
///
/// \descr  get Can undervoltage
///
/// \param  -
///
/// \return uint8 CAN undervoltage 
//-----------------------------------------------------------------------------
uint8 CddSbc_Rou_GetCanUV(void)
{
  return CddTle94x1_GetCanUV();
}
#endif

#if (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON)
//-----------------------------------------------------------------------------
/// \brief  CddSbc_Rou_Cycle0
///
/// \descr  Fucntion that calls the functions that need to be called cyclic.
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void CddSbc_Rou_Cycle0(void) 
{
  if (CddSbc_ucWdgTriggerStat == 0xBDu)
  {
    CddTle94x1_SetWdgWindowModeAnd200ms();
    CddSbc_ucWdgTriggerStat = 0u;
  }
  //CddSbc_InsertDefaultMessage_Copy();
#if (CDDSBC_CFG_VCC2_OPERATION == STD_ON)
  CddTle94x1_Short_To_VBAT();      // call the function for Short to VBAT checking
  CddTle94x1_Reset_Short_To_VBAT();      // call the function to reset the flag for Short to VBAT
  CddTle94x1_Short_To_GND();       // call the function for Short to GND checking
  CddTle94x1_Reset_Short_To_GND(); // call the function to switch back on VCC2 after Short to GND occured
  CddTle94x1_Thermal_Shutdown();   // call the function for Thermal Shotdown checking
#endif
  //CddSbc_InsertDefaultMessage_Copy();
} 

#if (CDDSBC_CFG_WK_INPUT == STD_ON)
boolean CddSbc_Rou_GetWakeUpStatus(void)
{
  return CddTle94x1_GetWakeUpStatus();
}
#endif //CDDSBC_CFG_WK_INPUT == STD_ON
#endif //CDDSBC_CFG_CYCLIC_OPERATION == STD_ON

#if (CDDSBC_CFG_STORE_RESETREASON == STD_ON)
///-----------------------------------------------------------------------------
/// \brief  CddSbc_Rou_GetSBCResetReason
///
/// \descr Function that calls the specific funtion from CddTle94x1 to get the 
///        reset reason.
///
/// \param  void
///
/// \return uint8
///-----------------------------------------------------------------------------
uint8 CddSbc_Rou_GetSBCResetReason(void)
{
  //Get SBC Reset Reason
  return CddTle94x1_GetSBCResetReason();
}
#endif

#if (CDDSBC_CFG_WATCHDOG == STD_ON)
///-----------------------------------------------------------------------------
/// \brief  CddSbc_Rou_SetWdgWindowModeAnd10ms
///
/// \descr Function that calls the specific funtion from CddTle94x1 to set the 
///        watchdog with window mode and 10ms
///
/// \param  void
///
/// \return void
///-----------------------------------------------------------------------------
void CddSbc_Rou_SetWdgWindowModeAnd10ms(void)
{
  CddTle94x1_SetWdgWindowModeAnd10ms();
}

///-----------------------------------------------------------------------------
/// \brief  CddSbc_Rou_SetWdgWindowModeAnd200ms
///
/// \descr Function that calls the specific funtion from CddTle94x1 to set the 
///        watchdog with window mode and 200ms
///
/// \param  void
///
/// \return void
///-----------------------------------------------------------------------------
void CddSbc_Rou_SetWdgWindowModeAnd200ms(void)
{
  //CddTle94x1_SetWdgWindowModeAnd200ms();
  CddSbc_ucWdgTriggerStat = 0xBDu;
}

///-----------------------------------------------------------------------------
/// \brief  CddSbc_Rou_SetWdgTimeoutModeAnd200ms
///
/// \descr Function that calls the specific funtion from CddTle94x1 to set the 
///        watchdog with timeout mode and 200ms
///
/// \param  void
///
/// \return void
///-----------------------------------------------------------------------------
void CddSbc_Rou_SetWdgTimeoutModeAnd200ms(void)
{
  CddTle94x1_SetWdgTimeoutModeAnd200ms();
}

#endif

#if (CDDSBC_CFG_GPIO == STD_ON)
///-----------------------------------------------------------------------------
/// \brief  CddSbc_Rou_SetPWM
///
/// \descr Set PWM on FO GPIO
///
/// \param  unPWMDutyCycle - PWM value [0..10000]
///
/// \return void
///-----------------------------------------------------------------------------
void CddSbc_Rou_SetPWM(uint16 unPWMDutyCycle)
{
  CddTle94x1_SetPWM(unPWMDutyCycle);
}
#endif

