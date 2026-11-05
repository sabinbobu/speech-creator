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
/// \file   SysMonCheck.h
///
/// \brief  
///
/// \descr  Cyclic Function prototypes for SysMonCheck
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __SYS_MON_CHECK_H__
#define __SYS_MON_CHECK_H__

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <RteCommonTypes.h>
#include <SysMon_Types.h>

//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
void    SysMonCheck_Init(void);
void    SysMonCheck_Cycle0(void);
void    SysMonCheck_TurnOffFusaChannels(SysMonCheck_Data_tLFName eLEDChannelParamName);
void    SysMonCheck_TriggerCddLed_LowBeam(uint8 ucValue);
void    SysMonCheck_TriggerCddLed_TurnIndicator_Off(void);
boolean SysMonCheck_Get_CodingFailureDiagLowBeamStatus(void);
boolean SysMonCheck_Get_CodingFailureDiagTurnIndicatorStatus(void);
boolean SysMonCheck_TI_Diag_Status(void);
boolean SysMonCheck_Get_TgtLed_FaultStatus_ASIL(void);
boolean SysMonCheck_GetTurnIndicatorCommandValue(void);
tSysMon_FuSaChannelsStatusReaction SysMonCheck_Get_LbTiFuSa_OffStatus(void);

#define Rte_Call_Get_TICmdValue SysMonCheck_GetTurnIndicatorCommandValue()

#endif // __SYS_MON_CHECK_H__

// EOF
