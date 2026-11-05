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
/// \file   ctaaAnima.h
///
/// \brief  ctaa wrapper file for animation module
///
//-----------------------------------------------------------------------------

#include <CodM_Types.h>

//=============================================================================
// function prototypes
//=============================================================================

void riAnima_Init(void);
void rpAnima_Cycle0(void);
void roAnima_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData);
