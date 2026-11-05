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
#include <RteCommonTypes.h>
//=============================================================================
// Typedef
//=============================================================================


//=============================================================================
// Stub function declarations
//=============================================================================
void            UtilMemCopy(uint8* pucDest, const uint8* pucSource, uint16_least unLength);
void            UtilMemClr(uint8* pucBuffer, uint16_least unLength);
uint32          Crc_CalculateCRC32(CONST_AL uint8* pucCrc_DataPtr, uint32_least ulCrc_Length, uint32 ulCrc_StartValue32);
void            Mt_Nvm_Internal_pfnCallBackFunc_Stub(void);
void            Mt_Nvm_Internal_pfnInitCallback_Stub(void);
Std_ReturnType  Rte_Read_CtrlPxl_Nvm_WriteData(tsRte_NvMBlock* ppara1);


//=============================================================================
// Stub function parameter stubs
//=============================================================================
extern uint8              UtilMemClr_Param1;
extern uint16_least       UtilMemClr_Param2;

extern uint8*             Crc_CalculateCRC32_Param1;
extern uint32_least       Crc_CalculateCRC32_Param2;
extern uint32             Crc_CalculateCRC32_Param3;

extern uint8              UtilMemCopy_Input_Param1;
extern uint8              UtilMemCopy_Input_Param2;
extern uint16_least       UtilMemCopy_Input_Param3;

extern uint8              UtilMemCopy_Output_Param1[90];
extern uint8              UtilMemCopy_Output_Param2[90];
 
extern tsRte_NvMBlock     Rte_Read_CtrlPxl_Nvm_WriteData_Param1;

//=============================================================================
// Stub function returned value stubs
//=============================================================================

extern uint32             Crc_CalculateCRC32_RetVal;
extern uint32             Rte_Read_CtrlPxl_Nvm_WriteData_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================

extern uint8              UtilMemClr_HitCount;
extern uint8              UtilMemCopy_HitCount;
extern uint8              Crc_CalculateCRC32_HitCount;
extern uint8              Mt_Nvm_Internal_CallbackFunction_Stub_HitCount;
extern uint8              Mt_Nvm_Internal_InitCallback_Stub_HitCount;
extern uint8              Rte_Read_CtrlPxl_Nvm_WriteData_HitCount;

#endif // TEST_STUBS_2023_08_25_H_
