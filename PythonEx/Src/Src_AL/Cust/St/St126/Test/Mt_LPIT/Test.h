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
#include <ALUnitTest_UserInterface.h>
#include <AL_Helper.h>
#include <Lpit.h>
#include <LPTMR.h>
#include <Lpit_reg_stubs.h>

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
// Module gunction declarations
//=============================================================================

//=============================================================================
// Module function parameter stubs
//=============================================================================

tsLpit_CfgData* Lpit_Init_Param1;

tsLpit_LpitTmrCfg Lpit_LpitSetTmrEnblBit_Param1;
uint32 Lpit_LpitSetTmrEnblBit_Param2;

tsLpit_LpitTmrCfg Lpit_LpitSetTmrChCompVal_Param1;
uint32 Lpit_LpitSetTmrChCompVal_Param2;

tsLpit_LpitTmrCfg Lpit_LpitSetTmrChIntEnbl_Param1;
uint32 Lpit_LpitSetTmrChIntEnbl_Param2;

tsLpit_LpitTmrCfg Lpit_LpitReturnCount_Param1;

tsLpit_LpitTmrCfg Lpit_LpitClearTimeout_Param1;

uint8 Lpit_ClearInterruptFlag_Param1;
uint8 Lpit_ClearInterruptFlag_Param2;

uint8 Lpit_TmrChannelEnable_Param1;
uint8 Lpit_TmrChannelEnable_Param2;

LPIT_Type Lpit_Drv_LpitSetDebugMode_Param1;
uint32 Lpit_Drv_LpitSetDebugMode_Param2;

LPIT_Type Lpit_Drv_LpitSetDozeMode_Param1;
uint32 Lpit_Drv_LpitSetDozeMode_Param2;

LPIT_Type Lpit_Drv_LpitSetModEnblStat_Param1;
uint32 Lpit_Drv_LpitSetModEnblStat_Param2;

tsLpit_LpitTmrCfg Lpit_Drv_LpitSetTmrChMode_Param1;
uint32 Lpit_Drv_LpitSetTmrChMode_Param2;

tsLpit_LpitTmrCfg Lpit_Drv_LpitSetTmrChTrigSrc_Param1;
uint32 Lpit_Drv_LpitSetTmrChTrigSrc_Param2;

tsLpit_LpitTmrCfg Lpit_Drv_LpitSetTmrChTrigSel_Param1;
uint32 Lpit_Drv_LpitSetTmrChTrigSel_Param2;

tsLpit_LpitTmrCfg Lpit_Drv_LpitSetTmrChRoT_Param1;
uint32 Lpit_Drv_LpitSetTmrChRoT_Param2;

tsLpit_LpitTmrCfg Lpit_Drv_LpitSetTmrChSoI_Param1;
uint32 Lpit_Drv_LpitSetTmrChSoI_Param2;

tsLpit_LpitTmrCfg Lpit_Drv_LpitSetTmrChSoT_Param1;
uint32 Lpit_Drv_LpitSetTmrChSoT_Param2;

tsLpit_LpitTmrCfg Lpit_Drv_LpitSetTmrChChain_Param1;
uint32 Lpit_Drv_LpitSetTmrChChain_Param2;

tsLpit_LpitTmrCfg Lpit_LpitSetTmrEnable_Param1;
boolean Lpit_LpitSetTmrEnable_Param2;

tsLpit_LpitTmrCfg Lpit_InitLpitTmrChn_Param1;

tsLpit_LpitInstanceCfg* Lpit_InitLpitInstance_Param1;

tsLpit_LpitTmrCfg Lpit_Drv_LpitSetTmrEnblBit_Param1;
uint32 Lpit_Drv_LpitSetTmrEnblBit_Param2;

tsLpit_LpitTmrCfg Lpit_Drv_LpitReturnCount_Param1;

uint8 Lpit_Drv_ClearInterruptFlag_Param1;
uint8 Lpit_Drv_ClearInterruptFlag_Param2;

uint8 Lpit_Drv_TimerChannelEnable_Param1;
uint8 Lpit_Drv_TimerChannelEnable_Param2;

tsLpit_LpitTmrCfg Lpit_Drv_LpitSetTmrChCompVal_Param1;
uint32 Lpit_Drv_LpitSetTmrChCompVal_Param2;

tsLpit_LpitTmrCfg Lpit_Drv_LpitClearTimeout_Param1;

tsLpit_LpitTmrCfg Lpit_Drv_LpitSetTmrChIntEnbl_Param1;
uint32 Lpit_Drv_LpitSetTmrChIntEnbl_Param2;

tsLpit_CfgData* Lpit_Drv_Init_Param1;

//=============================================================================
// Module function return value stubs
//=============================================================================


uint32 Lpit_LpitReturnCount_RetVal;
uint32 Lpit_Drv_LpitReturnCount_RetVal;
Std_ReturnType Lpit_Drv_Init_RetVal;

#endif // TEST_2023_08_25_H_
