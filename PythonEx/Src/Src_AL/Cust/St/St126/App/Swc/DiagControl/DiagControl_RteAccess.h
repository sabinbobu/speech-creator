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
/// \file  DiagControl_RteAccess .h
///
/// \brief Diagnostic Control Take Over rte wrappers header file
///
/// \author Tyirean Stefan F75617C
///         mail to <stefan.tyirean[at]magnetimarelli.com>
//-----------------------------------------------------------------------------
#ifndef DIAG_CONTROL_RTE_ACCESS_2021_11_11_H_
#define DIAG_CONTROL_RTE_ACCESS_2021_11_11_H_

#include "DiagControl_Types.h"
#include "DiagControl.h"

#if (DIAGCONTROL_FULL_VARIANT_SUPPORTED != 0u)
void DiagControl_RteAccess_GetDiagAfsControlRoutine(tsDiagControl_AfsRoutineControl* psRoutineInfo);
void DiagControl_RteAccess_SetAfsRoutineAck(boolean boStatus);
void DiagControl_RteAccess_SetAfsMode(boolean boAfsMasterOn, teDiagControl_AfsTakeOverRequest eAfsRequest);
#endif

#endif // DIAG_CONTROL_RTE_ACCESS_2021_11_11_H_

// EOF
