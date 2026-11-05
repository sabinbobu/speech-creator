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
/// \brief  Unit Test Cases for Fee module
///
/// \author Bodian Bianca Dorina (F31199D)
///         mailTo:bianca-dorina.bodian[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================================================================================================
//  Files covered by this module unit test:
//            - ctaaFee.c
//            - Fee_Cfg.c
//            - Fee.c
//            - Fee_InternalFct.c
//=============================================================================================================================================================

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
//  ctaaFee.c
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_riFee_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the initialization runnable does the Flash Driver
///                     Initialization, the Flash Driver Partitioning and Sets the
///                     FlexRam function as EEPROM emulated
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input Fee_State                              = FEE_STATE_NOT_INIT
/// \input FLASH_DRV_DEFlashPartition_HitCount    = 0u
/// \input FLASH_DRV_Init_HitCount                = 0u
/// \input FLASH_DRV_SetFlexRamFunction_HitCount  = 0u
///
/// - Expectations:
///
/// \output Fee_State                              = FEE_STATE_IDLE
/// \output Fee_t_Status                           = MEMIF_IDLE
/// \output FLASH_DRV_DEFlashPartition_HitCount    = 1u
/// \output FLASH_DRV_Init_HitCount                = 2u
/// \output FLASH_DRV_SetFlexRamFunction_HitCount  = 1u
///
//-----------------------------------------------------------------------------
void Mt_riFee_Init(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Fee_State = FEE_STATE_NOT_INIT;
  FLASH_DRV_DEFlashPartition_HitCount   = 0u;
  FLASH_DRV_Init_HitCount               = 0u;
  FLASH_DRV_SetFlexRamFunction_HitCount = 0u;

  //Step 3) Call FUT
  riFee_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Fee_State,                 FEE_STATE_IDLE, == );
  AL_UNITTEST_CHECK(Fee_t_Status,                  MEMIF_IDLE, == );
  AL_UNITTEST_CHECK(FLASH_DRV_DEFlashPartition_HitCount,   1u, == );
  AL_UNITTEST_CHECK(FLASH_DRV_Init_HitCount,               2u, == );
  AL_UNITTEST_CHECK(FLASH_DRV_SetFlexRamFunction_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_rpFee_Cycle0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the cyclic runnable calls the FeeStateMachine
///                     in case the Fee complete interrupt flag is set and
///                     updates the Fee State and the Job Result
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input Fee_State        = FEE_STATE_WRITE
/// \input FTFC->FSTAT      = FTFC_FSTAT_CCIF_MASK
/// \input FTFC->FCNFG      = FTFC_FCNFG_EEERDY_MASK
/// \input Fee_JobResult    = MEMIF_JOB_PENDING
///
/// - Expectations:
///
/// \output Fee_State       = FEE_STATE_IDLE
/// \output Fee_JobResult   = MEMIF_JOB_OK
///
//-----------------------------------------------------------------------------
void Mt_rpFee_Cycle0(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Fee_State     = FEE_STATE_WRITE;
  FTFC->FSTAT   = FTFC_FSTAT_CCIF_MASK;
  FTFC->FCNFG   = FTFC_FCNFG_EEERDY_MASK;
  Fee_JobResult = MEMIF_JOB_PENDING;

  //Step 3) Call FUT
  rpFee_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Fee_State,                  FEE_STATE_IDLE, == );
  AL_UNITTEST_CHECK(Fee_JobResult,                MEMIF_JOB_OK, == );
}


//-----------------------------------------------------------------------------
//  Fee_InternalFct.c
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/// \Test Case : Mt_FeeStateMachine
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the State Machine executes correctly the inputs
///                     and sets the corresponding state of Fee state information and 
///                     Job operation status based on input conditions and in some cases based
///                     on the completion of the memory operation (checking of interrupt flag)
///
///    - Test Design Technique: DT (Decision Table)
///
///    - Preconditions: Fee State and Job Result in initial state
///
/// \input  Fee_State_In : actual Flash Status 
/// \input  FTFCFlag     : flash operation flag  status Flash operation status flag (EEE operation not completed )
///
///    - Expected test results: 
///        - return the FEE state information and Job operation Status
///        - note: 2 conditions are needed to get the FEE information:
/// \output Fee_State         : resulting FEE status
/// \output Fee_JobResult_Out : Flash Job updated operation status

//-----------------------------------------------------------------------------
void Mt_FeeStateMachine(void)
{
  //Step 1) Set pre - conditions
  //initial status of the Fee flags
  Fee_State     = FEE_STATE_NOT_INIT;
  Fee_JobResult = MEMIF_JOB_OK;

  struct { tieFeeState Fee_State_In;  uint8 FTFCFlag; tieFeeState Fee_State_Out;  MemIf_JobResultType Fee_JobResult_Out; } asTestCaseData[]
    = { {        FEE_STATE_NOT_INIT,              0u,         FEE_STATE_NOT_INIT,                          MEMIF_JOB_OK  },
        {            FEE_STATE_IDLE,              0u,         FEE_STATE_NOT_INIT,                          MEMIF_JOB_OK  },
        {           FEE_STATE_WRITE,              0u,         FEE_STATE_NOT_INIT,                   MEMIF_BLOCK_INVALID  },
        {           FEE_STATE_WRITE, FTFC_FSTAT_CCIF_MASK,        FEE_STATE_IDLE,                          MEMIF_JOB_OK  },
        {            FEE_STATE_READ,              0u,             FEE_STATE_IDLE,                   MEMIF_BLOCK_INVALID  },
        {            FEE_STATE_READ, FTFC_FSTAT_CCIF_MASK,        FEE_STATE_IDLE,                          MEMIF_JOB_OK  },
        {        FEE_STATE_READ_ALL,              0u,             FEE_STATE_IDLE,                          MEMIF_JOB_OK  },
        {           FEE_STATE_ERROR,              0u,             FEE_STATE_IDLE,                          MEMIF_JOB_OK  },
        {                      255u,              0u,             FEE_STATE_IDLE,                          MEMIF_JOB_OK  },  }; // default state
    
  for (uint32 ulIdx = 0; ulIdx < _countof(asTestCaseData); ulIdx++)
  {
    //Step 2) Assign all input values to the corresponding input variables identified in the FUT
    FeeStateMachine_Param1 = asTestCaseData[ulIdx].Fee_State_In;
    FTFC->FSTAT            = asTestCaseData[ulIdx].FTFCFlag;

    //Step 3) Call the FUT
    FeeStateMachine(FeeStateMachine_Param1);

    //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
    AL_UNITTEST_CHECK(Fee_State,          asTestCaseData[ulIdx].Fee_State_Out, == );
    AL_UNITTEST_CHECK(Fee_JobResult,  asTestCaseData[ulIdx].Fee_JobResult_Out, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_LookUpIndex
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function returns the index from the FeeBlockTable
///                     array of the block id given as parameter
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions: 
///
/// \input unBlockNumber : flash block index either valid or not in range
///
/// - Expectations:
///
/// \output unFeeBlockIdx : the index computed from FeeBlockTable
///
//-----------------------------------------------------------------------------
void Mt_Fee_LookUpIndex(void)
{
  //Step 1: Set pre-conditions
  Fee_LookUpIndex_RetVal = 0u;

  struct { uint16  unBlockNumber;  uint16  unFeeBlockIdx; } asTestCaseData[]
    = {  {                    2u,     FeeBlockDemDataId,  },
         {         FeeBlockCount,               0xFFFFu,  }, };

  for (uint32 ulIdx = 0; ulIdx < _countof(asTestCaseData); ulIdx++)
  {
    //Step 2) Assign Input values
    Fee_LookUpIndex_Param1 = asTestCaseData[ulIdx].unBlockNumber;

    //Step 3) Call FUT
    Fee_LookUpIndex_RetVal = Fee_LookUpIndex(Fee_LookUpIndex_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Fee_LookUpIndex_RetVal, asTestCaseData[ulIdx].unFeeBlockIdx, == );
  }

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_GetAddressOffset
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function calculates the offset of the Block
///                     in the FEE memory given as parameter
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions: 
///
/// \input unBlockNumber : flash block index either valid or not in range
///
/// - Expectations:
///
/// \output unAddressOffset : the offset computed for the FeeBlock
///
//-----------------------------------------------------------------------------
void Mt_Fee_GetAddressOffset(void)
{
  //Step 1: Set pre-conditions
  Fee_GetAddressOffset_RetVal = 0u;

  //Step 1: Set pre-conditions
  Fee_LookUpIndex_RetVal = 0u;

  struct { uint16  unBlockNumber;  uint16  unAddressOffset; } asTestCaseData[]
    = {  {                     2u,                    0x1C,  },      // 0x1C = ( (offset Block1 = 6u + 2u) + (offsetBlock2 = 20) ) = 28
         {          FeeBlockCount,                   0x92C,  },      // add all blocks size + offsets   //this will fail every time DEM changes its size
      };

  for (uint32 ulIdx = 0; ulIdx < _countof(asTestCaseData); ulIdx++)
  {
    //Step 2) Assign Input values
    Fee_GetAddressOffset_Param1 = asTestCaseData[ulIdx].unBlockNumber;

    //Step 3) Call FUT
    Fee_GetAddressOffset_RetVal = Fee_GetAddressOffset(Fee_GetAddressOffset_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Fee_GetAddressOffset_RetVal, asTestCaseData[ulIdx].unAddressOffset, == );
  }
}

//-----------------------------------------------------------------------------
//  Fee.c
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check  the initialization  of the Flash Driver
///                     Initialization, the Flash Driver Partitioning and Setting of the
///                     FlexRam function as EEPROM emulated
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions: 
///
/// \input EEESize:  E-Flash size before/ after partitioning
///
/// - Expectations:
///
/// \output Fee_State_Out       : flash state after flash partitioning
/// \output MEMIF_Out           : memory interface state after flash partitioning
/// \output FLASH_Init_Cnt      : call of initialization of flash partitioning from low level driver
/// \output FLASH_Partition_Cnt : call of flash partitioning from low level driver
/// \output FLASH_FlexRam_Cnt   : call of flex RAM partitioning from low level driver
///
//-----------------------------------------------------------------------------
void Mt_Fee_Init(void)
{

  struct { uint16  EEESize;  tieFeeState Fee_State_Out; MemIf_StatusType  MEMIF_Out;  uint8 FLASH_Init_Cnt;  uint8 FLASH_Partition_Cnt;  uint8 FLASH_FlexRam_Cnt; } asTestCaseData[]
    = {  {              0u,             FEE_STATE_IDLE,                  MEMIF_IDLE,                    2u,                        1u,                        1u  },
         { FEATURE_FLS_FLEX_RAM_SIZE,   FEE_STATE_IDLE,                  MEMIF_IDLE,                    1u,                        0u,                        1u  }, };

  for (uint32 ulIdx = 0; ulIdx < _countof(asTestCaseData); ulIdx++)
  {
    //Step 1: Set pre-conditions
    FLASH_DRV_Init_HitCount               = 0u;
    FLASH_DRV_DEFlashPartition_HitCount   = 0u;
    FLASH_DRV_SetFlexRamFunction_HitCount = 0u;
    Fee_State     = FEE_STATE_NOT_INIT;
    Fee_t_Status  = MEMIF_UNINIT;

    //Step 2) Assign Input values
    flashSSDConfig.EEESize = asTestCaseData[ulIdx].EEESize;

    //Step 3) Call FUT
    Fee_Init();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Fee_State,                                   asTestCaseData[ulIdx].Fee_State_Out, == );
    AL_UNITTEST_CHECK(Fee_t_Status,                                    asTestCaseData[ulIdx].MEMIF_Out, == );
    AL_UNITTEST_CHECK(FLASH_DRV_Init_HitCount,                    asTestCaseData[ulIdx].FLASH_Init_Cnt, == );
    AL_UNITTEST_CHECK(FLASH_DRV_DEFlashPartition_HitCount,   asTestCaseData[ulIdx].FLASH_Partition_Cnt, == );
    AL_UNITTEST_CHECK(FLASH_DRV_SetFlexRamFunction_HitCount,   asTestCaseData[ulIdx].FLASH_FlexRam_Cnt, == );
    AL_UNITTEST_CHECK(flashSSDConfig.CallBack,                                           NULL_CALLBACK, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_Read_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function rejects the read request in case
///                     the FlexRam is not available for emulated EEPROM operation
///                     (FTFC->FCNFG register has EERDY flag = 0 )
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input Fee_State       = FEE_STATE_IDLE
/// \input Fee_Read_Param1 = FeeBlockDemDataId
/// \input Fee_Read_RetVal = E_OK
///
/// - Expectations:
///
/// \output Fee_State       = FEE_STATE_IDLE
/// \output Fee_Read_RetVal = E_NOT_OK
///
//-----------------------------------------------------------------------------
void Mt_Fee_Read_TestCase1(void)
{
  //Step 1: Set pre-conditions
  FTFC->FCNFG     = 0u;

  //Step 2) Assign Input values
  Fee_State       = FEE_STATE_IDLE;
  Fee_Read_Param1 = FeeBlockDemDataId;
  Fee_Read_RetVal = E_OK;

  //Step 3) Call FUT
  Fee_Read_RetVal = Fee_Read(Fee_Read_Param1, Fee_Read_Param2, &Fee_Read_Param3, Fee_Read_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Fee_State,       FEE_STATE_IDLE, == );
  AL_UNITTEST_CHECK(Fee_Read_RetVal,       E_NOT_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_Read_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function accepts the read request in case
///                     the FlexNVM block is partitioned for emulated EEPROM.
///                     (FTFC->FCNFG register has EERDY flag = 1 ) and sets
///                     the state of FEE to READ operation
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input Fee_State       = FEE_STATE_IDLE
/// \input Fee_Read_Param1 = FeeBlockDemDataId
/// \input Fee_Read_RetVal = E_NOT_OK
/// \input Fee_EEERead_Param1 = flashSSDConfig
///
/// - Expectations:
///
/// \output Fee_State       = FEE_STATE_READ
/// \output Fee_JobResult   = MEMIF_JOB_OK
/// \output Fee_Read_RetVal = E_OK
///
//-----------------------------------------------------------------------------
void Mt_Fee_Read_TestCase2(void)
{
  //Step 1: Set pre-conditions
  FTFC->FCNFG     = FTFC_FCNFG_EEERDY_MASK;
  uint32 Mt_EERAMAddress;
  flashSSDConfig.EERAMBase = (uint32)&Mt_EERAMAddress;

  //Step 2) Assign Input values
  Fee_State          = FEE_STATE_IDLE;
  Fee_Read_Param1    = FeeBlockDemDataId;
  Fee_Read_RetVal    = E_NOT_OK;
  Fee_EEERead_Param1 = flashSSDConfig;

  //Step 3) Call FUT
  Fee_Read_RetVal = Fee_Read(Fee_Read_Param1, Fee_Read_Param2, &Fee_Read_Param3, Fee_Read_Param4);

  //Step 4) Check expected output values
   AL_UNITTEST_CHECK(Fee_State,       FEE_STATE_READ, == );
   AL_UNITTEST_CHECK(Fee_JobResult,     MEMIF_JOB_OK, == );
   AL_UNITTEST_CHECK(Fee_Read_RetVal,           E_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_Read_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function rejects the Read operation because
///                     the Fee is already in Read status, so read operation is still
///                     in progress
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input Fee_State       = FEE_STATE_READ
/// \input Fee_Read_Param1 = FeeBlockDemDataId
/// \input Fee_Read_RetVal = E_OK
///
/// - Expectations:
///
/// \output Fee_State       = FEE_STATE_READ
/// \output Fee_Read_RetVal = E_NOT_OK
///
//-----------------------------------------------------------------------------
void Mt_Fee_Read_TestCase3(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Fee_State          = FEE_STATE_READ;
  Fee_Read_Param1    = FeeBlockDemDataId;
  Fee_Read_RetVal    = E_OK;

  //Step 3) Call FUT
  Fee_Read_RetVal = Fee_Read(Fee_Read_Param1, Fee_Read_Param2, &Fee_Read_Param3, Fee_Read_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Fee_State,       FEE_STATE_READ, == );
  AL_UNITTEST_CHECK(Fee_Read_RetVal,       E_NOT_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_Read
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function processes the read operation
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Fee_Read(void)
{
  Mt_Fee_Read_TestCase1();
  Mt_Fee_Read_TestCase2();
  Mt_Fee_Read_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_Write_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function rejects the write request in case
///                     the FlexRam is not available for emulated EEPROM operation
///                     (FTFC->FCNFG register has EERDY flag = 0 )
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input Fee_State        = FEE_STATE_IDLE
/// \input Fee_Write_Param1 = FeeBlockDemDataId
/// \input Fee_Write_RetVal = E_OK
///
/// - Expectations:
///
/// \output Fee_State        = FEE_STATE_IDLE
/// \output Fee_Write_RetVal = E_NOT_OK
///
//-----------------------------------------------------------------------------
void Mt_Fee_Write_TestCase1(void)
{
  //Step 1: Set pre-conditions
  FTFC->FCNFG = 0u;

  //Step 2) Assign Input values
  Fee_State        = FEE_STATE_IDLE;
  Fee_Write_Param1 = FeeBlockDemDataId;
  Fee_Write_RetVal = E_OK;

  //Step 3) Call FUT
  Fee_Write_RetVal = Fee_Write(Fee_Write_Param1, &Fee_Write_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Fee_State,  FEE_STATE_IDLE, == );
  AL_UNITTEST_CHECK(Fee_Write_RetVal, E_NOT_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_Write_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function accepts the write request in case
///                     the FlexNVM block is partitioned for emulated EEPROM.
///                     (FTFC->FCNFG register has EERDY flag = 1 ) , but does not
///                     process the write request due to protection violation errors
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input Fee_State           = FEE_STATE_IDLE
/// \input Fee_Write_Param1    = FeeBlockDemDataId
/// \input Fee_Write_RetVal    = E_OK
/// \input Fee_EEEWrite_Param1 = flashSSDConfig
/// \input FTFC->FSTAT         = 0x10
///
/// - Expectations:
///
/// \output Fee_State         = FEE_STATE_IDLE
/// \output Fee_JobResult     = MEMIF_JOB_FAILED
/// \output Fee_Write_RetVal  = E_NOT_OK
///
//-----------------------------------------------------------------------------
void Mt_Fee_Write_TestCase2(void)
{
  //Step 1: Set pre-conditions
  FTFC->FCNFG = FTFC_FCNFG_EEERDY_MASK;
  uint32 Mt_EERAMAddress;
  flashSSDConfig.EERAMBase = (uint32)&Mt_EERAMAddress;

  //Step 2) Assign Input values
  Fee_State           = FEE_STATE_IDLE;
  Fee_Write_Param1    = FeeBlockDemDataId;
  Fee_Write_RetVal    = E_OK;
  Fee_EEEWrite_Param1 = flashSSDConfig;
  FTFC->FSTAT         = 0x10;             // FPVIOL set

  //Step 3) Call FUT
  Fee_Write_RetVal = Fee_Write(Fee_Write_Param1, &Fee_Write_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Fee_State,            FEE_STATE_IDLE, == );
  AL_UNITTEST_CHECK(Fee_JobResult,      MEMIF_JOB_FAILED, == );
  AL_UNITTEST_CHECK(Fee_Write_RetVal,           E_NOT_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_Write_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function accepts the write request in case
///                     the FlexNVM block is partitioned for emulated EEPROM.
///                     (FTFC->FCNFG register has EERDY flag = 1 ) , and processed
///                     the write operation if no protection violation was detected
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input Fee_State           = FEE_STATE_IDLE
/// \input Fee_Write_Param1    = FeeBlockDemDataId
/// \input Fee_Write_RetVal    = E_OK
/// \input Fee_EEEWrite_Param1 = flashSSDConfig
///
/// - Expectations:
///
/// \output Fee_State         = FEE_STATE_WRITE
/// \output Fee_JobResult     = MEMIF_JOB_OK
/// \output Fee_Write_RetVal  = E_OK
///
//-----------------------------------------------------------------------------
void Mt_Fee_Write_TestCase3(void)
{
  //Step 1: Set pre-conditions
  FTFC->FCNFG = FTFC_FCNFG_EEERDY_MASK;     // EEE enabled for EEPROM emulation
  FTFC->FSTAT = 0x00;                       // no protection violation
  uint32 Mt_EERAMAddress;
  flashSSDConfig.EERAMBase = (uint32)&Mt_EERAMAddress;

  //Step 2) Assign Input values
  Fee_State         = FEE_STATE_IDLE;
  Fee_Write_Param1  = FeeBlockMultiBlockRequestId;
  FeeBlockTable[FeeBlockMultiBlockRequestId].unBlockSize = 0;     // reset size to 0 to skip "while ((size > 0U) && (retValue == E_OK)) " in Fee_EEEWrite (avoiding infinite loop)
  Fee_Write_RetVal    = E_NOT_OK;
  Fee_EEEWrite_Param1 = flashSSDConfig;

  //Step 3) Call FUT
  Fee_Write_RetVal = Fee_Write(Fee_Write_Param1, &Fee_Write_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Fee_State,              FEE_STATE_WRITE, == );
  AL_UNITTEST_CHECK(Fee_JobResult,             MEMIF_JOB_OK, == );
  AL_UNITTEST_CHECK(Fee_Write_RetVal,                  E_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_Write_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function rejects the write operation because
///                     the Fee is already in write status, so write operation is still
///                     in progress
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input Fee_State          = FEE_STATE_READ (invalid state)
/// \input Fee_Write_Param1   = FeeBlockDemDataId
/// \input Fee_Write_RetVal   = E_OK
///
/// - Expectations:
///
/// \output Fee_State         = FEE_STATE_READ
/// \output Fee_Write_RetVal  = E_NOT_OK
///
//-----------------------------------------------------------------------------
void Mt_Fee_Write_TestCase4(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Fee_State         = FEE_STATE_READ;
  Fee_Write_Param1  = FeeBlockDemDataId;
  Fee_Write_RetVal  = E_OK;

  //Step 3) Call FUT
  Fee_Write_RetVal = Fee_Write(Fee_Write_Param1, &Fee_Write_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Fee_State,        FEE_STATE_READ, == );
  AL_UNITTEST_CHECK(Fee_Write_RetVal,       E_NOT_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_Write
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function processes the read operation
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Fee_Write(void)
{
  Mt_Fee_Write_TestCase1();
  Mt_Fee_Write_TestCase2();
  Mt_Fee_Write_TestCase3();
  Mt_Fee_Write_TestCase4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_EEEWrite_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function rejects the write request in case
///                     the FeeBlock characteristics (size, address)are not in the
///                     accepted range of EEPROM emulation
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input FTFC->FCNFG = FTFx_FCNFG_EEERDY_MASK
/// \input Fee_EEEWrite_Param2 = FeeBlockTable[FeeBlockStatisticsId].unBlockSize
/// \input Fee_EEEWrite_RetVal = E_OK
///
/// - Expectations:
///
/// \output Fee_EEEWrite_RetVal = E_NOT_OK
///
//-----------------------------------------------------------------------------
void Mt_Fee_EEEWrite_TestCase1(void)
{
  //Step 1: Set pre-conditions
  FTFC->FCNFG = FTFx_FCNFG_EEERDY_MASK;
  //Step 2) Assign Input values
  Fee_EEEWrite_Param2 = FeeBlockTable[FeeBlockStatisticsId].unBlockSize;
  Fee_EEEWrite_RetVal = E_OK;


  //Step 3) Call FUT
  Fee_EEEWrite_RetVal = Fee_EEEWrite(&Fee_EEEWrite_Param1, Fee_EEEWrite_Param2, Fee_EEEWrite_Param3, Fee_EEEWrite_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Fee_EEEWrite_RetVal, E_NOT_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_EEEWrite_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function accepts the write request in case
///                     the FeeBlock characteristics (size, address) is in the
///                     accepted range of EEPROM emulation and the allignment is of 1byte
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input FTFC->FCNFG = FTFx_FCNFG_EEERDY_MASK
/// \input FeeBlockTable[FeeBlockStatisticsId].unBlockSize = 1u
/// \input Fee_EEEWrite_Param1.EERAMBase = (uint32)&Mt_Address[0]
/// \input Fee_EEEWrite_Param1.EEESize   = 20u
/// \input Fee_EEEWrite_Param2           =  (uint32)&Mt_Address[1]
/// \input Fee_EEEWrite_Param3 = FeeBlockTable[FeeBlockStatisticsId].unBlockSize
/// \input Fee_EEEWrite_RetVal = E_OK
/// \input Fee_EEEWrite_Param4 = &Mt_Data[0]
///
/// - Expectations:
///
/// \output Fee_EEEWrite_RetVal = E_OK
///
//-----------------------------------------------------------------------------
void Mt_Fee_EEEWrite_TestCase2(void)
{
  //Step 1: Set pre-conditions
  uint32 Mt_Address[] = { 0, 0, 0, 0, 0 };
  FTFC->FCNFG = FTFx_FCNFG_EEERDY_MASK;
  FeeBlockTable[FeeBlockStatisticsId].unBlockSize = 1u;   //simulate a block with 1byte size
  uint32 Mt_Data[] = { 0x55u, 0xFFu, 0, 0x55u, 0xFFu };

  //Step 2) Assign Input values
  Fee_EEEWrite_Param1.EERAMBase = (uint32)&Mt_Address[0];
  Fee_EEEWrite_Param1.EEESize   = 20u;
  Fee_EEEWrite_Param2 =  (uint32)&Mt_Address[1];     //address > pSSDConfig->EERAMBase
  Fee_EEEWrite_Param3 = FeeBlockTable[FeeBlockStatisticsId].unBlockSize;
  Fee_EEEWrite_RetVal = E_OK;
  Fee_EEEWrite_Param4 = &Mt_Data[0];

  //Step 3) Call FUT
  Fee_EEEWrite_RetVal = Fee_EEEWrite(&Fee_EEEWrite_Param1, Fee_EEEWrite_Param2, Fee_EEEWrite_Param3, Fee_EEEWrite_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Fee_EEEWrite_RetVal, E_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_EEEWrite_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function accepts the write request in case
///                     the FeeBlock characteristics (size, address) is in the
///                     accepted range of EEPROM emulation and the allignment is of 2bytes
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input FTFC->FCNFG = FTFx_FCNFG_EEERDY_MASK
/// \input FeeBlockTable[FeeBlockStatisticsId].unBlockSize = 2u
/// \input Fee_EEEWrite_Param1.EERAMBase = (uint32)&Mt_Address[0]
/// \input Fee_EEEWrite_Param1.EEESize   = 20u
/// \input Fee_EEEWrite_Param2           =  (uint32)&Mt_Address[1]
/// \input Fee_EEEWrite_Param3 = FeeBlockTable[FeeBlockStatisticsId].unBlockSize
/// \input Fee_EEEWrite_RetVal = E_OK
///
/// - Expectations:
///
/// \output Fee_EEEWrite_RetVal = E_OK
///
//-----------------------------------------------------------------------------
void Mt_Fee_EEEWrite_TestCase3(void)
{
  //Step 1: Set pre-conditions
  uint32 Mt_Address[] = { 0, 0, 0, 0, 0 };
  FTFC->FCNFG = FTFx_FCNFG_EEERDY_MASK;
  FeeBlockTable[FeeBlockStatisticsId].unBlockSize = 2u;   //simulate a block with 2byte size

  //Step 2) Assign Input values
  Fee_EEEWrite_Param1.EERAMBase = (uint32)&Mt_Address[0];
  Fee_EEEWrite_Param1.EEESize   = 20;
  Fee_EEEWrite_Param2           = (uint32)&Mt_Address[1];     //address > pSSDConfig->EERAMBase
  Fee_EEEWrite_Param3           = FeeBlockTable[FeeBlockStatisticsId].unBlockSize;
  Fee_EEEWrite_RetVal           = E_OK;

  //Step 3) Call FUT
  Fee_EEEWrite_RetVal = Fee_EEEWrite(&Fee_EEEWrite_Param1, Fee_EEEWrite_Param2, Fee_EEEWrite_Param3, Fee_EEEWrite_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Fee_EEEWrite_RetVal, E_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_EEEWrite_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function rejects the write operation in case
///                     the FlexRAM is not for EEPROM use -> FlexRAM = 0 bytes 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input FTFC->FCNFG         = 0u
/// \input Fee_EEEWrite_RetVal = E_OK
///
/// - Expectations:
///
/// \output Fee_EEEWrite_RetVal  = E_NOT_OK
///
//-----------------------------------------------------------------------------
void Mt_Fee_EEEWrite_TestCase4(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  FTFC->FCNFG = 0u;     //EEE not configured for EEprom emulation
  Fee_EEEWrite_RetVal = E_OK;

  //Step 3) Call FUT
  Fee_EEEWrite_RetVal = Fee_EEEWrite(&Fee_EEEWrite_Param1, Fee_EEEWrite_Param2, Fee_EEEWrite_Param3, Fee_EEEWrite_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Fee_EEEWrite_RetVal,       E_NOT_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_EEEWrite
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function processes the write request in FlexNVM partition
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Fee_EEEWrite(void)
{
  Mt_Fee_EEEWrite_TestCase1();
  Mt_Fee_EEEWrite_TestCase2();
  Mt_Fee_EEEWrite_TestCase3();
  Mt_Fee_EEEWrite_TestCase4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_EEERead_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function rejects the read request in case
///                     the FeeBlock characteristics (size, address)are not in the
///                     accepted range of EEPROM emulation
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input FTFC->FCNFG = FTFx_FCNFG_EEERDY_MASK
/// \input Fee_EEERead_Param2 = FeeBlockTable[FeeBlockStatisticsId].unBlockSize
/// \input Fee_EEERead_RetVal = E_OK
///
/// - Expectations:
///
/// \output Fee_EEERead_RetVal = E_NOT_OK
///
//-----------------------------------------------------------------------------
void Mt_Fee_EEERead_TestCase1(void)
{
  //Step 1: Set pre-conditions
  FTFC->FCNFG = FTFx_FCNFG_EEERDY_MASK;
  //Step 2) Assign Input values
  Fee_EEERead_Param2 = FeeBlockTable[FeeBlockStatisticsId].unBlockSize;
  Fee_EEERead_RetVal = E_OK;

  //Step 3) Call FUT
  Fee_EEERead_RetVal = Fee_EEERead(&Fee_EEERead_Param1, Fee_EEERead_Param2, Fee_EEERead_Param3, Fee_EEERead_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Fee_EEERead_RetVal, E_NOT_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_EEERead_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function rejects the write request in case
///                     the FeeBlock characteristics (size, address)aren not in the
///                     accepted range of EEPROM emulation
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input FTFC->FCNFG = FTFx_FCNFG_EEERDY_MASK
/// \input FeeBlockTable[FeeBlockStatisticsId].unBlockSize = 1u
/// \input flashSSDConfig.EERAMBase     = Fee_EEERead_Param1.EERAMBase
/// \input Fee_EEERead_Param1.EERAMBase = (uint32)&Mt_Address[2]
/// \input Fee_EEERead_Param1.EEESize   = 20
/// \input Fee_EEERead_Param2 = 2u
/// \input Fee_EEERead_Param3 = FeeBlockTable[FeeBlockStatisticsId].unBlockSize
/// \input Fee_EEERead_Param4 = &Mt_Address[0]
/// \input Fee_EEERead_RetVal = E_OK
///
/// - Expectations:
///
/// \output Fee_EEERead_RetVal = E_OK
///
//-----------------------------------------------------------------------------
void Mt_Fee_EEERead_TestCase2(void)
{
  //Step 1: Set pre-conditions
  uint32 Mt_Address[] = { 0, 0, 0, 0, 0 };
  FTFC->FCNFG = FTFx_FCNFG_EEERDY_MASK;
  FeeBlockTable[FeeBlockStatisticsId].unBlockSize = 1u;   //simulate a block with 2byte size

  //Step 2) Assign Input values
  Fee_EEERead_Param1.EERAMBase = (uint32)&Mt_Address[2];
  flashSSDConfig.EERAMBase     = Fee_EEERead_Param1.EERAMBase;
  Fee_EEERead_Param1.EEESize = 20;
  Fee_EEERead_Param2 = 2u;     //address > pSSDConfig->EERAMBase
  Fee_EEERead_Param3 = FeeBlockTable[FeeBlockStatisticsId].unBlockSize;
  Fee_EEERead_RetVal = E_OK;
  Fee_EEERead_Param4 = &Mt_Address[0];

  //Step 3) Call FUT
  Fee_EEERead_RetVal = Fee_EEERead(&Fee_EEERead_Param1, Fee_EEERead_Param2, Fee_EEERead_Param3, Fee_EEERead_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Fee_EEERead_RetVal, E_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_EEERead_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function rejects the read operation in case
///                     the FlexRAM is not for EEPROM use -> FlexRAM = 0 bytes 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input FTFC->FCNFG         = 0u
/// \input Fee_EEERead_RetVal = E_OK
///
/// - Expectations:
///
/// \output Fee_EEERead_RetVal  = E_NOT_OK
///
//-----------------------------------------------------------------------------
void Mt_Fee_EEERead_TestCase3(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  FTFC->FCNFG = 0u;     //EEE not configured for EEprom emulation
  Fee_EEERead_RetVal = E_OK;

  //Step 3) Call FUT
  Fee_EEERead_RetVal = Fee_EEERead(&Fee_EEERead_Param1, Fee_EEERead_Param2, Fee_EEERead_Param3, Fee_EEERead_Param4);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Fee_EEERead_RetVal,       E_NOT_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_EEERead
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function processes the read request from FlexNVM partition
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Fee_EEERead(void)
{
  Mt_Fee_EEERead_TestCase1();
  Mt_Fee_EEERead_TestCase2();
  Mt_Fee_EEERead_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_WaitEEWriteToFinish
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function copies data and
///                     writes in FlexRAM until operation has finished
///                     and no protection violation error detected
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions: 
///
/// \input ucStepAddressIncrement : Block address allignment (32bytes or less)
/// \input FSTAT_RegIn            : FSTAT register status regarding protection of memory location
///
/// - Expectations:
///
/// \output WriteOpStatus_Out: Write Operation Status set based on allignment and FSTAT register
///
//-----------------------------------------------------------------------------
void Mt_Fee_WaitEEWriteToFinish(void)
{
  struct { uint8 ucStepAddressIncrement;   uint32 FSTAT_RegIn; Std_ReturnType WriteOpStatus_Out; } asTestCaseData[]
    = {  {                       0x04u,                   0x0u,                  E_OK },
         {                       0x01u,                   0x0u,                  E_OK },
         {                       0x02u,                   0x0u,                  E_OK },
         {                          0u,  FTFC_FSTAT_FPVIOL_MASK ,            E_NOT_OK }, };

  for (uint32 ulIdx = 0u; ulIdx < _countof(asTestCaseData); ulIdx++)
  {
    //Step 1: Set pre-conditions
    //Step 2) Assign Input values
    uint32 Mt_ulBlockAddress;
    Fee_WaitEEWriteToFinish_Param2 = &Mt_ulBlockAddress;
    Fee_WaitEEWriteToFinish_Param4 = asTestCaseData[ulIdx].ucStepAddressIncrement;
    FTFC->FSTAT                    = asTestCaseData[ulIdx].FSTAT_RegIn;

    //Step 3) Call FUT
    Fee_WaitEEWriteToFinish_RetVal = Fee_WaitEEWriteToFinish(&Fee_WaitEEWriteToFinish_Param1, Fee_WaitEEWriteToFinish_Param2, &Fee_WaitEEWriteToFinish_Param3, Fee_WaitEEWriteToFinish_Param4);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Fee_WaitEEWriteToFinish_RetVal, asTestCaseData[ulIdx].WriteOpStatus_Out, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_GetStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the memory interface status is updated based on the
///                     current FEE status operation
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions: 
///
/// \input unFlashStatus_In : Flash operation status flag (EEE operation not completed )
/// \input unFlashConfig_In : Flash configuratioin status flag (EEE set for EEPROM emulation )
/// \input FeeState_In      : actual flash  state
///
/// - Expectations:
///
/// \output MemIfStatus_Out: Memory interface status is updated accordingly
///
//-----------------------------------------------------------------------------
void Mt_Fee_GetStatus(void)
{
  //Step 1: Set pre-conditions
  Fee_GetStatus_RetVal = E_NOT_OK;

  struct { uint8 unFlashStatus_In;     uint8 unFlashConfig_In;  tieFeeState FeeState_In;  MemIf_StatusType  MemIfStatus_Out; } asTestCaseData[]
    = {  {                      0u,                        0u,            FEE_STATE_IDLE,                MEMIF_BUSY_INTERNAL },
         {    FTFC_FSTAT_CCIF_MASK,     FTFC_FCNFG_EEERDY_MASK,           FEE_STATE_IDLE,                        MEMIF_IDLE  },
         {    FTFC_FSTAT_CCIF_MASK,     FTFC_FCNFG_EEERDY_MASK,           FEE_STATE_READ,                        MEMIF_BUSY  }, };

  for (uint32 ulIdx = 0; ulIdx < _countof(asTestCaseData); ulIdx++)
  {
    //Step 2) Assign Input values
    FTFC->FSTAT = asTestCaseData[ulIdx].unFlashStatus_In;
    FTFC->FCNFG = asTestCaseData[ulIdx].unFlashConfig_In;
    Fee_State   = asTestCaseData[ulIdx].FeeState_In;

    //Step 3) Call FUT
    Fee_GetStatus_RetVal = Fee_GetStatus();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Fee_GetStatus_RetVal,    asTestCaseData[ulIdx].MemIfStatus_Out, == );
  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_SetMode
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Setter for Fee Mode
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input Fee_SetMode_Param1 = MEMIF_MODE_SLOW
///
/// - Expectations:
///
/// \output NA (coverage only)
///
//-----------------------------------------------------------------------------
void Mt_Fee_SetMode(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Fee_SetMode_Param1 = MEMIF_MODE_SLOW;
  //Step 3) Call FUT
  Fee_SetMode(Fee_SetMode_Param1);
  //Step 4) Check expected output values
  //coverage only, nothing to be checked 
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_GetJobResult
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Return the requested Fee Job
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input Fee_JobResult           = MEMIF_JOB_PENDING
/// \input Fee_GetJobResult_RetVal = MEMIF_BLOCK_INVALID
///
/// - Expectations:
///
/// \output Fee_GetJobResult_RetVal = MEMIF_JOB_PENDING
///
//-----------------------------------------------------------------------------
void Mt_Fee_GetJobResult(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Fee_JobResult           = MEMIF_JOB_PENDING;
  Fee_GetJobResult_RetVal = MEMIF_BLOCK_INVALID;
  //Step 3) Call FUT
  Fee_GetJobResult_RetVal = Fee_GetJobResult();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Fee_GetJobResult_RetVal, MEMIF_JOB_PENDING, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_InvalidateBlock
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Function invalidates the block (not use- code design)
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input  Fee_InvalidateBlock_Param1 = FeeBlockDemDataId
///
/// - Expectations:
///
/// \output NA (coverage only)
///
//-----------------------------------------------------------------------------
void Mt_Fee_InvalidateBlock(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Fee_InvalidateBlock_Param1 = FeeBlockDemDataId;
  //Step 3) Call FUT
  Fee_InvalidateBlock_RetVal = Fee_InvalidateBlock(Fee_InvalidateBlock_Param1);
  //Step 4) Check expected output values
  //coverage only, nothing to be checked 
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_EraseImmediateBlock
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Function erases the block (not used - code design)
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input  Fee_InvalidateBlock_Param1 = FeeBlockDemDataId
///
/// - Expectations:
///
/// \output NA (coverage only)
///
//-----------------------------------------------------------------------------
void Mt_Fee_EraseImmediateBlock(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Fee_EraseImmediateBlock_Param1 = FeeBlockDemDataId;
  //Step 3) Call FUT
  Fee_EraseImmediateBlock_RetVal = Fee_EraseImmediateBlock(Fee_EraseImmediateBlock_Param1);
  //Step 4) Check expected output values
  //coverage only, nothing to be checked 
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_MainFunction
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the Main Function executes the FeeState Machine
///                     when no operation is in progress (they are completed)
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input  Fee_State   = FEE_STATE_WRITE
/// \input  FTFC->FSTAT = FTFC_FSTAT_CCIF_MASK
/// \input  FTFC->FCNFG = FTFC_FCNFG_EEERDY_MASK
///
/// - Expectations:
///
/// \output Fee_State       = FEE_STATE_IDLE
/// \output Fee_JobResult   = MEMIF_JOB_OK
///
//-----------------------------------------------------------------------------
void Mt_Fee_MainFunction(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  FTFC->FSTAT = FTFC_FSTAT_CCIF_MASK;     // command of emulated EEPROM has completed
  FTFC->FCNFG = FTFC_FCNFG_EEERDY_MASK;
  Fee_State   = FEE_STATE_WRITE;

  //Step 3) Call FUT
  Fee_MainFunction();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Fee_State,      FEE_STATE_IDLE, == );
  AL_UNITTEST_CHECK(Fee_JobResult,    MEMIF_JOB_OK, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Fee_GetOpStatus
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function returns the status of the internal
///                     FEE operation (check internal completion of a job)
///
///    - Test Design Technique: DT (Decision Table)
///
/// - Preconditions: 
/// - Fee Job not completed/ completed
/// \input unFlashStatus_In : flash status register input 
/// \input unFlashConfig_In : flash configuration register input 
///
/// - Expectations:
///
/// \output boState_Out : Fee Operation status 
///
//-----------------------------------------------------------------------------
void Mt_Fee_GetOpStatus(void)
{
  //Step 1: Set pre-conditions
  Fee_GetOpStatus_RetVal = E_NOT_OK;

  struct { uint8 unFlashStatus_In;  uint8 unFlashConfig_In; Std_ReturnType boState_Out; } asTestCaseData[]
    = {  {                      0u,                     0u,                    E_NOT_OK },
         {    FTFC_FSTAT_CCIF_MASK,  FTFC_FCNFG_EEERDY_MASK,                       E_OK }, };

  for (uint32 ulIdx = 0; ulIdx < _countof(asTestCaseData); ulIdx++)
  {
    //Step 2) Assign Input values
    FTFC->FSTAT = asTestCaseData[ulIdx].unFlashStatus_In;
    FTFC->FCNFG = asTestCaseData[ulIdx].unFlashConfig_In;

    //Step 3) Call FUT
    Fee_GetOpStatus_RetVal = Fee_GetOpStatus();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Fee_GetOpStatus_RetVal,    asTestCaseData[ulIdx].boState_Out, == );
  }
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
  //ctaaFee.c
  ALUnitTest_AddFunction("Mt_riFee_Init",                    Mt_riFee_Init);
  ALUnitTest_AddFunction("Mt_rpFee_Cycle0",                  Mt_rpFee_Cycle0);
  
  //Fee_InternalFct.c
  ALUnitTest_AddFunction("Mt_FeeStateMachine",               Mt_FeeStateMachine);
  ALUnitTest_AddFunction("Mt_Fee_LookUpIndex",               Mt_Fee_LookUpIndex);
  ALUnitTest_AddFunction("Mt_Fee_GetAddressOffset",          Mt_Fee_GetAddressOffset);
  
  //Fee.c
  ALUnitTest_AddFunction("Mt_Fee_Init",                      Mt_Fee_Init);
  ALUnitTest_AddFunction("Mt_Fee_Read",                      Mt_Fee_Read);
  ALUnitTest_AddFunction("Mt_Fee_EEERead",                   Mt_Fee_EEERead);
  ALUnitTest_AddFunction("Mt_Fee_Write",                     Mt_Fee_Write);
  ALUnitTest_AddFunction("Mt_Fee_EEEWrite",                  Mt_Fee_EEEWrite);
  ALUnitTest_AddFunction("Mt_Fee_WaitEEWriteToFinish",       Mt_Fee_WaitEEWriteToFinish);
  ALUnitTest_AddFunction("Mt_Fee_GetStatus",                 Mt_Fee_GetStatus);
  ALUnitTest_AddFunction("Mt_Fee_SetMode",                   Mt_Fee_SetMode);
  ALUnitTest_AddFunction("Mt_Fee_GetJobResult",              Mt_Fee_GetJobResult);
  ALUnitTest_AddFunction("Mt_Fee_InvalidateBlock",           Mt_Fee_InvalidateBlock);
  ALUnitTest_AddFunction("Mt_Fee_EraseImmediateBlock",       Mt_Fee_EraseImmediateBlock);
  ALUnitTest_AddFunction("Mt_Fee_MainFunction",              Mt_Fee_MainFunction);
  ALUnitTest_AddFunction("Mt_Fee_GetOpStatus",               Mt_Fee_GetOpStatus);
}