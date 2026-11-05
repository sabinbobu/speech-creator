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
/// \file  SysMonCheck_Rte.h
///
/// \brief Rte Access for SysMonCheck
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef SYS_MON_CHECK_RTE_2022_02_03_H_
#define SYS_MON_CHECK_RTE_2022_02_03_H_
//=============================================================================
// includes
//=============================================================================
#ifndef UNIT_TEST
#include <Rte.h>
#endif
#include <SysMon_Types.h>

//=============================================================================
// Prototypes
//=============================================================================
void  SysMonCheck_RteAccess_Get_ChannelState(uint8_fast ucIdx, tsSysMon_aChannelState *psChannelState);
void  SysMonCheck_RteAccess_Set_ChannelState(tsSysMon_ErrorHandler  sChannelState[12]);
void  SysMonCheck_RteAccess_Get_TiFailureStatus(boolean *pboStatus);
void  SysMonCheck_RteAccess_Get_ElecSupState(teSysMon_EngineState *pData);
uint8 SysMonCheck_RteAccess_Get_VoltageRange(void);

//=============================================================================
// defines
//=============================================================================

//---------------------------------------sender---------------------------------------

#define SYSMONCHECK_RTE_RE_SET_LED_STATES(pTarget)            SysMonCheck_RteAccess_Set_ChannelState(pTarget); // to CtrlLed


//---------------------------------------receiver---------------------------------------

#define SYSMONCHECK_RTE_RE_GET_LED_STATES(channel, pTarget)   SysMonCheck_RteAccess_Get_ChannelState(channel, pTarget); // from CddLed
#define SYSMONCHECK_RTE_RE_GET_TI_FAILURE_STATUS(pboStatus)   SysMonCheck_RteAccess_Get_TiFailureStatus(pboStatus); // from FctR
#define SYSMONCHECK_RTE_RE_GET_STT_PHASE(pData)               SysMonCheck_RteAccess_Get_ElecSupState(pData); // from SigPrep
#define SYSMONCHECK_RTE_RE_GET_VOLTAGE_RANGE                  SysMonCheck_RteAccess_Get_VoltageRange(); // from SysVolt

#endif // SYS_MON_CHECK_RTE_2022_02_03_H_

