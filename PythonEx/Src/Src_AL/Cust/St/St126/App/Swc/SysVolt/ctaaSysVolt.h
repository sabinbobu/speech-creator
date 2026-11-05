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
/// \file   ctaaSysVolt.h
///
/// \brief  Swc SysVolt runnables header file
///
/// \descr  Init and Cyclic runnable prototypes of SysVolt
///
/// \author Henrietta Futo (F31185D)
///         mailTo: henrietta-helena.futo[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CTAA_SYS_VOLT_2020_09_11_H_
#define CTAA_SYS_VOLT_2020_09_11_H_

//=============================================================================
// Function prototypes
//=============================================================================

void riSysVoltInit(void);
void rpSysVolt_Cycle(void);

#endif // CTAA_SYS_VOLT_2020_09_11_H_

// EOF
