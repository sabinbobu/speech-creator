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
/// \file  CddSpi_CallOuts.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef CDD_SPI_CALL_OUTS_2019_12_02_H_
#define CDD_SPI_CALL_OUTS_2019_12_02_H_

//=============================================================================
// Includes
//=============================================================================
#include <Std_Types.h>
#include <RteCommonTypes.h>


//=============================================================================
// Public function declarations
//=============================================================================
#if (CDDSPI_STATUS_FAULT == STD_ON)
void  CddSpi_StatusFault(uint8   ucData);
#endif
boolean CddSpi_GetStpConfig(uint16* punData);


#endif // CDD_SPI_CALL_OUTS_2019_12_02_H_