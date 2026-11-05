//*****************************************************************************
// (C) Marelli Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Marelli Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Marelli Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  CddMlc_Adapter.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef CDD_MLC_ADAPTER_2024_04_01_H
#define CDD_MLC_ADAPTER_2024_04_01_H

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <AL_Helper.h>

//-----------------------------------------------------------------------------
// Prototypes
//-----------------------------------------------------------------------------
void riCddMlc_Init(void);
void rpCddMlc_Cycle0(void);

uint8 CddMlc_GetEEPROMAddressId(void);

#endif // CDD_MLC_ADAPTER_2024_04_01_H
