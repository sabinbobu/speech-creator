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
/// \file  ApplCmd_Rdm.h
///
/// \brief ApplCmd_Rdm header file
///
/// \descr 
///
/// \author Alexandru Radu (F48828C)
///         mailTo:alexandru-gabriel.radu[at]marelli.com    
//-----------------------------------------------------------------------------
#ifndef __APPL_CMD_RDM_H__
#define __APPL_CMD_RDM_H__

//=============================================================================
// includes
//=============================================================================
#include <Std_Types.h>
#include <Diag_ApplCmd_RdmTypes.h>
#include <_DIAG_types.h>

#define DIAG_APPLCMD_PRIVILEGE_MODE_SWITCH_SUPPORT STD_ON

//=============================================================================
// prototypes
//=============================================================================
uint8 ApplCmd_Rdm_ReadMemByAddr (UINT8 const* p_ui8_Data, Diag_Length_Type Length);
uint8 ApplCmd_Rdm_WriteMemByAddr(UINT8 const* p_ui8_Data, Diag_Length_Type Length);
uint8 ApplCmd_Rdm_StartSession  (MsgContextType *const pMsgContext);
uint8 ApplCmd_Rdm_SecurityAccess(MsgContextType *const pMsgContext);
void* Diag_GetVirtData_OsSystemCounter(uint32* pulSize);

#if (DIAG_APPLCMD_PRIVILEGE_MODE_SWITCH_SUPPORT == STD_ON)

void ApplCmd_Rdm_PrivilegeUpdate(void);
void ApplCmd_Rdm_GetMcuPrivilegeStatus(void);
void ApplCmd_Rdm_PrivilegeSwitch(void);
void ApplCmd_Rdm_UserSwitch(void);

extern volatile uint32 ApplCmd_Rdm_ulMcuPrivStatus;

#endif

#endif // __APPL_CMD_RDM_H__
