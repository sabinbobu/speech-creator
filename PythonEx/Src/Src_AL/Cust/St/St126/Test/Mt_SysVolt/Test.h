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
/// \file  Test.h
///
/// \brief This file contains functions prototypes of the tested module, 
///        including functions parameters and global variables
///
//-----------------------------------------------------------------------------
#ifndef TEST_2023_08_25_H_
#define TEST_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>
#include <Bsw/Dem/Dem.h>
#include <SysVolt_Cfg.h>
#include <Swc/CodM/CodM_Para.h>
#include <Swc/CodM/CodM_Types.h>
#include <RteCommonTypes.h>
#include <Nvm.h>

//=============================================================================
// Module global variables
//=============================================================================
extern boolean                   SysVolt_boCodingValidStatus;
extern tsSysVolt_InVoltState     SysVolt_asInStateResult[eSysV_LastModule_Idx];
extern tsSysVolt_VoltageRangeSet SysVolt_asLevelVoltStp[];
extern tsSysVolt_VoltageRangeSet SysVolt_asLevelFan[];
extern tsSysVolt_VoltageRangeSet SysVolt_asLevelLocalDiagVbat[];
extern tsSysVolt_InVoltCfg       SysVolt_Configs[eSysV_LastModule_Idx];
extern teRte_SysVolt_Results     eSetVoltageState;
extern tsRteCodingParameters     SysVolt_sCodingParam;
extern boolean                   SysVolt_boIsCodingValid;
extern teSysVolt_VbatState       SysVolt_eVbatDiag;

//=============================================================================
// Module function declarations
//=============================================================================
extern void              riSysVoltInit(void);
extern void              rpSysVolt_Cycle(void);
extern void              SysVolt_Init(void);
extern void              SysVolt_Cycle(void);
extern void              SysVolt_ParaFct0(void);
extern void              SysVolt_LocalDiagVbat(teSysVolt_VoltRanges eVbatState);
extern void              SysVolt_ReportVbatDemError(teSysVolt_VbatState eVbatState);
extern void              SysVolt_RteAccess_Write_Stp_VoltState(teSysVolt_VoltRanges eInVoltageRange);
extern void              SysVolt_RteAccess_Write_Fan_VoltState(teSysVolt_VoltRanges eInVoltageRange);
extern void              SysVolt_RteAccess_Read_Vbat(uint16* const unVoltage_mV);
extern void              SysVolt_RteAccess_Write_Led_VoltState(teSysVolt_VoltRanges eInVoltageRange);
extern void              SysVolt_StMachine(boolean boInit);
extern boolean           SysVolt_DetectElecTransition(void);
extern void              SysVolt_Diagnosis(void);
extern Std_ReturnType    SysVolt_RteAccess_ReadVESMainState(teSysVolt_EtatPrincipSEV *psData);
extern teSysVolt_EtatFee SysVolt_RteAccess_ReadElectricalSuppState(void);

//=============================================================================
// Module function parameter stubs
//=============================================================================
teSysVolt_VoltRanges     SysVolt_LocalDiagVbat_Param1;
teSysVolt_VbatState      SysVolt_ReportVbatDemError_Param1;
teSysVolt_VoltRanges     SysVolt_RteAccess_Write_Stp_VoltState_Param1;
uint16                   SysVolt_RteAccess_Read_Vbat_Param1;
teSysVolt_VoltRanges     SysVolt_RteAccess_Write_Fan_VoltState_Param1;
teSysVolt_VoltRanges     SysVolt_RteAccess_Write_Led_VoltState_Param1;
teSysVolt_EtatPrincipSEV SysVolt_RteAccess_ReadVESMainState_Param1;
boolean                  SysVolt_StMachine_Param1;

//=============================================================================
// Module function return value stubs
//=============================================================================
Std_ReturnType    SysVolt_RteAccess_ReadVESMainState_RetVal;
teSysVolt_EtatFee SysVolt_RteAccess_ReadElectricalSuppState_RetVal;
boolean           SysVolt_DetectElecTransition_RetVal;

#endif // TEST_2023_08_25_H_
