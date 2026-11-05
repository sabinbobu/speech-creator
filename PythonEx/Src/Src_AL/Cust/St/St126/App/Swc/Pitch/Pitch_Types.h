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
/// \file  Pitch_Type.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef PITCH_TYPE_2021_11_02_H_
#define PITCH_TYPE_2021_11_02_H_

//=============================================================================
// includes
//=============================================================================
#include <Std_Types.h>
#include <AL_Helper.h>
#include <Cfg/Cfg.h>
#include <Rte\RteCommonTypes.h>
#ifndef UNIT_TEST
#include <Rte.h>
#endif // !UNIT_TEST



//=============================================================================
// types
//=============================================================================
typedef  teRte_SigQty tucPitchSigQty;
typedef struct
{
  sint16      nDisp[CFG_CntSens];     ///< [1/10 mm] moving up --> positive value
  tucPitchSigQty  eSigQty[CFG_CntSens];
} tsDisplacement;

typedef struct
{
  sint16      nAngle;           ///< [1/10 mrad] front side up --> positive value
  sint16      nHeightErr;       ///< [1/10 mrad] headlights up --> positive value
  tucPitchSigQty  eSigQty;
} tsPitch;

typedef struct
{
 uint16  IdSigLo;
 uint16  IdSigHi;
}tsPitchErrIdSet;

typedef struct
{
  uint8 aucSigLo[CFG_CntSens];
  uint8 aucSigHi[CFG_CntSens];
}tsPitchErrCnt;

typedef struct
{
  tNvmPara_CodingArea* psCodingParameters_Blocks;
  tParaFct0_Cmd        eCodingState;
}tsPitch_CodingParam;

typedef enum
{
  eHLS_NO_FAILURE,
  eHLS_SENSOR_FAILURE,
  eHLS_FROZEN_FAILURE,
  eHLS_STORED_FAILURE
}tePitchSensorState;

typedef enum
{
  ePlaus_NO_FAILURE = 0U,
  ePlaus_FAILURE    = 1U,
  ePlaus_NO_DATA    = 3U
}tePitchPlausState;

typedef enum
{
  eErrorTrigger = 0u,
  eClearErrTrigger = 1u
}tePitchErrorIdx;

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
typedef enum
{
  ePitchState_Init = 0,     // initial state
  ePitchState_Ref = 1,      // reference run active
  ePitchState_Adj = 2,      // Adjustment phase
  ePitchState_Fail = 3,     // stepper defect
  ePitchState_STT = 4,      // Cranking phase
  ePitchState_Maxsize = 5
} tePitch_LvlPhase;
#elif defined(SAMPLE_ECO)
typedef enum
{
  ePitchState_Init = 0,      // initial state
  ePitchState_Adj  = 1,      // Adjustment phase
  ePitchState_Fail = 2       // dc motor defect
} tePitch_LvlPhase;
#endif
typedef enum
{
  ePlauSig_Fail,
  ePlauSig_Pass,
  ePlauSig_SNA
} tePitch_PlauSigState;

typedef struct
{
  tsVitesseVehiculesRoues  eVehicleSpeed;
  tsChksumTrmeDynUcFrein   eChksumTrmeDynUcFrein;
  teVvhIndisp              eVehicleSpeedDispo;
  tsCptProcess4B38D        eCptProcess4B38D;
  teRte_SigQty             eSigQty; // Signal Quality
}tsPitch_VehicleSpeed;

typedef struct
{
  teRte_EtatPrincipSEV  eVESMainState;
  teRte_EtatReseauElec  eElectricNetworkState;
  teRte_SigQty          eSigQty; // Signal Quality
}tsPitch_VehNetState;
#endif // PITCH_TYPE_2021_11_02_H_
