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
/// \file  Test.h
///
/// \brief This file contains functions prototypes of the tested module, 
///        including functions parameters and global variables
///
//-----------------------------------------------------------------------------
#ifndef TEST_2023_08_25_H_
#define TEST_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>
#include <Adc_TargetTypes.h>
#include <CddDma.h>
#include <Adc_reg_stubs.h>

//=============================================================================
// Typedefs
//=============================================================================


//=============================================================================
// Defines
//=============================================================================
#define ADC_DRV_READ_CONV_ERROR                     0xFFFFu               // Invalid ADC value (16 bit)

//=============================================================================
// Module global variables
//============================================================================= 
extern tsAdc_AdcChInCfgMap* Adc_Drv_psInputMap;

//=============================================================================
// Module function declarations
//=============================================================================
//Adc.c:
extern void             Adc_Init(CONST_AL tsAdc_CfgData* CONST_AL psAdcCfgData);
extern Std_ReturnType   Adc_ReadGroup(uint8 ucAdcIn, uint16* CONST_AL unAdcValue);

//Adc_Dma.c:
extern void             Adc_Dma_SetDmaParam(CONST_AL tsAdc_CfgData* CONST_AL psAdcCfgData, tsAdc_DmaTriggerCfg * CONST_AL psDmaCfg);
extern Std_ReturnType   Adc_Dma_InitDmaJob(CONST_AL tsAdc_CfgData* CONST_AL psAdcCfgData);

//Adc_Drv.c:
extern Std_ReturnType   Adc_Drv_InitAdc(CONST_AL tsAdc_CfgData* CONST_AL psCfgData);
extern Std_ReturnType   Adc_Drv_ConfigAdc(CONST_AL tsAdc_AdcInstanceCfg * CONST_AL psAdcConfig);
extern Std_ReturnType   Adc_Drv_AutoCalibration(CONST_AL tsAdc_AdcInstanceCfg * CONST_AL psAdcConfig);
extern void             Adc_Drv_AdcChInit(CONST_AL tsAdc_AdcInputCfg* CONST_AL psAdcChInCfg);
extern Std_ReturnType   Adc_Drv_SwReadChannel(uint8 ucInput, tsAdc_AdcInputCfg CONST_AL sChnCfg[], uint16 * unAdcData);
extern uint16           Adc_Drv_GetAdcRawValue(uint8 ucInputIx);
extern void             Adc_Drv_SetAdcClkDivider(ADC_Type* CONST_AL psAdcInst, uint32 ulDividerVal);
extern void             Adc_Drv_SetAdcSampleNr(ADC_Type* CONST_AL psAdcInst, uint32 ulSmplNr);
extern void             Adc_Drv_SetAdcResolution(ADC_Type* CONST_AL psAdcInst, uint32 ulResolution);
extern void             Adc_Drv_SetAdcClkIn(ADC_Type* CONST_AL psAdcInst, uint32 ulClkIn);
extern void             Adc_Drv_SetAdcTrgType(ADC_Type* CONST_AL psAdcInst, uint32 ulTriggerTp);
extern void             Adc_Drv_SetAdcTrgInput(ADC_Type* CONST_AL psAdcInst, uint32 ulTriggerIn);
extern void             Adc_Drv_SetAdcPreTrgInput(ADC_Type* CONST_AL psAdcInst, uint32 ulPreTriggerIn);
extern void             Adc_Drv_SetAdcDmaEnbl(ADC_Type* CONST_AL psAdcInst, uint32 ulDmaEnbl);
extern void             Adc_Drv_SetAdcRefSel(ADC_Type* CONST_AL psAdcInst, uint32 ulRefSel);
extern void             Adc_Drv_SetAdcAvgEnbl(ADC_Type* CONST_AL psAdcInst, uint32 ulAvgEnbl);
extern void             Adc_Drv_SetAdcAvgMode(ADC_Type* CONST_AL psAdcInst, uint32 ulAvgMode);
extern void             Adc_Drv_SetAdcContinousMode(ADC_Type* CONST_AL psAdcInst, uint32 ulContinousMode);
extern void             Adc_Drv_SetAdcSupplyEn(ADC_Type* CONST_AL psAdcInst, uint32 ulSupplyEn);
extern void             Adc_Drv_SetAdcStartCalibration(ADC_Type* CONST_AL psAdcInst);
extern boolean          Adc_Drv_GetCalibrationStatus(ADC_Type* CONST_AL psAdcInst);
extern void             Adc_Drv_SetAdcChnInput(CONST_AL tsAdc_AdcInputCfg* CONST_AL psAdcChInCfg, uint32 ulInputSel);
extern boolean          Adc_Drv_GetAdcCompleteConvStat(ADC_Type* CONST_AL psAdcInst);
extern Std_ReturnType   Adc_Drv_EolCalibration(CONST_AL tsAdc_AdcInstanceCfg * CONST_AL psAdcConfig);

//=============================================================================
// Module function parameter stubs
//=============================================================================
//Adc.c:
tsAdc_CfgData*             Adc_Init_Param1;

uint8                      Adc_ReadGroup_Param1;
uint16*                    Adc_ReadGroup_Param2;

//Adc_Dma.c:
tsAdc_CfgData*             Adc_Dma_InitDmaJob_Param1;

tsAdc_CfgData*             Adc_Dma_SetDmaParam_Param1;
tsAdc_DmaTriggerCfg*       Adc_Dma_SetDmaParam_Param2;

//Adc_Drv.c:
tsAdc_CfgData*             Adc_Drv_InitAdc_Param1;

tsAdc_AdcInstanceCfg*      Adc_Drv_ConfigAdc_Param1;

tsAdc_AdcInstanceCfg*      Adc_Drv_AutoCalibration_Param1;

tsAdc_AdcInputCfg*         Adc_Drv_AdcChInit_Param1;

uint8                      Adc_Drv_SwReadChannel_Param1;
tsAdc_AdcInputCfg          Adc_Drv_SwReadChannel_Param2[];
uint16*                    Adc_Drv_SwReadChannel_Param3;

uint8                      Adc_Drv_GetAdcRawValue_Param1;

ADC_Type*                  Adc_Drv_SetAdcClkDivider_Param1;
uint32                     Adc_Drv_SetAdcClkDivider_Param2;

ADC_Type*                  Adc_Drv_SetAdcSampleNr_Param1;
uint32                     Adc_Drv_SetAdcSampleNr_Param2;

ADC_Type*                  Adc_Drv_SetAdcResolution_Param1;
uint32                     Adc_Drv_SetAdcResolution_Param2;

ADC_Type*                  Adc_Drv_SetAdcClkIn_Param1;
uint32                     Adc_Drv_SetAdcClkIn_Param2;

ADC_Type*                  Adc_Drv_SetAdcTrgType_Param1;
uint32                     Adc_Drv_SetAdcTrgType_Param2;

ADC_Type*                  Adc_Drv_SetAdcTrgInput_Param1;
uint32                     Adc_Drv_SetAdcTrgInput_Param2;

ADC_Type*                  Adc_Drv_SetAdcPreTrgInput_Param1;
uint32                     Adc_Drv_SetAdcPreTrgInput_Param2;

ADC_Type*                  Adc_Drv_SetAdcDmaEnbl_Param1;
uint32                     Adc_Drv_SetAdcDmaEnbl_Param2;

ADC_Type*                  Adc_Drv_SetAdcRefSel_Param1;
uint32                     Adc_Drv_SetAdcRefSel_Param2;

ADC_Type*                  Adc_Drv_SetAdcAvgEnbl_Param1;
uint32                     Adc_Drv_SetAdcAvgEnbl_Param2;

ADC_Type*                  Adc_Drv_SetAdcAvgMode_Param1;
uint32                     Adc_Drv_SetAdcAvgMode_Param2;

ADC_Type*                  Adc_Drv_SetAdcContinousMode_Param1;
uint32                     Adc_Drv_SetAdcContinousMode_Param2;

ADC_Type*                  Adc_Drv_SetAdcSupplyEn_Param1;
uint32                     Adc_Drv_SetAdcSupplyEn_Param2;

ADC_Type*                  Adc_Drv_SetAdcStartCalibration_Param1;

ADC_Type*                  Adc_Drv_GetCalibrationStatus_Param1;

tsAdc_AdcInputCfg*         Adc_Drv_SetAdcChnInput_Param1;
uint32                     Adc_Drv_SetAdcChnInput_Param2;

ADC_Type*                  Adc_Drv_GetAdcCompleteConvStat_Param1;

tsAdc_AdcInstanceCfg*      Adc_Drv_EolCalibration_Param1;

//=============================================================================
// Module function return value stubs
//=============================================================================
//Adc.c:
Std_ReturnType Adc_Dma_InitDmaJob_RetVal;

//Adc_Dma.c:

//Adc_Drv.c:
Std_ReturnType Adc_Drv_ConfigAdc_RetVal;
Std_ReturnType Adc_Drv_AutoCalibration_RetVal;
Std_ReturnType Adc_Drv_SwReadChannel_RetVal;
Std_ReturnType Adc_Drv_EolCalibration_RetVal;
uint16         Adc_Drv_GetAdcRawValue_RetVal;
boolean        Adc_Drv_GetCalibrationStatus_RetVal;
boolean        Adc_Drv_GetAdcCompleteConvStat_RetVal;

//=============================================================================
// Module static variables inside functions 
//=============================================================================


//=============================================================================
// Global variable stubs
//=============================================================================
tsAdc_AdcChInCfgMap         Adc_Drv_sInputMap_Dummy;
tsAdc_AdcInputCfg           psAdcInCfg_Dummy[30];
uint32                      ulAdcData_Dummy[30];
tsAdc_CfgData               psAdcCfgData_Dummy;
tsAdc_AdcInstanceCfg        Adc_Drv_ConfigAdc_Param1_Dummy;
tsAdc_CfgData               sAdc_Dma_SetDmaParam_Param1;
tsAdc_DmaTriggerCfg         sAdc_Dma_SetDmaParam_Param2;
tsAdc_AdcInstanceCfg        Adc_Drv_AutoCalibration_Param1_Dummy;
tsAdc_AdcInstanceCfg        Adc_Drv_Adc_Drv_EolCalibration_Param1_Dummy;
tsAdc_AdcInputCfg           Adc_Drv_AdcChInit_Param1_Dummy;
uint16                      Adc_Drv_SwReadChannel_Param3_Dummy;
tsAdc_AdcInputCfg           Adc_Drv_SetAdcChnInput_Param1_Dummy;
uint16                      Adc_ReadGroup_Param2_Dummy;
uint16                      Adc0_Eft_Data[22] =
{
  0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u, 10u, 11u, 12u, 13u, 14u, 15u, 16u, 17u, 18u, 19u, 20u, 65535u
};

uint16                     Adc1_Eft_Data[22] =
{
  21u, 22u, 23u, 24u, 25u, 26u, 27u, 28u, 29u, 30u, 31u, 32u, 33u, 34u, 35u, 36u, 37u, 38u, 39u, 40u, 41u, 65535u
};

#endif // TEST_2023_08_25_H_
