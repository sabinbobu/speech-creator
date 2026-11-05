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

#include <CddSbc.h>
#include <CddSbc_Cfg.h>
#include <CddSbc_Router.h>
#include <CddSbc_Types.h>

//=============================================================================
// Typedefs
//=============================================================================

//=============================================================================
// Defines
//=============================================================================

//=============================================================================
// Module global variables
//=============================================================================

extern uint8 CddSbc_ucWdgTriggerStat;
extern uint16 CddSbc_unPWM_Val;

//=============================================================================
// Module function declarations
//=============================================================================

extern void    CddSbc_Init(void);
extern void    CddSbc_DeInit(void);
extern void    CddSbc_SetSleepMode(void);
extern void    CddSbc_SetCanMode(uint8 ucCanChannel, uint8 ucCanMode);
extern uint8   CddSbc_GetCanMode(uint8 ucCanChannel);
extern uint8   CddSbc_GetCanUV(void);
extern void    CddSbc_Cycle0(void);
extern boolean CddSbc_GetWakeUpStatus(void);
extern void    CddSbc_SetWdgWindowModeAnd10ms(void);
extern void    CddSbc_SetWdgWindowModeAnd200ms(void);
extern void    CddSbc_SetWdgTimeoutModeAnd200ms(void);
extern uint8   CddSbc_GetResetReason(void);
extern void    CddSbc_SetPWM(uint16 unPWMDutyCycle);
extern uint16  CddSbc_GetPWM(uint8 ucMode);
extern void    reCddSbc_SetLssPwm(void);

extern void    CddSbc_Rou_Init(void);
extern void    CddSbc_Rou_DeInit(void);
extern uint8   CddSbc_Rou_GetSBCResetReason(void);
extern boolean CddSbc_Rou_GetWakeUpStatus(void);
extern void    CddSbc_Rou_SetSleepMode(void);
extern void    CddSbc_Rou_SetCanMode(uint8 ucCanChannel, uint8 ucCanMode);
extern uint8   CddSbc_Rou_GetCanMode(uint8 ucCanChannel);
extern uint8   CddSbc_Rou_GetCanUV(void);
extern void    CddSbc_Rou_SetWdgWindowModeAnd10ms(void);
extern void    CddSbc_Rou_SetWdgWindowModeAnd200ms(void);
extern void    CddSbc_Rou_SetWdgTimeoutModeAnd200ms(void);
extern void    CddSbc_Rou_Cycle0(void);

//=============================================================================
// Module function parameter stubs
//=============================================================================

uint8           CddSbc_SetCanMode_Param1;
uint8           CddSbc_SetCanMode_Param2;
uint8           CddSbc_GetCanMode_Param1;

uint8           CddSbc_Rou_SetCanMode_Param1;
uint8           CddSbc_Rou_SetCanMode_Param2;
uint8           CddSbc_Rou_GetCanMode_Param1;

uint16          CddSbc_SetPWM_Param1;
uint8           CddSbc_GetPWM_Param1;

//=============================================================================
// Module function return value stubs
//=============================================================================

uint8           CddSbc_GetCanMode_RetVal;
uint8           CddSbc_GetCanUV_RetVal;
boolean         CddSbc_GetWakeUpStatus_RetVal;
uint8           CddSbc_GetResetReason_RetVal;
uint16          CddSbc_GetPWM_RetVal;

uint8           CddSbc_Rou_GetSBCResetReason_RetVal;
boolean         CddSbc_Rou_GetWakeUpStatus_RetVal;
uint8           CddSbc_Rou_GetCanMode_RetVal;
uint8           CddSbc_Rou_GetCanUV_RetVal;

//=============================================================================
// Module static variables inside functions 
//=============================================================================

#endif // TEST_2023_08_25_H_
