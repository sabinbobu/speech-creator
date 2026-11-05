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

// Headers of the Module
#include <ctaaCtrlPxl.h>
#include <CtrlPxl.h>
#include <CtrlPxl_Data.h>
#include <CtrlPxl_DataInterfaces.h>
#include <CtrlPxl_Diag.h>
#include <CtrlPxl_MemHandling.h>
#include <CtrlPxl_RteAccess.h>
#include <CtrlPxl_Types.h>

//=============================================================================
// Typedefs
//=============================================================================
typedef  void(*pfcttype)(void);

//=============================================================================
// Defines
//=============================================================================

//=============================================================================
// Module global variables
//=============================================================================

// CtrlPxl.c 
extern  boolean CtrlPxl_boCodMap_OK;

// CtrlPxl_Data.c
extern  tNvmPara_CodingArea*        CtrlPxl_pCodingArea;

// CtrlPxl_Diag.c 
extern  tsCtrlPxl_MatrixFaultStates CtrlPxl_sMatrixFault;
extern  boolean                     CtrlPxl_boCommFaultActive;
extern  tuCtrlPxl_PxlFault          CtrlPxl_aPxlState[CFG_MLC_Chip_Cnt];
extern  tsCtrlPxl_ComStatus         CtrlPxl_sMlcStatus;
extern  uint8                       CtrlPxl_aucMlcErrors[CTRL_PXL_NUMBER_OF_MLC_CHIP];
extern  uint8                       CtrlPxl_aucCrcState[CFG_MLC_Chip_Cnt];

// CtrlPxl_DataInterfaces.h 
extern  tsCtrlPxl_InternalHandling CtrlPxl_sInternalHandling;

// CtrlPxl_MemHandling.c 
extern  uint8 CtrlPxl_CRC8_Eeprom;
extern  uint8 CtrlPxl_CRC8_Nvm;

//=============================================================================
// Module function declarations
//=============================================================================

// CtrlPxl.c 
extern void     CtrlPxl_ProcessIntensities(uint16* punMxBuff_Out);

// CtrlPxl_Data.c
extern boolean  CtrlPxl_ParaFct0(tParaFct0_Cmd eCmd, CONST_AL tNvmPara_CodingArea* CONST_AL pData);

// CtrlPxl_Diag.c 
extern void                          CtrlPxl_Diag_HandleMlcComFault(void);
extern void                          CtrlPxl_Diag_HandleMlcPxlFault(void);
extern void                          CtrlPxl_Diag_HandleMlcCrcFault(void);
extern void                          CtrlPxl_Diag_Handle_VCCx(void);

// CtrlPxl_MemHandling.c 
extern void CtrlPxl_HandleEEPromData(void);
extern void CtrlPxl_MatrixEEClbkInit_Fail(void);
extern void CtrlPxl_MatrixEEClbkInit_Success(void);
extern void CtrlPxl_CompareEEPromAndNvmData(void);
extern void CtrlPxl_AccessCalibDataAndCopy(uint8* pucDataBuff);
extern void CtrlPxl_CheckBrightness(uint8* pucDataBuff);

// CtrlPxl_RteAccsess.c 
extern Std_ReturnType CtrlPxl_RteAccess_Read_EcuSide(teCtrlPxl_EcuSide* peEcuSide);
extern Std_ReturnType CtrlPxl_RteAccess_Read_VccxLineState(teCtrlPxl_VccxLineState* peVccxState);
extern void           CtrlPxl_RteAccess_ReadNvmMatrixData(uint8* pucData, uint16 unSize);
extern void           CtrlPxl_RteAccess_MtxEE_Read(uint8* pucBuff_List, uint16 unStartAddr, uint16 unLength, void(*pfnSuccess)(void), void(*pfnFail)(void));

//=============================================================================
// Module function parameter stubs
//=============================================================================

// CtrlPxl.c 
uint16*  CtrlPxl_ProcessIntensities_Param1;

// CtrlPxl_Data.c 
tParaFct0_Cmd         CtrlPxl_ParaFct0_Param1;
tNvmPara_CodingArea*  CtrlPxl_ParaFct0_Param2;
uint8                 CtrlPxl_PxlMap_Param1[CTRLPXL_CFG_NR_OF_MATRIX_DRV][CTRLPXL_CFG_NR_OF_PXLs_STRING];
uint8                 CtrlPxl_Data_Matrix_Param1[CTRLPXL_CFG_MAX_NR_OF_PXL];
uint8                 CtrlPxl_Data_Matrix_Param2[CTRLPXL_CFG_NR_OF_MATRIX_DRV][CTRLPXL_CFG_NR_OF_PXLs_STRING];

// CtrlPxl_RteAccsess.c 
uint16                      CtrlPxl_RteAccess_Get_Intensities_CPM_Param1[CTRLPXL_CFG_NR_OF_LOGICAL_UNITS];
uint16                      *CtrlPxl_RteAccess_Set_MLCTgtPWMs_Param1;
uint8                       CtrlPxl_RteAccess_Get_MlcCrcError_Param1;
tsCtrlPxl_CodingParameters  CtrlPxl_RteAccess_Get_Coding_Param1;
teCtrlPxl_EcuSide           CtrlPxl_RteAccess_Read_EcuSide_Param1;
tuCtrlPxl_PxlFault          CtrlPxl_RteAccess_Get_PxlErrorStatus_Param1;
tsCtrlPxl_ComStatus         CtrlPxl_RteAccess_Get_CommErrorStatus_Param1;
teCtrlPxl_VccxLineState     CtrlPxl_RteAccess_Read_VccxLineState_Param1;
tsCtrlPxl_MatrixFaultStates CtrlPxl_RteAccess_Write_MatrixFaultStatus_Param1;
tuCtrlPxl_bErr              CtrlPxl_RteAccess_Write_MlcErrors_Param1;
tsRte_ucActualPxlPWM        CtrlPxl_RteAccess_Write_Mtx_PxlActPercPWM_ValidFrames_Param1;
tsRte_boMtxSegmentFault     CtrlPxl_RteAccess_Write_Mtx_PxlError_ValidFrames_Param1;
boolean                     CtrlPxl_RteAccess_Set_MtxEeprom_ErrorStatus_Param1;
boolean                     CtrlPxl_RteAccess_Set_MtxEeprom_ErrorStatus_Param2;

// CtrlPxl_Diag.c 
uint8_fast      CtrlPxl_GetMtxFaults_Param1;
uint8_fast      CtrlPxl_GetMtxFaults_Param2;

// CtrlPxl_MemHandling.c
pfcttype        CtrlPxl_RteAccess_MatrixEE_Init_Param1;
pfcttype        CtrlPxl_RteAccess_MatrixEE_Init_Param2;
uint8*          CtrlPxl_RteAccess_ReadNvmMatrixData_Param1;
uint16          CtrlPxl_RteAccess_ReadNvmMatrixData_Param2;
uint8*          CtrlPxl_RteAccess_MtxEE_Read_Param1;
uint16          CtrlPxl_RteAccess_MtxEE_Read_Param2;
uint16          CtrlPxl_RteAccess_MtxEE_Read_Param3;
pfcttype        CtrlPxl_RteAccess_MtxEE_Read_Param4;
pfcttype        CtrlPxl_RteAccess_MtxEE_Read_Param5;
uint8           CtrlPxl_RteAccess_MtxEE_Write_Param1[256];
uint16          CtrlPxl_RteAccess_MtxEE_Write_Param2;
uint16          CtrlPxl_RteAccess_MtxEE_Write_Param3;
pfcttype        CtrlPxl_RteAccess_MtxEE_Write_Param4;
pfcttype        CtrlPxl_RteAccess_MtxEE_Write_Param5;
boolean         CtrlPxl_RteAccess_ReadEntireMatrixData_Param1;
uint8*          CtrlPxl_RteAccess_ReadEntireMatrixData_Param2;
boolean         CtrlPxl_RteAccess_WriteBinningClass_Param1;
uint8*          CtrlPxl_RteAccess_WriteBinningClass_Param2;
uint8*          CtrlPxl_RteAccess_WriteEntireEEpromDataIntoNvM_Param1;
uint8*          CtrlPxl_CheckBrightness_Param1;

//=============================================================================
// Module function return value stubs
//=============================================================================

// CtrlPxl_Data.c 
boolean         CtrlPxl_ParaFct0_RetVal;
boolean         CtrlPxl_CodingDataValidation_RetVal;
boolean         CtrlPxl_PxlMap_RetVal;
boolean         CtrlPxl_Data_Matrix_RetVal;

// CtrlPxl_RteAccess.c 
uint8                           CtrlPxl_RteAccess_Get_ECU_Side_RetVal;
Std_ReturnType                  CtrlPxl_RteAccess_Read_EcuSide_RetVal;
boolean                         CtrlPxl_RteAccess_Get_PxlErrorStatus_RetVal;
boolean                         CtrlPxl_RteAccess_Get_CommErrorStatus_RetVal;
boolean                         CtrlPxl_RteAccess_Get_ResetErrorStatus_RetVal;
teCtrlPxl_VccxLineState         CtrlPxl_RteAccess_Get_VccxState_RetVal;
Std_ReturnType                  CtrlPxl_RteAccess_Read_VccxLineState_RetVal;
Std_ReturnType                  CtrlPxl_RteAccess_Write_MatrixFaultStatus_RetVal;
Std_ReturnType                  CtrlPxl_RteAccess_Write_MlcErrors_RetVal;

// CtrlPxl_Diag.c 
tuCtrlPxl_bErr                  CtrlPxl_GetMtxFaults_RetVal;

// CtrlPxl_MemHandling.c 
tsCtrlPxl_InternalHandling*     CtrlPxl_GetInternalHandlingStruct_RetVal;

//=============================================================================
// Module static variables inside functions 
//=============================================================================

// CtrlPxl.c 
tuCtrlPxl_bErr                aunErr_LogUnit[CTRLPXL_CFG_NR_OF_LOGICAL_UNITS];

// CtrlPxl_Diag.c 
TIMER                         ulPxlDefect_GeneralTimer;
TIMER                         ulPxlDefect_CycleTimer;
uint32                        ulPxlDefect_Timer;

TIMER                         ulComDefect_GeneralTimer;
TIMER                         ulComDefect_CycleTimer;
uint32                        ulComDefect_Timer;

boolean                       CtrlPxl_Force_DefaultVccxState;

TIMER                         ulCrcDefect_CycleTimer;
TIMER                         ulCrcDefect_GeneralTimer;
uint32                        ulCrcDefect_Timer;

// CtrlPxl_RteAccess.c 
tsRte_CddMlc_LedStatus        CtrlPxl_asPxlState[CTRL_PXL_NUMBER_OF_MLC_CHIP];


#endif // TEST_2023_08_25_H_
