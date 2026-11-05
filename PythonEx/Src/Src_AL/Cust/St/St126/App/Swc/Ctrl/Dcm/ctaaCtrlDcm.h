//*****************************************************************************
// (C) Marelli Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Marelli Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Marelli Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  ctaaCtrlDcm.h
///
/// \brief ctaa wrapper file for CtrlDcm module
///
//-----------------------------------------------------------------------------
#ifndef CTAA_CTRL_DCM_2022_06_23_H
#define CTAA_CTRL_DCM_2022_06_23_H


#include <../Ctrl/Dcm/Api/CtrlDcm.h>
#include <Cfg/Cfg.h>

//=============================================================================
// function prototypes
//=============================================================================

void riCtrlDcm_Init(void);
void rpCtrlDcm_Cycle(void);

#endif // CTAA_CTRL_DCM_2022_06_23_H
