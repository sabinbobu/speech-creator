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
#include <CtrlPxl_Cfg.h>


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

//struct tsCtrlLed_Gamma_Points { uint16 GAMMA_1_POINTS[CODM_PARA_GAMMA_PTS_SIZE];
//  //uint16 GAMMA_2_POINTS[CODM_PARA_GAMMA_PTS_SIZE];
//                              }asGAMMA_POINTS[CTRLLED_CFG_GAMMA_NUMBER] = CTRLLED_GAMMA_POINTS_LIST;


  ///* 1.  LED1 sheet : Binning classes */
                                                                         /* Class_0 | _1 |   _2 |   _3 |   _4 |   _5 */
  uint16 DRV01_CURRENT_BINNING_CLASSES[CTRL_PXL_CFG_MAX_BINNING_CLASSES] = { 1000u, 1000u, 1000u, 1000u, 1000u, 1000u };
  uint16 DRV02_CURRENT_BINNING_CLASSES[CTRL_PXL_CFG_MAX_BINNING_CLASSES] = { 1000u, 1000u, 1000u, 1000u, 1000u, 1000u };
  uint16 DRV03_CURRENT_BINNING_CLASSES[CTRL_PXL_CFG_MAX_BINNING_CLASSES] = { 1000u, 1000u, 1000u, 1000u, 1000u, 1000u };
  uint16 DRV04_CURRENT_BINNING_CLASSES[CTRL_PXL_CFG_MAX_BINNING_CLASSES] = { 650u,  650u,  650u,  650u,  650u,  650u };
  uint16 DRV05_CURRENT_BINNING_CLASSES[CTRL_PXL_CFG_MAX_BINNING_CLASSES] = { 250u,  250u,  250u,  250u,  250u,  250u };
  uint16 DRV06_CURRENT_BINNING_CLASSES[CTRL_PXL_CFG_MAX_BINNING_CLASSES] = { 250u,  250u,  250u,  250u,  250u,  250u };
  uint16 DRV07_CURRENT_BINNING_CLASSES[CTRL_PXL_CFG_MAX_BINNING_CLASSES] = { 250u,  250u,  250u,  250u,  250u,  250u };
  uint16 DRV08_CURRENT_BINNING_CLASSES[CTRL_PXL_CFG_MAX_BINNING_CLASSES] = { 210u,  210u,  210u,  210u,  210u,  210u };
  uint16 DRV09_CURRENT_BINNING_CLASSES[CTRL_PXL_CFG_MAX_BINNING_CLASSES] = { 210u,  210u,  210u,  210u,  210u,  210u };
  uint16 DRV10_CURRENT_BINNING_CLASSES[CTRL_PXL_CFG_MAX_BINNING_CLASSES] = { 210u,  210u,  210u,  210u,  210u,  210u };
  uint16 DRV11_CURRENT_BINNING_CLASSES[CTRL_PXL_CFG_MAX_BINNING_CLASSES] = { 290u,  290u,  290u,  290u,  290u,  290u };
  uint16 DRV12_CURRENT_BINNING_CLASSES[CTRL_PXL_CFG_MAX_BINNING_CLASSES] = { 250u,  250u,  250u,  250u,  250u,  250u };


//-----------------------------------------------------------------------------
// Function Prototype
//-----------------------------------------------------------------------------
STATIC_AL void Mt_MappingListLeft(void);
STATIC_AL void Mt_MappingListRight(void);
STATIC_AL void Mt_MatrixSheetLeft(void);
STATIC_AL void Mt_MatrixSheetRight(void);
STATIC_AL void Mt_CodingLeftSide(void);
STATIC_AL void Mt_CodingRightSide(void);


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
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit3  = DRV_01;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit3 = LMM_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit3 = PXL_NOTUSED;

  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit5  = DRV_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit5 = LMM_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit5 = PXL_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit6  = DRV_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit6 = LMM_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit6 = PXL_NOTUSED;

  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Drv_Left_Unit9   = DRV_09;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.Lmms_Left_Unit9  = LMM_NOTUSED;
  applicationCodingData->MappingList.LogicalUnitsLeftHeadlamp_DriverMapping.SwNr_Left_Unit9  = PXL_NOTUSED;
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

    memcpy(&CtrlPxl_pCodingArea, &applicationCodingData, sizeof(CtrlPxl_pCodingArea));
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

    memcpy(&CtrlPxl_pCodingArea, &applicationCodingData, sizeof(CtrlPxl_pCodingArea));

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




