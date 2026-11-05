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
/// \file   CtrlPxl_MemHandling.h
///
/// \brief  Header file for EEPROM handling
///
/// \author Bodian Bianca-Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CTRL_PXL_MEM_HANDLING_2022_05_09_H_
#define CTRL_PXL_MEM_HANDLING_2022_05_09_H_

//=============================================================================
// includes
//=============================================================================
#include "CtrlPxl_Types.h"

//=============================================================================
// Definitions
//=============================================================================

//=============================================================================
// variables
//=============================================================================

//=============================================================================
// Types
//=============================================================================

//=============================================================================
// prototypes
//=============================================================================
void CtrlPxl_ProcessMatrixEEPROM(void);
void CtrlPxl_ReadAndCheckNvMMatrixData(void);

void CtrlPxl_MtxEEClbkRead_Success(void);
void CtrlPxl_MtxEEClbkRead_Fail(void);
void CtrlPxl_MtxEEClbkWrite_Success(void);
void CtrlPxl_MtxEEClbkWrite_Fail(void);

tsCtrlPxl_InternalHandling * CtrlPxl_GetInternalHandlingStruct(void);

#endif // CTRL_PXL_MEM_HANDLING_2022_05_09_H_
