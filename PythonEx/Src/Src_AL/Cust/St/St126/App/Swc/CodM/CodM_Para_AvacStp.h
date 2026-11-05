#ifndef  __CODM_PARA__AvacStp_H
#define  __CODM_PARA__AvacStp_H

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
///  \file   CodM_Para_AvacStp.h
///
///  \brief  Content of datagroup "AvacStp"
///
///  \descr  Source: PS60_R2.xlsm. 
///         
///          For further details see coding parameter
///
///  \author Cretu Vlad (F78845C)
///          mailTo:vladut-ioan.cretu[at]marelli.com
///
///  \date   22.06.2019, 14:06:20
//-----------------------------------------------------------------------------
//=============================================================================
// Includes
//=============================================================================
#include <Std_Types.h>
//=============================================================================
// Definitions
//=============================================================================
#define CODM_PARA_RSV_SIZE            2u
//=============================================================================
// Types
//=============================================================================
typedef struct
{
  uint16 unWHEELBASE;
  uint16 unREFERENCING_SPEED_MAX;
  // a DBL and ADL referencing
  sint16 snLOW_STOP_POSITION;
  // referencing
  uint8  ucDPF;
  uint8  ucDPR;
  uint16 unR1;
  uint16 unR2;
  uint16 unSTT_TRANSITION_DELAY;
  uint16 unVccx_Min;
  uint16 unVccx_Max;
  sint16 snAngleMin;
  sint16 snAngleMax;
  uint8  ucDutyMinSens;
  uint8  ucDutyMaxSens;
  sint16 snSensorSlopeFront;
  sint16 snSensorSlopeRear;
  uint16 BhsPlausVehSpeed; //Plausibility check speed
  uint8  SensorOutRangeTime; //Sensor time to detect an error
  uint8  SensorFailureRecoveryTime; //Sensor Time to recover from an error
}
tNvmPara_AvacStp_PitchData;

typedef struct
{
  uint8  ucASL_FROZEN_VEH_SPEED; // Vehicle speed threshold above which the automatic
                                           // static levelling is frozen
  uint8  ucASL_HIGH_FROZEN_VEH_SPEED; // Vehicle speed threshold above which the automatic
                                           // static levelling is frozen
  uint8  ucVEHICLE_ATTITUDE_ADJUSTEMENT_THRESHOLD_STANDSTILL; // Threshold variation of the vehicle attitude
                                           // to adjust the aiming of the low beam lamps
                                           // when the vehicle is standstill (minimum of
                                           // attitude changed)
  uint8  ucVEHICLE_ATTITUDE_ADJUSTEMENT_THRESHOLD_STANDSTILL_HS; // Threshold variation of the vehicle attitude
                                           // in High speed mode to adjust the aiming of
                                           // the low beam lamps when the vehicle is standstill
                                           // (minimum of attitude changed)
  uint8  ucVEHICLE_ATTITUDE_ADJUSTEMENT_THRESHOLD_MOTION; // Threshold variation of the vehicle attitude
                                          // to adjust the aiming of the low beam lamps
                                          // when the vehicle is in motion (minimum of
                                          // attitude changed)
  uint8  ucASL_MOTION_DELAY; // Timer to consider the speed to be  stable
  uint8  ucreserviert1;
  sint8  scMin_Vehicle_Attitude; // ASL negative headlamp saturation limit :
                                          // 
                                          // Minimum limit of the aiming angle for the
                                          // function
  uint8  ucAsl_Enable;           // ASL feature present
  sint8  scMax_Vehicle_Attitude; // ASL positive headlamp saturation limit :
                                          // 
                                          // Maximum limit of the aiming angle for the
                                          //  function
  sint16 snMin_ASL_Adjust_Left; // Minimum limit of the aiming angle for the
                                          // ASL function
  sint16 snMax_ASL_Adjust_Left; // Maximun limit of the aiming angle for the
                                          // ASL function
  uint8  ucreserviert2;
  sint8  scSafety_Position_Left; // Offset of the aiming in case of failure to
                                          // avoid glaring
  sint16 snMin_ASL_Adjust_Right; // Minimum limit of the aiming angle for the
                                          // ASL function
  sint16 snMax_ASL_Adjust_Right; // Maximun limit of the aiming angle for the
                                          // ASL function
  uint8  ucreserviert3;
  sint8  scSafety_Position_Right; // Offset of the aiming in case of failure to
                                          // avoid glaring
}
tNvmPara_AvacStp_DCMotorData;


typedef struct
{
  uint8 ucAvacStp_Enable : 1; //1 = AvacStp-Motor active
                                          // 0 = AvacStp-Motor deactived. There is no energization
                                          // of the stepper motor.
  uint8 ucreserviert2 : 1;
  uint8 ucAvacStp_Step_mode : 2; //0 = 1/2 Half-step mode
                                          //1 = 1/4 Reserved
                                          //2 = 1/8 Micro-step mode
                                          //3 = 1/16 Reserved
  uint8 ucAvacStp_OL_Errorcount_Threshold : 4; // Number of the additional OpenLoad/ShortedCoil-Measurements
                                          // until failure input.
  uint8 ucAvacStp_TestActive : 1; //0 = Normal operation
                                          // 1 = Always active (see parameter AvacStp_TEST_DL_PERIODE
                                          // and AvacStp_TEST_DL_WEG)
  uint8 ucAvacStp_Test_NoError : 1; //0 = Normal operation
                                          //1 = Error input memory lock
  uint8 ucAvacStp_Test_IgnoreOL : 1; //0 = Normal operation
                                          // 1 = Open Load/ShortedCoil ignore driver error
  uint8 ucreserviert20 : 5;
  uint16 ucAvacStp_Test_AdjRange; //Adjustment range for test endurance.
  uint8 ucAvacStp_Test_AdjPeriod; // Period duration for the test endurance. During
                                          // the test endurance the AvacStp target position
                                          // is set to +12 HS for 50% of AvacStp_TEST_DL_PERIODE,
                                          // while the other 50% is set to the value AvacStp_TEST_DL_WEG
                                          // + 12 HS
  uint8 ucAvacStp_Movement_Threshold_HS; //Minimum limit to start an adjustment.
  uint8 ucAvacStp_PrewarningPos : 1; // Stopping of the motor due to Start/Stop warning
                                          // signal:
                                          //0 = no, 1 = yes
  uint8 ucAvacStp_NewRef_ForWarning : 1; // Performing a re-referencing for steploss
                                          // although Start/Stop warning signal:     
                                          //       0 = no, 1 = yes
  uint8 ucAvacStp_PrewarningSource : 2; //Source of Start/Stop warning signal
                                          //0 = No warning signal
                                          //1 = ??
                                          //2 = ??
                                          //3 = ??
  uint8 ucAvacStp_Fault_Response_VoltErr : 1; // AvacStp response in AHL Position Sensor-Supply
                                          // Voltage-Error:
                                          //0 = No AvacStp reduction
                                          //1 = AvacStp reduction
  uint8 ucAvacStp_Fault_Response_RefErr : 1; // AvacStp response at AHL Referencing-Error (Position
                                          // sensor Edge not found):
                                          //0 = No AvacStp reduction
                                          //1 = AvacStp reduction
  uint8 ucAvacStp_Fault_Response_PosErr : 1; // AvacStp response at AHL Position(sensor)-Error:
                                          //0 = No AvacStp reduction
                                          //1 = AvacStp reduction
  uint8 ucAvacStp_Fault_Response_ThermErr : 1; // AvacStp response at AHL StepperMotor(driver)-Error
                                          // (thermal/electric):
                                          //0 = No AvacStp reduction
                                          //1 = AvacStp reduction
  uint8 ucAvacStp_Autoreferencing_Delay; // Time offset ECU referencing left/right for
                                          // the car
  uint8 ucAvacStp_RedOffset;                //Offset at AvacStp reduction
  uint8 ucAvacStp_Levelling_Stepper_Failure_Report_Time;
  uint8 ucreserviert23[CODM_PARA_RSV_SIZE];
}
tNvmPara_AvacStp_StepperMotor_OperationMode;

#define NVMPARA_AVACSTP_STEPPERMOTOR_OPERATIONMODE_INIT      \
{                                                            \
  1u,                /* AvacStp_Enable*/                     \
  0u,                /* reserviert1*/                        \
  2u,                /* AvacStp_Step_mode*/                  \
  1u,                /* AvacStp_OL_Errorcount_Threshold*/    \
  0u,                /* AvacStp_TestActive*/                 \
  0u,                /* AvacStp_Test_NoError*/               \
  0u,                /* AvacStp_Test_IgnoreOL*/              \
  0u,                /* reserviert1*/                        \
  200u,              /* AvacStp_Test_AdjRange*/              \
  20u,               /* AvacStp_Test_AdjPeriod*/             \
  0u,                /* AvacStp_Movement_Threshold_HS*/      \
  0u,                /* AvacStp_PrewarningPos*/              \
  0u,                /* AvacStp_NewRef_ForWarning*/          \
  0u,                /* AvacStp_PrewarningSource*/           \
  0u,                /* AvacStp_Fault_Response_VoltErr*/     \
  0u,                /* AvacStp_Fault_Response_RefErr*/      \
  0u,                /* AvacStp_Fault_Response_PosErr*/      \
  0u,                /* AvacStp_Fault_Response_ThermErr*/    \
  30u,               /* AvacStp_Autoreferencing_Delay*/      \
  0u,                /* AvacStp_RedOffset*/                  \
  50u,               /*AvacStp_Levelling_Failure_Report*/    \
  {0u,0u}            /* reserviert1*/                        \
}

typedef struct
{
  // Hold current in the low temperature mode
  uint8  ucAvacStp_Hold_Current_LT;
  // Hold current in the normal temperature mode
  uint8  ucAvacStp_Hold_Current_NT;
  // Hold current in the high temperature mode
  uint8  ucAvacStp_Hold_Current_HT;
  // Operation current at low temperature mode
  uint8  ucAvacStp_Run_Current_LT;
  // Operation current at normal temperature mode
  uint8  ucAvacStp_Run_Current_NT;
  // Operation current at high temperature mode
  uint8  ucAvacStp_Run_Current_HT;
  // Operation current for the final phase of the referencing process, in which the motor moves the first 12 half-steps from the hard stop away, at low temperature mode
  uint8  ucAvacStp_Ref_Current_LT;
  // Operation current for the final phase of the referencing process, in which the motor moves the first 12 half - steps from the hard stop away, at normal temperature mode
  uint8  ucAvacStp_Ref_Current_NT;
  // Operation current for the final phase of the referencing process, in which the motor moves the first 12 half-steps from the hard stop away, at high temperature mode
  uint8  ucAvacStp_Ref_Current_HT;
  // Reserved
  uint8  ucreserviert3;
}
tNvmPara_AvacStp_StepperCurrent;

#define NVMPARA_AVACSTP_STEPPERCURRENT_INIT                  \
{                                                            \
  55u,               /* AvacStp_Hold_Current_LT*/            \
  12u,               /* AvacStp_Hold_Current_NT*/            \
  12u,               /* AvacStp_Hold_Current_HT*/            \
  79u,               /* AvacStp_Run_Current_LT*/             \
  55u,               /* AvacStp_Run_Current_NT*/             \
  55u,               /* AvacStp_Run_Current_HT*/             \
  79u,               /* AvacStp_Ref_Current_LT*/             \
  55u,               /* AvacStp_Ref_Current_NT*/             \
  55u,               /* AvacStp_Ref_Current_HT*/             \
  0u                 /* reserviert1*/                        \
}

typedef struct
{
  // Start speed
  uint16 unAvacStp_V_min;
  // Maximum Speed
  uint16 unAvacStp_V_max;   
  // Acceleration
  uint16 unAvacStp_Acceleration;
  // 0 = Brake ramp identical to acceleration ramp 1 = Brake ramp twice as fast as acceleration"
  uint8  ucAvacStp_Fast_Deceleration : 1;
  // Waiting time for reversal of the direction
  uint8  ucAvacStp_Reversing_Time : 7;
  // Time before current energization
  uint8  ucAvacStp_PreStepTime : 4;
  // Time after current energization
  uint8  ucAvacStp_PostStepTime : 4;
  // Half-step time for: 1. lower resonance frequency limit 0 = no resonance suppresion
  uint16 unAvacStp_Res_Hs_Time_U1;
  // Half-step time for 1. upper resonance frequency limit (AvacStp_RES_HS_ZEIT_U1 >  AvacStp_RES_HS_ZEIT_O1) 0 = no resonance suppresion
  uint16 unAvacStp_Res_Hs_Time_O1;
  // Half-step time for 2. lower resonance frequency limit 0 = no resonance suppresion
  uint16 unAvacStp_Res_Hs_Time_U2;
  // Half-step time for 2. upper resonance frequency limit (AvacStp_RES_HS_ZEIT_U2 >  AvacStp_RES_HS_ZEIT_O2) 0 = no resonance suppresion
  uint16 unAvacStp_Res_Hs_Time_O2;
  // Minimum allowed half-step time at low temperature
  uint16 unAvacStp_HsPeriodMin_LT;
  // Half-step time for adjusment to the safety position
  uint16 unAvacStp_HsPeriod_SP;
  // Half-step time for adjusment to the parking position
  uint16 unAvacStp_HsPeriod_PP;
  // Half-step time for 1. Adjustment at reference target
  uint16 unAvacStp_HsPeriod_ref1;
  // Half-step time for 2. Adjustment at reference target
  uint16 unAvacStp_HsPeriod_ref2;
  // Half-step time for 3. Adjustment at reference target(Motion 12 Half-steps away from the mechanical stop)
  uint16 unAvacStp_HsPeriod_ref3;
  // Half-step number for 2. adjustment at reference target
  uint16 unAvacStp_HS_ref2;
}
tNvmPara_AvacStp_StepperDynamic_Behaviour;

#define NVMPARA_AVACSTP_STEPPERDYNAMIC_BEHAVIOUR_INIT        \
{                                                            \
  152u,              /* AvacStp_V_min*/                      \
  912u,              /* AvacStp_V_max*/                      \
  17696u,            /* AvacStp_Acceleration*/               \
  0u,                /* AvacStp_Fast_Deceleration*/          \
  16u,               /* AvacStp_Reversing_Time*/             \
  6u,                /* AvacStp_PreStepTime*/                \
  8u,                /* AvacStp_PostStepTime*/               \
  0u,                /* AvacStp_Res_Hs_Time_U1*/             \
  0u,                /* AvacStp_Res_Hs_Time_O1*/             \
  0u,                /* AvacStp_Res_Hs_Time_U2*/             \
  0u,                /* AvacStp_Res_Hs_Time_O2*/             \
  1096u,             /* AvacStp_HsPeriodMin_LT*/             \
  7872u,             /* AvacStp_HsPeriod_SP*/                \
  7872u,             /* AvacStp_HsPeriod_PP*/                \
  1832u,             /* AvacStp_HsPeriod_ref1*/              \
  6579u,             /* AvacStp_HsPeriod_ref2*/              \
  6579u,             /* AvacStp_HsPeriod_ref3*/              \
  125u               /* AvacStp_HS_ref2*/                    \
}

typedef struct
{
  uint16 unAvacStp_LowerStpBlockRange_L;
  uint16 unAvacStp_UpperStpBlockRange_L;
  uint16 unAvacStp_LowerStpMovementRange_L;
  uint16 unAvacStp_UpperStpMovementRange_L;
  uint8  ucreserviert5;
  uint8  ucAvacStp_ParkingLowering_L : 7;
  uint8  ucAvacStp_ParkingSign_L : 1;
  uint8  ucAvacStp_SafetyPos_L : 7; // Distance between the lower stop and the optical axis
  uint8  ucAvacStp_SafetySign_L : 1; // Distance between the upper stop  and optical axis
  uint8  ucAvacStp_Hs_Degree_Denominator_L; //Maximum swing range downwards
  uint16 unAvacStp_Hs_Degree_Counter_L; //Maximum swing range upwards
  uint16 unAvacStp_Transmission_Factor_L; // nb of hs/degree
  uint8  ucAvacStp_Direction_L : 1;
  uint8  ucreserviert7 : 7;
  uint8  ucreserviert8; //Amount AvacStp storage position
}
tNvmPara_AvacStp_SwGeoLi;

typedef struct
{
  uint16 unAvacStp_LowerStpBlockRange_R;
  uint16 unAvacStp_UpperStpBlockRange_R; //AvacStp-Step-motor-Direction adjustment
                                          //0 = Standard direction adjustment
                                          //1 = Direction adjustment
  uint16 unAvacStp_LowerStpMovementRange_R;
  uint16 unAvacStp_UpperStpMovementRange_R;
  uint8  reserviert1;
  uint8  ucAvacStp_ParkingLowering_R : 7;
  uint8  ucAvacStp_ParkingSign_R : 1; // Distance between the lower stop and the optical
                                          // axis
  uint8  ucAvacStp_SafetyPos_R : 7; // Abstand zwischen dem oberen Anschlag und
                                          // der optischen Achse
  uint8  ucAvacStp_SafetySign_R : 1; //Maximum swivel range downward
  uint8  ucAvacStp_Hs_Degree_Denominator_R; //Maximum swivel range upward
  uint16 unAvacStp_Hs_Degree_Counter_R;
  uint16 unAvacStp_Transmission_Factor_R; // nb of hs/degree
  uint8  ucAvacStp_Direction_R : 1;
  uint8  ucreserviert1 : 7; //Amount AvacStp storage position
  uint8  ucreserviert2; //Sign AvacStp storage position
                                          //0 = positive (above the optical axis)
                                          //1 = negative (below the optical axis)
}
tNvmPara_AvacStp_SwGeoRe;

#define NVM_PARA_AVACSTP_SW_GEO_INIT                         \
{                                                            \
  300u,              /* AvacStp_LowerStpBlockRange_L*/       \
  100u,              /* AvacStp_UpperStpBlockRange_L*/       \
  280u,              /* AvacStp_LowerStpMovementRange_L*/    \
  50u,               /* AvacStp_UpperStpMovementRange_L*/    \
  0u,                /* reserviert1*/                        \
  0u,                /* AvacStp_ParkingLowering_L*/          \
  0u,                /* AvacStp_ParkingSign_L*/              \
  10u,               /* AvacStp_SafetyPos_L*/                \
  1u,                /* AvacStp_SafetySign_L*/               \
  197u,              /* AvacStp_Hs_Degree_Denominator_L*/    \
  184u,              /* AvacStp_Hs_Degree_Counter_L*/        \
  10476u,            /* AvacStp_Hs_Transmission_Factor_L*/   \
  0u,                /* AvacStp_Direction_L*/                \
  0u,                /* reserviert1*/                        \
  0u                 /* reserviert2*/                        \
}

#define NVMPARA_AVACSTP_PITCHDATA_INIT                      \
{                                                           \
  2500u,             /* WHEELBASE*/                          \
  20u,               /* REFERENCING_SPEED_MAX*/              \
  -5,               /* LOW_STOP_POSITION*/                  \
  11u,               /* DPF*/                                \
  11u,               /* DPR*/                                \
  4320u,             /* R1*/                                 \
  4320u,             /* R2*/                                 \
  0u,                /* STT_TRANSITION_DELAY*/               \
  4500u,             /* Vccx_Min*/                           \
  5500u,             /* Vccx_Max*/                           \
  -524,             /* AngleMin*/                           \
  524,              /* AngleMax*/                           \
  5u,                /* DutyMinSens*/                        \
  95u,               /* DutyMaxSens*/                        \
  4632,             /* SensorSlopeFront*/                   \
  -5687,            /* SensorSlopeRear*/                    \
  30u,               /* BhsPlausVehSpeed*/                   \
  5u,                /* SensorOutRangeTime*/                 \
  0u                 /* SensorFailureRecoveryTime*/          \
}

#define NVMPARA_AVACSTP_DCMOTORDATA_INIT                    \
{                                                           \
  0u,                /* ASL_FROZEN_VEH_SPEED*/               \
  0u,                /* ASL_HIGH_FROZEN_VEH_SPEED*/          \
  0u,                /* VEHICLE_ATTITUDE_ADJUSTEMENT_THRESHOLD_STANDSTILL*/\
  0u,                /* VEHICLE_ATTITUDE_ADJUSTEMENT_THRESHOLD_STANDSTILL_HS*/\
  0u,                /* VEHICLE_ATTITUDE_ADJUSTEMENT_THRESHOLD_MOTION*/\
  0u,                /* ASL_MOTION_DELAY*/                   \
  10u,                /* CONSTANT_SPEED_INTERVAL*/           \
  -50,              /* Min_Vehicle_Attitude*/               \
  1u,                /* Dcm_Enable*/                        \
  50,               /* Max_Vehicle_Attitude*/               \
  -300,             /* Min_ASL_Adjust_Left*/                \
  0,                /* Max_ASL_Adjust_Left*/                \
  0u,                /* reserviert2*/                        \
  -32,              /* Safety_Position_Left*/               \
  -300,             /* Min_ASL_Adjust_Right*/               \
  0,                /* Max_ASL_Adjust_Right*/               \
  0u,                /* reserviert3*/                        \
  -32               /* Safety_Position_Right*/              \
}

typedef struct
{
sint16 snAvacStp_AfsLevelling_Town_Ped_L; //AFS OFFSET For town, left headlamp
sint16 snAvacStp_AfsLevelling_MW_L      ; //AFS OFFSET For motorway, left headlamp
sint16 snAvacStp_AfsLevelling_MW_Boost_L; // AFS OFFSET For motorway boosted, left headlamp
sint16 snAvacStp_AfsLevelling_BDW_LHD_L ; // AFS OFFSET For badweather Left hand drive,
                                        // left headlamp
sint16 snAvacStp_AfsLevelling_BDW_RHD_L ; // AFS OFFSET For badweather Right hand drive,
                                        // left headlamp
sint16 snAvacStp_AfsLevelling_Foggy_LHD_L; // AFS OFFSET For Foggy left hand drive, left
                                        // headlamp
sint16 snAvacStp_AfsLevelling_Foggy_RHD_L; // AFS OFFSET For Foggy right hand drive, left
                                        // headlamp
sint16 snAvacStp_AfsLevelling_Off_L     ; //AFS OFFSET For state OFF, left headlamp
sint16 snAvacStp_AfsLevelling_HB_L      ; // AFS OFFSET For when High beam is activated,
                                        // left headlamp
sint16 snreserviert1                    ; 
}
tNvmPara_AvacStp_AfsOffset_Left;

#define NVMPARA_AVACSTP_AFSOFFSET_LEFT_INIT                 \
{                                                           \
  0,                /* AvacStp_AfsLevelling_Town_Ped_L*/    \
  3,                /* AvacStp_AfsLevelling_MW_L*/          \
  4,                /* AvacStp_AfsLevelling_MW_Boost_L*/    \
  0,                /* AvacStp_AfsLevelling_BDW_LHD_L*/     \
  0,                /* AvacStp_AfsLevelling_BDW_RHD_L*/     \
  -6,               /* AvacStp_AfsLevelling_Foggy_LHD_L*/   \
  0,                /* AvacStp_AfsLevelling_Foggy_RHD_L*/   \
  0,                /* AvacStp_AfsLevelling_Off_L*/         \
  3,                /* AvacStp_AfsLevelling_HB_L*/          \
  0                 /* reserviert1*/                        \
}

typedef struct
{
sint16 snAvacStp_AfsLevelling_Town_Ped_R; //AFS OFFSET For town, right headlamp
sint16 snAvacStp_AfsLevelling_MW_R      ; //AFS OFFSET For motorway, right headlamp
sint16 snAvacStp_AfsLevelling_MW_Boost_R; // AFS OFFSET For motorway boosted, right headlamp
sint16 snAvacStp_AfsLevelling_BDW_LHD_R ; // AFS OFFSET For badweather Left hand drive,
                                        // right headlamp
sint16 snAvacStp_AfsLevelling_BDW_RHD_R ; // AFS OFFSET For badweather Right hand drive,
                                        // right headlamp
sint16 snAvacStp_AfsLevelling_Foggy_LHD_R; // AFS OFFSET For Foggy left hand drive, right
                                        // headlamp
sint16 snAvacStp_AfsLevelling_Foggy_RHD_R; // AFS OFFSET For Foggy right hand drive, right
                                        // headlamp
sint16 snAvacStp_AfsLevelling_Off_R     ; //AFS OFFSET For state OFF, right headlamp
sint16 snAvacStp_AfsLevelling_HB_R      ; // AFS OFFSET For when High beam is activated,
                                        // right headlamp
sint16 snreserviert1                    ; 
}
tNvmPara_AvacStp_AfsOffset_Right;

#define NVMPARA_AVACSTP_AFSOFFSET_RIGHT_INIT                \
{                                                           \
  0,                /* AvacStp_AfsLevelling_Town_Ped_R*/    \
  3,                /* AvacStp_AfsLevelling_MW_R*/          \
  4,                /* AvacStp_AfsLevelling_MW_Boost_R*/    \
  0,                /* AvacStp_AfsLevelling_BDW_LHD_R*/     \
  0,                /* AvacStp_AfsLevelling_BDW_RHD_R*/     \
  0,                /* AvacStp_AfsLevelling_Foggy_LHD_R*/   \
  -6,               /* AvacStp_AfsLevelling_Foggy_RHD_R*/   \
  0,                /* AvacStp_AfsLevelling_Off_R*/         \
  0,                /* AvacStp_AfsLevelling_HB_R*/          \
  0                 /* reserviert1*/                        \
}

typedef struct
{
uint8 ucHB_APERTURE                     ; // Horizontal exterior aperture angle of high
                                        // beam, measured from 0° front axis.
uint8 ucreserviert; 
uint16 unGFHB_OFFSET_LEVELLING_DELAY; 
uint8 ucreserviert1[2]                  ; 
uint16 unOFFSET_AFS_CORRECT_SPEED       ; // Speed of the correction regarding an AFS
                                        // OFFSET
}
tNvmPara_AvacStp_AfsOffset_OperationData;

#define NVMPARA_AVACSTP_AFSOFFSET_OPERATIONDATA_INIT        \
{                                                           \
  0u,               /* HB_APERTURE*/                        \
  0u,               /* reserviert*/                        \
  100u,             /* GFHB_OFFSET_LEVELLING_DELAY*/         \
  {0u},               /* ucreserviert1[0]*/\
  1000u              /* OFFSET_AFS_CORRECT_SPEED*/           \
}

typedef struct
{
  uint8 AvacStp_FilterUpMax; // Influences stepper movement speed when going
                                          // to a higher angle
  uint8 AvacStp_FilterUpMid; // Influences stepper movement speed when going
                                          // to a higher angle
  uint8 AvacStp_FilterUpMin; // Influences stepper movement speed when going
                                          // to a higher angle
  uint8 AvacStp_FilterDownMax; // Influences stepper movement speed when going
                                          // to a lower angle
  uint8 AvacStp_FilterDownMid; // Influences stepper movement speed when going
                                          // to a lower angle
  uint8 AvacStp_FilterDownMin; // Influences stepper movement speed when going
                                          // to a lower angle
  uint8 AvacStp_HighDynamicLimit; // Acceleration pedal position value from where
                                          // High Dynamic is activated
  uint8 reserviert1[9];
}
tNvmPara_AvacStp_AvacFilter;

#define NVMPARA_AVACSTP_AVACFILTER_INIT                       \
{                                                             \
15u,                          /*AvacStp_FilterUpMax*/         \
20u,                          /*AvacStp_FilterUpMid*/         \
25u,                          /*AvacStp_FilterUpMin*/         \
15u,                          /*AvacStp_FilterDownMax*/       \
8u,                           /*AvacStp_FilterDownMid*/       \
12u,                          /*AvacStp_FilterDownMin*/       \
8u,                           /*AvacStp_HighDynamicLimit*/    \
{0u,0u,0u,0u,0u,0u,0u,0u,0u}  /* reserviert1*/                \
}

typedef struct
{
  tNvmPara_AvacStp_PitchData                           PitchData;
  tNvmPara_AvacStp_DCMotorData                         DCMotorData;
#if defined(CFG_VARIANT_FULL) || defined (UNIT_TEST)
  tNvmPara_AvacStp_StepperMotor_OperationMode          Modus;      //  12 bytes
  tNvmPara_AvacStp_StepperCurrent                      Strom;      //  10 bytes
  tNvmPara_AvacStp_StepperDynamic_Behaviour            Dynamik;    //  30 bytes
  tNvmPara_AvacStp_SwGeoLi                             SwGeoLi;    //  16 bytes
  tNvmPara_AvacStp_SwGeoRe                             SwGeoRe;    //  16 bytes
  tNvmPara_AvacStp_AfsOffset_Left                      AfsOffset_Left;
  tNvmPara_AvacStp_AfsOffset_Right                     AfsOffset_Right;
  tNvmPara_AvacStp_AfsOffset_OperationData             AfsOffset_OperationData;
  tNvmPara_AvacStp_AvacFilter                          AvacFilter;
#endif
}                                                                  // ---------
tNvmPara_AvacStpBlock;                                                 //  100 bytes
                                                                   
#ifdef CFG_VARIANT_FULL
#define NVMPARA_AVACSTPBLOCK_INIT                           \
{                                                           \
  NVMPARA_AVACSTP_PITCHDATA_INIT,                           \
  NVMPARA_AVACSTP_DCMOTORDATA_INIT,                         \
  NVMPARA_AVACSTP_STEPPERMOTOR_OPERATIONMODE_INIT,          \
  NVMPARA_AVACSTP_STEPPERCURRENT_INIT,                      \
  NVMPARA_AVACSTP_STEPPERDYNAMIC_BEHAVIOUR_INIT,            \
  NVM_PARA_AVACSTP_SW_GEO_INIT,                             \
  NVM_PARA_AVACSTP_SW_GEO_INIT,                             \
  NVMPARA_AVACSTP_AFSOFFSET_LEFT_INIT,                      \
  NVMPARA_AVACSTP_AFSOFFSET_RIGHT_INIT,                     \
  NVMPARA_AVACSTP_AFSOFFSET_OPERATIONDATA_INIT,             \
  NVMPARA_AVACSTP_AVACFILTER_INIT                             \
}
#else
#define NVMPARA_AVACSTPBLOCK_INIT                           \
{                                                           \
  NVMPARA_AVACSTP_PITCHDATA_INIT,                            \
  NVMPARA_AVACSTP_DCMOTORDATA_INIT                           \
}
#endif

#endif /*  __CODM_PARA_AVACSTP_H */

// EOF
