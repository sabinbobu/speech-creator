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
/// \file  Pdb_Dr.h
///
/// \brief Lpit Driver header file (low access to the PDB pheripheric)
///
/// \author Stefan Tyirean (f75617c)
///         mailto: stefan.tyirean[at]marelli.com
///
/// \Date April 2021
///
//-----------------------------------------------------------------------------
#ifndef PDB_DRV_2021_03_16_H_
#define PDB_DRV_2021_03_16_H_

//====================================================================
// Include files
//====================================================================

#include <Std_Types.h>
#include <Pdb.h>
#include "Pdb_TargetTypes.h"

//====================================================================
// Global functions declaration
//====================================================================

Std_ReturnType Pdb_Drv_Init(CONST_AL tsPdb_CfgData* CONST_AL psPdbDataCfg);

void PDB0_IRQHandler(void);
void PDB1_IRQHandler(void);

#endif // PDB_DRV_2021_03_16_H_

// EOF
