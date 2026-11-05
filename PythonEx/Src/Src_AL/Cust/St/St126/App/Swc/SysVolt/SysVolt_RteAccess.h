
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
/// \file   SysVolt_RteAccess.h
///
/// \brief  Rte wrappers header file
///
/// \descr  Rte Wrappers defines (read/write)
///
/// \author Henrietta Futo (F31185D)
///         mailTo: henrietta-helena.futo[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __SYS_VOLT_RTE_ACCESS_H__
#define __SYS_VOLT_RTE_ACCESS_H__

//=============================================================================
// Includes
//=============================================================================

//#include <Swc/RteS/Rte.h> //this will be used when Rte will be available
#include <SysVolt_Types.h>

//=============================================================================
// Rte wrapper function prototypes
//=============================================================================

void              SysVolt_RteAccess_Read_Vbat(uint16* const unVoltage_mV);
void              SysVolt_RteAccess_Write_Stp_VoltState(teSysVolt_VoltRanges eInVoltageRange);
void              SysVolt_RteAccess_Write_Led_VoltState(teSysVolt_VoltRanges eInVoltageRange);
void              SysVolt_RteAccess_Write_Fan_VoltState(teSysVolt_VoltRanges eInVoltageRange);
Std_ReturnType    SysVolt_RteAccess_ReadVESMainState(teSysVolt_EtatPrincipSEV *psData);
teSysVolt_EtatFee SysVolt_RteAccess_ReadElectricalSuppState(void);

#endif // __SYS_VOLT_RTE_ACCESS_H__

// EOF
