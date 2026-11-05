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
/// \file   SysMonTx.h
///
/// \brief  
///
/// \descr  Tx Frame Processing Header File
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __SYS_MON_TX_H__
#define __SYS_MON_TX_H__

//-----------------------------------------------------------------------------
//  includes
//-----------------------------------------------------------------------------
#include <SysMon_Types.h>

//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
void SysMonTx_Init(void);
void SysMonTx_Cycle0(void);
void SysMonTx_ComM_ActivateTxBufer(void);
void SysMonTx_ComM_DeactivateTxBuffer(void);

#endif // __SYS_MON_TX_H__

// EOF
