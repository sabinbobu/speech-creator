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
#include <RteCommonTypes.h>
#include <../App/Swc/CodM/CodM.h>
#include <../CodM/CodM_Para.h>
#include <Std_Types.h>
#include <CodM_Para.h>
#include <CodM_Types.h>

//=============================================================================
// Typedefs
//=============================================================================

//=============================================================================
// Defines
//=============================================================================

//=============================================================================
// Module global variables
//=============================================================================

//=============================================================================
// Module function declarations
//=============================================================================

extern void    CodM_InitModules(tParaFct0_Cmd eCmd);
extern void    CodM_Init(void);
extern void    rpCodM_Cycle0(void);
extern void    riCodM_Init(void);
extern void    CodM_Cycle0(void);

//=============================================================================
// Module function parameter stubs
//=============================================================================

tParaFct0_Cmd              CodM_InitModules_Param1;
tParaFct0_Cmd              CodM_InitModules_Param2;
tsRteCodingParameters      CodM_InitModules_Param3;

//=============================================================================
// Module function return value stubs
//=============================================================================

//=============================================================================
// Module static variables inside functions 
//=============================================================================

volatile unsigned char           CalibrationRom[];
extern boolean                   CodM_boPavDataValid;
extern boolean                   boSteeringWhl_FlagRx;
extern CONST_AL pCalibrationData CalibrationData;
extern boolean                   boSteeringWhl_FlagRx;
tieFeeState                      Fee_State;
MemIf_JobResultType              Fee_JobResult;

#endif // TEST_2023_08_25_H_