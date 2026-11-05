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
/// \file   ctaaDbl.h
///
/// \brief  ctaa wrapper file for dbl module
///
//-----------------------------------------------------------------------------
#ifndef CTAA_DBL_2020_11_11_H_
#define CTAA_DBL_2020_11_11_H_

//=============================================================================
// includes
//=============================================================================
#include "Dblc.h"
#include "DblData.h"
#include <Swc/CodM/CodM.h>
#include <Swc/CodM/CodM_Para.h>
#include <Cfg/Cfg.h>

//=============================================================================
// function prototypes
//=============================================================================

void riDbl_Init(void);
void rpDbl_Cycle(void);


#endif // CTAA_DBL_2020_11_11_H_
