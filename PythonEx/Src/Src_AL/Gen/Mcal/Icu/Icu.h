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
/// \file  Icu.h
///
/// \brief External interface oj ICU module
///
/// \author Tanase Alexandru-Anton (F58375C)
///         mailTo:alexandru-anton.tanase[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef ICU_H_
#define ICU_H_

//=============================================================================
// includes
//=============================================================================

#include <Std_Types.h>
#include <Icu_TargetTypes.h>
#include <stdint.h>
#include <AL_Helper.h>

#define CFG_SENS_PWM0                     0u   // SensPwm0
#define CFG_SENS_PWM1                     1u   // SensPwm1

#define FTM_SENS_PWM0                     0u
#define FTM_SENS_PWM1                     0u

#define FTM_CHANNEL_SENS_PWM0             0u
#define FTM_CHANNEL_SENS_PWM1             4u

#define ICU_MEASURE_MODE_DUTY             1u

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// \struct  tDiagSensPwmRes
/// 
/// \brief   PWM sensor response
///
/// \descr
///
typedef struct
{
  uint16        unSensPwm0; // sensor 0
  uint16        unSensPwm1; // sensor 1
}
tDiagSensPwmRes;

//=============================================================================
// data types
//=============================================================================

typedef tsIcu_SpecificType sIcu_ConfigType;
typedef uint32 Icu_PeriodType;
typedef uint32 Icu_ChannelType;



//=============================================================================
// prototypes
//=============================================================================

void Icu_Init(CONST_AL sIcu_ConfigType* ConfigPtr);
//uint16 Icu_CalcDutyCycle_0_ffff(uint32 ulInstance, uint8 ucChannel);
//uint16 Icu_ReadPwmSensor(uint8 ucIdx);
uint16 Icu_GetMeasurementSens(uint8 ucIdx);
void Icu_ChangeMeasurementMode(uint8 ucIndex, uint8 ucMesMode);

//=============================================================================
// constants
//=============================================================================

extern CONST_AL tsIcu_SpecificType sIcu_Config;

#endif // ICU_H_
