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
/// \file   CddNcv78702_Cb.h
///
/// \brief  API for callbacks of CddNcv78702
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef CDD_NCV78702_CB_2021_03_25_H_
#define CDD_NCV78702_CB_2021_03_25_H_


//=============================================================================
// Includes
//=============================================================================
#include <Std_Types.h>


//-----------------------------------------------------------------------------
// Start declaration or definitions of functions
//-----------------------------------------------------------------------------
#define ctadCddBoost_START_SEC_CODE
#include <../Cfg/CddNcv78702_MemMap.h>

uint32 CddNcv78702_SpiTx(const uint16 unIx);
void   CddNcv78702_SpiRx(const uint16 unIx, const uint32 ulData);

#define ctadCddBoost_STOP_SEC_CODE
#include <../Cfg/CddNcv78702_MemMap.h>
//-----------------------------------------------------------------------------
// End declaration or definitions of functions
//-----------------------------------------------------------------------------


#endif // CDD_NCV78702_CB_2021_03_25_H_
