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
/// \file   CddVn7140.h
///
/// \brief  API for CddVn7140
///
/// \author Adrian Horlescu (F31197D)
///         mailTo:adrian-marian.horlescu[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CDD_VN7140_2021_03_01_H_
#define CDD_VN7140_2021_03_01_H_

//=============================================================================
// Includes
//=============================================================================

#include <Std_Types.h>

#include <CddVn7140_Router.h>
#include <CddVn7140_Cfg.h>
#include <CddVn7140_Types.h>

//=============================================================================
// Types
//=============================================================================

//=============================================================================
// Prototypes
//=============================================================================

void                   CddVn7140_Init(CONST_AL uint32 ulChipIdx);
void                   CddVn7140_InitCodingParams(void);
void                   CddVn7140_Cycle0(void);
void                   CddVn7140_DeInit(CONST_AL uint32 ulChipIdx);
void                   CddVn7140_SetTgt(CONST_AL uint32 ulChipIdx, CONST_AL uint32 ulOutIdx, CONST_AL uint16 unTgtVal);  // 0 - 32768  = 0% - 100%
tsCddVn7140_DrvStatus  CddVn7140_GetState(CONST_AL uint32 ulChipIdx, CONST_AL uint32 ulOutIdx);


#endif // CDD_VN7140_2021_03_01_H_

// EOF
