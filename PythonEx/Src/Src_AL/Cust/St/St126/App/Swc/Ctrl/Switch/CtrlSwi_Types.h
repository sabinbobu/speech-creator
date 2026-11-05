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
/// \file  CtrlSwi_Types.h
///
/// \brief  software component module CtrlSwi
//
/// \descr
///
/// \author Zhao, Kai ALDE-RT (zhk2rt)
///         mailTo:kai.zhao[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __CTRL_HSS_TYPES_H__
#define __CTRL_HSS_TYPES_H__ // PRQA S 0602 // It is checked if the identifier is not is use already by the line above. Every header shall have an identifier.

//=============================================================================
//  preprocessor definitions
//=============================================================================

//=============================================================================
//  includes
//=============================================================================
#include <Std_Types.h>
#include <RteCommonTypes.h>
#include <CtrlSwi_Cfg.h>

//=============================================================================
//  definitions
//=============================================================================
#define FAN1                                   0u


#if defined (SAMPLE_FULL) || defined(UNIT_TEST)
#define FAN2                                   1u
#define RGB_SM                                 2u
#else
#define RGB_SM                                 1u
#endif
//=============================================================================
//  types
//=============================================================================
typedef enum teCtrlSwiMode
{
  eDiagCtrl_CtrlSwi_Disabled = 0,        // diagnose control is disabled: normal operation (outputs controlled by AppM)
  eDiagCtrl_CtrlSwi_Enabled              // diagnose control is enabled:  diagnose mode (outputs controlled by DiagM)
}teCtrlSwiMode;

typedef struct
{
  teCtrlSwiMode   teMode[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];             // Control mode: diagnose control / AppM Control
  uint8           ucHssOutput[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];        // Control output in case diagnose control
}tisDiagControl_CtrlSwi;

typedef struct
{
  boolean boEftCrcStatus;                                                              // Status of Eft-data
  boolean boCodingStatus;                                                              // Status of Coding-data
  boolean boHWVar;                                                                     // 0: High-Variant, 1: Low-Variant
  uint8   ucHssGNDErrCnt;                                                              // 0: No GND-error on Hss-outputs 1: GND-error is active on one of the Hss-outputs  2:  GND-error is active on two of the Hss-outputs 3: GND-error is active on three of the Hss-outputs
  uint8   ucHssOLErrCnt;                                                               // 0: No OL-error on Hss-outputs 1: OL-error is active on one of the Hss-outputs  2:  OL-error is active on two of the Hss-outputs 3: OL-error is active on three of the Hss-outputs
  boolean aboHssAvailable[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];                     // availablity of Hss-outputs
  uint8   aucHssAssignment[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];                    // store the HssAssignment from EFT data
  boolean aboHssTargetState[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];                   // state of target value
  boolean aboPreTargestState[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];                  // state of pre target value
  boolean aboHssActualState[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];                   // actual state
  boolean aboHssPreviousState[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];                 // previous state
  boolean aboHssStateChangedDiagDisabled[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];      // diagnose is disabled for 1s/500ms after the output is switched from ON to OFF/OFF to ON
  boolean aboHssSwitchOnDelay[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];                 // delay in case of switching from off to on
  uint32  aulHssStatisticOnTime[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];               // store the Switch On Time for the statistic
  boolean aboHssNewRequest[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];                    // if there is a new request (OFF--> ON) on the HSS-channel
  boolean aboHssShort2GNDDetected[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];             // if the short to GND is detected
  boolean aboRetryTarget[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];                      // Retry target in case of Short to GND
  boolean aboErrOffPermanent[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];                  // Permanent Off State in case of Short to GND
  uint8   aucRetryCounter[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];                     // Retry Counter in case of Short to GND
  uint16  aunRetryTimer[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];                       // Retry Timer in case of Short to GND  5s = 500x10ms
  boolean aboRetryAllowed[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];                     // Retry Allowed State in case of Short to GND
  boolean aboRetryStarted[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];                     // Retry Stategy Started State in case of Short to GND
} tisCtrlSwiState;

typedef struct
{
  uint8          ucErrShortToGnd[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];  // error state of short to GND
  uint8          ucErrShortToVbat[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS]; // error state of short to Vbat
  uint8          ucErrOpenLoad[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];    // error state of openload
  uint8          ucCntShortToGnd[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];  // error counter of short to GND
  uint8          ucCntShortToVbat[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS]; // error counter of short to Vbat
  uint8          ucCntOpenLoad[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];    // error counter of openload
} tisCtrlSwiErrState;

typedef struct
{
  boolean boSwitchOn[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];              // State of SwitchOn,     0: HSS-output cannot be switched from off to on. 1: HSS-output can be switched from off to on.
  boolean boRemainOn[CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS];              // State of RemainOn,     0: HSS-output is to be switched off. 1: HSS-output can be remained on.
  boolean boDiagEnabled;                                                   // State of DiagEnabled,  0: Diagnose is disabled. 1: Diangose is enabled.
}tisCtrlSwiVoltState;

typedef struct
{
  boolean boShort2GndFlag ;        // Sh2Gnd   Err Flag
  boolean boOpenLoadFlag  ;        // OpenLoad Err Flag
  boolean boShort2VbatFlag;        // Sh2Vbat  Err Flag
}tisCtrlSwiErrorFlags;

// Error States for the Fans
typedef enum teCtrlSwiErr_State
{
  eERR_SNA = 0u,  // SNA
  eERR_YES = 1u,  // Error active
  eERR_NO = 2u    // No error
}teCtrlSwiErr_State;

typedef enum
{
  eSwitchOnRetryOFF = 0,
  eSwitchOffRetryOff,
  eSwitchOnRetryON_FanONPhase,
  eSwitchOnRetryON_FanOFFPhase,
  eSwitchOnRetryON_FanPermanentOFF
}teSwitchOnRetryStrategyStates;

//=============================================================================
//  global variable
//=============================================================================

//=============================================================================
//  inline functions
//=============================================================================

//=============================================================================
//Intern prototypes
//=============================================================================

#endif // __CTRL_HSS_TYPES_H__
// EOF
