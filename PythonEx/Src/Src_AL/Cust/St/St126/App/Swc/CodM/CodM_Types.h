#ifndef CODM_TYPES_H_
#define CODM_TYPES_H_
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
/// \file   CodM_Types.h
///
/// \brief  Data types used in CodM module
///
/// \descr  
///
/// \author Cretu Vlad (F78845C)
///         mailTo:vladut-ioan.cretu[at]marelli.com
//-----------------------------------------------------------------------------
//=============================================================================
// includes
//=============================================================================
#include <Std_Types.h>
#include <CodM_Para.h>
//=============================================================================
// defines
//=============================================================================

//=============================================================================
// types
//=============================================================================
typedef struct
{
  tRomPara_CodingArea * pCodingArea;
  uint8  aucVariantName[VARIANT_NAME_LENGTH];
}
tCodMVariantInfo;

typedef struct
{
  tCodingHeader    sHeader;
  tNvmPara_CodingArea pCodingArea;
  uint8  aucVariantName[VARIANT_NAME_LENGTH];
}
tCalibrationData;

typedef tCalibrationData* pCalibrationData;

typedef enum
{
  eParaFct0_CodingDataInvalid = 0u,  // indicates coding data invalid
  eParaFct0_CodingDataValid = 1u  // indicates coding data valid
} tParaFct0_Cmd;

typedef enum
{
  eInitialValue = 0,
  eCodMHTrafficLeft = 1,
  eCodMtHTrafficRght = 2,
}teCodM_HandTraffic;


#endif // CODM_TYPES_H_

// EOF
