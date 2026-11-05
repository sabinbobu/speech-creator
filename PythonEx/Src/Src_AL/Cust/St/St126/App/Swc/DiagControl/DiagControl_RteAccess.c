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
/// \file  DiagControl_RteAccess.c
///
/// \brief Diagnostic Control Take Over rte wrappers
///
/// \author Tyirean Stefan F75617C
///         mail to <stefan.tyirean[at]magnetimarelli.com>
//-----------------------------------------------------------------------------

#include <Rte.h>
#include "DiagControl_RteAccess.h"

#if (DIAGCONTROL_FULL_VARIANT_SUPPORTED != 0u)
//-----------------------------------------------------------------------------
/// \brief DiagControl_RteAccess_GetDiagAfsControlRoutine
///
/// \descr Get Afs Routine Control Routine Status
///
/// \param  *psRoutineInfo - Afs Control routine data inpus
///
/// \return void
//-----------------------------------------------------------------------------
void DiagControl_RteAccess_GetDiagAfsControlRoutine(tsDiagControl_AfsRoutineControl* psRoutineInfo)
{
  // Translation variable from RTE ports
  tsRte_AfsRoutineControl sAfsRoutineInfo = { eAfsControl_Unknown, eAfs_Off, FALSE, FALSE };

  // Read Diag Control RTE port
  (void)Rte_Read_Diag_RoutineControl(&sAfsRoutineInfo);

  // Get the info
  // Ack status
  psRoutineInfo->boRequestAckStatus = sAfsRoutineInfo.boRequestAckStatus;
  // Request status
  psRoutineInfo->boRequestStatus = sAfsRoutineInfo.boRequestStatus;
  // Diagnostic Control
  // PRQA S 4322 1 // cast ok, enums are alligned
  psRoutineInfo->eAfsControl = (teDiagControl_AfsRoutineControl)sAfsRoutineInfo.eAfsControl;
  // Diagnostic Request
  // PRQA S 4322 1 // cast ok, enums are alligned
  psRoutineInfo->eAfsRequest = (teDiagControl_AfsTakeOverRequest)sAfsRoutineInfo.eAfsRequest;
}

//-----------------------------------------------------------------------------
/// \brief DiagControl_RteAccess_SetAfsRoutineAck
///
/// \descr Acknowledge return for Diagnostic routine
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void DiagControl_RteAccess_SetAfsRoutineAck(boolean boStatus)
{
  // Translation variable from RTE ports
  tsRte_AfsRoutineControl sAfsRoutineInfo = { eAfsControl_Unknown, eAfs_Off, FALSE, FALSE };

  // Read Diag Control RTE port
  (void)Rte_Read_Diag_RoutineControl(&sAfsRoutineInfo);

  // Update the Acnowledge status
  sAfsRoutineInfo.boRequestAckStatus = boStatus;
  sAfsRoutineInfo.boRequestStatus = FALSE;

  // Write Diag Control RTE port
  (void)Rte_Write_Diag_RoutineControl(&sAfsRoutineInfo);
}

//-----------------------------------------------------------------------------
/// \brief DiagControl_RteAccess_SetAfsMode
///
/// \descr Seta AFS requests for Swcs which handle light requests
///
/// \param  boAfsMasterOn - Diag Contol Master On
/// \param  eAfsRequest - Afs Request
///
/// \return void
//-----------------------------------------------------------------------------
void DiagControl_RteAccess_SetAfsMode(boolean boAfsMasterOn, teDiagControl_AfsTakeOverRequest eAfsRequest)
{
  // Translation variable to RTE ports
  tsRte_AfsDiagControl sAfsState = { eCtrlAFS_AfsOff, eLowBeamBoostAllowed_False, ePedestrianAllowed_False, FALSE, FALSE };

  // Init the default values
  sAfsState.boDiagRequestStatus = boAfsMasterOn;
  sAfsState.eLowBeamBoostAlwd = eLowBeamBoostAllowed_False;
  sAfsState.ePedestrianAlwd = ePedestrianAllowed_False;

  // Translate the diag control type to Rte
  switch (eAfsRequest)
  {
    // AFS off
    case eDiagControl_Afs_Off:
      sAfsState.eDiagRequestAfsState = eCtrlAFS_AfsOff;
      sAfsState.boDiagRequestStatus = FALSE;
      break;
    // Town
    case eDiagControl_Town:
      sAfsState.eDiagRequestAfsState = eCtrlAFS_Town;
      break;
    // Pedestrian
    case eDiagControl_Pedestrian:
      sAfsState.eDiagRequestAfsState = eCtrlAFS_Town;
      sAfsState.ePedestrianAlwd = ePedestrianAllowed_True;
      break;
    // Country
    case eDiagControl_Country:
      sAfsState.eDiagRequestAfsState = eCtrlAFS_Country;
      break;
    // Motorway
    case eDiagControl_Motorway:
      sAfsState.eDiagRequestAfsState = eCtrlAFS_Motorway;
      break;
    // Boost Lb
    case eDiagControl_Boost:
      sAfsState.eDiagRequestAfsState = eCtrlAFS_Motorway;
      sAfsState.eLowBeamBoostAlwd = eLowBeamBoostAllowed_True;
      break;
    // Bad Weather L
    case eDiagControl_Bad_Weather_L:
      sAfsState.eDiagRequestAfsState = eCtrlAFS_BadWeatherLhd;
      break;
    // Bad Weather R
    case eDiagControl_Bad_Weather_R:
      sAfsState.eDiagRequestAfsState = eCtrlAFS_BadWeatherRhd;
      break;
    // Foggy Left
    case eDiagControl_Fog_L:
      sAfsState.eDiagRequestAfsState = eCtrlAFS_FoggyLhd;
      break;
    // Foggy Right
    case eDiagControl_Fog_R:
      sAfsState.eDiagRequestAfsState = eCtrlAFS_FoggyRhd;
      break;
    // default
    default:
      sAfsState.eDiagRequestAfsState = eCtrlAFS_Invalid;
      break;
  }

  // Rte write
  //(void)Rte_Write_DiagControl_AfsState(&sAfsState);
}
#endif

// EOF
