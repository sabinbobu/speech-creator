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
/// \file   CddSwi.h
///
/// \brief  API for CddSwi
///
/// \author Adrian Horlescu (F31197D)
///         mailTo:adrian-marian.horlescu[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CDD_SWI_2021_03_01_H_
#define CDD_SWI_2021_03_01_H_

//=============================================================================
// Includes
//=============================================================================

#include <Std_Types.h>
#include <CddSwi_Types.h>

//=============================================================================
// Defines and Typedef
//=============================================================================

#define CDDSWI_HSS_SM 8u
#define CDDSWI_HSS_DRL 4u

//=============================================================================
// Prototypes
//=============================================================================

void                  CddSwi_Init(void);
void                  CddSwi_Cycle0(void);
void                  CddSwi_DeInit(void);
void                  CddSwi_SetTgt(CONST_AL uint32 ulChnIdx, CONST_AL uint16 unTgtVal);  // 0 - 32768   = off: 0, on: 32768
tsCddSwi_SwitchStatus CddSwi_GetState(CONST_AL uint32 ulChnIdx); // Get State

#endif // CDD_SWI_2021_03_01_H_
