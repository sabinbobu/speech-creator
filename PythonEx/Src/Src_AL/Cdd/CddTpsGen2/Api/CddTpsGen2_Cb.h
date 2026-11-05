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
/// \file  CddTpsGen2_Cb.h
///
/// \brief  API for callbacks of Tps92662A
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
///
//-----------------------------------------------------------------------------
#ifndef CDD_TPS_GEN2_CB_2024_01_30_H_
#define CDD_TPS_GEN2_CB_2024_01_30_H_

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <Std_Types.h>
#include <CddUart_Types.h>

// structure for a message in the LmmUart ringbuffer


//-----------------------------------------------------------------------------
// Declaration or definitions of functions
//-----------------------------------------------------------------------------

void    CddTpsGen2_UartRx(const uint8* pucRxData, boolean boRxStatus);
void    CddTpsGen2_UartTx(tsCddUart_MessageEntryType* psTxCbData);


#endif // CDD_TPS92662A_CB_2023_09_04_H
