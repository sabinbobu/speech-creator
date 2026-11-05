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
/// \file  AdbPxa3Data.c
///
/// \brief  
///
/// \descr  
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Alf Traulsen  (taf2rt)
///         mailTo:alf.traulsen@al-lighting.com
//-----------------------------------------------------------------------------

#include <CodM.h>
#include <CodM_Para.h>
#include "AdbPxa3Data.h"
#include <AL_Helper.h>
#include <Rte.h>

//=============================================================================
// Global variables
//=============================================================================
CONST_AL tNvmPara_CodingArea*  AdbPxa3Data_pCodingArea;
boolean                     AdbPxa3Data_boCodingValid; 

//=============================================================================
// Functions
//=============================================================================
void AdbPxa3Data_MapParams(void);
//-----------------------------------------------------------------------------
/// \func   AdbPxa3Data_ParaFct0
///
/// \brief  AdbMxb2 coding parameters
///
/// \param  eCmd (coding data valid / invalid)
/// \param  pData (pointer to coding data ram copy)
///
/// \return void
//-----------------------------------------------------------------------------
void AdbPxa3Data_ParaFct0(CONST_AL tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData)
{
  // set pointer to Nvm Data
  AdbPxa3Data_pCodingArea   = pData;
  AdbPxa3Data_boCodingValid = (boolean) (eCmd == eParaFct0_CodingDataValid) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
/// \brief  AdbPxa3Data_MapParams
///
/// \descr  Mapps the coding parameter in order to acces the in AdbPxa3Data
///
/// \param  [void]
///
/// \return [void]
//-----------------------------------------------------------------------------
void AdbPxa3Data_MapParams(void)
{
  tsRteCodingParameters sCodingParameters;

  Rte_Read_CodM_Adb_Pxa_Para(&sCodingParameters);

  AdbPxa3Data_ParaFct0(sCodingParameters.eCodingState, sCodingParameters.psCodingParameters_Blocks);

}

//-----------------------------------------------------------------------------
/// \brief  AdbPxa3Data_Init
///
/// \descr  initialize AdbMxb1 data
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
void AdbPxa3Data_Init(void)
{
  AdbPxa3Data_MapParams();
}
