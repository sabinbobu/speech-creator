//*****************************************************************************
// (C) Marelli Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Marelli Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Marelli Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  Test_Stubs.h
///
/// \brief Stub functions for access to software modules excluded from test
///
//-----------------------------------------------------------------------------
#ifndef TEST_STUBS_2024_08_06_H
#define TEST_STUBS_2024_08_06_H

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <AL_Helper.h>
#include <RteCommonTypes.h>

//-----------------------------------------------------------------------------
// Typedef
//-----------------------------------------------------------------------------

//=============================================================================
// Global variable stubs
//=============================================================================
extern tNvmPara_CodingArea  Coding_Dummy;
extern tParaFct0_Cmd        Coding_State;

//-----------------------------------------------------------------------------
// Stub function declarations
//-----------------------------------------------------------------------------
Std_ReturnType  Rte_Read_CodM_CddMlc_Para(tsRteCodingParameters* ppara1);
Std_ReturnType  Rte_Read_CtrlPxl_MatrixEE_DataRead(tsRte_MatrixEE0peration* ppara1);
Std_ReturnType  Rte_Read_CtrlPxl_MatrixEE_DataWrite(tsRte_MatrixEE0peration* ppara1);
Std_ReturnType  Rte_Read_CtrlPxl_MatrixEE_CbkInitData(tsRte_MatrixEE0CbkFn* ppara1);
Std_ReturnType  Rte_Read_IoHwAbUser_VccxLineState(teRte_VccxLineState* ppara1);

Std_ReturnType  Rte_Write_CtrlPxl_CddMlc_ComStatus_sVal (const tsRte_CddMlcComStatus* ppara1);
Std_ReturnType  Rte_Write_CtrlPxl_CddMlc_LedStatus_aVal (const tasRte_MlcLedStatus* ppara1);
Std_ReturnType  Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal (const tasRte_MlcAdcResult* ppara1);
Std_ReturnType  Rte_Write_CtrlPxl_CddMlc_ReinitMatrix   (const boolean* ppara1);
Std_ReturnType  Rte_Write_CtrlPxl_CddMlc_CrcError_sVal  (const tsRte_MlcComErrorStatus* ppara1);
Std_ReturnType  Rte_Write_CtrlPxl_CddMlc_SystemMode_eVal(const teRte_CddMlc_SystemMode* ppara1);


//-----------------------------------------------------------------------------
// Stub function parameter stubs
//-----------------------------------------------------------------------------
extern tsRteCodingParameters      Rte_Read_CodM_CddMlc_Para_Param1;
extern tsRte_MatrixEE0peration    Rte_Read_CtrlPxl_MatrixEE_DataRead_Param1;
extern tsRte_MatrixEE0peration    Rte_Read_CtrlPxl_MatrixEE_DataWrite_Param1;
extern tsRte_MatrixEE0CbkFn       Rte_Read_CtrlPxl_MatrixEE_CbkInitData_Param1;
extern teRte_VccxLineState        Rte_Read_IoHwAbUser_VccxLineState_Param1;

extern tsRte_CddMlcComStatus      Rte_Write_CtrlPxl_CddMlc_ComStatus_sVal_Param1;
extern tasRte_MlcLedStatus        Rte_Write_CtrlPxl_CddMlc_LedStatus_aVal_Param1;
extern tasRte_MlcAdcResult        Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal_Param1;
extern boolean                    Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_Param1;
extern tsRte_MlcComErrorStatus    Rte_Write_CtrlPxl_CddMlc_CrcError_sVal_Param1;
extern teRte_CddMlc_SystemMode    Rte_Write_CtrlPxl_CddMlc_SystemMode_eVal_Param1;

//-----------------------------------------------------------------------------
// Stub function returned value stubs
//-----------------------------------------------------------------------------
extern Std_ReturnType Rte_Read_CodM_CddMlc_Para_RetVal;
extern Std_ReturnType Rte_Read_CtrlPxl_MatrixEE_DataRead_RetVal;
extern Std_ReturnType Rte_Read_CtrlPxl_MatrixEE_DataWrite_RetVal;
extern Std_ReturnType Rte_Read_CtrlPxl_MatrixEE_CbkInitData_RetVal;
extern Std_ReturnType Rte_Read_IoHwAbUser_VccxLineState_RetVal;

extern Std_ReturnType Rte_Write_CtrlPxl_CddMlc_ComStatus_sVal_RetVal;
extern Std_ReturnType Rte_Write_CtrlPxl_CddMlc_LedStatus_aVal_RetVal;
extern Std_ReturnType Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal_RetVal;
extern Std_ReturnType Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_RetVal;
extern Std_ReturnType Rte_Write_CtrlPxl_CddMlc_CrcError_sVal_RetVal;
extern Std_ReturnType Rte_Write_CtrlPxl_CddMlc_SystemMode_eVal_RetVal;

//-----------------------------------------------------------------------------
// Stub function hit count variables
//-----------------------------------------------------------------------------
extern uint8 Rte_Read_CodM_CddMlc_Para_HitCount;
extern uint8 Rte_Read_CtrlPxl_MatrixEE_DataRead_HitCount;
extern uint8 Rte_Read_CtrlPxl_MatrixEE_DataWrite_HitCount;
extern uint8 Rte_Read_CtrlPxl_MatrixEE_CbkInitData_HitCount;
extern uint8 Rte_Read_IoHwAbUser_VccxLineState_HitCount;

extern uint8 Rte_Write_CtrlPxl_CddMlc_ComStatus_sVal_HitCount;
extern uint8 Rte_Write_CtrlPxl_CddMlc_LedStatus_aVal_HitCount;
extern uint8 Rte_Write_CtrlPxl_CddMlc_AdcResult_aVal_HitCount;
extern uint8 Rte_Write_CtrlPxl_CddMlc_ReinitMatrix_HitCount;
extern uint8 Rte_Write_CtrlPxl_CddMlc_CrcError_sVal_HitCount;
extern uint8 Rte_Write_CtrlPxl_CddMlc_SystemMode_eVal_HitCount;

#endif // TEST_STUBS_2024_08_06_H
