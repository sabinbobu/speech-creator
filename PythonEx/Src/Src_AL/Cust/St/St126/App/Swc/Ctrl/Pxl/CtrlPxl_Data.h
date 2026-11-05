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
/// \file  CtrlPxl_Data.h
///
/// \brief header file - coding data for CtrlPxl
///
/// \author Caba Ionut-Stefan (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef CTRL_PXL_DATA_2022_09_15_H_
#define CTRL_PXL_DATA_2022_09_15_H_

//=============================================================================
// includes
//=============================================================================
#include <CodM.h>
#include "CtrlPxl_Cfg.h"
#include "CtrlPxl_Types.h"

//=============================================================================
// externals variables
//=============================================================================
extern CONST_AL tNvmPara_CodingArea* CtrlPxl_pCodingArea;

//=============================================================================
// inline functions
//=============================================================================
LOCAL_INLINE uint8* CtrlPxl_Data_DriverMap(uint8 ucEcuSide)
{
  return ((ucEcuSide) == ((uint8)eEcu_Left))  ? (uint8*)&CtrlPxl_pCodingArea->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping  : \
         ((ucEcuSide) == ((uint8)eEcu_Right)) ? (uint8*)&CtrlPxl_pCodingArea->MappingList.LogicalUnitsRightHeadlamp_DriverMapping : (uint8*)NULL_PTR;
}

LOCAL_INLINE uint8* CtrlPxl_Data_Get_PxlMap(CONST_AL uint8 ucEcuSide)
{
  return ((ucEcuSide) == ((uint8)eEcu_Left))  ? (uint8*)&CtrlPxl_pCodingArea->Matrix.Left_MatrixPxl_Mapping : \
         ((ucEcuSide) == ((uint8)eEcu_Right)) ? (uint8*)&CtrlPxl_pCodingArea->Matrix.Right_MatrixPxl_Mapping : (uint8*)NULL_PTR;
}

LOCAL_INLINE uint16 CtrlPxl_Data_Get_Size_PxlMap(CONST_AL uint8 ucEcuSide)
{
  return ((ucEcuSide) == ((uint8)eEcu_Left))  ? (sizeof(CtrlPxl_pCodingArea->Matrix.Left_MatrixPxl_Mapping)) : \
         ((ucEcuSide) == ((uint8)eEcu_Right)) ? (sizeof(CtrlPxl_pCodingArea->Matrix.Right_MatrixPxl_Mapping)) : 0u;
}

#define CTRL_PXL_LED_DEFECT_DEBOUNCE_TIME                  (uint32)((uint32)CtrlPxl_pCodingArea->Sys.PxlDebounce.ucPixelFault_DebounceTime * 10u) //600u     //pixel defect maturation time
#define CTRL_PXL_CRC_DEFECT_DEBOUNCE_TIME                  (uint32)((uint32)CtrlPxl_pCodingArea->Sys.PxlDebounce.ucCrcFault_DebounceTime * 10u)// 140u     //crc defect maturation time
#define CTRL_PXL_COM_ERROR_DEBOUNCE_TIME                   (uint32)((uint32)CtrlPxl_pCodingArea->Sys.PxlDebounce.ucComFault_DebounceTime * 10u)//140u    //(cycle time + waiting time) * mlc max no. chips = (10 + 10) * 7 = 140
#define CTRL_PXL_MATRIX_DEFECT_MAX_CLR_ATTEMPTS            CtrlPxl_pCodingArea->Sys.PxlDebounce.ucComFault_NumberOfRetries      //number of retries in case of communication error

//=============================================================================
// prototypes
//=============================================================================
boolean CtrlPxl_CodingDataValidation(void);
boolean CtrlPxl_PxlMap(uint8 pucPxl[CTRLPXL_CFG_NR_OF_MATRIX_DRV][CTRLPXL_CFG_NR_OF_PXLs_STRING]);
boolean CtrlPxl_Data_Matrix(uint8* pucMatrixSegment, uint8 pucSegPos[CTRLPXL_CFG_NR_OF_MATRIX_DRV][CTRLPXL_CFG_NR_OF_PXLs_STRING]);


#endif // CTRL_PXL_DATA_2022_09_15_H_
