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
/// \file  CddSpi_PC_WIN32API.c
///
/// \brief
///
//-----------------------------------------------------------------------------
#include <Std_Types.h>
#include <CddSpi_PC_WIN32API.h>
#include <CddSpi_Cfg.h>
#include <stdio.h>

#ifndef UNIT_TEST
#include <CddSpi_Types.h>
#endif // UNIT_TEST

#ifndef UNIT_TEST
void CddSpi_InitIfc_Deriv(uint8 ucIfc)
{
  {};
  do {} while (0);
}

void CddSpi_TransferMsg_Deriv(const tsCddSpiDevCfg* psDevCfg, uint16* punData)
{
  (void)psDevCfg;
  (void)punData;
}

#ifdef CDDSPI_CYCLIC_OPERATION
boolean CddSpi_Start_Deriv(void)
{
  boolean boRetVal = FALSE;
  return boRetVal;
}

boolean CddSpi_Stop_Deriv(void)
{
  boolean boRetVal = FALSE;
  return boRetVal;
}
void CddSpi_Cycle_Deriv(void)
{

}
#endif
#endif // UNIT_TEST