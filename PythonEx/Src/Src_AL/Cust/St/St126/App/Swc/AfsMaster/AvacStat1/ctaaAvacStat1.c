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
/// \file  ctaaAvac.c
///
/// \brief  
///
/// \descr  
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Traulsen, Alf ALRT/EEG-PM2 (taf2rt)
///         mailTo:Alf.Traulsen[at]al-lighting.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

//#include <Bsw/Sys/Load/SysLoadRunable.h>
#include <Swc/AfsMaster/AvacStat1/AvacStat1.h>
#include <ctaaAvacStat1.h>


//=============================================================================
// functions
//=============================================================================

/// ---------------------------------------------------------------------------
/// \func     riAvacStat1_Init
///
/// \brief    init runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void riAvacStat1_Init(void)
{
  //SYS_LOAD_RI_BEGIN(0, RunId_riAvacStat1__Init)

  AvacStat1_Init();

  //SYS_LOAD_RI_END()
}


/// ---------------------------------------------------------------------------
/// \func     rpAvacStat1_Cycle0
///
/// \brief    cyclic runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void rpAvacStat1_Cycle0(void)
{
  //SYS_LOAD_RP_BEGIN(RunId_rpAvacStat1__Cycle0)

  AvacStat1_Cycle0();

  //SYS_LOAD_RP_END(RunId_rpAvacStat1__Cycle0)
}

// EOF

