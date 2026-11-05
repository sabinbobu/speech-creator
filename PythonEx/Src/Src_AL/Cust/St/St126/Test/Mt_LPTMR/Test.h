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
#include <LPTMR.h>
#include "Test_Stubs.h"

//=============================================================================
// Typedefs
//=============================================================================

//=============================================================================
// Defines
//=============================================================================

//=============================================================================
// Module global variables
//=============================================================================

extern lptmr_config_t LPTMR_sTimerCfg_Init;
extern uint32         ulLPTMR0_MicrosecondTimer;

static const lptmr_config_t  lptmr_1_config0 = {
  // dmaRequest, interruptEnable, freeRun, workMode, 
  //clockSelect, prescaler, bypassPrescaler, compareValue, 
  //counterUnits, pinSelect, pinPolarity
  false, true, false,  LPTMR_WORKMODE_TIMER,
  LPTMR_CLOCKSOURCE_PCC, LPTMR_PRESCALE_16_GLITCHFILTER_8, false, 1000U,
  LPTMR_COUNTER_UNITS_TICKS, LPTMR_PINSELECT_TRGMUX, LPTMR_PINPOLARITY_RISING
};

const LPTMR_SpecificType LPTMR_Config =
{
  1U,
  (lptmr_config_t*)&lptmr_1_config0 // PRQA S 310, 311 // Necessary cast to avoid using ThirdParty structures
};

//=============================================================================
// Module function declarations
//=============================================================================

extern void    LPTMR_INIT(const LPTMR_ConfigType* ConfigPtr);
extern void    LPTMR0_IRQHandler(void);
extern uint32  LPTMR0_GetTimeElapsed(const uint32 ulStartValue);
extern boolean LPTMR_Check_ByPassPrescaler_Cfg(lptmr_config_t * const psLPTMRCfg);
extern boolean LPTMR_Check_ClkSelect_Cfg(lptmr_config_t * const psLPTMRCfg);
extern boolean LPTMR_Check_CompVal_Cfg(lptmr_config_t * const psLPTMRCfg);
extern boolean LPTMR_Check_CntUnit_Cfg(lptmr_config_t * const psLPTMRCfg);
extern boolean LPTMR_Check_DmaReq_Cfg(lptmr_config_t * const psLPTMRCfg);
extern boolean LPTMR_Check_FreeRun_Cfg(lptmr_config_t * const psLPTMRCfg);
extern boolean LPTMR_Check_IntEnbl_Cfg(lptmr_config_t * const psLPTMRCfg);
extern boolean LPTMR_Check_PinPol_Cfg(lptmr_config_t * const psLPTMRCfg);
extern boolean LPTMR_Check_PinSel_Cfg(lptmr_config_t * const psLPTMRCfg);
extern boolean LPTMR_Check_Prescaler_Cfg(lptmr_config_t * const psLPTMRCfg);
extern boolean LPTMR_Check_WorkMode_Cfg(lptmr_config_t * const psLPTMRCfg);
extern boolean LPTMR_Check_Config(void);


//=============================================================================
// Module function parameter stubs
//=============================================================================

LPTMR_ConfigType* LPTMR_INIT_Param1;
uint32            LPTMR0_GetTimeElapsed_Param1;
lptmr_config_t    LPTMR_Check_ByPassPrescaler_Cfg_Param1;
lptmr_config_t    LPTMR_Check_ClkSelect_Cfg_Param1;
lptmr_config_t    LPTMR_Check_CompVal_Cfg_Param1;
lptmr_config_t    LPTMR_Check_CntUnit_Cfg_Param1;
lptmr_config_t    LPTMR_Check_DmaReq_Cfg_Param1;
lptmr_config_t    LPTMR_Check_FreeRun_Cfg_Param1;
lptmr_config_t    LPTMR_Check_IntEnbl_Cfg_Param1;
lptmr_config_t    LPTMR_Check_PinPol_Cfg_Param1;
lptmr_config_t    LPTMR_Check_PinSel_Cfg_Param1;
lptmr_config_t    LPTMR_Check_Prescaler_Cfg_Param1;
lptmr_config_t    LPTMR_Check_WorkMode_Cfg_Param1;


//=============================================================================
// Module function return value stubs
//=============================================================================

uint32  LPTMR0_GetTimeElapsed_RetVal;
boolean LPTMR_Check_ByPassPrescaler_Cfg_RetVal;
boolean LPTMR_Check_ClkSelect_Cfg_RetVal;
boolean LPTMR_Check_CompVal_Cfg_RetVal;
boolean LPTMR_Check_CntUnit_Cfg_RetVal;
boolean LPTMR_Check_DmaReq_Cfg_RetVal;
boolean LPTMR_Check_FreeRun_Cfg_RetVal;
boolean LPTMR_Check_IntEnbl_Cfg_RetVal;
boolean LPTMR_Check_PinPol_Cfg_RetVal;
boolean LPTMR_Check_PinSel_Cfg_RetVal;
boolean LPTMR_Check_Prescaler_Cfg_RetVal;
boolean LPTMR_Check_WorkMode_Cfg_RetVal;
boolean LPTMR_Check_Config_RetVal;

#endif // TEST_2023_08_25_H_
