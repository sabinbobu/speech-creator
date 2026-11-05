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
/// \brief
///
//-----------------------------------------------------------------------------

#ifndef DIAG_CONTROL_RTE_ACCESS_2021_11_11_H_
#define DIAG_CONTROL_RTE_ACCESS_2021_11_11_H_

#include "DiagControl_Types.h"

void DiagControl_GetDiagAfsControlRoutine(tsDiagControl_AfsRoutineControl* sRoutineInfo);
void DiagControl_SetAfsRoutineAck(boolean boStatus);

#endif // DIAG_CONTROL_RTE_ACCESS_2021_11_11_H_

// EOF
