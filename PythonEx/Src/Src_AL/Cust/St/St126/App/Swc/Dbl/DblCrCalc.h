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
/// \file  DblCrCalc.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef DBL_CR_CALC_2023_09_18_H_
#define DBL_CR_CALC_2023_09_18_H_

//=============================================================================
// includes
//=============================================================================
#include <Swc/CodM/CodM_Para.h>
#include <Swc/CodM/CodM.h>


//=============================================================================
// function prototypes
//=============================================================================
void              DblCrvCalc_Get_WfCodingParameters(void);
sint32            DblCrvCalc_getCurvatureValue(void);
void              DblCrvCalc_Get_CurvatureCodingParameters(void);


#endif // DBL_CR_CALC_2023_09_18_H_
