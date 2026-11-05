#ifndef __CODM_PARA_DBL_H__
#define __CODM_PARA_DBL_H__

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
///  \file   CodM_Para_Dbl.h
///
///  \brief  Content of datagroup "Dbl"
///
///  \descr  Source: PS60_R2.xlsm. 
///          Version TBD 
///          For further details see coding parameter
///
///  \author This file is auto generated - please do not edit
///
///  \date   25.03.2020, 12:26:30
//-----------------------------------------------------------------------------
//=============================================================================
// Includes
//=============================================================================

//=============================================================================
// Definitions
//=============================================================================

//=============================================================================
// Types
//=============================================================================
#define CODM_PARA_AFSDBL_SIZE 2u
#define CODM_PARA_AFSDBLS_RESERVED_SIZE 3u
typedef struct 
{
  uint8           ucCurvatureMode; // 0: Curvature through CAN, 1: Curvature calculated
  uint8           ucReserviert;
} 
tNvmPara_Dbl_DisableFuncs;

typedef struct 
{
  // Curvature C1, V1
  sint16     snC1;
  // Curvature C2, V2      
  sint16     snC2;
  // start slope  
  uint8      ucS1;       // start slope for C1, V1
  uint8      ucS2;       // start slope for C2, V2
  // end slope  
  uint8      ucE1;    // end slope for C1, V1
  uint8      ucE2;    // end slope for C2, V2
  // start slope correction values 
  uint8      ucDG;    // denominator for curvarure gradient correction, typical values   2-10 
  //   ->problem center passing
  uint8      ucReserviert3;    // denominator for end curvature limitation,      typical values  10-100 
  //   ->problem return cycle
} 
tNvmPara_Dbl_AFSPolySolver2_Parameter;

typedef struct 
{
  tNvmPara_Dbl_AFSPolySolver2_Parameter Parameter[CODM_PARA_AFSDBL_SIZE];   //< 160 Bytes
  uint8      ucV0;                      //< [km/h]     V0    DBL start 
  uint8      ucV1;                      //< [km/h]     V1    DBL reduced dynamic speed, full operation range
  uint8      ucV2;                      //< [km/h]     V2    DBL full dynamic, full operation range
  uint8      ucV3;                      //< [km/h]     V3    DBL starts hight speed attenuation
  uint8      ucV4;                      //< [km/h]     V4    DBL off
  uint8      ucHeadLightAngle; //head light angle
  uint8      DBL_CONSTANT_SPEED_THRESHOLD_UPPER; 
  uint8      reseviert;
  uint16     EGO_VEHICLE_MOTION_CONFIRMATION_TIME;
} 
tNvmPara_Dbl_AFSPolySolver2;

// Additional parameters for Dbl like sport mode curvatures
typedef struct 
{
  tNvmPara_Dbl_AFSPolySolver2_Parameter ParameterSport[CODM_PARA_AFSDBL_SIZE];    //< Swivel definition for sport mode //160 Bytes
  uint8      ucV0;                      //< [km/h]     V0    DBL start 
  uint8      ucV1;                      //< [km/h]     V1    DBL reduced dynamic speed, full operation range
  uint8      ucV2;                      //< [km/h]     V2    DBL full dynamic, full operation range
  uint8      ucV3;                      //< [km/h]     V3    DBL starts hight speed attenuation
  uint8      ucV4;                      //< [km/h]     V4    DBL off
  uint8      ucHeadLightAngle; //head light angle
  uint8      DBL_CONSTANT_SPEED_THRESHOLD_UPPER;
  uint8      reseviert;
  uint16     EGO_VEHICLE_MOTION_CONFIRMATION_TIME;
} 
tNvmPara_Dbl_AFSPolySolver2Add;

// control the calculation of nominal swiveling angle --> output (left, right) swiveling angle
typedef struct
{
  uint8 S0; //Start slope
  uint8 S1; //End slope
  uint8 S12; //Half of end slope
  uint8 reserviert1[3];
}
tNvmPara_Dbl_AFSPolySolver2Angle;

// -----------------------------------------------------------------------------
// AFS HLD/DBL development parameter
// (Dynamic bending light)
// -----------------------------------------------------------------------------
typedef struct
{ 
  uint8      ucRelationType;       // relation type                 
  uint8      ucDummy;              // dummy byte          
}
tNvmPara_Dbl_AFSHldDev; //32 Bytes

typedef struct
{
  uint8     reserviert1[CODM_PARA_AFSDBL_SIZE];
} 
tNvmPara_Dbl_CoursePara1;

// -----------------------------------------------------------------------------
// AFS HLD/DBL parameter
// (Dynamic bending light)
// -----------------------------------------------------------------------------
typedef struct
{
  uint8 ucHlaFilterSize; // Head Light Angle rate limiter, correction
                                          // factor
  uint8 ucFilterTimePrio; // Constant used for calculation of the filter
                                          // time priority
  uint8 ucFilterTracking; // Constant used for calculation of the filter
                                          // tracking
  uint8 ucFilterTrackingRange; // Constant used for calculation of the filter
                                          // tracking range
}
tNvmPara_Dbl_AfsHld;

// -----------------------------------------------------------------------------
// AFS StraightLineDetection parameter
//  DBL idle range calculation
// (Dynamic bending light)
// -----------------------------------------------------------------------------
typedef struct {
  uint8      ucIdleRange0[CODM_PARA_AFSDBL_SIZE];     // [0.000025/m]  Idle range <= V0, (left, right)     
  uint8      ucIdleRange1[CODM_PARA_AFSDBL_SIZE];     // [0.000025/m]  Idle range >= V1, (left, right)     

  uint8      ucV0_straight_ahead_speed;                // [km/h]  
  uint8      ucV1_straight_ahead_speed;                // [km/h]  

  uint8      ucOnTime;            // [100ms]
  uint8      ucOnDelay;           // [100ms]
  uint8      ucOffTime;           // [100ms]   
  uint8      ucOffDelay;          // [100ms] 

  uint8      ucDummy[2];
} tNvmPara_Dbl_AfsIdle;

// -----------------------------------------------------------------------------
// AFS SwiRateLimiter parameter
//  DBL adaptive swivelling rate limiter algorithm 2
// (Dynamic bending light)
// -----------------------------------------------------------------------------
typedef struct {
   uint8 ucLimOutFast                      ; // limit for a fast movement to the outer side
   uint8 ucLimInFast                       ; // limit for a fast movement to the inner side
   uint8 ucLimOutSlow                      ; // limit for a slow movement to the outer side
   uint8 ucLimInSlow                       ; // limit for a slow movement to the inner side
   uint8 ucChangeRateOut                   ; // change rate of limits for a movement to the
                                           // outer side
   uint8 ucChangeRateIn                    ; // change rate of limits for a movement to the
                                           // inner side
   uint8 ucConstCurvature                  ; // this limit is compared against the curvature
                                           // gradient and determines limits
   uint8 ucCGCorrection                    ; // this factor transforms a curvature gradient
                                           // into a swiveling rate limiter
   uint8 ucreserviert1[2]                  ; 
} tNvmPara_Dbl_AfsSwiRateLim;

typedef struct 
{
  uint8 ucConstMaxThr; // threshold for deactivating constant speed
                                          // drive situation
  uint8 ucConstTimeThr; // time for which speed must be over activation
                                          // threshold to activate constant drive situation
  uint8 ucSwivelBackAngle; // angle for activating swivel back situation
  uint8 ucSwivelBackTime; // time threshold for activating swivel back
                                          // situation
  uint8 ucreserviert1[4];
}
tNvmPara_Dbl_DrivingSituationParam;

typedef struct
{
  uint8 ucDBL_LB_ANGLE_LIMITS_RIGHT_RGT[CODM_PARA_AFSDBL_SIZE]; // Swiveling angle limitation for right hand traffic, left headlamp in right curves, positive to the right
  sint8 snDBL_LB_ANGLE_LIMIT_LEFT_RHT; // Swiveling angle limitation for right hand
                                          // traffic, both headlamps in left curves, positiveto the right
  sint8 snDBL_LB_ANGLE_LIMITS_LEFT_LHT[CODM_PARA_AFSDBL_SIZE]; // Swiveling angle limitation for left hand traffic, right headlamp in left curves

  uint8 ucDBL_LB_ANGLE_LIMIT_RIGHT_LHT; // Swiveling angle limitation for left hand
                                          // traffic, both headlamps in right curves
  uint8 ucDBL_CURVE_OUTSIDE_HL_FACTOR_ADAPTION; // Setting for a different headlamp swiveling
                                          // angle between left and right headlamp
  uint8 ucHBS_HB_SWIVELING_ANGLE_MAX; // Maximum value of the angle order for highbeam
                                          // swiveling
}
tNvmPara_Dbl_DblAngleLimitations;

typedef struct
{
  uint16 unCRC_VEHICLE_WHEELBASE; //	Distance between front and rear axis
  uint16 unCRC_STEERING_RATIO; // Constant factor for transmission ratio of
                                          // steering wheel angle to tire angle
  uint8 ucCRC_WF_1; // Weighting factor 1 at Vehicle speed threshold
                                          // 1
  uint8 ucCRC_WF_2; // Weighting factor 2 at Vehicle speed threshold
                                          // 2
  uint8 ucCRC_WF_3; // Weighting factor 3 at Vehicle speed threshold
                                          // 3
  uint8 ucCRC_VEHICLE_SPEED_WF_1; //Vehicle speed threshold 1
  uint8 ucCRC_VEHICLE_SPEED_WF_2; //Vehicle speed threshold 2
  uint8 ucCRC_VEHICLE_SPEED_WF_3; //Vehicle speed threshold 3
}
tNvmPara_Dbl_DblCurvatureCalculation;

typedef struct
{
  uint8 ucTYPE_ECL_VIR_DYN; // Indicated the light source concerned by the bending light function
  uint8 ucreserviert1;
}
tNvmPara_Dbl_DblDiversity;

typedef struct
{
  tNvmPara_Dbl_DisableFuncs              DisableFuncs;
  tNvmPara_Dbl_AFSPolySolver2            AFSPolySolver2;
  tNvmPara_Dbl_AFSPolySolver2Add         AFSPolySolver2Add;
  tNvmPara_Dbl_AFSPolySolver2Angle       AFSPolySolver2Angle;
  tNvmPara_Dbl_AFSHldDev                 AFSHldDev;
  tNvmPara_Dbl_CoursePara1               CoursePara1;
  tNvmPara_Dbl_AfsHld                    AfsHld;
  tNvmPara_Dbl_AfsIdle                   AfsIdle;
  tNvmPara_Dbl_AfsSwiRateLim             AfsSwiRateLim;
  tNvmPara_Dbl_DrivingSituationParam     DrivingSituationParam;
  tNvmPara_Dbl_DblAngleLimitations       DblAngleLimitations;
  tNvmPara_Dbl_DblCurvatureCalculation   DblCurvatureCalculation;
  tNvmPara_Dbl_DblDiversity              DblDiversity;
}
tNvmPara_DblBlock;                                          // 120 Byte

#endif // __CODM_PARA_AFSDBL_H__

// EOF
