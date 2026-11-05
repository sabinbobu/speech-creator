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
/// \file  Cfg.h
///
/// \brief  
///
/// \descr  
///
/// \author Cosmin Cojocaru (f11501c)
///         mailTo:constantin-cosmin.cojocaru(at)marelli.com
//-----------------------------------------------------------------------------

#ifndef CFG_2019_05_15_H_
#define CFG_2019_05_15_H_

//=============================================================================
// Defines
//=============================================================================

  // Use a preliminary Cfg.h file until a more complete architecture has been defined.
#define CFG_SysLoad_None       0U
#define CFG_SysLoad_ISRLoad    1U
#define CFG_SysLoad_TaskLoad   2U
#define CFG_SysLoad_SystemLoad 4U

// driver (CFG_DRV_...)
#define CFG_Drv_None                     1U
#define CFG_Drv_Default                  2U
// driver (CFG_DRV_SER and CFG_DRV_SER2)
#define CFG_Drv_Extended                 3U
// driver (CFG_DRV_PSENS)
#define CFG_Drv_Alternative1             4U
#define CFG_Drv_Alternative2             5U

#define CFG_DRV_CAN     CFG_Drv_Default

#define CFG_OPT_SYSLOAD CFG_SysLoad_None

// AVAC types (CFG_TYP_AVAC) TO DO
#define CFG_Avac_None                    1U
#define CFG_Avac_Prj                     2U
#define CFG_Avac_Dyn0                    3U   // otp2rt: DELETE
#define CFG_Avac_Dyn1                    4U
#define CFG_Avac_Stat1                   5U   // static  AVAC similar to Litronic 4
#define CFG_Avac_DynAdv1                 6U

// AVAC options (CFG_OPT_AVAC) TO DO
#define CFG_Avac_SupportHDDelay     0x0001U   // supported by CFG_AvacDyn1
#define CFG_Avac_SupportHeightCorr  0x0002U   // supported by CFG_AvacDyn1
#define CFG_Avac_SupportInvalidFlag 0x0004U   // supported by CFG_AvacDyn0 and ..1
#define CFG_Avac_DisAtSpeedFailure  0x0008U   // supported by CFG_AvacStat1
#define CFG_Avac_UseFixSafetyPos    0x0010U   // supported by CFG_AvacStat1
#define CFG_Avac_IgnoreStt          0x0020U   // STT-Config has no influence on AVAC
#define CFG_Avac_ActPosAtLbOff      0x0040U   // don't move to static pos at LB off

#define CFG_TYP_AVAC                CFG_Avac_Dyn1 
#define CFG_OPT_AVAC                CFG_Avac_SupportHDDelay

// Define support for RDM services
#define SUPPORT_RDM_SERVICES
//define of target that the CUST is running.
#define LDMO_B0_SAMPLE

#if defined (CPU_S32K146)
#define SAMPLE_FULL
#elif defined (CPU_S32K142)
#define SAMPLE_ECO
#elif defined (CPU_S32K144)
#define SAMPLE_ECO
#endif

//#define CFG_DV_MODE //should be commented if is not necessary 

#if defined (APP_BUILD_St126_TYPE_FULL) || defined (APP_BUILD_St126_TYPE_FULL_P64_LHD) || defined (APP_BUILD_St126_TYPE_FULL_P64_RHD)
#define CFG_VARIANT_FULL
#elif defined (APP_BUILD_St126_TYPE_ECO) || defined (APP_BUILD_St126_TYPE_ECO_P64)
#define CFG_VARIANT_ECO
#endif

// FOR DINAMYC BENDING LIGHT

  // CL Option (CFG_OPT_CL)                 Left/right head ligh angle relation
  //   left right relation types
#define CFG_Cl_LR_RelationDev            0x1000U  // development
#define CFG_Cl_LR_RelationPrj            0x2000U  // project specific
#define CFG_Cl_LR_Relation1              0x0001U  // linear         alpha - alpha/2
#define CFG_Cl_LR_Relation2              0x0002U  // adaptive       alpha - alpha/2
#define CFG_Cl_LR_Relation3              0x0004U  // adaptive DC    140 - 70 [0.1]
#define CFG_Cl_LR_Relation4              0x0008U  // adaptive PSA   alpha - alpha/3
#define CFG_Cl_LR_Relation5              0x0010U  // linear   PSA   alpha - alpha/3
#define CFG_Cl_LR_Relation6              0x0020U
#define CFG_Cl_LR_Relation7              0x0040U
#define CFG_Cl_LR_Relation8              0x0080U

  // idle range options
#define CFG_Cl_IdleRangeAlg2             0x0200U  // extended idle range algorithm

#define CFG_Cl_SwiRateLim2               0x0400U  // extended swivelling rate limiter

#define CFG_Cl_ActivateWithZeroCurvature   0x4000U  // DBL can be activated only if the curvature is zero
#define CFG_Cl_DeactivateWithZeroCurvature 0x8000U  // DBL can be deactivated only if the curvature is zero

#define CFG_OPT_CL                  ( CFG_Cl_LR_Relation2                 | \
                                        CFG_Cl_IdleRangeAlg2                | \
                                        CFG_Cl_SwiRateLim2                  | \
                                        CFG_Cl_ActivateWithZeroCurvature    | \
                                        CFG_Cl_DeactivateWithZeroCurvature      )
  // CL types (CFG_TYP_CL)
#define CFG_Cl_None                      1U
#define CFG_Cl_AlgPrj                    2U
#define CFG_Cl_Alg1                      3U
#define CFG_Cl_Alg2                      4U
#define CFG_Cl_Alg3                      5U
#define CFG_TYP_CL_LR06               CFG_Cl_Alg2         // dynamic bending light 

  // -----------------------------------------------------------------------------
  // (CFG_OPT_ENVCOND) options concerning environmental condition
#define CFG_EnvCond_SuppNightSensor      0x0001U  // support night sensor
#define CFG_EnvCond_SuppRainSensor       0x0002U  // support rain sensor
#define CFG_EnvCond_SuppEngineState      0x0004U  // support engine state
#define CFG_EnvCond_SuppNoLowBeam        0x0008U  // do *not* query for the low beam signal
#define CFG_EnvCond_SuppExternalCommand  0x0010U  // support external commands (e.g. SigPrep can set such commands)
#define CFG_EnvCond_SuppSportMode        0x0020U  // support sport mode (increase dynamics of system)
#define CFG_EnvCond_SuppCity             0x0040U  // support city detection?
#define CFG_EnvCond_SuppLoBmOnRq         0x0080U  // support low beam request?

#ifndef CFG_OPT_ENVCOND
#define CFG_OPT_ENVCOND   0U
#endif

  // VDDHLD types (CFG_TYP_VDDHLD)
#define CFG_VddHld_None                  1U
#define CFG_VddHld_Basic                 2U
#define CFG_VddHld_CurMixer1             2U   // mixes curvature to 40% Curvature and 60% CurvatureOpt
#define CFG_VddHld_EvaluateDynamicOff    1U
#define CFG_VddHld_SWA_Filter_DES        1U      // design filter , IIR filter or FIR filter different parameters
#define CFG_VddHld_YR_Filter_DES         1U      // design filter , IIR filter or FIR filter different parameters
  // VDDHDL
#define CFG_TYP_VDDHLD              CFG_VddHld_Basic              // pre-filtering
#define CFG_OPT_VDDHLD_CUR_MIXER    CFG_VddHld_CurMixer1        //CFG_VddHld_CurMixer1
#define CFG_OPT_VDDHLD_EVAL_DYNAMIC CFG_VddHld_EvaluateDynamicOff
#define CFG_OPT_VDDHLD_SWA_FILTER   CFG_VddHld_SWA_Filter_DES
#define CFG_OPT_VDDHLD_YR_FILTER    CFG_VddHld_YR_Filter_DES

#ifndef CFG_OPT_ECUFUNC
#define CFG_OPT_ECUFUNC   0U
#endif

#define CFG_EcuFunc_SuppExtDblcCtrl      0x0010U  // Dblc

  // Application Manager types (CFG_TYP_AM)
#define CFG_Am_None                     0u    // no Application Manager
#define CFG_Am_Default                  1u    // with default Application Manager
#define CFG_Am_Afs                      2u    // Application Manager for full AFS
#define CFG_Am_AfxVer                   3u    // Application Manager with AFX via vertical steppers

#define CFG_TYP_AM  CFG_Am_Afs

// LMM Sheets CFG
#define CFG_LF_Cnt                      (32u)                 // Number of Light Functions
#define CFG_LB_LDSTR_Cnt                (13u)                 // Number of LB light distibutions
#define CFG_LF_LUT_Size                 (40u)                 // Number of LookUpTable entries
#define CFG_LOGICAL_UNITS               (103u)                // Max number of logical units allowed in coding sheet

  // Number of LED channels
  #if defined (CFG_VARIANT_FULL ) || defined(UNIT_TEST)
    #define CFG_MLC_Chip_Cnt                7u
    #define CFG_MLC_Chip_Not_Connected      0xFFu
    #define CFG_BASE_CHANNELS_NR            4u
    #define CFG_UNUSED_CHANNEL              1u
    #define CFG_MATRIX_CHANNELS_NR          CFG_MLC_Chip_Cnt
    #define CFG_LED_CHANNELS_NR             12u
    #define CFG_LSM_LED_CHANNELS_NR         (16u)                 // Max number of illuminants allowed in coding sheet

    #define CFG_MATRIX_LEDs_PER_CH_Cnt      16u
    #define CFG_MATRIX_PXL_CNT              CFG_MLC_Chip_Cnt*CFG_MATRIX_LEDs_PER_CH_Cnt
    #define CFG_MATRIX_RAW_CNT              30u
    #define CFG_MATRIX_MAX_NO_PXL           90u 
    #define CFG_MATRIX_EEPROM_SIZE          256u 
  #elif defined (CFG_VARIANT_ECO)
    #define CFG_LED_CHANNELS_NR             4u
    #define CFG_LSM_LED_CHANNELS_NR         (6u)                 // Max number of illuminants allowed in coding sheet

  #endif

#define CFG_LSM_LED_ILLUMINANT_NR CFG_LSM_LED_CHANNELS_NR

#define CFG_NTC_BIN_CNT                (14u)      // Number of Ntcs and Binnings

#define CFG_BIN_CLASS_CNT               (6u)      // Number of Binning Classes



// To be removed when the modules are updated
#define CFG_NON_MATRIX_BUCKs           (4u)
#define CFG_MATRIX_BUCKs               (8u)
#define CFG_LAMP_CH_Cnt                (CFG_NON_MATRIX_BUCKs + CFG_MATRIX_BUCKs) //used in CtrlLed
#define CFG_LM_Cnt         (CFG_LAMP_CH_Cnt)     // Number of Leuchtmittel
#define CFG_LF_Cnt         (32u)     // Number of Light Functions
#define CFG_LB_LDSTR_Cnt   (13u)     // Number of LB light distibutions
#define CFG_LF_LUT_Size    (40u)     // Number of LookUpTable entries
#define CFG_PG_Cnt         (10u)     // Number of Pixelgroups
#define CFG_CntNtcExt      (4u)      // Number of external NTCs
#define CFG_CntSens        (2u)      // Number of sensor inputs (analog /PWM)

#define CFG_Fan_Cnt        (1u)      // Number of Fans
#define CFG_BinningCnt    (4u)      // Number of Binnig resistors
#define CFG_CntNtcTotal    (6u)      // Total numbers of NTCs
#define CFG_CntNtcPorts (6u)        //Total numbers of NTCs ports
// To be removed

//THERMO
#define CFG_THERMOZONES_NR           12u // Number of Thermozones for each led channel 

// ADC EOL calibration suport
#define CFG_SUPORT_ADC_EOL_CALIBRATION          TRUE     // ADC EOL calibration

#endif // CFG_2019_05_15_H_
