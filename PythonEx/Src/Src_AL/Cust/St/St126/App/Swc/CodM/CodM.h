#ifndef __CODM_H__
#define __CODM_H__ 

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
/// \file  CodM.h
///
/// \brief  
///
/// \descr  CodM header
///
///         
///         
///
/// \author Cretu Vlad (F78845C)
///         mailTo:vladut-ioan.cretu[at]marelli.com
//-----------------------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================
#include <Std_Types.h>
#include "CodM_Para_Led.h"
#include <CodM_Types.h>
#include <CodM_Para.h>

//=============================================================================
// defines
//=============================================================================

//=============================================================================
// types
//=============================================================================

//=============================================================================
// function prototypes
//=============================================================================
void CodM_Init(void);
void CodM_Cycle0(void);
void riCodM_Init(void);
void rpCodM_Cycle0(void);
// To be used
//tsCodM_MinBrightness_Param* CodM_GetMinBrightness_Param(void);

#endif /* (__CODM_H_ ) */

// EOF
