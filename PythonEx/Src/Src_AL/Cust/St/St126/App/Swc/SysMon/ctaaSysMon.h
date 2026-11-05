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
/// \file   ctaaSysMon.h
///
/// \brief  
///
/// \descr  Init and Cyclic Runnable prototypes for SysMonCheck
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __CTAA_SYS_MON_H__
#define __CTAA_SYS_MON_H__

//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
void riSysMon_Init(void);
void rcSysMon_Cycle1ms(void);

#endif // __CTAA_SYS_MON_CHECK_H__

// EOF
