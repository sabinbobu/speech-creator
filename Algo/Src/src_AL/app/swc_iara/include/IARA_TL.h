#ifndef __IARA_TL_H__
#define __IARA_TL_H__

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
/// \file  IARA_TL.h
///
/// \brief  
///
///
/// \author P Srijin (M12911A)
///         mailTo:srijin.p@marelli.com
//-----------------------------------------------------------------------------


//=============================================================================
// includes
//=============================================================================

// #include <Bsw/Common/Std_Types.h>
#include <Std_Types.h>
#include "IARA_TL_Data.h"
#include "IARA_TL_Types.h"
#include "IARA_TL_Ifc.h"
#include "IARA_TL_Main.h"
#include <AL_Helper.h>

/*------------------------------------------------------------------------------------------------*\
  DEFINES
\*------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------*\
  TYPEDEFS
\*------------------------------------------------------------------------------------------------*/


//=============================================================================
// Functions
//=============================================================================

  void IARA_TL_Init(void);
  void IARA_TL_Cycle0(void);

/*------------------------------------------------------------------------------------------------*\
  FUNCTION PROTOTYPES
\*------------------------------------------------------------------------------------------------*/

extern void IARA_TL_Data_Init(void);

extern void IARAData_Pitch_rad(tis32IARA_Angle_rad *IARAPitchRad);
extern void IARAData_Roll_rad(tis32IARA_Angle_rad *IARARollRad);
extern void IARAData_EarthPitch_rad(tis32IARA_Angle_rad *EarthPitchRad);
extern void IARAData_EarthRoll_rad(tis32IARA_Angle_rad *EarthRollRad);
extern void IARAData_RegressionCoefficient(tisIARA_RegressionCoeff *Regressionoeff);
extern void IARAData_LearningSts(tieIARA_LearningStates *LearningSts);
extern void IARAData_IARAEnblSts(Bool *IARAEnblSts);
extern void IARAData_IARAState(tieIARA_ModelStates *IARAState);
extern void IARAData_IMUSignalState(tieIARA_SignalStates *IMUSignalsSts);
extern void IARAData_PitchPlausibility(tieIARA_SignalStates *IARAPitchPlaus);
extern void IARAData_StillStandAlgoSts(tisIARA_StillStandAlgoStatus *StillStandAlgoSts);
extern void IARAData_SelfCalibSts(tisIARA_SelfCalibrationStatus *SelfCalibSts);
extern void IARAData_SensorOrientCalib_deg(tis32IARA_Angle_deg *SensorOrientationCalib_deg);



extern boolean IARA_TL_GetActivateModel(void);
extern boolean IARA_TL_GetNVMResetFlag(void);
extern void IARA_TL_GetAccelerometerData(tis32IARA_Acceleration_ms2 *AccData);
extern void IARA_TL_GetGyroscopeData(tis32IARA_AngleSpeed_rads *GyrData);
extern uint8 IARA_TL_GetIMUSequenceCounter(void);
extern tis32IARA_AngleSpeed_rads IARA_TL_GetRefAngVelZ_rads(void);
extern tis32IARA_Speed_ms IARA_TL_GetRLWhlSpeed(void);
extern tis32IARA_Speed_ms IARA_TL_GetRRWhlSpeed(void);
extern tis32IARA_Temperarur_C IARA_TL_GetTemp(void);
extern boolean IARA_TL_GetAnyDoorOpen_b(void);
extern tieIARA_GearStates IARA_TL_GetGearState(void);
extern tieIARA_BrakeStates IARA_TL_GetBrakeState(void);
extern tieIARA_BrakeStates IARA_TL_GetParkBrakeState(void);
extern tieIARA_SignalStates IARA_TL_GetCANSignalState(void);
extern boolean IARA_TL_GetMountingSide(void);
extern boolean IARA_TL_GetActivateLearning(void);
extern tieIARA_SelfCalibCmd IARA_TL_GetSelfCalibrationCmd(void);

#endif // __IARA_TL_H__
/*------------------------------------------------------------------------------------------------*\
  END OF FILE
\*------------------------------------------------------------------------------------------------*/
