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
/// \file  CddSpi_PC_WIN32API.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef CDD_SPI_PC_WIN32API_2020_11_25_H_
#define CDD_SPI_PC_WIN32API_2020_11_25_H_

#include <Std_Types.h>
#include <CddSpi_Cfg.h>
#include <CddSpi_Types.h>

void CddSpi_InitIfc_Deriv(uint8 ucIfc);
void CddSpi_TransferMsg_Deriv(const tsCddSpiDevCfg* psDevCfg, uint16* punData);

#ifdef CDDSPI_CYCLIC_OPERATION
boolean CddSpi_Start_Deriv(void);
boolean CddSpi_Stop_Deriv(void);
void    CddSpi_Cycle_Deriv(void);
#endif

#endif // CDD_SPI_PC_WIN32API_2020_11_25_H_
