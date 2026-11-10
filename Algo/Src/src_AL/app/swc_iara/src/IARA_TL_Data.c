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
/// \file  IARA_TL_Data.c
///
/// \brief  

///
/// \author Srijin P(M12911A)
///         mailTo:srijin.p@marelli.com
//-----------------------------------------------------------------------------

 //-----------------------------------------------------------------------------
 // Includes
 //-----------------------------------------------------------------------------

// #include <Swc/CodM/CodM_Para.h>

// #include <RteCommonTypes.h>
#include "IARA_TL_Data.h"
#include "IARA_TL_Types.h"
#include "IARA_TL.h"
//#include "Rte_Type.h"
//#include "Rte.h"


 //-----------------------------------------------------------------------------
 // Defines
 //-----------------------------------------------------------------------------
 
 //-----------------------------------------------------------------------------
 // Variables
 //-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
ExtY_IARA_T IARA_TL_Y;
 
//volatile Bool ActivateModel = 1;
//volatile Bool ResetNVMToDefault = 0;
volatile tis32IARA_Acceleration_ms2 Accelerometer_ms2[3] = {0 , 0 , 0}; /* LSB: 2^-22 OFF: 0 MIN/MAX: -512 .. 511.999
 999761581 */
static tis32IARA_Acceleration_ms2 PrevAccelerometer_ms2[3] = {0 , 0 , 0};
volatile tis32IARA_AngleSpeed_rads Gyroscope_rads[3] = {0 , 0 , 0}; /* LSB: 2^-22 OFF: 0 MIN/MAX: -512 .. 511.9999997
 61581 */
static tis32IARA_AngleSpeed_rads PrevGyroscope_rads[3] = {0 , 0 , 0};
volatile UInt8 IMUSeqCntr;
volatile tis32IARA_AngleSpeed_rads RefAngVelz_rads = 0; /* LSB: 2^-22 OFF: 0 MIN/MAX: -512 .. 511.999
 999761581 */
volatile tis32IARA_Speed_ms WheelSpeed_RearLeft_ms = 0; /* LSB: 2^-22 OFF: 0 MIN/MAX: -512 .. 511.999999761581
 */
volatile tis32IARA_Speed_ms WheelSpeed_RearRight_ms = 0; /* LSB: 2^-22 OFF: 0 MIN/MAX: -512 .. 511.999999761581
 */
volatile tis32IARA_Temperarur_C Temp_c = 0; /* LSB: 2^-21 OFF: 0 MIN/MAX: -1024 .. 1023.99999952316
 */
volatile Bool DoorOpenSts = FALSE;
volatile tieIARA_GearStates GearSts = Iara_GearForward;
volatile tieIARA_BrakeStates BreakSts = Iara_BrakeReleased;
volatile tieIARA_BrakeStates ParkBreakSts = Iara_BrakeReleased;
volatile tieIARA_SignalStates CANSignalsSts = Iara_SignalValid;
volatile Bool MountingSide_Left = TRUE;
volatile Bool LearningActive = TRUE;
volatile tieIARA_SelfCalibCmd SelfCalibrationCmd = Iara_SelfCalibNoCommand;
//-----------------------------------------------------------------------------
// Data Types
//-----------------------------------------------------------------------------

 //-----------------------------------------------------------------------------
 // Funtion prototypes
 //-----------------------------------------------------------------------------
STATIC_AL void IARA_TL_Data_MapParams(void);

//-----------------------------------------------------------------------------
// Funtions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \func   IARA_TL_Data_ParaFct0
///
/// \brief  IARA coding parameters
///
/// \param  eCmd (coding data valid / invalid)
/// \param  pData (pointer to coding data ram copy)
///
/// \return void
//-----------------------------------------------------------------------------
// void IARA_TL_Data_ParaFct0(CONST_AL tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData)
// {
  // set pointer to Nvm Data
  // IARA_TL_Data_pCodingArea   = pData;
  // IARA_TL_Data_boCodingValid = (eCmd == eParaFct0_CodingDataValid) ? TRUE : FALSE;
// }

//-----------------------------------------------------------------------------
/// \brief  IARA_TL_Data_MapParams
///
/// \descr  Mapps the coding parameter in order to acces the in IARA_TL_Data
///
/// \param  [void]
///
/// \return [void]
//-----------------------------------------------------------------------------
STATIC_AL void IARA_TL_Data_MapParams(void)
{
  // tsRteCodingParameters sCodingParameters;  /* RTE port for IARA coding parameters */

  // (void)Rte_Read_CodM_IARA_TL_Para(&sCodingParameters);

  // IARA_TL_Data_ParaFct0(sCodingParameters.eCodingState, sCodingParameters.psCodingParameters_Blocks);

}

//-----------------------------------------------------------------------------
/// \brief  IARA_TL_Data_Init
///
/// \descr  initialize IARA data
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
void IARA_TL_Data_Init(void)
{
  IARA_TL_Data_MapParams();
}

//-----------------------------------------------------------------------------
// Input Functions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \brief  IARA_TL_GetActivateModel
///
/// \descr  get the model activation command
///
/// \param  - 
///
/// \return boolean :  Disable model = 0U,
///                    Activate model = 1U.
//-----------------------------------------------------------------------------
boolean IARA_TL_GetActivateModel(void)
{
  boolean  activateIARA;
  activateIARA = TRUE;
  return activateIARA;
}

//-----------------------------------------------------------------------------
/// \brief  IARA_TL_GetNVMResetFlag
///
/// \descr  Get the NVM reset flag
///
/// \param  - 
///
/// \return boolean :  Do not reset to NVM values = 0, 
///                    Reset to NVM values = 1.
//-----------------------------------------------------------------------------
boolean IARA_TL_GetNVMResetFlag(void)
{
  boolean NVMresetFlg;
  static uint8 StepCnt = 0U;
  if (StepCnt < 1U)
  {
	  NVMresetFlg = TRUE;
	  StepCnt++;
  }
  else
  {
	  NVMresetFlg = FALSE;
  }
  return NVMresetFlg;
}

//-----------------------------------------------------------------------------
/// \brief  IARA_TL_GetAccelerometerData
///
/// \descr  Get the accelerometer data
///
/// \param  - 
///
/// \return void
//-----------------------------------------------------------------------------
void IARA_TL_GetAccelerometerData(tis32IARA_Acceleration_ms2 *AccData)
{
  AccData[0] = Accelerometer_ms2[0];
  AccData[1] = Accelerometer_ms2[1];
  AccData[2] = Accelerometer_ms2[2];
}

//-----------------------------------------------------------------------------
/// \brief  IARA_TL_GetGyroscopeData
///
/// \descr  Get the Gyroscope data
///
/// \param  - 
///
/// \return void 
//-----------------------------------------------------------------------------
void IARA_TL_GetGyroscopeData(tis32IARA_AngleSpeed_rads *GyrData)
{
  
  GyrData[0] = Gyroscope_rads[0];
  GyrData[1] = Gyroscope_rads[1];
  GyrData[2] = Gyroscope_rads[2]; 
}


//-----------------------------------------------------------------------------
/// \brief  IARA_TL_GetIMUSequenceCounter
///
/// \descr  - Get IMU sequence counter
///
/// \param  - 
///
/// \return uint8
//-----------------------------------------------------------------------------
uint8 IARA_TL_GetIMUSequenceCounter(void)
{
  if ((Accelerometer_ms2[0] != PrevAccelerometer_ms2[0])||(Accelerometer_ms2[1] != PrevAccelerometer_ms2[1])||
      (Accelerometer_ms2[2] != PrevAccelerometer_ms2[2])||(Gyroscope_rads[0] != PrevGyroscope_rads[0])||
	  (Gyroscope_rads[1] != PrevGyroscope_rads[1])||(Gyroscope_rads[2] != PrevGyroscope_rads[2])){
		  if (IMUSeqCntr == 255U)
		  {
			  IMUSeqCntr = 0;
		  }
		  IMUSeqCntr++;
		  PrevAccelerometer_ms2[0] = Accelerometer_ms2[0];
		  PrevAccelerometer_ms2[1] = Accelerometer_ms2[1];
		  PrevAccelerometer_ms2[2] = Accelerometer_ms2[2];
		  Gyroscope_rads[0] = PrevGyroscope_rads[0];
		  Gyroscope_rads[1] = PrevGyroscope_rads[1];
		  Gyroscope_rads[2] = PrevGyroscope_rads[2];
		  
	  }
  return IMUSeqCntr;
}

//-----------------------------------------------------------------------------
/// \brief  IARA_TL_GetRefAngVelZ_rads
///
/// \descr  - Get Reference angular velocity in z in rads
///
/// \param  - 
///
/// \return - tis32IARA_AngleSpeed_rads: int32
//-----------------------------------------------------------------------------
tis32IARA_AngleSpeed_rads IARA_TL_GetRefAngVelZ_rads(void)
{
  tis32IARA_AngleSpeed_rads RefAngVelZrads = RefAngVelz_rads;
  return RefAngVelZrads;
}

//-----------------------------------------------------------------------------
/// \brief  IARA_TL_GetRLWhlSpeed
///
/// \descr  - Get Rear Left wheel speed
///
/// \param  - 
///
/// \return - tis32IARA_Speed_ms: int32
//-----------------------------------------------------------------------------
tis32IARA_Speed_ms IARA_TL_GetRLWhlSpeed(void)
{
  tis32IARA_Speed_ms  RLWheelSpd = WheelSpeed_RearLeft_ms;
  return RLWheelSpd;
}

//-----------------------------------------------------------------------------
/// \brief  IARA_TL_GetRRWhlSpeed
///
/// \descr  - Get Rear Right wheel speed
///
/// \param  - 
///
/// \return - tis32IARA_Speed_ms: int32
//-----------------------------------------------------------------------------
tis32IARA_Speed_ms IARA_TL_GetRRWhlSpeed(void)
{
  tis32IARA_Speed_ms  RRWheelSpd = WheelSpeed_RearRight_ms;
  return RRWheelSpd;
}

//-----------------------------------------------------------------------------
/// \brief  IARA_TL_GetTemp
///
/// \descr  - Get temperature data in celsius
///
/// \param  - 
///
/// \return - tis32IARA_Temperarur_C: int32
//-----------------------------------------------------------------------------
tis32IARA_Temperarur_C IARA_TL_GetTemp(void)
{
  tis32IARA_Temperarur_C  IMUTemp_c = Temp_c;
  return IMUTemp_c;
}

//-----------------------------------------------------------------------------
/// \brief  IARA_TL_GetAnyDoorOpen_b
///
/// \descr  - Get any Door open status
///
/// \param  - 
///
/// \return - boolean
//-----------------------------------------------------------------------------
boolean IARA_TL_GetAnyDoorOpen_b(void)
{
  boolean AnyDoorOpen = DoorOpenSts;
  return AnyDoorOpen;
}

//-----------------------------------------------------------------------------
/// \brief  IARA_TL_GetGearState
///
/// \descr  - Get the gear status
///
/// \param  - 
///
/// \return - Enum:tieIARA_GearStates
///           Iara_GearParking(0)
///           Iara_GearNeutral(1)
///           Iara_GearForward(2)
///           Iara_GearReverse(3)
///           Iara_GearInvalid(255)
//-----------------------------------------------------------------------------
tieIARA_GearStates IARA_TL_GetGearState(void)
{
  tieIARA_GearStates IARAGearState = GearSts;
  return IARAGearState;
}

//-----------------------------------------------------------------------------
/// \brief  IARA_TL_GetBreakState
///
/// \descr  - Get the brake status
///
/// \param  - 
///
/// \return - Enum:tieIARA_BrakeStates
///           Iara_BrakeReleased(0)
///           Iara_BrakeEngaged(1)
///           Iara_BrakeInvalid(255)
//-----------------------------------------------------------------------------
tieIARA_BrakeStates IARA_TL_GetBrakeState(void)
{
  tieIARA_BrakeStates IARABrakeState = BreakSts;
  return IARABrakeState;
}

//-----------------------------------------------------------------------------
/// \brief  IARA_TL_GetParkBrakeState
///
/// \descr  - Get the park brake brake status
///
/// \param  - 
///
/// \return - Enum:tieIARA_BrakeStates
///           Iara_BrakeReleased(0)
///           Iara_BrakeEngaged(1)
///           Iara_BrakeInvalid(255)
//-----------------------------------------------------------------------------
tieIARA_BrakeStates IARA_TL_GetParkBrakeState(void)
{
  tieIARA_BrakeStates IARAParkBrakeState = ParkBreakSts;
  return IARAParkBrakeState;
}

//-----------------------------------------------------------------------------
/// \brief  IARA_TL_GetCANSignalState
///
/// \descr  - Get the CAN signal state
///
/// \param  - 
///
/// \return - Enum: tieIARA_SignalStates
///           Iara_SignalSNA(0)
///           Iara_SignalValid(1)
///           Iara_SignalError(2)
//-----------------------------------------------------------------------------
tieIARA_SignalStates IARA_TL_GetCANSignalState(void)
{
  tieIARA_SignalStates CANSignalState = CANSignalsSts;
  return CANSignalState;
}

//-----------------------------------------------------------------------------
/// \brief  IARA_TL_GetMountingSide
///
/// \descr  Get Mounting side
///
/// \param   
///
/// \return boolean 
//-----------------------------------------------------------------------------
boolean IARA_TL_GetMountingSide(void)
{
  boolean MountingSide_b = MountingSide_Left;
  return MountingSide_b;
}

//-----------------------------------------------------------------------------
/// \brief  IARA_TL_GetActivateLearning
///
/// \descr  Get learning activation command
///
/// \param  
///
/// \return boolean 
//-----------------------------------------------------------------------------

boolean IARA_TL_GetActivateLearning(void)
{
  boolean ActivateLearningCmd = LearningActive;
  return ActivateLearningCmd;
}

//-----------------------------------------------------------------------------
/// \brief IARA_TL_GetSelfCalibrationCmd

///
/// \descr  Get the self caliberation command
///
/// \param  
///
/// \return Enum:tieIARA_SelfCalibCmd
///         Iara_SelfCalibNoCommand(0)
///         Iara_SelfCalibStart(1)
///         Iara_SelfCalibStop(2)
///         Iara_SelfCalibSetAutoStop(3)
///         Iara_SelfCalibResetAutoStop(4)
///         Iara_SelfCalibResetNVMToDefault(5)
//-----------------------------------------------------------------------------
tieIARA_SelfCalibCmd IARA_TL_GetSelfCalibrationCmd(void)
{
  tieIARA_SelfCalibCmd SelfCalibCmd = SelfCalibrationCmd;
  return SelfCalibCmd;
}


//-----------------------------------------------------------------------------
//Output Fuctions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \brief IARAData_Pitch_rad

///
/// \descr  Write the IARA pitch in rad
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void IARAData_Pitch_rad(tis32IARA_Angle_rad *IARAPitchRad)
{
  *IARAPitchRad = IARA_TL_Y.IARAPitch_rad;
}

//-----------------------------------------------------------------------------
/// \brief IARAData_Roll_rad

///
/// \descr  Write the IARA roll in rad
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void IARAData_Roll_rad(tis32IARA_Angle_rad *IARARollRad)
{
  *IARARollRad = IARA_TL_Y.IARARoll_rad;
}

//-----------------------------------------------------------------------------
/// \brief IARAData_EarthPitch_rad

///
/// \descr  Write the Earth pitch in rad
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void IARAData_EarthPitch_rad(tis32IARA_Angle_rad *EarthPitchRad)
{
  *EarthPitchRad = IARA_TL_Y.EarthPitch_rad;
}

//-----------------------------------------------------------------------------
/// \brief IARAData_EarthRoll_rad

///
/// \descr  Write the Earth roll in rad
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void IARAData_EarthRoll_rad(tis32IARA_Angle_rad *EarthRollRad)
{
  *EarthRollRad = IARA_TL_Y.EarthRoll_rad;
}

//-----------------------------------------------------------------------------
/// \brief IARAData_RegressionCoefficient

///
/// \descr  Write the regression coefficients
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void IARAData_RegressionCoefficient(tisIARA_RegressionCoeff *Regressionoeff)
{
  *Regressionoeff = IARA_TL_Y.RegressionCoefficients;
}

//-----------------------------------------------------------------------------
/// \brief IARAData_LearningSts

///
/// \descr  Write the IARA learning status
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void IARAData_LearningSts(tieIARA_LearningStates *LearningSts)
{
  *LearningSts = IARA_TL_Y.IARALearningStatus_en;
}

//-----------------------------------------------------------------------------
/// \brief IARAData_IARAEnblSts

///
/// \descr  Write the IARA Enable status
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void IARAData_IARAEnblSts(Bool *IARAEnblSts)
{
  *IARAEnblSts = IARA_TL_Y.IARAEnabled_b;
}

//-----------------------------------------------------------------------------
/// \brief IARAData_IARAState

///
/// \descr  Write the IARA state
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void IARAData_IARAState(tieIARA_ModelStates *IARAState)
{
  *IARAState = IARA_TL_Y.IARAState_en;
}

//-----------------------------------------------------------------------------
/// \brief IARAData_IMUSignalState

///
/// \descr  Write the IMU signal state
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void IARAData_IMUSignalState(tieIARA_SignalStates *IMUSignalsSts)
{
  *IMUSignalsSts = IARA_TL_Y.IMUSignalsStatus_en;
}

//-----------------------------------------------------------------------------
/// \brief IARAData_PitchPlausibility

///
/// \descr  Write the IARA pitch plausibility
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void IARAData_PitchPlausibility(tieIARA_SignalStates *IARAPitchPlaus)
{
  *IARAPitchPlaus = IARA_TL_Y.IARAPitchPlausibility_en;
}

//-----------------------------------------------------------------------------
/// \brief IARAData_StillStandAlgoSts

///
/// \descr  Write the Still stand Algo Status
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void IARAData_StillStandAlgoSts(tisIARA_StillStandAlgoStatus *StillStandAlgoSts)
{
  *StillStandAlgoSts = IARA_TL_Y.StillStandAlgoStatus;
}

//-----------------------------------------------------------------------------
/// \brief IARAData_SelfCalibSts

///
/// \descr  Write the Self Caliberation status
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void IARAData_SelfCalibSts(tisIARA_SelfCalibrationStatus *SelfCalibSts)
{
  *SelfCalibSts = IARA_TL_Y.SelfCalibrationStatus;
}

//-----------------------------------------------------------------------------
/// \brief IARAData_SensorOrientCalib_deg

///
/// \descr  Write the sensor orientation caliberation in degrees
///
/// \param  
///
/// \return void
//-----------------------------------------------------------------------------
void IARAData_SensorOrientCalib_deg(tis32IARA_Angle_deg *SensorOrientationCalib_deg)
{
  SensorOrientationCalib_deg[0] = IARA_TL_Y.SensorOrientationCalibration_deg[0];
  SensorOrientationCalib_deg[1] = IARA_TL_Y.SensorOrientationCalibration_deg[1];
  SensorOrientationCalib_deg[2] = IARA_TL_Y.SensorOrientationCalibration_deg[2];
}


// EOF
