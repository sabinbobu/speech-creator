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
/// \file  Pdb_Drv.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef PDB_DRV_2021_03_16_H_
#define PDB_DRV_2021_03_16_H_

#include <Std_Types.h>
#include <../Cdd/CddAdc/Gen/CddAdc_Types.h>

Std_ReturnType CddAdc_Drv_InitPdb(tsCddAdc_CfgData sCfgData);
void PDB0_IRQHandler(void);
void PDB1_IRQHandler(void);

#endif // PDB_DRV_2021_03_16_H_
