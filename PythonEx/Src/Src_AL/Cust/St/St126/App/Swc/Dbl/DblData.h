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
/// \file   DblData.h
///
/// \brief  header file for coding functions
///
/// \descr  functions described
///
///
/// \author Futo Henrietta-Helena F31185D
///         mail to <henrietta-helena.futo[at]magnetimarelli.com>
//-----------------------------------------------------------------------------
#ifndef DBL_DATA_2021_11_02_H_
#define DBL_DATA_2021_11_02_H_

//=============================================================================
// includes
//=============================================================================
#include <Cfg/Cfg.h>
#include <Std_Types.h>
#include <AL_Helper.h>
#include <Swc/CodM/CodM_Para.h>
#include <RteCommonTypes.h>
#include "Dbl_Types.h"

//=============================================================================
// externals
//=============================================================================

extern  tsRteCodingParameters Dbl_sCodingParam;
extern  tsDbl_VehPathCurvatureData Dbl_sCurvatureData;


//=============================================================================
// defines
//=============================================================================

#define DBL_NEGATIVE_FACTOR                                  -1
// limit curvature for 0.000025 step
#define DBL_POSITIVE_CURVATURE_LIMIT                          25000
#define DBL_NEGATIVE_CURVATURE_LIMIT                         -25000

#define DBL_POSITIVE_RAW_CURVATURE_LIMIT                      30000
#define DBL_NEGATIVE_RAW_CURVATURE_LIMIT                     -30000

#define DBL_CURVE_OUTSIDE_HL_FACTOR_ADAPTION(x)               (((x) * 4) / 10) // factor applied on curvature
#define DBL_CURVATURE_INVALID_VALUE                           0x7FFF // this value is used for invalid value of steering wheel angle and curvature
#define DBL_STEERING_WHEEL_INIT_IN_PROGRESS_VALUE             -28673 // this value is used for init in progress value of steering wheel


//****************************************************************************
// gloabl variables
//****************************************************************************

//#################### AfsPolySolver2 ###########################################
STATIC_AL INLINE sint16   CodAFSPolySolver2_C1(const uint8 side) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2.Parameter[side].snC1; }
STATIC_AL INLINE sint16   CodAFSPolySolver2_C2(const uint8 side) { return  Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2.Parameter[side].snC2; }
STATIC_AL INLINE uint8    CodAFSPolySolver2_Slope1(const uint8 side) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2.Parameter[side].ucS1; }
STATIC_AL INLINE uint8    CodAFSPolySolver2_Slope2(const uint8 side) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2.Parameter[side].ucS2; }
STATIC_AL INLINE uint8    CodAFSPolySolver2_EndSlope1(const uint8 side) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2.Parameter[side].ucE1; }
STATIC_AL INLINE uint8    CodAFSPolySolver2_EndSlope2(const uint8 side) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2.Parameter[side].ucE2; }
STATIC_AL INLINE uint8    CodAFSPolySolver2_SlopeDenG(const uint8 side) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2.Parameter[side].ucDG; }

STATIC_AL INLINE uint8    CodAFSPolySolver2_SlopeDenC(const uint8 side) { return /*Dbl_sCodingParam->Dbl.AFSPolySolver2.Parameter[side].ucSlopeDenC;*/ 1; }

STATIC_AL INLINE uint8    CodAFSPolySolver2_V0(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2.ucV0; }
STATIC_AL INLINE uint8    CodAFSPolySolver2_V1(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2.ucV1; }
STATIC_AL INLINE uint8    CodAFSPolySolver2_V2(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2.ucV2; }
STATIC_AL INLINE uint8    CodAFSPolySolver2_V3(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2.ucV3; }
STATIC_AL INLINE uint8    CodAFSPolySolver2_V4(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2.ucV4; }
STATIC_AL INLINE uint8    CodAFSPolySolver2_Angle(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2.ucHeadLightAngle; }
STATIC_AL INLINE uint16   CodEgo_Vehicle_Motion_Confirmation_Time(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2.EGO_VEHICLE_MOTION_CONFIRMATION_TIME; }
STATIC_AL INLINE uint8    CodConstSpeed(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2.DBL_CONSTANT_SPEED_THRESHOLD_UPPER; }
STATIC_AL INLINE uint8    CodDblCurveFactor(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.DblAngleLimitations.ucDBL_CURVE_OUTSIDE_HL_FACTOR_ADAPTION; /*10*/ }
STATIC_AL INLINE uint8    CodDblHbAngleMax(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.DblAngleLimitations.ucHBS_HB_SWIVELING_ANGLE_MAX; /*50*/ }
STATIC_AL INLINE uint8    CodDblDiversityParam(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.DblDiversity.ucTYPE_ECL_VIR_DYN; }

//###############################################################################

//###################### AfsPolySolver2Add ######################################
STATIC_AL INLINE sint16   CodAFSPolySolver2Add_C1(const uint8 side) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2Add.ParameterSport[side].snC1; }
STATIC_AL INLINE sint16   CodAFSPolySolver2Add_C2(const uint8 side) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2Add.ParameterSport[side].snC2; }
STATIC_AL INLINE uint8    CodAFSPolySolver2Add_Slope1(const uint8 side) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2Add.ParameterSport[side].ucS1; }
STATIC_AL INLINE uint8    CodAFSPolySolver2Add_Slope2(const uint8 side) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2Add.ParameterSport[side].ucS2; }
STATIC_AL INLINE uint8    CodAFSPolySolver2Add_EndSlope1(const uint8 side) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2Add.ParameterSport[side].ucE1; }
STATIC_AL INLINE uint8    CodAFSPolySolver2Add_EndSlope2(const uint8 side) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2Add.ParameterSport[side].ucE2;}
STATIC_AL INLINE uint8    CodAFSPolySolver2Add_SlopeDenG(const uint8 side) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2Add.ParameterSport[side].ucDG; }
STATIC_AL INLINE uint8    CodAFSPolySolver2Add_SlopeDenC(const uint8 side) { return /*Dbl_sCodingParam->Dbl.AFSPolySolver2Add.ParameterSport[side].ucSlopeDenC;*/ 1; }

STATIC_AL INLINE uint8    CodAFSPolySolver2Add_V0(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2Add.ucV0; }
STATIC_AL INLINE uint8    CodAFSPolySolver2Add_V1(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2Add.ucV1; }
STATIC_AL INLINE uint8    CodAFSPolySolver2Add_V2(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2Add.ucV2; }
STATIC_AL INLINE uint8    CodAFSPolySolver2Add_V3(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2Add.ucV3; }
STATIC_AL INLINE uint8    CodAFSPolySolver2Add_V4(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2Add.ucV4; }
STATIC_AL INLINE uint8    CodAFSPolySolver2Add_Angle(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2Add.ucHeadLightAngle; }

//###############################################################################

//############################# DisableFuncs ####################################

LOCAL_INLINE uint8  CodSysConfigurability_Dbl_Enable(void)     { return Dbl_sCodingParam.psCodingParameters_Blocks->Sys.Configurability.ucDbl_Enable; }
LOCAL_INLINE uint8  CodDisableFuncs_Curvature_Mode(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.DisableFuncs.ucCurvatureMode;}

//###############################################################################

//####################### DblCurvatureCalculation ###############################

LOCAL_INLINE uint8  CodDblCurvatureCalculation_Crc_Wf_1                (void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.DblCurvatureCalculation.ucCRC_WF_1; }
LOCAL_INLINE uint8  CodDblCurvatureCalculation_Crc_Wf_2                (void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.DblCurvatureCalculation.ucCRC_WF_2; }
LOCAL_INLINE uint8  CodDblCurvatureCalculation_Crc_Wf_3                (void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.DblCurvatureCalculation.ucCRC_WF_3; }
LOCAL_INLINE uint8  CodDblCurvatureCalculation_Crc_Vehicle_Speed_Wf_1  (void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.DblCurvatureCalculation.ucCRC_VEHICLE_SPEED_WF_1; }
LOCAL_INLINE uint8  CodDblCurvatureCalculation_Crc_Vehicle_Speed_Wf_2  (void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.DblCurvatureCalculation.ucCRC_VEHICLE_SPEED_WF_2; }
LOCAL_INLINE uint8  CodDblCurvatureCalculation_Crc_Vehicle_Speed_Wf_3  (void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.DblCurvatureCalculation.ucCRC_VEHICLE_SPEED_WF_3; }
LOCAL_INLINE uint16 CodDblCurvatureCalculation_Crc_Vehicle_Wheelbase   (void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.DblCurvatureCalculation.unCRC_VEHICLE_WHEELBASE; }
LOCAL_INLINE uint16 CodDblCurvatureCalculation_Crc_Steering_Ratio      (void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.DblCurvatureCalculation.unCRC_STEERING_RATIO; }

LOCAL_INLINE uint8 CodDblCurvatureCalculation_getFilterTimePrio       (void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AfsHld.ucFilterTimePrio; }
LOCAL_INLINE uint8 CodDblCurvatureCalculation_getFilterTracking       (void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AfsHld.ucFilterTracking; }
LOCAL_INLINE uint8 CodDblCurvatureCalculation_getFilterTrackingRange  (void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AfsHld.ucFilterTrackingRange; }


//###############################################################################

STATIC_AL INLINE uint8    CodAFSPolySolver2Angle_RHT_RightCurve(const teDbl_MountingSide eSide)
{
  return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.DblAngleLimitations.ucDBL_LB_ANGLE_LIMITS_RIGHT_RGT[eSide]; /*70*/
}

STATIC_AL INLINE uint8    CodAFSPolySolver2Angle_RHT_BothLeftCurve(void)
{
  sint8 snDBL_LB_ANGLE_LIMIT_LEFT_RHT = Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.DblAngleLimitations.snDBL_LB_ANGLE_LIMIT_LEFT_RHT;
  if (snDBL_LB_ANGLE_LIMIT_LEFT_RHT < 0)
  {
    snDBL_LB_ANGLE_LIMIT_LEFT_RHT = snDBL_LB_ANGLE_LIMIT_LEFT_RHT * DBL_NEGATIVE_FACTOR;
  }
  return snDBL_LB_ANGLE_LIMIT_LEFT_RHT; /*-80*/
}

STATIC_AL INLINE uint8    CodAFSPolySolver2Angle_LHT_LeftCurve(const teDbl_MountingSide eSide)
{
  sint8 ucDbl_AngleLimitations_LEFT_LFT = Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.DblAngleLimitations.snDBL_LB_ANGLE_LIMITS_LEFT_LHT[eSide];

  if (ucDbl_AngleLimitations_LEFT_LFT < 0)
  {
    ucDbl_AngleLimitations_LEFT_LFT = ucDbl_AngleLimitations_LEFT_LFT * DBL_NEGATIVE_FACTOR;
  }
  return ucDbl_AngleLimitations_LEFT_LFT;/*-70 */
}

STATIC_AL INLINE uint8    CodAFSPolySolver2Angle_LHT_BothRightCurve(void)
{
  return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.DblAngleLimitations.ucDBL_LB_ANGLE_LIMIT_RIGHT_LHT;/*80 */
}

//###################### AFSPolySolver2Angle ####################################
STATIC_AL INLINE uint8    CodAFSPolySolver2Angle_S0(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2Angle.S0; }
STATIC_AL INLINE uint8    CodAFSPolySolver2Angle_S1(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2Angle.S1; }
STATIC_AL INLINE uint8    CodAFSPolySolver2Angle_S12(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2Angle.S12; }
//###############################################################################

//###################### AFSHldDev ##############################################
STATIC_AL INLINE uint8    CodAFSHldDev_OperatingMode(void) { return /*Dbl_sCodingParam->Dbl.AFSHldDev.ucOperatingMode; */ 1; }
STATIC_AL INLINE uint8    CodAFSHldDev_SolverType(void) { return /*Dbl_sCodingParam->Dbl.AFSHldDev.ucSolverType;*/ 1; }
STATIC_AL INLINE uint8    CodAFSHldDev_RelationType(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSHldDev.ucRelationType; }
//###############################################################################

//###################### CoursePara1 ############################################
STATIC_AL INLINE sint16   CodCoursePara1_SteeringAngleFactor(void) { return /*Dbl_sCodingParam->Dbl.CoursePara1.unSteeringBoxratio;*/ 173; }
STATIC_AL INLINE uint8    CodCoursePara1_YawRateFactor(void) { return /*Dbl_sCodingParam->Dbl.CoursePara1.unYawRateFactor;*/ 0; }
STATIC_AL INLINE uint8    CodCoursePara1_Traffic(void) { return /*Dbl_sCodingParam->Dbl.CoursePara1.ucTraffic;*/ 1; }
STATIC_AL INLINE uint8    CodCoursePara1_SteeringAnglePreFilter(void) { return /*Dbl_sCodingParam->Dbl.CoursePara1.ucSteeringAnglePreFilter;*/0; }
STATIC_AL INLINE uint8    CodCoursePara1_WheelBaseFactor(void) { return /*Dbl_sCodingParam->Dbl.CoursePara1.unWheelBaseFactor;*/0; }
//###############################################################################

//###################### AfsHld #################################################
STATIC_AL INLINE uint8    CodAfsHld_IdleRange(const uint8 side) { return /*Dbl_sCodingParam->Dbl.AfsHld.ucIdleRange[side];*/ 50; }
STATIC_AL INLINE sint16   CodAfsHld_IdleSwag(void) { return/* Dbl_sCodingParam->Dbl.AfsHld.nIdleSwag;*/ 200; }
STATIC_AL INLINE uint8    CodAfsHld_HlaOutMaxStep(void) { return /*Dbl_sCodingParam->Dbl.AfsHld.ucHlaOutMaxStep;*/ 80; }
STATIC_AL INLINE uint8    CodAfsHld_HlaOutMinStep(void) { return /*Dbl_sCodingParam->Dbl.AfsHld.ucHlaOutMinStep;*/20; }
STATIC_AL INLINE uint8    CodAfsHld_CGCorrection(void) { return /*Dbl_sCodingParam->Dbl.AfsHld.ucCGCorrection;*/ 6; }
STATIC_AL INLINE uint8    CodAfsHld_HlaFilterSize(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AfsHld.ucHlaFilterSize; }
//###############################################################################

//###################### AfsIdle ################################################
STATIC_AL INLINE uint8    CodAfsIdle_IdleRange0(const uint8 side) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AfsIdle.ucIdleRange0[side]; }
STATIC_AL INLINE uint8    CodAfsIdle_IdleRange1(const uint8 side) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AfsIdle.ucIdleRange1[side]; }
STATIC_AL INLINE uint8    CodAfsIdle_IdleV0(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AfsIdle.ucV0_straight_ahead_speed; }
STATIC_AL INLINE uint8    CodAfsIdle_IdleV1(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AfsIdle.ucV1_straight_ahead_speed;}
STATIC_AL INLINE uint8    CodAfsIdle_OnTime(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AfsIdle.ucOnTime; }
STATIC_AL INLINE uint8    CodAfsIdle_OnDelay(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AfsIdle.ucOnDelay; }
STATIC_AL INLINE uint8    CodAfsIdle_OffTime(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AfsIdle.ucOffTime; }
STATIC_AL INLINE uint8    CodAfsIdle_OffDelay(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AfsIdle.ucOffDelay; }
//###############################################################################

//###################### AfsSwiRateLim ##########################################
STATIC_AL INLINE uint8    CodAfsSwiRateLim_LimOutFast(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AfsSwiRateLim.ucLimOutFast; }
STATIC_AL INLINE uint8    CodAfsSwiRateLim_LimInFast(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AfsSwiRateLim.ucLimInFast; }
STATIC_AL INLINE uint8    CodAfsSwiRateLim_LimOutSlow(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AfsSwiRateLim.ucLimOutSlow; }
STATIC_AL INLINE uint8    CodAfsSwiRateLim_LimInSlow(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AfsSwiRateLim.ucLimInSlow; }
STATIC_AL INLINE uint8    CodAfsSwiRateLim_ChangeRateOut(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AfsSwiRateLim.ucChangeRateOut; }
STATIC_AL INLINE uint8    CodAfsSwiRateLim_ChangeRateIn(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AfsSwiRateLim.ucChangeRateIn; }
STATIC_AL INLINE uint8    CodAfsSwiRateLim_ConstCurvature(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AfsSwiRateLim.ucConstCurvature;}
STATIC_AL INLINE sint16   CodAfsSwiRateLim_CGCorrection(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AfsSwiRateLim.ucCGCorrection; }
//###############################################################################

//###################### DriveSituationParams ###################################
STATIC_AL INLINE uint8    CodDriveSit_ConstSpeedThr(void) { return Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.AFSPolySolver2.DBL_CONSTANT_SPEED_THRESHOLD_UPPER; }
STATIC_AL INLINE uint8    CodDriveSit_ConstMaxThr(void) { return  Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.DrivingSituationParam.ucConstMaxThr;}
STATIC_AL INLINE uint8    CodDriveSit_ConstTimeThr(void) { return  Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.DrivingSituationParam.ucConstTimeThr; }
STATIC_AL INLINE uint8    CodDriveSit_SwvlBckAngle(void) { return  Dbl_sCodingParam.psCodingParameters_Blocks->Dbl.DrivingSituationParam.ucSwivelBackAngle; }

//****************************************************************************
// public functions
//****************************************************************************

#endif // DBL_DATA_2021_11_02_H_