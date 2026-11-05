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
/// \file    RteCommonTypes.h
///
/// \brief   Typedefinitions for Rte-Structures
//-----------------------------------------------------------------------------

#ifndef _RTE_COMMONTYPES_H
#define _RTE_COMMONTYPES_H

//=============================================================================
// includes
//=============================================================================

#include <Std_Types.h>
#include <Cfg/Cfg.h>
#include <Dem.h>
// To be removed when rte client ports are available
#include <CodM_Para.h>
#include <CodM_Types.h>
#include <LgmEIMMainAPI.h>

#ifndef UNIT_TEST
#include <CddLed.h>
#include <CddBoost.h>
#include "CommonTypes.h"
#include "ConfigE2E.h"
#include "_NM_Types.h"
#else

#endif // !UNIT_TEST

// To be removed when rte client ports are available

#ifndef tieDataStatus_Invalid
#define tieDataStatus_Invalid 0U
#endif /*tieDataStatus_Invalid*/

#ifndef tieDataStatus_Valid
#define tieDataStatus_Valid 1U

#endif

#ifndef SUPPORT_YES
#define SUPPORT_YES 1U
#endif /*SUPPORT_YES*/

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
#define CFG_OUTPUT_HSS  4u
#else
#define CFG_OUTPUT_HSS  2u
#endif

#define CFG_ERR_HSS  3u

//=============================================================================
// Data type definitions
//=============================================================================
typedef unsigned short UInt10;

typedef unsigned short UInt11;

typedef unsigned short UInt12;

typedef unsigned short UInt13;

typedef unsigned short UInt14;

typedef unsigned short UInt15;

typedef unsigned short UInt9;

typedef unsigned char tieDataStatus;

typedef unsigned short VYAW_VEH;

typedef unsigned short V_VEH_COG;

typedef unsigned short WdgM_CheckpointIdType;

typedef unsigned short WdgM_SupervisedEntityIdType;

typedef unsigned short tiu16Angle_1_10degree;

typedef unsigned short tiu16BinNtcErrorBitMaskIoChannel;

typedef unsigned short tiu16Current_mA;

typedef signed int tis32Temperature_mCelsius;


typedef unsigned short tiu16StepperPosition_degree;

typedef unsigned short tiu16StepperSpeed_degreesPerSecond;

typedef signed short ti16StepperPosition_halfsteps;

typedef unsigned short tiu16TimeDiff_ms;

typedef unsigned char tieSigQty;

typedef unsigned char tieStatMData_Id;

typedef unsigned char tieStatusOnOff;

typedef unsigned char tieStepperIndex;

typedef unsigned char tieStepperState0;

typedef unsigned char tieStpTempMode;

typedef unsigned char tieSupportInfo;

typedef uint8 aucValStp[7];

typedef uint8 tieSigQty0;



typedef unsigned char tucEftDataHwStatus;

typedef unsigned short tun16Percent_1_328;

typedef unsigned short tRteSwitchTgtVal;

typedef unsigned char tucError;


typedef unsigned short tiu16StepPeriod_microseconds;


typedef unsigned char tieCtrSleepMode;

typedef enum
{
  eRte_ScrollingSatelite_Off = 0,
  eRte_eScrollingSatelite_On_Scrolling_Off = 1,
  eRte_eScrollingSatelite_On_Scrolling_On = 2
}teRte_SateliteStatus;

typedef enum
{
  eRte_eScrollingTgt_Off = 0,
  eRte_eScrollingTgt_On_Scrolling_Off = 1,
  eRte_eScrollingTgt_On_Scrolling_On = 2
}teRte_ScrollingTgt;

// -----------------------------------------------------------------------------
// Signal quality
typedef enum
{
  SIG_SNA = 0U,
  SIG_VALID = 1U,
  SIG_INIT = 2U,
  SIG_INVALID = 3U,
  SIG_TIMEOUT = 4U,
  SIG_DEFAULT = 5U,
  SIG_E2E_CRCERR = 6U,
  SIG_E2E_ALIVEERR = 7U,
  SIG_E2E_TIMEOUT = 8U,
  SIG_UNAVAILABLE = 9U,
  SIG_DISABLED = 255U
}teRte_SigQty;

typedef struct
{


  tieSupportInfo eStatSupported;




  boolean boInitActive;




  boolean boIsOn;




  boolean boIsReady;




  boolean boIsMoving;




  boolean boRefActive;




  boolean boIsRef;




  boolean boLowTemp;




  tieStpTempMode eTempMode;




  boolean boIsFatalError;




  boolean boVoltNorm;




  boolean boStepLoss;




  boolean boCommDefect;




  boolean boElecOL;




  boolean boElecSC;




  boolean boVoltUSSM;



  boolean boVoltUVShtDwn;



  boolean boVoltOver;



  boolean boOverTempShtDwn;
}tisStpStatusError;
typedef struct
{


  ti16StepperPosition_halfsteps nPosition;




  tiu16StepPeriod_microseconds nStepPeriod;




  tisStpStatusError sStatusError;


}tisStpActual;

typedef struct
{


  tisStpActual sLwrActual;


}tsRte_CddStpActual;

typedef struct
{


  ti16StepperPosition_halfsteps nPosition;




  boolean boStop;




  tiu16StepPeriod_microseconds unMinStepPeriod;


}tisStpTarget;
typedef struct
{


  tisStpTarget sLwrTarget;


}tsRte_CtrlStpTarget;

#if defined (CFG_VARIANT_ECO) || (UNIT_TEST)
typedef struct
{
  sint16  nPosition;
  boolean boStop;
}tisDcmTarget;

typedef struct
{

  tisDcmTarget sDcmTarget;

}tsRte_CtrlDcmTarget;

typedef enum
{
  eDcmModeUnavailable,
  eDcmModeAvailable,
  eDcmModeFrozen,
  eDcmModeFactory
} teRte_eDcmMode;

typedef enum
{
  eDcmPhase_Init = 0,     // Initialization phase
  eDcmPhase_Adj = 1,     // Adjustment phase
  eDcmPhase_Fail = 2      // Failure phase
} teRte_eDcmPhase;

typedef struct
{
  teRte_eDcmMode  eASL_MODE;
  teRte_eDcmPhase eASL_PHASE;
  boolean             boLvlAdjHeadlampFault;
  boolean             boLvlAdjFunctionalFault_R;
  boolean             boLvlAdjFunctionalFault_L;
  sint16              snVehAttitudeFactory;
}tsRte_CtrlDcmStatusParams;
#endif
//=============================================================================
// Levelling
//=============================================================================

typedef struct
{


  tiu16StepperPosition_degree ucLWRPosition;




  tiu16StepperSpeed_degreesPerSecond ucLWRSpeed;




  tieStepperState0 ucLWRState;


}tsRte_CtrlStpStatusSpinFront;



// -----------------------------------------------------------------------------
// -------------------------------RX Messages-----------------------------------
// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------
// HS6_ACQ_NEW_JDD_55F
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Acknowledgement of reception of JDD event data
// Used to identify MUX station code
typedef enum
{
  MuxStationCode1 = 0x01U,
  MuxStationCode2 = 0x02U,
  MuxStationCode4 = 0x04U,
  MuxStationCode16 = 0x10U,
  MuxStationCode32 = 0x20U,
  MuxStationCode64 = 0x40U,
  MuxStationCode128 = 0x80U
}teRte_DataAcqJddBsi2;

// -----------------------------------------------------------------------------
/// \struct  tHs1_Acq_New_Jdd_55f
///
/// \brief   Hs1_Acq_New_Jdd_55f Message
///
/// \descr   Hs1_Acq_New_Jdd_55f Message
///
typedef struct
{
  teRte_DataAcqJddBsi2  eAcquittementMedDeh2020; // Acknowledgement of reception of JDD event data
}tsRte_Hs6_Acq_New_Jdd_55F;



// -----------------------------------------------------------------------------
// HS6_COMMANDES_VSM_036
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Network life phase enum
typedef enum
{
  eStandBy = 0U, // Standby/Veille
  eNormalMode = 1U, // Normal mode/Mode normal
  eSwitchToStadby = 2U, // Switch to standby/Mise en veille
  eWake = 3U, // Wake/Reveil
  eCOM_OFF = 4U  // COM_OFF
}teRte_PhaseVie;

// -----------------------------------------------------------------------------
// Faults memorizing forbidden enum
typedef enum
{
  eMemorisationAuthorized = 0U, // Memorisation authorized/Memorisation autorisee
  eMemorisationForbidden = 1U  // Memorisation forbidden/Memorisation interdite
}teRte_InterdMemoDef;

// Authorization of network supervision enum
typedef enum
{
  eNoAuthorization = 0U, // No request/Pas de demande
  eAuthorization = 1U  // Clearing request/Demande d'effacement
}teRte_DiagMuxOnBody;

// Global fault clearing enum
typedef enum
{
  eNoRequest = 0U, // No request/Pas de demande
  eClearingRequest = 1U  // Clearing request/Demande d'effacement
}teRte_DemEffacDef;

// -----------------------------------------------------------------------------
/// \struct  tsRte_SysMon_LifePhases
///
/// \brief   tsRte_SysMon_LifePhases Message
///
/// \descr   tsRte_SysMon_LifePhases Message
///
typedef struct
{
  teRte_PhaseVie       ePhaseVie;
  teRte_InterdMemoDef  eInterdMemoDef;
  teRte_DiagMuxOnBody  eDiagMuxOnBody;
  teRte_DemEffacDef    eDemEffacDef;
  teRte_SigQty         eSigQty; // Signal Quality
}tsRte_SysMon_LifePhases;



// -----------------------------------------------------------------------------
// HS6_DAT_BSI_432
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Vehicle electric system main state enum
typedef enum
{
  VESState_Stop = 0U, // VES main state Stop/Arret
  VESState_Ignition = 1U, // VES main state Contact/Ignition
  VESState_Start = 2U, // VES main state Start Engine/DEM
  VESState_Invalid = 3U  // VES main state Invalid/Reserved
}teRte_EtatPrincipSEV;

// -----------------------------------------------------------------------------
// Electric network state enum
typedef enum
{
  eTI_NOMINAL = 0U,
  eTI_DEGRADE = 1U,
  eTI_DISPO_DEM = 2U,
  eDEMARRAGE = 3U,
  eREDEMARRAGE = 4U,
  eTA_NOMINAL = 5U,
  eTA_DEGRADE = 6U,
  eTA_SECU = 7U,
  eInvalid = 15U
}teRte_EtatReseauElec;

// -----------------------------------------------------------------------------
/// \struct  tsRte_SysMon_VehNetState
///
/// \brief   tsRte_SysMon_VehNetState Message
///
/// \descr   tsRte_SysMon_VehNetState Message
///
typedef struct
{
  teRte_EtatPrincipSEV  eVESMainState;
  teRte_EtatReseauElec  eElectricNetworkState;
  teRte_SigQty          eSigQty; // Signal Quality
}tsRte_SysMon_VehNetState;


typedef struct
{
  uint16 aunPxlIntAct[103];
} tsRte_Unit_Intensities;

// -----------------------------------------------------------------------------
// HS6_DAT_VSM_2AE
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Scrolling turn indicator enum
#if defined (CFG_VARIANT_FULL) || (UNIT_TEST) // Applicable only for FULL version
typedef enum
{
  eScrollingTI_Off = 0U,
  eScrollingTI_On = 1U
}teRte_ScrollingTI;
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)

// -----------------------------------------------------------------------------
// Light State
typedef enum
{
  ReqLighted_Off = 0U, // Light Off
  ReqLighted_On = 1U  // Light On
}teRte_ReqLightState;

// -----------------------------------------------------------------------------
// Warning Mode enum
typedef enum
{
  eWarningMode_PilotedWarningMode = 0U,
  eWarningMode_AutonomWarningMode = 1U
}teRte_WarningMode;

// -----------------------------------------------------------------------------
// Status of indicators enum
typedef enum
{
  eEtatClignotants_IndicatorInactive = 0U,
  eEtatClignotants_RightIndicatorActive = 1U,
  eEtatClignotants_LeftIndicatorActive = 2U,
  eEtatClignotants_LeftAndRightIndicatorActive = 3U
}teRte_EtatClignotants;

// -----------------------------------------------------------------------------
/// \struct  tsRte_SysMonLgtTiReq
///
/// \brief   tsRte_SysMonLgtTiReq Message
///
/// \descr   tsRte_SysMonLgtTiReq Message
///
typedef struct
{
  teRte_WarningMode      eWarning_Mode;
  teRte_EtatClignotants  eEtat_Clignotants;
#if defined (CFG_VARIANT_FULL) || (UNIT_TEST) // Applicable only for FULL version
  teRte_ScrollingTI      eTi_Scrolling;
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)
  teRte_SigQty           eSigQty;  // Signal Quality
}tsRte_SysMonLgtTiReq;



// -----------------------------------------------------------------------------
// HS6_DAT_VSM_34E
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Parking light state
typedef enum
{
  eEtatFeuxStationnement_Deactivated = 0U,
  eEtatFeuxStationnement_LeftSide = 1U,
  eEtatFeuxStationnement_RightSide = 2U,
  eEtatFeuxStationnement_Invalid = 3U
}teRte_EtatFeuxStationnement;

// -----------------------------------------------------------------------------
// The state of vehicle configuration
typedef enum
{
  eModeConfigVehicle_Montage = 0U,
  eModeConfigVehicle_Usine = 1U,
  eModeConfigVehicle_Controle = 2U,
  eModeConfigVehicle_Stockage = 3U,
  eModeConfigVehicle_Client = 4U,
  eModeConfigVehicle_Showroom = 5U,
  eModeConfigVehicle_AfterMarket = 6U,
  eModeConfigVehicle_Invalid = 7U,
  eModeConfigVehicle_Invalid2 = 15U
}teRte_ModeConfigVehicle;

#if defined (CFG_VARIANT_FULL) || (UNIT_TEST) // Applicable only for FULL version
// -----------------------------------------------------------------------------
// AFS - Advanced function to apply
typedef enum
{
  eCtrlAFS_AfsOff = 0U,
  eCtrlAFS_Country = 1U,
  eCtrlAFS_Motorway = 2U,
  eCtrlAFS_Town = 3U,
  eCtrlAFS_BadWeatherLhd = 4U,
  eCtrlAFS_BadWeatherRhd = 5U,
  eCtrlAFS_FoggyLhd = 6U,
  eCtrlAFS_FoggyRhd = 7U,
  eCtrlAFS_Invalid = 255U
}teRte_Ctrl_AFS;

// -----------------------------------------------------------------------------
// GFHB - Glare free high beam command
// Activation /inhibtion control of GFHB (Matrix beam) / PXB (Pixel beam)
typedef enum
{
  eGfhbCmd_Off = 0U,
  eGfhbCmd_CurtainAct = 1U,
  eGfhbCmd_On = 2U,
  eGfhbCmd_CurtainDeAct = 3U
}teRte_GfHb_Cmd;

// -----------------------------------------------------------------------------
// Autorization to activate boost led for low beam
typedef enum
{
  eLowBeamBoostAllowed_False = 0U,
  eLowBeamBoostAllowed_True = 1U
}teRte_LowBeamBoostAllowed;

// -----------------------------------------------------------------------------
// Activation condition of AFS pedestrain mode for OV
typedef enum
{
  ePedestrianAllowed_False = 0U,
  ePedestrianAllowed_True = 1U
}teRte_PedestrianAllowed;

// -----------------------------------------------------------------------------
// Activation request of the Aiming Mode
typedef enum
{
  eAimingModeActivation_False = 0U,
  eAimingModeActivation_True = 1U
}teRte_AimingModeActivation;

// -----------------------------------------------------------------------------
// Information to detect if the road is a motorway or not
typedef enum
{
  eMotorwayDetection_False = 0U,
  eMotorwayDetection_True = 1U
}teRte_MotorwayDetection;
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)

// -----------------------------------------------------------------------------
/// \struct  tsRte_SysMonLgtFctsReq
///
/// \brief   tsRte_SysMonLgtFctsReq Message
///
/// \descr   tsRte_SysMonLgtFctsReq Message
///
typedef struct
{
  teRte_ReqLightState          eDrl_Request;
  teRte_ReqLightState          eHbFlash_Request;
  teRte_ReqLightState          eHb_Request;
  teRte_ReqLightState          ePos_Request;
  teRte_ReqLightState          eSideM_Request;
#if defined (CFG_VARIANT_FULL) || (UNIT_TEST) // Applicable only for FULL version
  teRte_ReqLightState          eFog_Request;
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)
  teRte_EtatFeuxStationnement  eEtatFeuxStat;
  teRte_ModeConfigVehicle      eConfigVhl;
  teRte_SigQty                 eSigQty;  // Signal Quality
}tsRte_SysMonLgtFctsReq;

// -----------------------------------------------------------------------------
/// \struct  tsRte_SysMonAfsSignals
///
/// \brief   tsRte_SysMonAfsSignals Message
///
/// \descr   tsRte_SysMonAfsSignals Message
///
#if defined (CFG_VARIANT_FULL) || (UNIT_TEST) // Applicable only for FULL version
typedef struct
{
  teRte_Ctrl_AFS              eAfs_Mode;
  teRte_GfHb_Cmd              eGfhb_Cmd;
  teRte_LowBeamBoostAllowed   eLbBoost_Allowed;
  teRte_PedestrianAllowed     ePedestrian_Allowed;
  teRte_AimingModeActivation  eAimingMode_Activation;
  teRte_MotorwayDetection     eMotorway_Detection;
  teRte_SigQty                eSigQty; // Signal Quality
}tsRte_SysMonAfsSignals;
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)



// -----------------------------------------------------------------------------
// HS6_DAT_VSM_36E
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Delay of Follow Me Home function
typedef enum
{
  eDelayFmh_15Seconds = 0U,
  eDelayFmh_30Seconds = 1U,
  eDelayFmh_60Seconds = 2U,
  eDelayFmh_NotUsed = 3U
}teRte_DelayFmh;

// -----------------------------------------------------------------------------
// Home mode control
typedef enum
{
  eExtLightingAnimationReq_None = 0u,
  eExtLightingAnimationReq_WelcomeDay = 1u,
  eExtLightingAnimationReq_WelcomeNight = 2u,
  eExtLightingAnimationReq_ByeByeDay = 3u,
  eExtLightingAnimationReq_ByeByeNight = 4u,
  eExtLightingAnimationReq_ByeByeNightFmh = 5u,
  eExtLightingAnimationReq_UnlockDay = 6u,
  eExtLightingAnimationReq_UnlockNight = 7u,
  eExtLightingAnimationReq_UnlockDayExtension = 8u,
  eExtLightingAnimationReq_UnlockNightExtension = 9u,
  eExtLightingAnimationReq_Fmh = 10u,
  eExtLightingAnimationReq_RemoteLighting = 11u,
  eExtLightingAnimationReq_LockDay = 12u,
  eExtLightingAnimationReq_LockNight = 13u,
  eExtLightingAnimationReq_LockNightExtension = 14u,
  eExtLightingAnimationReq_Autorelock = 15u,
  eExtLightingAnimationReq_LocalizationDay = 16u,
  eExtLightingAnimationReq_LocalizationNight = 17u,
  eExtLightingAnimationReq_ShowroomEvent = 18u,
  eExtLightingAnimationReq_ShowroomContinu = 19u,
  eExtLightingAnimationReq_EndNightByeBye = 20u,
  eExtLightingAnimationReq_SwitchOff = 21u,
  eExtLightingAnimationReq_LockDayExtension = 22u,
  eExtLightingAnimationReq_Fmh15 = 23u,
  eExtLightingAnimationReq_Fmh30 = 24u,
  eExtLightingAnimationReq_Fmh60 = 25u,
  eExtLightingAnimationReq_Invalid = 255u
}teRte_ExtLightingAnimationReq;

// -----------------------------------------------------------------------------
// Low beam state
typedef enum
{
  eLightedOff = 0U,
  eLightedOn = 1U
}teRte_EtatFeuxCroist;

// -----------------------------------------------------------------------------
/// \struct  tsRte_AnimationReq
///
/// \brief   tsRte_AnimationReq Message
///
/// \descr   tsRte_AnimationReq Message
///
typedef struct
{
  teRte_DelayFmh                 eDelayFmh;
  teRte_ExtLightingAnimationReq  eFrontLightingAnimationCtrl;
  teRte_EtatFeuxCroist           eLowBeamState;
  teRte_SigQty                   eSigQty; // Signal Quality
}tsRte_AnimationReq;



// -----------------------------------------------------------------------------
// HS6_DAT_VSM_3AE
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Reverse gear status
typedef enum
{
  eEtatMar_Forward = 0U,
  eEtatMar_Reverse = 1U
}teRte_EtatMar;

// -----------------------------------------------------------------------------
/// \struct  tsRte_Hs6_Dat_Vsm_3AE
///
/// \brief   tsRte_Hs6_Dat_Vsm_3AE Message
///
/// \descr   tsRte_Hs6_Dat_Vsm_3AE Message
///
typedef struct
{
  teRte_EtatMar            eEtatMar;
  teRte_ModeConfigVehicle  eVehicleCfg;
  teRte_SigQty             eSigQty; // Signal Quality
}tsRte_SigPrep_VehicleConfigSig;



// -----------------------------------------------------------------------------
// HS6_DAT_VSM_54D
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Kilometrage of vehicle
typedef struct
{
  uint32  ulOdometerTotal;
}tsKmTotal;

// -----------------------------------------------------------------------------
/// \struct  tsRte_OdometerTotal
///
/// \brief   tsRte_OdometerTotal Message
///
/// \descr   tsRte_OdometerTotal Message
///
typedef struct
{
  tsKmTotal     eOdometerTotal;
  teRte_SigQty  eSigQty; // Signal Quality
}tsRte_OdometerTotal;



// -----------------------------------------------------------------------------
// HS6_DAT4_V2_BSI_552
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Temporal counter of the vehicle
typedef struct
{
  uint32  ulCompteurTemporelVehicule;
}tsCptTemporel;

// -----------------------------------------------------------------------------
/// \struct  tsRte_VehTimeCntr
///
/// \brief   tsRte_VehTimeCntr Message
///
/// \descr   tsRte_VehTimeCntr Message
///
typedef struct
{
  tsCptTemporel     eCompteurTemporelVehicule;
  teRte_SigQty      eSigQty; // Signal Quality
}tsRte_VehTimeCntr;



// -----------------------------------------------------------------------------
// HS6_DYN_ABR_38D
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Instantaneous vehicle speed
typedef struct
{
  uint16  unVehicleSpeed;
}tsVitesseVehiculesRoues;

// -----------------------------------------------------------------------------
// CRC of 38D frame
typedef struct
{
  uint8  ucChksumTrmeDynUcFrein;
}tsChksumTrmeDynUcFrein;

// -----------------------------------------------------------------------------
// Process counter for 38D frame.
typedef struct
{
  uint8  ucCptProcess4B38D;
}tsCptProcess4B38D;

// -----------------------------------------------------------------------------
// Vehicle speed unavailability flag
typedef enum
{
  eVvhIndisp_Invalid = 0U,
  eVvhIndisp_SpeedInfoAvailable = 1U,
  eVvhIndisp_SpeedInfoUnavailable = 2U
}teVvhIndisp;

// -----------------------------------------------------------------------------
/// \struct  tsRte_SysMon_VehicleSpeed
///
/// \brief   tsRte_SysMon_VehicleSpeed Message
///
/// \descr   tsRte_SysMon_VehicleSpeed Message
///
typedef struct
{
  tsVitesseVehiculesRoues  eVehicleSpeed;
  tsChksumTrmeDynUcFrein   eChksumTrmeDynUcFrein;
  teVvhIndisp              eVehicleSpeedDispo;
  tsCptProcess4B38D        eCptProcess4B38D;
  teRte_SigQty             eSigQty; // Signal Quality
  teRte_SigQty             eSigQtyDbl; // Signal Quality
}tsRte_SysMon_VehicleSpeed;

// -----------------------------------------------------------------------------
// Vehicle Speed Info data received on Can
typedef struct
{
  uint16       unVehicleSpeed;
  teVvhIndisp  eVehicleSpeedDispo;
}tsSysMon_RxSpeedFrmCheck;

// -----------------------------------------------------------------------------
// Yaw Speed and Cylinder pressure info data received on Can
typedef struct
{
  sint16  nYawSpeed;
  uint16  unCylinderPressure;
}tsSigPrep_RxYawSpeedFrmCheck;


// -----------------------------------------------------------------------------
typedef enum enum_LITSigQty
{
  LIT_SigWarn = 0U,  // do not change numbers:
  LIT_SigOk = 1U,  //   - 0x00 is used as initial value
  LIT_SigErrUnFix = 2U,  //   - numbers are used as indices
  LIT_SigErrFix = 3U
} tieLITSigQty;

typedef struct
{
  sint16   Speed;           ///< [1/10 km/h]  forward      --> positive value
  sint16   Acceleration;    ///< [1/10 m/s^2] acceleration --> positive value
  uint16   Motion;          ///< \brief optional motion direction and gear information.
                          ///  \descr optional motion direction and gear information
                          ///  - \c BB_MotionErr       <b>unknown/error                   </b>
                          ///  - \c BB_MotionRev       <b>reverse                         </b>
                          ///  - \c BB_MotionNeu       <b>neutral, parking                </b>
                          ///  - \c BB_MotionLow       <b>forward low  gear, high torque  </b>
                          ///  - \c BB_MotionMid       <b>forward mid  gear, mid torque   </b>
                          ///  - \c BB_MotionHig       <b>forward high gear, low torque   </b>

  uint8             eSigQty;
  tieLITSigQty           eLITSigQty;
} tSpeedMsg;

typedef struct
{
  sint16      Value;
  sint16      Delta;
  uint8     eSigQty;
} tAccelPreDetectMsg;

typedef struct
{
  sint16      Value;
  sint16      Delta;
  uint8     eSigQty;
} tBrakePreDetectMsg;

// -----------------------------------------------------------------------------
// displacement

typedef struct
{
  sint16      nDisp[CFG_CntSens];     ///< [1/10 mm] moving up --> positive value
  tieSigQty0  eSigQty[CFG_CntSens];
} tsDisplacement0;

//typedef struct
//{
//  uint8 ucVoltRng;
//} tisVoltRng0;

typedef struct
{
  uint8    ucHeader[2];
  uint8    ucRateUp;              /* [1/20 ms] */
  uint8    ucRateDown;            /* [1/20 ms] */
  uint8    ucPreFilterUpCoeff;
  uint8    ucPreFilterDownCoeff;
  uint8    ucOkFilterUpCoeff;
  uint8    ucOkFilterDownCoeff;
  uint8    ucErrFilterUpCoeff;
  uint8    ucErrFilterDownCoeff;
  uint8    ucOkFilterThreshold;
  uint8    ucErrFilterThreshold;
}
tSensorPlausibility1Struct;

typedef struct
{
  uint8 ucStateFront;
  uint8 ucStateRear;
  uint8 ucCtrFront;
  uint8 ucCtrRear;
}
tSensorMountState1Struct;

#ifndef SensorPlausibility1INIT
#define SensorPlausibility1INIT \
    { {0, 0},    /* ucHeader[2]          */ \
      255,    /* ucRateUp             */ \
      1,      /* ucRateDown           */ \
      127,      /* ucPreFilterUpCoeff   */ \
      127,    /* ucPreFilterDownCoeff */ \
      125,    /* ucOkFilterUpCoeff    */ \
      123,    /* ucOkFilterDownCoeff  */ \
      1,      /* ucErrFilterUpCoeff   */ \
      126,    /* ucErrFilterDownCoeff */ \
      20,     /* ucOkFilterThreshold  */ \
      200      /* ucErrFilterThreshold */ \
		    }
#endif

typedef struct
{
  uint16      unVal;     ///< [1/65536] sensor voltage scaled to 65536
} tSensRaw0;

// -----------------------------------------------------------------------------
// pitch
///
/// \struct  tPitch0
///
/// \brief   Pitch Message
///
/// \descr   Pitch Message
///
typedef struct
{
  sint16      nAngle;           ///< [1/10 mrad] front side up --> positive value
  sint16      nHeightErr;       ///< [1/10 mrad] headlights up --> positive value
  teRte_SigQty  eSigQty;
} tPitch0;


typedef enum
{
  eNO_FAILURE,
  eSENSOR_FAILURE,
  eFROZEN_FAILURE,
  eSTORED_FAILURE
}teRte_HlsSensorState;


// -----------------------------------------------------------------------------
/// \struct  tDcmPosMsg
/// 
/// \brief   DC motor position
///
/// \descr
///
typedef struct
{
  sint16 nPos;      // actual position
} tDcmPosMsg;

// -----------------------------------------------------------------------------
/// \struct  tDcmStateMsg
/// 
/// \brief   DC motor state
///
/// \descr
///
// -----------------------------------------------------------------------------
typedef struct
{
  uint16 unState;
} tDcmStateVal;

typedef struct
{
  unsigned  IsOn : 1;    // voltage ok (not overvoltage and not undervoltage)
  unsigned  IsMoving : 1;    // dc motor is "moving" (i.e. positioning by output signal)
  unsigned  IsReady : 1;    // target position achieved
  unsigned  ErrElec : 1;    // electrical failure (support depending on Dcm compiler switches)
  unsigned  Dummy : 4;
} tDcmStateBit;

typedef union
{
  tDcmStateVal Val;
  tDcmStateBit Bit;
} tDcmStateMsg;

typedef enum
{
  CDDDCM_ERROR,
  CDDDCM_NO_ERROR
} teRte_DcmErrorType;

typedef struct
{
  boolean boElecBAT;
  boolean boElecGND;
} tsRte_DcmStatusError;

// -----------------------------------------------------------------------------
/// \struct  tDcmCtrlMsg
/// 
/// \brief   DC motor control signal
///
/// \descr
///
typedef struct
{
  sint16 nPos;                // position in promille Ubat
  uint8  ucCtrl;              // control state
  uint8  ucDummy;
} tDcmCtrlVal;

typedef struct
{
  signed    nPos : 16;   // position in promille Ubat

  unsigned  Active : 1;   // normal(1) / stop (0) motor operation request
                              // (invers to Stop bit of tStpCtrlMsg)
  unsigned  Reserved1 : 1;   // reserved (Corr bit position of tStpCtrlMsg)
  unsigned  Reserved2 : 1;   // reserved (Ref bit position of tStpCtrlMsg)
  unsigned  ErrClr : 1;   // clear error status
  unsigned  Reserved : 4;   // reserved (Sync bits position of tStpCtrlMsg)

  unsigned  ucDummy : 8;
} tDcmCtrlBit;

typedef union
{
  uint32        ulData;
  uint16        unData[2];
  tDcmCtrlBit   Bit;
  tDcmCtrlVal   Val;
} tDcmCtrlMsg;

// Afs Angle
typedef struct
{
  sint16 Hor;      // [0.01�]
  sint16 Ver;      // [0.01�]
  uint8  Width;
} tAfsAngle;

// -----------------------------------------------------------------------------
/// \struct  tPositionOut
/// 
/// \brief   tPositionOut Message
///
/// \descr   tPositionOut Message
///
typedef struct
{
  tAfsAngle Position[1];
  uint8     State;
} tPositionOut;


typedef enum
{
  eDcm_UNDEF_SPEED = 0u,
  eDcm_LOW_SPEED = 1u,
  eDcm_HIGH_SPEED = 2u
}teRte_DcmSpeedMode;

typedef enum
{
  eDcmMovementToTop = 0x11,
  eDcmMovementToBottom = 0x12,
  eDcmMovementToZero = 0x13,
  eDcmSequence1 = 0x14,
  eDcmSequence2 = 0x15,
  eDcmStop = 255
}teRte_DcMotorRoutineControlRequest;

typedef enum
{
  eDcmControl_Start = 0,
  eDcmControl_Stop,
  eDcmControl_Results,
  eDcmControl_Unknown
}teRte_DcMotorRoutineControl;

typedef enum
{
  eDcmBothActuators = 0,
  eDcmLeftActuator,
  eDcmRightActuator
}teRte_DcMotorRoutineControlSide;

typedef enum
{
  eDD06 = 0xDD06,
  eDcmDID_Invalid = 0xFFFF
}teRte_DcMotorRoutineControlDID;

typedef struct
{
  teRte_DcMotorRoutineControl eDcmControl;
  teRte_DcMotorRoutineControlSide eDcmSide;
  teRte_DcMotorRoutineControlRequest eDcmRequest;
  boolean boRequestStatus;
  boolean boRequestAckStatus;
  teRte_DcMotorRoutineControlDID eDcmDID;
  uint8  ucPosRequest;
  uint8  ucStartSequence;
}tsRte_DcMotorRoutineControl;

// -----------------------------------------------------------------------------
// HS6_DYN3_CMM_468
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Status of the 12V electrical energy supply in by engine
typedef enum
{
  eEtatFee_1_1 = 0U,
  eEtatFee_1_2 = 1U,
  eEtatFee_1_3c = 2U,
  eEtatFee_1_3r = 3U,
  eEtatFee_2_1 = 4U,
  eEtatFee_3c_1 = 5U,
  eEtatFee_3r_1 = 6U,
  eEtatFee_4_1 = 7U,
  eEtatFee_5_5 = 8U,
  eEtatFee_1_3vr = 9U,
  eEtatFee_3vr_1 = 10U,
  eEtatFee_Invalid = 11U
}teRte_EtatFee;

// -----------------------------------------------------------------------------
/// \struct  tsRte_SigPrep_ElecSupState
///
/// \brief   tsRte_SigPrep_ElecSupState Message
///
/// \descr   tsRte_SigPrep_ElecSupState Message
///
typedef struct
{
  teRte_EtatFee  eElectrSupplyState;
  teRte_SigQty   eSigQty; // Signal Quality
}tsRte_SigPrep_ElecSupState;


// -----------------------------------------------------------------------------
/// \struct  tsRte_SigPrepNsoTrig
///
/// \brief   tsRte_SigPrepNsoTrig Message
///
/// \descr   tsRte_SigPrepNsoTrig Message
///
typedef struct
{
  boolean boNearSwitchOffTrigger;
  teRte_SigQty  eSigQty;
}tsRte_SigPrepNsoTrig;


// -----------------------------------------------------------------------------
// HS6_INTE_ELECTRON_VSM_092
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Erase failure code
typedef enum
{
  eEffacDefautDiag_NoAction = 0U, // No specific action
  eEffacDefautDiag_FaultMemoryErase = 1U  // Fault memory erasement
}teRte_EffacDefautDiag;

// -----------------------------------------------------------------------------
// Diagnosis Mode
typedef enum
{
  eModeDiag_NoOp = 0U, // No particular operation
  eModeDiag_OpAndCommInhibited = 1U  // Operational and communication inhibed
}teRte_ModeDiag;

// -----------------------------------------------------------------------------
// Diagnosis for Electronic integration mode
typedef enum
{
  eDiagIntegraElec_NoParticularOp = 0U, // No particular operation
  eDiagIntegraElec_NoFrameTransmission = 1U  // No frame transmission
}teRte_DiagIntegraElec;

// -----------------------------------------------------------------------------
/// \struct  tsRte_ElecIntegra
///
/// \brief   tsRte_ElecIntegra Message
///
/// \descr   tsRte_ElecIntegra Message
///
typedef struct
{
  teRte_EffacDefautDiag  eEraseFailureCode;
  teRte_ModeDiag         eDiagnosisMode;
  teRte_DiagIntegraElec  eDiagForElecIntegrationMode;
  teRte_SigQty           eSigQty; // Signal Quality
}tsRte_ElecIntegra;



// -----------------------------------------------------------------------------
// HS6_DYN2_FRE_3CD
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Yaw speed
typedef struct
{
  sint16  nYawSpeed;
}tsRte_VitesseLacet;

// -----------------------------------------------------------------------------
// TMC pressure
typedef struct
{
  uint16  unCylinderPressure;
}tsRte_PressionMaitreCyl;

// -----------------------------------------------------------------------------
/// \struct  tsRte_SigPrep_YawSpeed
///
/// \brief   tsRte_SigPrep_YawSpeed Message
///
/// \descr   tsRte_SigPrep_YawSpeed Message
///
typedef struct
{
  tsRte_VitesseLacet       eYawSpeed;
  tsRte_PressionMaitreCyl  eCylinderPressure;
  teRte_SigQty             eSigQty; // Signal Quality
}tsRte_SigPrep_YawSpeed;



// -----------------------------------------------------------------------------
// HS6_DYN_BEMP_2B7
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Sign of automatic dynamic levelling order for Right LDM
typedef enum
{
  eSigneConsigneSiteD_Positive = 0U,
  eSigneConsigneSiteD_Negativ = 1U
}teRte_SigneConsigneSiteD;

// -----------------------------------------------------------------------------
// Referencing control of automatic levelling of Right LDM
typedef enum
{
  eCmdRefSiteD_NoReferencing = 0U,
  eCmdRefSiteD_Referencing = 1U
}teRte_CmdRefSiteD;

// -----------------------------------------------------------------------------
// Absolute value of automatic dynamic levelling order for Right LDM
typedef struct
{
  uint16  unRCmdPosLvl;
}tsRte_ConsigneSiteD;

// -----------------------------------------------------------------------------
/// \struct  tsPositionOut
///
/// \brief   tsPositionOut Message
///
/// \descr   tsPositionOut Message
///
typedef struct
{
  tAfsAngle Position[2];
  uint8     State;
} tsPositionOut;

#if defined (CFG_VARIANT_FULL) || (UNIT_TEST) // Applicable only for FULL version
// -----------------------------------------------------------------------------
// Diagnosis flux of Digital LB swivelling function to deactivate right LDM
typedef enum
{
  eDynBendingBeamFault_False = 0U,
  eDynBendingBeamFault_True = 1U,
  eDynBendingBeamFault_Unavailable = 2U,
  eDynBendingBeamFault_Invalid = 3U
}teRte_DynBendingBeamFault;
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)

// -----------------------------------------------------------------------------
/// \struct  tsRte_Hs6_Dyn_Bemp_2B7
///
/// \brief   tsRte_Hs6_Dyn_Bemp_2B7 Message
///
/// \descr   tsRte_Hs6_Dyn_Bemp_2B7 Message
///
typedef struct
{
  teRte_SigneConsigneSiteD    eRCmdSignLvl;
  teRte_CmdRefSiteD           eRCmdRefLvl;
  tsRte_ConsigneSiteD         eRCmdPosLvl;
  teRte_SigQty                eSigQty; // Signal Quality
}tsRte_LevellingTgtPos;

// -----------------------------------------------------------------------------
// HS6_DAT_CSS_350
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// CSS Vehicle Trim Angle (pitch of the vehicle)/Assiette Vehicule CSS
typedef struct
{
  sint16  nVehiclePitchAngle; // Vehicle Trim Angle
}tsRte_AssietteVehicule;


// -----------------------------------------------------------------------------
/// \struct  tsRte_SigPrep_VehiclePitchAngle
///
/// \brief   tsRte_SigPrep_VehiclePitchAngle Message
///
/// \descr   tsRte_SigPrep_VehiclePitchAngle Message
///
typedef struct
{
  tsRte_AssietteVehicule  eAssietteVehicule;
  teRte_SigQty            eSigQty; // Signal Quality
}tsRte_SigPrep_VehiclePitchAngle;

#if defined (CFG_VARIANT_FULL) || (UNIT_TEST) // Applicable only for FULL version

// -----------------------------------------------------------------------------
// HS6_DAT_DRVLED_R_297
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Sign of lighting level right enum
typedef enum
{
  eSIGNPOSLVLR_Positiv = 0U,
  eSIGNPOSLVLR_Negative = 1U
}teRte_SignPosLvlR;

// -----------------------------------------------------------------------------
// Current level lighting position right
typedef struct
{
  uint16  unRPosLvl;
}tsRte_PositionSiteD;
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
/// \struct  tsRte_LevellingFeedback
///
/// \brief   tsRte_LevellingFeedback Message
///
/// \descr   tsRte_LevellingFeedback Message
///
typedef struct
{
  teRte_SignPosLvlR           eRPosSignLvl;
  tsRte_PositionSiteD         ePositionSiteD;
  teRte_SigQty                eSigQty; // Signal Quality
}tsRte_LevellingFeedback;



// -----------------------------------------------------------------------------
// HS6_DAT2_DRVLED_R_4D7
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Electric status of levelling stepper of Right LDM
typedef enum
{
  eLvlElecR_NoDefect = 0U,
  eLvlElecR_OpenCircuit = 1U,
  eLvlElecR_ShortCircuit = 2U,
  eLvlElecR_Reserved = 3U
}teLvlElecR;

// -----------------------------------------------------------------------------
// Temperature status of levelling stepper of Right LDM
typedef enum
{
  eLvlTemperatureR_NoWarning = 0U,
  eLvlTemperatureR_ColdTemperature = 1U,
  eLvlTemperatureR_HighTemperatureWarning = 2U,
  eLvlTemperatureR_HighTemperatureShutdown = 3U
}teLvlTemperatureR;

// -----------------------------------------------------------------------------
// Step loss status of levelling stepper of Right LDM
typedef enum
{
  eLvlSteplossR_NoSteploss = 0U,
  eLvlSteplossR_SteplossRisk = 1U
}teLvlSteplossR;

// -----------------------------------------------------------------------------
// Referencing status of levelling stepper of Right LDM
typedef enum
{
  eLvlRefStateR_WaitingForNewRefCmd = 0U,
  eLvlRefStateR_RefInProgress = 1U,
  eLvlRefStateR_SuccessfullyFinished = 2U,
  eLvlRefStateR_Invalid = 3U
}teLvlRefStateR;

// -----------------------------------------------------------------------------
// Voltage status of Right levelling stepper.
typedef enum
{
  eLvlVoltR_NominalVoltage = 0U,
  eLvlVoltR_UnderVoltage = 1U,
  eLvlVoltR_NotUsed = 2U,
  eLvlVoltR_OverVoltage = 3U
}teLvlVoltR;

// -----------------------------------------------------------------------------
/// \struct  tsRte_LevellingDiagStatus
///
/// \brief   tsRte_LevellingDiagStatus Message
///
/// \descr   tsRte_LevellingDiagStatus Message
///
typedef struct
{
  teLvlElecR         eLvlElecR;
  teLvlTemperatureR  eLvlTemperatureR;
  teLvlSteplossR     eLvlSteplossR;
  teLvlRefStateR     eLvlRefStateR;
  teLvlVoltR         eLvlVoltR;
  teRte_SigQty       eSigQty; // Signal Quality
}tsRte_LevellingDiagStatus;



// -----------------------------------------------------------------------------
// HS6_DYN_VSM_28E
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Image of the vehicle path curvature at the midle of the rear axle
typedef struct
{
  sint16  nVehiclePathCurvature;
}tsRte_VehPathCurvature;

// -----------------------------------------------------------------------------
/// \struct  tsRte_SigPrep_VehPathCurvature
///
/// \brief   tsRte_SigPrep_VehPathCurvature Message
///
/// \descr   tsRte_SigPrep_VehPathCurvature Message
///
typedef struct
{
  tsRte_VehPathCurvature  eVehiclePathCurvature;
  teRte_SigQty            eSigQty; // Signal Quality
}tsRte_SigPrep_VehPathCurvature;



// -----------------------------------------------------------------------------
// HS6_DAT_VSM_32E
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
/// \struct  tsRte_SigPrepLgtClSblReq
///
/// \brief   tsRte_SigPrepLgtClSblReq Message
///
/// \descr   tsRte_SigPrepLgtClSblReq Message
///
typedef struct
{
  teRte_ReqLightState  eCl_Request;
  teRte_ReqLightState  eSbl_Request;
  teRte_SigQty         eSigQty; // Signal Quality
}tsRte_SigPrepLgtClSblReq;



// -----------------------------------------------------------------------------
// HS6_DAT7_BSI_612
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Dynamic curve lighting inhibition enum
typedef enum
{
  eInhEclairageVirageDyn_NoInhibition = 0U,
  eInhEclairageVirageDyn_Inhibition = 1U
}teInhEclairageVirageDyn;

// -----------------------------------------------------------------------------
/// \struct  tsRte_SigPrep_EnvCondition
///
/// \brief   tsRte_SigPrep_EnvCondition Message
///
/// \descr   tsRte_SigPrep_EnvCondition Message
///
typedef struct
{
  teInhEclairageVirageDyn  eDblInhibition;
  teRte_SigQty             eSigQty; // Signal Quality
}tsRte_SigPrep_EnvCondition;



// -----------------------------------------------------------------------------
// HS6_DYN_VSM_0AB (X = 1)
// HS6_DYN_VSM_0C3 (X = 2)
// HS6_DYN_VSM_0CB (X = 3)
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Brightness score of the reflector X (X = 1 to 3)
typedef struct
{
  uint8  ucBrightness;
}tsRte_PerceiveRflXBrightness;

// -----------------------------------------------------------------------------
// Angle to left of the reflector X rectangle (X = 1 to 3)
typedef struct
{
  sint16  nLeftAngle;
}tsRte_PerceiveRflXLeftAngle;

// -----------------------------------------------------------------------------
// Angle to right of the reflector X rectangle (X = 1 to 3)
typedef struct
{
  sint16  nRightAngle;
}tsRte_PerceiveRflXRightAngle;

// -----------------------------------------------------------------------------
// Angle to top of the reflector X rectangle (X = 1 to 3)
typedef struct
{
  sint16  nTopAngle;
}tsRte_PerceiveRflXTopAngle;

// -----------------------------------------------------------------------------
// Angle to bottom of the reflector X rectangle (X = 1 to 3)
typedef struct
{
  sint16  nBottomAngle;
}tsRte_PerceiveRflXBottomAngle;

// -----------------------------------------------------------------------------
// Distance to the reflector X attention center (X = 1 to 3)
typedef struct
{
  uint16  unDistance;
}tsRte_PerceiveRflXDistance;

// -----------------------------------------------------------------------------
/// \struct  tsRte_SigPrep_PerceiveSigGroup1_sVal
///
/// \brief   tsRte_SigPrep_PerceiveSigGroup1_sVal Message
///
/// \descr   tsRte_SigPrep_PerceiveSigGroup1_sVal Message
///
typedef struct
{
  tsRte_PerceiveRflXBrightness   eBrightness;
  tsRte_PerceiveRflXLeftAngle    eLeftAngle;
  tsRte_PerceiveRflXRightAngle   eRightAngle;
  tsRte_PerceiveRflXTopAngle     eTopAngle;
  tsRte_PerceiveRflXBottomAngle  eBottomAngle;
  tsRte_PerceiveRflXDistance     eDistance;
  teRte_SigQty                   eSigQty; // Signal Quality
}tsRte_SigPrep_PerceiveSigGroup1_sVal;

// -----------------------------------------------------------------------------
// Camera data struct received on Can for CAN frames 0xAB, 0xC3, 0xCB
typedef struct
{
  uint8   ucBrightness;
  sint16  nLeftAngle;
  sint16  nRightAngle;
  sint16  nTopAngle;
  sint16  nBottomAngle;
  uint16  unDistance;
}tsSigPrep_PerceiveSigGroup1_FrmCheck;



// -----------------------------------------------------------------------------
// HS6_DYN_VSM_0E3 (X = 1)
// HS6_DYN_VSM_0EB (X = 2)
// HS6_DYN_VSM_103 (X = 3)
// HS6_DYN_VSM_10B (X = 4)
// HS6_DYN_VSM_123 (X = 5)
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Horizontal minimum distance to the closest vehicle 2 detected in the cluster (X = 1 to 5)
typedef struct
{
  uint16  unClusterMinDistance;
}tsRte_ClusterMinDistanceX;

// -----------------------------------------------------------------------------
// Horizontal minimum distance to the extreme left vehicle X detected in the cluster (X = 1 to 5)
typedef struct
{
  uint16  unClusterLeftDistance;
}tsRte_ClusterLeftDistanceX;

// -----------------------------------------------------------------------------
// Horizontal minimum distance to the extreme right vehicle X detected in the cluster (X = 1 to 5)
typedef struct
{
  uint16  unClusterRightDistance;
}tsRte_ClusterRightDistanceX;

// -----------------------------------------------------------------------------
// Horizontal left angle to the extreme left detected vehicle in the cluster. (X = 1 to 5)
// The angle is calculated from the camera reference system.
typedef struct
{
  sint16  nClusterAngleLeft;
}tsRte_ClusterAngleLeftX;

// -----------------------------------------------------------------------------
// Horizontal right angle to the extreme right detected vehicle in the cluster. (X = 1 to 5)
// The angle is calculated from the camera reference system.
typedef struct
{
  sint16  nClusterAngleRight;
}tsRte_ClusterAngleRightX;

// -----------------------------------------------------------------------------
// Horizontal azimuth angular velocity of the right side of vehicle 2 detected at the extreme right of the cluster (oncoming, leading or side).
// It is calculated in the camera coordinates system. (X = 1 to 5)
typedef struct
{
  sint8  cClusterRightAzimuthRate;
}tsRte_ClusterRightAzimuthRateX;

// -----------------------------------------------------------------------------
// Horizontal azimuth angular velocity of the left side of vehicle 2 detected at the extreme left of the cluster (oncoming, leading or side).
// It is calculated in the camera coordinates system. (X = 1 to 5)
typedef struct
{
  sint8  cClusterLeftAzimuthRate;
}tsRte_ClusterLeftAzimuthRateX;

// -----------------------------------------------------------------------------
// Vehicle 1 light type detected enum - Describes the vehicle 1  light type detected. Indicates oncoming or leading vehicle.
// In case of a cluster it represents the type of the closest vehicle in the cluster. Clearance = Truck cabin top lights (i.e. oncoming).
typedef enum
{
  eClstType_Invalid = 0U,
  eClstType_Oncomming = 1U,
  eClstType_Couple_Oncoming = 2U,
  eClstType_Taillight = 3U,
  eClstType_Couple_Taillight = 4U,
  eClstType_Couple_OC_Clearance = 5U,
  eClstType_Reserved = 6U
}teRte_ClusterTypeX;

// -----------------------------------------------------------------------------
/// \struct  tsRte_SigPrep_ClusterSigGroup1_sVal
///
/// \brief   tsRte_SigPrep_ClusterSigGroup1_sVal Message
///
/// \descr   tsRte_SigPrep_ClusterSigGroup1_sVal Message
///
typedef struct
{
  tsRte_ClusterMinDistanceX       eClusterMinDistance;
  tsRte_ClusterLeftDistanceX      eClusterLeftDistance;
  tsRte_ClusterRightDistanceX     eClusterRightDistance;
  tsRte_ClusterAngleLeftX         eClusterAngleLeft;
  tsRte_ClusterAngleRightX        eClusterAngleRight;
  tsRte_ClusterRightAzimuthRateX  eClusterRightAzimuthRate;
  tsRte_ClusterLeftAzimuthRateX   eClusterLeftAzimuthRate;
  teRte_ClusterTypeX              eClusterType;
  teRte_SigQty                    eSigQty; // Signal Quality
}tsRte_SigPrep_ClusterSigGroup1_sVal;

// -----------------------------------------------------------------------------
// Camera data struct received on Can for CAN frames 0xE3, 0xEB, 0x103, 0x10B, 0x123
typedef struct
{
  uint16               unClusterMinDistance;
  uint16               unClusterLeftDistance;
  uint16               unClusterRightDistance;
  sint16               nClusterAngleLeft;
  sint16               nClusterAngleRight;
  sint8                cClusterRightAzimuthRate;
  sint8                cClusterLeftAzimuthRate;
  teRte_ClusterTypeX   eClusterType;
}tsSigPrep_ClusterSigGroup1_FrmCheck;



// -----------------------------------------------------------------------------
// HS6_DYN_VSM_12B (X = 1)
// HS6_DYN_VSM_143 (X = 2)
// HS6_DYN_VSM_14B (X = 3)
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Id of reflector X (X = 1 to 3)
typedef struct
{
  uint8  ucPerceiveId;
}tsRte_PerceiveRflXId;

// -----------------------------------------------------------------------------
// Horizontal azimuth angular velocity of the left side of the reflector X. (X = 1 to 3)
// It is calculated in the camera coordinates system.
typedef struct
{
  sint8  cLeftAzimuthRate;
}tsRte_PerceiveRflXLeftAzimuthRate;

// -----------------------------------------------------------------------------
// Horizontal azimuth angular velocity of the right side of the reflector X. (X = 1 to 3)
// It is calculated in the camera coordinates system.
typedef struct
{
  sint8  cRightAzimuthRate;
}tsRte_PerceiveRflXRightAzimuthRate;

// -----------------------------------------------------------------------------
// ENUM Indicates the presence of the host vehicle in traffic or not.
typedef enum
{
  eTrffDet_True = 0U,
  eTrffDet_False = 1U,
  eTrffDet_Invalid = 2U,
  eTrffDet_Unavailable = 3U
}teRte_TrafficDetected;

// -----------------------------------------------------------------------------
/// \struct  tsRte_SigPrep_PerceiveSigGroup2_sVal
///
/// \brief   tsRte_SigPrep_PerceiveSigGroup2_sVal Message
///
/// \descr   tsRte_SigPrep_PerceiveSigGroup2_sVal Message
///
typedef struct
{
  tsRte_PerceiveRflXId                ePerceiveId;
  tsRte_PerceiveRflXLeftAzimuthRate   eLeftAzimuthRate;
  tsRte_PerceiveRflXRightAzimuthRate  eRightAzimuthRate;
  teRte_TrafficDetected               eTrafficDetected;
  teRte_SigQty                        eSigQty; // Signal Quality
}tsRte_SigPrep_PerceiveSigGroup2_sVal;

// -----------------------------------------------------------------------------
// HS6_DYN_VSM_163 (X = 1)
// HS6_DYN_VSM_16B (X = 2)
// HS6_DYN_VSM_183 (X = 3)
// HS6_DYN_VSM_18B (X = 4)
// HS6_DYN_VSM_1AB (X = 5)
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// ENUM describes cluster sub type. (X = 1 to 5)
// If not cluster = 0 Indicates if the cluster of vehicles is mixing oncoming and/or leading vehicles, or not.
typedef enum
{
  eClstSubType_Invalid = 0U,
  eClstSubType_Oncomming = 1U,
  eClstSubType_Taillight = 2U,
  eClstSubType_Left_Oncoming = 3U,
  eClstSubType_Right_Oncoming = 4U,
  eClstSubType_Left_and_Right_Oncoming = 5U,
  eClstSubType_Left_and_Right_Taillight = 6U,
  eClstSubType_Reserved = 7U
}teRte_ClusterSubTypeX;

// -----------------------------------------------------------------------------
// Vertical Angle to bottom of lthe closest / lowest vehicle 1 lights in the cluster rectangle including object lights.
// This angle is calculated from the camera reference. (X = 1 to 5)
typedef struct
{
  sint8  cClusterBottomAngle;
}tsRte_ClusterBottomAngleX;

// -----------------------------------------------------------------------------
// Vehicle 1 cluster object ID (based on light detection and object clustering). (X = 1 to 5)
// Updated each frame. Range is 1-255, while 0 indicates that the field in unfilled.
typedef struct
{
  uint8  ucClusterId;
}tsRte_ClusterIdX;

// -----------------------------------------------------------------------------
/// \struct  tsRte_SigPrep_ClusterSigGroup2_sVal
///
/// \brief   tsRte_SigPrep_ClusterSigGroup2_sVal Message
///
/// \descr   tsRte_SigPrep_ClusterSigGroup2_sVal Message
///
typedef struct
{
  teRte_ClusterSubTypeX      eClusterSubType;
  tsRte_ClusterBottomAngleX  eClusterBottomAngle;
  tsRte_ClusterIdX           eClusterId;
  teRte_SigQty               eSigQty; // Signal Quality
}tsRte_SigPrep_ClusterSigGroup2_sVal;

// -----------------------------------------------------------------------------
// Camera data struct received on Can for CAN frames 0x163, 0x16B, 0x183, 0x18B, 0x1AB
typedef struct
{
  uint8                      ucClusterSubType;
  sint8                      cClusterBottomAngle;
  teRte_ClusterSubTypeX      eClusterSubType;
}tsSigPrep_ClusterSigGroup2_FrmCheck;
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)


// -----------------------------------------------------------------------------
// HS6_DYN_VSM_257
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Acceleration pedal position
typedef struct
{
  uint8  ucPedalAcceleration;
}tsRte_EfcmntPdleAccel;

// -----------------------------------------------------------------------------
// Brake circuit pressure when ESP does automatic braking
typedef struct
{
  uint8  ucBrakePressure;
}tsRte_AutoBrakingPressure;

// -----------------------------------------------------------------------------
// Driver request (acceleration pedal)
typedef struct
{
  uint8  ucDriverRequest;
}tsRte_VolonteCond;

// -----------------------------------------------------------------------------
// Steering type
typedef enum
{
  eTypeDir_Invalid = 0U,
  eTypeDir_SteeringRight = 1U,
  eTypeDir_SteeringLeft = 2U
}teRte_TypeDir;

// -----------------------------------------------------------------------------
/// \struct  tsRte_SigPrep_DynamicSigs
///
/// \brief   tsRte_SigPrep_DynamicSigs Message
///
/// \descr   tsRte_SigPrep_DynamicSigs Message
///
typedef struct
{
  tsRte_EfcmntPdleAccel      ePedalAcceleration;
  tsRte_AutoBrakingPressure  eBrakePressure;
  tsRte_VolonteCond          eDriverRequest;
  teRte_TypeDir              eSteeringType;
  teRte_SigQty               eSigQty; // Signal Quality
}tsRte_SigPrep_DynamicSigs;

// -----------------------------------------------------------------------------
// Dynamic signals info data received on Can
typedef struct
{
  uint8          ucPedalAcceleration;
  uint8          ucBrakePressure;
  uint8          ucDriverRequest;
  teRte_TypeDir  eSteeringType;
}tsSigPrep_RxDynamicSigsFrmCheck;


#if defined (CFG_VARIANT_FULL) || defined (UNIT_TEST) // Applicable only for FULL version
// -----------------------------------------------------------------------------
/// \struct  tsRte_SigPrep_SteeringWheelAngle
///
/// \brief   tsRte_SigPrep_SteeringWheelAngle Message
///
/// \descr   tsRte_SigPrep_SteeringWheelAngle Message
///
typedef struct
{
  sint16        nSteeringWheelAngle;
  teRte_SigQty  eSigQty; // Signal Quality
}tsRte_SigPrep_SteeringWheelAngle;
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)



// -----------------------------------------------------------------------------
// -------------------------------TX Messages-----------------------------------
// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------
// HS6_DIAG_DRVLED_L_457
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// X Lowbeam diagnosis (X = L / R)
typedef enum
{
  eDiagLb_Ok = 0U,
  eDiagLb_Nok = 1U
}teDiagLbX;

// -----------------------------------------------------------------------------
// X Turn Indicator diagnosis (X = L / R)
typedef enum
{
  eDiagTiF_Ok = 0U,
  eDiagTiF_Nok = 1U
}teDiagTiXF;

// -----------------------------------------------------------------------------
// Status of automatic levelling adjustment
typedef enum
{
  eDiagLvl_Ok = 0U,
  eDiagLvl_Nok = 1U
}teDiagLvl;

#if defined (CFG_VARIANT_FULL) || (UNIT_TEST) // Applicable only for FULL version
// -----------------------------------------------------------------------------
// Status of Dynamic Bending Light function
typedef enum
{
  eDiagDbl_Ok = 0U,
  eDiagDbl_Nok = 1U
}teDiagDbl;

// -----------------------------------------------------------------------------
// Status of Glare Free High Beam (GFHB) of X LDM (X = L / R)
typedef enum
{
  eXGfhbFault_Ok = 0U,
  eXGfhbFault_Nok = 1U
}teXGfhbFault;

// -----------------------------------------------------------------------------
// X Static Bending Light diagnosis (X = L / R)
typedef enum
{
  eDiagSbl_Ok = 0U,
  eDiagSbl_Nok = 1U
}teDiagSblX;



#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)


// -----------------------------------------------------------------------------
/// \struct  tsRte_Hs6_Diag_Drvled_L_457
///
/// \brief   tsRte_Hs6_Diag_Drvled_L_457 Message
///
/// \descr   tsRte_Hs6_Diag_Drvled_L_457 Message
///
typedef struct
{
  teDiagLvl     eLevellingAdjustFault;
}tsRte_Hs6_Diag_Drvled_L_457;

// -----------------------------------------------------------------------------
/// \struct  tsRte_Hs6_Diag_Drvled_R_477
///
/// \brief   tsRte_Hs6_Diag_Drvled_R_477 Message
///
/// \descr   tsRte_Hs6_Diag_Drvled_R_477 Message
///
typedef struct
{
  teDiagLvl     eLevellingAdjustFaultR;
}tsRte_Hs6_Diag_Drvled_R_477;

// -----------------------------------------------------------------------------
// HS6_FLT_EVT_DRVLED_L_5D5
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Kind of message
typedef enum
{
  eTypeMessage_2004EEA = 0U,
  eTypeMessage_2010EEA = 1U,
  eTypeMessage_DEH2020 = 2U,
  eTypeMessage_Reserved = 3U
}teTypeMessage;

// -----------------------------------------------------------------------------
// Relevance of the Date information
typedef enum
{
  eRelevanceOfDate_Pertinent = 0U,
  eRelevanceOfDate_NonPertinent = 1U
}teRelevanceOfDate;

// -----------------------------------------------------------------------------
// Default state
typedef enum
{
  eEtatDtc_Disappearance = 0U,  // Transition from Permanent fault to transitory fault
  eEtatDtc_Appearance = 1U   // Fault considered as permanent
}teEtatDtc;

// -----------------------------------------------------------------------------
// Frame number
typedef enum
{
  eNumeroTrame_Reserved = 0U,
  eNumeroTrame_FrameNumber1 = 1U,
  eNumeroTrame_FrameNumber2 = 2U,
  eNumeroTrame_FrameNumber3 = 3U
}teNumeroTrame;

// -----------------------------------------------------------------------------
// Frame number
typedef enum
{
  eNombreTrames_Reserved = 0U,
  eNombreTrames_OneFrame = 1U,
  eNombreTrames_TwoFrames = 2U,
  eNombreTrames_ThreeFrames = 3U
}teNombreTrames;

// -----------------------------------------------------------------------------
// Fault code
typedef struct
{
  uint32  ulCodesDefaut;
}tsCodesDefaut;

// -----------------------------------------------------------------------------
// Format of DTC
typedef enum
{
  eDtcFormatIdentifier_SAE_J2012_DA_00 = 0U,
  eDtcFormatIdentifier_ISO_14229_1 = 1U,
  eDtcFormatIdentifier_SAE_J1939_73 = 2U,
  eDtcFormatIdentifier_ISO_11992_4 = 3U,
  eDtcFormatIdentifier_SAE_J2012_DA_04 = 4U
}teDtcFormatIdentifier;

// -----------------------------------------------------------------------------
// ECU code
typedef struct
{
  uint8  ucEcuCode;
}tsEcuCode;

// -----------------------------------------------------------------------------
// JDD number of kilometer
typedef struct
{
  uint32  ulMileageResolution;
}tsKilometrageDeh;

// -----------------------------------------------------------------------------
// Vehicle time counter
typedef struct
{
  uint32  ulReferenceHoraire;
}tsReferenceHoraire;

// -----------------------------------------------------------------------------
/// \struct  tsRte_Hs6_Flt_Evt_Drvled_L_5D5
///
/// \brief   tsRte_Hs6_Flt_Evt_Drvled_L_5D5 Message
///
/// \descr   tsRte_Hs6_Flt_Evt_Drvled_L_5D5 Message
///
typedef struct
{
  teTypeMessage          eTypeEcu;
  teRelevanceOfDate      eRelevanceOfDate;
  teEtatDtc              eTypeEvenement;
  teNumeroTrame          eNumeroTrame;
  teNombreTrames         eNombreTrames;
  tsCodesDefaut          eCodesDefaut;
  teDtcFormatIdentifier  eDtcFormatIdentifier;
  tsEcuCode              eEcuCode;
  tsKilometrageDeh       eMileageResolution;
  tsReferenceHoraire     eReferenceHoraire;
}tsRte_Hs6_Flt_Evt_Drvled_L_5D5;



// -----------------------------------------------------------------------------
// HS6_FLT_EVT_DRVLED_R_5F5
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
/// \struct  tsRte_Hs6_Flt_Evt_Drvled_R_5F5
///
/// \brief   tsRte_Hs6_Flt_Evt_Drvled_R_5F5 Message
///
/// \descr   tsRte_Hs6_Flt_Evt_Drvled_R_5F5 Message
///
typedef struct
{
  teTypeMessage          eTypeEcu;
  teRelevanceOfDate      eRelevanceOfDate;
  teEtatDtc              eTypeEvenement;
  teNumeroTrame          eNumeroTrame;
  teNombreTrames         eNombreTrames;
  tsCodesDefaut          eCodesDefaut;
  teDtcFormatIdentifier  eDtcFormatIdentifier;
  tsEcuCode              eEcuCode;
  tsKilometrageDeh       eMileageResolution;
  tsReferenceHoraire     eReferenceHoraire;
}tsRte_Hs6_Flt_Evt_Drvled_R_5F5;


// -----------------------------------------------------------------------------
// HS6_DIAG_DRVLED_R_477
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
typedef struct
{
  teDiagLvl     eLevellingAdjustFaultR;
  teRte_SigQty  eSigQty; // Signal Quality
}tsRte_DcmDiagStatusR;

// -----------------------------------------------------------------------------
// HS6_SUPV_DRVLED_L_5D7
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// Device under diagnostic
typedef enum
{
  eActDiag_ExcludingDiagnosticActivity = 0U,
  eActDiag_InDiagnosticActivity = 1U
}teActDiag;

// -----------------------------------------------------------------------------
// Device under diagnostic session
typedef enum
{
  eSessDiag_ExcludingDiagnostic = 0U,
  eSessDiag_UnderDiagnostic = 1U
}teSessDiag;

// -----------------------------------------------------------------------------
// Device in functional degraded mode
typedef enum
{
  eDegradFonc_ModeNormal = 0U,
  eDegradFonc_DegradedMode = 1U
}teDegradFonc;

// -----------------------------------------------------------------------------
// Status of supervision task
typedef enum
{
  eEtatNm_NmInactive = 0U,
  eEtatNm_NmActive = 1U
}teEtatNm;

// -----------------------------------------------------------------------------
// Status of NERR bit
typedef enum
{
  eBitNerr_NoFault = 0U,
  eBitNerr_FaultPresent = 1U
}teBitNerr;

// -----------------------------------------------------------------------------
// COM loss fault
typedef enum
{
  ePerteCom_NoFault = 0U,
  ePerteCom_FaultPresent = 1U
}tePerteCom;

// -----------------------------------------------------------------------------
// Value of the C_DEF_NERR counter according to the line diagnostic
typedef struct
{
  uint8  ucCDefautNerr;
}tsCDefautNerr;

// -----------------------------------------------------------------------------
// Rotating counter incremented upon each detection of "message non transmitted"
// of a message after 1 attempt on N_As timeout, it is reset to 0.
typedef struct
{
  uint8  ucDefautNAs;
}tsDefautNAs;

// -----------------------------------------------------------------------------
// Rotating counter incremented by 1 at each "BUS_OFF" fault, it is reset to 0
typedef struct
{
  uint8  ucDefautBusoff;
}tsDefautBusoff;

// -----------------------------------------------------------------------------
// Rotating counter incremented by 1 at each "PERTE_COM" transition, it is reset to 0
typedef struct
{
  uint8  ucDefautPerteCom;
}tsDefautPerteCom;

// -----------------------------------------------------------------------------
// Calculator(s) supervised absent by DRIVER_LED_L_F_X (X = 1 to 3)
typedef enum
{
  eUceAbsDriverLedFX_NoCalculatorAbsent = 0U,
  eUceAbsDriverLedFX_BsiAbsent = 18U,
  eUceAbsDriverLedFX_RadioAbsent = 32U,
  eUceAbsDriverLedFX_BtelAbsent = 36U,
  eUceAbsDriverLedFX_KmlAbsent = 51U
}teUceAbsDriverLedFX;

// -----------------------------------------------------------------------------
/// \struct  tsRte_Hs6_Supv_Drvled_L_5D7
///
/// \brief   tsRte_Hs6_Supv_Drvled_L_5D7 Message
///
/// \descr   tsRte_Hs6_Supv_Drvled_L_5D7 Message
///
typedef struct
{
  teActDiag            eActDiag;
  teSessDiag           eSessDiag;
  teDegradFonc         eDegradFonc;
  teEtatNm             eEtatNm;
  teBitNerr            eBitNerr;
  tePerteCom           ePerteCom;
  tsCDefautNerr        eCDefautNerr;
  tsDefautNAs          eDefautNAs;
  tsDefautBusoff       eDefautBusoff;
  tsDefautPerteCom     eDefautPerteCom;
  teUceAbsDriverLedFX  eUceAbsDriverLedF1;
  teUceAbsDriverLedFX  eUceAbsDriverLedF2;
  teUceAbsDriverLedFX  eUceAbsDriverLedF3;
}tsRte_Hs6_Supv_Drvled_L_5D7;

// -----------------------------------------------------------------------------
// HS6_SUPV_DRVLED_R_5F7
//
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
/// \struct  tsRte_Hs6_Supv_Drvled_R_5F7
///
/// \brief   tsRte_Hs6_Supv_Drvled_R_5F7 Message
///
/// \descr   tsRte_Hs6_Supv_Drvled_R_5F7 Message
///
typedef struct
{
  teActDiag            eActDiag;
  teSessDiag           eSessDiag;
  teDegradFonc         eDegradFonc;
  teEtatNm             eEtatNm;
  teBitNerr            eBitNerr;
  tePerteCom           ePerteCom;
  tsCDefautNerr        eCDefautNerr;
  tsDefautNAs          eDefautNAs;
  tsDefautBusoff       eDefautBusoff;
  tsDefautPerteCom     eDefautPerteCom;
  teUceAbsDriverLedFX  eUceAbsDriverLedF1;
  teUceAbsDriverLedFX  eUceAbsDriverLedF2;
  teUceAbsDriverLedFX  eUceAbsDriverLedF3;
}tsRte_Hs6_Supv_Drvled_R_5F7;

typedef struct
{


  uint8 assemblyCAN;




  uint8 assemblyCAN_reserved;


}tieEftEcuVarCfgCAN;

typedef struct
{


  uint8 assemblyHSS;




  uint8 assemblyHSS_reserved;


}tieEftEcuVarCfgHSS;

typedef struct
{


  uint16 IFactor;




  sint16 IOffset;


}tieEftCalibLEDCh;

typedef struct
{


  uint32 Reserved_EftCalibLEDDrv;



  tieEftCalibLEDCh channel[2];

}tieEftCalibLEDDrv;

typedef struct
{


  uint8 LEDDriverVariant;




  uint8 notused_1;




  uint16 Imax;




  uint16 Imin;




  uint8 PMax;




  uint8 reserved;




  uint16 Shunt;




  uint8 Inductor;




  uint8 notused_2;


}tieEftEcuVarCfgLED;

typedef struct
{

  uint8 EFT_CALIB_TEXT[4];



  uint8 EFT_CALIB_TYPE;



  uint8 EFT_CALIB_TYPE_reserved[3];


  tieEftCalibLEDDrv EFT_CALIB_LED_DRV[7];

  struct
  {


    uint16 Vfactor;




    sint16 Voffset;


  }EFT_CALIB_LED_BOOST;

  uint8 EFT_CALIB_RESERVED_BLOCK[156];


  uint8 HWEL_Version[8];


  uint8 HW_Development_Info[15];


  uint8 HweTableIndices[2];


  uint8 ECUSerialNumber[16];


  uint8 ECUManufacturingDate[3];


  uint8 HWModificationIndex[2];


  uint8 ECUUID[16];


  uint8 HWDESC_RESERVED[194];


  uint8 EFT_ECUVARCFG_TEXT[4];



  uint8 EFT_ECUVARCfG_TYPE;




  uint8 EFT_ECUVARCFG_ECU;




  uint8 EFT_ECUVARCFG_BOOSTER;




  uint8 EFT_ECUVARCFG_BOOSTER_Reserved;




  uint16 EFT_ECUVARCFG_LED_CHIPS;




  uint16 EFT_ECUVARCFG_LED_CHIPS_reserved;



  tieEftEcuVarCfgLED EFT_ECUVARCFG_LED_CH[14];


  uint8 EFT_ECUVARCFG_STEPPER[6];



  uint8 EFT_ECUVARCFG_SENSOR_SUPPLY;




  uint8 EFT_ECUVARCFG_SENSOR_SUPPLY_reserved;




  uint8 EFT_ECUVARCFG_SWITCH_ARRAY;




  uint8 EFT_ECUVARCFG_SWITCH_ARRAY_reserved;




  uint16 EFT_ECUVARCFG_NTC;




  uint16 EFT_ECUVARCFG_NTC_reserved;



  tieEftEcuVarCfgHSS EFT_ECUVARCFG_HSS[3];


  tieEftEcuVarCfgCAN EFT_ECUVARCFG_CAN[2];



  uint16 EFT_ECUVARCFG_ADC_FACTOR_PCB_TEMP;



  uint16 EFT_ECUVARCFG_ADC_FACTOR_NTC[12];



  uint16 EFT_ECUVARCFG_ADC_FACTOR_VBAT;




  uint16 EFT_ECUVARCFG_ADC_FACTOR_LR_DETECT;



  uint16 EFT_ECUVARCFG_ADC_FACTOR_HSS_SENSE[2];



  uint16 EFT_ECUVARCFG_ADC_FACTOR_VBOOST;




  uint16 EFT_ECUVARCFG_ADC_COND_1;




  uint16 EFT_ECUVARCFG_ADC_COND_2;



  uint8 EFT_ECUVARCFG_CC_VERSION[2];


  uint8 EFT_ECUVARCFT_RESERVED_BLOCK[10];

}tieEftData;

typedef  tieEftData * tieEftDataPtr;


//=============================================================================
// definition of LED state bits
//=============================================================================
typedef enum
{
  eLedState_Off = 0,
  eLedState_On = 1,
  eLedState_LowVolt = 2,
  eLedState_OpenLoad = 3,
  eLedState_ShortBat = 4,
  eLedState_ShortGnd = 5,
  eLedState_ThShutd = 6,
  eLedState_OverCurr = 7,
  eLedState_BoosterUV = 8,
  eLedState_SpiDefect = 9,
  eLedState_CRC = 10,
  eLedState_Boost = 11,
  eLedState_STATE_COUNT
} teRte_LedErrState;   // used for u8State in tuRte_LedState

// -----------------------------------------------------------------------------
// SysVolt typdefs
typedef enum
{
  SysVolt_eLow6 = 0,
  SysVolt_eLow5 = 1,
  SysVolt_eLow4 = 2,
  SysVolt_eLow3 = 3,
  SysVolt_eLow2 = 4,
  SysVolt_eLow1 = 5,

  SysVolt_eNormal = 6,

  SysVolt_eHigh1 = 7,
  SysVolt_eHigh2 = 8,
  SysVolt_eHigh3 = 9,
  SysVolt_eHigh4 = 10,
  SysVolt_eHigh5 = 11,
  SysVolt_eHigh6 = 12,
  SysVolt_eUnknown = 255
} teRte_SysVolt_Results;

// -----------------------------------------------------------------------------
// ECU Voltage Range from Vbat - Used for checking voltage ranges for FAN for eg.
typedef struct
{
  teRte_SysVolt_Results eVoltRng;

} tsRte_VoltRng0;

// Total number of FANs
typedef enum
{
  FAN_0 = 0,
  FAN_1 = 1,
  TOTAL_NO_OF_FANS
} teRte_FanNumbers;

// Hss Fan Errors
typedef struct
{
  boolean boErrorActive;
  // teRte_HssErrorTypes eHssErrorType;
  teRte_FanNumbers eFanNumber;
} tsRte_HssFanErrorInfo;

// To be deleted
typedef struct
{
  teRte_FanNumbers eFanNumber;
  uint8 ucRequestedState;
}tsRte_HssDeviceActivationArguments;
// To be deleted


// FAN Speed request : 0 ----- OFF / 100 = ON
typedef struct
{
  uint16 unFanSpeed;
} tsRte_TgtFanVal0;

typedef struct
{
  teRte_FanNumbers eFanNumber;
  boolean boDeviceIsUsed;
}tsRte_HssDeviceIsAttachedToECU;

//Enum used to define the HeadLamp Type
//typedef enum
//{
//  eCal_Family = 0,
//  eCal_INVALID = 255
//}teRte_CodM_eHeadLampType;
//

// CtrlFan diag commands
typedef enum
{
  eCtrlFan_DiagFct0_StartExtTakeover = 0,
  eCtrlFan_DiagFct0_StopExtTakeover = 1,
  eCtrlFan_DiagFct0_SetOff = 2,
  eCtrlFan_DiagFct0_SetOn = 3,
}teRte_CtrlFan_DiagFct0_FanCmd;


// CddSwi Switch Status
typedef struct
{
  tun16Percent_1_328 unActVal;
  tiu16Current_mA unActCurrent;
  tucError ucErrOpenLoad;
  tucError ucErrShort2VBAT;
  tucError ucErrShort2GND;
  tucEftDataHwStatus ucHwState;
}tsRte_SwitchStatus;

typedef struct
{
  tsRte_SwitchStatus sSwitchStatus[CFG_OUTPUT_HSS];
}tsRte_HssStatus;

typedef struct
{
  boolean boHss3_Sh2GndStatus;
  boolean boHss3_OpenLoadStatus;
  boolean boHss3_Sh2VbatStatus;
  boolean boHss3_Enabled;
}tsRte_Hss3Status;

typedef struct
{
  uint8          ucErrShortToGnd[CFG_OUTPUT_HSS];  // error state of short to GND
  uint8          ucErrShortToVbat[CFG_OUTPUT_HSS]; // error state of short to Vbat
  uint8          ucErrOpenLoad[CFG_OUTPUT_HSS];    // error state of openload
} tsRte_CtrlSwiErrState;

//General feedback for diagnose
typedef enum
{
  eDiag_ProcessingDone = 0,
  eDiag_RequestOutOfRange,
}teRte_DiagFeedback;

// Rsens
typedef struct
{
  sint16 s16_NTCTemperatureCelsius[12];
  teRte_SigQty eSigQty[12];
  uint8 eErrTypeA[12];
} tsRte_NTCTemperature;

typedef struct
{
  uint16 unTempMilliVolt;
  teRte_SigQty eQty;
}tsRte_MatrixPcbTemp;

typedef struct
{
  uint8 ucBinning;
  teRte_SigQty eSigQty;
} tsRte_Binning0;


//
typedef tsRte_Binning0 tisBinningResistorArr[20];

typedef enum
{
  eBinningClass0 = 0,
  eBinningClass1 = 1,
  eBinningClass2 = 2,
  eBinningClass3 = 3,
  eBinningClass4 = 4,
  eBinningClass5 = 5,
  eBinningClassErr = 255,
} teRte_RsensBinningClass;

// -----------------------------------------------------------------------------
// Structure for LED channel currents and duty cycle that will be read from CtrlLed
typedef struct
{
  uint16  unCurrent;
  uint16  unDutyCycle;
} tsRte_TgtLedSig0;

typedef struct
{
  uint16  unCurrent;
  uint16  unDutyCycle;
} tsRte_TgtLedSig13;

// -----------------------------------------------------------------------------
// Structure for LED channel currents and duty cycle that will be sent to CddLed
typedef struct
{
  tsRte_TgtLedSig0 asTgtVal[12U];
  uint8            ucCrc;
}tsRte_TgtLedSig0_ASIL;

// -----------------------------------------------------------------------------
// Structure for LED channel F-bit in case of force turn OFF
typedef struct
{
  boolean aboLedChFbit[12U];
}tsRte_LedChFbit;

// -----------------------------------------------------------------------------
// Structure for LED channel intensity and ramp time
typedef struct
{
  uint16 unTgtIntensity;
  uint16 unRampTime;
  boolean boFBit;
}tsRte_TgtLedVal0;

// -----------------------------------------------------------------------------
// Structure for LED channels intensity and ramp time
typedef struct
{
  tsRte_TgtLedVal0 asTgtLedVal[CFG_LSM_LED_ILLUMINANT_NR];
}tsRte_TgtLedVal0Arr;

// -----------------------------------------------------------------------------
// Structure for Illuminants state
typedef struct
{
  /* 1  */ uint16 bLedOL : 1U;  //buck-> open load
  /*    */ uint16 bLedSG : 1U;  //buck-> short to ground
  /*    */ uint16 bLedSB : 1U;  //buck-> short to battery
  /*    */ uint16 bLedVL : 1U;  //buck-> voltage low/under voltage
  /*    */ uint16 bLedVH : 1U;  //buck-> voltage high/over voltage
  /*    */ uint16 bLedTS : 1U;  //buck-> thermal shoutdown
  /*    */ uint16 bLedOC : 1U;  //buck-> over current
  /*    */ uint16 bLedSPI : 1U;  //buck-> SPI
  /*    */ uint16 bLedCRC : 1U;  //buck-> CRC
  /*    */ uint16 bLedBoost : 1U;  //buck-> Boost
  /*    */ uint16 bMtxCC : 1U;  //matrix-> corupt communication
  /*    */ uint16 bMtxLC : 1U;  //matrix-> loss communication
  /*    */ uint16 bMtxPD : 1U;  //matrix-> pixel defect
  /*    */ uint16 bMtxVccXSG : 1U;  //matrix-> Vccx short to ground
  /* 14 */ uint16 bMtxVccXSB : 1U;  //matrix-> Vccx short to battery
  /* 15 */ uint16 bMtxEeprom : 1U;  //matrix-> Eeprom no access/ wrong checksum
}tsCtrlLed_tsIllErr; //should be match with CtrlLed Illuminant error struct

typedef union
{
  tsCtrlLed_tsIllErr bIllErr;
  uint16 unRaw;
}tuCtrlLed_IllErr;

typedef struct
{
  tuCtrlLed_IllErr uIlluminantState[CFG_LSM_LED_ILLUMINANT_NR];
  boolean boIlluminantStatus[CFG_LSM_LED_ILLUMINANT_NR];
  uint8 ucIlluminantFctName[CFG_LSM_LED_ILLUMINANT_NR];
}tsRte_LedErrStateArr;

// Structure for CtrlLed state
typedef struct
{
  uint8 aLedStates[12];
  boolean boVinBoostOk[12];
}tsRte_SysMon_LedStates;

// Structure for Diag module 
typedef struct
{
  boolean aboChStates[12];
}tsRte_CtrlLed_ChStatesDiag;

// Structure for light functions state to be sent on Rte
// 0 = OK, 1 = NOK
typedef struct
{
  boolean boLb_State;
  boolean boSbl_State;
  boolean boTi_State;
  boolean boHb_State;
  boolean boGfHb_State;
  boolean boDrl_State;
  boolean boPos_State;
}tsRte_LgtFctState;

// Structure for light functions status to be sent on Rte
// 0 = OFF, 1 = ON
typedef struct
{
  boolean boLb_Status;
  boolean boSbl_Status;
  boolean boTi_Status;
  boolean boHb_Status;
  boolean boGfHb_Status;
  boolean boDrl_Status;
  boolean boPos_Status;
  boolean boFog_Status;
  boolean boSM_Status;
}tsRte_LgtFctStatus;
typedef struct
{
  uint16 unPxlState;
  uint16 unPxlMode;
}tsRte_PxlOutput;

// -----------------------------------------------------------------------------
// Standard light high beam request
typedef enum
{
  eHb_Off = 0U,
  eHb_Manual = 1U,
  eHb_Flash = 2U
}teRte_StdLgtHb_Req;

// -----------------------------------------------------------------------------
// Afs mode signal
typedef enum
{
  eLb_to_PXA_AfsOff = 0U,
  eLb_to_PXA_CountryLight = 1U,
  eLb_to_PXA_MotorwayLight = 2U,
  eLb_to_PXA_TownLight = 3U,
  eLb_to_PXA_BadWeather_Lhd = 4U,
  eLb_to_PXA_BadWeather_Rhd = 5U,
  eLb_to_PXA_Foggy_Lhd = 6U,
  eLb_to_PXA_Foggy_Rhd = 7U,
  eLb_to_PXA_LB_Boosted = 8U,
  eLb_to_PXA_Pedestrian = 9U,
  eLb_to_PXA_Adjustment = 10U,
  eLb_to_PXA_Adjustment_Blink = 11U,
  eLb_to_PXA_TestLightDistribution = 12U
}teRte_AfsModeSig_sVal;


//--------------------------------------------------------------------------------------------
// AfsM:Enumeration defined to represent the light distributions for the FctR interface.
//--------------------------------------------------------------------------------------------
//THIS IS TEMPORARY - to be discussed the structure
typedef enum
{
  ePixelMode_Off = 0,
  ePixelMode_TownMode,
  ePixelMode_LowBeamMode,
  ePixelMode_EcoMode,
  ePixelMode_TouristMode,
  ePixelMode_HighBeamMode,
  ePixelMode_AdverseWeather,
  ePixelMode_Adjustment,
  ePixelMode_Animation,
  ePixelMode_AdjustmentLightBlinkPhase
}teRte_AfsLgtFctMgr_LightDistribution;



// -----------------------------------------------------------------------------
// Afs Dbl command
typedef struct
{
  uint8 Primary; // use ePrimaryCmd
  uint8 Secondary;
} tsRte_AfsDblCmd;

// -----------------------------------------------------------------------------

typedef tsRte_TgtLedSig0 tsRte_TgtLedSig0Arr[12U];


typedef enum
{
  eRteCddLed_NoSupport = 0,  // not supported due to EFT data
  eRteCddLed_Reset = 1,  // still in "reset" state
  eRteCddLed_Disabled = 2,  // LED off
  eRteCddLed_DiagIdle = 3,  // normal operation, no test
  eRteCddLed_StatusOk = 4,  // normal operation
  eRteCddLed_ErrOpenLoad = 5,  // open load
  eRteCddLed_ErrShortToGnd = 6,  // short to GND
  eRteCddLed_ErrShortToUbat = 7,  // short to Ubat
  eRteCddLed_ErrUnderVoltage = 8,  // voltage of LED string too low
  eRteCddLed_ErrOverVoltage = 9,  // voltage of LED string too high
  eRteCddLed_ErrThermShutdn = 10,  // thermal shutdown
  eRteCddLed_ErrOvercurrent = 11,  // overcurrent
  eRteCddLed_ErrSpi = 12,  // SPI error
  eRteCddLed_ErrCrc = 13,   // CRC error
  eRteCddLed_ErrcBoost = 14,   // Booster error
} teRte_LedErrStatus;

typedef struct
{
  teRte_LedErrStatus eLedErrStatus;
  boolean boVinBoostOk;
}tsRte_ChLedStates;

// -----------------------------------------------------------------------------
// Led Status sent from CddLed to SysMon
typedef struct
{
  tsRte_ChLedStates aLedStates[12];
  uint8 ucCrc;
}tsRte_LedStates;

typedef struct
{
  boolean aboBoostDefect[1];
}tsRte_BoostState;

// -----------------------------------------------------------------------------
// CRC8 Error Status on TgtLedSig0 CRC8 integrity sent from CddLed to SysMon
typedef struct
{
  boolean boCrc8ErrorStatus;
  uint8 ucCrc;
}tsRte_TgtLedSig0_FaultStatus_ASIL;

typedef struct
{
  uint32 ulDisableErrE2E;
  uint32 ulDisableErrOpenLoad;
  uint32 ulDisableErrOverCurrent;
  uint32 ulDisableErrShortToGnd;
  uint32 ulDisableErrShortToUbat;
  uint32 ulDisableErrSpi;
  uint32 ulDisableErrThermalShutdown;
  uint32 ulDisableErrUnderVoltage;
  uint32 ulDisableErrOverVoltage;
}tsRte_ChLedSettings;

// -----------------------------------------------------------------------------
/// \struct  tsRte_TgtPxlSig0Arr
///
/// \brief  structure containing Matrix Pixel intensities for each logical unit
///
/// \descr
///
// -----------------------------------------------------------------------------
#if defined (CFG_VARIANT_FULL) || defined(UNIT_TEST)
typedef struct
{
  uint16  unPxl_Int[CFG_LOGICAL_UNITS]; //logical unit    
}tsRte_TgtPxlSig0Arr;
#endif


// ----------------------------------------------------------------------------
// Typdef Pow: POW_PXL
// ----------------------------------------------------------------------------

typedef struct
{
  uint8 ucPowPxlFact0;   //Power Factor Pixel 1; 0x00 - 0x64: 0�100% Resolution : 1 %
  uint8 ucPowPxlFact1;   //Power Factor Pixel 2; 0x00 - 0x64: 0�100% Resolution : 1 %
  uint8 ucPowPxlFact2;   //Power Factor Pixel 3; 0x00 - 0x64: 0�100% Resolution : 1 %
  uint8 ucPowPxlFact3;   //Power Factor Pixel 4; 0x00 - 0x64: 0�100% Resolution : 1 %
  uint8 ucPowPxlFan;     //Pixel Fan Control; 0x00 - 0xFF: Fan control
  uint8 ePowPxlRstAck;   //Pixel Reset Acknowledge; teRte_PowPxlRstAck
} tsRte_PowPxl;

typedef struct
{
  sint16    nVal;
  teRte_SigQty eQty;
}tsRte_PcbTemperatureMsg;

typedef struct
{
  uint16 unDutyHSS3;
}tsRte_CpmHSS3Duty;

typedef struct
{
  tsRte_PowPxl        PowPxl;     // Power pxl signals
  teRte_SigQty    ePowPxlQty;  // Quality factor
} tsRte_TgtPowPxl0;


typedef struct
{
  uint8 StatPxlInfoNR : 1;      //PXL_NR : not ready to operate, LED drivers and Light distribution cannot be switched On
  uint8 StatPxlInfoKA : 1;      //PXL_KA: not ready to be switched off, HSS cannot be turned off
  uint8 StatPxlInfoUOV : 1;     //PXL_UOV : UV/OV HSS voltage detection, leads to a deactivation
  uint8 StatPxlInfoOTEMP : 1;   //PXL_OTEMP : Thermal shutdown, all leds are short circuited, system is Off , LED drivers have to be switched off
  uint8 StatPxlInfoSOURCE : 1;  //PXL_SOURCE: Current source is not at the expected current level, performance is either highly restricted or completely off
  uint8 Reserved : 3;
} tsRte_StatPxlInfo;
typedef union
{
  tsRte_StatPxlInfo      Bit;
  uint8             ucRaw;
} tuRte_StatPxlInfoType;
typedef struct
{
  uint8 ucStatPxlTemp0;      //Status Pixel Temperature 1 0x00 - 0xC8: -40��160� Resolution: 1�
  uint8 ucStatPxlTemp1;      //Status Pixel Temperature 2 0x00 - 0xC8: -40��160� Resolution: 1�
  uint8 ucStatPxlTemp2;      //Status Pixel Temperature 3 0x00 - 0xC8: -40��160� Resolution: 1�
  uint8 ucStatPxlTemp3;      //Status Pixel Temperature 4 0x00 - 0xC8: -40��160� Resolution: 1�
  uint8 ucStatPxlFan;        //Status Pixel Fan; 0x00 - 0xFF: Fan control
  tuRte_StatPxlInfoType StatPxlInfo;  //Status Pixel Info
  uint8 eStatPxlHbErr;       //Status Pixel High Beam Error; teRte_StatPxlHbErr
  uint8 eStatPxlLdHb;        //Status Pixel High Beam Light Distribution;  teRte_AfsMCtrHbLd
  uint8 eStatPxlLbErr;       //Status Pixel High Beam Error; teRte_StatPxlLbErr
  uint8 eStatPxlLdLb;        //Status Pixel High Beam Light Distribution;  teRte_AfsMCtrLbLd
  uint8 eStatPxlRst;         //Status Pixel process reset; teRte_StatPxlRst
} tsRte_StatPxl;

typedef enum
{
  E_TYPE_SNA = 0,
  E_TYPE_FAILED_ShrtGnd = 1,
  E_TYPE_FAILED_ShrtVbatOpenload = 2,
  E_TYPE_FAILED_InvalidType = 3,
  E_TYPE_PASSED = 4
}tieErrTypeA;

typedef struct
{
  tsRte_StatPxl       StatPxl;     // Stat pxl signals
  teRte_SigQty    eStatPxlQty;  // Quality factor
  tieErrTypeA         eErrTypeA;
} tsRte_ActStatPxl0;






// -----------------------------------------------------------------------------
// IoHwAb typdefs

typedef unsigned long tiu32Voltage_mV;
typedef unsigned short int tiu16Voltage_mV;

typedef unsigned char tieMountingSide;
typedef unsigned long tieMountingSideRaw;
typedef unsigned char tieHssState;
typedef tiu16Voltage_mV(*tpfRte_NtcRead)(void);

typedef struct
{
  tiu16Voltage_mV aunNtcVoltage[14];
}tsRte_Voltage_mV;

typedef enum
{
  eVccx_noError = 0, //No error detected for Vccx voltage line
  eVccx_Short2GND = 1, //Short to ground detected for Vccx line
  eVccx_Short2Vbat = 2, //Short to battery detected for Vccx line
}teRte_VccxLineState;
typedef struct
{
  sint32 alSensBalance[CFG_CntSens];
}tsRte_SensorBalance;

typedef struct
{
  uint16 aucSensRaw[CFG_CntSens];
}tsRte_SensorRaw;

typedef struct
{
  uint8 ucNrNTC;
  tpfRte_NtcRead* Fct;
}tsRte_Ntc;

// -----------------------------------------------------------------------------
// CodM typdefs
typedef struct
{
  uint16 unSafetyTiMin_Curent;
  uint16 unSafetyTiMin_Pwm;
  uint16 unSafetyLbMin_Curent;
  uint16 unSafetyLbMin_Pwm;
  teRte_SigQty eQty;
}tsRte_CodMinBrightness_Param;

// -----------------------------------------------------------------------------
// Dem
// -----------------------------------------------------------------------------
#ifndef UNIT_TEST

#define Rte_Call_DemPrj_ReportErrorStatus(arg1, arg2)     \
{                                                         \
  if(arg1 > 0u)                                           \
  {                                                       \
    Dem_SetEventStatus(arg1,arg2);                        \
  }                                                       \
}

#define Rte_Call_DemPrj_Set_DiagWindow(arg1)             \
{                                                        \
  Dem_Set_Init_Window(arg1);                             \
}

typedef uint16 Dem_EventIdType;

#else


void Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus);
#define Rte_Call_DemPrj_ReportErrorStatus(arg1, arg2) \
  (Dem_SetEventStatus(arg1, arg2))

void  Dem_Set_Init_Window(boolean boWindow);
#define Rte_Call_DemPrj_Set_DiagWindow(arg1) \
  Dem_Set_Init_Window(arg1);


#endif // UNIT_TEST

// -----------------------------------------------------------------------------
// Diag
// -----------------------------------------------------------------------------
void Dem_Diag_LockDTC(boolean boEnableDTC);
#define Rte_Call_Diag_ControlDTCSetting(arg1, arg2) \
  (Dem_Diag_LockDTC(arg1))

//--------------------------------------------------------------------------------------------
// DBL
//--------------------------------------------------------------------------------------------

#if defined (CFG_VARIANT_FULL) || (UNIT_TEST) // Applicable only for FULL version
typedef struct
{
  sint16  nLimit[2];         // [1/10 mrad /20ms] Swivelling Limit Left
}
tsRte_SwiRateLimMsg;

typedef struct
{
  sint16 Hor;      // [0.1 mrad]
  uint8  Width;
} tsRte_DblAngle;

typedef enum  // states for engine state-machine
{
  eState_Init = 0,         // initial state
  eState_Nominal = 1,      // nominal phase
  eState_Adj = 2,          // Adjustment phase
  eState_Fail = 3,         // Defect
  eState_Maxsize = 5
} teRte_DblStatMain;

typedef struct
{
  tsRte_DblAngle SwivellingAngle[2];
  teRte_DblStatMain     State;
} tsRte_Dbl_SwivellingOut;


typedef enum
{
  eSubModeUnavailable,
  eSubModeAvailable,
  eSubModeFrozen,
}teRte_DblSubMode;

typedef enum
{
  eAfsState_NOTACTIVE = 0,
  eAfsState_ACTIVE = 1,
  eAfsState_HOLD = 2,
  eAfsState_ERROR = 3
} teRte_AfsState;


typedef enum
{
  Motion_Forward = 0x00,         // Motion forward
  Motion_Backward = 0x01         // Motion backward
} teRte_Motion;

typedef enum
{
  INIT_CMD = 0x00,
  PLAY_CMD = 0x01,
  PAUSE_CMD = 0x02,
  STOP_CMD = 0x03,
  RESET_CMD = 0x04
} teRte_PrimaryCmd;

typedef struct
{
  sint16 SwivelAngle[2];
  teRte_DblStatMain  DblState;
}tsRte_DblOut;

typedef struct
{
  uint8 bHighSpeed : 1;
  uint8 bSteerBack : 1;
  uint8 bStrAhead : 1;
  uint8 bReserved : 5;
}tsRte_AfsDblDriveSituation_BitType;

typedef union
{
  tsRte_AfsDblDriveSituation_BitType Bit;
  uint8 ucData;
}tsRte_AfsDblDriveSituation;

typedef struct
{
  boolean boReverseGearStatus;
  teRte_SigQty  eSigQty;
}tsRte_ReverseGearStatus;

typedef struct
{
  teDiagDbl     eDynamicBendingBeamFault;
}tsRte_Hs6_Diag_Drvled_BendingBeamFault;

typedef struct
{
  teRte_DynBendingBeamFault  eDynBendingBeamFault;
  teRte_SigQty               eSigQty; // Signal Quality
}tsRte_BendingBeamFault_OtherHL;
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)


//=============================================================================
// AppM
//=============================================================================
typedef union
{
  uint32         ulData;
  tsRte_TgtLedVal0  Bit32;
}tuRte_LedTgtVal;

typedef struct
{
  uint16    unCurrent;     // LED current    [1mA]
  uint16  unDutyCycle;   // LED duty cycle [1/65535]
}tsRte_ActLedSig0;

typedef struct
{
  uint16 unPowFact;      // LED power factor [0.1%]
}tsRte_ActLedVal0;

typedef struct
{
  uint32 sState;
  boolean boLedStatus; //FALSE - Led OFF
}tsRte_LedState0;

typedef struct
{
  uint16 unPowFact;      // Thermo power factor [0.1%]
}tsRte_TgtThermoVal0;

typedef struct
{
  uint8 eState;   // acc. to teRte_LedErrState
  boolean boLedStatus; //TRUE - led on
}tsRte_LedErrState0;

typedef struct
{
  tieHssState aeSetting[3];
}tsRteHssTarget;
//AppM Rte read LED Channels, MatrixNTC, ECU NTC commands
typedef enum
{
  eAppM_DiagFct0_ReadLedChannelsNTC = 1,
  eAppM_DiagFct0_ReadMatrixLeds_NTC,
  eAppM_DiagFct0_ReadEcuNTC,
}teRte_AppM_DiagFct0_Led_NTC_Temp;

// ----------------------------------------------------------------------------
/// input of algorithms: AFS123, AVAC, DBL (!!! preliminary !!!)
// ----------------------------------------------------------------------------

// Curvature from steering wheel angel with resolution of [0.1?]
typedef struct
{
  sint16      nCurvature;            // Curvature, mandatory signal, [0.000025 1/m]
  // calculated by steering wheel angle
  teRte_SigQty  eCurvatureQty;         // Quality of the steering wheel angle signal

  sint16      nCurvatureOpt;         // Curvature, optional signal, calculated by
  // yaw rate, lateral acceleration or wheel speed difference
  teRte_SigQty  eCurvatureOptQty;      // Quality of the related signals
}tsRte_DblCurInfo;

// -----------------------------------------------------------------------------
/// \struct  tsRte_VddHldMonMsg
///
/// \brief   tsRte_VddHldMonMsg Message
///
/// \descr   tsRte_VddHldMonMsg Message, monitoring of VddHld
///
typedef struct
{
  sint32        nCurvature;       // Filtered Curvature
  sint32        nCurvatureOpt;    // Filtered Curvature, optional signal
  teRte_SigQty     eCurvatureSigQty;    // Signal Quality
  teRte_SigQty     eCurvatureOptSigQty; // Signal Quality
} tsRte_VddHldMonMsg;

// -----------------------------------------------------------------------------
/// \struct  tsRte_VddHldOutMsg
///
/// \brief   tsRte_VddHldOutMsg Message
///
/// \descr   tsRte_VddHldOutMsg Message
///
typedef struct
{
  sint32        nCurvature;       // curvature [0.000025 1/m]
  sint32        nCurvatureGrad;   // curvature [0.000025 1/m*s]
  uint8         ucStreetClass;    // calculated street class
  uint8         ucDummy;          // fill byte
  teRte_SigQty     eSigQty;       // Signal Quality
} tsRte_VddHldOutMsg;

// Vehicle speed
typedef struct
{
  uint16 unVehicleSpeed;
  teRte_SigQty  eSigQty;
}tsRte_VehicleSpeed;
//DAT7_BSI_40E: Enum used to define steering wheel side
typedef enum
{
  eInitValue = 0,
  eLeftHandTraffic = 1,
  eRightHandTraffic = 2,
}teRte_HandTraffic;
//Structure used to define the headlamp region based on the steering wheel side
typedef struct
{
  teRte_HandTraffic eHandTraffic;
  teRte_SigQty  eSigQty;
}tsRte_HandTraffic;


typedef enum
{
  ePluggedLeft = 0,
  ePluggedRight = 1,
  eIdentityUndef = 255
} teRte_IdentityConfig;

typedef enum
{
  eMountedLeft = 0,
  eMountedRight = 1,
  eMountedUndef = 255
}teRte_MountingSide;

typedef struct
{
  uint8 aucBinningSelect[CFG_LAMP_CH_Cnt];
}tsRte_ucBinningSelect;

typedef struct
{
  uint8 aucBinClass[CFG_NTC_BIN_CNT];
  uint16 aunBinCurrent[CFG_NTC_BIN_CNT];
}tsRte_D409Binning;

#if defined (CFG_VARIANT_FULL) || defined(UNIT_TEST)

// -----------------------------------------------------------------------------
/// \struct  teRte_CddMlc_AdcQuality
///
/// \brief   Adc Quality Values
///
/// \descr   Status of the ADC signal for MLC chips
///
// -----------------------------------------------------------------------------
typedef enum
{
  CDD_MLC_QLTY_INVALID = 0,                       // Invalid Value        (Init value or Timeout)
  CDD_MLC_QLTY_SNA = 1,                       // Signal Not Available (Keep Last Value)
  CDD_MLC_QLTY_VALID = 2                        // Valid Signal         (Up-to-Date)
} teRte_CddMlc_AdcQuality;


// -----------------------------------------------------------------------------
/// \struct  tsRte_CddMlc_AdcResult
///
/// \brief   ADC results
///
/// \descr   ADC result/values including Quality Factor for each MLC device
///
// -----------------------------------------------------------------------------
typedef struct
{
  uint8 ucADC1Value;                            // Value of 8-Bit ADC
  uint8 ucADC2Value;                            // Value of 8-Bit ADC
  teRte_CddMlc_AdcQuality eQlty;                // Quality Factor
} tsRte_CddMlc_AdcResult;

typedef tsRte_CddMlc_AdcResult tasRte_MlcAdcResult[CFG_MLC_Chip_Cnt];

// -----------------------------------------------------------------------------
/// \struct  tsRte_CddMlc_LedStatus
///
/// \brief   LED Status for Cdd Mlc
///
/// \descr   LED Fault status for MLC chips
///
// -----------------------------------------------------------------------------
typedef struct
{
  uint16 unLedFault;           // Led Status Segment
} tsRte_CddMlc_LedStatus;

//Buffer which stores the faulty LED values for each MLC device
typedef tsRte_CddMlc_LedStatus tasRte_MlcLedStatus[CFG_MLC_Chip_Cnt];

//Buffer which stores the intensities for each segment of the MLC device
typedef uint16 tsRte_TgtMtxPixels_sVal[CFG_MLC_Chip_Cnt][CFG_MATRIX_LEDs_PER_CH_Cnt];

// -----------------------------------------------------------------------------
/// \enum  teRte_CddMlc_SystemMode
///
/// \brief   Cdd Mlc System Mode
///
/// \descr   System Mode chip commands
///
// -----------------------------------------------------------------------------
typedef enum
{
  CddMlc_SystemMode_Powerup = 0,                // Unconfigured Chips,
  CddMlc_SystemMode_CfgComm,                    // Set default communication Settings,
  CddMlc_SystemMode_CfgChips,                   // Configure Chip Settings,
  CddMlc_SystemMode_CfgPhases,                  // Configure Phase Shifts,
  CddMlc_SystemMode_CfgLeds,                    // Configure LED Settings,
  CddMlc_SystemMode_ClrFlts,                    // Broadcast Clear Faults
  CddMlc_SystemMode_Normal,                     // Set DutyCyles + Read FAULTS/ADCs + Monitor Chips,
  CddMlc_SystemMode_Inactive,                   // No commands are sent but driver is configured.
  CddMlc_SystemMode_Length,
}teRte_CddMlc_SystemMode;


// -----------------------------------------------------------------------------
/// \struct  tsRte_CddMlcComStatus
///
/// \brief   Cdd Mlc Communication status
///
/// \descr   Mlc chips global communication status and Power Cycles occured
///
// -----------------------------------------------------------------------------
typedef struct
{
  uint8 ucMlcStatus;      // Global Communication Status for each Mlc device
  uint8 ucPowerCycle;     // Global Power Cycle Flag for each Mlc device
}tsRte_CddMlcComStatus;

typedef struct {
  uint32 ulMlcStatus;                           // Global Communication Status for each Mlc device
  uint32 ulPowerCycleOccurred;                  // Global Power Cycle Flag for each Mlc device
  uint32 ulUartErrorsOccurred;                  // UART Communication Errors Occurrence Counter
  uint32 ulTxCommandOverrun;                    // Counter of Commands not sent during a Mlc cycle
  uint32 ulAckChipSetting;                      // Acknowledged Chip Setting Configuration
  uint32 ulAckPhaseShifts;                      // Acknowledged Phase Shifts Configuration
  uint32 ulAckLedSegments;                      // Acknowledged LED Segments Configuration
  uint8 ucMatrixIcID_List[CFG_MLC_Chip_Cnt];       // Matrix Chip ID for each device
  uint8 ucTimeoutCounter_List[CFG_MLC_Chip_Cnt];   // Reception failed counter for each device
  uint8 ucCrcFltOccurrence_List[CFG_MLC_Chip_Cnt]; // CRC ERROR count for each device
} tsRte_CddMlc_ComStatus;

// -----------------------------------------------------------------------------
/// \struct  tsRte_CddMlcComErrorStatus
///
/// \brief   Cdd Mlc Communication status (CRC corrupted)
///
/// \descr   CRC error detected on each device
///
// -----------------------------------------------------------------------------
typedef struct
{
  uint8 aboMlcCorruptedComm[CFG_MLC_Chip_Cnt];
}tsRte_MlcComErrorStatus;


typedef struct
{
  boolean boCommError;
  boolean boPxlError;
  boolean boShortToGndError;
  boolean boShortToVbatError;
}tsRte_MatrixFaultStates;


// -----------------------------------------------------------------------------
// Structure for matrix erros mapped on logical units

typedef struct {
  uint8 bLossComm : 1u;
  uint8 bCoruptComm : 1u;
  uint8 bPxlFault : 1u;
  uint8 Reserved : 5u;
}tsRte_CtrlPxl_bErr;


typedef union
{
  tsRte_CtrlPxl_bErr  bErr;
  uint8               ucRaw;
}tuRte_CtrlPxl_bErr;

typedef struct
{
  tuRte_CtrlPxl_bErr auMtxErrorStatus[CFG_LOGICAL_UNITS];
}tauRte_CtrlPxl_Mtx_bErr;

typedef struct
{
  boolean aboMtxSegmentFault[CFG_MATRIX_MAX_NO_PXL];
}tsRte_boMtxSegmentFault;

typedef struct
{
  uint8 aucActualPercMtxPWM[CFG_MATRIX_MAX_NO_PXL];
}tsRte_ucActualPxlPWM;


//typedef struct
//{
//  uint8 ucBinning[CFG_MATRIX_BUCKs];
//  teRte_SigQty eBinningClassSigQty[CFG_MATRIX_BUCKs];
//} tsRte_CtrlPxl_BinEEprom;

typedef tsRte_Binning0 tasRte_CtrlPxl_BinEEprom[CFG_LED_CHANNELS_NR];

//structure used to keep information from Nvm Block in case MLC Eeprom is corrupted

//keep this structure the same as the Nvm Blocks
typedef enum
{
  DemData = 2,
  ErrCustPs,
  FreezeFrameDataPs,
  DeltaPwmPara,
  FactoryData,
  AutonomMode,
  Statistics,
  DK_FD,
  VinNumber,
  CtrlPxlNvmContent,
  HeadlampData
}teRte_NvmBlockId;

typedef struct
{
  uint8*            pucData;
  uint16             unSize;
}tsRte_NvMBlock;


typedef struct
{
  void(*pfnMatrixEECbkSuccess)(void);
  void(*pfnMatrixEECbkFail)(void);
}tsRte_MatrixEE0CbkFn;

typedef struct
{
  uint8 *pucMatrixEEbuffer;
  uint16 unMatrixEEStartAdd;
  uint16 unMatrixEELength;
  tsRte_MatrixEE0CbkFn sMatrixEE0CbkFn;
}tsRte_MatrixEE0peration;

typedef struct
{
  boolean boEepromWrngChksumFault;
  boolean boEepromNoAccessFault;
}tsRte_MtxEeprom_ErrStatus;
#endif

/// \struct  tChannel
///
/// \brief   Mxb output Channel
///
/// \descr
///
typedef struct
{
  sint16 PowerFactor;
  sint16 MaximalIntensity;
  uint8  NormalizedDimmingTimeUp;
  uint8  NormalizedDimmingTimeDown;
  sint16 EdgeLeft;
  sint16 EdgeRight;
  sint16 EdgeTop;
  sint16 EdgeBottom;
  sint16 Type;
  sint16 Distance;
  sint16 DistanceLeft;
  sint16 DistanceRight;
} tChannel;

// -----------------------------------------------------------------------------
/// \struct  tAdbOut
///
/// \brief   Mxb output msg
///
/// \descr
///
typedef struct
{
  tChannel  Channel[2];
  uint8     State;
} tAdbOut;

// To be removed when the client ports will be available
typedef struct
{
  tNvmPara_CodingArea* psCodingParameters_Blocks;
  tParaFct0_Cmd       eCodingState;
}tsRteCodingParameters;
// To be removed when the client ports will be available
// -----------------------------------------------------------------------------
/// \struct  tAdbStatus
///
/// \brief   Mxb Status msg
///
/// \descr
///
typedef struct
{
  boolean  CurtainEffectStatus;
  boolean  HBBStatus;
} tAdbStatus;

// -----------------------------------------------------------------------------
/// \struct  tsRte_PxaIntensityMatrix
///
/// \brief
///
/// \descr
///
#if defined (CFG_VARIANT_FULL) || defined(UNIT_TEST)

typedef struct
{
  uint16  Top[CFG_MATRIX_RAW_CNT];
  uint16  Mid[CFG_MATRIX_RAW_CNT];
  uint16  Bottom[CFG_MATRIX_RAW_CNT];
}tsRte_PxaIntensityMatrix;
#endif


// ----------------------------------------------------------------------------
// Typdef Stat: STAT_STP
// ----------------------------------------------------------------------------
typedef enum
{
  StatStpMode_Off = 0x00,            //Off (default )
  StatStpMode_UnRef = 0x01,          //not referenced
  StatStpMode_Referencing = 0x02,    //is referencing
  StatStpMode_Stopped = 0x03,        //stopped
  StatStpMode_Moving = 0x04,         //is moving
  StatStpMode_Err = 0x05            //Error
} teRte_StatStpMode;

typedef enum
{
  StatStpTw_Normal = 0x00,           //Normal mode (default )
  StatStpTw_Active = 0x01,           //Thermal warning activ
} teRte_StatStpTw;


typedef enum
{
  eNominalVoltage = 0,  // Normal Voltage Operation
  eUndervoltage,        // Under Voltage Operation
  eReservedVoltage,     // Reserved value
  eOverVoltage          // Over Voltage Operation
}teRte_StpVoltageState;

typedef enum
{
  eLvlStatus_InDefect = 0,     // Automatic levelling function in defect
  eLvlStatus_Inhibited,        // Automatic levelling function inhibited
  eLvlStatus_NotImplemented,   // Automatic levelling function not implemented
  eLvlStatus_Active            // Automatic levelling function active
}teRte_StpLvlStatus;

typedef enum
{
  eNoElectricalDefect = 0,  // No Electrical Defect
  eOpenCircuitDefect,       // Open Load Defect
  eShortCircuitDefect,      // Short Circuit Defect
  eReservedElectrical       // Reserved value
}teRte_StpElectricalState;

typedef enum
{
  eNoThermalWarning = 0,    // Normal Temperature
  eColdTemperature,         // Cold Temperature
  eHighTemeratureWarning,   // High Temperature Warning
  eHighTemperatureSD        // High Temperature Shut-Down
}teRte_StpThermalState;

typedef enum
{
  eNoStepLoss = 0,    // No Steploss Error
  eStepLossRisk       // Steploss Error
}teRte_StpStepLosState;

typedef enum
{
  eWaitNewRefCmd = 0,   // Wait for New Reference Command
  eRefInProgres,        // Reference In Progres
  eRefSuccessfully,     // Reference Done
  eRefReserved,         // Reserved Value
}teRte_StpRefRunState;


typedef struct
{
  sint16 nStatStpPosVer;                             //Actual Position of Vertical Stepper;(0-1000): 0,01*raw-5;0x3FF = "(invalid)"
  sint8  cStatStpPosDegree;                          //Actual Position of Vertical Stepper(degree) with 0.01 resolution.
  teRte_StpRefRunState     eStatStpModeVer;             //Actual Operating Mode of Vertical Stepper; teRte_StatStpMode
  teRte_StpStepLosState    eStatStpStepLoss;            //Safety StepLoss information
  teRte_StpThermalState    eStatStpThermalState;        //Thermal State of Vertical Stepper; teRte_StatStpTw
  teRte_StpElectricalState eStatStpElectricDefect;      //Electrical Defect state;
  teRte_StpVoltageState    eStatStpVoltageState;        //Voltage State of Vertical Stepper;
  teRte_StpLvlStatus       eStatStpLevelStatus;         //Status of automatic levelling
  boolean              boStpFaultStatus;            //Stepper Fault Status
  boolean              boStpIsMoving;               // TRUE if Stepper is moving
  boolean              boStpCommDef;                // Communication Defect
  boolean              boStpPosDef;                 // Position Defect
} tsRte_StatStp;

typedef struct {
  boolean boLvl_Elec_Defect;
  boolean boLvl_Temp_Defect;
  boolean boLvl_StepLoss;
  boolean boLvl_Moving;
  sint16  snLvl_Degree_Ctrl;
  sint16  snLvl_Pos_Feedback;
}tsRte_LevellingValidationFrames;

typedef struct
{
  tsRte_StatStp                   StatStp;     // Stat stepper signals
  tsRte_LevellingValidationFrames sLvlValidationFrames;
  teRte_SigQty                    eStatStpQty;  // Quality factor
} tsRte_ActStatStp0;

typedef enum
{
  eStpSubModeUnavailable,
  eStpSubModeAvailable,
  eStpSubModeAftersale,
  eStpSubModeFrozen,
  eStpSubModeFactory

}teRte_eStpSubMode;

typedef enum
{
  eStpState_Init = 0,     // initial state
  eStpState_Ref = 1,      // reference run active
  eStpState_Adj = 2,      // Adjustment phase
  eStpState_Fail = 3,     // stepper defect
  eStpState_STT = 4,      // Cranking phase
  eStpState_Maxsize = 5
} teRte_eStpStatMain;

// Headlamp fault status
typedef enum
{
  eStpNo_Failure = 0U,
  eStpFrozen_Failure = 1U,
  eStpTransition_Failure = 2U
}teRte_eStpHeadlampFaultStatus;

typedef struct
{
  teRte_eStpSubMode eADL_MODE;
  teRte_eStpStatMain eADL_PHASE;
  teRte_eStpHeadlampFaultStatus eLvlAdjHeadlampFault_R;
  teRte_eStpHeadlampFaultStatus eLvlAdjHeadlampFault_L;
  sint16 snVehAttitudeFactory;
  boolean boLvlAdjFunctFault_L;
  boolean boLvlAdjFunctFault_R;
}tsRte_CtrlStpValidation;

typedef enum
{
  eMovementToTop = 0x11,
  eMovementToBottom = 0x12,
  eMovementToZero = 0x13,
  eSequence1 = 0x14,
  eSequence2 = 0x15,
  eStop = 255
}teRte_StepperRoutineControlRequest;

typedef enum
{
  eStpControl_Start = 0,
  eStpControl_Stop,
  eStpControl_Results,
  eStpControl_Unknown
}teRte_StepperRoutineControl;

typedef enum
{
  eBothActuators = 0,
  eLeftActuator,
  eRightActuator
}teRte_StepperRoutineControlSide;

typedef enum
{
  eDD05 = 0xDD05,
  eDF10 = 0xDF10,
  eDF11 = 0xDF11,
  eDF12 = 0xDF12,
  eDF13 = 0xDF13,
  eDID_Invalid = 0xFFFF
}teRte_StepperRoutineControlDID;

typedef struct
{
  teRte_StepperRoutineControl eStpControl;
  teRte_StepperRoutineControlSide eStpSide;
  teRte_StepperRoutineControlRequest eStpRequest;
  boolean boRequestStatus;
  boolean boRequestAckStatus;
  teRte_StepperRoutineControlDID eStpDID;
  sint16 snPosRequest;
  uint8  ucStartSequence;
}tsRte_StepperRoutineControl;

#if defined (CFG_VARIANT_FULL) || (UNIT_TEST)
typedef enum
{
  eAfsControl_Start = 0,
  eAfsControl_Stop,
  eAfsControl_Results,
  eAfsControl_Unknown
}teRte_AfsRoutineControl;

typedef enum
{
  eAfs_Off = 1,
  eAfs_Town = 2,
  eAfs_Pedestrian = 3,
  eAfs_Country = 4,
  eAfs_Motorway = 5,
  eAfs_Boost = 6,
  eAfs_Bad_Weather_L = 7,
  eAfs_Bad_Weather_R = 8,
  eAfs_Fog_L = 9,
  eAfs_Fog_R = 10,
  eAfs_Sequence_L = 11,
  eAfs_Sequence_R = 12,
}teRte_AfsStateRoutineControlRequest;

typedef struct
{
  teRte_AfsRoutineControl eAfsControl;
  teRte_AfsStateRoutineControlRequest eAfsRequest;
  boolean boRequestStatus;
  boolean boRequestAckStatus;
}tsRte_AfsRoutineControl;

typedef struct
{
  teRte_Ctrl_AFS eDiagRequestAfsState;
  teRte_LowBeamBoostAllowed eLowBeamBoostAlwd;
  teRte_PedestrianAllowed ePedestrianAlwd;
  boolean boDiagRequestStatus;
  boolean boDiagRequestAcksStatus;
}tsRte_AfsDiagControl;
#endif

// The bit order must match the order of light functions in teFctR_LightFunctions enum.
typedef struct
{
  uint32 biLB_TownLight : 1;      //  0
  uint32 biLB_Pedestrian : 1;      //  1
  uint32 biLB_CountryLight : 1;      //  2
  uint32 biLB_MotorwayLight : 1;      //  3
  uint32 biLB_Boost : 1;      //  4
  uint32 biLB_AdverseWeather_RHD : 1;      //  5
  uint32 biFoggyWeather_RHD : 1;      //  6
  uint32 biLB_AdverseWeather_LHD : 1;      //  7
  uint32 biFoggyWeather_LHD : 1;      //  8

  uint32 biLB_Reserved : 4;

  uint32 biHB_HighBeam : 1;      //  13   //if illuminant 14 has a problem => do not report (clear this bit)
  uint32 biHB_Boost : 1;      //  14   //if illuminant 14 has a problem => do not report (clear this bit)
  uint32 biHB_AimingMode : 1;      // 15  //if illuminant 14 has a problem => do not report (clear this bit)
  uint32 biHB_Adjustement_Mode : 1;      // 16        //if illuminant 14 has a problem => do not report (clear this bit)
  uint32 biHB_FlashToPass : 1;      // 17    //if illuminant 14 has a problem => do not report (clear this bit)

  uint32 biHB_Reserved2 : 4;

  uint32 biDRL_DaytimeRunningLight : 1;      // 22
  uint32 biPOS_PositionLight : 1;      // 23
  uint32 biPKL_ParkingLight : 1;      // 24
  uint32 biSBL_StaticBendingLight : 1;      // 25
  uint32 biCL_CorneringLight : 1;      // 26
  uint32 biFL_FogLight : 1;      // 27
  uint32 biSM_SideMarker : 1;      // 28

  uint32 biTI_TurnIndicator : 1;      // 29 - Only turn indicator request
  uint32 biTI_TiCmdPos : 1;           // 30 - when TI Comand (levier)
  uint32 biTI_TiReqPos : 1;           // 31 - when TI is Blinking
}tsRte_TgtLgtFctBits;

typedef union
{
  tsRte_TgtLgtFctBits Bits;
  uint32 ulRaw;
}tuRte_TgtLgtFct;

typedef struct
{
  boolean boRequestStatus;
  tuRte_TgtLgtFct uTgtLgtFct;
}tsRte_Ld_ActivationRoutineControl;
/// Used for port that is provided by SWC Anima
typedef struct
{
  uint16 unTgtAni[103]; ///< [1/0x8000 %] 0 = 0%, 0x8000 = 100%, TODO replace magic number 103 with a #define (should be equal to ANIMMA_NR_PIXELS)
  boolean boPriority;     ///< [0 - 15] 0...14: animation is active, 15 (or greater): animation is not active
} tsRte_TgtAniArr;

//used for TI Scrolling
typedef struct
{
  uint16 unTgtAniScr[1]; ///< [1/0x8000 %] 0 = 0%, 0x8000 = 100%, TODO replace magic number 103 with a #define (should be equal to ANIMMA_NR_PIXELS)
  boolean boPriorityScr;     ///< [0 - 15] 0...14: animation is active, 15 (or greater): animation is not active
} tsRte_TgtAniArrScr;

typedef struct
{
  boolean boScrollingTIPresent_Stat;
  boolean boScrollingDRLPresent_Stat;

}tScrollingPresent_Stat;

typedef struct
{
  uint8 ucPixelIntensity[103];
}tsRte_DIDPixelActivation;
// CtrlSwi

typedef unsigned char tieError;

typedef  uint16 tiaunSwitchTgtVal[CFG_OUTPUT_HSS];

typedef unsigned char tieEftDataHwStatus;

typedef struct
{
  tieSupportInfo  eStatSupported[CFG_OUTPUT_HSS];
  tieHssState     eStatOn[CFG_OUTPUT_HSS];
  tiu16Current_mA unStatCurrent[CFG_OUTPUT_HSS];
  tieError        eErrShortToGnd[CFG_OUTPUT_HSS];
  tieError        eErrOpenLoad[CFG_OUTPUT_HSS];
  tieError        eErrShortToVBat[CFG_OUTPUT_HSS];
}tisHssStatusError;

typedef struct
{
  boolean boErrSh2Gnd[CFG_OUTPUT_HSS];
  boolean boErrOpenLoad[CFG_OUTPUT_HSS];
  boolean boErrSh2Vbat[CFG_OUTPUT_HSS];
}tRteCtrlSwi_ErrorFlags;

// CtrlSwi_End


//CPM

typedef struct tsRteLsTargetPercArr12_tag {
  uint16 unCurrent[12]; /*
  Unit: PERCENT
  LSB: 0.0030517578125 OFF: 0 MIN/MAX: 0 .. 199.996948242188 */
  uint16 unDutyCycle[12]; /*
  Unit: PERCENT
  LSB: 0.0030517578125 OFF: 0 MIN/MAX: 0 .. 199.996948242188 */
} tsRteLsTargetPercArr12;

#ifndef UNIT_TEST
typedef struct tE2eRawState_tag {
  TE_ReturnType retStatus[CONF_D_NB_CHUNKS_PDU1];
  EECO_TEP_ProfileOneChunkStatusPtr pte_ChunkStateE2E[CONF_D_NB_CHUNKS_PDU1];
}tE2eRawState;
#endif

typedef struct tHS6_DAT_VSM_2AE {
  uint8  ucWarningMode;
  uint8  ucEtatClignotants;
  uint8  ucLeftTurnIndicatorCmd;
  uint8  ucRightTurnIndicatorCmd;
  uint8  ucTurnIndicatorScrolling;
}tHS6_DAT_VSM_2AE;

typedef struct tHS6_DAT_VSM_34E {
  uint8  ucFrontFogBeamCmd[2];
  uint8  ucAfsModeCmd;
  uint8  ucGfhbCmd;
  uint8  ucLowBeamBoostAllowed;
  uint8  ucPedestrianAllowed;
  uint8  ucAimingModeActivation;
  uint8  ucMotorwayDetection;
  uint8  ucDayTimeRunningLightCmd[2];
  uint8  ucLowBeamCmd[2];
  uint8  ucHighBeamCmd[2];
  uint8  ucSideMarkerCmd[2];
  uint8  ucFrontPositionCmd[2];
  uint8  ucHeadlampFlashBeamCmd;
  uint8  ucEtatFeuxStationnement;
  uint8  ucConfigVhl;
}tHS6_DAT_VSM_34E;

typedef struct tHS6_COMMANDES_VSM_036 {
  uint8  ucPhaseVie;
  uint8  ucInterdMemoDef;
  uint8  ucDemEffacDef;
  uint8  ucDiagMux;
}tHS6_COMMANDES_VSM_036;

typedef struct tHS6_DAT_BSI_432 {
  uint8  ucVESMainState;
  uint8  ucElectricNetworkState;
}tHS6_DAT_BSI_432;

typedef struct tHS6_DYN_ABR_38D {
  uint16 unVehicleSpeed;
  uint8  ucVehicleSpeedDispo;
  uint8  ucChksumTrmeDynUcFrein;
  uint8  ucCptProcess4B38D;
  uint8  aucCHKSUM[8];
}tHS6_DYN_ABR_38D;

typedef struct tSysMon_SendFrame457 {
  uint8  ucDynamicBendingBeamFault;
  uint8  ucGfhbFault;
  uint8  ucStaticBendingBeamFault;
  uint8  ucLevellingAdjustFault;
  uint8  ucLowBeamFault;
  uint8  ucFrontTurnIndicatorFault;
}tSysMon_SendFrame457;

typedef struct tSysMon_SendFrame477 {
  uint8  ucGfhbFault;
  uint8  ucStaticBendingBeamFault;
  uint8  ucLowBeamFault;
  uint8  ucFrontTurnIndicatorFault;
  uint8  ucLevellingAdjustFaultR;
}tSysMon_SendFrame477;

typedef struct tsRte_PowerFactor {
  uint8  ucPowerFactor[12u];
}tsRte_PowerFactor;

typedef struct tsRtePowFactTemp {
  sint16 snNTCTemperatureCelsius[CFG_THERMOZONES_NR];
  uint8  ucPowerFactor[CFG_THERMOZONES_NR];
}tsRtePowFactTemp;

typedef enum
{
  eExt_1 = 0,
  eExt_2,
  eExt_3,
  eExt_4,
  eExt_5,
  eExt_6,
  eExt_7,
  eExt_8,
  eExt_9,
  eExt_10,
  eExt_11,
  eExt_12,
  eExt_13,
  eExt_14,
  eLmm_1,
  eLmm_2,
  eLmm_3,
  eLmm_4,
  eLmm_5,
  eLmm_6,
  eLmm_7,
  eLmm1_Eeprom,
  eLmm2_Eeprom,
  eLmm3_Eeprom,
  eLmm4_Eeprom,
  eLmm5_Eeprom,
  eLmm6_Eeprom,
  eLmm7_Eeprom,
  eLmm8_Eeprom,
  eLmm9_Eeprom,
  eLmm10_Eeprom,
  eLmm11_Eeprom,
  eLmm12_Eeprom,
  eMaxNTCBin_Inputs
}teRteNTCBinInData;

typedef struct
{
  boolean aboNTCBinError_Stat[eMaxNTCBin_Inputs];
}tsRteNTCBinInData;


#endif /* _RTE_COMMONTYPES_H */


// EOF