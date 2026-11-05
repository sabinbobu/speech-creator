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
#include <Icu.h>

//=============================================================================
// Defines
//=============================================================================

//=============================================================================
// Typedefs
//=============================================================================

//=============================================================================
// Module global variables
//=============================================================================

extern ftm_input_ch_param_t sIcu_pal_configs_FTM0[2];

extern ftm_user_config_t sIcu_pal_info[1];
extern ftm_input_param_t sIcu_pal_configs[1];
extern uint32 ulIcu_pal_instances[1];
extern tsIcu_ConfigInstanceMap sIcu_Instance_Map[1U];

extern tsIcu_SpecificType sIcu_Config;

//=============================================================================
// Module function declarations
//=============================================================================


extern uint16 Icu_GetMeasurementSens(uint8 ucIdx);
extern void   Icu_ChangeMeasurementMode(uint8 ucIndex, uint8 ucMesMode);
extern void   Icu_Init(CONST_AL sIcu_ConfigType* ConfigPtr);


//=============================================================================
// Module function parameter stubs
//=============================================================================

uint8            Icu_GetMeasurementSens_Param1;
uint8            Icu_ChangeMeasurementMode_Param1;
uint8            Icu_ChangeMeasurementMode_Param2;
sIcu_ConfigType* Icu_Init_Param1;


//=============================================================================
// Module function return value stubs
//=============================================================================

uint16 Icu_GetMeasurementSens_RetVal;

//=============================================================================
// Module static variables inside functions 
//=============================================================================

//=============================================================================
// Module Global Stubs
//=============================================================================

ftm_state_t   ftmStatePtr1, ftmStatePtr2, ftmStatePtr3, ftmStatePtr4;
ftm_state_t* ftmStatePtr[4] = { &ftmStatePtr1 , &ftmStatePtr2 , &ftmStatePtr3 , &ftmStatePtr4 };
FTM_Type      g_ftmBase1, g_ftmBase2, g_ftmBase3, g_ftmBase4;
FTM_Type* g_ftmBase[4u] = { &g_ftmBase1 , &g_ftmBase2 , &g_ftmBase3 , &g_ftmBase4 };


#endif // TEST_2023_08_25_H_
