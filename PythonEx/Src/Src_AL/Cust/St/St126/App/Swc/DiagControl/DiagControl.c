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
/// \file  DiagControl.c
///
/// \brief Diagnostic Control Take Over routines
///
/// \author Tyirean Stefan F75617C
///         mail to <stefan.tyirean[at]magnetimarelli.com>
//-----------------------------------------------------------------------------
#include <AL_Helper.h>
#include "DiagControl_Types.h"
#include "DiagControl_RteAccess.h"
#include "DiagControl.h"
#include <Util_Time.h>
#include "DiagControl.h"
#include <Diag_Callbacks.h>


// Programing session take-over time-out
#define DIAGCONTROL_PROG_SESSION_TO_MS      1000u

#if (DIAGCONTROL_FULL_VARIANT_SUPPORTED != 0u)
#define DIAGCONTROL_AFS_SEQUENCE_TIME_MS    1000u

STATIC_AL void DiagControl_AfsTakeOver(void);

STATIC_AL teDiagControl_AfsTakeOverRequest DiagControl_SequenceMachine(CONST_AL teDiagControl_AfsTakeOverRequest* psData, uint8_least ucLength);

// Afs Sequence for Left Headlamp (Start sequence Left - 0x0B)
STATIC_AL CONST_AL teDiagControl_AfsTakeOverRequest DiagControl_aeAfsLeftSequence[]  = { eDiagControl_Motorway, eDiagControl_Boost, eDiagControl_Bad_Weather_L, eDiagControl_Fog_L, eDiagControl_Town, eDiagControl_Pedestrian, eDiagControl_Afs_Off };
// Afs Sequence for Left Headlamp (Start sequence Right - 0x0C)
STATIC_AL CONST_AL teDiagControl_AfsTakeOverRequest DiagControl_aeAfsRightSequence[] = { eDiagControl_Motorway, eDiagControl_Boost, eDiagControl_Bad_Weather_R, eDiagControl_Fog_R, eDiagControl_Town, eDiagControl_Pedestrian, eDiagControl_Afs_Off };
// Afs Current State
STATIC_AL teDiagControl_AfsTakeOverRequest DiagControl_eCurrentAfsState = eDiagControl_Afs_Off;
// Afs Sequence  Switch-On Status
STATIC_AL boolean DiagControl_boAfsOn = FALSE;
// Afs Start Sequence Status
STATIC_AL boolean DiagControl_boStartSequence = TRUE;
// Afs Sequence Timer
STATIC_AL uint32 DiagControl_ulAfsSequenceTimer = 0u;

#endif

// Programing session take-over
STATIC_AL void DiagControl_ProgramingSession_TakeOver(void);

// Programing Session Take-Over variables (flag and timer)
STATIC_AL boolean DiagControl_boProgramingReq_Status  = FALSE;
STATIC_AL uint32  DiagControl_ulTmrProgSessison       = 0u;


//-----------------------------------------------------------------------------
/// \brief DiagControl_Init
///
/// \descr Diagnostic Control (Take-Over) Initialization Routine
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void DiagControl_Init(void)
{
  return;
}


//-----------------------------------------------------------------------------
/// \brief DiagControl_Cycle0
///
/// \descr Diagnostic Control (Take-Over) Cyclic Routine
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void DiagControl_Cycle0(void)
{
#if (DIAGCONTROL_FULL_VARIANT_SUPPORTED != 0u)
  // Afs Routine Control
  DiagControl_AfsTakeOver();
#endif
  DiagControl_ProgramingSession_TakeOver();
}


#if (DIAGCONTROL_FULL_VARIANT_SUPPORTED != 0u)
//-----------------------------------------------------------------------------
/// \brief DiagControl_AfsTakeOver
///
/// \descr Afs Take Over Routine
///
/// \param void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void DiagControl_AfsTakeOver(void)
{
  // Afs control request
  tsDiagControl_AfsRoutineControl sAfsControlRequest;
  // Diagnostic take over status (master)
  boolean boDiagControlMasterStat = FALSE;

  // Get Afs Control Routine
  DiagControl_RteAccess_GetDiagAfsControlRoutine(&sAfsControlRequest);

  // Check the Diag Request status and Diagnostic Request (Start)
  if ((sAfsControlRequest.boRequestStatus != FALSE) && (sAfsControlRequest.eAfsControl == eDiagControl_AfsStart))
  {
    // Set Afs Status On
    DiagControl_boAfsOn = TRUE;
    // Set Acknowledge in order to handle the Diagnostic Result
    DiagControl_RteAccess_SetAfsRoutineAck(TRUE);
  }
  // Check the Diag Request status and Diagnostic Request (Stop)
  else if ((sAfsControlRequest.boRequestStatus != FALSE) && (sAfsControlRequest.eAfsControl == eDiagControl_AfsStop))
  {
    // // Set Afs Status Off
    DiagControl_boAfsOn = FALSE;
    // Prepare the flag for sequence start when the sequence start is requested
    DiagControl_boStartSequence = TRUE;
    // Clear Acknowledge in order to handle the Diagnostic Result
    DiagControl_RteAccess_SetAfsRoutineAck(FALSE);
  }
  else
  {
    // No one of the presvios states (no Afs request or Request is Result)
  }
 
  // Diagnostic Control over AFS
  if (DiagControl_boAfsOn != FALSE)
  {
    // Is request different than sequence
    if ((sAfsControlRequest.eAfsRequest != eDiagControl_Sequence_L) && (sAfsControlRequest.eAfsRequest != eDiagControl_Sequence_R))
    {
      // Set current state
      DiagControl_eCurrentAfsState = sAfsControlRequest.eAfsRequest;
    }
    // Sequence for left headlamp
    else if (sAfsControlRequest.eAfsRequest == eDiagControl_Sequence_L)
    {
      // Run the sequence for left
      DiagControl_eCurrentAfsState = DiagControl_SequenceMachine(DiagControl_aeAfsLeftSequence, sizeof(DiagControl_aeAfsLeftSequence) / sizeof(DiagControl_aeAfsLeftSequence[0]));
    }
    // Sequence for right headlamp
    else
    {
      // Sequence for right headlamp
      DiagControl_eCurrentAfsState = DiagControl_SequenceMachine(DiagControl_aeAfsRightSequence, sizeof(DiagControl_aeAfsRightSequence) / sizeof(DiagControl_aeAfsRightSequence[0]));
    }

    // Set diagnostic master control over light requests (take-over)
    boDiagControlMasterStat = TRUE;
  }
  else
  {
    // No Afs request, set Afs off
    DiagControl_eCurrentAfsState = eDiagControl_Afs_Off;
  }

  // Write diagnosti Afs Request on RTE
  DiagControl_RteAccess_SetAfsMode(boDiagControlMasterStat, DiagControl_eCurrentAfsState);
}

//-----------------------------------------------------------------------------
/// \brief DiagControl_SequenceMachine
///
/// \descr AFS sequence machine
///
/// \param  psData - sequence array (left/right)
///
/// \return STATIC_AL teDiagControl_AfsTakeOverRequest
//-----------------------------------------------------------------------------
STATIC_AL teDiagControl_AfsTakeOverRequest DiagControl_SequenceMachine(CONST_AL teDiagControl_AfsTakeOverRequest* psData, uint8_least ucLength)
{
  // Afs Sequence Return
  STATIC_UT(teDiagControl_AfsTakeOverRequest, eReturnState, eDiagControl_Afs_Off);
  // Sequence Index
  STATIC_UT(uint8_least, ucIndx, 0u);

  // Afs start is requested
  if (DiagControl_boStartSequence == TRUE)
  {
    // return the first state of sequence
    eReturnState = psData[0];
    // Reset the sequence index
    ucIndx = 0u;
    // Get the time
    DiagControl_ulAfsSequenceTimer = TimerGetTick();
    // Clear the sequence start flag
    DiagControl_boStartSequence = FALSE;
  }
  else
  {
    // Time-Out on sequence step
    if (TimerGetTimeSince(DiagControl_ulAfsSequenceTimer) >= UTILTIME_MSEC(DIAGCONTROL_AFS_SEQUENCE_TIME_MS))
    {
      // Increment the step or reset in at the end
      ucIndx = (ucIndx == ucLength) ? 0u : (ucIndx + 1u);
      // Get the time
      DiagControl_ulAfsSequenceTimer = TimerGetTick();
      // return the current state of the input sequence
      eReturnState = psData[ucIndx];
    }
    else
    {
      // there is no time-out, skip
    }
  }
  // return current state of the Afs sequence
  return eReturnState;
}
#endif

//-----------------------------------------------------------------------------
/// \brief DiagControl_ProgramingSession_TakeOver
///
/// \descr Programing Session Take-Over (waiting for valid Can Inputs)
///
/// \param  void
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void DiagControl_ProgramingSession_TakeOver(void)
{
  // Programming session Request
  if ((DiagControl_boProgramingReq_Status != FALSE))
  {
    // Diag Intergrationb mode
    if (roDiag_IntegrationMode() != FALSE)
    {
      // Programing session accepted
      roDiag_Callbacks_ProgramingSessionAccepted();
      // Clear flag
      DiagControl_boProgramingReq_Status = FALSE;
    }
    else
    {
      // Check the timer 
      if (TimerGetTimeSince(DiagControl_ulTmrProgSessison) >= UTILTIME_MSEC(DIAGCONTROL_PROG_SESSION_TO_MS))
      {
        // Clear flag
        DiagControl_boProgramingReq_Status = FALSE;
        // General reject
        roDiag_Callbacks_NRC_Response(0x22u);
      }
      else
      {
        // wait
      }
    }
  }
}


//-----------------------------------------------------------------------------
/// \brief DiagControl_ProgrammingSesion_Request
///
/// \descr Programming Session Request when Can signals are not available (or invalid)
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void  DiagControl_ProgrammingSesion_Request(void)
{
  DiagControl_boProgramingReq_Status = TRUE;
  DiagControl_ulTmrProgSessison = TimerGetTick();
}

// EOF
