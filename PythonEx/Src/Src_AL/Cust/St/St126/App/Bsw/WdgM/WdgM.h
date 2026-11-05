#ifndef __WDGM_H__
#define __WDGM_H__

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
/// \file  WdgM.h
///
/// \brief  
///
/// \descr  
///
/// \author Cretu Vladut Ioan
//-----------------------------------------------------------------------------

#include "WdgM_Types.h"

//=============================================================================
// function prototypes
//=============================================================================
void WdgM_SetLocalCheckPoint(uint8 ucId);
void WdgM_EntitySupervision(void);
void WdgM_Cycle0(void);
void WdgM_Init(void);
void WdgM_ResetShaDataResetReason(void);
extern void LPIT0_Ch1_IRQHandler(void);

#endif // __WDGM_H__

// EOF
