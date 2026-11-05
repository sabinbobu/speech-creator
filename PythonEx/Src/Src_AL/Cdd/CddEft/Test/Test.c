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
/// \file   Test.c
///
/// \brief  Unit Test Cases for  CddEft
///
/// \author Pop Anca Alexandra (M01470A)
///         mailTo:ancaalexandra.pop[at]marelli.com
//-----------------------------------------------------------------------------

//==============================================================================
//  Files covered by this module unit test:
//            - CddEft.c
//            - CddEft_Adapter.c
//==============================================================================

//=============================================================================
// Includes
//=============================================================================
#include <ALUnitTest_UserInterface.h>

// Stub headers
#include "Test_Stubs.h"

// Headers of the unit test Module
#include "Test.h"

//-----------------------------------------------------------------------------
//  Module Test Cases
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddEft_DataValid_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function get EFT data and returned the CRC 
///                        status valid if  local data structure is matching 
///                        with the EFT data
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Mt_InitEft() -EFT structure filled with data
/// \input  CddEft_CrcValid = FALSE
/// \input  CddEft_boCrcCalculated = FALSE
/// \input  Crc_CalculateCRC32_4C11DB7_RetVal = 0xBB1AABFEu
///
/// - Expectations:
///
/// \output    CddEft_DataValid_RetVal =  TRUE
///
//-----------------------------------------------------------------------------
void Mt_CddEft_DataValid_TestCase1(void)
{
    //Step 1) Set pre-conditions
    Mt_InitEft();

    //Step 2) Assign Input values
    CddEft_CrcValid = FALSE;
    CddEft_boCrcCalculated = FALSE;
    Crc_CalculateCRC32_4C11DB7_RetVal = 0xBB1AABFEu;
    
    //Step 3) Call FUT
    CddEft_DataValid_RetVal = CddEft_DataValid();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CddEft_DataValid_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddEft_DataValid_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test that in case the validity of EFT data was not checked, the function 
///                        get EFT data and returned the CRC status invalid if local
///                        data structure is not matching with the EFT data
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input     CddEft_CrcValid = FALSE
/// \input     CddEft_boCrcCalculated = FALSE
/// \input     EftData.Eft_Crc.Crc32.ulCrc = 0u
/// \input     Crc_CalculateCRC32_4C11DB7 = 0xBB1AABFFu
///
/// - Expectations:
///
/// \output    CddEft_DataValid_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddEft_DataValid_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CddEft_CrcValid = FALSE;
    CddEft_boCrcCalculated = FALSE;
    EftData.Eft_Crc.Crc32.ulCrc = 0u;
    Crc_CalculateCRC32_4C11DB7_RetVal = 0xBB1AABFFu;

    //Step 3) Call FUT
    CddEft_DataValid_RetVal = CddEft_DataValid();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CddEft_DataValid_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddEft_DataValid_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function doesn't calculate EFT because it was previously calculated and
///                        returned the CRC invalid status
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input     CddEft_CrcValid = FALSE
/// \input     CddEft_boCrcCalculated = TRUE
///
/// - Expectations:
///
/// \output    CddEft_DataValid_RetVal = FALSE
///
//-----------------------------------------------------------------------------
void Mt_CddEft_DataValid_TestCase3(void)
{
    //Step 1) Set pre-conditions
    CddEft_CrcValid = FALSE;

    //Step 2) Assign Input values
    CddEft_boCrcCalculated = TRUE;

    //Step 3) Call FUT
    CddEft_DataValid_RetVal = CddEft_DataValid();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CddEft_DataValid_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddEft_Init_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///         - Test subject: Test if function set event status to passed if CRC was 
///                         calculated and it is valid
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input     Mt_InitEft()
/// \input     CddEft_boCrcCalculated = FALSE
/// \input     Dem_SetEventStatus_HitCount=0u
/// \input     Dem_SetEventStatus_Param1 = CRC_CALIB_DEFECT
/// \input     Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_FAILED
/// \input     Dem_Set_Init_Window_HitCount = 0u
/// \input     Crc_CalculateCRC32_4C11DB7_RetVal = 0xBB1AABFEu
///
/// - Expectations:
///
/// \output    Dem_SetEventStatus_HitCount = 1u
/// \output    Dem_Set_Init_Window_HitCount = 2u
/// \output    Dem_SetEventStatus_Param1 = CRC_PAV_DEFECT
/// \output    Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED
///
//-----------------------------------------------------------------------------
void Mt_CddEft_Init_TestCase1(void)
{
    //Step 1) Set pre-conditions
    Mt_InitEft();

    //Step 2) Assign Input values
    CddEft_boCrcCalculated = FALSE;
    Dem_SetEventStatus_Param1 = CRC_CALIB_DEFECT;
    Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_FAILED;
    Dem_SetEventStatus_HitCount = 0u;
    Dem_Set_Init_Window_HitCount = 0u;
    Crc_CalculateCRC32_4C11DB7_RetVal = 0xBB1AABFEu;

    //Step 3) Call FUT
    CddEft_Init();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
    AL_UNITTEST_CHECK(Dem_Set_Init_Window_HitCount, 2u, == );
    AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, CRC_PAV_DEFECT, == );
    AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_PASSED, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddEft_Init_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject:  Test if function set DTC for error and set the event status
///                         to failed if CRC was calculated and it is invalid
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input     CddEft_boCrcCalculated = FALSE
/// \input     EftData.Eft_Crc.Crc32.ulCrc = 0u
/// \input     Dem_SetEventStatus_Param1 = CRC_CALIB_DEFECT
/// input      Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED
/// \input     Dem_Set_Init_Window_HitCount = 0u
/// \input     Dem_SetEventStatus_HitCount = 0u
///
/// - Expectations:
///
/// \output    Dem_SetEventStatus_HitCount = 1u
/// \output    Dem_Set_Init_Window_HitCount = 2u
/// \output    Dem_SetEventStatus_Param1 = CRC_PAV_DEFECT
/// \output    Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_FAILED
///
//-----------------------------------------------------------------------------
void Mt_CddEft_Init_TestCase2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CddEft_boCrcCalculated = FALSE;
    EftData.Eft_Crc.Crc32.ulCrc = 0u;
    Dem_SetEventStatus_Param1 = CRC_CALIB_DEFECT;
    Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED;
    Dem_Set_Init_Window_HitCount = 0u;
    Dem_SetEventStatus_HitCount = 0u;

    //Step 3) Call FUT
    CddEft_Init();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
    AL_UNITTEST_CHECK(Dem_Set_Init_Window_HitCount, 2u, == );
    AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, CRC_PAV_DEFECT, == );
    AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_FAILED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_riCddEftInit
///
/// \Functional Safety: NA
///
/// \Test Case Description
///        - Test subject: Test if function perform CRC check and if the CRC status is
///                        invalid set DTC for error and set the event status on failed
///
///         - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input CddEft_boCrcCalculated = FALSE;
/// \input EftData.Eft_Crc.Crc32.ulCrc = 0u;
/// \input Dem_SetEventStatus_Param1 = CRC_CALIB_DEFECT;
/// \input Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED;
/// \input Dem_Set_Init_Window_HitCount = 0u;
/// \input Dem_SetEventStatus_HitCount = 0u;
/// - Expectations:
///
/// \output    Dem_SetEventStatus_HitCount = 1u
/// \output    Dem_Set_Init_Window_HitCount = 2u
/// \output    Dem_SetEventStatus_Param1 = CRC_PAV_DEFECT
/// \output    Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_FAILED
///
//-----------------------------------------------------------------------------
void Mt_riCddEftInit(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input values
    CddEft_boCrcCalculated = FALSE;
    EftData.Eft_Crc.Crc32.ulCrc = 0u;
    Dem_SetEventStatus_Param1 = CRC_CALIB_DEFECT;
    Dem_SetEventStatus_Param2 = DEM_EVENT_STATUS_PASSED;
    Dem_Set_Init_Window_HitCount = 0u;
    Dem_SetEventStatus_HitCount = 0u;

    //Step 3) Call FUT
    riCddEftInit();

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
    AL_UNITTEST_CHECK(Dem_Set_Init_Window_HitCount, 2u, == );
    AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1, CRC_PAV_DEFECT, == );
    AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2, DEM_EVENT_STATUS_FAILED, == );

}

//----------------------------------------------------------------------------
/// \brief  Initialization 
///
/// \descr  initalization EFT for unit test.
///
/// \param  -EftData, Eft_TestData
///
/// \return void
//-----------------------------------------------------------------------------
void Mt_InitEft(void)
{
    memcpy(&EftData, Eft_ucTestData, sizeof(Eft_ucTestData));
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddEft_DataValid
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the CRC status is valid or invalid
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddEft_DataValid(void)
{
    Mt_CddEft_DataValid_TestCase1();
    Mt_CddEft_DataValid_TestCase2();
    Mt_CddEft_DataValid_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_CddEft_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the EFT data is valid or invalid, if EFT data is invalid 
///                     set DTC for error
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_CddEft_Init(void)
{
    Mt_CddEft_Init_TestCase1();
    Mt_CddEft_Init_TestCase2();
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
    ALUnitTest_AddFunction("Mt_CddEft_DataValid", Mt_CddEft_DataValid);
    ALUnitTest_AddFunction("Mt_CddEft_Init", Mt_CddEft_Init);
    ALUnitTest_AddFunction("Mt_riCddEftInit", Mt_riCddEftInit);
}