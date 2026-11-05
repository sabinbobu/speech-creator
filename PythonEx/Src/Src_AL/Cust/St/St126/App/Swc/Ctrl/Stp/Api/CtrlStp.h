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
/// \file  CtrlStp.h
///
/// \brief  The software component CtrlStp can be initialized from the RTE.
///         All monitor counters, values and timers will be initialized during initialization.
///         The RTE call CtrlStp cyclicaly. In each cycle call CtrlStp performs tbd for each stepper
///
//-----------------------------------------------------------------------------
#ifndef CTRLSTP_2020_07_10_H_
#define CTRLSTP_2020_07_10_H_


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <Std_Types.h>
#include <AL_Helper.h>
#include <Cfg/Cfg.h>

//#include <Rte_ctaaCtrlStp.h> // .\FLM3\Asr6\Src\Src_ThirdParty\Src_FLM3\Src_KPIT-FLM3\ApplicationStack\AppMode\Configuration\Generated_Files\2_Rte\inc\Rte_ctaaCtrlStp.h


//-----------------------------------------------------------------------------
// defines
//-----------------------------------------------------------------------------

// signal status generic
#define CTRLSTP_SignalSna  0xFDu  // signal temporarily not available
#define CTRLSTP_SignalErr  0xFEu  // signal not available due to error
#define CTRLSTP_SignalDis  0xFFu  // signal not available because component is disabled

#define CTRLSTP_SignalSpeedMax   250u  // range for speed in status signal

#define CTRLSTP_SignalAngleMax   120   // range for angle in status signal
#define CTRLSTP_SignalAngleMin (-120)

//-----------------------------------------------------------------------------
// types
//-----------------------------------------------------------------------------



// states for engine state-machine
typedef enum
{
  CtrlStp_eState_Init = 0,     // initial state
  CtrlStp_eState_Ref = 1,      // reference run active
  CtrlStp_eState_Adj = 2,      // Adjustment phase
  CtrlStp_eState_Fail = 3,     // stepper defect
  CtrlStp_eState_STT = 4,      // Cranking phase
  CtrlStp_eState_Maxsize = 5
} teCtrlStp_StatMain;

// main state struct
typedef struct
{
  teCtrlStp_StatMain  eMain;
  boolean            boEntry;
} tsCtrlStp_State;


typedef enum
{
  CtrlStp_eModeAssembly,
  CtrlStp_eModeCustomer,
}teCtrlStp_eMainMode;

typedef enum
{
  CtrlStp_eSubModeUnavailable,
  CtrlStp_eSubModeAvailable,
  CtrlStp_eSubModeAftersale,
  CtrlStp_eSubModeFrozen,
  CtrlStp_eSubModeFactory

}teCtrlStp_eSubMode;


// spinning status
typedef enum
{
  eStpSpnStatus_NoSupport   =  0,
  eStpSpnStatus_Init        =  1,  // reference run
  eStpSpnStatus_Norm        =  2,  // normal mode
  eStpSpnStatus_NoInit      =  5,  // not referenced
  eStpSpnStatus_Sna         = 13,  // signal temporarily not available
  eStpSpnStatus_Err         = 14,  // signal not available due to error
  eStpSpnStatus_Dis         = 15   // signal not available because component is disabled
} tCtrlStp_SpnStatus;


// target source selection
typedef enum
{
  eStpSrc_SleepPos          = 0,   // sleep position (LWR_AP)
  eStpSrc_InscenPos         = 1,   // positionning by inscenation
  eStpSrc_NormalPos         = 2,   // positionning by LA Master
  eStpSrc_DiagPos           = 3,   // positionning by diagnostic
  eStpSrc_SafetyPos         = 4,   // safety position (LWR_SP)
  eStpSrc_ContinPos         = 5,    // continous movement
  eStpSrc_ZeroPos           = 6    // zero electrical position
} teCtrlStp_SignalSrc;

typedef enum
{
  CtrlStp_eMountedLeft = 0,
  CtrlStp_eMountedRight = 1,
  CtrlStp_eMountedUndef = 255
}teCtrlStp_MountingSide;

// Status of the 12V electrical energy supply in by engine
typedef enum
{
  CtrlStp_eEtatFee_1_1 = 0U,
  CtrlStp_eEtatFee_1_2 = 1U,
  CtrlStp_eEtatFee_1_3c = 2U,
  CtrlStp_eEtatFee_1_3r = 3U,
  CtrlStp_eEtatFee_2_1 = 4U,
  CtrlStp_eEtatFee_3c_1 = 5U,
  CtrlStp_eEtatFee_3r_1 = 6U,
  CtrlStp_eEtatFee_4_1 = 7U,
  CtrlStp_eEtatFee_5_5 = 8U,
  CtrlStp_eEtatFee_1_3vr = 9U,
  CtrlStp_eEtatFee_3vr_1 = 10U,
  CtrlStp_eEtatFee_Invalid = 11U
}teCtrlStp_EtatFee;

// Electric status of levelling stepper of Right LDM
typedef enum
{
  CtrlStp_eLvlElecR_NoDefect = 0U,
  CtrlStp_eLvlElecR_OpenCircuit = 1U,
  CtrlStp_eLvlElecR_ShortCircuit = 2U,
  CtrlStp_eLvlElecR_Reserved = 3U
}teCtrlStp_LvlElecR;

// -----------------------------------------------------------------------------
// Temperature status of levelling stepper of Right LDM
typedef enum
{
  CtrlStp_eLvlTemperatureR_NoWarning = 0U,
  CtrlStp_eLvlTemperatureR_ColdTemperature = 1U,
  CtrlStp_eLvlTemperatureR_HighTemperatureWarning = 2U,
  CtrlStp_eLvlTemperatureR_HighTemperatureShutdown = 3U
}teCtrlStp_LvlTemperatureR;

// -----------------------------------------------------------------------------
// Step loss status of levelling stepper of Right LDM
typedef enum
{
  CtrlStp_eLvlSteplossR_NoSteploss = 0U,
  CtrlStp_eLvlSteplossR_SteplossRisk = 1U
}teCtrlStp_LvlSteplossR;

// -----------------------------------------------------------------------------
// Referencing status of levelling stepper of Right LDM
typedef enum
{
  CtrlStp_eLvlRefStateR_WaitingForNewRefCmd = 0U,
  CtrlStp_eLvlRefStateR_RefInProgress = 1U,
  CtrlStp_eLvlRefStateR_SuccessfullyFinished = 2U,
  CtrlStp_eLvlRefStateR_Invalid = 3U
}teCtrlStp_LvlRefStateR;

// -----------------------------------------------------------------------------
// Voltage status of Right levelling stepper.
typedef enum
{
  CtrlStp_eLvlVoltR_NominalVoltage = 0U,
  CtrlStp_eLvlVoltR_UnderVoltage = 1U,
  CtrlStp_eLvlVoltR_NotUsed = 2U,
  CtrlStp_eLvlVoltR_OverVoltage = 3U
}teCtrlStp_LvlVoltR;

// Sign of lighting level right enum
typedef enum
{
  CtrlStp_eSIGNPOSLVLR_Positiv = 0U,
  CtrlStp_eSIGNPOSLVLR_Negative = 1U
}teCtrlStp_SignPosLvlR;

// -----------------------------------------------------------------------------
// Current level lighting position right
typedef struct
{
  uint16  unRPosLvl;
}tsCtrlStp_PositionSiteD;

// -----------------------------------------------------------------------------
// TODO VS: To be define
typedef enum
{
  CtrlStp_eDynbendingBeamFaultR_False = 0U,
  CtrlStp_eDynbendingBeamFaultR_True = 1U,
  CtrlStp_eDynbendingBeamFaultR_Unavailable = 2U,
  CtrlStp_eDynbendingBeamFaultR_Invalid = 3U
}teCtrlStp_DynBendingBeamFaultR;

// Sign of automatic dynamic levelling order for Right LDM
typedef enum
{
  CtrlStp_eSigneConsigneSiteD_Positive = 0U,
  CtrlStp_eSigneConsigneSiteD_Negativ = 1U
}teCtrlStp_SigneConsigneSiteD;

// -----------------------------------------------------------------------------
// Referencing control of automatic levelling of Right LDM
typedef enum
{
  CtrlStp_eCmdRefSiteD_NoReferencing = 0U,
  CtrlStp_eCmdRefSiteD_Referencing = 1U
}teCtrlStp_CmdRefSiteD;

// -----------------------------------------------------------------------------
// Status of automatic levelling 
typedef enum
{
  CtrlStp_eLvlStatus_InDefect = 0U,
  CtrlStp_eLvlStatus_Inhibited = 1U,
  CtrlStp_eLvlStatus_NotImplemented = 2U,
  CtrlStp_eLvlStatus_Active = 3U
}teCtrlStp_LvlStatus;

// -----------------------------------------------------------------------------
// Headlamp fault status
typedef enum
{
  CtrlStp_eNo_Failure = 0U,
  CtrlStp_eFrozen_Failure = 1U,
  CtrlStp_eTransition_Failure = 2U
}teCtrlStp_HeadlampFaultStatus;

// -----------------------------------------------------------------------------
// Sensor error status
typedef enum
{
  CtrlStp_eHLS_NO_FAILURE,
  CtrlStp_eHLS_SENSOR_FAILURE,
  CtrlStp_eHLS_FROZEN_FAILURE,
  CtrlStp_eHLS_STORED_FAILURE
}teCtrlStp_SensorState;

// -----------------------------------------------------------------------------
// Fail state handling
typedef enum
{
  CtrlStp_eFreeze,
  CtrlStp_eFreeze_IgnitionNeeded,
  CtrlStp_eSafety,
  CtrlStp_eSafety_IgnitionNeeded,
  CtrlStp_eContinue
}teCtrlStp_FailStateHandling;

// -----------------------------------------------------------------------------
// Absolute value of automatic dynamic levelling order for Right LDM
typedef struct
{
  uint16  unRCmdPosLvl;
}tsCtrlStp_ConsigneSiteD;

#if defined (CFG_VARIANT_FULL) || (UNIT_TEST) // Applicable only for FULL version
// -----------------------------------------------------------------------------
// Diagnosis flux of Digital LB swivelling function to deactivate right LDM
typedef enum
{
  eCtrlStpDynBendingBeamFaultL_False = 0U,
  eCtrlStpDynBendingBeamFaultL_True = 1U,
  eCtrlStpDynBendingBeamFaultL_Unavailable = 2U,
  eCtrlStpDynBendingBeamFaultL_Invalid = 3U
}teCtrlStp_DynBendingBeamFaultL;
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)

// -----------------------------------------------------------------------------
// Signal quality
typedef enum
{
  CtrlStp_SIG_SNA = 0U,
  CtrlStp_SIG_VALID = 1U,
  CtrlStp_SIG_INIT = 2U,
  CtrlStp_SIG_INVALID = 3U,
  CtrlStp_SIG_TIMEOUT = 4U,
  CtrlStp_SIG_DEFAULT = 5U,
  CtrlStp_SIG_E2E_CRCERR = 6U,
  CtrlStp_SIG_E2E_ALIVEERR = 7U,
  CtrlStp_SIG_E2E_TIMEOUT = 8U,
  CtrlStp_SIG_UNAVAILABLE = 9U,
  CtrlStp_SIG_DISABLED = 255U
}teCtrlStp_SigQty;

typedef struct {
  teCtrlStp_LvlElecR              eLvlElecR;
  teCtrlStp_LvlTemperatureR       eLvlTemperatureR;
  teCtrlStp_LvlSteplossR          eLvlSteplossR;
  teCtrlStp_LvlRefStateR          eLvlRefStateR;
  teCtrlStp_LvlVoltR              eLvlVoltR;
  teCtrlStp_SigQty                eSigQty;
}tsCtrlStp_LevellingDiagStatus;

typedef struct {
  boolean boLvl_Elec_Defect;
  boolean boLvl_Temp_Defect;
  boolean boLvl_StepLoss;
  boolean boLvl_Moving;
  sint16  snLvl_Degree_Ctrl;
  sint16  snLvl_Pos_Feedback;
}tsCtrlStp_LevellingValidationFrames;

typedef struct
{
  sint16         nStatStpPosVer;                                   //Actual Position of Vertical Stepper;(0-1000): 0,01*raw-5;0x3FF = "(invalid)"
  sint8          cStatStpPosDegree;                                //Actual Position of Vertical Stepper(degree) with 0.01 resolution.
  teCtrlStp_LvlRefStateR              eStatStpModeVer;             //Actual Operating Mode of Vertical Stepper; teRte_StatStpMode
  teCtrlStp_LvlSteplossR              eStatStpStepLoss;            //Safety StepLoss information
  teCtrlStp_LvlTemperatureR           eStatStpThermalState;        //Thermal State of Vertical Stepper; teRte_StatStpTw
  teCtrlStp_LvlElecR                  eStatStpElectricDefect;      //Electrical Defect state;
  teCtrlStp_LvlVoltR                  eStatStpVoltageState;        //Voltage State of Vertical Stepper;
  teCtrlStp_LvlStatus                 eStatStpLevelStatus;         //Status of automatic levelling
  boolean                             boStpFaultStatus;            //Stepper Fault Status
  boolean                             boStpIsMoving;               // TRUE if Stepper is moving
  boolean                             boStpCommDef;                // Communication Defect
  boolean                             boStpPosDef;                 // Position Defect
  tsCtrlStp_LevellingValidationFrames sValidationFrames;           // Validation Frames for Levelling
} tsCtrlStp_DiagStatus;

typedef struct {
  teCtrlStp_SignPosLvlR           eRPosSignLvl;
  tsCtrlStp_PositionSiteD         ePositionSiteD;
  teCtrlStp_DynBendingBeamFaultR  eDynBendingBeamFaultR;
  teCtrlStp_SigQty                eSigQty;
}tsCtrlStp_LevellingFeedback;

typedef struct {
  teCtrlStp_SigneConsigneSiteD    eRCmdSignLvl;
  teCtrlStp_CmdRefSiteD           eRCmdRefLvl;
  tsCtrlStp_ConsigneSiteD         eRCmdPosLvl;
#if defined (CFG_VARIANT_FULL) || (UNIT_TEST) // Applicable only for FULL version
  teCtrlStp_DynBendingBeamFaultL  eDynBendingBeamFaultR;
#endif // (CFG_VARIANT_FULL) || (UNIT_TEST)
  teCtrlStp_SigQty                eSigQty;
}tsCtrlStp_LevellingTgtPos;

typedef struct {
  teCtrlStp_eSubMode eADL_MODE;
  teCtrlStp_StatMain eADL_PHASE;
  teCtrlStp_HeadlampFaultStatus eLvlAdjHeadlampFault_R;
  teCtrlStp_HeadlampFaultStatus eLvlAdjHeadlampFault_L;
  boolean boLvlAdjFunctionalFault_R;
  boolean boLvlAdjFunctionalFault_L;
}tsCtrlStp_ValidationParameters;


typedef enum
{
  CtrlStp_eMovementToTop = 0x11,
  CtrlStp_eMovementToBottom = 0x12,
  CtrlStp_eMovementToZero = 0x13,
  CtrlStp_eSequence1 = 0x14,
  CtrlStp_eSequence2 = 0x15,
  CtrlStp_eStop = 255
}teCtrlStp_StepperRoutineControlRequest;

typedef enum
{
  CtrlStp_eStpControl_Start = 0,
  CtrlStp_eStpControl_Stop,
  CtrlStp_eStpControl_Results,
  CtrlStp_eStpControl_Unknown
}teCtrlStp_StepperRoutineControl;

typedef enum
{
  CtrlStp_eBothActuators = 0,
  CtrlStp_eLeftActuator,
  CtrlStp_eRightActuator
}teCtrlStp_StepperRoutineControlSide;

typedef enum
{
  CtrlStp_eDD05 = 0xDD05,
  CtrlStp_eDF10 = 0xDF10,
  CtrlStp_eDF11 = 0xDF11,
  CtrlStp_eDF12 = 0xDF12,
  CtrlStp_eDF13 = 0xDF13,
  CtrlStp_eInvalid = 0xFFFF
}teCtrlStp_StepperRoutineControlDID;

typedef struct
{
  teCtrlStp_StepperRoutineControl eStpControl;
  teCtrlStp_StepperRoutineControlSide eStpSide;
  teCtrlStp_StepperRoutineControlRequest eStpRequest;
  boolean boRequestStatus;
  boolean boRequestAckStatus;
  teCtrlStp_StepperRoutineControlDID eStpDID;
  sint16 snPosRequest;
  uint8 ucStartSequence;
}tsCtrlStp_StepperRoutineControl;

//-----------------------------------------------------------------------------
// prototypes
//-----------------------------------------------------------------------------
void riCtrlStpInit(void);
void rpCtrlStp_Cycle(void);
teCtrlStp_StatMain CtrlStp_GetStateValue(void);

#endif // CTRLSTP_2020_07_10_H_

// EOF
