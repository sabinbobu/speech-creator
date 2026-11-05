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
/// \file   SysMonCheck_LedDiag.h
///
/// \brief  
///
/// \descr  Cyclic Function prototype for SysMonCheck_LedDiag
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __SYS_MON_CHECK_LEDDIAG_H__
#define __SYS_MON_CHECK_LEDDIAG_H__

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <RteCommonTypes.h>
#include <SysMonCheck_Data.h>

//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
void SysMonCheck_LedDiag_Init(void);
void SysMonCheck_LedDiag_Cycle(void);
boolean SysMonCheck_LedDiag_IsLightSourceErrorFree(uint8 ucChIdx);
boolean SysMonCheck_LedDiag_IsLightSourceSpiErrorFree(uint8 ucChIdx);
boolean SysMonCheck_LedDiag_IsTiLightSourceErrorFree(void);

#endif // __SYS_MON_CHECK_LEDDIAG_H__

// EOF
