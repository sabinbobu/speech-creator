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
/// \file  Fee.c
///
/// \brief  Flash EEPROM EMULATION
///
/// \descr  Stub functions for EMULATED EEPROM mechanism that are responsible for:
///         Partition the flash memory, Read and write operation using FlexRAM address space
///
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------
#include "Fee_TargetTypes.h"
#include "Fee_InternalFct.h"
#include "Fee.h"

//=============================================================================
// preprocessor definitions
//=============================================================================


//=============================================================================
// Private types
//=============================================================================

typedef Std_ReturnType(*CallbackFuncType)(void);

//=============================================================================
// function prototype
//=============================================================================

//=============================================================================
// variables
//=============================================================================


//=============================================================================
// Function parameter stubs
//=============================================================================
uint16              Fee_Read_unParam1;
uint16              Fee_Read_unParam2;
uint8*              Fee_Read_pucParam3;
uint16              Fee_Read_unParam4;

uint16              Fee_Write_unParam1;
uint8*              Fee_Write_pucParam2;

MemIf_ModeType      Fee_SetMode_eParam1;
uint16              Fee_InvalidateBlock_unParam1;
uint16              Fee_EraseImmediateBlock_unParam1;

//=============================================================================
// Function return value stubs
//=============================================================================
MemIf_JobResultType Fee_GetJobResult_eRetVal;
Std_ReturnType      Fee_Read_ucRetVal;
Std_ReturnType      Fee_Write_ucRetVal;
MemIf_StatusType    Fee_GetStatus_eRetVal;
Std_ReturnType      Fee_InvalidateBlock_ucRetVal;
Std_ReturnType      Fee_EraseImmediateBlock_ucRetVal;
Std_ReturnType      Fee_GetOpStatus_ucRetVal;

//=============================================================================
// Function hit counts
//=============================================================================
uint8               Fee_GetJobResult_ucHitCount;
uint8               Fee_Read_ucHitCount;
uint8               Fee_Write_ucHitCount;
uint8               Fee_GetStatus_ucHitCount;
uint8               Fee_SetMode_ucHitCount;
uint8               Fee_InvalidateBlock_ucHitCount;
uint8               Fee_EraseImmediateBlock_ucHitCount;
uint8               Fee_MainFunction_ucHitCount;
uint8               Fee_GetOpStatus_ucHitCount;

//=============================================================================
// functions
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief  Fee_Init
///
/// \descr  This function is a stub for Fee_Init
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void Fee_Init(void)
{
  return;
}

//-----------------------------------------------------------------------------
/// \brief  Fee_Read
///
/// \descr  This function is a stub for Fee_Read
///
/// \param  BlockNumber       : Number of logical block, which is the start address of that block in flash memory
/// \param  BlockOffset       : read address offset inside the block
/// \param  DataBufferPtr     : pointer to data buffer
/// \param  Length            : number of bytes to read
///
/// \return Std_ReturnType
///           E_OK: The requested job has been accepted by the module.
///           E_NOT_OK: The requested job has not been accepted by the module
//-----------------------------------------------------------------------------
Std_ReturnType Fee_Read(uint16 BlockNumber, uint16 BlockOffset, uint8* DataBufferPtr, uint16 Length)
{
  Fee_Read_unParam1   = BlockNumber;
  Fee_Read_unParam2   = BlockOffset;
  Fee_Read_pucParam3  = DataBufferPtr;
  Fee_Read_unParam4   = Length;

  Fee_Read_ucHitCount++;

  return Fee_Read_ucRetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Fee_write
///
/// \descr  This function is a stub for Fee_Write
///
/// \param  BlockNumber   : Number of logical block, which is the start address of that block in flash memory
/// \param  DataBufferPtr : pointer to data buffer
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Fee_Write(uint16 BlockNumber, uint8* DataBufferPtr)
{
  Fee_Write_unParam1  = BlockNumber;
  Fee_Write_pucParam2 = DataBufferPtr;

  Fee_Write_ucHitCount++;

  return Fee_Write_ucRetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Fee_GetStatus
///
/// \descr  This function is a stub for Fee_GetStatus
///
/// \param  -
///
/// \return MemIf_StatusType
//-----------------------------------------------------------------------------
MemIf_StatusType Fee_GetStatus(void)
{
  Fee_GetStatus_ucHitCount++;

  return Fee_GetStatus_eRetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Fee_SetMode
///
/// \descr  This function is a stub for Fee_SetMode
///
/// \param  Mode  : desired mode for underlying module
///
/// \return void
//-----------------------------------------------------------------------------
void Fee_SetMode(MemIf_ModeType Mode)
{
  Fee_SetMode_eParam1 = Mode;

  Fee_SetMode_ucHitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Fee_GetJobResult
///
/// \descr  This function is a stub for Fee_GetJobResult
///
/// \param  -
///
/// \return MemIf_JobResultType
//-----------------------------------------------------------------------------
MemIf_JobResultType Fee_GetJobResult(void)
{
  Fee_GetJobResult_ucHitCount++;

  return Fee_GetJobResult_eRetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Fee_InvalidateBlock
///
/// \descr  This function is a stub for Fee_InvalidateBlock
///
/// \param  BlockNumber : Number of logical block, which is the start address of that block in flash memory
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Fee_InvalidateBlock(uint16 BlockNumber)
{
  Fee_InvalidateBlock_unParam1 = BlockNumber;

  Fee_InvalidateBlock_ucHitCount++;

  return Fee_InvalidateBlock_ucRetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Fee_EraseImmediateBlock
///
/// \descr  This function is a stub for Fee_EraseImmediateBlock
///
/// \param  BlockNumber : Number of logical block, which is the start address of that block in flash memory
///
/// \return Std_ReturnType
//-----------------------------------------------------------------------------
Std_ReturnType Fee_EraseImmediateBlock(uint16 BlockNumber)
{
  Fee_EraseImmediateBlock_unParam1 = BlockNumber;

  Fee_EraseImmediateBlock_ucHitCount++;

  return Fee_EraseImmediateBlock_ucRetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Fee_MainFunction
///
/// \descr  This function is a stub for Fee_MainFunction
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void Fee_MainFunction(void)
{
  Fee_MainFunction_ucHitCount++;
}

//-----------------------------------------------------------------------------
/// \brief    Fee_GetOpStatus
///
/// \descr    This function is a stub for Fee_GetOpStatus
///
/// \param  -
///
/// \return Std_ReturnType
///           E_OK : previous operation has completed
///           E_NOT_OK: an operation is ongoing
//-----------------------------------------------------------------------------
Std_ReturnType Fee_GetOpStatus(void)
{
  Fee_GetOpStatus_ucHitCount++;

  return Fee_GetOpStatus_ucRetVal;
}

