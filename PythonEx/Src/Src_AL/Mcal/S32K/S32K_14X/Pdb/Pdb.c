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
/// \file  Pdb.c
///
/// \brief Pdb Lpit interfaces/runnables definitions
///
/// \author Stefan Tyirean (f75617c)
///         mailto: stefan.tyirean[at]marelli.com
///
/// \Date April 2021
///
//-----------------------------------------------------------------------------

//====================================================================
// Include files
//====================================================================

#include "Pdb.h"
#include "Pdb_Drv.h"
#include "Pdb_TargetTypes.h"

//====================================================================
// Global function definitions
//====================================================================

//-----------------------------------------------------------------------------
/// \brief Pdb_Init
///
/// \descr Programable Delay Block Initialization procedure
///
/// \param  sPdbDataCfg - PDB global config
///
/// \return void
//-----------------------------------------------------------------------------
void Pdb_Init(CONST_AL tsPdb_CfgData* CONST_AL psPdbDataCfg)
{
  // Check input config parameter
  if (psPdbDataCfg != NULL_PTR)
  {
    // Call Pdb Driver Init LLF 
    (void)Pdb_Drv_Init(psPdbDataCfg);
  }
  else
  {
    // NULL_PTR, Pdb configuration shall be avoided
  }
}

// EOF
