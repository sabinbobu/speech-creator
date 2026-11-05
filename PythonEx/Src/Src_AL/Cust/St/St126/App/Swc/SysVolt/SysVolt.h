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
/// \file   SysVolt.h
///
/// \brief  SysVolt generic header files
///
/// \descr  Defines and function prototypes
///
/// \author Henrietta Futo (F31185D)
///         mailTo: henrietta-helena.futo[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef _SYS_VOLT_2020_09_11_H_
#define _SYS_VOLT_2020_09_11_H_

//=============================================================================
// Includes
//=============================================================================

#include <Swc/SysVolt/SysVolt_Types.h>
#include <Swc/CodM/CodM.h>
#include <Swc/CodM/CodM_Para.h> //until codm is available
#include <SysVolt_Types.h>

//=============================================================================
//  Macros
//=============================================================================

#define CFG_PG_Cnt         (10u)     // Number of Pixelgroups
#define CFG_NON_MATRIX_BUCKs           (4u)
#define CFG_MATRIX_BUCKs               (8u)
#define CFG_LAMP_CH_Cnt                (CFG_NON_MATRIX_BUCKs + CFG_MATRIX_BUCKs) //used in CtrlLed
#define CFG_LM_Cnt                     (CFG_LAMP_CH_Cnt)     // Number of Leuchtmittel



//=============================================================================
// Prototypes
//=============================================================================

void SysVolt_Init(void);
void SysVolt_Cycle(void);
void SysVolt_ParaFct0(void);
void SysVolt_LocalDiagVbat(teSysVolt_VoltRanges eVbatState);

#endif // _SYS_VOLT_2020_09_11_H_

// EOF
