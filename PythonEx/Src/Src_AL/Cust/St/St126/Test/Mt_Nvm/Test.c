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
/// \file  Test.c
///
/// \brief  Unit Test Cases for Nvm module
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
//  Files covered by this module unit test:
//        Gen/Bsw/NvM:
//            - ctaaNvm.c
//            - Nvm.c
//            - Nvm_Id.c
//            - Nvm_Internal.c
//        Cust/St/St126/App/Bsw/Nvm:
//            - Nvm_Cfg.c
//=============================================================================

//=============================================================================
// Includes
//=============================================================================

// Standard unit test header
#include <ALUnitTest_UserInterface.h>
#include <stdio.h>
#include <string.h>

// Stub headers
#include "Test_Stubs.h"

// Headers of the unit test Module
#include "Test.h"

//=============================================================================
// Test Cases
//=============================================================================

//-----------------------------------------------------------------------------
//ctaaNvm.c
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_riNvM_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the internal flags are initialized with default values
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    NvM_boInitialized = FALSE
/// \input    NvM_eState        = NVM_STATE_NOT_INIT
///
/// - Expectations: 
///
/// \output   NvM_boInitialized = TRUE
/// \output   NvM_eState        = NVM_STATE_IDLE
///
//-----------------------------------------------------------------------------
void Mt_riNvM_Init(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_boInitialized           = FALSE;
  NvM_eState                  = NVM_STATE_NOT_INIT;

  //Step 3) Call FUT
  riNvM_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_boInitialized,            TRUE, == );
  AL_UNITTEST_CHECK(NvM_eState,         NVM_STATE_IDLE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpNvM_Cycle0_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that rpNvM_Cycle0 recalls the initialization runnable
///                     in case it was missed
///
///    - Test Design Technique:  Requirements-based test
///
/// - Preconditions:
///             NvM_Init() already called, but unsuccessfully
/// \input    NvM_boInitialized = FALSE
///
/// - Expectations: 
///
/// \output   NvM_boInitialized = TRUE
///
//-----------------------------------------------------------------------------
void Mt_rpNvM_Cycle0_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_boInitialized     = FALSE;

  //Step 3) Call FUT
  rpNvM_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_boInitialized, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpNvM_Cycle0_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that rpNvM_Cycle0 starts the state machine and
///                     updates the state of the Nvm
///
///    - Test Design Technique:  Requirements-based test
///
///    - Preconditions:
/// \input    NvM_eState         = NVM_STATE_IDLE
/// \input    NvM_boNeedsRewrite = TRUE
///
/// - Expectations: 
/// \output   NvM_eState         = NVM_STATE_IDLE
/// \output   NvM_boNeedsRewrite = FALSE
///
//-----------------------------------------------------------------------------
void Mt_rpNvM_Cycle0_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_eState          = NVM_STATE_IDLE;
  NvM_boNeedsRewrite  = TRUE;

  //Step 3) Call FUT
  rpNvM_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_eState,         NVM_STATE_IDLE, == );
  AL_UNITTEST_CHECK(NvM_boNeedsRewrite,          FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpNvM_Cycle0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test the cyclic runnable behaviour of the NVM 
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing) 
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_rpNvM_Cycle0(void)
{
  Mt_rpNvM_Cycle0_TestCase1();
  Mt_rpNvM_Cycle0_TestCase2();
}

//-----------------------------------------------------------------------------
//Nvm.c
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if the init function sets the NVM state to default
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    NvM_eState = NVM_STATE_NOT_INIT
///
/// - Expectations: 
///
/// \output   NvM_eState = NVM_STATE_IDLE
///
//-----------------------------------------------------------------------------
void Mt_NvM_Init(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_eState       = NVM_STATE_NOT_INIT;

  //Step 3) Call FUT
  NvM_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_eState, NVM_STATE_IDLE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_MainFunction
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test if NvM_MainFunction function starts the
///                         Nvm State Machine
///
///    - Test Design Technique:  Requirements-based test
///
/// - Preconditions:
///
/// \input    NvM_eState              = NVM_STATE_IDLE
/// \input    NvM_boNeedsRewrite      = TRUE
///
/// - Expectations: 
///
/// \output   NvM_eState              = NVM_STATE_IDLE
/// \output   NvM_boNeedsRewrite      = FALSE
///
//-----------------------------------------------------------------------------
void Mt_NvM_MainFunction(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_eState              = NVM_STATE_IDLE;
  NvM_boNeedsRewrite      = TRUE;

  //Step 3) Call FUT
  NvM_MainFunction();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_eState,         NVM_STATE_IDLE, == );
  AL_UNITTEST_CHECK(NvM_boNeedsRewrite,          FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_GetState
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:
///        Check if the function NvM_GetState returns the correct state of the Nvm module
///
///    - Test Design Technique: DT (Decision Table)
///
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT.
///
///      - DT-Info:
///         - Inputs:
///            actualState :  known value of internal variable before calling FUT
///         - Expected results
///            returnedState : expected return value by the FUT
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions:
///
//-----------------------------------------------------------------------------
void Mt_NvM_GetState(void)
{
  typedef struct tsTestCaseDataInput
  {
    tieNvMState actualState;
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    tieNvMState returnedState;
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput  sInputData;
    tsTestCaseDataOutput sOutputData;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    //           Inputs                                || Outputs
    // actual state                                    || returned state
    {  {  NVM_STATE_NOT_INIT                  }         ,  {NVM_STATE_NOT_INIT                  } },
    {  {  NVM_STATE_IDLE                      }         ,  {NVM_STATE_IDLE                      } },
    {  {  NVM_STATE_WRITE_BLOCK               }         ,  {NVM_STATE_WRITE_BLOCK               } },
    {  {  NVM_STATE_WRITE_ALL                 }         ,  {NVM_STATE_WRITE_ALL                 } },
    {  {  NVM_STATE_READ_BLOCK                }         ,  {NVM_STATE_READ_BLOCK                } },
    {  {  NVM_STATE_READ_ALL                  }         ,  {NVM_STATE_READ_ALL                  } },
    {  {  NVM_STATE_RESTORE_BLOCK_DEFAULTS    }         ,  {NVM_STATE_RESTORE_BLOCK_DEFAULTS    } },
    {  {  NVM_STATE_SETDATAINDEX              }         ,  {NVM_STATE_SETDATAINDEX              } },
    {  {  NVM_STATE_GETDATAINDEX              }         ,  {NVM_STATE_GETDATAINDEX              } },
    {  {  NVM_STATE_SETRAMBLOCKSTATUS         }         ,  {NVM_STATE_SETRAMBLOCKSTATUS         } },
    {  {  NVM_STATE_INVALIDATE_NV_BLOCK       }         ,  {NVM_STATE_INVALIDATE_NV_BLOCK       } },
  };

  for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
  {
    //Step 1: Set pre-conditions

    //Step 2) Assign Input values
    NvM_eState          = asTestCaseData[ucIdx].sInputData.actualState;

    //Step 3) Call FUT
    NvM_GetState_RetVal = NvM_GetState();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(NvM_GetState_RetVal, asTestCaseData[ucIdx].sOutputData.returnedState, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_WriteAll
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if the function initiates a multi block write request
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    NvM_AdminMultiBlock.MultiBlockState         = NVM_STATE_IDLE
/// \input    NvM_AdminMultiBlock.MultiBlockSubState      = NVM_MB_SUB_STATE_PROCESS_BLOCKS
/// \input    NvM_AdminMultiBlock.ErrorStatus             = NVM_REQ_NOT_OK
/// \input    NvM_AdminMultiBlock.SingleBlockErrorStatus  = NVM_REQ_NOT_OK
///
/// - Expectations: 
///
/// \output   NvM_AdminMultiBlock.MultiBlockState         = NVM_STATE_WRITE_ALL
/// \output   NvM_AdminMultiBlock.MultiBlockSubState      = NVM_MB_SUB_STATE_INIT
/// \output   NvM_AdminMultiBlock.ErrorStatus             = NVM_REQ_PENDING
/// \output   NvM_AdminMultiBlock.SingleBlockErrorStatus  = NVM_REQ_OK
///
//-----------------------------------------------------------------------------
void Mt_NvM_WriteAll(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_AdminMultiBlock.MultiBlockState             = NVM_STATE_IDLE;
  NvM_AdminMultiBlock.MultiBlockSubState          = NVM_MB_SUB_STATE_PROCESS_BLOCKS;
  NvM_AdminMultiBlock.ErrorStatus                 = NVM_REQ_NOT_OK;
  NvM_AdminMultiBlock.SingleBlockErrorStatus      = NVM_REQ_NOT_OK;

  //Step 3) Call FUT
  NvM_WriteAll();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.MultiBlockState,      NVM_STATE_WRITE_ALL, == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.MultiBlockSubState, NVM_MB_SUB_STATE_INIT, == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.ErrorStatus,              NVM_REQ_PENDING, == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.SingleBlockErrorStatus,        NVM_REQ_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_ReadAll
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if the function initiates a multi block read request
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    NvM_AdminMultiBlock.MultiBlockState         = NVM_STATE_IDLE
/// \input    NvM_AdminMultiBlock.MultiBlockSubState      = NVM_MB_SUB_STATE_PROCESS_BLOCKS
/// \input    NvM_AdminMultiBlock.ErrorStatus             = NVM_REQ_NOT_OK
/// \input    NvM_AdminMultiBlock.SingleBlockErrorStatus  = NVM_REQ_NOT_OK
/// - Expectations: 
///
/// \output   NvM_AdminMultiBlock.MultiBlockState         = NVM_STATE_READ_ALL
/// \output   NvM_AdminMultiBlock.MultiBlockSubState      = NVM_MB_SUB_STATE_INIT
/// \output   NvM_AdminMultiBlock.ErrorStatus             = NVM_REQ_PENDING
/// \output   NvM_AdminMultiBlock.SingleBlockErrorStatus  = NVM_REQ_OK
///
//-----------------------------------------------------------------------------
void Mt_NvM_ReadAll(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_AdminMultiBlock.MultiBlockState               = NVM_STATE_IDLE;
  NvM_AdminMultiBlock.MultiBlockSubState            = NVM_MB_SUB_STATE_PROCESS_BLOCKS;
  NvM_AdminMultiBlock.ErrorStatus                   = NVM_REQ_NOT_OK;
  NvM_AdminMultiBlock.SingleBlockErrorStatus        = NVM_REQ_NOT_OK;

  //Step 3) Call FUT
  NvM_ReadAll();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.MultiBlockState,        NVM_STATE_READ_ALL, == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.MultiBlockSubState,  NVM_MB_SUB_STATE_INIT, == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.ErrorStatus,               NVM_REQ_PENDING, == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.SingleBlockErrorStatus,         NVM_REQ_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_CancelWriteAll
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if the function cancels a previously started WriteAll request
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    UtilMemClr_HitCount    = 0u
///
/// - Expectations: 
///
/// \output   UtilMemClr_HitCount    = 1u
///
//-----------------------------------------------------------------------------
void Mt_NvM_CancelWriteAll(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  UtilMemClr_HitCount = 0u;

  //Step 3) Call FUT
  NvM_CancelWriteAll();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilMemClr_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_GetErrorStatus_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test if the function reads the block dependent error 
///                         status information
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input     NvM_GetErrorStatus_Param1      = 0u (NvmBlockMultiBlockRequestId)
/// \input     NvM_GetErrorStatus_Param2      = 1u
///
/// - Expectations: 
///
/// \output   NvM_GetErrorStatus_RetVal       = E_OK 
/// \output   NvM_GetErrorStatus_Param2       = NVM_REQ_PENDING
///
//-----------------------------------------------------------------------------
void Mt_NvM_GetErrorStatus_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_GetErrorStatus_Param1    = 0u;
  NvM_GetErrorStatus_Param2    = 1u;

  //Step 3) Call FUT
  NvM_GetErrorStatus_RetVal    = NvM_GetErrorStatus(NvM_GetErrorStatus_Param1, &NvM_GetErrorStatus_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_GetErrorStatus_RetVal,            E_OK, == );
  AL_UNITTEST_CHECK(NvM_GetErrorStatus_Param2, NVM_REQ_PENDING, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_GetErrorStatus_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test if the function reads the block dependent error 
///                         status information
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input     NvM_GetErrorStatus_Param1      = 1u (other NV Block)
/// \input     NvM_GetErrorStatus_Param2      = 1u
///
/// - Expectations: 
///
/// \output   NvM_GetErrorStatus_RetVal       = E_OK 
/// \output   NvM_GetErrorStatus_Param2       = NVM_REQ_BLOCK_SKIPPED
///
//-----------------------------------------------------------------------------
void Mt_NvM_GetErrorStatus_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_GetErrorStatus_Param1      = 1u;
  NvM_GetErrorStatus_Param2      = 1u;
                                 
  //Step 3) Call FUT             
  NvM_GetErrorStatus_RetVal      = NvM_GetErrorStatus(NvM_GetErrorStatus_Param1, &NvM_GetErrorStatus_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_GetErrorStatus_RetVal,                  E_OK, == );
  AL_UNITTEST_CHECK(NvM_GetErrorStatus_Param2, NVM_REQ_BLOCK_SKIPPED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_GetErrorStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the function reads the block error status
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_NvM_GetErrorStatus(void)
{
  Mt_NvM_GetErrorStatus_TestCase1();
  Mt_NvM_GetErrorStatus_TestCase2();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_WriteBlock_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject::     Test if the function reports error for a request out of
///                         the accepted range (Nvm Block Count)
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input      NvM_WriteBlock_Param1      = NvMBlockCount + 1
/// \input      NvM_WriteBlock_Param2      = 1u
///
/// - Expectations: 
///
/// \output   NvM_WriteBlock_RetVal       = E_NOT_OK
///
//-----------------------------------------------------------------------------
void Mt_NvM_WriteBlock_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_WriteBlock_Param1     = NvMBlockCount + 1;
  NvM_WriteBlock_Param2     = 1u;

  //Step 3) Call FUT
  NvM_WriteBlock_RetVal     = NvM_WriteBlock(NvM_WriteBlock_Param1, &NvM_WriteBlock_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_WriteBlock_RetVal, E_NOT_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_WriteBlock_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test if the function accepts the request of writing
///                         data from RAM block to the corresponding NV block
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    NvM_WriteBlock_Param1           = 1u
/// \input    NvM_WriteBlock_Param2           = 1u
///
/// - Expectations: 
///
/// \output   NvM_WriteBlock_RetVal           = E_OK
/// \output   NvM_WriteBlock_Param2           = 1u
/// \output   NvM_aAdminTable[1u].ErrorStatus = NVM_REQ_PENDING
///
//-----------------------------------------------------------------------------
void Mt_NvM_WriteBlock_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_WriteBlock_Param1     = 1u;
  NvM_WriteBlock_Param2     = 1u;

  //Step 3) Call FUT
  NvM_WriteBlock_RetVal     = NvM_WriteBlock(NvM_WriteBlock_Param1, &NvM_WriteBlock_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_WriteBlock_RetVal,                      E_OK, == );
  AL_UNITTEST_CHECK(NvM_WriteBlock_Param2,                        1u, == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[1u].ErrorStatus, NVM_REQ_PENDING, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_WriteBlock_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test if the function rejects the request of writing
///                         data from RAM block to the corresponding NV block
///                         in case the queue is already full
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    NvM_WriteBlock_Param1           = 1u
/// \input    NvM_WriteBlock_Param2           = 1u
/// \input    NvM_ucQueueFront                = 5u
/// \input    NvM_ucQueueRear                 = 4u
///
/// - Expectations: 
///
/// \output   NvM_WriteBlock_RetVal           = E_NOT_OK
/// \output   NvM_aAdminTable[1u].ErrorStatus = NVM_REQ_NOT_OK
//
//-----------------------------------------------------------------------------
void Mt_NvM_WriteBlock_TestCase3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_WriteBlock_Param1         = 1u;
  NvM_WriteBlock_Param2         = 1u;
  NvM_ucQueueFront              = 5u;
  NvM_ucQueueRear               = 4u;

  //Step 3) Call FUT
  NvM_WriteBlock_RetVal  = NvM_WriteBlock(NvM_WriteBlock_Param1, &NvM_WriteBlock_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_WriteBlock_RetVal,                 E_NOT_OK, == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[1u].ErrorStatus, NVM_REQ_NOT_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_WriteBlock
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the blocks are prepared to writr the data of
///                     the RAM block to its corresponding NV block
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing) 
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_NvM_WriteBlock(void)
{
  Mt_NvM_WriteBlock_TestCase1();
  Mt_NvM_WriteBlock_TestCase2();
  Mt_NvM_WriteBlock_TestCase3();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_ReadBlock_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///          - Test subject: Test if the function reports error for a request 
///                          out of the accepted range (Nvm Block Count)
///
///        - Test Design Technique: ET (Exploratory Testing)
///
///
/// - Preconditions:
///
/// \input      NvM_ReadBlock_Param1     = NvMBlockCount + 1
/// \input      NvM_ReadBlock_Param2     = 1u
///
/// - Expectations: 
///
/// \output   NvM_ReadBlock_RetVal       = FALSE
///
//-----------------------------------------------------------------------------
void Mt_NvM_ReadBlock_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_ReadBlock_Param1  = NvMBlockCount + 1;
  NvM_ReadBlock_Param2  = 1u;

  //Step 3) Call FUT
  NvM_ReadBlock_RetVal  = NvM_ReadBlock(NvM_ReadBlock_Param1, &NvM_ReadBlock_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_ReadBlock_RetVal, E_NOT_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_ReadBlock_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:  Test if the function accepts the request of reading
///                         data from RAM block to the corresponding NV block if it
///                         is in the queue
///
///        - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    NvM_ReadBlock_Param1              = 1u
/// \input    NvM_ReadBlock_Param2              = 1u
/// \input    NvM_ucQueueRear                   = 0u
/// \input    NvM_ucQueueFront                  = 0u
///
/// - Expectations: 
///
/// \output   NvM_ReadBlock_RetVal              = E_OK
/// \output   NvM_ReadBlock_Param2              = 1u
/// \output   NvM_aAdminTable[1u].ErrorStatus   = NVM_REQ_PENDING
///
//-----------------------------------------------------------------------------
void Mt_NvM_ReadBlock_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_ReadBlock_Param1    = 1u;
  NvM_ReadBlock_Param2    = 1u;
  NvM_ucQueueRear         = 0u;
  NvM_ucQueueFront        = 0u;

  //Step 3) Call FUT
  NvM_ReadBlock_RetVal    = NvM_ReadBlock(NvM_ReadBlock_Param1, &NvM_ReadBlock_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_ReadBlock_RetVal,                       E_OK, == );
  AL_UNITTEST_CHECK(NvM_ReadBlock_Param2,                         1u, == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[1u].ErrorStatus, NVM_REQ_PENDING, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_ReadBlock_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test if the function rejects the request of writing
///                         data from RAM block to the corresponding NV block
///                         in case the queue is already full
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    NvM_ReadBlock_Param1              = 1u
/// \input    NvM_ReadBlock_Param2              = 1u
/// \input    NvM_ucQueueFront                  = 5u
/// \input    NvM_ucQueueRear                   = 4u
///
/// - Expectations: 
///
/// \output   NvM_ReadBlock_RetVal              = E_NOT_OK
/// \output   NvM_aAdminTable[1u].ErrorStatus   = NVM_REQ_OK
///
//-----------------------------------------------------------------------------
void Mt_NvM_ReadBlock_TestCase3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_ReadBlock_Param1      = 1u;
  NvM_ReadBlock_Param2      = 1u;
  NvM_ucQueueFront          = 5u;
  NvM_ucQueueRear           = 4u;

  //Step 3) Call FUT
  NvM_ReadBlock_RetVal      = NvM_ReadBlock(NvM_ReadBlock_Param1, &NvM_ReadBlock_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_ReadBlock_RetVal,              E_NOT_OK, == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[1u].ErrorStatus, NVM_REQ_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_ReadBlock
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the blocks are prepared to copy the data of the NV block 
///                     to its corresponding RAM block.
///
///         - Test Design Technique:  - Requirement based test
///                                   - ET (Exploratory Testing) 
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_NvM_ReadBlock(void)
{
  Mt_NvM_ReadBlock_TestCase1();
  Mt_NvM_ReadBlock_TestCase2();
  Mt_NvM_ReadBlock_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_reNvm_WritePxlData
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if the function executes the event runnable and 
///                     writes the received data into the dedicated Nvm block
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    Rte_Read_CtrlPxl_Nvm_WriteData_HitCount        = 0u
/// \input    Rte_Read_CtrlPxl_Nvm_WriteData_Param1.unSize   = 256u
/// \input    Rte_Read_CtrlPxl_Nvm_WriteData_Param1.pucData  = &ucTestData[0]
///
/// - Expectations: 
///
/// \output   Rte_Read_CtrlPxl_Nvm_WriteData_HitCount    = 1u
/// \output   UtilMemCopy_HitCount                       = 1u
///
//-----------------------------------------------------------------------------
void Mt_reNvm_WritePxlData(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  uint8 ucTestData[256] = { 255u };
  Rte_Read_CtrlPxl_Nvm_WriteData_HitCount = 0u;
  Rte_Read_CtrlPxl_Nvm_WriteData_Param1.unSize = 256u;
  Rte_Read_CtrlPxl_Nvm_WriteData_Param1.pucData = &ucTestData[0];

  //Step 3) Call FUT
  reNvm_WritePxlData();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CtrlPxl_Nvm_WriteData_HitCount, 1u, == );
  AL_UNITTEST_CHECK(UtilMemCopy_HitCount,                    1u, == );

}

//-----------------------------------------------------------------------------
//Nvm_Internal.c
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_MemIfReadCrc
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if the function MemIfReadCrc reads CRC of a memory
///                     block and returns the CRC value
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input       UtilMemCopy_HitCount   = 0u
/// \input       MemIfReadCrc_Param1[0] = 15u
///
/// - Expectations: 
///
/// \output      UtilMemCopy_HitCount   = 1u
/// \output      MemIfReadCrc_RetVal    = 0u
///
//-----------------------------------------------------------------------------
void Mt_MemIfReadCrc(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  UtilMemCopy_HitCount       = 0u;
  MemIfReadCrc_Param1[0]     = 15u;

  //Step 3) Call FUT
  MemIfReadCrc_RetVal        = MemIfReadCrc(&MemIfReadCrc_Param1[0]);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilMemCopy_HitCount,      1u, == );
  AL_UNITTEST_CHECK(MemIfReadCrc_RetVal,       0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_MemIfWriteCrc
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that MemIfWriteCrc function adds CRC to the memory block
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input     MemIfWriteCrc_Param1[0]   = 0u
/// \input     MemIfWriteCrc_Param2      = 1818230u
///
/// - Expectations: 
///
/// \output   MemIfWriteCrc_Param1[0]   = 118u
/// \output   MemIfWriteCrc_Param1[1]   = 190u
/// \output   MemIfWriteCrc_Param1[2]   = 27u
///
//-----------------------------------------------------------------------------
void Mt_MemIfWriteCrc(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  MemIfWriteCrc_Param1[0]               = 0u;
  MemIfWriteCrc_Param2                  = 1818230u;

  //Step 3) Call FUT
  MemIfWriteCrc(&MemIfWriteCrc_Param1[0], MemIfWriteCrc_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(MemIfWriteCrc_Param1[0],        118u, == );
  AL_UNITTEST_CHECK(MemIfWriteCrc_Param1[1],        190u, == );
  AL_UNITTEST_CHECK(MemIfWriteCrc_Param1[2],         27u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_ClearQueue
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if the function NvM_ClearQueue clears the  queue
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input     NvM_ucQueueRear        = 0u
/// \input     NvM_ucQueueFront       = 0u
/// \input     UtilMemClr_HitCount    = 0u
///
/// - Expectations: 
///
/// \output   UtilMemClr_HitCount     = 1u
/// \output   NvM_ucQueueRear         = Nvm_EmptyMarker
/// \output   NvM_ucQueueFront        = Nvm_EmptyMarker
///
//-----------------------------------------------------------------------------
void Mt_NvM_ClearQueue(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  UtilMemClr_HitCount     = 0u;
  NvM_ucQueueRear         = 0u;
  NvM_ucQueueFront        = 0u;

  //Step 3) Call FUT
  NvM_ClearQueue();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilMemClr_HitCount,              1u, == );
  AL_UNITTEST_CHECK(NvM_ucQueueRear,     Nvm_EmptyMarker, == );
  AL_UNITTEST_CHECK(NvM_ucQueueFront,    Nvm_EmptyMarker, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NwM_IsQueueFull_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if the function NwM_IsQueueFull detects a full queue
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input     NvM_ucQueueRear          = 14u
/// \input     NvM_ucQueueFront         = 5u
///
/// - Expectations: 
///
/// \output   NwM_IsQueueFull_RetVal    = TRUE
///
//-----------------------------------------------------------------------------
void Mt_NwM_IsQueueFull_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_ucQueueRear           = 14u;
  NvM_ucQueueFront          =  5u;

  //Step 3) Call FUT
  NwM_IsQueueFull_RetVal    = NwM_IsQueueFull();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NwM_IsQueueFull_RetVal,   TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NwM_IsQueueFull_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if the function NwM_IsQueueFull detects a non-empty queue
///                     (filled, but not full)
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input     NvM_ucQueueRear          = 10u
/// \input     NvM_ucQueueFront         =  5u
///
/// - Expectations: 
///
/// \output   NwM_IsQueueFull_RetVal    = FALSE
///
//-----------------------------------------------------------------------------
void Mt_NwM_IsQueueFull_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_ucQueueRear     = 10u;
  NvM_ucQueueFront    =  5u;

  //Step 3) Call FUT
  NwM_IsQueueFull_RetVal = NwM_IsQueueFull();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NwM_IsQueueFull_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NwM_IsQueueFull
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that a full queue is detected
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_NwM_IsQueueFull(void)
{
  Mt_NwM_IsQueueFull_TestCase1();
  Mt_NwM_IsQueueFull_TestCase2();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_NwM_IsQueueEmpty_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if the function NwM_IsQueueEmpty detects an empty queue
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input     NvM_ucQueueRear      = -1
/// \input     NvM_ucQueueFront     = -1
///
/// - Expectations: 
///
/// \output   NwM_IsQueueEmpty_RetVal   = TRUE
///
//-----------------------------------------------------------------------------
void Mt_NwM_IsQueueEmpty_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_ucQueueRear         = -1;
  NvM_ucQueueFront        = -1;

  //Step 3) Call FUT
  NwM_IsQueueEmpty_RetVal = NwM_IsQueueEmpty();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NwM_IsQueueEmpty_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NwM_IsQueueEmpty_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if the function NwM_IsQueueEmpty detects a filled queue
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input     NvM_ucQueueRear      = 1u
/// \input     NvM_ucQueueFront     = 2u
///
/// - Expectations: 
///
/// \output   NwM_IsQueueEmpty_RetVal   = FALSE
///
//-----------------------------------------------------------------------------
void Mt_NwM_IsQueueEmpty_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_ucQueueRear         = 1u;
  NvM_ucQueueFront        = 2u;

  //Step 3) Call FUT
  NwM_IsQueueEmpty_RetVal = NwM_IsQueueEmpty();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NwM_IsQueueEmpty_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NwM_IsQueueEmpty
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that an empty queue is detected
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_NwM_IsQueueEmpty(void)
{
  Mt_NwM_IsQueueEmpty_TestCase1();
  Mt_NwM_IsQueueEmpty_TestCase2();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_QueueBlock_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function NvM_QueueBlock detects a job that
///                         is already present and the queue is full
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input     NvM_ucQueueRear      = -1
/// \input     NvM_ucQueueFront     = -1
/// \input     NvmQueue[NvM_ucQueueFront].job = NVM_STATE_IDLE
/// \input     NvM_QueueBlock_Param1 = &NvmQueue[NvM_ucQueueFront].job
/// \input     NvM_ucQueueRear  = 5u
/// \input     NvM_ucQueueFront = 6u
///
/// - Expectations: 
///
/// \output   NvM_QueueBlock_RetVal     = E_NOT_OK
/// \output   NwM_IsQueueFull_RetVal    = FALSE
///
//-----------------------------------------------------------------------------
void Mt_NvM_QueueBlock_TestCase1(void)
{
  //Step 1) Set pre-conditionsF
  //Step 2) Assign Input values
  NvM_ucQueueRear     = Nvm_EmptyMarker;
  NvM_ucQueueFront    = Nvm_EmptyMarker;
 
  NvmQueue[NvM_ucQueueFront].job = NVM_STATE_IDLE;
  NvM_QueueBlock_Param1 = &NvmQueue[NvM_ucQueueFront].job;

  NvM_ucQueueRear     = 5u;
  NvM_ucQueueFront    = 6u;

  //Step 3) Call FUT
  NvM_QueueBlock_RetVal = NvM_QueueBlock(NvM_QueueBlock_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_QueueBlock_RetVal, E_NOT_OK, == );
  AL_UNITTEST_CHECK(NwM_IsQueueFull_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_QueueBlock_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function NvM_QueueBlock detects a job that
///                         is already present and the queue is neither full nor empty
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input     NvM_ucQueueRear                   = 5u
/// \input     NvM_ucQueueFront                  = 10u
/// \input     NvmQueue[NvM_ucQueueFront].job    = NVM_STATE_IDLE
/// \input     NvM_QueueBlock_Param1             = &NvmQueue[NvM_ucQueueFront].job
///
/// - Expectations: 
///
/// \output   NvM_QueueBlock_RetVal     =  E_OK
/// \output   NwM_IsQueueFull_RetVal    =  FALSE
/// \output   NwM_IsQueueEmpty_RetVal   =  FALSE
///
//-----------------------------------------------------------------------------
void Mt_NvM_QueueBlock_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_ucQueueRear                   = 5u;
  NvM_ucQueueFront                  = 10u;
  NvmQueue[NvM_ucQueueFront].job    = NVM_STATE_IDLE;
  NvM_QueueBlock_Param1             = &NvmQueue[NvM_ucQueueFront].job;

  //Step 3) Call FUT
  NvM_QueueBlock_RetVal = NvM_QueueBlock(NvM_QueueBlock_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_QueueBlock_RetVal,     E_OK, == );
  AL_UNITTEST_CHECK(NwM_IsQueueFull_RetVal,   FALSE, == );
  AL_UNITTEST_CHECK(NwM_IsQueueEmpty_RetVal,  FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_QueueBlock_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function NvM_QueueBlock detects a job that
///                         is already present and the queue is empty
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input     NvM_ucQueueRear                    = Nvm_EmptyMarker
/// \input     NvM_ucQueueFront                   = Nvm_EmptyMarker
/// \input     NvmQueue[NvM_ucQueueFront].job     = NVM_STATE_IDLE
/// \input     NvM_QueueBlock_Param1              = &NvmQueue[NvM_ucQueueFront].job
///
/// - Expectations: 
///
/// \output   NvM_QueueBlock_RetVal     = E_OK
/// \output   NwM_IsQueueFull_RetVal    = FALSE
///
//-----------------------------------------------------------------------------
void Mt_NvM_QueueBlock_TestCase3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_ucQueueRear                 = Nvm_EmptyMarker;
  NvM_ucQueueFront                = Nvm_EmptyMarker;
  NvmQueue[NvM_ucQueueFront].job  = NVM_STATE_IDLE;
  NvM_QueueBlock_Param1           = &NvmQueue[NvM_ucQueueFront].job;

  //Step 3) Call FUT
  NvM_QueueBlock_RetVal   = NvM_QueueBlock(NvM_QueueBlock_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_QueueBlock_RetVal,     E_OK, == );
  AL_UNITTEST_CHECK(NwM_IsQueueFull_RetVal,   FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_QueueBlock
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that a job already present in the queue is detected
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_NvM_QueueBlock(void)
{
  Mt_NvM_QueueBlock_TestCase1();
  Mt_NvM_QueueBlock_TestCase2();
  Mt_NvM_QueueBlock_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_GetQueuedBlock_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check that the function NvM_GetQueuedBlock resets
///                         the queue indexes when the last block in the queue
///                         was copied
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input     NvM_ucQueueRear                 = 2u
/// \input     NvM_ucQueueFront                = 2u
/// \input     NvmQueue[NvM_ucQueueFront].job  = NVM_STATE_IDLE
/// \input     NvM_GetQueuedBlock_Param1       = &NvmQueue[NvM_ucQueueFront].job
///
/// - Expectations: 
///
/// \output   NwM_IsQueueEmpty_RetVal     = FALSE
/// \output   NvM_GetQueuedBlock_RetVal   = E_OK
/// \output   NvM_ucQueueRear             = Nvm_EmptyMarker
/// \output   NvM_ucQueueFront            = Nvm_EmptyMarker
///
//-----------------------------------------------------------------------------
void Mt_NvM_GetQueuedBlock_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_ucQueueRear                 = 2u;
  NvM_ucQueueFront                = 2u;
  NvmQueue[NvM_ucQueueFront].job  = NVM_STATE_IDLE;
  NvM_GetQueuedBlock_Param1       = &NvmQueue[NvM_ucQueueFront].job;

  //Step 3) Call FUT
  NvM_GetQueuedBlock_RetVal = NvM_GetQueuedBlock(NvM_GetQueuedBlock_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_GetQueuedBlock_RetVal,       E_OK, == );
  AL_UNITTEST_CHECK(NwM_IsQueueEmpty_RetVal,        FALSE, == );
  AL_UNITTEST_CHECK(NvM_ucQueueRear,      Nvm_EmptyMarker, == );
  AL_UNITTEST_CHECK(NvM_ucQueueFront,     Nvm_EmptyMarker, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_GetQueuedBlock_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check that the function NvM_GetQueuedBlock increments
///                         the queue indexes every time a block in the queue
///                         was copied
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input     NvM_ucQueueRear                 = 1u
/// \input     NvM_ucQueueFront                = 2u
/// \input     NvmQueue[NvM_ucQueueFront].job  = NVM_STATE_IDLE
/// \input     NvM_GetQueuedBlock_Param1       = &NvmQueue[NvM_ucQueueFront].job
///
/// - Expectations: 
///
/// \output   NwM_IsQueueEmpty_RetVal          = FALSE
/// \output   NvM_GetQueuedBlock_RetVal        = E_OK
/// \output   NvM_ucQueueFront                 = 3u
///
//-----------------------------------------------------------------------------
void Mt_NvM_GetQueuedBlock_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_ucQueueRear                 = 1u;
  NvM_ucQueueFront                = 2u;
  NvmQueue[NvM_ucQueueFront].job  = NVM_STATE_IDLE;
  NvM_GetQueuedBlock_Param1       = &NvmQueue[NvM_ucQueueFront].job;

  //Step 3) Call FUT
  NvM_GetQueuedBlock_RetVal = NvM_GetQueuedBlock(NvM_GetQueuedBlock_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_GetQueuedBlock_RetVal, E_OK, == );
  AL_UNITTEST_CHECK(NwM_IsQueueEmpty_RetVal,  FALSE, == );
  AL_UNITTEST_CHECK(NvM_ucQueueFront,            3u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_GetQueuedBlock
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the job present in the queue is copied
///                     and the current queue indexes are updated
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_NvM_GetQueuedBlock(void)
{
  Mt_NvM_GetQueuedBlock_TestCase1();
  Mt_NvM_GetQueuedBlock_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_HandleBlockWrite_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:
///        Check if the function HandleBlockWrite returns the correct state of the Nvm module in case of
///        a memory interface request
///
///    - Test Design Technique: - DT (Decision Table)
///                             - Requirements-based test
///
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT.
///
///      - DT-Info:
///         - Inputs:
///            actualState :  known value of internal variable before calling FUT
///         - Expected results
///            returnedState : expected return value by the FUT
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
//-----------------------------------------------------------------------------
void Mt_Nvm_HandleBlockWrite_TestCase1(void)
{
  typedef struct tsTestCaseDataInput
  {
    tNvMBlockDescriptor  actualState;
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    NvM_AdminBlockType returnedState;
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput  sInputData;
    tsTestCaseDataOutput sOutputData;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    //           Inputs                                           || Outputs
    // actual state                                               || returned state
    {  { {.MemIfDevice_u8 =  MEMIF_JOB_OK                }}        ,  { {.ErrorStatus =     NVM_REQ_OK   ,.BlockState = NVM_STATE_IDLE} }     },
    {  { {.MemIfDevice_u8 =  MEMIF_JOB_FAILED            }}        ,  { {.ErrorStatus = NVM_REQ_NOT_OK   ,.BlockState = NVM_STATE_IDLE} }     },
    {  { {.MemIfDevice_u8 =  MEMIF_JOB_PENDING           }}        ,  { {.ErrorStatus = NVM_REQ_NOT_OK   ,.BlockState = NVM_STATE_IDLE} }     },
    {  { {.MemIfDevice_u8 =  MEMIF_JOB_CANCELLED         }}        ,  { {.ErrorStatus = NVM_REQ_NOT_OK   ,.BlockState = NVM_STATE_IDLE} }     },
    {  { {.MemIfDevice_u8 =  MEMIF_BLOCK_INCONSISTENT    }}        ,  { {.ErrorStatus = NVM_REQ_NOT_OK   ,.BlockState = NVM_STATE_IDLE} }     },
    {  { {.MemIfDevice_u8 =  MEMIF_BLOCK_INVALID         }}        ,  { {.ErrorStatus = NVM_REQ_NOT_OK   ,.BlockState = NVM_STATE_IDLE} }     }
  };

  HandleBlockWrite_Param2.BlockSubState  = NVM_SUB_STATE_MEM_IF_REQ;

  for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
  {
    //Step 1: Set pre-conditions
    //Step 2) Assign Input values
    Fee_GetJobResult_eRetVal               = asTestCaseData[ucIdx].sInputData.actualState.MemIfDevice_u8;
    HandleBlockWrite_Param1.MemIfDevice_u8 = asTestCaseData[ucIdx].sInputData.actualState.MemIfDevice_u8;

    //Step 3) Call FUT
    HandleBlockWrite(&HandleBlockWrite_Param1, &HandleBlockWrite_Param2, HandleBlockWrite_Param3, HandleBlockWrite_Param4);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(HandleBlockWrite_Param2.ErrorStatus, asTestCaseData[ucIdx].sOutputData.returnedState.ErrorStatus, == );
    AL_UNITTEST_CHECK(HandleBlockWrite_Param2.BlockState,  asTestCaseData[ucIdx].sOutputData.returnedState.BlockState,  == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_HandleBlockWrite_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function HandleBlockWrite handles the requested
///                         CRC Write operation for a given NV Block 
///
///    - Test Design Technique: - ET ( Exploratory Testing )
///                             - Requirements-based test
///
/// - Preconditions:
///
/// \input        HandleBlockWrite_Param2.BlockSubState   = NVM_SUB_STATE_DO_CRC
/// \input        UtilMemCopy_HitCount                    = 0u
/// \input        NvM_aucMemIf_Buffer[84]                 = 5u
/// \input        UtilMemCopy_Input_Param1                = &NvM_aucMemIf_Buffer[0]
/// \input        MemIfWriteCrc_Param1[2]                 = &UtilMemCopy_Input_Param1
/// \input        HandleBlockWrite_Param3                 = &NvM_aucMemIf_Buffer[0]
/// \input        HandleBlockWrite_Param1.RamMirror       = &NvM_aucMemIf_Buffer[0]
/// \input        Fee_Write_ucRetVal                      = E_OK
///
/// - Expectations: 
///
/// \output   UtilMemCopy_HitCount                        = 1u
/// \output   HandleBlockWrite_Param2.ErrorStatus         = NVM_REQ_PENDING
/// \output   HandleBlockWrite_Param2.BlockSubState       = NVM_SUB_STATE_MEM_IF_REQ
///
//-----------------------------------------------------------------------------
void Mt_Nvm_HandleBlockWrite_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  HandleBlockWrite_Param2.BlockSubState   = NVM_SUB_STATE_DO_CRC;
  UtilMemCopy_HitCount                    = 0u;
  NvM_aucMemIf_Buffer[84]                 = 5u;
  UtilMemCopy_Input_Param1                = &NvM_aucMemIf_Buffer[0];
  MemIfWriteCrc_Param1[2]                 = &UtilMemCopy_Input_Param1;
  HandleBlockWrite_Param3                 = &NvM_aucMemIf_Buffer[0];
  HandleBlockWrite_Param1.RamMirror       = &NvM_aucMemIf_Buffer[0];
  Fee_Write_ucRetVal                      = E_OK;

  //Step 3) Call FUT
  HandleBlockWrite(&HandleBlockWrite_Param1, &HandleBlockWrite_Param2, HandleBlockWrite_Param3, HandleBlockWrite_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilMemCopy_HitCount,                                         1u, == );
  AL_UNITTEST_CHECK(HandleBlockWrite_Param2.ErrorStatus,             NVM_REQ_PENDING, == );
  AL_UNITTEST_CHECK(HandleBlockWrite_Param2.BlockSubState,  NVM_SUB_STATE_MEM_IF_REQ, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_HandleBlockWrite_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function HandleBlockWrite rejects the requested
///                         CRC Write operation for a given NV Block having a wrong
///                         status of the fee memory for that given block
///
///    - Test Design Technique: - ET ( Exploratory Testing )
///                             - Requirements-based test
///
/// - Preconditions:
///
/// \input        HandleBlockWrite_Param2.BlockSubState   = NVM_SUB_STATE_DO_CRC
/// \input        UtilMemCopy_HitCount                    = 0u
/// \input        Fee_Write_ucRetVal                      = E_NOT_OK
///
/// - Expectations: 
///
/// \output   UtilMemCopy_HitCount                        = 1u
/// \output   HandleBlockWrite_Param2.ErrorStatus         = NVM_REQ_NOT_OK
/// \output   HandleBlockWrite_Param2.BlockSubState       = NVM_SUB_STATE_MEM_IF_REQ
///
//-----------------------------------------------------------------------------
void Mt_Nvm_HandleBlockWrite_TestCase3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  HandleBlockWrite_Param2.BlockSubState = NVM_SUB_STATE_DO_CRC;
  UtilMemCopy_HitCount                  = 0u;
  Fee_Write_ucRetVal                    = E_NOT_OK;

  //Step 3) Call FUT
  HandleBlockWrite(&HandleBlockWrite_Param1, &HandleBlockWrite_Param2, HandleBlockWrite_Param3, HandleBlockWrite_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilMemCopy_HitCount,                                         1u, == );
  AL_UNITTEST_CHECK(HandleBlockWrite_Param2.ErrorStatus,              NVM_REQ_NOT_OK, == );
  AL_UNITTEST_CHECK(HandleBlockWrite_Param2.BlockSubState,  NVM_SUB_STATE_MEM_IF_REQ, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_HandleBlockWrite_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check if the function HandleBlockWrite does nothing
///                     if the job result is not valid
///
///    - Test Design Technique: - ET ( Exploratory Testing )
///                             - Requirements-based test
///
/// - Preconditions:
///
/// \input        HandleBlockWrite_Param2.BlockSubState   = NVM_SUB_STATE_MEM_IF_REQ
/// \input        Fee_GetJobResult_eRetVal                = 255u
/// \input        HandleBlockWrite_Param2.ErrorStatus     = 99u
/// \input        HandleBlockWrite_Param2.BlockState      = 99u
///
/// - Expectations: 
///
/// \output   HandleBlockWrite_Param2.ErrorStatus         = 99u
/// \output   HandleBlockWrite_Param2.BlockState          = 99u
////
//-----------------------------------------------------------------------------
void Mt_Nvm_HandleBlockWrite_TestCase4(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  HandleBlockWrite_Param2.BlockSubState = NVM_SUB_STATE_MEM_IF_REQ;
  Fee_GetJobResult_eRetVal              = 255u;
  HandleBlockWrite_Param2.ErrorStatus   = 99u;
  HandleBlockWrite_Param2.BlockState    = 99u;

  //Step 3) Call FUT
  HandleBlockWrite(&HandleBlockWrite_Param1, &HandleBlockWrite_Param2, HandleBlockWrite_Param3, HandleBlockWrite_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(HandleBlockWrite_Param2.ErrorStatus, 99u, == );
  AL_UNITTEST_CHECK(HandleBlockWrite_Param2.BlockState, 99u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_HandleBlockWrite
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test the handling of block writing request
///
///    - Test Design Technique:  - Requirement based test
///                              - ET (Exploratory Testing) 
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Nvm_HandleBlockWrite(void)
{
  Mt_Nvm_HandleBlockWrite_TestCase1();
  Mt_Nvm_HandleBlockWrite_TestCase2();
  Mt_Nvm_HandleBlockWrite_TestCase3();
  Mt_Nvm_HandleBlockWrite_TestCase4();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_HandleBlockRead_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:
///        Check if the function HandleBlockRead returns the correct error status  and sub state of the NV module for
///        the requested NVM_SUB_STATE_MEM_IF_PROC operation
///
///    - Test Design Technique: - DT (Decision Table)
///                             - Requirements-based test
///
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT.
///
///      - DT-Info:
///         - Inputs:
///            actualState :  known value of internal variable before calling FUT
///         - Expected results
///            returnedState : expected return value by the FUT
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
//-----------------------------------------------------------------------------
void Mt_Nvm_HandleBlockRead_TestCase1(void)
{

  typedef struct tsTestCaseDataInput
  {
    tNvMBlockDescriptor  actualState;
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    NvM_AdminBlockType returnedState;
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput  sInputData;
    tsTestCaseDataOutput sOutputData;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    //           Inputs                                           || Outputs
    // actual state                                               || returned state
    {  { {.MemIfDevice_u8 = MEMIF_JOB_OK                }}        ,  { {.ErrorStatus = NVM_REQ_OK      ,  .BlockSubState = NVM_SUB_STATE_DO_CRC       } }     },
    {  { {.MemIfDevice_u8 = MEMIF_JOB_FAILED            }}        ,  { {.ErrorStatus = NVM_REQ_NOT_OK  ,  .BlockSubState = NVM_SUB_STATE_FINALIZE     } }     },
    {  { {.MemIfDevice_u8 = MEMIF_JOB_PENDING           }}        ,  { {.ErrorStatus = NVM_REQ_NOT_OK  ,  .BlockSubState = NVM_SUB_STATE_MEM_IF_PROC  } }     },
    {  { {.MemIfDevice_u8 = MEMIF_JOB_CANCELLED         }}        ,  { {.ErrorStatus = NVM_REQ_NOT_OK  ,  .BlockSubState = NVM_SUB_STATE_FINALIZE     } }     },
    {  { {.MemIfDevice_u8 = MEMIF_BLOCK_INCONSISTENT    }}        ,  { {.ErrorStatus = NVM_REQ_NOT_OK  ,  .BlockSubState = NVM_SUB_STATE_FINALIZE     } }     },
    {  { {.MemIfDevice_u8 = MEMIF_BLOCK_INVALID         }}        ,  { {.ErrorStatus = NVM_REQ_NOT_OK  ,  .BlockSubState = NVM_SUB_STATE_FINALIZE     } }     },
  };

  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  uint8 unMtData[8]       = { 0u };
  HandleBlockRead_Param3  = &unMtData[0];

  for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
  {
    //Step 1: Set pre-conditions
    //Step 2) Assign Input values
    HandleBlockRead_Param2.BlockSubState  = NVM_SUB_STATE_MEM_IF_PROC;
    Fee_GetJobResult_eRetVal              = asTestCaseData[ucIdx].sInputData.actualState.MemIfDevice_u8;
    HandleBlockRead_Param1.MemIfDevice_u8 = Fee_GetJobResult_eRetVal;

    //Step 3) Call FUT
    HandleBlockRead(&HandleBlockRead_Param1, &HandleBlockRead_Param2, HandleBlockRead_Param3, HandleBlockRead_Param4);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(HandleBlockRead_Param2.ErrorStatus,    asTestCaseData[ucIdx].sOutputData.returnedState.ErrorStatus,   == );
    AL_UNITTEST_CHECK(HandleBlockRead_Param2.BlockSubState,  asTestCaseData[ucIdx].sOutputData.returnedState.BlockSubState, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_HandleBlockRead_TestCase2
///
/// \Test Case Description: Check if the function HandleBlockRead handles the requested
///                         CRC Read operation for a given NV Block and copies its content
///
///    - Test Design Technique: - ET ( Exploratory Testing )
///                             - Requirements-based test
///
/// - Preconditions:
///
/// \input    HandleBlockRead_Param2.BlockSubState  = NVM_SUB_STATE_DO_CRC
/// \input    UtilMemCopy_HitCount                  = 0u
///
/// - Expectations: 
///
/// \output   UtilMemCopy_HitCount                  = 2u
/// \output   HandleBlockRead_Param2.ErrorStatus    = NVM_REQ_OK
/// \output   HandleBlockRead_Param2.BlockChanged   = FALSE
/// \output   HandleBlockRead_Param2.BlockValid     = TRUE
/// \output   HandleBlockRead_Param2.BlockSubState  = NVM_SUB_STATE_FINALIZE
///
//-----------------------------------------------------------------------------
void Mt_Nvm_HandleBlockRead_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  HandleBlockRead_Param2.BlockSubState  = NVM_SUB_STATE_DO_CRC;
  UtilMemCopy_HitCount                  = 0u;

  //Step 3) Call FUT
  HandleBlockRead(&HandleBlockRead_Param1, &HandleBlockRead_Param2, HandleBlockRead_Param3, HandleBlockRead_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilMemCopy_HitCount,                                     2u, == );
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.ErrorStatus,               NVM_REQ_OK, == );
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.BlockChanged,                   FALSE, == );
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.BlockValid,                      TRUE, == );
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.BlockSubState, NVM_SUB_STATE_FINALIZE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_HandleBlockRead_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function HandleBlockRead rejects the requested
///                         CRC Read operation for a given block with different CRC values
///                         (inconsistent data)
///
///    - Test Design Technique: - ET ( Exploratory Testing )
///                             - Requirements-based test
///
/// - Preconditions:
///
/// \input    HandleBlockRead_Param2.BlockSubState  = NVM_SUB_STATE_DO_CRC
/// \input    UtilMemCopy_HitCount                  = 0u
/// \input    Crc_CalculateCRC32_RetVal             = 25485
/// - Expectations: 
///
/// \output   UtilMemCopy_HitCount                  = 1u
/// \output   HandleBlockRead_Param2.ErrorStatus    = NVM_REQ_NOT_OK
/// \output   HandleBlockRead_Param2.BlockChanged   = FALSE
/// \output   HandleBlockRead_Param2.BlockValid     = TRUE
/// \output   HandleBlockRead_Param2.BlockSubState  = NVM_SUB_STATE_FINALIZE
///
//-----------------------------------------------------------------------------
void Mt_Nvm_HandleBlockRead_TestCase3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  HandleBlockRead_Param2.BlockSubState  = NVM_SUB_STATE_DO_CRC;
  UtilMemCopy_HitCount                  = 0u;
  Crc_CalculateCRC32_RetVal             = 25485;

  //Step 3) Call FUT
  HandleBlockRead(&HandleBlockRead_Param1, &HandleBlockRead_Param2, HandleBlockRead_Param3, HandleBlockRead_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(UtilMemCopy_HitCount,                                     1u, == );
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.ErrorStatus,           NVM_REQ_NOT_OK, == );
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.BlockChanged,                   FALSE, == );
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.BlockValid,                      TRUE, == );
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.BlockSubState, NVM_SUB_STATE_FINALIZE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_HandleBlockRead_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function HandleBlockRead handles the requested
///                         Read operation for a given NV Block and updates the block
///                         status ready to be processed
///
///    - Test Design Technique: - ET ( Exploratory Testing )
///                             - Requirements-based test
///
/// - Preconditions:
///
/// \input    HandleBlockRead_Param2.BlockSubState  = NVM_SUB_STATE_MEM_IF_REQ
///
/// - Expectations: 
///
/// \output   HandleBlockRead_Param2.ErrorStatus    = NVM_REQ_PENDING
/// \output   HandleBlockRead_Param2.BlockSubState  = NVM_SUB_STATE_MEM_IF_PROC
///
//-----------------------------------------------------------------------------
void Mt_Nvm_HandleBlockRead_TestCase4(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  HandleBlockRead_Param2.BlockSubState = NVM_SUB_STATE_MEM_IF_REQ;

  //Step 3) Call FUT
  HandleBlockRead(&HandleBlockRead_Param1, &HandleBlockRead_Param2, HandleBlockRead_Param3, HandleBlockRead_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.ErrorStatus,             NVM_REQ_PENDING, == );
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.BlockSubState, NVM_SUB_STATE_MEM_IF_PROC, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_HandleBlockRead_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function HandleBlockRead rejects the requested
///                         Read operation for a given NV Block having a wrong
///                         status of the fee memory for that given block
///
///    - Test Design Technique: - ET ( Exploratory Testing )
///                             - Requirements-based test
///
/// - Preconditions:
///
/// \input    HandleBlockRead_Param2.BlockSubState  = NVM_SUB_STATE_MEM_IF_REQ
/// \input    Fee_Read_ucRetVal                     = E_NOT_OK
///
/// - Expectations: 
///
/// \output   HandleBlockRead_Param2.ErrorStatus    = NVM_REQ_NOT_OK
/// \output   HandleBlockRead_Param2.BlockSubState  = NVM_SUB_STATE_FINALIZE
///
//-----------------------------------------------------------------------------
void Mt_Nvm_HandleBlockRead_TestCase5(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  HandleBlockRead_Param2.BlockSubState = NVM_SUB_STATE_MEM_IF_REQ;
  Fee_Read_ucRetVal                    = E_NOT_OK;

  //Step 3) Call FUT
  HandleBlockRead(&HandleBlockRead_Param1, &HandleBlockRead_Param2, HandleBlockRead_Param3, HandleBlockRead_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.ErrorStatus,           NVM_REQ_NOT_OK, == );
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.BlockSubState, NVM_SUB_STATE_FINALIZE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_HandleBlockRead_TestCase6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function HandleBlockRead handles the requested
///                         Read operation for a given NV Block and skips to check 
///                         the block descriptor if error status is OK
///
///    - Test Design Technique: - ET ( Exploratory Testing )
///                             - Requirements-based test
///
/// - Preconditions:
///
/// \input    HandleBlockRead_Param2.BlockSubState  = NVM_SUB_STATE_FINALIZE
/// \input    HandleBlockRead_Param2.ErrorStatus    = NVM_REQ_OK
///
/// - Expectations: 
///
/// \output   HandleBlockRead_Param2.ErrorStatus    = NVM_REQ_OK
/// \output   HandleBlockRead_Param2.BlockSubState  = NVM_SUB_STATE_FINALIZE
/// \output   HandleBlockRead_Param2.BlockState     = NVM_STATE_IDLE
///
//-----------------------------------------------------------------------------
void Mt_Nvm_HandleBlockRead_TestCase6(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  HandleBlockRead_Param2.BlockSubState  = NVM_SUB_STATE_FINALIZE;
  HandleBlockRead_Param2.ErrorStatus    = NVM_REQ_OK;

  //Step 3) Call FUT
  HandleBlockRead(&HandleBlockRead_Param1, &HandleBlockRead_Param2, HandleBlockRead_Param3, HandleBlockRead_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.ErrorStatus,               NVM_REQ_OK, == );
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.BlockSubState, NVM_SUB_STATE_FINALIZE, == );
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.BlockState,            NVM_STATE_IDLE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_HandleBlockRead_TestCase7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function HandleBlockRead handles the requested
///                         Read operation for a given NV Block and calls the init callback
///                         function if needed
///
///    - Test Design Technique: - ET ( Exploratory Testing )
///                             - Requirements-based test
///
/// - Preconditions:
///
/// \input    HandleBlockRead_Param2.BlockSubState          = NVM_SUB_STATE_FINALIZE
/// \input    HandleBlockRead_Param2.ErrorStatus            = NVM_REQ_NOT_OK
/// \input    HandleBlockRead_Param1.pfnInitCallback        = &Mt_Nvm_Internal_pfnInitCallback_Stub
///
/// - Expectations: 
///
/// \output   HandleBlockRead_Param2.ErrorStatus            = NVM_REQ_NOT_OK
/// \output   Mt_Nvm_Internal_InitCallback_Stub_HitCount    = 1u
/// \output   HandleBlockRead_Param2.BlockSubState          = NVM_SUB_STATE_FINALIZE
/// \output   HandleBlockRead_Param2.BlockState             = NVM_STATE_IDLE
///
//-----------------------------------------------------------------------------
void Mt_Nvm_HandleBlockRead_TestCase7(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  HandleBlockRead_Param2.BlockSubState    = NVM_SUB_STATE_FINALIZE;
  HandleBlockRead_Param2.ErrorStatus      = NVM_REQ_NOT_OK;
  HandleBlockRead_Param1.pfnInitCallback  = &Mt_Nvm_Internal_pfnInitCallback_Stub;

  //Step 3) Call FUT
  HandleBlockRead(&HandleBlockRead_Param1, &HandleBlockRead_Param2, HandleBlockRead_Param3, HandleBlockRead_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.ErrorStatus,             NVM_REQ_NOT_OK, == );
  AL_UNITTEST_CHECK(Mt_Nvm_Internal_InitCallback_Stub_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.BlockSubState,   NVM_SUB_STATE_FINALIZE, == );
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.BlockState,              NVM_STATE_IDLE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_HandleBlockRead_TestCase8
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function HandleBlockRead handles the requested
///                         Read operation for a given NV Block and initializes the ROM
///                         blocks with RAM data if requested
///
///    - Test Design Technique: - ET ( Exploratory Testing )
///                             - Requirements-based test
///
/// - Preconditions:
///
/// \input    HandleBlockRead_Param2.BlockSubState                  = NVM_SUB_STATE_FINALIZE
/// \input    NvMBlockTable[NvmBlockFreezeFrameDataPsId].InitRom    = (uint8*)&ucDataInitRomRam
/// \input    NvMBlockTable[NvmBlockFreezeFrameDataPsId].RamMirror  = (uint8*)&ucDataInitRomRam
/// \input    HandleBlockRead_Param2.BlockSubState                  = NvM_aAdminTable[NvmBlockFreezeFrameDataPsId].BlockSubState
/// \input    HandleBlockRead_Param2.ErrorStatus                    = NVM_REQ_NOT_OK
/// \input    NvM_AdminMultiBlock.unCurrentBlock                    = NvmBlockFreezeFrameDataPsId
/// \input    HandleBlockRead_Param1                                = NvMBlockTable[NvmBlockFreezeFrameDataPsId]
/// \input    HandleBlockRead_Param1.InitRom                        = NvMBlockTable[NvmBlockFreezeFrameDataPsId].InitRom
/// \input    UtilMemCopy_HitCount                                  = 0u
///
/// - Expectations: 
///
/// \output   UtilMemCopy_HitCount                              = 1u
/// \output   HandleBlockRead_Param2.ErrorStatus                = NVM_REQ_NOT_OK
/// \output   HandleBlockRead_Param2.BlockSubState              = NVM_SUB_STATE_FINALIZE
/// \output   HandleBlockRead_Param2.BlockState                 = NVM_STATE_IDLE
/// \output   NvM_AdminMultiBlock.unCurrentBlock                = 4u
///
//-----------------------------------------------------------------------------
void Mt_Nvm_HandleBlockRead_TestCase8(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_aAdminTable[NvmBlockFreezeFrameDataPsId].BlockSubState  = NVM_SUB_STATE_FINALIZE;

  uint8 ucDataInitRomRam = 1;
  NvMBlockTable[NvmBlockFreezeFrameDataPsId].InitRom          = (uint8*)&ucDataInitRomRam;
  NvMBlockTable[NvmBlockFreezeFrameDataPsId].RamMirror        = (uint8*)&ucDataInitRomRam;

  HandleBlockRead_Param2.BlockSubState                        = NvM_aAdminTable[NvmBlockFreezeFrameDataPsId].BlockSubState;
  HandleBlockRead_Param2.ErrorStatus                          = NVM_REQ_NOT_OK;
  NvM_AdminMultiBlock.unCurrentBlock                          = NvmBlockFreezeFrameDataPsId;
  HandleBlockRead_Param1                                      = NvMBlockTable[NvmBlockFreezeFrameDataPsId];
  HandleBlockRead_Param1.InitRom                              = NvMBlockTable[NvmBlockFreezeFrameDataPsId].InitRom;
  UtilMemCopy_HitCount                                        = 0u;

  //Step 3) Call FUT
  HandleBlockRead(&HandleBlockRead_Param1, &HandleBlockRead_Param2, HandleBlockRead_Param3, HandleBlockRead_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.ErrorStatus,           NVM_REQ_NOT_OK, == );
  AL_UNITTEST_CHECK(UtilMemCopy_HitCount,                                     1u, == );
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.BlockSubState, NVM_SUB_STATE_FINALIZE, == );
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.BlockState,            NVM_STATE_IDLE, == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.unCurrentBlock,                       4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_HandleBlockRead_TestCase9
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function HandleBlockRead handles an invalid request
///                         Read operation for a given NV Block 
///
///    - Test Design Technique: - ET ( Exploratory Testing )
///                             - Requirements-based test
///
/// - Preconditions:
///
/// \input      HandleBlockRead_Param2.BlockSubState  = 4u
///
/// - Expectations: 
///
/// \output     HandleBlockRead_Param2.BlockSubState  = 4u
///
//-----------------------------------------------------------------------------
void Mt_Nvm_HandleBlockRead_TestCase9(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  HandleBlockRead_Param2.BlockSubState = 4u;

  //Step 3) Call FUT
  HandleBlockRead(&HandleBlockRead_Param1, &HandleBlockRead_Param2, HandleBlockRead_Param3, HandleBlockRead_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.BlockSubState, 4u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_HandleBlockRead_TestCase10
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function HandleBlockRead handles an invalid request
///                         Read operation for a given NV Block 
///
///    - Test Design Technique: - ET ( Exploratory Testing )
///                             - Requirements-based test
///
/// - Preconditions:
///
/// \input      HandleBlockRead_Param2.BlockSubState    = NVM_SUB_STATE_MEM_IF_PROC
/// \input      HandleBlockRead_Param2.BlockState       = 99u
/// \input      HandleBlockRead_Param2.ErrorStatus      = 99u
/// \input      Fee_GetJobResult_eRetVal                = 255u
///
/// - Expectations: 
///
/// \output     HandleBlockRead_Param2.BlockState       = 99u
/// \output     HandleBlockRead_Param2.ErrorStatus      = 99u
///
//-----------------------------------------------------------------------------
void Mt_Nvm_HandleBlockRead_TestCase10(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  HandleBlockRead_Param2.BlockSubState = NVM_SUB_STATE_MEM_IF_PROC;
  HandleBlockRead_Param2.BlockState    = 99u;
  HandleBlockRead_Param2.ErrorStatus   = 99u;
  Fee_GetJobResult_eRetVal             = 255u;

  //Step 3) Call FUT
  HandleBlockRead(&HandleBlockRead_Param1, &HandleBlockRead_Param2, HandleBlockRead_Param3, HandleBlockRead_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.BlockState,  99u, == );
  AL_UNITTEST_CHECK(HandleBlockRead_Param2.ErrorStatus, 99u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_HandleBlockRead
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test the handling of block reading request
///
///         - Test Design Technique:  - Requirement based test
///                                   - ET (Exploratory Testing) 
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Nvm_HandleBlockRead(void)
{
  Mt_Nvm_HandleBlockRead_TestCase1();
  Mt_Nvm_HandleBlockRead_TestCase2();
  Mt_Nvm_HandleBlockRead_TestCase3();
  Mt_Nvm_HandleBlockRead_TestCase4();
  Mt_Nvm_HandleBlockRead_TestCase5();
  Mt_Nvm_HandleBlockRead_TestCase6();
  Mt_Nvm_HandleBlockRead_TestCase7();
  Mt_Nvm_HandleBlockRead_TestCase8();
  Mt_Nvm_HandleBlockRead_TestCase9();
  Mt_Nvm_HandleBlockRead_TestCase10();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_WriteAllInit_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function NvM_WriteAllInit initiates a write
///                         request for NV blocks with status flag NVM_FLAG_WRITE_ALL
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    NvMBlockTable[0].Flags_u16        = NVM_FLAG_WRITE_ALL
///
/// - Expectations: 
///
/// \output   NvM_WriteAllInit_RetVal           = TRUE
/// \output   NvM_aAdminTable[0].ErrorStatus    = NVM_REQ_PENDING
/// \output   NvM_aAdminTable[0].RamCrc         = NVM_CRC_START_VALUE
/// \output   NvM_aAdminTable[0].BlockSubState  = NVM_SUB_STATE_DO_CRC
///
//-----------------------------------------------------------------------------
void Mt_NvM_WriteAllInit_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvMBlockTable[0].Flags_u16 = NVM_FLAG_WRITE_ALL;

  //Step 3) Call FUT
  NvM_WriteAllInit_RetVal = NvM_WriteAllInit();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_WriteAllInit_RetVal,                        TRUE,       == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[0].ErrorStatus,       NVM_REQ_PENDING,      == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[0].RamCrc,            NVM_CRC_START_VALUE,  == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[0].BlockSubState,     NVM_SUB_STATE_DO_CRC, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_WriteAllInit_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: :    Check if the function NvM_WriteAllInit skips write
///                         requests for NV blocks with status flag not NVM_FLAG_WRITE_ALL
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    NvMBlockTable[0].Flags_u16        = 0u
///
/// - Expectations: 
///
/// \output   NvM_WriteAllInit_RetVal           = FALSE
/// \output   NvM_aAdminTable[0].ErrorStatus    = NVM_REQ_BLOCK_SKIPPED
///
//-----------------------------------------------------------------------------
void Mt_NvM_WriteAllInit_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvMBlockTable[0].Flags_u16    = 0u;

  //Step 3) Call FUT
  NvM_WriteAllInit_RetVal = NvM_WriteAllInit();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_WriteAllInit_RetVal,                        FALSE, == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[0].ErrorStatus, NVM_REQ_BLOCK_SKIPPED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_WriteAllInit
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the internal flags are prepared for writing 
///                     at initialization phase
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_NvM_WriteAllInit(void)
{
  Mt_NvM_WriteAllInit_TestCase1();
  Mt_NvM_WriteAllInit_TestCase2();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_ReadAllInit_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function NvM_ReadAllInit initiates a read
///                         request for NV blocks with status flag NVM_FLAG_READ_ALL
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input       NvMBlockTable[0].Flags_u16     = NVM_FLAG_READ_ALL
///
/// - Expectations: 
///
/// \output   NvM_ReadAllInit_RetVal            = TRUE
/// \output   NvM_aAdminTable[0].ErrorStatus    = NVM_REQ_PENDING
/// \output   NvM_aAdminTable[0].BlockSubState  = NVM_SUB_STATE_MEM_IF_REQ
///
//-----------------------------------------------------------------------------
void Mt_NvM_ReadAllInit_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvMBlockTable[0].Flags_u16 = NVM_FLAG_READ_ALL;

  //Step 3) Call FUT
  NvM_ReadAllInit_RetVal = NvM_ReadAllInit();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_ReadAllInit_RetVal,                           TRUE,       == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[0].ErrorStatus,         NVM_REQ_PENDING,      == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[0].BlockSubState,   NVM_SUB_STATE_MEM_IF_REQ, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_ReadAllInit_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function NvM_ReadAllInit skips read
///                         requests for NV blocks with status flag not NVM_FLAG_READ_ALL
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input       NvMBlockTable[0].Flags_u16     = 0u
///
/// - Expectations: 
///
/// \output   NvM_ReadAllInit_RetVal            = FALSE
/// \output   NvM_aAdminTable[0].ErrorStatus    = NVM_REQ_BLOCK_SKIPPED
///
//-----------------------------------------------------------------------------
void Mt_NvM_ReadAllInit_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvMBlockTable[0].Flags_u16      = 0u;

  //Step 3) Call FUT
  NvM_ReadAllInit_RetVal = NvM_ReadAllInit();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_ReadAllInit_RetVal,                         FALSE, == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[0].ErrorStatus, NVM_REQ_BLOCK_SKIPPED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_ReadAllInit
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the internal flags are prepared for reading 
///                     at initialization phase
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_NvM_ReadAllInit(void)
{
  Mt_NvM_ReadAllInit_TestCase1();
  Mt_NvM_ReadAllInit_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_RestoreBlocksAfterSwChange_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: :    Test that the function NvM_RestoreBlocksAfterSwChange 
///                         checks if a NV block needs to be restored after a requested
///                         SW change
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input       BlockOver                      = FALSE
/// \input       NvMBlockTable[0].Flags_u16     = NVM_FLAG_RESISTANT_TO_SW_CHANGE
///
/// - Expectations: 
///
/// \output   NvM_RestoreBlocksAfterSwChange_RetVal            = TRUE
/// \output   NvM_aAdminTable[0].ErrorStatus                   = NVM_REQ_BLOCK_SKIPPED
///
//-----------------------------------------------------------------------------
void Mt_NvM_RestoreBlocksAfterSwChange_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  BlockOver = FALSE;
  NvMBlockTable[0].Flags_u16    = NVM_FLAG_RESISTANT_TO_SW_CHANGE;

  //Step 3) Call FUT
  NvM_RestoreBlocksAfterSwChange_RetVal = NvM_RestoreBlocksAfterSwChange();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_RestoreBlocksAfterSwChange_RetVal,               TRUE, == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[0].ErrorStatus,     NVM_REQ_BLOCK_SKIPPED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_RestoreBlocksAfterSwChange_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test that the function NvM_RestoreBlocksAfterSwChange 
///                         checks if a NV block needs to be reinitialized after a 
///                         requested SW change
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    NvMBlockTable[0].Flags_u16                  = NVM_FLAG_RESISTANT_TO_SW_CHANGE
/// \input    NvMBlockTable[1].pfnInitCallback            = &Mt_Nvm_Internal_pfnInitCallback_Stub
/// \input    Mt_Nvm_Internal_InitCallback_Stub_HitCount  = 0u
///
/// - Expectations: 
///
/// \output   NvM_RestoreBlocksAfterSwChange_RetVal       = TRUE
/// \output   NvM_aAdminTable[0].ErrorStatus              = NVM_REQ_BLOCK_SKIPPED
/// \output   Mt_Nvm_Internal_InitCallback_Stub_HitCount  = 1u
///
//-----------------------------------------------------------------------------
void Mt_NvM_RestoreBlocksAfterSwChange_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvMBlockTable[0].Flags_u16                  = NVM_FLAG_RESISTANT_TO_SW_CHANGE;
  NvMBlockTable[1].pfnInitCallback            = &Mt_Nvm_Internal_pfnInitCallback_Stub;
  Mt_Nvm_Internal_InitCallback_Stub_HitCount  = 0u;

  //Step 3) Call FUT
  NvM_RestoreBlocksAfterSwChange_RetVal = NvM_RestoreBlocksAfterSwChange();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_RestoreBlocksAfterSwChange_RetVal,              TRUE, == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[0].ErrorStatus,    NVM_REQ_BLOCK_SKIPPED, == );
  AL_UNITTEST_CHECK(Mt_Nvm_Internal_InitCallback_Stub_HitCount,           1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_RestoreBlocksAfterSwChange_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Test that the function NvM_RestoreBlocksAfterSwChange 
///                         checks if a NV block needs to call a callback fct. after a 
///                         requested SW change and initializes the ROM  blocks with RAM data if requested
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    ucNvM_RestoreBlocksAfterSwChange_TestData            = 1u
/// \input    NvMBlockTable[0].Flags_u16                           = NVM_FLAG_RESISTANT_TO_SW_CHANGE
/// \input    NvMBlockTable[NvmBlockFreezeFrameDataPsId].InitRom   = (uint8*)&ucNvM_RestoreBlocksAfterSwChange_TestData
/// \input    NvMBlockTable[NvmBlockFreezeFrameDataPsId].RamMirror = (uint8*)&ucNvM_RestoreBlocksAfterSwChange_TestData
/// \input    Mt_Nvm_Internal_InitCallback_Stub_HitCount  = 0u
///
/// - Expectations: 
///
/// \output   NvM_RestoreBlocksAfterSwChange_RetVal       = TRUE
/// \output   UtilMemCopy_HitCount                        = 1u
///
//-----------------------------------------------------------------------------
void Mt_NvM_RestoreBlocksAfterSwChange_TestCase3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  uint8  ucNvM_RestoreBlocksAfterSwChange_TestData       = 1u;
  NvMBlockTable[0].Flags_u16                             = NVM_FLAG_RESISTANT_TO_SW_CHANGE;
  NvMBlockTable[NvmBlockFreezeFrameDataPsId].InitRom     = (uint8*)&ucNvM_RestoreBlocksAfterSwChange_TestData;
  NvMBlockTable[NvmBlockFreezeFrameDataPsId].RamMirror   = (uint8*)&ucNvM_RestoreBlocksAfterSwChange_TestData;
  UtilMemCopy_HitCount                                   = 0u;

  //Step 3) Call FUT
  NvM_RestoreBlocksAfterSwChange_RetVal = NvM_RestoreBlocksAfterSwChange();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_RestoreBlocksAfterSwChange_RetVal,           TRUE, == );
  AL_UNITTEST_CHECK(UtilMemCopy_HitCount,                              1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_RestoreBlocksAfterSwChange
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test the behaviour for NVM blocks after a SW change
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_NvM_RestoreBlocksAfterSwChange(void)
{
  Mt_NvM_RestoreBlocksAfterSwChange_TestCase1();
  Mt_NvM_RestoreBlocksAfterSwChange_TestCase2();
  Mt_NvM_RestoreBlocksAfterSwChange_TestCase3();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvMStateMachine_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function NvMStateMachine calls correctly
///                         NvM_WriteAll function
///
///    - Test Design Technique: - ET ( Exploratory Testing )
///                             - Requirements-based test
///
/// - Preconditions:
///
/// \input      NvM_eState          = NVM_STATE_IDLE
/// \input      NvM_boNeedsRewrite  = TRUE
///
/// - Expectations: 
///
/// \output     NvM_boNeedsRewrite  = FALSE
///
//-----------------------------------------------------------------------------
void Mt_NvMStateMachine_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_eState          = NVM_STATE_IDLE;
  NvM_boNeedsRewrite  = TRUE;

  //Step 3) Call FUT
  NvMStateMachine();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_boNeedsRewrite, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvMStateMachine_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function NvMStateMachine updates correctly
///                         the NvM state for a READ ALL request
///
///    - Test Design Technique: - ET ( Exploratory Testing )
///                             - Requirements-based test
///
/// - Preconditions:
///
/// \input      NvM_eState                          = NVM_STATE_IDLE
/// \input      NvM_AdminMultiBlock.MultiBlockState = NVM_STATE_READ_ALL
/// \input      NvMBlockTable[1].Flags_u16          = NVM_FLAG_READ_WRITE_ALL
///
/// - Expectations: 
///
/// \output     NvM_eState                          = NVM_STATE_READ_ALL
///
//-----------------------------------------------------------------------------
void Mt_NvMStateMachine_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_eState                          = NVM_STATE_IDLE;
  NvM_AdminMultiBlock.MultiBlockState = NVM_STATE_READ_ALL;
  NvMBlockTable[1].Flags_u16          = NVM_FLAG_READ_WRITE_ALL;

  //Step 3) Call FUT
  NvMStateMachine();
  NvMStateMachine();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_eState,  NVM_STATE_READ_ALL, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvMStateMachine_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function NvMStateMachine updates correctly
///                         the NvM state for a WRITE ALL request
///
///    - Test Design Technique: - ET ( Exploratory Testing )
///                             - Requirements-based test
///
/// - Preconditions:
///
/// \input      NvM_eState                          = NVM_STATE_IDLE
/// \input      NvM_AdminMultiBlock.MultiBlockState = NVM_STATE_WRITE_ALL
/// \input      NvMBlockTable[1].Flags_u16          = NVM_FLAG_READ_WRITE_ALL
///
/// - Expectations: 
///
/// \output     NvM_eState                          = NVM_STATE_WRITE_ALL
///
//-----------------------------------------------------------------------------
void Mt_NvMStateMachine_TestCase3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_eState                          = NVM_STATE_IDLE;
  NvM_AdminMultiBlock.MultiBlockState = NVM_STATE_WRITE_ALL;
  NvMBlockTable[0].Flags_u16          = NVM_FLAG_READ_WRITE_ALL;

  //Step 3) Call FUT
  NvMStateMachine();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_eState, NVM_STATE_WRITE_ALL, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvMStateMachine_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function NvMStateMachine updates correctly
///                         the NvM state
///
///    - Test Design Technique: - ET ( Exploratory Testing )
///                             - Requirements-based test
///
/// - Preconditions:
///
/// \input      NvM_eState                          = NVM_STATE_NOT_INIT
///
/// - Expectations: 
///
/// \output     NvM_eState                          = NVM_STATE_NOT_INIT
///
//-----------------------------------------------------------------------------
void Mt_NvMStateMachine_TestCase4(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_eState = NVM_STATE_NOT_INIT;

  //Step 3) Call FUT
  NvMStateMachine();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_eState, NVM_STATE_NOT_INIT, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvMStateMachine_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function NvMStateMachine updates correctly
///                         the NvM state depending on the Job state
///
///    - Test Design Technique: - ET ( Exploratory Testing )
///                             - Requirements-based test
///
/// - Preconditions:
///
/// \input      NvM_eState                          = NVM_STATE_IDLE
/// \input      NvM_AdminMultiBlock.MultiBlockState = NVM_STATE_IDLE
/// \input      NvmQueue[NvM_ucQueueFront].job      = NVM_STATE_IDLE
/// \input      NvM_GetQueuedBlock_Param1           = &NvmQueue[NvM_ucQueueFront].job
///
/// - Expectations: 
///
/// \output     NvM_eState                          = NVM_STATE_IDLE
///
//-----------------------------------------------------------------------------
void Mt_NvMStateMachine_TestCase5(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_eState                            = NVM_STATE_IDLE;
  NvM_AdminMultiBlock.MultiBlockState   = NVM_STATE_IDLE;
  NvmQueue[NvM_ucQueueFront].job        = NVM_STATE_IDLE;
  NvM_GetQueuedBlock_Param1             = &NvmQueue[NvM_ucQueueFront].job;

  //Step 3) Call FUT
  NvMStateMachine();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_eState, NVM_STATE_IDLE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvMStateMachine_TestCase6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function NvMStateMachine updates correctly
///                         the NvM state for a Read Operation and Job not in idle state
///
///    - Test Design Technique: - ET ( Exploratory Testing )
///                             - Requirements-based test
///
/// - Preconditions:
///
/// \input      NvM_eState                          = NVM_STATE_READ_BLOCK
///
/// - Expectations: 
///
/// \output     NvM_eState                          = NVM_STATE_READ_BLOCK
///
//-----------------------------------------------------------------------------
void Mt_NvMStateMachine_TestCase6(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_eState = NVM_STATE_READ_BLOCK;

  //Step 3) Call FUT
  NvMStateMachine();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_eState, NVM_STATE_READ_BLOCK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvMStateMachine_TestCase7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function NvMStateMachine updates correctly
///                         the NvM state for a Read Operation and Job in idle state
///
///    - Test Design Technique: - ET ( Exploratory Testing )
///                             - Requirements-based test
///
/// - Preconditions:
///
/// \input      NvM_eState                            = NVM_STATE_READ_BLOCK
/// \input      HandleBlockRead_Param2.BlockSubState  = NVM_SUB_STATE_FINALIZE
///
/// - Expectations: 
///
/// \output     NvM_eState                          = NVM_STATE_IDLE
///
//-----------------------------------------------------------------------------
void Mt_NvMStateMachine_TestCase7(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_eState                            = NVM_STATE_READ_BLOCK;
  HandleBlockRead_Param2.BlockSubState  = NVM_SUB_STATE_FINALIZE;

  //Step 3) Call FUT
  NvMStateMachine();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_eState, NVM_STATE_IDLE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvMStateMachine_TestCase8
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function NvMStateMachine updates correctly
///                         the NvM state for a Write Operation and Job in idle state
///
///    - Test Design Technique: - ET ( Exploratory Testing )
///                             - Requirements-based test
///
/// - Preconditions:
///
/// \input      NvM_eState                              = NVM_STATE_WRITE_BLOCK
/// \input      HandleBlockWrite_Param1.MemIfDevice_u8  = MEMIF_JOB_OK
///
/// - Expectations: 
///
/// \output     NvM_eState                              = NVM_STATE_IDLE
///
//-----------------------------------------------------------------------------
void Mt_NvMStateMachine_TestCase8(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_eState                             = NVM_STATE_WRITE_BLOCK;
  HandleBlockWrite_Param1.MemIfDevice_u8 = MEMIF_JOB_OK;

  //Step 3) Call FUT
  NvMStateMachine();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_eState, NVM_STATE_IDLE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvMStateMachine_TestCase9
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function NvMStateMachine updates correctly
///                         the NvM state for a Write Operation and Job not in idle state
///
///    - Test Design Technique: - ET ( Exploratory Testing )
///                             - Requirements-based test
///
/// - Preconditions:
///
/// \input      NvM_eState                              = NVM_STATE_WRITE_BLOCK
/// \input      NvM_aAdminTable[0].BlockState           = NVM_STATE_WRITE_BLOCK
/// \input      HandleBlockWrite_Param2.BlockSubState   = NVM_SUB_STATE_DO_CRC
///
/// - Expectations: 
///
/// \output     NvM_eState                              = NVM_STATE_WRITE_BLOCK
///
//-----------------------------------------------------------------------------
void Mt_NvMStateMachine_TestCase9(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_aAdminTable[0].BlockState           = NVM_STATE_WRITE_BLOCK;
  HandleBlockWrite_Param2.BlockSubState   = NVM_SUB_STATE_DO_CRC;
  NvM_eState                              = NVM_STATE_WRITE_BLOCK;

  //Step 3) Call FUT
  NvMStateMachine();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_eState, NVM_STATE_WRITE_BLOCK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvMStateMachine_TestCase10
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function NvMStateMachine reaches the default case
///                         for an invalid NVM state
///
///    - Test Design Technique: - ET ( Exploratory Testing )
///                             - Requirements-based test
///
/// - Preconditions:
///
/// \input      NvM_eState          = NVM_STATE_SETRAMBLOCKSTATUS
///
/// - Expectations: 
///
/// \output     NvM_eState          = NVM_STATE_SETRAMBLOCKSTATUS
///
//-----------------------------------------------------------------------------
void Mt_NvMStateMachine_TestCase10(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_eState = NVM_STATE_SETRAMBLOCKSTATUS;

  //Step 3) Call FUT
  NvMStateMachine();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_eState, NVM_STATE_SETRAMBLOCKSTATUS, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvMStateMachine
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test all states from the Nvm State Machine
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_NvMStateMachine(void)
{
  Mt_NvMStateMachine_TestCase1();
  Mt_NvMStateMachine_TestCase2();
  Mt_NvMStateMachine_TestCase3();
  Mt_NvMStateMachine_TestCase4();
  Mt_NvMStateMachine_TestCase5();
  Mt_NvMStateMachine_TestCase6();
  Mt_NvMStateMachine_TestCase7();
  Mt_NvMStateMachine_TestCase8();
  Mt_NvMStateMachine_TestCase9();
  Mt_NvMStateMachine_TestCase10();
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_WriteAllMainFunction_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function Nvm_WriteAllMainFunction, after a write all blocks
///                         request was initiated, sets the NV Block States and 
///                         updates the substate of the Admin MultiBlock (for non-skipped blocks)
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input    NvM_AdminMultiBlock.MultiBlockSubState   = NVM_MB_SUB_STATE_INIT
///
/// - Expectations: 
///
/// \output   NvM_AdminMultiBlock.MultiBlockSubState   = NVM_MB_SUB_STATE_PROCESS_BLOCKS
///
//-----------------------------------------------------------------------------
void Mt_Nvm_WriteAllMainFunction_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_AdminMultiBlock.MultiBlockSubState = NVM_MB_SUB_STATE_INIT;

  //Step 3) Call FUT
  Nvm_WriteAllMainFunction();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.MultiBlockSubState, NVM_MB_SUB_STATE_PROCESS_BLOCKS, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_Nvm_WriteAllMainFunction_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function Nvm_WriteAllMainFunction, after a write all blocks
///                         request was initiated, skips blocks with no read/write operation 
///                         (status NVM_REQ_BLOCK_SKIPPED) and checks the next one
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input       NvM_AdminMultiBlock.MultiBlockSubState   = NVM_MB_SUB_STATE_INIT
/// \input       NvMBlockTable[0].Flags_u16               = 0u
/// \input       BlockOver                                = FALSE
///
/// - Expectations: 
///
/// \output      NvM_AdminMultiBlock.MultiBlockSubState   = NVM_MB_SUB_STATE_PROCESS_BLOCKS
/// \output      NvM_AdminMultiBlock.unCurrentBlock       = 1u
///
//-----------------------------------------------------------------------------
void Mt_Nvm_WriteAllMainFunction_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  BlockOver = FALSE;
  NvM_AdminMultiBlock.MultiBlockSubState  = NVM_MB_SUB_STATE_INIT;
  NvMBlockTable[0].Flags_u16              = 0u;

  //Step 3) Call FUT
  Nvm_WriteAllMainFunction();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.MultiBlockSubState, NVM_MB_SUB_STATE_PROCESS_BLOCKS, == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.unCurrentBlock,                                  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_WriteAllMainFunction_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function Nvm_WriteAllMainFunction, processes NVM Blocks and
///                         updates the status of Admin Multi Block if the Block is in IDLE state
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input       NvM_AdminMultiBlock.MultiBlockSubState      = NVM_MB_SUB_STATE_PROCESS_BLOCKS
/// \input       NvM_AdminMultiBlock.unCurrentBlock          = 2u
/// \input       Mt_Nvm_Nvm_WriteAllMainFunction_TestData    = 1u
/// \input       NvMBlockTable[2].RamMirror                  = &Mt_Nvm_Nvm_WriteAllMainFunction_TestData
/// \input       NvM_aAdminTable[2].BlockState               = NVM_STATE_IDLE
///
/// - Expectations: 
///
/// \output      NvM_eState                                  = NVM_STATE_IDLE
/// \output      NvM_AdminMultiBlock.MultiBlockState         = NVM_STATE_IDLE
/// \output      NvM_AdminMultiBlock.SingleBlockErrorStatus  = NVM_REQ_NOT_OK
/// \output      NvM_AdminMultiBlock.ErrorStatus             = NVM_REQ_NOT_OK
/// \output      NvM_AdminMultiBlock.unCurrentBlock          = NvMBlockCount
///
//-----------------------------------------------------------------------------
void Mt_Nvm_WriteAllMainFunction_TestCase3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_AdminMultiBlock.MultiBlockSubState          = NVM_MB_SUB_STATE_PROCESS_BLOCKS;
  NvM_AdminMultiBlock.unCurrentBlock              = 2u;
  uint8 Mt_Nvm_Nvm_WriteAllMainFunction_TestData  = 1u;
  NvMBlockTable[2].RamMirror                      = &Mt_Nvm_Nvm_WriteAllMainFunction_TestData;
  NvM_aAdminTable[2].BlockState                   = NVM_STATE_IDLE;
 
  //Step 3) Call FUT
  Nvm_WriteAllMainFunction();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_eState,                                 NVM_STATE_IDLE, == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.MultiBlockState,        NVM_STATE_IDLE, == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.SingleBlockErrorStatus, NVM_REQ_NOT_OK, == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.ErrorStatus,            NVM_REQ_NOT_OK, == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.unCurrentBlock,          NvMBlockCount, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_WriteAllMainFunction_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function Nvm_WriteAllMainFunction, processes NVM Blocks and
///                         updates the status of Admin  Block if the Block Error
///                         Status is different of NVM_REQ_BLOCK_SKIPPED
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input       NvM_AdminMultiBlock.MultiBlockSubState      = NVM_MB_SUB_STATE_PROCESS_BLOCKS
/// \input       NvM_AdminMultiBlock.unCurrentBlock          = 1u
/// \input       Mt_Nvm_Nvm_WriteAllMainFunction_TestData    = 1u
/// \input       NvMBlockTable[1].RamMirror                  = &Mt_Nvm_Nvm_WriteAllMainFunction_Data
/// \input       NvM_aAdminTable[1].BlockState               = NVM_STATE_IDLE
/// - Expectations: 
///
/// \output      NvM_eState                                  = NVM_STATE_IDLE
/// \output      NvM_aAdminTable[2].BlockState               = NVM_STATE_READ_BLOCK
/// \output      NvM_aAdminTable[2].BlockSubState            = NVM_SUB_STATE_DO_CRC
/// \output      NvM_aAdminTable[2].ErrorStatus              = NVM_REQ_PENDING
/// \output      NvM_AdminMultiBlock.unCurrentBlock          = 2u
///
//-----------------------------------------------------------------------------
void Mt_Nvm_WriteAllMainFunction_TestCase4(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_AdminMultiBlock.MultiBlockSubState          = NVM_MB_SUB_STATE_PROCESS_BLOCKS;
  NvM_AdminMultiBlock.unCurrentBlock              = 1u;
  uint8 Mt_Nvm_Nvm_WriteAllMainFunction_TestData  = 1u;
  NvMBlockTable[1].RamMirror                      = &Mt_Nvm_Nvm_WriteAllMainFunction_TestData;
  NvM_aAdminTable[1].BlockState                   = NVM_STATE_IDLE;
 
  //Step 3) Call FUT
  Nvm_WriteAllMainFunction();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_eState,                             NVM_STATE_IDLE,       == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[2].BlockState,          NVM_STATE_READ_BLOCK, == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[2].BlockSubState,       NVM_SUB_STATE_DO_CRC, == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[2].ErrorStatus,         NVM_REQ_PENDING,      == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.unCurrentBlock,     2u,                   == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_WriteAllMainFunction_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function Nvm_WriteAllMainFunction handles
///                         an invalid  Sub State of an Admin Block
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input       NvM_AdminMultiBlock.MultiBlockSubState      = 2u
///
/// - Expectations: 
///
/// \output      NvM_AdminMultiBlock.MultiBlockSubState      = 2u
///
//-----------------------------------------------------------------------------
void Mt_Nvm_WriteAllMainFunction_TestCase5(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_AdminMultiBlock.MultiBlockSubState = (tieMultiBlockSubState)2u;

  //Step 3) Call FUT
  Nvm_WriteAllMainFunction();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.MultiBlockSubState, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_WriteAllMainFunction_TestCase6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function Nvm_WriteAllMainFunction, processes NVM Blocks and
///                         updates the status of Admin Multi Block if the Block is  in IDLE state but
///                         the error status of the NV block to be processed is NVM_REQ_OK
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input       NvM_AdminMultiBlock.MultiBlockSubState      = NVM_MB_SUB_STATE_PROCESS_BLOCKS
/// \input       NvM_AdminMultiBlock.unCurrentBlock          = 1u
/// \input       NvM_aAdminTable[1].BlockState               = NVM_STATE_IDLE
/// \input       NvM_aAdminTable[1].ErrorStatus              = NVM_REQ_OK
/// - Expectations: 
///
/// \output      NvM_eState                                  = NVM_STATE_IDLE
/// \output      NvM_aAdminTable[2].BlockState               = NVM_STATE_READ_BLOCK
/// \output      NvM_aAdminTable[2].BlockSubState            = NVM_SUB_STATE_DO_CRC
/// \output      NvM_aAdminTable[2].ErrorStatus              = NVM_REQ_PENDING
/// \output      NvM_AdminMultiBlock.unCurrentBlock          = 2u
///
//-----------------------------------------------------------------------------
void Mt_Nvm_WriteAllMainFunction_TestCase6(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_AdminMultiBlock.MultiBlockSubState  = NVM_MB_SUB_STATE_PROCESS_BLOCKS;
  NvM_AdminMultiBlock.unCurrentBlock      = 1u;
  NvM_aAdminTable[1].BlockState           = NVM_STATE_IDLE;
  NvM_aAdminTable[1].ErrorStatus          = NVM_REQ_OK;

  //Step 3) Call FUT
  Nvm_WriteAllMainFunction();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_eState,                               NVM_STATE_IDLE, == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[2].BlockState,      NVM_STATE_READ_BLOCK, == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[2].BlockSubState,   NVM_SUB_STATE_DO_CRC, == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[2].ErrorStatus,          NVM_REQ_PENDING, == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.unCurrentBlock,                   2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_WriteAllMainFunction_TestCase7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Check if the function Nvm_WriteAllMainFunction updates
///                      Admin Multi Block State for out of range NV block 
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input       NvM_AdminMultiBlock.MultiBlockSubState      = NVM_MB_SUB_STATE_INIT
/// \input       BlockOver                                   = TRUE
///
/// - Expectations: 
///
/// \output      NvM_AdminMultiBlock.MultiBlockSubState      = NVM_MB_SUB_STATE_PROCESS_BLOCKS
///
//-----------------------------------------------------------------------------
void Mt_Nvm_WriteAllMainFunction_TestCase7(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  BlockOver = TRUE;
  NvM_AdminMultiBlock.MultiBlockSubState = NVM_MB_SUB_STATE_INIT;

  //Step 3) Call FUT
  Nvm_WriteAllMainFunction();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.MultiBlockSubState, NVM_MB_SUB_STATE_PROCESS_BLOCKS, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_WriteAllMainFunction
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test all substates of writing operation for all Nvm blocks 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Nvm_WriteAllMainFunction(void)
{
  Mt_Nvm_WriteAllMainFunction_TestCase1();
  Mt_Nvm_WriteAllMainFunction_TestCase2();
  Mt_Nvm_WriteAllMainFunction_TestCase3();
  Mt_Nvm_WriteAllMainFunction_TestCase4();
  Mt_Nvm_WriteAllMainFunction_TestCase5();
  Mt_Nvm_WriteAllMainFunction_TestCase6();
  Mt_Nvm_WriteAllMainFunction_TestCase7();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_ReadAllMainFunction_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Check if the function Nvm_ReadAllMainFunction updates
///                      Admin Multi Block State for out of range NV block 
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input       BlockOver                                   = TRUE
/// \input       NvM_AdminMultiBlock.MultiBlockSubState      = NVM_MB_SUB_STATE_INIT
///
/// - Expectations: 
///
/// \output      NvM_AdminMultiBlock.MultiBlockSubState      = NVM_MB_SUB_STATE_PROCESS_BLOCKS
///
//-----------------------------------------------------------------------------
void Mt_Nvm_ReadAllMainFunction_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  BlockOver = TRUE;
  NvM_AdminMultiBlock.MultiBlockSubState = NVM_MB_SUB_STATE_INIT;

  //Step 3) Call FUT
  Nvm_ReadAllMainFunction();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.MultiBlockSubState, NVM_MB_SUB_STATE_PROCESS_BLOCKS, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_ReadAllMainFunction_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function Nvm_ReadAllMainFunction, after a read all blocks
///                         request was initiated, sets the NV Block States and 
///                         updates the substate of the Admin Multi Block
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input       NvM_AdminMultiBlock.MultiBlockSubState   = NVM_MB_SUB_STATE_INIT
/// \input       NvMBlockTable[0].Flags_u16               = 0u        // it gives NVM_REQ_BLOCK_SKIPPED Error Status for 2nd block
/// \input       BlockOver                                = FALSE
/// \input       NvM_AdminMultiBlock.unCurrentBlock       = 0u
///
/// - Expectations: 
///
/// \output      NvM_AdminMultiBlock.MultiBlockSubState   = NVM_MB_SUB_STATE_PROCESS_BLOCKS
/// \output      NvM_aAdminTable[1].BlockState            = NVM_STATE_READ_BLOCK
/// \output      NvM_aAdminTable[1].BlockSubState         = NVM_SUB_STATE_MEM_IF_REQ
/// \output      NvM_aAdminTable[1].ErrorStatus           = NVM_REQ_PENDING
/// \output      NvM_AdminMultiBlock.unCurrentBlock       = 1u
///
//-----------------------------------------------------------------------------
void Mt_Nvm_ReadAllMainFunction_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_AdminMultiBlock.MultiBlockSubState  = NVM_MB_SUB_STATE_INIT;
  NvMBlockTable[0].Flags_u16              = 0u;
  BlockOver                               = FALSE;
  NvM_AdminMultiBlock.unCurrentBlock      = 0u;

  //Step 3) Call FUT
  Nvm_ReadAllMainFunction();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.MultiBlockSubState, NVM_MB_SUB_STATE_PROCESS_BLOCKS, == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[1].BlockState,                     NVM_STATE_READ_BLOCK, == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[1].BlockSubState,              NVM_SUB_STATE_MEM_IF_REQ, == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[1].ErrorStatus,                         NVM_REQ_PENDING, == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.unCurrentBlock,                                  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_ReadAllMainFunction_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function Nvm_ReadAllMainFunction, after a read all blocks
///                         request was initiated, skips blocks with no read/write operation 
///                         (status NVM_REQ_BLOCK_SKIPPED, ReadAllInit = FALSE) and does nothing to the Admin Block
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input       NvM_AdminMultiBlock.MultiBlockSubState = NVM_MB_SUB_STATE_INIT
/// \input       NvMBlockTable[1].Flags_u16             = 0u        // it gives NVM_REQ_BLOCK_SKIPPED Error Status
///
/// - Expectations: 
///
/// \output      NvM_AdminMultiBlock.MultiBlockState   = NVM_STATE_IDLE
/// \output      NvM_AdminMultiBlock.ErrorStatus       = NVM_REQ_OK
/// \output      NvM_AdminMultiBlock.unCurrentBlock    = 0u
/// \output      NvM_eState                            = NVM_STATE_IDLE
///
//-----------------------------------------------------------------------------
void Mt_Nvm_ReadAllMainFunction_TestCase3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_AdminMultiBlock.MultiBlockSubState = NVM_MB_SUB_STATE_INIT;
  NvMBlockTable[1].Flags_u16             = 0u;

  //Step 3) Call FUT
  Nvm_ReadAllMainFunction();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.MultiBlockState,    NVM_STATE_IDLE, == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.ErrorStatus,        NVM_REQ_OK,     == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.unCurrentBlock,                 0u, == );
  AL_UNITTEST_CHECK(NvM_eState,                             NVM_STATE_IDLE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_ReadAllMainFunction_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function Nvm_ReadAllMainFunction, after a read all blocks
///                         request was initiated, for the requested NVM_MB_SUB_STATE_PROCESS_BLOCKS 
///                         operation updates the Admin Multi Block content and Nvm status if the block
///                         state is in idle mode
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input       NvM_AdminMultiBlock.MultiBlockSubState = NVM_MB_SUB_STATE_PROCESS_BLOCKS
/// \input       NvM_AdminMultiBlock.unCurrentBlock     = 2u
/// \input       NvMBlockTable[2].MemIfDevice_u8        = MEMIF_JOB_CANCELLED
/// \input       NvM_aAdminTable[2].BlockState          = NVM_STATE_IDLE
/// \input       NvM_aAdminTable[2].BlockSubState       = NVM_SUB_STATE_MEM_IF_REQ
/// \input       NvM_aAdminTable[2].ErrorStatus         = NVM_REQ_NOT_OK
///
/// - Expectations: 
///
/// \output      NvM_AdminMultiBlock.SingleBlockErrorStatus  = NVM_REQ_NOT_OK;
/// \output      NvM_eState                                  = NVM_STATE_IDLE
/// \output      NvM_boNeedsRewrite                          = TRUE
/// \output      NvM_AdminMultiBlock.MultiBlockState         = NVM_STATE_IDLE
/// \output      NvM_AdminMultiBlock.ErrorStatus             = NVM_REQ_NOT_OK
/// \output      NvM_AdminMultiBlock.unCurrentBlock          = NvMBlockCount
///
//-----------------------------------------------------------------------------
void Mt_Nvm_ReadAllMainFunction_TestCase4(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_AdminMultiBlock.MultiBlockSubState     = NVM_MB_SUB_STATE_PROCESS_BLOCKS;
  NvM_AdminMultiBlock.unCurrentBlock         = 2u;
  NvMBlockTable[2].MemIfDevice_u8            = MEMIF_JOB_CANCELLED;
  NvM_aAdminTable[2].BlockState              = NVM_STATE_IDLE;
  NvM_aAdminTable[2].BlockSubState           = NVM_SUB_STATE_MEM_IF_REQ;
  NvM_aAdminTable[2].ErrorStatus             = NVM_REQ_NOT_OK;

  //Step 3) Call FUT
  Nvm_ReadAllMainFunction();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.SingleBlockErrorStatus, NVM_REQ_NOT_OK, == );
  AL_UNITTEST_CHECK(NvM_eState,                                 NVM_STATE_IDLE, == );
  AL_UNITTEST_CHECK(NvM_boNeedsRewrite,                                   TRUE, == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.MultiBlockState,        NVM_STATE_IDLE, == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.ErrorStatus,            NVM_REQ_NOT_OK, == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.unCurrentBlock,         NvMBlockCount,  == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_ReadAllMainFunction_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function Nvm_ReadAllMainFunction, after a read all blocks
///                         request was initiated, for the requested NVM_MB_SUB_STATE_PROCESS_BLOCKS 
///                         operation updates the Admin  Block content and Nvm status if the block
///                         state is in idle mode and error status is not NVM_REQ_BLOCK_SKIPPED
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input       NvM_AdminMultiBlock.MultiBlockSubState      = NVM_MB_SUB_STATE_PROCESS_BLOCKS
/// \input       NvM_AdminMultiBlock.unCurrentBlock          = 1u
/// \input       NvMBlockTable[1].MemIfDevice_u8             = MEMIF_JOB_CANCELLED
/// \input       NvM_aAdminTable[1].BlockState               = NVM_STATE_IDLE
/// \input       NvM_aAdminTable[1].BlockSubState            = NVM_SUB_STATE_DO_CRC
///
/// - Expectations: 
///
/// \output      NvM_eState                                  = NVM_STATE_IDLE
/// \output      NvM_aAdminTable[2].BlockState               = NVM_STATE_READ_BLOCK
/// \output      NvM_aAdminTable[2].BlockSubState            = NVM_SUB_STATE_MEM_IF_REQ
/// \output      NvM_aAdminTable[2].ErrorStatus              = NVM_REQ_PENDING
/// \output      NvM_AdminMultiBlock.unCurrentBlock          = 2u
///
//-----------------------------------------------------------------------------
void Mt_Nvm_ReadAllMainFunction_TestCase5(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_AdminMultiBlock.MultiBlockSubState     = NVM_MB_SUB_STATE_PROCESS_BLOCKS;
  NvM_AdminMultiBlock.unCurrentBlock         = 1u;
  NvMBlockTable[1].MemIfDevice_u8            = MEMIF_JOB_CANCELLED;
  NvM_aAdminTable[1].BlockState              = NVM_STATE_IDLE;
  NvM_aAdminTable[1].BlockSubState           = NVM_SUB_STATE_DO_CRC;

  //Step 3) Call FUT
  Nvm_ReadAllMainFunction();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_eState,                             NVM_STATE_IDLE,           == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[2].BlockState,          NVM_STATE_READ_BLOCK,     == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[2].BlockSubState,       NVM_SUB_STATE_MEM_IF_REQ, == );
  AL_UNITTEST_CHECK(NvM_aAdminTable[2].ErrorStatus,         NVM_REQ_PENDING,          == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.unCurrentBlock,     2u,                       == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_ReadAllMainFunction_TestCase6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function Nvm_ReadAllMainFunction, after a read all blocks
///                         request was initiated, for the requested NVM_MB_SUB_STATE_PROCESS_BLOCKS 
///                         operation updates the admin multi block content and Nvm status if the block
///                         state is in idle mode, error status is OK and Config Block has been done successfully
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input       NvM_AdminMultiBlock.MultiBlockSubState      = NVM_MB_SUB_STATE_PROCESS_BLOCKS
/// \input       NvM_AdminMultiBlock.unCurrentBlock          = 2u
/// \input       NvMBlockTable[2].MemIfDevice_u8             = MEMIF_JOB_CANCELLED
/// \input       NvM_aAdminTable[2].BlockState               = NVM_STATE_IDLE
/// \input       NvM_aAdminTable[2].BlockSubState            = NVM_SUB_STATE_DO_CRC
/// \input       NvM_aAdminTable[2].ErrorStatus              = NVM_REQ_OK
/// \input       NvM_aAdminTable[NvmBlockConfigBlockId].ErrorStatus = 0
///
/// - Expectations: 
///
/// \output      NvM_AdminMultiBlock.MultiBlockState         = NVM_STATE_IDLE
/// \output      NvM_AdminMultiBlock.unCurrentBlock          = NvMBlockCount
/// \output      NvM_boNeedsRewrite                          = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Nvm_ReadAllMainFunction_TestCase6(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_AdminMultiBlock.MultiBlockSubState              = NVM_MB_SUB_STATE_PROCESS_BLOCKS;
  NvM_AdminMultiBlock.unCurrentBlock                  = 2u;
  NvMBlockTable[2].MemIfDevice_u8                     = MEMIF_JOB_CANCELLED;
  NvM_aAdminTable[2].BlockState                       = NVM_STATE_IDLE;
  NvM_aAdminTable[2].BlockSubState                    = NVM_SUB_STATE_DO_CRC;
  NvM_aAdminTable[2].ErrorStatus                      = NVM_REQ_OK;
  NvM_aAdminTable[NvmBlockConfigBlockId].ErrorStatus  = 0;

  //Step 3) Call FUT
  Nvm_ReadAllMainFunction();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.MultiBlockState, NVM_STATE_IDLE, == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.unCurrentBlock,   NvMBlockCount, == );
  AL_UNITTEST_CHECK(NvM_boNeedsRewrite,                            TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_ReadAllMainFunction_TestCase7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function Nvm_ReadAllMainFunction, after a read all blocks
///                         request was initiated, for the requested NVM_MB_SUB_STATE_PROCESS_BLOCKS 
///                         operation updates the admin multi block content and Nvm status if the block
///                         state is in idle mode, error status is OK BUT Config Block has failed
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input       NvM_AdminMultiBlock.MultiBlockSubState      = NVM_MB_SUB_STATE_PROCESS_BLOCKS
/// \input       NvM_AdminMultiBlock.unCurrentBlock          = 2u
/// \input       NvMBlockTable[2].MemIfDevice_u8             = MEMIF_JOB_CANCELLED
/// \input       NvM_aAdminTable[2].BlockState               = NVM_STATE_IDLE
/// \input       NvM_aAdminTable[2].BlockSubState            = NVM_SUB_STATE_DO_CRC
/// \input       NvM_aAdminTable[2].ErrorStatus              = NVM_REQ_OK
/// \input       NvM_aAdminTable[NvmBlockConfigBlockId].ErrorStatus = 0
///
/// \input       DefaultConfigBlock.reserved                = 15u
/// \input       NvM_GetDefaultConfigBlock_Param1           = DefaultConfigBlock
/// \input       NvmBlockConfigBlock.reserved               = 25u
/// - Expectations: 
///
/// \output      NvM_AdminMultiBlock.unCurrentBlock          = NvMBlockCount
/// \output      NvM_AdminMultiBlock.MultiBlockState         = NVM_STATE_IDLE
/// \output      NvM_boNeedsRewrite                          = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Nvm_ReadAllMainFunction_TestCase7(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_AdminMultiBlock.MultiBlockSubState     = NVM_MB_SUB_STATE_PROCESS_BLOCKS;
  NvM_AdminMultiBlock.unCurrentBlock         = 2u;
  NvMBlockTable[2].MemIfDevice_u8            = MEMIF_JOB_CANCELLED;
  NvM_aAdminTable[2].BlockState              = NVM_STATE_IDLE;
  NvM_aAdminTable[2].BlockSubState           = NVM_SUB_STATE_DO_CRC;
  NvM_aAdminTable[2].ErrorStatus             = NVM_REQ_OK;
  NvM_aAdminTable[NvmBlockConfigBlockId].ErrorStatus = 0;

  tNvMConfigBlock DefaultConfigBlock;
  DefaultConfigBlock.reserved                = 15u;
  NvM_GetDefaultConfigBlock_Param1           = DefaultConfigBlock;
  NvmBlockConfigBlock.reserved               = 25u;

  //Step 3) Call FUT
  Nvm_ReadAllMainFunction();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.unCurrentBlock,                NvMBlockCount, == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.MultiBlockState,              NVM_STATE_IDLE, == );
  AL_UNITTEST_CHECK(NvM_boNeedsRewrite,                                         TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_ReadAllMainFunction_TestCase8
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Check if the function Nvm_ReadAllMainFunction handles
///                      an invalid  Sub State of an Admin Block
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input       NvM_AdminMultiBlock.MultiBlockSubState      = 2u
///
/// - Expectations: 
///
/// \output      NvM_AdminMultiBlock.MultiBlockSubState      = 2u
///
//-----------------------------------------------------------------------------
void Mt_Nvm_ReadAllMainFunction_TestCase8(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_AdminMultiBlock.MultiBlockSubState = (tieMultiBlockSubState)2u;
  //Step 3) Call FUT
  Nvm_ReadAllMainFunction();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.MultiBlockSubState, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_ReadAllMainFunction_TestCase9
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function Nvm_ReadAllMainFunction, after a read all blocks
///                         request was initiated, for the requested NVM_MB_SUB_STATE_PROCESS_BLOCKS 
///                         operation updates the admin multi block content and Nvm status if the block
///                         state is in idle mode but error status is NVM_REQ_OK
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input       NvM_AdminMultiBlock.MultiBlockSubState      = NVM_MB_SUB_STATE_PROCESS_BLOCKS
/// \input       NvM_AdminMultiBlock.unCurrentBlock          = 1u
/// \input       HandleBlockRead_Param2.BlockSubState        = NVM_SUB_STATE_DO_CRC
/// \input       HandleBlockRead_Param2.NvCrc                = 0u
/// \input       HandleBlockRead_Param2.RamCrc               = 0u
///
/// - Expectations: 
///
/// \output      NvM_aAdminTable[1].ErrorStatus              = NVM_REQ_OK
/// \output      NvM_AdminMultiBlock.MultiBlockState         = NVM_STATE_IDLE
/// \output      NvM_AdminMultiBlock.unCurrentBlock          = 2u
///
//----------------------------------------------------------------------------- 
void Mt_Nvm_ReadAllMainFunction_TestCase9(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_AdminMultiBlock.MultiBlockSubState  = NVM_MB_SUB_STATE_PROCESS_BLOCKS;
  NvM_AdminMultiBlock.unCurrentBlock      = 1u;
  HandleBlockRead_Param2.BlockSubState    = NVM_SUB_STATE_DO_CRC;
  HandleBlockRead_Param2.NvCrc            = 0u;
  HandleBlockRead_Param2.RamCrc           = 0u;

  //Step 3) Call FUT
  Nvm_ReadAllMainFunction();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_aAdminTable[1].ErrorStatus,           NVM_REQ_OK, == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.MultiBlockState,  NVM_STATE_IDLE, == );
  AL_UNITTEST_CHECK(NvM_AdminMultiBlock.unCurrentBlock,               2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_ReadAllMainFunction
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test all substates of reading operation for all Nvm blocks 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Nvm_ReadAllMainFunction(void)
{
  Mt_Nvm_ReadAllMainFunction_TestCase1();
  Mt_Nvm_ReadAllMainFunction_TestCase2();
  Mt_Nvm_ReadAllMainFunction_TestCase3();
  Mt_Nvm_ReadAllMainFunction_TestCase4();
  Mt_Nvm_ReadAllMainFunction_TestCase5();
  Mt_Nvm_ReadAllMainFunction_TestCase6();
  Mt_Nvm_ReadAllMainFunction_TestCase7();
  Mt_Nvm_ReadAllMainFunction_TestCase8();
  Mt_Nvm_ReadAllMainFunction_TestCase9();

}

//-----------------------------------------------------------------------------
//Nvm_Id.c
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvmCheckConfigBlock_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Check that  NvmCheckConfigBlock function returns the
///                      status of ConfigBlock
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///     Nvm_InitConfigBlock() not called => NvmBlockConfigBlock not initialized
///
/// \input    NvM_GetDefaultConfigBlock_Param1.strVersion[0] = 0u
/// \input    NvmBlockConfigBlock.reserved                   = 25u
///
/// - Expectations: 
///
/// \output   NvmCheckConfigBlock_RetVal   = E_NOT_OK
///
//-----------------------------------------------------------------------------
void Mt_NvmCheckConfigBlock_TestCase1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_GetDefaultConfigBlock_Param1.strVersion[0] = 0u;
  NvmBlockConfigBlock.reserved                   = 25u;

  //Step 3) Call FUT
  NvmCheckConfigBlock_RetVal = NvmCheckConfigBlock();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvmCheckConfigBlock_RetVal,   E_NOT_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvmCheckConfigBlock_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   Check that  NvmCheckConfigBlock function returns the
///                      status of ConfigBlock
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///     Nvm_InitConfigBlock()  called => NvmBlockConfigBlock is initialized
///
/// \input       NvM_GetDefaultConfigBlock_Param1.strVersion[0] = 0u
/// \input       NvmBlockConfigBlock.reserved                   = 0u
///
/// - Expectations: 
///
/// \output   NvmCheckConfigBlock_RetVal   = E_OK
///
//-----------------------------------------------------------------------------
void Mt_NvmCheckConfigBlock_TestCase2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_GetDefaultConfigBlock_Param1.strVersion[0] = 0u;
  NvmBlockConfigBlock.reserved                   = 0u;

  //Step 3) Call FUT
  NvmCheckConfigBlock_RetVal = NvmCheckConfigBlock();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvmCheckConfigBlock_RetVal, E_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvmCheckConfigBlock
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check the content of the NvmBlockConfigBlock with
///                     respect to DefaultConfigBlock
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_NvmCheckConfigBlock(void)
{
   Mt_NvmCheckConfigBlock_TestCase1();
   Mt_NvmCheckConfigBlock_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Nvm_InitConfigBlock
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function Nvm_InitConfigBlock initializes
///                         NvmBlockConfigBlock with default configuration
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input     NvM_GetDefaultConfigBlock_Param1.strVersion[0] = 0u
///
/// - Expectations: 
///
/// \output   NvM_GetDefaultConfigBlock_Param1.strVersion[]   = 0u  (null)
///
//-----------------------------------------------------------------------------
void Mt_Nvm_InitConfigBlock(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvM_GetDefaultConfigBlock_Param1.strVersion[0] = 0u;

  //Step 3) Call FUT
  Nvm_InitConfigBlock();

  //Step 4) Check expected output values
  for (uint8 ucIdx = 0; ucIdx < 11; ucIdx++)
  {
    AL_UNITTEST_CHECK(NvM_GetDefaultConfigBlock_Param1.strVersion[ucIdx], 0u, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_NvM_GetDefaultConfigBlock
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:      Check if the function NvM_GetDefaultConfigBlock copies the
///                         default NVM Config. Block into NvmBlockConfigBlock
///
///    - Test Design Technique: ET ( Exploratory Testing )
///
/// - Preconditions:
///
/// \input       NvM_GetDefaultConfigBlock_Param1.strVersion[0]       = 0u
///
/// - Expectations: 
///
/// \output      NvM_GetDefaultConfigBlock_Param1.aucKeyBytes[0]  = TIME
/// \output      NvM_GetDefaultConfigBlock_Param1.aucKeyBytes[1]  = TIME
/// \output      NvM_GetDefaultConfigBlock_Param1.aucKeyBytes[2]  = TIME
/// \output      (NvM_GetDefaultConfigBlock_Param1.strVersion[0]  = ASCII CHAR
/// \output      (NvM_GetDefaultConfigBlock_Param1.strVersion[1]  = ASCII CHAR
/// \output      (NvM_GetDefaultConfigBlock_Param1.strVersion[2]  = ASCII CHAR
/// \output      (NvM_GetDefaultConfigBlock_Param1.strVersion[3]  = ASCII CHAR
/// \output      (NvM_GetDefaultConfigBlock_Param1.strVersion[4]  = ASCII CHAR
/// \output      (NvM_GetDefaultConfigBlock_Param1.strVersion[5]  = ASCII CHAR
/// \output      (NvM_GetDefaultConfigBlock_Param1.strVersion[6]  = ASCII CHAR
/// \output      (NvM_GetDefaultConfigBlock_Param1.strVersion[7]  = ASCII CHAR
/// \output      (NvM_GetDefaultConfigBlock_Param1.strVersion[8]  = ASCII CHAR
/// \output      (NvM_GetDefaultConfigBlock_Param1.strVersion[9]  = ASCII CHAR
/// \output      (NvM_GetDefaultConfigBlock_Param1.strVersion[10] = ASCII CHAR
/// \output      (NvM_GetDefaultConfigBlock_Param1.strVersion[11] = END OF STRING
///
//-----------------------------------------------------------------------------
void Mt_NvM_GetDefaultConfigBlock(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  uint8 ucIdx = 0;

  //Step 3) Call FUT
  NvM_GetDefaultConfigBlock(&NvM_GetDefaultConfigBlock_Param1);

  //Step 4) Check expected output values

  //e.g time "10:14:35"   aucKeyBytes[0] = 1 
  //                      aucKeyBytes[1] = 4 
  //                      aucKeyBytes[2] = 3 
  //                      aucKeyBytes[3] = 5 

  //check if aucKeyBytes[ucIdx] is in between ASCII 48 (DEC 0) and ASCII 53 (DEC 5) 
  if ((NvM_GetDefaultConfigBlock_Param1.aucKeyBytes[0] >= 48u && NvM_GetDefaultConfigBlock_Param1.aucKeyBytes[0] <= 53u) &&
    (NvM_GetDefaultConfigBlock_Param1.aucKeyBytes[2] >= 48u && NvM_GetDefaultConfigBlock_Param1.aucKeyBytes[2] <= 53u))
  {
    //time-dependent variable, therefore is tested against itself
    AL_UNITTEST_CHECK(NvM_GetDefaultConfigBlock_Param1.aucKeyBytes[0], NvM_GetDefaultConfigBlock_Param1.aucKeyBytes[0], == );
    AL_UNITTEST_CHECK(NvM_GetDefaultConfigBlock_Param1.aucKeyBytes[2], NvM_GetDefaultConfigBlock_Param1.aucKeyBytes[2], == );
  }
  else
  {
    AL_UNITTEST_CHECK(NvM_GetDefaultConfigBlock_Param1.aucKeyBytes[0], -1u, == );
    AL_UNITTEST_CHECK(NvM_GetDefaultConfigBlock_Param1.aucKeyBytes[2], -1u, == );
  }

  //check if aucKeyBytes[ucIdx] is in between ASCII 48 (DEC 0) and ASCII 57 (DEC 9) 
  if ((NvM_GetDefaultConfigBlock_Param1.aucKeyBytes[1] >= 48u && NvM_GetDefaultConfigBlock_Param1.aucKeyBytes[1] <= 57u) &&
    (NvM_GetDefaultConfigBlock_Param1.aucKeyBytes[3] >= 48u && NvM_GetDefaultConfigBlock_Param1.aucKeyBytes[3] <= 57u))
  {
    //time-dependent variable, therefore is tested against itself
    AL_UNITTEST_CHECK(NvM_GetDefaultConfigBlock_Param1.aucKeyBytes[1], NvM_GetDefaultConfigBlock_Param1.aucKeyBytes[1], == );
    AL_UNITTEST_CHECK(NvM_GetDefaultConfigBlock_Param1.aucKeyBytes[3], NvM_GetDefaultConfigBlock_Param1.aucKeyBytes[3], == );
  }
  else
  {
    AL_UNITTEST_CHECK(NvM_GetDefaultConfigBlock_Param1.aucKeyBytes[0], -1u, == );
    AL_UNITTEST_CHECK(NvM_GetDefaultConfigBlock_Param1.aucKeyBytes[2], -1u, == );
  }

  //check string size, always 11 (10+1=11 ASCII chars plus end of string terminator)
  AL_UNITTEST_CHECK(sizeof(NvM_GetDefaultConfigBlock_Param1.strVersion), 11u, == );

  //check if strVersion[ucIdx] contains uppercase letters and numbers (between ASCII 48 (DEC 0) and ASCII 57 (DEC 9) OR between ASCII 65 ('A') and ASCII 90 ('Z') )
  for (ucIdx = 0u; ucIdx < sizeof(NvM_GetDefaultConfigBlock_Param1.strVersion) - 1; ucIdx++)
  {
    if ( ((NvM_GetDefaultConfigBlock_Param1.strVersion[ucIdx] >= 48u) && (NvM_GetDefaultConfigBlock_Param1.strVersion[ucIdx] <= 57u)) || 
         ((NvM_GetDefaultConfigBlock_Param1.strVersion[ucIdx] >= 65u) && (NvM_GetDefaultConfigBlock_Param1.strVersion[ucIdx] <= 90u)) )
    {
      AL_UNITTEST_CHECK(NvM_GetDefaultConfigBlock_Param1.strVersion[ucIdx], NvM_GetDefaultConfigBlock_Param1.strVersion[ucIdx], == );
    }
    else
    {
      AL_UNITTEST_CHECK(NvM_GetDefaultConfigBlock_Param1.strVersion[ucIdx], -1u, == );

    }
  }

  AL_UNITTEST_CHECK(NvM_GetDefaultConfigBlock_Param1.strVersion[11], 0u, == ); //End of string termiantor

}

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

  //Nvm_Id.c
  ALUnitTest_AddFunction("Mt_Nvm_InitConfigBlock",                    Mt_Nvm_InitConfigBlock);
  ALUnitTest_AddFunction("Mt_NvM_GetDefaultConfigBlock",              Mt_NvM_GetDefaultConfigBlock);
  ALUnitTest_AddFunction("Mt_NvmCheckConfigBlock",                    Mt_NvmCheckConfigBlock); 

  //ctaaNvm.c
  ALUnitTest_AddFunction("Mt_riNvM_Init",                             Mt_riNvM_Init);
  ALUnitTest_AddFunction("Mt_rpNvM_Cycle0",                           Mt_rpNvM_Cycle0);
  
  //Nvm.c
  ALUnitTest_AddFunction("Mt_NvM_Init",                               Mt_NvM_Init);
  ALUnitTest_AddFunction("Mt_NvM_MainFunction",                       Mt_NvM_MainFunction);
  ALUnitTest_AddFunction("Mt_NvM_GetState",                           Mt_NvM_GetState);
  ALUnitTest_AddFunction("Mt_NvM_WriteAll",                           Mt_NvM_WriteAll);
  ALUnitTest_AddFunction("Mt_NvM_ReadAll",                            Mt_NvM_ReadAll);
  ALUnitTest_AddFunction("Mt_NvM_CancelWriteAll",                     Mt_NvM_CancelWriteAll);
  ALUnitTest_AddFunction("Mt_NvM_GetErrorStatus",                     Mt_NvM_GetErrorStatus);
  ALUnitTest_AddFunction("Mt_NvM_WriteBlock",                         Mt_NvM_WriteBlock);
  ALUnitTest_AddFunction("Mt_NvM_ReadBlock",                          Mt_NvM_ReadBlock);
  ALUnitTest_AddFunction("Mt_reNvm_WritePxlData",                     Mt_reNvm_WritePxlData);

  //Nvm_Internal.c
  ALUnitTest_AddFunction("Mt_MemIfReadCrc",                           Mt_MemIfReadCrc);
  ALUnitTest_AddFunction("Mt_MemIfWriteCrc",                          Mt_MemIfWriteCrc);
  ALUnitTest_AddFunction("Mt_NvM_ClearQueue",                         Mt_NvM_ClearQueue);
  ALUnitTest_AddFunction("Mt_NwM_IsQueueFull",                        Mt_NwM_IsQueueFull);
  ALUnitTest_AddFunction("Mt_NwM_IsQueueEmpty",                       Mt_NwM_IsQueueEmpty);
  ALUnitTest_AddFunction("Mt_NvM_QueueBlock",                         Mt_NvM_QueueBlock);
  ALUnitTest_AddFunction("Mt_NvM_GetQueuedBlock",                     Mt_NvM_GetQueuedBlock);
  ALUnitTest_AddFunction("Mt_Nvm_HandleBlockWrite",                   Mt_Nvm_HandleBlockWrite);
  ALUnitTest_AddFunction("Mt_Nvm_HandleBlockRead",                    Mt_Nvm_HandleBlockRead);
  ALUnitTest_AddFunction("Mt_NvM_WriteAllInit",                       Mt_NvM_WriteAllInit);
  ALUnitTest_AddFunction("Mt_NvM_ReadAllInit",                        Mt_NvM_ReadAllInit);
  ALUnitTest_AddFunction("Mt_NvM_RestoreBlocksAfterSwChange",         Mt_NvM_RestoreBlocksAfterSwChange);
  ALUnitTest_AddFunction("Mt_NvMStateMachine",                        Mt_NvMStateMachine);
  ALUnitTest_AddFunction("Mt_Nvm_WriteAllMainFunction",               Mt_Nvm_WriteAllMainFunction);
  ALUnitTest_AddFunction("Mt_Nvm_ReadAllMainFunction",                Mt_Nvm_ReadAllMainFunction);

}