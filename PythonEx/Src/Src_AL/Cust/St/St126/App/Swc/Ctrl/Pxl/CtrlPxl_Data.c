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
/// \file  CtrlPxl_Data.c
///
/// \brief coding data for CtrlPxl
///
/// \author Caba Ionut-Stefan (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#include "CtrlPxl_Data.h"
#include "CtrlPxl_RteAccess.h"
#include "CtrlPxl_DataInterfaces.h"

//=============================================================================
// defines
//=============================================================================
#define CTRLPXL_INVALID_SIZE            0x00u

//=============================================================================
// variables
//=============================================================================
CONST_AL tNvmPara_CodingArea*  CtrlPxl_pCodingArea;

//=============================================================================
// functions prototype
//=============================================================================
STATIC_AL boolean CtrlPxl_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData);

//=============================================================================
// functions
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_CodingDataValidation
///
/// \descr  get and handle coding parameters for CtrlPxl module
///
/// \param  void
///
/// \return return validity of coding as TRUE
//-----------------------------------------------------------------------------
boolean CtrlPxl_CodingDataValidation(void)
{
  tsCtrlPxl_CodingParameters sCodingParameters;
  //get coding data via RTE
  CTRLPXL_RTE_RE_GET_CODING_DATA(&sCodingParameters)
  //get coding data and return validity of this
  CONST_AL boolean boCodingValidity = CtrlPxl_ParaFct0(sCodingParameters.eCodingState, sCodingParameters.psCodingParameters);
  //return validity of coding
  return boCodingValidity;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_ParaFct0
///
/// \descr  this function get coding params and validity of coding data 
///
/// \param  eCmd - valid/invalid, pData - coding params
///
/// \return coding validity
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlPxl_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData)
{
  boolean boCodingValidity = FALSE;
  //get coding data based on command received
  switch (eCmd)
  {
  case eParaFct0_CodingDataValid:
    boCodingValidity = TRUE;
    CtrlPxl_pCodingArea = pData;
  break;
  case eParaFct0_CodingDataInvalid:
    boCodingValidity = FALSE;
  break;
  default:
    break;
  }
  //return coding validity
  return boCodingValidity;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_PxlMap
///
/// \descr  this function skip the same value of driver type and fill out the 
///         structure with coresponding led channel/pixel from coding map list
///
/// \param  pucPxl : store the logical unit for the matrix chip
///
/// \return check for coding config
//-----------------------------------------------------------------------------
boolean CtrlPxl_PxlMap(uint8 pucPxl[CTRLPXL_CFG_NR_OF_MATRIX_DRV][CTRLPXL_CFG_NR_OF_PXLs_STRING])
{
  boolean boDataOk = TRUE;
  uint8 *pucData;
  tsCtrlPxl_CodHelper *psCodHelper;
  //get ecu side
  CONST_AL uint8 ucEcuSide = CTRLPXL_RTE_RE_GET_ECU_SIDE
  //get driver map data from coding
  //PRQA S 311, 310 1 // Cast needed
  pucData = CtrlPxl_Data_DriverMap(ucEcuSide);
  //check for null pointer
  if (pucData == NULL_PTR)
  {
    boDataOk = FALSE;
  }
  else
  {
    //PRQA S 310 1 // Cast needed
    psCodHelper = (tsCtrlPxl_CodHelper*)&pucData[0];

    for (uint8_fast ucIdx = 0u; ucIdx < CTRLPXL_CFG_NR_OF_LOGICAL_UNITS; ucIdx++)
    {
      uint8 ucLmmId = (uint8)psCodHelper[ucIdx].bLmms_Unit;

      if ((ucLmmId != 0u) && (ucLmmId <= CTRLPXL_CFG_NR_OF_MATRIX_DRV))
      {
        if ((psCodHelper[ucIdx].bSwNr_Unit <= CTRLPXL_CFG_NR_OF_PXLs_STRING) && (psCodHelper[ucIdx].bSwNr_Unit != 0u))
        {
          pucPxl[ucLmmId - 1u][psCodHelper[ucIdx].bSwNr_Unit - 1u] = (uint8)ucIdx;        //[lmm -pxl ] = logical unit
        }
      }
    }
  }
  //return valitity of data
  return boDataOk;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlPxl_Data_Matrix
///
/// \descr  store the logical unit associated to the segment from MATRIX sheet from coding
///
/// \param  pucMatrixSegment  : store logical unit for the matrix segement 
/// \param  pucSegPos         : store position of segment for the lmm-pxl of a logical unit
///
/// \return boolean : validity of coding data
//-----------------------------------------------------------------------------
boolean CtrlPxl_Data_Matrix(uint8* pucMatrixSegment, uint8 pucSegPos[CTRLPXL_CFG_NR_OF_MATRIX_DRV][CTRLPXL_CFG_NR_OF_PXLs_STRING])
{
  boolean boCodingDataStatus = TRUE;
  uint8 *pucData = NULL_PTR, *pucDataMtx = NULL_PTR;
  tsCtrlPxl_CodHelper *psCodHelper;

  //get ecu side
  CONST_AL uint8 ucEcuSide = CTRLPXL_RTE_RE_GET_ECU_SIDE

  //PRQA S 311, 310 1 // Cast needed
  pucDataMtx = CtrlPxl_Data_DriverMap(ucEcuSide);

  //PRQA S 310 1 // Cast needed
  psCodHelper = (tsCtrlPxl_CodHelper*)&pucDataMtx[0];   //access "Mapping List" sheet to take the "logical unit" index for the [lmm][pxl]

  //get data size - 90 segments
  CONST_AL uint16 unDataSize = CtrlPxl_Data_Get_Size_PxlMap(ucEcuSide);

  //get pixel map data
  pucData = CtrlPxl_Data_Get_PxlMap(ucEcuSide);

  //check data and size
  boCodingDataStatus = ((pucData == NULL_PTR) || (unDataSize == CTRLPXL_INVALID_SIZE)) ? FALSE : TRUE;

  //process if coding data is pressent
  if (boCodingDataStatus != FALSE)
  {
    for (uint8_fast ucIdx = 0u; ucIdx < unDataSize; ucIdx++)
    {
      if (pucData[ucIdx] > CTRLPXL_CFG_NR_OF_LOGICAL_UNITS)
      {
        boCodingDataStatus = FALSE;
        break;
      }
      else
      {
        pucMatrixSegment[ucIdx] = (pucData[ucIdx] == 0u) ? CTRLPXL_CFG_UNKNOWN_UINT8_VALUE : (pucData[ucIdx] - 1u);  // segment[0..89] = logical unit

        //get the LmmId and SwNr index from the position of logical unit from segment
        uint8 ucLmmId = (uint8)psCodHelper[pucMatrixSegment[ucIdx]].bLmms_Unit;
        uint8 ucSwNr  = (uint8)psCodHelper[pucMatrixSegment[ucIdx]].bSwNr_Unit;

        if (((ucLmmId != 0u) && (ucLmmId <= CTRLPXL_CFG_NR_OF_MATRIX_DRV)) && ((ucSwNr <= CTRLPXL_CFG_NR_OF_PXLs_STRING) && (ucSwNr != 0u)))
        {
          pucSegPos[(ucLmmId - 1u)][(ucSwNr - 1u)] = (uint8)ucIdx;                   //  [lmm-pxl] = segment
        }
        else
        {
          //do nothing, already 0xFF at invalid position
        }
      }
    }
  }
  return boCodingDataStatus;
}

