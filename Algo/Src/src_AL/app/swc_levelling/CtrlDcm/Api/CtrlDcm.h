//*****************************************************************************
// (C) Marelli Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Marelli Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Marelli Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  CtrlDcm.h
///
/// \brief
///
/// \author Pop Sandor (F92597C)
///         mailTo:sandor.pop[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CTRL_DCM_2022_06_23_H
#define CTRL_DCM_2022_06_23_H

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <Std_Types.h>
#include "ILCU_LevellingAdapter.h" /* ILCU_PORT: replaces DPE-only <AL_Helper.h>, <Cfg/Cfg.h> */

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

// states for DC motor state-machine
typedef enum
{
  CtrlDcm_ePhase_Init = 0,     // Initialization phase
  CtrlDcm_ePhase_Adj  = 1,     // Adjustment phase
  CtrlDcm_ePhase_Fail = 2      // Failure phase
} teCtrlDcm_eASLPhase;

// main state struct
typedef struct
{
  teCtrlDcm_eASLPhase ePhase;
  boolean             boEntry;
} tsCtrlDcm_State;


typedef enum
{
  CtrlDcm_eModeAssembly,
  CtrlDcm_eModeCustomer
} teCtrlDcm_eMainMode;

typedef enum
{
  CtrlDcm_eModeUnavailable,
  CtrlDcm_eModeAvailable,
  CtrlDcm_eModeFrozen,
  CtrlDcm_eModeFactory
} teCtrlDcm_eASLMode;

// target source selection
typedef enum
{
  eDcmSrc_SleepPos  = 0,   // sleep position (no movement)
  eDcmSrc_NormalPos = 1,   // positioning according to vehicle attitude
  eDcmSrc_DiagPos   = 2,   // positioning according to diagnostic services
  eDcmSrc_SafetyPos = 3    // safety position
} teCtrlDcm_SignalSrc;

typedef enum
{
  CtrlDcm_eMountedLeft  = 0,
  CtrlDcm_eMountedRight = 1,
  CtrlDcm_eMountedUndef = 255
} teCtrlDcm_MountingSide;


// Sign of automatic static levelling order for Right LDM
typedef enum
{
  CtrlDcm_eSigneConsigneSiteD_Positive = 0U,
  CtrlDcm_eSigneConsigneSiteD_Negativ = 1U
} teCtrlDcm_SigneConsigneSiteD;

// -----------------------------------------------------------------------------
// Status of automatic levelling
typedef enum
{
  CtrlDcm_eLvlStatus_InDefect = 0U,
  CtrlDcm_eLvlStatus_Inhibited = 1U,
  CtrlDcm_eLvlStatus_NotImplemented = 2U,
  CtrlDcm_eLvlStatus_Active = 3U
} teCtrlDcm_LvlStatus;

// -----------------------------------------------------------------------------
// Sensor error status
typedef enum
{
  CtrlDcm_eHLS_NO_FAILURE,
  CtrlDcm_eHLS_SENSOR_FAILURE,
  CtrlDcm_eHLS_FROZEN_FAILURE,
  CtrlDcm_eHLS_STORED_FAILURE
} teCtrlDcm_SensorState;

// -----------------------------------------------------------------------------
// Fail state handling
typedef enum
{
  CtrlDcm_eFreeze,
  CtrlDcm_eFreeze_IgnitionNeeded,
  CtrlDcm_eSafety,
  CtrlDcm_eSafety_IgnitionNeeded,
  CtrlDcm_eContinue
} teCtrlDcm_FailStateHandling;

// -----------------------------------------------------------------------------
// Absolute value of automatic static levelling order for Right LDM
typedef struct
{
  uint16  unRCmdPosLvl;
} tsCtrlDcm_ConsigneSiteD;

// -----------------------------------------------------------------------------
// Signal quality
typedef enum
{
  CtrlDcm_SIG_SNA          = 0U,
  CtrlDcm_SIG_VALID        = 1U,
  CtrlDcm_SIG_INIT         = 2U,
  CtrlDcm_SIG_INVALID      = 3U,
  CtrlDcm_SIG_TIMEOUT      = 4U,
  CtrlDcm_SIG_DEFAULT      = 5U,
  CtrlDcm_SIG_E2E_CRCERR   = 6U,
  CtrlDcm_SIG_E2E_ALIVEERR = 7U,
  CtrlDcm_SIG_E2E_TIMEOUT  = 8U,
  CtrlDcm_SIG_UNAVAILABLE  = 9U,
  CtrlDcm_SIG_DISABLED     = 255U
} teCtrlDcm_SigQty;

// -----------------------------------------------------------------------------
// Driver error status
typedef struct
{
  boolean boElecBAT;
  boolean boElecGND;
} tsCtrlDcm_ErrorStatus;

typedef struct
{
  boolean             boDiagLvlR;
  teCtrlDcm_SigQty    eSigQty;
} tsCtrlDcm_LevellingDiagStatus;

typedef struct
{
  boolean boLvl_Elec_Defect;
  boolean boLvl_Temp_Defect;
  boolean boLvl_Moving;
  sint16  snLvl_Degree_Ctrl;
  sint16  snLvl_Pos_Feedback;
} tsCtrlDcm_LevellingValidationFrames;

typedef struct
{
  sint16         nStatDcmPosVer;                                   //Actual Position of DC motor
  sint8          cStatDcmPosDegree;                                //Actual Position of DC motor(degree) with 0.01 resolution.
  teCtrlDcm_LvlStatus                 eStatDcmLevelStatus;         //Status of automatic levelling
  boolean                             boDcmFaultStatus;            //DC Motor Fault Status
  boolean                             boDcmIsMoving;               // TRUE if DC Motor is moving
  boolean                             boDcmCommDef;                // Communication Defect
  boolean                             boDcmPosDef;                 // Position Defect
  tsCtrlDcm_LevellingValidationFrames sValidationFrames;           // Validation Frames for Levelling
} tsCtrlDcm_DiagStatus;

typedef struct
{
  teCtrlDcm_SigneConsigneSiteD    eRCmdSignLvl;
  tsCtrlDcm_ConsigneSiteD         eRCmdPosLvl;
  teCtrlDcm_SigQty                eSigQty;
} tsCtrlDcm_LevellingTgtPos;

typedef struct
{
  teCtrlDcm_eASLMode  eASL_MODE;
  teCtrlDcm_eASLPhase eASL_PHASE;
  boolean             boLvlAdjHeadlampFault;
  boolean             boLvlAdjFunctionalFault_R;
  boolean             boLvlAdjFunctionalFault_L;
} tsCtrlDcm_DcmStatusParameters;

typedef struct
{
  sint16  nPosition;
  boolean boStop;
}tsCtrlCdm_DcmTarget;

typedef struct
{

  tsCtrlCdm_DcmTarget sDcmTarget;

}tsCtrlDcm_TargetValues;


typedef enum
{
  CtrlDcm_eMovementToTop = 0x11,
  CtrlDcm_eMovementToBottom = 0x12,
  CtrlDcm_eMovementToZero = 0x13,
  CtrlDcm_eSequence1 = 0x14,
  CtrlDcm_eSequence2 = 0x15,
  CtrlDcm_eStop = 255
} teCtrlDcm_DcMotorRoutineControlRequest;

typedef enum
{
  CtrlDcm_eDcmControl_Start = 0,
  CtrlDcm_eDcmControl_Stop,
  CtrlDcm_eDcmControl_Results,
  CtrlDcm_eDcmControl_Unknown
} teCtrlDcm_DcMotorRoutineControl;

typedef enum
{
  CtrlDcm_eBothActuators = 0,
  CtrlDcm_eLeftActuator,
  CtrlDcm_eRightActuator
} teCtrlDcm_DcMotorRoutineControlSide;

typedef enum
{
  CtrlDcm_eDD06    = 0xDD06,
  CtrlDcm_eInvalid = 0xFFFF
} teCtrlDcm_DcMotorRoutineControlDID;

typedef struct
{
  teCtrlDcm_DcMotorRoutineControl eDcmControl;
  teCtrlDcm_DcMotorRoutineControlSide eDcmSide;
  teCtrlDcm_DcMotorRoutineControlRequest eDcmRequest;
  boolean boRequestStatus;
  boolean boRequestAckStatus;
  teCtrlDcm_DcMotorRoutineControlDID eDcmDID;
  uint8 ucPosRequest;
  uint8 ucStartSequence;
} tsCtrlDcm_DcMotorRoutineControl;

//-----------------------------------------------------------------------------
// prototypes
//-----------------------------------------------------------------------------
void CtrlDcm_Init(void);
void CtrlDcm_Master_Cycle20ms(void);
void CtrlDcm_Slave_Cycle20ms(void);

#endif // CTRL_DCM_2022_06_23_H

// EOF