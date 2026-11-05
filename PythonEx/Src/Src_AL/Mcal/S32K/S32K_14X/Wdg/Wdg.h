#ifndef WDG_2021_07_26_H_
#define WDG_2021_07_26_H_
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
/// \file  Wdg.h
///
/// \brief This file contains all functions prototypes
///        and macros for Wdg module.
//
//-----------------------------------------------------------------------------


//=============================================================================
// Includes
//=============================================================================
#include "Wdg_Cfg.h"

//=============================================================================
// Defines
//=============================================================================
/// The 32-bit value used for unlocking the WDOG
#define WDG_UNLOCK_VALUE            ((uint32)0xD928C520U)
//=============================================================================
// Exported Types
//=============================================================================

// Configuration structure for Wdg better rename it to wdg instance
typedef Wdg_InstanceCfgType Wdg_InstanceType;

//=============================================================================
// Exported Variables
//=============================================================================
//lint -esym(9003, Wdg_timeout)
extern Wdg_InstanceType Wdg_Instance;

//=============================================================================
// Exported Functions Declaration
//=============================================================================
void Wdg_Init(Wdg_InstanceType* tsTimeoutPtr);
void Wdg_Trigger(void);
void Wdg_SetTimeout(uint16 unTimeout);
uint32 Wdg_GetCounter(void);


#endif // WDG_2021_07_26_H_

// EOF