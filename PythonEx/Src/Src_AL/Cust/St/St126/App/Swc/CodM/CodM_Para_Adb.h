#ifndef __CODM_PARA_ADB_H__
#define __CODM_PARA_ADB_H__

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
///  \file   CodM_Para_Adb.h
///
///  \brief  Content of datagroup "Adb"
///
///  \descr  Source: PS60_R2.xlsm. 
///         
///          For further details see coding parameter
///
///  \author Cretu Vlad (F78845C)
///          mailTo:vladut-ioan.cretu[at]marelli.com
///
///  \date   22.06.2020, 14:06:20
//-----------------------------------------------------------------------------

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include <Std_Types.h>

//=============================================================================
// Definitions
//=============================================================================
#define CODM_PARA_ADB_DUMMY_SIZE 10u
#define CODM_PAR_ADB_CAMERA_SIZE 5u
//=============================================================================
// Types
//=============================================================================

typedef struct 
{
  uint8   Coding;       // [1]
  uint8   Enable;       // [1]
  uint8   ucDrivingModeMaxSpeed; //Coding ADB functionality active or not
  uint8   ucDrivingModeMinSpeed; //ADB Functionality active or not
} 
tNvmPara_AdbModus;

typedef struct  
{
  uint8   DistCamHL_X;  // [cm]
  uint8   DistY_LHL;    // [cm]
  uint8   DistY_RHL;    // [cm]
  uint8   Dummy;        // [1]
} 
tNvmPara_AdbParallaxe;

typedef struct
{
  uint8   Up_Slow;      // [10ms]
  uint8   Up_Medium;    // [10ms]
  uint8   Up_Fast;      // [10ms]
  uint8   Down_Slow;    // [10ms]
  uint8   Down_Medium;  // [10ms]
  uint8   Down_Fast;    // [10ms]
} tNvmPara_AdbDimmingTime;

typedef struct  
{
  uint8   LeftDistanceLow;    // [2m]
  uint8   LeftDistanceHigh;   // [2m]
  uint8   LeftAngleLow;       // [-0.1°]
  uint8   LeftAngleHigh;      // [-0.1°]
  uint8   RightDistanceLow;   // [2m]
  uint8   RightDistanceHigh;  // [2m]
  uint8   RightAngleLow;      // [0.1°]
  uint8   RightAngleHigh;     // [0.1°]
} 
tNvmPara_AdbSafetyOffset;

typedef struct 
{
  uint8   Dummy[CODM_PARA_ADB_DUMMY_SIZE];                  // [1]
} 
tNvmPara_AdbHbpParameter;


typedef struct
{
  uint16  CamHorObjSpdFilterTau;      // [2^-10]
  uint8   CamHorObjSpdFilterScrSlct;  // [1]
  uint8   CamHorObjFilter[CODM_PAR_ADB_CAMERA_SIZE];         // [%]
  uint8   CamVerPosFilter[CODM_PAR_ADB_CAMERA_SIZE];         // [%]
  uint8   CamDistanceFilter[CODM_PAR_ADB_CAMERA_SIZE];       // [%]
} 
tNvmPara_AdbFilter;

typedef struct
{
  uint8   Mode;                       // [1]
  uint8   TimeHoldLeadSide;           // [0.1s]
  uint8   TimeHoldLeadCenter;         // [0.1s]
  uint8   Dummy;                      // [1]
} 
tNvmPara_AdbNoObjectsBehaviour;

typedef struct  
{
  uint8   LeftEdge;                   // [0.1°]
  uint8   RightEdge;                  // [0.1°]
} 
tNvmPara_AdbModuleOffset;

typedef struct 
{
  sint16 nLeftVerticalOffset;         // [0.02°]
  sint16 nRightVerticalOffset;        // [0.02°]
}
tNvmPara_Adb_AdbVerticalAlignment;


typedef struct 
{
  uint8   Mode;                       // [1]
  uint8   BorTrOut;                   // [1]
  uint8   LimitSlow;                  // [0.5°/s] 
  uint8   LimitFast;                  // [0.5°/s] 
  uint16  TrackBeta;                  // [2^-10]
  uint8   LTrackLeft;                 // [0.1°]
  uint8   LTrackRight;                // [-0.1°]
  uint8   RTrackLeft;                 // [0.1°]
  uint8   RTrackRight;                // [-0.1°]
  uint8   LHystLeft;                  // [-0.1°]
  uint8   LHystRight;                 // [0.1°]
  uint8   RHystLeft;                  // [-0.1°]
  uint8   RHystRight;                 // [0.1°]
} 
tNvmPara_AdbHorAngleRateLim;

typedef struct
{
  uint8   LeftSpeedLow;               // [-0.1°/s]
  uint8   LeftSpeedMid;              // [-0.1°/s]
  uint8   LeftSpeedHigh;              // [-0.1°/s]
  uint8   LeftOffsetLow;              // [-0.1°]
  uint8   LeftOffsetMid;             // [-0.1°]
  uint8   LeftOffsetHigh;             // [-0.1°]
  uint8   RightSpeedLow;              // [0.1°/s]
  uint8   RightSpeedMid;             // [0.1°/s]
  uint8   RightSpeedHigh;             // [0.1°/s]
  uint8   RightOffsetLow;             // [0.1°]
  uint8   RightOffsetMid;            // [0.1°]
  uint8   RightOffsetHigh;            // [0.1°]
  uint16  unGeometricalOffsetMinAngle;         // Minimum Angle of the Object for the additional // Geometrical offset.
  uint16  unGeometricalOffsetMaxAngle;         // Maximum Angle of the Object for the additional // Geometrical offset.
  uint8   ucGeometricalOffsetMinValue;         // Minimum additional offset value for the geometrical // offset.
  uint8   ucGeometricalOffsetMaxValue;         // Maximum additional offset value for the geometrical // offset.
  uint16  unGEOM_OFFSET_DISTANCE_APPLICATION;  // Distance where below this one the geometrical offset will be applied
} 
tNvmPara_AdbDynamicOffset;

typedef struct 
{
  uint8   Enable;                     // [1]
  uint8   SwSlow;                     // [0.1s]
  uint8   SwFast;                     // [0.1s]
  uint8   Dummy;                      // [1]
} 
tNvmPara_AdbDynOffsetAlg;

typedef struct 
{
  uint8   SelfGlaringLimit;           // [%]
  uint8   EnableAmbientLight;         // [1]
} 
tNvmPara_AdbCamData;

typedef struct 
{
  uint8   ResetDimmingTimes;            // [1]
  uint8   Dummy;                        // [1]
}
tNvmPara_AdbReset;

typedef struct 
{
  uint8   EnableSignDimming;            // [1]
  uint8   MinSizeSign;                  // [0.1°]
  uint8   TimeHoldOnc;                  // [0.1s]
  uint8   staticTimeHoldSign;           // [0.1s]
  uint8   EnablecalcSignShadowTime;     // [1]
  uint8   EnableLinearInterpolation;    // [1]
  uint8   EnableSimulateSignDistance;   // [1]
  uint8   AssumedSimulateSignDist;      // [2m]
  uint8   TimerMaxTime;                 // [s]
  uint8   SignDimmingPowerfactorModus;  // [1]
  uint8   SignDimmingStaticPowerfactor; // [%]
  uint8   DimmDownMaxPf;                // [%]
  uint8   DimmUpMaxPf;                  // [%]
  uint8   DynamicMode_DimmTimeUp;       // [0.1s]
  uint8   DynamicMode_DimmTimeDown;     // [0.1s]
  uint8   MinObjSize;                   // [1]
} 
tNvmPara_AdbSignDimming;

typedef struct
{
  uint8   AHB_OncomingDebounceTime;       // [0.1s]
  uint8   AHB_PreceedingDebounceTime;     // [0.1s]
  uint8   AHB_DefaultDebounceTime;        // [0.1s]
  uint8   AHB_DrvPastDebounceTime;        // [0.1s]
  uint8   AHB_OvertakingDebounceTime;     // [0.1s]
  uint8   AHB_FarTrafficDistDebounceTime; // [0.1s]
  uint8   AHB_DrvPastOvertakingDistance;  // [2m]
  uint8   AHB_FarTrafficDistance;         // [2m]
  uint8   AHB_HBOffDebounceTime;          // [0.1s]
  uint8   Dummy;                          // [1]
} 
tNvmPara_AhbTimings;

typedef struct
{
  uint8 ucreserviert1[6]; //not used on DPE
}
tNvmPara_Adb_PixelShadowFading;

typedef struct
{
  uint8 ucEnable; 
  uint8 ucRreserviert1;
}
tNvmPara_Adb_DynamicOffsetYaw;

typedef struct
{
  sint16 ucreserviert1[16]; //not used on DPE
}
tNvmPara_Adb_MotorwayLookUpTable;

typedef struct
{
  uint16 RampTimeUpDownMotorwayFade;
  uint16 RampTimeUpDownMotorwayReset;
}
tNvmPara_Adb_MotorwayRateLim;

typedef struct
{
  uint16 deltaLow;
  uint16 deltaHigh;
  uint16 dimSlow;
  uint16 dimFast;
}
tNvmPara_Adb_DynamicDimming;

typedef struct
{
  uint16 enable;
}
tNvmPara_Adb_EnDynamicDimming;

typedef struct
{
  uint16 AzimuthWeight; // Influence of azimuth rate on calc hold time value
  uint16 SpeedWeight; // Influence of distance/speed on calc hold time value
  uint16 AzimuthMinDynamic; // Lowest azimuth dynamic in calc hold time calculation (0 is not allowed)
  uint16 MaxTime; // Max delay from calc hold time + GFHB_DELAY_DISAPPEARANCE_ONCOMING/PRECEIDING
}
tNvmPara_Adb_CalcHoldTime;

typedef struct
{
  sint16 ucreserviert1[12];
}
tNvmPara_Adb_MultipleOncoming;

typedef struct
{
  uint8 ucGFHB_CURTAIN_CENTRAL_AREA_ANGLE; // Angular area, which defines the central area
                                          // for traffic objects, to be taken into account
                                          // for a movement direction outside to inside
                                          // during activation
  uint8 ucGFHB_MW_RESTRICTION_ANGLE; //Restriction angle for the motorway beam
  uint16 ucGFHB_OBJECT_CONFIRMATION_TIME; // Time to confirm the value “Invalid” or “Unavailable”
                                          // regarding all flows of traffic and strong
                                          // reflector objects coming from Driving Assistance
                                          // Subsystem
  uint16 ucGFHB_MM_CURTAIN_DIM_OFF_TIME; // Dim on time for the single segments, which
                                          // are affected by a curtain movement for Motorway
                                          // mode activation
  uint16 ucGFHB_MM_CURTAIN_DIM_ON_TIME; // Dim on time for the single segments, which
                                          // are affected by a curtain movement for Motorway
                                          // mode deactivation
  uint8 ucMW_RATIO; // Defines the ratio of intensity applied to
                                          // the segments by the Motorway Restriction
                                          // Mode
  sint8 ucGFHB_MOTORWAY_MODE_RESTRICTION_LIMIT; // limits the restriction in right curves for
                                          // LHD and left curves for RHD negative values
                                          // to the left, positive values to the right
  uint8 ucHBB_SPEED_ACTIVATION; //Activation speed for HBB.
  uint8 ucHBB_SPEED_DEACTIVATION; //Deactivation speed for HBB.
  uint8 ucreserviert1[16]; //not used on DPE
}
tNvmPara_Adb_GlareFreeHB_CfgParams;


typedef struct 
{
  tNvmPara_AdbModus                  Modus;                //   2 bytes
  tNvmPara_AdbParallaxe              Parallaxe;            //   4 bytes
  tNvmPara_AdbDimmingTime            DimmingTime;          //   6 bytes
  tNvmPara_AdbSafetyOffset           SafetyOffset;         //   8 bytes
  tNvmPara_AdbHbpParameter           HbpParameter;         //  10 bytes
  tNvmPara_AdbFilter                 Filter;               //  18 bytes
  tNvmPara_AdbNoObjectsBehaviour     NoObjectsBehaviour;   //   4 bytes
  tNvmPara_AdbModuleOffset           ModuleOffset;         //   2 bytes
  tNvmPara_Adb_AdbVerticalAlignment  VerticalAlignment;    //   4 bytes
  tNvmPara_AdbHorAngleRateLim        HorAngleRateLim;      //  14 bytes
  tNvmPara_AdbDynamicOffset          DynamicOffset;        //   8 bytes
  tNvmPara_AdbDynOffsetAlg           DynOffsetAlg;         //   4 bytes
  tNvmPara_AdbCamData                CamData;              //   2 bytes
  tNvmPara_AdbReset                  AdbResets;            //   2 bytes
  tNvmPara_AdbSignDimming            SignDimming;          //  16 bytes
  tNvmPara_Adb_PixelShadowFading     PixelShadowFading;    //   8 bytes
  tNvmPara_Adb_DynamicOffsetYaw      DynamicOffsetYaw;     //   1 bytes
  tNvmPara_Adb_MotorwayLookUpTable   MotorwayLookUpTable;  //  32 bytes
  tNvmPara_Adb_MotorwayRateLim       MotorwayRateLim;      //   4 bytes
  tNvmPara_Adb_EnDynamicDimming      EnableDynamicDimming; //   1 bytes
  tNvmPara_Adb_DynamicDimming        DynamicDimming;       //   8 bytes
  tNvmPara_Adb_CalcHoldTime          CalcHoldTime;         //   8 bytes
  tNvmPara_Adb_MultipleOncoming      MultipleOncoming;     //  16 bytes
  tNvmPara_Adb_GlareFreeHB_CfgParams GlareFreeHB_CfgParams;
}                                                          // ---------
tNvmPara_AdbBlock;                                         // 205 bytes

#endif // __CODM_PARA_ADB_H__

// EOF
