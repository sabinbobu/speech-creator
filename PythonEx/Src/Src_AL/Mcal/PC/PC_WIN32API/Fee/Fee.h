#ifndef _FEE_H_
#define _FEE_H_

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
/// \file   Fee.h
///
/// \brief  Header file for Fee.c
///
/// \descr  Functions used for Flash EEPROM EMULATION
///         Types of Fee Block structures and commands
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------

#include <MemIf_Types.h>

  #define _MAC_ENUM
//lint -e451 Header file repeatedly included but does not have a standard include guard
  #include <Fee_Cfg.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
  #undef  _MAC_ENUM


  #define _MAC_EXTERN
//lint -e451 Header file repeatedly included but does not have a standard include guard
  #include <Bsw/Mcal/Fee/Fee_Cfg.h>
//lint +e451 Header file repeatedly included but does not have a standard include guard
  #undef _MAC_EXTERN


//=============================================================================
// Exported Functions Declaration
//=============================================================================
// Flash access functions
  void Fee_Init(void);
  void Fee_SetMode(MemIf_ModeType Mode);
  void Fee_MainFunction(void);

  MemIf_StatusType Fee_GetStatus(void);
  MemIf_JobResultType Fee_GetJobResult(void);

  Std_ReturnType Fee_Read(uint16 BlockNumber,uint16 BlockOffset, uint8* DataBufferPtr, uint16 Length);
  Std_ReturnType Fee_Write(uint16 BlockNumber, uint8* DataBufferPtr);
  Std_ReturnType Fee_InvalidateBlock(uint16 BlockNumber);
  Std_ReturnType Fee_EraseImmediateBlock(uint16 BlockNumber);
  Std_ReturnType Fee_GetOpStatus(void);

#if FEE_USE_FEE_FORMAT == STD_ON
  Std_ReturnType Fee_Format(void);
#endif


//=============================================================================
// Function parameter stubs
//=============================================================================
extern uint16              Fee_Read_unParam1;
extern uint16              Fee_Read_unParam2;
extern uint8*              Fee_Read_pucParam3;
extern uint16              Fee_Read_unParam4;
extern uint16              Fee_Write_unParam1;
extern uint8*              Fee_Write_pucParam2;
extern MemIf_ModeType      Fee_SetMode_eParam1;
extern uint16              Fee_InvalidateBlock_unParam1;
extern uint16              Fee_EraseImmediateBlock_unParam1;

//=============================================================================
// Function return value stubs
//=============================================================================
extern MemIf_JobResultType Fee_GetJobResult_eRetVal;
extern Std_ReturnType      Fee_Read_ucRetVal;
extern Std_ReturnType      Fee_Write_ucRetVal;
extern MemIf_StatusType    Fee_GetStatus_eRetVal;
extern Std_ReturnType      Fee_InvalidateBlock_ucRetVal;
extern Std_ReturnType      Fee_EraseImmediateBlock_ucRetVal;
extern Std_ReturnType      Fee_GetOpStatus_ucRetVal;

//=============================================================================
// Function hit counts
//=============================================================================
extern uint8               Fee_GetJobResult_ucHitCount;
extern uint8               Fee_Read_ucHitCount;
extern uint8               Fee_Write_ucHitCount;
extern uint8               Fee_GetStatus_ucHitCount;
extern uint8               Fee_SetMode_ucHitCount;
extern uint8               Fee_InvalidateBlock_ucHitCount;
extern uint8               Fee_EraseImmediateBlock_ucHitCount;
extern uint8               Fee_MainFunction_ucHitCount;
extern uint8               Fee_GetOpStatus_ucHitCount;


#endif /*_FEE_H_ */
