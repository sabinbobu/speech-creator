#ifndef __CODM_PARA_AFSM_H__
#define __CODM_PARA_AFSM_H__

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
///  \file   CodM_Para_AFSM.h
///
///  \brief  Content of datagroup "AFSM"
///
///  \descr  Source: PS60_R2.xlsm. 
///          Version TBD 
///          For further details see coding parameter
///
///  \author This file is auto generated - please do not edit
///
///  \date   13.02.2020, 14:51:05
//-----------------------------------------------------------------------------
#define SIZE_ARR_CURVE_RADIUS       2u
#define SIZE_ARR_SBL_SLIGHT        13u
#define SIZE_ARR_TI_POS_DRL         3u
#define SIZE_ARR_SBL_CFG            4u

typedef struct
{
  // Used for calculation of weighting factor
  uint16 aunV_Min[SIZE_ARR_CURVE_RADIUS];
  uint16 aunV_Max[SIZE_ARR_CURVE_RADIUS];
  uint16 aunWf_Min[SIZE_ARR_CURVE_RADIUS];
  uint16 aunWf_Max[SIZE_ARR_CURVE_RADIUS];
  uint16 unFilterTimePrio;
  uint16 unFilterTracking; 
  uint16 unFilterTrackingTau;
  uint16 unFilterTrackingOpt;
  uint16 unFilterTrackingRange;
  uint16 unMixerV0;
  uint16 unCurvatureFactor;
  uint16 unRadianFactor;
}
tNvmPara_AFSM_AfsCurveRadius;

typedef struct
{
  // auto hb shall be active when this speed is reach
  uint16 unHB_AUTO_INSTANT; 
  // auto hb shall be active when this speed is reach and before auto hb was set
  uint16 unHB_AUTO_LATCH; 
}
tNvmPara_AFSM_AfsHighBeam;

typedef struct
{
  // PWM StaticBending Light (CL)
  uint16 aunPwm_SBL[SIZE_ARR_SBL_SLIGHT];
  // PWM S-Light
  uint16 aunPwm_SLgt[SIZE_ARR_SBL_SLIGHT];
  // Dim Up StaticBending (CL)
  uint16 aunDimUp_CL[SIZE_ARR_SBL_SLIGHT];
  // Dim Up S-Light
  uint16 aunDimUp_SLgt[SIZE_ARR_SBL_SLIGHT];
  // Dim Down StaticBending Light (CL)
  uint16 aunDimDw_CL[SIZE_ARR_SBL_SLIGHT];
  // Dim Down S-Light
  uint16 aunDimDw_SLgt[SIZE_ARR_SBL_SLIGHT];
  // PWM TI, POS/DRL
  uint16 aunPwm_Ti_Pos_Drl[SIZE_ARR_TI_POS_DRL];
  // Dim Down TI, POS/DRL
  uint16 aunDimDw_Ti_Pos_Drl[SIZE_ARR_TI_POS_DRL];
  // Dim Up TI, POS/DRL
  uint16 aunDimUp_Ti_Pos_Drl[SIZE_ARR_TI_POS_DRL];
}
tNvmPara_AFSM_AfsLightFunctionManagerSBL;

typedef struct
{
  // Timer start after TI falling edge - used to activate DRL/POS in case we dont have any TI rising edge during TI_TIMER_AFTER_FALLING_EDGE ms period
  uint16 unTI_TIMER_AFTER_FALLING_EDGE; 
}
tNvmPara_AFSM_AfsLightFunctionScenario;

typedef struct
{
  // town to country instant
  uint16 unAfsLmt70KMh;
  // town to country in AfsLmtTWN_55kmh_TIMER   
  uint16 unAfsLmt55KMh;
  // country to hb/gfhb/motorway instant
  uint16 unAfsLmt135KMh; 
  // country to town in AfsLmtCTRY_41kmhExit_TIMER
  uint16 unAfsLmt41KMh;
  // hb/gfhb/motorway to country in AfsLmtMTRWY_85kmh_TIMER    
  uint16 unAfsLmt85KMh;
  // country to hb/gfhb/motorway in AfsLmtCTRY_120kmh_TIMER
  uint16 unAfsLmt120KMh;
  // country to hb/gfhb/motorway in AfsLmtCTRY_105kmh_TIMER   
  uint16 unAfsLmt105KMh;
  // country to hb/gfhb/motorway in AfsLmtCTRY_105kmhLatch_TIMER
  uint16 unAfsLmt105KMhLatch; 
  // country to hb / gfhb / motorway curve radius parameter(threshold)
  uint16 unAfsLmt425m;
  // town to country timer
  uint16 unAfsLmtTWN_55kmh_TIMER; 
  // country to town timer 
  uint16 unAfsLmtCTRY_41kmhExit_TIMER; 
  // country to hb/gfhb/motorway timer for AfsLmt120KMh
  uint16 unAfsLmtCTRY_120kmh_TIMER;
  // country to hb/gfhb/motorway timer for AfsLmt105KMh
  uint16 unAfsLmtCTRY_105kmh_TIMER;
  // country to hb/gfhb/motorway latch timer for AfsLmt105KMhLatch
  uint16 unAfsLmtCTRY_105kmhLatch_TIMER; 
  // hb / gfhb / motorway to country timer
  uint16 unAfsLmtMTRWY_85kmh_TIMER;
  // country to hb/gfhb/motorway latch help timer for AfsLmt105KMhLatch
  uint16 unAfsLmtMTRWY_StayActive_105kmh_TIMER; 
}
tNvmPara_AFSM_AfsLightModeTransition;

typedef struct
{
  // AfsMnvr Instantly  
  uint16 unAfsMnvr_7KMh; 
  // Afs Manuvering timer
  uint16 unAFSMNVR_MNVR_TIMER; 
}
tNvmPara_AFSM_AfsManeuvering;

typedef struct
{
  // used for sbl activation via curve based on speed
  uint16 unTI_PERIOD;
  uint16 aunAFS_SBL_V_MIN[SIZE_ARR_SBL_CFG];
  uint16 aunAFS_SBL_V_HYS[SIZE_ARR_SBL_CFG];
  uint16 aunAFS_SBL_V_MAX[SIZE_ARR_SBL_CFG];
  uint16 aunAFS_SBL_RADIUS_V1[SIZE_ARR_SBL_CFG];
  uint16 aunAFS_SBL_RADIUS_V2[SIZE_ARR_SBL_CFG];
}
tNvmPara_AFSM_AfsStaticBendingLight;

typedef struct
{ 
  // used for aiming mode activation
  uint16 unAfsAiming_Input_3KMh;
  uint16 unAfsAiming_Exit_3KMh;
  uint16 unAfsAiming_AimingModeTimer;
  uint16 unAfsAimingMode_FeedbackCounter;
  uint16 unAfsAimingMode_FeedbackFreq;
  uint16 unAfsAimingMode_AimingProcedure;
  uint16 unAfsAimingMode_LbMaintainTime;
  uint16 unAfsAimingMode_DebounceTime;
}
tNvmPara_AFSM_AfsAimingMode;

typedef struct
{ 
  // used for adverse weather mode activation
  uint16 unAfsAdverseWeather_ActivationSpeed;
  uint16 unAfsAdverseWeather_DeactivationSpeed;
  uint16 unAfsAdverseWeather_ActivationTimer;
  uint16 unAfsAdverseWeather_DeactivationTimer;
}
tNvmPara_AFSM_AfsAdverseWeather;

typedef struct
{
  // used for adverse weather mode activation
  uint16 unAfsTouristMode_PixelDimTime;
  uint16 unAfsTouristMode_WaitParameter;
  uint16 unAfsTouristMode_EnableAfs;
  uint16 unAfsTouristMode_AngularSpeed;
}
tNvmPara_AFSM_AfsTouristMode;


typedef struct 
{
  tNvmPara_AFSM_AfsCurveRadius             AfsCurveRadius;
  tNvmPara_AFSM_AfsHighBeam                AfsHighBeam;
  tNvmPara_AFSM_AfsLightFunctionManagerSBL AfsLightFunctionManagerSBL;
  tNvmPara_AFSM_AfsLightFunctionScenario   AfsLightFunctionScenario;
  tNvmPara_AFSM_AfsLightModeTransition     AfsLightModeTransition;
  tNvmPara_AFSM_AfsManeuvering             AfsManeuvering;
  tNvmPara_AFSM_AfsStaticBendingLight      AfsStaticBendingLight;
  tNvmPara_AFSM_AfsAimingMode              AfsAimingMode;
  tNvmPara_AFSM_AfsAdverseWeather          AfsAdverseWeather;
  tNvmPara_AFSM_AfsTouristMode             AfsTouristMode;

} tNvmPara_AFSMBlock;

#endif // __CODM_PARA_AFSM_H__

// EOF
