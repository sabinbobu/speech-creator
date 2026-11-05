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
/// \file   CddEft_Adapter.c
///
/// \brief  Adapter for EFT data access above RTE
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#include <Std_Types.h>
#include <CddEft.h>
#include <CddEft_Adapter.h>

//=============================================================================
//  Static variable declarations
//=============================================================================


//-----------------------------------------------------------------------------
/// \brief  Init runnable
///
/// \descr  Init runnable to be called at MCU startup
///         This function shall perform CRC check
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void riCddEftInit(void)
{
  CddEft_Init();
}


