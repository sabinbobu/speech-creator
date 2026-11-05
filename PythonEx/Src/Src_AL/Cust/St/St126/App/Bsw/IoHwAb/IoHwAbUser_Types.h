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
/// \file  IoHwAbUser_Types.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef IO_HW_AB_USER_TYPES_2021_09_13_H_
#define IO_HW_AB_USER_TYPES_2021_09_13_H_

#include <AL_Helper.h>

//=============================================================================
// Types
//=============================================================================

typedef struct
{
  boolean boEnable1;
  boolean boEnable2;
  uint16 unBstSyncDuty;
}tsIoHwAb_BoostModeTarget;

typedef struct tsIoHwAbUser_HSSDioInfo
{
  boolean                 boDioSel0Toggle;
  uint8                   ucWaitingTime;
}tsIoHwAbUser_HSSDioInfo;

typedef enum
{
  eIoHwAb_Vccx_noError = 0, //No error detected for Vccx voltage line
  eIoHwAb_Vccx_Short2GND = 1, //Short to ground detected for Vccx line
  eIoHwAb_Vccx_Short2Vbat = 2, //Short to battery detected for Vccx line
}teIoHwAb_VccxLineState;

typedef enum
{
  eIoHwAb_Hls_noError = 0, //No error detected for Hls voltage
  eIoHwAb_Hls_Error = 1 //Short to ground/battery detected for Hls
}teIoHwAb_HlsState;

#endif // IO_HW_AB_USER_TYPES_2021_09_13_H_

//EOF

