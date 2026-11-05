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
#include <Std_Types.h>
#include <Dio.h>

//=============================================================================
// Typedefs
//=============================================================================


//=============================================================================
// Defines
//=============================================================================


//=============================================================================
// Module global variables
//=============================================================================
extern CONST_AL ChannelIdMap_t Dio_ChannelMap[];

//=============================================================================
// Module function declarations
//=============================================================================
extern void Dio_Init(const Dio_ConfigType* ConfigPtr);
extern void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);
extern Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

//=============================================================================
// Module function parameter stubs
//=============================================================================
Dio_ChannelType Dio_WriteChannel_Param1;
Dio_LevelType   Dio_WriteChannel_Param2;
Dio_ChannelType Dio_ReadChannel_Param1;

//=============================================================================
// Module function return value stubs
//=============================================================================
Dio_LevelType Dio_ReadChannel_RetVal;

#endif // TEST_2023_08_25_H_
