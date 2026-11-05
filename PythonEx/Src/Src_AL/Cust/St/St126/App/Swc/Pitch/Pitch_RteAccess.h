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
/// \file  Pitch_RteAcsess.h
///
/// \brief Header of wrapper file
///
/// Autor: Farcas Ciprian - Ionut(M)
///        ciprian - ionut.farcas@marelli.com
//-----------------------------------------------------------------------------
#ifndef PITCH_RTE_ACSESS_2021_11_02_H_
#define PITCH_RTE_ACSESS_2021_11_02_H_

//=============================================================================
// includes
//=============================================================================
#include "Pitch_Types.h"
#ifndef UNIT_TEST
#include <Rte.h>
#endif // !UNIT_TEST




//=============================================================================
// functions prototypes
//=============================================================================

// getter functions
void Pitch_RteAccess_Get_VehicleSpeed(tsPitch_VehicleSpeed* psData);
void Pitch_RteAccess_Get_VehNetState(tsPitch_VehNetState* psData);
void Pitch_RteAccess_Get_GetSens_Raw(uint16* punCntSens);
void Pitch_RteAccess_Get_GetSens_Balanced(sint32* pslCntSens);
void Pitch_RteAccess_Get_VCCX1Voltage(uint16* punVccx1);
void Pitch_RteAccess_Get_CodingPara(tsPitch_CodingParam *psCodingParam);
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
void Pitch_RteAccess_Get_GetAdlPhase(tePitch_LvlPhase* psData);
#elif defined(SAMPLE_ECO)
void Pitch_RteAccess_Get_GetAslPhase(tePitch_LvlPhase* psData);
#endif

// setter functions
void Pitch_RteAccess_Set_Angle(tsPitch* psPitch);
void Pitch_RteAccess_Set_SensorFailureState(tePitchSensorState* pePitch);


#endif // PITCH_RTE_ACSESS_2021_11_02_H_
