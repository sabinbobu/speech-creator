#ifndef __CTRL_LED_DATA_H__
#define __CTRL_LED_DATA_H__

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
/// \file  CtrlLed_Data.h
///
/// \brief header file - coding data for CtrlLed
///
/// \author Caba Ionut-Stefan (F37899C)
///         mailTo:ionut-stefan.caba[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
// defines
//=============================================================================
#include "CtrlLed_Types.h"
#include "CtrlLed_Cfg.h"
#include <Util_Time.h>
#include "CtrlLed_Rte.h"

//=============================================================================
// externals variables
//=============================================================================
extern CONST_AL tNvmPara_CodingArea* CtrlLed_pCodingArea;

//=============================================================================
// prototypes
//=============================================================================
boolean CtrlLed_CodingDataValidation(void);
boolean CtrlLed_CodMap(tsCtrlled_CodingData *psCodingData);
tsCtrlled_CodingData *CtrlLed_pfCodingData(void);
uint8 CtrlLed_GetAndCheckLedName(uint8_fast ucIdx, uint8_fast ucIdxIl);
boolean CtrlLed_CurrentUpdates(uint8_fast ucIdx, uint8 ucBinningSelect, tsCtrlled_CodingData *psCodingData);

//=============================================================================
// inline functions
//=============================================================================

//binning and channel types for diag
LOCAL_INLINE uint8   Cod_LedChannelType(uint8_fast ucIdx)    { return (CtrlLed_pfCodingData()->aucChannelType[ucIdx]); } 
LOCAL_INLINE uint16  Cod_LedBinningCurrent(uint8_fast ucIdx) { return (CtrlLed_pfCodingData()->aunBinningCurrent[ucIdx]); } 
LOCAL_INLINE uint8   Cod_LedName(uint8_fast ucIdx)           { return (CtrlLed_pfCodingData()->ucLedName[ucIdx]); } 
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
LOCAL_INLINE uint8   Cod_IluminantType(uint8_fast ucIdx)     { return (CtrlLed_pfCodingData()->aucLuIl[ucIdx]); } 
#endif


/*MAPPING LIST from coding*/
LOCAL_INLINE uint8* CtrlLed_Data_Get_DriverMap(CONST_AL uint8 ucEcuSide)
{
  return ((ucEcuSide) == ((uint8)eEcu_Left))  ? (uint8*)&CtrlLed_pCodingArea->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping  : \
         ((ucEcuSide) == ((uint8)eEcu_Right)) ? (uint8*)&CtrlLed_pCodingArea->MappingList.LogicalUnitsRightHeadlamp_DriverMapping : (uint8*)NULL_PTR;
}

#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
//MATRIX
LOCAL_INLINE uint8* CtrlLed_Data_Get_PxlMap(CONST_AL uint8 ucEcuSide)
{
  return ((ucEcuSide) == ((uint8)eEcu_Left))  ?  (uint8*)&CtrlLed_pCodingArea->Matrix.Left_MatrixPxl_Mapping : \
         ((ucEcuSide) == ((uint8)eEcu_Right)) ? (uint8*)&CtrlLed_pCodingArea->Matrix.Right_MatrixPxl_Mapping : (uint8*)NULL_PTR;
}

LOCAL_INLINE uint16 CtrlLed_Data_Get_Size_PxlMap(CONST_AL uint8 ucEcuSide)
{
  return ((ucEcuSide) == ((uint8)eEcu_Left))  ? (sizeof(CtrlLed_pCodingArea->Matrix.Left_MatrixPxl_Mapping)) : \
         ((ucEcuSide) == ((uint8)eEcu_Right)) ? (sizeof(CtrlLed_pCodingArea->Matrix.Right_MatrixPxl_Mapping)) : 0u;
}
#endif

/*LED1 from coding*/
LOCAL_INLINE uint8* CtrlLed_Data_Get_ConfigLedName(void) { return (uint8*)&CtrlLed_pCodingArea->Led1.FUSAConfig.FUSA_DRV01_NAMES; }
LOCAL_INLINE uint8 CtrlLed_Data_Get_ConfigLedHssName(void) { return CtrlLed_pCodingArea->Led1.LedConfigDRV13.FUSA_DRV13_NAME; }
//binning
LOCAL_INLINE uint16* CtrlLed_Data_Led_CurBinSel_Ch1(uint8 ucBinSel) { return (uint16*)&CtrlLed_pCodingArea->Led1.LedConfigDRV01.DRV01_CURRENT_BINNING_CLASSES[ucBinSel]; }
LOCAL_INLINE uint16* CtrlLed_Data_Led_CurBinSel_Ch2(uint8 ucBinSel) { return (uint16*)&CtrlLed_pCodingArea->Led1.LedConfigDRV02.DRV02_CURRENT_BINNING_CLASSES[ucBinSel]; }
LOCAL_INLINE uint16* CtrlLed_Data_Led_CurBinSel_Ch3(uint8 ucBinSel) { return (uint16*)&CtrlLed_pCodingArea->Led1.LedConfigDRV03.DRV03_CURRENT_BINNING_CLASSES[ucBinSel]; }
LOCAL_INLINE uint16* CtrlLed_Data_Led_CurBinSel_Ch4(uint8 ucBinSel) { return (uint16*)&CtrlLed_pCodingArea->Led1.LedConfigDRV04.DRV04_CURRENT_BINNING_CLASSES[ucBinSel]; }
#if defined(CFG_VARIANT_FULL) || defined(UNIT_TEST)
LOCAL_INLINE uint16* CtrlLed_Data_Led_CurBinSel_Ch5(uint8 ucBinSel) { return (uint16*)&CtrlLed_pCodingArea->Led1.LedConfigDRV05.DRV05_CURRENT_BINNING_CLASSES[ucBinSel]; }
LOCAL_INLINE uint16* CtrlLed_Data_Led_CurBinSel_Ch6(uint8 ucBinSel) { return (uint16*)&CtrlLed_pCodingArea->Led1.LedConfigDRV06.DRV06_CURRENT_BINNING_CLASSES[ucBinSel]; }
LOCAL_INLINE uint16* CtrlLed_Data_Led_CurBinSel_Ch7(uint8 ucBinSel) { return (uint16*)&CtrlLed_pCodingArea->Led1.LedConfigDRV07.DRV07_CURRENT_BINNING_CLASSES[ucBinSel]; }
LOCAL_INLINE uint16* CtrlLed_Data_Led_CurBinSel_Ch8(uint8 ucBinSel) { return (uint16*)&CtrlLed_pCodingArea->Led1.LedConfigDRV08.DRV08_CURRENT_BINNING_CLASSES[ucBinSel]; }
LOCAL_INLINE uint16* CtrlLed_Data_Led_CurBinSel_Ch9(uint8 ucBinSel) { return (uint16*)&CtrlLed_pCodingArea->Led1.LedConfigDRV09.DRV09_CURRENT_BINNING_CLASSES[ucBinSel]; }
LOCAL_INLINE uint16* CtrlLed_Data_Led_CurBinSel_Ch10(uint8 ucBinSel) { return (uint16*)&CtrlLed_pCodingArea->Led1.LedConfigDRV10.DRV10_CURRENT_BINNING_CLASSES[ucBinSel];}
LOCAL_INLINE uint16* CtrlLed_Data_Led_CurBinSel_Ch11(uint8 ucBinSel) { return (uint16*)&CtrlLed_pCodingArea->Led1.LedConfigDRV11.DRV11_CURRENT_BINNING_CLASSES[ucBinSel];}
LOCAL_INLINE uint16* CtrlLed_Data_Led_CurBinSel_Ch12(uint8 ucBinSel) { return (uint16*)&CtrlLed_pCodingArea->Led1.LedConfigDRV12.DRV12_CURRENT_BINNING_CLASSES[ucBinSel];}
#endif

/*LMMx from coding*/
LOCAL_INLINE uint16* CtrlLed_Data_Led_GammaCfg(void)       { return (uint16*)&CtrlLed_pCodingArea->LmmX.GammaCurveConfig;                    } //has 2 points * 17
LOCAL_INLINE uint8*  CtrlLed_Data_Led_GammaCfgSel(void)    { return (uint8*)&CtrlLed_pCodingArea->LmmX.LMGammaConfig.GAMMA_Curve_Config_LMs; } //selection for gamma points for each iluminant

LOCAL_INLINE uint8*  CtrlLed_Data_Led_LogicalUnitsIl(CONST_AL uint8 ucEcuSide) 
{ 
  return ((ucEcuSide) == ((uint8)eEcu_Left))  ? (uint8*)&CtrlLed_pCodingArea->LmmX.LMUnitConfigLeftHeadlamp : \
    ((ucEcuSide) == ((uint8)eEcu_Right)) ? (uint8*)&CtrlLed_pCodingArea->LmmX.LMUnitConfigRightHeadlamp : (uint8*)NULL_PTR;
} //get logical units for iluminants based on ECU side

//unit groups
LOCAL_INLINE uint8* CtrlLed_Data_UnitGroup_1(CONST_AL uint8 ucEcuSide)
{ return ((ucEcuSide) == ((uint8)eEcu_Left)) ? (uint8*)&CtrlLed_pCodingArea->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110 :
    ((ucEcuSide) == ((uint8)eEcu_Right)) ? (uint8*)&CtrlLed_pCodingArea->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110 : (uint8*)NULL_PTR;
}

LOCAL_INLINE uint8* CtrlLed_Data_UnitGroup_2(CONST_AL uint8 ucEcuSide)
{
  return ((ucEcuSide) == ((uint8)eEcu_Left)) ? (uint8*)&CtrlLed_pCodingArea->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit111 :
    ((ucEcuSide) == ((uint8)eEcu_Right)) ? (uint8*)&CtrlLed_pCodingArea->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit111 : (uint8*)NULL_PTR;
}
LOCAL_INLINE uint8* CtrlLed_Data_UnitGroup_3(CONST_AL uint8 ucEcuSide)
{
  return ((ucEcuSide) == ((uint8)eEcu_Left)) ? (uint8*)&CtrlLed_pCodingArea->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit112 :
    ((ucEcuSide) == ((uint8)eEcu_Right)) ? (uint8*)&CtrlLed_pCodingArea->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit112 : (uint8*)NULL_PTR;
}
LOCAL_INLINE uint8* CtrlLed_Data_UnitGroup_4(CONST_AL uint8 ucEcuSide)
{
  return ((ucEcuSide) == ((uint8)eEcu_Left)) ? (uint8*)&CtrlLed_pCodingArea->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit113 :
    ((ucEcuSide) == ((uint8)eEcu_Right)) ? (uint8*)&CtrlLed_pCodingArea->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit113 : (uint8*)NULL_PTR;
}
LOCAL_INLINE uint8* CtrlLed_Data_UnitGroup_5(CONST_AL uint8 ucEcuSide)
{
  return ((ucEcuSide) == ((uint8)eEcu_Left)) ? (uint8*)&CtrlLed_pCodingArea->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit114 :
    ((ucEcuSide) == ((uint8)eEcu_Right)) ? (uint8*)&CtrlLed_pCodingArea->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit114 : (uint8*)NULL_PTR;
}
LOCAL_INLINE uint8* CtrlLed_Data_UnitGroup_6(CONST_AL uint8 ucEcuSide)
{
  return ((ucEcuSide) == ((uint8)eEcu_Left)) ? (uint8*)&CtrlLed_pCodingArea->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit115 :
    ((ucEcuSide) == ((uint8)eEcu_Right)) ? (uint8*)&CtrlLed_pCodingArea->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit115 : (uint8*)NULL_PTR;
}
LOCAL_INLINE uint8* CtrlLed_Data_UnitGroup_7(CONST_AL uint8 ucEcuSide)
{
  return ((ucEcuSide) == ((uint8)eEcu_Left)) ? (uint8*)&CtrlLed_pCodingArea->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit116 :
    ((ucEcuSide) == ((uint8)eEcu_Right)) ? (uint8*)&CtrlLed_pCodingArea->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit116 : (uint8*)NULL_PTR;
}
LOCAL_INLINE uint8* CtrlLed_Data_UnitGroup_8(CONST_AL uint8 ucEcuSide)
{
  return ((ucEcuSide) == ((uint8)eEcu_Left)) ? (uint8*)&CtrlLed_pCodingArea->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit117 :
    ((ucEcuSide) == ((uint8)eEcu_Right)) ? (uint8*)&CtrlLed_pCodingArea->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit117 : (uint8*)NULL_PTR;
}
LOCAL_INLINE uint8* CtrlLed_Data_UnitGroup_9(CONST_AL uint8 ucEcuSide)
{
  return ((ucEcuSide) == ((uint8)eEcu_Left)) ? (uint8*)&CtrlLed_pCodingArea->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit118 :
    ((ucEcuSide) == ((uint8)eEcu_Right)) ? (uint8*)&CtrlLed_pCodingArea->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit118 : (uint8*)NULL_PTR;
}
LOCAL_INLINE uint8* CtrlLed_Data_UnitGroup_10(CONST_AL uint8 ucEcuSide)
{
  return ((ucEcuSide) == ((uint8)eEcu_Left)) ? (uint8*)&CtrlLed_pCodingArea->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit119 :
    ((ucEcuSide) == ((uint8)eEcu_Right)) ? (uint8*)&CtrlLed_pCodingArea->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit119 : (uint8*)NULL_PTR;
}

//ANIMATION MAPPING
LOCAL_INLINE uint8*  CtrlLed_Data_AnimationMapping(void) { return (uint8*)&CtrlLed_pCodingArea->Animation.AnimationsMapping.ucAnimaUnitMapping[0]; }


#endif // __CTRL_LED_DATA_H__

