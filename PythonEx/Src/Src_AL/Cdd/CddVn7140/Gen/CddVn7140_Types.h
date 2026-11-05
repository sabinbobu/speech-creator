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
/// \file   CddVn7140_Types.h
///
/// \brief  Types for CddVnd7140
///
/// \author Adrian Horlescu (F31197D)
///         mailTo:adrian-marian.horlescu[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CDD_VN7140_TYPES_2021_03_08_H_
#define CDD_VN7140_TYPES_2021_03_08_H_

//=============================================================================
// Includes
//=============================================================================

#include <Std_Types.h>

//=============================================================================
//  definitions
//=============================================================================

#define CDD_SWI_ON          0x8000u // HSS output active
#ifndef UNIT_TEST
#define CDD_SWI_OFF       0u      // HSS output inactive
#else 
#define CDD_SWI_OFF       1u      // used only for testing electrical error
#endif // !UNIT_TEST

//=============================================================================
//  types
//=============================================================================

typedef void(*pfIoHwAbUserSetTgtVn7140) (uint16 boTgtVal); // pointer to the  function which set the target value on HSS port
typedef void(*pfIoHwAbUserGetDiagValVn7140)(uint32* unDiagVal);        // pointer to the  function which get the diag value on HSS port

typedef struct
{
  pfIoHwAbUserSetTgtVn7140 IoHwAbUSerSetTgtFunc;
}
tsCddVn7140_SetTgt_Router;

typedef struct
{
  pfIoHwAbUserGetDiagValVn7140 IoHwAbUSerGetDiagValFunc;
}
tsCddVn7140_GetDiagVal_Router;

typedef unsigned char tucCddVn7140_Error;
typedef unsigned char tucCddVn7140_HWState;

typedef struct
{
  tucCddVn7140_HWState ucHwState;
  uint16              unActVal;
  uint16              unActCurrent;
  tucCddVn7140_Error   ucErrOpenLoad;
  tucCddVn7140_Error   ucErrShort2VBAT;
  tucCddVn7140_Error   ucErrShort2GND;
}tsCddVn7140_DrvStatus;

typedef struct
{
  tucCddVn7140_HWState ucHwState;         // Status of the eft data
  uint16              unTgtVal;           // Status of Target Value
  uint16              unPreTgtVal;        // Status of Previous Target Value
  uint16              unActVal;           // Status of Actual Value
  uint16              unDiagVal;          // Adc value of diagnose
  uint16              unCurrent;          // Current
  tucCddVn7140_Error   ucErrOpenload;       // Status of Openload
  tucCddVn7140_Error   ucErrShort2GND;      // Status of Shortcoil to GND
  tucCddVn7140_Error   ucErrShort2VBAT;     // Status of Shortcoil to VBAT
} tsCddVn7140_States;


#endif // CDD_VN7140_2021_03_01_H_

// EOF
