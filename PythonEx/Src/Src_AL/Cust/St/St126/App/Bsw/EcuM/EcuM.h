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
/// \file  EcuM.h
///
/// \brief Ecu Manager functionality main header file
///
/// \Project LDMO
///
/// \Author Stefan Tyirean (f75617c) mailto: stefan.tyirean[a]marelli.com
///
/// \Date September 2021
//-----------------------------------------------------------------------------
#ifndef ECU_M_2021_09_08_H_
#define ECU_M_2021_09_08_H_

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "EcuM_Types.h"

//-----------------------------------------------------------------------------
// prototypes
//-----------------------------------------------------------------------------
extern boolean EcuM_boDiagReqReset;

void EcuM_Init(void);
void EcuM_MainFunction(void);
void EcuM_StartupTwo_Trusted(void);
void EcuM_StartupTwo_NonTrusted(void);
void EcuM_RequestRUN(uint8 ucUser);
void EcuM_RequestPOST_RUN(uint8 ucUser);
void EcuM_ReleaseRUN(uint8 ucUser);
void EcuM_ReleasePOST_RUN(uint8 ucUser);
void EcuM_ReportWgdReset(void);
void EcuM_ReportAppCrcReset(void);
void EcuM_FlashCrcFailure_Indication(void);
void EcuM_DiagResetRequest(void);
void EcuM_PrivilegeUpdate(void);
void EcuM_InvalidInterrupt_Reset(void);
void EcuM_McuPrivilegeSwitch(uint8 ucMode);

extern void HardFault_Handler(void);
extern void FTFC_Fault_IRQHandler(void);
extern void ERM_double_fault_IRQHandler(void);
extern void ERM_single_fault_IRQHandler(void);

#if (CFG_DEV_HOOK_EN == 1u) || defined (UNIT_TEST)
void * EcuM_Get_Mpu_Test_Hook_Address(void);
#endif

#endif // ECU_M_2021_09_08_H_

// EOF
