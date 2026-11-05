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
/// \file   ctaaStatM.h
///
/// \brief  
///
/// \descr  Init and Cyclic Runnable prototypes for StatM
///
/// \author Liviu Topliceanu (F03343C)
///         mailTo:liviu.topliceanu[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __CTAA_STATM_H__
#define __CTAA_STATM_H__

//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
void riStatM_Init(void);
void rcStatM_Cycle10ms(void);
void reStatM_Deinit(void);
void reStatM_ResetStatistics(void);

#endif // __CTAA_STATM_H__

// EOF
