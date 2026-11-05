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
/// \file  DiagControl_Types.h
///
/// \brief Diagnostic Control Typess
///
/// \author Tyirean Stefan F75617C
///         mail to <stefan.tyirean[at]magnetimarelli.com>
//-----------------------------------------------------------------------------
#ifndef DIAG_CONTROL_TYPES_2021_11_11_H_
#define DIAG_CONTROL_TYPES_2021_11_11_H_

#include <Al_Helper.h>
#include "DiagControl.h"

#if (DIAGCONTROL_FULL_VARIANT_SUPPORTED != 0u)
typedef enum
{
  eDiagControl_AfsStart = 0,
  eDiagControl_AfsStop,
  eDiagControl_AfsResults,
  eDiagControl_AfsUnknown
}teDiagControl_AfsRoutineControl;

typedef enum
{
  eDiagControl_Afs_Off = 1,
  eDiagControl_Town = 2,
  eDiagControl_Pedestrian = 3,
  eDiagControl_Country = 4,
  eDiagControl_Motorway = 5,
  eDiagControl_Boost = 6,
  eDiagControl_Bad_Weather_L = 7,
  eDiagControl_Bad_Weather_R = 8,
  eDiagControl_Fog_L = 9,
  eDiagControl_Fog_R = 10,
  eDiagControl_Sequence_L = 11,
  eDiagControl_Sequence_R = 12,
}teDiagControl_AfsTakeOverRequest;

typedef struct
{
  teDiagControl_AfsRoutineControl eAfsControl;
  teDiagControl_AfsTakeOverRequest eAfsRequest;
  boolean boRequestStatus;
  boolean boRequestAckStatus;
}tsDiagControl_AfsRoutineControl;
#endif


#endif // DIAG_CONTROL_TYPES_2021_11_11_H_

// EOF
