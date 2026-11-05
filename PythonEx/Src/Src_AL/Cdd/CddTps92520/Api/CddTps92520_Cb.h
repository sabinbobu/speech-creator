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
/// \file   CddTps92520.h
///
/// \brief  API for callbacks of CddTps92520
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef CDD_TPS92520_CB_2021_01_21_H_
#define CDD_TPS92520_CB_2021_01_21_H_

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <Std_Types.h>


//-----------------------------------------------------------------------------
// Start declaration or definitions of functions
//-----------------------------------------------------------------------------
#define ctadCddLed_START_SEC_CODE
#include <../Cfg/CddTps92520_MemMap.h>

uint32  CddTps92520_SpiTx(const uint16 unDevIdx);
void    CddTps92520_SpiRx(const uint16 unDevIdx, const uint32 ulData);

boolean CddTps92520_SpiGetConfig(uint16* punData);

#define ctadCddLed_STOP_SEC_CODE
#include <../Cfg/CddTps92520_MemMap.h>
//-----------------------------------------------------------------------------
// End declaration or definitions of functions
//-----------------------------------------------------------------------------


#endif // CDD_TPS92520_CB_2021_01_21_H_
