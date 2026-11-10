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
/// \file  IARA_TL.c

///
/// \author P Srijin (M12911A)
///         mailTo:srijin.p@marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include "IARA_TL.h"

ExtU_IARA_T IARA_TL_U;
tis32IARA_Angle_rad IARAPitchRad;
tis32IARA_Angle_rad IARARollRad;
tis32IARA_Angle_rad EarthPitchRad;
tis32IARA_Angle_rad EarthRollRad;
tisIARA_RegressionCoeff Regressionoeff;
tieIARA_LearningStates LearningSts;
Bool IARAEnblSts;
tieIARA_ModelStates IARAState;
tieIARA_SignalStates IMUSignalsSts;
tieIARA_SignalStates IARAPitchPlaus;
tisIARA_StillStandAlgoStatus StillStandAlgoSts;
tisIARA_SelfCalibrationStatus SelfCalibSts;
tis32IARA_Angle_deg SensorOrientationCalib_deg[3];

// Functions
//=============================================================================


//-----------------------------------------------------------------------------
/// \brief  IARA_Init
///
/// \descr  initialize IARA
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
void IARA_TL_Init(void)
{
  return; // nothing to do
}


// ---------------------------------------------------------------------------
///
///  \func     IARA_TL_Cycle0
///
///  \brief    cyclic function called every ms
///
///  \param    none
///
///  \return   none
///
// ---------------------------------------------------------------------------

void IARA_TL_Cycle0(void)
{

IARA_TL_U.ActivateIARA_b = IARA_TL_GetActivateModel();
IARA_TL_U.ResetNVMToDefault_b = IARA_TL_GetNVMResetFlag();
IARA_TL_GetAccelerometerData(IARA_TL_U.IMUAccelerometer_ms2);
IARA_TL_GetGyroscopeData(IARA_TL_U.IMUGyroscope_rads);
IARA_TL_U.IMUSequenceCounter = IARA_TL_GetIMUSequenceCounter();
IARA_TL_U.RefAngularVelocityZ_rads = IARA_TL_GetRefAngVelZ_rads();
IARA_TL_U.WhlSpeed_RearLeft_ms = IARA_TL_GetRLWhlSpeed();
IARA_TL_U.WhlSpeed_RearRight_ms = IARA_TL_GetRRWhlSpeed();
IARA_TL_U.IMUTemperature_C = IARA_TL_GetTemp();
IARA_TL_U.AnyDoorOpen_b = IARA_TL_GetAnyDoorOpen_b();
IARA_TL_U.GearState_en = IARA_TL_GetGearState();
IARA_TL_U.BreakState_en = IARA_TL_GetBrakeState();
IARA_TL_U.ParkBreakState_en = IARA_TL_GetParkBrakeState();
IARA_TL_U.CANSignalsStatus_en = IARA_TL_GetCANSignalState();
IARA_TL_U.IsMountingSideLeft_b = IARA_TL_GetMountingSide();
IARA_TL_U.LearningActive_b = IARA_TL_GetActivateLearning();
IARA_TL_U.SelfCalibrationCommand_en = IARA_TL_GetSelfCalibrationCmd();

  // --------------------------------------------------------------------------
  // call algorithm
  // --------------------------------------------------------------------------
  IARA_Main();
  //---------------------------------------------------------------------------

  // --------------------------------------------------------------------------
  // write outputs
  // --------------------------------------------------------------------------
  // --------------------------------------------------------------------------
  // --------------------------------------------------------------------------
  // IARA Pitch in rad
  IARAData_Pitch_rad(&IARAPitchRad);
  // --------------------------------------------------------------------------
  // IARA Roll in rad
  IARAData_Roll_rad(&IARARollRad);
  // --------------------------------------------------------------------------
  // Earth Pitch in rad
  IARAData_EarthPitch_rad(&EarthPitchRad);
  // --------------------------------------------------------------------------
  // Earth roll in rad
  IARAData_EarthRoll_rad(&EarthRollRad);
  // --------------------------------------------------------------------------
  // Regression Coefficients
  IARAData_RegressionCoefficient(&Regressionoeff);
  // --------------------------------------------------------------------------  
  // IARA Learning Status
  IARAData_LearningSts(&LearningSts);
  // --------------------------------------------------------------------------
  // IARA Enable Status 
  IARAData_IARAEnblSts(&IARAEnblSts);
  // --------------------------------------------------------------------------
  // IARA State
  IARAData_IARAState(&IARAState);
  // --------------------------------------------------------------------------
  // IMU Signal State
  IARAData_IMUSignalState(&IMUSignalsSts);
  // --------------------------------------------------------------------------
  // IARA Pitch plausibility
  IARAData_PitchPlausibility(&IARAPitchPlaus);
  // --------------------------------------------------------------------------
  // Still stand Algo status
  IARAData_StillStandAlgoSts(&StillStandAlgoSts);
  // --------------------------------------------------------------------------
  // Self Caliberation status
  IARAData_SelfCalibSts(&SelfCalibSts);
  // --------------------------------------------------------------------------
  // Sensor orientation caliberation in deg
  IARAData_SensorOrientCalib_deg(SensorOrientationCalib_deg);
  // --------------------------------------------------------------------------

}
