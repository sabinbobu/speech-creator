#ifndef __COD_M_PARA_H__
#define __COD_M_PARA_H__

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
/// \file  CodM_Para.h
///
/// \brief  
///
/// \descr Header file which includes each coding data block
///
///               
/// \author Cretu Vlad (F78845C)
///         mailTo:vladut-ioan.cretu[at]marelli.com
//-----------------------------------------------------------------------------
//=============================================================================
// Includes
//=============================================================================
// Here a header file is included for each coding data block
#include <CodM_Para_System.h>
#include <CodM_Para_Led.h>
#include <CodM_Para_Lmm.h>
#include <CodM_Para_Thermo.h>
#include <CodM_Para_Fan.h>
#include <CodM_Para_MappingList.h>
#include <CodM_Para_UnitGroups.h>
#include <CodM_Para_Animation.h>
#include <CodM_Para_AvacStp.h>
#if defined (CFG_VARIANT_FULL) || (UNIT_TEST)
#include <CodM_Para_PXA.h>
#include <CodM_Para_Adb.h>
#include <CodM_Para_AfsDbl.h>
#include <CodM_Para_Matrix.h>
#include <CodM_Para_LmmConfig.h>
#endif
//=============================================================================
// Definitions
//=============================================================================
#define VARIANT_NAME_LENGTH (20u)
#define MAX_NR_OF_VARIANTS  (20u)
#define MAX_ID_LENGTH       (24u)

//=============================================================================
// Types
//=============================================================================
typedef struct
{
  uint8 aucSW__ID_L[MAX_ID_LENGTH];
  uint8 aucSW__ID_R[MAX_ID_LENGTH];
  uint8 ucMajorVersion;
  uint8 ucMinorVersion;
  uint8 ucPatchVersion;
  uint8 aucReserved[64 - 2 * MAX_ID_LENGTH - 3];
}
tCodingHeader;

///** LedBinning NVM struct */
typedef struct
{
    uint8 unData[12];
}
tDiagIfc_LedBinning;

///** Sens Offset NVM struct */
typedef struct
{
    uint16 unOffset[2];
}
tDiagIfc_SensOffset;

typedef struct
{
  tCodingHeader Header;
  uint8 reserved1[4u]; // pointer to start address of Coding Data blocks
  uint8 aucVariantName[VARIANT_NAME_LENGTH];
  uint8 reserved2[19u * 24u]; // reserved for unused pointers and variant tables (19 times unused out of 20)
  //  Parameters taken from ROM stored in RAM
  tNvmPara_SystemBlock           Sys;
  tNvmPara_Led1Block             Led1;
  tNvmPara_LmmABlock             LmmA;         /**< defined in CodM_Para_Lmm.h                */
  tNvmPara_LmmABlock             LmmA_B;       /**< defined in CodM_Para_Lmm.h                */
  tNvmPara_LmmXBlock             LmmX;         /**< defined in CodM_Para_Lmm.h                */
  tNvmPara_Thermo1Block          Thermo1;
  tNvmPara_Fan1Block             Fan1;
  tNvmPara_MappingListBlock      MappingList;
  tNvmPara_UnitGroupsBlock       UnitGroups;
  tNvmPara_AnimationBlock        Animation;
  tNvmPara_AvacStpBlock          AvacStp;
#if defined (CFG_VARIANT_FULL) || (UNIT_TEST)
  tNvmPara_PXABlock              PXA;
  tNvmPara_AdbBlock              Adb;
  tNvmPara_DblBlock              Dbl;
  tNvmPara_MatrixBlock           Matrix;
  tsNvmPara_LmmConfigBlock       LmmConfig;
#endif
}
tNvmPara_CodingArea;

typedef struct
{ 
  // Parameters stored in ROM
  tNvmPara_SystemBlock           Sys;
  tNvmPara_Led1Block             Led1;
  tNvmPara_LmmABlock             LmmA;         /**< defined in CodM_Para_Lmm.h                */
  tNvmPara_LmmABlock             LmmA_B;       /**< defined in CodM_Para_Lmm.h                */
  tNvmPara_LmmXBlock             LmmX;         /**< defined in CodM_Para_Lmm.h                */
  tNvmPara_Thermo1Block          Thermo1;
  tNvmPara_Fan1Block             Fan1;
  tNvmPara_MappingListBlock      MappingList;
  tNvmPara_UnitGroupsBlock       UnitGroups;
  tNvmPara_AnimationBlock        Animation;
  tNvmPara_AvacStpBlock          AvacStp;
#ifdef CFG_VARIANT_FULL
  tNvmPara_PXABlock              PXA;
  tNvmPara_AdbBlock              Adb;
  tNvmPara_DblBlock              Dbl;
  tNvmPara_MatrixBlock           Matrix;
  tsNvmPara_LmmConfigBlock       LmmConfig;
#endif
}
tRomPara_CodingArea;

#ifndef UNIT_TEST
extern volatile const unsigned char CalibrationRom[];
#else
extern volatile unsigned char CalibrationRom[];
#endif

#endif // __COD_M_PARA_H__

// EOF
