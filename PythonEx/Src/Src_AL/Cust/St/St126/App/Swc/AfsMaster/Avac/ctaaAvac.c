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
#include "Swc/AfsMaster/Avac/Avac.h"
#include <Bsw/Sys/Load/SysLoad.h>
#include "Avac.h"

#ifdef SYS_LOAD_RUNNABLE
SYS_LOAD_MEAS_VAR_DEC(riAvac_Init)
SYS_LOAD_MEAS_VAR_DEC(rpAvac_Cycle0)
#endif


//=============================================================================
// functions
//=============================================================================

/// ---------------------------------------------------------------------------
/// \func     riAvac_Init
///
/// \brief    init runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void riAvac_Init(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(riAvac_Init)
#endif

    Avac_Init();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(riAvac_Init)
#endif
}


/// ---------------------------------------------------------------------------
/// \func     rpAvac_Cycle0
///
/// \brief    cyclic runnable
///
/// \param    none
///
/// \return   none
///
/// \descr    
/// ---------------------------------------------------------------------------
void rpAvac_Cycle0(void)
{
#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_BEGIN(rpAvac_Cycle0)
#endif

  Avac_Cycle0();

#ifdef SYS_LOAD_RUNNABLE
  SYS_LOAD_MEAS_END(rpAvac_Cycle0)
#endif
}

// EOF

