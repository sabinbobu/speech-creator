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
/// \file  FctR_Data.c
///
/// \brief Defines data for Function Router including parameters.
///
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#include "FctR.h"
#include "FctR_Cfg.h"
#include "FctR_Data.h"

//=============================================================================
// variables
//=============================================================================
/// State of coding (valid, invalid)
// PRQA S 1514 1 // QAC is wrong
CONST_AL tNvmPara_CodingArea*  FctR_pCodingArea;
CONST_AL tNvmPara_LmmABlock*   FctR_pLmmABlock;
uint8 FctR_ucCodingState;

// LMM basic state
CONST_AL tsFctR_LmmInitBlock FctR_LmmInit =
{
#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
  { //  Intensity, TimeOn, TimeOff, Priority, RampType, ErrorImpact, Active
    {       0u,      0u,      0u,     15u,       0u,        0u,        0u   },  // 00 
    {       0u,      0u,      0u,     15u,       0u,        0u,        0u   },  // 01 
    {       0u,      0u,      0u,     15u,       0u,        0u,        0u   },  // 02 
    {       0u,      0u,      0u,     15u,       0u,        0u,        0u   },  // 03 
    {       0u,      0u,      0u,     15u,       0u,        0u,        0u   },  // 04 
    {       0u,      0u,      0u,     15u,       0u,        0u,        0u   },  // 05 
    {       0u,      0u,      0u,     15u,       0u,        0u,        0u   },  // 06 
    {       0u,      0u,      0u,     15u,       0u,        0u,        0u   },  // 07 
    {       0u,      0u,      0u,     15u,       0u,        0u,        0u   },  // 08 
    {       0u,      0u,      0u,     15u,       0u,        0u,        0u   },  // 09 
    {       0u,      0u,      0u,     15u,       0u,        0u,        0u   },  // 10 
    {       0u,      0u,      0u,     15u,       0u,        0u,        0u   },  // 11 
    {       0u,      0u,      0u,     15u,       0u,        0u,        0u   },  // 12
    {       0u,      0u,      0u,     15u,       0u,        0u,        0u   },  // 13
    {       0u,      0u,      0u,     15u,       0u,        0u,        0u   },  // 14
    {       0u,      0u,      0u,     15u,       0u,        0u,        0u   },  // 15
  }
#else
  { //  Intensity, TimeOn, TimeOff, Priority, RampType, ErrorImpact, Active
    {       0u,      0u,      0u,     15u,       0u,        0u,        0u   },  // 00 
    {       0u,      0u,      0u,     15u,       0u,        0u,        0u   },  // 01 
    {       0u,      0u,      0u,     15u,       0u,        0u,        0u   },  // 02 
    {       0u,      0u,      0u,     15u,       0u,        0u,        0u   },  // 03 
    {       0u,      0u,      0u,     15u,       0u,        0u,        0u   },  // 04 
    {       0u,      0u,      0u,     15u,       0u,        0u,        0u   },  // 05 
  }
#endif
};

///// 1 = LogLmp is used by this light function (Lmm[LgtFct].ucIntensity > 0), 0 = LogLmp is not used by this light function (Lmm[LgtFct].ucIntensity == 0)
tuFctR_LogLmp FctR_UsageLogLmpBTable[FCTR_CFG_LGTFCT_MAX];

// PRQA L:L3406  //Program architecture and readability


//-----------------------------------------------------------------------------
/// \brief  FctR_Cod_Valid
///
/// \descr  The function check the validity of coding data 
///
/// \param  -
///
/// \return boolean  : TRUE = coding data valid; FALSE = invalid coding data
//-----------------------------------------------------------------------------
boolean FctR_Cod_Valid(void)
{ 
  boolean boRet;
  if ((FctR_pCodingArea != NULL_PTR) && (FctR_ucCodingState == FCTR_CODING_VALID))
  {
    boRet = TRUE;
  }
  else
  {
    boRet = FALSE;
  }
  return boRet;
}

// EOF

