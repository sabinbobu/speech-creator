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
/// \file  CtrlPxl_Diag.h
///
/// \brief  Header file for diagnostic control of CtrlPxl
///
/// \author Bodian Bianca-Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CTRL_PXL_DIAG_2022_01_20_H_
#define CTRL_PXL_DIAG_2022_01_20_H_

//=============================================================================
// Function prototypes
//=============================================================================
void    CtrlPxl_Diag_ErrorDetected(void);
tuCtrlPxl_bErr   CtrlPxl_GetMtxFaults(uint8_fast ucDevice, uint8_fast ucSwitch);

#endif // CTRL_PXL_DIAG_2022_01_20_H_
