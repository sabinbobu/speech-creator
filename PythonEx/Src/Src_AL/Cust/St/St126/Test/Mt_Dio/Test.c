////*****************************************************************************
//// (C) Automotive Lighting Reutlingen GmbH
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
/// \brief Module test of Dio
///
//-----------------------------------------------------------------------------
//=============================================================================
// Includes
//=============================================================================
// Standard unit test header
#include <ALUnitTest_UserInterface.h>

// Stub headers
// Headers of the unit test Module
#include "Test.h"

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dio_Init
///
/// \Test Case Description
///        - Test subject: Test if function initialize all global variables of the DIO module
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Initialize the dio configuration 
///
/// - Preconditions:
///
/// \input 
///
/// - Expectations:
///
/// \output 
///
//-----------------------------------------------------------------------------
void Mt_Dio_Init(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  //Step 3) Call FUT
  Dio_Init(NULL_PTR);
  //Step 4) Check expected output value

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dio_WriteChannel_TestCase1
///
/// \Test Case Description
///        - Test subject: Test if function sets the specified channel with the specified level
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Goes thorugh each element from channel mapping
///         Step2: Check if the channel id is equal with the wanted channel id
///         Step3: Take the port base value
///         Step4: Check if the level is STD_HIGH
///         Step5: Set or Clear output register
///
/// - Preconditions:
///
/// \input Dio_WriteChannel_Param1     = 1u
/// \input Dio_WriteChannel_Param2     = 1u
/// \input Dio_ChannelMap[1].Pin       = 1u
/// \input Dio_ChannelMap[1].ChannelId = Dio_WriteChannel_Param1
/// \input Dio_ChannelMap[1].PortBase  = PTA_BASE
/// \input PTA->PDOR                   = 0xFFFFFFFFU
///
/// - Expectations:
///
/// \output PTA->PSOR                  = 2u
///
//-----------------------------------------------------------------------------
void Mt_Dio_WriteChannel_TestCase1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values

  Dio_WriteChannel_Param1     = 1u;
  Dio_WriteChannel_Param2     = 1u;
  Dio_ChannelMap[1].Pin       = 1u;
  Dio_ChannelMap[1].ChannelId = Dio_WriteChannel_Param1;
  Dio_ChannelMap[1].PortBase  = PTA_BASE;
  PTA->PDOR                   = 0xFFFFFFFFU;

  //Step 3) Call FUT
  Dio_WriteChannel(Dio_WriteChannel_Param1, Dio_WriteChannel_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(PTA->PSOR, 2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dio_WriteChannel_TestCase2
///
/// \Test Case Description
///        - Test subject: Test if function sets the specified channel with the specified level
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Goes thorugh each element from channel mapping
///         Step2: Check if the channel id is equal with the wanted channel id
///         Step3: Take the port base value
///         Step4: Check if the level is STD_HIGH
///         Step5: Set or Clear output register
///
/// - Preconditions:
///
/// \input Dio_WriteChannel_Param1     = 1u
/// \input Dio_WriteChannel_Param2     = 3u
/// \input Dio_ChannelMap[1].Pin       = 1u
/// \input Dio_ChannelMap[1].ChannelId = 0xFFFFFFFFU
/// \input Dio_ChannelMap[1].PortBase  = PTA_BASE
/// \input PTA->PDOR                   = 0xFFFFFFFFU
///
/// - Expectations:
///
/// \output PTA->PCOR                  = 0u
///
//-----------------------------------------------------------------------------
void Mt_Dio_WriteChannel_TestCase2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Dio_WriteChannel_Param1     = 1u;
  Dio_WriteChannel_Param2     = 3u;
  Dio_ChannelMap[1].Pin       = 0xFFFFFFFFU;
  Dio_ChannelMap[1].ChannelId = 2u;
  Dio_ChannelMap[1].PortBase  = PTA_BASE;
  PTA->PDOR                   = 0xFFFFFFFFU;

  //Step 3) Call FUT
  Dio_WriteChannel(Dio_WriteChannel_Param1, Dio_WriteChannel_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(PTA->PCOR, 0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dio_WriteChannel_TestCase3
///
/// \Test Case Description
///        - Test subject: Test if function sets the specified channel with the specified level
///
/// \FuSa Relevant:ASIL-B
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Goes thorugh each element from channel mapping
///         Step2: Check if the channel id is equal with the wanted channel id
///         Step3: Take the port base value
///         Step4: Check if the level is STD_HIGH
///         Step5: Set or Clear output register
///
/// - Preconditions:
///
/// \input Dio_WriteChannel_Param1     = 1u
/// \input Dio_WriteChannel_Param2     = 0u
/// \input Dio_ChannelMap[1].Pin       = 0u
/// \input Dio_ChannelMap[1].ChannelId = Dio_WriteChannel_Param1
/// \input Dio_ChannelMap[1].PortBase  = PTA_BASE
/// \input PTA->PDOR                   = 0xFFFFFFFFU
///
/// - Expectations:
///
/// \output PTA->PCOR                  = 1u
///
//-----------------------------------------------------------------------------
void Mt_Dio_WriteChannel_TestCase3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Dio_WriteChannel_Param1      = 1u;
  Dio_WriteChannel_Param2      = 0u;
  Dio_ChannelMap[1].Pin        = 0u;
  Dio_ChannelMap[1].ChannelId  = Dio_WriteChannel_Param1;
  Dio_ChannelMap[1].PortBase   = PTA_BASE;
  PTA->PDOR                    = 0xFFFFFFFFU;

  //Step 3) Call FUT
  Dio_WriteChannel(Dio_WriteChannel_Param1, Dio_WriteChannel_Param2);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(PTA->PCOR, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dio_ReadChannel
///
/// \FuSa Relevant:ASIL-B
///
/// \Test Case Description
///    - Test subject:  Test if function sets the specified channel with the specified level
///
///    - Test Design Technique: Requirements-based testing
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_Dio_WriteChannel(void)
{
  Mt_Dio_WriteChannel_TestCase1();
  Mt_Dio_WriteChannel_TestCase2();
  Mt_Dio_WriteChannel_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dio_ReadChannel_TestCase1
///
/// \Test Case Description
///        - Test subject: Test if function returns the value of the specified DIO channel
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Goes thorugh each element from channel mapping
///         Step2: Check if the channel id is equal with the wanted channel id
///         Step3: Take the port base value
///         Step4: Read if port data input register is STD LOR or STD HIGH
///
/// - Preconditions:
///
/// \input Dio_ReadChannel_Param1         = 1u
/// \input Dio_ChannelMap[1].Pin          = 0u
/// \input Dio_ChannelMap[1].ChannelId    = Dio_WriteChannel_Param1
/// \input Dio_ChannelMap[1].PortBase     = PTA_BASE
/// \input PTA->PDOR                      = 0xFFFFFFFFU
///
/// - Expectations:
///
/// \output Dio_ReadChannel_RetVal        = STD_LOW
///
//-----------------------------------------------------------------------------
void Mt_Dio_ReadChannel_TestCase1(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Dio_ReadChannel_Param1      = 1u;
  Dio_ChannelMap[1].Pin       = 0u;
  Dio_ChannelMap[1].ChannelId = Dio_WriteChannel_Param1;
  Dio_ChannelMap[1].PortBase  = PTA_BASE;
  PTA->PDOR                   = 0xFFFFFFFFU;

  //Step 3) Call FUT
  Dio_ReadChannel_RetVal = Dio_ReadChannel(Dio_ReadChannel_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dio_ReadChannel_RetVal, STD_LOW, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dio_ReadChannel_TestCase2
///
/// \Test Case Description
///        - Test subject: Test if function returns the value of the specified DIO channel
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Goes thorugh each element from channel mapping
///         Step2: Check if the channel id is equal with the wanted channel id
///         Step3: Take the port base value
///         Step4: Read if port data input register is STD LOR or STD HIGH
///
/// - Preconditions:
///
/// \input Dio_ReadChannel_Param1         = 1u
/// \input Dio_ChannelMap[1].Pin          = 0u
/// \input Dio_ChannelMap[1].ChannelId    = Dio_WriteChannel_Param1
/// \input Dio_ChannelMap[1].PortBase     = PTA_BASE
/// \input PTA->PDOR                      = 0xFFFFFFFFU
/// \input PTA->PDIR                      = 1u
///
/// - Expectations:
///
/// \output Dio_ReadChannel_RetVal        = STD_HIGH
///
//-----------------------------------------------------------------------------
void Mt_Dio_ReadChannel_TestCase2(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Dio_ReadChannel_Param1      = 1u;
  Dio_ChannelMap[1].Pin       = 0u;
  Dio_ChannelMap[1].ChannelId = Dio_WriteChannel_Param1;
  Dio_ChannelMap[1].PortBase  = PTA_BASE;
  PTA->PDOR                   = 0xFFFFFFFFU;
  PTA->PDIR                   = 1u;

  //Step 3) Call FUT
  Dio_ReadChannel_RetVal = Dio_ReadChannel(Dio_ReadChannel_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dio_ReadChannel_RetVal, STD_HIGH, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dio_ReadChannel_TestCase3
///
/// \Test Case Description
///        - Test subject: Test if function returns the value of the specified DIO channel
///
/// \FuSa Relevant:-
///
/// \Used Test method: Requirements-based test
///
/// \Steps:
///         Step1: Goes thorugh each element from channel mapping
///         Step2: Check if the channel id is equal with the wanted channel id
///         Step3: Take the port base value
///         Step4: Read if port data input register is STD LOR or STD HIGH
///
/// - Preconditions:
///
/// \input Dio_ReadChannel_Param1         = 1u
/// \input Dio_ChannelMap[1].Pin          = 0u
/// \input Dio_ChannelMap[1].ChannelId    = 15u
/// \input Dio_ChannelMap[1].PortBase     = PTA_BASE
/// \input PTA->PDOR                      = 0xFFFFFFFFU
/// \input PTA->PDIR                      = 1u
///
/// - Expectations:
///
/// \output Dio_ReadChannel_RetVal        = STD_LOW
///
//-----------------------------------------------------------------------------
void Mt_Dio_ReadChannel_TestCase3(void)
{
  //Step 1) Set pre - conditions
  //Step 2) Assign Input values
  Dio_ReadChannel_Param1      = 1u;
  Dio_ChannelMap[1].Pin       = 0u;
  Dio_ChannelMap[1].ChannelId = 15u;
  Dio_ChannelMap[1].PortBase  = PTA_BASE;
  PTA->PDOR                   = 0xFFFFFFFFU;
  PTA->PDIR                   = 1u;

  //Step 3) Call FUT
  Dio_ReadChannel_RetVal = Dio_ReadChannel(Dio_ReadChannel_Param1);

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Dio_ReadChannel_RetVal, STD_LOW, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Dio_ReadChannel
///
/// \FuSa Relevant:-
/// 
/// \Test Case Description
///    - Test subject:  Test if function returns the value of the specified DIO channel
///
///    - Test Design Technique: Requirements-based testing
///
/// \Expected Test Results : All contained test cases are passed
///
//-----------------------------------------------------------------------------
void Mt_Dio_ReadChannel(void)
{
  Mt_Dio_ReadChannel_TestCase1();
  Mt_Dio_ReadChannel_TestCase2();
  Mt_Dio_ReadChannel_TestCase3();
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
 ALUnitTest_AddFunction("Mt_Dio_Init", Mt_Dio_Init);
 ALUnitTest_AddFunction("Mt_Dio_WriteChannel", Mt_Dio_WriteChannel);
 ALUnitTest_AddFunction("Mt_Dio_ReadChannel", Mt_Dio_ReadChannel);
}
// EOF
