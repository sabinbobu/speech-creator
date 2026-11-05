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
/// \file   SigPrepTx.h
///
/// \brief  
///
/// \descr  Tx Frame Processing Header File
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __SIG_PREP_TX_H__
#define __SIG_PREP_TX_H__

//-----------------------------------------------------------------------------
//  includes
//-----------------------------------------------------------------------------
#include <SigPrep_Types.h>

//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
void SigPrepTx_Init(void);
void SigPrepTx_Cycle0(void);
void SigPrepTx_CommStackDataRouter(void);
void SigPrepTx_ComM_ActivateTxBufer(void);
void SigPrepTx_ComM_DeactivateTxBuffer(void);

#endif // __SIG_PREP_TX_H__

// EOF
