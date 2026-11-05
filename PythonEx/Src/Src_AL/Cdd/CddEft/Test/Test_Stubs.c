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
/// \file  Test_Stubs.c
///
/// \brief Stub functions for access to software modules excluded from test
///
//-----------------------------------------------------------------------------

//=============================================================================
// Includes
//=============================================================================
#include "Test_Stubs.h"

//=============================================================================
// Stub function parameter stubs
//=============================================================================
uint16               Dem_SetEventStatus_Param1;
uint8                Dem_SetEventStatus_Param2;
boolean              Dem_Set_Init_Window_Param1;
uint8*               Crc_CalculateCRC32_4C11DB7_Param1;
uint32               Crc_CalculateCRC32_4C11DB7_Param2;
uint32               Crc_CalculateCRC32_4C11DB7_Param3;

 //=============================================================================
 // Stub function returned value stubs
 //=============================================================================
uint32 Crc_CalculateCRC32_4C11DB7_RetVal;

//=============================================================================
// Stub function hit count variables
//=============================================================================
uint8 Dem_SetEventStatus_HitCount;
uint8 Dem_Set_Init_Window_HitCount;
uint8 Crc_CalculateCRC32_4C11DB7_HitCount;

//=============================================================================
// Stub function definitions
//=============================================================================

//-----------------------------------------------------------------------------
/// \brief  Crc_CalculateCRC8H1D
///
/// \descr  Stub function created to simulate the behaviour of Crc_CalculateCRC32_4C11DB7 
///
/// \param  pucCrc_DataPtr
/// \param  ulCrc_Length
/// \param  ulCrc_StartValue32
///
/// \return Crc_CalculateCRC8H1D_RetVal
//-----------------------------------------------------------------------------
uint32 Crc_CalculateCRC32_4C11DB7(CONST_AL uint8*  pucCrc_DataPtr, uint32  ulCrc_Length, uint32  ulCrc_StartValue32)
{
	Crc_CalculateCRC32_4C11DB7_Param1 = pucCrc_DataPtr;
	Crc_CalculateCRC32_4C11DB7_Param2 = ulCrc_Length;
	Crc_CalculateCRC32_4C11DB7_Param3 = ulCrc_StartValue32;

	Crc_CalculateCRC32_4C11DB7_HitCount++;

	return Crc_CalculateCRC32_4C11DB7_RetVal;
}

//-----------------------------------------------------------------------------
/// \brief  Dem_SetEventStatus
///
/// \descr  Stub function created to simulate the behaviour of Dem_SetEventStatus
///
/// \param  unAlecId
/// \param  ucTestStatus
///
/// \return void
//-----------------------------------------------------------------------------
void Dem_SetEventStatus(uint16 unAlecId, uint8 ucTestStatus)
{
	Dem_SetEventStatus_Param1 = unAlecId;
	Dem_SetEventStatus_Param2 = ucTestStatus;
	Dem_SetEventStatus_HitCount++;
}

//-----------------------------------------------------------------------------
/// \brief  Dem_Set_Init_Window
///
/// \descr  Stub function created to simulate the behaviour of Dem_Set_Init_Window
///
/// \param  Dem_Set_Init_Window_Param1
///
/// \return void
//-----------------------------------------------------------------------------
void  Dem_Set_Init_Window(boolean boWindow)
{
	Dem_Set_Init_Window_Param1 = boWindow;
	Dem_Set_Init_Window_HitCount++;
}
