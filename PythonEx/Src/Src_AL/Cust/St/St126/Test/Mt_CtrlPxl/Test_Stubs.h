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
/// \file  Test_Stubs.h
///
/// \brief Stub functions prototypes for access to software modules excluded from test
///        including stub parameters
///
//-----------------------------------------------------------------------------
#ifndef TEST_STUBS_2023_08_25_H_
#define TEST_STUBS_2023_08_25_H_

//=============================================================================
// Includes
//=============================================================================
#include <AL_Helper.h>
#include <Rte/RteCommonTypes.h>
#include <Nvm.h>

//=============================================================================
// Typedef
//=============================================================================


//=============================================================================
// Global variable stubs
//=============================================================================

extern tNvmPara_CodingArea  Coding_Dummy ;
extern tParaFct0_Cmd        Coding_State ;

//=============================================================================
// Stub function declarations
//=============================================================================

Std_ReturnType Rte_Read_CodM_CtrlPxl_Para(tsRteCodingParameters* ppara1);
Std_ReturnType Rte_Read_IoHwAbUser_GetMountingSide(teRte_MountingSide* ppara1);
Std_ReturnType Rte_Read_CtrlPxl_CddMlc_ComStatus_sVal(tsRte_CddMlcComStatus* ppara1);
Std_ReturnType Rte_Read_CtrlPxl_CddMlc_LedStatus_aVal(tasRte_MlcLedStatus* ppara1);
Std_ReturnType Rte_Read_CtrlPxl_CddMlc_CrcError_sVal(tsRte_MlcComErrorStatus* ppara1);
Std_ReturnType Rte_Read_IoHwAbUser_VccxLineState(teRte_VccxLineState* ppara1);
Std_ReturnType Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels(tsRte_TgtPxlSig0Arr* ppara1);

Std_ReturnType Rte_Write_CtrlPxl_TgtMtxPixels_sVal(const tsRte_TgtMtxPixels_sVal* ppara1);
Std_ReturnType Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState(const tsRte_MatrixFaultStates* ppara1);
Std_ReturnType Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal(const tauRte_CtrlPxl_Mtx_bErr* ppara1);
Std_ReturnType Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand(const uint8* ppara1);
Std_ReturnType Rte_Write_CtrlPxl_ActualPxlPWM(const tsRte_ucActualPxlPWM* ppara1);
Std_ReturnType Rte_Write_CtrlPxl_ActualPxlError(const tsRte_boMtxSegmentFault* ppara1);
Std_ReturnType Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus(const tsRte_MtxEeprom_ErrStatus* ppara1);
Std_ReturnType Rte_Write_CtrlPxl_CtrlLed_EepromBinningClass_aVal(const tasRte_CtrlPxl_BinEEprom* ppara1);
Std_ReturnType Rte_Write_CtrlPxl_MatrixEE_CbkInitData(const tsRte_MatrixEE0CbkFn* ppara1);
Std_ReturnType Rte_Write_CtrlPxl_MatrixEE_DataRead(const tsRte_MatrixEE0peration* ppara1);
Std_ReturnType Rte_Write_CtrlPxl_MatrixEE_DataWrite(const tsRte_MatrixEE0peration* ppara1);
Std_ReturnType Rte_Write_CtrlPxl_Nvm_WriteData(const tsRte_NvMBlock* ppara1);
Std_ReturnType Rte_Write_CtrlPxl_CddMlc_ReinitMatrix(const boolean* ppara1);


uint32         LPTMR0_GetTimeElapsed(const uint32 ulStartValue);
uint8          Crc_CalculateCRC8H1D(CONST_AL uint8 *DataPtr, CONST_AL uint32 Length, CONST_AL uint8  StartValue8);
void           UtilMemCopy(uint8* pucDest, const uint8* pucSource, uint16_least unLength);

//=============================================================================
// Stub function parameter stubs
//=============================================================================

extern tsRteCodingParameters       Rte_Read_CodM_CtrlPxl_Para_Param1;
extern teRte_MountingSide          Rte_Read_IoHwAbUser_GetMountingSide_Param1;
extern tsRte_CddMlcComStatus       Rte_Read_CtrlPxl_CddMlc_ComStatus_sVal_Param1;
extern tasRte_MlcLedStatus         Rte_Read_CtrlPxl_CddMlc_LedStatus_aVal_Param1;
extern tsRte_MlcComErrorStatus     Rte_Read_CtrlPxl_CddMlc_CrcError_sVal_Param1;
extern teRte_VccxLineState         Rte_Read_IoHwAbUser_VccxLineState_Param1;
extern tsRte_TgtPxlSig0Arr         Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_Param1;
                            
extern tsRte_TgtMtxPixels_sVal     Rte_Write_CtrlPxl_TgtMtxPixels_sVal_Param1;
extern tsRte_MatrixFaultStates     Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_Param1;
extern tauRte_CtrlPxl_Mtx_bErr     Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_Param1;
extern uint8                       Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand_Param1;
extern tsRte_ucActualPxlPWM        Rte_Write_CtrlPxl_ActualPxlPWM_Param1;
extern tsRte_boMtxSegmentFault     Rte_Write_CtrlPxl_ActualPxlError_Param1;
extern tsRte_MtxEeprom_ErrStatus   Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus_Param1;
extern tasRte_CtrlPxl_BinEEprom    Rte_Write_CtrlPxl_CtrlLed_EepromBinningClass_aVal_Param1;
extern tsRte_MatrixEE0CbkFn        Rte_Write_CtrlPxl_MatrixEE_CbkInitData_Param1;
extern tsRte_MatrixEE0peration     Rte_Write_CtrlPxl_MatrixEE_DataRead_Param1;
extern tsRte_MatrixEE0peration     Rte_Write_CtrlPxl_MatrixEE_DataWrite_Param1;
extern tsRte_NvMBlock              Rte_Write_CtrlPxl_Nvm_WriteData_Param1;
extern boolean                     Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_Param1;


extern uint32                      LPTMR0_GetTimeElapsed_Param1;
extern uint8*                      Crc_CalculateCRC8H1D_Param1;
extern uint32                      Crc_CalculateCRC8H1D_Param2;
extern uint8                       Crc_CalculateCRC8H1D_Param3;
extern uint8                       UtilMemCopy_Input_Param1;
extern uint8                       UtilMemCopy_Input_Param2;
extern uint16_least                UtilMemCopy_Input_Param3;                
extern uint8                       UtilMemCopy_Output_Param1[256];
extern uint8                       UtilMemCopy_Output_Param2[256];

//=============================================================================
// Stub function returned value stubs
//=============================================================================

extern Std_ReturnType  Rte_Read_CodM_CtrlPxl_Para_RetVal;
extern Std_ReturnType  Rte_Read_IoHwAbUser_GetMountingSide_RetVal;
extern Std_ReturnType  Rte_Read_CtrlPxl_CddMlc_ComStatus_sVal_RetVal;
extern Std_ReturnType  Rte_Read_CtrlPxl_CddMlc_LedStatus_aVal_RetVal;
extern Std_ReturnType  Rte_Read_CtrlPxl_CddMlc_CrcError_sVal_RetVal;
extern Std_ReturnType  Rte_Read_IoHwAbUser_VccxLineState_RetVal;
extern Std_ReturnType  Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_RetVal;

extern Std_ReturnType  Rte_Write_CtrlPxl_TgtMtxPixels_sVal_RetVal;
extern Std_ReturnType  Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_RetVal;
extern Std_ReturnType  Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_RetVal;
extern Std_ReturnType  Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand_RetVal;
extern Std_ReturnType  Rte_Write_CtrlPxl_ActualPxlPWM_RetVal;
extern Std_ReturnType  Rte_Write_CtrlPxl_ActualPxlError_RetVal;
extern Std_ReturnType  Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus_RetVal;
extern Std_ReturnType  Rte_Write_CtrlPxl_CtrlLed_EepromBinningClass_aVal_RetVal;
extern Std_ReturnType  Rte_Write_CtrlPxl_MatrixEE_CbkInitData_RetVal;
extern Std_ReturnType  Rte_Write_CtrlPxl_MatrixEE_DataRead_RetVal;
extern Std_ReturnType  Rte_Write_CtrlPxl_MatrixEE_DataWrite_RetVal;
extern Std_ReturnType  Rte_Write_CtrlPxl_Nvm_WriteData_RetVal;
extern Std_ReturnType  Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_RetVal;

extern uint32          LPTMR0_GetTimeElapsed_RetVal;
extern uint8           Crc_CalculateCRC8H1D_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

extern uint8   Rte_Read_CodM_CtrlPxl_Para_HitCount;
extern uint8   Rte_Read_IoHwAbUser_GetMountingSide_HitCount;
extern uint8   Rte_Read_CtrlPxl_CddMlc_ComStatus_sVal_HitCount;
extern uint8   Rte_Read_CtrlPxl_CddMlc_LedStatus_aVal_HitCount;
extern uint8   Rte_Read_CtrlPxl_CddMlc_CrcError_sVal_HitCount;
extern uint8   Rte_Read_IoHwAbUser_VccxLineState_HitCount;
extern uint8   Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount;

extern uint8   Rte_Write_CtrlPxl_TgtMtxPixels_sVal_HitCount;
extern uint8   Rte_Write_CtrlPxl_CtrLed_MatrixFault_sState_HitCount;
extern uint8   Rte_Write_CtrlPxl_CtrlLed_Matrix_bErr_aVal_HitCount;
extern uint8   Rte_Write_CtrlPxl_CddMlc_SysCtrlCommand_HitCount;
extern uint8   Rte_Write_CtrlPxl_ActualPxlPWM_HitCount;
extern uint8   Rte_Write_CtrlPxl_ActualPxlError_HitCount;
extern uint8   Rte_Write_CtrlPxl_MtxEeprom_ErrorStatus_HitCount;
extern uint8   Rte_Write_CtrlPxl_CtrlLed_EepromBinningClass_aVal_HitCount;
extern uint8   Rte_Write_CtrlPxl_MatrixEE_CbkInitData_HitCount;
extern uint8   Rte_Write_CtrlPxl_MatrixEE_DataRead_HitCount;
extern uint8   Rte_Write_CtrlPxl_MatrixEE_DataWrite_HitCount;
extern uint8   Rte_Write_CtrlPxl_Nvm_WriteData_HitCount;
extern uint8   Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_HitCount;

extern uint8   LPTMR0_GetTimeElapsed_HitCount;
extern uint8   Crc_CalculateCRC8H1D_HitCount;
extern uint8   UtilMemCopy_HitCount;

#endif // TEST_STUBS_2023_08_25_H_
