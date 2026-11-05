#ifndef __PITCH_H__
  #define __PITCH_H__

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
/// \file  Pitch.h
///
/// \brief
///
/// \descr
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Ott, Peter ALRT/EEG-PM2 * (otp2rt)
///         mailTo:Peter.Ott@al-lighting.com
//-----------------------------------------------------------------------------
 #include <Std_Types.h>
 #include <Cfg/Cfg.h>
 #include <Swc/CodM/CodM.h>
 #include <Swc/CodM/CodM_Para.h>
 #include "Pitch_Types.h"
 #include "AL_Helper.h"


//=============================================================================
// defines
//=============================================================================
#define PITCH_TauTracking     UTIL_Tau128   // 128 * 20ms = 2.5s: time constant used for tracking filter
#define PITCH_JitterTol       10      // 10 * 0.1mm = 1mm:  minimum change for dynamic behaviour

#define PITCH_FR_SENSOR       0u
#define PITCH_RR_SENSOR       1u
#define PITCH_RADIUS_SCALING  10000
#define PITCH_ZERO_LEVEL_DONE 0xFFu

//=============================================================================
// prototypes
//=============================================================================

void Pitch_Init(void);
void Pitch_Cycle0(void);
void Pitch_AdjustmentCheckPlausibility(void);
void Pitch_FailureCheckPlausibility(void);
void Pitch_CheckSensMountingInit(void);
void Pitch_GetLocal_DisplacementSens(tsDisplacement* psDispSens);
void Pitch_SetLocal_DisplacementSens(tsDisplacement sDispSens);
tucPitchSigQty Pitch_CheckSensSupply(void);
tePitchSensorState Pitch_GetSensorError(void);
#endif // __PITCH_H__
