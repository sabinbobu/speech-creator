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
#include <UtilUtility.h>

// Headers of the Module
#include <CddVn7140_Types.h>

//=============================================================================
// Typedefs
//=============================================================================

//=============================================================================
// Defines
//=============================================================================
#define CFG_VN7140_OUTPUTS_CNT         (2u)  // Number of Switch

//=============================================================================
// Module global variables
//=============================================================================
extern boolean                CddVn7140_boCodingValid;
extern boolean                CddVn7140_boEftValid;
extern tsCddVn7140_States     CddVn7140_asStates[CFG_VN7140_OUTPUTS_CNT];
extern uint16                 CddVn7140_aunOpenLoadThreshold[CFG_VN7140_OUTPUTS_CNT];
extern uint16                 CddVn7140_aunShort2GndThreshold[CFG_VN7140_OUTPUTS_CNT];
extern uint16                 CddVn7140_aunShort2VbatThreshold[CFG_VN7140_OUTPUTS_CNT];
extern uint16                 CddVn7140_unCurrentRsens;
extern uint16                 CddVn7140_HSSErrorWait;
extern boolean                CddVn7140_boHssSupport[CFG_VN7140_OUTPUTS_CNT];

//=============================================================================
// Module function declarations
//=============================================================================
extern void                   CddVn7140_Init(CONST_AL uint32 ulChipIdx);
extern void                   CddVn7140_Cycle0(void);
extern void                   CddVn7140_SetTgt(CONST_AL uint32 ulChipIdx, CONST_AL uint32 ulOutIdx, CONST_AL uint16 unTgtVal);
extern tsCddVn7140_DrvStatus  CddVn7140_GetState(CONST_AL uint32 ulChipIdx, CONST_AL uint32 ulOutIdx);
extern void                   CddVn7140_ReadDiagVal(void);
extern void                   CddVn7140_Diag_CheckAllErrors(void);
extern void                   CddVn7140_CheckOpenload(uint32 ulChIdx);
extern void                   CddVn7140_CheckShort2GND(uint32 ulChIdx);
extern void                   CddVn7140_CheckShort2VBAT(uint32 ulChIdx);
extern void                   CddVn7140_DeInit(CONST_AL uint32 ulChipIdx);
extern void                   CddVn7140_InitCodingParams(void);

//=============================================================================
// Module function parameter stubs
//=============================================================================
uint32                        CddVn7140_Init_Param1;
uint32                        CddVn7140_SetTgt_Param1;
uint32                        CddVn7140_SetTgt_Param2;
uint16                        CddVn7140_SetTgt_Param3;
uint32                        CddVn7140_GetState_Param1;
uint32                        CddVn7140_GetState_Param2;
uint32                        CddVn7140_CheckOpenload_Param1;
uint32                        CddVn7140_CheckShort2GND_Param1;
uint32                        CddVn7140_CheckShort2VBAT_Param1;
uint32                        CddVn7140_DeInit_Param1;

//=============================================================================
// Module function return value stubs
//=============================================================================
tsCddVn7140_DrvStatus         CddVn7140_GetState_RetVal;

//=============================================================================
// Module static variables inside functions 
//=============================================================================

#endif // TEST_2023_08_25_H_
