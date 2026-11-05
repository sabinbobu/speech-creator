
#ifndef __RTX_CONFIG2_H__
#define __RTX_CONFIG2_H__

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
/// \file  RTX_Config_CPUload.h
///
/// \brief  
///
/// \descr  header
///
///         
///         
///
/// \author Liviu Topliceanu (F03343C)
///         mailTo:liviu.topliceanu[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include <Std_Types.h>

//=============================================================================
// defines
//=============================================================================

//=============================================================================
// types
//=============================================================================

typedef struct
{
  uint32 ulTimeEntry;
  uint32 ulTimeExit;
  boolean boEventEntry;
  boolean boEventExit;
}RTX_tsCPULoad_CheckPoint;

//=============================================================================
// function prototypes
//=============================================================================

void RTX_WorkThreadSwitch_Notification(void);
void RTX_IdleThreadSwitch_Notification(void);
void RTX_Timer_Notification(void);
void RTX_Custom_IdleTask(void);

#endif /* (__RTX_CONFIG2_H__) */
