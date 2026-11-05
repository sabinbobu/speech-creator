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
/// \file  Test_Ext.c
///
/// \brief Stub functions for access to coding parameters excluded from test
///
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>
#include <string.h>
#include "Test_Ext.h"
#include <CtrlLed_Cfg.h>


//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#define CODM_PARA_GAMMA_PTS_SIZE        17u


//-----------------------------------------------------------------------------
// Stub variables
//-----------------------------------------------------------------------------
tNvmPara_CodingArea*  applicationCodingData;
tNvmPara_CodingArea   InitCoding = { 0u };

//-----------------------------------------------------------------------------
// DATA TYPES TO SIMULATE CODING DATA
//-----------------------------------------------------------------------------

struct tsCtrlLed_Gamma_Points { uint16 GAMMA_1_POINTS[CODM_PARA_GAMMA_PTS_SIZE];
  //uint16 GAMMA_2_POINTS[CODM_PARA_GAMMA_PTS_SIZE];
                              }asGAMMA_POINTS[CTRLLED_CFG_GAMMA_NUMBER] = CTRLLED_GAMMA_POINTS_LIST;


  ///* 1.  LED1 sheet : Binning classes */ 
  // binning currents taken from P64 coding R6
                                                                         /* Class_0 | _1 |   _2 |   _3 |   _4 |   _5 */
  uint16 DRV01_CURRENT_BINNING_CLASSES[CTRLLED_CFG_MAX_BINNING_CLASSES] = {    930u, 780u,  705u,  705u,  705u,  705u };
  uint16 DRV02_CURRENT_BINNING_CLASSES[CTRLLED_CFG_MAX_BINNING_CLASSES] = {    930u, 780u,  705u,  705u,  705u,  705u };
  uint16 DRV03_CURRENT_BINNING_CLASSES[CTRLLED_CFG_MAX_BINNING_CLASSES] = {    930u, 780u,  705u,  705u,  705u,  705u };
  uint16 DRV04_CURRENT_BINNING_CLASSES[CTRLLED_CFG_MAX_BINNING_CLASSES] = {    930u, 780u,  705u,  705u,  705u,  705u };
  uint16 DRV05_CURRENT_BINNING_CLASSES[CTRLLED_CFG_MAX_BINNING_CLASSES] = {    885u, 785u,  730u,  730u,  730u,  730u };
  uint16 DRV06_CURRENT_BINNING_CLASSES[CTRLLED_CFG_MAX_BINNING_CLASSES] = {    680u, 590u,  535u,  535u,  535u,  535u };
  uint16 DRV07_CURRENT_BINNING_CLASSES[CTRLLED_CFG_MAX_BINNING_CLASSES] = {    885u, 785u,  730u,  730u,  730u,  730u };
  uint16 DRV08_CURRENT_BINNING_CLASSES[CTRLLED_CFG_MAX_BINNING_CLASSES] = {    210u, 210u,  210u,  210u,  210u,  210u };
  uint16 DRV09_CURRENT_BINNING_CLASSES[CTRLLED_CFG_MAX_BINNING_CLASSES] = {    210u, 210u,  210u,  210u,  210u,  210u };
  uint16 DRV10_CURRENT_BINNING_CLASSES[CTRLLED_CFG_MAX_BINNING_CLASSES] = {    210u, 210u,  210u,  210u,  210u,  210u };
  uint16 DRV11_CURRENT_BINNING_CLASSES[CTRLLED_CFG_MAX_BINNING_CLASSES] = {    290u, 290u,  290u,  290u,  290u,  290u };
  uint16 DRV12_CURRENT_BINNING_CLASSES[CTRLLED_CFG_MAX_BINNING_CLASSES] = {    680u, 590u,  535u,  535u,  535u,  535u };

//-----------------------------------------------------------------------------
// Function Prototype
//-----------------------------------------------------------------------------
STATIC_AL void Mt_MappingListLeft(void);
STATIC_AL void Mt_MappingListRight(void);
STATIC_AL void Mt_MatrixSheetLeft(void);
STATIC_AL void Mt_MatrixSheetRight(void);
STATIC_AL void Mt_CodingLeftSide(void);
STATIC_AL void Mt_CodingRightSide(void);
STATIC_AL void CtrlLed_CreateAnimationMapping(void);

//-----------------------------------------------------------------------------
// Helper Functions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
///  Description
///    - Function for testing purposes to simulate the actual behavior using
///      valid coding data (as in AL- coding tool) for Left ECU Side.
///      Values are taken from IFD-AL coding tool, Mapping List Sheet. 
///      Assign to each logical unit (0...102 Lu) a :
///                 - LED_DRV Id (0..11 Leds)
///                 - LMM_Id (0...7 Lmms)
///                 - Switch_Id (0...12 Pxls)
//-----------------------------------------------------------------------------
STATIC_AL void Mt_MappingListLeft(void)
{
  /* Mapping - List */
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit1  = DRV_01;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit1 = LMM_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit1 = PXL_NOTUSED;

  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit2  = DRV_02;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit2 = LMM_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit2 = PXL_NOTUSED;

  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit3  = DRV_03;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit3 = LMM_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit3 = PXL_NOTUSED;

  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit4  = DRV_04;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit4 = LMM_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit4 = PXL_NOTUSED;

  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit5  = DRV_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit5 = LMM_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit5 = PXL_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit6  = DRV_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit6 = LMM_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit6 = PXL_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit7  = DRV_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit7 = LMM_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit7 = PXL_NOTUSED;

  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit8  = DRV_08;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit8 = LMM_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit8 = PXL_NOTUSED;

  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit9   = DRV_09;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit9  = LMM_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit9  = PXL_NOTUSED;

  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit10  = DRV_10;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit10 = LMM_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit10 = PXL_NOTUSED;

  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit11  = DRV_11;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit11 = LMM_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit11 = PXL_NOTUSED;

  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit12  = HSS3;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit12 = LMM_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit12 = PXL_NOTUSED;

  /*LMM 1 */
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit13  = DRV_05;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit13 = LMM_1;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit13 = PXL_1;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit14  = DRV_05;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit14 = LMM_1;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit14 = PXL_2;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit15  = DRV_05;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit15 = LMM_1;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit15 = PXL_3;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit16  = DRV_05;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit16 = LMM_1;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit16 = PXL_4;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit17  = DRV_05;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit17 = LMM_1;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit17 = PXL_5;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit18  = DRV_05;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit18 = LMM_1;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit18 = PXL_6;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit19  = DRV_05;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit19 = LMM_1;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit19 = PXL_7;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit20  = DRV_05;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit20 = LMM_1;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit20 = PXL_8;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit21  = DRV_05;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit21 = LMM_1;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit21 = PXL_9;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit22  = DRV_05;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit22 = LMM_1;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit22 = PXL_10;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit23  = DRV_05;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit23 = LMM_1;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit23 = PXL_11;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit24  = DRV_05;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit24 = LMM_1;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit24 = PXL_12;
  /*LMM 3 */
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit25 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit25 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit25 = PXL_1;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit26 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit26 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit26 = PXL_2;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit27 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit27 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit27 = PXL_3;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit28 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit28 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit28 = PXL_4;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit29 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit29 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit29 = PXL_5;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit30 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit30 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit30 = PXL_6;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit31 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit31 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit31 = PXL_7;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit32 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit32 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit32 = PXL_8;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit33 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit33 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit33 = PXL_9;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit34 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit34 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit34 = PXL_10;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit35 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit35 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit35 = PXL_11;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit36 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit36 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit36 = PXL_12;

    /*LMM 5 */
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit37  = DRV_06;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit37 = LMM_5;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit37 = PXL_1;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit38  = DRV_06;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit38 = LMM_5;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit38 = PXL_2;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit39  = DRV_06;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit39 = LMM_5;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit39 = PXL_3;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit40  = DRV_06;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit40 = LMM_5;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit40 = PXL_4;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit41  = DRV_06;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit41 = LMM_5;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit41 = PXL_5;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit42  = DRV_06;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit42 = LMM_5;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit42 = PXL_6;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit43  = DRV_06;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit43 = LMM_5;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit43 = PXL_7;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit44  = DRV_06;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit44 = LMM_5;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit44 = PXL_8;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit45  = DRV_06;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit45 = LMM_5;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit45 = PXL_9;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit46  = DRV_06;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit46 = LMM_5;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit46 = PXL_10;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit47  = DRV_06;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit47 = LMM_5;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit47 = PXL_11;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit48  = DRV_06;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit48 = LMM_5;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit48 = PXL_12;

  /*LMM 7 */
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit49 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit49 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit49 = PXL_1;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit50 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit50 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit50 = PXL_2;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit51 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit51 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit51 = PXL_3;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit52 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit52 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit52 = PXL_4;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit53 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit53 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit53 = PXL_5;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit54 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit54 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit54 = PXL_6;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit55 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit55 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit55 = PXL_7;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit56 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit56 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit56 = PXL_8;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit57 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit57 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit57 = PXL_9;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit58 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit58 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit58 = PXL_10;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit59 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit59 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit59 = PXL_11;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit60 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit60 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit60 = PXL_12;

   //Unit Group Selection 
  /* UnitGroup110 -> Logical Units 13 - 24, 49 - 60 */
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Fbit   = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit13 = 1u; 
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit14 = 1u; 
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit15 = 1u; 
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit16 = 1u; 
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit17 = 1u; 
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit18 = 1u; 
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit19 = 1u; 
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit20 = 1u; 
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit21 = 1u; 
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit22 = 1u; 
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit23 = 1u; 
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit24 = 1u;

  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit49 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit50 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit51 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit52 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit53 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit54 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit55 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit56 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit57 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit58 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit59 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit110.UnitGroup110_Left_Unit60 = 1u;


  /* UnitGroup111 -> Logical Units 25 - 36 */
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit111.UnitGroup111_Left_Fbit   = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit111.UnitGroup111_Left_Unit25 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit111.UnitGroup111_Left_Unit26 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit111.UnitGroup111_Left_Unit27 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit111.UnitGroup111_Left_Unit28 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit111.UnitGroup111_Left_Unit29 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit111.UnitGroup111_Left_Unit30 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit111.UnitGroup111_Left_Unit31 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit111.UnitGroup111_Left_Unit32 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit111.UnitGroup111_Left_Unit33 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit111.UnitGroup111_Left_Unit34 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit111.UnitGroup111_Left_Unit35 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit111.UnitGroup111_Left_Unit36 = 1u;

  /* UnitGroup112 -> Logical Units 37 - 48 */
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit112.UnitGroup112_Left_Fbit   = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit112.UnitGroup112_Left_Unit37 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit112.UnitGroup112_Left_Unit38 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit112.UnitGroup112_Left_Unit39 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit112.UnitGroup112_Left_Unit40 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit112.UnitGroup112_Left_Unit41 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit112.UnitGroup112_Left_Unit42 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit112.UnitGroup112_Left_Unit43 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit112.UnitGroup112_Left_Unit44 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit112.UnitGroup112_Left_Unit45 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit112.UnitGroup112_Left_Unit46 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit112.UnitGroup112_Left_Unit47 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit112.UnitGroup112_Left_Unit48 = 1u;

  /* UnitGroup113 */
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit113.UnitGroup113_Left_Fbit = 0u;

  /* UnitGroup114 */
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit114.UnitGroup114_Left_Fbit = 0u;

  /* UnitGroup115 */
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit115.UnitGroup115_Left_Fbit = 0u;

  /* UnitGroup116 */
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit116.UnitGroup116_Left_Fbit = 0u;

  /* UnitGroup117 */
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit117.UnitGroup117_Left_Fbit = 0u;

  /* UnitGroup118 */
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit118.UnitGroup118_Left_Fbit = 0u;

  /* UnitGroup119 */
  applicationCodingData->UnitGroups.LogicalUnitsLeftHeadlamp_GroupUnit119.UnitGroup119_Left_Fbit = 0u;
}

//-----------------------------------------------------------------------------
///  Description
///    - Function for testing purposes to simulate the actual behavior using
///      valid coding data (as in AL- coding tool) for Right ECU Side.
///      Values are taken from IFD-AL coding tool, Mapping List Sheet. 
///      Assign to each logical unit (0...102 Lu) a :
///                 - LED_DRV Id (0..11 Leds)
///                 - LMM_Id (0...7 Lmms)
///                 - Switch_Id (0...12 Pxls)
//-----------------------------------------------------------------------------
STATIC_AL void Mt_MappingListRight(void)
{
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit2 = DRV_02;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit2 = LMM_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit2 = PXL_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit4 = DRV_04;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit4 = LMM_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit4 = PXL_NOTUSED;

  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit7 = DRV_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit7 = LMM_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit7 = PXL_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit8 = DRV_08;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit8 = LMM_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit8 = PXL_NOTUSED;

  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit10 = DRV_10;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit10 = LMM_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit10 = PXL_NOTUSED;

  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit12 = HSS3;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit12 = LMM_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit12 = PXL_NOTUSED;

  /*LMM 3 */
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit25 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit25 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit25 = PXL_1;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit26 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit26 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit26 = PXL_2;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit27 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit27 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit27 = PXL_3;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit28 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit28 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit28 = PXL_4;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit29 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit29 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit29 = PXL_5;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit30 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit30 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit30 = PXL_6;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit31 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit31 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit31 = PXL_7;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit32 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit32 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit32 = PXL_8;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit33 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit33 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit33 = PXL_9;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit34 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit34 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit34 = PXL_10;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit35 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit35 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit35 = PXL_11;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit36 = DRV_07;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit36 = LMM_3;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit36 = PXL_12;

  /*LMM 7 */
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit49 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit49 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit49 = PXL_1;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit50 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit50 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit50 = PXL_2;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit51 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit51 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit51 = PXL_3;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit52 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit52 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit52 = PXL_4;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit53 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit53 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit53 = PXL_5;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit54 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit54 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit54 = PXL_6;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit55 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit55 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit55 = PXL_7;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit56 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit56 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit56 = PXL_8;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit57 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit57 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit57 = PXL_9;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit58 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit58 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit58 = PXL_10;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit59 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit59 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit59 = PXL_11;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Drv_Right_Unit60 = DRV_12;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.Lmms_Right_Unit60 = LMM_7;
  applicationCodingData->MappingList.LogicalUnitsRightHeadlamp_DriverMapping.SwNr_Right_Unit60 = PXL_12;


  //Unit Group Selection 
  /* UnitGroup110 -> Logical Units 13 - 24, 49 - 60 */
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Fbit   = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit13 = 1u; 
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit14 = 1u; 
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit15 = 1u; 
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit16 = 1u; 
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit17 = 1u; 
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit18 = 1u; 
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit19 = 1u; 
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit20 = 1u; 
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit21 = 1u; 
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit22 = 1u; 
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit23 = 1u; 
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit24 = 1u;

  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit49 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit50 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit51 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit52 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit53 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit54 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit55 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit56 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit57 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit58 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit59 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit110.UnitGroup110_Right_Unit60 = 1u;


  /* UnitGroup111 -> Logical Units 25 - 36 */
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit111.UnitGroup111_Right_Fbit   = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit111.UnitGroup111_Right_Unit25 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit111.UnitGroup111_Right_Unit26 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit111.UnitGroup111_Right_Unit27 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit111.UnitGroup111_Right_Unit28 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit111.UnitGroup111_Right_Unit29 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit111.UnitGroup111_Right_Unit30 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit111.UnitGroup111_Right_Unit31 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit111.UnitGroup111_Right_Unit32 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit111.UnitGroup111_Right_Unit33 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit111.UnitGroup111_Right_Unit34 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit111.UnitGroup111_Right_Unit35 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit111.UnitGroup111_Right_Unit36 = 1u;

  /* UnitGroup112 -> Logical Units 37 - 48 */
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit112.UnitGroup112_Right_Fbit   = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit112.UnitGroup112_Right_Unit37 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit112.UnitGroup112_Right_Unit38 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit112.UnitGroup112_Right_Unit39 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit112.UnitGroup112_Right_Unit40 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit112.UnitGroup112_Right_Unit41 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit112.UnitGroup112_Right_Unit42 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit112.UnitGroup112_Right_Unit43 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit112.UnitGroup112_Right_Unit44 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit112.UnitGroup112_Right_Unit45 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit112.UnitGroup112_Right_Unit46 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit112.UnitGroup112_Right_Unit47 = 1u;
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit112.UnitGroup112_Right_Unit48 = 1u;

  /* UnitGroup113 */
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit113.UnitGroup113_Right_Fbit = 0u;

  /* UnitGroup114 */
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit114.UnitGroup114_Right_Fbit = 0u;

  /* UnitGroup115 */
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit115.UnitGroup115_Right_Fbit = 0u;

  /* UnitGroup116 */
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit116.UnitGroup116_Right_Fbit = 0u;

  /* UnitGroup117 */
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit117.UnitGroup117_Right_Fbit = 0u;

  /* UnitGroup118 */
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit118.UnitGroup118_Right_Fbit = 0u;

  /* UnitGroup119 */
  applicationCodingData->UnitGroups.LogicalUnitsRightHeadlamp_GroupUnit119.UnitGroup119_Right_Fbit = 0u;

}

//-----------------------------------------------------------------------------
///  Description
///    - Function for testing purposes to simulate the actual behavior using
///      valid coding data (as in AL- coding tool) for Left ECU Side.
///      Values are taken from IFD-AL coding tool, Matrix Sheet. Fill the matrix
///      segments ( 3 rows * 30 pxls) with corresponding logical units.
///
//-----------------------------------------------------------------------------
STATIC_AL void Mt_MatrixSheetLeft(void)
  {
    uint8 ucSeg64 = 12u; //logical Unit
    uint8 ucSeg76 = 48u; //logical Unit
    for (uint8 ucRow = 0u; ucRow < 3u; ucRow++)
    {
      for (uint8 ucCol = 0u; ucCol < 30u; ucCol++)
      {
        if ((ucRow == 2u) && (ucCol >= 3u && ucCol < 15u))
        {
          //fill first half of FLAT row
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][ucCol] = ucSeg64++;
        }
        else if ((ucRow == 2u) && (ucCol >= 15u && ucCol < 27u))
        {
          //fill second half of FLAT row
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][ucCol] = ucSeg76++;
        }
        else if (ucRow == 0u)
        { // High Beam Row
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][6]  = 36u;
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][7]  = 33u;
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][8]  = 32u;
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][9]  = 29u;
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][10] = 28u;
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][11] = 25u;
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][18] = 48u;
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][19] = 45u;
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][20] = 44u;
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][21] = 41u;
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][22] = 40u;
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][23] = 37u;
        }
        else if (ucRow == 1u)
        {
          // Kink Row
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][6]  = 35u;
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][7]  = 34u;
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][8]  = 31u;
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][9]  = 30u;
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][10] = 27u;
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][11] = 26u;
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][18] = 47u;
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][19] = 46u;
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][20] = 43u;
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][21] = 42u;
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][22] = 39u;
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][23] = 38u;
        }
        else
        {
          applicationCodingData->Matrix.Left_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][ucCol] = 0x00u;
        }
      }
    }
  }

  //-----------------------------------------------------------------------------
///  Description
///    - Function for testing purposes to simulate the actual behavior using
///      valid coding data (as in AL- coding tool) for Right ECU Side.
///      Values are taken from IFD-AL coding tool, Matrix Sheet. Fill the matrix
///      segments ( 3 rows * 30 pxls) with corresponding logical units.
///
//-----------------------------------------------------------------------------
STATIC_AL void Mt_MatrixSheetRight(void)
  {
    uint8 ucSeg64 = 12u; //logical Unit
    uint8 ucSeg76 = 48u; //logical Unit
    for (uint8 ucRow = 0u; ucRow < 3u; ucRow++)
    {
      for (uint8 ucCol = 0u; ucCol < 30u; ucCol++)
      {
        if ((ucRow == 2u) && (ucCol >= 3u && ucCol < 15u))
        {
          //fill first half of FLAT row
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][ucCol] = ucSeg64++;
        }
        else if ((ucRow == 2u) && (ucCol >= 15u && ucCol < 27u))
        {
          //fill second half of FLAT row
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][ucCol] = ucSeg76++;
        }
        else if (ucRow == 0u)
        { // High Beam Row
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][6]  = 36u;
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][7]  = 33u;
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][8]  = 32u;
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][9]  = 29u;
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][10] = 28u;
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][11] = 25u;
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][18] = 48u;
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][19] = 45u;
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][20] = 44u;
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][21] = 41u;
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][22] = 40u;
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][23] = 37u;
        }
        else if (ucRow == 1u)
        {
          // Kink Row
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][6]  = 35u;
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][7]  = 34u;
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][8]  = 31u;
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][9]  = 30u;
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][10] = 27u;
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][11] = 26u;
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][18] = 47u;
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][19] = 46u;
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][20] = 43u;
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][21] = 42u;
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][22] = 39u;
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][23] = 38u;
        }
        else
        {
          applicationCodingData->Matrix.Right_MatrixPxl_Mapping.anLIGHT_INTENS_LFT[ucRow][ucCol] = 0x00u;
        }
      }
    }
  }

//-----------------------------------------------------------------------------
///  Description
///    - Function for testing purposes to simulate the actual behavior using
///      valid coding data (as in AL- coding tool) for Left ECU Side.
///      Contains the coding sheets used by CtrlLed filled with valid data.
///
//-----------------------------------------------------------------------------
STATIC_AL void Mt_CodingLeftSide(void)
  {
    /* Mapping List */
    Mt_MappingListLeft();

    /* Matrix Sheet*/
    Mt_MatrixSheetLeft();

    //memcpy(&CtrlLed_pCodingArea, &applicationCodingData, sizeof(CtrlLed_pCodingArea));
}

//-----------------------------------------------------------------------------
///  Description
///    - Function for testing purposes to simulate the actual behavior using
///      valid coding data (as in AL- coding tool) for Right ECU Side.
///      Contains the coding sheets used by CtrlLed filled with valid data.
///
//-----------------------------------------------------------------------------
STATIC_AL void Mt_CodingRightSide()
  {
    /* Mapping - List */
    Mt_MappingListRight();

    /* Matrix Sheet*/
    Mt_MatrixSheetRight();

   // memcpy(&CtrlLed_pCodingArea, &applicationCodingData, sizeof(CtrlLed_pCodingArea));

  }

//-----------------------------------------------------------------------------
///  Description
///    - Function for testing purposes to simulate the actual behavior using
///      valid coding data (as in AL- coding tool)
///      Each mounted side has its own parameters and values may differ.
///
//-----------------------------------------------------------------------------
void Mt_InitializeCodingData(teEcuSide eEcuSide)
{

    applicationCodingData = &InitCoding;

    switch (eEcuSide)
    {
    case Mount_Left:   Mt_CodingLeftSide();    break;
    case Mount_Right:  Mt_CodingRightSide();   break;
    default:          /* undefined*/          break;
    }
  }

STATIC_AL void CtrlLed_CreateAnimationMapping(void)
{
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[0]   = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[1]   = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[2]   = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[3]   = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[4]   = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[5]   = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[6]   = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[7]   = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[8]   = 0u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[9]   = 1u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[10]  = 2u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[11]  = 34u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[12]  = 10u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[13]  = 11u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[14]  = 12u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[15]  = 13u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[16]  = 14u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[17]  = 15u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[18]  = 16u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[19]  = 17u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[20]  = 18u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[21]  = 19u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[22]  = 20u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[23]  = 21u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[24]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[25]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[26]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[27]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[28]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[29]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[30]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[31]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[32]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[33]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[34]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[35]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[36]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[37]  = 4u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[38]  = 5u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[39]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[40]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[41]  = 6u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[42]  = 7u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[43]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[44]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[45]  = 8u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[46]  = 9u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[47]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[48]  = 22u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[49]  = 23u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[50]  = 24u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[51]  = 25u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[52]  = 26u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[53]  = 27u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[54]  = 28u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[55]  = 29u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[56]  = 30u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[57]  = 31u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[58]  = 32u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[59]  = 38u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[60]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[61]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[62]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[63]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[64]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[65]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[66]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[67]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[68]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[69]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[70]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[71]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[72]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[73]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[74]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[75]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[76]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[77]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[78]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[79]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[80]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[81]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[82]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[83]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[84]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[85]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[86]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[87]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[88]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[89]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[90]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[91]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[92]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[93]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[94]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[95]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[96]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[97]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[98]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[99]  = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[100] = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[101] = 255u;
   applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[102] = 255u;

}
//-----------------------------------------------------------------------------
///  Description
///    - Function for testing purposes to populate the coding parameters
///      as in the actual AL-Coding file used by the software
///      Coding sheets covered:
///             - Led1   : binning class currents
///             - Lmmx   : illuminants configuration, gamma config.
///
//-----------------------------------------------------------------------------
void CtrlLed_CreateCodingData_FULLVariant(void)
{
  applicationCodingData = &InitCoding;

  /* Assign valid values for CtrlLed_Data.h*/
  /* 1.  LED1 sheet : Binning classes */

  for (uint8 ucBinningClass = 0u; ucBinningClass < CTRLLED_CFG_MAX_BINNING_CLASSES; ucBinningClass++)
  {
      applicationCodingData->Led1.LedConfigDRV01.DRV01_CURRENT_BINNING_CLASSES[ucBinningClass] = DRV01_CURRENT_BINNING_CLASSES[ucBinningClass];
      applicationCodingData->Led1.LedConfigDRV02.DRV02_CURRENT_BINNING_CLASSES[ucBinningClass] = DRV02_CURRENT_BINNING_CLASSES[ucBinningClass];
      applicationCodingData->Led1.LedConfigDRV03.DRV03_CURRENT_BINNING_CLASSES[ucBinningClass] = DRV03_CURRENT_BINNING_CLASSES[ucBinningClass];
      applicationCodingData->Led1.LedConfigDRV04.DRV04_CURRENT_BINNING_CLASSES[ucBinningClass] = DRV04_CURRENT_BINNING_CLASSES[ucBinningClass];
      applicationCodingData->Led1.LedConfigDRV05.DRV05_CURRENT_BINNING_CLASSES[ucBinningClass] = DRV05_CURRENT_BINNING_CLASSES[ucBinningClass];
      applicationCodingData->Led1.LedConfigDRV06.DRV06_CURRENT_BINNING_CLASSES[ucBinningClass] = DRV06_CURRENT_BINNING_CLASSES[ucBinningClass];
      applicationCodingData->Led1.LedConfigDRV07.DRV07_CURRENT_BINNING_CLASSES[ucBinningClass] = DRV07_CURRENT_BINNING_CLASSES[ucBinningClass];
      applicationCodingData->Led1.LedConfigDRV08.DRV08_CURRENT_BINNING_CLASSES[ucBinningClass] = DRV08_CURRENT_BINNING_CLASSES[ucBinningClass];
      applicationCodingData->Led1.LedConfigDRV09.DRV09_CURRENT_BINNING_CLASSES[ucBinningClass] = DRV09_CURRENT_BINNING_CLASSES[ucBinningClass];
      applicationCodingData->Led1.LedConfigDRV10.DRV10_CURRENT_BINNING_CLASSES[ucBinningClass] = DRV10_CURRENT_BINNING_CLASSES[ucBinningClass];
      applicationCodingData->Led1.LedConfigDRV11.DRV11_CURRENT_BINNING_CLASSES[ucBinningClass] = DRV11_CURRENT_BINNING_CLASSES[ucBinningClass];
      applicationCodingData->Led1.LedConfigDRV12.DRV12_CURRENT_BINNING_CLASSES[ucBinningClass] = DRV12_CURRENT_BINNING_CLASSES[ucBinningClass];
  
    //debug reasons
    //printf("\n applicationCodingData->Led1.LedConfigDRV12.DRV12_CURRENT_BINNING_CLASSES[%d] = %d", ucBinningClass, applicationCodingData->Led1.LedConfigDRV12.DRV12_CURRENT_BINNING_CLASSES[ucBinningClass]);
  }


  /* 2. LmmX Sheet : Logical Units Configured for Illuminants of Left and Right Headlamp */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[0]  =    1u;  /* Illuminant 1 (LB[Safety])  -  LED_DRIVER_01 */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[1]  =    2u;  /* Illuminant 2 (LB[Spot DBL])-  LED_DRIVER_02 */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[2]  =    3u;  /* Illuminant 3 (LB[MW])      -  LED_DRIVER_03 */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[3]  =    4u;  /* Illuminant 4 (LB[SBL])     -  LED_DRIVER_04 */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[4]  =    8u;  /* Illuminant 5 (LB[DRL 1])   -  LED_DRIVER_08 */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[5]  =    9u;  /* Illuminant 6 (LB[DRL 2])   -  LED_DRIVER_09 */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[6]  =   10u;  /* Illuminant 7 (LB[DRL 3])   -  LED_DRIVER_10 */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[7]  =   11u;  /* Illuminant 8 (TI[TI])      -  LED_DRIVER_11 */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[8]  = 0xFFu;  /* Illuminant 9 (LB/HB[FLAT]) -  none          */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[9]  = 0xFFu;  /* Illuminant 10 (none[none]) -  none          */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[10] = 0xFFu;  /* Illuminant 11 (none[none]) -  none          */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[11] = 0xFFu;  /* Illuminant 12 (none[none]) -  none          */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[12] =  HSS3;  /* Illuminant 13 HSS3 - on logical unit 12     */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[13] =  110u;  /* Illuminant 14 FLAT[FLAT]   -  MATRIX: LED_DRIVER_05, LED_DRIVER_12 */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[14] =  111u;  /* Illuminant 15 KINK[KINK]   -  MATRIX: LED_DRIVER_07                */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[15] =  112u;  /* Illuminant 16 HB[HB]       -  MATRIX: LED_DRIVER_06                */

  memcpy(&applicationCodingData->LmmX.LMUnitConfigRightHeadlamp.LSM_Illum_Assigned_Units_Right_LMs, &applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs, sizeof(applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs));


 /* 3. LmmX Sheet : Gamma Curve Config */
for (uint8 ucGammaPoint = 0u; ucGammaPoint < CODM_PARA_GAMMA_PTS_SIZE; ucGammaPoint++)
  {
     applicationCodingData->LmmX.GammaCurveConfig.GAMMA_1_POINTS[ucGammaPoint] =  asGAMMA_POINTS[0].GAMMA_1_POINTS[ucGammaPoint];
     applicationCodingData->LmmX.GammaCurveConfig.GAMMA_2_POINTS[ucGammaPoint] =  asGAMMA_POINTS[0].GAMMA_1_POINTS[ucGammaPoint];
     //debug reasons
    // printf("\n applicationCodingData->LmmX.GammaCurveConfig.GAMMA_1_POINTS[%d] = %d", ucGammaPoint, applicationCodingData->LmmX.GammaCurveConfig.GAMMA_1_POINTS[ucGammaPoint]);
     //printf("\n applicationCodingData->LmmX.GammaCurveConfig.GAMMA_2_POINTS[%d] = %d", ucGammaPoint, applicationCodingData->LmmX.GammaCurveConfig.GAMMA_2_POINTS[ucGammaPoint]);
  }

  //Gamma Curve LUT selection ( LUT 1 / LUT2 / 0xFF (none) )
  applicationCodingData->LmmX.LMGammaConfig.GAMMA_Curve_Config_LMs[0]  = 1u;
  applicationCodingData->LmmX.LMGammaConfig.GAMMA_Curve_Config_LMs[1]  = 1u;
  applicationCodingData->LmmX.LMGammaConfig.GAMMA_Curve_Config_LMs[2]  = 1u;
  applicationCodingData->LmmX.LMGammaConfig.GAMMA_Curve_Config_LMs[3]  = 1u;
  applicationCodingData->LmmX.LMGammaConfig.GAMMA_Curve_Config_LMs[4]  = 1u;
  applicationCodingData->LmmX.LMGammaConfig.GAMMA_Curve_Config_LMs[5]  = 1u;
  applicationCodingData->LmmX.LMGammaConfig.GAMMA_Curve_Config_LMs[6]  = 1u;
  applicationCodingData->LmmX.LMGammaConfig.GAMMA_Curve_Config_LMs[7]  = 1u;
  applicationCodingData->LmmX.LMGammaConfig.GAMMA_Curve_Config_LMs[8]  = 0xFFu;
  applicationCodingData->LmmX.LMGammaConfig.GAMMA_Curve_Config_LMs[9]  = 0xFFu;
  applicationCodingData->LmmX.LMGammaConfig.GAMMA_Curve_Config_LMs[10] = 0xFFu;
  applicationCodingData->LmmX.LMGammaConfig.GAMMA_Curve_Config_LMs[11] = 0xFFu;
  applicationCodingData->LmmX.LMGammaConfig.GAMMA_Curve_Config_LMs[12] = 0xFFu;
  applicationCodingData->LmmX.LMGammaConfig.GAMMA_Curve_Config_LMs[13] = 1u;
  applicationCodingData->LmmX.LMGammaConfig.GAMMA_Curve_Config_LMs[14] = 1u;
  applicationCodingData->LmmX.LMGammaConfig.GAMMA_Curve_Config_LMs[15] = 1u;
  

  /* IFD - channel name */
 applicationCodingData->Led1.FUSAConfig.FUSA_DRV01_NAMES[0]  = 2u;   /* LB_FUSA */
 applicationCodingData->Led1.FUSAConfig.FUSA_DRV01_NAMES[1]  = 1u;   /* LB - Low Beam */
 applicationCodingData->Led1.FUSAConfig.FUSA_DRV01_NAMES[2]  = 1u;   /* LB - Low Beam */
 applicationCodingData->Led1.FUSAConfig.FUSA_DRV01_NAMES[3]  = 13u;  /* CL - Cornering Light */
 applicationCodingData->Led1.FUSAConfig.FUSA_DRV01_NAMES[4]  = 14u;  /* PXL - matrix channel */
 applicationCodingData->Led1.FUSAConfig.FUSA_DRV01_NAMES[5]  = 14u;  /* PXL - matrix channel */
 applicationCodingData->Led1.FUSAConfig.FUSA_DRV01_NAMES[6]  = 14u;  /* PXL - matrix channel */
 applicationCodingData->Led1.FUSAConfig.FUSA_DRV01_NAMES[7]  = 4u;   /* DRL/POS - Daytime Running Light/ Position Light */
 applicationCodingData->Led1.FUSAConfig.FUSA_DRV01_NAMES[8]  = 4u;   /* DRL/POS - Daytime Running Light/ Position Light */
 applicationCodingData->Led1.FUSAConfig.FUSA_DRV01_NAMES[9]  = 4u;   /* DRL/POS - Daytime Running Light/ Position Light */
 applicationCodingData->Led1.FUSAConfig.FUSA_DRV01_NAMES[10] = 6u;   /* TI - Turn Indicator */
 applicationCodingData->Led1.FUSAConfig.FUSA_DRV01_NAMES[11] = 14u;  /* PXL - matrix channel */
 applicationCodingData->Led1.LedConfigDRV13.FUSA_DRV13_NAME  = HSS3;  //OUTPUT OFF = 0; SM=8; RGB=9; consider geenral fo UT as Hss3

 //create animation mapping from Coding Tool - Animation sheet 
  CtrlLed_CreateAnimationMapping();

 // copy the coding data in the actual working variable from CtrlLed module
  memcpy(&CtrlLed_pCodingArea, &applicationCodingData, sizeof(CtrlLed_pCodingArea));

}

//-----------------------------------------------------------------------------
///  Description
///    - Function for testing purposes to populate the internal handling structure
///      with remapped coding parameters as in the actual AL-Coding file used by the software
///
//-----------------------------------------------------------------------------
void Mt_InternalCodingMapping(void)
{
  /*  ---------- Internal Structure     tsCtrlled_CodingData  CtrlLed_sCodingData; -------  */

  // 1)  uint16 aunChannelIlluminant[CTRLLED_CFG_NO_ILLUMINANTS]; //used on bits
  // 2)  uint8 aucChannelType[CTRLLED_CFG_LED_CHANNELS_NR];
  // 3)  uint16 aunBinningCurrent[CTRLLED_CFG_LED_CHANNELS_NR];
  // 4)  tsCtrlLed_Gamma sGamma;
  // 5)  uint8 ucLedName[CTRLLED_CFG_MAX_BUCK_DRV];
  //   #if (CTRLLED_CFG_ALLOW_ANIMATION)
  // 6)  uint8 ucLogicalUnitIl[CTRLLED_CFG_NO_ILLUMINANTS];
  //   #endif
  //   #if defined(CFG_VARIANT_FULL) || (UNIT_TEST)
  // 7)  uint8 aucLmmSwitchNo[CTRLLED_CFG_MAX_NR_OF_PXL];
  // 8)  uint8 aucLuIl[CTRLLED_CFG_NR_OF_LOGICAL_UNITS];
  // 9)  boolean aboIlMtxType[CTRLLED_CFG_NO_ILLUMINANTS];
  //   #endif


  /* ------------- 1) Illuminant - assigned LED channel on bit position ------ */
  /* ------------------------------------------------------------------------- */
  CtrlLed_sCodingData.aunChannelIlluminant[0]  = 1u;
  CtrlLed_sCodingData.aunChannelIlluminant[1]  = 2u;
  CtrlLed_sCodingData.aunChannelIlluminant[2]  = 4u;
  CtrlLed_sCodingData.aunChannelIlluminant[3]  = 8u;
  CtrlLed_sCodingData.aunChannelIlluminant[4]  = 128u;
  CtrlLed_sCodingData.aunChannelIlluminant[5]  = 256u;
  CtrlLed_sCodingData.aunChannelIlluminant[6]  = 512u;
  CtrlLed_sCodingData.aunChannelIlluminant[7]  = 1024u;
  CtrlLed_sCodingData.aunChannelIlluminant[8]  = 0u;
  CtrlLed_sCodingData.aunChannelIlluminant[9]  = 0u;
  CtrlLed_sCodingData.aunChannelIlluminant[10] = 0u;
  CtrlLed_sCodingData.aunChannelIlluminant[11] = 4096u;  // HSS3
  CtrlLed_sCodingData.aunChannelIlluminant[12] = 0u;
  CtrlLed_sCodingData.aunChannelIlluminant[13] = 2064u;
  CtrlLed_sCodingData.aunChannelIlluminant[14] = 64u;
  CtrlLed_sCodingData.aunChannelIlluminant[15] = 32u;


  /* ------------- 2) LED channel type - matrix / non -matrix  --------------- */
  /* ------------------------------------------------------------------------- */
  CtrlLed_sCodingData.aucChannelType[0]  = CTRLLED_CFG_NON_MATRIX_BUCK;
  CtrlLed_sCodingData.aucChannelType[1]  = CTRLLED_CFG_NON_MATRIX_BUCK;
  CtrlLed_sCodingData.aucChannelType[2]  = CTRLLED_CFG_NON_MATRIX_BUCK;
  CtrlLed_sCodingData.aucChannelType[3]  = CTRLLED_CFG_NON_MATRIX_BUCK;
  CtrlLed_sCodingData.aucChannelType[4]  = CTRLLED_CFG_MATRIX_BUCK;
  CtrlLed_sCodingData.aucChannelType[5]  = CTRLLED_CFG_MATRIX_BUCK;
  CtrlLed_sCodingData.aucChannelType[6]  = CTRLLED_CFG_MATRIX_BUCK;
  CtrlLed_sCodingData.aucChannelType[7]  = CTRLLED_CFG_NON_MATRIX_BUCK;
  CtrlLed_sCodingData.aucChannelType[8]  = CTRLLED_CFG_NON_MATRIX_BUCK;
  CtrlLed_sCodingData.aucChannelType[9]  = CTRLLED_CFG_NON_MATRIX_BUCK;
  CtrlLed_sCodingData.aucChannelType[10] = CTRLLED_CFG_NON_MATRIX_BUCK;
  CtrlLed_sCodingData.aucChannelType[11] = CTRLLED_CFG_MATRIX_BUCK;
  CtrlLed_sCodingData.aucChannelType[12] = CTRLLED_CFG_NON_MATRIX_BUCK;


  /* ------------- 3) Binning Class Current Selection for each LED ch.-------- */
  /* ------------------------------------------------------------------------- */
  CtrlLed_sCodingData.aunBinningCurrent[0u]  = 1000u;
  CtrlLed_sCodingData.aunBinningCurrent[1u]  = 1000u;
  CtrlLed_sCodingData.aunBinningCurrent[2u]  = 1000u;
  CtrlLed_sCodingData.aunBinningCurrent[3u]  = 650u;
  CtrlLed_sCodingData.aunBinningCurrent[4u]  = 250u;
  CtrlLed_sCodingData.aunBinningCurrent[5u]  = 250u;
  CtrlLed_sCodingData.aunBinningCurrent[6u]  = 250u;
  CtrlLed_sCodingData.aunBinningCurrent[7u]  = 210u;
  CtrlLed_sCodingData.aunBinningCurrent[8u]  = 210u;
  CtrlLed_sCodingData.aunBinningCurrent[9u]  = 210u;
  CtrlLed_sCodingData.aunBinningCurrent[10u] = 290u;
  CtrlLed_sCodingData.aunBinningCurrent[11u] = 250u;
  CtrlLed_sCodingData.aunBinningCurrent[12u] = 200u;


  /* ------------- 4) Fill Gamma LUT with Gamma Points [2 *17 ]--------------- */
  /* ------------------------------------------------------------------------- */
  for (uint8 ucLut = 0u; ucLut < 2u; ucLut++)
  {
    for (uint8 ucGammaPt = 0u; ucGammaPt < 17u; ucGammaPt++)
    {
      CtrlLed_sCodingData.sGamma.aunGamma[ucLut][ucGammaPt] = asGAMMA_POINTS[ucLut].GAMMA_1_POINTS[ucGammaPt];
      // printf("\n CtrlLed_sCodingData.sGamma.aunGamma[%d][%d] = %d", ucLut, ucGammaPt, CtrlLed_sCodingData.sGamma.aunGamma[ucLut][ucGammaPt]);
    }
  }

  /* ------------- Gamma LUT selection for each illuminant ---------------- */
  /* ---------------------------------------------------------------------- */
  CtrlLed_sCodingData.sGamma.aucGammaSel[0]  = 1u;
  CtrlLed_sCodingData.sGamma.aucGammaSel[1]  = 1u;
  CtrlLed_sCodingData.sGamma.aucGammaSel[2]  = 1u;
  CtrlLed_sCodingData.sGamma.aucGammaSel[3]  = 1u;
  CtrlLed_sCodingData.sGamma.aucGammaSel[4]  = 1u;
  CtrlLed_sCodingData.sGamma.aucGammaSel[5]  = 1u;
  CtrlLed_sCodingData.sGamma.aucGammaSel[6]  = 1u;
  CtrlLed_sCodingData.sGamma.aucGammaSel[7]  = 1u;
  CtrlLed_sCodingData.sGamma.aucGammaSel[8]  = 0u;
  CtrlLed_sCodingData.sGamma.aucGammaSel[9]  = 0u;
  CtrlLed_sCodingData.sGamma.aucGammaSel[10] = 0u;
  CtrlLed_sCodingData.sGamma.aucGammaSel[11] = 0u;
  CtrlLed_sCodingData.sGamma.aucGammaSel[12] = 0u;
  CtrlLed_sCodingData.sGamma.aucGammaSel[13] = 1u;
  CtrlLed_sCodingData.sGamma.aucGammaSel[14] = 1u;
  CtrlLed_sCodingData.sGamma.aucGammaSel[15] = 1u;


  /* ------------- Logical units selelction of gamma LUT ---------------- */
  /* -------------------------------------------------------------------- */
 // for (uint8 ucLu = 0u; ucLu < 103u; ucLu++)
 // {
 //   if (ucLu >= 12u && ucLu < 60u)
 //   {
 //     CtrlLed_sCodingData.sGamma.aucGammaSelLuMx[ucLu] = 1u;
 //   }
 //   else {
 //     CtrlLed_sCodingData.sGamma.aucGammaSelLuMx[ucLu] = 0u;
 //   }
 // }

  
  /* ------------- 5) LED Channel   - Light Function assigned  --------------- */
  /* ------------------------------------------------------------------------- */
  /* IFD - channel name */
  CtrlLed_sCodingData.ucLedName[0]  = 2u;   /* LB_FUSA */
  CtrlLed_sCodingData.ucLedName[1]  = 1u;   /* LB - Low Beam */
  CtrlLed_sCodingData.ucLedName[2]  = 1u;   /* LB - Low Beam */
  CtrlLed_sCodingData.ucLedName[3]  = 13u;  /* CL - Cornering Light */
  CtrlLed_sCodingData.ucLedName[4]  = 14u;  /* PXL - matrix channel */
  CtrlLed_sCodingData.ucLedName[5]  = 14u;  /* PXL - matrix channel */
  CtrlLed_sCodingData.ucLedName[6]  = 14u;  /* PXL - matrix channel */
  CtrlLed_sCodingData.ucLedName[7]  = 4u;   /* DRL/POS - Daytime Running Light/ Position Light */
  CtrlLed_sCodingData.ucLedName[8]  = 4u;   /* DRL/POS - Daytime Running Light/ Position Light */
  CtrlLed_sCodingData.ucLedName[9]  = 4u;   /* DRL/POS - Daytime Running Light/ Position Light */
  CtrlLed_sCodingData.ucLedName[10] = 6u;   /* TI - Turn Indicator */
  CtrlLed_sCodingData.ucLedName[11] = 14u;  /* PXL - matrix channel */
  CtrlLed_sCodingData.ucLedName[12] = HSS3;  /*HSS3*/


  /* -------------  6) Illuminant = Logical Unit assigned ------------------ */
  /* ----------------------------------------------------------------------- */
  CtrlLed_sCodingData.ucLogicalUnitIl[0]  = 1u;    /* Illuminant 1 (LB[Safety])  -  LED_DRIVER_01 */
  CtrlLed_sCodingData.ucLogicalUnitIl[1]  = 2u;    /* Illuminant 2 (LB[Spot DBL])-  LED_DRIVER_02 */
  CtrlLed_sCodingData.ucLogicalUnitIl[2]  = 3u;    /* Illuminant 3 (LB[MW])      -  LED_DRIVER_03 */
  CtrlLed_sCodingData.ucLogicalUnitIl[3]  = 4u;    /* Illuminant 4 (LB[SBL])     -  LED_DRIVER_04 */
  CtrlLed_sCodingData.ucLogicalUnitIl[4]  = 8u;    /* Illuminant 5 (LB[DRL 1])   -  LED_DRIVER_08 */
  CtrlLed_sCodingData.ucLogicalUnitIl[5]  = 9u;    /* Illuminant 6 (LB[DRL 2])   -  LED_DRIVER_09 */
  CtrlLed_sCodingData.ucLogicalUnitIl[6]  = 10u;   /* Illuminant 7 (LB[DRL 3])   -  LED_DRIVER_10 */
  CtrlLed_sCodingData.ucLogicalUnitIl[7]  = 11u;   /* Illuminant 8 (TI[TI])      -  LED_DRIVER_11 */
  CtrlLed_sCodingData.ucLogicalUnitIl[8]  = 255u;  /* Illuminant 9 (LB/HB[FLAT]) -  none          */
  CtrlLed_sCodingData.ucLogicalUnitIl[9]  = 255u;  /* Illuminant 10 (none[none]) -  none          */
  CtrlLed_sCodingData.ucLogicalUnitIl[10] = 255u;  /* Illuminant 11 (none[none]) -  none          */
  CtrlLed_sCodingData.ucLogicalUnitIl[11] = 255u;  /* Illuminant 12 (none[none]) -  none          */
  CtrlLed_sCodingData.ucLogicalUnitIl[12] = 255u;  /* Illuminant 13 (none[none]) -  none          */
  CtrlLed_sCodingData.ucLogicalUnitIl[13] = 110u;  /* Illuminant 14 FLAT[FLAT]   -  MATRIX: LED_DRIVER_05, LED_DRIVER_12 */
  CtrlLed_sCodingData.ucLogicalUnitIl[14] = 111u;  /* Illuminant 15 KINK[KINK]   -  MATRIX: LED_DRIVER_07                */
  CtrlLed_sCodingData.ucLogicalUnitIl[15] = 112u;  /* Illuminant 16 HB[HB]       -  MATRIX: LED_DRIVER_06                */


  /* ------------- 7) Internal Switch   - Mapping from Matrix Sheet ---------- */
  /* ------------------------------------------------------------------------- */
  uint8 ucSeg64 = 12u; //logical Unit
  uint8 ucSeg76 = 48u; //logical Unit
  for (uint8 ucCol = 0u; ucCol < 90u; ucCol++)
  {
    if ((ucCol >= 63u && ucCol < 75u))
    {
      //fill first half of FLAT row
      CtrlLed_sCodingData.aucLmmSwitchNo[ucCol] = ucSeg64++;
    }
    else if ((ucCol >= 75u && ucCol < 87u))
    {
      //fill second half of FLAT row
      CtrlLed_sCodingData.aucLmmSwitchNo[ucCol] = ucSeg76++;
    }
    else
    {
      CtrlLed_sCodingData.aucLmmSwitchNo[ucCol] = 0xFFu;

      // High Beam Row
      CtrlLed_sCodingData.aucLmmSwitchNo[6]  = 35u;
      CtrlLed_sCodingData.aucLmmSwitchNo[7]  = 32u;
      CtrlLed_sCodingData.aucLmmSwitchNo[8]  = 31u;
      CtrlLed_sCodingData.aucLmmSwitchNo[9]  = 28u;
      CtrlLed_sCodingData.aucLmmSwitchNo[10] = 27u;
      CtrlLed_sCodingData.aucLmmSwitchNo[11] = 24u;
      CtrlLed_sCodingData.aucLmmSwitchNo[18] = 47u;
      CtrlLed_sCodingData.aucLmmSwitchNo[19] = 44u;
      CtrlLed_sCodingData.aucLmmSwitchNo[20] = 43u;
      CtrlLed_sCodingData.aucLmmSwitchNo[21] = 40u;
      CtrlLed_sCodingData.aucLmmSwitchNo[22] = 39u;
      CtrlLed_sCodingData.aucLmmSwitchNo[23] = 36u;

      // Kink Row
      CtrlLed_sCodingData.aucLmmSwitchNo[36] = 34u;
      CtrlLed_sCodingData.aucLmmSwitchNo[37] = 33u;
      CtrlLed_sCodingData.aucLmmSwitchNo[38] = 30u;
      CtrlLed_sCodingData.aucLmmSwitchNo[39] = 29u;
      CtrlLed_sCodingData.aucLmmSwitchNo[40] = 26u;
      CtrlLed_sCodingData.aucLmmSwitchNo[41] = 25u;
      CtrlLed_sCodingData.aucLmmSwitchNo[48] = 46u;
      CtrlLed_sCodingData.aucLmmSwitchNo[49] = 45u;
      CtrlLed_sCodingData.aucLmmSwitchNo[50] = 42u;
      CtrlLed_sCodingData.aucLmmSwitchNo[51] = 41u;
      CtrlLed_sCodingData.aucLmmSwitchNo[52] = 38u;
      CtrlLed_sCodingData.aucLmmSwitchNo[53] = 37u;
    }
   // printf("\n CtrlLed_sCodingData.aucLmmSwitchNo[%d] = %d", ucCol, CtrlLed_sCodingData.aucLmmSwitchNo[ucCol]);
  }

  memcpy(&CtrlLed_sCodingData.aucAnimaMap[0], &applicationCodingData->Animation.AnimationsMapping.ucAnimaUnitMapping[0], CTRLLED_CFG_NR_OF_LOGICAL_UNITS);

  /* ------------- 8) Illuminant assigned for logical units ------------------ */
  /* ------------------------------------------------------------------------- */
  CtrlLed_sCodingData.aucLuIl[0u]  = 0u;
  CtrlLed_sCodingData.aucLuIl[1u]  = 1u;
  CtrlLed_sCodingData.aucLuIl[2u]  = 2u;
  CtrlLed_sCodingData.aucLuIl[3u]  = 3u;
  CtrlLed_sCodingData.aucLuIl[4u]  = 0xFFu;
  CtrlLed_sCodingData.aucLuIl[5u]  = 0xFFu;
  CtrlLed_sCodingData.aucLuIl[6u]  = 0xFFu;
  CtrlLed_sCodingData.aucLuIl[7u]  = 4u;
  CtrlLed_sCodingData.aucLuIl[8u]  = 5u;
  CtrlLed_sCodingData.aucLuIl[9u]  = 6u;
  CtrlLed_sCodingData.aucLuIl[10u] = 7u;
  CtrlLed_sCodingData.aucLuIl[11u] = 0xFFu;
  CtrlLed_sCodingData.aucLuIl[12u] = 11u;

  for (uint8 ucLuIdx = 12u; ucLuIdx < 60u; ucLuIdx++) 
  { 
    if ((ucLuIdx >= 12u && ucLuIdx < 24u) || (ucLuIdx >= 48u && ucLuIdx < 60u))
    {
      CtrlLed_sCodingData.aucLuIl[ucLuIdx] = 13u;  //illuminant 14 ([FLAT])
    }
    else if (ucLuIdx >= 24u && ucLuIdx < 36u)
    {
      CtrlLed_sCodingData.aucLuIl[ucLuIdx] = 14u;  //illuminant 15 ([KINK])
    }
    else
      CtrlLed_sCodingData.aucLuIl[ucLuIdx] = 15u;  //illuminant 16 ([HB])
  }

  for (uint8 ucLuIdx = 60u; ucLuIdx < 103u; ucLuIdx++) { CtrlLed_sCodingData.aucLuIl[ucLuIdx] = 0xFFu; }

  /* ------------- 9) assign illuminant to unit group (110 -119) = 10 groups - */
  /* ------------------------------------------------------------------------- */
  CtrlLed_sCodingData.asUnitGroups[0u].ucIlluminantAssigned = 13u;
  CtrlLed_sCodingData.asUnitGroups[0u].ucName = CTRLLED_CFG_FIRST_UNIT_GROUP;
  CtrlLed_sCodingData.asUnitGroups[1u].ucIlluminantAssigned = 14u;
  CtrlLed_sCodingData.asUnitGroups[1u].ucName = CTRLLED_CFG_FIRST_UNIT_GROUP +1u;
  CtrlLed_sCodingData.asUnitGroups[2u].ucIlluminantAssigned = 15u;
  CtrlLed_sCodingData.asUnitGroups[2u].ucName = CTRLLED_CFG_FIRST_UNIT_GROUP + 2u;

  for (uint8 ucGroupIdx = 3u; ucGroupIdx < 10u; ucGroupIdx++) 
  { 
    CtrlLed_sCodingData.asUnitGroups[ucGroupIdx].ucIlluminantAssigned = 0xFFu; 
    CtrlLed_sCodingData.asUnitGroups[ucGroupIdx].ucName = CTRLLED_CFG_FIRST_UNIT_GROUP + ucGroupIdx;
  }


}



