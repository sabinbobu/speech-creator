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
/// \file  DiagControl.h
///
/// \brief Diagnostic Control Take Over routines header file
///
/// \author Tyirean Stefan F75617C
///         mail to <stefan.tyirean[at]magnetimarelli.com>
//-----------------------------------------------------------------------------
#ifndef DIAG_CONTROL_2021_11_11_H_
#define DIAG_CONTROL_2021_11_11_H_

#include <Cfg/Cfg.h>

// Macro to see if FULL Ecu variant is supported
#if defined (CFG_VARIANT_FULL) || (UNIT_TEST)
// not needed anymore
#define DIAGCONTROL_FULL_VARIANT_SUPPORTED 0u
#else
#define DIAGCONTROL_FULL_VARIANT_SUPPORTED 0u
#endif

void  DiagControl_Init(void);
void  DiagControl_Cycle0(void);
void  DiagControl_ProgrammingSesion_Request(void);

#endif // DIAG_CONTROL_2021_11_11_H_
