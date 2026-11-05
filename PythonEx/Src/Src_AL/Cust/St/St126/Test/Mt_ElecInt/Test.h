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
#include <ElecInt.h>


//=============================================================================
// Module function declarations
//=============================================================================
extern void  riElecInt_Init(void);
extern void  rpElecInt_Cycle(void);
extern void  ElecInt_Init(void);
extern void  ElecInt_Cycle(void);
extern void  ElecInt_EnterEIMMode(void);
extern void  Com_Loss_Callback(void);
extern void  ElecInt_ExitEIMMode(void);
extern void  Normal_Request_Callback(void);
extern void  Wake_Up_Request_Callback(void);
extern void  Sleep_Callback(void);
extern void  Sleep_Request_Callback(void);
extern void  Com_Off_Request_Callback(void);
extern void  Connected_Callback(void);


#endif // TEST_2023_08_25_H_
