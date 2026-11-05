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
/// \file  Anima_CodPrj.h
///
/// \brief	
///
//-----------------------------------------------------------------------------
#ifndef ANIMA_CODPRJ_H_
#define ANIMA_CODPRJ_H_

#include <RteCommonTypes.h>

void Anima_MapParams(void);
/// Return pointer to animation byte stream
extern  CONST_AL tNvmPara_CodingArea*    AnimMa_pCodingData;

/// Return sequence ID for given PSA animation
teRte_ExtLightingAnimationReq CodPrj_GetAnimMaSequenceId(teRte_ExtLightingAnimationReq eReq);
/// Set coding data
void Anima_ParaFct0(CONST_AL tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData);

#endif // ANIMA_CODPRJ_H_