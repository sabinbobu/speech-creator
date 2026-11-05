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
/// \file   SigPrep_Types.h
///
/// \brief  Data Types Definition
///
/// \descr  Types definitions for SigPrep module is defined here
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __SYS_MON_TYPES_H__
#define __SYS_MON_TYPES_H__

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <Util_Time.h> 
#include <RteCommonTypes.h>
#include <AL_Helper.h>
#include <Cfg/Cfg.h>
#include <UtilUtility.h>
#include <Std_Types.h>
#ifndef UNIT_TEST
#include <Rte.h>
#else
#include <p_IL.h>
#include <p_IL_messages.h>
#include <p_IpduCallback.h>
#include <SigPrep_Types.h>
#endif

//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------
#define SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS    12u

#define SYSMON_LOWBEAM_OFF                        1u
#define SYSMON_LOWBEAM_ON                         2u
#define SYSMON_TURNINDICATOR_OFF                  1u
#define SYSMON_TURNINDICATOR_ON                   2u
#define SYSMON_TURNINDICATOR_INVALID              3u

#define SYSMON_SCALE_PERCENT_TO_UINT16(perValue) (uint16)(perValue)* 32768u / 100u

#define SYSMON_ZERO_VALUE                         (uint16)0u

// CRC32 Init Value (Seed)
#define SYSMON_INIT_CRC32_VAL                     (uint32)0xFFFFFFFFu
#define SYSMON_FUSA_DATA_LENGTH                   (uint32)76u

//-----------------------------------------------------------------------------
// Configuration defines
//-----------------------------------------------------------------------------
#define SYSMON_DIAG_ERR_ID_UNKNOWN                 0xFFu
#define SYSMON_DIAG_STATUS_LED_OFF                 2u      // -  eRteCddLed_Disabled = 2,         // LED off
#define SYSMON_DIAG_STATUS_ERR_OK                  4u      // -  eRteCddLed_StatusOk = 4,         // normal operation
#define SYSMON_DIAG_ERR_OPEN_LOAD                  5u      // 0  eRteCddLed_ErrOpenLoad = 5,      // open load
#define SYSMON_DIAG_ERR_SHORT_TO_GND               6u      // 1  eRteCddLed_ErrShortToGnd = 6,    // short to GND
#define SYSMON_DIAG_ERR_SHORT_TO_BAT               7u      // 2  eRteCddLed_ErrShortToUbat = 7,   // short to Ubat
#define SYSMON_DIAG_ERR_VOLTAGE_LOW                8u      // 3  eRteCddLed_ErrUnderVoltage = 8,  // voltage of LED string too low
#define SYSMON_DIAG_ERR_VOLTAGE_HIGH               9u      // 4  eRteCddLed_ErrOverVoltage = 9,   // voltage of LED string too high
#define SYSMON_DIAG_ERR_THERM_SHUT_DOWN            10u     // 5  eRteCddLed_ErrThermShutdn = 10,  // thermal shutdown
#define SYSMON_DIAG_ERR_OVER_CURRENT               11u     // 6  eRteCddLed_ErrOvercurrent = 11,  // overcurrent
#define SYSMON_DIAG_ERR_SPI                        12u     // 7  eRteCddLed_ErrSpi = 12,          // SPI error
#define SYSMON_DIAG_ERR_CRC                        13u     // 8  eRteCddLed_ErrCrc = 13,          // CRC error
#define SYSMON_DIAG_ERR_BOOST                      14u     // 9  eRteCddLed_ErrBoost = 14,       // Boost error
#define SYSMON_DIAG_MAX_CNT                        (SYSMON_DIAG_ERR_BOOST + 1U)
#define SYSMON_DIAG_MAX_STATUS_CNT                 SYSMON_DIAG_MAX_CNT
#define SYSMON_DIAG_MAX_ERR_ARRAY                  (SYSMON_DIAG_MAX_STATUS_CNT - SYSMON_DIAG_STATUS_ERR_OK)
#define SYSMON_DIAG_START_ERR_CNT                  SYSMON_DIAG_ERR_OPEN_LOAD

#define SYSMON_CFG_LED_CHANNELS_NR                   CFG_LED_CHANNELS_NR
#define SYSMON_CFG_NR_OF_LOGICAL_UNITS               CFG_LOGICAL_UNITS
#define SYSMON_CFG_MAX_BUCK_DRV                      12u //coding driver type
#define SYSMON_CFG_MAX_LMM_SW_NO                     12u //max switch number allowed
#define SYSMON_CFG_MAX_LMM_DRV                       7u  //coding LMM type

#define SYSMON_MS_CONVERTION                         1000u //[us]

//=============================================================================
// Data for Rte8 CRC failure
//=============================================================================
#define INTERNALCOM_CRC8_RTE_ERROR_MS                    320u   // 320 ms

//-----------------------------------------------------------------------------
// Handles of receive objects
//-----------------------------------------------------------------------------
#define CANRX_HS6_DAT_VSM_2AE              (uint8)0
#define CANRX_HS6_DAT_VSM_34E              (uint8)1
#define CANRX_HS6_COMMANDES_VSM_036        (uint8)2
#define CANRX_HS6_DAT_BSI_432              (uint8)3
#define CANRX_HS6_DYN_ABR_38D              (uint8)4
#define CANRX_AFS_MODE_CMD_ID              (uint8)5
#define CANRX_VES_MAIN_STATE_ID            (uint8)6
#define CANRX_ELEC_NET_STATE_ID            (uint8)7

#define CANRX_NR_FRAMES                    (uint8)5
#define CANRX_NR_EVENTS                    (uint8)8

#define SYSMON_RUNNABLE_CYCLE_TIME_MS        (uint8)10u   // SysMon Cyclic Runnable period
#define SYSMON_0x2AE_TIMEOUT              (uint16)60u/(uint16)SYSMON_RUNNABLE_CYCLE_TIME_MS
#define SYSMON_0x34E_TIMEOUT             (uint16)300u/(uint16)SYSMON_RUNNABLE_CYCLE_TIME_MS
#define SYSMON_0x36_TIMEOUT              (uint16)300u/(uint16)SYSMON_RUNNABLE_CYCLE_TIME_MS
#define SYSMON_0x432_TIMEOUT             (uint16)150u/(uint16)SYSMON_RUNNABLE_CYCLE_TIME_MS
#define SYSMON_0x38D_TIMEOUT             (uint16)120u/(uint16)SYSMON_RUNNABLE_CYCLE_TIME_MS

#define SYSMON_FS_TIMEOUT_MS              (uint16)2000u

#define SYSMON_UNKNOWN_VOLT     0U
#define SYSMON_NORMAL_VOLT      1U
#define SYSMON_LOW2_VOLT        2U
#define SYSMON_LOW1_VOLT        3U


//-----------------------------------------------------------------------------
// Handles of send objects
//-----------------------------------------------------------------------------
#define CANTX_HS6_DIAG_DRVLED_L_457        (uint8)0
#define CANTX_HS6_DIAG_DRVLED_R_477        (uint8)1

//-----------------------------------------------------------------------------
// Diagnostic TI feedback default Not Requested Time
//-----------------------------------------------------------------------------
#define SYSMON_DELAY_TI_NOT_REQUESTED      (uint16)500U

//-----------------------------------------------------------------------------
// typedef
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

// Tx Frame Side State
typedef enum
{
  eSysMonLeftTxFrame = 0,
  eSysMonRightTxFrame
}teSysMon_TxSideFrameState;

// SysMonRx Event Callback State
typedef enum
{
  eSysMonFrameInit = 0,
  eSysMonFrmTimeOut,
  eSysMonFrmEvent
}teSysMon_RxFrameState;

// Enum used for debugging coding
typedef enum
{
  FUSA_CRC32_Failed = 0U,
  FUSA_NbOfCodedFuSiChannel,
  FUSA_FuSaChannelNotPopulated,
  FUSA_FuSaChannelCurrentMax,
  FUSA_RangeCheckFailed,
  FUSA_NoError
}tSysMon_FuSaCheckEnum;

typedef struct
{
  boolean boLb_FuSa_Idx[SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS];
  boolean boTi_FuSa_Idx[SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS];
}tSysMon_FuSaChannelsStatusReaction;

typedef struct
{
  uint32 ulRxCounter;
  uint16 unTimeoutVal;
}tSysMon_RxFrameCheck;

typedef struct
{
  tSysMon_RxFrameCheck sRxCyclicCheck[CANRX_NR_FRAMES];
}tSysMon_RxCyclicCounters;

//--------------------------------------------------------------------------------------------------
/// \brief  Enum LifePhases states for Emergency Operation Mode
/// \notes
///
/// LDM.FuSa.602
/// The application shall support 4 possible states as the result of the evaluation of the received CAN message HS6_COMMANDES_VSM_036 :
/// LifePhase_SNA_State,
/// LifePhase_Normal_State,
/// LifePhase_Not_Normal_State,
/// LifePhase_Invalid_State.
///
/// LDM.FuSa.949
/// If the received CAN signal PHASE_VIE equals 0x01 (Normal Mode) for at least 300 ms,
/// then the application shall set the state LifePhase_Normal_State.
///
/// LDM.FuSa.950
/// If the received CAN signal PHASE_VIE equals one of the following values :
/// 0x00 : Standby
/// 0x02 : Switch to standby
/// 0x03 : Wake
/// 0x04 : COM_OFF for at least 300 ms,
/// then the application shall set the state LifePhase_Not_Normal_State.
///
/// LDM.FuSa.606
/// If the received CAN signal PHASE_VIE has a value different from the following values :
/// 0x00 : Standby
/// 0x01 : Normal mode
/// 0x02 : Switch to standby
/// 0x03 : Wake
/// 0x04 : COM_OFF
/// for 300 milliseconds, then the application shall set the state LifePhase_Invalid_State.
//--------------------------------------------------------------------------------------------------

typedef enum SysMon_EnumLifePhaseState //-- see CAN frame HS6_COMMANDES_VSM_036, signal PHASE_VIE
{
  SysMon_LifePhase_SNA_State        = 0U,
  SysMon_LifePhase_Normal_State     = 1U,
  SysMon_LifePhase_Not_Normal_State = 2U,
  SysMon_LifePhase_Invalid_State    = 3U
} SysMon_EnumLifePhaseState;


//--------------------------------------------------------------------------------------------------
/// \brief  Enum Speed states for Emergency Operation Mode
/// \notes
///
/// LDM.FuSa.933
/// The application shall support 4 possible states as the result of the evaluation of the received CAN message HS6_DYN_ABR_38D :
/// Speed_SNA_State,
/// Speed_0_State,
/// Speed_Drive_State,
/// Speed_Invalid_State.
/// 
/// LDM.FuSa.612
/// If
/// - the application is in state Speed_Invalid_State, and
/// - the vehicle speed calculated from the CAN signal VITESSE_VEHICULE_ROUES is less than or equal to 5 km / h, and
/// - the CAN signal VVH_INDISP is 0x1 (Speed Info Available), and
/// - the CAN message HS6_DYN_ABR_38D is received continuously within 120 milliseconds, then
/// the application shall set the state Speed_0_State.
///
/// LDM.FuSa.622
/// If
/// - the application is in state Speed_Invalid_State, and
/// - the vehicle speed calculated from the CAN signal VITESSE_VEHICULE_ROUES is greater than 5 km / h, and
/// - the vehicle speed calculated from the CAN signal VITESSE_VEHICULE_ROUES is less than or equal to 655 km / h, and
/// - the CAN signal VVH_INDISP is 0x1 (Speed Info Available), and
/// - the CAN message HS6_DYN_ABR_38D is received continuously within 120 milliseconds, then
/// the application shall set the state Speed_Drive_State.
///
/// LDM.FuSa.611
/// If the calculated CRC for the CAN message HS6_DYN_ABR_38D is not equal to the CAN signal value CHKSUM_TRME_DYN_UC_FREIN for at least 120 milliseconds,
/// then the application shall set the state Speed_Invalid_State.
///
/// LDM.FuSa.612
/// If the CAN signal CPT_PROCESS_4B_38D does not receive an expected value for at least 120 milliseconds,
/// then the application shall set the state Speed_Invalid_State.
/// Note: expected value = previous value + 1 (mod 16)
///
/// LDM.FuSa.616
/// If the CAN message HS6_DYN_ABR_38D is not received within 120 milliseconds, then the application shall set the state Speed_Invalid_State.
///
/// LDM.FuSa.618
/// If the CAN signal VVH_INDISP has one of the following values :
/// 0x0 : Invalid,
/// 0x2 : Speed Info Unavailable,
/// 0x3 : Invalid,
/// then the application shall set the state Speed_Invalid_State.
///
/// LDM.FuSa.623
/// If the vehicle speed calculated from the CAN signal VITESSE_VEHICULE_ROUES is equal to 655.35 km / h(0xFFFF) for at least 120 ms,
/// then the application shall set the state Speed_Invalid_State.
//--------------------------------------------------------------------------------------------------

typedef enum SysMon_EnumSpeedState //-- see CAN frame HS6_DYN_ABR_38D, signals VVH_INDISP, VITESSE_VEHICULE_ROUES
{
  SysMon_Speed_SNA_State      = 0U,
  SysMon_Speed_0_State        = 1U,
  SysMon_Speed_Drive_State    = 2U,
  SysMon_Speed_Invalid_State  = 3U
} SysMon_EnumSpeedState;


//--------------------------------------------------------------------------------------------------
/// \brief  Enum Low Beam states for Emergency Operation Mode
/// \notes
///
/// LDM.FuSa.931
/// The application shall support 3 possible states as the result of the evaluation of the received CAN message HS6_DAT_VSM_34E :
/// LowBeam_SNA_State,
/// LowBeam_Valid_State,
/// LowBeam_Invalid_State.
///
/// LDM.FuSa.580
/// If the CAN message HS6_DAT_VSM_34E is not received within 300 milliseconds, then the application shall set the state LowBeam_Invalid_State.///
///
/// LDM.FuSa.581
/// If the CAN message HS6_DAT_VSM_34E is received within 300 milliseconds, then the application shall set the state LowBeam_Valid_State.
//--------------------------------------------------------------------------------------------------

typedef enum SysMon_EnumLowBeamState //-- see CAN frame HS6_DAT_VSM_34E
{
  SysMon_LowBeam_SNA_State      = 0U,
  SysMon_LowBeam_Valid_State    = 1U,
  SysMon_LowBeam_Invalid_State  = 2U
} SysMon_EnumLowBeamState;


//--------------------------------------------------------------------------------------------------
/// \brief  Enum VES Main State states for Emergency Operation Mode
/// \notes
///
/// LDM.FuSa.951
/// The application shall support 3 possible states as the result of the evaluation of the received CAN message HS6_DAT_BSI_432 :
/// VESMainState_SNA_State,
/// VESMainState_Valid_State,
/// VESMainState_Invalid_State.
///
/// LDM.FuSa.804
/// If the CAN message HS6_DAT_BSI_432 is not received within 150 milliseconds, then the application shall set the state VESMainState_Invalid_State.
///
/// LDM.FuSa.805
/// If the CAN message HS6_DAT_BSI_432 is received within 150 milliseconds, then the application shall set the state VESMainState_Valid_State.
///
/// LDM.FuSa.807
/// If the received CAN signal ETAT_PRINCIP_SEV has a value different from the following values :
/// 0x0 : Stop
/// 0x1 : Contact
/// 0x2 : Start
/// for 150 milliseconds, then the application shall set the state VESMainState_Invalid_State.
//--------------------------------------------------------------------------------------------------

typedef enum SysMon_EnumVESMainState //-- see CAN frame HS6_DAT_BSI_432, signal ETAT_PRINCIP_SEV
{
  SysMon_VESMainState_SNA_State     = 0U,
  SysMon_VESMainState_Valid_State   = 1U,
  SysMon_VESMainState_Invalid_State = 2U
} SysMon_EnumVESMainState;


//--------------------------------------------------------------------------------------------------
/// \brief  Enum Turn Indicator states for Emergency Operation Mode
/// \notes
///
/// LDM.FuSa.935
/// The application shall support 3 possible states as the result of the evaluation of the received CAN message HS6_DAT_VSM_2AE :
/// TurnIndicator_SNA_State,
/// TurnIndicator_Valid_State,
/// TurnIndicator_Invalid_State.
///
/// LDM.FuSa.785
/// If the CAN message HS6_DAT_VSM_2AE is not received within 60 milliseconds, then the application shall set the state TurnIndicator_Invalid_State.
///
/// LDM.FuSa.887
/// If the CAN message HS6_DAT_VSM_2AE is received within 60 milliseconds, then the application shall set the state TurnIndicator_Valid_State.
///
/// LDM.FuSa.788
/// If the received CAN signal CTRL_TI_L_F_S respectively CTRL_TI_R_F_S has a value different from the following values :
/// 1 (TI left / right ON),
/// 2 (TI left / right OFF)
/// for 60 milliseconds, then the application shall set the state TurnIndicator_Invalid_State.
//--------------------------------------------------------------------------------------------------

typedef enum SysMon_EnumTurnIndicatorState //-- see CAN frame HS6_DAT_VSM_2AE, signals CTRL_TI_L_F_S and CTRL_TI_R_F_S
{
  SysMon_TurnIndicator_SNA_State      = 0U,
  SysMon_TurnIndicator_Valid_State    = 1U,
  SysMon_TurnIndicator_Invalid_State  = 2U
} SysMon_EnumTurnIndicatorState;


//--------------------------------------------------------------------------------------------------
// Enum used for Light Functions taken from Coding
typedef enum
{
  SysMonCheck_Data_eLFNotUsed = 0u,
  SysMonCheck_Data_eLF_LB,
  SysMonCheck_Data_eLF_LB_FuSa,
  SysMonCheck_Data_eLF_HB,
  SysMonCheck_Data_eLF_DRL_POS,
  SysMonCheck_Data_eLF_DRL_POS_SCRL,
  SysMonCheck_Data_eLF_TI,
  SysMonCheck_Data_eLF_TI_SCRL,
  SysMonCheck_Data_eLF_SM,
  SysMonCheck_Data_eLF_RGB,
  SysMonCheck_Data_eLF_FOG,
  SysMonCheck_Data_eLF_LB_BOOST,
  SysMonCheck_Data_eLF_HB_BOOST,
  SysMonCheck_Data_eLF_CL,
  SysMonCheck_Data_eLF_PXL,
  SysMonCheck_Data_eLF_MXB,
  SysMonCheck_Data_eLFNameCount
}SysMonCheck_Data_tLFName;

//--------------------------------------------------------------------------------------------------
/// \brief  Data struct to keep all data relevant for Emergency Operation Mode of Low Beam
//--------------------------------------------------------------------------------------------------

typedef struct
{
  SysMon_EnumLowBeamState     eLowBeamState;
  SysMon_EnumLifePhaseState   eLifePhaseState;
  SysMon_EnumSpeedState       eSpeedState;
  uint8                       ucLastLowBeamValidRequest;  //ON or OFF

  //-- conditions checks results -----
  //-- LowBeam
  boolean boDoNotActivateLowBeam;     //-- TRUE when LowBeam shall not be activated
  boolean boDoNotDeactivateLowBeam;   //-- TRUE when LowBeam shall not be de-activated
  boolean boDoActivateLowBeam;        //-- TRUE when LowBeam shall be activated
  boolean boDoDeactivateLowBeam;      //-- TRUE when LowBeam shall be de-activated

  boolean boDiagLowBeam;              //-- TRUE when LowBeam has a fault
} tSysMonLbEmergencyOperationData;


//-- Emergency Operation analysis function of states
typedef void(*SYSMON_FUNC_PTR_EMERENCY_OPERATION_LOWBEAM_CASE)(tSysMonLbEmergencyOperationData* const pEOdata);
struct SysMon_ASIL_sEmergencyOperationLowBeamFctArg {
  SYSMON_FUNC_PTR_EMERENCY_OPERATION_LOWBEAM_CASE func;
  tSysMonLbEmergencyOperationData* const arg;
};


//--------------------------------------------------------------------------------------------------
/// \brief  Data struct to keep all data relevant for Emergency Operation Mode of Turn Indicator
//--------------------------------------------------------------------------------------------------

typedef struct
{
  SysMon_EnumTurnIndicatorState  eTurnIndicatorState;
  SysMon_EnumLifePhaseState      eLifePhaseState;
  SysMon_EnumVESMainState        eVESMainState;
  uint8                          ucLastTurnIndicatorValidRequest;  //ON or OFF

  //-----------------------------------------------------------------------------
  //-- conditions checks results -----
  //-- TurnIndicator
  boolean boDoNotDeactivateTurnIndicator;   //-- TRUE when TurnIndicator shall not be de-activated
  boolean boDoDeactivateTurnIndicator;      //-- TRUE when TurnIndicator shall be de-activated
  boolean boDiagTurnIndicator;              //-- TRUE when TurnIndicator has a fault

} tSysMonTiEmergencyOperationData;


//-----------------------------------------------------------------------------
//-- Emergency Operation analysis function of states
typedef void(*SYSMON_FUNC_PTR_EMERENCY_OPERATION_TURNINDICATOR_CASE)(tSysMonTiEmergencyOperationData* const pEOdata);
struct SysMon_ASIL_sEmergencyOperationTurnIndicatorFctArg {
  SYSMON_FUNC_PTR_EMERENCY_OPERATION_TURNINDICATOR_CASE func;
  tSysMonTiEmergencyOperationData* const arg;
};

//-----------------------------------------------------------------------------
// SysMonCheck_Data FuSa coding parameters structure
typedef struct tSysMonCheck_Data_FuSaParam
{
  uint8                            aucFUSA_DRVxx_NAMES_ASIL[SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS];              // Name of light function mapped on LED channel
  uint8                            aucFUSA_DRVxx_LED_UNDER_VOLTAGE_ASIL[SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS];  // Error limit: lower limit for "line voltage
  uint8                            aucFUSA_DRVxx_LED_OVER_VOLTAGE_ASIL[SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS];   // Error limit: upper limit for "line voltage
  uint8                            aucFUSA_DRVxx_MIN_PWM_ASIL[SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS];            // Minimum Pwm
  uint16                           aunFUSA_DRVxx_MIN_CURRENT_ASIL[SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS];        // Minimum Current
  uint8                            ucFUSA_LB_FS_BEHAVIOUR_ASIL;                                                  // Low Beam Fail Safe Behaviour Value
  uint8                            ucFUSA_TI_FS_BEHAVIOUR_ASIL;                                                  // Turn Indicator Fail Safe Behaviour Value
}tSysMonCheck_Data_FuSaParam;

//-----------------------------------------------------------------------------
// Copy of EFT Data
typedef struct tsSysMonCheck_Data_EftData
{
  uint8    aucAssignedOutput[SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS];
  uint16   aunImax[SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS];
  boolean  boEftDataValid;
}tsSysMonCheck_Data_EftData;

//-----------------------------------------------------------------------------
// SysMon Rx frame handle data struct
typedef struct
{
  boolean           boMsgUpdated;
  boolean           boMsgTimedOut;
  void(*CONST_AL pfFrmCallback)(teSysMon_RxFrameState eSysMonRxState);
}tsSysMon_RxFrameInfoConst;

//-----------------------------------------------------------------------------
// SysMon Tx frame handle data struct
typedef struct
{
  CONST_AL teSysMon_TxSideFrameState  eFrameSide;
  boolean                             boMsgConfirmed;
  CONST_AL uint32                     ulTimeOut;
  TIMER                               ulTimer;
  void(*CONST_AL pfCycleCb)  (void);
  void(*CONST_AL pfNotAckCb) (void);
}tsSysMon_TxFrameInfoConst;

//-----------------------------------------------------------------------------
// SysMon Signal Quality and Value of Low Beam
typedef struct
{
  uint8         ucLowBeamValue;
  teRte_SigQty  eLowBeamSigQty;
}tsSysMonRx_LowBeamSignal;

//-----------------------------------------------------------------------------
// SysMon Signal Quality and Value of Phase Vie (Life Phases)
typedef struct
{
  teRte_PhaseVie  eLifePhaseValue;
  teRte_SigQty    eLifePhaseSigQty;
}tsSysMonRx_LifePhaseSignal;

//-----------------------------------------------------------------------------
// SysMon Signal Quality and Speed Value of Vehicle Speed
typedef struct
{
  uint16        unSpeedValue;
  teRte_SigQty  eSpeedSigQty;
}teSysMonRx_SpeedSignal;

//-----------------------------------------------------------------------------
// SysMon Signal Quality and Value of Turn Indicator
typedef struct
{
  uint8         ucTurnIndicatorValue;
  teRte_SigQty  eTurnIndicatorSigQty;
}tsSysMonRx_TurnIndicatorSignal;


// Structure used to compute the value and state of LowBeam
typedef struct
{
  uint8                   ucValue;
  SysMon_EnumLowBeamState eLowBeamState;
} tSysMonRx_Signal_Low_Beam;


// Structure used to compute the value and state of Turn Indicator
typedef struct
{
  uint8                         ucValue;
  SysMon_EnumTurnIndicatorState eTurnIndicatorState;
} tSysMonRx_Signal_Turn_Indicator;


// Structure used to compute the state of Phase Vie
typedef struct
{
  SysMon_EnumLifePhaseState eLbLifePhaseState;
  SysMon_EnumLifePhaseState eTiLifePhaseState;
} tSysMonRx_Signal_Life_Phase;


// Structure used to compute the state of VES Main State
typedef struct
{
  SysMon_EnumVESMainState eVESMainState;
} tSysMonRx_Signal_VES_Main_State;


// Structure used to compute the state of Speed
typedef struct
{
  SysMon_EnumSpeedState eSpeedState;
} tSysMonRx_Signal_Speed;

// Structure used to handle Low Beam
typedef struct
{
  boolean TurnAll_LB_FuSa_OFF;
  uint8   ucLowBeamCmd;
  TIMER   startDelayTimerMonitor_MS;
  boolean bostartDelayTimerMonitor_MS;
}tsSysMonCheck_FUSA_LB_ASIL;

// Structure used to handle Turn Indicator
typedef struct
{
  uint8   ucTurnIndicatorCmd;
  TIMER   startDelayTimerMonitor_MS;
  boolean bostartDelayTimerMonitor_MS;
}tsSysMonCheck_FUSA_TI_ASIL;

// Structure used to handle Turn Indicator
typedef struct
{
  boolean TurnAll_TI_FuSa_OFF;
  boolean boTurnIndicatorCmd;
}tsSysMonCheck_FUSA_TI_ASIL_TURN_OFF;

// Diag Mux Signal State
typedef struct
{
  boolean boDiagMuxValue;
  boolean boDiagMuxSigStatus;
}tsSysMon_DiagMuxState;

typedef struct
{
  uint8   ucChannelStatus;
  boolean boVinOk;
}tsSysMon_ChannelState;

// Structure for Channel Error State
typedef struct
{
  tsSysMon_ChannelState asChannelState[12];
}tsSysMon_aChannelState;


typedef struct
{
  uint8   ucLedState;
  boolean boVinBoostOk;
}tsSysMon_ErrorHandler;


typedef struct
{
  TIMER   ErrorDebounce;
  boolean boErrorWriteStatus;
}tsSysMon_Diag_ErrStatus;


typedef struct
{
  tsSysMon_Diag_ErrStatus asErrorState[SYSMON_DIAG_MAX_ERR_ARRAY];
}tsSysMon_Diag_ErrHandler;

typedef enum
{
  eCheckError,
  eDoDebounce,
  eResetError,
  eWriteError
}teSysMon_DebounceState;

typedef struct
{
  uint8 ucLed_Debounce[SYSMON_CFG_LED_MAX_NO_OF_LED_CHANNELS];
}tsSysMon_Error;

// Engine state
typedef enum
{
  eEngineRunning = 0u,
  eSTT_Phase = 1u,
  eInvalid_State = 2u
}teSysMon_EngineState;

// Vehicle electric system main state enum
typedef enum
{
  eSysMon_VESState_Stop = 0U, // VES main state Stop/Arret
  eSysMon_VESState_Ignition = 1U, // VES main state Contact/Ignition
  eSysMon_VESState_Start = 2U, // VES main state Start Engine/DEM
  eSysMon_VESState_Invalid = 3U  // VES main state Invalid/Reserved
}teSysMon_EtatPrincipSEV;

// -----------------------------------------------------------------------------
// Warning Mode enum
typedef enum
{
  eSysMon_PilotedMode = 0U,
  eSysMon_AutonomMode = 1U
}teSysMon_WarningMode;


#endif // __SYS_MON_TYPES_H__



// EOF
