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
/// \file  CddTpsGen3_Cb.h
///
/// \brief
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
///
//-----------------------------------------------------------------------------
#ifndef CDD_TPS_GEN3_CB_2024_02_05_H
#define CDD_TPS_GEN3_CB_2024_02_05_H

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <Std_Types.h>

#ifndef UNIT_TEST
#include <CddUart_Types.h>
#else
#include <Test/Test_Ext.h>
#endif


//-----------------------------------------------------------------------------
// Declaration or definitions of functions
//-----------------------------------------------------------------------------
void    CddTpsGen3_UartRx(const uint8* pucRxData, boolean boRxStatus);
void    CddTpsGen3_UartTx(tsCddUart_MessageEntryType* psTxCbData);

#endif // CDD_TPS_GEN3_CB_2024_02_05_H
