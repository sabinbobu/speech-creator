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
/// \file   CddTle94x1.h
///
/// \brief  API for CddTle94x1
///
/// \author Diana Ursan
/// \e-mail: elena-diana.ursan[at]marelli.com
///
//-----------------------------------------------------------------------------

#ifndef CDD_TLE94X1_2021_03_08_H_
#define CDD_TLE94X1_2021_03_08_H_


//=============================================================================
//  preprocessor definitions
//=============================================================================

//=============================================================================
//  includes
//=============================================================================
#include <CddSbc_Router.h>
#include <../../St126/Cdd/CddSbc/CddSbc_Cfg.h>

//=============================================================================
//  definitions
//=============================================================================

//=============================================================================
//  types
//=============================================================================

//=============================================================================
//  global variable
//=============================================================================

//=============================================================================
//  inline functions
//=============================================================================

//=============================================================================
//Intern prototypes
//=============================================================================

/******************************************************************************/
/* Prototypes                                                                 */
/******************************************************************************/
#if (CDDSBC_CFG_INIT_OPERATION == STD_ON)
void    CddTle94x1_Init(void);
void    CddTle94x1_DeInit(void);
#endif

#if (CDDSBC_CFG_SLEEPMODE == STD_ON)
void    CddTle94x1_SetSleepMode(void);
#endif

#if (CDDSBC_CFG_CAN_OPERATION == STD_ON)
void    CddTle94x1_SetCanMode(uint8 ucCanChannel, uint8 ucCanMode);
uint8   CddTle94x1_GetCanMode(uint8 ucCanChannel);
uint8   CddTle94x1_GetCanUV(void);
#endif

#if (CDDSBC_CFG_CYCLIC_OPERATION == STD_ON)
boolean CddTle94x1_GetWakeUpStatus(void);
void    CddSbc_InsertDefaultMessage(void);
void    CddSbc_ScheduleTableFull(boolean boStatus);
#endif

#if (CDDSBC_CFG_STORE_RESETREASON == STD_ON)
uint8 CddTle94x1_GetSBCResetReason(void);
#endif

#if (CDDSBC_CFG_WATCHDOG == STD_ON)
void    CddTle94x1_SetWdgWindowModeAnd10ms(void);
void    CddTle94x1_SetWdgTimeoutModeAnd200ms(void);
void    CddTle94x1_SetWdgWindowModeAnd200ms(void);
#endif

#if (CDDSBC_CFG_VCC2_OPERATION == STD_ON)
void CddTle94x1_Short_To_VBAT(void);
void CddTle94x1_Reset_Short_To_VBAT(void);
void CddTle94x1_Short_To_GND(void);
void CddTle94x1_Reset_Short_To_GND(void);
void CddTle94x1_Thermal_Shutdown(void);
#endif

#if (CDDSBC_CFG_GPIO == STD_ON)
void CddTle94x1_SetPWM(uint16 unPWMDutyCycle);
uint8 CddTle94x1_GetPWM(void);
#endif

//void CddSbc_InsertDefaultMessage_Copy(void);

#endif // EOF CDD_TLE94X1_2021_03_08_H_
