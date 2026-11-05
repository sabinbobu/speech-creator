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
/// \file   SysMonCheck_InternalCom.h
///
/// \brief  
///
/// \descr  Function prototypes for SysMonCheck_InternalCom
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __SYS_MON_CHECK_INTERNALCOM_H__
#define __SYS_MON_CHECK_INTERNALCOM_H__

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <RteCommonTypes.h>
#include <SysMon_Types.h>

//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
boolean SysMonCheck_InternalCom_LedState_CheckCrc(tsRte_LedStates* pLedStates_ASIL);
boolean SysMonCheck_InternalCom_TgtLed_FaultStatus_ASIL_CheckCrc(tsRte_TgtLedSig0_FaultStatus_ASIL* pTgtLed_FaultStatus_ASIL);
void    SysMonCheck_InternalCom_Init(void);
void    SysMonCheck_InternalCom_Cycle(void);
boolean SysMonCheck_InternalCom_IsComErrActive(void);

#endif // __SYS_MON_CHECK_INTERNALCOM_H__

// EOF
