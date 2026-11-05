#ifndef __FCTRTYPES_H__
#define __FCTRTYPES_H__

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
/// \file  FctR_Types.h
///
/// \brief  Define (internal) types for FctR
///
/// \descr  
///
/// \author Ralf Sondershaus  (sor2rt)
///         mailTo:ralf.sondershaus@al-lighting.com       
//-----------------------------------------------------------------------------

#include "FctR_Cfg.h"
#include <Std_Types.h>
#include <AL_Helper.h>
#include <CodM.h>


// A logical lamp index, e.g. LL1='0' ... FCTR_CFG_LOGLMP_MAX='13' = currently '14' LED-Channels
typedef uint8 tAppLogLamp;
// A light function index
typedef uint8 tAppLightFunction;

typedef uint16  tLogLmpStg;

// A unique index for each light function
//
// THE ORDER OF THE ENTRIES HERE MUST BE THE SAME AS IN THE LMM!
// (see NvM_Para_lmmInit.h)
// AND IN THE BITFIELD tTgtLgtFctBits BELOW!
typedef enum
{
  LB_TownLight             = 0,
  LB_Pedestrian            = 1,
  LB_CountryLight          = 2, // ECO - basic light distribution for low beam
  LB_MotorwayLight         = 3,
  LB_Boost                 = 4,
  LB_AdverseWeather_RHD    = 5,
  LB_FoggyWeather_RHD      = 6,
  LB_AdverseWeather_LHD    = 7,
  LB_FoggyWeather_LHD      = 8,


  HB_HighBeam              = 13, // ECO
  HB_Boost                 = 14,
  //HB_Adjustement_Mode      = 16,
  HB_AimingMode            = 15,

  DRL_DaytimeRunningLight  = 22, // ECO
  POS_PositionLight        = 23, // ECO
  PKL_ParkingLight         = 24, // ECO - POS light only on one side (left or right)
  SBL_StaticBendingLight   = 25,
  CL_CorneringLight        = 26,
  FL_FogLight              = 27,
  SM_SideMarker            = 28, // ECO

  TI_TurnIndicator         = 29, // ECO - Only turn indicator request
  TI_POS_TurnIndicatorPos  = 30, // ECO - Turn indicator and position light request
  TI_Scrolling             = 31, //     - Scrolling turn indicator request 
  //TI_Scrolling_POS         = 31, //     - Scrolling turn indicator and position l

  LF_INIT                  = 255 // Initial state
}teFctR_LightFunctions;

// Bit field for Light Functions (32 bit).
// The bit order must match the order of light functions in teFctR_LightFunctions enum.
typedef struct
{
  uint32 biLB_TownLight             : 1;      //  0
  uint32 biLB_Pedestrian            : 1;      //  1
  uint32 biLB_CountryLight          : 1;      //  2
  uint32 biLB_MotorwayLight         : 1;      //  3
  uint32 biLB_Boost                 : 1;      //  4
  uint32 biLB_AdverseWeather_RHD    : 1;      //  5
  uint32 biFoggyWeather_RHD         : 1;      //  6
  uint32 biLB_AdverseWeather_LHD    : 1;      //  7
  uint32 biFoggyWeather_LHD         : 1;      //  8

  uint32 biLB_Reserved              : 4;
                                                  
  uint32 biHB_HighBeam              : 1;      //  13   //if illuminant 14 has a problem => do not report (clear this bit)
  uint32 biHB_Boost                 : 1;      //  14   //if illuminant 14 has a problem => do not report (clear this bit)
  uint32 biHB_Adjustement_Mode      : 1;      // 15  //if illuminant 14 has a problem => do not report (clear this bit)
  uint32 biHB_AimingMode            : 1;      // 16        //if illuminant 14 has a problem => do not report (clear this bit)
  uint32 biHB_FlashToPass           : 1;      // 17    //if illuminant 14 has a problem => do not report (clear this bit)

  uint32 biHB_Reserved2             : 4;      

  uint32 biDRL_DaytimeRunningLight  : 1;      // 22
  uint32 biPOS_PositionLight        : 1;      // 23
  uint32 biPKL_ParkingLight         : 1;      // 24
  uint32 biSBL_StaticBendingLight   : 1;      // 25
  uint32 biCL_CorneringLight        : 1;      // 26
  uint32 biFL_FogLight              : 1;      // 27
  uint32 biSM_SideMarker            : 1;      // 28

  uint32 biTI_TurnIndicator         : 1;      // 29 - Only turn indicator request
  uint32 biTI_TiCmdPos              : 1;      // 30 - when TI Comand (levier)
  uint32 biTI_TiReqPos              : 1;      // 31 - when TI is Blinking
}tsFctR_TgtLgtFctBits;

// Requests for light functions (not safety relevant like daytime running light) computed from input signals (e.g. CAN).
typedef union
{
  uint32               ulRaw;  // Raw data access
  tsFctR_TgtLgtFctBits Bits;   // Bit wise access
}tuFctR_LgtFct;

// Requests for light functions B together with additional state information for certain light functions B
typedef struct
{
  tuFctR_LgtFct Req;           // Requests
}tsFctR_TgtLgtReq;

#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
typedef struct
{
  uint8 ucCurrentState;
  uint8 ucTargetState;
  uint8 ucDimOut;
}tsFctR_ClSblDimState;
#endif
// A unique index for each logical lamp
typedef enum
{
  LL1  =  0,                  // Logical Lamp  1
  LL2  =  1,                  // Logical Lamp  2
  LL3  =  2,                  // Logical Lamp  3
  LL4  =  3,                  // Logical Lamp  4
  LL5  =  4,                  // Logical Lamp  5
  LL6  =  5,                  // Logical Lamp  6
  LL7  =  6,                  // Logical Lamp  7
  LL8  =  7,                  // Logical Lamp  8
  LL9  =  8,                  // Logical Lamp  9
  LL10 =  9,                  // Logical Lamp 10
  LL11 = 10,                  // Logical Lamp 11
  LL12 = 11,                  // Logical Lamp 12
  LL13 = 12,                  // Logical Lamp 13
  LL14 = 13,                  // Logical Lamp 14
  LL15 = 14,                  // Logical Lamp 15
  LL16 = 15,                  // Logical Lamp 16
  LLMax = FCTR_CFG_LOGLMP_MAX // Number of logical lamps
}teFctR_LogLmps;

// A bit for each logical lamp
typedef struct
{
  uint16 Ll1      : 1;        // Logical Lamp  1
  uint16 Ll2      : 1;        // Logical Lamp  2
  uint16 Ll3      : 1;        // Logical Lamp  3
  uint16 Ll4      : 1;        // Logical Lamp  4
  uint16 Ll5      : 1;        // Logical Lamp  5
  uint16 Ll6      : 1;        // Logical Lamp  6
  uint16 Ll7      : 1;        // Logical Lamp  7
  uint16 Ll8      : 1;        // Logical Lamp  8
  uint16 Ll9      : 1;        // Logical Lamp  9
  uint16 Ll10     : 1;        // Logical Lamp 10
  uint16 Ll11     : 1;        // Logical Lamp 11
  uint16 Ll12     : 1;        // Logical Lamp 12
  uint16 Ll13     : 1;        // Logical Lamp 13
  uint16 Ll14     : 1;        // Logical Lamp 14
  uint16 Ll15     : 1;        // Logical Lamp 15
  uint16 Ll16     : 1;        // Logical Lamp 16
}tsFctR_LogLmpBits;

// A bit for each Logical Lamp
typedef union
{
  tsFctR_LogLmpBits Bits;   // Bit wise access
  uint16            Raw;    // Raw data access (either 8 bit or 16 bit depending on FCTR_CFG_LOGLMP_MAX)
}tuFctR_LogLmp;

// Parking light request
typedef enum
{
  Pkl_Deactivated,
  Pkl_Left,
  Pkl_Right
}teFctR_PklReq;

// Internal enum for signal quality
typedef enum
{
  eSig_Invalid = 0u,
  eSig_Valid   = 1u
}teFctR_SigQty;

// Standard light functions requests
typedef struct
{
  boolean       boDrl_Req;
  boolean       boHbFlash_Req;
  boolean       boHb_Req;
  boolean       boLb_Req;
  boolean       boPos_Req;
  boolean       boSideM_Req;
#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
  boolean       boTiDiag_Req;//only for diag mode
  boolean       boFog_Req;
  boolean       boClDiag_Req;//only for diag mode
  boolean       boSblDiag_Req;//only for diag mode
#endif
  teFctR_PklReq ePkl_Req;
  teFctR_SigQty eSigQuality;
}tsFctR_StdLgtFctsReq;

// Afs Mode
typedef enum
{
  Afs_Off,
  Afs_Country,
  Afs_Motorway,
  Afs_Town,
  Afs_BadWeather_Lhd,
  Afs_BadWeather_Rhd,
  Afs_Foggy_Lhd,
  Afs_Foggy_Rhd,
  Afs_Invalid = 255
}teFctR_AfsMode;

// Glare Free HighBeam command
typedef enum
{
  GfHb_Off,
  Curtain_Activation,
  GfHb_On,
  Curtain_Deactivation
}teFctR_GfHbCmd;

// Afs signals
typedef struct
{
  teFctR_AfsMode eAfsMode;
  teFctR_GfHbCmd eGfHbCmd;
  boolean        boLbBoost_Allowed;
  boolean        boPedestrian_Allowed;
  boolean        boAimingMode_Activation;
}tsFctR_AfsSignals;

// Turn Indicator status
typedef enum
{
  Ti_Inactive,
  Ti_ActiveRight,
  Ti_ActiveLeft,
  Ti_ActiveBoth
}teFctR_TiStatus;

// Warning mode for Ti
typedef enum
{
  WarningMode_Piloted,
  WarningMode_Autonom,
}teFctr_TiWarningMode;

// Turn Indicator requests
typedef struct
{
  boolean              boTi_Req;
#if(FCTR_CFG_FULL_VARIANT_SUPPORTED != 0u)
  boolean              boTiScrolling_Req;
#endif
  teFctR_TiStatus      eTiStatus;
  teFctr_TiWarningMode eTiWarnMode;
}tsFctR_TiReq;

// Output structure of FctR module
typedef struct
{
  uint16 unIntensity;
  uint16 unIntensitySpeedInv;
}tsFctR_TgtLmpVal0;

// Ecu mounting side
typedef enum
{
  eEcu_Left  = 0,
  eEcu_Right = 1,
  eEcu_Undef = 255
}teFctR_EcuSide;

// Ecu operating mode
typedef enum
{
  eEcu_NormalMode = 0,
  eEcu_OffMode    = 1
}teFctR_EcuOperationgMode;

// Dbl command values
typedef enum
{
  INIT_DBL  = 0x00,
  PLAY_DBL  = 0x01,
  PAUSE_DBL = 0x02,
  STOP_DBL  = 0x03,
  RESET_DBL = 0x04
}teFctR_DblCommand;

// Illuminant error state
typedef struct
{
  uint16  unIlluminantErrState;
  boolean boIlluminantStatus; //On/Off
  uint8   ucIlluminantName; //illuminant name
  boolean boIlFailureStatus;
}tsFctR_IlluminantStates;

// Structure for light functions state to be sent on Rte
// 0 = OK, 1 = NOK
typedef struct
{
  uint8 bLb_Diag : 1u;
  uint8 bSbl_Diag : 1u;
  uint8 bTi_Diag : 1u;
  uint8 bHb_Diag : 1u;
  uint8 bGfHb_Diag : 1u;
  uint8 bDrl_Diag : 1u;
  uint8 bPos_Diag : 1u;
  uint8 bReserve : 1u;
}tsFctR_LgtFctState;

typedef struct
{
  boolean boLb_Status;
  boolean boSbl_Status;
  boolean boTiBlink_Status;
  boolean boTi_Status;
  boolean boHb_Status;
  boolean boGfHb_Status;
  boolean boDrl_Status;
  boolean boPos_Status;
  boolean boSM_Status;
  boolean boFog_Status;
}tsFctR_LightStatus;

typedef struct
{
  boolean boLb_State;
  boolean boSbl_State;
  boolean boTi_State;
  boolean boHb_State;
  boolean boGfHb_State;
  boolean boDrl_State;
  boolean boPos_State;
}tsFctR_LightFailureStatus;

// Vehicle main state
typedef enum
{
  eState_Stop       = 0U, // VES main state Stop/Arret
  eState_Contact    = 1U, // VES main state Contact/Ignition
  eState_Start      = 2U, // VES main state Start Engine/DEM
  eState_InvalidSEV = 3U  // VES main state Invalid/Reserved
}teFctR_EtatPrincipSEV;

typedef enum
{
  eState_TI_NOMINAL   = 0U,
  eState_TI_DEGRADE   = 1U,
  eState_TI_DISPO_DEM = 2U,
  eState_DEMARRAGE    = 3U,
  eState_REDEMARRAGE  = 4U,
  eState_TA_NOMINAL   = 5U,
  eState_TA_DEGRADE   = 6U,
  eState_TA_SECU      = 7U,
  eState_InvalidElec  = 15U
}teFctR_EtatReseauElec;

typedef struct
{
  teFctR_EtatPrincipSEV eFctR_EtatPrincipSEV;
  teFctR_EtatReseauElec eFctR_EtatReseauElec;
  //requirements are missing for qty
}tsFctR_VehState;

typedef enum
{
  eFctR_ModeConfigVehicle_Montage     = 0U,
  eFctR_ModeConfigVehicle_Usine       = 1U,
  eFctR_ModeConfigVehicle_Controle    = 2U,
  eFctR_ModeConfigVehicle_Stockage    = 3U,
  eFctR_ModeConfigVehicle_Client      = 4U,
  eFctR_ModeConfigVehicle_Showroom    = 5U,
  eFctR_ModeConfigVehicle_AfterMarket = 6U,
  eFctR_ModeConfigVehicle_Invalid     = 7U,
  eFctR_ModeConfigVehicle_Invalid2    = 15U
}teFctR_ModeConfigVehicle;

// Engine state
typedef enum
{
  eEngineRunning = 0u,
  eSTT_Phase     = 1u,
  eInvalid_State = 2u
}teFctR_EngineState;

// Temporary struct for LUT
typedef struct
{
  uint8  ucIntensity;
  uint8  ucPriority;
  uint8  ucRampType;
  uint16 unTon;
  uint16 unToff;
  uint8  ucFailureBit;
  uint8  ucActiveBit;
}tsFctR_ChLutType;

// A LMM cell consists of total 4 bytes
//typedef struct
//{
//  uint8 ucPower;           // PWM [%]
//  uint8 ucTimeOn;          // Time for activation   [100 ms]
//  uint8 ucTimeOff;         // Time for deactivation [100 ms]
//  uint8 biPriority    : 4; // Priority (0 is highest)
//  uint8 biRampType    : 2; // Ramp Type
//  uint8 biErrorImpact : 1; // 1 = switch off light function in case of a malfunction of the logical lamp
//  uint8 biActive      : 1; // 1 = Activate logical lamp only if it is activated already by another light function
//}
//tsFctR_Lmm_LutCell;

// The init state consists of a single row
typedef struct
{
  tNvmPara_Lmm_LutCell sLmmCell[FCTR_CFG_LOGLMP_MAX];
}tsFctR_LmmInitBlock;


typedef enum
{
 eAimingOff,
 eBlinkOn,
 eBlinkOff,
 eAimOn
}FctR_eAimingType;

///// The Look-Up-Table.
///// Total number of bytes: CFG_LF_LUT_Size x NVM_PARA_LMM_LUT_ENTRY_SIZE.
//typedef struct
//{
//  tsFctR_Lmm_LutCell cell[FCTR_CFG_LF_LUT_SIZE]; ///< The cells (40 x 4 bytes = 160 bytes)
//}
//tsFctR_NvmPara_Lmm_Lut;
//
//// ----------------------------------------------------------------------------
///// The X block contains additional information for a LMM (like Look-Up-Tables).
///// Total size: 182 Bytes
//// ----------------------------------------------------------------------------
//typedef struct
//{
//  tsFctR_NvmPara_Lmm_Lut Lut;                 ///< 40 x 4 Byte = 160 bytes
//  sint8                  LwrOffset_A[14];     ///< 14 bytes
//  sint8                  LwrOffset_B[14];     ///< 14 bytes
//  uint8                  LwrSpd[2];           ///<  2 bytes
//  uint8                  Di[4];               ///<  4 bytes
//  uint8                  TransitionTimes[32]; ///< 32 bytes
//  uint8                  WL[24];              ///< 24 bytes
//  uint8                  Reserviert[16];      ///< 16 bytes
//}                                             ///< -----------
//tsFctR_NvmPara_LmmXBlock;                     ///< 266 bytes
//
///// A LMM cell consists of an index into a Look-Up-Table
//typedef struct
//{
//  uint8 ucIdx;    ///< Index into Look-Up-Table [0 ... CFG_LF_LUT_Size-1]
//}
//tsFctR_NvmPara_Lmm_LmmCell;
//
///// A single row consists of CFG_LM_Cnt Cells.
///// Total size: CFG_LM_Cnt bytes
//typedef struct
//{
//  tsFctR_NvmPara_Lmm_LmmCell cell[FCTR_CFG_LOGLMP_MAX];    ///< An index for each Logical Lamp
//}
//tsFctR_NvmPara_Lmm_Row;
//
//// ----------------------------------------------------------------------------
///// Rows 0 ... CFG_LF_Cnt-1
///// Size 384 byte
//// ----------------------------------------------------------------------------
//typedef struct
//{
//  tsFctR_NvmPara_Lmm_Row  row[FCTR_CFG_LGTFCT_MAX]; // 32 x 12 bytes = 384 bytes
//}
//tsFctR_NvmPara_LmmABlock;

///** @brief complete structure of CodM RAM Mirror */
//typedef  struct
//{
//  /** @name Parameters stored in ROM */
//  /*@{*/
//  uint8                     Sys[38];              /**< defined in CodM_Para_System.h             */
//  uint8                     Lwr[100];             /**< defined in CodM_Para_Lwr.h                */
//  uint8                     AfsMaster[148];       /**< defined in CodM_Para_AfsMaster.h          */
//  tsFctR_NvmPara_LmmABlock  LmmA;                 /**< defined in CodM_Para_Lmm.h                */
//  tsFctR_NvmPara_LmmABlock  LmmA_B;               /**< defined in CodM_Para_Lmm.h                */
//  tsFctR_NvmPara_LmmXBlock  LmmX;                 /**< defined in CodM_Para_Lmm.h                */
//  uint8                     Led1[248];            /**< defined in CodM_Para_Led.h                */
//  uint8                     Led2[268];            /**< defined in CodM_Para_Led.h                */
//  uint8                     Thermo1[294];         /**< defined in CodM_Para_Thermo.h             */
//  uint8                     Fan1[102];            /**< defined in CodM_Para_Thermo.h             */
//  uint8                     Adb;                  /**< defined in CodM_Para_Adb.h                */
//  uint8                     Dbl;                  /**< defined in CodM_Para_AfsDbl.h             */
//  /*@}*/
//  /** @name Parameters stored in NVM */
//  /*@{*/
//  uint8                     LedBinning;           /**> defined in DiagIfc.h                      */
//  uint8                     SensOffset;           /**> defined in DiagIfc.h                      */
//  uint8                     CarConfigNvM;         /**> defined in CodM_Para_System.h             */
//  uint8                     Header;
//  uint8                     aucVariantName[8];
//  uint8                     aucSwVersion[4];
//  uint8                     BeamStatus;           /**< defined in SigPrepTxCallbacks.h   */
//  uint8                     AfsVddHldFilterCur3;  /**< defined in CodM_Para_VddHld.h     */
//  uint8                     AFSVddHld2;           /**< defined in CodM_Para_VddHld.h     */
//  /*@}*/
//
//}tsFctR_NvmPara_CodingArea;

///// A bit for each input signal of Light Functions (e.g. via LIN)
//typedef struct
//{
//  uint8 DrlPos : 1;    ///< DRL and POS use same LIN request
//  uint8 Sm : 1;    ///< Side Marker
//  uint8 Reserved : (8 - 2);    ///< For future use
//}tsFctR_LgtFctBits;
//
///// A bit for each input signal of Light Functions
//typedef union
//{
//  tsFctR_LgtFctBits Bits;   ///< Bit wise access
//  uint8             ucRaw;  ///< Raw data access
//}tFctRLgtFctB;
//
///// A bit for each input signal of Environment
//typedef struct
//{
//  uint8 VehSpd : 1;        ///< Vehicle Speed
//  uint8 reserved : (8 - 1);    // reserved Bits
//} tFctREnvBits;
//
///// A bit for each input signal of Environmental states
//typedef union
//{
//  tFctREnvBits Bits;   ///< Bit wise access
//  uint8        ucRaw;  ///< Raw data access
//} tFctREnv;
//
///// A bit for each input signal
//typedef struct
//{
//  tFctRLgtFctB   LgtFctB;           ///< Light Functions B
//  tuFctR_LogLmp  LogLmp;            ///< Logical Lamps Errors (from LedState via ActLmp ports, see also #LEDSTATE_ERR_MASK)
//  tuFctR_LogLmp  LogLmpDebounce;    ///< Debouncing of logical lamp states running [0=running, 1=not running]
//  tuFctR_LogLmp  LogLmpNewDetCycle; ///< A new error detection cycle has been started (e.g. after Clear DTC or system startup).
//                                    ///< 1=Logical lamp has been requested (at least once) since restart of a validation cycle
//                                    ///< 0=Logical lamp has not been requested (at least once) since restart of a validation cycle.
//                                    ///< Initial value: 0.
//  tFctREnv     Env;                 ///< Environment
//} tFctRStateBits;

#endif // __FCTRTYPES_H__
