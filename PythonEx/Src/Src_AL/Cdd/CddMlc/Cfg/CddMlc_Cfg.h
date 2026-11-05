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
/// \file  CddMlc_Cfg.h
///
/// \brief
///
//-----------------------------------------------------------------------------

//=============================================================================
//  !!! ATTENTION : DO NOT create include guard for this file ! 
//=============================================================================


#include <CddMlc_Mac.h>
//==============================================================================
//  PROROTYPES : TODO: include header file for each driver
//==============================================================================
#ifdef UNIT_TEST

#include <Test_Ext.h>

#else
void CddTpsGen2_Init(void);
void CddTpsGen2_Cycle(void);

void CddTpsGen3_Init(void);
void CddTpsGen3_Cycle(void);


#endif
void CddTpsMixed_Init(void);
void CddTpsMixed_Cycle(void);
//==============================================================================
//  User Configuration: Driver map
//==============================================================================

BEGIN_MLC_DEVICE_CONFIGURATION
  MLC_DEVICE_CONFIG(DEV_TI_GEN2,   COM_UART_OVER_CAN, CddTpsGen2_Init,  CddTpsGen2_Cycle)
  MLC_DEVICE_CONFIG(DEV_TI_GEN3,   COM_UART_OVER_CAN, CddTpsGen3_Init,  CddTpsGen3_Cycle)
  MLC_DEVICE_CONFIG(DEV_MIXED_TI,  COM_UART_OVER_CAN, CddTpsMixed_Init, CddTpsMixed_Cycle)
END_MLC_DEVICE_CONFIGURATION
