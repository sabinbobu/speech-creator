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
/// \file  Pitch_SensPlau.c
///
/// \brief
///
/// \descr
///
///
/// \author Adrian Horlescu (F31197D)
///         mailTo:adrian-marian.horlescu[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include <Cfg/Cfg.h>
#ifndef UNIT_TEST
#include <Rte.h>
#ifdef SAMPLE_FULL
#include <CddStpIfc.h>
#endif
#endif // !UNIT_TEST


#include "PitchCfg.h"
#include "Pitch_Types.h"
#include "Pitch_Data.h"
#include "Pitch.h"
#include "Pitch_RteAccess.h"
#include <UtilMath.h>
#include <Nvm.h>


//=============================================================================
// defines
//=============================================================================

#define ASHR(x,y)  ( (x) >> (y) )
#define VEHICLE_THRESHOLD_MOVING_SPEED_SCALED	1500u         // Threshold speed greater than 15kmph to measure the vehicle moving state 
#define PITCH_PLAUS_HEALTIME_AFTER_RESET      5000u         // 5s to start detection of sensor state
#define PITCH_PLAUS_ERR_THRESHOLD             5u            // Threshold error less than 1 to set the plausibility error

  // order 1 filter support
#define PITCH_TAU_Abtast_Min     1
#define PITCH_TAU_Abtast_1x     47
#define PITCH_TAU_Abtast_2x     78
#define PITCH_TAU_Abtast_3x     92
#define PITCH_TAU_Abtast_4x    100
#define PITCH_TAU_Abtast_5x    105
#define PITCH_TAU_Abtast_6x    108
#define PITCH_TAU_Abtast_8x    113
#define PITCH_TAU_Abtast_10x   116
#define PITCH_TAU_Abtast_12x   118
#define PITCH_TAU_Abtast_15x   120
#define PITCH_TAU_Abtast_20x   122
#define PITCH_TAU_Abtast_25x   123
#define PITCH_TAU_Abtast_30x   124
#define PITCH_TAU_Abtast_40x   125
#define PITCH_TAU_Abtast_60x   126
#define PITCH_TAU_Abtast_130x  127

#define PITCH_Max_Filtered_Val 145

//=============================================================================
// variables
//=============================================================================

STATIC_AL tePitchSensorState Pitch_ePitchSensorFailure;
STATIC_AL TIMER Pitch_ulCheckBHS_us    = 0u;

STATIC_AL sint16 Sens_Disp[2];

STATIC_AL ORDER1_Filter Pitch_DT1SensFrontRMounting;
STATIC_AL ORDER1_Filter Pitch_PT1SensFrontRMountingPreOk;
STATIC_AL ORDER1_Filter Pitch_PT1SensFrontRMountingPreErr;
STATIC_AL ORDER1_Filter Pitch_PT1SensFrontRMountingOk;
STATIC_AL ORDER1_Filter Pitch_PT1SensFrontRMountingErr;

STATIC_AL ORDER1_Filter Pitch_DT1SensRearRMounting;
STATIC_AL ORDER1_Filter Pitch_PT1SensRearRMountingPreOk;
STATIC_AL ORDER1_Filter Pitch_PT1SensRearRMountingPreErr;
STATIC_AL ORDER1_Filter Pitch_PT1SensRearRMountingOk;
STATIC_AL ORDER1_Filter Pitch_PT1SensRearRMountingErr;

STATIC_AL sint16 Pitch_nSensFrontRHyst;
STATIC_AL sint16 Pitch_nSensFrontRGrad;
STATIC_AL sint16 Pitch_nSensFrontRFilterPreOk;
STATIC_AL sint16 Pitch_nSensFrontRFilterPreErr;
STATIC_AL sint16 Pitch_nSensFrontRFilterOk;
STATIC_AL sint16 Pitch_nSensFrontRFilterErr;

STATIC_AL sint16 Pitch_nSensRearRHyst;
STATIC_AL sint16 Pitch_nSensRearRGrad;
STATIC_AL sint16 Pitch_nSensRearRFilterPreOk;
STATIC_AL sint16 Pitch_nSensRearRFilterPreErr;
STATIC_AL sint16 Pitch_nSensRearRFilterOk;
STATIC_AL sint16 Pitch_nSensRearRFilterErr;

STATIC_AL uint8  Pitch_biSensFrontRMountingStateOk;
/* PRQA S 3229 1 */ /* TBD : Need to decide use of this variable to set related fault */
STATIC_AL uint8  Pitch_biSensFrontRMountingStateErr;
STATIC_AL uint8  Pitch_biSensRearRMountingStateOk;
/* PRQA S 3229 1 */ /* TBD : Need to decide use of this variable to set related fault */
STATIC_AL uint8  Pitch_biSensRearRMountingStateErr;

STATIC_AL sint16 Pitch_nSensFrontRInit;
STATIC_AL sint16 Pitch_nSensRearRInit;

STATIC_AL volatile tSensorPlausibility1Struct SensorPlausData = SensorPlausibility1INIT;

STATIC_AL TIMER Pitch_SensPlau_CheckSensState_us = 0u;

//=============================================================================
// prototypes
//=============================================================================

STATIC_AL tePitch_PlauSigState Pitch_CheckVehSpeedData(void);
STATIC_AL tePitch_PlauSigState Pitch_CheckSensValue(void);
STATIC_AL void                 Pitch_CheckSensMounting(void);
STATIC_AL void                 Pitch_CheckSensMountingState(void);
STATIC_AL void                 Pitch_SetNvmFlag(void);

STATIC_AL void   RateLimiterPwmSens(sint16* pRateLimiter, sint16 RateUp, sint16 RateDown, sint16  Value);
STATIC_AL void   Order1FilterPwmSens(ORDER1_Filter* const pFilter, const sint16 nValue, const uint16 unBeta);
STATIC_AL sint16 Order1FilterValuePwmSens(const ORDER1_Filter* const pFilter);
STATIC_AL void   Order1FilterInitPwmSens(ORDER1_Filter* const pFilter, const sint16 nValue);

//=============================================================================
// functions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief Pitch_AdjustmentCheckPlausibility
///
/// \descr This function is checking the sensor plausibility state when Adl phase
///        is read as Adjustment and is setting the Sensor Failure state for CtrlStp
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Pitch_AdjustmentCheckPlausibility(void)
{
  static tePitch_PlauSigState boVehSpeedState;
  static tePitch_PlauSigState boBhsValueState;
  static tePitch_PlauSigState boDispValueState;

  boVehSpeedState  = Pitch_CheckVehSpeedData();
  boDispValueState = Pitch_CheckSensValue();
  
  // Check vehicle speed data
  if (boVehSpeedState == ePlauSig_Pass)
  {
    // if veh speed data is valid, check Bhs measured sample
    Pitch_CheckSensMounting();
    Pitch_CheckSensMountingState();

    if (NvmBlockDeltaPwmPara.ucSensPlausError[0u] == (uint8)ePlaus_FAILURE ||
        NvmBlockDeltaPwmPara.ucSensPlausError[1u] == (uint8)ePlaus_FAILURE)
    {
      Pitch_ePitchSensorFailure = eHLS_FROZEN_FAILURE;
    }
  }
  else if (boDispValueState == ePlauSig_Fail)
  {
    Pitch_ePitchSensorFailure = eHLS_SENSOR_FAILURE;
  }
  else
  {
    // do nothing
  }

  // Write Sensor Failure for CtrlStp
  (void)Pitch_RteAccess_Set_SensorFailureState(&Pitch_ePitchSensorFailure);
}

//-----------------------------------------------------------------------------
/// \brief Pitch_FailureCheckPlausibility
///
/// \descr This function is checking the sensor plausibility state when Adl phase
///        is read as Failure and is setting the Sensor Failure state for CtrlStp
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Pitch_FailureCheckPlausibility(void)
{
  static tsPitch_VehNetState sVehNetState_Old = { 0 };
         tsPitch_VehNetState sVehNetState_New = { 0 };

  static tePitch_PlauSigState boVehSpeedState;
  static tePitch_PlauSigState boBhsValueState;
  static tePitch_PlauSigState boDispValueState;

  Pitch_RteAccess_Get_VehNetState(&sVehNetState_New);  // Read ETAT_PRINCIP_SEV 

   // Transition on ignition key to Stop
  if (((sVehNetState_Old.eVESMainState != VESState_Stop) && (sVehNetState_New.eVESMainState == VESState_Stop)) && (Pitch_ePitchSensorFailure == eHLS_FROZEN_FAILURE))
  {
    Pitch_ePitchSensorFailure = eHLS_STORED_FAILURE;
  }

  // Store previous ignition key value
  sVehNetState_Old = sVehNetState_New;

  if ((Pitch_ePitchSensorFailure == eHLS_STORED_FAILURE) || (Pitch_ePitchSensorFailure == eHLS_FROZEN_FAILURE))
  {
    // Diagnosis status of levelling function shall be set to true value (LEVELLING_ADJUST_FAULT=True)

    // Check vehicle speed data
    boVehSpeedState = Pitch_CheckVehSpeedData();

    if (boVehSpeedState == ePlauSig_Pass)
    {
      // Check Bhs measured sample
      Pitch_CheckSensMounting();
      Pitch_CheckSensMountingState();

      if (NvmBlockDeltaPwmPara.ucSensPlausError[0u] == (uint8)ePlaus_NO_FAILURE && 
          NvmBlockDeltaPwmPara.ucSensPlausError[1u] == (uint8)ePlaus_NO_FAILURE)
      {
        Pitch_ePitchSensorFailure = eHLS_NO_FAILURE;
      }
    }
  }
  else if (Pitch_ePitchSensorFailure == eHLS_SENSOR_FAILURE)
  {
    boDispValueState = Pitch_CheckSensValue();
    Pitch_ePitchSensorFailure = (boDispValueState == ePlauSig_Pass) ? eHLS_NO_FAILURE : eHLS_SENSOR_FAILURE;
  }
  else
  {
    // do nothing
  }

  // Write Sensor Failure for CtrlStp
  Pitch_RteAccess_Set_SensorFailureState(&Pitch_ePitchSensorFailure);
}


//-----------------------------------------------------------------------------
/// \brief Checking the Pitch_CheckVehSpeedData state
///
/// \descr This function is checking vehicle speed and signal quality
///        Returns TRUE if data is OK and FALSE if data is NOK
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL tePitch_PlauSigState Pitch_CheckVehSpeedData(void)
{
  tsPitch_VehicleSpeed sSpeedData = { 0 };
  tePitch_PlauSigState boVehSpeedState = ePlauSig_SNA;

  // Read Vehicle Speed Data
  Pitch_RteAccess_Get_VehicleSpeed(&sSpeedData);

  if ((sSpeedData.eVehicleSpeed.unVehicleSpeed > Cod_Pitch_SensPlausVehSpeed()) && (sSpeedData.eSigQty == SIG_VALID))
  {
    boVehSpeedState = ePlauSig_Pass;
  }
  else
  {
    boVehSpeedState = ePlauSig_Fail;
  }

  return boVehSpeedState;
}


//-----------------------------------------------------------------------------
/// \brief Pitch_CheckSensValue
///
/// \descr This function is checking Sensor data 
///        Returns FALSE if Sensor data is not valid for more than SENSOR_OUTRANGE_TIME
///        Returns TRUE if Sensor data is valid for more than SENSOR_FAILURE_RECOVERY_TIME
///
/// \param  void
///
/// \return boolean
//-----------------------------------------------------------------------------
STATIC_AL tePitch_PlauSigState Pitch_CheckSensValue(void)
{
#define PITCH_DEF_TIMER_INIT_VAL { FALSE, FALSE }

  STATIC_UT(boolean, boDispValCheck[CFG_CntSens], PITCH_DEF_TIMER_INIT_VAL);

  uint16               aucSensRaw[CFG_CntSens] = { 0u };
  uint16               ucSensMin               = Cod_Pitch_SensMin();
  uint16               ucSensMax               = Cod_Pitch_SensMax();
  tePitch_PlauSigState boPitchDispValState     = ePlauSig_SNA;

  // Read RAW value from sensors
  Pitch_RteAccess_Get_GetSens_Raw(&aucSensRaw[0]);

  if ( (aucSensRaw[PITCH_FR_SENSOR] < ucSensMin) || (aucSensRaw[PITCH_FR_SENSOR] > ucSensMax)
    || (aucSensRaw[PITCH_RR_SENSOR] < ucSensMin) || (aucSensRaw[PITCH_RR_SENSOR] > ucSensMax)
    || (NvmBlockDeltaPwmPara.ucSensGndError[PITCH_FR_SENSOR] != 0u) || (NvmBlockDeltaPwmPara.ucSensGndError[PITCH_RR_SENSOR] != 0u)
    || (NvmBlockDeltaPwmPara.ucSensVbatError[PITCH_FR_SENSOR] != 0u) || (NvmBlockDeltaPwmPara.ucSensVbatError[PITCH_FR_SENSOR] != 0u))
  {
    if (boDispValCheck[eErrorTrigger] == FALSE)
    {
      // Start timer
      Pitch_ulCheckBHS_us = TimerGetTick();
      // Invalidate flag so that we do not restart the timer
      boDispValCheck[eErrorTrigger] = TRUE;
    }
    else if (TimerGetTimeSince(Pitch_ulCheckBHS_us) > UTILTIME_MSEC(Cod_Pitch_SensOutrangeTime()))
    {
      boPitchDispValState = ePlauSig_Fail;
      boDispValCheck[eClearErrTrigger] = FALSE;
    }
    else
    {
      // do nothing
    }
  }
  else
  {
    if (boDispValCheck[eClearErrTrigger] == FALSE)
    {
      // Start timer
      Pitch_ulCheckBHS_us = TimerGetTick();
      // Invalidate flag so that we do not restart the timer
      boDispValCheck[eClearErrTrigger] = TRUE;
    }
    else if (TimerGetTimeSince(Pitch_ulCheckBHS_us) > UTILTIME_MSEC(Cod_Pitch_SensFailRecoverTime()))
    {
      boPitchDispValState = ePlauSig_Pass;
      boDispValCheck[eErrorTrigger] = FALSE;
    }
    else
    {
      // do nothing
    }
  }

  return boPitchDispValState;
}


//-----------------------------------------------------------------------------
/// \brief Pitch_CheckSensMountingInit
///
/// \descr This function is initializing global variables used for detection of 
///        plausibility errors on leveling sensors
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void Pitch_CheckSensMountingInit(void)
{
  uint16 ulIx;
  tsDisplacement  sDisp = { 0 };

  Pitch_GetLocal_DisplacementSens(&sDisp); // Read values of Displacement calculated by Pitch Module
  for (ulIx = 0; ulIx < CFG_CntSens; ulIx++)
  {
    Sens_Disp[ulIx] = sDisp.nDisp[ulIx];
  }

  Pitch_nSensFrontRInit = Sens_Disp[PITCH_FR_SENSOR];
  Pitch_nSensRearRInit = Sens_Disp[PITCH_RR_SENSOR];

  Pitch_nSensFrontRFilterErr = (sint16)(SensorPlausData.ucErrFilterThreshold);
  Pitch_nSensRearRFilterErr = (sint16)(SensorPlausData.ucErrFilterThreshold);

  Pitch_nSensFrontRFilterPreErr = Pitch_nSensFrontRFilterErr;
  Pitch_nSensRearRFilterPreErr = Pitch_nSensRearRFilterErr;

  Order1FilterInitPwmSens(&Pitch_DT1SensFrontRMounting, Pitch_nSensFrontRInit);
  Order1FilterInitPwmSens(&Pitch_PT1SensFrontRMountingPreOk, 0);
  Order1FilterInitPwmSens(&Pitch_PT1SensFrontRMountingPreErr, 0);
  Order1FilterInitPwmSens(&Pitch_PT1SensFrontRMountingOk, 0);
  Order1FilterInitPwmSens(&Pitch_PT1SensFrontRMountingErr, Pitch_nSensFrontRFilterErr);

  Order1FilterInitPwmSens(&Pitch_DT1SensRearRMounting, Pitch_nSensRearRInit);
  Order1FilterInitPwmSens(&Pitch_PT1SensRearRMountingPreOk, 0);
  Order1FilterInitPwmSens(&Pitch_PT1SensRearRMountingPreErr, 0);
  Order1FilterInitPwmSens(&Pitch_PT1SensRearRMountingOk, 0);
  Order1FilterInitPwmSens(&Pitch_PT1SensRearRMountingErr, Pitch_nSensRearRFilterErr);

  Pitch_biSensFrontRMountingStateOk = 0;
  Pitch_biSensFrontRMountingStateErr = 0;
  Pitch_biSensRearRMountingStateOk = 0;
  Pitch_biSensRearRMountingStateErr = 0;

}


//-----------------------------------------------------------------------------
/// \brief Pitch_CheckSensMounting
///
/// \descr This function is checking the plausibility of the rear and front
///        leveling sensors and raises flags in case of errors
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pitch_CheckSensMounting(void)
{
  tsDisplacement       sDisp = { 0 };
  tieLITSigQty         ucVccxState, SensFrontRStateNew, SensRearRStateNew;
  tsPitch_VehicleSpeed sSpeedData = { 0 };
  boolean              boVehicleMoving = FALSE;
  tucPitchSigQty       ucVccxSigQty;

  Pitch_GetLocal_DisplacementSens(&sDisp); // Read values of Displacement calculated by Pitch Module
  for (uint16 ulIx = 0; ulIx < CFG_CntSens; ulIx++)
  {
    Sens_Disp[ulIx] = sDisp.nDisp[ulIx];
  }

  // Read Vehicle Speed Data
  Pitch_RteAccess_Get_VehicleSpeed(&sSpeedData);
  if ((sSpeedData.eSigQty == SIG_VALID) && (sSpeedData.eVehicleSpeed.unVehicleSpeed > VEHICLE_THRESHOLD_MOVING_SPEED_SCALED))
  {
    boVehicleMoving = TRUE;
  }
  else
  {
    boVehicleMoving = FALSE;
  }

  // check if supply voltage to sensor is OK
  ucVccxSigQty = Pitch_CheckSensSupply();

  if (ucVccxSigQty != SIG_VALID)
  {
    ucVccxState = LIT_SigErrUnFix;
  }
  else
  {
    ucVccxState = LIT_SigOk;
  }
  //TBD :check sensor state 
  if (ucVccxState == LIT_SigOk)
  {

    SensFrontRStateNew = LIT_SigOk;
    SensRearRStateNew = LIT_SigOk;
  }
  else
  {

    SensFrontRStateNew = LIT_SigErrUnFix;
    SensRearRStateNew = LIT_SigErrUnFix;

  }

  //#if( CFG_OPT_PITCH & CFG_Pitch_CheckSensorMounting)
  if ((SensorPlausData.ucOkFilterThreshold != 0u)
    || (SensorPlausData.ucErrFilterThreshold != 0u))
  {
    static sint16 nDownsampling = 1;

    if (--nDownsampling <= 0)
    {
      nDownsampling = 100;  // sampling time: 2s
    }

    // -----------------------------------------------------------------------------
    // check if SensRearRight-Mounting is Ok

    if (SensRearRStateNew == LIT_SigOk)
    {
      sint16 nSensRearRNew;

      nSensRearRNew = Sens_Disp[PITCH_RR_SENSOR];


      // high-pass filtering of sensor signal (T=1s)
      Order1FilterPwmSens(&Pitch_DT1SensRearRMounting, nSensRearRNew, PITCH_TAU_Abtast_60x);
      nSensRearRNew = nSensRearRNew - Order1FilterValuePwmSens(&Pitch_DT1SensRearRMounting);

      if (((nSensRearRNew - Pitch_nSensRearRHyst) > 2) || ((nSensRearRNew - Pitch_nSensRearRHyst) < 2))
      {
        Pitch_nSensRearRHyst = (sint16)UTIL_ABS(nSensRearRNew);
      }

      // prepare signal for evaluation-downsampling of OkFilter
      // tbd: avoid overflow !!!
      Order1FilterPwmSens(&Pitch_PT1SensRearRMountingPreOk, Pitch_nSensRearRHyst, PITCH_TAU_Abtast_130x);
      Pitch_nSensRearRFilterPreOk = Order1FilterValuePwmSens(&Pitch_PT1SensRearRMountingPreOk);

      // prepare signal for evaluation-downsampling
      // tbd: avoid overflow !!!
      /*  PRQA S 4443 2 */ /*implicit type conversion unsigned char to short is accetable for this particular case*/
      RateLimiterPwmSens(&Pitch_nSensRearRGrad, SensorPlausData.ucRateUp,
        SensorPlausData.ucRateDown, Pitch_nSensRearRHyst);
      //RateLimiterPwmSens(&IoHwAb_nSensRear0Grad, 6400, 1, (IoHwAb_nSensRear0Hyst*64) + 32);

      if (Pitch_nSensRearRGrad > Pitch_nSensRearRFilterPreErr)
      {
        Order1FilterPwmSens(&Pitch_PT1SensRearRMountingPreErr, Pitch_nSensRearRGrad, SensorPlausData.ucPreFilterUpCoeff);
        Pitch_nSensRearRFilterPreErr = Order1FilterValuePwmSens(&Pitch_PT1SensRearRMountingPreErr);
      }
      else
      {
        /* PRQA S 3747 1 */ /* implicit conversion from unsigned short to short is accetable for this particular case */
        Order1FilterPwmSens(&Pitch_PT1SensRearRMountingPreErr, Pitch_nSensRearRGrad, SensorPlausData.ucPreFilterDownCoeff);
        Pitch_nSensRearRFilterPreErr = Order1FilterValuePwmSens(&Pitch_PT1SensRearRMountingPreErr);
      }
#ifndef UNIT_TEST
      // evaluate signal (ok decision)
      if (nDownsampling % 10 == 0)    // sampling time: 0.2 sec
      {
        if (Pitch_nSensRearRFilterPreOk > Pitch_nSensRearRFilterOk)
        {
          /* PRQA S 4446 1 */ /* implicit conversion from unsigned short to short is accetable for this particular case */
          Order1FilterPwmSens(&Pitch_PT1SensRearRMountingOk, (uint16)Pitch_nSensRearRFilterPreOk, SensorPlausData.ucOkFilterUpCoeff);
          Pitch_nSensRearRFilterOk = Order1FilterValuePwmSens(&Pitch_PT1SensRearRMountingOk);
        }
        else
        {
          /* PRQA S 4446 1 */ /* implicit conversion from unsigned short to short is accetable for this particular case */
          Order1FilterPwmSens(&Pitch_PT1SensRearRMountingOk, (uint16)Pitch_nSensRearRFilterPreOk, SensorPlausData.ucOkFilterDownCoeff);
          Pitch_nSensRearRFilterOk = Order1FilterValuePwmSens(&Pitch_PT1SensRearRMountingOk);
        }

        if (Pitch_nSensRearRFilterOk > (sint16)SensorPlausData.ucErrFilterThreshold)
        {
          //To be romoved once related DTC is implemented
          Pitch_biSensRearRMountingStateOk = 1;     // RearRight sensor mounting is OK 
        }
        else
        {
          Pitch_biSensRearRMountingStateOk = 0;   // RearRight sensor mounting is NOT OK

        }
      }
#endif
      // else: keep value of Pitch_biSensRearRMountingStateOk
    }
    else
    {
      Pitch_biSensRearRMountingStateOk = 0;
    }

    // -----------------------------------------------------------------------------
    if (SensFrontRStateNew == LIT_SigOk)
    {
      sint16 nSensFrontRNew;

      nSensFrontRNew = Sens_Disp[PITCH_FR_SENSOR];


      // high-pass filtering of sensor signal (T=1s)
      Order1FilterPwmSens(&Pitch_DT1SensFrontRMounting, nSensFrontRNew, PITCH_TAU_Abtast_60x);
      nSensFrontRNew = nSensFrontRNew - Order1FilterValuePwmSens(&Pitch_DT1SensFrontRMounting);

      if (((nSensFrontRNew - Pitch_nSensFrontRHyst) > 2) || ((nSensFrontRNew - Pitch_nSensFrontRHyst) < 2))
      {
        Pitch_nSensFrontRHyst = (sint16)UTIL_ABS(nSensFrontRNew);
      }

      // prepare signal for evaluation-downsampling of OkFilter
      // tbd: avoid overflow !!!
      Order1FilterPwmSens(&Pitch_PT1SensFrontRMountingPreOk, Pitch_nSensFrontRHyst, PITCH_TAU_Abtast_130x);
      Pitch_nSensFrontRFilterPreOk = Order1FilterValuePwmSens(&Pitch_PT1SensFrontRMountingPreOk);

      // prepare signal for evaluation-downsampling of ErrFilter
      // tbd: avoid overflow !!!
      /* PRQA S 4443 2 */ /* implicit conversion from unsigned char to short is acceptable for this particular case */
      RateLimiterPwmSens(&Pitch_nSensFrontRGrad, SensorPlausData.ucRateUp,
        SensorPlausData.ucRateDown, Pitch_nSensFrontRHyst);

      if (Pitch_nSensFrontRGrad > Pitch_nSensFrontRFilterPreErr)
      {
        Order1FilterPwmSens(&Pitch_PT1SensFrontRMountingPreErr, Pitch_nSensFrontRGrad, SensorPlausData.ucPreFilterUpCoeff);
        Pitch_nSensFrontRFilterPreErr = Order1FilterValuePwmSens(&Pitch_PT1SensFrontRMountingPreErr);
      }
      else
      {
        Order1FilterPwmSens(&Pitch_PT1SensFrontRMountingPreErr, Pitch_nSensFrontRGrad, SensorPlausData.ucPreFilterDownCoeff);
        Pitch_nSensFrontRFilterPreErr = Order1FilterValuePwmSens(&Pitch_PT1SensFrontRMountingPreErr);
      }
#ifndef UNIT_TEST
      // evaluate signal (ok decision)
      if (nDownsampling % 10 == 0)    // sampling time: 0.2 sec
      {
        if (Pitch_nSensFrontRFilterPreOk > Pitch_nSensFrontRFilterOk)
        {
          /* PRQA S 4446 1 */ /* implicit conversion from unsigned short to short is acceptable for this particular case */
          Order1FilterPwmSens(&Pitch_PT1SensFrontRMountingOk, (uint16)Pitch_nSensFrontRFilterPreOk, SensorPlausData.ucOkFilterUpCoeff);
          Pitch_nSensFrontRFilterOk = Order1FilterValuePwmSens(&Pitch_PT1SensFrontRMountingOk);
        }
        else
        {
          /* PRQA S 4446 1 */ /* implicit conversion from unsigned short to short is accetable for this particular case */
          Order1FilterPwmSens(&Pitch_PT1SensFrontRMountingOk, (uint16)Pitch_nSensFrontRFilterPreOk, SensorPlausData.ucOkFilterDownCoeff);
          Pitch_nSensFrontRFilterOk = Order1FilterValuePwmSens(&Pitch_PT1SensFrontRMountingOk);
        }

        if (Pitch_nSensFrontRFilterOk > (sint16)SensorPlausData.ucOkFilterThreshold)
        {
          //To be romoved once related DTC is implemented
          Pitch_biSensFrontRMountingStateOk = 1;     // FrontRight sensor mounting is OK 
        }
        else
        {
          Pitch_biSensFrontRMountingStateOk = 0;    // FrontRight sensor mounting is NOT OK
        }
      }
      // else: keep value of Pitch_biSensFrontRMountingStateOk
#endif
    }
    else
    {
      Pitch_biSensFrontRMountingStateOk = 0;
    }

#ifndef UNIT_TEST
    // -----------------------------------------------------------------------------
        // Err-Check
    if (nDownsampling == 100) // sampling time: 2 sec
    {
      // get environmental conditions

      // -----------------------------------------------------------------------------
      // check if SensRearRight-Mounting is Err
      // evaluate signal (err decision, only if other sensors are ok,
      // own electrical state is ok and vehicle is moving)
      if ((SensRearRStateNew == LIT_SigOk) && (Pitch_biSensFrontRMountingStateOk != 0u) && (boVehicleMoving == TRUE))
      {
        if (Pitch_nSensRearRFilterPreErr > Pitch_nSensRearRFilterErr)
        {
          Order1FilterInitPwmSens(&Pitch_PT1SensRearRMountingErr, Pitch_nSensRearRFilterPreErr);
          Pitch_nSensRearRFilterErr = Pitch_nSensRearRFilterPreErr;
          // Limit the filtered value
          Pitch_nSensRearRFilterErr = min(Pitch_nSensRearRFilterErr, PITCH_Max_Filtered_Val);
        }
        else
        {
          Order1FilterPwmSens(&Pitch_PT1SensRearRMountingErr, (sint16)Pitch_nSensRearRFilterPreErr,
            SensorPlausData.ucErrFilterDownCoeff);

          Pitch_nSensRearRFilterErr = Order1FilterValuePwmSens(&Pitch_PT1SensRearRMountingErr);
          // Limit the filtered value
          Pitch_nSensRearRFilterErr = min(Pitch_nSensRearRFilterErr, PITCH_Max_Filtered_Val);
        }

        if (Pitch_nSensRearRFilterErr < (sint16)PITCH_PLAUS_ERR_THRESHOLD)

        {
          Pitch_biSensRearRMountingStateErr = 1;      // mounting Error on Rear sensor
        }
        else
        {
          Pitch_biSensRearRMountingStateErr = 0;      // Rear mounting is OK
        }
      }
      else
      {
        Pitch_biSensRearRMountingStateErr = 0;        // Rear mounting is OK

        if (Pitch_nSensRearRFilterPreErr > Pitch_nSensRearRFilterErr)
        {
          Order1FilterInitPwmSens(&Pitch_PT1SensRearRMountingErr, Pitch_nSensRearRFilterPreErr);
          Pitch_nSensRearRFilterErr = Pitch_nSensRearRFilterPreErr;
          // Limit the filtered value
          Pitch_nSensRearRFilterErr = min(Pitch_nSensRearRFilterErr, PITCH_Max_Filtered_Val);
        }
      }

      // -----------------------------------------------------------------------------
      // check if SensFrontRight-Mounting is Err
      // evaluate signal (err decision, only if other sensors are ok,
      // own electrical state is ok and vehicle is moving)
      if ((SensFrontRStateNew == LIT_SigOk) && (Pitch_biSensRearRMountingStateOk != 0u) && (boVehicleMoving == TRUE))
      {
        if (Pitch_nSensFrontRFilterPreErr > Pitch_nSensFrontRFilterErr)
        {
          Order1FilterInitPwmSens(&Pitch_PT1SensFrontRMountingErr, Pitch_nSensFrontRFilterPreErr);
          Pitch_nSensFrontRFilterErr = Pitch_nSensFrontRFilterPreErr;
          // Limit the filtered value
          Pitch_nSensFrontRFilterErr = min(Pitch_nSensFrontRFilterErr, PITCH_Max_Filtered_Val);
        }
        else
        {
          Order1FilterPwmSens(&Pitch_PT1SensFrontRMountingErr,
            (sint16)Pitch_nSensFrontRFilterPreErr, SensorPlausData.ucErrFilterDownCoeff);
          Pitch_nSensFrontRFilterErr = Order1FilterValuePwmSens(&Pitch_PT1SensFrontRMountingErr);
          // Limit the filtered value
          Pitch_nSensFrontRFilterErr = min(Pitch_nSensFrontRFilterErr, PITCH_Max_Filtered_Val);
        }

        if (Pitch_nSensFrontRFilterErr < (sint16)PITCH_PLAUS_ERR_THRESHOLD)
        {
          Pitch_biSensFrontRMountingStateErr = 1;      // mounting Error on FrontRight sensor
        }
        else
        {
          Pitch_biSensFrontRMountingStateErr = 0;      // FrontRight sensor mounting is OK
        }
      }
      else
      {
        Pitch_biSensFrontRMountingStateErr = 0;        // FrontRight sensor mounting is OK


        if (Pitch_nSensFrontRFilterPreErr > Pitch_nSensFrontRFilterErr)
        {
          Order1FilterInitPwmSens(&Pitch_PT1SensFrontRMountingErr, Pitch_nSensFrontRFilterPreErr);
          Pitch_nSensFrontRFilterErr = Pitch_nSensFrontRFilterPreErr;
          // Limit the filtered value
          Pitch_nSensFrontRFilterErr = min(Pitch_nSensFrontRFilterErr, PITCH_Max_Filtered_Val);
        }
      }

    }
#endif
  }

  Pitch_SetNvmFlag();
  //#endif //(CFG_OPT_PITCH & CFG_Pitch_CheckSensorMounting)
}/* PRQA S 5310, 5316, 5324, 5330 1 */ /* HIS METRICS violation, function will need refactoring */


//-----------------------------------------------------------------------------
/// \brief Pitch_CheckSensMountingState
///
/// \descr This function is setting plausibility DTCs depending on error flags
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pitch_CheckSensMountingState(void)
{
  if ((Pitch_biSensFrontRMountingStateErr == 1u) || (NvmBlockDeltaPwmPara.ucSensPlausError[1u] == TRUE))
  {
    Rte_Call_DemPrj_ReportErrorStatus((uint16)FR_BHS_PLAUS_FAIL, DEM_EVENT_STATUS_FAILED);
  }
  else if (Pitch_biSensFrontRMountingStateOk == 1u)
  {
    Rte_Call_DemPrj_ReportErrorStatus((uint16)FR_BHS_PLAUS_FAIL, DEM_EVENT_STATUS_PASSED);
  }
  else
  {
    // do nothing
  }

  if ((Pitch_biSensRearRMountingStateErr == 1u) || (NvmBlockDeltaPwmPara.ucSensPlausError[0u] == TRUE))
  {
    Rte_Call_DemPrj_ReportErrorStatus((uint16)RR_BHS_PLAUS_FAIL, DEM_EVENT_STATUS_FAILED);
  }
  else if (Pitch_biSensRearRMountingStateOk == 1u)
  {
    Rte_Call_DemPrj_ReportErrorStatus((uint16)RR_BHS_PLAUS_FAIL, DEM_EVENT_STATUS_PASSED);
  }
  else
  {
    // do nothing
  }
}

//-----------------------------------------------------------------------------
/// \brief Pitch_SetNvmFlag
///
/// \descr This function is writing the plausibility flag for each sensor inside
///        the NVM block, the writting starts only after 5 seconds so the 
///        sensor ok flag have time to be detected
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Pitch_SetNvmFlag(void)
{
  STATIC_UT(boolean, boSensPlauCheck, TRUE); // Check if 5000 ms have passed

  STATIC_AL tePitchPlausState eSensPlausNew[CFG_CntSens];

  if (boSensPlauCheck != FALSE)
  {
    // Start timer
    Pitch_SensPlau_CheckSensState_us = TimerGetTick();
    // Invalidate flag so that we do not restart the timer
    boSensPlauCheck = FALSE;
  }
  else if (TimerGetTimeSince(Pitch_SensPlau_CheckSensState_us) > UTILTIME_MSEC(PITCH_PLAUS_HEALTIME_AFTER_RESET))
  {
    // Check front sensor mounting state
    if ((Pitch_biSensFrontRMountingStateErr == 1u) && (Pitch_biSensFrontRMountingStateOk == 0u))
    {
      eSensPlausNew[1u] = ePlaus_FAILURE;
    }
    else if ((Pitch_biSensFrontRMountingStateErr == 0u) && (Pitch_biSensFrontRMountingStateOk == 1u))
    {
      eSensPlausNew[1u] = ePlaus_NO_FAILURE;
    }
    else
    {
      eSensPlausNew[1u] = ePlaus_NO_DATA;
    }

    // Check rear sensor mounting state
    if ((Pitch_biSensRearRMountingStateErr == 1u) && (Pitch_biSensRearRMountingStateOk == 0u))
    {
      eSensPlausNew[0u] = ePlaus_FAILURE;
    }
    else if ((Pitch_biSensRearRMountingStateErr == 0u) && (Pitch_biSensRearRMountingStateOk == 1u))
    {
      eSensPlausNew[0u] = ePlaus_NO_FAILURE;
    }
    else
    {
      eSensPlausNew[0u] = ePlaus_NO_DATA;
    }

    // Check if error state has changed
    if (((NvmBlockDeltaPwmPara.ucSensPlausError[0u] != (uint8)eSensPlausNew[0u]) && (eSensPlausNew[0u] != ePlaus_NO_DATA)) ||
      ((NvmBlockDeltaPwmPara.ucSensPlausError[1u] != (uint8)eSensPlausNew[1u]) && (eSensPlausNew[1u] != ePlaus_NO_DATA)))
    {
      // Write new values
      NvmBlockDeltaPwmPara.ucSensPlausError[0u] = (uint8)eSensPlausNew[0u];
      NvmBlockDeltaPwmPara.ucSensPlausError[1u] = (uint8)eSensPlausNew[1u];

      (void)NvM_WriteBlock((NvM_BlockIdType)NvmBlockDeltaPwmParaId, (void*)&NvmBlockDeltaPwmPara);
    }
    else
    {
      // do nothing
    }

  }
  else
  {
    // do nothing
  }
}


//-----------------------------------------------------------------------------
/// \brief RateLimiterPwmSens
///
/// \descr RateLimiterPwmSens
///
/// \param  pRateLimiter
/// \param  RateUp
/// \param  RateDown
/// \param  Value
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void RateLimiterPwmSens(sint16* pRateLimiter, sint16 RateUp, sint16 RateDown, sint16 Value)
{
  if (Value > *pRateLimiter + RateUp)
  {
    *pRateLimiter += RateUp;
  }
  else if (Value < *pRateLimiter - RateDown)
  {
    *pRateLimiter -= RateDown;
  }
  else
  {
    *pRateLimiter = Value;
  }
}

//-----------------------------------------------------------------------------
/// \brief Pitch_GetSensorError
///
/// \descr
///
/// \param  -
///
/// \return tePitchSensorState
//-----------------------------------------------------------------------------
tePitchSensorState Pitch_GetSensorError(void)
{
  return Pitch_ePitchSensorFailure;
}

//-----------------------------------------------------------------------------
/// \brief Order1FilterPwmSens
///
/// \descr Order1FilterPwmSens
///
/// \param  pFilter
/// \param  nValue
/// \param  unBeta
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Order1FilterPwmSens(ORDER1_Filter* const pFilter, const sint16 nValue, const uint16 unBeta)
{
  //lint -e702 LINT Info: Shift right of signed quantity (long)
  /* PRQA S 1860, 4533, 4544, 4394 1 */ /* Compiler can do right shift */
  *pFilter = ASHR((*pFilter * (sint16)unBeta + 64), 7) + (sint16)((128 - unBeta) * 4) * (sint32)nValue;
  //lint +e702 LINT Info: Shift right of signed quantity (long)
}


//-----------------------------------------------------------------------------
/// \brief Order1FilterInitPwmSens
///
/// \descr Order1FilterInitPwmSens
///
/// \param  pFilter
/// \param  nValue
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void Order1FilterInitPwmSens(ORDER1_Filter* const pFilter, const sint16 nValue)
{
  //lint -e702 LINT Info: Shift right of signed quantity (long)
  /* PRQA S 502 1 */ /* Compiler can do right shift */
  *pFilter = (sint32)nValue * 512;
  //lint +e702 LINT Info: Shift right of signed quantity (long)
}


//-----------------------------------------------------------------------------
/// \brief Order1FilterValuePwmSens
///
/// \descr Order1FilterValuePwmSens
///
/// \param  pFilter
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL sint16 Order1FilterValuePwmSens(const ORDER1_Filter* const pFilter)
{
  /*PRQA S 4533, 4544 1 */ /* Compiler can do right shift */
  return (sint16)ASHR((*pFilter + 256), 9);
}
