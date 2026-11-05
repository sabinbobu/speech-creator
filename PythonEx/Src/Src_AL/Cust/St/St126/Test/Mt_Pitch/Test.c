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
/// \brief  Unit Test Cases for Pitch module
///
/// \author MaramReddy Sathishreddy (F01517E)
///         mailTo:sathishreddy.maramreddy[at]external.marelli.com
//-----------------------------------------------------------------------------

//=============================================================================================================================================================
//  Files covered by this module unit test:
//        Gen/Bsw/NvM:
//            - ctaaPitch.c
//            - Pitch.c
//            - Pitch_Data.c
//            - Pitch_RteAccess.c
//            - Pitch_SensPlau.c
//
//=============================================================================================================================================================

//=============================================================================
// includes
//=============================================================================

#include <ALUnitTest_UserInterface.h>

#include "Test.h"
#include "Test_Stubs.h"

//=============================================================================
// Test Cases
//=============================================================================

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Pitch_Pitch_ParaFct0_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the function checks the coding data is valid or not
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
///input Pitch_ParaFct0_Param1 = eParaFct0_CodingDataValid;
///input Pitch_ParaFct0_Param2 = &Coding_Dummy;
///input Pitch_ParaFct0_RetVal = FALSE;
///
/// - Expectations:
///
/// output Pitch_ParaFct0_RetVal   = TRUE
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_ParaFct0_TestCase_1(void)
{
  //Step 1) Set pre-conditions
   //Step 2) Assign Input values
  Pitch_ParaFct0_Param1 = eParaFct0_CodingDataValid;
  Pitch_ParaFct0_Param2 = &Coding_Dummy;
  Pitch_ParaFct0_RetVal = FALSE;

  //Step 3) Call FUT
  Pitch_ParaFct0_RetVal = Pitch_ParaFct0(Pitch_ParaFct0_Param1, Pitch_ParaFct0_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_ParaFct0_RetVal, TRUE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Pitch_Pitch_ParaFct0_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the function checks the coding data is valid or not
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
///input Pitch_ParaFct0_Param1 = eParaFct0_CodingDataInValid;
///input Pitch_ParaFct0_Param2 = &Coding_Dummy;
///input Pitch_ParaFct0_RetVal = TRUE;
///
/// - Expectations:
///
/// output Pitch_ParaFct0_RetVal   = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_ParaFct0_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Pitch_ParaFct0_Param1 = eParaFct0_CodingDataInvalid;
  Pitch_ParaFct0_Param2 = &Coding_Dummy;
  Pitch_ParaFct0_RetVal = TRUE;

  //Step 3) Call FUT
  Pitch_ParaFct0_RetVal = Pitch_ParaFct0(Pitch_ParaFct0_Param1, Pitch_ParaFct0_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_ParaFct0_RetVal, FALSE, == );
}


//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Pitch_Pitch_ParaFct0_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the function checks the coding data is valid or not
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
///input Pitch_ParaFct0_Param1 = 255
///input Pitch_ParaFct0_Param2 = &Coding_Dummy;
///input Pitch_ParaFct0_RetVal = TRUE;
///
/// - Expectations:
///
/// output Pitch_ParaFct0_RetVal   = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_ParaFct0_TestCase_3(void)
{
  //Step 1) Set pre-conditions
   //Step 2) Assign Input values
  Pitch_ParaFct0_Param1 = 255;
  Pitch_ParaFct0_Param2 = &Coding_Dummy;
  Pitch_ParaFct0_RetVal = TRUE;

  //Step 3) Call FUT
  Pitch_ParaFct0_RetVal = Pitch_ParaFct0(Pitch_ParaFct0_Param1, Pitch_ParaFct0_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_ParaFct0_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Pitch_Pitch_ParaFct0_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Test that the function checks the coding data is valid or not
///                    
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions: 
///
///input Pitch_ParaFct0_Param1 = eParaFct0_CodingDataValid
///input Pitch_ParaFct0_Param2 = NULL_PTR;
///input Pitch_ParaFct0_RetVal = FALSE;
///
/// - Expectations:
///
/// output Pitch_ParaFct0_RetVal   = FALSE
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_ParaFct0_TestCase_4(void)
{
  //Step 1) Set pre-conditions
   //Step 2) Assign Input values
  Pitch_ParaFct0_Param1 = eParaFct0_CodingDataValid;
  Pitch_ParaFct0_Param2 = NULL_PTR;
  Pitch_ParaFct0_RetVal = TRUE;

  //Step 3) Call FUT
  Pitch_ParaFct0_RetVal = Pitch_ParaFct0(Pitch_ParaFct0_Param1, Pitch_ParaFct0_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_ParaFct0_RetVal, FALSE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_ParaFct0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if all the cases are covered in the coding data validity check
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_ParaFct0(void)
{
  Mt_Pitch_Pitch_ParaFct0_TestCase_1();
  Mt_Pitch_Pitch_ParaFct0_TestCase_2();
  Mt_Pitch_Pitch_ParaFct0_TestCase_3();
  Mt_Pitch_Pitch_ParaFct0_TestCase_4();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_CodingDataValidation
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function reads the Pitch CodingDataValidation is true or false
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///      input Pitch_CodingDataValidation_RetVal      = FALSE;
///      input Rte_Read_CodM_Pitch_Para_HitCount      = 0;
///      input Coding_State                  = eParaFct0_CodingDataValid;
///      input Rte_Read_CodM_Pitch_Para_Param1.eCodingState = eParaFct0_CodingDataInvalid;
///
///       Expectations:
///     output Rte_Read_CodM_Pitch_Para_HitCount =    1;
///     output Pitch_CodingDataValidation_RetVal = TRUE;
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CodingDataValidation(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Pitch_CodingDataValidation_RetVal       = FALSE;
  Rte_Read_CodM_Pitch_Para_HitCount       = 0;
  Coding_State                 = eParaFct0_CodingDataValid;
  Rte_Read_CodM_Pitch_Para_Param1.eCodingState = eParaFct0_CodingDataInvalid;

  //Step 3) Call FUT
  Pitch_CodingDataValidation_RetVal = Pitch_CodingDataValidation();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CodM_Pitch_Para_HitCount,   1u,   == );
  AL_UNITTEST_CHECK(Pitch_CodingDataValidation_RetVal, TRUE,   == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_SetLocal_DisplacementSens
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that the function to check the signal qauntity anD ndisp VALUES
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///     input Pitch_SetLocal_DisplacementSens_Param1.nDisp[0u]   = 2u;
///    input Pitch_SetLocal_DisplacementSens_Param1.eSigQty[0u] = 1u;
///    input Pitch_SetLocal_DisplacementSens_Param1.nDisp[1u]   = 2u;
///    input Pitch_SetLocal_DisplacementSens_Param1.eSigQty[1u] = 1u;
///
///       Expectations:
///     output sPitch_DispSens.eSigQty[0u] = 1u
///     output sPitch_DispSens.nDisp[0u]   = 2u
///     output sPitch_DispSens.nDisp[1u]   = 2u
///     output sPitch_DispSens.eSigQty[1u] = 1u
///
//-----------------------------------------------------------------------------

void Mt_Pitch_Pitch_SetLocal_DisplacementSens(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Pitch_SetLocal_DisplacementSens_Param1.nDisp[0u]  = 2u;
  Pitch_SetLocal_DisplacementSens_Param1.eSigQty[0u]  = 1u;
  Pitch_SetLocal_DisplacementSens_Param1.nDisp[1u]  = 2u;
  Pitch_SetLocal_DisplacementSens_Param1.eSigQty[1u]  = 1u;

  //Step 3) Call FUT
  Pitch_SetLocal_DisplacementSens(Pitch_SetLocal_DisplacementSens_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(sPitch_DispSens.eSigQty[0u], 1u,  == );
  AL_UNITTEST_CHECK(sPitch_DispSens.nDisp[0u],   2u,  == );
  AL_UNITTEST_CHECK(sPitch_DispSens.eSigQty[1u], 1u,  == );
  AL_UNITTEST_CHECK(sPitch_DispSens.nDisp[1u],   2u,  == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_RteAccess_Get_CodingPara
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   check the function to get the coding state is valid or not for invalid coding data input
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///      input Rte_Read_CodM_Pitch_Para_HitCount             = 0u;
///      input Rte_Read_CodM_Pitch_Para_Param1.eCodingState         = eParaFct0_CodingDataValid;
///      input Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
///
///       Expectations:
///      output Rte_Read_CodM_Pitch_Para_HitCount          = 1u
///      output Pitch_RteAccess_Get_CodingPara_Param1.eCodingState = eParaFct0_CodingDataInvalid
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_RteAccess_Get_CodingPara(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value
  Rte_Read_CodM_Pitch_Para_HitCount              = 0u;
  Rte_Read_CodM_Pitch_Para_Param1.eCodingState        = eParaFct0_CodingDataValid;
  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;

  //Step 3) Call FUT
  Pitch_RteAccess_Get_CodingPara(&Pitch_RteAccess_Get_CodingPara_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CodM_Pitch_Para_HitCount,                       1u, == );
  AL_UNITTEST_CHECK(Pitch_RteAccess_Get_CodingPara_Param1.eCodingState,   eParaFct0_CodingDataValid, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_RteAccess_Set_Angle
///
/// \Functional Safety: NA
///
/// \Test Case Description check the function to get the Set_Angle parameters
///    - Test subject:  check the function to set the  pitch_angle parameters based on given inputs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///      input Rte_Write_Pitch_Angle_HitCount               = 0u;
///      input Pitch_RteAccess_Set_Angle_Param1.eSigQty     = 2u;
///      input Pitch_RteAccess_Set_Angle_Param1.nAngle      = 2u;
///      input Pitch_RteAccess_Set_Angle_Param1.nHeightErr  = 2u;
///
///       Expectations:
///
///       output Rte_Write_Pitch_Angle_HitCount          =1u;
///       output Rte_Write_Pitch_Angle_Param1.eSigQty     =2u;
///       output Rte_Write_Pitch_Angle_Param1.nAngle    =2u;
///       output Rte_Write_Pitch_Angle_Param1.nHeightErr  =2u;
///
//-----------------------------------------------------------------------------/
void Mt_Pitch_Pitch_RteAccess_Set_Angle(void)
{

  //Step 1) Set pre-conditions
  //Step 2) Assign Input value
  Rte_Write_Pitch_Angle_HitCount          = 0u;
  Pitch_RteAccess_Set_Angle_Param1.eSigQty    = 2u;
  Pitch_RteAccess_Set_Angle_Param1.nAngle     = 2u;
  Pitch_RteAccess_Set_Angle_Param1.nHeightErr = 2u;

  //Step 3) Call FUT
  Pitch_RteAccess_Set_Angle(&Pitch_RteAccess_Set_Angle_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_Pitch_Angle_HitCount,          1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_Angle_Param1.eSigQty,    2u,  == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_Angle_Param1.nAngle,     2u,  == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_Angle_Param1.nHeightErr, 2u,  == );


}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_RteAccess_Set_SensorFailureState_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///    - Test subject:  check the  function to write the Pitch_PlausState parameters
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///     input Rte_Write_Pitch_PlausState_HitCount       = 0u;
///     input Pitch_RteAccess_Set_SensorFailureState_Param1 = eHLS_NO_FAILURE
///
///       Expectations:
///      output Rte_Write_Pitch_PlausState_HitCount   = 1u
///      output Rte_Write_Pitch_PlausState_Param1     = eHLS_NO_FAILURE
///
//-----------------------------------------------------------------------------/
void Mt_Pitch_Pitch_RteAccess_Set_SensorFailureState_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value
  Rte_Write_Pitch_PlausState_HitCount        = 0u;
  Pitch_RteAccess_Set_SensorFailureState_Param1 = eHLS_NO_FAILURE;

  //Step 3) Call FUT
  Pitch_RteAccess_Set_SensorFailureState(&Pitch_RteAccess_Set_SensorFailureState_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_HitCount,        1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_Param1, eHLS_NO_FAILURE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_RteAccess_Set_SensorFailureState_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description 
///    - Test subject : check the function to update the Pitch_PlausState_Parameters  based  on given inputs 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
///      input Rte_Write_Pitch_PlausState_HitCount       = 0;
///      input Pitch_RteAccess_Set_SensorFailureState_Param1 = eHLS_SENSOR_FAILURE;
///       Expectations:
///      output Rte_Write_Pitch_PlausState_HitCount = 1u
///      output Rte_Write_Pitch_PlausState_Param1   = eHLS_SENSOR_FAILURE
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_RteAccess_Set_SensorFailureState_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value
  Rte_Write_Pitch_PlausState_HitCount        = 0u;
  Pitch_RteAccess_Set_SensorFailureState_Param1 = eHLS_SENSOR_FAILURE;

  //Step 3) Call FUT
  Pitch_RteAccess_Set_SensorFailureState(&Pitch_RteAccess_Set_SensorFailureState_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_HitCount,            1u,  == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_Param1,   eHLS_SENSOR_FAILURE, == );


}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_RteAccess_Set_SensorFailureState_TestCase_3
///
/// \Test Case Description 
///    - Test subject  : check the function to update the Pitch_PlausState_Parameters  based  on given inputs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
///      input Rte_Write_Pitch_PlausState_HitCount       = 0;
///      input Pitch_RteAccess_Set_SensorFailureState_Param1 = eHLS_FROZEN_FAILURE;
///
///       Expectations:
///
///      output Rte_Write_Pitch_PlausState_HitCount = 1u
///      output Rte_Write_Pitch_PlausState_Param1   = eHLS_FROZEN_FAILURE
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_RteAccess_Set_SensorFailureState_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value

  Rte_Write_Pitch_PlausState_HitCount        = 0u;
  Pitch_RteAccess_Set_SensorFailureState_Param1 = eHLS_FROZEN_FAILURE;
  //Step 3) Call FUT
  Pitch_RteAccess_Set_SensorFailureState(&Pitch_RteAccess_Set_SensorFailureState_Param1);
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_HitCount,          1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_Param1, eHLS_FROZEN_FAILURE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_RteAccess_Set_SensorFailureState_TestCase_4
///
/// \Test Case Description
///    - Test subject  : check the function to update the Pitch_PlausState_Parameters  based  on given inputs 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
///      input Rte_Write_Pitch_PlausState_HitCount       = 0;
///      input Pitch_RteAccess_Set_SensorFailureState_Param1 = eHLS_STORED_FAILURE;
///
///       Expectations:
///
///      output Rte_Write_Pitch_PlausState_HitCount = 1u
///      output Rte_Write_Pitch_PlausState_Param1   = eHLS_STORED_FAILURE
//----------------------------------------------------------------------------- 
void Mt_Pitch_Pitch_RteAccess_Set_SensorFailureState_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value

  Rte_Write_Pitch_PlausState_HitCount        = 0;
  Pitch_RteAccess_Set_SensorFailureState_Param1 = eHLS_STORED_FAILURE;

  //Step 3) Call FUT
  Pitch_RteAccess_Set_SensorFailureState(&Pitch_RteAccess_Set_SensorFailureState_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_HitCount,         1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_Param1, eHLS_STORED_FAILURE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_RteAccess_Set_SensorFailureState_TestCase_5
///
/// \Test Case Description 
///    - Test subject:   check the function to update the Pitch_PlausState_Parameters  based  on given inputs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
///    input Rte_Write_Pitch_PlausState_HitCount        = 0u;
///    input Pitch_RteAccess_Set_SensorFailureState_Param1   = 255u;
///
///       Expectations:
///
///      output Rte_Write_Pitch_PlausState_HitCount = 1u
///      output Rte_Write_Pitch_PlausState_Param1   = 0u
//-----------------------------------------------------------------------------/ 
void Mt_Pitch_Pitch_RteAccess_Set_SensorFailureState_TestCase_5(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value  
  Rte_Write_Pitch_PlausState_HitCount        = 0u;
  Pitch_RteAccess_Set_SensorFailureState_Param1 = 255u;

  //Step 3) Call FUT
  Pitch_RteAccess_Set_SensorFailureState(&Pitch_RteAccess_Set_SensorFailureState_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_Param1,   0u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_RteAccess_Set_SensorFailureState
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if the function updates the Pitch_PlausState_Parameters according to all given inputs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_RteAccess_Set_SensorFailureState(void)
{
  Mt_Pitch_Pitch_RteAccess_Set_SensorFailureState_TestCase_1();
  Mt_Pitch_Pitch_RteAccess_Set_SensorFailureState_TestCase_2();
  Mt_Pitch_Pitch_RteAccess_Set_SensorFailureState_TestCase_3();
  Mt_Pitch_Pitch_RteAccess_Set_SensorFailureState_TestCase_4();
  Mt_Pitch_Pitch_RteAccess_Set_SensorFailureState_TestCase_5();
}

//----------------------------------------------------------------------------------------------------------------------------------------/
/// \Test Case : Mt_Pitch_Pitch_RteAccess_Get_VehicleSpeed
///
/// \Functional Safety: NA
///
/// \Test Case Description 
///    - Test subject:  check the function to get the vehicle speed parameters  based on given inputs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
///     input  Rte_Read_SysMon_VehicleSpeed_HitCount                       = 0u;
///     input  Rte_Read_SysMon_VehicleSpeed_Param1.eChksumTrmeDynUcFrein.ucChksumTrmeDynUcFrein = 2u;
///     input  Rte_Read_SysMon_VehicleSpeed_Param1.eCptProcess4B38D.ucCptProcess4B38D       = 4u;
///     input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                     = SIG_INVALID;
///     input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed         = 4u;
///     input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo               = eVvhIndisp_SpeedInfoUnavailable;
///
///       Expectations:
///      output Rte_Read_SysMon_VehicleSpeed_HitCount                        = 1u
///      output Pitch_RteAccess_Get_VehicleSpeed_Param1.eChksumTrmeDynUcFrein.ucChksumTrmeDynUcFrein= 2u
///      output Pitch_RteAccess_Get_VehicleSpeed_Param1.eCptProcess4B38D.ucCptProcess4B38D      = 4u
///      output Pitch_RteAccess_Get_VehicleSpeed_Param1.eSigQty                    = SIG_INVALID
///      output Pitch_RteAccess_Get_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed        = 4u
///      output Pitch_RteAccess_Get_VehicleSpeed_Param1.eVehicleSpeedDispo              = eVvhIndisp_SpeedInfoUnavailable
///
//----------------------------------------------------------------------------------------------------------------------------------------/ 
void Mt_Pitch_Pitch_RteAccess_Get_VehicleSpeed(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value

  Rte_Read_SysMon_VehicleSpeed_HitCount                       = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eChksumTrmeDynUcFrein.ucChksumTrmeDynUcFrein = 2u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eCptProcess4B38D.ucCptProcess4B38D       = 4u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty                     = SIG_INVALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed         = 4u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeedDispo               = eVvhIndisp_SpeedInfoUnavailable;

  //Step 3) Call FUT
  Pitch_RteAccess_Get_VehicleSpeed(&Pitch_RteAccess_Get_VehicleSpeed_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,                          1u, == );
  AL_UNITTEST_CHECK(Pitch_RteAccess_Get_VehicleSpeed_Param1.eChksumTrmeDynUcFrein.ucChksumTrmeDynUcFrein,   2u, == );
  AL_UNITTEST_CHECK(Pitch_RteAccess_Get_VehicleSpeed_Param1.eCptProcess4B38D.ucCptProcess4B38D,          4u, == );
  AL_UNITTEST_CHECK(Pitch_RteAccess_Get_VehicleSpeed_Param1.eSigQty,                   SIG_INVALID, == );
  AL_UNITTEST_CHECK(Pitch_RteAccess_Get_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed,                   4u, == );
  AL_UNITTEST_CHECK(Pitch_RteAccess_Get_VehicleSpeed_Param1.eVehicleSpeedDispo,eVvhIndisp_SpeedInfoUnavailable, == );


}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase1
///
/// \Functional Safety: NA
///
/// \Test Case Description :
///    - Test subject:   check the  function to get the  ADL phase parameters based on given inputs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///     input Rte_Read_CtrlStp_Validation_Port_HitCount       = 0u;
///     input Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE = eStpState_Init;
///  
///       Expectations:
///     output Pitch_RteAccess_Get_GetAdlPhase_Param1    = ePitchState_Init
///     output Rte_Read_CtrlStp_Validation_Port_HitCount = 1u
///
//-----------------------------------------------------------------------------/ 
void Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value

  Rte_Read_CtrlStp_Validation_Port_HitCount       = 0u;
  Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE = eStpState_Init;


  //Step 3) Call FUT
  Pitch_RteAccess_Get_GetAdlPhase(&Pitch_RteAccess_Get_GetAdlPhase_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_RteAccess_Get_GetAdlPhase_Param1, ePitchState_Init, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_Validation_Port_HitCount,      1u, == );



}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  check the function to get the ADL phase parameters based on given inputs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///     input Rte_Read_CtrlStp_Validation_Port_HitCount = 0u
///     input Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE = eStpState_Ref
///
///       Expectations:
///     output Pitch_RteAccess_Get_GetAdlPhase_Param1    = ePitchState_Ref
///     output Rte_Read_CtrlStp_Validation_Port_HitCount = 1u
///
//-----------------------------------------------------------------------------/ 
void Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value

  Rte_Read_CtrlStp_Validation_Port_HitCount       = 0u;
  Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE = eStpState_Ref;

  //Step 3) Call FUT
  Pitch_RteAccess_Get_GetAdlPhase(&Pitch_RteAccess_Get_GetAdlPhase_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_RteAccess_Get_GetAdlPhase_Param1, ePitchState_Ref, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_Validation_Port_HitCount,       1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  check the function to get the ADL phase parameters based on given inputs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///     input  Rte_Read_CtrlStp_Validation_Port_HitCount       = 0u;
///     input  Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE = eStpState_Adj;
///
///       Expectations:
///     output Pitch_RteAccess_Get_GetAdlPhase_Param1    = ePitchState_Adj
///     output Rte_Read_CtrlStp_Validation_Port_HitCount = 1u
///
//-----------------------------------------------------------------------------/ 
void Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value

  Rte_Read_CtrlStp_Validation_Port_HitCount       = 0u;
  Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE = eStpState_Adj;
  //Step 3) Call FUT
  Pitch_RteAccess_Get_GetAdlPhase(&Pitch_RteAccess_Get_GetAdlPhase_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_RteAccess_Get_GetAdlPhase_Param1, ePitchState_Adj, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_Validation_Port_HitCount,           1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  check the function to get the ADL phase parameters based on given inputs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///     input Rte_Read_CtrlStp_Validation_Port_HitCount = 0u;
///     input Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE = eStpState_Fail;
///
///       Expectations:
///     output Pitch_RteAccess_Get_GetAdlPhase_Param1    = ePitchState_Fail
///     output Rte_Read_CtrlStp_Validation_Port_HitCount = 1u
///
//-----------------------------------------------------------------------------/ 
void Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value

  Rte_Read_CtrlStp_Validation_Port_HitCount          = 0u;
  Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE = eStpState_Fail;

  //Step 3) Call FUT
  Pitch_RteAccess_Get_GetAdlPhase(&Pitch_RteAccess_Get_GetAdlPhase_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_RteAccess_Get_GetAdlPhase_Param1, ePitchState_Fail,  == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_Validation_Port_HitCount,       1u, == );


}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  check the function to get the ADL phase parameters based on given inputs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///     input Rte_Read_CtrlStp_Validation_Port_HitCount       = 0u;
///     input Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE = eStpState_STT;
///
///       Expectations:
///     output Pitch_RteAccess_Get_GetAdlPhase_Param1    = ePitchState_STT
///     output Rte_Read_CtrlStp_Validation_Port_HitCount = 1u
///
//-----------------------------------------------------------------------------/ 
void Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase_5(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value

  Rte_Read_CtrlStp_Validation_Port_HitCount       = 0u;
  Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE = eStpState_STT;

  //Step 3) Call FUT
  Pitch_RteAccess_Get_GetAdlPhase(&Pitch_RteAccess_Get_GetAdlPhase_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_RteAccess_Get_GetAdlPhase_Param1, ePitchState_STT, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_Validation_Port_HitCount,       1u, == );


}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  check the function to get the ADL phase parameters based on given inputs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
///     input Rte_Read_CtrlStp_Validation_Port_HitCount      = 0u;
///     input Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE = eStpState_Maxsize;
/// 
///       Expectations:
///     output Pitch_RteAccess_Get_GetAdlPhase_Param1    = ePitchState_Maxsize
///     output Rte_Read_CtrlStp_Validation_Port_HitCount = 1u
///
//-----------------------------------------------------------------------------/ 
void Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase_6(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value

  Rte_Read_CtrlStp_Validation_Port_HitCount       = 0u;
  Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE = eStpState_Maxsize;
  //Step 3) Call FUT
  Pitch_RteAccess_Get_GetAdlPhase(&Pitch_RteAccess_Get_GetAdlPhase_Param1);
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_RteAccess_Get_GetAdlPhase_Param1, ePitchState_Maxsize, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_Validation_Port_HitCount,               1u, == );


}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  check the function to get the ADL phase parameters based on given inputs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
///     input  Rte_Read_CtrlStp_Validation_Port_HitCount       = 0u;
///     input  Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE = eStpState_Maxsize + 1;
///     input  tePitch_AdlPhase tmpRand               = 0; // (tePitch_AdlPhase)rand();
///     input  Pitch_RteAccess_Get_GetAdlPhase_Param1         = tmpRand;
///
///       Expectations:
///     output Pitch_RteAccess_Get_GetAdlPhase_Param1    = tmpRand
///
//-----------------------------------------------------------------------------/ 
void Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase_7(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value

  Rte_Read_CtrlStp_Validation_Port_HitCount       = 0u;
  Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE = eStpState_Maxsize + 1;
  tePitch_LvlPhase tmpRand               = 0; // (tePitch_AdlPhase)rand();
  Pitch_RteAccess_Get_GetAdlPhase_Param1         = tmpRand;

  //Step 3) Call FUT
  Pitch_RteAccess_Get_GetAdlPhase(&Pitch_RteAccess_Get_GetAdlPhase_Param1);
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_RteAccess_Get_GetAdlPhase_Param1, tmpRand, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase8
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  check the function to get the ADL phase parameters based on given inputs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
///     input  Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE = eStpState_Maxsize;
///     input  tePitch_AdlPhase tmpRand               = 0;
///     input  Pitch_RteAccess_Get_GetAdlPhase_Param1             = tmpRand;
///
///       Expectations:
///     output Pitch_RteAccess_Get_GetAdlPhase_Param1     != tmpRand
///     output Rte_Read_CtrlStp_Validation_Port_HitCount  = 2u
///
//-----------------------------------------------------------------------------/ 
void Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase_8(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value
  Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE = eStpState_Maxsize;
  tePitch_LvlPhase tmpRand               = 0;
  Pitch_RteAccess_Get_GetAdlPhase_Param1             = tmpRand;

  //Step 3) Call FUT

  Pitch_RteAccess_Get_GetAdlPhase(&Pitch_RteAccess_Get_GetAdlPhase_Param1);
  //Step 4) Check expected output values

  AL_UNITTEST_CHECK(Pitch_RteAccess_Get_GetAdlPhase_Param1,     tmpRand,   != );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_Validation_Port_HitCount,       2u,   == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if all the ADL phase parameters are set correctly in all cases
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase(void)
{
  Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase_1();
  Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase_2();
  Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase_3();
  Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase_4();
  Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase_5();
  Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase_6();
  Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase_7();
  Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase_TestCase_8();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_RteAccess_Get_GetSens_Raw
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: function for Rte_Read_IoHwAb_GetSens_Raw
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
///     input  Pitch_RteAccess_Get_GetSens_Raw_Param1 = 1u;  
///     input  Rte_Read_IoHwAb_GetSens_Raw_HitCount   = 0u;
///
///       Expectations:
///     output Rte_Read_IoHwAb_GetSens_Raw_HitCount  = 1u
///
//-----------------------------------------------------------------------------/ 
void Mt_Pitch_Pitch_RteAccess_Get_GetSens_Raw(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value

  Pitch_RteAccess_Get_GetSens_Raw_Param1 = 1u;  
  Rte_Read_IoHwAb_GetSens_Raw_HitCount   = 0u;

  //Step 3) Call FUT
  Pitch_RteAccess_Get_GetSens_Raw(&Pitch_RteAccess_Get_GetSens_Raw_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_GetSens_Raw_HitCount, 1u, == );

}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_RteAccess_Get_GetSens_Balanced
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  check the  function for Rte_Read_IoHwAb_GetSens_Balanced
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
///     input  Rte_Read_IoHwAb_GetSens_Balanced_HitCount = 0u;  
///
///       Expectations:
///     output Rte_Read_IoHwAb_GetSens_Balanced_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_RteAccess_Get_GetSens_Balanced(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value

  Rte_Read_IoHwAb_GetSens_Balanced_HitCount = 0u;

  //Step 3) Call FUT
  Pitch_RteAccess_Get_GetSens_Balanced(&Pitch_RteAccess_Get_GetSens_Balanced_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_GetSens_Balanced_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_RteAccess_Get_VCCX1Voltage
///
/// \Functional Safety: NA
///
/// \Test Case Description 
///    - Test subject:  check the function for Pitch_RteAccess_Get_VCCX1Voltage
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
///     input  Rte_Read_IoHwAb_VCCX1Voltage_HitCount = 0u;
///     input  Rte_Read_IoHwAb_VCCX1Voltage_Param1   = 1u;
///  
///       Expectations:
///   
///     output Rte_Read_IoHwAb_VCCX1Voltage_HitCount   = 1u
///     output Pitch_RteAccess_Get_VCCX1Voltage_Param1 = 1u
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_RteAccess_Get_VCCX1Voltage(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value

  Rte_Read_IoHwAb_VCCX1Voltage_HitCount = 0u;
  Rte_Read_IoHwAb_VCCX1Voltage_Param1   = 1u;

  //Step 3) Call FUT
  Pitch_RteAccess_Get_VCCX1Voltage(&Pitch_RteAccess_Get_VCCX1Voltage_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_VCCX1Voltage_HitCount,   1u, == );
  AL_UNITTEST_CHECK(Pitch_RteAccess_Get_VCCX1Voltage_Param1, 1u, == );


}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Pitch_Pitch_RteAccess_Get_VehNetState
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  checking the function for Rte_Read_SysMon_VehNetState
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
///     input  Rte_Read_SysMon_VehNetStat_HitCount             = 0u;
///     input  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTI_DEGRADE;
///     input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState     = VESState_Start;
///     input  Rte_Read_SysMon_VehNetState_Param1.eSigQty         = SIG_E2E_ALIVEERR;
///  
///       Expectations:
///   
///     output  Rte_Read_SysMon_VehNetStat_HitCount              = 1u                  
///     output  Pitch_RteAccess_Get_VehNetState_Param1.eElectricNetworkState   = eTI_DEGRADE
///     output  Pitch_RteAccess_Get_VehNetState_Param1.eVESMainState           = VESState_Start    
///     output  Pitch_RteAccess_Get_VehNetState_Param1.eSigQty          = SIG_E2E_ALIVEERR      
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_RteAccess_Get_VehNetState(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  // Step 1) Set pre-conditions
  // Step 2) Assign Input value
  //-----------------------------------------------------------------------------

  Rte_Read_SysMon_VehNetState_HitCount           = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eElectricNetworkState = eTI_DEGRADE;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState     = VESState_Start;
  Rte_Read_SysMon_VehNetState_Param1.eSigQty         = SIG_E2E_ALIVEERR;

  //-----------------------------------------------------------------------------
  // Function call
  // Step 3) Call FUT
  //-----------------------------------------------------------------------------
  Pitch_RteAccess_Get_VehNetState(&Pitch_RteAccess_Get_VehNetState_Param1);

  //-----------------------------------------------------------------------------
  // Outputs
  // Step 4) Check expected output values
  //----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount,                      1u,   == );
  AL_UNITTEST_CHECK(Pitch_RteAccess_Get_VehNetState_Param1.eElectricNetworkState,       eTI_DEGRADE,  == );
  AL_UNITTEST_CHECK(Pitch_RteAccess_Get_VehNetState_Param1.eVESMainState,            VESState_Start,  == );
  AL_UNITTEST_CHECK(Pitch_RteAccess_Get_VehNetState_Param1.eSigQty,                SIG_E2E_ALIVEERR,  == );


}

//------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_CheckVehSpeedData_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: check the function for vehicle speed and signal quality
///        Returns TRUE if data is OK and FALSE if data is NOK
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// - Preconditions: 
///
/// \input
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount               = 0u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty             = SIG_VALID;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 3002u;
///
///
/// - Expectations:
///
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount       = 1u
/// \output Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty      = SIG_VALID
/// \output Pitch_CheckVehSpeedData_RetVal                   = ePlauSig_Pass
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckVehSpeedData_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value
  //-----------------------------------------------------------------------------

  Rte_Read_SysMon_VehicleSpeed_HitCount               = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty             = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 3002u;

  //-----------------------------------------------------------------------------
  // Function call
  // Step 3) Call FUT
  //-----------------------------------------------------------------------------
  Pitch_CheckVehSpeedData_RetVal = Pitch_CheckVehSpeedData();

  //-----------------------------------------------------------------------------
  // Outputs
  // Step 4) Check expected output values
  //----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,        1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty, SIG_VALID, == );
  AL_UNITTEST_CHECK(Pitch_CheckVehSpeedData_RetVal,          ePlauSig_Pass, == );


}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_CheckVehSpeedData_TestCase2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  checking the function for vehicle speed and signal quality
///        Returns TRUE if data is OK and FALSE if data is NOK
///    - Test Design Technique: ET (Exploratory Testing)
/// - Preconditions:
///
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount               = 0u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty             = SIG_INVALID;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 3002u;
///
/// - Expectations:
///
/// 
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount      =           1u ;
/// \output Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty  =  SIG_INVALID ;
/// \output Pitch_CheckVehSpeedData_RetVal           = ePlauSig_Fail;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckVehSpeedData_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value
  //-----------------------------------------------------------------------------
  Rte_Read_SysMon_VehicleSpeed_HitCount               = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty             = SIG_INVALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 3002u;
  //-----------------------------------------------------------------------------
  // Function call
  //Step 3) Call FUT
  //----------------------------------------------------------------------------
  Pitch_CheckVehSpeedData_RetVal = Pitch_CheckVehSpeedData();
  //-----------------------------------------------------------------------------
  // Outputs
  // Step 4) Check expected output values
  //-----------------------------------------------------------------------------
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,        1u, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty, SIG_INVALID, == );
  AL_UNITTEST_CHECK(Pitch_CheckVehSpeedData_RetVal,       ePlauSig_Fail, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_CheckVehSpeedData
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckVehSpeedData(void)
{
  Mt_Pitch_Pitch_CheckVehSpeedData_TestCase_1();
  Mt_Pitch_Pitch_CheckVehSpeedData_TestCase_2();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_FailureCheckPlausibility_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  This function is checking the sensor plausibility state when Adl phase
///        is read as Failure and is setting the Sensor Failure state for CtrlStp
///    - Test Design Technique: ET (Exploratory Testing)
///
///     - Preconditions:
///
/// \input  Rte_Read_SysMon_VehNetState_HitCount        = 0u;
/// \input  Rte_Write_Pitch_PlausState_HitCount          = 0u;
/// \input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState    = VESState_Stop;
/// \input  Pitch_ePitchSensorFailure              = eHLS_FROZEN_FAILURE;
///
/// - Expectations:
///
/// 
/// \output Rte_Read_SysMon_VehNetState_HitCount =        1u;
/// \output  Rte_Write_Pitch_PlausState_HitCount   =        1u;
/// \output Rte_Write_Pitch_PlausState_Param1    = eSTORED_FAILURE;
///
//-----------------------------------------------------------------------------

void Mt_Pitch_Pitch_FailureCheckPlausibility_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  /*Step 2) Assign Input value*/

  Rte_Read_SysMon_VehNetState_HitCount = 0u;
  Rte_Write_Pitch_PlausState_HitCount = 0u;
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Stop;
  Pitch_ePitchSensorFailure = eHLS_FROZEN_FAILURE;


  //Step 3) Call FUT
  Pitch_FailureCheckPlausibility();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_HitCount, 1u, == );
  //AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_Param1, eSTORED_FAILURE, == );


}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_FailureCheckPlausibility_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  This function is checking the sensor plausibility state when Adl phase
///        is read as Failure and is setting the Sensor Failure state for CtrlStp
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input    Rte_Read_Cpm_CtrlPxl_DeratedMtxPixels_HitCount = 0u
/// \input   Rte_Read_SysMon_VehNetState_Param1.eVESMainState           = VESState_Start;
/// \input   Pitch_ePitchSensorFailure                       = eHLS_FROZEN_FAILURE;
/// \input   Pitch_RteAccess_Get_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 200u;
/// \input   Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed   = 200u;
/// \input   Pitch_pCodingArea->AvacStp.PitchData.BhsPlausVehSpeed         = 1u;
/// \input   Pitch_RteAccess_Get_VehicleSpeed_Param1.eSigQty             = SIG_VALID;
/// \input   Rte_Read_SysMon_VehNetState_HitCount                 = 0u;
/// \input   Rte_Write_Pitch_PlausState_HitCount                   = 0u;
/// 
/// \input   Pitch_pCodingArea->AvacStp.PitchData.BhsPlausMin           = 15;
/// \input   Pitch_pCodingArea->AvacStp.PitchData.BhsPlausMax           = 30;
/// \input   Rte_Read_IoHwAb_GetSens_Balanced_HitCount               = 0u;
/// \input   Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[0]       = 600u;
/// \input   Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[1]       = 1400u;
/// \input   boBhsValCheck                             = TRUE;
/// \input   LPTMR0_GetTimeElapsed_RetVal                     = 0xFFFFu;
/// 
/// \input   Rte_Read_SysMon_VehicleSpeed_HitCount                 = 0u;
/// \input   Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty               = SIG_VALID;
/// \input   Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed   = 3002u;
///
/// - Expectations: 
///
/// \output  Rte_Read_SysMon_VehNetState_HitCount     =  1u;
/// \output  Rte_Write_Pitch_PlausState_HitCount     =  1u;
/// \output  Pitch_CheckVehSpeedData_RetVal         =  PlauSig_Fail;
/// \output  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty =  SIG_VALID;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_FailureCheckPlausibility_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value
  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Start;
  Pitch_ePitchSensorFailure = eHLS_FROZEN_FAILURE;
  Pitch_RteAccess_Get_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 200u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 200u;
  Pitch_pCodingArea->AvacStp.PitchData.BhsPlausVehSpeed = 1u;
  Pitch_RteAccess_Get_VehicleSpeed_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehNetState_HitCount = 0u;
  Rte_Write_Pitch_PlausState_HitCount = 0u;

  Rte_Read_IoHwAb_GetSens_Balanced_HitCount = 0u;
  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[0] = 600u;
  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[1] = 1400u;
  boBhsValCheck = TRUE;
  LPTMR0_GetTimeElapsed_RetVal = 0xFFFFu;

  Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 3002u;

  //Step 3) Call FUT
  Pitch_FailureCheckPlausibility();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Pitch_CheckVehSpeedData_RetVal, ePlauSig_Fail, == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty, SIG_VALID, == );


}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_FailureCheckPlausibility_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  This function is checking the sensor plausibility state when Adl phase
///        is read as Failure and is setting the Sensor Failure state for CtrlStp
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  Rte_Read_SysMon_VehNetState_Param1.eVESMainState         = VESState_Start;
/// \input  Pitch_ePitchSensorFailure                     = eHLS_SENSOR_FAILURE;
/// \input  Rte_Read_SysMon_VehNetState_HitCount               = 0u;
/// \input  Rte_Write_Pitch_PlausState_HitCount                 = 0u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens         = 1u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens         = 2u;
/// \input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0]         = 600u; 
/// \input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1]         = 600u;
/// \input  boDispValCheck                           = TRUE;
/// \input  Pitch_CheckSensValue_RetVal                     = ePlauSig_SNA;
/// \input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[PITCH_FR_SENSOR] = 0u;
/// \input  Rte_Read_IoHwAb_GetSens_Raw_HitCount               = 0u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.SensorOutRangeTime        = 1u;
/// \input  LPTMR0_GetTimeElapsed_HitCount                   = 0u;
/// \input  LPTMR0_GetTimeElapsed_RetVal                   = 0xFFFFu;
///
/// - Expectations: 
///
/// \output  Rte_Read_SysMon_VehNetState_HitCount  = 1u;
/// \output  Rte_Read_SysMon_VehNetState_HitCount  = 1u;
/// \output  Rte_Write_Pitch_PlausState_HitCount   = 1u;
/// \output  Rte_Read_IoHwAb_GetSens_Raw_HitCount  = 1u;
/// \output  Rte_Write_Pitch_PlausState_Param1     = ePlauSig_Pas;
/// \output  Pitch_CheckSensValue_RetVal       = ePlauSig_SNA;
/// \output  boDispValCheck               = FALSE;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_FailureCheckPlausibility_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value

  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Start;
  Pitch_ePitchSensorFailure = eHLS_SENSOR_FAILURE;
  Rte_Read_SysMon_VehNetState_HitCount = 0u;
  Rte_Write_Pitch_PlausState_HitCount = 0u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 2u;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0] = 600u;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1] = 600u;
  boDispValCheck[1] = TRUE;
  Pitch_CheckSensValue_RetVal = ePlauSig_SNA;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[PITCH_FR_SENSOR] = 0u;
  Rte_Read_IoHwAb_GetSens_Raw_HitCount = 0u;
  Pitch_pCodingArea->AvacStp.PitchData.SensorOutRangeTime = 1u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 0xFFFFu;

  //Step 3) Call FUT
  Pitch_FailureCheckPlausibility();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_GetSens_Raw_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_Param1, ePlauSig_Pass, == );
  AL_UNITTEST_CHECK(Pitch_CheckSensValue_RetVal, ePlauSig_SNA, == );
  AL_UNITTEST_CHECK(boDispValCheck[1], TRUE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_FailureCheckPlausibility_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  This function is checking the sensor plausibility state when Adl phase
///        is read as Failure and is setting the Sensor Failure state for CtrlStp
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input   Rte_Read_SysMon_VehNetState_Param1.eVESMainState         = VESState_Start;
/// \input   Pitch_ePitchSensorFailure                     = eHLS_NO_FAILURE;
/// \input   Rte_Read_SysMon_VehNetState_HitCount               = 0u;
/// \input   Rte_Write_Pitch_PlausState_HitCount                 = 0u;
///
/// - Expectations: 
///
/// \output  Rte_Read_SysMon_VehNetState_HitCount = 1u;
/// \output  Rte_Write_Pitch_PlausState_HitCount  = 1u;
/// \output  Rte_Write_Pitch_PlausState_Param1    = eNO_FAILURE;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_FailureCheckPlausibility_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value

  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Start;
  Pitch_ePitchSensorFailure = eHLS_NO_FAILURE;
  Rte_Read_SysMon_VehNetState_HitCount = 0u;
  Rte_Write_Pitch_PlausState_HitCount = 0u;

  //Step 3) Call FUT
  Pitch_FailureCheckPlausibility();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_Param1, eNO_FAILURE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_FailureCheckPlausibility_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  This function is checking the sensor plausibility state when Adl phase
///        is read as Failure and is setting the FROZEN Failure state for CtrlStp
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input   Rte_Read_SysMon_VehNetState_Param1.eVESMainState   5= VESState_Stop;
/// \input   Pitch_ePitchSensorFailure                           = eHLS_FROZEN_FAILURE;
/// \input   Rte_Read_SysMon_VehNetState_HitCount               = 0u;
/// \input   Rte_Write_Pitch_PlausState_HitCount                 = 0u;
///
/// - Expectations: 
///
/// \output  Rte_Read_SysMon_VehNetState_HitCount = 1u;
/// \output  Rte_Write_Pitch_PlausState_HitCount  = 1u;
/// \output  Rte_Write_Pitch_PlausState_Param1    = eNO_FAILURE;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_FailureCheckPlausibility_TestCase_5(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value

  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Stop;
  Pitch_ePitchSensorFailure = eHLS_FROZEN_FAILURE;
  Rte_Read_SysMon_VehNetState_HitCount = 0u;
  Rte_Write_Pitch_PlausState_HitCount = 0u;

  //Step 3) Call FUT
  Pitch_FailureCheckPlausibility();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_Param1, eNO_FAILURE, == );


}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_FailureCheckPlausibility_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  This function is checking the sensor plausibility state when Adl phase
///        is read as Failure and is setting the SENSOR Failure state for CtrlStp
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input Rte_Read_SysMon_VehNetState_Param1.eVESMainState   = VESState_Start;
/// \input Pitch_ePitchSensorFailure                           = eHLS_SENSOR_FAILURE
/// \input Rte_Read_SysMon_VehNetState_HitCount               = 0u;
/// \input Rte_Write_Pitch_PlausState_HitCount                 = 0u;
/// \input Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0]   = 0x4000u;
/// \input Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1]   = 0x4000u;
/// \input boDispValCheck                                     = FALSE;
/// \input Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 10u;
/// \input Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 90u;
/// \input LPTMR0_GetTimeElapsed_RetVal                       = 0xFFFFFFFF;
///
/// - Expectations: 
///
/// \output  Rte_Read_SysMon_VehNetState_HitCount = 1u;
/// \output  Rte_Write_Pitch_PlausState_HitCount  = 1u;
/// \output  Rte_Write_Pitch_PlausState_Param1    = eNO_FAILURE;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_FailureCheckPlausibility_TestCase_6(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value

  Rte_Read_SysMon_VehNetState_Param1.eVESMainState = VESState_Start;
  Pitch_ePitchSensorFailure = eHLS_SENSOR_FAILURE;
  Rte_Read_SysMon_VehNetState_HitCount = 0u;
  Rte_Write_Pitch_PlausState_HitCount = 0u;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0] = 0x4000u;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1] = 0x4000u;
  boDispValCheck[1] = TRUE;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 10u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 90u;
  LPTMR0_GetTimeElapsed_RetVal = 0xFFFFFFFF;

  //Step 3) Call FUT
  Pitch_FailureCheckPlausibility();

  //Step 4) Check expected output value
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehNetState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_Param1, eNO_FAILURE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_FailureCheckPlausibility
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests the sensor plausibility state in the case of failures
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_FailureCheckPlausibility(void)
{
  Mt_Pitch_Pitch_FailureCheckPlausibility_TestCase_1();
  Mt_Pitch_Pitch_FailureCheckPlausibility_TestCase_2();
  Mt_Pitch_Pitch_FailureCheckPlausibility_TestCase_3();
  Mt_Pitch_Pitch_FailureCheckPlausibility_TestCase_4();
  Mt_Pitch_Pitch_FailureCheckPlausibility_TestCase_5();
  Mt_Pitch_Pitch_FailureCheckPlausibility_TestCase_6();
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Pitch_Pitch_AdjustmentCheckPlausibility_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  This function is checking the sensor plausibility state when Adl phase
///        is read as Adjustment and is setting the Sensor Failure state for CtrlStp
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount                 = 0u;
/// \input  Rte_Write_Pitch_PlausState_HitCount                   = 0u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.BhsPlausVehSpeed         = 1u;  
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed   = 120u;   
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty               = SIG_VALID;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens           = 1u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens           = 2u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.SensorOutRangeTime         = 1u;
/// \input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0u]           = 800u;
/// \input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1u]           = 800u;
/// \input  boDispValCheck                             = FALSE;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.BhsPlausVehSpeed         = 1u;
/// \input  Pitch_CheckSensValue_RetVal                       = ePlauSig_Fail;
/// \input  Pitch_CheckVehSpeedData_RetVal                     = ePlauSig_Fail;
/// \input  Rte_Read_IoHwAb_GetSens_Raw_HitCount                 = 0u;
/// \input  Pitch_ePitchSensorFailure                       = eSTORED_FAILURE;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.BhsPlausMin           = 1u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.BhsPlausMax           = 2u;
/// \input  LPTMR0_GetTimeElapsed_RetVal                     = 0xFFFFu;
///
/// - Expectations: 
///
/// \output  Rte_Write_Pitch_PlausState_HitCount   = 1u;
/// \output  Rte_Write_Pitch_PlausState_Param1     = eSTORED_FAILURE;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_AdjustmentCheckPlausibility_TestCase_1(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  // Step 1) Set pre-conditions
  // Step 2) Assign Input value
  //-----------------------------------------------------------------------------

  Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;
  Rte_Write_Pitch_PlausState_HitCount = 0u;
  Pitch_pCodingArea->AvacStp.PitchData.BhsPlausVehSpeed = 1u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 120u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = SIG_VALID;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 2u;
  Pitch_pCodingArea->AvacStp.PitchData.SensorOutRangeTime = 1u;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0u] = 800u;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1u] = 800u;
  boDispValCheck[0] = TRUE;
  Pitch_pCodingArea->AvacStp.PitchData.BhsPlausVehSpeed = 1u;
  Pitch_CheckSensValue_RetVal = ePlauSig_Fail;
  Pitch_CheckVehSpeedData_RetVal = ePlauSig_Fail;
  Rte_Read_IoHwAb_GetSens_Raw_HitCount = 0u;
  Pitch_ePitchSensorFailure = eSTORED_FAILURE;
  LPTMR0_GetTimeElapsed_RetVal = 0xFFFFu;
  //-----------------------------------------------------------------------------
  // Function call
  // Step 3) Call FUT
  //-----------------------------------------------------------------------------

  Pitch_AdjustmentCheckPlausibility();
  //-----------------------------------------------------------------------------
  // Outputs
  // Step 4) Check expected output values
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_Param1, eSTORED_FAILURE, == );


}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Pitch_Pitch_AdjustmentCheckPlausibility_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  This function is checking the sensor plausibility state when Adl phase
///        is read as Adjustment and is setting the Sensor Failure state for CtrlStp
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount               = 0u;
/// \input  Pitch_ePitchSensorFailure                     = eHLS_SENSOR_FAILURE;
/// \input  Rte_Write_Pitch_PlausState_HitCount                 = 0u;
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount               = 0u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty             = SIG_VALID;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 120u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.BhsPlausVehSpeed       = 1u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.BhsPlausMin         = 15u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.BhsPlausMax         = 30u;
/// \input  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[0]     = 600u;
/// \input  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[1]     = 600u;
/// \input  boBhsValCheck                           = FALSE;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens         = 1u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens         = 2u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.unSensor_Error_Time     = 1u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.unSensor_Recover_Time     = 1u;
/// \input  Rte_Read_IoHwAb_GetSens_Balanced_HitCount             = 0u;
/// \input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0]         = 800u;
/// \input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1]         = 800u;
/// \input  Pitch_CheckVehSpeedData_RetVal                   = ePlauSig_Fail;
/// \input  Pitch_CheckSensValue_RetVal                     = ePlauSig_Fail;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.SensorOutRangeTime       = 1u;
/// \input  LPTMR0_GetTimeElapsed_RetVal                   = 0xFFFFu;
/// \input  boDispValCheck                           = FALSE;
/// \input  Rte_Read_IoHwAb_GetSens_Raw_HitCount               = 0u;
/// \input  Pitch_ulCheckBHS_us                         = 20u;
///
/// - Expectations: 
///
/// \output  Rte_Write_Pitch_PlausState_HitCount           = 1u;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_AdjustmentCheckPlausibility_TestCase_2(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  // Step 1) Set pre-conditions
  // Step 2) Assign Input value
  //-----------------------------------------------------------------------------

  Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;
  Pitch_ePitchSensorFailure = eHLS_SENSOR_FAILURE;
  Rte_Write_Pitch_PlausState_HitCount = 0u;
  Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 120u;
  Pitch_pCodingArea->AvacStp.PitchData.BhsPlausVehSpeed = 1u;
  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[0] = 600u;
  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[1] = 600u;
  boBhsValCheck = FALSE;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 2u;
  Rte_Read_IoHwAb_GetSens_Balanced_HitCount = 0u;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0] = 800u;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1] = 800u;
  Pitch_CheckVehSpeedData_RetVal = ePlauSig_Fail;
  Pitch_CheckSensValue_RetVal = ePlauSig_Fail;
  Pitch_pCodingArea->AvacStp.PitchData.SensorOutRangeTime = 1u;
  LPTMR0_GetTimeElapsed_RetVal = 0xFFFFu;
  boDispValCheck[1] = TRUE;
  Rte_Read_IoHwAb_GetSens_Raw_HitCount = 0u;
  Pitch_ulCheckBHS_us = 20u;

  //Pitch_ePitchSensorFailure                     = eSTORED_FAILURE;


    //Step 3) Call FUT
  Pitch_AdjustmentCheckPlausibility();

  //-----------------------------------------------------------------------------
  // Outputs
  // Step 4) Check expected output values
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Pitch_Pitch_AdjustmentCheckPlausibility_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  This function is checking the sensor plausibility state when Adl phase
///        is read as Adjustment and is setting the Sensor Failure state for CtrlStp
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount               = 0u;
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount               = 0u;
/// \input  Pitch_ePitchSensorFailure                     = eHLS_SENSOR_FAILURE;
/// \input  Rte_Write_Pitch_PlausState_HitCount                 = 0u;
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount               = 0u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty             = SIG_INVALID;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 120u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.BhsPlausVehSpeed       = 1u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.BhsPlausMin         = 15u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.BhsPlausMax         = 30u;
/// \input  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[0]     = 600u;
/// \input  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[1]     = 600u;
/// \input  boBhsValCheck                           = FALSE;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens         = 1u
/// \input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens         = 2u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.unSensor_Error_Time     = -500u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.unSensor_Recover_Time     = 1u;
/// \input  Rte_Read_IoHwAb_GetSens_Balanced_HitCount             = 0u;
/// \input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0]         = 600u;
/// \input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1]         = 600u;
/// \input  Pitch_CheckVehSpeedData_RetVal                   = ePlauSig_Fail;
/// \input  Pitch_CheckSensValue_RetVal                     = ePlauSig_Fail;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.SensorOutRangeTime       = 1u;
/// \input  LPTMR0_GetTimeElapsed_RetVal                   = 0xFFFFu;
/// \input  boDispValCheck                           = FALSE;
/// \input  Rte_Read_IoHwAb_GetSens_Raw_HitCount               = 0u;
/// \input  Pitch_ulCheckBHS_us                         = 20u;
///
/// - Expectations: 
///
/// \output  Rte_Read_SysMon_VehicleSpeed_HitCount           =   1u,
/// \output  Rte_Write_Pitch_PlausState_HitCount         =   1u,
/// \output  Pitch_CheckSensValue_RetVal          =   ePlauSig_Fail,
/// \output  Rte_Write_Pitch_PlausState_Param1        =   eHLS_SENSOR_FAILURE
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_AdjustmentCheckPlausibility_TestCase_3(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  // Step 1) Set pre-conditions
  // Step 2) Assign Input value
  //-----------------------------------------------------------------------------
  Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;
  Pitch_ePitchSensorFailure = eHLS_SENSOR_FAILURE;
  Rte_Write_Pitch_PlausState_HitCount = 0u;
  Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = SIG_INVALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 120u;
  Pitch_pCodingArea->AvacStp.PitchData.BhsPlausVehSpeed = 1u;
  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[0] = 600u;
  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[1] = 600u;
  boBhsValCheck = FALSE;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 2u;
  Rte_Read_IoHwAb_GetSens_Balanced_HitCount = 0u;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0] = 600u;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1] = 600u;
  Pitch_CheckVehSpeedData_RetVal = ePlauSig_Fail;
  Pitch_CheckSensValue_RetVal = ePlauSig_Fail;
  Pitch_pCodingArea->AvacStp.PitchData.SensorOutRangeTime = 1u;
  LPTMR0_GetTimeElapsed_RetVal = 0xFFFFu;
  boDispValCheck[1] = TRUE;
  Rte_Read_IoHwAb_GetSens_Raw_HitCount = 0u;
  Pitch_ulCheckBHS_us = 20u;
  NvmBlockDeltaPwmPara.ucSensPlausError[0u] = ePlaus_FAILURE;

  //-----------------------------------------------------------------------------
  // Function call
  // Step 3) Call FUT
  //-----------------------------------------------------------------------------

  Pitch_AdjustmentCheckPlausibility();
  //-----------------------------------------------------------------------------
  // Outputs
  // Step 4) Check expected output values
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Pitch_CheckSensValue_RetVal, ePlauSig_Fail, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_Param1, eHLS_SENSOR_FAILURE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Pitch_Pitch_AdjustmentCheckPlausibility_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  This function is checking the sensor plausibility state when Adl phase
///        is read as Adjustment and is setting the Sensor Failure state for CtrlStp
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  Rte_Read_SysMon_VehicleSpeed_HitCount               = 0u;
/// \input  Pitch_ePitchSensorFailure                     = eHLS_SENSOR_FAILURE;
/// \input  Rte_Write_Pitch_PlausState_HitCount                 = 0u;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty             = SIG_VALID;
/// \input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 0u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.BhsPlausVehSpeed       = 1u;
/// \input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0]   = 0u;
/// \input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1]   = 0u;
/// \input  boDispValCheck                                     = FALSE;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 10u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 90u;
/// \input  LPTMR0_GetTimeElapsed_RetVal                       = 0xFFFFFFFF;
///
/// - Expectations: 
///
/// \output  Rte_Write_Pitch_PlausState_HitCount         =   1u,
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_AdjustmentCheckPlausibility_TestCase_4(void)
{
  //-----------------------------------------------------------------------------
  // Inputs
  // Step 1) Set pre-conditions
  // Step 2) Assign Input value
  //-----------------------------------------------------------------------------

  Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;
  Pitch_ePitchSensorFailure = eHLS_SENSOR_FAILURE;
  Rte_Write_Pitch_PlausState_HitCount = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 0u;
  Pitch_pCodingArea->AvacStp.PitchData.BhsPlausVehSpeed = 1u;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0] = 0u;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1] = 0u;
  boDispValCheck[1] = TRUE;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 10u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 90u;
  LPTMR0_GetTimeElapsed_RetVal = 0xFFFFFFFF;


  //Step 3) Call FUT
  Pitch_AdjustmentCheckPlausibility();

  //-----------------------------------------------------------------------------
  // Outputs
  // Step 4) Check expected output values
  //-----------------------------------------------------------------------------

  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_AdjustmentCheckPlausibility
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests the sensor plausibility state in the case of adjustment phase
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_AdjustmentCheckPlausibility(void)
{
  Mt_Pitch_Pitch_AdjustmentCheckPlausibility_TestCase_1();
  Mt_Pitch_Pitch_AdjustmentCheckPlausibility_TestCase_2();
  Mt_Pitch_Pitch_AdjustmentCheckPlausibility_TestCase_3();
  Mt_Pitch_Pitch_AdjustmentCheckPlausibility_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Pitch_Pitch_SigWorst_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   check the function Regard the following 3 qualities:
///         prio1: SIG_INVALID
///         prio2: SIG_SNA
///         prio3: SIG_VALID
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  Pitch_SigWorst_Param1 = (uint8)SIG_VALID;
/// \input  Pitch_SigWorst_Param2 = (uint8)SIG_VALID;
/// \input  Pitch_SigWorst_RetVal = (uint8)SIG_SNA;
///
/// - Expectations: 
///
/// \output  Pitch_SigWorst_RetVal = (uint8)SIG_VALID
///
//-----------------------------------------------------------------------------

void  Mt_Pitch_Pitch_SigWorst_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Pitch_SigWorst_Param1 = (uint8)SIG_VALID;
  Pitch_SigWorst_Param2 = (uint8)SIG_VALID;
  Pitch_SigWorst_RetVal = (uint8)SIG_SNA;

  //Step 3) Call FUT
  Pitch_SigWorst_RetVal = Pitch_SigWorst(Pitch_SigWorst_Param1, Pitch_SigWorst_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_SigWorst_RetVal, (uint8)SIG_VALID, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Pitch_Pitch_SigWorst_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   check the function Regard the following 3 qualities:
///         prio1: SIG_INVALID
///         prio2: SIG_SNA
///         prio3: SIG_VALID
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  Pitch_SigWorst_Param1 = (uint8)SIG_INVALID;
/// \input  Pitch_SigWorst_Param2 = (uint8)SIG_INVALID;
/// \input  Pitch_SigWorst_RetVal = (uint8)SIG_SNA;
///
/// - Expectations: 
///
/// \output  Pitch_SigWorst_RetVal = (uint8)SIG_INVALID;
///
//-----------------------------------------------------------------------------
void  Mt_Pitch_Pitch_SigWorst_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Pitch_SigWorst_Param1 = (uint8)SIG_INVALID;
  Pitch_SigWorst_Param2 = (uint8)SIG_INVALID;
  Pitch_SigWorst_RetVal = (uint8)SIG_SNA;

  //Step 3) Call FUT
  Pitch_SigWorst_RetVal = Pitch_SigWorst(Pitch_SigWorst_Param1, Pitch_SigWorst_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_SigWorst_RetVal, (uint8)SIG_INVALID, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Pitch_Pitch_SigWorst_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   check the function Regard the following 3 qualities:
///         prio1: SIG_INVALID
///         prio2: SIG_SNA
///         prio3: SIG_VALID
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  Pitch_SigWorst_Param1 = (uint8)SIG_SNA;
/// \input  Pitch_SigWorst_Param2 = (uint8)SIG_SNA;
/// \input  Pitch_SigWorst_RetVal = (uint8)SIG_VALID;
///
/// - Expectations: 
///
/// \output  Pitch_SigWorst_RetVal = (uint8)SIG_SNA;
///
//-----------------------------------------------------------------------------
void  Mt_Pitch_Pitch_SigWorst_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Pitch_SigWorst_Param1 = (uint8)SIG_SNA;
  Pitch_SigWorst_Param2 = (uint8)SIG_SNA;
  Pitch_SigWorst_RetVal = (uint8)SIG_VALID;

  //Step 3) Call FUT
  Pitch_SigWorst_RetVal = Pitch_SigWorst(Pitch_SigWorst_Param1, Pitch_SigWorst_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_SigWorst_RetVal, (uint8)SIG_SNA, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_SigWorst
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Checks if the function returns the worst between 2 signals in all possible cases
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_SigWorst(void)
{
  Mt_Pitch_Pitch_SigWorst_TestCase_1();
  Mt_Pitch_Pitch_SigWorst_TestCase_2();
  Mt_Pitch_Pitch_SigWorst_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Pitch_Pitch_GetLocal_DisplacementSens
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:   function to read data from a global structure used inside this file
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  sPitch_DispSens.nDisp[0]   = 10;
/// \input  sPitch_DispSens.eSigQty[0] = 10;
/// \input  sPitch_DispSens.nDisp[1]   = 10;
/// \input  sPitch_DispSens.eSigQty[1] = 10;
///
/// - Expectations: 
///
/// \output  Pitch_GetLocal_DisplacementSens_Param1.nDisp[0]   = 10;
/// \output  Pitch_GetLocal_DisplacementSens_Param1.eSigQty[0] = 10;
/// \output  Pitch_GetLocal_DisplacementSens_Param1.nDisp[1]   = 10;
/// \output  Pitch_GetLocal_DisplacementSens_Param1.eSigQty[1] = 10;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_GetLocal_DisplacementSens(void)
{
   //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  sPitch_DispSens.nDisp[0]   = 10;
  sPitch_DispSens.eSigQty[0] = 10;
  sPitch_DispSens.nDisp[1]   = 10;
  sPitch_DispSens.eSigQty[1] = 10;

  //Step 3) Call FUT
  Pitch_GetLocal_DisplacementSens(&Pitch_GetLocal_DisplacementSens_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_GetLocal_DisplacementSens_Param1.nDisp[0],   10, == );
  AL_UNITTEST_CHECK(Pitch_GetLocal_DisplacementSens_Param1.eSigQty[0], 10, == );
  AL_UNITTEST_CHECK(Pitch_GetLocal_DisplacementSens_Param1.nDisp[1],   10, == );
  AL_UNITTEST_CHECK(Pitch_GetLocal_DisplacementSens_Param1.eSigQty[1], 10, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :   Mt_Pitch_Pitch_ErrCntInc_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:    This function is setting to FAILD the coresponding DTC for an event afther the dedicated time of 1s
///        the time is mesured based on counters this function is call at every 20ms
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  Pitch_ErrCntInc_Param1                     = &a;
/// \input  Pitch_ErrCntInc_Param2                     = RR_BHS_SUPPLY_LOW;
/// \input  Dem_SetEventStatus_HitCount                   = 0u;
///
/// - Expectations: 
///
/// \output  Dem_SetEventStatus_HitCount    = 0u
/// \output  Pitch_ErrCntInc_RetVal        = (uint8)SIG_SNA
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_ErrCntInc_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Pitch_ErrCntInc_Param1                     = 1u;
  Pitch_ErrCntInc_Param2                     = RR_BHS_SUPPLY_LOW;
  Dem_SetEventStatus_HitCount                   = 0u;

  //Step 3) Call FUT
  Pitch_ErrCntInc_RetVal = Pitch_ErrCntInc(&Pitch_ErrCntInc_Param1, Pitch_ErrCntInc_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,      0u, == );
  AL_UNITTEST_CHECK(Pitch_ErrCntInc_RetVal, (uint8)SIG_SNA, == );


}

//-----------------------------------------------------------------------------
/// \Test Case :   Mt_Pitch_Pitch_ErrCntInc_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:    This function is setting to FAILD the coresponding DTC for an event afther the dedicated time of 1s
///        the time is mesured based on counters this function is call at every 20ms
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  Pitch_ErrCntInc_Param1                   = &a;
/// \input  Pitch_ErrCntInc_Param2                   = RR_BHS_SUPPLY_LOW;
///
/// - Expectations: 
///
/// \output  Pitch_ErrCntInc_RetVal = SIG_SNA
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_ErrCntInc_TestCase_2(void)
{ 
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Pitch_ErrCntInc_Param1                   = 3u;
  Pitch_ErrCntInc_Param2                   = RR_BHS_SUPPLY_LOW;

  //Step 3) Call FUT
  Pitch_ErrCntInc_RetVal = Pitch_ErrCntInc(&Pitch_ErrCntInc_Param1, Pitch_ErrCntInc_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_ErrCntInc_RetVal, SIG_SNA, == );


}


//-----------------------------------------------------------------------------
/// \Test Case :   Mt_Pitch_Pitch_ErrCntInc_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:    This function is setting to FAILD the coresponding DTC for an event afther the dedicated time of 1s
///        the time is mesured based on counters this function is call at every 20ms
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  Pitch_ErrCntInc_Param1                   = &a;
/// \input  Pitch_ErrCntInc_Param2                   = RR_BHS_SUPPLY_LOW;
///
/// - Expectations: 
///
/// \output  Pitch_ErrCntInc_RetVal = SIG_INVALID
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_ErrCntInc_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Pitch_ErrCntInc_Param1 = 254u;
  Pitch_ErrCntInc_Param2 = RR_BHS_SUPPLY_LOW;

  //Step 3) Call FUT
  Pitch_ErrCntInc_RetVal = Pitch_ErrCntInc(&Pitch_ErrCntInc_Param1, Pitch_ErrCntInc_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_ErrCntInc_RetVal, SIG_INVALID, == );

}


//-----------------------------------------------------------------------------
/// \Test Case :   Mt_Pitch_Pitch_ErrCntInc_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:    This function is setting to FAILD the coresponding DTC for an event afther the dedicated time of 1s
///        the time is mesured based on counters this function is call at every 20ms
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  Pitch_ErrCntInc_Param1                   = &a;
/// \input  Pitch_ErrCntInc_Param2                   = RR_BHS_SUPPLY_LOW;
///
/// - Expectations: 
///
/// \output  Pitch_ErrCntInc_RetVal = SIG_SNA
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_ErrCntInc_TestCase_4(void)
{ 
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Pitch_ErrCntInc_Param1                   = 99u;
  Pitch_ErrCntInc_Param2                   = RR_BHS_SUPPLY_LOW;

  //Step 3) Call FUT
  Pitch_ErrCntInc_RetVal = Pitch_ErrCntInc(&Pitch_ErrCntInc_Param1, Pitch_ErrCntInc_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_ErrCntInc_RetVal, SIG_SNA, == );


}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_ErrCntInc
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Checks if the function sets the corresponding DTC to FAILED after the triggering event
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_ErrCntInc(void)
{
  Mt_Pitch_Pitch_ErrCntInc_TestCase_1();
  Mt_Pitch_Pitch_ErrCntInc_TestCase_2();
  Mt_Pitch_Pitch_ErrCntInc_TestCase_3();
  Mt_Pitch_Pitch_ErrCntInc_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case :   Mt_Pitch_Pitch_ErrCntDec_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:    This function is setting to PASED the coresponding DTC for an event afther the dedicated time of 1s
///        the time is mesured based on counters this function is call at every 20ms
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  Pitch_ErrCntDec_Param1                   = &a;
/// \input  Pitch_ErrCntDec_Param2                   = FR_BHS_SUPPLY_LOW;
///
/// - Expectations: 
///
/// \output  Pitch_ErrCntDec_RetVal = (uint8)SIG_VALID
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_ErrCntDec_TestCase_1(void)
{ 
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Pitch_ErrCntDec_Param1                   = 0u;
  Pitch_ErrCntDec_Param2                   = FR_BHS_SUPPLY_LOW;

  //Step 3) Call FUT
  Pitch_ErrCntDec_RetVal = Pitch_ErrCntDec(&Pitch_ErrCntDec_Param1, Pitch_ErrCntDec_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_ErrCntDec_RetVal, (uint8)SIG_VALID, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :   Mt_Pitch_Pitch_ErrCntDec_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:    This function is setting to PASED the coresponding DTC for an event afther the dedicated time of 1s
///        the time is mesured based on counters this function is call at every 20ms
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  Pitch_ErrCntDec_Param1                   = &a;
/// \input  Pitch_ErrCntDec_Param2                   = FR_BHS_SUPPLY_LOW;
///
/// - Expectations: 
///
/// \output  Dem_SetEventStatus_HitCount   = 1u;
/// \output  Pitch_ErrCntDec_RetVal        = (uint8)SIG_VALID;
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_ErrCntDec_TestCase_2(void)
{ 
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Pitch_ErrCntDec_Param1                   = 1u;
  Pitch_ErrCntDec_Param2                   = FR_BHS_SUPPLY_LOW;

  //Step 3) Call FUT
  Pitch_ErrCntDec_RetVal = Pitch_ErrCntDec(&Pitch_ErrCntDec_Param1, Pitch_ErrCntDec_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,       2u, == );
  AL_UNITTEST_CHECK(Pitch_ErrCntDec_RetVal, (uint8)SIG_SNA, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :   Mt_Pitch_Pitch_ErrCntDec_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:    This function is setting to PASED the coresponding DTC for an event afther the dedicated time of 1s
///        the time is mesured based on counters this function is call at every 20ms
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  Pitch_ErrCntDec_Param1                   = &a;
/// \input  Pitch_ErrCntDec_Param2                   = FR_BHS_SUPPLY_HIGH;
///
/// - Expectations: 
///
/// \output  Pitch_ErrCntDec_RetVal        = (uint8)SIG_SNA;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_ErrCntDec_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Pitch_ErrCntDec_Param1                   = 4u;
  Pitch_ErrCntDec_Param2                   = FR_BHS_SUPPLY_HIGH;
   
  //Step 3) Call FUT
  Pitch_ErrCntDec_RetVal = Pitch_ErrCntDec(&Pitch_ErrCntDec_Param1, Pitch_ErrCntDec_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_ErrCntDec_RetVal, (uint8)SIG_SNA, == );


}

//-----------------------------------------------------------------------------
/// \Test Case :   Mt_Pitch_Pitch_ErrCntDec_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:    This function is setting to PASED the coresponding DTC for an event afther the dedicated time of 1s
///        the time is mesured based on counters this function is call at every 20ms
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  Pitch_ErrCntDec_Param1                   = &a;
/// \input  Pitch_ErrCntDec_Param2                   = FR_BHS_SUPPLY_HIGH;
///
/// - Expectations: 
///
/// \output  Pitch_ErrCntDec_RetVal        = (uint8)SIG_INVALID;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_ErrCntDec_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Pitch_ErrCntDec_Param1                   = 254u;
  Pitch_ErrCntDec_Param2                   = FR_BHS_SUPPLY_HIGH;
   
  //Step 3) Call FUT
  Pitch_ErrCntDec_RetVal = Pitch_ErrCntDec(&Pitch_ErrCntDec_Param1, Pitch_ErrCntDec_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_ErrCntDec_RetVal, (uint8)SIG_INVALID, == );


}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_ErrCntDec
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Checks if the function sets the corresponding DTC to PASSED after the triggering event
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_ErrCntDec(void)
{
  Mt_Pitch_Pitch_ErrCntDec_TestCase_1();
  Mt_Pitch_Pitch_ErrCntDec_TestCase_2();
  Mt_Pitch_Pitch_ErrCntDec_TestCase_3();
  Mt_Pitch_Pitch_ErrCntDec_TestCase_4();
}


//-----------------------------------------------------------------------------
/// \Test Case :    Mt_Pitch_Pitch_CheckSensSupply_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:    This function is setting to PASED the coresponding DTC for an event afther the dedicated time of 1s
///        the time is mesured based on counters this function is call at every 20ms
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Min       = 30u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Max       = 40u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.unSensor_Error_Time = 400u;
/// \input  Rte_Read_IoHwAb_VCCX1Voltage_HitCount           = 0u;
/// \input  Pitch_CheckSensSupply_RetVal               = SIG_SNA;
///
/// \input  ucPitch_ErrCntVccxLoRR        = 30u;
/// \input  ucPitch_ErrCntVccxLoFR        = 30u;
/// \input  ucPitch_ErrCntVccxHiRR        = 30u;
/// \input  ucPitch_ErrCntVccxHiFR        = 30u;
/// \input  Rte_Read_IoHwAb_VCCX1Voltage_Param1 = 20u;
///
/// - Expectations: 
///
/// \output Rte_Read_IoHwAb_VCCX1Voltage_HitCount = 1u;
/// \output Pitch_CheckSensSupply_RetVal      = (uint8)SIG_SNA;
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensSupply_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Min       = 30u;
  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Max       = 40u;
  Rte_Read_IoHwAb_VCCX1Voltage_HitCount           = 0u;
  Pitch_CheckSensSupply_RetVal               = SIG_SNA;

  //Step 2) Assign Input values
  ucPitch_ErrCntVccxLoRR        = 30u;
  ucPitch_ErrCntVccxLoFR        = 30u;
  ucPitch_ErrCntVccxHiRR        = 30u;
  ucPitch_ErrCntVccxHiFR        = 30u;
  Rte_Read_IoHwAb_VCCX1Voltage_Param1 = 20u;

  //Step 3) Call FUT
  Pitch_CheckSensSupply_RetVal = Pitch_CheckSensSupply();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_VCCX1Voltage_HitCount,    1u, == );
  AL_UNITTEST_CHECK(Pitch_CheckSensSupply_RetVal, (uint8)SIG_SNA, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :    Mt_Pitch_Pitch_CheckSensSupply_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:    This function is checking the sensors supply voltage Vccx to be in
///        to be in range of datasheet parameters  4.5V - 5V - 5.5V
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Min       = 30u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Max       = 40u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.unSensor_Error_Time = 400u;
/// \input  Pitch_CheckSensSupply_RetVal               = SIG_INVALID;
/// \input  Rte_Read_IoHwAb_VCCX1Voltage_HitCount           = 0u;
/// \input  //Step 2) Assign Input values
/// \input  Rte_Read_IoHwAb_VCCX1Voltage_Param1 = 50u;
/// \input  ucPitch_ErrCntVccxLoRR        = 0u;
/// \input  ucPitch_ErrCntVccxLoFR        = 0u;
/// \input  ucPitch_ErrCntVccxHiRR        = 19u;
/// \input  ucPitch_ErrCntVccxHiFR        = 19u;
///
/// - Expectations: 
///
/// \output Rte_Read_IoHwAb_VCCX1Voltage_HitCount = 1u;
/// \output Pitch_CheckSensSupply_RetVal          = (uint8)SIG_SNA;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensSupply_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Min       = 30u;
  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Max       = 40u;
  Pitch_CheckSensSupply_RetVal               = SIG_INVALID;
  Rte_Read_IoHwAb_VCCX1Voltage_HitCount           = 0u;

  //Step 2) Assign Input values
  Rte_Read_IoHwAb_VCCX1Voltage_Param1 = 50u;
  ucPitch_ErrCntVccxLoRR        = 0u;
  ucPitch_ErrCntVccxLoFR        = 0u;
  ucPitch_ErrCntVccxHiRR        = 19u;
  ucPitch_ErrCntVccxHiFR        = 19u;

  //Step 3) Call FUT
  Pitch_CheckSensSupply_RetVal = Pitch_CheckSensSupply();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_VCCX1Voltage_HitCount,    1u, == );
  AL_UNITTEST_CHECK(Pitch_CheckSensSupply_RetVal, (uint8)SIG_SNA, == );
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_CheckSensSupply_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check that sensor supply signal quality remains valid in
///                     case the supply is in the accepted range
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// \input  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Min       = 30u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Max       = 40u;
/// \input  Pitch_pCodingArea->AvacStp.PitchData.unSensor_Error_Time = 400u;
/// \input  Rte_Read_IoHwAb_VCCX1Voltage_HitCount           = 0u;
/// \input  Pitch_CheckSensSupply_RetVal               = SIG_INVALID;
/// \input  ucPitch_ErrCntVccxLoRR                   = 0u;
/// \input  ucPitch_ErrCntVccxLoFR                   = 0u;
/// \input  ucPitch_ErrCntVccxHiRR                   = 0u;
/// \input  ucPitch_ErrCntVccxHiFR                   = 0u;
/// \input  Rte_Read_IoHwAb_VCCX1Voltage_Param1             = 35u;
///
///   - Expectations:
///
/// \output Pitch_CheckSensSupply_RetVal          = SIG_VALID
/// \output Rte_Read_IoHwAb_VCCX1Voltage_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensSupply_TestCase_3(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Min       = 30u;
  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Max       = 40u;
  Rte_Read_IoHwAb_VCCX1Voltage_HitCount           = 0u;
  Pitch_CheckSensSupply_RetVal               = SIG_INVALID;
  ucPitch_ErrCntVccxLoRR                   = 0u;
  ucPitch_ErrCntVccxLoFR                   = 0u;
  ucPitch_ErrCntVccxHiRR                   = 0u;
  ucPitch_ErrCntVccxHiFR                   = 0u;
  Rte_Read_IoHwAb_VCCX1Voltage_Param1             = 35u;

  //Step 3) Call FUT
  Pitch_CheckSensSupply_RetVal = Pitch_CheckSensSupply();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_VCCX1Voltage_HitCount,    1u, == );
  AL_UNITTEST_CHECK(Pitch_CheckSensSupply_RetVal, (uint8)SIG_VALID, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_CheckSensSupply
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if the function checks if the supply voltage of the sensor is in the correct range
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensSupply(void)
{
  Mt_Pitch_Pitch_CheckSensSupply_TestCase_1();
  Mt_Pitch_Pitch_CheckSensSupply_TestCase_2();
  Mt_Pitch_Pitch_CheckSensSupply_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_CheckSensorState_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: This function is checking the sensor state and set the coresponding DTC
///        in case of invalid state of the signal, also the it will set the quality
///        variable for coresponding state SIG_VALID; SIG_INVALID or SIG_SNA
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens     = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens     = 2u;
/// input  Dem_SetEventStatus_HitCount                 = 0u;
/// input  Pitch_CheckSensorState_Param1               = 0u;
/// input  Pitch_CheckSensorState_RetVal               = SIG_SNA;
///
///   - Expectations:
///
/// \output Pitch_CheckSensorState_RetVal = SIG_VALID
/// \output Dem_SetEventStatus_HitCount   = 0u
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensorState_TestCase_1(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 2u;
  Dem_SetEventStatus_HitCount = 0u;
  Pitch_CheckSensorState_Param1 = 0u;
  Pitch_CheckSensorState_RetVal = SIG_SNA;


  //Step 3) Call FUT
  Pitch_CheckSensorState_RetVal = Pitch_CheckSensorState(Pitch_CheckSensorState_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_CheckSensorState_RetVal, SIG_VALID, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_CheckSensorState_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  This function is checking the sensor state and set the coresponding DTC
///        in case of invalid state of the signal, also the it will set the quality
///        variable for coresponding state SIG_VALID; SIG_INVALID or SIG_SNA
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// input Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens     = 1u;
/// input Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens     = 2u;
/// input Dem_SetEventStatus_HitCount                 = 0u;
/// input Pitch_CheckSensorState_Param1               = 1u;
/// input Pitch_CheckSensorState_RetVal               = SIG_SNA;
/// input NvmBlockDeltaPwmPara.eNVM_VAC_Input        = eInput_HLS;
/// input NvmBlockDeltaPwmPara.ucSensGndError[1]     = 1u;
///
///   - Expectations:
///
/// \output 
/// \output  Pitch_CheckSensorState_RetVal, = SIG_INVALID
/// \output  Dem_SetEventStatus_HitCount,   =  1u
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensorState_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 2u;
  Dem_SetEventStatus_HitCount = 0u;
  Pitch_CheckSensorState_Param1 = 1u;
  Pitch_CheckSensorState_RetVal = SIG_SNA;
  NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_HLS;
  NvmBlockDeltaPwmPara.ucSensGndError[1] = 1u;

  //Step 3) Call FUT
  Pitch_CheckSensorState_RetVal = Pitch_CheckSensorState(Pitch_CheckSensorState_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_CheckSensorState_RetVal, SIG_VALID, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_CheckSensorState_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  This function is checking the sensor state and set the coresponding DTC
///        in case of invalid state of the signal, also the it will set the quality
///        variable for coresponding state SIG_VALID; SIG_INVALID or SIG_SNA
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens     = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens     = 2u;
/// input  Pitch_CheckSensorState_Param1               = 1u;
/// input  Pitch_CheckSensorState_RetVal               = SIG_VALID;
/// input  Dem_SetEventStatus_HitCount                 = 0u;
///   - Expectations:
///
/// \output 
/// \output  Pitch_CheckSensorState_RetVal = SIG_INVALID;
/// \output  Dem_SetEventStatus_HitCount   =  1u;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensorState_TestCase_3(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 2u;
  Pitch_CheckSensorState_Param1 = 1u;
  Pitch_CheckSensorState_RetVal = SIG_VALID;
  Dem_SetEventStatus_HitCount = 0u;

  //Step 3) Call FUT
  Pitch_CheckSensorState_RetVal = Pitch_CheckSensorState(Pitch_CheckSensorState_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_CheckSensorState_RetVal, SIG_VALID, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_CheckSensorState_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  This function is checking the sensor state and set the coresponding DTC
///        in case of invalid state of the signal, also the it will set the quality
///        variable for coresponding state SIG_VALID; SIG_INVALID or SIG_SNA
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
/// input Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 1u;
/// input Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 2u;
/// input Pitch_CheckSensorState_Param1               = 2u;
/// input Pitch_CheckSensorState_RetVal               = SIG_VALID;
///   - Expectations:
///
/// \output  Pitch_CheckSensorState_RetVal = SIG_SNA ;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensorState_TestCase_4(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 2u;
  Pitch_CheckSensorState_Param1 = 2u;
  Pitch_CheckSensorState_RetVal = SIG_VALID;

  //Step 3) Call FUT
  Pitch_CheckSensorState_RetVal = Pitch_CheckSensorState(Pitch_CheckSensorState_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_CheckSensorState_RetVal, SIG_VALID, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_CheckSensorState_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  This function is checking the sensor state and set the coresponding DTC
///        in case of invalid state of the signal, also the it will set the quality
///        variable for coresponding state SIG_VALID; SIG_INVALID or SIG_SNA
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
/// input Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 1u;
/// input Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 2u;
/// input Pitch_CheckSensorState_Param1 = 1u;
/// input Pitch_CheckSensorState_RetVal = SIG_VALID;
/// input NvmBlockDeltaPwmPara.ucSensGndError[1u] = 1u;
///
///   - Expectations:
///
/// \output  Pitch_CheckSensorState_RetVal = SIG_INVALID ;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensorState_TestCase_5(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 2u;
  Pitch_CheckSensorState_Param1 = 1u;
  Pitch_CheckSensorState_RetVal = SIG_VALID;
  NvmBlockDeltaPwmPara.ucSensGndError[1u] = 1u;

  //Step 3) Call FUT
  Pitch_CheckSensorState_RetVal = Pitch_CheckSensorState(Pitch_CheckSensorState_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_CheckSensorState_RetVal, SIG_VALID, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_CheckSensorState_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  This function is checking the sensor state and set the coresponding DTC
///        in case of invalid state of the signal, also the it will set the quality
///        variable for coresponding state SIG_VALID; SIG_INVALID or SIG_SNA
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
/// input Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 1u;
/// input Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 2u;
/// input Pitch_CheckSensorState_Param1 = 1u;
/// input Pitch_CheckSensorState_RetVal = SIG_VALID;
/// input NvmBlockDeltaPwmPara.ucSensGndError[1u] = 0u;
/// input NvmBlockDeltaPwmPara.ucSensVbatError[1u] = 1u;
///
///   - Expectations:
///
/// \output  Pitch_CheckSensorState_RetVal = SIG_INVALID
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensorState_TestCase_6(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 2u;
  Pitch_CheckSensorState_Param1 = 1u;
  Pitch_CheckSensorState_RetVal = SIG_VALID;
  NvmBlockDeltaPwmPara.ucSensGndError[1u] = 0u;
  NvmBlockDeltaPwmPara.ucSensVbatError[1u] = 1u;

  //Step 3) Call FUT
  Pitch_CheckSensorState_RetVal = Pitch_CheckSensorState(Pitch_CheckSensorState_Param1);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_CheckSensorState_RetVal, SIG_VALID, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_CheckSensorState
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if the function checks the sensor state and sets the corresponding DTC in case of a failure
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensorState(void)
{
  Mt_Pitch_Pitch_CheckSensorState_TestCase_1();
  Mt_Pitch_Pitch_CheckSensorState_TestCase_2();
  Mt_Pitch_Pitch_CheckSensorState_TestCase_3();
  Mt_Pitch_Pitch_CheckSensorState_TestCase_4();
  Mt_Pitch_Pitch_CheckSensorState_TestCase_5();
  Mt_Pitch_Pitch_CheckSensorState_TestCase_6();
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: this  function is checking for reset to warning levels of error count values of lower and higher locations
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
/// input  Rte_Read_CodM_Pitch_Para_Param1.eCodingState         = eParaFct0_CodingDataValid;
/// input  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks   = &Coding_Dummy;
/// input  Pitch_ParaFct0_RetVal                     = TRUE;
/// input  Rte_Read_CodM_Pitch_Para_HitCount               = 0u;
/// input  boPitch_CodingValidity                     = TRUE;
///
///   - Expectations:
///
/// \output 
/// \output  sPitch_ErrCnt.aucSigLo[1u] = 1;
/// \output  sPitch_ErrCnt.aucSigHi[1u] = 1;
/// \output  boPitch_CodingValidity     = TRUE;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_Init(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_CodM_Pitch_Para_Param1.eCodingState         = eParaFct0_CodingDataValid;
  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks   = &Coding_Dummy;
  Pitch_ParaFct0_RetVal                     = TRUE;
  Rte_Read_CodM_Pitch_Para_HitCount               = 0u;
  boPitch_CodingValidity                     = TRUE;

  //Step 3) Call FUT
  Pitch_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(sPitch_ErrCnt.aucSigLo[1u], 1, == );
  AL_UNITTEST_CHECK(sPitch_ErrCnt.aucSigHi[1u], 1, == );
  AL_UNITTEST_CHECK(boPitch_CodingValidity,  TRUE, == );


}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_ErrPassed
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Calculate the minimum and maximum displacement values based on given inputs 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
/// input  Dem_SetEventStatus_Param1   = (uint16)RR_BHS_SUPPLY_HIGH;
/// input  Dem_SetEventStatus_Param2   =  DEM_EVENT_STATUS_PASSED;
/// input  Dem_SetEventStatus_HitCount = 0u;
///   - Expectations:
///
/// \output 
/// \output  Dem_SetEventStatus_HitCount = 10u ;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_ErrPassed(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  
  Dem_SetEventStatus_Param1   =  (uint16)RR_BHS_SUPPLY_HIGH;
  Dem_SetEventStatus_Param2   =  DEM_EVENT_STATUS_PASSED;
  Dem_SetEventStatus_HitCount =  0u;
  //Step 3) Call FUT

  Pitch_ErrPassed();
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 10u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_DispCalc_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Calculate the minimum and maximum displacement values based on given inputs 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
/// input Pitch_DispCal_Param1    = 1u;
/// input Pitch_DispCal_Param2    = 14;
/// input Pitch_DispCal_Param3    = 65536;
/// input Pitch_DispCal_returnVal = 1;
///   - Expectations:
///
/// \output 
/// \output  Pitch_DispCal_returnVal = 0 ;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_DispCalc_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Pitch_DispCal_Param1    = 1u;
  Pitch_DispCal_Param2    = 14;
  Pitch_DispCal_Param3    = 65536;
  Pitch_DispCal_returnVal = 1;

  //Step 3) Call FUT
  Pitch_DispCal_returnVal = Pitch_DispCalc(Pitch_DispCal_Param1, &Pitch_DispCal_Param2, Pitch_DispCal_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_DispCal_returnVal, 0, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_DispCalc_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Calculate the minimum and maximum displacement values based on given inputs 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
/// input Pitch_DispCal_Param1    = -32758;
/// input Pitch_DispCal_Param2    = 14;
/// input Pitch_DispCal_Param3    = 65536;
/// input Pitch_DispCal_returnVal = 1;
///   - Expectations:
///
/// \output 
/// \output  Pitch_DispCal_returnVal = -32758 ;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_DispCalc_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Pitch_DispCal_Param1    = -32768;
  Pitch_DispCal_Param2    = 14;
  Pitch_DispCal_Param3    = 65536;
  Pitch_DispCal_returnVal = 1;

  //Step 3) Call FUT
  Pitch_DispCal_returnVal = Pitch_DispCalc(Pitch_DispCal_Param1, &Pitch_DispCal_Param2, Pitch_DispCal_Param3);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_DispCal_returnVal, -32758, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_DispCalc_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Calculate the minimum and maximum displacement values based on given inputs 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
/// input Pitch_DispCal_Param1 = 32767;
/// input Pitch_DispCal_Param2 = 14;
/// input Pitch_DispCal_Param3 = 2147483647;
/// input Pitch_DispCal_returnVal = 1;
///   - Expectations:
///
/// \output 
/// \output  Pitch_DispCal_returnVal = -32759 ;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_DispCalc_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Pitch_DispCal_Param1 = 32767;
  Pitch_DispCal_Param2 = 14;
  Pitch_DispCal_Param3 = 2147483647;
  Pitch_DispCal_returnVal = 1;

  //Step 3) Call FUT

  Pitch_DispCal_returnVal = Pitch_DispCalc(Pitch_DispCal_Param1, &Pitch_DispCal_Param2, Pitch_DispCal_Param3);
 
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_DispCal_returnVal, -32759, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_DispCalc
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if the function calculates all the minimum and maximum displacement values
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_DispCalc(void)
{
  Mt_Pitch_Pitch_DispCalc_TestCase_1();
  Mt_Pitch_Pitch_DispCalc_TestCase_2();
  Mt_Pitch_Pitch_DispCalc_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_DispMeasurement_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  check this function to check the wuality of the signal based on Displancemet
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  Rte_Read_IoHwAb_GetSens_Raw_HitCount           = 0u;
/// input  Rte_Read_IoHwAb_GetSens_Balanced_HitCount         = 0u;
/// input  Pitch_CheckSensSupply_RetVal               = (uint8)SIG_VALID;
/// input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0]     = 800u;
/// input  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[0] = 700u;
/// input  Rte_Read_IoHwAb_VCCX1Voltage_Param1             = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens     = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens     = 2u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.snSensorSlopeFront  = 4u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.snSensorSlopeRear   = 3u;
///
/// input  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Min       = 30u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Max       = 40u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unSensor_Error_Time = 400u;
/// input  Rte_Read_IoHwAb_VCCX1Voltage_HitCount           = 0u;
/// input  Pitch_CheckSensSupply_RetVal               = SIG_INVALID;
/// input  ucPitch_ErrCntVccxLoRR                   = 0u;
/// input  ucPitch_ErrCntVccxLoFR                   = 0u;
/// input  ucPitch_ErrCntVccxHiRR                   = 0u;
/// input  ucPitch_ErrCntVccxHiFR                   = 0u;
/// input  Rte_Read_IoHwAb_VCCX1Voltage_Param1             = 35u;
///
/// input  Pitch_DispCal_Param1                   = 1u;
/// input  Pitch_DispCal_Param2                   = 14u;
/// input  Pitch_DispCal_Param3                   = 650;
/// input  Pitch_DispCal_returnVal                   = 1u;
/// 
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens     = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens     = 2u;
/// input  Dem_SetEventStatus_HitCount                 = 0u;
/// input  Pitch_CheckSensorState_Param1               = 2u;
/// input  Pitch_CheckSensorState_RetVal               = SIG_SNA;
///
/// input  Pitch_SigWorst_Param1                   = (uint8)SIG_SNA;
/// input  Pitch_SigWorst_Param2                   = (uint8)SIG_SNA;
/// input  Pitch_SigWorst_RetVal                   = (uint8)SIG_SNA;
///
///   - Expectations:
/// 
/// \output  sPitch_DispSens.eSigQty[0]              = (uint8)SIG_VALID
/// \output  Rte_Read_IoHwAb_VCCX1Voltage_HitCoun        = 1u
/// \output  Pitch_SigWorst_RetVal                = (uint8)SIG_SNA
/// \output  Pitch_CheckSensorState_RetVal            = SIG_SNA
/// \output  Dem_SetEventStatus_HitCount            = 3u
/// \output  Pitch_GetLocal_DisplacementSens_Param1.nDisp[0]  = 10
/// \output  Pitch_GetLocal_DisplacementSens_Param1.eSigQty[0]= 10
/// \output  Pitch_GetLocal_DisplacementSens_Param1.nDisp[1]  = 10
/// \output  Pitch_GetLocal_DisplacementSens_Param1.eSigQty[1]= 10
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_DispMeasurement_TestCase_1(void)
{ 
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAb_GetSens_Raw_HitCount           = 0u;
  Rte_Read_IoHwAb_GetSens_Balanced_HitCount         = 0u;
  Pitch_CheckSensSupply_RetVal               = (uint8)SIG_VALID;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0]     = 800u;
  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[0] = 700u;
  Rte_Read_IoHwAb_VCCX1Voltage_Param1             = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens     = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens     = 2u;
  Pitch_pCodingArea->AvacStp.PitchData.snSensorSlopeFront  = 4u;
  Pitch_pCodingArea->AvacStp.PitchData.snSensorSlopeRear   = 3u;

  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Min       = 30u;
  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Max       = 40u;
  Rte_Read_IoHwAb_VCCX1Voltage_HitCount           = 0u;
  Pitch_CheckSensSupply_RetVal               = SIG_INVALID;
  ucPitch_ErrCntVccxLoRR                   = 0u;
  ucPitch_ErrCntVccxLoFR                   = 0u;
  ucPitch_ErrCntVccxHiRR                   = 0u;
  ucPitch_ErrCntVccxHiFR                   = 0u;
  Rte_Read_IoHwAb_VCCX1Voltage_Param1             = 35u;

  Pitch_DispCal_Param1                   = 1u;
  Pitch_DispCal_Param2                   = 14u;
  Pitch_DispCal_Param3                   = 650;
  Pitch_DispCal_returnVal                   = 1u;

  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens     = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens     = 2u;
  Dem_SetEventStatus_HitCount                 = 0u;
  Pitch_CheckSensorState_Param1               = 2u;
  Pitch_CheckSensorState_RetVal               = SIG_SNA;

  Pitch_SigWorst_Param1                   = (uint8)SIG_SNA;
  Pitch_SigWorst_Param2                   = (uint8)SIG_SNA;
  Pitch_SigWorst_RetVal                   = (uint8)SIG_SNA;
  
  //Step 3) Call FUT         
  Pitch_DispMeasurement();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(sPitch_DispSens.eSigQty[0],       (uint8)SIG_VALID, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_VCCX1Voltage_HitCount,       1u, == );
  AL_UNITTEST_CHECK(Pitch_SigWorst_RetVal,         (uint8)SIG_SNA, == );
  AL_UNITTEST_CHECK(Pitch_CheckSensorState_RetVal,            SIG_SNA, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,             3u, == );
  AL_UNITTEST_CHECK(Pitch_GetLocal_DisplacementSens_Param1.nDisp[0],   10, == );
  AL_UNITTEST_CHECK(Pitch_GetLocal_DisplacementSens_Param1.eSigQty[0], 10, == );
  AL_UNITTEST_CHECK(Pitch_GetLocal_DisplacementSens_Param1.nDisp[1],   10, == );
  AL_UNITTEST_CHECK(Pitch_GetLocal_DisplacementSens_Param1.eSigQty[1], 10, == );
       
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_DispMeasurement_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Calculate the minimum and maximum displacement values based on given inputs 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
/// input  Rte_Read_IoHwAb_GetSens_Raw_HitCount               = 0u;
/// input  Rte_Read_IoHwAb_GetSens_Balanced_HitCount         = 0u;
/// input  Pitch_CheckSensSupply_RetVal                 = (uint8)SIG_VALID;
/// input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0]       = 800u;
/// input  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[0]  = 700u;
/// input  Rte_Read_IoHwAb_VCCX1Voltage_Param1             = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens     = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens     = 2u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.snSensorSlopeFront   = 4u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.snSensorSlopeRear   = 3u;
///  
/// input  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Min       = 30u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Max       = 40u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unSensor_Error_Time  = 400u;
/// input  Rte_Read_IoHwAb_VCCX1Voltage_HitCount           = 0u;
/// input  Pitch_CheckSensSupply_RetVal                   = SIG_INVALID;
/// input  ucPitch_ErrCntVccxLoRR                   = 0u;
/// input  ucPitch_ErrCntVccxLoFR                   = 0u;
/// input  ucPitch_ErrCntVccxHiRR                   = 0u;
/// input  ucPitch_ErrCntVccxHiFR                   = 0u;
/// input  Rte_Read_IoHwAb_VCCX1Voltage_Param1             = 35u;
///
/// input  Pitch_DispCal_Param1                       = 1u;
/// input  Pitch_DispCal_Param2                       = 14u;
/// input  Pitch_DispCal_Param3                       = 65536;
/// input  Pitch_DispCal_returnVal                   = 1;
///    
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens     = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens     = 2u;
/// input  Dem_SetEventStatus_HitCount                 = 0u;
/// input  Pitch_CheckSensorState_Param1               = 1u;
/// input  Pitch_CheckSensorState_RetVal               = SIG_SNA;
///  
/// input  Pitch_SigWorst_Param1                   = (uint8)SIG_INVALID;
/// input  Pitch_SigWorst_Param2                   = (uint8)SIG_INVALID;
/// input  Pitch_SigWorst_RetVal                   = (uint8)SIG_INVALID;
///
///   - Expectations:
///
/// \output 
/// \output sPitch_DispSens.eSigQty[0]                        = (uint8)SIG_VALID;
/// \output Pitch_GetLocal_DisplacementSens_Param1.eSigQty[1] = 10;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_DispMeasurement_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAb_GetSens_Raw_HitCount           = 0u;
  Rte_Read_IoHwAb_GetSens_Balanced_HitCount         = 0u;
  Pitch_CheckSensSupply_RetVal               = (uint8)SIG_VALID;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0]     = 800u;
  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[0] = 700u;
  Rte_Read_IoHwAb_VCCX1Voltage_Param1             = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens     = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens     = 2u;
  Pitch_pCodingArea->AvacStp.PitchData.snSensorSlopeFront  = 4u;
  Pitch_pCodingArea->AvacStp.PitchData.snSensorSlopeRear   = 3u;

  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Min       = 30u;
  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Max       = 40u;
  Rte_Read_IoHwAb_VCCX1Voltage_HitCount           = 0u;
  Pitch_CheckSensSupply_RetVal               = SIG_INVALID;
  ucPitch_ErrCntVccxLoRR                   = 0u;
  ucPitch_ErrCntVccxLoFR                   = 0u;
  ucPitch_ErrCntVccxHiRR                   = 0u;
  ucPitch_ErrCntVccxHiFR                   = 0u;
  Rte_Read_IoHwAb_VCCX1Voltage_Param1             = 35u;

  Pitch_DispCal_Param1                   = 1u;
  Pitch_DispCal_Param2                   = 14u;
  Pitch_DispCal_Param3                   = 65536;
  Pitch_DispCal_returnVal                   = 1;
    
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens     = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens     = 2u;
  Dem_SetEventStatus_HitCount                 = 0u;
  Pitch_CheckSensorState_Param1               = 1u;
  Pitch_CheckSensorState_RetVal               = SIG_SNA;

  Pitch_SigWorst_Param1                   = (uint8)SIG_INVALID;
  Pitch_SigWorst_Param2                   = (uint8)SIG_INVALID;
  Pitch_SigWorst_RetVal                   = (uint8)SIG_INVALID;
     
  //Step 3) Call FUT
  Pitch_DispMeasurement();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(sPitch_DispSens.eSigQty[0], (uint8)SIG_VALID, == );
  AL_UNITTEST_CHECK(Pitch_GetLocal_DisplacementSens_Param1.eSigQty[1], 10, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_DispMeasurement_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Calculate the minimum and maximum displacement values based on given inputs 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
/// input  Rte_Read_IoHwAb_GetSens_Raw_HitCount               = 0u;
/// input  Rte_Read_IoHwAb_GetSens_Balanced_HitCount         = 0u;
/// input  Pitch_CheckSensSupply_RetVal                 = (uint8)SIG_VALID;
/// input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0]       = 800u;
/// input  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[0]  = 700u;
/// input  Rte_Read_IoHwAb_VCCX1Voltage_Param1             = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens     = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens     = 2u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.snSensorSlopeFront   = 4u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.snSensorSlopeRear   = 3u;
///  
/// input  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Min       = 30u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Max       = 40u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unSensor_Error_Time  = 400u;
/// input  Rte_Read_IoHwAb_VCCX1Voltage_HitCount           = 0u;
/// input  Pitch_CheckSensSupply_RetVal                   = SIG_INVALID;
/// input  ucPitch_ErrCntVccxLoRR                   = 0u;
/// input  ucPitch_ErrCntVccxLoFR                   = 0u;
/// input  ucPitch_ErrCntVccxHiRR                   = 0u;
/// input  ucPitch_ErrCntVccxHiFR                   = 0u;
/// input  Rte_Read_IoHwAb_VCCX1Voltage_Param1             = 35u;
///
/// input  Pitch_DispCal_Param1                       = 1u;
/// input  Pitch_DispCal_Param2                       = 14u;
/// input  Pitch_DispCal_Param3                       = 65536;
/// input  Pitch_DispCal_returnVal                   = 1;
///    
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens     = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens     = 2u;
/// input  Dem_SetEventStatus_HitCount                 = 0u;
/// input  Pitch_CheckSensorState_Param1               = 1u;
/// input  Pitch_CheckSensorState_RetVal               = SIG_SNA;
///  
/// input  Pitch_SigWorst_Param1                   = (uint8)SIG_INVALID;
/// input  Pitch_SigWorst_Param2                   = (uint8)SIG_INVALID;
/// input  Pitch_SigWorst_RetVal                   = (uint8)SIG_INVALID;
///
///   - Expectations:
///
/// \output sPitch_DispSens.eSigQty[0]                        = (uint8)SIG_VALID;
/// \output Pitch_GetLocal_DisplacementSens_Param1.eSigQty[1] = 10;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_DispMeasurement_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAb_GetSens_Raw_HitCount           = 0u;
  Rte_Read_IoHwAb_GetSens_Balanced_HitCount         = 0u;
  Pitch_CheckSensSupply_RetVal               = (uint8)SIG_VALID;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0]     = 800u;
  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[0] = 700u;
  Rte_Read_IoHwAb_VCCX1Voltage_Param1             = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens     = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens     = 2u;
  Pitch_pCodingArea->AvacStp.PitchData.snSensorSlopeFront = 4u;
  Pitch_pCodingArea->AvacStp.PitchData.snSensorSlopeRear   = 3u;

  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Min       = 30u;
  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Max       = 40u;
  Rte_Read_IoHwAb_VCCX1Voltage_HitCount           = 0u;
  Pitch_CheckSensSupply_RetVal               = SIG_INVALID;
  ucPitch_ErrCntVccxLoRR                   = 0u;
  ucPitch_ErrCntVccxLoFR                   = 0u;
  ucPitch_ErrCntVccxHiRR                   = 0u;
  ucPitch_ErrCntVccxHiFR                   = 0u;
  Rte_Read_IoHwAb_VCCX1Voltage_Param1             = 35u;
    
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens     = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens     = 2u;
  Dem_SetEventStatus_HitCount                 = 0u;

  NvmBlockDeltaPwmPara.ucSensVbatError[2u] = 1u;
  //Step 3) Call FUT
  Pitch_DispMeasurement();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(sPitch_DispSens.eSigQty[0], (uint8)SIG_VALID, == );
  AL_UNITTEST_CHECK(Pitch_GetLocal_DisplacementSens_Param1.eSigQty[1], 10, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_DispMeasurement_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  check this function to check the wuality of the signal based on Displancemet
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  Rte_Read_IoHwAb_GetSens_Raw_HitCount = 0u;
/// input  Rte_Read_IoHwAb_GetSens_Balanced_HitCount = 0u;
/// input  Pitch_CheckSensSupply_RetVal = (uint8)SIG_SNA;
/// input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0] = 800u;
/// input  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[0] = 700u;
/// input  Rte_Read_IoHwAb_VCCX1Voltage_Param1 = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 2u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.snSensorSlopeFront = 4u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.snSensorSlopeRear = 3u;
///
/// input  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Min = 30u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Max = 40u;
/// input  Rte_Read_IoHwAb_VCCX1Voltage_HitCount = 0u;
/// input  Pitch_CheckSensSupply_RetVal = SIG_INVALID;
/// input  ucPitch_ErrCntVccxLoRR = 0u;
/// input  ucPitch_ErrCntVccxLoFR = 0u;
/// input  ucPitch_ErrCntVccxHiRR = 0u;
/// input  ucPitch_ErrCntVccxHiFR = 0u;
/// input  Rte_Read_IoHwAb_VCCX1Voltage_Param1 = 0u;
/// input  
///
/// input  Pitch_DispCal_Param1 = 1u;
/// input  Pitch_DispCal_Param2 = 14u;
/// input  Pitch_DispCal_Param3 = 650;
/// input  Pitch_DispCal_returnVal = 1u;
/// 
/// input   Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 1u;
/// input   Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 2u;
/// input   Dem_SetEventStatus_HitCount = 0u;
/// input   Pitch_CheckSensorState_Param1 = 2u;
/// input   Pitch_CheckSensorState_RetVal = SIG_SNA;
///
/// input  Pitch_SigWorst_Param1 = (uint8)SIG_INIT;
/// input  Pitch_SigWorst_Param2 = (uint8)SIG_INIT;
/// input  Pitch_SigWorst_RetVal = (uint8)SIG_INIT;
///
///   - Expectations:
/// 
/// \output  sPitch_DispSens.eSigQty[0]              = (uint8)SIG_VALID
/// \output  Rte_Read_IoHwAb_VCCX1Voltage_HitCoun        = 1u
/// \output  Pitch_SigWorst_RetVal                = (uint8)SIG_INIT
/// \output  Pitch_CheckSensorState_RetVal            = SIG_SNA
/// \output  Dem_SetEventStatus_HitCount            = 3u
/// \output  Pitch_GetLocal_DisplacementSens_Param1.nDisp[0]  = 10
/// \output  Pitch_GetLocal_DisplacementSens_Param1.eSigQty[0]= 10
/// \output  Pitch_GetLocal_DisplacementSens_Param1.nDisp[1]  = 10
/// \output  Pitch_GetLocal_DisplacementSens_Param1.eSigQty[1]= 10
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_DispMeasurement_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Rte_Read_IoHwAb_GetSens_Raw_HitCount = 0u;
  Rte_Read_IoHwAb_GetSens_Balanced_HitCount = 0u;
  Pitch_CheckSensSupply_RetVal = (uint8)SIG_SNA;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0] = 800u;
  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[0] = 700u;
  Rte_Read_IoHwAb_VCCX1Voltage_Param1 = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 2u;
  Pitch_pCodingArea->AvacStp.PitchData.snSensorSlopeFront = 4u;
  Pitch_pCodingArea->AvacStp.PitchData.snSensorSlopeRear = 3u;

  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Min = 30u;
  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Max = 40u;
  Rte_Read_IoHwAb_VCCX1Voltage_HitCount = 0u;
  Pitch_CheckSensSupply_RetVal = SIG_INVALID;
  ucPitch_ErrCntVccxLoRR = 0u;
  ucPitch_ErrCntVccxLoFR = 0u;
  ucPitch_ErrCntVccxHiRR = 0u;
  ucPitch_ErrCntVccxHiFR = 0u;
  Rte_Read_IoHwAb_VCCX1Voltage_Param1 = 0u;

  Pitch_DispCal_Param1 = 1u;
  Pitch_DispCal_Param2 = 14u;
  Pitch_DispCal_Param3 = 650;
  Pitch_DispCal_returnVal = 1u;

  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 2u;
  Dem_SetEventStatus_HitCount = 0u;
  Pitch_CheckSensorState_Param1 = 2u;
  Pitch_CheckSensorState_RetVal = SIG_SNA;

  Pitch_SigWorst_Param1 = (uint8)SIG_INIT;
  Pitch_SigWorst_Param2 = (uint8)SIG_INIT;
  Pitch_SigWorst_RetVal = (uint8)SIG_INIT;

  //Step 3) Call FUT         
  Pitch_DispMeasurement();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(sPitch_DispSens.eSigQty[0], (uint8)SIG_VALID, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_VCCX1Voltage_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Pitch_SigWorst_RetVal, (uint8)SIG_INIT, == );
  AL_UNITTEST_CHECK(Pitch_CheckSensorState_RetVal, SIG_SNA, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 3u, == );
  AL_UNITTEST_CHECK(Pitch_GetLocal_DisplacementSens_Param1.nDisp[0], 10, == );
  AL_UNITTEST_CHECK(Pitch_GetLocal_DisplacementSens_Param1.eSigQty[0], 10, == );
  AL_UNITTEST_CHECK(Pitch_GetLocal_DisplacementSens_Param1.nDisp[1], 10, == );
  AL_UNITTEST_CHECK(Pitch_GetLocal_DisplacementSens_Param1.eSigQty[1], 10, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_DispMeasurement
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if the function correctly checks the quality of the displacement signals
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_DispMeasurement(void)
{
  Mt_Pitch_Pitch_DispMeasurement_TestCase_1();
  Mt_Pitch_Pitch_DispMeasurement_TestCase_2();
  Mt_Pitch_Pitch_DispMeasurement_TestCase_3();
  Mt_Pitch_Pitch_DispMeasurement_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_AngleCalc_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  calculate AutoAngle in 1/10 mrad (mm at distance of 10m)
///         --------------------------------------------------------
///         AutoAngle[0.1mrad] = ((Front[mm]    - Rear[mm])    * 10000 ) / Wheelbase[mm]
///                            = ((Front[0.1mm] - Rear[0.1mm]) *  1000 ) / Wheelbase[mm] 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
/// input  Pitch_AngleCalc_Param1               = 8;
/// input  Pitch_AngleCalc_Param2               = 2;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unR1     = 5;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unR2     = 4;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unWHEELBASE = 3;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDPF     = 3;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDPR     = 4;
/// input  Pitch_pCodingArea->AvacStp.PitchData.snAngleMin  = 200;
/// input  Pitch_pCodingArea->AvacStp.PitchData.snAngleMax  = 5000;
///
///   - Expectations:
///
/// \output 
/// \output  Pitch_AngleCalc_RetVal = 3866 ;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_AngleCalc_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Pitch_AngleCalc_Param1               = 8;
  Pitch_AngleCalc_Param2               = 2;
  Pitch_pCodingArea->AvacStp.PitchData.unR1     = 5;
  Pitch_pCodingArea->AvacStp.PitchData.unR2     = 4;
  Pitch_pCodingArea->AvacStp.PitchData.unWHEELBASE = 3;
  Pitch_pCodingArea->AvacStp.PitchData.ucDPF     = 3;
  Pitch_pCodingArea->AvacStp.PitchData.ucDPR     = 4;
  Pitch_pCodingArea->AvacStp.PitchData.snAngleMin  = 200;
  Pitch_pCodingArea->AvacStp.PitchData.snAngleMax  = 5000;

  //Step 3) Call FUT
  Pitch_AngleCalc_RetVal = Pitch_AngleCalc(Pitch_AngleCalc_Param1, Pitch_AngleCalc_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_AngleCalc_RetVal, 3866, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_AngleCalc_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  calculate AutoAngle in 1/10 mrad (mm at distance of 10m)
///         --------------------------------------------------------
///         AutoAngle[0.1mrad] = ((Front[mm]    - Rear[mm])    * 10000 ) / Wheelbase[mm]
///                            = ((Front[0.1mm] - Rear[0.1mm]) *  1000 ) / Wheelbase[mm] 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input   Pitch_AngleCalc_Param1               = 8;
/// input   Pitch_AngleCalc_Param2               = 2;
/// input   Pitch_pCodingArea->AvacStp.PitchData.unR1     = 5;
/// input   Pitch_pCodingArea->AvacStp.PitchData.unR2     = 4;
/// input   Pitch_pCodingArea->AvacStp.PitchData.ucDPF     = 3;
/// input   Pitch_pCodingArea->AvacStp.PitchData.ucDPR     = 4;
/// input   Pitch_pCodingArea->AvacStp.PitchData.snAngleMin  = 200;
/// input   Pitch_pCodingArea->AvacStp.PitchData.snAngleMax  = 5000;
/// input   Pitch_pCodingArea->AvacStp.PitchData.unWHEELBASE = 0;
///
///   - Expectations:
///
/// \output 
/// \output  Pitch_AngleCalc_RetVal = 200 ;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_AngleCalc_TestCase_2(void)
{ 
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Pitch_AngleCalc_Param1               = 8;
  Pitch_AngleCalc_Param2               = 2;
  Pitch_pCodingArea->AvacStp.PitchData.unR1     = 5;
  Pitch_pCodingArea->AvacStp.PitchData.unR2     = 4;
  Pitch_pCodingArea->AvacStp.PitchData.ucDPF     = 3;
  Pitch_pCodingArea->AvacStp.PitchData.ucDPR     = 4;
  Pitch_pCodingArea->AvacStp.PitchData.snAngleMin  = 200;
  Pitch_pCodingArea->AvacStp.PitchData.snAngleMax  = 5000;
  Pitch_pCodingArea->AvacStp.PitchData.unWHEELBASE = 0;

  //Step 3) Call FUT
  Pitch_AngleCalc_RetVal = Pitch_AngleCalc(Pitch_AngleCalc_Param1, Pitch_AngleCalc_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_AngleCalc_RetVal, 200, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_AngleCalc_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  calculate AutoAngle in 1/10 mrad (mm at distance of 10m)
///         --------------------------------------------------------
///         AutoAngle[0.1mrad] = ((Front[mm]    - Rear[mm])    * 10000 ) / Wheelbase[mm]
///                            = ((Front[0.1mm] - Rear[0.1mm]) *  1000 ) / Wheelbase[mm] 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
/// input  Pitch_AngleCalc_Param1               = 8;
/// input  Pitch_AngleCalc_Param2               = 2;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unR1     = 5;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unR2     = 4;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unWHEELBASE = 3;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDPF     = 3;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDPR     = 4;
/// input  Pitch_pCodingArea->AvacStp.PitchData.snAngleMin  = 200;
/// input  Pitch_pCodingArea->AvacStp.PitchData.snAngleMax  = 5000;
///
///   - Expectations:
///
/// \output 
/// \output  Pitch_AngleCalc_RetVal = 200u ;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_AngleCalc_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Pitch_AngleCalc_Param1 = 8;
  Pitch_AngleCalc_Param2 = 0;
  Pitch_pCodingArea->AvacStp.PitchData.unR1 = 5;
  Pitch_pCodingArea->AvacStp.PitchData.unR2 = 0;
  Pitch_pCodingArea->AvacStp.PitchData.unWHEELBASE = 1;
  Pitch_pCodingArea->AvacStp.PitchData.ucDPF = 300;
  Pitch_pCodingArea->AvacStp.PitchData.ucDPR = 4;
  Pitch_pCodingArea->AvacStp.PitchData.snAngleMin = 200;
  Pitch_pCodingArea->AvacStp.PitchData.snAngleMax = 100;

  //Step 3) Call FUT
  Pitch_AngleCalc_RetVal = Pitch_AngleCalc(Pitch_AngleCalc_Param1, Pitch_AngleCalc_Param2);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_AngleCalc_RetVal, 200u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_AngleCalc
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if the function calculates the correct angle in 1/10 mrad
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_AngleCalc(void)
{
  Mt_Pitch_Pitch_AngleCalc_TestCase_1();
  Mt_Pitch_Pitch_AngleCalc_TestCase_2();
  Mt_Pitch_Pitch_AngleCalc_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_PitchMeasurement()
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  check the function for delivering the Pitch angle and the quality of the signal
///        based on the displacement. This function is the output of this module
///        The Angle and the quality of the signal is needed in AVAC module
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input   sPitch_DispSens.nDisp[0u]             = 1;
/// input   sPitch_DispSens.eSigQty[0u]             = 1;
/// input   sPitch_DispSens.nDisp[1u]             = 1;
/// input   sPitch_DispSens.eSigQty[1u]             = 1;
/// input   Rte_Write_Pitch_Angle_HitCount           = 0u;
/// input   Pitch_pCodingArea->AvacStp.PitchData.unWHEELBASE = 0u;
///
///   - Expectations:
///
/// \output 
/// \output  Rte_Write_Pitch_Angle_HitCount          = 1u ;
/// \output  Rte_Write_Pitch_Angle_Param1.eSigQty    = SIG_VALID;
/// \output  Rte_Write_Pitch_Angle_Param1.nAngle     = 200 ;
/// \output  Rte_Write_Pitch_Angle_Param1.nHeightErr = 0 ;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_PitchMeasurement(void)
{  
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  sPitch_DispSens.nDisp[0u]             = 1;
  sPitch_DispSens.eSigQty[0u]             = 1;
  sPitch_DispSens.nDisp[1u]             = 1;
  sPitch_DispSens.eSigQty[1u]             = 1;
  Rte_Write_Pitch_Angle_HitCount           = 0u;
  Pitch_pCodingArea->AvacStp.PitchData.unWHEELBASE = 0u;
  
  //Step 3) Call FUT
  Pitch_PitchMeasurement();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_Pitch_Angle_HitCount,         1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_Angle_Param1.eSigQty, SIG_VALID, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_Angle_Param1.nAngle,        200, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_Angle_Param1.nHeightErr,      0, == );
  

}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_Cycle0_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_CAN;
/// input  Dem_SetEventStatus_HitCount      = 0u;
/// input  boPitch_CodingValidity        = FALSE;
/// input  Dem_SetEventStatus_Param1           = (uint16)RR_BHS_SUPPLY_HIGH;
/// input  Dem_SetEventStatus_Param2           = DEM_EVENT_STATUS_PASSED;
/// input  boPitch_CodingValidity        = FALSE;
///   - Expectations:
///
/// \output 
/// \output  Dem_SetEventStatus_HitCount = 0u; 
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_Cycle0_TestCase_1()
{ 
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_CAN;
  Dem_SetEventStatus_HitCount      = 0u;
  boPitch_CodingValidity        = FALSE;
  Dem_SetEventStatus_Param1           = (uint16)RR_BHS_SUPPLY_HIGH;
  Dem_SetEventStatus_Param2           = DEM_EVENT_STATUS_PASSED;
  boPitch_CodingValidity        = FALSE;

  //Step 3) Call FUT
  Pitch_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 0u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_Cycle0_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  NvmBlockDeltaPwmPara.eNVM_VAC_Input                 = eInput_HLS;
/// input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0u]         = 1u;   
/// input  Rte_Write_Pitch_PlausState_HitCount                 = 0u;
/// input  Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE         = ePitchState_Fail;
/// input  Pitch_RteAccess_Get_VehNetState_Param1.eVESMainState       = VESState_Stop;
/// input  Pitch_CheckVehSpeedData_RetVal                   = ePlauSig_Pass;
/// input  Pitch_ePitchSensorFailure                     = eHLS_FROZEN_FAILURE;
/// input  boPitch_CodingValidity                       = TRUE;
/// input  Rte_Read_IoHwAb_GetSens_Raw_HitCount               = 0u;
/// input  Rte_Read_IoHwAb_GetSens_Balanced_HitCount             = 0u;
/// input  Pitch_CheckSensSupply_RetVal                   = (uint8)SIG_VALID;
/// input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0]         = 800u;
/// input  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[0]     = 700u;
/// input  Rte_Read_IoHwAb_VCCX1Voltage_Param1                 = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens         = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens         = 2u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.snSensorSlopeFront     = 4u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.snSensorSlopeRear       = 3u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Min           = 30u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Max           = 40u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unSensor_Error_Time     = 400u;
/// input  Rte_Read_IoHwAb_VCCX1Voltage_HitCount               = 0u;
/// input  Pitch_CheckSensSupply_RetVal                   = SIG_INVALID;
/// input  ucPitch_ErrCntVccxLoRR                       = 0u;
/// input  ucPitch_ErrCntVccxLoFR                       = 0u;
/// input  ucPitch_ErrCntVccxHiRR                       = 0u;
/// input  ucPitch_ErrCntVccxHiFR                       = 0u;
/// input  Rte_Read_IoHwAb_VCCX1Voltage_Param1                 = 35u;
/// input  Pitch_DispCal_Param1                       = 1u;
/// input  Pitch_DispCal_Param2                       = 14u;
/// input  Pitch_DispCal_Param3                       = 650;
/// input  Pitch_DispCal_returnVal                       = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens         = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens         = 2u;
/// input  Dem_SetEventStatus_HitCount                     = 0u;
/// input  Pitch_CheckSensorState_Param1                   = 2u;
/// input  Pitch_CheckSensorState_RetVal                   = SIG_SNA;
/// input  Pitch_SigWorst_Param1                       = (uint8)SIG_SNA;
/// input  Pitch_SigWorst_Param2                       = (uint8)SIG_SNA;
/// input  Pitch_SigWorst_RetVal                       = (uint8)SIG_SNA;  
/// input  sPitch_DispSens.nDisp[0u]                     = 1;
/// input  sPitch_DispSens.eSigQty[0u]                     = 1;
/// input  sPitch_DispSens.nDisp[1u]                     = 1;
/// input  sPitch_DispSens.eSigQty[1u]                     = 1;
/// input  Rte_Write_Pitch_Angle_HitCount                   = 0u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unWHEELBASE         = 0u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.snAngleMin           = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.snAngleMax           = 3u;
/// input                                   
/// input  Pitch_AngleCalc_Param1                       = 8;
/// input  Pitch_AngleCalc_Param2                       = 2;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unR1             = 5;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unR2             = 4;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDPF             = 3;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDPR             = 4;
/// input  Pitch_pCodingArea->AvacStp.PitchData.snAngleMin           = 200;
/// input  Pitch_pCodingArea->AvacStp.PitchData.snAngleMax           = 5000;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unWHEELBASE         = 0;
/// input                                   
/// input  Pitch_SigWorst_Param1                       = SIG_SNA;
/// input  Pitch_SigWorst_Param2                       = SIG_SNA;
/// input                                   
/// input  Rte_Write_Pitch_Angle_HitCount                   = 0u;
/// input                                   
/// input  Rte_Read_CtrlStp_Validation_Port_HitCount             = 0u;
/// input  Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE         = eStpState_Adj;
/// input  
/// input  Rte_Read_SysMon_VehicleSpeed_HitCount               = 0u;
/// input  Pitch_ePitchSensorFailure                     = eHLS_SENSOR_FAILURE;
/// input  Rte_Write_Pitch_PlausState_HitCount                 = 0u;
/// input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty             = SIG_VALID;
/// input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 120u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.BhsPlausVehSpeed       = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.BhsPlausMin         = 15u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.BhsPlausMax         = 30u;
/// input  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[0]     = 600u;
/// input  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[1]     = 600u;
/// input  boBhsValCheck                           = FALSE;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens         = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens         = 2u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unSensor_Error_Time     = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unSensor_Recover_Time     = 1u;
/// input  Rte_Read_IoHwAb_GetSens_Balanced_HitCount             = 0u;
/// input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0]         = 800u;
/// input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1]         = 800u;
/// input  Pitch_CheckVehSpeedData_RetVal                   = ePlauSig_Fail;
/// input  Pitch_CheckSensValue_RetVal                     = ePlauSig_Fail;
/// input  Pitch_pCodingArea->AvacStp.PitchData.SensorOutRangeTime       = 1u;
/// input  LPTMR0_GetTimeElapsed_RetVal                   = 0xFFFFu;
/// input  boDispValCheck[0]                           = FALSE;
/// input  Rte_Read_IoHwAb_GetSens_Raw_HitCount               = 0u;
/// input  Pitch_ulCheckBHS_us                         = 20u;
///
///   - Expectations:
///
/// \output 
/// \output sPitch_DispSens.eSigQty[0]                          = (uint8)SIG_VALID
/// \output Rte_Read_IoHwAb_VCCX1Voltage_HitCount        = 2u
/// \output Pitch_SigWorst_RetVal                = (uint8)SIG_SNA
/// \output Pitch_CheckSensorState_RetVal            = SIG_SNA
/// \output Dem_SetEventStatus_HitCount              = 11u
/// \output Pitch_GetLocal_DisplacementSens_Param1.nDisp[0]    = 10
/// \output Pitch_GetLocal_DisplacementSens_Param1.eSigQty[0]  = 10
/// \output Pitch_GetLocal_DisplacementSens_Param1.nDisp[1]    = 10
/// \output Pitch_GetLocal_DisplacementSens_Param1.eSigQty[1]  = 10
/// \output Rte_Write_Pitch_Angle_HitCount            = 1u
/// \output Rte_Write_Pitch_Angle_Param1.eSigQty        = SIG_VALID
/// \output Rte_Write_Pitch_Angle_Param1.nAngle          = 200
/// \output Rte_Write_Pitch_Angle_Param1.nHeightErr        = 0
/// \output Pitch_AngleCalc_RetVal                = 200
/// \output Pitch_RteAccess_Get_GetAdlPhase_Param1        = ePitchState_Maxsize
/// \output Rte_Read_CtrlStp_Validation_Port_HitCount      = 1u
/// \output Rte_Write_Pitch_PlausState_HitCount          = 1u
/// \output Rte_Read_SysMon_VehicleSpeed_HitCount        = 2u
/// \output Pitch_ePitchSensorFailure              = eHLS_FROZEN_FAILURE
/// \output Rte_Write_Pitch_PlausState_Param1          = eHLS_FROZEN_FAILURE
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_Cycle0_TestCase_2(void)
{  
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvmBlockDeltaPwmPara.eNVM_VAC_Input                 = eInput_HLS;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0u]         = 1u;   
  Rte_Write_Pitch_PlausState_HitCount                 = 0u;
  Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE         = ePitchState_Fail;
  Pitch_RteAccess_Get_VehNetState_Param1.eVESMainState       = VESState_Stop;
  Pitch_CheckVehSpeedData_RetVal                   = ePlauSig_Pass;
  Pitch_ePitchSensorFailure                     = eHLS_FROZEN_FAILURE;
  boPitch_CodingValidity                       = TRUE;
  Rte_Read_IoHwAb_GetSens_Raw_HitCount               = 0u;
  Rte_Read_IoHwAb_GetSens_Balanced_HitCount             = 0u;
  Pitch_CheckSensSupply_RetVal                   = (uint8)SIG_VALID;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0]         = 800u;
  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[0]     = 700u;
  Rte_Read_IoHwAb_VCCX1Voltage_Param1                 = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens         = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens         = 2u;
  Pitch_pCodingArea->AvacStp.PitchData.snSensorSlopeFront     = 4u;
  Pitch_pCodingArea->AvacStp.PitchData.snSensorSlopeRear       = 3u;
  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Min           = 30u;
  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Max           = 40u;
  Rte_Read_IoHwAb_VCCX1Voltage_HitCount               = 0u;
  Pitch_CheckSensSupply_RetVal                   = SIG_INVALID;
  ucPitch_ErrCntVccxLoRR                       = 0u;
  ucPitch_ErrCntVccxLoFR                       = 0u;
  ucPitch_ErrCntVccxHiRR                       = 0u;
  ucPitch_ErrCntVccxHiFR                       = 0u;
  Rte_Read_IoHwAb_VCCX1Voltage_Param1                 = 35u;
  Pitch_DispCal_Param1                       = 1u;
  Pitch_DispCal_Param2                       = 14u;
  Pitch_DispCal_Param3                       = 650;
  Pitch_DispCal_returnVal                       = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens         = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens         = 2u;
  Dem_SetEventStatus_HitCount                     = 0u;
  Pitch_CheckSensorState_Param1                   = 2u;
  Pitch_CheckSensorState_RetVal                   = SIG_SNA;
  Pitch_SigWorst_Param1                       = (uint8)SIG_SNA;
  Pitch_SigWorst_Param2                       = (uint8)SIG_SNA;
  Pitch_SigWorst_RetVal                       = (uint8)SIG_SNA;  
  sPitch_DispSens.nDisp[0u]                     = 1;
  sPitch_DispSens.eSigQty[0u]                     = 1;
  sPitch_DispSens.nDisp[1u]                     = 1;
  sPitch_DispSens.eSigQty[1u]                     = 1;
  Rte_Write_Pitch_Angle_HitCount                   = 0u;
  Pitch_pCodingArea->AvacStp.PitchData.unWHEELBASE         = 0u;
  Pitch_pCodingArea->AvacStp.PitchData.snAngleMin           = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.snAngleMax           = 3u;
                                   
  Pitch_AngleCalc_Param1                       = 8;
  Pitch_AngleCalc_Param2                       = 2;
  Pitch_pCodingArea->AvacStp.PitchData.unR1             = 5;
  Pitch_pCodingArea->AvacStp.PitchData.unR2             = 4;
  Pitch_pCodingArea->AvacStp.PitchData.ucDPF             = 3;
  Pitch_pCodingArea->AvacStp.PitchData.ucDPR             = 4;
  Pitch_pCodingArea->AvacStp.PitchData.snAngleMin           = 200;
  Pitch_pCodingArea->AvacStp.PitchData.snAngleMax           = 5000;
  Pitch_pCodingArea->AvacStp.PitchData.unWHEELBASE         = 0;
                                   
  Pitch_SigWorst_Param1                       = SIG_SNA;
  Pitch_SigWorst_Param2                       = SIG_SNA;
                                   
  Rte_Write_Pitch_Angle_HitCount                   = 0u;
                                   
  Rte_Read_CtrlStp_Validation_Port_HitCount             = 0u;
  Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE         = eStpState_Adj;
  
  Rte_Read_SysMon_VehicleSpeed_HitCount               = 0u;
  Pitch_ePitchSensorFailure                     = eHLS_SENSOR_FAILURE;
  Rte_Write_Pitch_PlausState_HitCount                 = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty             = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 120u;
  Pitch_pCodingArea->AvacStp.PitchData.BhsPlausVehSpeed       = 1u;
  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[0]     = 600u;
  Rte_Read_IoHwAb_GetSens_Balanced_Param1.alSensBalance[1]     = 600u;
  boBhsValCheck                           = FALSE;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens         = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens         = 2u;
  Rte_Read_IoHwAb_GetSens_Balanced_HitCount             = 0u;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0]         = 800u;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1]         = 800u;
  Pitch_CheckVehSpeedData_RetVal                   = ePlauSig_Fail;
  Pitch_CheckSensValue_RetVal                     = ePlauSig_Fail;
  Pitch_pCodingArea->AvacStp.PitchData.SensorOutRangeTime       = 1u;
  LPTMR0_GetTimeElapsed_RetVal                   = 0xFFFFu;
  boDispValCheck[0]                           = FALSE;
  Rte_Read_IoHwAb_GetSens_Raw_HitCount               = 0u;
  Pitch_ulCheckBHS_us                         = 20u;
  NvmBlockDeltaPwmPara.eNVM_VAC_Input = eInput_CAN;


  //Step 3) Call FUT
  Pitch_Cycle0();
  

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(sPitch_DispSens.eSigQty[0],                   (uint8)SIG_VALID, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_VCCX1Voltage_HitCount,                    2u, == );
  AL_UNITTEST_CHECK(Pitch_SigWorst_RetVal,                     (uint8)SIG_SNA, == );
  AL_UNITTEST_CHECK(Pitch_CheckSensorState_RetVal,                        SIG_SNA, == );
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,                         11u, == );
  AL_UNITTEST_CHECK(Pitch_GetLocal_DisplacementSens_Param1.nDisp[0],               10, == );
  AL_UNITTEST_CHECK(Pitch_GetLocal_DisplacementSens_Param1.eSigQty[0],             10, == );
  AL_UNITTEST_CHECK(Pitch_GetLocal_DisplacementSens_Param1.nDisp[1],               10, == );
  AL_UNITTEST_CHECK(Pitch_GetLocal_DisplacementSens_Param1.eSigQty[1],             10, == );                                        
  AL_UNITTEST_CHECK(Rte_Write_Pitch_Angle_HitCount,                            1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_Angle_Param1.eSigQty,                   SIG_VALID, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_Angle_Param1.nAngle,                          200, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_Angle_Param1.nHeightErr,                       0, == );
  AL_UNITTEST_CHECK(Pitch_AngleCalc_RetVal,                             200, == );
  AL_UNITTEST_CHECK(Pitch_RteAccess_Get_GetAdlPhase_Param1,       ePitchState_Maxsize, == );
  AL_UNITTEST_CHECK(Rte_Read_CtrlStp_Validation_Port_HitCount,                     1u, == );  
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_HitCount,                          1u,  == );
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,                        2u,  == );
  AL_UNITTEST_CHECK(Pitch_ePitchSensorFailure,           eHLS_FROZEN_FAILURE,  == );   
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_Param1,           eHLS_FROZEN_FAILURE,  == );

}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_Cycle0_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  NvmBlockDeltaPwmPara.eNVM_VAC_Input           = eInput_HLS;
/// input  boPitch_CodingValidity                 = TRUE;
/// input  Pitch_SetLocal_DisplacementSens_Param1.eSigQty[0u] = (uint8)SIG_VALID;
/// input  Pitch_SetLocal_DisplacementSens_Param1.nDisp[0u]   = 1u;
/// input  Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE = eStpState_Adj;
/// input  Rte_Write_Pitch_PlausState_HitCount           = 0u;
/// input  Pitch_CheckVehSpeedData_RetVal             = ePlauSig_Fail;
/// input  Pitch_CheckSensValue_RetVal               = ePlauSig_Fail;
///
///
///   - Expectations:
///
/// \output 
/// \output Rte_Write_Pitch_PlausState_HitCount  = 1u ;
/// \output Rte_Write_Pitch_PlausState_Param1    = eHLS_FROZEN_FAILURE;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_Cycle0_TestCase_3(void)
{  
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvmBlockDeltaPwmPara.eNVM_VAC_Input           = eInput_HLS;
  boPitch_CodingValidity                 = TRUE;
  Pitch_SetLocal_DisplacementSens_Param1.eSigQty[0u] = (uint8)SIG_VALID;
  Pitch_SetLocal_DisplacementSens_Param1.nDisp[0u]   = 1u;
  Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE = eStpState_Adj;
  Rte_Write_Pitch_PlausState_HitCount           = 0u;
  Pitch_CheckVehSpeedData_RetVal             = ePlauSig_Fail;
  Pitch_CheckSensValue_RetVal               = ePlauSig_Fail;

  //Step 3) Call FUT
  Pitch_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_HitCount,          1u, == );
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_Param1, eHLS_FROZEN_FAILURE, == );
  
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_Cycle0_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  NvmBlockDeltaPwmPara.eNVM_VAC_Input          = eInput_HLS;
/// input  boPitch_CodingValidity                = TRUE;
/// input  Pitch_SetLocal_DisplacementSens_Param1.eSigQty[0u]  = (uint8)SIG_VALID;
/// input  Pitch_SetLocal_DisplacementSens_Param1.nDisp[0u]    = 1u;
/// input  Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE  = ePitchState_Fail;
/// input  Rte_Write_Pitch_PlausState_HitCount          = 0u;
/// input  Pitch_CheckVehSpeedData_RetVal            = ePlauSig_Fail;
/// input  Pitch_CheckSensValue_RetVal              = ePlauSig_Fail;
///
///   - Expectations:
///
/// \output 
/// \output Rte_Write_Pitch_PlausState_Param1  = eHLS_FROZEN_FAILURE;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_Cycle0_TestCase_4(void)
{ 
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvmBlockDeltaPwmPara.eNVM_VAC_Input          = eInput_HLS;
  boPitch_CodingValidity                = TRUE;
  Pitch_SetLocal_DisplacementSens_Param1.eSigQty[0u]  = (uint8)SIG_VALID;
  Pitch_SetLocal_DisplacementSens_Param1.nDisp[0u]    = 1u;
  Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE  = ePitchState_Fail;
  Rte_Write_Pitch_PlausState_HitCount          = 0u;
  Pitch_CheckVehSpeedData_RetVal            = ePlauSig_Fail;
  Pitch_CheckSensValue_RetVal              = ePlauSig_Fail;

  //Step 3) Call FUT
  Pitch_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_Param1, eHLS_FROZEN_FAILURE, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_Cycle0_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: 
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  NvmBlockDeltaPwmPara.eNVM_VAC_Input           = eInput_HLS;
/// input  boPitch_CodingValidity                 = TRUE;
/// input  Pitch_SetLocal_DisplacementSens_Param1.eSigQty[0u] = (uint8)SIG_VALID;
/// input  Pitch_SetLocal_DisplacementSens_Param1.nDisp[0u]   = 1u;
/// input  Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE = ePitchState_STT;
/// input  Rte_Write_Pitch_PlausState_HitCount           = 0u;
/// input  Pitch_CheckVehSpeedData_RetVal             = ePlauSig_Fail;
/// input  Pitch_CheckSensValue_RetVal               = ePlauSig_Fail;
///
///   - Expectations:
///
/// \output 
/// \output Rte_Write_Pitch_PlausState_Param1  = eHLS_FROZEN_FAILURE;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_Cycle0_TestCase_5(void)
{ 
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  NvmBlockDeltaPwmPara.eNVM_VAC_Input           = eInput_HLS;
  boPitch_CodingValidity                 = TRUE;
  Pitch_SetLocal_DisplacementSens_Param1.eSigQty[0u] = (uint8)SIG_VALID;
  Pitch_SetLocal_DisplacementSens_Param1.nDisp[0u]   = 1u;
  Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE = ePitchState_STT;
  Rte_Write_Pitch_PlausState_HitCount           = 0u;
  Pitch_CheckVehSpeedData_RetVal             = ePlauSig_Fail;
  Pitch_CheckSensValue_RetVal               = ePlauSig_Fail;


  //Step 3) Call FUT
  Pitch_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Write_Pitch_PlausState_Param1, eHLS_FROZEN_FAILURE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Pitch_Pitch_Cycle0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if the cyclic function reads all the signals correctly and calls the appropiate functions
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_Cycle0(void)
{
  Mt_Pitch_Pitch_Cycle0_TestCase_1();
  Mt_Pitch_Pitch_Cycle0_TestCase_2();
  Mt_Pitch_Pitch_Cycle0_TestCase_3();
  Mt_Pitch_Pitch_Cycle0_TestCase_4();
  Mt_Pitch_Pitch_Cycle0_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_CheckSensValue_TestCase_1 
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: This function is checking Displacement data 
///        Returns FALSE if Displacement data is not valid for more than SENSOR_OUTRANGE_TIME
///        Returns TRUE if Displacement data is valid for more than SENSOR_FAILURE_RECOVERY_TIME
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens             = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens             = 2u;
/// input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0]               = 600u; 
/// input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1]               = 600u;
/// input  boDispValCheck[0]                                              = FALSE;
/// input  Pitch_CheckSensValue_RetVal                                    = ePlauSig_SNA;
/// input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[PITCH_FR_SENSOR] = 0u;
/// input  Rte_Read_IoHwAb_GetSens_Raw_HitCount                           = 0u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.SensorOutRangeTime        = 1u;
/// input  LPTMR0_GetTimeElapsed_HitCount                                 = 0u;
/// input  LPTMR0_GetTimeElapsed_RetVal                                   = 0x0;
///
///   - Expectations:
///
/// \output Pitch_CheckSensValue_RetVal          = ePlauSig_SNA;
/// \output Rte_Read_IoHwAb_GetSens_Raw_HitCount = 1u;
/// \output boDispValCheck                       = FALSE;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensValue_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 2u;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0] = 600u;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1] = 600u;
  boDispValCheck[0] = FALSE;
  Pitch_CheckSensValue_RetVal = ePlauSig_SNA;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[PITCH_FR_SENSOR] = 0u;
  Rte_Read_IoHwAb_GetSens_Raw_HitCount = 0u;
  Pitch_pCodingArea->AvacStp.PitchData.SensorOutRangeTime = 1u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 0x0;

  //Step 3) Call FUT
  Pitch_CheckSensValue_RetVal = Pitch_CheckSensValue();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_CheckSensValue_RetVal, ePlauSig_SNA, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_GetSens_Raw_HitCount, 1u, == );
  AL_UNITTEST_CHECK(boDispValCheck[0], TRUE, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_CheckDispValue_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: his function is checking Displacement data 
///        Returns FALSE if Displacement data is not valid for more than SENSOR_OUTRANGE_TIME
///        Returns TRUE if Displacement data is valid for more than SENSOR_FAILURE_RECOVERY_TIME
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens      = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens      = 2u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.SensorOutRangeTime = 1u;
/// input  boDispValCheck[0]                                       = TRUE;
/// input  Pitch_CheckSensValue_RetVal                             = ePlauSig_SNA;
/// input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0]        = 600u; //700
/// input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1]        = 600u; //700
/// input  Rte_Read_IoHwAb_GetSens_Raw_HitCount                    = 0u;
/// input  LPTMR0_GetTimeElapsed_RetVal                            = 0xFFFFFFFF;
///
///   - Expectations:
///
/// \output Rte_Read_IoHwAb_GetSens_Raw_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensValue_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 2u;
  Pitch_pCodingArea->AvacStp.PitchData.SensorOutRangeTime = 1u;
  boDispValCheck[0] = TRUE;
  Pitch_CheckSensValue_RetVal = ePlauSig_SNA;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0] = 600u; //700
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1] = 600u; //700
  Rte_Read_IoHwAb_GetSens_Raw_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 0xFFFFFFFF;

  //Step 3) Call FUT
  Pitch_CheckSensValue_RetVal = Pitch_CheckSensValue();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_GetSens_Raw_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_CheckDispValue_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: his function is checking Displacement data 
///        Returns FALSE if Displacement data is not valid for more than SENSOR_OUTRANGE_TIME
///        Returns TRUE if Displacement data is valid for more than SENSOR_FAILURE_RECOVERY_TIME
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens    = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens    = 2u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.SensorOutRangeTime = 1u;
/// input  bool boDispValCheck                    = FALSE;
/// input  Pitch_CheckSensValue_RetVal                = ePlauSig_SNA;
/// input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0]    = 600u; //700
/// input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1]    = 600u; //700
/// input  Rte_Read_IoHwAb_GetSens_Raw_HitCount          = 0u;
///
///   - Expectations:
///
/// \output Rte_Read_IoHwAb_GetSens_Raw_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensValue_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 2u;
  Pitch_pCodingArea->AvacStp.PitchData.SensorOutRangeTime = 20u;
  boDispValCheck[0] = TRUE;
  Pitch_CheckSensValue_RetVal = ePlauSig_SNA;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0] = 600u; //700
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1] = 600u; //700
  Rte_Read_IoHwAb_GetSens_Raw_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 0x01;

  //Step 3) Call FUT
  Pitch_CheckSensValue_RetVal = Pitch_CheckSensValue();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_GetSens_Raw_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_CheckSensValue_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: his function is checking Displacement data 
///        Returns FALSE if Displacement data is not valid for more than SENSOR_OUTRANGE_TIME
///        Returns TRUE if Displacement data is valid for more than SENSOR_FAILURE_RECOVERY_TIME
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens      = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens      = 2u;
/// input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0]        = 900u; //700
/// input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1]        = 900u; //700
/// input  boDispValCheck[0]                                       = TRUE;
/// input  Pitch_CheckSensValue_RetVal                             = ePlauSig_SNA;
/// input  Rte_Read_IoHwAb_GetSens_Raw_HitCount                    = 0u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.SensorOutRangeTime = 1u;
/// input  LPTMR0_GetTimeElapsed_HitCount                          = 0u;
/// input  LPTMR0_GetTimeElapsed_RetVal                            = 0xFFFFu;
///
///   - Expectations:
///
/// \output Pitch_CheckSensValue_RetVal           = ePlauSig_SNA;
/// \output Rte_Read_IoHwAb_GetSens_Raw_HitCount  = 1u;
/// \output boDispValCheck[0]                     = TRUE;
/// \output LPTMR0_GetTimeElapsed_HitCount        = 1u;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensValue_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 2u;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0] = 900u; //700
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1] = 900u; //700
  boDispValCheck[0] = TRUE;
  Pitch_CheckSensValue_RetVal = ePlauSig_SNA;
  Rte_Read_IoHwAb_GetSens_Raw_HitCount = 0u;
  Pitch_pCodingArea->AvacStp.PitchData.SensorOutRangeTime = 1u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 0xFFFFu;

  //Step 3) Call FUT
  Pitch_CheckSensValue_RetVal = Pitch_CheckSensValue();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_CheckSensValue_RetVal, ePlauSig_SNA, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_GetSens_Raw_HitCount, 1u, == );
  AL_UNITTEST_CHECK(boDispValCheck[0], TRUE, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_CheckSensValue_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: his function is checking Displacement data 
///        Returns FALSE if Displacement data is not valid for more than SENSOR_OUTRANGE_TIME
///        Returns TRUE if Displacement data is valid for more than SENSOR_FAILURE_RECOVERY_TIME
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens      = 1u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens      = 2u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.SensorOutRangeTime = 1u;
/// input  boDispValCheck[1]                                       = TRUE;
/// input  Pitch_CheckSensValue_RetVal                             = ePlauSig_SNA;
/// input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0]        = 900u; //700
/// input  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1]        = 900u; //700
/// input  Rte_Read_IoHwAb_GetSens_Raw_HitCount                    = 0u;
/// input  LPTMR0_GetTimeElapsed_HitCount                          = 0u;
/// input  LPTMR0_GetTimeElapsed_RetVal                            = 0xFFFFu;
///
///   - Expectations:
///
/// \output LPTMR0_GetTimeElapsed_HitCount       = 1u;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensValue_TestCase_5(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMinSens = 1u;
  Pitch_pCodingArea->AvacStp.PitchData.ucDutyMaxSens = 2u;
  Pitch_pCodingArea->AvacStp.PitchData.SensorOutRangeTime = 1u;
  boDispValCheck[1] = TRUE;
  Pitch_CheckSensValue_RetVal = ePlauSig_SNA;
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[0] = 900u; //700
  Rte_Read_IoHwAb_GetSens_Raw_Param1.aucSensRaw[1] = 900u; //700
  Rte_Read_IoHwAb_GetSens_Raw_HitCount = 0u;
  LPTMR0_GetTimeElapsed_HitCount = 0u;
  LPTMR0_GetTimeElapsed_RetVal = 0xFFFFFFFF;

  //Step 3) Call FUT
  Pitch_CheckSensValue_RetVal = Pitch_CheckSensValue();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Pitch_Pitch_CheckSensValue
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if the function checks the validity of the displacement data
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensValue(void)
{
  Mt_Pitch_Pitch_CheckSensValue_TestCase_1();
  Mt_Pitch_Pitch_CheckSensValue_TestCase_2();
  Mt_Pitch_Pitch_CheckSensValue_TestCase_3();
  Mt_Pitch_Pitch_CheckSensValue_TestCase_4();
  Mt_Pitch_Pitch_CheckSensValue_TestCase_5();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_CheckSensMountingInit
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: This function is initializing global variables used for detection of 
///        plausibility errors on leveling sensors
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input   sPitch_DispSens.nDisp[1]   = 1u;
/// input   sPitch_DispSens.eSigQty[0] = 1u;
/// input   sPitch_DispSens.nDisp[0]   = 2u;
/// input   sPitch_DispSens.eSigQty[1] = 2u;
///
///   - Expectations:
///
///  \output Pitch_nSensFrontRInit = 2u
///   \output Pitch_nSensRearRInit  = 1u
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensMountingInit(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  sPitch_DispSens.nDisp[1]   = 1u;
  sPitch_DispSens.eSigQty[0] = 1u;
  sPitch_DispSens.nDisp[0]   = 2u;
  sPitch_DispSens.eSigQty[1] = 2u;

  //Step 3) Call FUT
  Pitch_CheckSensMountingInit();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Pitch_nSensFrontRInit, 2u, == );
  AL_UNITTEST_CHECK(Pitch_nSensRearRInit,  1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_CheckSensMounting_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: This function is checking the plausibility of the rear and front
///        leveling sensors and raises flags in case of errors
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  sPitch_DispSens.nDisp[0u]                     = 3u;
/// input  sPitch_DispSens.eSigQty[1u]                     = 2u;
/// input  Rte_Read_SysMon_VehicleSpeed_HitCount               = 0u;
/// input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty             = SIG_VALID;
/// input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 1600u;
///
///   - Expectations:
///
///  \output Rte_Read_SysMon_VehicleSpeed_HitCount = 1u;
///  \output Sens_Disp[1u]               = 1u;
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensMounting_TestCase_1(void)
{    
  //Step 1) Set pre-conditions
    //Step 2) Assign Input values                                  
  sPitch_DispSens.nDisp[0u]                     = 3u;
  sPitch_DispSens.eSigQty[1u]                     = 2u;
  Rte_Read_SysMon_VehicleSpeed_HitCount               = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty             = SIG_VALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 1600u;

  //Step 3) Call FUT
  Pitch_CheckSensMounting();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount,1u, == );
  AL_UNITTEST_CHECK(Sens_Disp[1u],            1u, == );
  
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_CheckSensMounting_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: This function is checking the plausibility of the rear and front
///        leveling sensors and raises flags in case of errors
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  sPitch_DispSens.nDisp[0u]                     = 3u;
/// input  sPitch_DispSens.eSigQty[1u]                     = 2u;
/// input  Rte_Read_SysMon_VehicleSpeed_HitCount               = 0u;
/// input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty             = SIG_INVALID;
/// input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 1600u;
///
///   - Expectations:
///
///  \output
///  \output Rte_Read_SysMon_VehicleSpeed_HitCount = 1u;
///  \output Sens_Disp[1u]               = 1u;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensMounting_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  sPitch_DispSens.nDisp[0u]                     = 3u;
  sPitch_DispSens.eSigQty[1u]                     = 2u;
  Rte_Read_SysMon_VehicleSpeed_HitCount               = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty             = SIG_INVALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 1600u;

  //Step 3) Call FUT
  Pitch_CheckSensMounting();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Sens_Disp[1u],             1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_CheckSensMounting_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: This function is checking the plausibility of the rear and front
///        leveling sensors and raises flags in case of errors
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  sPitch_DispSens.nDisp[1u]                     = 3u;
/// input  sPitch_DispSens.eSigQty[1u]                     = 2u;
/// input  Rte_Read_SysMon_VehicleSpeed_HitCount               = 0u;
/// input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty             = SIG_INVALID;
/// input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 1600u;
/// input  Rte_Read_IoHwAb_VCCX1Voltage_HitCount                 = 0u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Min           = 30u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Max           = 40u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unSensor_Error_Time     = 400u;
/// input  Rte_Read_IoHwAb_VCCX1Voltage_HitCount               = 0u;
/// input  Rte_Read_IoHwAb_VCCX1Voltage_Param1                 = 50u;
/// input  ucPitch_ErrCntVccxLoRR                       = 0u;
/// input  ucPitch_ErrCntVccxLoFR                       = 0u;
/// input  ucPitch_ErrCntVccxHiRR                       = 19u;
/// input  ucPitch_ErrCntVccxHiFR                       = 19u;
///
///   - Expectations:
///
///  \output
///  \output Rte_Read_SysMon_VehicleSpeed_HitCount = 1u;
///  \output Rte_Read_IoHwAb_VCCX1Voltage_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensMounting_TestCase_3(void)
{ 
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  sPitch_DispSens.nDisp[1u]                     = 3u;
  sPitch_DispSens.eSigQty[1u]                     = 2u;
  Rte_Read_SysMon_VehicleSpeed_HitCount               = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty             = SIG_INVALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 1600u;
  Rte_Read_IoHwAb_VCCX1Voltage_HitCount                 = 0u;
  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Min           = 30u;
  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Max           = 40u;
  Rte_Read_IoHwAb_VCCX1Voltage_Param1                 = 50u;
  ucPitch_ErrCntVccxLoRR                       = 0u;
  ucPitch_ErrCntVccxLoFR                       = 0u;
  ucPitch_ErrCntVccxHiRR                       = 19u;
  ucPitch_ErrCntVccxHiFR                       = 19u;

  //Step 3) Call FUT
  Pitch_CheckSensMounting();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_VCCX1Voltage_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_CheckSensMounting_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: This function is checking the plausibility of the rear and front
///        leveling sensors and raises flags in case of errors
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  sPitch_DispSens.nDisp[1u]                     = 3u;
/// input  sPitch_DispSens.eSigQty[1u]                     = 2u;
/// input  Rte_Read_SysMon_VehicleSpeed_HitCount               = 0u;
/// input  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty             = SIG_INVALID;
/// input  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 1600u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Min           = 30u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Max           = 40u;
/// input  Pitch_pCodingArea->AvacStp.PitchData.unSensor_Error_Time     = 400u;
/// input  Rte_Read_IoHwAb_VCCX1Voltage_HitCount               = 0u;
/// input  ucPitch_ErrCntVccxLoRR                       = 0u;
/// input  ucPitch_ErrCntVccxLoFR                       = 0u;
/// input  ucPitch_ErrCntVccxHiRR                       = 0u;
/// input  ucPitch_ErrCntVccxHiFR                       = 0u;
/// input  Rte_Read_IoHwAb_VCCX1Voltage_Param1                 = 35u;
///
///   - Expectations:
///
///  \output
///  \output Rte_Read_SysMon_VehicleSpeed_HitCount = 1u;
///  \output Rte_Read_IoHwAb_VCCX1Voltage_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensMounting_TestCase_4(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values

  sPitch_DispSens.nDisp[1u]                     = 3u;
  sPitch_DispSens.eSigQty[1u]                     = 2u;
  Rte_Read_SysMon_VehicleSpeed_HitCount               = 0u;
  Rte_Read_SysMon_VehicleSpeed_Param1.eSigQty             = SIG_INVALID;
  Rte_Read_SysMon_VehicleSpeed_Param1.eVehicleSpeed.unVehicleSpeed = 1600u;
  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Min           = 30u;
  Pitch_pCodingArea->AvacStp.PitchData.unVccx_Max           = 40u;
  Rte_Read_IoHwAb_VCCX1Voltage_HitCount               = 0u;
  ucPitch_ErrCntVccxLoRR                       = 0u;
  ucPitch_ErrCntVccxLoFR                       = 0u;
  ucPitch_ErrCntVccxHiRR                       = 0u;
  ucPitch_ErrCntVccxHiFR                       = 0u;
  Rte_Read_IoHwAb_VCCX1Voltage_Param1                 = 35u;

  //Step 3) Call FUT
  Pitch_CheckSensMounting();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_VCCX1Voltage_HitCount, 1u, == );
    
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_CheckSensMounting_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: This function does not check the plausibility of the rear and front
///        leveling sensors when filter thresholds are NOK
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  SensorPlausData.ucOkFilterThreshold  = 0u
/// input  SensorPlausData.ucErrFilterThreshold = 0u
/// input  SensorPlausData.ucOkFilterThreshold  = 0u
/// input  SensorPlausData.ucErrFilterThreshold = 0u
///
///   - Expectations:
///
///  \output
///  \output Rte_Read_SysMon_VehicleSpeed_HitCount = 1u;
///  \output Rte_Read_IoHwAb_VCCX1Voltage_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensMounting_TestCase_5(void)
{
  //Step 1: Set pre-conditions
  //Step 2) Assign Input values

  SensorPlausData.ucOkFilterThreshold   = 0u;
  SensorPlausData.ucErrFilterThreshold  = 0u;
  Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;
  Rte_Read_IoHwAb_VCCX1Voltage_HitCount = 0u;

  //Step 3) Call FUT
  Pitch_CheckSensMounting();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_VCCX1Voltage_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_CheckSensMounting_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: This function is checking the plausibility of the rear and front
///        leveling sensors and raises flags in case of errors
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  SensorPlausData.ucOkFilterThreshold   = 1u;
/// input  SensorPlausData.ucErrFilterThreshold  = 1u;
/// input  Pitch_nSensRearRGrad                  = 10u;
/// input  Pitch_nSensFrontRGrad                 = 10u;
/// input  Pitch_nSensRearRFilterPreErr          = 0u;
/// input  Pitch_nSensFrontRFilterPreErr         = 0u;
/// input  Pitch_nSensRearRHyst                  = 0u;
/// input  Pitch_nSensFrontRHyst                 = 0u;
/// input  Pitch_DT1SensRearRMounting            = 0u;
/// input  Pitch_DT1SensFrontRMounting           = 0u;
/// input  sPitch_DispSens.nDisp[0]              = 2u;
/// input  sPitch_DispSens.nDisp[1]              = 2u;
/// input  Pitch_nSensRearRFilterOk              = 0u;
/// input  Pitch_nSensFrontRFilterOk             = 0u;
///
///   - Expectations:
///
///  \output
///  \output Rte_Read_SysMon_VehicleSpeed_HitCount = 1u;
///  \output Rte_Read_IoHwAb_VCCX1Voltage_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensMounting_TestCase_6(void)
{
  //Step 1: Set pre-conditions
  SensorPlausData.ucOkFilterThreshold   = 1u;
  SensorPlausData.ucErrFilterThreshold  = 1u;
  Pitch_nSensRearRGrad                  = 10u;
  Pitch_nSensFrontRGrad                 = 10u;
  Pitch_nSensRearRFilterPreErr          = 0u;
  Pitch_nSensFrontRFilterPreErr         = 0u;
  Pitch_nSensRearRHyst                  = 0u;
  Pitch_nSensFrontRHyst                 = 0u;
  Pitch_DT1SensRearRMounting            = 0u;
  Pitch_DT1SensFrontRMounting           = 0u;
  sPitch_DispSens.nDisp[0]              = 2u;
  sPitch_DispSens.nDisp[1]              = 2u;
  Pitch_nSensRearRFilterOk              = 0u;
  Pitch_nSensFrontRFilterOk             = 0u;
  Rte_Read_SysMon_VehicleSpeed_HitCount = 0u;
  Rte_Read_IoHwAb_VCCX1Voltage_HitCount = 0u;

  //Step 2) Assign Input values

  //Step 3) Call FUT
  Pitch_CheckSensMounting();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_SysMon_VehicleSpeed_HitCount, 1u, == );
  AL_UNITTEST_CHECK(Rte_Read_IoHwAb_VCCX1Voltage_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Pitch_Pitch_CheckSensMounting
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if the function checks the plausibility data on front and rear sensors
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensMounting(void)
{
  Mt_Pitch_Pitch_CheckSensMounting_TestCase_1();
  Mt_Pitch_Pitch_CheckSensMounting_TestCase_2();
  Mt_Pitch_Pitch_CheckSensMounting_TestCase_3();
  Mt_Pitch_Pitch_CheckSensMounting_TestCase_4();
  Mt_Pitch_Pitch_CheckSensMounting_TestCase_5();
  Mt_Pitch_Pitch_CheckSensMounting_TestCase_6();
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_CheckSensMountingState_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: This function is setting plausibility DTCs depending on error flags
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input   Pitch_biSensFrontRMountingStateErr      = 1u;
/// input   Pitch_biSensRearRMountingStateErr      = 0u;
/// input   Pitch_biSensFrontRMountingStateOk      = 0u;
/// input   Pitch_biSensRearRMountingStateErr      = 0u;
/// input   NvmBlockDeltaPwmPara.ucSensPlausError[0u] = FALSE;
/// input   NvmBlockDeltaPwmPara.ucSensPlausError[1u] = TRUE;
/// input   Pitch_biSensRearRMountingStateOk      = 0u;
/// input   Dem_SetEventStatus_HitCount            = 0u;
/// input   Dem_SetEventStatus_Param1          = FR_BHS_PLAUS_FAIL;
/// input   Dem_SetEventStatus_Param2            = DEM_EVENT_STATUS_FAILED;
///
///   - Expectations:
///
///  \output
///  \output Dem_SetEventStatus_HitCount   = 1u ;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensMountingState_TestCase_1()
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Pitch_biSensFrontRMountingStateErr      = 1u;
  Pitch_biSensRearRMountingStateErr      = 0u;
  Pitch_biSensFrontRMountingStateOk      = 0u;
  Pitch_biSensRearRMountingStateErr      = 0u;
  NvmBlockDeltaPwmPara.ucSensPlausError[0u] = FALSE;
  NvmBlockDeltaPwmPara.ucSensPlausError[1u] = TRUE;
  Pitch_biSensRearRMountingStateOk      = 0u;
  Dem_SetEventStatus_HitCount            = 0u;
  Dem_SetEventStatus_Param1          = FR_BHS_PLAUS_FAIL;
  Dem_SetEventStatus_Param2            = DEM_EVENT_STATUS_FAILED;

  //Step 3) Call FUT
   Pitch_CheckSensMountingState();

   //Step 4) Check expected output values
   AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,        1u, == );
   
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_CheckSensMountingState_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: This function is setting plausibility DTCs depending on error flags
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input   Pitch_biSensFrontRMountingStateErr        = 2u;
/// input   Pitch_biSensRearRMountingStateErr        = 0u;
/// input   Pitch_biSensFrontRMountingStateOk        = 1u;
/// input   Pitch_biSensRearRMountingStateOk      = 0u;
/// input   NvmBlockDeltaPwmPara.ucSensPlausError[1u] = FALSE;
/// input   NvmBlockDeltaPwmPara.ucSensPlausError[0u] = FALSE;
/// input   Dem_SetEventStatus_HitCount            = 0u;
/// input   Dem_SetEventStatus_Param1          = FR_BHS_PLAUS_FAIL;
/// input   Dem_SetEventStatus_Param2            = DEM_EVENT_STATUS_PASSED;
/// input   Rte_Read_IoHwAb_VCCX1Voltage_HitCount    = 0u;
///
///   - Expectations:
///
///  \output
///  \output Dem_SetEventStatus_HitCount   = 1u ;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensMountingState_TestCase_2()
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Pitch_biSensFrontRMountingStateErr        = 2u;
  Pitch_biSensRearRMountingStateErr        = 0u;
  Pitch_biSensFrontRMountingStateOk        = 1u;
  Pitch_biSensRearRMountingStateOk      = 0u;
  NvmBlockDeltaPwmPara.ucSensPlausError[1u] = FALSE;
  NvmBlockDeltaPwmPara.ucSensPlausError[0u] = FALSE;
  Dem_SetEventStatus_HitCount            = 0u;
  Dem_SetEventStatus_Param1          = FR_BHS_PLAUS_FAIL;
  Dem_SetEventStatus_Param2            = DEM_EVENT_STATUS_PASSED;
  Rte_Read_IoHwAb_VCCX1Voltage_HitCount    = 0u;
     
  //Step 3) Call FUT
  Pitch_CheckSensMountingState();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount,       1u, == );
  
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_CheckSensMountingState_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: This function is setting plausibility DTCs depending on error flags
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  Pitch_biSensFrontRMountingStateErr        = 2u;
/// input  Pitch_biSensRearRMountingStateErr        = 1u;
/// input  Pitch_biSensFrontRMountingStateOk        = 0u;
/// input  Pitch_biSensRearRMountingStateOk      = 0u;
/// input  NvmBlockDeltaPwmPara.ucSensPlausError[1u] = FALSE;
/// input  NvmBlockDeltaPwmPara.ucSensPlausError[0u] = TRUE;
/// input  Dem_SetEventStatus_HitCount            = 0u;
/// input  Dem_SetEventStatus_Param1          = RR_BHS_PLAUS_FAIL;
/// input  Dem_SetEventStatus_Param2            = DEM_EVENT_STATUS_FAILED;
/// input  Rte_Read_IoHwAb_VCCX1Voltage_HitCount    = 0u;
///
///   - Expectations:
///
///  \output
///  \output Dem_SetEventStatus_HitCount   = 1u ;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensMountingState_TestCase_3()
{  
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Pitch_biSensFrontRMountingStateErr        = 2u;
  Pitch_biSensRearRMountingStateErr        = 1u;
  Pitch_biSensFrontRMountingStateOk        = 0u;
  Pitch_biSensRearRMountingStateOk      = 0u;
  NvmBlockDeltaPwmPara.ucSensPlausError[1u] = FALSE;
  NvmBlockDeltaPwmPara.ucSensPlausError[0u] = TRUE;
  Dem_SetEventStatus_HitCount            = 0u;
  Dem_SetEventStatus_Param1          = RR_BHS_PLAUS_FAIL;
  Dem_SetEventStatus_Param2            = DEM_EVENT_STATUS_FAILED;
  Rte_Read_IoHwAb_VCCX1Voltage_HitCount    = 0u;

  //Step 3) Call FUT
  Pitch_CheckSensMountingState();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );;
}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_Pitch_CheckSensMountingState_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: This function is setting plausibility DTCs depending on error flags
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input    Pitch_biSensFrontRMountingStateErr        = 2u;
/// input    Pitch_biSensRearRMountingStateErr        = 0u;
/// input    Pitch_biSensFrontRMountingStateOk        = 0u;
/// input    Pitch_biSensRearRMountingStateOk      = 1u;
/// input    NvmBlockDeltaPwmPara.ucSensPlausError[1u] = FALSE;
/// input    NvmBlockDeltaPwmPara.ucSensPlausError[0u] = FALSE;
/// input    Dem_SetEventStatus_HitCount            = 0u;
/// input    Dem_SetEventStatus_Param1          = RR_BHS_PLAUS_FAIL;
/// input    Dem_SetEventStatus_Param2            = DEM_EVENT_STATUS_PASSED;
/// input    Rte_Read_IoHwAb_VCCX1Voltage_HitCount    = 0u;
///
///   - Expectations:
///
///  \output
///  \output Dem_SetEventStatus_HitCount   = 1u ;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensMountingState_TestCase_4()
{  
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Pitch_biSensFrontRMountingStateErr        = 2u;
  Pitch_biSensRearRMountingStateErr        = 0u;
  Pitch_biSensFrontRMountingStateOk        = 0u;
  Pitch_biSensRearRMountingStateOk      = 1u;
  NvmBlockDeltaPwmPara.ucSensPlausError[1u] = FALSE;
  NvmBlockDeltaPwmPara.ucSensPlausError[0u] = FALSE;
  Dem_SetEventStatus_HitCount            = 0u;
  Dem_SetEventStatus_Param1          = RR_BHS_PLAUS_FAIL;
  Dem_SetEventStatus_Param2            = DEM_EVENT_STATUS_PASSED;
  Rte_Read_IoHwAb_VCCX1Voltage_HitCount    = 0u;

  //Step 3) Call FUT
  Pitch_CheckSensMountingState();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Dem_SetEventStatus_HitCount, 1u, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Pitch_Pitch_CheckSensMountingState
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if the function sets the correct plausibility DTCs
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_CheckSensMountingState(void)
{
  Mt_Pitch_Pitch_CheckSensMountingState_TestCase_1();
  Mt_Pitch_Pitch_CheckSensMountingState_TestCase_2();
  Mt_Pitch_Pitch_CheckSensMountingState_TestCase_3();
  Mt_Pitch_Pitch_CheckSensMountingState_TestCase_4();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_riPitch_Init
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: This function is checking the plausibility of the rear and front
///        leveling sensors and raises flags in case of errors
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  sPitch_DispSens.nDisp[0u]                  = 1u;
/// input  sPitch_DispSens.eSigQty[0u]                  = 1u;
/// input  sPitch_DispSens.nDisp[1u]                  = 2u;
/// input  sPitch_DispSens.eSigQty[1u]                  = 2u;
/// input  Rte_Read_CodM_Pitch_Para_HitCount              = 0u;
/// input  Rte_Read_CodM_Pitch_Para_Param1.eCodingState        = eParaFct0_CodingDataValid ;
/// input  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
/// input  boPitch_CodingValidity                    = FALSE;
///
///   - Expectations:
///
///  \output
///  \output boPitch_CodingValidity            = TRUE;
///  \output Rte_Read_CodM_Pitch_Para_HitCount = 1u;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_riPitch_Init(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  sPitch_DispSens.nDisp[0u]                  = 1u;
  sPitch_DispSens.eSigQty[0u]                  = 1u;
  sPitch_DispSens.nDisp[1u]                  = 2u;
  sPitch_DispSens.eSigQty[1u]                  = 2u;
  Rte_Read_CodM_Pitch_Para_HitCount              = 0u;
  Rte_Read_CodM_Pitch_Para_Param1.eCodingState        = eParaFct0_CodingDataValid ;
  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
  boPitch_CodingValidity                    = FALSE;
  
  //Step 3) Call FUT
  riPitch_Init();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(boPitch_CodingValidity,         TRUE, == );
  AL_UNITTEST_CHECK(Rte_Read_CodM_Pitch_Para_HitCount,1u, == );
  
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Pitch_rpPitch_Cycle0
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: This function is checking the plausibility of the rear and front
///        leveling sensors and raises flags in case of errors
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  boPitch_CodingValidity                    = FALSE;
/// input  Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE      = eStpState_Ref;
/// input  Rte_Read_CodM_Pitch_Para_HitCount              = 0u;
/// input  Rte_Read_CodM_Pitch_Para_Param1.eCodingState        = eParaFct0_CodingDataValid;
/// input  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;
///
///   - Expectations:
///
///  \output
///  \output Rte_Read_CodM_Pitch_Para_HitCount = 1u;
///  \output boPitch_CodingValidity         = TRUE;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_rpPitch_Cycle0(void)
{ 
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  boPitch_CodingValidity                    = FALSE;
  Rte_Read_CtrlStp_Validation_Port_Param1.eADL_PHASE      = eStpState_Ref;
  Rte_Read_CodM_Pitch_Para_HitCount              = 0u;
  Rte_Read_CodM_Pitch_Para_Param1.eCodingState        = eParaFct0_CodingDataValid;
  Rte_Read_CodM_Pitch_Para_Param1.psCodingParameters_Blocks = &Coding_Dummy;

  //Step 3) Call FUT
  rpPitch_Cycle0();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CodM_Pitch_Para_HitCount,   1u, == );
  AL_UNITTEST_CHECK(boPitch_CodingValidity,         TRUE, == );
  
}


//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_RateLimiterPwmSens_TestCase_1()
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: This function is checking the plausibility of the rear and front
///        leveling sensors and raises flags in case of errors
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  RateLimiterPwmSens_Param2_Data = 4;
/// input  RateLimiterPwmSens_Param3_Data = 3;
/// input  RateLimiterPwmSens_Param4_Data = 19;
/// input  sint16               a = 12;
/// input  RateLimiterPwmSens_Param1_Data = &a;
///   - Expectations:
///
///  \output
///  \output *RateLimiterPwmSens_Param1_Data = 16;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_RateLimiterPwmSens_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  RateLimiterPwmSens_Param2_Data = 4;
  RateLimiterPwmSens_Param3_Data = 3;
  RateLimiterPwmSens_Param4_Data = 19;
  sint16             a = 12;
  RateLimiterPwmSens_Param1_Data = &a;
  
  //Step 3) Call FUT
  RateLimiterPwmSens(RateLimiterPwmSens_Param1_Data, RateLimiterPwmSens_Param2_Data, RateLimiterPwmSens_Param3_Data, RateLimiterPwmSens_Param4_Data);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(*RateLimiterPwmSens_Param1_Data, 16, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_RateLimiterPwmSens_TestCase_2()
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: This function is checking the plausibility of the rear and front
///        leveling sensors and raises flags in case of errors
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  RateLimiterPwmSens_Param2_Data = 2;
/// input  RateLimiterPwmSens_Param3_Data = 1;
/// input  RateLimiterPwmSens_Param4_Data = 6;
/// input  sint16 a             = 10;
/// input  RateLimiterPwmSens_Param1_Data = &a;
///   - Expectations:
///
///  \output
///  \output *RateLimiterPwmSens_Param1_Data = 9;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_RateLimiterPwmSens_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  RateLimiterPwmSens_Param2_Data = 2;
  RateLimiterPwmSens_Param3_Data = 1;
  RateLimiterPwmSens_Param4_Data = 6;
  sint16             a = 10;
  RateLimiterPwmSens_Param1_Data = &a;

  //Step 3) Call FUT
  RateLimiterPwmSens(RateLimiterPwmSens_Param1_Data, RateLimiterPwmSens_Param2_Data, RateLimiterPwmSens_Param3_Data, RateLimiterPwmSens_Param4_Data);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(*RateLimiterPwmSens_Param1_Data, 9, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :Mt_Pitch_RateLimiterPwmSens_TestCase_3()
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject: This function is checking the plausibility of the rear and front
///        leveling sensors and raises flags in case of errors
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions
///
/// input  RateLimiterPwmSens_Param2_Data = 2;
/// input  RateLimiterPwmSens_Param3_Data = 1;
/// input  RateLimiterPwmSens_Param4_Data = 12;
/// input  sint16             a = 10;
/// input  RateLimiterPwmSens_Param1_Data = &a;
///   - Expectations:
///
///  \output
///  \output *RateLimiterPwmSens_Param1_Data = 12;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_RateLimiterPwmSens_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  RateLimiterPwmSens_Param2_Data = 2;
  RateLimiterPwmSens_Param3_Data = 1;
  RateLimiterPwmSens_Param4_Data = 12;
  sint16             a = 10;
  RateLimiterPwmSens_Param1_Data = &a;

  //Step 3) Call FUT
  RateLimiterPwmSens(RateLimiterPwmSens_Param1_Data, RateLimiterPwmSens_Param2_Data, RateLimiterPwmSens_Param3_Data, RateLimiterPwmSens_Param4_Data);

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(*RateLimiterPwmSens_Param1_Data, 12, == );

}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Pitch_RateLimiterPwmSens
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if the function calculates the correct rate limit
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Pitch_RateLimiterPwmSens(void)
{
  Mt_Pitch_RateLimiterPwmSens_TestCase_1();
  Mt_Pitch_RateLimiterPwmSens_TestCase_2();
  Mt_Pitch_RateLimiterPwmSens_TestCase_3();
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_SetNvmFlag_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for writing the plausibility flag for each sensor inside
///        the NVM block, the writting starts only after 5 seconds so the 
///        sensor ok flag have time to be detected
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// input LPTMR0_GetTimeElapsed_RetVal       = 0xFFFFu;
/// input LPTMR0_GetTimeElapsed_HitCount     = 0u;
/// input boSensPlauCheck             = TRUE;
///   - Expectations:
///
/// \output LPTMR0_GetTimeElapsed_HitCount   = 1u
/// \output boSensPlauCheck             = FALSE
/// \output Pitch_SensPlau_CheckSensState_us = 0xFFFFu
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_SetNvmFlag_TestCase_1(void)
{ 
  //Step 1) Set pre-conditions
  //Step 2) Assign Input value  
     LPTMR0_GetTimeElapsed_RetVal   = 0xFFFFu;
     LPTMR0_GetTimeElapsed_HitCount = 0u;
     boSensPlauCheck          = TRUE;
  // Function call
  // Step 3) Call FUT

    Pitch_SetNvmFlag();

  // Outputs
  // Step 4) Check expected output values
  
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,           1u, == );
  AL_UNITTEST_CHECK(boSensPlauCheck,             FALSE, == );
  AL_UNITTEST_CHECK(Pitch_SensPlau_CheckSensState_us,     0xFFFFu, == );
  
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_SetNvmFlag_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for writing the plausibility flag for each sensor inside
///        the NVM block, the writting starts only after 5 seconds so the 
///        sensor ok flag have time to be detected
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// input  LPTMR0_GetTimeElapsed_HitCount     = 0u;
/// input  boSensPlauCheck             = FALSE;
/// input  Pitch_biSensFrontRMountingStateErr = 1u;
/// input  Pitch_biSensFrontRMountingStateOk  = 0u;
/// input  Pitch_biSensRearRMountingStateErr  = 2u;
/// input  Pitch_biSensRearRMountingStateOk   = 2u;
/// input  LPTMR0_GetTimeElapsed_RetVal     = 15u;
///
///   - Expectations:
///
/// \output LPTMR0_GetTimeElapsed_HitCount   = 1u;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_SetNvmFlag_TestCase_2(void)
{
    //Step 1) Set pre-conditions
    //Step 2) Assign Input value  
  LPTMR0_GetTimeElapsed_HitCount     = 0u;
  boSensPlauCheck             = FALSE;
  Pitch_biSensFrontRMountingStateErr = 1u;
  Pitch_biSensFrontRMountingStateOk  = 0u;
  Pitch_biSensRearRMountingStateErr  = 2u;
  Pitch_biSensRearRMountingStateOk   = 2u;
  LPTMR0_GetTimeElapsed_RetVal     = 15u;
  
  // Step 3) Call FUT
  Pitch_SetNvmFlag();

  // Outputs
  // Step 4) Check expected output values

  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,  1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_SetNvmFlag_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for writing the plausibility flag for each sensor inside
///        the NVM block, the writting starts only after 5 seconds so the 
///        sensor ok flag have time to be detected
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// input   LPTMR0_GetTimeElapsed_HitCount     = 0u;
/// input   Pitch_biSensFrontRMountingStateErr = 0u;
/// input   Pitch_biSensFrontRMountingStateOk  = 1u;
/// input   Pitch_biSensRearRMountingStateErr  = 2u;
/// input   Pitch_biSensRearRMountingStateOk   = 2u;
/// input   LPTMR0_GetTimeElapsed_RetVal     = 15u;
/// input   boSensPlauCheck             = FALSE;
///
///   - Expectations:
///
/// \output LPTMR0_GetTimeElapsed_HitCount   = 1u;
/// 
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_SetNvmFlag_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  LPTMR0_GetTimeElapsed_HitCount     = 0u;
  Pitch_biSensFrontRMountingStateErr = 0u;
  Pitch_biSensFrontRMountingStateOk  = 1u;
  Pitch_biSensRearRMountingStateErr  = 2u;
  Pitch_biSensRearRMountingStateOk   = 2u;
  LPTMR0_GetTimeElapsed_RetVal     = 15u;
  boSensPlauCheck             = FALSE;

  //Step 3) Call FUT
  Pitch_SetNvmFlag();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_SetNvmFlag_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for writing the plausibility flag for each sensor inside
///        the NVM block, the writting starts only after 5 seconds so the 
///        sensor ok flag have time to be detected
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// input  Pitch_biSensFrontRMountingStateErr = 2u;
/// input  Pitch_biSensFrontRMountingStateOk  = 2u;
/// input  Pitch_biSensRearRMountingStateErr  = 2u;
/// input  Pitch_biSensRearRMountingStateOk   = 2u;
/// input  LPTMR0_GetTimeElapsed_RetVal     = 15u;
/// input  boSensPlauCheck             = FALSE;
/// input  LPTMR0_GetTimeElapsed_HitCount     = 0u;
///
///   - Expectations:
///
/// \output 
/// LPTMR0_GetTimeElapsed_HitCount = 1u
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_SetNvmFlag_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values
  Pitch_biSensFrontRMountingStateErr = 2u;
  Pitch_biSensFrontRMountingStateOk  = 2u;
  Pitch_biSensRearRMountingStateErr  = 2u;
  Pitch_biSensRearRMountingStateOk   = 2u;
  LPTMR0_GetTimeElapsed_RetVal     = 15u;
  boSensPlauCheck             = FALSE;
  LPTMR0_GetTimeElapsed_HitCount     = 0u;

  //Step 3) Call FUT
  Pitch_SetNvmFlag();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
       
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_SetNvmFlag_TestCase_5
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for writing the plausibility flag for each sensor inside
///        the NVM block, the writting starts only after 5 seconds so the 
///        sensor ok flag have time to be detected
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// input  Pitch_biSensFrontRMountingStateErr = 2u;
/// input  Pitch_biSensFrontRMountingStateOk  = 2u;
/// input  Pitch_biSensRearRMountingStateErr  = 1u;
/// input  Pitch_biSensRearRMountingStateOk   = 0u;
/// input  LPTMR0_GetTimeElapsed_RetVal     = 15u;
/// input  boSensPlauCheck             = FALSE;
/// input  LPTMR0_GetTimeElapsed_HitCount     = 0u;
///
///   - Expectations:
///
/// \output 
/// \output LPTMR0_GetTimeElapsed_HitCount = 1u ;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_SetNvmFlag_TestCase_5(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Pitch_biSensFrontRMountingStateErr = 2u;
  Pitch_biSensFrontRMountingStateOk  = 2u;
  Pitch_biSensRearRMountingStateErr  = 1u;
  Pitch_biSensRearRMountingStateOk   = 0u;
  LPTMR0_GetTimeElapsed_RetVal     = 15u;
  boSensPlauCheck             = FALSE;
  LPTMR0_GetTimeElapsed_HitCount     = 0u;
  //Step 3) Call FUT
  Pitch_SetNvmFlag();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
       
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_SetNvmFlag_TestCase_6
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for writing the plausibility flag for each sensor inside
///        the NVM block, the writting starts only after 5 seconds so the 
///        sensor ok flag have time to be detected
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// input  Pitch_biSensFrontRMountingStateErr = 2u;
/// input  Pitch_biSensFrontRMountingStateOk  = 2u;
/// input  Pitch_biSensRearRMountingStateErr  = 0u;
/// input  Pitch_biSensRearRMountingStateOk   = 1u;
/// input  LPTMR0_GetTimeElapsed_RetVal     = 15u;
/// input  boSensPlauCheck             = FALSE;
/// input  LPTMR0_GetTimeElapsed_HitCount     = 0u;
///
///   - Expectations:
///
/// \output 
/// \output LPTMR0_GetTimeElapsed_HitCount = 1u ;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_SetNvmFlag_TestCase_6(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Pitch_biSensFrontRMountingStateErr = 2u;
  Pitch_biSensFrontRMountingStateOk  = 2u;
  Pitch_biSensRearRMountingStateErr  = 0u;
  Pitch_biSensRearRMountingStateOk   = 1u;
  LPTMR0_GetTimeElapsed_RetVal     = 15u;
  boSensPlauCheck             = FALSE;
  LPTMR0_GetTimeElapsed_HitCount     = 0u;
  //Step 3) Call FUT
  Pitch_SetNvmFlag();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount, 1u, == );
       
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_Pitch_Pitch_SetNvmFlag_TestCase_7
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function for writing the plausibility flag for each sensor inside
///        the NVM block, the writting starts only after 5 seconds so the 
///        sensor ok flag have time to be detected
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// input  Pitch_biSensFrontRMountingStateErr      = 1u;
/// input  Pitch_biSensFrontRMountingStateOk      = 0u;
/// input  Pitch_biSensRearRMountingStateErr      = 2u;
/// input  Pitch_biSensRearRMountingStateOk      = 2u;
/// input  LPTMR0_GetTimeElapsed_RetVal        = 15u;
/// input  boSensPlauCheck                = FALSE;
/// input  LPTMR0_GetTimeElapsed_HitCount        = 0u;
/// input  NvmBlockDeltaPwmPara.ucSensPlausError[0u] = 23u;
/// input  NvmBlockDeltaPwmPara.ucSensPlausError[1u] = 23u;
/// input  NvM_WriteBlock_HitCount            = 0u;
///   - Expectations:
///
/// \output 
/// \output LPTMR0_GetTimeElapsed_HitCount           = 1u;
/// \output LPTMR0_GetTimeElapsed_HitCount           = 1u;
/// \output NvmBlockDeltaPwmPara.ucSensPlausError[0u]= 3u;
/// \output NvmBlockDeltaPwmPara.ucSensPlausError[1u]= 1u;
/// \output NvM_WriteBlock_HitCount              = 1u;
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_SetNvmFlag_TestCase_7(void)
{
  //Step 1) Set pre-conditions
  //Step 2) Assign Input values

  Pitch_biSensFrontRMountingStateErr        = 1u;
  Pitch_biSensFrontRMountingStateOk        = 0u;
  Pitch_biSensRearRMountingStateErr        = 2u;
  Pitch_biSensRearRMountingStateOk        = 2u;
  LPTMR0_GetTimeElapsed_RetVal          = 15u;
  boSensPlauCheck                  = FALSE;
  LPTMR0_GetTimeElapsed_HitCount          = 0u;
  NvmBlockDeltaPwmPara.ucSensPlausError[0u] = 23u;
  NvmBlockDeltaPwmPara.ucSensPlausError[1u] = 23u;
  NvM_WriteBlock_HitCount            = 0u;

  //Step 3) Call FUT
  Pitch_SetNvmFlag();

  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,            1u, == );
  AL_UNITTEST_CHECK(LPTMR0_GetTimeElapsed_HitCount,            1u, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.ucSensPlausError[0u], 3u, == );
  AL_UNITTEST_CHECK(NvmBlockDeltaPwmPara.ucSensPlausError[1u], 1u, == );
  AL_UNITTEST_CHECK(NvM_WriteBlock_HitCount,                 1u, == );
  
       
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Pitch_Pitch_SetNvmFlag
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if the function sets the correct plausibility flags inside the NVM
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_SetNvmFlag(void)
{
  Mt_Pitch_Pitch_SetNvmFlag_TestCase_1();
  Mt_Pitch_Pitch_SetNvmFlag_TestCase_2();
  Mt_Pitch_Pitch_SetNvmFlag_TestCase_3();
  Mt_Pitch_Pitch_SetNvmFlag_TestCase_4();
  Mt_Pitch_Pitch_SetNvmFlag_TestCase_5();
  Mt_Pitch_Pitch_SetNvmFlag_TestCase_6();
  Mt_Pitch_Pitch_SetNvmFlag_TestCase_7();
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_Pitch_Pitch_RteAccess_Get_GetAslPhase_TestCase_1
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function reads Dc Motor phase
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// input Rte_Read_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE = eDcmPhase_Adj
/// input Rte_Read_CtrlDcm_StatusParameters_Port_HitCount          = 0u
/// input Pitch_RteAccess_Get_GetAslPhase_Param1                   = ePitchState_Fail
///
///   - Expectations:
///
/// \output Rte_Read_CtrlDcm_StatusParameters_Port_HitCount  = 1u
/// \output Pitch_RteAccess_Get_GetAslPhase_Param1           = ePitchState_Adj
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_RteAccess_Get_GetAslPhase_TestCase_1(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE = eDcmPhase_Adj;
  Rte_Read_CtrlDcm_StatusParameters_Port_HitCount          = 0u;
  //Step 2) Assign Input values
  Pitch_RteAccess_Get_GetAslPhase_Param1 = ePitchState_Fail;

  //Step 3) Call FUT
  Pitch_RteAccess_Get_GetAslPhase(&Pitch_RteAccess_Get_GetAslPhase_Param1);
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CtrlDcm_StatusParameters_Port_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(Pitch_RteAccess_Get_GetAslPhase_Param1,             ePitchState_Adj, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_Pitch_Pitch_RteAccess_Get_GetAslPhase_TestCase_2
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function reads Dc Motor phase
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// input Rte_Read_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE = eDcmPhase_Init
/// input Rte_Read_CtrlDcm_StatusParameters_Port_HitCount          = 0u
/// input Pitch_RteAccess_Get_GetAslPhase_Param1                   = ePitchState_Fail
///
///   - Expectations:
///
/// \output Rte_Read_CtrlDcm_StatusParameters_Port_HitCount  = 1u
/// \output Pitch_RteAccess_Get_GetAslPhase_Param1           = ePitchState_Init
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_RteAccess_Get_GetAslPhase_TestCase_2(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE = eDcmPhase_Init;
  Rte_Read_CtrlDcm_StatusParameters_Port_HitCount          = 0u;
  //Step 2) Assign Input values
  Pitch_RteAccess_Get_GetAslPhase_Param1 = ePitchState_Fail;

  //Step 3) Call FUT
  Pitch_RteAccess_Get_GetAslPhase(&Pitch_RteAccess_Get_GetAslPhase_Param1);
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CtrlDcm_StatusParameters_Port_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(Pitch_RteAccess_Get_GetAslPhase_Param1,            ePitchState_Init, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_Pitch_Pitch_RteAccess_Get_GetAslPhase_TestCase_3
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function reads Dc Motor phase
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// input Rte_Read_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE = eDcmPhase_Fail
/// input Rte_Read_CtrlDcm_StatusParameters_Port_HitCount          = 0u
/// input Pitch_RteAccess_Get_GetAslPhase_Param1                   = ePitchState_Adj
///
///   - Expectations:
///
/// \output Rte_Read_CtrlDcm_StatusParameters_Port_HitCount  = 1u
/// \output Pitch_RteAccess_Get_GetAslPhase_Param1           = ePitchState_Fail
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_RteAccess_Get_GetAslPhase_TestCase_3(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE = eDcmPhase_Fail;
  Rte_Read_CtrlDcm_StatusParameters_Port_HitCount          = 0u;
  //Step 2) Assign Input values
  Pitch_RteAccess_Get_GetAslPhase_Param1 = ePitchState_Adj;

  //Step 3) Call FUT
  Pitch_RteAccess_Get_GetAslPhase(&Pitch_RteAccess_Get_GetAslPhase_Param1);
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CtrlDcm_StatusParameters_Port_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(Pitch_RteAccess_Get_GetAslPhase_Param1,            ePitchState_Fail, == );
}

//-----------------------------------------------------------------------------
/// \Test Case : void Mt_Pitch_Pitch_RteAccess_Get_GetAslPhase_TestCase_4
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Check this function reads Dc Motor phase
///
///    - Test Design Technique: ET (Exploratory Testing)
///
///    - Preconditions:
///
/// input Rte_Read_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE = 40u
/// input Rte_Read_CtrlDcm_StatusParameters_Port_HitCount          = 0u
/// input Pitch_RteAccess_Get_GetAslPhase_Param1                   = ePitchState_Adj
///
///   - Expectations:
///
/// \output Rte_Read_CtrlDcm_StatusParameters_Port_HitCount  = 1u
/// \output Pitch_RteAccess_Get_GetAslPhase_Param1           = ePitchState_Adj
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_RteAccess_Get_GetAslPhase_TestCase_4(void)
{
  //Step 1) Set pre-conditions
  Rte_Read_CtrlDcm_StatusParameters_Port_Param1.eASL_PHASE = 40u;
  Rte_Read_CtrlDcm_StatusParameters_Port_HitCount          = 0u;
  //Step 2) Assign Input values
  Pitch_RteAccess_Get_GetAslPhase_Param1 = ePitchState_Adj;

  //Step 3) Call FUT
  Pitch_RteAccess_Get_GetAslPhase(&Pitch_RteAccess_Get_GetAslPhase_Param1);
  
  //Step 4) Check expected output values
  AL_UNITTEST_CHECK(Rte_Read_CtrlDcm_StatusParameters_Port_HitCount,                 1u, == );
  AL_UNITTEST_CHECK(Pitch_RteAccess_Get_GetAslPhase_Param1,             ePitchState_Adj, == );
}

//-----------------------------------------------------------------------------
/// \Test Case :  Mt_Pitch_Pitch_RteAccess_Get_GetAslPhase
///
/// \Functional Safety: NA
///
/// \Test Case Description
///    - Test subject:  Tests if the function reads the correct DC motor state
///
///    - Test Design Technique: ET (Exploratory Testing)
///
/// \Expected test results : All test cases contained are passed
///
//-----------------------------------------------------------------------------
void Mt_Pitch_Pitch_RteAccess_Get_GetAslPhase(void)
{
  Mt_Pitch_Pitch_RteAccess_Get_GetAslPhase_TestCase_1();
  Mt_Pitch_Pitch_RteAccess_Get_GetAslPhase_TestCase_2();
  Mt_Pitch_Pitch_RteAccess_Get_GetAslPhase_TestCase_3();
  Mt_Pitch_Pitch_RteAccess_Get_GetAslPhase_TestCase_4();
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
  //Pitch_Data.c
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_ParaFct0",                              Mt_Pitch_Pitch_ParaFct0);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_CodingDataValidation",                  Mt_Pitch_Pitch_CodingDataValidation);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_SetLocal_DisplacementSens",             Mt_Pitch_Pitch_SetLocal_DisplacementSens);
  ALUnitTest_AddFunction(" Mt_Pitch_RteAccess_Get_CodingPara",                    Mt_Pitch_Pitch_RteAccess_Get_CodingPara);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_RteAccess_Set_Angle",                   Mt_Pitch_Pitch_RteAccess_Set_Angle);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_RteAccess_Set_SensorFailureState",      Mt_Pitch_Pitch_RteAccess_Set_SensorFailureState); 
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_RteAccess_Get_VehicleSpeed",            Mt_Pitch_Pitch_RteAccess_Get_VehicleSpeed);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase",             Mt_Pitch_Pitch_RteAccess_Get_GetAdlPhase);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_RteAccess_Get_GetSens_Raw",             Mt_Pitch_Pitch_RteAccess_Get_GetSens_Raw);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_RteAccess_Get_GetSens_Balanced",        Mt_Pitch_Pitch_RteAccess_Get_GetSens_Balanced);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_RteAccess_Get_VCCX1Voltage",            Mt_Pitch_Pitch_RteAccess_Get_VCCX1Voltage);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_RteAccess_Get_VehNetState",             Mt_Pitch_Pitch_RteAccess_Get_VehNetState);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_CheckVehSpeedData",                     Mt_Pitch_Pitch_CheckVehSpeedData);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_FailureCheckPlausibility",              Mt_Pitch_Pitch_FailureCheckPlausibility);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_AdjustmentCheckPlausibility",           Mt_Pitch_Pitch_AdjustmentCheckPlausibility);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_SigWorst",                              Mt_Pitch_Pitch_SigWorst); 
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_GetLocal_DisplacementSens",             Mt_Pitch_Pitch_GetLocal_DisplacementSens);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_ErrCntInc",                             Mt_Pitch_Pitch_ErrCntInc);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_ErrCntDec",                             Mt_Pitch_Pitch_ErrCntDec);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_DispCalc",                              Mt_Pitch_Pitch_DispCalc);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_CheckSensSupply",                       Mt_Pitch_Pitch_CheckSensSupply);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_CheckSensorState",                      Mt_Pitch_Pitch_CheckSensorState);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_Init",                                  Mt_Pitch_Pitch_Init);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_ErrPassed",                             Mt_Pitch_Pitch_ErrPassed);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_AngleCalc",                             Mt_Pitch_Pitch_AngleCalc);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_DispMeasurement",                       Mt_Pitch_Pitch_DispMeasurement);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_PitchMeasurement",                      Mt_Pitch_Pitch_PitchMeasurement);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_Cycle0",                                Mt_Pitch_Pitch_Cycle0);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_CheckSensValue",                        Mt_Pitch_Pitch_CheckSensValue);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_CheckSensMountingInit",                 Mt_Pitch_Pitch_CheckSensMountingInit);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_CheckSensMounting",                     Mt_Pitch_Pitch_CheckSensMounting);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_CheckSensMountingState",                Mt_Pitch_Pitch_CheckSensMountingState);
  ALUnitTest_AddFunction(" Mt_Pitch_riPitch_Init",                                Mt_Pitch_riPitch_Init);
  ALUnitTest_AddFunction(" Mt_Pitch_rpPitch_Cycle0",                              Mt_Pitch_rpPitch_Cycle0);
  ALUnitTest_AddFunction(" Mt_Pitch_RateLimiterPwmSens",                          Mt_Pitch_RateLimiterPwmSens);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_SetNvmFlag",                            Mt_Pitch_Pitch_SetNvmFlag);
  ALUnitTest_AddFunction(" Mt_Pitch_Pitch_RteAccess_Get_GetAslPhase",             Mt_Pitch_Pitch_RteAccess_Get_GetAslPhase);
       
}

// EOF