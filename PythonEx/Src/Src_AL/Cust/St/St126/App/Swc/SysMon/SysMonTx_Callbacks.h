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
/// \file   SysMonTx_Callbacks.h
///
/// \brief  
///
/// \descr  Output Frame Tx Callbacks Header file
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __SYS_MON_TX_CALLBACKS_H__
#define __SYS_MON_TX_CALLBACKS_H__

//-----------------------------------------------------------------------------
//  includes
//-----------------------------------------------------------------------------
#include <SysMon_Types.h>

//-----------------------------------------------------------------------------
//  defines
//-----------------------------------------------------------------------------
#define SYSMONTX_CALLBACKS_DIAG_TI_OK     0x01u
#define SYSMONTX_CALLBACKS_DIAG_TI_NOK    0x02u

//-----------------------------------------------------------------------------
// callbacks prototypes
//-----------------------------------------------------------------------------
void SysMon_TxCallbacks_CyclicFrame_457(void);
void SysMon_TxCallbacks_CyclicFrame_477(void);
void SysMon_TxCallbacks_ToFrame_4x7(void);

#endif // __SIG_PREP_TX_CALLBACKS_H__

// EOF

