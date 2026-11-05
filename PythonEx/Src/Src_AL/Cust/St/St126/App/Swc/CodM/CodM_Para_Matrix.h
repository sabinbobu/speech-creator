#ifndef __CODM_PARA_MATRIX_H__
#define __CODM_PARA_MATRIX_H__


//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************

///-----------------------------------------------------------------------------
///  \file   CodM_Para_Matrix.h
///
///  \brief  Content of datagroup "Matrix"
///
///  \descr  Source: LDMO_CodingTool_FULL.xlsm. 
///          Version TBD 
///          For further details see coding parameter
///
///  \author This file is auto generated - please do not edit
///
///  \date   27.09.2021, 18:51:15
///-----------------------------------------------------------------------------
#include <AL_Helper/AL_Helper.h>

#define CODM_PARA_MATRIX_ROW_COUNT   3u
#define CODM_PARA_MATRIX_COL_COUNT   30u

typedef struct
{
  // Light intesity for Led from row1 to row3, column1 to column 30
  uint8 anLIGHT_INTENS_LFT[CODM_PARA_MATRIX_ROW_COUNT][CODM_PARA_MATRIX_COL_COUNT];
}
tNvmPara_Matrix_LghtDstrbtn;


typedef struct 
{
  tNvmPara_Matrix_LghtDstrbtn Left_MatrixPxl_Mapping;
  tNvmPara_Matrix_LghtDstrbtn Right_MatrixPxl_Mapping;
} tNvmPara_MatrixBlock;



#endif // __CODM_PARA_MATRIX_H__
