#ifndef __ADB_MXB4DATA_H__
#define __ADB_MXB4DATA_H__

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
/// \file  AdbMxb4Data.h
///
/// \brief  
///
/// \descr  
///
///         Additional information can be found in the design description (Link:
///         <a href="file:///\\Dereu1nquest1\XXX_Docu\Gen\03_MDRD\MDDD_XXX.doc">MDDD</a>)
///
/// \author Vornicu, Tony ALRT/EEG3 * (F63906B)
///         mailTo:tony.vornicu@marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//  Includes
//-----------------------------------------------------------------------------

#include <Bsw/Common/Std_Types.h>
#include <Swc/CodM/CodM.h>
#include <AL_Helper.h>
#include "AdbMxb3Types.h"
#include <RteCommonTypes.h>
#ifndef UNIT_TEST
#include <Rte.h>
#endif // UNIT_TEST


//-----------------------------------------------------------------------------
//  Defines
//-----------------------------------------------------------------------------

#define ADBMXB4DATA_0_BIT                                        1u     // 2 pow 0
#define ADBMXB4DATA_1_BIT                                        2u     // 2 pow 1
#define ADBMXB4DATA_2_BIT                                        4u     // 2 pow 2
#define ADBMXB4DATA_3_BIT                                        8u     // 2 pow 3
#define ADBMXB4DATA_4_BIT                                        16u    // 2 pow 4
#define ADBMXB4DATA_5_BIT                                        32u    // 2 pow 5
#define ADBMXB4DATA_6_BIT                                        64u    // 2 pow 6
#define ADBMXB4DATA_7_BIT                                        128u   // 2 pow 7

#define ADBMXB4DATA_INVALID_HCLUSTERMINDISTANCE_X                0x1FFu       //  HCLUSTERMINDISTANCE_X left and right invalid value (X = 1 to 5)
#define ADBMXB4DATA_INVALID_HCLUSTERMINDISTANCE_X_MIN_VAL        0x1F5u       //  HCLUSTERMINDISTANCE_X left and right minimum invalid value (X = 1 to 5)
#define ADBMXB4DATA_INVALID_HCLUSTERMINDISTANCE_X_MAX_VAL        0x1FDu       //  HCLUSTERMINDISTANCE_X left and right maximum invalid value (X = 1 to 5)
#define ADBMXB4DATA_INVALID_HCLUSTERDISTANCE_X                   0x1FFu       //  HCLUSTERDISTANCE_X left and right invalid value (X = 1 to 5)
#define ADBMXB4DATA_INVALID_HCLUSTERDISTANCE_X_MIN_VAL           0x1F5u       //  HCLUSTERDISTANCE_X left and right minimum invalid value (X = 1 to 5)
#define ADBMXB4DATA_INVALID_HCLUSTERDISTANCE_X_MAX_VAL           0x1FDu       //  HCLUSTERDISTANCE_X left and right maximum invalid value (X = 1 to 5)
#define ADBMXB4DATA_INVALID_HCLUSTERANGLE_X                      0x0FF        //  HCLUSTERANGLE_X left and right invalid value (X = 1 to 5)
#define ADBMXB4DATA_INVALID_HCLUSTERANGLE_X_MIN_VAL_1            0x0FB        //  HCLUSTERANGLE_X left and right minimum invalid value 1 (X = 1 to 5)
#define ADBMXB4DATA_INVALID_HCLUSTERANGLE_X_MAX_VAL_1            0x0FD        //  HCLUSTERANGLE_X left and right maximum invalid value 1 (X = 1 to 5)
#define ADBMXB4DATA_INVALID_HCLUSTERANGLE_X_MIN_VAL_2            0x100        //  HCLUSTERANGLE_X left and right minimum invalid value 2 (X = 1 to 5)
#define ADBMXB4DATA_INVALID_HCLUSTERANGLE_X_MAX_VAL_2            0x105        //  HCLUSTERANGLE_X left and right maximum invalid value 2 (X = 1 to 5)
#define ADBMXB4DATA_INVALID_HCLUSTERBOTTOMANGLE_X                0x7F         //  HCLUSTERBOTTOMANGLE_X invalid value (X = 1 to 5)
#define ADBMXB4DATA_INVALID_HCLUSTERBOTTOMANGLE_X_MIN_VAL_1       101         //  HCLUSTERBOTTOMANGLE_X minimum invalid value 1 (X = 1 to 5)
#define ADBMXB4DATA_INVALID_HCLUSTERBOTTOMANGLE_X_MAX_VAL_1       125         //  HCLUSTERBOTTOMANGLE_X maximum invalid value 1 (X = 1 to 5)
#define ADBMXB4DATA_INVALID_HCLUSTERBOTTOMANGLE_X_MIN_VAL_2      -128         //  HCLUSTERBOTTOMANGLE_X minimum invalid value 2 (X = 1 to 5)
#define ADBMXB4DATA_INVALID_HCLUSTERBOTTOMANGLE_X_MAX_VAL_2      -101         //  HCLUSTERBOTTOMANGLE_X maximum invalid value 2 (X = 1 to 5)
#define ADBMXB4DATA_INVALID_HCLUSTERAZIMUTHRATE_X                0x7F         //  HCLUSTERAZIMUTHRATE_X left and right invalid value (X = 1 to 5)
#define ADBMXB4DATA_INVALID_HCLUSTERAZIMUTHRATE_LR_X_MIN_VAL_1    117         //  HCLUSTERAZIMUTHRATE_X left and right minimum invalid value 1 (X = 1 to 5)
#define ADBMXB4DATA_INVALID_HCLUSTERAZIMUTHRATE_L_MAX_VAL_1       126         //  HCLUSTERAZIMUTHRATE_X left maximum invalid value 1 (X = 1 to 5)
#define ADBMXB4DATA_INVALID_HCLUSTERAZIMUTHRATE_R_MAX_VAL_1       125         //  HCLUSTERAZIMUTHRATE_X right maximum invalid value 1 (X = 1 to 5)
#define ADBMXB4DATA_INVALID_HCLUSTERAZIMUTHRATE_X_MIN_VAL_2      -128         //  HCLUSTERAZIMUTHRATE_X left and right minimum invalid value 2 (X = 1 to 5)
#define ADBMXB4DATA_INVALID_HCLUSTERAZIMUTHRATE_X_MAX_VAL_2      -101         //  HCLUSTERAZIMUTHRATE_X left and right maximum invalid value 2 (X = 1 to 5)

#define ADBMXB4DATA_UNAVAILABLE_HCLUSTERMINDISTANCE_0E3_1        0x1FEu       //  HCLUSTERMINDISTANCE_1 unavailable value for frame 0xE3
#define ADBMXB4DATA_UNAVAILABLE_HCLUSTERMINDISTANCE_0E3_2        0x1FEu       //  HCLUSTERMINDISTANCE_1 unavailable value for frame 0xE3
#define ADBMXB4DATA_UNAVAILABLE_HCLUSTERMINDISTANCE_X            0x1FEu       //  HCLUSTERMINDISTANCE_X unavailable value (X = 2 to 5)
#define ADBMXB4DATA_UNAVAILABLE_HCLUSTERDISTANCE_X               0x1FEu       //  HCLUSTERDISTANCE_X unavailable value (X = 1 to 5)
#define ADBMXB4DATA_UNAVAILABLE_HCLUSTERBOTTOMANGLE_X             0x7E        //  HCLUSTERBOTTOMANGLE_X unavilable value (X = 1 to 5)
#define ADBMXB4DATA_UNAVAILABLE_HCLUSTERANGLE_0E3                 0x0FE        //  H_CLUSTER_ANGLE_50D left and right unavailable value for frame 0xE3
#define ADBMXB4DATA_UNAVAILABLE_HCLUSTERANGLE_X                  0x0FE        //  HCLUSTERANGLE_X left and right unavailable value (X = 2 to 5)
#define ADBMXB4DATA_UNAVAILABLE_HCLUSTERAZIMUTHRATE_0E3             0x7E        //  H_CLUSTER_AZIMUTH_RATE left and right unavailable value for frame 0xE3
#define ADBMXB4DATA_UNAVAILABLE_HCLUSTERAZIMUTHRATE_X               0x7E        //  HCLUSTERAZIMUTHRATE_X left and right unavailable value (X = 2 to 5)

#define ADBMXB4DATA_CAMOBJDISRES                            (uint16)2u        // Distance resolution

#define ADBMXB4DATA_CAMOBJ_1                                       0u           //  Index for frame ID 0xE3
#define ADBMXB4DATA_CAMOBJ_2                                       1u           //  Index for frame ID 0xEB
#define ADBMXB4DATA_CAMOBJ_3                                       2u           //  Index for frame ID 0x103
#define ADBMXB4DATA_CAMOBJ_4                                       3u           //  Index for frame ID 0x10B
#define ADBMXB4DATA_CAMOBJ_5                                       4u           //  Index for frame ID 0x123

#define ADBMXB4DATA_CHANNEL_1                                      0u           //  Index for channel output 
#define ADBMXB4DATA_CHANNEL_2                                      1u           //  Index for channel output 
#define ADBMXB4DATA_CHANNEL_3                                      2u           //  Index for channel output 
#define ADBMXB4DATA_CHANNEL_4                                      3u           //  Index for channel output 
#define ADBMXB4DATA_CHANNEL_5                                      4u           //  Index for channel output 

#define ADBMXB4DATA_CAMOBJ_NR                                      5u           //  Number of incoming objects

#define ADBMXB4DATA_CAMOBJ_PERCEIVE_1                              0u           //  Index for frame ID 0xAB
#define ADBMXB4DATA_CAMOBJ_PERCEIVE_2                              1u           //  Index for frame ID 0xCB
#define ADBMXB4DATA_CAMOBJ_PERCEIVE_3                              2u           //  Index for frame ID 0xC3

#define ADBMXB4DATA_CAMOBJ_PERCEIVE_NR                             3u           //  Number of incoming Perceive objects

#define ADBMXB4DATA_ZERO_VALUE                                     0u

// [LDMO-1823] - Workaround applied , needs to be decided with Stellantis if this solution is OK TODO VS: Allign with Stellantis and Amish
#define ADBMXB4DATA_CLUSTER_ID_INVALID                            255           // Invalid value used to deactivate GFHB tunnels in case of unavailable or invalid values

#define ADBMXB4DATA_PERCIEVERFL_X_TYPE                           3u
#define ADBMXB4DATA_INVALID_PERCEIVERFL_X_BRIGHTNESS_MIN_VAL     0x65u        //  PERCEIVERFL_X_BRIGHTNESS minimum invalid value (X = 1 to 3)
#define ADBMXB4DATA_INVALID_PERCEIVERFL_X_BRIGHTNESS_MAX_VAL     0x7Du        //  PERCEIVERFL_X_BRIGHTNESS maximum invalid value (X = 1 to 3)
#define ADBMXB4DATA_INVALID_PERCEIVERFL_X_BRIGHTNESS             0x7Fu        //  PERCEIVERFL_X_BRIGHTNESS invalid
#define ADBMXB4DATA_INVALID_PERCEIVERFL_X_L_R_ANGLE_MIN_VAL_1    0x0FA1       //  PERCEIVERFL_X_L_R_ANGLE left and right minimum invalid value 1 (X = 1 to 3)
#define ADBMXB4DATA_INVALID_PERCEIVERFL_X_L_R_ANGLE_MAX_VAL_1    0x0FFD       //  PERCEIVERFL_X_L_R_ANGLE left and right maximum invalid value 1 (X = 1 to 3)
#define ADBMXB4DATA_INVALID_PERCEIVERFL_X_L_R_ANGLE              0x0FFF       //  PERCEIVERFL_X_L_R_ANGLE left and right INVALID value
#define ADBMXB4DATA_INVALID_PERCEIVERFL_X_L_R_ANGLE_MIN_VAL_2    -4096        //  PERCEIVERFL_X_L_R_ANGLE left and right minimum invalid value 2 (X = 1 to 3)
#define ADBMXB4DATA_INVALID_PERCEIVERFL_X_L_R_ANGLE_MAX_VAL_2    -4001        //  PERCEIVERFL_X_L_R_ANGLE left and right maximum invalid value 2 (X = 1 to 3)
#define ADBMXB4DATA_INVALID_PERCEIVERFL_X_T_B_ANGLE_MIN_VAL_1    -1024        //  PERCEIVERFL_X_T_B_ANGLE top and bottom minimum invalid value 1 (X = 1 to 3)
#define ADBMXB4DATA_INVALID_PERCEIVERFL_X_T_B_ANGLE_MAX_VAL_1    -1001        //  PERCEIVERFL_X_T_B_ANGLE top and bottom maximum invalid value 1 (X = 1 to 3)
#define ADBMXB4DATA_INVALID_PERCEIVERFL_X_T_B_ANGLE_MIN_VAL_2    0x3E9        //  PERCEIVERFL_X_T_B_ANGLE top and bottom minimum invalid value 2 (X = 1 to 3)
#define ADBMXB4DATA_INVALID_PERCEIVERFL_X_T_B_ANGLE_MAX_VAL_2    0x3FD        //  PERCEIVERFL_X_T_B_ANGLE top and bottom maximum invalid value 2 (X = 1 to 3)
#define ADBMXB4DATA_INVALID_PERCEIVERFL_X_T_B_ANGLE              0x3FF        //  PERCEIVERFL_X_T_B_ANGLE top and bottom invalid value
#define ADBMXB4DATA_INVALID_PERCEIVERFL_X_DISTANCE_MIN_VAL       0x1F5u       //  PERCEIVERFL_X_DISTANCE minimum invalid value (X = 1 to 3)
#define ADBMXB4DATA_INVALID_PERCEIVERFL_X_DISTANCE_MAX_VAL       0x1FDu       //  PERCEIVERFL_X_DISTANCE maximum invalid value (X = 1 to 3)
#define ADBMXB4DATA_INVALID_PERCEIVERFL_X_DISTANCE               0x1FFu       //  PERCEIVERFL_X_DISTANCE invalid value
#define ADBMXB4DATA_INVALID_PERCEIVERFL_X_AZIMUTHRATE_MIN_VAL_1  66           //  PERCEIVERFL_X_AZIMUTHRATE left and right minimum invalid value 1 (X = 1 to 3)
#define ADBMXB4DATA_INVALID_PERCEIVERFL_X_AZIMUTHRATE_MAX_VAL_1  125          //  PERCEIVERFL_X_AZIMUTHRATE left and right maximum invalid value 1 (X = 1 to 3)
#define ADBMXB4DATA_INVALID_PERCEIVERFL_X_AZIMUTHRATE_MIN_VAL_2  -128         //  PERCEIVERFL_X_AZIMUTHRATE left and right minimum invalid value 2 (X = 1 to 3)
#define ADBMXB4DATA_INVALID_PERCEIVERFL_X_AZIMUTHRATE_MAX_VAL_2  -66          //  PERCEIVERFL_X_AZIMUTHRATE left and right maximum invalid value 2 (X = 1 to 3)
#define ADBMXB4DATA_INVALID_PERCEIVERFL_X_AZIMUTHRATE            0x7F         //  PERCEIVERFL_X_AZIMUTHRATE invalid value 
#define ADBMXB4DATA_UNAVAILABLE_PERCEIVERFL_X_BRIGHTNESS         0x7Eu        //  ADBMXB4DATA_UNAVAILABLE_PERCEIVERFL_X_BRIGHTNESS UNAVAILABLE
#define ADBMXB4DATA_UNAVAILABLE_PERCEIVERFL_X_L_R_ANGLE          0x0FFE       //  ADBMXB4DATA_UNAVAILABLE_PERCEIVERFL_X_L_R_ANGLE left and right UNAVAILABLE value
#define ADBMXB4DATA_UNAVAILABLE_PERCEIVERFL_X_T_B_ANGLE          0x3FE        //  ADBMXB4DATA_UNAVAILABLE_PERCEIVERFL_X_T_B_ANGLE top and bottom UNAVAILABLE value
#define ADBMXB4DATA_UNAVAILABLE_PERCEIVERFL_X_DISTANCE           0x1FEu       //  ADBMXB4DATA_UNAVAILABLE_PERCEIVERFL_X_DISTANCE UNAVAILABLE value
#define ADBMXB4DATA_UNAVAILABLE_PERCEIVERFL_X_AZIMUTHRATE        0x7E         //  ADBMXB4DATA_UNAVAILABLE_PERCEIVERFL_X_AZIMUTHRATE UNAVAILABLE value 


//-----------------------------------------------------------------------------
//  Types
//-----------------------------------------------------------------------------

extern CONST_AL tNvmPara_CodingArea*   AdbMxb4Data_pCodingArea;
extern boolean                         AdbMxb4Data_boCodingValid; 

// Structure used to validate the signals coming from SigPrep
typedef struct
{
  uint8               ucClusterId;
  teRte_ClusterTypeX  eClusterType;
  sint16              nClusterAngleLeft;
  sint16              nClusterAngleRight;
  sint8               cClusterRightAzimuthRate;
  sint8               cClusterLeftAzimuthRate;
  sint8               cClusterBottomAngle;
  uint16              unClusterMinDistance;
  uint16			  unClusterLeftDistance;
  uint16              unClusterRightDistance;
}tsCamObject_FrmCheck;

// Structure used to validate the Perceive signals coming from SigPrep
typedef struct
{
  uint8               ucPerceiveId;
  sint16              nLeftAngle;
  sint16              nRightAngle;
  sint8               cLeftAzimuthRate;
  sint8               cRightAzimuthRate;
  sint16              nBottomAngle;
  sint16              nTopAngle;
  uint16              unDistance;
  uint8               ucBrightness;
}tsCamObjectPerceive_FrmCheck;


// Structure used to validate the flags and timers of Validity Check
typedef struct
{
  TIMER   ulConstCheck_StartTime;
  boolean boConstCheck_Flag;
  TIMER   ulInvalCheck_StartTime;
  boolean boInvalCheck_Flag;
  TIMER   ulUnavalCheck_StartTime;
  boolean boUnavalCheck_Flag;
}tsCamObject_ValidityTimers;

// Structure used to validate the flags and timers of Azimuth Rate Validity Check
typedef struct
{
  TIMER   ulUnavalCheck_StartTime;
  boolean boUnavalCheck_Flag;
}tsCamObject_AzimuthRateValidity;

// Structure used to validate the flags and timers of Perceive Signals Validity Check
typedef struct
{
  TIMER   ulInvalCheck_StartTime;
  boolean boInvalCheck_Flag;
}tsCamObjectPerceive_ValidityTimers;

// Structure used to send GFHB_DIAG back to SysMonTx
typedef struct
{
  boolean boDiagGfhb;
}tsCamObject_GfhbDiag;

// AdbMxb4Data strcture to handle invalid data and DTC setting for CVM frames
typedef struct tsAdbMxb4Data_ClusterSigGroup1_InvalidData
{
	Dem_EventListId_EnumType  eDemEventId;
}tsAdbMxb4Data_ClusterSigGroup1_InvalidData;

// AdbMxb4Data strcture to handle invalid data and DTC setting for Perceive frames
typedef struct tsAdbMxb4Data_PerceiveSigGroup1_InvalidData
{
	Dem_EventListId_EnumType  eDemEventId;
}tsAdbMxb4Data_PerceiveSigGroup1_InvalidData;


// ----------------------------------------------------------------------------
// Function prototypes
// ----------------------------------------------------------------------------

void AdbMxb4Data_ParaFct0(CONST_AL tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData);
void AdbMxb4Data_Init(void);

void AdbMxb4Data_AdbStatus(boolean bCurtainEffectStatus, boolean bHBBStatus);
tieAdbTrafficStyle AdbMxb4Data_GetTrafficStyle(void);
tAdbSpeedTL_kph AdbMxb4Data_GetSpeed(void);
uint8 AdbMxb4Data_GetMotorwayDetection(void);
uint8 AdbMxb4Data_GetHBActivation(void);
uint8 AdbMxb4Data_GetHBFlashActivation(void);
uint8 AdbMxb4Data_GetGFHB_CMD(void);
sint16 AdbMxb4Data_GetCurvatureAngle(void);
boolean AdbMxb4Data_Get_GfhbDiag(void);
uint8 AdbMxb4Data_GetConfigVehicleMode(void);
teRte_EtatPrincipSEV AdbMxb4Data_GetVESMainState(void);
sint32 AdbMxb4Data_GetYawRate(void);
tieAdbHeadlampSide AdbMxb4Data_GetMountingSide(void);

void AdbMxb4Data_ConvertCamObj(tCamObjectTL* pCamObjectTL, uint8 ucObjIdx);
void AdbMxb4Data_ConvertCamObj_Percieve(tCamObjectTL* pCamObjectTL, uint8 ucObjIdx);
           
void AdbMxb4Data_ConvertAdbChannel(tAdbChannelX* pChannelXLeft, tAdbChannelX* pChannelXRight, tieAdbMode eAdbMode, uint8 channelIdx);

// ----------------------------------------------------------------------------
// AdbMxb4 - CodingData
// ----------------------------------------------------------------------------
LOCAL_INLINE boolean AdbMxb4Data_GetCodingValid(void)
{
  return AdbMxb4Data_boCodingValid;
}

LOCAL_INLINE uint8 Cod_aSampleTime(void)
{
	return 15;
}

// ----------------------------------------------------------------------------
LOCAL_INLINE sint16 Cod_aCamDistanceFilter_Indexed(sint32 _index)
{
  return ((sint16) AdbMxb4Data_pCodingArea->Adb.Filter.CamDistanceFilter[_index]);
}

// ----------------------------------------------------------------------------
LOCAL_INLINE sint16 Cod_aCamHorObjFilter_Indexed(sint32 _index)
{
  return ((sint16) AdbMxb4Data_pCodingArea->Adb.Filter.CamHorObjFilter[_index]);
}

// ----------------------------------------------------------------------------
LOCAL_INLINE sint16 Cod_aCamHorObjSpdFilterCfg_Indexed(sint32 _index)
{
  switch (_index) {
    case 0:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.Filter.CamHorObjSpdFilterTau);
    case 1:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.Filter.CamHorObjSpdFilterScrSlct);
    default:  return  ((sint16) 0);
  }
}

// ----------------------------------------------------------------------------
LOCAL_INLINE sint16 Cod_aCamVerPosFilter_Indexed(sint32 _index)
{
  return ((sint16) AdbMxb4Data_pCodingArea->Adb.Filter.CamVerPosFilter[_index]);
}

// ----------------------------------------------------------------------------
LOCAL_INLINE sint16 Cod_aHbpDynamicOffset_Indexed(sint32 _index1, sint32 _index2)
{
  switch (_index1) {
    case 0:
      switch (_index2) {
      case 0:   return -((sint16) AdbMxb4Data_pCodingArea->Adb.DynamicOffset.LeftSpeedLow);
      case 1:   return -((sint16) AdbMxb4Data_pCodingArea->Adb.DynamicOffset.LeftSpeedHigh);
      case 2:   return -((sint16) AdbMxb4Data_pCodingArea->Adb.DynamicOffset.LeftOffsetLow);
      case 3:   return -((sint16) AdbMxb4Data_pCodingArea->Adb.DynamicOffset.LeftOffsetHigh);
        default:  return  ((sint16) 0);
      }
    case 1:
      switch (_index2) {
        case 0:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.DynamicOffset.RightSpeedLow);
        case 1:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.DynamicOffset.RightSpeedHigh);
        case 2:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.DynamicOffset.RightOffsetLow);
        case 3:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.DynamicOffset.RightOffsetHigh);
        default:  return  ((sint16) 0);
      }
    default:
      return (sint16) 0;
  }
}

// ----------------------------------------------------------------------------
LOCAL_INLINE sint16 Cod_aHbpDynamicOffsetAlg_Indexed(sint32 _index)
{
  switch (_index) {
  case 0:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.DynOffsetAlg.Enable);
  case 1:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.DynOffsetAlg.SwSlow);
  case 2:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.DynOffsetAlg.SwFast);
    default:  return  ((sint16) 0);
  }
}

// ----------------------------------------------------------------------------
LOCAL_INLINE sint16 Cod_aHbpSafetyOffset_Indexed(sint32 _index1, sint32 _index2)
{
  switch (_index1) {
    case 0:
      switch (_index2) {
      case 0:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.SafetyOffset.LeftDistanceLow);
      case 1:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.SafetyOffset.LeftDistanceHigh);
      case 2:   return -((sint16) AdbMxb4Data_pCodingArea->Adb.SafetyOffset.LeftAngleLow);
      case 3:   return -((sint16) AdbMxb4Data_pCodingArea->Adb.SafetyOffset.LeftAngleHigh);
        default:  return  ((sint16) 0);
      }
    case 1:
      switch (_index2) {
      case 0:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.SafetyOffset.RightDistanceLow);
      case 1:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.SafetyOffset.RightDistanceHigh);
      case 2:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.SafetyOffset.RightAngleLow);
      case 3:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.SafetyOffset.RightAngleHigh);
        default:  return  ((sint16) 0);
      }
    default:
      return ((sint16) 0);
  }
}

// ----------------------------------------------------------------------------
LOCAL_INLINE sint16 Cod_aMxbDim_Indexed(sint32 _index1, sint32 _index2)
{
  switch (_index1) {
    case 0:
      switch (_index2) {
      case 0:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.DimmingTime.Up_Slow);
      case 1:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.DimmingTime.Up_Medium);
      case 2:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.DimmingTime.Up_Fast);
        default:  return  ((sint16) 0);
      }
    case 1:
      switch (_index2) {
      case 0:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.DimmingTime.Down_Slow);
      case 1:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.DimmingTime.Down_Medium);
      case 2:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.DimmingTime.Down_Fast);
        default:  return  ((sint16) 0);
      }
    default:
      return ((sint16) 0);
  }
}

// ----------------------------------------------------------------------------
LOCAL_INLINE sint16 Cod_aMxbHorAngleRateLim_Indexed(sint32 _index)
{
  switch (_index) {
    case 0:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.HorAngleRateLim.Mode);
    case 1:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.HorAngleRateLim.LimitSlow * 5); // [0.5deg/s] -> [0.1deg/s] 
    case 2:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.HorAngleRateLim.LimitFast * 5); // [0.5deg/s] -> [0.1deg/s] 
    case 3:   return -((sint16) AdbMxb4Data_pCodingArea->Adb.HorAngleRateLim.LHystLeft);
    case 4:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.HorAngleRateLim.LHystRight);
    case 5:   return -((sint16) AdbMxb4Data_pCodingArea->Adb.HorAngleRateLim.RHystLeft);
    case 6:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.HorAngleRateLim.RHystRight);
    case 7:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.HorAngleRateLim.LTrackLeft);
    case 8:   return -((sint16) AdbMxb4Data_pCodingArea->Adb.HorAngleRateLim.LTrackRight);
    case 9:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.HorAngleRateLim.RTrackLeft);
    case 10:  return -((sint16) AdbMxb4Data_pCodingArea->Adb.HorAngleRateLim.RTrackRight);
    case 11:  return  ((sint16) AdbMxb4Data_pCodingArea->Adb.HorAngleRateLim.TrackBeta);
    default:  return  ((sint16) 0);
  }
}

// ----------------------------------------------------------------------------
LOCAL_INLINE sint16 Cod_aMxbModuleOffset_Indexed(sint32 _index)
{
  switch (_index) {
    case 0:   return -((sint16) AdbMxb4Data_pCodingArea->Adb.ModuleOffset.LeftEdge);
    case 1:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.ModuleOffset.RightEdge);
    default:  return  ((sint16) 0);
  }
}

// ----------------------------------------------------------------------------
LOCAL_INLINE sint16 Cod_aMxbNoObjects_Indexed(sint32 _index)
{
  switch (_index) {
    case 0:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.NoObjectsBehaviour.Mode);
    case 1:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.NoObjectsBehaviour.TimeHoldLeadSide);  
    case 2:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.NoObjectsBehaviour.TimeHoldLeadCenter);
    default:  return  ((sint16) 0);
  }
}

// ----------------------------------------------------------------------------
LOCAL_INLINE sint16 Cod_aParallaxecorrection_Indexed(sint32 _index)
{
  switch (_index) {
    case 0:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.Parallaxe.DistCamHL_X);
    case 1:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.Parallaxe.DistY_LHL);
    case 2:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.Parallaxe.DistY_RHL);
    default:  return  ((sint16) 0);
  }
}

// ----------------------------------------------------------------------------
LOCAL_INLINE boolean Cod_aSignDimming(void)
{
  boolean bIsSignDimmingEnabled = TRUE;

  return bIsSignDimmingEnabled;
}

// ----------------------------------------------------------------------------
LOCAL_INLINE sint16 Cod_aSa2_MinSizeSign(void)
{
  return ((sint16) AdbMxb4Data_pCodingArea->Adb.SignDimming.MinSizeSign/10);
}

// ----------------------------------------------------------------------------
LOCAL_INLINE sint16 Cod_aSa2_MinSizeObj(void)
{
    return ((sint16)AdbMxb4Data_pCodingArea->Adb.SignDimming.MinObjSize);
}

// ----------------------------------------------------------------------------
LOCAL_INLINE sint16 Cod_aSa2_MxbNoObjectsAdvancedSign_Indexed(sint32 _index)
{
  switch (_index) {
    case 0:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.SignDimming.TimeHoldOnc);
    case 1:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.SignDimming.staticTimeHoldSign);
    case 2:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.SignDimming.EnablecalcSignShadowTime);
    case 3:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.SignDimming.EnableLinearInterpolation);
    case 4:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.SignDimming.EnableSimulateSignDistance);
    case 5:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.SignDimming.AssumedSimulateSignDist * 2); //[2m -> m]
    case 6:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.SignDimming.TimerMaxTime);
    default:  return  ((sint16) 0);
  }

}

// ----------------------------------------------------------------------------
LOCAL_INLINE boolean Cod_aSa2_ResetDimmingTimes(void)
{
  return TRUE; //TODO CodingData: AdbMxb4Data_pCodingArea->Adb.AdbResets.ResetDimmingTimes;
}

// ----------------------------------------------------------------------------
LOCAL_INLINE sint16 Cod_aSa2_SignDimmingPowerfactor_Indexed(sint32 _index)
{
  //TODO:
  switch (_index) {
    case 0:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.SignDimming.SignDimmingPowerfactorModus);
    case 1:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.SignDimming.SignDimmingStaticPowerfactor);
    case 2:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.SignDimming.DimmDownMaxPf);    // reverse gamma done in coding tool
    case 3:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.SignDimming.DimmUpMaxPf);      // reverse gamma done in coding tool
    case 4:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.SignDimming.DynamicMode_DimmTimeUp);   //[0.1s ] transformation to 10ms is done in the model.
    case 5:   return  ((sint16) AdbMxb4Data_pCodingArea->Adb.SignDimming.DynamicMode_DimmTimeDown); //[0.1s ] transformation to 10ms is done in the model.
    default:  return  ((sint16) 0);
  }
}

//TODO: fill in the coding Data
// ----------------------------------------------------------------------------
LOCAL_INLINE sint32 Cod_aSa2_CentralAreaAngle(void)
{
  return  ((sint32)AdbMxb4Data_pCodingArea->Adb.GlareFreeHB_CfgParams.ucGFHB_CURTAIN_CENTRAL_AREA_ANGLE);//[°]
}

// ----------------------------------------------------------------------------
LOCAL_INLINE sint32 Cod_aSa2_MWCurteinDimOnTime(void)
{
  return  ((sint32)(AdbMxb4Data_pCodingArea->Adb.GlareFreeHB_CfgParams.ucGFHB_MM_CURTAIN_DIM_ON_TIME*1000));//[ms]
}

// ----------------------------------------------------------------------------
LOCAL_INLINE sint32 Cod_aSa2_MWCurteinDimOffTime(void)
{
  return  ((sint32)(AdbMxb4Data_pCodingArea->Adb.GlareFreeHB_CfgParams.ucGFHB_MM_CURTAIN_DIM_OFF_TIME * 1000));//[ms]
}

// ----------------------------------------------------------------------------
LOCAL_INLINE sint32 Cod_aSa2_MWRestrictionAng(void)
{
  return  ((sint32)AdbMxb4Data_pCodingArea->Adb.GlareFreeHB_CfgParams.ucGFHB_MW_RESTRICTION_ANGLE << 16);//[°]
}

// ----------------------------------------------------------------------------
LOCAL_INLINE sint32 Cod_aSa2_MWRestrictionMax(void)
{
  return  ((sint32)(AdbMxb4Data_pCodingArea->Adb.GlareFreeHB_CfgParams.ucGFHB_MOTORWAY_MODE_RESTRICTION_LIMIT / 10)<< 16);//[°]
}

// ----------------------------------------------------------------------------
LOCAL_INLINE uint16 Sa2_HBBSpeedAct(void)
{
  return  ((uint16)AdbMxb4Data_pCodingArea->Adb.GlareFreeHB_CfgParams.ucHBB_SPEED_ACTIVATION); //[km/h]
}

// ----------------------------------------------------------------------------
LOCAL_INLINE uint16 Sa2_HBBSpeedDeact(void)
{
  return  ((uint16)AdbMxb4Data_pCodingArea->Adb.GlareFreeHB_CfgParams.ucHBB_SPEED_DEACTIVATION);//[km/h]
}

// ----------------------------------------------------------------------------
LOCAL_INLINE uint16 Cod_aSa2_GfhbObjectConfirmationTime(void)
{
  return  ((uint16)AdbMxb4Data_pCodingArea->Adb.GlareFreeHB_CfgParams.ucGFHB_OBJECT_CONFIRMATION_TIME);//[ms]
}

// ----------------------------------------------------------------------------
LOCAL_INLINE uint16 Cod_aGeomOffsetDistanceApplication(void)
{
  return  ((uint16)AdbMxb4Data_pCodingArea->Adb.DynamicOffset.unGEOM_OFFSET_DISTANCE_APPLICATION);//[m]
}

// ----------------------------------------------------------------------------
LOCAL_INLINE uint16 Cod_aGeometricalOffsetMaxAngle(void)
{
  return  ((uint16)AdbMxb4Data_pCodingArea->Adb.DynamicOffset.unGeometricalOffsetMaxAngle);//[0.1 Deg]
}

// ----------------------------------------------------------------------------
LOCAL_INLINE uint8 Cod_aGeometricalOffsetMaxValue(void)
{
  return  ((uint8)AdbMxb4Data_pCodingArea->Adb.DynamicOffset.ucGeometricalOffsetMaxValue);//[0.1 Deg]
}

// ----------------------------------------------------------------------------
LOCAL_INLINE uint16 Cod_aGeometricalOffsetMinAngle(void)
{
  return  ((uint16)AdbMxb4Data_pCodingArea->Adb.DynamicOffset.unGeometricalOffsetMinAngle);//[0.1 Deg]
}

// ----------------------------------------------------------------------------
LOCAL_INLINE uint8 Cod_aGeometricalOffsetMinValue(void)
{
  return  ((uint8)AdbMxb4Data_pCodingArea->Adb.DynamicOffset.ucGeometricalOffsetMinValue);//[0.1 Deg]
}

// ----------------------------------------------------------------------------
LOCAL_INLINE uint8 Cod_aSa2_DrivingModeMaxSpeed(void)
{
  return  ((uint8)AdbMxb4Data_pCodingArea->Adb.Modus.ucDrivingModeMaxSpeed);//[km/h]
}

// ----------------------------------------------------------------------------
LOCAL_INLINE uint8 Cod_aSa2_DrivingModeMinSpeed(void)
{
  return  ((uint8)AdbMxb4Data_pCodingArea->Adb.Modus.ucDrivingModeMinSpeed);//[km/h]
}

// ----------------------------------------------------------------------------
LOCAL_INLINE sint16 Cod_aSa2_SelfGlaringMin(void)
{
  return ((sint16)AdbMxb4Data_pCodingArea->Adb.CamData.SelfGlaringLimit);//[%]
}

LOCAL_INLINE uint16 Cod_aparAzimuthWeight(void)
{
  return ((uint16)AdbMxb4Data_pCodingArea->Adb.CalcHoldTime.AzimuthWeight);
}

LOCAL_INLINE uint16 Cod_aparSpeedWeight(void)
{
  return ((uint16)AdbMxb4Data_pCodingArea->Adb.CalcHoldTime.SpeedWeight);
}

LOCAL_INLINE uint16 Cod_aparMaxTime(void)
{
  return ((uint16)AdbMxb4Data_pCodingArea->Adb.CalcHoldTime.MaxTime);
}


//Act/deactivation of features for GFHB
// ----------------------------------------------------------------------------
LOCAL_INLINE uint16 Cod_aSa2_EnableTSAG(void)
{
    return ((uint16)AdbMxb4Data_pCodingArea->Sys.Configurability.ucTSAG_Enable);
}

LOCAL_INLINE uint16 Cod_aSa2_EnableMotorwayMode(void)
{
    return ((uint16)AdbMxb4Data_pCodingArea->Sys.Configurability.ucMotorway_Enable);
}

LOCAL_INLINE uint16 Cod_aSa2_EnableHBB(void)
{
    return ((uint16)AdbMxb4Data_pCodingArea->Sys.Configurability.ucHBB_Enable);
}

LOCAL_INLINE uint16 Cod_aSa2_EnableGFHB(void)
{
    return ((uint16)AdbMxb4Data_pCodingArea->Sys.Configurability.ucGFHB_Enable);
}

LOCAL_INLINE uint16 Cod_aSa2_EnableCurtainEffect(void)
{
    return ((uint16)AdbMxb4Data_pCodingArea->Sys.Configurability.ucCurtainEffect_Enable);
}
// ----------------------------------------------------------------------------

LOCAL_INLINE uint8 Cod_aSchedulerDelay(void)
{
    return 20; //4 times 5 ms runnable
}




#endif // __ADB_MXB3DATA_H__
