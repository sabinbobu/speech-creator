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
/// \file   CddSwi_Types.h
///
/// \brief  Types for CddSwi
///
/// \author Adrian Horlescu (F31197D)
///         mailTo:adrian-marian.horlescu[at]marelli.com
//-----------------------------------------------------------------------------

#ifndef CDD_SWI_TYPES_2021_03_08_H_
#define CDD_SWI_TYPES_2021_03_08_H_

//=============================================================================
// Includes
//=============================================================================

#include <Std_Types.h>
#include <RteCommonTypes.h>

//=============================================================================
//  definitions
//=============================================================================

#define CDD_SWI_FAN_ON                                                 0x8000u
#define CDD_SWI_FAN_OFF                                                     0u

//=============================================================================
//  types
//============================================================================+
// This enum represent all the errors that can be detected by HSS. TBD
typedef enum
{
  CddSwi_eErrorType_None = 0,
  CddSwi_eOpenLoad,
  CddSwi_eShort2Gnd,
  CddSwi_eShort2VBAT,
  CddSwi_MaxErrorTypes
} teCddSwi_ErrorTypes;

//This enum represents the available switching states of the Hss output.
typedef enum
{
  CddSwi_eSwitchState_Off = 0,
  CddSwi_eSwitchState_On,
} eCddSwi_State;

// This type is used to control all of the switching aspects and handling for the CddSwi (Double output Hss driver)
typedef struct
{
  // index of the device which is connected to the Hss output and which is controlled by it
  uint8 ucIndex;
  //// TBD -
  teCddSwi_ErrorTypes              ucErrorStates;
  // flag to indicate whether the device controlled in purposefully connected or disconnected from the Hss output
  boolean boDeviceIsUsed;
  // 'real' (internal) state of HSS
  eCddSwi_State  ucActual_State;
  // (external) 'requested' state of HSS
  eCddSwi_State  ucRequested_State; // the requested state of the Hss output for this particular channel index/device: on or off
  // voltage of HSS-Sense - represents somehow the current (only HSS-1 & -2, NOT used for HSS-3=Ani-DI)
  uint16                      unVoltageSense;
  boolean                     boHssErrorCheckingAllowed;

} tsCddSwi_Ctrl;

typedef enum
{
  eDrvVnd7140,
  eDrvVn7140,
  eDrvTle94x1
}
teCddSwi_DrvTyp;

typedef struct
{
  teCddSwi_DrvTyp eDrvTyp;
  uint8_least     ucDrvIdx;
  uint8_least     ucOutIdx;
}
tsCddSwi_Router;

typedef enum
{
  FAN_NO_0 = 0,
#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
  FAN_NO_1 = 1,
  RGB_SM = 2,
  NO_OF_FANS = 3
#elif defined(SAMPLE_ECO)
  RGB_SM = 1,
  NO_OF_FANS
#endif
} teCddSwi_FanNumbers;

// CddSwi Switch Status
typedef struct
{
  uint16 unHssActVal;
  uint16 unHssActCurrent;
  uint8  ucHssOpenLoad;
  uint8  ucHssShort2VBAT;
  uint8  ucHssShort2GND;
  uint8  ucHssHwState;
}tsCddSwi_SwitchStatus;

typedef uint16 tCddSwi_TgtVal;

typedef enum
{
  eCddSwi_ScrollingSatalite_Off = 0,
  eCddSwi_ScrollingSatelite_On_Scrolling_Off = 1,
  eCddSwi_ScrollingSatelite_On_Scrolling_On = 2
}teCddSwi_ScrollingSateliteState;

#endif // CDD_SWI_2021_03_01_H_
