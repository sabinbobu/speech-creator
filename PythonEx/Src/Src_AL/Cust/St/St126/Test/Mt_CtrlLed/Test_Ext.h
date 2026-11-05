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
/// \file  Test_Ext.h
///
/// \brief Stub functions for access to coding parameters excluded from test
///
//-----------------------------------------------------------------------------
#ifndef TEST_EXT_2022_09_07_H_
#define TEST_EXT_2022_09_07_H_

//=============================================================================
// Includes
//=============================================================================
#include <CodM_Para.h>
#include <CtrlLed_Types.h>

//-----------------------------------------------------------------------------
// Types
//-----------------------------------------------------------------------------
extern tNvmPara_CodingArea*   applicationCodingData;
extern tNvmPara_CodingArea*   CtrlLed_pCodingArea;
extern tsCtrlled_CodingData   CtrlLed_sCodingData;

// Ecu mounting side
typedef enum
{
  Mount_Left   = 0,
  Mount_Right  = 1,
  Mount_Undef  = 255
}teEcuSide;


typedef enum { DRV_01 = 1, DRV_02, DRV_03, DRV_04, DRV_05, DRV_06, DRV_07, DRV_08, DRV_09, DRV_10, DRV_11, DRV_12, HSS3,  DRV_NOTUSED = 255  }eDrvId;
typedef enum { LMM_1  = 1,  LMM_2,  LMM_3,  LMM_4,  LMM_5,  LMM_6,  LMM_7,  LMM_8,                                 LMM_NOTUSED = 255         }eLMMId;
typedef enum { PXL_1  = 1,  PXL_2,  PXL_3,  PXL_4,  PXL_5,  PXL_6,  PXL_7,  PXL_8,  PXL_9, PXL_10, PXL_11, PXL_12, PXL_NOTUSED = 255         }eSwitchId;


#define CTRLLED_GAMMA_POINTS_LIST                                                                                                                \
{                                                                                                                                                \
/*GAMMA_1_POINTS*/ { 66u, 82u, 193u, 497u, 1089u, 2064u, 3518u, 5548u, 8249u, 11718u, 16050u, 21340u, 27686u, 35182u, 43926u, 54012u, 65535u },  \
/*GAMMA_2_POINTS*/ { 66u, 82u, 193u, 497u, 1089u, 2064u, 3518u, 5548u, 8249u, 11718u, 16050u, 21340u, 27686u, 35182u, 43926u, 54012u, 65535u },  \
} 


//-----------------------------------------------------------------------------
// Access specific coding parameters
//-----------------------------------------------------------------------------
void Mt_InitializeCodingData(teEcuSide eEcuSide);
void CtrlLed_CreateCodingData_FULLVariant(void);
void Mt_InternalCodingMapping(void);

#endif // TEST_EXT_2022_09_07_H_
