/******************************************************************************/
/*!
* \file     ILCU_LevellingAdapter.h
*
* \brief    Single integration point between ILCU and the ASL chain ported
*           from DPE (ECO): AvacStat1 -> CtrlDcm -> CddDcm.
*
* \descr    The ported files include only this header for anything outside
*           the three modules. It replaces the DPE headers that do not exist
*           in ILCU (Rte.h, RteCommonTypes.h, Cfg/Cfg.h, Nvm.h, NvM_Para.h,
*           CodM*.h, UtilUtility.h, UtilMath.h, Util_Time.h, AL_Helper.h,
*           _NM_Types.h, IoHwAbUser.h, Pwm.h, SysLoad.h).
*           DPE type subsets are copied with identical names, member names
*           and enumerator values so the ported code compiles unchanged.
*           See PORT_PLAN.md / PORT_CHANGES.md in this folder.
*/
/******************************************************************************/
#ifndef ILCU_LEVELLING_ADAPTER_H
#define ILCU_LEVELLING_ADAPTER_H

#include "Std_Types.h"
#include <stdbool.h>  /* DPE NvM types and defaults use bool/true/false */

/*============================================================================*/
/* 1. ILCU-facing API                                                         */
/*============================================================================*/

/* Call once after IoHwAb_Init(). Loads the NvM RAM defaults, then runs the
 * DPE init runnables in DPE order (Rte_Cfg.c: AvacStat1, CddDcm, CtrlDcm). */
void ILCU_LevellingAdapter_Init(void);

/* Call every 5 ms (ILCU BasicTask). CddDcm runs every call (DPE 5 ms slot),
 * AvacStat1 and CtrlDcm every 4th call (DPE 20 ms slots). */
void ILCU_LevellingAdapter_MainFunction(void);

/* Pitch input for AvacStat1 (replaces DPE Pitch_Angle).
 * Unit 0.1 mrad, front side up = positive (DPE tPitch0 convention).
 * E_OK = sample usable, E_NOT_OK = no usable sample this cycle. The adapter
 * turns this into the DPE signal quality: SIG_INIT until the first usable
 * sample, SIG_INVALID only after a timeout (section 1a). A single E_NOT_OK
 * therefore no longer sends CtrlDcm to Fail.
 * Default implementation (ILCU_LevellingAdapter.c): IARA pitch from
 * Rte_Iara_TargetPitch_cdeg, usable once Rte_ImuInitResult == E_OK.
 * To supply the pitch from another module, define
 * ILCU_LVLADP_EXTERNAL_PITCH_SOURCE in the build and implement this function
 * there (1 cdeg = 1.745 x 0.1 mrad). */
Std_ReturnType ILCU_LevellingAdapter_GetPitchAngle(sint16* Pitch_0p1mrad);

/*============================================================================*/
/* 1a. Integration configuration (each value can be overridden in C_DEFINES)  */
/*============================================================================*/
/* --- Pitch conditioning, run every 20 ms before AvacStat1 ------------------*/
#ifndef ILCU_LVLADP_PITCH_SIGN
#define ILCU_LVLADP_PITCH_SIGN                (1)      /* -1 if the source reads front up as negative */
#endif
#ifndef ILCU_LVLADP_PITCH_FILTER_SHIFT
#define ILCU_LVLADP_PITCH_FILTER_SHIFT        (4u)     /* first-order low pass, 2^4 x 20 ms = 320 ms; 0 = off */
#endif
#ifndef ILCU_LVLADP_PITCH_STARTUP_TIMEOUT
#define ILCU_LVLADP_PITCH_STARTUP_TIMEOUT     (250u)   /* x 20 ms = 5 s without a first sample -> SIG_INVALID */
#endif
#ifndef ILCU_LVLADP_PITCH_INVALID_DEBOUNCE
#define ILCU_LVLADP_PITCH_INVALID_DEBOUNCE    (25u)    /* x 20 ms = 500 ms of dropout is held before SIG_INVALID */
#endif
#ifndef ILCU_LVLADP_PITCH_AUTO_ZERO
#define ILCU_LVLADP_PITCH_AUTO_ZERO           STD_ON   /* demo: the attitude at power-on is the zero reference */
#endif
#ifndef ILCU_LVLADP_PITCH_ZERO_SETTLE
#define ILCU_LVLADP_PITCH_ZERO_SETTLE         (50u)    /* x 20 ms = 1 s of usable samples before the zero is taken */
#endif

/* --- KL15 and LWR feedback -------------------------------------------------*/
/* Raw ADC counts are scaled here: the Al077a IoHwAb analog table reads KL15
 * from a result slot the ADC never writes and converts the LWR feedback for
 * the wrong divider (PORT_CHANGES.md 11). Both inputs use 82.5k/15k and the
 * 3.3 V reference (Al077HardwareSchematic.md 6). */
#ifndef ILCU_LVLADP_KL15_RAW_CHID
#define ILCU_LVLADP_KL15_RAW_CHID             IOHWAB_CHID_HSS_SENSE_1_2  /* ADC group 0 slot 0 = ADC0 ch5 (PB24) */
#endif
#ifndef ILCU_LVLADP_LWRFB_RAW_CHID
#define ILCU_LVLADP_LWRFB_RAW_CHID            IOHWAB_CHID_ADIN_3         /* ADC group 1 slot 0 = ADC1 ch0 (PA15) */
#endif
#ifndef ILCU_LVLADP_ADC_FULLSCALE_MV
#define ILCU_LVLADP_ADC_FULLSCALE_MV          (21450u) /* 3300 mV x (82.5k + 15k) / 15k */
#endif
#ifndef ILCU_LVLADP_ADC_MAX_COUNTS
#define ILCU_LVLADP_ADC_MAX_COUNTS            (4095u)  /* 12 bit, right aligned */
#endif
#ifndef ILCU_LVLADP_START_ADC_GROUPS
#define ILCU_LVLADP_START_ADC_GROUPS          STD_ON   /* IoHwAb only copies the result buffers; nothing else starts the groups */
#endif

/* --- Demo timing -----------------------------------------------------------*/
#ifndef ILCU_LVLADP_LOAD_CHANGE_INTERVAL
#define ILCU_LVLADP_LOAD_CHANGE_INTERVAL      (20)     /* x 100 ms = 2 s hold before a pitch change moves the lamp; DPE: 100 */
#endif

/* --- Debugger / bench hooks (RAM only) -------------------------------------*/
extern volatile uint8   ILCU_LvlAdp_BenchPitchEnable;    /* 1: feed ILCU_LvlAdp_BenchPitch_0p1mrad to AvacStat1, unfiltered */
extern volatile sint16  ILCU_LvlAdp_BenchPitch_0p1mrad;
extern volatile uint8   ILCU_LvlAdp_CalibRequest;        /* write 1: the current attitude becomes the zero reference */

/*============================================================================*/
/* 2. DPE build switches (were in Cfg/Cfg.h)                                  */
/*============================================================================*/
#define CFG_VARIANT_ECO
#define CFG_DEV_HOOK_EN             0u
#define CFG_EnvCond_SuppLoBmOnRq    0x0080U
#define CFG_OPT_ENVCOND             0U

/*============================================================================*/
/* 3. AL helper macros/types (AL_Helper.h, UtilUtility.h, UtilMath.h are     */
/*    absent from both snapshots; semantics derived from their usage)         */
/*============================================================================*/
#define STATIC_AL                       static
#define CONST_AL                        const
#define STATIC_UT(type, name, init)     static type name = (init)

#define UTIL_ABS(x)                     (((x) < 0) ? -(x) : (x))
#define UTIL_MIN(a, b)                  (((a) < (b)) ? (a) : (b))
#define UTIL_MAX(a, b)                  (((a) > (b)) ? (a) : (b))
#define UTIL_COUNTOF(arr)               (sizeof(arr) / sizeof((arr)[0]))

/* First-order filter storage (as in DPE Mt_Avac/Test_Stubs.h) */
typedef sint32 ORDER1_Filter;

/*============================================================================*/
/* 4. Time base (Util_Time.h absent): 1 tick = 1 us, advanced by the adapter  */
/*    MainFunction (5000 us per call)                                         */
/*============================================================================*/
typedef uint32 TIMER;
#define UTILTIME_MSEC(ms)               ((TIMER)(ms) * (TIMER)1000u)

TIMER TimerGetTick(void);
TIMER TimerGetTimeSince(TIMER Start);

/*============================================================================*/
/* 5. Network management (_NM_Types.h absent)                                 */
/*============================================================================*/
typedef uint8 NM_ModeType;
typedef uint8 NM_ErrorCodeType;
/* Adapter-defined value: DPE value unknown, only compared for equality */
#define LIMP_HOME_MODE                  ((NM_ModeType)0x02u)

NM_ErrorCodeType NM_GetMode(NM_ModeType* p_NMMode);

/*============================================================================*/
/* 6. Dem (no Dem in ILCU): values from DPE Dem.h / Dem_EventListId.h          */
/*============================================================================*/
/* Guarded: ILCU code (NvM.c, EcuM) also uses these names from an ILCU/MCAL
 * Dem header; the values only reach the debug-only Dem stub. */
#ifndef DEM_EVENT_STATUS_PASSED
#define DEM_EVENT_STATUS_PASSED         0x02u   /* DPE: DEM_EVENT_STATUS_PREPASSED */
#endif
#ifndef DEM_EVENT_STATUS_FAILED
#define DEM_EVENT_STATUS_FAILED         0x03u   /* DPE: DEM_EVENT_STATUS_PREFAILED */
#endif

#define DCMotor_SC_GND                  23u
#define DCMotor_SC_BAT                  25u
#define ZERO_LVL_PROG                   29u

/* STUB: records the last status per event, no DTC storage */
void Rte_Call_DemPrj_ReportErrorStatus(uint16 EventId, uint8 EventStatus);

/*============================================================================*/
/* 7. RTE types (subset of DPE RteCommonTypes.h)                              */
/*============================================================================*/
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
} teRte_SigQty;

typedef unsigned long tiu32Voltage_mV;

/* --- Pitch ----------------------------------------------------------------*/
typedef struct
{
  sint16        nAngle;       /* [1/10 mrad] front side up --> positive value */
  sint16        nHeightErr;   /* [1/10 mrad] headlights up --> positive value */
  teRte_SigQty  eSigQty;
} tPitch0;

typedef enum
{
  eNO_FAILURE,
  eSENSOR_FAILURE,
  eFROZEN_FAILURE,
  eSTORED_FAILURE
} teRte_HlsSensorState;

typedef struct
{
  sint16  nVehiclePitchAngle;
} tsRte_AssietteVehicule;

typedef struct
{
  tsRte_AssietteVehicule  eAssietteVehicule;
  teRte_SigQty            eSigQty;
} tsRte_SigPrep_VehiclePitchAngle;

/* --- Vehicle speed / dynamics (subset: only members read by ported code) ---*/
typedef enum
{
  eVvhIndisp_Invalid = 0U,
  eVvhIndisp_SpeedInfoAvailable = 1U,
  eVvhIndisp_SpeedInfoUnavailable = 2U
} teVvhIndisp;

typedef struct
{
  uint16  unVehicleSpeed;
} tsVitesseVehiculesRoues;

typedef struct
{
  tsVitesseVehiculesRoues  eVehicleSpeed;
  teVvhIndisp              eVehicleSpeedDispo;
  teRte_SigQty             eSigQty;
} tsRte_SysMon_VehicleSpeed;

typedef struct
{
  uint8  ucPedalAcceleration;
} tsRte_EfcmntPdleAccel;

typedef struct
{
  tsRte_EfcmntPdleAccel  ePedalAcceleration;
  teRte_SigQty           eSigQty;
} tsRte_SigPrep_DynamicSigs;

/* --- Vehicle network / configuration ---------------------------------------*/
typedef enum
{
  VESState_Stop = 0U,
  VESState_Ignition = 1U,
  VESState_Start = 2U,
  VESState_Invalid = 3U
} teRte_EtatPrincipSEV;

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
} teRte_EtatReseauElec;

typedef struct
{
  teRte_EtatPrincipSEV  eVESMainState;
  teRte_EtatReseauElec  eElectricNetworkState;
  teRte_SigQty          eSigQty;
} tsRte_SysMon_VehNetState;

typedef enum
{
  eEtatMar_Forward = 0U,
  eEtatMar_Reverse = 1U
} teRte_EtatMar;

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
} teRte_ModeConfigVehicle;

typedef struct
{
  teRte_EtatMar            eEtatMar;
  teRte_ModeConfigVehicle  eVehicleCfg;
  teRte_SigQty             eSigQty;
} tsRte_SigPrep_VehicleConfigSig;

typedef enum
{
  eMountedLeft = 0,
  eMountedRight = 1,
  eMountedUndef = 255
} teRte_MountingSide;

/* --- AvacStat1 -> CtrlDcm --------------------------------------------------*/
typedef struct
{
  sint16 Hor;      /* [0.01 deg] */
  sint16 Ver;      /* [0.01 deg] */
  uint8  Width;
} tAfsAngle;

typedef struct
{
  tAfsAngle Position[1];
  uint8     State;
} tPositionOut;

/* --- CtrlDcm <-> CddDcm / status ------------------------------------------*/
typedef struct
{
  sint16  nPosition;
  boolean boStop;
} tisDcmTarget;

typedef struct
{
  tisDcmTarget sDcmTarget;
} tsRte_CtrlDcmTarget;

typedef enum
{
  eDcmModeUnavailable,
  eDcmModeAvailable,
  eDcmModeFrozen,
  eDcmModeFactory
} teRte_eDcmMode;

typedef enum
{
  eDcmPhase_Init = 0,
  eDcmPhase_Adj = 1,
  eDcmPhase_Fail = 2
} teRte_eDcmPhase;

typedef struct
{
  teRte_eDcmMode  eASL_MODE;
  teRte_eDcmPhase eASL_PHASE;
  boolean         boLvlAdjHeadlampFault;
  boolean         boLvlAdjFunctionalFault_R;
  boolean         boLvlAdjFunctionalFault_L;
  sint16          snVehAttitudeFactory;
} tsRte_CtrlDcmStatusParams;

typedef struct
{
  boolean boElecBAT;
  boolean boElecGND;
} tsRte_DcmStatusError;

/* --- Left/right levelling signals (CAN in DPE) -----------------------------*/
typedef enum
{
  eSigneConsigneSiteD_Positive = 0U,
  eSigneConsigneSiteD_Negativ = 1U
} teRte_SigneConsigneSiteD;

typedef enum
{
  eCmdRefSiteD_NoReferencing = 0U,
  eCmdRefSiteD_Referencing = 1U
} teRte_CmdRefSiteD;

typedef struct
{
  uint16  unRCmdPosLvl;
} tsRte_ConsigneSiteD;

typedef struct
{
  teRte_SigneConsigneSiteD  eRCmdSignLvl;
  teRte_CmdRefSiteD         eRCmdRefLvl;
  tsRte_ConsigneSiteD       eRCmdPosLvl;
  teRte_SigQty              eSigQty;
} tsRte_LevellingTgtPos;

typedef enum
{
  eDiagLvl_Ok = 0U,
  eDiagLvl_Nok = 1U
} teDiagLvl;

typedef struct
{
  teDiagLvl  eLevellingAdjustFault;
} tsRte_Hs6_Diag_Drvled_L_457;

typedef struct
{
  teDiagLvl  eLevellingAdjustFaultR;
} tsRte_Hs6_Diag_Drvled_R_477;

typedef struct
{
  teDiagLvl     eLevellingAdjustFaultR;
  teRte_SigQty  eSigQty;
} tsRte_DcmDiagStatusR;

/* --- Diagnostic routine control (UDS DD06 in DPE) --------------------------*/
typedef enum
{
  eDcmMovementToTop = 0x11,
  eDcmMovementToBottom = 0x12,
  eDcmMovementToZero = 0x13,
  eDcmSequence1 = 0x14,
  eDcmSequence2 = 0x15,
  eDcmStop = 255
} teRte_DcMotorRoutineControlRequest;

typedef enum
{
  eDcmControl_Start = 0,
  eDcmControl_Stop,
  eDcmControl_Results,
  eDcmControl_Unknown
} teRte_DcMotorRoutineControl;

typedef enum
{
  eDcmBothActuators = 0,
  eDcmLeftActuator,
  eDcmRightActuator
} teRte_DcMotorRoutineControlSide;

typedef enum
{
  eDD06 = 0xDD06,
  eDcmDID_Invalid = 0xFFFF
} teRte_DcMotorRoutineControlDID;

typedef struct
{
  teRte_DcMotorRoutineControl         eDcmControl;
  teRte_DcMotorRoutineControlSide     eDcmSide;
  teRte_DcMotorRoutineControlRequest  eDcmRequest;
  boolean                             boRequestStatus;
  boolean                             boRequestAckStatus;
  teRte_DcMotorRoutineControlDID      eDcmDID;
  uint8                               ucPosRequest;
  uint8                               ucStartSequence;
} tsRte_DcMotorRoutineControl;

/* --- CddDcm blackboard / control messages. Byte-exact copies: CddDcmCtrl.c
 *     writes .Bit and reads .Val of the same union. ------------------------*/
typedef struct
{
  uint16 unState;
} tDcmStateVal;

typedef struct
{
  unsigned  IsOn : 1;
  unsigned  IsMoving : 1;
  unsigned  IsReady : 1;
  unsigned  ErrElec : 1;
  unsigned  Dummy : 4;
} tDcmStateBit;

typedef union
{
  tDcmStateVal Val;
  tDcmStateBit Bit;
} tDcmStateMsg;

typedef struct
{
  sint16 nPos;
} tDcmPosMsg;

typedef struct
{
  sint16 nPos;
  uint8  ucCtrl;
  uint8  ucDummy;
} tDcmCtrlVal;

typedef struct
{
  signed    nPos : 16;
  unsigned  Active : 1;
  unsigned  Reserved1 : 1;
  unsigned  Reserved2 : 1;
  unsigned  ErrClr : 1;
  unsigned  Reserved : 4;
  unsigned  ucDummy : 8;
} tDcmCtrlBit;

typedef union
{
  uint32        ulData;
  uint16        unData[2];
  tDcmCtrlBit   Bit;
  tDcmCtrlVal   Val;
} tDcmCtrlMsg;

/*============================================================================*/
/* 8. Coding data (subset of DPE CodM_Types.h / CodM_Para*.h)                 */
/*============================================================================*/
typedef enum
{
  eParaFct0_CodingDataInvalid = 0u,
  eParaFct0_CodingDataValid = 1u
} tParaFct0_Cmd;

/* Verbatim from DPE CodM_Para_AvacStp.h */
typedef struct
{
  uint8  ucASL_FROZEN_VEH_SPEED;
  uint8  ucASL_HIGH_FROZEN_VEH_SPEED;
  uint8  ucVEHICLE_ATTITUDE_ADJUSTEMENT_THRESHOLD_STANDSTILL;
  uint8  ucVEHICLE_ATTITUDE_ADJUSTEMENT_THRESHOLD_STANDSTILL_HS;
  uint8  ucVEHICLE_ATTITUDE_ADJUSTEMENT_THRESHOLD_MOTION;
  uint8  ucASL_MOTION_DELAY;
  uint8  ucreserviert1;
  sint8  scMin_Vehicle_Attitude;
  uint8  ucAsl_Enable;
  sint8  scMax_Vehicle_Attitude;
  sint16 snMin_ASL_Adjust_Left;
  sint16 snMax_ASL_Adjust_Left;
  uint8  ucreserviert2;
  sint8  scSafety_Position_Left;
  sint16 snMin_ASL_Adjust_Right;
  sint16 snMax_ASL_Adjust_Right;
  uint8  ucreserviert3;
  sint8  scSafety_Position_Right;
} tNvmPara_AvacStp_DCMotorData;

/* Verbatim from DPE CodM_Para_AvacStp.h */
#define NVMPARA_AVACSTP_DCMOTORDATA_INIT                    \
{                                                           \
  0u,                /* ASL_FROZEN_VEH_SPEED*/               \
  0u,                /* ASL_HIGH_FROZEN_VEH_SPEED*/          \
  0u,                /* VEHICLE_ATTITUDE_ADJUSTEMENT_THRESHOLD_STANDSTILL*/\
  0u,                /* VEHICLE_ATTITUDE_ADJUSTEMENT_THRESHOLD_STANDSTILL_HS*/\
  0u,                /* VEHICLE_ATTITUDE_ADJUSTEMENT_THRESHOLD_MOTION*/\
  0u,                /* ASL_MOTION_DELAY*/                   \
  10u,               /* CONSTANT_SPEED_INTERVAL*/            \
  -50,               /* Min_Vehicle_Attitude*/               \
  1u,                /* Dcm_Enable*/                         \
  50,                /* Max_Vehicle_Attitude*/               \
  -300,              /* Min_ASL_Adjust_Left*/                \
  0,                 /* Max_ASL_Adjust_Left*/                \
  0u,                /* reserviert2*/                        \
  -32,               /* Safety_Position_Left*/               \
  -300,              /* Min_ASL_Adjust_Right*/               \
  0,                 /* Max_ASL_Adjust_Right*/               \
  0u,                /* reserviert3*/                        \
  -32                /* Safety_Position_Right*/              \
}

/* Reduced: the DPE ECO block also holds PitchData, which belongs to Pitch */
typedef struct
{
  tNvmPara_AvacStp_DCMotorData DCMotorData;
} tNvmPara_AvacStpBlock;

#define NVMPARA_AVACSTPBLOCK_INIT  { NVMPARA_AVACSTP_DCMOTORDATA_INIT }

/* Reduced: only the datagroup read by the ported modules */
typedef struct
{
  tNvmPara_AvacStpBlock AvacStp;
} tNvmPara_CodingArea;

typedef struct
{
  tNvmPara_CodingArea* psCodingParameters_Blocks;
  tParaFct0_Cmd        eCodingState;
} tsRteCodingParameters;

/*============================================================================*/
/* 9. NvM (STUB: RAM only, no persistence; adding blocks to ILCU NvM would    */
/*    require editing existing ILCU configuration)                            */
/*============================================================================*/
typedef uint16 NvM_BlockIdType;   /* identical to ILCU NvM_Types.h */

#define NvmBlockDeltaPwmParaId      ((NvM_BlockIdType)1u)
#define NvmBlockStatAvacOp1DataId   ((NvM_BlockIdType)2u)
#define NvmBlockDcMotorDataId       ((NvM_BlockIdType)3u)

typedef enum
{
  eInput_Invalid = 0U,
  eInput_CAN = 1U,
  eInput_HLS = 2U
} teVacInput;

typedef enum
{
  eASL_Absent,
  eASL_Present
} teAslInput;

/* Reduced to the members used by the ported modules */
typedef struct
{
  uint8       ucZeroLevProg;
  sint16      snVehicleAttitude;
  teVacInput  eNVM_VAC_Input;
  teAslInput  eASL_Present;
} tisNvmDeltaPwmPara;

/* Verbatim from DPE NvM_Para.h */
typedef struct tisStatAvacPrj1Para_tag
{
  uint8  byZeroSpeed;
  uint8  byMinSpeed;
  uint8  byMaxSpeed;

  uint8  byStaticFilterCoefAtInterStop;
  uint8  byStaticFilterCoefAtZeroSpeed;
  uint8  byStaticFilterCoefAtConstSpeed;

  uint8  bySampleTimeShort;
  uint8  bySampleTimeLong;

  sint16 nTransientStatePeriod;
  sint16 nConstantSpeedInterval;

  uint8  byFilterCoefInc;
  uint8  abyFilterCoefToUnlock[5];
} tisStatAvacPrj1Para;

typedef struct tisStatAvac1Para_tag
{
  uint8  byDataHeader[2];
  uint8  byHighDynamicLimit;
  uint8  byAccFilterCoeff;
  uint8  byPowerOnMinChange;
  uint8  byDynamicMinChange;
  uint8  byInterStopMinChange;
  uint8  byStaticMinChange;
  sint16 nLoadChangeInterval;
} tisStatAvac1Para;

typedef struct tisStatAvacOp1Data_tag
{
  sint16 nHeadlightAngle;
  sint16 nSafetyAngle;
  uint16 unAdjCounter;
} tisStatAvacOp1Data;

typedef struct
{
  bool    boMotorStarted;
  bool    boMotorStopped;
  sint16  nPosition;
} tDcMotorDataStruct;

typedef struct
{
  uint8   ucHeader;
  uint8   ucMaxAdjustingTime;
  uint8   ucInvalid;
} tDcMotorCharacteristicStruct;

extern tisNvmDeltaPwmPara   NvmBlockDeltaPwmPara;
extern tisStatAvacPrj1Para  NvmBlockStatAvacPrj1Para;
extern tisStatAvac1Para     NvmBlockStatAvac1Para;
extern tisStatAvacOp1Data   NvmBlockStatAvacOp1Data;
extern tDcMotorDataStruct   NvmBlockDcMotorData;

/* Replaces NvM_WriteBlock at the ported call sites (name collides with ILCU
 * NvM). STUB: returns E_OK, nothing is written to non-volatile memory. */
Std_ReturnType ILCU_LvlAdp_NvM_WriteBlock(NvM_BlockIdType BlockId, void* NvM_SrcPtr);

/*============================================================================*/
/* 10. LWR output stage (CddDcmHal) -> ILCU IoHwAb                            */
/*============================================================================*/
/* DPE IoHwAbUser API, same names (no ILCU symbol with these names) */
void IoHwAb_User_SetDio_EN_DC(uint8 ucSignal);
void IoHwAbUser_GetAdc_VoltDC_OUT1(uint16* pio_signal);

/* Replace Pwm_* at the ported call sites (names collide with TI MCAL Pwm).
 * DutyCycle uses AUTOSAR scaling, 0x8000 = 100 %. */
void ILCU_LvlAdp_LwrPwmSetDuty(uint16 DutyCycle);
void ILCU_LvlAdp_LwrPwmStart(void);
void ILCU_LvlAdp_LwrPwmToIdle(void);

/*============================================================================*/
/* 11. DPE RTE ports used by the ported modules (implemented in the adapter)  */
/*============================================================================*/
/* AvacStat1 */
Std_ReturnType Rte_Read_CodM_Pitch_Para(tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Read_Pitch_Angle(tPitch0* ppara1);
Std_ReturnType Rte_Read_SysMon_VehicleSpeed(tsRte_SysMon_VehicleSpeed* ppara1);
Std_ReturnType Rte_Read_SigPrep_DynamicSigs(tsRte_SigPrep_DynamicSigs* ppara1);
Std_ReturnType Rte_Write_ppsAvacStat1Out_Port(const tPositionOut* ppara1);

/* CtrlDcm */
Std_ReturnType Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1);
Std_ReturnType Rte_Read_SysMon_VehNetState(tsRte_SysMon_VehNetState* ppara1);
Std_ReturnType Rte_Read_SigPrep_VehicleConfigSig(tsRte_SigPrep_VehicleConfigSig* ppara1);
Std_ReturnType Rte_Read_ppsAvacStat1Out_Port(tPositionOut* ppara1);
Std_ReturnType Rte_Read_CddDcm_ErrorStatus(tsRte_DcmStatusError* ppara1);
Std_ReturnType Rte_Read_Pitch_PlausState(teRte_HlsSensorState* ppara1);
Std_ReturnType Rte_Read_SigPrep_LevellingTgtPos(tsRte_LevellingTgtPos* ppara1);
Std_ReturnType Rte_Read_CtrlDcm_MasterCommand(tsRte_LevellingTgtPos* ppara1);
Std_ReturnType Rte_Write_CtrlDcm_MasterCommand(const tsRte_LevellingTgtPos* ppara1);
Std_ReturnType Rte_Read_DrvLedDiag(tsRte_Hs6_Diag_Drvled_L_457* ppara1);
Std_ReturnType Rte_Write_DrvLedDiag(const tsRte_Hs6_Diag_Drvled_L_457* ppara1);
Std_ReturnType Rte_Read_DrvLedDiagR(tsRte_Hs6_Diag_Drvled_R_477* ppara1);
Std_ReturnType Rte_Write_DrvLedDiagR(const tsRte_Hs6_Diag_Drvled_R_477* ppara1);
Std_ReturnType Rte_Read_SigPrep_DcmDiagStatusR(tsRte_DcmDiagStatusR* ppara1);
Std_ReturnType Rte_Write_ppCtrlDcmTarget0_DcmTargetValues(const tsRte_CtrlDcmTarget* ppara1);
Std_ReturnType Rte_Write_CtrlDcm_StatusParameters_Port(const tsRte_CtrlDcmStatusParams* ppara1);
Std_ReturnType Rte_Read_Dcm_RoutineControl(tsRte_DcMotorRoutineControl* ppara1);
Std_ReturnType Rte_Write_Dcm_RoutineControl(const tsRte_DcMotorRoutineControl* ppara1);

/* CddDcm */
Std_ReturnType Rte_Read_DcmState0_Port(tDcmStateMsg* ppara1);
Std_ReturnType Rte_Write_DcmState0_Port(const tDcmStateMsg* ppara1);
Std_ReturnType Rte_Read_DcmPos0_Port(tDcmPosMsg* ppara1);
Std_ReturnType Rte_Write_DcmPos0_Port(const tDcmPosMsg* ppara1);
Std_ReturnType Rte_Read_ppCtrlDcmTarget0_DcmTargetValues(tsRte_CtrlDcmTarget* ppara1);
Std_ReturnType Rte_Write_CddDcm_ErrorStatus(const tsRte_DcmStatusError* ppara1);
Std_ReturnType Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT(tiu32Voltage_mV* ppara1);

/*============================================================================*/
/* 12. Ported runnables (defined in the ported modules, scheduled by the      */
/*     adapter; DPE declared them in its generated RTE)                       */
/*============================================================================*/
void riAvacStat1_Init(void);
void rpAvacStat1_Cycle0(void);
void riCtrlDcm_Init(void);
void rpCtrlDcm_Cycle(void);
void riCddDcm_Init(void);
void rpCddDcm_Cycle0(void);

#endif /* ILCU_LEVELLING_ADAPTER_H */
