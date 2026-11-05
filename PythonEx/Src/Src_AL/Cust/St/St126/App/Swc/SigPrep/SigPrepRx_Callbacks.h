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
/// \file   SigPrepRxCallbacks.h
///
/// \brief  
///
/// \descr  Input Rx Frame Callbacks Header file
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __SIG_PREP_RX_CALLBACKS_H__
#define __SIG_PREP_RX_CALLBACKS_H__

//-----------------------------------------------------------------------------
//  includes
//-----------------------------------------------------------------------------
#include <SigPrep_Types.h>

//-----------------------------------------------------------------------------
//  defines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Handles for invalid data timers
//-----------------------------------------------------------------------------

//define for each frame which will be skip sending of data
#define SIGPREP_RX_MSEC_INVALID_DATA            2000U

//number of frames used to skip sending of data in case of invalid data
#define SIGPREP_RX_NUMBER_OF_INVALID_DATA         11U 

#define SIGPREP_RX_ANIMA_ID                        0U
#define SIGPREP_RX_MODE_CONFIG_VEHICLE_ID          1U
#define SIGPREP_RX_KM_TOTAL_ID                     2U
#define SIGPREP_RX_CPT_TEMPOREL_ID                 3U
#define SIGPREP_RX_ETAT_FEE_ID                     4U
#define SIGPREP_RX_CONSIGNE_SITE_D_ID              5U
#define SIGPREP_RX_ACCELERATION_ID                 6U
#define SIGPREP_RX_PITCH_ID                        7U
#define SIGPREP_RX_POSITION_SITE_D_ID              8U
#define SIGPREP_RX_DYN_BEND_BEAM_FAULT_ID          9U
#define SIGPREP_RX_LVL_REF_STATE_ID               10U

#define SIGPREP_CFG_32_BIT_MASK                                 0xFFFFFFFFu    // 32 Bit Mask
#define SIGPREP_RX_ZERO_VALUE                                   0u
#define SIGPREP_RX_INVALID_CONSIGNE_SITE_D_MIN_VAL              0x3FDu       // CONSIGNE_SITE_D minimum invalid value
#define SIGPREP_RX_INVALID_CONSIGNE_SITE_D_MAX_VAL              0x3FFu       // CONSIGNE_SITE_D maximum invalid value
#define SIGPREP_RX_INVALID_CYLINDER_PRESSURE                    0xFFFu       // PRESSION_MAITRE_CYL invalid value
#define SIGPREP_RX_EFCMNT_PDLE_ACCEL_MAX_VAL                    0xC8u        // Maximum value of EFCMNT_PDLE_ACCEL signal
#define SIGPREP_RX_AUTO_BRAKING_PRESSURE_MAX_VAL                0xFEu        // Maximum value of AUTO_BRAKING_PRESSURE signal

#define SIGPREP_RX_LENGTH_VITESSE_LACET                         16u    // VITESSE_LACET signal length

#define SIGPREP_RX_CONFIG_TIME_THRESHOLD                        2000u    // VITESSE_LACET signal length

#define SIGPREP_RX_INVALID_CPT_TEMPOREL                 0xFFFFFFFFu
#define SIGPREP_RX_UNAVAILABLE_CPT_TEMPOREL             0xFFFFFFFEu

#define SIGPREP_RX_INVALID_ODOMETER                     0xFFFFFFu

#define SIGPREP_RX_INVALID_VITESSE_LACET                        0x7FFF       // VITESSE_LACET invalid value
#define SIGPREP_RX_INVALID_VITESSE_LACET_MIN_VAL_1              1001         // VITESSE_LACET minimum invalid value 1
#define SIGPREP_RX_INVALID_VITESSE_LACET_MAX_VAL_1              32766        // VITESSE_LACET maximum invalid value 1
#define SIGPREP_RX_INVALID_VITESSE_LACET_MIN_VAL_2              -32768       // VITESSE_LACET minimum invalid value 2
#define SIGPREP_RX_INVALID_VITESSE_LACET_MAX_VAL_2              -1001        // VITESSE_LACET maximum invalid value 2


#define SIGPREP_RX_VALID_STEER_WHEEL_ANGLE_MAX_VAL              7800         // STEER_WHEEL_ANGLE_CONF maximum valid value
#define SIGPREP_RX_VALID_STEER_WHEEL_ANGLE_MIN_VAL              -7800        // STEER_WHEEL_ANGLE_CONF minimum valid value
#define SIGPREP_RX_STEER_WHEEL_ANGLE_INIT_IN_PROGRESS           -28673       // STEER_WHEEL_ANGLE_CONF INIT_IN_PROGRESS value

#define SIGPREP_RX_VEHICLE_CONFIG_FITTING                       0u    // Fitting
#define SIGPREP_RX_VEHICLE_CONFIG_PLANT                         1u    // Plant
#define SIGPREP_RX_VEHICLE_CONFIG_CHECK                         2u    // Check
#define SIGPREP_RX_VEHICLE_CONFIG_STORAGE                       3u    // Storage
#define SIGPREP_RX_VEHICLE_CONFIG_CLIENT                        4u    // Client
#define SIGPREP_RX_VEHICLE_CONFIG_SHOWROOM                      5u    // Showroom
#define SIGPREP_RX_VEHICLE_CONFIG_APV                           6u    // APV

#define SIGPREP_RX_INVALID_VITESSE_VEHICULE_ROUES    (uint16)0xFFFF       //  VITESSE_VEHICULE_ROUES  invalid value
#define SIGPREP_RX_5KMH_THRESHOLD                    (uint16)500u         //  VITESSE_VEHICULE_ROUES 5 km/h value

#if defined (CFG_VARIANT_FULL) || (UNIT_TEST) // Applicable only for FULL version
#define SIGPREP_RX_LENGTH_ASSIETTE_VEHICULE                    10u    // ASSIETTE_VEHICULE signal length
#define SIGPREP_RX_ASSIETTE_VEHICULE_RESOLUTION_NUMERATOR      6      // ASSIETTE_VEHICULE resolution numerator
#define SIGPREP_RX_ASSIETTE_VEHICULE_RESOLUTION_DENOMINATOR    10     // ASSIETTE_VEHICULE resolution denominator
#define SIGPREP_RX_LENGTH_PERCEIVE_L_R_ANGLE                   13u    // PERCEIVE_ANGLE LEFT/RIGHT signal length
#define SIGPREP_RX_LENGTH_PERCEIVE_T_B_ANGLE                   11u    // PERCEIVE_ANGLE TOP/BOTTOM signal length
#define SIGPREP_RX_LENGTH_CLUSTER_ANGLE_L_R                     9u    // CLUSTER_ANGLE LEFT/RIGHT signal length
#define SIGPREP_RX_LENGTH_CLUSTER_L_R_AZIMUTH_RATE              8u    // CLUSTER_AZIMUTH_RATE LEFT/RIGHT signal length
#define SIGPREP_RX_LENGTH_PERCEIVE_L_R_AZIMUTHRATE              8u    // PERCEIVE_AZIMUTHRATE LEFT/RIGHT signal length
#define SIGPREP_RX_LENGTH_CLUSTER_BOTTOMANGLE                   8u    // CLUSTER_BOTTOMANGLE signal length
#define SIGPREP_RX_LENGTH_VEH_PATH_CURVATURE                   16u    // VEH_PATH_CURVATURE signal length
#define SIGPREP_RX_LENGTH_STEER_WHEEL_ANGLE                    16u    // STEERING_WHEEL_ANGLE signal length

#define SIGPREP_RX_0_BIT                                        1u     // 2 pow 0
#define SIGPREP_RX_1_BIT                                        2u     // 2 pow 1
#define SIGPREP_RX_2_BIT                                        4u     // 2 pow 2
#define SIGPREP_RX_3_BIT                                        8u     // 2 pow 3
#define SIGPREP_RX_4_BIT                                        16u    // 2 pow 4
#define SIGPREP_RX_5_BIT                                        32u    // 2 pow 5
#define SIGPREP_RX_6_BIT                                        64u    // 2 pow 6

#define SIGPREP_RX_INVALID_HCLUSTERDISTANCE_X                   0x1FFu       //  HCLUSTERDISTANCE_X left and right invalid value (X = 1 to 5)
#define SIGPREP_RX_INVALID_HCLUSTERDISTANCE_X_MIN_VAL           0x1F5u       //  HCLUSTERDISTANCE_X left and right minimum invalid value (X = 1 to 5)
#define SIGPREP_RX_INVALID_HCLUSTERDISTANCE_X_MAX_VAL           0x1FDu       //  HCLUSTERDISTANCE_X left and right maximum invalid value (X = 1 to 5)
#define SIGPREP_RX_INVALID_HCLUSTERANGLE_X                      0x0FF        //  HCLUSTERANGLE_X left and right invalid value (X = 1 to 5)
#define SIGPREP_RX_INVALID_HCLUSTERANGLE_X_MIN_VAL_1            0x0FB        //  HCLUSTERANGLE_X left and right minimum invalid value 1 (X = 1 to 5)
#define SIGPREP_RX_INVALID_HCLUSTERANGLE_X_MAX_VAL_1            0x0FD        //  HCLUSTERANGLE_X left and right maximum invalid value 1 (X = 1 to 5)
#define SIGPREP_RX_INVALID_HCLUSTERANGLE_X_MIN_VAL_2            0x100        //  HCLUSTERANGLE_X left and right minimum invalid value 2 (X = 1 to 5)
#define SIGPREP_RX_INVALID_HCLUSTERANGLE_X_MAX_VAL_2            0x105        //  HCLUSTERANGLE_X left and right maximum invalid value 2 (X = 1 to 5)
#define SIGPREP_RX_INVALID_HCLUSTERAZIMUTHRATE_X                0x7F         //  HCLUSTERAZIMUTHRATE_X left and right invalid value (X = 1 to 5)
#define SIGPREP_RX_INVALID_HCLUSTERAZIMUTHRATE_LR_X_MIN_VAL_1    117         //  HCLUSTERAZIMUTHRATE_X left and right minimum invalid value 1 (X = 1 to 5)
#define SIGPREP_RX_INVALID_HCLUSTERAZIMUTHRATE_L_MAX_VAL_1       126         //  HCLUSTERAZIMUTHRATE_X left maximum invalid value 1 (X = 1 to 5)
#define SIGPREP_RX_INVALID_HCLUSTERAZIMUTHRATE_R_MAX_VAL_1       125         //  HCLUSTERAZIMUTHRATE_X right maximum invalid value 1 (X = 1 to 5)
#define SIGPREP_RX_INVALID_HCLUSTERAZIMUTHRATE_X_MIN_VAL_2      -128         //  HCLUSTERAZIMUTHRATE_X left and right minimum invalid value 2 (X = 1 to 5)
#define SIGPREP_RX_INVALID_HCLUSTERAZIMUTHRATE_X_MAX_VAL_2      -101         //  HCLUSTERAZIMUTHRATE_X left and right maximum invalid value 2 (X = 1 to 5)
#define SIGPREP_RX_INVALID_HCLUSTERMINDISTANCE_X                0x1FFu       //  HCLUSTERMINDISTANCE_X left and right invalid value (X = 1 to 5)
#define SIGPREP_RX_INVALID_HCLUSTERMINDISTANCE_X_MIN_VAL        0x1F5u       //  HCLUSTERMINDISTANCE_X left and right minimum invalid value (X = 1 to 5)
#define SIGPREP_RX_INVALID_HCLUSTERMINDISTANCE_X_MAX_VAL        0x1FDu       //  HCLUSTERMINDISTANCE_X left and right maximum invalid value (X = 1 to 5)

#define SIGPREP_RX_INVALID_ASSIETTE_VEHICULE                    0x1FF        //  ASSIETTE_VEHICULE invalid value
#define SIGPREP_RX_INVALID_ASSIETTE_VEHICULE_MIN_VAL_1          0x200        //  Minimum value of ASSIETTE_VEHICULE signal 1
#define SIGPREP_RX_INVALID_ASSIETTE_VEHICULE_MAX_VAL_1          0x20B        //  Minimum value of ASSIETTE_VEHICULE signal 2
#define SIGPREP_RX_INVALID_ASSIETTE_VEHICULE_MIN_VAL_2          0x1F5        //  Maximum value of ASSIETTE_VEHICULE signal 1
#define SIGPREP_RX_INVALID_ASSIETTE_VEHICULE_MAX_VAL_2          0x1FE        //  Maximum value of ASSIETTE_VEHICULE signal 2
#define SIGPREP_RX_INVALID_POSITION_SITE_D                      0x3FFu       //  POSITION_SITE_D invalid value
#define SIGPREP_RX_INVALID_VEH_PATH_CURVATURE                   0x7FFF       //  VEH_PATH_CURVATURE invalid value
#define SIGPREP_RX_INVALID_VEH_PATH_CURVATURE_MIN_VAL_1         30001        //  VEH_PATH_CURVATURE invalid value minimum invalid value 1
#define SIGPREP_RX_INVALID_VEH_PATH_CURVATURE_MAX_VAL_1         32765        //  VEH_PATH_CURVATURE invalid value maximum invalid value 1
#define SIGPREP_RX_INVALID_VEH_PATH_CURVATURE_MIN_VAL_2         -32768       //  VEH_PATH_CURVATURE invalid value minimum invalid value 2
#define SIGPREP_RX_INVALID_VEH_PATH_CURVATURE_MAX_VAL_2         -30001       //  VEH_PATH_CURVATURE invalid value maximum invalid value 2
#define SIGPREP_RX_UNAVAILABLE_VEH_PATH_CURVATURE               0x7FFE       //  VEH_PATH_CURVATURE unavailable value
#define SIGPREP_RX_INVALID_KM_TOTAL                             0xFFFFFFu    //  KM_TOTAL invalid value

#define SIGPREP_RX_INVALID_PERCEIVERFL_X_BRIGHTNESS             0x7Fu        //  PERCEIVERFL_X_BRIGHTNESS invalid value (X = 1 to 3)
#define SIGPREP_RX_INVALID_PERCEIVERFL_X_BRIGHTNESS_MIN_VAL     0x65u        //  PERCEIVERFL_X_BRIGHTNESS minimum invalid value (X = 1 to 3)
#define SIGPREP_RX_INVALID_PERCEIVERFL_X_BRIGHTNESS_MAX_VAL     0x7Du        //  PERCEIVERFL_X_BRIGHTNESS maximum invalid value (X = 1 to 3)
#define SIGPREP_RX_INVALID_PERCEIVERFL_X_L_R_ANGLE              0x0FFF       //  PERCEIVERFL_X_L_R_ANGLE left and right invalid value (X = 1 to 3)
#define SIGPREP_RX_INVALID_PERCEIVERFL_X_L_R_ANGLE_MIN_VAL_1    0x0FA1       //  PERCEIVERFL_X_L_R_ANGLE left and right minimum invalid value 1 (X = 1 to 3)
#define SIGPREP_RX_INVALID_PERCEIVERFL_X_L_R_ANGLE_MAX_VAL_1    0x0FFD       //  PERCEIVERFL_X_L_R_ANGLE left and right maximum invalid value 1 (X = 1 to 3)
#define SIGPREP_RX_INVALID_PERCEIVERFL_X_L_R_ANGLE_MIN_VAL_2    -4096       //  PERCEIVERFL_X_L_R_ANGLE left and right minimum invalid value 2 (X = 1 to 3)
#define SIGPREP_RX_INVALID_PERCEIVERFL_X_L_R_ANGLE_MAX_VAL_2    -4001       //  PERCEIVERFL_X_L_R_ANGLE left and right maximum invalid value 2 (X = 1 to 3)
#define SIGPREP_RX_INVALID_PERCEIVERFL_X_T_B_ANGLE              0x3FF        //  PERCEIVERFL_X_T_B_ANGLE top and bottom invalid value (X = 1 to 3)
#define SIGPREP_RX_INVALID_PERCEIVERFL_X_T_B_ANGLE_MIN_VAL_1    -1024        //  PERCEIVERFL_X_T_B_ANGLE top and bottom minimum invalid value 1 (X = 1 to 3)
#define SIGPREP_RX_INVALID_PERCEIVERFL_X_T_B_ANGLE_MAX_VAL_1    -1001        //  PERCEIVERFL_X_T_B_ANGLE top and bottom maximum invalid value 1 (X = 1 to 3)
#define SIGPREP_RX_INVALID_PERCEIVERFL_X_T_B_ANGLE_MIN_VAL_2    0x3E9        //  PERCEIVERFL_X_T_B_ANGLE top and bottom minimum invalid value 2 (X = 1 to 3)
#define SIGPREP_RX_INVALID_PERCEIVERFL_X_T_B_ANGLE_MAX_VAL_2    0x3FD        //  PERCEIVERFL_X_T_B_ANGLE top and bottom maximum invalid value 2 (X = 1 to 3)
#define SIGPREP_RX_INVALID_PERCEIVERFL_X_DISTANCE               0x1FFu       //  PERCEIVERFL_X_DISTANCE invalid value (X = 1 to 3)
#define SIGPREP_RX_INVALID_PERCEIVERFL_X_DISTANCE_MIN_VAL       0x1F5u       //  PERCEIVERFL_X_DISTANCE minimum invalid value (X = 1 to 3)
#define SIGPREP_RX_INVALID_PERCEIVERFL_X_DISTANCE_MAX_VAL       0x1FDu       //  PERCEIVERFL_X_DISTANCE maximum invalid value (X = 1 to 3)

#define SIGPREP_RX_INVALID_PERCEIVEEFL_X_ID                     0x00u        //  PERCEIVEEFL_X_ID invalid value (X = 1 to 3)
#define SIGPREP_RX_INVALID_PERCEIVERFL_X_AZIMUTHRATE            0x7F         //  PERCEIVERFL_X_AZIMUTHRATE left and right invalid value (X = 1 to 3)
#define SIGPREP_RX_INVALID_PERCEIVERFL_X_AZIMUTHRATE_MIN_VAL_1  66           //  PERCEIVERFL_X_AZIMUTHRATE left and right minimum invalid value 1 (X = 1 to 3)
#define SIGPREP_RX_INVALID_PERCEIVERFL_X_AZIMUTHRATE_MAX_VAL_1  125          //  PERCEIVERFL_X_AZIMUTHRATE left and right maximum invalid value 1 (X = 1 to 3)
#define SIGPREP_RX_INVALID_PERCEIVERFL_X_AZIMUTHRATE_MIN_VAL_2  -128         //  PERCEIVERFL_X_AZIMUTHRATE left and right minimum invalid value 2 (X = 1 to 3)
#define SIGPREP_RX_INVALID_PERCEIVERFL_X_AZIMUTHRATE_MAX_VAL_2  -66          //  PERCEIVERFL_X_AZIMUTHRATE left and right maximum invalid value 2 (X = 1 to 3)

#define SIGPREP_RX_INVALID_HCLUSTERBOTTOMANGLE_X                0x7F         //  HCLUSTERBOTTOMANGLE_X invalid value (X = 1 to 5)
#define SIGPREP_RX_INVALID_HCLUSTERBOTTOMANGLE_X_MIN_VAL_1      101          //  HCLUSTERBOTTOMANGLE_X minimum invalid value 1 (X = 1 to 5)
#define SIGPREP_RX_INVALID_HCLUSTERBOTTOMANGLE_X_MAX_VAL_1      125          //  HCLUSTERBOTTOMANGLE_X maximum invalid value 1 (X = 1 to 5)
#define SIGPREP_RX_INVALID_HCLUSTERBOTTOMANGLE_X_MIN_VAL_2      -128         //  HCLUSTERBOTTOMANGLE_X minimum invalid value 2 (X = 1 to 5)
#define SIGPREP_RX_INVALID_HCLUSTERBOTTOMANGLE_X_MAX_VAL_2      -101         //  HCLUSTERBOTTOMANGLE_X maximum invalid value 2 (X = 1 to 5)
#define SIGPREP_RX_INVALID_HCLUSTERID_X                         255u        //  HCLUSTERID_X invalid value (X = 1 to 5)

#define SIGPREP_RX_INVALID_AUTO_BREAKING_PRESSURE               0xFFu        //  AUTO_BREAKING_PRESSURE invalid value
#define SIGPREP_RX_INVALID_EFCMNT_PDLE_ACCEL                    0xFFu        //  EFCMNT_PDLE_ACCEL invalid value
#define SIGPREP_RX_INVALID_VOLONTE_COND                         0xFFu        //  INVALID_VOLONTE_COND invalid value

#define SIGPREP_RX_CVM_FRAMES                                   8u           //  Number of frames coming from CVM
#define SIGPREP_RX_3_FRAMES                                     3u           //  3 consecutive frames define

#define SIGPREP_RX_163_ID                                       0u           //  Index for frame ID 0x163
#define SIGPREP_RX_16B_ID                                       1u           //  Index for frame ID 0x16B
#define SIGPREP_RX_183_ID                                       2u           //  Index for frame ID 0x183
#define SIGPREP_RX_18B_ID                                       3u           //  Index for frame ID 0x18B
#define SIGPREP_RX_1AB_ID                                       4u           //  Index for frame ID 0x1AB
#define SIGPREP_RX_12B_ID                                       5u           //  Index for frame ID 0x12B
#define SIGPREP_RX_143_ID                                       6u           //  Index for frame ID 0x143
#define SIGPREP_RX_14B_ID                                       7u           //  Index for frame ID 0x14B

#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)

#if defined (CFG_VARIANT_ECO) || (UNIT_TEST) // Applicable only for ECO version
#define SIGPREP_RX_DIAG_LVL_R_OK  0u
#define SIGPREP_RX_DIAG_LVL_R_NOK 1u
#endif // (CFG_VARIANT_ECO) || (UNIT_TEST)

//-----------------------------------------------------------------------------
//  function prototypes
//-----------------------------------------------------------------------------
void SigPrep_RxCallbacks_HS6_ACQ_NEW_JDD_55F       (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DAT_VSM_36E           (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DAT_VSM_3AE           (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DAT_VSM_54D           (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DAT4_V2_BSI_552       (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DYN3_CMM_468          (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_INTE_ELECTRON_BSI_092 (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DYN2_FRE_3CD          (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DYN_BEMP_2B7_RX       (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DYN_VSM_257           (teSigPrep_RxFrameState eSigPrepRxState);
boolean SigPrep_RxCallback_SideCheck_2B7_RX        (void);
#if defined (CFG_VARIANT_ECO) || (UNIT_TEST) // Applicable only for ECO version
boolean SigPrep_RxCallback_SideCheck_477_RX         (void);
void    SigPrep_RxCallbacks_HS6_DIAG_DRVLED_R_477_RX(teSigPrep_RxFrameState eSigPrepRxState);
#endif
#if defined (CFG_VARIANT_FULL) || (UNIT_TEST) // Applicable only for FULL version
void SigPrep_RxCallbacks_HS6_DAT2_DRVLED_R_4D7_RX(teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DAT_CSS_350           (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DAT_DRVLED_R_297_RX   (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DYN_VSM_28E           (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DAT_VSM_32E           (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DAT7_BSI_612          (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DYN_VSM_0AB           (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DYN_VSM_0C3           (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DYN_VSM_0CB           (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DYN_VSM_0E3           (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DYN_VSM_0EB           (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DYN_VSM_103           (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DYN_VSM_10B           (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DYN_VSM_123           (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DYN_VSM_12B           (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DYN_VSM_143           (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DYN_VSM_14B           (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DYN_VSM_163           (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DYN_VSM_16B           (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DYN_VSM_183           (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DYN_VSM_18B           (teSigPrep_RxFrameState eSigPrepRxState);
void SigPrep_RxCallbacks_HS6_DYN_VSM_1AB           (teSigPrep_RxFrameState eSigPrepRxState);
boolean SigPrep_RxCallback_SideCheck_297_RX        (void);
boolean SigPrep_RxCallback_SideCheck_4D7_RX(void);
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)

#endif // __SIG_PREP_RX_CALLBACKS_H__

// EOF
