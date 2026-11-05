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
/// \file   Dbl_Types.h
///
/// \brief  Types for the external interface of LgtFctMgr module
///
/// \descr
///
/// \author Futo Henrietta-Helena F31185D
///         mail to <henrietta-helena.futo[at]magnetimarelli.com>
//-----------------------------------------------------------------------------
#ifndef DBL_TYPES_2021_11_02_H_
#define DBL_TYPES_2021_11_02_H_

//=============================================================================
// includes
//=============================================================================
#include <Std_Types.h>

/******************************************************************************/
/* Types                                                                      */
/******************************************************************************/
typedef struct
{
  uint8 bHighSpeed : 1;
  uint8 bSteerBack : 1;
  uint8 bStrAhead : 1;
  uint8 bReserved : 5;
}tsDriveSituation_BitType;

// AFS traffic type 
typedef enum
{
  unknown = 0,
  RightHandTraffic = 1,
  LeftHandTraffic = 2
}teTraffic;

typedef enum
{
  Dbl_eMountedLeft = 0,
  Dbl_eMountedRight = 1,
  Dbl_eMountedUndef = 255
}teDbl_MountingSide;

typedef union
{
  tsDriveSituation_BitType Bit;
  uint8 ucData;
}tuDblDriveSituation;

typedef struct
{
    sint16  nLimit[2];         // [1/10 mrad /20ms] Swivelling Limit Left 
}
tsDbl_SwiRateLimMsg;

typedef enum
{
    eINIT = 0x00,
    ePLAY = 0x01,
    ePAUSE = 0x02,
    eSTOP = 0x03,
    eRESET = 0x04
} teDBL_PrimaryCmd;

typedef enum
{
  eDbl_StateHold = 0,   // state hold from old implementation
  eDbl_StateNormal = 1,   // state normal
  eDbl_StateOff = 2,   // state off
} tDbl_SignalSrc;

typedef enum  // states for engine state-machine
{
  Dbl_eState_Init = 0,         // initial state
  Dbl_eState_Nominal = 1,      // nominal phase
  Dbl_eState_Adj = 2,          // Adjustment phase
  Dbl_eState_Fail = 3,         // Defect
  Dbl_eState_Maxsize = 5
} tDbl_StatMain;

typedef struct
{
  tDbl_StatMain      eMain;
  boolean            boEntry;
} tDbl_State;


typedef enum
{
  Dbl_eModeAssembly,
  Dbl_eModeCustomer,
}teDbl_eMainMode;

typedef enum
{
  Dbl_eSubModeUnavailable,
  Dbl_eSubModeAvailable,
  Dbl_eSubModeFrozen,
}teDbl_eSubMode;

typedef struct
{
  uint32    nSpeed;
  sint32    slCurvature;
  sint32    nCurvatureGrad;
  uint8     ucStreetClass;
  uint8     ucMotion;
} tDblcSignal;

typedef struct
{
  sint16 Hor;      // [0.1 mrad]
  uint8  Width;
} tsDbl_DblAngle;


typedef struct
{
  tsDbl_DblAngle SwivellingAngle[2];
  tDbl_StatMain     State;
} tsDbl_SwivellingOut;

typedef enum
{
  ActEntry,         ///< entry action  
  ActDo,            ///< do activity
  ActExit           ///< exit action 
}
tAction;

typedef struct
{
  uint8  biDemoMode : 1;      ///< Showroom / Demo Mode is activated, Demo Mode Activation
  uint8  FreeNotUsed1 : 1;
  uint8  FreeNotUsed2 : 1;
  uint8  FreeNotUsed3 : 1;
  uint8  FreeNotUsed4 : 1;
  uint8  FreeNotUsed5 : 1;
  uint8  FreeNotUsed6 : 1;
  uint8  FreeNotUsed7 : 1;
}tDblSmcBits;

typedef enum
{
  eLeft = 0,
  eRight = 1,
  eEnd = 2
} teDir;

typedef enum
{
  Dbl_eAUC_01 = 0, // LowBeam
  Dbl_eAUC_02 = 1, // HighBeam
  Dbl_eAUC_03 = 2  // LowBeam and HighBeam
}teDbl_DiversityParam;

// Transition function pointer
typedef boolean(*ptTransitionFctPtrDbl)(void);
typedef void(*tStateFctPtrDbl)(void);

// Transition function informations
typedef struct
{
  const tDbl_StatMain             eNewState;
  const ptTransitionFctPtrDbl ptTransitionFct;
} tTransitionDbl;
typedef struct
{
  const uint8                        ucCount;
  const tTransitionDbl *const pTransition;
  const tStateFctPtrDbl      pStateFct;
} tsDbl_StateMType;

typedef  void(*tStateFct)(tAction arg);


// Dbl command values
typedef enum
{
  eINIT_DBL = 0x00,
  ePLAY_DBL = 0x01,
  ePAUSE_DBL = 0x02,
  eSTOP_DBL = 0x03,
  eRESET_DBL = 0x04
}teDbl_Command;

typedef enum
{
  eDbl_DynBendingBeamFault_False = 0U,
  eDbl_DynBendingBeamFault_True = 1U,
  eDbl_DynBendingBeamFault_Unavailable = 2U,
  eDbl_DynBendingBeamFault_Invalid = 3U,
  eDbl_DynBendingBeamFault_SNA = 4U
}teDbl_DynBendingBeamFault;
typedef struct
{
  boolean boLossOfFrame;
  boolean boInvalidCurv;
} tsDblDTCFlag;

typedef enum
{
 eDBL_VESState_Stop = 0U, // VES main state Stop/Arret
 eDBL_VESState_Ignition = 1U, // VES main state Contact/Ignition
 eDBL_VESState_Start = 2U, // VES main state Start Engine/DEM
 eDBL_VESState_Invalid = 3U  // VES main state Invalid/Reserved
}teDbl_EtatPrincipSEV;

// -----------------------------------------------------------------------------
// Steering type
typedef enum
{
  eDBL_TypeDir_Invalid = 0U,
  eDBL_TypeDir_SteeringRight = 1U,
  eDBL_TypeDir_SteeringLeft = 2U
}teDbl_TypeDir;

// Curvature datas
typedef struct
{
  uint32 ulV_Min;
  uint32 ulV_Max;
  uint8  ucWf_Min;
  uint8  ucWf_Max;
}tsWfTable;

typedef struct
{
  sint8 scSgn;
  sint16 snAngleValue;
}tsAngleData;

typedef enum
{
  eDbl_Unavailable = 0,
  eDbl_Available = 1
}teCalculationMode;

typedef enum
{
  eDbl_Nominal = 0,
  eDbl_Invalid = 1
}teCalculationPhase;

typedef struct
{
  teCalculationMode eCalculationMode;
  teCalculationPhase eCalculationPhase;
}tsModeState;

typedef enum
{
 Dbl_SIG_VALID                 = 0u,
 Dbl_SIG_INVALID               = 1u,
 Dbl_SIG_INVALID_CRANKING      = 2u
}teDbl_SigQty;

typedef struct
{
  sint16        nSteeringWheelAngle;
  teDbl_SigQty  eSigQty; // Signal Quality
}tsDbl_SteeringWheelAngle;

typedef struct
{
  uint16  unVehicleSpeed;
}tsDblVehiculesRoues;

typedef struct
{
  tsDblVehiculesRoues      eVehicleSpeed;
  teDbl_SigQty             eSigQty; // Signal Quality
}tsDbl_VehicleSpeed;

typedef struct
{
  sint16  nYawSpeed;
}tsDbl_VitesseLacet;

typedef struct
{
  tsDbl_VitesseLacet       eYawSpeed;
  teDbl_SigQty             eSigQty; // Signal Quality
}tsDbl_YawSpeed;


typedef enum
{
  eDblTI_NOMINAL = 0U,
  eDblTI_DEGRADE = 1U,
  eDblTI_DISPO_DEM = 2U,
  eDblDEMARRAGE = 3U,
  eDblREDEMARRAGE = 4U,
  eDblTA_NOMINAL = 5U,
  eDblTA_DEGRADE = 6U,
  eDblTA_SECU = 7U,
  eDblInvalid = 15U
}teDbl_EtatReseauElec;

typedef enum
{
  DBL_VNS_SIG_SNA = 0U,
  DBL_VNS_SIG_VALID = 1U,
  DBL_VNS_SIG_INIT = 2U,
  DBL_VNS_SIG_INVALID = 3U,
  DBL_VNS_SIG_TIMEOUT = 4U,
  DBL_VNS_SIG_DEFAULT = 5U,
  DBL_VNS_SIG_E2E_CRCERR = 6U,
  DBL_VNS_SIG_E2E_ALIVEERR = 7U,
  DBL_VNS_SIG_E2E_TIMEOUT = 8U,
  DBL_VNS_SIG_UNAVAILABLE = 9U,
  DBL_VNS_SIG_DISABLED = 255U
}teDbl_VehNetStateSigQty;

typedef struct
{
  teDbl_EtatReseauElec  eElectricNetworkState;
  teDbl_VehNetStateSigQty          eSigQty; // Signal Quality
}tsDbl_VehNetState;

typedef struct
{
  uint8  ucCurvatureMode;
  uint8  ucDblEnable;
  sint32 slCurvatureRawValue;
  sint32 slCurvatureProcessedValue;
  sint32 slCurveRadiusValue;
  sint32 slCrcRadiusYaw;
  sint32 slCrcRadiusSteering;
  uint8  ucWf;
  tsModeState sCurvatureState;
}tsDbl_VehPathCurvatureData;


typedef struct
{
  uint8 ucFilterTimePrio;
  uint8 ucFilterTracking;
  uint8 ucFilterTrackingRange;
}tsDbl_FilteredCalculatedCurvatureData;

#endif // DBL_TYPES_2021_11_02_H_
