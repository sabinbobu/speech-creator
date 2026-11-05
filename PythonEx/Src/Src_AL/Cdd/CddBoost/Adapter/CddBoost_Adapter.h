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
/// \file  CddBoost_Adapter.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef CDD_BOOST_ADAPTER_2021_08_30_H_
#define CDD_BOOST_ADAPTER_2021_08_30_H_

//=============================================================================
// includes
//=============================================================================
#include <CodM.h>

//-----------------------------------------------------------------------------
// Access to CodM
//-----------------------------------------------------------------------------
#define CDDBOOST_RTE_RE_GET_CODING_DATA(pTarget)     CddBoost_Get_CodingPara(pTarget); //from CodM

//=============================================================================
// types
//=============================================================================
typedef struct
{
  tNvmPara_CodingArea* psCodingParameters_Blocks;
  tParaFct0_Cmd        eCodingState;
}tsCddBoost_CodingParam;

void rpCddBoost_Cycle(void);
void riCddBoostInit(void);
void CddBoost_Get_CodingPara(tsCddBoost_CodingParam *sCodingParam);

#endif // CDD_BOOST_ADAPTER_2021_08_30_H_
