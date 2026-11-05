//*****************************************************************************
// (C) Marelli Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Marelli Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Marelli Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  CtrlLed_Diag.h
///
/// \brief
///
/// \author Caba Ionut-Stefan (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CTRL_LED_DIAG_2023_09_20_H
#define CTRL_LED_DIAG_2023_09_20_H


//=============================================================================
// includes
//=============================================================================
#include "CtrlLed_Cfg.h"
#include <Std_Types.h>
#include <AL_Helper.h>
#include "CtrlLed_Types.h"

//=============================================================================
// function prototypes
//=============================================================================
tsCtrlLed_ErrorHandler CtrlLed_Diag_ErrorHandler(uint8_fast ucIl, uint8_fast ucCh, uint16 unDuty, uint16 unCurrent);
tsCtrlled_InternalHandlings* CtrlLed_pfInternalHandling(void);
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
boolean CtrlLed_Diag_MtxVccx_Eeprom(void);
boolean CtrlLed_GetMatrixError(uint8 ucRow, uint8 ucLmmPxl, uint8 ucIll);
void CtrlLed_HandleMatrixDtc(void);
#endif


#endif // CTRL_LED_DIAG_2023_09_20_H
