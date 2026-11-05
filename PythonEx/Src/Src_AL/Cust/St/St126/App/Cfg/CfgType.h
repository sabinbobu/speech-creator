#ifndef _CFGTYPE_H
#define _CFGTYPE_H

// ****************************************************************************
//
// (C) Automotive-Lighting Reutlingen GmbH  -  ALRT/EEG4
//     Tuebinger Strasse 123, 72703 Reutlingen, Germany
//
// ****************************************************************************

/// ---------------------------------------------------------------------------
///
///  \file    CfgType.h
///
///  \author  -
///  \owner   -
///
///  \date    27.09.2006
///
///  \brief   List of supported configurations, options and links
///
///  \descr
///
/// ---------------------------------------------------------------------------

///
/// \addtogroup DxyCfgHw
///   <B> Hardware configuration <HR> </B>\n

/// \addtogroup DxyCfgHw
/// \par "CFG_TYP_HW" select hardware:\n
///       CFG_Hw_B0  board versions B0, B1, ... \n
///       CFG_Hw_C0  board versions C0, C1, ... \n
///       CFG_Hw_D0  board versions D0, D1, ...

/// \addtogroup DxyCfgHw
/// \par "CFG_DRV_STP_LWR" driver for LWR stepper:\n
///       CFG_Drv_None\n
///       CFG_Drv_Default


// -----------------------------------------------------------------------------
// include list of all defined projects
//#include <Cfg/CfgProjects.h>


// -----------------------------------------------------------------------------
// cpu type (CFG_TYP_CPU)
#define CFG_Cpu_C164                     1U
#define CFG_Cpu_XC164                    2U
#define CFG_Cpu_Fx3                      3U
#define CFG_Cpu_Ph3                      4U
#define CFG_Cpu_Cg4                      5U
#define CFG_Cpu_Fx4                      6U
#define CFG_Cpu_STM8A                    7U
#define CFG_Cpu_RH850                    8U

// -----------------------------------------------------------------------------
// ecu type (CFG_TYP_ECU)
#define CFG_Ecu_L6                       1U   // Litronic 6
#define CFG_Ecu_A1                       2U   // AL-Box
#define CFG_Ecu_A2                       3U   // AL-Control
#define CFG_Ecu_A3                       4U   // AL-Control2

#define CFG_Ecu_B1                      10U   // AL-Box2
#define CFG_Ecu_B2                      11U   // XALWA Flexray
#define CFG_Ecu_B3                      12U   // AL-Motion3
#define CFG_Ecu_B4                      13U   // ALTU-2
#define CFG_Ecu_B5                      14U   // Win32
#define CFG_Ecu_B6                      15U   // AL-Control3
#define CFG_Ecu_B7                      16U   // Led-Matrix
#define CFG_Ecu_C1                      17U   // V850-Fx4 Prototype
#define CFG_Ecu_Q1                      18U   // LED-ECU 4.1
#define CFG_Ecu_Q3                      19U   // LED-ECU 4.3
#define CFG_Ecu_D5                      20U   // AL-Control5


// -----------------------------------------------------------------------------
// operating-system type (CFG_TYP_OS)
#define CFG_Os_LitOS                     1U
#define CFG_Os_osCAN                     2U

// -----------------------------------------------------------------------------
// variant type (CFG_TYP_VAR)
#define CFG_Var_default                  1U
#define CFG_Var_TL                       2U   // used for Vw/Audi
#define CFG_Var_AMIS30621                3U   // used for Al11/Vo02
#define CFG_Var_EmcTest                  4U   // used for Alxx only
#define CFG_Var_LifeCycleTest            5U   // used for Alxx only
#define CFG_Var_L                        6U   // Left mounting position
#define CFG_Var_R                        7U   // Right mounting position
#define CFG_Var_ApplSWT                  8U   // used for Ch01
#define CFG_Var_DcApplIhcPlusDefault     9U   // Dc52 IHC+ application
#define CFG_Var_DcApplMarkerLight       10U   // Dc52 marker light configuration
#define CFG_Var_AlApplHbpDefault        11U   // Dc52 AL HighBeam assist|plus
#define CFG_Var_DefaultAfxStd           12U   // Dc52 AL Std Afx Shutter
#define CFG_Var_rta                     13U   // Runtime analysis

// -----------------------------------------------------------------------------
// mode type (CFG_TYP_MOD)
#define CFG_Mod_App                      1U   // default (application)
#define CFG_Mod_Fbl                      2U   // flash boot loader
#define CFG_Mod_Pbl                      3U   // primary boot loader
#define CFG_Mod_Sbl                      4U   // secondary boot loader

// -----------------------------------------------------------------------------
// hardware

// version (CFG_TYP_HW)
#define CFG_Hw_A0                        1U
#define CFG_Hw_B0                        2U
#define CFG_Hw_B1                        3U
#define CFG_Hw_C0                        4U
#define CFG_Hw_C1                        5U

// hardware options (CFG_OPT_HW)
#define CFG_Hw_DoCheck              0x0001U

// driver (CFG_DRV_...)
#define CFG_Drv_None                     1U
#define CFG_Drv_Default                  2U
// driver (CFG_DRV_SER and CFG_DRV_SER2)
#define CFG_Drv_Extended                 3U
// driver (CFG_DRV_PSENS)
#define CFG_Drv_Alternative1             4U
#define CFG_Drv_Alternative2             5U

// -----------------------------------------------------------------------------
// types and options concerning complete system

// type of ECU Part Number (CFG_TYP_ECUPARTNO)
#define CFG_EcuPartNo_10Digits          1U  // ECU Part Number: 10 digits
#define CFG_EcuPartNo_Use10of12Digits   2U  // ECU Part Number: 10 digits used,
                                            //   (2 digits unused in EEPROM)
#define CFG_EcuPartNo_12Digits          3U  // ECU Part Number: 12 digits

// type of ECU Running Number (CFG_TYP_ECURUNNINGNO)
#define CFG_EcuRunningNo_4Digits        1U  // ECU Running Number: 4 digits
#define CFG_EcuRunningNo_6Digits        2U  // ECU Running Number: 6 digits


// (CFG_OPT_SYSTEM) options concerning complete system
#define CFG_System_DisHlFactory          0x0001U  // disable headlamp factory services
#define CFG_System_DisRomChecksum        0x0002U  // disable rom checksum (remove code)
#define CFG_System_SuppEngineState       0x0004U  // use engine state for start of referencing


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

// -----------------------------------------------------------------------------
// type of ECU mode coding (CFG_TYP_ECUMODE)

#define CFG_EcuMode_NoHwCoding                1U       // no hardware coding of ECU mode
#define CFG_EcuMode_Prj                       2U       // implemented in PRJ area
#define CFG_EcuMode_SensPinDefault            3U       // default coding by Sens0 / Sens1
#define CFG_EcuMode_MsePinDefault             4U       // default coding by MSE Pin using bridge top Vccx or GND
#define CFG_EcuMode_MsePinAnalog              5U       // analog detection of IN1 Pin using bridge to Vps or GND

// ECU mode options (CFG_OPT_ECUMODE)
#define CFG_EcuMode_ExtModeAnalog        0x0001U       // extended ECU mode on pin IN2 using bridge to Vps or GND

// -----------------------------------------------------------------------------
// light function (CFG_TYP_GDLC) and (CFG_OPT_GDLC)

#define CFG_Gdlc_None                         1U
#define CFG_Gdlc_Default                      2U
#define CFG_Gdlc_LongVoltDropTimeBurnMode     3U

// -----------------------------------------------------------------------------
// light function CFG_OPT_GDLC_13V

#define CFG_Gdlc_NoSwitchOff                  1U   // do not switch off light because of U13V failure during 400Hz-operation
#define CFG_Gdlc_SwitchOff                    2U   // switch off light, if U13V has a malfunction in 400Hz-operation

// -----------------------------------------------------------------------------
// light function CFG_OPT_GDLC_EC11Delay  (Open Circuit Z-)

#define CFG_Gdlc_EC11Default                  1U   // Gdlc error EC11 is logged immediately
#define CFG_Gdlc_EC11DelayActive              2U   // Gdlc error EC11 is logged with 2s delay

// -----------------------------------------------------------------------------
// Eeprom

// (CFG_OPT_EEP)
#define CFG_Eep_NotUseFixData                 0x0001U

// (CFG_OPT_EEP_PSEUDODATA)
// take pseudo Eeprom data
//      addionally as project specific data
#define CFG_Eep_Pseudo_PrjData                0x0001U
//   or instead of real (once or tripple) data
#define CFG_Eep_Pseudo_EcuFuncModeFlags       0x0002U
#define CFG_Eep_Pseudo_HeadlampPara           0x0004U
#define CFG_Eep_Pseudo_InputOutputConfig      0x0008U
#define CFG_Eep_Pseudo_SysLoadInfo            0x0010U

// -----------------------------------------------------------------------------
// ECU functions / CTRL

// CFG_TYP_LIT_THIS
#define CFG_Lit_This_None                     1U
#define CFG_Lit_This_Dynamic                  2U
#define CFG_Lit_This_Master                   3U
#define CFG_Lit_This_Slave                    4U


// CFG_AUTO_TYP_ECUFUNC
#define CFG_EcuFunc_None                      1U
#define CFG_EcuFunc_Default                   2U

// CFG_OPT_ECUFUNC
#define CFG_EcuFunc_SuppEcuFuncModeFlags 0x0001U  // support EcuFuncModeFlags
                                                  //   see EepType.h for details
                                                  // support External Function Control
#define CFG_EcuFunc_SuppExtDblcCtrl      0x0010U  // Dblc
#define CFG_EcuFunc_SuppExtTlcCtrl       0x0020U  // Tlc
#define CFG_EcuFunc_SuppExtPvoCtrl       0x0040U  // Pvo
#define CFG_EcuFunc_SuppExtAvacCtrl      0x0080U  // Avac



// AVAC types (CFG_TYP_AVAC)
#define CFG_Avac_None                    1U
#define CFG_Avac_Prj                     2U
#define CFG_Avac_Dyn0                    3U   // otp2rt: DELETE
#define CFG_Avac_Dyn1                    4U
#define CFG_Avac_Stat1                   5U   // static  AVAC similar to Litronic 4
#define CFG_Avac_DynAdv1                 6U

// AVAC options (CFG_OPT_AVAC)
#define CFG_Avac_SupportHDDelay     0x0001U   // supported by CFG_AvacDyn1
#define CFG_Avac_SupportHeightCorr  0x0002U   // supported by CFG_AvacDyn1
#define CFG_Avac_SupportInvalidFlag 0x0004U   // supported by CFG_AvacDyn0 and ..1
#define CFG_Avac_DisAtSpeedFailure  0x0008U   // supported by CFG_AvacStat1
#define CFG_Avac_UseFixSafetyPos    0x0010U   // supported by CFG_AvacStat1
#define CFG_Avac_IgnoreStt          0x0020U   // STT-Config has no influence on AVAC
#define CFG_Avac_ActPosAtLbOff      0x0040U   // don't move to static pos at LB off

// VDDAVAC types (CFG_TYP_VDDAVAC)
#define  CFG_VddAvac_None                1U
#define  CFG_VddAvac_Basic               2U
#define  CFG_VddAvac_Advanced            3U

// Avac Algorithms (CFG_TYP_ALGAVAC)
#define  CFG_AlgAvac_None                1U
#define  CFG_AlgAvac_Stat1               2U
#define  CFG_AlgAvac_Dyn0                3U
#define  CFG_AlgAvac_Dyn1                4U

// VDD types (CFG_TYP_VDD)
#define CFG_Vdd_None                     1U
#define CFG_Vdd_Basic                    2U

// -----------------------------------------------------------------------------
//   the following configuration switches will be changed from AUTO to normal
//

// HLD options (CFG_OPT_HLD)
#define CFG_Hld_CoursePara1              1U    // use a simple multiplication for the mapping STW -> C
#define CFG_Hld_CoursePara2              2U    // use linear interpolations for the mapping STW -> C (Variolenkung)

// VDDHLD types (CFG_TYP_VDDHLD)
#define CFG_VddHld_None                  1U
#define CFG_VddHld_Basic                 2U

// VDDHLD option curvature mixer (CFG_OPT_VDDHLD_CUR_MIXER)
#define CFG_VddHld_CurMixerOff           1U
#define CFG_VddHld_CurMixer1             2U   // mixes curvature to 40% Curvature and 60% CurvatureOpt
#define CFG_VddHld_CurMixer2             4U   // mixes curvature according EEPROM parameter

// VDDHLD option dynamic evaluation (CFG_OPT_VDDHLD_EVAL_DYNAMIC)
#define CFG_VddHld_EvaluateDynamicOff    1U
#define CFG_VddHld_EvaluateDynamic1      2U

// VDDHld option steering wheel angle filtering (CFG_OPT_VDDHLD_SWA_FILTER )
#define CFG_VddHld_SWA_Filter_DES        1U      // design filter , IIR filter or FIR filter different parameters
#define CFG_VddHld_SWA_Filter_IIR        2U      // IIR    filter selected (default)
#define CFG_VddHld_SWA_Filter_FIR        3U      // FIR    filter selected

// VDDHld option yaw rate filtering (CFG_OPT_VDDHLD_YR_FILTER )
#define CFG_VddHld_YR_Filter_DES         1U      // design filter , IIR filter or FIR filter different parameters
#define CFG_VddHld_YR_Filter_IIR         2U      // IIR    filter selected (default)
#define CFG_VddHld_YR_Filter_FIR         3U      // FIR    filter selected
#define CFG_VddHld_YR_Filter_IIR2        4U      // IIR2   filter selected


// CL types (CFG_TYP_CL)
#define CFG_Cl_None                      1U
#define CFG_Cl_AlgPrj                    2U
#define CFG_Cl_Alg1                      3U
#define CFG_Cl_Alg2                      4U
#define CFG_Cl_Alg3                      5U

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
// slope calculation options
#define CFG_Cl_EndSlopeQuickBack         0x0100U  // end slope quick back option
// idle range options
#define CFG_Cl_IdleRangeAlg2             0x0200U  // extended idle range algorithm
// swivelling rate limiter 2
#define CFG_Cl_SwiRateLim2               0x0400U  // extended swivelling rate limiter
#define CFG_Cl_TouristActivation         0x0800U  // if set, DBL does *not* depend on the tourist mode;
                                                  // if not set, DBL can be active with a deactived tourist mode only
#define CFG_Cl_ActivateWithZeroCurvature   0x4000U  // DBL can be activated only if the curvature is zero
#define CFG_Cl_DeactivateWithZeroCurvature 0x8000U  // DBL can be deactivated only if the curvature is zero

// CL Option 2 (CFG_OPT_CL2)
#define CFG_Cl_ActivateWithMotor        0x0001U   // Activate DBL only if the engine has been started

// TLC types (CFG_TYP_TCL)
#define CFG_Tlc_None                     1U
#define CFG_Tlc_AlgPrj                   2U
#define CFG_Tlc_Alg1                     3U
#define CFG_Tlc_Alg2                     4U
#define CFG_Tlc_Alg3                     5U
#define CFG_Tlc_Alg4                     6U

// TLC Option (CFG_OPT_TLC)
#define CFG_Tlc_SupportC                  0x0001U  // support conering light
#define CFG_Tlc_SupportSBL                0x0002U  // support static bending light
#define CFG_Tlc_SupportCSBL               0x0004U  // support overlay of conering and static bending light
#define CFG_Tlc_SupportLightSourceLimited 0x0008U  // support light source limited
#define CFG_Tlc_SupportXOffRamp           0x0010U  // support extended OFF ramp
#define CFG_Tlc_TouristActivation         0x0020U  // if set, TL does *not* depend on the tourist mode;
                                                   // if not set, TL can be active with a deactived tourist mode only
#define CFG_Tlc_SpeedOutput               0x0040U  // support output of target light value and change rate of light
#define CFG_Tlc_ReverseBoth               0x0080U  // both cornering lamps are switched on while driving reverse

// PVO types (CFG_TYP_PVO)
#define CFG_Pvo_None                     1U
#define CFG_Pvo_Prj                      2U   // project specific pvo implementation
#define CFG_Pvo_Alg1                     3U   // Pvo full implementation with ML1
#define CFG_Pvo_Alg2                     4U   // Pvo full implementation with ML2
#define CFG_Pvo_Alg3                     5U   // AFS: Pvo AFS version with ML2 and new output variables AppOut2
#define CFG_Pvo_Alg4                     6U   // Pvo full implementation
#define CFG_Pvo_Full           CFG_Pvo_Alg1   // for compatibility with old projects


// PVO options (CFG_OPT_PVO)
#define CFG_Pvo_Speed1              0x0001U   // Pvo speed ramp
#define CFG_Pvo_Time1               0x0002U   // Pvo time ramp
#define CFG_Pvo_Tourist             0x0010U   // tourist mode implemented
#define Cfg_Pvo_Mc                  0x0020U   // motorway conditions
#define CFG_Pvo_FogLight            0x0040U   // extended fog light
#define CFG_Pvo_FogLight2           0x0080U   // AFX: extended fog light
#define CFG_Pvo_Tourist2            0x0100U   // AFX: tourist mode
#define CFG_Pvo_Ovac                0x0200U   // AFX: Optical Vertical Aim Control support (OVAC)
#define CFG_Pvo_Grd                 0x0400U   // AFX: Glare Reduction Detection support (GRD)
#define CFG_Pvo_Hba                 0x0800U   // AFX: Automatic High Beam support (HBA)
#define CFG_Pvo_Hb                  0x1000U   // AFX: High Beam support (HB2)
#define CFG_Pvo_FogLight3           0x2000U   // extended fog light with additional speed conditions as necessary in the US
#define CFG_Pvo_Hbp                 0x4000U   // AFX: High Beam Plus support (Hbp)
#define CFG_Pvo_Ext                 0x8000U   // AFX: External control of AFX actors

// PVO options (CFG_OPT_PVO2)
#define CFG_Pvo2_Hbm                0x0001U   // AFX: Marker Light support (Hbm)
#define CFG_Pvo2_Tnl                0x0002U   // AFS: Town Light (Tnl)
#define CFG_Pvo2_Psl                0x0004U   // AFS: Play Street Light (Psl)
#define CFG_Pvo2_Awl                0x0008U   // AFS: Adverse Weather Light (Awl)

// PVO options (CFG_OPT_PVO_ALG2 or CFG_OPT_PVO_ALG3)
#define CFG_Pvo_Support_classE3         0x0002U   // support class E3 light distribution
#define CFG_Pvo_Support_classV          0x0004U   // support class V  light distribution
#define CFG_Pvo_Support_MSpot           0x0008U   // support a spot light
#define CFG_Pvo_Support_Engine          0x0010U   // ML is disabled if engine is off, otherwise enabled
#define CFG_Pvo_Support_DistMeasurement 0x0020U   // ML changes light distributions based on distance measurements
#define CFG_Pvo_Support_TimeMeasurement 0x0040U   // ML changes light distributions based on time measurements
#define CFG_Pvo_Support_RoadCategories  0x0080U   // ML changes light distributions based on road categories
#define CFG_Pvo_Support_Rain            0x0100U   // ML changes light distributions based on rain information

// Ovac options (CFG_OPT_OVAC)
#define CFG_Ovac_Ver                0x0001U   // support vertical offsets (instead of shutter)
#define CFG_Ovac_EstimateCol        0x0002U   // estimate change over level from distance changes
#define CFG_Ovac_VerTopo            0x0004U   // support vertical offsets (in addition to shutter, e.g. topological adjustment)
#define CFG_Ovac_Statistics         0x0008U   // support statistical information

// Grd options (CFG_OPT_GRD)
#define CFG_Grd_Ver                 0x0001U   // support vertical offsets and LED devices

// Hba options (CFG_OPT_HBA)
#define CFG_Hba_Ver                   0x0001U   // support vertical offsets
#define CFG_Hba_CurvatureRestriction  0x0002U   // restrict vertical opening angle if the road is curvy

// Hb2 options (CFG_OPT_HB)
#define CFG_Hb_Ver                  0x0001U   // support vertical offsets
#define CFG_Hb_PowTarget            0x0002U   // support target power offsets (do not calculate power)

// HBp options (CFG_OPT_HBP)
#define CFG_Hbp_AreaDetection       0x0001U   // support area detection algorithm
#define CFG_Hbp_AngleLimitation     0x0002U   // support angle limitation algorithm
#define CFG_Hbp_TrafficDetection    0x0010U   // support traffic detection algorithm
#define CFG_Hbp_Camera2Headlamp     0x0020U   // support camera to headlamp angle transformation
#define CFG_Hbp_Statistic           0x0040U   // support statistic

// Tm options (CFG_OPT_TM, tourist mode)
#define CFG_Tm_ShowRef              0x0001U   // support show referencing

// -----------------------------------------------------------------------------

// Application Manager types (CFG_TYP_AM)
#define CFG_Am_None                     0u    // no Application Manager
#define CFG_Am_Default                  1u    // with default Application Manager
#define CFG_Am_Afs                      2u    // Application Manager for full AFS
#define CFG_Am_AfxVer                   3u    // Application Manager with AFX via vertical steppers

// Application Manager options (CFG_OPT_AM)
#define CFG_Am_Overtake_VerInc      0x0001u    // increments of vertical stepper are written into output messages
#define CFG_Am_Overtake_HorInc      0x0002u    // increments of horizontal stepper are written into output messages
#define CFG_Am_Overtake_ShtInc      0x0004u    // increments of shutter are written into output messages
#define CFG_Am_Overtake_PowInc      0x0008u    // increments of power offset are written into output messages
#define CFG_Am_HasExtCmd            0x0010u    // support of external commands?
#define CFG_Am_Statistics           0x0020u    // support statistics?

// CTRL types (CFG_TYP_CTRL)
#define CFG_Ctrl_None                    1U
#define CFG_Ctrl_Prj                     2U
#define CFG_Ctrl_Default                 3U

// CTRL options (CFG_OPT_CTRL)
#define CFG_Ctrl_StandAlone             0x0001U
#define CFG_Ctrl_NoGdlcError            0x0002U
#define CFG_Ctrl_NoVoltSync             0x0004U
#define CFG_Ctrl_StartRefSupport        0x0008U
#define CFG_Ctrl_DisAfsAtError          0x0010U
#define CFG_Ctrl_EnableSensErr          0x0020U     // activate sensor errors for Al01,2,3
#define CFG_Ctrl_NoRefTimeout           0x0040U     // do not use timeout if reference synchronization failed
#define CFG_Ctrl_EnPvoAtCl15Down        0x0080U
#define CFG_Ctrl_EnMotorAtCl15Down      0x0100U
#define CFG_Ctrl_EtoStopWithOffset      0x0200U
#define CFG_Ctrl_DisAfsAtAvacErr        0x0400U
#define CFG_Ctrl_SuppDynSwitching       0x0800U     // support different configurations (1/2 axes)
#define CFG_Ctrl_SupportShowMovement    0x1000U     // Support "WOW-Effect" (movement before referencing"
#define CFG_Ctrl_SuppSafetyPosRequest   0x2000U     // advice Ctrl to activate/release safety pos
#define CFG_Ctrl_WaitForRef             0x4000U     // activate EcuFunc only if all steppers are referenced
#define CFG_Ctrl_NewVoltConcept         0x8000U     // new generic volt-concept according PSA requirements

// more CTRL options (CFG_OPT_CTRL2)
#define CFG_Ctrl2_SupportAfxLoBmOff     0x0001U     // Must the light be switched off due to shutter and horizontal stepper failure, e.g. plug of AFX module has a defect (formerly known as CFG_Ctrl2_SupportSht0Hor0)
#define CFG_Ctrl2_ExtAdjustment         0x0002U     // Adjustment of headlamp with an EEPROM parameter
#define CFG_Ctrl2_SupportHeadlampPara4  0x0004U     // Use Headlamp para4 if the system has a shutter
#define CFG_Ctrl2_ExtRequests           0x0008U     // Support external requests (e.g. blackboard message CtrlRequestExt)
#define CFG_Ctrl2_Support2ndReactionTable 0x0010U   // Support a second reaction table. The reaction tables can be switched at run-time

// CTRL links (CFG_LNK_CTRL_VER0, CFG_LNK_CTRL_VER1, CFG_LNK_CTRL_HOR0, CFG_LNK_CTRL_HOR1, CFG_LNK_CTRL_LBM0, CFG_LNK_CTRL_LBM1)
#define CFG_LnkCtrl_None                0x0000U
#define CFG_LnkCtrl_MotorNone           0x0001U
#define CFG_LnkCtrl_Dcm                 0x0002U
#define CFG_LnkCtrl_StpVer0             0x0004U
#define CFG_LnkCtrl_StpVer1             0x0008U
#define CFG_LnkCtrl_StpHor0             0x0010U
#define CFG_LnkCtrl_StpHor1             0x0020U
#define CFG_LnkCtrl_StpSht0             0x0040U
#define CFG_LnkCtrl_StpSht1             0x0080U
#define CFG_LnkCtrl_StpExt              0x0100U
#define CFG_LnkCtrl_DcmExt              0x0200U
#define CFG_LnkCtrl_Xen0                0x0400U
#define CFG_LnkCtrl_Xen1                0x0800U
#define CFG_LnkCtrl_Tl0                 0x1000U
#define CFG_LnkCtrl_Tl1                 0x2000U

// definitions for type of axis-actuator  (CFG_AUTO_TYPE_Act...)
#define CFG_ActType_Stp                  1U
#define CFG_ActType_Dcm                  2U
#define CFG_ActType_None                 3U


// -----------------------------------------------------------------------------

// SIGPREP types (CFG_TYP_SIGPREP)
#define CFG_SigPrep_None                 1U
#define CFG_SigPrep_Prj                  2U
#define CFG_SigPrep_Default              3U
#define CFG_SigPrep_Evt                  4U

// SIGPREP types (CFG_OPT_SIGPREP)
#define CFG_SigPrep_NoEnvCond       0x0001U
#define CFG_SigPrep_OnlyEnvCond     0x0002U

// -----------------------------------------------------------------------------
// Communication

// CAN support
#define CFG_Can_None                     1U
#define CFG_Can_Default                  2U
#define CFG_Can_Volcano                  3U

// CFG_OPT_CAN_DIA
#define CFG_CAN_DIA_SUPPORT_RDM_SERVICES    0x0001U
// #define CFG_CAN_DIA_...

// LIN support
#define CFG_Lin_None                     1U     // LIN not present
#define CFG_Lin_9600Baud                 2U     // LIN present ( 9600 Baud)
#define CFG_Lin_19200Baud                3U     // LIN presend (19200 Baud)
#define CFG_Lin_Prj                      4U     // LIN project specific

#define CFG_Lin_Node_Master              0x00   // do not change!
#define CFG_Lin_Node_Slave1              0x01   // do not change!
#define CFG_Lin_Node_Slave2              0x02   // do not change!
#define CFG_Lin_Node_Extern              0x03   // do not change!

#define CFG_Lin_MsgTypeAsync             0x80   // do not change!

#define CFG_Lin_This_Dynamic             -1     // Type of this LIN-Node: dynamically detected
#define CFG_Lin_This_Master              CFG_Lin_Node_Master
#define CFG_Lin_This_Slave1              CFG_Lin_Node_Slave1
#define CFG_Lin_This_Slave2              CFG_Lin_Node_Slave2
#define CFG_Lin_This_Extern              CFG_Lin_Node_Extern

#define CFG_Lin_TaskMaster_None          1U
#define CFG_Lin_TaskMaster_Default       2U

#define CFG_Lin_NodeMaster_None          1U
#define CFG_Lin_NodeMaster_Default       2U

#define CFG_Lin_NodeSlave1_None          1U
#define CFG_Lin_NodeSlave1_Default       2U

#define CFG_Lin_NodeSlave2_None          1U
#define CFG_Lin_NodeSlave2_Default       2U

#define CFG_Lin_NodeExtern_None          1U
#define CFG_Lin_NodeExtern_Default       2U

// CFG_OPT_LIN
#define CFG_Lin_AsyMsc                   0x0001U
#define CFG_Lin_Gateway                  0x0002U
#define CFG_Lin_EcExt                    0x0004U
#define CFG_Lin_MasterTakeOver           0x0008U
#define CFG_Lin_2ndChannelAdded          0x0010U

// CFG_OPT_LIN2x_DIA
// (typically together with AL-internal LIN2x-Dia driver in use, by CFG_LIN2_0_PROTOCOL_IN_USE)
#define CFG_LIN2x_Dia_ServiceB0          0x0001U  // 0xB0 "Assign NAD" (LIN2.0 and LIN2.1 diagnostics)
#define CFG_LIN2x_Dia_ServiceB1          0x0002U  // 0xB1 "Assign Frame Identifier" - only LIN2.0 diagnostics
#define CFG_LIN2x_Dia_ServiceB7          0x0004U  // 0xB7 "Assign Frame ID Range" - only LIN2.1 diagnostics
// #define CFG_LIN2x_Dia_...
#define CFG_LIN2x_Dia_CH2_Enabled        0x0100U  // enable 2nd instance (channel) of LIN2.x diagnostics
#define CFG_LIN2x_Dia_CH2_SupportTP      0x0200U  // support TP for 2nd instance (channel) of LIN2.x diagnostics
// #define CFG_LIN2x_Dia_...
#define CFG_LIN2x_Dia_CH2_CommonLinProductId  0x2000U // common LIN Product ID value used for both channels of LIN2.x diagnostics
#define CFG_LIN2x_Dia_CH2_CommonNad      0x4000U  // common NAD used for both channels of LIN2.x diagnostics
#define CFG_LIN2x_Dia_NadByMountingSide  0x8000U  // NAD (of LIN diagnostcs) determined by mounting side detection (not as fix value)

// CFG_OPT_BICOM support
#define CFG_BiCom_HiLoErrDetect_On       0x0001U

// CFG_LNK_KTP (KeyWord200 pr.) and CFG_LNK_BICOM (BiCom pr.)
// CFG_LNK_DEVSERTEST (DevSerialPortTest) and CFG_LNK_DEBUG_OUTPUT (Debug output port) support.
#define CFG_LnkDrv_None                  1U   // Protocol is using no ser. Port
#define CFG_LnkDrv_HalBiCom              2U   // Protocol is using the simulated ser. Port (HalBiCom)
#define CFG_LnkDrv_HalSerExt             3U   // Protocol is using the real ser. Uart (HalSerExt)
#define CFG_LnkDrv_HalSer2Ext            4U   // Protocol is using the second real ser. Uart (HalSer2Ext)

// CFG_TYP_MSC: Master-Slave Communication Type
#define CFG_Msc_None                     1U
#define CFG_Msc_LitCom                   2U
#define CFG_Msc_CanCom                   3U
#define CFG_Msc_BiCom                    4U
#define CFG_Msc_FrCom                    5U

// CFG_OPT_MSC: options for Master-Slave Communication
#define CFG_Msc_2Slaves                  0x0001U
#define CFG_Msc_Amis                     0x0002U

// CFG_TYP_KTP
#define CFG_Ktp_None                     1U
#define CFG_Ktp_Type1                    2U       // KeyWord Pr. 2000 on KLine

// CFG_OPT_KTP
#define CFG_Ktp_DataLogging1             0x0001U  // Data Logging feature enabled

// CFG_TYP_XCP
#define CFG_Xcp_None                     1U
#define CFG_Xcp_Default                  2U
// -----------------------------------------------------------------------------
// Supported signals (messages)

// CFG_TYP_PITCH
#define CFG_Pitch_None                    1U
#define CFG_Pitch_Prj                     2U
#define CFG_Pitch_Cxd1                    3U
#define CFG_Pitch_CxdPrj                  4U
#define CFG_Pitch_IpdDefault              3U  // for backward compatibility: to be removed
#define CFG_Pitch_IpdPrj                  4U  // for backward compatibility: to be removed

// Pitch options
#define CFG_Pitch_NoOffset                0x0001U
#define CFG_Pitch_CheckSensorMounting     0x0002U
#define CFG_Pitch_RestrictedErrDetect     0x0004U
#define CFG_Pitch_SuppDynSwitching        0x8000U  // to be deleted !!

// Pitch algorithm
#define CFG_Pitch_DoubleSens              1U
#define CFG_Pitch_SingleSens              2U
#define CFG_Pitch_DoubleDisp              3U
#define CFG_Pitch_SingleDisp              4U
#define CFG_Pitch_Inclinat                5U

// Pitch links
// do not change order: symbols are used as indices
#define CFG_Sens_Ana0                     0U   // Sens0
#define CFG_Sens_Pwm0                     0U   // SensPwm0
#define CFG_Sens_Ana1                     1U   // Sens1
#define CFG_Sens_Pwm1                     1U   // SensPwm1
#define CFG_Sens_Ana2                     2U   // Sens2
#define CFG_Sens_Pwm2                     2U   // SensPwm2
#define CFG_Sens_Ana3                     3U   // Sens3
#define CFG_Sens_Pwm3                     3U   // SensPwm3
#define CFG_Sens_Ana4                     4U   // Sens4
#define CFG_Sens_Pwm4                     4U   // SensPwm4

// CFG_OPT_PWM: Options for PWM-Measurement
#define CFG_Pwm_Measurement               0x0001U   // Enable PWM measurement (results in special variables)
#define CFG_Pwm_ModeStartNeg              0x0002U   // Use negative slope for start of PWM measurement
#define CFG_Pwm_Use1kHzSensor             0x0004U   // Use Pwm-Sensor with 1kHz signal
#define CFG_PWM_UseHighTime               0x0008U   // Use high time of an inverted pwm signal (= CFG_Pwm_ModeStartNeg)
#define CFG_PWM_Higher_Resolution         0x0010U   // Normally the Pwm resolution is about 1% now it will be 0.01%
// CFG_PWM_MEASUREMENT_TYPE:
#define CFG_High_Width_Measurement        0U //High width measurement
#define CFG_Low_Width_Measurement         1U //Low width measurement

// IpdSpd types
#define CFG_Speed_None                    1U
#define CFG_Speed_Prj                     2U
#define CFG_Speed_IpdDefault              3U
#define CFG_Speed_Cxd1                    4U

// TrafficInfo
#define CFG_TrafficInfo_None              0u
#define CFG_TrafficInfo1                  1u
#define CFG_TrafficInfo2                  2u
#define CFG_TrafficInfo3                  3u

// MarkerInfo
#define CFG_MarkerInfo_None               0u
#define CFG_MarkerInfo1                   1u

// AfxCtrl
#define CFG_AfxCtrl_None                  0u
#define CFG_AfxCtrl1                      1u

// AfxEnv
#define CFG_AfxEnv_None                   0u
#define CFG_AfxEnv1                       1u

// Navigation
#define CFG_Navigation_None               0u
#define CFG_Navigation1                   1u

// -----------------------------------------------------------------------------
// actuators

// CFG_LNK_STPXXXn (XXXn = VER0, VER1, HOR0, HOR1, SHT0, SHT1) - for onboard steppers only
#define CFG_LnkDrv_StpNone                1U
#define CFG_LnkDrv_StpLwr                 2U
#define CFG_LnkDrv_StpKl                  3U
#define CFG_LnkDrv_StpGlw                 4U

// CFG_LNK_PSENSXXXn (XXXn = VER0, VER1, HOR0, HOR1, SHT0, SHT1)
// CFG_LNK_PSENSSTPEXTn (n = 0..3)
#define CFG_LnkDrv_PsensNone              1U
#define CFG_LnkDrv_PsensLwr               2U   // for onboard steppers only
#define CFG_LnkDrv_PsensKl                3U   // for onboard steppers only
#define CFG_LnkDrv_PsensGlw               4U   // for onboard steppers only
#define CFG_LnkDrv_PsensExt               5U   // for external steppers only

// CFA_OPT_STP - !automatic option!
#define CFG_Stp_UseSafetyPos         0x0001U   // stepper program uses safety pos

// CFG_TYP_DCM
#define CFG_Dcm_None                      1U
#define CFG_Dcm_Prj                       2U
#define CFG_Dcm_Cxd1                      3U

// CFG_OPT_DCM
#define CFG_Dcm_Reverse              0x0001U
#define CFG_Dcm_UseMaxAdjTimeData    0x0002U
#define CFG_Dcm_SuppLowHighError     0x0004U
#define CFG_Dcm_ReverseByParaFlag    0x0008U
#define CFG_Dcm_DirectPositioning    0x0010U

// CFG_TYP_TL
#define CFG_Tl_None                       1U
#define CFG_Tl_Default                    2U

// CFG_OPT_TL
#define CFG_Tl_RuntimeCfg            0x0001U
#define CFG_TL_NoLimit               0x0002U   // Keine Begrenzung der Aussgangsspannung
#define CFG_TL_LinearLimit           0x0004U   // Lineare Berechnung der Ausgangsspannung für maximale Ausgangsleistung
#define CFG_TL_ErrZeroPWMDetect      0x0008U   // Error detection at 0%PWM
#define CFG_TL_ErrPowerOnClear       0x0010U   // Clear the errors through complete Cl.15 cycle
#define CFG_TL_DynHwRecognition      0x0020U   // dyn. recognition of C2/C3 hardware changes
#define CFG_TL_SuppDynSwitching      0x0040U   // dyn parametr. of IpdTl
#define CFG_TL_ErrVSBLOff            0x0080U   // voltage supply will be switched off if error is detected
#define CFG_TL_PowerSupplyMismatch   0x0100U   // PWM-Error detecting if Power Supply is out of range


//CFG_OPT_GDLC
#define CFG_GDLC_Default             0x0001U
#define CFG_GDLC_CustBurnTime        0x0002U   // customer LampBurnTime can be reseted by diagnose
#define CFG_GDLC_CustAsymLight       0x0004U   // customer timind definition  of Asymetric Light error

//CFG_OPT_GDLC
#define CFG_BFL_Default              0x0001U
#define CFG_BFL_HighBeamOffset       0x0002U   // add 2,5[W]Poweroffset on GDL for active Highbeam

// CFG_TYP_EL
#define CFG_El_None                       1U
#define CFG_El_Led                        2U
#define CFG_El_Xenon                      3U

// CFG_OPT_EL
//#define CFG_EL_???                  0x0001U


// CFG_TYP_LM  (Lin Manager )
#define CFG_Lm_None                      1U
#define CFG_Lm_Prj                       2U
#define CFG_Lm_Default                   3U

// CFG_OPT_LM
#define CFG_Lm_Diag                  0x0001U   // LIN diagnostic is used

// -----------------------------------------------------------------------------
// Clamp definition

#define CFG_ClUnbound                0xFFFFU   // do not change the values, the values are
#define CFG_Cl15                     0x0000U   // used as index in the SysVolt module !!!!!
#define CFG_Cl30                     0x0001U
#define CFG_Cl56b                    0x0002U
#define CFG_Cl56a                    0x0003U
#define CFG_Cl15or56b                0x0004U
#define CFG_ClVAbl                   0x0005U   // clamp is used for TL supply only
#define CFG_GdlU13                   0x0006U

#define CFG_ClVccx                   0x0007U
#define CFG_ClVps                    0x0008U

#define CFG_ClMaxCnt                 0x0009U   // this mut be the last vaule for array definitions

//CFA_OPT_CLAMP_USAGE (clamp options)

#define CFG_ClUsed_Cl15              0x0001U
#define CFG_ClUsed_Cl30              0x0002U
#define CFG_ClUsed_Cl56b             0x0004U
#define CFG_ClUsed_Cl56a             0x0008U
#define CFG_ClUsed_Cl15or56b         0x0010U
#define CFG_ClUsed_ClVAbl            0x0020U
#define CFG_ClUsed_GdlU13            0x0040U

#define CFG_ClUsed_ClVccx            0x0080U
#define CFG_ClUsed_ClVps             0x0100U

//CFG_OPT_CLAMP
#define CFG_Clamp_ExtCl15            0x0001U   // use an extended state machine in SysVolt

// -----------------------------------------------------------------------------
// Err characteristics

// customer error logging types (CFG_TYP_ERRCUST)
#define CFG_ErrCust_None                  1U   // only AL-internal error logging,
                                               // no project specific error logging

#define CFG_ErrCust_Prj                   2U   // project specific error logging


// customer error logging options (CFG_OPT_ERRCUST)
#define CFG_ErrCust_SupportInitFct          0x0001U
#define CFG_ErrCust_SupportSetStatusFct     0x0002U
#define CFG_ErrCust_SupportHandlingFct      0x0004U
#define CFG_ErrCust_SupportCntInterpretFct  0x0008U
#define CFG_ErrCust_SupportDisEnable        0x0010U
#define CFG_ErrCust_SupportLinVState        0x0020U
#define CFG_ErrCust_SupportAlarm1           0x0040U
#define CFG_ErrCust_SupportAlarm2           0x0080U
#define CFG_ErrCust_SupportAlarm3           0x0100U
#define CFG_ErrCust_SupportAlarm4           0x0200U
#define CFG_ErrCust_SupportClearSingleError 0x0400U

// configure project specific error counting (CFG_OPT_ERRCNT)
#define CFG_ErrCnt_PrjEntries               0x0001U
#define CFG_ErrCnt_SupportInitSingleCounter 0x0002U
#define CFG_ErrCnt_SuspendIncrement         0x0004U
#define CFG_ErrCnt_SupportMomentErrInfo     0x0008U
#define CFG_ErrCnt_DiscardErrCnt            0x0010U
#define CFG_ErrCnt_SuspendDecrement         0x0020U

// configure project specific error logging (CFG_OPT_ERRLOG)
#define CFG_ErrLog_PrjEntries               0x0001U
#define CFG_ErrLog_ReadAccessAlEcStatus     0x0002U
#define CFG_ErrLog_2ByteAlEc                0x0004U

// -----------------------------------------------------------------------------
// CFG_OPT_PBLSBL
#define CFG_PblSbl_None                     0x0000U
#define CFG_PblSbl_DualChannel              0x0001U
#define CFG_PblSbl_SoftIsp                  0x0002U

// -----------------------------------------------------------------------------
// extensions for development and application

// stepper options (CFG_OPT_STP)
#define CFG_Stp_SupportSlaveAddr          0x0001U   // support different addresses depending on master/slave selection
#define CFG_Stp_IgnoreMissingPsens        0x0002U   // no position error if Psens missing
#define CFG_Stp_UseInvPsensPol            0x0004U   // use of dynamic configuration of interface function CxdStpXxx0/1_InvertPsensPolarity()
#define CFG_Stp_PsensDiag                 0x0008U   // diagnosis of position sensor available
#define CFG_Stp_SwitchPsensSigDiag        0x0010U   // CFG_Stp_PsensDiag without position sensor signal diagnosis and possibility to switch on by using CxdStpXxx0/1_SwitchPsensSignalDiag()
#define CFG_Stp_PosCorr                   0x0020U   // use position correction on LIN based systems (all onboard systems use position correction)
#define CFG_Stp_TimeoutLock               0x0040U   // lock timeout state after timeout error entry
#define CFG_Stp_OnAfterPowerOn            0x0080U   // switch on driver immediately after power on (Teststeps and hold current)

// CFG_TYP_STPXXXn (XXXn = VER0, HOR0, SHT0)
#define CFG_Stp_None                      1U
#define CFG_Stp_Prj                       2U
#define CFG_Stp_9942                      3U   // ST L9942
#define CFG_Stp_705XX                     4U   // ON NCV705XX
#define CFG_Stp_706XX                     5U   // ON NCV706xx (as external stepper via LIN-subbus)

// statistic options (CFG_OPT_STATISTIC)
#define CFG_Statistic_ExtendedStpLwr        0x0001U
#define CFG_Statistic_ExtendedStpKl         0x0002U
#define CFG_Statistic_ExtendedStpGlw        0x0004U
#define CFG_Statistic_ExtendedTl            0x0008U

// *****************************************************************************
// Additional switches (for temporary use)
// *****************************************************************************
// (CFG_OPT_DEV) options concerning special test/monitor features.
#define CFG_Dev_ActorRemote                   0x0001U
#define CFG_Dev_EepromReadOrWriteTest         0x0002U
#define CFG_Dev_SensorToActuator              0x0004U
#define CFG_Dev_FreeSpare03                   0x0008U

// Bit mask for the feature of scanning/sampling the min max ADC-Values
#define CFG_Dev_ADValuesSampleMinMaxEnabled   0x0010U
#define CFG_Dev_FreeSpare05                   0x0020U
#define CFG_Dev_FreeSpare06                   0x0040U
#define CFG_Dev_FreeSpare07                   0x0080U

#define CFG_Dev_FreeSpare08                   0x0100U
#define CFG_Dev_ActHorVertStepPosCycle        0x0200U
#define CFG_Dev_ActHorVertStepPosAsynchr      0x0400U
#define CFG_Dev_SerialPortTest                0x0800U

#define CFG_Dev_LinStatistic                    0x1000U
#define CFG_Dev_SystemLoad                      0x2000U
#define CFG_Dev_CanCtrlSetActorRemoteAutomatic  0x4000U
#define CFG_Dev_CanCtrlMsg                      0x8000U
//#define CFG_Dev_SpeedFrequInput                 0x4000U
//#define CFG_Dev_WatchDogTest                    0x8000U

// -----------------------------------------------------------------------------
// Debug options (CFG_OPT_DEBUG)

#define CFG_DebugIrLoadRam        0x00000001UL
#define CFG_DebugIrLoadPin        0x00000002UL
#define CFG_DebugTaskLoadPin      0x00000004UL
#define CFG_DebugFreeBit3         0x00000008UL

#define CFG_DebugCANStpControl    0x00000010UL    // receive stepper target position via CAN
#define CFG_DebugCANStpInfo       0x00000020UL    // send stepper info via CAN
#define CFG_DebugWdtTest          0x00000040UL    // watchdogtest-function
#define CFG_DebugFreeBit7         0x00000080UL
#define CFG_DebugDisDataFlash     0x00000100UL    // no data flash support (for IE-Cube)

#define CFG_DebugSPI              0x00001000UL    // SPI-Statistic
#define CFG_DebugTemperature      0x00002000UL    // Temperature state machine test
#define CFG_DebugSM_Test          0x00004000UL    // Stepper motor test (MV)
#define CFG_DebugStp_Test         0x00008000UL    // Stepper test
#define CFG_DebugIN2              0x00010000UL    // Trigger IN2
#define CFG_DebugSD               0x00020000UL    // StallDetection

// Debug options (CFG_OPT_RDM)
#define CFG_RdmNone              0U
#define CFG_RdmSinglePin         1U
#define CFG_RdmSinglePinLite     2U
#define CFG_RdmSinglePinReadOnly 3U

// Following debug options can not be used together !!!
// (Monitoring information uses the same CAN Message!!)
#define CFG_DebugCANAfsMonitor    0x01000000UL    // send AFS monitoring information
#define CFG_DebugCANGdlMonitor    0x02000000UL    // send GDL monitoring information
#define CFG_DebugMonMsgEnable     0x04000000UL    // enable generic debug message DebugMonMsg1
                                                  //                              DebugMonMsg2
#define CFG_DebugAfsMonitorDblc   0x08000000UL    // monitor DBLC in DebugMonMsg

#define CFG_DebugFreeBit12        0x10000000UL
#define CFG_DebugCANAvacMonitor   0x20000000UL    // send AVAC monitoring information via CanMsgTransmit(...)
#define CFG_DebugCANSensorMonitor 0x40000000UL    // send sensor raw-values via CAN
#define CFG_DebugMaskBB           0x80000000UL    // enable BlackBoard Read/Write Masks


// -----------------------------------------------------------------------------
//Performance Analysis options (CFG_Performance_Analysis)
#define CFG_Performance_None                     (0x00000000U)
//Used only for task timing using timers
#define CFG_Performance_TaskTiming               (0x00000001U)
//Used only for CPU loading using timers
#define CFG_Performance_CPULoading               (0x00000002U)
//Used for measurments of PowerUp and ShutDown parameters using timers
#define CFG_Performance_PowerUpShutDown          (0x00000004U)
//Used for measurments of PowerUp and ShutDown parameters using an Oscilloscope
#define CFG_Performance_PowerUpShutDown_Pins     (0x00000008U)
//Used only for Memory Stack measurements
#define CFG_Performance_MemoryUsage              (0x00000010U)
//Used only for measuring the ISRs loads using timers
#define CFG_Performance_ISR                      (0x00000020U)
//Used only for measuring the ISRs loads using an Oscilloscope
#define CFG_Performance_ISR_Pins                 (0x00000040U)
//Used only for runnables measurment using timers
#define CFG_Performance_Runnables                (0x00000080U)


// SysLoad options (CFG_OPT_SYSLOAD)
#define CFG_SysLoad_None                         (0x00000000U)
#define CFG_SysLoad_SystemLoad                   (0x00000001U)
#define CFG_SysLoad_IrqLatency                   (0x00000002U)
#define CFG_SysLoad_TaskLoad                     (0x00000004U)
#define CFG_SysLoad_RunableLoad                  (0x00000008U)
#define CFG_SysLoad_RunableEvents                (0x00000010U)
#define CFG_SysLoad_ISRLoad                      (0x00000020U)
#define CFG_SysLoad_StackInitTest                (0x00000040U)
#define CFG_SysLoad_PowerUp_ShutDown             (0x00000080U)

// SysLoad Type options (CFG_OPT_SYSLOAD_TYP)
#define CFG_OPT_SYSLOAD_TYP_NONE                 (0x00000000U)
#define CFG_OPT_SYSLOAD_TYP_OSEK                 (0x00000001U)
#define CFG_OPT_SYSLOAD_TYP_RTE                  (0x00000002U)
#define CFG_OPT_SYSLOAD_TYP_OSEK_RTE             (0x00000004U)


// -----------------------------------------------------------------------------
// External Led devices (CFG_TYP_EXTLED)

#define CFG_ExtLed_None                          (0x00000000U)
#define CFG_ExtLed_LAM2                          (0x00000001U)

// Support of Win32 DLL
// intentionally left empty
#define CFG_Dll_None
// imports and exports
#if defined(_WIN32) || defined(_WIN64)
#define CFG_Dll_Import                            __declspec(dllimport)
#define CFG_Dll_Export                            __declspec(dllexport)
#endif

// CFG_OPT_SBC
#define CFG_Sbc_NoCommEnable      0x00000001UL    // no support of COMM_ENABLE wake up pin

// project class (CFG_TYP_PRJ2)
#define CFG_Prj_Led_Matrix_5_1   0x01
#define CFG_Prj_Mlcc             0x02
#define CFG_Prj_LED_6_1          0x03
#define CFG_Prj_LED_6_2          0x04

// configuration of SBC LIN/V2/HVIO5 to HVIO8  (CFG_SBC_LIN1, CFG_SBC_LIN2, CFG_SBC_V2S, CFG_SBC_HVIO5..8_USE)
#define CFG_SBC_FUNCTION_USED         0x01
#define CFG_SBC_FUNCTION_NOT_USED     0x02

// configuration of HVIO1 to HVIO4 (CFG_SBC_HVIO1..4_TYPE)
#define CFG_SBC_HVIO_NOT_USED         0x00
#define CFG_SBC_HVIO_HSS              0x01
#define CFG_SBC_HVIO_LSS              0x02
#define CFG_SBC_HVIO_PWM              0x03

// configuration of HVIO Wake-Up Threshold Config (CFG_SBC_WTC_TYPE)
#define CFG_SBC_WTC_RATIO             0x00
#define CFG_SBC_WTC_ABS               0x01

// -----------------------------------------------------------------------------
// include project specific type definitions (see CfgPrj.h)


// generic config TRUE/FALSE
#define CFG_TRUE  1U
#define CFG_FALSE 0U

// CFG_OPT_SLEEP
#define CFG_Sleep_Disable             0x00  // Diasable sleep function
#define CFG_Sleep_Enable              0x01  // Enable sleep function
#define CFG_Sleep_Cust                0x02  // Enable customer specific sleep function

// SBC TLE9263QX SBC_CFG_ERRATA_POSSOL
#define ERRATA_NO_POSSOL              0x00  // No solution selected for SBC sleep mode error
#define ERRATA_POSSOL_2               0x01  // Possible solution 2 selected for SBC sleep mode error
#define ERRATA_POSSOL_3               0x02  // Possible solution 3 selected for SBC sleep mode error

// PHD / DLP Power ECU Hardware
#define CFG_PHD_HW_UNKNOWN            0x00  // unknown hardware
#define CFG_PHD_HW_EVALBOARD          0x01  // Evaluation Board
#define CFG_PHD_HW_A_SAMPLE           0x02  // DLP-Power A-Sample (INE)
#define CFG_PHD_HW_B_SAMPLE           0x03  // PHD B2-Sample

// ILS Location, Run on ECU or externally using CAN
#define CFG_ILS_UNKNOWN               0x00
#define CFG_ILS_INTERNAL_IN_ECU       0x01
#define CFG_ILS_EXTERNAL_ON_CAN       0x02

// Eviyos project variant
#define CFG_EVIYOS_VAR_UNKNOWN        0x00
#define CFG_EVIYOS_VAR_INTERIOR_LIGHT 0x01
#define CFG_EVIYOS_VAR_HEADLAMP       0x02

// Matrix Types
#define CFG_MATRIX_TYPE_NONE          0x00 // Matrix type - none
#define CFG_MATRIX_TYPE_1             0x01 // Matrix with 12 Segments
#define CFG_MATRIX_TYPE_2             0x02 // Matrix with 84 Segments

// IARA Type
#define CFG_IARA_CAR_MODEL_UNKNOWN    0x00
#define CFG_IARA_CAR_MODEL_DAI_W177   0x01
#define CFG_IARA_CAR_MODEL_PSA_X74    0x02

#endif //_CFGTYPE_H
