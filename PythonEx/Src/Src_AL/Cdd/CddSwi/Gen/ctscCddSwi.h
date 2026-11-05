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
/// \file   ctscCddSwi.h
///
/// \brief  
///
/// \descr  Init and Cyclic Runnable prototypes for CddSwi
///
/// \author Adrian Horlescu (F31197D)
///         mailTo:adrian-marian.horlescu[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __CTSC_CDD_SWI_H__
#define __CTSC_CDD_SWI_H__

#include <Std_Types.h>
//-----------------------------------------------------------------------------
// function prototypes
//-----------------------------------------------------------------------------
void riCddSwi_Init(void);
void rpCddSwi_Cycle0(void);

#endif // __CTSC_CDD_SWI_H_

// EOF
