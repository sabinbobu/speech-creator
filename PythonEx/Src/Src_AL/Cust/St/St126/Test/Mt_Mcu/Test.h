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

//=============================================================================
// Typedefs
//=============================================================================


//=============================================================================
// Defines
//=============================================================================


//=============================================================================
// Module global variables
//=============================================================================
extern S32_SCB_Type SCB_Register_Layout;
extern LMEM_Type LMem_Register_Layout;
extern RCM_Type RCM_Register_Layout;


//=============================================================================
// Module function declarations
//=============================================================================
extern void Mcu_Init(const Mcu_ConfigType* ConfigPtr);
extern Std_ReturnType Mcu_InitClock(Mcu_ClockType* ClockSetting);
extern Std_ReturnType Mcu_DistributePllClock(void);
extern Mcu_ResetType Mcu_GetResetReason(void);
extern void Mcu_PerformReset(void);

//=============================================================================
// Module function parameter stubs
//=============================================================================
Mcu_ConfigType* Mcu_Init_Param1;
Mcu_ClockType* Mcu_InitClock_Param1;

//=============================================================================
// Module function return value stubs
//=============================================================================
Std_ReturnType          Mcu_InitClock_RetVal;
Std_ReturnType          Mcu_DistributePllClock_RetVal;
Mcu_ResetType           Mcu_GetResetReason_RetVal;

#endif // TEST_2023_08_25_H_
