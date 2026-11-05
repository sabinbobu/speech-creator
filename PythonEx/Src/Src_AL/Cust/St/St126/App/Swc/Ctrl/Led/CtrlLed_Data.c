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
/// \file  CtrlLed_Data.c
///
/// \brief coding data for CtrlLed
///
/// \author Caba Ionut-Stefan (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================
#include "CtrlLed_Data.h"
#include "CtrlLed_Rte.h"

/* PRQA S 310,311 EOF */
//=============================================================================
// variables
//=============================================================================
CONST_AL tNvmPara_CodingArea*  CtrlLed_pCodingArea;

//=============================================================================
// local types
//=============================================================================


//=============================================================================
// defines
//=============================================================================
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
#define CTRLLED_INVALID_SIZE            0x00u
#endif

#define CTRLLED_DATA_SINGLE_UNIT_SELECTION   0x01u
#define CTRLLED_DATA_GROUP_UNIT_SELECTION    0x02u
#define CTRLLED_DATA_UNKNOWN_UNIT_SELECTION  0xFFu

//=============================================================================
// functions prototype
//=============================================================================
STATIC_AL boolean CtrlLed_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData);
STATIC_AL boolean CtrlLed_Data_DriverMap(CONST_AL uint8 ucEcuSide, tsCtrlled_CodingData *psCodingData);
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
STATIC_AL boolean CtrlLed_Data_Matrix(CONST_AL uint8 ucEcuSide, tsCtrlled_CodingData *psCodingData);
STATIC_AL boolean CtrlLed_Data_Get_UnitGroup(CONST_AL uint8 ucEcuSide, tsCtrlled_CodingData *psCodingData);
STATIC_AL void CtrlLed_Data_Process_MultiUnits(uint8 ucDrvIdIdx, uint8_fast ucIdxLu, tsCtrlled_CodingData *psCodingData);
#endif
STATIC_AL void CtrlLed_Data_Process_SingleUnits(uint8 *pucData, uint8 ucDrvIdIdx, uint8_fast ucIdxLu, tsCtrlled_CodingData *psCodingData);
STATIC_AL boolean CtrlLed_Data_Led1(CONST_AL uint8 ucEcuSide, tsCtrlled_CodingData *psCodingData);
STATIC_AL boolean CtrlLed_Data_LmmX(CONST_AL uint8 ucEcuSide, tsCtrlled_CodingData *psCodingData);
STATIC_AL boolean CtrlLed_Data_AnimaMap(CONST_AL uint8 ucEcuSide, tsCtrlled_CodingData *psCodingData);
// Array of function pointers to handle coding data 
STATIC_AL boolean(*CtrlLed_Data_apfnDataMap_List[]) (CONST_AL uint8 ucEcuSide, tsCtrlled_CodingData *psCodingData) =
{ 
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  CtrlLed_Data_Matrix,
  CtrlLed_Data_Get_UnitGroup,
#endif
  CtrlLed_Data_DriverMap,
  CtrlLed_Data_Led1,
  CtrlLed_Data_LmmX,
  CtrlLed_Data_AnimaMap,
};

#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
STATIC_AL uint8 ucUnitGroupCnt = 0U;
#endif

#ifdef UNIT_TEST
/* -------------------------------------------------- */
/* Special UT instrumentation to force invalid coding */
/* -------------------------------------------------- */
STATIC_AL void CtrlLed_Special_UT_Instrumentation_Force_InvalidCoding(uint16** punData, boolean* boCodingValid);
STATIC_AL void CtrlLed_Special_UT_Instrumentation_Force_InvalidBinnCoding(uint16* punData, boolean* boCodingValid);

#endif

//=============================================================================
// functions
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief  CtrlLed_CodingDataValidation
///
/// \descr  get and handle coding parameters for CtrlLed module
///
/// \param  void
///
/// \return return validity of coding as TRUE
//-----------------------------------------------------------------------------
boolean CtrlLed_CodingDataValidation(void)
{
  tsCtrlLed_CodingParam sCodingParameters;

  //get coding data via RTE
  CTRLLED_RTE_RE_GET_CODING_DATA(&sCodingParameters)
  //get coding data and return validity of this
  CONST_AL boolean boCodingValidity = CtrlLed_ParaFct0(sCodingParameters.eCodingState, sCodingParameters.psCodingParameters_Blocks);

  //return validity of coding
  return boCodingValidity;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_ParaFct0
///
/// \descr  this function get coding params and validity of coding data 
///
/// \param  eCmd - valid/invalid, pData - coding params
///
/// \return coding validity
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlLed_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData)
{
  boolean boCodingValidity = FALSE;

  switch (eCmd)
  {
  case eParaFct0_CodingDataValid:
    boCodingValidity = TRUE;
    CtrlLed_pCodingArea = pData;
  break;
  case eParaFct0_CodingDataInvalid:
    boCodingValidity = FALSE;
  break;
  default:
    break;
  }

  return boCodingValidity;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_CodMap
///
/// \descr  this function skip the same value of driver type and fill out the 
///         structure with coresponding led channel/pixel from coding map list
///
/// \param  *psCodingData
///
/// \return check for coding config
//-----------------------------------------------------------------------------
boolean CtrlLed_CodMap(tsCtrlled_CodingData *psCodingData)
{
  boolean boCodingDataStatus = TRUE;
  //size of CtrlLed_Data_apfnDataMap_List
  CONST_AL uint8 ucSize = (sizeof(CtrlLed_Data_apfnDataMap_List) / sizeof(CtrlLed_Data_apfnDataMap_List[0]));
  //get ECU side
  CONST_AL uint8 ucEcuSide = CTRLLED_RTE_RE_GET_ECU_SIDE

  //handle data coding used in this module
  for (uint8_fast ucShSel = 0u; ucShSel < ucSize; ucShSel++)
  {
    boCodingDataStatus = (CtrlLed_Data_apfnDataMap_List[ucShSel] == NULL_PTR) ? FALSE : CtrlLed_Data_apfnDataMap_List[ucShSel](ucEcuSide, psCodingData);

    if (boCodingDataStatus == FALSE) 
    { 
      break;
    }
  }

  //return validity of coding data
  return boCodingDataStatus;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_Data_DriverMap
///
/// \descr  store buck type from DRIVER MAP sheet from coding
///
/// \param  ucEcuSide, *psCodingData
///
/// \return validity of coding data
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlLed_Data_DriverMap(CONST_AL uint8 ucEcuSide, tsCtrlled_CodingData *psCodingData)
{
  boolean boCodingDataStatus = TRUE;
  uint8 *pucData_DrvMap = NULL_PTR;
  uint8 *pucData_LuIl = NULL_PTR;
  tsCtrlLed_CodHelper *psCodHelper;
  uint8 ucDrvIdIdx = 0u;
  //get driver map data
  pucData_DrvMap = CtrlLed_Data_Get_DriverMap(ucEcuSide);
  //get logical iluminants maped
  pucData_LuIl = CtrlLed_Data_Led_LogicalUnitsIl(ucEcuSide);

  //check for null ptr
  boCodingDataStatus = ((pucData_DrvMap == NULL_PTR) || (pucData_LuIl == NULL_PTR)) ? FALSE : TRUE;

  //process if coding data is pressent
  if (boCodingDataStatus != FALSE)
  {
    //fit data 
    psCodHelper = (tsCtrlLed_CodHelper*)&pucData_DrvMap[0];
    
    for (uint8_fast ucIdxLu = 0u; ucIdxLu < CTRLLED_CFG_NR_OF_LOGICAL_UNITS; ucIdxLu++)
    {
      uint8 ucLmmId = (uint8)psCodHelper[ucIdxLu].bLmms_Unit;
      uint8 ucDrvId = (uint8)psCodHelper[ucIdxLu].bDrv_Unit;
      
      //check for invalid data
      if ((ucDrvId != 0u) && (ucDrvId <= CTRLLED_CFG_MAX_BUCK_DRV))
      {
        ucDrvIdIdx = ucDrvId - 1U;
#if defined(CFG_VARIANT_ECO) || defined(UNIT_TEST)
        if (ucDrvId == CTRLLED_CFG_MAX_BUCK_DRV)
        {
          ucDrvIdIdx = 4u;
        }
#endif
        //store buck driver type (matrix or non-matrix)
        // PRQA S 1860 1 // ucDrvId always will be != 0
        psCodingData->aucChannelType[ucDrvIdIdx] = ((ucLmmId != 0u) && (ucLmmId <= CTRLLED_CFG_MAX_LMM_DRV)) ? CTRLLED_CFG_MATRIX_BUCK : CTRLLED_CFG_NON_MATRIX_BUCK;

        if (psCodingData->aucChannelType[ucDrvIdIdx] == CTRLLED_CFG_NON_MATRIX_BUCK) //single unit group
        {
          CtrlLed_Data_Process_SingleUnits(pucData_LuIl, ucDrvIdIdx, ucIdxLu, psCodingData);
        }
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
        else //unit group
        {
          CtrlLed_Data_Process_MultiUnits(ucDrvIdIdx, ucIdxLu, psCodingData);
        }
#endif
      }
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
      else
      {
        psCodingData->aucLuIl[ucIdxLu] = 0xFFu;
      }
#endif

#ifdef UNIT_TEST
      /* -------------------------------------------------- */
      /* Special UT instrumentation to force invalid coding */
      /* -------------------------------------------------- */
      CtrlLed_Special_UT_Instrumentation_Force_InvalidCoding(&pucData_DrvMap, &boCodingDataStatus);
#endif
    }
  }

  return boCodingDataStatus;
}

 //-----------------------------------------------------------------------------
/// \brief  CtrlLed_Data_Process_SingleUnits
///
/// \descr  
///
/// \param  *pucData, ucDrvIdIdx, ucIdxLu, *psCodingData
///
/// \return void
//-----------------------------------------------------------------------------
 STATIC_AL void CtrlLed_Data_Process_SingleUnits(uint8 *pucData, uint8 ucDrvIdIdx, uint8_fast ucIdxLu, tsCtrlled_CodingData *psCodingData)
 {
#if defined(CFG_VARIANT_ECO) || defined(UNIT_TEST)   
   (void)ucIdxLu;
#endif
   
   //should not be reach here in case pucData is = to null pointer because is check before of calling this function
   if (pucData != NULL_PTR)
   {
     for (uint8_fast ucIdxIl = 0u; ucIdxIl < CTRLLED_CFG_NO_ILLUMINANTS; ucIdxIl++)
     {
       //pucData[ucIdxIl] contain value of Logical Unit and should be checked with current logical unit, and in case is matching, store DriverId, Current Logical Unit for
       //current illuminant and Vice-Versa
       if ((pucData[ucIdxIl] - 1U) == (uint8)ucIdxLu)
       {
         CTRLLED_SET_BIT_U16(psCodingData->aunChannelIlluminant[ucIdxIl], ucDrvIdIdx);
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
         psCodingData->aucLuIl[ucIdxLu] = (uint8)ucIdxIl;
#endif
         psCodingData->ucLogicalUnitIl[ucIdxIl] = (pucData[ucIdxIl] - 1U);
         //stop the loop
         break;
       }
     }
   }
 }

#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
 //-----------------------------------------------------------------------------
/// \brief  CtrlLed_Data_Process_MultiUnits
///
/// \descr  
///
/// \param  ucDrvIdIdx, ucIdxLu, *psCodingData
///
/// \return void
//-----------------------------------------------------------------------------
 STATIC_AL void CtrlLed_Data_Process_MultiUnits(uint8 ucDrvIdIdx, uint8_fast ucIdxLu, tsCtrlled_CodingData *psCodingData)
 {
   for (uint8_fast ucIdxG = 0U; ucIdxG < ucUnitGroupCnt; ucIdxG++)
   {
     CONST_AL uint16 unLuMirror = ((uint16)CTRLLED_CFG_NR_OF_LOGICAL_UNITS - (uint16)ucIdxLu);
     CONST_AL uint16 unByteUsage = (unLuMirror / 8U);
     CONST_AL uint16 unPos = (unLuMirror % 8U);

     if (CTRLLED_CHECK_BIT_U16(psCodingData->asUnitGroups[ucIdxG].uUnitGroups.aucUg[unByteUsage], unPos) != FALSE)
     {
       CTRLLED_SET_BIT_U16(psCodingData->aunChannelIlluminant[psCodingData->asUnitGroups[ucIdxG].ucIlluminantAssigned], ucDrvIdIdx);
       psCodingData->aucLuIl[ucIdxLu] = psCodingData->asUnitGroups[ucIdxG].ucIlluminantAssigned;
       psCodingData->aboIlMtxType[psCodingData->asUnitGroups[ucIdxG].ucIlluminantAssigned] = TRUE;
       psCodingData->ucLogicalUnitIl[psCodingData->asUnitGroups[ucIdxG].ucIlluminantAssigned] = psCodingData->asUnitGroups[ucIdxG].ucName;
       //stop the loop
       break;
     }
   }
 }

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_Data_Matrix
///
/// \descr  store lmm switch number from MATRIX sheet from coding
///
/// \param  ucEcuSide, *psCodingData
///
/// \return validity of coding data
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlLed_Data_Matrix(CONST_AL uint8 ucEcuSide, tsCtrlled_CodingData *psCodingData)
{
  boolean boCodingDataStatus = TRUE;
  uint8 *pucData = NULL_PTR;
  //get data size
  CONST_AL uint16 unDataSize = CtrlLed_Data_Get_Size_PxlMap(ucEcuSide);

  //get pixel map data
  pucData = CtrlLed_Data_Get_PxlMap(ucEcuSide);
  //check data and size
  boCodingDataStatus = ((pucData == NULL_PTR) || (unDataSize == CTRLLED_INVALID_SIZE)) ? FALSE : TRUE;

  //process if coding data is pressent
  if (boCodingDataStatus != FALSE)
  {
    for (uint8_fast ucIdx = 0u; ucIdx < unDataSize; ucIdx++)
    {
      if (pucData[ucIdx] > CTRLLED_CFG_NR_OF_LOGICAL_UNITS)
      {
        boCodingDataStatus = FALSE;
        break;
      }
      else
      {
        psCodingData->aucLmmSwitchNo[ucIdx] = (pucData[ucIdx] == 0u) ? CTRLLED_CFG_UNKNOWN_UINT8_VALUE : (pucData[ucIdx] - 1u);
      }
    }
  }
 
  return boCodingDataStatus;
}
#endif

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_Data_Led1
///
/// \descr  get binning and voltage data from LED1 sheet from coding
///
/// \param  ucEcuSide, *psCodingData
///
/// \return validity of coding data
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlLed_Data_Led1(CONST_AL uint8 ucEcuSide, tsCtrlled_CodingData *psCodingData)
{
  boolean boCodingDataStatus = TRUE;
  uint8 ucBinningSelect = CTRLLED_CFG_UNKNOWN_UINT8_VALUE;
  uint8  *puc_LedName = NULL_PTR;

  (void)ucEcuSide;
  
  for (uint8_fast ucIdx = 0u; ucIdx < CTRLLED_CFG_BASIC_LED_CH; ucIdx++)
  {
    //get binning class selection
    ucBinningSelect = CTRLLED_RTE_RE_BINNING_CLASS(ucIdx)
    //update binning current
    boCodingDataStatus = CtrlLed_CurrentUpdates(ucIdx, ucBinningSelect, psCodingData);
    
    if(boCodingDataStatus == FALSE)
    { 
      break;
    }
  }

  puc_LedName = CtrlLed_Data_Get_ConfigLedName();

#ifdef UNIT_TEST
      /* -------------------------------------------------- */
      /* Special UT instrumentation to force invalid coding */
      /* -------------------------------------------------- */
  CtrlLed_Special_UT_Instrumentation_Force_InvalidCoding(&puc_LedName, &boCodingDataStatus);
#endif

  //check for null ptr
  if (puc_LedName == NULL_PTR)
  {
    boCodingDataStatus = FALSE;
  }
  else
  {
    //LED Names for DTCs and error selection
    for (uint8_fast ucIdx = 0u; ucIdx < CTRLLED_CFG_LED_CHANNELS_NR; ucIdx++)
    {
      if (ucIdx == CTRLLED_CFG_BASIC_LED_CH)
      {
        psCodingData->ucLedName[ucIdx] = CtrlLed_Data_Get_ConfigLedHssName();
      }
      else
      {
        psCodingData->ucLedName[ucIdx] = puc_LedName[ucIdx];
      }
    }
  }
 
  return boCodingDataStatus;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_Data_LmmX
///
/// \descr  store gamma from LmmX sheet
///
/// \param  ucEcuSide, *psCodingData
///
/// \return validity of coding data
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlLed_Data_LmmX(CONST_AL uint8 ucEcuSide, tsCtrlled_CodingData *psCodingData)
{
  boolean boCodingDataStatus = TRUE;
  uint16 *punData = NULL_PTR;
  uint8 *pucGammaSel = NULL_PTR;

  (void)ucEcuSide;
  //get gamma
  punData = CtrlLed_Data_Led_GammaCfg(); 

  //get gamma selector
  pucGammaSel = CtrlLed_Data_Led_GammaCfgSel();

#ifdef UNIT_TEST
      /* -------------------------------------------------- */
      /* Special UT instrumentation to force invalid coding */
      /* -------------------------------------------------- */
  CtrlLed_Special_UT_Instrumentation_Force_InvalidCoding(&punData, &boCodingDataStatus);
#endif

  //check data validity
  boCodingDataStatus = ((punData == NULL_PTR) || (pucGammaSel == NULL_PTR)) ? FALSE : TRUE;
  
  if (boCodingDataStatus != FALSE)
  {
    //gamma points
    for (uint8_fast ucIdxI = 0u; ucIdxI < CTRLLED_CFG_GAMMA_NUMBER; ucIdxI++)
    {
      for (uint8_fast ucIdxJ = 0u; ucIdxJ < CTRLLED_CFG_GAMMA_POINTS; ucIdxJ++)
      {
        psCodingData->sGamma.aunGamma[ucIdxI][ucIdxJ] = punData[CTRLLED_CFG_GAMMA_POINTS * ucIdxI + ucIdxJ];
      }
    }

    //gamma sel
    for (uint8_fast ucIdxIl = 0u; ucIdxIl < CTRLLED_CFG_NO_ILLUMINANTS; ucIdxIl++)
    {
      psCodingData->sGamma.aucGammaSel[ucIdxIl] = pucGammaSel[ucIdxIl];
    }
  }

  return boCodingDataStatus;
}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_GetAndCheckLedName
///
/// \descr  
///
/// \param  ucIdx, ucIdxIl
///
/// \return uint8 -channel name
//-----------------------------------------------------------------------------
uint8 CtrlLed_GetAndCheckLedName(uint8_fast ucIdx, uint8_fast ucIdxIl)
{
  uint8 ucChannelName = CTRLLED_CFG_UNKNOWN_UINT8_VALUE;
#if defined(CFG_VARIANT_ECO) || defined(UNIT_TEST)
  (void)ucIdxIl;
#endif
  ucChannelName = Cod_LedName(ucIdx);

  //check range
  if ((ucChannelName == CTRLLED_CH_NAME_COD_OUTPUT_OFF) || (ucChannelName > CTRLLED_CH_NAME_MAX))
  {
    ucChannelName = CTRLLED_CFG_UNKNOWN_UINT8_VALUE;
  }
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
  //pixel 
  else if ((ucChannelName == CTRLLED_CH_NAME_COD_PXL) || (ucChannelName == CTRLLED_CH_NAME_COD_MXB))
  {
    if (ucIdxIl == 15U)//last illuminant (HB stand alone)
    {
      ucChannelName = CTRLLED_CH_NAME_PXL_HB;
    }
    else
    {
      ucChannelName = CTRLLED_CH_NAME_PXL_LB;
    }
  }
#endif
  else
  {
    ucChannelName -= 1U;
  }
  //return channel name
  return ucChannelName;
}

#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
//-----------------------------------------------------------------------------
/// \brief  CtrlLed_Data_Decompressed_UnitGroup
///
/// \descr  this function extract channel usage in *boData from each unit group
///
/// \param  ucEcuSide, ucLogicalUnit, ucUnitGroup, *pboData
///
/// \return boolean - validity of coding data 
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlLed_Data_Get_UnitGroup(CONST_AL uint8 ucEcuSide, tsCtrlled_CodingData *psCodingData)
{
  boolean boCodingDataStatus = TRUE;
  uint8 *pucLogicalUnitsUG = NULL_PTR;
  uint8 *pucIl = NULL_PTR;
  tsCtrlLed_CodHelperUg *puaUg[CTRLLED_CFG_NO_UNIT_GROUPS];
  uint8*(*pfaunAddUnitGroups[])(CONST_AL uint8 ucEcuSide1) =
  {
    CtrlLed_Data_UnitGroup_1 ,
    CtrlLed_Data_UnitGroup_2 ,
    CtrlLed_Data_UnitGroup_3 ,
    CtrlLed_Data_UnitGroup_4 ,
    CtrlLed_Data_UnitGroup_5 ,
    CtrlLed_Data_UnitGroup_6 ,
    CtrlLed_Data_UnitGroup_7 ,
    CtrlLed_Data_UnitGroup_8 ,
    CtrlLed_Data_UnitGroup_9 ,
    CtrlLed_Data_UnitGroup_10,
  };

  //get logical iluminants maped
  pucIl = CtrlLed_Data_Led_LogicalUnitsIl(ucEcuSide);

  for (uint8_fast ucIdx = 0U; ucIdx < CTRLLED_CFG_NO_UNIT_GROUPS; ucIdx++)
  {
    //get data
    pucLogicalUnitsUG = pfaunAddUnitGroups[ucIdx](ucEcuSide);
    //check for null pointer
    if ((pucLogicalUnitsUG == NULL_PTR) || (pucIl == NULL_PTR))
    {
      boCodingDataStatus = FALSE;
      break;
    }
    //store data
    else
    {
      puaUg[ucIdx] = (tsCtrlLed_CodHelperUg*)&pucLogicalUnitsUG[0];

      for (uint8_fast ucJdx = 0U; ucJdx < 13U; ucJdx++)
      {
        psCodingData->asUnitGroups[ucUnitGroupCnt].uUnitGroups.aucUg[ucJdx] = puaUg[ucIdx]->aucUg[ucJdx];
      }
      psCodingData->asUnitGroups[ucUnitGroupCnt].ucName = (CTRLLED_CFG_FIRST_UNIT_GROUP + (uint8)ucIdx);
      
      for (uint8_fast ucIdxIl = 0U; ucIdxIl < CTRLLED_CFG_NO_ILLUMINANTS; ucIdxIl++)
      {
        if (pucIl[ucIdxIl] == psCodingData->asUnitGroups[ucUnitGroupCnt].ucName)
        {
          psCodingData->asUnitGroups[ucUnitGroupCnt].ucIlluminantAssigned = (uint8)ucIdxIl;
          ucUnitGroupCnt++;
          //stop the loop
          break;
        }
      }
      
    }
  }

  return boCodingDataStatus;
}
#endif

//-----------------------------------------------------------------------------
/// \brief CtrlLed_Data_AnimaMap
///
/// \descr
///
/// \param  ucEcuSide, *psCodingData
///
/// \return bool
//-----------------------------------------------------------------------------
STATIC_AL boolean CtrlLed_Data_AnimaMap(CONST_AL uint8 ucEcuSide, tsCtrlled_CodingData *psCodingData)
{
  (void)ucEcuSide;

  boolean boCodingDataStatus = TRUE;
  uint8* punAnimaData = NULL_PTR;
  punAnimaData = CtrlLed_Data_AnimationMapping();

#ifdef UNIT_TEST
  /* -------------------------------------------------- */
  /* Special UT instrumentation to force invalid coding */
  /* -------------------------------------------------- */
  CtrlLed_Special_UT_Instrumentation_Force_InvalidCoding(&punAnimaData, &boCodingDataStatus);
#endif

  if (punAnimaData == NULL_PTR)
  {
    boCodingDataStatus = FALSE;
  }
  else
  {
    for (uint8_fast ucIdx = 0u; ucIdx < CTRLLED_CFG_NR_OF_LOGICAL_UNITS; ucIdx++)
    {
      psCodingData->aucAnimaMap[ucIdx] = punAnimaData[ucIdx];
    }
  }

  return boCodingDataStatus;
}

//-----------------------------------------------------------------------------
/// \brief CtrlLed_CurrentUpdates
///
/// \descr  this function update current used for all bucks (matrix and non-matrix) based
///         on binning class selection
///
/// \param  *psCodingData
///
/// \return coding validity (TRUE = ok)
//-----------------------------------------------------------------------------
boolean CtrlLed_CurrentUpdates(uint8_fast ucIdx, uint8 ucBinningSelect, tsCtrlled_CodingData *psCodingData)
{
  boolean boCodingDataStatus = TRUE;
  
  uint16*(*pfaunAddCurBin[])(uint8 ucBinSel) =
  {
    CtrlLed_Data_Led_CurBinSel_Ch1 ,
    CtrlLed_Data_Led_CurBinSel_Ch2 ,
    CtrlLed_Data_Led_CurBinSel_Ch3 ,
    CtrlLed_Data_Led_CurBinSel_Ch4 ,
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
    CtrlLed_Data_Led_CurBinSel_Ch5 ,
    CtrlLed_Data_Led_CurBinSel_Ch6 ,
    CtrlLed_Data_Led_CurBinSel_Ch7 ,
    CtrlLed_Data_Led_CurBinSel_Ch8 ,
    CtrlLed_Data_Led_CurBinSel_Ch9 ,
    CtrlLed_Data_Led_CurBinSel_Ch10,
    CtrlLed_Data_Led_CurBinSel_Ch11,
    CtrlLed_Data_Led_CurBinSel_Ch12,
#endif
  };

#ifdef UNIT_TEST
  /* -------------------------------------------------- */
  /* Special UT instrumentation to force invalid coding */
  /* -------------------------------------------------- */
  CtrlLed_Special_UT_Instrumentation_Force_InvalidBinnCoding(&pfaunAddCurBin, &boCodingDataStatus);
#endif

  //binning current, ucIdx is the actual channel
  {
    //init with 0 mA
    psCodingData->aunBinningCurrent[ucIdx] = 0U;
    
    //store actual binning sellection
    psCodingData->aucBinningSelection[ucIdx] = ucBinningSelect;
    //check binning selection range (max 6 binning classes)
    if ((ucBinningSelect != CTRLLED_CFG_UNKNOWN_UINT8_VALUE) && (ucBinningSelect < CTRLLED_CFG_MAX_BINNING_CLASSES))
    {
      //check for a vaid address
      if (pfaunAddCurBin[ucIdx](ucBinningSelect) != NULL_PTR)
      {
        //store the coresponding current based on binning selection
        psCodingData->aunBinningCurrent[ucIdx] = *pfaunAddCurBin[ucIdx](ucBinningSelect);
      }
      else
      {
        //here is null pointer and store the coding validity as invalid
        boCodingDataStatus = FALSE;
      }
    }
    else //binning selection is invalid
    {
      psCodingData->aucBinningSelection[ucIdx] = CTRLLED_CFG_BINNING_CLASS_0;

      //check for a vaid address
      if (pfaunAddCurBin[ucIdx](CTRLLED_CFG_BINNING_CLASS_0) != NULL_PTR)
      {
        //store the current from Binning Class 0
        psCodingData->aunBinningCurrent[ucIdx] = *pfaunAddCurBin[ucIdx](CTRLLED_CFG_BINNING_CLASS_0);
      }
      else
      {
        //here is null pointer and store the coding validity as invalid
        boCodingDataStatus = FALSE;
      }
    }

  }

  if (boCodingDataStatus != FALSE)
  {
    (void)Rte_Write_CtrlLed_BinningClass((tsRte_ucBinningSelect*)&psCodingData->aucBinningSelection);
  }

  return boCodingDataStatus;
}

#ifdef UNIT_TEST
//-----------------------------------------------------------------------------
/// \brief CtrlLed_Special_UT_Instrumentation_Force_InvalidCoding
///
/// \descr Special UT instrumentation handler (simulates uninitialized coding)
///
/// \param  uint16** punData, boolean* boCodingValid
///
/// \return void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlLed_Special_UT_Instrumentation_Force_InvalidCoding(uint16** punData, boolean* boCodingValid)
{
  STATIC_UT(boolean, CtrlLed_Force_InvalidCoding, FALSE);

  if (CtrlLed_Force_InvalidCoding == TRUE)
  {
    *punData = NULL_PTR;
    *boCodingValid = FALSE;
  }
  else
  {
    // skip the UT instrumentation
  }

}

//-----------------------------------------------------------------------------
/// \brief  CtrlLed_Special_UT_Instrumentation_Force_InvalidBinnCoding
///
/// \descr Special UT instrumentation handler (simulates uninitialized coding)
///
/// \param  punData
/// \param  boCodingValid
///
/// \return STATIC_AL void
//-----------------------------------------------------------------------------
STATIC_AL void CtrlLed_Special_UT_Instrumentation_Force_InvalidBinnCoding(uint16* punData, boolean* boCodingValid)
{
  STATIC_UT(boolean, CtrlLed_Force_InvalidCoding, FALSE);

  if (CtrlLed_Force_InvalidCoding == TRUE)
  {
    punData = NULL_PTR;
    *boCodingValid = FALSE;
  }
  else
  {
    // skip the UT instrumentation
  }

}
#endif

