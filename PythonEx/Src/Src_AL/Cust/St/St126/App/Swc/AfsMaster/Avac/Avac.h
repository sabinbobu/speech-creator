#ifndef __AVAC_H__
#define __AVAC_H__

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
/// \file  Avac.h
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


//=============================================================================
// Functions
//=============================================================================

//  void Avac_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData);
  void Avac_ParaChanged(void);
  void Avac_Init(void);
  void Avac_Cycle0(void);
  void riAvac_Init(void);
  void rpAvac_Cycle0(void);


#endif // __AVAC_H__
