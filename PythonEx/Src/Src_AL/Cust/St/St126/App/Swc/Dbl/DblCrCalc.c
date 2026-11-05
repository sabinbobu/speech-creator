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
/// \file  DblCrCalc.c
///
/// \brief  Calculate curvature:
///
/// \desc   This module is calculating the Vehicle Path Curvature based 
///         on sine calculation, input signals and calibration data
///
///  \author  CALUGAR Radu - ALRO-CJ (M01472A)
///           mailTo:radusilviu.calugar[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#include "Dbl_RteAccess.h"
#include "DblCrCalc.h"
#include "DblData.h"
#include <ClAlg.h>

#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version

STATIC_AL CONST_AL uint16 DblCrCalc_aunCrvSin[91u] =
{
  //   sin(degree)*100000            degree
           0u	           ,            // 0
          175u	         ,            // 1
          349u	         ,            // 2
          523u	         ,            // 3
          698u	         ,            // 4
          872u	         ,            // 5
          1045u	         ,            // 6
          1219u	         ,            // 7
          1392u	         ,            // 8
          1564u	         ,            // 9
          1736u	         ,            // 10
          1908u	         ,            // 11
          2079u	         ,            // 12
          2250u	         ,            // 13
          2419u	         ,            // 14
          2588u	         ,            // 15
          2756u	         ,            // 16
          2924u	         ,            // 17
          3090u	         ,            // 18
          3256u	         ,            // 19
          3420u	         ,            // 20
          3584u	         ,            // 21
          3746u	         ,            // 22
          3907u	         ,            // 23
          4067u	         ,            // 24
          4226u	         ,            // 25
          4384u	         ,            // 26
          4540u	         ,            // 27
          4695u	         ,            // 28
          4848u	         ,            // 29
          5000u	         ,            // 30
          5150u	         ,            // 31
          5299u	         ,            // 32
          5446u	         ,            // 33
          5592u	         ,            // 34
          5736u	         ,            // 35
          5878u	         ,            // 36
          6018u	         ,            // 37
          6157u	         ,            // 38
          6293u	         ,            // 39
          6428u	         ,            // 40
          6561u	         ,            // 41
          6691u	         ,            // 42
          6820u	         ,            // 43
          6947u	         ,            // 44
          7071u	         ,            // 45
          7193u	         ,            // 46
          7314u	         ,            // 47
          7431u	         ,            // 48
          7547u	         ,            // 49
          7660u	         ,            // 50
          7771u	         ,            // 51
          7880u	         ,            // 52
          7986u	         ,            // 53
          8090u	         ,            // 54
          8192u	         ,            // 55
          8290u	         ,            // 56
          8387u	         ,            // 57
          8480u	         ,            // 58
          8572u	         ,            // 59
          8660u	         ,            // 60
          8746u	         ,            // 61
          8829u	         ,            // 62
          8910u	         ,            // 63
          8988u	         ,            // 64
          9063u	         ,            // 65
          9135u	         ,            // 66
          9205u	         ,            // 67
          9272u	         ,            // 68
          9336u	         ,            // 69
          9397u	         ,            // 70
          9455u	         ,            // 71
          9511u	         ,            // 72
          9563u	         ,            // 73
          9613u	         ,            // 74
          9659u	         ,            // 75
          9703u	         ,            // 76
          9744u	         ,            // 77
          9781u	         ,            // 78
          9816u	         ,            // 79
          9848u	         ,            // 80
          9877u	         ,            // 81
          9903u	         ,            // 82
          9925u	         ,            // 83
          9945u	         ,            // 84
          9962u	         ,            // 85
          9976u	         ,            // 86
          9986u	         ,            // 87
          9994u	         ,            // 88
          9998u	         ,            // 89
          10000u	       ,            // 90 
};

//=============================================================================
// defines
//=============================================================================

// quadrant degree x 10 delimeters
#define DBLCRCALC_Q1_MIN_LIMIT                           (sint16)0u //quadrant 1 min limit
#define DBLCRCALC_Q1_MAX_LIMIT                           (sint16)900  //quadrant 1 max limit
#define DBLCRCALC_Q2_MAX_LIMIT                           (sint16)1800 //quadrant 2 max limit
#define DBLCRCALC_Q3_MAX_LIMIT                           (sint16)2700 //quadrant 3 max limit
#define DBLCRCALC_Q4_MAX_LIMIT                           (sint16)3600 //quadrant 4 max limit
#define DBLCRCALC_ANGLE_MAX_VALUE                        7200  //angle max value
// angle sign
#define DBLCRCALC_POSITIVE_ANGLE_SIGN                        1
#define DBLCRCALC_NEGATIVE_ANGLE_SIGN                       -1

// parameters for weghting factor algorithm
#define DBLCRCALC_CFG_VVEHICLE_WF_1                          0    //[m/s]
#define DBLCRCALC_CFG_VVEHICLE_WF_2                          0  //[0.01m/s]
#define DBLCRCALC_CFG_VVEHICLE_WF_3                          DBLCRCALC_CFG_VVEHICLE_WF_2
#define DBLCRCALC_CFG_VVEHICLE_WF_4                          0  //[0.01m/s]

#define DBLCRCALC_CFG_WF_YAW_RATE_1                          0u
#define DBLCRCALC_CFG_WF_YAW_RATE_2                          0
#define DBLCRCALC_CFG_WF_YAW_RATE_3                          DBLCRCALC_CFG_WF_YAW_RATE_2
#define DBLCRCALC_CFG_WF_YAW_RATE_4                          0
#define DBLCRCALC_CFG_WF_YAW_RATE_MAX                        100
#define DBLCRCALC_CFG_WF_1ST_POINT                          -0
#define DBLCRCALC_CFG_WF_2ND_POINT                           1
#define DBLCRCALC_RESOLUTION_FACTOR_100                      100
#define DBLCRCALC_RESOLUTION_FACTOR_10                       10
#define DBLCRCALC_VELOCITY_FACTOR                            1000 / 3600  // [km / h to m / s]
#define DBLCRCALC_DEGREE2RADIAN(x)                           (sint32)((x) * (3140 / 180)) // convert degree to radian with 10000 resolution
#define DBLCRCALC_CURVATURE_FACTOR                           1000000000
#define DBLCRCALC_WF_CCALCULATION_FIRST_SLOPE                0
#define DBLCRCALC_WF_CCALCULATION_SECOND_SLOPE               1
#define DBLCRCALC_NULL_VALUE                                 0
#define DBLCRCALC_STEERING_RATIO_VALUE                       155u   // hardcoded value for steering ratio
#define DBLCRCALC_VEHICLE_WHEELBASE_VALUE                    2737u  // hardcoded value for wheelbase
#define DBLCRCALC_SINE_MIN_VALUE                             200    // min value for sine to avoid division by 0


//weighting factor configuration table
#define DBLCRCALC_CFG_WF_TABLE                                                                                                                                                                   \
{                                                                                                                                                                                                \
  /*                                                                                                                                                                                  */         \
  /*       index                     v_min                                    v_max                                wf_min                                wf_max                       */         \
  /*                                                                                                                                                                                  */         \
  /*  eWf_Slope1,    */ {     DBLCRCALC_CFG_VVEHICLE_WF_1          , DBLCRCALC_CFG_VVEHICLE_WF_2       ,     DBLCRCALC_CFG_WF_YAW_RATE_1         , DBLCRCALC_CFG_WF_YAW_RATE_2        },         \
  /*  eWf_Slope2,    */ {     DBLCRCALC_CFG_VVEHICLE_WF_3          , DBLCRCALC_CFG_VVEHICLE_WF_4       ,     DBLCRCALC_CFG_WF_YAW_RATE_3         , DBLCRCALC_CFG_WF_YAW_RATE_4        },         \
}// this table is overwritted with coding data

//=============================================================================
// function prototype
//=============================================================================
STATIC_AL tsAngleData       DblCrvCalc_ProcessAngle(sint16 snAngle);
STATIC_AL uint32            DblCrvCalc_getLinearInterpolatedValue(uint32 ulPointX, uint32 ulPointX0, uint32 ulPointX1, uint32 ulPointY0, uint32 ulPointY1);
STATIC_AL uint8             DblCrvCalc_WeightingFactorCalculation(uint16 nVehicleSpeed);
STATIC_AL uint8             DblCrvCalc_FindWfZone(uint32 ulVehicleSpeed);
STATIC_AL sint32            DblCrvCalc_GetSin(sint16 snAngle);

//=============================================================================
// global variables
//=============================================================================
STATIC_AL tsWfTable DblCrCalc_asCrv_WfTable[]  = DBLCRCALC_CFG_WF_TABLE;
STATIC_AL uint16    DblCrCalc_unSteering_Ratio = DBLCRCALC_STEERING_RATIO_VALUE, DblCrCalc_unCrcVehicleWheelbase = DBLCRCALC_VEHICLE_WHEELBASE_VALUE; // this values are overwritted with coding data
tsDbl_VehPathCurvatureData Dbl_sCurvatureData;

//=============================================================================
// functions
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief DblCrvCalc_getCurvatureValue
///
/// \descr This function calculate curvature value
///
/// \param  void
///
/// \return sint32 slVehPahCrvt
//-----------------------------------------------------------------------------
sint32 DblCrvCalc_getCurvatureValue(void)
{
  uint8  ucWf = 0u;
  sint32 slSineBeta = 0, slVitesseLacet = 0, slCrcBetaTire = 0, slVitesseVehicleRoues, slVehPahCrvt = 0;
  tsDbl_VehicleSpeed       sSpeedMsg           = { 0 };
  tsDbl_YawSpeed           sYawSpeed           = { 0 };
  tsDbl_SteeringWheelAngle sSteeringWheelAngle = { 0 };

  // get input values
  sSpeedMsg = Dbl_RteAccess_ReadVehicleSpeed();
  sYawSpeed = Dbl_RteAccess_ReadYawSpeed();
  sSteeringWheelAngle = Dbl_RteAccess_ReadSteeringWheelAngle();

  // resolution x10
  slCrcBetaTire = (sint32)(sSteeringWheelAngle.nSteeringWheelAngle * (sint32)DBLCRCALC_RESOLUTION_FACTOR_10) / (sint32)DblCrCalc_unSteering_Ratio; // degree
  slSineBeta = DblCrvCalc_GetSin((sint16)slCrcBetaTire);
  // resolution x100; >200 and <-200  to avoid division by 0
  Dbl_sCurvatureData.slCrcRadiusSteering = ((slSineBeta > DBLCRCALC_SINE_MIN_VALUE) || (slSineBeta < -DBLCRCALC_SINE_MIN_VALUE)) ? ((sint32)DblCrCalc_unCrcVehicleWheelbase * (sint32)DBLCRCALC_RESOLUTION_FACTOR_100) / (slSineBeta / (sint32)DBLCRCALC_RESOLUTION_FACTOR_100) : DBLCRCALC_NULL_VALUE; // m
  // resolution x1000
  slVitesseVehicleRoues = (sint32)sSpeedMsg.eVehicleSpeed.unVehicleSpeed * (sint32)DBLCRCALC_VELOCITY_FACTOR * (sint32)DBLCRCALC_RESOLUTION_FACTOR_100; // m/s
  // resolution 10 000
  slVitesseLacet = DBLCRCALC_DEGREE2RADIAN((sint32)sYawSpeed.eYawSpeed.nYawSpeed) ; // radians
  // resolution x10
  Dbl_sCurvatureData.slCrcRadiusYaw = (slVitesseLacet != DBLCRCALC_NULL_VALUE) ? ((slVitesseVehicleRoues * DBLCRCALC_RESOLUTION_FACTOR_10) / slVitesseLacet) : DBLCRCALC_NULL_VALUE; // m
  // resolution x 100
  Dbl_sCurvatureData.ucWf = DblCrvCalc_WeightingFactorCalculation(sSpeedMsg.eVehicleSpeed.unVehicleSpeed);
  // resolution x 100
  Dbl_sCurvatureData.slCurveRadiusValue = ((sint32)(((Dbl_sCurvatureData.slCrcRadiusYaw * (sint32)Dbl_sCurvatureData.ucWf) + ((Dbl_sCurvatureData.slCrcRadiusSteering * ((sint32)DBLCRCALC_RESOLUTION_FACTOR_100 - (sint32)Dbl_sCurvatureData.ucWf)))))); //m
  // resolution x 1000
  slVehPahCrvt = (Dbl_sCurvatureData.slCurveRadiusValue != DBLCRCALC_NULL_VALUE) ? DBLCRCALC_CURVATURE_FACTOR / Dbl_sCurvatureData.slCurveRadiusValue : DBLCRCALC_NULL_VALUE; //m^-1

  // limit raw curvature value 
  Dbl_sCurvatureData.slCurvatureRawValue = slVehPahCrvt > DBL_POSITIVE_RAW_CURVATURE_LIMIT ? DBL_POSITIVE_RAW_CURVATURE_LIMIT : slVehPahCrvt;
  Dbl_sCurvatureData.slCurvatureRawValue = slVehPahCrvt < DBL_NEGATIVE_RAW_CURVATURE_LIMIT ? DBL_NEGATIVE_RAW_CURVATURE_LIMIT : slVehPahCrvt;
  Dbl_sCurvatureData.slCurvatureRawValue = slVehPahCrvt == DBLCRCALC_NULL_VALUE ? DBLCRCALC_NULL_VALUE : Dbl_sCurvatureData.slCurvatureRawValue;

  // limitation for angle calculation
  slVehPahCrvt = slVehPahCrvt > DBL_POSITIVE_CURVATURE_LIMIT  ? DBL_POSITIVE_CURVATURE_LIMIT : slVehPahCrvt;
  slVehPahCrvt = slVehPahCrvt < DBL_NEGATIVE_CURVATURE_LIMIT  ? DBL_NEGATIVE_CURVATURE_LIMIT : slVehPahCrvt;
  slVehPahCrvt = slVehPahCrvt == DBLCRCALC_NULL_VALUE         ? DBLCRCALC_NULL_VALUE         : slVehPahCrvt;
  slVehPahCrvt = DBL_CURVE_OUTSIDE_HL_FACTOR_ADAPTION(slVehPahCrvt);

  return slVehPahCrvt;
}

//-----------------------------------------------------------------------------
/// \brief  DblCrvCalc_GetSin
///
/// \descr  This function revies an angle in range [-360, 360] handles the 
/// position of angle in unit circle and calculates the sine of that angle
///
/// \param  snAngle : recived angle
///
/// \return slRetSinValue : value of sine
//-----------------------------------------------------------------------------
STATIC_AL sint32 DblCrvCalc_GetSin(sint16 snAngle)
{
  uint16      unAngle0 = 0u, unAngle1 = 0u;
  uint32      ulInterpolatedSinAngle = 0u;
  sint16      snGetSignedAngle = 0, snRecivedAngle = 0;
  sint32      slRetSinValue = 0;
  tsAngleData sAngleData = {0};
 
  sAngleData = DblCrvCalc_ProcessAngle(snAngle);
  snRecivedAngle = sAngleData.snAngleValue;

  // current and next angle is needed in [0,90] range
  unAngle0 = (uint16)(snRecivedAngle) / (uint16)DBLCRCALC_RESOLUTION_FACTOR_10;
  unAngle1 = unAngle0 + 1u;
  
  // if there is a fixed angle, interpolation is not needed
  if (snRecivedAngle % DBLCRCALC_RESOLUTION_FACTOR_10 != DBLCRCALC_NULL_VALUE) // get last digit
  {
    // store interpolated value of angle
    ulInterpolatedSinAngle = DblCrvCalc_getLinearInterpolatedValue((uint32)(snRecivedAngle), (uint32)unAngle0 * (uint32)DBLCRCALC_RESOLUTION_FACTOR_10, (uint32)((uint32)unAngle1 * (uint32)DBLCRCALC_RESOLUTION_FACTOR_10), (uint32) (DblCrCalc_aunCrvSin[(uint32)unAngle0] * (uint32)DBLCRCALC_RESOLUTION_FACTOR_10), (uint32)(DblCrCalc_aunCrvSin[(uint32)unAngle1] * (uint32)DBLCRCALC_RESOLUTION_FACTOR_10));
    // get sine value
    slRetSinValue = (sint32)sAngleData.scSgn * (sint32)ulInterpolatedSinAngle;
  }
  else
  {
    // get the value of sine directly from LUT
    slRetSinValue = (sint32)sAngleData.scSgn * (sint32)DblCrCalc_aunCrvSin[unAngle0] * (sint32)DBLCRCALC_RESOLUTION_FACTOR_10;
  }
  return slRetSinValue;
}

//-----------------------------------------------------------------------------
/// \brief DblCrvCalc_ProcessAngle
///
/// \descr  Gets the quadrant and sign for the angle recived
///
/// \param  unAngle
///
/// \return sQadData : sign and angle processed value
//-----------------------------------------------------------------------------
STATIC_AL tsAngleData DblCrvCalc_ProcessAngle(sint16 snAngle)
{
  tsAngleData sAngleData;
  sint16 sngetAngleValue, sngetAngleSign;

  sngetAngleSign = (snAngle < DBLCRCALC_NULL_VALUE) ? DBLCRCALC_NEGATIVE_ANGLE_SIGN : DBLCRCALC_POSITIVE_ANGLE_SIGN;
  sngetAngleValue = sngetAngleSign * snAngle;

  if (sngetAngleValue > DBLCRCALC_Q4_MAX_LIMIT)
  {
    // limit angle in [0,3600] range
    sngetAngleValue = (sngetAngleValue < DBLCRCALC_ANGLE_MAX_VALUE) ? sngetAngleValue - DBLCRCALC_Q4_MAX_LIMIT : sngetAngleValue - DBLCRCALC_ANGLE_MAX_VALUE;
  }
  else
  {
    // do nothing
  }

  // get angle processed value and sign
  sAngleData.scSgn = (sint8)sngetAngleSign;

  //sin(x) = | sin(x)       ; 0  <= x < = 90 
  //         |
  //         | sin(180 - x) ; 90  < x <= 180 
  //         |
  //         | sin(x - 180) ; 180 < x <= 270
  //         |
  //         | sin(360 - x) ; 270 < x <= 360

  // get angle value
  if ((sngetAngleValue >= DBLCRCALC_Q1_MIN_LIMIT) && (sngetAngleValue <= DBLCRCALC_Q1_MAX_LIMIT))
  {
    sAngleData.snAngleValue = sngetAngleValue;
  }
  else
  if ((sngetAngleValue >  DBLCRCALC_Q1_MAX_LIMIT) && (sngetAngleValue <= DBLCRCALC_Q2_MAX_LIMIT))
  {
    sAngleData.snAngleValue = DBLCRCALC_Q2_MAX_LIMIT - sngetAngleValue;
  }
  else
  if ((sngetAngleValue >  DBLCRCALC_Q2_MAX_LIMIT) && (sngetAngleValue <= DBLCRCALC_Q3_MAX_LIMIT))
  {
    sAngleData.snAngleValue = sngetAngleValue - DBLCRCALC_Q2_MAX_LIMIT;
    sAngleData.scSgn *= DBLCRCALC_NEGATIVE_ANGLE_SIGN;
  }
  else
  if ((sngetAngleValue >  DBLCRCALC_Q3_MAX_LIMIT) && (sngetAngleValue <= DBLCRCALC_Q4_MAX_LIMIT))
  {
    sAngleData.snAngleValue = DBLCRCALC_Q4_MAX_LIMIT - sngetAngleValue;  //4th quadrant
    sAngleData.scSgn *= DBLCRCALC_NEGATIVE_ANGLE_SIGN;
  }
#ifndef UNIT_TEST
  else
  {
    //do nothing-angle is already processed
  }
#endif // !UNIT_TEST

  return sAngleData;
}

//-----------------------------------------------------------------------------
/// \brief  DblCrvCalc_getLinearInterpolatedValue
///
/// \descr  Interpolates interpolates value of an angle  
///
/// \param  ulPointX
/// \param  ulPointX0
/// \param  ulPointX1
/// \param  ulPointY0
/// \param  ulPointY1
///
/// \return interpolated value
//-----------------------------------------------------------------------------
STATIC_AL uint32 DblCrvCalc_getLinearInterpolatedValue(uint32 ulPointX, uint32 ulPointX0, uint32 ulPointX1, uint32 ulPointY0, uint32 ulPointY1)
{
  return (ulPointY0 + ((ulPointY1 - ulPointY0) * (uint32)((uint32)ulPointX - (uint32)ulPointX0)) / (uint32)((uint32)ulPointX1 - (uint32)ulPointX0));
}

//-----------------------------------------------------------------------------
/// \brief  DblCrvCalc_WeightingFactorCalculation
///
/// \descr This function calculate Weighting Factor based on Current speed
///
/// \param  nVehicleSpeed - current speed
///
/// \return Weighting Factor [0.1]
//-----------------------------------------------------------------------------
STATIC_AL uint8 DblCrvCalc_WeightingFactorCalculation(uint16 nVehicleSpeed)
{
  uint8 ucWf = 0u;
  uint8 ucZoneIndex = 0u;

  //check out of range
  if ((sint32)nVehicleSpeed < (sint32)DblCrCalc_asCrv_WfTable[DBLCRCALC_CFG_WF_1ST_POINT].ulV_Min)
  {
    ucWf = DblCrCalc_asCrv_WfTable[DBLCRCALC_CFG_WF_1ST_POINT].ucWf_Min;
  }
  else if ((sint32)nVehicleSpeed > (sint32)DblCrCalc_asCrv_WfTable[DBLCRCALC_CFG_WF_2ND_POINT].ulV_Max)
  {
    ucWf = DblCrCalc_asCrv_WfTable[DBLCRCALC_CFG_WF_2ND_POINT].ucWf_Max;
  }
  else
  {
    ucZoneIndex = DblCrvCalc_FindWfZone((uint32)nVehicleSpeed);
    ucWf = (uint8)(DblCrvCalc_getLinearInterpolatedValue((uint32)nVehicleSpeed, (uint32)DblCrCalc_asCrv_WfTable[ucZoneIndex].ulV_Min , (uint32)DblCrCalc_asCrv_WfTable[ucZoneIndex].ulV_Max , (uint32)DblCrCalc_asCrv_WfTable[ucZoneIndex].ucWf_Min , (uint32)DblCrCalc_asCrv_WfTable[ucZoneIndex].ucWf_Max )) ;
  }
  return ucWf;
}

// ---------------------------------------------------------------------------
//  \func     DblCrvCalc_FindWfZone
//
//  \brief    this function find the coresponding point from CFG table based on 
//            actual speed
//
//  \param    DblCrvCalc_FindWfZone - current speed
//
//  \return   uint8 - point
// ---------------------------------------------------------------------------
STATIC_AL uint8 DblCrvCalc_FindWfZone(uint32 ulVehicleSpeed)
{
  uint8 ucIdx = 0;
  uint8 ucSizeOfWfTable = (sizeof(DblCrCalc_asCrv_WfTable) / sizeof(DblCrCalc_asCrv_WfTable[0]));
  for (ucIdx = 0u; ucIdx < ucSizeOfWfTable; ucIdx++)
  {
    // check range
    if ((ulVehicleSpeed >= DblCrCalc_asCrv_WfTable[ucIdx].ulV_Min) && (ulVehicleSpeed <= DblCrCalc_asCrv_WfTable[ucIdx].ulV_Max))
    {
      break;
    }
    else
    {
      // keep counting
    }
  }
  // return zone
  return ucIdx;
}

// ---------------------------------------------------------------------------
//  \func     DblCrvCalc_Get_WfCodingParameters
//
//  \brief    get weghting factor parameters from coding
//
//  \param    void
//
//  \return   void
// ---------------------------------------------------------------------------
void DblCrvCalc_Get_WfCodingParameters(void)
{
  // Get coding data for first slope parameters
  DblCrCalc_asCrv_WfTable[DBLCRCALC_WF_CCALCULATION_FIRST_SLOPE].ulV_Min   = (uint32)CodDblCurvatureCalculation_Crc_Vehicle_Speed_Wf_1() * (uint32)DBLCRCALC_RESOLUTION_FACTOR_100;
  DblCrCalc_asCrv_WfTable[DBLCRCALC_WF_CCALCULATION_FIRST_SLOPE].ulV_Max   = (uint32)CodDblCurvatureCalculation_Crc_Vehicle_Speed_Wf_2() * (uint32)DBLCRCALC_RESOLUTION_FACTOR_100;
  DblCrCalc_asCrv_WfTable[DBLCRCALC_WF_CCALCULATION_FIRST_SLOPE].ucWf_Min  = (uint8)CodDblCurvatureCalculation_Crc_Wf_1() * (uint8)DBLCRCALC_RESOLUTION_FACTOR_10;
  DblCrCalc_asCrv_WfTable[DBLCRCALC_WF_CCALCULATION_FIRST_SLOPE].ucWf_Max  = (uint8)CodDblCurvatureCalculation_Crc_Wf_2() * (uint8)DBLCRCALC_RESOLUTION_FACTOR_10;
  // Get coding data for second slope parameters
  DblCrCalc_asCrv_WfTable[DBLCRCALC_WF_CCALCULATION_SECOND_SLOPE].ulV_Min  = (uint32)CodDblCurvatureCalculation_Crc_Vehicle_Speed_Wf_2() * (uint32)DBLCRCALC_RESOLUTION_FACTOR_100;
  DblCrCalc_asCrv_WfTable[DBLCRCALC_WF_CCALCULATION_SECOND_SLOPE].ulV_Max  = (uint32)CodDblCurvatureCalculation_Crc_Vehicle_Speed_Wf_3() * (uint32)DBLCRCALC_RESOLUTION_FACTOR_100;
  DblCrCalc_asCrv_WfTable[DBLCRCALC_WF_CCALCULATION_SECOND_SLOPE].ucWf_Min = CodDblCurvatureCalculation_Crc_Wf_2() * (uint8)DBLCRCALC_RESOLUTION_FACTOR_10;
  DblCrCalc_asCrv_WfTable[DBLCRCALC_WF_CCALCULATION_SECOND_SLOPE].ucWf_Max = CodDblCurvatureCalculation_Crc_Wf_3() * (uint8)DBLCRCALC_RESOLUTION_FACTOR_10;
}


// ---------------------------------------------------------------------------
//  \func     DblCrvCalc_Get_CurvatureCodingParameters
//
//  \brief    get curvature  parameters from coding
//
//  \param    void
//
//  \return   void
// ---------------------------------------------------------------------------
void DblCrvCalc_Get_CurvatureCodingParameters(void)
{
// Get coding data for curvature parameters
DblCrCalc_unCrcVehicleWheelbase = CodDblCurvatureCalculation_Crc_Vehicle_Wheelbase();
DblCrCalc_unSteering_Ratio = CodDblCurvatureCalculation_Crc_Steering_Ratio();
}

#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)
