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
/// \file  Test.cpp
///
/// \brief Module test for ElecInt
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
//  Files covered by this module unit test:
//        Cust/St/St126/App/Swc/ElecInt:
//            - ctaaElecInt.c
//            - ElecInt.c
//=============================================================================
//=============================================================================
// includes
//=============================================================================
#include <ALUnitTest_UserInterface.h>

// Stub headers
#include "Test_Stubs.h"

// Headers of the unit test Module
#include "Test.h"


//=============================================================================
// Test Cases
//=============================================================================

//=============================================================================
// ctaaElecInt.c testcases coverage
//=============================================================================

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ElecInt_riElecInt_Init_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the initialization function riElecInt_Init is called.
///
/// - Preconditions:
///
/// \input  EAPI_InitModule_HitCount                 = 0u
/// \input  EAPI_SetSafetyConditions_HitCount        = 0u
/// \input  EAPI_SetSafetyConditions_Param1          = 0u
///
/// - Expectations:
///
/// \output EAPI_InitModule_HitCount                 = 1u
/// \output EAPI_SetSafetyConditions_HitCount        = 1u
/// \output EAPI_SetSafetyConditions_Param1          = 170u
///
//-----------------------------------------------------------------------------
void Mt_ElecInt_riElecInt_Init_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  EAPI_InitModule_HitCount                 = 0u;
  EAPI_SetSafetyConditions_HitCount        = 0u;
  EAPI_SetSafetyConditions_Param1          = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  riElecInt_Init();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(EAPI_InitModule_HitCount,               1u, == );
  AL_UNITTEST_CHECK(EAPI_SetSafetyConditions_HitCount,      1u, == );
  AL_UNITTEST_CHECK(EAPI_SetSafetyConditions_Param1,      170u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ElecInt_rpElecInt_Cycle_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the cyclic function rpElecInt_Cycle is called
///                        and Electronic Integration Mode is Entered.
///
/// - Preconditions:
///
/// \input  EAPI_MainFunction_HitCount              = 0u
/// \input  EAPI_MainFunction_RetVal                = 0u
/// \input  NM_ProhibitDefectMemorization_HitCount  = 0u
/// \input  NM_ProhibitDefectMemorization_Param1    = 0u
/// \input  DAPI_PermFifoStorage_HitCount           = 0u
/// \input  DAPI_PermFifoStorage_Param1             = 0u
/// \input  NM_CommunicationControl_HitCount        = 0u
/// \input  NM_CommunicationControl_Param1          = 0u
/// \input  NM_CommunicationControl_RetVal          = 0u
///
/// - Expectations:
///
/// \output EAPI_MainFunction_HitCount              = 1u
/// \output NM_ProhibitDefectMemorization_HitCount  = 1u
/// \output NM_ProhibitDefectMemorization_Param1    = 170u
/// \output DAPI_PermFifoStorage_HitCount           = 1u
/// \output DAPI_PermFifoStorage_Param1             = 0u
/// \output NM_CommunicationControl_HitCount        = 1u
/// \output NM_CommunicationControl_Param1          = 1u
///
//-----------------------------------------------------------------------------
void Mt_ElecInt_rpElecInt_Cycle_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  EAPI_MainFunction_HitCount              = 0u;
  EAPI_MainFunction_RetVal                = 0u;
  NM_ProhibitDefectMemorization_HitCount  = 0u;
  NM_ProhibitDefectMemorization_Param1    = 0u;
  DAPI_PermFifoStorage_HitCount           = 0u;
  DAPI_PermFifoStorage_Param1             = 0u;
  NM_CommunicationControl_HitCount        = 0u;
  NM_CommunicationControl_Param1          = 0u;
  NM_CommunicationControl_RetVal          = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  rpElecInt_Cycle();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(EAPI_MainFunction_HitCount,                  1u, == );
  AL_UNITTEST_CHECK(NM_ProhibitDefectMemorization_HitCount,      1u, == );
  AL_UNITTEST_CHECK(NM_ProhibitDefectMemorization_Param1,      170u, == );
  AL_UNITTEST_CHECK(DAPI_PermFifoStorage_HitCount,               1u, == );
  AL_UNITTEST_CHECK(DAPI_PermFifoStorage_Param1,                 0u, == );
  AL_UNITTEST_CHECK(NM_CommunicationControl_HitCount,            1u, == );
  AL_UNITTEST_CHECK(NM_CommunicationControl_Param1,              1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ElecInt_rpElecInt_Cycle_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if the cyclic function rpElecInt_Cycle is called.
///                        and Electronic Integration Mode is Exited.
///
/// - Preconditions:
///
/// \input  EAPI_MainFunction_HitCount              = 0u
/// \input  EAPI_MainFunction_RetVal                = 1u
/// \input  NM_ProhibitDefectMemorization_HitCount  = 0u
/// \input  NM_ProhibitDefectMemorization_Param1    = 0u
/// \input  DAPI_PermFifoStorage_HitCount           = 0u
/// \input  DAPI_PermFifoStorage_Param1             = 0u
/// \input  NM_GetMode_HitCount                     = 0u
/// \input  NM_GetMode_Param1                       = 0u
/// \input  NM_GetMode_RetVal                       = 0u
/// \input  NM_CommunicationControl_HitCount        = 0u
/// \input  NM_CommunicationControl_Param1          = 0u
/// \input  NM_CommunicationControl_RetVal          = 0u
///
/// - Expectations:
///
/// \output EAPI_MainFunction_HitCount              = 1u
/// \output NM_ProhibitDefectMemorization_HitCount  = 1u
/// \output NM_ProhibitDefectMemorization_Param1    = 85u
/// \input  DAPI_PermFifoStorage_HitCount           = 1u
/// \input  DAPI_PermFifoStorage_Param1             = 1u
/// \output NM_GetMode_HitCount                     = 1u
/// \output NM_GetMode_Param1                       = 0u
/// \output NM_CommunicationControl_HitCount        = 0u
/// \output NM_CommunicationControl_Param1          = 0u
///
//-----------------------------------------------------------------------------
void Mt_ElecInt_rpElecInt_Cycle_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  EAPI_MainFunction_HitCount              = 0u;
  EAPI_MainFunction_RetVal                = 1u;
  NM_ProhibitDefectMemorization_HitCount  = 0u;
  NM_ProhibitDefectMemorization_Param1    = 0u;
  DAPI_PermFifoStorage_HitCount           = 0u;
  DAPI_PermFifoStorage_Param1             = 0u;
  NM_GetMode_HitCount                     = 0u;
  NM_GetMode_Param1                       = 0u;
  NM_GetMode_RetVal                       = 0u;
  NM_CommunicationControl_HitCount        = 0u;
  NM_CommunicationControl_Param1          = 0u;
  NM_CommunicationControl_RetVal          = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  rpElecInt_Cycle();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(EAPI_MainFunction_HitCount,                  1u, == );
  AL_UNITTEST_CHECK(NM_ProhibitDefectMemorization_HitCount,      1u, == );
  AL_UNITTEST_CHECK(NM_ProhibitDefectMemorization_Param1,       85u, == );
  AL_UNITTEST_CHECK(DAPI_PermFifoStorage_HitCount,               1u, == );
  AL_UNITTEST_CHECK(DAPI_PermFifoStorage_Param1,                 1u, == );
  AL_UNITTEST_CHECK(NM_GetMode_HitCount,                         1u, == );
  AL_UNITTEST_CHECK(NM_GetMode_Param1,                           0u, == );
  AL_UNITTEST_CHECK(NM_CommunicationControl_HitCount,            0u, == );
  AL_UNITTEST_CHECK(NM_CommunicationControl_Param1,              0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ElecInt_rpElecInt_Cycle_TestCase_3
///
/// \Test Case Description
///        - Test subject: Test if the cyclic function rpElecInt_Cycle is called.
///
/// - Preconditions:
///
/// \input  EAPI_MainFunction_HitCount              = 0u
/// \input  EAPI_MainFunction_RetVal                = 1u
/// \input  NM_ProhibitDefectMemorization_HitCount  = 0u
/// \input  NM_ProhibitDefectMemorization_Param1    = 0u
/// \input  NM_GetMode_HitCount                     = 0u
/// \input  NM_GetMode_Param1                       = 5u
/// \input  NM_GetMode_RetVal                       = 0u
/// \input  NM_CommunicationControl_HitCount        = 0u
/// \input  NM_CommunicationControl_Param1          = 0u
/// \input  NM_CommunicationControl_RetVal          = 0u
///
/// - Expectations:
///
/// \output EAPI_MainFunction_HitCount              = 1u
/// \output NM_ProhibitDefectMemorization_HitCount  = 1u
/// \output NM_ProhibitDefectMemorization_Param1    = 85u
/// \output NM_GetMode_HitCount                     = 1u
/// \output NM_GetMode_Param1                       = 5u
/// \output NM_CommunicationControl_HitCount        = 1u
/// \output NM_CommunicationControl_Param1          = 0u
///
//-----------------------------------------------------------------------------
void Mt_ElecInt_rpElecInt_Cycle_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  EAPI_MainFunction_HitCount              = 0u;
  EAPI_MainFunction_RetVal                = 1u;
  NM_ProhibitDefectMemorization_HitCount  = 0u;
  NM_ProhibitDefectMemorization_Param1    = 0u;
  NM_GetMode_HitCount                     = 0u;
  NM_GetMode_Param1                       = 5u;
  NM_GetMode_RetVal                       = 0u;
  NM_CommunicationControl_HitCount        = 0u;
  NM_CommunicationControl_Param1          = 0u;
  NM_CommunicationControl_RetVal          = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  rpElecInt_Cycle();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(EAPI_MainFunction_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(NM_ProhibitDefectMemorization_HitCount,     1u, == );
  AL_UNITTEST_CHECK(NM_ProhibitDefectMemorization_Param1,      85u, == );
  AL_UNITTEST_CHECK(NM_GetMode_HitCount,                        1u, == );
  AL_UNITTEST_CHECK(NM_GetMode_Param1,                          5u, == );
  AL_UNITTEST_CHECK(NM_CommunicationControl_HitCount,           1u, == );
  AL_UNITTEST_CHECK(NM_CommunicationControl_Param1,             0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ElecInt_rpElecInt_Cycle_TestCase_4
///
/// \Test Case Description
///        - Test subject: Test if the cyclic function rpElecInt_Cycle is called
///                        and Electronic Integration Mode is not Entered or Exited.
///
/// - Preconditions:
///
/// \input  EAPI_MainFunction_HitCount              = 0u
/// \input  EAPI_MainFunction_RetVal                = 9u
/// \input  NM_ProhibitDefectMemorization_HitCount  = 0u
/// \input  NM_ProhibitDefectMemorization_Param1    = 0u
/// \input  DAPI_PermFifoStorage_HitCount           = 0u
/// \input  DAPI_PermFifoStorage_Param1             = 0u
/// \input  NM_GetMode_HitCount                     = 0u
/// \input  NM_GetMode_Param1                       = 0u
/// \input  NM_GetMode_RetVal                       = 0u
/// \input  NM_CommunicationControl_HitCount        = 0u
/// \input  NM_CommunicationControl_Param1          = 0u
/// \input  NM_CommunicationControl_RetVal          = 0u
///
/// - Expectations:
///
/// \output EAPI_MainFunction_HitCount              = 1u
/// \output NM_ProhibitDefectMemorization_HitCount  = 0u
/// \output NM_ProhibitDefectMemorization_Param1    = 0u
/// \input  DAPI_PermFifoStorage_HitCount           = 0u
/// \input  DAPI_PermFifoStorage_Param1             = 0u
/// \output NM_GetMode_HitCount                     = 0u
/// \output NM_GetMode_Param1                       = 0u
/// \output NM_CommunicationControl_HitCount        = 0u
/// \output NM_CommunicationControl_Param1          = 0u
///
//-----------------------------------------------------------------------------
void Mt_ElecInt_rpElecInt_Cycle_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  EAPI_MainFunction_HitCount              = 0u;
  EAPI_MainFunction_RetVal                = 9u;
  NM_ProhibitDefectMemorization_HitCount  = 0u;
  NM_ProhibitDefectMemorization_Param1    = 0u;
  DAPI_PermFifoStorage_HitCount           = 0u;
  DAPI_PermFifoStorage_Param1             = 0u;
  NM_GetMode_HitCount                     = 0u;
  NM_GetMode_Param1                       = 0u;
  NM_GetMode_RetVal                       = 0u;
  NM_CommunicationControl_HitCount        = 0u;
  NM_CommunicationControl_Param1          = 0u;
  NM_CommunicationControl_RetVal          = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  rpElecInt_Cycle();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(EAPI_MainFunction_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(NM_ProhibitDefectMemorization_HitCount,     0u, == );
  AL_UNITTEST_CHECK(NM_ProhibitDefectMemorization_Param1,       0u, == );
  AL_UNITTEST_CHECK(DAPI_PermFifoStorage_HitCount,              0u, == );
  AL_UNITTEST_CHECK(DAPI_PermFifoStorage_Param1,                0u, == );
  AL_UNITTEST_CHECK(NM_GetMode_HitCount,                        0u, == );
  AL_UNITTEST_CHECK(NM_GetMode_Param1,                          0u, == );
  AL_UNITTEST_CHECK(NM_CommunicationControl_HitCount,           0u, == );
  AL_UNITTEST_CHECK(NM_CommunicationControl_Param1,             0u, == );
}

//=============================================================================
// ElecInt.c testcases coverage
//=============================================================================

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ElecInt_Com_Loss_Callback_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the cyclic function Com_Loss_Callback is called.
///
/// - Preconditions:
///
/// \input  DAPI_SetPermToSend_HitCount             = 0u
/// \input  DAPI_SetPermToSend_Param1               = 0u
/// \input  EAPI_GetCurrentEIMode_HitCount          = 0u
/// \input  EAPI_GetCurrentEIMode_RetVal            = 0u
/// \input  NM_CommunicationControl_HitCount        = 0u
/// \input  NM_CommunicationControl_Param1          = 0u
/// \input  NM_CommunicationControl_RetVal          = 0u
/// \input  NM_ProhibitDefectMemorization_HitCount  = 0u
/// \input  NM_ProhibitDefectMemorization_Param1    = 0u
///
/// - Expectations:
///
/// \output DAPI_SetPermToSend_HitCount             = 1u
/// \output DAPI_SetPermToSend_Param1               = 0u
/// \output EAPI_GetCurrentEIMode_HitCount          = 1u
/// \output NM_CommunicationControl_HitCount        = 1u
/// \output NM_CommunicationControl_Param1          = 1u
/// \output NM_ProhibitDefectMemorization_HitCount  = 0u
/// \output NM_ProhibitDefectMemorization_Param1    = 0u
///
//-----------------------------------------------------------------------------
void Mt_ElecInt_Com_Loss_Callback_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  DAPI_SetPermToSend_HitCount             = 0u;
  DAPI_SetPermToSend_Param1               = 0u;
  EAPI_GetCurrentEIMode_HitCount          = 0u;
  EAPI_GetCurrentEIMode_RetVal            = 0u;
  NM_CommunicationControl_HitCount        = 0u;
  NM_CommunicationControl_Param1          = 0u;
  NM_CommunicationControl_RetVal          = 0u;
  NM_ProhibitDefectMemorization_HitCount  = 0u;
  NM_ProhibitDefectMemorization_Param1    = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  Com_Loss_Callback();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(DAPI_SetPermToSend_HitCount,                  1u, == );
  AL_UNITTEST_CHECK(DAPI_SetPermToSend_Param1,                    0u, == );
  AL_UNITTEST_CHECK(EAPI_GetCurrentEIMode_HitCount,               1u, == );
  AL_UNITTEST_CHECK(NM_CommunicationControl_HitCount,             1u, == );
  AL_UNITTEST_CHECK(NM_CommunicationControl_Param1,               1u, == );
  AL_UNITTEST_CHECK(NM_ProhibitDefectMemorization_HitCount,       0u, == );
  AL_UNITTEST_CHECK(NM_ProhibitDefectMemorization_Param1,         0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ElecInt_Com_Loss_Callback_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if the cyclic function Com_Loss_Callback is called.
///
/// - Preconditions:
///
/// \input  DAPI_SetPermToSend_HitCount             = 0u
/// \input  DAPI_SetPermToSend_Param1               = 0u
/// \input  EAPI_GetCurrentEIMode_HitCount          = 0u
/// \input  EAPI_GetCurrentEIMode_RetVal            = 9u
/// \input  NM_CommunicationControl_HitCount        = 0u
/// \input  NM_CommunicationControl_Param1          = 0u
/// \input  NM_CommunicationControl_RetVal          = 0u
/// \input  NM_ProhibitDefectMemorization_HitCount  = 0u
/// \input  NM_ProhibitDefectMemorization_Param1    = 0u
///
/// - Expectations:
///
/// \output DAPI_SetPermToSend_HitCount             = 1u
/// \output DAPI_SetPermToSend_Param1               = 0u
/// \output EAPI_GetCurrentEIMode_HitCount          = 1u
/// \output NM_CommunicationControl_HitCount        = 0u
/// \output NM_CommunicationControl_Param1          = 0u
/// \output NM_ProhibitDefectMemorization_HitCount  = 1u
/// \output NM_ProhibitDefectMemorization_Param1    = 85u
///
//-----------------------------------------------------------------------------
void Mt_ElecInt_Com_Loss_Callback_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  DAPI_SetPermToSend_HitCount             = 0u;
  DAPI_SetPermToSend_Param1               = 0u;
  EAPI_GetCurrentEIMode_HitCount          = 0u;
  EAPI_GetCurrentEIMode_RetVal            = 9u;
  NM_CommunicationControl_HitCount        = 0u;
  NM_CommunicationControl_Param1          = 0u;
  NM_CommunicationControl_RetVal          = 0u;
  NM_ProhibitDefectMemorization_HitCount  = 0u;
  NM_ProhibitDefectMemorization_Param1    = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  Com_Loss_Callback();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(DAPI_SetPermToSend_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(DAPI_SetPermToSend_Param1,                   0u, == );
  AL_UNITTEST_CHECK(EAPI_GetCurrentEIMode_HitCount,              1u, == );
  AL_UNITTEST_CHECK(NM_CommunicationControl_HitCount,            0u, == );
  AL_UNITTEST_CHECK(NM_CommunicationControl_Param1,              0u, == );
  AL_UNITTEST_CHECK(NM_ProhibitDefectMemorization_HitCount,      1u, == );
  AL_UNITTEST_CHECK(NM_ProhibitDefectMemorization_Param1,       85u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ElecInt_Normal_Request_Callback_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the cyclic function Normal_Request_Callback is called.
///
/// - Preconditions:
///
/// \input  DAPI_SetPermToSend_HitCount                 = 0u
/// \input  DAPI_SetPermToSend_Param1                   = 0u
/// \input  EAPI_GetCurrentEIMode_HitCount              = 0u
/// \input  EAPI_GetCurrentEIMode_RetVal                = 0u
/// \input  NM_CommunicationControl_HitCount            = 0u
/// \input  NM_CommunicationControl_Param1              = 0u
/// \input  NM_CommunicationControl_RetVal              = 0u
/// \input  NM_ProhibitDefectMemorization_HitCount      = 0u
/// \input  NM_ProhibitDefectMemorization_Param1        = 0u
/// \input  EcuM_RequestRUN_HitCount                    = 0u
/// \input  EcuM_ReleasePOST_RUN_HitCount               = 0u
/// \input  EcuM_RequestRUN_Param1                      = 0u
/// \input  EcuM_ReleasePOST_RUN_Param1                 = 0u
/// \input  Rte_Write_ElecInt_EnableCallbacks_HitCount  = 0u
/// \input  Rte_Write_ElecInt_EnableCallbacks_Param1    = 0u
/// \input  Rte_Write_ElecInt_ActivateTxBufer_HitCount  = 0u
/// \input  Rte_Write_ElecInt_ActivateTxBufer_Param1    = 0u
/// \input  SigPrepRx_ComM_EnableCallbacks_HitCount     = 0u
/// \input  SigPrepTx_ComM_ActivateTxBufer_HitCount     = 0u
///
/// - Expectations:
///
/// \output DAPI_SetPermToSend_HitCount                 = 1u
/// \output DAPI_SetPermToSend_Param1                   = 1u
/// \output EAPI_GetCurrentEIMode_HitCount              = 1u
/// \output NM_CommunicationControl_HitCount            = 1u
/// \output NM_CommunicationControl_Param1              = 1u
/// \output NM_ProhibitDefectMemorization_HitCount      = 0u
/// \output NM_ProhibitDefectMemorization_Param1        = 0u
/// \output EcuM_RequestRUN_Param1                      = 0u
/// \output EcuM_ReleasePOST_RUN_Param1                 = 0u
/// \output SigPrepRx_ComM_EnableCallbacks_HitCount     = 1u
/// \output SigPrepTx_ComM_ActivateTxBufer_HitCount     = 1u
/// \output Rte_Write_ElecInt_EnableCallbacks_HitCount  = 1u
/// \output Rte_Write_ElecInt_EnableCallbacks_Param1    = TRUE
/// \output Rte_Write_ElecInt_ActivateTxBufer_HitCount  = 1u
/// \output Rte_Write_ElecInt_ActivateTxBufer_Param1    = TRUE
///
//-----------------------------------------------------------------------------
void Mt_ElecInt_Normal_Request_Callback_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  DAPI_SetPermToSend_HitCount                = 0u;
  DAPI_SetPermToSend_Param1                  = 0u;
  EAPI_GetCurrentEIMode_HitCount             = 0u;
  EAPI_GetCurrentEIMode_RetVal               = 0u;
  NM_CommunicationControl_HitCount           = 0u;
  NM_CommunicationControl_Param1             = 0u;
  NM_CommunicationControl_RetVal             = 0u;
  NM_ProhibitDefectMemorization_HitCount     = 0u;
  NM_ProhibitDefectMemorization_Param1       = 0u;
  EcuM_RequestRUN_HitCount                   = 0u;
  EcuM_ReleasePOST_RUN_HitCount              = 0u;
  EcuM_RequestRUN_Param1                     = 0u;
  EcuM_ReleasePOST_RUN_Param1                = 0u;
  SigPrepRx_ComM_EnableCallbacks_HitCount    = 0u;
  SigPrepTx_ComM_ActivateTxBufer_HitCount    = 0u;
  Rte_Write_ElecInt_EnableCallbacks_HitCount = 0u;
  Rte_Write_ElecInt_EnableCallbacks_Param1   = 0u;
  Rte_Write_ElecInt_ActivateTxBufer_HitCount = 0u;
  Rte_Write_ElecInt_ActivateTxBufer_Param1   = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  Normal_Request_Callback();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(DAPI_SetPermToSend_HitCount,                  1u, == );
  AL_UNITTEST_CHECK(DAPI_SetPermToSend_Param1,                    1u, == );
  AL_UNITTEST_CHECK(EAPI_GetCurrentEIMode_HitCount,               1u, == );
  AL_UNITTEST_CHECK(NM_CommunicationControl_HitCount,             1u, == );
  AL_UNITTEST_CHECK(NM_CommunicationControl_Param1,               1u, == );
  AL_UNITTEST_CHECK(NM_ProhibitDefectMemorization_HitCount,       0u, == );
  AL_UNITTEST_CHECK(NM_ProhibitDefectMemorization_Param1,         0u, == );
  AL_UNITTEST_CHECK(EcuM_RequestRUN_Param1,                       0u, == );
  AL_UNITTEST_CHECK(EcuM_ReleasePOST_RUN_Param1,                  0u, == );
  AL_UNITTEST_CHECK(SigPrepRx_ComM_EnableCallbacks_HitCount,      1u, == );
  AL_UNITTEST_CHECK(SigPrepTx_ComM_ActivateTxBufer_HitCount,      1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_EnableCallbacks_HitCount,   1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_EnableCallbacks_Param1,   TRUE, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_ActivateTxBufer_HitCount,   1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_ActivateTxBufer_Param1,   TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ElecInt_Normal_Request_Callback_TestCase_2
///
/// \Test Case Description
///        - Test subject: Test if the cyclic function Normal_Request_Callback is called.
///
/// - Preconditions:
///
/// \input  DAPI_SetPermToSend_HitCount                 = 0u
/// \input  DAPI_SetPermToSend_Param1                   = 0u
/// \input  EAPI_GetCurrentEIMode_HitCount              = 0u
/// \input  EAPI_GetCurrentEIMode_RetVal                = 9u
/// \input  NM_CommunicationControl_HitCount            = 0u
/// \input  NM_CommunicationControl_Param1              = 0u
/// \input  NM_CommunicationControl_RetVal              = 0u
/// \input  NM_ProhibitDefectMemorization_HitCount      = 0u
/// \input  NM_ProhibitDefectMemorization_Param1        = 0u
/// \input  EcuM_RequestRUN_HitCount                    = 0u
/// \input  EcuM_ReleasePOST_RUN_HitCount               = 0u
/// \input  EcuM_RequestRUN_Param1                      = 0u
/// \input  EcuM_ReleasePOST_RUN_Param1                 = 0u
/// \input  Rte_Write_ElecInt_RequestRUN_Param1         = 1u
/// \input  Rte_Write_ElecInt_ReleasePOST_RUN_Param1    = 1u
/// \input  SigPrepRx_ComM_EnableCallbacks_HitCount     = 0u
/// \input  SigPrepTx_ComM_ActivateTxBufer_HitCount     = 0u
/// \input  Rte_Write_ElecInt_EnableCallbacks_HitCount  = 0u
/// \input  Rte_Write_ElecInt_EnableCallbacks_Param1    = 0u
/// \input  Rte_Write_ElecInt_ActivateTxBufer_HitCount  = 0u
/// \input  Rte_Write_ElecInt_ActivateTxBufer_Param1    = 0u
///
/// - Expectations:
///
/// \output DAPI_SetPermToSend_HitCount                 = 1u
/// \output DAPI_SetPermToSend_Param1                   = 1u
/// \output EAPI_GetCurrentEIMode_HitCount              = 1u
/// \output NM_CommunicationControl_HitCount            = 0u
/// \output NM_CommunicationControl_Param1              = 0u
/// \output NM_ProhibitDefectMemorization_HitCount      = 1u
/// \output NM_ProhibitDefectMemorization_Param1        = 85u
/// \output EcuM_RequestRUN_HitCount                    = 1u
/// \output EcuM_ReleasePOST_RUN_HitCount               = 1u
/// \output EcuM_RequestRUN_Param1                      = 0u
/// \output EcuM_ReleasePOST_RUN_Param1                 = 0u
/// \output Rte_Write_ElecInt_RequestRUN_Param1         = 0u
/// \output Rte_Write_ElecInt_ReleasePOST_RUN_Param1    = 0u
/// \output SigPrepRx_ComM_EnableCallbacks_HitCount     = 1u
/// \output SigPrepTx_ComM_ActivateTxBufer_HitCount     = 1u
/// \output Rte_Write_ElecInt_EnableCallbacks_HitCount  = 1u
/// \output Rte_Write_ElecInt_EnableCallbacks_Param1    = TRUE
/// \output Rte_Write_ElecInt_ActivateTxBufer_HitCount  = 1u
/// \output Rte_Write_ElecInt_ActivateTxBufer_Param1    = TRUE
///
//-----------------------------------------------------------------------------
void Mt_ElecInt_Normal_Request_Callback_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  DAPI_SetPermToSend_HitCount                 = 0u;
  DAPI_SetPermToSend_Param1                   = 0u;
  EAPI_GetCurrentEIMode_HitCount              = 0u;
  EAPI_GetCurrentEIMode_RetVal                = 9u;
  NM_CommunicationControl_HitCount            = 0u;
  NM_CommunicationControl_Param1              = 0u;
  NM_CommunicationControl_RetVal              = 0u;
  NM_ProhibitDefectMemorization_HitCount      = 0u;
  NM_ProhibitDefectMemorization_Param1        = 0u;
  EcuM_RequestRUN_HitCount                    = 0u;
  EcuM_ReleasePOST_RUN_HitCount               = 0u;
  EcuM_RequestRUN_Param1                      = 0u;
  EcuM_ReleasePOST_RUN_Param1                 = 0u;
  SigPrepRx_ComM_EnableCallbacks_HitCount     = 0u;
  SigPrepTx_ComM_ActivateTxBufer_HitCount     = 0u;
  Rte_Write_ElecInt_RequestRUN_Param1         = 1u;
  Rte_Write_ElecInt_ReleasePOST_RUN_Param1    = 1u;
  Rte_Write_ElecInt_EnableCallbacks_HitCount  = 0u;
  Rte_Write_ElecInt_EnableCallbacks_Param1    = 0u;
  Rte_Write_ElecInt_ActivateTxBufer_HitCount  = 0u;
  Rte_Write_ElecInt_ActivateTxBufer_Param1    = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  Normal_Request_Callback();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(DAPI_SetPermToSend_HitCount,                    1u, == );
  AL_UNITTEST_CHECK(DAPI_SetPermToSend_Param1,                      1u, == );
  AL_UNITTEST_CHECK(EAPI_GetCurrentEIMode_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(NM_CommunicationControl_HitCount,               0u, == );
  AL_UNITTEST_CHECK(NM_CommunicationControl_Param1,                 0u, == );
  AL_UNITTEST_CHECK(NM_ProhibitDefectMemorization_HitCount,         1u, == );
  AL_UNITTEST_CHECK(NM_ProhibitDefectMemorization_Param1,          85u, == );
  AL_UNITTEST_CHECK(EcuM_RequestRUN_Param1,                         0u, == );
  AL_UNITTEST_CHECK(EcuM_ReleasePOST_RUN_Param1,                    0u, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_RequestRUN_Param1,            0u, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_ReleasePOST_RUN_Param1,       0u, == );
  AL_UNITTEST_CHECK(SigPrepRx_ComM_EnableCallbacks_HitCount,        1u, == );
  AL_UNITTEST_CHECK(SigPrepTx_ComM_ActivateTxBufer_HitCount,        1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_EnableCallbacks_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_EnableCallbacks_Param1,     TRUE, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_ActivateTxBufer_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_ActivateTxBufer_Param1,     TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ElecInt_Wake_Up_Request_Callback_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the cyclic function Wake_Up_Request_Callback is called.
///
/// - Preconditions:
///
/// \input  SigPrepRx_ComM_DisableCallbacks_HitCount    = 0u
/// \input  SigPrepTx_ComM_DeactivateTxBuffer_HitCount  = 0u
/// \input  Rte_Write_ElecInt_EnableCallbacks_HitCount  = 0u
/// \input  Rte_Write_ElecInt_EnableCallbacks_Param1    = 0u
/// \input  Rte_Write_ElecInt_ActivateTxBufer_HitCount  = 0u
/// \input  Rte_Write_ElecInt_ActivateTxBufer_Param1    = 0u
///
/// - Expectations:
///
/// \output SigPrepRx_ComM_DisableCallbacks_HitCount    = 1u
/// \output SigPrepTx_ComM_DeactivateTxBuffer_HitCount  = 1u
/// \output Rte_Write_ElecInt_EnableCallbacks_HitCount  = 1u
/// \output Rte_Write_ElecInt_EnableCallbacks_Param1    = FALSE
/// \output Rte_Write_ElecInt_ActivateTxBufer_HitCount  = 1u
/// \output Rte_Write_ElecInt_ActivateTxBufer_Param1    = FALSE
///
//-----------------------------------------------------------------------------
void Mt_ElecInt_Wake_Up_Request_Callback_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SigPrepRx_ComM_DisableCallbacks_HitCount    = 0u;
  SigPrepTx_ComM_DeactivateTxBuffer_HitCount  = 0u;
  Rte_Write_ElecInt_EnableCallbacks_HitCount  = 0u;
  Rte_Write_ElecInt_EnableCallbacks_Param1    = 0u;
  Rte_Write_ElecInt_ActivateTxBufer_HitCount  = 0u;
  Rte_Write_ElecInt_ActivateTxBufer_Param1    = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  Wake_Up_Request_Callback();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SigPrepRx_ComM_DisableCallbacks_HitCount,       1u, == );
  AL_UNITTEST_CHECK(SigPrepTx_ComM_DeactivateTxBuffer_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_EnableCallbacks_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_EnableCallbacks_Param1,    FALSE, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_ActivateTxBufer_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_ActivateTxBufer_Param1,    FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ElecInt_Sleep_Callback_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the cyclic function Sleep_Callback is called.
///
/// - Preconditions:
///
/// \input  SigPrepRx_ComM_DisableCallbacks_HitCount    = 0u
/// \input  SigPrepTx_ComM_DeactivateTxBuffer_HitCount  = 0u
/// \input  Rte_Write_ElecInt_EnableCallbacks_HitCount  = 0u
/// \input  Rte_Write_ElecInt_EnableCallbacks_Param1    = 0u
/// \input  Rte_Write_ElecInt_ActivateTxBufer_HitCount  = 0u
/// \input  Rte_Write_ElecInt_ActivateTxBufer_Param1    = 0u
///
/// - Expectations:
///
/// \output SigPrepRx_ComM_DisableCallbacks_HitCount    = 1u
/// \output SigPrepTx_ComM_DeactivateTxBuffer_HitCount  = 1u
/// \output Rte_Write_ElecInt_EnableCallbacks_HitCount  = 1u
/// \output Rte_Write_ElecInt_EnableCallbacks_Param1    = FALSE
/// \output Rte_Write_ElecInt_ActivateTxBufer_HitCount  = 1u
/// \output Rte_Write_ElecInt_ActivateTxBufer_Param1    = FALSE
///
//-----------------------------------------------------------------------------
void Mt_ElecInt_Sleep_Callback_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SigPrepRx_ComM_DisableCallbacks_HitCount    = 0u;
  SigPrepTx_ComM_DeactivateTxBuffer_HitCount  = 0u;
  Rte_Write_ElecInt_EnableCallbacks_HitCount  = 0u;
  Rte_Write_ElecInt_EnableCallbacks_Param1    = 0u;
  Rte_Write_ElecInt_ActivateTxBufer_HitCount  = 0u;
  Rte_Write_ElecInt_ActivateTxBufer_Param1    = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  Sleep_Callback();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SigPrepRx_ComM_DisableCallbacks_HitCount,       1u, == );
  AL_UNITTEST_CHECK(SigPrepTx_ComM_DeactivateTxBuffer_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_EnableCallbacks_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_EnableCallbacks_Param1,    FALSE, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_ActivateTxBufer_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_ActivateTxBufer_Param1,    FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ElecInt_Sleep_Request_Callback_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the cyclic function Sleep_Request_Callback is called.
///
/// - Preconditions:
///
/// \input  SigPrepRx_ComM_DisableCallbacks_HitCount    = 0u
/// \input  SigPrepTx_ComM_DeactivateTxBuffer_HitCount  = 0u
/// \input  Rte_Write_ElecInt_EnableCallbacks_HitCount  = 0u
/// \input  Rte_Write_ElecInt_EnableCallbacks_Param1    = 0u
/// \input  Rte_Write_ElecInt_ActivateTxBufer_HitCount  = 0u
/// \input  Rte_Write_ElecInt_ActivateTxBufer_Param1    = 0u
/// \input  Rte_Write_ElecInt_ReleaseRUN_Param1         = 0u
/// \input  Rte_Write_ElecInt_ReleaseRUN_HitCount       = 0u
///
/// - Expectations:
///
/// \output SigPrepRx_ComM_DisableCallbacks_HitCount    = 1u
/// \output SigPrepTx_ComM_DeactivateTxBuffer_HitCount  = 1u
/// \output Rte_Write_ElecInt_EnableCallbacks_HitCount  = 1u
/// \output Rte_Write_ElecInt_EnableCallbacks_Param1    = FALSE
/// \output Rte_Write_ElecInt_ActivateTxBufer_HitCount  = 1u
/// \output Rte_Write_ElecInt_ActivateTxBufer_Param1    = FALSE
/// \output Rte_Write_ElecInt_ReleaseRUN_Param1         = 0u
/// \output Rte_Write_ElecInt_ReleaseRUN_HitCount       = 1u
///
//-----------------------------------------------------------------------------
void Mt_ElecInt_Sleep_Request_Callback_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SigPrepRx_ComM_DisableCallbacks_HitCount    = 0u;
  SigPrepTx_ComM_DeactivateTxBuffer_HitCount  = 0u;
  Rte_Write_ElecInt_EnableCallbacks_HitCount  = 0u;
  Rte_Write_ElecInt_EnableCallbacks_Param1    = 0u;
  Rte_Write_ElecInt_ActivateTxBufer_HitCount  = 0u;
  Rte_Write_ElecInt_ActivateTxBufer_Param1    = 0u;
  Rte_Write_ElecInt_ReleaseRUN_Param1         = 0u;
  Rte_Write_ElecInt_ReleaseRUN_HitCount       = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  Sleep_Request_Callback();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SigPrepRx_ComM_DisableCallbacks_HitCount,       1u, == );
  AL_UNITTEST_CHECK(SigPrepTx_ComM_DeactivateTxBuffer_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_EnableCallbacks_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_EnableCallbacks_Param1,    FALSE, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_ActivateTxBufer_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_ActivateTxBufer_Param1,    FALSE, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_ReleaseRUN_Param1,            0u, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_ReleaseRUN_HitCount,          1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ElecInt_Com_Off_Request_Callback_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the cyclic function Com_Off_Request_Callback is called.
///
/// - Preconditions:
///
/// \input  SigPrepRx_ComM_DisableCallbacks_HitCount    = 0u
/// \input  SigPrepTx_ComM_DeactivateTxBuffer_HitCount  = 0u
/// \input  Rte_Write_ElecInt_EnableCallbacks_HitCount  = 0u
/// \input  Rte_Write_ElecInt_EnableCallbacks_Param1    = 0u
/// \input  Rte_Write_ElecInt_ActivateTxBufer_HitCount  = 0u
/// \input  Rte_Write_ElecInt_ActivateTxBufer_Param1    = 0u
///
/// - Expectations:
///
/// \output SigPrepRx_ComM_DisableCallbacks_HitCount    = 1u
/// \output SigPrepTx_ComM_DeactivateTxBuffer_HitCount  = 1u
/// \output Rte_Write_ElecInt_EnableCallbacks_HitCount  = 1u
/// \output Rte_Write_ElecInt_EnableCallbacks_Param1    = FALSE
/// \output Rte_Write_ElecInt_ActivateTxBufer_HitCount  = 1u
/// \output Rte_Write_ElecInt_ActivateTxBufer_Param1    = FALSE
///
//-----------------------------------------------------------------------------
void Mt_ElecInt_Com_Off_Request_Callback_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  SigPrepRx_ComM_DisableCallbacks_HitCount    = 0u;
  SigPrepTx_ComM_DeactivateTxBuffer_HitCount  = 0u;
  Rte_Write_ElecInt_EnableCallbacks_HitCount  = 0u;
  Rte_Write_ElecInt_EnableCallbacks_Param1    = 0u;
  Rte_Write_ElecInt_ActivateTxBufer_HitCount  = 0u;
  Rte_Write_ElecInt_ActivateTxBufer_Param1    = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  Com_Off_Request_Callback();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(SigPrepRx_ComM_DisableCallbacks_HitCount,       1u, == );
  AL_UNITTEST_CHECK(SigPrepTx_ComM_DeactivateTxBuffer_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_EnableCallbacks_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_EnableCallbacks_Param1,    FALSE, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_ActivateTxBufer_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_ActivateTxBufer_Param1,    FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ElecInt_Connected_Callback_TestCase_1
///
/// \Test Case Description
///        - Test subject: Test if the cyclic function Connected_Callback is called.
///
/// - Preconditions:
///
/// \input  Rte_Write_ElecInt_RequestRUN_HitCount  = 0u
/// \input  Rte_Write_ElecInt_RequestRUN_Param1    = 0u
///
/// - Expectations:
///
/// \output Rte_Write_ElecInt_RequestRUN_HitCount  = 1u
/// \output Rte_Write_ElecInt_RequestRUN_Param1    = 0u
///
//-----------------------------------------------------------------------------
void Mt_ElecInt_Connected_Callback_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //-----------------------------------------------------------------------------

  Rte_Write_ElecInt_RequestRUN_HitCount  = 0u;
  Rte_Write_ElecInt_RequestRUN_Param1    = 0u;

  //-----------------------------------------------------------------------------
  // Function call
  //-----------------------------------------------------------------------------

  Connected_Callback();

  //-----------------------------------------------------------------------------
  // Outputs
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_ElecInt_RequestRUN_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ElecInt_RequestRUN_Param1,       0u, == );
}


//=============================================================================
// Test Cases
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief  ALUnitTest_AddTests
///
/// \descr  Every test case shall be added to this list
///
/// \param  -
///
/// \return void
//-----------------------------------------------------------------------------
void ALUnitTest_AddTests(void)
{
  ALUnitTest_AddFunction("Mt_ElecInt_riElecInt_Init_TestCase_1", Mt_ElecInt_riElecInt_Init_TestCase_1);
  ALUnitTest_AddFunction("Mt_ElecInt_rpElecInt_Cycle_TestCase_1", Mt_ElecInt_rpElecInt_Cycle_TestCase_1);
  ALUnitTest_AddFunction("Mt_ElecInt_rpElecInt_Cycle_TestCase_2", Mt_ElecInt_rpElecInt_Cycle_TestCase_2);
  ALUnitTest_AddFunction("Mt_ElecInt_rpElecInt_Cycle_TestCase_3", Mt_ElecInt_rpElecInt_Cycle_TestCase_3);
  ALUnitTest_AddFunction("Mt_ElecInt_rpElecInt_Cycle_TestCase_4", Mt_ElecInt_rpElecInt_Cycle_TestCase_4);
  ALUnitTest_AddFunction("Mt_ElecInt_Com_Loss_Callback_TestCase_1", Mt_ElecInt_Com_Loss_Callback_TestCase_1);
  ALUnitTest_AddFunction("Mt_ElecInt_Com_Loss_Callback_TestCase_2", Mt_ElecInt_Com_Loss_Callback_TestCase_2);
  ALUnitTest_AddFunction("Mt_ElecInt_Normal_Request_Callback_TestCase_1", Mt_ElecInt_Normal_Request_Callback_TestCase_1);
  ALUnitTest_AddFunction("Mt_ElecInt_Normal_Request_Callback_TestCase_2", Mt_ElecInt_Normal_Request_Callback_TestCase_2);
  ALUnitTest_AddFunction("Mt_ElecInt_Wake_Up_Request_Callback_TestCase_1", Mt_ElecInt_Wake_Up_Request_Callback_TestCase_1);
  ALUnitTest_AddFunction("Mt_ElecInt_Sleep_Callback_TestCase_1", Mt_ElecInt_Sleep_Callback_TestCase_1);
  ALUnitTest_AddFunction("Mt_ElecInt_Sleep_Request_Callback_TestCase_1", Mt_ElecInt_Sleep_Request_Callback_TestCase_1);
  ALUnitTest_AddFunction("Mt_ElecInt_Com_Off_Request_Callback_TestCase_1", Mt_ElecInt_Com_Off_Request_Callback_TestCase_1);
  ALUnitTest_AddFunction("Mt_ElecInt_Connected_Callback_TestCase_1", Mt_ElecInt_Connected_Callback_TestCase_1);
}


// EOF
