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
// \file   CddDcmCtrl.h
//
// \brief  Interface header for DC motor driver (of all types)
//
// \descr  DC motor driver
//
// \author Braun, Martin ALRT/EEG-CA (bnm2rt)
//         Paland, Marco ALRT/EEG-PM2 (pm88rt)
//-----------------------------------------------------------------------------

#ifndef _CTRLDCM_H_
#define _CTRLDCM_H_

#include "ILCU_LevellingAdapter.h" /* ILCU_PORT: replaces DPE-only <UtilUtility.h> */


#define CtrlDcm_PosUnknown    1001     // Promill

#define CtrlDcm_MotorStarted     1u
#define CtrlDcm_MotorStopped     0u

// default for AL DC motor
#define CtrlDcm_MaxAdjustingTime 32u // [~ sec ] (0 ... 100%)

#define CtrlDcm_PosRangeMax  850      // Promill
#define CtrlDcm_PosRangeMin  150      // Promill

#define CtrlDcm_Offset         0      // Promill
#define CtrlDcm_Threshold      5      // Promill
#define CtrlDcm_Hysteresis    30      // Promill

#define CtrlDcm_LowestAdjTime  1u     // seconds

#define CtrlDcm_ErrorTime    500u     // milliseconds

  // ??? Muss noch richtig gemacht werden, von Ctrl oder Eep holen.
#define CtrlGetDcMotorMinPos_()   (200)  // 20% DutyCycle
#define CtrlGetDcMotorMaxPos_()   (800)  // 80% DutyCycle

//=============================================================================
// defines for fct calls:
//=============================================================================

void CddDcmCtrl_Init(void);
void CddDcmCtrl_Main(void);

void CddDcmCtrl_Disable(void);
void CddDcmCtrl_CtrlMsg(void);
void CddDcmCtrl_VoltChange(void);

void CddDcmCtrl_DoErrorDetection(void);

//=============================================================================
// States for Dc-Motor State Machine and VoltState
//=============================================================================

typedef enum
{
  CtrlDcm_StateNotActive,
  CtrlDcm_StateMovingDown,
  CtrlDcm_StateMovingPause,
  CtrlDcm_StateMovingUp,
  CtrlDcm_StateMovingDone,
  CtrlDcm_StateLocked,
  CtrlDcm_StateErrorOff
}
tCtrlDcmState;

typedef enum
{
  CtrlDcm_VoltOn,
  CtrlDcm_VoltOff
}
tCtrlDcmVoltage;



#endif // _CTRLDCM_H_
