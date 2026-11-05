#ifndef __PITCH_DATA_H__
  #define __PITCH_DATA_H__

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
/// \file  PitchData.h
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
#include "Pitch.h"
#include "Pitch_Types.h"

//=============================================================================
// externals (for use in LOCAL_INLINE functions only)
//=============================================================================
extern tNvmPara_CodingArea* Pitch_pCodingArea;  // pointer to const data

//=============================================================================
// prototypes
//=============================================================================
boolean Pitch_CodingDataValidation(void);

//=============================================================================
// LOCAL_INLINE functions
//=============================================================================

LOCAL_INLINE sint16   Cod_Pitch_SensorSlope(const uint32 ul) { return ul == 0 ? Pitch_pCodingArea->AvacStp.PitchData.snSensorSlopeFront : Pitch_pCodingArea->AvacStp.PitchData.snSensorSlopeRear; }
LOCAL_INLINE uint16   Cod_Pitch_Wheelbase(void)              { return Pitch_pCodingArea->AvacStp.PitchData.unWHEELBASE; }

LOCAL_INLINE uint16   Cod_Pitch_SensMin(void)                { return (uint16)(((uint16)Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens * 65536u) / 100u); }
LOCAL_INLINE uint16   Cod_Pitch_SensMax(void)                { return (uint16)(((uint16)Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens * 65536u) / 100u); }

LOCAL_INLINE uint16   Cod_Pitch_VccxMin(void)                { return Pitch_pCodingArea->AvacStp.PitchData.unVccx_Min; }
LOCAL_INLINE uint16   Cod_Pitch_VccxMax(void)                { return Pitch_pCodingArea->AvacStp.PitchData.unVccx_Max; }

LOCAL_INLINE sint32   Cod_Pitch_AngleMin(void)               { return  (sint32)Pitch_pCodingArea->AvacStp.PitchData.snAngleMin ; }  // [0.1mrad] (-3deg)
LOCAL_INLINE sint32   Cod_Pitch_AngleMax(void)               { return  (sint32)Pitch_pCodingArea->AvacStp.PitchData.snAngleMax; }  // [0.1mrad] (+3deg)

LOCAL_INLINE uint16   Cod_Pitch_ErrCntMax(void)              { return  100u; }  // have to be divided to 20 until timers will be used 100 * 20ms = 2s

LOCAL_INLINE uint8    Cod_Pitch_DPF(void)                    { return (Pitch_pCodingArea->AvacStp.PitchData.ucDPF*10u); } // Compression of tires parameters for front (1.1 default)
LOCAL_INLINE uint8    Cod_Pitch_DPR(void)                    { return (Pitch_pCodingArea->AvacStp.PitchData.ucDPR)*10u; }  // Compression of tires parameters for rear  (1.1 default)
LOCAL_INLINE uint16   Cod_Pitch_R1(void)                     { return  Pitch_pCodingArea->AvacStp.PitchData.unR1; }      // Front wheel radius [0.1mm]
LOCAL_INLINE uint16   Cod_Pitch_R2(void)                     { return  Pitch_pCodingArea->AvacStp.PitchData.unR2;}       // Rear wheel radius  [0.1mm]

LOCAL_INLINE uint16   Cod_Pitch_SensOutrangeTime(void)       { return (Pitch_pCodingArea->AvacStp.PitchData.SensorOutRangeTime * 20u); }
LOCAL_INLINE uint16   Cod_Pitch_SensFailRecoverTime(void)    { return (Pitch_pCodingArea->AvacStp.PitchData.SensorFailureRecoveryTime * 20u); }

LOCAL_INLINE uint16   Cod_Pitch_SensPlausVehSpeed(void)      { return ((Pitch_pCodingArea->AvacStp.PitchData.BhsPlausVehSpeed) * 100u); }
#endif // __PITCH_DATA_H__

// EOF
