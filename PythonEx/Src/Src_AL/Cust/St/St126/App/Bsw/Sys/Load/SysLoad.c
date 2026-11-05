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
/// \file  SysLoad.c
///
/// \brief
///
//-----------------------------------------------------------------------------
//=============================================================================
//  Includes
//=============================================================================

#include <Bsw/Common/Std_Types.h>

//=============================================================================
//  Global variables
//=============================================================================

// Variable used to track the call orders. It is incremented once in every runnable/task/isr that is measured.
volatile uint32 tiSysLoad_ExecutionOrder_Number;

// EOF
