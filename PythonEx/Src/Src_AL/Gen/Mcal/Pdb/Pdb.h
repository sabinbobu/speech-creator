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
/// \file  Pdb.h
///
/// \brief Mcal Pdb interfaces/runnables
///
/// \author Stefan Tyirean (f75617c)
///         mailto: stefan.tyirean[at]marelli.com
///
/// \Date April 2021
///
//-----------------------------------------------------------------------------
#ifndef PDB_2021_03_24_H_
#define PDB_2021_03_24_H_

#include <Pdb_TargetTypes.h>
#include <AL_Helper.h>

#if defined(__cplusplus)
extern "C"
{
#endif

  // Pdb data structure for Pdb init procedure
  extern CONST_AL tsPdb_CfgData Pdb_sPdbDatatCfg;

  // Pdb init (EcuM in start-up phase)
  void Pdb_Init(CONST_AL tsPdb_CfgData* CONST_AL psPdbDataCfg);

#if defined(__cplusplus)
}
#endif

#endif // PDB_2021_03_24_H_

// EOF
