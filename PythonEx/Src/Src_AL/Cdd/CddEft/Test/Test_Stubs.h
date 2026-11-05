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

//=============================================================================
// Stub function declarations
//=============================================================================
void           Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus);
void           Dem_Set_Init_Window(boolean boWindow);
uint32         Crc_CalculateCRC32_4C11DB7(CONST_AL uint8*  pucCrc_DataPtr, uint32  ulCrc_Length, uint32  ulCrc_StartValue32);

//=============================================================================
// Stub function parameter stubs
//=============================================================================
extern uint16               Dem_SetEventStatus_Param1;
extern uint8                Dem_SetEventStatus_Param2;
extern boolean              Dem_Set_Init_Window_Param1;
extern uint8*               Crc_CalculateCRC32_4C11DB7_Param1;
extern uint32               Crc_CalculateCRC32_4C11DB7_Param2;
extern uint32               Crc_CalculateCRC32_4C11DB7_Param3;

//=============================================================================
// Stub function returned value stubs
//=============================================================================
extern uint32 Crc_CalculateCRC32_4C11DB7_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
extern uint8 Dem_SetEventStatus_HitCount;
extern uint8 Dem_Set_Init_Window_HitCount;
extern uint8 Crc_CalculateCRC32_4C11DB7_HitCount;


#endif // TEST_STUBS_2023_08_25_H_
