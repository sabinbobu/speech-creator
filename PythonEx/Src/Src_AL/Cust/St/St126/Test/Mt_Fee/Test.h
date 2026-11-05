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
#include <Fee.h>
#include <ctaaFee.h>
#include <Fee_InternalFct.h>

//=============================================================================
// Typedefs
//=============================================================================

//=============================================================================
// Defines
//=============================================================================

#define FEATURE_FLS_FLEX_RAM_SIZE (4096u)

//=============================================================================
// Module global variables
//=============================================================================

/* Fee.c */
extern flash_ssd_config_t flashSSDConfig;
extern const flash_user_config_t Flash_InitConfig0;

/* Fee_Internal.c */
extern tieFeeState          Fee_State;
extern MemIf_StatusType     Fee_t_Status;
extern MemIf_JobResultType  Fee_JobResult;

//=============================================================================
// Module function declarations
//=============================================================================

// Fee.c
extern Std_ReturnType Fee_EEERead(const flash_ssd_config_t* pSSDConfig, uint32 ulAddress, uint32 ulSize, uint8* pucData);
extern Std_ReturnType Fee_EEEWrite(const flash_ssd_config_t* pSSDConfig, uint32 ulAddress, uint32 ulSize, const uint8* pucData);
extern Std_ReturnType Fee_WaitEEWriteToFinish(const flash_ssd_config_t* pSSDConfig, uint32 ulAddress, const uint8* pucData, uint8 ucStep);

//=============================================================================
// Module function parameter stubs
//=============================================================================

/* Fee.c */
MemIf_ModeType      Fee_SetMode_Param1;
flash_ssd_config_t  Fee_EEERead_Param1;
uint32              Fee_EEERead_Param2;
uint32              Fee_EEERead_Param3;
uint8*              Fee_EEERead_Param4;
flash_ssd_config_t  Fee_EEEWrite_Param1;
uint32              Fee_EEEWrite_Param2;
uint32              Fee_EEEWrite_Param3;
uint8*              Fee_EEEWrite_Param4;
flash_ssd_config_t  Fee_WaitEEWriteToFinish_Param1;
uint32              Fee_WaitEEWriteToFinish_Param2;
uint8               Fee_WaitEEWriteToFinish_Param3;
uint8               Fee_WaitEEWriteToFinish_Param4;
uint16              Fee_Write_Param1;
uint8               Fee_Write_Param2;
uint16              Fee_Read_Param1;
uint16              Fee_Read_Param2;
uint8               Fee_Read_Param3;
uint16              Fee_Read_Param4;

/* Fee_Internal.c */
tieFeeState         FeeStateMachine_Param1;
uint16              Fee_LookUpIndex_Param1;
uint16              Fee_GetAddressOffset_Param1;
uint16              Fee_InvalidateBlock_Param1;
uint16              Fee_EraseImmediateBlock_Param1;

//=============================================================================
// Module function return value stubs
//=============================================================================

/* Fee_Internal.c */
uint16              Fee_LookUpIndex_RetVal;
uint16              Fee_GetAddressOffset_RetVal;
Std_ReturnType      Fee_EEERead_RetVal;
Std_ReturnType      Fee_EEEWrite_RetVal;
Std_ReturnType      Fee_WaitEEWriteToFinish_RetVal;
Std_ReturnType      Fee_Write_RetVal;
Std_ReturnType      Fee_Read_RetVal;
MemIf_StatusType    Fee_GetStatus_RetVal;
MemIf_JobResultType Fee_GetJobResult_RetVal;
Std_ReturnType      Fee_InvalidateBlock_RetVal;
Std_ReturnType      Fee_EraseImmediateBlock_RetVal;
Std_ReturnType      Fee_GetOpStatus_RetVal;

//=============================================================================
// Module static variables inside functions 
//=============================================================================


#endif // TEST_2023_08_25_H_
