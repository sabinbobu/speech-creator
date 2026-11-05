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
/// \file  FctR.c
///
/// \brief Defines the Function Router (FctR).
///
/// \descr The Function Router is responsible for
///
///        Map input signals (which have CAN signal structure) to (an internal representation of) light functions
///        Resolve priorities for light functions
///        Compute target values and speed for logical lamps
///        Fail / Safe reactions for light functions
///        Transmit state information for LEDs
///
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include "FctR.h"
#include "FctR_Tgt.h"
#include "FctR_Data.h"
#include "FctR_Types.h"

#include <CodM.h>
//#include <Swc/Appl/ApplMain.h>

//=============================================================================
// functions
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief  FctR_Init
///
/// \descr  Initialize FctR module
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void FctR_Init(void)
{
  FctR_TgtInit();
}


//-----------------------------------------------------------------------------
/// \brief  FctR_Cycle
///
/// \descr  Cyclic function of FctR at every 10ms
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void FctR_Cycle(void)
{
  FctR_TgtLgt();
}


//-----------------------------------------------------------------------------
/// \brief  FctR_ParaFct0
///
/// \descr  The function maps the coding structure parameters block for the detected
///         side
///
/// \param  eCmd    : coding validity
/// \param  pData   : pointer to coding data structure
///
/// \return void
//-----------------------------------------------------------------------------
void FctR_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData)
{
  teFctR_EcuSide eEcuSideDetect;

  FctR_pCodingArea = pData;

  (void)FctR_RteAccess_Read_EcuSide(&eEcuSideDetect);

  if(eEcuSideDetect == eEcu_Left)
  {
    FctR_pLmmABlock = &pData->LmmA;
  }
  else
  {
    FctR_pLmmABlock = &pData->LmmA_B;
  }

  switch (eCmd)
  {
    case eParaFct0_CodingDataValid:
    {
      FctR_ucCodingState = FCTR_CODING_VALID;
    }
    break;

    case eParaFct0_CodingDataInvalid:
    {
      FctR_ucCodingState = FCTR_CODING_INVALID;
    }
    break;

    default:
    break;
  }

  // PRQA S 5324 2   // Program architecture and readability
  // PRQA S 5342 1   // Program architecture and readability
}

//-----------------------------------------------------------------------------
/// \brief  FctR_MapParams
///
/// \descr  Mapps the coding parameter in order to acces the in FctR
///
/// \param  [void]
///
/// \return [void]
//-----------------------------------------------------------------------------
void FctR_MapParams(void) 
{
  tsRteCodingParameters sCodingParameters;

  (void)Rte_Read_CodM_FctR_Para(&sCodingParameters);

  FctR_ParaFct0(sCodingParameters.eCodingState, sCodingParameters.psCodingParameters_Blocks);

}

// EOF
