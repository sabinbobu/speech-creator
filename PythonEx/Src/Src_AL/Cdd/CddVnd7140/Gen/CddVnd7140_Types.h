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
/// \file   CddVnd7140_Types.h
///
/// \brief  Types for CddVnd7140
///
/// \author Adrian Horlescu (F31197D)
///         mailTo:adrian-marian.horlescu[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CDD_VND7140_TYPES_2021_03_08_H_
#define CDD_VND7140_TYPES_2021_03_08_H_

//=============================================================================
// Includes
//=============================================================================

#include <Std_Types.h>

//=============================================================================
//  definitions
//=============================================================================

#define CDD_SWI_ON        0x8000u // HSS output active
#define CDD_SWI_OFF       0u      // HSS output inactive

//=============================================================================
//  types
//=============================================================================

typedef void(*pfIoHwAbUserSetTgtVnd7140) (tun16Percent_1_328 boTgtVal); // pointer to the  function which set the target value on HSS port
typedef void(*pfIoHwAbUserGetDiagValVnd7140)(uint32* unDiagVal);        // pointer to the  function which get the diag value on HSS port

typedef struct
{
  pfIoHwAbUserSetTgtVnd7140 IoHwAbUSerSetTgtFunc;
}
tsCddVnd7140_SetTgtRouter;

typedef struct
{
  pfIoHwAbUserGetDiagValVnd7140 IoHwAbUSerGetDiagValFunc;
}
tsCddVnd7140_GetDiagValRouter;

typedef unsigned char tucCddVnd7140_Error;
typedef unsigned char tucCddVnd7140_HWState;

typedef struct
{
  tucCddVnd7140_HWState ucHwState;
  uint16               unActVal;
  uint16               unActCurrent;
  tucCddVnd7140_Error   ucErrOpenLoad;
  tucCddVnd7140_Error   ucErrShort2VBAT;
  tucCddVnd7140_Error   ucErrShort2GND;
}tsCddVnd7140_DrvStatus;

typedef struct
{
  tucCddVnd7140_HWState ucHwState;         // Status of the eft data
  uint16               unTgtVal;          // Status of Target Value
  uint16               unPreTgtVal;       // Status of Previous Target Value
  uint16               unActVal;          // Status of Actual Value
  uint16               unDiagVal;         // Adc value of diagnose
  uint16               unCurrent;         // Current
  tucCddVnd7140_Error   ucErrOpenload;      // Status of Openload
  tucCddVnd7140_Error   ucErrShort2GND;     // Status of Shortcoil to GND
  tucCddVnd7140_Error   ucErrShort2VBAT;    // Status of Shortcoil to VBAT
} tsCddVnd7140_States;


#endif // CDD_VND7140_2021_03_01_H_

// EOF
