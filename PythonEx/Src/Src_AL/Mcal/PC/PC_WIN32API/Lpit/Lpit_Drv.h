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
/// \file  Lpit_Drv.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef LPIT_DRV_2021_03_16_H_
#define LPIT_DRV_2021_03_16_H_

//====================================================================
// Include files
//====================================================================

#include <Std_Types.h>
#include <Lpit.h>
#include "Lpit_TargetTypes.h"

//====================================================================
// Global functions definitions
//===================================================================

Std_ReturnType  Lpit_Drv_Init(CONST_AL tsLpit_CfgData* CONST_AL psLpitCfgData);
void            Lpit_Drv_LpitSetTmrEnblBit(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulEnblBit);
void            Lpit_Drv_LpitSetTmrChCompVal(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulCompVal);
void            Lpit_Drv_LpitSetTmrChIntEnbl(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr, uint32 ulIntEnbl);
uint32          Lpit_Drv_LpitReturnCount(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr);
void            Lpit_Drv_LpitClearTimeout(CONST_AL tsLpit_LpitTmrCfg* CONST_AL psLpitTmr);

#endif // LPIT_DRV_2021_03_16_H_

// EOF
