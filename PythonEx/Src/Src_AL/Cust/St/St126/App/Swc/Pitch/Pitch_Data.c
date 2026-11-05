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
/// \file  PitchData.c
///
/// \brief In this file the coding is read an validated 
///
/// \author Adrian Horlescu (F31197D)
///         mailTo:adrian-marian.horlescu[at]marelli.com
//-----------------------------------------------------------------------------
#include "Pitch_Data.h"
#include "Pitch_RteAccess.h"

/* PRQA S 310,311 EOF */
//=============================================================================
// variables
//=============================================================================

 tNvmPara_CodingArea*  Pitch_pCodingArea;

//=============================================================================
// functions prototype
//=============================================================================

STATIC_AL boolean Pitch_ParaFct0(tParaFct0_Cmd eCmd,  tNvmPara_CodingArea* CONST_AL pData);

//-----------------------------------------------------------------------------
/// \brief  Pitch_CodingDataValidation
///
/// \descr  get and handle coding parameters for Pitch module
///
/// \param  void
///
/// \return return validity of coding as TRUE
//-----------------------------------------------------------------------------
boolean Pitch_CodingDataValidation(void)
{
  tsPitch_CodingParam sCodingParameters;
  //get coding data via RTE
  Pitch_RteAccess_Get_CodingPara(&sCodingParameters);
  //get coding data and return validity of this
  CONST_AL boolean boCodingValidity = Pitch_ParaFct0(sCodingParameters.eCodingState, sCodingParameters.psCodingParameters_Blocks);
  //return validity of coding
  return boCodingValidity;
}

//-----------------------------------------------------------------------------
/// \brief  Pitch_ParaFct0
///
/// \descr  this function get coding params and validity of coding data
///
/// \param  eCmd - valid/invalid, pData - coding params
///
/// \return coding validity
//-----------------------------------------------------------------------------
STATIC_AL boolean Pitch_ParaFct0(tParaFct0_Cmd eCmd, tNvmPara_CodingArea* CONST_AL pData)
{
  boolean boCodingValidity = FALSE;

  switch (eCmd)
  {
  case eParaFct0_CodingDataValid:
    Pitch_pCodingArea = pData;
    boCodingValidity = (Pitch_pCodingArea == NULL_PTR) ? FALSE : TRUE;
    break;
  case eParaFct0_CodingDataInvalid:
    boCodingValidity = FALSE;
    break;
  default:
    break;
  }

  return boCodingValidity;
}
//EOF
