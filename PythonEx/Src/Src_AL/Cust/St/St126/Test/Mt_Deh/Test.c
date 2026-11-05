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
/// \brief  Unit Test Cases for Deh module
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//=============================================================================
//  Files covered by this module unit test:
//        Cust/St/St126/App/Bsw/Deh:
//            - ctaaDeh.c
//            - Deh.c
//=============================================================================

//=============================================================================
// Includes
//=============================================================================
#include <ALUnitTest_UserInterface.h>

// Stub headers
#include "Test_Stubs.h"

// Headers of the unit test Module
#include "Test.h"


//=============================================================================
// Test Cases
//=============================================================================

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_riDeh_Init_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if riDeh_Init calls correctly Deh_Init function.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1           = eMountedRight
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount         = 0u
/// \input DAPI_InitModule_HitCount                             = 0u
/// \input DAPI_PermFifoStorage_Param1                          = LDEH_E_FIFO_NOTPERM
/// \input DAPI_PermFifoStorage_HitCount                        = 0u
/// \input DAPI_SetPermToSend_Param1                            = LDEH_E_SEND_NOTPERM
/// \input DAPI_SetPermToSend_HitCount                          = 0u
/// \input DAPI_SetSafetyConditions_HitCount                    = 0u
/// \input DAPI_SetSafetyConditions_Param1                      = E_TRUE
/// \input DAPI_SetMainStatus_HitCount                          = 0u
/// \input ucEcuCode                                            = DEH_L_ECU_CODE
/// \input DAPI_InitModule_Param1                               = E_FALSE
/// \input DAPI_InitModule_Param1                               = DEH_L_ECU_CODE
/// \input DAPI_SetMainStatus_Param1                            = DAPI_E_MS_START
///
/// - Expectations: 
///
/// \output Rte_Read_IoHwAbUser_GetMountingSide_HitCount        = 1u
/// \output DAPI_InitModule_Param1                              = E_TRUE
/// \output DAPI_InitModule_Param2                              = DEH_R_ECU_CODE
/// \output DAPI_PermFifoStorage_Param1                         = LDEH_E_FIFO_PERM
/// \output DAPI_PermFifoStorage_HitCount                       = 1u
/// \output DAPI_SetPermToSend_Param1                           = LDEH_E_SEND_PERM
/// \output DAPI_SetPermToSend_HitCount                         = 1u
/// \output DAPI_SetSafetyConditions_Param1                     = E_FALSE
/// \output DAPI_SetSafetyConditions_HitCount                   = 1u
/// \output DAPI_SetMainStatus_Param1                           = DAPI_E_MS_IGNITION
/// \output ucEcuCode                                           = DEH_R_ECU_CODE
///
//-----------------------------------------------------------------------------
void Mt_Deh_riDeh_Init_TestCase1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values 
  Rte_Read_IoHwAbUser_GetMountingSide_Param1    = eMountedRight;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;
  DAPI_InitModule_HitCount                      = 0u;
  DAPI_PermFifoStorage_Param1                   = LDEH_E_FIFO_NOTPERM;
  DAPI_PermFifoStorage_HitCount                 = 0u;
  DAPI_SetPermToSend_Param1                     = LDEH_E_SEND_NOTPERM;
  DAPI_SetPermToSend_HitCount                   = 0u;
  DAPI_SetSafetyConditions_HitCount             = 0u;
  DAPI_SetSafetyConditions_Param1               = E_TRUE;
  DAPI_SetMainStatus_HitCount                   = 0u;
  ucEcuCode                                     = DEH_L_ECU_CODE;
  DAPI_InitModule_Param1                        = E_FALSE;
  DAPI_InitModule_Param2                        = DEH_L_ECU_CODE;
  DAPI_SetMainStatus_Param1                     = DAPI_E_MS_START;

  //Step 3) Call FUT
  riDeh_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,  1u, == );
  AL_UNITTEST_CHECK(DAPI_InitModule_Param1,                        E_TRUE, == );
  AL_UNITTEST_CHECK(DAPI_InitModule_Param2,                        DEH_R_ECU_CODE, == );
  AL_UNITTEST_CHECK(DAPI_PermFifoStorage_Param1,                   LDEH_E_FIFO_PERM, == );
  AL_UNITTEST_CHECK(DAPI_PermFifoStorage_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(DAPI_SetPermToSend_Param1,                     LDEH_E_SEND_PERM, == );
  AL_UNITTEST_CHECK(DAPI_SetPermToSend_HitCount,                   1u, == );
  AL_UNITTEST_CHECK(DAPI_SetSafetyConditions_Param1,               E_FALSE, == );
  AL_UNITTEST_CHECK(DAPI_SetSafetyConditions_HitCount,             1u, == );
  AL_UNITTEST_CHECK(DAPI_SetMainStatus_HitCount,                   1u, == );
  AL_UNITTEST_CHECK(DAPI_SetMainStatus_Param1,                     DAPI_E_MS_IGNITION, == );
  AL_UNITTEST_CHECK(ucEcuCode,                                     DEH_R_ECU_CODE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_riDeh_Init_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if riDeh_Init calls correctly Deh_Init function.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1           = eMountedLeft
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount         = 0u
/// \input DAPI_InitModule_HitCount                             = 0u
/// \input DAPI_InitModule_Param1                               = E_FALSE
/// \input DAPI_InitModule_Param2                               = DEH_R_ECU_CODE
/// \input DAPI_PermFifoStorage_Param1                          = LDEH_E_FIFO_NOTPERM
/// \input DAPI_PermFifoStorage_HitCount                        = 0u
/// \input DAPI_SetPermToSend_Param1                            = LDEH_E_SEND_NOTPERM
/// \input DAPI_SetPermToSend_HitCount                          = 0u
/// \input DAPI_SetSafetyConditions_HitCount                    = 0u
/// \input DAPI_SetMainStatus_HitCount                          = 0u
/// \input ucEcuCode                                            = 1u
/// \input DAPI_SetMainStatus_Param1                            = DAPI_E_MS_START
///
/// - Expectations: 
///
/// \output Rte_Read_IoHwAbUser_GetMountingSide_HitCount        = 1u
/// \output DAPI_InitModule_Param1                              = E_TRUE
/// \output DAPI_InitModule_Param2                              = DEH_L_ECU_CODE
/// \output DAPI_PermFifoStorage_Param1                         = LDEH_E_FIFO_PERM
/// \output DAPI_PermFifoStorage_HitCount                       = 1u
/// \output DAPI_SetPermToSend_Param1                           = LDEH_E_SEND_PERM
/// \output DAPI_SetPermToSend_HitCount                         = 1u
/// \output DAPI_SetSafetyConditions_Param1                     = E_FALSE
/// \output DAPI_SetSafetyConditions_HitCount                   = 1u
/// \output DAPI_SetMainStatus_Param1                           = DAPI_E_MS_IGNITION
/// \output ucEcuCode                                           = DEH_L_ECU_CODE
///
//-----------------------------------------------------------------------------
void Mt_Deh_riDeh_Init_TestCase2(void)
{
 
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAbUser_GetMountingSide_Param1    = eMountedLeft;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;
  DAPI_InitModule_HitCount                      = 0u;
  DAPI_InitModule_Param1                        = E_FALSE;
  DAPI_InitModule_Param2                        = DEH_R_ECU_CODE;
  DAPI_PermFifoStorage_Param1                   = LDEH_E_FIFO_NOTPERM;
  DAPI_PermFifoStorage_HitCount                 = 0u;
  DAPI_SetPermToSend_Param1                     = LDEH_E_SEND_NOTPERM;
  DAPI_SetPermToSend_HitCount                   = 0u;
  DAPI_SetSafetyConditions_HitCount             = 0u;
  DAPI_SetSafetyConditions_Param1               = E_TRUE;
  DAPI_SetMainStatus_HitCount                   = 0u;
  ucEcuCode                                     = DEH_R_ECU_CODE;
  DAPI_SetMainStatus_Param1                     = DAPI_E_MS_START;

  //Step 3) Call FUT
  riDeh_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,  1u, == );
  AL_UNITTEST_CHECK(DAPI_InitModule_Param1,                        E_TRUE, == );
  AL_UNITTEST_CHECK(DAPI_InitModule_Param2,                        DEH_L_ECU_CODE, == );
  AL_UNITTEST_CHECK(DAPI_PermFifoStorage_Param1,                   LDEH_E_FIFO_PERM, == );
  AL_UNITTEST_CHECK(DAPI_PermFifoStorage_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(DAPI_SetPermToSend_Param1,                     LDEH_E_SEND_PERM, == );
  AL_UNITTEST_CHECK(DAPI_SetPermToSend_HitCount,                   1u, == );
  AL_UNITTEST_CHECK(DAPI_SetSafetyConditions_Param1,               E_FALSE, == );
  AL_UNITTEST_CHECK(DAPI_SetSafetyConditions_HitCount,             1u, == );
  AL_UNITTEST_CHECK(DAPI_SetMainStatus_HitCount,                   1u, == );
  AL_UNITTEST_CHECK(DAPI_SetMainStatus_Param1,                     DAPI_E_MS_IGNITION, == );
  AL_UNITTEST_CHECK(ucEcuCode,                                     DEH_L_ECU_CODE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_riDeh_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if riDeh_Init calls correctly Deh_Init function.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Deh_riDeh_Init(void)
{
  Mt_Deh_riDeh_Init_TestCase1();
  Mt_Deh_riDeh_Init_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_rpDeh_Cycle0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if rpDeh_Cycle0 calls correctly Deh_Cycle0 function.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SysMon_LifePhases_HitCount                               =0u
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount -                           =0u
/// \input Rte_Read_SysMon_LifePhases_Param1.ePhaseVie                       = eNormalMode
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 400u
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                       = SIG_VALID
/// \input DAPI_SetSafetyConditions_Param1                                   = E_FALSE
/// \input DAPI_SetSafetyConditions_HitCount                                 = 0u
/// \input DAPI_ScheduleMainFunction_HitCount                                = 0u
///
/// - Expectations: 
///
/// \output Rte_Read_SysMon_LifePhases_HitCount                             = 1u;
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount                           = 1u;
/// \output DAPI_SetSafetyConditions_Param1                                 = 170u;
/// \output DAPI_SetSafetyConditions_HitCount                               = 1u;
/// \output DAPI_ScheduleMainFunction_HitCount                              = 1u;
///
//-----------------------------------------------------------------------------
void Mt_Deh_rpDeh_Cycle0(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_LifePhases_HitCount                               = 0u;
  Rte_Read_SysMon_VehicleSpeed_HitCount                             = 0u;
  Rte_Read_SysMon_LifePhases_Param1.ePhaseVie                       = eNormalMode;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = DEH_5KMH_THRESHOLD;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                       = SIG_VALID;
  DAPI_SetSafetyConditions_Param1                                   = E_FALSE;
  DAPI_SetSafetyConditions_HitCount                                 = 0u;
  DAPI_ScheduleMainFunction_HitCount                                = 0u;

  //Step 3) Call FUT
  rpDeh_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_LifePhases_HitCount,    1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,  1u, == );
  AL_UNITTEST_CHECK(DAPI_SetSafetyConditions_Param1,        E_TRUE, == );
  AL_UNITTEST_CHECK(DAPI_SetSafetyConditions_HitCount,      1u, == );
  AL_UNITTEST_CHECK(DAPI_ScheduleMainFunction_HitCount,     1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_AppearanceDetected_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description: Test if Deh_AppearanceDetected calls correctly DAPI_BuildDECtxt,
///                         ErrCust_GetActualErrorIndex and ErrCust_ulGetDtcCode functions.
///
///    - Test Design Technique: ET (Exploratory Testing)

/// - Preconditions:
///
/// \input  DAPI_BuildDECtxt_HitCount             = 0u;
/// \input  ErrCust_ulGetDtcCode_HitCount         = 0u;
/// \input  ErrCust_GetActualErrorIndex_HitCount  = 0u;
/// \input  Deh_AppearanceDetected_Param1         = 14u;
/// \input  DAPI_BuildDECtxt_Param2               = LDEH_E_DISAPPEAR;
/// \input  ErrCust_ulGetDtcCode_RetVal           = 5u;
/// \input  DAPI_BuildDECtxt_Param4               = DEH_R_ECU_CODE;
/// \input  DAPI_BuildDECtxt_Param5               = 2u;
/// \input  ucEcuCode                             = 1u;
/// \input  ErrCust_GetActualErrorIndex_RetVal    = 2u;
/// \input  ErrCust_ulGetDtcCode_Param1           = 3u;
/// \input DAPI_BuildDECtxt_Param1                = 0u;
/// \input DAPI_BuildDECtxt_Param3                = 0u;
///
/// - Expectations: 
///
/// \output  DAPI_BuildDECtxt_HitCount             = 1u
/// \output  ErrCust_ulGetDtcCode_HitCount         = 1u
/// \output  ErrCust_GetActualErrorIndex_HitCount  = 1u
/// \output  ErrCust_GetActualErrorIndex_Param1    = 15u
/// \output  DAPI_BuildDECtxt_Param2               = LDEH_E_APPEAR
/// \output  DAPI_BuildDECtxt_Param3               = 5u
/// \output  DAPI_BuildDECtxt_Param4               = DEH_DTC_FORMAT_ID
/// \output  DAPI_BuildDECtxt_Param5               = 1u
/// \output  ErrCust_ulGetDtcCode_Param1           = 2u
///
//-----------------------------------------------------------------------------
void Mt_Deh_AppearanceDetected_TestCase1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  DAPI_BuildDECtxt_HitCount             = 0u;
  ErrCust_ulGetDtcCode_HitCount         = 0u;
  ErrCust_GetActualErrorIndex_HitCount  = 0u;
  Deh_AppearanceDetected_Param1         = 14u;
  DAPI_BuildDECtxt_Param2               = LDEH_E_DISAPPEAR;
  ErrCust_ulGetDtcCode_RetVal           = 5u;
  DAPI_BuildDECtxt_Param4               = DEH_R_ECU_CODE;
  DAPI_BuildDECtxt_Param5               = 2u;
  ucEcuCode                             = 1u;
  ErrCust_GetActualErrorIndex_RetVal    = 2u;
  ErrCust_GetActualErrorIndex_Param1    = 0u;
  ErrCust_ulGetDtcCode_Param1           = 3u;
  DAPI_BuildDECtxt_Param1               = 0u;
  DAPI_BuildDECtxt_Param3               = 0u;
  Deh_asDehLogTab[10].eEventState       = eDeh_Undef;
 
  //Step 3) Call FUT
  Deh_AppearanceDetected(Deh_AppearanceDetected_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_HitCount,             1u, == );
  AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_HitCount,         1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_HitCount,  1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_Param1,    15u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param2,               LDEH_E_APPEAR, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param3,               5u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param4,               DEH_DTC_FORMAT_ID, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param5,               1u, == );
  AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_Param1,           2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_AppearanceDetected_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description: Test if Deh_AppearanceDetected calls correctly DAPI_BuildDECtxt,
///                         ErrCust_GetActualErrorIndex and ErrCust_ulGetDtcCode functions.
///
///    - Test Design Technique: ET (Exploratory Testing)

/// - Preconditions:
///
/// \input    ErrCust_ulGetDtcCode_HitCount      = 0u;
/// \input ErrCust_GetActualErrorIndex_HitCount  = 0u;
/// \input Deh_AppearanceDetected_Param1         = 14u;
/// \input ErrCust_ulGetDtcCode_RetVal           = 5u;
/// \input ucEcuCode                             = 1u;
/// \input ErrCust_GetActualErrorIndex_RetVal    = 2u;
/// \input ErrCust_GetActualErrorIndex_Param1    = 0u;
/// \input ErrCust_ulGetDtcCode_Param1           = 3u;
/// \input for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
/// \input {
/// \input 
/// \input   Deh_asDehLogTab[ucIndx].ulDTCCode    = 10;
/// \input   Deh_asDehLogTab[ucIndx].eEventState  = eDeh_ApearedConf;
/// \input }
///
/// - Expectations: 
///
/// \output    AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_HitCount,         1u, == );
/// \output    AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_HitCount,  1u, == );
/// \output    AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_Param1,    15u, == );
/// \output    AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_Param1,           2u, == );
///
//-----------------------------------------------------------------------------
void Mt_Deh_AppearanceDetected_TestCase2(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  ErrCust_ulGetDtcCode_HitCount         = 0u;
  ErrCust_GetActualErrorIndex_HitCount  = 0u;
  Deh_AppearanceDetected_Param1         = 14u;
  ErrCust_ulGetDtcCode_RetVal           = 5u;
  ucEcuCode                             = 1u;
  ErrCust_GetActualErrorIndex_RetVal    = 2u;
  ErrCust_GetActualErrorIndex_Param1    = 0u;
  ErrCust_ulGetDtcCode_Param1           = 3u;
  for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
  {

    Deh_asDehLogTab[ucIndx].ulDTCCode    = 10;
    Deh_asDehLogTab[ucIndx].eEventState  = eDeh_ApearedConf;
  }
  //Step 3) Call FUT
  Deh_AppearanceDetected(Deh_AppearanceDetected_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_HitCount,         1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_HitCount,  1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_Param1,    15u, == );
  AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_Param1,           2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_AppearanceDetected_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description: Test if Deh_AppearanceDetected calls correctly DAPI_BuildDECtxt,
///                         ErrCust_GetActualErrorIndex and ErrCust_ulGetDtcCode functions.
///
///    - Test Design Technique: ET (Exploratory Testing)
/// - Preconditions:
///
/// \input  ErrCust_ulGetDtcCode_HitCount         = 0u;
/// \input  ErrCust_GetActualErrorIndex_HitCount  = 0u;
/// \input  Deh_AppearanceDetected_Param1         = 14u;
/// \input  ErrCust_ulGetDtcCode_RetVal           = 5u;
/// \input  ucEcuCode                             = 1u;
/// \input  ErrCust_GetActualErrorIndex_RetVal    = 2u;
/// \input  ErrCust_GetActualErrorIndex_Param1    = 0u;
/// \input  ErrCust_ulGetDtcCode_Param1           = 3u;
/// \input  Deh_asDehLogTab[10].eEventState       = eDeh_Apeared;
/// \input  Deh_asDehLogTab[10].ulDTCCode         = 5u;
///
/// - Expectations: 
///
/// \output   AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_HitCount, 1u, == );
/// \output   AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_HitCount, 1u, == );
/// \output   AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_Param1, 15u, == );
/// \output   AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_Param1, 2u, == );
///
//-----------------------------------------------------------------------------
void Mt_Deh_AppearanceDetected_TestCase4(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  ErrCust_ulGetDtcCode_HitCount         = 0u;
  ErrCust_GetActualErrorIndex_HitCount  = 0u;
  Deh_AppearanceDetected_Param1         = 14u;
  ErrCust_ulGetDtcCode_RetVal           = 5u;
  ucEcuCode                             = 1u;
  ErrCust_GetActualErrorIndex_RetVal    = 2u;
  ErrCust_GetActualErrorIndex_Param1    = 0u;
  ErrCust_ulGetDtcCode_Param1           = 3u;
  Deh_asDehLogTab[10].eEventState       = eDeh_Apeared;
  Deh_asDehLogTab[10].ulDTCCode         = 5u;
  //Step 3) Call FUT
  Deh_AppearanceDetected(Deh_AppearanceDetected_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_HitCount,         1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_HitCount,  1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_Param1,    15u, == );
  AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_Param1,           2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_AppearanceDetected_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description: Test if Deh_AppearanceDetected calls correctly DAPI_BuildDECtxt,
///                         ErrCust_GetActualErrorIndex and ErrCust_ulGetDtcCode functions.
///
///    - Test Design Technique: ET (Exploratory Testing)
/// - Preconditions:
///
/// \input  Deh_AppearanceDetected_Param1         = 14u;
/// \input  DAPI_BuildDECtxt_RetVal               = LDEH_E_ERR_NSYNC;
/// \input    for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
/// \input {
/// \input   Deh_asDehLogTab[ucIndx].eEventState  = eDeh_Disapeared;
/// \input }
/// \input  Deh_asDehLogTab[17].eEventState       = eDeh_Init;
///
/// - Expectations: 
///
/// \output   AL_UNITTEST_CHECK(Deh_asDehLogTab[17].eEventState, eDeh_Undef, == );

///
//-----------------------------------------------------------------------------
void Mt_Deh_AppearanceDetected_TestCase3(void)
{

  //Step 1: Set pre-conditions
  //Step 2) Assign Input values

  Deh_AppearanceDetected_Param1          = 14u;
  DAPI_BuildDECtxt_RetVal                = LDEH_E_ERR_NSYNC;
 
  for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
  {
    Deh_asDehLogTab[ucIndx].eEventState  = eDeh_Disapeared;
  }

  Deh_asDehLogTab[17].eEventState        = eDeh_Init;

  //Step 3) Call FUT
  Deh_AppearanceDetected(Deh_AppearanceDetected_Param1);


  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Deh_asDehLogTab[17].eEventState,  eDeh_Undef, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Mt_Deh_AppearanceDetected
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that function verify allback from Dem module. It is called at first detection of a fault
///        (transition from confirmed absent to present).
///        In this momment the enviromental parameters needed for DEH reporting are freezed
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Deh_AppearanceDetected()
{
  Mt_Deh_AppearanceDetected_TestCase1();
  Mt_Deh_AppearanceDetected_TestCase2();
  Mt_Deh_AppearanceDetected_TestCase3();
  Mt_Deh_AppearanceDetected_TestCase4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_AppearanceConfirmed_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if Deh_AppearanceConfirmed calls correctly DAPI_AddDE function.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Deh_AppearanceConfirmed_Param1  = 14u;
/// \input ErrCust_ulGetDtcCode_RetVal     = 13u;
/// \input 
/// \input for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
/// \input {
/// \input   Deh_asDehLogTab[ucIndx].eEventState  = eDeh_Undef;
/// \input   Deh_asDehLogTab[ucIndx].ulDTCCode    = 0u;
/// \input }
/// \input 
/// \input Deh_asDehLogTab[5].ulDTCCode    = 13u;
/// \input Deh_asDehLogTab[5].unDemEvent   = 14u;
/// \input Deh_asDehLogTab[5].eEventState  = eDeh_Apeared;
///
/// - Expectations: 
///
/// \output   AL_UNITTEST_CHECK(Deh_asDehLogTab[5].eEventState, eDeh_ApearedConf, == );
///
//-----------------------------------------------------------------------------
void Mt_Deh_AppearanceConfirmed_TestCase1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Deh_AppearanceConfirmed_Param1         = 14u;
  ErrCust_ulGetDtcCode_RetVal            = 13u;

  for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
  {
    Deh_asDehLogTab[ucIndx].eEventState  = eDeh_Undef;
    Deh_asDehLogTab[ucIndx].ulDTCCode    = 0u;
  }

  Deh_asDehLogTab[5].ulDTCCode           = 13u;
  Deh_asDehLogTab[5].unDemEvent          = 14u;
  Deh_asDehLogTab[5].eEventState         = eDeh_Apeared;

  //Step 3) Call FUT
  Deh_AppearanceConfirmed(Deh_AppearanceConfirmed_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Deh_asDehLogTab[5].eEventState,  eDeh_ApearedConf, == );

}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_AppearanceConfirmed_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if Verify if CONFIRMED bit from DTC is set
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DAPI_AddDE_HitCount                   = 0u
/// \input ErrCust_GetStatusOfDtc_RetVal         = 9u
/// \input ErrCust_GetActualErrorIndex_RetVal    = 9u
/// \input ErrCust_GetActualErrorIndex_HitCount  = 0u
/// \input ErrCust_GetStatusOfDtc_HitCount       = 0u
/// \input DAPI_AddDE_Param2                     = E_FALSE
/// \input DAPI_BuildDECtxt_HitCount             = 0u
/// \input ucEcuCode                             = 5u
/// \input DAPI_AddDE_Param1                     = 0u
///
/// - Expectations: 
///
/// \output DAPI_AddDE_HitCount                  = 0u
/// \output ErrCust_GetActualErrorIndex_HitCount = 1u
/// \output ErrCust_GetStatusOfDtc_HitCount      = 1u
/// \output DAPI_AddDE_Param2                    = E_FALSE
/// \output DAPI_BuildDECtxt_HitCount            = 0u
/// \input DAPI_AddDE_Param1                     = 0u;
/// \input DAPI_BuildDECtxt_Param1               = 0u;
/// \input DAPI_BuildDECtxt_Param2               = LDEH_E_DISAPPEAR;
/// \input DAPI_BuildDECtxt_Param3               = 0u;
/// \input DAPI_BuildDECtxt_Param4               = DEH_DTC_FORMAT_ID;
/// \input DAPI_BuildDECtxt_Param5               = 0u;
/// \output DAPI_AddDE_Param1                    = 0u
///
//-----------------------------------------------------------------------------
void Mt_Deh_AppearanceConfirmed_TestCase2(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  DAPI_AddDE_HitCount                   = 0u;
  ErrCust_GetStatusOfDtc_RetVal         = 9u; //status flags
  ErrCust_GetActualErrorIndex_RetVal    = 9u; // status flags
  ErrCust_GetActualErrorIndex_HitCount  = 0u;
  ErrCust_GetActualErrorIndex_Param1    = 0u;
  ErrCust_GetStatusOfDtc_HitCount       = 0u;
  DAPI_AddDE_Param2                     = E_FALSE;
  DAPI_BuildDECtxt_HitCount             = 0u;
  DAPI_BuildDECtxt_Param1               = 0u;
  DAPI_BuildDECtxt_Param2               = LDEH_E_DISAPPEAR;
  DAPI_BuildDECtxt_Param3               = 0u;
  DAPI_BuildDECtxt_Param4               = 0u;
  DAPI_BuildDECtxt_Param5               = 0u;
  ucEcuCode                             = 5u;
  DAPI_AddDE_Param1                     = 0u;
  DAPI_AddDE_Param2                     = E_FALSE;
  Deh_AppearanceConfirmed_Param1        = 14u;

  //Step 3) Call FUT
  Deh_AppearanceConfirmed(Deh_AppearanceConfirmed_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(DAPI_AddDE_HitCount,                   0u, == );
  AL_UNITTEST_CHECK(ErrCust_GetStatusOfDtc_HitCount,       1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_HitCount,  1u, == );
  AL_UNITTEST_CHECK(DAPI_AddDE_Param2,                     E_FALSE, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_HitCount,             0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param1,               0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param2,               LDEH_E_DISAPPEAR, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param3,               0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param4,               DEH_DTC_FORMAT_ID, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param5,               0u, == );
  AL_UNITTEST_CHECK(DAPI_AddDE_Param1,                     0u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_Param1,    15u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_AppearanceConfirmed_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if Deh_AppearanceConfirmed calls correctly DAPI_AddDE function.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Deh_AppearanceConfirmed_Param1  = 14u;
/// \input ErrCust_ulGetDtcCode_RetVal     = 13u;
/// \input 
/// \input for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
/// \input {
/// \input   Deh_asDehLogTab[ucIndx].eEventState  = 0xFF;
/// \input   Deh_asDehLogTab[ucIndx].ulDTCCode    = 0u;
/// \input }
/// \input 
/// \input Deh_asDehLogTab[5].ulDTCCode    = 13u;
/// \input Deh_asDehLogTab[5].unDemEvent   = 14u;
/// \input Deh_asDehLogTab[5].eEventState  = eDeh_Undef;
///
/// - Expectations: 
///
/// \output   AL_UNITTEST_CHECK(Deh_asDehLogTab[5].eEventState, eDeh_ApearedConf_DirectSent, == );
///
//-----------------------------------------------------------------------------
void Mt_Deh_AppearanceConfirmed_TestCase3(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Deh_AppearanceConfirmed_Param1  = 14u;
  ErrCust_ulGetDtcCode_RetVal     = 13u;

  for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
  {
    Deh_asDehLogTab[ucIndx].eEventState  = 0xFF;
    Deh_asDehLogTab[ucIndx].ulDTCCode    = 0u;
  }

  Deh_asDehLogTab[5].ulDTCCode    = 13u;
  Deh_asDehLogTab[5].unDemEvent   = 14u;
  Deh_asDehLogTab[5].eEventState  = eDeh_Undef;

  //Step 3) Call FUT
  Deh_AppearanceConfirmed(Deh_AppearanceConfirmed_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Deh_asDehLogTab[5].eEventState,  eDeh_ApearedConf_DirectSent, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_AppearanceConfirmed
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test Callback from Dem module. It is called at first detection of a 
///                     fault confirmed present (transition from present to confirmed present).
///                     In this momment the DEH frames shall be sent.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Deh_AppearanceConfirmed(void)
{
  Mt_Deh_AppearanceConfirmed_TestCase1();
  Mt_Deh_AppearanceConfirmed_TestCase2();
  Mt_Deh_AppearanceConfirmed_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_DisappearanceDetected_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if Deh_DisappearanceDetected calls correctly DAPI_BuildDECtxt, 
///                     ErrCust_ulGetDtcCode, and ErrCust_GetActualErrorIndex functions
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DAPI_BuildDECtxt_HitCount                    = 0u;
/// \input ErrCust_ulGetDtcCode_HitCount                = 0u;
/// \input ErrCust_GetActualErrorIndex_HitCount         = 0u;
/// \input ErrCust_GetActualErrorIndex_Param1           = 0u;
/// \input Deh_DisappearanceDetected_Param1             = 15u;
/// \input ErrCust_ulGetDtcCode_RetVal                  = 2u;
/// \input Deh_asDehLogTab[0u].ulDTCCode                = 2u;
/// \input Deh_asDehLogTab[0u].eEventState              = eDeh_Apeared;
/// \input Deh_asDehLogTab[0u].ucDemEvntCnt_Disapeared  = 0u;
///
/// - Expectations: 
/// \output ErrCust_GetActualErrorIndex_Param1           = 16u
/// \output Deh_asDehLogTab[0u].ucDemEvntCnt_Disapeared  = 1u
///
//-----------------------------------------------------------------------------
void Mt_Deh_DisappearanceDetected_TestCase1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  DAPI_BuildDECtxt_HitCount                    = 0u;
  ErrCust_ulGetDtcCode_HitCount                = 0u;
  ErrCust_GetActualErrorIndex_HitCount         = 0u;
  ErrCust_GetActualErrorIndex_Param1           = 0u;
  Deh_DisappearanceDetected_Param1             = 15u;
  ErrCust_ulGetDtcCode_RetVal                  = 2u;
  Deh_asDehLogTab[0u].ulDTCCode                = 2u;
  Deh_asDehLogTab[0u].eEventState              = eDeh_Apeared;
  Deh_asDehLogTab[0u].ucDemEvntCnt_Disapeared  = 0u; 

  //Step 3) Call FUT
  Deh_DisappearanceDetected(Deh_DisappearanceDetected_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_Param1,           16u, == );
  AL_UNITTEST_CHECK(Deh_asDehLogTab[0u].ucDemEvntCnt_Disapeared,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_DisappearanceDetected_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if Deh_DisappearanceDetected calls correctly DAPI_BuildDECtxt, 
///                     ErrCust_ulGetDtcCode, and ErrCust_GetActualErrorIndex functions
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  DAPI_BuildDECtxt_HitCount                    = 0u;
/// \input  ErrCust_ulGetDtcCode_HitCount                = 0u;
/// \input  ErrCust_GetActualErrorIndex_HitCount         = 0u;
/// \input  Deh_asDehLogTab[0u].ucDemEvntCnt_Disapeared  = 0u;
///
/// - Expectations: 
/// \output ErrCust_GetActualErrorIndex_Param1           = 16u
/// \output Deh_asDehLogTab[0u].ucDemEvntCnt_Disapeared  = 0u
///
//-----------------------------------------------------------------------------
void Mt_Deh_DisappearanceDetected_TestCase2(void)
{
    //Step 1: Set pre-conditions
    //Step 2) Assign Input values
    DAPI_BuildDECtxt_HitCount                    = 0u;
    ErrCust_ulGetDtcCode_HitCount                = 0u;
    ErrCust_GetActualErrorIndex_HitCount         = 0u;
    Deh_asDehLogTab[0u].ucDemEvntCnt_Disapeared  = 0u;

    for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
    {
        Deh_asDehLogTab[ucIndx].eEventState  = eDeh_DisapearedConf_LGM;
    }

    //Step 3) Call FUT
    Deh_DisappearanceDetected(Deh_DisappearanceDetected_Param1);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_Param1,           16u, == );
    AL_UNITTEST_CHECK(Deh_asDehLogTab[0u].ucDemEvntCnt_Disapeared,  0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_DisappearanceDetected_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if Deh_DisappearanceDetected calls correctly DAPI_BuildDECtxt, 
///                     ErrCust_ulGetDtcCode, and ErrCust_GetActualErrorIndex functions
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input    Deh_DisappearanceDetected_Param1  = 14u;
/// \input    for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
/// \input    {
/// \input      Deh_asDehLogTab[ucIndx].eEventState  = 0xFF;
/// \input      Deh_asDehLogTab[ucIndx].ulDTCCode    = 0xFF;
/// \input    }
/// \input    Deh_asDehLogTab[7].ucDemEvntCnt_Disapeared  = 0u;
/// \input    Deh_asDehLogTab[7].eEventState              = eDeh_Init;
/// \input    ErrCust_ucGetStatusOfDTC_RetVal             = 0xF;
///
/// - Expectations: 
/// \output  AL_UNITTEST_CHECK(Deh_asDehLogTab[7].ucDemEvntCnt_Disapeared, 1u, == );
///
//-----------------------------------------------------------------------------
void Mt_Deh_DisappearanceDetected_TestCase3(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Deh_DisappearanceDetected_Param1       = 14u;
  for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
  {
    Deh_asDehLogTab[ucIndx].eEventState  = 0xFF;
    Deh_asDehLogTab[ucIndx].ulDTCCode    = 0xFF;
  }
  Deh_asDehLogTab[7].ucDemEvntCnt_Disapeared  = 0u;
  Deh_asDehLogTab[7].eEventState              = eDeh_Init;
  ErrCust_ucGetStatusOfDTC_RetVal             = 0xF;

  //Step 3) Call FUT
  Deh_DisappearanceDetected(Deh_DisappearanceDetected_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Deh_asDehLogTab[7].ucDemEvntCnt_Disapeared,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_DisappearanceDetected
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that function verify Callback from Dem module. 
///            It is called at first detection of a fault present (transition from confirmed present to absent).
///            In this momment the DEH frames shall be Nvm stored
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Deh_DisappearanceDetected(void)
{
  Mt_Deh_DisappearanceDetected_TestCase1();
  Mt_Deh_DisappearanceDetected_TestCase2();
  Mt_Deh_DisappearanceDetected_TestCase3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_DisappearanceConfirmed_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if Deh_DisappearanceConfirmed calls correctly DAPI_BuildDECtxt, 
///                     ErrCust_ulGetDtcCode, ErrCust_GetActualErrorIndex and DAPI_AddDE functions.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  DAPI_BuildDECtxt_HitCount             = 0u;
/// \input  ErrCust_ulGetDtcCode_HitCount         = 0u;
/// \input  ErrCust_GetActualErrorIndex_HitCount  = 0u;
/// \input  DAPI_AddDE_HitCount                   = 0u;
/// \input  DAPI_AddDE_Param2                     = E_FALSE;
/// \input  DAPI_BuildDECtxt_Param2               = 0u;
/// \input  DAPI_BuildDECtxt_Param4               = 0u;
/// \input  DAPI_BuildDECtxt_Param3               = 0u;
/// \input  DAPI_BuildDECtxt_Param1               = 0u;
/// \input  DAPI_BuildDECtxt_Param5               = 0u;
/// \input  ucEcuCode                             = 5u;
/// \input  ErrCust_GetActualErrorIndex_RetVal    = 2u;
/// \imput  DAPI_BuildDECtxt_Param1               = 0u;
/// \input  ErrCust_GetActualErrorIndex_RetVal    = 2u;
/// \input  Deh_DisappearanceConfirmed_Param1     = 14u;
/// \input  ErrCust_ulGetDtcCode_RetVal           = 1u;
///
/// - Expectations: 
///
/// \output  ErrCust_ulGetDtcCode_HitCount         = 1u
/// \output  ErrCust_GetActualErrorIndex_HitCount  = 1u
/// \output  ErrCust_GetActualErrorIndex_Param1    = 15u
///
//-----------------------------------------------------------------------------
void Mt_Deh_DisappearanceConfirmed_TestCase1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  ErrCust_ulGetDtcCode_HitCount         = 0u;
  ErrCust_GetActualErrorIndex_HitCount  = 0u;
  ucEcuCode                             = 5u;
  ErrCust_GetActualErrorIndex_RetVal    = 2u;
  Deh_DisappearanceConfirmed_Param1     = 14u;
  ErrCust_ulGetDtcCode_RetVal           = 1u;
  for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
  {
    Deh_asDehLogTab[ucIndx].ulDTCCode                = 10;
    Deh_asDehLogTab[ucIndx].eEventState              = eDeh_ApearedConf;
    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared     = 0;
    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Disapeared  = 0;
  }

  //Step 3) Call FUT
  Deh_DisappearanceConfirmed(Deh_DisappearanceConfirmed_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_HitCount,         1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_HitCount,  1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_Param1,    15u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_DisappearanceConfirmed_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if Deh_DisappearanceConfirmed calls correctly DAPI_BuildDECtxt, 
///                     ErrCust_ulGetDtcCode, ErrCust_GetActualErrorIndex and DAPI_AddDE functions.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Deh_DisappearanceConfirmed_Param1     = 0u;
/// \input  ErrCust_GetActualErrorIndex_Param1    = 1u;
/// \input  ErrCust_GetActualErrorIndex_RetVal    = 1u;
/// \input  ErrCust_GetActualErrorIndex_HitCount  = 0u;
/// \input  ErrCust_ulGetDtcCode_Param1           = 1u;
/// \input  ErrCust_ulGetDtcCode_RetVal           = 10u;
/// \input  ErrCust_ulGetDtcCode_HitCount         = 0u;
/// \input  for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
/// \input  {
/// \input    Deh_asDehLogTab[ucIndx].ulDTCCode                = 10u;
/// \input    Deh_asDehLogTab[ucIndx].eEventState              = eDeh_ApearedConf;
/// \input    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared     = 0u;
/// \input    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Disapeared  = 0u;
/// \input  }
/// \input  DAPI_BuildDECtxt_RetVal            = LDEH_E_ERR_NSYNC;
/// \input  Deh_asDehLogTab[5].eEventState     = eDeh_ApearedConf;
/// \input  Deh_asDehLogTab[5].ulDTCCode       = 0u;
/// \input  Deh_DisappearanceConfirmed_Param1  = 14u;
///
/// - Expectations: 
///
/// \output  ErrCust_ulGetDtcCode_HitCount         = 1u;
/// \output  ErrCust_GetActualErrorIndex_HitCount  = 1u;
/// \output  ErrCust_GetActualErrorIndex_Param1    = 15u;
///
//-----------------------------------------------------------------------------
void Mt_Deh_DisappearanceConfirmed_TestCase2(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Deh_DisappearanceConfirmed_Param1     = 0u;
  ErrCust_GetActualErrorIndex_Param1    = 1u;
  ErrCust_GetActualErrorIndex_RetVal    = 1u;
  ErrCust_GetActualErrorIndex_HitCount  = 0u;
  ErrCust_ulGetDtcCode_Param1           = 1u;
  ErrCust_ulGetDtcCode_RetVal           = 10u;
  ErrCust_ulGetDtcCode_HitCount         = 0u;
  for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
  {
    Deh_asDehLogTab[ucIndx].ulDTCCode                = 10u;
    Deh_asDehLogTab[ucIndx].eEventState              = eDeh_ApearedConf;
    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared     = 0u;
    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Disapeared  = 0u;
  }
  DAPI_BuildDECtxt_RetVal           = LDEH_E_ERR_NSYNC;
  Deh_asDehLogTab[5].eEventState    = eDeh_ApearedConf;
  Deh_asDehLogTab[5].ulDTCCode      = 0u;
  Deh_DisappearanceConfirmed_Param1 = 14u;
  
  //Step 3) Call FUT
  Deh_DisappearanceConfirmed(Deh_DisappearanceConfirmed_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_HitCount,         1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_HitCount,  1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_Param1,    15u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_DisappearanceConfirmed_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if Deh_DisappearanceConfirmed calls correctly DAPI_BuildDECtxt, 
///                     ErrCust_ulGetDtcCode, ErrCust_GetActualErrorIndex and DAPI_AddDE functions.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  DAPI_BuildDECtxt_HitCount             = 0u;
/// \input  ErrCust_ulGetDtcCode_HitCount         = 0u;
/// \input  ErrCust_GetActualErrorIndex_HitCount  = 0u;
/// \input  DAPI_AddDE_HitCount                   = 0u;
/// \input  DAPI_AddDE_Param2                     = E_FALSE;
/// \input  DAPI_BuildDECtxt_Param1               = 0u;
/// \input  DAPI_BuildDECtxt_Param2               = LDEH_E_APPEAR;
/// \input  DAPI_BuildDECtxt_Param3               = 0u;
/// \input  DAPI_BuildDECtxt_Param4               = DEH_DTC_FORMAT_ID;
/// \input  DAPI_BuildDECtxt_Param5               = 0u;
/// \input  ucEcuCode                             = 2u;
/// \input  ErrCust_GetActualErrorIndex_RetVal    = 2u;
/// \imput  Deh_DisappearanceConfirmed_Param1     = 14u;
///
/// - Expectations: 
///
/// \output  DAPI_BuildDECtxt_HitCount             = 0u;
/// \output  ErrCust_ulGetDtcCode_HitCount         = 1u;
/// \output  ErrCust_GetActualErrorIndex_HitCount  = 1u;
/// \output  DAPI_AddDE_HitCount                   = 0u;
/// \output  DAPI_AddDE_Param2                     = E_FALSE;
/// \output  DAPI_BuildDECtxt_Param2               = LDEH_E_APPEAR;
/// \output  DAPI_BuildDECtxt_Param4               = DEH_DTC_FORMAT_ID;
/// \output  DAPI_BuildDECtxt_Param5               = 0u;
/// \output  DAPI_BuildDECtxt_Param1               = 0u;
/// \output  DAPI_BuildDECtxt_Param3               = 0u;
/// \output  ErrCust_GetActualErrorIndex_Param1    = 15u;
///
//-----------------------------------------------------------------------------
void Mt_Deh_DisappearanceConfirmed_TestCase3(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  DAPI_BuildDECtxt_HitCount             = 0u;
  ErrCust_ulGetDtcCode_HitCount         = 0u;
  ErrCust_GetActualErrorIndex_HitCount  = 0u;
  DAPI_AddDE_HitCount                   = 0u;
  DAPI_AddDE_Param2                     = E_FALSE;
  DAPI_AddDE_Param1                     = 0u;
  DAPI_BuildDECtxt_Param1               = 0u;
  DAPI_BuildDECtxt_Param2               = LDEH_E_APPEAR;
  DAPI_BuildDECtxt_Param3               = 0u;
  DAPI_BuildDECtxt_Param4               = DEH_DTC_FORMAT_ID;
  DAPI_BuildDECtxt_Param5               = 0u;
  DAPI_BuildDECtxt_RetVal               = LDEH_E_ERR_INVAL;
  ucEcuCode                             = 2u;
  ErrCust_GetActualErrorIndex_RetVal    = 2u;
  Deh_DisappearanceConfirmed_Param1     = 14u;

  for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
  {
    Deh_asDehLogTab[ucIndx].ulDTCCode                = 10;
    Deh_asDehLogTab[ucIndx].eEventState              = eDeh_ApearedConf;
    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared     = 110;
    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Disapeared  = 0;
  }

  //Step 3) Call FUT
  Deh_DisappearanceConfirmed(Deh_DisappearanceConfirmed_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_HitCount,             0u, == );
  AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_HitCount,         1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_HitCount,  1u, == );
  AL_UNITTEST_CHECK(DAPI_AddDE_HitCount,                   0u, == );
  AL_UNITTEST_CHECK(DAPI_AddDE_Param1,                     0u, == );
  AL_UNITTEST_CHECK(DAPI_AddDE_Param2,                     E_FALSE, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param2,               LDEH_E_APPEAR, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param4,               DEH_DTC_FORMAT_ID, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param5,               0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param1,               0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param3,               0u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_Param1,    15u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_DisappearanceConfirmed_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if Deh_DisappearanceConfirmed calls correctly DAPI_BuildDECtxt, 
///                     ErrCust_ulGetDtcCode, ErrCust_GetActualErrorIndex and DAPI_AddDE functions.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Deh_DisappearanceConfirmed_Param1       = 14u;
/// \input ErrCust_ulGetDtcCode_HitCount           = 0u;
/// \input ErrCust_GetActualErrorIndex_HitCount-   = 0u;
/// \input ErrCust_GetActualErrorIndex_Param1      = 1u;
/// \input ErrCust_GetActualErrorIndex_RetVal      = 1u;
/// \input ErrCust_ulGetDtcCode_Param1             = 1u;
/// \input ErrCust_ulGetDtcCode_RetVal             = 10u;
/// \input  DAPI_BuildDECtxt_RetVal                = LDEH_E_SUCCESS;
///
/// - Expectations: 
///
/// \output  ErrCust_ulGetDtcCode_HitCount         = 1u;
/// \output  ErrCust_GetActualErrorIndex_HitCount  = 1u;
/// \output  ErrCust_GetActualErrorIndex_Param1    = 15u;
///
//-----------------------------------------------------------------------------
void Mt_Deh_DisappearanceConfirmed_TestCase4(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Deh_DisappearanceConfirmed_Param1     = 14u;
  ErrCust_ulGetDtcCode_HitCount         = 0u;
  ErrCust_GetActualErrorIndex_HitCount  = 0u;
  ErrCust_GetActualErrorIndex_Param1    = 1u;
  ErrCust_GetActualErrorIndex_RetVal    = 1u;
  ErrCust_ulGetDtcCode_Param1           = 1u;
  ErrCust_ulGetDtcCode_RetVal           = 10u;
  for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
  {
    Deh_asDehLogTab[ucIndx].ulDTCCode                = 10;
    Deh_asDehLogTab[ucIndx].eEventState              = eDeh_ApearedConf;
    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared     = 0;
    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Disapeared  = 0;
  }
  DAPI_BuildDECtxt_RetVal = LDEH_E_SUCCESS;

  //Step 3) Call FUT
  Deh_DisappearanceConfirmed(Deh_DisappearanceConfirmed_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_HitCount,         1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_HitCount,  1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_Param1,    15u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_DisappearanceConfirmed_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if Deh_DisappearanceConfirmed calls correctly DAPI_BuildDECtxt, 
///                     ErrCust_ulGetDtcCode, ErrCust_GetActualErrorIndex and DAPI_AddDE functions.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Deh_DisappearanceConfirmed_Param1  = 14u;
/// \input  ErrCust_ulGetDtcCode_RetVal        = 13u;
/// \input  DAPI_BuildDECtxt_RetVal            = LDEH_E_SUCCESS;
/// \input  DAPI_AddDE_Param2                  = E_FALSE;
/// \input  for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
/// \input  {
/// \input    Deh_asDehLogTab[ucIndx].ulDTCCode                = 0xFF;
/// \input    Deh_asDehLogTab[ucIndx].eEventState              = 0xFF;
/// \input    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared     = 0;
/// \input    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Disapeared  = 0;
/// \input  }
/// \input  Deh_asDehLogTab[7].eEventState  = eDeh_Init;
/// \input  Deh_asDehLogTab[7].ulDTCCode    = 13u;
///
/// - Expectations: 
///
/// \output   AL_UNITTEST_CHECK(Deh_asDehLogTab[7].eEventState,  eDeh_DisapearedConf_LGM, == );
/// \output   AL_UNITTEST_CHECK(DAPI_AddDE_Param2,               E_TRUE, == );
///
//-----------------------------------------------------------------------------
void Mt_Deh_DisappearanceConfirmed_TestCase5(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Deh_DisappearanceConfirmed_Param1  = 14u;
  ErrCust_ulGetDtcCode_RetVal        = 13u;
  DAPI_BuildDECtxt_RetVal            = LDEH_E_SUCCESS;
  DAPI_AddDE_Param2                  = E_FALSE;
  for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
  {
    Deh_asDehLogTab[ucIndx].ulDTCCode                = 0xFF;
    Deh_asDehLogTab[ucIndx].eEventState              = 0xFF;
    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared     = 0;
    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Disapeared  = 0;
  }

  Deh_asDehLogTab[7].eEventState  = eDeh_Init;
  Deh_asDehLogTab[7].ulDTCCode    = 13u;

  //Step 3) Call FUT
  Deh_DisappearanceConfirmed(Deh_DisappearanceConfirmed_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Deh_asDehLogTab[7].eEventState,  eDeh_DisapearedConf_LGM, == );
  AL_UNITTEST_CHECK(DAPI_AddDE_Param2,               E_TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_DisappearanceConfirmed_TestCase6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if Deh_DisappearanceConfirmed calls correctly DAPI_BuildDECtxt, 
///                     ErrCust_ulGetDtcCode, ErrCust_GetActualErrorIndex and DAPI_AddDE functions.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  Deh_DisappearanceConfirmed_Param1  = 14u;
/// \input  ErrCust_ulGetDtcCode_RetVal        = 13u;
/// \input  DAPI_BuildDECtxt_RetVal            = LDEH_E_ERR_NSYNC;
/// \input  DAPI_AddDE_Param2                  = E_FALSE;
/// \input  for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
/// \input  {
/// \input    Deh_asDehLogTab[ucIndx].ulDTCCode                = 0xFF;
/// \input    Deh_asDehLogTab[ucIndx].eEventState              = 0xFF;
/// \input    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared     = 0;
/// \input    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Disapeared  = 0;
/// \input  }
/// \input  Deh_asDehLogTab[7].eEventState  = eDeh_Init;
/// \input  Deh_asDehLogTab[7].ulDTCCode    = 13u;
///
/// - Expectations: 
///
/// \output  AL_UNITTEST_CHECK(Deh_asDehLogTab[7].eEventState, eDeh_Undef, == );
///
//-----------------------------------------------------------------------------
void Mt_Deh_DisappearanceConfirmed_TestCase6(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Deh_DisappearanceConfirmed_Param1  = 14u;
  ErrCust_ulGetDtcCode_RetVal        = 13u;
  DAPI_BuildDECtxt_RetVal            = LDEH_E_ERR_NSYNC;
  DAPI_AddDE_Param2                  = E_FALSE;
  for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
  {
    Deh_asDehLogTab[ucIndx].ulDTCCode                = 0xFF;
    Deh_asDehLogTab[ucIndx].eEventState              = 0xFF;
    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared     = 0;
    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Disapeared  = 0;
  }

  Deh_asDehLogTab[7].eEventState  = eDeh_Init;
  Deh_asDehLogTab[7].ulDTCCode    = 13u;

  //Step 3) Call FUT
  Deh_DisappearanceConfirmed(Deh_DisappearanceConfirmed_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Deh_asDehLogTab[7].eEventState,  eDeh_Undef, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_DisappearanceConfirmed
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Callback from Dem module. It is called at first detection of a fault confirmed absent
///                     (transition from absent to confirmed absent).
///                     In this momment the DEH frames shall be Nvm stored and sen
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Deh_DisappearanceConfirmed(void)
{
  Mt_Deh_DisappearanceConfirmed_TestCase1();
  Mt_Deh_DisappearanceConfirmed_TestCase2();
  Mt_Deh_DisappearanceConfirmed_TestCase3();
  Mt_Deh_DisappearanceConfirmed_TestCase4();
  Mt_Deh_DisappearanceConfirmed_TestCase5();
  Mt_Deh_DisappearanceConfirmed_TestCase6();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_APPLI_Send_Defaut_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test the correct behaviour of APPLI_Send_Defaut function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  LGM_InitMessage_HitCount             = 0u;
/// \input  IL_EnvoyerIpdu_HitCount              = 0u;
/// \input  IL_EnvoyerIpdu_RetVal                = IL_E_OK;
/// \input  LGM_InitMessage_Param1               = DATA_JDD;
/// \input  LGM_InitMessage_Param2[0]            = APPLI_Send_Defaut_Param1[7];
///
/// - Expectations: 
///
/// \output  AL_UNITTEST_CHECK(LGM_InitMessage_HitCount,   2u, == );
/// \output  AL_UNITTEST_CHECK(IL_EnvoyerIpdu_HitCount,    1u, == );
/// \output  AL_UNITTEST_CHECK(APPLI_Send_Defaut_RetVal,   LDEH_E_SUCCESS, == );
/// \output  AL_UNITTEST_CHECK(LGM_InitMessage_Param1,     HEADER_JDD, == );
/// \output  AL_UNITTEST_CHECK(LGM_InitMessage_Param2[0],  APPLI_Send_Defaut_Param1[0], == );
/// \output  AL_UNITTEST_CHECK(IL_EnvoyerIpdu_Param1,      EVT_DEFAUT_FRAME_ID, == );
///
//-----------------------------------------------------------------------------
void Mt_Deh_APPLI_Send_Defaut_TestCase1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  LGM_InitMessage_HitCount   = 0u;
  IL_EnvoyerIpdu_HitCount    = 0u;
  IL_EnvoyerIpdu_RetVal      = IL_E_OK;
  IL_EnvoyerIpdu_Param1      = 0u;
  LGM_InitMessage_Param1     = DATA_JDD;
  LGM_InitMessage_Param2[0]  = APPLI_Send_Defaut_Param1[7];

  //Step 3) Call FUT
  APPLI_Send_Defaut_RetVal  = APPLI_Send_Defaut(APPLI_Send_Defaut_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LGM_InitMessage_HitCount,   2u, == );
  AL_UNITTEST_CHECK(IL_EnvoyerIpdu_HitCount,    1u, == );
  AL_UNITTEST_CHECK(APPLI_Send_Defaut_RetVal,   LDEH_E_SUCCESS, == );
  AL_UNITTEST_CHECK(LGM_InitMessage_Param1,     HEADER_JDD, == );
  AL_UNITTEST_CHECK(LGM_InitMessage_Param2[0],  APPLI_Send_Defaut_Param1[0], == );
  AL_UNITTEST_CHECK(IL_EnvoyerIpdu_Param1,      EVT_DEFAUT_FRAME_ID, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_APPLI_Send_Defaut_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test the correct behaviour of APPLI_Send_Defaut function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  LGM_InitMessage_HitCount             = 0u;
/// \input  IL_EnvoyerIpdu_HitCount              = 0u;
/// \input  IL_EnvoyerIpdu_RetVal                = IL_E_COM_ID;
/// \input  LGM_InitMessage_Param1               = DATA_JDD;
///
/// - Expectations: 
///
/// \output  LGM_InitMessage_HitCount             = 2u;
/// \output  IL_EnvoyerIpdu_HitCount              = 1u;
/// \output  APPLI_Send_Defaut_RetVal             = LDEH_E_ERR_FATAL;
/// \output  LGM_InitMessage_Param1               = HEADER_JDD;
//-----------------------------------------------------------------------------
void Mt_Deh_APPLI_Send_Defaut_TestCase2(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  LGM_InitMessage_HitCount  = 0u;
  IL_EnvoyerIpdu_HitCount   = 0u;
  IL_EnvoyerIpdu_RetVal     = IL_E_COM_ID;
  LGM_InitMessage_Param1    = DATA_JDD;

  //Step 3) Call FUT
  APPLI_Send_Defaut_RetVal  = APPLI_Send_Defaut(APPLI_Send_Defaut_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LGM_InitMessage_HitCount,  2u, == );
  AL_UNITTEST_CHECK(IL_EnvoyerIpdu_HitCount,   1u, == );
  AL_UNITTEST_CHECK(APPLI_Send_Defaut_RetVal,  LDEH_E_ERR_FATAL, == );
  AL_UNITTEST_CHECK(LGM_InitMessage_Param1,    HEADER_JDD, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_APPLI_Send_Defaut
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test the correct behaviour of APPLI_Send_Defaut function
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Deh_APPLI_Send_Defaut(void)
{
  Mt_Deh_APPLI_Send_Defaut_TestCase1();
  Mt_Deh_APPLI_Send_Defaut_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_CheckSafetyConditions_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if we set the correct safety condition the API
///                         is called with E_TRUE value.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SysMon_LifePhases_HitCount =                              0u
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount =                            0u
/// \input Rte_Read_SysMon_LifePhases_Param1.ePhaseVie =                      eNormalMode
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = DEH_5KMH_THRESHOLD-100u;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty =                      SIG_VALID
/// \input DAPI_SetSafetyConditions_Param1 =                                  E_FALSE
/// \input DAPI_SetSafetyConditions_HitCount =                                0u
///
///   - Expectations:
/// \output Rte_Read_SysMon_LifePhases_HitCount =                             1u
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount =                           1u
/// \output DAPI_SetSafetyConditions_Param1 =                                 E_TRUE
/// \output DAPI_SetSafetyConditions_HitCount =                               1u
///
//-----------------------------------------------------------------------------
void Mt_Deh_CheckSafetyConditions_TestCase1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_LifePhases_HitCount                               = 0u;
  Rte_Read_SysMon_VehicleSpeed_HitCount                             = 0u;
  Rte_Read_SysMon_LifePhases_Param1.ePhaseVie                       = eNormalMode;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = DEH_5KMH_THRESHOLD;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                       = SIG_VALID;
  DAPI_SetSafetyConditions_Param1                                   = E_FALSE;
  DAPI_SetSafetyConditions_HitCount                                 = 0u;

  //Step 3) Call FUT
  Deh_CheckSafetyConditions();

  //Step 4) Check expected output values	
  AL_UNITTEST_CHECK(Rte_Read_SysMon_LifePhases_HitCount,    1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,  1u, == );
  AL_UNITTEST_CHECK(DAPI_SetSafetyConditions_Param1,        E_TRUE, == );
  AL_UNITTEST_CHECK(DAPI_SetSafetyConditions_HitCount,      1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_CheckSafetyConditions_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if we set the correct safety condition the API
///                         is called with E_FALSE value.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SysMon_LifePhases_HitCount =                              0u
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount =                            0u
/// \input Rte_Read_SysMon_LifePhases_Param1.ePhaseVie =                      eStandBy
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 600u
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty =                      SIG_VALID
/// \input DAPI_SetSafetyConditions_Param1 =                                  E_TRUE
/// \input DAPI_SetSafetyConditions_HitCount =                                0u
/// 
///
///   - Expectations:
/// \output Rte_Read_SysMon_LifePhases_HitCount =                             1u
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount =                           1u
/// \output DAPI_SetSafetyConditions_Param1 =                                 E_FALSE
/// \output DAPI_SetSafetyConditions_HitCount =                               1u
///
//-----------------------------------------------------------------------------
void Mt_Deh_CheckSafetyConditions_TestCase2(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_SysMon_LifePhases_HitCount                               = 0u;
  Rte_Read_SysMon_VehicleSpeed_HitCount                             = 0u;
  Rte_Read_SysMon_LifePhases_Param1.ePhaseVie                       = eStandBy;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = 600u; //vehicle speed
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                       = SIG_VALID;
  DAPI_SetSafetyConditions_Param1                                   = E_TRUE;
  DAPI_SetSafetyConditions_HitCount                                 = 0u;

  //Step 3) Call FUT
  Deh_CheckSafetyConditions();

    //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_LifePhases_HitCount,    1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,  1u, == );
  AL_UNITTEST_CHECK(DAPI_SetSafetyConditions_Param1,        E_FALSE, == );
  AL_UNITTEST_CHECK(DAPI_SetSafetyConditions_HitCount,      1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_CheckSafetyConditions
///
///
/// \Test Case Description
///    - Test subject:  Check that the function processes the check safety conditions
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Deh_CheckSafetyConditions(void)
{
  Mt_Deh_CheckSafetyConditions_TestCase1();
  Mt_Deh_CheckSafetyConditions_TestCase2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_APPLI_DENotAck
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if the DTC is set when the API is called
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_SetEventStatus_Param1                             = 0u
/// \input Dem_SetEventStatus_Param2                             = DEM_EVENT_STATUS_PASSED
/// \input Dem_SetEventStatus_HitCount                           = 0u
/// 
///
///   - Expectations:
/// \output Dem_SetEventStatus_Param1                            = MED_NOT_ACK
/// \output Dem_SetEventStatus_Param2                            = DEM_EVENT_STATUS_FAILED
///
//-----------------------------------------------------------------------------
void Mt_Deh_APPLI_DENotAck(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Dem_SetEventStatus_Param1    = 0u;
  Dem_SetEventStatus_Param2    = DEM_EVENT_STATUS_PASSED;
  Dem_SetEventStatus_HitCount  = 0u;
  
  //Step 3) Call FUT
  APPLI_DENotAck(0u);
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,  MED_NOT_ACK, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2,  DEM_EVENT_STATUS_FAILED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_APPLI_DEAck
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if the DTC is reset when the API is called
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_SetEventStatus_Param1                             = 0u
/// \input Dem_SetEventStatus_Param2                             = DEM_EVENT_STATUS_PASSED
/// \input Dem_SetEventStatus_HitCount                           = 0u
///
///   - Expectations:
/// \output Dem_SetEventStatus_Param1                           = MED_NOT_ACK
/// \output Dem_SetEventStatus_Param2                           = DEM_EVENT_STATUS_PASSED
///
//-----------------------------------------------------------------------------
void Mt_Deh_APPLI_DEAck(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Dem_SetEventStatus_Param1    = 0;
  Dem_SetEventStatus_Param2    = DEM_EVENT_STATUS_FAILED;
  Dem_SetEventStatus_HitCount  = 0u;

  //Step 3) Call FUT
  APPLI_DEAck(0u);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,  MED_NOT_ACK, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2,  DEM_EVENT_STATUS_PASSED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Recover_UCE_ABS_RL_F_1_HDC
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that LGM callback for recovery from NvM of 
///                     UCE_ABS_RL_F_1_HDC counter
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input NvmBlockNmBackupCounters.ucUCE_ABS_RL_F_1_HDC_Counter    = 1u;
/// \input Recover_UCE_ABS_RL_F_1_HDC_Param1[1]                     = 2u;
///
///   - Expectations:
/// \output Recover_UCE_ABS_RL_F_1_HDC_Param1                       = 1u;
///
//-----------------------------------------------------------------------------
void Mt_Recover_UCE_ABS_RL_F_1_HDC(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  NvmBlockNmBackupCounters.ucUCE_ABS_RL_F_1_HDC_Counter  = 1u;
  Recover_UCE_ABS_RL_F_1_HDC_Param1                      = 2u;

  //Step 3) Call FUT
  Recover_UCE_ABS_RL_F_1_HDC(&Recover_UCE_ABS_RL_F_1_HDC_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Recover_UCE_ABS_RL_F_1_HDC_Param1,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Backup_UCE_ABS_RL_F_1_HDC
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that LGM callback for backup in NvM of 
///                     UCE_ABS_RL_F_1_HDC counter
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input NvmBlockNmBackupCounters.ucUCE_ABS_RL_F_1_HDC_Counter    = 1u;
/// \input Recover_UCE_ABS_RL_F_1_HDC_Param1                        = 2u;
/// 
///
///   - Expectations:
/// \output NvmBlockNmBackupCounters.ucUCE_ABS_RL_F_1_HDC_Counter    = 2u;
///
//-----------------------------------------------------------------------------
void Mt_Backup_UCE_ABS_RL_F_1_HDC(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  NvmBlockNmBackupCounters.ucUCE_ABS_RL_F_1_HDC_Counter  = 1u;
  Backup_UCE_ABS_RL_F_1_HDC_Param1                       = 2u;

  //Step 3) Call FUT
  Backup_UCE_ABS_RL_F_1_HDC(Backup_UCE_ABS_RL_F_1_HDC_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvmBlockNmBackupCounters.ucUCE_ABS_RL_F_1_HDC_Counter,  2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Default_Mute_DisappearedConfirmed
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that LGM callback for CAN Mute default disappearance confirmed
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  DAPI_BuildDECtxt_HitCount             = 0u
/// \input  ErrCust_ulGetDtcCode_HitCount         = 0u
/// \input  ErrCust_GetActualErrorIndex_HitCount  = 0u
/// \input  DAPI_AddDE_HitCount                   = 0u
/// \input  DAPI_AddDE_Param2                     = E_FALSE
/// \input  DAPI_BuildDECtxt_Param1               = 0u
/// \input  DAPI_BuildDECtxt_Param2               = LDEH_E_APPEAR
/// \input  DAPI_BuildDECtxt_Param3               = 0u
/// \input  DAPI_BuildDECtxt_Param4               = DEH_DTC_FORMAT_ID
/// \input  DAPI_BuildDECtxt_Param5               = 0u
/// \input  ucEcuCode                             = 2u
/// \input  ErrCust_GetActualErrorIndex_RetVal    = 2u
/// \imput  Deh_DisappearanceConfirmed_Param1     = Mute_ECU
/// \input Dem_SetEventStatus_Param1              = 0u
/// \input Dem_SetEventStatus_Param2              = DEM_EVENT_STATUS_FAILED
/// \input Dem_SetEventStatus_HitCount            = 0u
/// 
///
///   - Expectations:
///
/// \output  DAPI_BuildDECtxt_HitCount             = 1u;
/// \output  ErrCust_ulGetDtcCode_HitCount         = 1u;
/// \output  ErrCust_GetActualErrorIndex_HitCount  = 1u;
/// \output  DAPI_AddDE_HitCount                   = 1u;
/// \output  DAPI_AddDE_Param2                     = E_TRUE;
/// \output  DAPI_BuildDECtxt_Param2               = LDEH_E_DISAPPEAR;
/// \output  DAPI_BuildDECtxt_Param4               = DEH_DTC_FORMAT_ID;
/// \output  DAPI_BuildDECtxt_Param5               = 0u;
/// \output  DAPI_BuildDECtxt_Param1               = 0u;
/// \output  DAPI_BuildDECtxt_Param3               = 10u;
/// \output  ErrCust_GetActualErrorIndex_Param1    = 80u;
/// \output Dem_SetEventStatus_Param1              = Mute_ECU
/// \output Dem_SetEventStatus_Param2              = DEM_EVENT_STATUS_PASSED
/// \output Dem_SetEventStatus_HitCount            =1u
///
//-----------------------------------------------------------------------------
void Mt_Default_Mute_DisappearedConfirmed(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values  
  ErrCust_ulGetDtcCode_HitCount         = 0u;
  ErrCust_GetActualErrorIndex_HitCount  = 0u;
  DAPI_AddDE_Param2                     = E_FALSE;
  DAPI_AddDE_Param1                     = 0u;
  DAPI_AddDE_HitCount                   = 0u;
  DAPI_BuildDECtxt_Param1               = 0u;
  DAPI_BuildDECtxt_Param2               = LDEH_E_APPEAR;
  DAPI_BuildDECtxt_Param3               = 0u;
  DAPI_BuildDECtxt_Param4               = DEH_DTC_FORMAT_ID;
  DAPI_BuildDECtxt_Param5               = 0u;
  DAPI_BuildDECtxt_HitCount             = 0u;
  DAPI_BuildDECtxt_RetVal               = LDEH_E_SUCCESS;
  ucEcuCode                             = 2u;
  ErrCust_GetActualErrorIndex_RetVal    = 2u;
  Deh_DisappearanceConfirmed_Param1     = Mute_ECU;
  Dem_SetEventStatus_Param1             = 0u;
  Dem_SetEventStatus_Param2             = DEM_EVENT_STATUS_FAILED;
  Dem_SetEventStatus_HitCount           = 0u;

  //Step 3) Call FUT
  Default_Mute_DisappearedConfirmed();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_HitCount,             1u, == );
  AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_HitCount,         1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_HitCount,  1u, == );
  AL_UNITTEST_CHECK(DAPI_AddDE_HitCount,                   1u, == );
  AL_UNITTEST_CHECK(DAPI_AddDE_Param2,                     E_TRUE, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param2,               LDEH_E_DISAPPEAR, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param4,               DEH_DTC_FORMAT_ID, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param5,               2u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param3,               2u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_Param1,    82, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,             Mute_ECU, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2,             DEM_EVENT_STATUS_PASSED, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,           1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Default_Mute_DisappearedDetected
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that LGM callback for CAN Mute default disappearance detected
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input ErrCust_ulGetDtcCode_HitCount         = 0u
/// \input ErrCust_GetActualErrorIndex_HitCount  = 0u
/// \input DAPI_AddDE_HitCount                   = 0u
/// 
///
///   - Expectations:
///
/// \output ErrCust_GetActualErrorIndex_Param1     = 82u
/// \output ErrCust_ulGetDtcCode_HitCount          = 1u
/// \output ErrCust_GetActualErrorIndex_HitCount   = 1u
///
//-----------------------------------------------------------------------------
void Mt_Default_Mute_DisappearedDetected(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  ErrCust_ulGetDtcCode_HitCount         = 0u;
  ErrCust_GetActualErrorIndex_Param1    = 0u;
  ErrCust_GetActualErrorIndex_HitCount  = 0u;
  
  //Step 3) Call FUT
  Default_Mute_DisappearedDetected();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_Param1,    82u, == );
  AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_HitCount,         1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_HitCount,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Recover_C_Mute
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that LGM callback for recovery from NvM of C_Mute counter
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input NvmBlockNmBackupCounters.ucC_Mute_Counter             = 1u
/// \input Recover_C_Mute_Param1                                 = 2u
///
///   - Expectations:
///
/// \output Recover_C_Mute_Param1                                = 1u
///
//-----------------------------------------------------------------------------
void Mt_Recover_C_Mute(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values  
  NvmBlockNmBackupCounters.ucC_Mute_Counter  = 1u;
  Recover_C_Mute_Param1                      = 2u;

  //Step 3) Call FUT
  Recover_C_Mute(&Recover_C_Mute_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Recover_C_Mute_Param1,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Backup_C_Mute
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that LGM callback for backup in NvM of C_Mute counter
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input NvmBlockNmBackupCounters.ucC_Mute_Counter             = 1u
/// \input Backup_C_Mute_Param1                                  = 2u
///
///   - Expectations:
///
/// \output Backup_C_Mute_Param1                                 = 2u
///
//-----------------------------------------------------------------------------
void Mt_Backup_C_Mute(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values   
  NvmBlockNmBackupCounters.ucC_Mute_Counter  = 1u;
  Backup_C_Mute_Param1                       = 2u;

  //Step 3) Call FUT
  Backup_C_Mute(Backup_C_Mute_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvmBlockNmBackupCounters.ucC_Mute_Counter,  2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Default_Mute_AppearedConfirmed
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test that LGM callback for CAN Mute default appearance confirmed
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_SetEventStatus_Param1               = 0u
/// \input Dem_SetEventStatus_Param2               = DEM_EVENT_STATUS_PASSED
/// \input Dem_SetEventStatus_HitCount             = 0u
/// \input DAPI_AddDE_HitCount                     = 0u;
/// \input ErrCust_GetStatusOfDtc_RetVal           = 0u;
/// \input ErrCust_GetActualErrorIndex_RetVal      = 0u; // status flags
/// \input ErrCust_GetActualErrorIndex_HitCount    = 0u; // status flags
/// \input ErrCust_GetStatusOfDtc_HitCount         = 0u;
/// \input ErrCust_ulGetDtcCode_HitCount           = 0u;
/// \input DAPI_BuildDECtxt_HitCount               = 0u;
/// \input DAPI_AddDE_Param2                       = E_FALSE;
/// \input S_DE[0u].Au8_FirstFrame[DAPI_D_DTC_B0]  = 1u;
/// \input S_DE[0u].Au8_FirstFrame[DAPI_D_DTC_B1]  = 1u;
/// \input S_DE[0u].Au8_FirstFrame[DAPI_D_DTC_B2]  = 1u;
/// \input ucEcuCode                               = 5u;
/// \input DAPI_AddDE_Param1                       = 0u;
/// \input DAPI_BuildDECtxt_Param1                 = 0u;
/// \input DAPI_BuildDECtxt_Param2                 = LDEH_E_DISAPPEAR;
/// \input DAPI_BuildDECtxt_Param3                 = 0u;
/// \input DAPI_BuildDECtxt_Param4                 = DEH_DTC_FORMAT_ID;
/// \input DAPI_BuildDECtxt_Param5                 = 0u;
/// \input Deh_AppearanceConfirmed_Param1          = Mute_ECU;
/// \input Deh_TableFullStatus                     = FALSE;
///
///   - Expectations:
///
/// \output Deh_TableFullStatus                   = TRUE
/// \output Dem_SetEventStatus_Param1             = Mute_ECU
/// \output Dem_SetEventStatus_Param2             = DEM_EVENT_STATUS_FAILED
/// \output Dem_SetEventStatus_HitCount           = 1u
/// \output DAPI_AddDE_HitCount                   = 0u
/// \output ErrCust_GetStatusOfDtc_HitCount       = 0u
/// \output ErrCust_GetActualErrorIndex_HitCount  = 0u
/// \output DAPI_BuildDECtxt_Param5               = 1u
/// \output DAPI_BuildDECtxt_Param1               = 0u;
/// \output DAPI_BuildDECtxt_Param2               = LDEH_E_DISAPPEAR;
/// \output DAPI_BuildDECtxt_Param3               = 0u;
/// \output DAPI_BuildDECtxt_Param4               = DEH_DTC_FORMAT_ID;
/// \output  DAPI_AddDE_Param1                    = &S_DE[0u];
/// \output ErrCust_GetActualErrorIndex_Param1    = 82u
///
//-----------------------------------------------------------------------------
void Mt_Default_Mute_AppearedConfirmed(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Dem_SetEventStatus_Param1               = 0u;
  Dem_SetEventStatus_Param2               = DEM_EVENT_STATUS_PASSED;
  Dem_SetEventStatus_HitCount             = 0u;
  DAPI_AddDE_HitCount                     = 0u;
  ErrCust_GetStatusOfDtc_RetVal           = 0u;
  ErrCust_GetActualErrorIndex_RetVal      = 0u; // status flags
  ErrCust_GetActualErrorIndex_HitCount    = 0u; // status flags
  ErrCust_GetStatusOfDtc_HitCount         = 0u;
  ErrCust_ulGetDtcCode_HitCount           = 0u;
  DAPI_BuildDECtxt_HitCount               = 0u;
  DAPI_AddDE_Param2                       = E_FALSE;
  S_DE[0u].Au8_FirstFrame[DAPI_D_DTC_B0]  = 1u;
  S_DE[0u].Au8_FirstFrame[DAPI_D_DTC_B1]  = 1u;
  S_DE[0u].Au8_FirstFrame[DAPI_D_DTC_B2]  = 1u;
  ucEcuCode                               = 5u;
  DAPI_BuildDECtxt_Param1                 = 0u;
  DAPI_BuildDECtxt_Param2                 = LDEH_E_DISAPPEAR;
  DAPI_BuildDECtxt_Param3                 = 0u;
  DAPI_BuildDECtxt_Param4                 = DEH_DTC_FORMAT_ID;
  DAPI_BuildDECtxt_Param5                 = 0u;
  DAPI_BuildDECtxt_RetVal                 = LDEH_E_SUCCESS;
  Deh_AppearanceConfirmed_Param1          = Mute_ECU;
  Deh_TableFullStatus                     = FALSE;
  
  //Step 3) Call FUT
  Default_Mute_AppearedConfirmed();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Deh_TableFullStatus,                   TRUE, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,           1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,             Mute_ECU, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2,             DEM_EVENT_STATUS_FAILED, == );
  AL_UNITTEST_CHECK(ErrCust_GetStatusOfDtc_HitCount,       1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_HitCount,  1u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_HitCount,             0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param5,               0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param1,               0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param2,               LDEH_E_DISAPPEAR, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param3,               0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param4,               DEH_DTC_FORMAT_ID, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_Param1,    82u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Default_Mute_AppearedDetected
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test that LGM callback for CAN Mute default appearance detected
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  DAPI_BuildDECtxt_HitCount             = 0u;
/// \input  ErrCust_ulGetDtcCode_HitCount         = 0u;
/// \input  ErrCust_GetActualErrorIndex_HitCount  = 0u;
/// \input  Deh_AppearanceDetected_Param1         = Mute_ECU;
/// \input  DAPI_BuildDECtxt_Param2               = LDEH_E_DISAPPEAR;
/// \input  ErrCust_ulGetDtcCode_RetVal           = 5u;
/// \input  DAPI_BuildDECtxt_Param4               = DEH_R_ECU_CODE;
/// \input  DAPI_BuildDECtxt_Param5               = 2u;
/// \input  ucEcuCode                             = 1u;
/// \input  ErrCust_GetActualErrorIndex_RetVal    = 2u;
/// \input  ErrCust_ulGetDtcCode_Param1           = 3u;
/// \input DAPI_BuildDECtxt_Param1                = 0u;
/// \input DAPI_BuildDECtxt_Param3                = 0u;
///
/// - Expectations: 
///
/// \output  DAPI_BuildDECtxt_HitCount             = 1u
/// \output  ErrCust_ulGetDtcCode_HitCount         = 1u
/// \output  ErrCust_GetActualErrorIndex_HitCount  = 1u
/// \output  ErrCust_GetActualErrorIndex_Param1    = 82u
/// \output  DAPI_BuildDECtxt_Param2               = LDEH_E_APPEAR
/// \output  DAPI_BuildDECtxt_Param3               = 5u
/// \output  DAPI_BuildDECtxt_Param4               = DEH_DTC_FORMAT_ID
/// \output  DAPI_BuildDECtxt_Param5               = 1u
/// \output  ErrCust_ulGetDtcCode_Param1           = 2u
///
//-----------------------------------------------------------------------------
void Mt_Default_Mute_AppearedDetected(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  DAPI_BuildDECtxt_HitCount             = 0u;
  ErrCust_ulGetDtcCode_HitCount         = 0u;
  ErrCust_GetActualErrorIndex_HitCount  = 0u;
  Deh_AppearanceDetected_Param1         = Mute_ECU;
  DAPI_BuildDECtxt_Param2               = LDEH_E_DISAPPEAR;
  ErrCust_ulGetDtcCode_RetVal           = 5u;
  DAPI_BuildDECtxt_Param4               = DEH_R_ECU_CODE;
  DAPI_BuildDECtxt_Param5               = 2u;
  DAPI_BuildDECtxt_RetVal               = LDEH_E_SUCCESS;
  ucEcuCode                             = 1u;
  ErrCust_GetActualErrorIndex_RetVal    = 2u;
  ErrCust_GetActualErrorIndex_Param1    = 0u;
  ErrCust_ulGetDtcCode_Param1           = 3u;
  DAPI_BuildDECtxt_Param1               = 0u;
  DAPI_BuildDECtxt_Param3               = 0u;

  //Step 3) Call FUT
  Default_Mute_AppearedDetected();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_HitCount,             1u, == );
  AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_HitCount,         1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_HitCount,  1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_Param1,    82u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param2,               LDEH_E_APPEAR, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param3,               5u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param4,               DEH_DTC_FORMAT_ID, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param5,               1u, == );
  AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_Param1,           2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Bus_Off_Callback
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that LGM callback for Buss Off detection
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input NvM_WriteBlock_Param1           = 1u
/// \input NvM_WriteBlock_HitCount         = 0u
///
///   - Expectations:
///
/// \output NvM_WriteBlock_Param1          = NvmBlockNmBackupCountersId
/// \output NvM_WriteBlock_HitCount        = 1u
///
//-----------------------------------------------------------------------------
void Mt_Bus_Off_Callback(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  NvM_WriteBlock_Param1    = 1u;
  NvM_WriteBlock_HitCount  = 0u;
  
  //Step 3) Call FUT
  Bus_Off_Callback();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvM_WriteBlock_Param1,    NvmBlockNmBackupCountersId, == );
  AL_UNITTEST_CHECK(NvM_WriteBlock_HitCount,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Recover_C_BusOff
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that LGM callback for recovery from NvM of C_BussOff counte
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input NvmBlockNmBackupCounters.ucC_BusOff_Counter    = 1u
/// \input Recover_C_BusOff_Param1                        = 2u
///
///   - Expectations:
///
/// \output Recover_C_BusOff_Param1                       = 1u
///
//-----------------------------------------------------------------------------
void Mt_Recover_C_BusOff(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  NvmBlockNmBackupCounters.ucC_BusOff_Counter  = 1u;
  Recover_C_BusOff_Param1                      = 2u;

  //Step 3) Call FUT
  Recover_C_BusOff(&Recover_C_BusOff_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Recover_C_BusOff_Param1,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Backup_C_BusOff
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that LGM callback for backup in NvM of C_BussOff counter
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input NvmBlockNmBackupCounters.ucC_BusOff_Counter   = 1u
/// \input Recover_C_BusOff_Param1                       = 2u
///
///   - Expectations:
///
/// \output NvmBlockNmBackupCounters.ucC_BusOff_Counter  = 2u
///
//-----------------------------------------------------------------------------
void Mt_Backup_C_BusOff(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values   
  NvmBlockNmBackupCounters.ucC_BusOff_Counter  = 1u;
  Backup_C_BusOff_Param1                       = 2u;

  //Step 3) Call FUT
  Backup_C_BusOff(Backup_C_BusOff_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvmBlockNmBackupCounters.ucC_BusOff_Counter,  2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Default_BusOff_DisappearedConfirmed
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that LGM callback for Bus Off default appearance confirmed
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DAPI_AddDE_HitCount                     = 0u
/// \input Dem_SetEventStatus_Param1               = 0u
/// \input Dem_SetEventStatus_Param2               = DEM_EVENT_STATUS_FAILED
/// \input Dem_SetEventStatus_HitCount             = 0u
/// \input DAPI_AddDE_HitCount                     = 0u
/// \input ErrCust_GetStatusOfDtc_RetVal           = 0u
/// \input ErrCust_GetActualErrorIndex_RetVal      = 0u
/// \input ErrCust_GetActualErrorIndex_HitCount    = 0u
/// \input ErrCust_GetStatusOfDtc_HitCount         = 0u
/// \input ErrCust_ulGetDtcCode_HitCount           = 0u
/// \input S_DE[0u].Au8_FirstFrame[DAPI_D_DTC_B0]  = 1u
/// \input S_DE[0u].Au8_FirstFrame[DAPI_D_DTC_B1]  = 1u
/// \input S_DE[0u].Au8_FirstFrame[DAPI_D_DTC_B2]  = 1u
/// \input ucEcuCode                               = 5u
/// \input DAPI_AddDE_Param1                       = 0u;
/// \input DAPI_BuildDECtxt_Param1                 = 0u;
/// \input DAPI_BuildDECtxt_Param2                 = LDEH_E_DISAPPEAR;
/// \input DAPI_BuildDECtxt_Param3                 = 0u;
/// \input DAPI_BuildDECtxt_Param4                 = DEH_DTC_FORMAT_ID;
/// \input DAPI_BuildDECtxt_Param5                 = 0u;
/// \input Deh_AppearanceConfirmed_Param1          = SUBCAN_BUSOFF;
/// \input Dem_Set_Init_Window_Param1              = TRUE
/// \input Dem_Set_Init_Window_HitCount            = 0u
///
///   - Expectations:
///
/// \output DAPI_AddDE_HitCount                    = 1u
/// \output Dem_SetEventStatus_Param1              = SUBCAN_BUSOFF
/// \output Dem_SetEventStatus_Param2              = DEM_EVENT_STATUS_PASSED
/// \output Dem_SetEventStatus_HitCount            =1u
/// \output  DAPI_BuildDECtxt_HitCount             = 0u;
/// \output  ErrCust_ulGetDtcCode_HitCount         = 1u;
/// \output  ErrCust_GetActualErrorIndex_HitCount  = 1u;
/// \output  DAPI_AddDE_HitCount                   = 0u;
/// \output  DAPI_AddDE_Param2                     = E_FALSE;
/// \output  DAPI_BuildDECtxt_Param2               = LDEH_E_APPEAR;
/// \output  DAPI_BuildDECtxt_Param4               = DEH_DTC_FORMAT_ID;
/// \output  DAPI_BuildDECtxt_Param5               = 0u;
/// \output  DAPI_BuildDECtxt_Param1               = 0u;
/// \output  DAPI_BuildDECtxt_Param3               = 0u;
/// \output  ErrCust_GetActualErrorIndex_Param1    = 90u;
/// \output Dem_Set_Init_Window_Param1             = FALSE
/// \output Dem_Set_Init_Window_HitCount           = 1u
///
//-----------------------------------------------------------------------------
void Mt_Default_BusOff_DisappearedConfirmed(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Dem_SetEventStatus_Param1             = 0u;
  Dem_SetEventStatus_Param2             = DEM_EVENT_STATUS_FAILED;
  Dem_SetEventStatus_HitCount           = 0u;
  DAPI_BuildDECtxt_HitCount             = 0u;
  ErrCust_ulGetDtcCode_HitCount         = 0u;
  ErrCust_GetActualErrorIndex_HitCount  = 0u;
  DAPI_AddDE_HitCount                   = 0u;
  DAPI_AddDE_Param2                     = E_FALSE;
  DAPI_AddDE_Param1                     = 0u;
  DAPI_BuildDECtxt_Param1               = 0u;
  DAPI_BuildDECtxt_Param2               = LDEH_E_APPEAR;
  DAPI_BuildDECtxt_Param3               = 0u;
  DAPI_BuildDECtxt_Param4               = DEH_DTC_FORMAT_ID;
  DAPI_BuildDECtxt_Param5               = 0u;
  DAPI_BuildDECtxt_RetVal               = LDEH_E_SUCCESS;
  ucEcuCode                             = 2u;
  ErrCust_GetActualErrorIndex_RetVal    = 2u;
  Deh_DisappearanceConfirmed_Param1     = SUBCAN_BUSOFF;
  Dem_Set_Init_Window_Param1            = TRUE;
  Dem_Set_Init_Window_HitCount          = 0u;

  //Step 3) Call FUT
  Default_BusOff_DisappearedConfirmed();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,           1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,             SUBCAN_BUSOFF, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2,             DEM_EVENT_STATUS_PASSED, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_HitCount,             0u, == );
  AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_HitCount,         1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_HitCount,  1u, == );
  AL_UNITTEST_CHECK(DAPI_AddDE_HitCount,                   0u, == );
  AL_UNITTEST_CHECK(DAPI_AddDE_Param1,                     0u, == );
  AL_UNITTEST_CHECK(DAPI_AddDE_Param2,                     E_FALSE, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param2,               LDEH_E_APPEAR, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param4,               DEH_DTC_FORMAT_ID, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param5,               0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param1,               0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param3,               0u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_Param1,    106u, == );
  AL_UNITTEST_CHECK(Dem_Set_Init_Window_Param1,            FALSE, == );
  AL_UNITTEST_CHECK(Dem_Set_Init_Window_HitCount,          1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Default_BusOff_DisappearedDetected
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that LGM callback for Bus Off default appearance detected
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DAPI_BuildDECtxt_HitCount             = 0u
/// \input ErrCust_ulGetDtcCode_HitCount         = 0u
/// \input ErrCust_GetActualErrorIndex_HitCount  = 0u
/// \input DAPI_BuildDECtxt_Param2               = 0u
/// \input DAPI_BuildDECtxt_Param4               = 0u
/// \input DAPI_BuildDECtxt_Param1               = 0u
/// \input DAPI_BuildDECtxt_Param3               = 0u
/// \input DAPI_BuildDECtxt_Param5               = 0u
/// \input ucEcuCode                             = 1u
///
///   - Expectations:
///
/// \output DAPI_BuildDECtxt_HitCount             = 0u
/// \output ErrCust_ulGetDtcCode_HitCount         = 1u
/// \output ErrCust_GetActualErrorIndex_HitCount  = 1u
/// \input DAPI_BuildDECtxt_Param2                = 0u
/// \input DAPI_BuildDECtxt_Param4                = 0u
/// \input DAPI_BuildDECtxt_Param5                = 0u
/// \input DAPI_BuildDECtxt_Param1                = 0u
/// \input DAPI_BuildDECtxt_Param3                = 0u
///
//-----------------------------------------------------------------------------
void Mt_Default_BusOff_DisappearedDetected(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  DAPI_BuildDECtxt_HitCount             = 0u;
  ErrCust_ulGetDtcCode_HitCount         = 0u;
  ErrCust_GetActualErrorIndex_HitCount  = 0u;
  DAPI_BuildDECtxt_Param2               = 0u;
  DAPI_BuildDECtxt_Param4               = 0u;
  DAPI_BuildDECtxt_Param1               = 0u;
  DAPI_BuildDECtxt_Param3               = 0u;
  DAPI_BuildDECtxt_Param5               = 0u;
  ucEcuCode                             = 1u;

  //Step 3) Call FUT
  Default_BusOff_DisappearedDetected();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_HitCount,             0u, == );
  AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_HitCount,         1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_HitCount,  1u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param2,               0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param4,               0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param5,               0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param1,               0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param3,               0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Default_BusOff_AppearedConfirmed
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that LGM callback for Bus Off default appearance confirmed
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DAPI_AddDE_HitCount                     = 0u
/// \input Dem_SetEventStatus_Param1               = 0u
/// \input Dem_SetEventStatus_Param2               = DEM_EVENT_STATUS_PASSED
/// \input Dem_SetEventStatus_HitCount             = 0u
/// \input DAPI_AddDE_HitCount                     = 0u
/// \input ErrCust_GetStatusOfDtc_RetVal           = 0u
/// \input ErrCust_GetActualErrorIndex_RetVal      = 0u
/// \input ErrCust_GetActualErrorIndex_HitCount    = 0u
/// \input ErrCust_GetStatusOfDtc_HitCount         = 0u
/// \input ErrCust_ulGetDtcCode_HitCount           = 0u
/// \input S_DE[0u].Au8_FirstFrame[DAPI_D_DTC_B0]  = 1u
/// \input S_DE[0u].Au8_FirstFrame[DAPI_D_DTC_B1]  = 1u
/// \input S_DE[0u].Au8_FirstFrame[DAPI_D_DTC_B2]  = 1u
/// \input ucEcuCode                               = 5u
/// \input DAPI_AddDE_Param1                       = 0u;
/// \input DAPI_BuildDECtxt_Param1                 = 0u;
/// \input DAPI_BuildDECtxt_Param2                 = LDEH_E_DISAPPEAR;
/// \input DAPI_BuildDECtxt_Param3                 = 0u;
/// \input DAPI_BuildDECtxt_Param4                 = DEH_DTC_FORMAT_ID;
/// \input DAPI_BuildDECtxt_Param5                 = 0u;
/// \input Deh_AppearanceConfirmed_Param1          = SUBCAN_BUSOFF;
/// \input Dem_Set_Init_Window_Param1              = FALSE
/// \input Dem_Set_Init_Window_HitCount            = 0u
///
///   - Expectations:
///
/// \output DAPI_AddDE_HitCount                   = 1u
/// \output Dem_SetEventStatus_Param1             = SUBCAN_BUSOFF
/// \output Dem_SetEventStatus_Param2             = DEM_EVENT_STATUS_FAILED
/// \output Dem_SetEventStatus_HitCount           = 1u
/// \output DAPI_AddDE_HitCount                   = 0u
/// \output ErrCust_GetStatusOfDtc_HitCount       = 0u
/// \output ErrCust_GetActualErrorIndex_HitCount  = 0u
/// \output DAPI_BuildDECtxt_Param5               = 1u
/// \output DAPI_BuildDECtxt_Param1               = 0u;
/// \output DAPI_BuildDECtxt_Param2               = LDEH_E_DISAPPEAR;
/// \output DAPI_BuildDECtxt_Param3               = 0u;
/// \output DAPI_BuildDECtxt_Param4               = DEH_DTC_FORMAT_ID;
/// \output  DAPI_AddDE_Param1                    = &S_DE[0u];
/// \output ErrCust_GetActualErrorIndex_Param1    = 90u
/// \output Dem_Set_Init_Window_Param1            = TRUE
/// \output Dem_Set_Init_Window_HitCount          = 1u
///
//-----------------------------------------------------------------------------
void Mt_Default_BusOff_AppearedConfirmed(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Dem_SetEventStatus_Param1               = 0u;
  Dem_SetEventStatus_Param2               = DEM_EVENT_STATUS_PASSED;
  Dem_SetEventStatus_HitCount             = 0u;
  DAPI_AddDE_HitCount                     = 0u;
  ErrCust_GetStatusOfDtc_RetVal           = 0u;
  ErrCust_GetActualErrorIndex_RetVal      = 0u; // status flags
  ErrCust_GetActualErrorIndex_HitCount    = 0u; // status flags
  ErrCust_GetStatusOfDtc_HitCount         = 0u;
  ErrCust_ulGetDtcCode_HitCount           = 0u;
  DAPI_BuildDECtxt_HitCount               = 0u;
  DAPI_AddDE_Param2                       = E_FALSE;
  S_DE[0u].Au8_FirstFrame[DAPI_D_DTC_B0]  = 1u;
  S_DE[0u].Au8_FirstFrame[DAPI_D_DTC_B1]  = 1u;
  S_DE[0u].Au8_FirstFrame[DAPI_D_DTC_B2]  = 1u;
  ucEcuCode                               = 5u;
  DAPI_AddDE_Param1                       = 0u;
  DAPI_BuildDECtxt_Param1                 = 0u;
  DAPI_BuildDECtxt_Param2                 = LDEH_E_DISAPPEAR;
  DAPI_BuildDECtxt_Param3                 = 0u;
  DAPI_BuildDECtxt_Param4                 = DEH_DTC_FORMAT_ID;
  DAPI_BuildDECtxt_Param5                 = 0u;
  Deh_AppearanceConfirmed_Param1          = SUBCAN_BUSOFF;
  Dem_Set_Init_Window_Param1              = FALSE;
  Dem_Set_Init_Window_HitCount            = 0u;

  //Step 3) Call FUT
  Default_BusOff_AppearedConfirmed();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,           1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,             SUBCAN_BUSOFF, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2,             DEM_EVENT_STATUS_FAILED, == );
  AL_UNITTEST_CHECK(DAPI_AddDE_HitCount,                   0u, == );
  AL_UNITTEST_CHECK(ErrCust_GetStatusOfDtc_HitCount,       1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_HitCount,  1u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_HitCount,             0u, == );
  AL_UNITTEST_CHECK(DAPI_AddDE_Param2,                     E_FALSE, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param5,               0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param1,               0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param2,               LDEH_E_DISAPPEAR, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param3,               0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param4,               DEH_DTC_FORMAT_ID, == );
  AL_UNITTEST_CHECK(DAPI_AddDE_Param1,                     0u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_Param1,    106u, == );
  AL_UNITTEST_CHECK(Dem_Set_Init_Window_Param1,            TRUE, == );
  AL_UNITTEST_CHECK(Dem_Set_Init_Window_HitCount,          1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Default_BusOff_AppearedDetected
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that LGM callback for Bus Off default appearance detected
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DAPI_BuildDECtxt_HitCount             = 0u
/// \input ErrCust_ulGetDtcCode_HitCount         = 0u
/// \input ErrCust_GetActualErrorIndex_HitCount  = 0u
/// \input ErrCust_GetActualErrorIndex_Param1    = 12u
/// \input DAPI_BuildDECtxt_Param2               = 0u
///
///   - Expectations:
///
/// \output DAPI_BuildDECtxt_HitCount             = 0u
/// \output ErrCust_ulGetDtcCode_HitCount         = 1u
/// \output ErrCust_GetActualErrorIndex_HitCount  = 1u
/// \output ErrCust_GetActualErrorIndex_Param1    = 106u
/// \output DAPI_BuildDECtxt_Param2               = LDEH_E_DISAPPEAR
/// \output DAPI_BuildDECtxt_Param3               = 5u
/// \output DAPI_BuildDECtxt_Param4               = 169
/// \output DAPI_BuildDECtxt_Param5               = 2u
/// \output ErrCust_ulGetDtcCode_Param1           = 2u
/// \output DAPI_BuildDECtxt_Param1               = 0u
///
//-----------------------------------------------------------------------------
void Mt_Default_BusOff_AppearedDetected(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  DAPI_BuildDECtxt_HitCount             = 0u;
  ErrCust_ulGetDtcCode_HitCount         = 0u;
  ErrCust_GetActualErrorIndex_HitCount  = 0u;
  Deh_AppearanceDetected_Param1         = SUBCAN_BUSOFF;
  DAPI_BuildDECtxt_Param2               = LDEH_E_DISAPPEAR;
  ErrCust_ulGetDtcCode_RetVal           = 5u;
  DAPI_BuildDECtxt_Param4               = DEH_R_ECU_CODE;
  DAPI_BuildDECtxt_Param5               = 2u;
  ucEcuCode                             = 1u;
  ErrCust_GetActualErrorIndex_RetVal    = 2u;
  ErrCust_GetActualErrorIndex_Param1    = 0u;
  ErrCust_ulGetDtcCode_Param1           = 3u;
  DAPI_BuildDECtxt_Param1               = 0u;
  DAPI_BuildDECtxt_Param3               = 0u;

  //Step 3) Call FUT
  Default_BusOff_AppearedDetected();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_HitCount,             0u, == );
  AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_HitCount,         1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_HitCount,  1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_Param1,    106u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param2,               LDEH_E_DISAPPEAR, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param3,               0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param4,               169u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param5,               2u, == );
  AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_Param1,           2u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param1,               0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Recover_C_ABS_BSI
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that LGM callback for recovery from NvM of C_ABS_BSI counte
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input NvmBlockNmBackupCounters.ucC_ABS_BSI_Counter          = 1u
/// \input Recover_C_ABS_BSI_Param1                              = 2u
///
///   - Expectations:
///
/// \output Recover_C_ABS_BSI_Param1                             = 1u
///
//-----------------------------------------------------------------------------
void Mt_Recover_C_ABS_BSI(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values 
  NvmBlockNmBackupCounters.ucC_ABS_BSI_Counter  = 1u;
  Recover_C_ABS_BSI_Param1                      = 2u;

  //Step 3) Call FUT
  Recover_C_ABS_BSI(&Recover_C_ABS_BSI_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Recover_C_ABS_BSI_Param1,  1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Backup_C_ABS_BSI
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that LGM callback for backup in NvM of C_ABS_BSI counter
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input NvmBlockNmBackupCounters.ucC_ABS_BSI_Counter          = 1u
/// \input Backup_C_ABS_BSI_Param1                               = 2u
///
///   - Expectations:
///
/// \output NvmBlockNmBackupCounters.ucC_ABS_BSI_Counter         = 2u
///
//-----------------------------------------------------------------------------
void Mt_Backup_C_ABS_BSI(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values  
  NvmBlockNmBackupCounters.ucC_ABS_BSI_Counter  = 1u;
  Backup_C_ABS_BSI_Param1                       = 2u;

  //Step 3) Call FUT
  Backup_C_ABS_BSI(Backup_C_ABS_BSI_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(NvmBlockNmBackupCounters.ucC_ABS_BSI_Counter,  2u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Default_BSI_DisappearedConfirmed
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that  disappearance confirmed of 0x036 frame callback
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DAPI_BuildDECtxt_HitCount              = 0u
/// \input ErrCust_ulGetDtcCode_HitCount          = 0u
/// \input ErrCust_GetActualErrorIndex_HitCount   = 0u
/// \input DAPI_AddDE_HitCount                    = 0u
/// \input DAPI_BuildDECtxt_HitCount              = 0u
/// \input Dem_SetEventStatus_Param1              = 0u
/// \input Dem_SetEventStatus_Param2              = DEM_EVENT_STATUS_FAILED
/// \input Dem_SetEventStatus_HitCount            = 0u
/// \input  DAPI_BuildDECtxt_HitCount             = 0u;
/// \input  ErrCust_ulGetDtcCode_HitCount         = 0u;
/// \input  ErrCust_GetActualErrorIndex_HitCount  = 0u;
/// \input  DAPI_AddDE_HitCount                   = 0u;
/// \input  DAPI_AddDE_Param2                     = E_FALSE;
/// \input  DAPI_BuildDECtxt_Param1               = 0u;
/// \input  DAPI_BuildDECtxt_Param2               = LDEH_E_APPEAR;
/// \input  DAPI_BuildDECtxt_Param3               = 0u;
/// \input  DAPI_BuildDECtxt_Param4               = DEH_DTC_FORMAT_ID;
/// \input  DAPI_BuildDECtxt_Param5               = 0u;
/// \input  ucEcuCode                             = 2u;
/// \input  ErrCust_GetActualErrorIndex_RetVal    = 2u;
/// \input  Deh_DisappearanceConfirmed_Param1     = HS6_COMMANDES_VSM_036_ID;
///
///   - Expectations:
///
/// \output  DAPI_BuildDECtxt_HitCount             = 0u;
/// \output  ErrCust_ulGetDtcCode_HitCount         = 1u;
/// \output  ErrCust_GetActualErrorIndex_HitCount  = 1u;
/// \output  DAPI_AddDE_HitCount                   = 0u;
/// \output  DAPI_AddDE_Param2                     = E_FALSE;
/// \output  DAPI_BuildDECtxt_Param2               = LDEH_E_APPEAR;
/// \output  DAPI_BuildDECtxt_Param4               = DEH_DTC_FORMAT_ID;
/// \output  DAPI_BuildDECtxt_Param5               = 0u;
/// \output  DAPI_BuildDECtxt_Param1               = 0u;
/// \output  DAPI_BuildDECtxt_Param3               = 0u;
/// \output  ErrCust_GetActualErrorIndex_Param1    = 40u;
/// \output Dem_SetEventStatus_Param1              = HS6_COMMANDES_VSM_036_ID
/// \output Dem_SetEventStatus_Param2              = DEM_EVENT_STATUS_PASSED
/// \output Dem_SetEventStatus_HitCount            =1u
///
//-----------------------------------------------------------------------------
void Mt_Default_BSI_DisappearedConfirmed(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values   
  DAPI_BuildDECtxt_HitCount             = 0u;
  ErrCust_ulGetDtcCode_HitCount         = 0u;
  ErrCust_GetActualErrorIndex_HitCount  = 0u;
  DAPI_AddDE_HitCount                   = 0u;
  DAPI_AddDE_Param2                     = E_FALSE;
  DAPI_AddDE_Param1                     = 0u;
  DAPI_BuildDECtxt_Param1               = 0u;
  DAPI_BuildDECtxt_Param2               = LDEH_E_APPEAR;
  DAPI_BuildDECtxt_Param3               = 0u;
  DAPI_BuildDECtxt_Param4               = DEH_DTC_FORMAT_ID;
  DAPI_BuildDECtxt_Param5               = 0u;
  ucEcuCode                             = 2u;
  ErrCust_GetActualErrorIndex_RetVal    = 2u;
  Deh_DisappearanceConfirmed_Param1     = HS6_COMMANDES_VSM_036_ID;
  Dem_SetEventStatus_Param1             = 0u;
  Dem_SetEventStatus_Param2             = DEM_EVENT_STATUS_FAILED;
  Dem_SetEventStatus_HitCount           = 0u;

  //Step 3) Call FUT
  Default_BSI_DisappearedConfirmed();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_HitCount,             0u, == );
  AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_HitCount,         1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_HitCount,  1u, == );
  AL_UNITTEST_CHECK(DAPI_AddDE_HitCount,                   0u, == );
  AL_UNITTEST_CHECK(DAPI_AddDE_Param1,                     0u, == );
  AL_UNITTEST_CHECK(DAPI_AddDE_Param2,                     E_FALSE, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param2,               LDEH_E_APPEAR, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param4,               DEH_DTC_FORMAT_ID, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param5,               0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param1,               0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param3,               0u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_Param1,    40u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,             HS6_COMMANDES_VSM_036_ID, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2,             DEM_EVENT_STATUS_PASSED, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Default_BSI_DisappearedDetected
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that disappearance detected of 0x036 frame callback
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input DAPI_BuildDECtxt_HitCount             = 0u
/// \input ErrCust_ulGetDtcCode_HitCount         = 0u
/// \input ErrCust_GetActualErrorIndex_HitCount  = 0u
/// \input DAPI_AddDE_HitCount                   = 0u
/// \input DAPI_BuildDECtxt_HitCount             = 0u
///
///   - Expectations:
///
/// \output DAPI_BuildDECtxt_HitCount             = 0u
/// \output ErrCust_ulGetDtcCode_HitCount         = 1u
/// \output ErrCust_GetActualErrorIndex_HitCount  = 1u
/// \output EDAPI_AddDE_HitCount                  = 0u
///
//-----------------------------------------------------------------------------
void Mt_Default_BSI_DisappearedDetected(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values   
  DAPI_BuildDECtxt_HitCount             = 0u;
  ErrCust_ulGetDtcCode_HitCount         = 0u;
  ErrCust_GetActualErrorIndex_HitCount  = 0u;
  DAPI_AddDE_HitCount                   = 0u;
  DAPI_BuildDECtxt_HitCount             = 0u;

  //Step 3) Call FUT  
  Default_BSI_DisappearedDetected();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_HitCount,             0u, == );
  AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_HitCount,         1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_HitCount,  1u, == );
  AL_UNITTEST_CHECK(DAPI_AddDE_HitCount,                   0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Default_BSI_AppearedConfirmed
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that  appearance confirmed of 0x036 frame callback
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Dem_SetEventStatus_Param1             = 0u
/// \input Dem_SetEventStatus_Param2             = DEM_EVENT_STATUS_PASSED
/// \input Dem_SetEventStatus_HitCount           = 0u
/// \input DAPI_AddDE_HitCount                    = 0u
/// \input ErrCust_GetStatusOfDtc_RetVal          = 0u
/// \input ErrCust_GetActualErrorIndex_RetVal     = 0u
/// \input ErrCust_GetActualErrorIndex_HitCount   = 0u
/// \input ErrCust_GetStatusOfDtc_HitCount        = 0u
/// \input ErrCust_ulGetDtcCode_HitCount          = 0u
/// \input S_DE[0u].Au8_FirstFrame[DAPI_D_DTC_B0] = 1u
/// \input S_DE[0u].Au8_FirstFrame[DAPI_D_DTC_B1] = 1u
/// \input S_DE[0u].Au8_FirstFrame[DAPI_D_DTC_B2] = 1u
/// \input ucEcuCode                              = 5u
/// \input DAPI_AddDE_Param1                      = 0u;
/// \input DAPI_BuildDECtxt_Param1                = 0u;
/// \input DAPI_BuildDECtxt_Param2                = LDEH_E_DISAPPEAR;
/// \input DAPI_BuildDECtxt_Param3                = 0u;
/// \input DAPI_BuildDECtxt_Param4                = DEH_DTC_FORMAT_ID;
/// \input DAPI_BuildDECtxt_Param5                = 0u;
/// \input Deh_AppearanceConfirmed_Param1         = 14u;
///
///   - Expectations:
///
/// \output Dem_SetEventStatus_Param1              = HS6_COMMANDES_VSM_036_ID
/// \output Dem_SetEventStatus_Param2              = DEM_EVENT_STATUS_FAILED
/// \output Dem_SetEventStatus_HitCount            =1u
/// \output DAPI_AddDE_HitCount                   = 0u
/// \output ErrCust_GetStatusOfDtc_HitCount       = 0u
/// \output ErrCust_GetActualErrorIndex_HitCount  = 1u
/// \output DAPI_BuildDECtxt_Param5               = 0u
/// \output DAPI_BuildDECtxt_Param1               = 0u;
/// \output DAPI_BuildDECtxt_Param2               = LDEH_E_DISAPPEAR;
/// \output DAPI_BuildDECtxt_Param3               = 0u;
/// \output DAPI_BuildDECtxt_Param4               = DEH_DTC_FORMAT_ID;
/// \output  DAPI_AddDE_Param1                    = 0u;
/// \output ErrCust_GetActualErrorIndex_Param1    = 40u

///
//-----------------------------------------------------------------------------
void Mt_Default_BSI_AppearedConfirmed(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  DAPI_AddDE_HitCount                     = 0u;
  ErrCust_GetStatusOfDtc_RetVal           = 0u;
  ErrCust_GetActualErrorIndex_RetVal      = 0u; // status flags
  ErrCust_GetActualErrorIndex_HitCount    = 0u; // status flags
  ErrCust_GetStatusOfDtc_HitCount         = 0u;
  ErrCust_ulGetDtcCode_HitCount           = 0u;
  DAPI_BuildDECtxt_HitCount               = 0u;
  DAPI_AddDE_Param2                       = E_FALSE;
  S_DE[0u].Au8_FirstFrame[DAPI_D_DTC_B0]  = 1u;
  S_DE[0u].Au8_FirstFrame[DAPI_D_DTC_B1]  = 1u;
  S_DE[0u].Au8_FirstFrame[DAPI_D_DTC_B2]  = 1u;
  ucEcuCode                               = 5u;
  DAPI_AddDE_Param1                       = 0u;
  DAPI_BuildDECtxt_Param1                 = 0u;
  DAPI_BuildDECtxt_Param2                 = LDEH_E_DISAPPEAR;
  DAPI_BuildDECtxt_Param3                 = 0u;
  DAPI_BuildDECtxt_Param4                 = DEH_DTC_FORMAT_ID;
  DAPI_BuildDECtxt_Param5                 = 0u;
  Deh_AppearanceConfirmed_Param1          = HS6_COMMANDES_VSM_036_ID;
  Dem_SetEventStatus_Param1               = 0u;
  Dem_SetEventStatus_Param2               = DEM_EVENT_STATUS_PASSED;
  Dem_SetEventStatus_HitCount             = 0u;

  //Step 3) Call FUT
  Default_BSI_AppearedConfirmed();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,           1u, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param1,             HS6_COMMANDES_VSM_036_ID, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_Param2,             DEM_EVENT_STATUS_FAILED, == );
  AL_UNITTEST_CHECK(DAPI_AddDE_HitCount,                   0u, == );
  AL_UNITTEST_CHECK(ErrCust_GetStatusOfDtc_HitCount,       1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_HitCount,  1u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_HitCount,             0u, == );
  AL_UNITTEST_CHECK(DAPI_AddDE_Param2,                     E_FALSE, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param5,               0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param1,               0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param2,               LDEH_E_DISAPPEAR, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param3,               0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param4,               DEH_DTC_FORMAT_ID, == );
  AL_UNITTEST_CHECK(DAPI_AddDE_Param1,                     0u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_Param1,    40u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Default_BSI_AppearedDetected
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: Test that appearance confirmed of 0x036 frame callback
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  DAPI_BuildDECtxt_HitCount             = 0u;
/// \input  ErrCust_ulGetDtcCode_HitCount         = 0u;
/// \input  ErrCust_GetActualErrorIndex_HitCount  = 0u;
/// \input  Deh_AppearanceDetected_Param1         = HS6_COMMANDES_VSM_036_ID;
/// \input  DAPI_BuildDECtxt_Param2               = LDEH_E_DISAPPEAR;
/// \input  ErrCust_ulGetDtcCode_RetVal           = 5u;
/// \input  DAPI_BuildDECtxt_Param4               = DEH_R_ECU_CODE;
/// \input  DAPI_BuildDECtxt_Param5               = 2u;
/// \input  ucEcuCode                             = 1u;
/// \input  ErrCust_GetActualErrorIndex_RetVal    = 2u;
/// \input  ErrCust_ulGetDtcCode_Param1           = 3u;
/// \input DAPI_BuildDECtxt_Param1                = 0u;
/// \input DAPI_BuildDECtxt_Param3                = 0u;
///
///   - Expectations:
///
/// \output  DAPI_BuildDECtxt_HitCount             = 0u
/// \output  ErrCust_ulGetDtcCode_HitCount         = 1u
/// \output  ErrCust_GetActualErrorIndex_HitCount  = 1u
/// \output  ErrCust_GetActualErrorIndex_Param1    = 40u
/// \output  DAPI_BuildDECtxt_Param2               = LDEH_E_DISAPPEAR
/// \output  DAPI_BuildDECtxt_Param3               = 0u
/// \output  DAPI_BuildDECtxt_Param4               = 169u
/// \output  DAPI_BuildDECtxt_Param5               = 1u
/// \output  ErrCust_ulGetDtcCode_Param1           = 2u
/// \output  DAPI_BuildDECtxt_Param1               = 0u
///
//-----------------------------------------------------------------------------
void Mt_Default_BSI_AppearedDetected(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  DAPI_BuildDECtxt_HitCount             = 0u;
  ErrCust_ulGetDtcCode_HitCount         = 0u;
  ErrCust_GetActualErrorIndex_HitCount  = 0u;
  Deh_AppearanceDetected_Param1         = HS6_COMMANDES_VSM_036_ID;
  DAPI_BuildDECtxt_Param2               = LDEH_E_DISAPPEAR;
  ErrCust_ulGetDtcCode_RetVal           = 5u;
  DAPI_BuildDECtxt_Param4               = DEH_R_ECU_CODE;
  DAPI_BuildDECtxt_Param5               = 2u;
  ucEcuCode                             = 1u;
  ErrCust_GetActualErrorIndex_RetVal    = 2u;
  ErrCust_GetActualErrorIndex_Param1    = 0u;
  ErrCust_ulGetDtcCode_Param1           = 3u;
  DAPI_BuildDECtxt_Param1               = 0u;
  DAPI_BuildDECtxt_Param3               = 0u;

  //Step 3) Call FUT
  Default_BSI_AppearedDetected();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_HitCount,             0u, == );
  AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_HitCount,         1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_HitCount,  1u, == );
  AL_UNITTEST_CHECK(ErrCust_GetActualErrorIndex_Param1,    40u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param2,               LDEH_E_DISAPPEAR, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param3,               0u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param4,               169u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param5,               2u, == );
  AL_UNITTEST_CHECK(ErrCust_ulGetDtcCode_Param1,           2u, == );
  AL_UNITTEST_CHECK(DAPI_BuildDECtxt_Param1,               0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_Cycle0_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if  calls correctly  functions.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_SysMon_LifePhases_HitCount                               =0u
/// \input Rte_Read_SysMon_VehicleSpeed_HitCount -                           =0u
/// \input Rte_Read_SysMon_LifePhases_Param1.ePhaseVie                       = eNormalMode
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = DEH_5KMH_THRESHOLD;
/// \input Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                       = SIG_VALID
/// \input DAPI_SetSafetyConditions_Param1                                   = 85u
/// \input DAPI_SetSafetyConditions_HitCount                                 = 0u
/// \input DAPI_ScheduleMainFunction_HitCount                                = 0u
///
/// - Expectations: 
///
/// \output Rte_Read_SysMon_LifePhases_HitCount                             = 1u;
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount                           = 1u;
/// \output DAPI_SetSafetyConditions_Param1                                 = E_TRUE
/// \output DAPI_SetSafetyConditions_HitCount                               = 1u;
/// \output DAPI_ScheduleMainFunction_HitCount                              = 1u;
///
//-----------------------------------------------------------------------------
void Mt_Deh_Cycle0_TestCase1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values   
  Rte_Read_SysMon_LifePhases_HitCount                               = 0u;
  Rte_Read_SysMon_VehicleSpeed_HitCount                             = 0u;
  Rte_Read_SysMon_LifePhases_Param1.ePhaseVie                       = eNormalMode;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed  = DEH_5KMH_THRESHOLD;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                       = SIG_VALID;
  DAPI_SetSafetyConditions_Param1                                   = E_FALSE;
  DAPI_SetSafetyConditions_HitCount                                 = 0u;
  DAPI_ScheduleMainFunction_HitCount                                = 0u;

  //Step 3) Call FUT
  Deh_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_LifePhases_HitCount,    1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,  1u, == );
  AL_UNITTEST_CHECK(DAPI_SetSafetyConditions_Param1,        E_TRUE, == );
  AL_UNITTEST_CHECK(DAPI_SetSafetyConditions_HitCount,      1u, == );
  AL_UNITTEST_CHECK(DAPI_ScheduleMainFunction_HitCount,     1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_Cycle0_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if  calls correctly  functions.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
/// \input  {
/// \input    Deh_asDehLogTab[ucIndx].eEventState           = 0xFF;
/// \input    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared  = 0xFF;
/// \input  }
/// \input  DAPI_BuildDECtxt_RetVal                  = LDEH_E_SUCCESS;
/// \input  Deh_asDehLogTab[7].eEventState           = eDeh_Undef;
/// \input  Deh_asDehLogTab[7].ucDemEvntCnt_Apeared  = 2u;
///
/// - Expectations: 
///
/// \output   AL_UNITTEST_CHECK(Deh_asDehLogTab[7].eEventState,  eDeh_Apeared, == );
///
//-----------------------------------------------------------------------------
void Mt_Deh_Cycle0_TestCase2(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values   
  for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
  {
    Deh_asDehLogTab[ucIndx].eEventState           = 0xFF;
    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared  = 0xFF;
  }
  DAPI_BuildDECtxt_RetVal                  = LDEH_E_SUCCESS;
  Deh_asDehLogTab[7].eEventState           = eDeh_Undef;
  Deh_asDehLogTab[7].ucDemEvntCnt_Apeared  = 2u;

  //Step 3) Call FUT
  Deh_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Deh_asDehLogTab[7].eEventState,  eDeh_Apeared, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_Cycle0_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if  calls correctly  functions.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
/// \input {
/// \input   Deh_asDehLogTab[ucIndx].eEventState           = 0xFF;
/// \input   Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared  = 0xFF;
/// \input }
/// \input DAPI_BuildDECtxt_RetVal                  = LDEH_E_ERR_INVAL;
/// \input Deh_asDehLogTab[7].eEventState           = eDeh_Undef;
/// \input Deh_asDehLogTab[7].ucDemEvntCnt_Apeared  = 2u;
///
/// - Expectations: 
///
/// \output AL_UNITTEST_CHECK(Deh_asDehLogTab[7].eEventState, eDeh_Undef, == );
///
//-----------------------------------------------------------------------------
void Mt_Deh_Cycle0_TestCase3(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values   
  for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
  {
    Deh_asDehLogTab[ucIndx].eEventState           = 0xFF;
    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared  = 0xFF;
  }
  DAPI_BuildDECtxt_RetVal                  = LDEH_E_ERR_INVAL;
  Deh_asDehLogTab[7].eEventState           = eDeh_Undef;
  Deh_asDehLogTab[7].ucDemEvntCnt_Apeared  = 2u;

  //Step 3) Call FUT
  Deh_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Deh_asDehLogTab[7].eEventState,  eDeh_Undef, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_Cycle0_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if  calls correctly  functions.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input  for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
/// \input  {
/// \input  
/// \input    Deh_asDehLogTab[ucIndx].eEventState           = 0xFF;
/// \input    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared  = 0xFF;
/// \input  }
/// \input  DAPI_BuildDECtxt_RetVal                  = LDEH_E_SUCCESS;
/// \input  Deh_asDehLogTab[7].eEventState           = eDeh_ApearedConf_DirectSent;
/// \input  Deh_asDehLogTab[7].ucDemEvntCnt_Apeared  = 2u;
///
/// - Expectations: 
///
/// \output AL_UNITTEST_CHECK(Deh_asDehLogTab[7].eEventState,  eDeh_Apeared, == );
///
//-----------------------------------------------------------------------------
void Mt_Deh_Cycle0_TestCase4(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values   
  for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
  {
    Deh_asDehLogTab[ucIndx].eEventState           = 0xFF;
    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared  = 0xFF;
  }
  DAPI_BuildDECtxt_RetVal                  = LDEH_E_SUCCESS;
  Deh_asDehLogTab[7].eEventState           = eDeh_ApearedConf_DirectSent;
  Deh_asDehLogTab[7].ucDemEvntCnt_Apeared  = 2u;

  //Step 3) Call FUT
  Deh_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Deh_asDehLogTab[7].eEventState,  eDeh_Apeared, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_Cycle0_TestCase5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if  calls correctly  functions.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
/// \input {
/// \input   Deh_asDehLogTab[ucIndx].eEventState           = 0xFF;
/// \input   Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared  = 0xFF;
/// \input }
/// \input DAPI_BuildDECtxt_RetVal                  = LDEH_E_ERR_INVAL;
/// \input Deh_asDehLogTab[7].eEventState           = eDeh_ApearedConf_DirectSent;
/// \input Deh_asDehLogTab[7].ucDemEvntCnt_Apeared  = 2u;

///
/// - Expectations: 
///
/// \output AL_UNITTEST_CHECK(Deh_asDehLogTab[7].eEventState, eDeh_Undef, == );
///
//-----------------------------------------------------------------------------
void Mt_Deh_Cycle0_TestCase5(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values   
  for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
  {

    Deh_asDehLogTab[ucIndx].eEventState           = 0xFF;
    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared  = 0xFF;
  }
  DAPI_BuildDECtxt_RetVal                  = LDEH_E_ERR_INVAL;
  Deh_asDehLogTab[7].eEventState           = eDeh_ApearedConf_DirectSent;
  Deh_asDehLogTab[7].ucDemEvntCnt_Apeared  = 2u;

  //Step 3) Call FUT
  Deh_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Deh_asDehLogTab[7].eEventState,  eDeh_Undef, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_Cycle0_TestCase6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if  calls correctly  functions.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
/// \input {
/// \input   Deh_asDehLogTab[ucIndx].eEventState              = 0xFF;
/// \input   Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared     = 0;
/// \input   Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Disapeared  = 0u;
/// \input }
/// \input DAPI_BuildDECtxt_RetVal                  = LDEH_E_SUCCESS;
/// \input Deh_asDehLogTab[7].eEventState           = eDeh_Undef;
/// \input Deh_asDehLogTab[7].ucDemEvntCnt_Apeared  = 2u;
///
/// - Expectations: 
///
/// \output AL_UNITTEST_CHECK(Deh_asDehLogTab[7].eEventState, eDeh_DisapearedConf_LGM, == );
///
//-----------------------------------------------------------------------------
void Mt_Deh_Cycle0_TestCase6(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values   
  for (uint8 ucIndx = 0u; ucIndx < DEH_TABLE_LOG_LENGTH; ucIndx++)
  {
    Deh_asDehLogTab[ucIndx].eEventState              = 0xFF;
    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Disapeared  = 0u;
    Deh_asDehLogTab[ucIndx].ucDemEvntCnt_Apeared     = 0u;
  }
  DAPI_BuildDECtxt_RetVal                     = LDEH_E_SUCCESS;
  Deh_asDehLogTab[7].eEventState              = eDeh_Undef;
  Deh_asDehLogTab[7].ucDemEvntCnt_Disapeared  = 2u;

  //Step 3) Call FUT
  Deh_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Deh_asDehLogTab[7].eEventState,  eDeh_DisapearedConf_LGM, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_Cycle0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if call correctly functions.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Deh_Cycle0(void)
{
  Mt_Deh_Cycle0_TestCase1();
  Mt_Deh_Cycle0_TestCase2();
  Mt_Deh_Cycle0_TestCase3();
  Mt_Deh_Cycle0_TestCase4();
  Mt_Deh_Cycle0_TestCase5();
  Mt_Deh_Cycle0_TestCase6();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_Init_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if  call correctly  functions.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1           = eMountedLeft
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount         = 0u
/// \input DAPI_InitModule_HitCount                             = 0u
/// \input DAPI_PermFifoStorage_Param1                          = LDEH_E_FIFO_NOTPERM
/// \input DAPI_PermFifoStorage_HitCount                        = 0u
/// \input DAPI_SetPermToSend_Param1                            = LDEH_E_SEND_NOTPERM
/// \input DAPI_SetPermToSend_HitCount                          = 0u
/// \input DAPI_SetSafetyConditions_HitCount                    = 0u
/// \input DAPI_SetMainStatus_HitCount                          = 0u
/// \input ucEcuCode                                            = DEH_R_ECU_CODE
/// \input DAPI_SetMainStatus_Param1                            = DAPI_E_MS_START

///
/// - Expectations: 
///
/// \output Rte_Read_IoHwAbUser_GetMountingSide_HitCount        = 1u
/// \output DAPI_InitModule_Param1                              = E_TRUE
/// \output DAPI_InitModule_Param2                              = DEH_L_ECU_CODE
/// \output DAPI_PermFifoStorage_Param1                         = LDEH_E_FIFO_PERM
/// \output DAPI_PermFifoStorage_HitCount                       = 1u
/// \output DAPI_SetPermToSend_Param1                           = LDEH_E_SEND_PERM
/// \output DAPI_SetPermToSend_HitCount                         = 1u
/// \output DAPI_SetSafetyConditions_Param1                     = E_FALSE
/// \output DAPI_SetSafetyConditions_HitCount                   = 1u
/// \output DAPI_SetMainStatus_Param1                           = DAPI_E_MS_IGNITION
/// \output ucEcuCode                                           = DEH_L_ECU_CODE
///
//-----------------------------------------------------------------------------
void Mt_Deh_Init_TestCase1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values   
  Rte_Read_IoHwAbUser_GetMountingSide_Param1    = eMountedLeft;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;
  DAPI_InitModule_HitCount                      = 0u;
  DAPI_PermFifoStorage_Param1                   = LDEH_E_FIFO_NOTPERM;
  DAPI_PermFifoStorage_HitCount                 = 0u;
  DAPI_SetPermToSend_Param1                     = LDEH_E_SEND_NOTPERM;
  DAPI_SetPermToSend_HitCount                   = 0u;
  DAPI_SetSafetyConditions_HitCount             = 0u;
  DAPI_SetMainStatus_HitCount                   = 0u;
  ucEcuCode                                     = DEH_R_ECU_CODE;
  DAPI_SetMainStatus_Param1                     = DAPI_E_MS_START;

  //Step 3) Call FUT
  Deh_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,  1u, == );
  AL_UNITTEST_CHECK(DAPI_InitModule_Param1,                        E_TRUE, == );
  AL_UNITTEST_CHECK(DAPI_InitModule_Param2,                        DEH_L_ECU_CODE, == );
  AL_UNITTEST_CHECK(DAPI_PermFifoStorage_Param1,                   LDEH_E_FIFO_PERM, == );
  AL_UNITTEST_CHECK(DAPI_PermFifoStorage_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(DAPI_SetPermToSend_Param1,                     LDEH_E_SEND_PERM, == );
  AL_UNITTEST_CHECK(DAPI_SetPermToSend_HitCount,                   1u, == );
  AL_UNITTEST_CHECK(DAPI_SetSafetyConditions_Param1,               E_FALSE, == );
  AL_UNITTEST_CHECK(DAPI_SetSafetyConditions_HitCount,             1u, == );
  AL_UNITTEST_CHECK(DAPI_SetMainStatus_HitCount,                   1u, == );
  AL_UNITTEST_CHECK(DAPI_SetMainStatus_Param1,                     DAPI_E_MS_IGNITION, == );
  AL_UNITTEST_CHECK(ucEcuCode,                                     DEH_L_ECU_CODE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_Init_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if call correctly functions.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions:
///
/// \input Rte_Read_IoHwAbUser_GetMountingSide_Param1           = eMountedRight
/// \input Rte_Read_IoHwAbUser_GetMountingSide_HitCount         = 0u
/// \input DAPI_InitModule_HitCount                             = 0u
/// \input DAPI_PermFifoStorage_Param1                          = LDEH_E_FIFO_NOTPERM
/// \input DAPI_PermFifoStorage_HitCount                        = 0u
/// \input DAPI_SetPermToSend_Param1                            = LDEH_E_SEND_NOTPERM
/// \input DAPI_SetPermToSend_HitCount                          = 0u
/// \input DAPI_SetSafetyConditions_HitCount                    = 0u
/// \input DAPI_SetMainStatus_HitCount                          = 0u
/// \input ucEcuCode                                            = DEH_L_ECU_CODE
/// \input DAPI_SetMainStatus_Param1                            = DAPI_E_MS_START
///
/// - Expectations: 
///
/// \output Rte_Read_IoHwAbUser_GetMountingSide_HitCount        = 1u
/// \output DAPI_InitModule_Param1                              = E_TRUE
/// \output DAPI_InitModule_Param2                              = DEH_R_ECU_CODE
/// \output DAPI_PermFifoStorage_Param1                         = LDEH_E_FIFO_PERM
/// \output DAPI_PermFifoStorage_HitCount                       = 1u
/// \output DAPI_SetPermToSend_Param1                           = LDEH_E_SEND_PERM
/// \output DAPI_SetPermToSend_HitCount                         = 1u
/// \output DAPI_SetSafetyConditions_Param1                     = E_FALSE
/// \output DAPI_SetSafetyConditions_HitCount                   = 1u
/// \output DAPI_SetMainStatus_Param1                           = DAPI_E_MS_IGNITION
/// \output ucEcuCode                                           = DEH_R_ECU_CODE
///
//-----------------------------------------------------------------------------
void Mt_Deh_Init_TestCase2(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values  
  Rte_Read_IoHwAbUser_GetMountingSide_Param1    = eMountedRight;
  Rte_Read_IoHwAbUser_GetMountingSide_HitCount  = 0u;
  DAPI_InitModule_HitCount                      = 0u;
  DAPI_PermFifoStorage_Param1                   = LDEH_E_FIFO_NOTPERM;
  DAPI_PermFifoStorage_HitCount                 = 0u;
  DAPI_SetPermToSend_Param1                     = LDEH_E_SEND_NOTPERM;
  DAPI_SetPermToSend_HitCount                   = 0u;
  DAPI_SetSafetyConditions_HitCount             = 0u;
  DAPI_SetMainStatus_HitCount                   = 0u;
  ucEcuCode                                     = DEH_L_ECU_CODE;
  DAPI_SetMainStatus_Param1                     = DAPI_E_MS_START;

  //Step 3) Call FUT
  Deh_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAbUser_GetMountingSide_HitCount,  1u, == );
  AL_UNITTEST_CHECK(DAPI_InitModule_Param1,                        E_TRUE, == );
  AL_UNITTEST_CHECK(DAPI_InitModule_Param2,                        DEH_R_ECU_CODE, == );
  AL_UNITTEST_CHECK(DAPI_PermFifoStorage_Param1,                   LDEH_E_FIFO_PERM, == );
  AL_UNITTEST_CHECK(DAPI_PermFifoStorage_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(DAPI_SetPermToSend_Param1,                     LDEH_E_SEND_PERM, == );
  AL_UNITTEST_CHECK(DAPI_SetPermToSend_HitCount,                   1u, == );
  AL_UNITTEST_CHECK(DAPI_SetSafetyConditions_Param1,               E_FALSE, == );
  AL_UNITTEST_CHECK(DAPI_SetSafetyConditions_HitCount,             1u, == );
  AL_UNITTEST_CHECK(DAPI_SetMainStatus_HitCount,                   1u, == );
  AL_UNITTEST_CHECK(DAPI_SetMainStatus_Param1,                     DAPI_E_MS_IGNITION, == );
  AL_UNITTEST_CHECK(ucEcuCode,                                     DEH_R_ECU_CODE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Deh_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test if call correctly functions.
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Deh_Init(void)
{
  Mt_Deh_Init_TestCase1();
  Mt_Deh_Init_TestCase2();
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
  //ctaaDeh.c
  ALUnitTest_AddFunction("Mt_Deh_rpDeh_Cycle0",                    Mt_Deh_rpDeh_Cycle0);
  ALUnitTest_AddFunction("Mt_Deh_riDeh_Init",                      Mt_Deh_riDeh_Init);

  //Deh.c
  ALUnitTest_AddFunction("Mt_Recover_UCE_ABS_RL_F_1_HDC",          Mt_Recover_UCE_ABS_RL_F_1_HDC);
  ALUnitTest_AddFunction("Mt_Backup_UCE_ABS_RL_F_1_HDC",           Mt_Backup_UCE_ABS_RL_F_1_HDC);
  ALUnitTest_AddFunction("Mt_Deh_CheckSafetyConditions",           Mt_Deh_CheckSafetyConditions);
  ALUnitTest_AddFunction("Mt_Deh_AppearanceDetected",              Mt_Deh_AppearanceDetected);
  ALUnitTest_AddFunction("Mt_Deh_AppearanceConfirmed",             Mt_Deh_AppearanceConfirmed);
  ALUnitTest_AddFunction("Mt_Deh_DisappearanceDetected",           Mt_Deh_DisappearanceDetected);

  ALUnitTest_AddFunction("Mt_Deh_APPLI_Send_Defaut",               Mt_Deh_APPLI_Send_Defaut);
  ALUnitTest_AddFunction("Mt_Deh_APPLI_DENotAck",                  Mt_Deh_APPLI_DENotAck);
  ALUnitTest_AddFunction("Mt_Deh_APPLI_DEAck",                     Mt_Deh_APPLI_DEAck);
  ALUnitTest_AddFunction("Mt_Recover_C_Mute",                      Mt_Recover_C_Mute);
  ALUnitTest_AddFunction("Mt_Backup_C_Mute",                       Mt_Backup_C_Mute);
  ALUnitTest_AddFunction("Mt_Default_Mute_DisappearedConfirmed",   Mt_Default_Mute_DisappearedConfirmed);
  ALUnitTest_AddFunction("Mt_Default_Mute_DisappearedDetected",    Mt_Default_Mute_DisappearedDetected);
  ALUnitTest_AddFunction("Mt_Default_Mute_AppearedConfirmed",      Mt_Default_Mute_AppearedConfirmed);
  ALUnitTest_AddFunction("Mt_Default_Mute_AppearedDetected",       Mt_Default_Mute_AppearedDetected);
  ALUnitTest_AddFunction("Mt_Bus_Off_Callback",                    Mt_Bus_Off_Callback);
  ALUnitTest_AddFunction("Mt_Recover_C_BusOff",                    Mt_Recover_C_BusOff);
  ALUnitTest_AddFunction("Mt_Backup_C_BusOff",                     Mt_Backup_C_BusOff);
  ALUnitTest_AddFunction("Mt_Default_BusOff_DisappearedConfirmed", Mt_Default_BusOff_DisappearedConfirmed);
  ALUnitTest_AddFunction("Mt_Default_BusOff_DisappearedDetected",  Mt_Default_BusOff_DisappearedDetected);
  ALUnitTest_AddFunction("Mt_Default_BusOff_AppearedConfirmed",    Mt_Default_BusOff_AppearedConfirmed);
  ALUnitTest_AddFunction("Mt_Default_BusOff_AppearedDetected",     Mt_Default_BusOff_AppearedDetected);
  ALUnitTest_AddFunction("Mt_Recover_C_ABS_BSI",                   Mt_Recover_C_ABS_BSI);
  ALUnitTest_AddFunction("Mt_Backup_C_ABS_BSI",                    Mt_Backup_C_ABS_BSI);
  ALUnitTest_AddFunction("Mt_Default_BSI_DisappearedConfirmed",    Mt_Default_BSI_DisappearedConfirmed);
  ALUnitTest_AddFunction("Mt_Default_BSI_DisappearedDetected",     Mt_Default_BSI_DisappearedDetected);
  ALUnitTest_AddFunction("Mt_Default_BSI_AppearedConfirmed",       Mt_Default_BSI_AppearedConfirmed);
  ALUnitTest_AddFunction("Mt_Default_BSI_AppearedDetected",        Mt_Default_BSI_AppearedDetected);
  ALUnitTest_AddFunction("Mt_Deh_Cycle0",                          Mt_Deh_Cycle0);
  ALUnitTest_AddFunction("Mt_Deh_Init",                            Mt_Deh_Init);
  ALUnitTest_AddFunction("Mt_Deh_DisappearanceConfirmed", Mt_Deh_DisappearanceConfirmed);
}


// EOF
