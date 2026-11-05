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
/// \file  CddSbc_Router.h
///
/// \brief  Configuration of CddSbc router
///
/// \author Diana Ursan
///         mailTo: elena-diana.ursa[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CDD_SBC_ROUTER_2021_03_01_H_
#define CDD_SBC_ROUTER_2021_03_01_H_

#include <Std_Types.h>
#include <CddSbc_Cfg.h>
#include <../../St126/Cdd/CddSbc/CddSbc_Cfg.h>

//=============================================================================
// Prototypes
//=============================================================================

#if (CDDSBC_CFG_GPIO == STD_ON)
void CddSbc_Rou_SetPWM(uint16 unPWMDutyCycle);
#endif

#if (CDDSBC_CFG_INIT_OPERATION == STD_ON)
void CddSbc_Rou_Init(void);
void CddSbc_Rou_DeInit(void);
#endif


#if (CDDSBC_CFG_SLEEPMODE == STD_ON)
void CddSbc_Rou_SetSleepMode(void);
#endif

#if (CDDSBC_CFG_CAN_OPERATION == STD_ON)
void    CddSbc_Rou_SetCanMode(uint8 ucCanChannel, uint8 ucCanMode);
uint8   CddSbc_Rou_GetCanMode(uint8 ucCanChannel);
uint8   CddSbc_Rou_GetCanUV(void);
#endif

#if (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON)
void    CddSbc_Rou_Cycle0(void);
boolean CddSbc_Rou_GetWakeUpStatus(void);
#endif

#if (CDDSBC_CFG_STORE_RESETREASON == STD_ON)
uint8    CddSbc_Rou_GetSBCResetReason(void);
#endif

#if (CDDSBC_CFG_WATCHDOG == STD_ON)
#if (CDDSBC_CFG_TYPE == CDDSBC_CFG_94x1)
void    CddSbc_Rou_SetWdgWindowModeAnd10ms(void);
void    CddSbc_Rou_SetWdgWindowModeAnd200ms(void);
void    CddSbc_Rou_SetWdgTimeoutModeAnd200ms(void);
#endif
#endif

#endif // CDD_SBC_ROUTER_2021_03_01_H_
