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
#include <FctR_Cfg.h>


//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Stub variables
//-----------------------------------------------------------------------------
tNvmPara_CodingArea*  applicationCodingData;
tNvmPara_CodingArea   InitCoding = { 0u };

//-----------------------------------------------------------------------------
// DATA TYPES TO SIMULATE CODING DATA
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Function Prototype
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Helper Functions
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
///  Description
///    - Function for testing purposes to populate the coding parameters
///      as in the actual AL-Coding file used by the software
///      Coding sheets covered:
///             - Led1   : binning class currents
///             - Lmmx   : illuminants configuration, gamma config.
///
//-----------------------------------------------------------------------------
void FctR_CreateCodingData_FULLVariant(void)
{
  applicationCodingData = &InitCoding;


  /* 2. LmmX Sheet : Logical Units Configured for Illuminants of Left and Right Headlamp */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[0]  =   1u;  /* Illuminant 1 (LB[Safety])  -  LED_DRIVER_01 */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[1]  =   2u;  /* Illuminant 2 (LB[Spot DBL])-  LED_DRIVER_02 */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[2]  =   3u;  /* Illuminant 3 (LB[MW])      -  LED_DRIVER_03 */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[3]  =   4u;  /* Illuminant 4 (LB[SBL])     -  LED_DRIVER_04 */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[4]  =   8u;  /* Illuminant 5 (LB[DRL 1])   -  LED_DRIVER_08 */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[5]  =   9u;  /* Illuminant 6 (LB[DRL 2])   -  LED_DRIVER_09 */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[6]  =  10u;  /* Illuminant 7 (LB[DRL 3])   -  LED_DRIVER_10 */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[7]  =  11u;  /* Illuminant 8 (TI[TI])      -  LED_DRIVER_11 */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[8]  =   0u;  /* Illuminant 9 (LB/HB[FLAT]) -  none          */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[9]  =   0u;  /* Illuminant 10 (none[none]) -  none          */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[10] =   0u;  /* Illuminant 11 (none[none]) -  none          */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[11] =   0u;  /* Illuminant 12 (none[none]) -  none          */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[12] = HSS3;  /* Illuminant 13 HSS3          */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[13] = 110u;  /* Illuminant 14 FLAT[FLAT]   -  MATRIX: LED_DRIVER_05, LED_DRIVER_12 */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[14] = 111u;  /* Illuminant 15 KINK[KINK]   -  MATRIX: LED_DRIVER_07                */
  applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs[15] = 112u;  /* Illuminant 16 HB[HB]       -  MATRIX: LED_DRIVER_06                */

  memcpy(&applicationCodingData->LmmX.LMUnitConfigRightHeadlamp.LSM_Illum_Assigned_Units_Right_LMs, &applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs, sizeof(applicationCodingData->LmmX.LMUnitConfigLeftHeadlamp.LSM_Illum_Assigned_Units_Left_LMs));


   /* 3. LmmX Sheet : Gamma Curve Config */
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


 // copy the coding data in the actual working variable from CtrlLed module
  memcpy(&FctR_pCodingArea, &applicationCodingData, sizeof(FctR_pCodingArea));

}

