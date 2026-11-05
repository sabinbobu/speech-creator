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
/// \file   SysMonRx_ASIL.h
///
/// \brief  
///
/// \descr  SysMon Emergency Operation Mode Header File
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __SYS_MON_RX_ASIL_H__
#define __SYS_MON_RX_ASIL_H__

//-----------------------------------------------------------------------------
//  includes
//-----------------------------------------------------------------------------
#include <SysMon_Types.h>

//-----------------------------------------------------------------------------
//  defines
//-----------------------------------------------------------------------------
// Low Beam timer values
#define SYSMONRX_ASIL_LOWBEAM_CRC_ALIVE_ERROR_MS               320u
#define SYSMONRX_ASIL_LOWBEAM_NO_ERROR_MS                      220u
#define SYSMONRX_ASIL_LOWBEAM_TIMEOUT_ERROR_MS                 300u

// Life Phase timer values for Low Beam
#define SYSMONRX_ASIL_LIFEPHASE_LB_INVALID_ERROR_MS               320u
#define SYSMONRX_ASIL_LIFEPHASE_LB_NO_ERROR_MS                    320u
#define SYSMONRX_ASIL_LIFEPHASE_LB_TIMEOUT_ERROR_MS                20u

// Life Phase timer values for Turn Indicator
#define SYSMONRX_ASIL_LIFEPHASE_TI_INVALID_ERROR_MS               340u
#define SYSMONRX_ASIL_LIFEPHASE_TI_NO_ERROR_MS                    340u
#define SYSMONRX_ASIL_LIFEPHASE_TI_TIMEOUT_ERROR_MS                40u

// Speed timer values
#define SYSMONRX_ASIL_SPEED_CRC_ALIVE_INVALID_ERROR_MS       320u
#define SYSMONRX_ASIL_SPEED_NO_ERROR_MS                      320u
#define SYSMONRX_ASIL_SPEED_TIMEOUT_ERROR_MS                 200u

// VES Main State timer values
#define SYSMONRX_ASIL_VESMAINSTATE_INVALID_ERROR_MS               340u
#define SYSMONRX_ASIL_VESMAINSTATE_NO_ERROR_MS                    340u
#define SYSMONRX_ASIL_VESMAINSTATE_TIMEOUT_ERROR_MS               190u

// Turn Indicator timer values
#define SYSMONRX_ASIL_TURNINDICATOR_INVALID_ERROR_MS               340u
#define SYSMONRX_ASIL_TURNINDICATOR_NO_ERROR_MS                    340u
#define SYSMONRX_ASIL_TURNINDICATOR_TIMEOUT_ERROR_MS               280u
#define SYSMONRX_ASIL_TURNINDICATOR_SCROLLING_MS                   200u
#define SYSMONRX_ASIL_TURNINDICATOR_NO_SCROLLING_MS                  0u

#define SYSMONRX_ASIL_SCROLLING_TI_CHECK_MS                         20u

//-----------------------------------------------------------------------------
//  function prototypes
//-----------------------------------------------------------------------------
void      SysMonRx_ASIL_InitLowBeamAndTurnIndicatorInterfaces(void);
void      SysMonRx_ASIL_EmergencyOperation                               (void);
boolean   SysMonRx_ASIL_Get_boEmergencyOperation_FinalLowBeamStatus      (void);
boolean   SysMonRx_ASIL_Get_boEmergencyOperation_FinalTurnIndicatorStatus(void);
boolean   SysMonRx_ASIL_Get_boDiagLowBeamStatus                          (void);
boolean   SysMonRx_ASIL_Get_boDiagTurnIndicatorStatus                    (void);
boolean   SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam    (void);
boolean   SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationTurnIndicator(void);
SysMon_EnumLowBeamState       SysMonRx_ASIL_GetLowBeamState              (void);
uint8                         SysMonRx_ASIL_GetLowBeamValue              (void);
SysMon_EnumTurnIndicatorState SysMonRx_ASIL_GetTurnIndicatorState        (void);
uint8                         SysMonRx_ASIL_GetTurnIndicatorValue        (void);
SysMon_EnumSpeedState         SysMonRx_ASIL_GetSpeedState                (void);

// -----------------------------------------------------------------------------
// SysMon Rte calls for EcuM
// -----------------------------------------------------------------------------

#define Rte_Call_Get_LB_EmergencyOperationMode  SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam()

#define Rte_Call_Get_SpeedState SysMonRx_ASIL_GetSpeedState()

#define Rte_Call_Get_LowBeamState SysMonRx_ASIL_GetLowBeamState()

#define Rte_Call_Get_TurnIndicatorState SysMonRx_ASIL_GetTurnIndicatorState()

#endif // __SYS_MON_RX_ASIL_H__

// EOF
