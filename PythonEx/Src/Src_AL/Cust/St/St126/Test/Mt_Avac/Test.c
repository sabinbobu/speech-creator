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
/// \brief  Unit Test Cases for AVAC
///
/// \author 
///         mailTo:
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Files covered by this module unit test:
///
///St126/App/Swc/AfsMaster/Avac:
///               - Avac.c
///               - AvacAlgDyn1.c
///               - AvacData.c
///               - AvacUtil.c
///               - AvacVddAdvanced.c
///               - ctaaAvac.c
///
//-----------------------------------------------------------------------------

//=============================================================================
// includes
//=============================================================================

#include <ALUnitTest_UserInterface.h>

// Headers of the unit test Module
#include "Test.h"

// Stub headers
#include "Test_Stubs.h"

//=============================================================================
// Test Cases
//=============================================================================

/*AvacUtil.c*/

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacUtil_Order1FilterByRelTime_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if Avac calculates filter coefficient and calls of Order1Filter()
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input AvacUtil_Order1FilterByRelTime_Param1 = 10
/// input AvacUtil_Order1FilterByRelTime_Param2 = 0u
/// input AvacUtil_Order1FilterByRelTime_Param3 = 20
/// input AvacUtil_Order1FilterByRelTime_RetVal = 0
/// input Order1Filter_Param1                   = 0u
/// input Order1Filter_Param2                   = 0u
/// input Order1Filter_HitCount                 = 0u
/// input Order1FilterValue_Param1              = 0u
/// input Order1FilterValue_HitCount            = 0u
/// input Order1FilterValue_RetVal              = 23
///
/// - Expectations:
///
/// output Order1Filter_Param1                   = 10
/// output Order1Filter_Param2                   = 20
/// output Order1Filter_HitCount                 = 1u
/// output Order1FilterValue_Param1              = 10
/// output Order1FilterValue_HitCount            = 1u
/// output AvacUtil_Order1FilterByRelTime_RetVal = 23
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacUtil_Order1FilterByRelTime_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacUtil_Order1FilterByRelTime_Param1 = 10;
  AvacUtil_Order1FilterByRelTime_Param2 = 0u;
  AvacUtil_Order1FilterByRelTime_Param3 = 20;
  AvacUtil_Order1FilterByRelTime_RetVal = 0;

  Order1Filter_Param1                   = 0u;
  Order1Filter_Param2                   = 0u;
  Order1Filter_HitCount                 = 0u;
  Order1FilterValue_Param1              = 0u;
  Order1FilterValue_HitCount            = 0u;
  Order1FilterValue_RetVal              = 23;

  //Step 3) Call the FUT

  AvacUtil_Order1FilterByRelTime_RetVal = AvacUtil_Order1FilterByRelTime(&AvacUtil_Order1FilterByRelTime_Param1, AvacUtil_Order1FilterByRelTime_Param2, AvacUtil_Order1FilterByRelTime_Param3);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Order1Filter_Param1,                   10, == );
  AL_UNITTEST_CHECK(Order1Filter_Param2,                   20, == );
  AL_UNITTEST_CHECK(Order1Filter_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(Order1FilterValue_Param1,              10, == );
  AL_UNITTEST_CHECK(Order1FilterValue_HitCount,            1u, == );
  AL_UNITTEST_CHECK(AvacUtil_Order1FilterByRelTime_RetVal, 23, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacUtil_Order1FilterByRelTime_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if Avac calculates filter coefficient and calls of Order1Filter()
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input AvacUtil_Order1FilterByRelTime_Param1 = 10
/// input AvacUtil_Order1FilterByRelTime_Param2 = 10u
/// input AvacUtil_Order1FilterByRelTime_Param3 = 20
/// input AvacUtil_Order1FilterByRelTime_RetVal = 0
/// input Order1Filter_Param1                   = 0u
/// input Order1Filter_Param2                   = 0u
/// input Order1Filter_HitCount                 = 0u
/// input Order1FilterValue_Param1              = 0u
/// input Order1FilterValue_HitCount            = 0u
/// input Order1FilterValue_RetVal              = 23
///
/// - Expectations:
///
/// output Order1Filter_Param1                   = 10
/// output Order1Filter_Param2                   = 20
/// output Order1Filter_HitCount                 = 1u
/// output Order1FilterValue_Param1              = 10
/// output Order1FilterValue_HitCount            = 1u
/// output AvacUtil_Order1FilterByRelTime_RetVal = 23
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacUtil_Order1FilterByRelTime_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  
  AvacUtil_Order1FilterByRelTime_Param1 = 10;
  AvacUtil_Order1FilterByRelTime_Param2 = 10u;
  AvacUtil_Order1FilterByRelTime_Param3 = 20;
  AvacUtil_Order1FilterByRelTime_RetVal = 0;

  Order1Filter_Param1                   = 0u;
  Order1Filter_Param2                   = 0u;
  Order1Filter_HitCount                 = 0u;
  Order1FilterValue_Param1              = 0u;
  Order1FilterValue_HitCount            = 0u;
  Order1FilterValue_RetVal              = 23;

  //Step 3) Call the FUT

  AvacUtil_Order1FilterByRelTime_RetVal = AvacUtil_Order1FilterByRelTime(&AvacUtil_Order1FilterByRelTime_Param1, AvacUtil_Order1FilterByRelTime_Param2, AvacUtil_Order1FilterByRelTime_Param3);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Order1Filter_Param1,                   10, == );
  AL_UNITTEST_CHECK(Order1Filter_Param2,                   20, == );
  AL_UNITTEST_CHECK(Order1Filter_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(Order1FilterValue_Param1,              10, == );
  AL_UNITTEST_CHECK(Order1FilterValue_HitCount,            1u, == );
  AL_UNITTEST_CHECK(AvacUtil_Order1FilterByRelTime_RetVal, 23, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacUtil_Order1FilterByRelTime_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if Avac calculates filter coefficient and calls of Order1Filter()
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input AvacUtil_Order1FilterByRelTime_Param1 = 10
/// input AvacUtil_Order1FilterByRelTime_Param2 = 128u
/// input AvacUtil_Order1FilterByRelTime_Param3 = 20
/// input AvacUtil_Order1FilterByRelTime_RetVal = 0
/// input Order1Filter_Param1                   = 0u
/// input Order1Filter_Param2                   = 0u
/// input Order1Filter_HitCount                 = 0u
/// input Order1FilterValue_Param1              = 0u
/// input Order1FilterValue_HitCount            = 0u
/// input Order1FilterValue_RetVal              = 23
///
/// - Expectations:
///
/// output Order1Filter_Param1                   = 10
/// output Order1Filter_Param2                   = 20
/// output Order1Filter_HitCount                 = 1u
/// output Order1FilterValue_Param1              = 10
/// output Order1FilterValue_HitCount            = 1u
/// output AvacUtil_Order1FilterByRelTime_RetVal = 23
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacUtil_Order1FilterByRelTime_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  
  AvacUtil_Order1FilterByRelTime_Param1 = 10;
  AvacUtil_Order1FilterByRelTime_Param2 = 128u;
  AvacUtil_Order1FilterByRelTime_Param3 = 20;
  AvacUtil_Order1FilterByRelTime_RetVal = 0;

  Order1Filter_Param1                   = 0u;
  Order1Filter_Param2                   = 0u;
  Order1Filter_HitCount                 = 0u;
  Order1FilterValue_Param1              = 0u;
  Order1FilterValue_HitCount            = 0u;
  Order1FilterValue_RetVal              = 23;

  //Step 3) Call the FUT

  AvacUtil_Order1FilterByRelTime_RetVal = AvacUtil_Order1FilterByRelTime(&AvacUtil_Order1FilterByRelTime_Param1, AvacUtil_Order1FilterByRelTime_Param2, AvacUtil_Order1FilterByRelTime_Param3);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Order1Filter_Param1,                   10, == );
  AL_UNITTEST_CHECK(Order1Filter_Param2,                   20, == );
  AL_UNITTEST_CHECK(Order1Filter_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(Order1FilterValue_Param1,              10, == );
  AL_UNITTEST_CHECK(Order1FilterValue_HitCount,            1u, == );
  AL_UNITTEST_CHECK(AvacUtil_Order1FilterByRelTime_RetVal, 23, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacUtil_SignalLimiter_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if limits the signal value
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacUtil_SignalLimiter_Param1 = 100
/// input  AvacUtil_SignalLimiter_Param2 = 0
/// input  AvacUtil_SignalLimiter_Param3 = 10
/// input  AvacUtil_SignalLimiter_RetVal = 0
///
/// - Expectations:
///
/// output AvacUtil_SignalLimiter_RetVal  = 10
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacUtil_SignalLimiter_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacUtil_SignalLimiter_Param1 = 100;
  AvacUtil_SignalLimiter_Param2 = 0;
  AvacUtil_SignalLimiter_Param3 = 10;
  AvacUtil_SignalLimiter_RetVal = 0;

  //Step 3) Call the FUT

  AvacUtil_SignalLimiter_RetVal = AvacUtil_SignalLimiter(AvacUtil_SignalLimiter_Param1, AvacUtil_SignalLimiter_Param2, AvacUtil_SignalLimiter_Param3);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(AvacUtil_SignalLimiter_RetVal, 10, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacUtil_SignalLimiter_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if limits the signal value
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacUtil_SignalLimiter_Param1 = 100
/// input  AvacUtil_SignalLimiter_Param2 = 0
/// input  AvacUtil_SignalLimiter_Param3 = 101
/// input  AvacUtil_SignalLimiter_RetVal = 0
///
/// - Expectations:
///
/// output AvacUtil_SignalLimiter_RetVal  = 10
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacUtil_SignalLimiter_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacUtil_SignalLimiter_Param1 = 100;
  AvacUtil_SignalLimiter_Param2 = 0;
  AvacUtil_SignalLimiter_Param3 = 101;
  AvacUtil_SignalLimiter_RetVal = 0;

  //Step 3) Call the FUT

  AvacUtil_SignalLimiter_RetVal = AvacUtil_SignalLimiter(AvacUtil_SignalLimiter_Param1, AvacUtil_SignalLimiter_Param2, AvacUtil_SignalLimiter_Param3);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(AvacUtil_SignalLimiter_RetVal, 100, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacUtil_SignalLimiter_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if limits the signal value
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacUtil_SignalLimiter_Param1 = 100
/// input  AvacUtil_SignalLimiter_Param2 = 0
/// input  AvacUtil_SignalLimiter_Param3 = -6
/// input  AvacUtil_SignalLimiter_RetVal = 10
///
/// - Expectations:
///
/// output AvacUtil_SignalLimiter_RetVal  = 0
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacUtil_SignalLimiter_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacUtil_SignalLimiter_Param1 = 100;
  AvacUtil_SignalLimiter_Param2 = 0;
  AvacUtil_SignalLimiter_Param3 = -6;
  AvacUtil_SignalLimiter_RetVal = 10;

  //Step 3) Call the FUT

  AvacUtil_SignalLimiter_RetVal = AvacUtil_SignalLimiter(AvacUtil_SignalLimiter_Param1, AvacUtil_SignalLimiter_Param2, AvacUtil_SignalLimiter_Param3);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(AvacUtil_SignalLimiter_RetVal, 0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacUtil_RateLimiter_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function limits the rate value
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacUtil_RateLimiter_Param1 = 1
/// input  AvacUtil_RateLimiter_Param2 = 1
/// input  AvacUtil_RateLimiter_Param3 = 0
/// input  AvacUtil_RateLimiter_Param4 = 10
///
/// - Expectations:
///
/// output AvacUtil_RateLimiter_Param1 = 2
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacUtil_RateLimiter_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacUtil_RateLimiter_Param1 = 1;
  AvacUtil_RateLimiter_Param2 = 1;
  AvacUtil_RateLimiter_Param3 = 0;
  AvacUtil_RateLimiter_Param4 = 10;

  //Step 3) Call the FUT

 AvacUtil_RateLimiter(&AvacUtil_RateLimiter_Param1, AvacUtil_RateLimiter_Param2, AvacUtil_RateLimiter_Param3, AvacUtil_RateLimiter_Param4);

 //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(AvacUtil_RateLimiter_Param1, 2, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacUtil_RateLimiter_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function limits the rate value
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacUtil_RateLimiter_Param1 = 3
/// input  AvacUtil_RateLimiter_Param2 = 0
/// input  AvacUtil_RateLimiter_Param3 = 1
/// input  AvacUtil_RateLimiter_Param4 = 1
///
/// - Expectations:
///
/// output AvacUtil_RateLimiter_Param1 = 2
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacUtil_RateLimiter_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacUtil_RateLimiter_Param1 = 3;
  AvacUtil_RateLimiter_Param2 = 0;
  AvacUtil_RateLimiter_Param3 = 1;
  AvacUtil_RateLimiter_Param4 = 1;

  //Step 3) Call the FUT

  AvacUtil_RateLimiter(&AvacUtil_RateLimiter_Param1, AvacUtil_RateLimiter_Param2, AvacUtil_RateLimiter_Param3, AvacUtil_RateLimiter_Param4);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(AvacUtil_RateLimiter_Param1, 2, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacUtil_RateLimiter_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function limits the rate value
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacUtil_RateLimiter_Param1 = 2
/// input  AvacUtil_RateLimiter_Param2 = 0
/// input  AvacUtil_RateLimiter_Param3 = 1
/// input  AvacUtil_RateLimiter_Param4 = 1
///
/// - Expectations:
///
/// output AvacUtil_RateLimiter_Param1 = 1
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacUtil_RateLimiter_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacUtil_RateLimiter_Param1 = 2;
  AvacUtil_RateLimiter_Param2 = 0;
  AvacUtil_RateLimiter_Param3 = 1;
  AvacUtil_RateLimiter_Param4 = 1;

  //Step 3) Call the FUT

  AvacUtil_RateLimiter(&AvacUtil_RateLimiter_Param1, AvacUtil_RateLimiter_Param2, AvacUtil_RateLimiter_Param3, AvacUtil_RateLimiter_Param4);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(AvacUtil_RateLimiter_Param1, 1, == );
}


/*AvacData.c*/

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacData_ParaFct0_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if the coding data is being passed correctly
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacData_ParaFct0_Param1                       = 0u (eParaFct0_CodingDataInvalid)
/// input  AvacData_ParaFct0_Param2.Header.ucMajorVersion = 5u
///
/// - Expectations:
///
/// output  AvacData_ParaFct0_Param1                       = 0u (eParaFct0_CodingDataInvalid)
/// output  AvacData_ParaFct0_Param2.Header.ucMajorVersion = 5u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacData_ParaFct0_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_ParaFct0_Param1                       = eParaFct0_CodingDataInvalid;
  AvacData_ParaFct0_Param2.Header.ucMajorVersion = 5u;

  //Step 3) Call the FUT

  AvacData_ParaFct0(AvacData_ParaFct0_Param1, &AvacData_ParaFct0_Param2);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(AvacData_ParaFct0_Param1                      , eParaFct0_CodingDataInvalid, == );
  AL_UNITTEST_CHECK(AvacData_ParaFct0_Param2.Header.ucMajorVersion,                          5u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacData_ParaFct0_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if the coding data is being passed correctly
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacData_ParaFct0_Param1                                             = eParaFct0_CodingDataValid;
/// input  AvacData_CodingData.AvacFilter.AvacStp_HighDynamicLimit              = 0;
/// input  AvacData_ParaFct0_Param2.AvacStp.AvacFilter.AvacStp_HighDynamicLimit = 8;
///
/// - Expectations:
///
/// output  AvacData_ParaFct0_Param1                                = eParaFct0_CodingDataValid
/// output  AvacData_CodingData.AvacFilter.AvacStp_HighDynamicLimit = 8
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacData_ParaFct0_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_ParaFct0_Param1                                             = eParaFct0_CodingDataValid;
  AvacData_CodingData.AvacFilter.AvacStp_HighDynamicLimit              = 0;
  AvacData_ParaFct0_Param2.AvacStp.AvacFilter.AvacStp_HighDynamicLimit = 8;

  //Step 3) Call the FUT

  AvacData_ParaFct0(AvacData_ParaFct0_Param1, &AvacData_ParaFct0_Param2);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(AvacData_ParaFct0_Param1                               , eParaFct0_CodingDataValid, == );
  AL_UNITTEST_CHECK(AvacData_CodingData.AvacFilter.AvacStp_HighDynamicLimit,                         8, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacData_Init_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if function initialises the data correctly
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacData_boUseDynamicLeveling = 1u;
///
/// - Expectations:
///
/// output  AvacData_boUseDynamicLeveling = 1u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacData_Init_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_boUseDynamicLeveling = 1u;

  //Step 3) Call the FUT

  AvacData_Init();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(AvacData_boUseDynamicLeveling, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacData_GetLowBeamOn_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if the function returns the low beam on status
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacData_GetLowBeamOn_RetVal = 0u;
///
/// - Expectations:
///
/// output  AvacData_GetLowBeamOn_RetVal = 1u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacData_GetLowBeamOn_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_GetLowBeamOn_RetVal = 0u;

  //Step 3) Call the FUT

  AvacData_GetLowBeamOn_RetVal = AvacData_GetLowBeamOn();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(AvacData_GetLowBeamOn_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacData_GetAvacS_Ok_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if the function returns the TRUE value
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacData_GetAvacS_Ok_RetVal = 0u;
///
/// - Expectations:
///
/// output  AvacData_GetAvacS_Ok_RetVal = 1u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacData_GetAvacS_Ok_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_GetAvacS_Ok_RetVal = 0u;

  //Step 3) Call the FUT

  AvacData_GetAvacS_Ok_RetVal = AvacData_GetAvacS_Ok();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(AvacData_GetAvacS_Ok_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacData_GetAvacS_En_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if the function returns the TRUE value
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacData_GetAvacS_En_RetVal = 0u;
///
/// - Expectations:
///
/// output  AvacData_GetAvacS_En_RetVal = 1u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacData_GetAvacS_En_TestCase_1(void)
{
  //Step 1) Set pre - conditions
   //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_GetAvacS_En_RetVal = 0u;

  //Step 3) Call the FUT

  AvacData_GetAvacS_En_RetVal = AvacData_GetAvacS_En();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(AvacData_GetAvacS_En_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacData_GetAvacD_Ok_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if the function returns the TRUE value
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacData_GetAvacD_Ok_RetVal = 0u;
///
/// - Expectations:
///
/// output  AvacData_GetAvacD_Ok_RetVal = 1u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacData_GetAvacD_Ok_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_GetAvacD_Ok_RetVal = 0u;

  //Step 3) Call the FUT

  AvacData_GetAvacD_Ok_RetVal = AvacData_GetAvacD_Ok();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(AvacData_GetAvacD_Ok_RetVal, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacData_GetAvacD_En_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if the function returns the dynamic leveling status
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacData_boUseDynamicLeveling = 1u;
/// input  AvacData_GetAvacD_En_RetVal   = 0u;
///
/// - Expectations:
///
/// output  AvacData_GetAvacD_En_RetVal = 1
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacData_GetAvacD_En_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_boUseDynamicLeveling = 1u;
  AvacData_GetAvacD_En_RetVal   = 0u;

  //Step 3) Call the FUT

  AvacData_GetAvacD_En_RetVal = AvacData_GetAvacD_En();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(AvacData_GetAvacD_En_RetVal, 1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacData_ReadPitch_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function reads pitch angle data
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacData_ReadPitch_Param1.nAngle       = 0u;
/// input  AvacData_ReadPitch_Param1.nHeightErr   = 0u;
/// input  AvacData_ReadPitch_Param1.eSigQty      = 0u;
/// input  Rte_Read_Pitch_Angle_Param1.nAngle     = 30u;
/// input  Rte_Read_Pitch_Angle_Param1.nHeightErr = 1u;
/// input  Rte_Read_Pitch_Angle_Param1.eSigQty    = 2u;
/// input  Rte_Read_Pitch_Angle_HitCount          = 0u;
/// input  NvmBlockDeltaPwmPara.eNVM_VAC_Input    = eInput_HLS;
///
/// - Expectations:
///
/// output  AvacData_ReadPitch_Param1.nAngle     = 30u
/// output  AvacData_ReadPitch_Param1.nHeightErr = 1u
/// output  AvacData_ReadPitch_Param1.eSigQty    = 2u
/// output  Rte_Read_Pitch_Angle_HitCount        = 1u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacData_ReadPitch_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_ReadPitch_Param1.nAngle       = 0u;
  AvacData_ReadPitch_Param1.nHeightErr   = 0u;
  AvacData_ReadPitch_Param1.eSigQty      = 0u;
  Rte_Read_Pitch_Angle_Param1.nAngle     = 30u;
  Rte_Read_Pitch_Angle_Param1.nHeightErr = 1u;
  Rte_Read_Pitch_Angle_Param1.eSigQty    = 2u;
  Rte_Read_Pitch_Angle_HitCount          = 0u;
  NvmBlockDeltaPwmPara.eNVM_VAC_Input    = eInput_HLS;

  //Step 3) Call the FUT

  AvacData_ReadPitch(&AvacData_ReadPitch_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(AvacData_ReadPitch_Param1.nAngle,       30u, == );
  AL_UNITTEST_CHECK(AvacData_ReadPitch_Param1.nHeightErr,    1u, == );
  AL_UNITTEST_CHECK(AvacData_ReadPitch_Param1.eSigQty,       2u, == );
  AL_UNITTEST_CHECK(Rte_Read_Pitch_Angle_HitCount,           1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacData_ReadPitch_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function reads pitch angle data
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacData_ReadPitch_Param1.nAngle                                                   = 0u;
/// input  AvacData_ReadPitch_Param1.nHeightErr                                               = 0u;
/// input  AvacData_ReadPitch_Param1.eSigQty                                                  = 0u;
/// input  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eAssietteVehicule.nVehiclePitchAngle     = 30u;
/// input  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eSigQty                                  = 2u;
/// input  Rte_Read_SigPrep_VehiclePitchAngle_HitCount                                        = 0u;
/// input  NvmBlockDeltaPwmPara.eNVM_VAC_Input                                                = eInput_CAN;
///
/// - Expectations:
///
/// output  AvacData_ReadPitch_Param1.nAngle                   = -53u
/// output  AvacData_ReadPitch_Param1.nHeightErr               = 0u
/// output  AvacData_ReadPitch_Param1.eSigQty                  = 2u
/// output  Rte_Read_SigPrep_VehiclePitchAngle_HitCount        = 1u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacData_ReadPitch_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_ReadPitch_Param1.nAngle       = 0u;
  AvacData_ReadPitch_Param1.nHeightErr   = 0u;
  AvacData_ReadPitch_Param1.eSigQty      = 0u;
  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eAssietteVehicule.nVehiclePitchAngle     = 30u;
  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eSigQty                                  = 2u;
  Rte_Read_SigPrep_VehiclePitchAngle_HitCount                                        = 0u;
  NvmBlockDeltaPwmPara.eNVM_VAC_Input                                                = eInput_CAN;

  //Step 3) Call the FUT

  AvacData_ReadPitch(&AvacData_ReadPitch_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(AvacData_ReadPitch_Param1.nAngle,                    -53u, == );
  AL_UNITTEST_CHECK(AvacData_ReadPitch_Param1.nHeightErr,                  0u, == );
  AL_UNITTEST_CHECK(AvacData_ReadPitch_Param1.eSigQty,                     2u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehiclePitchAngle_HitCount,           1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacData_ReadPitch_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function reads pitch angle data
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacData_ReadPitch_Param1.nAngle                                                   = 0u;
/// input  AvacData_ReadPitch_Param1.nHeightErr                                               = 0u;
/// input  AvacData_ReadPitch_Param1.eSigQty                                                  = 0u;
/// input  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eAssietteVehicule.nVehiclePitchAngle     = -30u;
/// input  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eSigQty                                  = 2u;
/// input  Rte_Read_SigPrep_VehiclePitchAngle_HitCount                                        = 0u;
/// input  NvmBlockDeltaPwmPara.eNVM_VAC_Input                                                = eInput_CAN;
///
/// - Expectations:
///
/// output  AvacData_ReadPitch_Param1.nAngle                   = 53u
/// output  AvacData_ReadPitch_Param1.nHeightErr               = 0u
/// output  AvacData_ReadPitch_Param1.eSigQty                  = 2u
/// output  Rte_Read_SigPrep_VehiclePitchAngle_HitCount        = 1u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacData_ReadPitch_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_ReadPitch_Param1.nAngle       = 0u;
  AvacData_ReadPitch_Param1.nHeightErr   = 0u;
  AvacData_ReadPitch_Param1.eSigQty      = 0u;
  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eAssietteVehicule.nVehiclePitchAngle     = -30u;
  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eSigQty                                  = 2u;
  Rte_Read_SigPrep_VehiclePitchAngle_HitCount                                        = 0u;
  NvmBlockDeltaPwmPara.eNVM_VAC_Input                                                = eInput_CAN;

  //Step 3) Call the FUT

  AvacData_ReadPitch(&AvacData_ReadPitch_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(AvacData_ReadPitch_Param1.nAngle,                     53u, == );
  AL_UNITTEST_CHECK(AvacData_ReadPitch_Param1.nHeightErr,                  0u, == );
  AL_UNITTEST_CHECK(AvacData_ReadPitch_Param1.eSigQty,                     2u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_VehiclePitchAngle_HitCount,           1u, == );
}


//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacData_ReadSpeed_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function reads vehicle speed from RTE
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacData_ReadSpeed_Param1.nSpeed                                           = 0u;
/// input  AvacData_ReadSpeed_Param1.nAcceleration                                    = 0u;
/// input  AvacData_ReadSpeed_Param1.unMotion                                         = 10u;
/// input  AvacData_ReadSpeed_Param1.eSigQty                                          = 0u;
/// input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 50u;
/// input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = 10u;
/// input  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
/// input  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 20u;
/// input  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;
///
/// - Expectations:
///
/// output  AvacData_ReadSpeed_Param1.nSpeed               = 50uu
/// output  AvacData_ReadSpeed_Param1.nAcceleration        = 20u
/// output  AvacData_ReadSpeed_Param1.unMotion             =  0u
/// output  AvacData_ReadSpeed_Param1.eSigQty              = 10u
/// output  Rte_Read_SysMon_VehicleSpeed_HitCount          =  1u
/// output  Rte_Read_SigPrep_DynamicSigs_HitCount          =  1u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacData_ReadSpeed_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_ReadSpeed_Param1.nSpeed                                           = 0u;
  AvacData_ReadSpeed_Param1.nAcceleration                                    = 0u;
  AvacData_ReadSpeed_Param1.unMotion                                         = 10u;
  AvacData_ReadSpeed_Param1.eSigQty                                          = 0u;

  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 50u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = 10u;
  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 20u;
  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;

  //Step 3) Call the FUT

  AvacData_ReadSpeed(&AvacData_ReadSpeed_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(AvacData_ReadSpeed_Param1.nSpeed,            50u, == );
  AL_UNITTEST_CHECK(AvacData_ReadSpeed_Param1.nAcceleration,     20u, == );
  AL_UNITTEST_CHECK(AvacData_ReadSpeed_Param1.unMotion,           0u, == );
  AL_UNITTEST_CHECK(AvacData_ReadSpeed_Param1.eSigQty,           10u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,        1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,        1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacData_ReadAccelPreDetect_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function reads Pedal Acceleration data from RTE
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacData_ReadAccelPreDetect_Param1.nValue                                  = 0u;
/// input  AvacData_ReadAccelPreDetect_Param1.nDelta                                  = 10u;
/// input  AvacData_ReadAccelPreDetect_Param1.eSigQty                                 = 0u;
/// input  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 20u;
/// input  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                                = 30u;
/// input  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;
///
/// - Expectations:
///
/// output  AvacData_ReadAccelPreDetect_Param1.nValue         = 20u
/// output  AvacData_ReadAccelPreDetect_Param1.nDelta         =  0u
/// output  AvacData_ReadAccelPreDetect_Param1.eSigQty        = 30u
/// output  Rte_Read_SigPrep_DynamicSigs_HitCount             =  1u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacData_ReadAccelPreDetect_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_ReadAccelPreDetect_Param1.nValue                                  = 0u;
  AvacData_ReadAccelPreDetect_Param1.nDelta                                  = 10u;
  AvacData_ReadAccelPreDetect_Param1.eSigQty                                 = 0u;

  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 20u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                                = 30u;
  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;

  //Step 3) Call the FUT

  AvacData_ReadAccelPreDetect(&AvacData_ReadAccelPreDetect_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(AvacData_ReadAccelPreDetect_Param1.nValue,    20u, == );
  AL_UNITTEST_CHECK(AvacData_ReadAccelPreDetect_Param1.nDelta,     0u, == );
  AL_UNITTEST_CHECK(AvacData_ReadAccelPreDetect_Param1.eSigQty,   30u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,         1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacData_ReadBrakePreDetect_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function reads Pedal Brake data from RTE
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacData_ReadBrakePreDetect_Param1.nValue                          = 0u;
/// input  AvacData_ReadBrakePreDetect_Param1.nDelta                          = 10u;
/// input  AvacData_ReadBrakePreDetect_Param1.eSigQty                         = 0u;
/// input  Rte_Read_SigPrep_DynamicSigs_Param1.eBrakePressure.ucBrakePressure = 32u;
/// input  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                        = 10u;
/// input  Rte_Read_SigPrep_DynamicSigs_HitCount                              = 0u;
///
/// - Expectations:
///
/// output  AvacData_ReadBrakePreDetect_Param1.nValue         = 32u
/// output  AvacData_ReadBrakePreDetect_Param1.nDelta         =  0u
/// output  AvacData_ReadBrakePreDetect_Param1.eSigQty        = 10u
/// output  Rte_Read_SigPrep_DynamicSigs_HitCount             =  1u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacData_ReadBrakePreDetect_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_ReadBrakePreDetect_Param1.nValue                          = 0u;
  AvacData_ReadBrakePreDetect_Param1.nDelta                          = 10u;
  AvacData_ReadBrakePreDetect_Param1.eSigQty                         = 0u;

  Rte_Read_SigPrep_DynamicSigs_Param1.eBrakePressure.ucBrakePressure = 32u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                        = 10u;
  Rte_Read_SigPrep_DynamicSigs_HitCount                              = 0u;

  //Step 3) Call the FUT

  AvacData_ReadBrakePreDetect(&AvacData_ReadBrakePreDetect_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(AvacData_ReadBrakePreDetect_Param1.nValue,    32u, == );
  AL_UNITTEST_CHECK(AvacData_ReadBrakePreDetect_Param1.nDelta,     0u, == );
  AL_UNITTEST_CHECK(AvacData_ReadBrakePreDetect_Param1.eSigQty,   10u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,         1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacData_WriteAvacOut_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if the function writes the data over the RTE port
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacData_WriteAvacOut_Param1.eSigQty                                           = 1u;
/// input  AvacData_WriteAvacOut_Param1.nAngle                                            = 1u;
/// input  NvmBlockDeltaPwmPara.eNVM_VAC_Input                                            = eInput
/// input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState                               = 0u;
/// input  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eAssietteVehicule.nVehiclePitchAngle = 511u;
/// input  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eSigQty                              = 0u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[0].Ver                                    = 0u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[1].Ver                                    = 0u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[0].Hor                                    = 10u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[1].Hor                                    = 10u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[0].Width                                  = 10u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[1].Width                                  = 10u;
/// input  Rte_Write_ppsAvacOut_Param1.State                                              = 0u;
/// input  Rte_Write_ppsAvacOut_HitCount                                                  = 0u;
///
/// - Expectations:
///
/// output  Rte_Write_ppsAvacOut_HitCount                        = 1u
/// output  Rte_Write_ppsAvacOut_Param1.Position[0].Ver          = 1u
/// output  Rte_Write_ppsAvacOut_Param1.Position[1].Ver          = 1u
/// output  Rte_Write_ppsAvacOut_Param1.Position[0].Hor          = 0u
/// output  Rte_Write_ppsAvacOut_Param1.Position[1].Hor          = 0u
/// output  Rte_Write_ppsAvacOut_Param1.Position[0].Width        = 0u
/// output  Rte_Write_ppsAvacOut_Param1.Position[1].Width        = 0u
/// output  Rte_Write_ppsAvacOut_Param1.State                    = 1u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacData_WriteAvacOut_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_WriteAvacOut_Param1.eSigQty                                           = 1u;
  AvacData_WriteAvacOut_Param1.nAngle                                            = 1u;
  NvmBlockDeltaPwmPara.eNVM_VAC_Input                                            = eInput_HLS;

  Rte_Read_SysMon_VehNetState_Param1.eVESMainState                               = 0u;
  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eAssietteVehicule.nVehiclePitchAngle = 511u;
  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eSigQty                              = 0u;
  Rte_Write_ppsAvacOut_Param1.Position[0].Ver                                    = 0u;
  Rte_Write_ppsAvacOut_Param1.Position[1].Ver                                    = 0u;
  Rte_Write_ppsAvacOut_Param1.Position[0].Hor                                    = 10u;
  Rte_Write_ppsAvacOut_Param1.Position[1].Hor                                    = 10u;
  Rte_Write_ppsAvacOut_Param1.Position[0].Width                                  = 10u;
  Rte_Write_ppsAvacOut_Param1.Position[1].Width                                  = 10u;
  Rte_Write_ppsAvacOut_Param1.State                                              = 0u;
  Rte_Write_ppsAvacOut_HitCount                                                  = 0u;

  //Step 3) Call the FUT

  AvacData_WriteAvacOut(&AvacData_WriteAvacOut_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
 
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_HitCount,                      1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[0].Ver,        1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[1].Ver,        1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[0].Hor,        0u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[1].Hor,        0u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[0].Width,      0u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[1].Width,      0u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.State,                  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacData_WriteAvacOut_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if the function writes the data over the RTE port
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacData_WriteAvacOut_Param1.eSigQty                                           = 1u;
/// input  AvacData_WriteAvacOut_Param1.nAngle                                            = -2;
/// input  NvmBlockDeltaPwmPara.eNVM_VAC_Input                                            = eInput_CAN;
/// input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState                               = 1u;
/// input  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eAssietteVehicule.nVehiclePitchAngle = 0x200;
/// input  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eSigQty                              = 1u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[0].Ver                                    = 0u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[1].Ver                                    = 0u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[0].Hor                                    = 10u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[1].Hor                                    = 10u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[0].Width                                  = 10u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[1].Width                                  = 10u;
/// input  Rte_Write_ppsAvacOut_Param1.State                                              = 0u;
/// input  Rte_Write_ppsAvacOut_HitCount                                                  = 0u;
///
/// - Expectations:
///
/// output  Rte_Write_ppsAvacOut_HitCount                        = 1u
/// output  Rte_Write_ppsAvacOut_Param1.Position[0].Ver          = -1
/// output  Rte_Write_ppsAvacOut_Param1.Position[1].Ver          = -1
/// output  Rte_Write_ppsAvacOut_Param1.Position[0].Hor          = 0u
/// output  Rte_Write_ppsAvacOut_Param1.Position[1].Hor          = 0u
/// output  Rte_Write_ppsAvacOut_Param1.Position[1].Width        = 0u
/// output  Rte_Write_ppsAvacOut_Param1.Position[0].Width        = 0u
/// output  Rte_Write_ppsAvacOut_Param1.State                    = 1u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacData_WriteAvacOut_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_WriteAvacOut_Param1.eSigQty                                           = 1u;
  AvacData_WriteAvacOut_Param1.nAngle                                            = -2;
  NvmBlockDeltaPwmPara.eNVM_VAC_Input                                            = eInput_CAN;

  Rte_Read_SysMon_VehNetState_Param1.eVESMainState                               = 1u;
  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eAssietteVehicule.nVehiclePitchAngle = 0x200;
  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eSigQty                              = 1u;
  Rte_Write_ppsAvacOut_Param1.Position[0].Ver                                    = 0u;
  Rte_Write_ppsAvacOut_Param1.Position[1].Ver                                    = 0u;
  Rte_Write_ppsAvacOut_Param1.Position[0].Hor                                    = 10u;
  Rte_Write_ppsAvacOut_Param1.Position[1].Hor                                    = 10u;
  Rte_Write_ppsAvacOut_Param1.Position[0].Width                                  = 10u;
  Rte_Write_ppsAvacOut_Param1.Position[1].Width                                  = 10u;
  Rte_Write_ppsAvacOut_Param1.State                                              = 0u;
  Rte_Write_ppsAvacOut_HitCount                                                  = 0u;

  //Step 3) Call the FUT

  AvacData_WriteAvacOut(&AvacData_WriteAvacOut_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_HitCount,                      1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[0].Ver,        -1, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[1].Ver,        -1, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[0].Hor,        0u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[1].Hor,        0u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[0].Width,      0u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[1].Width,      0u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.State,                  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacData_WriteAvacOut_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if the function writes the data over the RTE port
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacData_WriteAvacOut_Param1.eSigQty                                           = 1u;
/// input  AvacData_WriteAvacOut_Param1.nAngle                                            = -2;
/// input  NvmBlockDeltaPwmPara.eNVM_VAC_Input                                            = eInput_Invalid;
/// input  NvmBlockDeltaPwmPara.ucZeroLevProg                                             = 0xFFu;
/// input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState                               = 3u;
/// input  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eAssietteVehicule.nVehiclePitchAngle = 0u;
/// input  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eSigQty                              = 1u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[0].Ver                                    = 10u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[1].Ver                                    = 10u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[0].Hor                                    = 10u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[1].Hor                                    = 10u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[0].Width                                  = 10u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[1].Width                                  = 10u;
/// input  Rte_Write_ppsAvacOut_Param1.State                                              = 0u;
/// input  Rte_Write_ppsAvacOut_HitCount                                                  = 0u;
///
/// - Expectations:
///
/// output  Rte_Write_ppsAvacOut_HitCount                        = 1u
/// output  Rte_Write_ppsAvacOut_Param1.Position[0].Ver          = -1
/// output  Rte_Write_ppsAvacOut_Param1.Position[1].Ver          = -1
/// output  Rte_Write_ppsAvacOut_Param1.Position[0].Hor          = 0u
/// output  Rte_Write_ppsAvacOut_Param1.Position[1].Hor          = 0u
/// output  Rte_Write_ppsAvacOut_Param1.Position[0].Width        = 0u
/// output  Rte_Write_ppsAvacOut_Param1.Position[1].Width        = 0u
/// output  Rte_Write_ppsAvacOut_Param1.State                    = 1u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacData_WriteAvacOut_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_WriteAvacOut_Param1.eSigQty                                           = 1u;
  AvacData_WriteAvacOut_Param1.nAngle                                            = -2;
  NvmBlockDeltaPwmPara.eNVM_VAC_Input                                            = eInput_Invalid;
  NvmBlockDeltaPwmPara.ucZeroLevProg                                             = 0xFFu;

  Rte_Read_SysMon_VehNetState_Param1.eVESMainState                               = 3u;
  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eAssietteVehicule.nVehiclePitchAngle = 0u;
  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eSigQty                              = 1u;
  Rte_Write_ppsAvacOut_Param1.Position[0].Ver                                    = 10u;
  Rte_Write_ppsAvacOut_Param1.Position[1].Ver                                    = 10u;
  Rte_Write_ppsAvacOut_Param1.Position[0].Hor                                    = 10u;
  Rte_Write_ppsAvacOut_Param1.Position[1].Hor                                    = 10u;
  Rte_Write_ppsAvacOut_Param1.Position[0].Width                                  = 10u;
  Rte_Write_ppsAvacOut_Param1.Position[1].Width                                  = 10u;
  Rte_Write_ppsAvacOut_Param1.State                                              = 0u;
  Rte_Write_ppsAvacOut_HitCount                                                  = 0u;

  //Step 3) Call the FUT

  AvacData_WriteAvacOut(&AvacData_WriteAvacOut_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_HitCount,                      1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[0].Ver,        -1, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[1].Ver,        -1, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[0].Hor,        0u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[1].Hor,        0u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[0].Width,      0u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[1].Width,      0u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.State,                  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacData_WriteAvacOut_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if the function writes the data over the RTE port
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacData_WriteAvacOut_Param1.eSigQty                                           = 1u;
/// input  AvacData_WriteAvacOut_Param1.nAngle                                            = -1;
/// input  NvmBlockDeltaPwmPara.eNVM_VAC_Input                                            = eInput_HLS;
/// input  NvmBlockDeltaPwmPara.ucZeroLevProg                                             = 0u;
/// input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState                               = 0u;
/// input  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eAssietteVehicule.nVehiclePitchAngle = 511u;
/// input  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eSigQty                              = 0u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[0].Ver                                    = 0u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[1].Ver                                    = 0u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[0].Hor                                    = 10u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[1].Hor                                    = 10u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[0].Width                                  = 10u;
/// input  Rte_Write_ppsAvacOut_Param1.Position[1].Width                                  = 10u;
/// input  Rte_Write_ppsAvacOut_Param1.State                                              = 0u;
/// input  Rte_Write_ppsAvacOut_HitCount                                                  = 0u;
///
/// - Expectations:
///
/// output Rte_Write_ppsAvacOut_HitCount                        = 1u
/// output Rte_Write_ppsAvacOut_Param1.Position[0].Ver          = -1
/// output Rte_Write_ppsAvacOut_Param1.Position[1].Ver          = -1
/// output Rte_Write_ppsAvacOut_Param1.Position[0].Hor          = 0u
/// output Rte_Write_ppsAvacOut_Param1.Position[1].Hor          = 0u
/// output Rte_Write_ppsAvacOut_Param1.Position[0].Width        = 0u
/// output Rte_Write_ppsAvacOut_Param1.Position[1].Width        = 0u
/// output Rte_Write_ppsAvacOut_Param1.State                    = 1u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacData_WriteAvacOut_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_WriteAvacOut_Param1.eSigQty                                           = 1u;
  AvacData_WriteAvacOut_Param1.nAngle                                            = -1;
  NvmBlockDeltaPwmPara.eNVM_VAC_Input                                            = eInput_HLS;
  NvmBlockDeltaPwmPara.ucZeroLevProg                                             = 0u;

  Rte_Read_SysMon_VehNetState_Param1.eVESMainState                               = 0u;
  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eAssietteVehicule.nVehiclePitchAngle = 511u;
  Rte_Read_SigPrep_VehiclePitchAngle_Param1.eSigQty                              = 0u;
  Rte_Write_ppsAvacOut_Param1.Position[0].Ver                                    = 0u;
  Rte_Write_ppsAvacOut_Param1.Position[1].Ver                                    = 0u;
  Rte_Write_ppsAvacOut_Param1.Position[0].Hor                                    = 10u;
  Rte_Write_ppsAvacOut_Param1.Position[1].Hor                                    = 10u;
  Rte_Write_ppsAvacOut_Param1.Position[0].Width                                  = 10u;
  Rte_Write_ppsAvacOut_Param1.Position[1].Width                                  = 10u;
  Rte_Write_ppsAvacOut_Param1.State                                              = 0u;
  Rte_Write_ppsAvacOut_HitCount                                                  = 0u;

  //Step 3) Call the FUT

  AvacData_WriteAvacOut(&AvacData_WriteAvacOut_Param1);

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
 
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_HitCount,                      1u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[0].Ver,        -1, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[1].Ver,        -1, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[0].Hor,        0u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[1].Hor,        0u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[0].Width,      0u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.Position[1].Width,      0u, == );
  AL_UNITTEST_CHECK(Rte_Write_ppsAvacOut_Param1.State,                  1u, == );
}


/*AvacVddAdvanced.c*/

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if acceleration state and acceleration index are set to invalid
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty      = 3u;
/// input  Rte_Read_SysMon_VehicleSpeed_HitCount            = 0u;
/// input  Rte_Read_SigPrep_DynamicSigs_HitCount            = 0u;
/// input  AvacVdd_ucDynState                               = 0u;
/// input  AvacVdd_ucAccIndex                               = 0u;
///
/// - Expectations:
///
/// output Rte_Read_SysMon_VehicleSpeed_HitCount =     1u
/// output Rte_Read_SigPrep_DynamicSigs_HitCount =     3u
/// output AvacVdd_ucDynState,                   =  0x80u
/// output AvacVdd_ucAccIndex                    =  0xFFu
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty      = 3u;
  Rte_Read_SysMon_VehicleSpeed_HitCount            = 0u;
  Rte_Read_SigPrep_DynamicSigs_HitCount            = 0u;

  AvacVdd_ucDynState                               = 0u;
  AvacVdd_ucAccIndex                               = 0u;

  //Step 3) Call the FUT

  AvacVdd_DetectVehicleDynamic();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,        1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,        3u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucDynState,                        0x80u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucAccIndex,                        0xFFu, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function prepares dynamic state and calculates acceleration index
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input   Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                      = 1u;
/// input   Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 20u;
/// input   Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u;
/// input   Rte_Read_SigPrep_DynamicSigs_HitCount                            = 0u;
/// input   AvacVdd_ucDynState                                               = 0u;
/// input   AvacVdd_ucAccIndex                                               = 0u;
/// input   UTIL_ABS_HitCount                                                = 0u;
/// input   UTIL_ABS_RetVal                                                  = 20u;
/// input   AvacVdd_acAccelArray[0u]                                         = 30u;
/// input   AvacVdd_acAccelArray[1u]                                         = 10u;
///
/// - Expectations:
///
/// output Rte_Read_SysMon_VehicleSpeed_HitCount =     1u
/// output Rte_Read_SigPrep_DynamicSigs_HitCount =     3u
/// output UTIL_ABS_HitCount                     =     2u
/// output AvacVdd_ucDynState                    =  0x04u
/// output AvacVdd_ucAccIndex                    =   128u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                      = 1u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 20u;
  Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u;
  Rte_Read_SigPrep_DynamicSigs_HitCount                            = 0u;
  
  AvacVdd_ucDynState                                               = 0u;
  AvacVdd_ucAccIndex                                               = 0u;
  UTIL_ABS_HitCount                                                = 0u;
  UTIL_ABS_RetVal                                                  = 20u;
  AvacVdd_acAccelArray[0u]                                         = 30u;
  AvacVdd_acAccelArray[1u]                                         = 10u;

  //Step 3) Call the FUT

  AvacVdd_DetectVehicleDynamic();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,        1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,        3u, == );
  AL_UNITTEST_CHECK(UTIL_ABS_HitCount,                            2u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucDynState,                        0x04u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucAccIndex,                         128u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function prepares dynamic state and calculates acceleration index
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input   Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                      = 1u;
/// input   Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 700u;
/// input   Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u;
/// input   Rte_Read_SigPrep_DynamicSigs_HitCount                            = 0u;
/// input   AvacVdd_ucDynState                                               = 0u;
/// input   AvacVdd_ucAccIndex                                               = 0u;
/// input   UTIL_ABS_HitCount                                                = 0u;
/// input   UTIL_ABS_RetVal                                                  = 20u;
/// input   AvacVdd_acAccelArray[0u]                                         = 30u;
/// input   AvacVdd_acAccelArray[1u]                                         = 10u;
///
/// - Expectations:
///
/// output Rte_Read_SysMon_VehicleSpeed_HitCount  =     1u
/// output Rte_Read_SigPrep_DynamicSigs_HitCount  =     3u
/// output UTIL_ABS_HitCount                      =     2u
/// output AvacVdd_ucDynState                     =  0x01u
/// output AvacVdd_ucAccIndex                     =   128u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
 
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                      = 1u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 700u;
  Rte_Read_SysMon_VehicleSpeed_HitCount                            = 0u;
  Rte_Read_SigPrep_DynamicSigs_HitCount                            = 0u;
  
  AvacVdd_ucDynState                                               = 0u;
  AvacVdd_ucAccIndex                                               = 0u;
  UTIL_ABS_HitCount                                                = 0u;
  UTIL_ABS_RetVal                                                  = 20u;
  AvacVdd_acAccelArray[0u]                                         = 30u;
  AvacVdd_acAccelArray[1u]                                         = 10u;

  //Step 3) Call the FUT

  AvacVdd_DetectVehicleDynamic();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,        1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,        3u, == );
  AL_UNITTEST_CHECK(UTIL_ABS_HitCount,                            2u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucDynState,                        0x01u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucAccIndex,                         128u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function prepares dynamic state and calculates acceleration index
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input    Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = 1u;
/// input    Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 700u;
/// input    Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
/// input    Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 20u;
/// input    Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                                = 1u;
/// input    Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;
/// input    AvacVdd_ucDynState                                                         = 0u;
/// input    AvacVdd_ucAccIndex                                                         = 0u;
/// input    UTIL_ABS_HitCount                                                          = 0u;
/// input    UTIL_ABS_RetVal                                                            = 2u;
/// input    AvacVdd_acAccelArray[0u]                                                   = 30u;
/// input    AvacVdd_acAccelArray[1u]                                                   = 10u;
///
/// - Expectations:
///
/// output Rte_Read_SysMon_VehicleSpeed_HitCount  =     1u
/// output Rte_Read_SigPrep_DynamicSigs_HitCount  =     3u
/// output UTIL_ABS_HitCount                      =     2u
/// output AvacVdd_ucDynState                     =  0x01u
/// output AvacVdd_ucAccIndex                     =   128u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = 1u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 700u;
  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 20u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                                = 1u;
  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;

  AvacVdd_ucDynState                                                         = 0u;
  AvacVdd_ucAccIndex                                                         = 0u;
  UTIL_ABS_HitCount                                                          = 0u;
  UTIL_ABS_RetVal                                                            = 2u;
  AvacVdd_acAccelArray[0u]                                                   = 30u;
  AvacVdd_acAccelArray[1u]                                                   = 10u;

  //Step 3) Call the FUT

  AvacVdd_DetectVehicleDynamic();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,        1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,        3u, == );
  AL_UNITTEST_CHECK(UTIL_ABS_HitCount,                            2u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucDynState,                        0x01u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucAccIndex,                         128u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function prepares dynamic state and calculates acceleration index
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input   Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = 1u;
/// input   Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 700u;
/// input   Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
/// input   Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 20u;
/// input   Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                                = 2u;
/// input   Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;
/// input   AvacVdd_ucDynState                                                         = 0u;
/// input   AvacVdd_ucAccIndex                                                         = 0u;
/// input   UTIL_ABS_HitCount                                                          = 0u;
/// input   UTIL_ABS_RetVal                                                            = 2u;
/// input   AvacVdd_acAccelArray[0u]                                                   = 30u;
/// input   AvacVdd_acAccelArray[1u]                                                   = 10u;
///
/// - Expectations:
///
/// output Rte_Read_SysMon_VehicleSpeed_HitCount  =     1u
/// output Rte_Read_SigPrep_DynamicSigs_HitCount  =     3u
/// output UTIL_ABS_HitCount                      =     2u
/// output AvacVdd_ucDynState                     =  0x02u
/// output AvacVdd_ucAccIndex                     =   128u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = 1u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 700u;
  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 20u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                                = 2u;
  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;

  AvacVdd_ucDynState                                                         = 0u;
  AvacVdd_ucAccIndex                                                         = 0u;
  UTIL_ABS_HitCount                                                          = 0u;
  UTIL_ABS_RetVal                                                            = 2u;
  AvacVdd_acAccelArray[0u]                                                   = 30u;
  AvacVdd_acAccelArray[1u]                                                   = 10u;

  //Step 3) Call the FUT

  AvacVdd_DetectVehicleDynamic();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,        1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,        3u, == );
  AL_UNITTEST_CHECK(UTIL_ABS_HitCount,                            2u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucDynState,                        0x02u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucAccIndex,                         128u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function prepares dynamic state and calculates acceleration index
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = 1u;
/// input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 700u;
/// input  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
/// input  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 20u;
/// input  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                                = 2u;
/// input  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;
/// input  AvacVdd_ucDynState                                                         = 0u;
/// input  AvacVdd_ucAccIndex                                                         = 0u;
/// input  UTIL_ABS_HitCount                                                          = 0u;
/// input  UTIL_ABS_RetVal                                                            = 5u;
/// input  AvacVdd_acAccelArray[0u]                                                   = 30u;
/// input  AvacVdd_acAccelArray[1u]                                                   = 10u;
///
/// - Expectations:
///
/// output Rte_Read_SysMon_VehicleSpeed_HitCount  =    1u
/// output Rte_Read_SigPrep_DynamicSigs_HitCount  =    3u
/// output UTIL_ABS_HitCount                      =    2u
/// output AvacVdd_ucDynState                     =    0u
/// output AvacVdd_ucAccIndex                     =  128u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_6(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                                = 1u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed           = 700u;
  Rte_Read_SysMon_VehicleSpeed_HitCount                                      = 0u;
  Rte_Read_SigPrep_DynamicSigs_Param1.ePedalAcceleration.ucPedalAcceleration = 20u;
  Rte_Read_SigPrep_DynamicSigs_Param1.eSigQty                                = 2u;
  Rte_Read_SigPrep_DynamicSigs_HitCount                                      = 0u;
  AvacVdd_ucDynState                                                         = 0u;
  AvacVdd_ucAccIndex                                                         = 0u;
  UTIL_ABS_HitCount                                                          = 0u;
  UTIL_ABS_RetVal                                                            = 5u;
  AvacVdd_acAccelArray[0u]                                                   = 30u;
  AvacVdd_acAccelArray[1u]                                                   = 10u;

  //Step 3) Call the FUT

  AvacVdd_DetectVehicleDynamic();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value  

  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,        1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,        3u, == );
  AL_UNITTEST_CHECK(UTIL_ABS_HitCount,                            2u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucDynState,                           0u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucAccIndex,                         128u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacVdd_DetectStreetQuality_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function changes BadStreetIndex only at constant speed at rising signal
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  Rte_Read_Pitch_Angle_Param1.nAngle     = 2u;
/// input  Rte_Read_Pitch_Angle_HitCount          = 0u;
/// input  UTIL_ABS_HitCount                      = 0u;
/// input  UTIL_ABS_Param1                        = 0u;
/// input  UTIL_ABS_RetVal                        = 4u;
/// input  AvacVdd_ucDynState                     = 2u;
/// input  AvacVdd_ucBadStreetIndex               = 0u;
/// input  Order1Filter_HitCount                  = 0u;
/// input  Order1Filter_Param2                    = 0u;
/// input  Order1FilterValue_HitCount             = 0u;
/// input  Order1FilterValue_RetVal               = 1u;
///
/// - Expectations:
///
/// output Rte_Read_Pitch_Angle_HitCount  =  1u
/// output UTIL_ABS_HitCount              =  1u
/// output UTIL_ABS_Param1                =  1u
/// output Order1Filter_HitCount          =  2u
/// output Order1Filter_Param2            =  2u
/// output Order1FilterValue_HitCount     =  3u
/// output AvacVdd_ucBadStreetIndex       =  1u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacVdd_DetectStreetQuality_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  
  Rte_Read_Pitch_Angle_Param1.nAngle     = 2u;
  Rte_Read_Pitch_Angle_HitCount          = 0u;
  UTIL_ABS_HitCount                      = 0u;
  UTIL_ABS_Param1                        = 0u;
  UTIL_ABS_RetVal                        = 4u;
  AvacVdd_ucDynState                     = 2u;
  AvacVdd_ucBadStreetIndex               = 0u;
  Order1Filter_HitCount                  = 0u;
  Order1Filter_Param2                    = 0u;
  Order1FilterValue_HitCount             = 0u;
  Order1FilterValue_RetVal               = 1u;

  //Step 3) Call the FUT

  AvacVdd_DetectStreetQuality();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Rte_Read_Pitch_Angle_HitCount,              1u, == );
  AL_UNITTEST_CHECK(UTIL_ABS_HitCount,                          1u, == );
  AL_UNITTEST_CHECK(UTIL_ABS_Param1,                            1u, == );
  AL_UNITTEST_CHECK(Order1Filter_HitCount,                      2u, == );
  AL_UNITTEST_CHECK(Order1Filter_Param2,                        2u, == );
  AL_UNITTEST_CHECK(Order1FilterValue_HitCount,                 3u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucBadStreetIndex,                   1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacVdd_DetectStreetQuality_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function changes BadStreetIndex only at constant speed at rising signal
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  Rte_Read_Pitch_Angle_Param1.nAngle     = 2u;
/// input  Rte_Read_Pitch_Angle_HitCount          = 0u;
/// input  UTIL_ABS_HitCount                      = 0u;
/// input  UTIL_ABS_Param1                        = 0u;
/// input  UTIL_ABS_RetVal                        = 4u;
/// input  AvacVdd_ucDynState                     = 2u;
/// input  AvacVdd_ucBadStreetIndex               = 0u;
/// input  Order1Filter_HitCount                  = 0u;
/// input  Order1Filter_Param2                    = 0u;
/// input  Order1FilterValue_HitCount             = 0u;
/// input  Order1FilterValue_RetVal               = 200u;
///
/// - Expectations:
///
/// output Rte_Read_Pitch_Angle_HitCount  =    1u
/// output UTIL_ABS_HitCount              =    1u
/// output UTIL_ABS_Param1                =  -198
/// output Order1Filter_HitCount          =    2u
/// output Order1Filter_Param2            =    2u
/// output Order1FilterValue_HitCount     =    3u
/// output AvacVdd_ucBadStreetIndex       =  128u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacVdd_DetectStreetQuality_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  
  Rte_Read_Pitch_Angle_Param1.nAngle     = 2u;
  Rte_Read_Pitch_Angle_HitCount          = 0u;
  UTIL_ABS_HitCount                      = 0u;
  UTIL_ABS_Param1                        = 0u;
  UTIL_ABS_RetVal                        = 4u;
  AvacVdd_ucDynState                     = 2u;
  AvacVdd_ucBadStreetIndex               = 0u;
  Order1Filter_HitCount                  = 0u;
  Order1Filter_Param2                    = 0u;
  Order1FilterValue_HitCount             = 0u;
  Order1FilterValue_RetVal               = 200u;

  //Step 3) Call the FUT

  AvacVdd_DetectStreetQuality();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Rte_Read_Pitch_Angle_HitCount,              1u, == );
  AL_UNITTEST_CHECK(UTIL_ABS_HitCount,                          1u, == );
  AL_UNITTEST_CHECK(UTIL_ABS_Param1,                          -198, == );
  AL_UNITTEST_CHECK(Order1Filter_HitCount,                      2u, == );
  AL_UNITTEST_CHECK(Order1Filter_Param2,                        2u, == );
  AL_UNITTEST_CHECK(Order1FilterValue_HitCount,                 3u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucBadStreetIndex,                 128u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacVdd_DetectStreetQuality_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function changes BadStreetIndex only at constant speed
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  Rte_Read_Pitch_Angle_Param1.nAngle     = 2u;
/// input  Rte_Read_Pitch_Angle_HitCount          = 0u;
/// input  UTIL_ABS_HitCount                      = 0u;
/// input  UTIL_ABS_Param1                        = 0u;
/// input  UTIL_ABS_RetVal                        = 4u;
/// input  AvacVdd_ucDynState                     = 0u;
/// input  AvacVdd_ucBadStreetIndex               = 0u;
/// input  Order1Filter_HitCount                  = 0u;
/// input  Order1Filter_Param2                    = 0u;
/// input  Order1FilterValue_HitCount             = 0u;
/// input  Order1FilterValue_RetVal               = 200u;
///
/// - Expectations:
///
/// output Rte_Read_Pitch_Angle_HitCount  =    1u
/// output UTIL_ABS_HitCount              =    1u
/// output UTIL_ABS_Param1                =  -198
/// output Order1Filter_HitCount          =    1u
/// output Order1Filter_Param2            =    2u
/// output Order1FilterValue_HitCount     =    1u
/// output AvacVdd_ucBadStreetIndex       =    0u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacVdd_DetectStreetQuality_TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  
  Rte_Read_Pitch_Angle_Param1.nAngle     = 2u;
  Rte_Read_Pitch_Angle_HitCount          = 0u;
  UTIL_ABS_HitCount                      = 0u;
  UTIL_ABS_Param1                        = 0u;
  UTIL_ABS_RetVal                        = 4u;
  AvacVdd_ucDynState                     = 0u;
  AvacVdd_ucBadStreetIndex               = 0u;
  Order1Filter_HitCount                  = 0u;
  Order1Filter_Param2                    = 0u;
  Order1FilterValue_HitCount             = 0u;
  Order1FilterValue_RetVal               = 200u;

  //Step 3) Call the FUT

  AvacVdd_DetectStreetQuality();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Rte_Read_Pitch_Angle_HitCount,              1u, == );
  AL_UNITTEST_CHECK(UTIL_ABS_HitCount,                          1u, == );
  AL_UNITTEST_CHECK(UTIL_ABS_Param1,                          -198, == );
  AL_UNITTEST_CHECK(Order1Filter_HitCount,                      1u, == );
  AL_UNITTEST_CHECK(Order1Filter_Param2,                        2u, == );
  AL_UNITTEST_CHECK(Order1FilterValue_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucBadStreetIndex,                   0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacVdd_Init_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  TBD... Empty function
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  Order1FilterGetCoef_RetVal = 12u;
/// input  Order1FilterGetCoef_HitCount = 0u;
///
/// - Expectations:
///
/// output AvacVdd_unAccelFilterCoef           = 12u
/// output AvacVdd_unBadStreetHPFilterCoef     = 12u
/// output AvacVdd_unBadStreetLPFilterCoefRise = 12u
/// output AvacVdd_unBadStreetLPFilterCoefFall = 12u
/// output Order1FilterGetCoef_HitCount        = 4u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacVdd_Init_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  
  Order1FilterGetCoef_RetVal = 12u;
  Order1FilterGetCoef_HitCount = 0u;

  //Step 3) Call the FUT

  AvacVdd_Init();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
 
  AL_UNITTEST_CHECK(AvacVdd_unAccelFilterCoef, 12u, == );
  AL_UNITTEST_CHECK(AvacVdd_unBadStreetHPFilterCoef, 12u, == );
  AL_UNITTEST_CHECK(AvacVdd_unBadStreetLPFilterCoefRise, 12u, == );
  AL_UNITTEST_CHECK(AvacVdd_unBadStreetLPFilterCoefFall, 12u, == );
  AL_UNITTEST_CHECK(Order1FilterGetCoef_HitCount, 4u, == );
}


/*AvacAlgDyn1.c*/

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_GetAutoAngle__TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function reads auto angle from blackboard and check signal state
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  Rte_Read_Pitch_Angle_Param1.nAngle     = 30u;
/// input  Rte_Read_Pitch_Angle_Param1.eSigQty    = 1u;
/// input  Rte_Read_Pitch_Angle_HitCount          = 0u;
/// input  AvacData_boPitchConfigValid            = 1u;
/// input  Avac_nAutoAngle                        = 0u;
///
/// - Expectations:
///
/// output Rte_Read_Pitch_Angle_HitCount  =  1u
/// output Avac_nAutoAngle                = 30u
///
//-----------------------------------------------------------------------------
void Mt_Avac_GetAutoAngle__TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  Rte_Read_Pitch_Angle_Param1.nAngle     = 30u;
  Rte_Read_Pitch_Angle_Param1.eSigQty    = 1u;
  Rte_Read_Pitch_Angle_HitCount          = 0u;
  AvacData_boPitchConfigValid            = 1u;
  Avac_nAutoAngle                        = 0u;

  //Step 3) Call the FUT

  GetAutoAngle_();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Rte_Read_Pitch_Angle_HitCount,           1u, == );
  AL_UNITTEST_CHECK(Avac_nAutoAngle,                        30u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_GetAutoAngle__TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function reads auto angle from blackboard and check signal state
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  Rte_Read_Pitch_Angle_Param1.nAngle     = 30u;
/// input  Rte_Read_Pitch_Angle_Param1.eSigQty    = 1u;
/// input  Rte_Read_Pitch_Angle_HitCount          = 0u;
/// input  AvacData_boPitchConfigValid            = 0u;
/// input  Avac_nAutoAngle                        = 0u;
///
/// - Expectations:
///
/// output Rte_Read_Pitch_Angle_HitCount  =  1u
/// output Avac_nAutoAngle                =  0u
///
//-----------------------------------------------------------------------------
void Mt_Avac_GetAutoAngle__TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  Rte_Read_Pitch_Angle_Param1.nAngle     = 30u;
  Rte_Read_Pitch_Angle_Param1.eSigQty    = 1u;
  Rte_Read_Pitch_Angle_HitCount          = 0u;
  AvacData_boPitchConfigValid            = 0u;
  Avac_nAutoAngle                        = 0u;

  //Step 3) Call the FUT

  GetAutoAngle_();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Rte_Read_Pitch_Angle_HitCount,           1u, == );
  AL_UNITTEST_CHECK(Avac_nAutoAngle,                         0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_DoStaticRegulation__TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function calculates static headlight angle
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacVdd_ucDynState             = 0x02u;
/// input  AvacData_ucGradientLimiterDown = 1u;
/// input  Avac_nStaticAngle              = 0u;
/// input  Order1Filter_HitCount          = 0u;
///
/// - Expectations:
///
/// output Order1Filter_HitCoun  =  1u
///
//-----------------------------------------------------------------------------
void Mt_Avac_DoStaticRegulation__TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacVdd_ucDynState             = 0x02u;
  AvacData_ucGradientLimiterDown = 1u;
  Avac_nStaticAngle              = 0u;
  Order1Filter_HitCount          = 0u;

  //Step 3) Call the FUT

  DoStaticRegulation_();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Order1Filter_HitCount,        1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_DoStaticRegulation__TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function calculates static headlight angle
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacVdd_ucDynState             = 0x02u;
/// input  AvacData_ucGradientLimiterDown = 10u;
/// input  Avac_nStaticAngle              = 0u;
/// input  Order1Filter_HitCount          = 0u;
///
/// - Expectations:
///
/// output Order1Filter_HitCoun  =  1u
///
//-----------------------------------------------------------------------------
void Mt_Avac_DoStaticRegulation__TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacVdd_ucDynState             = 0x02u;
  AvacData_ucGradientLimiterDown = 10u;
  Avac_nStaticAngle              = 0u;
  Order1Filter_HitCount          = 0u;

  //Step 3) Call the FUT

  DoStaticRegulation_();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Order1Filter_HitCount,        1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_DoStaticRegulation__TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function calculates static headlight angle
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacVdd_ucDynState             = 0x02u;
/// input  AvacData_ucGradientLimiterDown = 10u;
/// input  Avac_nStaticAngle              = 0u;
/// input  Order1Filter_HitCount          = 0u;
///
/// - Expectations:
///
/// output Order1Filter_HitCount  =  48u
///
//-----------------------------------------------------------------------------
void Mt_Avac_DoStaticRegulation__TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacVdd_ucDynState             = 0x02u;
  AvacData_ucGradientLimiterDown = 10u;
  Avac_nStaticAngle              = 0u;
  Order1Filter_HitCount          = 0u;

  //Step 3) Call the FUT

  for (uint8 ucIdx = 0u; ucIdx < 48; ucIdx++)
  {
    DoStaticRegulation_();
  }

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Order1Filter_HitCount,       48u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_DoStaticRegulation__TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function calculates static headlight angle
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacVdd_ucDynState             = 0u;
/// input  AvacData_ucGradientLimiterDown = 10u;
/// input  Avac_nStaticAngle              = 0u;
/// input  Order1Filter_HitCount          = 0u;
///
/// - Expectations:
///
/// output Order1Filter_HitCount  =  0u
///
//-----------------------------------------------------------------------------
void Mt_Avac_DoStaticRegulation__TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacVdd_ucDynState             = 0u;
  AvacData_ucGradientLimiterDown = 10u;
  Avac_nStaticAngle              = 0u;
  Order1Filter_HitCount          = 0u;

  //Step 3) Call the FUT

  for (uint8 ucIdx = 0u; ucIdx < 206; ucIdx++)
  {
    DoStaticRegulation_();
  }

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Order1Filter_HitCount,      0, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_SetDynamicIndex__TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function calculates dynamic index
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacData_boUseDynamicLeveling = 1u;
/// input  AvacVdd_ucDynState            = 1u;
/// input  Avac_ucDynamicIndex           = 0u;
/// input  Avac_cDynamicIndexCtr         = 0u;
///
/// - Expectations:
///
/// output Avac_ucDynamicIndex    =  128u
/// output Avac_cDynamicIndexCtr  =   30u
///
//-----------------------------------------------------------------------------
void Mt_Avac_SetDynamicIndex__TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_boUseDynamicLeveling = 1u;
  AvacVdd_ucDynState            = 1u;
  Avac_ucDynamicIndex           = 0u;
  Avac_cDynamicIndexCtr         = 0u;

  //Step 3) Call the FUT

  SetDynamicIndex_();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Avac_ucDynamicIndex,        128u, == );
  AL_UNITTEST_CHECK(Avac_cDynamicIndexCtr,       30u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_SetDynamicIndex__TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function calculates dynamic index
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacData_boUseDynamicLeveling = 0u;
/// input  AvacVdd_ucDynState            = 0u;
/// input  Avac_ucDynamicIndex           = 10u;
/// input  Avac_cDynamicIndexCtr         = 0u;
///
/// - Expectations:
///
/// output Avac_ucDynamicIndex    =  7u
/// output Avac_cDynamicIndexCtr  =  -1
///
//-----------------------------------------------------------------------------
void Mt_Avac_SetDynamicIndex__TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_boUseDynamicLeveling = 0u;
  AvacVdd_ucDynState            = 0u;
  Avac_ucDynamicIndex           = 10u;
  Avac_cDynamicIndexCtr         = 0u;

  //Step 3) Call the FUT

  SetDynamicIndex_();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Avac_ucDynamicIndex,          7u, == );
  AL_UNITTEST_CHECK(Avac_cDynamicIndexCtr,        -1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_SetDynamicIndex__TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function calculates dynamic index
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input   AvacData_boUseDynamicLeveling = 0u;
/// input   AvacVdd_ucDynState            = 0u;
/// input   Avac_ucDynamicIndex           = 10u;
/// input   Avac_cDynamicIndexCtr         = 0u;
///
/// - Expectations:
///
/// output Avac_ucDynamicIndex    =  10u
/// output Avac_cDynamicIndexCtr  =   -1
///
//-----------------------------------------------------------------------------
void Mt_Avac_SetDynamicIndex__TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_boUseDynamicLeveling = 0u;
  AvacVdd_ucDynState            = 0u;
  Avac_ucDynamicIndex           = 10u;
  Avac_cDynamicIndexCtr         = 0u;

  //Step 3) Call the FUT

  SetDynamicIndex_();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Avac_ucDynamicIndex,         10u, == );
  AL_UNITTEST_CHECK(Avac_cDynamicIndexCtr,        -1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_SetDynamicIndex__TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function calculates dynamic index
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input   AvacData_boUseDynamicLeveling = 0u;
/// input   AvacVdd_ucDynState            = 0u;
/// input   Avac_ucDynamicIndex           = 2u;
/// input   Avac_cDynamicIndexCtr         = 0u;
///
/// - Expectations:
///
/// output Avac_ucDynamicIndex    =  0u
/// output Avac_cDynamicIndexCtr  =  -1
///
//-----------------------------------------------------------------------------
void Mt_Avac_SetDynamicIndex__TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_boUseDynamicLeveling = 0u;
  AvacVdd_ucDynState            = 0u;
  Avac_ucDynamicIndex           = 2u;
  Avac_cDynamicIndexCtr         = 0u;

  //Step 3) Call the FUT

  SetDynamicIndex_();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Avac_ucDynamicIndex,          0u, == );
  AL_UNITTEST_CHECK(Avac_cDynamicIndexCtr,        -1, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_SetDynamicIndex__TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function calculates dynamic index
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input   AvacData_boUseDynamicLeveling = 0u;
/// input   AvacVdd_ucDynState            = 0u;
/// input   Avac_ucDynamicIndex           = 0u;
/// input   Avac_cDynamicIndexCtr         = 0u;
///
/// - Expectations:
///
/// output Avac_ucDynamicIndex    =  0u
/// output Avac_cDynamicIndexCtr  =  0u
///
//-----------------------------------------------------------------------------
void Mt_Avac_SetDynamicIndex__TestCase_5(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_boUseDynamicLeveling = 0u;
  AvacVdd_ucDynState            = 0u;
  Avac_ucDynamicIndex           = 0u;
  Avac_cDynamicIndexCtr         = 0u;

  //Step 3) Call the FUT

  SetDynamicIndex_();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Avac_ucDynamicIndex,          0u, == );
  AL_UNITTEST_CHECK(Avac_cDynamicIndexCtr,        0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_SetFilterTimeConstants__TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function calculates filter time constants for dynamic regulation
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  Avac_boMovingUp                                    = 1u;
/// input  Avac_nDynamicAngle                                 = -120;
/// input  AvacVdd_ucAccIndex                                 = 1u;
/// input  AvacVdd_ucBadStreetIndex                           = 110u;
/// input  AvacVdd_ucDynState                                 = 0x80u;
/// input  Avac_ucActualFilterTime                            = 0u;
/// input  AvacData_CodingData.AvacFilter.AvacStp_FilterUpMid = 14u;
///
/// - Expectations:
///
/// output Avac_ucActualFilterTime  =  14u
///
//-----------------------------------------------------------------------------
void Mt_Avac_SetFilterTimeConstants__TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  Avac_boMovingUp                                    = 1u;
  Avac_nDynamicAngle                                 = -120;
  AvacVdd_ucAccIndex                                 = 1u;
  AvacVdd_ucBadStreetIndex                           = 110u;
  AvacVdd_ucDynState                                 = 0x80u;
  Avac_ucActualFilterTime                            = 0u;
  AvacData_CodingData.AvacFilter.AvacStp_FilterUpMid = 14u;

  //Step 3) Call the FUT

  SetFilterTimeConstants_();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Avac_ucActualFilterTime,  14u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_SetFilterTimeConstants__TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function calculates filter time constants for dynamic regulation
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  Avac_boMovingUp                                    = 1u;
/// input  Avac_nDynamicAngle                                 = 0u;
/// input  AvacVdd_ucAccIndex                                 = 0xFFu;
/// input  AvacVdd_ucBadStreetIndex                           = 10u;
/// input  AvacVdd_ucDynState                                 = 0x04u;
/// input  Avac_ucActualFilterTime                            = 0u;
/// input  AvacData_CodingData.AvacFilter.AvacStp_FilterUpMax = 29u;
///
/// - Expectations:
///
/// output Avac_ucActualFilterTime  =  29u
///
//-----------------------------------------------------------------------------
void Mt_Avac_SetFilterTimeConstants__TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  Avac_boMovingUp                                    = 1u;
  Avac_nDynamicAngle                                 = 0u;
  AvacVdd_ucAccIndex                                 = 0xFFu;
  AvacVdd_ucBadStreetIndex                           = 10u;
  AvacVdd_ucDynState                                 = 0x04u;
  Avac_ucActualFilterTime                            = 0u;
  AvacData_CodingData.AvacFilter.AvacStp_FilterUpMax = 29u;

  //Step 3) Call the FUT

  SetFilterTimeConstants_();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Avac_ucActualFilterTime,  29u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_SetFilterTimeConstants__TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function calculates filter time constants for dynamic regulation
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  Avac_boMovingUp          = 0u;
/// input  Avac_nDynamicAngle       = 30u;
/// input  AvacVdd_ucAccIndex       = 0xFFu;
/// input  AvacVdd_ucBadStreetIndex = 10u;
/// input  AvacVdd_ucDynState       = 0x01u;
/// input  Avac_ucActualFilterTime  = 0u;
///
/// - Expectations:
///
/// output Avac_ucActualFilterTime  =  2u
///
//-----------------------------------------------------------------------------
void Mt_Avac_SetFilterTimeConstants__TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  Avac_boMovingUp          = 0u;
  Avac_nDynamicAngle       = 30u;
  AvacVdd_ucAccIndex       = 0xFFu;
  AvacVdd_ucBadStreetIndex = 10u;
  AvacVdd_ucDynState       = 0x01u;
  Avac_ucActualFilterTime  = 0u;
  

  //Step 3) Call the FUT

  SetFilterTimeConstants_();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Avac_ucActualFilterTime,  2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_SetFilterTimeConstants__TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function calculates filter time constants for dynamic regulation
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  Avac_boMovingUp                                      = 0u;
/// input  Avac_nDynamicAngle                                   = 10u;
/// input  AvacVdd_ucAccIndex                                   = 0xFFu;
/// input  AvacVdd_ucBadStreetIndex                             = 10u;
/// input  AvacVdd_ucDynState                                   = 0x01u;
/// input  Avac_ucActualFilterTime                              = 0u;
/// input  AvacData_CodingData.AvacFilter.AvacStp_FilterDownMax = 33u;
///
/// - Expectations:
///
/// output Avac_ucActualFilterTime  =  33u
///
//-----------------------------------------------------------------------------
void Mt_Avac_SetFilterTimeConstants__TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  Avac_boMovingUp          = 0u;
  Avac_nDynamicAngle       = 10u;
  AvacVdd_ucAccIndex       = 0xFFu;
  AvacVdd_ucBadStreetIndex = 10u;
  AvacVdd_ucDynState       = 0x01u;
  Avac_ucActualFilterTime  = 0u;
  AvacData_CodingData.AvacFilter.AvacStp_FilterDownMax = 33u;

  //Step 3) Call the FUT

  SetFilterTimeConstants_();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Avac_ucActualFilterTime,  33u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_DoDynamicRegulation__TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function calculates dynamic headlight angle
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  Avac_nAutoAngle            = 1u;
/// input  Avac_nStaticAngle          = -2;
/// input  Avac_nDynamicAngleGrad     = 0u;
/// input  Avac_nDynamicAngle         = -10u;
/// input  Avac_ucDynamicIndex        = 128u;
/// input  Avac_boMovingUp            = 0u;
/// input  Order1Filter_HitCount      = 0u;
/// input  Order1FilterValue_HitCount = 0u;
/// input  Order1FilterValue_RetVal   = 33u;
///
/// - Expectations:
///
/// output Order1Filter_HitCount       =   1u
/// output Order1FilterValue_HitCount  =   1u
/// output Avac_boMovingUp             =   1u
/// output Avac_nDynamicAngle          =  33u
///
//-----------------------------------------------------------------------------
void Mt_Avac_DoDynamicRegulation__TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  Avac_nAutoAngle            = 1u;
  Avac_nStaticAngle          = -2;
  Avac_nDynamicAngleGrad     = 0u;
  Avac_nDynamicAngle         = -10u;
  Avac_ucDynamicIndex        = 128u;
  Avac_boMovingUp            = 0u;
  Order1Filter_HitCount      = 0u;
  Order1FilterValue_HitCount = 0u;
  Order1FilterValue_RetVal   = 33u;

  //Step 3) Call the FUT

  DoDynamicRegulation_();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Order1Filter_HitCount,          1u, == );
  AL_UNITTEST_CHECK(Order1FilterValue_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Avac_boMovingUp,                1u, == );
  AL_UNITTEST_CHECK(Avac_nDynamicAngle,            33u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_DoDynamicRegulation__TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if function calculates dynamic headlight angle
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  Avac_nAutoAngle            = 1u;
/// input  Avac_nStaticAngle          = -2;
/// input  Avac_nDynamicAngleGrad     = 0u;
/// input  Avac_nDynamicAngle         = 10u;
/// input  Avac_ucDynamicIndex        = 128u;
/// input  Avac_boMovingUp            = 1u;
/// input  Order1Filter_HitCount      = 0u;
/// input  Order1FilterValue_HitCount = 0u;
/// input  Order1FilterValue_RetVal   = 33u;
///
/// - Expectations:
///
/// output Order1Filter_HitCount       =   1u
/// output Order1FilterValue_HitCount  =   1u
/// output Avac_boMovingUp             =   0u
/// output Avac_nDynamicAngle          =  33u
///
//-----------------------------------------------------------------------------
void Mt_Avac_DoDynamicRegulation__TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  Avac_nAutoAngle            = 1u;
  Avac_nStaticAngle          = -2;
  Avac_nDynamicAngleGrad     = 0u;
  Avac_nDynamicAngle         = 10u;
  Avac_ucDynamicIndex        = 128u;
  Avac_boMovingUp            = 1u;
  Order1Filter_HitCount      = 0u;
  Order1FilterValue_HitCount = 0u;
  Order1FilterValue_RetVal   = 33u;

  //Step 3) Call the FUT

  DoDynamicRegulation_();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Order1Filter_HitCount,          1u, == );
  AL_UNITTEST_CHECK(Order1FilterValue_HitCount,     1u, == );
  AL_UNITTEST_CHECK(Avac_boMovingUp,                0u, == );
  AL_UNITTEST_CHECK(Avac_nDynamicAngle,            33u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_CreateOutputSignal__TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test if function updats AngleSum only if Light is switched on
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacVdd_ucDynState   = 0x02u;
/// input  Avac_nStaticAngle    = -1000;
/// input  Avac_nDynamicAngle   = -1000;
/// input  Avac_nAngleSum       = -2100;
///
/// - Expectations:
///
/// output Avac_nAngleSum  =  -875
///
//-----------------------------------------------------------------------------
void Mt_Avac_CreateOutputSignal__TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacVdd_ucDynState   = 0x02u;
  Avac_nStaticAngle    = -1000;
  Avac_nDynamicAngle   = -1000;
  Avac_nAngleSum       = -2100;

  //Step 3) Call the FUT

  CreateOutputSignal_();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Avac_nAngleSum,  -875, == )
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_CreateOutputSignal__TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test if function updats AngleSum only if Light is switched on
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input  AvacVdd_ucDynState   = 0u;
/// input  Avac_nStaticAngle    = 1000;
/// input  Avac_nDynamicAngle   = 1000;
/// input  Avac_nAngleSum       = 3000;
///
/// - Expectations:
///
/// output Avac_nAngleSum  =  875
///
//-----------------------------------------------------------------------------
void Mt_Avac_CreateOutputSignal__TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacVdd_ucDynState   = 0u;
  Avac_nStaticAngle    = 1000;
  Avac_nDynamicAngle   = 1000;
  Avac_nAngleSum       = 3000;

  //Step 3) Call the FUT

  CreateOutputSignal_();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Avac_nAngleSum,  875, == )
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_CreateOutputSignal__TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test if function updats AngleSum only if Light is switched on
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input AvacVdd_ucDynState   = 0u;
/// input Avac_nStaticAngle    = 1000;
/// input Avac_nDynamicAngle   = 1000;
/// input Avac_nAngleSum       = 3000;
/// input AvacData_boLowBeamOn = FALSE;
///
/// - Expectations:
///
/// output Avac_nAngleSum  =  Avac_nStaticAngle
///
//-----------------------------------------------------------------------------
void Mt_Avac_CreateOutputSignal__TestCase_3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacVdd_ucDynState   = 0u;
  Avac_nStaticAngle    = 1000;
  Avac_nDynamicAngle   = 1000;
  Avac_nAngleSum       = 3000;
  AvacData_boLowBeamOn = FALSE;

  //Step 3) Call the FUT

  CreateOutputSignal_();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Avac_nAngleSum, Avac_nStaticAngle, == )
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_CreateOutputSignal__TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test if function updats AngleSum only if Light is switched on
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input AvacVdd_ucDynState   = 0u;
/// input Avac_nStaticAngle    = 1000;
/// input Avac_nDynamicAngle   = 1000;
/// input Avac_nAngleSum       = 3000;
/// input AvacData_boLowBeamOn = FALSE;
///
/// - Expectations:
///
/// output Avac_nAngleSum  =  3000
///
//-----------------------------------------------------------------------------
void Mt_Avac_CreateOutputSignal__TestCase_4(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacVdd_ucDynState   = 0u;
  Avac_nStaticAngle    = 1000;
  Avac_nDynamicAngle   = 1000;
  Avac_nAngleSum       = 3000;
  AvacData_boLowBeamOn = FALSE;

  //Step 3) Call the FUT

  CreateOutputSignal_();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Avac_nAngleSum, 3000, == )
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacAlg_Main_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test if Avac calls main function
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input Rte_Read_Pitch_Angle_Param1.nAngle     = 30u;
/// input Rte_Read_Pitch_Angle_Param1.eSigQty    = 1u;
/// input Rte_Read_Pitch_Angle_HitCount          = 0u;
/// input AvacData_boPitchConfigValid            = 1u;
/// input Avac_nAutoAngle                        = 0u;;
/// input Avac_AngleQty                          = 1u;
/// input AvacData_boUseDynamicLeveling          = 1u;
/// input AvacVdd_ucDynState                     = 1u;
/// input Avac_ucDynamicIndex                    = 0u;
/// input Avac_cDynamicIndexCtr                  = 0u;;
/// input Avac_nStaticAngle                      = -2;
/// input Avac_nDynamicAngleGrad                 = 0u;
/// input Avac_nDynamicAngle                     = -10u;
/// input Avac_boMovingUp                        = 0u;
/// input Order1Filter_HitCount                  = 0u;;
/// input Order1FilterValue_HitCount             = 0u;
/// input Order1FilterValue_RetVal               = 33u;
/// input Avac_nAngleSum                         = -2100;
///
/// - Expectations:
///
/// output Rte_Read_Pitch_Angle_HitCount  =    1u
/// output Avac_nAutoAngle                =   30u
/// output Avac_ucDynamicIndex            =  128u
/// output Avac_cDynamicIndexCtr          =   30u
/// output Order1Filter_HitCount          =    1u
/// output Order1FilterValue_HitCount     =    1u
/// output Avac_boMovingUp                =    0u
/// output Avac_nDynamicAngle             =   33u
/// output Avac_nAngleSum                 =    31
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacAlg_Main_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  
  Rte_Read_Pitch_Angle_Param1.nAngle     = 30u;
  Rte_Read_Pitch_Angle_Param1.eSigQty    = 1u;
  Rte_Read_Pitch_Angle_HitCount          = 0u;
  AvacData_boPitchConfigValid            = 1u;
  Avac_nAutoAngle                        = 0u;
  Avac_AngleQty                          = 1u;
  AvacData_boUseDynamicLeveling          = 1u;
  AvacVdd_ucDynState                     = 1u;
  Avac_ucDynamicIndex                    = 0u;
  Avac_cDynamicIndexCtr                  = 0u;
  Avac_nStaticAngle                      = -2;
  Avac_nDynamicAngleGrad                 = 0u;
  Avac_nDynamicAngle                     = -10u;
  Avac_boMovingUp                        = 0u;
  Order1Filter_HitCount                  = 0u;
  Order1FilterValue_HitCount             = 0u;
  Order1FilterValue_RetVal               = 33u;
  Avac_nAngleSum                         = -2100;

  //Step 3) Call the FUT

  AvacAlg_Main();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  
  AL_UNITTEST_CHECK(Rte_Read_Pitch_Angle_HitCount,           1u, == );
  AL_UNITTEST_CHECK(Avac_nAutoAngle,                        30u, == );
  AL_UNITTEST_CHECK(Avac_ucDynamicIndex,                   128u, == );
  AL_UNITTEST_CHECK(Avac_cDynamicIndexCtr,                  30u, == );
  AL_UNITTEST_CHECK(Order1Filter_HitCount,                   1u, == );
  AL_UNITTEST_CHECK(Order1FilterValue_HitCount,              1u, == );
  AL_UNITTEST_CHECK(Avac_boMovingUp,                         0u, == );
  AL_UNITTEST_CHECK(Avac_nDynamicAngle,                     33u, == );
  AL_UNITTEST_CHECK(Avac_nAngleSum,                          31, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacAlg_Main_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test if Avac calls main function
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input Rte_Read_Pitch_Angle_Param1.nAngle     = 30u;
/// input Rte_Read_Pitch_Angle_Param1.eSigQty    = 1u;
/// input Rte_Read_Pitch_Angle_HitCount          = 0u;
/// input AvacData_boPitchConfigValid            = 0u;
/// input Avac_nAutoAngle                        = 0u;
/// input Avac_AngleQty                          = 2u;
/// input AvacData_boUseDynamicLeveling          = 1u;
/// input AvacVdd_ucDynState                     = 1u;
/// input Avac_ucDynamicIndex                    = 0u;
/// input Avac_cDynamicIndexCtr                  = 0u;
/// input Avac_nStaticAngle                      = -2;
/// input Avac_nDynamicAngleGrad                 = 0u;
/// input Avac_nDynamicAngle                     = -10u;
/// input Avac_boMovingUp                        = 0u;
/// input Order1Filter_HitCount                  = 0u;
/// input Order1FilterValue_HitCount             = 0u;
/// input Order1FilterValue_RetVal               = 33u;
///
/// - Expectations:
///
/// output Rte_Read_Pitch_Angle_HitCount  =  1u
/// output Avac_nAutoAngle,               =  0u
/// output Avac_ucDynamicIndex,           =  0u
/// output Avac_cDynamicIndexCtr,         =  0u
/// output Order1Filter_HitCount,         =  0u
/// output Order1FilterValue_HitCount,    =  0u
/// output Avac_boMovingUp,               =  0u
/// output Avac_nDynamicAngle,            =  -10
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacAlg_Main_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  
  Rte_Read_Pitch_Angle_Param1.nAngle     = 30u;
  Rte_Read_Pitch_Angle_Param1.eSigQty    = 1u;
  Rte_Read_Pitch_Angle_HitCount          = 0u;
  AvacData_boPitchConfigValid            = 0u;
  Avac_nAutoAngle                        = 0u;
  Avac_AngleQty                          = 2u;
  AvacData_boUseDynamicLeveling          = 1u;
  AvacVdd_ucDynState                     = 1u;
  Avac_ucDynamicIndex                    = 0u;
  Avac_cDynamicIndexCtr                  = 0u;
  Avac_nStaticAngle                      = -2;
  Avac_nDynamicAngleGrad                 = 0u;
  Avac_nDynamicAngle                     = -10u;
  Avac_boMovingUp                        = 0u;
  Order1Filter_HitCount                  = 0u;
  Order1FilterValue_HitCount             = 0u;
  Order1FilterValue_RetVal               = 33u;

  //Step 3) Call the FUT

  AvacAlg_Main();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
  
  AL_UNITTEST_CHECK(Rte_Read_Pitch_Angle_HitCount,           1u, == );
  AL_UNITTEST_CHECK(Avac_nAutoAngle,                         0u, == );
  AL_UNITTEST_CHECK(Avac_ucDynamicIndex,                     0u, == );
  AL_UNITTEST_CHECK(Avac_cDynamicIndexCtr,                   0u, == );
  AL_UNITTEST_CHECK(Order1Filter_HitCount,                   0u, == );
  AL_UNITTEST_CHECK(Order1FilterValue_HitCount,              0u, == );
  AL_UNITTEST_CHECK(Avac_boMovingUp,                         0u, == );
  AL_UNITTEST_CHECK(Avac_nDynamicAngle,                     -10, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacAlg_Add_Main_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test if Avac calls main function
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input Avac_AngleQty                                      = 1u;
/// input Avac_boMovingUp                                    = 1u;
/// input Avac_nDynamicAngle                                 = -120;
/// input AvacVdd_ucAccIndex                                 = 1u;
/// input AvacVdd_ucBadStreetIndex                           = 110u;
/// input AvacVdd_ucDynState                                 = 0x80u;
/// input Avac_ucActualFilterTime                            = 0u;
/// input AvacData_ucGradientLimiterDown                     = 1u;
/// input Avac_nStaticAngle                                  = 0u;
/// input Order1Filter_HitCount                              = 0u;
/// input AvacData_CodingData.AvacFilter.AvacStp_FilterUpMid = 81u;
///
/// - Expectations:
///
/// outputAvac_ucActualFilterTime  =  81u
/// outputOrder1Filter_HitCount    =  1u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacAlg_Add_Main_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  
  Avac_AngleQty                                      = 1u;
  Avac_boMovingUp                                    = 1u;
  Avac_nDynamicAngle                                 = -120;
  AvacVdd_ucAccIndex                                 = 1u;
  AvacVdd_ucBadStreetIndex                           = 110u;
  AvacVdd_ucDynState                                 = 0x80u;
  Avac_ucActualFilterTime                            = 0u;
  AvacData_ucGradientLimiterDown                     = 1u;
  Avac_nStaticAngle                                  = 0u;
  Order1Filter_HitCount                              = 0u;
  AvacData_CodingData.AvacFilter.AvacStp_FilterUpMid = 81u;

  //Step 3) Call the FUT

  AvacAlg_Add_Main();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Avac_ucActualFilterTime,     81u, == );
  AL_UNITTEST_CHECK(Order1Filter_HitCount,        1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacAlg_Add_Main_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test if Avac calls main function
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input Avac_AngleQty                  = 2u;
/// input Avac_boMovingUp                = 1u;
/// input Avac_nDynamicAngle             = -120;
/// input AvacVdd_ucAccIndex             = 1u;
/// input AvacVdd_ucBadStreetIndex       = 110u;
/// input AvacVdd_ucDynState             = 0x80u;
/// input Avac_ucActualFilterTime        = 0u;
/// input AvacData_ucGradientLimiterDown = 1u;
/// input Avac_nStaticAngle              = 0u;
/// input Order1Filter_HitCount          = 0u;
/// input Order1Filter_Param3            = 0u;
///
/// - Expectations:
///
/// output Avac_ucActualFilterTime   =  0u
/// output Order1Filter_HitCount     =  0u
/// output Order1Filter_Param3       =  0u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacAlg_Add_Main_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT
  
  Avac_AngleQty                  = 2u;
  Avac_boMovingUp                = 1u;
  Avac_nDynamicAngle             = -120;
  AvacVdd_ucAccIndex             = 1u;
  AvacVdd_ucBadStreetIndex       = 110u;
  AvacVdd_ucDynState             = 0x80u;
  Avac_ucActualFilterTime        = 0u;
  AvacData_ucGradientLimiterDown = 1u;
  Avac_nStaticAngle              = 0u;
  Order1Filter_HitCount          = 0u;
  Order1Filter_Param3            = 0u;

  //Step 3) Call the FUT

  AvacAlg_Add_Main();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Avac_ucActualFilterTime,      0u, == );
  AL_UNITTEST_CHECK(Order1Filter_HitCount,        0u, == );
  AL_UNITTEST_CHECK(Order1Filter_Param3,          0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_AvacAlg_Init_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test if Avac calls main function
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input Avac_AngleQty             = 0u;
/// input Avac_nStaticAngle         = 10u;
/// input Avac_nStaticAngleGrad     = 10u;
/// input Order1FilterInit_HitCount = 0u;
/// input Order1FilterInit_Param2   = 10u;
///
/// - Expectations:
///
/// output Avac_AngleQty               =  1u
/// output Avac_nStaticAngle           =  0u
/// output Avac_nStaticAngleGrad       =  0u
/// output Order1FilterInit_HitCount   =  1u
/// output Order1FilterInit_Param2     =  0u
///
//-----------------------------------------------------------------------------
void Mt_Avac_AvacAlg_Init_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  Avac_AngleQty             = 0u;
  Avac_nStaticAngle         = 10u;
  Avac_nStaticAngleGrad     = 10u;
  Order1FilterInit_HitCount = 0u;
  Order1FilterInit_Param2   = 10u;

  //Step 3) Call the FUT

  AvacAlg_Init();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Avac_AngleQty,             1u, == );
  AL_UNITTEST_CHECK(Avac_nStaticAngle,         0u, == );
  AL_UNITTEST_CHECK(Avac_nStaticAngleGrad,     0u, == );
  AL_UNITTEST_CHECK(Order1FilterInit_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Order1FilterInit_Param2,   0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_reAppAvac_DeInit_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test if Avac calls init function
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input Avac_AngleQty  =  0u;
///
/// - Expectations:
///
/// output Avac_AngleQt  =  0u
///
//-----------------------------------------------------------------------------
void Mt_Avac_reAppAvac_DeInit_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  Avac_AngleQty = 0u;

  //Step 3) Call the FUT

  reAppAvac_DeInit();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Avac_AngleQty,  0u, == );
}

/*Avac.c*/

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_Avac_ParaChanged_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test if coding parameters changed
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input AvacData_boCodingValid    = 1u;
/// input Avac_AngleQty             = 0u;
/// input Avac_nStaticAngle         = 10u;
/// input Avac_nStaticAngleGrad     = 10u;
/// input Order1FilterInit_HitCount = 0u;
/// input Order1FilterInit_Param2   = 10u;
///
/// - Expectations:
///
/// output Avac_AngleQty               =  1u
/// output Avac_nStaticAngle           =  0u
/// output Avac_nStaticAngleGrad       =  0u
/// output Order1FilterInit_HitCount   =  1u
/// output Order1FilterInit_Param2     =  0u
///
//-----------------------------------------------------------------------------
void Mt_Avac_Avac_ParaChanged_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_boCodingValid    = 1u;
  Avac_AngleQty             = 0u;
  Avac_nStaticAngle         = 10u;
  Avac_nStaticAngleGrad     = 10u;
  Order1FilterInit_HitCount = 0u;
  Order1FilterInit_Param2   = 10u;

  //Step 3) Call the FUT

  Avac_ParaChanged();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Avac_AngleQty,             1u, == );
  AL_UNITTEST_CHECK(Avac_nStaticAngle,         0u, == );
  AL_UNITTEST_CHECK(Avac_nStaticAngleGrad,     0u, == );
  AL_UNITTEST_CHECK(Order1FilterInit_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Order1FilterInit_Param2,   0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_Avac_ParaChanged_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test if coding parameters changed
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input AvacData_boCodingValid    = 0u;
/// input Avac_AngleQty             = 0u;
/// input Avac_nStaticAngle         = 0u;
/// input Avac_nStaticAngleGrad     = 0u;
/// input Order1FilterInit_HitCount = 0u;
/// input Order1FilterInit_Param2   = 0u;
///
/// - Expectations:
///
/// output Avac_AngleQty               =  0u
/// output Avac_nStaticAngle           =  0u
/// output Avac_nStaticAngleGrad       =  0u
/// output Order1FilterInit_HitCount   =  0u
/// output Order1FilterInit_Param2     =  0u
///
//-----------------------------------------------------------------------------
void Mt_Avac_Avac_ParaChanged_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_boCodingValid    = 0u;
  Avac_AngleQty             = 0u;
  Avac_nStaticAngle         = 0u;
  Avac_nStaticAngleGrad     = 0u;
  Order1FilterInit_HitCount = 0u;
  Order1FilterInit_Param2   = 0u;

  //Step 3) Call the FUT

  Avac_ParaChanged();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Avac_AngleQty,             0u, == );
  AL_UNITTEST_CHECK(Avac_nStaticAngle,         0u, == );
  AL_UNITTEST_CHECK(Avac_nStaticAngleGrad,     0u, == );
  AL_UNITTEST_CHECK(Order1FilterInit_HitCount, 0u, == );
  AL_UNITTEST_CHECK(Order1FilterInit_Param2,   0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_Avac_Init_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test if coding parameters changed
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input AvacData_boCodingValid    = 1u;
/// input Avac_AngleQty             = 0u;
/// input Avac_nStaticAngle         = 10u;
/// input Avac_nStaticAngleGrad     = 10u;
/// input Order1FilterInit_HitCount = 0u;
/// input Order1FilterInit_Param2   = 10u;
///
/// - Expectations:
///
/// output Avac_AngleQty                =  1u
/// output Avac_nStaticAngle            =  0u
/// output Avac_nStaticAngleGrad        =  0u
/// output Order1FilterInit_HitCount    =  1u
/// output Order1FilterInit_Param2      =  0u
///
//-----------------------------------------------------------------------------
void Mt_Avac_Avac_Init_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_boCodingValid    = 1u;
  Avac_AngleQty             = 0u;
  Avac_nStaticAngle         = 10u;
  Avac_nStaticAngleGrad     = 10u;
  Order1FilterInit_HitCount = 0u;
  Order1FilterInit_Param2   = 10u;

  //Step 3) Call the FUT

  Avac_Init();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Avac_AngleQty,             1u, == );
  AL_UNITTEST_CHECK(Avac_nStaticAngle,         0u, == );
  AL_UNITTEST_CHECK(Avac_nStaticAngleGrad,     0u, == );
  AL_UNITTEST_CHECK(Order1FilterInit_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Order1FilterInit_Param2,   0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_Avac_Init_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test if coding parameters changed
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input AvacData_boCodingValid    =  0u;
/// input Avac_AngleQty             =  0u;
/// input Avac_nStaticAngle         =  0u;
/// input Avac_nStaticAngleGrad     =  0u;
/// input Order1FilterInit_HitCount =  0u;
/// input Order1FilterInit_Param2   =  0u;
///
/// - Expectations:
///
/// output Avac_AngleQty                =  0u
/// output Avac_nStaticAngle            =  0u
/// output Avac_nStaticAngleGrad        =  0u
/// output Order1FilterInit_HitCount    =  0u
/// output Order1FilterInit_Param2      =  0u
///
//-----------------------------------------------------------------------------
void Mt_Avac_Avac_Init_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_boCodingValid    = 0u;
  Avac_AngleQty             = 0u;
  Avac_nStaticAngle         = 0u;
  Avac_nStaticAngleGrad     = 0u;
  Order1FilterInit_HitCount = 0u;
  Order1FilterInit_Param2   = 0u;

  //Step 3) Call the FUT

  Avac_Init();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Avac_AngleQty,             0u, == );
  AL_UNITTEST_CHECK(Avac_nStaticAngle,         0u, == );
  AL_UNITTEST_CHECK(Avac_nStaticAngleGrad,     0u, == );
  AL_UNITTEST_CHECK(Order1FilterInit_HitCount, 0u, == );
  AL_UNITTEST_CHECK(Order1FilterInit_Param2,   0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_Avac_Cycle0_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test if cycle function is called
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input AvacData_boCodingValid                             = 1u;
/// input Rte_Read_Pitch_Angle_Param1.nAngle                 = 2u;
/// input Rte_Read_Pitch_Angle_HitCount                      = 0u;
/// input UTIL_ABS_HitCount                                  = 0u;
/// input UTIL_ABS_Param1                                    = 0u;
/// input UTIL_ABS_RetVal                                    = 4u;
/// input AvacVdd_ucDynState                                 = 2u;
/// input AvacVdd_ucBadStreetIndex                           = 0u;
/// input Order1Filter_HitCount                              = 0u;
/// input Order1Filter_Param2                                = 0u;
/// input Order1Filter_Param3                                = 0u;
/// input Order1FilterValue_HitCount                         = 0u;
/// input Order1FilterValue_RetVal                           = 1u;
/// input Avac_AngleQty                                      = 1u;
/// input Avac_boMovingUp                                    = 1u;
/// input Avac_nDynamicAngle                                 = -120;
/// input AvacVdd_ucAccIndex                                 = 1u;
/// input Avac_ucActualFilterTime                            = 0u;
/// input AvacData_ucGradientLimiterDown                     = 1u;
/// input Avac_nStaticAngle                                  = 0u;
/// input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty        = 3u;
/// input Rte_Read_SysMon_VehicleSpeed_HitCount              = 0u;
/// input Rte_Read_SigPrep_DynamicSigs_HitCount              = 0u;
/// input Rte_Read_Pitch_Angle_Param1.eSigQty                = 1u;
/// input AvacData_boPitchConfigValid                        = 1u;
/// input Avac_nAutoAngle                                    = 0u;
/// input AvacData_boUseDynamicLeveling                      = 1u;
/// input Avac_ucDynamicIndex                                = 0u;
/// input Avac_cDynamicIndexCtr                              = 0u;
/// input Avac_nDynamicAngleGrad                             = 0u;
/// input Avac_nAngleSum                                     = -2100;
/// input AvacData_CodingData.AvacFilter.AvacStp_FilterUpMin = 27u;
///
/// - Expectations:
///
/// output Rte_Read_Pitch_Angle_HitCount,            =     2u
/// output UTIL_ABS_HitCount,                        =     1u
/// output UTIL_ABS_Param1,                          =    -1u
/// output Order1Filter_HitCount,                    =     3u
/// output Order1Filter_Param2,                      =     0u
/// output Order1Filter_Param3,                      =     0u
/// output Order1FilterValue_HitCount,               =     4u
/// output AvacVdd_ucBadStreetIndex,                 =     1u
/// output Avac_ucActualFilterTime,                  =    27u
/// output Rte_Read_SysMon_VehicleSpeed_HitCount,    =     1u
/// output Rte_Read_SigPrep_DynamicSigs_HitCount,    =     3u
/// output AvacVdd_ucDynState,                       =  0x80u
/// output AvacVdd_ucAccIndex,                       =  0xFFu
/// output Avac_nAutoAngle,                          =     0u
/// output Avac_ucDynamicIndex,                      =     0u
/// output Avac_cDynamicIndexCtr,                    =     0u
/// output Avac_boMovingUp,                          =     1u
/// output Avac_nDynamicAngle,                       =   -120
/// output Avac_nAngleSum,                           =   -124
///
//-----------------------------------------------------------------------------
void Mt_Avac_Avac_Cycle0_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_boCodingValid                             = 1u;
  AvacData_CodingData.Modus.ucAvacStp_Enable         = 1u;
  Rte_Read_Pitch_Angle_Param1.nAngle                 = 2u;
  Rte_Read_Pitch_Angle_HitCount                      = 0u;
  UTIL_ABS_HitCount                                  = 0u;
  UTIL_ABS_Param1                                    = 0u;
  UTIL_ABS_RetVal                                    = 4u;
  AvacVdd_ucDynState                                 = 2u;
  AvacVdd_ucBadStreetIndex                           = 0u;
  Order1Filter_HitCount                              = 0u;
  Order1Filter_Param2                                = 0u;
  Order1Filter_Param3                                = 0u;
  Order1FilterValue_HitCount                         = 0u;
  Order1FilterValue_RetVal                           = 1u;
  Avac_AngleQty                                      = 1u;
  Avac_boMovingUp                                    = 1u;
  Avac_nDynamicAngle                                 = -120;
  AvacVdd_ucAccIndex                                 = 1u;
  Avac_ucActualFilterTime                            = 0u;
  AvacData_ucGradientLimiterDown                     = 1u;
  Avac_nStaticAngle                                  = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty        = 3u;
  Rte_Read_SysMon_VehicleSpeed_HitCount              = 0u;
  Rte_Read_SigPrep_DynamicSigs_HitCount              = 0u;
  Rte_Read_Pitch_Angle_Param1.eSigQty                = 1u;
  AvacData_boPitchConfigValid                        = 1u;
  Avac_nAutoAngle                                    = 0u;
  AvacData_boUseDynamicLeveling                      = 1u;
  Avac_ucDynamicIndex                                = 0u;
  Avac_cDynamicIndexCtr                              = 0u;
  Avac_nDynamicAngleGrad                             = 0u;
  Avac_nAngleSum                                     = -2100;
  AvacData_CodingData.AvacFilter.AvacStp_FilterUpMin = 27u;

  //Step 3) Call the FUT

  Avac_Cycle0();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Rte_Read_Pitch_Angle_HitCount,              2u, == );
  AL_UNITTEST_CHECK(UTIL_ABS_HitCount,                          1u, == );
  AL_UNITTEST_CHECK(UTIL_ABS_Param1,                           -1u, == );
  AL_UNITTEST_CHECK(Order1Filter_HitCount,                      3u, == );
  AL_UNITTEST_CHECK(Order1Filter_Param2,                        0u, == );
  AL_UNITTEST_CHECK(Order1Filter_Param3,                        0u, == );
  AL_UNITTEST_CHECK(Order1FilterValue_HitCount,                 4u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucBadStreetIndex,                   1u, == );
  AL_UNITTEST_CHECK(Avac_ucActualFilterTime,                   27u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,      1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,      3u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucDynState,                      0x80u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucAccIndex,                      0xFFu, == );
  AL_UNITTEST_CHECK(Avac_nAutoAngle,                            0u, == );
  AL_UNITTEST_CHECK(Avac_ucDynamicIndex,                        0u, == );
  AL_UNITTEST_CHECK(Avac_cDynamicIndexCtr,                      0u, == );
  AL_UNITTEST_CHECK(Avac_boMovingUp,                            1u, == );
  AL_UNITTEST_CHECK(Avac_nDynamicAngle,                       -120, == );
  AL_UNITTEST_CHECK(Avac_nAngleSum,                           -124, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_Avac_Cycle0_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test if cycle function is called
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input AvacData_boCodingValid                           = 0u;
/// input Rte_Read_Pitch_Angle_Param1.nAngle               = 2u;
/// input Rte_Read_Pitch_Angle_HitCount                    = 0u;
/// input UTIL_ABS_HitCount                                = 0u;
/// input UTIL_ABS_Param1                                  = 0u;
/// input UTIL_ABS_RetVal                                  = 4u;
/// input AvacVdd_ucDynState                               = 2u;
/// input AvacVdd_ucBadStreetIndex                         = 0u;
/// input Order1Filter_HitCount                            = 0u;
/// input Order1Filter_Param2                              = 0u;
/// input Order1Filter_Param3                              = 0u;
/// input Order1FilterValue_HitCount                       = 0u;
/// input Order1FilterValue_RetVal                         = 1u;
/// input Avac_AngleQty                                    = 1u;
/// input Avac_boMovingUp                                  = 1u;
/// input Avac_nDynamicAngle                               = -120;
/// input AvacVdd_ucAccIndex                               = 1u;
/// input Avac_ucActualFilterTime                          = 0u;
/// input AvacData_ucGradientLimiterDown                   = 1u;
/// input Avac_nStaticAngle                                = 0u;
/// input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty      = 3u;
/// input Rte_Read_SysMon_VehicleSpeed_HitCount            = 0u;
/// input Rte_Read_SigPrep_DynamicSigs_HitCount            = 0u;
/// input Rte_Read_Pitch_Angle_Param1.eSigQty              = 1u;
/// input AvacData_boPitchConfigValid                      = 1u;
/// input Avac_nAutoAngle                                  = 0u;
/// input AvacData_boUseDynamicLeveling                    = 1u;
/// input Avac_ucDynamicIndex                              = 0u;
/// input Avac_cDynamicIndexCtr                            = 0u;
/// input Avac_nDynamicAngleGrad                           = 0u;
/// input Avac_nAngleSum                                   = -2100;
///
/// - Expectations:
///
/// output Rte_Read_Pitch_Angle_HitCount,            =    0u
/// output UTIL_ABS_HitCount,                        =    0u
/// output UTIL_ABS_Param1,                          =    0u
/// output Order1Filter_HitCount,                    =    0u
/// output Order1Filter_Param2,                      =    0u
/// output Order1Filter_Param3,                      =    0u
/// output Order1FilterValue_HitCount,               =    0u
/// output AvacVdd_ucBadStreetIndex,                 =    0u
/// output Avac_ucActualFilterTime,                  =    0u
/// output Rte_Read_SysMon_VehicleSpeed_HitCount,    =    0u
/// output Rte_Read_SigPrep_DynamicSigs_HitCount,    =    0u
/// output AvacVdd_ucDynState,                       =    2u
/// output AvacVdd_ucAccIndex,                       =    1u
/// output Avac_nAutoAngle,                          =    0u
/// output Avac_ucDynamicIndex,                      =    0u
/// output Avac_cDynamicIndexCtr,                    =    0u
/// output Avac_boMovingUp,                          =    1u
/// output Avac_nDynamicAngle,                       =  -120
/// output Avac_nAngleSum,                           = -2100
///
//-----------------------------------------------------------------------------
void Mt_Avac_Avac_Cycle0_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_boCodingValid                           = 0u;
  Rte_Read_Pitch_Angle_Param1.nAngle               = 2u;
  Rte_Read_Pitch_Angle_HitCount                    = 0u;
  UTIL_ABS_HitCount                                = 0u;
  UTIL_ABS_Param1                                  = 0u;
  UTIL_ABS_RetVal                                  = 4u;
  AvacVdd_ucDynState                               = 2u;
  AvacVdd_ucBadStreetIndex                         = 0u;
  Order1Filter_HitCount                            = 0u;
  Order1Filter_Param2                              = 0u;
  Order1Filter_Param3                              = 0u;
  Order1FilterValue_HitCount                       = 0u;
  Order1FilterValue_RetVal                         = 1u;
  Avac_AngleQty                                    = 1u;
  Avac_boMovingUp                                  = 1u;
  Avac_nDynamicAngle                               = -120;
  AvacVdd_ucAccIndex                               = 1u;
  Avac_ucActualFilterTime                          = 0u;
  AvacData_ucGradientLimiterDown                   = 1u;
  Avac_nStaticAngle                                = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty      = 3u;
  Rte_Read_SysMon_VehicleSpeed_HitCount            = 0u;
  Rte_Read_SigPrep_DynamicSigs_HitCount            = 0u;
  Rte_Read_Pitch_Angle_Param1.eSigQty              = 1u;
  AvacData_boPitchConfigValid                      = 1u;
  Avac_nAutoAngle                                  = 0u;
  AvacData_boUseDynamicLeveling                    = 1u;
  Avac_ucDynamicIndex                              = 0u;
  Avac_cDynamicIndexCtr                            = 0u;
  Avac_nDynamicAngleGrad                           = 0u;
  Avac_nAngleSum                                   = -2100;

  //Step 3) Call the FUT

  Avac_Cycle0();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Rte_Read_Pitch_Angle_HitCount,              0u, == );
  AL_UNITTEST_CHECK(UTIL_ABS_HitCount,                          0u, == );
  AL_UNITTEST_CHECK(UTIL_ABS_Param1,                            0u, == );
  AL_UNITTEST_CHECK(Order1Filter_HitCount,                      0u, == );
  AL_UNITTEST_CHECK(Order1Filter_Param2,                        0u, == );
  AL_UNITTEST_CHECK(Order1Filter_Param3,                        0u, == );
  AL_UNITTEST_CHECK(Order1FilterValue_HitCount,                 0u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucBadStreetIndex,                   0u, == );
  AL_UNITTEST_CHECK(Avac_ucActualFilterTime,                    0u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,      0u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,      0u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucDynState,                         2u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucAccIndex,                         1u, == );
  AL_UNITTEST_CHECK(Avac_nAutoAngle,                            0u, == );
  AL_UNITTEST_CHECK(Avac_ucDynamicIndex,                        0u, == );
  AL_UNITTEST_CHECK(Avac_cDynamicIndexCtr,                      0u, == );
  AL_UNITTEST_CHECK(Avac_boMovingUp,                            1u, == );
  AL_UNITTEST_CHECK(Avac_nDynamicAngle,                       -120, == );
  AL_UNITTEST_CHECK(Avac_nAngleSum,                          -2100, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_Avac_CheckZeroLvl_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test if function reports dtc for zero lvl prog
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input NvmBlockDeltaPwmPara.ucZeroLevProg = 0x00u;
/// input Dem_SetEventStatus_Param1          = 0u;
/// input Dem_SetEventStatus_Param2          = 5u;
/// input Dem_SetEventStatus_HitCount        = 0u;
///
/// - Expectations:
///
/// output Dem_SetEventStatus_HitCount,     =                        1u
/// output Dem_SetEventStatus_Param1,       =             ZERO_LVL_PROG
/// output Dem_SetEventStatus_Param2,       =   DEM_EVENT_STATUS_FAILED
///
//-----------------------------------------------------------------------------
void Mt_Avac_Avac_CheckZeroLvl_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  NvmBlockDeltaPwmPara.ucZeroLevProg = 0x00u;
  Dem_SetEventStatus_Param1          = 0u;
  Dem_SetEventStatus_Param2          = 5u;
  Dem_SetEventStatus_HitCount        = 0u;

  //Step 3) Call the FUT

  Avac_CheckZeroLvl();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                       1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,              ZERO_LVL_PROG, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2,    DEM_EVENT_STATUS_FAILED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_Avac_CheckZeroLvl_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test if function reports dtc for zero lvl prog
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input NvmBlockDeltaPwmPara.ucZeroLevProg = 0xFFu;
/// input Dem_SetEventStatus_Param1          = 0u;
/// input Dem_SetEventStatus_Param2          = 5u;
/// input Dem_SetEventStatus_HitCount        = 0u;
///
/// - Expectations:
///
/// output Dem_SetEventStatus_HitCount,     =                        1u
/// output Dem_SetEventStatus_Param1,       =             ZERO_LVL_PROG
/// output Dem_SetEventStatus_Param2,       =   DEM_EVENT_STATUS_PASSED
///
//-----------------------------------------------------------------------------
void Mt_Avac_Avac_CheckZeroLvl_TestCase_2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  NvmBlockDeltaPwmPara.ucZeroLevProg = 0xFFu;
  Dem_SetEventStatus_Param1          = 0u;
  Dem_SetEventStatus_Param2          = 5u;
  Dem_SetEventStatus_HitCount        = 0u;

  //Step 3) Call the FUT

  Avac_CheckZeroLvl();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                       1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,              ZERO_LVL_PROG, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2,    DEM_EVENT_STATUS_PASSED, == );
}


/*ctaaAvac.c*/

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_riAvac_Init_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test if coding parameters changed
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input AvacData_boCodingValid    = 1u;
/// input Avac_AngleQty             = 0u;
/// input Avac_nStaticAngle         = 10u;
/// input Avac_nStaticAngleGrad     = 10u;
/// input Order1FilterInit_HitCount = 0u;
/// input Order1FilterInit_Param2   = 10u;
///
/// - Expectations:
///
/// output Avac_AngleQty,                  =  1u
/// output Avac_nStaticAngle,              =  0u
/// output Avac_nStaticAngleGrad,          =  0u
/// output Order1FilterInit_HitCount,      =  1u
/// output Order1FilterInit_Param2,        =  0u
///
//-----------------------------------------------------------------------------
void Mt_Avac_riAvac_Init_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_boCodingValid    = 1u;
  Avac_AngleQty             = 0u;
  Avac_nStaticAngle         = 10u;
  Avac_nStaticAngleGrad     = 10u;
  Order1FilterInit_HitCount = 0u;
  Order1FilterInit_Param2   = 10u;

  //Step 3) Call the FUT

  riAvac_Init();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Avac_AngleQty,             1u, == );
  AL_UNITTEST_CHECK(Avac_nStaticAngle,         0u, == );
  AL_UNITTEST_CHECK(Avac_nStaticAngleGrad,     0u, == );
  AL_UNITTEST_CHECK(Order1FilterInit_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Order1FilterInit_Param2,   0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Avac_rpAvac_Cycle0_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test if cycle function is called
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
/// input AvacData_boCodingValid                             = 1u;
/// input Rte_Read_Pitch_Angle_Param1.nAngle                 = 2u;
/// input Rte_Read_Pitch_Angle_HitCount                      = 0u;
/// input UTIL_ABS_HitCount                                  = 0u;
/// input UTIL_ABS_Param1                                    = 0u;
/// input UTIL_ABS_RetVal                                    = 4u;
/// input AvacVdd_ucDynState                                 = 2u;
/// input AvacVdd_ucBadStreetIndex                           = 0u;
/// input Order1Filter_HitCount                              = 0u;
/// input Order1Filter_Param2                                = 0u;
/// input Order1Filter_Param3                                = 0u;
/// input Order1FilterValue_HitCount                         = 0u;
/// input Order1FilterValue_RetVal                           = 1u;
/// input Avac_AngleQty                                      = 1u;
/// input Avac_boMovingUp                                    = 1u;
/// input Avac_nDynamicAngle                                 = -120;
/// input AvacVdd_ucAccIndex                                 = 1u;
/// input Avac_ucActualFilterTime                            = 0u;
/// input AvacData_ucGradientLimiterDown                     = 1u;
/// input Avac_nStaticAngle                                  = 0u;
/// input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty        = 3u;
/// input Rte_Read_SysMon_VehicleSpeed_HitCount              = 0u;
/// input Rte_Read_SigPrep_DynamicSigs_HitCount              = 0u;
/// input Rte_Read_Pitch_Angle_Param1.eSigQty                = 1u;
/// input AvacData_boPitchConfigValid                        = 1u;
/// input Avac_nAutoAngle                                    = 0u;
/// input AvacData_boUseDynamicLeveling                      = 1u;
/// input Avac_ucDynamicIndex                                = 0u;
/// input Avac_cDynamicIndexCtr                              = 0u;
/// input Avac_nDynamicAngleGrad                             = 0u;
/// input Avac_nAngleSum                                     = -2100;
/// input AvacData_CodingData.AvacFilter.AvacStp_FilterUpMin = 53u;
///
/// - Expectations:
///
/// output Rte_Read_Pitch_Angle_HitCount,            =      2u
/// output UTIL_ABS_HitCount,                        =      1u
/// output UTIL_ABS_Param1,                          =     -1u
/// output Order1Filter_HitCount,                    =      3u
/// output Order1Filter_Param2,                      =      0u
/// output Order1Filter_Param3,                      =      0u
/// output Order1FilterValue_HitCount,               =      4u
/// output AvacVdd_ucBadStreetIndex,                 =      1u
/// output Avac_ucActualFilterTime,                  =     53u
/// output Rte_Read_SysMon_VehicleSpeed_HitCount,    =      1u
/// output Rte_Read_SigPrep_DynamicSigs_HitCount,    =      3u
/// output AvacVdd_ucDynState,                       =   0x80u
/// output AvacVdd_ucAccIndex,                       =   0xFFu
/// output Avac_nAutoAngle,                          =      0u
/// output Avac_ucDynamicIndex,                      =      0u
/// output Avac_cDynamicIndexCtr,                    =      0u
/// output Avac_boMovingUp,                          =      1u
/// output Avac_nDynamicAngle,                       =    -120
/// output Avac_nAngleSum,                           =    -124
///
//-----------------------------------------------------------------------------
void Mt_Avac_rpAvac_Cycle0_TestCase_1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign all input values to the corresponding input variables identified in the FUT

  AvacData_boCodingValid                             = 1u;
  Rte_Read_Pitch_Angle_Param1.nAngle                 = 2u;
  Rte_Read_Pitch_Angle_HitCount                      = 0u;
  UTIL_ABS_HitCount                                  = 0u;
  UTIL_ABS_Param1                                    = 0u;
  UTIL_ABS_RetVal                                    = 4u;
  AvacVdd_ucDynState                                 = 2u;
  AvacVdd_ucBadStreetIndex                           = 0u;
  Order1Filter_HitCount                              = 0u;
  Order1Filter_Param2                                = 0u;
  Order1Filter_Param3                                = 0u;
  Order1FilterValue_HitCount                         = 0u;
  Order1FilterValue_RetVal                           = 1u;
  Avac_AngleQty                                      = 1u;
  Avac_boMovingUp                                    = 1u;
  Avac_nDynamicAngle                                 = -120;
  AvacVdd_ucAccIndex                                 = 1u;
  Avac_ucActualFilterTime                            = 0u;
  AvacData_ucGradientLimiterDown                     = 1u;
  Avac_nStaticAngle                                  = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty        = 3u;
  Rte_Read_SysMon_VehicleSpeed_HitCount              = 0u;
  Rte_Read_SigPrep_DynamicSigs_HitCount              = 0u;
  Rte_Read_Pitch_Angle_Param1.eSigQty                = 1u;
  AvacData_boPitchConfigValid                        = 1u;
  Avac_nAutoAngle                                    = 0u;
  AvacData_boUseDynamicLeveling                      = 1u;
  Avac_ucDynamicIndex                                = 0u;
  Avac_cDynamicIndexCtr                              = 0u;
  Avac_nDynamicAngleGrad                             = 0u;
  Avac_nAngleSum                                     = -2100;
  AvacData_CodingData.AvacFilter.AvacStp_FilterUpMin = 53u;

  //Step 3) Call the FUT

  rpAvac_Cycle0();

  //Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value

  AL_UNITTEST_CHECK(Rte_Read_Pitch_Angle_HitCount,              2u, == );
  AL_UNITTEST_CHECK(UTIL_ABS_HitCount,                          1u, == );
  AL_UNITTEST_CHECK(UTIL_ABS_Param1,                           -1u, == );
  AL_UNITTEST_CHECK(Order1Filter_HitCount,                      3u, == );
  AL_UNITTEST_CHECK(Order1Filter_Param2,                        0u, == );
  AL_UNITTEST_CHECK(Order1Filter_Param3,                        0u, == );
  AL_UNITTEST_CHECK(Order1FilterValue_HitCount,                 4u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucBadStreetIndex,                   1u, == );
  AL_UNITTEST_CHECK(Avac_ucActualFilterTime,                   53u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,      1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SigPrep_DynamicSigs_HitCount,      3u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucDynState,                      0x80u, == );
  AL_UNITTEST_CHECK(AvacVdd_ucAccIndex,                      0xFFu, == );
  AL_UNITTEST_CHECK(Avac_nAutoAngle,                            0u, == );
  AL_UNITTEST_CHECK(Avac_ucDynamicIndex,                        0u, == );
  AL_UNITTEST_CHECK(Avac_cDynamicIndexCtr,                      0u, == );
  AL_UNITTEST_CHECK(Avac_boMovingUp,                            1u, == );
  AL_UNITTEST_CHECK(Avac_nDynamicAngle,                       -120, == );
  AL_UNITTEST_CHECK(Avac_nAngleSum,                           -124, == );
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
  /*ctaaAvac.c*/
  ALUnitTest_AddFunction("Mt_Avac_riAvac_Init_TestCase_1" , Mt_Avac_riAvac_Init_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_rpAvac_Cycle0_TestCase_1" , Mt_Avac_rpAvac_Cycle0_TestCase_1);
  
  /*Avac.c*/
  ALUnitTest_AddFunction("Mt_Avac_Avac_ParaChanged_TestCase_1",                    Mt_Avac_Avac_ParaChanged_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_Avac_ParaChanged_TestCase_2",                    Mt_Avac_Avac_ParaChanged_TestCase_2);
  ALUnitTest_AddFunction("Mt_Avac_Avac_Init_TestCase_1",                           Mt_Avac_Avac_Init_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_Avac_Init_TestCase_2",                           Mt_Avac_Avac_Init_TestCase_2);
  ALUnitTest_AddFunction("Mt_Avac_Avac_Cycle0_TestCase_1",                         Mt_Avac_Avac_Cycle0_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_Avac_Cycle0_TestCase_2",                         Mt_Avac_Avac_Cycle0_TestCase_2);
  ALUnitTest_AddFunction("Mt_Avac_Avac_CheckZeroLvl_TestCase_1",                   Mt_Avac_Avac_CheckZeroLvl_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_Avac_CheckZeroLvl_TestCase_2",                   Mt_Avac_Avac_CheckZeroLvl_TestCase_2);
  
  /*AvacUtil.c*/
  ALUnitTest_AddFunction("Mt_Avac_AvacUtil_Order1FilterByRelTime_TestCase_1",      Mt_Avac_AvacUtil_Order1FilterByRelTime_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_AvacUtil_Order1FilterByRelTime_TestCase_2",      Mt_Avac_AvacUtil_Order1FilterByRelTime_TestCase_2);
  ALUnitTest_AddFunction("Mt_Avac_AvacUtil_Order1FilterByRelTime_TestCase_3",      Mt_Avac_AvacUtil_Order1FilterByRelTime_TestCase_3);
  ALUnitTest_AddFunction("Mt_Avac_AvacUtil_SignalLimiter_TestCase_1",              Mt_Avac_AvacUtil_SignalLimiter_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_AvacUtil_SignalLimiter_TestCase_2",              Mt_Avac_AvacUtil_SignalLimiter_TestCase_2);
  ALUnitTest_AddFunction("Mt_Avac_AvacUtil_SignalLimiter_TestCase_3",              Mt_Avac_AvacUtil_SignalLimiter_TestCase_3);
  ALUnitTest_AddFunction("Mt_Avac_AvacUtil_RateLimiter_TestCase_1",                Mt_Avac_AvacUtil_RateLimiter_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_AvacUtil_RateLimiter_TestCase_2",                Mt_Avac_AvacUtil_RateLimiter_TestCase_2);
  ALUnitTest_AddFunction("Mt_Avac_AvacUtil_RateLimiter_TestCase_3",                Mt_Avac_AvacUtil_RateLimiter_TestCase_3);
  
  /*AvacData.c*/
  ALUnitTest_AddFunction("Mt_Avac_AvacData_ParaFct0_TestCase_1",                   Mt_Avac_AvacData_ParaFct0_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_AvacData_ParaFct0_TestCase_2",                   Mt_Avac_AvacData_ParaFct0_TestCase_2);
  ALUnitTest_AddFunction("Mt_Avac_AvacData_Init_TestCase_1",                       Mt_Avac_AvacData_Init_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_AvacData_GetLowBeamOn_TestCase_1",               Mt_Avac_AvacData_GetLowBeamOn_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_AvacData_GetAvacS_Ok_TestCase_1",                Mt_Avac_AvacData_GetAvacS_Ok_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_AvacData_GetAvacS_En_TestCase_1",                Mt_Avac_AvacData_GetAvacS_En_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_AvacData_GetAvacD_Ok_TestCase_1",                Mt_Avac_AvacData_GetAvacD_Ok_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_AvacData_GetAvacD_En_TestCase_1",                Mt_Avac_AvacData_GetAvacD_En_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_AvacData_ReadPitch_TestCase_1",                  Mt_Avac_AvacData_ReadPitch_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_AvacData_ReadPitch_TestCase_2",                  Mt_Avac_AvacData_ReadPitch_TestCase_2);
  ALUnitTest_AddFunction("Mt_Avac_AvacData_ReadPitch_TestCase_3",                  Mt_Avac_AvacData_ReadPitch_TestCase_3);
  ALUnitTest_AddFunction("Mt_Avac_AvacData_ReadSpeed_TestCase_1",                  Mt_Avac_AvacData_ReadSpeed_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_AvacData_ReadAccelPreDetect_TestCase_1",         Mt_Avac_AvacData_ReadAccelPreDetect_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_AvacData_ReadBrakePreDetect_TestCase_1",         Mt_Avac_AvacData_ReadBrakePreDetect_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_AvacData_WriteAvacOut_TestCase_1",               Mt_Avac_AvacData_WriteAvacOut_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_AvacData_WriteAvacOut_TestCase_2",               Mt_Avac_AvacData_WriteAvacOut_TestCase_2);
  ALUnitTest_AddFunction("Mt_Avac_AvacData_WriteAvacOut_TestCase_3",               Mt_Avac_AvacData_WriteAvacOut_TestCase_3);
  ALUnitTest_AddFunction("Mt_Avac_AvacData_WriteAvacOut_TestCase_4",               Mt_Avac_AvacData_WriteAvacOut_TestCase_4);
  
  /*AvacVddAdvanced.c*/
  ALUnitTest_AddFunction("Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_1",        Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_2",        Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_2);
  ALUnitTest_AddFunction("Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_3",        Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_3);
  ALUnitTest_AddFunction("Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_4",        Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_4);
  ALUnitTest_AddFunction("Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_5",        Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_5);
  ALUnitTest_AddFunction("Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_6",        Mt_Avac_AvacVdd_DetectVehicleDynamic_TestCase_6);
  ALUnitTest_AddFunction("Mt_Avac_AvacVdd_DetectStreetQuality_TestCase_1",         Mt_Avac_AvacVdd_DetectStreetQuality_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_AvacVdd_DetectStreetQuality_TestCase_2",         Mt_Avac_AvacVdd_DetectStreetQuality_TestCase_2);
  ALUnitTest_AddFunction("Mt_Avac_AvacVdd_DetectStreetQuality_TestCase_3",         Mt_Avac_AvacVdd_DetectStreetQuality_TestCase_3);
  ALUnitTest_AddFunction("Mt_Avac_AvacVdd_Init_TestCase_1",                        Mt_Avac_AvacVdd_Init_TestCase_1);
  
  /*AvacAlgDyn1.c*/
  ALUnitTest_AddFunction("Mt_Avac_GetAutoAngle__TestCase_1",                       Mt_Avac_GetAutoAngle__TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_GetAutoAngle__TestCase_2",                       Mt_Avac_GetAutoAngle__TestCase_2);
  ALUnitTest_AddFunction("Mt_Avac_DoStaticRegulation__TestCase_1",                 Mt_Avac_DoStaticRegulation__TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_DoStaticRegulation__TestCase_2",                 Mt_Avac_DoStaticRegulation__TestCase_2);
  ALUnitTest_AddFunction("Mt_Avac_DoStaticRegulation__TestCase_3",                 Mt_Avac_DoStaticRegulation__TestCase_3);
  ALUnitTest_AddFunction("Mt_Avac_DoStaticRegulation__TestCase_4",                 Mt_Avac_DoStaticRegulation__TestCase_4);
  ALUnitTest_AddFunction("Mt_Avac_SetDynamicIndex__TestCase_1",                    Mt_Avac_SetDynamicIndex__TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_SetDynamicIndex__TestCase_2",                    Mt_Avac_SetDynamicIndex__TestCase_2);
  ALUnitTest_AddFunction("Mt_Avac_SetDynamicIndex__TestCase_3",                    Mt_Avac_SetDynamicIndex__TestCase_3);
  ALUnitTest_AddFunction("Mt_Avac_SetDynamicIndex__TestCase_4",                    Mt_Avac_SetDynamicIndex__TestCase_4);
  ALUnitTest_AddFunction("Mt_Avac_SetDynamicIndex__TestCase_5",                    Mt_Avac_SetDynamicIndex__TestCase_5);
  ALUnitTest_AddFunction("Mt_Avac_SetFilterTimeConstants__TestCase_1",             Mt_Avac_SetFilterTimeConstants__TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_SetFilterTimeConstants__TestCase_2",             Mt_Avac_SetFilterTimeConstants__TestCase_2);
  ALUnitTest_AddFunction("Mt_Avac_SetFilterTimeConstants__TestCase_3",             Mt_Avac_SetFilterTimeConstants__TestCase_3);
  ALUnitTest_AddFunction("Mt_Avac_SetFilterTimeConstants__TestCase_4",             Mt_Avac_SetFilterTimeConstants__TestCase_4);
  ALUnitTest_AddFunction("Mt_Avac_DoDynamicRegulation__TestCase_1",                Mt_Avac_DoDynamicRegulation__TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_DoDynamicRegulation__TestCase_2",                Mt_Avac_DoDynamicRegulation__TestCase_2);
  ALUnitTest_AddFunction("Mt_Avac_AvacAlg_Main_TestCase_1",                        Mt_Avac_AvacAlg_Main_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_AvacAlg_Main_TestCase_2",                        Mt_Avac_AvacAlg_Main_TestCase_2);
  ALUnitTest_AddFunction("Mt_Avac_AvacAlg_Add_Main_TestCase_1",                    Mt_Avac_AvacAlg_Add_Main_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_AvacAlg_Add_Main_TestCase_2",                    Mt_Avac_AvacAlg_Add_Main_TestCase_2);
  ALUnitTest_AddFunction("Mt_Avac_AvacAlg_Init_TestCase_1",                        Mt_Avac_AvacAlg_Init_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_reAppAvac_DeInit_TestCase_1",                    Mt_Avac_reAppAvac_DeInit_TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_CreateOutputSignal__TestCase_1",                 Mt_Avac_CreateOutputSignal__TestCase_1);
  ALUnitTest_AddFunction("Mt_Avac_CreateOutputSignal__TestCase_2",                 Mt_Avac_CreateOutputSignal__TestCase_2);
  ALUnitTest_AddFunction("Mt_Avac_CreateOutputSignal__TestCase_3",                 Mt_Avac_CreateOutputSignal__TestCase_3);
  ALUnitTest_AddFunction("Mt_Avac_CreateOutputSignal__TestCase_4",                 Mt_Avac_CreateOutputSignal__TestCase_4);
  }