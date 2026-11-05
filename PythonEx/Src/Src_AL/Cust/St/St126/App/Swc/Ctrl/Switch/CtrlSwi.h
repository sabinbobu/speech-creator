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
/// \file   CtrlSwi.h
///
/// \brief  API for CtrlSwi
///
/// \author ZHAO, Kai ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef CTRL_HSS_2021_05_20_H_
#define CTRL_HSS_2021_05_20_H_

//=============================================================================
// Includes
//=============================================================================
#include <Std_Types.h>
#include <RteCommonTypes.h>
#ifndef UNIT_TEST
#include <Rte.h>
#endif

//=============================================================================
// macros
//=============================================================================

//=============================================================================
// Exported functions
//=============================================================================
void CtrlSwi_Init(void);
void CtrlSwi_Cycle0(void);
void CtrlSwi_DeInit(void);
void CtrlSwi_ParaFct0(tParaFct0_Cmd eCmd, tNvmPara_CodingArea*  pData);
void roCtrlSwiExtTakeoverSwitchHssOutputChannel0Start(uint8 ucChannelNo, uint8 ucSwitchOutput);
void roCtrlSwiExtTakeoverSwitchHssOutputChannel0Stop(uint8 ucChannelNo);
//void roCtrlSwiGetOnTime(tiu32HssChannel ulIx, tiu32TimeDiff_us* ulTimeDiff);

#endif // CTRL_HSS_2021_05_20_H_

// EOF 
