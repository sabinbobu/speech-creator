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
/// \file   CddSbc.h
///
/// \brief  API for CddSbc
///
/// \author Diana Ursan
///         mailTo: elena-diana.ursan[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CDD_SBC_2021_03_08_H_
#define CDD_SBC_2021_03_08_H_

#include <Std_Types.h>
#include <CddSbc_Cfg.h>
#include <CddSbc_Router.h>

//=============================================================================
// macros
//=============================================================================

//=============================================================================
// Exported functions
//=============================================================================

#if (CDDSBC_CFG_GPIO == STD_ON)
void    CddSbc_SetPWM(uint16 unPWMDutyCycle);
uint16 CddSbc_GetPWM(uint8 ucMode);
#endif

#if (CDDSBC_CFG_INIT_OPERATION == STD_ON)
void    CddSbc_Init(void);
void    CddSbc_DeInit(void);
#endif

#if (CDDSBC_CFG_SLEEPMODE == STD_ON)
void    CddSbc_SetSleepMode(void);
#endif

#if (CDDSBC_CFG_CAN_OPERATION == STD_ON)
void    CddSbc_SetCanMode(uint8 ucCanChannel, uint8 ucCanMode);
uint8   CddSbc_GetCanMode(uint8 ucCanChannel);
uint8   CddSbc_GetCanUV(void);
#endif

#if (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON)
void    CddSbc_Cycle0(void);
#if (CDDSBC_CFG_WK_INPUT == STD_ON)
boolean CddSbc_GetWakeUpStatus(void);
#endif //CDDSBC_CFG_WK_INPUT == STD_ON
#endif //CDDSBC_CFG_CYCLIC_OPERATION == STD_ON

#if (CDDSBC_CFG_WATCHDOG == STD_ON)
void    CddSbc_SetWdgWindowModeAnd10ms(void);
void    CddSbc_SetWdgWindowModeAnd200ms(void);
void    CddSbc_SetWdgTimeoutModeAnd200ms(void);
#endif

#if (CDDSBC_CFG_STORE_RESETREASON == STD_ON)
uint8 CddSbc_GetResetReason(void);
#endif
#endif // CDD_SBC_2021_03_08_H_
