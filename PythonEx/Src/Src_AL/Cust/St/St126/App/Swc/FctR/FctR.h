#ifndef __FCTR_H__
#define __FCTR_H__

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
/// \file  FctR.h
///
/// \brief  External interface of Function Router.
///
/// \author Ralf Sondershaus  (sor2rt)
///         mailTo:ralf.sondershaus@al-lighting.com       
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include "FctR_RteAccess.h"

//=============================================================================
// function prototypes
//=============================================================================

void FctR_Init(void);

void FctR_Cycle(void);

void FctR_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData);

void FctR_MapParams(void);

#endif // __FCTR_H__
