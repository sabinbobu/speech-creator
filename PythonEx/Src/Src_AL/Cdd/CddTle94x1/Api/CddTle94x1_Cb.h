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
/// \file   CddTle94x1_Cb.h
///
/// \brief  API for callbacks of CddTle94x1
///
/// \author Diana Ursan
/// \e-mail: elena-diana.ursan[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CDD_TLE94X1_CB_2021_04_13_H_
#define CDD_TLE94X1_CB_2021_04_13_H_


//=============================================================================
// Includes
//=============================================================================
#include <Std_Types.h>


//=============================================================================
// Prototypes
//=============================================================================
uint32 CddTle94x1_SpiTx(uint16 unIx);
void   CddTle94x1_SpiRx(uint16 unIx, uint32 ulData);


#endif // CDD_TLE94x1_CB_2021_04_13_H_
